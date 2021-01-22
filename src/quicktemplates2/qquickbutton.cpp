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

#include "qquickbutton_p.h"
#include "qquickbutton_p_p.h"

#include <QtGui/qpa/qplatformtheme.h>

QT_BEGIN_NAMESPACE

/*!
    \qmltype Button
    \inherits AbstractButton
//!     \instantiates QQuickButton
    \inqmlmodule QtQuick.Controls
    \since 5.7
    \ingroup qtquickcontrols2-buttons
    \brief Push-button that can be clicked to perform a command or answer a question.

    \image qtquickcontrols2-button.gif

    Button presents a push-button control that can be pushed or clicked by
    the user. Buttons are normally used to perform an action, or to answer
    a question. Typical buttons are \e OK, \e Apply, \e Cancel, \e Close,
    \e Yes, \e No, and \e Help.

    Button inherits its API from AbstractButton. For instance, you can set
    \l {AbstractButton::text}{text}, display an \l {Icons in Qt Quick Controls}{icon},
    and react to \l {AbstractButton::clicked}{clicks} using the AbstractButton API.

    A button emits the signal \l {AbstractButton::}{clicked()} when it is activated by the user.
    Connect to this signal to perform the button's action. Buttons also
    provide the signals \l {AbstractButton::}{canceled()}, \l {AbstractButton::}{doubleClicked()}, \l {AbstractButton::}{pressed()},
    \l {AbstractButton::}{released()} and \l {AbstractButton::}{pressAndHold()} for long presses.

    See the snippet below on how to connect to the button's signals.

    \code
    RowLayout {
        Button {
            text: "Ok"
            onClicked: model.submit()
        }
        Button {
            text: "Cancel"
            onClicked: model.revert()
        }
    }
    \endcode

    \sa {Customizing Button}, {Button Controls}
*/

QQuickButton::QQuickButton(QQuickItem *parent)
    : QQuickAbstractButton(*(new QQuickButtonPrivate), parent)
{
}

QQuickButton::QQuickButton(QQuickButtonPrivate &dd, QQuickItem *parent)
    : QQuickAbstractButton(dd, parent)
{
}

QFont QQuickButton::defaultFont() const
{
    return QQuickTheme::font(QQuickTheme::Button);
}

QPalette QQuickButton::defaultPalette() const
{
    return QQuickTheme::palette(QQuickTheme::Button);
}

/*!
    \qmlproperty bool QtQuick.Controls::Button::highlighted

    This property holds whether the button is highlighted.

    \image qtquickcontrols2-button-highlighted.gif

    A button can be highlighted in order to draw the user's attention towards
    it. It has no effect on keyboard interaction.

    The default value is \c false.
*/
bool QQuickButton::isHighlighted() const
{
    Q_D(const QQuickButton);
    return d->highlighted;
}

void QQuickButton::setHighlighted(bool highlighted)
{
    Q_D(QQuickButton);
    if (highlighted == d->highlighted)
        return;

    d->highlighted = highlighted;
    emit highlightedChanged();
}

/*!
    \qmlproperty bool QtQuick.Controls::Button::flat

    This property holds whether the button is flat.

    \image qtquickcontrols2-button-flat.gif

    A flat button typically does not draw a background unless it is pressed or checked.

    The default value is \c false.
*/
bool QQuickButton::isFlat() const
{
    Q_D(const QQuickButton);
    return d->flat;
}

void QQuickButton::setFlat(bool flat)
{
    Q_D(QQuickButton);
    if (flat == d->flat)
        return;

    d->flat = flat;
    emit flatChanged();
}

QT_END_NAMESPACE
