#ifndef UTILS_XMLHELPER_HPP
#define UTILS_XMLHELPER_HPP

#include <QList>
#include <QString>

#include "../dto/CardDAVResponseItem.hpp"

class XMLHelper {
 public:
  QList<CardDAVResponseItem*> parseCardDAVMultiStatusResponse(
      QString responseXml);
};

#endif
