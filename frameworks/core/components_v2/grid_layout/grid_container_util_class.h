/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_GRID_LAYOUT_GRID_CONTAINER_UTIL_CLASS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_GRID_LAYOUT_GRID_CONTAINER_UTIL_CLASS_H

#include <functional>
#include <sstream>
#include <utility>

#include "base/geometry/dimension.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/common/resource/resource_object.h"
#include "core/components/common/layout/grid_container_info.h"

namespace OHOS::Ace::V2 {

constexpr int32_t DEFAULT_COLUMN_NUMBER = 12;
constexpr int32_t DEFAULT_XS_COLUMN = 2;
constexpr int32_t DEFAULT_SM_COLUMN = 4;
constexpr int32_t DEFAULT_MD_COLUMN = 8;
constexpr int32_t DEFAULT_LG_COLUMN = 12;

struct GridContainerSize : public Referenced {
    GridContainerSize() = default;
    explicit GridContainerSize(int32_t column)
    {
        xs = column;
        sm = column;
        md = column;
        lg = column;
        xl = column;
        xxl = column;
    };
    DEFINE_COPY_CONSTRUCTOR_AND_COPY_OPERATOR_AND_COMPARE_OPERATOR_WITH_PROPERTIES(
        GridContainerSize, (xs)(sm)(md)(lg)(xl)(xxl))
    int32_t xs = DEFAULT_XS_COLUMN;
    int32_t sm = DEFAULT_SM_COLUMN;
    int32_t md = DEFAULT_MD_COLUMN;
    int32_t lg = DEFAULT_LG_COLUMN;
    int32_t xl = DEFAULT_LG_COLUMN;
    int32_t xxl = DEFAULT_LG_COLUMN;

    std::string ToString()
    {
        std::stringstream ss;
        ss << "GridContainerSize: {";
        ss << "xs: " << xs << ", ";
        ss << "sm: " << sm << ", ";
        ss << "md: " << md << ", ";
        ss << "lg: " << lg << ", ";
        ss << "xl: " << xl << ", ";
        ss << "xxl: " << xxl;
        ss << " }";
        return ss.str();
    }
};

enum class BreakPointsReference {
    WindowSize,
    ComponentSize,
};

enum class GridRowDirection {
    Row,
    RowReverse,
};

enum class GridSizeType {
    XS = 0,
    SM = 1,
    MD = 2,
    LG = 3,
    XL = 4,
    XXL = 5,
    UNDEFINED = 6,
};

struct GridSizeInfo : public Referenced {
    std::vector<Dimension> sizeInfo {
        Dimension(320, DimensionUnit::VP),
        Dimension(600, DimensionUnit::VP),
        Dimension(840, DimensionUnit::VP),
    };

    void Reset()
    {
        sizeInfo.clear();
    }
};

class Gutter : public AceType {
    DECLARE_ACE_TYPE(Gutter, AceType);

public:
    Gutter() = default;
    DEFINE_COPY_CONSTRUCTOR_AND_COPY_OPERATOR_AND_COMPARE_OPERATOR_WITH_PROPERTIES(
        Gutter, (xXs)(yXs)(xSm)(ySm)(xMd)(yMd)(xLg)(yLg)(xXl)(yXl)(xXXl)(yXXl))
    explicit Gutter(Dimension dimension)
        : xXs(dimension), yXs(dimension), xSm(dimension), ySm(dimension), xMd(dimension), yMd(dimension),
          xLg(dimension), yLg(dimension), xXl(dimension), yXl(dimension), xXXl(dimension), yXXl(dimension) {};
    Gutter(Dimension xDimension, Dimension yDimension)
        : xXs(xDimension), yXs(yDimension), xSm(xDimension), ySm(yDimension), xMd(xDimension), yMd(yDimension),
          xLg(xDimension), yLg(yDimension), xXl(xDimension), yXl(yDimension), xXXl(xDimension), yXXl(yDimension) {};

    void SetYGutter(Dimension yDimension)
    {
        yXs = yDimension;
        ySm = yDimension;
        yMd = yDimension;
        yLg = yDimension;
        yXl = yDimension;
        yXXl = yDimension;
    }

    void SetXGutter(Dimension xDimension)
    {
        xXs = xDimension;
        xSm = xDimension;
        xMd = xDimension;
        xLg = xDimension;
        xXl = xDimension;
        xXXl = xDimension;
    }
    Dimension xXs;
    Dimension yXs;
    Dimension xSm;
    Dimension ySm;
    Dimension xMd;
    Dimension yMd;
    Dimension xLg;
    Dimension yLg;
    Dimension xXl;
    Dimension yXl;
    Dimension xXXl;
    Dimension yXXl;
    struct resourceUpdater {
        RefPtr<ResourceObject> resObj;
        std::function<void(const RefPtr<ResourceObject>&, RefPtr<V2::Gutter>&)> updateFunc;
    };
    std::unordered_map<std::string, resourceUpdater> resMap_;

    std::string ToString()
    {
        std::stringstream ss;
        ss << "Gutter: {";
        ss << "xXs: " << xXs.ToString().c_str() << ", ";
        ss << "yXs: " << yXs.ToString().c_str() << ", ";
        ss << "xSm: " << xSm.ToString().c_str() << ", ";
        ss << "ySm: " << ySm.ToString().c_str() << ", ";
        ss << "xMd: " << xMd.ToString().c_str() << ", ";
        ss << "yMd: " << yMd.ToString().c_str() << ", ";
        ss << "xLg: " << xLg.ToString().c_str() << ", ";
        ss << "yLg: " << yLg.ToString().c_str() << ", ";
        ss << "xXl: " << xXl.ToString().c_str() << ", ";
        ss << "yXl: " << yXl.ToString().c_str() << ", ";
        ss << "xXXl: " << xXXl.ToString().c_str() << ", ";
        ss << "yXXl: " << yXXl.ToString().c_str();
        ss << " }";
        return ss.str();
    }

    void AddResource(
        const std::string& key,
        const RefPtr<ResourceObject>& resObj,
        std::function<void(const RefPtr<ResourceObject>&, RefPtr<V2::Gutter>&)>&& updateFunc)
    {
        if (resObj == nullptr || !updateFunc) {
            return;
        }
        resMap_[key] = {resObj, std::move(updateFunc)};
    }

    void ReloadResources(RefPtr<V2::Gutter>& gutter)
    {
        for (const auto& [key, resourceUpdater] : resMap_) {
            resourceUpdater.updateFunc(resourceUpdater.resObj, gutter);
        }
    }
};

class BreakPoints : public AceType {
    DECLARE_ACE_TYPE(BreakPoints, AceType);

public:
    BreakPoints() = default;
    DEFINE_COPY_CONSTRUCTOR_AND_COPY_OPERATOR_AND_COMPARE_OPERATOR_WITH_PROPERTIES(
        BreakPoints, (reference)(breakpoints))
    BreakPointsReference reference = BreakPointsReference::WindowSize;
    std::vector<std::string> breakpoints { "320vp", "600vp", "840vp" };

    std::string ToString()
    {
        std::stringstream ss;
        ss << "BreakPoints: {";
        ss << "reference: " << static_cast<int32_t>(reference) << ", ";
        ss << "breakpoints: [";
        for (const auto& breakpoint : breakpoints) {
            ss << breakpoint << ", ";
        }
        ss << "]";
        ss << " }";
        return ss.str();
    }
};

} // namespace OHOS::Ace::V2
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_GRID_LAYOUT_GRID_CONTAINER_UTIL_CLASS_H