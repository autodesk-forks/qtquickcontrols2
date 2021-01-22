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

#include "qquickmenubaritem_p.h"
#include "qquickmenubaritem_p_p.h"
#include "qquickmenubar_p.h"
#include "qquickmenu_p.h"

QT_BEGIN_NAMESPACE

/*!
    \qmltype MenuBarItem
    \inherits AbstractButton
//!     \instantiates QQuickMenuBarItem
    \inqmlmodule QtQuick.Controls
    \since 5.10
    \ingroup qtquickcontrols2-menus
    \brief Presents a drop-down menu within a MenuBar.

    MenuBarItem presents a Menu within a MenuBar. The respective drop-down menu
    is shown when a MenuBarItem is \l triggered via keyboard, mouse, or touch.

    \image qtquickcontrols2-menubar.png

    MenuBarItem is used as a default \l {MenuBar::}{delegate} type for MenuBar.
    Notice that it is not necessary to declare MenuBarItem instances by hand when
    using MenuBar. It is sufficient to declare Menu instances as children of the
    MenuBar and the respective items are created automatically.

    \sa {Customizing MenuBar}, MenuBar, {Menu Controls}
*/

/*!
    \qmlsignal void QtQuick.Controls::MenuBarItem::triggered()

    This signal is emitted when the menu bar item is triggered by the user.
*/

void QQuickMenuBarItemPrivate::setMenuBar(QQuickMenuBar *newMenuBar)
{
    Q_Q(QQuickMenuBarItem);
    if (menuBar == newMenuBar)
        return;

    menuBar = newMenuBar;
    emit q->menuBarChanged();
}

QQuickMenuBarItem::QQuickMenuBarItem(QQuickItem *parent)
    : QQuickAbstractButton(*(new QQuickMenuBarItemPrivate), parent)
{
    setFocusPolicy(Qt::NoFocus);
    connect(this, &QQuickAbstractButton::clicked, this, &QQuickMenuBarItem::triggered);
}

/*!
    \qmlproperty Menu QtQuick.Controls::MenuBarItem::menuBar
    \readonly

    This property holds the menu bar that contains this item,
    or \c null if the item is not in a menu bar.
*/
QQuickMenuBar *QQuickMenuBarItem::menuBar() const
{
    Q_D(const QQuickMenuBarItem);
    return d->menuBar;
}

/*!
    \qmlproperty Menu QtQuick.Controls::MenuBarItem::menu

    This property holds the menu that this item presents in a
    menu bar, or \c null if this item does not have a menu.
*/
QQuickMenu *QQuickMenuBarItem::menu() const
{
    Q_D(const QQuickMenuBarItem);
    return d->menu;
}

void QQuickMenuBarItem::setMenu(QQuickMenu *menu)
{
    Q_D(QQuickMenuBarItem);
    if (d->menu == menu)
        return;

    if (d->menu)
        disconnect(d->menu, &QQuickMenu::titleChanged, this, &QQuickAbstractButton::setText);

    if (menu) {
        setText(menu->title());
        menu->setY(height());
        menu->setParentItem(this);
        menu->setClosePolicy(QQuickPopup::CloseOnEscape | QQuickPopup::CloseOnPressOutsideParent | QQuickPopup::CloseOnReleaseOutsideParent);
        connect(menu, &QQuickMenu::titleChanged, this, &QQuickAbstractButton::setText);
    }

    d->menu = menu;
    emit menuChanged();
}

/*!
    \qmlproperty bool QtQuick.Controls::MenuBarItem::highlighted

    This property holds whether the menu bar item is highlighted by the user.

    A menu bar item can be highlighted by mouse hover or keyboard navigation.

    The default value is \c false.
*/
bool QQuickMenuBarItem::isHighlighted() const
{
    Q_D(const QQuickMenuBarItem);
    return d->highlighted;
}

void QQuickMenuBarItem::setHighlighted(bool highlighted)
{
    Q_D(QQuickMenuBarItem);
    if (highlighted == d->highlighted)
        return;

    d->highlighted = highlighted;
    emit highlightedChanged();
}

void QQuickMenuBarItem::geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry)
{
    Q_D(QQuickMenuBarItem);
    QQuickAbstractButton::geometryChanged(newGeometry, oldGeometry);
    if (d->menu)
        d->menu->setY(newGeometry.height());
}

QFont QQuickMenuBarItem::defaultFont() const
{
    return QQuickTheme::font(QQuickTheme::MenuBar);
}

QPalette QQuickMenuBarItem::defaultPalette() const
{
    return QQuickTheme::palette(QQuickTheme::MenuBar);
}

#if QT_CONFIG(accessibility)
QAccessible::Role QQuickMenuBarItem::accessibleRole() const
{
    return QAccessible::MenuBar;
}
#endif

QT_END_NAMESPACE
