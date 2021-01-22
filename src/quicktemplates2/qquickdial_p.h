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

#ifndef QQUICKDIAL_P_H
#define QQUICKDIAL_P_H

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

#include <QtCore/qvariant.h>
#include <QtQml/qqmlcomponent.h>
#include <QtQuickTemplates2/private/qquickcontrol_p.h>

QT_BEGIN_NAMESPACE

class QQuickDialAttached;
class QQuickDialPrivate;

class Q_QUICKTEMPLATES2_PRIVATE_EXPORT QQuickDial : public QQuickControl
{
    Q_OBJECT
    Q_PROPERTY(qreal from READ from WRITE setFrom NOTIFY fromChanged FINAL)
    Q_PROPERTY(qreal to READ to WRITE setTo NOTIFY toChanged FINAL)
    Q_PROPERTY(qreal value READ value WRITE setValue NOTIFY valueChanged FINAL)
    Q_PROPERTY(qreal position READ position NOTIFY positionChanged FINAL)
    Q_PROPERTY(qreal angle READ angle NOTIFY angleChanged FINAL)
    Q_PROPERTY(qreal stepSize READ stepSize WRITE setStepSize NOTIFY stepSizeChanged FINAL)
    Q_PROPERTY(SnapMode snapMode READ snapMode WRITE setSnapMode NOTIFY snapModeChanged FINAL)
    Q_PROPERTY(bool wrap READ wrap WRITE setWrap NOTIFY wrapChanged FINAL)
    Q_PROPERTY(bool pressed READ isPressed NOTIFY pressedChanged FINAL)
    Q_PROPERTY(QQuickItem *handle READ handle WRITE setHandle NOTIFY handleChanged FINAL)
    // 2.2 (Qt 5.9)
    Q_PROPERTY(bool live READ live WRITE setLive NOTIFY liveChanged FINAL REVISION 2)
    // 2.5 (Qt 5.12)
    Q_PROPERTY(InputMode inputMode READ inputMode WRITE setInputMode NOTIFY inputModeChanged FINAL REVISION 5)
    Q_CLASSINFO("DeferredPropertyNames", "background,handle")

public:
    explicit QQuickDial(QQuickItem *parent = nullptr);

    qreal from() const;
    void setFrom(qreal from);

    qreal to() const;
    void setTo(qreal to);

    qreal value() const;
    void setValue(qreal value);

    qreal position() const;

    qreal angle() const;

    qreal stepSize() const;
    void setStepSize(qreal step);

    enum SnapMode {
        NoSnap,
        SnapAlways,
        SnapOnRelease
    };
    Q_ENUM(SnapMode)

    SnapMode snapMode() const;
    void setSnapMode(SnapMode mode);

    enum InputMode {
        Circular,
        Horizontal,
        Vertical,
    };
    Q_ENUM(InputMode)

    bool wrap() const;
    void setWrap(bool wrap);

    bool isPressed() const;
    void setPressed(bool pressed);

    QQuickItem *handle() const;
    void setHandle(QQuickItem *handle);

    // 2.2 (Qt 5.9)
    bool live() const;
    void setLive(bool live);

    // 2.5 (Qt 5.12)
    InputMode inputMode() const;
    void setInputMode(InputMode mode);

public Q_SLOTS:
    void increase();
    void decrease();

Q_SIGNALS:
    void fromChanged();
    void toChanged();
    void valueChanged();
    void positionChanged();
    void angleChanged();
    void stepSizeChanged();
    void snapModeChanged();
    void wrapChanged();
    void pressedChanged();
    void handleChanged();
    // 2.2 (Qt 5.9)
    Q_REVISION(2) void moved();
    Q_REVISION(2) void liveChanged();
    // 2.5 (Qt 5.12)
    Q_REVISION(5) void inputModeChanged();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
#if QT_CONFIG(quicktemplates2_multitouch)
    void touchEvent(QTouchEvent *event) override;
#endif
#if QT_CONFIG(wheelevent)
    void wheelEvent(QWheelEvent *event) override;
#endif

    void mirrorChange() override;
    void componentComplete() override;

#if QT_CONFIG(accessibility)
    void accessibilityActiveChanged(bool active) override;
    QAccessible::Role accessibleRole() const override;
#endif

private:
    Q_DISABLE_COPY(QQuickDial)
    Q_DECLARE_PRIVATE(QQuickDial)
};

QT_END_NAMESPACE

QML_DECLARE_TYPE(QQuickDial)

#endif // QQUICKDIAL_P_H
