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

#include "core/components/common/properties/color.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/picker/picker_type_define.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text_picker/textpicker_event_hub.h"
#include "core/components_ng/pattern/text_picker/textpicker_layout_algorithm.h"
#include "core/components_ng/pattern/text_picker/textpicker_layout_property.h"
#include "core/components_ng/pattern/text_picker/textpicker_paint_method.h"
#include "core/components_ng/pattern/text_picker/toss_animation_controller.h"
#include "core/components/picker/picker_theme.h"

namespace OHOS::Ace::NG {
using EventCallback = std::function<void(bool)>;

struct TextProperties {
    Dimension upFontSize;
    Dimension fontSize;
    Dimension downFontSize;
    Color upColor;
    Color currentColor;
    Color downColor;
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
        layoutAlgorithm->SetCurrentOffset(GetCurrentOffset());
        layoutAlgorithm->SetDefaultPickerItemHeight(defaultPickerItemHeight_);
        return layoutAlgorithm;
    }

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<LinearLayoutProperty>(true);
    }

    void FlushCurrentOptions(bool isDown = false, bool isUpateTextContentOnly = false);

    void InitilaScorllEvent();

    void UpdateCurrentOffset(float offset);

    void UpdateColumnChildPosition(double offsetY);

    bool CanMove(bool isDown) const;

    bool NotLoopOptions() const;

    bool InnerHandleScroll(bool isDown, bool isUpatePropertiesOnly = false);

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
            LOGE("input value of range is empty.");
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
            LOGE("index out of range.");
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
        } else {
            LOGE("event callback is null.");
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

private:
    void OnModifyDone() override;
    void OnAttachToFrameNode() override;
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;

    bool OnKeyEvent(const KeyEvent& event);
    bool HandleDirectionKey(KeyCode code);

    void InitPanEvent(const RefPtr<GestureEventHub>& gestureHub);
    void HandleDragStart(const GestureEvent& event);
    void HandleDragMove(const GestureEvent& event);
    void HandleDragEnd();
    void CreateAnimation();
    RefPtr<CurveAnimation<double>> CreateAnimation(double from, double to);
    void HandleCurveStopped();
    void ScrollOption(double delta, bool isJump = false);
    void OnTouchDown();
    void OnTouchUp();
    void InitMouseAndPressEvent();
    void HandleMouseEvent(bool isHover);
    void SetButtonBackgroundColor(const Color& pressColor);
    void PlayPressAnimation(const Color& pressColor);
    void FlushCurrentTextOptions(RefPtr<TextPickerLayoutProperty>& textPickerLayoutProperty,
        bool isUpateTextContentOnly);
    void FlushCurrentImageOptions();
    void FlushCurrentMixtureOptions(RefPtr<TextPickerLayoutProperty>& textPickerLayoutProperty,
        bool isUpateTextContentOnly);
    void UpdatePickerTextProperties(RefPtr<TextLayoutProperty>& textLayoutProperty,
        RefPtr<TextPickerLayoutProperty>& textPickerLayoutProperty,
        uint32_t currentIndex, uint32_t middleIndex, uint32_t showCount);
    void UpdateSelectedTextProperties(RefPtr<PickerTheme>& pickerTheme,
        RefPtr<TextLayoutProperty>& textLayoutProperty,
        RefPtr<TextPickerLayoutProperty>& textPickerLayoutProperty);
    void UpdateCandidateTextProperties(RefPtr<PickerTheme>& pickerTheme,
        RefPtr<TextLayoutProperty>& textLayoutProperty,
        RefPtr<TextPickerLayoutProperty>& textPickerLayoutProperty);
    void UpdateDisappearTextProperties(RefPtr<PickerTheme>& pickerTheme,
        RefPtr<TextLayoutProperty>& textLayoutProperty,
        RefPtr<TextPickerLayoutProperty>& textPickerLayoutProperty);
    void AddAnimationTextProperties(uint32_t currentIndex, RefPtr<TextLayoutProperty>& textLayoutProperty);
    void UpdateTextPropertiesLinear(bool isDown, double scale);
    void TextPropertiesLinearAnimation(RefPtr<TextLayoutProperty>& textLayoutProperty,
        uint32_t index, uint32_t showCount, bool isDown, double scale);
    void FlushAnimationTextProperties(bool isDown);
    Dimension LinearFontSize(const Dimension& startFontSize, const Dimension& endFontSize, double percent);

    float localDownDistance_ = 0.0f;
    Color pressColor_;
    Color hoverColor_;
    EventCallback EventCallback_;
    RefPtr<ClickEvent> clickEventListener_;
    bool enabled_ = true;
    int32_t focusKeyID_ = 0;
    RefPtr<TouchEventImpl> touchListener_;
    bool isPress_ = false;
    bool isHover_ = false;
    RefPtr<InputEvent> mouseEvent_;
    double defaultPickerItemHeight_;
    uint32_t selectedIndex_ = 0;
    std::string selectedValue_;
    std::vector<std::string> range_ { "" };
    uint32_t currentIndex_ = 0;
    std::vector<NG::RangeContent> options_;
    int32_t columnkind_;
    int32_t currentChildIndex_ = 0;
    float deltaSize_ = 0.0f;
    RefPtr<ScrollableEvent> scrollableEvent_;
    double yLast_ = 0.0;
    double yOffset_ = 0.0;
    double jumpInterval_;
    Size optionSize_;
    Dimension fixHeight_;
    bool isIndexChanged_ = false;

    RefPtr<PanEvent> panEvent_;
    bool pressed_ = false;
    double scrollDelta_ = 0.0;
    bool animationCreated_ = false;
    RefPtr<Animator> toController_;
    RefPtr<Animator> fromController_;
    RefPtr<CurveAnimation<double>> fromBottomCurve_;
    RefPtr<CurveAnimation<double>> fromTopCurve_;
    RefPtr<TextPickerTossAnimationController> tossAnimationController_ =
        AceType::MakeRefPtr<TextPickerTossAnimationController>();
    std::vector<TextProperties> animationProperties_;
    bool isJump_ = false;

    ACE_DISALLOW_COPY_AND_MOVE(TextPickerColumnPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_PICKER_TEXT_PICKER_COLUMN_PATTERN_H
