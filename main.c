#include "rks.h"

int main() 
{
	FILE* mainStorage;
	
	OPENTOREAD;
	
	if(!mainStorage) // якщо база відсутня
	{
		mainStorage = InitialAdd(mainStorage);
		
		if(!mainStorage) 
		{
			puts("NO CASES ADDED");
			return;	
		}
	}
	
	CLOSE;
	
	int incorrectChoiceMain = 0;

	while(1)   // ГОЛОВНЕ МЕНЮ 
	{
		char mainChoice;
		int totalCaseNumber = 0;
		
		OPENTOREAD;
		PCase trash = (PCase) calloc(1, sizeof(struct Case));
		while(fread(trash, sizeof(struct Case), 1, mainStorage)) totalCaseNumber++;
		CLOSE;

		ShowMainMenu(incorrectChoiceMain, totalCaseNumber);

		incorrectChoiceMain = 0;
		
		fflush(stdin);
		scanf("%c", &mainChoice);
		
		switch(mainChoice)
		{
			case '1': AddCase(); break;
			case '2': FindCase(); break;
			case '3': EditJudgeList(); break;
			case '9': showManual(); break;
			case '0': return;
			default: system("cls"); incorrectChoiceMain = 1; 
		}
	}
	
	return 0;
}
	
