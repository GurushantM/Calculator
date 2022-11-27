#ifndef VIEW_H
#define VIEW_H

#include <QWidget>

QT_BEGIN_NAMESPACE

namespace Ui {
    class View;
} // namespace Ui

QT_END_NAMESPACE

class View : public QWidget
{
    Q_OBJECT
public:
    explicit View(QWidget *parent = nullptr);
    ~View();

    void updateDisplay(const QString &text);

private slots:
    void buttonPressed();

protected slots:
    void keyPressEvent(QKeyEvent *event);

signals:
    void valuePressed(const QString &val);
    void clearPressed();
    void resultNeeded();

private:
    Ui::View *mView;
};

#endif // VIEW_H
