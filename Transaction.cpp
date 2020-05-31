#include "Transaction.h"

std::ostream &operator<<(std::ostream& os, const Transaction& transaction) {
    struct tm *timeinfo;
    timeinfo = localtime (&(transaction._date));
    os << transaction._amount << "\t-\t" <<  timeinfo->tm_hour << ":" << timeinfo->tm_min << ":" <<  timeinfo->tm_sec << "-" << timeinfo->tm_mday << "/" << (timeinfo->tm_mon)+1 << "/" <<  ((timeinfo->tm_year)+1900) << std::endl;
    return os;
}
    
Transaction::Transaction()
{
    _amount=-1; _date=-1;
}

Transaction::Transaction(double amount, time_t date)
{
    _amount=amount; _date=date;
}

Transaction::Transaction(const Transaction& rhs)
{
   _amount=rhs._amount; _date=rhs._date;
}

bool Transaction::operator<(const Transaction& rhs) const
{
    return (this->_date < rhs._date) ;
}

bool Transaction::operator>(const Transaction& rhs) const
{
    return (this->_date > rhs._date) ;
}

bool Transaction::operator <(const time_t date) const
{
    if (date>0) return (this->_date > date) ;
    else return (this->_date < date) ;

}
bool Transaction::operator>(const time_t date) const
{
    if (date>0) return (this->_date < date) ;
    else return (this->_date > date) ;

}
double Transaction::operator+(const Transaction& rhs)
{
    return (double) (this->_amount + rhs._amount) ;

}
double Transaction::operator+(const double add)
{
    return (double) (this->_amount + add) ;

}
Transaction& Transaction::operator=(const Transaction& rhs)
{
    this->_amount=rhs._amount; this->_date=rhs._date;
    return *this;
}
