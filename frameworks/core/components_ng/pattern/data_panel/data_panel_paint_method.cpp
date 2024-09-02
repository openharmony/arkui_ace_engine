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

#include "core/components_ng/pattern/data_panel/data_panel_paint_method.h"

namespace OHOS::Ace::NG {

RefPtr<Modifier> DataPanelPaintMethod::GetContentModifier(PaintWrapper* paintWrapper)
{
    CHECK_NULL_RETURN(dataPanelModifier_, nullptr);
    return dataPanelModifier_;
}

void DataPanelPaintMethod::UpdateContentModifier(PaintWrapper* paintWrapper)
{
    CHECK_NULL_VOID(dataPanelModifier_);
    auto paintProperty = DynamicCast<DataPanelPaintProperty>(paintWrapper->GetPaintProperty());
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto theme = pipelineContext->GetTheme<DataPanelTheme>();

    auto values_ = paintProperty->GetValues().value();
    auto max_ = paintProperty->GetMax().value_or(DEFAULT_MAX_VALUE);
    auto dataPanelType_ = paintProperty->GetDataPanelType().value_or(0);
    auto effect_ = paintProperty->GetEffect().value_or(true);
    auto offset_ = paintWrapper->GetContentOffset();
    auto trackBackgroundColor = paintProperty->GetTrackBackground().value_or(theme->GetBackgroundColor());
    auto strokeWidth = paintProperty->GetStrokeWidth().value_or(theme->GetThickness()).ConvertToPx();

    std::vector<Gradient> valuesColor;
    if (paintProperty->HasValueColors()) {
        valuesColor = paintProperty->GetValueColorsValue();
    } else {
        auto colors = theme->GetColorsArray();
        for (const auto& item : colors) {
            Gradient gradient;
            CreateGradient(item, gradient);
            valuesColor.emplace_back(gradient);
        }
    }

    DataPanelShadow shadowOption;
    bool isHasShadowValue = false;
    if (paintProperty->HasShadowOption()) {
        isHasShadowValue = true;
        shadowOption = paintProperty->GetShadowOptionValue();
    }

    size_t shadowColorsLastLength = MAX_COUNT;
    if (shadowOption.colors.size() == 0) {
        shadowOption.colors = valuesColor;
    } else {
        shadowColorsLastLength = shadowOption.colors.size();
    }

    dataPanelModifier_->SetValues(values_);
    dataPanelModifier_->SetMax(max_);
    dataPanelModifier_->SetDataPanelType(dataPanelType_);
    dataPanelModifier_->SetEffect(effect_);
    dataPanelModifier_->SetOffset(offset_);

    dataPanelModifier_->SetValueColors(valuesColor);
    dataPanelModifier_->SetTrackBackground(trackBackgroundColor);
    dataPanelModifier_->SetStrokeWidth(strokeWidth);
    dataPanelModifier_->SetIsHasShadowValue(isHasShadowValue);
    dataPanelModifier_->SetShadowVisible(shadowOption.isShadowVisible);
    dataPanelModifier_->SetShadowRadius(shadowOption.radius);
    dataPanelModifier_->SetShadowOffsetX(shadowOption.offsetX);
    dataPanelModifier_->SetShadowOffsetY(shadowOption.offsetY);
    dataPanelModifier_->SetShadowColors(shadowOption.colors, shadowColorsLastLength);
    dataPanelModifier_->UpdateDate();
}

void DataPanelPaintMethod::CreateGradient(const std::pair<Color, Color>& itemParam, Gradient& gradient) const
{
    GradientColor gradientColorStart;
    gradientColorStart.SetLinearColor(LinearColor(itemParam.first));
    gradientColorStart.SetDimension(Dimension(0.0));
    gradient.AddColor(gradientColorStart);
    GradientColor gradientColorEnd;
    gradientColorEnd.SetLinearColor(LinearColor(itemParam.second));
    gradientColorEnd.SetDimension(Dimension(1.0));
    gradient.AddColor(gradientColorEnd);
}

} // namespace OHOS::Ace::NG
