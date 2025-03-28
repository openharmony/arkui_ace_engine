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
} // namespace OHOS::Ace::NG