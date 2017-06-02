#include<stdio.h>
#include<stdlib.h>
struct student
{
        int s_rno;
        int password;
        struct student *nextstudent;
        struct friendpointer  *nextfriendpointer;
};
//---------------------------------------------------------------------------------
struct student *start=NULL,*temp;
struct friendpointer *fptemp;
struct student *login_pointer;
struct student *search_pointer;
//---------------------------------------------------------------------------------
struct friendpointer
{
        struct student *nextfriend;
        struct friendpointer *nextfriendpointerfp;
};
//---------------------------------------------------------------------------------
void create_account()
{
        struct student *s, *s1, *end;
        int s_roll;
        int pass;

        if(start==NULL)
        {
            temp=(struct student *)malloc(sizeof(struct student));
            printf("\n\nEnter Your Unique Roll Number : ");
            scanf("%d",&(temp->s_rno));
            printf("\n\nEnter Password : ");
            scanf("%d",&(temp->password));
            temp->nextstudent=NULL;
            temp->nextfriendpointer=NULL;
            start=temp;
            return;
        }
        if(start!=NULL)
        {
            printf("\n\nEnter Your Unique Roll Number : ");
            scanf("%d",&s_roll);
            s=start;
            while(s!=NULL && s->s_rno!=s_roll)
            {
                s=s->nextstudent;
            }

            if(s!=NULL)
            {
                printf("\n\nRoll number %d already exists",s_roll);
                return;
            }
            temp=(struct student *)malloc(sizeof(struct student));
            temp->s_rno=s_roll;
            printf("\n\nEnter Password : ");
            scanf("%d",&(temp->password));
            s1=start;
            while(s1->nextstudent!=NULL)
            {
                s1=s1->nextstudent;
            }
            temp->nextstudent=NULL;
            s1->nextstudent=temp;
            temp->nextfriendpointer=NULL;
        }
}
//---------------------------------------------------------------------------------
void login()
{
    struct student *p;
    int s_rno1;
    int password1;
    printf("\n\nEnter your roll number : ");
    scanf("%d",&s_rno1);
    login_pointer=start;
    while(login_pointer!=NULL && login_pointer->s_rno!=s_rno1)
    {
        login_pointer=login_pointer->nextstudent;
    }
    if(login_pointer==NULL)
    {
        printf("\n\nEnter correct roll number");
        return;
    }
    printf("\n\nEnter your password : ");
    scanf("%d",&password1);
    if(login_pointer->password!=password1)
    {
        printf("\n\nEnter correct password");
        return;
    }
    login_display();
}
//---------------------------------------------------------------------------------
void login_display()
{

    int logdisch;
    do{
        printf("\n\n1 : SEARCH OTHER STUDENTS");
        printf("\n\n2 : DISPLAY FOLLOWING");
        printf("\n\n3 : PERSONAL SETTINGS");
        printf("\n\n4 : LOGOUT");
        printf("\n\nEnter your choice : ");
        scanf("%d",&logdisch);
        switch(logdisch)
        {
            case 1:
            {
                search_student();
                break;
            }
            case 2:
            {
                display();
                break;
            }
            case 3:
            {
                personal_settings();
                break;
            }
            case 4:
            {
                logout();
                break;
            }
            default :
            {
                login_display();
                break;
            }
        }
    }while(logdisch!=6);
}
//---------------------------------------------------------------------------------


void search_student()
{
    search_pointer=NULL;
    int s_rno1;
    printf("\n\nEnter the roll number of the student you want to search : ");
    scanf("%d",&s_rno1);
    search_pointer=start;
    while(search_pointer!=NULL && search_pointer->s_rno!=s_rno1)
    {
        search_pointer=search_pointer->nextstudent;
    }
    if(search_pointer==NULL)
    {
        printf("\n\nStudent not found");
        return;
    }
    if(login_pointer->s_rno==search_pointer->s_rno)
    {
        printf("\n\nCant search yourself");
        return;
    }
    printf("\n\nStudent found.");
    search_student_display();
}
//---------------------------------------------------------------------------------

void search_student_display()
{
    int searchch;
    do{
        printf("\n\n1 : FOLLOW");
        printf("\n\n2 : UNFOLLOW");
        printf("\n\n3 : BACK");
        printf("\n\nEnter your choice : ");
        scanf("%d",&searchch);
        switch(searchch)
        {
            case 1:
            {
                follow();
                break;
            }
            case 2:
            {
                unfollow();
                break;
            }
            case 3:
            {
                login_display();
                break;
            }
            default :
            {
                search_student_display();
                break;
            }
        }

    }while(searchch!=5);
}
//---------------------------------------------------------------------------------
void follow()
{
    struct friendpointer *p, *p1;
    if(login_pointer->nextfriendpointer==NULL)
    {
        fptemp=(struct friendpointer *)malloc(sizeof(struct friendpointer));
        login_pointer->nextfriendpointer=fptemp;
        fptemp->nextfriendpointerfp=NULL;
        fptemp->nextfriend=search_pointer;
        printf("\n\nFollowing");
        return;
    }
    p=login_pointer->nextfriendpointer;
    while(p!=NULL && (p->nextfriend)!=search_pointer)
    {
        p1=p;
        p=p->nextfriendpointerfp;
    }
    if(p==NULL)
    {
        fptemp=(struct friendpointer *)malloc(sizeof(struct friendpointer));
        p1->nextfriendpointerfp=fptemp;
        fptemp->nextfriendpointerfp=NULL;
        fptemp->nextfriend=search_pointer;
        printf("\n\nFollowing");
        return;
    }
    if(p!=NULL)
    {
        printf("\n\nAlready Following");
        return;
    }
}
//---------------------------------------------------------------------------------
void unfollow()
{
    struct friendpointer *p, *p1, *pro;
    if(login_pointer->nextfriendpointer==NULL)
    {
        printf("\n\nAlready unfollowing");
        return;
    }
    p=login_pointer->nextfriendpointer;
    if((login_pointer->nextfriendpointer)->nextfriend==search_pointer)
    {
        login_pointer->nextfriendpointer=p->nextfriendpointerfp;
        p->nextfriend=NULL;
        p->nextfriendpointerfp=NULL;
        free(p);
        printf("\n\nUnfollowed");
        return;
    }
    pro=login_pointer->nextfriendpointer;
    while(p!=NULL && p->nextfriend!=search_pointer)
    {
        p1=p;
        p=p->nextfriendpointerfp;
    }
    if(p==NULL)
    {
        printf("\n\nAlready Unfollowing");
        return;
    }
    p1->nextfriendpointerfp=p->nextfriendpointerfp;
    p->nextfriend=NULL;
    p->nextfriendpointerfp=NULL;
    free(p);
    printf("\n\nUnfollowed");
    return;
}
//---------------------------------------------------------------------------------
void display()
{
    struct friendpointer *p, *p1;
    if(login_pointer->nextfriendpointer==NULL)
    {
        printf("\n\nNO Following");
        return;
    }
    p=login_pointer->nextfriendpointer;
    printf("\n\n");
    while(p->nextfriendpointerfp!=NULL)
    {
        printf("%d ",(p->nextfriend)->s_rno);
        p=p->nextfriendpointerfp;
    }
    printf("%d ",(p->nextfriend)->s_rno);
}
//---------------------------------------------------------------------------------
void personal_settings()
{
    int psch;
    do{
        printf("\n\n1 : CHANGE PASSWORD");
        printf("\n\n2 : DELETE ACCOUNT");
        printf("\n\n3 : BACK");
        printf("\n\nEnter your choice : ");
        scanf("%d",&psch);
        switch(psch)
        {

            case 1:
            {
                change_pass();
                break;
            }
            case 2:
            {
                delete_acc();
                break;
            }
            case 3:
            {
                login_display();
                break;
            }
            default :
            {
                personal_settings();
                break;
            }
        }
    }while(psch!=5);
}
//---------------------------------------------------------------------------------

void change_pass()
{
    int password1;
    printf("\n\nEnter your current password : ");
    scanf("%d",&password1);
    if(login_pointer->password!=password1)
    {
        printf("\n\nEnter correct password");
        change_pass();
    }
    printf("\n\nEnter new password : ");
    scanf("%d",&(login_pointer->password));
    printf("\n\nPassword successfully changed");
    return;

}
//---------------------------------------------------------------------------------
void delete_acc()
{
    struct student *p,*p1,*p2;
    p=login_pointer;
    if(login_pointer==start)
    {
        start=start->nextstudent;
        login_pointer=NULL;
        p->nextfriendpointer=NULL;
        p->nextstudent=NULL;
        free(p);
        main();
    }
    p2=start;
    while(p2!=login_pointer)
    {
        p1=p2;
        p2=p2->nextstudent;
    }
    p1->nextstudent=p2->nextstudent;
    login_pointer=NULL;
    p2->nextfriendpointer=NULL;
    p2->nextstudent=NULL;
    free(p2);
    main();

}
//---------------------------------------------------------------------------------
void logout()
{
    printf("\n\nSuccessfully logged out.");
    login_pointer=NULL;
    main();
}
//---------------------------------------------------------------------------------
void main()
{
    int n;
    do{
        printf("\n\n************* WELCOME TO INSTAGRAM *************");
        printf("\n\n1 : CREATE ACCOUNT");
        printf("\n\n2 : LOGIN");
        printf("\n\n3 : EXIT\n");
        printf("\n\nEnter your choice : ");
        scanf("%d",&n);
        switch(n)
        {
            case 1:
            {
                create_account();
                break;
            }
            case 2:
            {
                login();
                break;
            }
            case 3:
            {
                break;
            }
            default :
            {
                main();
                break;
            }

        }

    }while(n!=3);

}
