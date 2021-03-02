#pragma once
#include "gmock/gmock.h"
#include "lacze_do_gnuplota.hh"

class LinkMock : public Link {
public:
    MOCK_METHOD(bool, Rysuj, (), (override));
    MOCK_METHOD(bool,
                DodajNazwePliku,
                (const char*, PzG::RodzajRysowania, int),
                (override));
    MOCK_METHOD(void, ZmienTrybRys, (PzG::TrybRysowania), (override));
    MOCK_METHOD(bool, Inicjalizuj, (), (override));
};
