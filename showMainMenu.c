#include "rks.h"

void ShowMainMenu(int incorrectChoiceMain, int totalCaseNumber)
{
	system("cls");
	puts("                     <<<=====RECORD KEEPING SYSTEM=====>>>\n\n");
	printf("\n                                                      total case number - %d", totalCaseNumber);
	printf("\n                                                      ______________________\n");
	puts("ENTER DIGIT TO CHOOSE OPTION\n");
	printf("1 - Add case\n");
	puts("---------------");
	printf("2 - Find and edit case\n");
	puts("---------------");
	printf("3 - Edit judge list\n");
	puts("---------------");
	printf("9 - Manual\n");
	puts("---------------");
	printf("0 - Exit\n");
	puts("---------------");
	if(incorrectChoiceMain == 1) printf("\nERROR, choose digit from the list\n");
}

void ShowInitialMenu(int incorrectInitAdd)
{
		system("cls");
		puts("                     <<<=====RECORD KEEPING SYSTEM=====>>>\n\n\n");
		puts("PRESS DIGIT TO CHOOSE OPTION\n");
		printf("Storage is empty. Add first case? \n");
		printf("\n");
		printf("1 - yes \n");
		printf("2 - no (exit) \n");
		
		if(incorrectInitAdd == 1) printf("\nERROR, choose digit from the list\n");
}

void ShowFindMenu(int* NotFound, int* incorrectFindChoice)
{
			system("cls");
			puts("                     <<<=====RECORD KEEPING SYSTEM=====>>>\n\n\n");
			puts("ENTER DIGIT TO CHOOSE OPTION\n");

			puts("1 - find by number");
			puts("---------------");
			puts("2 - find by participant");
			puts("---------------");
			puts("3 - find by income date");
			puts("---------------");
			puts("4 - sort all cases");
			puts("---------------");
			puts("0 - back");
			puts("---------------");
			
			if(*NotFound == 1) puts("\nNO CASES FOUND\n");
			if(*incorrectFindChoice == 1) puts("\nERROR, choose digit from the list\n");
}

void ShowSortMenu()
{
	system("cls");	
	puts("                     <<<=====RECORD KEEPING SYSTEM=====>>>\n\n\n");
	puts("ENTER DIGIT TO CHOOSE OPTION\n");	
	puts("1 - sort by number");
	puts("---------------");
	puts("2 - sort by participant");
	puts("---------------");
	puts("3 - sort by category");
	puts("---------------");
	puts("4 - sort judge");
	puts("---------------");
	puts("0 - back");
	puts("---------------");
}

void ShowJudgeMenu (int judgeMenuError)
{
		system("cls");
		puts("                     <<<=====RECORD KEEPING SYSTEM=====>>>\n\n\n");
		puts("ENTER DIGIT TO CHOOSE OPTION\n");
		puts("1 - Add new judge");
		puts("---------------");
		puts("2 - Set inactivity period");
		puts("---------------");
		puts("3 - Delete judge");
		puts("---------------");
		puts("0 - Back");
		puts("---------------");
						
		if(judgeMenuError == 1) printf("\nERROR, choose digit from the list\n");
}

void ShowSortByParticipantMenu(int incorrectChoice)
{
	system("cls");
	puts("                     <<<=====RECORD KEEPING SYSTEM=====>>>\n\n\n");
	
	puts("ENTER DIGIT TO CHOOSE OPTION\n");
	puts("Choose paricipant for alphabet sort");
	puts("1 - accused");
	puts("2 - victim");
	puts("3 - plaintiff");
	puts("4 - defendant");
	puts("5 - investigator");
	puts("6 - violator");
	puts("7 - exit");
				
	if(incorrectChoice == 1) printf("\nERROR, choose digit from the list\n");
}

ShowChooseCategoryMenu(int incorrectCategory)
{
	printf("Choose case category: \n\n");
	printf("1 - Criminal \n");
	puts("---------------");
	printf("2 - Civil \n");
	puts("---------------");
	printf("3 - Investigator request\n");
	puts("---------------");
	printf("4 - Administrative offense \n");
	puts("---------------");
	printf("0 - Back\n");
	puts("---------------");
	if(incorrectCategory == 1) puts("\nERROR, choose correct category: \n");
}
