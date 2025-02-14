#ifndef ACADEMICDIALOG_H
#define ACADEMICDIALOG_H

#include <QDialog>
#include "academicitem.h"

// Forward declaration of UI namespace
namespace Ui {
class AcademicDialog;
}

// Dialog for adding/editing academic items
class AcademicDialog : public QDialog
{
    Q_OBJECT

public:
    // Constructor takes the type of academic item to create
    // and optional parent widget
    explicit AcademicDialog(AcademicItem::Type type, QWidget *parent = nullptr);
    ~AcademicDialog();

    // Returns the academic item created from user input
    AcademicItem getAcademicItem() const;

private slots:
    // Validates user input before accepting the dialog
    void validateInput();

private:
    Ui::AcademicDialog *ui;        // Pointer to UI form
    AcademicItem::Type m_type;     // Type of item being created
};

#endif // ACADEMICDIALOG_H 