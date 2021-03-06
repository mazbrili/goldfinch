/***************************************************************************
 *      Project created by QtCreator 2018-06-01T17:15:24                   *
 *                                                                         *
 *    goldfinch Copyright (C) 2014 AbouZakaria <yahiaui@gmail.com>         *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "player_adaptor.h"
#include <QDBusConnection>

//---------------------------------------------------------------MainAdaptor
MainAdaptor::MainAdaptor(QObject *parent)
    : QDBusAbstractAdaptor(parent)
{
    // constructor
    setAutoRelaySignals(true);
}

MainAdaptor::~MainAdaptor()
{
    // destructor
}

void MainAdaptor:: Quit()
{  QMetaObject::invokeMethod(parent(), "appQuit"); }

void MainAdaptor:: Raise()
{  QMetaObject::invokeMethod(parent(), "showRaise"); }

void MainAdaptor:: Hide()
{  QMetaObject::invokeMethod(parent(), "appHide"); }

void MainAdaptor:: ToggleHide()
{  QMetaObject::invokeMethod(parent(), "toggleHide"); }

//----------------------------------------------------------PlayerAdaptor
PlayerAdaptor::PlayerAdaptor(QObject *parent)
    : QDBusAbstractAdaptor(parent)
{
    // constructor
    setAutoRelaySignals(true);
    connect(this,&PlayerAdaptor::Seeked,this,&PlayerAdaptor::Seek);
}

PlayerAdaptor::~PlayerAdaptor()
{
    // destructor

}

//--------------------------- METHODS ---------------------------

void PlayerAdaptor::Seek(qlonglong Offset)
{
    qDebug()<<"PlayerAdaptor::Seek==========================="<<Offset;
    QMetaObject::invokeMethod(parent(), "seek", Q_ARG(qlonglong, Offset));}

void PlayerAdaptor::SetPosition(const QDBusObjectPath &TrackId, qlonglong Position)
{
     qDebug()<<"PlayerAdaptor::SetPosition========================"<<Position<<&TrackId;
    Q_UNUSED(TrackId);
      QMetaObject::invokeMethod(parent(), "seek", Q_ARG(qlonglong, Position));
}

void PlayerAdaptor::Play()
{  QMetaObject::invokeMethod(parent(), "play");     }

void PlayerAdaptor::Pause()
{  QMetaObject::invokeMethod(parent(), "pause");    }

void PlayerAdaptor::Stop()
{  QMetaObject::invokeMethod(parent(), "stop");     }

void PlayerAdaptor::PlayPause()
{  QMetaObject::invokeMethod(parent(), "playPause");}

void PlayerAdaptor::Next()
{  QMetaObject::invokeMethod(parent(), "next");     }

void PlayerAdaptor::Previous()
{  QMetaObject::invokeMethod(parent(), "previous"); }

//--------------------------- PROOERTIES ---------------------------

bool PlayerAdaptor::CanPlay()
{
    bool retVal;
    QMetaObject::invokeMethod(parent(), "canPlay", Qt::DirectConnection,
                              Q_RETURN_ARG(bool, retVal)  );
    return  retVal;
}

bool PlayerAdaptor::CanPause()
{
        bool retVal;
        QMetaObject::invokeMethod(parent(), "canPause", Qt::DirectConnection,
                                  Q_RETURN_ARG(bool, retVal));
        return  retVal;
  //  return true;
}

bool PlayerAdaptor::CanSeek()
{
    bool retVal;
    QMetaObject::invokeMethod(parent(), "canSeek", Qt::DirectConnection,
                              Q_RETURN_ARG(bool, retVal));
    return  retVal;
}

bool PlayerAdaptor::CanGoPrevious()
{
    bool retVal;
    QMetaObject::invokeMethod(parent(), "canGoPrevious", Qt::DirectConnection,
                              Q_RETURN_ARG(bool, retVal));
    return  retVal;
    // return  true;
}

bool PlayerAdaptor::CanGoNext()
{
    bool retVal;
    QMetaObject::invokeMethod(parent(), "canGoNext", Qt::DirectConnection,
                              Q_RETURN_ARG(bool, retVal));
    return  retVal;
}

QString PlayerAdaptor::PlaybackStatus()
{
    QString retVal;
    QMetaObject::invokeMethod(parent(), "playbackStatus", Qt::DirectConnection,
                              Q_RETURN_ARG(QString, retVal));
    return  retVal;
}

qint64 PlayerAdaptor::Position()
{
    qlonglong retVal;
    QMetaObject::invokeMethod(parent(), "position", Qt::DirectConnection,
                              Q_RETURN_ARG(qlonglong, retVal));
    return  retVal;
}

void PlayerAdaptor::setPos(qint64 p)
{
    QVariantMap changedProps;
    changedProps.insert("Position", p*1000);
    propertiesChanged(changedProps);
}


QVariantMap  PlayerAdaptor::Metadata()
{
    QVariantMap map;
    QMetaObject::invokeMethod(parent(), "metadata", Qt::DirectConnection,
                              Q_RETURN_ARG(QVariantMap, map));
    return  map;
}

//--------------------------- SIGNALS ---------------------------
void PlayerAdaptor::propertiesChanged(QVariantMap changedProps)
{
    QDBusMessage signal = QDBusMessage::createSignal(
                "/org/mpris/MediaPlayer2",
                "org.freedesktop.DBus.Properties",
                "PropertiesChanged");

    signal << "org.mpris.MediaPlayer2.Player";
    signal << changedProps;
    signal << QStringList();

    if (QDBusConnection::sessionBus().send(signal))
        qDebug()<<"PlayerAdaptor::propertiesChanged :signal emited"/*<<changedProps*/;
    else
        qDebug()<<"PlayerAdaptor::propertiesChanged :signal No Emited";
}

 void PlayerAdaptor:: SetUrl(const QString &url)
 {
     qDebug()<<"Adaptor:: setUrl"<<url;
  //   QUrl urlm=QUrl::fromLocalFile(url);
  QMetaObject::invokeMethod(parent(), "setFile", Q_ARG(QString, url));
 // QMetaObject::invokeMethod(parent(), "playLast");
 }

 bool PlayerAdaptor::Notify(const QString &app_name, const QString &app_icon,
                    const QString &summary, const QString &body,
                        int expire_timeout)
 {
     QDBusConnection connection = QDBusConnection::sessionBus();

      if ( connection.registerService("org.freedesktop.Notifications"))
      {
          connection.unregisterService("org.freedesktop.Notifications");
          return  false;
      }
     QDBusInterface kdbus("org.freedesktop.Notifications",
                         "/org/freedesktop/Notifications",
                         "org.freedesktop.Notifications");

     if (!kdbus.isValid()) {  return false; }

     QList<QVariant> args;
     args.append(app_name);       // Application Name
     args.append(0123U);         // Replaces ID (0U)
     args.append(app_icon);     // Notification Icon
     args.append( summary);       // Summary
     args.append(body);          // Body
     args.append(QStringList()); // Actions
     args.append(QVariantMap());
     args.append(expire_timeout);
     kdbus.callWithArgumentList(QDBus::AutoDetect, "Notify", args);

     return  true;
 }
