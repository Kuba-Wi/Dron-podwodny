#pragma once
#include "hexagon.hh"
#include "obiekt.hh"

/*!
 * \brief Modeluje pojęcie drona
 * Klasa opisuje drona złożonego z obiektu i dwóch graniastosłupów sześciokątnych, który może się poruszać
 * i obracać wokół własnej osi.
 */
class dron {
private:
    /*! \brief body drona */
    obiekt body;
    /*! \brief Prawa śruba drona */
    hexagon right_motor;
    /*! Lewa śruba drona */
    hexagon left_motor;
    /*! \brief Łączny kąt rotationu obiektu */
    double all_angle;
    /*! \brief przesunięcie obiektu względem wspolrzednych lokalnych */
    TVector<double, size_of_TVector> translation;

    /*!
     * \brief Wylicza vector translacji.
     * Metoda wylicza vector translacji na podstawie zadanych parametrów
     * \param[in] vec - vector który będzie zapisany
     * \param[in] rising_angle - kąt o jaki ma być odchylony vector
     * \param[in] distance - długość vectora
     */
    void count_translation(TVector<double, size_of_TVector>& vec, double rising_angle, double distance) const;
    /*!
     * \brief Wylicza macierz rotationu.
     * Metoda wylicza macierz rotationu wokół osi OZ na podstawie zadanych parametrów.
     * \param[in] rotation - wypełniana macierz rotationu
     * \param[in] rotation_angle - kąt dla jakiego ma zostać wyliczona macierz
     */
    void count_rotation_angle(TMatrix<double, size_of_TVector>& rotation, double rotation_angle) const;

    /*!
     * \brief Powoduje ruch sruby lewej
     * Metoda powoduje ruch lewej śruby o vector przesunięcie i obrót o zadaną macierz.
     * \param[in] rotation - macierz z zapisanym rotationem
     */
    void left_motor_move(const TMatrix<double, size_of_TVector>& rotation);
    /*!
     * \brief Powoduje ruch sruby prawej
     * Metoda powoduje ruch prawej śruby o vector przesunięcie i obrót o zadaną macierz.
     * \param[in] rotation - macierz z zapisanym rotationem
     */
    void right_motor_move(const TMatrix<double, size_of_TVector>& rotation);
    /*!
     * \brief Powoduje ruch bodyu
     * Metoda powoduje ruch bodyu o vector przesunięcie i obrót o zadaną macierz.
     * \param[in] rotation - macierz z zapisanym rotationem
     */
    void body_move(const TMatrix<double, size_of_TVector>& rotation);

public:
    /*!
     * \brief Konstruktor
     * Zeruje vector przesunięcie i all_angle
     */
    dron();
    /*!
     * \brief Inicjaizuje drona
     * Metoda initializee body i śruby oraz przesuwa śruby względem bodyu.
     */
    void initialize_drone();
    /*!
     * \brief Dodaje pliki bodyu
     * Metoda dodaje plik lokalny i globalny, które zawierają punkty tworzące body.
     * \param[in] local_name - plik ze współrzędnymi lokalnymi
     * \param[in] global_name - plik ze współrzędnymi globalnymi
     */
    void add_files_body(const std::string& local_name, const std::string& global_name);
    /*!
     * \brief Dodaje pliki lewej śruby
     * Metoda dodaje plik lokalny i globalny, które zawierają punkty tworzące lewą śrubę.
     * \param[in] local_name - plik ze współrzędnymi lokalnymi
     * \param[in] global_name - plik ze współrzędnymi globalnymi
     */
    void add_files_left_motor(const std::string& local_name, const std::string& global_name);
    /*!
     * \brief Dodaje pliki prawej śruby
     * Metoda dodaje plik lokalny i globalny, które zawierają punkty tworzące prawą śrubę.
     * \param[in] local_name - plik ze współrzędnymi lokalnymi
     * \param[in] global_name - plik ze współrzędnymi globalnymi
     */
    void add_files_right_motor(const std::string& local_name, const std::string& global_name);

    /*!
     * \brief Powoduje ruch drona po prostej
     * Metoda powoduje przesunięcie drona o zadany kąt i zadaną odległość
     * \param[in] rising_angle - kąt o jaki ma wznieść się dron
     * \param[in] distance - odległość na jaką ma przesunąć się dron
     */
    void move_ahead(double rising_angle, double distance);
    /*!
     * \brief Powoduje obrót drona
     * Metoda powoduje obrót drona o zadany kąt rotationu
     * \param[in] rotation_angle - kąt o jaki ma obrócić się dron w osi OZ
     */
    void rotation(double rotation_angle);

    /*!
     * \brief Zwraca położenie drona
     * Metoda zwraca aktualne położenie drona
     * \return vector z zapisanymi współrzędnymi kartezjańskimi drona
     */
    TVector<double, size_of_TVector> return_location() const;
    /*!
     * \brief Zwraca wymiary drona
     * Metoda zwraca odległości środka drona od jego ścian.
     * \return vector z zapisanymi długościami
     */
    TVector<double, size_of_TVector> return_lenghts() const;
};
