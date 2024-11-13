#ifndef URLMAPPER_H
#define URLMAPPER_H
#include <QString>

class UrlMapper {
public:
  static QString getUrlForJdwpCommand(const QString &section);
};

#endif // URLMAPPER_H
