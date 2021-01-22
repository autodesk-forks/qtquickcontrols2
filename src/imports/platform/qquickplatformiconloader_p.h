/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Labs Platform module of the Qt Toolkit.
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

#ifndef QQUICKPLATFORMICONLOADER_P_H
#define QQUICKPLATFORMICONLOADER_P_H

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
#include <QtCore/qstring.h>
#include <QtGui/qicon.h>
#include <QtQuick/private/qquickpixmapcache_p.h>

#include "qquickplatformicon_p.h"

QT_BEGIN_NAMESPACE

class QObject;

class QQuickPlatformIconLoader : public QQuickPixmap
{
public:
    QQuickPlatformIconLoader(int slot, QObject *parent);

    bool isEnabled() const;
    void setEnabled(bool enabled);

    QIcon toQIcon() const;

    QQuickPlatformIcon icon() const;
    void setIcon(const QQuickPlatformIcon &icon);

private:
    void loadIcon();

    QObject *m_parent;
    int m_slot;
    bool m_enabled;
    QQuickPlatformIcon m_icon;
};

QT_END_NAMESPACE

#endif // QQUICKPLATFORMICONLOADER_P_H
