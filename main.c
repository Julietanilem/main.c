#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

int y=-70, yo=-70, y2=-70, vidas_trivia=3, mostrarImagenGanador=0, x, xo, x2, vidas=3, esperar, cabezax, cabezay, cuerpox, cuerpoy;
int c=0, direccion_carrrera=0, lado_carrera=0, cx, cy, ancho, largo, centroMeCa1x , centroMeCa1y, centroMeCa2x, centroMeCa2y;
int xmet=0, ymet, x2met=0, y2met=0, rango, segundo=1;
int pantallaperdiste=0, pantallaganaste=0, pantallaseguir=0;

ALLEGRO_FONT *fuente1, *fuentegrande, *fuentechica;

ALLEGRO_TIMER *timer_atrapalo, *timeresperar;

ALLEGRO_BITMAP *fondo_atra, *astronauta, *meteorito, *corazon, *fondo, *fondo_ganador, *entreJuegos, *imagenFinal;
ALLEGRO_BITMAP  *fondo_carrera, *astronauta_carrera, *astronauta_salto, *astronauta_quieto, *meteorito_carrera, *astronauta_agachado;

ALLEGRO_SAMPLE *colision, *ganador, *respuesta_correcta, *respuesta_incorrecta, *perdiste;


//MOSTRAR IMAGEN FINAL
void imagen_final()
{
    imagenFinal = al_load_bitmap("Imagenes/Fondo_Final.jpg");
    if(!imagenFinal)
    {
        printf("No se pudo cargar la inagen del final");
    }
    al_draw_scaled_bitmap(imagenFinal, 0, 0, 701, 394, 0, 0, 800, 500, 0);
}
//SONIDO GANADOR
void sonido_ganador()
{
    ganador = al_load_sample("Musica/Ganador.mp3");
    pantallaganaste=1;
}
//COLISION ATRAPALO
int colisiono(int cx1, int cy1, int cx2, int cy2, int cx3, int cy3, int cAstrox, int cAstroy)
{
    int sn=0, distancia, distancia1, distancia2;
    int r1=50, r2=24;
    distancia = sqrt( (cx1-cAstrox )*(cx1-cAstrox ) + (cy1-cAstroy )*(cy1-cAstroy) );
    distancia1 = sqrt( ( cx2-cAstrox )*( cx2-cAstrox ) + ( cy2-cAstroy )*(cy2-cAstroy ) );
    distancia2 = sqrt( (cx3-cAstrox )*( cx3-cAstrox ) + ( cy3-cAstroy)*( cy3-cAstroy) );

    if ( distancia <= r1 + r2 || distancia1 <= r1 + r2 || distancia2 <= r1 + r2 ) {
        sn=1;
    }
    return sn;
}
//ATRAPALO
void fondomovil( int a, int xc, int direccion) {

    int c1x, c2x, c3x, c1y, c2y, c3y, cAstrox, cAstroy, colisionar, i;

    int meteoritosCoor[2][3] = {{150, 400, 750},{250, 500, 650}};
    srand(time(NULL));
    al_draw_scaled_bitmap(fondo_atra, 0, a + 3950, 800, 4500, 0, 0, 800, 4500, 0);


    if (direccion == 1 && xc < 50)
        al_draw_scaled_bitmap(astronauta, 0, 0, 527, 653, xc + 335, 250, 125, 125, 0); //izquierda
    else {
        al_draw_scaled_bitmap(astronauta, 0, 0, 527, 653, xc + 335, 250, 125, 125,ALLEGRO_FLIP_HORIZONTAL); //derecha
    }
    cAstrox = (xc + 335 + 125) - 62;
    cAstroy = (250 + 125) - 80;
    if (y == 525) {
        y = -70;
        yo = -70;
        y2 = -70;
    }
    i=rand()%2;
    if (y == -70) {
        x = rand() % 3;
        x = meteoritosCoor[i][x];
        xo = rand() % 3;
        xo = meteoritosCoor[i][xo];
        x2 = rand() % 3;
        x2 = meteoritosCoor[i][x2];
    }
    c1x = (x + 50) - 27;
    c1y = (y + 117)-2;
    c2x = (xo + 50) - 27;
    c2y = (yo + 117)-2;
    c3y = (y2 + 117)-2;
    c3x = (x2 + 50) - 27;
    if (a<-20 && a>-3900) {
        al_draw_scaled_bitmap(meteorito, 0, 0, 210, 408, x, y += 35, 46.3, 88, 0);
        al_draw_scaled_bitmap(meteorito, 0, 0, 210, 408, xo, yo += 35, 46.3, 88, 0);
        al_draw_scaled_bitmap(meteorito, 0, 0, 210, 408, x2, y2 += 35, 46.3, 88, 0);
        //que no colisione
        colisionar = colisiono(c1x, c1y, c2x, c2y, c3x, c3y, cAstrox, cAstroy);

       // al_draw_filled_circle(c1x, c1y, 18, al_map_rgb(87, 198, 134));
        if (colisionar == 1) {
            vidas--;
            y=455;
            yo=455;
            y2=455;
            al_play_sample(colision,50,1,1,ALLEGRO_PLAYMODE_ONCE, NULL );
        }
    }
    if(vidas>0 && a==-3940)
    {
        al_play_sample(ganador,1,1,1,ALLEGRO_PLAYMODE_ONCE, NULL );
        pantallaganaste=1;
    }
    if (vidas>2)
    {
        al_draw_scaled_bitmap(corazon, 0, 0, 677, 444, 760, 450, 30, 19.2, 0);
    }
    if(vidas>1)
    {
        al_draw_scaled_bitmap(corazon, 0, 0, 677, 444, 735, 450, 30, 19.2, 0);
    }
    if(vidas>0)
    {
        al_draw_scaled_bitmap(corazon, 0, 0, 677, 444, 710, 450, 30, 19.2, 0);
    }

    //MOSTRAR LA PANTALLA DE PERDISTE
    if(vidas==0)
    {
        al_draw_scaled_bitmap(fondo, 0, 0, 1920, 1080, 0, 0, 800, 500, 0);
        al_play_sample(perdiste,1,1,1,ALLEGRO_PLAYMODE_ONCE, NULL );
        pantallaperdiste=1;
    }
    al_flip_display();
}
//OBTENER PREGUNTAS
void obtenerPreguntas(char pregunta[100], int fila)
{
    int  i;
    FILE *arch;
    //llenando el arreglo de \0
    for (i=0;i<50;i++) {
        pregunta[i] = '\0';
    }

    //hacer archivo de preguntas
    arch=fopen("Trivia/preguntas.txt", "r");
    if(!arch)
        printf("No se pudieron cargar las preguntas");
    //checar archivo
    for (i=0;i<fila;i++)
    {
        fgets(pregunta, 100,arch);
    }
    for(i=0;i<100;i++)
    {
        if(pregunta[i] == ';')
        {
            pregunta[i]='\0';
            i++;
            pregunta[i]='\0';
            i++;
            pregunta[i]='\0';
            i=100;
        }
    }
    fclose(arch);
}
//OBTENER OPCIONES
void obtenerOpciones(char opA[50], char opB[50], char opC[50], int fila) {
    //A siempre es la correcta
    //Las cordenadas donde se muestran rando
    int o = 0, u = 0, i;
    FILE *arch;
    char opciones[300];
    //llenando el arreglo de \0
    for (i = 0; i < 300; i++) {
        opciones[i] = '\0';
    }
    //hacer archivo de preguntas
    arch = fopen("Trivia/respuestas.txt", "r");
    if (!arch)
        printf("No se pudieron cargar las opciones");
    //checar archivo
    for (i = 0; i < fila; i++) {
        fgets(opciones, 300, arch);

    }

    while (opciones[o] != ';') {
        opA[u] = opciones[o];
        u++;
        o++;
    }
    o++;
    opA[u] = '\0';
    u = 0;
    while (opciones[o] != ';') {
        opB[u] = opciones[o];
        u++;
        o++;
    }
    o++;
    opB[u] = '\0';
    u = 0;
    while (opciones[o] != ';') {
        opC[u] = opciones[o];
        u++;
        o++;
    }
    opC[u] = '\0';


    fclose(arch);
}
//TRIVIA
int triviaPantalla()
{
    ALLEGRO_FONT *fuentepregunta;

    char opcionA[50], opcionB[50], opcionC[50], pregunta[300];
    int preguntado[10];
    int coordenadasOp[3]={270, 360, 450}, coordenada1, coordenada2, coordenada, coordenada3;

    int fila, correcto=0, i, numPregunta=0, Yapreguntado=0;
    ALLEGRO_BITMAP *pantallaEsperaResp;
    pantallaEsperaResp = al_load_bitmap("Imagenes/PantallaTrivia.png");

    if(!pantallaEsperaResp)
    {
        printf("No se pudo cargar la imagen de trivia");
    }
    al_draw_scaled_bitmap(pantallaEsperaResp, 0, 0, 1920, 1080, 0, 0, 800, 500, 0);

    //MOSTRAR LOS CORAZONES EN LA TRIVIA
    if (vidas_trivia>2)
    {
        al_draw_scaled_bitmap(corazon, 0, 0, 677, 444, 710, 35, 30, 19.2, 0);
    }
    if(vidas_trivia>1)
    {
        al_draw_scaled_bitmap(corazon, 0, 0, 677, 444, 735, 35, 30, 19.2, 0);
    }
    if(vidas_trivia>0)
    {
        al_draw_scaled_bitmap(corazon, 0, 0, 677, 444, 760, 35, 30, 19.2, 0);
    }

    //MOSTRAR EL FONDO SI PERDIÓ
    if(vidas_trivia==0)
    {
        al_draw_scaled_bitmap(fondo, 0, 0, 1920, 1080, 0, 0, 800, 500, 0);
        al_play_sample(perdiste,1,1,1,ALLEGRO_PLAYMODE_ONCE, NULL );
        pantallaperdiste=1;
    }


    fuentepregunta=al_load_font("Fuentes/letra-pixelada.ttf", 10, 0);
    //Elegir aleatoriamente la regunta
    srand(time(NULL));
    fila = rand()%17;

    if(vidas_trivia>0)
    {
        obtenerPreguntas(pregunta, fila);
        //imprimir la pregunta
        al_draw_text(fuentepregunta, al_map_rgb(0, 0, 0), 57, 110, ALLEGRO_ALIGN_LEFT, pregunta);
        // imprimir las opciones
        obtenerOpciones(opcionA, opcionB, opcionC, fila);

        //respuesta correcta
        srand(time(NULL));
        coordenada = rand() % 3;
        al_draw_text(fuentepregunta, al_map_rgb(0, 0, 0), 400, coordenadasOp[coordenada], ALLEGRO_ALIGN_LEFT, opcionA);
        coordenada1 = coordenada;

        srand(time(NULL));
        coordenada = rand() % 3;
        while (coordenada == coordenada1) {
            coordenada = rand() % 3;
        }
        al_draw_text(fuentepregunta, al_map_rgb(0, 0, 0), 400, coordenadasOp[coordenada], ALLEGRO_ALIGN_LEFT, opcionB);
        coordenada2 = coordenada;
        srand(time(NULL));
        coordenada = rand() % 3;
        while (coordenada == coordenada1 || coordenada == coordenada2) {
            coordenada = rand() % 3;
        }
        coordenada3 = coordenada;
        al_draw_text(fuentepregunta, al_map_rgb(0, 0, 0), 400, coordenadasOp[coordenada], ALLEGRO_ALIGN_LEFT, opcionC);
        al_flip_display();
        coordenada1++;
    }
    al_flip_display();
    return coordenada1;
}
//PREGUNTA CORRECTA TRIVIA
void pregCorrecta()
{
   // printf("\nbien");
    al_draw_filled_rectangle(0, 150, 800, 350, al_map_rgb(55, 44, 98));
    al_draw_text(fuentegrande, al_map_rgb(255, 255, 255),225, 230, ALLEGRO_ALIGN_LEFT, "Correcto :)");
    al_draw_text(fuentechica, al_map_rgb(255, 255, 255),200, 290, ALLEGRO_ALIGN_LEFT, "Presiona cualquier tecla para continuar");
    al_play_sample(respuesta_correcta,1,1,1,ALLEGRO_PLAYMODE_ONCE, NULL );
    al_flip_display();
}
//PREGUNTA INCORRECTA TRIVIA
void pregIncorrecta()
{
    //printf("\nmal");
    al_draw_filled_rectangle(0, 150, 800, 350, al_map_rgb(55, 44, 98));
    al_draw_text(fuentegrande, al_map_rgb(255, 255, 255),225, 230, ALLEGRO_ALIGN_LEFT, "Incorrecto :(");
    al_draw_text(fuentechica, al_map_rgb(255, 255, 255),200, 290, ALLEGRO_ALIGN_LEFT, "Presiona cualquier tecla para continuar");
    al_play_sample(respuesta_incorrecta,1,1,1,ALLEGRO_PLAYMODE_ONCE, NULL );
    vidas_trivia--;
    al_flip_display();
}
//COLISION CARRERA
int colisiono2()
{
    int sn=0, distancia, distacia1, px, py, px2, py2, r=11;

    // Círculo con centro en (cx,cy) y radio r
// Rectángulo con esquina superior izquierda en (x,y) ancho w y algto h
// Punto (en verde) del perímetro del rectángulo más cercano a la circunferencia en (px,py)
    px = centroMeCa1x; // En principio son iguales
    if ( px < cabezax ) px = cabezax;
    if ( px > cabezax + ancho ) px = cabezax + ancho;
    py = centroMeCa1y;
    if ( py < cabezay ) py = cabezay;
    if ( py > cabezay + largo ) py = cabezay + largo;
    distancia = sqrt( (centroMeCa1x - px)*(centroMeCa1x- px) + (centroMeCa1y - py)*(centroMeCa1y - py) );
    if ( distancia < r ) {
        sn=1;
        xmet=0;

    }
    px2 = centroMeCa2x; // En principio son iguales
    if ( px2 < cabezax ) px2 = cabezax;
    if ( px2 > cabezax + ancho ) px2 = cabezax + ancho;
    py2 = centroMeCa2y;
    if ( py2 < cabezay ) py2 = cabezay;
    if ( py2 > cabezay + largo ) py2 = cabezay + largo;
    distancia = sqrt( (centroMeCa2x - px2)*(centroMeCa2x- px2) + (centroMeCa2y - py2)*(centroMeCa2y - py2) );
    if ( distancia < r ) {
        sn=1;
        x2met=0;
    }
    return sn;
}
//METEOROS CARRERAS
void meteoritos()
{
    int coory[3]={260, 325, 370};
    //centros
    int cx1, cy1, cx2, cy2;

    srand(time(NULL));
    if(segundo==1)
        rango=rand()%200+600;
    if(xmet==0) {
        xmet=1100;
    }
    if(xmet==800)
    {
        ymet=rand()%3;
        ymet=coory[ymet];
    }

    al_draw_scaled_bitmap(meteorito_carrera, 0, 0, 408, 210,  xmet -= 50, ymet, 47.5,25,  0);
    //centros
    centroMeCa1x=(xmet+47.5)-(47.5/2)-10;
    centroMeCa1y=(ymet+25)-(25/2)-1;
    // al_draw_filled_circle(centroMeCa1x, centroMeCa1y, 11, al_map_rgb(56, 87, 90));
    if(xmet<rango && segundo==1)
    {
        segundo=0;
        x2met=1100;
        y2met=rand()%3;
        y2met=coory[y2met];
    }

    al_draw_scaled_bitmap(meteorito_carrera, 0, 0, 408, 210,  x2met -= 50, y2met, 47.5,25,  0);
    if(x2met==0)
    {
        x2met=1000;
        segundo=1;
    }
    centroMeCa2x=(x2met+47.5)-(47.5/2)-10;
    centroMeCa2y=(y2met+25)-(25/2)-1;
    //al_draw_filled_circle(centroMeCa2x, centroMeCa2y, 11, al_map_rgb(56, 87, 90));
    if(colisiono2()==1)
    {
        vidas--;
        al_play_sample(colision,50,1,1,ALLEGRO_PLAYMODE_ONCE, NULL );
    }

}
//CARRERA
void carrera()
{

    //if para que tenga un límite el fondo
    if(c>=0 && c<=9205)
    {
        al_draw_scaled_bitmap(fondo_carrera, c, 0, 800, 508, 0, 0, 800, 500, 0);
    }
    //if para que cuando llegue al final suene una misiquita
    if(c == 9400)
    {
        sonido_ganador();
        al_play_sample(ganador, 1, 1, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
    }

    //Corazones vidas
    if(vidas>2)
        al_draw_scaled_bitmap(corazon, 0, 0, 607, 444, 680, 460, 25, 25, 0);
    if(vidas>1)
        al_draw_scaled_bitmap(corazon, 0, 0, 607, 444, 715, 460, 25, 25, 0);
    if(vidas>0)
        al_draw_scaled_bitmap(corazon, 0, 0, 607, 444,  750, 460, 25, 25, 0);

    //Astronauta del inicio (opcional)
    if(direccion_carrrera == 0)
    {
        al_draw_scaled_bitmap(astronauta_quieto, 0, 0, 400, 488, 200, 304, 75, 100, 0);
    }
    //Astronauta mirando a la izquierda
    if(direccion_carrrera == 1)
    {
        cx=200;
        cy=304;
        ancho=65;
        largo=100;
        al_draw_scaled_bitmap(astronauta_carrera, 0, 0, 446, 655, cx, cy, ancho, largo,ALLEGRO_FLIP_HORIZONTAL); //Izquierda
        //Guarda el lado en el que está para el salto
        lado_carrera=1;
    }
    //Astronauta mirando a la derecha
    if(direccion_carrrera == 2)
    {
        cx=200;
        cy=304;
        ancho=65;
        largo=100;
        al_draw_scaled_bitmap(astronauta_carrera, 0, 0, 446, 655, cx, cy, ancho, largo, 0); //Derecha
        //Guarda el lado en el que está para el salto
        lado_carrera=2;
    }
    //Astronauta saltando
    if(direccion_carrrera == 3)
    {
        cx=200;
        cy=254;
        ancho=65;
        largo=100;
        //Salto derecha
        if(lado_carrera==2)
        {

            al_draw_scaled_bitmap(astronauta_salto, 0, 0, 327, 522, cx, cy, ancho, largo,  0);
        }
        //Salto izquierda
        if(lado_carrera==1)
        {
            al_draw_scaled_bitmap(astronauta_salto, 0, 0, 327, 522, cx, cy, ancho, largo, ALLEGRO_FLIP_HORIZONTAL);
        }

    }
    //Astronauta agachado
    if(direccion_carrrera==4)
    {
        cx=200;
        cy=354;
        ancho=65;
        largo=100;
        //Agachado derecha
        if(lado_carrera==2)
        {
            al_draw_scaled_bitmap(astronauta_agachado, 0, 0, 493, 663, cx, cy, ancho, largo, ALLEGRO_FLIP_HORIZONTAL);
        }
        //Agachado izquierda
        if(lado_carrera==1)
        {
            al_draw_scaled_bitmap(astronauta_agachado, 0, 0, 493, 663, cx, cy, ancho, largo, 0);
        }
    }
    // cabezax=(cx+ancho)-(ancho/2);
    // cabezay=(cy+largo)-(largo/2)-15;
    //cuerpox=cx+ancho;
    //cuerpoy=cy+ancho;
    cabezax=cx;
    cabezay=cy;
    //   al_draw_filled_circle(cabezax,cabezay , 28, al_map_rgb(45, 87, 100));
    //  al_draw_filled_rectangle(cx, cy, cuerpox, cuerpoy, al_map_rgb(56, 98, 230));
    if(direccion_carrrera!=0 && c<=9205)
    {
        meteoritos();
    }

    if(vidas==0)
    {
        al_draw_scaled_bitmap(fondo, 0, 0, 1920, 1080, 0, 0, 800, 500, 0);
        al_play_sample(perdiste,1,1,1,ALLEGRO_PLAYMODE_ONCE, NULL );
        pantallaperdiste=1;
    }
    al_flip_display();
}
//AHORCADO
void Ahorcado()
{
    printf("Ahorcado");
}
//MENU
void imagen_menu()
{
    ALLEGRO_BITMAP *menu;
    menu = al_load_bitmap("Imagenes/Fondo_Menu.jpg");
    if(!menu)
    {
        printf("No se cargo la imagen de fondo");
    }
    al_draw_scaled_bitmap(menu, 0, 0, 700, 395, 0, 0, 800, 500, 0);
    al_draw_text(fuente1, al_map_rgb(255, 255, 255), 400, 260, ALLEGRO_ALIGN_CENTRE, "1. Jugar");
    al_draw_text(fuente1, al_map_rgb(255, 255, 255), 400, 310, ALLEGRO_ALIGN_CENTRE, "2. Reglas");
    al_draw_text(fuente1, al_map_rgb(255, 255, 255), 400, 360, ALLEGRO_ALIGN_CENTRE, "3. Creditos");
    al_draw_text(fuente1, al_map_rgb(255, 255, 255), 400, 410, ALLEGRO_ALIGN_CENTRE, "4. Salir");
    al_flip_display();
}
//FONDO CRÉDITOS
void Pancreditos()
{
    ALLEGRO_BITMAP *creditos;
    creditos = al_load_bitmap("Imagenes/Fondo_Creditos.jpg");
    if(!creditos)
    {
        printf("No se cargo la imagen de creditos");
    }
    al_draw_scaled_bitmap(creditos, 0, 0, 700, 400, 0, 0, 800, 500, 0);
    al_flip_display();
}
//FONDO REGLAS
void Panreglas()
{
    ALLEGRO_BITMAP *reglas;
    reglas = al_load_bitmap("Imagenes/Fondo_Reglas.jpg");
    if(!reglas)
    {
        printf("No se cargo la imagen de reglas");
    }
    al_draw_scaled_bitmap(reglas, 0, 0, 700, 400, 0, 0, 800, 500, 0);
    al_flip_display();
}
//FONDO COMIENZO
void contexto()
{
    ALLEGRO_BITMAP *historia;
    historia= al_load_bitmap("Imagenes/Fondo_Comienzo.jpg");
    if(!historia)
    {
        printf("No se cargo la imagen del comienzo");
    }
    al_draw_scaled_bitmap(historia, 0, 0, 700, 395, 0, 0, 800, 500, 0);
    al_flip_display();
}
//FONDO DE PREGUNTA ENTRE JUEGOS
void entrejuegos()
{
    pantallaseguir=1;
    entreJuegos= al_load_bitmap("Imagenes/CambioJuego.jpg");
    if(!entreJuegos)
    {
        printf("No se cargo la imagen entre juego");
    }
    al_draw_scaled_bitmap(entreJuegos, 0, 0, 704, 394, 0, 0, 800, 500, 0);
    mostrarImagenGanador=2;
    al_flip_display();
}
//FONDO PARA CUANDO GANE LA TRIVIA
void felicidades()
{
    fondo_ganador= al_load_bitmap("Imagenes/LoLograste.png");
    if(!fondo_ganador)
    {
        printf("No se cargo la imagen del logrado");
    }
    pantallaganaste=1;
    al_draw_scaled_bitmap(fondo_ganador, 0, 0, 1920, 1100, 0, 0, 800, 500, 0);
    //al_draw_text(fuente1, al_map_rgb(255, 255, 255), 40, 400, ALLEGRO_ALIGN_LEFT, "Respondiste 3 preguntas correctamente");
    //mostrarImagenGanador=1;
    al_play_sample(ganador,1,1,1,ALLEGRO_PLAYMODE_ONCE, NULL );
    al_flip_display();
}
//FONDO SE AGOTÓ EL TIEMPO
void seAgotoTiempo()
{
    al_draw_scaled_bitmap(fondo, 0, 0, 1920, 1080, 0, 0, 800, 500, 0);
    al_draw_text(fuentegrande, al_map_rgb(255, 255, 255), 140, 300, ALLEGRO_ALIGN_LEFT, "Se agotó el tiempo");
    al_flip_display();
}

int main()
{
    ALLEGRO_DISPLAY *disp;
    ALLEGRO_EVENT_QUEUE *eventos;
    ALLEGRO_EVENT evento;
    ALLEGRO_TIMER *timer3min;
    ALLEGRO_BITMAP *icono;
    int fin = 0, puntoEnElJuego = 1, redibujar=0,minijuego=0, tiempo=1, x1 = 0, direccion = 1, a = 20;
    int correcta=0, respuesta=0, cambioPregunta=1, Preguntascorrectas=0, jugando=0;

    //INICIAR LOS COMPLEMENTOS
    if (!al_init()) {
        printf("No se pudo iniciar allegro");
        fin = 1;
    }
    if (!al_init_primitives_addon() || !al_install_keyboard() || !al_init_font_addon() || !al_init_ttf_addon())
    {
        printf("No se pudieron inicializar los complementos");
        fin = 1;
    }
    if (!al_install_audio() || !al_init_acodec_addon() || !al_init_image_addon())
    {
        printf("No se pudo inicializar complemento de audio");
        fin = 1;
    }
    //El "5" sirve para decir cuantas canciones va a tener el juego
    if(!al_reserve_samples(5))
    {
        printf("No se pudo reservar las pistas");
        fin = 1;
    }
    //ASIGNAR PARA LA MUSICA
    colision = al_load_sample("Musica/Explosion.mp3");
    ganador = al_load_sample("Musica/Ganador.mp3");
    respuesta_correcta = al_load_sample("Musica/RespuestaCorrecta.mp3");
    respuesta_incorrecta = al_load_sample("Musica/Respuesta_Incorrecta.mp3");
    perdiste = al_load_sample("Musica/Perdiste.mp3");
    //VERIFICAR SI SE CARGO EL AUDIO
    if(!colision || !ganador || !respuesta_correcta || !respuesta_incorrecta || !perdiste)
    {
        printf("No se cargo la musica");
        fin = 1;
    }

    icono = al_load_bitmap("Imagenes/icono.jpg");
    if (!icono) {
        printf("No se cargo el icono");
        fin = 1;
    }
    //ASIGNACION PARA IMAGENES
    fondo_carrera = al_load_bitmap("Imagenes/Fondo_Carrera_Obstaculos.jpg");
    astronauta_carrera = al_load_bitmap("Imagenes/Astronauta_Perfil_Derecho.png");
    astronauta_salto = al_load_bitmap("Imagenes/Astronauta_Caminando_Derecha.png");
    astronauta_quieto = al_load_bitmap("Imagenes/Astronauta_Frente2.png");
    meteorito = al_load_bitmap("Imagenes/Meteorito_Vertical.png");
    astronauta_agachado = al_load_bitmap("Imagenes/Astronauta_Agachado2.png");
    fondo = al_load_bitmap("Imagenes/LoSentimos.png");
    meteorito_carrera = al_load_bitmap("Imagenes/Meteorito_Horizontal.png");
    fondo_atra = al_load_bitmap("Imagenes/Fondo_Esquivalo.jpg");
    astronauta = al_load_bitmap("Imagenes/Astronauta_Esquivalo.png");
    corazon = al_load_bitmap("Imagenes/CorazonJuego.png");
    //VERIFICAR SI SE CARGARON LAS IMAGENES
    if(!fondo_carrera || !astronauta_carrera || !astronauta_salto || !astronauta_quieto || !meteorito)
    {
        printf("No se cargaron las imagenes 1");
    }
    if(!astronauta_agachado || !fondo || !meteorito_carrera || !fondo_atra || !astronauta || !corazon)
    {
        printf("No se cargaron las imagenes 2");
    }

    //VENTANA
    disp = al_create_display(800, 500);
    al_set_window_title(disp, "Rescate Espacial");
    al_set_display_icon(disp, icono);
    al_clear_to_color(al_map_rgb(150, 150, 150));
    al_flip_display();

    //FUENTES
    fuente1 = al_load_font("Fuentes/letra-pixelada.ttf", 20, 0);
    fuentegrande = al_load_font("Fuentes/letra-pixelada.ttf", 30, 0);
    fuentechica = al_load_font("Fuentes/letra-pixelada.ttf", 10, 0);
    if (!fuente1 || !fuentegrande || !fuentechica)
    {
        printf("No se pudieron cargar las fuentes");
        fin = 1;
    }

    //EVENTOS
    eventos = al_create_event_queue();
    al_register_event_source(eventos, al_get_display_event_source(disp));
    al_register_event_source(eventos, al_get_keyboard_event_source());
    imagen_menu();
    timer3min = al_create_timer(40);
    timeresperar = al_create_timer(6);
    timer_atrapalo = al_create_timer(0.2);
    al_register_event_source(eventos, al_get_timer_event_source(timer3min));
    al_register_event_source(eventos, al_get_timer_event_source(timer_atrapalo));
    al_register_event_source(eventos, al_get_timer_event_source(timeresperar));


    while (fin == 0)
    {
        if (al_event_queue_is_empty(eventos) && redibujar==1)
        {
            switch (puntoEnElJuego) {
                case 1:
                {
                    //MENU
                    imagen_menu();
                    xmet=0;
                    x2met=0;
                    y2met=0;
                    y=-70;
                    yo=-70;
                    y2=-70;
                    vidas_trivia=3;
                    minijuego=0;
                    vidas=3;
                    c=0;
                    a=20;
                    correcta=0;
                    respuesta=0;
                    cambioPregunta=1;
                    Preguntascorrectas=0;
                    jugando=0;
                    tiempo=1;
                    x1 = 0;
                    direccion = 1;
                    a = 20;
                    direccion_carrrera=0;
                    lado_carrera=0;
                    segundo=1;
                    pantallaperdiste=0;
                    pantallaganaste=0;
                    pantallaseguir=0;
                    break;
                }
                case -1:
                {
                    //REGLAS
                    Panreglas();
                    break;
                }
                case -2:
                {
                    //CREDITOS
                    Pancreditos();
                    break;
                }
                case 2:
                {
                    //MINIJUEGOS
                    if(minijuego==0)
                    {
                        contexto();
                    }
                    break;
                }
                case 3:
                {
                    //PREGUNTA ENTRE JUEGOS
                    entrejuegos();
                    pantallaseguir=1;
                    break;
                }
                case 4:
                {
                    //LA VERDAD NO SÉ, PERO AQUI ESTÁ XD
                    if(minijuego==3)
                    {
                        al_draw_text(fuente1, al_map_rgb(255, 255, 255), 100, 550, ALLEGRO_ALIGN_LEFT, "Respondiste las 3 preguntas");
                    }
                    break;
                }
                case 5:
                {
                    //FONDO FELICIDADES TRIVIA
                    felicidades();
                    break;
                }
                case 6:
                {
                    //FONDO FINAL
                    imagen_final();
                    break;
                }
            }

            if(puntoEnElJuego==2&&pantallaperdiste==0)
            {
                switch (minijuego)
                {
                    case 1:
                    {
                        //AHORCADO
                       // Ahorcado();
                        break;
                    }
                    case 2:
                    {
                        //TRIVIA
                        if(Preguntascorrectas<3 && tiempo==1)
                        {
                            jugando=1;
                            if (evento.timer.source == timer3min)
                            {
                                tiempo=0;
                                seAgotoTiempo();
                            }
                           // printf("%i", Preguntascorrectas);
                            if (cambioPregunta == 1) {
                                correcta = triviaPantalla();
                                if (Preguntascorrectas == 0 && vidas_trivia>0) {
                                    al_draw_text(fuente1, al_map_rgb(217, 0, 98), 105, 430, ALLEGRO_ALIGN_LEFT, "0");
                                }
                                if(Preguntascorrectas==1 && vidas_trivia>0)
                                {
                                    al_draw_text(fuente1, al_map_rgb(217, 0, 98), 105, 430,ALLEGRO_ALIGN_LEFT, "1" );
                                }
                                if(Preguntascorrectas==2 && vidas_trivia>0)
                                {
                                    al_draw_text(fuente1, al_map_rgb(217, 0, 98), 105, 430,ALLEGRO_ALIGN_LEFT, "2" );
                                }
                                cambioPregunta = 0;
                            }
                            if (respuesta != 0) {
                                //printf("\nCorrecta:%i Respuesta: %i", correcta, respuesta);
                                if (correcta == respuesta) {
                                    pregCorrecta();
                                    Preguntascorrectas += 1;
                                } else {
                                    pregIncorrecta();
                                }
                                respuesta = 0;
                                cambioPregunta = 1;
                            }
                            if(Preguntascorrectas==3 && vidas_trivia>0)
                            {
                                al_draw_filled_rectangle(98, 430, 130, 450, al_map_rgb(255, 255, 44));
                                al_draw_text(fuente1, al_map_rgb(217, 0, 98), 100, 430,ALLEGRO_ALIGN_LEFT, "3" );
                                //puntoEnElJuego=5;
                                jugando=0;

                                //CUANDO GANE SE MUESTRE LA PANTALLA DE FELICIDADES EN TRIVIA
                                felicidades();
                                //entrejuegos();

                                //minijuego++;
                            }
                        }
                        break;
                    }
                    case 3:
                    {
                        //ATRAPALO
                        if(a==20)
                        {
                            vidas=3;
                        }
                        if (vidas>0 && a<3920)
                        {
                            fondomovil(a, x1, direccion);
                        }
                        else if(vidas>0)
                        {
                            sonido_ganador();
                            pantallaganaste=1;
                        }
                        if (a == 3920)
                        {
                            puntoEnElJuego = 3; //pantalla continuar si o no
                            minijuego = 3;
                        }
                        if (vidas == 0)
                        {
                            al_draw_scaled_bitmap(fondo, 0, 0, 1920, 1080, 0, 0, 800, 500, 0);
                        }
                        break;
                    }
                    case 4:
                    {
                        //CARRERA
                        if(c==0)
                        {
                            vidas=3;
                        }
                        if(vidas>0 && c<=9205)
                        {
                            carrera();
                        }
                        if(vidas==0)
                        {
                            al_draw_scaled_bitmap(fondo, 0, 0, 1920, 1080, 0, 0, 800, 500, 0);
                            redibujar=0;
                        }

                        break;
                    }
                }
            }
            al_flip_display();
            redibujar=0;
        }


        //COSAS LÓGICAS
        al_wait_for_event(eventos, &evento);
        switch (evento.type) {
            case ALLEGRO_EVENT_DISPLAY_SWITCH_IN:
            {
                redibujar=1;
                break;
            }
            case ALLEGRO_EVENT_DISPLAY_CLOSE: {
                fin = 1;
                break;
            }
            case ALLEGRO_EVENT_TIMER: {

                if(puntoEnElJuego==2 && x1 !=0 )
                {
                    if(evento.timer.source == timer_atrapalo)
                    {
                        if(a>-3940) {
                            a-=20;
                        }
                    }
                    if(evento.timer.source==timer_atrapalo)
                    {
                        esperar=1;
                    }

                }

            }
            case ALLEGRO_EVENT_KEY_CHAR:
            {
                redibujar=1;
                switch (evento.keyboard.keycode)
                {
                    //JUGAR
                    case ALLEGRO_KEY_1:
                    {
                        if (puntoEnElJuego == 1)
                        {
                            puntoEnElJuego = 2; //Inicio juego
                        }
                        break;
                    }
                        //REGLAS
                    case ALLEGRO_KEY_2:
                    {
                        if (puntoEnElJuego == 1)
                        {
                            puntoEnElJuego = -1;

                        }
                        break;
                    }
                        //CREDITOS
                    case ALLEGRO_KEY_3:
                    {
                        if (puntoEnElJuego == 1)
                        {
                            puntoEnElJuego = -2;
                        }
                        break;
                    }
                        //SALIR
                    case ALLEGRO_KEY_4:
                    {
                        if (puntoEnElJuego == 1)
                        {
                            fin = 1;
                        }
                        break;
                    }
                        //REGRESAR AL MENU
                    case ALLEGRO_KEY_R:
                    {
                        if (puntoEnElJuego == 2 || puntoEnElJuego == -1  || puntoEnElJuego == -2)
                        {
                            puntoEnElJuego = 1; //Menú
                        }
                        break;
                    }
                        //CONFIRMAR QUE QUIERE SEGUIR JUGANDO
                    case ALLEGRO_KEY_S:
                    {
                        if(pantallaseguir==1)
                        {
                            minijuego++;
                            puntoEnElJuego=2;
                            if(puntoEnElJuego == 2 && minijuego==3)
                            {
                                al_start_timer(timer_atrapalo);
                            }
                            pantallaseguir=0;
                        }

                        break;
                    }
                        //RESPUESTAS TRIVIA
                    case ALLEGRO_KEY_A:
                    {
                        if(puntoEnElJuego==2 && minijuego==2)
                        {
                            respuesta=1;
                        }
                        break;
                    }
                    case ALLEGRO_KEY_B:
                    {
                        if(puntoEnElJuego==2 && minijuego==2)
                        {
                            respuesta=2;
                        }
                        break;
                    }
                    case ALLEGRO_KEY_C:
                    {
                        if(puntoEnElJuego==2 && minijuego==2)
                        {
                            respuesta=3;
                        }
                        break;
                    }
                        //NEGAR QUE QUIERE SEGUIR JUGANDO
                    case ALLEGRO_KEY_N:
                    {
                        if(pantallaseguir==1)
                        {
                            pantallaseguir=0;
                            puntoEnElJuego=1;
                        }

                        break;
                    }
                        //TEMPORAL SOLO PARA NOSOTROS
                    case ALLEGRO_KEY_Z:
                    {
                        minijuego++;
                        if(minijuego==3)
                        {
                            al_start_timer(timer_atrapalo);
                        }
                        if(puntoEnElJuego==4)
                        {
                            minijuego=3;
                        }
                        break;
                    }
                        //TRIVIA: PASA DE LA FELICITACION A LA PREGUNTA
                        //ATRAPALO: PASA A PREGUNTAR
                        //CARRERA: PASA A LA IMAGEN FINAL
                    case ALLEGRO_KEY_ENTER:
                    {
                        if(pantallaganaste==1)
                        {
                            if(puntoEnElJuego==2 && minijuego==2)
                            {
                                entrejuegos();
                                pantallaseguir=1;
                            }
                            if(puntoEnElJuego==2 && minijuego==3)
                            {
                                puntoEnElJuego=3;
                            }
                            if(puntoEnElJuego == 2 && minijuego == 4)
                            {
                                puntoEnElJuego = 6;
                            }
                            pantallaganaste=0;
                        }

                        break;
                    }
                        //PARA MOVER AL ASTRONAUTA EN ATRAPALO Y CARRERA
                    case ALLEGRO_KEY_DOWN:
                    {
                        if(puntoEnElJuego==2 && minijuego==4)
                        {
                            direccion_carrrera = 4;
                        }
                        break;
                    }
                    case ALLEGRO_KEY_UP:
                    {
                        if(puntoEnElJuego==2 && minijuego==4)
                        {
                            direccion_carrrera = 3;
                        }
                        break;
                    }
                    case ALLEGRO_KEY_RIGHT:
                    {
                        if(puntoEnElJuego==2 && minijuego==3)
                        {
                            direccion = 1;
                            if(x1<250)
                            {
                                x1 = x1 + 10;
                            }
                        }
                        if(puntoEnElJuego==2 && minijuego==4)
                        {
                            direccion_carrrera = 2;
                            c = c + 20;
                        }
                        break;
                    }
                    case ALLEGRO_KEY_LEFT:
                    {
                        if(puntoEnElJuego==2 && minijuego==3)
                        {
                            direccion = 2;
                            if(x1>-250)
                            {
                                x1 = x1 - 10;
                            }
                        }
                        if(puntoEnElJuego==2 && minijuego==4)
                        {
                            direccion_carrrera = 1;
                            c = c - 20;
                        }
                        break;
                    }
                        //PARA SALIR DE CUALQUIER JUEGO Y DE LA IMAGEN FINAL
                    case ALLEGRO_KEY_ESCAPE:
                    {
                        if(puntoEnElJuego==2 && minijuego==1 && pantallaperdiste==1)
                        {
                            pantallaperdiste=0;
                            puntoEnElJuego=1;
                        }
                        if(puntoEnElJuego==2 && minijuego==2 && pantallaperdiste==1)
                        {
                            pantallaperdiste=0;
                            puntoEnElJuego=1;
                        }
                        if(puntoEnElJuego==2 && minijuego==3&& pantallaperdiste==1)
                        {
                            pantallaperdiste=0;
                            puntoEnElJuego=1;
                        }
                        if(puntoEnElJuego==2 && minijuego==4 && pantallaperdiste==1)
                        {
                            pantallaperdiste=0;
                            puntoEnElJuego=1;
                        }
                        if(puntoEnElJuego==6)
                        {
                            pantallaperdiste=0;
                            puntoEnElJuego=1;
                        }
                        break;
                    }
                    case ALLEGRO_KEY_SPACE:
                    {
                        if(puntoEnElJuego==2 && minijuego==0)
                        {
                            minijuego=2;
                        }
                        break;
                    }
                }
                break;
            }
        }
    }

    al_destroy_display(disp);
    al_destroy_event_queue(eventos);
    return 0;
}