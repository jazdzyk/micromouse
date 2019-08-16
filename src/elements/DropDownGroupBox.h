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

class DropDownGroupBox : public QGroupBox {
public:
    using ActionCallback = std::optional<std::function<void(int, int)>>;
    using Texts = const std::vector<QString>;

    explicit DropDownGroupBox(const QString &title, Texts &labels, Texts &dropDownOptions,
            ActionCallback onDropDownChanged);
    ~DropDownGroupBox();

    void setDropDownOption(int id, int option);
    void setDropDownVisible(int id, bool visible);

private:
    using DropDown = std::pair<int, QComboBox*>;

    std::vector<DropDown> dropDowns;
    std::vector<QHBoxLayout*> horizontalLayouts;
    QVBoxLayout *boxLayout;

    void setUpUi(Texts &labels, Texts &dropDownOptions);
    void setDropDownAction(ActionCallback onDropDownChanged);
    void addDropDowns(Texts &labels, Texts &dropDownOptions, int initialId);
    static QComboBox* prepareDropDown(Texts &dropDownOptions);
};


#endif //MICROMOUSE_DROPDOWNGROUPBOX_H
