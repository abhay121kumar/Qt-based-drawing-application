#ifndef DRAWINGCANVAS_H
#define DRAWINGCANVAS_H

#include <QWidget>
#include <QPainter>
#include <QPen>
#include <QMouseEvent>
#include <QImage>

class DrawingCanvas : public QWidget {
    Q_OBJECT

public:
    explicit DrawingCanvas(QWidget *parent = nullptr);
    void clearCanvas();
    void setPenColor(const QColor &color);
    void setPenSize(int size);
    void setEraserMode(bool enabled);
    bool isEraserMode() const;
    QColor getPenColor() const;
    void saveImage(const QString &fileName);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    QImage canvasImage;
    QPen pen;
    QPoint lastPoint;
    bool drawing;
    bool eraserMode; // Added for eraser mode
};

#endif // DRAWINGCANVAS_H
