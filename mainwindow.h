#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "drawingcanvas.h"  // Include the custom canvas

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void clearCanvas();
    void changePenColor();
    void changePenSize(int size);
    void saveDrawing();
    void toggleEraser();  // Add this function declaration

private:
    Ui::MainWindow *ui;
    DrawingCanvas *canvas;  // Custom drawing widget
};

#endif // MAINWINDOW_H



// #ifndef MAINWINDOW_H
// #define MAINWINDOW_H

// #include <QMainWindow>
// #include "drawingcanvas.h"  // Include the custom canvas

// QT_BEGIN_NAMESPACE
// namespace Ui {
// class MainWindow;
// }
// QT_END_NAMESPACE

// class MainWindow : public QMainWindow
// {
//     Q_OBJECT

// public:
//     explicit MainWindow(QWidget *parent = nullptr);
//     ~MainWindow();

// private slots:
//     void on_clearButton_clicked();

//     void on_colorButton_clicked();

//     void on_saveButton_clicked();

//     void on_sizeSpinBox_valueChanged(int arg1);
//     void clearCanvas();
//     void changePenColor();
//     void changePenSize(int size);
//     void saveDrawing();

// private:
//     Ui::MainWindow *ui;
//     DrawingCanvas *canvas;  // Custom drawing widget
// };

// #endif // MAINWINDOW_H
