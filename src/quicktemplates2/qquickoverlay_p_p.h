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

#ifndef QQUICKOVERLAY_P_P_H
#define QQUICKOVERLAY_P_P_H

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

#include <QtQuickTemplates2/private/qquickoverlay_p.h>

#include <QtQuick/private/qquickitem_p.h>
#include <QtQuick/private/qquickitemchangelistener_p.h>

QT_BEGIN_NAMESPACE

class QQuickPopup;
class QQuickDrawer;

class QQuickOverlayPrivate : public QQuickItemPrivate, public QQuickItemChangeListener
{
    Q_DECLARE_PUBLIC(QQuickOverlay)

public:
    static QQuickOverlayPrivate *get(QQuickOverlay *overlay)
    {
        return overlay->d_func();
    }

    bool startDrag(QEvent *event, const QPointF &pos);
    bool handlePress(QQuickItem *source, QEvent *event, QQuickPopup *target);
    bool handleMove(QQuickItem *source, QEvent *event, QQuickPopup *target);
    bool handleRelease(QQuickItem *source, QEvent *event, QQuickPopup *target);

    bool handleMouseEvent(QQuickItem *source, QMouseEvent *event, QQuickPopup *target = nullptr);
#if QT_CONFIG(quicktemplates2_multitouch)
    bool handleTouchEvent(QQuickItem *source, QTouchEvent *event, QQuickPopup *target = nullptr);
#endif

    void addPopup(QQuickPopup *popup);
    void removePopup(QQuickPopup *popup);
    void setMouseGrabberPopup(QQuickPopup *popup);

    QVector<QQuickPopup *> stackingOrderPopups() const;
    QVector<QQuickDrawer *> stackingOrderDrawers() const;

    void itemGeometryChanged(QQuickItem *item, QQuickGeometryChange change, const QRectF &diff) override;

    void updateGeometry();

    QQmlComponent *modal = nullptr;
    QQmlComponent *modeless = nullptr;
    QVector<QQuickPopup *> allPopups;
    QVector<QQuickDrawer *> allDrawers;
    QPointer<QQuickPopup> mouseGrabberPopup;
};

QT_END_NAMESPACE

#endif // QQUICKOVERLAY_P_P_H
