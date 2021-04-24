#include "rks.h"

void EditJudgeList()
{
	char judgeMenuChoice;
	int judgeMenuError = 0;
	while(1) 
	{
		ShowJudgeMenu(judgeMenuError);
		judgeMenuError = 0;
						
		fflush(stdin);
		scanf("%c", &judgeMenuChoice);;
					
		if(judgeMenuChoice < '0' || judgeMenuChoice > '3') judgeMenuError = 1;
		else break;
	}
				
	switch(judgeMenuChoice)
	{
		case '1': AddJudge(); break;
		case '2': SetPeriod(); updateStatus(); break;
		case '3': DeleteJudge(); updateStatus(); break;
		case '0': return;
	}
}

void AddJudge()
{
	FILE* fp = fopen("judges.dat", "ab+");
	struct judgeInfo* judgeList = (struct judgeInfo*) calloc(1, sizeof(struct judgeInfo));
	struct judgeInfo* checkName = (struct judgeInfo*) calloc(1, sizeof(struct judgeInfo));
	
	int countNewJudge = 1;
	
	char Fdate[50] = "";
	char Ldate[50] = "";
	
	int Fday;
	int Fmonth;
	int Fyear;
	int Lday;
	int Lmonth;
	int Lyear;

	char wantToSet;
	char confirmToAdd;
	char addMore;
	int nameRepeat;
	
	struct DateInfo InActivePeriodStart;
	struct DateInfo InActivePeriodEnd;
	
	while(1) // введення інформації про суддю
	{
		nameRepeat = 0;
		system("cls");
		puts("                     <<<=====RECORD KEEPING SYSTEM=====>>>\n\n\n");
		
		puts("Enter name: ");
		fflush(stdin);
		gets((judgeList+countNewJudge-1)->name);
		
		while(fread(checkName, sizeof(struct judgeInfo), 1, fp))
		{
			if(strcmp((judgeList+countNewJudge-1)->name, checkName->name) == 0)
			{
				nameRepeat = 1;
				rewind(fp);
				break;
			}
		}
		if(nameRepeat == 1)
		{
			printf("Judge %s is already in the list. Add digit to the name.", checkName->name);
			puts("Press any key to proceed.");
			getch();
			continue;
		}
		
		puts("Enter specialization: ");
		printf("1 - Criminal \n");
		printf("2 - Civil \n");
		printf("3 - Investigation\n");
		
		while(1)
		{
			fflush(stdin);
			scanf("%d", &(judgeList+countNewJudge-1)->spec);
			if((judgeList+countNewJudge-1)->spec == CRIMINAL || (judgeList+countNewJudge-1)->spec == CIVIL || (judgeList+countNewJudge-1)->spec == INVESTIGATORREQUEST) break;
			else puts("ERROR, choose correct answer");
		}
		
		puts("Set inactive period?");
		puts("1 - yes");
		puts("2 - no");
		
		while(1)
		{
			fflush(stdin);
			scanf("%c", &wantToSet);
			if(wantToSet == YES)
			{
				system("cls");
				puts("                     <<<=====RECORD KEEPING SYSTEM=====>>>\n\n\n");
				while(1) // перевірка періоду неактивності
				{
					printf("Enter first day of period (included in period) (dd.mm.yyyy format): \n");
					
					strcpy(Fdate, GetDay(&Fday, &Fmonth, &Fyear));
					(judgeList+countNewJudge-1)->InActivePeriodStart.day = Fday;	
					(judgeList+countNewJudge-1)->InActivePeriodStart.month = Fmonth;	
					(judgeList+countNewJudge-1)->InActivePeriodStart.year = Fyear;
					
					printf("Enter last day of period (included in period) (dd.mm.yyyy format): \n");
					
					strcpy(Ldate, GetDay(&Lday, &Lmonth, &Lyear));
					(judgeList+countNewJudge-1)->InActivePeriodEnd.day = Lday;	
					(judgeList+countNewJudge-1)->InActivePeriodEnd.month = Lmonth;	
					(judgeList+countNewJudge-1)->InActivePeriodEnd.year = Lyear;
					
					if(!PeriodIsCorrect(Fday, Fmonth, Fyear, Lday, Lmonth, Lyear)) continue;
					break;	
				}
			}
			else if (wantToSet == NO)
			{
				(judgeList+countNewJudge-1)->InActivePeriodStart.day = 0;	
				(judgeList+countNewJudge-1)->InActivePeriodStart.month = 0;	
				(judgeList+countNewJudge-1)->InActivePeriodStart.year = 0;
				(judgeList+countNewJudge-1)->InActivePeriodEnd.day = 0;	
				(judgeList+countNewJudge-1)->InActivePeriodEnd.month = 0;	
				(judgeList+countNewJudge-1)->InActivePeriodEnd.year = 0;
				break;	
			}
			else
			{
				puts("ERROR, choose correct answer");
				continue;
			}
			break;
		}	
	
		system("cls");
		puts("                     <<<=====RECORD KEEPING SYSTEM=====>>>\n\n\n");
		puts("\nDO YOU WANT TA ADD:\n");
		printf("Judge name: %s \n", (judgeList+countNewJudge-1)->name);
		switch((judgeList+countNewJudge-1)->spec)
		{
			case CRIMINAL:puts("Specialization: Criminal "); break;
			case CIVIL:puts("Specialization: Civil "); break;
			case INVESTIGATORREQUEST:puts("Specialization: Investigation "); break;
		}
		if((judgeList+countNewJudge-1)->InActivePeriodStart.day == 0)
		{
			puts("Inactivity period unsettled");
		}
		else
		{
			printf("Inactivity period: %s - %s \n", Fdate, Ldate);
		}
		puts("\n1-yes");
		puts("\n2-no(exit)");
		puts("\n3-edit");
		
		int add = 0;
		int edit = 0;
		int exit = 0;
		
		while(1)
		{
			fflush(stdin);
			scanf("%c", &confirmToAdd);
			if(confirmToAdd == YES)
			{
				add = 1;
				break;
			}
			else if(confirmToAdd == NO)
			{
				exit = 1;
				break;
			}
			else if(confirmToAdd == '3')
			{
				edit = 1;
				break;
			}
			else  puts("ERROR, choose correct answer");
		}
		
		int addMore = 0;
		int finish = 0;
		
		if (add==1)
		{
			system("cls");
			puts("                     <<<=====RECORD KEEPING SYSTEM=====>>>\n\n\n");
			puts("Judge added. Add more?");	
			puts("1 - yes");	
			puts("2 - no");	
			while(1) // запит на подальше подальше додоавання судді
			{
				fflush(stdin);
				scanf("%c", &addMore);
				if(addMore == YES)
				{
					addMore = 1;
					break;
				}
				else if(addMore == NO)
				{
					finish = 1;
					break;
				}
				else puts("ERROR, choose correct answer");
			}
				
			if(addMore == 1)
			{
				countNewJudge++;
				judgeList = (struct judgeInfo*)realloc(judgeList, countNewJudge * sizeof(struct judgeInfo));
				continue;
			}
			
			if(finish == 1)
			{
				fwrite(judgeList, countNewJudge * sizeof(struct judgeInfo), 1, fp);
				fclose(fp);
				return;
			}
		}
		if(edit == 1)
		{
			continue;
		}
		if(exit == 1)
		{
			free(judgeList);
			fclose(fp);
			return;
		}
	}
}

int DateIsCorrect(int day, int month, int year) // перевірка дати
{
	if(month<1 || month>12) return 0;
	if(month == 4  || month == 6 || month == 9 || month == 11 )
	{
		if (day>30) return 0;
	}
	
	if( (year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
	{
		if(month == 2)
		{
			if(day > 29) return 0;
		}
	}
	else if(month == 2)
	{
		if(day > 28) return 0;
	}
	
	if(day>31) return 0;
	
	return 1;
}

int updateStatus() // оновлення статусу активності всіх суддів
{
	FILE* Judges = fopen("judges.dat", "rb+");
  
	int countJudges = 0;
	struct tm* getTime;
	time_t timer = time(NULL);
	getTime = localtime(&timer);
	int todayD = getTime->tm_mday;
	int todayM = getTime->tm_mon+1;
	int todayY = getTime->tm_year+1900;
	
	int diffD;
	int diffM;
	int diffY;
	
	
	struct judgeInfo* refreshedJudgeList = (struct judgeInfo*) calloc(1, sizeof(struct judgeInfo));
	
	struct judgeInfo* temp = (struct judgeInfo*) calloc(1, sizeof(struct judgeInfo));
	
	
	while(1)
	{
		int todayIsAfterFirst = 0;
		int todayIsBeforeLast = 0;
		int readJudge = 1;
	
		
		readJudge = fread(temp, sizeof(struct judgeInfo), 1, Judges); // вичитка суддів
		
		if(!readJudge)
		{
			fclose(Judges);
			break;
		}
		
		
		if((temp)->InActivePeriodStart.day == 0) // день початку неактивності 0 - ознака завершення періоду неактивності
		{
			(temp)->status = 1;
			refreshedJudgeList[countJudges] = *temp;
			countJudges++;
			refreshedJudgeList = (struct judgeInfo*)realloc(refreshedJudgeList, (countJudges+1) * sizeof(struct judgeInfo));
			
			continue;
		}
		else // інкашке - перевіряємо статус
		{
			
			
			diffY = (temp)->InActivePeriodStart.year - todayY;
			diffM = (temp)->InActivePeriodStart.month - todayM;
			diffD = (temp)->InActivePeriodStart.day - todayD;
			
			if(diffY<0) // перевірка чи сьогоднішня дата - після початку періоду
			{
				todayIsAfterFirst = 1;
			}
			else if(diffY == 0)
			{
				if(diffM<0)
				{
					todayIsAfterFirst = 1;
				}
				else if(diffM == 0)
				{
					if(diffD<=0)
					{
						todayIsAfterFirst = 1;
					}
				}
			}
		}
		
		if (todayIsAfterFirst == 1) // якщо після початку - перевірка чи до завершення
		{
			diffY = (temp)->InActivePeriodEnd.year - todayY;
			diffM = (temp)->InActivePeriodEnd.month - todayM;
			diffD = (temp)->InActivePeriodEnd.day - todayD;
			
			if(diffY>0)
			{
				todayIsBeforeLast = 1;
			}
			else if(diffY == 0)
			{
				if(diffM>0)
				{
					todayIsBeforeLast = 1;
				}
				else if(diffM == 0)
				{
					if(diffD>=0)
					{
						todayIsBeforeLast = 1;
					}
				}
			}
		}
		
		if(todayIsAfterFirst && todayIsBeforeLast) // попадання у період
		{
			(temp)->status = 0;
			refreshedJudgeList[countJudges] = *temp;
			countJudges++;
			refreshedJudgeList = (struct judgeInfo*)realloc(refreshedJudgeList, (countJudges+1) * sizeof(struct judgeInfo));
		}
		else if (todayIsAfterFirst && !todayIsBeforeLast) // період вже пройшов 
		{
			(temp)->status = 1;
			(temp)->InActivePeriodStart.day = 0; // встановлення ознаки завершення періоду
			refreshedJudgeList[countJudges] = *temp;
			countJudges++;
			refreshedJudgeList = (struct judgeInfo*)realloc(refreshedJudgeList, (countJudges+1) * sizeof(struct judgeInfo));
		}
		else
		{
			(temp)->status = 1; // інкашше - період ще не почався
			refreshedJudgeList[countJudges] = *temp;
			countJudges++;
			refreshedJudgeList = (struct judgeInfo*)realloc(refreshedJudgeList, (countJudges+1) * sizeof(struct judgeInfo));
		}
	}
	
	Judges = fopen("judges.dat", "wb");
	
	fwrite(refreshedJudgeList, _msize(refreshedJudgeList)-sizeof(struct judgeInfo), 1, Judges);
	
	fclose(Judges);
	
	return _msize(refreshedJudgeList)-sizeof(struct judgeInfo);
}

void SetPeriod() // встановлення/зміна статусу активності судді із відповідною перевіркою нового періоду
{
	updateStatus();
	system("cls");
	puts("                     <<<=====RECORD KEEPING SYSTEM=====>>>\n\n\n");
	
	FILE* Judges = fopen("judges.dat", "rb+");
	
	struct judgeInfo* temp = (struct judgeInfo*) calloc(1, sizeof(struct judgeInfo));
	struct judgeInfo* list = (struct judgeInfo*) calloc(1, sizeof(struct judgeInfo));
	int countJudge = 0;
	int judgeNumber;
	
	
	while(fread(temp, sizeof(struct judgeInfo), 1, Judges)) // вичитка та вивидення суддів
	{
		list[countJudge] = temp[0];
		
		printf("#%d.\n", countJudge+1);
		printf("Name: %s\n", (list+countJudge)->name);
		switch((list+countJudge)->spec)
		{
			case CRIMINAL: puts("Spec: Criminal"); break;
			case CIVIL: puts("Spec: Civil"); break;
			case INVESTIGATORREQUEST: puts("Spec: Investigation"); break;
		}

	
		ShowInactivePeriod(list+countJudge);
		
		
		countJudge++;
		list = (struct judgeInfo*)realloc(list, (countJudge+1)*sizeof(struct judgeInfo));
		printf("\n");
	}
	
	char setOrClearChoice;

	while(1)
	{
		puts("Enter judge number to edit");
		puts("Enter 0 to exit");
		fflush(stdin);
		scanf("%d", &judgeNumber);
		if(judgeNumber == 0)
		{
			fclose(Judges);
			return;
		}
		if(judgeNumber < 1 || judgeNumber > countJudge)
		{
			puts ("\nERROR, choose correct number\n");
			continue;
		}
		else
		{
			puts("\n1 - set/reset inactivity period");
			puts("2 - clear inactivity period");
			
			while(1)
			{
				fflush(stdin);
				scanf("%c", &setOrClearChoice);
				if(setOrClearChoice == '1' || setOrClearChoice == '2') break;
				puts ("\nERROR, choose correct number\n");
			}
			
			judgeNumber = judgeNumber-1; // реальний номер суддів починаючи від 0
			
			if(setOrClearChoice == '1') // встановлення/редагування періоду
			{
				system("cls");
				puts("                     <<<=====RECORD KEEPING SYSTEM=====>>>\n\n\n");
			
				while(1)
				{
					int Fday;
					int Fmonth;
					int Fyear;
					int Lday;
					int Lmonth;
					int Lyear;
					
					printf("Enter first day of period (included in period) (dd.mm.yyyy format): \n");
					
					GetDay(&Fday, &Fmonth, &Fyear);
					
					(list+judgeNumber)->InActivePeriodStart.day = Fday;	
					(list+judgeNumber)->InActivePeriodStart.month = Fmonth;	
					(list+judgeNumber)->InActivePeriodStart.year = Fyear;
					
					printf("Enter last day of period (included in period) (dd.mm.yyyy format): \n");
			
					GetDay(&Lday, &Lmonth, &Lyear);
		
					(list+judgeNumber)->InActivePeriodEnd.day = Lday;	
					(list+judgeNumber)->InActivePeriodEnd.month = Lmonth;	
					(list+judgeNumber)->InActivePeriodEnd.year = Lyear;
					
					
					if(!PeriodIsCorrect(Fday, Fmonth, Fyear, Lday, Lmonth, Lyear)) continue; 
						
					
					fseek(Judges, sizeof(struct judgeInfo)*judgeNumber, 0);
					fwrite(list+judgeNumber, sizeof(struct judgeInfo), 1, Judges);
					fclose(Judges);
					
					puts("PERIOD SETTLED\n");
					puts("press any key to continue");
					getch();
					return;
				}
			}
			else if (setOrClearChoice == '2') // очистка періоду
			{
				(list+judgeNumber)->InActivePeriodStart.day = 0; // встановлення ознаки завершення періоду
				fseek(Judges, sizeof(struct judgeInfo)*judgeNumber, 0);
				fwrite(list+judgeNumber, sizeof(struct judgeInfo), 1, Judges);
				fclose(Judges);
				puts("PERIOD CLEAR\n");
				puts("press any key to continue");
				getch();
				return;
			}
		}
	}
}

void DeleteJudge() // процедура видалення судді
{
	updateStatus();
	system("cls");
	puts("                     <<<=====RECORD KEEPING SYSTEM=====>>>\n\n\n");
	puts("ENTER DIGIT TO CHOOSE OPTION\n");
	
	FILE* Judges = fopen("judges.dat", "rb");
	
	struct judgeInfo* temp = (struct judgeInfo*) calloc(1, sizeof(struct judgeInfo));
	struct judgeInfo* list = (struct judgeInfo*) calloc(1, sizeof(struct judgeInfo));
	int countJudge = 0;
	int judgeNumber;
	
	while(fread(temp, sizeof(struct judgeInfo), 1, Judges)) // вичитка та вивидення суддів
	{
		list[countJudge] = temp[0];
		
		printf("#%d.\n", countJudge+1);
		printf("Name: %s\n", (list+countJudge)->name);
		switch((list+countJudge)->spec)
		{
			case CRIMINAL: puts("Spec: Criminal"); break;
			case CIVIL: puts("Spec: Civil"); break;
			case INVESTIGATORREQUEST: puts("Spec: Investigation"); break;
		}
		
		ShowInactivePeriod(list+countJudge);
		
		countJudge++;
		list = (struct judgeInfo*)realloc(list, (countJudge+1)*sizeof(struct judgeInfo));
		printf("\n");
	}
	
	int totalJudges = countJudge-1; // декремент зайвої ітераціїї каунтджадж
	int nextToDeletedNumber;
	
	while(1)
	{
		puts("Enter judge number to delete");
		puts("Enter 0 to exit");
		fflush(stdin);
		scanf("%d", &judgeNumber);
		if(judgeNumber == 0)
		{
			fclose(Judges);
			return;
		}
		if(judgeNumber < 1 || judgeNumber > countJudge) puts ("ERROR, choose correct number");
		else
		{
			if (totalJudges == 0)
			{
				fclose(Judges);
				Judges = fopen("judges.dat", "wb");
				fwrite(list, 0, 1, Judges);
				fclose(Judges);
				remove("judges.dat");
				puts("JUDGE LIST IS EMPTY!");
				puts("press any key to continue");
				getch();
				return;
			}
			else
			{
			
				for(nextToDeletedNumber = judgeNumber; nextToDeletedNumber<countJudge+1; nextToDeletedNumber++)
				{
					list[nextToDeletedNumber-1] = list[nextToDeletedNumber]; // перествановка елементів масиву через звільнення (видалення) елемента
				}
				fclose(Judges);
				Judges = fopen("judges.dat", "wb");
				list = (struct judgeInfo*)realloc(list, _msize(list)-sizeof(struct judgeInfo)); // відсікання зайвого (пустого) реаллока
				fwrite(list, _msize(list) - sizeof(struct judgeInfo), 1, Judges);
				fclose(Judges);
				
				puts("\nJUDGE DELETED\n");
				puts("press any key to continue");
				getch();
				return;
			}
		}
	}
}

void ShowInactivePeriod (struct judgeInfo* list) // виведення періоду неактивності судді
{
	if(list->InActivePeriodStart.day == 0)
	{
		puts("Inactive period unsettled"); 
		return;
	}
	
	printf("Inactive period: ");
	
	if(list->InActivePeriodStart.day<10 && list->InActivePeriodStart.month<10)
	{
		printf("0%d.0%d.%d - ", list->InActivePeriodStart.day, list->InActivePeriodStart.month, list->InActivePeriodStart.year);
	}
	else if( list->InActivePeriodStart.day>=10 && list->InActivePeriodStart.month<10 )
	{
		printf("%d.0%d.%d - ", list->InActivePeriodStart.day, list->InActivePeriodStart.month, list->InActivePeriodStart.year);
	}
	else if( list->InActivePeriodStart.day<10 && list->InActivePeriodStart.month>=10 )
	{
		printf("0%d.%d.%d - ", list->InActivePeriodStart.day, list->InActivePeriodStart.month, list->InActivePeriodStart.year);
	}
	else if( list->InActivePeriodStart.day>=10 && list->InActivePeriodStart.month>=10 )
	{
		printf("%d.%d.%d - ", list->InActivePeriodStart.day, list->InActivePeriodStart.month, list->InActivePeriodStart.year);
	}
	
	if(list->InActivePeriodEnd.day<10 && list->InActivePeriodEnd.month<10)
	{
		printf("0%d.0%d.%d \n", list->InActivePeriodEnd.day, list->InActivePeriodEnd.month, list->InActivePeriodEnd.year);
	}
	else if( list->InActivePeriodEnd.day>=10 && list->InActivePeriodEnd.month<10 )
	{
		printf("%d.0%d.%d \n", list->InActivePeriodEnd.day, list->InActivePeriodEnd.month, list->InActivePeriodEnd.year);
	}
	else if( list->InActivePeriodEnd.day<10 && list->InActivePeriodEnd.month>=10 )
	{
		printf("0%d.%d.%d \n", list->InActivePeriodEnd.day, list->InActivePeriodEnd.month, list->InActivePeriodEnd.year);
	}
	else if( list->InActivePeriodEnd.day>=10 && list->InActivePeriodEnd.month>=10 )
	{
		printf("%d.%d.%d \n", list->InActivePeriodEnd.day, list->InActivePeriodEnd.month, list->InActivePeriodEnd.year);
	}
}
