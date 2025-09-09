/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LIST_LIST_CHILDREN_MAIN_SIZE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LIST_LIST_CHILDREN_MAIN_SIZE_H

#include <cstddef>
#include <cstdint>
#include <functional>
#include <optional>
#include <tuple>
#include <vector>

#include "base/geometry/dimension.h"
#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/components_ng/property/measure_property.h"

namespace OHOS::Ace::NG {

using ListChangeFlag = std::uint8_t;

inline constexpr ListChangeFlag LIST_NO_CHANGE = 0;
inline constexpr ListChangeFlag LIST_UPDATE_DEFAULT_SIZE = 1;
inline constexpr ListChangeFlag LIST_UPDATE_CHILD_SIZE = 1 << 1;
inline constexpr ListChangeFlag LIST_UPDATE_LANES = 1 << 2;
inline constexpr ListChangeFlag LIST_UPDATE_SPACE = 1 << 3;
inline constexpr ListChangeFlag LIST_GROUP_UPDATE_HEADER_FOOTER = 1 << 4;
inline constexpr ListChangeFlag LIST_UPDATE_ITEM_COUNT = 1 << 5;
inline constexpr ListChangeFlag LIST_UPDATE_HEADER_FOOTER = 1 << 6;

namespace {
constexpr float DEFAULT_SIZE = -1.0f;
}

class ListChildrenMainSize : public virtual AceType {
    DECLARE_ACE_TYPE(ListChildrenMainSize, AceType);
public:
    ListChildrenMainSize() = default;
    ListChildrenMainSize(const std::vector<float>& mainSize, float defaulatMainSize)
        : childrenSize_(mainSize), defaultSize_(defaulatMainSize) {};
    ~ListChildrenMainSize() override = default;

    void SetOnDataChange(std::function<void(std::tuple<int32_t, int32_t, int32_t>, ListChangeFlag)>&& func)
    {
        onChildrenSizeChange_ = func;
    }

    void ChangeData(const int32_t start, const int32_t deleteCount, const std::vector<float>& newChildrenSize)
    {
        if (deleteCount == -1) {
            childrenSize_.resize(start, DEFAULT_SIZE);
            if (onChildrenSizeChange_) {
                onChildrenSizeChange_(std::make_tuple(start, -1, -1), LIST_UPDATE_CHILD_SIZE);
            }
            return;
        }
        int32_t newChildrenSizeSize = static_cast<int32_t>(newChildrenSize.size());
        int32_t replaceCount = std::min(deleteCount, newChildrenSizeSize);
        int32_t cursor = 0;
        if (static_cast<int32_t>(childrenSize_.size()) < start + replaceCount) {
            childrenSize_.resize(start + replaceCount, DEFAULT_SIZE);
        }
        for (; cursor < replaceCount; cursor++) {
            childrenSize_[start + cursor] = newChildrenSize[cursor];
        }
        if (deleteCount > newChildrenSizeSize) {
            auto deleteStartPos = childrenSize_.begin() + start + cursor;
            auto deleteEndPos = deleteStartPos;
            int32_t needDeleteSpan = deleteCount - newChildrenSizeSize;
            while (deleteEndPos != childrenSize_.end() && needDeleteSpan > 0) {
                needDeleteSpan--;
                deleteEndPos++;
            }
            childrenSize_.erase(deleteStartPos, deleteEndPos);
        } else if (deleteCount < newChildrenSizeSize) {
            auto insertStartPos = childrenSize_.begin() + start + cursor;
            childrenSize_.insert(insertStartPos, newChildrenSize.begin() + cursor, newChildrenSize.end());
        }
        if (onChildrenSizeChange_) {
            onChildrenSizeChange_(std::make_tuple(start, deleteCount, newChildrenSizeSize), LIST_UPDATE_CHILD_SIZE);
        }
    }

    void UpdateDefaultSize(float defaultSize)
    {
        if (NearEqual(defaultSize_, defaultSize)) {
            return;
        }
        defaultSize_ = defaultSize;
        if (onChildrenSizeChange_) {
            // -1: default size changed.
            onChildrenSizeChange_(std::make_tuple(-1, -1, -1), LIST_UPDATE_DEFAULT_SIZE);
        }
    }

    void SyncChildrenSize(float childSize)
    {
        childrenSize_.emplace_back(childSize);
    }

    void SyncChildrenSizeOver()
    {
        if (onChildrenSizeChange_) {
            onChildrenSizeChange_(std::make_tuple(-1, -1, -1), LIST_UPDATE_CHILD_SIZE);
        }
        initialized_ = true;
    }

    bool NeedSync() const
    {
        return !initialized_;
    }

    float GetChildSize(int32_t index, bool isStackFromEnd = false)
    {
        index = isStackFromEnd ? static_cast<int32_t>(childrenSize_.size()) - index - 1 : index;
        return isRoundingMode_ ? GetRoundingSize(index) : GetRealSize(index);
    }

    void ResizeChildrenSize(int32_t size)
    {
        childrenSize_.resize(std::max(size, 0), DEFAULT_SIZE);
    }

    void SetIsRoundingMode()
    {
        isRoundingMode_ = true;
    }

private:
    float GetRealSize(int32_t index)
    {
        if (index > (static_cast<int32_t>(childrenSize_.size()) - 1) || index < 0 ||
            NearEqual(childrenSize_[index], DEFAULT_SIZE)) {
            return defaultSize_;
        }
        if (Negative(childrenSize_[index])) {
            TAG_LOGW(AceLogTag::ACE_LIST, "ChildrenMainSize child index:%{public}d, size:%{public}f.", index,
                childrenSize_[index]);
        }
        return childrenSize_[index];
    }

    float GetRoundingSize(int32_t index)
    {
        if (index > (static_cast<int32_t>(childrenSize_.size()) - 1) || index < 0 ||
            NearEqual(childrenSize_[index], DEFAULT_SIZE)) {
            return Round(defaultSize_);
        }
        if (Negative(childrenSize_[index])) {
            TAG_LOGW(AceLogTag::ACE_LIST, "ChildrenMainSize child index:%{public}d, size:%{public}f.", index,
                childrenSize_[index]);
        }
        return Round(childrenSize_[index]);
    }

    std::vector<float> childrenSize_;
    float defaultSize_ = 0.0f;
    bool initialized_ = false;
    bool isRoundingMode_ = false;
    std::function<void(std::tuple<int32_t, int32_t, int32_t>, ListChangeFlag)> onChildrenSizeChange_;
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LIST_LIST_CHILDREN_MAIN_SIZE_H