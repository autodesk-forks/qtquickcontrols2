/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtQuick module of the Qt Toolkit.
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
**
**
**
****************************************************************************/

#ifndef QQUICKHEADERVIEW_P_H
#define QQUICKHEADERVIEW_P_H

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

#include <private/qquicktableview_p.h>
#include <private/qtquicktemplates2global_p.h>

QT_BEGIN_NAMESPACE

class QQuickHeaderViewBase;
class QQuickHeaderViewBasePrivate;
class Q_QUICKTEMPLATES2_PRIVATE_EXPORT QQuickHeaderViewBase : public QQuickTableView
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(QQuickHeaderViewBase)
    Q_PROPERTY(QString textRole READ textRole WRITE setTextRole NOTIFY textRoleChanged FINAL)

public:
    explicit QQuickHeaderViewBase(Qt::Orientation orient, QQuickItem *parent = nullptr);
    ~QQuickHeaderViewBase();

    QString textRole() const;
    void setTextRole(const QString &role);

protected:
    QQuickHeaderViewBase(QQuickHeaderViewBasePrivate &dd, QQuickItem *parent);

Q_SIGNALS:
    void textRoleChanged();

private:
    Q_DISABLE_COPY(QQuickHeaderViewBase)
    friend class QQuickHorizontalHeaderView;
    friend class QQuickVerticalHeaderView;
};

class QQuickHorizontalHeaderViewPrivate;
class Q_QUICKTEMPLATES2_PRIVATE_EXPORT QQuickHorizontalHeaderView : public QQuickHeaderViewBase
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(QQuickHorizontalHeaderView)

public:
    QQuickHorizontalHeaderView(QQuickItem *parent = nullptr);
    ~QQuickHorizontalHeaderView() override;

protected:
    QQuickHorizontalHeaderView(QQuickHorizontalHeaderViewPrivate &dd, QQuickItem *parent);

private:
    Q_DISABLE_COPY(QQuickHorizontalHeaderView)
};

class QQuickVerticalHeaderViewPrivate;
class Q_QUICKTEMPLATES2_PRIVATE_EXPORT QQuickVerticalHeaderView : public QQuickHeaderViewBase
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(QQuickVerticalHeaderView)

public:
    QQuickVerticalHeaderView(QQuickItem *parent = nullptr);
    ~QQuickVerticalHeaderView() override;

protected:
    QQuickVerticalHeaderView(QQuickVerticalHeaderViewPrivate &dd, QQuickItem *parent);

private:
    Q_DISABLE_COPY(QQuickVerticalHeaderView)
};

QT_END_NAMESPACE

QML_DECLARE_TYPE(QQuickHorizontalHeaderView)
QML_DECLARE_TYPE(QQuickVerticalHeaderView)

#endif // QQUICKHEADERVIEW_P_H
