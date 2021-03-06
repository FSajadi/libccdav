#ifndef UTILS_NETWORKHELPER_HPP
#define UTILS_NETWORKHELPER_HPP

#include <QIODevice>
#include <QMap>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QObject>
#include <QString>

class NetworkHelper : public QObject {
  Q_OBJECT

 private:
  QString host;
  QString username;
  QString password;
  QNetworkAccessManager* networkManager;

  void setRequestAuthHeader(QNetworkRequest* request);
  void setRequestHeaders(QNetworkRequest* request,
                         QMap<QString, QString> headers);

 public:
  NetworkHelper(QString host, QString username, QString password);

  QNetworkReply* makeRequest(QString method, QMap<QString, QString> headers);
  QNetworkReply* makeRequest(QString method, QMap<QString, QString> headers,
                             QString body);
  QNetworkReply* makeRequest(QString method, QUrl path,
                             QMap<QString, QString> headers, QString body);
  QNetworkReply* makePutRequest(QMap<QString, QString> headers,
                                QIODevice* file);
};

#endif
