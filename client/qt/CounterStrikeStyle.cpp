#include "CounterStrikeStyle.h"
#include <QFontDatabase>
#include <QDir>

#define PATH_TO_COUNTER_STRIKE_FONT "/var/cs2d/resources/fonts/counter_strike.ttf"
CounterStrikeStyle::CounterStrikeStyle() {
    font_path = PATH_TO_COUNTER_STRIKE_FONT;
}

void CounterStrikeStyle::setCounterStrikeFont(QDialog* qDialog, int size) {
    QFontDatabase::addApplicationFont(font_path);
    QFont CounterStrikeFont("Counter-Strike", size, QFont::Normal);
    qDialog->setFont(CounterStrikeFont);
}


void CounterStrikeStyle::setCounterStrikeFont(QWidget* qWidget, int size) {
    QFontDatabase::addApplicationFont(font_path);
    QFont CounterStrikeFont("Counter-Strike", size, QFont::Normal);
    qWidget->setFont(CounterStrikeFont);
}
