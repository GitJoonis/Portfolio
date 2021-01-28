/*
####################################################################
# TIE-02201 Ohjelmointi 2: Perusteet, K2019                        #
# TIE-02207 Programming 2: Basics, S2019                           #
#                                                                  #
# Project4: Snake: The Revengeance                                 #
# Program description: "While revenge is served cold and vengeance #
#                       is served hot revengeance is often seen    #
#                       served with Cajun with a side of onion     #
#                       rings and often dumplings in the Orient."  #
#                       - urbandictionary                          #
#                                                                  #
# File: main_window.hh                                             #
# Description: Declares a class implementing a UI for the game.    #
#                                                                  #
# Author: Joona Nousiainen, 267048, joona.nousiainen@tuni.fi       #
####################################################################
*/

#ifndef PRG2_SNAKE2_MAINWINDOW_HH
#define PRG2_SNAKE2_MAINWINDOW_HH

#include "ui_main_window.h"
#include <QGraphicsScene>
#include <QMainWindow>
#include <QTimer>
#include <random>
#include <list>

/* \class MainWindow
 * \brief Implements the main window through which the game is played.
 */
class MainWindow: public QMainWindow {
    Q_OBJECT

public:

    /* \brief Construct a MainWindow.
     *
     * \param[in] parent The parent widget of this MainWindow.
     */
    explicit MainWindow(QWidget* parent = nullptr);

    /* \brief Destruct a MainWindow.
     */
    ~MainWindow() override = default;

    /* \brief Change the Snake's bearing when certain keys get pressed.
     *
     * \param[in] event Contains data on pressed and released keys.
     */
    void keyPressEvent(QKeyEvent* event) override;


private slots:
    void update();

    /* \brief Start the game.
     */
    void on_playButton_clicked();

    /* \brief Move the Snake by a square and check for collisions.
     *
     * The game ends if a wall or the Snake itself gets in the way.
     * When a food gets eaten a point is gained and the Snake grows.
     */
    void moveSnake();

    void moveFood();

    void getDirection();

    QPoint isOffPlayfield(int x, int y);

    void on_rngSeed_editingFinished();

    void on_pauseButton_clicked();

    void gameOver();

    void clear();

private:

    /* \brief Make the play field visible and fit it into the view.
     *
     * Should be called every time the field's size changes.
     */
    void adjustSceneArea();

    Ui::MainWindow ui_;                 /**< Accesses the UI widgets. */
    QGraphicsEllipseItem* food_ = nullptr; /**< The food item in the scene. */
    QGraphicsRectItem* head_ = nullptr;
    QGraphicsScene scene_;              /**< Manages drawable objects. */
    QTimer timer_;                      /**< Triggers the Snake to move. */
    QTimer playtime_;
    std::default_random_engine rng_;    /**< Randomizes food locations. */
    int time_s = 0;
    int time_m = 0;
    int interval_ = 1000;
    int score_ = 0;
    int height_ = 0;
    int width_ = 0;
    int x_ = -1;
    int y_ = 0;
    int difficulty_ = 0;
    unsigned int size_ = 0;
    QChar direction_ = 'a';
    bool dead_ = 0;
    std::list<QGraphicsRectItem*> body_parts;
};  // class MainWindow


#endif  // PRG2_SNAKE2_MAINWINDOW_HH
