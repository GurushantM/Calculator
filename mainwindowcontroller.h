#ifndef MAINWINDOWCONTROLLER_H
#define MAINWINDOWCONTROLLER_H

#include <QMainWindow>
#include <QJSEngine>
#include "view.h"

class MainWindowController : public QMainWindow
{
    Q_OBJECT

public:
    MainWindowController(QWidget *parent = nullptr);
    ~MainWindowController();

private slots:
    void calculateResult();

private:
    void updateError(QJSValue::ErrorType errorType);

private:
    View *mView;
    QJSEngine* mJSEngine;
    QString mCurrentExpression;
};
#endif // MAINWINDOWCONTROLLER_H
