#include <stdio.h>
#include <stdlib.h>

/* Coada */

typedef struct coada {
    int inf;
    struct coada *urm;
};

void pushc(int a,struct coada **p)
{
    struct coada *t=*p,*q=(struct coada*)malloc(sizeof(struct coada));
    q->inf=a;
    q->urm=NULL;
    if (!t) *p=q;
        else {
            while (t->urm!=NULL) t=t->urm;
            t->urm=q;
        }
}

void popc(struct coada **p)
{
    struct coada *q=*p;
    if (q) {
    *p=q->urm;
    free(q);
    }
}

/* Stiva */

typedef struct stiva{
    int inf;
    struct stiva *urm;
};

void pushs(int a,struct stiva **p)
{
    struct stiva *q=(struct stiva *)malloc(sizeof(struct stiva));
    q->inf=a;
    q->urm=*p;
    *p=q;
}

void pops(struct stiva **p)
{
    struct stiva *q=*p;
    if (q) {
    *p=q->urm;
    free(q);
    }
}

/* Algoritmi grafuri neorientate */

void citire(int *n,int a[100][100])
{
    printf("n(numar de noduri)=");scanf("%d",n);
    int m,i,j,x,y;
    for (i=0;i<*n;i++) for (j=0;j<*n;j++) a[i][j]=0;
    printf("numar de muchii=");scanf("%d",&m);
    for (i=0;i<m;i++) {
        do {
        printf("primul nod=");scanf("%d",&x);
        printf("al doilea nod=");scanf("%d",&y);
        } while (x<0 && x>=*n && y<0 && y>=*n);
        a[x][y]=a[y][x]=1;
    }
    //Am ales citirea grafului prin citirea muchiilor pentru a ne misca mai repede.Altfel trebuiau introduse n*n valori
}

void df(int x,int n,int a[100][100])
{
    struct stiva *p=NULL;
    int i,y,*v=malloc(n*sizeof(int)); //v reprezinta vectorul care retine daca un nod a fost sau nu vizitat
    for (i=0;i<n;i++) v[i]=0;
    pushs(x,&p);
    while (p!=NULL) {
        y=p->inf;
        pops(&p);
        if (v[y]==0) {
            printf("%d ",y);
            v[y]=1;
            for (i=n-1;i>=0;i--) if (a[y][i]==1) pushs(i,&p); //parcurgere de la dreapta la stanga pentru ca varful stivei sa fie ales cel mai mic nod ca si valoare
        }
    }
    printf("\n");
}

void bf(int x,int n,int a[100][100])
{
    struct coada *p=NULL;
    int i,y,*v=malloc(n*sizeof(int));
    for (i=0;i<n;i++) v[i]=0;
    pushc(x,&p);
    while (p!=NULL) {
        y=p->inf;
        popc(&p);
        if (v[y]==0) {
            printf("%d ",y);
            v[y]=1;
            for (i=0;i<n;i++) if (a[y][i]==1) pushc(i,&p); //parcurgere de la stanga la dreapta datorita structurii de coada
        }
    }
    printf("\n");
}

void compconex(int n,int a[100][100])
{
    struct coada *p=NULL;
    int j,i,y,*v=malloc(n*sizeof(int));
    for (i=0;i<n;i++) v[i]=0;
    for (j=0;j<n;j++)
    if (v[j]==0) {
        printf("{");
        pushc(j,&p);
        while (p!=NULL) {
            y=p->inf;
            popc(&p);
            if (v[y]==0) {
                printf("%d ",y);
                v[y]=1;
                for (i=0;i<n;i++) if (a[y][i]==1) pushc(i,&p);
            }
        }
        printf("}");
    }
    printf("\n");
}

int** roywarshall(int n,int a[100][100])
{
    int i,j,k,**b=malloc(n*sizeof(int *));
    for (i=0;i<n;i++) b[i]=calloc(n,sizeof(int));
    for (i=0;i<n;i++)
        for (j=0;j<n;j++)
            b[i][j]=a[i][j];
    for(k=0;k<n;k++)
        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
                if(b[i][j]==0 && i!=k && j!=k)
                    b[i][j]=b[i][k]*b[k][j];
    return b;
}

void afisaremat(int n,int **b)
{
    int i,j;
    for (i=0;i<n;i++) {
        for (j=0;j<n;j++)
            printf("%d ",b[i][j]);
        printf("\n");
    }
    printf("\n");
}

int menu()
{
    int opt;
    printf("Alegeti una dintre optiunile:\n0.Citire matrice graf nou.\n1.Parcurgere in adancime\n2.Parcurgere in latime\n3.Determinare componente conexe\n4.Determinarea matricii drumurilor\n5.Exit\n");
    scanf("%d",&opt);
    return opt;
}

int main()
{
    int opt,x,n,a[100][100],**b;
    printf("\tObservatie! Nodurile grafului reprezinta valori consecutive incepand \ncu 0 si pana la n-1 inclusiv.\n\n");
    citire(&n,a);
    do {
        opt=menu();
        switch (opt)
        {
        case 0:
            citire(&n,a);
            break;
        case 1:
            printf("Introduceti nodul de pornire:");scanf("%d",&x);
            df(x,n,a);
            break;
        case 2:
            printf("Introduceti nodul de pornire:");scanf("%d",&x);
            bf(x,n,a);
            break;
        case 3:
            printf("Componentele conexe ale grafului sunt:\n");
            compconex(n,a);
            break;
        case 4:
            printf("Matricea drumurilor:\n");
            b=roywarshall(n,a);
            afisaremat(n,b);
            break;
        case 5:
            break;
        default: break;
        }
    } while (opt!=5);
    return 0;
}
