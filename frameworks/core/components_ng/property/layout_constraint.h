/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PROPERTIES_LAYOUT_CONSTRAINT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PROPERTIES_LAYOUT_CONSTRAINT_H

#include <optional>
#include <string>

#include "base/geometry/ng/size_t.h"
#include "core/components_ng/property/calc_length.h"

namespace OHOS::Ace::NG {
template<typename T>
struct LayoutConstraintT {
    ScaleProperty scaleProperty;
    SizeT<T> minSize { 0, 0 };
    SizeT<T> maxSize { Infinity<T>(), Infinity<T>() };
    std::optional<SizeT<T>> parentIdealSize;
    std::optional<SizeT<T>> selfIdealSize;

    void Reset()
    {
        scaleProperty.Reset();
        minSize = { 0, 0 };
        maxSize = { Infinity<T>(), Infinity<T>() };
        parentIdealSize.reset();
        selfIdealSize.reset();
    }

    void MinusPadding(const std::optional<T>& left, const std::optional<T>& right, const std::optional<T>& top,
        const std::optional<T>& bottom)
    {
        minSize.MinusPadding(left, right, top, bottom);
        maxSize.MinusPadding(left, right, top, bottom);
        if (parentIdealSize.has_value()) {
            parentIdealSize.value().MinusPadding(left, right, top, bottom);
        }
        if (selfIdealSize.has_value()) {
            selfIdealSize.value().MinusPadding(left, right, top, bottom);
        }
    }

    bool operator==(const LayoutConstraintT& layoutConstraint) const
    {
        return (minSize == layoutConstraint.minSize) && (maxSize == layoutConstraint.maxSize) &&
               (parentIdealSize == layoutConstraint.parentIdealSize) &&
               (selfIdealSize == layoutConstraint.selfIdealSize);
    }

    bool operator!=(const LayoutConstraintT& layoutConstraint) const
    {
        return !(*this == layoutConstraint);
    }

    bool UpdateSelfIdealSizeWithCheck(const SizeT<T>& size)
    {
        if (selfIdealSize == size) {
            return false;
        }
        if (selfIdealSize.has_value()) {
            return selfIdealSize->UpdateSizeWithCheck(size);
        }
        selfIdealSize = size;
        return true;
    }

    bool UpdateParentIdealSizeWithCheck(const SizeT<T>& size)
    {
        if (parentIdealSize == size) {
            return false;
        }
        if (parentIdealSize.has_value()) {
            return parentIdealSize->UpdateSizeWithCheck(size);
        }
        parentIdealSize = size;
        return true;
    }

    bool UpdateMaxSizeWithCheck(const SizeT<T>& size)
    {
        if (maxSize == size) {
            return false;
        }
        return maxSize.UpdateSizeWhenSmaller(size);
    }

    bool UpdateMinSizeWithCheck(const SizeT<T>& size)
    {
        if (minSize == size) {
            return false;
        }
        return minSize.UpdateSizeWhenLarger(size);
    }

    std::string ToString() const
    {
        std::string str;
        str.append("minSize: [").append(minSize.ToString()).append("]");
        str.append("maxSize: [").append(maxSize.ToString()).append("]");
        str.append("parentIdealSize: [")
            .append(parentIdealSize.has_value() ? parentIdealSize.value().ToString() : "NA")
            .append("]");
        str.append("selfIdealSize: [")
            .append(selfIdealSize.has_value() ? selfIdealSize.value().ToString() : "NA")
            .append("]");
        return str;
    }
};

using LayoutConstraintF = LayoutConstraintT<float>;
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PROPERTIES_LAYOUT_CONSTRAINT_H