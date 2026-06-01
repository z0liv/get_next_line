*Este proyecto ha sido creado como parte del currículo de 42 por omarquez*

# GET_NEXT_LINE:
## DESCRIPCION:
El objetivo de `get_next_line` es leer un archivo descriptor de archivo (`fd`) y retornar una línea a la vez, gestionando de forma eficiente la memoria y el almacenamiento de los datos leídos.

Esta función es extremadamente útil para manejar la entrada de archivos de manera eficiente y controlada, permitiendo al usuario obtener una línea de texto a la vez hasta llegar al final del archivo (EOF).

### Características principales:
- Gestión eficiente de la memoria para evitar fugas.
- Uso de variables estáticas para mantener el estado entre múltiples llamadas a la función.

## INSTRUCCIONES:
### Requisitos
- Compilador de C (como `gcc` o `clang`).
- Sistema operativo tipo Unix (Linux o macOS).
- `make` para la compilación (si has incluido un Makefile).

### Compilación
Para probar la función, puedes compilarla junto con un programa de prueba y ademas necesitaras un archivo de texto para leer. El BUFFER_SIZE ya esta predefinido en el archivo de cabecera pero lo puedes redefinir con el flag -D BUFFER_SIZE=(int). Si tienes un archivo `main.c` para testear, utiliza el siguiente comando:

```bash
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o gnl
```
o podrias usar este codigo de ejemplo:
```c
int	main(void)
{
	int		fd;
	char	*line;
	
	fd = open("nombre_del_archivo_a_leer", O_RDONLY);
	if(fd == -1)
		return (-1);
	while((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}
```
## RECURSOS:

Mis compañeros de el 42 Cursus me han ayudado:

- @patperez, @ugarcia- y @francysa: en el reconocimiento del algoritmo a utilizar y entender el flujo del programa.
- @xlopez-g y @mostoloz: en visualizar otra manera de hacer el ejercicio y me ha ayudado a entender el funcionamiento mas profundamente.
- @khurtado: me ha ayudado haciendo peer-coding ayudandome a reconocer los errores de mi código.

- [geeksforgeeks]https://www.geeksforgeeks.org/c/static-variables-in-c/ La use de introduccion al concepto de variables estaticas.
- [geeksforgeeks]https://www.geeksforgeeks.org/c/input-output-system-calls-c-create-open-close-read-write/ Use este articulo para recordar el funcionamiento de las funciones read y open.
- [learn.microsoft]https://learn.microsoft.com/es-es/cpp/preprocessor/hash-if-hash-elif-hash-else-and-hash-endif-directives-c-cpp?view=msvc-170 Use esta documentación para aprender a como crear una Macro y redefinirla.

### Uso de la IA:

- He utilizado la IA para la realización de este archivo README.md.
- Y también me ha ayudado a localizar algunos errores de fugas de memoria y de logica en mi codigo.

## Arquitectura del Algoritmo

El núcleo del programa se basa en una **variable estática** (`static char *store`), la cual permite persistir los datos entre múltiples llamadas a la función. Dado que el sistema de archivos entrega datos en bloques de tamaño `BUFFER_SIZE`, esta variable actúa como un almacén temporal de residuos.

### Flujo de Ejecución

1. **Fase de Lectura (`read_store`)**: 
   - Utiliza un bucle para leer bloques del archivo mediante `read()` hasta que se encuentre un salto de línea (`\n`) o se alcance el final del archivo (EOF).
   - Los datos leídos se concatenan a la variable `store` utilizando `ft_strjoin`.
   - Se libera la memoria intermedia (`free`) en cada iteración para evitar fugas.

2. **Fase de Extracción (`ft_get_line`)**:
   - Una vez que `store` contiene una línea completa, esta función escanea la cadena hasta encontrar `\n` o `\0`.
   - Retorna una nueva cadena (mediante `malloc`) que contiene únicamente la línea extraída.

3. **Fase de Actualización (`update_store`)**:
   - Es el paso crítico para las llamadas sucesivas.
   - Calcula el residuo sobrante tras la línea extraída y lo reasigna a `store`.
   - La memoria antigua se libera, dejando `store` preparado únicamente con el contenido pendiente.

## Componentes Principales

| Función | Responsabilidad |
| :--- | :--- |
| `get_next_line` | Función principal; orquesta la lectura, extracción y actualización del buffer. |
| `ft_read_store` | Lee desde el `fd` y acumula datos en la variable estática hasta encontrar un salto de línea. |
| `ft_get_line` | Aísla y extrae la línea de texto desde el buffer acumulado. |
| `ft_update_store` | Gestiona el "recorte" del buffer, eliminando la línea ya entregada y guardando el resto. |
| `ft_strjoin` | Une dos cadenas de caracteres gestionando dinámicamente la memoria. |
| `ft_substr` | Crea subcadenas necesarias para el manejo preciso de los punteros. |

## Consideraciones de Memoria
El algoritmo ha sido diseñado para ser **estricto en la gestión de memoria**:
- Cada `malloc` realizado durante la concatenación o extracción tiene su correspondiente `free`.
- El manejo de la variable estática `store` asegura que no se pierdan datos entre llamadas, permitiendo leer archivos de cualquier tamaño sin desbordar la pila.
- El uso de `BUFFER_SIZE` permite ajustar la eficiencia de la lectura según el entorno de ejecución, definiéndose en tiempo de compilación.
