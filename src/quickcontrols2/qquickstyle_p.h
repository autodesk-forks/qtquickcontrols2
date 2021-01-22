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

#ifndef QQUICKSTYLE_P_H
#define QQUICKSTYLE_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <QtCore/qurl.h>
#include <QtCore/qsharedpointer.h>
#include <QtQuickControls2/private/qtquickcontrols2global_p.h>

QT_BEGIN_NAMESPACE

class QSettings;

class Q_QUICKCONTROLS2_PRIVATE_EXPORT QQuickStylePrivate
{
public:
    static QStringList stylePaths(bool resolve = false);
    static QString fallbackStyle();
    static bool isCustomStyle();
    static void init(const QUrl &baseUrl);
    static void reset();
    static QString configFilePath();
    static QSharedPointer<QSettings> settings(const QString &group = QString());
    static const QFont *readFont(const QSharedPointer<QSettings> &settings);
    static const QPalette *readPalette(const QSharedPointer<QSettings> &settings);
    static bool isDarkSystemTheme();
};

QT_END_NAMESPACE

#endif // QQUICKSTYLE_P_H
