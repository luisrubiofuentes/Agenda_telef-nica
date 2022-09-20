//Rubio Fuentes, Luis
//Gonzalez Gomez, Jorge

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#define MAX_CAD 100

struct persona{
    char nombre[MAX_CAD];
    char apellidos[MAX_CAD];
    unsigned long telefono;
    char email[MAX_CAD];
};

void lower(char texto[]);
void ordenar(struct persona agenda[], int capacidad); //Ordena alfabeticamente (a-z)
int insertarPersona(struct persona agenda[], int capacidad, struct persona nuevo); //Busca un hueco libre, si lo hay guarda el contacto nuevo
void inicializarAgenda(struct persona agenda[],int capacidad);//Llena todos los espacios del array agenda[] con ? si no hay un contacto
void listarAgenda(struct persona agenda[], int capacidad);//Muestra todos los contactos de la agenda de forma ordenada
struct persona buscarPersona(struct persona agenda[], int capacidad, char nombre[]);//Muestra el primer contacto que coincide con el nombre que se busca
int borrarPersona(struct persona agenda[], int capacidad, char nombre[]);//Borra todos los contactos con el mismo nombre que se da y tambien ordena los contactos
int cargarAgenda(struct persona agenda[]);//Carga en agenda[] los contactos que haya en el fichero agenda.txt
int actualizarAgenda(struct persona agenda[], int capacidad);//Al terminar el programa carga en agenda.txt el resultado final de agenda[]

int main(){
    char buscar[MAX_CAD], borrar[MAX_CAD];
    struct persona agenda[MAX_CAD];
    struct persona nuevo;
    char opcion[MAX_CAD];
    int borrado=0;


    inicializarAgenda(agenda, MAX_CAD);
    do{
        char ch;
        printf("\n1.Insertar contacto\n2.Buscar contacto\n3.Listar agenda\n4.Borrar contacto\n5.Salir\nIntroduce opcion: ");
        fflush(stdin);
        scanf("%s",opcion);
        while((ch = getchar()) != '\n' && ch != EOF){;} //limpia el buffer

        if(strcmp(opcion, "1")==0){                      //Recoge los datos de un nuevo contacto
            printf("Introduce nombre: ");
            gets(nuevo.nombre);
            printf("Introduce apellidos: ");
            gets(nuevo.apellidos);
            printf("Introduce telefono: ");
            fflush(stdin);
            scanf("%lu",&nuevo.telefono);
            printf("Introduce email: ");
            fflush(stdin);
            scanf("%s", nuevo.email);

            if(insertarPersona(agenda,MAX_CAD,nuevo)==1){
                printf("\nSe ha podido insertar el contacto\n");
            }else{                                              //Indica que no habia espacio para otro contacto
                printf("\nNo se ha podido insertar el contacto\n");
            }
        }else if(strcmp(opcion, "2")==0){
            printf("Introducir nombre a buscar: ");
            fflush(stdin);
            scanf("%s", buscar);
            struct persona buscado = buscarPersona(agenda, MAX_CAD, buscar);
            printf("\n%s, %s %lu\t%s\n", buscado.apellidos, buscado.nombre, buscado.telefono, buscado.email);
        }else if(strcmp(opcion, "3")==0){
            listarAgenda(agenda, MAX_CAD);
        }else if(strcmp(opcion, "4")==0){
            printf("Introducir contacto a borrar: ");
            fflush(stdin);
            scanf("%s",borrar);
            borrado = borrarPersona(agenda, MAX_CAD, borrar);
            if(borrado>0){
                printf("\n%d contacto(s) eliminado(s)\n", borrado);
            }else{
                printf("\nEl contacto no existe\n");
            }
        }
    }while(strcmp(opcion, "5")!=0);

    if(actualizarAgenda(agenda, MAX_CAD)==1){
        printf("\nAgenda guardada correctamente\n\n");
    }else{
        printf("\nERROR: Agenda no guardada\n");
    }
}



void inicializarAgenda(struct persona agenda[],int capacidad){
    int cont_cargados = cargarAgenda(agenda);

    for(int i=cont_cargados ; i<capacidad ; i++){
        strcpy(agenda[i].nombre, "?");
        strcpy(agenda[i].apellidos, "?");
        agenda[i].telefono = 0;
        strcpy(agenda[i].email, "?");
    }
}


int insertarPersona(struct persona agenda[],int capacidad,struct persona nuevo){
    int i=0, exito=0;
    char nombreauxiliar[MAX_CAD];
    char apellidosauxiliar[MAX_CAD];
    unsigned long telefonoauxiliar=0;
    char emailauxiliar[MAX_CAD];

    while(exito==0 && i<capacidad){                                            //Busca una posicion vacia en la agenda
        if(agenda[i].apellidos[0] == '?' && i < capacidad){

            strcpy(agenda[i].nombre, nuevo.nombre);
            strcpy(agenda[i].apellidos, nuevo.apellidos);
            agenda[i].telefono = nuevo.telefono;
            strcpy(agenda[i].email, nuevo.email);
            exito=1;

        }else{
            exito=0;
            i++;
        }
    }
    for(int k=0 ; k<capacidad && agenda[k].apellidos[0]!='?' ; k++){
        for(int j=k+1 ; j<capacidad && agenda[j].apellidos[0]!='?' ; j++){
            int tam1 = strlen(agenda[k].apellidos);
            int tam2 = strlen(agenda[j].apellidos);
            char ape[tam1];
            char ape2[tam2];
            strcpy(ape, agenda[k].apellidos);
            lower(ape);
            strcpy(ape2, agenda[j].apellidos);
            lower(ape2);

            if((strcmp(ape, ape2)>0) && agenda[j].apellidos[0]!='?'){

                strcpy(nombreauxiliar,agenda[k].nombre);
                strcpy(agenda[k].nombre,agenda[j].nombre);
                strcpy(agenda[j].nombre,nombreauxiliar);

                strcpy(apellidosauxiliar,agenda[k].apellidos);
                strcpy(agenda[k].apellidos,agenda[j].apellidos);
                strcpy(agenda[j].apellidos,apellidosauxiliar);

                telefonoauxiliar = agenda[k].telefono;
                agenda[k].telefono = agenda[j].telefono;
                agenda[j].telefono = telefonoauxiliar;

                strcpy(emailauxiliar,agenda[k].email);
                strcpy(agenda[k].email,agenda[j].email);
                strcpy(agenda[j].email,emailauxiliar);
            }else if(strcmp(ape,ape2)==0 && agenda[j].apellidos[0]!='?'){
                int tam_1=strlen(agenda[k].apellidos);
                int tam_2=strlen(agenda[j].apellidos);
                char nom_1[tam_1];
                char nom_2[tam_2];
                strcpy(nom_1, agenda[k].nombre);
                lower(nom_1);
                strcpy(nom_2, agenda[j].nombre);
                lower(nom_2);
                if(strcmp(nom_1,nom_2)>0){

                    strcpy(nombreauxiliar,agenda[k].nombre);
                    strcpy(agenda[k].nombre,agenda[j].nombre);
                    strcpy(agenda[j].nombre,nombreauxiliar);

                    strcpy(apellidosauxiliar,agenda[k].apellidos);
                    strcpy(agenda[k].apellidos,agenda[j].apellidos);
                    strcpy(agenda[j].apellidos,apellidosauxiliar);

                    telefonoauxiliar = agenda[k].telefono;
                    agenda[k].telefono = agenda[j].telefono;
                    agenda[j].telefono = telefonoauxiliar;

                    strcpy(emailauxiliar,agenda[k].email);
                    strcpy(agenda[k].email,agenda[j].email);
                    strcpy(agenda[j].email,emailauxiliar);
                }
            }
        }
    }

    return exito;
}


void lower(char texto[]){
    int longitud = strlen(texto);
    for(int i=0 ; i<longitud ; i++)
        texto[i] = tolower(texto[i]);
}



struct persona buscarPersona(struct persona agenda[], int capacidad, char nombre[]){

    int x=0, i=0, correcto=0, confirm=0;
    int lon=strlen(nombre);             //Longitud del nombre a buscar
    int lon2=0;
    char nom[lon], nom2[lon];
    struct persona informacion ={
            "?",
            "?",
            0,
            "?"
        };

    strcpy(nom,nombre);                 //Copiamos el nombre original en otra variable para variar la copia
    lower(nom);
    while(x<capacidad && correcto==0){
        lon2=strlen(agenda[x].nombre);
        if(lon==lon2){                  //Solo si la palabra a buscar y la que comprueba en ese momento de la agenda tienen el mismo tamaño sigue con la comprobacion
            strcpy(nom2,agenda[x].nombre);//Se guarda en la variable nom2 para no variar la palabra original
            lower(nom2);
            while(confirm>=i && confirm<lon){   //Comprueba letra a letra si son iguales
                if(nom[i]==nom2[i]){            //Cuenta cada vez que coinciden en una letra
                    confirm++;
                }
                i++;
            }
            if(confirm==lon){                   //Si coinciden en todas las letras la imprime y termina
                correcto++;
            }else{
                x++;
                i=0;
            }
        }else{
            x++;
        }
    }
    if(correcto!=0){
        strcpy(informacion.nombre,agenda[x].nombre);
        strcpy(informacion.apellidos,agenda[x].apellidos);
        informacion.telefono = agenda[x].telefono;
        strcpy(informacion.email,agenda[x].email);
    }
    return informacion;
}



void listarAgenda(struct persona agenda[], int capacidad){
    int cont=0;

    for(int j=0 ; j<capacidad ; j++){
        if(agenda[j].apellidos[0]!='?'){     //Imprime todos los contactos de agenda[]
            printf("%d  %s, %s %lu %s\n", j+1, agenda[j].apellidos, agenda[j].nombre, agenda[j].telefono, agenda[j].email);
            cont++;
        }
    }
    if(cont==0){                            //Condicion por si no hay ningun contacto en agenda[]
        printf("\nAgenda vacia\n");
    }
}


int borrarPersona(struct persona agenda[], int capacidad, char nombre[]){
    int x=0, i=0, cont=0, confirm=0;
    unsigned long telefonoauxiliar=0;
    int lon=strlen(nombre);
    int lon2=0;
    char nombreauxiliar[capacidad], apellidosauxiliar[capacidad], emailauxiliar[capacidad];
    char nom[lon], nom2[lon];//nom es el nombre a buscar para borrar; nom2 es el nombre de la agenda con el que se compara
    strcpy(nom, nombre);
    lower(nom);

    while(x<capacidad){     //Ahora se hace toda la agenda, en buscarPersona para encuantro encuentra 1
        lon2=strlen(agenda[x].nombre);
        if(lon==lon2){

            strcpy(nom2, agenda[x].nombre);
            lower(nom2);

            while(confirm>=i && confirm<lon){
                if(nom[i]==nom2[i]){
                    confirm++;
                }
                i++;
            }
            if(confirm==lon){

                strcpy(agenda[x].nombre, "?");
                strcpy(agenda[x].apellidos, "?");
                agenda[x].telefono = 0;
                strcpy(agenda[x].email, "?");
                cont++;                         //cont cuenta cuantos contactos se ha eliminado
            }else{
                x++;
            }
        }else{
            x++;
        }
        for(int k=x ; k<capacidad ; k++){ //empieza en la posicion donde se ha borrado el contacto y lleva el contacto vacio hasta el ultimo de los contactos
            for(int q=k+1 ; q<capacidad ; q++){
                if((strcmp(agenda[k].apellidos,"?")==0) && agenda[q].apellidos[0]!='?'){

                    strcpy(nombreauxiliar,agenda[k].nombre);
                    strcpy(agenda[k].nombre,agenda[q].nombre);
                    strcpy(agenda[q].nombre,nombreauxiliar);

                    strcpy(apellidosauxiliar,agenda[k].apellidos);
                    strcpy(agenda[k].apellidos,agenda[q].apellidos);
                    strcpy(agenda[q].apellidos,apellidosauxiliar);

                    telefonoauxiliar = agenda[k].telefono;
                    agenda[k].telefono = agenda[q].telefono;
                    agenda[q].telefono = telefonoauxiliar;

                    strcpy(emailauxiliar,agenda[k].email);
                    strcpy(agenda[k].email,agenda[q].email);
                    strcpy(agenda[q].email,emailauxiliar);
                }
            }
        }
        i=0;
        confirm=0;
    }
    return cont;
}

int cargarAgenda(struct persona agenda[]){
    FILE* fichero;
    fichero = fopen("agenda.txt","r");
    int existe = 0;

    if(fichero == NULL){                    //Si no hay fichero lo crea
        fichero = fopen("agenda.txt", "w+");
        if(fichero == NULL){
            printf("\nERROR: imposible inicializar la agenda desde fichero\n");
        }
    }else{
        char contacto[MAX_CAD];
        int cont_actual = 0;

        while(fgets(contacto, MAX_CAD, fichero) != NULL){//El bucle separa cada linea del fichero en partes y las mete dentro de su sitio dentro del contacto
            char* datos = strtok(contacto, ";");
            strcpy(agenda[cont_actual].nombre, datos);
            datos = strtok(NULL, ";");
            strcpy(agenda[cont_actual].apellidos, datos);
            datos = strtok(NULL, ";");
            agenda[cont_actual].telefono = atol(datos);
            datos = strtok(NULL, ";");
            int lon = strlen(datos);
            if(datos[lon-1] == '\n'){ //Al final del string generabamos dos \n y asi sustituimos el ultimo por NULL
                datos[lon-1]=0;
            }
            strcpy(agenda[cont_actual].email, datos);
            cont_actual++;
        }

        existe = cont_actual;
    }

    fclose(fichero);

    return existe;
}

int actualizarAgenda(struct persona agenda[], int capacidad){
    int exito=0;
    FILE* fichero;
    fichero = fopen("agenda.txt","w+");
    if(fichero == NULL){
        exito=0;
    }else{
        for(int i = 0; i < capacidad; i++){
            if(strcmp(agenda[i].nombre, "?") != 0){
                fprintf(fichero,"%s;%s;%lu;%s\n",agenda[i].nombre,agenda[i].apellidos,agenda[i].telefono,agenda[i].email);
            }                                //Nos has dicho que quitemos el \n pero a Jorge no le hacia el salto de linea de forma automatica
        }
        exito=1;
    }

    if(fclose(fichero)!=0){
        exito=0;
    }
    return exito;
}

