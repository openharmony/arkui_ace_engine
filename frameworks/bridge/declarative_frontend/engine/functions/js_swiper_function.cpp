/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/declarative_frontend/engine/functions/js_swiper_function.h"


namespace OHOS::Ace::Framework {
void JsSwiperContentTransitionProxy::JSBind(BindingTarget globalObj)
{
    JSClass<JsSwiperContentTransitionProxy>::Declare("SwiperContentTransitionProxy");
    JSClass<JsSwiperContentTransitionProxy>::CustomProperty(
        "selectedIndex", &JsSwiperContentTransitionProxy::GetSelectedIndex,
        &JsSwiperContentTransitionProxy::SetSelectedIndex);
    JSClass<JsSwiperContentTransitionProxy>::CustomProperty(
        "index", &JsSwiperContentTransitionProxy::GetIndex, &JsSwiperContentTransitionProxy::SetIndex);
    JSClass<JsSwiperContentTransitionProxy>::CustomProperty(
        "position", &JsSwiperContentTransitionProxy::GetPosition, &JsSwiperContentTransitionProxy::SetPosition);
    JSClass<JsSwiperContentTransitionProxy>::CustomProperty(
        "mainAxisLength", &JsSwiperContentTransitionProxy::GetMainAxisLength,
        &JsSwiperContentTransitionProxy::SetMainAxisLength);
    JSClass<JsSwiperContentTransitionProxy>::CustomMethod(
        "finishTransition", &JsSwiperContentTransitionProxy::FinishTransition);
    JSClass<JsSwiperContentTransitionProxy>::Bind(
        globalObj, &JsSwiperContentTransitionProxy::Constructor, &JsSwiperContentTransitionProxy::Destructor);
}

void JsSwiperContentTransitionProxy::SetSelectedIndex(const JSCallbackInfo& args)
{
    TAG_LOGD(AceLogTag::ACE_SWIPER, "SwiperContentTransitionProxy can not support set selectedIndex value.");
}

void JsSwiperContentTransitionProxy::GetSelectedIndex(const JSCallbackInfo& args)
{
    auto selectedIndex = 0;
    if (proxy_) {
        selectedIndex = proxy_->GetSelectedIndex();
    }
    auto fromRef = JSRef<JSVal>::Make(JSVal(ToJSValue(selectedIndex)));
    args.SetReturnValue(fromRef);
}

void JsSwiperContentTransitionProxy::SetIndex(const JSCallbackInfo& args)
{
    TAG_LOGD(AceLogTag::ACE_SWIPER, "SwiperContentTransitionProxy can not support set index value.");
}

void JsSwiperContentTransitionProxy::GetIndex(const JSCallbackInfo& args)
{
    auto index = 0;
    if (proxy_) {
        index = proxy_->GetIndex();
    }
    auto fromRef = JSRef<JSVal>::Make(JSVal(ToJSValue(index)));
    args.SetReturnValue(fromRef);
}

void JsSwiperContentTransitionProxy::SetPosition(const JSCallbackInfo& args)
{
    TAG_LOGD(AceLogTag::ACE_SWIPER, "SwiperContentTransitionProxy can not support set position value.");
}

void JsSwiperContentTransitionProxy::GetPosition(const JSCallbackInfo& args)
{
    auto position = 0.0f;
    if (proxy_) {
        position = proxy_->GetPosition();
    }
    auto toRef = JSRef<JSVal>::Make(JSVal(ToJSValue(position)));
    args.SetReturnValue(toRef);
}

void JsSwiperContentTransitionProxy::SetMainAxisLength(const JSCallbackInfo& args)
{
    TAG_LOGD(AceLogTag::ACE_SWIPER, "SwiperContentTransitionProxy can not support set mainAxisLength value.");
}

void JsSwiperContentTransitionProxy::GetMainAxisLength(const JSCallbackInfo& args)
{
    auto mainAxisLength = 0.0f;
    if (proxy_) {
        mainAxisLength = proxy_->GetMainAxisLength();
    }
    auto toRef = JSRef<JSVal>::Make(JSVal(ToJSValue(mainAxisLength)));
    args.SetReturnValue(toRef);
}

void JsSwiperContentTransitionProxy::FinishTransition(const JSCallbackInfo& args)
{
    if (proxy_) {
        proxy_->FinishTransition();
    }
}

void JsSwiperContentTransitionProxy::Constructor(const JSCallbackInfo& args)
{
    auto proxy = Referenced::MakeRefPtr<JsSwiperContentTransitionProxy>();
    proxy->IncRefCount();
    args.SetReturnValue(Referenced::RawPtr(proxy));
}

void JsSwiperContentTransitionProxy::Destructor(JsSwiperContentTransitionProxy* proxy)
{
    if (proxy != nullptr) {
        proxy->DecRefCount();
    }
}

void JsSwiperFunction::JSBind(BindingTarget globalObj)
{
    JsSwiperContentTransitionProxy::JSBind(globalObj);
}

void JsSwiperFunction::Execute(int32_t index, int32_t targetIndex, const AnimationCallbackInfo& animationCallbackInfo)
{
    JSRef<JSObject> obj = JSRef<JSObject>::New();
    float currentOffset = animationCallbackInfo.currentOffset.value_or(0.0f);
    float targetOffset = animationCallbackInfo.targetOffset.value_or(0.0f);
    float velocity = animationCallbackInfo.velocity.value_or(0.0f);

    obj->SetProperty<float>("currentOffset", currentOffset);
    obj->SetProperty<float>("targetOffset", targetOffset);
    obj->SetProperty<float>("velocity", velocity);

    int32_t paramCount = 3;
    JSRef<JSVal> params[paramCount];
    params[0] = JSRef<JSVal>::Make(ToJSValue(index));
    params[1] = JSRef<JSVal>::Make(ToJSValue(targetIndex));
    params[2] = obj;
    JsFunction::ExecuteJS(paramCount, params);
}

void JsSwiperFunction::Execute(int32_t index, const AnimationCallbackInfo& animationCallbackInfo)
{
    JSRef<JSObject> obj = JSRef<JSObject>::New();
    float currentOffset = animationCallbackInfo.currentOffset.value_or(0.0f);
    float targetOffset = animationCallbackInfo.targetOffset.value_or(0.0f);
    float velocity = animationCallbackInfo.velocity.value_or(0.0f);

    obj->SetProperty<float>("currentOffset", currentOffset);
    obj->SetProperty<float>("targetOffset", targetOffset);
    obj->SetProperty<float>("velocity", velocity);

    int32_t paramCount = 2;
    JSRef<JSVal> params[paramCount];
    params[0] = JSRef<JSVal>::Make(ToJSValue(index));
    params[1] = obj;
    JsFunction::ExecuteJS(paramCount, params);
}

void JsSwiperFunction::Execute(int32_t errorCode)
{
    JSRef<JSObject> obj = JSRef<JSObject>::New();
    if (errorCode == ERROR_CODE_PARAM_INVALID) {
        obj->SetProperty<int32_t>("code", errorCode);
    }

    JSRef<JSVal> params[1];
    params[0] = obj;
    JsFunction::ExecuteJS(1, params);
}

void JsSwiperFunction::Execute(const RefPtr<SwiperContentTransitionProxy>& proxy)
{
    JSRef<JSObject> proxyObj = JSClass<JsSwiperContentTransitionProxy>::NewInstance();
    auto jsProxy = Referenced::Claim(proxyObj->Unwrap<JsSwiperContentTransitionProxy>());
    jsProxy->SetProxy(proxy);

    JSRef<JSVal> param = JSRef<JSObject>::Cast(proxyObj);
    JsFunction::ExecuteJS(1, &param);
}

void JsSwiperFunction::Execute(int32_t selectedIndex, int32_t index, float position, float mainAxisLength)
{
    JSRef<JSVal> selectedIndexValue = JSRef<JSVal>::Make(ToJSValue(selectedIndex));
    JSRef<JSVal> indexValue = JSRef<JSVal>::Make(ToJSValue(index));
    JSRef<JSVal> positionValue = JSRef<JSVal>::Make(ToJSValue(position));
    JSRef<JSVal> mainAxisLengthValue = JSRef<JSVal>::Make(ToJSValue(mainAxisLength));

    JSRef<JSVal> params[] = { selectedIndexValue, indexValue, positionValue, mainAxisLengthValue };
    JsFunction::ExecuteJS(4, params);
}

JSRef<JSVal> JsSwiperFunction::Execute(const SwiperContentWillScrollResult& result)
{
    JSRef<JSObject> obj = JSRef<JSObject>::New();
    obj->SetProperty<int32_t>("currentIndex", result.currentIndex);
    obj->SetProperty<int32_t>("comingIndex", result.comingIndex);
    obj->SetProperty<float>("offset", result.offset);

    JSRef<JSVal> params[] = { obj };
    return JsFunction::ExecuteJS(1, params);
}
} // namespace OHOS::Ace::Framework
