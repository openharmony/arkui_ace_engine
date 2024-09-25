/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_MENU_PAINT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_MENU_PAINT_PROPERTY_H

#include "base/geometry/dimension.h"
#include "base/utils/utils.h"
#include "core/components/common/properties/placement.h"
#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/render/paint_property.h"
#include "core/components_v2/inspector/utils.h"

namespace OHOS::Ace::NG {
namespace {
constexpr Dimension ARROW_WIDTH = 32.0_vp;
// arrow actual display height against shadow
constexpr Dimension ARROW_HIGHT = 8.0_vp;
constexpr Dimension TARGET_SECURITY = 8.0_vp;
// space from menu to target for arrow display
constexpr Dimension TARGET_SPACE = 8.0_vp;
constexpr Dimension ARROW_ZERO_PERCENT_VALUE = Dimension(0.0, DimensionUnit::PERCENT);
constexpr Dimension ARROW_HALF_PERCENT_VALUE = Dimension(0.5, DimensionUnit::PERCENT);
constexpr Dimension ARROW_ONE_HUNDRED_PERCENT_VALUE = Dimension(1.0, DimensionUnit::PERCENT);
// preview menu
constexpr Dimension PORTRAIT_TOP_SECURITY = 48.0_vp;
constexpr Dimension PORTRAIT_BOTTOM_SECURITY = 48.0_vp;
constexpr Dimension PORTRAIT_TOP_SECURITY_API12 = 16.0_vp;
constexpr Dimension PORTRAIT_BOTTOM_SECURITY_API12 = 4.0_vp;
constexpr Dimension LANDSCAPE_TOP_SECURITY = 24.0_vp;
constexpr Dimension LANDSCAPE_BOTTOM_SECURITY = 24.0_vp;
constexpr Dimension PREVIEW_INNER_SECURITY = 24.0_vp;
} // namespace
class ACE_EXPORT MenuPaintProperty : public PaintProperty {
    DECLARE_ACE_TYPE(MenuPaintProperty, PaintProperty)

public:
    MenuPaintProperty() = default;
    ~MenuPaintProperty() override = default;

    RefPtr<PaintProperty> Clone() const override
    {
        auto paintProperty = MakeRefPtr<MenuPaintProperty>();
        paintProperty->propEnableArrow_ = CloneEnableArrow();
        paintProperty->propArrowOffset_ = CloneArrowOffset();
        paintProperty->propArrowPosition_ = CloneArrowPosition();
        paintProperty->propArrowPlacement_ = CloneArrowPlacement();
        paintProperty->propClipPath_ = CloneClipPath();
        return paintProperty;
    }

    void Reset() override
    {
        PaintProperty::Reset();
        ResetEnableArrow();
        ResetArrowOffset();
        ResetArrowPosition();
        ResetArrowPlacement();
        ResetClipPath();
    }

    std::string ConvertPlacementToString(const Placement& place) const
    {
        static const LinearEnumMapNode<Placement, std::string> placementTable[] = {
            { Placement::LEFT, "Placement.Left" },
            { Placement::RIGHT, "Placement.Right" },
            { Placement::TOP, "Placement.Top" },
            { Placement::BOTTOM, "Placement.Bottom" },
            { Placement::TOP_LEFT, "Placement.TopLeft" },
            { Placement::TOP_RIGHT, "Placement.TopRight" },
            { Placement::BOTTOM_LEFT, "Placement.BottomLeft" },
            { Placement::BOTTOM_RIGHT, "Placement.BottomRight" },
            { Placement::LEFT_TOP, "Placement.LeftTop" },
            { Placement::LEFT_BOTTOM, "Placement.LeftBottom" },
            { Placement::RIGHT_TOP, "Placement.RightTop" },
            { Placement::RIGHT_BOTTOM, "Placement.RightBottom" },
            { Placement::NONE, "Placement.None" },
        };

        auto index = BinarySearchFindIndex(placementTable, ArraySize(placementTable), place);
        return index < 0 ? "Placement.None" : placementTable[index].value;
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override
    {
        PaintProperty::ToJsonValue(json, filter);
        /* no fixed attr below, just return */
        if (filter.IsFastFilter()) {
            return;
        }
        json->PutExtAttr("enableArrow", V2::ConvertBoolToString(GetEnableArrow().value_or(false)).c_str(), filter);
        json->PutExtAttr("arrowOffset",
            GetArrowOffset().value_or(Dimension(0.0, DimensionUnit::VP)).ToString().c_str(), filter);
        json->PutExtAttr("arrowPosition",
            GetArrowPosition().value_or(OffsetF(0.0f, 0.0f)).ToString().c_str(), filter);
        json->PutExtAttr("arrowPlacement",
            ConvertPlacementToString(GetArrowPlacement().value_or(Placement::NONE)).c_str(), filter);
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(EnableArrow, bool, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ArrowOffset, Dimension, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ArrowPosition, OffsetF, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ArrowPlacement, Placement, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ClipPath, std::string, PROPERTY_UPDATE_RENDER);
    ACE_DISALLOW_COPY_AND_MOVE(MenuPaintProperty);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_MENU_PAINT_PROPERTY_H
