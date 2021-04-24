#include "rks.h"

void FindCase()
{
	while(1)
	{
		FILE* mainStorage; 
		OPENTOREAD; 
		char findChoice;
		char sortChoice;
		char wantToEdit;
		char caseNumberInput[20];
		int foundCases = 0;
		char participant[50];
		int exit = 0;
		int NotFound = 0;
		int incorrectFindChoice = 0;
		
		PCase temp = (PCase) calloc(1, sizeof(struct Case));
		PCase sortmas = (PCase) calloc(1, sizeof(struct Case));

		while(1)
		{			
			ShowFindMenu(&NotFound, &incorrectFindChoice);
			
			NotFound = 0;
			incorrectFindChoice = 0;
			
			fflush(stdin);
			scanf("%c", &findChoice);
			switch(findChoice)
			{
				case '1': // ����� �� ������� ������
					
					system("cls");
					puts("                     <<<=====RECORD KEEPING SYSTEM=====>>>\n\n\n");
					
					puts("Enter number: ");
					fflush(stdin);
					gets(caseNumberInput);
					
					system("cls");
					puts("                     <<<=====RECORD KEEPING SYSTEM=====>>>\n\n\n");
					
					while(fread(temp, sizeof(struct Case), 1, mainStorage)) // ������� �����
					{
						if(strstr(temp->CNnumber, caseNumberInput)) // ����� ��������
						{
							sortmas[foundCases] = temp[0];
							foundCases++;
							sortmas = (PCase)realloc(sortmas, (foundCases+1)*sizeof(struct Case));
						}
					}
					if(!fread(temp, sizeof(struct Case), 1, mainStorage) && sortmas->CNnumber[0] == 0) // ���� �������� �� ����� �� ��������
					{
						rewind(mainStorage);
						NotFound = 1;
						continue;
					}
					break;
				case '2': // ����� �� ��������� ������
					
					system("cls");
					puts("                     <<<=====RECORD KEEPING SYSTEM=====>>>\n\n\n");
					
					puts("Enter participant: ");
					fflush(stdin);
					gets(participant);
					
					system("cls");
					puts("                     <<<=====RECORD KEEPING SYSTEM=====>>>\n\n\n");
					
					while(fread(temp, sizeof(struct Case), 1, mainStorage))
					{
						if( strstr(temp->accussed, participant) || strstr(temp->applicant, participant) || strstr(temp->defendant, participant) || strstr(temp->investigator, participant)
						|| strstr(temp->plaintiff, participant) || strstr(temp->victim, participant) || strstr(temp->violator, participant) )
						{
							sortmas[foundCases] = temp[0];
							foundCases++;
							sortmas = (PCase)realloc(sortmas, (foundCases+1)*sizeof(struct Case));
						}
					}
					if(!fread(temp, sizeof(struct Case), 1, mainStorage) && sortmas->CNnumber[0] == 0)
					{
						rewind(mainStorage);
						NotFound = 1;
						continue;	
					} 
					break;	
				case '3': // ����� �� ����� �����������
					system("cls");
					puts("                     <<<=====RECORD KEEPING SYSTEM=====>>>\n\n\n");
					
					CLOSE;
					sortmas = FindByIncomeDate();
					foundCases = _msize(sortmas)/sizeof(struct Case);
					OPENTOREAD;
					
					system("cls");
					puts("                     <<<=====RECORD KEEPING SYSTEM=====>>>\n\n\n");
					
					if(sortmas == NULL) 
					{
						rewind(mainStorage);
						NotFound = 1;
						continue;	
					} 
					break;	
				case '4': // ���������� �����
					ShowSortMenu();			
					while(1)
					{
						
						fflush(stdin);
		            	scanf("%c", &sortChoice);
						switch (sortChoice)
						{
							case '1':  // ���������� �� ������� 
								system("cls");
								puts("                     <<<=====RECORD KEEPING SYSTEM=====>>>\n\n\n");

								while(fread(temp, sizeof(struct Case), 1, mainStorage)) // ������� ��� ����� �� �������
								{
									sortmas[foundCases] = temp[0];
									foundCases++;
									sortmas = (PCase)realloc(sortmas, (foundCases+1)*sizeof(struct Case));
								}
								break;
							case '2': // ���������� �� ���������, �������� �� ������ - �� ��������� ���������� �� ��������
							case '3':
							case '4':
								system("cls");
								puts("                     <<<=====RECORD KEEPING SYSTEM=====>>>\n\n\n");
								CLOSE;
								sortmas = SortBy(sortChoice);
								foundCases = _msize(sortmas)/sizeof(struct Case);
								OPENTOREAD;
								break;	
							case '0':
								exit = 1;
								break;
							default:
								puts("ERROR, choose correct answer");
								continue;
						}
							
						if(exit == 1 || foundCases != 0) break;
					
					}
					break;
				case '0':
					return;	
				default:
					incorrectFindChoice = 1;
					continue;	
			}
			if(exit == 1)
			{
				CLOSE;
				break;
			} 
			if(foundCases!=0)  break;
		}
		
		if(exit==1) continue;
		
		foundCases = foundCases-1; // ������� ������� ������� �� ����
		
		system("cls");
		puts("                     <<<=====RECORD KEEPING SYSTEM=====>>>\n\n\n");
		
		if(sortmas != NULL) //  ���� ������������ ������� �� ������ - ����
		{
			ShowSorted(sortmas, foundCases);
		}
		else continue;
		
		while(1) //  ������� ��������� ����������� ��������� ������
		{
			puts("Edit any case?");
			puts("1 - yes");
			puts("2 - no");
		
	
			fflush(stdin);
			scanf("%c", &wantToEdit);
			if(wantToEdit == YES)
			{
				sortmas = EditCase(sortmas);
				if(sortmas != NULL)
				{
					system("cls");
					puts("                     <<<=====RECORD KEEPING SYSTEM=====>>>\n\n\n");
					ShowSorted(sortmas, foundCases);
				}
				else break;
				
			}
			else if(wantToEdit == NO)
			{
				return;
			}
			else
			{
				puts("\n ERROR, choose correct answer");
			}
		}
	}
	
}

PCase FindByIncomeDate()
{
	
	int Fday;
	int Fmonth;
	int Fyear;
	int Lday;
	int Lmonth;
	int Lyear;
	
	int foundCases = 0;
	
	struct DateInfo Start;
	struct DateInfo End;
	
	system("cls");
	puts("                     <<<=====RECORD KEEPING SYSTEM=====>>>\n\n\n");
	
	while(1)
	{
		printf("Enter first day of period (included in period) (dd.mm.yyyy format): \n");
		
		GetDay(&Fday, &Fmonth, &Fyear);
		Start.day = Fday;	
		Start.month = Fmonth;	
		Start.year = Fyear;
		
		printf("Enter last day of period (included in period) (dd.mm.yyyy format): \n");
		
		GetDay(&Lday, &Lmonth, &Lyear);
		End.day = Lday;	
		End.month = Lmonth;	
		End.year = Lyear;
		
		
		if(!PeriodIsCorrect(Fday, Fmonth, Fyear, Lday, Lmonth, Lyear)) continue; 
			
		FILE* mainStorage;
		OPENTOREAD;
					
		PCase mas = (PCase) calloc(1, sizeof(struct Case));
		PCase temp = (PCase) calloc(1, sizeof(struct Case));
		int readSuccess = 0;
						
		while(1)  // ���������� �� �������� ������� - ��������� ���, �� ����� ����� �� ����
		{
			
			readSuccess = fread(temp, sizeof(struct Case), 1, mainStorage); // �������
			
			if(readSuccess == 0) // ���� ��� �������� - ��������� ����
			{
				
				switch(Start.month)
				{
					case 4:
					case 6:
					case 9:
					case 11:
						if(Start.day<30) Start.day++;
						else
						{
							Start.month++;
							Start.day = 1;
						} 
						break;
					case 1:
					case 3:
					case 5:
					case 7:
					case 8:
					case 10:
					if(Start.day<31) Start.day++;
						else
						{
							Start.month++;
							Start.day = 1;
						}
						break;
					case 12:
						if(Start.day<31) Start.day++;
						else
						{
							Start.year++;
							Start.month = 1;
							Start.day = 1;
						} 	
					case 2:
						if( (Start.year % 4 == 0 && Start.year % 100 != 0) || Start.year % 400 == 0)
						{
							if(Start.day<29) Start.day++;
							else
							{
								Start.month++;
								Start.day = 1;	
							} 
						}
						else
						{
							if(Start.day<28) Start.day++;
							else
							{
								Start.month++;
								Start.day = 1;
							} 
						}
						break;
				}
				
				rewind(mainStorage);
				
				if(Lyear - Start.year < 0) // ������������ ������ �� �������� �����
				{
					fclose(mainStorage);
					mas = (PCase)realloc(mas, _msize(mas) - sizeof(struct Case)); // ������� ������� (������) realloc
					return mas;
				}
				else if(Lyear - Start.year == 0)
				{
					if(Lmonth - Start.month < 0)
					{
						fclose(mainStorage);
						mas = (PCase)realloc(mas, _msize(mas) - sizeof(struct Case));
						return mas;
					}
					else if(Lmonth - Start.month == 0)
					{
						if(Lday - Start.day < 0)
						{
							fclose(mainStorage);
							mas = (PCase)realloc(mas, _msize(mas) - sizeof(struct Case));
							return mas;
						}
					}
				}
			}
			else // ���� �� �������� - ���������� ����
			{
				if(Start.day == temp->dateOfIncome.day && Start.month == temp->dateOfIncome.month && Start.year == temp->dateOfIncome.year) // ���� ��������� - ��������� �� ������������� ������
				{
					mas[foundCases] = temp[0];
					foundCases++;
					mas = (PCase)realloc(mas, (foundCases+1)*sizeof(struct Case));	
				}
			}	
		}		
	}
	
}
