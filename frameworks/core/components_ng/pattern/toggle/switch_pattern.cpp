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

#include "core/components_ng/pattern/toggle/switch_pattern.h"

#include "base/log/dump_log.h"
#include "core/common/recorder/node_data_cache.h"
#include "core/components/toggle/toggle_theme.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t DEFAULT_DURATION = 200;
const Color ITEM_FILL_COLOR = Color::TRANSPARENT;
constexpr double NUMBER_TWO = 2.0;
constexpr int32_t  HOTZONE_SPACE = 2;
} // namespace

void SwitchPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->SetAlphaOffscreen(true);
}

bool SwitchPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, bool skipMeasure, bool skipLayout)
{
    if (skipMeasure || dirty->SkipMeasureContent()) {
        return false;
    }
    if (isOn_.value_or(false)) {
        currentOffset_ = GetSwitchWidth();
    }

    auto layoutAlgorithmWrapper = DynamicCast<LayoutAlgorithmWrapper>(dirty->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, false);
    auto switchLayoutAlgorithm = DynamicCast<SwitchLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(switchLayoutAlgorithm, false);

    auto height = switchLayoutAlgorithm->GetHeight();
    auto width = switchLayoutAlgorithm->GetWidth();

    width_ = width;
    height_ = height;
    auto geometryNode = dirty->GetGeometryNode();
    offset_ = geometryNode->GetContentOffset();
    size_ = geometryNode->GetContentSize();
    if (!isUserSetResponseRegion_) {
        AddHotZoneRect();
    }
    return true;
}

void SwitchPattern::OnModifyDone()
{
    Pattern::OnModifyDone();
    UpdateSwitchLayoutProperty();
    UpdateSwitchPaintProperty();
    InitClickEvent();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hub = host->GetOrCreateEventHub<EventHub>();
    CHECK_NULL_VOID(hub);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    auto pipeline = host->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    switchTheme_ = pipeline->GetTheme<SwitchTheme>(host->GetThemeScopeId());
    InitPanEvent(gestureHub);
    InitTouchEvent();
    InitMouseEvent();
    InitFocusEvent();
    auto focusHub = host->GetFocusHub();
    CHECK_NULL_VOID(focusHub);
    InitOnKeyEvent(focusHub);
    SetAccessibilityAction();
    FireBuilder();
    HandleEnabled();
}

void SwitchPattern::InitFocusEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto focusHub = host->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);
    auto focusTask = [weak = WeakClaim(this)](FocusReason reason) {
        TAG_LOGD(AceLogTag::ACE_SELECT_COMPONENT, "switch button handle focus event");
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleFocusEvent();
    };
    focusHub->SetOnFocusInternal(focusTask);

    auto blurTask = [weak = WeakClaim(this)]() {
        TAG_LOGD(AceLogTag::ACE_SELECT_COMPONENT, "switch button handle blur event");
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleBlurEvent();
    };
    focusHub->SetOnBlurInternal(blurTask);
}

void SwitchPattern::HandleBlurEvent()
{
    RemoveIsFocusActiveUpdateEvent();
    OnIsFocusActiveUpdate(false);
}

void SwitchPattern::HandleFocusEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    AddIsFocusActiveUpdateEvent();
    if (pipeline->GetIsFocusActive()) {
        OnIsFocusActiveUpdate(true);
    }
}

void SwitchPattern::AddIsFocusActiveUpdateEvent()
{
    if (!isFocusActiveUpdateEvent_) {
        isFocusActiveUpdateEvent_ = [weak = WeakClaim(this)](bool isFocusAcitve) {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->OnIsFocusActiveUpdate(isFocusAcitve);
        };
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    pipeline->AddIsFocusActiveUpdateEvent(host, isFocusActiveUpdateEvent_);
}

void SwitchPattern::RemoveIsFocusActiveUpdateEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    pipeline->RemoveIsFocusActiveUpdateEvent(host);
}

void SwitchPattern::OnIsFocusActiveUpdate(bool isFocusAcitve)
{
    if (isFocusAcitve) {
        touchHoverType_ = TouchHoverAnimationType::FOCUS;
    } else {
        touchHoverType_ = TouchHoverAnimationType::NONE;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void SwitchPattern::HandleEnabled()
{
    if (UseContentModifier()) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetOrCreateEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    auto enabled = eventHub->IsEnabled();
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto pipeline = host->GetContextWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<ToggleTheme>();
    CHECK_NULL_VOID(theme);
    auto alpha = theme->GetDisabledAlpha();
    auto originalOpacity = renderContext->GetOpacityValue(1.0);
    renderContext->OnOpacityUpdate(enabled ? originalOpacity : alpha * originalOpacity);
}

void SwitchPattern::UpdateSwitchPaintProperty()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto switchPaintProperty = host->GetPaintProperty<SwitchPaintProperty>();
    CHECK_NULL_VOID(switchPaintProperty);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    if (!isOn_.has_value()) {
        isOn_ = switchPaintProperty->GetIsOnValue(false);
    }
    auto isOn = switchPaintProperty->GetIsOnValue(false);
    if (isOn != isOn_.value_or(false)) {
        isOn_ = isOn;
        OnChange();
    }
}

void SwitchPattern::UpdateSwitchLayoutProperty()
{
    auto pipeline = GetContext();
    CHECK_NULL_VOID(pipeline);
    auto switchTheme = pipeline->GetTheme<SwitchTheme>();
    CHECK_NULL_VOID(switchTheme);
    hotZoneHorizontalPadding_ = switchTheme->GetHotZoneHorizontalPadding();
    hotZoneVerticalPadding_ = switchTheme->GetHotZoneVerticalPadding();
    hotZoneHorizontalSize_ = switchTheme->GetHotZoneHorizontalSize();
    hotZoneVerticalSize_ = switchTheme->GetHotZoneVerticalSize();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    direction_ = layoutProperty->GetNonAutoLayoutDirection();
    InitDefaultMargin();
    if (layoutProperty->GetPositionProperty()) {
        layoutProperty->UpdateAlignment(
            layoutProperty->GetPositionProperty()->GetAlignment().value_or(Alignment::CENTER));
    } else {
        layoutProperty->UpdateAlignment(Alignment::CENTER);
    }
}

void SwitchPattern::InitDefaultMargin()
{
    if (makeFunc_.has_value()) {
        ResetDefaultMargin();
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    MarginProperty margin;
    margin.left = CalcLength(hotZoneHorizontalPadding_.Value());
    margin.right = CalcLength(hotZoneHorizontalPadding_.Value());
    margin.top = CalcLength(hotZoneVerticalPadding_.Value());
    margin.bottom = CalcLength(hotZoneVerticalPadding_.Value());
    auto& setMargin = layoutProperty->GetMarginProperty();
    if (setMargin) {
        if (setMargin->left.has_value()) {
            margin.left = setMargin->left;
        }
        if (setMargin->right.has_value()) {
            margin.right = setMargin->right;
        }
        if (setMargin->top.has_value()) {
            margin.top = setMargin->top;
        }
        if (setMargin->bottom.has_value()) {
            margin.bottom = setMargin->bottom;
        }
    }
    layoutProperty->UpdateMargin(margin);
}

void SwitchPattern::ResetDefaultMargin()
{
    if (isUserSetMargin_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    MarginProperty margin;
    layoutProperty->UpdateMargin(margin);
}

void SwitchPattern::SetAccessibilityAction()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto accessibilityProperty = host->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);
    accessibilityProperty->SetActionSelect([weakPtr = WeakClaim(this)]() {
        const auto& pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->UpdateSelectStatus(true);
    });

    accessibilityProperty->SetActionClearSelection([weakPtr = WeakClaim(this)]() {
        const auto& pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->UpdateSelectStatus(false);
    });
    FireBuilder();
}

void SwitchPattern::UpdateSelectStatus(bool isSelected)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetRenderContext();
    CHECK_NULL_VOID(context);
    MarkIsSelected(isSelected);
    context->OnMouseSelectUpdate(isSelected, ITEM_FILL_COLOR, ITEM_FILL_COLOR);
}

void SwitchPattern::MarkIsSelected(bool isSelected)
{
    if (isOn_ == isSelected) {
        return;
    }
    isOn_ = isSelected;
    auto eventHub = GetOrCreateEventHub<SwitchEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->UpdateChangeEvent(isSelected);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    eventHub->SetCurrentUIState(UI_STATE_SELECTED, isSelected);
    host->OnAccessibilityEvent(AccessibilityEventType::COMPONENT_CHANGE);
}

void SwitchPattern::OnAfterModifyDone()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto inspectorId = host->GetInspectorId().value_or("");
    if (!inspectorId.empty()) {
        Recorder::NodeDataCache::Get().PutBool(host, inspectorId, isOn_.value_or(false));
    }
}

RefPtr<Curve> SwitchPattern::GetCurve() const
{
    auto switchPaintProperty = GetPaintProperty<SwitchPaintProperty>();
    CHECK_NULL_RETURN(switchPaintProperty, nullptr);
    return switchPaintProperty->GetCurve().value_or(nullptr);
}

int32_t SwitchPattern::GetDuration() const
{
    auto switchPaintProperty = GetPaintProperty<SwitchPaintProperty>();
    CHECK_NULL_RETURN(switchPaintProperty, DEFAULT_DURATION);
    return switchPaintProperty->GetDuration().value_or(DEFAULT_DURATION);
}

void SwitchPattern::OnChange()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto switchPaintProperty = host->GetPaintProperty<SwitchPaintProperty>();
    CHECK_NULL_VOID(switchPaintProperty);
    CHECK_NULL_VOID(paintMethod_);
    auto switchModifier = paintMethod_->GetSwitchModifier();
    CHECK_NULL_VOID(switchModifier);
    switchModifier->SetIsOn(isOn_.value());
    switchPaintProperty->UpdateIsOn(isOn_.value_or(false));
    UpdateChangeEvent();
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

float SwitchPattern::GetSwitchWidth() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, false);
    auto switchWidth = geometryNode->GetContentSize().Width() - geometryNode->GetContentSize().Height();
    return switchWidth;
}

float SwitchPattern::GetSwitchContentOffsetX() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, 0.0f);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, 0.0f);
    return geometryNode->GetContentOffset().GetX();
}

void SwitchPattern::UpdateChangeEvent() const
{
    auto switchEventHub = GetOrCreateEventHub<SwitchEventHub>();
    CHECK_NULL_VOID(switchEventHub);
    switchEventHub->UpdateChangeEvent(isOn_.value());
}

void SwitchPattern::OnClick()
{
    if (UseContentModifier()) {
        return;
    }
    isOn_ = !isOn_.value_or(false);
    TAG_LOGI(AceLogTag::ACE_SELECT_COMPONENT, "switch click result %{public}d", isOn_.value_or(false));
    UpdateColorWhenIsOn(isOn_.value_or(false));
    OnChange();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->OnAccessibilityEvent(AccessibilityEventType::COMPONENT_CHANGE);
}

void SwitchPattern::UpdateColorWhenIsOn(bool isOn)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto switchPaintProperty = host->GetPaintProperty<SwitchPaintProperty>();
    CHECK_NULL_VOID(switchPaintProperty);
    CHECK_NULL_VOID(switchTheme_);
    CHECK_NULL_VOID(paintMethod_);
    auto switchModifier = paintMethod_->GetSwitchModifier();
    CHECK_NULL_VOID(switchModifier);

    Color onBgColor = switchTheme_->GetActiveColor();
    Color offBgColor = switchTheme_->GetInactiveColor();
    if (isOn) {
        if (switchPaintProperty->HasSelectedColor() && switchPaintProperty->GetSelectedColor() == onBgColor) {
            switchPaintProperty->UpdateSelectedColor(onBgColor);
        }
    } else {
        if (switchPaintProperty->HasUnselectedColor() && switchPaintProperty->GetUnselectedColor() == offBgColor) {
            Color bgColor = isFocus_ ? switchTheme_->GetFocusedBGColorUnselected() : switchTheme_->GetInactiveColor();
            switchPaintProperty->UpdateUnselectedColor(bgColor);
        }
        if (isFocus_) {
            switchModifier->SetFocusPointColor(switchTheme_->GetPointColorUnselectedFocus());
        }
    }
}

void SwitchPattern::UpdateComponentColor(const Color& color, const ToggleColorType toggleColorType)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipelineContext = host->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto paintProperty = GetPaintProperty<SwitchPaintProperty>();
    CHECK_NULL_VOID(paintProperty);

    if (pipelineContext->IsSystmColorChange()) {
        switch (toggleColorType) {
            case ToggleColorType::SELECTED_COLOR:
                paintProperty->UpdateSelectedColor(color);
                break;
            case ToggleColorType::SWITCH_POINT_COLOR:
                paintProperty->UpdateSwitchPointColor(color);
                break;
            case ToggleColorType::UN_SELECTED_COLOR:
                paintProperty->UpdateUnselectedColor(color);
                break;
        }
    }
    if (host->GetRerenderable()) {
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    }
}

void SwitchPattern::UpdateComponentDimension(const CalcDimension& dimension,
    const ToggleDimensionType toggleDimensionType)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipelineContext = host->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto paintProperty = GetPaintProperty<SwitchPaintProperty>();
    CHECK_NULL_VOID(paintProperty);

    if (pipelineContext->IsSystmColorChange()) {
        switch (toggleDimensionType) {
            case ToggleDimensionType::POINT_RADIUS:
                paintProperty->UpdatePointRadius(dimension);
                break;
            case ToggleDimensionType::TRACK_BORDER_RADIUS:
                paintProperty->UpdateTrackBorderRadius(dimension);
                break;
        }
    }
    if (host->GetRerenderable()) {
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    }
}

void SwitchPattern::OnTouchDown()
{
    if (UseContentModifier()) {
        return;
    }
    TAG_LOGI(AceLogTag::ACE_SELECT_COMPONENT, "switch touch down hover status %{public}d", isHover_);
    if (isHover_) {
        touchHoverType_ = TouchHoverAnimationType::HOVER_TO_PRESS;
    } else {
        touchHoverType_ = TouchHoverAnimationType::PRESS;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    isTouch_ = true;
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void SwitchPattern::OnTouchUp()
{
    if (UseContentModifier()) {
        return;
    }
    TAG_LOGI(AceLogTag::ACE_SELECT_COMPONENT, "switch touch up hover status %{public}d", isHover_);
    if (isHover_) {
        touchHoverType_ = TouchHoverAnimationType::PRESS_TO_HOVER;
    } else {
        touchHoverType_ = TouchHoverAnimationType::NONE;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    isTouch_ = false;
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    FireBuilder();
}

void SwitchPattern::InitPanEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    if (panEvent_) {
        return;
    }

    auto actionStartTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        TAG_LOGI(AceLogTag::ACE_SELECT_COMPONENT, "switch drag start");
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (info.GetInputEventType() == InputEventType::AXIS) {
            return;
        }
        pattern->HandleDragStart();
    };

    auto actionUpdateTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleDragUpdate(info);
    };

    auto actionEndTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        TAG_LOGI(AceLogTag::ACE_SELECT_COMPONENT, "switch drag end");
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (info.GetInputEventType() == InputEventType::AXIS) {
            return;
        }
        pattern->HandleDragEnd();
    };

    auto actionCancelTask = [weak = WeakClaim(this)]() {
        TAG_LOGI(AceLogTag::ACE_SELECT_COMPONENT, "switch drag cancel");
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleDragEnd();
    };

    PanDirection panDirection;
    panDirection.type = PanDirection::HORIZONTAL;

    panEvent_ = MakeRefPtr<PanEvent>(
        std::move(actionStartTask), std::move(actionUpdateTask), std::move(actionEndTask), std::move(actionCancelTask));
    PanDistanceMap distanceMap = { { SourceTool::UNKNOWN, DEFAULT_PAN_DISTANCE.ConvertToPx() },
        { SourceTool::PEN, DEFAULT_PEN_PAN_DISTANCE.ConvertToPx() } };
    gestureHub->AddPanEvent(panEvent_, panDirection, 1, distanceMap);
}

void SwitchPattern::InitClickEvent()
{
    if (clickListener_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gesture = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gesture);
    auto clickCallback = [weak = WeakClaim(this)](GestureEvent& info) {
        auto switchPattern = weak.Upgrade();
        CHECK_NULL_VOID(switchPattern);
        switchPattern->OnClick();
    };

    clickListener_ = MakeRefPtr<ClickEvent>(std::move(clickCallback));
    gesture->AddClickEvent(clickListener_);
}

void SwitchPattern::InitTouchEvent()
{
    if (touchListener_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gesture = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gesture);
    auto touchCallback = [weak = WeakClaim(this)](const TouchEventInfo& info) {
        auto switchPattern = weak.Upgrade();
        CHECK_NULL_VOID(switchPattern);
        if (info.GetTouches().front().GetTouchType() == TouchType::DOWN) {
            switchPattern->OnTouchDown();
        }
        if (info.GetTouches().front().GetTouchType() == TouchType::UP ||
            info.GetTouches().front().GetTouchType() == TouchType::CANCEL) {
            switchPattern->OnTouchUp();
        }
    };
    touchListener_ = MakeRefPtr<TouchEventImpl>(std::move(touchCallback));
    gesture->AddTouchEvent(touchListener_);
}

void SwitchPattern::InitMouseEvent()
{
    if (mouseEvent_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gesture = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gesture);
    auto eventHub = GetHost()->GetOrCreateEventHub<SwitchEventHub>();
    auto inputHub = eventHub->GetOrCreateInputEventHub();

    auto mouseTask = [weak = WeakClaim(this)](bool isHover) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleMouseEvent(isHover);
    };
    mouseEvent_ = MakeRefPtr<InputEvent>(std::move(mouseTask));
    inputHub->AddOnHoverEvent(mouseEvent_);
}

void SwitchPattern::InitOnKeyEvent(const RefPtr<FocusHub>& focusHub)
{
    auto getInnerPaintRectCallback = [wp = WeakClaim(this)](RoundRect& paintRect) {
        auto pattern = wp.Upgrade();
        if (pattern) {
            pattern->GetInnerFocusPaintRect(paintRect);
        }
    };
    focusHub->SetInnerFocusPaintRectCallback(getInnerPaintRectCallback);
    auto onKeyCallbackFunc = [wp = WeakClaim(this)](const KeyEvent& keyEventInfo) -> bool {
        auto pattern = wp.Upgrade();
        if (pattern) {
            return pattern->OnKeyEvent(keyEventInfo);
        }
        TAG_LOGI(AceLogTag::ACE_SELECT_COMPONENT, "InitOnKeyEvent return false");
        return false;
    };
    focusHub->SetOnKeyEventInternal(std::move(onKeyCallbackFunc));
}

bool SwitchPattern::OnKeyEvent(const KeyEvent& keyEventInfo)
{
    if (keyEventInfo.action == KeyAction::DOWN && keyEventInfo.code == KeyCode::KEY_FUNCTION) {
        this->OnClick();
        return true;
    }
    return false;
}

void SwitchPattern::GetInnerFocusPaintRect(RoundRect& paintRect)
{
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto switchTheme = pipelineContext->GetTheme<SwitchTheme>();
    CHECK_NULL_VOID(switchTheme);
    auto focusPaintPadding = switchTheme->GetFocusPaintPadding().ConvertToPx();

    auto height = height_ + focusPaintPadding * 2;
    auto width = width_ + focusPaintPadding * 2;
    auto radio = height / 2.0;
    auto offsetX = offset_.GetX() - focusPaintPadding;
    auto offsetY = offset_.GetY() - focusPaintPadding;
    CHECK_NULL_VOID(paintMethod_);
    auto switchModifier = paintMethod_->GetSwitchModifier();
    CHECK_NULL_VOID(switchModifier);
    auto trackRadius = switchModifier->GetTrackRadius();
    auto pointRadius = switchModifier->GetPointRadius();
    if (pointRadius * NUMBER_TWO > height_) {
        width = width_ - height_ + pointRadius * NUMBER_TWO + focusPaintPadding * NUMBER_TWO;
        height = pointRadius * NUMBER_TWO + focusPaintPadding * NUMBER_TWO;
        radio = pointRadius + focusPaintPadding;
        offsetX = offset_.GetX() - focusPaintPadding - (pointRadius - height_ / NUMBER_TWO);
        offsetY = offset_.GetY() - focusPaintPadding - (pointRadius - height_ / NUMBER_TWO);
        if (width_ < height_) {
            width = width_ + (pointRadius - trackRadius + focusPaintPadding) * NUMBER_TWO;
            offsetX = offset_.GetX() - (pointRadius - trackRadius + focusPaintPadding);
        }
    } else {
        if (SWITCH_ERROR_RADIUS != trackRadius) {
            radio = trackRadius + focusPaintPadding;
        }
        if (width_ < height_ && pointRadius > trackRadius) {
            width = width_ + (pointRadius - trackRadius + focusPaintPadding) * NUMBER_TWO;
            offsetX = offset_.GetX() - (pointRadius - trackRadius + focusPaintPadding);
        }
    }
    auto Rect = RectF(offsetX, offsetY, width, height);

    paintRect.SetCornerRadius(RoundRect::CornerPos::TOP_LEFT_POS, radio, radio);
    paintRect.SetCornerRadius(RoundRect::CornerPos::TOP_RIGHT_POS, radio, radio);
    paintRect.SetCornerRadius(RoundRect::CornerPos::BOTTOM_LEFT_POS, radio, radio);
    paintRect.SetCornerRadius(RoundRect::CornerPos::BOTTOM_RIGHT_POS, radio, radio);
    paintRect.SetRect(Rect);
}

void SwitchPattern::HandleMouseEvent(bool isHover)
{
    TAG_LOGI(AceLogTag::ACE_SELECT_COMPONENT, "switch mouse event %{public}d", isHover);
    isHover_ = isHover;
    if (isHover) {
        touchHoverType_ = TouchHoverAnimationType::HOVER;
    } else {
        touchHoverType_ = TouchHoverAnimationType::NONE;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void SwitchPattern::HandleDragStart()
{
    isDragEvent_ = true;
}

void SwitchPattern::HandleDragUpdate(const GestureEvent& info)
{
    dragOffsetX_ = static_cast<float>(info.GetLocalLocation().GetX());
    TAG_LOGI(AceLogTag::ACE_SELECT_COMPONENT, "switch drag update %{public}f", dragOffsetX_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void SwitchPattern::HandleDragEnd()
{
    auto mainSize = GetSwitchWidth();
    auto contentOffset = GetSwitchContentOffsetX();
    if ((direction_ == TextDirection::RTL &&
        ((isOn_.value() && dragOffsetX_ - contentOffset > mainSize / 2) ||
        (!isOn_.value() && dragOffsetX_ - contentOffset <= mainSize / 2))) ||
        (direction_ != TextDirection::RTL &&
        ((isOn_.value() && dragOffsetX_ - contentOffset < mainSize / 2) ||
        (!isOn_.value() && dragOffsetX_ - contentOffset >= mainSize / 2)))) {
        OnClick();
    }
    isDragEvent_ = false;
    dragOffsetX_ = 0.0f;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

bool SwitchPattern::IsOutOfBoundary(double mainOffset) const
{
    return mainOffset < 0 || mainOffset > GetSwitchWidth();
}

// Set the default hot zone for the component.
void SwitchPattern::AddHotZoneRect()
{
    hotZoneOffset_.SetX(offset_.GetX() - hotZoneHorizontalSize_.ConvertToPx());
    hotZoneOffset_.SetY(offset_.GetY() - hotZoneVerticalSize_.ConvertToPx());
    hotZoneSize_.SetWidth(size_.Width() + HOTZONE_SPACE * hotZoneHorizontalSize_.ConvertToPx());
    hotZoneSize_.SetHeight(size_.Height() + HOTZONE_SPACE * hotZoneVerticalSize_.ConvertToPx());
    DimensionRect hotZoneRegion;
    hotZoneRegion.SetSize(DimensionSize(Dimension(hotZoneSize_.Width()), Dimension(hotZoneSize_.Height())));
    hotZoneRegion.SetOffset(DimensionOffset(Dimension(hotZoneOffset_.GetX()), Dimension(hotZoneOffset_.GetY())));
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gestureHub = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    std::vector<DimensionRect> hotZoneRegions;
    hotZoneRegions.emplace_back(hotZoneRegion);
    gestureHub->SetResponseRegion(hotZoneRegions);
}

void SwitchPattern::RemoveLastHotZoneRect() const
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->RemoveLastHotZoneRect();
}

std::string SwitchPattern::ProvideRestoreInfo()
{
    auto jsonObj = JsonUtil::Create(true);
    jsonObj->Put("IsOn", isOn_.value_or(false));
    return jsonObj->ToString();
}

void SwitchPattern::OnRestoreInfo(const std::string& restoreInfo)
{
    auto switchPaintProperty = GetPaintProperty<SwitchPaintProperty>();
    CHECK_NULL_VOID(switchPaintProperty);
    auto info = JsonUtil::ParseJsonString(restoreInfo);
    if (!info->IsValid() || !info->IsObject()) {
        return;
    }
    auto jsonIsOn = info->GetValue("IsOn");
    switchPaintProperty->UpdateIsOn(jsonIsOn->GetBool());
    OnModifyDone();
}

void SwitchPattern::OnColorConfigurationUpdate()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    CHECK_NULL_VOID(paintMethod_);
    auto switchModifier = paintMethod_->GetSwitchModifier();
    CHECK_NULL_VOID(switchModifier);
    switchModifier->InitializeParam(host->GetThemeScopeId());
    if (SystemProperties::ConfigChangePerform()) {
        auto pipeline = host->GetContext();
        CHECK_NULL_VOID(pipeline);
        auto theme = pipeline->GetTheme<SwitchTheme>();
        CHECK_NULL_VOID(theme);
        auto pops = host->GetPaintProperty<SwitchPaintProperty>();
        CHECK_NULL_VOID(pops);
        if (!pops->GetSelectedColorSetByUserValue(false)) {
            Color color = theme->GetActiveColor();
            pops->UpdateSelectedColor(color);
        }
        if (!pops->GetSwitchPointColorSetByUserValue(false)) {
            Color color = theme->GetPointColor();
            pops->UpdateSwitchPointColor(color);
        }
        if (!pops->GetUnselectedColorSetByUserValue(false)) {
            Color color = theme->GetInactiveColor();
            pops->UpdateUnselectedColor(color);
        }
    }
    host->MarkDirtyNode();
    host->SetNeedCallChildrenUpdate(false);
}

bool SwitchPattern::OnThemeScopeUpdate(int32_t themeScopeId)
{
    bool result = false;
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto paintProperty = host->GetPaintProperty<SwitchPaintProperty>();
    CHECK_NULL_RETURN(paintProperty, false);

    if (!paintProperty->HasSelectedColor() || !paintProperty->HasSwitchPointColor()) {
        result = true;
    }

    return result;
}

void SwitchPattern::DumpInfo()
{
    auto paintProperty = GetPaintProperty<SwitchPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    if (paintProperty->HasIsOn()) {
        DumpLog::GetInstance().AddDesc("IsOn: " + std::string(paintProperty->GetIsOn().value() ? "true" : "false"));
    }
    if (paintProperty->HasSelectedColor()) {
        DumpLog::GetInstance().AddDesc("SelectedColor: " + paintProperty->GetSelectedColor().value().ToString());
    }
    if (paintProperty->HasUnselectedColor()) {
        DumpLog::GetInstance().AddDesc("UnselectedColor: " + paintProperty->GetUnselectedColor().value().ToString());
    }
    if (paintProperty->HasSwitchPointColor()) {
        DumpLog::GetInstance().AddDesc("SwitchPointColor: " + paintProperty->GetSwitchPointColor().value().ToString());
    }
    if (paintProperty->HasPointRadius()) {
        DumpLog::GetInstance().AddDesc("PointRadius: " + paintProperty->GetPointRadius().value().ToString());
    }
    if (paintProperty->HasTrackBorderRadius()) {
        DumpLog::GetInstance().AddDesc(
            "TrackBorderRadius: " + paintProperty->GetTrackBorderRadius().value().ToString());
    }
}

void SwitchPattern::SetSwitchIsOn(bool ison)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetOrCreateEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    auto enabled = eventHub->IsEnabled();
    if (!enabled) {
        return;
    }
    auto paintProperty = host->GetPaintProperty<SwitchPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    paintProperty->UpdateIsOn(ison);
    OnModifyDone();
}

void SwitchPattern::FireBuilder()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (!makeFunc_.has_value()) {
        auto children = host->GetChildren();
        for (const auto& child : children) {
            if (child->GetId() == nodeId_) {
                host->RemoveChildAndReturnIndex(child);
                host->MarkNeedFrameFlushDirty(PROPERTY_UPDATE_MEASURE);
                break;
            }
        }
        return;
    }
    auto node = BuildContentModifierNode();
    if (contentModifierNode_ == node) {
        return;
    }
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->UpdateBackgroundColor(Color::TRANSPARENT);
    host->RemoveChildAndReturnIndex(contentModifierNode_);
    contentModifierNode_ = node;
    CHECK_NULL_VOID(contentModifierNode_);
    nodeId_ = contentModifierNode_->GetId();
    host->AddChild(contentModifierNode_, 0);
    host->MarkNeedFrameFlushDirty(PROPERTY_UPDATE_MEASURE);
}

RefPtr<FrameNode> SwitchPattern::BuildContentModifierNode()
{
    if (!makeFunc_.has_value()) {
        return nullptr;
    }
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto paintProperty = host->GetPaintProperty<SwitchPaintProperty>();
    CHECK_NULL_RETURN(paintProperty, nullptr);
    auto eventHub = host->GetOrCreateEventHub<SwitchEventHub>();
    CHECK_NULL_RETURN(eventHub, nullptr);
    auto enabled = eventHub->IsEnabled();
    bool isOn = false;
    if (paintProperty->HasIsOn()) {
        isOn = paintProperty->GetIsOnValue();
    }
    ToggleConfiguration toggleConfiguration(enabled, isOn);
    return (makeFunc_.value())(toggleConfiguration);
}
} // namespace OHOS::Ace::NG
