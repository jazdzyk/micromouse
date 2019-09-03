//
// Created by Kuba Jazdzyk on 8/16/19.
//

#ifndef MICROMOUSE_DROPDOWNGROUPBOX_H
#define MICROMOUSE_DROPDOWNGROUPBOX_H


#include <QtWidgets/QGroupBox>
#include <QtWidgets/QVBoxLayout>
#include <functional>
#include <optional>
#include <QtWidgets/QComboBox>
#include <src/utils/Logging.h>
#include <QtWidgets/QLabel>

/**
 * The DropDownGroupBox class inherits from QGroupBox and extends its functionalities.
 * It contains multiple drop-down lists with options to choose.
 */
class DropDownGroupBox : public QGroupBox {
public:
    using ActionCallback = std::optional<std::function<void(int, int)>>;
    using Texts = const std::vector<QString>;

    /**
     * DropDownGroupBox class constructor.
     *
     * @param title a title for a box
     * @param labels a vector of labels to describe drop-down lists
     * @param dropDownOptions a vector of drop-downs' options
     * @param onDropDownChanged a callback for a drop-downs' change event
     */
    explicit DropDownGroupBox(const QString &title, Texts &labels, Texts &dropDownOptions,
                              ActionCallback onDropDownChanged);

    /**
     * DropDownGroupBox class destructor.
     */
    ~DropDownGroupBox() override;

    /**
     * A public setter of drop-down option for a drop-down list identified with a given id.
     *
     * @param id an id of a drop-down list
     * @param option an option to be set
     */
    void setDropDownOption(int id, int option);

    /**
     * A public method which enables setting the visibility of a drop-down list identified with a given id.
     *
     * @param id an id of a drop-down list
     * @param visible an appropriate boolean flag
     */
    void setDropDownVisible(int id, bool visible);

private:
    using DropDown = std::pair<int, QComboBox*>;

    std::vector<DropDown> dropDowns;
    std::vector<QHBoxLayout*> horizontalLayouts;
    QVBoxLayout *boxLayout;

    /**
     * A private method which enables a configuration of box's UI.
     *
     * @param labels a vector of labels to describe drop-down lists
     * @param dropDownOptions a vector of drop-downs' options
     */
    void setUpUi(Texts &labels, Texts &dropDownOptions);

    /**
     * A private method which enables setting the callback action for drop-downs' change event.
     *
     * @param onDropDownChanged a callback for a drop-downs' change event
     */
    void setDropDownAction(ActionCallback onDropDownChanged);

    /**
     * A private method which enables adding drop-down lists to the box's layout.
     *
     * @param labels a vector of labels to describe drop-down lists
     * @param dropDownOptions a vector of drop-downs' options
     * @param initialId an id of the first drop-down list
     */
    void addDropDowns(Texts &labels, Texts &dropDownOptions, int initialId);

    /**
     * A private static factory method which prepares a drop-down list.
     *
     * @param dropDownOptions a vector of drop-downs' options
     * @return a drop-down list
     */
    static QComboBox *prepareDropDown(Texts &dropDownOptions);
};


#endif //MICROMOUSE_DROPDOWNGROUPBOX_H
