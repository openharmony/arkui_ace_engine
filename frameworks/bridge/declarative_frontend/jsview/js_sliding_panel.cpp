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

#include "frameworks/bridge/declarative_frontend/jsview/js_sliding_panel.h"

#include <algorithm>
#include <iterator>

#include "base/log/ace_scoring_log.h"
#include "bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "bridge/declarative_frontend/jsview/models/sliding_panel_model_impl.h"
#include "core/components_ng/base/view_abstract_model_ng.h"
#include "core/components_ng/pattern/panel/sliding_panel_model.h"
#include "core/components_ng/pattern/panel/sliding_panel_model_ng.h"

namespace OHOS::Ace {

std::unique_ptr<SlidingPanelModel> SlidingPanelModel::instance_ = nullptr;

SlidingPanelModel* SlidingPanelModel::GetInstance()
{
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
    return instance_.get();
}

} // namespace OHOS::Ace
namespace OHOS::Ace::Framework {
namespace {

const std::vector<PanelMode> PANEL_MODES = { PanelMode::MINI, PanelMode::HALF, PanelMode::FULL, PanelMode::AUTO };
const std::vector<PanelType> PANEL_TYPES = { PanelType::MINI_BAR, PanelType::FOLDABLE_BAR, PanelType::TEMP_DISPLAY };
const std::vector<VisibleType> PANEL_VISIBLE_TYPES = { VisibleType::GONE, VisibleType::VISIBLE,
    VisibleType::INVISIBLE };

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
    JSClass<JSSlidingPanel>::StaticMethod("mode", &JSSlidingPanel::SetPanelMode, opt);
    JSClass<JSSlidingPanel>::StaticMethod("type", &JSSlidingPanel::SetPanelType, opt);
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

    JSClass<JSSlidingPanel>::Inherit<JSContainerBase>();
    JSClass<JSSlidingPanel>::Inherit<JSViewAbstract>();
    JSClass<JSSlidingPanel>::Bind<>(globalObj);
}

void JSSlidingPanel::SetBackgroundMask(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The argv is wrong, it is supposed to have at least 1 argument");
        return;
    }
    Color color;
    if (!ParseJsColor(info[0], color)) {
        return;
    }

    SlidingPanelModel::GetInstance()->SetBackgroundMask(color);
}

void JSSlidingPanel::ParsePanelRadius(const JSRef<JSVal>& args, BorderRadius& borderRadius)
{
    if (!args->IsObject() && !args->IsNumber() && !args->IsString()) {
        LOGE("args need a object or number or string. %{public}s", args->ToString().c_str());
        return;
    }

    Dimension radius;
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
    LOGE("args format error. %{public}s", args->ToString().c_str());
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
        LOGE("The argv is wrong, it is supposed to have at least 1 argument");
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
        LOGE("The argv is wrong, it is supposed to have at least 1 argument");
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
        LOGE("The argv is wrong, it is supposed to have at least 1 argument");
        return;
    }
    Dimension borderWidth;
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
        LOGE("The arg is wrong, it is supposed to have atleast 1 arguments");
        return;
    }
    if (!info[0]->IsObject()) {
        LOGE("arg is not a object.");
        return;
    }

    auto argsPtrItem = JSRef<JSObject>::Cast(info[0]);
    Dimension width = Dimension(0.0, DimensionUnit::VP);
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
        LOGE("The argv is wrong, it is supposed to have at least 1 argument");
        return;
    }
    if (!args[0]->IsFunction()) {
        return;
    }

    auto onHeightChangeCallback = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(args[0]));
    auto onHeightChange = [execCtx = args.GetExecutionContext(), func = std::move(onHeightChangeCallback)](
                              int32_t height) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("OnHeightChange");
        JSRef<JSVal> param = JSRef<JSVal>::Make(ToJSValue(height));
        func->ExecuteJS(1, &param);
    };

    SlidingPanelModel::GetInstance()->SetOnHeightChange(std::move(onHeightChange));

    args.ReturnSelf();
}

void JSSlidingPanel::SetHasDragBar(bool hasDragBar)
{
    SlidingPanelModel::GetInstance()->SetHasDragBar(hasDragBar);
}

void JSSlidingPanel::SetShow(bool isShow)
{
    SlidingPanelModel::GetInstance()->SetIsShow(isShow);
}

void JSSlidingPanel::SetPanelMode(int32_t mode)
{
    if (mode < 0 || mode >= static_cast<int32_t>(PANEL_MODES.size())) {
        return;
    }

    SlidingPanelModel::GetInstance()->SetPanelMode(PANEL_MODES[mode]);
}

void JSSlidingPanel::SetPanelType(int32_t type)
{
    if (type < 0 || type >= static_cast<int32_t>(PANEL_TYPES.size())) {
        return;
    }

    SlidingPanelModel::GetInstance()->SetPanelType(PANEL_TYPES[type]);
}

void JSSlidingPanel::SetMiniHeight(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 argument");
        return;
    }
    Dimension miniHeight;
    if (!ParseJsDimensionVp(info[0], miniHeight)) {
        return;
    }

    SlidingPanelModel::GetInstance()->SetMiniHeight(miniHeight);
}

void JSSlidingPanel::SetHalfHeight(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 argument");
        return;
    }
    Dimension halfHeight;
    if (!ParseJsDimensionVp(info[0], halfHeight)) {
        return;
    }
    SlidingPanelModel::GetInstance()->SetHalfHeight(halfHeight);
}

void JSSlidingPanel::SetFullHeight(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 argument");
        return;
    }
    Dimension fullHeight;
    if (!ParseJsDimensionVp(info[0], fullHeight)) {
        return;
    }
    SlidingPanelModel::GetInstance()->SetFullHeight(fullHeight);
}

void JSSlidingPanel::Pop()
{
    SlidingPanelModel::GetInstance()->Pop();
}

} // namespace OHOS::Ace::Framework
