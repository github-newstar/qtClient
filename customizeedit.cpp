#include "customizeedit.h"

CustomizeEdit::CustomizeEdit(QWidget *parent) : QLineEdit(parent), maxLen_(0) {
    connect(this, &QLineEdit::textChanged, this,
            &CustomizeEdit::limitTestLength);
}
void CustomizeEdit::SetMaxLength(int maxLen) { maxLen_ = maxLen; }
