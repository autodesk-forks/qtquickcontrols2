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

#ifndef QQUICKFUSIONDIAL_P_H
#define QQUICKFUSIONDIAL_P_H

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

#include <QtGui/qpalette.h>
#include <QtQuick/qquickpainteditem.h>

QT_BEGIN_NAMESPACE

class QQuickFusionDial : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(bool highlight READ highlight WRITE setHighlight FINAL)
    Q_PROPERTY(QPalette palette READ palette WRITE setPalette FINAL)

public:
    explicit QQuickFusionDial(QQuickItem *parent = nullptr);

    bool highlight() const;
    void setHighlight(bool highlight);

    QPalette palette() const;
    void setPalette(const QPalette &palette);

    void paint(QPainter *painter) override;

private:
    bool m_highlight = false;
    QPalette m_palette;
};

QT_END_NAMESPACE

#endif // QQUICKFUSIONDIAL_P_H
