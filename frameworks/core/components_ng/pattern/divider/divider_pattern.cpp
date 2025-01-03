/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "base/log/dump_log.h"
#include "core/components_ng/pattern/divider/divider_pattern.h"

namespace OHOS::Ace::NG {
bool DividerPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (config.skipMeasure || dirty->SkipMeasureContent()) {
        return false;
    }
    auto layoutAlgorithmWrapper = DynamicCast<LayoutAlgorithmWrapper>(dirty->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, false);
    auto dividerLayoutAlgorithm = DynamicCast<DividerLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(dividerLayoutAlgorithm, false);
    constrainStrokeWidth_ = dividerLayoutAlgorithm->GetConstrainStrokeWidth();
    dividerLength_ = dividerLayoutAlgorithm->GetDividerLength();
    vertical_ = dividerLayoutAlgorithm->GetVertical();
    strokeWidthLimitation_ = dividerLayoutAlgorithm->GetStrokeWidthLimitation();
    return true;
}

bool DividerPattern::OnThemeScopeUpdate(int32_t themeScopeId)
{
    bool result = false;
    auto host = GetHost();
    CHECK_NULL_RETURN(host, result);
    auto paintProperty = host->GetPaintProperty<DividerRenderProperty>();
    CHECK_NULL_RETURN(paintProperty, result);
    return !paintProperty->HasDividerColor();
}

std::string DividerPattern::DumpDividerColor()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, "NA");
    auto pipelineContext = host->GetContext();
    CHECK_NULL_RETURN(pipelineContext, "NA");
    auto theme = pipelineContext->GetTheme<DividerTheme>(host->GetThemeScopeId());
    CHECK_NULL_RETURN(theme, "NA");
    auto paintProperty = host->GetPaintProperty<DividerRenderProperty>();
    CHECK_NULL_RETURN(paintProperty, "NA");
    return paintProperty->GetDividerColorValue(theme->GetColor()).ColorToString();
}

void DividerPattern::DumpInfo()
{
    DumpLog::GetInstance().AddDesc(std::string("DividerColor: ").append(DumpDividerColor().c_str()));
}

void DividerPattern::DumpInfo(std::unique_ptr<JsonValue>& json)
{
    json->Put("DividerColor: ", DumpDividerColor().c_str());
}
} // namespace OHOS::Ace::NG
