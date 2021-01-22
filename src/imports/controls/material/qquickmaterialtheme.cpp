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

#include "qquickmaterialtheme_p.h"
#include "qquickmaterialstyle_p.h"

#include <QtGui/qpa/qplatformdialoghelper.h>
#include <QtGui/qfont.h>
#include <QtGui/qfontinfo.h>
#include <QtQuickTemplates2/private/qquicktheme_p.h>

QT_BEGIN_NAMESPACE

void QQuickMaterialTheme::initialize(QQuickTheme *theme)
{
    QFont systemFont;
    QFont buttonFont;
    QFont toolTipFont;
    QFont itemViewFont;
    QFont listViewFont;
    QFont menuItemFont;
    QFont editorFont;

    QFont font;
    font.setFamily(QLatin1String("Roboto"));
    QString family = QFontInfo(font).family();

    if (family != QLatin1String("Roboto")) {
        font.setFamily(QLatin1String("Noto"));
        family = QFontInfo(font).family();
    }

    if (family == QLatin1String("Roboto") || family == QLatin1String("Noto")) {
        systemFont.setFamily(family);
        buttonFont.setFamily(family);
        toolTipFont.setFamily(family);
        itemViewFont.setFamily(family);
        listViewFont.setFamily(family);
        menuItemFont.setFamily(family);
        editorFont.setFamily(family);
    }

    const bool dense = QQuickMaterialStyle::variant() == QQuickMaterialStyle::Dense;
    systemFont.setPixelSize(dense ? 13 : 14);
    theme->setFont(QQuickTheme::System, systemFont);

    // https://material.io/guidelines/components/buttons.html#buttons-style
    buttonFont.setPixelSize(dense ? 13 : 14);
    buttonFont.setCapitalization(QFont::AllUppercase);
    buttonFont.setWeight(QFont::Medium);
    theme->setFont(QQuickTheme::Button, buttonFont);
    theme->setFont(QQuickTheme::TabBar, buttonFont);
    theme->setFont(QQuickTheme::ToolBar, buttonFont);

    // https://material.io/guidelines/components/tooltips.html
    toolTipFont.setPixelSize(dense ? 10 : 14);
    toolTipFont.setWeight(QFont::Medium);
    theme->setFont(QQuickTheme::ToolTip, toolTipFont);

    itemViewFont.setPixelSize(dense ? 13 : 14);
    itemViewFont.setWeight(QFont::Medium);
    theme->setFont(QQuickTheme::ItemView, itemViewFont);

    // https://material.io/guidelines/components/lists.html#lists-specs
    listViewFont.setPixelSize(dense ? 13 : 16);
    theme->setFont(QQuickTheme::ListView, listViewFont);

    menuItemFont.setPixelSize(dense ? 13 : 16);
    theme->setFont(QQuickTheme::Menu, menuItemFont);
    theme->setFont(QQuickTheme::MenuBar, menuItemFont);
    theme->setFont(QQuickTheme::ComboBox, menuItemFont);

    editorFont.setPixelSize(dense ? 13 : 16);
    theme->setFont(QQuickTheme::TextArea, editorFont);
    theme->setFont(QQuickTheme::TextField, editorFont);
    theme->setFont(QQuickTheme::SpinBox, editorFont);
}

QT_END_NAMESPACE
