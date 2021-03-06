#pragma once

#include <list>
#include <memory>
#include "bar.hh"
#include "cuboid.hh"
#include "dron.hh"
#include "lacze_do_gnuplota.hh"
#include "rectangle.hh"

/*!
 * \brief Modeluje pojęcie sceny
 * Klasa opisuje scenę na której będzie poruszać się obiekt
 * oraz będą przechowywane surface wody i surface dna.
 */
class stage {
private:
    /*! \brief Opisuje powierzchnię dna */
    surface bottom;
    /*! \brief Opisuje powierzchnię wody */
    surface water;
    /*! \brief Opisuje obiekt dron */
    dron dron_stage;
    /*! \brief Łącze z programem gnuplot */
    Link& link;

    /*! \brief lista z wskaźnikami na przeszkody */
    std::list<std::shared_ptr<obiekt>> obstacles_list;

    /*! \brief Rysuje wszystkie powierzchnie i obiekty na scenie */
    void draw() { link.Rysuj(); }
    /*!
     * \brief Dodaje plik do łącza do gnuplota
     * \param[in] file_name - nazwa dołączanego pliku
     */
    void link_add_file(const std::string& file_name);

    /*!
     * \brief Dodaje przeszkodę na scenie
     * Metoda dodaje na scenę przeszkodę zapisaną w zadanych plikach
     * \param[in] local_name - nazwa pliku z danymi lokalnymi
     * \param[in] global_name - nazwa pliku z danymi globalnymi
     */
    void add_obstacle(const std::string& local_name, const std::string& global_name);

    /*!
     * \brief Zwraca informację o kolizji
     * Sprawdza czy jest colision z jakąś przeszkodą
     * \retval true - gdy będzie colision
     * \retval false - gdy nie będzie colision
     */
    bool colision() const;
    /*!
     * \brief Zwraca informację o kolizji z dnem
     * Metoda sprawdza czy nie ma kolizji z dnem
     * \retval true - gdy jest colision
     * \retval false - gdy nie ma kolizji
     */
    bool colision_bottom() const;

    /*!
     * \brief Zwraca informację o emergence
     * Sprawdza czy obiekt jest wynurzony
     * \retval true - gdy jest emergence
     * \retval false - gdy nie ma wynurzenia
     */
    bool emergence() const;

public:
    stage(Link& lin) : link(lin) {}
    /*!
     * \brief Dodaje bottom na scenę
     * Zapisuje pliki opisujące powierzchnię dna
     * \param[in] local_name - nazwa pliku z współrzędnymi lokalnymi
     * \param[in] global_name - nazwa pliku z współrzędnymi globalnymi
     */
    void add_bottom(const std::string& local_name, const std::string& global_name);
    /*!
     * \brief Dodaje wodę na scenę
     * Zapisuje pliki opisujące powierzchnię wody
     * \param[in] local_name - nazwa pliku z współrzędnymi lokalnymi
     * \param[in] global_name - nazwa pliku z współrzędnymi globalnymi
     */
    void add_water(const std::string& local_name, const std::string& global_name);
    /*!
     * \brief Dodaje body drona na scenę
     * Zapisuje pliki opisujące body
     * \param[in] local_name - nazwa pliku z współrzędnymi lokalnymi
     * \param[in] global_name - nazwa pliku z współrzędnymi globalnymi
     */
    void add_body(const std::string& local_name, const std::string& global_name);
    /*!
     * \brief Dodaje lewą śrubę drona na scenę
     * Zapisuje pliki opisujące lewą śrubę
     * \param[in] local_name - nazwa pliku z współrzędnymi lokalnymi
     * \param[in] global_name - nazwa pliku z współrzędnymi globalnymi
     */
    void add_left_motor(const std::string& local_name, const std::string& global_name);
    /*!
     * \brief Dodaje prawą śrubę drona na scenę
     * Zapisuje pliki opisujące prawą śrubę
     * \param[in] local_name - nazwa pliku z współrzędnymi lokalnymi
     * \param[in] global_name - nazwa pliku z współrzędnymi globalnymi
     */
    void add_right_motor(const std::string& local_name, const std::string& global_name);
    /*!
     * \brief Dodaje prostopadłościan na scenę
     * Zapisuje pliki opisujące prostopadłościan i dodaje go na koniec listy przeszkód.
     * \param[in] local_name - nazwa pliku z współrzędnymi lokalnymi
     * \param[in] global_name - nazwa pliku z współrzędnymi globalnymi
     */
    void add_cuboid(const std::string& local_name, const std::string& global_name);
    /*!
     * \brief Dodaje pręt na scenę
     * Zapisuje pliki opisujące pręt i dodaje go na koniec listy przeszkód.
     * \param[in] local_name - nazwa pliku z współrzędnymi lokalnymi
     * \param[in] global_name - nazwa pliku z współrzędnymi globalnymi
     */
    void add_bar(const std::string& local_name, const std::string& global_name);
    /*!
     * \brief Dodaje prostokąt na scenę
     * Zapisuje pliki opisujące prostokąt i dodaje go na koniec listy przeszkód.
     * \param[in] local_name - nazwa pliku z współrzędnymi lokalnymi
     * \param[in] global_name - nazwa pliku z współrzędnymi globalnymi
     */
    void add_rectangle(const std::string& local_name, const std::string& global_name);

    /*! \brief initializee Łącze do gnuplota oraz drona */
    void initialize();

    /*!
     * \brief Powoduje ruch drona na wprost
     * Powoduje ruch obiektu dron na wprost na zadaną odległość
     * i o dany kąt wznoszenia
     * \param[in] rising_angle - kąt o jaki ma się wznieść dron
     * \param[in] distance - odległość na jaką ma się przemiaeścić dron
     */
    void move_ahead(double rising_angle, double distance);
    /*!
     * \brief Powoduje obrót drona
     * Powoduje obrót drona wokół własnej osi o zadany kąt
     * \param[in] rotation_angle - kąt o jaki ma być wykonany obrót
     */
    void rotation(double rotation_angle);
};
