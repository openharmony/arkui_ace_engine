/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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
#include "core/components/web/resource/web_delegate.h"
#include "core/components_ng/pattern/web/web_pattern.h"
#undef private

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_v2/inspector/inspector_constants.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class WebPatternKeyboardTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void WebPatternKeyboardTestNg::SetUpTestCase() {}
void WebPatternKeyboardTestNg::TearDownTestCase() {}
void WebPatternKeyboardTestNg::SetUp() {}
void WebPatternKeyboardTestNg::TearDown() {}

/**
 * @tc.name: SetNestedScrollExt001
 * @tc.desc: SetNestedScrollExt.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternKeyboardTestNg, SetNestedScrollExt001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);

    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, [] { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);

    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);

    NestedScrollOptionsExt nestedScroll;
    nestedScroll.scrollUp = NestedScrollMode::SELF_ONLY;
    nestedScroll.scrollDown = NestedScrollMode::SELF_ONLY;

    webPattern->SetNestedScrollExt(nestedScroll);

    NestedScrollOptions expectedOptions;
    expectedOptions.forward = nestedScroll.scrollDown;
    expectedOptions.backward = nestedScroll.scrollUp;

    webPattern->SetNestedScrollExt(nestedScroll);

    EXPECT_EQ(webPattern->nestedScroll_.scrollUp, nestedScroll.scrollUp);
    EXPECT_EQ(webPattern->nestedScroll_.scrollDown, nestedScroll.scrollDown);
    EXPECT_EQ(webPattern->nestedScroll_.scrollLeft, nestedScroll.scrollLeft);
    EXPECT_EQ(webPattern->nestedScroll_.scrollRight, nestedScroll.scrollRight);
#endif
}

/**
 * @tc.name: IsDialogNested001
 * @tc.desc: IsDialogNested.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternKeyboardTestNg, IsDialogNested001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);

    auto nodeId = stack->ClaimNodeId();
    auto rootFrameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(rootFrameNode, nullptr);
    stack->Push(rootFrameNode);

    auto webPatternNodeId = stack->ClaimNodeId();
    auto webPatternFrameNode = FrameNode::GetOrCreateFrameNode(
        V2::WEB_ETS_TAG, webPatternNodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(webPatternFrameNode, nullptr);
    rootFrameNode->SetParent(webPatternFrameNode);

    auto webPattern = webPatternFrameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    bool result = webPattern->IsDialogNested();

    EXPECT_FALSE(result);
#endif
}

/**
 * @tc.name: OnRootLayerChanged001
 * @tc.desc: OnRootLayerChanged.
 * @tc.type: FUNC
 */

HWTEST_F(WebPatternKeyboardTestNg, OnRootLayerChanged001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);

    auto nodeId = stack->ClaimNodeId();
    auto rootFrameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(rootFrameNode, nullptr);
    stack->Push(rootFrameNode);

    auto webPatternNodeId = stack->ClaimNodeId();
    auto webPatternFrameNode = FrameNode::GetOrCreateFrameNode(
        V2::WEB_ETS_TAG, webPatternNodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(webPatternFrameNode, nullptr);
    rootFrameNode->SetParent(webPatternFrameNode);

    auto webPattern = webPatternFrameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);

    webPattern->layoutMode_ = WebLayoutMode::FIT_CONTENT;
    webPattern->OnRootLayerChanged(200, 300);

    EXPECT_EQ(webPattern->rootLayerWidth_, 200);
    EXPECT_EQ(webPattern->rootLayerHeight_, 300);

    webPattern->layoutMode_ = WebLayoutMode::FIT_CONTENT;
    webPattern->OnRootLayerChanged(400, 500);

    EXPECT_EQ(webPattern->rootLayerWidth_, 400);
    EXPECT_EQ(webPattern->rootLayerHeight_, 500);
#endif
}

/**
 * @tc.name: ReleaseResizeHold001
 * @tc.desc: ReleaseResizeHold.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternKeyboardTestNg, ReleaseResizeHold001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);

    auto nodeId = stack->ClaimNodeId();
    auto rootFrameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(rootFrameNode, nullptr);
    stack->Push(rootFrameNode);

    auto webPatternNodeId = stack->ClaimNodeId();
    auto webPatternFrameNode = FrameNode::GetOrCreateFrameNode(
        V2::WEB_ETS_TAG, webPatternNodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(webPatternFrameNode, nullptr);
    rootFrameNode->SetParent(webPatternFrameNode);

    auto webPattern = webPatternFrameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);

    webPattern->layoutMode_ = WebLayoutMode::FIT_CONTENT;
    webPattern->rootLayerChangeSize_ = Size(100, 200);

    webPattern->ReleaseResizeHold();
#endif
}

/**
 * @tc.name: FilterScrollEvent001
 * @tc.desc: FilterScrollEvent.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternKeyboardTestNg, FilterScrollEvent001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);

    auto nodeId = stack->ClaimNodeId();
    auto webPatternFrameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(webPatternFrameNode, nullptr);
    stack->Push(webPatternFrameNode);

    auto webPattern = webPatternFrameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);

    webPattern->OnScrollStart(1.0, 2.0);
    bool isConsumed = webPattern->FilterScrollEvent(100, 50, 10, 5);
    EXPECT_FALSE(isConsumed);
#endif
}

/**
 * @tc.name: FilterScrollEvent002
 * @tc.desc: FilterScrollEvent.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternKeyboardTestNg, FilterScrollEvent002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);

    auto nodeId = stack->ClaimNodeId();
    auto webPatternFrameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(webPatternFrameNode, nullptr);
    stack->Push(webPatternFrameNode);

    auto webPattern = webPatternFrameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);

    bool isConsumed = webPattern->FilterScrollEvent(100, 50, 10, 5);
    EXPECT_FALSE(isConsumed);
#endif
}

/**
 * @tc.name: FilterScrollEventHandleOffset001
 * @tc.desc: FilterScrollEventHandleOffset.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternKeyboardTestNg, FilterScrollEventHandleOffset001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);

    webPattern->expectedScrollAxis_ = Axis::HORIZONTAL;
    webPattern->isParentReachEdge_ = false;

    float offset = 10.0f;
    bool result = webPattern->FilterScrollEventHandleOffset(offset);
    EXPECT_FALSE(result);
#endif
}

/**
 * @tc.name: CheckParentScroll001
 * @tc.desc: CheckParentScroll.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternKeyboardTestNg, CheckParentScroll001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);

    auto nodeId = stack->ClaimNodeId();
    auto rootFrameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(rootFrameNode, nullptr);
    stack->Push(rootFrameNode);

    auto webPattern = rootFrameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);

    webPattern->expectedScrollAxis_ = Axis::VERTICAL;
    EXPECT_FALSE(webPattern->CheckParentScroll(1.0f, NestedScrollMode::PARALLEL));
#endif
}

/**
 * @tc.name: CheckParentScroll002
 * @tc.desc: CheckParentScroll.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternKeyboardTestNg, CheckParentScroll002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);

    auto nodeId = stack->ClaimNodeId();
    auto rootFrameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(rootFrameNode, nullptr);
    stack->Push(rootFrameNode);

    auto webPattern = rootFrameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);

    webPattern->expectedScrollAxis_ = Axis::HORIZONTAL;
    EXPECT_FALSE(webPattern->CheckParentScroll(1.0f, NestedScrollMode::PARALLEL));
#endif
}

/**
 * @tc.name: CheckParentScroll003
 * @tc.desc: CheckParentScroll.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternKeyboardTestNg, CheckParentScroll003, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);

    auto nodeId = stack->ClaimNodeId();
    auto rootFrameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(rootFrameNode, nullptr);
    stack->Push(rootFrameNode);

    auto webPattern = rootFrameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);

    webPattern->expectedScrollAxis_ = Axis::VERTICAL;
    EXPECT_FALSE(webPattern->CheckParentScroll(-1.0f, NestedScrollMode::PARALLEL));
#endif
}

/**
 * @tc.name: CheckParentScroll004
 * @tc.desc: CheckParentScroll.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternKeyboardTestNg, CheckParentScroll004, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);

    auto nodeId = stack->ClaimNodeId();
    auto rootFrameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(rootFrameNode, nullptr);
    stack->Push(rootFrameNode);

    auto webPattern = rootFrameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);

    webPattern->expectedScrollAxis_ = Axis::HORIZONTAL;
    EXPECT_FALSE(webPattern->CheckParentScroll(-1.0f, NestedScrollMode::PARALLEL));
#endif
}

/**
 * @tc.name: CheckParentScroll005
 * @tc.desc: CheckParentScroll.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternKeyboardTestNg, CheckParentScroll005, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);

    auto nodeId = stack->ClaimNodeId();
    auto rootFrameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(rootFrameNode, nullptr);
    stack->Push(rootFrameNode);

    auto webPattern = rootFrameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);

    EXPECT_TRUE(webPattern->CheckParentScroll(1.0f, NestedScrollMode::SELF_ONLY));
#endif
}

/**
 * @tc.name: CheckParentScroll006
 * @tc.desc: CheckParentScroll.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternKeyboardTestNg, CheckParentScroll006, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);

    auto nodeId = stack->ClaimNodeId();
    auto rootFrameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(rootFrameNode, nullptr);
    stack->Push(rootFrameNode);

    auto webPattern = rootFrameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);

    EXPECT_TRUE(webPattern->CheckParentScroll(-1.0f, NestedScrollMode::SELF_ONLY));
#endif
}

/**
 * @tc.name: CheckOverParentScroll001
 * @tc.desc: CheckOverParentScroll.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternKeyboardTestNg, CheckOverParentScroll001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);

    auto nodeId = stack->ClaimNodeId();
    auto rootFrameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(rootFrameNode, nullptr);
    stack->Push(rootFrameNode);

    auto webPattern = rootFrameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);

    webPattern->expectedScrollAxis_ = Axis::VERTICAL;
    EXPECT_FALSE(webPattern->CheckParentScroll(1.0f, NestedScrollMode::PARALLEL));
#endif
}

/**
 * @tc.name: CheckOverParentScroll002
 * @tc.desc: CheckOverParentScroll.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternKeyboardTestNg, CheckOverParentScroll002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);

    auto nodeId = stack->ClaimNodeId();
    auto rootFrameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(rootFrameNode, nullptr);
    stack->Push(rootFrameNode);

    auto webPattern = rootFrameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);

    webPattern->expectedScrollAxis_ = Axis::HORIZONTAL;
    EXPECT_FALSE(webPattern->CheckParentScroll(1.0f, NestedScrollMode::PARALLEL));
#endif
}

/**
 * @tc.name: CheckOverParentScroll003
 * @tc.desc: CheckOverParentScroll.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternKeyboardTestNg, CheckOverParentScroll003, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);

    auto nodeId = stack->ClaimNodeId();
    auto rootFrameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(rootFrameNode, nullptr);
    stack->Push(rootFrameNode);

    auto webPattern = rootFrameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);

    webPattern->expectedScrollAxis_ = Axis::VERTICAL;
    EXPECT_FALSE(webPattern->CheckParentScroll(-1.0f, NestedScrollMode::PARALLEL));
#endif
}

/**
 * @tc.name: CheckOverParentScroll004
 * @tc.desc: CheckOverParentScroll.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternKeyboardTestNg, CheckOverParentScroll004, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);

    auto nodeId = stack->ClaimNodeId();
    auto rootFrameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(rootFrameNode, nullptr);
    stack->Push(rootFrameNode);

    auto webPattern = rootFrameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);

    webPattern->expectedScrollAxis_ = Axis::HORIZONTAL;
    EXPECT_FALSE(webPattern->CheckParentScroll(-1.0f, NestedScrollMode::PARALLEL));
#endif
}

/**
 * @tc.name: CheckOverParentScroll005
 * @tc.desc: CheckOverParentScroll.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternKeyboardTestNg, CheckOverParentScroll005, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);

    auto nodeId = stack->ClaimNodeId();
    auto rootFrameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(rootFrameNode, nullptr);
    stack->Push(rootFrameNode);

    auto webPattern = rootFrameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);

    EXPECT_TRUE(webPattern->CheckParentScroll(1.0f, NestedScrollMode::SELF_ONLY));
#endif
}

/**
 * @tc.name: CheckOverParentScroll006
 * @tc.desc: CheckOverParentScroll.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternKeyboardTestNg, CheckOverParentScroll006, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);

    auto nodeId = stack->ClaimNodeId();
    auto rootFrameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(rootFrameNode, nullptr);
    stack->Push(rootFrameNode);

    auto webPattern = rootFrameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);

    EXPECT_TRUE(webPattern->CheckParentScroll(-1.0f, NestedScrollMode::SELF_ONLY));
#endif
}

/**
 * @tc.name: FilterScrollEventHandlevVlocity001
 * @tc.desc: FilterScrollEventHandlevVlocity.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternKeyboardTestNg, FilterScrollEventHandlevVlocity001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);

    auto nodeId = stack->ClaimNodeId();
    auto rootFrameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(rootFrameNode, nullptr);
    stack->Push(rootFrameNode);

    auto webPatternNodeId = stack->ClaimNodeId();
    auto webPatternFrameNode = FrameNode::GetOrCreateFrameNode(
        V2::WEB_ETS_TAG, webPatternNodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(webPatternFrameNode, nullptr);
    rootFrameNode->SetParent(webPatternFrameNode);

    auto webPattern = webPatternFrameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);

    webPattern->isParentReachEdge_ = true;

    bool result = webPattern->FilterScrollEventHandlevVlocity(100.0f);
    EXPECT_FALSE(result);

    webPattern->isParentReachEdge_ = false;
    result = webPattern->FilterScrollEventHandlevVlocity(-100.0f);
    EXPECT_FALSE(result);
#endif
}

/**
 * @tc.name: IsDefaultFocusNodeExist001
 * @tc.desc: IsDefaultFocusNodeExist.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternKeyboardTestNg, IsDefaultFocusNodeExist001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);

    auto result = webPattern->IsDefaultFocusNodeExist();
    EXPECT_FALSE(result);
#endif
}

/**
 * @tc.name: IsDefaultFocusNodeExist002
 * @tc.desc: IsDefaultFocusNodeExist.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternKeyboardTestNg, IsDefaultFocusNodeExist002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);

    auto result = webPattern->IsDefaultFocusNodeExist();
    EXPECT_FALSE(result);
#endif
}

/**
 * @tc.name: InitSlideUpdateListener001
 * @tc.desc: InitSlideUpdateListener.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternKeyboardTestNg, InitSlideUpdateListener001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);

    auto nodeId = stack->ClaimNodeId();
    auto rootFrameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(rootFrameNode, nullptr);
    stack->Push(rootFrameNode);

    auto webPatternNodeId = stack->ClaimNodeId();
    auto webPatternFrameNode = FrameNode::GetOrCreateFrameNode(
        V2::WEB_ETS_TAG, webPatternNodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(webPatternFrameNode, nullptr);
    rootFrameNode->SetParent(webPatternFrameNode);

    auto scrollPatternNodeId = stack->ClaimNodeId();
    auto scrollPatternFrameNode = FrameNode::GetOrCreateFrameNode(
        V2::LIST_ETS_TAG, scrollPatternNodeId, []() { return AceType::MakeRefPtr<ScrollPattern>(); });
    ASSERT_NE(scrollPatternFrameNode, nullptr);
    webPatternFrameNode->SetParent(scrollPatternFrameNode);

    auto webPattern = webPatternFrameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);

    auto scrollPattern = scrollPatternFrameNode->GetPattern<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);

    webPattern->InitSlideUpdateListener();
    ASSERT_NE(webPattern->renderSurface_, nullptr);
    webPattern->InitSlideUpdateListener();
#endif
}

/**
 * @tc.name: UpdateSlideOffset001
 * @tc.desc: UpdateSlideOffset.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternKeyboardTestNg, UpdateSlideOffset001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);

    webPattern->syncAxis_ = Axis::HORIZONTAL;
    webPattern->UpdateSlideOffset();
#endif
}

/**
 * @tc.name: UpdateSlideOffset002
 * @tc.desc: UpdateSlideOffset.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternKeyboardTestNg, UpdateSlideOffset002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);

    webPattern->syncAxis_ = Axis::VERTICAL;
    webPattern->UpdateSlideOffset();
#endif
}

/**
 * @tc.name: CalculateHorizontalDrawRect001
 * @tc.desc: CalculateHorizontalDrawRect.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternKeyboardTestNg, CalculateHorizontalDrawRect001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);

    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);

    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->fitContentOffset_.SetX(10);
    webPattern->CalculateHorizontalDrawRect();

#endif
}

/**
 * @tc.name: CalculateHorizontalDrawRect002
 * @tc.desc: CalculateHorizontalDrawRect.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternKeyboardTestNg, CalculateHorizontalDrawRect002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);

    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);

    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->fitContentOffset_.SetX(-10);
    webPattern->CalculateHorizontalDrawRect();

#endif
}

/**
 * @tc.name: CalculateVerticalDrawRect001
 * @tc.desc: CalculateVerticalDrawRect.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternKeyboardTestNg, CalculateVerticalDrawRect001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);

    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);

    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);

    webPattern->fitContentOffset_.SetY(10);
    webPattern->CalculateVerticalDrawRect();
#endif
}

/**
 * @tc.name: CalculateVerticalDrawRect002
 * @tc.desc: CalculateVerticalDrawRect.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternKeyboardTestNg, CalculateVerticalDrawRect002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);

    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);

    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);

    webPattern->fitContentOffset_.SetY(-10);
    webPattern->CalculateVerticalDrawRect();
#endif
}

/**
 * @tc.name: PostTaskToUI001
 * @tc.desc: PostTaskToUI.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternKeyboardTestNg, PostTaskToUI001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);

    auto task = []() {};
    webPattern->PostTaskToUI(task, "testTask");
#endif
}

/**
 * @tc.name: SetDrawRect001
 * @tc.desc: SetDrawRect.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternKeyboardTestNg, SetDrawRect001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);

    auto nodeId = stack->ClaimNodeId();
    auto rootFrameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(rootFrameNode, nullptr);
    stack->Push(rootFrameNode);

    auto webPatternNodeId = stack->ClaimNodeId();
    auto webPatternFrameNode = FrameNode::GetOrCreateFrameNode(
        V2::WEB_ETS_TAG, webPatternNodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(webPatternFrameNode, nullptr);
    rootFrameNode->SetParent(webPatternFrameNode);

    auto webPattern = webPatternFrameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);

    webPattern->SetDrawRect(10, 20, 100, 200);

    EXPECT_EQ(webPattern->drawRectWidth_, 100);
    EXPECT_EQ(webPattern->drawRectHeight_, 200);
#endif
}

/**
 * @tc.name: GetPendingSizeStatus001
 * @tc.desc: GetPendingSizeStatus.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternKeyboardTestNg, GetPendingSizeStatus001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);

    auto nodeId = stack->ClaimNodeId();
    auto rootFrameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(rootFrameNode, nullptr);
    stack->Push(rootFrameNode);

    auto webPatternNodeId = stack->ClaimNodeId();
    auto webPatternFrameNode = FrameNode::GetOrCreateFrameNode(
        V2::WEB_ETS_TAG, webPatternNodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(webPatternFrameNode, nullptr);
    rootFrameNode->SetParent(webPatternFrameNode);

    auto webPattern = webPatternFrameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    EXPECT_FALSE(webPattern->GetPendingSizeStatus());

    webPattern->delegate_ = nullptr;
    EXPECT_FALSE(webPattern->GetPendingSizeStatus());
#endif
} // namespace OHOS::Ace::NG

/**
 * @tc.name: CreateNodePaintMethod001
 * @tc.desc: CreateNodePaintMethod.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternKeyboardTestNg, CreateNodePaintMethod001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);

    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);

    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);

    auto nodePaintMethod = webPattern->CreateNodePaintMethod();
    ASSERT_NE(nodePaintMethod, nullptr);
#endif
}

/**
 * @tc.name: UpdateFocusedAccessibilityId001
 * @tc.desc: UpdateFocusedAccessibilityId.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternKeyboardTestNg, UpdateFocusedAccessibilityId001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    // 设置栈和 FrameNode
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);

    webPattern->accessibilityState_ = false;
    webPattern->UpdateFocusedAccessibilityId(1);

    webPattern->accessibilityState_ = true;
    webPattern->UpdateFocusedAccessibilityId(-1);
#endif
}

/**
 * @tc.name: SetTouchEventInfo001
 * @tc.desc: SetTouchEventInfo.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternKeyboardTestNg, SetTouchEventInfo001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);

    auto nodeId = stack->ClaimNodeId();
    auto rootFrameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, [this] { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(rootFrameNode, nullptr);
    stack->Push(rootFrameNode);

    auto webPatternNodeId = stack->ClaimNodeId();
    auto webPatternFrameNode = FrameNode::GetOrCreateFrameNode(
        V2::WEB_ETS_TAG, webPatternNodeId, [this] { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(webPatternFrameNode, nullptr);
    rootFrameNode->SetParent(webPatternFrameNode);

    auto webPattern = webPatternFrameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);

    TouchEvent touchEvent;
    touchEvent.id = 1;
    touchEvent.type = TouchType::DOWN;
    touchEvent.x = 100.0f;
    touchEvent.y = 100.0f;

    TouchEventInfo touchEventInfo { "touchEvent" };
    webPattern->SetTouchEventInfo(touchEvent, touchEventInfo, "embedId");
#endif
}

/**
 * @tc.name: GetAccessibilityFocusRect001
 * @tc.desc: GetAccessibilityFocusRect.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternKeyboardTestNg, GetAccessibilityFocusRect001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);

    auto nodeId = stack->ClaimNodeId();
    auto rootFrameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(rootFrameNode, nullptr);
    stack->Push(rootFrameNode);

    auto webPatternNodeId = stack->ClaimNodeId();
    auto webPatternFrameNode = FrameNode::GetOrCreateFrameNode(
        V2::WEB_ETS_TAG, webPatternNodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(webPatternFrameNode, nullptr);
    rootFrameNode->SetParent(webPatternFrameNode);

    auto webPattern = webPatternFrameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);

    webPattern->accessibilityState_ = true;

    RectT<int32_t> paintRect;
    bool result = webPattern->GetAccessibilityFocusRect(paintRect, 12345);

    EXPECT_FALSE(result);

    webPattern->delegate_ = nullptr;
    result = webPattern->GetAccessibilityFocusRect(paintRect, 12345);
    EXPECT_FALSE(result);

    webPattern->accessibilityState_ = false;
    result = webPattern->GetAccessibilityFocusRect(paintRect, 12345);
    EXPECT_FALSE(result);

    webPattern->accessibilityState_ = true;
    result = webPattern->GetAccessibilityFocusRect(paintRect, 12345);
    EXPECT_FALSE(result);
#endif
}

/**
 * @tc.name: SetTouchLocationInfo001
 * @tc.desc: SetTouchLocationInfo.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternKeyboardTestNg, SetTouchLocationInfo001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);

    auto nodeId = stack->ClaimNodeId();
    auto rootFrameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(rootFrameNode, nullptr);
    stack->Push(rootFrameNode);

    auto webPatternNodeId = stack->ClaimNodeId();
    auto webPatternFrameNode = FrameNode::GetOrCreateFrameNode(
        V2::WEB_ETS_TAG, webPatternNodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(webPatternFrameNode, nullptr);
    rootFrameNode->SetParent(webPatternFrameNode);

    auto webPattern = webPatternFrameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);

    TouchEvent touchEvent;
    touchEvent.id = 1;
    touchEvent.x = 100.0f;
    touchEvent.y = 100.0f;

    TouchEventInfo tempTouchInfo { "onTouch1" };
    TouchEventInfo touchEventInfo { "onTouch2" };

    TouchLocationInfo touchLocationInfo1("onTouch", 1);
    touchLocationInfo1.SetLocalLocation(Offset(110.0f, 110.0f));
    touchLocationInfo1.SetGlobalLocation(Offset(210.0f, 210.0f));
    touchLocationInfo1.SetScreenLocation(Offset(310.0f, 310.0f));
    touchLocationInfo1.SetTouchType(TouchType::DOWN);

    TouchLocationInfo touchLocationInfo2("onTouch", 2);
    touchLocationInfo2.SetLocalLocation(Offset(120.0f, 120.0f));
    touchLocationInfo2.SetGlobalLocation(Offset(220.0f, 220.0f));
    touchLocationInfo2.SetScreenLocation(Offset(320.0f, 320.0f));
    touchLocationInfo2.SetTouchType(TouchType::DOWN);

    tempTouchInfo.AddTouchLocationInfo(std::move(touchLocationInfo1));
    tempTouchInfo.AddTouchLocationInfo(std::move(touchLocationInfo2));

    TouchLocationInfo changedInfo("onTouch", touchEvent.id);
    changedInfo.SetLocalLocation(Offset(touchEvent.x, touchEvent.y));
    changedInfo.SetGlobalLocation(Offset(touchEvent.x + 100.0f, touchEvent.y + 100.0f));
    changedInfo.SetScreenLocation(Offset(touchEvent.x + 200.0f, touchEvent.y + 200.0f));
    changedInfo.SetTouchType(TouchType::DOWN);

    webPattern->SetTouchLocationInfo(touchEvent, changedInfo, tempTouchInfo, touchEventInfo);
    ASSERT_EQ(touchEventInfo.GetTouches().size(), 2u);

    const TouchLocationInfo& firstTouchInfo = touchEventInfo.GetTouches().front();
    EXPECT_EQ(firstTouchInfo.GetFingerId(), 1);
    EXPECT_EQ(firstTouchInfo.GetTouchType(), TouchType::DOWN);

    const TouchLocationInfo& secondTouchInfo = touchEventInfo.GetTouches().back();
    EXPECT_EQ(secondTouchInfo.GetFingerId(), 2);
    EXPECT_EQ(secondTouchInfo.GetTouchType(), TouchType::DOWN);

#endif // OHOS_STANDARD_SYSTEM
}
} // namespace OHOS::Ace::NG