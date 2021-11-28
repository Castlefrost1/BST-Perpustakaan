// Aldi Julyah Sugiyarto - 2301852455
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 10

//struct for node
struct info_buku {
    char *value;            // all void* types replaced by char*
    struct info_buku *p_left;
    struct info_buku *p_right;
};

struct borrow_list {
	char *valueb;
	struct borrow_list *b_left;
	struct borrow_list *b_right;
};

//use typedef to make calling the compare function easier
typedef int (*Compare)(const char *, const char *);

//inserts elements into the tree
void insert(char* key, struct info_buku** leaf, Compare cmp)
{
    int res;
    if( *leaf == NULL ) {
        *leaf = (struct info_buku*) malloc( sizeof( struct info_buku ) );
        (*leaf)->value = malloc( strlen (key) +1 );     // memory for key
        strcpy ((*leaf)->value, key);                   // copy the key
        (*leaf)->p_left = NULL;
        (*leaf)->p_right = NULL;
        //printf(  "\nnew node for %s" , key);
    } else {
        res = cmp (key, (*leaf)->value);
        if( res < 0)
            insert( key, &(*leaf)->p_left, cmp);
        else if( res > 0)
            insert( key, &(*leaf)->p_right, cmp);
        else                                            // key already exists
            printf ("Key '%s' sudah ada dalam list!\n", key);
    }
}

//inserts elements into the borrow tree
void insertb(char* key, struct borrow_list** leaf, Compare cmp)
{
    int res;
    if( *leaf == NULL ) {
        *leaf = (struct borrow_list*) malloc( sizeof( struct borrow_list ) );
        (*leaf)->valueb = malloc( strlen (key) +1 );     // memory for key
        strcpy ((*leaf)->valueb, key);                   // copy the key
        (*leaf)->b_left = NULL;
        (*leaf)->b_right = NULL;
        //printf(  "\nnew node for %s" , key);
    } else {
        res = cmp (key, (*leaf)->valueb);
        if( res < 0)
            insertb( key, &(*leaf)->b_left, cmp);
        else if( res > 0)
            insertb( key, &(*leaf)->b_right, cmp);
        else                                            // key already exists
            printf ("Key '%s' sudah ada dalam list!\n", key);
    }
}

//compares value of the new node against the previous node
int CmpStr(const char *a, const char *b)
{
    return (strcmp (a, b));     // string comparison instead of pointer comparison
}

char *input( void )
{
    static char line[MAXLEN+1];       // where to place key    
    printf("\nMasukkan nama/judul buku : ");
    fgets( line, sizeof line, stdin );
    return ( strtok(line, "\n" ));    // remove trailing newline
}

//recursive function to print out the tree inorder
void in_order(struct info_buku *root)
{
    if( root != NULL ) {
        in_order(root->p_left);
        printf("  -  %s\n", root->value);     // string type
        in_order(root->p_right);
    }
}

void in_orderb(struct borrow_list *root)
{
    if( root != NULL ) {
        in_orderb(root->b_left);
        printf("  -  %s\n", root->valueb);     // string type
        in_orderb(root->b_right);
    }
}

//searches elements in the tree
void search(char* key, struct info_buku* leaf, Compare cmp)  // no need for **
{
    int res;
    if( leaf != NULL ) {
        res = cmp(key, leaf->value);
        if( res < 0)
            search( key, leaf->p_left, cmp);
        else if( res > 0)
            search( key, leaf->p_right, cmp);
        else
            printf("\n'%s' ada dalam list!\n", key);     // string type
    }
    else printf("\nTidak ada dalam list!\n");
    return;
}


void delete_tree(struct info_buku** leaf)
{
    if( *leaf != NULL ) {
        delete_tree(&(*leaf)->p_left);
        delete_tree(&(*leaf)->p_right);
        free( (*leaf)->value );         // free the key
        free( (*leaf) );
    }
}

//display
void menu()
{
    printf("\nTekan 'i' untuk memasukkan judul buku\n");
    printf("Tekan 's' untuk mencari buku\n");
    printf("Tekan 'm' untuk meminjam buku\n");
    printf("Tekan 'p' untuk melihat list buku\n");
    printf("Tekan 'b' untuk melihat list buku yang dipinjam\n");
    printf("Tekan 'f' untuk menghapus list\n");
    printf("Tekan 'q' untuk quit\n");
}

int main()
{
    struct info_buku *p_root = NULL;
    struct borrow_list *b_root = NULL;
    char *value;
    char option = 'x';
    
//deletes elements in the tree
void borrow(char* key, struct info_buku* leaf, Compare cmp)  // no need for **
{
//	struct borrow_list *b_root = NULL;
    int res;
    if( leaf != NULL ) {
        res = cmp(key, leaf->value);
        if( res < 0){
            search( key, leaf->p_left, cmp);
            printf("Buku '%s' berhasil dipinjam!\n", key);
            insertb(key, &b_root, (Compare)CmpStr);
        }
		else if( res > 0){
            search( key, leaf->p_right, cmp);
            printf("Buku '%s' berhasil dipinjam!\n", key);
            insertb(key, &b_root, (Compare)CmpStr);
    	}
    	else {
            printf("\n'%s' ada dalam list!\n", key);     // string type
            printf("Buku '%s' berhasil dipinjam!\n", key);
            insertb(key, &b_root, (Compare)CmpStr);
        }
    }
    else printf("\nBuku tidak ada dalam list, buku gagal dipinjam!\n");
    return;
}


    while( option != 'q' ) {
        //displays menu for program
        menu();

        //gets the char input to drive menu
        option = getch();           // instead of two getchar() calls

        if( option == 'i') {
            value = input();
            if (value == NULL)
            {
            	printf("Masukkan judul buku!\n");
            	continue;
			}
            printf ("\nMemasukkan %s\n", value);
            insert(value,  &p_root, (Compare)CmpStr);
        }
        else if( option == 's' ) {
            value = input();
            if (value == NULL)
            {
            	printf("Masukkan judul buku!\n");
            	continue;
			}
            search(value, p_root, (Compare)CmpStr);     // no need for **
        }
        else if( option == 'm') {
        	value = input();
        	if (value == NULL)
            {
            	printf("Masukkan judul buku!\n");
            	continue;
			}
        	borrow(value, p_root, (Compare)CmpStr);
		}
        else if( option == 'p' ) {
        	printf("\nList Buku dalam perpustakaan : \n");
            in_order(p_root);
        }
        else if( option == 'b') {
        	printf("\nList Buku yang dipinjam : \n");
        	in_orderb(b_root);
		}
        else if( option == 'f' ) {
            delete_tree(&p_root);
            printf("\nList dihapus");
            p_root = NULL;
        }
        else if( option == 'q' ) {
            printf("\nQuitting");
        }
    }
return 0;
}
