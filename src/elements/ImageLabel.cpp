//
// Created by Kuba Jazdzyk on 8/29/19.
//

#include "ImageLabel.h"

ImageLabel::ImageLabel(const QString &imageUrl, int size) : ImageLabel(QPixmap(imageUrl), size) {
    Log::print("ImageLabel::ImageLabel(&imageUrl, size: " + std::to_string(size) + ")");
}

ImageLabel::ImageLabel(const QPixmap &imagePixmap, int size) : QLabel(), size(size) {
    Log::print("ImageLabel::ImageLabel(&imagePixmap, size: " + std::to_string(size) + ")");
    updatePixmap(imagePixmap);
}

ImageLabel::ImageLabel(const QImage &image, int size) : ImageLabel(QPixmap::fromImage(image), size) {
    Log::print("ImageLabel::ImageLabel(&image, size: " + std::to_string(size) + ")");
}

void ImageLabel::updatePixmap(const QString &imageUrl) {
    Log::print("ImageLabel::updatePixmap(&imageUrl)");
    updatePixmap(QPixmap(imageUrl));
}

void ImageLabel::updatePixmap(const QPixmap &imagePixmap) {
    Log::print("ImageLabel::updatePixmap(&imagePixmap)");
    setPixmap(imagePixmap.scaled(this->size, this->size, Qt::KeepAspectRatio));
}

void ImageLabel::updatePixmap(const QImage &image) {
    Log::print("ImageLabel::updatePixmap(&image)");
    updatePixmap(QPixmap::fromImage(image));
}