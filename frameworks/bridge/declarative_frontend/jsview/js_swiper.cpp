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

#include "frameworks/bridge/declarative_frontend/jsview/js_swiper.h"

#include <algorithm>
#include <iterator>

#include "core/components/common/layout/constants.h"
#include "core/components/swiper/swiper_component.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"

namespace OHOS::Ace::Framework {
namespace {

JSRef<JSVal> SwiperChangeEventToJSValue(const SwiperChangeEvent& eventInfo)
{
    JSRef<JSObject> obj = JSRef<JSObject>::New();
    obj->SetProperty<int32_t>("index", eventInfo.GetIndex());
    return obj;
}

} // namespace

void JSSwiper::Create(const JSCallbackInfo& info)
{
    std::list<RefPtr<OHOS::Ace::Component>> componentChildren;
    RefPtr<OHOS::Ace::SwiperComponent> component = AceType::MakeRefPtr<OHOS::Ace::SwiperComponent>(componentChildren);
    if (info.Length() > 0 && info[0]->IsObject()) {
        JSSwiperController* jsController = JSRef<JSObject>::Cast(info[0])->Unwrap<JSSwiperController>();
        if (jsController) {
            jsController->SetController(component->GetSwiperController());
        }
    }
    component->SetIndicator(InitIndicatorStyle());
    component->SetMainSwiperSize(MainSwiperSize::MIN);
    ViewStackProcessor::GetInstance()->Push(component);
    JSInteractableView::SetFocusNode(true);
}

void JSSwiper::JSBind(BindingTarget globalObj)
{
    JSClass<JSSwiper>::Declare("Swiper");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSSwiper>::StaticMethod("create", &JSSwiper::Create, opt);
    JSClass<JSSwiper>::StaticMethod("autoPlay", &JSSwiper::SetAutoplay, opt);
    JSClass<JSSwiper>::StaticMethod("digital", &JSSwiper::SetDigital, opt);
    JSClass<JSSwiper>::StaticMethod("duration", &JSSwiper::SetDuration, opt);
    JSClass<JSSwiper>::StaticMethod("index", &JSSwiper::SetIndex, opt);
    JSClass<JSSwiper>::StaticMethod("interval", &JSSwiper::SetInterval, opt);
    JSClass<JSSwiper>::StaticMethod("loop", &JSSwiper::SetLoop, opt);
    JSClass<JSSwiper>::StaticMethod("vertical", &JSSwiper::SetVertical, opt);
    JSClass<JSSwiper>::StaticMethod("indicator", &JSSwiper::SetIndicator, opt);
    JSClass<JSSwiper>::StaticMethod("cancelSwipeOnOtherAxis", &JSSwiper::SetCancelSwipeOnOtherAxis, opt);
    JSClass<JSSwiper>::StaticMethod("onChange", &JSSwiper::SetOnChange);
    JSClass<JSSwiper>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSSwiper>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSSwiper>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSSwiper>::StaticMethod("onClick", &JSSwiper::SetOnClick);
    JSClass<JSSwiper>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSSwiper>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSSwiper>::StaticMethod("indicatorStyle", &JSSwiper::SetIndicatorStyle);
    JSClass<JSSwiper>::StaticMethod("height", &JSSwiper::SetHeight);
    JSClass<JSSwiper>::StaticMethod("width", &JSSwiper::SetWidth);
    JSClass<JSSwiper>::Inherit<JSContainerBase>();
    JSClass<JSSwiper>::Inherit<JSViewAbstract>();
    JSClass<JSSwiper>::Bind<>(globalObj);
}

void JSSwiper::SetAutoplay(bool autoPlay)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto swiper = AceType::DynamicCast<OHOS::Ace::SwiperComponent>(component);
    if (swiper) {
        swiper->SetAutoPlay(autoPlay);
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

void JSSwiper::SetDuration(double duration)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto swiper = AceType::DynamicCast<OHOS::Ace::SwiperComponent>(component);
    if (swiper) {
        swiper->SetDuration(duration);
    }
}

void JSSwiper::SetIndex(uint32_t index)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto swiper = AceType::DynamicCast<OHOS::Ace::SwiperComponent>(component);
    if (swiper) {
        swiper->SetIndex(index);
    }
}

void JSSwiper::SetInterval(double interval)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto swiper = AceType::DynamicCast<OHOS::Ace::SwiperComponent>(component);
    if (swiper) {
        swiper->SetAutoPlayInterval(interval);
    }
}

void JSSwiper::SetLoop(bool loop)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto swiper = AceType::DynamicCast<OHOS::Ace::SwiperComponent>(component);
    if (swiper) {
        swiper->SetLoop(loop);
    }
}

void JSSwiper::SetVertical(bool isVertical)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto swiper = AceType::DynamicCast<OHOS::Ace::SwiperComponent>(component);
    if (swiper) {
        swiper->SetAxis(isVertical ? Axis::VERTICAL : Axis::HORIZONTAL);
    }
}

void JSSwiper::SetIndicator(bool showIndicator)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto swiper = AceType::DynamicCast<OHOS::Ace::SwiperComponent>(component);
    if (!showIndicator && swiper) {
        swiper->SetIndicator(nullptr);
    }
}

void JSSwiper::SetCancelSwipeOnOtherAxis(bool cancel)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto swiper = AceType::DynamicCast<OHOS::Ace::SwiperComponent>(component);
    // TODO: swiper->SetCancelSwipeOnOtherAxis(cancel) is no longer supported. check whether need this method
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
            JSRef<JSObject> obj = JSRef<JSObject>::Cast(info[1]);
            JSRef<JSVal> leftValue = obj->GetProperty("left");
            JSRef<JSVal> topValue = obj->GetProperty("top");
            JSRef<JSVal> rightValue = obj->GetProperty("right");
            JSRef<JSVal> bottomValue = obj->GetProperty("bottom");
            JSRef<JSVal> sizeValue = obj->GetProperty("size");
            JSRef<JSVal> maskValue = obj->GetProperty("mask");
            JSRef<JSVal> colorValue = obj->GetProperty("color");
            JSRef<JSVal> selectedColorValue = obj->GetProperty("selectedColor");

            if (leftValue->IsNumber()) {
                auto left = leftValue->ToNumber<double>();
                indictor->SetLeft(Dimension(left));
            }
            if (topValue->IsNumber()) {
                auto top = topValue->ToNumber<double>();
                indictor->SetTop(Dimension(top));
            }
            if (rightValue->IsNumber()) {
                auto right = rightValue->ToNumber<double>();
                indictor->SetRight(Dimension(right));
            }
            if (bottomValue->IsNumber()) {
                auto bottom = bottomValue->ToNumber<double>();
                indictor->SetBottom(Dimension(bottom));
            }
            if (sizeValue->IsNumber()) {
                auto size = sizeValue->ToNumber<double>();
                indictor->SetSize(Dimension(size));
            }
            if (maskValue->IsBoolean()) {
                auto mask = maskValue->ToBoolean();
                indictor->SetIndicatorMask(mask);
            }
            if (colorValue->IsString()) {
                auto colorString = colorValue->ToString();
                indictor->SetColor(Color::FromString(colorString));
            }
            if (selectedColorValue->IsString()) {
                auto selectedColorString = selectedColorValue->ToString();
                indictor->SetSelectedColor(Color::FromString(selectedColorString));
            }
        }
    }
    info.ReturnSelf();
}

void JSSwiper::SetOnChange(const JSCallbackInfo& args)
{
    if (args[0]->IsFunction()) {
        auto changeHandler = AceType::MakeRefPtr<JsEventFunction<SwiperChangeEvent, 1>>(
            JSRef<JSFunc>::Cast(args[0]), SwiperChangeEventToJSValue);
        auto onChange = EventMarker([executionContext = args.GetExecutionContext(), func = std::move(changeHandler)](
                                        const BaseEventInfo* info) {
            JAVASCRIPT_EXECUTION_SCOPE(executionContext);
            auto swiperInfo = TypeInfoHelper::DynamicCast<SwiperChangeEvent>(info);
            if (!swiperInfo) {
                LOGE("HandleChangeEvent swiperInfo == nullptr");
                return;
            }
            func->Execute(*swiperInfo);
        });
        auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
        auto swiper = AceType::DynamicCast<OHOS::Ace::SwiperComponent>(component);
        if (swiper) {
            swiper->SetChangeEventId(onChange);
        }
    }
    args.ReturnSelf();
}

void JSSwiper::SetOnClick(const JSCallbackInfo& args)
{
    if (args[0]->IsFunction()) {
        auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
        auto swiper = AceType::DynamicCast<OHOS::Ace::SwiperComponent>(component);
        if (swiper) {
            swiper->SetClickEventId(JSInteractableView::GetClickEventMarker(args));
        }
    }
    args.SetReturnValue(args.This());
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
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto swiper = AceType::DynamicCast<OHOS::Ace::SwiperComponent>(component);
    if (swiper) {
        JSViewAbstract::JsWidth(info);
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
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto swiper = AceType::DynamicCast<OHOS::Ace::SwiperComponent>(component);
    if (swiper) {
        JSViewAbstract::JsHeight(info);
        if (swiper->GetMainSwiperSize() == MainSwiperSize::MAX ||
            swiper->GetMainSwiperSize() == MainSwiperSize::MAX_X) {
            swiper->SetMainSwiperSize(MainSwiperSize::MAX);
        } else {
            swiper->SetMainSwiperSize(MainSwiperSize::MAX_Y);
        }
    }
}

void JSSwiperController::JSBind(BindingTarget globalObj)
{
    JSClass<JSSwiperController>::Declare("SwiperController");
    JSClass<JSSwiperController>::CustomMethod("showNext", &JSSwiperController::ShowNext);
    JSClass<JSSwiperController>::CustomMethod("showPrevious", &JSSwiperController::ShowPrevious);
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

} // namespace OHOS::Ace::Framework
