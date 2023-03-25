/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include <list>

#include "gtest/gtest.h"

#define protected public
#define private public

#include "base/json/json_util.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "core/components_ng/test/mock/render/mock_render_context.h"
#include "core/components_v2/inspector/inspector_constants.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const RefPtr<FrameNode> FRAME_NODE_PARENT =
    FrameNode::CreateFrameNode("parent", 0, AceType::MakeRefPtr<Pattern>(), true);
const RefPtr<FrameNode> FRAME_NODE = FrameNode::CreateFrameNode("one", 1, AceType::MakeRefPtr<Pattern>());
} // namespace
class FrameNodeTestNg : public testing::Test {
public:
    static void SetUpTestCase() {}
    static void TearDownTestCase() {}
};

/**
 * @tc.name: FrameNodeTestNg001
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNg001, TestSize.Level1)
{
    auto one = FrameNode::GetOrCreateFrameNode("one", 1, []() { return AceType::MakeRefPtr<Pattern>(); });
    auto two = FrameNode::GetFrameNode("two", 1);
    EXPECT_NE(one, nullptr);
    EXPECT_EQ(two, nullptr);
}

/**
 * @tc.name: FrameNodeTestNg002
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNg002, TestSize.Level1)
{
    auto one = FrameNode::GetOrCreateFrameNode("one", 1, []() { return AceType::MakeRefPtr<Pattern>(); });
    one->SetParent(FRAME_NODE_PARENT);
    auto two = FrameNode::GetFrameNode("two", 1);
    EXPECT_NE(one, nullptr);
    EXPECT_EQ(two, nullptr);
    ElementRegister::GetInstance()->Clear();
}

/**
 * @tc.name: FrameNodeTestNg003
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNg003, TestSize.Level1)
{
    auto jsonValue = std::make_unique<JsonValue>();
    FRAME_NODE->GetOrCreateFocusHub();
    FRAME_NODE->FocusToJsonValue(jsonValue);
    EXPECT_FALSE(jsonValue->GetBool("enabled", false));
}

/**
 * @tc.name: FrameNodeTestNg004
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNg004, TestSize.Level1)
{
    auto node = FrameNode::CreateFrameNode("main", 10, AceType::MakeRefPtr<Pattern>(), true);
    node->AttachToMainTree();
    node->GetRenderContext()->RequestNextFrame();
    EXPECT_TRUE(node->IsOnMainTree());
}

/**
 * @tc.name: FrameNodeTouchTest001
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTouchTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create framenode and initialize the params used in Test.
     */
    auto node = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    node->AttachToMainTree();
    node->GetOrCreateGestureEventHub();
    auto mockRenderContext = AceType::MakeRefPtr<MockRenderContext>();
    node->renderContext_ = mockRenderContext;
    node->SetActive(true);
    auto localPoint = PointF(10, 10);
    auto parentLocalPoint = PointF(10, 10);
    const NG::PointF point { 10, 10 };
    const PointF parentLocalPointOne = { 10, 10 };
    TouchRestrict touchRestrict = { TouchRestrict::NONE };
    auto globalPoint = PointF(10, 10);
    auto touchTestResult = std::list<RefPtr<TouchEventTarget>>();

    EXPECT_CALL(*mockRenderContext, GetPaintRectWithTransform()).WillRepeatedly(Return(RectF(0, 0, 100, 100)));
    EXPECT_CALL(*mockRenderContext, GetPointWithTransform(_)).WillRepeatedly(DoAll(SetArgReferee<0>(localPoint)));

    /**
     * @tc.steps: step2. create childnode
     */
    auto childNode = FrameNode::CreateFrameNode("main", 2, AceType::MakeRefPtr<Pattern>(), true);
    childNode->SetExclusiveEventForChild(true);
    auto mockRenderContextforChild = AceType::MakeRefPtr<MockRenderContext>();
    childNode->renderContext_ = mockRenderContextforChild;
    EXPECT_CALL(*mockRenderContextforChild, GetPaintRectWithTransform()).WillRepeatedly(Return(RectF(0, 0, 100, 100)));
    EXPECT_CALL(*mockRenderContextforChild, GetPointWithTransform(_))
        .WillRepeatedly(DoAll(SetArgReferee<0>(localPoint)));
    childNode->GetOrCreateGestureEventHub();
    childNode->SetActive(true);
    auto childEventHub = childNode->GetOrCreateGestureEventHub();

    /**
     * @tc.steps: step3. add childnode to the framenode
     */
    std::list<RefPtr<FrameNode>> children;
    children.push_back(childNode);
    node->frameChildren_ = { children.begin(), children.end() };

    /**
     * @tc.steps: step4. create grandChildNode
     */

    auto grandChildNode = FrameNode::CreateFrameNode("main", 3, AceType::MakeRefPtr<Pattern>(), true);
    grandChildNode->SetExclusiveEventForChild(true);
    grandChildNode->renderContext_ = mockRenderContextforChild;
    EXPECT_CALL(*mockRenderContextforChild, GetPaintRectWithTransform()).WillRepeatedly(Return(RectF(0, 0, 100, 100)));
    EXPECT_CALL(*mockRenderContextforChild, GetPointWithTransform(_))
        .WillRepeatedly(DoAll(SetArgReferee<0>(localPoint)));
    grandChildNode->GetOrCreateGestureEventHub();
    grandChildNode->SetActive(true);
    auto grandChildEventHub = grandChildNode->GetOrCreateGestureEventHub();

    /**
     * @tc.steps: step5. add grandChildNode to the childnode
     */
    std::list<RefPtr<FrameNode>> grandChild;
    grandChild.push_back(grandChildNode);
    childNode->frameChildren_ = { grandChild.begin(), grandChild.end() };

    /**
     * @tc.steps: step6. compare hitTestResult which is retured in function TouchTest whith expected value.
     * @tc.expected: step6. hitTestResult  is STOP_BUBBLING when hitTestModeofGrandChilds or hitTestModeofChild is
     * HTMBLOCK;
     */
    HitTestMode hitTestModeofGrandChilds[] = { HitTestMode::HTMBLOCK, HitTestMode::HTMDEFAULT };
    HitTestMode hitTestModeofChilds[] = { HitTestMode::HTMDEFAULT, HitTestMode::HTMBLOCK, HitTestMode::HTMTRANSPARENT,
        HitTestMode::HTMNONE, HitTestMode::HTMTRANSPARENT_SELF };
    bool isStacks[] = { true, false };

    for (auto hitTestModeofGrandChild : hitTestModeofGrandChilds) {
        grandChildEventHub->SetHitTestMode(hitTestModeofGrandChild);
        for (auto isStack : isStacks) {
            for (auto hitTestModeofChild : hitTestModeofChilds) {
                childNode->SetExclusiveEventForChild(isStack);
                childEventHub->SetHitTestMode(hitTestModeofChild);
                auto result = childNode->TouchTest(globalPoint, parentLocalPointOne, touchRestrict, touchTestResult, 0);
                auto expectedResult =
                    (hitTestModeofGrandChild == HitTestMode::HTMBLOCK || hitTestModeofChild == HitTestMode::HTMBLOCK)
                        ? HitTestResult::STOP_BUBBLING
                        : HitTestResult::BUBBLING;
                result = node->TouchTest(globalPoint, parentLocalPointOne, touchRestrict, touchTestResult, 0);
                EXPECT_EQ(result, expectedResult);
            }
        }
    }
}
} // namespace OHOS::Ace::NG