/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/image/image_layout_algorithm.h"

#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/components_ng/property/measure_utils.h"

namespace OHOS::Ace::NG {
namespace {
// returns maximum size of image component
// if maxSize is infinite, match screen size and retain aspectRatio
SizeF GetMaxSize(const SizeF& maxSize, float aspectRatio)
{
    if (NearZero(aspectRatio)) {
        return { 0.0, 0.0 };
    }
    // infinite size not allowed
    bool infWidth = GreaterOrEqualToInfinity(maxSize.Width());
    bool infHeight = GreaterOrEqualToInfinity(maxSize.Height());
    if (infWidth && infHeight) {
        auto width = PipelineContext::GetCurrentRootWidth();
        return { width, width / aspectRatio };
    }
    if (infWidth) {
        return { maxSize.Height() * aspectRatio, maxSize.Height() };
    }
    if (infHeight) {
        return { maxSize.Width(), maxSize.Width() / aspectRatio };
    }
    return maxSize;
}
} // namespace

std::optional<SizeF> ImageLayoutAlgorithm::MeasureContent(
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
    // case 1: image component is set with valid size, return contentConstraint.selfIdealSize as component size
    if (contentConstraint.selfIdealSize.IsValid()) {
        return contentConstraint.selfIdealSize.ConvertToSizeT();
    }
    // case 2: image component is not set with size, use image source size to determine component size
    // if image data and altImage are both not ready, can not decide content size,
    // return std::nullopt and wait for next layout task triggered by [OnImageDataReady]
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(host, std::nullopt);
    auto pattern = host->GetPattern<ImagePattern>();
    CHECK_NULL_RETURN(pattern, std::nullopt);
    auto rawImageSize = pattern->GetImageSizeForMeasure();
    if (rawImageSize == std::nullopt) {
        return std::nullopt;
    }
    SizeF size(rawImageSize.value());
    do {
        auto aspectRatio = static_cast<float>(Size::CalcRatio(rawImageSize.value()));
        if (NearZero(aspectRatio)) {
            TAG_LOGW(AceLogTag::ACE_IMAGE, "image aspectRatio is 0");
            return std::nullopt;
        }
        // case 2.1: image component is not set with size, use image source size as image component size
        //          if fitOriginalSize is true, use image source size as image component size
        //          if fitOriginalSize is false, use the parent component LayoutConstraint size as image component size
        const auto& props = DynamicCast<ImageLayoutProperty>(layoutWrapper->GetLayoutProperty());
        bool fitOriginalSize = props->GetFitOriginalSize().value_or(false);
        if (contentConstraint.selfIdealSize.IsNull()) {
            if (!fitOriginalSize) {
                size.SetSizeT(GetMaxSize(contentConstraint.maxSize, aspectRatio));
            }
            break;
        }
        // case 2.2 image component is set with width or height, and
        //          image data is ready, use image source size to determine image component size
        //          keep the principle of making the component aspect ratio and the image source aspect ratio the same.
        //          the fitOriginSize is only useful in case 2.1.
        auto sizeSet = contentConstraint.selfIdealSize.ConvertToSizeT();
        size.SetSizeT(sizeSet);
        uint8_t sizeSetStatus = (Negative(sizeSet.Width()) << 1) | Negative(sizeSet.Height());
        switch (sizeSetStatus) {
            case 0b01: // width is positive and height is negative
                size.SetHeight(sizeSet.Width() / aspectRatio);
                break;
            case 0b10: // width is negative and height is positive
                size.SetWidth(sizeSet.Height() * aspectRatio);
                break;
            case 0b11: // both width and height are negative
            default:
                break;
        }
    } while (false);
    return contentConstraint.Constrain(size);
}

/**
 * Measure the layout size of the Image component based on its layout policy.
 *
 * This method handles different layout policies:
 * - For WRAP_CONTENT or FIXED policies, it calculates the image's frame size using its raw size.
 * - For MATCH_PARENT, it delegates the measurement to the base BoxLayoutAlgorithm and uses the result as the frame
 *  size. If a valid size is determined, it is set on the geometry node.
 */
void ImageLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    const auto& layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    auto layoutPolicy = layoutProperty->GetLayoutPolicyProperty();
    bool isPolicy = layoutPolicy.has_value();
    if (isPolicy && (layoutPolicy->IsWrap() || layoutPolicy->IsFix())) {
        auto host = layoutWrapper->GetHostNode();
        CHECK_NULL_VOID(host);
        auto pattern = host->GetPattern<ImagePattern>();
        CHECK_NULL_VOID(pattern);
        auto rawImageSize = pattern->GetImageSizeForMeasure();
        if (rawImageSize == std::nullopt) {
            return;
        }
        OptionalSizeF imageFrameSize;
        if (layoutPolicy->IsMatch()) {
            BoxLayoutAlgorithm::Measure(layoutWrapper);
            imageFrameSize.SetWidth(layoutWrapper->GetGeometryNode()->GetFrameSize().Width());
            imageFrameSize.SetHeight(layoutWrapper->GetGeometryNode()->GetFrameSize().Height());
        }
        UpdateFrameSizeWithLayoutPolicy(layoutWrapper, imageFrameSize, rawImageSize);
        if (imageFrameSize.IsValid()) {
            layoutWrapper->GetGeometryNode()->SetFrameSize(imageFrameSize.ConvertToSizeT());
        }
    } else {
        BoxLayoutAlgorithm::Measure(layoutWrapper);
    }
}

/**
 * Update the frame size of the image (`imageFrameSize`) based on the layout policy defined in the layout property.
 *
 * This method handles different layout policies for width and height:
 * - WRAP_CONTENT:
 *   - If width or height is set to WRAP, use the smaller of the raw image size and the parent ideal size.
 *   - This ensures the image adapts to its content but remains within parent constraints.
 *
 * - FIX_AT_IDEAL_SIZE:
 *   - If width or height is FIXED, directly use the raw image's dimensions.
 *   - This simulates a hardcoded size, unaffected by surrounding layout constraints.
 *
 * - MATCH_PARENT:
 *   - MATCH is not handled here; it is assumed to be processed by other logic.
 *   - Typically used when the image should stretch to fill the available space.
 *
 * - Default (neither WRAP, FIXED, nor MATCH):
 *   - Use the self ideal size if specified, otherwise fall back to raw image size.
 */
void ImageLayoutAlgorithm::UpdateFrameSizeWithLayoutPolicy(
    LayoutWrapper* layoutWrapper, OptionalSizeF& imageFrameSize, const std::optional<SizeF>& rawImageSize)
{
    // Update frame size based on layout policy
    auto layoutProperty = AceType::DynamicCast<ImageLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto layoutPolicy = layoutProperty->GetLayoutPolicyProperty();
    auto layoutConstraint = layoutProperty->GetLayoutConstraint();
    CHECK_NULL_VOID(layoutConstraint.has_value());
    // Calculate the frameWidth size based on the layout policy
    if (layoutPolicy->IsWidthWrap()) {
        auto parentIdealSize = layoutConstraint->parentIdealSize;
        imageFrameSize.SetWidth(std::min(
            parentIdealSize.Width().value_or(rawImageSize->Width()), rawImageSize->Width()
        ));
    } else if (layoutPolicy->IsWidthFix()) {
        // If width is fixed, use the raw image size
        imageFrameSize.SetWidth(rawImageSize->Width());
    } else if (!layoutPolicy->IsWidthMatch()) {
        imageFrameSize.SetWidth(layoutConstraint->selfIdealSize.Width().value_or(rawImageSize->Width()));
    }
    // Calculate the frameHeight size based on the layout policy
    if (layoutPolicy->IsHeightWrap()) {
        auto parentIdealSize = layoutConstraint->parentIdealSize;
        imageFrameSize.SetHeight(std::min(
            parentIdealSize.Height().value_or(rawImageSize->Height()), rawImageSize->Height()
        ));
    } else if (layoutPolicy->IsHeightFix()) {
        // If height is fixed, use the raw image size
        imageFrameSize.SetHeight(rawImageSize->Height());
    } else if (!layoutPolicy->IsHeightMatch()) {
        imageFrameSize.SetHeight(layoutConstraint->selfIdealSize.Height().value_or(rawImageSize->Height()));
    }
}

void ImageLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    if (IsImageAnimationLayout(layoutWrapper)) {
        PerformImageAnimationLayout(layoutWrapper);
        for (auto&& child : layoutWrapper->GetAllChildrenWithBuild()) {
            child->Layout();
        }
        return;
    }
    BoxLayoutAlgorithm::Layout(layoutWrapper);
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto pattern = host->GetPattern<ImagePattern>();
    CHECK_NULL_VOID(pattern);
    pattern->FinishMeasureForOnComplete();
}

void ImageLayoutAlgorithm::PerformImageAnimationLayout(LayoutWrapper* layoutWrapper)
{
    // update child position.
    CHECK_NULL_VOID(layoutWrapper);
    auto size = layoutWrapper->GetGeometryNode()->GetFrameSize();
    const auto& padding = layoutWrapper->GetLayoutProperty()->CreatePaddingAndBorder();
    MinusPaddingToSize(padding, size);
    auto left = padding.left.value_or(0);
    auto top = padding.top.value_or(0);
    auto paddingOffset = OffsetF(left, top);
    auto align = Alignment::CENTER;
    if (layoutWrapper->GetLayoutProperty()->GetPositionProperty()) {
        align = layoutWrapper->GetLayoutProperty()->GetPositionProperty()->GetAlignment().value_or(align);
    }
    // Update child position.
    for (const auto& child : layoutWrapper->GetAllChildrenWithBuild()) {
        if (!child) {
            continue;
        }
        SizeF childSize = child->GetGeometryNode()->GetMarginFrameSize();
        auto translate = Alignment::GetAlignPosition(size, childSize, align);
        if (!child->GetHostNode() || child->GetHostNode()->GetTag() != V2::IMAGE_ETS_TAG) {
            translate += paddingOffset;
        }
        child->GetGeometryNode()->SetMarginFrameOffset(translate);
    }
    // Update content position.
    const auto& content = layoutWrapper->GetGeometryNode()->GetContent();
    if (content) {
        auto translate = Alignment::GetAlignPosition(size, content->GetRect().GetSize(), align) + paddingOffset;
        content->SetOffset(translate);
    }
}

bool ImageLayoutAlgorithm::IsImageAnimationLayout(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_RETURN(layoutWrapper, false);
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(frameNode, false);
    auto pattern = AceType::DynamicCast<ImagePattern>(frameNode->GetPattern());
    CHECK_NULL_RETURN(pattern, false);
    CHECK_EQUAL_RETURN(pattern->GetIsAnimation(), true, true);
    return false;
}
} // namespace OHOS::Ace::NG
