//
//  main.c
//  dspd2 assignment2
//
//  Created by Official on 06/04/20.
//  Copyright © 2020 Official. All rights reserved.
//
//
// Note : Implemented A.V.L Tree



#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define HASHSIZE 11
#define NAMESIZE 10

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Typedefs <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

typedef struct n{
    long int number;
    struct n *nxt;
} HashNode;

typedef struct t{
    HashNode *hshList[HASHSIZE];
} Number_Set;

typedef struct avl{
    int id;
    char name[NAMESIZE];
    int left_height,right_height;
    Number_Set numbers_in_node;
    struct avl *parent,*left,*right;
} AVL_Node;

typedef struct nt{
    char name[NAMESIZE];
    struct nt *nxt;
}   Route_Node;

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Typedefs end <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Hashfunction <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

int HashFunction(long int num){
    return num%HASHSIZE;
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Hashfunction <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Initialissing Functions <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

void init_AVL_Node(AVL_Node *nd){
    nd->id=0;
    nd->left=NULL;
    nd->name[0]='\0';
    nd->right=NULL;
    nd->parent=NULL;
    nd->left_height=0;
    nd->right_height=0;
    for(int i=0;i<HASHSIZE;i++){
        nd->numbers_in_node.hshList[i]=NULL;
    }
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Initialissing Functions End<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Rotation Functions<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

AVL_Node* Left_Rotate(AVL_Node *root){
  AVL_Node *rt=root;
  AVL_Node *tmp = rt->right;
  rt->right=tmp->left;
    if(tmp->left){
        tmp->left->parent=rt;
    }
    AVL_Node *rtparent = rt->parent;
  tmp->left=rt;
    rt->parent=tmp;
  root = tmp;
    tmp->parent=rtparent;
    return root;
}

AVL_Node* RightRotate(AVL_Node *root){
    AVL_Node *rt=root;
    AVL_Node *tmp = rt->left;
    AVL_Node *rtparent = rt->parent;
    rt->left=tmp->right;
    if(tmp->right!=NULL){
        tmp->right->parent=rt;
    }
    
    tmp->right=rt;
    rt->parent=tmp;
    root = tmp;
    tmp->parent=rtparent;
    return root;
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Rotation Functions End <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

int height(AVL_Node *root){
    if(!root){
        return 0;
    }
    else{
        int lh = height(root->left);
        int rh = height(root->right);
        if(lh>rh){
            return 1+lh;
        }
        else{
            return 1+rh;
        }
    }
}

int num_in_Tree(AVL_Node *root,long int num){
    int fnd=0;
    if(root){
        for(int i=0;i<HASHSIZE && !fnd; i++){
            HashNode *ptr = root->numbers_in_node.hshList[i];
            while(ptr && (!fnd)){
                if(ptr->number==num){
                    fnd=1;
                }
                else{
                    ptr = ptr->nxt;
                }
            }
        }
    }
    return fnd;
}

void print_numbers_in_Node(AVL_Node *nd){
    HashNode *a;
    for (int i=0; i<HASHSIZE; i++) {
        a = nd->numbers_in_node.hshList[i];
        while(a){
            printf(" %ld -->",a->number);
            a = a->nxt;
        }
    }
}

/*               ans 1
               is_Empty
*/
int is_Empty(AVL_Node *root){
    HashNode *ptr = NULL;
    int empty = 1;
    for(int i=0;i<HASHSIZE && empty;i++){
        ptr = root->numbers_in_node.hshList[i];
        if(ptr){
            empty = 0;
        }
    }
    return empty;
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Searching Functions <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

AVL_Node *search(AVL_Node *root,long int num){
    if(!root){
        return NULL;
    }
    else if(!num_in_Tree(root, num)){
        return NULL;
    }
    else{
        if((root->left ==NULL) && (root->right==NULL)){
            return root;
        }
        else{
            AVL_Node *left = search(root->left, num);
            AVL_Node *right = search(root->right, num);
            if(!right){
                return left;
            }
            else{
                return right;
            }
        }
    }
}

AVL_Node *search_via_id(AVL_Node *root,int id){
    if(root){
        if(root->id==id){
            return root;
        }
        else if (root->id>id){
            return search_via_id(root->left, id);
        }
        else{
            return search_via_id(root->right, id);
        }
    }
    else{
        return NULL;
    }
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Searching Functions End <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Insertion Functions <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

HashNode *insert_num_in_hashlist(HashNode *lptr,long int num){
    if(!lptr){
        lptr = malloc(sizeof(HashNode));
        lptr->number=num;
        lptr->nxt=NULL;
    }
    else{
        HashNode *ptr = lptr,*prev=NULL;
        int fnd=0;
        while(ptr&&!fnd){
            if(ptr->number>num){
                fnd=1;
            }
            else{
                prev = ptr;
                ptr=ptr->nxt;
            }
        }
        HashNode *tmp = malloc(sizeof(HashNode));
        tmp->number=num;
        tmp->nxt=ptr;
        if(!prev){
            lptr = tmp;
        }
        else{
            prev->nxt=tmp;
        }
    }
    return lptr;
}

void insert_in_Number_set(AVL_Node *nd,long int num){
    int index = HashFunction(num);
    nd->numbers_in_node.hshList[index]=insert_num_in_hashlist(nd->numbers_in_node.hshList[index], num);
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Pseudocode for insert <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
void insert_in_tree(AVL_Node *root,AVL_Node *nd,long int num){
    if(!num_in_Tree(root, num)){
        while (nd->parent!=NULL) {
            insert_in_Number_set(nd, num);
            nd = nd->parent;
        }
        insert_in_Number_set(root, num);
        //Debug
        print_numbers_in_Node(root);
    }
    else{
        printf("The Number %ld is already in the tree\n",num);
    }
}

//from the given node:
//    go up and add/insert the number till you reach the root
//then insert in root

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>Insertion Functions End <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>Deletion Functions <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

HashNode *delete_from_Hashlist(HashNode *lptr,long int num){
    HashNode *ptr=lptr,*prev = NULL;
    int fnd=0;
    while(!fnd){
        if(ptr->number==num){
            fnd=1;
        }
        else{
            prev = ptr;
            ptr = ptr->nxt;
        }
    }
    if(!prev){
        HashNode *temp = lptr;
        lptr = temp->nxt;
        free(temp);
    }
    else{
        prev->nxt=ptr->nxt;
        free(ptr);
    }
    return lptr;
}


void delete_from_number_set(AVL_Node *nd,long int num){
    int index = HashFunction(num);
    HashNode *ptr = nd->numbers_in_node.hshList[index];
    ptr=delete_from_Hashlist(ptr, num);
    nd->numbers_in_node.hshList[index]=ptr;
}

void delete_from_tree(AVL_Node *root,long int num){
    if(num_in_Tree(root, num)){
        AVL_Node *nd = search(root, num);
        while(nd!=NULL){
            delete_from_number_set(nd, num);
            nd = nd->parent;
        }
    }
    else{
        printf("Number Not in tree\n");
    }
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>Pseudocode for delete <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

//first find if the num is present or not
//if present:
//    search(num,root);
//    while root.parent:
//        del(root,num)
//    del(root,num)


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>Deletion Functions End <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Pseudocode for searching node <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

//if root is null:
//    return null
//else if !number(root->hash_list,num):
//    return null
//else:
//    //print the root for route
//    if !root->left and ! root->right:
//        return root
//    else:
//        avl node left = search(root->left,num)
//        avl node right = search(root->right,num)
//        if !right:
//            return left
//        else:
//            return right

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Pseudocode for lowest router <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

long int Number_in_Node(AVL_Node *nd){
    HashNode *hn;
    long int ret_val=-1;
    hn = nd->numbers_in_node.hshList[0];
    int fnd=0;
    for(int i=0;i<HASHSIZE &&!fnd; i++){
        if(!hn){
            hn=nd->numbers_in_node.hshList[i+1];
        }
        else{
            fnd=1;
            ret_val=hn->number;
        }
    }
    return ret_val;
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Pseudocode for lowest router <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Pseudocode for lowest router <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

AVL_Node *Lowest_router(AVL_Node *a,AVL_Node *b){
    int fnd=0;
    long int num_in_a = Number_in_Node(a);
    long int num_in_b = Number_in_Node(b);
    if((num_in_b==-1) || (num_in_a==-1)){
        printf("\nNo Lowest Route as numbers Doesnot Exist\n");
        return NULL;
    }
    else{
        AVL_Node *ptr = a;
        AVL_Node *ret_val=NULL;
        
        while(ptr && !fnd){
            if(num_in_Tree(ptr, num_in_b)){
                fnd=1;
                ret_val=ptr;
            }
            else{
                ptr = ptr->parent;
            }
        }
        if(!fnd || !ptr){
            printf("Not Present in The Tree\n");
        }
        return ret_val;
    }
}

//Pseudocode for lowest router
//while root.parent && !fnd :
//    if number(root.hash_list,num):
//        fnd=1
//    else:
//        root = root.parent
//    if number(root.hash_list,num):
//        fnd=1
//    if fnd:
//        return root
//    else:
//        return null


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Print lowest Route <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

void Modified_search(AVL_Node *root,long int num){
    if(!root){
        
    }
    else if(!num_in_Tree(root, num)){
        
    }
    else{
        if((root->left ==NULL) && (root->right==NULL)){
            printf("%s\n",root->name);
        }
        else{
            printf("%s --> ",root->name);
            if(num_in_Tree(root->left, num)){
                Modified_search(root->left, num);
            }
            else{
                Modified_search(root->right, num);
            }
            
        }
    }
}

void Print_lowest_route(AVL_Node *root,int id_a,int id_b){
    AVL_Node *a = search_via_id(root, id_a);
    AVL_Node* b = search_via_id(root, id_b);
    long int num_in_b = Number_in_Node(b);
    AVL_Node *intersection = Lowest_router(a, b);
    if(intersection){
        AVL_Node *ptr = a;
        while (ptr!=intersection) {
            printf("%s --> ",ptr->name);
            ptr = ptr->parent;
        }
        Modified_search(intersection, num_in_b);
    }
    else{
        printf("No route Found\n");
    }
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Print lowest route end <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Main <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Main <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Main <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Main <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<



AVL_Node* AVL_FIXUP(AVL_Node *root,AVL_Node *nd){
    while(nd!=NULL){
        AVL_Node* prnt = nd->parent;
        nd->left_height=height(nd->left);
        nd->right_height = height(nd->right);
        if(abs(nd->left_height-nd->right_height)>1){
            if(nd->left_height>nd->right_height){
                if(nd->left->left_height>nd->left->right_height){
                    printf("... Left Fixup ...\n");
                    if(prnt){
                        prnt->left = RightRotate(nd);
                    }
                    else{
                        root = RightRotate(root);
                    }
                }
                else{
                    printf("... Left-Right Fixup ...\n");
                    nd->left = Left_Rotate((nd->left));
                    if(prnt){
                        prnt->left = RightRotate(nd);
                    }
                    else{
                        root = RightRotate(root);
                    }
                }
            }
            else{
                if(nd->right->right_height>nd->right->left_height){
                    printf("... Right Fixup ...\n");
                    if(prnt){
                        prnt->right = Left_Rotate(nd);
                    }
                    else{
                        root = Left_Rotate(root);
                    }
                }
                else{
                    printf("... Right-Left Fixup ...\n");
                    nd->right = RightRotate((nd->right));
                    if(prnt){
                        prnt->right = Left_Rotate(nd);
                    }
                    else{
                        root = Left_Rotate(root);
                    }
            }
        }
        
    }
        nd=nd->parent;
    }
    return root;
}


void AVL_Insert(AVL_Node **root,AVL_Node *nd){
    AVL_Node *y,*x;
    x = *root;
    y = NULL;
    while(x!=NULL){
        y=x;
        if(nd->id<x->id){
            x = x->left;
        }
        else{
            x = x->right;
        }
    }
    nd->parent=y;
    if(!y){
        *root = nd;
    }
    else{
        if(nd->id<y->id){
            y->left=nd;
        }
        else{
            y->right=nd;
        }
    }
    *root = AVL_FIXUP(*root, nd);
    
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Main <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

void print_leaves(AVL_Node *root){
    if(root){
        if(!(root->left) && !(root->right)){
            printf("Name : %s , Id : %d\n",root->name,root->id);
        }
        else{
            print_leaves(root->left);
            print_leaves(root->right);
        }
    }
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Exchange Number <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

void Exchange_Numbers(AVL_Node *root,int id_a,int id_b,long int num){
    AVL_Node* a = search_via_id(root, id_a);
    AVL_Node* b = search_via_id(root, id_b);
    if(num_in_Tree(a, num)){
        AVL_Node *ptr=a;
        while(ptr->parent!=NULL){
            ptr = ptr->parent;
        }
        delete_from_tree(root, num);
        insert_in_tree(root, b, num);
    }
    else{
        printf("\nNumber : %ld is not in node : %s\n",num,a->name);
    }
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Exchange Number <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
Route_Node *insert_in_head(Route_Node *head,Route_Node *nd){
    Route_Node *ptr=head,*prev = NULL;
    while (ptr) {
        prev = ptr;
        ptr = ptr->nxt;
    }
    if(!prev){
        head = nd;
    }
    else{
        prev->nxt=nd;
        nd->nxt=NULL;
    }
    return head;
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Route <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

Route_Node *Lowest_route(AVL_Node *root,int id_a,int id_b){
    AVL_Node *a = search_via_id(root, id_a);
    AVL_Node *b = search_via_id(root, id_b);
    Route_Node *head = NULL;
    AVL_Node *intersection = Lowest_router(a, b);
    if(intersection){
        AVL_Node *ptr = a;
        while (ptr!=intersection) {
            Route_Node *rnd = malloc(sizeof(Route_Node));
            strcpy(rnd->name, ptr->name);
            head = insert_in_head(head, rnd);
            ptr = ptr->parent;
        }
        while (ptr) {
            Route_Node *rnd = malloc(sizeof(Route_Node));
            strcpy(rnd->name, ptr->name);
            head = insert_in_head(head, rnd);
            if(b->id>ptr->id){
                ptr = ptr->right;
            }
            else{
                ptr = ptr->left;
            }
        }
    }
    else{
        printf("No route Found\n");
    }
    return head;
}


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Route <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
void print_tree(AVL_Node *root){
    if(!root){
        
    }
    else{
        print_tree(root->left);
        printf("The Node is : %s and its I.D is : %d --> ",root->name,root->id);
        print_tree(root->right);
    }
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Exchange Number end <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Main <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
Number_Set *residentSet(AVL_Node *root){
    Number_Set *ptr = &(root->numbers_in_node);
    return ptr;
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Main <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
/*                      ans 1
                is_Empty - 135
 */
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
/*                      ans 2
                num_in_tree() - 119
 */
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
/*                      ans 3
                insert_in_tree() - 216
 */
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
/*                      ans 4
                delete_from_tree() - 267
 */
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
/*                      ans 5
                residentSet - 626
 */
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
/*                      ans 6
                search() - 136
 */
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
/*                      ans 7
                Lowest_router() - 330
 */
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
/*                      ans 8
                Lowest_route - 573
 */
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
/*                      ans 9
                Exchange_Number()
 */

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Main <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Main <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

int main(void) {
    AVL_Node *root = NULL;
    printf("Enter The Number Of Leaves : \n");
    int lvs;
    scanf("%d",&lvs);
    int nodes;
    long int num;
    int id_a,id_b;
    nodes = 2*lvs;
    for(int i=0;i<nodes;i++){
        char nme[NAMESIZE];
        nme[0]='n';
        nme[1]='d';
        nme[2]=i+49;
        nme[3]='\0';
//        printf("Enter Name of Node : \n");
//        scanf("%s",nme);
        AVL_Node *ptr = malloc(sizeof(AVL_Node));
        init_AVL_Node(ptr);
        strcpy(ptr->name, nme);
        ptr->id=i+1;
        AVL_Insert(&root, ptr);
    }
    int choice=0;
    do{
        printf("\n1.To check if the station is empty or not\n2.To check if a number is a member of a station\n3.Insert A Number\n4.Delete a number\n5.Print Number Set\n6.To find the level 0 base station of a number\n7.To print the Lowest Routeer\n8.To print the route and store in a list\n9.To Exchange Number\n10.Exit\n");
        int ch;
        scanf("%d",&ch);
        switch (ch) {
            case 1:
                print_tree(root);
                printf("\nEnter The I.D of Node which is being checked\n");
                int id1;
                scanf("%d",&id1);
                AVL_Node *nd1 = search_via_id(root, id1);
                if(nd1){
                    if(!is_Empty(nd1)){
                        printf("The Node is Not Empty\n");
                    }
                    else{
                        printf("The Node Is Empty\n");
                    }
                }
                else{
                    printf("The Node Doesnot Exist\n");
                }
                break;
            case 2:
                print_leaves(root);
                printf("\nEnter the number and Id of Level 0 stations\n");
                int id2;
                long int num2;
                scanf("%d%ld",&id2,&num2);
                AVL_Node *nd2 = search_via_id(root, id2);
                if(num_in_Tree(nd2, num2)){
                    printf("The Number %ld is in the Node %s\n",num2,nd2->name);
                }
                else{
                    printf("The Number %ld is not in Node %s\n",num2,nd2->name);
                }
                break;
            case 3:
                printf("Enter Number : \n");
                scanf("%ld",&num);
                print_leaves(root);
                printf("\nEnter Id of Station : \n");
                int lvid;
                scanf("%d",&lvid);
                AVL_Node *nd = search_via_id(root, lvid);
                insert_in_tree(root, nd, num);
                printf("The Root is %s : \n",root->name);
                break;
            case 4:
                printf("Enter The Number you want to delete\n");
                scanf("%ld",&num);
                delete_from_tree(root, num);
                break;
            case 5:
                print_leaves(root);
                printf("\nEnter Id of the leaves\n");
                int id;
                scanf("%d",&id);
                AVL_Node *ptr = search_via_id(root, id);
                Number_Set *ns = residentSet(ptr);
                print_numbers_in_Node(ptr);
                break;
            case 6:
                printf("Enter the Number you want to find\n");
                scanf("%ld",&num);
                AVL_Node *nd6 = search(root, num);
                if(nd6){
                    printf("Name of the Base is : %s and its I.D is : %d\n",nd6->name,nd6->id);
                }
                else{
                    printf("The Number doesnot exist in the tree\n");
                }
                break;
            case 7:
                print_leaves(root);
                printf("Enter the I.D's of the base Stations (Note they must contain atleast 1 number)\n");
                scanf("%d%d",&id_a,&id_b);
                AVL_Node *a,*b;
                a = search_via_id(root, id_a);
                b = search_via_id(root, id_b);
                if(a && b){
                    AVL_Node *nd7 = Lowest_router(a, b);
                    if(nd7){
                        printf("The Lowest Router is : %s and its I.D is : %d\n",nd7->name,nd7->id);
                    }
                    else{
                        printf("Please Read the information clearly\n");
                    }
                }
                else{
                    printf("The Base Doesnot Exist\n");
                }
                break;
            case 8:
                printf("Enter id's \n");
                print_leaves(root);
                scanf("%d%d",&id_a,&id_b);
                printf("\n\n");
                Print_lowest_route(root, id_a, id_b);
                break;
            case 9:
                printf("Enter id's from where to where and number \n");
                long int exc_num;
                print_leaves(root);
                scanf("%d%d%ld",&id_a,&id_b,&exc_num);
                Exchange_Numbers(root, id_a, id_b, exc_num);
                break;
            case 10:
                choice = 1;
                break;
            default:
                printf("Invalid Choice\n");
                break;
        }
        
        
    }while(choice==0);
    
    return 0;
}
