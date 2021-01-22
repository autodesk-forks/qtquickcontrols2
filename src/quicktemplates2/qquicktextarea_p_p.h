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

#ifndef QQUICKTEXTAREA_P_P_H
#define QQUICKTEXTAREA_P_P_H

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

#include <QtQml/private/qlazilyallocated_p.h>
#include <QtQuick/private/qquicktextedit_p_p.h>
#include <QtQuick/private/qquickitemchangelistener_p.h>
#include <QtQuickTemplates2/private/qquickpresshandler_p_p.h>
#include <QtQuickTemplates2/private/qquickdeferredpointer_p_p.h>

#include <QtQuickTemplates2/private/qquicktextarea_p.h>

#if QT_CONFIG(accessibility)
#include <QtGui/qaccessible.h>
#endif

QT_BEGIN_NAMESPACE

class QQuickFlickable;

class QQuickTextAreaPrivate : public QQuickTextEditPrivate, public QQuickItemChangeListener
#if QT_CONFIG(accessibility)
    , public QAccessible::ActivationObserver
#endif
{
    Q_DECLARE_PUBLIC(QQuickTextArea)

public:
    QQuickTextAreaPrivate();
    ~QQuickTextAreaPrivate();

    static QQuickTextAreaPrivate *get(QQuickTextArea *item)
    {
        return static_cast<QQuickTextAreaPrivate *>(QObjectPrivate::get(item));
    }

    inline QMarginsF getInset() const { return QMarginsF(getLeftInset(), getTopInset(), getRightInset(), getBottomInset()); }
    inline qreal getTopInset() const { return extra.isAllocated() ? extra->topInset : 0; }
    inline qreal getLeftInset() const { return extra.isAllocated() ? extra->leftInset : 0; }
    inline qreal getRightInset() const { return extra.isAllocated() ? extra->rightInset : 0; }
    inline qreal getBottomInset() const { return extra.isAllocated() ? extra->bottomInset : 0; }

    void setTopInset(qreal value, bool reset = false);
    void setLeftInset(qreal value, bool reset = false);
    void setRightInset(qreal value, bool reset = false);
    void setBottomInset(qreal value, bool reset = false);

    void resizeBackground();

    void resolveFont();
    void inheritFont(const QFont &font);
    void updateFont(const QFont &font);
    inline void setFont_helper(const QFont &font) {
        if (sourceFont.resolve() == font.resolve() && sourceFont == font)
            return;
        updateFont(font);
    }

    void resolvePalette();
    void inheritPalette(const QPalette &palette);
    void updatePalette(const QPalette &palette);
    inline void setPalette_helper(const QPalette &palette) {
        if (resolvedPalette.resolve() == palette.resolve() && resolvedPalette == palette)
            return;
        updatePalette(palette);
    }

#if QT_CONFIG(quicktemplates2_hover)
    void updateHoverEnabled(bool h, bool e);
#endif

    void attachFlickable(QQuickFlickable *flickable);
    void detachFlickable();
    void ensureCursorVisible();
    void resizeFlickableControl();
    void resizeFlickableContent();

    void itemGeometryChanged(QQuickItem *item, QQuickGeometryChange change, const QRectF &diff) override;

    qreal getImplicitWidth() const override;
    qreal getImplicitHeight() const override;

    void implicitWidthChanged() override;
    void implicitHeightChanged() override;

    void readOnlyChanged(bool isReadOnly);

#if QT_CONFIG(accessibility)
    void accessibilityActiveChanged(bool active) override;
    QAccessible::Role accessibleRole() const override;
#endif

    void cancelBackground();
    void executeBackground(bool complete = false);

    void itemImplicitWidthChanged(QQuickItem *item) override;
    void itemImplicitHeightChanged(QQuickItem *item) override;
    void itemDestroyed(QQuickItem *item) override;

#if QT_CONFIG(quicktemplates2_hover)
    bool hovered = false;
    bool explicitHoverEnabled = false;
#endif

    struct ExtraData {
        bool hasTopInset = false;
        bool hasLeftInset = false;
        bool hasRightInset = false;
        bool hasBottomInset = false;
        bool hasBackgroundWidth = false;
        bool hasBackgroundHeight = false;
        qreal topInset = 0;
        qreal leftInset = 0;
        qreal rightInset = 0;
        qreal bottomInset = 0;
        QFont requestedFont;
        QPalette requestedPalette;
    };
    QLazilyAllocated<ExtraData> extra;

    bool resizingBackground = false;
    QPalette resolvedPalette;
    QQuickDeferredPointer<QQuickItem> background;
    QString placeholder;
    QColor placeholderColor;
    Qt::FocusReason focusReason = Qt::OtherFocusReason;
    QQuickPressHandler pressHandler;
    QQuickFlickable *flickable = nullptr;
};

QT_END_NAMESPACE

#endif // QQUICKTEXTAREA_P_P_H
