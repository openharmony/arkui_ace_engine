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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_FIELD_TEXT_SELECTOR_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_FIELD_TEXT_SELECTOR_H

#include <cstdint>
#include <string>

#include "base/geometry/ng/offset_t.h"
#include "frameworks/base/geometry/ng/rect_t.h"

namespace OHOS::Ace::NG {

enum class CaretUpdateType {
    PRESSED,
    LONG_PRESSED,
    DEL,
    EVENT,
    HANDLE_MOVE,
    HANDLE_MOVE_DONE,
    INPUT,
    NONE,
    RIGHT_CLICK
};
/**
 * Stands for selection indexes
 * We use base/destination to indicate the start/end position because of uncertain direction.
 */
struct TextSelector {
    TextSelector() = default;
    TextSelector(int32_t base, int32_t destination) : baseOffset(base), destinationOffset(destination) {}

    void TextUpdate(int32_t base, int32_t destination)
    {
        baseOffset = base;
        destinationOffset = destination;
    }

    void Update(int32_t base, int32_t destination)
    {
        baseOffset = base;
        destinationOffset = destination;
    }

    // Usually called when none is selected.
    void Update(int32_t both)
    {
        baseOffset = both;
        destinationOffset = both;
    }

    bool operator==(const TextSelector& other) const
    {
        return baseOffset == other.baseOffset && destinationOffset == other.destinationOffset;
    }

    bool operator!=(const TextSelector& other) const
    {
        return !operator==(other);
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

    bool StartEqualToDest() const
    {
        return baseOffset == destinationOffset;
    }

    std::string ToString()
    {
        std::string result;
        result.append("base offset: ");
        result.append(std::to_string(baseOffset));
        result.append(", destination offset: ");
        result.append(std::to_string(destinationOffset));
        return result;
    }

    // May larger than, smaller than or equal to destinationOffset.
    int32_t baseOffset = -1;
    OffsetF selectionBaseOffset;

    // When paints caret, this is where the caret position is.
    int32_t destinationOffset = -1;
    OffsetF selectionDestinationOffset;

    int32_t charCount = 0;
    RectF firstHandle;
    RectF secondHandle;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_FIELD_TEXT_SELECTOR_H
