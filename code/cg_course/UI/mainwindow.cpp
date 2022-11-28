#include "mainwindow.h"
#include "./ui_mainwindow.h"

#define HEIGHT 960
#define WIDTH 1580

#define MODELS 0
#define LIGHTS 1
#define Camera 1

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = make_shared<QGraphicsScene>(0, 0, WIDTH, HEIGHT, this);
    ui->GraphicsView->setScene(scene.get());

    pixmap = make_shared<QPixmap>(WIDTH, HEIGHT);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_RenderButton_clicked()
{
    shared_ptr<BaseDrawer> drawer = make_shared<QtDrawer>(pixmap);
    CameraProperties props = {WIDTH, HEIGHT, 3, 1};
    shared_ptr<BaseCommand> command = make_shared<RenderCommand>(drawer, props);

    manager.execute(command);

    scene->addPixmap(*pixmap);
}


void MainWindow::on_AddObjectButton_clicked()
{
    //todo rework
    Color red{255, 0, 0}, gren{0, 0, 255}, blue{0, 0, 255};
    Point3d p = {1, 1, -5}, p2 = {-1, 1, -5}, p3 = {1, -1, -5}, p4 = {-1, -1, -5};

    shared_ptr<BaseCommand> com1, com2, com3, com4;

    com1 = make_shared<AddModelCommand>(make_shared<Sphere>(p, 3));
    com2 = make_shared<AddModelCommand>(make_shared<Sphere>(p2, 2, red));
    com3 = make_shared<AddModelCommand>(make_shared<Sphere>(p3, 2, gren));
    com4 = make_shared<AddModelCommand>(make_shared<Sphere>(p4, 1, blue));

    manager.execute(com1);
    manager.execute(com2);
    manager.execute(com3);
    manager.execute(com4);
}


void MainWindow::on_DelObjectButton_clicked()
{
    shared_ptr<BaseCommand> command;

    int i = tabIndex();
    if (i == MODELS)
        command = make_shared<DelModelCommand>(modelIndex());
    else
        command = make_shared<DelLightCommand>(lightIndex());

    manager.execute(command);
}


void MainWindow::on_moveButoon_clicked()
{
    shared_ptr<BaseCommand> command;

    int i = tabIndex();
    if (i == MODELS)
        command = make_shared<TransformModelCommand>(moveData(), TransformType::MOVE, modelIndex());
    else if (i == LIGHTS)
        command = make_shared<TransformLightCommand>(moveData(), TransformType::MOVE, lightIndex());
    else
        command = make_shared<TransformCameraCommand>(moveData(), TransformType::MOVE);

    manager.execute(command);
}


void MainWindow::on_rotateButton_clicked()
{
    shared_ptr<BaseCommand> command;

    int i = tabIndex();
    if (i == MODELS)
        command = make_shared<TransformModelCommand>(moveData(), TransformType::ROTATE, modelIndex());
    else if (i == LIGHTS)
        command = make_shared<TransformLightCommand>(moveData(), TransformType::ROTATE, lightIndex());
    else
        command = make_shared<TransformCameraCommand>(moveData(), TransformType::ROTATE);

    manager.execute(command);
}


void MainWindow::on_ScaleButton_clicked()
{
    shared_ptr<BaseCommand> command;

    int i = tabIndex();
    if (i == MODELS)
        command = make_shared<TransformModelCommand>(moveData(), TransformType::SCALE, modelIndex());
    else if (i == LIGHTS)
        command = make_shared<TransformLightCommand>(moveData(), TransformType::SCALE, lightIndex());
    else
        command = make_shared<TransformCameraCommand>(moveData(), TransformType::SCALE);

    manager.execute(command);
}


void MainWindow::on_ColorButton_clicked()
{
    //todo
}


void MainWindow::on_TexturButton_clicked()
{
//todo
}

int MainWindow::tabIndex()
{//todo
    return 0;
}

int MainWindow::modelIndex()
{//todo
    return 0;
}

int MainWindow::lightIndex()
{//todo
    return 0;
}


Vec3d MainWindow::moveData()
{//todo
    return Vec3d();
}

Vec3d MainWindow::rotateData()
{//todo
    return Vec3d();
}

Vec3d MainWindow::scaleData()
{//todo
    return Vec3d();
}
