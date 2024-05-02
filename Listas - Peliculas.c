#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Peliculas_MAX 15

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
void LiberarEspacio();

int main(void) {
  menu();           // Función principal 
  LiberarEspacio(); // Libera la memoria asignada a las películas antes de salir
  return 0;
}

void Pedir_Informacion(Pelicula_t *pelicula) { // Función para solicitar
                                               // información de una película
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

void CargarPelicula() { // Función para cargar una nueva película
  Pelicula_t *pelicula_aux;
  pelicula_aux =
      malloc(sizeof(Pelicula_t)); // Reserva memoria para la nueva película
  if (pelicula_aux == NULL) {     // Verifica si se asignó memoria bien
    printf("No hay más espacio en la memoria.\n");
    return;
  }
  Pedir_Informacion(pelicula_aux); // Solicita información de la nueva peli
  pelicula_aux->next = lista_peliculas;
  lista_peliculas =
      pelicula_aux; // Actualiza la primera película a la nueva película
}

void MostrarPeliculas(
    Pelicula_t *pelicula) { // Función para mostrar información de una película
  printf("✦✧✦✧✦✧✦✧✦✧✦✧✦✧✦✧✦\n");
  printf("Nombre: %s\n", pelicula->nombre);
  printf("Genero: %s\n", pelicula->genero);
  printf("Año de estreno: %d\n", pelicula->año_estreno);
  printf("✦✧✦✧✦✧✦✧✦✧✦✧✦✧✦✧✦\n");
}
void VerLista() { // Función para mostrar la lista de películas cargadas
  Pelicula_t *temp = lista_peliculas;
  if (temp == NULL) {
    printf("No hay películas cargadas\n"); // Si está vacio printea esto
  } else {
    while (temp != NULL) {
      MostrarPeliculas(temp); // Muestra la info de cada peli
      temp = temp->next;      // Avanza al siguiente coso en la lista
    }
  }
}
void menu() { // Función del menú principal
  int opcion;
  do {
    printf("▾▵▾▵ Bienvenido al menú ▵▾▵▾\n");
    printf("1. Cargar una nueva pelicula\n");
    printf("2. Ver todas las peliculas cargadas\n");
    printf("3. Borrar la memoria\n");
    printf("4. Salir\n");
    printf("▾▵▾▵▾▵▾▵▾▵▾▵▾▵▾▵▾▵▾▵▾▵▾▵▾▵▾▵\n");
    scanf("%d", &opcion); // Lee la opción seleccionada por el usuario
    getchar();            // Limpia el buffer de entrada
    if (opcion == 1)
      CargarPelicula(); // Llama a la función para cargar una película
    if (opcion == 2)
      VerLista(); // Llama a la función para mostrar la lista de películas
    if (opcion == 3)
      LiberarEspacio();  // Llama a la función para liberar la memoria
  } while (opcion != 4); // Repite el menú hasta que el usuario seleccione salir
}
void LiberarEspacio() { // Función para liberar la memoria asignada a la lista
                        // de películas
  Pelicula_t *aux = NULL;
  while (lista_peliculas != NULL) {
    aux = lista_peliculas; // Almacena temporalmente el nodo actual
    lista_peliculas = lista_peliculas->next; // Avanza al siguiente en la lista
    free(aux);
  }
}
