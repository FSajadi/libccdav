#include "CardDAVReply.hpp"

void CardDAVReply::sendTestConnectionResponseSignal(bool isSuccess) {
  emit testConnectionResponse(isSuccess);
}

void CardDAVReply::sendListContactsResponseSignal(QList<Contact *> contacts) {
  emit listAllContactsResponse(contacts);
}

void CardDAVReply::sendCreateContactResponseSignal() {
  emit createContactResponse();
}

void CardDAVReply::sendUpdateContactResponseSignal() {
  emit updateContactResponse();
}

void CardDAVReply::sendDeleteContactResponseSignal() {
  emit deleteContactResponse();
}

void CardDAVReply::sendError(QNetworkReply::NetworkError err) {
  emit error(err);
}
