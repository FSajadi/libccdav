#ifndef UTILS_CARDDAVREPLY_HPP
#define UTILS_CARDDAVREPLY_HPP

#include <QObject>
#include <QNetworkReply>

#include "../dto/CardDAVResponseItem.hpp"

class CardDAVReply : public QObject {
  Q_OBJECT

 public:
  void sendTestConnectionResponseSignal(bool isSuccess);
  void sendListContactsResponseSignal(QList<Contact *> contacts);
  void sendCreateContactResponseSignal();
  void sendUpdateContactResponseSignal();
  void sendDeleteContactResponseSignal();
  void sendError(QNetworkReply::NetworkError err);

 signals:
  void testConnectionResponse(bool isSuccess);
  void listAllContactsResponse(QList<Contact *> contacts);
  void createContactResponse();
  void updateContactResponse();
  void deleteContactResponse();
  void error(QNetworkReply::NetworkError err);
};

#endif
