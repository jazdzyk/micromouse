//
// Created by Kuba Jazdzyk on 8/29/19.
//

#ifndef MICROMOUSE_IMAGELABEL_H
#define MICROMOUSE_IMAGELABEL_H


#include <QtWidgets/QLabel>
#include <src/utils/Logging.h>

/**
 * The ImageLabel class inherits from QLabel and extends its functionalities.
 * Its purpose is to display image.
 */
class ImageLabel : public QLabel {
public:
    /**
     * ImageLabel class constructor.
     *
     * @param imageUrl a url to the location of the image to be displayed
     * @param size a size of the image square
     */
    ImageLabel(const QString &imageUrl, int size);

    /**
     * ImageLabel class constructor.
     *
     * @param imagePixmap a pixmap of the image to be displayed
     * @param size a size of the image square
     */
    ImageLabel(const QPixmap &imagePixmap, int size);

    /**
     * ImageLabel class constructor.
     *
     * @param image an image to be displayed
     * @param size a size of the image square
     */
    ImageLabel(const QImage &image, int size);

    /**
     * A private method which enables updating an image being displayed.
     *
     * @param imageUrl a url to the location of the image to be displayed
     */
    void updatePixmap(const QString &imageUrl);

    /**
     * A private method which enables updating an image being displayed.
     *
     * @param imagePixmap a pixmap of the image to be displayed
     */
    void updatePixmap(const QPixmap &imagePixmap);

    /**
     * A private method which enables updating an image being displayed.
     *
     * @param image an image to be displayed
     */
    void updatePixmap(const QImage &image);

private:
    int size;
};


#endif //MICROMOUSE_IMAGELABEL_H
