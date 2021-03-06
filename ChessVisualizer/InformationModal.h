#ifndef INFORMATIONMODAL_H
#define INFORMATIONMODAL_H

#include <QDialog>
#include <QPushButton>
#include <string>
#include <QWidget>
#include <QLabel>

class InformationModal : public QDialog
{
public:
    InformationModal(QWidget* parent);

    void setMessageText(const std::string& text);
    void setModalTitle(const std::string& title);
private:
    QPushButton okButton;
    QLabel infoIconLabel;
    QLabel infoMessage;
};

#endif // INFORMATIONMODAL_H
