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
#include "frameworks/bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "frameworks/bridge/declarative_frontend/jsview/models/side_bar_container_model_impl.h"

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
constexpr Dimension DEFAULT_CONTROL_BUTTON_TOP = 48.0_vp;
constexpr Dimension DEFAULT_DIVIDER_STROKE_WIDTH = 1.0_vp;
constexpr Dimension DEFAULT_DIVIDER_START_MARGIN = 0.0_vp;
constexpr Dimension DEFAULT_DIVIDER_END_MARGIN = 0.0_vp;
static Dimension DEFAULT_SIDE_BAR_WIDTH = 200.0_vp;
static Dimension DEFAULT_MIN_SIDE_BAR_WIDTH = 200.0_vp;
constexpr Dimension DEFAULT_MAX_SIDE_BAR_WIDTH = 280.0_vp;
constexpr Color DEFAULT_DIVIDER_COLOR = Color(0x08000000);

void ParseAndSetWidth(const JSCallbackInfo& info, WidthType widthType)
{
    if (info.Length() < 1) {
        return;
    }
    switch (widthType) {
        case WidthType::SIDEBAR_WIDTH:
            SideBarContainerModel::GetInstance()->ResetResObj("sideBarContainer.sideBarWidth");
            break;
        case WidthType::MIN_SIDEBAR_WIDTH:
            SideBarContainerModel::GetInstance()->ResetResObj("sideBarContainer.minSideBarWidth");
            break;
        case WidthType::MAX_SIDEBAR_WIDTH:
            SideBarContainerModel::GetInstance()->ResetResObj("sideBarContainer.maxSideBarWidth");
            break;
        default:
            break;
    }

    CalcDimension value;
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
        DEFAULT_SIDE_BAR_WIDTH = 240.0_vp;
        DEFAULT_MIN_SIDE_BAR_WIDTH = 240.0_vp;
    }

    RefPtr<ResourceObject> valueResObj;
    auto isValid = Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)
                       ? JSViewAbstract::ParseJsDimensionVpNG(info[0], value, valueResObj)
                       : JSViewAbstract::ParseJsDimensionVp(info[0], value, valueResObj);
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
    if (SystemProperties::ConfigChangePerform() && valueResObj) {
        SideBarContainerModel::GetInstance()->ParseAndSetWidth(widthType, valueResObj);
        return;
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
            return;
        }
    }
    SideBarContainerModel::GetInstance()->SetSideBarContainerType(style);
}

void JSSideBar::SetShowControlButton(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    if (info[0]->IsNull() || info[0]->IsUndefined()) {
        if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
            // showControlButton set default true when input illegal value
            SideBarContainerModel::GetInstance()->SetShowControlButton(true);
        }
        return;
    }
    if (info[0]->IsBoolean()) {
        SideBarContainerModel::GetInstance()->SetShowControlButton(info[0]->ToBoolean());
    }
}

void JSSideBar::JsSideBarPosition(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    if (info[0]->IsNull() || info[0]->IsUndefined()) {
        if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
            // sideBarPosition set default START when input illegal value
            SideBarContainerModel::GetInstance()->SetSideBarPosition(SideBarPosition::START);
        }
        return;
    }
    if (info[0]->IsNumber() && info[0]->ToNumber<int32_t>() >= 0 && info[0]->ToNumber<int32_t>() <= 1) {
        SideBarContainerModel::GetInstance()->SetSideBarPosition(
            static_cast<SideBarPosition>(info[0]->ToNumber<int32_t>()));
    }
}

void JSSideBar::JSBind(BindingTarget globalObj)
{
    JSClass<JSSideBar>::Declare("SideBarContainer");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSSideBar>::StaticMethod("create", &JSSideBar::Create, opt);
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
    JSClass<JSSideBar>::StaticMethod("onAttach", &JSInteractableView::JsOnAttach);
    JSClass<JSSideBar>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSSideBar>::StaticMethod("onDetach", &JSInteractableView::JsOnDetach);
    JSClass<JSSideBar>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSSideBar>::InheritAndBind<JSContainerBase>(globalObj);
}

void JSSideBar::OnChange(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsFunction()) {
        return;
    }

    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onChange = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), node = targetNode](bool isShow) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("SideBarContainer.onChange");
        PipelineContext::SetCallBackNode(node);
        auto newJSVal = JSRef<JSVal>::Make(ToJSValue(isShow));
        func->ExecuteJS(1, &newJSVal);
    };
    SideBarContainerModel::GetInstance()->SetOnChange(std::move(onChange));
    info.ReturnSelf();
}

void ParseSideBarWidthObject(const JSCallbackInfo& info, JSRef<JSVal> arrowFunc, bool isNumber)
{
    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(arrowFunc));
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onChangeEvent = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc),
                        node = targetNode, useNumber = isNumber](const Dimension& sideBarWidth) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("SideBarContainer.onSideBarWidthChangeEvent");
        PipelineContext::SetCallBackNode(node);
        auto newJSVal = useNumber ? JSRef<JSVal>::Make(ToJSValue(sideBarWidth.ConvertToVp())) :
            JSRef<JSVal>::Make(ToJSValue(sideBarWidth.ToString()));
        func->ExecuteJS(1, &newJSVal);
    };
    SideBarContainerModel::GetInstance()->SetOnSideBarWidthChangeEvent(std::move(onChangeEvent));
}

void JSSideBar::JsSideBarWidth(const JSCallbackInfo& info)
{
    if (info[0]->IsObject()) {
        JSRef<JSObject> callbackObj = JSRef<JSObject>::Cast(info[0]);
        CalcDimension value;
        auto sideBarWidthValue = callbackObj->GetProperty("value");
        auto sideBarWidthCallbackValue = callbackObj->GetProperty("$value");
        auto isValid = JSViewAbstract::ParseJsDimensionVpNG(sideBarWidthValue, value);
        bool isNumber = sideBarWidthValue->IsNumber();
        if (isValid && sideBarWidthCallbackValue->IsFunction()) {
            SideBarContainerModel::GetInstance()->ParseAndSetWidth(WidthType::SIDEBAR_WIDTH, value, true);
            ParseSideBarWidthObject(info, sideBarWidthCallbackValue, isNumber);
            return;
        }
    }
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
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onChangeEvent = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), node = targetNode](
                             bool isShow) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("SideBarContainer.onChangeEvent");
        PipelineContext::SetCallBackNode(node);
        auto newJSVal = JSRef<JSVal>::Make(ToJSValue(isShow));
        func->ExecuteJS(1, &newJSVal);
    };
    SideBarContainerModel::GetInstance()->SetOnChangeEvent(std::move(onChangeEvent));
}

void JSSideBar::JsShowSideBar(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || info.Length() > 2) {
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
        return;
    }
    std::string iconPath;
    RefPtr<ResourceObject> iconPathResObj;
    auto isStrType = ParseJsMedia(icon, iconPath, iconPathResObj);
    RefPtr<PixelMap> pixMap = nullptr;
#if defined(PIXEL_MAP_SUPPORTED)
    if (!isStrType) {
        pixMap = CreatePixelMapFromNapiValue(icon);
    }
#endif
    bool isNewframework = iconPathResObj && SystemProperties::ConfigChangePerform();
    if (isStrType || pixMap != nullptr) {
        switch (iconType) {
            case SideBarControlButtonType::SHOWN:
                if (isNewframework) {
                    SideBarContainerModel::GetInstance()->SetControlButtonShowIconInfo(
                        iconPathResObj, !isStrType, pixMap);
                } else {
                    SideBarContainerModel::GetInstance()->SetControlButtonShowIconInfo(iconPath, !isStrType, pixMap);
                }
                break;
            case SideBarControlButtonType::HIDDEN:
                if (isNewframework) {
                    SideBarContainerModel::GetInstance()->SetControlButtonHiddenIconInfo(
                        iconPathResObj, !isStrType, pixMap);
                } else {
                    SideBarContainerModel::GetInstance()->SetControlButtonHiddenIconInfo(iconPath, !isStrType, pixMap);
                }
                break;
            case SideBarControlButtonType::SWITCHING:
                if (isNewframework) {
                    SideBarContainerModel::GetInstance()->SetControlButtonSwitchingIconInfo(
                        iconPathResObj, !isStrType, pixMap);
                } else {
                    SideBarContainerModel::GetInstance()->SetControlButtonSwitchingIconInfo(
                        iconPath, !isStrType, pixMap);
                }
                break;
            default:
                break;
        }
    }
}

void JSSideBar::JsControlButton(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    SideBarContainerModel::GetInstance()->ResetResObj("sideBarContainer.buttonIconOptions.shown");
    SideBarContainerModel::GetInstance()->ResetResObj("sideBarContainer.buttonIconOptions.hidden");
    SideBarContainerModel::GetInstance()->ResetResObj("sideBarContainer.buttonIconOptions.switching");
    if (info[0]->IsNull() || info[0]->IsUndefined()) {
        if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
            // controlButton icon set default style and position when input illegal value
            SideBarContainerModel::GetInstance()->ResetControlButton();
        }
        return;
    }
    if (info[0]->IsObject()) {
        JSRef<JSObject> value = JSRef<JSObject>::Cast(info[0]);
        if (!AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TEN)) {
            ParseControlButtonOG(value);
        } else {
            ParseControlButtonNG(value);
        }

        JSRef<JSVal> icons = value->GetProperty("icons");
        if (icons->IsNull() || icons->IsUndefined()) {
            if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
                // controlButton icon set default style when input illegal value
                SideBarContainerModel::GetInstance()->ResetControlButtonIconInfo();
            }
            return;
        }
        if (icons->IsObject()) {
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

void JSSideBar::ProcessDividerProperties(const JSRef<JSObject>& obj)
{
    Dimension strokeWidth = DEFAULT_DIVIDER_STROKE_WIDTH;
    RefPtr<ResourceObject> strokeWidthResObj;
    if (!ConvertFromJSValueNG(obj->GetProperty("strokeWidth"), strokeWidth, strokeWidthResObj) ||
        (strokeWidth.Value() < 0.0f)) {
        strokeWidth = DEFAULT_DIVIDER_STROKE_WIDTH;
    }
    if (SystemProperties::ConfigChangePerform() && strokeWidthResObj) {
        SideBarContainerModel::GetInstance()->SetDividerStrokeWidth(strokeWidthResObj);
    } else {
        SideBarContainerModel::GetInstance()->SetDividerStrokeWidth(strokeWidth);
    }

    Color color = DEFAULT_DIVIDER_COLOR;
    RefPtr<ResourceObject> colorResObj;
    if (!ConvertFromJSValue(obj->GetProperty("color"), color, colorResObj)) {
        color = DEFAULT_DIVIDER_COLOR;
    }
    if (SystemProperties::ConfigChangePerform() && colorResObj) {
        SideBarContainerModel::GetInstance()->SetDividerColor(colorResObj);
    } else {
        SideBarContainerModel::GetInstance()->SetDividerColor(color);
    }

    Dimension startMargin = DEFAULT_DIVIDER_START_MARGIN;
    RefPtr<ResourceObject> startMarginResObj;
    if (!ConvertFromJSValueNG(obj->GetProperty("startMargin"), startMargin, startMarginResObj) ||
        (startMargin.Value() < 0.0f)) {
        startMargin = DEFAULT_DIVIDER_START_MARGIN;
    }
    if (SystemProperties::ConfigChangePerform() && startMarginResObj) {
        SideBarContainerModel::GetInstance()->SetDividerStartMargin(startMarginResObj);
    } else {
        SideBarContainerModel::GetInstance()->SetDividerStartMargin(startMargin);
    }

    Dimension endMargin = DEFAULT_DIVIDER_END_MARGIN;
    RefPtr<ResourceObject> endMarginResObj;
    if (!ConvertFromJSValueNG(obj->GetProperty("endMargin"), endMargin, endMarginResObj) ||
        (endMargin.Value() < 0.0f)) {
        endMargin = DEFAULT_DIVIDER_END_MARGIN;
    }
    if (SystemProperties::ConfigChangePerform() && endMarginResObj) {
        SideBarContainerModel::GetInstance()->SetDividerEndMargin(endMarginResObj);
    } else {
        SideBarContainerModel::GetInstance()->SetDividerEndMargin(endMargin);
    }
}

void JSSideBar::JsDivider(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    SideBarContainerModel::GetInstance()->ResetResObj("sideBarContainer.dividerStyle.strokeWidth");
    SideBarContainerModel::GetInstance()->ResetResObj("sideBarContainer.dividerStyle.color");
    SideBarContainerModel::GetInstance()->ResetResObj("sideBarContainer.dividerStyle.startMargin");
    SideBarContainerModel::GetInstance()->ResetResObj("sideBarContainer.dividerStyle.endMargin");
    if (info[0]->IsNull() || info[0]->IsUndefined()) {
        if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
            // sideBar divider set default width when input illegal value
            SideBarContainerModel::GetInstance()->SetDividerStrokeWidth(DEFAULT_DIVIDER_STROKE_WIDTH);
        } else if (info[0]->IsNull()) {
            SideBarContainerModel::GetInstance()->SetDividerStrokeWidth(0.0_vp);
        }
        return;
    }
    if (info[0]->IsObject()) {
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(info[0]);
        ProcessDividerProperties(obj);
    }
}

void JSSideBar::JsMinContentWidth(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    SideBarContainerModel::GetInstance()->ResetResObj("sideBarContainer.minContentWidth");
    if (info[0]->IsNull()) {
        SideBarContainerModel::GetInstance()->SetMinContentWidth(-1.0_vp);
        return;
    }
    CalcDimension minContentWidth;
    RefPtr<ResourceObject> valueResObj;
    if (!JSViewAbstract::ParseJsDimensionVp(info[0], minContentWidth, valueResObj)) {
        SideBarContainerModel::GetInstance()->SetMinContentWidth(-1.0_vp);
        return;
    }
    if (SystemProperties::ConfigChangePerform() && valueResObj) {
        SideBarContainerModel::GetInstance()->SetMinContentWidth(valueResObj);
        return;
    }
    SideBarContainerModel::GetInstance()->SetMinContentWidth(minContentWidth);
}

void JSSideBar::JsAutoHide(bool autoHide)
{
    SideBarContainerModel::GetInstance()->SetAutoHide(autoHide);
}

void JSSideBar::ParseControlButtonOG(JSRef<JSObject> value)
{
    JSRef<JSVal> width = value->GetProperty("width");
    JSRef<JSVal> height = value->GetProperty("height");
    JSRef<JSVal> left = value->GetProperty("left");
    JSRef<JSVal> top = value->GetProperty("top");

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
        SideBarContainerModel::GetInstance()->SetControlButtonLeft(
            Dimension(left->ToNumber<double>(), DimensionUnit::VP));
    }

    if (!top->IsNull() && top->IsNumber()) {
        SideBarContainerModel::GetInstance()->SetControlButtonTop(
            Dimension(top->ToNumber<double>(), DimensionUnit::VP));
    }
}

void JSSideBar::ParseControlButtonNG(JSRef<JSObject> value)
{
    JSRef<JSVal> width = value->GetProperty("width");
    JSRef<JSVal> height = value->GetProperty("height");
    JSRef<JSVal> left = value->GetProperty("left");
    JSRef<JSVal> top = value->GetProperty("top");

    auto controlButtonWidth = DEFAULT_CONTROL_BUTTON_WIDTH;
    if (width->IsNumber() && GreatOrEqual(width->ToNumber<double>(), 0.0)) {
        controlButtonWidth = CalcDimension(width->ToNumber<double>(), DimensionUnit::VP);
    }
    SideBarContainerModel::GetInstance()->SetControlButtonWidth(controlButtonWidth);

    auto controlButtonHeight = DEFAULT_CONTROL_BUTTON_HEIGHT;
    if (height->IsNumber() && GreatOrEqual(height->ToNumber<double>(), 0.0)) {
        controlButtonHeight = CalcDimension(height->ToNumber<double>(), DimensionUnit::VP);
    }
    SideBarContainerModel::GetInstance()->SetControlButtonHeight(controlButtonHeight);

    if (left->IsNumber() && GreatOrEqual(left->ToNumber<double>(), 0.0)) {
        auto controlButtonLeft = CalcDimension(left->ToNumber<double>(), DimensionUnit::VP);
        SideBarContainerModel::GetInstance()->SetControlButtonLeft(controlButtonLeft);
    } else {
        SideBarContainerModel::GetInstance()->ResetControlButtonLeft();
    }

    auto controlButtonTop = DEFAULT_CONTROL_BUTTON_TOP;
    if (top->IsNumber() && GreatOrEqual(top->ToNumber<double>(), 0.0)) {
        controlButtonTop = CalcDimension(top->ToNumber<double>(), DimensionUnit::VP);
    }
    SideBarContainerModel::GetInstance()->SetControlButtonTop(controlButtonTop);
}

} // namespace OHOS::Ace::Framework
