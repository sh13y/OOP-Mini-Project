#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include "transaction.h"
#include <QtCharts>
#include "academicitem.h"
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addIncomeButton_clicked();
    void on_addExpenseButton_clicked();
    void on_generateReportButton_clicked();
    void on_setBudgetButton_clicked();
    void on_addLectureButton_clicked();
    void on_addDeadlineButton_clicked();
    void checkDeadlines();
    void setupAcademicTable();
    void addAcademicItem(const AcademicItem &item);
    void onRemoveTransactionClicked();
    void onRemoveAcademicItemClicked();

private:
    void setupTransactionsTable();
    void addTransaction(const Transaction &transaction);
    void updateChart();
    void saveData();
    void loadData();
    void loadDummyData();

    Ui::MainWindow *ui;
    QVector<Transaction> transactions;
    QMap<QString, double> budgets;
    QChartView *chartView;
    QVector<AcademicItem> academicItems;
    QTimer *deadlineTimer;
};

#endif // MAINWINDOW_H 