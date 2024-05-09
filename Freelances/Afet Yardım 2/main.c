#include <stdio.h>
#include <stdlib.h>
#include "afet_yardim_sistemi.h"

void menu_secim_yap(int secim);  // Function prototype for menu selection
void afetzede_ekle_menu();       // Function prototype for victim addition
void afetzede_guncelle_menu();   // Function prototype for victim update
void afetzede_sil_menu();        // Function prototype for victim deletion
void talep_olustur_menu();       // Function prototype for help request creation
void afetzede_listele_menu();    // Function prototype for victim listing
void afetzede_ara_menu();        // Function prototype for victim searching
void talepleri_listele_menu();   // Function prototype for help requests listing

int main() 
{
    int choose;
    
    while (1)
    {
        menu_goster();             // Displays the menu options
        scanf("%d" , &choose);     // Reads user input for menu selection

        menu_secim_yap(choose);    // Calls the corresponding function for the selected menu option
    }

    return 0;
}

void menu_secim_yap(int x)
{
    if (x == 1)         afetzede_ekle_menu();       // Calls the function to add a victim
    else if (x == 2)    afetzede_guncelle_menu();   // Calls the function to update a victim's information
    else if (x == 3)    afetzede_sil_menu();        // Calls the function to delete a victim
    else if (x == 4)    talep_olustur_menu();       // Calls the function to create a help request
    else if (x == 5)    afetzede_listele_menu();    // Calls the function to list all victims
    else if (x == 6)    afetzede_ara_menu();        // Calls the function to search for a victim
    else if (x == 7)    talepleri_listele_menu();   // Calls the function to list all help requests
    else if (x == 8)    exit(0);                    // Exits the program if user selects option 8
    else                    hata_mesaji();           // Displays an error message if user input is invalid
}

void afetzede_ekle_menu() 
{
    char name[100], surname[100], phone[100], adress[100];

    //IO section
    printf("Ad:");              
    scanf("%s", name);          

    printf("Soyad:");           
    scanf("%s", surname);       

    printf("Telefon:");         
    scanf("%s", phone);         

    printf("Adres:");           
    scanf("%s", adress);        

    afetzede_ekle(name, surname, phone, adress);  // Calls the function to add the victim to the system
}

// This function is used to update the information of a disaster victim
void afetzede_guncelle_menu() 
{
    char name[100], surname[100], phone[100], adress[100]; // define variables to store name, surname, phone, and address of the victim
    int id = -1; // initialize the ID to -1


    //IO section
    printf("Id giriniz:"); 
    scanf("%d", &id);

    printf("Ad:"); 
    scanf("%s", name); 

    printf("Soyad:"); 
    scanf("%s", surname); 

    printf("Telefon:"); 
    scanf("%s", phone); 

    printf("Adres:");
    scanf("%s", adress); 

    afetzede_guncelle(id, name, surname, phone, adress); // call the function to update the information of the victim
}

// This function is used to delete a disaster victim
void afetzede_sil_menu() 
{
    int id; // define a variable to store the ID of the victim to be deleted

    //IO section
    printf("Id giriniz:");
    scanf("%d", &id); 

    afetzede_sil(id); // call the function to delete the victim with the given ID
}

// This function is used to create a new help request
void talep_olustur_menu() 
{
    char talep[MAX_TALEP_UZUNLUK]; // define a variable to store the help request
    int id; // define a variable to store the ID of the person who made the request

    //IO section
    printf("Talep Aciklamasi:"); 
    scanf(" %[^\n]", talep);

    printf("Kisi id'si:"); 
    scanf("%d", &id); 

    yardim_talebi_kaydet(id, talep); // call the function to save the help request with the given ID
}

// This function is used to list all disaster victims
void afetzede_listele_menu() 
{
    afetzede_listele(); // call the function to list all the victims
}

// This function is used to search for a disaster victim
void afetzede_ara_menu()
{
    int id; // define a variable to store the ID of the victim to be searched

    //IO section
    printf("Id:"); 
    scanf("%d", &id); 
    
    afetzede_ara(id); // call the function to search for the victim with the given ID
}

// This function is used to list all help requests
void talepleri_listele_menu()
{
    yardim_talepleri_listele(); // call the function to list all the help requests
}
