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

#include "frameworks/bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"
#include "frameworks/core/components/panel/sliding_panel_component_v2.h"
#include "frameworks/core/components_ng/base/view_abstract.h"
#include "frameworks/core/components_ng/base/view_stack_processor.h"
#include "frameworks/core/components_ng/pattern/panel/sliding_panel_view.h"

namespace OHOS::Ace::Framework {
namespace {

const std::vector<PanelMode> PANEL_MODES = { PanelMode::MINI, PanelMode::HALF, PanelMode::FULL, PanelMode::AUTO };
const std::vector<PanelType> PANEL_TYPES = { PanelType::MINI_BAR, PanelType::FOLDABLE_BAR, PanelType::TEMP_DISPLAY };
const std::vector<VisibleType> PANEL_VISIBLE_TYPES = { VisibleType::GONE, VisibleType::VISIBLE,
    VisibleType::INVISIBLE };

} // namespace

void JSSlidingPanel::Create(const JSCallbackInfo& info)
{
    if (Container::IsCurrentUseNewPipeline()) {
        NG::SlidingPanelView::Create();
        return;
    }
    auto slidingPanel = AceType::MakeRefPtr<SlidingPanelComponentV2>();
    ViewStackProcessor::GetInstance()->ClaimElementId(slidingPanel);
    slidingPanel->SetHasDragBar(true);
    ViewStackProcessor::GetInstance()->Push(slidingPanel);
    if (info.Length() > 0 && info[0]->IsBoolean()) {
        auto isShow = info[0]->ToBoolean();
        slidingPanel->SetVisible(isShow);
        auto component = ViewStackProcessor::GetInstance()->GetDisplayComponent();
        auto display = AceType::DynamicCast<DisplayComponent>(component);
        if (!display) {
            LOGE("display is null");
            return;
        }
        display->SetVisible(isShow ? VisibleType::VISIBLE : VisibleType::GONE);
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

    if (Container::IsCurrentUseNewPipeline()) {
        NG::ViewAbstract::SetBackgroundColor(color);
        return;
    }

    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto panel = AceType::DynamicCast<SlidingPanelComponent>(component);
    if (!panel) {
        LOGE("Panel is null");
        return;
    }

    auto displayComponent = ViewStackProcessor::GetInstance()->GetDisplayComponent();
    auto display = AceType::DynamicCast<DisplayComponent>(displayComponent);
    if (!display) {
        LOGE("display is null");
        return;
    }
    if (ParseJsColor(info[0], color)) {
        display->SetBackgroundMask(color);
    }
}

void JSSlidingPanel::SetOnHeightChange(const JSCallbackInfo& args)
{
    if (args.Length() < 1) {
        LOGE("The argv is wrong, it is supposed to have at least 1 argument");
        return;
    }
    if (args[0]->IsFunction()) {
        auto onHeightChangeCallback = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(args[0]));
        auto onHeightChange = [execCtx = args.GetExecutionContext(), func = std::move(onHeightChangeCallback)](
                                  int32_t height) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("OnHeightChange");
            JSRef<JSVal> param = JSRef<JSVal>::Make(ToJSValue(height));
            func->ExecuteJS(1, &param);
        };
        auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
        auto panel = AceType::DynamicCast<SlidingPanelComponent>(component);
        if (panel) {
            panel->SetOnHeightChanged(onHeightChange);
        }
    }
    args.ReturnSelf();
}

void JSSlidingPanel::ParsePanelRadius(const JSRef<JSVal>& args)
{
    if (!args->IsObject() && !args->IsNumber() && !args->IsString()) {
        LOGE("args need a object or number or string. %{public}s", args->ToString().c_str());
        return;
    }
    RefPtr<Decoration> tarDecoration = GetPanelDecoration();
    Dimension radiusTopLeft;
    Dimension radiusTopRight;
    Dimension radiusBottomLeft;
    Dimension radiusBottomRight;
    Dimension borderRadius;
    if (ParseJsDimensionVp(args, borderRadius)) {
        radiusTopLeft = borderRadius;
        radiusTopRight = borderRadius;
        radiusBottomLeft = borderRadius;
        radiusBottomRight = borderRadius;
    } else if (args->IsObject()) {
        JSRef<JSObject> object = JSRef<JSObject>::Cast(args);
        auto valueTopLeft = object->GetProperty("topLeft");
        if (!valueTopLeft->IsUndefined()) {
            ParseJsDimensionVp(valueTopLeft, radiusTopLeft);
        }
        auto valueTopRight = object->GetProperty("topRight");
        if (!valueTopRight->IsUndefined()) {
            ParseJsDimensionVp(valueTopRight, radiusTopRight);
        }
        auto valueBottomLeft = object->GetProperty("bottomLeft");
        if (!valueBottomLeft->IsUndefined()) {
            ParseJsDimensionVp(valueBottomLeft, radiusBottomLeft);
        }
        auto valueBottomRight = object->GetProperty("bottomRight");
        if (!valueBottomRight->IsUndefined()) {
            ParseJsDimensionVp(valueBottomRight, radiusBottomRight);
        }
    } else {
        LOGE("args format error. %{public}s", args->ToString().c_str());
        return;
    }
    auto border = tarDecoration->GetBorder();
    border.SetTopLeftRadius(Radius(radiusTopLeft));
    border.SetTopRightRadius(Radius(radiusTopRight));
    border.SetBottomLeftRadius(Radius(radiusBottomLeft));
    border.SetBottomRightRadius(Radius(radiusBottomRight));
    tarDecoration->SetBorder(border);
}

void JSSlidingPanel::JsPanelBorderRadius(const JSCallbackInfo& info)
{
    if (Container::IsCurrentUseNewPipeline()) {
        JSViewAbstract::JsBorderRadius(info);
        return;
    }
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto panel = AceType::DynamicCast<SlidingPanelComponentV2>(component);
    ParsePanelRadius(info[0]);
    panel->SetHasBorderStyle(true);
    panel->SetHasDecorationStyle(true);
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
    if (Container::IsCurrentUseNewPipeline()) {
        NG::SlidingPanelView::SetBackgroundColor(backgroundColor);
        return;
    }

    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto panel = AceType::DynamicCast<SlidingPanelComponentV2>(component);
    auto box = JSSlidingPanel::GetPanelBox();
    if (!panel || !box) {
        LOGE("Not valid type for SlidingPanel");
        return;
    }
    box->SetColor(backgroundColor);
    panel->SetHasBgStyle(true);
    panel->SetHasDecorationStyle(true);
}

RefPtr<BoxComponent> JSSlidingPanel::GetPanelBox()
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto panel = AceType::DynamicCast<SlidingPanelComponentV2>(component);
    if (!panel) {
        return nullptr;
    }
    if (panel->HasBoxStyle()) {
        return panel->GetBoxStyle();
    } else {
        panel->SetHasBoxStyle(true);
        auto box = AceType::MakeRefPtr<BoxComponent>();
        panel->SetBoxStyle(box);
        return box;
    }
}

RefPtr<Decoration> JSSlidingPanel::GetPanelDecoration()
{
    auto box = JSSlidingPanel::GetPanelBox();
    if (!box) {
        return nullptr;
    }
    auto decoration = box->GetBackDecoration();
    if (!decoration) {
        decoration = AceType::MakeRefPtr<Decoration>();
        box->SetBackDecoration(decoration);
    }
    return decoration;
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
    if (Container::IsCurrentUseNewPipeline()) {
        NG::ViewAbstract::SetBorderColor(borderColor);
        return;
    }

    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto panel = AceType::DynamicCast<SlidingPanelComponentV2>(component);
    auto decoration = JSSlidingPanel::GetPanelDecoration();
    if (!panel || !decoration) {
        return;
    }
    auto border = decoration->GetBorder();
    border.SetColor(borderColor);
    decoration->SetBorder(border);
    panel->SetHasBorderStyle(true);
    panel->SetHasDecorationStyle(true);
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
    if (Container::IsCurrentUseNewPipeline()) {
        NG::ViewAbstract::SetBorderWidth(borderWidth);
        return;
    }

    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto panel = AceType::DynamicCast<SlidingPanelComponentV2>(component);
    auto decoration = JSSlidingPanel::GetPanelDecoration();
    if (!panel || !decoration) {
        return;
    }
    auto border = decoration->GetBorder();
    border.SetWidth(borderWidth);
    decoration->SetBorder(border);
    panel->SetHasBorderStyle(true);
    panel->SetHasDecorationStyle(true);
}

void JSSlidingPanel::JsPanelBorderStyle(int32_t style)
{
    BorderStyle borderStyle = BorderStyle::SOLID;
    if (style > 0 && style < 4) {
        borderStyle = static_cast<BorderStyle>(style);
    }
    if (Container::IsCurrentUseNewPipeline()) {
        NG::ViewAbstract::SetBorderStyle(borderStyle);
        return;
    }

    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto panel = AceType::DynamicCast<SlidingPanelComponentV2>(component);
    auto decoration = JSSlidingPanel::GetPanelDecoration();
    if (!panel || !decoration) {
        return;
    }
    auto border = decoration->GetBorder();
    border.SetStyle(borderStyle);
    decoration->SetBorder(border);
    panel->SetHasBorderStyle(true);
    panel->SetHasDecorationStyle(true);
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
    if (Container::IsCurrentUseNewPipeline()) {
        JSViewAbstract::JsBorder(info);
        return;
    }
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto panel = AceType::DynamicCast<SlidingPanelComponentV2>(component);
    if (!panel) {
        LOGE("Panel is Null");
        return;
    }
    auto decoration = JSSlidingPanel::GetPanelDecoration();
    auto argsPtrItem = JSRef<JSObject>::Cast(info[0]);

    Dimension width = Dimension(0.0, DimensionUnit::VP);
    ParseJsDimensionVp(argsPtrItem->GetProperty("width"), width);
    ParsePanelRadius(argsPtrItem->GetProperty("radius"));
    auto styleJsValue = argsPtrItem->GetProperty("style");
    auto borderStyle = BorderStyle::SOLID;
    if (!styleJsValue->IsUndefined() && styleJsValue->IsNumber()) {
        auto styleValue = styleJsValue->ToNumber<uint32_t>();
        if (styleValue > 0 && styleValue < 4) {
            borderStyle = static_cast<BorderStyle>(styleValue);
        }
    }
    auto border = decoration->GetBorder();
    border.SetStyle(borderStyle);
    border.SetWidth(width);
    Color color;
    if (ParseJsColor(argsPtrItem->GetProperty("color"), color)) {
        border.SetColor(color);
    }
    decoration->SetBorder(border);
    panel->SetHasBorderStyle(true);
    panel->SetHasDecorationStyle(true);
}

void JSSlidingPanel::SetOnSizeChange(const JSCallbackInfo& args)
{
    if (args[0]->IsFunction()) {
        auto onSizeChange = EventMarker(
            [execCtx = args.GetExecutionContext(), func = JSRef<JSFunc>::Cast(args[0])](const BaseEventInfo* info) {
                JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
                auto eventInfo = TypeInfoHelper::DynamicCast<SlidingPanelSizeChangeEvent>(info);
                if (!eventInfo) {
                    return;
                }
                auto params = ConvertToJSValues(eventInfo->GetWidth(), eventInfo->GetHeight(), eventInfo->GetMode());
                ACE_SCORING_EVENT("SlidingPanel.OnSizeChange");
                func->Call(JSRef<JSObject>(), params.size(), params.data());
            });
        auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
        auto panel = AceType::DynamicCast<SlidingPanelComponent>(component);
        if (panel) {
            panel->SetOnSizeChanged(onSizeChange);
        }
    }
    args.ReturnSelf();
}

void JSSlidingPanel::SetHasDragBar(bool hasDragBar)
{
    if (Container::IsCurrentUseNewPipeline()) {
        NG::SlidingPanelView::SetHasDragBar(hasDragBar);
        return;
    }
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto panel = AceType::DynamicCast<SlidingPanelComponent>(component);
    if (panel) {
        panel->SetHasDragBar(hasDragBar);
    }
}

void JSSlidingPanel::SetShow(bool isShow)
{
    if (Container::IsCurrentUseNewPipeline()) {
        NG::ViewAbstract::SetVisibility(isShow ? VisibleType::VISIBLE : VisibleType::GONE);
        return;
    }
    auto component = ViewStackProcessor::GetInstance()->GetDisplayComponent();
    auto display = AceType::DynamicCast<DisplayComponent>(component);
    if (!display) {
        LOGE("display is null");
        return;
    }
    display->SetVisible(isShow ? VisibleType::VISIBLE : VisibleType::GONE);
    auto panelComponent = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto panel = AceType::DynamicCast<SlidingPanelComponent>(panelComponent);
    if (!panel) {
        LOGE("Panel is null");
        return;
    }
    panel->SetVisible(isShow);
}

void JSSlidingPanel::SetPanelMode(int32_t mode)
{
    if (mode < 0 || mode >= static_cast<int32_t>(PANEL_MODES.size())) {
        return;
    }
    if (Container::IsCurrentUseNewPipeline()) {
        NG::SlidingPanelView::SetPanelMode(PANEL_MODES[mode]);
        return;
    }

    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto panel = AceType::DynamicCast<SlidingPanelComponent>(component);
    if (panel) {
        if (static_cast<int32_t>(PanelMode::HALF) == mode) {
            panel->SetMode(PanelMode::HALF);
        } else if (static_cast<int32_t>(PanelMode::MINI) == mode) {
            panel->SetMode(PanelMode::MINI);
        } else {
            panel->SetMode(PanelMode::FULL);
        }
    }
}

void JSSlidingPanel::SetPanelType(int32_t type)
{
    if (type < 0 || type >= static_cast<int32_t>(PANEL_TYPES.size())) {
        return;
    }
    if (Container::IsCurrentUseNewPipeline()) {
        NG::SlidingPanelView::SetPanelType(PANEL_TYPES[type]);
        return;
    }

    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto panel = AceType::DynamicCast<SlidingPanelComponent>(component);
    if (panel) {
        if (static_cast<int32_t>(PanelType::MINI_BAR) == type) {
            panel->SetType(PanelType::MINI_BAR);
        } else if (static_cast<int32_t>(PanelType::TEMP_DISPLAY) == type) {
            panel->SetType(PanelType::TEMP_DISPLAY);
        } else {
            panel->SetType(PanelType::FOLDABLE_BAR);
        }
    }
}

void JSSlidingPanel::SetMiniHeight(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 argument");
        return;
    }
    Dimension minHeight;
    if (!ParseJsDimensionVp(info[0], minHeight)) {
        return;
    }
    if (Container::IsCurrentUseNewPipeline()) {
        NG::SlidingPanelView::SetMiniHeight(minHeight);
        return;
    }

    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto panel = AceType::DynamicCast<SlidingPanelComponent>(component);
    if (panel) {
        panel->SetMiniHeight(std::pair(minHeight, true));
    }
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
    if (Container::IsCurrentUseNewPipeline()) {
        NG::SlidingPanelView::SetHalfHeight(halfHeight);
        return;
    }

    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto panel = AceType::DynamicCast<SlidingPanelComponent>(component);
    if (panel) {
        panel->SetHalfHeight(std::pair(halfHeight, true));
    }
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
    if (Container::IsCurrentUseNewPipeline()) {
        NG::SlidingPanelView::SetFullHeight(fullHeight);
        return;
    }

    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto panel = AceType::DynamicCast<SlidingPanelComponent>(component);
    if (panel) {
        panel->SetFullHeight(std::pair(fullHeight, true));
    }
}

void JSSlidingPanel::Pop()
{
    if (Container::IsCurrentUseNewPipeline()) {
        NG::SlidingPanelView::Pop();
        NG::ViewStackProcessor::GetInstance()->PopContainer();
        return;
    }

    JSContainerBase::Pop();
}

} // namespace OHOS::Ace::Framework
