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

#ifndef QQUICKDIALOGBUTTONBOX_P_P_H
#define QQUICKDIALOGBUTTONBOX_P_P_H

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

#include <QtQuickTemplates2/private/qquickcontainer_p_p.h>
#include <QtQuickTemplates2/private/qquickdialogbuttonbox_p.h>

QT_BEGIN_NAMESPACE

class QQuickDialogButtonBoxPrivate : public QQuickContainerPrivate
{
    Q_DECLARE_PUBLIC(QQuickDialogButtonBox)

public:
    static QQuickDialogButtonBoxPrivate *get(QQuickDialogButtonBox *box)
    {
        return box->d_func();
    }

    void itemImplicitWidthChanged(QQuickItem *item) override;
    void itemImplicitHeightChanged(QQuickItem *item) override;

    void resizeContent() override;

    void updateLayout();

    qreal getContentWidth() const override;
    qreal getContentHeight() const override;

    void handleClick();

    QQuickAbstractButton *createStandardButton(QPlatformDialogHelper::StandardButton button);
    void removeStandardButtons();

    void updateLanguage();

    Qt::Alignment alignment;
    QQuickDialogButtonBox::Position position = QQuickDialogButtonBox::Footer;
    QPlatformDialogHelper::StandardButtons standardButtons = QPlatformDialogHelper::NoButton;
    QPlatformDialogHelper::ButtonLayout buttonLayout = QPlatformDialogHelper::UnknownLayout;
    QQmlComponent *delegate = nullptr;
};

class QQuickDialogButtonBoxAttachedPrivate : public QObjectPrivate
{
    Q_DECLARE_PUBLIC(QQuickDialogButtonBoxAttached)

public:
    static QQuickDialogButtonBoxAttachedPrivate *get(QQuickDialogButtonBoxAttached *q)
    {
        return q->d_func();
    }

    void setButtonBox(QQuickDialogButtonBox *box);

    QQuickDialogButtonBox *buttonBox = nullptr;
    QPlatformDialogHelper::ButtonRole buttonRole = QPlatformDialogHelper::InvalidRole;
    QPlatformDialogHelper::StandardButton standardButton = QPlatformDialogHelper::NoButton;
};

QT_END_NAMESPACE

#endif // QQUICKDIALOGBUTTONBOX_P_P_H
