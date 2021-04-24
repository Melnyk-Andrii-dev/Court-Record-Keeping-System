#ifndef RKS_H
#define RKS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <malloc.h>
#include "rks.h"

#define YES '1'
#define NO '2'

#define OPENTOREAD mainStorage = fopen("mainStorage.dat", "rb+")
#define CLOSE fclose(mainStorage)

enum Category
{
	CRIMINAL = 1, CIVIL, INVESTIGATORREQUEST, ADMINISTRATIVEOFFENSE
};

enum ParticipantChoice
{
	ACCUSSED = 1, VICTIM, PLAINTIFF, DEFENDANT, INVESTIGATOR, VIOLATOR
};

struct DateInfo 
{
	int year;
	int month;
	int day;
};

struct judgeInfo
{
	char name[50];
	int spec;
	int status;
	struct DateInfo InActivePeriodStart;
	struct DateInfo InActivePeriodEnd;
};

struct CN
{
	int index;
	int number;
	int year;
};

struct Case
{
	char CNnumber[20];
	
	char category[50];
	char jadge[50];
	char accussed[200];
	char victim[200];
	char plaintiff[200];
	char defendant[200];
	char investigator[50];
	char applicant[50];
	char violator[50];
	char matter[200];
	
	char processStage[50];
	struct DateInfo dateOfIncome;
	char processDuration;
};
typedef struct Case* PCase;

struct Node
{
	char CNnumber[20];
	
	char Kcategory[50];
	char Kjadge[50];
	char Kaccussed[200];
	char Kvictim[200];
	char Kplaintiff[200];
	char Kdefendant[200];
	char Kinvestigator[50];
	char Kapplicant[50];
	char Kviolator[50];
	char Kmatter[200];
	
	char KprocessStage[50];
	struct DateInfo KdateOfIncome;
	char KprocessDuration;
	
	struct Node* left;
	struct Node* right;
};
typedef struct Node* PNode;


PCase EditCase(PCase sortmas);
FILE* InitialAdd(FILE* mainStorage);
int AddCase();
char* CaseAllocation(int category);
char* CaseNumberAssign(PCase NewCase);
struct DateInfo IncomeDateAssign();


void FindCase();
PCase FindByIncomeDate();
PCase SortByCategory();
PCase SortBy(char answer);
void ShowSorted(PCase sortmas, int foundCases);
void AddToTreeParticipant(PNode* Tree, PCase temp, char answer2);
void AddToTreeJudge(PNode* Tree, PCase temp);
void AddToTreeCategory(PNode* Tree, PCase temp);
void SortInTempFileLKP(PNode Tree, FILE* mainStorage);


PCase ChangeCaseInfo(PCase change, int category);
int ChangeCategory(PCase change);
void ClearJudge(PCase change);
int ChangeFirstLine(PCase change);
PCase ReplaceChangedInSorted(PCase sortmas, PCase change);
int ChangeSecondLine(PCase change);
int ChangeThirdLine(PCase change);
PCase GetNewCaseInfo(PCase NewCase, int category);
int GetCategory(int* incorrectCategory);


void EditJudgeList();
void AddJudge();
char* GetDay(int* day, int* month, int* year);
int DateIsCorrect(int day, int month, int year);
int updateStatus();
void SetPeriod();
void DeleteJudge();
void ShowInactivePeriod (struct judgeInfo* list);
int PeriodIsCorrect(int Fday, int Fmonth, int Fyear, int Lday, int Lmonth, int Lyear);


void ShowCaseToEdit(PCase temp);
void showManual();
void ShowMainMenu(int incorrectChoiceMain, int totalCaseNumber);
void ShowInitialMenu(int incorrectInitAdd);
void ShowFindMenu(int* NotFound, int* incorrectFindChoice);
void ShowSortMenu();
void ShowJudgeMenu (int judgeMenuError);
void ShowSortByParticipantMenu(int incorrectChoice);
void ShowChooseCategoryMenu(int incorrectCategory);


#endif

