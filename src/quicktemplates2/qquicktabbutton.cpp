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

#include "qquicktabbutton_p.h"
#include "qquickcontrol_p_p.h"

#include <QtGui/qpa/qplatformtheme.h>

QT_BEGIN_NAMESPACE

/*!
    \qmltype TabButton
    \inherits AbstractButton
//!     \instantiates QQuickTabButton
    \inqmlmodule QtQuick.Controls
    \since 5.7
    \ingroup qtquickcontrols2-navigation
    \brief Button with a look suitable for a TabBar.

    \image qtquickcontrols2-tabbutton.png

    TabButton is used in conjunction with a \l TabBar.

    \snippet qtquickcontrols2-tabbutton.qml 1

    TabButton inherits its API from AbstractButton. For instance, you can set
    \l {AbstractButton::text}{text}, and react to \l {AbstractButton::clicked}{clicks}
    using the AbstractButton API.

    \sa TabBar, {Customizing TabButton}, {Button Controls}, {Navigation Controls}
*/

QQuickTabButton::QQuickTabButton(QQuickItem *parent)
    : QQuickAbstractButton(parent)
{
    setCheckable(true);
    setAutoExclusive(true);
}

QFont QQuickTabButton::defaultFont() const
{
    return QQuickTheme::font(QQuickTheme::TabBar);
}

QPalette QQuickTabButton::defaultPalette() const
{
    return QQuickTheme::palette(QQuickTheme::TabBar);
}

#if QT_CONFIG(accessibility)
QAccessible::Role QQuickTabButton::accessibleRole() const
{
    return QAccessible::PageTab;
}
#endif

QT_END_NAMESPACE
