#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Peliculas_MAX 15
#define NOMBRE_ARCHIVO "peliculas.txt"

typedef struct Pelicula {
  char nombre[45];
  char genero[30];
  int año_estreno;
  struct Pelicula *next;
} Pelicula_t;
Pelicula_t *lista_peliculas = NULL;
void menu();
void Pedir_Informacion(Pelicula_t *pelicula);
void CargarPelicula();
void MostrarPeliculas(Pelicula_t *pelicula);
void VerLista();
void GuardarLista();
void LeerLista();
void LiberarEspacio();

int main(void) {
  LeerLista(); // Carga la lista de películas al iniciar el programa
  menu();
  LiberarEspacio(); // Libera la memoria asignada a las películas antes de salir
  return 0;
}
void Pedir_Informacion(Pelicula_t *pelicula) {
  printf("Ingrese el nombre de la pelicula: ");
  fgets(pelicula->nombre, sizeof(pelicula->nombre), stdin);
  pelicula->nombre[strcspn(pelicula->nombre, "\n")] =
      '\0'; // Elimina el salto de línea

  printf("Ingrese el genero de la pelicula: ");
  fgets(pelicula->genero, sizeof(pelicula->genero), stdin);
  pelicula->genero[strcspn(pelicula->genero, "\n")] = '\0';

  printf("Ingrese el año de estreno de la pelicula: ");
  scanf("%d", &(pelicula->año_estreno));
  getchar(); // Limpia el buffer de entrada
}
void CargarPelicula() {
  Pelicula_t *pelicula_aux;
  pelicula_aux =
      malloc(sizeof(Pelicula_t)); // Reserva memoria para la nueva película
  if (pelicula_aux == NULL) {
    printf("No hay más espacio en la memoria.\n");
    return;
  }
  Pedir_Informacion(pelicula_aux); // Pide información de la nueva peli
  pelicula_aux->next = lista_peliculas;
  lista_peliculas =
      pelicula_aux; // Actualiza la primera película a la nueva película
  GuardarLista();   // Guarda la lista de películas en el archivo
}
void MostrarPeliculas(Pelicula_t *pelicula) {
  printf("✦✧✦✧✦✧✦✧✦✧✦✧✦✧✦✧✦\n");
  printf("Nombre: %s\n", pelicula->nombre);
  printf("Genero: %s\n", pelicula->genero);
  printf("Año de estreno: %d\n", pelicula->año_estreno);
  printf("✦✧✦✧✦✧✦✧✦✧✦✧✦✧✦✧✦\n");
}
void VerLista() {
  Pelicula_t *temp = lista_peliculas;
  if (temp == NULL) {
    printf("No hay películas cargadas\n"); // Si está vacio printea esto
  } else {
    FILE *archivo =
        fopen(NOMBRE_ARCHIVO, "a"); // abre el archivo en modo escritura
    if (archivo == NULL) {
      printf("Error al abrir el archivo de películas.\n");
      return;
    }

    while (temp != NULL) {
      fprintf(archivo, "%s;%s;%d\n", temp->nombre, temp->genero,
              temp->año_estreno);
      temp = temp->next; // Avanza al siguiente coso en la lista
    }

    fclose(archivo);
  }
}
void menu() {
  int opcion;
  do {
    printf("▾▵▾▵ Bienvenido al menú ▵▾▵▾\n");
    printf("1. Cargar una nueva pelicula\n");
    printf("2. Ver todas las peliculas cargadas\n");
    printf("3. Borrar las peliculas del archivo\n");
    printf("4. Salir\n");
    printf("▾▵▾▵▾▵▾▵▾▵▾▵▾▵▾▵▾▵▾▵▾▵▾▵▾▵▾▵\n");
    scanf("%d", &opcion);
    getchar(); // Limpia el buffer de entrada

    if (opcion == 1)
      CargarPelicula();
    if (opcion == 2)
      VerLista();
    if (opcion == 3) {
      LiberarEspacio();
      lista_peliculas = NULL; // Asigna null a la lista de peliculas
      GuardarLista();  // Elimina el contenido del archivo de peliculas
    }
  } while (opcion != 4);
}
void GuardarLista() {
  FILE *archivo = fopen(NOMBRE_ARCHIVO, "w"); // Abrir en modo escritura
  if (archivo == NULL) {
    printf("Error al abrir el archivo de películas.\n");
    return;
  }

  Pelicula_t *temp = lista_peliculas;
  int ya_escrito = 0; // Revisa que no este cargada ya la pelicula

  while (temp != NULL) {
    if (!ya_escrito) {
      printf("Almacenando la pelicula..: %s\n",
             temp->nombre); //aviso de que se carga la nueva pelicula
      fprintf(archivo, "%s;%s;%d\n", temp->nombre, temp->genero,
              temp->año_estreno);
      ya_escrito = 1; // Marcar como ya escrito
    }

    temp = temp->next; // Avanzar al siguiente coso de la lista
    ya_escrito = 0;    // Reinicio para que analice el estado de la prox peli
  }

  fclose(archivo);
  printf("Lista de peliculas actualizada con éxito.\n"); // Mensaje de confirmación
}
void LeerLista() {
  FILE *archivo = fopen(NOMBRE_ARCHIVO, "r");
  if (archivo == NULL) {
    return; // Si no existe el archivo, no hace nada
  }

  char nombre[45], genero[30];
  int año_estreno;
  while (fscanf(archivo, "%[^;];%[^;];%d\n", nombre, genero, &año_estreno) !=
         EOF) { //EOF es end of file!!
    Pelicula_t *pelicula_aux =
        malloc(sizeof(Pelicula_t)); // Reserva memoria para la nueva peli
    if (pelicula_aux == NULL) {
      printf("No hay más espacio en la memoria.\n");
      fclose(archivo);
      return;
    }

    strcpy(pelicula_aux->nombre, nombre);
    strcpy(pelicula_aux->genero, genero);
    pelicula_aux->año_estreno = año_estreno;
    pelicula_aux->next = lista_peliculas;
    lista_peliculas = pelicula_aux;
  }

  fclose(archivo);
}
void LiberarEspacio() {
  Pelicula_t *aux = NULL;
  while (lista_peliculas != NULL) {
    aux = lista_peliculas;
    lista_peliculas = lista_peliculas->next;
    free(aux);
  }
}