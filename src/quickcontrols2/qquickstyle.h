/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Quick Controls 2 module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
****************************************************************************/

#ifndef QQUICKSTYLE_H
#define QQUICKSTYLE_H

#include <QtCore/qurl.h>
#include <QtCore/qstring.h>
#include <QtQuickControls2/qtquickcontrols2global.h>

QT_BEGIN_NAMESPACE

class Q_QUICKCONTROLS2_EXPORT QQuickStyle
{
public:
    static QString name();
    static QString path();
    static void setStyle(const QString &style);
    static void setFallbackStyle(const QString &style);
    static QStringList availableStyles();
    static QStringList stylePathList();
    static void addStylePath(const QString &path);
};

QT_END_NAMESPACE

#endif // QQUICKSTYLE_H
