#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qaction.h>
#include <qtoolbar.h>
#include <qfiledialog.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);
    ui->gridLayout->addWidget(view);

    view->setRenderHint(QPainter::Antialiasing);
    view->setDragMode(QGraphicsView::ScrollHandDrag);

    // Toolbar
    QToolBar *toolbar = addToolBar("Tools");

    QAction *loadAct = toolbar->addAction("Load Image");
    QAction *zoomInAct = toolbar->addAction("Zoom In");
    QAction *zoomOutAct = toolbar->addAction("Zoom Out");

    connect(loadAct, &QAction::triggered, this, &MainWindow::loadImage);
    connect(zoomInAct, &QAction::triggered, this, &MainWindow::zoomIn);
    connect(zoomOutAct, &QAction::triggered, this, &MainWindow::zoomOut);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadImage()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Open Image", "", "Images (*.png *.jpg *.bmp)");

    if (filePath.isEmpty())
        return;

    QPixmap pixmap(filePath);

    scene->clear();
    imageItem = scene->addPixmap(pixmap);

    view->fitInView(imageItem, Qt::KeepAspectRatioByExpanding);

    scaleFactor = 1.0;
}

void MainWindow::zoomIn()
{
    scaleFactor *= 1.2;
    view->scale(1.2, 1.2);
}

void MainWindow::zoomOut()
{
    scaleFactor /= 1.2;
    view->scale(1 / 1.2, 1 / 1.2);
}
