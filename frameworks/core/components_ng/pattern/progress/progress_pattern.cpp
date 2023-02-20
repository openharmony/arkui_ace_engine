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

#include "core/components_ng/pattern/progress/progress_pattern.h"

#include "core/components_ng/pattern/progress/progress_layout_algorithm.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace::NG {
bool ProgressPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (config.skipMeasure || dirty->SkipMeasureContent()) {
        return false;
    }
    auto layoutAlgorithmWrapper = DynamicCast<LayoutAlgorithmWrapper>(dirty->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, false);
    auto progressLayoutAlgorithm = DynamicCast<ProgressLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(progressLayoutAlgorithm, false);
    strokeWidth_ = progressLayoutAlgorithm->GetStrokeWidth();
    return true;
}

void ProgressPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->GetRenderContext()->SetClipToFrame(true);
}

void ProgressPattern::ToJsonValue(std::unique_ptr<JsonValue>& json) const
{
    auto layoutProperty = GetLayoutProperty<ProgressLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto paintProperty = GetPaintProperty<ProgressPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<ProgressTheme>();
    CHECK_NULL_VOID(theme);
    auto jsonValue = JsonUtil::Create(true);
    auto progressStyle = layoutProperty->GetTypeValue(ProgressType::LINEAR);
    jsonValue->Put("strokeWidth",
        layoutProperty->GetStrokeWidthValue(
            progressStyle == ProgressType::LINEAR ?
                theme->GetTrackThickness() :
                theme->GetScaleLength())
        .ToString().c_str());
    jsonValue->Put("scaleCount", std::to_string(paintProperty->GetScaleCountValue(theme->GetScaleNumber())).c_str());
    jsonValue->Put("scaleWidth", paintProperty->GetScaleWidthValue(theme->GetScaleWidth()).ToString().c_str());
    json->Put("style", jsonValue->ToString().c_str());
}
} // namespace OHOS::Ace::NG
