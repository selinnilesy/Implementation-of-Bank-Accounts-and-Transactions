#include "Account.h"
Account:: Account(){
    _id=-1;
    _activity=nullptr;
    _monthly_activity_frequency=nullptr;
}
Account:: Account(int id, Transaction** const activity, int* monthly_activity_frequency){
    _id=id;
    int trans_count=0;
    Transaction** (month_ptr)= new Transaction* [12];
    _monthly_activity_frequency= new int [12];
       for(int i=0; i<12; i++){
           _monthly_activity_frequency[i]=monthly_activity_frequency[i];
           trans_count=_monthly_activity_frequency[i];
           if(trans_count){
               Transaction *transactions= new Transaction [trans_count];
               for(int j=0; j<trans_count; j++){ transactions[j]= activity[i][j];}
               month_ptr[i]=&(transactions[0]);}
           else month_ptr[i]=nullptr;
       }
       
      for(int i=0; i<12; i++){
          Transaction* (temp_ptr)=month_ptr[i];
          trans_count=_monthly_activity_frequency[i];
          if(trans_count>1){
           for (int i = 0; i < trans_count-1; i++){ //my_bubble_sort
               for (int j = 0; j < trans_count-i-1; j++){
                   if (temp_ptr[j] > temp_ptr[j+1]){
                       Transaction temp = temp_ptr[j];
                       temp_ptr[j] = temp_ptr[j+1];
                       temp_ptr[j+1] = temp;}
                   }
           }}
       }
       _activity=month_ptr;
}
    
Account::~Account() {
if(_activity){
    for(int i=0; i<12; i++){
        if(_activity[i]){
            delete[] _activity[i];
            _activity[i]=nullptr;}
    }
    delete[] _activity;
    _activity=nullptr;
}
if(_monthly_activity_frequency ){
    delete[] _monthly_activity_frequency;
    _monthly_activity_frequency=nullptr;
}
    _id=-1;
}

Account::Account(const Account& rhs){
       _id=rhs._id;
       _activity=new Transaction* [12];
       _monthly_activity_frequency= new int [12];
       for(int i=0; i<12; i++){
           _monthly_activity_frequency[i]=rhs._monthly_activity_frequency[i];
           int trans_count=_monthly_activity_frequency[i];
           if(trans_count){
               Transaction *transactions= new Transaction [trans_count];
               for(int j=0; j<trans_count; j++){ transactions[j]= rhs._activity[i][j];}
               _activity[i]=&(transactions[0]);}
           else _activity[i]=nullptr;
       }
}
Account::Account(const Account& rhs , time_t start_date , time_t end_date) {
       Transaction time1 (1,start_date);
       Transaction time2 (2,end_date);
       _id=rhs._id;
       _activity=new Transaction* [12];
       _monthly_activity_frequency= new int [12];
       for(int i=0; i<12; i++) _monthly_activity_frequency[i]=0;
       for(int i=0; i<12; i++){
           if(rhs._monthly_activity_frequency[i]){
                for(int j=0; j<rhs._monthly_activity_frequency[i];j++){
                  if(time1 < rhs._activity[i][j] && rhs._activity[i][j] < time2)
                      (_monthly_activity_frequency[i])++;
                }
           }
       }
       for(int i=0; i<12; i++){
           int trans_count=_monthly_activity_frequency[i];
           if(trans_count){
               Transaction *transactions= new Transaction [trans_count];
               int index=0,massive_count=rhs._monthly_activity_frequency[i];
               for(int j=0; j<massive_count;j++){
                   if(time1 < rhs._activity[i][j] && rhs._activity[i][j] < time2) transactions[index++]=rhs._activity[i][j];
               }
               _activity[i]=&(transactions[0]);
           }
           else _activity[i]=nullptr;
       }
}

Account::Account(Account&& rhs){
    _id=rhs._id;
    _monthly_activity_frequency=rhs._monthly_activity_frequency;
    _activity=rhs._activity;
    rhs._id=-1;
    rhs._activity=nullptr;
    rhs._monthly_activity_frequency=nullptr;
}

Account& Account::operator=(Account&& rhs){
if(this!=&rhs)
{   if(this->_activity){
    for(int i=0; i<12; i++){  //destruct current object
        if(_activity[i]){
            delete[] _activity[i];
            _activity[i]=nullptr;}
    }
    delete[] _activity;
    _activity=nullptr;
    if(this->_monthly_activity_frequency){delete[] _monthly_activity_frequency;
    _monthly_activity_frequency=nullptr;}
    }
    _id=rhs._id;
    _monthly_activity_frequency=rhs._monthly_activity_frequency;
    _activity=rhs._activity;
    rhs._activity=nullptr;
    rhs._monthly_activity_frequency=nullptr;
}
    return *this;
}

Account& Account::operator=(const Account& rhs){
if(this!=&rhs)
{
    if(this->_activity){
    for(int i=0; i<12; i++){  //destruct current object
        if(_activity[i]){
            delete[] _activity[i];
            _activity[i]=nullptr;}
    }
    delete[] _activity;
    _activity=nullptr;
    if(this->_monthly_activity_frequency){delete[] _monthly_activity_frequency;
    _monthly_activity_frequency=nullptr;}
    }
    _id=rhs._id; //constructor starts for deep copying rhs
          _activity=new Transaction* [12];
          _monthly_activity_frequency= new int [12];
          for(int i=0; i<12; i++){
              _monthly_activity_frequency[i]=rhs._monthly_activity_frequency[i];
              int trans_count=_monthly_activity_frequency[i];
              if(trans_count){
                  Transaction *transactions= new Transaction [trans_count];
                  for(int j=0; j<trans_count; j++){ transactions[j]= rhs._activity[i][j];}
                  _activity[i]=&(transactions[0]);}
              else _activity[i]=nullptr;
          }
}
    return *this;
}
bool Account::operator==(const Account& rhs) const{
    return (this->_id==rhs._id);
}
bool Account::operator==(int id) const{
       return (this->_id==id);
}
Account& Account::operator+=(const Account& rhs){
if(!rhs._activity || !rhs._monthly_activity_frequency) return *this; //rhs bossa
else if(!_activity || !_monthly_activity_frequency){ //objem bossa
    int trans_count=0;
    _activity= new Transaction* [12];
    _monthly_activity_frequency= new int [12];
    for(int i=0; i<12; i++){
        _monthly_activity_frequency[i]=rhs._monthly_activity_frequency[i];
        trans_count=_monthly_activity_frequency[i];
        if(trans_count){
           Transaction *transactions= new Transaction [trans_count];
           for(int j=0; j<trans_count; j++){ transactions[j]= rhs._activity[i][j];}
            _activity[i]=&(transactions[0]);
        }
        else _activity[i]=nullptr;
    }
    return *this;
}
else{
    int trans_count=0;
    Transaction** (month_ptr)= new Transaction* [12];
    int *nw_monthly_activity_frequency= new int [12];
       for(int i=0; i<12; i++){
           nw_monthly_activity_frequency[i]=_monthly_activity_frequency[i]+rhs._monthly_activity_frequency[i];
           trans_count=nw_monthly_activity_frequency[i];
           if(trans_count){ //there is transactions to create
               Transaction *transactions= new Transaction [trans_count];
               if(!(_activity[i])) //transactions only comes from rhs
               for(int j=0; j<trans_count; j++){ transactions[j]= rhs._activity[i][j];}
               else if(!(rhs._activity[i])) //transactions only comes from object itself
               for(int j=0; j<trans_count; j++){ transactions[j]= _activity[i][j];}
               else { //  comes from both lhs and rhs
                   for(int j=0; j<_monthly_activity_frequency[i]; j++){ transactions[j]= _activity[i][j];}
                   for(int j=0; j<rhs._monthly_activity_frequency[i]; j++){ transactions[(_monthly_activity_frequency[i])+j]= rhs._activity[i][j];}
               }
               month_ptr[i]=&(transactions[0]);
            }
            else month_ptr[i]=nullptr;
       }
      if(_activity){ //destruct old objects pointers
          for(int i=0; i<12; i++){
              if(_activity[i]){
                  delete[] _activity[i];
                  _activity[i]=nullptr;}
          }
          delete[] _activity;
          _activity=nullptr;
      }
      if(_monthly_activity_frequency ){
          delete[] _monthly_activity_frequency;
          _monthly_activity_frequency=nullptr;
      }
    _monthly_activity_frequency=nw_monthly_activity_frequency;
    _activity=month_ptr;
       
      for(int i=0; i<12; i++){
          Transaction* (temp_ptr)=_activity[i];
          trans_count=_monthly_activity_frequency[i];
          if(trans_count>1){
           for (int i = 0; i < trans_count-1; i++){ //my_bubble_sort
               for (int j = 0; j < trans_count-i-1; j++){
                   if (temp_ptr[j] > temp_ptr[j+1]){
                       Transaction temp = temp_ptr[j];
                       temp_ptr[j] = temp_ptr[j+1];
                       temp_ptr[j+1] = temp;}
                   }
           }}
       }
    return *this;
}}
double Account::balance(){
       Transaction temp (0, 0);
       if(this->_activity){
           double total_count=0;
           for(int i=0;i<12;i++){
               double sum=0;
               if (_activity[i]){
                   int trans_count=this->_monthly_activity_frequency[i];
                   for(int j=0;j<trans_count;j++) sum+=temp+this->_activity[i][j];
               }
               total_count+=sum;
           }
           return total_count;
       }
       else return (double) 0;
}
double Account::balance(time_t end_date){
    Transaction temp_obj(0, end_date);
    if(this->_activity){
        double total_count=0;
        for(int i=0;i<12;i++){
            double sum=0;
            if (_activity[i]){
                Transaction temp (0, 0);
                int trans_count=this->_monthly_activity_frequency[i];
                for(int j=0;j<trans_count;j++){
                    if(_activity[i][j]< temp_obj) sum+=temp+_activity[i][j];
                    else return total_count+sum;
                    }
            }
            total_count+=sum;
        }
        return total_count;
    }
    else return (double) 0;
}
double Account::balance(time_t start_date, time_t end_date){
    Transaction temp_objs(0, start_date);
    Transaction temp_objf(0, end_date);
    Transaction temp(0, 0);
    if(this->_activity){
        double total_count=0;
        for(int i=0;i<12;i++){
            double sum=0;
            if(_activity[i]){
                    int trans_count=this->_monthly_activity_frequency[i];
                    for(int j=0;j<trans_count;j++){
                        if(_activity[i][j]< temp_objs) continue;
                        else  if(temp_objs < _activity[i][j] && _activity[i][j]< temp_objf) sum+=temp+_activity[i][j];
                        }
                    total_count+=sum;
            }
        }
    return total_count;
    }
    else return (double) 0;
}
std::ostream& operator<<(std::ostream& os, const Account& account){
    if((!account._monthly_activity_frequency) || (!account._activity)) os << -1 << std::endl;
    else{
       os << account._id << std::endl;
       for(int i=0;i<12;i++){
           if(account._activity[i] && account._monthly_activity_frequency[i]){
               int trans_count=account._monthly_activity_frequency[i];
               for(int j=0;j<trans_count;j++){
                   os << account._activity[i][j];
               }
           }
       }
    }
    return os;
}
