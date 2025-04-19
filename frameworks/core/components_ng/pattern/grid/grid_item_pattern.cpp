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

#include "core/components_ng/pattern/grid/grid_item_pattern.h"

#include "base/log/dump_log.h"
#include "core/components_ng/pattern/grid/grid_pattern.h"
namespace OHOS::Ace::NG {
namespace {
const Color ITEM_FILL_COLOR = Color::TRANSPARENT;
} // namespace
void GridItemPattern::OnAttachToFrameNode()
{
    if (gridItemStyle_ == GridItemStyle::PLAIN) {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto pipeline = GetContext();
        CHECK_NULL_VOID(pipeline);
        auto theme = pipeline->GetTheme<GridItemTheme>();
        CHECK_NULL_VOID(theme);
        auto renderContext = host->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        renderContext->UpdateBorderRadius(theme->GetGridItemBorderRadius());
    }
}

void GridItemPattern::OnModifyDone()
{
    Pattern::OnModifyDone();
    SetAccessibilityAction();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto focusHub = host->GetFocusHub();
    CHECK_NULL_VOID(focusHub);
    InitFocusPaintRect(focusHub);
    InitOnFocusEvent(focusHub);
    InitDisableStyle();
    if (gridItemStyle_ == GridItemStyle::PLAIN) {
        InitHoverEvent();
        InitPressEvent();
    }
}

void GridItemPattern::MarkIsSelected(bool isSelected)
{
    if (isSelected_ != isSelected) {
        isSelected_ = isSelected;
        auto eventHub = GetOrCreateEventHub<GridItemEventHub>();
        CHECK_NULL_VOID(eventHub);
        eventHub->FireSelectChangeEvent(isSelected);
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        if (isSelected) {
            eventHub->UpdateCurrentUIState(UI_STATE_SELECTED);
            host->OnAccessibilityEvent(AccessibilityEventType::SELECTED);
        } else {
            eventHub->ResetCurrentUIState(UI_STATE_SELECTED);
            host->OnAccessibilityEvent(AccessibilityEventType::CHANGE);
        }
    }
}

void GridItemPattern::SetSelectable(bool selectable)
{
    if (isSelected_ && selectable_ && !selectable) {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto context = host->GetRenderContext();
        CHECK_NULL_VOID(context);
        context->OnMouseSelectUpdate(false, ITEM_FILL_COLOR, ITEM_FILL_COLOR);
        MarkIsSelected(false);
    }
    selectable_ = selectable;
}

void GridItemPattern::SetAccessibilityAction()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto accessibilityProperty = host->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);
    accessibilityProperty->SetActionSelect([weakPtr = WeakClaim(this)]() {
        const auto& pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (!pattern->Selectable()) {
            return;
        }
        auto host = pattern->GetHost();
        CHECK_NULL_VOID(host);
        auto context = host->GetRenderContext();
        CHECK_NULL_VOID(context);
        pattern->MarkIsSelected(true);
        context->OnMouseSelectUpdate(true, ITEM_FILL_COLOR, ITEM_FILL_COLOR);
    });

    accessibilityProperty->SetActionClearSelection([weakPtr = WeakClaim(this)]() {
        const auto& pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (!pattern->Selectable()) {
            return;
        }
        auto host = pattern->GetHost();
        CHECK_NULL_VOID(host);
        auto context = host->GetRenderContext();
        CHECK_NULL_VOID(context);
        pattern->MarkIsSelected(false);
        context->OnMouseSelectUpdate(false, ITEM_FILL_COLOR, ITEM_FILL_COLOR);
    });
}

void GridItemPattern::BeforeCreateLayoutWrapper()
{
    if (shallowBuilder_ && !shallowBuilder_->IsExecuteDeepRenderDone()) {
        shallowBuilder_->ExecuteDeepRender();
        shallowBuilder_.Reset();
    }
}

Color GridItemPattern::GetBlendGgColor()
{
    Color color = Color::TRANSPARENT;
    auto pipeline = GetContext();
    CHECK_NULL_RETURN(pipeline, color);
    auto theme = pipeline->GetTheme<GridItemTheme>();
    CHECK_NULL_RETURN(theme, color);
    if (isPressed_) {
        color = color.BlendColor(theme->GetGridItemPressColor());
    } else if (isHover_) {
        color = color.BlendColor(theme->GetGridItemHoverColor());
    }
    return color;
}

void GridItemPattern::InitHoverEvent()
{
    if (hoverEvent_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetOrCreateEventHub<GridItemEventHub>();
    CHECK_NULL_VOID(eventHub);
    auto inputHub = eventHub->GetOrCreateInputEventHub();
    CHECK_NULL_VOID(inputHub);
    auto hoverTask = [weak = WeakClaim(this)](bool isHover) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleHoverEvent(isHover);
        }
    };
    hoverEvent_ = MakeRefPtr<InputEvent>(std::move(hoverTask));
    inputHub->AddOnHoverEvent(hoverEvent_);
}

void GridItemPattern::HandleHoverEvent(bool isHover)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<GridItemTheme>();
    CHECK_NULL_VOID(theme);

    isHover_ = isHover;
    auto hoverColor = GetBlendGgColor();
    AnimationUtils::BlendBgColorAnimation(
        renderContext, hoverColor, theme->GetHoverAnimationDuration(), Curves::FRICTION);
}

void GridItemPattern::InitPressEvent()
{
    if (touchListener_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gesture = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gesture);
    auto touchCallback = [weak = WeakClaim(this)](const TouchEventInfo& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto touchType = info.GetTouches().front().GetTouchType();
        if (touchType == TouchType::DOWN || touchType == TouchType::UP) {
            pattern->HandlePressEvent(touchType == TouchType::DOWN);
        }
    };
    auto touchListener_ = MakeRefPtr<TouchEventImpl>(std::move(touchCallback));
    gesture->AddTouchEvent(touchListener_);
}

void GridItemPattern::HandlePressEvent(bool isPressed)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto pipeline = GetContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<GridItemTheme>();
    CHECK_NULL_VOID(theme);
    auto duration = isHover_ ? theme->GetHoverToPressAnimationDuration() : theme->GetHoverAnimationDuration();
    isPressed_ = isPressed;
    Color color = GetBlendGgColor();
    AnimationUtils::BlendBgColorAnimation(renderContext, color, duration, Curves::SHARP);
}

void GridItemPattern::InitDisableStyle()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetOrCreateEventHub<GridItemEventHub>();
    CHECK_NULL_VOID(eventHub);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto pipeline = GetContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<GridItemTheme>();
    CHECK_NULL_VOID(theme);
    float opacity = 1.0f;
    if (!eventHub->IsDeveloperEnabled()) {
        opacity = theme->GetGridItemDisabledAlpha();
    }
    renderContext->SetOpacityMultiplier(opacity);
}

void GridItemPattern::InitFocusPaintRect(const RefPtr<FocusHub>& focusHub)
{
    auto getInnerPaintRectCallback = [wp = WeakClaim(this)](RoundRect& paintRect) {
        auto pattern = wp.Upgrade();
        if (pattern) {
            pattern->GetInnerFocusPaintRect(paintRect);
        }
    };
    focusHub->SetInnerFocusPaintRectCallback(getInnerPaintRectCallback);
}

void GridItemPattern::GetInnerFocusPaintRect(RoundRect& paintRect)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto gridItemSize = geometryNode->GetFrameSize();
    auto pipelineContext = GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto theme = pipelineContext->GetTheme<GridItemTheme>();
    CHECK_NULL_VOID(theme);
    auto focusPaintPadding = theme->GetFocusPaintPadding().ConvertToPx();
    float width = gridItemSize.Width() + 2 * focusPaintPadding;
    float height = gridItemSize.Height() + 2 * focusPaintPadding;
    paintRect.SetRect({ -focusPaintPadding, -focusPaintPadding, width, height });
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto radius = renderContext->GetBorderRadius().value_or(BorderRadiusProperty());
    paintRect.SetCornerRadius(RoundRect::CornerPos::TOP_LEFT_POS,
        static_cast<float>(radius.radiusTopLeft->ConvertToPx() + focusPaintPadding),
        static_cast<float>(radius.radiusTopLeft->ConvertToPx() + focusPaintPadding));
    paintRect.SetCornerRadius(RoundRect::CornerPos::TOP_RIGHT_POS,
        static_cast<float>(radius.radiusTopRight->ConvertToPx() + focusPaintPadding),
        static_cast<float>(radius.radiusTopRight->ConvertToPx() + focusPaintPadding));
    paintRect.SetCornerRadius(RoundRect::CornerPos::BOTTOM_LEFT_POS,
        static_cast<float>(radius.radiusBottomLeft->ConvertToPx() + focusPaintPadding),
        static_cast<float>(radius.radiusBottomLeft->ConvertToPx() + focusPaintPadding));
    paintRect.SetCornerRadius(RoundRect::CornerPos::BOTTOM_RIGHT_POS,
        static_cast<float>(radius.radiusBottomRight->ConvertToPx() + focusPaintPadding),
        static_cast<float>(radius.radiusBottomRight->ConvertToPx() + focusPaintPadding));
}

void GridItemPattern::DumpAdvanceInfo()
{
    auto property = GetLayoutProperty<GridItemLayoutProperty>();
    CHECK_NULL_VOID(property);
    property->GetMainIndex().has_value()
        ? DumpLog::GetInstance().AddDesc("MainIndex:" + std::to_string(property->GetMainIndex().value()))
        : DumpLog::GetInstance().AddDesc("MainIndex:null");
    property->GetCrossIndex().has_value()
        ? DumpLog::GetInstance().AddDesc("CrossIndex:" + std::to_string(property->GetCrossIndex().value()))
        : DumpLog::GetInstance().AddDesc("CrossIndex:null");
    property->GetRowStart().has_value()
        ? DumpLog::GetInstance().AddDesc("RowStart:" + std::to_string(property->GetRowStart().value()))
        : DumpLog::GetInstance().AddDesc("RowStart:null");
    property->GetRowEnd().has_value()
        ? DumpLog::GetInstance().AddDesc("RowEnd:" + std::to_string(property->GetRowEnd().value()))
        : DumpLog::GetInstance().AddDesc("RowEnd:null");
    property->GetColumnStart().has_value()
        ? DumpLog::GetInstance().AddDesc("ColumnStart:" + std::to_string(property->GetColumnStart().value()))
        : DumpLog::GetInstance().AddDesc("ColumnStart:null");
    property->GetColumnEnd().has_value()
        ? DumpLog::GetInstance().AddDesc("ColumnEnd:" + std::to_string(property->GetColumnEnd().value()))
        : DumpLog::GetInstance().AddDesc("ColumnEnd:null");
    property->GetNeedStretch() ? DumpLog::GetInstance().AddDesc("needStretch:true")
                               : DumpLog::GetInstance().AddDesc("needStretch:false");
    selectable_ ? DumpLog::GetInstance().AddDesc("selectable:true")
                : DumpLog::GetInstance().AddDesc("selectable:false");
    isSelected_ ? DumpLog::GetInstance().AddDesc("isSelected:true")
                : DumpLog::GetInstance().AddDesc("isSelected:false");
    isHover_ ? DumpLog::GetInstance().AddDesc("isHover:true") : DumpLog::GetInstance().AddDesc("isHover:false");
    isPressed_ ? DumpLog::GetInstance().AddDesc("isPressed:true") : DumpLog::GetInstance().AddDesc("isPressed:false");
    switch (gridItemStyle_) {
        case GridItemStyle::NONE: {
            DumpLog::GetInstance().AddDesc("GridItemStyle:NONE");
            break;
        }
        case GridItemStyle::PLAIN: {
            DumpLog::GetInstance().AddDesc("GridItemStyle:PLAIN");
            break;
        }
        default: {
            break;
        }
    }
}

void GridItemPattern::UpdateGridItemStyle(GridItemStyle gridItemStyle)
{
    gridItemStyle_ = gridItemStyle;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<GridItemTheme>();
    CHECK_NULL_VOID(theme);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    if (gridItemStyle_ == GridItemStyle::PLAIN) {
        renderContext->UpdateBorderRadius(theme->GetGridItemBorderRadius());
    } else if (gridItemStyle_ == GridItemStyle::NONE) {
        renderContext->UpdateBorderRadius(BorderRadiusProperty());
    }
}

void GridItemPattern::DumpAdvanceInfo(std::unique_ptr<JsonValue>& json)
{
    auto property = GetLayoutProperty<GridItemLayoutProperty>();
    CHECK_NULL_VOID(property);
    json->Put("MainIndex",
        property->GetMainIndex().has_value() ? std::to_string(property->GetMainIndex().value()).c_str() : "null");
    json->Put("CrossIndex",
        property->GetCrossIndex().has_value() ? std::to_string(property->GetCrossIndex().value()).c_str() : "null");
    json->Put("RowStart",
        property->GetRowStart().has_value() ? std::to_string(property->GetRowStart().value()).c_str() : "null");
    json->Put(
        "RowEnd", property->GetRowEnd().has_value() ? std::to_string(property->GetRowEnd().value()).c_str() : "null");
    json->Put("ColumnStart",
        property->GetColumnStart().has_value() ? std::to_string(property->GetColumnStart().value()).c_str() : "null");
    json->Put("ColumnEnd",
        property->GetColumnEnd().has_value() ? std::to_string(property->GetColumnEnd().value()).c_str() : "null");

    json->Put("needStretch", property->GetNeedStretch());
    json->Put("selectable", selectable_);
    json->Put("isSelected", isSelected_);
    json->Put("isHover", isHover_);
    json->Put("isPressed", isPressed_);
    switch (gridItemStyle_) {
        case GridItemStyle::NONE: {
            json->Put("GridItemStyle", "NONE");
            break;
        }
        case GridItemStyle::PLAIN: {
            json->Put("GridItemStyle", "PLAIN");
            break;
        }
        default: {
            break;
        }
    }
}

void GridItemPattern::InitOnFocusEvent(const RefPtr<FocusHub>& focusHub)
{
    focusHub->SetOnFocusInternal([weak = WeakClaim(this)](FocusReason reason) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleFocusEvent();
        }
    });
}

void GridItemPattern::HandleFocusEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto uiNode = DynamicCast<UINode>(host);
    while (uiNode->GetTag() != V2::GRID_ETS_TAG) {
        uiNode = uiNode->GetParent();
        CHECK_NULL_VOID(uiNode);
    }
    auto grid = DynamicCast<FrameNode>(uiNode);
    CHECK_NULL_VOID(grid);
    auto pattern = grid->GetPattern<GridPattern>();
    CHECK_NULL_VOID(pattern);
    auto property = GetLayoutProperty<GridItemLayoutProperty>();
    CHECK_NULL_VOID(property);
    auto index = property->GetIndex();
    if (index.has_value()) {
        pattern->HandleOnItemFocus(index.value());
    }
}
} // namespace OHOS::Ace::NG
