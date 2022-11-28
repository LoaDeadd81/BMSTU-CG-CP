#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QPainter>
#include <QGraphicsScene>
#include <memory>
#include <list>

#include "SceneManager.h"
#include "Commands.h"

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

    void on_moveButoon_clicked();

    void on_rotateButton_clicked();

    void on_ScaleButton_clicked();

    void on_ColorButton_clicked();

    void on_TexturButton_clicked();

private:
    int tabIndex();

    int modelIndex();

    int lightIndex();

    Vec3d moveData();

    Vec3d rotateData();

    Vec3d scaleData();

private:
    Ui::MainWindow *ui;
    shared_ptr<QGraphicsScene> scene;
    shared_ptr<QPixmap> pixmap;

    SceneManager manager;
};

#endif // MAINWINDOW_H
