#include "chatitembase.h"
#include <QGridLayout>


ChatItemBase::ChatItemBase(ChatRole role, QWidget *parent) : QWidget(parent), role_(role)
{
    pNameLable_ = new QLabel;
    pNameLable_->setObjectName("chat_user_name_");
    QFont font("Microsoft YaHei");
    font.setPointSize(9);
    pNameLable_->setFont(font);
    pNameLable_->setFixedHeight(20);

    pIconLable_ = new QLabel;
    pIconLable_->setScaledContents(true);
    pIconLable_->setFixedSize(42, 42);

    pBubble_ = new QWidget();
    QGridLayout *pGLayout = new QGridLayout;
    pGLayout->setVerticalSpacing(3);
    pGLayout->setHorizontalSpacing(3);
    pGLayout->setMargin(3);
    
    QSpacerItem*pSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    if(role_== ChatRole::Self)
    {
        pNameLable_->setContentsMargins(0,0,8,0);
        pNameLable_->setAlignment(Qt::AlignRight);
        pGLayout->addWidget(pNameLable_, 0,1, 1,1);
        pGLayout->addWidget(pIconLable_, 0, 2, 2,1, Qt::AlignTop);
        pGLayout->addItem(pSpacer, 1, 0, 1, 1);
        pGLayout->addWidget(pBubble_, 1,1, 1,1);
        pGLayout->setColumnStretch(0, 2);
        pGLayout->setColumnStretch(1, 3);
    }else{
        pNameLable_->setContentsMargins(8,0,0,0);
        pNameLable_->setAlignment(Qt::AlignLeft);
        pGLayout->addWidget(pIconLable_, 0, 0, 2,1, Qt::AlignTop);
        pGLayout->addWidget(pNameLable_, 0,1, 1,1);
        pGLayout->addWidget(pBubble_, 1,1, 1,1);
        pGLayout->addItem(pSpacer, 2, 2, 1, 1);
        pGLayout->setColumnStretch(1, 3);
        pGLayout->setColumnStretch(2, 2);
    }
    this->setLayout(pGLayout);
}

void ChatItemBase::setUserName(const QString &name) {
    pNameLable_->setText(name);
}

void ChatItemBase::setUserIcon(const QPixmap &icon) {
    pIconLable_->setPixmap(icon);
}

void ChatItemBase::setWidget(QWidget *w) {
    QGridLayout *pGLayout = (qobject_cast<QGridLayout *>)(this->layout());
    pGLayout->replaceWidget(pBubble_, w);
    delete pBubble_;
    pBubble_= w;
}
