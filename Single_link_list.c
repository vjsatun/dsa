/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include<stdio.h>
#include<stdlib.h>


struct st
{
int data;
struct st *next;
};


void add_begin(int n, struct st **p)
{
  struct st *temp;
  temp = (struct st *) malloc(sizeof(struct st));
  //printf("Enter data to add in single link list\n");
  //scanf("%d", &temp->data);

  temp->data = n;
  temp->next = *p;
  *p = temp;
}

void add_end(int n, struct st **p)
{
  struct st *temp;
  temp = (struct st *) malloc(sizeof(struct st));   
  if(temp == NULL) {
      printf("malloc failed\n");
      return;
  }
  
  temp->data = n;
  
  if(*p == NULL) {
    temp->next = *p;
    *p = temp;
  } else {
      struct st *temp1 = *p;
      while(temp1->next)
        temp1 = temp1->next;
        
      temp->next = temp1->next;
      temp1->next = temp;
  }
  return;
}

void add_middle(int n, struct st **p)
{
  struct st *temp;
  temp = (struct st *)malloc(sizeof(struct st));
  if(temp == NULL) {
    printf("malloc failed\n");
  }
  
  temp->data = n;
  
  if(*p == NULL || n < (*p)->data) {
    temp->next = *p;
    *p = temp;
  } else {
      struct st *temp1 = *p;
      while(temp1) {
          if(temp1->data == n) {
              printf("node already present\n");
              break;
          } else if (temp1->next == NULL || temp1->next->data > n) {
              temp->next = temp1->next;
              temp1->next = temp;
              break;
          }
          temp1 = temp1->next;
      }
  }
  
}

void save_file(struct st *p)
{
    FILE *fp;
    fp = fopen("temp.txt", "w");
    while(p) {
        fprintf(fp, "%d\n", p->data);
        p = p->next;
    }
    
}

void read_file(struct st **p)
{
    int n;
    struct st v, *temp, *temp1;
    FILE *fp;
    fp = fopen("temp.txt", "r");
    while(fscanf(fp, "%d", &v.data) != EOF) {
        temp = (struct st *)malloc(sizeof(struct st));
        temp = &v;
        
        if(*p == NULL) {
            temp->next = *p;
            *p = temp;
            temp1 = temp;
        } else {
            temp->next = temp1->next;
            temp1->next = temp;
            temp1 = temp;
        }
    }
}

int count(struct st *p) {
    int count = 0;
    while(p) {
        count++;
        p = p->next;
    }
    return count;
}

void print_list(struct st *p) {

    while(p) {
        printf("%d...\n", p->data);
        p = p->next;
    }
    
}

void rev_print(struct st *p)
{
    if(p) {
        rev_print(p->next);
        printf("%d ", p->data);
    }
}

void rev_print_1(struct st *p)
{
    struct st **ptr;
    struct st *temp = p;
    int c = count(p);
    ptr = malloc(sizeof(struct st) * c);
    
    for(int i=0; i<c; i++){
        ptr[i] = temp;
        temp = temp->next;
    }
    
    for(int i=c-1; i>=0; i--){
        printf("%d ", ptr[i]->data);
    }
    printf("\n");
}

struct st *search(int n, struct st *p)
{
    while(p) {
        if(p->data == n) {
            return p;
        }
        p = p->next;
    }
    return 0;
}

struct st *search_rec(int n, struct st *p)
{
    if(p) {
        if(p->data == n)
            return p;
        search_rec(n, p->next);
    } else
        return 0;
}

void reverse_link(struct st **hp)
{
    struct st *p=*hp, *q=0, *r=0;
    while(p) {
        r = q;
        q = p;
        p = p->next;
        q->next = r;
    }
    *hp = q;
}

void reverse_data(struct st **hp)
{
    struct st *temp = *hp;
    int *p;
    int c = count(*hp);
    
    p = malloc(sizeof(temp->data) * c);
    
    for(int i=c-1; i>=0; i--) {
        p[i] = temp->data;
        temp = temp->next;
    }

    temp = *hp;

    for (int i=0; i<c; ++i) {
        temp->data = p[i];
        temp = temp->next;
    }

    return;
}

int detectLoop(struct st *p)
{
    struct st *slow, *fast;
    slow = fast = p;
    
    while(slow && fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if(slow == fast)
            return 1;
    }
    return 0;
}

void deleteNode(int n, struct st **p)
{
    struct st *temp = *p;
    struct st *temp1;

    while(temp) {
        if(temp->data == n) {
            if(temp == *p) {
                *p = temp->next;
            } else {
                temp1->next = temp->next;
            }
            free(temp);
            return;
        } else {
            temp1 = temp;
            temp = temp->next;
        }
    }
}

void deleteAllNode(struct st **p){
    struct st *temp = *p;
    while(*p) {
        *p = temp->next;
        free(temp);
        temp = *p;
    }
}

int main()
{
  int n = 5;
  struct st *p, *hp = NULL;

  for (int i=1; i<=n; i++) {
    //add_begin(i*10, &hp);
    add_end(i*10, &hp);
  }
  
  add_middle(5, &hp);
  add_middle(25, &hp);
  add_middle(65, &hp);
  
  save_file(hp);
  //read_file(&hp);
  print_list(hp);
  printf("\ncount node in list: %d\n", count(hp));
  
  printf("\nreverse print using recursion\n");
  rev_print(hp);
  printf("\n\nreverse print using duble pointer\n");
  rev_print_1(hp);
  
  p = search(20, hp);
  if(p!=0)
    printf("\nNode %d found at %u\n", p->data, p);

  p = search_rec(20, hp);
  if(p!=0)
    printf("\nrecursion search Node %d found at %u\n", p->data, p);
    
  printf("\nbefore reverse data %d %u %u\n", hp->data, hp, &hp);
  reverse_data(&hp);
  printf("\after reverse data %d %u %u\n", hp->data, hp, &hp);
    
  //printf("\nbefore reverse link %d %u %u\n", hp->data, hp, &hp);
  //reverse_link(&hp);
  //printf("before reverse link %d %u %u\n", hp->data, hp, &hp);
  
  /* just for make loop in link list */
  //hp->next->next->next->next = hp->next->next;
  int status = detectLoop(hp);
  printf("loop status %d\n", status);
  
  
  deleteNode(25, &hp);
  printf("\n..........after delete node..........\n");
  print_list(hp);
  
  deleteAllNode(&hp);
  printf("\n..........after delete all node..........\n");
  print_list(hp);
  
  return 0;
}

