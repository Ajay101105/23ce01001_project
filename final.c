#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int i;
struct bank
{
    int acno;
    char name[20];
    char pass[10];
    char qns[30];
    char ans[30];
    int bal;
    char status;
    char type;
};
struct transaction

{
    int acno;
    char trtype; // c for credit (deposit) d for debit(withdraw)
    int amt;
};
void createAccount()
{
    system("cls");
    struct bank b1;
    FILE *p;
    p = fopen("ddaatt", "ab");
    if (p == NULL)
    {
        printf("\nSomething Went Wrong!!");
        getch();
        return;
    }
    else
    {
        fseek(p, 0, SEEK_END);
        int po = ftell(p);
        int num = po / sizeof(b1);

        b1.acno = num + 1; // new acno is +1
        b1.status = 'a';
        printf("\nEnter Your Name: ");
        scanf("%s", b1.name);
        printf("\nEnter Balance: ");
        scanf("%d", &b1.bal);
        printf("\nEnter the Account Type(Saving/ Current): ");
        fflush(stdin);
        scanf("%c", &b1.type);
        printf("\nEnter Password: ");
        getPassword(b1.pass);

        printf("\nEnter Your Recover Question: ");
        fflush(stdin);
        gets(b1.qns);
        printf("\nEnter the Answer: ");
        fflush(stdin);
        gets(b1.ans);
        fwrite(&b1, sizeof(b1), 1, p); // b1 represents a single account that's why we used 1
        fclose(p);
        printf("\nAccount %d is created Succesfully", b1.acno);
    }
}
void clearScreen()
{
    system("cls"); // For Windows
}
void getPassword(char *password)
{
    int i = 0;
    char ch;
    while ((ch = getch()) != '\r' && i < 9)
    {
        if (ch == '\b' && i > 0)
        {
            printf("\b \b");
            i--;
        }
        else if (ch != '\b')
        {
            password[i++] = ch;
            printf("*");
        }
    }
    password[i] = '\0';
}
void changeName()
{
    system("cls");
    struct bank b1;
    FILE *p;
    int amt;
    p = fopen("ddaatt", "rb+");
    if (p == NULL)
    {
        printf("\nSomething Went Wrong!!!");
        getch();
        return;
    }
    else
    {
        fseek(p, 0, SEEK_END); // this moves the file pointer to the end of the line
        int po = ftell(p);     // this function gets the current position of the file pointer,which effectively gives the size of the file
        int num = po / sizeof(b1);

        int n;
        printf("\nEnter the Account Number: ");
        scanf("%d", &n);

        if (n > num)
        {
            printf("\nInvalid Account Number. ");
            getch();
            return;
        }
        else
        {
            int pos = (n - 1) * sizeof(b1);
            fseek(p, pos, SEEK_SET);
            fread(&b1, sizeof(b1), 1, p);
            char nam[10];
            char opas[10];
            printf("\nEnter Your Password: ");
            getPassword(opas);

            if (strcmp(b1.pass, opas) == 0)
            {

                if (b1.status == 'a')
                {
                    printf("\nEnter New Name: ");
                    scanf("%s", nam);
                    strcpy(b1.name, nam);
                    fseek(p, pos, SEEK_SET);
                    fwrite(&b1, sizeof(b1), 1, p);
                    printf("\nYour Name is Changed Succesfully");
                    fclose(p);
                }
            }
            else
            {
                printf("\nPassword Do Not Match");
            }
        }
    }
}
void changePass()
{
    system("cls");
    struct bank b1;
    FILE *p;

    p = fopen("ddaatt", "rb+");
    if (p == NULL)
    {
        printf("\nSomething Went Wrong!!");
        getch();
        return;
    }
    else
    {
        fseek(p, 0, SEEK_END);
        int po = ftell(p);
        int num = po / sizeof(b1);

        int n;
        printf("\nEnter the Account Number: ");
        scanf("%d", &n);

        if (n > num)
        {
            printf("\nInvalid Account Number!!!");
            getch();
            return;
        }
        else
        {

            int pos = (n - 1) * sizeof(b1);
            fseek(p, pos, SEEK_SET);
            fread(&b1, sizeof(b1), 1, p);

            char opas[10];
            printf("\nEnter Your Password: ");
            getPassword(opas);

            if (strcmp(b1.pass, opas) == 0)
            {

                if (b1.status == 'a')
                {
                    char pas[10];
                    printf("\nEnter the New Password: ");
                    getPassword(pas);
                    strcpy(b1.pass, pas);
                    fseek(p, pos, SEEK_SET);
                    fwrite(&b1, sizeof(b1), 1, p);
                    printf("\nPassword is Changed Successfully");
                    fclose(p);
                }
            }
            else
            {
                printf("\nPassword Do not Match!!");
            }
        }
    }
}
void changeType()
{
    system("cls");
    struct bank b1;
    FILE *p;
    int amt;
    p = fopen("ddaatt", "rb+");
    if (p == NULL)
    {
        printf("\nSomething Went Wrong!!");
        getch();
        return;
    }
    else
    {
        fseek(p, 0, SEEK_END);
        int po = ftell(p);
        int num = po / sizeof(b1);

        int n;
        printf("\nEnter the Account Number: ");
        scanf("%d", &n);

        if (n > num)
        {
            printf("\nInvalid Account Number");
            getch();
            return;
        }
        else
        {
            int pos = (n - 1) * sizeof(b1);
            fseek(p, pos, SEEK_SET);
            fread(&b1, sizeof(b1), 1, p);
            char nam[10];
            char opas[10];
            printf("\nEnter Your Password: ");
            getPassword(opas);
            if (strcmp(b1.pass, opas) == 0)
            {

                if (b1.status == 'a')
                {
                    if (b1.type == 's')
                        b1.type = 'c';
                    else
                        b1.type = 's';
                    fseek(p, pos, SEEK_SET);
                    fwrite(&b1, sizeof(b1), 1, p);
                    printf("\nYour Account Type is changed Successfully");
                    fclose(p);
                }
            }
            else
            {
                printf("\nPassword Do not Match!!");
            }
        }
    }
}
void showDetails()
{
    system("cls");
    struct bank b1;

    FILE *p;
    p = fopen("ddaatt", "rb");
    if (p == NULL)
    {
        printf("\nSomething Went Wrong!!!");
        getch();
        return;
    }
    else
    {
        fseek(p, 0, SEEK_END);
        int po = ftell(p);
        int num = po / sizeof(b1);

        int n;
        printf("\nEnter the Account Number: ");
        scanf("%d", &n);

        if (n > num)
        {
            printf("\nInvalid Account Number!!");
            getch();
            return;
        }
        else
        {
            char passs[10];

            printf("\nEnter Your Password: ");
            getPassword(passs);

            int pos = (n - 1) * sizeof(b1);
            fseek(p, pos, SEEK_SET);
            fread(&b1, sizeof(b1), 1, p);
            if (strcmp(b1.pass, passs) == 0)
            {
                if (b1.status == 'a')
                {
                    printf("\nAccount Number= %d \n Name= %s \n Balance = %d \n Type = %c \n Recover Question = %s \n Answer = %s \n", b1.acno, b1.name, b1.bal, b1.type, b1.qns, b1.ans);
                }
                else
                {
                    printf("\nYour Account is Suspended!!! Please Contact the Bank");
                    getch();
                    return;
                }
            }
            else
            {
                printf("\nPassword Do Not Match");
            }
        }
    }
}
void depositeAccount()
{
    system("cls");
    struct bank b1;
    FILE *p, *q;
    int amt;
    p = fopen("ddaatt", "rb+");
    if (p == NULL)
    {
        printf("\nSomething Went Wrong!!");
        getch();
        return;
    }
    else
    {
        fseek(p, 0, SEEK_END);
        int po = ftell(p);
        int num = po / sizeof(b1);

        int n;
        printf("\nEnter the Account Number: ");
        scanf("%d", &n);

        if (n > num)
        {
            printf("\nInvalid Account Number!!");
            getch();
            return;
        }
        else
        {
            int pos = (n - 1) * sizeof(b1);
            fseek(p, pos, SEEK_SET);
            fread(&b1, sizeof(b1), 1, p);
            char opas[10];
            printf("\nEnter Your Password: ");
            getPassword(opas);
            if (strcmp(b1.pass, opas) == 0)
            {

                if (b1.status == 'a')
                {
                    printf("\nEnter Deposit Amount: ");
                    scanf("%d", &amt);
                    b1.bal = b1.bal + amt;
                    fseek(p, pos, SEEK_SET);
                    fwrite(&b1, sizeof(b1), 1, p);
                    printf("\nAmount Deposited Sucessfully");
                    q = fopen("trnc", "ab");
                    if (q == NULL)
                    {
                        printf("\nSomething Went Wrong!!");
                        getch();
                        return;
                    }
                    else
                    {
                        struct transaction t1;
                        t1.acno = b1.acno;
                        t1.trtype = 'c';
                        t1.amt = amt;
                        fwrite(&t1, sizeof(t1), 1, q);
                    }
                    fclose(p);
                    fclose(q);
                }
                else
                {
                    printf("\nYour Account is Suspended!! Please Contact The Bank");
                    getch();
                    return;
                }
            }
            else
            {
                printf("\nPassword Do not Match");
            }
        }
    }
}
void withdrawAccount()
{
    system("cls");
    struct bank b1;
    FILE *p, *q;
    int amt;
    p = fopen("ddaatt", "rb+");
    if (p == NULL)
    {
        printf("\nSomething Went Wrong!!!");
        getch();
        return;
    }
    else
    {
        fseek(p, 0, SEEK_END);
        int po = ftell(p);
        int num = po / sizeof(b1);

        int n;
        printf("\nEnter the Account Number: ");
        scanf("%d", &n);

        if (n > num)
        {
            printf("\nInvalid Account Number!!");
            getch();
            return;
        }
        else
        {
            int pos = (n - 1) * sizeof(b1);
            fseek(p, pos, SEEK_SET);
            fread(&b1, sizeof(b1), 1, p);
            char opas[10];
            printf("\nEnter Your Password: ");
            getPassword(opas);
            if (strcmp(b1.pass, opas) == 0)
            {

                if (b1.status == 'a')
                {
                    printf("\nEnter the Withdrawl Amount: ");
                    scanf("%d", &amt);
                    if ((b1.type == 's' && (b1.bal - amt) >= 1000) ||(b1.type == 'S' && (b1.bal - amt) >= 1000)||(b1.type == 'C' && (b1.bal - amt) >= 3000) || (b1.type == 'c' && (b1.bal - amt) >= 3000))
                    {
                        b1.bal = b1.bal - amt;
                        fseek(p, pos, SEEK_SET);
                        fwrite(&b1, sizeof(b1), 1, p);
                        printf("\nAmount has been Withdrawn from Your Account");
                        q = fopen("trnc", "ab");
                        if (q == NULL)
                        {
                            printf("\nSomething Went Wrong!!");
                            getch();
                            return;
                        }
                        else
                        {
                            struct transaction t1;
                            t1.acno = b1.acno;
                            t1.trtype = 'd';
                            t1.amt = amt;
                            fwrite(&t1, sizeof(t1), 1, q);
                        }
                        fclose(q);
                        fclose(p);
                    }
                    else
                    {
                        printf("\nInsufficient Balance");
                        getch();
                        return;
                    }
                }
                else
                {
                    printf("\nYour  Account is Suspended!!! Please Contact the Bank!!!");
                    getch();
                    return;
                }
            }
            else
            {
                printf("\nPassword Do not Match");
            }
        }
    }
}
void activateAccount()
{
    system("cls");
    struct bank b1;
    FILE *p;
    int amt;
    p = fopen("ddaatt", "rb+");
    if (p == NULL)
    {
        printf("\nSomething Went Wrong!!");
        getch();
        return;
    }
    else
    {
        fseek(p, 0, SEEK_END);
        int po = ftell(p);
        int num = po / sizeof(b1);

        int n;
        printf("\nEnter the Account Number:  ");
        scanf("%d", &n);

        if (n > num)
        {
            printf("\nInvalid Account Number!! ");
            getch();
            return;
        }
        else
        {
            int pos = (n - 1) * sizeof(b1);
            fseek(p, pos, SEEK_SET);
            fread(&b1, sizeof(b1), 1, p);
            char opas[10];
            printf("\nEnter Your Password: ");
            getPassword(opas);

            if (strcmp(b1.pass, opas) == 0)
            {

                if (b1.status == 'd')
                {
                    b1.status = 'a';
                    fseek(p, pos, SEEK_SET);
                    fwrite(&b1, sizeof(b1), 1, p);
                    fclose(p);
                    printf("\nYour Account is Successfully Activated");
                }
                else
                {
                    printf("\nYour Account is Already Activate");
                    getch();
                    return;
                }
            }
            else
            {
                printf("\nPassword Do not Match");
            }
        }
    }
}
void deactivateAccount()
{
    system("cls");
    struct bank b1;
    FILE *p;
    int amt;
    p = fopen("ddaatt", "rb+");
    if (p == NULL)
    {
        printf("\nAccount Not Found!!!");
        getch();
        return;
    }
    else
    {
        fseek(p, 0, SEEK_END);
        int po = ftell(p);
        int num = po / sizeof(b1);

        int n;
        printf("\nEnter the Account Number: \n");
        scanf("%d", &n);

        if (n > num)
        {
            printf("\nInvalid Account Number");
            getch();
            return;
        }
        else
        {
            int pos = (n - 1) * sizeof(b1);
            fseek(p, pos, SEEK_SET);
            fread(&b1, sizeof(b1), 1, p);
            char opas[10];
            printf("\nEnter Your Password:");
            getPassword(opas);

            if (strcmp(b1.pass, opas) == 0)
            {

                if (b1.status == 'a')
                {
                    b1.status = 'd';
                    fseek(p, pos, SEEK_SET);
                    fwrite(&b1, sizeof(b1), 1, p);
                    fclose(p);
                    printf("\nYour Account is Successfully Deactivated");
                }
                else
                {
                    printf("\nYour Account is Suspended!!! Please Contact the Bank");
                    getch();
                    return;
                }
            }
            else
            {
                printf("\nPassword Do Not Match");
            }
        }
    }
}
void transferAccount() {
    system("cls");
    struct bank sender, receiver;
    FILE *p;
    int amt;
    p = fopen("ddaatt", "rb+");
    if (p == NULL) {
        printf("Account data file not found!!");
        getch();
        return;
    } else {
        fseek(p, 0, SEEK_END);
        int po = ftell(p);
        int num = po / sizeof(struct bank);
        system("cls");
        int to, frm;
        printf("Enter the Sender's Account Number: ");
        scanf("%d", &frm);
        printf("Enter the Receiver's Account Number: ");
        scanf("%d", &to);
        if (to > num || frm > num || to <= 0 || frm <= 0) {
            printf("Sender or Receiver Account Number is not valid");
            getch();
            fclose(p);
            return;
        } else {
            printf("\nEnter the Transfer Amount: ");
            scanf("%d", &amt);
            if (amt <= 0) {
                printf("Invalid amount");
                getch();
                fclose(p);
                return;
            }
            int pos_to = (to - 1) * sizeof(struct bank);
            int pos_frm = (frm - 1) * sizeof(struct bank);
            fseek(p, pos_to, SEEK_SET);
            fread(&receiver, sizeof(struct bank), 1, p);
            if (receiver.status != 'a') {
                printf("Receiver's account is not active");
                getch();
                fclose(p);
                return;
            }
            char opas[10];
            printf("\nEnter Sender's Password: ");
            getPassword(opas);
            fseek(p, pos_frm, SEEK_SET);
            fread(&sender, sizeof(struct bank), 1, p);
            if (strcmp(sender.pass, opas) == 0) {
                if ((sender.type == 's' || sender.type == 'S') && (sender.bal - amt < 1000)) {
                    printf("Insufficient balance in the sender's account");
                    getch();
                    fclose(p);
                    return;
                }
                if ((sender.type == 'c' || sender.type == 'C') && (sender.bal - amt < 3000)) {
                    printf("Insufficient balance in the sender's account");
                    getch();
                    fclose(p);
                    return;
                }
                sender.bal -= amt;
                fseek(p, pos_frm, SEEK_SET);
                fwrite(&sender, sizeof(struct bank), 1, p);

                receiver.bal += amt;
                fseek(p, pos_to, SEEK_SET);
                fwrite(&receiver, sizeof(struct bank), 1, p);
                printf("\nAmount Transferred Successfully");
            } else {
                printf("\nIncorrect Password");
            }
            fclose(p);
        }
    }
}

void forgotPass()
{
    system("cls");
    struct bank b1;
    FILE *p;
    int amt;
    p = fopen("ddaatt", "rb+");
    if (p == NULL)
    {
        printf("\nAccount Not Found!!");
        getch();
        return;
    }
    else
    {
        fseek(p, 0, SEEK_END);
        int po = ftell(p);
        int num = po / sizeof(b1);

        int n;
        printf("\nEnter the Account Number you want to recover the password: ");
        scanf("%d", &n);

        if (n > num)
        {
            printf("\nInvalid Account Number ");
            getch();
            return;
        }
        else
        {
            int pos = (n - 1) * sizeof(b1);
            fseek(p, pos, SEEK_SET);
            fread(&b1, sizeof(b1), 1, p);
            printf("\nGive Answer to Your Recover Question: ");
            printf("%s\n", b1.qns);
            char an[30];
            fflush(stdin);
            gets(an);
            if (strcmp(b1.ans, an) == 0)
            {
                printf("\nYour Password is= %s\n", b1.pass);
                getch();
                return;
            }
            else
            {
                printf("\nInvalid Answer");
                getch();
                return;
            }
        }
    }
}
int main()
{
    char ch;
    int n;
    do
    {
        clearScreen();
        printf("\n===== Bank Management System =====\n");
        printf("1. Create Account\n");
        printf("2. Show Details\n");
        printf("3. Deposit\n");
        printf("4. Withdraw\n");
        printf("5. Activate Account\n");
        printf("6. Deactivate Account\n");
        printf("7. Transfer\n");
        printf("8. Change Name\n");
        printf("9. Change Type\n");
        printf("10. Change Password\n");
        printf("11. Forgot Password\n");
        printf("12. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &n);
        fflush(stdin);

        if (n == 1)
            createAccount();
        else if (n == 2)
            showDetails();
        else if (n == 3)
            depositeAccount();
        else if (n == 4)
            withdrawAccount();
        else if (n == 5)
            activateAccount();
        else if (n == 6)
            deactivateAccount();
        else if (n == 7)
            transferAccount();
        else if (n == 8)
            changeName();
        else if (n == 9)
            changeType();
        else if (n == 10)
            changePass();
        else if (n == 11)
            forgotPass();
        else if (n == 12)
            printf("Thank you for visiting");
        else
        {
            printf("Invalid Choice");
            exit(0);
        }

        printf("\nDo you want to Continue (y for yes and n for no)?: ");
        fflush(stdin);
        scanf("%c", &ch);

    } while (ch != 'n' && ch != 'N');

    return 0;
}