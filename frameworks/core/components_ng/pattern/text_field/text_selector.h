/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_FIELD_TEXT_SELECTOR_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_FIELD_TEXT_SELECTOR_H

#include <cstdint>
#include <string>
#include <functional>

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/rect_t.h"
#include "frameworks/core/components/common/properties/decoration.h"

// avoid windows build error about macro defined in wincon.h
#ifdef DOUBLE_CLICK
#undef DOUBLE_CLICK
#endif

namespace OHOS::Ace::NG {

using OnAccessibilityCallback = std::function<void()>;

enum class CaretUpdateType {
    PRESSED,
    LONG_PRESSED,
    ICON_PRESSED,
    DEL,
    EVENT,
    HANDLE_MOVE,
    HANDLE_MOVE_DONE,
    INPUT,
    NONE,
    RIGHT_CLICK,
    VISIBLE_PASSWORD_ICON,
    DOUBLE_CLICK
};

enum class AIResetSelectionReason {
    INIT_SELECTION = 0,
    SHOW_FOR_CANCEL = 1,
    LONG_PRESS = 2,
    CLICK = 3,
    DRAG_START = 4,
    DRAG_START_ON_CHILDREN = 5,
    CLOSE_CONTEXT_MENU = 6
};
/**
 * Stands for selection indexes
 * We use base/destination to indicate the start/end position because of uncertain direction.
 */
struct HandleInfo {
    int32_t index = 0;
    RectF rect;

    void AddRectY(float deltaY)
    {
        auto newOffset = rect.GetOffset();
        newOffset.AddY(deltaY);
        rect.SetOffset(newOffset);
    }

    void AddRectX(float deltaX)
    {
        auto newOffset = rect.GetOffset();
        newOffset.AddX(deltaX);
        rect.SetOffset(newOffset);
    }
};
struct TextSelector {
    TextSelector() = default;
    TextSelector(int32_t base, int32_t destination) : baseOffset(base), destinationOffset(destination) {}

    void SetOnAccessibility(OnAccessibilityCallback&& onAccessibilityCallback)
    {
        if (onAccessibilityCallback) {
            onAccessibilityCallback_ = std::move(onAccessibilityCallback);
        }
    }

    void FireAccessibilityCallback() const
    {
        if (onAccessibilityCallback_) {
            onAccessibilityCallback_();
        }
    }

    void Update(int32_t base, int32_t destination)
    {
        if (base == baseOffset && destination == destinationOffset) {
            return;
        }
        bool isChanged = baseOffset != destinationOffset || base != destination;
        baseOffset = base;
        if (baseOffset >= 0) {
            lastValidStart = baseOffset;
        }
        destinationOffset = destination;
        if (isChanged) {
            FireAccessibilityCallback();
        }
    }

    // Usually called when none is selected.
    void Update(int32_t both)
    {
        if ((baseOffset != both) || (destinationOffset != both)) {
            if (baseOffset != destinationOffset) {
                FireAccessibilityCallback();
            }
        }
        baseOffset = both;
        destinationOffset = both;
        if (baseOffset >= 0) {
            lastValidStart = baseOffset;
        }
    }

    void ReverseTextSelector()
    {
        if (baseOffset > destinationOffset) {
            Update(destinationOffset, baseOffset);
        }
    }

    bool operator==(const TextSelector& other) const
    {
        return baseOffset == other.baseOffset && destinationOffset == other.destinationOffset;
    }

    bool operator!=(const TextSelector& other) const
    {
        return !operator==(other);
    }

    inline int32_t GetTextStart() const
    {
        return std::min(baseOffset, destinationOffset);
    }

    inline int32_t GetTextEnd() const
    {
        return std::max(baseOffset, destinationOffset);
    }

    inline int32_t GetStart() const
    {
        return baseOffset;
    }

    inline int32_t GetEnd() const
    {
        return destinationOffset;
    }

    inline bool IsValid() const
    {
        return baseOffset > -1 && destinationOffset > -1;
    }

    inline bool SelectNothing() const
    {
        return !IsValid() || baseOffset == destinationOffset;
    }

    bool MoveSelectionLeft()
    {
        destinationOffset = std::max(0, destinationOffset - 1);
        return destinationOffset == baseOffset;
    }

    bool MoveSelectionRight()
    {
        destinationOffset = std::min(charCount, destinationOffset + 1);
        return destinationOffset == baseOffset;
    }

    double GetSelectHeight() const
    {
        return std::max(firstHandle.Height(), secondHandle.Height());
    }

    bool StartEqualToDest() const
    {
        return baseOffset == destinationOffset;
    }

    bool StartGreaterDest() const
    {
        return baseOffset > destinationOffset;
    }

    bool ContainsRange(const std::pair<int32_t, int32_t>& range) const
    {
        return IsValid() && GetTextStart() <= range.first && range.second <= GetTextEnd();
    }

    void ResetAiSelected()
    {
        aiStart = std::nullopt;
        aiEnd = std::nullopt;
    }

    std::string ToString()
    {
        std::string result;
        result.append("baseOffset: ");
        result.append(std::to_string(baseOffset));
        result.append(", selectionBaseOffset: ");
        result.append(selectionBaseOffset.ToString());
        result.append(", destinationOffset: ");
        result.append(std::to_string(destinationOffset));
        result.append(", selectionDestinationOffset: ");
        result.append(selectionDestinationOffset.ToString());
        result.append(", firstHandle: ");
        result.append(firstHandle.ToString());
        result.append(", secondHandle: ");
        result.append(secondHandle.ToString());
        result.append(", firstHandleOffset_: ");
        result.append(firstHandleOffset_.ToString());
        result.append(", secondHandleOffset_: ");
        result.append(secondHandleOffset_.ToString());
        return result;
    }

    // May larger than, smaller than or equal to destinationOffset.
    int32_t baseOffset = -1;
    OffsetF selectionBaseOffset;

    // When paints caret, this is where the caret position is.
    int32_t destinationOffset = -1;
    OffsetF selectionDestinationOffset;

    std::optional<int32_t> aiStart;
    std::optional<int32_t> aiEnd;

    int32_t charCount = 0;
    RectF firstHandle;
    RectF secondHandle;
    OffsetF firstHandleOffset_;
    OffsetF secondHandleOffset_;
    OnAccessibilityCallback onAccessibilityCallback_;
    int32_t lastValidStart = 0;
};

enum class TextSpanType : int32_t {
    TEXT = 0,
    IMAGE,
    MIXED,
    BUILDER,
    NONE,
};

enum class TextResponseType : int32_t {
    RIGHT_CLICK = 0,
    LONG_PRESS,
    SELECTED_BY_MOUSE,
    NONE,
};

enum class SelectionMenuType : int32_t {
    SELECTION_MENU = 0,
    PREVIEW_MENU = 1,
};

struct PreviewMenuOptions {
    HapticFeedbackMode hapticFeedbackMode = HapticFeedbackMode::DISABLED;
};

struct SelectMenuParam {
    std::function<void(int32_t, int32_t)> onAppear;
    std::function<void()> onDisappear;
    std::function<void(int32_t, int32_t)> onMenuShow;
    std::function<void(int32_t, int32_t)> onMenuHide;
    bool isValid = true;
    PreviewMenuOptions previewMenuOptions;
};

struct SelectionMenuParams {
    TextSpanType type;
    std::function<void()> buildFunc;
    std::function<void(int32_t, int32_t)> onAppear;
    std::function<void()> onDisappear;
    TextResponseType responseType;
    std::function<void(int32_t, int32_t)> onMenuShow;
    std::function<void(int32_t, int32_t)> onMenuHide;
    bool isValid = true;

    SelectionMenuParams(TextSpanType _type, std::function<void()> _buildFunc,
        std::function<void(int32_t, int32_t)> _onAppear, std::function<void()> _onDisappear,
        TextResponseType _responseType)
        : type(_type), buildFunc(_buildFunc), onAppear(_onAppear), onDisappear(_onDisappear),
          responseType(_responseType)
    {}
};

struct TextSpanTypeMapper {
    static bool GetTextSpanTypeFromJsType(int32_t spanTypeId, NG::TextSpanType& spanType)
    {
        std::unordered_map<int32_t, NG::TextSpanType> spanTypeMap = {
            { 0, NG::TextSpanType::TEXT },
            { 1, NG::TextSpanType::IMAGE },
            { 2, NG::TextSpanType::MIXED },
            { 3, NG::TextSpanType::NONE }
        };
        if (spanTypeMap.find(spanTypeId) != spanTypeMap.end()) {
            spanType = spanTypeMap[spanTypeId];
            return true;
        }
        spanType = static_cast<NG::TextSpanType>(spanTypeId);
        return false;
    }

    static int32_t GetJsSpanType(const NG::TextSpanType& spanType, bool isValid)
    {
        std::unordered_map<NG::TextSpanType, int32_t> spanTypeMap = {
            { NG::TextSpanType::TEXT, 0 },
            { NG::TextSpanType::IMAGE, 1 },
            { NG::TextSpanType::MIXED, 2 },
            { NG::TextSpanType::NONE, 3 }
        };
        if (isValid) {
            return spanTypeMap[spanType];
        }
        return static_cast<int32_t>(spanType);
    }
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_FIELD_TEXT_SELECTOR_H
