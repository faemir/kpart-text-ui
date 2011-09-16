/*
    KDE Telepathy AdiumxtraProtocolHandler - Install Adiumxtra packages through adiumxtra://-pseudo protocol
    Copyright (C) 2010 Dominik Schmidt <domme@rautelinux.org>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "adiumxtra-protocol-handler.h"
#include "chat-style-installer.h"
#include "emoticon-set-installer.h"

#include <KDETelepathy/ChatWindowStyleManager>

#include <KDebug>
#include <KZip>
#include <KTar>
#include <KEmoticons>
#include <KTemporaryFile>
#include <KIO/Job>
#include <KIO/NetAccess>
#include <KNotification>
#include <KIcon>

AdiumxtraProtocolHandler::AdiumxtraProtocolHandler()
{
    kDebug();
}

AdiumxtraProtocolHandler::~AdiumxtraProtocolHandler()
{
    kDebug();
}

BundleInstaller::BundleStatus AdiumxtraProtocolHandler::install(const QString &path)
{
    kDebug();

    KUrl url(path);
    if(url.protocol() == QLatin1String("adiumxtra")) {
        url.setProtocol(QLatin1String("http"));
    }

    KTemporaryFile *tmpFile = new KTemporaryFile();
    if (tmpFile->open()) {
        KIO::Job* getJob = KIO::file_copy(url.prettyUrl(), KUrl(tmpFile->fileName()), -1, KIO::Overwrite);
        if (!KIO::NetAccess::synchronousRun(getJob, 0)) {
            kDebug() << "download failed";
            return BundleInstaller::BundleCannotOpen;
        }
    }

    KArchive *archive = 0L;

    QString currentBundleMimeType = KMimeType::findByPath(tmpFile->fileName(), 0, false)->name();
    if (currentBundleMimeType == QLatin1String("application/zip")) {
        archive = new KZip(tmpFile->fileName());
    } else if (currentBundleMimeType == QLatin1String("application/x-compressed-tar") ||
               currentBundleMimeType == QLatin1String("application/x-bzip-compressed-tar") ||
               currentBundleMimeType == QLatin1String("application/x-gzip") ||
               currentBundleMimeType == QLatin1String("application/x-bzip")) {
        archive = new KTar(tmpFile->fileName());
    } else {
        KNotification *notification = new KNotification(QLatin1String("packagenotrecognized"), NULL, KNotification::Persistent);
        notification->setText( i18n("Package type not recognized or not supported") );
        notification->setActions( QStringList() << i18n("Ok") );
        QObject::connect(notification, SIGNAL(action1Activated()), this, SLOT(install()));
        QObject::connect(notification, SIGNAL(action1Activated()), notification, SLOT(close()));

        QObject::connect(notification, SIGNAL(ignored()), this, SLOT(ignoreRequest()));
        QObject::connect(notification, SIGNAL(ignored()), notification, SLOT(close()));
        notification->sendEvent();
        kDebug() << "unsupported file type" << currentBundleMimeType;
        kDebug() << tmpFile->fileName();
        return BundleInstaller::BundleNotValid;
    }

    if (!archive->open(QIODevice::ReadOnly)) {
        delete archive;
        kDebug() << "cannot open theme file";
        return BundleInstaller::BundleCannotOpen;
    }

    BundleInstaller *installer = new ChatStyleInstaller(archive, tmpFile);
    if(installer->validate() == BundleInstaller::BundleValid) {
        installer->showRequest();

        QObject::connect(installer, SIGNAL(finished(BundleInstaller::BundleStatus)),
                         installer, SLOT(showResult()));
        QObject::connect(installer, SIGNAL(showedResult()), this, SLOT(quit()));
        QObject::connect(installer, SIGNAL(ignoredRequest()), this, SLOT(quit()));

        kDebug() << "sent messagestyle request";
    } else {
        delete installer;
        installer = new EmoticonSetInstaller(archive, tmpFile);
        if(installer->validate() == BundleInstaller::BundleValid) {
            installer->showRequest();

            QObject::connect(installer, SIGNAL(finished(BundleInstaller::BundleStatus)),
                             installer, SLOT(showResult()));
            QObject::connect(installer, SIGNAL(showedResult()), this, SLOT(quit()));
            QObject::connect(installer, SIGNAL(ignoredRequest()), this, SLOT(quit()));

            kDebug() << "sent emoticonset request";
        } else {
            KNotification *notification = new KNotification(QLatin1String("packagenotrecognized"), NULL,
                                                            KNotification::Persistent);
            notification->setText( i18n("Package type not recognized or not supported") );
            QObject::connect(notification, SIGNAL(action1Activated()), this, SLOT(install()));
            QObject::connect(notification, SIGNAL(action1Activated()), notification, SLOT(close()));

            QObject::connect(notification, SIGNAL(ignored()), this, SLOT(ignoreRequest()));
            QObject::connect(notification, SIGNAL(ignored()), notification, SLOT(close()));
            notification->setActions( QStringList() << i18n("Ok") );
            notification->sendEvent();
            kDebug() << "sent error";

            return BundleInstaller::BundleUnknownError;
        }
    }

    return BundleInstaller::BundleValid;
}
