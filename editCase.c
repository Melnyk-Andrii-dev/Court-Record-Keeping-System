#include "rks.h"

FILE* InitialAdd(FILE* mainStorage)
{
	char initialAdd;
	char moreAdd;
	int incorrectInitAdd = 0;
					
	showManual();
		
	while(1) // запит на первинне наповнення бази
	{
		ShowInitialMenu(incorrectInitAdd);
		
		incorrectInitAdd = 0;
		
		fflush(stdin);
		scanf("%c", &initialAdd);
		system("cls");
		if(initialAdd == YES)
		{
			AddCase();
			CLOSE;
			OPENTOREAD;
			
			if(!mainStorage) 
			{
				return NULL;	
			}
			
			return mainStorage;	 
		}
		else if(initialAdd == NO)
		{
			return NULL;
		}	
		else
		{	
			incorrectInitAdd = 1;
			continue;	
		}
	}
}

PCase EditCase(PCase sortmas)
{
	updateStatus();
	
	char inputNumberToEdit[20] = "";
	FILE* mainStorage;
	OPENTOREAD;
	PCase temp = (PCase) calloc(1, sizeof(struct Case));
	PCase caseToChange = (PCase) calloc(1, sizeof(struct Case));
	char inputLine;
	char changeJudge;
	int category = 0;
	
	char* judge;
	
		
	while(1)
	{
		puts("\nEnter full case number to edit");
		puts("Enter 2 to exit");
		
		fflush(stdin);
		gets(inputNumberToEdit);
		if(inputNumberToEdit[0] == NO) return NULL;
		
		while(1) // пошук введеної справи
		{
			if(fread(temp, sizeof(struct Case), 1, mainStorage) == 0) // не знайдено
			{
				printf("Case #%s not found! ", inputNumberToEdit);
				puts("\nPRESS ANY KEY TO PROCEED\n");
				getch();
				return NULL;
			}
			if(strcmp(temp->CNnumber, inputNumberToEdit) == 0) // знайдено
			{
				break;
			}
		}
		
	
		puts("\nWHAT LINE DO YOU WANT TO CHANGE :\n");
		ShowCaseToEdit(temp);
		
		
		puts("Enter number of line to edit:");
		
		while(1)
		{
			fflush(stdin);
			scanf("%c", &inputLine);
			if(inputLine == '1')  // зміна категорії (зміна всіх полів)
			{
				strcpy(caseToChange->CNnumber, temp->CNnumber);
				printf("Enter case category: \n");
				printf("1 - Criminal \n");
				printf("2 - Civil \n");
				printf("3 - Investigator request\n");
				printf("4 - Administrative offense \n");
				
				while(1)
				{
					fflush(stdin);
					scanf("%d", &category);
					if(category != CRIMINAL && category != CIVIL && category != INVESTIGATORREQUEST && category != ADMINISTRATIVEOFFENSE)
					{
						puts("ERROR, choose correct category: \n");
					}
					else break;
				}
		
				caseToChange = ChangeCaseInfo(caseToChange, category);
		
				puts("Change judge?");
				puts("1 - yes");
				puts("2 - no");
				
				while(1)
				{
			    	fflush(stdin);
			        scanf("%c", &changeJudge);
					if(changeJudge == YES)
					{	
						judge = CaseAllocation(category);
						if(judge)
						{
							strcpy(caseToChange->jadge, judge);
						}
						else
						{
							puts("No judges are available for this category");
						}
					}
					else if(changeJudge == NO)
					{
						strcpy(caseToChange->jadge, temp->jadge);
					}
					else
					{
						puts("ERROR, choose correct option: \n");
						continue;
					}
					break;
				}
		
				caseToChange->dateOfIncome.day = temp->dateOfIncome.day;	
				caseToChange->dateOfIncome.month = temp->dateOfIncome.month;
				caseToChange->dateOfIncome.year = temp->dateOfIncome.year;
				
				fseek(mainStorage, -(long)sizeof(struct Case), 1);
				
				fwrite(caseToChange, sizeof(struct Case), 1, mainStorage);
				CLOSE;
				
				sortmas = ReplaceChangedInSorted(sortmas, caseToChange);
				return sortmas;	
			}
			else if(inputLine == '2') // зміна судді - повторний авторозподіл
			{
				
				*caseToChange = *temp;
				
				FILE* fpJ = fopen("judges.dat", "rb");
				struct judgeInfo* checkJudge = (struct judgeInfo*)calloc(1, sizeof(struct judgeInfo));
				
				if(!fpJ)
				{
					puts("\nERROR, no judges available!");
					return NULL;
				}
				else
				{
					while(1) // перевірка можливості заміни обраного судді
					{
						if(fread(checkJudge, sizeof(struct judgeInfo), 1, fpJ) == 0)
						{
							break;
						}
						
						if(strcmp(checkJudge->name, caseToChange->jadge) == 0)
						{
							if(checkJudge->status == 1) // якщо статус активний - неможливо змінити
							{
								printf("\nJUDGE %s IS STILL ACTIVE AND CAN NOT BE CHANGED!\n",caseToChange->jadge);
								printf("\npress any key to continue\n");
								getch();
								return NULL;
							}
						}	
					}
				}
				
				fclose(fpJ);
				
				category = ChangeCategory(caseToChange);
				
				judge = CaseAllocation(category);
			
				if(judge) 
				{
					strcpy(caseToChange->jadge, judge);
				}
				else
				{
					ClearJudge(caseToChange);
				}
			
				fseek(mainStorage, -(long)sizeof(struct Case), 1);
				
				fwrite(caseToChange, sizeof(struct Case), 1, mainStorage);
				CLOSE;
				
				sortmas = ReplaceChangedInSorted(sortmas, caseToChange);
				return sortmas;		
			}
			else if(inputLine == '3') // зміна третього поля - відповідно до категорії справи
			{
				*caseToChange = *temp;
				
				if(ChangeFirstLine(caseToChange) == 0) continue;
				
				fseek(mainStorage, -(long)sizeof(struct Case), 1);
				
				fwrite(caseToChange, sizeof(struct Case), 1, mainStorage);
				CLOSE;
				
				sortmas = ReplaceChangedInSorted(sortmas, caseToChange);
				return sortmas;		
			}
			else if(inputLine == '4') // зміна четвертого поля - відповідно до категорії справи
			{
				*caseToChange = *temp;
				
				if(ChangeSecondLine(caseToChange) == 0) continue;
				
				fseek(mainStorage, -(long)sizeof(struct Case), 1);
				
				fwrite(caseToChange, sizeof(struct Case), 1, mainStorage);
				CLOSE;
				
				sortmas = ReplaceChangedInSorted(sortmas, caseToChange);
				return sortmas;	
			}
			else if(inputLine == '5') // зміна п'ятого поля - передбачена не для всіх категорії
			{
				*caseToChange = *temp;
				
				if(ChangeThirdLine(caseToChange) == 0) continue;
				
				fseek(mainStorage, -(long)sizeof(struct Case), 1);
				
				fwrite(caseToChange, sizeof(struct Case), 1, mainStorage);
				CLOSE;
				
				sortmas = ReplaceChangedInSorted(sortmas, caseToChange);
				return sortmas;	
			}
			else puts("\nERROR, choose correct option\n");
		}	
	}
}
