//Autor: Marcos Sarmiento Pellitero
//Fecha de creación: 26 de octubre de 2023

//Descripción: En este código se va a tratar de realizar un programa que permita introducir una distribución 
//de cargas puntuales en un espacio y permita calcular los momentos dipolares correspondientes a dicha 
//distribución

//Sección de paquetes empleados

#include <iostream>
#include <cmath>
#include "vecandmat.h"

//Sección de clases

//Sección de Funciones

//Esta función recibe una matriz y el número de partículas que se va a tener en el problema y pide que se introduzcan las coordenadas correspondientes para cada partícula

void establecer_vectores(matrix& mat, int n){

    int i;

    std::cout << "\nIntroduzca el valor de la carga de la " << n+1 << "º partícula.\n" << std::endl;
    std::cin >> mat[0][n];

    std::cout << "\nIntroduzca las coordenadas cartesianas atribuidas a la " << n+1 << "º partícula.\n" << std::endl;

    for (i = 1; i < 4; i++){
        
        std::cin >> mat[i][n];
          
    }

}

//Se calcula el momento monopolar. Para ello se suma el valor de las cargas de todas las partículas.

int calc_mom_monopolar(matrix mat, int n){
    
    int mom_monopolar = 0, i;

    for (i=0; i<n; i++){
        
        mom_monopolar = mom_monopolar + mat[0][i];

    }

    return mom_monopolar;

}

//Se calcula el momento dipolar. 

rows calc_mom_dipolar(matrix mat, int n){

    rows mom_dipolar(3);
    int i, j;

    for(j = 0; j < 3; j++){
        mom_dipolar[j] = 0;
        for(i = 0; i < n; i++){

            mom_dipolar[j] = mom_dipolar[j] + mat[0][i]*mat[j+1][i];

        }
    }

    return mom_dipolar;
}

//Se calcula el momento cuadrupolar

matrix mom_cuadrupolar(matrix mat, int n){

    matrix matriz_mom_cuadrupolar(3, rows(3));

    for (int j = 1; j < 4; j++){
        for (int i = 1; i < 4; i++){
            matriz_mom_cuadrupolar[j-1][i] = 0;
            for (int k = 0; k < n; k++){

                if (i == j) {

                    matriz_mom_cuadrupolar[j-1][i-1] = matriz_mom_cuadrupolar[j-1][i-1] + mat[0][k]*(3*mat[i][k]*mat[j][k] - (mat[1][k]*mat[1][k]+mat[2][k]*mat[2][k]+mat[3][k]*mat[3][k]));
                    
                }else{

                    matriz_mom_cuadrupolar[j-1][i-1] = matriz_mom_cuadrupolar[j-1][i-1] + mat[0][k]*(3*mat[i][k]*mat[j][k]);

                }

            }
        }
    }

    return matriz_mom_cuadrupolar;
}


//Sección de Código Principal

int main(){

    system("clear");

    matrix mat_mom_cuadrupolar(3, rows(3));
    rows mom_dipolar;
    int i, j, numero_part;

    //Se pide el número de partículas con el que se va trabajar

    std::cout << "\nIntroduzca el número de partículas con el que se va a trabajar:\n" << std::endl;
    std::cin >> numero_part;

    std::vector<rows> all_vectors(4,rows(numero_part));

    //Se llama a la función correspondiente para poder designar las componentes de cada vector
    
    for(i=0; i<numero_part; i++){

        establecer_vectores(all_vectors, i);
        
    }

    //Se llama a la función correspondiente para calcular el momento monopolar

    std::cout << "\nEl momento monopolar del sistema será de: " << calc_mom_monopolar(all_vectors, numero_part) << std::endl << std::endl;

    //Se llama a la función correspondiente para calcular el momento dipolar
    
    mom_dipolar = calc_mom_dipolar(all_vectors, numero_part);

    std::cout << "El momento dipolar del sistema será: q x [(" << mom_dipolar[0] << ") x u_x + ("<< mom_dipolar[1] << ") x u_y + ("<< mom_dipolar[2] << ") x u_z]\n" << std::endl;
    
    //Se llama a la función correspondiente para calcular el momento cuadrupolar
    
    mat_mom_cuadrupolar = mom_cuadrupolar(all_vectors, numero_part);

    std::cout << "El momento cuadrupolar del sistema vendrá dado por el siguiente tensor:\n" << std::endl;

    printf("      %i %i %i\n  q x %i %i %i\n      %i %i %i\n", mat_mom_cuadrupolar[0][0],mat_mom_cuadrupolar[1][0],mat_mom_cuadrupolar[2][0],mat_mom_cuadrupolar[0][1],mat_mom_cuadrupolar[1][1],mat_mom_cuadrupolar[2][1],mat_mom_cuadrupolar[0][2],mat_mom_cuadrupolar[1][2],mat_mom_cuadrupolar[2][2]);

}
