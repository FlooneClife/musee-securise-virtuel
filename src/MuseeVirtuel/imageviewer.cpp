#include "imageviewer.h"
#include "ui_imageviewer.h"

ImageViewer::ImageViewer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ImageViewer)
{
    ui->setupUi(this);

    //trouver un moyen d'ouvrir l'image sans chemin global
    QImage image("K:/Users/Documents/#Floone/Cours/UM COURS/S3/Image et compression/PROJET/Qt/MuseeVirtuel/img/img2.ppm");
    ui->imageLabel->setPixmap(QPixmap::fromImage(image));
    ui->imageLabel->setScaledContents( true );
    ui->imageLabel->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
}

ImageViewer::~ImageViewer()
{
    delete ui;
}

