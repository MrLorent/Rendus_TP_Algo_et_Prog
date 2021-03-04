#include <iostream>

using namespace std;

// LISTES CHAINEES
struct Noeud{
    int donnee;
    Noeud* suivant;
};

struct Liste{
    Noeud* premier;
    int nbNoeud;
    Noeud* dernier;
};

void initialise(Liste* liste)
{
    liste->premier = NULL;
    liste->dernier = NULL;
    liste->nbNoeud = 0;
}

bool est_vide(const Liste* liste)
{
    if(liste->nbNoeud == 0){
        return true;
    }else{
        return false;
    }
}

void ajoute(Liste* liste, int valeur)
{
    //On créer le nouveau noeud et on l'initialise
    Noeud * nvNoeud = new Noeud;
    nvNoeud->donnee = valeur;
    nvNoeud->suivant = NULL;

    //On parcours la liste pour trouver le dernier noeud
    if(liste->premier == NULL){
        liste->premier = nvNoeud;
        liste->dernier = nvNoeud;
    }else{
        liste->dernier->suivant = nvNoeud;
        liste->dernier = nvNoeud;
    }

    liste->nbNoeud = liste->nbNoeud + 1;
}

void affiche(const Liste* liste)
{
    cout << endl;
    cout << "AFFICHAGE D'UNE LISTE:" << endl;
    cout << endl;

    int count = 1;
    Noeud * tmp = liste->premier;

    while(tmp != NULL){
        cout << "Valeur n°" << count << " : " << tmp->donnee << " ; " << endl;
        tmp = tmp->suivant;
        count++;
    }
    cout << endl;
}

int recupere(const Liste* liste, int n)
{
    if(n>=0 && n<=liste->nbNoeud){
        Noeud * tmp = liste->premier;

        for(int i=0; i<n-1; i++){
            tmp = tmp->suivant;
        }

        return tmp->donnee;
    }else{
        return -1;
    }
}

int cherche(const Liste* liste, int valeur)
{
    int count = 0, index = -1;
    bool trouve = false;

    Noeud * tmp = liste->premier;

    while(!trouve && tmp != NULL){
        if(tmp->donnee == valeur){
            index = count;
            trouve = true;
        }
        tmp = tmp->suivant;
        count++;
    }

    return index;
}

void stocke(Liste* liste, int n, int valeur)
{
    if(n>=0 && n<=liste->nbNoeud){
        Noeud * tmp = liste->premier;

        for(int i=0; i<n-1; i++){
            tmp = tmp->suivant;
        }

        tmp->donnee = valeur;
    }else{
        cout << "Erreur: le rang saisi n'existe pas dans la liste" << endl;
    }
}

// TABLEAUX DYNAMIQUES
struct DynaTableau{
    int* donnees;
    int nbDonnees;
    int capacite;
};

void ajoute(DynaTableau* tableau, int valeur)
{
    if(tableau->nbDonnees == tableau->capacite){
        int * tmp = new int[tableau->capacite + 1];

        for(int i=0; i<tableau->capacite; i++){
            tmp[i] = tableau->donnees[i];
        }
        tmp[tableau->capacite] = valeur;

        free(tableau->donnees);

        tableau->donnees = tmp;
        tableau->capacite = tableau->capacite + 1;
    }else{
        tableau->donnees[tableau->nbDonnees] = valeur;
    }
    tableau->nbDonnees = tableau->nbDonnees + 1;
}


void initialise(DynaTableau* tableau, int capacite)
{
    tableau->capacite = capacite;
    tableau->donnees = new int[capacite];
    tableau->nbDonnees = 0;
}

bool est_vide(const DynaTableau* tableau)
{
    if(tableau->nbDonnees == 0){
        return true;
    }else{
        return false;
    }
}

void affiche(const DynaTableau* tableau)
{
    cout << endl;
    cout << "AFFICHAGE D'UN TABLEAU DYNAMIQUE :" << endl;
    cout << endl;
    for(int i=0; i<tableau->nbDonnees; i++){
        cout << "Valeur n°" << i << " : " << tableau->donnees[i] << " ;" << endl;
    }
    cout << endl;
}

int recupere(const DynaTableau* tableau, int n)
{
    if(n>=0 && n <tableau->nbDonnees){
        return tableau->donnees[n];
    }else{
        cout << "Erreur: le rang demandé n'existe pas dans le tableau" << endl;
        return -1;
    }
}

int cherche(const DynaTableau* tableau, int valeur)
{
    int count = 0, index = -1;
    bool trouve = false;

    while(!trouve && count < tableau->nbDonnees){
        if(tableau->donnees[count] == valeur){
            index = count;
            trouve = true;
        }
        count++;
    }

    return index;
}

void stocke(DynaTableau* tableau, int n, int valeur)
{
    if(n>=0 && n <tableau->nbDonnees){
         tableau->donnees[n] = valeur;
    }else{
        cout << "Erreur: le rang demandé n'existe pas dans le tableau" << endl;
    }
}

//void pousse_file(DynaTableau* liste, int valeur)
void pousse_file(Liste* liste, int valeur)
{
    ajoute(liste, valeur);
}

//int retire_file(Liste* liste)
int retire_file(Liste* liste)
{
    Noeud * tmp = liste->premier;
    int valeur = tmp->donnee;

    liste->premier = liste->premier->suivant;
    liste->nbNoeud = liste->nbNoeud - 1;
    free(tmp);

    return valeur;
}

//void pousse_pile(DynaTableau* liste, int valeur)
void pousse_pile(Liste* liste, int valeur)
{
    Noeud * nvNoeud = new Noeud;

    nvNoeud->donnee = valeur;
    nvNoeud->suivant = liste->premier;
    liste->premier = nvNoeud;
    liste->nbNoeud = liste->nbNoeud + 1;
}

//int retire_pile(DynaTableau* liste)
int retire_pile(Liste* liste)
{
    Noeud * tmp = liste->premier;
    int valeur = tmp->donnee;

    liste->premier = liste->premier->suivant;
    liste->nbNoeud = liste->nbNoeud - 1;
    free(tmp);

    return valeur;
}


int main()
{
    Liste liste;
    initialise(&liste);
    DynaTableau tableau;
    initialise(&tableau, 5);

    if (!est_vide(&liste))
    {
        std::cout << "Oups y a une anguille dans ma liste" << std::endl;
    }

    if (!est_vide(&tableau))
    {
        std::cout << "Oups y a une anguille dans mon tableau" << std::endl;
    }

    for (int i=1; i<=7; i++) {
        ajoute(&liste, i*7);
        ajoute(&tableau, i*5);
    }

    if (est_vide(&liste))
    {
        std::cout << "Oups y a une anguille dans ma liste" << std::endl;
    }

    if (est_vide(&tableau))
    {
        std::cout << "Oups y a une anguille dans mon tableau" << std::endl;
    }

    std::cout << "Elements initiaux:" << std::endl;
    affiche(&liste);
    affiche(&tableau);
    std::cout << std::endl;

    std::cout << "5e valeur de la liste " << recupere(&liste, 4) << std::endl;
    std::cout << "5e valeur du tableau " << recupere(&tableau, 4) << std::endl;

    std::cout << "21 se trouve dans la liste à " << cherche(&liste, 21) << std::endl;
    std::cout << "15 se trouve dans la liste à " << cherche(&tableau, 15) << std::endl;

    stocke(&liste, 4, 7);
    stocke(&tableau, 4, 7);

    std::cout << "Elements après stockage de 7:" << std::endl;
    affiche(&liste);
    affiche(&tableau);
    std::cout << std::endl;

    Liste pile; // DynaTableau pile;
    Liste file; // DynaTableau file;

    initialise(&pile);
    initialise(&file);

    for (int i=1; i<=7; i++) {
        pousse_file(&file, i);
        pousse_pile(&pile, i);
    }

    int compteur = 10;
    while(!est_vide(&pile) && compteur > 0)
    {
        std::cout << retire_pile(&pile) << std::endl;
        compteur--;
    }

    if (compteur == 0)
    {
        std::cout << "Ah y a un soucis là..." << std::endl;
    }

    compteur = 10;
    while(!est_vide(&file) && compteur > 0)
    {
        std::cout << retire_file(&file) << std::endl;
        compteur--;
    }

    if (compteur == 0)
    {
        std::cout << "Ah y a un soucis là..." << std::endl;
    }

    return 0;
}
