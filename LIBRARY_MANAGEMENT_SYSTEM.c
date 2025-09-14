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

// ***NOTE***--   fscanf(fp, "%49[^,]", str);
// Matlab: string me maximum 49 characters daalo jab tak comma na aa jaye.
// Agar comma aa gaya toh wahi stop kar do (comma ko consume nahi karega, usse agla fscanf handle karega). 


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
    while (fscanf(fp, "%d,%49[^,],%49[^,],%49s", &b.id, b.name, b.author, b.status) == 4) {
        printf("ID=%d, Name=%s, Author=%s, Status=%s\n", b.id, b.name, b.author, b.status);
        flag = 1 ;
    }
    if(flag==0){
        printf("Library is empty!\n");
    }
    fclose(fp);
}            

// Search a book 
void searchBook() {
    FILE *fp = fopen("books.txt", "r");
    if (fp == NULL) {
        printf("No books found!\n");
        return;
    }
    int found = 0 ;
    int opt;
    printf("Enter 1. when you want to search a Book by its id\nEnter 2. when you want to search Book by its Name\n");
    scanf("%d",&opt);

    // Search a book by ID
    if(opt==1){
        int id;    
        printf("Enter Book ID to search: ");
        scanf("%d", &id);

        struct Book b;
        while (fscanf(fp, "%d,%49[^,],%49[^,],%49s", &b.id, b.name, b.author, b.status) == 4) {// yaha (==4) safest method hai fscanf me (!=EOF) ke jagah 
            if (b.id == id) {                                                                  //jitna format data Read krna hai uska count likhte hai 
                printf("Book Found-> ID=%d, Name=%s, Author=%s, Status=%s\n",
                       b.id, b.name, b.author, b.status);
                found = 1;
                break;
            }
        }

        if (!found) {
            printf("%d id Book not found in library!\n",id);
        }
    }

    // Search a book by Name
    else if(opt==2){
        getchar();
        char name[100];
        printf("Enter your Book name which you want to search:- ");
        fgets(name,sizeof(name),stdin);
        name[strcspn(name,"\n")]= '\0';
        struct Book b;
        while (fscanf(fp, "%d,%49[^,],%49[^,],%49s", &b.id, b.name, b.author, b.status) == 4) {
            if(strcmp(name,b.name)==0){
                printf("Book Found-> ID=%d, Name=%s, Author=%s, Status=%s\n",
                       b.id, b.name, b.author, b.status);
                found = 1;
                break;
            }
        }

        if (!found) {
            printf("%s Book not found in library!\n",name);
        }
    }
    else{
        printf("Invalid option\n");
    }

    fclose(fp);
}

// Issue a book
void issueBook() {
    FILE *fp = fopen("books.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if (fp == NULL) {
        printf("No books found!\n");
        if (temp) fclose(temp);
        return;
    }
    if (temp == NULL) {
        printf("Error creating temporary file!\n");
        fclose(fp);
        return;
    }
    int found = 0;
    
    int opt;
    printf("Enter 1. when you want to issue a Book by its id\nEnter 2. when you want to issue Book by its Name\n");
    scanf("%d",&opt);

    // Issue a book by its ID:--
    if(opt==1){
        int id;
        printf("Enter Book ID to issue: ");
        scanf("%d", &id);

        struct Book b;
        while (fscanf(fp, "%d,%49[^,],%49[^,],%49s", &b.id, b.name, b.author, b.status) == 4) {
            if (b.id == id) {
                found = 1;
                printf("id:- %d, Name :- %s,Author name:- %s, status:- %s\n",b.id,b.name,b.author,b.status);
                if (strcmp(b.status, "Available") == 0) {
                    strcpy(b.status, "Issued");
                    printf("Book issued successfully!\n");
                } else {
                    printf("Book already issued \n");
                }
            }
            fprintf(temp, "%d,%s,%s,%s\n", b.id, b.name, b.author, b.status);
        }

        if (!found) {
            printf("%d id Book not found!\n",id);
        }
    }

   // Issue a book by its Name :--
    else if(opt==2) {
        getchar();
        char name[100];
        printf("Enter your Book name which you want to issue:- ");
        fgets(name,sizeof(name),stdin);
        name[strcspn(name,"\n")]= '\0';

        struct Book b;
        while (fscanf(fp, "%d,%49[^,],%49[^,],%49s", &b.id, b.name, b.author, b.status) == 4) {
            if(strcmp(name,b.name)==0){
                found = 1;
                printf("id:- %d, Name :- %s,Author name:- %s, status:- %s\n",b.id,b.name,b.author,b.status);
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
            printf("%s  Book is not found in Library!\n",name);
        }
    }
    else{
        printf(" Invalid options \n");
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
        if (temp) fclose(temp);
        return;
    }
    if (temp == NULL) {
        printf("Error creating temporary file!\n");
        fclose(fp);
        return;
    }
    int found = 0 ;

    int opt;
    printf("Enter 1. when you want to return a Book by its id\nEnter 2. when you want to return Book by its Name\n");
    scanf("%d",&opt);

    // Return a book by its id 
    if (opt==1){
        int id;
        printf("Enter Book ID to return: ");
        scanf("%d", &id);

        struct Book b;
        while (fscanf(fp, "%d,%49[^,],%49[^,],%49s", &b.id, b.name, b.author, b.status) == 4) {
            if (b.id == id) {
                found = 1;
                printf("id:- %d, Name :- %s,Author name:- %s, status:- %s\n",b.id,b.name,b.author,b.status);
                if (strcmp(b.status, "Issued") == 0) {
                    strcpy(b.status, "Available");
                    printf("Book returned successfully!\n");
                } else {
                    printf("This book was not issued!\n");
                }
            }
            fprintf(temp, "%d,%s,%s,%s\n", b.id, b.name, b.author, b.status);
        }

        if (!found) {
            printf("%d id Book not found!\n",id);
        }
    }

    // Return a book by its Name 
    else if(opt==2){
        getchar();
        char name[100];
        printf("Enter your Book name which you want to Return:- ");
        fgets(name,sizeof(name),stdin);
        name[strcspn(name,"\n")]= '\0';

        struct Book b;
        while (fscanf(fp, "%d,%49[^,],%49[^,],%49s", &b.id, b.name, b.author, b.status) == 4) {
            if(strcmp(name,b.name)==0){
                found = 1;
                printf("id:- %d, Name :- %s,Author name:- %s, status:- %s\n",b.id,b.name,b.author,b.status);
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
            printf("%s  Book is not found in Library!\n",name);
        }
    }
    else{
        printf("Invalid Options \n");
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
        if (temp) fclose(temp);
        return;
    }
    if (temp == NULL) {
        printf("Error creating temporary file!\n");
        fclose(fp);
        return;
    }
    int found = 0 ;

    int opt;
    printf("Enter 1. when you want to delete a Book by its id\nEnter 2. when you want to delete Book by its Name\n");
    scanf("%d",&opt);

    // Delete a book by its id 
    if(opt==1){
        int id;
        printf("Enter Book ID to delete: ");
        scanf("%d", &id);

        struct Book b;
        while (fscanf(fp, "%d,%49[^,],%49[^,],%49s", &b.id, b.name, b.author, b.status) == 4) {
            if (b.id == id) {
                found = 1;
                printf("id:- %d, Name :- %s,Author name:- %s, status:- %s\n",b.id,b.name,b.author,b.status);
                printf("Book deleted successfully!\n");
                continue; // skip writing this book to new file
            }
            fprintf(temp, "%d,%s,%s,%s\n", b.id, b.name, b.author, b.status);
        }

        if (!found) {
            printf("%d id Book not found!\n",id);
        }
    }

    // Delete a book by its Name 
    else if(opt==2){
        getchar();
        char name[100];
        printf("Enter your Book name which you want to Delete:- ");
        fgets(name,sizeof(name),stdin);
        name[strcspn(name,"\n")]= '\0';

        struct Book b;
        while (fscanf(fp, "%d,%49[^,],%49[^,],%49s", &b.id, b.name, b.author, b.status) == 4) {
            if(strcmp(name,b.name)==0){
                found = 1;
                printf("id:- %d, Name :- %s,Author name:- %s, status:- %s\n",b.id,b.name,b.author,b.status);
                printf("\nBook deleted successfully!\n");
                continue; // skip writing this book to new file
            }
            fprintf(temp, "%d,%s,%s,%s\n", b.id, b.name, b.author, b.status);
        }

        if (!found) {
            printf("%s Book is not found in Library!\n",name);
        }
    }

    else{
        printf("Invalid option \n");
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
        case 7: printf("Library closed \n");
             return 0 ;
        default: printf("Invalid choice!\n");
        }
    }

    return 0;
}
