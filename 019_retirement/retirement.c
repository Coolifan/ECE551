#include <stdlib.h>
#include <stdio.h>

struct _retire_info {
  int months;  //number of months it is applicable to
  double contribution; //how many $ are contributed from account per month
  double rate_of_return;
};

typedef struct _retire_info retire_info;

double calc(retire_info status, double balance) {
  balance += balance * status.rate_of_return;
  balance += status.contribution;
  return balance;
}


void retirement(int startAge, double initial, retire_info working, retire_info retired) {
  double balance = initial;
  int time;
  
  for (time = startAge; time < startAge+working.months; time++) {
    printf("Age %3d month %2d you have $%.2lf\n",time/12, time%12, balance);
    balance = calc(working, balance);
  }
  for (time = startAge+working.months; time < startAge+working.months+retired.months; time++) {
    printf("Age %3d month %2d you have $%.2lf\n",time/12, time%12, balance);
    balance = calc(retired, balance);
  }
 
}

int main(void){
  int startAge = 327;
  double initial = 21345;
  
  retire_info working;
  working.months = 489;
  working.contribution = 1000;
  working.rate_of_return = 0.045/12; //per month
  retire_info retired;
  retired.months = 384;
  retired.contribution = -4000;
  retired.rate_of_return = 0.01/12;

  retirement(startAge, initial, working, retired);
  
  return EXIT_SUCCESS;
}
