//
//  main.c
//  dspd2assignment
//
//  Created by Official on 07/03/20.
//  Copyright © 2020 Official. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<ctype.h>


//>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

typedef struct Word{
    char start_alphabet;
    char word[30];
    int freq;
    struct Word *next_word;
} Word;

typedef struct Dict_Node{
    char start_alphabet;
    Word *alphabet_list;
    struct Dict_Node *nextDict_Node;
} Dict_Node;

typedef enum{
    FAILURE,SUCCESS
} Status_Code;

typedef struct MRL{
    int count;
    Word *MRU_list;
} MRL;

typedef struct {
    Word *last;
} Miss_spelled;

//>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

char* Stringlower(char *str){
    char *head;
    head = (char*)malloc(strlen(str));
    strcpy(head, str);
    unsigned long len = strlen(head);
    for(int i=0;i<len;i++){
        head[i]=tolower(head[i]);
    }
    
    return head;
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
void init_Misspelled(Miss_spelled *ms){
    ms->last=NULL;
}



//>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

Dict_Node* init_Dict(){
    Dict_Node *ptr,*prev,*head;
    prev = NULL;
    ptr = (Dict_Node*)malloc(sizeof(Dict_Node));
    if(!ptr){
        return NULL;
    }
    head = ptr;
    head->alphabet_list=NULL;
    head->start_alphabet='a';
    for(int i=1;i<26;i++){
        prev = ptr;
        ptr = (Dict_Node*)malloc(sizeof(Dict_Node));
        ptr->alphabet_list=NULL;
        ptr->start_alphabet='a' + i;
        prev->nextDict_Node=ptr;
    }
    ptr->nextDict_Node=NULL;
    return head;
    
}

void init_MRL(MRL *mrl){
    mrl->count=0;
    mrl->MRU_list=NULL;
}


//>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

Status_Code search_in_Dict(char *word,Dict_Node *dict){
    Status_Code ret_val=SUCCESS;
    char stword=tolower(*word);
    printf("Searching Dict with word %c  \n",stword);
    Dict_Node *ptr;
    ptr=dict;
    while(ptr->start_alphabet<stword){
        ptr=ptr->nextDict_Node;
    }
    Word *srch=ptr->alphabet_list;
    int fnd=0;
    while(srch && !fnd){
        if(strcmp(srch->word, word)==0){
            fnd=1;
        }
        else{
            srch = srch->next_word;
        }
    }
    if(!fnd){
        printf("Word not found inside dict \n");
        ret_val=FAILURE;
    }
    return ret_val;
}


//>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


Status_Code Insert_in_Dict(char *word,Dict_Node *head){
    char start_word=word[0];
    start_word = tolower(start_word);
    Dict_Node *ptr,*prev;
    ptr = head;
    prev = NULL;
    while(ptr->start_alphabet<start_word){
        ptr = ptr->nextDict_Node;
    }
    Word *wordptr = NULL,*wordprev;
    wordptr = ptr->alphabet_list;
    wordprev=NULL;
    if(!wordptr){
        printf("Wordptr is Null for word %s \n\n",word);
        wordptr = (Word*)malloc(sizeof(Word));
        wordptr->freq=1;
        strcpy(wordptr->word, word);
        wordptr->next_word=NULL;
        wordptr->start_alphabet=ptr->start_alphabet;
        ptr->alphabet_list=wordptr;
        
    }//if NO list of the word
    else{
        
        //while(strcmp(Stringlower(wordptr->word), Stringlower(word))<0){
        while(wordptr && strcasecmp(wordptr->word, word)<0){
            wordprev=wordptr;
            wordptr=wordptr->next_word;
            }
        if(wordptr==NULL){
            wordptr = (Word*)malloc(sizeof(Word));
                   wordptr->freq=1;
                   strcpy(wordptr->word, word);
                   wordptr->next_word=NULL;
                   wordptr->start_alphabet=ptr->start_alphabet;
                    wordprev->next_word=wordptr;
        }
        else{
            if(strcmp(wordptr->word,word)==0){
                wordptr->freq++;
            }
            else{
                if(word[0]>wordptr->word[0]){
                    if(wordptr->next_word){
                        if((strcmp(wordptr->next_word->word, word)!=0)){
                        Word *tmp = (Word*)malloc(sizeof(Word));
                        strcpy(tmp->word, word);
                        tmp->next_word=wordptr->next_word;
                        wordptr->next_word=tmp;
                        }//if word not found
                        else{
                            wordptr->next_word->freq++;
                        }
                    }//if next word exists
                    else{//next Word DNE
                        Word *tmp = (Word*)malloc(sizeof(Word));
                        strcpy(tmp->word, word);
                        tmp->next_word=wordptr->next_word;
                        tmp->freq=1;
                        wordptr->next_word=tmp;
                    }
                }
                else{//The
                    if(wordprev){
                        Word *tmp = (Word*)malloc(sizeof(Word));
                        strcpy(tmp->word, word);
                        tmp->next_word=wordptr;
                        tmp->freq=1;
                        wordprev->next_word=tmp;
                    }//if wordprev is not empty lower word is not present
                    else{
                        Word *tmp = (Word*)malloc(sizeof(Word));
                        strcpy(tmp->word, word);
                        tmp->next_word=wordptr;
                        tmp->freq=1;
                        ptr->alphabet_list=tmp;
                    }
                }
            }//strcmp not equal or big or small
        }
    }//If list Of Word Present
    return SUCCESS;
}



//>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
Status_Code inMisspelled(Miss_spelled *miss,char *word,Word **ans){
    if(miss->last==NULL){
        return FAILURE;
    }
    else{
        int fnd=0;
        if(strcmp(miss->last->word, word)==0){
            fnd = 1;
            *ans = miss->last;
        }
        Word *first=miss->last->next_word;
        while(first!=miss->last && !fnd){
            if(strcmp(first->word, word)==0){
                fnd=1;
                *ans = first;
            }
            else{
                first=first->next_word;
            }
        }
        if(!fnd){
            return FAILURE;
        }
        else{
            return SUCCESS;
        }
    }
}


void insert_mis(Miss_spelled *ms,char *word){
    if(ms->last==NULL){
        ms->last = (Word*)malloc(sizeof(Word));
        ms->last->freq=1;
        strcpy(ms->last->word, word);
        ms->last->next_word=ms->last;
        ms->last->start_alphabet=word[0];
    }
    else{
        Word *abc = NULL;
        if(inMisspelled(ms, word, &abc)){
            if(abc){
                abc->freq++;
            }
        }
        else{
            Word *tmp=(Word*)malloc(sizeof(Word));
            strcpy(tmp->word, word);
            tmp->freq=1;
            tmp->next_word=ms->last->next_word;
            ms->last->next_word=tmp;
            ms->last=tmp;
        }
    }
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//Word* sort(Word *list){
//    Word *retval=list;
//    Word *out,*in;
//    out=list;
//    while(out->next_word){
//        in=out->next_word;
//        while(in){
//            if(strcasecmp(out->word, in->word)<=0){
//                Word tmp=*in;
//                *in=*out;
//                *out=tmp;
//            }
//        }
//    }
//
//    return retval;
//}

//>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
Status_Code is_present_MRL(MRL *mrl,char *word,Word **ans){
    Word *ptr;
    ptr=mrl->MRU_list;
    //>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    if(ptr){
        printf("Word is %s \n",ptr->word);
    }
    //>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    int fnd=0;
    while(ptr && !fnd){
        if(strcmp(ptr->word, word)==0){
            fnd=1;
            *ans = ptr;
            printf("The Word is %s (Inside ispresent mrl)\n",ptr->word);
        }
        else{
            ptr=ptr->next_word;
        }
    }
    if(fnd==1){
        return SUCCESS;
    }
    else{
        *ans=NULL;
        return FAILURE;
    }
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


void increment(MRL *mrl,char *word){
    Word *ptr = NULL;
    if(is_present_MRL(mrl, word, &ptr)==SUCCESS){
        if(ptr){
            ptr->freq++;
        }
    }
}

 //>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

//>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
void insert_MRU(MRL *mrl,char *word,Dict_Node *dict,Miss_spelled *miss){
    Word *tmp = NULL;
    if(is_present_MRL(mrl, word, &tmp)==SUCCESS){
        printf("Word Found in Mrl\n");
        increment(mrl, word);
        Word *ptr=mrl->MRU_list;
        Word *prev=NULL;
        while(ptr!=tmp && ptr){
            prev = ptr;
            ptr=ptr->next_word;
        }
        if(!prev){
            
        }
        else{
            prev->next_word=ptr->next_word;
            ptr=mrl->MRU_list;
            mrl->MRU_list=ptr;
        }
    }
    else{//Not Found in Mrl
        if(search_in_Dict(word, dict)){
            if(mrl->count<10){
                printf("Word found in dict and count < 10 \n");
                Word *new=(Word*)malloc(sizeof(Word));
                new->freq=1;
                new->start_alphabet=tolower(word[0]);
                mrl->count++;
                strcpy(new->word, word);
                new->next_word=mrl->MRU_list;
                mrl->MRU_list=new;
                if(mrl->count==1){
                    mrl->MRU_list->next_word=NULL;
                }
            }
            else{
                printf("Word found in dict and count = 10 \n");
                Word *new=(Word*)malloc(sizeof(Word));
                new->freq=1;
                new->start_alphabet=word[0];
                strcpy(new->word, word);
                new->next_word=mrl->MRU_list;
                mrl->MRU_list=new;
                Word *ptr=mrl->MRU_list,*prev=NULL;
                while(ptr->next_word){
                    prev=ptr;
                    ptr=ptr->next_word;
                }
                free(ptr);
                prev->next_word=NULL;
            }
        }//Found in dict
        else{//not found in dict => misspelled
            printf("Word not found and inserting in mis \n");
            insert_mis(miss, word);
            
        }
        
        
    }
}



//>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


void print_dict(Dict_Node *head){
    while(head){
        Word *ptr;
        ptr=head->alphabet_list;
        printf("The words Starting From %c are : \n",head->start_alphabet);
        while(ptr){
            printf(" %s ,",ptr->word);
            ptr=ptr->next_word;
        }
        printf("\n\n");
        head=head->nextDict_Node;
    }
}


void display_MRU(MRL mrl){
    Word *iw = NULL;
    Word *out,*in;
    out = mrl.MRU_list;
    while(out){
            in=out->next_word;
            while(in){
                if(strcasecmp(out->word, in->word)>0){
                    Word tmp;
                    tmp.freq=in->freq;
                    tmp.start_alphabet=in->start_alphabet;
                    strcpy(tmp.word, in->word);
                    in->freq=out->freq;
                    in->start_alphabet=out->start_alphabet;
                    strcpy(in->word, out->word);
                    out->freq=tmp.freq;
                    out->start_alphabet=tmp.start_alphabet;
                    strcpy(out->word, tmp.word);
                }
                in = in->next_word;
            }
        out = out->next_word;
        }
    
    iw = mrl.MRU_list;
    int i=0;
    while(iw){
        char ans[30];
        strcpy(ans , iw->word);
        printf("The %d Word is : < ",i+1);
        printf("%s > ",ans);
        printf("And its frequency is : %d\n",iw->freq);
        iw=iw->next_word;
        i++;
    }
}


void display_misspelled(Miss_spelled msp){
    if(msp.last){
        Word *ptr=msp.last->next_word;
        msp.last->next_word=NULL;
        Word *in,*out;
        out = ptr;
        while(out){
                in=out->next_word;
                while(in){
                    if(strcasecmp(out->word, in->word)>0){
                        Word tmp;
                        tmp.freq=in->freq;
                        tmp.start_alphabet=in->start_alphabet;
                        strcpy(tmp.word, in->word);
                        in->freq=out->freq;
                        in->start_alphabet=out->start_alphabet;
                        strcpy(in->word, out->word);
                        out->freq=tmp.freq;
                        out->start_alphabet=tmp.start_alphabet;
                        strcpy(out->word, tmp.word);
                    }
                    in = in->next_word;
                }
            out = out->next_word;
            }
        while (ptr) {
            char ans[30];
            strcpy(ans, ptr->word);
            printf("The Word is : < ");
            printf("%s > ",ans);
            printf("And its frequency is : %d\n",ptr->freq);
            ptr=ptr->next_word;

        }
    }
}







int main(int argc,const char **argv) {
    
    Dict_Node *dict = init_Dict();
    
    Miss_spelled miss;
    MRL RecentList;
    init_MRL(&RecentList);
    display_MRU(RecentList);
    init_Misspelled(&miss);
    
    FILE *dictionary=fopen(argv[1],"r");
    FILE *file = fopen(argv[2],"r");

    char filecontents[1000];
    char word[100];
    if(!dictionary){
        printf("no and %s , %s \n",argv[1],argv[2]);
        if(!file){
            printf("2nd File dno \n");
        }
        exit(1);
    }
    while(fgets(word, 100, dictionary)!=NULL){
        int ctr=0;
        int prev=0;
        while(word[ctr]!='\n'){
            prev=ctr;
            ctr++;
        }
        word[ctr]='\0';
        Insert_in_Dict(word, dict);
        }
    print_dict(dict);
    while(fgets(filecontents, 1000, file)!=NULL){
        int ctr=0;
        printf("Inside Scanning\n");
        while(filecontents[ctr]!='\0'){
            char word[100];
            int wc=0;
            int chk;
            while((chk=(filecontents[ctr]!=' ' && filecontents[ctr]!='\0' && filecontents[ctr]!='-'&&filecontents[ctr]!='\0'))){
                if(filecontents[ctr]=='.'||filecontents[ctr]=='!'||filecontents[ctr]=='?'||filecontents[ctr]==';'||filecontents[ctr]==','||filecontents[ctr]=='"'||filecontents[ctr]=='\n'){
                    ctr++;
                    break;
                }
                else{
                    word[wc]=filecontents[ctr];
                    wc++;
                    ctr++;
                }
            }
            if(wc!=0){
            word[wc]='\0';
                printf("About to insert in mru\n");
                printf(" >>>>>>>>>>>>>>>>. %s <<<<<<<<<<<<<<<\n\n",word);
            insert_MRU(&RecentList, word, dict,&miss);
                printf("Inserted in Mru\n");
            }
            if(!chk){
                ctr++;
            }
        }

    }
    
    int t=0;
    printf("\n\n\n\n\n\n\n\n");
    do{
        printf("\n\n*****WELCOME*****\n");
        printf("Press 1 to show Dictionary\n");
        printf("Press 2 to show Most Recently Used Words\n");
        printf("Press 3 to show Miss-spelled words\n");
        printf("Press 4 to exit\n");
        int choice;
        scanf("%d",&choice);
        switch (choice) {
            case 1:
                print_dict(dict);
                break;
            case 2:
                display_MRU(RecentList);
                break;
            case 3:
                printf("The missspelled list is :-> \n");
                display_misspelled(miss);
                break;
            case 4:
                t=1;
                break;
            default:
                printf("Invalid Choice \n");
                break;
        }
        
    }while(!t);
    
    fclose(file);
    fclose(dictionary);
    return 0;
    
}
