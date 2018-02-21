#ifndef CALENDAR_H
#define CALENDAR_H
#include <QDateTime>
typedef std::pair<QDateTime,QDateTime> DateRange;
class Calendar
{
public:
    Calendar();
    static QDateTime GetTodayDate();
    static DateRange Last24Hour();
    static DateRange Last3Days();
    static DateRange LastWeek();
    static DateRange LastMonth();
    static DateRange LastYear();
};

#endif // CALENDAR_H
