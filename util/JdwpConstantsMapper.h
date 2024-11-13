#ifndef JDWPERRORMAPPER_H
#define JDWPERRORMAPPER_H
#include "client/JdwpClientWrapper.h"

#include <QString>

class JdwpConstantsMapper {
public:
  static QString getJdwpLibErrorEnumName(JdwpLibError error);
  static QString getJdwpLibErrorDescription(JdwpLibError error);

  static QString getStatusString(int status);
  static QString getTypeTagString(JdwpTypeTag tag);
};

#endif // JDWPERRORMAPPER_H
