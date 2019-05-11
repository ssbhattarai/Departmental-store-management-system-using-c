/*
Departmental store management system to insert, display, delete,update and sale product 
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define USERNAME "admin"
#define PASSWORD "admin123"
#define MAX 20

typedef struct items
{
    char product_code[MAX];
    char product_name[MAX];
    int rate;
    int quantity;
    char description[30];

} ITEM;

ITEM item;

// function to check if the given product code is available
int isCodeAvailable(char code[])
{
    FILE *file;
    file = fopen("Record.txt", "r");
    while (!feof(file))
    {
        fread(&item, sizeof(item), 1, file);
        if (strcmp(code, item.product_code) == 0)
        {
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}

//function to insert the product to the file.
void addProduct()
{
    printf("\v\v\t\t\t\t\t\t\tAdd Product\n");
    printf("\t\t\t\t\t\t************************\n");
    FILE *file;
    char code[MAX];
    file = fopen("Record.txt", "ab");
    printf("\n\t\t\t\t\tEnter Product code: ");
    scanf("%s", code);
    int available;
    available = isCodeAvailable(code); // return 1 if code id found and return 0 if the code is not available.
    if (available == 1)
    {
        system("clear");
        printf("\033[1;31m");
        printf("\n\v\t\t\t\t\t\t* Item is already there.\n");
        printf("\033[0m");
        options();
    }
    strcpy(item.product_code, code); // copy the code to the structure item
    // fflush(stdin);
    // printf("%s", item.product_code);
    // printf("%s", code);
    printf("\nEnter Product Name: ");
    scanf("%s", item.product_name);
    printf("Enter Product Rate: ");
    scanf("%d", &item.rate);
    printf("Enter Quantity: ");
    scanf("%d", &item.quantity);
    printf("Enter product descriptions: ");
    scanf("%s", item.description);

    // writing structure to a file
    fwrite(&item, sizeof(item), 1, file);
    fclose(file);
} // End of addproduct function

void display()
{
    FILE *file;
    int count = 0;
    file = fopen("Record.txt", "rb");
    printf("\t\t\t\t\t--------------------------------------------------------------------------------------\n");
    printf("\t\t\t\t\t  CODE\t||\tNAME\t||\tRATE\t||\tQUANTITY\t||\tDESCRIPTION\n");
    printf("\t\t\t\t\t--------------------------------------------------------------------------------------\n");
    while (fread(&item, sizeof(item), 1, file))
    {
        printf("\t\t\t\t\t%s\t||\t%s\t||\t%d\t||\t %d\t\t||\t%s \n", item.product_code, item.product_name, item.rate, item.quantity, item.description);
        count++;
    }
    printf("\t\t\t\t\t--------------------------------------------------------------------------------------------------\n");
    if (count == 0)
    {
        printf("\n NO record to display");
    }
    fclose(file);
} // End of display functions

void close_app()
{
    char choice;
    printf("\n Do you want to close the applications?(Y/y)");
    scanf("%s", &choice);
    if (choice == 'Y' || choice == 'y')
    {
        exit(0);
    }
}

// search function start
void search()
{
    FILE *file;
    char code[MAX], product[MAX];
    int available;
    printf("\v\t\t\t\t\tEnter the Product code to search: ");
    scanf("%s", code);
    available = isCodeAvailable(code);
    if (available == 0)
    {
        system("clear");
        system("clear");
        printf("\033[1;31m");
        printf("\n\t\t\t\t\t\tProduct code is not found.\n");
        printf("\033[0m");
    }
    else
    {
        file = fopen("Record.txt", "rb");
        while (fread(&item, sizeof(item), 1, file))
        {
            strcpy(product, item.product_code);
            if (strcmp(product, code) == 0)
            {
                printf("\n\t\t\t\t\tProduct Code: %s", item.product_code);
                printf("\n\t\t\t\t\tName of Product: %s\n\n", item.product_name);
            }
        }
        fclose(file);
    }
} // end of the search function

// Delete function start

void deleteRecord()
{
    FILE *file1, *file2;
    char code[MAX], product[MAX];
    int available;
    printf("Enter the Product code to delete: ");
    scanf("%s", code);
    available = isCodeAvailable(code);
    if (available == 0)
    {
        printf("No Product is found");
    }
    else
    {
        file1 = fopen("Record.txt", "rb");
        file2 = fopen("tempfile.txt", "wb");
        while (fread(&item, sizeof(item), 1, file1))
        {
            strcpy(product, item.product_code);
            if (strcmp(product, code) != 0)
            {
                fwrite(&item, sizeof(item), 1, file2);
            }
        }
        fclose(file1);
        fclose(file2);
        file1 = fopen("Record.txt", "wb");
        file2 = fopen("tempfile.txt", "rb");
        while (fread(&item, sizeof(item), 1, file2))
        {
            fwrite(&item, sizeof(item), 1, file1);
        }
        printf("Product deleted sucessfully!!\n\n");
        fclose(file1);
        fclose(file2);
    }

} // end of delete file

// Function to delete the functions
void updateProduct()
{
    FILE *file1, *file2;
    char code[MAX], product[MAX];
    int available;
    printf("enter the Product code to update the record:");
    scanf("%s", code);
    available = isCodeAvailable(code);
    if (available == 0)
    {
        printf("no Product is found for update.");
    }
    else
    {
        file1 = fopen("Record.txt", "rb");
        file2 = fopen("tempfile.txt", "wb");
        while (fread(&item, sizeof(item), 1, file1))
        {
            strcpy(product, item.product_code);
            if (strcmp(product, code) != 0)
            {
                fwrite(&item, sizeof(item), 1, file2);
            }
            else
            {
                printf("\n Updating data for the privious product %s\n", code);
                // printf("Enter new product code: ");
                // scanf("%s", item.product_code);
                // fflush(stdin);
                printf("enter Product Name: ");
                scanf("%s", item.product_name);
                printf("Enter Product Rate: ");
                scanf("%d", &item.rate);
                printf("Enter Quantity: ");
                scanf("%d", &item.quantity);
                printf("enter product descriptions: ");
                scanf("%s", item.description);
                printf("\n\n");
                fwrite(&item, sizeof(item), 1, file2);
            }
        }
        fclose(file1);
        fclose(file2);
        file1 = fopen("Record.txt", "wb");
        file2 = fopen("tempfile.txt", "rb");
        while (fread(&item, sizeof(item), 1, file2))
        {
            fwrite(&item, sizeof(item), 1, file1);
        }
        fclose(file1);
        fclose(file2);
    }
} //end of update file.

void login()
{
    char username[15], password[10];
loginAgain:
    //system("clear");

    printf("\v\v\t\t\tEnter username: ");
    scanf("%s", username);
    printf("\t\t\tEnter password: ");
    scanf("%s", password);
    while (1)
    {
        if ((strcmp(USERNAME, username)) == 0 && (strcmp(PASSWORD, password)) == 0)
        {
            system("clear");
            printf("\033[1;32m");
            printf("\n\t\t\tLogin successfully!!");
            printf("\033[0m");
            //printf("\v\v\t\t\t--Welcome to the Hritik Departmental Store--\n");
            options();
        }
        else
        {
            system("clear");
            printf("\033[1;31m");
            printf("\n\t\t\tsorry you enter the worng information.\n");
            printf("\n\t\t\tPlease try again.\n");
            printf("\033[0m");
            goto loginAgain;
            break;
        }
    }
} //end of login function

// start main funcion
int main()
{
    login();
    system("clear");
    return 0;
} // end of main

void saleProduct()
{
    char x[4] = {0}; // for item code
    int q = 0, size = 0, i = 1;
    int total = 0, gtotal = 0;
    FILE *file;
    file = fopen("Record.txt", "r+b");
    rewind(file);
    system("clear");
    // dbill();
    printf("Enter  \"end\" to finish input");
    while (1)
    {

        printf("                    ");
        printf("                    ");
        printf("\n\v\vEnter Item Code:");
        // printf("\n\v\vEnter Item Code:");
        scanf("%s", x);
        // getline(&x, MAX, stdin);
        if (strcmp(x, "end") == 0)
        {
            break;
        }
        printf("Enter Quantity:");
        scanf("%d", &q);
        rewind(file);
        while (fread(&item, sizeof(item), 1, file))
        {
            if ((strcmp(item.product_code, x) == 0))
            {
                total = item.rate * q;
                printf("%4d ", i);
                printf("%9s ", item.product_name);
                printf("%13d ", q);
                printf("%d ", item.rate);
                printf("%d ", total);
                gtotal = gtotal + total;
                size = sizeof(item);
                item.quantity = item.quantity - q;
                i++;
                fseek(file, -size, SEEK_CUR);
                fwrite(&item, sizeof(item), 1, file);
                break;
            }
        }
    }
    if (gtotal != 0)
    {
        printf("TOTAL AMOUNT = NRs. %d", gtotal);
    }
    fclose(file);
    // options();
}
// display of the bill.
// void dbill()
// {
//     int i;
//     for (i = 1; i <= 10; i++)
//         printf("-");
//     printf(" HRITIK DEPARTMENTAL STORE");
//     for (i = 1; i <= 10; i++)
//         printf("-");
//     printf("\n\n");
//     printf("CUSTOMER'S BILL\n");
//     printf("SN.   Item Name     Quantity     Rate          Total\n");
// }

void options()
{
    printf("\v\v\n\v\t\t\t\t\t\t\t\t--Hritik Departmental Store--\n");
    printf("\t\t\t\t\t\t\t\t**********************************\n");
    int choice;
    // FILE *file;s
    // file = fopen("Record.txt", "rb");
    // fseek(file, SEEK_CUR, 2);
    // n = ftell(file) / sizeof(item);
    // printf("\n There are %d records.\n", n);
    // // fclose(file);
    while (1)
    {
        // printf("\n__________________________\n");
        // printf("\v\v\t\t\t--Welcome to the Hritik Departmental Store--\n");
        printf("\n\t\t\t\t\t\t\t\t\t\t1. Insert\n\t\t\t\t\t\t\t\t\t\t2. Display");
        printf("\n\t\t\t\t\t\t\t\t\t\t3. Search\n\t\t\t\t\t\t\t\t\t\t4. Delete\n\t\t\t\t\t\t\t\t\t\t5. Update");
        printf("\n\t\t\t\t\t\t\t\t\t\t6. close\n\t\t\t\t\t\t\t\t\t\t7. Sale product\n\n");
        printf("\t\t\t\t\t\t\t\t\t\tEnter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            system("clear");
            addProduct();
            break;
        case 2:
            system("clear");
            display();
            break;
        case 3:
            system("clear");
            search();
            break;
        case 4:
            system("clear");
            deleteRecord();
            break;
        case 5:
            system("clear");
            updateProduct();
            break;

        case 6:
            system("clear");
            close_app();
            break;
        case 7:
            system("clear");
            saleProduct();
            break;
        default:
            system("clear");
            printf("\033[1;31m");
            printf("\t\t* Invalid choice.\n");
            printf("\033[0m");
            break;
        } //end of switch
    }
}

// login function

// saleP function starts here.
