#include "academicdialog.h"
#include "ui_academicdialog.h"
#include <QMessageBox>

// Constructor
AcademicDialog::AcademicDialog(AcademicItem::Type type, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AcademicDialog)
    , m_type(type)
{
    // Set up the UI form
    ui->setupUi(this);

    // Configure dialog based on type (lecture or deadline)
    if (type == AcademicItem::Lecture) {
        setWindowTitle("Add Lecture");
        // Show duration fields for lectures
        ui->durationLabel->show();
        ui->durationSpinBox->show();
    } else {
        setWindowTitle("Add Deadline");
        // Hide duration fields for deadlines
        ui->durationLabel->hide();
        ui->durationSpinBox->hide();
    }

    // Initialize date/time field with current date and time
    ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());

    // Connect the OK button click to input validation
    connect(ui->buttonBox, &QDialogButtonBox::accepted,
            this, &AcademicDialog::validateInput);
}

// Destructor - clean up UI
AcademicDialog::~AcademicDialog()
{
    delete ui;
}

// Validate user input before accepting the dialog
void AcademicDialog::validateInput()
{
    // Make sure title is not empty
    if (ui->titleEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter a title");
        return;
    }

    // For lectures, ensure duration is set
    if (m_type == AcademicItem::Lecture && ui->durationSpinBox->value() == 0) {
        QMessageBox::warning(this, "Error", "Please enter lecture duration");
        return;
    }

    // If all validation passes, accept the dialog
    accept();
}

// Create and return an AcademicItem from the user input
AcademicItem AcademicDialog::getAcademicItem() const
{
    return AcademicItem(
        m_type,                         // Type (lecture/deadline)
        ui->titleEdit->text(),          // Title
        ui->descriptionEdit->toPlainText(), // Description
        ui->dateTimeEdit->dateTime(),   // Date/time
        ui->durationSpinBox->value()    // Duration (only used for lectures)
    );
} 