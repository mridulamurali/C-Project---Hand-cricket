#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>


// declaring function definitions
void batting(int computer_finalscore, int x);
void bowling(int user_finalscore, int y);
void scoresave();


/*
MAX_YR is used to decide the maximum year allowed to be used in the game
MIN_YR is used to decide the minimum year allowed to be used in the game
*/
#define MAX_YR  9999
#define MIN_YR  2020


// struct playerregister - user defined datatype to store player details and date
struct playerregister
{
    char p1[20];
    int dd;
    int mm;
    int yyyy;
    int batscore;
    float bowlavg;
} S1, S2;


// struct score - user defined datatype to store the performance of the player
struct score
{
    int bat;
    float bowl;
    char name[80];
} sc;


// Function to check leap year.
// Function returns 1 if leap year
int  IsLeapYear(int year)
{
    return (((year % 4 == 0) &&
             (year % 100 != 0)) ||
            (year % 400 == 0));
}


// Function to check whether given date is valid
// returns 1 if given date is valid.
int isValidDate(struct playerregister *validDate)
{

    //check range of year,month and day
    if (validDate->yyyy > MAX_YR ||
            validDate->yyyy < MIN_YR)
        return 0;
    if (validDate->mm < 1 || validDate->mm > 12)
        return 0;
    if (validDate->dd < 1 || validDate->dd > 31)
        return 0;

    //Handle feburary days in leap year
    if (validDate->mm == 2)
    {
        if (IsLeapYear(validDate->yyyy))
            return (validDate->dd <= 29);
        else
            return (validDate->dd <= 28);
    }

    //handle months which has only 30 days
    if (validDate->mm == 4 || validDate->mm == 6 ||
            validDate->mm == 9 || validDate->mm == 11)
        return (validDate->dd <= 30);

    return 1;
}


// The Toss function emulates the action of a coin toss, and consequently passes control according to the winner's choice
void Toss(int a,char str[])
{

    // srand - A library function used to produce a random number within a specific range. It also sets the seed to call rand()
    srand(time(NULL));


    int ch=(rand()%6)+1;

    printf("Computer choice:%d\n",ch);


    // if statement is used to add computer choice and user choice and checks if user has won
    if(((ch+a)%2==0 && strcmpi(str,"even")==0) || ((ch+a)%2!=0) && strcmpi(str,"odd")==0)
    {
        printf("YOU WON THE TOSS!\n");
        printf("Do you choose to\n1. Bat\n2. Bowl\n(Note:Type option number)\n");

        int decision;
        scanf("%d",&decision);

        while((decision>2) || (decision<1))
        {
            printf("Please choose a valid option:");
            scanf("%d",&decision);
        }
        if(decision==1)
        {
            int dummy=0;
            batting(dummy,0);
        }
        else
        {
            int dummy=0;
            bowling(dummy,0);
        }
    }
    else
    {
        srand(time(NULL));

        int cp=(rand()%2);
        if(cp==1)
        {
            printf("The computer chooses to bat!");
            int dummy=0;
            bowling(dummy,0);
        }
        else
        {
            printf("The computer chooses to bowl!");
            int dummy=0;
            batting(dummy,0);
        }
    }
}


/*
handles batting actions, by user or computer, and determines the result of the game as per game flow
int FLAG - control variable to detect / control the flow of the program and to determine whether the user is batting or bowling first
*/
void batting(int computer_finalscore, int FLAG)
{
    int user_runs, computer_bowls, user_score=0, a = 0;

    if(FLAG==1)
    {
        printf("\nTarget to beat - %d\n",computer_finalscore);
    }

    printf("\nYou are now batting");

    // a - variable used to run an infinite loop and to recognize the end of user batting
    while(a != 1)
    {
        printf("\nEnter a number between 1-6: ");
        scanf("%d",&user_runs);
        while((user_runs>6) || (user_runs<1))
        {
            printf("INVALID INPUT!!!\nPlease enter a valid number: ");
            scanf("%d",&user_runs);
        }
        srand(time(NULL));
        computer_bowls=(rand()%6)+1;
        printf("\nComputer's turns: %d", computer_bowls);
        if(user_runs==computer_bowls)
        {
            printf("\nYou are Out!!\nTotal runs scored = %d\n",user_score);
            a=1;
        }
        else if((user_runs!=computer_bowls) && (user_runs<7))
        {
            user_score=user_score+user_runs;
            printf("\nCurrent score = %d",user_score);
        }
        if((FLAG==1) && (user_score>computer_finalscore))
        {
            a = 1;
            printf("\nYOU WON!!!");
        }
    }
    S1.batscore = user_score;
    if (FLAG==1)
    {
        scoresave();
    }
    if ((a==1) && (FLAG==0))
    {
        printf("\nYour turn to bat is over");
        bowling(user_score,1);
    }

    else if ((FLAG==1) && (computer_finalscore>user_score))
    {
        printf("\nSORRY, YOU LOST");
    }

    else if ((computer_finalscore==user_score) && (FLAG==1))
    {
        printf("\nIT IS A DRAW!");
    }
}


/*
handles batting actions, by user or computer, and determines the result of the game as per game flow
int FLAG - control variable to detect /control the flow of program and to determine whether the user is batting or bowling first
*/
void bowling(int user_finalscore, int FLAG)
{
    int user_bowls, computer_runs, computer_score=0, a=0, ballcount=0;

    if(FLAG==1)
    {
        printf("\nScore to defend - %d\n",user_finalscore);
    }

    printf("\nYou are now bowling");

    // a - variable used to run an infinite loop and to recognize the end of user bowling
    while(a!=1)
    {
        printf("\nEnter a number between 1-6: ");
        scanf("%d",&user_bowls);


        if(user_bowls>6)
        {
            printf("INVALID INPUT!!!\nPlease enter the number again: ");
            scanf("%d",&user_bowls);
        }
        srand(time(NULL));
        computer_runs=(rand()%6)+1;

        if(user_bowls==computer_runs)
        {
            printf("\nComputer's turn: %d", computer_runs);
            printf("\nThe computer is Out!!!\nTotal runs scored = %d\n",computer_score);
            a=1;
            ballcount++;
        }
        else if(computer_runs!=user_bowls && computer_runs<7)
        {
            printf("\nComputer's turn: %d", computer_runs);
            computer_score=computer_score+computer_runs;

            ballcount++;

            printf("\nCurrent score = %d",computer_score);
        }
        if(FLAG==1 && computer_score>user_finalscore)
        {
            a = 1;
            printf("\nSORRY, YOU LOST");
        }
    }

    S1.bowlavg=(computer_score);
    S1.bowlavg=S1.bowlavg/(ballcount);

    if(FLAG==1)
    {
        scoresave();
    }

    if (FLAG==0)
    {
        printf("\nYour turn to bowl is over");
        batting(computer_score,1);
    }

    else if((computer_score<user_finalscore) && (FLAG==1))
    {
        printf("\nYOU WON!!!");
    }

    else if((computer_score==user_finalscore) && (FLAG==1))
    {
        printf("\n IT IS A DRAW!");
    }

}


/*
Function displays instructions to play the game if FLAG is 0
Function displays information about the game if FLAG is not 0
*/
void disp_instructions_and_about(int FLAG)
{
    FILE *fptr;

    if(FLAG==0)
    {
        fptr=fopen("Instructions.txt","r");
    }

    else
    {
        fptr=fopen("About.txt","r");
    }

    if (fptr == NULL)
    {
        printf("Cannot open file \n");
        return;
    }

    char ch = fgetc(fptr);
    while (ch != EOF)
    {
        printf ("%c", ch);
        ch = fgetc(fptr);
    }

    fclose(fptr);

}


// records player details and date in a binary file
void reg()
{
    FILE *fptr;

    fptr = fopen("register.bin","ab");
    printf("\nEnter Player Name: ");
    scanf("%s", &S1.p1);
    printf("\nEnter the date that the game is being played in DD/MM/YYYY format: ");
    scanf("%d/%d/%d", &S1.dd, &S1.mm, &S1.yyyy);

    // To check date validity
    int status = 0;
    status = isValidDate(&S1);

    while(status !=1)
    {
        printf("\n\nPlease enter a valid date in correct format!\n");
        scanf("%d/%d/%d", &S1.dd, &S1.mm, &S1.yyyy);
        status = isValidDate(&S1);
    }

    fwrite(&S1, sizeof(struct playerregister), 1, fptr);

    fclose(fptr);
}


// Function prints player details when called
void display()
{
    FILE *fptr;

    fptr = fopen("register.bin","rb");
    if (fptr == NULL)
    {
        printf("Sorry, no records found \n");
        return;
    }

    while(fread(&S1, sizeof(struct playerregister), 1, fptr))
    {
        printf("\nRecord from %d/%d/%d", S1.dd, S1.mm, S1.yyyy);
        printf("\nPlayer name: %s", S1.p1);
    }

    fclose(fptr);
}


// Function filters stored player records according to user choice
void filter()
{
    FILE *fptr;

    fptr = fopen("register.bin","rb");
    if (fptr == NULL)
    {
        printf("Sorry, no records found \n");
        return;
    }

    int ch, flag = 0;

    printf("Filter by name or date\n");
    printf("Enter \n1 - For Name\n2 - For date\n");
    scanf("%d", &ch);

    while((ch!=1) && (ch!=2))
    {
        printf("Choose a valid filter:");
        scanf("%d", &ch);
    }

    if(ch==1)
    {
        printf("Please enter Full name of player (case sensitive):\n");
        scanf("%s", &S2.p1);
        printf("\n%s", &S2.p1);
        while(fread(&S1, sizeof(struct playerregister), 1, fptr))
        {
            if(strcmp(S2.p1, S1.p1)==0)
            {
                printf("\nRecord from %d/%d/%d", S1.dd, S1.mm, S1.yyyy);
        printf("\nPlayer name: %s", S1.p1);
                flag=1;
            }
        }

        if(flag==0)
        {
            printf("\nSorry, Record not found");
        }

        fclose(fptr);
    }

    if(ch==2)
    {
        printf("Please enter date in format DD/MM/YYYY :\n");
        scanf("%d/%d/%d", &S2.dd, &S2.mm, &S2.yyyy);

        int status = 0;
        status = isValidDate(&S2);

        while(status !=1)
        {
            printf("\n\nPlease enter a valid date in correct format!\n");
            scanf("%d/%d/%d", &S2.dd, &S2.mm, &S2.yyyy);
            status = isValidDate(&S2);
        }

        while(fread(&S1, sizeof(struct playerregister), 1, fptr))
        {
            if((S2.dd== S1.dd) && (S2.mm == S1.mm) && (S2.yyyy == S1.yyyy))
            {
                printf("\nRecord from %d/%d/%d", S1.dd, S1.mm, S1.yyyy);
        printf("\nPlayer name: %s", S1.p1);
                flag=1;
            }

        }

        if(flag==0)
        {
            printf("\nSorry, Record not found");
        }

        fclose(fptr);
    }
}


// Function gets the Toss conditions and the input
int gameplay()
{
    char choice[10], check[10];
    printf("\nODD or EVEN? ");
    scanf("%s",&choice);

    strcpy(check, choice);
    for(int i = 0; choice[i]; i++)
    {
        check[i] = tolower(choice[i]);
    }

    while((strcmp(check,"odd")!=0) && (strcmp(check,"even")!=0))
    {
        printf("%s", choice);
        printf("\nPlease enter a valid option : ODD or EVEN\n");
        scanf("%s", &choice);
        strcpy(check, choice);
        for(int i = 0; choice[i]; i++)
        {
            check[i] = tolower(choice[i]);
        }
    }

    int a;
    printf("Enter the number for toss(1-6): ");
    scanf("%d",&a);

    while((a>6) || (a<1))
    {
        printf("Please enter a valid number:");
        scanf("%d",&a);
    }
    Toss(a,choice);
}


// Function used to save the score of players in a different file for ease of access
void scoresave()
{
    FILE *fptr;
    fptr = fopen("scorelist.dat","ab");
    sc.bat=S1.batscore;
    sc.bowl=S1.bowlavg;
    strcpy(sc.name, S1.p1);
    fwrite(&sc, sizeof(struct score), 1, fptr);
    fprintf(fptr,"%d\n",sc.bat);
    fprintf(fptr,"%f\n",sc.bowl);
    fclose(fptr);

}

// Function displays the scores of all players
void scoredisplay()
{
    FILE *fptr;

    fptr = fopen("scorelist.dat","rb");
    if (fptr == NULL)
    {
        printf("Sorry, no records found\n");
        exit(0);
    }

    while(fread(&sc, sizeof(struct score), 1, fptr))
    {
        printf("\nplayer name: %s", sc.name);
        printf("\nbatting score: %d", sc.bat);
        printf("\nbowling average: %.2f", sc.bowl);
    }

    fclose(fptr);
}


int  main()
{
    printf("WELCOME TO HAND-CRICKET");
    int menuchoice;
    // The Main Menu of the Game
    do
    {
        printf("\n\nCHOOSE YOUR OPTIONS:\n");
        printf("0. About the game\n");
        printf("1. Instructions\n");
        printf("2. Start Game\n");
        printf("3. Filter record by date/Name\n");
        printf("4. Player records\n");
        printf("5. Score records\n");
        printf("6. Exit\n");
        printf("CHOOSE YOUR OPTION\n");
        scanf("%d", &menuchoice);
        while((menuchoice<0) || (menuchoice>6))
        {
            printf("\nPlease choose a valid option from the given choices:");
            scanf("%d", &menuchoice);

        }
        switch(menuchoice)
        {
        case 0:
            disp_instructions_and_about(1);
            getch();
            break;
        case 1:
            disp_instructions_and_about(0);
            getch();
            break;
        case 2:
            reg();
            gameplay();
            getch();
            break;
        case 3:
            filter();
            getch();
            break;
        case 4:
            display();
            break;
        case 5:
            scoredisplay();
            break;
        case 6:
            exit(0);
            break;
        }
    }
    while((menuchoice>=0) && (menuchoice<=6));
}

