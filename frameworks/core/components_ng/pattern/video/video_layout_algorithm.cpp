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

#include <unicode/uchar.h>

#include "base/geometry/ng/size_t.h"
#include "base/i18n/localization.h"
#include "base/utils/utils.h"
#include "core/components_ng/pattern/video/video_layout_property.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {
namespace {
SizeF CalculateFitContain(const SizeF& videoSize, const SizeF& layoutSize)
{
    double layoutRatio = NearZero(layoutSize.Height()) ? 0.0 : layoutSize.Width() / layoutSize.Height();
    double sourceRatio = NearZero(videoSize.Height()) ? layoutRatio : videoSize.Width() / videoSize.Height();

    if (NearZero(layoutRatio) || NearZero(sourceRatio)) {
        return layoutSize;
    }
    if (sourceRatio < layoutRatio) {
        return { static_cast<float>(sourceRatio) * layoutSize.Height(), layoutSize.Height() };
    }
    return { layoutSize.Width(), static_cast<float>(layoutSize.Width() / sourceRatio) };
}
SizeF CalculateFitFill(const SizeF& layoutSize)
{
    return layoutSize;
}
SizeF CalculateFitCover(const SizeF& videoSize, const SizeF& layoutSize)
{
    double layoutRatio = NearZero(layoutSize.Height()) ? 0.0 : layoutSize.Width() / layoutSize.Height();
    double sourceRatio = NearZero(videoSize.Height()) ? layoutRatio : videoSize.Width() / videoSize.Height();

    if (NearZero(layoutRatio) || NearZero(sourceRatio)) {
        return layoutSize;
    }
    if (sourceRatio < layoutRatio) {
        return { layoutSize.Width(), static_cast<float>(layoutSize.Width() / sourceRatio) };
    }
    return { static_cast<float>(layoutSize.Height() * sourceRatio), layoutSize.Height() };
}
SizeF CalculateFitNone(const SizeF& videoSize)
{
    return videoSize;
}
SizeF CalculateFitScaleDown(const SizeF& videoSize, const SizeF& layoutSize)
{
    if (layoutSize.Width() > videoSize.Width()) {
        return CalculateFitNone(videoSize);
    }
    return CalculateFitContain(videoSize, layoutSize);
}
} // namespace
VideoLayoutAlgorithm::VideoLayoutAlgorithm() = default;

void VideoLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    BoxLayoutAlgorithm::PerformLayout(layoutWrapper);

    auto frameLayoutOffset = layoutWrapper->GetGeometryNode()->GetFrameOffset();
    auto parentGlobalOffset = layoutWrapper->GetGeometryNode()->GetParentGlobalOffset();
    auto offset = frameLayoutOffset + parentGlobalOffset;
    for (auto&& child : layoutWrapper->GetAllChildrenWithBuild()) {
        child->Layout(offset);
        if (child->GetHostTag() == V2::IMAGE_ETS_TAG) {
            child->GetGeometryNode()->SetFrameOffset(offset);
        }
    }
}
void VideoLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    PerformMeasureSelf(layoutWrapper);
    auto layoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    // 从layoutWrapper获取自身的ContentSize后，更新孩子节点的layoutConstraint，给image组件设置最小最大和selfIdeaSize为自身的ContentSize
    auto contentSize = layoutWrapper->GetGeometryNode()->GetContentSize();
    for (auto&& child : layoutWrapper->GetAllChildrenWithBuild()) {
        if (child->GetHostTag() == V2::IMAGE_ETS_TAG) {
            auto layoutConstraintForImage = layoutConstraint;
            layoutConstraintForImage.UpdateSelfIdealSizeWithCheck(OptionalSizeF(contentSize));
            layoutConstraintForImage.UpdateMaxSizeWithCheck(contentSize);
            layoutConstraintForImage.UpdateMinSizeWithCheck(contentSize);
            child->Measure(layoutConstraintForImage);
        } else {
            child->Measure(layoutConstraint);
        }
    }
}
std::optional<SizeF> VideoLayoutAlgorithm::MeasureContent(
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
    auto layoutProperty = DynamicCast<VideoLayoutProperty>(layoutWrapper->GetLayoutProperty());
    auto layoutSize = contentConstraint.selfIdealSize.IsValid() ? contentConstraint.selfIdealSize.ConvertToSizeT()
                                                                : contentConstraint.maxSize;
    if (!layoutProperty->HasVideoSize()) {
        LOGW("VideoSize has not set");
        return layoutSize;
    }
    auto videoSize = layoutProperty->GetVideoSizeValue(SizeF(0, 0));
    LOGD("VideoSize = %{public}s", videoSize.ToString().c_str());
    auto imageFit = layoutProperty->GetObjectFitValue(ImageFit::COVER);
    SizeF contentSize = { 0.0, 0.0 };
    switch (imageFit) {
        case ImageFit::CONTAIN:
            contentSize = CalculateFitContain(videoSize, layoutSize);
            break;
        case ImageFit::FILL:
            contentSize = CalculateFitFill(layoutSize);
            break;
        case ImageFit::COVER:
            contentSize = CalculateFitCover(videoSize, layoutSize);
            break;
        case ImageFit::NONE:
            contentSize = CalculateFitNone(videoSize);
            break;
        case ImageFit::SCALEDOWN:
            contentSize = CalculateFitScaleDown(videoSize, layoutSize);
            break;
        default:
            contentSize = CalculateFitContain(videoSize, layoutSize);
    }
    return contentSize;
}

} // namespace OHOS::Ace::NG
