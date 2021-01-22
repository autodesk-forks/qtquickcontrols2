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

#include <QtQuickControls2/private/qquickstyleplugin_p.h>
#include <QtQml/qqml.h>

#include "qquickfusionbusyindicator_p.h"
#include "qquickfusiondial_p.h"
#include "qquickfusionknob_p.h"
#include "qquickfusionstyle_p.h"
#include "qquickfusiontheme_p.h"

QT_BEGIN_NAMESPACE

static QObject *styleSingleton(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);
    return new QQuickFusionStyle;
}

class QtQuickControls2FusionStylePlugin: public QQuickStylePlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

public:
    QtQuickControls2FusionStylePlugin(QObject *parent = nullptr);

    void registerTypes(const char *uri) override;

    QString name() const override;
    void initializeTheme(QQuickTheme *theme) override;
};

QtQuickControls2FusionStylePlugin::QtQuickControls2FusionStylePlugin(QObject *parent) : QQuickStylePlugin(parent)
{
}

void QtQuickControls2FusionStylePlugin::registerTypes(const char *uri)
{
    qmlRegisterModule(uri, 2, 3); // Qt 5.10->2.3
    qmlRegisterModule(uri, 2, QT_VERSION_MINOR); // Qt 5.12->2.12, 5.13->2.13...

    QByteArray import = QByteArray(uri) + ".impl";
    qmlRegisterModule(import, 2, QT_VERSION_MINOR); // Qt 5.12->2.12, 5.13->2.13...

    qmlRegisterSingletonType<QQuickFusionStyle>(import, 2, 3, "Fusion", styleSingleton);

    qmlRegisterType<QQuickFusionBusyIndicator>(import, 2, 3, "BusyIndicatorImpl");
    qmlRegisterType<QQuickFusionDial>(import, 2, 3, "DialImpl");
    qmlRegisterType<QQuickFusionKnob>(import, 2, 3, "KnobImpl");

    qmlRegisterType(resolvedUrl(QStringLiteral("ButtonPanel.qml")), import, 2, 3, "ButtonPanel");
    qmlRegisterType(resolvedUrl(QStringLiteral("CheckIndicator.qml")), import, 2, 3, "CheckIndicator");
    qmlRegisterType(resolvedUrl(QStringLiteral("RadioIndicator.qml")), import, 2, 3, "RadioIndicator");
    qmlRegisterType(resolvedUrl(QStringLiteral("SliderGroove.qml")), import, 2, 3, "SliderGroove");
    qmlRegisterType(resolvedUrl(QStringLiteral("SliderHandle.qml")), import, 2, 3, "SliderHandle");
    qmlRegisterType(resolvedUrl(QStringLiteral("SwitchIndicator.qml")), import, 2, 3, "SwitchIndicator");
}

QString QtQuickControls2FusionStylePlugin::name() const
{
    return QStringLiteral("Fusion");
}

void QtQuickControls2FusionStylePlugin::initializeTheme(QQuickTheme *theme)
{
    QQuickFusionTheme::initialize(theme);
}

QT_END_NAMESPACE

#include "qtquickcontrols2fusionstyleplugin.moc"
