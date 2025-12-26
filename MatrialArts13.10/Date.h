#ifndef __MYDATE__
#define __MYDATE__

#define MIN_YEAR 1950

typedef unsigned char BYTE;

typedef struct
{
	int	day;
	int	month;
	int	year;
}Date;

void  getCorrectDate(Date* pDate);
int	  checkDate(char* date, Date* pDate);
void  printDate(const Date* pDate);
int	  compareDate(const void* d1, const void* d2);
int   writeDateToFile(FILE* fp, const Date* pDate);
int   readDateFromFile(FILE* fp, Date* pDate);
void  saveDateText(const Date* pDate, FILE* fp);
void  loadDateText(Date* pDate, FILE* fp);

#endif
