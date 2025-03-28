#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>

#define MAX_DISPOSITIVOS 10
#define MAX_CATEGORIAS 3
#define MAX_NOMBRE 100

// Arrays para almacenar los nombres, categorías, estados y valores de los
// dispositivos
char nombresDispositivos[MAX_DISPOSITIVOS][MAX_NOMBRE];
char categoriasDispositivos[MAX_DISPOSITIVOS][MAX_NOMBRE];
char estadosDispositivos[MAX_DISPOSITIVOS][MAX_NOMBRE];
int contadorDispositivos = 0;

// Arrays para las categorías disponibles
char categorias[MAX_CATEGORIAS][MAX_NOMBRE] = {
    "Motores", "Bombas y Compresores",
    "L�neas de Producci�n (Cintas Transportadoras)"};

// Funciones para actualizar el estado de los dispositivos
void actualizarEstadoMotor(float velocidad, int indice)
{
  if (velocidad > 80.0)
  {
    strcpy(estadosDispositivos[indice], "[WARNING] - Motor con alta velocidad!");
  }
  else
  {
    strcpy(estadosDispositivos[indice],
           "[OK] - Motor funcionando correctamente.");
  }
}

void actualizarEstadoBandaTransportadora(float velocidad, int indice)
{
  if (velocidad > 400.0)
  {
    strcpy(estadosDispositivos[indice],
           "[WARNING] - Banda transportadora con velocidad muy alta!");
  }
  else
  {
    strcpy(estadosDispositivos[indice],
           "[OK] - Banda transportadora funcionando correctamente.");
  }
}

void actualizarEstadoBombasCompresores(float presion, int indice)
{
  if (presion > 600.0)
  {
    strcpy(estadosDispositivos[indice],
           "[WARNING] - Bomba con presi�n muy alta!");
  }
  else
  {
    strcpy(estadosDispositivos[indice], "[OK] - Bomba funcionando correctamente.");
  }
}

// Función para mostrar menú
void mostrarMenu()
{
  printf("\n=== Men� VISSOR ===\n");
  printf("1. Monitorear por Categor�a\n");
  printf("2. Agregar Nuevo Dispositivo\n");
  printf("3. Salir\n");
  printf("Seleccione una opci�n: ");
}

// Función para agregar dispositivos
void agregarDispositivo()
{
  if (contadorDispositivos >= MAX_DISPOSITIVOS)
  {
    printf("[ERROR] - No se pueden agregar m�s dispositivos, el l�mite ha sido "
           "alcanzado.\n");
    return;
  }

  printf("\nIngrese el nombre del dispositivo: ");
  scanf(" %[^\n]", nombresDispositivos[contadorDispositivos]);

  // Menú para seleccionar la categoría
  int categoria;
  int categoriaValida = 0;
  while (!categoriaValida)
  {
  	int i;
    printf("\nSeleccione la categor�a del dispositivo:\n");
    for (i = 0; i < MAX_CATEGORIAS; i++)
    {
      printf("%d. %s\n", i + 1, categorias[i]);
    }

    scanf("%d", &categoria);

    if (categoria >= 1 && categoria <= MAX_CATEGORIAS)
    {
      strcpy(categoriasDispositivos[contadorDispositivos],
             categorias[categoria - 1]);
      categoriaValida = 1; // Categoria válida
    }
    else
    {
      printf("[ERROR] - Opci�n no v�lida. Intente nuevamente.\n");
    }
  }

  // Asignar estado inicial como 'OK'
  strcpy(estadosDispositivos[contadorDispositivos],
         "[OK] - Dispositivo agregado correctamente.");

  contadorDispositivos++;
  printf("[OK] - Dispositivo agregado exitosamente.\n");
}

// Función para mostrar dispositivos de una categoría específica
void monitorearPorCategoria()
{
  int categoriaSeleccionada;
  int categoriaValida = 0;
  int i;
  // Selección de categoría con validación
  while (!categoriaValida)
  {
    printf("\nSeleccione la categor�a que desea monitorear:\n");
    for (i = 0; i < MAX_CATEGORIAS; i++)
    {
      printf("%d. %s\n", i + 1, categorias[i]);
    }

    scanf("%d", &categoriaSeleccionada);

    if (categoriaSeleccionada >= 1 && categoriaSeleccionada <= MAX_CATEGORIAS)
    {
      categoriaValida = 1; // Categoría válida
    }
    else
    {
      printf("[ERROR] - Opci�n no v�lida. Intente nuevamente.\n");
    }
  }

  printf("\n=== Dispositivos en la categor�a '%s' ===\n",
         categorias[categoriaSeleccionada - 1]);
  printf("| %-25s | %-25s | %-20s | %-20s |\n", "Dispositivo", "Categor�a",
         "Estado", "Lectura");
  printf("|-------------------------|-------------------------|----------------"
         "------|----------------------|\n");

  // Mostrar los dispositivos de la categoría seleccionada
  for (i= 0; i < contadorDispositivos; i++)
  {
    if (strcmp(categoriasDispositivos[i],
               categorias[categoriaSeleccionada - 1]) == 0)
    {
      // Asignar estado según el dispositivo y categoría
      float lectura = 0.0;
      if (strcmp(categoriasDispositivos[i], "Motores") == 0)
      {
        lectura =
            (rand() % 100) + ((float)rand() / RAND_MAX); // Simulación de motor
        actualizarEstadoMotor(lectura, i);
      }
      else if (strcmp(categoriasDispositivos[i],
                      "Líneas de Producción (Cintas Transportadoras)") == 0)
      {
        lectura =
            (rand() % 500) +
            ((float)rand() / RAND_MAX); // Simulación de banda transportadora
        actualizarEstadoBandaTransportadora(lectura, i);
      }
      else if (strcmp(categoriasDispositivos[i], "Bombas y Compresores") ==
               0)
      {
        lectura =
            (rand() % 700) +
            ((float)rand() / RAND_MAX); // Simulación de banda transportadora
        actualizarEstadoBombasCompresores(lectura, i);
      }
      printf("| %-25s | %-25s | %-20s | %-20.2f |\n", nombresDispositivos[i],
             categoriasDispositivos[i], estadosDispositivos[i], lectura);
    }
  }
  printf("\n");
}

int main()
{
  srand(time(NULL));
  int opcion;
  setlocale(LC_ALL, "");
  do
  {
    mostrarMenu();
    scanf("%d", &opcion);

    switch (opcion)
    {
    case 1:
      monitorearPorCategoria(); // Monitorear por categoría seleccionada
      break;
    case 2:
      agregarDispositivo(); // Agregar un nuevo dispositivo
      break;
    case 3:
      printf("Saliendo del sistema...\n");
      break;
    default:
      printf("[ERROR] - Opci�n no v�lida. Intente nuevamente.\n");
    }
  } while (opcion != 3);

  return 0;
}
