#include "calendar.h"

Calendar::Calendar()
{

}

DateRange Calendar::Last24Hour()
{
    auto now = QDateTime::currentDateTime();
    auto earlier = now.addDays(-1);
    now = now.addSecs(1);
    return std::make_pair(earlier,now);
}

DateRange Calendar::Last3Days()
{
    auto now = QDateTime::currentDateTime();
    auto earlier = now.addDays(-3);
    now = now.addSecs(1);
    return std::make_pair(earlier,now);
}

DateRange Calendar::LastWeek()
{
    auto now = QDateTime::currentDateTime();
    auto earlier = now.addDays(-7);
    now = now.addSecs(1);
    return std::make_pair(earlier,now);
}

DateRange Calendar::LastMonth()
{
    auto now = QDateTime::currentDateTime();
    auto earlier = now.addMonths(-1);
    now = now.addSecs(1);
    return std::make_pair(earlier,now);
}

DateRange Calendar::LastYear()
{
    auto now = QDateTime::currentDateTime();
    auto earlier = now.addYears(-1);
    now = now.addSecs(1);
    return std::make_pair(earlier,now);
}
