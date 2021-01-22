/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Quick Templates 2 module of the Qt Toolkit.
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

#ifndef QQUICKPOPUPANCHORS_P_P_H
#define QQUICKPOPUPANCHORS_P_P_H

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

#include <QtCore/private/qobject_p.h>
#include <QtQuickTemplates2/private/qquickpopup_p_p.h>

QT_BEGIN_NAMESPACE

class QQuickItem;
class QQuickPopup;

class QQuickPopupAnchorsPrivate : public QObjectPrivate
{
    Q_DECLARE_PUBLIC(QQuickPopupAnchors)

public:
    static QQuickPopupAnchorsPrivate *get(QQuickPopupAnchors *popupAnchors)
    {
        return popupAnchors->d_func();
    }

    QQuickPopup *popup = nullptr;
    QQuickItem *centerIn = nullptr;
};

QT_END_NAMESPACE

#endif // QQUICKPOPUPANCHORS_P_P_H
