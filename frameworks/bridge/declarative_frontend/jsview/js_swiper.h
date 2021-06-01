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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_SWIPER_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_SWIPER_H

#include "core/components/swiper/swiper_component.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_container_base.h"

namespace OHOS::Ace::Framework {

class JSSwiper : public JSContainerBase {
    DECLARE_ACE_TYPE(JSSwiper, JSContainerBase);

public:
    JSSwiper() = delete;
#ifdef USE_QUICKJS_ENGINE
    JSSwiper(const std::list<JSViewAbstract*>& children, std::list<JSValue> jsChildren);
#elif USE_V8_ENGINE
    JSSwiper(const std::list<JSViewAbstract*>& children,
        std::list<v8::Persistent<v8::Object, v8::CopyablePersistentTraits<v8::Object>>> jsChildren);
#endif

    ~JSSwiper();
    virtual void Destroy(JSViewAbstract* parentCustomView) override;
    static void JSBind(BindingTarget globalObj);

#ifdef USE_QUICKJS_ENGINE
    static JSValue ConstructorCallback(JSContext* ctx, JSValueConst new_target, int argc, JSValueConst* argv);
    static void QjsDestructor(JSRuntime* rt, JSSwiper* ptr);
    static void QjsGcMark(JSRuntime* rt, JSValueConst val, JS_MarkFunc* markFunc);
    static JSValue SetIndicatorStyle(JSContext* ctx, JSValueConst jsSwiper, int argc, JSValueConst* argv);
    void MarkGC(JSRuntime* rt, JS_MarkFunc* markFunc) override;
    void ReleaseRT(JSRuntime* rt) override;
#elif USE_V8_ENGINE
    static void ConstructorCallback(const v8::FunctionCallbackInfo<v8::Value>& args);
#endif

protected:
    RefPtr<OHOS::Ace::Component> CreateSpecializedComponent() override;
    std::vector<RefPtr<OHOS::Ace::SingleChild>> CreateInteractableComponents() override;
    void SetAutoplay(bool autoPlay);
    void SetDigital(bool digitalIndicator);
    void SetDuration(double duration);
    void SetIndex(uint32_t index);
    void SetInterval(double interval);
    void SetLoop(bool loop);
    void SetVertical(bool isVertical);
    void SetIndicator(bool showIndicator);
#ifdef USE_V8_ENGINE
    void SetIndicatorStyle(const v8::FunctionCallbackInfo<v8::Value>& info);
    void SetOnChange(const v8::FunctionCallbackInfo<v8::Value>& args);
#elif USE_QUICKJS_ENGINE
    JSValue SetOnChange(JSContext* ctx, JSValueConst this_value, int32_t argc, JSValueConst* argv);
#endif

private:
    void InitIndicatorStyle();
    void HandleChangeEvent(const BaseEventInfo& param);

    uint32_t index_ = DEFAULT_SWIPER_CURRENT_INDEX;
    double duration_ = DEFAULT_SWIPER_ANIMATION_DURATION;
    double autoPlayInterval_ = DEFAULT_SWIPER_AUTOPLAY_INTERVAL;
    bool autoPlay_ = false;
    bool digitalIndicator_ = false;
    bool loop_ = true;
    bool showIndicator_ = true;
    Axis axis_ = Axis::HORIZONTAL;
    // indicator
    RefPtr<SwiperIndicator> indicator_;
#ifdef USE_V8_ENGINE
    RefPtr<V8EventFunction<SwiperChangeEvent, 1>> onChangeFunc_;
#elif USE_QUICKJS_ENGINE
    RefPtr<QJSEventFunction<SwiperChangeEvent, 1>> onChangeFunc_;
#endif
};

} // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_SWIPER_H
