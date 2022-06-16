#ifndef ANNCELISTWINDOW_H
#define ANNCELISTWINDOW_H

#include <QWidget>
#include <QListWidget>
#include <vector>
#include "anncedetailwindow.h"


namespace Ui {
class anncelistwindow;
}

class anncelistwindow : public QWidget
{
    Q_OBJECT

public:
    explicit anncelistwindow(int anncetype, QWidget *parent = nullptr);
    bool getAnnceFiles(const char *path);
    QString parsingAnnceFile(QString annceFilePath);
    ~anncelistwindow();

public slots:
    void back_clicked();
    void ItemClicked(QListWidgetItem *item);

private:
    int anncetype;

    std::vector<QString> annceList;
    Ui::anncelistwindow *ui;
    anncedetailwindow *annceDetailWindow;
};

#endif // ANNCELISTWINDOW_H
