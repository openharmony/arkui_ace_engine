/*
 * Copyright (c) 2023 iSoftStone Information Technology (Group) Co.,Ltd.
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

#include <optional>

#include "gtest/gtest.h"

#include "base/utils/utils.h"
#define protected public
#define private public

#include "base/utils/utils.h"
#include "core/components_ng/layout/layout_wrapper_builder.h"
#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/syntax/lazy_for_each_model.h"
#include "core/components_ng/syntax/lazy_layout_wrapper_builder.h"
#include "test/unittest/core/syntax/mock_lazy_for_each_builder.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const int32_t INDEX = 1;
constexpr int32_t NODE_ID_0 = 0;
constexpr int32_t NODE_ID_1 = 1;

RefPtr<LazyLayoutWrapperBuilder> CreateWrapperBuilder()
{
    RefPtr<LazyForEachActuator> actuator = AceType::MakeRefPtr<LazyForEachActuator>();
    auto builder = AceType::DynamicCast<LazyForEachBuilder>(actuator);
    RefPtr<LazyForEachNode> host = AceType::MakeRefPtr<LazyForEachNode>(INDEX, builder);
    RefPtr<LazyLayoutWrapperBuilder> wrapperBuilder = AceType::MakeRefPtr<LazyLayoutWrapperBuilder>(builder, host);
    return wrapperBuilder;
}

RefPtr<LayoutWrapperNode> CreateLayoutWrapper()
{
    auto rowFrameNode = FrameNode::CreateFrameNode("test", 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(rowFrameNode, geometryNode, rowFrameNode->GetLayoutProperty());
    return layoutWrapper;
}
} // namespace

class LayoutWrapperBuildTestNg : public testing::Test {};

/**
 * @tc.name: LayoutPropertyTest0001
 * @tc.desc: Test the operation of layout_property.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperBuildTestNg, LayoutWrapperBuildGetOrCreateWrapperByIndex, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create a wrapperBuilder.
     */
    RefPtr<LazyLayoutWrapperBuilder> wrapperBuilder = CreateWrapperBuilder();

    /**
     * @tc.steps: step2. callback GetOrCreateWrapperByIndex
     * @tc.expected: expect Return GetOrCreateWrapperByIndex is null.
     */
    wrapperBuilder->OnExpandChildLayoutWrapper();
    auto test = wrapperBuilder->GetOrCreateWrapperByIndex(INDEX);
    EXPECT_EQ(test, nullptr);

    /**
     * @tc.steps: step3. create a layoutWrapper for putting wrapperMap_.
     */
    wrapperBuilder->wrapperMap_ = std::unordered_map<int32_t, RefPtr<LayoutWrapper>>(
        { { 1, CreateLayoutWrapper() }, { 2, CreateLayoutWrapper() } });

    /**
     * @tc.steps: step4. callback GetOrCreateWrapperByIndex
     * @tc.expected: expect Return GetOrCreateWrapperByIndex is not null.
     */
    auto test1 = wrapperBuilder->GetOrCreateWrapperByIndex(INDEX);
    ASSERT_NE(test1, nullptr);
}

/**
 * @tc.name: LayoutPropertyTest0002
 * @tc.desc: Test the operation of layout_property.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperBuildTestNg, LayoutWrapperBuildExpandAllChildWrappers, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create a wrapperBuilder and callback ExpandAllChildWrappers.
     * @tc.expected: expect wrapperBuilder is not null.
     */
    RefPtr<LazyLayoutWrapperBuilder> wrapperBuilder = CreateWrapperBuilder();
    wrapperBuilder->ExpandAllChildWrappers();
    ASSERT_NE(wrapperBuilder, nullptr);
}

/**
 * @tc.name: LayoutPropertyTest0003
 * @tc.desc: Test the operation of layout_property.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperBuildTestNg, LayoutWrapperBuildRemoveAllChildInRenderTree, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create a wrapperBuilder and callback RemoveAllChildInRenderTree.
     * @tc.expected: expect wrapperBuilder is not null.
     */
    RefPtr<LazyLayoutWrapperBuilder> wrapperBuilder = CreateWrapperBuilder();
    wrapperBuilder->RemoveAllChildInRenderTree();
    ASSERT_NE(wrapperBuilder, nullptr);

    /**
     * @tc.steps: step3. callback RemoveAllChildInRenderTree and build a std::unordered_map.
     * @tc.expected: expect wrapperBuilder->wrapperMap_ is not null.
     */
    wrapperBuilder->wrapperMap_ = std::unordered_map<int32_t, RefPtr<LayoutWrapper>>(
        { { 1, CreateLayoutWrapper() }, { 2, CreateLayoutWrapper() } });
    wrapperBuilder->RemoveAllChildInRenderTree();
    EXPECT_EQ(wrapperBuilder->wrapperMap_.size(), 2);
}

/**
 * @tc.name: LayoutWrapperBuildTest0001
 * @tc.desc: Test the operation of GetOrCreateWrapperByIndex.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperBuildTestNg, LayoutWrapperBuildTest0001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create a wrapperBuilder.
     */
    RefPtr<LazyLayoutWrapperBuilder> wrapperBuilder = CreateWrapperBuilder();

    /**
     * @tc.steps: step2. callback GetOrCreateWrapperByIndex
     * @tc.expected: expect Return GetOrCreateWrapperByIndex is null.
     */
    wrapperBuilder->OnExpandChildLayoutWrapper();
    auto test = wrapperBuilder->GetOrCreateWrapperByIndex(INDEX);
    EXPECT_EQ(test, nullptr);

    /**
     * @tc.steps: step2. add cachedItems_
     * @tc.expected: add Successful.
     */
    RefPtr<LazyForEachBuilder> lazyEach = AceType::MakeRefPtr<Framework::MockLazyForEachBuilder>();
    auto node = FrameNode::CreateFrameNode(OHOS::Ace::V2::FLEX_ETS_TAG, NODE_ID_0, AceType::MakeRefPtr<Pattern>());
    auto node2 = FrameNode::CreateFrameNode(OHOS::Ace::V2::FLEX_ETS_TAG, NODE_ID_1, AceType::MakeRefPtr<Pattern>());
    lazyEach->cachedItems_[INDEX] = std::make_pair("test1", node);
    lazyEach->cachedItems_[INDEX + 1] = std::make_pair("test2", node2);
    wrapperBuilder->builder_ = lazyEach;
    EXPECT_EQ(lazyEach->GetTotalCount(), 2);

    /**
     * @tc.steps: step3. callback GetOrCreateWrapperByIndex
     * @tc.expected: expect Return GetOrCreateWrapperByIndex is not null.
     */
    test = wrapperBuilder->GetOrCreateWrapperByIndex(INDEX);
    EXPECT_NE(test, nullptr);
}
} // namespace OHOS::Ace::NG
