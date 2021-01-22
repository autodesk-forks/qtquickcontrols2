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

#include "qquickshortcutcontext_p_p.h"
#include "qquickoverlay_p_p.h"
#include "qquicktooltip_p.h"
#include "qquickpopup_p.h"
#include "qquickmenu_p.h"
#include "qquickmenubaritem_p.h"

#include <QtGui/qguiapplication.h>
#include <QtQuick/qquickrendercontrol.h>

QT_BEGIN_NAMESPACE

static bool isBlockedByPopup(QQuickItem *item)
{
    if (!item || !item->window())
        return false;

    QQuickOverlay *overlay = QQuickOverlay::overlay(item->window());
    const auto popups = QQuickOverlayPrivate::get(overlay)->stackingOrderPopups();
    for (QQuickPopup *popup : popups) {
        if (qobject_cast<QQuickToolTip *>(popup))
            continue; // ignore tooltips (QTBUG-60492)
        if (popup->isModal() || popup->closePolicy() & QQuickPopup::CloseOnEscape) {
            if (QQuickMenu *menu = qobject_cast<QQuickMenu *>(popup)) {
                if (qobject_cast<QQuickMenuBarItem *>(menu->parentItem()))
                    continue;
            }
            return item != popup->popupItem() && !popup->popupItem()->isAncestorOf(item);
        }
    }

    return false;
}

bool QQuickShortcutContext::matcher(QObject *obj, Qt::ShortcutContext context)
{
    QQuickItem *item = nullptr;
    switch (context) {
    case Qt::ApplicationShortcut:
        return true;
    case Qt::WindowShortcut:
        while (obj && !obj->isWindowType()) {
            item = qobject_cast<QQuickItem *>(obj);
            if (item && item->window()) {
                obj = item->window();
                break;
            } else if (QQuickPopup *popup = qobject_cast<QQuickPopup *>(obj)) {
                obj = popup->window();
                item = popup->popupItem();
                break;
            }
            obj = obj->parent();
        }
        if (QWindow *renderWindow = QQuickRenderControl::renderWindowFor(qobject_cast<QQuickWindow *>(obj)))
            obj = renderWindow;
        return obj && obj == QGuiApplication::focusWindow() && !isBlockedByPopup(item);
    default:
        return false;
    }
}

QT_END_NAMESPACE
