/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the test suite of the Qt Toolkit.
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

#include <QtTest/qtest.h>
#include "../shared/visualtestutil.h"

#include <QtGui/qpalette.h>
#include <QtGui/private/qguiapplication_p.h>
#include <QtQml/qqmlengine.h>
#include <QtQml/qqmlcomponent.h>
#include <QtQuick/private/qquickitem_p.h>
#include <QtQuickTemplates2/private/qquickapplicationwindow_p.h>
#include <QtQuickTemplates2/private/qquickcontrol_p.h>
#include <QtQuickTemplates2/private/qquickcontrol_p_p.h>
#include <QtQuickTemplates2/private/qquickpopup_p.h>
#include <QtQuickTemplates2/private/qquickpopup_p_p.h>
#include <QtQuickTemplates2/private/qquicktheme_p_p.h>
#include <QtQuickTemplates2/private/qquickbutton_p.h>

using namespace QQuickVisualTestUtil;

// Need a more descriptive failure message: QTBUG-87039
#define COMPARE_PALETTES(actualPalette, expectedPalette) \
    QVERIFY2(actualPalette == expectedPalette, \
        qPrintable(QString::fromLatin1("\n   Actual:    %1\n   Expected:  %2") \
            .arg(QDebug::toString(actualPalette)).arg(QDebug::toString(expectedPalette))));

class tst_palette : public QQmlDataTest
{
    Q_OBJECT

private slots:
    void initTestCase() override;

    void palette_data();
    void palette();

    void inheritance_data();
    void inheritance();

    void defaultPalette_data();
    void defaultPalette();

    void listView_data();
    void listView();

    void setDynamicallyCreatedPalette();
    void createBindings();
    void updateBindings();
};

void tst_palette::initTestCase()
{
    QQuickStyle::setStyle("Basic");

    QQmlDataTest::initTestCase();

    // Import QtQuick.Controls to initialize styles and themes so that
    // QQuickControlPrivate::themePalette() returns a palette from the
    // style's theme instead of the platform's theme.
    QQmlEngine engine;
    QQmlComponent component(&engine);
    component.setData("import QtQuick.Controls; Control { }", QUrl());
    delete component.create();
}

void tst_palette::palette_data()
{
    QTest::addColumn<QString>("testFile");
    QTest::addColumn<QPalette>("expectedPalette");

    QPalette defaultPalette = QQuickTheme::palette(QQuickTheme::System);
    defaultPalette.setColor(QPalette::Base, QColor("#efefef"));
    defaultPalette.setColor(QPalette::Text, QColor("#101010"));

    QTest::newRow("Control") << "palette-control-default.qml" << defaultPalette;
    QTest::newRow("AppWindow") << "palette-appwindow-default.qml" << defaultPalette;
    QTest::newRow("Popup") << "palette-popup-default.qml" << defaultPalette;

    QPalette customPalette;
    customPalette.setColor(QPalette::AlternateBase, QColor("aqua"));
    customPalette.setColor(QPalette::Base, QColor("azure"));
    customPalette.setColor(QPalette::BrightText, QColor("beige"));
    customPalette.setColor(QPalette::Button, QColor("bisque"));
    customPalette.setColor(QPalette::ButtonText, QColor("chocolate"));
    customPalette.setColor(QPalette::Dark, QColor("coral"));
    customPalette.setColor(QPalette::Highlight, QColor("crimson"));
    customPalette.setColor(QPalette::HighlightedText, QColor("fuchsia"));
    customPalette.setColor(QPalette::Light, QColor("gold"));
    customPalette.setColor(QPalette::Link, QColor("indigo"));
    customPalette.setColor(QPalette::LinkVisited, QColor("ivory"));
    customPalette.setColor(QPalette::Mid, QColor("khaki"));
    customPalette.setColor(QPalette::Midlight, QColor("lavender"));
    customPalette.setColor(QPalette::Shadow, QColor("linen"));
    customPalette.setColor(QPalette::Text, QColor("moccasin"));
    customPalette.setColor(QPalette::ToolTipBase, QColor("navy"));
    customPalette.setColor(QPalette::ToolTipText, QColor("orchid"));
    customPalette.setColor(QPalette::Window, QColor("plum"));
    customPalette.setColor(QPalette::WindowText, QColor("salmon"));

    QTest::newRow("Control:custom") << "palette-control-custom.qml" << customPalette;
    QTest::newRow("AppWindow:custom") << "palette-appwindow-custom.qml" << customPalette;
    QTest::newRow("Popup:custom") << "palette-popup-custom.qml" << customPalette;
}

void tst_palette::palette()
{
    QFETCH(QString, testFile);
    QFETCH(QPalette, expectedPalette);

    QQmlEngine engine;
    QQmlComponent component(&engine);
    component.loadUrl(testFileUrl(testFile));

    QScopedPointer<QObject> object(component.create());
    QVERIFY2(!object.isNull(), qPrintable(component.errorString()));

    QVariant var = object->property("palette");
    QVERIFY(var.isValid());

    COMPARE_PALETTES(var.value<QQuickPalette*>()->toQPalette(), expectedPalette);
}

void tst_palette::inheritance_data()
{
    QTest::addColumn<QString>("testFile");

    QTest::newRow("Control") << "inheritance-control.qml";
    QTest::newRow("Child Control") << "inheritance-childcontrol.qml";
    QTest::newRow("Dynamic Control") << "inheritance-dynamiccontrol.qml";
    QTest::newRow("Dynamic Child Control") << "inheritance-dynamicchildcontrol.qml";

    QTest::newRow("Popup") << "inheritance-popup.qml";
    QTest::newRow("Child Popup") << "inheritance-childpopup.qml";
    QTest::newRow("Dynamic Popup") << "inheritance-dynamicpopup.qml";
    QTest::newRow("Dynamic Child Popup") << "inheritance-dynamicchildpopup.qml";
}

void tst_palette::inheritance()
{
    QFETCH(QString, testFile);

    QQmlEngine engine;
    QQmlComponent component(&engine);
    component.loadUrl(testFileUrl(testFile));

    QScopedPointer<QQuickApplicationWindow> window(qobject_cast<QQuickApplicationWindow *>(component.create()));
    QVERIFY2(!window.isNull(), qPrintable(component.errorString()));

    QObject *control = window->property("control").value<QObject *>();
    QObject *child = window->property("child").value<QObject *>();
    QObject *grandChild = window->property("grandChild").value<QObject *>();
    QVERIFY(control && child && grandChild);

    QPalette defaultPalette = QQuickTheme::palette(QQuickTheme::System);
    defaultPalette.setColor(QPalette::Base, QColor("#efefef"));
    defaultPalette.setColor(QPalette::Text, QColor("#101010"));

    auto windowPalette = QQuickWindowPrivate::get(window.get())->palette();

    QCOMPARE(windowPalette->toQPalette(), defaultPalette);

    auto controlPalette = control->property("palette").value<QQuickPalette*>();
    auto childPalette = child->property("palette").value<QQuickPalette*>();
    auto grandChildPalette = grandChild->property("palette").value<QQuickPalette*>();
    QVERIFY(controlPalette && childPalette && grandChildPalette);

    QCOMPARE(controlPalette->toQPalette(), defaultPalette);
    QCOMPARE(childPalette->toQPalette(), defaultPalette);
    QCOMPARE(grandChildPalette->toQPalette(), defaultPalette);

    childPalette->setBase(Qt::red);
    childPalette->setText(Qt::green);
    childPalette->setButton(Qt::blue);

    QCOMPARE(childPalette->base(), grandChildPalette->base());
    QCOMPARE(childPalette->text(), grandChildPalette->text());
    QCOMPARE(childPalette->button(), grandChildPalette->button());

    windowPalette->setWindow(Qt::gray);
    QCOMPARE(controlPalette->window(), windowPalette->window());

    childPalette->setWindow(Qt::red);
    QCOMPARE(childPalette->window(), Qt::red);

    grandChildPalette->setWindow(Qt::blue);
    QCOMPARE(grandChildPalette->window(), Qt::blue);

    auto childMo = child->metaObject();
    childMo->property(childMo->indexOfProperty("palette")).reset(child);
    QCOMPARE(childPalette->window(), windowPalette->window());
    QCOMPARE(grandChildPalette->window(), Qt::blue);

    auto grandChildMo = grandChild->metaObject();
    grandChildMo->property(grandChildMo->indexOfProperty("palette")).reset(grandChild);
    QCOMPARE(grandChildPalette->window(), windowPalette->window());
}

class TestTheme : public QQuickTheme
{
public:
    static const uint NPalettes = QQuickTheme::Tumbler + 1;

    TestTheme()
    {
        for (uint i = 0; i < NPalettes; ++i)
            setPalette(static_cast<Scope>(i), QPalette(QColor::fromRgb(i)));
    }
};

Q_DECLARE_METATYPE(QQuickTheme::Scope)

void tst_palette::defaultPalette_data()
{
    QTest::addColumn<QString>("control");
    QTest::addColumn<QQuickTheme::Scope>("scope");

    QTest::newRow("AbstractButton") << "AbstractButton" << QQuickTheme::System;
    QTest::newRow("ApplicationWindow") << "ApplicationWindow" << QQuickTheme::System;
    QTest::newRow("Button") << "Button" << QQuickTheme::Button;
    QTest::newRow("CheckBox") << "CheckBox" << QQuickTheme::CheckBox;
    QTest::newRow("CheckDelegate") << "CheckDelegate" << QQuickTheme::ListView;
    QTest::newRow("ComboBox") << "ComboBox" << QQuickTheme::ComboBox;
    QTest::newRow("Container") << "Container" << QQuickTheme::System;
    QTest::newRow("Control") << "Control" << QQuickTheme::System;
    QTest::newRow("Dial") << "Dial" << QQuickTheme::System;
    QTest::newRow("Dialog") << "Dialog" << QQuickTheme::System;
    QTest::newRow("DialogButtonBox") << "DialogButtonBox" << QQuickTheme::System;
    QTest::newRow("Drawer") << "Drawer" << QQuickTheme::System;
    QTest::newRow("Frame") << "Frame" << QQuickTheme::System;
    QTest::newRow("GroupBox") << "GroupBox" << QQuickTheme::GroupBox;
    QTest::newRow("ItemDelegate") << "ItemDelegate" << QQuickTheme::ItemView;
    QTest::newRow("Label") << "Label" << QQuickTheme::Label;
    QTest::newRow("Menu") << "Menu" << QQuickTheme::Menu;
    QTest::newRow("MenuItem") << "MenuItem" << QQuickTheme::Menu;
    QTest::newRow("MenuSeparator") << "MenuSeparator" << QQuickTheme::Menu;
    QTest::newRow("Page") << "Page" << QQuickTheme::System;
    QTest::newRow("Pane") << "Pane" << QQuickTheme::System;
    QTest::newRow("Popup") << "Popup" << QQuickTheme::System;
    QTest::newRow("ProgressBar") << "ProgressBar" << QQuickTheme::System;
    QTest::newRow("RadioButton") << "RadioButton" << QQuickTheme::RadioButton;
    QTest::newRow("RadioDelegate") << "RadioDelegate" << QQuickTheme::ListView;
    QTest::newRow("RangeSlider") << "RangeSlider" << QQuickTheme::System;
    QTest::newRow("RoundButton") << "RoundButton" << QQuickTheme::Button;
    QTest::newRow("ScrollBar") << "ScrollBar" << QQuickTheme::System;
    QTest::newRow("ScrollIndicator") << "ScrollIndicator" << QQuickTheme::System;
    QTest::newRow("Slider") << "Slider" << QQuickTheme::System;
    QTest::newRow("SpinBox") << "SpinBox" << QQuickTheme::SpinBox;
    QTest::newRow("SwipeDelegate") << "SwipeDelegate" << QQuickTheme::ListView;
    QTest::newRow("Switch") << "Switch" << QQuickTheme::Switch;
    QTest::newRow("SwitchDelegate") << "SwitchDelegate" << QQuickTheme::ListView;
    QTest::newRow("TabBar") << "TabBar" << QQuickTheme::TabBar;
    QTest::newRow("TabButton") << "TabButton" << QQuickTheme::TabBar;
    QTest::newRow("TextArea") << "TextArea" << QQuickTheme::TextArea;
    QTest::newRow("TextField") << "TextField" << QQuickTheme::TextField;
    QTest::newRow("ToolBar") << "ToolBar" << QQuickTheme::ToolBar;
    QTest::newRow("ToolButton") << "ToolButton" << QQuickTheme::ToolBar;
    QTest::newRow("ToolSeparator") << "ToolSeparator" << QQuickTheme::ToolBar;
    QTest::newRow("ToolTip") << "ToolTip" << QQuickTheme::ToolTip;
    QTest::newRow("Tumbler") << "Tumbler" << QQuickTheme::Tumbler;
}

void tst_palette::defaultPalette()
{
    QFETCH(QString, control);
    QFETCH(QQuickTheme::Scope, scope);

    QQmlEngine engine;
    QQmlComponent component(&engine);
    component.setData(QString("import QtQuick.Controls; %1 { }").arg(control).toUtf8(), QUrl());

    // The call to setData() above causes QQuickBasicTheme to be set as the current theme,
    // so we must make sure we only set our theme afterwards.
    std::unique_ptr<QQuickTheme> oldTheme(QQuickThemePrivate::instance.release());
    QQuickThemePrivate::instance.reset(new TestTheme);

    QScopedPointer<QObject> object(component.create());
    QVERIFY2(!object.isNull(), qPrintable(component.errorString()));

    QVariant var = object->property("palette");
    QVERIFY(var.isValid());

    QPalette expectedPalette = QQuickTheme::palette(scope);
    auto actualPalette = var.value<QQuickPalette*>();
    QVERIFY(actualPalette);
    QCOMPARE(actualPalette->toQPalette(), expectedPalette);

    QQuickThemePrivate::instance.reset(oldTheme.release());
}

void tst_palette::listView_data()
{
    QTest::addColumn<QString>("objectName");

    QTest::newRow("Control") << "control";
    QTest::newRow("Label") << "label";
    QTest::newRow("TextArea") << "textarea";
    QTest::newRow("TextField") << "textfield";
}

void tst_palette::listView()
{
    QFETCH(QString, objectName);

    QQmlEngine engine;
    QQmlComponent component(&engine);
    component.loadUrl(testFileUrl("listview.qml"));

    QScopedPointer<QQuickApplicationWindow> window(qobject_cast<QQuickApplicationWindow *>(component.create()));
    QVERIFY2(!window.isNull(), qPrintable(component.errorString()));

    window->show();
    QVERIFY(QTest::qWaitForWindowActive(window.data()));

    QQuickItem *listView = window->property("listView").value<QQuickItem *>();
    QVERIFY(listView);

    QQuickItem *contentItem = listView->property("contentItem").value<QQuickItem *>();
    QVERIFY(contentItem);

    QVERIFY(QMetaObject::invokeMethod(listView, "forceLayout"));

    QQuickItem *column = contentItem->childItems().value(0);
    QVERIFY(column);

    QQuickItem *control = column->property(objectName.toUtf8()).value<QQuickItem *>();
    QVERIFY(control);

    QCOMPARE(QQuickItemPrivate::get(control)->palette()->highlight(), Qt::red);
}

void tst_palette::setDynamicallyCreatedPalette()
{
    QQmlEngine engine;
    QQmlComponent component(&engine);
    component.loadUrl(testFileUrl("set-palette.qml"));

    QScopedPointer<QObject> object(component.create());
    QVERIFY2(!object.isNull(), qPrintable(component.errorString()));

    QVariant var = object->property("palette");
    QVERIFY(var.isValid());

    auto palette = var.value<QQuickPalette*>();
    QVERIFY(palette);

    QCOMPARE(palette->buttonText(), QColor("azure"));
    QCOMPARE(palette->button(), QColor("khaki"));

    QCOMPARE(palette->disabled()->buttonText(), QColor("lavender"));
    QCOMPARE(palette->disabled()->button(), QColor("coral"));
}

void tst_palette::createBindings()
{
    QQmlEngine engine;
    QQmlComponent component(&engine);
    component.loadUrl(testFileUrl("bindings.qml"));

    QScopedPointer<QObject> window(component.create());
    QVERIFY2(!window.isNull(), qPrintable(component.errorString()));

    auto disabledButton = window->property("disabledButton").value<QQuickButton*>();
    QVERIFY(disabledButton);

    auto enabledButton = window->property("enabledButton").value<QQuickButton*>();
    QVERIFY(enabledButton);

    QCOMPARE(QQuickItemPrivate::get(disabledButton)->palette()->button(), QColor("aqua"));
    QCOMPARE(QQuickItemPrivate::get(disabledButton)->palette()->buttonText(), QColor("azure"));

    QCOMPARE(QQuickItemPrivate::get(enabledButton)->palette()->button(), QColor("khaki"));
    QCOMPARE(QQuickItemPrivate::get(enabledButton)->palette()->buttonText(), QColor("bisque"));

    QCOMPARE(QQuickItemPrivate::get(enabledButton)->palette()->disabled()->button(), QColor("aqua"));
    QCOMPARE(QQuickItemPrivate::get(enabledButton)->palette()->disabled()->buttonText(), QColor("azure"));
}

void tst_palette::updateBindings()
{
    QQmlEngine engine;
    QQmlComponent component(&engine);
    component.loadUrl(testFileUrl("bindings.qml"));

    QScopedPointer<QObject> window(component.create());
    QVERIFY2(!window.isNull(), qPrintable(component.errorString()));

    auto disabledButton = window->property("disabledButton").value<QQuickButton*>();
    QVERIFY(disabledButton);

    auto enabledButton = window->property("enabledButton").value<QQuickButton*>();
    QVERIFY(enabledButton);

    QQuickItemPrivate::get(disabledButton)->palette()->disabled()->setButton(QColor("navy"));
    enabledButton->setEnabled(false);

    QCOMPARE(QQuickItemPrivate::get(enabledButton)->palette()->button(), QColor("navy"));
}

QTEST_MAIN(tst_palette)

#include "tst_palette.moc"
