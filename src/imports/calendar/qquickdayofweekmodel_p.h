/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Labs Calendar module of the Qt Toolkit.
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

#ifndef QQUICKDAYOFWEEKMODEL_P_H
#define QQUICKDAYOFWEEKMODEL_P_H

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

#include <QtCore/qabstractitemmodel.h>
#include <QtCore/qlocale.h>
#include <QtQml/qqml.h>

QT_BEGIN_NAMESPACE

class QQuickDayOfWeekModelPrivate;

class QQuickDayOfWeekModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QLocale locale READ locale WRITE setLocale NOTIFY localeChanged FINAL)
    Q_PROPERTY(int count READ rowCount CONSTANT FINAL)

public:
    explicit QQuickDayOfWeekModel(QObject *parent = nullptr);

    QLocale locale() const;
    void setLocale(const QLocale &locale);

    Q_INVOKABLE int dayAt(int index) const;

    enum {
        DayRole = Qt::UserRole + 1,
        LongNameRole,
        ShortNameRole,
        NarrowNameRole
    };

    QHash<int, QByteArray> roleNames() const override;
    QVariant data(const QModelIndex &index, int role) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

Q_SIGNALS:
    void localeChanged();

private:
    Q_DISABLE_COPY(QQuickDayOfWeekModel)
    Q_DECLARE_PRIVATE(QQuickDayOfWeekModel)
};

QT_END_NAMESPACE

QML_DECLARE_TYPE(QQuickDayOfWeekModel)

#endif // QQUICKDAYOFWEEKMODEL_P_H
