/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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
#include "scroll_test_ng.h"
#include "base/memory/ace_type.h"

namespace OHOS::Ace::NG {

void ScrollPatternTestNg::SetUp() {}

void ScrollPatternTestNg::TearDown() {}

/**
 * @tc.name: ScrollPatternTestNg001
 * @tc.desc: Test OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTestNg, ScrollPatternTestNg001, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    DirtySwapConfig dirtySwapConfig;
    dirtySwapConfig.skipLayout = false;
    dirtySwapConfig.skipMeasure = false;
    auto frameNode =
        FrameNode::CreateFrameNode(V2::NAVIGATION_CONTENT_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(frameNode, nullptr);
    auto layoutWrapper = frameNode->CreateLayoutWrapper(true, true);
    ASSERT_NE(layoutWrapper, nullptr);
    auto result = scrollPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, dirtySwapConfig);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: ScrollPatternTestNg002
 * @tc.desc: Test OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTestNg, ScrollPatternTestNg002, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    DirtySwapConfig dirtySwapConfig;
    dirtySwapConfig.skipLayout = false;
    dirtySwapConfig.skipMeasure = true;
    auto frameNode =
        FrameNode::CreateFrameNode(V2::NAVIGATION_CONTENT_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(frameNode, nullptr);
    auto layoutWrapper = frameNode->CreateLayoutWrapper(true, true);
    ASSERT_NE(layoutWrapper, nullptr);
    auto result = scrollPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, dirtySwapConfig);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: ScrollPatternTestNg003
 * @tc.desc: Test OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTestNg, ScrollPatternTestNg003, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    DirtySwapConfig dirtySwapConfig;
    dirtySwapConfig.skipLayout = true;
    dirtySwapConfig.skipMeasure = false;
    auto frameNode =
        FrameNode::CreateFrameNode(V2::NAVIGATION_CONTENT_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(frameNode, nullptr);
    auto layoutWrapper = frameNode->CreateLayoutWrapper(true, true);
    ASSERT_NE(layoutWrapper, nullptr);
    auto result = scrollPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, dirtySwapConfig);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: ScrollPatternTestNg004
 * @tc.desc: Test OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTestNg, ScrollPatternTestNg004, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    DirtySwapConfig dirtySwapConfig;
    dirtySwapConfig.skipLayout = true;
    dirtySwapConfig.skipMeasure = true;
    auto frameNode =
        FrameNode::CreateFrameNode(V2::NAVIGATION_CONTENT_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(frameNode, nullptr);
    auto layoutWrapper = frameNode->CreateLayoutWrapper(true, true);
    ASSERT_NE(layoutWrapper, nullptr);
    auto result = scrollPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, dirtySwapConfig);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: OnModifyDone001
 * @tc.desc: Test OnDirtyLayoutWrapperSwap 1,1
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTestNg, OnModifyDone001, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::GAUGE_ETS_TAG, -1, scrollPattern);
    ASSERT_NE(frameNode, nullptr);
    scrollPattern->AttachToFrameNode(frameNode);
    auto host = scrollPattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto overlayNode_ = host->GetOverlayNode();
    ASSERT_EQ(overlayNode_, nullptr);
    auto paintProperty = host->GetPaintProperty<ScrollablePaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateFadingEdge(scrollPattern->CreateNodePaintMethod());
    scrollPattern->OnModifyDone();
    EXPECT_NE(host->overlayNode_, nullptr);
}

/**
 * @tc.name: OnModifyDone001
 * @tc.desc: Test GetChildrenExpandedSize
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTestNg, GetChildrenExpandedSize001, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    scrollPattern->axis_ = Axis::VERTICAL;
    scrollPattern->viewPort_.AddWidth(10.0f);
    auto result = scrollPattern->GetChildrenExpandedSize();
    SizeF sizeF;
    EXPECT_NE(sizeF.Width(), result.Width());
}

/**
 * @tc.name: OnModifyDone002
 * @tc.desc: Test GetChildrenExpandedSize
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTestNg, GetChildrenExpandedSize002, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    scrollPattern->axis_ = Axis::VERTICAL;
    scrollPattern->viewPort_.AddWidth(10.0f);
    auto result = scrollPattern->GetChildrenExpandedSize();
    SizeF sizeF;
    EXPECT_NE(sizeF.Width(), result.Width());
}

/**
 * @tc.name: OnModifyDone003
 * @tc.desc: Test GetChildrenExpandedSize
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTestNg, GetChildrenExpandedSize003, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    scrollPattern->axis_ = Axis::NONE;
    auto result = scrollPattern->GetChildrenExpandedSize();
    SizeF sizeF;
    EXPECT_EQ(sizeF.Width(), result.Width());
}

/**
 * @tc.name: StartSnapAnimation001
 * @tc.desc: Test OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTestNg, StartSnapAnimation001, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    SnapAnimationOptions options;
    options.fromScrollBar = true;
    auto scrollBar = scrollPattern->GetScrollBar();
    scrollBar = nullptr;
    auto result = scrollPattern->StartSnapAnimation(options);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: StartSnapAnimation002
 * @tc.desc: Test OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTestNg, StartSnapAnimation002, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    auto scrollBar_ = AceType::MakeRefPtr<ScrollBar>(DisplayMode::OFF, ShapeMode::DEFAULT);
    ASSERT_NE(scrollBar_, nullptr);
    SnapAnimationOptions options;
    options.fromScrollBar = true;
    scrollPattern->scrollBar_ = scrollBar_;
    auto scrollBar = scrollPattern->GetScrollBar();
    ASSERT_NE(scrollBar, nullptr);
    auto driving = scrollBar->IsDriving();
    driving = true;
    auto result = scrollPattern->StartSnapAnimation(options);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: StartSnapAnimation003
 * @tc.desc: Test OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTestNg, StartSnapAnimation003, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    auto scrollBar_ = AceType::MakeRefPtr<ScrollBar>(DisplayMode::OFF, ShapeMode::DEFAULT);
    ASSERT_NE(scrollBar_, nullptr);
    SnapAnimationOptions options;
    options.fromScrollBar = true;
    scrollPattern->scrollBar_ = scrollBar_;
    auto scrollBar = scrollPattern->GetScrollBar();
    ASSERT_NE(scrollBar, nullptr);
    auto driving = scrollBar->IsDriving();
    driving = false;
    auto result = scrollPattern->StartSnapAnimation(options);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: StartSnapAnimation004
 * @tc.desc: Test OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTestNg, StartSnapAnimation004, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    SnapAnimationOptions options;
    options.fromScrollBar = false;
    auto scrollBar = scrollPattern->GetScrollBar();
    scrollBar = nullptr;
    auto result = scrollPattern->StartSnapAnimation(options);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: StartSnapAnimation005
 * @tc.desc: Test OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTestNg, StartSnapAnimation005, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    auto scrollBar_ = AceType::MakeRefPtr<ScrollBar>(DisplayMode::OFF, ShapeMode::DEFAULT);
    ASSERT_NE(scrollBar_, nullptr);
    SnapAnimationOptions options;
    options.fromScrollBar = false;
    scrollPattern->scrollBar_ = scrollBar_;
    auto scrollBar = scrollPattern->GetScrollBar();
    ASSERT_NE(scrollBar, nullptr);
    auto driving = scrollBar->IsDriving();
    driving = true;
    auto result = scrollPattern->StartSnapAnimation(options);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: StartSnapAnimation006
 * @tc.desc: Test OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTestNg, StartSnapAnimation006, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    auto scrollBar_ = AceType::MakeRefPtr<ScrollBar>(DisplayMode::OFF, ShapeMode::DEFAULT);
    ASSERT_NE(scrollBar_, nullptr);
    SnapAnimationOptions options;
    options.fromScrollBar = false;
    scrollPattern->scrollBar_ = scrollBar_;
    auto scrollBar = scrollPattern->GetScrollBar();
    ASSERT_NE(scrollBar, nullptr);
    auto driving = scrollBar->IsDriving();
    driving = false;
    auto result = scrollPattern->StartSnapAnimation(options);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: StartSnapAnimation007
 * @tc.desc: Test OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTestNg, StartSnapAnimation007, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    SnapAnimationOptions options;
    options.fromScrollBar = true;
    auto scrollBarProxy = scrollPattern->GetScrollBarProxy();
    scrollBarProxy = nullptr;
    auto result = scrollPattern->StartSnapAnimation(options);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: StartSnapAnimation008
 * @tc.desc: Test OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTestNg, StartSnapAnimation008, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    auto scrollBarProxy_ = AceType::MakeRefPtr<NG::ScrollBarProxy>();
    ASSERT_NE(scrollBarProxy_, nullptr);
    scrollPattern->SetScrollBarProxy(scrollBarProxy_);
    SnapAnimationOptions options;
    options.fromScrollBar = true;
    auto scrollBarProxy = scrollPattern->GetScrollBarProxy();
    ASSERT_NE(scrollBarProxy, nullptr);
    auto driving = scrollBarProxy->IsScrollSnapTrigger();
    driving = true;
    auto result = scrollPattern->StartSnapAnimation(options);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: StartSnapAnimation009
 * @tc.desc: Test OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTestNg, StartSnapAnimation009, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    auto scrollBarProxy_ = AceType::MakeRefPtr<NG::ScrollBarProxy>();
    ASSERT_NE(scrollBarProxy_, nullptr);
    scrollPattern->SetScrollBarProxy(scrollBarProxy_);
    SnapAnimationOptions options;
    options.fromScrollBar = true;
    auto scrollBarProxy = scrollPattern->GetScrollBarProxy();
    ASSERT_NE(scrollBarProxy, nullptr);
    auto driving = scrollBarProxy->IsScrollSnapTrigger();
    driving = false;
    auto result = scrollPattern->StartSnapAnimation(options);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: StartSnapAnimation010
 * @tc.desc: Test OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTestNg, StartSnapAnimation010, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    SnapAnimationOptions options;
    options.fromScrollBar = false;
    auto scrollBarProxy = scrollPattern->GetScrollBarProxy();
    scrollBarProxy = nullptr;
    auto result = scrollPattern->StartSnapAnimation(options);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: StartSnapAnimation011
 * @tc.desc: Test OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTestNg, StartSnapAnimation011, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    auto scrollBarProxy_ = AceType::MakeRefPtr<NG::ScrollBarProxy>();
    ASSERT_NE(scrollBarProxy_, nullptr);
    scrollPattern->SetScrollBarProxy(scrollBarProxy_);
    SnapAnimationOptions options;
    options.fromScrollBar = false;
    auto scrollBarProxy = scrollPattern->GetScrollBarProxy();
    ASSERT_NE(scrollBarProxy, nullptr);
    auto driving = scrollBarProxy->IsScrollSnapTrigger();
    driving = true;
    auto result = scrollPattern->StartSnapAnimation(options);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: StartSnapAnimation012
 * @tc.desc: Test OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTestNg, StartSnapAnimation012, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    auto scrollBarProxy_ = AceType::MakeRefPtr<NG::ScrollBarProxy>();
    ASSERT_NE(scrollBarProxy_, nullptr);
    scrollPattern->SetScrollBarProxy(scrollBarProxy_);
    SnapAnimationOptions options;
    options.fromScrollBar = false;
    auto scrollBarProxy = scrollPattern->GetScrollBarProxy();
    ASSERT_NE(scrollBarProxy, nullptr);
    auto driving = scrollBarProxy->IsScrollSnapTrigger();
    driving = false;
    auto result = scrollPattern->StartSnapAnimation(options);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: NeedScrollSnapToSide001
 * @tc.desc: Test NeedScrollSnapToSide
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTestNg, NeedScrollSnapToSide001, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, scrollPattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = AceType::MakeRefPtr<ScrollLayoutProperty>();
    layoutProperty->UpdateScrollSnapAlign(ScrollSnapAlign::START);
    frameNode->layoutProperty_ = layoutProperty;
    scrollPattern->frameNode_ = frameNode;
    Dimension dimension(2.F);
    scrollPattern->snapPaginations_ = { dimension };
    scrollPattern->snapOffsets_ = { 2.0f, 1.0f, 9.0f, 4.0f };
    scrollPattern->currentOffset_ = 2.0f;
    scrollPattern->enableSnapToSide_ = { false, true };
    auto result = scrollPattern->NeedScrollSnapToSide(-2.0f);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: NeedScrollSnapToSide002
 * @tc.desc: Test NeedScrollSnapToSide
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTestNg, NeedScrollSnapToSide002, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, scrollPattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = AceType::MakeRefPtr<ScrollLayoutProperty>();
    layoutProperty->UpdateScrollSnapAlign(ScrollSnapAlign::START);
    frameNode->layoutProperty_ = layoutProperty;
    scrollPattern->frameNode_ = frameNode;
    Dimension dimension(2.F);
    scrollPattern->snapPaginations_ = { dimension };
    scrollPattern->snapOffsets_ = { 2.0f, 1.0f, 9.0f, 4.0f };
    scrollPattern->currentOffset_ = 2.0f;
    scrollPattern->enableSnapToSide_ = { true, true };
    auto result = scrollPattern->NeedScrollSnapToSide(-2.0f);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: NeedScrollSnapToSide003
 * @tc.desc: Test NeedScrollSnapToSide
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTestNg, NeedScrollSnapToSide003, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, scrollPattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = AceType::MakeRefPtr<ScrollLayoutProperty>();
    layoutProperty->UpdateScrollSnapAlign(ScrollSnapAlign::START);
    frameNode->layoutProperty_ = layoutProperty;
    scrollPattern->frameNode_ = frameNode;
    Dimension dimension(2.F);
    scrollPattern->snapPaginations_ = { dimension };
    scrollPattern->snapOffsets_ = { 2.0f, 1.0f, 9.0f, 4.0f };
    scrollPattern->currentOffset_ = 2.0f;
    scrollPattern->enableSnapToSide_ = { false, true };
    auto result = scrollPattern->NeedScrollSnapToSide(2.0f);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: NeedScrollSnapToSide004
 * @tc.desc: Test NeedScrollSnapToSide
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTestNg, NeedScrollSnapToSide004, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, scrollPattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = AceType::MakeRefPtr<ScrollLayoutProperty>();
    layoutProperty->UpdateScrollSnapAlign(ScrollSnapAlign::START);
    frameNode->layoutProperty_ = layoutProperty;
    scrollPattern->frameNode_ = frameNode;
    Dimension dimension(2.F);
    scrollPattern->snapPaginations_ = { dimension };
    scrollPattern->snapOffsets_ = { 2.0f, 5.0f, 9.0f, 4.0f };
    scrollPattern->currentOffset_ = 2.0f;
    scrollPattern->enableSnapToSide_ = { false, true };
    auto result = scrollPattern->NeedScrollSnapToSide(2.0f);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: NeedScrollSnapToSide005
 * @tc.desc: Test NeedScrollSnapToSide
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTestNg, NeedScrollSnapToSide005, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, scrollPattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = AceType::MakeRefPtr<ScrollLayoutProperty>();
    layoutProperty->UpdateScrollSnapAlign(ScrollSnapAlign::START);
    frameNode->layoutProperty_ = layoutProperty;
    scrollPattern->frameNode_ = frameNode;
    Dimension dimension(2.F);
    scrollPattern->snapPaginations_ = { dimension };
    scrollPattern->snapOffsets_ = { 2.0f, 3.0f, 9.0f, 4.0f };
    scrollPattern->currentOffset_ = 2.0f;
    scrollPattern->enableSnapToSide_ = { false, true };
    auto result = scrollPattern->NeedScrollSnapToSide(2.0f);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: NeedScrollSnapToSide006
 * @tc.desc: Test NeedScrollSnapToSide
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTestNg, NeedScrollSnapToSide006, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, scrollPattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = AceType::MakeRefPtr<ScrollLayoutProperty>();
    layoutProperty->UpdateScrollSnapAlign(ScrollSnapAlign::START);
    frameNode->layoutProperty_ = layoutProperty;
    scrollPattern->frameNode_ = frameNode;
    Dimension dimension(2.F);
    scrollPattern->snapPaginations_ = { dimension };
    scrollPattern->snapOffsets_ = { 2.0f, 3.0f, 3.0f, 4.0f };
    scrollPattern->currentOffset_ = 2.0f;
    scrollPattern->enableSnapToSide_ = { true, false };
    auto result = scrollPattern->NeedScrollSnapToSide(2.0f);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: NeedScrollSnapToSide007
 * @tc.desc: Test NeedScrollSnapToSide
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTestNg, NeedScrollSnapToSide007, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, scrollPattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = AceType::MakeRefPtr<ScrollLayoutProperty>();
    layoutProperty->UpdateScrollSnapAlign(ScrollSnapAlign::START);
    frameNode->layoutProperty_ = layoutProperty;
    scrollPattern->frameNode_ = frameNode;
    Dimension dimension(2.F);
    scrollPattern->snapPaginations_ = { dimension };
    scrollPattern->snapOffsets_ = { 2.0f, 5.0f, 5.0f, 4.0f };
    scrollPattern->currentOffset_ = 2.0f;
    scrollPattern->enableSnapToSide_ = { true, false };
    auto result = scrollPattern->NeedScrollSnapToSide(2.0f);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: NeedScrollSnapToSide008
 * @tc.desc: Test NeedScrollSnapToSide
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTestNg, NeedScrollSnapToSide008, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, scrollPattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = AceType::MakeRefPtr<ScrollLayoutProperty>();
    layoutProperty->UpdateScrollSnapAlign(ScrollSnapAlign::START);
    frameNode->layoutProperty_ = layoutProperty;
    scrollPattern->frameNode_ = frameNode;
    Dimension dimension(2.F);
    scrollPattern->snapPaginations_ = { dimension };
    scrollPattern->snapOffsets_ = { 2.0f, 1.0f, 1.0f, 4.0f };
    scrollPattern->currentOffset_ = 2.0f;
    scrollPattern->enableSnapToSide_ = { true, false };
    auto result = scrollPattern->NeedScrollSnapToSide(2.0f);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: NeedScrollSnapToSide009
 * @tc.desc: Test NeedScrollSnapToSide
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTestNg, NeedScrollSnapToSide009, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, scrollPattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = AceType::MakeRefPtr<ScrollLayoutProperty>();
    layoutProperty->UpdateScrollSnapAlign(ScrollSnapAlign::START);
    frameNode->layoutProperty_ = layoutProperty;
    scrollPattern->frameNode_ = frameNode;
    Dimension dimension(2.F);
    scrollPattern->snapPaginations_ = { dimension };
    scrollPattern->snapOffsets_ = { 2.0f, 1.0f, 1.0f, 4.0f };
    scrollPattern->currentOffset_ = 2.0f;
    scrollPattern->enableSnapToSide_ = { true, false };
    auto result = scrollPattern->NeedScrollSnapToSide(-2.0f);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CaleSnapOffsetsByPaginations001
 * @tc.desc: Test CaleSnapOffsetsByPaginations
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTestNg, CaleSnapOffsetsByPaginations001, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, scrollPattern);
    ASSERT_NE(frameNode, nullptr);
    SizeF viewPort(2.0f, 4.0f);
    scrollPattern->viewPort_ = viewPort;
    auto layoutProperty = AceType::MakeRefPtr<ScrollLayoutProperty>();
    frameNode->layoutProperty_ = layoutProperty;
    SizeF viewPortExtent(4.0f, 8.0f);
    scrollPattern->viewPortExtent_ = viewPortExtent;
    scrollPattern->scrollableDistance_ = -2.0f;
    Dimension dimension(2.0f);
    scrollPattern->snapPaginations_ = { dimension };
    scrollPattern->snapOffsets_ = { 2.0f, 3.0f, 4.0f, 5.0f };
    scrollPattern->CaleSnapOffsetsByPaginations(ScrollSnapAlign::START);
    EXPECT_EQ(*(scrollPattern->snapOffsets_.rbegin()), 2.0f);
}

/**
 * @tc.name: CaleSnapOffsetsByPaginations002
 * @tc.desc: Test CaleSnapOffsetsByPaginations
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTestNg, CaleSnapOffsetsByPaginations002, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, scrollPattern);
    ASSERT_NE(frameNode, nullptr);
    SizeF viewPort(2.0f, 4.0f);
    scrollPattern->viewPort_ = viewPort;
    auto layoutProperty = AceType::MakeRefPtr<ScrollLayoutProperty>();
    frameNode->layoutProperty_ = layoutProperty;
    SizeF viewPortExtent(4.0f, 8.0f);
    scrollPattern->viewPortExtent_ = viewPortExtent;
    scrollPattern->scrollableDistance_ = 4.0f;
    Dimension dimension(2.0f);
    scrollPattern->snapPaginations_ = { dimension };
    scrollPattern->snapOffsets_ = { 2.0f, 3.0f, 4.0f, 5.0f };
    scrollPattern->CaleSnapOffsetsByPaginations(ScrollSnapAlign::CENTER);
    EXPECT_EQ(*(scrollPattern->snapOffsets_.rbegin()), -4.0f);
    EXPECT_EQ(*(scrollPattern->snapOffsets_.rbegin() + 1), -3.0f);
}

/**
 * @tc.name: CaleSnapOffsetsByPaginations003
 * @tc.desc: Test CaleSnapOffsetsByPaginations
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTestNg, CaleSnapOffsetsByPaginations003, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, scrollPattern);
    ASSERT_NE(frameNode, nullptr);
    SizeF viewPort(2.0f, 4.0f);
    scrollPattern->viewPort_ = viewPort;
    auto layoutProperty = AceType::MakeRefPtr<ScrollLayoutProperty>();
    frameNode->layoutProperty_ = layoutProperty;
    SizeF viewPortExtent(4.0f, 8.0f);
    scrollPattern->viewPortExtent_ = viewPortExtent;
    scrollPattern->scrollableDistance_ = -2.0f;
    Dimension dimension(2.0f);
    scrollPattern->snapPaginations_ = { dimension };
    scrollPattern->snapOffsets_ = { 2.0f, 3.0f, 4.0f, 5.0f };
    scrollPattern->CaleSnapOffsetsByPaginations(ScrollSnapAlign::END);
    EXPECT_EQ(*(scrollPattern->snapOffsets_.rbegin()), 2.0f);
}

/**
 * @tc.name: CaleSnapOffsetsByPaginations004
 * @tc.desc: Test CaleSnapOffsetsByPaginations
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTestNg, CaleSnapOffsetsByPaginations004, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, scrollPattern);
    ASSERT_NE(frameNode, nullptr);
    SizeF viewPort(2.0f, 4.0f);
    scrollPattern->viewPort_ = viewPort;
    auto layoutProperty = AceType::MakeRefPtr<ScrollLayoutProperty>();
    frameNode->layoutProperty_ = layoutProperty;
    SizeF viewPortExtent(4.0f, 8.0f);
    scrollPattern->viewPortExtent_ = viewPortExtent;
    scrollPattern->scrollableDistance_ = -2.0f;
    Dimension dimension(2.0f);
    scrollPattern->snapPaginations_ = { dimension };
    scrollPattern->snapOffsets_ = { 2.0f, 3.0f, 4.0f, 5.0f };
    scrollPattern->CaleSnapOffsetsByPaginations(ScrollSnapAlign::NONE);
    EXPECT_EQ(*(scrollPattern->snapOffsets_.rbegin()), 2.0f);
}

/**
 * @tc.name: GetScrollPagingStatusDumpInfo001
 * @tc.desc: Test GetScrollPagingStatusDumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTestNg, GetScrollPagingStatusDumpInfo001, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    ScrollPagingStatus enablePagingStatus = ScrollPagingStatus::NONE;
    scrollPattern->SetEnablePaging(enablePagingStatus);
    auto json = JsonUtil::Create(true);
    scrollPattern->GetScrollPagingStatusDumpInfo(json);
    EXPECT_EQ(json->GetString("enablePaging"), "ScrollPagingStatus::NONE");
}

/**
 * @tc.name: GetScrollPagingStatusDumpInfo002
 * @tc.desc: Test GetScrollPagingStatusDumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTestNg, GetScrollPagingStatusDumpInfo002, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    ScrollPagingStatus enablePagingStatus = ScrollPagingStatus::INVALID;
    scrollPattern->SetEnablePaging(enablePagingStatus);
    auto json = JsonUtil::Create(true);
    scrollPattern->GetScrollPagingStatusDumpInfo(json);
    EXPECT_EQ(json->GetString("enablePaging"), "ScrollPagingStatus::INVALID");
}

/**
 * @tc.name: GetScrollPagingStatusDumpInfo003
 * @tc.desc: Test GetScrollPagingStatusDumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTestNg, GetScrollPagingStatusDumpInfo003, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    ScrollPagingStatus enablePagingStatus = ScrollPagingStatus::VALID;
    scrollPattern->SetEnablePaging(enablePagingStatus);
    auto json = JsonUtil::Create(true);
    scrollPattern->GetScrollPagingStatusDumpInfo(json);
    EXPECT_EQ(json->GetString("enablePaging"), "ScrollPagingStatus::VALID");
}

/**
 * @tc.name: GetScrollPagingStatusDumpInfo004
 * @tc.desc: Test GetScrollPagingStatusDumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTestNg, GetScrollPagingStatusDumpInfo004, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    int32_t number = 6;
    ScrollPagingStatus enablePagingStatus = static_cast<ScrollPagingStatus>(number);
    scrollPattern->SetEnablePaging(enablePagingStatus);
    auto json = JsonUtil::Create(true);
    scrollPattern->GetScrollPagingStatusDumpInfo(json);
    EXPECT_EQ(json->GetString("enablePaging"), "");
}

/**
 * @tc.name: GetScrollSnapAlignDumpInfo001
 * @tc.desc: Test GetScrollSnapAlignDumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTestNg, GetScrollSnapAlignDumpInfo001, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, scrollPattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = AceType::MakeRefPtr<ScrollLayoutProperty>();
    layoutProperty->UpdateScrollSnapAlign(ScrollSnapAlign::NONE);
    frameNode->layoutProperty_ = layoutProperty;
    scrollPattern->frameNode_ = frameNode;
    auto json = JsonUtil::Create(true);
    scrollPattern->GetScrollSnapAlignDumpInfo(json);
    EXPECT_EQ(json->GetString("snapAlign"), "ScrollSnapAlign::NONE");
}

/**
 * @tc.name: GetScrollSnapAlignDumpInfo002
 * @tc.desc: Test GetScrollSnapAlignDumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTestNg, GetScrollSnapAlignDumpInfo002, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, scrollPattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = AceType::MakeRefPtr<ScrollLayoutProperty>();
    layoutProperty->UpdateScrollSnapAlign(ScrollSnapAlign::START);
    frameNode->layoutProperty_ = layoutProperty;
    scrollPattern->frameNode_ = frameNode;
    auto json = JsonUtil::Create(true);
    scrollPattern->GetScrollSnapAlignDumpInfo(json);
    EXPECT_EQ(json->GetString("snapAlign"), "ScrollSnapAlign::START");
}

/**
 * @tc.name: GetScrollSnapAlignDumpInfo003
 * @tc.desc: Test GetScrollSnapAlignDumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTestNg, GetScrollSnapAlignDumpInfo003, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, scrollPattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = AceType::MakeRefPtr<ScrollLayoutProperty>();
    layoutProperty->UpdateScrollSnapAlign(ScrollSnapAlign::CENTER);
    frameNode->layoutProperty_ = layoutProperty;
    scrollPattern->frameNode_ = frameNode;
    auto json = JsonUtil::Create(true);
    scrollPattern->GetScrollSnapAlignDumpInfo(json);
    EXPECT_EQ(json->GetString("snapAlign"), "ScrollSnapAlign::CENTER");
}

/**
 * @tc.name: GetScrollSnapAlignDumpInfo004
 * @tc.desc: Test GetScrollSnapAlignDumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTestNg, GetScrollSnapAlignDumpInfo004, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, scrollPattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = AceType::MakeRefPtr<ScrollLayoutProperty>();
    layoutProperty->UpdateScrollSnapAlign(ScrollSnapAlign::END);
    frameNode->layoutProperty_ = layoutProperty;
    scrollPattern->frameNode_ = frameNode;
    auto json = JsonUtil::Create(true);
    scrollPattern->GetScrollSnapAlignDumpInfo(json);
    EXPECT_EQ(json->GetString("snapAlign"), "ScrollSnapAlign::END");
}

/**
 * @tc.name: GetScrollSnapAlignDumpInfo005
 * @tc.desc: Test GetScrollSnapAlignDumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTestNg, GetScrollSnapAlignDumpInfo005, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, scrollPattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = AceType::MakeRefPtr<ScrollLayoutProperty>();
    int32_t number = 6;
    layoutProperty->UpdateScrollSnapAlign(static_cast<ScrollSnapAlign>(number));
    frameNode->layoutProperty_ = layoutProperty;
    scrollPattern->frameNode_ = frameNode;
    auto json = JsonUtil::Create(true);
    scrollPattern->GetScrollSnapAlignDumpInfo(json);
    EXPECT_EQ(json->GetString("snapAlign"), "");
}

/**
 * @tc.name: GetChildrenExpandedSize01
 * @tc.desc: Test GetChildrenExpandedSize
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTestNg, GetChildrenExpandedSize01, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG, 2, scrollPattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = AceType::MakeRefPtr<ScrollLayoutProperty>();
    frameNode->layoutProperty_ = layoutProperty;
    SizeF viewPort(2.0f, 4.0f);
    scrollPattern->viewPort_ = viewPort;
    SizeF viewPortExtent(1.0f, 3.0f);
    scrollPattern->viewPortExtent_ = viewPortExtent;
    scrollPattern->axis_ = Axis::VERTICAL;
    auto result = scrollPattern->GetChildrenExpandedSize();
    EXPECT_EQ(result.Width(), 2.0f);
    EXPECT_EQ(result.Height(), 3.0f);
}

/**
 * @tc.name: GetChildrenExpandedSize02
 * @tc.desc: Test GetChildrenExpandedSize
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTestNg, GetChildrenExpandedSize02, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG, 2, scrollPattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = AceType::MakeRefPtr<ScrollLayoutProperty>();
    frameNode->layoutProperty_ = layoutProperty;
    SizeF viewPort(2.0f, 4.0f);
    scrollPattern->viewPort_ = viewPort;
    SizeF viewPortExtent_(1.0f, 3.0f);
    scrollPattern->viewPortExtent_ = viewPortExtent_;
    scrollPattern->axis_ = Axis::FREE;
    auto result = scrollPattern->GetChildrenExpandedSize();
    EXPECT_EQ(result.Width(), 0.0f);
    EXPECT_EQ(result.Height(), 0.0f);
}

/**
 * @tc.name: GetChildrenExpandedSize03
 * @tc.desc: Test GetChildrenExpandedSize
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTestNg, GetChildrenExpandedSize03, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG, 2, scrollPattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = AceType::MakeRefPtr<ScrollLayoutProperty>();
    frameNode->layoutProperty_ = layoutProperty;
    SizeF viewPort(2.0f, 4.0f);
    scrollPattern->viewPort_ = viewPort;
    SizeF viewPortExtent_(1.0f, 3.0f);
    scrollPattern->viewPortExtent_ = viewPortExtent_;
    scrollPattern->axis_ = Axis::HORIZONTAL;
    SizeF sizeF = scrollPattern->GetChildrenExpandedSize();
    EXPECT_EQ(sizeF.Width(), 1.0f);
    EXPECT_EQ(sizeF.Height(), 4.0f);
}

/**
 * @tc.name: GetChildrenExpandedSize04
 * @tc.desc: Test GetChildrenExpandedSize
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTestNg, GetChildrenExpandedSize04, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG, 2, scrollPattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = AceType::MakeRefPtr<ScrollLayoutProperty>();
    frameNode->layoutProperty_ = layoutProperty;
    SizeF viewPort(2.0f, 4.0f);
    scrollPattern->viewPort_ = viewPort;
    SizeF viewPortExtent_(1.0f, 3.0f);
    scrollPattern->viewPortExtent_ = viewPortExtent_;
    scrollPattern->axis_ = Axis::NONE;
    SizeF sizeF = scrollPattern->GetChildrenExpandedSize();
    EXPECT_EQ(sizeF.Width(), 0.0f);
    EXPECT_EQ(sizeF.Height(), 0.0f);
}


/**
 * @tc.name: CaleSnapOffsetsByInterval001
 * @tc.desc: Test CaleSnapOffsetsByInterval
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTestNg, CaleSnapOffsetsByInterval001, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG, 2, scrollPattern);
    ASSERT_NE(frameNode, nullptr);
    SizeF viewPort(2.0f, 4.0f);
    scrollPattern->viewPort_ = viewPort;
    auto layoutProperty = AceType::MakeRefPtr<ScrollLayoutProperty>();
    int32_t number = 6;
    layoutProperty->UpdateScrollSnapAlign(static_cast<ScrollSnapAlign>(number));
    frameNode->layoutProperty_ = layoutProperty;
    scrollPattern->frameNode_ = frameNode;
    Dimension intervalSize(2.0f, DimensionUnit::PERCENT);
    scrollPattern->intervalSize_ = intervalSize;
    SizeF viewPortExtent(4.0f, 8.0f);
    scrollPattern->viewPortExtent_ = viewPortExtent;
    scrollPattern->scrollableDistance_ = -2.0f;
    Dimension dimension(2.0f);
    scrollPattern->snapPaginations_ = { dimension };
    scrollPattern->snapOffsets_ = { 2.0f, 3.0f, 4.0f, 5.0f };
    scrollPattern->CaleSnapOffsetsByInterval(ScrollSnapAlign::START);
    EXPECT_EQ(*(scrollPattern->snapOffsets_.rbegin()), 0.0f);
}

/**
 * @tc.name: CaleSnapOffsetsByInterval002
 * @tc.desc: Test CaleSnapOffsetsByInterval
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTestNg, CaleSnapOffsetsByInterval002, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG, 2, scrollPattern);
    ASSERT_NE(frameNode, nullptr);
    SizeF viewPort(2.0f, 4.0f);
    scrollPattern->viewPort_ = viewPort;
    auto layoutProperty = AceType::MakeRefPtr<ScrollLayoutProperty>();
    int32_t number = 6;
    layoutProperty->UpdateScrollSnapAlign(static_cast<ScrollSnapAlign>(number));
    frameNode->layoutProperty_ = layoutProperty;
    scrollPattern->frameNode_ = frameNode;
    Dimension intervalSize(2.0f, DimensionUnit::PERCENT);
    scrollPattern->intervalSize_ = intervalSize;
    SizeF viewPortExtent(4.0f, 8.0f);
    scrollPattern->viewPortExtent_ = viewPortExtent;
    scrollPattern->scrollableDistance_ = -2.0f;
    Dimension dimension(2.0f);
    scrollPattern->snapPaginations_ = { dimension };
    scrollPattern->snapOffsets_ = { 2.0f, 3.0f, 4.0f, 5.0f };
    scrollPattern->CaleSnapOffsetsByInterval(ScrollSnapAlign::CENTER);
    EXPECT_EQ(*(scrollPattern->snapOffsets_.rbegin()), -2.0f);
}

/**
 * @tc.name: CaleSnapOffsetsByInterval003
 * @tc.desc: Test CaleSnapOffsetsByInterval
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTestNg, CaleSnapOffsetsByInterval003, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG, 2, scrollPattern);
    ASSERT_NE(frameNode, nullptr);
    SizeF viewPort(2.0f, 4.0f);
    scrollPattern->viewPort_ = viewPort;
    auto layoutProperty = AceType::MakeRefPtr<ScrollLayoutProperty>();
    int32_t number = 6;
    layoutProperty->UpdateScrollSnapAlign(static_cast<ScrollSnapAlign>(number));
    frameNode->layoutProperty_ = layoutProperty;
    scrollPattern->frameNode_ = frameNode;
    Dimension intervalSize(2.0f, DimensionUnit::PERCENT);
    scrollPattern->intervalSize_ = intervalSize;
    SizeF viewPortExtent(4.0f, 8.0f);
    scrollPattern->viewPortExtent_ = viewPortExtent;
    scrollPattern->scrollableDistance_ = -2.0f;
    Dimension dimension(2.0f);
    scrollPattern->snapPaginations_ = { dimension };
    scrollPattern->snapOffsets_ = { 2.0f, 3.0f, 4.0f, 5.0f };
    scrollPattern->CaleSnapOffsetsByInterval(ScrollSnapAlign::END);
    EXPECT_EQ(*(scrollPattern->snapOffsets_.rbegin()), -4.0f);
}

/**
 * @tc.name: CaleSnapOffsetsByInterval004
 * @tc.desc: Test CaleSnapOffsetsByInterval
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTestNg, CaleSnapOffsetsByInterval004, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG, 2, scrollPattern);
    ASSERT_NE(frameNode, nullptr);
    SizeF viewPort(5.0f, 1.0f);
    scrollPattern->viewPort_ = viewPort;
    auto layoutProperty = AceType::MakeRefPtr<ScrollLayoutProperty>();
    int32_t number = 6;
    layoutProperty->UpdateScrollSnapAlign(static_cast<ScrollSnapAlign>(number));
    frameNode->layoutProperty_ = layoutProperty;
    scrollPattern->frameNode_ = frameNode;
    Dimension intervalSize(2.0f, DimensionUnit::PERCENT);
    scrollPattern->intervalSize_ = intervalSize;
    SizeF viewPortExtent(4.0f, 8.0f);
    scrollPattern->viewPortExtent_ = viewPortExtent;
    scrollPattern->scrollableDistance_ = 2.0f;
    Dimension dimension(2.0f);
    scrollPattern->snapPaginations_ = { dimension };
    scrollPattern->snapOffsets_ = { 2.0f, 3.0f, 4.0f, 5.0f };
    scrollPattern->CaleSnapOffsetsByInterval(ScrollSnapAlign::NONE);
    EXPECT_EQ(*(scrollPattern->snapOffsets_.rbegin()), -2.0f);
}

/**
 * @tc.name: CaleSnapOffsetsByInterval005
 * @tc.desc: Test CaleSnapOffsetsByInterval
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTestNg, CaleSnapOffsetsByInterval005, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG, 2, scrollPattern);
    ASSERT_NE(frameNode, nullptr);
    SizeF viewPort(5.0f, 1.0f);
    scrollPattern->viewPort_ = viewPort;
    auto layoutProperty = AceType::MakeRefPtr<ScrollLayoutProperty>();
    int32_t number = 6;
    layoutProperty->UpdateScrollSnapAlign(static_cast<ScrollSnapAlign>(number));
    frameNode->layoutProperty_ = layoutProperty;
    scrollPattern->frameNode_ = frameNode;
    Dimension intervalSize(2.0f, DimensionUnit::PERCENT);
    scrollPattern->intervalSize_ = intervalSize;
    SizeF viewPortExtent(-4.0f, 8.0f);
    scrollPattern->viewPortExtent_ = viewPortExtent;
    scrollPattern->scrollableDistance_ = 10.0f;
    Dimension dimension(2.0f);
    scrollPattern->snapPaginations_ = { dimension };
    scrollPattern->snapOffsets_ = { 2.0f, 3.0f, 4.0f, 5.0f };
    scrollPattern->CaleSnapOffsetsByInterval(ScrollSnapAlign::START);
    EXPECT_EQ(*(scrollPattern->snapOffsets_.rbegin()), -8.0f);
}

/**
 * @tc.name: CaleSnapOffsetsByInterval006
 * @tc.desc: Test CaleSnapOffsetsByInterval
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTestNg, CaleSnapOffsetsByInterval006, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG, 2, scrollPattern);
    ASSERT_NE(frameNode, nullptr);
    SizeF viewPort(5.0f, 1.0f);
    scrollPattern->viewPort_ = viewPort;
    auto layoutProperty = AceType::MakeRefPtr<ScrollLayoutProperty>();
    int32_t number = 6;
    layoutProperty->UpdateScrollSnapAlign(static_cast<ScrollSnapAlign>(number));
    frameNode->layoutProperty_ = layoutProperty;
    scrollPattern->frameNode_ = frameNode;
    Dimension intervalSize(2.0f, DimensionUnit::PERCENT);
    scrollPattern->intervalSize_ = intervalSize;
    SizeF viewPortExtent(-4.0f, 8.0f);
    scrollPattern->viewPortExtent_ = viewPortExtent;
    scrollPattern->scrollableDistance_ = 5.0f;
    Dimension dimension(2.0f);
    scrollPattern->snapPaginations_ = { dimension };
    scrollPattern->snapOffsets_ = { 2.0f, 3.0f, 4.0f, 5.0f };
    scrollPattern->CaleSnapOffsetsByInterval(ScrollSnapAlign::START);
    EXPECT_EQ(*(scrollPattern->snapOffsets_.rbegin()), -4.0f);
}

/**
 * @tc.name: CaleSnapOffsetsByInterval007
 * @tc.desc: Test CaleSnapOffsetsByInterval
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTestNg, CaleSnapOffsetsByInterval007, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG, 2, scrollPattern);
    ASSERT_NE(frameNode, nullptr);
    SizeF viewPort(5.0f, 1.0f);
    scrollPattern->viewPort_ = viewPort;
    auto layoutProperty = AceType::MakeRefPtr<ScrollLayoutProperty>();
    int32_t number = 6;
    layoutProperty->UpdateScrollSnapAlign(static_cast<ScrollSnapAlign>(number));
    frameNode->layoutProperty_ = layoutProperty;
    scrollPattern->frameNode_ = frameNode;
    Dimension intervalSize(2.0f, DimensionUnit::PERCENT);
    scrollPattern->intervalSize_ = intervalSize;
    SizeF viewPortExtent(-4.0f, 1.0f);
    scrollPattern->viewPortExtent_ = viewPortExtent;
    scrollPattern->scrollableDistance_ = 5.0f;
    Dimension dimension(2.0f);
    scrollPattern->snapPaginations_ = { dimension };
    scrollPattern->snapOffsets_ = { 2.0f, 3.0f, 4.0f, 5.0f };
    scrollPattern->CaleSnapOffsetsByInterval(ScrollSnapAlign::START);
    EXPECT_EQ(*(scrollPattern->snapOffsets_.rbegin()), 0.0f);
}

/**
 * @tc.name: CaleSnapOffsetsByInterval008
 * @tc.desc: Test CaleSnapOffsetsByInterval
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTestNg, CaleSnapOffsetsByInterval008, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG, 2, scrollPattern);
    ASSERT_NE(frameNode, nullptr);
    SizeF viewPort(5.0f, 1.0f);
    scrollPattern->viewPort_ = viewPort;
    auto layoutProperty = AceType::MakeRefPtr<ScrollLayoutProperty>();
    int32_t number = 6;
    layoutProperty->UpdateScrollSnapAlign(static_cast<ScrollSnapAlign>(number));
    frameNode->layoutProperty_ = layoutProperty;
    scrollPattern->frameNode_ = frameNode;
    Dimension intervalSize(2.0f, DimensionUnit::PERCENT);
    scrollPattern->intervalSize_ = intervalSize;
    SizeF viewPortExtent(-4.0f, -1.0f);
    scrollPattern->viewPortExtent_ = viewPortExtent;
    scrollPattern->scrollableDistance_ = -1.0f;
    Dimension dimension(2.0f);
    scrollPattern->snapPaginations_ = { dimension };
    scrollPattern->snapOffsets_ = { 2.0f, 3.0f, 4.0f, 5.0f };
    scrollPattern->CaleSnapOffsetsByInterval(ScrollSnapAlign::CENTER);
    EXPECT_EQ(*(scrollPattern->snapOffsets_.rbegin()), -0.5f);
}

/**
 * @tc.name: CaleSnapOffsetsByInterval009
 * @tc.desc: Test CaleSnapOffsetsByInterval
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTestNg, CaleSnapOffsetsByInterval009, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG, 2, scrollPattern);
    ASSERT_NE(frameNode, nullptr);
    SizeF viewPort(5.0f, 1.0f);
    scrollPattern->viewPort_ = viewPort;
    auto layoutProperty = AceType::MakeRefPtr<ScrollLayoutProperty>();
    int32_t number = 6;
    layoutProperty->UpdateScrollSnapAlign(static_cast<ScrollSnapAlign>(number));
    frameNode->layoutProperty_ = layoutProperty;
    scrollPattern->frameNode_ = frameNode;
    Dimension intervalSize(2.0f, DimensionUnit::PERCENT);
    scrollPattern->intervalSize_ = intervalSize;
    SizeF viewPortExtent(-4.0f, 1.0f);
    scrollPattern->viewPortExtent_ = viewPortExtent;
    scrollPattern->scrollableDistance_ = 1.0f;
    Dimension dimension(2.0f);
    scrollPattern->snapPaginations_ = { dimension };
    scrollPattern->snapOffsets_ = { 2.0f, 3.0f, 4.0f, 5.0f };
    scrollPattern->CaleSnapOffsetsByInterval(ScrollSnapAlign::END);
    EXPECT_EQ(*(scrollPattern->snapOffsets_.rbegin()), -1.0f);
}

/**
 * @tc.name: CaleSnapOffsetsByInterval010
 * @tc.desc: Test CaleSnapOffsetsByInterval
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTestNg, CaleSnapOffsetsByInterval010, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG, 2, scrollPattern);
    ASSERT_NE(frameNode, nullptr);
    SizeF viewPort(5.0f, 1.0f);
    scrollPattern->viewPort_ = viewPort;
    auto layoutProperty = AceType::MakeRefPtr<ScrollLayoutProperty>();
    int32_t number = 0;
    layoutProperty->UpdateScrollSnapAlign(static_cast<ScrollSnapAlign>(number));
    frameNode->layoutProperty_ = layoutProperty;
    scrollPattern->frameNode_ = frameNode;
    Dimension intervalSize(2.0f, DimensionUnit::PERCENT);
    scrollPattern->intervalSize_ = intervalSize;
    SizeF viewPortExtent(-4.0f, 1.0f);
    scrollPattern->viewPortExtent_ = viewPortExtent;
    scrollPattern->scrollableDistance_ = 1.0f;
    Dimension dimension(2.0f);
    scrollPattern->snapPaginations_ = { dimension };
    scrollPattern->snapOffsets_ = { 2.0f, 3.0f, 4.0f, 5.0f };
    ScrollPagingStatus enablePagingStatus = ScrollPagingStatus::VALID;
    scrollPattern->SetEnablePaging(enablePagingStatus);
    scrollPattern->CaleSnapOffsetsByInterval(ScrollSnapAlign::NONE);
    EXPECT_EQ(*(scrollPattern->snapOffsets_.rbegin()), -1.0f);
}

/**
 * @tc.name: CaleSnapOffsetsByInterval011
 * @tc.desc: Test CaleSnapOffsetsByInterval
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTestNg, CaleSnapOffsetsByInterval011, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG, 2, scrollPattern);
    ASSERT_NE(frameNode, nullptr);
    SizeF viewPort(5.0f, 1.0f);
    scrollPattern->viewPort_ = viewPort;
    auto layoutProperty = AceType::MakeRefPtr<ScrollLayoutProperty>();
    int32_t number = 0;
    layoutProperty->UpdateScrollSnapAlign(static_cast<ScrollSnapAlign>(number));
    frameNode->layoutProperty_ = layoutProperty;
    scrollPattern->frameNode_ = frameNode;
    Dimension intervalSize(2.0f, DimensionUnit::PERCENT);
    scrollPattern->intervalSize_ = intervalSize;
    SizeF viewPortExtent(-4.0f, 1.0f);
    scrollPattern->viewPortExtent_ = viewPortExtent;
    scrollPattern->scrollableDistance_ = 0.0f;
    Dimension dimension(2.0f);
    scrollPattern->snapPaginations_ = { dimension };
    scrollPattern->snapOffsets_ = { 2.0f, 3.0f, 4.0f, 5.0f };
    ScrollPagingStatus enablePagingStatus = ScrollPagingStatus::VALID;
    scrollPattern->SetEnablePaging(enablePagingStatus);
    scrollPattern->CaleSnapOffsetsByInterval(ScrollSnapAlign::NONE);
    EXPECT_EQ(*(scrollPattern->snapOffsets_.rbegin()), 0.0f);
}

/**
 * @tc.name: GetPagingDelta001
 * @tc.desc: Test GetPagingDelta
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTestNg, GetPagingDelta001, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    auto result = scrollPattern->GetPagingDelta(2.0f, 3.0f, 4.0f);
    EXPECT_EQ(result, 4.0f);
}

/**
 * @tc.name: GetPagingDelta002
 * @tc.desc: Test GetPagingDelta
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTestNg, GetPagingDelta002, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    auto result = scrollPattern->GetPagingDelta(1.0f, 3.0f, 5.0f);
    EXPECT_EQ(result, 0.0f);
}

/**
 * @tc.name: GetPagingDelta003
 * @tc.desc: Test GetPagingDelta
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTestNg, GetPagingDelta003, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    auto result = scrollPattern->GetPagingDelta(1.0f, 1300.0f, 5.0f);
    EXPECT_EQ(result, 5.0f);
}

/**
 * @tc.name: GetPagingDelta004
 * @tc.desc: Test GetPagingDelta
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTestNg, GetPagingDelta004, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    auto result = scrollPattern->GetPagingDelta(2.0f, 1300.0f, 3.0f);
    EXPECT_EQ(result, 3.0f);
}

/**
 * @tc.name: GetPagingDelta005
 * @tc.desc: Test GetPagingDelta
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTestNg, GetPagingDelta005, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    auto result = scrollPattern->GetPagingDelta(2.0f, 3.0f, 3.0f);
    EXPECT_EQ(result, 3.0f);
}

/**
 * @tc.name: GetPagingDelta006
 * @tc.desc: Test GetPagingDelta
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTestNg, GetPagingDelta006, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    auto result = scrollPattern->GetPagingDelta(2.0f, -3.0f, 3.0f);
    EXPECT_EQ(result, 3.0f);
}

/**
 * @tc.name: GetPagingDelta007
 * @tc.desc: Test GetPagingDelta
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTestNg, GetPagingDelta007, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    auto result = scrollPattern->GetPagingDelta(-1.0f, 1300.0f, 3.0f);
    EXPECT_EQ(result, 0.0f);
}

/**
 * @tc.name: GetPagingDelta008
 * @tc.desc: Test GetPagingDelta
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTestNg, GetPagingDelta008, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    auto result = scrollPattern->GetPagingDelta(-1.0f, 1300.0f, -4.0f);
    EXPECT_EQ(result, 0.0f);
}

/**
 * @tc.name: DoJump001
 * @tc.desc: Test DoJump
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTestNg, DoJump001, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    scrollPattern->axis_ = Axis::HORIZONTAL;
    scrollPattern->direction_ = FlexDirection::ROW_REVERSE;
    scrollPattern->currentOffset_ = 0.0f;
    scrollPattern->scrollableDistance_ = 1.0f;
    scrollPattern->canStayOverScroll_ = false;
    scrollPattern->DoJump(0.0f, SCROLL_FROM_JUMP);
    EXPECT_FALSE(scrollPattern->GetCanStayOverScroll());
    scrollPattern->canStayOverScroll_ = true;
    scrollPattern->DoJump(0.0f, SCROLL_FROM_JUMP);
    EXPECT_TRUE(scrollPattern->GetCanStayOverScroll());
    scrollPattern->DoJump(10.0f, SCROLL_FROM_JUMP);

    scrollPattern->currentOffset_ = 1.0f;
    scrollPattern->axis_ = Axis::VERTICAL;
    scrollPattern->DoJump(1000.0f, SCROLL_FROM_JUMP);
    EXPECT_TRUE(scrollPattern->IsOutOfBoundary());
}
} // namespace OHOS::Ace::NG