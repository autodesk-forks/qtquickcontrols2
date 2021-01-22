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

#ifndef QQUICKUNIVERSALPROGRESSBAR_P_H
#define QQUICKUNIVERSALPROGRESSBAR_P_H

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
#include <QtQuick/qquickitem.h>

QT_BEGIN_NAMESPACE

class QQuickUniversalProgressBar : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor FINAL)
    Q_PROPERTY(qreal progress READ progress WRITE setProgress FINAL)
    Q_PROPERTY(bool indeterminate READ isIndeterminate WRITE setIndeterminate FINAL)

public:
    explicit QQuickUniversalProgressBar(QQuickItem *parent = nullptr);

    QColor color() const;
    void setColor(const QColor &color);

    qreal progress() const;
    void setProgress(qreal progress);

    bool isIndeterminate() const;
    void setIndeterminate(bool indeterminate);

protected:
    void itemChange(ItemChange change, const ItemChangeData &data) override;
    QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *) override;

private:
    QColor m_color = Qt::black;
    qreal m_progress = 0.0;
    bool m_indeterminate = false;
};

QT_END_NAMESPACE

QML_DECLARE_TYPE(QQuickUniversalProgressBar)

#endif // QQUICKUNIVERSALPROGRESSBAR_P_H
