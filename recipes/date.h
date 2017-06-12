#pragma once

#include <string>

namespace mtl
{

class noncopyable
{
protected:
    noncopyable() = default;
    ~noncopyable() = default;
    noncopyable(const noncopyable&) = delete;
    noncopyable& operator=(const noncopyable&) = delete;
};

}


namespace mtl
{

class Date// : public muduo::copyable | public boost::less_than_comparable<Date>, public boost::equality_comparable<Date>
{
public:
    struct YearMonthDay
    {
        int year;
        int month;
        int day;
    };
    
    static const int kDaysPerWeek = 7;
    static const int kJulianDayOf1970_01_01;
    
    Date()
    :julianDayNumber_(0) {}  //no content
    
    Date(int year, int month, int day);
    
    explicit Date(int julianDayNum)
    :julianDayNumber_(julianDayNum) {}  //no content
    
    explicit Date(const struct tm&);
    
    void swap(Date& other)
    {
        std::swap(julianDayNumber_, that.julianDayNumber_);
    }
    
    bool valid() const
    {
        return julianDayNumber_ > 0;
    }
    
    std::string toIsoString() const;
    
    struct YearMonthDay yearMonthDay() const;
    
    int year() const
    {
        return yearMonthDay().year;
    }
    
    int month() const
    {
        return yearMonthDay().month;
    }
    
    int day() const
    {
        return yearMonthDay().day;
    }
    
    //[0 - 6]
    int weekDay() const
    {
        return (julianDayNumber_ + 1) % kDaysPerWeek;
    }
    
    int julianDayNumber() const
    {
        return julianDayNumber_;
    }
    
private:
    int julianDayNumber_;
};

inline bool operator<(Date x, Date y)
{
    return x.julianDayNumber() < y.julianDayNumber();
}

inline bool operator==(Date x, Date y)
{
    return x.julianDayNumber() == y.julianDayNumber();
}

}
