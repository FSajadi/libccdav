#ifndef TEST_TESTWEBDAVCLIENT
#define TEST_TESTWEBDAVCLIENT

#include <QCoreApplication>
#include <QObject>
#include <QTest>

#include "../CardDAV.hpp"
#include "../utils/CardDAVReply.hpp"
#include "../utils/Environment.hpp"

class TestCardDAV : public QObject {
  Q_OBJECT

 private:
  CardDAV* cardDAVClient;
  QCoreApplication* app;
  QString uid;

 private slots:
  void initTestCase() {
    int argc = 1;
    char* argv[] = {"test"};

    this->uid = QUuid::createUuid().toString().mid(1, 36);
    this->app = new QCoreApplication(argc, argv);
    this->cardDAVClient =
        new CardDAV(Environment::get("LIBCCDAV_TEST_HOST"),
                    Environment::get("LIBCCDAV_TEST_USER"),
                    Environment::get("LIBCCDAV_TEST_PASSWORD"));
  }

  void testConnection() {
    CardDAVReply* reply = this->cardDAVClient->testConnection();
    this->connect(reply, &CardDAVReply::testConnectionResponse,
                  [=](bool isSuccess) {
                    QCoreApplication::exit(0);
                    QCOMPARE(isSuccess, true);
                  });
    this->app->exec();

    CardDAV wrongCardDAVClient(
        "https://cloud.opendesktop.org/remote.php/dav/addressbooks/"
        "ab0027/",
        Environment::get("LIBCCDAV_TEST_USER"),
        Environment::get("LIBCCDAV_TEST_PASSWORD"));
    reply = wrongCardDAVClient.testConnection();
    this->connect(reply, &CardDAVReply::testConnectionResponse,
                  [=](bool isSuccess) {
                    QCoreApplication::exit(0);
                    QCOMPARE(isSuccess, false);
                  });
    this->app->exec();
  }

  void testCreateContact() {
    QString vCard =
        "BEGIN:VCARD\nVERSION:3.0\nN:Basak;Anupam;;;Basak\n ADR;INTL;PARCEL;"
        "WORK:;;;;;;India\nEMAIL;INTERNET:anupam.basak27@gmail.com\nTEL;WORK:"
        "8981861008\nEND:VCARD";
    CardDAVReply* reply = this->cardDAVClient->createContact(this->uid, vCard);
    this->connect(reply, &CardDAVReply::createContactResponse,
                  [=](Contact* contact) {
                    QCoreApplication::exit(0);

                    qDebug() << "\n\n    Contact Created."
                             << "\n    ETAG :" << contact->getEtag()
                             << "\n    Href:" << contact->getHref()
                             << "\n    vCard :" << contact->getVcard() << "\n";
                  });
    this->connect(reply, &CardDAVReply::error,
                  [=](QNetworkReply::NetworkError err) {
                    QCoreApplication::exit(0);
                    qDebug() << err;
                    QCOMPARE(err, QNetworkReply::NoError);
                  });
    this->app->exec();
  }

  void testUpdateContact() {
    QString vCard =
        "BEGIN:VCARD\nVERSION:3.0\nN:Basak;Probal;;;Basak\n ADR;INTL;PARCEL;"
        "WORK:;;;;;;India\nEMAIL;INTERNET:probal31@gmail.com\nTEL;WORK:"
        "8981861008\nEND:VCARD";
    CardDAVReply* reply = this->cardDAVClient->updateContact(
        QUrl(Environment::get("LIBCCDAV_TEST_HOST") + "/" + this->uid + ".vcf"),
        vCard, "*");
    this->connect(reply, &CardDAVReply::updateContactResponse,
                  [=](Contact* contact) {
                    QCoreApplication::exit(0);

                    qDebug() << "\n\n    Contact Updated."
                             << "\n    ETAG :" << contact->getEtag()
                             << "\n    Href:" << contact->getHref()
                             << "\n    vCard:" << contact->getVcard() << "\n";
                  });
    this->connect(reply, &CardDAVReply::error,
                  [=](QNetworkReply::NetworkError err) {
                    QCoreApplication::exit(0);
                    qDebug() << err;
                    QCOMPARE(err, QNetworkReply::NoError);
                  });
    this->app->exec();
  }

  void testDeleteContact() {
    CardDAVReply* reply = this->cardDAVClient->deleteContact(QUrl(
        Environment::get("LIBCCDAV_TEST_HOST") + "/" + this->uid + ".vcf"));
    this->connect(reply, &CardDAVReply::deleteContactResponse, [=]() {
      QCoreApplication::exit(0);

      qDebug() << "Contact Deleted";
    });
    this->connect(reply, &CardDAVReply::error,
                  [=](QNetworkReply::NetworkError err) {
                    QCoreApplication::exit(0);
                    qDebug() << err;
                    QCOMPARE(err, QNetworkReply::NoError);
                  });
    this->app->exec();
  }

  void testListAllContacts() {
    CardDAVReply* reply = this->cardDAVClient->listAllContacts();
    this->connect(reply, &CardDAVReply::listAllContactsResponse,
                  [=](QList<Contact*> contacts) {
                    QCoreApplication::exit(0);

                    for (Contact* contact : contacts) {
                      qDebug() << ", ETag :" << contact->getEtag()
                               << "Contact URL :" << contact->getHref();
                      //                               << ", vCard :" <<
                      //                               contact->getVcard();
                    }
                  });
    this->connect(reply, &CardDAVReply::error,
                  [=](QNetworkReply::NetworkError err) {
                    QCoreApplication::exit(0);
                    qDebug() << err;
                    QCOMPARE(err, QNetworkReply::NoError);
                  });
    this->app->exec();
  }

  void cleanupTestCase() {
    delete this->app;
    delete this->cardDAVClient;
  }
};

QTEST_MAIN(TestCardDAV)
#include "TestCardDAV.moc"

#endif
