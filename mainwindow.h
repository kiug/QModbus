/****************************************************************************
**
** SPDX-License-Identifier: LGPL-3.0-or-later
** SPDX-FileCopyrightText: 2012 - present, Karol Drożak <karoldro@gmail.com>
**
****************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qmodbus.h"
#include "qmodbusmaster.h"

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void connectToDevice ();
    void sendQuery ();

private:
    void addResultRow (int address, const QString &value);

    Ui::MainWindow *ui;
    Modbus::QModbusMaster * modbus;
};

#endif // MAINWINDOW_H
