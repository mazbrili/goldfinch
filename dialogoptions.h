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

#ifndef DIALOGOPTIONS_H
#define DIALOGOPTIONS_H

#include <QDialog>

namespace Ui {
class DialogOptions;
}

class DialogOptions : public QDialog
{
    Q_OBJECT

public:
    explicit DialogOptions(QWidget *parent = nullptr);

    ~DialogOptions();

    bool clearData();

private slots:
    void on_toolButtonAdd_clicked();

    void on_toolButtonRemove_clicked();

    void on_buttonBox_accepted();

    void on_checkBoxRemove_toggled(bool checked);

    void on_comboBoxStyls_activated(const QString &arg1);

    void on_checkBoxNotify_toggled(bool checked);

    void on_checkBoxTrayIcon_toggled(bool checked);

    void on_comboBoxLanguage_activated(const QString &arg1);

    void on_checkBoxShowMenu_toggled(bool checked);

private:
    Ui::DialogOptions *ui;
};

#endif // DIALOGOPTIONS_H
