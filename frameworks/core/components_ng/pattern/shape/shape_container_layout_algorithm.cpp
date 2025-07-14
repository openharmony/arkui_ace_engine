/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/shape/shape_container_layout_algorithm.h"

#include "core/components_ng/pattern/shape/shape_container_paint_property.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/components_ng/property/measure_utils.h"
namespace OHOS::Ace::NG {
void ShapeContainerLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    BoxLayoutAlgorithm::Measure(layoutWrapper);
    const auto& layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    auto layoutPolicy = layoutProperty->GetLayoutPolicyProperty();
    CHECK_NULL_VOID(layoutPolicy.has_value());
    const auto& content = layoutWrapper->GetGeometryNode()->GetContent();
    CHECK_NULL_VOID(content);
    auto contentSize = content->GetRect().GetSize();
    OptionalSizeF frameSize =
        UpdateOptionSizeByCalcLayoutConstraint(OptionalSizeF(contentSize.Width(), contentSize.Height()),
            layoutWrapper->GetLayoutProperty()->GetCalcLayoutConstraint(),
            layoutWrapper->GetLayoutProperty()->GetLayoutConstraint()->percentReference);
    if (layoutPolicy->IsWidthFix()) {
        layoutWrapper->GetGeometryNode()->SetFrameWidth(frameSize.Width().value_or(-1));
    }
    if (layoutPolicy->IsHeightFix()) {
        layoutWrapper->GetGeometryNode()->SetFrameHeight(frameSize.Height().value_or(-1));
    }
    auto childrenSize = frameSize.ConvertToSizeT();
    MeasureAdaptiveLayoutChildren(layoutWrapper, childrenSize);
}

std::optional<SizeF> ShapeContainerLayoutAlgorithm::MeasureContent(
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
    auto curFrameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(curFrameNode, std::nullopt);
    auto paintProperty = curFrameNode->GetPaintProperty<ShapeContainerPaintProperty>();
    CHECK_NULL_RETURN(paintProperty, std::nullopt);
    double portWidth = 0.0;
    double portHeight = 0.0;
    if (paintProperty->HasShapeViewBox() && paintProperty->GetShapeViewBoxValue().IsValid()) {
        portWidth = paintProperty->GetShapeViewBoxValue().Width().ConvertToPx();
        portHeight = paintProperty->GetShapeViewBoxValue().Height().ConvertToPx();
    }
    auto newSize = contentConstraint.maxSize;

    // When the width and height are both specified, shape size will not be influenced by viewport.
    if (contentConstraint.selfIdealSize.IsValid()) {
        return contentConstraint.selfIdealSize.ConvertToSizeT();
    }

    bool hasDefineWidth = contentConstraint.selfIdealSize.Width().has_value();
    bool hasDefineHeight = contentConstraint.selfIdealSize.Height().has_value();
    // When the width and height are both not specified, shape size is determined by viewport's size.
    // When only the width is not specified, width = (contentSize.Height() / portHeight) * portWidth
    // When only the height is not specified, height = (contentSize.Width() / portWidth) * portHeight
    if (contentConstraint.selfIdealSize.IsNull() && GreatNotEqual(portWidth, 0.0) && GreatNotEqual(portHeight, 0.0)) {
        newSize = contentConstraint.Constrain(SizeF(portWidth, portHeight));
    } else if (hasDefineWidth && !hasDefineHeight && GreatNotEqual(portWidth, 0.0)) {
        auto selfWidth = contentConstraint.selfIdealSize.Width().value();
        auto newHeight = (selfWidth / portWidth) * portHeight;
        newSize = contentConstraint.Constrain(SizeF(selfWidth, newHeight));
    } else if (!hasDefineWidth && hasDefineHeight && GreatNotEqual(portHeight, 0.0)) {
        auto selfHeight = contentConstraint.selfIdealSize.Height().value();
        auto newWidth = (selfHeight / portHeight) * portWidth;
        newSize = contentConstraint.Constrain(SizeF(newWidth, selfHeight));
    } else {
        newSize = contentConstraint.Constrain(GetChildrenSize(layoutWrapper, newSize));
    }
    MeasureLayoutPolicySize(contentConstraint, layoutWrapper, newSize);
    return newSize;
}

void ShapeContainerLayoutAlgorithm::MeasureLayoutPolicySize(
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper, SizeF& size)
{
    const auto& layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    auto layoutPolicy = layoutProperty->GetLayoutPolicyProperty();
    CHECK_NULL_VOID(layoutPolicy.has_value());
    const std::optional<float>& parentIdealSizeWidth = contentConstraint.parentIdealSize.Width();
    const std::optional<float>& parentIdealSizeHeight = contentConstraint.parentIdealSize.Height();
    if (layoutPolicy->IsWidthMatch() && parentIdealSizeWidth.has_value()) {
        size.SetWidth(parentIdealSizeWidth.value());
    }
    if (layoutPolicy->IsHeightMatch() && parentIdealSizeHeight.has_value()) {
        size.SetHeight(parentIdealSizeHeight.value());
    }

    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto paintProperty = host->GetPaintProperty<ShapeContainerPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    auto pixelMapInfo = paintProperty->GetPixelMapInfoValue(ImageSourceInfo());
    CHECK_NULL_VOID(pixelMapInfo.GetPixmap());
    if (layoutPolicy->IsWidthAdaptive()) {
        size.SetWidth(std::max(static_cast<float>(pixelMapInfo.GetPixmap()->GetWidth()), size.Width()));
    }
    if (layoutPolicy->IsHeightAdaptive()) {
        size.SetHeight(std::max(static_cast<float>(pixelMapInfo.GetPixmap()->GetHeight()), size.Height()));
    }
}

// get the max child size and offset.
SizeF ShapeContainerLayoutAlgorithm::GetChildrenSize(LayoutWrapper* layoutWrapper, SizeF maxSize)
{
    SizeF childFrame;
    float maxWidth = 0.0f;
    float maxHeight = 0.0f;

    auto childLayoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    auto layoutPolicy = layoutWrapper->GetLayoutProperty()->GetLayoutPolicyProperty();
    if (layoutPolicy.has_value()) {
        if (layoutPolicy->IsWidthAdaptive() && !childLayoutConstraint.parentIdealSize.Width().has_value()) {
            childLayoutConstraint.parentIdealSize.SetWidth(0);
        }
        if (layoutPolicy->IsHeightAdaptive() && !childLayoutConstraint.parentIdealSize.Height().has_value()) {
            childLayoutConstraint.parentIdealSize.SetHeight(0);
        }
    }

    for (auto&& child : layoutWrapper->GetAllChildrenWithBuild()) {
        child->Measure(childLayoutConstraint);
    }
    // reference: BoxLayoutAlgorithm::PerformMeasureSelfWithChildList()
    for (const auto& child : layoutWrapper->GetAllChildrenWithBuild()) {
        auto childSize = child->GetGeometryNode()->GetMarginFrameSize();
        float offsetX = 0.0f;
        float offsetY = 0.0f;
        // reference: RosenRenderContext::AdjustPaintRect()
        auto node = child->GetHostNode();
        CHECK_NULL_RETURN(node, maxSize);
        const auto& layoutConstraint = node->GetGeometryNode()->GetParentLayoutConstraint();
        auto widthPercentReference = layoutConstraint.has_value() ? layoutConstraint->percentReference.Width()
                                                                : PipelineContext::GetCurrentRootWidth();
        auto heightPercentReference = layoutConstraint.has_value() ? layoutConstraint->percentReference.Height()
                                                                : PipelineContext::GetCurrentRootHeight();
        auto context = node->GetRenderContext();
        CHECK_NULL_RETURN(context, maxSize);
        if (context->HasOffset()) {
            auto offset = context->GetOffsetValue({});
            offsetX = ConvertToPx(offset.GetX(), ScaleProperty::CreateScaleProperty(),
                widthPercentReference).value_or(0.0f);
            offsetY = ConvertToPx(offset.GetY(), ScaleProperty::CreateScaleProperty(),
                heightPercentReference).value_or(0.0f);
        }

        maxWidth = std::max(maxWidth, childSize.Width() + offsetX);
        maxHeight = std::max(maxHeight, childSize.Height() + offsetY);
    }
    childFrame.SetSizeT(SizeF { maxWidth, maxHeight });
    return childFrame;
}
} // namespace OHOS::Ace::NG
