#ifndef DTO_CONTACT_HPP
#define DTO_CONTACT_HPP

#include <QString>

class Contact {
  public:
    Contact(QString vCard, QString eTag, QString href);

    QString getVcard();
    QString getEtag();
    QString getHref();

  private:
    QString vCard;
    QString eTag;
    QString href;
};

#endif
