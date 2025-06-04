#pragma once
#include <QWidget>
#include <QMap>
#include <QString>
#include <QPainter>
#include <QPaintEvent>
#include <algorithm>

class BarChartWidget : public QWidget {
    Q_OBJECT

public:
    explicit BarChartWidget(const QMap<QString, int>& data) : chartData(data) {
        setMinimumSize(1000, 600);
    }

protected:
    void paintEvent(QPaintEvent* event) override {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);
        int margin = 40;
        int barWidth = (width() - 2 * margin) / chartData.size();
        int maxVal = *std::max_element(chartData.begin(), chartData.end());
        int i = 0;
        for (auto it = chartData.begin(); it != chartData.end(); ++it, ++i) {
            int barHeight = static_cast<int>((double(it.value()) / maxVal) * (height() - 2 * margin));
            QRect barRect(margin + i * barWidth, height() - margin - barHeight, barWidth - 10, barHeight);
            painter.setBrush(QColor(100, 150, 255));
            painter.drawRect(barRect);
            QString countText = QString::number(it.value());
            painter.drawText(barRect.center().x() - 10, barRect.top() - 5, countText);
            painter.drawText(barRect.left(), height() - 10, it.key());
        }
    }

private:
    QMap<QString, int> chartData;
};