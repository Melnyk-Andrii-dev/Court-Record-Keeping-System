#include "rks.h"

int AddCase()
{
	while(1)
	{
		system("cls");
		puts("                     <<<=====RECORD KEEPING SYSTEM=====>>>\n\n\n");
		puts("ENTER DIGIT TO CHOOSE OPTION\n");
		
		int category;
		int incorrectCategory;
		char addMore;
		
		
		char* CaseNumber;
		char* judge;
		char accussed[200];
		char victim[200];
		char plaintiff[200];
		char defendant[200];
		char investigator[50];
		char applicant[50];
		char violator[50];
		char matter[200];
		
		PCase NewCase = (PCase) calloc(1, sizeof(struct Case));
		
		ShowChooseCategoryMenu(incorrectCategory);
		
		incorrectCategory = 0;
		
		category = GetCategory(&incorrectCategory);
		
		if(incorrectCategory == 1) continue;
		
		if(category == 0)
		{
			system("cls");
			return 0;
		}
		
		
		NewCase = GetNewCaseInfo(NewCase, category);
		
		judge = CaseAllocation(category); // авторозподіл справи - обрання судді якщо є можливість відповідно до статусу активності
		if(judge)
		{
			strcpy(NewCase->jadge, judge);
		}
		else
		{
			puts("No judges are available for this category");
		}
		
		
		NewCase->dateOfIncome = IncomeDateAssign();
		
		strcpy(NewCase->CNnumber, CaseNumberAssign(NewCase));
		
		
		
		FILE* mainStorage = fopen("mainStorage.dat", "ab+");
		
		fwrite(NewCase, sizeof(struct Case), 1, mainStorage);
		
		CLOSE;
		
		printf("\n\nCase #%s added. Judge - %s.\n", NewCase->CNnumber, NewCase->jadge);
		
		puts("Add more?");
		printf("1 - yes \n");
		printf("2 - no \n");
		while(1)
		{
			fflush(stdin);
			scanf("%c", &addMore);
			if(addMore == YES || addMore == NO) break;
			printf("ERROR, choose correct answer\n");
		}
		if(addMore == YES) continue;
		if(addMore == NO) return 0;
	}
}

char* CaseAllocation(int category) // функція авторозподілу
{
	
	FILE* fpJudges = fopen("judges.dat", "rb");
	char initialAdd = 0;
	int countTotalJudge = 0;
	int countFiltredJudge = 0;
	int countAddedJudge = 0;
	int judgesListSize;
	
	if(!fpJudges)
	{
		fclose(fpJudges);
		puts("The list of judges is empty. Fullfill the list?");
		puts("1 - yes");
		puts("2 - no");
		
		while(1)
		{
			fflush(stdin);
			scanf("%c", &initialAdd);
			if(initialAdd == YES)
			{
				AddJudge();
				break;	
			}
			else if(initialAdd == NO) return NULL;
			else puts("ERROR, choose correct answer");
		}
		fpJudges = fopen("judges.dat", "rb");
	}
	
	judgesListSize = updateStatus();
	countTotalJudge = judgesListSize/sizeof(struct judgeInfo);
	
	struct judgeInfo* Globalmas = (struct judgeInfo*) calloc(judgesListSize, sizeof(struct judgeInfo));
	struct judgeInfo* filtredMas = (struct judgeInfo*) calloc(1, sizeof(struct judgeInfo));
	
	fread(Globalmas, judgesListSize, 1, fpJudges); // вичитка всіх суддів


	for(countFiltredJudge=0; countFiltredJudge<countTotalJudge; countFiltredJudge++)
	{
		if( ( (Globalmas+countFiltredJudge)->spec == category && (Globalmas+countFiltredJudge)->status == 1) || (category == ADMINISTRATIVEOFFENSE && (Globalmas+countFiltredJudge)->status == 1))
		{
			filtredMas = (struct judgeInfo*)realloc(filtredMas, _msize(filtredMas) + sizeof(struct judgeInfo));
			filtredMas[countAddedJudge] = Globalmas[countFiltredJudge];
			countAddedJudge++;
		}
	}
	
	char* judge = (char*) calloc(50, sizeof(char));
	
	if(filtredMas[0].spec == 0) return NULL;
	
	int randJudge;
	
	srand(time(NULL));
	
	randJudge = 0 + rand() % (countAddedJudge-1-0+1);

	strcpy(judge, (filtredMas+randJudge)->name);
	
	return judge;
}

char* CaseNumberAssign(PCase NewCase) // функція присвоєння номера справи
{
	FILE* mainStorage;
	OPENTOREAD;
	PCase CaseTrash = (PCase) calloc(1, sizeof(struct Case));
	int countCase = 0;
	char* caseNumber = (char*) calloc(20, sizeof(char));
	int prevCaseYear;
	
	struct CN number;
	
	
	struct tm* getTime;
	time_t timer = time(NULL);
	getTime = localtime(&timer);
	int todayY = getTime->tm_year+1900-2000; // дві останні цифри року
	
	number.index = 127;
	
	if(!mainStorage)
	{
		number.number = 1;
		CLOSE;
	}
	else
	{
		while(fread(CaseTrash, sizeof(struct Case), 1, mainStorage))
		{
			countCase++;
			if(CaseTrash->dateOfIncome.year != prevCaseYear) countCase = 1; // присвоєння чергового номера
			prevCaseYear = CaseTrash->dateOfIncome.year;
		}
		if(CaseTrash->dateOfIncome.year != NewCase->dateOfIncome.year) countCase = 0; // при зміні років - обнулення порядкового номера
		number.number = countCase+1;
		CLOSE;
	}
	
	
	number.year = todayY;
	
	sprintf(caseNumber, "%d/%d/%d", number.index, number.number, number.year);
	
	return caseNumber;
}

struct DateInfo IncomeDateAssign() // присвоєння вхідної дати
{
	struct DateInfo Income;
	struct tm* getTime;
	time_t timer = time(NULL);
	getTime = localtime(&timer);
	Income.day = getTime->tm_mday;
	Income.month = getTime->tm_mon+1;
	Income.year = getTime->tm_year+1900;
	
	return Income;	
}
	
