#ifndef VIDEO_H
#define VIDEO_H

///
/// \file video.h
/// \brief widget d'affichage d'une video
/// \author Pierre Lespingal
///

#include <define.h>
#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

///
/// \class Video
/// \brief La classe Video
///
/// La classe propose un widget permettant d'afficher un flux video.
///
class Video : public QWidget
{
    Q_OBJECT
public:
    ///
    /// \brief Constructeur Video
    /// \param parent
    ///
    /// Constructeur de la classe Video.
    ///
    Video(QWidget *parent = 0);

    ///
    /// \brief Destructeur ~Video
    ///
    /// Destructeur de la classe Video.
    ///
    virtual ~Video();

    ///
    /// \brief Chargement d'une vidéo
    /// \param path : chemin vers la video à charger.
    ///
    /// Charge une video située à un chemin donné, pour un affichage ultérieur.
    ///
    ///  \return 0 si la video est trouvée et chargée, -1 sinon.
    double setVideo(const std::string path);

    ///
    /// \brief Affichage à l'écran d'une frame.
    ///
    /// Affiche la frame suivante de la vidéo.
    ///
    /// \return 0 si la frame est récuperée, -1 sinon, par exemple si la video est terminée.
    ///
    int nextFrame();

    ///
    /// \brief Conversion du type IplImage vers QImage.
    /// \param newImage : Une image au format IplImage.
    ///
    /// Les frames des vidéos étant capturées au format Ipl2Qimage, une conversion est necessaire pour l'affichage de l'image dans un widget.
    ///
    /// \return Image d'origine au format QImage.
    ///
    QImage Ipl2QImage(const IplImage *newImage);

    QImage Mat2QImage(cv::Mat const& src);

private:

    QGridLayout* m_layout; ///< Layout pour positionner le label.
    QLabel* m_label; ///< Label pour y poser les frames.
    CvCapture* m_capture; ///< capture du flux video.
    IplImage* m_image; ///< image pour récuperer les frames stocké dans m_capture une par une.
    cv::VideoCapture m_cap;
    cv::Mat m_im;




};

#endif // VIDEO_H
