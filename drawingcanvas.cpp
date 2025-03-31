#include "drawingcanvas.h"

DrawingCanvas::DrawingCanvas(QWidget *parent) : QWidget(parent), drawing(false), eraserMode(false) {
    // Set up canvas size and color
    canvasImage = QImage(800, 600, QImage::Format_ARGB32);
    canvasImage.fill(Qt::white);

    // Default pen settings
    pen.setColor(Qt::black);
    pen.setWidth(3);
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);
}

void DrawingCanvas::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.drawImage(0, 0, canvasImage);
}

void DrawingCanvas::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        drawing = true;
        lastPoint = event->pos();
    }
}

void DrawingCanvas::mouseMoveEvent(QMouseEvent *event) {
    if (drawing && (event->buttons() & Qt::LeftButton)) {
        QPainter painter(&canvasImage);

        if (eraserMode) {
            QPen eraser(Qt::white, pen.width()); // White pen to erase
            painter.setPen(eraser);
        } else {
            painter.setPen(pen);
        }

        painter.drawLine(lastPoint, event->pos());
        lastPoint = event->pos();
        update();
    }
}

void DrawingCanvas::clearCanvas() {
    canvasImage.fill(Qt::white);
    update();
}

void DrawingCanvas::setPenColor(const QColor &color) {
    if (!eraserMode) {
        pen.setColor(color);
    }
}

void DrawingCanvas::setPenSize(int size) {
    pen.setWidth(size);
}

QColor DrawingCanvas::getPenColor() const {
    return pen.color();
}

void DrawingCanvas::setEraserMode(bool enabled) {
    eraserMode = enabled;
}

bool DrawingCanvas::isEraserMode() const {
    return eraserMode;
}

void DrawingCanvas::saveImage(const QString &fileName) {
    canvasImage.save(fileName);
}

// #include "drawingcanvas.h"
// #include <QDebug>
// #include <tesseract/baseapi.h>
// #include <leptonica/allheaders.h>
// #include <opencv2/opencv.hpp>

// using namespace cv;

// DrawingCanvas::DrawingCanvas(QWidget *parent) : QWidget(parent), drawing(false), eraserMode(false) {
//     // Set up canvas size and color
//     canvasImage = QImage(800, 600, QImage::Format_ARGB32);
//     canvasImage.fill(Qt::white);

//     // Default pen settings
//     pen.setColor(Qt::black);
//     pen.setWidth(3);
//     pen.setCapStyle(Qt::RoundCap);
//     pen.setJoinStyle(Qt::RoundJoin);
// }

// void DrawingCanvas::paintEvent(QPaintEvent *event) {
//     QPainter painter(this);
//     painter.drawImage(0, 0, canvasImage);
// }

// void DrawingCanvas::mousePressEvent(QMouseEvent *event) {
//     if (event->button() == Qt::LeftButton) {
//         drawing = true;
//         lastPoint = event->pos();
//     }
// }

// void DrawingCanvas::mouseMoveEvent(QMouseEvent *event) {
//     if (drawing && (event->buttons() & Qt::LeftButton)) {
//         QPainter painter(&canvasImage);

//         if (eraserMode) {
//             QPen eraser(Qt::white, pen.width()); // White pen to erase
//             painter.setPen(eraser);
//         } else {
//             painter.setPen(pen);
//         }

//         painter.drawLine(lastPoint, event->pos());
//         lastPoint = event->pos();
//         update();
//     }
// }

// void DrawingCanvas::mouseReleaseEvent(QMouseEvent *event) {
//     if (drawing) {
//         drawing = false;
//         recognizeHandwriting();  // Trigger handwriting recognition after drawing
//         detectShapes();  // Trigger shape detection
//     }
// }

// void DrawingCanvas::clearCanvas() {
//     canvasImage.fill(Qt::white);
//     update();
// }

// void DrawingCanvas::setPenColor(const QColor &color) {
//     if (!eraserMode) {
//         pen.setColor(color);
//     }
// }

// void DrawingCanvas::setPenSize(int size) {
//     pen.setWidth(size);
// }

// QColor DrawingCanvas::getPenColor() const {
//     return pen.color();
// }

// void DrawingCanvas::setEraserMode(bool enabled) {
//     eraserMode = enabled;
// }

// bool DrawingCanvas::isEraserMode() const {
//     return eraserMode;
// }

// void DrawingCanvas::saveImage(const QString &fileName) {
//     canvasImage.save(fileName);
// }

// // AI Feature 1: Handwriting Recognition
// void DrawingCanvas::recognizeHandwriting() {
//     // Convert QImage to OpenCV Mat
//     Mat img = QImageToMat(canvasImage);
//     cvtColor(img, img, COLOR_BGR2GRAY);
//     threshold(img, img, 0, 255, THRESH_BINARY | THRESH_OTSU);

//     // Initialize Tesseract OCR
//     tesseract::TessBaseAPI ocr;
//     ocr.Init(nullptr, "eng", tesseract::OEM_LSTM_ONLY);
//     ocr.SetImage(img.data, img.cols, img.rows, 1, img.step);

//     // Get recognized text
//     std::string text = ocr.GetUTF8Text();
//     ocr.End();

//     qDebug() << "Recognized Text: " << QString::fromStdString(text);
// }

// // AI Feature 2: Shape Detection
// void DrawingCanvas::detectShapes() {
//     Mat img = QImageToMat(canvasImage);
//     cvtColor(img, img, COLOR_BGR2GRAY);
//     Canny(img, img, 50, 150);
//     std::vector<std::vector<Point>> contours;
//     findContours(img, contours, RETR_TREE, CHAIN_APPROX_SIMPLE);

//     for (const auto &contour : contours) {
//         double epsilon = 0.02 * arcLength(contour, true);
//         std::vector<Point> approx;
//         approxPolyDP(contour, approx, epsilon, true);

//         if (approx.size() == 3) {
//             qDebug() << "Triangle detected";
//         } else if (approx.size() == 4) {
//             qDebug() << "Rectangle detected";
//         } else {
//             qDebug() << "Circle detected";
//         }
//     }
// }

// // Convert QImage to OpenCV Mat
// Mat DrawingCanvas::QImageToMat(const QImage &image) {
//     Mat mat(image.height(), image.width(), CV_8UC4, (void *)image.bits(), image.bytesPerLine());
//     return mat.clone();
// }

