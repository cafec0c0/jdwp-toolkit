#include "UrlMapper.h"
QString UrlMapper::getUrlForJdwpCommand(const QString &section) {
  return "https://docs.oracle.com/en/java/javase/23/docs/specs/jdwp/"
         "jdwp-protocol.html#" +
         section;
}