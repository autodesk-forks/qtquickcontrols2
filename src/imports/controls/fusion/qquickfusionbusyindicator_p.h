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

#ifndef QQUICKFUSIONBUSYINDICATOR_P_H
#define QQUICKFUSIONBUSYINDICATOR_P_H

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

#include <QtGui/qcolor.h>
#include <QtQuick/qquickpainteditem.h>

QT_BEGIN_NAMESPACE

class QQuickFusionBusyIndicator : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor FINAL)
    Q_PROPERTY(bool running READ isRunning WRITE setRunning)

public:
    explicit QQuickFusionBusyIndicator(QQuickItem *parent = nullptr);

    QColor color() const;
    void setColor(const QColor &color);

    bool isRunning() const;
    void setRunning(bool running);

    void paint(QPainter *painter) override;

protected:
    void itemChange(ItemChange change, const ItemChangeData &data) override;

private:
    QColor m_color;
};

QT_END_NAMESPACE

#endif // QQUICKFUSIONBUSYINDICATOR_P_H
