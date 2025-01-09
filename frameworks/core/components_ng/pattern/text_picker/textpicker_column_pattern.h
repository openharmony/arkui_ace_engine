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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_PICKER_TEXT_PICKER_COLUMN_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_PICKER_TEXT_PICKER_COLUMN_PATTERN_H

#include <optional>

#include "adapter/ohos/entrance/picker/picker_haptic_interface.h"
#include "core/components/common/properties/color.h"
#include "core/components/picker/picker_theme.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/picker/picker_type_define.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text_picker/textpicker_accessibility_property.h"
#include "core/components_ng/pattern/text_picker/textpicker_event_hub.h"
#include "core/components_ng/pattern/text_picker/textpicker_layout_algorithm.h"
#include "core/components_ng/pattern/text_picker/textpicker_layout_property.h"
#include "core/components_ng/pattern/text_picker/textpicker_overscroll.h"
#include "core/components_ng/pattern/text_picker/textpicker_paint_method.h"
#include "core/components_ng/pattern/text_picker/toss_animation_controller.h"

namespace OHOS::Ace::NG {
using EventCallback = std::function<void(bool)>;
using ColumnChangeCallback = std::function<void(const RefPtr<FrameNode>&, bool, uint32_t, bool)>;

struct TextProperties {
    Dimension upFontSize;
    Dimension fontSize;
    Dimension downFontSize;
    Color upColor;
    Color currentColor;
    Color downColor;
    FontWeight upFontWeight;
    FontWeight fontWeight;
    FontWeight downFontWeight;
};

struct TextPickerOptionProperty {
    float height = 0.0f;
    float fontheight = 0.0f;
    float prevDistance = 0.0f; // between the prev item and itself when scroll up
    float nextDistance = 0.0f; // between the next item and itself when scroll down
};

class EventParam : public virtual AceType {
    DECLARE_ACE_TYPE(EventParam, AceType)

public:
    WeakPtr<FrameNode> instance;
    int32_t itemIndex = 0;
    int32_t itemTotalCounts = 0;
};

enum class ScrollDirection {
    UP = 0,
    DOWN,
};

enum class OptionIndex {
    COLUMN_INDEX_0 = 0,
    COLUMN_INDEX_1,
    COLUMN_INDEX_2,
    COLUMN_INDEX_3,
    COLUMN_INDEX_4,
    COLUMN_INDEX_5,
    COLUMN_INDEX_6
};

class TextPickerColumnPattern : public LinearLayoutPattern {
    DECLARE_ACE_TYPE(TextPickerColumnPattern, LinearLayoutPattern);

public:
    TextPickerColumnPattern() : LinearLayoutPattern(true) {};

    ~TextPickerColumnPattern() override = default;

    bool IsAtomicNode() const override
    {
        return true;
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        auto layoutAlgorithm = MakeRefPtr<TextPickerLayoutAlgorithm>();
        if (algorithmOffset_.size() == 0) {
            ResetAlgorithmOffset();
        }
        layoutAlgorithm->SetCurrentOffset(algorithmOffset_);
        layoutAlgorithm->SetDefaultPickerItemHeight(defaultPickerItemHeight_);
        return layoutAlgorithm;
    }

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<LinearLayoutProperty>(true);
    }

    void FlushCurrentOptions(bool isDown = false, bool isUpateTextContentOnly = false, bool isDirectlyClear = false,
        bool isUpdateAnimationProperties = false);

    void InitilaScorllEvent();

    void UpdateCurrentOffset(float offset);

    void UpdateColumnChildPosition(double offsetY);

    TextPickerOverscroller& GetOverscroller()
    {
        return overscroller_;
    }

    bool CanMove(bool isDown) const;

    bool NotLoopOptions() const;

    bool InnerHandleScroll(bool isDown, bool isUpatePropertiesOnly = false, bool isUpdateAnimationProperties = false);

    void SetDefaultPickerItemHeight(double defaultPickerItemHeight)
    {
        defaultPickerItemHeight_ = defaultPickerItemHeight;
    }

    uint32_t GetShowOptionCount() const;

    std::string GetSelectedObject(bool isColumnChange, int32_t status = 0) const;

    void SetSelected(uint32_t value)
    {
        selectedIndex_ = value;
    }
    uint32_t GetSelected() const
    {
        return selectedIndex_;
    }

    void SetRange(const std::vector<std::string>& value)
    {
        if (value.empty()) {
            return;
        }
        range_ = value;
    }

    const std::vector<std::string>& GetRange() const
    {
        return range_;
    }

    std::string GetCurrentText() const
    {
        return GetOption(GetCurrentIndex());
    }

    uint32_t GetCurrentIndex() const
    {
        return currentIndex_;
    }
    void SetCurrentIndex(uint32_t value)
    {
        if (value != currentIndex_) {
            isIndexChanged_ = true;
            currentIndex_ = value;
        }
    }

    uint32_t GetOptionCount() const
    {
        return options_.size();
    }

    std::string GetOption(uint32_t index) const
    {
        if (index >= GetOptionCount()) {
            return "";
        }
        return options_[index].text_;
    }

    void SetOptions(std::vector<NG::RangeContent>& value)
    {
        options_.clear();
        for (auto& content : value) {
            options_.emplace_back(content);
        }
    }

    void ClearOptions()
    {
        options_.clear();
    }

    void SetColumnKind(int32_t kind)
    {
        columnkind_ = kind;
    }

    float GetCurrentOffset() const
    {
        return deltaSize_;
    }

    void SetCurrentOffset(float deltaSize)
    {
        deltaSize_ = deltaSize;
    }

    const RefPtr<TextPickerTossAnimationController>& GetToss() const
    {
        return tossAnimationController_;
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

    void HandleScrollStopEventCallback(bool refresh)
    {
        if (scrollStopEventCallback_) {
            scrollStopEventCallback_(refresh);
        }
    }

    const EventCallback& GetScrollStopEventCallback() const
    {
        return scrollStopEventCallback_;
    }

    void SetScrollStopEventCallback(EventCallback&& value)
    {
        scrollStopEventCallback_ = value;
    }

    std::string GetEnterText() const
    {
        return GetOption(GetEnterIndex());
    }

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

    void SetLocalDownDistance(float value)
    {
        localDownDistance_ = value;
    }

    float GetLocalDownDistance() const
    {
        return localDownDistance_;
    }

    void UpdateToss(double offsetY);

    void TossStoped();

    void UpdateScrollDelta(double delta);

    RefPtr<AccessibilityProperty> CreateAccessibilityProperty() override
    {
        return MakeRefPtr<TextPickerAccessibilityProperty>();
    }

    void SetChangeCallback(ColumnChangeCallback&& value)
    {
        changeCallback_ = value;
    }

    void HandleChangeCallback(bool isAdd, bool needNotify)
    {
        if (changeCallback_) {
            changeCallback_(GetHost(), isAdd, GetCurrentIndex(), needNotify);
        }
    }

    int32_t GetHalfDisplayCounts() const
    {
        return halfDisplayCounts_;
    }

    double GetOffset() const
    {
        return offsetCurSet_;
    }

    void SetYLast(double value)
    {
        yLast_ = value;
    }

    void TossAnimationStoped();

    void PlayResetAnimation();

    std::vector<TextPickerOptionProperty> GetMidShiftDistance() const
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
        if (!status && NotLoopOptions() && !pressed_ && !isReboundInProgress_ && overscroller_.IsOverScroll()) {
            // Start rebound animation when toss stoped
            CreateReboundAnimation(overscroller_.GetOverScroll(), 0.0);
            HandleScrollStopEventCallback(true);
        }
    }

    bool GetTossStatus() const
    {
        return isTossStatus_;
    }

    void SetYOffset(double value)
    {
        yOffset_ = value;
    }

    bool GetTouchBreakStatus() const
    {
        return touchBreak_;
    }

    void NeedResetOptionPropertyHeight(bool needOptionPropertyHeightReset)
    {
        needOptionPropertyHeightReset_ = needOptionPropertyHeightReset;
    }

    bool isHover() const
    {
        return isHover_;
    }

    int32_t GetOverScrollDeltaIndex() const;
    void SetCanLoop(bool isLoop);

    void SetScrollDirection(bool isDown)
    {
        isDownScroll_ = isDown;
    }

    bool IsDownScroll()
    {
        return isDownScroll_;
    }
    void ResetOptionPropertyHeight();
    void ResetTotalDelta();
    void InitHapticController(const RefPtr<FrameNode>& host);

    void SetDisableTextStyleAnimation(bool value)
    {
        isDisableTextStyleAnimation_ = value;
    }
    void UpdateColumnButtonFocusState(bool haveFocus, bool needMarkDirty);

private:
    void OnModifyDone() override;
    void OnAttachToFrameNode() override;
    void OnDetachFromFrameNode(FrameNode* frameNode) override;
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;
    void InitSelectorButtonProperties(const RefPtr<PickerTheme>& pickerTheme);
    void UpdateSelectorButtonProps(bool haveFocus, bool needMarkDirty);
    const Color& GetButtonHoverColor() const;
    void UpdateTextAreaPadding(const RefPtr<PickerTheme>& pickerTheme,
        const RefPtr<TextLayoutProperty>& textLayoutProperty);

    bool OnKeyEvent(const KeyEvent& event);
    bool HandleDirectionKey(KeyCode code);

    void InitPanEvent(const RefPtr<GestureEventHub>& gestureHub);
    void HandleDragStart(const GestureEvent& event);
    void HandleDragMove(const GestureEvent& event);
    void HandleDragEnd();
    void CreateAnimation();
    void CreateAnimation(double from, double to);
    void CreateReboundAnimation(double from, double to);
    void ScrollOption(double delta);
    std::vector<TextPickerOptionProperty> optionProperties_;
    std::vector<int32_t> algorithmOffset_;
    void ResetAlgorithmOffset();
    void CalcAlgorithmOffset(double distancePercent);
    void SetOptionShiftDistance();
    double GetShiftDistanceForLandscape(int32_t index, ScrollDirection dir);
    double GetShiftDistance(int32_t index, ScrollDirection dir);
    double GetSelectedDistance(int32_t index, int32_t nextIndex, ScrollDirection dir);
    double GetUpCandidateDistance(int32_t index, int32_t nextIndex, ScrollDirection dir);
    double GetDownCandidateDistance(int32_t index, int32_t nextIndex, ScrollDirection dir);
    void OnTouchDown();
    void OnTouchUp();
    void ParseTouchListener();
    void ParseMouseEvent();
    void InitMouseAndPressEvent();
    void HandleMouseEvent(bool isHover);
    void SetButtonBackgroundColor(const Color& pressColor);
    void PlayPressAnimation(const Color& pressColor);
    void FlushCurrentTextOptions(const RefPtr<TextPickerLayoutProperty>& textPickerLayoutProperty,
        bool isUpateTextContentOnly, bool isDirectlyClear);
    void FlushCurrentImageOptions();
    void FlushCurrentMixtureOptions(
        const RefPtr<TextPickerLayoutProperty>& textPickerLayoutProperty, bool isUpateTextContentOnly);
    void UpdatePickerTextProperties(const RefPtr<TextLayoutProperty>& textLayoutProperty,
        const RefPtr<TextPickerLayoutProperty>& textPickerLayoutProperty, uint32_t currentIndex, uint32_t middleIndex,
        uint32_t showCount);
    void UpdateSelectedTextProperties(const RefPtr<PickerTheme>& pickerTheme,
        const RefPtr<TextLayoutProperty>& textLayoutProperty,
        const RefPtr<TextPickerLayoutProperty>& textPickerLayoutProperty);
    void UpdateCandidateTextProperties(const RefPtr<PickerTheme>& pickerTheme,
        const RefPtr<TextLayoutProperty>& textLayoutProperty,
        const RefPtr<TextPickerLayoutProperty>& textPickerLayoutProperty);
    void UpdateDisappearTextProperties(const RefPtr<PickerTheme>& pickerTheme,
        const RefPtr<TextLayoutProperty>& textLayoutProperty,
        const RefPtr<TextPickerLayoutProperty>& textPickerLayoutProperty);
    void AddAnimationTextProperties(uint32_t currentIndex, const RefPtr<TextLayoutProperty>& textLayoutProperty);
    void UpdateTextPropertiesLinear(bool isDown, double scale);
    void TextPropertiesLinearAnimation(const RefPtr<TextLayoutProperty>& textLayoutProperty, uint32_t index,
        uint32_t showCount, bool isDown, double scale);
    void FlushAnimationTextProperties(bool isDown);
    Dimension LinearFontSize(const Dimension& startFontSize, const Dimension& endFontSize, double percent);
    void ClearCurrentTextOptions(const RefPtr<TextPickerLayoutProperty>& textPickerLayoutProperty,
        bool isUpateTextContentOnly, bool isDirectlyClear);
    void UpdateDefaultTextProperties(const RefPtr<TextLayoutProperty>& textLayoutProperty,
        const RefPtr<TextPickerLayoutProperty>& textPickerLayoutProperty);

    RefPtr<TextPickerLayoutProperty> GetParentLayout() const;
    RefPtr<TouchEventImpl> CreateItemTouchEventListener();
    void OnAroundButtonClick(RefPtr<EventParam> param);
    void OnMiddleButtonTouchDown();
    void OnMiddleButtonTouchMove();
    void OnMiddleButtonTouchUp();
    int32_t GetMiddleButtonIndex();

    bool touchEventInit_ = false;
    RefPtr<InputEvent> CreateMouseHoverEventListener(RefPtr<EventParam> param);
    RefPtr<ClickEvent> CreateItemClickEventListener(RefPtr<EventParam> param);
    void SetAccessibilityAction();

    void InitTextFontFamily();
    bool SpringCurveTailMoveProcess(bool useRebound, double& dragDelta);
    void SpringCurveTailEndProcess(bool useRebound, bool stopMove);
    void UpdateTextAccessibilityProperty(
        int32_t virtualIndex, std::list<RefPtr<UINode>>::iterator& iter, bool virtualIndexValidate);
    void OnWindowHide() override;
    void OnWindowShow() override;

    void InitTextFadeOut();
    void UpdateTextOverflow(bool isSel, const RefPtr<TextLayoutProperty>& textLayoutProperty);
    double GetDragDeltaLessThanJumpInterval(
        double offsetY, float originalDragDelta, bool useRebound, float shiftDistance);
    void RegisterWindowStateChangedCallback();
    void UnregisterWindowStateChangedCallback();

    void HandleEnterSelectedArea(double scrollDelta, float shiftDistance);

    bool isFocusColumn_ = false;
    bool isTextFadeOut_ = false;
    float localDownDistance_ = 0.0f;
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
    EventCallback EventCallback_;
    EventCallback scrollStopEventCallback_;
    EventCallback enterSelectedAreaEventCallback_;
    RefPtr<ClickEvent> clickEventListener_;
    bool enabled_ = true;
    int32_t focusKeyID_ = 0;
    RefPtr<TouchEventImpl> touchListener_;
    bool isPress_ = false;
    bool isHover_ = false;
    RefPtr<InputEvent> mouseEvent_;
    double defaultPickerItemHeight_ = 0.0;
    uint32_t selectedIndex_ = 0;
    std::string selectedValue_;
    std::vector<std::string> range_ { "" };
    uint32_t currentIndex_ = 0;
    std::vector<NG::RangeContent> options_;
    int32_t columnkind_ = 0;
    int32_t currentChildIndex_ = 0;
    float deltaSize_ = 0.0f;
    double totalDragDelta_ = 0.0;
    double yLast_ = 0.0;
    double yOffset_ = 0.0;
    double jumpInterval_ = 0.0;
    Size optionSize_;
    Dimension fixHeight_;
    bool isIndexChanged_ = false;

    RefPtr<PanEvent> panEvent_;
    bool pressed_ = false;
    double scrollDelta_ = 0.0;
    bool animationCreated_ = false;
    RefPtr<TextPickerTossAnimationController> tossAnimationController_ =
        AceType::MakeRefPtr<TextPickerTossAnimationController>();
    RefPtr<NodeAnimatablePropertyFloat> scrollProperty_;
    RefPtr<NodeAnimatablePropertyFloat> aroundClickProperty_;
    std::shared_ptr<AnimationUtils::Animation> animation_;
    std::shared_ptr<AnimationUtils::Animation> reboundAnimation_;
    std::vector<TextProperties> animationProperties_;
    float dividerSpacing_ = 0.0f;
    float gradientHeight_ = 0.0f;
    bool isReboundInProgress_ = false;
    TextPickerOverscroller overscroller_;
    ColumnChangeCallback changeCallback_;

    int32_t halfDisplayCounts_ = 0;

    double mainVelocity_ = 0.0;
    float offsetCurSet_ = 0.0f;
    float distancePercent_ = 0.0f;
    bool isTossStatus_ = false;
    bool clickBreak_ = false;
    bool touchBreak_ = false;
    bool animationBreak_ = false;
    bool needOptionPropertyHeightReset_ = false;
    bool isLoop_ = true;
    bool isDownScroll_ = false;

    bool hasAppCustomFont_ = false;
    bool hasUserDefinedDisappearFontFamily_ = false;
    bool hasUserDefinedNormalFontFamily_ = false;
    bool hasUserDefinedSelectedFontFamily_ = false;

    bool isDisableTextStyleAnimation_ = false;
    bool isShow_ = true;
    bool isEnableHaptic_ = true;
    std::shared_ptr<IPickerAudioHaptic> hapticController_ = nullptr;

    uint32_t currentEnterIndex_ = 0;

    ACE_DISALLOW_COPY_AND_MOVE(TextPickerColumnPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_PICKER_TEXT_PICKER_COLUMN_PATTERN_H
