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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_INDEXER_INDEXER_PAINT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_INDEXER_INDEXER_PAINT_PROPERTY_H

#include "core/components/common/properties/color.h"
#include "core/components/common/properties/decoration.h"
#include "core/components/indexer/indexer_theme.h"
#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/pattern/indexer/indexer_theme.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/render/paint_property.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT IndexerPaintProperty : public PaintProperty {
    DECLARE_ACE_TYPE(IndexerPaintProperty, PaintProperty);

public:
    IndexerPaintProperty() = default;

    ~IndexerPaintProperty() override = default;

    RefPtr<PaintProperty> Clone() const override
    {
        auto value = MakeRefPtr<IndexerPaintProperty>();
        value->PaintProperty::UpdatePaintProperty(DynamicCast<PaintProperty>(this));
        value->propSelectedBackgroundColor_ = CloneSelectedBackgroundColor();
        value->propPopupBackground_ = ClonePopupBackground();
        value->propPopupSelectedColor_ = ClonePopupSelectedColor();
        value->propPopupUnselectedColor_ = ClonePopupUnselectedColor();
        value->propPopupItemBackground_ = ClonePopupItemBackground();
        value->propPopupBorderRadius_ = ClonePopupBorderRadius();
        value->propPopupItemBorderRadius_ = ClonePopupItemBorderRadius();
        value->propItemBorderRadius_ = CloneItemBorderRadius();
        value->propIndexerBorderRadius_ = CloneIndexerBorderRadius();
        value->propPopupBackgroundBlurStyle_ = ClonePopupBackgroundBlurStyle();
        value->propPopupTitleBackground_ = ClonePopupTitleBackground();

        return value;
    }

    void Reset() override
    {
        PaintProperty::Reset();
        ResetSelectedBackgroundColor();
        ResetPopupBackground();
        ResetPopupSelectedColor();
        ResetPopupUnselectedColor();
        ResetPopupItemBackground();
        ResetPopupBorderRadius();
        ResetPopupItemBorderRadius();
        ResetItemBorderRadius();
        ResetIndexerBorderRadius();
        ResetPopupBackgroundBlurStyle();
        ResetPopupTitleBackground();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override
    {
        PaintProperty::ToJsonValue(json, filter);
        /* no fixed attr below, just return */
        if (filter.IsFastFilter()) {
            return;
        }
        json->PutExtAttr("selectedBackgroundColor",
            propSelectedBackgroundColor_.value_or(Color::WHITE).ColorToString().c_str(), filter);
        json->PutExtAttr("popupBackground",
            propPopupBackground_.value_or(Color::WHITE).ColorToString().c_str(), filter);
        auto pipeline = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto indexerTheme = pipeline->GetTheme<IndexerTheme>();
        CHECK_NULL_VOID(indexerTheme);
        json->PutExtAttr("popupSelectedColor", propPopupSelectedColor_.
            value_or(indexerTheme->GetPopupSelectedTextColor()).ColorToString().c_str(), filter);
        json->PutExtAttr("popupUnselectedColor", propPopupUnselectedColor_.
            value_or(indexerTheme->GetPopupUnselectedTextColor()).ColorToString().c_str(), filter);
        json->PutExtAttr("popupItemBackground", propPopupItemBackground_.
            value_or(indexerTheme->GetPopupBackgroundColor()).ColorToString().c_str(), filter);
        BorderRadiusToJsonValue(json, filter);
        BlurStyleOption blurStyleOption;
        if (propPopupBackgroundBlurStyle_.has_value()) {
            blurStyleOption = propPopupBackgroundBlurStyle_.value();
        } else {
            blurStyleOption.blurStyle = BlurStyle::COMPONENT_REGULAR;
        }
        auto jsonValue = JsonUtil::Create(true);
        blurStyleOption.ToJsonValue(jsonValue, filter);
        json->PutExtAttr("popupBackgroundBlurStyle",
            jsonValue->GetValue("backgroundBlurStyle")->GetValue("value"), filter);
        json->PutExtAttr("popupTitleBackground", propPopupTitleBackground_.
            value_or(indexerTheme->GetPopupTitleBackground()).ColorToString().c_str(), filter);
    }

    void BorderRadiusToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
    {
        if (propPopupBorderRadius_.has_value()) {
            json->PutExtAttr("popupBorderRadius", propPopupBorderRadius_.value().ToString().c_str(), filter);
        } else {
            json->PutExtAttr("popupBorderRadius",
                Dimension(NG::BUBBLE_RADIUS, DimensionUnit::VP).ToString().c_str(), filter);
        }
        if (propPopupItemBorderRadius_.has_value()) {
            json->PutExtAttr("popupItemBorderRadius",
                propPopupItemBorderRadius_.value().ToString().c_str(), filter);
        } else {
            json->PutExtAttr("popupItemBorderRadius",
                Dimension(NG::BUBBLE_ITEM_RADIUS, DimensionUnit::VP).ToString().c_str(), filter);
        }
        if (propItemBorderRadius_.has_value()) {
            json->PutExtAttr("itemBorderRadius", propItemBorderRadius_.value().ToString().c_str(), filter);
        } else {
            json->PutExtAttr("itemBorderRadius",
                Dimension(NG::INDEXER_ITEM_DEFAULT_RADIUS, DimensionUnit::VP).ToString().c_str(), filter);
        }
        if (propIndexerBorderRadius_.has_value()) {
            json->PutExtAttr("indexerBorderRadius", propIndexerBorderRadius_.value().ToString().c_str(), filter);
        } else {
            json->PutExtAttr("indexerBorderRadius",
                Dimension(NG::INDEXER_DEFAULT_RADIUS, DimensionUnit::VP).ToString().c_str(), filter);
        }
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(PopupSelectedColor, Color, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(PopupUnselectedColor, Color, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(SelectedBackgroundColor, Color, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(PopupBackground, Color, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(PopupItemBackground, Color, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(PopupBorderRadius, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(PopupItemBorderRadius, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ItemBorderRadius, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(IndexerBorderRadius, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(PopupBackgroundBlurStyle, BlurStyleOption, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(PopupTitleBackground, Color, PROPERTY_UPDATE_RENDER);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_INDEXER_INDEXER_PAINT_PROPERTY_H
