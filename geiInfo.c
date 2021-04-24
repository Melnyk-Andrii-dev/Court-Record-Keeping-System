#include "rks.h"

PCase ChangeCaseInfo(PCase change, int category)
{
	
	switch (category)
	{
		case CRIMINAL:
			printf("Enter accussed: ");
			fflush(stdin);
			gets(change->accussed);
			printf("Enter victim: ");
			fflush(stdin);
			gets(change->victim);
			printf("Enter the matter of case: ");
			fflush(stdin);
			gets(change->matter);
			strcpy(change->category, "Criminal");
			
			change->plaintiff[0] = 0;
			change->defendant[0] = 0;
			change->investigator[0] = 0;
			change->violator[0] = 0;
			
			break;
		case CIVIL:
			printf("Enter plaintiff: ");
			fflush(stdin);
			gets(change->plaintiff);
			printf("Enter defendant: ");
			fflush(stdin);
			gets(change->defendant);
			printf("Enter the matter of case: ");
			fflush(stdin);
			gets(change->matter);
			strcpy(change->category, "Civil");
			
			change->accussed[0] = 0;
			change->victim[0] = 0;
			change->investigator[0] = 0;
			change->violator[0] = 0;
				
			break;
		case INVESTIGATORREQUEST:
			printf("Enter investigator: ");
			fflush(stdin);
			gets(change->investigator);
			printf("Enter the matter of case: ");
			fflush(stdin);
			gets(change->matter);
			strcpy(change->category, "Investigator request");
			
			change->accussed[0] = 0;
			change->victim[0] = 0;
			change->plaintiff[0] = 0;
			change->defendant[0] = 0;
			change->violator[0] = 0;
				
			break;	
		case ADMINISTRATIVEOFFENSE:
			printf("Enter violator: ");
			fflush(stdin);
			gets(change->violator);
			printf("Enter the matter of case: ");
			fflush(stdin);
			gets(change->matter);
			strcpy(change->category, "Administrative offense");	
			
			change->accussed[0] = 0;
			change->victim[0] = 0;
			change->plaintiff[0] = 0;
			change->defendant[0] = 0;
			change->investigator[0] = 0;
				
			break;
	}
	return change;
}

int ChangeCategory(PCase change)
{
	int category;
	if(strcmp(change->category, "Criminal") == 0) category = CRIMINAL;
	if(strcmp(change->category, "Civil") == 0) category = CIVIL;
	if(strcmp(change->category, "Investigation") == 0) category = INVESTIGATORREQUEST;
	if(strcmp(change->category, "Administrative offense") == 0) category = ADMINISTRATIVEOFFENSE;
	return category;
}
void ClearJudge(PCase change)
{
	int countSymbols;
	int totalNameSymbols;
	puts("No judges are available for this category");
	printf("\npress any key to continue\n");
	totalNameSymbols = strlen(change->jadge);
	for(countSymbols=0; countSymbols<=totalNameSymbols; countSymbols++)
	{
		change->jadge[countSymbols] = 0;
	}
	getch();
}

int ChangeFirstLine(PCase change)
{
	int changedSucces = 1;
	if(strcmp(change->category, "Criminal") == 0)
	{
		
		puts("Enter new accused");
		fflush(stdin);
		gets(change->accussed);
	}
	else if(strcmp(change->category, "Civil") == 0)
	{
		puts("Enter new plaintiff");
		fflush(stdin);
		gets(change->plaintiff);
	}
	else if(strcmp(change->category, "Investigator request") == 0)
	{
		puts("Enter new investigator");
		fflush(stdin);
		gets(change->investigator);
	}
	else if(strcmp(change->category, "Administrative offense") == 0)
	{
		puts("Enter new violator");
		fflush(stdin);
		gets(change->violator);
	}
	else
	{
		puts("\nERROR, choose correct option\n");
		changedSucces = 0;
	} 
	return changedSucces;			
}

PCase ReplaceChangedInSorted(PCase sortmas, PCase change)
{
	int totalSorted =  _msize(sortmas)/sizeof(struct Case)  - 1;
	int countSorted;
	
	for(countSorted=0; countSorted<totalSorted; countSorted++)
	{
		if(strcmp((sortmas+countSorted)->CNnumber, change->CNnumber) == 0)
		{
			sortmas[countSorted] = change[0];
			break;
		}
	}
	return sortmas;
}

int ChangeSecondLine(PCase change)
{
	int changedSucces = 1;
	if(strcmp(change->category, "Criminal") == 0)
	{
		
		puts("Enter new victim");
		fflush(stdin);
		gets(change->victim);
	}
	else if(strcmp(change->category, "Civil") == 0)
	{
		puts("Enter new defendant");
		fflush(stdin);
		gets(change->defendant);
	}
	else if(strcmp(change->category, "Investigator request") == 0)
	{
		puts("Enter new metter of case");
		fflush(stdin);
		gets(change->matter);
	}
	else if(strcmp(change->category, "Administrative offense") == 0)
	{
		puts("Enter new metter of case");
		fflush(stdin);
		gets(change->matter);
	}
	else
	{
		puts("\nERROR, choose correct option\n");
		changedSucces = 0;
	} 
	
	return changedSucces;
}

int ChangeThirdLine(PCase change)
{
	int changedSucces = 1;
	if(strcmp(change->category, "Criminal") == 0)
	{
		
		puts("Enter new metter of case");
		fflush(stdin);
		gets(change->matter);
	}
	else if(strcmp(change->category, "Civil") == 0)
	{
		puts("Enter new metter of case");
		fflush(stdin);
		gets(change->matter);
	}
	else
	{
		puts("\nERROR, choose correct option\n");
		changedSucces = 0;
	} 
	return changedSucces;
}

char* GetDay(int* day, int* month, int* year)
{
	char* date = (char*) calloc (20, sizeof(char));
	int	incorrectDate = 0;
	int dateSymbol = 0;
	char checkDate;
	
	
	while(1) // введення періоду із перевіркою
	{
		dateSymbol = 0;
		
		fflush(stdin);
		gets(date);
		*day = (date[0] - '0') * 10 + date[1] - '0';
		if(*day > 31 || *day < 1)
		{
			puts("ERROR, incorrect date");
			continue;
		}
		if(date[2] != '.')
		{
			puts("ERROR, incorrect date");
			continue;	
		}
		if(strlen(date) != 10)
		{
			puts("ERROR, incorrect date");
			continue;
		}
		
		*month = (date[3] - '0') * 10 + date[4] - '0';
		if(*month > 12 || *month < 1) break;
		*year =  (date[6] - '0') * 1000 + (date[7] - '0') * 100 + (date[8] - '0') * 10 + date[9] - '0';
		if(date[10] != '\0')
		{
			puts("ERROR, incorrect date");
			continue;	
		}
		
		while(1)
		{
			checkDate = date[dateSymbol];
			
				if(  ( (checkDate < '0' || checkDate > '9' ) && ( dateSymbol != 2 && dateSymbol != 5) ) || (date[2] != '.' || date[5] != '.' )  )
				{
					puts("ERROR, incorrect date");
					incorrectDate = 1;
					break;
				}
	
			dateSymbol++;
			if(dateSymbol==10) break;
		}
					
		if(incorrectDate == 1) continue;
		if(!DateIsCorrect(*day, *month, *year))
		{
			puts("ERROR, incorrect date");
			continue;		
		}
		else return date;
	}
}

int PeriodIsCorrect(int Fday, int Fmonth, int Fyear, int Lday, int Lmonth, int Lyear)
{
	if(Lday - Fday < 0)
	{
		puts("ERROR, incorrect date");
		return 0;
	}
	else if(Lyear - Fyear == 0)
	{
		if(Lmonth - Fmonth < 0)
		{
			puts("ERROR, incorrect date");
			return 0;
		}
		else if(Lmonth - Fmonth == 0)
		{
			if(Lday - Fday < 0)
			{
				puts("ERROR, incorrect date");
				return 0;
			}
		}
	}
	
	return 1;
}

PCase GetNewCaseInfo(PCase NewCase, int category)
{
	system("cls");	
	puts("                     <<<=====RECORD KEEPING SYSTEM=====>>>\n\n\n");
	
	switch (category) // введення справи відповідно до обраної категорії
	{
		case 1:
			printf("Enter accussed: ");
			fflush(stdin);
			gets(NewCase->accussed);
			printf("Enter victim: ");
			fflush(stdin);
			gets(NewCase->victim);
			printf("Enter the matter of case: ");
			fflush(stdin);
			gets(NewCase->matter);
			strcpy(NewCase->category, "Criminal");
			break;
		case 2:
			printf("Enter plaintiff: ");
			fflush(stdin);
			gets(NewCase->plaintiff);
			printf("Enter defendant: ");
			fflush(stdin);
			gets(NewCase->defendant);
			printf("Enter the matter of case: ");
			fflush(stdin);
			gets(NewCase->matter);
			strcpy(NewCase->category, "Civil");	
			break;
		case 3:
			printf("Enter investigator: ");
			fflush(stdin);
			gets(NewCase->investigator);
			printf("Enter the matter of case: ");
			fflush(stdin);
			gets(NewCase->matter);
			strcpy(NewCase->category, "Investigator request");	
			break;	
		case 4:
			printf("Enter violator: ");
			fflush(stdin);
			gets(NewCase->violator);
			printf("Enter the matter of case: ");
			fflush(stdin);
			gets(NewCase->matter);
			strcpy(NewCase->category, "Administrative offense");		
			break;	
	}
	
	return NewCase;
}

int GetCategory(int* incorrectCategory)
{
	int category;
	char categoryChoice;
	
	fflush(stdin);
	scanf("%c", &categoryChoice); // вибір категорії справи
	
	categoryChoice = categoryChoice - '0';
	
	if(categoryChoice==CRIMINAL) category = CRIMINAL;
	else if(categoryChoice==CIVIL) category = CIVIL;
	else if(categoryChoice==INVESTIGATORREQUEST) category = INVESTIGATORREQUEST;
	else if(categoryChoice==ADMINISTRATIVEOFFENSE) category = ADMINISTRATIVEOFFENSE;
	else if(categoryChoice==0) category = 0;
	else *incorrectCategory = 1;

	return category;	
}
