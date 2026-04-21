/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/depth_component/depth_component_layout_algorithm.h"

#include "core/components_ng/pattern/depth_component/depth_component_layout_property.h"
#include "core/components_ng/pattern/depth_component/depth_component_pattern.h"
#include "core/components_ng/property/measure_utils.h"

namespace OHOS::Ace::NG {

namespace {
constexpr float DEFAULT_DEPTH_COMPONENT_WIDTH = 640.0f;
constexpr float DEFAULT_DEPTH_COMPONENT_HEIGHT = 480.0f;
}

void DepthComponentLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto depthLayoutProperty = AceType::DynamicCast<DepthComponentLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(depthLayoutProperty);
    const auto& layoutConstraint = depthLayoutProperty->GetLayoutConstraint();
    CHECK_NULL_VOID(layoutConstraint);
    auto contentConstraint = depthLayoutProperty->GetContentLayoutConstraint().value();
    const auto& children = layoutWrapper->GetAllChildrenWithBuild();

    OptionalSizeF frameSize;
    frameSize.UpdateSizeWithCheck(layoutConstraint->selfIdealSize);
    auto layoutPolicy = depthLayoutProperty->GetLayoutPolicyProperty();
    bool hasLayoutPolicy = layoutPolicy.has_value();

    float maxChildWidth = 0.0f;
    float maxChildHeight = 0.0f;
    bool isWrapContent = hasLayoutPolicy && (layoutPolicy->IsWidthWrap() || layoutPolicy->IsHeightWrap());
    for (const auto& child : children) {
        CHECK_NULL_VOID(child);
        child->Measure(contentConstraint);
        auto childGeometryNode = child->GetGeometryNode();
        CHECK_NULL_VOID(childGeometryNode);
        if (isWrapContent) {
            auto childSize = childGeometryNode->GetMarginFrameSize();
            maxChildWidth = std::max(maxChildWidth, childSize.Width());
            maxChildHeight = std::max(maxChildHeight, childSize.Height());
        }
    }

    if (hasLayoutPolicy) {
        if (layoutPolicy->IsWidthWrap()) {
            if (!frameSize.Width().has_value() && Positive(maxChildWidth)) {
                frameSize.SetWidth(maxChildWidth);
            }
        } else if (layoutPolicy->IsWidthMatch()) {
            frameSize.UpdateIllegalSizeWithCheck(layoutConstraint->parentIdealSize);
        }
        if (layoutPolicy->IsHeightWrap()) {
            if (!frameSize.Height().has_value() && Positive(maxChildHeight)) {
                frameSize.SetHeight(maxChildHeight);
            }
        } else if (layoutPolicy->IsHeightMatch()) {
            frameSize.UpdateIllegalSizeWithCheck(layoutConstraint->parentIdealSize);
        }
    }

    AdjustDepthComponentFrameSize(layoutWrapper, frameSize);
}

void DepthComponentLayoutAlgorithm::AdjustDepthComponentFrameSize(
    LayoutWrapper* layoutWrapper, OptionalSizeF& frameSize)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto depthLayoutProperty = AceType::DynamicCast<DepthComponentLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(depthLayoutProperty);
    const auto& layoutConstraint = depthLayoutProperty->GetLayoutConstraint();
    CHECK_NULL_VOID(layoutConstraint);
    if (!frameSize.Width().has_value()) {
        if (layoutConstraint->parentIdealSize.Width().has_value()) {
            frameSize.SetWidth(layoutConstraint->parentIdealSize.Width().value());
        } else {
            frameSize.SetWidth(DEFAULT_DEPTH_COMPONENT_WIDTH);
        }
    }
    if (!frameSize.Height().has_value()) {
        if (layoutConstraint->parentIdealSize.Height().has_value()) {
            frameSize.SetHeight(layoutConstraint->parentIdealSize.Height().value());
        } else {
            frameSize.SetHeight(DEFAULT_DEPTH_COMPONENT_HEIGHT);
        }
    }

    frameSize.Constrain(layoutConstraint->minSize, layoutConstraint->maxSize);
    auto geometryNode = layoutWrapper->GetGeometryNode();
    if (geometryNode) {
        geometryNode->SetFrameSize(frameSize.ConvertToSizeT());
    }
}

void DepthComponentLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto depthLayoutProperty = AceType::DynamicCast<DepthComponentLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(depthLayoutProperty);
    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);

    auto frameSize = geometryNode->GetFrameSize();
    if (frameSize.Width() <= 0 || frameSize.Height() <= 0) {
        TAG_LOGW(AceLogTag::ACE_DEPTH_COMPONENT, "Invalid frame size for layout");
        return;
    }

    const auto& padding = depthLayoutProperty->CreatePaddingAndBorder();
    auto contentWidth = frameSize.Width() - padding.Width();
    auto contentHeight = frameSize.Height() - padding.Height();
    auto contentOffset = padding.Offset();

    const auto& children = layoutWrapper->GetAllChildrenWithBuild();
    if (!children.empty()) {
        for (const auto& childWrapper : children) {
            CHECK_NULL_VOID(childWrapper);
            auto childGeometryNode = childWrapper->GetGeometryNode();
            CHECK_NULL_VOID(childGeometryNode);
            childGeometryNode->SetMarginFrameOffset(contentOffset);
            childWrapper->Layout();
        }
    }
    TAG_LOGI(AceLogTag::ACE_DEPTH_COMPONENT, "DepthComponentLayoutAlgorithm::Layout: content=%{public}.0fx%{public}.0f",
        contentWidth, contentHeight);
}

} // namespace OHOS::Ace::NG
