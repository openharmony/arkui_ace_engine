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
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#undef protected
#undef private

#include "core/components_ng/layout/layout_wrapper.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class MarqueePatternTestNg : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        MockContainer::SetUp();
        MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
        MockPipelineContext::SetUp();
        auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
        MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    }

    static void TearDownTestSuite()
    {
        MockPipelineContext::TearDown();
    }
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

    /**
     *  @tc.step test if amonut is 0.0f
     *
     */
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

/*
 * @tc.name: MarqueePattern_UpdateTextDirection_LTR
 * @tc.desc: Test UpdateTextDirection with LTR content
 * @tc.type: FUNC
 */
HWTEST_F(MarqueePatternTestNg, MarqueePattern_UpdateTextDirection_LTR, TestSize.Level1)
{
    MarqueePattern marqueePattern;
    auto content = "test";
    auto result = marqueePattern.GetTextDirection(content, TextDirection::LTR);
    EXPECT_NE(result, TextDirection::AUTO);
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

    auto textFrameNode1 = FrameNode::CreateFrameNode("Text", 2, AceType::MakeRefPtr<TextPattern>(), false);
    frameNode->AddChild(textFrameNode1);

    auto textFrameNode2 = FrameNode::CreateFrameNode("Text", 3, AceType::MakeRefPtr<TextPattern>(), false);
    frameNode->AddChild(textFrameNode2);

    auto marqueeModel = AceType::DynamicCast<MarqueePattern>(pattern);
    WeakPtr<FrameNode> hostNode(frameNode);
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

    auto textFrameNode1 = FrameNode::CreateFrameNode("Text", 2, AceType::MakeRefPtr<TextPattern>(), false);
    frameNode->AddChild(textFrameNode1);

    auto textFrameNode2 = FrameNode::CreateFrameNode("Text", 3, AceType::MakeRefPtr<TextPattern>(), false);
    frameNode->AddChild(textFrameNode2);

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

/**
 * @tc.name: MarqueePattern_ChangeSecondChildVisibility001
 * @tc.desc: Test ChangeSecondChildVisibility with no second child
 * @tc.type: FUNC
 */
HWTEST_F(MarqueePatternTestNg, MarqueePattern_ChangeSecondChildVisibility001, TestSize.Level1)
{
    RefPtr<Pattern> pattern = AceType::MakeRefPtr<MarqueePattern>();
    auto frameNode = FrameNode::CreateFrameNode("Marquee", 1, pattern, false);
    WeakPtr<FrameNode> hostNode(frameNode);
    auto marqueeModel = AceType::MakeRefPtr<MarqueePattern>();
    marqueeModel->frameNode_ = hostNode;
    
    marqueeModel->ChangeSecondChildVisibility(false);
    
    EXPECT_EQ(frameNode->GetChildren().size(), 0);
}

/**
 * @tc.name: MarqueePattern_ChangeSecondChildVisibility002
 * @tc.desc: Test ChangeSecondChildVisibility with single child
 * @tc.type: FUNC
 */
HWTEST_F(MarqueePatternTestNg, MarqueePattern_ChangeSecondChildVisibility002, TestSize.Level1)
{
    RefPtr<Pattern> pattern = AceType::MakeRefPtr<MarqueePattern>();
    auto frameNode = FrameNode::CreateFrameNode("Marquee", 1, pattern, false);
    auto textFrameNode = FrameNode::CreateFrameNode("Text", 2, AceType::MakeRefPtr<TextPattern>(), false);
    frameNode->AddChild(textFrameNode);
    WeakPtr<FrameNode> hostNode(frameNode);
    auto marqueeModel = AceType::MakeRefPtr<MarqueePattern>();
    marqueeModel->frameNode_ = hostNode;
    
    EXPECT_EQ(frameNode->GetChildren().size(), 1);
    
    marqueeModel->ChangeSecondChildVisibility(false);
    
    EXPECT_EQ(frameNode->GetChildren().size(), 1);
}

/**
 * @tc.name: MarqueePattern_ChangeSecondChildVisibility003
 * @tc.desc: Test ChangeSecondChildVisibility with two children and IsRunMarquee returns false
 * @tc.type: FUNC
 */
HWTEST_F(MarqueePatternTestNg, MarqueePattern_ChangeSecondChildVisibility003, TestSize.Level1)
{
    RefPtr<Pattern> pattern = AceType::MakeRefPtr<MarqueePattern>();
    auto frameNode = FrameNode::CreateFrameNode("Marquee", 1, pattern, false);
    auto textFrameNode1 = FrameNode::CreateFrameNode("Text1", 2, AceType::MakeRefPtr<TextPattern>(), false);
    auto textFrameNode2 = FrameNode::CreateFrameNode("Text2", 3, AceType::MakeRefPtr<TextPattern>(), false);
    frameNode->AddChild(textFrameNode1);
    frameNode->AddChild(textFrameNode2);
    WeakPtr<FrameNode> hostNode(frameNode);
    auto marqueeModel = AceType::MakeRefPtr<MarqueePattern>();
    marqueeModel->frameNode_ = hostNode;
    
    EXPECT_EQ(frameNode->GetChildren().size(), 2);
    
    auto secondChild = AceType::DynamicCast<FrameNode>(frameNode->GetLastChild());
    auto textLayoutProperty = secondChild->GetLayoutProperty<TextLayoutProperty>();
    textLayoutProperty->UpdateVisibility(VisibleType::VISIBLE);
    RefPtr<GeometryNode> geo1 = AceType::MakeRefPtr<GeometryNode>();
    geo1->SetFrameSize(SizeF(100, 50));
    frameNode->SetGeometryNode(geo1);
    RefPtr<GeometryNode> geo2 = AceType::MakeRefPtr<GeometryNode>();
    geo2->SetFrameSize(SizeF(50, 50));
    textFrameNode1->SetGeometryNode(geo2);
    marqueeModel->ChangeSecondChildVisibility(false);
    
    EXPECT_TRUE(textLayoutProperty->GetVisibilityValue(VisibleType::VISIBLE) == VisibleType::INVISIBLE);
}

/**
 * @tc.name: MarqueePattern_ChangeSecondChildVisibility004
 * @tc.desc: Test ChangeSecondChildVisibility with stopAndStart = true
 * @tc.type: FUNC
 */
HWTEST_F(MarqueePatternTestNg, MarqueePattern_ChangeSecondChildVisibility004, TestSize.Level1)
{
    RefPtr<Pattern> pattern = AceType::MakeRefPtr<MarqueePattern>();
    auto frameNode = FrameNode::CreateFrameNode("Marquee", 1, pattern, false);
    auto textFrameNode1 = FrameNode::CreateFrameNode("Text1", 2, AceType::MakeRefPtr<TextPattern>(), false);
    auto textFrameNode2 = FrameNode::CreateFrameNode("Text2", 3, AceType::MakeRefPtr<TextPattern>(), false);
    frameNode->AddChild(textFrameNode1);
    frameNode->AddChild(textFrameNode2);
    WeakPtr<FrameNode> hostNode(frameNode);
    auto marqueeModel = AceType::MakeRefPtr<MarqueePattern>();
    marqueeModel->frameNode_ = hostNode;
    
    auto secondChild = AceType::DynamicCast<FrameNode>(frameNode->GetLastChild());
    auto textLayoutProperty = secondChild->GetLayoutProperty<TextLayoutProperty>();
    textLayoutProperty->UpdateVisibility(VisibleType::INVISIBLE);

    RefPtr<GeometryNode> geo1 = AceType::MakeRefPtr<GeometryNode>();
    geo1->SetFrameSize(SizeF(50, 50));
    frameNode->SetGeometryNode(geo1);
    RefPtr<GeometryNode> geo2 = AceType::MakeRefPtr<GeometryNode>();
    geo2->SetFrameSize(SizeF(100, 50));
    textFrameNode1->SetGeometryNode(geo1);
    
    marqueeModel->ChangeSecondChildVisibility(true);
    
    EXPECT_TRUE(textLayoutProperty->GetVisibilityValue(VisibleType::VISIBLE) == VisibleType::VISIBLE);
}

/**
 * @tc.name: MarqueePattern_FireStartEvent001
 * @tc.desc: Test FireStartEvent
 * @tc.type: FUNC
 */
HWTEST_F(MarqueePatternTestNg, MarqueePattern_FireStartEvent001, TestSize.Level1)
{
    RefPtr<Pattern> pattern = AceType::MakeRefPtr<MarqueePattern>();
    auto frameNode = FrameNode::CreateFrameNode("Marquee", 1, pattern, false);
    WeakPtr<FrameNode> hostNode(frameNode);
    auto marqueeModel = AceType::MakeRefPtr<MarqueePattern>();
    marqueeModel->frameNode_ = hostNode;
    marqueeModel->FireStartEvent();
    EXPECT_NE(marqueeModel, nullptr);
}

/**
 * @tc.name: MarqueePattern_FireBounceEvent001
 * @tc.desc: Test FireBounceEvent
 * @tc.type: FUNC
 */
HWTEST_F(MarqueePatternTestNg, MarqueePattern_FireBounceEvent001, TestSize.Level1)
{
    RefPtr<Pattern> pattern = AceType::MakeRefPtr<MarqueePattern>();
    auto frameNode = FrameNode::CreateFrameNode("Marquee", 1, pattern, false);
    WeakPtr<FrameNode> hostNode(frameNode);
    auto marqueeModel = AceType::MakeRefPtr<MarqueePattern>();
    marqueeModel->frameNode_ = hostNode;
    marqueeModel->FireBounceEvent();
    EXPECT_NE(marqueeModel, nullptr);
}

/**
 * @tc.name: MarqueePattern_FireFinishEvent001
 * @tc.desc: Test FireFinishEvent
 * @tc.type: FUNC
 */
HWTEST_F(MarqueePatternTestNg, MarqueePattern_FireFinishEvent001, TestSize.Level1)
{
    RefPtr<Pattern> pattern = AceType::MakeRefPtr<MarqueePattern>();
    auto frameNode = FrameNode::CreateFrameNode("Marquee", 1, pattern, false);
    WeakPtr<FrameNode> hostNode(frameNode);
    auto marqueeModel = AceType::MakeRefPtr<MarqueePattern>();
    marqueeModel->frameNode_ = hostNode;
    marqueeModel->FireFinishEvent();
    EXPECT_NE(marqueeModel, nullptr);
}

/**
 * @tc.name: MarqueePattern_StoreProperties001
 * @tc.desc: Test StoreProperties
 * @tc.type: FUNC
 */
HWTEST_F(MarqueePatternTestNg, MarqueePattern_StoreProperties001, TestSize.Level1)
{
    MarqueePattern marqueeModel;
    marqueeModel.StoreProperties();
    EXPECT_EQ(marqueeModel.IsRunMarquee(), false);
}

/**
 * @tc.name: MarqueePattern_GetMarqueeSpacing002
 * @tc.desc: Test GetMarqueeSpacing with spacing set
 * @tc.type: FUNC
 */
HWTEST_F(MarqueePatternTestNg, MarqueePattern_GetMarqueeSpacing002, TestSize.Level1)
{
    RefPtr<Pattern> pattern = AceType::MakeRefPtr<MarqueePattern>();
    auto frameNode = FrameNode::CreateFrameNode("Marquee", 1, pattern, false);
    auto layoutProperty = frameNode->GetLayoutProperty<MarqueeLayoutProperty>();
    layoutProperty->UpdateMarqueeSpacing(Dimension(15.0));
    WeakPtr<FrameNode> hostNode(frameNode);
    auto marqueeModel = AceType::MakeRefPtr<MarqueePattern>();
    marqueeModel->frameNode_ = hostNode;
    auto spacing = marqueeModel->GetMarqueeSpacing();
    EXPECT_GT(spacing, 0.0f);
}

/**
 * @tc.name: MarqueePattern_GetScrollAmount002
 * @tc.desc: Test GetScrollAmount with custom value
 * @tc.type: FUNC
 */
HWTEST_F(MarqueePatternTestNg, MarqueePattern_GetScrollAmount002, TestSize.Level1)
{
    RefPtr<Pattern> pattern = AceType::MakeRefPtr<MarqueePattern>();
    auto frameNode = FrameNode::CreateFrameNode("Marquee", 1, pattern, false);
    auto paintProperty = frameNode->GetPaintProperty<MarqueePaintProperty>();
    paintProperty->UpdateScrollAmount(12.0);
    frameNode->paintProperty_ = paintProperty;
    WeakPtr<FrameNode> hostNode(frameNode);
    auto marqueeModel = AceType::MakeRefPtr<MarqueePattern>();
    marqueeModel->frameNode_ = hostNode;
    auto amount = marqueeModel->GetScrollAmount();
    EXPECT_GT(amount, 0.0);
}

/**
 * @tc.name: MarqueePattern_CalculateStart002
 * @tc.desc: Test CalculateStart with different direction
 * @tc.type: FUNC
 */
HWTEST_F(MarqueePatternTestNg, MarqueePattern_CalculateStart002, TestSize.Level1)
{
    RefPtr<Pattern> pattern = AceType::MakeRefPtr<MarqueePattern>();
    auto frameNode = FrameNode::CreateFrameNode("Marquee", 1, pattern, false);
    auto layoutProperty = frameNode->GetLayoutProperty<MarqueeLayoutProperty>();
    layoutProperty->UpdateDirection(MarqueeDirection::RIGHT);
    WeakPtr<FrameNode> hostNode(frameNode);
    auto marqueeModel = AceType::MakeRefPtr<MarqueePattern>();
    marqueeModel->frameNode_ = hostNode;
    auto start = marqueeModel->CalculateStart();
    EXPECT_EQ(start, 0.0f);
}

/**
 * @tc.name: MarqueePattern_CalculateEnd002
 * @tc.desc: Test CalculateEnd with different direction
 * @tc.type: FUNC
 */
HWTEST_F(MarqueePatternTestNg, MarqueePattern_CalculateEnd002, TestSize.Level1)
{
    RefPtr<Pattern> pattern = AceType::MakeRefPtr<MarqueePattern>();
    auto frameNode = FrameNode::CreateFrameNode("Marquee", 1, pattern, false);
    auto layoutProperty = frameNode->GetLayoutProperty<MarqueeLayoutProperty>();
    layoutProperty->UpdateDirection(MarqueeDirection::RIGHT);
    WeakPtr<FrameNode> hostNode(frameNode);
    auto marqueeModel = AceType::MakeRefPtr<MarqueePattern>();
    marqueeModel->frameNode_ = hostNode;
    auto end = marqueeModel->CalculateEnd();
    EXPECT_EQ(end, 0.0f);
}

/**
 * @tc.name: MarqueePattern_ChangeAnimationPlayStatus001
 * @tc.desc: Test ChangeAnimationPlayStatus
 * @tc.type: FUNC
 */
HWTEST_F(MarqueePatternTestNg, MarqueePattern_ChangeAnimationPlayStatus001, TestSize.Level1)
{
    MarqueePattern marqueeModel;
    marqueeModel.ChangeAnimationPlayStatus();
    EXPECT_FALSE(marqueeModel.IsRunMarquee());
}

/**
 * @tc.name: MarqueePattern_UpdateNodeInitialPos001
 * @tc.desc: Test UpdateNodeInitialPos
 * @tc.type: FUNC
 */
HWTEST_F(MarqueePatternTestNg, MarqueePattern_UpdateNodeInitialPos001, TestSize.Level1)
{
    MarqueePattern marqueeModel;
    marqueeModel.UpdateNodeInitialPos();
    EXPECT_FALSE(marqueeModel.IsRunMarquee());
}

/**
 * @tc.name: MarqueePattern_UpdateNodeInitialPos002
 * @tc.desc: Test UpdateNodeInitialPos with cancel=true
 * @tc.type: FUNC
 */
HWTEST_F(MarqueePatternTestNg, MarqueePattern_UpdateNodeInitialPos002, TestSize.Level1)
{
    MarqueePattern marqueeModel;
    marqueeModel.UpdateNodeInitialPos(true);
    EXPECT_FALSE(marqueeModel.IsRunMarquee());
}

/**
 * @tc.name: MarqueePattern_ProcessVisibleAreaCallback001
 * @tc.desc: Test ProcessVisibleAreaCallback
 * @tc.type: FUNC
 */
HWTEST_F(MarqueePatternTestNg, MarqueePattern_ProcessVisibleAreaCallback001, TestSize.Level1)
{
    MarqueePattern marqueeModel;
    marqueeModel.ProcessVisibleAreaCallback();
    EXPECT_FALSE(marqueeModel.IsRunMarquee());
}

/**
 * @tc.name: MarqueePattern_PauseAnimation001
 * @tc.desc: Test PauseAnimation
 * @tc.type: FUNC
 */
HWTEST_F(MarqueePatternTestNg, MarqueePattern_PauseAnimation001, TestSize.Level1)
{
    MarqueePattern marqueeModel;
    marqueeModel.PauseAnimation();
    EXPECT_FALSE(marqueeModel.IsRunMarquee());
}

/**
 * @tc.name: MarqueePattern_ResumeAnimation001
 * @tc.desc: Test ResumeAnimation
 * @tc.type: FUNC
 */
HWTEST_F(MarqueePatternTestNg, MarqueePattern_ResumeAnimation001, TestSize.Level1)
{
    MarqueePattern marqueeModel;
    marqueeModel.ResumeAnimation();
    EXPECT_FALSE(marqueeModel.IsRunMarquee());
}

/**
 * @tc.name: MarqueePattern_GetTextDirection001
 * @tc.desc: Test GetTextDirection with LTR content
 * @tc.type: FUNC
 */
HWTEST_F(MarqueePatternTestNg, MarqueePattern_GetTextDirection001, TestSize.Level1)
{
    MarqueePattern marqueeModel;
    auto direction = marqueeModel.GetTextDirection("Hello World", TextDirection::LTR);
    EXPECT_EQ(direction, TextDirection::LTR);
}

/**
 * @tc.name: MarqueePattern_GetTextDirection002
 * @tc.desc: Test GetTextDirection with RTL content
 * @tc.type: FUNC
 */
HWTEST_F(MarqueePatternTestNg, MarqueePattern_GetTextDirection002, TestSize.Level1)
{
    MarqueePattern marqueeModel;
    auto direction = marqueeModel.GetTextDirection("\u0591Hello", TextDirection::LTR);
    EXPECT_EQ(direction, TextDirection::LTR);
}

/**
 * @tc.name: MarqueePattern_GetTextDirection003
 * @tc.desc: Test GetTextDirection with RTL parameter (should return RTL directly)
 * @tc.type: FUNC
 */
HWTEST_F(MarqueePatternTestNg, MarqueePattern_GetTextDirection003, TestSize.Level1)
{
    MarqueePattern marqueeModel;
    auto direction = marqueeModel.GetTextDirection("Hello World", TextDirection::RTL);
    EXPECT_EQ(direction, TextDirection::RTL);
}

/**
 * @tc.name: MarqueePattern_GetTextDirection004
 * @tc.desc: Test GetTextDirection with LTR parameter (should return LTR directly)
 * @tc.type: FUNC
 */
HWTEST_F(MarqueePatternTestNg, MarqueePattern_GetTextDirection004, TestSize.Level1)
{
    MarqueePattern marqueeModel;
    auto direction = marqueeModel.GetTextDirection("Hebrew text", TextDirection::LTR);
    EXPECT_EQ(direction, TextDirection::LTR);
}

/**
 * @tc.name: MarqueePattern_GetTextDirection005
 * @tc.desc: Test GetTextDirection with AUTO and text content (mock returns LTR)
 * @tc.type: FUNC
 */
HWTEST_F(MarqueePatternTestNg, MarqueePattern_GetTextDirection005, TestSize.Level1)
{
    MarqueePattern marqueeModel;
    // Due to mock TextLayoutadapter always returning false for RTL, this returns LTR
    auto direction = marqueeModel.GetTextDirection("\u05D0\u05D1\u05D2", TextDirection::AUTO);
    EXPECT_EQ(direction, TextDirection::LTR);
}

/**
 * @tc.name: MarqueePattern_GetTextDirection006
 * @tc.desc: Test GetTextDirection with AUTO and text content (mock returns LTR)
 * @tc.type: FUNC
 */
HWTEST_F(MarqueePatternTestNg, MarqueePattern_GetTextDirection006, TestSize.Level1)
{
    MarqueePattern marqueeModel;
    // Due to mock TextLayoutadapter always returning false for RTL, this returns LTR
    auto direction = marqueeModel.GetTextDirection("\u0627\u0628\u062A\u062B", TextDirection::AUTO);
    EXPECT_EQ(direction, TextDirection::LTR);
}

/**
 * @tc.name: MarqueePattern_GetTextDirection007
 * @tc.desc: Test GetTextDirection with empty string (should return default LTR)
 * @tc.type: FUNC
 */
HWTEST_F(MarqueePatternTestNg, MarqueePattern_GetTextDirection007, TestSize.Level1)
{
    MarqueePattern marqueeModel;
    auto direction = marqueeModel.GetTextDirection("", TextDirection::AUTO);
    EXPECT_EQ(direction, TextDirection::LTR);
}

/**
 * @tc.name: MarqueePattern_GetTextDirection008
 * @tc.desc: Test GetTextDirection with mixed text - LTR first
 * @tc.type: FUNC
 */
HWTEST_F(MarqueePatternTestNg, MarqueePattern_GetTextDirection008, TestSize.Level1)
{
    MarqueePattern marqueeModel;
    // LTR text first, then RTL - should return LTR (first detection wins)
    auto direction = marqueeModel.GetTextDirection("Hello\u05D0", TextDirection::AUTO);
    EXPECT_EQ(direction, TextDirection::LTR);
}

/**
 * @tc.name: MarqueePattern_GetTextDirection009
 * @tc.desc: Test GetTextDirection with mixed text - first char then LTR (mock returns LTR)
 * @tc.type: FUNC
 */
HWTEST_F(MarqueePatternTestNg, MarqueePattern_GetTextDirection009, TestSize.Level1)
{
    MarqueePattern marqueeModel;
    // Due to mock TextLayoutadapter always returning false for RTL, this returns LTR
    auto direction = marqueeModel.GetTextDirection("\u05D0Hello", TextDirection::AUTO);
    EXPECT_EQ(direction, TextDirection::LTR);
}

/**
 * @tc.name: MarqueePattern_GetTextDirection010
 * @tc.desc: Test GetTextDirection with mixed text - first char then LTR (mock returns LTR)
 * @tc.type: FUNC
 */
HWTEST_F(MarqueePatternTestNg, MarqueePattern_GetTextDirection010, TestSize.Level1)
{
    MarqueePattern marqueeModel;
    // Due to mock TextLayoutadapter always returning false for RTL, this returns LTR
    auto direction = marqueeModel.GetTextDirection("\u0627Hello", TextDirection::AUTO);
    EXPECT_EQ(direction, TextDirection::LTR);
}

/**
 * @tc.name: MarqueePattern_GetTextDirection011
 * @tc.desc: Test GetTextDirection with AUTO and LTR text content
 * @tc.type: FUNC
 */
HWTEST_F(MarqueePatternTestNg, MarqueePattern_GetTextDirection011, TestSize.Level1)
{
    MarqueePattern marqueeModel;
    auto direction = marqueeModel.GetTextDirection("Left to Right text", TextDirection::AUTO);
    EXPECT_EQ(direction, TextDirection::LTR);
}

/**
 * @tc.name: MarqueePattern_GetTextDirection012
 * @tc.desc: Test GetTextDirection with ASCII characters (should detect LTR)
 * @tc.type: FUNC
 */
HWTEST_F(MarqueePatternTestNg, MarqueePattern_GetTextDirection012, TestSize.Level1)
{
    MarqueePattern marqueeModel;
    auto direction = marqueeModel.GetTextDirection("ABC123", TextDirection::AUTO);
    EXPECT_EQ(direction, TextDirection::LTR);
}

/**
 * @tc.name: MarqueePattern_GetTextDirection013
 * @tc.desc: Test GetTextDirection with special character (mock returns LTR)
 * @tc.type: FUNC
 */
HWTEST_F(MarqueePatternTestNg, MarqueePattern_GetTextDirection013, TestSize.Level1)
{
    MarqueePattern marqueeModel;
    // Due to mock TextLayoutadapter always returning false for RTL, this returns LTR
    auto direction = marqueeModel.GetTextDirection("\u05D0", TextDirection::AUTO);
    EXPECT_EQ(direction, TextDirection::LTR);
}

/**
 * @tc.name: MarqueePattern_GetTextDirection014
 * @tc.desc: Test GetTextDirection with special character (mock returns LTR)
 * @tc.type: FUNC
 */
HWTEST_F(MarqueePatternTestNg, MarqueePattern_GetTextDirection014, TestSize.Level1)
{
    MarqueePattern marqueeModel;
    // Due to mock TextLayoutadapter always returning false for RTL, this returns LTR
    auto direction = marqueeModel.GetTextDirection("\u0627", TextDirection::AUTO);
    EXPECT_EQ(direction, TextDirection::LTR);
}

/**
 * @tc.name: MarqueePattern_GetTextDirection015
 * @tc.desc: Test GetTextDirection with multiple characters (mock returns LTR)
 * @tc.type: FUNC
 */
HWTEST_F(MarqueePatternTestNg, MarqueePattern_GetTextDirection015, TestSize.Level1)
{
    MarqueePattern marqueeModel;
    // Due to mock TextLayoutadapter always returning false for RTL, this returns LTR
    auto direction = marqueeModel.GetTextDirection("\u05D0\u05D1\u05D2\u05D3\u05D4", TextDirection::AUTO);
    EXPECT_EQ(direction, TextDirection::LTR);
}

/**
 * @tc.name: MarqueePattern_GetTextDirection016
 * @tc.desc: Test GetTextDirection with multiple characters (mock returns LTR)
 * @tc.type: FUNC
 */
HWTEST_F(MarqueePatternTestNg, MarqueePattern_GetTextDirection016, TestSize.Level1)
{
    MarqueePattern marqueeModel;
    // Due to mock TextLayoutadapter always returning false for RTL, this returns LTR
    auto direction = marqueeModel.GetTextDirection("\u0627\u0628\u062C\u062F\u0647", TextDirection::AUTO);
    EXPECT_EQ(direction, TextDirection::LTR);
}

/**
 * @tc.name: MarqueePattern_GetTextDirection017
 * @tc.desc: Test GetTextDirection with numbers only (should detect LTR)
 * @tc.type: FUNC
 */
HWTEST_F(MarqueePatternTestNg, MarqueePattern_GetTextDirection017, TestSize.Level1)
{
    MarqueePattern marqueeModel;
    auto direction = marqueeModel.GetTextDirection("123456789", TextDirection::AUTO);
    EXPECT_EQ(direction, TextDirection::LTR);
}

/**
 * @tc.name: MarqueePattern_GetTextDirection018
 * @tc.desc: Test GetTextDirection with whitespace only (should return default)
 * @tc.type: FUNC
 */
HWTEST_F(MarqueePatternTestNg, MarqueePattern_GetTextDirection018, TestSize.Level1)
{
    MarqueePattern marqueeModel;
    auto direction = marqueeModel.GetTextDirection("   ", TextDirection::AUTO);
    EXPECT_EQ(direction, TextDirection::LTR);
}

/**
 * @tc.name: MarqueePattern_GetTextDirection019
 * @tc.desc: Test GetTextDirection with mixed scripts (mock returns LTR)
 * @tc.type: FUNC
 */
HWTEST_F(MarqueePatternTestNg, MarqueePattern_GetTextDirection019, TestSize.Level1)
{
    MarqueePattern marqueeModel;
    // Due to mock TextLayoutadapter always returning false for RTL, this returns LTR
    auto direction = marqueeModel.GetTextDirection("\u05D0\u0627\u05D1\u0628", TextDirection::AUTO);
    EXPECT_EQ(direction, TextDirection::LTR);
}

/**
 * @tc.name: MarqueePattern_GetTextDirection020
 * @tc.desc: Test GetTextDirection with text content and RTL parameter
 * @tc.type: FUNC
 */
HWTEST_F(MarqueePatternTestNg, MarqueePattern_GetTextDirection020, TestSize.Level1)
{
    MarqueePattern marqueeModel;
    auto direction = marqueeModel.GetTextDirection("\u05D0\u05D1", TextDirection::RTL);
    EXPECT_EQ(direction, TextDirection::RTL);
}

/**
 * @tc.name: MarqueePattern_CalcAnimationStart001
 * @tc.desc: Test CalcAnimationStart with first marquee at visibleAreaStart, directionMoveLeft=true, condition true
 * @tc.type: FUNC
 */
HWTEST_F(MarqueePatternTestNg, MarqueePattern_CalcAnimationStart001, TestSize.Level1)
{
    RefPtr<Pattern> pattern = AceType::MakeRefPtr<MarqueePattern>();
    auto frameNode = FrameNode::CreateFrameNode("Marquee", 1, pattern, false);
    auto layoutProperty = frameNode->GetLayoutProperty<MarqueeLayoutProperty>();
    RefPtr<GeometryNode> geoNode = AceType::MakeRefPtr<GeometryNode>();
    geoNode->SetFrameSize(SizeF(300.0f, 50.0f));
    frameNode->SetGeometryNode(geoNode);

    auto textFrameNode = FrameNode::CreateFrameNode("Text", 2, AceType::MakeRefPtr<TextPattern>(), false);
    RefPtr<GeometryNode> textGeo = AceType::MakeRefPtr<GeometryNode>();
    textGeo->SetFrameSize(SizeF(200.0f, 30.0f));
    textFrameNode->SetGeometryNode(textGeo);
    frameNode->AddChild(textFrameNode);

    WeakPtr<FrameNode> hostNode(frameNode);
    auto marqueeModel = AceType::MakeRefPtr<MarqueePattern>();
    marqueeModel->frameNode_ = hostNode;

    float firstStart = 0.0f;
    float secondStart = 0.0f;
    float textTotalLen = 200.0f;
    float aniStartPos = 200.0f;
    float aniEndPos = -300.0f;
    bool directionMoveLeft = true;

    marqueeModel->CalcAnimationStart(firstStart, secondStart, textTotalLen, aniStartPos, aniEndPos, directionMoveLeft);

    EXPECT_EQ(secondStart, 200.0f);
}

/**
 * @tc.name: MarqueePattern_CalcAnimationStart002
 * @tc.desc: Test CalcAnimationStart with first marquee at visibleAreaStart, directionMoveLeft=true, condition false
 * @tc.type: FUNC
 */
HWTEST_F(MarqueePatternTestNg, MarqueePattern_CalcAnimationStart002, TestSize.Level1)
{
    RefPtr<Pattern> pattern = AceType::MakeRefPtr<MarqueePattern>();
    auto frameNode = FrameNode::CreateFrameNode("Marquee", 1, pattern, false);
    auto layoutProperty = frameNode->GetLayoutProperty<MarqueeLayoutProperty>();
    RefPtr<GeometryNode> geoNode = AceType::MakeRefPtr<GeometryNode>();
    geoNode->SetFrameSize(SizeF(300.0f, 50.0f));
    frameNode->SetGeometryNode(geoNode);

    auto textFrameNode = FrameNode::CreateFrameNode("Text", 2, AceType::MakeRefPtr<TextPattern>(), false);
    RefPtr<GeometryNode> textGeo = AceType::MakeRefPtr<GeometryNode>();
    textGeo->SetFrameSize(SizeF(200.0f, 30.0f));
    textFrameNode->SetGeometryNode(textGeo);
    frameNode->AddChild(textFrameNode);

    WeakPtr<FrameNode> hostNode(frameNode);
    auto marqueeModel = AceType::MakeRefPtr<MarqueePattern>();
    marqueeModel->frameNode_ = hostNode;

    float firstStart = 0.0f;
    float secondStart = 0.0f;
    float textTotalLen = 200.0f;
    float aniStartPos = 100.0f;
    float aniEndPos = -100.0f;
    bool directionMoveLeft = true;

    marqueeModel->CalcAnimationStart(firstStart, secondStart, textTotalLen, aniStartPos, aniEndPos, directionMoveLeft);

    EXPECT_EQ(secondStart, -200.0f);
}

/**
 * @tc.name: MarqueePattern_CalcAnimationStart003
 * @tc.desc: Test CalcAnimationStart with first marquee at visibleAreaStart, directionMoveLeft=false, condition true
 * @tc.type: FUNC
 */
HWTEST_F(MarqueePatternTestNg, MarqueePattern_CalcAnimationStart003, TestSize.Level1)
{
    RefPtr<Pattern> pattern = AceType::MakeRefPtr<MarqueePattern>();
    auto frameNode = FrameNode::CreateFrameNode("Marquee", 1, pattern, false);
    auto layoutProperty = frameNode->GetLayoutProperty<MarqueeLayoutProperty>();
    RefPtr<GeometryNode> geoNode = AceType::MakeRefPtr<GeometryNode>();
    geoNode->SetFrameSize(SizeF(300.0f, 50.0f));
    frameNode->SetGeometryNode(geoNode);

    auto textFrameNode = FrameNode::CreateFrameNode("Text", 2, AceType::MakeRefPtr<TextPattern>(), false);
    RefPtr<GeometryNode> textGeo = AceType::MakeRefPtr<GeometryNode>();
    textGeo->SetFrameSize(SizeF(200.0f, 30.0f));
    textFrameNode->SetGeometryNode(textGeo);
    frameNode->AddChild(textFrameNode);

    WeakPtr<FrameNode> hostNode(frameNode);
    auto marqueeModel = AceType::MakeRefPtr<MarqueePattern>();
    marqueeModel->frameNode_ = hostNode;

    float firstStart = 0.0f;
    float secondStart = 0.0f;
    float textTotalLen = 200.0f;
    float aniStartPos = 100.0f;
    float aniEndPos = 300.0f;
    bool directionMoveLeft = false;

    marqueeModel->CalcAnimationStart(firstStart, secondStart, textTotalLen, aniStartPos, aniEndPos, directionMoveLeft);

    EXPECT_EQ(secondStart, 200.0f);
}

/**
 * @tc.name: MarqueePattern_CalcAnimationStart004
 * @tc.desc: Test CalcAnimationStart with first marquee at visibleAreaStart, directionMoveLeft=false, condition false
 * @tc.type: FUNC
 */
HWTEST_F(MarqueePatternTestNg, MarqueePattern_CalcAnimationStart004, TestSize.Level1)
{
    RefPtr<Pattern> pattern = AceType::MakeRefPtr<MarqueePattern>();
    auto frameNode = FrameNode::CreateFrameNode("Marquee", 1, pattern, false);
    auto layoutProperty = frameNode->GetLayoutProperty<MarqueeLayoutProperty>();
    RefPtr<GeometryNode> geoNode = AceType::MakeRefPtr<GeometryNode>();
    geoNode->SetFrameSize(SizeF(300.0f, 50.0f));
    frameNode->SetGeometryNode(geoNode);

    auto textFrameNode = FrameNode::CreateFrameNode("Text", 2, AceType::MakeRefPtr<TextPattern>(), false);
    RefPtr<GeometryNode> textGeo = AceType::MakeRefPtr<GeometryNode>();
    textGeo->SetFrameSize(SizeF(200.0f, 30.0f));
    textFrameNode->SetGeometryNode(textGeo);
    frameNode->AddChild(textFrameNode);

    WeakPtr<FrameNode> hostNode(frameNode);
    auto marqueeModel = AceType::MakeRefPtr<MarqueePattern>();
    marqueeModel->frameNode_ = hostNode;

    float firstStart = 0.0f;
    float secondStart = 0.0f;
    float textTotalLen = 200.0f;
    float aniStartPos = -100.0f;
    float aniEndPos = 100.0f;
    bool directionMoveLeft = false;

    marqueeModel->CalcAnimationStart(firstStart, secondStart, textTotalLen, aniStartPos, aniEndPos, directionMoveLeft);

    EXPECT_EQ(secondStart, 200.0f);
}

/**
 * @tc.name: MarqueePattern_CalcAnimationStart005
 * @tc.desc: Test CalcAnimationStart with both marquees to the left of visible area, directionMoveLeft=true
 * @tc.type: FUNC
 */
HWTEST_F(MarqueePatternTestNg, MarqueePattern_CalcAnimationStart005, TestSize.Level1)
{
    RefPtr<Pattern> pattern = AceType::MakeRefPtr<MarqueePattern>();
    auto frameNode = FrameNode::CreateFrameNode("Marquee", 1, pattern, false);
    auto layoutProperty = frameNode->GetLayoutProperty<MarqueeLayoutProperty>();
    RefPtr<GeometryNode> geoNode = AceType::MakeRefPtr<GeometryNode>();
    geoNode->SetFrameSize(SizeF(300.0f, 50.0f));
    frameNode->SetGeometryNode(geoNode);

    auto textFrameNode = FrameNode::CreateFrameNode("Text", 2, AceType::MakeRefPtr<TextPattern>(), false);
    RefPtr<GeometryNode> textGeo = AceType::MakeRefPtr<GeometryNode>();
    textGeo->SetFrameSize(SizeF(200.0f, 30.0f));
    textFrameNode->SetGeometryNode(textGeo);
    frameNode->AddChild(textFrameNode);

    WeakPtr<FrameNode> hostNode(frameNode);
    auto marqueeModel = AceType::MakeRefPtr<MarqueePattern>();
    marqueeModel->frameNode_ = hostNode;

    float firstStart = -400.0f;
    float secondStart = -400.0f;
    float textTotalLen = 200.0f;
    float aniStartPos = 100.0f;
    float aniEndPos = -300.0f;
    bool directionMoveLeft = true;

    marqueeModel->CalcAnimationStart(firstStart, secondStart, textTotalLen, aniStartPos, aniEndPos, directionMoveLeft);

    EXPECT_EQ(secondStart, -200.0f);
}

/**
 * @tc.name: MarqueePattern_CalcAnimationStart006
 * @tc.desc: Test CalcAnimationStart with second marquee at visibleAreaStart, directionMoveLeft=true, condition true
 * @tc.type: FUNC
 */
HWTEST_F(MarqueePatternTestNg, MarqueePattern_CalcAnimationStart006, TestSize.Level1)
{
    RefPtr<Pattern> pattern = AceType::MakeRefPtr<MarqueePattern>();
    auto frameNode = FrameNode::CreateFrameNode("Marquee", 1, pattern, false);
    auto layoutProperty = frameNode->GetLayoutProperty<MarqueeLayoutProperty>();
    RefPtr<GeometryNode> geoNode = AceType::MakeRefPtr<GeometryNode>();
    geoNode->SetFrameSize(SizeF(300.0f, 50.0f));
    frameNode->SetGeometryNode(geoNode);

    auto textFrameNode = FrameNode::CreateFrameNode("Text", 2, AceType::MakeRefPtr<TextPattern>(), false);
    RefPtr<GeometryNode> textGeo = AceType::MakeRefPtr<GeometryNode>();
    textGeo->SetFrameSize(SizeF(200.0f, 30.0f));
    textFrameNode->SetGeometryNode(textGeo);
    frameNode->AddChild(textFrameNode);

    WeakPtr<FrameNode> hostNode(frameNode);
    auto marqueeModel = AceType::MakeRefPtr<MarqueePattern>();
    marqueeModel->frameNode_ = hostNode;

    float firstStart = 300.0f;
    float secondStart = 0.0f;
    float textTotalLen = 200.0f;
    float aniStartPos = -100.0f;
    float aniEndPos = -300.0f;
    bool directionMoveLeft = true;

    marqueeModel->CalcAnimationStart(firstStart, secondStart, textTotalLen, aniStartPos, aniEndPos, directionMoveLeft);

    EXPECT_EQ(firstStart, 300.0f);
}

/**
 * @tc.name: MarqueePattern_CalcAnimationStart007
 * @tc.desc: Test CalcAnimationStart with second marquee at visibleAreaStart, directionMoveLeft=true, condition false
 * @tc.type: FUNC
 */
HWTEST_F(MarqueePatternTestNg, MarqueePattern_CalcAnimationStart007, TestSize.Level1)
{
    RefPtr<Pattern> pattern = AceType::MakeRefPtr<MarqueePattern>();
    auto frameNode = FrameNode::CreateFrameNode("Marquee", 1, pattern, false);
    auto layoutProperty = frameNode->GetLayoutProperty<MarqueeLayoutProperty>();
    RefPtr<GeometryNode> geoNode = AceType::MakeRefPtr<GeometryNode>();
    geoNode->SetFrameSize(SizeF(300.0f, 50.0f));
    frameNode->SetGeometryNode(geoNode);

    auto textFrameNode = FrameNode::CreateFrameNode("Text", 2, AceType::MakeRefPtr<TextPattern>(), false);
    RefPtr<GeometryNode> textGeo = AceType::MakeRefPtr<GeometryNode>();
    textGeo->SetFrameSize(SizeF(200.0f, 30.0f));
    textFrameNode->SetGeometryNode(textGeo);
    frameNode->AddChild(textFrameNode);

    WeakPtr<FrameNode> hostNode(frameNode);
    auto marqueeModel = AceType::MakeRefPtr<MarqueePattern>();
    marqueeModel->frameNode_ = hostNode;

    float firstStart = 300.0f;
    float secondStart = 0.0f;
    float textTotalLen = 200.0f;
    float aniStartPos = 100.0f;
    float aniEndPos = -100.0f;
    bool directionMoveLeft = true;

    marqueeModel->CalcAnimationStart(firstStart, secondStart, textTotalLen, aniStartPos, aniEndPos, directionMoveLeft);

    EXPECT_EQ(firstStart, 300.0f);
}

/**
 * @tc.name: MarqueePattern_CalcAnimationStart008
 * @tc.desc: Test CalcAnimationStart with second marquee at visibleAreaStart, directionMoveLeft=false, condition false
 * @tc.type: FUNC
 */
HWTEST_F(MarqueePatternTestNg, MarqueePattern_CalcAnimationStart008, TestSize.Level1)
{
    RefPtr<Pattern> pattern = AceType::MakeRefPtr<MarqueePattern>();
    auto frameNode = FrameNode::CreateFrameNode("Marquee", 1, pattern, false);
    auto layoutProperty = frameNode->GetLayoutProperty<MarqueeLayoutProperty>();
    RefPtr<GeometryNode> geoNode = AceType::MakeRefPtr<GeometryNode>();
    geoNode->SetFrameSize(SizeF(300.0f, 50.0f));
    frameNode->SetGeometryNode(geoNode);

    auto textFrameNode = FrameNode::CreateFrameNode("Text", 2, AceType::MakeRefPtr<TextPattern>(), false);
    RefPtr<GeometryNode> textGeo = AceType::MakeRefPtr<GeometryNode>();
    textGeo->SetFrameSize(SizeF(200.0f, 30.0f));
    textFrameNode->SetGeometryNode(textGeo);
    frameNode->AddChild(textFrameNode);

    WeakPtr<FrameNode> hostNode(frameNode);
    auto marqueeModel = AceType::MakeRefPtr<MarqueePattern>();
    marqueeModel->frameNode_ = hostNode;

    float firstStart = -300.0f;
    float secondStart = 0.0f;
    float textTotalLen = 200.0f;
    float aniStartPos = -100.0f;
    float aniEndPos = 300.0f;
    bool directionMoveLeft = false;

    marqueeModel->CalcAnimationStart(firstStart, secondStart, textTotalLen, aniStartPos, aniEndPos, directionMoveLeft);

    EXPECT_EQ(firstStart, 200.0f);
}

/**
 * @tc.name: MarqueePattern_CalcAnimationStart009
 * @tc.desc: Test CalcAnimationStart with both marquees outside visible area, directionMoveLeft=false
 * @tc.type: FUNC
 */
HWTEST_F(MarqueePatternTestNg, MarqueePattern_CalcAnimationStart009, TestSize.Level1)
{
    RefPtr<Pattern> pattern = AceType::MakeRefPtr<MarqueePattern>();
    auto frameNode = FrameNode::CreateFrameNode("Marquee", 1, pattern, false);
    auto layoutProperty = frameNode->GetLayoutProperty<MarqueeLayoutProperty>();
    RefPtr<GeometryNode> geoNode = AceType::MakeRefPtr<GeometryNode>();
    geoNode->SetFrameSize(SizeF(300.0f, 50.0f));
    frameNode->SetGeometryNode(geoNode);

    auto textFrameNode = FrameNode::CreateFrameNode("Text", 2, AceType::MakeRefPtr<TextPattern>(), false);
    RefPtr<GeometryNode> textGeo = AceType::MakeRefPtr<GeometryNode>();
    textGeo->SetFrameSize(SizeF(200.0f, 30.0f));
    textFrameNode->SetGeometryNode(textGeo);
    frameNode->AddChild(textFrameNode);

    WeakPtr<FrameNode> hostNode(frameNode);
    auto marqueeModel = AceType::MakeRefPtr<MarqueePattern>();
    marqueeModel->frameNode_ = hostNode;

    float firstStart = -300.0f;
    float secondStart = -500.0f;
    float textTotalLen = 200.0f;
    float aniStartPos = -200.0f;
    float aniEndPos = 100.0f;
    bool directionMoveLeft = false;

    marqueeModel->CalcAnimationStart(firstStart, secondStart, textTotalLen, aniStartPos, aniEndPos, directionMoveLeft);

    EXPECT_EQ(firstStart, -300.0f);
}

/**
 * @tc.name: MarqueePattern_CalcAnimationStart010
 * @tc.desc: Test CalcAnimationStart with both marquees outside visible area, directionMoveLeft=true
 * @tc.type: FUNC
 */
HWTEST_F(MarqueePatternTestNg, MarqueePattern_CalcAnimationStart010, TestSize.Level1)
{
    RefPtr<Pattern> pattern = AceType::MakeRefPtr<MarqueePattern>();
    auto frameNode = FrameNode::CreateFrameNode("Marquee", 1, pattern, false);
    auto layoutProperty = frameNode->GetLayoutProperty<MarqueeLayoutProperty>();
    RefPtr<GeometryNode> geoNode = AceType::MakeRefPtr<GeometryNode>();
    geoNode->SetFrameSize(SizeF(300.0f, 50.0f));
    frameNode->SetGeometryNode(geoNode);

    auto textFrameNode = FrameNode::CreateFrameNode("Text", 2, AceType::MakeRefPtr<TextPattern>(), false);
    RefPtr<GeometryNode> textGeo = AceType::MakeRefPtr<GeometryNode>();
    textGeo->SetFrameSize(SizeF(200.0f, 30.0f));
    textFrameNode->SetGeometryNode(textGeo);
    frameNode->AddChild(textFrameNode);

    WeakPtr<FrameNode> hostNode(frameNode);
    auto marqueeModel = AceType::MakeRefPtr<MarqueePattern>();
    marqueeModel->frameNode_ = hostNode;

    float firstStart = 400.0f;
    float secondStart = 600.0f;
    float textTotalLen = 200.0f;
    float aniStartPos = 100.0f;
    float aniEndPos = -300.0f;
    bool directionMoveLeft = true;

    marqueeModel->CalcAnimationStart(firstStart, secondStart, textTotalLen, aniStartPos, aniEndPos, directionMoveLeft);

    EXPECT_EQ(firstStart, 400.0f);
}

/**
 * @tc.name: MarqueePattern_CalcAnimationStart011
 * @tc.desc: Test CalcAnimationStart with both marquees outside visible area, directionMoveLeft=false
 * @tc.type: FUNC
 */
HWTEST_F(MarqueePatternTestNg, MarqueePattern_CalcAnimationStart011, TestSize.Level1)
{
    RefPtr<Pattern> pattern = AceType::MakeRefPtr<MarqueePattern>();
    auto frameNode = FrameNode::CreateFrameNode("Marquee", 1, pattern, false);
    auto layoutProperty = frameNode->GetLayoutProperty<MarqueeLayoutProperty>();
    RefPtr<GeometryNode> geoNode = AceType::MakeRefPtr<GeometryNode>();
    geoNode->SetFrameSize(SizeF(300.0f, 50.0f));
    frameNode->SetGeometryNode(geoNode);

    auto textFrameNode = FrameNode::CreateFrameNode("Text", 2, AceType::MakeRefPtr<TextPattern>(), false);
    RefPtr<GeometryNode> textGeo = AceType::MakeRefPtr<GeometryNode>();
    textGeo->SetFrameSize(SizeF(200.0f, 30.0f));
    textFrameNode->SetGeometryNode(textGeo);
    frameNode->AddChild(textFrameNode);

    WeakPtr<FrameNode> hostNode(frameNode);
    auto marqueeModel = AceType::MakeRefPtr<MarqueePattern>();
    marqueeModel->frameNode_ = hostNode;

    float firstStart = -400.0f;
    float secondStart = -600.0f;
    float textTotalLen = 200.0f;
    float aniStartPos = 100.0f;
    float aniEndPos = 300.0f;
    bool directionMoveLeft = false;

    marqueeModel->CalcAnimationStart(firstStart, secondStart, textTotalLen, aniStartPos, aniEndPos, directionMoveLeft);

    EXPECT_EQ(firstStart, -400.0f);
}

/**
 * @tc.name: MarqueePattern_CalcAnimationStart012
 * @tc.desc: Test CalcAnimationStart with first marquee to the right of visible area, directionMoveLeft=true,
 *  condition true
 * @tc.type: FUNC
 */
HWTEST_F(MarqueePatternTestNg, MarqueePattern_CalcAnimationStart012, TestSize.Level1)
{
    RefPtr<Pattern> pattern = AceType::MakeRefPtr<MarqueePattern>();
    auto frameNode = FrameNode::CreateFrameNode("Marquee", 1, pattern, false);
    auto layoutProperty = frameNode->GetLayoutProperty<MarqueeLayoutProperty>();
    RefPtr<GeometryNode> geoNode = AceType::MakeRefPtr<GeometryNode>();
    geoNode->SetFrameSize(SizeF(300.0f, 50.0f));
    frameNode->SetGeometryNode(geoNode);

    auto textFrameNode = FrameNode::CreateFrameNode("Text", 2, AceType::MakeRefPtr<TextPattern>(), false);
    RefPtr<GeometryNode> textGeo = AceType::MakeRefPtr<GeometryNode>();
    textGeo->SetFrameSize(SizeF(200.0f, 30.0f));
    textFrameNode->SetGeometryNode(textGeo);
    frameNode->AddChild(textFrameNode);

    WeakPtr<FrameNode> hostNode(frameNode);
    auto marqueeModel = AceType::MakeRefPtr<MarqueePattern>();
    marqueeModel->frameNode_ = hostNode;

    float firstStart = 400.0f;
    float secondStart = 600.0f;
    float textTotalLen = 200.0f;
    float aniStartPos = 800.0f;
    float aniEndPos = -300.0f;
    bool directionMoveLeft = true;

    marqueeModel->CalcAnimationStart(firstStart, secondStart, textTotalLen, aniStartPos, aniEndPos, directionMoveLeft);

    EXPECT_EQ(secondStart, 600.0f);
}

/**
 * @tc.name: MarqueePattern_CalcAnimationStart013
 * @tc.desc: Test CalcAnimationStart with no marquee in visible area, directionMoveLeft=true, condition false
 * @tc.type: FUNC
 */
HWTEST_F(MarqueePatternTestNg, MarqueePattern_CalcAnimationStart013, TestSize.Level1)
{
    RefPtr<Pattern> pattern = AceType::MakeRefPtr<MarqueePattern>();
    auto frameNode = FrameNode::CreateFrameNode("Marquee", 1, pattern, false);
    auto layoutProperty = frameNode->GetLayoutProperty<MarqueeLayoutProperty>();
    RefPtr<GeometryNode> geoNode = AceType::MakeRefPtr<GeometryNode>();
    geoNode->SetFrameSize(SizeF(300.0f, 50.0f));
    frameNode->SetGeometryNode(geoNode);

    auto textFrameNode = FrameNode::CreateFrameNode("Text", 2, AceType::MakeRefPtr<TextPattern>(), false);
    RefPtr<GeometryNode> textGeo = AceType::MakeRefPtr<GeometryNode>();
    textGeo->SetFrameSize(SizeF(200.0f, 30.0f));
    textFrameNode->SetGeometryNode(textGeo);
    frameNode->AddChild(textFrameNode);

    WeakPtr<FrameNode> hostNode(frameNode);
    auto marqueeModel = AceType::MakeRefPtr<MarqueePattern>();
    marqueeModel->frameNode_ = hostNode;

    float firstStart = 400.0f;
    float secondStart = 0.0f;
    float textTotalLen = 200.0f;
    float aniStartPos = 100.0f;
    float aniEndPos = -100.0f;
    bool directionMoveLeft = true;

    marqueeModel->CalcAnimationStart(firstStart, secondStart, textTotalLen, aniStartPos, aniEndPos, directionMoveLeft);

    EXPECT_EQ(secondStart, 0.0f);
}

/**
 * @tc.name: MarqueePattern_CalcAnimationStart014
 * @tc.desc: Test CalcAnimationStart with both marquees outside visible area, directionMoveLeft=false, condition true
 * @tc.type: FUNC
 */
HWTEST_F(MarqueePatternTestNg, MarqueePattern_CalcAnimationStart014, TestSize.Level1)
{
    RefPtr<Pattern> pattern = AceType::MakeRefPtr<MarqueePattern>();
    auto frameNode = FrameNode::CreateFrameNode("Marquee", 1, pattern, false);
    auto layoutProperty = frameNode->GetLayoutProperty<MarqueeLayoutProperty>();
    RefPtr<GeometryNode> geoNode = AceType::MakeRefPtr<GeometryNode>();
    geoNode->SetFrameSize(SizeF(300.0f, 50.0f));
    frameNode->SetGeometryNode(geoNode);

    auto textFrameNode = FrameNode::CreateFrameNode("Text", 2, AceType::MakeRefPtr<TextPattern>(), false);
    RefPtr<GeometryNode> textGeo = AceType::MakeRefPtr<GeometryNode>();
    textGeo->SetFrameSize(SizeF(200.0f, 30.0f));
    textFrameNode->SetGeometryNode(textGeo);
    frameNode->AddChild(textFrameNode);

    WeakPtr<FrameNode> hostNode(frameNode);
    auto marqueeModel = AceType::MakeRefPtr<MarqueePattern>();
    marqueeModel->frameNode_ = hostNode;

    float firstStart = -400.0f;
    float secondStart = -600.0f;
    float textTotalLen = 200.0f;
    float aniStartPos = -700.0f;
    float aniEndPos = 300.0f;
    bool directionMoveLeft = false;

    marqueeModel->CalcAnimationStart(firstStart, secondStart, textTotalLen, aniStartPos, aniEndPos, directionMoveLeft);

    EXPECT_EQ(secondStart, -600.0f);
}

/**
 * @tc.name: MarqueePattern_CalcAnimationStart015
 * @tc.desc: Test CalcAnimationStart with both marquees outside visible area, directionMoveLeft=false, condition false
 * @tc.type: FUNC
 */
HWTEST_F(MarqueePatternTestNg, MarqueePattern_CalcAnimationStart015, TestSize.Level1)
{
    RefPtr<Pattern> pattern = AceType::MakeRefPtr<MarqueePattern>();
    auto frameNode = FrameNode::CreateFrameNode("Marquee", 1, pattern, false);
    auto layoutProperty = frameNode->GetLayoutProperty<MarqueeLayoutProperty>();
    RefPtr<GeometryNode> geoNode = AceType::MakeRefPtr<GeometryNode>();
    geoNode->SetFrameSize(SizeF(300.0f, 50.0f));
    frameNode->SetGeometryNode(geoNode);

    auto textFrameNode = FrameNode::CreateFrameNode("Text", 2, AceType::MakeRefPtr<TextPattern>(), false);
    RefPtr<GeometryNode> textGeo = AceType::MakeRefPtr<GeometryNode>();
    textGeo->SetFrameSize(SizeF(200.0f, 30.0f));
    textFrameNode->SetGeometryNode(textGeo);
    frameNode->AddChild(textFrameNode);

    WeakPtr<FrameNode> hostNode(frameNode);
    auto marqueeModel = AceType::MakeRefPtr<MarqueePattern>();
    marqueeModel->frameNode_ = hostNode;

    float firstStart = -400.0f;
    float secondStart = -600.0f;
    float textTotalLen = 200.0f;
    float aniStartPos = 100.0f;
    float aniEndPos = 300.0f;
    bool directionMoveLeft = false;

    marqueeModel->CalcAnimationStart(firstStart, secondStart, textTotalLen, aniStartPos, aniEndPos, directionMoveLeft);

    EXPECT_EQ(secondStart, -200.0f);
}

/**
 * @tc.name: MarqueePattern_CalcAnimationStart016
 * @tc.desc: Test CalcAnimationStart with small visible area
 * @tc.type: FUNC
 */
HWTEST_F(MarqueePatternTestNg, MarqueePattern_CalcAnimationStart016, TestSize.Level1)
{
    RefPtr<Pattern> pattern = AceType::MakeRefPtr<MarqueePattern>();
    auto frameNode = FrameNode::CreateFrameNode("Marquee", 1, pattern, false);
    auto layoutProperty = frameNode->GetLayoutProperty<MarqueeLayoutProperty>();
    RefPtr<GeometryNode> geoNode = AceType::MakeRefPtr<GeometryNode>();
    geoNode->SetFrameSize(SizeF(200.0f, 50.0f));
    frameNode->SetGeometryNode(geoNode);

    auto textFrameNode = FrameNode::CreateFrameNode("Text", 2, AceType::MakeRefPtr<TextPattern>(), false);
    RefPtr<GeometryNode> textGeo = AceType::MakeRefPtr<GeometryNode>();
    textGeo->SetFrameSize(SizeF(200.0f, 30.0f));
    textFrameNode->SetGeometryNode(textGeo);
    frameNode->AddChild(textFrameNode);

    WeakPtr<FrameNode> hostNode(frameNode);
    auto marqueeModel = AceType::MakeRefPtr<MarqueePattern>();
    marqueeModel->frameNode_ = hostNode;

    float firstStart = 0.0f;
    float secondStart = 0.0f;
    float textTotalLen = 200.0f;
    float aniStartPos = 200.0f;
    float aniEndPos = -300.0f;
    bool directionMoveLeft = true;

    marqueeModel->CalcAnimationStart(firstStart, secondStart, textTotalLen, aniStartPos, aniEndPos, directionMoveLeft);

    EXPECT_EQ(secondStart, 200.0f);
}

/**
 * @tc.name: MarqueePattern_CalcAnimationStart017
 * @tc.desc: Test CalcAnimationStart with textTotalLen equal to boundary condition, directionMoveLeft=true
 * @tc.type: FUNC
 */
HWTEST_F(MarqueePatternTestNg, MarqueePattern_CalcAnimationStart017, TestSize.Level1)
{
    RefPtr<Pattern> pattern = AceType::MakeRefPtr<MarqueePattern>();
    auto frameNode = FrameNode::CreateFrameNode("Marquee", 1, pattern, false);
    auto layoutProperty = frameNode->GetLayoutProperty<MarqueeLayoutProperty>();
    RefPtr<GeometryNode> geoNode = AceType::MakeRefPtr<GeometryNode>();
    geoNode->SetFrameSize(SizeF(300.0f, 50.0f));
    frameNode->SetGeometryNode(geoNode);

    auto textFrameNode = FrameNode::CreateFrameNode("Text", 2, AceType::MakeRefPtr<TextPattern>(), false);
    RefPtr<GeometryNode> textGeo = AceType::MakeRefPtr<GeometryNode>();
    textGeo->SetFrameSize(SizeF(100.0f, 30.0f));
    textFrameNode->SetGeometryNode(textGeo);
    frameNode->AddChild(textFrameNode);

    WeakPtr<FrameNode> hostNode(frameNode);
    auto marqueeModel = AceType::MakeRefPtr<MarqueePattern>();
    marqueeModel->frameNode_ = hostNode;

    float firstStart = 0.0f;
    float secondStart = 0.0f;
    float textTotalLen = 100.0f;
    float aniStartPos = 150.0f;
    float aniEndPos = -200.0f;
    bool directionMoveLeft = true;

    marqueeModel->CalcAnimationStart(firstStart, secondStart, textTotalLen, aniStartPos, aniEndPos, directionMoveLeft);

    EXPECT_EQ(secondStart, 100.0f);
}

/**
 * @tc.name: MarqueePattern_CalcAnimationStart018
 * @tc.desc: Test CalcAnimationStart with textTotalLen equal to boundary condition, directionMoveLeft=false
 * @tc.type: FUNC
 */
HWTEST_F(MarqueePatternTestNg, MarqueePattern_CalcAnimationStart018, TestSize.Level1)
{
    RefPtr<Pattern> pattern = AceType::MakeRefPtr<MarqueePattern>();
    auto frameNode = FrameNode::CreateFrameNode("Marquee", 1, pattern, false);
    auto layoutProperty = frameNode->GetLayoutProperty<MarqueeLayoutProperty>();
    RefPtr<GeometryNode> geoNode = AceType::MakeRefPtr<GeometryNode>();
    geoNode->SetFrameSize(SizeF(300.0f, 50.0f));
    frameNode->SetGeometryNode(geoNode);

    auto textFrameNode = FrameNode::CreateFrameNode("Text", 2, AceType::MakeRefPtr<TextPattern>(), false);
    RefPtr<GeometryNode> textGeo = AceType::MakeRefPtr<GeometryNode>();
    textGeo->SetFrameSize(SizeF(100.0f, 30.0f));
    textFrameNode->SetGeometryNode(textGeo);
    frameNode->AddChild(textFrameNode);

    WeakPtr<FrameNode> hostNode(frameNode);
    auto marqueeModel = AceType::MakeRefPtr<MarqueePattern>();
    marqueeModel->frameNode_ = hostNode;

    float firstStart = 0.0f;
    float secondStart = 0.0f;
    float textTotalLen = 100.0f;
    float aniStartPos = -150.0f;
    float aniEndPos = 200.0f;
    bool directionMoveLeft = false;

    marqueeModel->CalcAnimationStart(firstStart, secondStart, textTotalLen, aniStartPos, aniEndPos, directionMoveLeft);

    EXPECT_EQ(secondStart, -100.0f);
}

/**
 * @tc.name: MarqueePattern_GetDoubleTextOffset001
 * @tc.desc: Test GetDoubleTextOffset with IsRunMarquee() returns false
 * @tc.type: FUNC
 */
HWTEST_F(MarqueePatternTestNg, MarqueePattern_GetDoubleTextOffset001, TestSize.Level1)
{
    MarqueePattern marqueeModel;
    auto res = marqueeModel.GetDoubleTextOffset();
    EXPECT_EQ(res.first, 0.0f);
    EXPECT_EQ(res.second, 0.0f);
}

/**
 * @tc.name: MarqueePattern_GetDoubleTextOffset002
 * @tc.desc: Test GetDoubleTextOffset with DEFAULT marquee update strategy
 * @tc.type: FUNC
 */
HWTEST_F(MarqueePatternTestNg, MarqueePattern_GetDoubleTextOffset002, TestSize.Level1)
{
    RefPtr<Pattern> pattern = AceType::MakeRefPtr<MarqueePattern>();
    auto frameNode = FrameNode::CreateFrameNode("Marquee", 1, pattern, false);
    auto layoutProperty = frameNode->GetLayoutProperty<MarqueeLayoutProperty>();
    layoutProperty->UpdateMarqueeUpdateStrategy(MarqueeUpdateStrategy::DEFAULT);
    auto paintProperty = frameNode->GetPaintProperty<MarqueePaintProperty>();
    paintProperty->UpdatePlayerStatus(true);
    frameNode->paintProperty_ = paintProperty;
    RefPtr<GeometryNode> geoNode = AceType::MakeRefPtr<GeometryNode>();
    geoNode->SetFrameSize(SizeF(100.0f, 50.0f));
    frameNode->SetGeometryNode(geoNode);

    auto textFrameNode = FrameNode::CreateFrameNode("Text", 2, AceType::MakeRefPtr<TextPattern>(), false);
    RefPtr<GeometryNode> textGeo = AceType::MakeRefPtr<GeometryNode>();
    textGeo->SetFrameSize(SizeF(200.0f, 30.0f));
    textFrameNode->SetGeometryNode(textGeo);
    frameNode->AddChild(textFrameNode);

    WeakPtr<FrameNode> hostNode(frameNode);
    auto marqueeModel = AceType::MakeRefPtr<MarqueePattern>();
    marqueeModel->frameNode_ = hostNode;

    auto res = marqueeModel->GetDoubleTextOffset();
    EXPECT_EQ(res.first, 0.0f);
    EXPECT_EQ(res.second, 300.0f);
}

/**
 * @tc.name: MarqueePattern_GetDoubleTextOffset003
 * @tc.desc: Test GetDoubleTextOffset with PRESERVE_POSITION strategy and playStatus=false
 * @tc.type: FUNC
 */
HWTEST_F(MarqueePatternTestNg, MarqueePattern_GetDoubleTextOffset003, TestSize.Level1)
{
    RefPtr<Pattern> pattern = AceType::MakeRefPtr<MarqueePattern>();
    auto frameNode = FrameNode::CreateFrameNode("Marquee", 1, pattern, false);
    auto layoutProperty = frameNode->GetLayoutProperty<MarqueeLayoutProperty>();
    layoutProperty->UpdateMarqueeUpdateStrategy(MarqueeUpdateStrategy::PRESERVE_POSITION);
    auto paintProperty = frameNode->GetPaintProperty<MarqueePaintProperty>();
    paintProperty->UpdatePlayerStatus(false);
    frameNode->paintProperty_ = paintProperty;
    RefPtr<GeometryNode> geoNode = AceType::MakeRefPtr<GeometryNode>();
    geoNode->SetFrameSize(SizeF(100.0f, 50.0f));
    frameNode->SetGeometryNode(geoNode);

    auto textFrameNode = FrameNode::CreateFrameNode("Text", 2, AceType::MakeRefPtr<TextPattern>(), false);
    RefPtr<GeometryNode> textGeo = AceType::MakeRefPtr<GeometryNode>();
    textGeo->SetFrameSize(SizeF(200.0f, 30.0f));
    textFrameNode->SetGeometryNode(textGeo);
    frameNode->AddChild(textFrameNode);

    WeakPtr<FrameNode> hostNode(frameNode);
    auto marqueeModel = AceType::MakeRefPtr<MarqueePattern>();
    marqueeModel->frameNode_ = hostNode;

    auto res = marqueeModel->GetDoubleTextOffset();
    EXPECT_EQ(res.first, 0.0f);
    EXPECT_EQ(res.second, 300.0f);
}

/**
 * @tc.name: MarqueePattern_GetDoubleTextOffset004
 * @tc.desc: Test GetDoubleTextOffset with PRESERVE_POSITION strategy, playStatus=true, but no lastAnimationOffset
 * @tc.type: FUNC
 */
HWTEST_F(MarqueePatternTestNg, MarqueePattern_GetDoubleTextOffset004, TestSize.Level1)
{
    RefPtr<Pattern> pattern = AceType::MakeRefPtr<MarqueePattern>();
    auto frameNode = FrameNode::CreateFrameNode("Marquee", 1, pattern, false);
    auto layoutProperty = frameNode->GetLayoutProperty<MarqueeLayoutProperty>();
    layoutProperty->UpdateMarqueeUpdateStrategy(MarqueeUpdateStrategy::PRESERVE_POSITION);
    auto paintProperty = frameNode->GetPaintProperty<MarqueePaintProperty>();
    paintProperty->UpdatePlayerStatus(true);
    frameNode->paintProperty_ = paintProperty;
    RefPtr<GeometryNode> geoNode = AceType::MakeRefPtr<GeometryNode>();
    geoNode->SetFrameSize(SizeF(100.0f, 50.0f));
    frameNode->SetGeometryNode(geoNode);

    auto textFrameNode = FrameNode::CreateFrameNode("Text", 2, AceType::MakeRefPtr<TextPattern>(), false);
    RefPtr<GeometryNode> textGeo = AceType::MakeRefPtr<GeometryNode>();
    textGeo->SetFrameSize(SizeF(200.0f, 30.0f));
    textFrameNode->SetGeometryNode(textGeo);
    frameNode->AddChild(textFrameNode);

    WeakPtr<FrameNode> hostNode(frameNode);
    auto marqueeModel = AceType::MakeRefPtr<MarqueePattern>();
    marqueeModel->frameNode_ = hostNode;

    auto res = marqueeModel->GetDoubleTextOffset();
    EXPECT_EQ(res.first, 0.0f);
    EXPECT_EQ(res.second, 300.0f);
}

/**
 * @tc.name: MarqueePattern_GetDoubleTextOffset005
 * @tc.desc: Test GetDoubleTextOffset with lastAnimationOffset set but secondChildLastAnimationOffset not set
 * @tc.type: FUNC
 */
HWTEST_F(MarqueePatternTestNg, MarqueePattern_GetDoubleTextOffset005, TestSize.Level1)
{
    RefPtr<Pattern> pattern = AceType::MakeRefPtr<MarqueePattern>();
    auto frameNode = FrameNode::CreateFrameNode("Marquee", 1, pattern, false);
    auto layoutProperty = frameNode->GetLayoutProperty<MarqueeLayoutProperty>();
    layoutProperty->UpdateMarqueeUpdateStrategy(MarqueeUpdateStrategy::PRESERVE_POSITION);
    auto paintProperty = frameNode->GetPaintProperty<MarqueePaintProperty>();
    paintProperty->UpdatePlayerStatus(true);
    frameNode->paintProperty_ = paintProperty;
    RefPtr<GeometryNode> geoNode = AceType::MakeRefPtr<GeometryNode>();
    geoNode->SetFrameSize(SizeF(100.0f, 50.0f));
    frameNode->SetGeometryNode(geoNode);

    auto textFrameNode = FrameNode::CreateFrameNode("Text", 2, AceType::MakeRefPtr<TextPattern>(), false);
    RefPtr<GeometryNode> textGeo = AceType::MakeRefPtr<GeometryNode>();
    textGeo->SetFrameSize(SizeF(200.0f, 30.0f));
    textFrameNode->SetGeometryNode(textGeo);
    frameNode->AddChild(textFrameNode);

    WeakPtr<FrameNode> hostNode(frameNode);
    auto marqueeModel = AceType::MakeRefPtr<MarqueePattern>();
    marqueeModel->frameNode_ = hostNode;
    marqueeModel->lastAnimationOffset_ = OffsetF(50.0f, 0.0f);

    auto res = marqueeModel->GetDoubleTextOffset();
    EXPECT_EQ(res.first, 0.0f);
    EXPECT_EQ(res.second, 300.0f);
}

/**
 * @tc.name: MarqueePattern_GetDoubleTextOffset006
 * @tc.desc: Test GetDoubleTextOffset with secondChildLastAnimationOffset set but lastAnimationOffset not set
 * @tc.type: FUNC
 */
HWTEST_F(MarqueePatternTestNg, MarqueePattern_GetDoubleTextOffset006, TestSize.Level1)
{
    RefPtr<Pattern> pattern = AceType::MakeRefPtr<MarqueePattern>();
    auto frameNode = FrameNode::CreateFrameNode("Marquee", 1, pattern, false);
    auto layoutProperty = frameNode->GetLayoutProperty<MarqueeLayoutProperty>();
    layoutProperty->UpdateMarqueeUpdateStrategy(MarqueeUpdateStrategy::PRESERVE_POSITION);
    auto paintProperty = frameNode->GetPaintProperty<MarqueePaintProperty>();
    paintProperty->UpdatePlayerStatus(true);
    frameNode->paintProperty_ = paintProperty;
    RefPtr<GeometryNode> geoNode = AceType::MakeRefPtr<GeometryNode>();
    geoNode->SetFrameSize(SizeF(100.0f, 50.0f));
    frameNode->SetGeometryNode(geoNode);

    auto textFrameNode = FrameNode::CreateFrameNode("Text", 2, AceType::MakeRefPtr<TextPattern>(), false);
    RefPtr<GeometryNode> textGeo = AceType::MakeRefPtr<GeometryNode>();
    textGeo->SetFrameSize(SizeF(200.0f, 30.0f));
    textFrameNode->SetGeometryNode(textGeo);
    frameNode->AddChild(textFrameNode);

    WeakPtr<FrameNode> hostNode(frameNode);
    auto marqueeModel = AceType::MakeRefPtr<MarqueePattern>();
    marqueeModel->frameNode_ = hostNode;
    marqueeModel->secondChildLastAnimationOffset_ = OffsetF(100.0f, 0.0f);

    auto res = marqueeModel->GetDoubleTextOffset();
    EXPECT_EQ(res.first, 0.0f);
    EXPECT_EQ(res.second, 300.0f);
}

/**
 * @tc.name: MarqueePattern_GetDoubleTextOffset007
 * @tc.desc: Test GetDoubleTextOffset with both lastAnimationOffset and secondChildLastAnimationOffset set
 * @tc.type: FUNC
 */
HWTEST_F(MarqueePatternTestNg, MarqueePattern_GetDoubleTextOffset007, TestSize.Level1)
{
    RefPtr<Pattern> pattern = AceType::MakeRefPtr<MarqueePattern>();
    auto frameNode = FrameNode::CreateFrameNode("Marquee", 1, pattern, false);
    auto layoutProperty = frameNode->GetLayoutProperty<MarqueeLayoutProperty>();
    layoutProperty->UpdateMarqueeUpdateStrategy(MarqueeUpdateStrategy::PRESERVE_POSITION);
    auto paintProperty = frameNode->GetPaintProperty<MarqueePaintProperty>();
    paintProperty->UpdatePlayerStatus(true);
    frameNode->paintProperty_ = paintProperty;
    RefPtr<GeometryNode> geoNode = AceType::MakeRefPtr<GeometryNode>();
    geoNode->SetFrameSize(SizeF(100.0f, 50.0f));
    frameNode->SetGeometryNode(geoNode);

    auto textFrameNode = FrameNode::CreateFrameNode("Text", 2, AceType::MakeRefPtr<TextPattern>(), false);
    RefPtr<GeometryNode> textGeo = AceType::MakeRefPtr<GeometryNode>();
    textGeo->SetFrameSize(SizeF(200.0f, 30.0f));
    textFrameNode->SetGeometryNode(textGeo);
    frameNode->AddChild(textFrameNode);

    WeakPtr<FrameNode> hostNode(frameNode);
    auto marqueeModel = AceType::MakeRefPtr<MarqueePattern>();
    marqueeModel->frameNode_ = hostNode;
    marqueeModel->lastAnimationOffset_ = OffsetF(-50.0f, 0.0f);
    marqueeModel->secondChildLastAnimationOffset_ = OffsetF(-150.0f, 0.0f);

    auto res = marqueeModel->GetDoubleTextOffset();
    EXPECT_EQ(res.first, -50.0f);
    EXPECT_EQ(res.second, -150.0f);
    EXPECT_FALSE(marqueeModel->lastAnimationOffset_.has_value());
    EXPECT_FALSE(marqueeModel->secondChildLastAnimationOffset_.has_value());
}

/**
 * @tc.name: MarqueePattern_GetDoubleTextOffset008
 * @tc.desc: Test GetDoubleTextOffset with positive offset values
 * @tc.type: FUNC
 */
HWTEST_F(MarqueePatternTestNg, MarqueePattern_GetDoubleTextOffset008, TestSize.Level1)
{
    RefPtr<Pattern> pattern = AceType::MakeRefPtr<MarqueePattern>();
    auto frameNode = FrameNode::CreateFrameNode("Marquee", 1, pattern, false);
    auto layoutProperty = frameNode->GetLayoutProperty<MarqueeLayoutProperty>();
    layoutProperty->UpdateMarqueeUpdateStrategy(MarqueeUpdateStrategy::PRESERVE_POSITION);
    auto paintProperty = frameNode->GetPaintProperty<MarqueePaintProperty>();
    paintProperty->UpdatePlayerStatus(true);
    frameNode->paintProperty_ = paintProperty;
    RefPtr<GeometryNode> geoNode = AceType::MakeRefPtr<GeometryNode>();
    geoNode->SetFrameSize(SizeF(100.0f, 50.0f));
    frameNode->SetGeometryNode(geoNode);

    auto textFrameNode = FrameNode::CreateFrameNode("Text", 2, AceType::MakeRefPtr<TextPattern>(), false);
    RefPtr<GeometryNode> textGeo = AceType::MakeRefPtr<GeometryNode>();
    textGeo->SetFrameSize(SizeF(200.0f, 30.0f));
    textFrameNode->SetGeometryNode(textGeo);
    frameNode->AddChild(textFrameNode);

    WeakPtr<FrameNode> hostNode(frameNode);
    auto marqueeModel = AceType::MakeRefPtr<MarqueePattern>();
    marqueeModel->frameNode_ = hostNode;
    marqueeModel->lastAnimationOffset_ = OffsetF(75.0f, 0.0f);
    marqueeModel->secondChildLastAnimationOffset_ = OffsetF(275.0f, 0.0f);

    auto res = marqueeModel->GetDoubleTextOffset();
    EXPECT_EQ(res.first, 75.0f);
    EXPECT_EQ(res.second, 275.0f);
}

/**
 * @tc.name: MarqueePattern_GetDoubleTextOffset009
 * @tc.desc: Test GetDoubleTextOffset with zero offset values
 * @tc.type: FUNC
 */
HWTEST_F(MarqueePatternTestNg, MarqueePattern_GetDoubleTextOffset009, TestSize.Level1)
{
    RefPtr<Pattern> pattern = AceType::MakeRefPtr<MarqueePattern>();
    auto frameNode = FrameNode::CreateFrameNode("Marquee", 1, pattern, false);
    auto layoutProperty = frameNode->GetLayoutProperty<MarqueeLayoutProperty>();
    layoutProperty->UpdateMarqueeUpdateStrategy(MarqueeUpdateStrategy::PRESERVE_POSITION);
    auto paintProperty = frameNode->GetPaintProperty<MarqueePaintProperty>();
    paintProperty->UpdatePlayerStatus(true);
    frameNode->paintProperty_ = paintProperty;
    RefPtr<GeometryNode> geoNode = AceType::MakeRefPtr<GeometryNode>();
    geoNode->SetFrameSize(SizeF(100.0f, 50.0f));
    frameNode->SetGeometryNode(geoNode);

    auto textFrameNode = FrameNode::CreateFrameNode("Text", 2, AceType::MakeRefPtr<TextPattern>(), false);
    RefPtr<GeometryNode> textGeo = AceType::MakeRefPtr<GeometryNode>();
    textGeo->SetFrameSize(SizeF(200.0f, 30.0f));
    textFrameNode->SetGeometryNode(textGeo);
    frameNode->AddChild(textFrameNode);

    WeakPtr<FrameNode> hostNode(frameNode);
    auto marqueeModel = AceType::MakeRefPtr<MarqueePattern>();
    marqueeModel->frameNode_ = hostNode;
    marqueeModel->lastAnimationOffset_ = OffsetF(0.0f, 0.0f);
    marqueeModel->secondChildLastAnimationOffset_ = OffsetF(0.0f, 0.0f);

    auto res = marqueeModel->GetDoubleTextOffset();
    EXPECT_EQ(res.first, 0.0f);
    EXPECT_EQ(res.second, 0.0f);
}

/**
 * @tc.name: MarqueePattern_GetDoubleTextOffset010
 * @tc.desc: Test GetDoubleTextOffset with large offset values
 * @tc.type: FUNC
 */
HWTEST_F(MarqueePatternTestNg, MarqueePattern_GetDoubleTextOffset010, TestSize.Level1)
{
    RefPtr<Pattern> pattern = AceType::MakeRefPtr<MarqueePattern>();
    auto frameNode = FrameNode::CreateFrameNode("Marquee", 1, pattern, false);
    auto layoutProperty = frameNode->GetLayoutProperty<MarqueeLayoutProperty>();
    layoutProperty->UpdateMarqueeUpdateStrategy(MarqueeUpdateStrategy::PRESERVE_POSITION);
    auto paintProperty = frameNode->GetPaintProperty<MarqueePaintProperty>();
    paintProperty->UpdatePlayerStatus(true);
    frameNode->paintProperty_ = paintProperty;
    RefPtr<GeometryNode> geoNode = AceType::MakeRefPtr<GeometryNode>();
    geoNode->SetFrameSize(SizeF(100.0f, 50.0f));
    frameNode->SetGeometryNode(geoNode);

    auto textFrameNode = FrameNode::CreateFrameNode("Text", 2, AceType::MakeRefPtr<TextPattern>(), false);
    RefPtr<GeometryNode> textGeo = AceType::MakeRefPtr<GeometryNode>();
    textGeo->SetFrameSize(SizeF(200.0f, 30.0f));
    textFrameNode->SetGeometryNode(textGeo);
    frameNode->AddChild(textFrameNode);

    WeakPtr<FrameNode> hostNode(frameNode);
    auto marqueeModel = AceType::MakeRefPtr<MarqueePattern>();
    marqueeModel->frameNode_ = hostNode;
    marqueeModel->lastAnimationOffset_ = OffsetF(-500.0f, 0.0f);
    marqueeModel->secondChildLastAnimationOffset_ = OffsetF(-700.0f, 0.0f);

    auto res = marqueeModel->GetDoubleTextOffset();
    EXPECT_EQ(res.first, -500.0f);
    EXPECT_EQ(res.second, -700.0f);
}

/**
 * @tc.name: MarqueePattern_GetDoubleTextOffset011
 * @tc.desc: Test GetDoubleTextOffset with text width less than marquee width (no scroll)
 * @tc.type: FUNC
 */
HWTEST_F(MarqueePatternTestNg, MarqueePattern_GetDoubleTextOffset011, TestSize.Level1)
{
    RefPtr<Pattern> pattern = AceType::MakeRefPtr<MarqueePattern>();
    auto frameNode = FrameNode::CreateFrameNode("Marquee", 1, pattern, false);
    auto layoutProperty = frameNode->GetLayoutProperty<MarqueeLayoutProperty>();
    layoutProperty->UpdateMarqueeUpdateStrategy(MarqueeUpdateStrategy::PRESERVE_POSITION);
    auto paintProperty = frameNode->GetPaintProperty<MarqueePaintProperty>();
    paintProperty->UpdatePlayerStatus(true);
    frameNode->paintProperty_ = paintProperty;
    RefPtr<GeometryNode> geoNode = AceType::MakeRefPtr<GeometryNode>();
    geoNode->SetFrameSize(SizeF(300.0f, 50.0f));
    frameNode->SetGeometryNode(geoNode);

    auto textFrameNode = FrameNode::CreateFrameNode("Text", 2, AceType::MakeRefPtr<TextPattern>(), false);
    RefPtr<GeometryNode> textGeo = AceType::MakeRefPtr<GeometryNode>();
    textGeo->SetFrameSize(SizeF(200.0f, 30.0f));
    textFrameNode->SetGeometryNode(textGeo);
    frameNode->AddChild(textFrameNode);

    WeakPtr<FrameNode> hostNode(frameNode);
    auto marqueeModel = AceType::MakeRefPtr<MarqueePattern>();
    marqueeModel->frameNode_ = hostNode;
    marqueeModel->lastAnimationOffset_ = OffsetF(-100.0f, 0.0f);
    marqueeModel->secondChildLastAnimationOffset_ = OffsetF(-300.0f, 0.0f);

    auto res = marqueeModel->GetDoubleTextOffset();
    EXPECT_EQ(res.first, 0.0f);
    EXPECT_EQ(res.second, 500.0f);
}

/**
 * @tc.name: MarqueePattern_GetDoubleTextOffset012
 * @tc.desc: Test GetDoubleTextOffset with fractional offset values
 * @tc.type: FUNC
 */
HWTEST_F(MarqueePatternTestNg, MarqueePattern_GetDoubleTextOffset012, TestSize.Level1)
{
    RefPtr<Pattern> pattern = AceType::MakeRefPtr<MarqueePattern>();
    auto frameNode = FrameNode::CreateFrameNode("Marquee", 1, pattern, false);
    auto layoutProperty = frameNode->GetLayoutProperty<MarqueeLayoutProperty>();
    layoutProperty->UpdateMarqueeUpdateStrategy(MarqueeUpdateStrategy::PRESERVE_POSITION);
    auto paintProperty = frameNode->GetPaintProperty<MarqueePaintProperty>();
    paintProperty->UpdatePlayerStatus(true);
    frameNode->paintProperty_ = paintProperty;
    RefPtr<GeometryNode> geoNode = AceType::MakeRefPtr<GeometryNode>();
    geoNode->SetFrameSize(SizeF(100.0f, 50.0f));
    frameNode->SetGeometryNode(geoNode);

    auto textFrameNode = FrameNode::CreateFrameNode("Text", 2, AceType::MakeRefPtr<TextPattern>(), false);
    RefPtr<GeometryNode> textGeo = AceType::MakeRefPtr<GeometryNode>();
    textGeo->SetFrameSize(SizeF(200.0f, 30.0f));
    textFrameNode->SetGeometryNode(textGeo);
    frameNode->AddChild(textFrameNode);

    WeakPtr<FrameNode> hostNode(frameNode);
    auto marqueeModel = AceType::MakeRefPtr<MarqueePattern>();
    marqueeModel->frameNode_ = hostNode;
    marqueeModel->lastAnimationOffset_ = OffsetF(123.5f, 0.0f);
    marqueeModel->secondChildLastAnimationOffset_ = OffsetF(323.5f, 0.0f);

    auto res = marqueeModel->GetDoubleTextOffset();
    EXPECT_FLOAT_EQ(res.first, 123.5f);
    EXPECT_FLOAT_EQ(res.second, 323.5f);
}
} // namespace OHOS::Ace::NG