#define ST(e) #e
#include "JdwpConstantsMapper.h"

#include <QMap>

static QMap<JdwpLibError, QPair<QString, QString>> errorEnumMap = {
    {
        JDWP_LIB_ERR_NONE,
        {
            ST(JDWP_LIB_ERR_NONE),
            "none",
        },
    },
    {
        JDWP_LIB_ERR_UNKNOWN_COMMAND_SET,
        {
            ST(JDWP_LIB_ERR_UNKNOWN_COMMAND_SET),
            "unknown JDWP command set",
        },
    },
    {
        JDWP_LIB_ERR_UNKNOWN_COMMAND,
        {
            ST(JDWP_LIB_ERR_UNKNOWN_COMMAND),
            "unknown JDWP command",
        },
    },
    {
        JDWP_LIB_ERR_NULL_POINTER,
        {
            ST(JDWP_LIB_ERR_NULL_POINTER),
            "null pointer",
        },
    },
    {
        JDWP_LIB_ERR_MALLOC,
        {
            ST(JDWP_LIB_ERR_MALLOC),
            "unable to allocate memory",
        },
    },
    {
        JDWP_LIB_ERR_EOF,
        {
            ST(JDWP_LIB_ERR_EOF),
            "unexpected EOF on the JDWP socket",
        },
    },
    {
        JDWP_LIB_ERR_NATIVE,
        {
            ST(JDWP_LIB_ERR_NATIVE),
            "native error",
        },
    },
    {
        JDWP_LIB_ERR_PTHREAD,
        {
            ST(JDWP_LIB_ERR_PTHREAD),
            "pthread error",
        },
    },
    {
        JDWP_LIB_ERR_HANDSHAKE_FAILED,
        {
            ST(JDWP_LIB_ERR_HANDSHAKE_FAILED),
            "jdwp handshake failed",
        },
    },
    {
        JDWP_LIB_ERR_INVALID_ADDRESS,
        {
            ST(JDWP_LIB_ERR_INVALID_ADDRESS),
            "invalid address",
        },
    },
    {
        JDWP_LIB_ERR_COMMAND_BUFFER_FULL,
        {
            ST(JDWP_LIB_ERR_COMMAND_BUFFER_FULL),
            "command buffer full",
        },
    },
};

QString JdwpConstantsMapper::getJdwpLibErrorEnumName(JdwpLibError error) {
  return errorEnumMap[error].first;
}

QString JdwpConstantsMapper::getJdwpLibErrorDescription(JdwpLibError error) {
  return errorEnumMap[error].second;
}

QString JdwpConstantsMapper::getStatusString(int status) {
  QList<QString> list;
  if (status & JDWP_CLASS_STATUS_VERIFIED)
    list.push_back("VERIFIED");
  if (status & JDWP_CLASS_STATUS_PREPARED)
    list.push_back("PREPARED");
  if (status & JDWP_CLASS_STATUS_INITIALIZED)
    list.push_back("INITIALIZED");
  if (status & JDWP_CLASS_STATUS_ERROR)
    list.push_back("ERROR");
  return list.join("|");
}

QString JdwpConstantsMapper::getTypeTagString(JdwpTypeTag tag) {
  switch (tag) {
  case JDWP_TYPE_TAG_CLASS:
    return "CLASS";
  case JDWP_TYPE_TAG_INTERFACE:
    return "INTERFACE";
  case JDWP_TYPE_TAG_ARRAY:
    return "ARRAY";
  default:
    return "UNKNOWN";
  }
}