#pragma once
#include "obiekt.hh"
#include "szesciokat.hh"

/*!
 * \brief Modeluje pojęcie drona
 * Klasa opisuje drona złożonego z obiektu i dwóch graniastosłupów sześciokątnych, który może się poruszać
 * i obracać wokół własnej osi.
 */
class dron {
private:
    /*! \brief Korpus drona */
    obiekt korpus;
    /*! \brief Prawa śruba drona */
    szesciokat sruba_prawa;
    /*! Lewa śruba drona */
    szesciokat sruba_lewa;
    /*! \brief Łączny kąt obrotu obiektu */
    double laczny_kat_obrotu;
    /*! \brief przesunięcie obiektu względem wspolrzednych lokalnych */
    SWektor<double, 3> przesuniecie;

    /*!
     * \brief Wylicza wektor translacji.
     * Metoda wylicza wektor translacji na podstawie zadanych parametrów
     * \param[in] wek - wektor który będzie zapisany
     * \param[in] kat_wznoszenia - kąt o jaki ma być odchylony wektor
     * \param[in] odleglosc - długość wektora
     */
    void wylicz_translacje(SWektor<double, 3>& wek, double kat_wznoszenia, double odleglosc) const;
    /*!
     * \brief Wylicza macierz obrotu.
     * Metoda wylicza macierz obrotu wokół osi OZ na podstawie zadanych parametrów.
     * \param[in] obrot - wypełniana macierz obrotu
     * \param[in] kat_obrotu - kąt dla jakiego ma zostać wyliczona macierz
     */
    void wylicz_macierz_obrotu(SMacierz<double, 3>& obrot, double kat_obrotu) const;

    /*!
     * \brief Powoduje ruch sruby lewej
     * Metoda powoduje ruch lewej śruby o wektor przesunięcie i obrót o zadaną macierz.
     * \param[in] obrot - macierz z zapisanym obrotem
     */
    void sruba_lewa_ruch(const SMacierz<double, 3>& obrot);
    /*!
     * \brief Powoduje ruch sruby prawej
     * Metoda powoduje ruch prawej śruby o wektor przesunięcie i obrót o zadaną macierz.
     * \param[in] obrot - macierz z zapisanym obrotem
     */
    void sruba_prawa_ruch(const SMacierz<double, 3>& obrot);
    /*!
     * \brief Powoduje ruch korpusu
     * Metoda powoduje ruch korpusu o wektor przesunięcie i obrót o zadaną macierz.
     * \param[in] obrot - macierz z zapisanym obrotem
     */
    void korpus_ruch(const SMacierz<double, 3>& obrot);

public:
    /*!
     * \brief Konstruktor
     * Zeruje wektor przesunięcie i laczny_kat_obrotu
     */
    dron();
    /*!
     * \brief Inicjaizuje drona
     * Metoda inicjalizuje korpus i śruby oraz przesuwa śruby względem korpusu.
     */
    void inicjalizuj_drona();
    /*!
     * \brief Dodaje pliki korpusu
     * Metoda dodaje plik lokalny i globalny, które zawierają punkty tworzące korpus.
     * \param[in] nazwa_lok - plik ze współrzędnymi lokalnymi
     * \param[in] nazwa_glob - plik ze współrzędnymi globalnymi
     */
    void dodaj_pliki_korpus(const std::string& nazwa_lok, const std::string& nazwa_glob);
    /*!
     * \brief Dodaje pliki lewej śruby
     * Metoda dodaje plik lokalny i globalny, które zawierają punkty tworzące lewą śrubę.
     * \param[in] nazwa_lok - plik ze współrzędnymi lokalnymi
     * \param[in] nazwa_glob - plik ze współrzędnymi globalnymi
     */
    void dodaj_pliki_sruby_lewej(const std::string& nazwa_lok, const std::string& nazwa_glob);
    /*!
     * \brief Dodaje pliki prawej śruby
     * Metoda dodaje plik lokalny i globalny, które zawierają punkty tworzące prawą śrubę.
     * \param[in] nazwa_lok - plik ze współrzędnymi lokalnymi
     * \param[in] nazwa_glob - plik ze współrzędnymi globalnymi
     */
    void dodaj_pliki_sruby_prawej(const std::string& nazwa_lok, const std::string& nazwa_glob);

    /*!
     * \brief Powoduje ruch drona po prostej
     * Metoda powoduje przesunięcie drona o zadany kąt i zadaną odległość
     * \param[in] kat_wznoszenia - kąt o jaki ma wznieść się dron
     * \param[in] odleglosc - odległość na jaką ma przesunąć się dron
     */
    void ruch_na_wprost(double kat_wznoszenia, double odleglosc);
    /*!
     * \brief Powoduje obrót drona
     * Metoda powoduje obrót drona o zadany kąt obrotu
     * \param[in] kat_obrotu - kąt o jaki ma obrócić się dron w osi OZ
     */
    void obrot(double kat_obrotu);

    /*!
     * \brief Zwraca położenie drona
     * Metoda zwraca aktualne położenie drona
     * \return wektor z zapisanymi współrzędnymi kartezjańskimi drona
     */
    SWektor<double, 3> zwroc_polozenie() const;
    /*!
     * \brief Zwraca wymiary drona
     * Metoda zwraca odległości środka drona od jego ścian.
     * \return wektor z zapisanymi długościami
     */
    SWektor<double, 3> zwroc_dlugosci() const;
};
