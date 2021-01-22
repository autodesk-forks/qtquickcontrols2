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

#ifndef QQUICKDRAWER_P_P_H
#define QQUICKDRAWER_P_P_H

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

#include <QtQuickTemplates2/private/qquickdrawer_p.h>
#include <QtQuickTemplates2/private/qquickpopup_p_p.h>
#include <QtQuickTemplates2/private/qquickvelocitycalculator_p_p.h>

QT_BEGIN_NAMESPACE

class QQuickDrawerPrivate : public QQuickPopupPrivate
{
    Q_DECLARE_PUBLIC(QQuickDrawer)

public:
    static QQuickDrawerPrivate *get(QQuickDrawer *drawer)
    {
        return drawer->d_func();
    }

    qreal offsetAt(const QPointF &point) const;
    qreal positionAt(const QPointF &point) const;

    QQuickPopupPositioner *getPositioner() override;
    void showOverlay() override;
    void hideOverlay() override;
    void resizeOverlay() override;

    bool startDrag(QEvent *event);
    bool grabMouse(QQuickItem *item, QMouseEvent *event);
#if QT_CONFIG(quicktemplates2_multitouch)
    bool grabTouch(QQuickItem *item, QTouchEvent *event);
#endif
    bool blockInput(QQuickItem *item, const QPointF &point) const override;

    bool handlePress(QQuickItem* item, const QPointF &point, ulong timestamp) override;
    bool handleMove(QQuickItem* item, const QPointF &point, ulong timestamp) override;
    bool handleRelease(QQuickItem* item, const QPointF &point, ulong timestamp) override;
    void handleUngrab() override;

    bool prepareEnterTransition() override;
    bool prepareExitTransition() override;

    bool setEdge(Qt::Edge edge);

    Qt::Edge edge = Qt::LeftEdge;
    qreal offset = 0;
    qreal position = 0;
    qreal dragMargin = 0;
    QQuickVelocityCalculator velocityCalculator;
};

QT_END_NAMESPACE

#endif // QQUICKDRAWER_P_P_H
