/*
 * Copyright (c) 2022-2026 Huawei Device Co., Ltd.
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

#include "interfaces/inner_api/ui_session/ui_session_manager.h"

#include "base/log/dump_log.h"
#include "base/utils/system_properties.h"
#include "core/common/recorder/node_data_cache.h"
#include "core/components/toggle/toggle_theme.h"
#include "core/components/common/properties/ui_material.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/event/state_style_manager.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/property/position_property.h"
#include "core/components_ng/property/border_property.h"
#include "core/components_ng/render/animation_utils.h"
#include "core/components_ng/render/adapter/rosen_effect_converter.h"
#include "core/components/common/properties/blur_style_option.h"
#include "ui/properties/ui_material_structs.h"
#ifndef ACE_UNITTEST
#include "ui_effect/effect/include/brightness_blender.h"
#endif
#include "core/animation/curve.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t DEFAULT_DURATION = 200;
const Color ITEM_FILL_COLOR = Color::TRANSPARENT;
constexpr double NUMBER_TWO = 2.0;

// Drag animation constants
constexpr float DRAG_FRAME_BASE_SCALE = 2.0f;
constexpr float DRAG_FRAME_PRESS_START_SCALE = 1.1f;
constexpr float DRAG_FRAME_PRESS_END_SCALE = 1.0f;
constexpr float DRAG_FRAME_DRAG_SCALE_X = 1.06f;
constexpr float DRAG_FRAME_DRAG_SCALE_Y = 0.95f;
constexpr int32_t DRAG_FRAME_ANIMATION_DURATION = 150;
// Spring curve: velocity=0, mass=1, stiffness=305, damping=24
constexpr float SPRING_VELOCITY = 0.0f;
constexpr float SPRING_MASS = 1.0f;
constexpr float SPRING_STIFFNESS = 305.0f;
constexpr float SPRING_DAMPING = 24.0f;

// Low-grade material constants
constexpr float LOW_GRADE_SHRINK_SCALE = 0.78f;
constexpr float LOW_GRADE_EXPAND_SCALE = 1.56f;
constexpr float LOW_GRADE_SPRING_VELOCITY = 0.0f;
constexpr float LOW_GRADE_SPRING_MASS = 1.0f;
constexpr float LOW_GRADE_SPRING_STIFFNESS = 224.0f;
constexpr float LOW_GRADE_SPRING_DAMPING = 12.0f;

constexpr int32_t LONG_PRESS_DELAY_MS = 400;

constexpr float LIGHT_POSITION_Z_SCALE = 1.5f;
constexpr int32_t  HOTZONE_SPACE = 2;
const std::string INJECTION_CMD_FORMAT_ERROR = "Invalid injection command format.";
const std::string COMPONENT_IN_READONLY = "The component is in read-only state.";
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
    auto hub = host->GetEventHub<EventHub>();
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
    ResetHostMaterialEffects();
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
    auto eventHub = host->GetEventHub<EventHub>();
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
    auto eventHub = GetEventHub<SwitchEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->UpdateChangeEvent(isSelected);
    ReportChangeEvent(isSelected);
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
    switchModifier->SetIsOn(isOn_.value_or(false));
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

void SwitchPattern::UpdateChangeEvent()
{
    auto switchEventHub = GetEventHub<SwitchEventHub>();
    CHECK_NULL_VOID(switchEventHub);
    auto isOn = isOn_.value_or(false);
    switchEventHub->UpdateChangeEvent(isOn);
    ReportChangeEvent(isOn);
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
    pendingHide_ = false;
    ShowMaterialNode();
    StartLongPressTimer();
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
    if (longPressTask_) {
        longPressTask_.Cancel();
    }
    if (IsHighGradeMaterial() && HasSystemMaterial() && (dragPointNode_ || dragFrameNode_)) {
        pendingHide_ = true;
    } else {
        HideMaterialNode();
    }
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

void SwitchPattern::HandleLongPress()
{
    if (!HasSystemMaterial()) { return; }
    if (IsHighGradeMaterial()) {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto renderContext = host->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        renderContext->SetAlphaOffscreen(false);
        HandleHighGradeLongPress();
    } else {
        HandleLowGradeLongPress();
    }
}

void SwitchPattern::StartLongPressTimer()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    auto taskExecutor = pipeline->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);

    longPressTask_.Reset([weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleLongPress();
    });
    taskExecutor->PostDelayedTask(longPressTask_,
        TaskExecutor::TaskType::UI, LONG_PRESS_DELAY_MS, "ArkUISwitchLongPress");
}

void SwitchPattern::HandleHighGradeLongPress()
{
    CreateDragFrameNode();
    CHECK_NULL_VOID(dragFrameNode_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto frameRC = dragFrameNode_->GetRenderContext();
    CHECK_NULL_VOID(frameRC);
    host->AddChild(dragFrameNode_);
    isFrameNodeVisible_ = true;
    RegisterMaterialNodePositionCallback();
    ApplyDragFrameNodeSystemMaterial();
    AnimationUtils::ExecuteWithoutAnimation(
        [frameRC]() {
            frameRC->UpdateOpacity(0.0);
            frameRC->UpdateTransformScale({ DRAG_FRAME_PRESS_START_SCALE, DRAG_FRAME_PRESS_START_SCALE });
        },
        host->GetContextRefPtr());
    AnimationOption option = CreateDragAnimationOption();
    AnimationUtils::Animate(option,
        [weak = WeakClaim(this), frameRC]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            frameRC->UpdateOpacity(1.0);
            if (pattern->isDragEvent_) {
                frameRC->UpdateTransformScale({ DRAG_FRAME_DRAG_SCALE_X, DRAG_FRAME_DRAG_SCALE_Y });
            } else {
                frameRC->UpdateTransformScale({ DRAG_FRAME_PRESS_END_SCALE, DRAG_FRAME_PRESS_END_SCALE });
            }
        },
        nullptr, nullptr, host->GetContextRefPtr());
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
}

void SwitchPattern::HandleLowGradeLongPress()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto switchModifier = paintMethod_ ? paintMethod_->GetSwitchModifier() : nullptr;
    CHECK_NULL_VOID(switchModifier);
    AnimationOption option = CreateLowGradeSpringOption();
    AnimationUtils::Animate(
        option,
        [switchModifier]() {
            if (switchModifier) {
                switchModifier->SetPointScale(LOW_GRADE_SHRINK_SCALE);
            }
        },
        nullptr, nullptr, host->GetContextRefPtr());
    AnimationUtils::Animate(
        option,
        [switchModifier]() {
            if (switchModifier) {
                switchModifier->SetPointScale(LOW_GRADE_EXPAND_SCALE);
            }
        },
        nullptr, nullptr, host->GetContextRefPtr());
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
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
    auto eventHub = GetHost()->GetEventHub<SwitchEventHub>();
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
    AnimateToDragState();
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
    auto midPoint = (mainSize + height_) / NUMBER_TWO;
    if ((direction_ == TextDirection::RTL &&
        ((isOn_.value_or(false) && dragOffsetX_ - contentOffset > midPoint) ||
        (!isOn_.value_or(false) && dragOffsetX_ - contentOffset <= midPoint))) ||
        (direction_ != TextDirection::RTL &&
        ((isOn_.value_or(false) && dragOffsetX_ - contentOffset < midPoint) ||
        (!isOn_.value_or(false) && dragOffsetX_ - contentOffset >= midPoint)))) {
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

float SwitchPattern::GetPointRadius() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, 0.0f);
    auto switchTheme = host->GetTheme<SwitchTheme>(true);
    CHECK_NULL_RETURN(switchTheme, 0.0f);

    auto height = size_.Height();
    auto radius = height / NUMBER_TWO;
    auto actualGap = GetActualGap();
    return radius - actualGap;
}

float SwitchPattern::GetActualGap() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, 0.0f);
    auto switchTheme = host->GetTheme<SwitchTheme>(true);
    CHECK_NULL_RETURN(switchTheme, 0.0f);

    auto height = size_.Height();
    constexpr Dimension radiusGap = 2.0_vp;
    return radiusGap.ConvertToPx() * height /
        (switchTheme->GetHeight() - switchTheme->GetHotZoneVerticalPadding() * NUMBER_TWO).ConvertToPx();
}

bool SwitchPattern::HasSystemMaterial() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, false);
    auto material = renderContext->GetSystemMaterial();
    return material != nullptr;
}

bool SwitchPattern::IsHighGradeMaterial() const
{
    auto level = SystemProperties::GetUiMaterialLevel();
    return level == UiMaterialLevel::EXQUISITE || level == UiMaterialLevel::GENTLE;
}

void SwitchPattern::ResetHostMaterialEffects()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);

    auto material = renderContext->GetSystemMaterial();
    CHECK_NULL_VOID(material);

    // Clear SO-level material effects
    MaterialUtils::CallSetMaterial(AceType::RawPtr(host), nullptr);

    // Clear RS material filter
    renderContext->UpdateUiMaterialFilter(nullptr);

    // Reset visual properties (handles SetSystemMaterialImmediate path)
    auto preBackgroundColor = renderContext->GetPreBackgroundColor();
    if (preBackgroundColor.has_value()) {
        renderContext->UpdateBackgroundColor(preBackgroundColor.value());
    } else {
        renderContext->ResetBackgroundColor();
        renderContext->OnBackgroundColorUpdate(Color::TRANSPARENT);
    }

    auto preBorderWidth = renderContext->GetPreBorderWidth();
    if (preBorderWidth.has_value()) {
        auto layoutProperty = host->GetLayoutProperty();
        if (layoutProperty) {
            layoutProperty->UpdateBorderWidth(preBorderWidth.value());
        }
        renderContext->UpdateBorderWidth(preBorderWidth.value());
    } else {
        BorderWidthProperty borderWidth;
        borderWidth.SetBorderWidth(Dimension(0));
        auto layoutProperty = host->GetLayoutProperty();
        if (layoutProperty) {
            layoutProperty->UpdateBorderWidth(borderWidth);
        }
        renderContext->UpdateBorderWidth(borderWidth);
    }

    auto preBorderColor = renderContext->GetPreBorderColor();
    if (preBorderColor.has_value()) {
        renderContext->UpdateBorderColor(preBorderColor.value());
    } else {
        renderContext->ResetBorderColor();
    }

    auto preBackShadow = renderContext->GetPreBackShadow();
    if (preBackShadow.has_value()) {
        renderContext->UpdateBackShadow(preBackShadow.value());
    } else {
        renderContext->ResetBackShadow();
    }

    // DO NOT clear uiMaterial_ from RenderContext - needed for dragFrameNode
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

AnimationOption SwitchPattern::CreateDragAnimationOption() const
{
    AnimationOption option;
    auto curve = AceType::MakeRefPtr<InterpolatingSpring>(
        SPRING_VELOCITY, SPRING_MASS, SPRING_STIFFNESS, SPRING_DAMPING);
    option.SetCurve(curve);
    option.SetDuration(DRAG_FRAME_ANIMATION_DURATION);
    option.SetFillMode(FillMode::FORWARDS);
    return option;
}

BlurStyleOption SwitchPattern::CreateDragBlurStyleOption(float scale) const
{
    BlurStyleOption option;
    option.blurStyle = BlurStyle::THIN;
    option.colorMode = ThemeColorMode::LIGHT;
    option.adaptiveColor = AdaptiveColor::DEFAULT;
    option.scale = scale;
    return option;
}

AnimationOption SwitchPattern::CreateLowGradeSpringOption() const
{
    AnimationOption option;
    auto curve = AceType::MakeRefPtr<InterpolatingSpring>(
        LOW_GRADE_SPRING_VELOCITY, LOW_GRADE_SPRING_MASS,
        LOW_GRADE_SPRING_STIFFNESS, LOW_GRADE_SPRING_DAMPING);
    option.SetCurve(curve);
    option.SetDuration(DRAG_FRAME_ANIMATION_DURATION);
    option.SetFillMode(FillMode::FORWARDS);
    return option;
}

void SwitchPattern::HideMaterialNodes()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (dragFrameNode_ && isFrameNodeVisible_) {
        host->RemoveChild(dragFrameNode_);
        isFrameNodeVisible_ = false;
    }
    if (dragPointNode_) {
        host->RemoveChild(dragPointNode_);
    }
    if (blurCoverNode_) {
        host->RemoveChild(blurCoverNode_);
    }
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->SetAlphaOffscreen(true);
}

void SwitchPattern::CreateDragFrameNode()
{
    if (dragFrameNode_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    dragFrameNode_ = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, nodeId, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    CHECK_NULL_VOID(dragFrameNode_);

    auto renderContext = dragFrameNode_->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto paintProperty = GetPaintProperty<SwitchPaintProperty>();
    CHECK_NULL_VOID(paintProperty);

    auto pointRadius = GetPointRadius();
    auto pointDiameter = pointRadius * NUMBER_TWO;
    auto frameSize = pointDiameter * DRAG_FRAME_BASE_SCALE;

    BorderRadiusProperty borderRadius;
    borderRadius.SetRadius(Dimension(frameSize / NUMBER_TWO, DimensionUnit::PX));
    renderContext->UpdateBorderRadius(borderRadius);
    renderContext->UpdateBackgroundColor(Color::TRANSPARENT);

    dragFrameNode_->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(frameSize), CalcLength(frameSize)));

    if (paintProperty->HasSwitchPointColor()) {
        ViewAbstract::SetLightPosition(AceType::RawPtr(dragFrameNode_),
            CalcDimension(pointDiameter, DimensionUnit::PX), CalcDimension(pointDiameter, DimensionUnit::PX),
            CalcDimension(pointDiameter, DimensionUnit::PX));
        ViewAbstract::SetLightColor(AceType::RawPtr(dragFrameNode_), paintProperty->GetSwitchPointColor().value());
        ViewAbstract::SetLightIntensity(AceType::RawPtr(dragFrameNode_), 1.5f);
        ViewAbstract::SetLightIlluminated(AceType::RawPtr(dragFrameNode_), 2u);
    }
}

void SwitchPattern::CreateDragPointNode()
{
    if (dragPointNode_) {
        return;
    }

    auto host = GetHost();
    CHECK_NULL_VOID(host);

    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    dragPointNode_ = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, nodeId, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    CHECK_NULL_VOID(dragPointNode_);

    auto renderContext = dragPointNode_->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto paintProperty = GetPaintProperty<SwitchPaintProperty>();
    CHECK_NULL_VOID(paintProperty);

    auto trackWidth = size_.Width();
    auto trackHeight = size_.Height();
    float halfHeight = trackHeight / NUMBER_TWO;

    dragPointNode_->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(trackWidth), CalcLength(trackHeight)));

    BorderRadiusProperty borderRadius;
    borderRadius.SetRadius(Dimension(halfHeight, DimensionUnit::PX));
    renderContext->UpdateBorderRadius(borderRadius);
    renderContext->UpdateBackgroundColor(Color::TRANSPARENT);

    auto pointRadius = GetPointRadius();
    float initialLightX = isOn_.value_or(false) ? (trackWidth - halfHeight) : halfHeight;
    if (paintProperty->HasSwitchPointColor()) {
        ViewAbstract::SetLightPosition(AceType::RawPtr(dragPointNode_),
            CalcDimension(initialLightX, DimensionUnit::PX), CalcDimension(halfHeight, DimensionUnit::PX),
            CalcDimension(pointRadius * LIGHT_POSITION_Z_SCALE, DimensionUnit::PX));
        ViewAbstract::SetLightColor(AceType::RawPtr(dragPointNode_), paintProperty->GetSwitchPointColor().value());
        ViewAbstract::SetLightIntensity(AceType::RawPtr(dragPointNode_), 10.0f);
        ViewAbstract::SetLightIlluminated(AceType::RawPtr(dragPointNode_), 2u);
    }
}

void SwitchPattern::CreateBlurCoverNode()
{
    if (blurCoverNode_) {
        return;
    }

    auto host = GetHost();
    CHECK_NULL_VOID(host);

    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    blurCoverNode_ = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, nodeId, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    CHECK_NULL_VOID(blurCoverNode_);

    auto renderContext = blurCoverNode_->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto paintProperty = GetPaintProperty<SwitchPaintProperty>();
    CHECK_NULL_VOID(paintProperty);

    renderContext->UpdateBackgroundColor(Color::TRANSPARENT);

    auto pointRadius = GetPointRadius();
    auto pointDiameter = pointRadius * NUMBER_TWO;
    auto frameSize = pointDiameter * DRAG_FRAME_BASE_SCALE;

    blurCoverNode_->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(frameSize), CalcLength(frameSize)));

    BorderRadiusProperty borderRadius;
    borderRadius.SetRadius(Dimension(frameSize / NUMBER_TWO, DimensionUnit::PX));
    renderContext->UpdateBorderRadius(borderRadius);
}

void SwitchPattern::UpdateMaterialNodePosition(float centerX, float centerY, float pointRadius)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pointDiameter = pointRadius * NUMBER_TWO;
    auto frameSize = pointDiameter * DRAG_FRAME_BASE_SCALE;
    float frameNodeX = centerX - frameSize / NUMBER_TWO;
    float frameNodeY = centerY - frameSize / NUMBER_TWO;
    if (dragFrameNode_) {
        dragFrameNode_->GetLayoutProperty()->UpdateUserDefinedIdealSize(
            CalcSize(CalcLength(frameSize), CalcLength(frameSize)));
        auto frameRC = dragFrameNode_->GetRenderContext();
        if (frameRC) {
            frameRC->UpdatePosition(OffsetT<Dimension>(Dimension(frameNodeX), Dimension(frameNodeY)));
        }
    }
    if (blurCoverNode_) {
        blurCoverNode_->GetLayoutProperty()->UpdateUserDefinedIdealSize(
            CalcSize(CalcLength(frameSize), CalcLength(frameSize)));
        auto blurRC = blurCoverNode_->GetRenderContext();
        if (blurRC) {
            blurRC->UpdatePosition(OffsetT<Dimension>(Dimension(frameNodeX), Dimension(frameNodeY)));
        }
    }
    if (dragPointNode_) {
        auto pointRC = dragPointNode_->GetRenderContext();
        if (pointRC) {
            auto paintProperty = GetPaintProperty<SwitchPaintProperty>();
            if (paintProperty && paintProperty->HasSwitchPointColor()) {
                float lightX = centerX - offset_.GetX();
                float lightY = centerY - offset_.GetY();
                ViewAbstract::SetLightPosition(AceType::RawPtr(dragPointNode_),
                    CalcDimension(lightX, DimensionUnit::PX), CalcDimension(lightY, DimensionUnit::PX),
                    CalcDimension(pointRadius * LIGHT_POSITION_Z_SCALE, DimensionUnit::PX));
            }
        }
    }
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
}

void SwitchPattern::RegisterMaterialNodePositionCallback()
{
    auto switchModifier = paintMethod_ ? paintMethod_->GetSwitchModifier() : nullptr;
    CHECK_NULL_VOID(switchModifier);
    switchModifier->SetMaterialNodePositionCallback(
        [weak = WeakClaim(this)](float centerX, float centerY, float pointRadius) {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->UpdateMaterialNodePosition(centerX, centerY, pointRadius);
        });
    paintMethod_->SetSlideFinishedCallback(
        [weak = WeakClaim(this)]() {
            auto pattern = weak.Upgrade();
            if (pattern && pattern->pendingHide_) {
                pattern->pendingHide_ = false;
                pattern->HideMaterialNode();
            }
        });
}

void SwitchPattern::ShowMaterialNode()
{
    if (!HasSystemMaterial()) { return; }
    if (!IsHighGradeMaterial()) { return; }
    CreateDragFrameNode();
    CreateDragPointNode();
    CreateBlurCoverNode();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pointRC = dragPointNode_ ? dragPointNode_->GetRenderContext() : nullptr;
    auto blurRC = blurCoverNode_ ? blurCoverNode_->GetRenderContext() : nullptr;
    if (dragPointNode_) {
        auto pointRCNonNull = dragPointNode_->GetRenderContext();
        if (pointRCNonNull) {
            pointRCNonNull->UpdatePosition(
                OffsetT<Dimension>(Dimension(offset_.GetX()), Dimension(offset_.GetY())));
        }
        host->AddChild(dragPointNode_);
    }
    if (blurCoverNode_) {
        host->AddChild(blurCoverNode_);
    }
    RegisterMaterialNodePositionCallback();
    AnimationUtils::ExecuteWithoutAnimation(
        [pointRC, blurRC]() {
            if (pointRC) { pointRC->UpdateOpacity(0.0); }
            if (blurRC) {
                blurRC->UpdateOpacity(0.0);
                blurRC->UpdateTransformScale({ DRAG_FRAME_PRESS_START_SCALE, DRAG_FRAME_PRESS_START_SCALE });
            }
        },
        host->GetContextRefPtr());
    AnimationOption option = CreateDragAnimationOption();
    auto switchModifier = paintMethod_ ? paintMethod_->GetSwitchModifier() : nullptr;
    AnimationUtils::Animate(option,
        [pointRC, blurRC, switchModifier]() {
            if (pointRC) { pointRC->UpdateOpacity(1.0); }
            if (blurRC) {
                blurRC->UpdateOpacity(1.0);
                blurRC->UpdateTransformScale({ DRAG_FRAME_PRESS_END_SCALE, DRAG_FRAME_PRESS_END_SCALE });
            }
            if (switchModifier) { switchModifier->SetPointAlpha(0.0f); }
        },
        nullptr, nullptr, host->GetContextRefPtr());
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
}

void SwitchPattern::AnimateToDragState()
{
    if (!IsHighGradeMaterial()) {
        return;
    }

    auto host = GetHost();
    CHECK_NULL_VOID(host);

    AnimationOption option = CreateDragAnimationOption();
    auto blurRC = blurCoverNode_ ? blurCoverNode_->GetRenderContext() : nullptr;

    if (isFrameNodeVisible_ && dragFrameNode_) {
        auto frameRC = dragFrameNode_->GetRenderContext();
        CHECK_NULL_VOID(frameRC);
        AnimationUtils::Animate(
            option,
            [frameRC, blurRC]() {
                frameRC->UpdateTransformScale({ DRAG_FRAME_DRAG_SCALE_X, DRAG_FRAME_DRAG_SCALE_Y });
                if (blurRC) {
                    blurRC->UpdateTransformScale({ DRAG_FRAME_DRAG_SCALE_X, DRAG_FRAME_DRAG_SCALE_Y });
                }
            },
            nullptr, nullptr, host->GetContextRefPtr());
    } else if (blurRC) {
        AnimationUtils::Animate(
            option,
            [blurRC]() {
                blurRC->UpdateTransformScale({ DRAG_FRAME_DRAG_SCALE_X, DRAG_FRAME_DRAG_SCALE_Y });
            },
            nullptr, nullptr, host->GetContextRefPtr());
    }
}

void SwitchPattern::ResetMaterialNodeAppearance(const RefPtr<RenderContext>& pointRC,
    const RefPtr<RenderContext>& blurRC)
{
    if (isFrameNodeVisible_ && dragFrameNode_) {
        auto frameRC = dragFrameNode_->GetRenderContext();
        if (frameRC) {
            frameRC->UpdateOpacity(1.0);
            frameRC->UpdateTransformScale({ 1.0f, 1.0f });
        }
    }
    if (pointRC) { pointRC->UpdateOpacity(1.0); }
    if (blurRC) {
        blurRC->UpdateOpacity(1.0);
        blurRC->UpdateTransformScale({ 1.0f, 1.0f });
    }
}

void SwitchPattern::AnimateHighGradeHide(const RefPtr<RenderContext>& pointRC,
    const RefPtr<RenderContext>& blurRC, const RefPtr<SwitchModifier>& switchModifier)
{
    if (isFrameNodeVisible_ && dragFrameNode_) {
        auto frameRC = dragFrameNode_->GetRenderContext();
        if (frameRC) {
            frameRC->UpdateOpacity(0.0);
            frameRC->UpdateTransformScale({ DRAG_FRAME_PRESS_START_SCALE, DRAG_FRAME_PRESS_START_SCALE });
        }
    }
    if (pointRC) {
        pointRC->UpdateOpacity(0.0);
    }
    if (blurRC) {
        blurRC->UpdateOpacity(0.0);
        blurRC->UpdateTransformScale({ DRAG_FRAME_PRESS_START_SCALE, DRAG_FRAME_PRESS_START_SCALE });
    }
    if (switchModifier) { switchModifier->SetPointAlpha(1.0f); }
}

void SwitchPattern::HideMaterialNode()
{
    pendingHide_ = false;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (!IsHighGradeMaterial()) {
        auto switchModifier = paintMethod_ ? paintMethod_->GetSwitchModifier() : nullptr;
        CHECK_NULL_VOID(switchModifier);
        AnimationUtils::Animate(CreateLowGradeSpringOption(),
            [switchModifier]() { switchModifier->SetPointScale(1.0f); },
            nullptr, nullptr, host->GetContextRefPtr());
        return;
    }
    auto switchModifier = paintMethod_ ? paintMethod_->GetSwitchModifier() : nullptr;
    auto pointRC = dragPointNode_ ? dragPointNode_->GetRenderContext() : nullptr;
    auto blurRC = blurCoverNode_ ? blurCoverNode_->GetRenderContext() : nullptr;
    AnimationUtils::ExecuteWithoutAnimation(
        [pointRC, blurRC, this]() { ResetMaterialNodeAppearance(pointRC, blurRC); },
        host->GetContextRefPtr());
    AnimationOption option = CreateDragAnimationOption();
    AnimationUtils::Animate(option,
        [pointRC, blurRC, switchModifier, this]() {
            AnimateHighGradeHide(pointRC, blurRC, switchModifier);
        },
        [weak = WeakClaim(this)]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            if (!pattern->isTouch_) { pattern->HideMaterialNodes(); }
        },
        nullptr, host->GetContextRefPtr());
}

void SwitchPattern::ApplyDragFrameNodeSystemMaterial()
{
    CHECK_NULL_VOID(dragFrameNode_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    FrostedGlassParam dragFrameMaterialParam {
        .blurParams = { 1.0f, 50.0f },
        .weightsEmboss = { 0.8f, 0.8f },
        .weightsEdl = { 1.0f, 0.7f },
        .bgRates = { 0.1789f, -0.6972f },
        .bgKBS = { 1.4384f, 0.0718f, 1.2f },
        .bgPos = { 0.3f, 0.5f, 1.0f },
        .bgNeg = { 0.5f, 0.5f, 1.0f },
        .refractParams = { -0.008f, 0.15f, 0.22f },
        .edLightParams = { 0.62f, 0.92f },
        .edLightAngles = { 75.0f, 120.0f },
        .edLightDir = { 0.0f, -1.0f },
        .edLightKBS = { 1.0f, 0.1568f, 1.2f },
        .edLightPos = { 1.0f, 1.5f, 2.0f },
        .edLightNeg = { 1.7f, 3.0f, 1.0f },
        .darkModeBlurParams = { 5.0f, 20.0f },
        .darkModeWeightsEmboss = { 0.8f, 0.8f },
        .darkModeBgRates = { 0.0023f, -0.0176f },
        .darkModeBgKBS = { 0.8414f, 0.0765f, 1.2f },
        .darkModeBgPos = { 0.3f, 1.0f, 1.0f },
        .darkModeBgNeg = { 1.2f, 2.5f, 1.0f },
        .darkModeEdLightAngles = { 75.0f, 120.0f },
        .darkModeEdLightKBS = { 1.0f, 0.2268f, 1.2f },
    };
    constexpr float MIN_POINT_SIZE = 32.0f;
    constexpr float MAX_POINT_SIZE = 56.0f;
    float pointDiameter = GetPointRadius() * NUMBER_TWO;
    float t = std::clamp((pointDiameter - MIN_POINT_SIZE) / (MAX_POINT_SIZE - MIN_POINT_SIZE), 0.0f, 1.0f);
    dragFrameMaterialParam.refractParams[0] = -0.008f + t * (-0.01f - (-0.008f));
    dragFrameMaterialParam.refractParams[1] = 0.15f + t * (0.13f - 0.15f);
    float dipScale = static_cast<float>(pipeline->GetDipScale());
    auto filter = RosenEffectConverter::ConvertToFrostedGlassFilter(dragFrameMaterialParam, dipScale);
    if (filter) {
        auto renderContext = dragFrameNode_->GetRenderContext();
        if (renderContext) {
            renderContext->SetMaterialWithQualityLevel(filter, UiMaterialFilterQuality::DEFAULT);
            renderContext->UpdateBackShadow(MaterialUtils::GetImmersiveShadow(dipScale));
        }
    }
    ResetHostMaterialEffects();
#ifndef ACE_UNITTEST
    ApplyDragFrameNodeBlendMode();
#endif
}

#ifndef ACE_UNITTEST
void SwitchPattern::ApplyDragFrameNodeBlendMode()
{
    CHECK_NULL_VOID(dragFrameNode_);
    static const auto brightnessBlender = CreateBrightnessBlender();
    ViewAbstract::SetBlender(AceType::RawPtr(dragFrameNode_), brightnessBlender.get());
    ViewAbstract::SetBlendApplyType(AceType::RawPtr(dragFrameNode_), BlendApplyType::OFFSCREEN);
}

std::shared_ptr<Rosen::BrightnessBlender> SwitchPattern::CreateBrightnessBlender()
{
    auto blender = std::make_shared<Rosen::BrightnessBlender>();
    blender->SetCubicRate(0.0f);
    blender->SetQuadRate(0.0f);
    blender->SetLinearRate(1.048f);
    blender->SetDegree(0.37647f);
    blender->SetSaturation(1.5f);
    blender->SetPositiveCoeff(Rosen::Vector3f(3.5f, 4.0f, 1.0f));
    blender->SetNegativeCoeff(Rosen::Vector3f(1.0f, 2.0f, 2.0f));
    blender->SetFraction(0.0f);
    return blender;
}
#endif

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
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto switchTheme = pipeline->GetTheme<SwitchTheme>(host->GetThemeScopeId());
    CHECK_NULL_VOID(switchTheme);
    CHECK_NULL_VOID(paintMethod_);
    auto switchModifier = paintMethod_->GetSwitchModifier();
    CHECK_NULL_VOID(switchModifier);
    switchModifier->InitializeParam(host->GetThemeScopeId());
    if (SystemProperties::ConfigChangePerform()) {
        auto pipeline = host->GetContext();
        CHECK_NULL_VOID(pipeline);
        auto theme = pipeline->GetTheme<SwitchTheme>(host->GetThemeScopeId());
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

void SwitchPattern::DumpSimplifyInfoOnlyForParamConfig(std::shared_ptr<JsonValue>& json, ParamConfig config)
{
    auto paintProperty = GetPaintProperty<SwitchPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    if (paintProperty->HasIsOn() && config.interactionInfo) {
        json->Put("isOn", paintProperty->GetIsOn().value() ? "true" : "false");
    }
}

void SwitchPattern::SetSwitchIsOn(bool ison)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<EventHub>();
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
    auto eventHub = host->GetEventHub<SwitchEventHub>();
    CHECK_NULL_RETURN(eventHub, nullptr);
    auto enabled = eventHub->IsEnabled();
    bool isOn = false;
    if (paintProperty->HasIsOn()) {
        isOn = paintProperty->GetIsOnValue();
    }
    ToggleConfiguration toggleConfiguration(enabled, isOn);
    return (makeFunc_.value())(toggleConfiguration);
}

bool SwitchPattern::ParseCommand(const std::string& command, bool& isOn)
{
    auto jsonObj = JsonUtil::ParseJsonString(command);
    if (!jsonObj->IsValid() || !jsonObj->IsObject()) {
        ReportInjectionResult(false, INJECTION_CMD_FORMAT_ERROR);
        return false;
    }
    auto cmdObj = jsonObj->GetValue("cmd");
    if (!cmdObj->IsValid() || !cmdObj->IsString()) {
        ReportInjectionResult(false, INJECTION_CMD_FORMAT_ERROR);
        return false;
    }
    auto cmdType = cmdObj->GetString();
    if (cmdType != "onToggleChange") {
        ReportInjectionResult(false, INJECTION_CMD_FORMAT_ERROR);
        return false;
    }
    auto paramJson = jsonObj->GetValue("params");
    if (!paramJson->IsValid() || !paramJson->IsObject()) {
        ReportInjectionResult(false, INJECTION_CMD_FORMAT_ERROR);
        return false;
    }
    auto isOnJson = paramJson->GetValue("isOn");
    if (!isOnJson->IsValid() || !isOnJson->IsBool()) {
        ReportInjectionResult(false, INJECTION_CMD_FORMAT_ERROR);
        return false;
    }
    isOn = isOnJson->GetBool();
    return true;
}

int32_t SwitchPattern::OnInjectionEvent(const std::string& command)
{
    bool isOn = false;
    auto ret = ParseCommand(command, isOn);
    CHECK_EQUAL_RETURN(ret, false, RET_FAILED);
    auto host = GetHost();
    CHECK_NULL_RETURN(host, RET_FAILED);
    auto eventHub = host->GetEventHub<EventHub>();
    CHECK_NULL_RETURN(eventHub, RET_FAILED);
    if (!eventHub->IsEnabled()) {
        ReportInjectionResult(false, COMPONENT_IN_READONLY);
        return RET_FAILED;
    }
    SetSwitchIsOn(isOn);
    ReportInjectionResult(true, "");
    return RET_SUCCESS;
}

void SwitchPattern::ReportChangeEvent(bool isOn)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto nodeId = host->GetId();
    auto params = JsonUtil::Create();
    CHECK_NULL_VOID(params);
    params->Put("nodeId", nodeId);
    params->Put("isOn", isOn);
    auto json = JsonUtil::Create();
    CHECK_NULL_VOID(json);
    json->Put("event", "onToggleChange");
    json->Put("params", params);
    UiSessionManager::GetInstance()->ReportComponentChangeEvent(
        "result", json->ToString(), ComponentEventType::COMPONENT_EVENT_SELECT);
}

bool SwitchPattern::ReportInjectionResult(bool isSuccess, const std::string& reason)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto nodeId = host->GetId();
    CHECK_NULL_RETURN(nodeId, false);
    auto result = JsonUtil::Create();
    CHECK_NULL_RETURN(result, false);
    result->Put("nodeId", nodeId);
    result->Put("event", "onToggleChange");
    result->Put("result", isSuccess ? "success" : "failed");
    result->Put("reason", reason.c_str());
    UiSessionManager::GetInstance()->ReportComponentChangeEvent(
        "ToggleResult", result->ToString(), ComponentEventType::COMPONENT_EVENT_SELECT);
    return true;
}
} // namespace OHOS::Ace::NG
