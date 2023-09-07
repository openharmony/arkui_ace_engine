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

#include "core/components_ng/pattern/video/video_layout_algorithm.h"

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/utils/utils.h"
#include "core/components/video/video_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/video/video_layout_property.h"
#include "core/components_ng/pattern/video/video_pattern.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
float CalControlBarHeight()
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, 0.0f);
    auto videoTheme = pipelineContext->GetTheme<VideoTheme>();
    CHECK_NULL_RETURN(videoTheme, 0.0f);
    auto controlsHeight =
        pipelineContext->NormalizeToPx(Dimension(videoTheme->GetBtnSize().Height(), DimensionUnit::VP));
    controlsHeight += pipelineContext->NormalizeToPx(videoTheme->GetBtnEdge().Top());
    controlsHeight += pipelineContext->NormalizeToPx(videoTheme->GetBtnEdge().Bottom());
    return static_cast<float>(controlsHeight);
}
} // namespace
VideoLayoutAlgorithm::VideoLayoutAlgorithm() = default;

void VideoLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    BoxLayoutAlgorithm::PerformLayout(layoutWrapper);
    auto contentOffset = layoutWrapper->GetGeometryNode()->GetContentOffset();
    for (auto&& child : layoutWrapper->GetAllChildrenWithBuild()) {
        if (child->GetHostTag() == V2::IMAGE_ETS_TAG) {
            child->GetGeometryNode()->SetMarginFrameOffset({ contentOffset.GetX(), contentOffset.GetY() });
        } else if (child->GetHostTag() == V2::ROW_ETS_TAG) {
            auto controlBarHeight = CalControlBarHeight();
            auto contentSize = layoutWrapper->GetGeometryNode()->GetContentSize();
            child->GetGeometryNode()->SetMarginFrameOffset(
                { contentOffset.GetX(), contentOffset.GetY() + contentSize.Height() - controlBarHeight });
        } else if (child->GetHostTag() == V2::COLUMN_ETS_TAG) {
            child->GetGeometryNode()->SetMarginFrameOffset(OffsetF { contentOffset.GetX(), contentOffset.GetY() });
        }
        child->Layout();
    }
}

void VideoLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    auto layoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    auto contentSize = layoutWrapper->GetGeometryNode()->GetContentSize();
    auto layoutProperty = DynamicCast<VideoLayoutProperty>(layoutWrapper->GetLayoutProperty());
    for (auto&& child : layoutWrapper->GetAllChildrenWithBuild()) {
        if (child->GetHostTag() == V2::IMAGE_ETS_TAG) {
            auto layoutConstraintForImage = layoutConstraint;
            layoutConstraintForImage.UpdateSelfMarginSizeWithCheck(OptionalSizeF(contentSize));
            layoutConstraintForImage.UpdateMaxSizeWithCheck(contentSize);
            layoutConstraintForImage.UpdateMinSizeWithCheck(contentSize);
            child->Measure(layoutConstraintForImage);
        } else if (child->GetHostTag() == V2::ROW_ETS_TAG && layoutProperty->GetControlsValue(true)) {
            auto controlBarHeight = CalControlBarHeight();
            SizeF controlBarSize(contentSize.Width(), controlBarHeight);
            auto layoutConstraintForControlBar = layoutConstraint;
            layoutConstraintForControlBar.UpdateSelfMarginSizeWithCheck(OptionalSizeF(controlBarSize));
            layoutConstraintForControlBar.UpdateMaxSizeWithCheck(controlBarSize);
            layoutConstraintForControlBar.UpdateMinSizeWithCheck(controlBarSize);
            child->Measure(layoutConstraintForControlBar);
        } else if (child->GetHostTag() == V2::COLUMN_ETS_TAG) {
            auto layoutConstraintForImage = layoutConstraint;
            layoutConstraintForImage.UpdateSelfMarginSizeWithCheck(OptionalSizeF(contentSize));
            layoutConstraintForImage.UpdateMaxSizeWithCheck(contentSize);
            layoutConstraintForImage.UpdateMinSizeWithCheck(contentSize);
            child->Measure(layoutConstraintForImage);
        }
    }

    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto pattern = DynamicCast<VideoPattern>(host->GetPattern());
    CHECK_NULL_VOID(pattern);
    if (pattern->IsFullScreen()) {
        SizeF fullSize = { PipelineContext::GetCurrentRootWidth(), PipelineContext::GetCurrentRootHeight() };
        layoutWrapper->GetGeometryNode()->SetFrameSize(fullSize);
        return;
    }
    PerformMeasureSelf(layoutWrapper);
}

std::optional<SizeF> VideoLayoutAlgorithm::MeasureContent(
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(host, std::nullopt);
    auto pattern = DynamicCast<VideoPattern>(host->GetPattern());
    CHECK_NULL_RETURN(pattern, std::nullopt);
    if (pattern->IsFullScreen()) {
        SizeF fullSize = { PipelineContext::GetCurrentRootWidth(), PipelineContext::GetCurrentRootHeight() };
        return fullSize;
    }
    auto layoutSize = contentConstraint.selfIdealSize.IsValid() ? contentConstraint.selfIdealSize.ConvertToSizeT()
                                                                : contentConstraint.maxSize;
    return layoutSize;
}

} // namespace OHOS::Ace::NG
