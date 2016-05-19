#include "videoswidget.h"
#include <QDir>

///
/// \file videowidget.cpp
/// \brief méthodes de la classe VideosWidget
///
/// Gestion de fichier d'entrée/sortie, gestion des flux vidéos en parallèles
/// \author Pierre Lespingal
///


using namespace std;

VideosWidget::VideosWidget(QWidget *parent, int w, int h) :
    QWidget(parent)
{
    //On régle la résolution
    m_height = h;
    m_width = w;
    setFixedSize(m_width, m_height);

    m_videoLayout = new QGridLayout(this);
    m_videoLayout->setVerticalSpacing(LAYOUT_V_SPACE);
    m_videoLayout->setHorizontalSpacing(LAYOUT_SPACE);
    setLayout(m_videoLayout);

    for(int i = 0;i<3;i++)
    {
        Video* video = new Video;
        m_videos.append(video);

    }

    m_labelRef = new QLabel("<html><strong>Référence<strong></html>", this);
    m_labelRef->setFixedHeight(15);
    m_labelRef->setStyleSheet("color:white;");

    //Lancement du timer, toute les 30 ms affichage des frames suivantes
    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(runVideos()));

    m_cmpFrames = 0;

    //Lancement du timer de boucle
    //m_boucleTimer = new QTimer(this);
    //connect(m_boucleTimer, SIGNAL(timeout()), this, SLOT(start()));


}

VideosWidget::~VideosWidget()
{
    if(m_timer)
    {
    m_timer->stop();
    delete(m_timer);
    }
    delete(m_labelRef);

    for(int i = 0;i< m_videos.size();i++)
    {
        if(m_videos[i])
        delete(m_videos[i]);
    }
    m_videos.clear();
    m_sequence.clear();

    delete(m_videoLayout);
}

void VideosWidget::loadSequence(string path)
{
    //Nettoyage des sequences
    m_sequence.clear();
    //QMessageBox::information(0, "error", QDir::currentPath());
    //Recuperation des noms de videos à partir du fichier sequence
    ifstream sequence_flux(path.c_str());
    if(sequence_flux)
    {
    string line;
    while(getline(sequence_flux, line))
    {
        m_sequence.append(line);
    }
    //Initialisation du compteur de tests
    m_cmpSequence = -1;
    }
    else
    {
    QMessageBox::information(0, "Error", "impossible de lire le fichier");
    exit(0);
    }
    //sauvegarde du nom du fichier de sequence
    m_sequencePath = path;


}

bool VideosWidget::exportResult(QVector<int> choices, QVector<int> respondTime)
{
    string path = "./resultats/resultat_" + QDateTime::currentDateTime().toString().toStdString();
	ofstream result_flux(path.c_str());

	if(!result_flux)//testons si le fichier est bien ouvert
    {
		return false;
    }
    else
    {
        result_flux << m_sequencePath.c_str() << endl;
	for(int i = 0;i<choices.size();i++)//Ecriture de la sequence, suivit du choix et du temps de réponse
    {
        result_flux << m_sequence[3*i].c_str() << endl << m_sequence[3*i + 1].c_str() << endl << m_sequence[3*i + 2] << endl;
        result_flux << choices[i] << " in " << respondTime[i] << " ms " << endl;

    }
    return true;
    }

}

void VideosWidget::stop()//Les vidéos sont arretées
{
    m_timer->stop();
}

void VideosWidget::play()//Les videos sont relancé
{
    m_timer->start(40);
}

void VideosWidget::start()
{
    for(int i = 0;i<3;i++)
    {
        m_videos[i]->setVideo(m_sequence[3*m_cmpSequence + i]);
    }
    m_cmpFrames = 0;
}

bool VideosWidget::loadNext()
{
    m_videos[1]->setStyleSheet("border: none");
    m_videos[2]->setStyleSheet("border: none");
    vector<double> resolution(3);
    m_cmpSequence++;
    m_cmpFrames = 0;
    if(m_cmpSequence <= NB_TEST && 3*m_cmpSequence < m_sequence.size())// si le test n'est pas finit
    {
    for(int i = 0;i<3;i++)
    resolution[i] = m_videos[i]->setVideo(m_sequence[3*m_cmpSequence + i]);

    if(resolution[0] == -1)
    {
        QMessageBox::information(0, "error", "Erreur chargement des vidéos, vérifiez la presence des videos");
        exit(0);
    }
    else
    {
        organizeLayout(resolution[0]);
        return true;
    }

    }
    else
        return false;
}

void VideosWidget::runVideos()
{
    //Affichage des frames suivantes de chaque videos
    if(m_cmpFrames < 360)
    {
    for(int i = 0;i<m_videos.size();i++)
    {
        m_videos[i]->nextFrame();
    }
    m_cmpFrames++;
    }
    else
    {
        start();
        m_cmpFrames = 0;
    }

}

void VideosWidget::setFocus(int i)
{
    m_videos[i]->setStyleSheet("border: 4px solid green");
}


void VideosWidget::organizeLayout(double resolution)
{
    m_videoLayout->removeWidget(m_labelRef);
        for(int i = 0; i < m_videos.size();i++)
        {
            m_videoLayout->removeWidget(m_videos[i]);
        }
        //Si en plaçant les vidéos toutes côte à côte, en prenant tout la largeur de l'espace, il reste assez de place en hauteur pour en disposer deux l'une au dessus de l'autre, on s'oriente vers un placement en pyramide.
            if(((m_width - 4*LAYOUT_SPACE)/3)*resolution <= ((m_height - 3*LAYOUT_V_SPACE - LAYOUT_LABEL)/2) )
            {
                //Il faut encore s'assurer que les vidéos ne se chevauchent pas
                //Si en plaçant deux vidéos côte à côte en occupant toute la largeur disponnible, on peut toujours en placer aussi deux en hauteur, la taille final de chaque vidéo est determiné par la largeur de l'espace vidéo.
               // if(((m_width - 3*LAYOUT_SPACE)/2)*resolution <= (m_height - 3*LAYOUT_V_SPACE)/2)
                    for(int i = 0; i < m_videos.size();i++)
                        m_videos[i]->setFixedSize((m_width - 3*LAYOUT_SPACE)/2 ,((m_height - 3*LAYOUT_V_SPACE - LAYOUT_LABEL )/2));
               /* else//Sinon, par la hauteur.
                    for(int i = 0; i < m_videos.size();i++)
                        m_videos[i]->setFixedSize(((m_height - 3*LAYOUT_V_SPACE)/2)/resolution ,(m_height - 3*LAYOUT_V_SPACE)/2);*/

                m_videoLayout->addWidget(m_videos[0], 0, 1, 1, 2, Qt::AlignHCenter | Qt::AlignBottom);
                m_videoLayout->addWidget(m_labelRef, 1, 1, 1, 2, Qt::AlignHCenter);

                for(int i = 1; i < m_videos.size();i++)
                    m_videoLayout->addWidget(m_videos[i], 2, 2*(i-1), 1, 2, Qt::AlignHCenter | Qt::AlignTop);
            }
            else//Sinon on opte pour un placement côte à côte.
            {
                //On determine de même la taille final des vidéos en évitant les chevauchements.
               // if(((m_width - 4*LAYOUT_SPACE)/3)*resolution <= m_height - 2*LAYOUT_SPACE)
                    for(int i = 0; i < m_videos.size();i++)
                        m_videos[i]->setFixedSize((m_width - 4*LAYOUT_SPACE)/3 ,(m_height - 2*LAYOUT_V_SPACE - LAYOUT_LABEL) );
               /* else
                    for(int i = 0; i < m_videos.size();i++)
                        m_videos[i]->setFixedSize((m_height - 2*LAYOUT_V_SPACE)/resolution, m_height - 2*LAYOUT_V_SPACE);*/

                    m_videoLayout->addWidget(m_videos[0], 0, 4, 1, 4, Qt::AlignHCenter | Qt::AlignBottom);
                    m_videoLayout->addWidget(m_labelRef, 1, 4, 1, 4, Qt::AlignHCenter);

                    for(int i = 1; i < m_videos.size();i++)
                        m_videoLayout->addWidget(m_videos[i], 0, 8*(i-1), 1, 4, Qt::AlignHCenter | Qt::AlignBottom);
            }
}

void VideosWidget::resizeLayout(int w, int h)
{
    m_width = w;
    m_height = h;
    setFixedSize(m_width, m_height);
}

void VideosWidget::cleanVideos()
{
    m_labelRef->hide();
    for(int i = 0;i<3;i++)
    {
        m_videos[i]->hide();
    }
}

void VideosWidget::showVideos()
{
    m_labelRef->show();
    for(int i =0;i<3;i++)
    {
        m_videos[i]->show();
    }
}
