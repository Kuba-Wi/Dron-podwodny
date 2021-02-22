#include "surface.hh"
#include <fstream>
#include "TVector.hh"

void surface::add_local_file(const std::string& local_name) {
    local_file_name = local_name;
}

void surface::add_global_file(const std::string& global_name) {
    file_with_points = global_name;
}

void surface::read_local() {
    std::ifstream read;
    std::ofstream write;
    TVector<double, 3> wiersz;

    read.open(local_file_name);
    write.open(file_with_points);

    if (!(read.is_open() && write.is_open()))
        return;

    read >> wiersz;
    while (!read.eof()) {
        if (!read) {
            read.clear();
            while (read.get() != '\n')
                ;
            write << "#\n\n";
        } else
            write << wiersz;

        read >> wiersz;
    }

    z_of_surface = wiersz[2];

    read.close();
    write.close();
}
