/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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
#include "base/image/pixel_map.h"
#include "base/log/ace_scoring_log.h"
#include "base/log/log.h"
#include "bridge/declarative_frontend/engine/js_ref_ptr.h"
#include "bridge/declarative_frontend/engine/js_types.h"
#include "bridge/declarative_frontend/jsview/js_utils.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/side_bar/side_bar_container_model_ng.h"
#include "frameworks/bridge/declarative_frontend/jsview/models/side_bar_container_model_impl.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_common_def.h"

namespace OHOS::Ace {
std::unique_ptr<SideBarContainerModel> SideBarContainerModel::instance_ = nullptr;
std::mutex SideBarContainerModel::mutex_;

SideBarContainerModel* SideBarContainerModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
#ifdef NG_BUILD
            instance_.reset(new NG::SideBarContainerModelNG());
#else
            if (Container::IsCurrentUseNewPipeline()) {
                instance_.reset(new NG::SideBarContainerModelNG());
            } else {
                instance_.reset(new Framework::SideBarContainerModelImpl());
            }
#endif
        }
    }
    return instance_.get();
}
} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {
namespace {
constexpr Dimension DEFAULT_CONTROL_BUTTON_WIDTH = 32.0_vp;
constexpr Dimension DEFAULT_CONTROL_BUTTON_HEIGHT = 32.0_vp;
constexpr Dimension DEFAULT_DIVIDER_STROKE_WIDTH = 1.0_vp;
constexpr Dimension DEFAULT_DIVIDER_START_MARGIN = 0.0_vp;
constexpr Dimension DEFAULT_DIVIDER_END_MARGIN = 0.0_vp;
constexpr Dimension DEFAULT_SIDE_BAR_WIDTH = 200.0_vp;
constexpr Dimension DEFAULT_MIN_SIDE_BAR_WIDTH = 200.0_vp;
constexpr Dimension DEFAULT_MAX_SIDE_BAR_WIDTH = 280.0_vp;
constexpr Color DEFAULT_DIVIDER_COLOR = Color(0x08000000);
constexpr int32_t PLATFORM_VERSION_TEN = 10;

void ParseAndSetWidth(const JSCallbackInfo& info, WidthType widthType)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 arguments");
        return;
    }

    CalcDimension value;
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);

    auto isValid = pipeline->GetMinPlatformVersion() >= PLATFORM_VERSION_TEN
                       ? JSViewAbstract::ParseJsDimensionVpNG(info[0], value)
                       : JSViewAbstract::ParseJsDimensionVp(info[0], value);

    if (!isValid) {
        switch (widthType) {
            case WidthType::SIDEBAR_WIDTH:
                value = DEFAULT_SIDE_BAR_WIDTH;
                break;
            case WidthType::MIN_SIDEBAR_WIDTH:
                value = DEFAULT_MIN_SIDE_BAR_WIDTH;
                break;
            case WidthType::MAX_SIDEBAR_WIDTH:
                value = DEFAULT_MAX_SIDE_BAR_WIDTH;
                break;
            default:
                break;
        }
    }
    SideBarContainerModel::GetInstance()->ParseAndSetWidth(widthType, value);
}
} // namespace

void JSSideBar::Create(const JSCallbackInfo& info)
{
    SideBarContainerModel::GetInstance()->Create();
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
    SideBarContainerModel::GetInstance()->SetSideBarContainerType(style);
}

void JSSideBar::SetShowControlButton(bool isShow)
{
    SideBarContainerModel::GetInstance()->SetShowControlButton(isShow);
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
    SideBarContainerModel::GetInstance()->SetSideBarPosition(sideBarPosition);
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
    JSClass<JSSideBar>::StaticMethod("divider", &JSSideBar::JsDivider);
    JSClass<JSSideBar>::StaticMethod("minContentWidth", &JSSideBar::JsMinContentWidth);
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
    JSClass<JSSideBar>::InheritAndBind<JSContainerBase>(globalObj);
}

void JSSideBar::OnChange(const JSCallbackInfo& info)
{
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
    SideBarContainerModel::GetInstance()->SetOnChange(std::move(onChange));
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

void ParseShowSideBarObject(const JSCallbackInfo& args, const JSRef<JSVal>& changeEventVal)
{
    CHECK_NULL_VOID(changeEventVal->IsFunction());

    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(changeEventVal));
    auto onChangeEvent = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc)](bool isShow) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("SideBarContainer.onChangeEvent");
        auto newJSVal = JSRef<JSVal>::Make(ToJSValue(isShow));
        func->ExecuteJS(1, &newJSVal);
    };
    SideBarContainerModel::GetInstance()->SetOnChangeEvent(std::move(onChangeEvent));
}

void JSSideBar::JsShowSideBar(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || info.Length() > 2) {
        LOGE("The arg is wrong, it is supposed to have 1 or 2 arguments");
        return;
    }

    bool isShow = true;
    if (info.Length() > 0 && info[0]->IsBoolean()) {
        isShow = info[0]->ToBoolean();
    }

    SideBarContainerModel::GetInstance()->SetShowSideBar(isShow);
    if (info.Length() > 1 && info[1]->IsFunction()) {
        ParseShowSideBarObject(info, info[1]);
    }
}

void JSSideBar::SetControlButtonIcon(SideBarControlButtonType iconType, JSRef<JSVal> icon)
{
    if (icon->IsUndefined() || icon->IsNull()) {
        LOGE("SetControlButtonIcon icon parse failed, icon is null.");
        return;
    }
    std::string iconPath;
    auto isStrType = ParseJsMedia(icon, iconPath);
    RefPtr<PixelMap> pixMap = nullptr;
#if defined (PIXEL_MAP_SUPPORTED)
    if (!isStrType) {
        pixMap = CreatePixelMapFromNapiValue(icon);
    }
#endif
    if (isStrType || pixMap != nullptr) {
        switch (iconType) {
            case SideBarControlButtonType::SHOWN:
                SideBarContainerModel::GetInstance()->SetControlButtonShowIconInfo(
                    iconPath, !isStrType, pixMap);
                break;
            case SideBarControlButtonType::HIDDEN:
                SideBarContainerModel::GetInstance()->SetControlButtonHiddenIconInfo(
                    iconPath, !isStrType, pixMap);
                break;
            case SideBarControlButtonType::SWITCHING:
                SideBarContainerModel::GetInstance()->SetControlButtonSwitchingIconInfo(
                    iconPath, !isStrType, pixMap);
                break;
            default:
                break;
        }
    }
}

void JSSideBar::JsControlButton(const JSCallbackInfo& info)
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
            auto controlButtonWidth = CalcDimension(width->ToNumber<double>(), DimensionUnit::VP);
            if (LessNotEqual(controlButtonWidth.Value(), 0.0)) {
                controlButtonWidth = DEFAULT_CONTROL_BUTTON_WIDTH;
            }
            SideBarContainerModel::GetInstance()->SetControlButtonWidth(controlButtonWidth);
        }

        if (!height->IsNull() && height->IsNumber()) {
            auto controlButtonHeight = CalcDimension(height->ToNumber<double>(), DimensionUnit::VP);
            if (LessNotEqual(controlButtonHeight.Value(), 0.0)) {
                controlButtonHeight = DEFAULT_CONTROL_BUTTON_HEIGHT;
            }
            SideBarContainerModel::GetInstance()->SetControlButtonHeight(controlButtonHeight);
        }

        if (!left->IsNull() && left->IsNumber()) {
            SideBarContainerModel::GetInstance()->SetControlButtonLeft(Dimension(left->ToNumber<double>(),
                DimensionUnit::VP));
        }

        if (!top->IsNull() && top->IsNumber()) {
            SideBarContainerModel::GetInstance()->SetControlButtonTop(Dimension(top->ToNumber<double>(),
                DimensionUnit::VP));
        }

        if (!icons->IsNull() && icons->IsObject()) {
            JSRef<JSObject> iconsVal = JSRef<JSObject>::Cast(icons);
            JSRef<JSVal> showIcon = iconsVal->GetProperty("shown");
            JSRef<JSVal> switchingIcon = iconsVal->GetProperty("switching");
            JSRef<JSVal> hiddenIcon = iconsVal->GetProperty("hidden");
            SetControlButtonIcon(SideBarControlButtonType::SHOWN, showIcon);
            SetControlButtonIcon(SideBarControlButtonType::HIDDEN, hiddenIcon);
            SetControlButtonIcon(SideBarControlButtonType::SWITCHING, switchingIcon);
        }
    }
}

void JSSideBar::JsDivider(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("Invalid params");
        return;
    }

    if (info[0]->IsNull()) {
        SideBarContainerModel::GetInstance()->SetDividerStrokeWidth(0.0_vp);
        return;
    }

    if (info[0]->IsObject()) {
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(info[0]);

        Dimension strokeWidth = DEFAULT_DIVIDER_STROKE_WIDTH;
        if (!ConvertFromJSValueNG(obj->GetProperty("strokeWidth"), strokeWidth) || (strokeWidth.Value() < 0.0f)) {
            strokeWidth = DEFAULT_DIVIDER_STROKE_WIDTH;
        }
        SideBarContainerModel::GetInstance()->SetDividerStrokeWidth(strokeWidth);

        Color color = DEFAULT_DIVIDER_COLOR;
        if (!ConvertFromJSValue(obj->GetProperty("color"), color)) {
            color = DEFAULT_DIVIDER_COLOR;
        }
        SideBarContainerModel::GetInstance()->SetDividerColor(color);

        Dimension startMargin = DEFAULT_DIVIDER_START_MARGIN;
        if (!ConvertFromJSValueNG(obj->GetProperty("startMargin"), startMargin) || (startMargin.Value() < 0.0f)) {
            startMargin = DEFAULT_DIVIDER_START_MARGIN;
        }
        SideBarContainerModel::GetInstance()->SetDividerStartMargin(startMargin);

        Dimension endMargin = DEFAULT_DIVIDER_END_MARGIN;
        if (!ConvertFromJSValueNG(obj->GetProperty("endMargin"), endMargin) || (endMargin.Value() < 0.0f)) {
            endMargin = DEFAULT_DIVIDER_END_MARGIN;
        }
        SideBarContainerModel::GetInstance()->SetDividerEndMargin(endMargin);
    }
}

void JSSideBar::JsMinContentWidth(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGW("JsMinContentWidth::Invalid params");
        return;
    }
    if (info[0]->IsNull()) {
        SideBarContainerModel::GetInstance()->SetMinContentWidth(-1.0_vp);
        LOGW("JsMinContentWidth::info[0]->IsNull()");
        return;
    }
    CalcDimension minContentWidth;
    if (!JSViewAbstract::ParseJsDimensionVp(info[0], minContentWidth)) {
        SideBarContainerModel::GetInstance()->SetMinContentWidth(-1.0_vp);
        LOGW("JsMinContentWidth::ParseJsDimensionVp Fail!!!");
        return;
    }
    SideBarContainerModel::GetInstance()->SetMinContentWidth(minContentWidth);
}

void JSSideBar::JsAutoHide(bool autoHide)
{
    SideBarContainerModel::GetInstance()->SetAutoHide(autoHide);
}

void JSSideBar::Pop()
{
    SideBarContainerModel::GetInstance()->Pop();
}

} // namespace OHOS::Ace::Framework
