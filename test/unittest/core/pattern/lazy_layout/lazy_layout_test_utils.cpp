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

#include "test/unittest/core/pattern/lazy_layout/lazy_layout_test_utils.h"

#include "gtest/gtest.h"

namespace OHOS::Ace::NG {
namespace {
class FixedHeightLayoutAlgorithm : public LayoutAlgorithm {
    DECLARE_ACE_TYPE(FixedHeightLayoutAlgorithm, LayoutAlgorithm);

public:
    FixedHeightLayoutAlgorithm(float height, int32_t& measureCount)
        : height_(height), measureCount_(measureCount)
    {}

    void Measure(LayoutWrapper* layoutWrapper) override
    {
        ASSERT_NE(layoutWrapper, nullptr);
        auto geometryNode = layoutWrapper->GetGeometryNode();
        ASSERT_NE(geometryNode, nullptr);
        geometryNode->SetFrameSize(SizeF(100.0f, height_));
        if (!hasCounted_) {
            ++measureCount_;
            hasCounted_ = true;
        }
    }

    void Layout(LayoutWrapper*) override {}

private:
    float height_ = 0.0f;
    int32_t& measureCount_;
    bool hasCounted_ = false;
};
} // namespace

void AppendFixedHeightChild(
    const RefPtr<LayoutWrapperNode>& parent, int32_t nodeId, float height, int32_t& measureCount)
{
    ASSERT_NE(parent, nullptr);
    auto childNode = FrameNode::CreateFrameNode(
        "LazyLayoutTestItem", nodeId, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(childNode, nullptr);
    auto parentNode = parent->GetHostNode();
    ASSERT_NE(parentNode, nullptr);
    parentNode->AddChild(childNode);
    auto childWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        childNode, AceType::MakeRefPtr<GeometryNode>(), childNode->GetLayoutProperty());
    childWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(
        AceType::MakeRefPtr<FixedHeightLayoutAlgorithm>(height, measureCount)));
    parent->AppendChild(childWrapper);
}

CachedLazyLayoutTestContext CreateCachedLazyLayoutTestContext(const std::string& lazyTag,
    const RefPtr<Pattern>& lazyPattern, const RefPtr<LayoutAlgorithm>& algorithm, const SizeF& viewportSize)
{
    CachedLazyLayoutTestContext context;
    auto parentPattern = AceType::MakeRefPtr<WaterFlowPattern>();
    parentPattern->SetAxis(Axis::VERTICAL);
    auto parentProperty = AceType::MakeRefPtr<WaterFlowLayoutProperty>();
    context.parent = FrameNode::CreateFrameNode(
        V2::WATERFLOW_ETS_TAG, CACHED_LAZY_PARENT_NODE_ID, parentPattern, parentProperty);
    if (!context.parent) {
        return context;
    }
    auto parentGeometry = AceType::MakeRefPtr<GeometryNode>();
    parentGeometry->SetFrameSize(viewportSize);
    context.parent->SetGeometryNode(parentGeometry);
    context.parentConstraint.maxSize = viewportSize;
    context.parentConstraint.percentReference = viewportSize;
    parentProperty->UpdateLayoutConstraint(context.parentConstraint);

    context.host = FrameNode::CreateFrameNode(lazyTag, CACHED_LAZY_HOST_NODE_ID, lazyPattern);
    if (!context.host) {
        return context;
    }
    context.host->MountToParent(context.parent, DEFAULT_NODE_SLOT, true);
    auto hostGeometry = AceType::MakeRefPtr<GeometryNode>();
    hostGeometry->SetFrameSize(viewportSize);
    hostGeometry->SetParentLayoutConstraint(context.parentConstraint);
    context.host->SetGeometryNode(hostGeometry);
    context.wrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        context.host, hostGeometry, context.host->GetLayoutProperty());
    context.wrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(algorithm));
    return context;
}
} // namespace OHOS::Ace::NG
