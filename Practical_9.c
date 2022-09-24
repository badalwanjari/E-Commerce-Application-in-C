#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 30
int auth = 0;
void main_menu();
void login();
void reg();
void profile();
typedef struct prod{
    int id;
    char title[30];
    char categary[20];
    int price;
}product;
product productlist[] = {
    {0, "Samsung Galaxy Note 22+", "Mobile", 170000},
    {1, "Samsung Galaxy Note 10", "Mobile", 45000},
    {2, "Samsung Galaxy Note 10 Plus", "Mobile", 70000},
    {3, "Apple iPhone 13", "Mobile", 75000},
    {4, "Apple iPhone 13 Pro", "Mobile", 95000},
    {5, "Apple iPhone 13 Pro Max", "Mobile", 108000},
    {6, "OnePlus 10", "Mobile", 60000},
    {7, "OnePlus 10T", "Mobile", 65000},
    {8, "OnePlus Buds", "HeadPhones", 5000},
    {9, "Apple Buds Pro", "HeadPhones", 14000},
    {10, "Samsung Galaxy Buds", "HeadPhones", 45000},
    {11, "RealMe 22' TV", "TV", 20000},
    {12, "RealMe 36' TV", "TV", 30000},
    {13, "RealMe 104cm TV", "TV", 24000},
    {14, "Samsung OLED 32'", "TV", 104000},
    {15, "Pooma Tshirt S/M/L", "Clothing", 3000},
    {16, "Adidas Polo t-shirt", "Clothing", 4000},
    {17, "Titan Mechanical Watch", "Watch", 10000},
    {18, "Sonata analog watch", "Watch", 3200},
    {19, "Titan Mechanical Watch", "Watch", 10000},
    {20, "TIMEX analog watch", "Watch", 5600}
};
char catList[][30] = {"Mobile", "HeadPhones", "TV", "Clothing", "Watch"};
typedef struct cust{
    char username[20], password[20], address[20], phone[15];
    int list[30];
    struct cust* next;
}*customer;
customer custhead;
customer myself;
void writeLinkedList(){
    customer temp = custhead;
    FILE* file;
    file = fopen ("customer.txt", "w");
    if (file == NULL){
        fprintf(stderr, "\nCouldn't Open File'\n");
        exit (1);
    }
    while(temp!=NULL){
        fwrite(temp, sizeof(struct cust), 1, file);
        temp = temp->next;
    }
    fclose(file);

}
void readLinkedList(){
    customer temp = (customer)malloc(sizeof(struct cust));;
    customer head; // points to the first node of the linked list in the file
    customer last; // points to the last node of the linked list in the file
    last = head = NULL;

    FILE* file;
    file = fopen ("customer.txt", "r");
    if (file == NULL){
        fprintf(stderr, "\nCouldn't Open File'\n");
        exit (1);
    }
    while(fread(temp, sizeof(struct cust), 1, file)){
        if(head==NULL){
            head = last = (customer)malloc(sizeof(struct cust));
        }
        else{
            last->next = (customer)malloc(sizeof(struct cust));
            last = last->next;
        }
        strcpy(last->username, temp->username);
        strcpy(last->password, temp->password);
        strcpy(last->phone, temp->phone);
        strcpy(last->address, temp->address);
        for(int i=0;i<SIZE;i++){
            last->list[i] = temp->list[i];
        }
    }
    fclose(file);
    custhead = head;
}
void productsDisplay(){
    if(auth == 0)main_menu();
    system("cls");
    int opt;
    printf("\t\tCATEGORIES\n\t\t\t1. ALL PRODUCTS \n\t\t\t2. Category-wise\n\t\t\t0. Back\n");
    printf("\n\t\tEnter choice : ");
    scanf("%d", &opt);
    if(opt==2){
        char cat[20];
        system("cls");
        printf("\t\tCategories\n");
        for(int i=0;i<sizeof(catList)/sizeof(catList[0]);i++){
            printf("\t%2d : %-20s\n", i+1, catList[i]);
        }
        printf("\t\t\tITEMS\n");
        printf("\t\tENTER OPTION: ");
        scanf("%d", &opt);

        for(int i=0;i<sizeof(productlist)/sizeof(productlist[0]);i++){
            if(strcmp(productlist[i].categary,catList[opt-1])==0){
                printf("\t\t%-5d: %-30s\t%10d\n", productlist[i].id, productlist[i].title, productlist[i].price);
            }
        }
    }else if(opt==1){
        system("cls");
        printf("\t\t\tITEMS\n");
        for(int i=0;i<sizeof(productlist)/sizeof(productlist[0]);i++){
                printf("\t\t%-5d: %-30s\t%10d\n", productlist[i].id, productlist[i].title, productlist[i].price);
        }
    }else{
        return;
    }
    char ch;
    printf("\n\tDo you want to buy something (y/n)? ");scanf(" %c", &ch);
    if(ch == 'y'){
        printf("\t\tEnter Product ID: ");
        scanf("%d", &opt);
        myself->list[opt] = -1;
        productsDisplay();
    }else{
        productsDisplay();
    }
}
void showCart(){
    system("cls");
    printf("\n\t\tMY CART\n");
    int total = 0;
    for(int i=0;i<SIZE;i++){
        if(myself->list[i] == -1){
            printf("%-2d - %-30s - Rs. %7d\n", productlist[i].id, productlist[i].title, productlist[i].price);
            total += productlist[i].price;
        }
    }
    if(total == 0){
        printf("\t\t\tYOUR CART IS EMPTY! LOL!\n\n");return;
    }
    printf("\n\nTOTAL - RS. %-7d\n\n", total);
    char ch;
    int flag;
    printf("\nWant to remove any product?(y/n): ");scanf(" %c", &ch);
    if(ch == 'y'){
        printf("ENTER PRODUCT ID : ");
        scanf("%d", &flag);
        myself->list[flag] = 0;
        printf("PRODUCT REMOVED!\n\n");
        system("pause");
        return;
    }
    return;
}
void checkout(){
    system("cls");
    printf("\n\t\tMY CART\n");
    int total = 0;
    for(int i=0;i<SIZE;i++){
        if(myself->list[i] == -1){
            printf("%-2d - %-30s - Rs. %7d\n", productlist[i].id, productlist[i].title, productlist[i].price);
            total += productlist[i].price;
        }
    }
    if(total == 0){
        printf("\t\t\tCART IS EMPTY! LOL!\n");return;
    }
    printf("\n\nTOTAL - RS. %-7d\n\n", total);
    char flag;
    printf("Pay Amount?(y/n) : ");
    scanf(" %c", &flag);
    if(flag == 'y'){
        for(int i=0;i<SIZE;i++){
            myself->list[i] = 0;
        }
        printf("PRODUCTS WILL SHIP to: ");
        profile();
        printf("WAITING FOR PAYMENT\n");
        system("pause");
        system("cls");
        printf("\nCHECKOUT SUCCEED\n");
    }else{
        system("cls");
        printf("CHECKOUT FAILED\n");
    }
    system("pause");
    writeLinkedList();
    return;
}
void inputPass(char password[]){
//     int index = 0;
//     char c;
//     while((c = getch()) != 13){
//        if(index < 0){
//            index = 0;
//        }
//        if(c == 8){
//            index--;
//        continue;
//        }
//        password[index++] = c;
//        putch('*');
//    }
    gets(password);

}
void main_menu(){
    while(1){
        system("cls");
        printf("\n%10s\n", "****WELCOME TO MART****");
        printf("1. LOGIN\n");
        printf("2. New to mart? REGISTER...\n");
        printf("0. EXIT\n");
        int opt;
        printf("Enter option : ");
        scanf("%d", &opt);
        switch(opt){
            case 1: login();break;
            case 2: reg();break;
            case 0: writeLinkedList();exit(0);
            default: printf("\nTRY AGAIN\n");
        }
    }
}
void profile(){
printf("\nUSERNAME:%s\nADDRESS:%s\nPHONE NO:%s\n\n", myself->username, myself->address, myself->phone);return;
}
void login(){
    printf("\n-----LOGIN------\n");
    char phone[20];char password[20];
    printf("Enter phone number: ");fflush(stdin);
    gets(phone);
    printf("Enter Password: ");fflush(stdin);
    inputPass(password);
    customer ptr = custhead;
    while(ptr != NULL){
        if(strcmp(phone, ptr->phone) == 0 && strcmp(password, ptr->password) == 0){
            auth = 1;
            myself = ptr;
            system("cls");
            printf("\n\t\tLOGGED IN SUCCESSFULLY!\n");
            system("pause");
            int opt;
            while(1){
                system("cls");
                printf("\nNamaste %s!\n\n",myself->username);
                printf("\n\tHOMEPAGE-MENU\n\t1. Go to store\n\t2. Show my cart\n\t3. Checkout\n\t4. Profile\n\t0. LOGOUT\n");
                printf("\n\tEnter Option : ");scanf("%d", &opt);
                switch(opt){
                    case 1: productsDisplay();system("pause");break;
                    case 2: showCart();system("pause");break;
                    case 3: checkout();system("pause");break;
                    case 4: profile();system("pause");break;
                    case 0: auth = 0; myself = NULL; writeLinkedList(); return main_menu();
                }
                writeLinkedList();
            }
            return;
        }
        ptr = ptr->next;
    }
    if(auth == 0){
        printf("\nLOGIN FAILED\n\n");
        system("pause");
        main_menu();
    }
}
void reg(){
    system("cls");
    printf("\n-----REGISTER PAGE------\n");
    customer ptr = custhead;
    customer temp = (customer)malloc(sizeof(struct cust));
    printf("Enter Your Name : ");fflush(stdin);
    gets(temp->username);
    printf("Enter Your Phone Number : ");fflush(stdin);
    gets(temp->phone);
    printf("Enter Residential Address : ");fflush(stdin);
    gets(temp->address);
    char str[20], str1[20];
    do{
        printf("Create Password : ");
        inputPass(str);
        printf("Confirm Password : ");
        inputPass(str1);
    }while(strcmp(str, str1)!=0);
    strcpy(temp->password, str);
    if(ptr == NULL){
        custhead = temp;
    }else{
        while(ptr->next != NULL)ptr = ptr->next;
        ptr->next = temp;
    }
    writeLinkedList();
    printf("Please Enter your credential and happy shopping!\n");
    system("pause");
    main_menu();
}
void userlist(){
    customer ptr = custhead;
    while(ptr!=NULL){
        printf("%s - %s -%s\n", ptr->username, ptr->phone, ptr->password);
        ptr = ptr->next;
    }
}
int main(){
    readLinkedList();
    customer ptr = custhead;
    main_menu();
    //userlist();
    writeLinkedList();
}
