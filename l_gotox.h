#include <iostream>
#include <string>
#include <sstream>

Template <class T>
    inline string ToString(const T& t) {
    stringstream ss;
    ss << t;
    return ss.str();
}
/* Función para emular al gotoxy en la consola de
Linux.
*/
inline string gotoxy(const int& x,const int& y) {
  return "\33[" + ToString(y) + ";" + ToString(x) + "H";
}
