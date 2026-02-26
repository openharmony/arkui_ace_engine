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
#include "core/components_ng/pattern/marquee/marquee_layout_property.h"
#include "core/components_ng/pattern/marquee/marquee_paint_property.h"
#include "core/components_ng/pattern/marquee/marquee_pattern.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
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

/**
 * @tc.name: MarqueePattern_NeedSecondChild001
 * @tc.desc: Test NeedSecondChild
 * @tc.type: FUNC
 */
HWTEST_F(MarqueePatternTestNg, MarqueePattern_NeedSecondChild001, TestSize.Level1)
{
    MarqueePattern marqueeModel;
    auto result = marqueeModel.NeedSecondChild();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: MarqueePattern_NeedSecondChild002
 * @tc.desc: Test NeedSecondChild with MarqueeSpacing set
 * @tc.type: FUNC
 */
HWTEST_F(MarqueePatternTestNg, MarqueePattern_NeedSecondChild002, TestSize.Level1)
{
    RefPtr<Pattern> pattern = AceType::MakeRefPtr<MarqueePattern>();
    auto frameNode = FrameNode::CreateFrameNode("tag", 2, pattern, false);
    auto layoutProperty = frameNode->GetLayoutProperty<MarqueeLayoutProperty>();
    layoutProperty->UpdateMarqueeSpacing(Dimension(10.0));
    WeakPtr<FrameNode> hostNode(frameNode);
    auto marqueeModel = AceType::MakeRefPtr<MarqueePattern>();
    marqueeModel->frameNode_ = hostNode;
    auto result = marqueeModel->NeedSecondChild();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: MarqueePattern_NeedSecondChild003
 * @tc.desc: Test NeedSecondChild with MarqueeDelay set
 * @tc.type: FUNC
 */
HWTEST_F(MarqueePatternTestNg, MarqueePattern_NeedSecondChild003, TestSize.Level1)
{
    RefPtr<Pattern> pattern = AceType::MakeRefPtr<MarqueePattern>();
    auto frameNode = FrameNode::CreateFrameNode("tag", 2, pattern, false);
    auto layoutProperty = frameNode->GetLayoutProperty<MarqueeLayoutProperty>();
    layoutProperty->UpdateMarqueeDelay(100);
    WeakPtr<FrameNode> hostNode(frameNode);
    auto marqueeModel = AceType::MakeRefPtr<MarqueePattern>();
    marqueeModel->frameNode_ = hostNode;
    auto result = marqueeModel->NeedSecondChild();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: MarqueePattern_NeedSecondChild004
 * @tc.desc: Test NeedSecondChild with both MarqueeSpacing and MarqueeDelay set
 * @tc.type: FUNC
 */
HWTEST_F(MarqueePatternTestNg, MarqueePattern_NeedSecondChild004, TestSize.Level1)
{
    RefPtr<Pattern> pattern = AceType::MakeRefPtr<MarqueePattern>();
    auto frameNode = FrameNode::CreateFrameNode("tag", 2, pattern, false);
    auto layoutProperty = frameNode->GetLayoutProperty<MarqueeLayoutProperty>();
    layoutProperty->UpdateMarqueeSpacing(Dimension(20.0));
    layoutProperty->UpdateMarqueeDelay(200);
    WeakPtr<FrameNode> hostNode(frameNode);
    auto marqueeModel = AceType::MakeRefPtr<MarqueePattern>();
    marqueeModel->frameNode_ = hostNode;
    auto result = marqueeModel->NeedSecondChild();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: MarqueePattern_GetMarqueeSpacing001
 * @tc.desc: Test GetMarqueeSpacing
 * @tc.type: FUNC
 */
HWTEST_F(MarqueePatternTestNg, MarqueePattern_GetMarqueeSpacing001, TestSize.Level1)
{
    MarqueePattern marqueeModel;
    auto spacing = marqueeModel.GetMarqueeSpacing();
    EXPECT_EQ(spacing, 0.0f);
}

/**
 * @tc.name: MarqueePattern_GetSecondChildStart001
 * @tc.desc: Test GetSecondChildStart
 * @tc.type: FUNC
 */
HWTEST_F(MarqueePatternTestNg, MarqueePattern_GetSecondChildStart001, TestSize.Level1)
{
    MarqueePattern marqueeModel;
    auto start = marqueeModel.GetSecondChildStart();
    EXPECT_EQ(start, 0.0f);
}

/**
 * @tc.name: MarqueePattern_IsRunMarquee001
 * @tc.desc: Test IsRunMarquee
 * @tc.type: FUNC
 */
HWTEST_F(MarqueePatternTestNg, MarqueePattern_IsRunMarquee001, TestSize.Level1)
{
    MarqueePattern marqueeModel;
    auto result = marqueeModel.IsRunMarquee();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: MarqueePattern_OnlyPlayStatusChange001
 * @tc.desc: Test OnlyPlayStatusChange
 * @tc.type: FUNC
 */
HWTEST_F(MarqueePatternTestNg, MarqueePattern_OnlyPlayStatusChange001, TestSize.Level1)
{
    MarqueePattern marqueeModel;
    auto result = marqueeModel.OnlyPlayStatusChange();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: MarqueePattern_CalculateStart001
 * @tc.desc: Test CalculateStart
 * @tc.type: FUNC
 */
HWTEST_F(MarqueePatternTestNg, MarqueePattern_CalculateStart001, TestSize.Level1)
{
    MarqueePattern marqueeModel;
    auto start = marqueeModel.CalculateStart();
    EXPECT_EQ(start, 0.0f);
}

/**
 * @tc.name: MarqueePattern_CalculateEnd001
 * @tc.desc: Test CalculateEnd
 * @tc.type: FUNC
 */
HWTEST_F(MarqueePatternTestNg, MarqueePattern_CalculateEnd001, TestSize.Level1)
{
    MarqueePattern marqueeModel;
    auto end = marqueeModel.CalculateEnd();
    EXPECT_EQ(end, 0.0f);
}

/**
 * @tc.name: MarqueePattern_GetTextNodeWidth001
 * @tc.desc: Test GetTextNodeWidth
 * @tc.type: FUNC
 */
HWTEST_F(MarqueePatternTestNg, MarqueePattern_GetTextNodeWidth001, TestSize.Level1)
{
    MarqueePattern marqueeModel;
    auto width = marqueeModel.GetTextNodeWidth();
    EXPECT_EQ(width, 0.0f);
}

/**
 * @tc.name: MarqueePattern_GetScrollAmount001
 * @tc.desc: Test GetScrollAmount
 * @tc.type: FUNC
 */
HWTEST_F(MarqueePatternTestNg, MarqueePattern_GetScrollAmount001, TestSize.Level1)
{
    MarqueePattern marqueeModel;
    auto amount = marqueeModel.GetScrollAmount();
    EXPECT_EQ(amount, 0.0f);
}

/**
 * @tc.name: MarqueePattern_OnWindowSizeChanged001
 * @tc.desc: Test OnWindowSizeChanged
 * @tc.type: FUNC
 */
HWTEST_F(MarqueePatternTestNg, MarqueePattern_OnWindowSizeChanged001, TestSize.Level1)
{
    MarqueePattern marqueeModel;
    marqueeModel.OnWindowSizeChanged(100, 200, WindowSizeChangeReason::ROTATION);
    EXPECT_EQ(marqueeModel.lastWindowWidth_, 100);
    EXPECT_EQ(marqueeModel.lastWindowHeight_, 200);
}

/**
 * @tc.name: MarqueePattern_OnWindowSizeChanged002
 * @tc.desc: Test OnWindowSizeChanged with same size
 * @tc.type: FUNC
 */
HWTEST_F(MarqueePatternTestNg, MarqueePattern_OnWindowSizeChanged002, TestSize.Level1)
{
    MarqueePattern marqueeModel;
    marqueeModel.lastWindowWidth_ = 100;
    marqueeModel.lastWindowHeight_ = 200;
    marqueeModel.OnWindowSizeChanged(100, 200, WindowSizeChangeReason::ROTATION);
    EXPECT_FALSE(marqueeModel.measureChanged_);
}

/**
 * @tc.name: MarqueePattern_GetCurrentTextDirection001
 * @tc.desc: Test GetCurrentTextDirection
 * @tc.type: FUNC
 */
HWTEST_F(MarqueePatternTestNg, MarqueePattern_GetCurrentTextDirection001, TestSize.Level1)
{
    MarqueePattern marqueeModel;
    auto direction = marqueeModel.GetCurrentTextDirection();
    EXPECT_EQ(direction, TextDirection::LTR);
}

/**
 * @tc.name: MarqueePattern_OnModifyDone001
 * @tc.desc: Test OnModifyDone with NeedSecondChild() returns true (MarqueeSpacing set)
 * @tc.type: FUNC
 */
HWTEST_F(MarqueePatternTestNg, MarqueePattern_OnModifyDone001, TestSize.Level1)
{
    RefPtr<Pattern> pattern = AceType::MakeRefPtr<MarqueePattern>();
    auto frameNode = FrameNode::CreateFrameNode("Marquee", 1, pattern, false);
    auto layoutProperty = frameNode->GetLayoutProperty<MarqueeLayoutProperty>();
    layoutProperty->UpdateMarqueeSpacing(Dimension(10.0));
    auto paintProperty = frameNode->GetPaintProperty<MarqueePaintProperty>();
    frameNode->paintProperty_ = paintProperty;

    auto textFrameNode = FrameNode::CreateFrameNode("Text", 2, AceType::MakeRefPtr<TextPattern>(), false);
    frameNode->AddChild(textFrameNode);

    WeakPtr<FrameNode> hostNode(frameNode);
    auto marqueeModel = AceType::MakeRefPtr<MarqueePattern>();
    marqueeModel->frameNode_ = hostNode;

    marqueeModel->OnModifyDone();

    EXPECT_EQ(frameNode->GetChildren().size(), 2);
}

/**
 * @tc.name: MarqueePattern_OnModifyDone002
 * @tc.desc: Test OnModifyDone with NeedSecondChild() returns true (MarqueeDelay set)
 * @tc.type: FUNC
 */
HWTEST_F(MarqueePatternTestNg, MarqueePattern_OnModifyDone002, TestSize.Level1)
{
    RefPtr<Pattern> pattern = AceType::MakeRefPtr<MarqueePattern>();
    auto frameNode = FrameNode::CreateFrameNode("Marquee", 1, pattern, false);
    auto layoutProperty = frameNode->GetLayoutProperty<MarqueeLayoutProperty>();
    layoutProperty->UpdateMarqueeDelay(100);
    auto paintProperty = frameNode->GetPaintProperty<MarqueePaintProperty>();
    frameNode->paintProperty_ = paintProperty;

    auto textFrameNode = FrameNode::CreateFrameNode("Text", 2, AceType::MakeRefPtr<TextPattern>(), false);
    frameNode->AddChild(textFrameNode);

    WeakPtr<FrameNode> hostNode(frameNode);
    auto marqueeModel = AceType::MakeRefPtr<MarqueePattern>();
    marqueeModel->frameNode_ = hostNode;

    marqueeModel->OnModifyDone();

    EXPECT_EQ(frameNode->GetChildren().size(), 2);
}

/**
 * @tc.name: MarqueePattern_OnModifyDone003
 * @tc.desc: Test OnModifyDone with children > 1 and NeedSecondChild() returns false (should remove second child)
 * @tc.type: FUNC
 */
HWTEST_F(MarqueePatternTestNg, MarqueePattern_OnModifyDone003, TestSize.Level1)
{
    RefPtr<Pattern> pattern = AceType::MakeRefPtr<MarqueePattern>();
    auto frameNode = FrameNode::CreateFrameNode("Marquee", 1, pattern, false);
    auto layoutProperty = frameNode->GetLayoutProperty<MarqueeLayoutProperty>();
    auto paintProperty = frameNode->GetPaintProperty<MarqueePaintProperty>();
    frameNode->paintProperty_ = paintProperty;

    auto textFrameNode1 = FrameNode::CreateFrameNode("Text1", 2, AceType::MakeRefPtr<TextPattern>(), false);
    auto textFrameNode2 = FrameNode::CreateFrameNode("Text2", 3, AceType::MakeRefPtr<TextPattern>(), false);
    frameNode->AddChild(textFrameNode1);
    frameNode->AddChild(textFrameNode2);

    EXPECT_EQ(frameNode->GetChildren().size(), 2);

    WeakPtr<FrameNode> hostNode(frameNode);
    auto marqueeModel = AceType::MakeRefPtr<MarqueePattern>();
    marqueeModel->frameNode_ = hostNode;

    marqueeModel->OnModifyDone();

    EXPECT_EQ(frameNode->GetChildren().size(), 1);
}

/**
 * @tc.name: MarqueePattern_OnModifyDone004
 * @tc.desc: Test OnModifyDone with single child and NeedSecondChild() returns false (no change)
 * @tc.type: FUNC
 */
HWTEST_F(MarqueePatternTestNg, MarqueePattern_OnModifyDone004, TestSize.Level1)
{
    RefPtr<Pattern> pattern = AceType::MakeRefPtr<MarqueePattern>();
    auto frameNode = FrameNode::CreateFrameNode("Marquee", 1, pattern, false);
    auto layoutProperty = frameNode->GetLayoutProperty<MarqueeLayoutProperty>();
    auto paintProperty = frameNode->GetPaintProperty<MarqueePaintProperty>();
    frameNode->paintProperty_ = paintProperty;

    auto textFrameNode = FrameNode::CreateFrameNode("Text", 2, AceType::MakeRefPtr<TextPattern>(), false);
    frameNode->AddChild(textFrameNode);

    EXPECT_EQ(frameNode->GetChildren().size(), 1);

    WeakPtr<FrameNode> hostNode(frameNode);
    auto marqueeModel = AceType::MakeRefPtr<MarqueePattern>();
    marqueeModel->frameNode_ = hostNode;

    marqueeModel->OnModifyDone();

    EXPECT_EQ(frameNode->GetChildren().size(), 1);
}
} // namespace OHOS::Ace::NG