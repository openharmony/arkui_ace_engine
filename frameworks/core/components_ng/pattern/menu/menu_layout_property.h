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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MENU_MENU_LAYOUT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MENU_MENU_LAYOUT_PROPERTY_H

#include <string>

#include "base/utils/utils.h"
#include "core/components/select/select_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/select/select_pattern.h"
#include "core/components_ng/property/property.h"
#include "core/components_v2/inspector/utils.h"
#include "core/components_v2/list/list_properties.h"
#include "core/pipeline/pipeline_base.h"
#include "core/pipeline_ng/pipeline_context.h"
namespace OHOS::Ace::NG {
class InspectorFilter;

enum class SubMenuExpandingMode { SIDE, EMBEDDED, STACK };

struct MenuItemFontStyle {
    ACE_DEFINE_PROPERTY_GROUP_ITEM(FontSize, Dimension);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(FontColor, Color);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(FontWeight, FontWeight);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(FontFamily, std::vector<std::string>);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(ItalicFontStyle, Ace::FontStyle);
};

struct SelectMenuAlignOption {
    ACE_DEFINE_PROPERTY_GROUP_ITEM(AlignType, MenuAlignType);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(Offset, DimensionOffset);
};

class ACE_EXPORT MenuLayoutProperty : public LayoutProperty {
    DECLARE_ACE_TYPE(MenuLayoutProperty, LayoutProperty);

public:
    MenuLayoutProperty() = default;

    ~MenuLayoutProperty() override = default;

    RefPtr<LayoutProperty> Clone() const override
    {
        auto value = MakeRefPtr<MenuLayoutProperty>();
        value->LayoutProperty::UpdateLayoutProperty(DynamicCast<LayoutProperty>(this));
        value->propIsRectInTarget_ = CloneIsRectInTarget();
        value->propMenuOffset_ = CloneMenuOffset();
        value->propTargetSize_ = CloneTargetSize();
        value->propPositionOffset_ = ClonePositionOffset();
        value->propMenuItemFontStyle_ = CloneMenuItemFontStyle();
        value->propTitle_ = CloneTitle();
        value->propMenuPlacement_ = CloneMenuPlacement();
        value->propSelectMenuAlignOption_ = CloneSelectMenuAlignOption();
        value->propBorderRadius_ = CloneBorderRadius();
        value->propMenuWidth_ = CloneMenuWidth();
        value->propShowInSubWindow_ = CloneShowInSubWindow();
        value->propExpandingMode_ = CloneExpandingMode();
        value->propItemDivider_ = CloneItemDivider();
        value->propItemGroupDivider_ = CloneItemGroupDivider();
        return value;
    }

    void Reset() override
    {
        LayoutProperty::Reset();
        ResetIsRectInTarget();
        ResetMenuOffset();
        ResetTargetSize();
        ResetPositionOffset();
        ResetMenuItemFontStyle();
        ResetTitle();
        ResetMenuPlacement();
        ResetSelectMenuAlignOption();
        ResetBorderRadius();
        ResetMenuWidth();
        ResetShowInSubWindow();
        ResetExpandingMode();
        ResetItemDivider();
        ResetItemGroupDivider();
    }

    // if is a rect in target frameNode
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(IsRectInTarget, bool, PROPERTY_UPDATE_MEASURE);
    // target frameNode that this menu belongs to
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(MenuOffset, NG::OffsetF, PROPERTY_UPDATE_MEASURE);
    // target frameNode size, null for click show menu
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(TargetSize, NG::SizeF, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(BorderRadius, NG::BorderRadiusProperty, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(MenuWidth, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ItemDivider, V2::ItemDivider, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ItemDividerMode, DividerMode, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ItemGroupDivider, V2::ItemDivider, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ItemGroupDividerMode, DividerMode, PROPERTY_UPDATE_MEASURE);

    // offset to cursor
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(PositionOffset, NG::OffsetF, PROPERTY_UPDATE_LAYOUT);

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Title, std::string, PROPERTY_UPDATE_LAYOUT);

    // placement to menu
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(MenuPlacement, Placement, PROPERTY_UPDATE_LAYOUT);
    
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(SelectMenuModifiedWidth, float, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(SelectModifiedHeight, float, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_GROUP(MenuItemFontStyle, MenuItemFontStyle);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(MenuItemFontStyle, FontSize, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(MenuItemFontStyle, FontColor, Color, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(MenuItemFontStyle, FontWeight, FontWeight, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(MenuItemFontStyle, FontFamily,
        std::vector<std::string>, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(MenuItemFontStyle, ItalicFontStyle, Ace::FontStyle, PROPERTY_UPDATE_MEASURE);

    ACE_DEFINE_PROPERTY_GROUP(SelectMenuAlignOption, SelectMenuAlignOption);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SelectMenuAlignOption, AlignType, MenuAlignType, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SelectMenuAlignOption, Offset, DimensionOffset, PROPERTY_UPDATE_MEASURE);

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ShowInSubWindow, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ExpandingMode, SubMenuExpandingMode, PROPERTY_UPDATE_MEASURE)

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override;
    void BindToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const;
    void DividerToJsonValue(std::unique_ptr<JsonValue>& json) const;
    ACE_DISALLOW_COPY_AND_MOVE(MenuLayoutProperty);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MENU_MENU_LAYOUT_PROPERTY_H
