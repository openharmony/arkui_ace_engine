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

#include "core/components_ng/pattern/custom_node_ext/custom_node_ext_pattern.h"

namespace OHOS::Ace::NG {

RefPtr<NodePaintMethod> CustomNodeExtPattern::CreateNodePaintMethod()
{
    auto paintMethod = AceType::MakeRefPtr<CustomNodeExtPaintMethod>(
        contentModifier_, foregroundModifier_, overlayModifier_);
    return paintMethod;
}

void CustomNodeExtPattern::SetMeasureCallback(std::function<void(LayoutConstraintF constraints)>&& onMeasure)
{
    measureCallback_ = std::move(onMeasure);
    auto host = GetHost();
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void CustomNodeExtPattern::SetLayoutCallback(std::function<void(RectF rect)>&& onLayout)
{
    layoutCallback_ = std::move(onLayout);
    auto host = GetHost();
    host->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
}

void CustomNodeExtPattern::SetContentDrawCallback(DrawFunction&& onContent)
{
    contentModifier_ = AceType::MakeRefPtr<CustomNodeExtContentModifier>(std::move(onContent));
    auto host = GetHost();
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CustomNodeExtPattern::SetForegroundDrawCallback(DrawFunction&& onForeground)
{
    foregroundModifier_ = AceType::MakeRefPtr<CustomNodeExtForegroundModifier>(std::move(onForeground));
    auto host = GetHost();
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CustomNodeExtPattern::SetOverlayDrawCallback(DrawFunction&& onOverlay)
{
    overlayModifier_ = AceType::MakeRefPtr<CustomNodeExtOverlayModifier>(std::move(onOverlay));
    auto host = GetHost();
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CustomNodeExtPattern::OnModifyDone()
{
    if (onModifyDoneCallback_) {
        onModifyDoneCallback_();
    }
}

bool CustomNodeExtPattern::OnDirtyLayoutWrapperSwap(
    const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (onDirtySwap_) {
        onDirtySwap_(config);
        return true;
    }
    return false;
}

void CustomNodeExtPattern::OnLanguageConfigurationUpdate()
{
    if (onConfigUpdate_) {
        onConfigUpdate_(ConfigurationType::LANGUAGE_UPDATE);
    }
}

void CustomNodeExtPattern::OnColorConfigurationUpdate()
{
    if (onConfigUpdate_) {
        onConfigUpdate_(ConfigurationType::COLOR_MODE_UPDATE);
    }
}

void CustomNodeExtPattern::OnDirectionConfigurationUpdate()
{
    if (onConfigUpdate_) {
        onConfigUpdate_(ConfigurationType::DIRECTION_UPDATE);
    }
}

void CustomNodeExtPattern::OnDpiConfigurationUpdate()
{
    if (onConfigUpdate_) {
        onConfigUpdate_(ConfigurationType::DPI_UPDATE);
    }
}

void CustomNodeExtPattern::OnIconConfigurationUpdate()
{
    if (onConfigUpdate_) {
        onConfigUpdate_(ConfigurationType::ICON_UPDATE);
    }
}

void CustomNodeExtPattern::OnFontConfigurationUpdate()
{
    if (onConfigUpdate_) {
        onConfigUpdate_(ConfigurationType::FONT_UPDATE);
    }
}

void CustomNodeExtPattern::OnFontScaleConfigurationUpdate()
{
    if (onConfigUpdate_) {
        onConfigUpdate_(ConfigurationType::FONT_SCALE_UPDATE);
    }
}
} // OHOS::Ace::NG