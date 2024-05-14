#ifndef IMAGEVIEWERDIALOG_H
#define IMAGEVIEWERDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QHBoxLayout>
#include <QGuiApplication>
#include <QScreen>

class ImageViewerDialog : public QDialog {
public:
    ImageViewerDialog(QWidget *parent = nullptr) : QDialog(parent) {
        setWindowTitle("Image Viewer");
        setFixedSize(500, 400);

        // 设置对话框的布局为水平布局
        QHBoxLayout *layout = new QHBoxLayout(this);
        layout->setContentsMargins(0, 0, 0, 0);

        // 创建标签用于显示图片
        imageLabel = new QLabel(this);
        imageLabel->setAlignment(Qt::AlignCenter);
        imageLabel->setScaledContents(true); // 设置图片自适应大小
        layout->addWidget(imageLabel);
    }

    // 设置要显示的图片
    void setImage(const QPixmap &pixmap) {
        imageLabel->setPixmap(pixmap);
        adjustSize();
        // 让对话框在屏幕中央显示
        move(QGuiApplication::primaryScreen()->geometry().center() - rect().center());
    }

private:
    QLabel *imageLabel;
};
#endif // IMAGEVIEWERDIALOG_H
