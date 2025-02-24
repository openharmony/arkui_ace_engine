/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include <gmock/gmock.h>

#include "gtest/gtest.h"

#define private public
#define protected public
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/marquee/marquee_pattern.h"
#include "core/components_ng/pattern/pattern.h"
#undef protected
#undef private

#include "core/components_ng/layout/layout_wrapper.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class MarqueePatternTestNg : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};
};

class MockLayoutWrapper : public LayoutWrapper {
public:
    explicit MockLayoutWrapper(WeakPtr<FrameNode> hostNode) : LayoutWrapper(std::move(hostNode)) {}
    ~MockLayoutWrapper() override = default;

    MOCK_METHOD(const RefPtr<LayoutAlgorithmWrapper>&, GetLayoutAlgorithm, (bool needReset), (override));
    MOCK_METHOD(void, Measure, (const std::optional<LayoutConstraintF>& parentConstraint), (override));
    MOCK_METHOD(void, Layout, (), (override));
    MOCK_METHOD(int32_t, GetTotalChildCount, (), (const, override));
    MOCK_METHOD(const RefPtr<GeometryNode>&, GetGeometryNode, (), (const, override));
    MOCK_METHOD(const RefPtr<LayoutProperty>&, GetLayoutProperty, (), (const, override));
    MOCK_METHOD(RefPtr<LayoutWrapper>, GetOrCreateChildByIndex, (uint32_t index, bool addToRenderTree, bool isCache),
        (override));
    MOCK_METHOD(RefPtr<LayoutWrapper>, GetChildByIndex, (uint32_t index, bool isCache), (override));
    MOCK_METHOD(ChildrenListWithGuard, GetAllChildrenWithBuild, (bool addToRenderTree), (override));
    MOCK_METHOD(void, RemoveChildInRenderTree, (uint32_t index), (override));
    MOCK_METHOD(void, RemoveAllChildInRenderTree, (), (override));
    MOCK_METHOD(void, SetActiveChildRange,
        (int32_t start, int32_t end, int32_t cacheStart, int32_t cacheEnd, bool showCached), (override));
    MOCK_METHOD(void, RecycleItemsByIndex, (int32_t start, int32_t end), (override));
    MOCK_METHOD(const std::string&, GetHostTag, (), (const, override));
    MOCK_METHOD(bool, IsActive, (), (const, override));
    MOCK_METHOD(void, SetActive, (bool active, bool needRebuildRenderContext), (override));
    MOCK_METHOD(
        void, SetCacheCount, (int32_t cacheCount, const std::optional<LayoutConstraintF>& itemConstraint), (override));
    MOCK_METHOD(float, GetBaselineDistance, (), (const, override));
    MOCK_METHOD(bool, CheckNeedForceMeasureAndLayout, (), (override));
};

/**
 * @tc.name: MarqueePattern_OnDirtyLayoutWrapperSwap001
 * @tc.desc: Test OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(MarqueePatternTestNg, MarqueePattern_OnDirtyLayoutWrapperSwap001, TestSize.Level1)
{
    MarqueePattern marqueeModel;
    RefPtr<Pattern> pattern = AceType::MakeRefPtr<MarqueePattern>();
    auto frameNode = FrameNode::CreateFrameNode("tag", 2, pattern, false);
    RefPtr<PaintProperty> paintProperty = AceType::MakeRefPtr<MarqueePaintProperty>();
    frameNode->paintProperty_ = paintProperty;
    WeakPtr<FrameNode> hostNode(frameNode);
    marqueeModel.frameNode_ = hostNode;
    RefPtr<LayoutWrapper> dirty = AceType::MakeRefPtr<MockLayoutWrapper>(hostNode);
    DirtySwapConfig config;
    auto result = marqueeModel.OnDirtyLayoutWrapperSwap(dirty, config);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: MarqueePattern_GetTextOffset001
 * @tc.desc: Test GetTextOffset
 * @tc.type: FUNC
 */
HWTEST_F(MarqueePatternTestNg, MarqueePattern_GetTextOffset001, TestSize.Level1)
{
    MarqueePattern marqueeModel;
    auto offsetX = marqueeModel.GetTextOffset();
    EXPECT_EQ(offsetX, 0);
}
} // namespace OHOS::Ace::NG