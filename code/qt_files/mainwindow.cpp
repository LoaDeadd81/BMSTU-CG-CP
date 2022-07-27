#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _scene = make_shared<QGraphicsScene>(this);
    _scene->setSceneRect(0, 0, 1, 1);
    ui->graphicsView->setScene(_scene.get());

    init_scene();
    ui->ObjectComboBox->addItem("Все объекты");
    create_first_cam();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_LoadButton_clicked()
{
    string filename = get_filename();
    if (filename.empty())
    {
        show_error_message("Файл не выбран");
        return;
    }
    auto command = LoadObjectCommandCreator().create(filename);
    try
    { _interface->execute(LOAD_OBJECT, command); }
    catch (FileError &e)
    {
        show_error_message("Ошибка чтения из файла");
        return;
    }
    catch (BadModel &e)
    {
        show_error_message("Некорректные данные модели");
        return;
    }
    add_model();
    update_scene();
}


void MainWindow::on_LoadCamButton_clicked()
{
    string filename = get_filename();
    if (filename.empty())
    {
        show_error_message("Файл не выбран");
        return;
    }
    auto command = LoadCameraCommandCreator().create(filename);
    try
    { _interface->execute(LOAD_CAMERA, command); }
    catch (FileError &e)
    {
        show_error_message("Ошибка чтения из файла");
        return;
    }
    add_cam();
    update_scene();
}


void MainWindow::on_RotateButton_clicked()
{
    Coord3d data = get_rotate_data(), center = get_center();
    if (ui->ObjectComboBox->currentIndex() == 0)
    {
        for (int i = 2; i < ui->ObjectComboBox->count(); i++)
        {
            auto command = RotateCommandCreator().create(i - 1, data, center);
            _interface->execute(ROTATE, command);
        }
    }
    else
    {
        int i = ui->ObjectComboBox->currentIndex() - 1;
        auto command = RotateCommandCreator().create(i, data, center);
        _interface->execute(ROTATE, command);
    }
    update_scene();
}


void MainWindow::on_ScaleButton_clicked()
{
    Coord3d data = get_scale_data(), center = get_center();
    if (ui->ObjectComboBox->currentIndex() == 0)
    {
        for (int i = 2; i < ui->ObjectComboBox->count(); i++)
        {
            auto command = ScaleCommandCreator().create(i - 1, data, center);
            _interface->execute(SCALE, command);
        }
    }
    else
    {
        int i = ui->ObjectComboBox->currentIndex() - 1;
        auto command = ScaleCommandCreator().create(i, data, center);
        _interface->execute(SCALE, command);
    }
    update_scene();
}


void MainWindow::on_MoveButton_clicked()
{
    Coord3d data = get_move_data();
    if (ui->ObjectComboBox->currentIndex() == 0)
    {
        for (int i = 2; i < ui->ObjectComboBox->count(); i++)
        {
            auto command = MoveCommandCreator().create(i - 1, data);
            _interface->execute(MOVE, command);
        }
    }
    else
    {
        int i = ui->ObjectComboBox->currentIndex() - 1;
        auto command = MoveCommandCreator().create(i, data);
        _interface->execute(MOVE, command);
    }
    update_scene();
}


void MainWindow::on_RemoveButton_clicked()
{
    int i = ui->ObjectComboBox->currentIndex();
    if (!check_del_available(i))
    {
        show_error_message("Нельзя удалять единственную камеру");
        return;
    }
    if (check_current_cam(i))
        switch_first_cam();
    auto command = DelObjectCommandCreator().create(i - 1);
    try
    { _interface->execute(DEL, command); }
    catch (RangeError &e)
    {
        show_error_message("Нет объекта с таким индексом");
        return;
    }
    remove_object(i);
    update_scene();
}


void MainWindow::on_CamComboBox_currentIndexChanged(int index)
{
    int cam_index = ui->CamComboBox->currentData().toInt();
    auto cam_command = ChangeCameraCommandCreator().create(cam_index);
    try
    { _interface->execute(CHANGE_CAM, cam_command); }
    catch (RangeError &e)
    {
        show_error_message("Нет камеры с таким индексом");
        return;
    }
    update_scene();
}


void MainWindow::init_scene()
{
    shared_ptr<BaseScene> scene = make_shared<Scene>();
    _interface = make_shared<SceneInterface>(scene);

    shared_ptr<BaseCanvas> canvas = make_shared<QtCanvas>(_scene);
    shared_ptr<BaseDrawerFactory> factory = FabricSolution().get_creator()->create();
    _drawer = factory->create_drawer(canvas);
}

void MainWindow::show_error_message(QString message)
{
    QMessageBox msgBox;
    msgBox.setText(message);
    msgBox.setIcon(QMessageBox::Critical);
    msgBox.exec();
}

void MainWindow::update_scene()
{

    auto command = DrawCommandCreator().create(_drawer);
    try
    { _interface->execute(DRAW, command); }
    catch (CamExistError &e)
    {
        show_error_message("Для отрисовки необходима хотя бы 1 камера");
    }
}

void MainWindow::create_first_cam()
{
    string filename = "C:/Users/vvolk/Documents/GitHub/BMSTU-OOP/lab_03/lab_03/data/cam.txt";
    auto command = LoadCameraCommandCreator().create(filename);
    _interface->execute(LOAD_CAMERA, command);

    auto cam_command = ChangeCameraCommandCreator().create(0);
    _interface->execute(CHANGE_CAM, cam_command);
    ui->ObjectComboBox->addItem("Камера");
    ui->CamComboBox->addItem("Камера", 0);
}

string MainWindow::get_filename()
{
    auto dialog_filename = QFileDialog::getOpenFileName();
    return dialog_filename.toUtf8().data();
}

void MainWindow::add_model()
{
    ui->ObjectComboBox->addItem("Модель");
}

void MainWindow::add_cam()
{
    int i = ui->ObjectComboBox->count();
    ui->ObjectComboBox->addItem("Камера");
    ui->CamComboBox->addItem("Камера", i);
}

void MainWindow::remove_object(int i)
{
    int cam_index = ui->CamComboBox->findData(i);
    if (cam_index > -1)
        ui->CamComboBox->removeItem(cam_index);
    ui->ObjectComboBox->removeItem(i);
    for (int j = 0; j < ui->CamComboBox->count(); j++)
    {
        int data = ui->CamComboBox->itemData(j).toInt();
        if (data >= i)
            ui->CamComboBox->setItemData(j, data - 1);
    }
}

bool MainWindow::check_del_available(int i)
{
    int cam_index = ui->CamComboBox->findData(i);
    if (cam_index > -1 && ui->CamComboBox->count() < 2)
        return false;
    return true;
}

bool MainWindow::check_current_cam(int i)
{
    int cam_index = ui->CamComboBox->findData(i);
    if (cam_index > -1 && ui->CamComboBox->currentData().toInt() == i)
        return true;
    return false;
}

void MainWindow::switch_first_cam()
{
    int cam_index = ui->CamComboBox->itemData(0).toInt();
    auto cam_command = ChangeCameraCommandCreator().create(cam_index);
    _interface->execute(CHANGE_CAM, cam_command);
}

Coord3d MainWindow::get_center()
{
    double x = ui->xSpinBox->value(),
            y = ui->ySpinBox->value(),
            z = ui->zSpinBox->value();
    return {x, y, z};
}

Coord3d MainWindow::get_move_data()
{
    double dx = ui->dxSpinBox->value(),
            dy = ui->dySpinBox->value(),
            dz = ui->dzSpinBox->value();
    return {dx, dy, dz};
}

Coord3d MainWindow::get_rotate_data()
{
    double rx = ui->rxSpinBox->value(),
            ry = ui->rySpinBox->value(),
            rz = ui->rzSpinBox->value();
    return {rx, ry, rz};
}

Coord3d MainWindow::get_scale_data()
{
    double cx = ui->cxSpinBox->value(),
            cy = ui->cySpinBox->value(),
            cz = ui->czSpinBox->value();
    return {cx, cy, cz};
}




