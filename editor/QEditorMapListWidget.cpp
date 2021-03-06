#include "QEditorMapListWidget.h"

QEditorMapListWidget::QEditorMapListWidget(QWidget *parent)
    : QListWidget(parent) {
    this->doAutoScroll();
    this->scrollBarWidgets(Qt::AlignCenter);
    this->setMapItems();
}

void QEditorMapListWidget::setMapItems() {
    this->update();
}

void QEditorMapListWidget::setMapItem(QString &mapName) {
    QListWidgetItem* item = new QListWidgetItem();
    item->setText(mapName);
    this->addItem(item);
}


void QEditorMapListWidget::update() {
    this->clear();
    QDir directory(PATH_TO_MAPS);
    QStringList mapsList  = directory.entryList();
    for (QString& mapName : mapsList) {
        if(mapName != "." && mapName != "..") {
            mapName.chop(4);
            this->addItem(mapName);
        }
    }
}

