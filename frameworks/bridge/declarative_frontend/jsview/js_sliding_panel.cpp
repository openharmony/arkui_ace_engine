/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/declarative_frontend/jsview/js_sliding_panel.h"

#include <algorithm>
#include <cstdint>
#include <iterator>

#include "base/log/ace_scoring_log.h"
#include "bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "bridge/declarative_frontend/jsview/models/sliding_panel_model_impl.h"
#include "core/components_ng/base/view_abstract_model_ng.h"
#include "core/components_ng/base/view_stack_model.h"
#include "core/components_ng/pattern/panel/sliding_panel_model.h"
#include "core/components_ng/pattern/panel/sliding_panel_model_ng.h"

namespace OHOS::Ace {

std::unique_ptr<SlidingPanelModel> SlidingPanelModel::instance_ = nullptr;
std::mutex SlidingPanelModel::mutex_;

SlidingPanelModel* SlidingPanelModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
#ifdef NG_BUILD
            instance_.reset(new NG::SlidingPanelModelNG());
#else
            if (Container::IsCurrentUseNewPipeline()) {
                instance_.reset(new NG::SlidingPanelModelNG());
            } else {
                instance_.reset(new Framework::SlidingPanelModelImpl());
            }
#endif
        }
    }
    return instance_.get();
}

} // namespace OHOS::Ace
namespace OHOS::Ace::Framework {
namespace {

const std::vector<PanelMode> PANEL_MODES = { PanelMode::MINI, PanelMode::HALF, PanelMode::FULL, PanelMode::AUTO };
const std::vector<PanelType> PANEL_TYPES = { PanelType::MINI_BAR, PanelType::FOLDABLE_BAR, PanelType::TEMP_DISPLAY,
    PanelType::CUSTOM };
const std::vector<VisibleType> PANEL_VISIBLE_TYPES = { VisibleType::GONE, VisibleType::VISIBLE,
    VisibleType::INVISIBLE };

const static bool DEFAULT_HASDRAGBAR = true;
const static bool DEFAULT_SHOWCLOSEICON = false;
const static PanelMode DEFAULT_PANELMODE = PanelMode::HALF;
const static PanelType DEFAULT_PANELTYPE = PanelType::FOLDABLE_BAR;
const std::string DEFAULT_BACKGROUND_MASK = "#08182431";
} // namespace

void JSSlidingPanel::Create(const JSCallbackInfo& info)
{
    if (info.Length() > 0 && info[0]->IsBoolean()) {
        bool isShow = true;
        isShow = info[0]->ToBoolean();
        SlidingPanelModel::GetInstance()->Create(isShow);
        return;
    }
}

void JSSlidingPanel::JSBind(BindingTarget globalObj)
{
    JSClass<JSSlidingPanel>::Declare("Panel");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSSlidingPanel>::StaticMethod("create", &JSSlidingPanel::Create, opt);
    JSClass<JSSlidingPanel>::StaticMethod("pop", &JSSlidingPanel::Pop, opt);
    JSClass<JSSlidingPanel>::StaticMethod("dragBar", &JSSlidingPanel::SetHasDragBar, opt);
    JSClass<JSSlidingPanel>::StaticMethod("show", &JSSlidingPanel::SetShow, opt);
    JSClass<JSSlidingPanel>::StaticMethod("showCloseIcon", &JSSlidingPanel::SetShowCloseIcon, opt);
    JSClass<JSSlidingPanel>::StaticMethod("mode", &JSSlidingPanel::SetPanelMode, opt);
    JSClass<JSSlidingPanel>::StaticMethod("type", &JSSlidingPanel::SetPanelType, opt);
    JSClass<JSSlidingPanel>::StaticMethod("customHeight", &JSSlidingPanel::SetCustomHeight, opt);
    JSClass<JSSlidingPanel>::StaticMethod("backgroundMask", &JSSlidingPanel::SetBackgroundMask, opt);
    JSClass<JSSlidingPanel>::StaticMethod("fullHeight", &JSSlidingPanel::SetFullHeight, opt);
    JSClass<JSSlidingPanel>::StaticMethod("halfHeight", &JSSlidingPanel::SetHalfHeight, opt);
    JSClass<JSSlidingPanel>::StaticMethod("miniHeight", &JSSlidingPanel::SetMiniHeight, opt);
    JSClass<JSSlidingPanel>::StaticMethod("backgroundColor", JsBackgroundColor);
    JSClass<JSSlidingPanel>::StaticMethod("border", JsPanelBorder);
    JSClass<JSSlidingPanel>::StaticMethod("borderWidth", JsPanelBorderWidth);
    JSClass<JSSlidingPanel>::StaticMethod("borderColor", JsPanelBorderColor);
    JSClass<JSSlidingPanel>::StaticMethod("borderStyle", JsPanelBorderStyle);
    JSClass<JSSlidingPanel>::StaticMethod("borderRadius", JsPanelBorderRadius);

    JSClass<JSSlidingPanel>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSSlidingPanel>::StaticMethod("onHover", &JSInteractableView::JsOnHover);
    JSClass<JSSlidingPanel>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSSlidingPanel>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSSlidingPanel>::StaticMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSSlidingPanel>::StaticMethod("onChange", &JSSlidingPanel::SetOnSizeChange);
    JSClass<JSSlidingPanel>::StaticMethod("onHeightChange", &JSSlidingPanel::SetOnHeightChange);
    JSClass<JSSlidingPanel>::StaticMethod("onAttach", &JSInteractableView::JsOnAttach);
    JSClass<JSSlidingPanel>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSSlidingPanel>::StaticMethod("onDetach", &JSInteractableView::JsOnDetach);
    JSClass<JSSlidingPanel>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);

    JSClass<JSSlidingPanel>::InheritAndBind<JSContainerBase>(globalObj);
}

void JSSlidingPanel::SetBackgroundMask(const JSCallbackInfo& info)
{
    Color color;
    if (info.Length() < 1) {
        color = Color::FromString(DEFAULT_BACKGROUND_MASK);
    } else if (!ParseJsColor(info[0], color)) {
        color = Color::FromString(DEFAULT_BACKGROUND_MASK);
    }

    SlidingPanelModel::GetInstance()->SetBackgroundMask(color);
}

void JSSlidingPanel::ParsePanelRadius(const JSRef<JSVal>& args, BorderRadius& borderRadius)
{
    if (!args->IsObject() && !args->IsNumber() && !args->IsString()) {
        return;
    }

    CalcDimension radius;
    if (ParseJsDimensionVp(args, radius)) {
        borderRadius.radiusTopLeft = radius;
        borderRadius.radiusTopRight = radius;
        borderRadius.radiusBottomLeft = radius;
        borderRadius.radiusBottomRight = radius;
        return;
    }
    if (args->IsObject()) {
        JSRef<JSObject> object = JSRef<JSObject>::Cast(args);
        auto valueTopLeft = object->GetProperty("topLeft");
        if (!valueTopLeft->IsUndefined()) {
            ParseJsDimensionVp(valueTopLeft, borderRadius.radiusTopLeft);
        }
        auto valueTopRight = object->GetProperty("topRight");
        if (!valueTopRight->IsUndefined()) {
            ParseJsDimensionVp(valueTopRight, borderRadius.radiusTopRight);
        }
        auto valueBottomLeft = object->GetProperty("bottomLeft");
        if (!valueBottomLeft->IsUndefined()) {
            ParseJsDimensionVp(valueBottomLeft, borderRadius.radiusBottomLeft);
        }
        auto valueBottomRight = object->GetProperty("bottomRight");
        if (!valueBottomRight->IsUndefined()) {
            ParseJsDimensionVp(valueBottomRight, borderRadius.radiusBottomRight);
        }
        return;
    }
}

void JSSlidingPanel::JsPanelBorderRadius(const JSCallbackInfo& info)
{
    BorderRadius borderRadius;
    ParsePanelRadius(info[0], borderRadius);

    ViewAbstractModel::GetInstance()->SetBorderRadius(borderRadius.radiusTopLeft, borderRadius.radiusTopRight,
        borderRadius.radiusBottomLeft, borderRadius.radiusBottomRight);
}

void JSSlidingPanel::JsBackgroundColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    Color backgroundColor;
    if (!ParseJsColor(info[0], backgroundColor)) {
        return;
    }

    SlidingPanelModel::GetInstance()->SetBackgroundColor(backgroundColor);
}

void JSSlidingPanel::JsPanelBorderColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    Color borderColor;
    if (!ParseJsColor(info[0], borderColor)) {
        return;
    }

    SlidingPanelModel::GetInstance()->SetBorderColor(borderColor);
}

void JSSlidingPanel::JsPanelBorderWidth(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    CalcDimension borderWidth;
    if (!ParseJsDimensionVp(info[0], borderWidth)) {
        return;
    }
    SlidingPanelModel::GetInstance()->SetBorderWidth(borderWidth);
}

void JSSlidingPanel::JsPanelBorderStyle(int32_t style)
{
    BorderStyle borderStyle = BorderStyle::SOLID;
    if (style > 0 && style < 4) {
        borderStyle = static_cast<BorderStyle>(style);
    }
    SlidingPanelModel::GetInstance()->SetBorderStyle(borderStyle);
}

void JSSlidingPanel::JsPanelBorder(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    if (!info[0]->IsObject()) {
        return;
    }

    auto argsPtrItem = JSRef<JSObject>::Cast(info[0]);
    CalcDimension width = CalcDimension(0.0, DimensionUnit::VP);
    ParseJsDimensionVp(argsPtrItem->GetProperty("width"), width);
    SlidingPanelModel::GetInstance()->SetBorderWidth(width);

    BorderRadius borderRadius;
    ParsePanelRadius(argsPtrItem->GetProperty("radius"), borderRadius);
    ViewAbstractModel::GetInstance()->SetBorderRadius(borderRadius.radiusTopLeft, borderRadius.radiusTopRight,
        borderRadius.radiusBottomLeft, borderRadius.radiusBottomRight);

    auto styleJsValue = argsPtrItem->GetProperty("style");
    auto borderStyle = BorderStyle::SOLID;
    if (!styleJsValue->IsUndefined() && styleJsValue->IsNumber()) {
        auto styleValue = styleJsValue->ToNumber<uint32_t>();
        if (styleValue > 0 && styleValue < 4) {
            borderStyle = static_cast<BorderStyle>(styleValue);
        }
    }
    SlidingPanelModel::GetInstance()->SetBorderStyle(borderStyle);

    Color borderColor;
    ParseJsColor(argsPtrItem->GetProperty("color"), borderColor);
    SlidingPanelModel::GetInstance()->SetBorderColor(borderColor);
}

void JSSlidingPanel::SetOnSizeChange(const JSCallbackInfo& args)
{
    if (!args[0]->IsFunction()) {
        return;
    }

    auto onSizeChangeNG = [execCtx = args.GetExecutionContext(), func = JSRef<JSFunc>::Cast(args[0])](
                              const BaseEventInfo* info) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        auto eventInfo = TypeInfoHelper::DynamicCast<SlidingPanelSizeChangeEvent>(info);
        if (!eventInfo) {
            return;
        }
        auto params = ConvertToJSValues(eventInfo->GetWidth(), eventInfo->GetHeight(), eventInfo->GetMode());
        ACE_SCORING_EVENT("SlidingPanel.OnSizeChange");
        func->Call(JSRef<JSObject>(), params.size(), params.data());
    };
    SlidingPanelModel::GetInstance()->SetOnSizeChange(onSizeChangeNG);

    args.ReturnSelf();
}

void JSSlidingPanel::SetOnHeightChange(const JSCallbackInfo& args)
{
    if (args.Length() < 1) {
        return;
    }
    if (!args[0]->IsFunction()) {
        return;
    }

    auto onHeightChangeCallback = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(args[0]));
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onHeightChange = [execCtx = args.GetExecutionContext(), func = std::move(onHeightChangeCallback),
                              node = targetNode](int32_t height) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("OnHeightChange");
        PipelineContext::SetCallBackNode(node);
        JSRef<JSVal> param = JSRef<JSVal>::Make(ToJSValue(height));
        func->ExecuteJS(1, &param);
    };

    SlidingPanelModel::GetInstance()->SetOnHeightChange(std::move(onHeightChange));

    args.ReturnSelf();
}

void JSSlidingPanel::SetHasDragBar(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    auto hasDragBar = DEFAULT_HASDRAGBAR;
    if (info[0]->IsBoolean()) {
        hasDragBar = info[0]->ToBoolean();
    }
    SlidingPanelModel::GetInstance()->SetHasDragBar(hasDragBar);
}

void JSSlidingPanel::SetShowCloseIcon(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    auto showCloseIcon = DEFAULT_SHOWCLOSEICON;
    if (info[0]->IsBoolean()) {
        showCloseIcon = info[0]->ToBoolean();
    }
    SlidingPanelModel::GetInstance()->SetShowCloseIcon(showCloseIcon);
}

void JSSlidingPanel::SetShow(const JSCallbackInfo& info)
{
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN) &&
        (info[0]->IsUndefined() || info[0]->IsNull())) {
        SlidingPanelModel::GetInstance()->SetIsShow(true);
    } else {
        SlidingPanelModel::GetInstance()->SetIsShow(info[0]->ToBoolean());
    }
}

void ParseModeObject(const JSCallbackInfo& info, const JSRef<JSVal>& changeEventVal)
{
    CHECK_NULL_VOID(changeEventVal->IsFunction());

    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(changeEventVal));
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onMode = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), node = targetNode](
                      const BaseEventInfo* baseEventInfo) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("SlidingPanel.ModeChangeEvent");
        auto eventInfo = TypeInfoHelper::DynamicCast<SlidingPanelSizeChangeEvent>(baseEventInfo);
        if (!eventInfo) {
            return;
        }
        PipelineContext::SetCallBackNode(node);
        auto newJSVal = JSRef<JSVal>::Make(ToJSValue(static_cast<int32_t>(eventInfo->GetMode())));
        func->ExecuteJS(1, &newJSVal);
    };
    SlidingPanelModel::GetInstance()->SetModeChangeEvent(std::move(onMode));
}

void JSSlidingPanel::SetPanelMode(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || info.Length() > 2) {
        return;
    }

    int32_t mode = static_cast<int32_t>(DEFAULT_PANELMODE);
    if (info.Length() > 0 && info[0]->IsNumber()) {
        const auto modeNumber = info[0]->ToNumber<int32_t>();
        if (modeNumber >= 0 && modeNumber < static_cast<int32_t>(PANEL_MODES.size())) {
            mode = modeNumber;
        }
    }

    if (info.Length() > 1 && info[1]->IsFunction()) {
        ParseModeObject(info, info[1]);
    }

    SlidingPanelModel::GetInstance()->SetPanelMode(PANEL_MODES[mode]);
}

void JSSlidingPanel::SetPanelType(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    auto type = static_cast<int32_t>(DEFAULT_PANELTYPE);
    if (info[0]->IsNumber()) {
        const auto typeNumber = info[0]->ToNumber<int32_t>();
        if (typeNumber >= 0 && typeNumber < static_cast<int32_t>(PANEL_TYPES.size())) {
            type = typeNumber;
        }
    }
    SlidingPanelModel::GetInstance()->SetPanelType(PANEL_TYPES[type]);
}

void JSSlidingPanel::SetCustomHeight(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    CalcDimension customHeight;
    if (info[0]->IsString() && info[0]->ToString().find("wrapContent") != std::string::npos) {
        customHeight = CalcDimension(info[0]->ToString());
    } else if (!ParseJsDimensionVp(info[0], customHeight)) {
        customHeight = Dimension(0.0);
    }

    SlidingPanelModel::GetInstance()->SetCustomHeight(customHeight);
}

void JSSlidingPanel::SetMiniHeight(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    CalcDimension miniHeight;
    if (!ParseJsDimensionVp(info[0], miniHeight)) {
        return;
    }

    SlidingPanelModel::GetInstance()->SetMiniHeight(miniHeight);
}

void JSSlidingPanel::SetHalfHeight(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    CalcDimension halfHeight;
    if (!ParseJsDimensionVp(info[0], halfHeight)) {
        return;
    }
    SlidingPanelModel::GetInstance()->SetHalfHeight(halfHeight);
}

void JSSlidingPanel::SetFullHeight(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    CalcDimension fullHeight;
    if (!ParseJsDimensionVp(info[0], fullHeight)) {
        return;
    }
    SlidingPanelModel::GetInstance()->SetFullHeight(fullHeight);
}

void JSSlidingPanel::Pop()
{
    if (ViewStackModel::GetInstance()->IsPrebuilding()) {
        return ViewStackModel::GetInstance()->PushPrebuildCompCmd("[JSSlidingPanel][pop]", &JSSlidingPanel::Pop);
    }
    SlidingPanelModel::GetInstance()->Pop();
}

} // namespace OHOS::Ace::Framework
