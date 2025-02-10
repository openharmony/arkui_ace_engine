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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DATE_PICKER_DATE_PICKER_COLUMN_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DATE_PICKER_DATE_PICKER_COLUMN_PATTERN_H

#include <utility>

#include "adapter/ohos/entrance/picker/picker_haptic_factory.h"
#include "base/i18n/localization.h"
#include "core/components/picker/picker_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/picker/datepicker_column_accessibility_property.h"
#include "core/components_ng/pattern/picker/datepicker_column_layout_algorithm.h"
#include "core/components_ng/pattern/picker/datepicker_event_hub.h"
#include "core/components_ng/pattern/picker/datepicker_layout_property.h"
#include "core/components_ng/pattern/picker/datepicker_paint_method.h"
#include "core/components_ng/pattern/picker/datepicker_row_layout_property.h"
#include "core/components_ng/pattern/picker/toss_animation_controller.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/pipeline_ng/ui_task_scheduler.h"
#ifdef SUPPORT_DIGITAL_CROWN
#include "core/event/crown_event.h"
#endif
#include "core/components_ng/pattern/picker_utils/picker_column_pattern_utils.h"

namespace OHOS::Ace::NG {

using ColumnChangeCallback = std::function<void(const RefPtr<FrameNode>&, bool, uint32_t, bool)>;
using ColumnFinishCallback = std::function<void(bool)>;
using EventCallback = std::function<void(bool)>;

struct DateTextProperties {
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

struct DatePickerOptionProperty {
    float height = 0.0f;
    float fontheight = 0.0f;
    float prevDistance = 0.0f; // between the prev item and itself when scroll up
    float nextDistance = 0.0f; // between the next item and itself when scroll down
};

class DatePickerEventParam : public virtual AceType {
    DECLARE_ACE_TYPE(DatePickerEventParam, AceType)

public:
    WeakPtr<FrameNode> instance_;
    int32_t itemIndex_ = 0;
    int32_t itemTotalCounts_ = 0;
};

enum class DatePickerScrollDirection {
    UP = 0,
    DOWN,
};
enum class DatePickerOptionIndex {
    COLUMN_INDEX_0 = 0,
    COLUMN_INDEX_1,
    COLUMN_INDEX_2,
    COLUMN_INDEX_3,
    COLUMN_INDEX_4,
    COLUMN_INDEX_5,
    COLUMN_INDEX_6,
};

class DatePickerColumnPattern : public LinearLayoutPattern {
    DECLARE_ACE_TYPE(DatePickerColumnPattern, LinearLayoutPattern);

public:
    DatePickerColumnPattern() : LinearLayoutPattern(true) {};
    ~DatePickerColumnPattern() override
    {
        if (circleUtils_) {
            delete circleUtils_;
        }
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        auto layoutAlgorithm = MakeRefPtr<DatePickerColumnLayoutAlgorithm>();
        if (algorithmOffset_.size() == 0) {
            ResetAlgorithmOffset();
        }
        layoutAlgorithm->SetCurrentOffset(algorithmOffset_);
        return layoutAlgorithm;
    }

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<DataPickerLayoutProperty>();
    }

    RefPtr<AccessibilityProperty> CreateAccessibilityProperty() override
    {
        return MakeRefPtr<DatePickerColumnAccessibilityProperty>();
    }

    void FlushCurrentOptions(
        bool isDown = false, bool isUpateTextContentOnly = false, bool isUpdateAnimationProperties = false);

    bool NotLoopOptions() const;

    void UpdateColumnChildPosition(double offsetY);

    bool CanMove(bool isDown) const;

    bool InnerHandleScroll(bool isDown, bool isUpatePropertiesOnly = false, bool isUpdateAnimationProperties = false);

    uint32_t GetCurrentIndex() const
    {
        // currentIndex_ is year/month/day information, for example month [0, 11] is Equivalent to [1, 12]
        return currentIndex_;
    }

    void SetCurrentIndex(uint32_t value)
    {
        currentIndex_ = value;
    }

    double GetCurrentOffset() const
    {
        return deltaSize_;
    }

    void SetCurrentOffset(double deltaSize)
    {
        deltaSize_ = deltaSize;
    }

    const std::map<WeakPtr<FrameNode>, std::vector<PickerDateF>>& GetOptions() const
    {
        return options_;
    }

    void SetOptions(const std::map<WeakPtr<FrameNode>, std::vector<PickerDateF>>& value)
    {
        options_ = value;
    }

    uint32_t GetShowCount() const
    {
        return showCount_;
    }

    void SetShowCount(const uint32_t showCount)
    {
        showCount_ = showCount;
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

    const RefPtr<TossAnimationController>& GetToss() const
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

    std::vector<DatePickerOptionProperty> GetMidShiftDistance()
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

    void UpdateColumnButtonFocusState(bool haveFocus, bool needMarkDirty);
    void InitHapticController();
    void StopHaptic();
    void SetSelectedMarkListener(std::function<void(std::string& selectedColumnId)>& listener);
    void SetSelectedMark(bool focus = true, bool notify = true, bool reRender = true);
    void SetSelectedMarkId(const std::string &strColumnId);
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
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;
    void SetDividerHeight(uint32_t showOptionCount);
    void OnTouchDown();
    void OnTouchUp();
    void ParseTouchListener();
    void ParseMouseEvent();
    void InitMouseAndPressEvent();
    void HandleMouseEvent(bool isHover);
    void SetButtonBackgroundColor(const Color& pressColor);
    void PlayPressAnimation(const Color& pressColor);
    void PlayHoverAnimation(const Color& color);
    void InitSelectorButtonProperties(const RefPtr<PickerTheme>& pickerTheme);
    void UpdateSelectorButtonProps(bool haveFocus, bool needMarkDirty);
    const Color& GetButtonHoverColor() const;
    void UpdateTextAreaPadding(const RefPtr<PickerTheme>& pickerTheme,
        const RefPtr<TextLayoutProperty>& textLayoutProperty);

    std::vector<DatePickerOptionProperty> optionProperties_;
    RefPtr<ClickEvent> CreateItemClickEventListener(RefPtr<DatePickerEventParam> param);
    RefPtr<TouchEventImpl> CreateItemTouchEventListener();
    void OnAroundButtonClick(RefPtr<DatePickerEventParam> param);
    std::vector<int32_t> algorithmOffset_;
    void ResetAlgorithmOffset();
    void CalcAlgorithmOffset(DatePickerScrollDirection dir, double distancePercent);
    void SetOptionShiftDistance();
    float GetShiftDistanceForLandscape(uint32_t index, DatePickerScrollDirection dir);
    float GetShiftDistance(uint32_t index, DatePickerScrollDirection dir);
    int32_t CalcScrollIndex(int32_t totalOptionCount, int32_t currentIndex, bool canLoop, int32_t step);
    void ShiftOptionProp(RefPtr<FrameNode> curNode, RefPtr<FrameNode> shiftNode);

    void InitPanEvent(const RefPtr<GestureEventHub>& gestureHub);
    void HandleDragStart(const GestureEvent& event);
    void HandleDragMove(const GestureEvent& event);
    void HandleDragEnd();
    void SetSelectedMarkPaint(bool paint);
    void UpdateSelectedTextColor(const RefPtr<PickerTheme>& pickerTheme);
#ifdef SUPPORT_DIGITAL_CROWN
    void HandleCrownBeginEvent(const CrownEvent& event);
    void HandleCrownMoveEvent(const CrownEvent& event);
    void HandleCrownEndEvent(const CrownEvent& event);
#endif
    void CreateAnimation();
    void CreateAnimation(double from, double to);
    void ScrollOption(double delta, bool isJump = false);
    void UpdatePickerTextProperties(uint32_t index, uint32_t showOptionCount,
        const RefPtr<TextLayoutProperty>& textLayoutProperty,
        const RefPtr<DataPickerRowLayoutProperty>& dataPickerRowLayoutProperty);
    void UpdateDisappearTextProperties(const RefPtr<PickerTheme>& pickerTheme,
        const RefPtr<TextLayoutProperty>& textLayoutProperty,
        const RefPtr<DataPickerRowLayoutProperty>& timePickerLayoutProperty);
    void UpdateCandidateTextProperties(const RefPtr<PickerTheme>& pickerTheme,
        const RefPtr<TextLayoutProperty>& textLayoutProperty,
        const RefPtr<DataPickerRowLayoutProperty>& timePickerLayoutProperty);
    void UpdateSelectedTextProperties(const RefPtr<PickerTheme>& pickerTheme,
        const RefPtr<TextLayoutProperty>& textLayoutProperty,
        const RefPtr<DataPickerRowLayoutProperty>& timePickerLayoutProperty);
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
    void OnDetachFromFrameNode(FrameNode* frameNode) override;
    void RegisterWindowStateChangedCallback();
    void UnregisterWindowStateChangedCallback();
    void OnWindowHide() override;
    void OnWindowShow() override;

    float localDownDistance_ = 0.0f;
    RefPtr<TouchEventImpl> touchListener_;
    RefPtr<InputEvent> mouseEvent_;
    std::map<WeakPtr<FrameNode>, std::vector<PickerDateF>> options_;
    ColumnChangeCallback changeCallback_;
    EventCallback EventCallback_;
    uint32_t currentIndex_ = 0;
    int32_t currentChildIndex_ = 0;
    double yLast_ = 0.0;
    double yOffset_ = 0.0;
    double jumpInterval_ = 0.0;
    uint32_t showCount_ = 0;
    float gradientHeight_ = 0.0f;
    float dividerHeight_ = 0.0f;
    float dividerSpacingWidth_ = 0.0f;
    double mainVelocity_ = 0.0;
    float dividerSpacing_ = 0.0f;
    FontWeight SelectedWeight_ = FontWeight::MEDIUM;
    FontWeight CandidateWeight_ = FontWeight::REGULAR;
    double offsetCurSet_ = 0.0;
    double distancePercent_ = 0.0;
    Color pressColor_;
    Color hoverColor_;
    Color buttonBgColor_ = Color::TRANSPARENT;
    Color buttonDefaultBgColor_ = Color::TRANSPARENT;
    Color buttonFocusBgColor_ = Color::TRANSPARENT;
    Color buttonDefaultBorderColor_ = Color::TRANSPARENT;
    Color buttonFocusBorderColor_ = Color::TRANSPARENT;
    Color selectorTextFocusColor_ = Color::WHITE;
    Dimension buttonDefaultBorderWidth_ = 0.0_vp;
    Dimension buttonFocusBorderWidth_ = 0.0_vp;
    bool isFirstTimeUpdateButtonProps_ = true;
    bool useButtonFocusArea_ = false;
    bool isFocusColumn_ = false;
    bool isTossStatus_ = false;
    bool clickBreak_ = false;
    bool touchBreak_ = false;
    bool animationBreak_ = false;
    double deltaSize_ = 0.0;
    RefPtr<PanEvent> panEvent_;
    bool pressed_ = false;
    bool hoverd_ = false;
    double scrollDelta_ = 0.0;
    bool animationCreated_ = false;
    OffsetF offset_;
    SizeF size_;
    RefPtr<TossAnimationController> tossAnimationController_ = AceType::MakeRefPtr<TossAnimationController>();
    std::vector<DateTextProperties> animationProperties_;

    RefPtr<NodeAnimatablePropertyFloat> scrollProperty_;
    RefPtr<NodeAnimatablePropertyFloat> aroundClickProperty_;
    std::shared_ptr<AnimationUtils::Animation> animation_;

    bool hasAppCustomFont_ = false;
    bool hasUserDefinedDisappearFontFamily_ = false;
    bool hasUserDefinedNormalFontFamily_ = false;
    bool hasUserDefinedSelectedFontFamily_ = false;
    bool isShow_ = true;
    bool isEnableHaptic_ = true;
    bool stopHaptic_ = false;
    bool selectedMarkPaint_ = false;
    std::shared_ptr<IPickerAudioHaptic> hapticController_ = nullptr;

    ACE_DISALLOW_COPY_AND_MOVE(DatePickerColumnPattern);

    friend class PickerColumnPatternCircleUtils<DatePickerColumnPattern>;
    PickerColumnPatternCircleUtils<DatePickerColumnPattern> *circleUtils_ = nullptr;
    std::string selectedColumnId_ = "";
    std::function<void(std::string& selectedColumnId)> focusedListerner_ = nullptr;
#ifdef SUPPORT_DIGITAL_CROWN
    bool isCrownEventEnded_ = true;
    int32_t crownSensitivity_ = INVALID_CROWNSENSITIVITY;
#endif
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DATE_PICKER_DATE_PICKER_COLUMN_PATTERN_H
