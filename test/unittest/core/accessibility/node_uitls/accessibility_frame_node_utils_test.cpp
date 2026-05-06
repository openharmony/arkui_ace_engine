/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "gtest/gtest.h"
#include <gmock/gmock.h>

#define private public
#define protected public

#include "test/mock/frameworks/base/thread/mock_task_executor.h"
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

#include "base/log/dump_log.h"
#include "base/log/log_wrapper.h"
#include "core/accessibility/node_utils/accessibility_frame_node_utils.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"
#include "core/components_ng/property/accessibility_property.h"
#include "core/pipeline_ng/pipeline_context.h"

#include "test/mock/frameworks/core/components_ng/render/mock_render_context.h"

using namespace testing;
using namespace testing::ext;

namespace {
const float PARENT_SIZE_WIDTH = 100.0f;
const float PARENT_SIZE_HEIGHT = 100.0f;
const float CHILD_SIZE_WIDTH = 20.0f;
const float CHILD_SIZE_HEIGHT = 20.0f;
const float CHILD_OFFSET_BELOW_VISIBLE = 150.0f;
const float CHILD_OFFSET_NEAR_TOP = 5.0f;
const float CHILD_OFFSET_NEAR_BOTTOM = 85.0f;
const float INNER_PARENT_SIZE = 80.0f;
} // namespace

namespace OHOS::Ace::NG {

class AccessibilityFrameNodeUtilsTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

class MockAccessibilityProperty : public AccessibilityProperty {
public:
    MOCK_METHOD(bool, GetAccessibilityInnerVisibleRect, (RectF&), (override));
};

class MockScrollPatternForA11y : public ScrollPattern {
public:
    bool OnScrollCallback(float offset, int32_t source) override
    {
        onScrollCallbackCalled_ = true;
        scrollOffset_ = offset;
        scrollSource_ = source;
        return true;
    }

    bool onScrollCallbackCalled_ = false;
    float scrollOffset_ = 0.0f;
    int32_t scrollSource_ = -1;
};

class MockScrollablePatternNoAbility : public ScrollablePattern {
public:
    Axis GetAxis() const override
    {
        return Axis::NONE;
    }
    bool UpdateCurrentOffset(float delta, int32_t source) override { return false; }
    bool IsAtTop() const override { return true; }
    bool IsAtBottom(bool considerRepeat = false) const override { return true; }
    void UpdateScrollBarOffset() override {}
};

void AccessibilityFrameNodeUtilsTest::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
    MockContainer::Current()->pipelineContext_->taskExecutor_ = MockContainer::Current()->taskExecutor_;
    auto context = NG::PipelineContext::GetCurrentContext();
    std::unique_ptr<std::ostream> ostream = std::make_unique<std::ostringstream>();
    ASSERT_NE(ostream, nullptr);
    DumpLog::GetInstance().SetDumpFile(std::move(ostream));
}

void AccessibilityFrameNodeUtilsTest::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

/**
 * @tc.name: GetFramenodeByAccessibilityId001
 * @tc.desc: vitural node
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFrameNodeUtilsTest, GetFramenodeByAccessibilityId001, TestSize.Level1)
{
    auto context = NG::PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto root = context->GetRootElement();
    ASSERT_NE(root, nullptr);
    auto frameNode1 = FrameNode::CreateFrameNode("framenode",
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(frameNode1, nullptr);
    root->AddChild(frameNode1);
    auto virtualNode = FrameNode::CreateFrameNode("framenode",
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(virtualNode, nullptr);

    // step 1 can not find virtual node
    auto findNode = AccessibilityFrameNodeUtils::GetFramenodeByAccessibilityId(root, virtualNode->GetAccessibilityId());
    EXPECT_EQ(findNode, nullptr);

    // step 2  add virtual node and find it
    auto accessibilityProperty = frameNode1->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    virtualNode->SetAccessibilityNodeVirtual();
    virtualNode->SetAccessibilityVirtualNodeParent(frameNode1);
    virtualNode->SetFirstAccessibilityVirtualNode();
    frameNode1->HasAccessibilityVirtualNode(true);
    accessibilityProperty->SaveAccessibilityVirtualNode(virtualNode);
    findNode = AccessibilityFrameNodeUtils::GetFramenodeByAccessibilityId(root, virtualNode->GetAccessibilityId());
    ASSERT_NE(findNode, nullptr);
    EXPECT_EQ(findNode->GetAccessibilityId(), virtualNode->GetAccessibilityId());

    // step 3  add virtual node and find with wrong id
    findNode = AccessibilityFrameNodeUtils::GetFramenodeByAccessibilityId(root, virtualNode->GetAccessibilityId() + 1);
    EXPECT_EQ(findNode, nullptr);

    // step4 reset testcase
    root->RemoveChild(frameNode1);
}

/**
 * @tc.name: GetFramenodeByAccessibilityId002
 * @tc.desc: overlay node
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFrameNodeUtilsTest, GetFramenodeByAccessibilityId002, TestSize.Level1)
{
    auto context = NG::PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto root = context->GetRootElement();
    ASSERT_NE(root, nullptr);
    auto frameNode1 = FrameNode::CreateFrameNode("framenode",
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(frameNode1, nullptr);
    root->AddChild(frameNode1);
    auto overlayNode = FrameNode::CreateFrameNode("framenode",
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(overlayNode, nullptr);

    // step 1 can not find overlay node
    auto findNode = AccessibilityFrameNodeUtils::GetFramenodeByAccessibilityId(root, overlayNode->GetAccessibilityId());
    EXPECT_EQ(findNode, nullptr);

    // step 2  add overlay node and find it
    frameNode1->SetOverlayNode(overlayNode);
    findNode = AccessibilityFrameNodeUtils::GetFramenodeByAccessibilityId(root, overlayNode->GetAccessibilityId());
    ASSERT_NE(findNode, nullptr);
    EXPECT_EQ(findNode->GetAccessibilityId(), overlayNode->GetAccessibilityId());

    // step 3  add overlay node and find with wrong id
    frameNode1->SetOverlayNode(overlayNode);
    findNode = AccessibilityFrameNodeUtils::GetFramenodeByAccessibilityId(root, overlayNode->GetAccessibilityId() + 1);
    EXPECT_EQ(findNode, nullptr);
    // step4 reset testcase
    root->RemoveChild(frameNode1);
}

/**
 * @tc.name: UpdateAccessibilityVisibleToRoot001
 * @tc.desc: IsFirstVirtualNode
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFrameNodeUtilsTest, UpdateAccessibilityVisibleToRoot001, TestSize.Level1)
{
    auto context = NG::PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);

    auto frameNode1 = FrameNode::CreateFrameNode("framenode",
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(frameNode1, nullptr);
    auto virtualNode = FrameNode::CreateFrameNode("virtualNode",
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(virtualNode, nullptr);
    auto virtualNode1 = FrameNode::CreateFrameNode("virtualNode",
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(virtualNode1, nullptr);
    virtualNode->AddChild(virtualNode1);

    auto accessibilityProperty = frameNode1->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    virtualNode->SetAccessibilityNodeVirtual();
    virtualNode->SetAccessibilityVirtualNodeParent(frameNode1);
    virtualNode->SetFirstAccessibilityVirtualNode();
    frameNode1->HasAccessibilityVirtualNode(true);
    accessibilityProperty->SaveAccessibilityVirtualNode(virtualNode);
    // step 1 IsFirstVirtualNode GetNodeAccessibilityVisible
    AccessibilityFrameNodeUtils::UpdateAccessibilityVisibleToRoot(virtualNode);
    EXPECT_EQ(virtualNode->GetAccessibilityVisible(), false);
    // step 2 IsFirstVirtualNode GetNodeAccessibilityVisible
    AccessibilityFrameNodeUtils::UpdateAccessibilityVisibleToRoot(virtualNode1);
    EXPECT_EQ(virtualNode1->GetAccessibilityVisible(), false);
}

/**
 * @tc.name: UpdateAccessibilityVisibleToRoot001
 * @tc.desc: PageNode
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFrameNodeUtilsTest, UpdateAccessibilityVisibleToRoot002, TestSize.Level1)
{
    auto context = NG::PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);

    auto frameNode1 = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(frameNode1, nullptr);
    auto frameNode2 = FrameNode::CreateFrameNode("frameNode2",
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(frameNode2, nullptr);
    frameNode1->AddChild(frameNode2);
    auto frameNode3 = FrameNode::CreateFrameNode("frameNode3",
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(frameNode3, nullptr);
    frameNode2->AddChild(frameNode3);

    // step 1 gettag == V2::PAGE_ETS_TAG
    AccessibilityFrameNodeUtils::UpdateAccessibilityVisibleToRoot(frameNode2);
    EXPECT_EQ(frameNode2->GetAccessibilityVisible(), false);
}

/**
 * @tc.name: IsCoveredByBrother_001
 * @tc.desc: Covered by brother
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFrameNodeUtilsTest, IsCoveredByBrother_001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("node",
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(frameNode, nullptr);
    auto backupScreenReadEnabled = AceApplicationInfo::GetInstance().IsAccessibilityScreenReadEnabled();

    AceApplicationInfo::GetInstance().SetAccessibilityScreenReadEnabled(false);
    bool nodeAccessibilityVisible = true;
    AccessibilityFrameNodeUtils::IsCoveredByBrother(frameNode, nodeAccessibilityVisible);
    EXPECT_TRUE(nodeAccessibilityVisible);

    AceApplicationInfo::GetInstance().SetAccessibilityScreenReadEnabled(true);
    nodeAccessibilityVisible = false;
    AccessibilityFrameNodeUtils::IsCoveredByBrother(frameNode, nodeAccessibilityVisible);
    EXPECT_FALSE(nodeAccessibilityVisible);

    auto parentNode = FrameNode::CreateFrameNode("parent",
    ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(parentNode, nullptr);
    auto frameNodeChild1 = FrameNode::CreateFrameNode("child1",
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(frameNodeChild1, nullptr);
    parentNode->AddChild(frameNodeChild1);
    AceApplicationInfo::GetInstance().SetAccessibilityScreenReadEnabled(true);
    nodeAccessibilityVisible = true;
    AccessibilityFrameNodeUtils::IsCoveredByBrother(frameNodeChild1, nodeAccessibilityVisible);
    EXPECT_TRUE(nodeAccessibilityVisible);

    auto frameNodeChild2 = FrameNode::CreateFrameNode("child2",
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(frameNodeChild2, nullptr);
    parentNode->AddChild(frameNodeChild2);
    auto frameNodeChild3 = FrameNode::CreateFrameNode("child3",
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(frameNodeChild3, nullptr);
    parentNode->AddChild(frameNodeChild3);

    auto mockRenderContext1 = AceType::MakeRefPtr<MockRenderContext>();
    auto mockRenderContext2 = AceType::MakeRefPtr<MockRenderContext>();
    auto mockRenderContext3 = AceType::MakeRefPtr<MockRenderContext>();
    frameNodeChild1->renderContext_ = mockRenderContext1;
    frameNodeChild2->renderContext_ = mockRenderContext2;
    frameNodeChild3->renderContext_ = mockRenderContext3;
    RectF rect1(100, 100, 100, 100);
    RectF rect2(100, 200, 100, 100);
    RectF rect3(100, 300, 100, 100);
    mockRenderContext1->UpdatePaintRect(rect1);
    mockRenderContext2->UpdatePaintRect(rect2);
    mockRenderContext3->UpdatePaintRect(rect3);
    mockRenderContext1->SetPaintRectWithTransform(rect1);
    mockRenderContext2->SetPaintRectWithTransform(rect2);
    mockRenderContext3->SetPaintRectWithTransform(rect3);
    auto accProp = AceType::MakeRefPtr<MockAccessibilityProperty>();
    parentNode->accessibilityProperty_ = accProp;
    EXPECT_CALL(*accProp, GetAccessibilityInnerVisibleRect(_)).Times(4)
        .WillOnce([](RectF& rect) -> bool {
            rect = RectF(100, 201, 100, 98);
            return true;
        })
        .WillOnce([](RectF& rect) -> bool {
            rect = RectF(100, 201, 100, 98);
            return true;
        })
        .WillOnce([](RectF& rect) -> bool {
            rect = RectF(100, 201, 100, 98);
            return true;
        })
        .WillOnce([](RectF& rect) -> bool {
            rect = RectF(100, 250, 100, 0);
            return true;
        });

    parentNode->isWindowBoundary_ = true;
    nodeAccessibilityVisible = true;
    AccessibilityFrameNodeUtils::IsCoveredByBrother(frameNodeChild1, nodeAccessibilityVisible);
    EXPECT_TRUE(nodeAccessibilityVisible);

    parentNode->isWindowBoundary_ = false;
    AceApplicationInfo::GetInstance().SetAccessibilityScreenReadEnabled(true);
    nodeAccessibilityVisible = true;
    AccessibilityFrameNodeUtils::IsCoveredByBrother(frameNodeChild1, nodeAccessibilityVisible);
    EXPECT_FALSE(nodeAccessibilityVisible);

    nodeAccessibilityVisible = true;
    AccessibilityFrameNodeUtils::IsCoveredByBrother(frameNodeChild3, nodeAccessibilityVisible);
    EXPECT_FALSE(nodeAccessibilityVisible);

    nodeAccessibilityVisible = true;
    AccessibilityFrameNodeUtils::IsCoveredByBrother(frameNodeChild2, nodeAccessibilityVisible);
    EXPECT_FALSE(nodeAccessibilityVisible);

    AceApplicationInfo::GetInstance().SetAccessibilityScreenReadEnabled(backupScreenReadEnabled);
}

/**
 * @tc.name: IsNodeEnabled001
 * @tc.desc: check node is enabled
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFrameNodeUtilsTest, IsNodeEnabled001, TestSize.Level1)
{
    auto frameNode1 = FrameNode::CreateFrameNode("framenode",
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(frameNode1, nullptr);

    auto eventHub = frameNode1->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);

    auto focusHub = frameNode1->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);

    eventHub->SetEnabled(false);
    // step 1 origin enable false equals false
    auto result = AccessibilityFrameNodeUtils::IsNodeEnabled(frameNode1);
    EXPECT_EQ(result, false);
    // step 2 origin enable true equals true
    eventHub->SetEnabled(true);
    result = AccessibilityFrameNodeUtils::IsNodeEnabled(frameNode1);
    EXPECT_EQ(result, true);
    // step 3 origin enable true， user disable true  equals false
    eventHub->SetEnabled(true);
    auto accessibilityProperty = frameNode1->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    accessibilityProperty->SetUserDisabled(true);
    result = AccessibilityFrameNodeUtils::IsNodeEnabled(frameNode1);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: ProcessFocusScroll001
 * @tc.desc: check ProcessFocusScroll with invalid params
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFrameNodeUtilsTest, ProcessFocusScroll001, TestSize.Level1)
{
    RefPtr<PipelineContext> context = nullptr;
    AccessibilityFrameNodeUtils::ProcessFocusScroll(nullptr, context);
    auto frameNode = FrameNode::CreateFrameNode("framenode",
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(frameNode, nullptr);
    AccessibilityFrameNodeUtils::ProcessFocusScroll(frameNode, context);
}

/**
 * @tc.name: ProcessFocusScroll002
 * @tc.desc: check ProcessFocusScroll branch when focus state is false
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFrameNodeUtilsTest, ProcessFocusScroll002, TestSize.Level1)
{
    auto context = NG::PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto focusNode = FrameNode::CreateFrameNode("focusNode",
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(focusNode, nullptr);
    auto accessibilityProperty = focusNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    accessibilityProperty->SetAccessibilityFocusState(false);
    AccessibilityFrameNodeUtils::ProcessFocusScroll(focusNode, context);
}

/**
 * @tc.name: ProcessFocusScroll003
 * @tc.desc: check ProcessFocusScroll branch with user scroll triggerable false
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFrameNodeUtilsTest, ProcessFocusScroll003, TestSize.Level1)
{
    auto context = NG::PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);

    auto scrollPattern = AceType::MakeRefPtr<MockScrollPatternForA11y>();
    auto parentNode = FrameNode::CreateFrameNode("scrollParentNode",
        ElementRegister::GetInstance()->MakeUniqueId(), scrollPattern, true);
    ASSERT_NE(parentNode, nullptr);
    auto parentAccessibilityProperty = parentNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(parentAccessibilityProperty, nullptr);
    parentAccessibilityProperty->SetUserScrollTriggerable(false);

    auto focusNode = FrameNode::CreateFrameNode("focusNode",
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(focusNode, nullptr);
    parentNode->AddChild(focusNode);
    auto focusAccessibilityProperty = focusNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(focusAccessibilityProperty, nullptr);
    focusAccessibilityProperty->SetAccessibilityFocusState(true);
    AccessibilityFrameNodeUtils::ProcessFocusScroll(focusNode, context);
    EXPECT_FALSE(scrollPattern->onScrollCallbackCalled_);
}

/**
 * @tc.name: ProcessFocusScroll004
 * @tc.desc: check ProcessFocusScroll branch with SCROLL_ETS_TAG
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFrameNodeUtilsTest, ProcessFocusScroll004, TestSize.Level1)
{
    auto context = NG::PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);

    auto scrollPattern = AceType::MakeRefPtr<MockScrollPatternForA11y>();
    auto scrollNode = FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), scrollPattern, true);
    ASSERT_NE(scrollNode, nullptr);

    auto focusNode = FrameNode::CreateFrameNode("focusNode",
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(focusNode, nullptr);
    scrollNode->AddChild(focusNode);

    auto focusAccessibilityProperty = focusNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(focusAccessibilityProperty, nullptr);
    focusAccessibilityProperty->SetAccessibilityFocusState(true);
    AccessibilityFrameNodeUtils::ProcessFocusScroll(focusNode, context);
    EXPECT_FALSE(scrollPattern->onScrollCallbackCalled_);
}

/**
 * @tc.name: ProcessFocusScroll006
 * @tc.desc: check ScrollByOffsetToParent when scrollFunc is null and scrollAxis is NONE
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFrameNodeUtilsTest, ProcessFocusScroll006, TestSize.Level1)
{
    auto context = NG::PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);

    auto scrollablePattern = AceType::MakeRefPtr<MockScrollablePatternNoAbility>();
    auto parentNode = FrameNode::CreateFrameNode("noAbilityParent",
        ElementRegister::GetInstance()->MakeUniqueId(), scrollablePattern, true);
    ASSERT_NE(parentNode, nullptr);

    auto focusNode = FrameNode::CreateFrameNode("focusNode",
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(focusNode, nullptr);
    parentNode->AddChild(focusNode);

    auto focusAccessibilityProperty = focusNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(focusAccessibilityProperty, nullptr);
    focusAccessibilityProperty->SetAccessibilityFocusState(true);

    AccessibilityFrameNodeUtils::ProcessFocusScroll(focusNode, context);
}

/**
 * @tc.name: ProcessFocusScroll007
 * @tc.desc: check ScrollByOffsetToParent when moveOffset is NearZero (child already visible)
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFrameNodeUtilsTest, ProcessFocusScroll007, TestSize.Level1)
{
    auto context = NG::PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);

    auto scrollPattern = AceType::MakeRefPtr<MockScrollPatternForA11y>();
    auto parentNode = FrameNode::CreateFrameNode("scrollParentNode",
        ElementRegister::GetInstance()->MakeUniqueId(), scrollPattern, true);
    ASSERT_NE(parentNode, nullptr);
    parentNode->geometryNode_->SetFrameSize(SizeF(100.0f, 100.0f));
    parentNode->geometryNode_->SetFrameOffset(OffsetF(0.0f, 0.0f));

    auto focusNode = FrameNode::CreateFrameNode("focusNode",
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(focusNode, nullptr);
    focusNode->geometryNode_->SetFrameSize(SizeF(20.0f, 20.0f));
    focusNode->geometryNode_->SetFrameOffset(OffsetF(0.0f, 0.0f));
    parentNode->AddChild(focusNode);

    auto focusAccessibilityProperty = focusNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(focusAccessibilityProperty, nullptr);
    focusAccessibilityProperty->SetAccessibilityFocusState(true);

    AccessibilityFrameNodeUtils::ProcessFocusScroll(focusNode, context);
    EXPECT_FALSE(scrollPattern->onScrollCallbackCalled_);
}

/**
 * @tc.name: ProcessFocusScroll009
 * @tc.desc: check ScrollByOffset with multiple parents, ScrollByOffsetToParent returns false for all
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFrameNodeUtilsTest, ProcessFocusScroll009, TestSize.Level1)
{
    auto context = NG::PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);

    auto grandParentNode = FrameNode::CreateFrameNode("grandParent",
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(grandParentNode, nullptr);

    auto focusNode = FrameNode::CreateFrameNode("focusNode",
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(focusNode, nullptr);
    grandParentNode->AddChild(focusNode);

    auto focusAccessibilityProperty = focusNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(focusAccessibilityProperty, nullptr);
    focusAccessibilityProperty->SetAccessibilityFocusState(true);

    AccessibilityFrameNodeUtils::ProcessFocusScroll(focusNode, context);
}

/**
 * @tc.name: ProcessFocusScroll005
 * @tc.desc: check ScrollByOffsetToParent triggers scroll when child is outside visible area
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFrameNodeUtilsTest, ProcessFocusScroll005, TestSize.Level1)
{
    auto context = NG::PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);

    auto scrollPattern = AceType::MakeRefPtr<MockScrollPatternForA11y>();
    auto parentNode = FrameNode::CreateFrameNode("scrollParentNode",
        ElementRegister::GetInstance()->MakeUniqueId(), scrollPattern, true);
    ASSERT_NE(parentNode, nullptr);
    parentNode->geometryNode_->SetFrameSize(SizeF(PARENT_SIZE_WIDTH, PARENT_SIZE_HEIGHT));
    parentNode->geometryNode_->SetFrameOffset(OffsetF(0.0f, 0.0f));
    auto mockParentRenderContext = AceType::MakeRefPtr<MockRenderContext>();
    parentNode->renderContext_ = mockParentRenderContext;
    mockParentRenderContext->SetPaintRectWithTransform(RectF(0, 0, PARENT_SIZE_WIDTH, PARENT_SIZE_HEIGHT));

    auto focusNode = FrameNode::CreateFrameNode("focusNode",
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(focusNode, nullptr);
    focusNode->geometryNode_->SetFrameSize(SizeF(CHILD_SIZE_WIDTH, CHILD_SIZE_HEIGHT));
    focusNode->geometryNode_->SetFrameOffset(OffsetF(0.0f, CHILD_OFFSET_BELOW_VISIBLE));
    parentNode->AddChild(focusNode);
    auto mockChildRenderContext = AceType::MakeRefPtr<MockRenderContext>();
    focusNode->renderContext_ = mockChildRenderContext;
    mockChildRenderContext->SetPaintRectWithTransform(
        RectF(0, CHILD_OFFSET_BELOW_VISIBLE, CHILD_SIZE_WIDTH, CHILD_SIZE_HEIGHT));

    auto focusAccessibilityProperty = focusNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(focusAccessibilityProperty, nullptr);
    focusAccessibilityProperty->SetAccessibilityFocusState(true);

    AccessibilityFrameNodeUtils::ProcessFocusScroll(focusNode, context);
    EXPECT_TRUE(scrollPattern->onScrollCallbackCalled_);
    EXPECT_NE(scrollPattern->scrollOffset_, 0.0f);
}

/**
 * @tc.name: ProcessFocusScroll008
 * @tc.desc: check ScrollByOffsetToParent with noNeedMargin=true does not scroll when child is at edge
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFrameNodeUtilsTest, ProcessFocusScroll008, TestSize.Level1)
{
    auto context = NG::PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);

    auto scrollPattern = AceType::MakeRefPtr<MockScrollPatternForA11y>();
    auto parentNode = FrameNode::CreateFrameNode("scrollParentNode",
        ElementRegister::GetInstance()->MakeUniqueId(), scrollPattern, true);
    ASSERT_NE(parentNode, nullptr);
    parentNode->geometryNode_->SetFrameSize(SizeF(PARENT_SIZE_WIDTH, PARENT_SIZE_HEIGHT));
    parentNode->geometryNode_->SetFrameOffset(OffsetF(0.0f, 0.0f));
    auto mockParentRenderContext = AceType::MakeRefPtr<MockRenderContext>();
    parentNode->renderContext_ = mockParentRenderContext;
    mockParentRenderContext->SetPaintRectWithTransform(RectF(0, 0, PARENT_SIZE_WIDTH, PARENT_SIZE_HEIGHT));

    // Child positioned near top edge - with noNeedMargin=true, no focus margin is applied,
    // so the child is considered visible and no scroll should be triggered
    auto focusNode = FrameNode::CreateFrameNode("focusNode",
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(focusNode, nullptr);
    focusNode->geometryNode_->SetFrameSize(SizeF(CHILD_SIZE_WIDTH, CHILD_SIZE_HEIGHT));
    focusNode->geometryNode_->SetFrameOffset(OffsetF(0.0f, CHILD_OFFSET_NEAR_TOP));
    parentNode->AddChild(focusNode);
    auto mockChildRenderContext = AceType::MakeRefPtr<MockRenderContext>();
    focusNode->renderContext_ = mockChildRenderContext;
    mockChildRenderContext->SetPaintRectWithTransform(
        RectF(0, CHILD_OFFSET_NEAR_TOP, CHILD_SIZE_WIDTH, CHILD_SIZE_HEIGHT));

    auto focusAccessibilityProperty = focusNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(focusAccessibilityProperty, nullptr);
    focusAccessibilityProperty->SetAccessibilityFocusState(true);

    AccessibilityFrameNodeUtils::ProcessFocusScroll(focusNode, context);
    EXPECT_FALSE(scrollPattern->onScrollCallbackCalled_);
}

/**
 * @tc.name: ProcessFocusScroll010
 * @tc.desc: check ScrollByOffset with nested scrollable parents, scroll succeeds on outer parent
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFrameNodeUtilsTest, ProcessFocusScroll010, TestSize.Level1)
{
    auto context = NG::PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);

    auto outerScrollPattern = AceType::MakeRefPtr<MockScrollPatternForA11y>();
    auto outerNode = FrameNode::CreateFrameNode("outerScroll",
        ElementRegister::GetInstance()->MakeUniqueId(), outerScrollPattern, true);
    ASSERT_NE(outerNode, nullptr);
    outerNode->geometryNode_->SetFrameSize(SizeF(PARENT_SIZE_WIDTH, PARENT_SIZE_HEIGHT));
    outerNode->geometryNode_->SetFrameOffset(OffsetF(0.0f, 0.0f));
    auto mockOuterRenderContext = AceType::MakeRefPtr<MockRenderContext>();
    outerNode->renderContext_ = mockOuterRenderContext;
    mockOuterRenderContext->SetPaintRectWithTransform(RectF(0, 0, PARENT_SIZE_WIDTH, PARENT_SIZE_HEIGHT));

    auto innerNode = FrameNode::CreateFrameNode("innerNode",
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(innerNode, nullptr);
    innerNode->geometryNode_->SetFrameSize(SizeF(INNER_PARENT_SIZE, INNER_PARENT_SIZE));
    innerNode->geometryNode_->SetFrameOffset(OffsetF(0.0f, 0.0f));
    auto mockInnerRenderContext = AceType::MakeRefPtr<MockRenderContext>();
    innerNode->renderContext_ = mockInnerRenderContext;
    mockInnerRenderContext->SetPaintRectWithTransform(RectF(0, 0, INNER_PARENT_SIZE, INNER_PARENT_SIZE));
    outerNode->AddChild(innerNode);

    auto focusNode = FrameNode::CreateFrameNode("focusNode",
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(focusNode, nullptr);
    focusNode->geometryNode_->SetFrameSize(SizeF(CHILD_SIZE_WIDTH, CHILD_SIZE_HEIGHT));
    focusNode->geometryNode_->SetFrameOffset(OffsetF(0.0f, CHILD_OFFSET_BELOW_VISIBLE));
    innerNode->AddChild(focusNode);
    auto mockChildRenderContext = AceType::MakeRefPtr<MockRenderContext>();
    focusNode->renderContext_ = mockChildRenderContext;
    mockChildRenderContext->SetPaintRectWithTransform(
        RectF(0, CHILD_OFFSET_BELOW_VISIBLE, CHILD_SIZE_WIDTH, CHILD_SIZE_HEIGHT));

    auto focusAccessibilityProperty = focusNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(focusAccessibilityProperty, nullptr);
    focusAccessibilityProperty->SetAccessibilityFocusState(true);

    AccessibilityFrameNodeUtils::ProcessFocusScroll(focusNode, context);
    EXPECT_TRUE(outerScrollPattern->onScrollCallbackCalled_);
}

/**
 * @tc.name: ProcessFocusScroll011
 * @tc.desc: check ScrollByOffsetToParent verifies scroll source is SCROLL_FROM_FOCUS_JUMP
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFrameNodeUtilsTest, ProcessFocusScroll011, TestSize.Level1)
{
    auto context = NG::PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);

    auto scrollPattern = AceType::MakeRefPtr<MockScrollPatternForA11y>();
    auto parentNode = FrameNode::CreateFrameNode("scrollParentNode",
        ElementRegister::GetInstance()->MakeUniqueId(), scrollPattern, true);
    ASSERT_NE(parentNode, nullptr);
    parentNode->geometryNode_->SetFrameSize(SizeF(PARENT_SIZE_WIDTH, PARENT_SIZE_HEIGHT));
    parentNode->geometryNode_->SetFrameOffset(OffsetF(0.0f, 0.0f));
    auto mockParentRenderContext = AceType::MakeRefPtr<MockRenderContext>();
    parentNode->renderContext_ = mockParentRenderContext;
    mockParentRenderContext->SetPaintRectWithTransform(RectF(0, 0, PARENT_SIZE_WIDTH, PARENT_SIZE_HEIGHT));

    auto focusNode = FrameNode::CreateFrameNode("focusNode",
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(focusNode, nullptr);
    focusNode->geometryNode_->SetFrameSize(SizeF(CHILD_SIZE_WIDTH, CHILD_SIZE_HEIGHT));
    focusNode->geometryNode_->SetFrameOffset(OffsetF(0.0f, CHILD_OFFSET_BELOW_VISIBLE));
    parentNode->AddChild(focusNode);
    auto mockChildRenderContext = AceType::MakeRefPtr<MockRenderContext>();
    focusNode->renderContext_ = mockChildRenderContext;
    mockChildRenderContext->SetPaintRectWithTransform(
        RectF(0, CHILD_OFFSET_BELOW_VISIBLE, CHILD_SIZE_WIDTH, CHILD_SIZE_HEIGHT));

    auto focusAccessibilityProperty = focusNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(focusAccessibilityProperty, nullptr);
    focusAccessibilityProperty->SetAccessibilityFocusState(true);

    AccessibilityFrameNodeUtils::ProcessFocusScroll(focusNode, context);
    EXPECT_TRUE(scrollPattern->onScrollCallbackCalled_);
    EXPECT_EQ(scrollPattern->scrollSource_, SCROLL_FROM_FOCUS_JUMP);
}

/**
 * @tc.name: ProcessFocusScroll012
 * @tc.desc: check ScrollByOffsetToParent with noNeedMargin=true when child is near bottom edge
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFrameNodeUtilsTest, ProcessFocusScroll012, TestSize.Level1)
{
    auto context = NG::PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);

    auto scrollPattern = AceType::MakeRefPtr<MockScrollPatternForA11y>();
    auto parentNode = FrameNode::CreateFrameNode("scrollParentNode",
        ElementRegister::GetInstance()->MakeUniqueId(), scrollPattern, true);
    ASSERT_NE(parentNode, nullptr);
    parentNode->geometryNode_->SetFrameSize(SizeF(PARENT_SIZE_WIDTH, PARENT_SIZE_HEIGHT));
    parentNode->geometryNode_->SetFrameOffset(OffsetF(0.0f, 0.0f));
    auto mockParentRenderContext = AceType::MakeRefPtr<MockRenderContext>();
    parentNode->renderContext_ = mockParentRenderContext;
    mockParentRenderContext->SetPaintRectWithTransform(RectF(0, 0, PARENT_SIZE_WIDTH, PARENT_SIZE_HEIGHT));

    // Child positioned near bottom edge (offset 85 + height 20 = 105, just beyond parent 100)
    // With noNeedMargin=true, focusMargin=0, child bottom at 105 exceeds parent 100
    auto focusNode = FrameNode::CreateFrameNode("focusNode",
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(focusNode, nullptr);
    focusNode->geometryNode_->SetFrameSize(SizeF(CHILD_SIZE_WIDTH, CHILD_SIZE_HEIGHT));
    focusNode->geometryNode_->SetFrameOffset(OffsetF(0.0f, CHILD_OFFSET_NEAR_BOTTOM));
    parentNode->AddChild(focusNode);
    auto mockChildRenderContext = AceType::MakeRefPtr<MockRenderContext>();
    focusNode->renderContext_ = mockChildRenderContext;
    mockChildRenderContext->SetPaintRectWithTransform(
        RectF(0, CHILD_OFFSET_NEAR_BOTTOM, CHILD_SIZE_WIDTH, CHILD_SIZE_HEIGHT));

    auto focusAccessibilityProperty = focusNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(focusAccessibilityProperty, nullptr);
    focusAccessibilityProperty->SetAccessibilityFocusState(true);

    AccessibilityFrameNodeUtils::ProcessFocusScroll(focusNode, context);
    // Child bottom (85+20=105) exceeds parent height (100), scroll should be triggered
    EXPECT_TRUE(scrollPattern->onScrollCallbackCalled_);
}
} // namespace OHOS::Ace::NG