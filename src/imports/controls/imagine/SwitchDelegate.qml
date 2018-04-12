/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Quick Controls 2 module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL3$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPLv3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or later as published by the Free
** Software Foundation and appearing in the file LICENSE.GPL included in
** the packaging of this file. Please review the following information to
** ensure the GNU General Public License version 2.0 requirements will be
** met: http://www.gnu.org/licenses/gpl-2.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

import QtQuick 2.12
import QtQuick.Templates 2.5 as T
import QtQuick.Controls 2.5
import QtQuick.Controls.impl 2.5
import QtQuick.Controls.Imagine 2.5
import QtQuick.Controls.Imagine.impl 2.5

T.SwitchDelegate {
    id: control

    implicitWidth: Math.max(implicitBackgroundWidth,
                            implicitContentWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(implicitBackgroundHeight,
                             Math.max(implicitContentHeight,
                                      indicator ? indicator.implicitHeight : 0) + topPadding + bottomPadding)

    spacing: 12 // ###

    topPadding: background ? background.topPadding : 0
    leftPadding: background ? background.leftPadding : 0
    rightPadding: background ? background.rightPadding : 0
    bottomPadding: background ? background.bottomPadding : 0

    icon.width: 24
    icon.height: 24
    icon.color: control.palette.text

    indicator: NinePatchImage {
        x: text ? (control.mirrored ? control.leftPadding : control.width - width - control.rightPadding) : control.leftPadding + (control.availableWidth - width) / 2
        y: control.topPadding + (control.availableHeight - height) / 2
        width: Math.max(implicitWidth, handle.leftPadding && handle.rightPadding ? handle.implicitWidth : 2 * handle.implicitWidth)
        height: Math.max(implicitHeight, handle.implicitHeight)

        source: Imagine.url + "switchdelegate-indicator"
        NinePatchImageSelector on source {
            states: [
                {"disabled": !control.enabled},
                {"pressed": control.down},
                {"checked": control.checked},
                {"focused": control.visualFocus},
                {"highlighted": control.highlighted},
                {"mirrored": control.mirrored},
                {"hovered": control.hovered}
            ]
        }

        property NinePatchImage handle: NinePatchImage {
            readonly property real minPos: parent.leftPadding - leftPadding
            readonly property real maxPos: parent.width - width + rightPadding - parent.rightPadding
            readonly property real dragPos: control.visualPosition * parent.width - (width / 2)

            parent: control.indicator

            x: Math.max(minPos, Math.min(maxPos, control.visualPosition * parent.width - (width / 2)))
            y: (parent.height - height) / 2

            source: Imagine.url + "switchdelegate-handle"
            NinePatchImageSelector on source {
                states: [
                    {"disabled": !control.enabled},
                    {"pressed": control.down},
                    {"checked": control.checked},
                    {"focused": control.visualFocus},
                    {"highlighted": control.highlighted},
                    {"mirrored": control.mirrored},
                    {"hovered": control.hovered}
                ]
            }

            Behavior on x {
                enabled: !control.down
                SmoothedAnimation { velocity: 200 }
            }
        }
    }

    contentItem: IconLabel {
        leftPadding: control.mirrored ? control.indicator.width + control.spacing : 0
        rightPadding: !control.mirrored ? control.indicator.width + control.spacing : 0

        spacing: control.spacing
        mirrored: control.mirrored
        display: control.display
        alignment: control.display === IconLabel.IconOnly || control.display === IconLabel.TextUnderIcon ? Qt.AlignCenter : Qt.AlignLeft

        icon: control.icon
        text: control.text
        font: control.font
        color: control.palette.text
    }

    background: NinePatchImage {
        x: -leftInset; y: -topInset
        width: control.width + leftInset + rightInset
        height: control.height + topInset + bottomInset

        source: Imagine.url + "switchdelegate-background"
        NinePatchImageSelector on source {
            states: [
                {"disabled": !control.enabled},
                {"pressed": control.down},
                {"checked": control.checked},
                {"focused": control.visualFocus},
                {"highlighted": control.highlighted},
                {"mirrored": control.mirrored},
                {"hovered": control.hovered}
            ]
        }
    }
}
