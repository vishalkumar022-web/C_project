//                ****LIBRARY MANAGEMENT SYSTEM****

#include <stdio.h>
#include <string.h>
     
// Book structure
struct Book {
    int id;
    char name[50];
    char author[50];
    char status[50]; 
};

// Add a new book
void addBook() {
    FILE *fp = fopen("books.txt", "a");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    struct Book b;
    printf("Enter Book ID: ");
    scanf("%d", &b.id);
    getchar(); // clear buffer
    printf("Enter Book Name: ");
    fgets(b.name, sizeof(b.name), stdin);
    b.name[strcspn(b.name, "\n")] = '\0'; // remove newline
    printf("Enter Author Name: ");
    fgets(b.author, sizeof(b.author), stdin);
    b.author[strcspn(b.author, "\n")] = '\0';

    strcpy(b.status, "Available"); // Pahle sara book by Default availlable hi rahega..

    fprintf(fp, "%d,%s,%s,%s\n", b.id, b.name, b.author, b.status);
    fclose(fp);

    printf("Book added successfully!\n");
}

// View all books
void viewBooks() {
    FILE *fp = fopen("books.txt", "r");
    if (fp == NULL) {
        printf("No books found!\n");
        return;
    }
        struct Book b ;
        int flag = 0 ;
    printf("\n--- All Books in Library ---\n");
    while (fscanf(fp, "%d, %49[^,], %49[^,], %s", &b.id, b.name, b.author, b.status) != EOF) {
        printf("ID=%d, Name=%s, Author=%s, Status=%s\n", b.id, b.name, b.author, b.status);
            flag = 1 ;
    }
    if(flag!=1){
        printf("Library is empty!");
    }
 
    fclose(fp);
}             //fscanf(fp, "%49[^,]", str);
// Matlab: string me maximum 49 characters daalo jab tak comma na aa jaye Agar comma aa gaya
//  toh wahi stop kar do (comma ko consume nahi karega, usse agla fscanf handle karega).
                    
// Search a book by ID
void searchBook() {
    FILE *fp = fopen("books.txt", "r");
    if (fp == NULL) {
        printf("No books found!\n");
        return;
    }
    int found = 0 ;
    // int id, found = 0;    
    // printf("Enter Book ID to search: ");
    // scanf("%d", &id);
    getchar();
    char name[100];
    printf("Enter your Book name which you want to search:- ");
    fgets(name,sizeof(name),stdin);
    name[strcspn(name,"\n")]= '\0';
    struct Book b;
    while (fscanf(fp, "%d, %49[^,], %49[^,], %s", &b.id, b.name, b.author, b.status) != EOF) {
        // if (b.id == id) {
        if(strcmp(name,b.name)==0){
            printf("Book Found-> ID=%d, Name=%s, Author=%s, Status=%s\n",
                   b.id, b.name, b.author, b.status);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Book not found in library!\n");
    }

    fclose(fp);
}

// Issue a book
void issueBook() {
    FILE *fp = fopen("books.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if (fp == NULL) {
        printf("No books found!\n");
        return;
    }
        int found = 0;
    // int id, found = 0;
    // printf("Enter Book ID to issue: ");
    // scanf("%d", &id);
        getchar();
     char name[100];
      printf("Enter your Book name which you want to issue:- ");
    fgets(name,sizeof(name),stdin);
    name[strcspn(name,"\n")]= '\0';

    struct Book b;
    while (fscanf(fp, "%d, %49[^,], %49[^,], %s", &b.id, b.name, b.author, b.status) != EOF) {
        // if (b.id == id) {
        if(strcmp(name,b.name)==0){
            found = 1;
        printf("id:- %d, Name :- %s,Author name:- %s, status:- %s",b.id,b.name,b.author,b.status);
            if (strcmp(b.status, "Available") == 0) {
                strcpy(b.status, "Issued");
                printf("\nBook issued successfully!\n");
            } else {
                printf("Book already issued \n");
            }
        }
        fprintf(temp, "%d,%s,%s,%s\n", b.id, b.name, b.author, b.status);
    }

    if (!found) {
        // printf("%d id Book is not found in Library!\n",id);
         printf("%s  Book is not found in Library!\n",name);
    }

    fclose(fp);
    fclose(temp);
    remove("books.txt");
    rename("temp.txt", "books.txt");
}

// Return a book
void returnBook() {
    FILE *fp = fopen("books.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if (fp == NULL) {
        printf("No books found!\n");
        return;
    }
    int found = 0 ;
    // int id, found = 0;
    // printf("Enter Book ID to return: ");
    // scanf("%d", &id);
        getchar();
     char name[100];
      printf("Enter your Book name which you want to Return:- ");
    fgets(name,sizeof(name),stdin);
    name[strcspn(name,"\n")]= '\0';

    struct Book b;
    while (fscanf(fp, "%d, %49[^,], %49[^,], %s", &b.id, b.name, b.author, b.status) != EOF) {
        // if (b.id == id) {
        if(strcmp(name,b.name)==0){
            found = 1;
         printf("id:- %d, Name :- %s,Author name:- %s, status:- %s",b.id,b.name,b.author,b.status);
            if (strcmp(b.status, "Issued") == 0) {
                strcpy(b.status, "Available");
                printf("\nBook returned successfully!\n");
            } else {
                printf("This book was not issued!\n");
            }
        }
        fprintf(temp, "%d,%s,%s,%s\n", b.id, b.name, b.author, b.status);
    }

    if (!found) {
        // printf("%d id Book is not found in Library!\n",id);
         printf("%s  Book is not found in Library!\n",name);
    }

    fclose(fp);
    fclose(temp);
    remove("books.txt");
    rename("temp.txt", "books.txt");
}

// Delete a book
void deleteBook() {
    FILE *fp = fopen("books.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if (fp == NULL) {
        printf("No books found!\n");
        return;
    }
    int found = 0 ;
    // int id, found = 0;
    // printf("Enter Book ID to delete: ");
    // scanf("%d", &id);
        getchar();
    char name[100];
     printf("Enter your Book name which you want to Delete:- ");
    fgets(name,sizeof(name),stdin);
    name[strcspn(name,"\n")]= '\0';

    struct Book b;
    while (fscanf(fp, "%d, %49[^,], %49[^,], %s", &b.id, b.name, b.author, b.status) != EOF) {
        // if (b.id == id) {
        if(strcmp(name,b.name)==0){
            found = 1;
         printf("id:- %d, Name :- %s,Author name:- %s, status:- %s",b.id,b.name,b.author,b.status);
            printf("\nBook deleted successfully!\n");
            continue; // skip writing this book to new file
        }
        fprintf(temp, "%d,%s,%s,%s\n", b.id, b.name, b.author, b.status);
    }

    if (!found) {
    //    printf("%d id Book is not found in Library!\n",id);
          printf("%s id Book is not found in Library!\n",name);
    }

    fclose(fp);
    fclose(temp);
    remove("books.txt");
    rename("temp.txt", "books.txt");
}

int main() {
    int choice;

    while (1) {
        printf("\n====== Library Management System ======\n");
        printf("1. Add New Book\n");
        printf("2. View All Books\n");
        printf("3. Search Book\n");
        printf("4. Issue Book\n");
        printf("5. Return Book\n");
        printf("6. Delete Book\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1: addBook(); break;
        case 2: viewBooks(); break;
        case 3: searchBook(); break;
        case 4: issueBook(); break;
        case 5: returnBook(); break;
        case 6: deleteBook(); break;
        case 7: printf("Library closed ");
             return 0 ;
             
        default: printf("Invalid choice!\n");
        }
    }

    return 0;
}
