///
/// \file main.cpp
/// \brief Interface de test subjectif
/// \author Pierre Lespingal
/// \date 10 Juin 2014
///
/// Propose un protocole de test utilisateur pour l'évaluation de la qualité d'objet 3D
///


#include <QApplication>
#include <QTextCodec>
#include "menu.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //Affichage des accents et autres caractères spéciaux (seulement sous système Linux)
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    //Creation et affichage de la fenêtre de base
    Menu *fenetre = new Menu;
    fenetre->show();


    return a.exec();
}
