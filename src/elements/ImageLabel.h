//
// Created by Kuba Jazdzyk on 8/29/19.
//

#ifndef MICROMOUSE_IMAGELABEL_H
#define MICROMOUSE_IMAGELABEL_H


#include <QtWidgets/QLabel>
#include <src/utils/Logging.h>

class ImageLabel : public QLabel {
public:
    ImageLabel(const QString& imageUrl, int size);
    ImageLabel(const QPixmap& imagePixmap, int size);
    ImageLabel(const QImage& image, int size);

    void updatePixmap(const QString& imageUrl);
    void updatePixmap(const QPixmap& imagePixmap);
    void updatePixmap(const QImage& image);

private:
    int size;
};


#endif //MICROMOUSE_IMAGELABEL_H
