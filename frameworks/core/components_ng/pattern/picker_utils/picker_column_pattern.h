/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_PICKER_UTILS_PICKER_COLUMN_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_PICKER_UTILS_PICKER_COLUMN_PATTERN_H
#include <cstdint>

#include "adapter/ohos/entrance/picker/picker_haptic_factory.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/picker/datepicker_layout_property.h"
#include "core/components_ng/pattern/picker_utils/picker_column_pattern_utils.h"
#include "core/components_ng/pattern/picker_utils/picker_layout_property.h"
#include "core/components_ng/pattern/picker_utils/toss_animation_controller.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#ifdef SUPPORT_DIGITAL_CROWN
#include "core/event/crown_event.h"
#endif
namespace OHOS::Ace::NG {

using ColumnChangeCallback = std::function<void(const RefPtr<FrameNode>&, bool, uint32_t, bool)>;
using ColumnFinishCallback = std::function<void(bool)>;
using EventCallback = std::function<void(bool)>;

struct TextProperties {
    Dimension upFontSize;
    Dimension fontSize;
    Dimension downFontSize;
    FontWeight upFontWeight = FontWeight::W100;
    FontWeight fontWeight = FontWeight::W100;
    FontWeight downFontWeight = FontWeight::W100;
    Color upColor;
    Color currentColor;
    Color downColor;
};

struct PickerOptionProperty {
    float height = 0.0f;
    float fontheight = 0.0f;
    float prevDistance = 0.0f; // between the prev item and itself when scroll up
    float nextDistance = 0.0f; // between the next item and itself when scroll down
};

class PickerEventParam : public virtual AceType {
    DECLARE_ACE_TYPE(PickerEventParam, AceType)

public:
    WeakPtr<FrameNode> instance_;
    int32_t itemIndex_ = 0;
    int32_t itemTotalCounts_ = 0;
};

enum class PickerScrollDirection {
    UP = 0,
    DOWN,
};

enum class PickerOptionIndex {
    COLUMN_INDEX_0 = 0,
    COLUMN_INDEX_1,
    COLUMN_INDEX_2,
    COLUMN_INDEX_3,
    COLUMN_INDEX_4,
    COLUMN_INDEX_5,
    COLUMN_INDEX_6,
};

class PickerColumnPattern : public LinearLayoutPattern {
    DECLARE_ACE_TYPE(PickerColumnPattern, LinearLayoutPattern);

public:
    PickerColumnPattern(bool isVertical = false) : LinearLayoutPattern(isVertical) {};
    virtual ~PickerColumnPattern()
    {
        if (circleUtils_) {
            delete circleUtils_;
        }
    }

    virtual void FlushCurrentOptions(bool isDown = false, bool isUpateTextContentOnly = false,
        bool isUpdateAnimationProperties = false, bool isTossPlaying = false) = 0;
    virtual void InitHapticController(const RefPtr<FrameNode>& host) = 0;
    virtual void UpdateColumnChildPosition(double offsetY) = 0;
    virtual void UpdateSelectedTextColor(const RefPtr<PickerTheme>& pickerTheme) = 0;
    virtual void TextPropertiesLinearAnimation(const RefPtr<TextLayoutProperty>& textLayoutProperty, uint32_t index,
        uint32_t showCount, bool isDown, double scale) = 0;
    virtual void InitTextFontFamily() = 0;
    virtual uint32_t GetOptionCount() const = 0;
    virtual const Color& GetButtonHoverColor() const = 0;
    virtual const Color& GetButtonBgColor() const = 0;
    virtual const Color& GetButtonPressColor() const = 0;
    virtual bool CanMove(bool isDown) const = 0;
    virtual std::string GetCurrentOption() const = 0;

    virtual uint32_t GetShowCount() const
    {
        return showCount_;
    }

    virtual void SetTossStatus(bool status)
    {
        isTossStatus_ = status;
    }

    virtual bool GetTossStatus() const
    {
        return isTossStatus_;
    }

    virtual const RefPtr<TossAnimationController>& GetToss() const
    {
        return tossAnimationController_;
    }

    virtual void SetYLast(double value)
    {
        yLast_ = value;
    }

    virtual void SetLocalDownDistance(float value)
    {
        localDownDistance_ = value;
    }

    virtual float GetLocalDownDistance() const
    {
        return localDownDistance_;
    }
    virtual void SetMainVelocity(double mainVelocity)
    {
        mainVelocity_ = mainVelocity;
    }

    virtual double GetMainVelocity() const
    {
        return mainVelocity_;
    }

    virtual std::vector<PickerOptionProperty> GetMidShiftDistance()
    {
        return optionProperties_;
    }

    virtual void SetCurrentIndex(uint32_t value)
    {
        // minute : [0, 59];
        // AM_PM hour : [0, 11]; 24 hour : [0, 23]
        currentIndex_ = value;
    }

    virtual uint32_t GetCurrentIndex() const
    {
        // currentIndex_ is year/month/day information, for example month [0, 11] is Equivalent to [1, 12]
        return currentIndex_;
    }

    virtual void HandleChangeCallback(bool isAdd, bool needNotify)
    {
        if (changeCallback_) {
            changeCallback_(GetHost(), isAdd, GetCurrentIndex(), needNotify);
        }
    }

    virtual const ColumnChangeCallback& GetChangeCallback() const
    {
        return changeCallback_;
    }

    virtual void SetChangeCallback(ColumnChangeCallback&& value)
    {
        changeCallback_ = value;
    }

    virtual void HandleEventCallback(bool refresh)
    {
        if (EventCallback_) {
            EventCallback_(refresh);
        }
    }

    virtual const EventCallback& GetEventCallback() const
    {
        return EventCallback_;
    }

    virtual void SetEventCallback(EventCallback&& value)
    {
        EventCallback_ = value;
    }

    virtual bool GetWheelModeEnabled() const
    {
        return wheelModeEnabled_;
    }

    virtual void SetWheelModeEnabled(bool value)
    {
        wheelModeEnabled_ = value;
    }

    virtual bool GetTouchBreakStatus() const
    {
        return touchBreak_;
    }

    virtual void SetYOffset(double value)
    {
        yOffset_ = value;
    }

    virtual double GetOffset() const
    {
        return offsetCurSet_;
    }

    virtual float GetCurrentOffset() const
    {
        return deltaSize_;
    }

    virtual void SetCurrentOffset(float deltaSize)
    {
        deltaSize_ = deltaSize;
    }

    virtual bool GetClickBreakStatus() const
    {
        return clickBreak_;
    }

    virtual void SetclickBreak(bool value)
    {
        clickBreak_ = value;
    }

    virtual bool IsTossNeedToStop()
    {
        return false;
    }

public:
    virtual void OnAttachToFrameNode() override;
    virtual void OnDetachFromFrameNode(FrameNode* frameNode) override;
    virtual bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;
    virtual void CreateAnimation(double from, double to);
    virtual void CreateAnimation();
    virtual void TossAnimationStoped();
    virtual void StopHaptic();
    virtual void SetSelectedMark(bool focus = true, bool notify = true, bool reRender = true);
    virtual void SetSelectedMarkId(const std::string& strColumnId);
    virtual void UpdateUserSetSelectColor();
    virtual Dimension LinearFontSize(const Dimension& startFontSize, const Dimension& endFontSize, double percent);
    virtual void CalcAlgorithmOffset(PickerScrollDirection dir, double distancePercent);
    virtual void SetSelectedMarkListener(const std::function<void(std::string& selectedColumnId)>& listener);
    virtual RefPtr<TouchEventImpl> CreateItemTouchEventListener();
    virtual void OnAroundButtonClick(RefPtr<PickerEventParam> param);
    virtual void OnTouchDown();
    virtual void OnTouchUp();
    virtual void ParseTouchListener();
    virtual void ParseMouseEvent();
    virtual void InitMouseAndPressEvent();
    virtual void HandleMouseEvent(bool isHover);
    virtual void SetButtonBackgroundColor(const Color& pressColor);
    virtual void PlayHoverAnimation(const Color& color);
    virtual void PlayPressAnimation(const Color& pressColor);
    virtual void RegisterWindowStateChangedCallback();
    virtual void UnregisterWindowStateChangedCallback(FrameNode* frameNode);
    virtual void AddHotZoneRectToText();
    virtual DimensionRect CalculateHotZone(
        int32_t index, int32_t midSize, float middleChildHeight, float otherChildHeight);
    virtual void SetSelectedMarkPaint(bool paint);
    virtual void InitPanEvent(const RefPtr<GestureEventHub>& gestureHub);
    virtual void HandleDragStart(const GestureEvent& event);
    virtual void HandleDragEnd();
    virtual void ResetAlgorithmOffset();
    virtual void ShiftOptionProp(RefPtr<FrameNode> curNode, RefPtr<FrameNode> shiftNode);
    virtual void AddAnimationTextProperties(
        uint32_t currentIndex, const RefPtr<TextLayoutProperty>& textLayoutProperty);
    virtual void UpdateFinishToss(double offsetY);
    virtual void FlushAnimationTextProperties(bool isDown);
    virtual void SetAccessibilityAction();
    virtual void OnWindowHide() override;
    virtual void OnWindowShow() override;
    virtual RefPtr<ClickEvent> CreateItemClickEventListener(RefPtr<PickerEventParam> param);
    virtual bool InnerHandleScroll(
        bool isDown, bool isUpatePropertiesOnly = false, bool isUpdateAnimationProperties = false);
    virtual bool NotLoopOptions() const;
    virtual void TossStoped();
    virtual void ScrollOption(double delta, bool isJump = false);
    virtual void UpdateDisappearTextProperties(const RefPtr<PickerTheme>& pickerTheme,
        const RefPtr<TextLayoutProperty>& textLayoutProperty, const RefPtr<PickerLayoutProperty>& pickerLayoutProperty);
    virtual void UpdateCandidateTextProperties(const RefPtr<PickerTheme>& pickerTheme,
        const RefPtr<TextLayoutProperty>& textLayoutProperty, const RefPtr<PickerLayoutProperty>& pickerLayoutProperty);
    virtual void UpdateSelectedTextProperties(const RefPtr<PickerTheme>& pickerTheme,
        const RefPtr<TextLayoutProperty>& textLayoutProperty, const RefPtr<PickerLayoutProperty>& pickerLayoutProperty);
    virtual void HandleEnterSelectedArea(double scrollDelta, float shiftDistance, PickerScrollDirection dir) {}
    virtual void HandleDragMove(const GestureEvent& event);
    virtual void PlayRestAnimation();
    virtual void SetOptionShiftDistance();
    virtual bool GetOptionItemCount(uint32_t& itemCounts);
    virtual bool IsLanscape(uint32_t itemCount);
    virtual float GetShiftDistanceForLandscape(uint32_t index, PickerScrollDirection dir);
    virtual float GetShiftDistance(uint32_t index, PickerScrollDirection dir);
    virtual void UpdateTextPropertiesLinear(bool isDown, double scale);
    virtual void UpdateToss(double offsetY);
    virtual void HandleAccessibilityTextChange();
#ifdef SUPPORT_DIGITAL_CROWN
    virtual void HandleCrownBeginEvent(const CrownEvent& event);
    virtual void HandleCrownMoveEvent(const CrownEvent& event);
    virtual void HandleCrownEndEvent(const CrownEvent& event);
#endif

#ifdef SUPPORT_DIGITAL_CROWN
    std::string& GetSelectedColumnId();
    bool IsCrownEventEnded();
    int32_t GetDigitalCrownSensitivity();
    void SetDigitalCrownSensitivity(int32_t crownSensitivity);
    bool OnCrownEvent(const CrownEvent& event);
#endif
protected:
    uint32_t showCount_ = 0;
    float localDownDistance_ = 0.0f;
    OffsetF offset_;
    SizeF size_;
    double scrollDelta_ = 0.0;
    double yLast_ = 0.0;
    double yOffset_ = 0.0;
    double offsetCurSet_ = 0.0;
    double distancePercent_ = 0.0;
    double mainVelocity_ = 0.0;
    double jumpInterval_ = 0.0;
    double deltaSize_ = 0.0;
    bool stopHaptic_ = false;
    bool hoverd_ = false;
    bool useButtonFocusArea_ = false;
    bool isFocusColumn_ = false;
    bool isTossStatus_ = false;
    bool clickBreak_ = false;
    bool touchBreak_ = false;
    bool animationBreak_ = false;
    bool selectedMarkPaint_ = false;
    bool pressed_ = false;
    bool animationCreated_ = false;
    bool isShow_ = true;
    bool isEnableHaptic_ = true;
    bool isHapticPlayOnce_ = true;
    bool wheelModeEnabled_ = true;
    bool isTossPlaying_ = false;
    std::shared_ptr<IPickerAudioHaptic> hapticController_ = nullptr;
    RefPtr<NodeAnimatablePropertyFloat> scrollProperty_;
    RefPtr<TossAnimationController> tossAnimationController_ = AceType::MakeRefPtr<TossAnimationController>();
    std::vector<TextProperties> animationProperties_;
    RefPtr<NodeAnimatablePropertyFloat> aroundClickProperty_;
    std::shared_ptr<AnimationUtils::Animation> animation_;
    RefPtr<TouchEventImpl> touchListener_;
    RefPtr<InputEvent> mouseEvent_;
    RefPtr<PanEvent> panEvent_;
    std::vector<int32_t> algorithmOffset_;
    std::vector<PickerOptionProperty> optionProperties_;
    uint32_t currentIndex_ = 0;
    ColumnChangeCallback changeCallback_;
    EventCallback EventCallback_;
    FontWeight SelectedWeight_ = FontWeight::MEDIUM;

public:
    PickerColumnPatternCircleUtils<PickerColumnPattern>* circleUtils_ = nullptr;
    std::function<void(std::string& selectedColumnId)> focusedListerner_ = nullptr;
    std::string selectedColumnId_ = "";
    bool isUserSetSelectColor_ = false;
#ifdef SUPPORT_DIGITAL_CROWN
    bool isCrownEventEnded_ = true;
    int32_t crownSensitivity_ = INVALID_CROWNSENSITIVITY;
#endif
    ACE_DISALLOW_COPY_AND_MOVE(PickerColumnPattern);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_PICKER_UTILS_PICKER_COLUMN_PATTERN_H
