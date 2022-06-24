//
//  main.cpp
//  testlecturefichier
//
//  Created by MacBook on 16/05/2022.
//

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "function.h"
#include <iterator>
#include <algorithm>
#include <ostream>
#include <iterator>
#include <unistd.h>
#include <getopt.h>
#include<typeinfo>


using namespace std;

vector<string> vec; // vecteur global contenant le résultat du split du contenu du fichier txt

vector<string> vecteta; //vecteur contenant les valeurs calculées de Theta

vector<string> vecEta; // vecteur contenant les valeurs calculées de Eta

vector<string> res; // vecteur contenant le résultat d'assignation du prototype.

vector<float> vecteta_trans; // vecteur contenant les valeurs de Theta converties en float

vector<float> vecEta_trans; // vecteur contenant les valeurs de Theta converties en float

vector <string> vec_sep; // vecteur contenant les donées récupérées par la fonction split sur le fichier d'intervalles
vector<string> posInfT;  // vecteur contenant toutes les bornes inférieures Theta
vector<string> posSupT;  // vecteur contenant toutes les bornes supérieures Theta
vector<string> posInfE;  // vecteur contenant toutes les bornes inférieures Eta
vector<string> posSupE;  //  vecteur contenant toutes les bornes supérieures Eta
vector <string> letter;  //  vecteur contenant les lettres encodant les différents clusters

vector<float> posInfT_trans;  // vecteur cotenant les valeurs de posInfT convertis en float
vector<float> posSupT_trans;  // vecteur cotenant les valeurs de posSupT convertis en float
vector<float> posInfE_trans;  // vecteur cotenant les valeurs de posInfE convertis en float
vector<float> posSupE_trans;  // vecteur contenant les valeurs de posSupE convertis en float

vector <string> res2;  // vecteur contenant le résultat de l'annotation à partir du fichier d'intervalle




        /* fonction lecture et traitement du fichier résultat contenant les valeur d'angles Theta et Eta */


void get_angle_values (string inputfile){
    
    ifstream fichier(inputfile);
            if(fichier)  // si l'ouverture a fonctionné
            {
                string contenu;  // déclaration d'une chaîne qui contiendra la ligne lue
                getline(fichier,contenu);
                while(getline(fichier, contenu)){ // on met dans "contenu" la ligne
                    
                    
                    vector<string> vec = split(contenu,'\t');
                    vecteta.push_back(vec[0]);
                    
                    vecEta.push_back(vec[1]);
                    
                    cout << " Valeur récupérée de Theta : " <<vec[0] << " // " ;
                    
                    cout << "Valeur récupérée de Eta correspondante : " << vec[1] << endl;
                    
                    
                    
                }
                fichier.close();
            }
            else cout << "Impossible d'ouvrir le fichier ";
                
}


        /*  Fonction lecture du fichier contenant la définition d'intervalles pour l'assignation  */


void get_intervals(string input_Interval_file){
    
    ifstream fichierInput (input_Interval_file);
    if(fichierInput){
        string intervalle;
        getline(fichierInput,intervalle);
        while(getline(fichierInput,intervalle)){
            
            vec_sep = split(intervalle,'*') ;
            
            
            posInfT.push_back(vec_sep[0]);
            posSupT.push_back(vec_sep[1]);
            posInfE.push_back(vec_sep[2]);
            posSupE.push_back(vec_sep[3]);
            letter.push_back(vec_sep[4]);
            
            
            
            
            
        }
        fichierInput.close();
    }
    else cout << "impossible d'ouvrir le fichier !";
    
}








int main(int argc,  char **argv )
{
    string Interval_file_directory;
    string angle_file_directory;
    int opt ;
    while ((opt=getopt(argc,argv,"f:r:"))!=EOF){
        switch(opt){
            case'f': Interval_file_directory=optarg;break;
            case'r':angle_file_directory=optarg;break;
        }
    }
    if(Interval_file_directory.empty() or angle_file_directory.empty()){cerr<<"Argument is missing ! To fix this add: -f Interval file directory and -r result file directory" <<endl ; return 1;}
    
    
    cout << "Voici les résultats des valeurs d'angles récupérées : " << endl ;
    
    
    get_angle_values(angle_file_directory); // appel de la fonction get_angle_values
    

        /*  Traitement du format du fichier pour éviter les erreurs de typage lors de la convertion stof  */
                
                for (int i =0; i<vecteta.size(); ++i){

                    int posmot1 = vecteta[i].find("  NA"); // chercher dans vecteta les valeurs NA
                    
                    if (posmot1==0)
                        {vecteta[i]="0";}  // posmot1==0 signifie que une valeur NA a été retrouvé celle ci est ensuite remplacée par un 0

                }
    
               // Application de la même procédure pour vecEta :
    
               for (int i = 0; i<vecEta.size();++i){
                    
                    int posmot2=vecEta[i].find("  NA");
                    
                    int posmot3=vecEta[i].find("   ");
                   
                    
                    
                        if (posmot2==0 or posmot3==0 )
                            {vecEta[i]="0";}  // Meme procédure que pour vecteta
                
               
               }
    
    
    
                
                
    /*     Convertion du vecteur de string en vecteur de float     */
                
                /*  Convertir les valeurs de TETA en float : */
                
                
                
                for (int i=0; i<vecteta.size();++i){
                    
                    vecteta_trans.push_back(stof(vecteta[i]));
                    
                    //cout<<vecteta_trans.at(i)<<";";
                }
                
                /*  Convertir les veleur du vecteur ETA en Float : */
                
                
                
                for (int i=0; i<vecEta.size();++i){
                 
                    
                    vecEta_trans.push_back(stof(vecEta[i]));
                    
                    //cout<<vecEta_trans.at(i)<<";";
                    
                }
                
                
                
                
                
                /*Après définition des vecteurs de valeurs de TETHA et de ETA , on définit les intervalle de couple ETA THETA = PROTOTYPE */
                
                
                for (int i=0; i<vecteta_trans.size();++i){
                    if (vecteta_trans[i]<=360 and vecteta_trans[i]>= 315 and vecEta_trans[i]<=202 and vecEta_trans[i]>=135){res.push_back("A");}
                        
                    if(vecteta_trans[i]<=247.5 and vecteta_trans[i]>= 191 and vecEta_trans[i]<=50 and vecEta_trans[i]>=0){res.push_back("B");}
                            
                    if(vecteta_trans[i]<=248 and vecteta_trans[i]>= 203 and vecEta_trans[i]<=135 and vecEta_trans[i]>=101.5){res.push_back("C");}
                            
                    if(vecteta_trans[i]<=292 and vecteta_trans[i]>= 247 and vecEta_trans[i]<=191.25 and vecEta_trans[i]>=146){res.push_back("D");}
                    
                    if(vecteta_trans[i]<=236 and vecteta_trans[i]>= 203 and vecEta_trans[i]<=328 and vecEta_trans[i]>=248){res.push_back("E");}
                        
                    if(vecteta_trans[i]<=192 and vecteta_trans[i]>= 101.5 and vecEta_trans[i]<=225 and vecEta_trans[i]>=150){
                       
                                res.push_back("F");}

                    else
                        res.push_back("-");  // Etat de stucturation sacondaire = pas de stucturation
                    
                    
                    }
                
                
               
        
           
         
    
    
    
    
    
    /*  Ouverture Fichier cluster etrécupération d'intervalles fournies dans un fichier txt  */
    
    
    get_intervals(Interval_file_directory); // Appel de la fonction get_intervals ouvrant le fichier cotenant les intevalles et traitement de celui-ci
        
        
    /*  Convertion des valeurs contenus dans les vecteur de string en Float  */
    
    
    cout << "Les valeurs de bornes Theta Inférieures :  " << endl;
    
        for (int i=0; i<posInfT.size();++i){
            posInfT_trans.push_back(stof(posInfT[i]));
            cout<<posInfT_trans.at(i)<<";"; // Affichage de toutes les valeurs des bornes Theta Inférieures
        }
    
    cout << " "<< endl;
    cout<<"Les valeurs de bornes Theta Supérieures :  "<< endl;
        
        for (int i=0; i<posSupT.size();++i){
            posSupT_trans.push_back(stof(posSupT[i]));
            cout<<posSupT_trans.at(i)<<";";  // Affichage de toutes les valeurs des bornes Theta Supérieures
        }
    
    cout << " "<< endl;
    cout<<"Les valeurs de bornes Eta Supérieures :  "<< endl;
    
        for(int i=0; i<posSupE.size();++i){
            posSupE_trans.push_back(stof(posSupE[i]));
            cout<<posSupE_trans.at(i)<<";";  // affichage de toutes les valeurs des borne Eta Supérieures
        }
    
    cout << " "<< endl;
    cout<<"Les valeurs de bornes Eta Inférieures :  "<< endl;
        
        for(int i=0; i<posInfE.size();++i){
        
            posInfE_trans.push_back(stof(posInfE[i]));
            cout<<posInfE_trans.at(i)<<";"; // affichage de toutes les valeurs des bornes Eta Inférieures
            }
        
        
        
        
        
        
        
        
    
    
    /*  Partie Comparaison et  Annotation  */
    
    cout<<" "<<endl;
    
    cout<<" Résultats d'annotation de la stucturation secondaire  : " << endl;
    
    
    
    for (int j=0; j<vecteta_trans.size();++j){
        bool assignation=false;
        
        for (int i=0; i<posInfT_trans.size();++i){
            
            if (vecEta_trans[j]>posInfE_trans[i] and vecEta_trans[j]<posSupE_trans[i] and vecteta_trans[j]>posInfT_trans[i] and vecteta_trans[j]<posSupT_trans[i]){
                assignation=true;
                res2.push_back(letter[i]);
                
            }
            
            cout<< "  posinf ::  " << posInfT_trans[i];
                
                
            
            
        }
        
        if(!assignation) {res2.push_back("-");};
        
        
        cout<< "  Valuer Theta j    " << vecteta_trans[j];
        cout << " Valeur Teta j " << vecEta_trans[j];
        cout<< "  res1 ::  " <<res[j] ;
        cout<<"  res2 ::  " << res2[j] << endl; // affichage de res1 et res2 pour tester si même résultat que le prototype
        
        

     }
    
    cout << "Voici la chaine d'états de stucturation en 1 D : " << endl ;
    
    for (int i =0; i< res2.size();++i){
        cout<<res2[i]<<"//"; // Affichage de la chaine d'alphabet structural
    }
   
        
    
    
    
    
    
    
}
    

    
    
        

        
    
        
    
    
    
    

        
    
    

        



