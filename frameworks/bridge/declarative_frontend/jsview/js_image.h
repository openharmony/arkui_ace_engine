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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_IMAGE_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_IMAGE_H

#include "core/components/image/image_component.h"
#include "core/components/image/image_event.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_interactable_view.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_abstract.h"

#ifdef USE_QUICKJS_ENGINE
#ifdef __cplusplus
extern "C" {
#endif
#include "third_party/quickjs/quickjs.h"
#ifdef __cplusplus
}
#endif
#endif

namespace OHOS::Ace::Framework {

class JSImage : public JSViewAbstract, public JSInteractableView {
    DECLARE_ACE_TYPE(JSImage, JSViewAbstract);

public:
    JSImage() = delete;
    JSImage(const std::string& src) : src_(src) {}
    ~JSImage();

    RefPtr<OHOS::Ace::Component> CreateSpecializedComponent() override;
    std::vector<RefPtr<OHOS::Ace::SingleChild>> CreateInteractableComponents() override;
    void HandleLoadImageSuccess(const BaseEventInfo& param);
    void HandleLoadImageFail(const BaseEventInfo& param);
    void SetAlt(std::string& value);
    void SetObjectFit(int32_t value);
    void SetMatchTextDirection(bool value);
    void SetFitOriginalSize(bool value);

#ifdef USE_QUICKJS_ENGINE
    void MarkGC(JSRuntime* rt, JS_MarkFunc* markFunc) override;
    void ReleaseRT(JSRuntime* rt) override;
    JSValue QjsOnComplete(JSContext* ctx, JSValueConst jsObject, int argc, JSValueConst* argv);
    JSValue QjsOnError(JSContext* ctx, JSValueConst jsObject, int argc, JSValueConst* argv);
#endif // USE_QUICKJS_ENGINE

#ifdef USE_V8_ENGINE
    void V8OnComplete(const v8::FunctionCallbackInfo<v8::Value>& args);
    void V8OnError(const v8::FunctionCallbackInfo<v8::Value>& args);
#endif // USE_V8_ENGINE

public:
    static void JSBind(BindingTarget globalObj);

#ifdef USE_QUICKJS_ENGINE
    static void QjsDestructor(JSRuntime* rt, JSImage* ptr);
    static void QjsGcMark(JSRuntime* rt, JSValueConst val, JS_MarkFunc* markFunc);
#endif // USE_QUICKJS_ENGINE

private:
    const std::string src_;
    std::string alt_;
    ImageFit objectFit_ = ImageFit::COVER;
    bool matchTextDirection_ = false;
    bool fitOriginalSize_ = false;

#ifdef USE_QUICKJS_ENGINE
    RefPtr<QJSEventFunction<LoadImageSuccessEvent, 2>> jsLoadSuccFunc_;
    RefPtr<QJSEventFunction<LoadImageFailEvent, 0>> jsLoadFailFunc_;
#endif // USE_QUICKJS_ENGINE

#ifdef USE_V8_ENGINE
    RefPtr<V8EventFunction<LoadImageSuccessEvent, 2>> jsLoadSuccFunc_;
    RefPtr<V8EventFunction<LoadImageFailEvent, 0>> jsLoadFailFunc_;
#endif // USE_V8_ENGINE
};

} // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_IMAGE_H
