#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QPainter>
#include <QGraphicsScene>
#include <memory>
#include <list>
#include <QFileDialog>
#include <QListWidget>
#include <QColorDialog>

#include <ctime>
#include <string>
#include <chrono>

#include "SceneManager.h"
#include "Commands.h"

Q_DECLARE_METATYPE(Scene::ModelIter);

Q_DECLARE_METATYPE(Scene::LightIter);

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private slots:

    void on_RenderButton_clicked();

    void on_AddObjectButton_clicked();

    void on_DelObjectButton_clicked();

    void on_mMoveButoon_clicked();

    void on_mRotateButton_clicked();

    void on_mScaleButton_clicked();

    void on_mColorButton_clicked();

    void on_mApplyButton_clicked();

    void on_mlistWidget_itemClicked(QListWidgetItem *item);

    void on_lMoveButoon_clicked();

    void on_lColorButton_clicked();

    void on_lApplyButton_clicked();

    void on_llistWidget_itemClicked(QListWidgetItem *item);

    void on_wApplyButton_clicked();

    void on_mTexturButton_clicked();

    void on_cMoveButoon_clicked();

    void on_mRotateButton_2_clicked();

private:
    void init_ui();

    shared_ptr<BaseCommand> makePolModelAddCommand();

    void set_mTexture(shared_ptr<BaseTexture> &texture);

    void set_mColor(Color color);

    void set_mProps(ObjectProperties &props);

    void set_lData(Color &color, double i);

    QList<QListWidgetItem *> mSelectedItems();

    QList<QListWidgetItem *> lSelectedItems();

private:
    Ui::MainWindow *ui;
    shared_ptr<QGraphicsScene> scene;
    shared_ptr<QImage> image;
    shared_ptr<BaseRenderer> renderer;
    shared_ptr<BaseDrawer> drawer;

    SceneManager manager;

    RenderProperties render_props;

    objl::Loader loader;
};

#endif // MAINWINDOW_H
