#include <windows.h>
#include <iostream>
#include <string>
#include <conio.h>
#include <string>
#include <sstream>
#include <ctime>
#define KEY_UP 72 + 256
#define KEY_DOWN 80 + 256
#define KEY_RIGHT 77 + 256
#define KEY_LEFT 75 + 256
#define ENTER 13
#define NEGRO 0
#define AZUL 1
#define VERDE 2
#define ROJO 4
#define MAGENTA 5

using namespace std;

void gotoxy(int x,int y){  
      HANDLE hcon;  
      hcon = GetStdHandle(STD_OUTPUT_HANDLE);  
      COORD dwPos;  
      dwPos.X = x;  
      dwPos.Y= y;  
      SetConsoleCursorPosition(hcon,dwPos);  
 }  
 
 /*

colores disponibles

0   BLACK
1   BLUE
2   GREEN
3   CYAN
4   RED
5   MAGENTA
6   BROWN
7   LIGHTGRAY
8   DARKGRAY
9   LIGHTBLUE
10  LIGHTGREEN
11  LIGHTCYAN
12  LIGHTRED
13  LIGHTMAGENTA
14  YELLOW
15  WHITE
*/
 
 void setColorText(int color){		//cambia el color del texto

 	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color | FOREGROUND_INTENSITY);
 }
 
bool AjustarVentana(int Ancho, int Alto){	//redimensiona la ventana de consola
	
	COORD Coordenada;
	Coordenada.X = Ancho;
	Coordenada.Y = Alto;

	_SMALL_RECT Rect;
	Rect.Top = 0;
	Rect.Left = 0;
	Rect.Right = Ancho - 1;
	Rect.Bottom = Alto - 1;

	// Obtener el handle de la consola
	HANDLE hConsola = GetStdHandle(STD_OUTPUT_HANDLE);

	// Ajustar el buffer al nuevo tama�o
	SetConsoleScreenBufferSize(hConsola, Coordenada);

	// Cambiar tama�o de consola a lo especificado en el buffer
	SetConsoleWindowInfo(hConsola, TRUE, &Rect);
	
	return true;
}

void dibujar_marco(int inicio_x, int inicio_y, int alto, int ancho, int color, string titulo){
		
		setColorText(color);
		//pinta el marco horizontal
		
		gotoxy(inicio_x, inicio_y);
		printf(" ");
		
		for(int i = inicio_x; i< ancho-3; i++){
			gotoxy(i+1, inicio_y);
			printf("%c", 205);
			gotoxy(i, alto-2);
			printf("%c", 205);
			gotoxy(i, inicio_y + 5);
			printf("%c", 205);
		}
		
		//dibuja el marco vertical
		for(int i = inicio_y; i< alto-1; i++){
			if(i == inicio_y){
				gotoxy(inicio_x, i);
				printf("%c", 201);
				gotoxy(ancho-3, i);
				printf("%c", 187);
			}
			else if(i == inicio_y + 5){
				gotoxy(inicio_x, i);
				printf("%c", 204);
				gotoxy(ancho-3, i);
				printf("%c", 185);
			}
			else if(i == alto-2){
				gotoxy(inicio_x, i);
				printf("%c", 200);
				gotoxy(ancho-3, i);
				printf("%c", 188);
			}
			else{
				gotoxy(inicio_x, i);
				printf("%c", 186);
				gotoxy(ancho-3, i);
				printf("%c", 186);
			}
		}	
		
		gotoxy(ancho/3, inicio_y + 3);
		cout<<titulo;
		
}

void mover_opcion(int &tecla, int &x, int &y, int &max, int &min){
		
		if(tecla == KEY_UP){
			if(y == min){
				y = max;
			}
			else{
				y--;
			}
		}
		else if(tecla == KEY_DOWN){
			if(y == max){
				y = min;
			}
			else{
				y++;
			}
		}
}

string ConvertirNumero(int num){	//convierte de entero a string
    stringstream convert;
    convert << num;
    return convert.str();
}

string fecha(){		//obtiene la fecha del sistema
	
	struct tm *tiempo;
	int dia;
	int mes;
	int anio;
	
	time_t fecha_sistema;
    time(&fecha_sistema);
	tiempo=localtime(&fecha_sistema); 
	anio=tiempo->tm_year + 1900;
	mes=tiempo->tm_mon + 1;
	dia=tiempo->tm_mday;
	 
 	string fecha =  ConvertirNumero(dia)+"/"+ConvertirNumero(mes)+"/"+ConvertirNumero(anio);

	return fecha;
}

void dibujar_marco_ingreso_datos(){
	
	setColorText(7);
	
	for(int i = 4; i <= 60; i++){	//dibuja las barras horizontales
		gotoxy(i, 6);
		printf("%c", 223);
		gotoxy(i, 8);
		printf("%c", 220);
		gotoxy(i,	11);
		printf("%c", 196);
		gotoxy(i, 13);
		printf("%c", 196);
		gotoxy(i, 15);
		printf("%c", 196);
		gotoxy(i, 17);
		printf("%c", 196);
		gotoxy(i, 19);
		printf("%c", 220);

	}
			
	for(int i = 6;  i <= 19; i++){	//dibuja las barras verticales
				
		if(i <= 8){
			gotoxy(4, i);
			printf("%c", 219);
			gotoxy(60, i);
			printf("%c", 219);
		}
		else{
			gotoxy(4, i);
			printf("%c", 219);
			gotoxy(60, i);
			printf("%c", 219);
			gotoxy(25, i);
			printf("%c", 219);
		}
	}
	
	setColorText(10);
	gotoxy(6, 10);
	cout<<"Numero de Chasis:";
	gotoxy(6, 12);
	cout<<"Marca: ";
	gotoxy(6, 14);
	cout<<"Modelo: ";
	gotoxy(6, 16);
	cout<<"Color: ";
	gotoxy(6, 18);
	cout<<"A"<<char(164)<<"o: ";
	
	gotoxy(38, 2);
	cout<<"Fecha Actual: "<<fecha();
}

string generar_id(string anio, int &id_, string nombre, bool jefe){

	string id;
	int e = 0;

	if(jefe){
		for(int i = 0; i < nombre.size(); i++){

			if(nombre[i] == ' '){
				e++;
				if(e == 2 || e == 3){
					id = id + nombre[i+1];
				}
			}

		}
	}
	else{
		id = id + nombre[0];
	}

	id = id + anio;
	string digitos;

	if(id_ < 10){
		digitos = "00" + ConvertirNumero(id_);
	}
	else if( id_ < 100){
		digitos = "0" + ConvertirNumero(id_);
	}
	else{
		digitos = ConvertirNumero(id_);
	}

	id = id + digitos;

	id_++;

	for(int i = 0; i < id.size(); i++){
		id.at(i) = toupper(id.at(i));
	}

	return id;

}

void marco_ingreso(int x, int y, int ancho, int lineas, string texto[], string titulo, int color) {

    setColorText(color);

    lineas*=2;
    lineas+=4;

    //barras horizontales
	for (int i = x; i <= x+ancho; i++) {

		if (i == x) {
			gotoxy(i, y);
			printf("%c", 201);
			gotoxy(i, y+lineas);
			printf("%c", 200);
		} else if (i == ancho+x) {
			gotoxy(i, y);
			printf("%c", 187);
			gotoxy(i, y+lineas);
			printf("%c", 188);
		}
        else{
            gotoxy(i, y);
            printf("%c", 205);
            gotoxy(i, y+lineas);
            printf("%c", 205);
        }

	}


    for(int e = y+4; e<= y+lineas-2; e+=2){

        for(int i = x; i <= x+ancho; i++){

            if(e == y+4){
                gotoxy(i, e);
                printf("%c", 196);
            }

            gotoxy(i, e);
            printf("%c", 196);

        }

    }

    gotoxy(((x+ancho)/3), y+2);
    cout << titulo;

    int text = 0;
    for (int i = y+5; i < y+lineas ; i+=2) {
        gotoxy(x+2, i);
        cout << texto[text];
        text++;
    }

    //barras verticales
	for (int i = y+1; i <= y+lineas-1; i++) {
		gotoxy(x, i);
		printf("%c", 186);
		gotoxy(x+ancho, i);
		printf("%c", 186);

		if (i >= y+5) {
			gotoxy(((x+ancho)/3), i);
			printf("%c", 179);
		}
	}

}

void recuadro_nota(){
	//cuadro de nota

	for (int i = 14; i <= 85; i++) {

		if (i == 14) {
			gotoxy(i, 34);
			printf("%c", 201);
			gotoxy(i, 38);
			printf("%c", 200);
		} else if (i == 85) {
			gotoxy(i, 34);
			printf("%c", 187);
			gotoxy(i, 38);
			printf("%c", 188);
		} else {

			gotoxy(i, 34);
			printf("%c", 205);
			gotoxy(i, 38);
			printf("%c", 205);
		}

	}

	for (int i = 35; i <= 37; i++) {

		gotoxy(14, i);
		printf("%c", 186);
		gotoxy(85, i);
		printf("%c", 186);

	}
}