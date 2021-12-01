#include "imageviewer.h"
#include "ui_imageviewer.h"
#include "decipher.h"

#include <QtWidgets>
#include <QFileDialog>
#include <QMessageBox>

#ifndef QT_NO_PRINTER
#include <QPrintDialog>
#endif

QString fileName;

ImageViewer::ImageViewer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ImageViewer)
{

    ui->setupUi(this);

    openAct = ui->openAct;
    exitAct = ui->exitAct;
    zoomInAct = ui->zoomInAct;
    zoomOutAct = ui->zoomOutAct;
    normalSizeAct = ui->normalSizeAct;
    fitToWindowAct = ui->fitToWindowAct;
    //-----
    selectAct = ui->selectAct;
    decipherAct = ui->decipherAct;

    imageLabel = new QLabel;
    imageLabel->setBackgroundRole(QPalette::Base);
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel->setScaledContents(true);

    scrollArea = new QScrollArea;
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(imageLabel);
    setCentralWidget(scrollArea);

    setWindowTitle(tr("Image Viewer"));
    resize(900, 900);

    connect(openAct,SIGNAL(triggered()),this,SLOT(open()));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));
    connect(zoomInAct, SIGNAL(triggered()), this, SLOT(zoomIn()));
    connect(zoomOutAct, SIGNAL(triggered()), this, SLOT(zoomOut()));
    connect(normalSizeAct, SIGNAL(triggered()), this, SLOT(normalSize()));
    connect(fitToWindowAct, SIGNAL(triggered()), this, SLOT(fitToWindow()));
    //-----
    connect(selectAct, SIGNAL(triggered()), this, SLOT(select()));
    connect(decipherAct, SIGNAL(triggered()), this, SLOT(decipher()));
}

ImageViewer::~ImageViewer()
{
    delete ui;
}

void ImageViewer::updateActions()
{
    zoomInAct->setEnabled(!fitToWindowAct->isChecked());
    zoomOutAct->setEnabled(!fitToWindowAct->isChecked());
    normalSizeAct->setEnabled(!fitToWindowAct->isChecked());
}

void ImageViewer::scaleImage(double factor)
{
    Q_ASSERT(imageLabel->pixmap());
    scaleFactor *= factor;
    imageLabel->resize(scaleFactor * imageLabel->pixmap()->size());

    adjustScrollBar(scrollArea->horizontalScrollBar(), factor);
    adjustScrollBar(scrollArea->verticalScrollBar(), factor);

    zoomInAct->setEnabled(scaleFactor < 3.0);
    zoomOutAct->setEnabled(scaleFactor > 0.333);
}

void ImageViewer::adjustScrollBar(QScrollBar *scrollBar, double factor)
{
    scrollBar->setValue(int(factor * scrollBar->value()
                            + ((factor - 1) * scrollBar->pageStep()/2)));
}

void ImageViewer::open()
{
    fileName = QFileDialog::getOpenFileName(this,
                                     tr("Open File"), QDir::currentPath());
    if (!fileName.isEmpty()) {
         QImage image(fileName);
         if (image.isNull()) {
             QMessageBox::information(this, tr("Image Viewer"),
                                      tr("Cannot load %1.").arg(fileName));
             return;
         }
         imageLabel->setPixmap(QPixmap::fromImage(image));
         scaleFactor = 1.0;

         fitToWindowAct->setEnabled(true);
         updateActions();

         if (!fitToWindowAct->isChecked())
             imageLabel->adjustSize();
    }
}

void ImageViewer::zoomIn()
{
    scaleImage(1.25);
}

void ImageViewer::zoomOut()
{
    scaleImage(0.8);
}

void ImageViewer::normalSize()
{
    imageLabel->adjustSize();
    scaleFactor = 1.0;
}

void ImageViewer::fitToWindow()
{
    bool fitToWindow = fitToWindowAct->isChecked();
    scrollArea->setWidgetResizable(fitToWindow);
    if (!fitToWindow) {
        normalSize();
    }
    updateActions();
}

void ImageViewer::select() {

}

void ImageViewer::decipher() {
    std::string str = fileName.toStdString();
    const char* fileNameIn = str.c_str();
    char* fileEnd = ".Dechiffre.ppm";
    char* fileNameOut;
    strcpy(fileNameOut, fileNameIn);
    strcat(fileNameOut, fileEnd);

    printf("%s\n", fileNameIn);
    lancerDechiffrage((char*)fileNameIn, fileNameOut, 20);

    QImage image(fileNameOut);
    imageLabel->setPixmap(QPixmap::fromImage(image));
    scaleFactor = 1.0;

    fitToWindowAct->setEnabled(true);
    updateActions();

    if (!fitToWindowAct->isChecked())
        imageLabel->adjustSize();
}
