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

#ifndef QQUICKDRAWER_P_H
#define QQUICKDRAWER_P_H

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

#include <QtQuickTemplates2/private/qquickpopup_p.h>

QT_BEGIN_NAMESPACE

class QQuickDrawerPrivate;

class Q_QUICKTEMPLATES2_PRIVATE_EXPORT QQuickDrawer : public QQuickPopup
{
    Q_OBJECT
    Q_PROPERTY(Qt::Edge edge READ edge WRITE setEdge NOTIFY edgeChanged FINAL)
    Q_PROPERTY(qreal position READ position WRITE setPosition NOTIFY positionChanged FINAL)
    Q_PROPERTY(qreal dragMargin READ dragMargin WRITE setDragMargin RESET resetDragMargin NOTIFY dragMarginChanged FINAL)
    // 2.2 (Qt 5.9)
    Q_PROPERTY(bool interactive READ isInteractive WRITE setInteractive NOTIFY interactiveChanged FINAL REVISION 2)

public:
    explicit QQuickDrawer(QObject *parent = nullptr);

    Qt::Edge edge() const;
    void setEdge(Qt::Edge edge);

    qreal position() const;
    void setPosition(qreal position);

    qreal dragMargin() const;
    void setDragMargin(qreal margin);
    void resetDragMargin();

    // 2.2 (Qt 5.9)
    bool isInteractive() const;
    void setInteractive(bool interactive);

Q_SIGNALS:
    void edgeChanged();
    void positionChanged();
    void dragMarginChanged();
    // 2.2 (Qt 5.9)
    Q_REVISION(2) void interactiveChanged();

protected:
    bool childMouseEventFilter(QQuickItem *child, QEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    bool overlayEvent(QQuickItem *item, QEvent *event) override;
#if QT_CONFIG(quicktemplates2_multitouch)
    void touchEvent(QTouchEvent *event) override;
#endif

    void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry) override;

private:
    Q_DISABLE_COPY(QQuickDrawer)
    Q_DECLARE_PRIVATE(QQuickDrawer)
};

QT_END_NAMESPACE

QML_DECLARE_TYPE(QQuickDrawer)

#endif // QQUICKDRAWER_P_H
