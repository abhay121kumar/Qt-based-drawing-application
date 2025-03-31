#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QColorDialog>
#include <QFileDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Create a QWidget container to hold both canvas and controls
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // Create the drawing canvas
    canvas = new DrawingCanvas(this);

    // Create UI elements (buttons and spinbox)
    QPushButton *clearButton = new QPushButton("Clear");
    QPushButton *colorButton = new QPushButton("Change Color");
    QPushButton *saveButton = new QPushButton("Save");
    QPushButton *eraserButton = new QPushButton("Eraser");
    QSpinBox *sizeSpinBox = new QSpinBox();
    sizeSpinBox->setRange(1, 20);
    sizeSpinBox->setValue(3);

    // Layouts
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    QHBoxLayout *controlsLayout = new QHBoxLayout();

    // Add controls to layout
    controlsLayout->addWidget(clearButton);
    controlsLayout->addWidget(colorButton);
    controlsLayout->addWidget(sizeSpinBox);
    controlsLayout->addWidget(saveButton);
    controlsLayout->addWidget(eraserButton);

    // Add canvas and controls to the main layout
    mainLayout->addLayout(controlsLayout);
    mainLayout->addWidget(canvas);

    // Connect UI elements to slots
    connect(clearButton, &QPushButton::clicked, this, &MainWindow::clearCanvas);
    connect(colorButton, &QPushButton::clicked, this, &MainWindow::changePenColor);
    connect(saveButton, &QPushButton::clicked, this, &MainWindow::saveDrawing);
    connect(sizeSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::changePenSize);
    connect(eraserButton, &QPushButton::clicked, this, &MainWindow::toggleEraser);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::clearCanvas() {
    canvas->clearCanvas();
    canvas->setEraserMode(false);  // Disable eraser after clearing
    canvas->setPenColor(Qt::black);  // Restore pen color
}

void MainWindow::changePenColor() {
    QColor newColor = QColorDialog::getColor(canvas->getPenColor(), this, "Select Pen Color");
    if (newColor.isValid()) {
        canvas->setPenColor(newColor);
    }
}

void MainWindow::changePenSize(int size) {
    canvas->setPenSize(size);
}

void MainWindow::saveDrawing() {
    QString fileName = QFileDialog::getSaveFileName(this, "Save Drawing", "", "PNG Files (*.png)");
    if (!fileName.isEmpty()) {
        canvas->saveImage(fileName);
    }
}

void MainWindow::toggleEraser() {
    if (canvas->isEraserMode()) {
        canvas->setEraserMode(false);
        canvas->setPenColor(Qt::black);  // Restore pen color
    } else {
        canvas->setEraserMode(true);
    }
}
