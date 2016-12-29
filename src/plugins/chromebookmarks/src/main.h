// albert - a simple application launcher for linux
// Copyright (C) 2014-2016 Manuel Schneider
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#pragma once
#include <QObject>
#include <QTimer>
#include <QPointer>
#include <QMutex>
#include <QFileSystemWatcher>
#include <vector>
#include <memory>
#include "extension.h"
#include "queryhandler.h"
#include "offlineindex.h"
using std::vector;
using std::shared_ptr;
namespace Core {
class StandardIndexItem;
}

namespace ChromeBookmarks {

class ConfigWidget;

class Extension final :
        public QObject,
        public Core::Extension,
        public Core::QueryHandler
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID ALBERT_EXTENSION_IID FILE "metadata.json")

    class Indexer;

public:

    Extension();
    ~Extension();

    /*
     * Implementation of extension interface
     */

    QString name() const override { return "Chrome bookmarks"; }
    QWidget *widget(QWidget *parent = nullptr) override;
    void handleQuery(Core::Query * query) override;

    /*
     * Extension specific members
     */

    const QString &path();
    void setPath(const QString &path);
    void restorePath();

    bool fuzzy();
    void setFuzzy(bool b = true);

    void updateIndex();

private:
    QPointer<ConfigWidget> widget_;
    vector<shared_ptr<Core::StandardIndexItem>> index_;
    Core::OfflineIndex offlineIndex_;
    QMutex indexAccess_;
    QPointer<Indexer> indexer_;
    QString bookmarksFile_;
    QFileSystemWatcher watcher_;

    /* const */
    static const char* CFG_PATH;
    static const char* CFG_FUZZY;
    static const bool  DEF_FUZZY;

signals:
    void pathChanged(const QString&);
    void statusInfo(const QString&);
};
}
