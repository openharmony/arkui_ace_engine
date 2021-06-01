/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "frameworks/bridge/declarative_frontend/engine/quickjs/functions/qjs_view_function.h"

#include "base/log/log.h"
#include "frameworks/bridge/declarative_frontend/engine/quickjs/qjs_declarative_engine_instance.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_register.h"
#include "frameworks/bridge/js_frontend/engine/quickjs/qjs_utils.h"

namespace OHOS::Ace::Framework {

QJSViewFunction::QJSViewFunction(JSContext* ctx, JSValue jsObject, JSValue jsFunction)
    : QJSFunction(ctx, jsObject, JS_UNDEFINED), jsRenderResult_(JS_NULL)
{
    LOGD("Create: QJSViewFunction");

    QJSContext::Scope scope(ctx);

    JSAtom appearProp = JS_NewAtom(ctx, "aboutToAppear");
    JSValue jsAppearFunction = JS_GetProperty(ctx, jsObject, appearProp);
    if (JS_IsFunction(ctx, jsAppearFunction)) {
        jsAppearFunction_ = jsAppearFunction;
    }
    JS_FreeAtom(ctx, appearProp);

    JSAtom disappearProp = JS_NewAtom(ctx, "aboutToDisappear");
    JSValue jsDisappearFunction = JS_GetProperty(ctx, jsObject, disappearProp);
    if (JS_IsFunction(ctx, jsDisappearFunction)) {
        jsDisappearFunction_ = jsDisappearFunction;
    }
    JS_FreeAtom(ctx, disappearProp);
    JSAtom aboutToRenderProp = JS_NewAtom(ctx, "aboutToRender");
    JSValue jsAboutToRenderFunction = JS_GetProperty(ctx, jsObject, aboutToRenderProp);
    if (JS_IsFunction(ctx, jsAboutToRenderFunction)) {
        jsAboutToRenderFunc_ = jsAboutToRenderFunction;
    }
    JS_FreeAtom(ctx, aboutToRenderProp);

    JSAtom renderDoneProp = JS_NewAtom(ctx, "onRenderDone");
    JSValue jsRenderDoneFunction = JS_GetProperty(ctx, jsObject, renderDoneProp);
    if (JS_IsFunction(ctx, jsRenderDoneFunction)) {
        jsRenderDoneFunc_ = jsRenderDoneFunction;
    }
    JS_FreeAtom(ctx, renderDoneProp);
    jsRenderFunction_ = jsFunction;
}

QJSViewFunction::~QJSViewFunction()
{
    LOGD("Destroy: QJSViewFunction");
}

// FIXME: This need to return const value. So no accidental deletions of the returned view.
JSViewAbstract* QJSViewFunction::executeRender()
{
    /*
        Function might not be invoked in the JS file ever (like render())
        In that case, the returned value is neve referenced there so it never goes out of scope
        Because of that, the JSValue is never released.
        Since C++ produces the result value, it is the responsibility of this native object to release it.
    */

    ACE_SCOPED_TRACE("QJSViewFunction::executeRender(complete function)");

    ACE_DCHECK(ctx_ != nullptr);
    QJSContext::Scope scope(ctx_);

    jsFunction_ = jsRenderFunction_;
    jsRenderResult_ = QJSFunction::executeJS();
    jsFunction_ = JS_UNDEFINED;

    if (JS_IsException(jsRenderResult_)) {
        QjsUtils::JsStdDumpErrorAce(ctx_);
        JS_FreeValue(ctx_, jsRenderResult_);
        jsRenderResult_ = JS_NULL;
        return nullptr;
    }

    JSViewAbstract* view = static_cast<JSViewAbstract*>(UnwrapAny(jsRenderResult_));
    return view;
}

void QJSViewFunction::executeAppear()
{
    ACE_SCOPED_TRACE("QJSViewFunction::executeAppear(complete function)");

    ACE_DCHECK(ctx_ != nullptr);
    QJSContext::Scope scope(ctx_);

    if (!JS_IsNull(jsAppearFunction_)) {
        jsFunction_ = jsAppearFunction_;
        QJSFunction::executeJS();
        jsFunction_ = JS_UNDEFINED;
    } else {
        LOGD("View doesn't have aboutToAppear() method!");
    }
}

void QJSViewFunction::executeDisappear()
{
    ACE_SCOPED_TRACE("QJSViewFunction::executeDisappear(complete function)");

    ACE_DCHECK(ctx_ != nullptr);
    QJSContext::Scope scope(ctx_);

    if (!JS_IsNull(jsDisappearFunction_)) {
        jsFunction_ = jsDisappearFunction_;
        QJSFunction::executeJS();
        jsFunction_ = JS_UNDEFINED;
    } else {
        LOGD("View doesn't have aboutToDisappear() method!");
    }
}

void QJSViewFunction::executeAboutToRender()
{
    ACE_SCOPED_TRACE("QJSViewFunction::executeAboutToRender(complete function)");

    ACE_DCHECK(ctx_ != nullptr);
    QJSContext::Scope scope(ctx_);

    if (JS_IsFunction(ctx_, jsAboutToRenderFunc_)) {
        jsFunction_ = jsAboutToRenderFunc_;
        QJSFunction::executeJS();
        jsFunction_ = JS_UNDEFINED;
    }
}

void QJSViewFunction::executeOnRenderDone()
{
    ACE_SCOPED_TRACE("QJSViewFunction::executeOnRenderDone(complete function)");

    ACE_DCHECK(ctx_ != nullptr);
    QJSContext::Scope scope(ctx_);

    if (JS_IsFunction(ctx_, jsRenderDoneFunc_)) {
        jsFunction_ = jsRenderDoneFunc_;
        QJSFunction::executeJS();
        jsFunction_ = JS_UNDEFINED;
    }
}
void QJSViewFunction::MarkGC(JSRuntime* rt, JS_MarkFunc* markFunc)
{
    LOGD("QJSViewFunction(MarkGC): start");
    QJSFunction::MarkGC(rt, markFunc);
    if (!JS_IsNull(jsRenderResult_)) {
        JS_MarkValue(rt, jsRenderResult_, markFunc);
    }
    LOGD("QJSViewFunction(MarkGC): end");
}

void QJSViewFunction::ReleaseRT(JSRuntime* rt)
{
    LOGD("QJSViewFunction(release): start");
    QJSFunction::ReleaseRT(rt);

    if (!JS_IsNull(jsRenderResult_)) {
        JS_FreeValueRT(rt, jsRenderResult_);
    }
    ctx_ = nullptr;
    LOGD("QJSViewFunction(release): end");
}

void QJSViewFunction::Destroy(JSViewAbstract* parentCustomView)
{
    LOGD("QJSViewFunction::Destroy() start");

    if (!JS_IsNull(jsRenderResult_)) {
        JSViewAbstract* view = static_cast<JSViewAbstract*>(UnwrapAny(jsRenderResult_));

        if (view && !view->IsCustomView()) {
            view->Destroy(parentCustomView);
        }

        LOGD("Release previous view");
        JS_FreeValue(ctx_, jsRenderResult_);
        jsRenderResult_ = JS_NULL;
    }
    LOGD("QJSViewFunction::Destroy() end");
}

} // namespace OHOS::Ace::Framework
