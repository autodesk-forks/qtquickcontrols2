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

#include "qquickstacktransition_p_p.h"
#include "qquickstackelement_p_p.h"
#include "qquickstackview_p_p.h"

QT_BEGIN_NAMESPACE

static QQuickStackTransition exitTransition(QQuickStackView::Operation operation, QQuickStackElement *element, QQuickStackView *view)
{
    QQuickStackTransition st;
    st.status = QQuickStackView::Deactivating;
    st.element = element;

    const QQuickItemViewTransitioner *transitioner = QQuickStackViewPrivate::get(view)->transitioner;

    switch (operation) {
    case QQuickStackView::PushTransition:
        st.type = QQuickItemViewTransitioner::AddTransition;
        if (transitioner)
            st.transition = transitioner->addDisplacedTransition;
        break;
    case QQuickStackView::ReplaceTransition:
        st.type = QQuickItemViewTransitioner::MoveTransition;
        if (transitioner)
            st.transition = transitioner->moveDisplacedTransition;
        break;
    case QQuickStackView::PopTransition:
        st.target = true;
        st.type = QQuickItemViewTransitioner::RemoveTransition;
        st.viewBounds = view->boundingRect();
        if (transitioner)
            st.transition = transitioner->removeTransition;
        break;
    default:
        Q_UNREACHABLE();
        break;
    }

    return st;
}

static QQuickStackTransition enterTransition(QQuickStackView::Operation operation, QQuickStackElement *element, QQuickStackView *view)
{
    QQuickStackTransition st;
    st.status = QQuickStackView::Activating;
    st.element = element;

    const QQuickItemViewTransitioner *transitioner = QQuickStackViewPrivate::get(view)->transitioner;

    switch (operation) {
    case QQuickStackView::PushTransition:
        st.target = true;
        st.type = QQuickItemViewTransitioner::AddTransition;
        st.viewBounds = view->boundingRect();
        if (transitioner)
            st.transition = transitioner->addTransition;
        break;
    case QQuickStackView::ReplaceTransition:
        st.target = true;
        st.type = QQuickItemViewTransitioner::MoveTransition;
        st.viewBounds = view->boundingRect();
        if (transitioner)
            st.transition = transitioner->moveTransition;
        break;
    case QQuickStackView::PopTransition:
        st.type = QQuickItemViewTransitioner::RemoveTransition;
        if (transitioner)
            st.transition = transitioner->removeDisplacedTransition;
        break;
    default:
        Q_UNREACHABLE();
        break;
    }

    return st;
}

static QQuickStackView::Operation operationTransition(QQuickStackView::Operation operation, QQuickStackView::Operation transition)
{
    if (operation == QQuickStackView::Immediate || operation == QQuickStackView::Transition)
        return transition;
    return operation;
}

QQuickStackTransition QQuickStackTransition::popExit(QQuickStackView::Operation operation, QQuickStackElement *element, QQuickStackView *view)
{
    return exitTransition(operationTransition(operation, QQuickStackView::PopTransition), element, view);
}

QQuickStackTransition QQuickStackTransition::popEnter(QQuickStackView::Operation operation, QQuickStackElement *element, QQuickStackView *view)
{
    return enterTransition(operationTransition(operation, QQuickStackView::PopTransition), element, view);
}

QQuickStackTransition QQuickStackTransition::pushExit(QQuickStackView::Operation operation, QQuickStackElement *element, QQuickStackView *view)
{
    return exitTransition(operationTransition(operation, QQuickStackView::PushTransition), element, view);
}

QQuickStackTransition QQuickStackTransition::pushEnter(QQuickStackView::Operation operation, QQuickStackElement *element, QQuickStackView *view)
{
    return enterTransition(operationTransition(operation, QQuickStackView::PushTransition), element, view);
}

QQuickStackTransition QQuickStackTransition::replaceExit(QQuickStackView::Operation operation, QQuickStackElement *element, QQuickStackView *view)
{
    return exitTransition(operationTransition(operation, QQuickStackView::ReplaceTransition), element, view);
}

QQuickStackTransition QQuickStackTransition::replaceEnter(QQuickStackView::Operation operation, QQuickStackElement *element, QQuickStackView *view)
{
    return enterTransition(operationTransition(operation, QQuickStackView::ReplaceTransition), element, view);
}

QT_END_NAMESPACE
