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
#include "core/components/indexer/indexer_theme.h"
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
        value->propPopupHorizontalSpace_ = ClonePopupHorizontalSpace();

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
        ResetPopupHorizontalSpace();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json) const override
    {
        PaintProperty::ToJsonValue(json);
        json->Put(
            "selectedBackgroundColor", propSelectedBackgroundColor_.value_or(Color::WHITE).ColorToString().c_str());
        json->Put("popupBackground", propPopupBackground_.value_or(Color::WHITE).ColorToString().c_str());
        auto pipeline = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto indexerTheme = pipeline->GetTheme<IndexerTheme>();
        CHECK_NULL_VOID(indexerTheme);
        json->Put("popupSelectedColor",
            propPopupSelectedColor_.value_or(indexerTheme->GetPopupSelectedTextColor()).ColorToString().c_str());
        json->Put("popupUnselectedColor",
            propPopupUnselectedColor_.value_or(indexerTheme->GetPopupUnselectedTextColor()).ColorToString().c_str());
        json->Put("popupItemBackground",
            propPopupItemBackground_.value_or(indexerTheme->GetPopupBackgroundColor()).ColorToString().c_str());
        json->Put("popupHorizontalSpace", propPopupHorizontalSpace_.value_or(
            Dimension(NG::INDEXER_BUBBLE_INVALID_SPACE, DimensionUnit::VP)).ToString().c_str());
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(PopupSelectedColor, Color, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(PopupUnselectedColor, Color, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(SelectedBackgroundColor, Color, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(PopupBackground, Color, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(PopupItemBackground, Color, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(PopupHorizontalSpace, Dimension, PROPERTY_UPDATE_RENDER);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_INDEXER_INDEXER_PAINT_PROPERTY_H
