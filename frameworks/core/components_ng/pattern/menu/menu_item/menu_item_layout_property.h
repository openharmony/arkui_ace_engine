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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MENU_MENU_ITEM_LAYOUT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MENU_MENU_ITEM_LAYOUT_PROPERTY_H

#include <string>

#include "base/utils/utils.h"
#include "core/components/select/select_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/menu/menu_layout_property.h"
#include "core/components_ng/property/property.h"
#include "core/components_v2/inspector/utils.h"
#include "core/pipeline/pipeline_base.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
struct MenuItemLabelFontStyle {
    ACE_DEFINE_PROPERTY_GROUP_ITEM(LabelFontSize, Dimension);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(LabelFontColor, Color);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(LabelFontWeight, FontWeight);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(LabelFontFamily, std::vector<std::string>);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(LabelItalicFontStyle, Ace::FontStyle);
};

struct MenuItemSelectIconStyle {
    ACE_DEFINE_PROPERTY_GROUP_ITEM(SelectIcon, bool);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(SelectIconSrc, std::string);
};

class ACE_EXPORT MenuItemLayoutProperty : public LayoutProperty {
    DECLARE_ACE_TYPE(MenuItemLayoutProperty, LayoutProperty);

private:
    std::function<void(WeakPtr<NG::FrameNode>)> startSymbol_;
    std::function<void(WeakPtr<NG::FrameNode>)> endSymbol_;
    std::function<void(WeakPtr<NG::FrameNode>)> selectSymbol_;

public:
    MenuItemLayoutProperty() = default;
    ~MenuItemLayoutProperty() override = default;

    RefPtr<LayoutProperty> Clone() const override
    {
        auto value = MakeRefPtr<MenuItemLayoutProperty>();
        value->LayoutProperty::UpdateLayoutProperty(DynamicCast<LayoutProperty>(this));
        value->propFontStyle_ = CloneFontStyle();
        value->propLabelFontStyle_ = CloneLabelFontStyle();
        value->propStartIcon_ = CloneStartIcon();
        value->propContent_ = CloneContent();
        value->propEndIcon_ = CloneEndIcon();
        value->propLabel_ = CloneLabel();
        value->propSelectIconStyle_ = CloneSelectIconStyle();
        value->propMenuWidth_ = CloneMenuWidth();
        return value;
    }

    void Reset() override
    {
        LayoutProperty::Reset();
        ResetFontStyle();
        ResetLabelFontStyle();
        ResetStartIcon();
        ResetContent();
        ResetEndIcon();
        ResetLabel();
        ResetSelectIconStyle();
        ResetMenuWidth();
    }

    std::function<void(WeakPtr<NG::FrameNode>)>& GetStartSymbol()
    {
        return startSymbol_;
    }

    void SetStartSymbol(const std::function<void(WeakPtr<NG::FrameNode>)>& symbol)
    {
        startSymbol_ = symbol;
    }

    std::function<void(WeakPtr<NG::FrameNode>)>& GetEndSymbol()
    {
        return endSymbol_;
    }

    void SetEndSymbol(const std::function<void(WeakPtr<NG::FrameNode>)>& symbol)
    {
        endSymbol_ = symbol;
    }

    std::function<void(WeakPtr<NG::FrameNode>)>& GetSelectSymbol()
    {
        return selectSymbol_;
    }

    void SetSelectSymbol(const std::function<void(WeakPtr<NG::FrameNode>)>& symbol)
    {
        selectSymbol_ = symbol;
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(StartIcon, ImageSourceInfo, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Content, std::string, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(EndIcon, ImageSourceInfo, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Label, std::string, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(MenuWidth, Dimension, PROPERTY_UPDATE_MEASURE);

    ACE_DEFINE_PROPERTY_GROUP(SelectIconStyle, MenuItemSelectIconStyle);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SelectIconStyle, SelectIcon, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SelectIconStyle, SelectIconSrc, std::string, PROPERTY_UPDATE_MEASURE);

    ACE_DEFINE_PROPERTY_GROUP(FontStyle, MenuItemFontStyle);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(FontStyle, FontSize, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(FontStyle, FontColor, Color, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(FontStyle, FontWeight, FontWeight, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(FontStyle, FontFamily, std::vector<std::string>, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(FontStyle, ItalicFontStyle, Ace::FontStyle, PROPERTY_UPDATE_MEASURE);

    ACE_DEFINE_PROPERTY_GROUP(LabelFontStyle, MenuItemLabelFontStyle);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(LabelFontStyle, LabelFontSize, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(LabelFontStyle, LabelFontColor, Color, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(LabelFontStyle, LabelFontWeight, FontWeight, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(LabelFontStyle, LabelFontFamily, std::vector<std::string>,
        PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(LabelFontStyle, LabelItalicFontStyle, Ace::FontStyle, PROPERTY_UPDATE_MEASURE);

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override
    {
        LayoutProperty::ToJsonValue(json, filter);
        if (filter.IsFastFilter()) {
            json->PutFixedAttr("content", GetContent().value_or("").c_str(), filter, FIXED_ATTR_CONTENT);
            return;
        }
        if (GetStartIcon().has_value()) {
            json->PutExtAttr("startIcon", GetStartIcon()->GetSrc().c_str(), filter);
        }
        json->PutFixedAttr("content", GetContent().value_or("").c_str(), filter, FIXED_ATTR_CONTENT);
        json->PutExtAttr("labelInfo", GetLabel().value_or("").c_str(), filter);
        if (GetEndIcon().has_value()) {
            json->PutExtAttr("endIcon", GetEndIcon()->GetSrc().c_str(), filter);
        }
        auto selectIconShow = GetSelectIcon().value_or(false);
        auto selectIconSrc = GetSelectIconSrc().value_or("");
        if (selectIconShow) {
            json->PutExtAttr("selectIcon", selectIconSrc.empty() ? "true" : selectIconSrc.c_str(), filter);
        } else {
            json->PutExtAttr("selectIcon", "false", filter);
        }
        auto context = PipelineBase::GetCurrentContext();
        auto theme = context ? context->GetTheme<SelectTheme>() : nullptr;
        auto defaultFontSize = theme ? theme->GetMenuFontSize() : Dimension(0, DimensionUnit::FP);
        auto defaultFontColor = theme ? theme->GetMenuFontColor() : Color::BLACK;
        auto contentFontJsonObject = JsonUtil::Create(true);
        contentFontJsonObject->Put("size", GetFontSize().value_or(defaultFontSize).ToString().c_str());
        contentFontJsonObject->Put("weight",
            V2::ConvertWrapFontWeightToStirng(GetFontWeight().value_or(FontWeight::REGULAR)).c_str());
        contentFontJsonObject->Put("style",
            V2::ConvertWrapFontStyleToStirng(GetItalicFontStyle().value_or(Ace::FontStyle::NORMAL)).c_str());
        contentFontJsonObject->Put("family", V2::ConvertFontFamily(GetFontFamilyValue({})).c_str());
        json->PutExtAttr("contentFont", contentFontJsonObject, filter);
        json->PutExtAttr("contentFontColor",
            GetFontColor().value_or(defaultFontColor).ColorToString().c_str(), filter);
        auto labelFontJsonObject = JsonUtil::Create(true);
        labelFontJsonObject->Put("size", GetLabelFontSize().value_or(defaultFontSize).ToString().c_str());
        labelFontJsonObject->Put("weight",
            V2::ConvertWrapFontWeightToStirng(GetLabelFontWeight().value_or(FontWeight::REGULAR)).c_str());
        labelFontJsonObject->Put("style",
            V2::ConvertWrapFontStyleToStirng(GetLabelItalicFontStyle().value_or(Ace::FontStyle::NORMAL)).c_str());
        labelFontJsonObject->Put("family", V2::ConvertFontFamily(GetLabelFontFamilyValue({})).c_str());
        json->PutExtAttr("labelFont", labelFontJsonObject, filter);
        auto defaultLabelFontColor = theme ? theme->GetSecondaryFontColor() : Color::GRAY;
        json->PutExtAttr("labelFontColor",
            GetLabelFontColor().value_or(defaultLabelFontColor).ColorToString().c_str(), filter);
        json->PutFixedAttr("label", GetContent().value_or("").c_str(), filter, FIXED_ATTR_CONTENT);
    }

    void ToTreeJson(std::unique_ptr<JsonValue>& json, const InspectorConfig& config) const override
    {
        LayoutProperty::ToTreeJson(json, config);
        json->Put(TreeKey::CONTENT, GetContent().value_or("").c_str());
    }

    ACE_DISALLOW_COPY_AND_MOVE(MenuItemLayoutProperty);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MENU_MENU_ITEM_LAYOUT_PROPERTY_H
