#include "Bank.h"
Bank::Bank(){
    _bank_name="not_defined";
    _user_count=0;
    _users=nullptr;
}
Bank::Bank(std::string bank_name, Account* const users, int user_count){
    _bank_name=bank_name;
    _user_count=user_count;
    _users=new Account [_user_count];
    for(int i=0; i<user_count;i++) _users[i]=users[i];
}
   
Bank::~Bank(){
    if(_users){
        delete [] _users;
        _users=nullptr;}
    _bank_name="not_defined";
    _user_count=0;
}

Bank::Bank(const Bank& rhs){
    _bank_name=rhs._bank_name;
    _user_count=rhs._user_count;
    _users=new Account [_user_count];
    for(int i=0; i<_user_count;i++) _users[i]=rhs._users[i];
}
    
Bank& Bank::operator+=(const Bank& rhs){
    if(!(rhs._users)) return *this;
    else if(!(this->_users)){
        _bank_name=rhs._bank_name;
        _user_count=rhs._user_count;
        _users=new Account [rhs._user_count];
        for(int i=0; i<_user_count; i++) _users[i]=rhs._users[i];
        return *this;
    }
    else{
        int diff_ones=0;
        for(int i=0;i<rhs._user_count;i++){
            bool flag=false;
            for(int j=0;j<_user_count;j++){
                if(_users[j]==rhs._users[i]){ //merge the same ones
                    _users[j]+=rhs._users[i];
                    flag=true;
                    break;
                }
            }
            if(!flag) diff_ones++;  //count diff ones
        }
        if(!diff_ones) return *this; //if no diff ids, return
        else{
        int nw_user_count=diff_ones+_user_count;
        Account *nw_users= new Account [nw_user_count]; //allocate new array
        for(int i=0;i<_user_count;i++) nw_users[i]=_users[i];
        int rest_index=_user_count;
        for(int i=0;i<rhs._user_count;i++){
            bool flag=false;
            for(int j=0;j<_user_count;j++){
                if(_users[j]==rhs._users[i]){
                    flag=true;
                    break;
                }
            }
             if(!flag) nw_users[rest_index]=rhs._users[i]; //append diff ones to the new list
             rest_index++;
        }
        delete [] _users;  //clean up the ex
        _users=nw_users;
        _user_count=nw_user_count;
        return *this;
        }
    }
}
Bank& Bank::operator+=(const Account& new_acc){
    if(!this->_users){
        _users=new Account;
        *_users=new_acc;
        _user_count=1;
    }
    else{
        bool flag=false;
        for(int i=0;i<_user_count;i++){
            if(_users[i]==new_acc){
                _users[i]+=new_acc; //if same id merge
                flag=true;
                break;
            }
        }
        if(!flag){    //if distinct account
            int nw_user_count=_user_count+1;
            Account *nw_users= new Account [nw_user_count];
            for(int i=0;i<_user_count;i++) nw_users[i]=_users[i];
            nw_users[nw_user_count-1]=new_acc;
            _user_count=nw_user_count;
            delete [] _users;  //clean up the ex
            _users=nw_users;
            _user_count=nw_user_count;
        }
    }
    return *this;
}

Account& Bank::operator[](uint account_id){
    for(int i=0;i<_user_count;i++){
        if(_users[i]==account_id){
            return _users[i];
        }
    }
    return _users[0];
}

std::ostream& operator<<(std::ostream& os, const Bank& bank){
    int loan_users=0, total_balance=0;;
    int monthly_balance=0,next_m_balance=0,prev_month=0;
    for(int i=0;i<bank._user_count;i++){
        bool flag=false;  //loan user or not
        for(int j=0;j<12;j++){
        struct tm temp = {0};
        temp.tm_hour = 0;   temp.tm_min = 0; temp.tm_sec = 0;
        temp.tm_year = 119; temp.tm_mon = j+1; temp.tm_mday = 0;
        time_t temp_time = mktime(&temp);
        monthly_balance=bank._users[i].balance(temp_time)-prev_month;
        if(monthly_balance<0){
            struct tm temp2 = {0};
            temp2.tm_hour = 0;   temp2.tm_min = 0; temp2.tm_sec = 0;
            temp2.tm_year = 119; temp2.tm_mon = j+2; temp2.tm_mday = 0;
            time_t temp_time2 = mktime(&temp2);
            next_m_balance=bank._users[i].balance(temp_time2)-bank._users[i].balance(temp_time);
            if(next_m_balance<0) {flag =true; break;} //not a loan user
        }
        prev_month=monthly_balance;
        }
    if(!flag) loan_users++;
    total_balance+=bank._users[i].balance();
    }
    os << bank._bank_name << "\t" << loan_users <<"\t" << total_balance << std::endl;
    return os;
}
