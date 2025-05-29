/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_LAYOUT_POSITION_PARAM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_LAYOUT_POSITION_PARAM_H

#include <functional>
#include <optional>

#include "base/geometry/animatable_dimension.h"
#include "base/geometry/calc_dimension.h"
#include "base/geometry/dimension.h"
#include "core/common/resource/resource_object.h"
#include "core/components/common/layout/constants.h"
#include "core/pipeline/base/constants.h"

namespace OHOS::Ace {

constexpr int32_t HORIZONTAL_DIRECTION_RANGE = 3;
constexpr int32_t VERTICAL_DIRECTION_RANGE = 6;
constexpr int32_t HORIZONTAL_DIRECTION_START_INDEX = 7;
constexpr int32_t HORIZONTAL_DIRECTION_END_INDEX = 8;

struct PositionParam {
    std::pair<AnimatableDimension, bool> left = { AnimatableDimension(0.0, DimensionUnit::PX), false };
    std::pair<AnimatableDimension, bool> right = { AnimatableDimension(0.0, DimensionUnit::PX), false };
    std::pair<AnimatableDimension, bool> top = { AnimatableDimension(0.0, DimensionUnit::PX), false };
    std::pair<AnimatableDimension, bool> bottom = { AnimatableDimension(0.0, DimensionUnit::PX), false };
    std::pair<Dimension, Dimension> anchor = {0.0_px, 0.0_px};
    PositionType type = PositionType::PTRELATIVE;
};

struct EdgesParam {
    std::optional<Dimension> top;
    std::optional<Dimension> left;
    std::optional<Dimension> bottom;
    std::optional<Dimension> right;
    std::optional<Dimension> start;
    std::optional<Dimension> end;
    struct resourceUpdater {
        RefPtr<ResourceObject> resObj;
        std::function<void(const RefPtr<ResourceObject>&, EdgesParam&)> updateFunc;
    };
    std::unordered_map<std::string, resourceUpdater> resMap_;
    EdgesParam() = default;

    void SetTop(const CalcDimension& top)
    {
        this->top = top;
    }

    void SetLeft(const CalcDimension& left)
    {
        this->left = left;
    }

    void SetBottom(const CalcDimension& bottom)
    {
        this->bottom = bottom;
    }

    void SetRight(const CalcDimension& right)
    {
        this->right = right;
    }

    bool operator==(const EdgesParam& rhs) const
    {
        return ((this->top == rhs.top) && (this->left == rhs.left) && (this->bottom == rhs.bottom) &&
                (this->right == rhs.right));
    }

    std::string ToString() const
    {
        std::string str;
        str.append("top: [").append(top.has_value() ? top->ToString() : "NA").append("]");
        str.append("left: [").append(left.has_value() ? left->ToString() : "NA").append("]");
        str.append("right: [").append(right.has_value() ? right->ToString() : "NA").append("]");
        str.append("bottom: [").append(bottom.has_value() ? bottom->ToString() : "NA").append("]");
        return str;
    }

    void AddResource(
        const std::string& key,
        const RefPtr<ResourceObject>& resObj,
        std::function<void(const RefPtr<ResourceObject>&, EdgesParam&)>&& updateFunc)
    {
        if (resObj == nullptr || !updateFunc) {
            return;
        }
        resMap_[key] = {resObj, std::move(updateFunc)};
    }

    void ReloadResources()
    {
        for (const auto& [key, resourceUpdater] : resMap_) {
            resourceUpdater.updateFunc(resourceUpdater.resObj, *this);
        }
    }
};

enum class AlignDirection {
    LEFT = 0,
    MIDDLE,
    RIGHT,
    TOP,
    CENTER,
    BOTTOM,
    START,
    END,
};
struct AlignRule {
    std::string anchor;
    union {
        HorizontalAlign horizontal;
        VerticalAlign vertical;
    };
    
    bool operator==(const AlignRule& right) const
    {
        return ((this->anchor == right.anchor) && (this->vertical == right.vertical) &&
                (this->horizontal == right.horizontal));
    }
    bool operator!=(const AlignRule& right) const
    {
        return !operator==(right);
    }
};

enum class ChainStyle {
    SPREAD,
    SPREAD_INSIDE,
    PACKED,
};

enum class LineDirection {
    VERTICAL,
    HORIZONTAL,
};

enum class BarrierDirection {
    LEFT,
    RIGHT,
    TOP,
    BOTTOM,
    START,
    END,
};

struct GuidelineInfo {
    std::string id;
    LineDirection direction = LineDirection::VERTICAL;
    std::optional<Dimension> start;
    std::optional<Dimension> end;
    struct resourceUpdater {
        RefPtr<ResourceObject> resObj;
        std::function<void(const RefPtr<ResourceObject>&, GuidelineInfo&)> updateFunc;
    };
    std::unordered_map<std::string, resourceUpdater> resMap_;

    bool operator==(const GuidelineInfo& right) const
    {
        return ((this->id == right.id) && (this->direction == right.direction) &&
                (this->start == right.start) && (this->end == right.end));
    }

    void AddResource(
        const std::string& key,
        const RefPtr<ResourceObject>& resObj,
        std::function<void(const RefPtr<ResourceObject>&, GuidelineInfo&)>&& updateFunc)
    {
        if (resObj == nullptr || !updateFunc) {
            return;
        }
        resMap_[key] = {resObj, std::move(updateFunc)};
    }

    void ReloadResources()
    {
        for (const auto& [key, resourceUpdater] : resMap_) {
            resourceUpdater.updateFunc(resourceUpdater.resObj, *this);
        }
    }
};

struct ChainInfo {
    std::optional<LineDirection> direction;
    std::optional<ChainStyle> style;

    bool operator==(const ChainInfo& right) const
    {
        return ((this->direction == right.direction) && (this->style == right.style));
    }
};

struct BarrierInfo {
    std::string id;
    BarrierDirection direction = BarrierDirection::LEFT;
    std::vector<std::string> referencedId;

    bool operator==(const BarrierInfo& right) const
    {
        return ((this->id == right.id) && (this->direction == right.direction) &&
                (this->referencedId == right.referencedId));
    }
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_LAYOUT_POSITION_PARAM_H
