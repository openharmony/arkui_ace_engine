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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_INDEXER_ARC_INDEXER_PAINT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_INDEXER_ARC_INDEXER_PAINT_PROPERTY_H

#include "core/components_ng/pattern/indexer/indexer_paint_property.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT ArcIndexerPaintProperty : public IndexerPaintProperty {
    DECLARE_ACE_TYPE(ArcIndexerPaintProperty, IndexerPaintProperty);

public:
    ArcIndexerPaintProperty() = default;

    ~ArcIndexerPaintProperty() override = default;

    RefPtr<PaintProperty> Clone() const override
    {
        auto value = MakeRefPtr<ArcIndexerPaintProperty>();
        value->IndexerPaintProperty::UpdateLayoutProperty(DynamicCast<IndexerPaintProperty>(this));
        return value;
    }

    void Reset() override
    {
        IndexerPaintProperty::Reset();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override
    {
        PaintProperty::ToJsonValue(json, filter);
        /* no fixed attr below, just return */
        if (filter.IsFastFilter()) {
            return;
        }
        json->PutExtAttr("selectedBackgroundColor",
        propSelectedBackgroundColor_.value_or(Color(ARC_INDEXER_SELECTED_BG_COLOR)).ColorToString().c_str(), filter);
        json->PutExtAttr("popupBackground",
            propPopupBackground_.value_or(Color(ARC_POPUP_BG_COLOR)).ColorToString().c_str(), filter);
        auto pipeline = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto indexerTheme = pipeline->GetTheme<IndexerTheme>();
        CHECK_NULL_VOID(indexerTheme);
        if (propPopupBorderRadius_.has_value()) {
            json->PutExtAttr("popupBorderRadius", propPopupBorderRadius_.value().ToString().c_str(), filter);
        } else {
            json->PutExtAttr("popupBorderRadius",
                Dimension(ARC_BUBBLE_BOX_RADIUS, DimensionUnit::VP).ToString().c_str(), filter);
        }
        if (propItemBorderRadius_.has_value()) {
            json->PutExtAttr("itemBorderRadius", propItemBorderRadius_.value().ToString().c_str(), filter);
        } else {
            json->PutExtAttr("itemBorderRadius",
                Dimension(ARC_INDEXER_DEFAULT_RADIUS, DimensionUnit::VP).ToString().c_str(), filter);
        }
        if (propIndexerBorderRadius_.has_value()) {
            json->PutExtAttr("indexerBorderRadius", propIndexerBorderRadius_.value().ToString().c_str(), filter);
        } else {
            json->PutExtAttr("indexerBorderRadius",
                Dimension(ARC_INDEXER_DEFAULT_RADIUS, DimensionUnit::VP).ToString().c_str(), filter);
        }
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
    }
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_INDEXER_INDEXER_PAINT_PROPERTY_H
