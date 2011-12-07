/*
    WPN-XM Server Control Panel

    WPN-XM SCP is a tool to manage Nginx, PHP and MariaDb daemons under windows.
    It's a fork of Easy WEMP originally written by Yann Le Moigne and (c) 2010.
    WPN-XM SCP is written by Jens-Andre Koch and (c) 2011 - onwards.

    This file is part of WPN-XM Serverpack for Windows.

    WPN-XM SCP is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    WPN-XM SCP is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with WPN-XM SCP. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef WpnxmTRAY_H
#define WpnxmTRAY_H

#include <QSystemTrayIcon>
#include <QProcess>

class QMenu;
class QAction;
class QApplication;
class QSettings;

// declare interfaces
void exitIfAlreadyRunning();

class WpnxmTray : public QSystemTrayIcon
{
        Q_OBJECT // Enables signals and slots

public:
        explicit WpnxmTray(QApplication *parent = 0);
        ~WpnxmTray();

signals:

public slots:

        // General Action Slots
        void runAll();
        void stopAll();
        void restartAll();        
        void goToWebsiteHelp();

        // Nginx Action Slots
        void runNginx();
        void stopNginx();
        void reloadNginx();
        void restartNginx();

        // PHP Action Slots
        void runPhp();
        void stopPhp();
        void restartPhp();

        // MySQL Action Slots
        void runMySQL();
        void stopMySQL();
        void restartMySQL();

        // Config Action Slots
        void manageHosts();

        void openNginxSite();
        void openNginxConfig();
        void openNginxLogs();

        void openPhpConfig();

        void openMySqlWorkbench();
        void openMySqlClient();
        void openMySqlConfig();

        // Status Action Slots
        void globalStateChanged();
        void updateGlobalStatusImage();
        void nginxStateChanged(QProcess::ProcessState state);
        void phpStateChanged(QProcess::ProcessState state);
        void mysqlStateChanged(QProcess::ProcessState state);

        void nginxProcessError(QProcess::ProcessError error);
        void phpProcessError(QProcess::ProcessError error);
        void mysqlProcessError(QProcess::ProcessError error);

private:

        QTimer* timer;
        int iCurrentImage;

        bool bAutostartDaemons;

        // PHP
#define PHPCGI_EXEC "/php-cgi.exe"
        QString cfgPhpDir;
        QString cfgPhpExec;
        QString cfgPhpFastCgiHost;
        QString cfgPhpFastCgiPort;

        // NGINX
        QString cfgNginxDir;
        QString cfgNginxExec;
        QString cfgNginxSites;
        QString cfgNginxConfig;
        QString cfgNginxLogs;

        // MySQL
        QString cfgMySqlDir;
        QString cfgMySqlExec;
        QString cfgMySqlConfig;
        QString cfgMySqlClientExec;

        // MySQL Workbench
        QString cfgMySqlWorkbenchExec;
        QString cfgMySqlWorkbenchDir;

        // Process Monitoring
        QProcess* processNginx;
        QProcess* processPhp;
        QProcess* processMySql;

        // Menus
        void createTrayMenu();
        QMenu* MainMenu;
        QMenu* globalStatusSubmenu;
        QMenu* nginxStatusSubmenu;
        QMenu* phpStatusSubmenu;
        QMenu* mysqlStatusSubmenu;        

        void initializeConfiguration();

        QString getProcessErrorMessage(QProcess::ProcessError);
};

#endif // WpnxmTRAY_H