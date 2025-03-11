#include "chatview.h"
#include <QStyleOption>
#include <QPainter>
#include <QScrollBar>
#include <QTimer>
#include <QDebug>

ChatView::ChatView(QWidget *parent) : QWidget(parent),
isAppended(false) {
    QVBoxLayout *pMainLayout = new QVBoxLayout();
    this->setLayout(pMainLayout);
    pMainLayout->setMargin(0);
    
    scrollArea_ = new QScrollArea();
    scrollArea_->setObjectName("chat_area");
    pMainLayout->addWidget(scrollArea_);
    
    QWidget *w = new QWidget(this);
    w->setObjectName("chat_bg");
    w->setAutoFillBackground(true);
    
    QVBoxLayout *pVlayout_1 = new QVBoxLayout();
    pVlayout_1->addWidget(new QWidget(), 100000);
    w->setLayout(pVlayout_1);
    scrollArea_->setWidget(w);

    scrollArea_->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    QScrollBar *pVScrollBar = scrollArea_->verticalScrollBar();
    connect(pVScrollBar, &QScrollBar::rangeChanged, this, &ChatView::onVScrollBarMoved);
    
    //把垂直srollbar放上边 而不是并排
    QHBoxLayout *pHlayout_2 = new QHBoxLayout();
    pHlayout_2->addWidget(pVScrollBar, 0,Qt::AlignRight);
    pHlayout_2->setMargin(0);
    scrollArea_->setLayout(pHlayout_2);
    pVScrollBar->setHidden(true);
    
    scrollArea_->setWidgetResizable(true);
    scrollArea_->installEventFilter(this);
    initStyleSheet();
    qDebug() << "ChatView";
}

void ChatView::appendChatItem(QWidget *item) {
    QVBoxLayout *vl = qobject_cast<QVBoxLayout*>(scrollArea_->widget()->layout());
    vl->insertWidget(vl->count() - 1, item);
    isAppended = true;
}

void ChatView::prependChatItem(QWidget *item) {
}

void ChatView::insertChatItem(QWidget *before, QWidget *item) {
}

bool ChatView::eventFilter(QObject *obj, QEvent *event) {
    if(event->type() == QEvent::Enter && obj == scrollArea_ ){
        scrollArea_->verticalScrollBar()->setHidden(
            scrollArea_->verticalScrollBar()->maximum() == 0);
    }else if(event->type() == QEvent::Leave && obj == scrollArea_ ){
        scrollArea_->verticalScrollBar()->setHidden(true);
    }
    
    return QWidget::eventFilter(obj, event);
}

void ChatView::paintEvent(QPaintEvent *event) {
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void ChatView::onVScrollBarMoved(int min, int max) {
    if(isAppended){
        QScrollBar *pvScrollBar = scrollArea_->verticalScrollBar();
        pvScrollBar->setSliderPosition(pvScrollBar->maximum());
    }
    QTimer::singleShot(500, [this](){
        isAppended = false;
    });
}
void ChatView::initStyleSheet() {

}
