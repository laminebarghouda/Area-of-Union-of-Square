#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cstring>
#include <bitset>
using namespace std;

class Rectangle{
    int x1;
    int y1;
    int x2;
    int y2;

public:
    Rectangle(int x1, int y1, int x2, int y2) {
        this->x1=x1;
        this->y1=y1;
        this->x2=x2;
        this->y2=y2;
    }

    int getX1() {
        return this->x1;
    }

    int getY1() {
        return this->y1;
    }

    int getX2() {
        return this->x2;
    }

    int getY2() {
        return this->y2;
    }

    // les deux couples (X1,Y1) et (X2,Y2) répresentent les coordonées de deux points d'extrémités du carré
// Calcul de (X1,Y1) et (X2,Y2) à partir du coordonnées du centre et du longueur et hauteur du carré
    int calculX1(int cX,int longueur){
        return (cX - (longueur/2));
    }

    int calculY1(int cY,int hauteur){
        return (cY - (hauteur/2));
    }

    int calculX2(int cX,int longueur){
        return (cX + (longueur/2));
    }

    int calculY2(int cY,int hauteur){
        return (cY + (hauteur/2));
    }

    int calculAire(vector<Rectangle> rectsPositive,vector<Rectangle> rectsNegative){
        int aire=0;
        bitset<1000> cartesian_coordinates[1000];
        int x1,x2,y1,y2;
        int nbIter = rectsPositive.size();
        int i=0;
        while(nbIter--)
        {
            x1 = rectsPositive.at(i).getX1();
            y1 = rectsPositive.at(i).getY1();
            x2 = rectsPositive.at(i).getX2();
            y2 = rectsPositive.at(i).getY2();

            for(int x=x1;x<x2;++x)
                for(int y=y1;y<y2;++y)
                    cartesian_coordinates[x][y]=1;
            i++;
        }

        nbIter = rectsNegative.size();
        i=0;
        while(nbIter--)
        {
            x1 = rectsNegative.at(i).getX1();
            y1 = rectsNegative.at(i).getY1();
            x2 = rectsNegative.at(i).getX2();
            y2 = rectsNegative.at(i).getY2();

            for(int x=x1;x<x2;++x)
                for(int y=y1;y<y2;++y)
                    cartesian_coordinates[x][y]=0;
            i++;
        }


        for(int x=0;x<1000;++x) {
            for (int y = 0; y <1000;++y) {
                if (cartesian_coordinates[x][y] == 1) {
                    ++aire;
                }
            }
        }

        return aire;
    }

    int calculPerimetre(vector<Rectangle> rectsPositive,vector<Rectangle> rectsNegative){
        int perimetre=0;
        bitset<1000> cartesian_coordinates[1000];
        int x1,x2,y1,y2;
        int nbIter = rectsPositive.size();
        int i=0;
        while(nbIter--)
        {
            x1 = rectsPositive.at(i).getX1();
            y1 = rectsPositive.at(i).getY1();
            x2 = rectsPositive.at(i).getX2();
            y2 = rectsPositive.at(i).getY2();

            for(int x=x1;x<x2;++x)
                for(int y=y1;y<y2;++y)
                    cartesian_coordinates[x][y]=1;
            i++;
        }

        nbIter = rectsNegative.size();
        i=0;
        while(nbIter--)
        {
            x1 = rectsNegative.at(i).getX1();
            y1 = rectsNegative.at(i).getY1();
            x2 = rectsNegative.at(i).getX2();
            y2 = rectsNegative.at(i).getY2();

            for(int x=x1;x<x2;++x)
                for(int y=y1;y<y2;++y)
                    cartesian_coordinates[x][y]=0;
            i++;
        }
        for(int x=0;x<1000;++x) {
            for (int y = 0; y < 1000; ++y) {
                if(x==0){
                    if((y==0)&&(cartesian_coordinates[x][y] == 1)) {
                        perimetre += 4;
                    }
                    else if((y>0)&&(cartesian_coordinates[x][y] == 1)&&(cartesian_coordinates[x][y-1] == 1)){
                        perimetre+=2;
                    }
                    else if((x>0)&&(cartesian_coordinates[x][y] == 1)&&(cartesian_coordinates[x][y-1] == 0)){
                        perimetre+=4;
                    }
                }
                else {
                    if((y==0)&&(cartesian_coordinates[x][y] == 1)&&(cartesian_coordinates[x-1][y] == 1)) {
                        perimetre += 2;
                    }
                    else if((y==0)&&(cartesian_coordinates[x][y] == 1)&&(cartesian_coordinates[x-1][y] == 0)) {
                        perimetre += 4;
                    }
                    else if((y>0)&&(cartesian_coordinates[x][y] == 1)&&(cartesian_coordinates[x][y-1] == 1)&&(cartesian_coordinates[x-1][y] == 1)){
                        perimetre+=0;
                    }
                    else if((y>0)&&(cartesian_coordinates[x][y] == 1)&&(cartesian_coordinates[x][y-1] == 1)&&(cartesian_coordinates[x-1][y] == 0)){
                        perimetre+=2;
                    }
                    else if((y>0)&&(cartesian_coordinates[x][y] == 1)&&(cartesian_coordinates[x][y-1] == 0)&&(cartesian_coordinates[x-1][y] == 1)){
                        perimetre+=2;
                    }
                    else if((x>0)&&(cartesian_coordinates[x][y] == 1)&&(cartesian_coordinates[x][y-1] == 0)&&(cartesian_coordinates[x-1][y] == 0)){
                        perimetre+=4;
                    }
                }
            }
        }

        return  perimetre;
    }



    int main() {
        string fic;
        cout << "Entrer le nom du fichier ! " << endl;
        cin >> fic;
        vector<Rectangle> rectsPositive;
        vector<Rectangle> rectsNegative;
        ifstream file(fic, ios::in);
        if (! file) {
            cout << "Impossible d'ouvrir le fichier " << fic << endl;
            cout << "Fichier introuvable ! " << endl;
            exit(1);
        }

        string line;
        while (getline(file, line)) {
            char aux[line.length() + 1];
            char *tokens;
            strcpy(aux, line.c_str());
            tokens = strtok(aux, " ");
            while (tokens) {
                string type = tokens;
                tokens = strtok(NULL," ");
                int cX = stoi(tokens);
                tokens = strtok(NULL, " ");
                int cY = stoi(tokens);
                tokens = strtok(NULL, " ");
                int longueur = stoi(tokens);
                tokens = strtok(NULL, " ");
                int hauteur = stoi(tokens);
                tokens = strtok(NULL, " ");
                Rectangle r(calculX1(cX,longueur),calculY1(cY,hauteur),calculX2(cX,longueur),calculY2(cY,hauteur));
                if(type=="p")
                    rectsPositive.push_back(r);
                else
                    rectsNegative.push_back(r);
            }

        }
        cout<< "Aire : " << calculAire(rectsPositive,rectsNegative) << endl;
        cout<< "Perimetre : " << calculPerimetre(rectsPositive,rectsNegative) << endl;

        return 0;
    }
};

