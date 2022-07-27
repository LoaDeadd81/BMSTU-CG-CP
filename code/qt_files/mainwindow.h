#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>
#include <QGraphicsScene>
#include <QFileDialog>
#include <QMessageBox>
#include <QString>

#include "SceneInterface.h"
#include "Scene.h"
#include "Solution.h"
#include "Creator.h"
#include "Drawer.h"
#include "Coord.h"
#include "Error.h"

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_LoadButton_clicked();

    void on_LoadCamButton_clicked();

    void on_RotateButton_clicked();

    void on_ScaleButton_clicked();

    void on_MoveButton_clicked();

    void on_RemoveButton_clicked();

    void on_CamComboBox_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
    shared_ptr<SceneInterface> _interface;
    shared_ptr<BaseDrawer> _drawer;
    shared_ptr<QGraphicsScene> _scene;

    void init_scene();
    void show_error_message(QString message);
    void update_scene();
    void create_first_cam();
    string get_filename();
    void add_model();
    void add_cam();
    void remove_object(int i);
    bool check_del_available(int i);
    bool check_current_cam(int i);
    void switch_first_cam();

    Coord3d get_center();
    Coord3d get_move_data();
    Coord3d get_rotate_data();
    Coord3d get_scale_data();
};
#endif // MAINWINDOW_H
