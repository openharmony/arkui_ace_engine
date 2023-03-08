/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/declarative_frontend/jsview/js_side_bar.h"

#include "base/geometry/dimension.h"
#include "base/log/ace_scoring_log.h"
#include "base/log/log.h"
#include "core/components/button/button_component.h"
#include "core/components/side_bar/render_side_bar_container.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/side_bar/side_bar_container_view.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"

namespace OHOS::Ace::Framework {
namespace {
constexpr Dimension DEFAULT_CONTROL_BUTTON_WIDTH = 32.0_vp;
constexpr Dimension DEFAULT_CONTROL_BUTTON_HEIGHT = 32.0_vp;
constexpr Dimension DEFAULT_SIDE_BAR_WIDTH = 200.0_vp;
constexpr Dimension DEFAULT_MIN_SIDE_BAR_WIDTH = 200.0_vp;
constexpr Dimension DEFAULT_MAX_SIDE_BAR_WIDTH = 280.0_vp;

enum class WidthType : uint32_t {
    SIDEBAR_WIDTH = 0,
    MIN_SIDEBAR_WIDTH,
    MAX_SIDEBAR_WIDTH,
};

void ParseAndSetWidth(const JSCallbackInfo& info, WidthType widthType)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 arguments");
        return;
    }

    Dimension value;
    if (!JSViewAbstract::ParseJsDimensionVp(info[0], value)) {
        return;
    }

    if (Container::IsCurrentUseNewPipeline()) {
        switch (widthType) {
            case WidthType::SIDEBAR_WIDTH:
                NG::SideBarContainerView::SetSideBarWidth(value.IsNonNegative() ? value : DEFAULT_SIDE_BAR_WIDTH);
                break;
            case WidthType::MIN_SIDEBAR_WIDTH:
                NG::SideBarContainerView::SetMinSideBarWidth(
                    value.IsNonNegative() ? value : DEFAULT_MIN_SIDE_BAR_WIDTH);
                break;
            case WidthType::MAX_SIDEBAR_WIDTH:
                NG::SideBarContainerView::SetMaxSideBarWidth(
                    value.IsNonNegative() ? value : DEFAULT_MAX_SIDE_BAR_WIDTH);
                break;
            default:
                break;
        }
        return;
    }

    if (LessNotEqual(value.Value(), 0.0)) {
        LOGW("JSSideBar::ParseAndSetWidth info[0] value is less than 0, the default is set to 0.");
        value.SetValue(0.0);
    }

    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::SideBarContainerComponent>(stack->GetMainComponent());
    if (!component) {
        LOGE("side bar is null");
        return;
    }

    if (value.Unit() == DimensionUnit::PERCENT) {
        component->SetIsPercentSize(value.Unit() == DimensionUnit::PERCENT);
    }

    switch (widthType) {
        case WidthType::SIDEBAR_WIDTH:
            component->SetSideBarWidth(value);
            break;
        case WidthType::MIN_SIDEBAR_WIDTH:
            component->SetSideBarMinWidth(value);
            break;
        case WidthType::MAX_SIDEBAR_WIDTH:
            component->SetSideBarMaxWidth(value);
            break;
        default:
            break;
    }
}

} // namespace

void JSSideBar::Create(const JSCallbackInfo& info)
{
    if (Container::IsCurrentUseNewPipeline()) {
        CreateForNG(info);
        return;
    }

    SideBarContainerType style = SideBarContainerType::EMBED;
    if (!info[0]->IsNull()) {
        if (info[0]->IsBoolean()) {
            style = static_cast<SideBarContainerType>(info[0]->ToBoolean());
        } else if (info[0]->IsNumber()) {
            style = static_cast<SideBarContainerType>(info[0]->ToNumber<int>());
        } else {
            LOGE("The arg is wrong");
            return;
        }
    }

    std::list<RefPtr<Component>> children;
    auto sideBarContainer = AceType::MakeRefPtr<OHOS::Ace::SideBarContainerComponent>(children);
    ViewStackProcessor::GetInstance()->ClaimElementId(sideBarContainer);
    sideBarContainer->SetMainStackSize(MainStackSize::MAX);
    sideBarContainer->SetSideBarContainerType(style);

    auto stack = ViewStackProcessor::GetInstance();
    stack->Push(sideBarContainer);
    JSInteractableView::SetFocusable(false);
    JSInteractableView::SetFocusNode(true);
}

void JSSideBar::CreateForNG(const JSCallbackInfo& info)
{
    NG::SideBarContainerView::Create();

    SideBarContainerType style = SideBarContainerType::EMBED;
    if (!info[0]->IsNull()) {
        if (info[0]->IsBoolean()) {
            style = static_cast<SideBarContainerType>(info[0]->ToBoolean());
        } else if (info[0]->IsNumber()) {
            style = static_cast<SideBarContainerType>(info[0]->ToNumber<int>());
        } else {
            LOGE("JSSideBar::CreateForNG The SideBarContainerType arg is wrong");
            return;
        }
    }

    NG::SideBarContainerView::SetSideBarContainerType(style);
}

void JSSideBar::SetShowControlButton(bool isShow)
{
    if (Container::IsCurrentUseNewPipeline()) {
        NG::SideBarContainerView::SetShowControlButton(isShow);
        return;
    }

    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::SideBarContainerComponent>(stack->GetMainComponent());
    if (!component) {
        LOGE("side bar is null");
        return;
    }

    component->SetShowControlButton(isShow);
}

void JSSideBar::JsSideBarPosition(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 arguments");
        return;
    }
    SideBarPosition sideBarPosition = SideBarPosition::START;
    if (info[0]->IsNumber()) {
        sideBarPosition = static_cast<SideBarPosition>(info[0]->ToNumber<int>());
    } else {
        LOGE("The arg is wrong");
        return;
    }

    if (Container::IsCurrentUseNewPipeline()) {
        NG::SideBarContainerView::SetSideBarPosition(sideBarPosition);
        return;
    }

    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<SideBarContainerComponent>(stack->GetMainComponent());
    if (!component) {
        LOGE("side bar is null");
        return;
    }

    component->SetSideBarPosition(sideBarPosition);
}

void JSSideBar::JSBind(BindingTarget globalObj)
{
    JSClass<JSSideBar>::Declare("SideBarContainer");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSSideBar>::StaticMethod("create", &JSSideBar::Create, opt);
    JSClass<JSSideBar>::StaticMethod("pop", &JSSideBar::Pop);
    JSClass<JSSideBar>::StaticMethod("showSideBar", &JSSideBar::JsShowSideBar);
    JSClass<JSSideBar>::StaticMethod("controlButton", &JSSideBar::JsControlButton);
    JSClass<JSSideBar>::StaticMethod("showControlButton", &JSSideBar::SetShowControlButton);
    JSClass<JSSideBar>::StaticMethod("onChange", &JSSideBar::OnChange);
    JSClass<JSSideBar>::StaticMethod("sideBarWidth", &JSSideBar::JsSideBarWidth);
    JSClass<JSSideBar>::StaticMethod("minSideBarWidth", &JSSideBar::JsMinSideBarWidth);
    JSClass<JSSideBar>::StaticMethod("maxSideBarWidth", &JSSideBar::JsMaxSideBarWidth);
    JSClass<JSSideBar>::StaticMethod("autoHide", &JSSideBar::JsAutoHide);
    JSClass<JSSideBar>::StaticMethod("sideBarPosition", &JSSideBar::JsSideBarPosition);
    JSClass<JSSideBar>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSSideBar>::StaticMethod("width", SetWidth);
    JSClass<JSSideBar>::StaticMethod("height", SetHeight);
    JSClass<JSSideBar>::StaticMethod("size", SetSize);
    JSClass<JSSideBar>::StaticMethod("width", &JSStack::SetWidth);
    JSClass<JSSideBar>::StaticMethod("height", &JSStack::SetHeight);
    JSClass<JSSideBar>::StaticMethod("size", &JSStack::SetSize);
    JSClass<JSSideBar>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSSideBar>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSSideBar>::StaticMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSSideBar>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSSideBar>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSSideBar>::Inherit<JSContainerBase>();
    JSClass<JSSideBar>::Inherit<JSViewAbstract>();
    JSClass<JSSideBar>::Bind(globalObj);
}

void JSSideBar::OnChange(const JSCallbackInfo& info)
{
    if (Container::IsCurrentUseNewPipeline()) {
        if (info.Length() < 1 || !info[0]->IsFunction()) {
            LOGE("JSSideBar::OnChange info param is wrong.");
            return;
        }

        auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
        auto onChange = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc)](bool isShow) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("SideBarContainer.onChange");
            auto newJSVal = JSRef<JSVal>::Make(ToJSValue(isShow));
            func->ExecuteJS(1, &newJSVal);
        };
        NG::SideBarContainerView::SetOnChange(std::move(onChange));
        return;
    }

    if (!JSViewBindEvent(&SideBarContainerComponent::SetOnChange, info)) {
        LOGE("Failed to bind event");
    }
    info.ReturnSelf();
}

void JSSideBar::JsSideBarWidth(const JSCallbackInfo& info)
{
    ParseAndSetWidth(info, WidthType::SIDEBAR_WIDTH);
}

void JSSideBar::JsMaxSideBarWidth(const JSCallbackInfo& info)
{
    ParseAndSetWidth(info, WidthType::MAX_SIDEBAR_WIDTH);
}

void JSSideBar::JsMinSideBarWidth(const JSCallbackInfo& info)
{
    ParseAndSetWidth(info, WidthType::MIN_SIDEBAR_WIDTH);
}

void JSSideBar::JsShowSideBar(bool isShow)
{
    if (Container::IsCurrentUseNewPipeline()) {
        NG::SideBarContainerView::SetShowSideBar(isShow);
        return;
    }

    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::SideBarContainerComponent>(stack->GetMainComponent());
    if (!component) {
        LOGE("side bar is null");
        return;
    }
    component->SetShowSideBar(isShow);
}

void JSSideBar::JsControlButton(const JSCallbackInfo& info)
{
    if (Container::IsCurrentUseNewPipeline()) {
        JsControlButtonForNG(info);
        return;
    }

    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::SideBarContainerComponent>(stack->GetMainComponent());
    if (!component) {
        LOGE("side bar is null");
        return;
    }

    if (!info[0]->IsNull() && info[0]->IsObject()) {
        JSRef<JSObject> value = JSRef<JSObject>::Cast(info[0]);
        JSRef<JSVal> width = value->GetProperty("width");
        JSRef<JSVal> height = value->GetProperty("height");
        JSRef<JSVal> left = value->GetProperty("left");
        JSRef<JSVal> top = value->GetProperty("top");
        JSRef<JSVal> icons = value->GetProperty("icons");

        if (!width->IsNull() && width->IsNumber()) {
            auto controlButtonWidth = width->ToNumber<double>();
            if (LessNotEqual(controlButtonWidth, 0.0)) {
                controlButtonWidth = DEFAULT_CONTROL_BUTTON_WIDTH.Value();
            }
            component->SetButtonWidth(controlButtonWidth);
        }

        if (!height->IsNull() && height->IsNumber()) {
            auto controlButtonHeight = height->ToNumber<double>();
            if (LessNotEqual(controlButtonHeight, 0.0)) {
                controlButtonHeight = DEFAULT_CONTROL_BUTTON_HEIGHT.Value();
            }
            component->SetButtonHeight(controlButtonHeight);
        }

        if (!left->IsNull() && left->IsNumber()) {
            component->SetButtonLeft(left->ToNumber<double>());
        }

        if (!top->IsNull() && top->IsNumber()) {
            component->SetButtonTop(top->ToNumber<double>());
        }

        if (!icons->IsNull() && icons->IsObject()) {
            JSRef<JSObject> iconsVal = JSRef<JSObject>::Cast(icons);
            JSRef<JSVal> showIcon = iconsVal->GetProperty("shown");
            JSRef<JSVal> switchingIcon = iconsVal->GetProperty("switching");
            JSRef<JSVal> hiddenIcon = iconsVal->GetProperty("hidden");
            std::string showIconStr;
            if (!showIcon->IsNull() && ParseJsMedia(showIcon, showIconStr)) {
                component->SetShowIcon(showIconStr);
            }
            std::string hiddenIconStr;
            if (!hiddenIcon->IsNull() && ParseJsMedia(hiddenIcon, hiddenIconStr)) {
                component->SetHiddenIcon(hiddenIconStr);
            }
            std::string switchingIconStr;
            if (!switchingIcon->IsNull() && ParseJsMedia(switchingIcon, switchingIconStr)) {
                component->SetSwitchIcon(switchingIconStr);
            }
        }
    }
}

void JSSideBar::JsControlButtonForNG(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("JSSideBar::JsControlButtonForNG The arg is wrong, it is supposed to have at least 1 arguments");
        return;
    }

    if (!info[0]->IsNull() && info[0]->IsObject()) {
        JSRef<JSObject> value = JSRef<JSObject>::Cast(info[0]);
        JSRef<JSVal> width = value->GetProperty("width");
        JSRef<JSVal> height = value->GetProperty("height");
        JSRef<JSVal> left = value->GetProperty("left");
        JSRef<JSVal> top = value->GetProperty("top");
        JSRef<JSVal> icons = value->GetProperty("icons");

        if (!width->IsNull() && width->IsNumber()) {
            auto controlButtonWidth = Dimension(width->ToNumber<double>(), DimensionUnit::VP);
            if (LessNotEqual(controlButtonWidth.Value(), 0.0)) {
                controlButtonWidth = DEFAULT_CONTROL_BUTTON_WIDTH;
            }
            NG::SideBarContainerView::SetControlButtonWidth(controlButtonWidth);
        }

        if (!height->IsNull() && height->IsNumber()) {
            auto controlButtonHeight = Dimension(height->ToNumber<double>(), DimensionUnit::VP);
            if (LessNotEqual(controlButtonHeight.Value(), 0.0)) {
                controlButtonHeight = DEFAULT_CONTROL_BUTTON_HEIGHT;
            }
            NG::SideBarContainerView::SetControlButtonHeight(controlButtonHeight);
        }

        if (!left->IsNull() && left->IsNumber()) {
            NG::SideBarContainerView::SetControlButtonLeft(Dimension(left->ToNumber<double>(), DimensionUnit::VP));
        }

        if (!top->IsNull() && top->IsNumber()) {
            NG::SideBarContainerView::SetControlButtonTop(Dimension(top->ToNumber<double>(), DimensionUnit::VP));
        }

        if (!icons->IsNull() && icons->IsObject()) {
            JSRef<JSObject> iconsVal = JSRef<JSObject>::Cast(icons);
            JSRef<JSVal> showIcon = iconsVal->GetProperty("shown");
            JSRef<JSVal> switchingIcon = iconsVal->GetProperty("switching");
            JSRef<JSVal> hiddenIcon = iconsVal->GetProperty("hidden");
            std::string showIconStr;
            if (!showIcon->IsNull() && ParseJsMedia(showIcon, showIconStr)) {
                NG::SideBarContainerView::SetControlButtonShowIconStr(showIconStr);
            }
            std::string hiddenIconStr;
            if (!hiddenIcon->IsNull() && ParseJsMedia(hiddenIcon, hiddenIconStr)) {
                NG::SideBarContainerView::SetControlButtonHiddenIconStr(hiddenIconStr);
            }
            std::string switchingIconStr;
            if (!switchingIcon->IsNull() && ParseJsMedia(switchingIcon, switchingIconStr)) {
                NG::SideBarContainerView::SetControlButtonSwitchingIconStr(switchingIconStr);
            }
        }
    }
}

void JSSideBar::JsAutoHide(bool autoHide)
{
    if (Container::IsCurrentUseNewPipeline()) {
        NG::SideBarContainerView::SetAutoHide(autoHide);
        return;
    }

    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::SideBarContainerComponent>(stack->GetMainComponent());
    if (!component) {
        LOGE("side bar is null");
        return;
    }
    component->SetAutoHide(autoHide);
}

void JSSideBar::Pop()
{
    if (Container::IsCurrentUseNewPipeline()) {
        NG::SideBarContainerView::Pop();
        NG::ViewStackProcessor::GetInstance()->PopContainer();
        return;
    }

    ViewStackProcessor::GetInstance()->PopContainer();
}

} // namespace OHOS::Ace::Framework
