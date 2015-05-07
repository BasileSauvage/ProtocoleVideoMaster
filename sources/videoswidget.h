#ifndef VIDEOSWIDGET_H
#define VIDEOSWIDGET_H

///
/// \file videowidget.h
/// \brief Classe de disposition des vidéos
///
/// \author Pierre Lespingal
///

#include <QWidget>
#include <vector>
#include <QGridLayout>
#include <QDateTime>
#include <QVector>
#include "video.h"
#include <QMessageBox>
#include <QTimer>
#include <fstream>

///
/// \class VideosWidget
/// \brief La classe VideosWidget
///
/// Classe d'affichage et de gestion de trois flux vidéos en parallèle, ainsi que de gestion de flux d'entrée/sortie des séquences et des résultats
///

class VideosWidget : public QWidget
{
    Q_OBJECT
public:

    ///
    /// \brief Constructeur VideosWidget
    ///
    /// Constructeur de la classe VideosWidget
    ///
    /// \param parent : widget parent
    /// \param h : hauteur du widget
    /// \param w : largeur du widget
    ///
    VideosWidget(QWidget *parent = 0, int w = 800, int h = 600);

    ///
    /// \brief Destructeur VideosWidget
    ///
    /// Destructeur de la classe VideosWidget
    ///
    virtual ~VideosWidget();

    ///
    /// \brief loadSequence
    ///
    /// Charge une séquence de test
    ///
    void loadSequence(std::string path);

    ///
    /// \brief exportation des résultats du test
    /// \param choices : tableau des choix de l'utilisateur
    /// \param respondTime : tableau des temps de réponse associés
    ///
    /// Exporte les résultats du test, avec les temps de réponse.
    ///
    bool exportResult(QVector<int> choices, QVector<int> respondTime);

    ///
    /// \brief Organisation du layout vidéos
    /// \param resolution : Les resolutions respectives des trois videos
    ///
    /// Permet de modifier le layout pour qu'il s'adapte au format des videos (hauteur, placement vis à vis de chacune)
    ///

    void organizeLayout(double resolution);

    ///
    /// \brief stop
    ///
    /// Met en pause les vidéos
    ///
    void stop();

    ///
    /// \brief play
    ///
    /// Met en route les vidéos
    ///
    void play();

    ///
    /// \brief Chargement des vidéos suivantes
    ///
    /// Charge les trois vidéos suivantes de la sequence
    ///
    bool loadNext();

    ///
    /// \brief Met en avant une vidéo
    /// \param i : numero de la video
    ///
    /// encadre en vert la vidéo indiquée
    ///
    void setFocus(int i);

    ///
    /// \brief redimensionnement du layout
    /// \param w : une largeur
    /// \param h : une hauteur
    ///
    /// Redimensionne le layout, notamment entre la phase d'entraînement et le test réel.
    ///
    void resizeLayout(int w, int h);

    ///
    /// \brief Cache les vidéos
    ///
    /// Les trois vidéos sont cachées, pour assurer une transition correct entre les différentes phase du test.
    ///
    void cleanVideos();

    ///
    /// \brief Affiche les vidéos
    ///
    /// Affiche les vidéos à l'écran.
    ///
    void showVideos();
    
public slots:

    ///
    /// \brief Affiche les frames suivantes des trois videos
    ///
    /// Appel la méthode d'affichage de frame suivante des trois vidéos, pour une lecture synchronisée.
    ///
    void runVideos();

    ///
    /// \brief recharge les vidéos
    ///
    /// recharge les vidéos de la séquence de test, i.e. remet au début la lecture des vidéos.
    ///
    void start();

private:

    int m_height; ///< hauteur du layout
    int m_width; ///< largeur du layout

    int m_cmpSequence; ///< compteur de comparaison effectué par l'utilisateur

    std::string m_sequencePath; ///< Le nom du fichier contenant la sequence
    QVector<std::string> m_sequence; ///< La sequence de test
    QVector<Video*> m_videos; ///< les trois videos à afficher

    QLabel* m_labelRef; ///< texte "référence" pour indiquer la référence

    QGridLayout* m_videoLayout; ///< Layout des vidéos

    QTimer* m_timer; ///< timer de synchronisation des videos
    //QTimer* m_boucleTimer; ///< timer de boucle des videos
    int m_cmpFrames;


};

#endif // VIDEOSWIDGET_H
