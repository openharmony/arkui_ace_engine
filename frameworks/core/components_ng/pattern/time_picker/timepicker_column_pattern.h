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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TIME_PICKER_TIME_PICKER_COLUMN_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TIME_PICKER_TIME_PICKER_COLUMN_PATTERN_H

#include <utility>

#include "adapter/ohos/entrance/picker/picker_haptic_interface.h"
#include "base/i18n/localization.h"
#include "core/components/common/properties/color.h"
#include "core/components/picker/picker_base_component.h"
#include "core/components/picker/picker_date_component.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/time_picker/timepicker_column_accessibility_property.h"
#include "core/components_ng/pattern/time_picker/timepicker_column_layout_algorithm.h"
#include "core/components_ng/pattern/time_picker/timepicker_layout_property.h"
#include "core/components_ng/pattern/time_picker/toss_animation_controller.h"
#include "core/components_ng/pattern/picker_utils/picker_column_pattern_utils.h"
#ifdef SUPPORT_DIGITAL_CROWN
#include "core/event/crown_event.h"
#endif

namespace OHOS::Ace::NG {

using ColumnChangeCallback = std::function<void(const RefPtr<FrameNode>&, bool, uint32_t, bool)>;
using ColumnFinishCallback = std::function<void(bool)>;
using EventCallback = std::function<void(bool)>;

struct TimeTextProperties {
    Dimension upFontSize;
    Dimension fontSize;
    Dimension downFontSize;
    FontWeight upFontWeight;
    FontWeight fontWeight;
    FontWeight downFontWeight;
    Color upColor;
    Color currentColor;
    Color downColor;
};

struct TimePickerOptionProperty {
    float height = 0.0f;
    float fontheight = 0.0f;
    float prevDistance = 0.0f; // between the prev item and itself when scroll up
    float nextDistance = 0.0f; // between the next item and itself when scroll down
};

class TimePickerEventParam : public virtual AceType {
    DECLARE_ACE_TYPE(TimePickerEventParam, AceType)

public:
    WeakPtr<FrameNode> instance_;
    int32_t itemIndex_ = 0;
    int32_t itemTotalCounts_ = 0;
};

enum class TimePickerScrollDirection {
    UP = 0,
    DOWN,
};
enum class TimePickerOptionIndex {
    COLUMN_INDEX_0 = 0,
    COLUMN_INDEX_1,
    COLUMN_INDEX_2,
    COLUMN_INDEX_3,
    COLUMN_INDEX_4,
    COLUMN_INDEX_5,
    COLUMN_INDEX_6,
};

class TimePickerColumnPattern : public LinearLayoutPattern {
    DECLARE_ACE_TYPE(TimePickerColumnPattern, LinearLayoutPattern);

public:
    TimePickerColumnPattern() : LinearLayoutPattern(true) {};
    ~TimePickerColumnPattern() override
    {
        if (circleUtils_) {
            delete circleUtils_;
        }
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        auto layoutAlgorithm = MakeRefPtr<TimePickerColumnLayoutAlgorithm>();
        if (algorithmOffset_.size() == 0) {
            ResetAlgorithmOffset();
        }
        layoutAlgorithm->SetCurrentOffset(algorithmOffset_);
        return layoutAlgorithm;
    }

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<LinearLayoutProperty>(isVertical_);
    }

    RefPtr<AccessibilityProperty> CreateAccessibilityProperty() override
    {
        return MakeRefPtr<TimePickerColumnAccessibilityProperty>();
    }

    void FlushCurrentOptions(bool isDown = false, bool isUpateTextContentOnly = false);

    bool NotLoopOptions() const;

    void UpdateColumnChildPosition(double offsetY);

    bool CanMove(bool isDown) const;

    bool InnerHandleScroll(bool isDown, bool isUpatePropertiesOnly = false);

    void ScrollTimeColumn();

    void UpdateCurrentOffset(float offset);

    uint32_t GetCurrentIndex() const
    {
        return currentIndex_;
    }

    void SetCurrentIndex(uint32_t value)
    {
        // minute : [0, 59];
        // AM_PM hour : [0, 11]; 24 hour : [0, 23]
        currentIndex_ = value;
    }

    float GetCurrentOffset() const
    {
        return deltaSize_;
    }

    void SetCurrentOffset(float deltaSize)
    {
        deltaSize_ = deltaSize;
    }

    const std::map<WeakPtr<FrameNode>, uint32_t>& GetOptions() const
    {
        return optionsTotalCount_;
    }

    void SetOptions(const std::map<WeakPtr<FrameNode>, uint32_t>& value)
    {
        optionsTotalCount_ = value;
    }

    uint32_t GetShowCount() const
    {
        return showCount_;
    }

    void SetShowCount(const uint32_t showCount)
    {
        showCount_ = showCount;
        GetHost()->MarkModifyDone();
    }

    void HandleChangeCallback(bool isAdd, bool needNotify)
    {
        if (changeCallback_) {
            changeCallback_(GetHost(), isAdd, GetCurrentIndex(), needNotify);
        }
    }

    const ColumnChangeCallback& GetChangeCallback() const
    {
        return changeCallback_;
    }

    void SetChangeCallback(ColumnChangeCallback&& value)
    {
        changeCallback_ = value;
    }

    void HandleEventCallback(bool refresh)
    {
        if (EventCallback_) {
            EventCallback_(refresh);
        }
    }

    const EventCallback& GetEventCallback() const
    {
        return EventCallback_;
    }

    void SetEventCallback(EventCallback&& value)
    {
        EventCallback_ = value;
    }

    FocusPattern GetFocusPattern() const override
    {
        return { FocusType::NODE, true };
    }

    void SetHour24(bool value)
    {
        hour24_ = value;
    }

    bool GetHour24() const
    {
        return hour24_;
    }

    bool GetWheelModeEnabled() const
    {
        return wheelModeEnabled_;
    }

    void SetWheelModeEnabled(bool value)
    {
        wheelModeEnabled_ = value;
    }

    const RefPtr<TimePickerTossAnimationController>& GetToss() const
    {
        return tossAnimationController_;
    }

    void SetLocalDownDistance(float value)
    {
        localDownDistance_ = value;
    }

    float GetLocalDownDistance() const
    {
        return localDownDistance_;
    }

    void UpdateToss(double offsetY);

    void UpdateFinishToss(double offsetY);

    void TossStoped();

    void UpdateScrollDelta(double delta);

    void SetYLast(double value)
    {
        yLast_ = value;
    }
    double GetOffset()
    {
        return offsetCurSet_;
    }
    void PlayRestAnimation();

    void TossAnimationStoped();

    std::vector<TimePickerOptionProperty> GetMidShiftDistance()
    {
        return optionProperties_;
    }

    void SetMainVelocity(double mainVelocity)
    {
        mainVelocity_ = mainVelocity;
    }

    double GetMainVelocity() const
    {
        return mainVelocity_;
    }

    void SetTossStatus(bool status)
    {
        isTossStatus_ = status;
    }

    bool GetTossStatus()
    {
        return isTossStatus_;
    }

    void SetYOffset(double value)
    {
        yOffset_ = value;
    }

    bool GetTouchBreakStatus()
    {
        return touchBreak_;
    }

    bool GetClickBreakStatus()
    {
        return clickBreak_;
    }

    void SetclickBreak(bool value)
    {
        clickBreak_ = value;
    }

    void InitHapticController(const RefPtr<FrameNode>& host);
    bool IsStartEndTimeDefined();

    void StopHaptic();
    uint32_t GetEnterIndex() const
    {
        return currentEnterIndex_;
    }

    void SetEnterIndex(uint32_t value)
    {
        if (value != currentEnterIndex_) {
            currentEnterIndex_ = value;
        }
    }

    void HandleEnterSelectedAreaEventCallback(bool refresh)
    {
        if (enterSelectedAreaEventCallback_) {
            enterSelectedAreaEventCallback_(refresh);
        }
    }

    const EventCallback& GetEnterSelectedAreaEventCallback() const
    {
        return enterSelectedAreaEventCallback_;
    }

    void SetEnterSelectedAreaEventCallback(EventCallback&& value)
    {
        enterSelectedAreaEventCallback_ = value;
    }

    void SetSelectedMarkListener(const std::function<void(const std::string& selectedColumnId)>& listener);
    void SetSelectedMark(bool focus = true, bool notify = true, bool reRender = true);
    void SetSelectedMarkId(const std::string &strColumnId);
    void UpdateUserSetSelectColor();
#ifdef SUPPORT_DIGITAL_CROWN
    std::string& GetSelectedColumnId();
    bool IsCrownEventEnded();
    int32_t GetDigitalCrownSensitivity();
    void SetDigitalCrownSensitivity(int32_t crownSensitivity);
    bool OnCrownEvent(const CrownEvent& event);
#endif

private:
    void OnModifyDone() override;
    void OnAttachToFrameNode() override;
    void OnDetachFromFrameNode(FrameNode* frameNode) override;
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;
    void SetDividerHeight(uint32_t showOptionCount);
    void ChangeTextStyle(uint32_t index, uint32_t showOptionCount, const RefPtr<TextLayoutProperty>& textLayoutProperty,
        const RefPtr<TimePickerLayoutProperty>& timePickerLayoutProperty);
    void ChangeAmPmTextStyle(uint32_t index, uint32_t showOptionCount,
        const RefPtr<TextLayoutProperty>& textLayoutProperty,
        const RefPtr<TimePickerLayoutProperty>& timePickerLayoutProperty);

    void InitOnKeyEvent(const RefPtr<FocusHub>& focusHub);
    bool OnKeyEvent(const KeyEvent& event);
    bool HandleDirectionKey(KeyCode code);
    void SetSelectedMarkPaint(bool paint);
    void UpdateSelectedTextColor(const RefPtr<PickerTheme>& pickerTheme);
    void GetAnimationColor(uint32_t index, uint32_t showCount, Color& color, bool selectedMark = false);
    void UpdateAnimationColor(const RefPtr<PickerTheme>& pickerTheme);
#ifdef SUPPORT_DIGITAL_CROWN
    void HandleCrownBeginEvent(const CrownEvent& event);
    void HandleCrownMoveEvent(const CrownEvent& event);
    void HandleCrownEndEvent(const CrownEvent& event);
#endif
    RefPtr<TouchEventImpl> CreateItemTouchEventListener();
    void InitPanEvent(const RefPtr<GestureEventHub>& gestureHub);
    void HandleDragStart(const GestureEvent& event);
    void HandleDragMove(const GestureEvent& event);
    void HandleDragEnd();
    void CreateAnimation();
    void CreateAnimation(double from, double to);
    void ScrollOption(double delta, bool isJump = false);

    std::vector<TimePickerOptionProperty> optionProperties_;
    RefPtr<ClickEvent> CreateItemClickEventListener(RefPtr<TimePickerEventParam> param);
    void OnAroundButtonClick(RefPtr<TimePickerEventParam> param);
    std::vector<int32_t> algorithmOffset_;
    void ResetAlgorithmOffset();
    void CalcAlgorithmOffset(TimePickerScrollDirection dir, double distancePercent);
    void SetOptionShiftDistance();
    float GetShiftDistanceForLandscape(uint32_t index, TimePickerScrollDirection dir);
    float GetShiftDistance(uint32_t index, TimePickerScrollDirection dir);
    void ShiftOptionProp(RefPtr<FrameNode> curNode, RefPtr<FrameNode> shiftNode);

    void OnTouchDown();
    void OnTouchUp();
    void ParseTouchListener();
    void ParseMouseEvent();
    void InitMouseAndPressEvent();
    void HandleMouseEvent(bool isHover);
    void SetButtonBackgroundColor(const Color& pressColor);
    void PlayPressAnimation(const Color& pressColor);
    void PlayHoverAnimation(const Color& color);
    void UpdateDisappearTextProperties(const RefPtr<PickerTheme>& pickerTheme,
        const RefPtr<TextLayoutProperty>& textLayoutProperty,
        const RefPtr<TimePickerLayoutProperty>& timePickerLayoutProperty);
    void UpdateCandidateTextProperties(const RefPtr<PickerTheme>& pickerTheme,
        const RefPtr<TextLayoutProperty>& textLayoutProperty,
        const RefPtr<TimePickerLayoutProperty>& timePickerLayoutProperty);
    void UpdateSelectedTextProperties(const RefPtr<PickerTheme>& pickerTheme,
        const RefPtr<TextLayoutProperty>& textLayoutProperty,
        const RefPtr<TimePickerLayoutProperty>& timePickerLayoutProperty);
    void AddAnimationTextProperties(uint32_t currentIndex, const RefPtr<TextLayoutProperty>& textLayoutProperty);
    void UpdateTextPropertiesLinear(bool isDown, double scale);
    void TextPropertiesLinearAnimation(const RefPtr<TextLayoutProperty>& textLayoutProperty, uint32_t index,
        uint32_t showCount, bool isDown, double scale);
    void FlushAnimationTextProperties(bool isDown);
    Dimension LinearFontSize(const Dimension& startFontSize, const Dimension& endFontSize, double percent);
    void SetAccessibilityAction();
    DimensionRect CalculateHotZone(int32_t index, int32_t midSize, float middleChildHeight, float otherChildHeight);
    void AddHotZoneRectToText();
    void InitTextFontFamily();
    void RegisterWindowStateChangedCallback();
    void UnregisterWindowStateChangedCallback(FrameNode* frameNode);
    void OnWindowHide() override;
    void OnWindowShow() override;

    void HandleEnterSelectedArea(double scrollDelta, float shiftDistance, TimePickerScrollDirection dir);

    double mainVelocity_ = 0.0;
    float localDownDistance_ = 0.0f;
    Color pressColor_;
    Color hoverColor_;
    FontWeight SelectedWeight_ = FontWeight::MEDIUM;
    FontWeight DisappearWeight_ = FontWeight::REGULAR;
    RefPtr<TouchEventImpl> touchListener_;
    RefPtr<InputEvent> mouseEvent_;
    bool hour24_ = SystemProperties::Is24HourClock();
    // column options number
    std::map<WeakPtr<FrameNode>, uint32_t> optionsTotalCount_;
    ColumnChangeCallback changeCallback_;
    EventCallback EventCallback_;
    EventCallback enterSelectedAreaEventCallback_;
    uint32_t currentIndex_ = 0;
    uint32_t currentEnterIndex_ = 0;
    double yLast_ = 0.0;
    double yOffset_ = 0.0;
    double jumpInterval_ = 0.0;
    uint32_t showCount_ = 0;
    bool isVertical_ = true;
    float gradientHeight_ = 0.0f;
    float dividerHeight_ = 0.0f;
    float dividerSpacingWidth_ = 0.0f;
    double distancePercent_ = 0.0;
    double offsetCurSet_ = 0.0;
    bool isTossStatus_ = false;
    bool clickBreak_ = false;
    bool touchBreak_ = false;
    bool animationBreak_ = false;
    float deltaSize_ = 0.0f;
    RefPtr<PanEvent> panEvent_;
    bool pressed_ = false;
    bool hoverd_ = false;
    bool wheelModeEnabled_ = true;
    double scrollDelta_ = 0.0;
    double enterDelta_ = 0.0;
    bool animationCreated_ = false;
    OffsetF offset_;
    SizeF size_;
    RefPtr<TimePickerTossAnimationController> tossAnimationController_ =
        AceType::MakeRefPtr<TimePickerTossAnimationController>();
    RefPtr<NodeAnimatablePropertyFloat> scrollProperty_;
    RefPtr<NodeAnimatablePropertyFloat> aroundClickProperty_;
    std::shared_ptr<AnimationUtils::Animation> animation_;
    std::vector<TimeTextProperties> animationProperties_;
    float dividerSpacing_ = 0.0f;

    bool hasAppCustomFont_ = false;
    bool hasUserDefinedDisappearFontFamily_ = false;
    bool hasUserDefinedNormalFontFamily_ = false;
    bool hasUserDefinedSelectedFontFamily_ = false;
    bool isShow_ = true;
    bool isEnableHaptic_ = true;
    bool stopHaptic_ = false;
    bool isTossReadyToStop_ = false;

    std::shared_ptr<IPickerAudioHaptic> hapticController_ = nullptr;
    ACE_DISALLOW_COPY_AND_MOVE(TimePickerColumnPattern);

    friend class PickerColumnPatternCircleUtils<TimePickerColumnPattern>;
    PickerColumnPatternCircleUtils<TimePickerColumnPattern> *circleUtils_ = nullptr;
    std::string selectedColumnId_ = "";
    bool selectedMarkPaint_ = false;
    std::function<void(std::string& selectedColumnId)> focusedListerner_ = nullptr;
    bool isUserSetSelectColor_ = false;
#ifdef SUPPORT_DIGITAL_CROWN
    bool isCrownEventEnded_ = true;
    int32_t crownSensitivity_ = INVALID_CROWNSENSITIVITY;
#endif
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TIME_PICKER_TIME_PICKER_COLUMN_PATTERN_H
