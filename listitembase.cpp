#include "listitembase.h"

ListItemBase::ListItemBase(QWidget *parent) : QWidget(parent)
{
}
void ListItemBase::SetItemType(ListItemType itemType)
{
    itemType_ = itemType;
}
ListItemType ListItemBase::GetItemType()
{
    return itemType_;
}