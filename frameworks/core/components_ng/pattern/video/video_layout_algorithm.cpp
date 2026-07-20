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

#include "core/components_ng/pattern/video/video_theme.h"
#include "core/components_ng/layout/drawing_layout_utils.h"
#include "core/components_ng/pattern/video/video_pattern.h"
#include "core/components_ng/pattern/video/video_state_machine_pattern.h"

namespace OHOS::Ace::NG {
namespace {
const Dimension LIFT_HEIGHT = 28.0_vp;
float CalControlBarHeight(bool needLift = false)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, 0.0f);
    auto videoTheme = pipelineContext->GetTheme<VideoTheme>();
    CHECK_NULL_RETURN(videoTheme, 0.0f);
    auto controlsHeight =
        pipelineContext->NormalizeToPx(Dimension(videoTheme->GetBtnSize().Height(), DimensionUnit::VP));
    controlsHeight += pipelineContext->NormalizeToPx(videoTheme->GetBtnEdge().Top());
    controlsHeight += pipelineContext->NormalizeToPx(videoTheme->GetBtnEdge().Bottom());
    if (needLift) {
        controlsHeight += LIFT_HEIGHT.ConvertToPx();
    }
    return static_cast<float>(controlsHeight);
}
} // namespace
VideoLayoutAlgorithm::VideoLayoutAlgorithm() = default;

void VideoLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    BoxLayoutAlgorithm::PerformLayout(layoutWrapper);
    auto contentOffset = layoutWrapper->GetGeometryNode()->GetContentOffset();
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto pattern = host->GetPattern();
    bool isFullScreen = false;
    auto stateMachinePattern = DynamicCast<VideoStateMachinePattern>(pattern);
    if (stateMachinePattern) {
        isFullScreen = stateMachinePattern->IsFullScreen();
    } else {
        auto videoPattern = DynamicCast<VideoPattern>(pattern);
        CHECK_NULL_VOID(videoPattern);
        isFullScreen = videoPattern->IsFullScreen();
    }
    for (auto&& child : layoutWrapper->GetAllChildrenWithBuild()) {
        if (child->GetHostTag() == V2::IMAGE_ETS_TAG) {
            child->GetGeometryNode()->SetMarginFrameOffset({ contentOffset.GetX(), contentOffset.GetY() });
        } else if (child->GetHostTag() == V2::ROW_ETS_TAG) {
            auto controlBarHeight = CalControlBarHeight(isFullScreen);
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
    auto layoutProperty = DynamicCast<VideoLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto layoutConstraint = layoutProperty->CreateChildConstraint();
    auto contentSize = layoutWrapper->GetGeometryNode()->GetContentSize();
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto pattern = host->GetPattern();
    bool isFullScreen = false;
    auto stateMachinePattern = DynamicCast<VideoStateMachinePattern>(pattern);
    if (stateMachinePattern) {
        isFullScreen = stateMachinePattern->IsFullScreen();
    } else {
        auto videoPattern = DynamicCast<VideoPattern>(pattern);
        CHECK_NULL_VOID(videoPattern);
        isFullScreen = videoPattern->IsFullScreen();
    }
    for (auto&& child : layoutWrapper->GetAllChildrenWithBuild()) {
        if (child->GetHostTag() == V2::IMAGE_ETS_TAG) {
            auto layoutConstraintForImage = layoutConstraint;
            layoutConstraintForImage.UpdateSelfMarginSizeWithCheck(OptionalSizeF(contentSize));
            layoutConstraintForImage.UpdateMaxSizeWithCheck(contentSize);
            layoutConstraintForImage.UpdateMinSizeWithCheck(contentSize);
            child->Measure(layoutConstraintForImage);
        } else if (child->GetHostTag() == V2::ROW_ETS_TAG && layoutProperty->GetControlsValue(true)) {
            auto controlBarHeight = CalControlBarHeight(isFullScreen);
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

    if (isFullScreen) {
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
    auto pattern = host->GetPattern();
    auto stateMachinePattern = DynamicCast<VideoStateMachinePattern>(pattern);
    if (stateMachinePattern) {
        if (stateMachinePattern->IsFullScreen()) {
            SizeF fullSize = { PipelineContext::GetCurrentRootWidth(), PipelineContext::GetCurrentRootHeight() };
            return fullSize;
        }
        auto layoutSize = contentConstraint.selfIdealSize.IsValid() ? contentConstraint.selfIdealSize.ConvertToSizeT()
                                                                     : contentConstraint.maxSize;
        MeasureLayoutPolicySize(contentConstraint, layoutWrapper, layoutSize);
        return layoutSize;
    }
    auto videoPattern = DynamicCast<VideoPattern>(pattern);
    if (videoPattern && videoPattern->IsFullScreen()) {
        SizeF fullSize = { PipelineContext::GetCurrentRootWidth(), PipelineContext::GetCurrentRootHeight() };
        return fullSize;
    }
    auto layoutSize = contentConstraint.selfIdealSize.IsValid() ? contentConstraint.selfIdealSize.ConvertToSizeT()
                                                                 : contentConstraint.maxSize;
    MeasureLayoutPolicySize(contentConstraint, layoutWrapper, layoutSize);
    return layoutSize;
}

} // namespace OHOS::Ace::NG
