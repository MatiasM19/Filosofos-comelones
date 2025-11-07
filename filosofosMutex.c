#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int comida = 6; //La cantidad de comida que hay en cada plato

struct filosofo{
    char * nombre;
    int cantComida;
    struct tenedor * ten1;
    struct tenedor * ten2;
};

struct tenedor{
    int estado; // 0 significa esta desocupado, 1 significa esta ocupado
};

void * comer( void * h1)
{
    struct filosofo * fil;
    fil = (struct filosofo*) h1;
    pthread_mutex_lock( &mutex );
    printf("%s %s \n", fil->nombre, "esta pensando");

    while(fil->cantComida > 0){
        if(fil->ten1->estado == 0 && fil->ten2->estado == 0){/////Si los 2 tenedroes estan libres puede comer
            printf("%s %s \n", fil->nombre, "tiene hambre");
            fil->ten1->estado = fil->ten2->estado = 1; //El filosof agarra los tenedores
            printf("%s %s \n", fil->nombre, "agarro los 2 tenedores");
            while(fil->cantComida > 0){
                fil->cantComida--;
                printf("%s %s \n", fil->nombre, "esta comiendo");
            }
        }
        else{
            printf("%s %s \n", fil->nombre, "no puede comer");
        }
    } 

    fil->ten1->estado = fil->ten2->estado = 0; ///En caso de llegar aca es porque ya termino de comer, por lo tanto, libera los tenedores
    printf("%s %s \n", fil->nombre, "termino de comer");
    pthread_mutex_unlock( &mutex );

}



int main() {
     pthread_t thread1, thread2,thread3,thread4,thread5;  //Se declaran los dos hilos
     
     struct tenedor * ten1 = (struct tenedor *) malloc (sizeof(struct tenedor));
     struct tenedor * ten2 = (struct tenedor *) malloc (sizeof(struct tenedor));
     struct tenedor * ten3 = (struct tenedor *) malloc (sizeof(struct tenedor));
     struct tenedor* ten4 = (struct tenedor *) malloc (sizeof(struct tenedor));
     struct tenedor * ten5 = (struct tenedor *) malloc (sizeof(struct tenedor));
     struct filosofo * fil1 = (struct filosofo *) malloc (sizeof(struct filosofo));
     struct filosofo* fil2 = (struct filosofo *) malloc (sizeof(struct filosofo));
     struct filosofo * fil3 = (struct filosofo *) malloc (sizeof(struct filosofo));
     struct filosofo * fil4 = (struct filosofo *) malloc (sizeof(struct filosofo));
     struct filosofo * fil5 = (struct filosofo *) malloc (sizeof(struct filosofo));

     ten1->estado = ten2->estado = ten3->estado = ten4->estado = ten5->estado = 0; ////Todos los tenedores desocupados

     fil1->nombre = "Platon";
     fil1->cantComida = comida;
     fil1->ten1 = ten1;
     fil1->ten2 = ten2;

     fil2->nombre = "Descartes";
     fil2->cantComida = comida;
     fil2->ten1 = ten2;
     fil2->ten2 = ten3;

     fil3->nombre = "Nietsche";
     fil3->cantComida = comida;
     fil3->ten1 = ten3;
     fil3->ten2 = ten4;

     fil4->nombre = "Hegel";
     fil4->cantComida = comida;
     fil4->ten1 = ten4;
     fil4->ten2 = ten5;

     fil5->nombre = "Aristoteles";
     fil5->cantComida = comida;
     fil5->ten1 = ten5;
     fil5->ten2 = ten1;

 
     int  iret1, iret2,iret3,iret4,iret5;
 
     iret1 = pthread_create( &thread1, NULL, comer, (void*) fil1);
     iret2 = pthread_create( &thread2, NULL, comer, (void*) fil2);
     iret3 = pthread_create( &thread3, NULL, comer, (void*) fil3);
     iret4 = pthread_create( &thread4, NULL, comer, (void*) fil4);
     iret5 = pthread_create( &thread5, NULL, comer, (void*) fil5);

     pthread_join( thread1, NULL);
     pthread_join( thread2, NULL);
     pthread_join( thread3, NULL);
     pthread_join( thread4, NULL);
     pthread_join( thread5, NULL);
 
     printf("Thread 1 returns: %d\n",iret1);
     printf("Thread 2 returns: %d\n",iret2);
     printf("Thread 3 returns: %d\n",iret3);
     printf("Thread 4 returns: %d\n",iret4);
     printf("Thread 5 returns: %d\n",iret5);
     return 0;
}


