#ifndef CUSTOMIZEEDIT_H
#define CUSTOMIZEEDIT_H
#include <QLineEdit>
#include <QDebug>


class CustomizeEdit : public QLineEdit
{
    Q_OBJECT
public:
    CustomizeEdit(QWidget *parent = 0);
    void SetMaxLength(int maxLen);

protected:
    void focusOutEvent(QFocusEvent *event) override{
        QLineEdit::focusOutEvent(event);
        emit sig_foucus_out();
    }
private:
    void limitTestLength(QString text){
        if(maxLen_ <= 0){
            return ;
        }
        
        QByteArray byteArray = text.toUtf8();
        if(byteArray.length() > maxLen_){
            byteArray = byteArray.left(maxLen_);
            this->setText(QString::fromUtf8(byteArray));
        }

    }
    
    int maxLen_;
signals:
    void sig_foucus_out();
};


#endif // CUSTOMIZEEDIT_H
