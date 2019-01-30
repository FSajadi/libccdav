#include "Contact.hpp"

Contact::Contact(QString vCard, QString eTag, QString href) {
  this->vCard = vCard;
  this->eTag = eTag;
  this->href = href;
}

QString Contact::getVcard() { return this->vCard; }

QString Contact::getEtag() { return this->eTag; }

QString Contact::getHref() { return this->href; }
