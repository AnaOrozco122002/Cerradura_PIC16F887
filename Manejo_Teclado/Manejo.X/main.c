/*
 * File:   main.c
 * Author: :C
 *
 * Created on June 19, 2022, 4:00 PM
 */


#include "config.h"
#include "teclado.h"

// Procedimientos

void Prender_Verde(){
    RC0 = 1;
}
void Apagar_Verde(){
    RC0 = 0;
}
void Prender_Rojo(){
    RC1 = 1;
}
void Apagar_Rojo(){
    RC1 = 0;
}
void Sonar(){
    RC2 = 1;
    __delay_ms(100);
    RC2=0;
    __delay_ms(100);
}
void Bloqueo(){
    RC2 = 1;
    __delay_ms(1000);
    RC2=0;
    __delay_ms(100);
}
//Variables
int Try=0,True=0; //Intentos para digitar la clave correctamente
int X,XD,XC,XM=0; //Para Suma de Numeros
int Clave,Tecla; //Control de Clave
int Bandera = 0; //Control de Ciclos
//Contraseña
int Password=1202;
//Main
int main()
{ 
  char Cadena[20];
  TRISD = 0x00;  //Salida LCD 
  TRISC = 0x00;  //Salida LED y BUCER
  TRISB = 0xF0; //Entradas y Salidas
  PORTD = 0;
  PORTC = 0;
  PORTB = 0;
  
  Lcd_Init();
  Lcd_Clear();
  Lcd_Set_Cursor(1,4);
  Lcd_Write_String("Cerradura");
  Lcd_Set_Cursor(2,3);
  Lcd_Write_String("Electronica");
  Prender_Rojo();
  __delay_ms(1000);
  
  
  while((Try < 3) && (True == 0) ){
    
    Apagar_Verde();  
    //Ingreso de Contraseña 
    Tecla = Leer_tecla();
    if((Tecla != 100) && (Tecla != 42) && (Tecla != 35)){
        if(Bandera == 0){
          Sonar();  
          __delay_ms(500);
          sprintf(Cadena,"Primer Digito %i",Tecla);
          Lcd_Clear();
          Lcd_Set_Cursor(1,1);
          Lcd_Write_String(Cadena);
          __delay_ms(500);
          XM = Tecla * 1000;
          Bandera ++;
        }
        else if (Bandera == 1){
            Sonar();
            sprintf(Cadena,"Segundo Digito %i",Tecla);
            Lcd_Clear();
            Lcd_Set_Cursor(1,1);
            Lcd_Write_String(Cadena);
            __delay_ms(500);
            XC = Tecla * 100;
            Bandera ++;
        }
        else if (Bandera == 2){
            Sonar();
            sprintf(Cadena,"Tercer Digito %i",Tecla);
            Lcd_Clear();
            Lcd_Set_Cursor(1,1);
            Lcd_Write_String(Cadena);
            __delay_ms(500);
            XD = Tecla * 10;
            Bandera ++;
        }
        else if(Bandera == 3){
            Sonar();
            sprintf(Cadena,"Cuarto Digito %i",Tecla);
            Lcd_Clear();
            Lcd_Set_Cursor(1,1);
            Lcd_Write_String(Cadena);
            __delay_ms(500);
            X = Tecla;
            Bandera ++;
        }
      
       //Contraseña Ingresada 
       Clave = X + XD + XC + XM; 
    }
    if(Clave == Password){
        True = 1;
        Apagar_Rojo();
        Prender_Verde();
        Lcd_Clear();
        Lcd_Set_Cursor(1,4);
        Lcd_Write_String("Cerradura");
        Lcd_Set_Cursor(2,5);
        Lcd_Write_String("Abierta");
        __delay_ms(5000);
    }
    else if(Bandera == 4){
        
        Lcd_Clear();
        Lcd_Set_Cursor(1,6);
        Lcd_Write_String("Wrong");
        Lcd_Set_Cursor(2,5);
        Lcd_Write_String("Password");
        __delay_ms(2000);
        Try ++;
        Bandera =  0;
        if(Try == 3){
            Bloqueo();
            Lcd_Clear();
            Lcd_Set_Cursor(1,4);
            Lcd_Write_String("Bloqueada");
            __delay_ms(3000);
            True = 2;
            __delay_ms(500);
        }
        else{
            Lcd_Clear();
            Lcd_Set_Cursor(1,4);
            Lcd_Write_String("Try Again");
            __delay_ms(1500);
            Lcd_Clear();
            Lcd_Set_Cursor(1,5);
            Lcd_Write_String("Press #");
            Tecla = Leer_tecla();
            __delay_ms(500);
            while(Tecla != 35){
                Tecla = Leer_tecla();
                __delay_ms(500);
            }
            Sonar();
            Lcd_Clear();
            Lcd_Set_Cursor(1,3);
            Lcd_Write_String("Ingrese Clave");
            Lcd_Set_Cursor(2,4);
            Lcd_Write_String("Otra Vez");
        }
           
           
       }
       
      //Fin del While de Clave 
      }
  
      
  return 0;
}

