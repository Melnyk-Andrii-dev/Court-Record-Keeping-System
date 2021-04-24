#include "rks.h"

PCase SortBy(char sortChoice)
{
	
	FILE* mainStorage;
	OPENTOREAD;
	PCase temp = (PCase) calloc(1, sizeof(struct Case));
	PNode Tree = NULL;
	PCase res = (PCase) calloc(1, sizeof(struct Case));
	int countCase = 0;
	char participantChoice;
	
	switch(sortChoice)
	{
		case '2': // меню вибору при сортуванні за учасником
			while(1)
			{
				int incorrectChoice;
				
				ShowSortByParticipantMenu(incorrectChoice);
				
				incorrectChoice = 0;
				fflush(stdin);
			    scanf("%c", &participantChoice);
			    participantChoice = participantChoice - '0';
				if(participantChoice == 7) return NULL;
				if(participantChoice < ACCUSSED || participantChoice > 7)
				{
					incorrectChoice = 1;
				} 
				else break;
			}
			while(fread(temp, sizeof(struct Case), 1, mainStorage)) // виконання сортування за учасником
			{
				AddToTreeParticipant(&Tree, temp, participantChoice);
			}
			break;
		case '3': // виконання сортування за категорією
			while(fread(temp, sizeof(struct Case), 1, mainStorage))
			{
				AddToTreeCategory(&Tree, temp);
			}
			break;
		case '4':  // сортування за суддею
			while(fread(temp, sizeof(struct Case), 1, mainStorage))
			{
				AddToTreeJudge(&Tree, temp);
			}
			break;	
	}
	

	
	CLOSE;
	
	FILE* tempStorage = fopen("temp.dat", "wb");
	SortInTempFileLKP(Tree, tempStorage);
	fclose(tempStorage);
	
	tempStorage = fopen("temp.dat", "rb");
	
	if(!tempStorage) puts("ERROR");
	
	while(fread(temp, sizeof(struct Case), 1, tempStorage))
	{
		fseek(tempStorage, sizeof(struct Node*)*2, 1);
		res[countCase] = temp[0];
		countCase++;
		res = (PCase)realloc(res, (countCase+1)*sizeof(struct Case));
	}
	res = (PCase)realloc(res, _msize(res) - sizeof(struct Case));
	fclose(tempStorage);
	return res;
	
	
}

void AddToTreeParticipant(PNode* Tree, PCase temp, char participantChoice)
{

	if(!*Tree)
	{ // сортуванння відповідно довибору (0 на початку учасника - ознака пустого (зміненого) поля
		if(participantChoice == ACCUSSED && temp->accussed[0] != 0 || participantChoice == VICTIM && temp->accussed[0] != 0 || participantChoice == PLAINTIFF && temp->plaintiff[0] != 0
		||  participantChoice == DEFENDANT && temp->plaintiff[0] != 0 || participantChoice == INVESTIGATOR && temp->investigator[0] != 0 || participantChoice == VIOLATOR && temp->violator[0] != 0)
		{	
			*Tree = (PNode) calloc(1, sizeof(struct Node));
			strcpy((*Tree)->Kcategory, temp->category);
			strcpy((*Tree)->CNnumber, temp->CNnumber);
			(*Tree)->KdateOfIncome.day = temp->dateOfIncome.day;
			(*Tree)->KdateOfIncome.month = temp->dateOfIncome.month;
			(*Tree)->KdateOfIncome.year = temp->dateOfIncome.year;
			strcpy((*Tree)->Kaccussed, temp->accussed);
			strcpy((*Tree)->Kdefendant, temp->defendant);
			strcpy((*Tree)->Kinvestigator, temp->investigator);
			strcpy((*Tree)->Kjadge, temp->jadge);
			strcpy((*Tree)->Kmatter, temp->matter);
			strcpy((*Tree)->Kplaintiff, temp->plaintiff);
			strcpy((*Tree)->Kvictim, temp->victim);
			strcpy((*Tree)->Kviolator, temp->violator);
			strcpy((*Tree)->Kapplicant, temp->applicant);
			(*Tree)->left = NULL;
			(*Tree)->right = NULL;
		}
	}
	else
	{

		if(participantChoice == ACCUSSED && temp->accussed[0] != 0)
		{
			
			if(strcmp( (*Tree)->Kaccussed, temp->accussed) > 0)
			{
				AddToTreeParticipant(&(*Tree)->left, temp, participantChoice); 
			}
			else
			{
				AddToTreeParticipant(&(*Tree)->right, temp, participantChoice);
			}	
		}
		if(participantChoice == VICTIM && temp->accussed[0] != 0)
		{
			
			if(strcmp( (*Tree)->Kvictim, temp->victim) > 0)
			{
				AddToTreeParticipant(&(*Tree)->left, temp, participantChoice); 
			}
			else
			{
				AddToTreeParticipant(&(*Tree)->right, temp, participantChoice);
			}
		}
		if(participantChoice == PLAINTIFF && temp->plaintiff[0] != 0)
		{
			
			if(strcmp( (*Tree)->Kplaintiff, temp->plaintiff) > 0)
			{
				AddToTreeParticipant(&(*Tree)->left, temp, participantChoice); 
			}
			else
			{
				AddToTreeParticipant(&(*Tree)->right, temp, participantChoice);
			}
			
		}
		if(participantChoice == DEFENDANT && temp->plaintiff[0] != 0)
		{
			
			if(strcmp( (*Tree)->Kdefendant, temp->defendant) > 0)
			{
				AddToTreeParticipant(&(*Tree)->left, temp, participantChoice); 
			}
			else
			{
				AddToTreeParticipant(&(*Tree)->right, temp, participantChoice);
			}
			
		}
		if(participantChoice == INVESTIGATOR && temp->investigator[0] != 0)
		{
			
			if(strcmp( (*Tree)->Kinvestigator, temp->investigator) > 0)
			{
				AddToTreeParticipant(&(*Tree)->left, temp, participantChoice); 
			}
			else
			{
				AddToTreeParticipant(&(*Tree)->right, temp, participantChoice);
			}
			
		}
		if(participantChoice == VIOLATOR && temp->violator[0] != 0)
		{
			
			if(strcmp( (*Tree)->Kviolator, temp->violator) > 0)
			{
				AddToTreeParticipant(&(*Tree)->left, temp, participantChoice); 
			}
			else
			{
				AddToTreeParticipant(&(*Tree)->right, temp, participantChoice);
			}
		}	
	}
}



void AddToTreeJudge(PNode* Tree, PCase temp)
{
	
	if(!*Tree)
	{
			(*Tree) = (PNode) calloc(1, sizeof(struct Node));
			strcpy((*Tree)->CNnumber, temp->CNnumber);
			strcpy((*Tree)->Kaccussed, temp->accussed);
			strcpy((*Tree)->Kcategory, temp->category);
			(*Tree)->KdateOfIncome.day = temp->dateOfIncome.day;
			(*Tree)->KdateOfIncome.month = temp->dateOfIncome.month;
			(*Tree)->KdateOfIncome.year = temp->dateOfIncome.year;
			strcpy((*Tree)->Kdefendant, temp->defendant);
			strcpy((*Tree)->Kinvestigator, temp->investigator);
			strcpy((*Tree)->Kjadge, temp->jadge);
			strcpy((*Tree)->Kmatter, temp->matter);
			strcpy((*Tree)->Kplaintiff, temp->plaintiff);
			strcpy((*Tree)->Kvictim, temp->victim);
			strcpy((*Tree)->Kviolator, temp->violator);
			strcpy((*Tree)->Kapplicant, temp->applicant);
			(*Tree)->left = NULL;
			(*Tree)->right = NULL;
	}
	else
	{
		if(strcmp((*Tree)->Kjadge, temp->jadge) > 0)
		{
			AddToTreeJudge(&(*Tree)->left, temp);
		}
		else
		{
			AddToTreeJudge(&(*Tree)->right, temp);
		}
		
	}
}

void AddToTreeCategory(PNode* Tree, PCase temp)
{
	
	if(!*Tree)
	{
			(*Tree) = (PNode) calloc(1, sizeof(struct Node));
			strcpy((*Tree)->CNnumber, temp->CNnumber);
			strcpy((*Tree)->Kaccussed, temp->accussed);
			strcpy((*Tree)->Kcategory, temp->category);
			(*Tree)->KdateOfIncome.day = temp->dateOfIncome.day;
			(*Tree)->KdateOfIncome.month = temp->dateOfIncome.month;
			(*Tree)->KdateOfIncome.year = temp->dateOfIncome.year;
			strcpy((*Tree)->Kdefendant, temp->defendant);
			strcpy((*Tree)->Kinvestigator, temp->investigator);
			strcpy((*Tree)->Kjadge, temp->jadge);
			strcpy((*Tree)->Kmatter, temp->matter);
			strcpy((*Tree)->Kplaintiff, temp->plaintiff);
			strcpy((*Tree)->Kvictim, temp->victim);
			strcpy((*Tree)->Kviolator, temp->violator);
			strcpy((*Tree)->Kapplicant, temp->applicant);
			(*Tree)->left = NULL;
			(*Tree)->right = NULL;
	}
	else
	{
		if(strcmp((*Tree)->Kcategory, temp->category) > 0)
		{
			AddToTreeCategory(&(*Tree)->left, temp);
		}
		else
		{
			AddToTreeCategory(&(*Tree)->right, temp);
		}
		
	}
}

void SortInTempFileLKP(PNode Tree, FILE* mainStorage) // запис відсортованого дерева у тимчасовий файл
{
	if (!Tree) return; 
	
	SortInTempFileLKP(Tree->left, mainStorage); 
	
	fwrite(Tree, sizeof(struct Node), 1, mainStorage);

	SortInTempFileLKP(Tree->right, mainStorage); 
}

void ShowSorted(PCase sortmas, int foundCases) // виведення відсортованих справ
{
	int countSorted;
	
	for(countSorted=0; countSorted<=foundCases; countSorted++)
	{
		if(strcmp((sortmas+countSorted)->category, "Criminal") == 0) 
		{
			printf("Case %d\n", countSorted+1);	
			printf("\n");
			printf("Case number: %s \n", (sortmas+countSorted)->CNnumber);
			printf("Category: %s \n", (sortmas+countSorted)->category);
			printf("Jadge: %s \n", (sortmas+countSorted)->jadge);
			printf("Accused: %s \n", (sortmas+countSorted)->accussed);
			printf("Victim: %s \n", (sortmas+countSorted)->victim);
			printf("matter: %s \n", (sortmas+countSorted)->matter);
		}
		else if(strcmp((sortmas+countSorted)->category, "Civil") == 0)
		{
			printf("Case %d\n", countSorted+1);
			printf("\n");
			printf("Case number: %s \n", (sortmas+countSorted)->CNnumber);
			printf("Category: %s \n", (sortmas+countSorted)->category);
			printf("Jadge: %s \n", (sortmas+countSorted)->jadge);
			printf("Plaintiff: %s \n", (sortmas+countSorted)->plaintiff);
			printf("Defendant: %s \n", (sortmas+countSorted)->defendant);
			printf("matter: %s \n", (sortmas+countSorted)->matter);
		}
		else if(strcmp((sortmas+countSorted)->category, "Investigator request") == 0)
		{
			printf("Case %d\n", countSorted+1);
			printf("\n");
			printf("Case number: %s \n", (sortmas+countSorted)->CNnumber);
			printf("Category: %s \n", (sortmas+countSorted)->category);
			printf("Jadge: %s \n", (sortmas+countSorted)->jadge);
			printf("Investigator: %s \n", (sortmas+countSorted)->investigator);
			printf("matter: %s \n", (sortmas+countSorted)->matter);
		}
		else if(strcmp((sortmas+countSorted)->category, "Administrative offense") == 0)
		{
			printf("Case %d\n", countSorted+1);
			printf("\n");
			printf("Case number: %s \n", (sortmas+countSorted)->CNnumber);
			printf("Category: %s \n", (sortmas+countSorted)->category);
			printf("Jadge: %s \n", (sortmas+countSorted)->jadge);
			printf("Violator: %s \n", (sortmas+countSorted)->violator);
			printf("matter: %s \n", (sortmas+countSorted)->matter);
		}
		
		
		if((sortmas+countSorted)->dateOfIncome.day<10 && (sortmas+countSorted)->dateOfIncome.month<10)
		{
			printf("Date of income: 0%d.0%d.%d \n", (sortmas+countSorted)->dateOfIncome.day, (sortmas+countSorted)->dateOfIncome.month, (sortmas+countSorted)->dateOfIncome.year);
		}
		else if( (sortmas+countSorted)->dateOfIncome.day>=10 && (sortmas+countSorted)->dateOfIncome.month<10 )
		{
			printf("Date of income: %d.0%d.%d \n", (sortmas+countSorted)->dateOfIncome.day, (sortmas+countSorted)->dateOfIncome.month, (sortmas+countSorted)->dateOfIncome.year);
		}
		else if( (sortmas+countSorted)->dateOfIncome.day<10 && (sortmas+countSorted)->dateOfIncome.month>=10 )
		{
			printf("Date of income: 0%d.%d.%d \n", (sortmas+countSorted)->dateOfIncome.day, (sortmas+countSorted)->dateOfIncome.month, (sortmas+countSorted)->dateOfIncome.year);
		}
		else if( (sortmas+countSorted)->dateOfIncome.day>=10 && (sortmas+countSorted)->dateOfIncome.month>=10 )
		{
			printf("Date of income: %d.%d.%d \n", (sortmas+countSorted)->dateOfIncome.day, (sortmas+countSorted)->dateOfIncome.month, (sortmas+countSorted)->dateOfIncome.year);
		}
		printf("\n");
	
	
	}

}

void ShowCaseToEdit(PCase temp) // виведення справи при зміні
{

	if(strcmp(temp->category, "Criminal") == 0) 
	{	
		printf("\n");
		printf("Case number: %s \n", temp->CNnumber);
		printf("1.   Category: %s \n", temp->category);
		printf("2.   Jadge: %s \n", temp->jadge);
		printf("3.   Accused: %s \n", temp->accussed);
		printf("4.   Victim: %s \n", temp->victim);
		printf("5.   matter: %s \n", temp->matter);
	}
	else if(strcmp(temp->category, "Civil") == 0)
	{
		printf("\n");
		printf("Case number: %s \n", temp->CNnumber);
		printf("1.   Category: %s \n", temp->category);
		printf("2.   Jadge: %s \n", temp->jadge);
		printf("3.   Plaintiff: %s \n", temp->plaintiff);
		printf("4.   Defendant: %s \n", temp->defendant);
		printf("5.   matter: %s \n", temp->matter);
	}
	else if(strcmp(temp->category, "Investigator request") == 0)
	{
		printf("\n");
		printf("Case number: %s \n", temp->CNnumber);
		printf("1.   Category: %s \n", temp->category);
		printf("2.   Jadge: %s \n", temp->jadge);
		printf("3.   Investigator: %s \n", temp->investigator);
		printf("4.   matter: %s \n", temp->matter);
	}
	else if(strcmp(temp->category, "Administrative offense") == 0)
	{
		printf("\n");
		printf("Case number: %s \n", temp->CNnumber);
		printf("1.   Category: %s \n", temp->category);
		printf("2.   Jadge: %s \n", temp->jadge);
		printf("3.   Violator: %s \n", temp->violator);
		printf("4.   matter: %s \n", temp->matter);
	}   
	
	if(temp->dateOfIncome.day<10 && temp->dateOfIncome.month<10)
	{
		printf("Date of income: 0%d.0%d.%d \n", temp->dateOfIncome.day, temp->dateOfIncome.month, temp->dateOfIncome.year);
	}
	else if( temp->dateOfIncome.day>=10 && temp->dateOfIncome.month<10 )
	{
		printf("Date of income: %d.0%d.%d \n", temp->dateOfIncome.day, temp->dateOfIncome.month, temp->dateOfIncome.year);
	}
	else if( temp->dateOfIncome.day<10 && temp->dateOfIncome.month>=10 )
	{
		printf("Date of income: 0%d.%d.%d \n", temp->dateOfIncome.day, temp->dateOfIncome.month, temp->dateOfIncome.year);
	}
	else if( temp->dateOfIncome.day>=10 && temp->dateOfIncome.month>=10 )
	{
		printf("Date of income: %d.%d.%d \n", temp->dateOfIncome.day, temp->dateOfIncome.month, temp->dateOfIncome.year);
	}
	printf("\n");              					
}
