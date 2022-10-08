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
#include "bridge/js_frontend/engine/jsi/js_value.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/scroll_bar.h"
#include "core/components/swiper/swiper_component.h"
#include "core/components_ng/pattern/swiper/swiper_view.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"

namespace OHOS::Ace::Framework {
namespace {

constexpr int32_t DEFAULT_SWIPER_CACHED_COUNT = 1;

const std::vector<EdgeEffect> EDGE_EFFECT = { EdgeEffect::SPRING, EdgeEffect::FADE, EdgeEffect::NONE };
const std::vector<SwiperDisplayMode> DISPLAY_MODE = { SwiperDisplayMode::STRETCH, SwiperDisplayMode::AUTO_LINEAR };

JSRef<JSVal> SwiperChangeEventToJSValue(const SwiperChangeEvent& eventInfo)
{
    return JSRef<JSVal>::Make(ToJSValue(eventInfo.GetIndex()));
}

} // namespace

void JSSwiper::Create(const JSCallbackInfo& info)
{
    if (Container::IsCurrentUseNewPipeline()) {
        auto controller = NG::SwiperView::Create();
        if (info.Length() > 0 && info[0]->IsObject()) {
            auto* jsController = JSRef<JSObject>::Cast(info[0])->Unwrap<JSSwiperController>();
            if (jsController) {
                jsController->SetController(controller);
            }
        }
        return;
    }

    std::list<RefPtr<OHOS::Ace::Component>> componentChildren;
    RefPtr<OHOS::Ace::SwiperComponent> component = AceType::MakeRefPtr<OHOS::Ace::SwiperComponent>(componentChildren);
    if (info.Length() > 0 && info[0]->IsObject()) {
        auto* jsController = JSRef<JSObject>::Cast(info[0])->Unwrap<JSSwiperController>();
        if (jsController) {
            jsController->SetController(component->GetSwiperController());
        }
    }
    component->SetIndicator(InitIndicatorStyle());
    component->SetMainSwiperSize(MainSwiperSize::MIN);
    component->SetCachedSize(DEFAULT_SWIPER_CACHED_COUNT);
    component->SetCurve(Curves::LINEAR);
    ViewStackProcessor::GetInstance()->ClaimElementId(component);
    ViewStackProcessor::GetInstance()->Push(component);
    JSInteractableView::SetFocusNode(true);
}

void JSSwiper::JsRemoteMessage(const JSCallbackInfo& info)
{
    RemoteCallback remoteCallback;
    JSInteractableView::JsRemoteMessage(info, remoteCallback);
    EventMarker remoteMessageEventId(std::move(remoteCallback));
    auto* stack = ViewStackProcessor::GetInstance();
    auto swiperComponent = AceType::DynamicCast<SwiperComponent>(stack->GetMainComponent());
    if (!swiperComponent) {
        LOGE("swiperComponent is null");
        return;
    }
    swiperComponent->SetRemoteMessageEventId(remoteMessageEventId);
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
    JSClass<JSSwiper>::StaticMethod("cancelSwipeOnOtherAxis", &JSSwiper::SetCancelSwipeOnOtherAxis, opt);
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
    if (Container::IsCurrentUseNewPipeline()) {
        NG::SwiperView::SetAutoPlay(autoPlay);
        return;
    }

    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto swiper = AceType::DynamicCast<OHOS::Ace::SwiperComponent>(component);
    if (swiper) {
        swiper->SetAutoPlay(autoPlay);
    }
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

    if (Container::IsCurrentUseNewPipeline()) {
        NG::SwiperView::SetEnabled(info[0]->IsBoolean());
        return;
    }

    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto swiper = AceType::DynamicCast<OHOS::Ace::SwiperComponent>(component);
    if (swiper) {
        swiper->SetDisabledStatus(!(info[0]->ToBoolean()));
    }
}

void JSSwiper::SetDisableSwipe(bool disableSwipe)
{
    if (Container::IsCurrentUseNewPipeline()) {
        NG::SwiperView::SetDisableSwipe(disableSwipe);
        return;
    }

    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto swiper = AceType::DynamicCast<OHOS::Ace::SwiperComponent>(component);
    if (swiper) {
        swiper->DisableSwipe(disableSwipe);
    }
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

    if (Container::IsCurrentUseNewPipeline()) {
        auto edgeEffect = info[0]->ToNumber<int32_t>();
        if (edgeEffect < 0 || edgeEffect >= static_cast<int32_t>(EDGE_EFFECT.size())) {
            LOGE("Edge effect: %{public}d illegal value", edgeEffect);
            return;
        }
        NG::SwiperView::SetEdgeEffect(EDGE_EFFECT[edgeEffect]);
        return;
    }

    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto swiper = AceType::DynamicCast<OHOS::Ace::SwiperComponent>(component);
    if (!swiper) {
        return;
    }

    auto swiperMode = static_cast<EdgeEffect>(info[0]->ToNumber<int32_t>());
    if (swiperMode == EdgeEffect::SPRING) {
        swiper->SetEdgeEffect(EdgeEffect::SPRING);
    } else if (swiperMode == EdgeEffect::FADE) {
        swiper->SetEdgeEffect(EdgeEffect::FADE);
    } else {
        swiper->SetEdgeEffect(EdgeEffect::NONE);
    }
}

void JSSwiper::SetDisplayCount(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The info is wrong, it is supposed to have atleast 1 arguments");
        return;
    }

    if (Container::IsCurrentUseNewPipeline()) {
        if (info[0]->IsString() && info[0]->ToString() == "auto") {
            NG::SwiperView::SetDisplayMode(SwiperDisplayMode::AUTO_LINEAR);
        } else if (info[0]->IsNumber()) {
            NG::SwiperView::SetDisplayCount(info[0]->ToNumber<int32_t>());
        }
        LOGE("display count is not valid");
        return;
    }

    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto swiper = AceType::DynamicCast<OHOS::Ace::SwiperComponent>(component);
    if (!swiper) {
        return;
    }

    if (info[0]->ToString() == "auto") {
        swiper->SetDisplayMode(SwiperDisplayMode::AUTO_LINEAR);
    }

    if (info[0]->IsNumber()) {
        swiper->SetDisplayCount(info[0]->ToNumber<int32_t>());
    }
}

void JSSwiper::SetDigital(bool digitalIndicator)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto swiper = AceType::DynamicCast<OHOS::Ace::SwiperComponent>(component);
    if (swiper) {
        swiper->SetDigitalIndicator(digitalIndicator);
    }
}

void JSSwiper::SetDuration(int32_t duration)
{
    if (duration < 0) {
        LOGE("duration is not valid: %{public}d", duration);
        return;
    }

    if (Container::IsCurrentUseNewPipeline()) {
        NG::SwiperView::SetDuration(duration);
        return;
    }
    
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto swiper = AceType::DynamicCast<OHOS::Ace::SwiperComponent>(component);
    if (swiper) {
        swiper->SetDuration(duration);
    }
}

void JSSwiper::SetIndex(int32_t index)
{
    if (index < 0) {
        LOGE("index is not valid: %{public}d", index);
        return;
    }

    if (Container::IsCurrentUseNewPipeline()) {
        NG::SwiperView::SetIndex(index);
        return;
    }

    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto swiper = AceType::DynamicCast<OHOS::Ace::SwiperComponent>(component);
    if (swiper) {
        swiper->SetIndex(index);
    }
}

void JSSwiper::SetInterval(int32_t interval)
{
    if (interval <= 0) {
        LOGE("interval is not valid: %{public}d", interval);
        return;
    }

    if (Container::IsCurrentUseNewPipeline()) {
        NG::SwiperView::SetAutoPlayInterval(interval);
        return;
    }

    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto swiper = AceType::DynamicCast<OHOS::Ace::SwiperComponent>(component);
    if (swiper) {
        swiper->SetAutoPlayInterval(interval);
    }
}

void JSSwiper::SetLoop(bool loop)
{
    if (Container::IsCurrentUseNewPipeline()) {
        NG::SwiperView::SetLoop(loop);
        return;
    }

    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto swiper = AceType::DynamicCast<OHOS::Ace::SwiperComponent>(component);
    if (swiper) {
        swiper->SetLoop(loop);
    }
}

void JSSwiper::SetVertical(bool isVertical)
{
    if (Container::IsCurrentUseNewPipeline()) {
        NG::SwiperView::SetDirection(isVertical ? Axis::VERTICAL : Axis::HORIZONTAL);
        return;
    }

    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto swiper = AceType::DynamicCast<OHOS::Ace::SwiperComponent>(component);
    if (swiper) {
        swiper->SetAxis(isVertical ? Axis::VERTICAL : Axis::HORIZONTAL);
    }
}

void JSSwiper::SetIndicator(bool showIndicator)
{
    if (Container::IsCurrentUseNewPipeline()) {
        NG::SwiperView::SetShowIndicator(showIndicator);
        return;
    }

    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto swiper = AceType::DynamicCast<OHOS::Ace::SwiperComponent>(component);
    if (swiper) {
        swiper->SetShowIndicator(showIndicator);
        if (!showIndicator) {
            swiper->SetIndicator(nullptr);
        }
    }
}

void JSSwiper::SetCancelSwipeOnOtherAxis(bool cancel)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto swiper = AceType::DynamicCast<OHOS::Ace::SwiperComponent>(component);
}

void JSSwiper::SetIndicatorStyle(const JSCallbackInfo& info)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto swiper = AceType::DynamicCast<OHOS::Ace::SwiperComponent>(component);
    if (swiper) {
        auto indictor = swiper->GetIndicator();
        if (!indictor) {
            return;
        }

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
                indictor->SetLeft(dimLeft);
            }
            Dimension dimTop;
            if (ParseJsDimensionPx(topValue, dimTop)) {
                indictor->SetTop(dimTop);
            }
            Dimension dimRight;
            if (ParseJsDimensionPx(rightValue, dimRight)) {
                indictor->SetRight(dimRight);
            }
            Dimension dimBottom;
            if (ParseJsDimensionPx(bottomValue, dimBottom)) {
                indictor->SetBottom(dimBottom);
            }
            Dimension dimSize;
            if (ParseJsDimensionPx(sizeValue, dimSize)) {
                indictor->SetSize(dimSize);
            }
            if (maskValue->IsBoolean()) {
                auto mask = maskValue->ToBoolean();
                indictor->SetIndicatorMask(mask);
            }
            Color colorVal;
            if (ParseJsColor(colorValue, colorVal)) {
                indictor->SetColor(colorVal);
            }
            Color selectedColorVal;
            if (ParseJsColor(selectedColorValue, selectedColorVal)) {
                indictor->SetSelectedColor(selectedColorVal);
            }
        }
    }
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

    if (Container::IsCurrentUseNewPipeline()) {
        NG::SwiperView::SetItemSpace(value);
        return;
    }

    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto swiper = AceType::DynamicCast<OHOS::Ace::SwiperComponent>(component);
    if (swiper) {
        swiper->SetItemSpace(value);
    }
}

void JSSwiper::SetDisplayMode(int32_t index)
{
    if (index < 0 || index >= static_cast<int32_t>(DISPLAY_MODE.size())) {
        LOGE("display mode is not valid: %{public}d", index);
        return;
    }

    if (Container::IsCurrentUseNewPipeline()) {
        NG::SwiperView::SetDisplayMode(DISPLAY_MODE[index]);
        return;
    }

    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto swiper = AceType::DynamicCast<OHOS::Ace::SwiperComponent>(component);
    if (swiper) {
        swiper->SetDisplayMode(static_cast<SwiperDisplayMode>(index));
    }
}

void JSSwiper::SetCachedCount(int32_t cachedCount)
{
    if (Container::IsCurrentUseNewPipeline()) {
        NG::SwiperView::SetCachedCount(cachedCount);
        return;
    }

    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto swiper = AceType::DynamicCast<OHOS::Ace::SwiperComponent>(component);
    if (swiper) {
        swiper->SetCachedSize(cachedCount);
    }
}

void JSSwiper::SetCurve(const std::string& curveStr)
{
    RefPtr<Curve> curve = CreateCurve(curveStr);

    if (Container::IsCurrentUseNewPipeline()) {
        NG::SwiperView::SetCurve(curve);
        return;
    }

    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto swiper = AceType::DynamicCast<OHOS::Ace::SwiperComponent>(component);
    swiper->SetCurve(curve);
}

void JSSwiper::SetOnChange(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        return;
    }

    if (Container::IsCurrentUseNewPipeline()) {
        auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
        auto onChange = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc)](int32_t index) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("Swiper.onChange");
            auto newJSVal = JSRef<JSVal>::Make(ToJSValue(index));
            func->ExecuteJS(1, &newJSVal);
        };
        NG::SwiperView::SetOnChange(std::move(onChange));
        return;
    }

    auto changeHandler = AceType::MakeRefPtr<JsEventFunction<SwiperChangeEvent, 1>>(
        JSRef<JSFunc>::Cast(info[0]), SwiperChangeEventToJSValue);
    auto onChange = EventMarker([executionContext = info.GetExecutionContext(), func = std::move(changeHandler)](
                                    const BaseEventInfo* info) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext);
        const auto* swiperInfo = TypeInfoHelper::DynamicCast<SwiperChangeEvent>(info);
        if (!swiperInfo) {
            LOGE("HandleChangeEvent swiperInfo == nullptr");
            return;
        }
        ACE_SCORING_EVENT("Swiper.OnChange");
        func->Execute(*swiperInfo);
    });
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto swiper = AceType::DynamicCast<OHOS::Ace::SwiperComponent>(component);
    if (swiper) {
        swiper->SetChangeEventId(onChange);
    }
}

EventMarker GetClickEventMarker(const JSCallbackInfo& info)
{
    auto inspector = ViewStackProcessor::GetInstance()->GetInspectorComposedComponent();
    if (!inspector) {
        LOGE("fail to get inspector for on get click event marker");
        return EventMarker();
    }
    auto impl = inspector->GetInspectorFunctionImpl();
    RefPtr<JsClickFunction> jsOnClickFunc = AceType::MakeRefPtr<JsClickFunction>(JSRef<JSFunc>::Cast(info[0]));
    auto onClickId = EventMarker(
        [execCtx = info.GetExecutionContext(), func = std::move(jsOnClickFunc), impl](const BaseEventInfo* info) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            auto clickInfo = TypeInfoHelper::DynamicCast<ClickInfo>(info);
            auto newInfo = *clickInfo;
            if (impl) {
                impl->UpdateEventInfo(newInfo);
            }
            ACE_SCORING_EVENT("onClick");
            func->Execute(newInfo);
        });
    return onClickId;
}

void JSSwiper::SetOnClick(const JSCallbackInfo& info)
{
    if (info[0]->IsFunction()) {
        auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
        auto swiper = AceType::DynamicCast<OHOS::Ace::SwiperComponent>(component);
        if (swiper) {
            swiper->SetClickEventId(GetClickEventMarker(info));
        }
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

    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto swiper = AceType::DynamicCast<OHOS::Ace::SwiperComponent>(component);
    if (swiper) {
        JSViewAbstract::JsWidth(jsValue);
        if (swiper->GetMainSwiperSize() == MainSwiperSize::MAX ||
            swiper->GetMainSwiperSize() == MainSwiperSize::MAX_Y) {
            swiper->SetMainSwiperSize(MainSwiperSize::MAX);
        } else {
            swiper->SetMainSwiperSize(MainSwiperSize::MAX_X);
        }
    }
}

void JSSwiper::SetHeight(const JSCallbackInfo& info)
{
    if (Container::IsCurrentUseNewPipeline()) {
        JSViewAbstract::JsHeight(info);
        return;
    }

    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 arguments");
        return;
    }

    SetHeight(info[0]);
}

void JSSwiper::SetHeight(const JSRef<JSVal>& jsValue)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto swiper = AceType::DynamicCast<OHOS::Ace::SwiperComponent>(component);
    if (swiper) {
        JSViewAbstract::JsHeight(jsValue);
        if (swiper->GetMainSwiperSize() == MainSwiperSize::MAX ||
            swiper->GetMainSwiperSize() == MainSwiperSize::MAX_X) {
            swiper->SetMainSwiperSize(MainSwiperSize::MAX);
        } else {
            swiper->SetMainSwiperSize(MainSwiperSize::MAX_Y);
        }
    }
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
