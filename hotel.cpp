//HOTEL GRANSYLVANIA

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 100

struct guest {
	char name[40], phone[21], room[11], id[6];
	int age, duration;
	
	struct guest *next = NULL;
};

struct guest *booking[SIZE];

struct guest *createBooking (char *name, char *phone, int age, char *room, int duration, char *id) {
	struct guest *newBooking = (struct guest*) malloc(sizeof(guest));
	
	strcpy(newBooking -> id, id);
	strcpy(newBooking -> name, name);
	strcpy(newBooking -> phone, phone);
	newBooking -> age = age;
	strcpy(newBooking -> room, room);
	newBooking -> duration = duration;
	
	newBooking -> next = NULL;
	
	return newBooking;
}


//int hashKey (char *id) {
//	int idLength = strlen(id);
//	int x = 0;
//	for(int i = 0; i < 3; i++)
//	{
//		x = x + id[i + 2]; //<-- nomor pada id dimulai index ke 2
//	}
//	
//	x = x - 1;
//	
//	return x % SIZE;
//}

int hashKey (char id[6]) {
	int x = ((id[2] + id[3] + id[4]) - 1) % SIZE;
	
	return x;
}

void Enter()
{
    printf("Press Enter to continue ...\n");
    getchar();
}

void bookingLogic () {
	
	//name
	char name[40];
	do
	{
		printf("Input Full Name [3..30] : ");
		scanf("%[^\n]", name);
		getchar();
		
		if(strlen(name) < 3 && strlen(name) > 30)
		{
			printf("Full name length must be between 3 and 30\n");
		}
	}
	while(strlen(name) < 3 && strlen(name) > 30);
    
    //phone
    char phone[21];
    do
    {
    	printf("Input Phone Number : ");
		scanf("%[^\n]", phone);
		getchar();
	
		if(phone[0] != '+' && phone[1] != '6' && phone[2] != '2' && phone[3] != ' ' || strlen(phone) != 15)
		{
			printf("Phone number must begin with '+62', contains with at least 1 space\n and the length must be 11 (Exclude +62 and space)\n");
		}
	}
	while(phone[0] != '+' && phone[1] != '6' && phone[2] != '2' && phone[3] != ' ' || strlen(phone) != 15);
    
    //age
    int age;
	do
	{
		printf("Input Age [minimum 18] : ");
		scanf("%d", &age);
		getchar();
	
		if(age < 18)
		{
			printf("Age must be minimum 18\n");
		}
	}
	while(age < 18);
	
	//room
	char room[11];
	do	
	{
		printf("Input room type [Regular | Deluxe | Suite] (Case Sensitive) : ");
		scanf("%[^\n]", room);
		getchar();
		
		if(strcmp(room, "Regular") != 0 && strcmp(room, "Deluxe") != 0 && strcmp(room, "Suite") != 0)
		{
			printf("Room type must be either [Regular | Deluxe | Suite] (Case Sensitive)\n");
		}
	}
	while(strcmp(room, "Regular") != 0 && strcmp(room, "Deluxe") != 0 && strcmp(room, "Suite") != 0);
	
	//duration
	int duration;
	do
	{
		printf("Input How Many Night You Will Stay [1..30] : ");
		scanf("%d", &duration);
		getchar();
		
		if(duration < 1 || duration > 30)
		{
			printf("You can't stay less than 1 night or more than 30 nights\n");
		}
	}
	while(duration < 1 || duration > 30);

	//generateId 
	char id[10];
	
	if(strcmp(room, "Regular") == 0) strcpy(id, "RE");
	else if(strcmp(room, "Deluxe") == 0) strcpy(id, "DE");
	else if(strcmp(room, "Suite") == 0)	strcpy(id, "SU");
	
	srand(time(0));
	for(int i = 0; i <= 3; i++)
	{
		id[i + 2] = (char)(rand() % 10 + '0');
	}
	
	//insertBooking
	struct guest *node = createBooking(name, phone, age, room, duration, id);
	int key = hashKey(node -> id);
	
	//kalau belum ada booking, maka  masukkan ke newBooking 
	if(booking[key] == NULL)
	{
		booking[key] = node;
	}
	else
	{
		int current = key;
		//kalau sudah ada booking
		while(booking[current] != NULL)
		{
			current = (current + 1) % SIZE;
            if(current == key)
            {
                printf("System Full!");
                Enter();
                return;
            }
        }
        booking[current] = node;
    }
	
}

void viewBooking () {
	
	int count = 0;
	
	for(int i = 0; i < SIZE; i++)
	{
		//kalo locker ke 0 ada buku (berdasarkan looping), dia bakal jalanin bawah, cek ada buku atau tidak
		if(booking[i])
		{	
			guest *node = booking[i];
			//kalo di locker ada lebih dari 1 buku, maka print terus menerus" 
			while(node != NULL)
			{
				printf("+=======================================================+\n");
				printf("|     BOOKING ID       : %-20s          |\n", node -> id);
				printf("+=======================================================+\n");
				printf("|     FULL NAME        : %-20s          |\n", node -> name);
				printf("|     PHONE NUMBER     : %-20s          |\n", node -> phone);
				printf("|     ROOM TYPE        : %-20s          |\n", node -> room);
				printf("|     NIGHT STAY       : %-20d          |\n", node -> duration);
				printf("+=======================================================+\n");
				//penghubung, instruksi buat dia pindah ke buku selajtnya
				node = node -> next;
				//ada buku
				count = 1;
			}
			//kalau struct cukup tau index laci, gausah barang didalamya
		}
	}
	
	if(count == 0)
	{
		printf("+-----------------------+\n");
		printf("| There is no booking ! |\n");
		printf("+-----------------------+\n");
	}
	
	Enter();
}

void deleteBooking () {
	char id[5];
	
	int flag = 1;
	for(int i = 0; i <= SIZE; i++)
	{
		if(booking[i] == NULL)
		{
			//penanda udah liat dari atas kebawah kalau data nya ada atau ga
			flag = 0;

		}
		else
		{
			flag = 1;
			break;
		}
	}
	
	if(flag == 0)
	{
		printf("+-----------------------+\n");
		printf("| There is no booking ! |\n");
		printf("+-----------------------+\n\n");
		Enter();
	}
	
	if(flag == 1)
	{
		viewBooking();
		printf("Input Booking ID (Case Sensitive) : ");
		scanf("%s", id);
		getchar();
		int key = hashKey(id);
			
		//searching
//		struct guest *temp = booking[key];
//		if(temp != NULL)
//		{
//			if(strcmp(id, temp -> id) == 0)
//			{
//				//temp = NULL;
//				free(temp);
//				booking[key] = NULL;
//					
//				//rasa yang belum hilang
//				printf("BookingID %s is Succesfully Deleted!\n\n", id);
//				Enter();
//				
//				return;
//			}
//			else
//			{
//				printf("+--------------------------------------+\n");
//				printf("| Failed to Delete, There is no Data ! |\n");
//				printf("+--------------------------------------+\n\n");
//				Enter();
//						
//				return;
//			}
//		}
		struct guest *temp = booking[key];
		struct guest *prev = NULL;

		while (temp != NULL)
		{
		    if (strcmp(id, temp->id) == 0)
		    {
		        if (prev == NULL)
		        {
		            // If the booking is the first element in the bucket
		            booking[key] = temp->next;
		        }
		        else
		        {
		            prev->next = temp->next;
		        }
		
		        free(temp);
		        printf("BookingID %s is Successfully Deleted!\n\n", id);
		        Enter();
		        return;
		    }
		
		    prev = temp;
		    temp = temp->next;
		}
		
		// If we reach here, the booking with the given ID was not found
		printf("+--------------------------------------+\n");
		printf("| Failed to Delete, There is no Data ! |\n");
		printf("+--------------------------------------+\n\n");
		Enter();
	
	}
}

int main () {
	
	int menu;
	
	do 
	{ 
		printf("\n");
		printf("+--------------------+\n");
		printf("| Hotel GrAnsylvania |\n");
		printf("+--------------------+\n");
		puts("\n");
		do
		{   
			puts("1. Booking Hotel");
			puts("2. View Bookings");
			puts("3. Delete Booking");
			puts("4. Exit");
			printf(">> ");
			scanf("%d", &menu);
			getchar();
		}
		while(menu > 4 || menu < 1);
		//kalau menu memenuhi while maka ulang tampilkan menu semula
		
		switch(menu) 
		{
			case 1:
				bookingLogic();
				break;
				
			case 2:
				viewBooking();
				break;
				
			case 3:
				deleteBooking();
				break;
				
			case 4:
				printf("Thank You!!!\n");
				break;
		}
	}
	while(menu != 4);
	
	return 0;
}

