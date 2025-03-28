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
#define private public
#include "scroll_test_ng.h"

#include "base/memory/ace_type.h"
#undef private
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
 * @tc.name: CreateNodePaintMethod001
 * @tc.desc: Test SetEnablePaging When enablePaging is false
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTestNg, CreateNodePaintMethod001, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    auto host = scrollPattern->GetHost();
    auto layoutProperty = host->GetLayoutProperty<ScrollLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto layoutDirection = layoutProperty->GetNonAutoLayoutDirection();
    auto drawDirection = (layoutDirection == TextDirection::RTL);
    auto scrollEffect = scrollPattern->GetScrollEdgeEffect();
    ASSERT_NE(scrollPattern, nullptr);
    scrollEffect->IsFadeEffect();
    auto paint = AceType::MakeRefPtr<ScrollPaintMethod>(scrollPattern->GetAxis() == Axis::HORIZONTAL, drawDirection);
    scrollPattern->CreateNodePaintMethod();
    paint->SetEdgeEffect(scrollEffect);
    EXPECT_EQ(scrollPattern->GetScrollEdgeEffect(), nullptr);
}

/**
 * @tc.name: CreateNodePaintMethod002
 * @tc.desc: Test SetEnablePaging When enablePaging is false
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTestNg, CreateNodePaintMethod002, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    auto host = scrollPattern->GetHost();
    auto layoutProperty = host->GetLayoutProperty<ScrollLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto layoutDirection = layoutProperty->GetNonAutoLayoutDirection();
    auto drawDirection = (layoutDirection == TextDirection::RTL);
    auto scrollEffect = nullptr;
    ASSERT_NE(scrollPattern, nullptr);
    auto paint = AceType::MakeRefPtr<ScrollPaintMethod>(scrollPattern->GetAxis() == Axis::HORIZONTAL, drawDirection);
    scrollPattern->CreateNodePaintMethod();
    paint->SetEdgeEffect(scrollEffect);
    EXPECT_EQ(scrollPattern->GetScrollEdgeEffect(), nullptr);
}

/**
 * @tc.name: CreateNodePaintMethod003
 * @tc.desc: Test SetEnablePaging When enablePaging is false
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTestNg, CreateNodePaintMethod003, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    auto host = scrollPattern->GetHost();
    auto layoutProperty = host->GetLayoutProperty<ScrollLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto layoutDirection = layoutProperty->GetNonAutoLayoutDirection();
    auto drawDirection = (layoutDirection == TextDirection::RTL);
    auto scrollEffect = scrollPattern->GetScrollEdgeEffect();
    ASSERT_NE(scrollPattern, nullptr);
    scrollEffect->IsRestrictBoundary();
    auto paint = AceType::MakeRefPtr<ScrollPaintMethod>(scrollPattern->GetAxis() == Axis::HORIZONTAL, drawDirection);
    scrollPattern->CreateNodePaintMethod();
    paint->SetEdgeEffect(scrollEffect);
    EXPECT_EQ(scrollPattern->GetScrollEdgeEffect(), nullptr);
}

/**
 * @tc.name: CreateNodePaintMethod004
 * @tc.desc: Test SetEnablePaging When enablePaging is false
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTestNg, CreateNodePaintMethod004, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    auto host = scrollPattern->GetHost();
    auto layoutProperty = host->GetLayoutProperty<ScrollLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto layoutDirection = layoutProperty->GetNonAutoLayoutDirection();
    auto drawDirection = (layoutDirection == TextDirection::RTL);
    auto scrollEffect = scrollPattern->GetScrollEdgeEffect();
    ASSERT_NE(scrollPattern, nullptr);
    scrollEffect->IsNoneEffect();
    auto paint = AceType::MakeRefPtr<ScrollPaintMethod>(scrollPattern->GetAxis() == Axis::HORIZONTAL, drawDirection);
    scrollPattern->CreateNodePaintMethod();
    paint->SetEdgeEffect(scrollEffect);
    EXPECT_EQ(scrollPattern->GetScrollEdgeEffect(), nullptr);
}

/**
 * @tc.name: CreateNodePaintMethod005
 * @tc.desc: Test SetEnablePaging When enablePaging is false
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTestNg, CreateNodePaintMethod005, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    auto host = scrollPattern->GetHost();
    auto layoutProperty = host->GetLayoutProperty<ScrollLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto layoutDirection = layoutProperty->GetNonAutoLayoutDirection();
    auto drawDirection = (layoutDirection == TextDirection::RTL);
    auto scrollEffect = scrollPattern->GetScrollEdgeEffect();
    ASSERT_NE(scrollPattern, nullptr);
    scrollEffect->IsSpringEffect();
    auto paint = AceType::MakeRefPtr<ScrollPaintMethod>(scrollPattern->GetAxis() == Axis::HORIZONTAL, drawDirection);
    scrollPattern->CreateNodePaintMethod();
    paint->SetEdgeEffect(scrollEffect);
    EXPECT_EQ(scrollPattern->GetScrollEdgeEffect(), nullptr);
}
} // namespace OHOS::Ace::NG