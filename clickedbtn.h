#ifndef CLICKEDBTN_H
#define CLICKEDBTN_H
#include <QPushButton>
#include <QVariant>

class ClickedBtn : public QPushButton
{
    Q_OBJECT
public:
    ClickedBtn(QWidget *parent = nullptr);
    ~ClickedBtn();
    void SetState(QString normal = "", QString hover = "", QString press = "");
protected:
    virtual void enterEvent(QEvent *event) override;
    virtual void leaveEvent(QEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
private:
    QString normal_;
    QString hover_;
    QString press_;
};

#endif // CLICKEDBTN_H
