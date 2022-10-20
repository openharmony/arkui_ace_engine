/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/declarative_frontend/jsview/js_swiper.h"

#include <algorithm>
#include <iterator>

#include "bridge/common/utils/utils.h"
#include "bridge/declarative_frontend/engine/functions/js_click_function.h"
#include "bridge/declarative_frontend/jsview/models/swiper_model_impl.h"
#include "bridge/js_frontend/engine/jsi/js_value.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/scroll_bar.h"
#include "core/components/swiper/swiper_component.h"
#include "core/components_ng/pattern/swiper/swiper_model_ng.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"

namespace OHOS::Ace {

std::unique_ptr<SwiperModel> SwiperModel::instance_ = nullptr;

SwiperModel* SwiperModel::GetInstance()
{
    if (!instance_) {
#ifdef NG_BUILD
        instance_.reset(new NG::SwiperModelNG());
#else
        if (Container::IsCurrentUseNewPipeline()) {
            instance_.reset(new NG::SwiperModelNG());
        } else {
            instance_.reset(new Framework::SwiperModelImpl());
        }
#endif
    }
    return instance_.get();
}

} // namespace OHOS::Ace
namespace OHOS::Ace::Framework {
namespace {

const std::vector<EdgeEffect> EDGE_EFFECT = { EdgeEffect::SPRING, EdgeEffect::FADE, EdgeEffect::NONE };
const std::vector<SwiperDisplayMode> DISPLAY_MODE = { SwiperDisplayMode::STRETCH, SwiperDisplayMode::AUTO_LINEAR };

JSRef<JSVal> SwiperChangeEventToJSValue(const SwiperChangeEvent& eventInfo)
{
    return JSRef<JSVal>::Make(ToJSValue(eventInfo.GetIndex()));
}

} // namespace

void JSSwiper::Create(const JSCallbackInfo& info)
{
    auto controller = SwiperModel::GetInstance()->Create();

    if (info.Length() > 0 && info[0]->IsObject()) {
        auto* jsController = JSRef<JSObject>::Cast(info[0])->Unwrap<JSSwiperController>();
        if (jsController) {
            jsController->SetController(controller);
        }
    }
}

void JSSwiper::JsRemoteMessage(const JSCallbackInfo& info)
{
    RemoteCallback remoteCallback;
    JSInteractableView::JsRemoteMessage(info, remoteCallback);

    SwiperModel::GetInstance()->SetRemoteMessageEventId(std::move(remoteCallback));
}

void JSSwiper::JSBind(BindingTarget globalObj)
{
    JSClass<JSSwiper>::Declare("Swiper");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSSwiper>::StaticMethod("create", &JSSwiper::Create, opt);
    JSClass<JSSwiper>::StaticMethod("autoPlay", &JSSwiper::SetAutoPlay, opt);
    JSClass<JSSwiper>::StaticMethod("digital", &JSSwiper::SetDigital, opt);
    JSClass<JSSwiper>::StaticMethod("duration", &JSSwiper::SetDuration, opt);
    JSClass<JSSwiper>::StaticMethod("index", &JSSwiper::SetIndex, opt);
    JSClass<JSSwiper>::StaticMethod("interval", &JSSwiper::SetInterval, opt);
    JSClass<JSSwiper>::StaticMethod("loop", &JSSwiper::SetLoop, opt);
    JSClass<JSSwiper>::StaticMethod("vertical", &JSSwiper::SetVertical, opt);
    JSClass<JSSwiper>::StaticMethod("indicator", &JSSwiper::SetIndicator, opt);
    JSClass<JSSwiper>::StaticMethod("displayMode", &JSSwiper::SetDisplayMode);
    JSClass<JSSwiper>::StaticMethod("effectMode", &JSSwiper::SetEffectMode);
    JSClass<JSSwiper>::StaticMethod("displayCount", &JSSwiper::SetDisplayCount);
    JSClass<JSSwiper>::StaticMethod("itemSpace", &JSSwiper::SetItemSpace);
    JSClass<JSSwiper>::StaticMethod("cachedCount", &JSSwiper::SetCachedCount);
    JSClass<JSSwiper>::StaticMethod("curve", &JSSwiper::SetCurve);
    JSClass<JSSwiper>::StaticMethod("onChange", &JSSwiper::SetOnChange);
    JSClass<JSSwiper>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSSwiper>::StaticMethod("onHover", &JSInteractableView::JsOnHover);
    JSClass<JSSwiper>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSSwiper>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSSwiper>::StaticMethod("remoteMessage", &JSSwiper::JsRemoteMessage);
    JSClass<JSSwiper>::StaticMethod("onClick", &JSSwiper::SetOnClick);
    JSClass<JSSwiper>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSSwiper>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSSwiper>::StaticMethod("indicatorStyle", &JSSwiper::SetIndicatorStyle);
    JSClass<JSSwiper>::StaticMethod("enabled", &JSSwiper::SetEnabled);
    JSClass<JSSwiper>::StaticMethod("disableSwipe", &JSSwiper::SetDisableSwipe);
    JSClass<JSSwiper>::StaticMethod("height", &JSSwiper::SetHeight);
    JSClass<JSSwiper>::StaticMethod("width", &JSSwiper::SetWidth);
    JSClass<JSSwiper>::StaticMethod("size", &JSSwiper::SetSize);
    JSClass<JSSwiper>::Inherit<JSContainerBase>();
    JSClass<JSSwiper>::Inherit<JSViewAbstract>();
    JSClass<JSSwiper>::Bind<>(globalObj);
}

void JSSwiper::SetAutoPlay(bool autoPlay)
{
    SwiperModel::GetInstance()->SetAutoPlay(autoPlay);
}

void JSSwiper::SetEnabled(const JSCallbackInfo& info)
{
    JSViewAbstract::JsEnabled(info);
    if (info.Length() < 1) {
        LOGE("The info is wrong, it is supposed to have at least 1 arguments");
        return;
    }

    if (!info[0]->IsBoolean()) {
        LOGE("info is not bool.");
        return;
    }

    SwiperModel::GetInstance()->SetEnabled(info[0]->IsBoolean());
}

void JSSwiper::SetDisableSwipe(bool disableSwipe)
{
    SwiperModel::GetInstance()->SetDisableSwipe(disableSwipe);
}

void JSSwiper::SetEffectMode(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The info is wrong, it is supposed to have atleast 1 arguments");
        return;
    }

    if (!info[0]->IsNumber()) {
        LOGE("info is not a  number ");
        return;
    }

    auto edgeEffect = info[0]->ToNumber<int32_t>();
    if (edgeEffect < 0 || edgeEffect >= static_cast<int32_t>(EDGE_EFFECT.size())) {
        LOGE("Edge effect: %{public}d illegal value", edgeEffect);
        return;
    }

    SwiperModel::GetInstance()->SetEdgeEffect(EDGE_EFFECT[edgeEffect]);
}

void JSSwiper::SetDisplayCount(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The info is wrong, it is supposed to have atleast 1 arguments");
        return;
    }

    if (info[0]->IsString() && info[0]->ToString() == "auto") {
        SwiperModel::GetInstance()->SetDisplayMode(SwiperDisplayMode::AUTO_LINEAR);
    } else if (info[0]->IsNumber()) {
        SwiperModel::GetInstance()->SetDisplayCount(info[0]->ToNumber<int32_t>());
    }
}

void JSSwiper::SetDigital(bool digitalIndicator)
{
    SwiperModel::GetInstance()->SetDigital(digitalIndicator);
}

void JSSwiper::SetDuration(int32_t duration)
{
    if (duration < 0) {
        LOGE("duration is not valid: %{public}d", duration);
        return;
    }

    SwiperModel::GetInstance()->SetDuration(duration);
}

void JSSwiper::SetIndex(int32_t index)
{
    if (index < 0) {
        LOGE("index is not valid: %{public}d", index);
        return;
    }

    SwiperModel::GetInstance()->SetIndex(index);
}

void JSSwiper::SetInterval(int32_t interval)
{
    if (interval <= 0) {
        LOGE("interval is not valid: %{public}d", interval);
        return;
    }

    SwiperModel::GetInstance()->SetAutoPlayInterval(interval);
}

void JSSwiper::SetLoop(bool loop)
{
    SwiperModel::GetInstance()->SetLoop(loop);
}

void JSSwiper::SetVertical(bool isVertical)
{
    SwiperModel::GetInstance()->SetDirection(isVertical ? Axis::VERTICAL : Axis::HORIZONTAL);
}

void JSSwiper::SetIndicator(bool showIndicator)
{
    SwiperModel::GetInstance()->SetShowIndicator(showIndicator);
}

void JSSwiper::SetIndicatorStyle(const JSCallbackInfo& info)
{
    SwiperParameters swiperParameters;
    if (info[0]->IsObject()) {
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(info[0]);
        JSRef<JSVal> leftValue = obj->GetProperty("left");
        JSRef<JSVal> topValue = obj->GetProperty("top");
        JSRef<JSVal> rightValue = obj->GetProperty("right");
        JSRef<JSVal> bottomValue = obj->GetProperty("bottom");
        JSRef<JSVal> sizeValue = obj->GetProperty("size");
        JSRef<JSVal> maskValue = obj->GetProperty("mask");
        JSRef<JSVal> colorValue = obj->GetProperty("color");
        JSRef<JSVal> selectedColorValue = obj->GetProperty("selectedColor");

        Dimension dimLeft;
        if (ParseJsDimensionPx(leftValue, dimLeft)) {
            swiperParameters.dimLeft = dimLeft;
        }
        Dimension dimTop;
        if (ParseJsDimensionPx(topValue, dimTop)) {
            swiperParameters.dimTop = dimTop;
        }
        Dimension dimRight;
        if (ParseJsDimensionPx(rightValue, dimRight)) {
            swiperParameters.dimRight = dimRight;
        }
        Dimension dimBottom;
        if (ParseJsDimensionPx(bottomValue, dimBottom)) {
            swiperParameters.dimBottom = dimBottom;
        }
        Dimension dimSize;
        if (ParseJsDimensionPx(sizeValue, dimSize)) {
            swiperParameters.dimSize = dimSize;
        }
        if (maskValue->IsBoolean()) {
            auto mask = maskValue->ToBoolean();
            swiperParameters.maskValue = mask;
        }
        Color colorVal;
        if (ParseJsColor(colorValue, colorVal)) {
            swiperParameters.colorVal = colorVal;
        }
        Color selectedColorVal;
        if (ParseJsColor(selectedColorValue, selectedColorVal)) {
            swiperParameters.selectedColorVal = selectedColorVal;
        }
    }

    SwiperModel::GetInstance()->SetIndicatorStyle(swiperParameters);

    info.ReturnSelf();
}

void JSSwiper::SetItemSpace(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 arguments");
        return;
    }

    Dimension value;
    if (!ParseJsDimensionVp(info[0], value)) {
        return;
    }

    if (LessNotEqual(value.Value(), 0.0)) {
        value.SetValue(0.0);
    }

    SwiperModel::GetInstance()->SetItemSpace(value);
}

void JSSwiper::SetDisplayMode(int32_t index)
{
    if (index < 0 || index >= static_cast<int32_t>(DISPLAY_MODE.size())) {
        LOGE("display mode is not valid: %{public}d", index);
        return;
    }

    SwiperModel::GetInstance()->SetDisplayMode(DISPLAY_MODE[index]);
}

void JSSwiper::SetCachedCount(int32_t cachedCount)
{
    SwiperModel::GetInstance()->SetCachedCount(cachedCount);
}

void JSSwiper::SetCurve(const std::string& curveStr)
{
    RefPtr<Curve> curve = CreateCurve(curveStr);

    SwiperModel::GetInstance()->SetCurve(curve);
}

void JSSwiper::SetOnChange(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        return;
    }

    auto changeHandler = AceType::MakeRefPtr<JsEventFunction<SwiperChangeEvent, 1>>(
        JSRef<JSFunc>::Cast(info[0]), SwiperChangeEventToJSValue);
    auto onChange = [executionContext = info.GetExecutionContext(), func = std::move(changeHandler)](
                        const BaseEventInfo* info) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext);
        const auto* swiperInfo = TypeInfoHelper::DynamicCast<SwiperChangeEvent>(info);
        if (!swiperInfo) {
            LOGE("HandleChangeEvent swiperInfo == nullptr");
            return;
        }
        ACE_SCORING_EVENT("Swiper.OnChange");
        func->Execute(*swiperInfo);
    };

    SwiperModel::GetInstance()->SetOnChange(std::move(onChange));
}

void JSSwiper::SetOnClick(const JSCallbackInfo& info)
{
    if (info[0]->IsFunction()) {
        RefPtr<JsClickFunction> jsOnClickFunc = AceType::MakeRefPtr<JsClickFunction>(JSRef<JSFunc>::Cast(info[0]));
        auto onClick = [execCtx = info.GetExecutionContext(), func = std::move(jsOnClickFunc)](
                           const BaseEventInfo* info, const RefPtr<V2::InspectorFunctionImpl>& impl) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            const auto* clickInfo = TypeInfoHelper::DynamicCast<ClickInfo>(info);
            auto newInfo = *clickInfo;
            if (impl) {
                impl->UpdateEventInfo(newInfo);
            }
            ACE_SCORING_EVENT("onClick");
            func->Execute(newInfo);
        };

        SwiperModel::GetInstance()->SetOnClick(onClick);
    }

    info.SetReturnValue(info.This());
}

RefPtr<OHOS::Ace::SwiperIndicator> JSSwiper::InitIndicatorStyle()
{
    auto indicator = AceType::MakeRefPtr<OHOS::Ace::SwiperIndicator>();
    auto indicatorTheme = GetTheme<SwiperIndicatorTheme>();
    if (indicatorTheme) {
        indicator->InitStyle(indicatorTheme);
    }
    return indicator;
}

void JSSwiper::SetWidth(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 arguments");
        return;
    }

    SetWidth(info[0]);
}

void JSSwiper::SetWidth(const JSRef<JSVal>& jsValue)
{
    if (Container::IsCurrentUseNewPipeline()) {
        JSViewAbstract::JsWidth(jsValue);
        return;
    }

    JSViewAbstract::JsWidth(jsValue);
    SwiperModel::GetInstance()->SetMainSwiperSizeWidth();
}

void JSSwiper::SetHeight(const JSRef<JSVal>& jsValue)
{
    if (Container::IsCurrentUseNewPipeline()) {
        JSViewAbstract::JsHeight(jsValue);
        return;
    }

    JSViewAbstract::JsHeight(jsValue);
    SwiperModel::GetInstance()->SetMainSwiperSizeHeight();
}

void JSSwiper::SetHeight(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 arguments");
        return;
    }

    SetHeight(info[0]);
}

void JSSwiper::SetSize(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 arguments");
        return;
    }

    if (!info[0]->IsObject()) {
        LOGE("arg is not Object or String.");
        return;
    }

    JSRef<JSObject> sizeObj = JSRef<JSObject>::Cast(info[0]);
    SetWidth(sizeObj->GetProperty("width"));
    SetHeight(sizeObj->GetProperty("height"));
}

void JSSwiperController::JSBind(BindingTarget globalObj)
{
    JSClass<JSSwiperController>::Declare("SwiperController");
    JSClass<JSSwiperController>::CustomMethod("swipeTo", &JSSwiperController::SwipeTo);
    JSClass<JSSwiperController>::CustomMethod("showNext", &JSSwiperController::ShowNext);
    JSClass<JSSwiperController>::CustomMethod("showPrevious", &JSSwiperController::ShowPrevious);
    JSClass<JSSwiperController>::CustomMethod("finishAnimation", &JSSwiperController::FinishAnimation);
    JSClass<JSSwiperController>::Bind(globalObj, JSSwiperController::Constructor, JSSwiperController::Destructor);
}

void JSSwiperController::Constructor(const JSCallbackInfo& args)
{
    auto scroller = Referenced::MakeRefPtr<JSSwiperController>();
    scroller->IncRefCount();
    args.SetReturnValue(Referenced::RawPtr(scroller));
}

void JSSwiperController::Destructor(JSSwiperController* scroller)
{
    if (scroller != nullptr) {
        scroller->DecRefCount();
    }
}

void JSSwiperController::FinishAnimation(const JSCallbackInfo& args)
{
    if (!args[0]->IsFunction() || !controller_) {
        return;
    }

    RefPtr<JsFunction> jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(args[0]));
    auto onFinish = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc)]() {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("Swiper.finishAnimation");
        func->Execute();
    };

    if (Container::IsCurrentUseNewPipeline()) {
        controller_->SetFinishCallback(onFinish);
        controller_->FinishAnimation();
        return;
    }

    controller_->SetFinishCallback(onFinish);
    controller_->FinishAnimation();
}

} // namespace OHOS::Ace::Framework
