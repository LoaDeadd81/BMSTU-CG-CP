#include "mainwindow.h"
#include "./ui_mainwindow.h"

#define HEIGHT 960
#define WIDTH 1580

#define SPHERE 0
#define PLANE 1
#define POL_MODEL 2
#define LIGHT 3

#define MODEL_TAB 0
#define LIGHT_TAB 1

#define COLOR_TAB 0
#define TEXTURE_TAB 1

const Color default_color = {200, 200, 200}, default_light_color = {255, 255, 255};
const Point3d default_spawn = {0, 0, 0}, default_light_spawn = {0, 0, 5};
const double default_r = 2, default_d = 1, default_i = 0.5;
const ObjectProperties default_props = ObjectProperties(1, 1, 10, 0, 0, 1);
const Vec3d default_normal = {0, 1, 0};

const double default_ambient = 0.5, default_world_mi = 1, focal_length = 1;
const int max_depth = 4, viewport_height = 1;
int thread_num = 4;

int sphere_num = 0, plane_num = 0, pol_num = 0, light_num = 0;

Point3d cam_or = {0, 0, 5};
Vec3d cam_dir = {0, 0, -1}, cam_up = {0, 1, 0};

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    init_ui();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_RenderButton_clicked()
{

//    int t_max = 20, n = 10;
//    for (int i = 1; i <= t_max; i++)
//    {
//        shared_ptr<BaseCommand> command = make_shared<RenderCommand>(renderer, i);
//
//        auto start = chrono::steady_clock::now();
//        for (int j = 0; j < n; j++)
//            manager.execute(command);
//        auto end = chrono::steady_clock::now();
//
//        cout << i << " : " << chrono::duration_cast<chrono::milliseconds>(end - start).count() / n << endl;
//            scene->addPixmap(QPixmap::fromImage(*image));
//    }

    scene->clear();
    drawer->clear();

    shared_ptr<BaseCommand> command = make_shared<RenderCommand>(renderer, thread_num);

    auto start = chrono::steady_clock::now();
    manager.execute(command);
    auto end = chrono::steady_clock::now();

    ui->label->setText(
            QString::fromStdString(to_string(chrono::duration_cast<chrono::milliseconds>(end - start).count())));

//    image->setPixelColor(100, 100, QColor(255, 0, 0));
    scene->addPixmap(QPixmap::fromImage(*image));
}


void MainWindow::on_AddObjectButton_clicked()
{

    int item_i = ui->ModelComboBox->currentIndex();
    QString name;
    QVariant var;
    bool is_light = false;

    shared_ptr<BaseCommand> com;
    if (item_i == SPHERE)
    {
        com = make_shared<AddModelCommand>(make_shared<Sphere>(default_spawn, default_r, default_color, default_props));
        sphere_num++;
        name = "Сфера " + QString::number(sphere_num);
    }
    else if (item_i == PLANE)
    {
        com = make_shared<AddModelCommand>(make_shared<Plane>(default_normal, default_d, default_color, default_props));
        plane_num++;
        name = "Плоскость " + QString::number(plane_num);
    }
    else if (item_i == POL_MODEL)
    {
        com = makePolModelAddCommand();
        if (!com)
            return;
        pol_num++;
        name = "Модель " + QString::number(pol_num);
    }
    else if (item_i == LIGHT)
    {
        com = make_shared<AddLightCommand>(make_shared<Light>(default_light_spawn, default_i, default_light_color));
        light_num++;
        name = "Точечный источник " + QString::number(light_num);
        is_light = true;
    }

    manager.execute(com);

    auto item = new QListWidgetItem(name);

    if (is_light)
    {
        var = QVariant::fromValue(dynamic_pointer_cast<AddCommand>(com)->l_iter);
        item->setData(Qt::UserRole, var);
        ui->llistWidget->addItem(item);
    }
    else
    {
        var = QVariant::fromValue(dynamic_pointer_cast<AddCommand>(com)->m_iter);
        item->setData(Qt::UserRole, var);
        ui->mlistWidget->addItem(item);
    }

//    Color red{255, 0, 0}, gren{0, 255, 0}, blue{0, 0, 255}, yellow{255, 255, 0}, black{0, 0, 0}, white{230, 230, 230};
//    Point3d p = {0, 1, 0}, p2 = {-5, -5, -20}, p3 = {0, 0, -20}, p4 = {4, 4, -20}, l = {5, 5, 0}, l2 = {-5, -5, 0},
//            n1 = {1, 0, 0}, n2 = {0, 0, 1};
//
//
//    shared_ptr<BaseCommand> com1, com2, com3, com4, com5, com6, com7, com8, com9, com10, com11, com12, com13;
//
//    com1 = make_shared<AddModelCommand>(make_shared<Plane>(p, 10, default_color, default_props));
//    com2 = make_shared<AddModelCommand>(make_shared<Sphere>(p2, 2, gren, ObjectProperties(1, 1, 100, 0, 0, 1)));
//    com3 = make_shared<AddModelCommand>(make_shared<Sphere>(p3, 2, black, ObjectProperties(1, 1, 10, 1, 0, 1)));
//    com4 = make_shared<AddModelCommand>(make_shared<Sphere>(p4, 2, black, ObjectProperties(1, 1, 10, 0, 1, 1.5)));
//    com5 = make_shared<AddLightCommand>(make_shared<Light>(l, 0.5, white));
//    com6 = make_shared<AddLightCommand>(make_shared<Light>(l2, 0.5, white));
//    com7 = make_shared<AddModelCommand>(make_shared<Plane>(p, -10, white, default_props));
//    com8 = make_shared<AddModelCommand>(make_shared<Plane>(n1, -10, red, default_props));
//    com9 = make_shared<AddModelCommand>(make_shared<Plane>(n1, 10, gren, default_props));
//    com10 = make_shared<AddModelCommand>(make_shared<Plane>(n2, 60, blue, default_props));
//
//    manager.execute(com1);
//    manager.execute(com2);
//    manager.execute(com3);
//    manager.execute(com4);
//    manager.execute(com5);
//    manager.execute(com6);
//    manager.execute(com7);
//    manager.execute(com8);
//    manager.execute(com9);
//    manager.execute(com10);

}


void MainWindow::on_DelObjectButton_clicked()
{
    int index = ui->ListTab->currentIndex();
    shared_ptr<BaseCommand> command;

    if (index == MODEL_TAB)
    {
        auto items = mSelectedItems();
        if (items.empty())
            return;

        Scene::ModelIter iter;
        for (auto &it: items)
        {
            iter = it->data(Qt::UserRole).value<Scene::ModelIter>();
            command = make_shared<DelModelCommand>(iter);
            delete it;
        }
    }
    else if (index == LIGHT_TAB)
    {
        auto items = lSelectedItems();
        if (items.empty())
            return;

        Scene::LightIter iter;
        for (auto &it: items)
        {
            iter = it->data(Qt::UserRole).value<Scene::LightIter>();
            command = make_shared<DelLightCommand>(iter);
            delete it;
        }
    }

    manager.execute(command);
}

void MainWindow::init_ui()
{
    auto cam = make_shared<Camera>(cam_or, cam_dir, cam_up);
    manager = SceneManager(cam);

    scene = make_shared<QGraphicsScene>(0, 0, WIDTH, HEIGHT, this);
    ui->GraphicsView->setScene(scene.get());

    ui->mTextureView->setScene(new QGraphicsScene());
    ui->mColorView->setScene(new QGraphicsScene());
    ui->lColorView->setScene(new QGraphicsScene());

    image = make_shared<QImage>(WIDTH, HEIGHT, QImage::Format_RGB32);

    render_props = RenderProperties(WIDTH, HEIGHT, viewport_height, focal_length, default_ambient, max_depth,
                                    default_world_mi);
    drawer = make_shared<QtDrawer>(image);
    renderer = make_shared<RayTracingRendered>(drawer, render_props);

    ui->ModelComboBox->addItem("Шар");
    ui->ModelComboBox->addItem("Плоскость");
    ui->ModelComboBox->addItem("Полигональная модель");
    ui->ModelComboBox->addItem("Точечный источник света");
}

shared_ptr<BaseCommand> MainWindow::makePolModelAddCommand()
{
    std::string path = QFileDialog::getOpenFileName().toStdString();

    try
    { loader.LoadFile(path); }
    catch (exception &e)
    {
        cout << e.what();
        return nullptr;
    }
    return make_shared<AddModelCommand>(
            make_shared<PolygonalBoundedModel>(loader.LoadedMeshes[0], default_color, default_props));
}

void MainWindow::on_mMoveButoon_clicked()
{
    auto items = mSelectedItems();
    if (items.empty())
        return;

    Scene::ModelIter iter;
    Vec3d data = {ui->mmxSB->value(), ui->mmySB->value(), ui->mmzSB->value()};
    shared_ptr<BaseCommand> com;
    for (auto &it: items)
    {
        iter = it->data(Qt::UserRole).value<Scene::ModelIter>();
        com = make_shared<TransformModelCommand>(data, TransformType::MOVE, iter);
        manager.execute(com);
    }
}


void MainWindow::on_mRotateButton_clicked()
{
    auto items = mSelectedItems();
    if (items.empty())
        return;

    Scene::ModelIter iter;
    Vec3d data = {ui->mrxSB->value(), ui->mrySB->value(), ui->mrzSB->value()};
    shared_ptr<BaseCommand> com;
    for (auto &it: items)
    {
        iter = it->data(Qt::UserRole).value<Scene::ModelIter>();
        com = make_shared<TransformModelCommand>(data, TransformType::ROTATE, iter);
        manager.execute(com);
    }
}


void MainWindow::on_mScaleButton_clicked()
{
    auto items = mSelectedItems();
    if (items.empty())
        return;

    Scene::ModelIter iter;
    Vec3d data = {ui->msxSB->value(), ui->msySB->value(), ui->mszSB->value()};
    shared_ptr<BaseCommand> com;
    for (auto &it: items)
    {
        iter = it->data(Qt::UserRole).value<Scene::ModelIter>();
        com = make_shared<TransformModelCommand>(data, TransformType::SCALE, iter);
        manager.execute(com);
    }
}


void MainWindow::on_mColorButton_clicked()
{
    auto items = mSelectedItems();
    if (items.empty())
        return;

    QColor clr = QColorDialog::getColor(Qt::gray, this, QStringLiteral("Выберите цвет модели"));
    if (clr.spec() == QColor::Invalid)
        return;

    set_mColor(clr);

    Scene::ModelIter iter;
    Color color = {double(clr.red()), double(clr.green()), double(clr.blue())};
    for (auto &it: items)
    {
        iter = it->data(Qt::UserRole).value<Scene::ModelIter>();
        iter->get()->setColor(color);
    }
}


void MainWindow::on_mApplyButton_clicked()
{
    auto items = mSelectedItems();
    if (items.empty())
        return;

    Scene::ModelIter iter;
    double diffuse = ui->mDiffuseDB->value(),
            specular = ui->mMirrorSB->value(),
            shine = ui->mShineSB->value(),
            reflective = ui->mReflSB->value(),
            refraction = ui->mRefrSB->value(),
            mi = ui->mmiSB->value();
    ObjectProperties props(diffuse, specular, shine, reflective, refraction, mi);

    for (auto &it: items)
    {
        iter = it->data(Qt::UserRole).value<Scene::ModelIter>();
        iter->get()->props() = props;
    }

}

void MainWindow::set_mColor(Color color)
{
    ui->ModelCTTab->setCurrentIndex(COLOR_TAB);
    ui->mColorView->scene()->setBackgroundBrush(QColor(color));
}

void MainWindow::set_mTexture(shared_ptr<BaseTexture> &texture)
{
    ui->ModelCTTab->setCurrentIndex(TEXTURE_TAB);
    QImage img = dynamic_pointer_cast<QImageTexture>(texture)->
            img.scaled(ui->mTextureView->width(), ui->mTextureView->height());
    ui->mTextureView->scene()->addPixmap(QPixmap::fromImage(img));
}

void MainWindow::set_mProps(ObjectProperties &props)
{
    ui->mDiffuseDB->setValue(props.diffuse);
    ui->mMirrorSB->setValue(props.specular);
    ui->mShineSB->setValue(props.shine);
    ui->mReflSB->setValue(props.reflective);
    ui->mRefrSB->setValue(props.refraction);
    ui->mmiSB->setValue(props.mi);
}

void MainWindow::on_mlistWidget_itemClicked(QListWidgetItem *item)
{
    QListWidgetItem *cur = ui->mlistWidget->currentItem();
    if (!cur)
        return;
    Scene::ModelIter iter = cur->data(Qt::UserRole).value<Scene::ModelIter>();

    if (iter->get()->hasTecture())
        set_mTexture(iter->get()->txtr());
    else
        set_mColor(iter->get()->clr());
    set_mProps(iter->get()->props());
}


void MainWindow::on_lMoveButoon_clicked()
{
    auto items = lSelectedItems();
    if (items.empty())
        return;

    Scene::LightIter iter;
    Vec3d data = {ui->lmxSB->value(), ui->lmySB->value(), ui->lmzSB->value()};
    shared_ptr<BaseCommand> com;
    for (auto &it: items)
    {
        iter = it->data(Qt::UserRole).value<Scene::LightIter>();
        com = make_shared<TransformLightCommand>(data, TransformType::MOVE, iter);
        manager.execute(com);
    }
}


void MainWindow::on_lColorButton_clicked()
{
    auto items = lSelectedItems();
    if (items.empty())
        return;

    QColor clr = QColorDialog::getColor(Qt::gray, this, QStringLiteral("Выберите цвет модели"));
    if (clr.spec() == QColor::Invalid)
        return;
    ui->lColorView->scene()->setBackgroundBrush(clr);

    Scene::LightIter iter;
    Color color = {double(clr.red()), double(clr.green()), double(clr.blue())};
    for (auto &it: items)
    {
        iter = it->data(Qt::UserRole).value<Scene::LightIter>();
        iter->get()->setColor(color);
    }
}


void MainWindow::on_lApplyButton_clicked()
{
    auto items = lSelectedItems();
    if (items.empty())
        return;

    Scene::LightIter iter;
    double i = ui->lIntesiveSB->value();
    for (auto &it: items)
    {
        iter = it->data(Qt::UserRole).value<Scene::LightIter>();
        iter->get()->setI(i);
    }
}


void MainWindow::on_llistWidget_itemClicked(QListWidgetItem *item)
{
    QListWidgetItem *cur = ui->llistWidget->currentItem();
    if (!cur)
        return;
    Scene::LightIter iter = cur->data(Qt::UserRole).value<Scene::LightIter>();

    set_lData(iter->get()->color, iter->get()->I);
}

void MainWindow::set_lData(Color &color, double i)
{
    ui->lColorView->scene()->setBackgroundBrush(QColor(color));
    ui->lIntesiveSB->setValue(i);
}


void MainWindow::on_wApplyButton_clicked()
{
    renderer->getProps().ambient = ui->wAmbSB->value();
    renderer->getProps().mi_world = ui->wmiSB->value();
    renderer->getProps().f_len = ui->fLenSB->value();
    thread_num = ui->threadSB->value();
}


void MainWindow::on_mTexturButton_clicked()
{
    auto items = mSelectedItems();
    if (items.empty())
        return;

    Scene::ModelIter iter;
    std::string path = QFileDialog::getOpenFileName().toStdString();
    if (path.empty())
        return;

    shared_ptr<BaseTexture> tex = make_shared<QImageTexture>(path);

    set_mTexture(tex);

    for (auto &it: items)
    {
        iter = it->data(Qt::UserRole).value<Scene::ModelIter>();
        iter->get()->setTexture(tex);
    }
}

QList<QListWidgetItem *> MainWindow::mSelectedItems()
{
    return ui->mlistWidget->selectedItems();
}

QList<QListWidgetItem *> MainWindow::lSelectedItems()
{
    return ui->llistWidget->selectedItems();
}


void MainWindow::on_cMoveButoon_clicked()
{
    manager.getScene()->cam()->move(ui->cmxSB->value(), ui->cmySB->value(), ui->cmzSB->value());
}


void MainWindow::on_mRotateButton_2_clicked()
{
    manager.getScene()->cam()->rotate(ui->crxSB->value(), ui->crySB->value(), ui->crzSB->value());
}

