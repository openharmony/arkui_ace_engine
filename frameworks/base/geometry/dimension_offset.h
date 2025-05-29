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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_GEOMETRY_DIMENSION_OFFSET_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_GEOMETRY_DIMENSION_OFFSET_H

#include <cmath>
#include <limits>
#include <optional>
#include <functional>

#include "base/geometry/dimension.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/offset.h"
#include "core/common/resource/resource_object.h"

namespace OHOS::Ace {

class DimensionOffset {
public:
    DimensionOffset() = default;
    ~DimensionOffset() = default;
    DimensionOffset(const Dimension& deltaX, const Dimension& deltaY) : deltaX_(deltaX), deltaY_(deltaY) {}
    DimensionOffset(const Offset& offset) : deltaX_(Dimension(offset.GetX(), DimensionUnit::PX)),
        deltaY_(Dimension(offset.GetY(), DimensionUnit::PX)) {}

    explicit DimensionOffset(const NG::OffsetF& offset)
        : deltaX_(Dimension(offset.GetX())), deltaY_(Dimension(offset.GetY()))
    {}

    const Dimension& GetX() const
    {
        return deltaX_;
    }

    const Dimension& GetY() const
    {
        return deltaY_;
    }

    const std::optional<Dimension>& GetZ() const
    {
        return deltaZ_;
    }

    void SetX(Dimension& x)
    {
        deltaX_ = x;
    }

    void SetY(Dimension& y)
    {
        deltaY_ = y;
    }

    void SetZ(const Dimension& z)
    {
        deltaZ_ = z;
    }

    DimensionOffset operator+(const DimensionOffset& dimensionOffset) const
    {
        return DimensionOffset(deltaX_ + dimensionOffset.deltaX_, deltaY_ + dimensionOffset.deltaY_);
    }

    DimensionOffset operator-(const DimensionOffset& dimensionOffset) const
    {
        return DimensionOffset(deltaX_ - dimensionOffset.deltaX_, deltaY_ - dimensionOffset.deltaY_);
    }

    DimensionOffset operator*(double value) const
    {
        return DimensionOffset(deltaX_ * value, deltaY_ * value);
    }

    bool operator==(const DimensionOffset& dimensionOffset) const
    {
        return deltaX_ == dimensionOffset.deltaX_ && deltaY_ == dimensionOffset.deltaY_ && deltaZ_ == deltaZ_;
    }
    void AddResource(const std::string& key, const RefPtr<ResourceObject>& resObj,
        std::function<void(const RefPtr<ResourceObject>&, DimensionOffset&)>&& updateFunc)
    {
        if (resObj == nullptr || !updateFunc) {
            return;
        }
        resMap_[key] = { resObj, std::move(updateFunc) };
    }

    void ReloadResources()
    {
        for (const auto& [key, resourceUpdater] : resMap_) {
            resourceUpdater.updateFunc(resourceUpdater.resObj, *this);
        }
    }

private:
    Dimension deltaX_;
    Dimension deltaY_;
    std::optional<Dimension> deltaZ_;
    struct ResourceUpdater {
        RefPtr<ResourceObject> resObj;
        std::function<void(const RefPtr<ResourceObject>&, DimensionOffset&)> updateFunc;
    };
    std::unordered_map<std::string, ResourceUpdater> resMap_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_GEOMETRY_DIMENSION_OFFSET_H
