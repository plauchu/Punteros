#include "stdio.h"
#include "stdlib.h"

typedef struct direccion {

	char calle[30];
	int numero;
	int cp;
	char ciudad[30];
	char pais[30];

};

typedef struct empleado {

	char nom[30];
	char apell[30];
	int id;
	struct direccion dir_emp;
	float salario;
	char genero;
	char est_civil;
	int num_hijos;
	struct empleado* proxEmp;
} EMP;
EMP* emp, * nomina;


EMP* crear_empleado() {
	int i, j;
	char aux;
	emp = (EMP*)malloc(sizeof(EMP));//pido espacio de memoria

	printf("Indicar nombre del empleado (sin apellidos): ");
	aux = getchar();
	for (i = 0; aux != '\n'; i++) {
		emp->nom[i] = aux;
		aux = getchar();
	}

	if (emp){
		emp->nom[i] = '\0';
	}

	printf("Indicar apellidos del empleado: ");
	aux = getchar();
	for (i = 0; aux != '\n'; i++) {
		emp->apell[i] = aux;
		aux = getchar();
	}

	if (emp) {
		emp->apell[i] = '\0';
	}

	printf("Indicar id del empleado a crear: ");

	if (emp) {
		scanf_s("%i", &emp->id);
		aux = getchar();
	}

	printf("Indicar la dirección (calle): ");
	aux = getchar();
	for (i = 0; aux != '\n'; i++) {
		emp->dir_emp.calle[i] = aux;
		aux = getchar();
	}

	if (emp) {
		emp->dir_emp.calle[i] = '\0';
	}

	printf("Indicar la dirección (número): ");

	if (emp) {
		scanf_s("%i", &emp->dir_emp.numero);
	}

	printf("Indicar la dirección (cp): ");

	if (emp) {
		scanf_s("%i", &emp->dir_emp.cp);
		aux = getchar();
	}

	printf("Indicar la dirección (ciudad): ");
	aux = getchar();
	for (i = 0; aux != '\n'; i++) {
		emp->dir_emp.ciudad[i] = aux;
		aux = getchar();
	}

	if (emp) {
		emp->dir_emp.ciudad[i] = '\0';
	}

	printf("Indicar la dirección (país): ");
	aux = getchar();
	for (i = 0; aux != '\n'; i++) {
		if (emp) {
			emp->dir_emp.pais[i] = aux;
			aux = getchar();
		}
	}

	if (emp) {
		emp->dir_emp.pais[i] = '\0';
	}

	printf("Indicar el salario: ");

	if (emp) {
		scanf_s("%f", &emp->salario);
		aux = getchar();
	}

	printf("Indicar género (caracter): ");

	if (emp) {
		scanf_s("%c", &emp->genero, 1);
		aux = getchar();
	}

	printf("Indicar estado civil (caracter): ");

	if (emp) {
		scanf_s("%c", &emp->est_civil, 1);
	}

	printf("Indicar número de hijos: ");

	if (emp) {
		scanf_s("%i", &emp->num_hijos);
		aux = getchar();
	}

	if (emp == NULL) {//cachar error de falta de memoria
		printf("\nNo hay memoria disponible");
		perror("\nNo memoria: ");
		exit(0);
	}
	else
		return(emp);//recupero apuntador
}

void insertar_empleado(EMP* nuevo) {
	EMP* prox;
	EMP* ant;
	prox = nomina;
	ant = nomina;
	if (prox == NULL or prox->id > nuevo->id) {//caso inicio de la lista
		nuevo->proxEmp = nomina;
		nomina = nuevo;
	}
	else {
		prox = prox->proxEmp;
		bool band = false;
		while (prox != NULL and band == false) {//caso entre 2 emps
			if (prox->id > nuevo->id) {
				nuevo->proxEmp = ant->proxEmp;
				ant->proxEmp = nuevo;
				band = true;
			}
			prox = prox->proxEmp;
			ant = ant->proxEmp;
		}
		if (band == false) {//caso final de lista
			nuevo->proxEmp = NULL;
			ant->proxEmp = nuevo;
		}
	}
}

void borrar_empleado(int id) {
	EMP* e;
	EMP* prox;
	EMP* ant;
	e = nomina;
	prox= nomina;
	ant = nomina;
	if (e == NULL)//caso lista vacia
		printf("\nLa lista de empleados está vacia");
	else {
		prox = prox->proxEmp;
		if (e->id == id) {//caso de primero en la lista
			nomina = prox;
			e->proxEmp = NULL;
			printf("\nSe borro exitosamente el empleado con el id: %d", id);
		}
		else {
			if (prox == NULL)//solo hay un empleado y no es el primero
				printf("\nNo se encontro el empleado con el id: %d", id);
			else {
				prox = prox->proxEmp;
				e = e->proxEmp;
				bool band = false;
				while (e != NULL and band == false) {//busca empleado
					if (e->id == id)//encuentra empleado
						band = true;
					else {
						ant = ant->proxEmp;
						e = e->proxEmp;
						if (prox->proxEmp != NULL)
							prox = prox->proxEmp;
					}
				}
				if (band == true) {//borra empleado
					ant->proxEmp = e->proxEmp;
					e->proxEmp = NULL;
					printf("\nSe borro exitosamente el empleado con el id: %d", id);
				}
				else//no se encontro el empleado
					printf("\nNo se encontro el empleado con el id: %d", id);
			}
		}
	}
}


int num_empleados(EMP* nomi) {
	int cant_emps = 0;
	while (nomi != NULL) {//recorre la lista
		cant_emps++;
		nomi = nomi->proxEmp;
	}
	printf("\nEl numero de empleados es: %d", cant_emps);
	return cant_emps;
}

void mostrar_empleado(int id) {
	EMP* prox;
	prox = nomina;
	if (prox == NULL)//lista de empleados vacia
		printf("\nLa lista de empleados esta vacia");
	else {
		bool band = false;
		while (prox != NULL and band == false) {//busca el empleado
			if (prox->id == id)//encuentra el empleado
				band = true;
			else
				prox = prox->proxEmp;
		}
		if (band == true) {//muestra los datos del empleado
			printf("\nID %d\nNombre Empleado  %s\nApellidos Empleado  %s\nDirección: Calle  %s \nDirección: número  %d \nDirección: CP  %d \nDirección: Ciudad  %s \nDirección: País  %s \nSalario %f \nGénero %c \nEstado Civil  %c \nNúmero hijos  %d \n", prox->id, prox->nom, prox->apell, prox->dir_emp.calle, prox->dir_emp.numero, prox->dir_emp.cp, prox->dir_emp.ciudad, prox->dir_emp.pais, prox->salario, prox->genero, prox->est_civil, prox->num_hijos);
		}
		else//no se encontro empleado
			printf("\nNo se encontro el empleado con el id: %d", id);
	}
}

void los_empleados() {
	EMP* prox;
	prox = nomina;
	if (prox == NULL)//lista vacia
		printf("\nLa lista de empleados esta vacia");
	else {
		while (prox != NULL) {//recorre la lista e imprime los datos de los empleados
			printf("\nID %d\nNombre Empleado  %s\nApellidos Empleado  %s\nDirección: Calle  %s \nDirección: número  %d \nDirección: CP  %d \nDirección: Ciudad  %s \nDirección: País  %s \nSalario %f \nGénero %c \nEstado Civil  %c \nNúmero hijos  %d \n", prox->id, prox->nom, prox->apell, prox->dir_emp.calle, prox->dir_emp.numero, prox->dir_emp.cp, prox->dir_emp.ciudad, prox->dir_emp.pais, prox->salario, prox->genero, prox->est_civil, prox->num_hijos);
			prox = prox->proxEmp;
		}
	}
}

int main() {//pruebas
	nomina = NULL;
	insertar_empleado(crear_empleado());
	insertar_empleado(crear_empleado());
	insertar_empleado(crear_empleado());
	insertar_empleado(crear_empleado());
	los_empleados();
	num_empleados(nomina);
	mostrar_empleado(3);
	borrar_empleado(3);
	los_empleados();
}