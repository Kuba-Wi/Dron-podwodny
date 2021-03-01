#include <string>
#include "TMatrix.hh"
#include "TVector.hh"

void rtrim_string(std::string& str);
void check_reading_writing_to_file(const std::string& local_name, const std::string& global_name);
void check_moved(const TMatrix<double, 3>& rotation_3D,
                 const TVector<double, 3>& translation_3D,
                 const TVector<double, 3>& local_3D,
                 const TVector<double, 3>& global_3D);

void check_move_and_rotation(const std::string& local_name,
                             const std::string& global_name,
                             const TMatrix<double, 3>& rotation_3D,
                             const TVector<double, 3>& translation_3D);

void rotation_z(TMatrix<double, size_of_TVec_3D>& rotation, double rotation_angle);
