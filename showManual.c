#include "rks.h"

void showManual()
{
	system("cls");
	puts("                     <<<=====RECORD KEEPING SYSTEM=====>>>\n\n\n");
	printf("                    <<<<<MANUAL>>>>>\n");
			
		printf("INTRODUCTION:\n");
		printf("   Any choice in the program (exept separately mentioned) should be made by \nentering appropriate DIGIT (settled LEFT from\nthe menu articles) or string\nand pressing ENTER.\n");
		printf("   You can also change your choice using BACKSPACE (before ENTER).\n\n");
		printf("HOW TO ADD CASE:\n");
		printf("   Follow the information on the menu and enter appropriate information \naccordingly to choosen case category.\n");
		printf("   NOTE, that number of case (structure: court index/number/sequense number\n(in approprate year)/year) is assigning automatically as well as\na specific judge.\n");
		printf("   Judge is being chosen be the randomiser acordingly to his \nactive/inactivestatus and specialization.\n");
		printf("   You are not able to change judge in the case unless he/she is inactive \nor deleted from the database.\n");
		printf("   Income date is processing by the system and can not be changed, any other \ninformaion can be replaced!\n");
		printf("   KEEP IN MIND that you can not delete the court case after it is loaded in \nthe system.\n\n");
		printf("JUDGE INFO MANIPULATION:\n");
		printf("   Choose edit judge option and follow the information on the menu.\n");
		printf("   Program disactivates judge automatically in obedience to entered inactive \nperiod and system time.\n");
		
		puts("PRESS ANY KEY TO PROCEED");
		
		getch();
}
