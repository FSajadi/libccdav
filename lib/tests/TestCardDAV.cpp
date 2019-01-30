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

 private slots:
  void initTestCase() {
    int argc = 1;
    char* argv[] = {"test"};

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
    QString uid = QUuid::createUuid().toString();
    QString vCard =
        "BEGIN:VCARD \
        VERSION:3.0 \
        N:Basak;Anupam;;;Basak \
        ADR;INTL;PARCEL;WORK:;;;;;;India \
        EMAIL;INTERNET:anupam.basak27@gmail.com \
        TEL;WORK:8981861008 \
        UID: " +
        uid + "END:VCARD";
    CardDAVReply* reply = this->cardDAVClient->createContact(uid, vCard);
    this->connect(reply, &CardDAVReply::createContactResponse, [=]() {
      QCoreApplication::exit(0);

      qDebug() << "Contact Created";
    });
    this->connect(reply, &CardDAVReply::error,
                  [=](QNetworkReply::NetworkError err) {
                    QCoreApplication::exit(0);
                    //                    QCOMPARE(err, nullptr);
                  });
    this->app->exec();
  }

  void testUpdateContact() {}

  void testDeleteContact() {}

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
                    //                    QCOMPARE(err, nullptr);
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
