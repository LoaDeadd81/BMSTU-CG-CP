#include "mainwindow.h"
#include "./ui_mainwindow.h"

#define HEIGHT 960
#define WIDTH 1580

#define MODELS 0
#define LIGHTS 1
#define Camera 2

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = make_shared<QGraphicsScene>(0, 0, WIDTH, HEIGHT, this);
    ui->GraphicsView->setScene(scene.get());

    pixmap = make_shared<QPixmap>(WIDTH, HEIGHT);

    //todo
    render_props = RenderProperties(WIDTH, HEIGHT, 1, 1, 0.1, 3);
    drawer = make_shared<QtDrawer>(pixmap);
    renderer = make_shared<RayTracingRendered>(drawer, render_props);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_RenderButton_clicked()
{
    shared_ptr<BaseCommand> command = make_shared<RenderCommand>(renderer);

    manager.execute(command);

//    const int N = 4;
//    int dir_arr[N][2] = {{-1, 0},
//                         {1,  0},
//                         {0,  -1},
//                         {0,  1}};
//
//    QImage img = pixmap->toImage();
//
//    for (int j = 1; j < HEIGHT - 1; j++)
//    {
//        for (int i = 1; i < WIDTH - 1; i++)
//        {
//            Vec3d arr;
//            for (auto & k : dir_arr)
//            {
//                QColor color = img.pixelColor(i + k[0], HEIGHT - (j + k[1]));
//                arr[0] += color.red();
//                arr[1] += color.green();
//                arr[2] += color.blue();
//            }
//
//            arr /= N;
//
//            drawer->draw_pixel(i, HEIGHT - j, arr);
//        }
//    }

    scene->addPixmap(*pixmap);
}


void MainWindow::on_AddObjectButton_clicked()
{
    //todo rework
    Color red{255, 0, 0}, gren{0, 255, 0}, blue{0, 0, 255}, yellow{255, 255, 0}, black{0, 0, 0}, white{230, 230, 230};
    Point3d p = {0, 1, 0}, p2 = {-5, -5, -20}, p3 = {0, 2, -20}, p4 = {8, 8, -20}, l = {5, 5, -5}, l2 = {7, 7, -5},
            n1 = {1, 0, 0}, n2 = {0, 0, 1};

    shared_ptr<BaseCommand> com1, com2, com3, com4, com5, com6, com7, com8, com9, com10;

    com1 = make_shared<AddModelCommand>(make_shared<Plane>(p, 10, white, ObjectProperties(1, 1, 1, 0, 0)));
    com2 = make_shared<AddModelCommand>(make_shared<Sphere>(p2, 2, red, ObjectProperties(1, 1, 1, 0, 0)));
    com3 = make_shared<AddModelCommand>(make_shared<Sphere>(p3, 2, gren, ObjectProperties(1, 1, 1, 0, 0)));
    com4 = make_shared<AddModelCommand>(make_shared<Sphere>(p4, 2, black, ObjectProperties(1, 1, 1, 0, 0.8)));
    com5 = make_shared<AddLightCommand>(make_shared<Light>(l, 0.5));
    com6 = make_shared<AddLightCommand>(make_shared<Light>(l2, 0.5));
    com7 = make_shared<AddModelCommand>(make_shared<Plane>(p, -10, white, ObjectProperties(1, 1, 1, 0, 0)));
    com8 = make_shared<AddModelCommand>(make_shared<Plane>(n1, -10, red, ObjectProperties(1, 1, 1, 0, 0)));
    com9 = make_shared<AddModelCommand>(make_shared<Plane>(n1, 10, gren, ObjectProperties(1, 1, 1, 0, 0)));
    com10 = make_shared<AddModelCommand>(make_shared<Plane>(n2, 25, blue, ObjectProperties(1, 1, 1, 0, 0)));

    manager.execute(com1);
    manager.execute(com2);
    manager.execute(com3);
    manager.execute(com4);
    manager.execute(com5);
//    manager.execute(com6);
    manager.execute(com7);
    manager.execute(com8);
    manager.execute(com9);
    manager.execute(com10);
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
