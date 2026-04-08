#include <stdio.h>
#include <string.h>

#define MAX 100

typedef struct {
    int ticketID;
    int seatNumber;
    float price;
    int isAvailable;
} Ticket;

Ticket tickets[MAX];
int totalTickets = 0;

void insertTicket() {
    if(totalTickets >= MAX) { printf("Storage full!\n"); return; }
    Ticket t;
    printf("\nEnter Ticket ID     : "); scanf("%d", &t.ticketID);
    printf("Enter Seat Number   : "); scanf("%d", &t.seatNumber);
    printf("Enter Price (Rs.)   : "); scanf("%f", &t.price);
    t.isAvailable = 1;
    tickets[totalTickets++] = t;
    printf("Ticket added successfully!\n");
}

void displayTickets() {
    if(totalTickets == 0) { printf("\nNo tickets available.\n"); return; }
    printf("\n%-10s %-12s %-12s %-12s\n", "TicketID","SeatNumber","Price(Rs)","Status");
    printf("--------------------------------------------------\n");
    for(int i=0; i<totalTickets; i++)
        printf("%-10d %-12d %-12.2f %-12s\n",
               tickets[i].ticketID, tickets[i].seatNumber,
               tickets[i].price,
               tickets[i].isAvailable ? "Available" : "Booked");
}

int partition(Ticket arr[], int low, int high) {
    float pivot = arr[high].price;
    int i = low - 1;
    for(int j=low; j<high; j++) {
        if(arr[j].price <= pivot) {
            i++;
            Ticket temp=arr[i]; arr[i]=arr[j]; arr[j]=temp;
        }
    }
    Ticket temp=arr[i+1]; arr[i+1]=arr[high]; arr[high]=temp;
    return i+1;
}

void quickSort(Ticket arr[], int low, int high) {
    if(low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi-1);
        quickSort(arr, pi+1, high);
    }
}

void sortTickets() {
    if(totalTickets==0){printf("\nNo tickets to sort.\n");return;}
    quickSort(tickets, 0, totalTickets-1);
    printf("\nTickets sorted by price using Quick Sort!\n");
    displayTickets();
}

void searchByID() {
    int id;
    printf("\nEnter Ticket ID to search: "); scanf("%d", &id);
    for(int i=0; i<totalTickets; i++) {
        if(tickets[i].ticketID == id) {
            printf("\nTicket Found!\n");
            printf("Ticket ID   : %d\n", tickets[i].ticketID);
            printf("Seat Number : %d\n", tickets[i].seatNumber);
            printf("Price       : Rs. %.2f\n", tickets[i].price);
            printf("Status      : %s\n", tickets[i].isAvailable?"Available":"Booked");
            return;
        }
    }
    printf("\nTicket ID %d not found.\n", id);
}

void searchBySeat() {
    Ticket temp[MAX];
    for(int i=0; i<totalTickets; i++) temp[i]=tickets[i];
    for(int i=1; i<totalTickets; i++) {
        Ticket key=temp[i]; int j=i-1;
        while(j>=0 && temp[j].seatNumber>key.seatNumber)
            { temp[j+1]=temp[j]; j--; }
        temp[j+1]=key;
    }
    int seat;
    printf("\nEnter Seat Number to search: "); scanf("%d", &seat);
    int lo=0, hi=totalTickets-1;
    while(lo<=hi) {
        int mid=(lo+hi)/2;
        if(temp[mid].seatNumber==seat) {
            printf("\nSeat Found!\n");
            printf("Ticket ID   : %d\n", temp[mid].ticketID);
            printf("Seat Number : %d\n", temp[mid].seatNumber);
            printf("Price       : Rs. %.2f\n", temp[mid].price);
            printf("Status      : %s\n", temp[mid].isAvailable?"Available":"Booked");
            return;
        }
        if(temp[mid].seatNumber < seat) lo=mid+1; else hi=mid-1;
    }
    printf("\nSeat %d not found.\n", seat);
}

void bookTicket() {
    int id;
    printf("\nEnter Ticket ID to book: "); scanf("%d", &id);
    for(int i=0; i<totalTickets; i++) {
        if(tickets[i].ticketID == id) {
            if(!tickets[i].isAvailable)
                printf("\nSorry! This ticket is already booked.\n");
            else {
                tickets[i].isAvailable = 0;
                printf("\nTicket %d booked successfully!\n", id);
                printf("Seat Number : %d | Price: Rs. %.2f\n",
                       tickets[i].seatNumber, tickets[i].price);
            }
            return;
        }
    }
    printf("\nTicket ID %d not found.\n", id);
}

int main() {
    int choice;
    printf("\n========================================");
    printf("\n   TICKET BOOKING SYSTEM (Quick Sort)   ");
    printf("\n========================================\n");
    do {
        printf("\n----- MENU -----\n");
        printf("1. Add Ticket\n");
        printf("2. Display All Tickets\n");
        printf("3. Sort Tickets by Price (Quick Sort)\n");
        printf("4. Search Ticket by ID\n");
        printf("5. Search Ticket by Seat Number\n");
        printf("6. Book a Ticket\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch(choice) {
            case 1: insertTicket();   break;
            case 2: displayTickets(); break;
            case 3: sortTickets();    break;
            case 4: searchByID();     break;
            case 5: searchBySeat();   break;
            case 6: bookTicket();     break;
            case 7: printf("\nExiting... Thank you!\n"); break;
            default: printf("\nInvalid choice!\n");
        }
    } while(choice != 7);
    return 0;
}