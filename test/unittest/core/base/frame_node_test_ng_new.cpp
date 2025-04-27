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
#include "test/unittest/core/base/frame_node_test_ng.h"

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "frameworks/core/components_ng/pattern/image/image_pattern.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const PanDirection DRAG_DIRECTION = { PanDirection::LEFT };
constexpr int32_t FINGERS_NUMBER = 2;
constexpr float DISTANCE = 10.5f;
constexpr float DEFAULT_OPACITY = 0.95f;
constexpr float PARA_OPACITY_VALUE_1 = 0.1f;
constexpr float PARA_OPACITY_VALUE_2 = 0.2f;
constexpr float PARA_OPACITY_VALUE_3 = 0.3f;
constexpr float PARA_OPACITY_VALUE_4 = 0.4f;
constexpr float PARA_OPACITY_VALUE_5 = 0.5f;
constexpr float PARA_OPACITY_VALUE_6 = 0.6f;
constexpr float PARA_OPACITY_VALUE_7 = 0.7f;
constexpr float PARA_OPACITY_VALUE_8 = 1.0f;
constexpr float MIN_OPACITY { 0.0f };
constexpr float MAX_OPACITY { 1.0f };
} // namespace

/**
 * @tc.name: FrameNodeTestNg_TouchTest041
 * @tc.desc: Test frameNode TouchTest
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTouchTest041, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct TouchTest parameters.
     */
    PointF globalPoint;
    PointF parentLocalPoint;
    TouchRestrict touchRestrict;
    TouchTestResult result;
    ResponseLinkResult responseLinkResult;
    /**
     * @tc.steps: step2. set isActive_ and debugEnabled_ is true and FRAME_NODE2 eventHub is HTMBLOCK.
     * @tc.expected: expect The function return value is STOP_BUBBLING.
     */
    FRAME_NODE2->isActive_ = true;
    FRAME_NODE2->GetOrCreateEventHub<EventHub>()->SetEnabled(true);
    SystemProperties::debugEnabled_ = true;
    auto eventHub = FRAME_NODE2->GetOrCreateGestureEventHub();
    eventHub->SetHitTestMode(HitTestMode::HTMBLOCK);
    auto test = FRAME_NODE2->TouchTest(
        globalPoint, parentLocalPoint, parentLocalPoint, touchRestrict, result, 1, responseLinkResult);
    EXPECT_EQ(test, HitTestResult::OUT_OF_REGION);
}

/**
 * @tc.name: FrameNodeTestNg_TouchTest042
 * @tc.desc: Test frameNode TouchTest
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTouchTest042, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct TouchTest parameters.
     */
    PointF globalPoint;
    PointF parentLocalPoint;
    TouchRestrict touchRestrict;
    TouchTestResult result;
    ResponseLinkResult responseLinkResult;

    /**
     * @tc.steps: step2. set debugEnabled_ is true.
     */
    FRAME_NODE2->isActive_ = true;
    FRAME_NODE2->GetOrCreateEventHub<EventHub>()->SetEnabled(true);
    SystemProperties::debugEnabled_ = true;
    auto test = FRAME_NODE2->TouchTest(
        globalPoint, parentLocalPoint, parentLocalPoint, touchRestrict, result, 1, responseLinkResult);

    /**
     * @tc.steps: step3. create childnode.
     */
    auto childNode = FrameNode::CreateFrameNode("main", 2, AceType::MakeRefPtr<Pattern>(), true);
    childNode->SetExclusiveEventForChild(true);
    auto mockRenderContextforChild = AceType::MakeRefPtr<MockRenderContext>();
    childNode->renderContext_ = mockRenderContextforChild;
    auto localPoint = PointF(10, 10);
    mockRenderContextforChild->rect_ = RectF(0, 0, 100, 100);
    EXPECT_CALL(*mockRenderContextforChild, GetPointWithTransform(_))
        .WillRepeatedly(DoAll(SetArgReferee<0>(localPoint)));
    auto childEventHub = childNode->GetOrCreateGestureEventHub();
    childEventHub->SetHitTestMode(HitTestMode::HTMBLOCK);
    childNode->SetActive(true);

    /**
     * @tc.steps: step4. add childnode to the framenode.
     * @tc.expected: expect The function return value is STOP_BUBBLING.
     */
    std::list<RefPtr<FrameNode>> children;
    children.push_back(childNode);
    FRAME_NODE2->frameChildren_ = { children.begin(), children.end() };
    test = FRAME_NODE2->TouchTest(
        globalPoint, parentLocalPoint, parentLocalPoint, touchRestrict, result, 1, responseLinkResult);
    EXPECT_EQ(test, HitTestResult::OUT_OF_REGION);
}

/**
 * @tc.name: FrameNodeTestNg_TouchTest043
 * @tc.desc: Test frameNode TouchTest
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTouchTest043, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct TouchTest parameters.
     */
    PointF globalPoint;
    PointF parentLocalPoint;
    TouchRestrict touchRestrict;
    TouchTestResult result;
    ResponseLinkResult responseLinkResult;
    /**
     * @tc.steps:    step2. eventHub_->GetGestureEventHub() != nullptr and callback != null.
     * @tc.expected: expect The function return value is STOP_BUBBLING.
     */
    FRAME_NODE2->isActive_ = true;
    FRAME_NODE2->GetOrCreateEventHub<EventHub>()->SetEnabled(true);
    SystemProperties::debugEnabled_ = true;
    auto gestureJudgeFunc = [](const RefPtr<GestureInfo>& gestureInfo, const std::shared_ptr<BaseGestureEvent>& info) {
        return GestureJudgeResult::REJECT;
    };
    auto gestureEventHub = FRAME_NODE2->GetOrCreateEventHub<EventHub>()->GetOrCreateGestureEventHub();
    gestureEventHub->SetOnGestureJudgeBegin(gestureJudgeFunc);
    auto test = FRAME_NODE2->TouchTest(
        globalPoint, parentLocalPoint, parentLocalPoint, touchRestrict, result, 1, responseLinkResult);
    EXPECT_EQ(test, HitTestResult::OUT_OF_REGION);
}

/**
 * @tc.name: FrameNodeTouchTest044
 * @tc.desc: Test method TransferExecuteAction
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTouchTest044, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct parameters.
     */
    FRAME_NODE2->isActive_ = true;
    FRAME_NODE2->GetOrCreateEventHub<EventHub>()->SetEnabled(true);
    SystemProperties::debugEnabled_ = true;
    auto eventHub = FRAME_NODE2->GetOrCreateGestureEventHub();
    eventHub->SetHitTestMode(HitTestMode::HTMBLOCK);
    std::map<std::string, std::string> actionArguments;

    /**
     * @tc.steps: step2. call TransferExecuteAction.
     * @tc.expected: expect result is false.
     */
    bool result = FRAME_NODE2->TransferExecuteAction(1, actionArguments, 1, 1);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: FrameNodeTouchTest045
 * @tc.desc: Test method GetUiExtensionId
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTouchTest045, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct parameters.
     */
    FRAME_NODE2->isActive_ = true;
    FRAME_NODE2->GetOrCreateEventHub<EventHub>()->SetEnabled(true);
    SystemProperties::debugEnabled_ = true;

    /**
     * @tc.steps: step2. call GetUiExtensionId.
     * @tc.expected: expect result is -1.
     */
    int32_t result = FRAME_NODE2->GetUiExtensionId();
    EXPECT_EQ(result, -1);
}

/**
 * @tc.name: FrameNodeTouchTest046
 * @tc.desc: Test method WrapExtensionAbilityId
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTouchTest046, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct parameters.
     */
    FRAME_NODE2->isActive_ = true;
    FRAME_NODE2->GetOrCreateEventHub<EventHub>()->SetEnabled(true);
    SystemProperties::debugEnabled_ = true;

    int32_t extensionOffset = 1;
    int32_t abilityId = 1;

    /**
     * @tc.steps: step2. call WrapExtensionAbilityId.
     * @tc.expected: expect result is -1.
     */
    int32_t result = FRAME_NODE2->WrapExtensionAbilityId(extensionOffset, abilityId);
    EXPECT_EQ(result, -1);
}

/**
 * @tc.name: FrameNodeTouchTest048
 * @tc.desc: Test method DumpViewDataPageNode
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTouchTest048, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct parameters.
     */
    FRAME_NODE2->isActive_ = true;
    FRAME_NODE2->GetOrCreateEventHub<EventHub>()->SetEnabled(true);
    SystemProperties::debugEnabled_ = true;
    auto viewDataWrap = ViewDataWrap::CreateViewDataWrap();

    /**
     * @tc.steps: step2. call DumpViewDataPageNode.
     * @tc.expected: expect renderContext_ not nullptr.
     */

    FRAME_NODE2->DumpViewDataPageNode(viewDataWrap);
    EXPECT_NE(FRAME_NODE2->renderContext_, nullptr);
}

/**
 * @tc.name: FrameNodeTouchTest049
 * @tc.desc: Test method GetResponseRegionList
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTouchTest049, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct parameters.
     */
    FRAME_NODE2->isActive_ = true;
    FRAME_NODE2->GetOrCreateEventHub<EventHub>()->SetEnabled(true);

    DimensionRect responseRect(Dimension(0), Dimension(0), DimensionOffset(OFFSETF));
    std::vector<DimensionRect> mouseResponseRegion;
    mouseResponseRegion.emplace_back(responseRect);

    /**
     * @tc.steps: step2. call GetResponseRegionList.
     * @tc.expected: expect MouseResponseRegion is not empty.
     */
    auto gestureEventHub = FRAME_NODE2->GetOrCreateEventHub<EventHub>()->GetOrCreateGestureEventHub();
    gestureEventHub->SetMouseResponseRegion(mouseResponseRegion);

    auto paintRect = FRAME_NODE2->renderContext_->GetPaintRectWithoutTransform();
    FRAME_NODE2->GetResponseRegionList(paintRect, 1);
    EXPECT_FALSE(gestureEventHub->GetMouseResponseRegion().empty());
}

/**
 * @tc.name: FrameNodeTouchTest050
 * @tc.desc: Test method GetResponseRegionList
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTouchTest050, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct parameters.
     */
    FRAME_NODE2->isActive_ = true;

    /**
     * @tc.steps: step2. call GetResponseRegionList.
     * @tc.expected: expect GetResponseRegion is not empty.
     */
    std::vector<DimensionRect> responseRegion;
    responseRegion.push_back(DimensionRect());
    auto gestureEventHub = FRAME_NODE2->GetOrCreateEventHub<EventHub>()->GetOrCreateGestureEventHub();
    gestureEventHub->SetResponseRegion(responseRegion);
    auto paintRect = FRAME_NODE2->renderContext_->GetPaintRectWithoutTransform();
    FRAME_NODE2->GetResponseRegionList(paintRect, 1);
    EXPECT_FALSE(gestureEventHub->GetResponseRegion().empty());
}

/**
 * @tc.name: FrameNodeTestNg_DumpAdvanceInfo001
 * @tc.desc: Test frame node method DumpAdvanceInfo
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, DumpAdvanceInfo001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. initialize parameters.
     */
    FRAME_NODE3->isActive_ = true;
    FRAME_NODE3->GetOrCreateEventHub<EventHub>()->SetEnabled(true);
    SystemProperties::debugEnabled_ = true;

    auto mockRenderContext = AceType::MakeRefPtr<MockRenderContext>();
    FRAME_NODE3->renderContext_ = mockRenderContext;
    FRAME_NODE3->DumpInfo();

    /**
     * @tc.steps: step2. initialize layoutProperty_ and call DumpAdvanceInfo.
     * @tc.expected: expect DumpAdvanceInfo run ok.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    FRAME_NODE2->layoutProperty_ = layoutProperty;
    FRAME_NODE3->layoutProperty_->geometryTransition_ =
        ElementRegister::GetInstance()->GetOrCreateGeometryTransition("test", false, true);
    FRAME_NODE3->DumpAdvanceInfo();
    EXPECT_NE(FRAME_NODE3->renderContext_, nullptr);
}

/**
 * @tc.name: FrameNodeTestNg_GetOnChildTouchTestRet001
 * @tc.desc: Test frame node method GetOnChildTouchTestRet
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, GetOnChildTouchTestRet001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. initialize parameters.
     */
    std::vector<TouchTestInfo> touchInfos;
    TouchTestInfo info;
    touchInfos.emplace_back(info);

    TouchResult touchResult;
    touchResult.strategy = TouchTestStrategy::DEFAULT;
    touchResult.id = "test1";

    OnChildTouchTestFunc callback = [](const std::vector<TouchTestInfo>& touchInfo) {
        TouchResult res;
        res.strategy = TouchTestStrategy::DEFAULT;
        res.id = "test1";
        return res;
    };

    /**
     * @tc.steps: step2. set parent node and initialize gestureHub.
     */
    const RefPtr<FrameNode> GET_PARENT = FrameNode::CreateFrameNode("parent", 4, AceType::MakeRefPtr<Pattern>());
    auto gestureHub = GET_PARENT->GetOrCreateGestureEventHub();
    gestureHub->SetOnTouchTestFunc(std::move(callback));

    /**
     * @tc.steps: step3. call GetOnChildTouchTestRet.
     * @tc.expected: expect GetOnChildTouchTestRet run ok.
     */
    TouchResult test = GET_PARENT->GetOnChildTouchTestRet(touchInfos);
    EXPECT_EQ(test.id, touchResult.id);
}

/**
 * @tc.name: FrameNodeTestNg_GetOnTouchTestFunc001
 * @tc.desc: Test frame node method GetOnTouchTestFunc
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, GetOnTouchTestFunc001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set parent node and call GetOnTouchTestFunc.
     */
    const RefPtr<FrameNode> GET_PARENT = FrameNode::CreateFrameNode("parent", 4, AceType::MakeRefPtr<Pattern>());
    OnChildTouchTestFunc test = GET_PARENT->GetOnTouchTestFunc();

    /**
     * @tc.expected: expect GetOnTouchTestFunc ruturn nullptr.
     */
    EXPECT_EQ(test, nullptr);

    OnChildTouchTestFunc callback = [](const std::vector<TouchTestInfo>& touchInfo) {
        TouchResult result;
        return result;
    };

    /**
     * @tc.steps: step2. set parent node and initialize gestureHub.
     */
    auto gestureHub = GET_PARENT->GetOrCreateGestureEventHub();
    gestureHub->SetOnTouchTestFunc(std::move(callback));

    /**
     * @tc.steps: step3. call GetOnTouchTestFunc.
     * @tc.expected: expect GetOnTouchTestFunc run ok.
     */
    OnChildTouchTestFunc res = GET_PARENT->GetOnTouchTestFunc();
    EXPECT_NE(res, nullptr);
}

/**
 * @tc.name: FrameNodeTestNg_GetDispatchFrameNode001
 * @tc.desc: Test frame node method GetDispatchFrameNode
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, GetDispatchFrameNode001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. creat node and generate a node tree.
     */
    const RefPtr<FrameNode> GET_PARENT = FrameNode::CreateFrameNode("parent", 4, AceType::MakeRefPtr<Pattern>());
    const RefPtr<FrameNode> GET_CHILD1 = FrameNode::CreateFrameNode("child1", 5, AceType::MakeRefPtr<Pattern>());
    const RefPtr<FrameNode> GET_CHILD2 = FrameNode::CreateFrameNode("child2", 6, AceType::MakeRefPtr<Pattern>());
    GET_CHILD1->UpdateInspectorId("child1");
    GET_CHILD2->UpdateInspectorId("child2");
    GET_PARENT->frameChildren_.insert(GET_CHILD1);
    GET_PARENT->frameChildren_.insert(GET_CHILD2);

    /**
     * @tc.steps: step2. initialize parentEventHub and set HitTestMode.
     */
    auto parentEventHub = GET_PARENT->GetOrCreateGestureEventHub();
    parentEventHub->SetHitTestMode(HitTestMode::HTMBLOCK);
    TouchResult touchResult;

    /**
     * @tc.steps: step3. call GetDispatchFrameNode.
     * @tc.expected: expect GetDispatchFrameNode ruturn nullptr.
     */
    auto test = GET_PARENT->GetDispatchFrameNode(touchResult);
    EXPECT_EQ(test, nullptr);
}

/**
 * @tc.name: FrameNodeTestNg_GetDispatchFrameNode002
 * @tc.desc: Test frame node method GetDispatchFrameNode
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, GetDispatchFrameNode002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. creat node and generate a node tree.
     */
    const RefPtr<FrameNode> GET_PARENT = FrameNode::CreateFrameNode("parent", 4, AceType::MakeRefPtr<Pattern>());
    const RefPtr<FrameNode> GET_CHILD1 = FrameNode::CreateFrameNode("child1", 5, AceType::MakeRefPtr<Pattern>());
    const RefPtr<FrameNode> GET_CHILD2 = FrameNode::CreateFrameNode("child2", 6, AceType::MakeRefPtr<Pattern>());
    GET_CHILD1->UpdateInspectorId("child1");
    GET_CHILD2->UpdateInspectorId("child2");
    GET_PARENT->frameChildren_.insert(GET_CHILD1);
    GET_PARENT->frameChildren_.insert(GET_CHILD2);

    /**
     * @tc.steps: step2. initialize parentEventHub, set HitTestMode and TouchTestStrategy.
     */
    auto parentEventHub = GET_PARENT->GetOrCreateGestureEventHub();
    parentEventHub->SetHitTestMode(HitTestMode::HTMDEFAULT);
    TouchResult touchResult;
    touchResult.strategy = TouchTestStrategy::FORWARD_COMPETITION;
    touchResult.id = "child1";

    /**
     * @tc.steps: step3. call GetDispatchFrameNode.
     * @tc.expected: expect GetDispatchFrameNode run ok.
     */
    auto test = GET_PARENT->GetDispatchFrameNode(touchResult);
    EXPECT_EQ(test, GET_CHILD1);
}

/**
 * @tc.name: FrameNodeTestNg_GetDispatchFrameNode003
 * @tc.desc: Test frame node method GetDispatchFrameNode
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, GetDispatchFrameNode003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. creat node and generate a node tree.
     */
    const RefPtr<FrameNode> GET_PARENT = FrameNode::CreateFrameNode("parent", 4, AceType::MakeRefPtr<Pattern>());
    const RefPtr<FrameNode> GET_CHILD1 = FrameNode::CreateFrameNode("child1", 5, AceType::MakeRefPtr<Pattern>());
    const RefPtr<FrameNode> GET_CHILD2 = FrameNode::CreateFrameNode("child2", 6, AceType::MakeRefPtr<Pattern>());
    GET_CHILD1->UpdateInspectorId("child1");
    GET_CHILD2->UpdateInspectorId("child2");
    GET_PARENT->frameChildren_.insert(GET_CHILD1);
    GET_PARENT->frameChildren_.insert(GET_CHILD2);

    /**
     * @tc.steps: step2. initialize parentEventHub, set HitTestMode and TouchTestStrategy.
     */
    auto parentEventHub = GET_PARENT->GetOrCreateGestureEventHub();
    parentEventHub->SetHitTestMode(HitTestMode::HTMDEFAULT);
    TouchResult touchResult;
    touchResult.strategy = TouchTestStrategy::DEFAULT;

    /**
     * @tc.steps: step3. call GetDispatchFrameNode.
     * @tc.expected: expect GetDispatchFrameNode ruturn nullptr.
     */
    auto test = GET_PARENT->GetDispatchFrameNode(touchResult);
    EXPECT_EQ(test, nullptr);
}

/**
 * @tc.name: FrameNodeTestNg_CollectTouchInfos001
 * @tc.desc: Test frame node method CollectTouchInfos
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, CollectTouchInfos001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. initialize parameters.
     */
    PointF globalPoint;
    PointF parentRevertPoint;
    std::vector<TouchTestInfo> touchInfos;

    /**
     * @tc.steps: step2. creat node and generate a node tree.
     */
    const RefPtr<FrameNode> GET_PARENT = FrameNode::CreateFrameNode("parent", 4, AceType::MakeRefPtr<Pattern>());
    const RefPtr<FrameNode> GET_CHILD1 = FrameNode::CreateFrameNode("child1", 5, AceType::MakeRefPtr<Pattern>());
    const RefPtr<FrameNode> GET_CHILD2 = FrameNode::CreateFrameNode("child2", 6, AceType::MakeRefPtr<Pattern>());
    GET_CHILD1->UpdateInspectorId("child1");
    GET_CHILD2->UpdateInspectorId("child2");
    GET_PARENT->frameChildren_.insert(GET_CHILD1);
    GET_PARENT->frameChildren_.insert(GET_CHILD2);

    OnChildTouchTestFunc callback = [](const std::vector<TouchTestInfo>& touchInfo) {
        TouchResult result;
        return result;
    };

    /**
     * @tc.steps: step3. initialize gestureHub and set HitTestMode.
     */
    auto gestureHub = GET_PARENT->GetOrCreateGestureEventHub();
    gestureHub->SetHitTestMode(HitTestMode::HTMDEFAULT);
    gestureHub->SetOnTouchTestFunc(std::move(callback));

    /**
     * @tc.steps: step4. call CollectTouchInfos.
     * @tc.expected: expect CollectTouchInfos run ok.
     */
    GET_PARENT->CollectTouchInfos(globalPoint, parentRevertPoint, touchInfos);
    EXPECT_EQ(touchInfos.size(), 2);
}

/**
 * @tc.name: FrameNodeTestNg_CollectTouchInfos002
 * @tc.desc: Test frame node method CollectTouchInfos
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, CollectTouchInfos002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. initialize parameters.
     */
    PointF globalPoint;
    PointF parentRevertPoint;
    std::vector<TouchTestInfo> touchInfos;

    /**
     * @tc.steps: step2. creat node and generate a node tree.
     */
    const RefPtr<FrameNode> GET_PARENT = FrameNode::CreateFrameNode("parent", 4, AceType::MakeRefPtr<Pattern>());
    const RefPtr<FrameNode> GET_CHILD1 = FrameNode::CreateFrameNode("child1", 5, AceType::MakeRefPtr<Pattern>());
    const RefPtr<FrameNode> GET_CHILD2 = FrameNode::CreateFrameNode("child2", 6, AceType::MakeRefPtr<Pattern>());
    GET_CHILD1->UpdateInspectorId("child1");
    GET_CHILD2->UpdateInspectorId("child2");
    GET_PARENT->frameChildren_.insert(GET_CHILD1);
    GET_PARENT->frameChildren_.insert(GET_CHILD2);

    /**
     * @tc.steps: step3. initialize gestureHub and set HitTestMode.
     */
    auto gestureHub = GET_PARENT->GetOrCreateGestureEventHub();
    gestureHub->SetHitTestMode(HitTestMode::HTMBLOCK);

    /**
     * @tc.steps: step4. call CollectTouchInfos.
     * @tc.expected: expect CollectTouchInfos return touchInfos.size is 0.
     */
    GET_PARENT->CollectTouchInfos(globalPoint, parentRevertPoint, touchInfos);
    EXPECT_EQ(touchInfos.size(), 0);
}

/**
 * @tc.name: FrameNodeTestNg_CollectTouchInfos003
 * @tc.desc: Test frame node method CollectTouchInfos
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, CollectTouchInfos003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. initialize parameters.
     */
    PointF globalPoint;
    PointF parentRevertPoint;
    std::vector<TouchTestInfo> touchInfos;

    /**
     * @tc.steps: step2. creat node and generate a node tree.
     */
    const RefPtr<FrameNode> GET_PARENT = FrameNode::CreateFrameNode("parent", 4, AceType::MakeRefPtr<Pattern>());
    const RefPtr<FrameNode> GET_CHILD1 = FrameNode::CreateFrameNode("child1", 5, AceType::MakeRefPtr<Pattern>());
    const RefPtr<FrameNode> GET_CHILD2 = FrameNode::CreateFrameNode("child2", 6, AceType::MakeRefPtr<Pattern>());
    GET_CHILD1->UpdateInspectorId("child1");
    GET_CHILD2->UpdateInspectorId("child2");
    GET_PARENT->frameChildren_.insert(GET_CHILD1);
    GET_PARENT->frameChildren_.insert(GET_CHILD2);

    /**
     * @tc.steps: step3. initialize gestureHub and set HitTestMode.
     */
    auto gestureHub = GET_PARENT->GetOrCreateGestureEventHub();
    gestureHub->SetHitTestMode(HitTestMode::HTMDEFAULT);

    /**
     * @tc.steps: step4. call CollectTouchInfos.
     * @tc.expected: expect CollectTouchInfos return touchInfos.size is 0.
     */
    GET_PARENT->CollectTouchInfos(globalPoint, parentRevertPoint, touchInfos);
    EXPECT_EQ(touchInfos.size(), 0);
}

/**
 * @tc.name: FrameNodeTestNg_GetPreviewScaleVal001
 * @tc.desc: Test frame node method GetPreviewScaleVal
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, GetPreviewScaleVal001, TestSize.Level1)
{
    auto frameNode = FRAME_NODE;
    /**
     * @tc.steps: step1. initialize parameters.
     */
    frameNode->isActive_ = true;
    frameNode->GetOrCreateEventHub<EventHub>()->SetEnabled(true);
    SystemProperties::debugEnabled_ = true;

    /**
     * @tc.steps: step2. call GetPreviewScaleVal
     * @tc.expected: expect GetPreviewScaleVal return scale value.
     */
    auto geometryNode = frameNode->GetGeometryNode();
    geometryNode->SetFrameSize(CONTAINER_SIZE_ZERO);
    EXPECT_FLOAT_EQ(frameNode->GetPreviewScaleVal(), 1.0f);

    double screenWidth = 1216.0;
    ScreenSystemManager::GetInstance().SetWindowInfo(screenWidth, 1.0, 1.0);
    geometryNode->SetFrameSize(CONTAINER_SIZE_SMALL);
    EXPECT_FLOAT_EQ(frameNode->GetPreviewScaleVal(), 1.0f);

    /**
     * @tc.steps: step3. set a large size and call GetPreviewScaleVal.
     * @tc.expected: expect GetPreviewScaleVal return scale value.
     */
    geometryNode->SetFrameSize(CONTAINER_SIZE_HUGE);
    EXPECT_LT(frameNode->GetPreviewScaleVal(), 1.0f);
}

/**
 * @tc.name: FrameNodeTestNg_GetPreviewScaleVal002
 * @tc.desc: Test frame node method GetPreviewScaleVal
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, GetPreviewScaleVal002, TestSize.Level1)
{
    auto frameNode = FRAME_NODE;
    /**
     * @tc.steps: step1. initialize parameters.
     */
    frameNode->isActive_ = true;
    frameNode->GetOrCreateEventHub<EventHub>()->SetEnabled(true);
    SystemProperties::debugEnabled_ = true;

    /**
     * @tc.steps: step2. set frame size to huge and drag preview options to disable scale then call GetPreviewScaleVal
     * @tc.expected: expect GetPreviewScaleVal return scale value.
     */
    auto geometryNode = frameNode->GetGeometryNode();
    geometryNode->SetFrameSize(CONTAINER_SIZE_HUGE);
    NG::DragPreviewOption option { false };
    frameNode->SetDragPreviewOptions(option);
    EXPECT_FLOAT_EQ(frameNode->GetPreviewScaleVal(), 1.0f);

    /**
     * @tc.steps: step3. set set drag preview options to auto and call GetPreviewScaleVal.
     * @tc.expected: expect GetPreviewScaleVal return scale value.
     */
    option = { true };
    frameNode->SetDragPreviewOptions(option);
    EXPECT_LT(frameNode->GetPreviewScaleVal(), 1.0f);
}

/**
 * @tc.name: FrameNodeTestNg_GetPreviewApplyVal001
 * @tc.desc: Test frame node method GetPreviewApplyVal001
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, GetPreviewApplyVal001, TestSize.Level1)
{
    auto frameNode = FRAME_NODE;
    /**
     * @tc.steps: step1. initialize parameters.
     */
    frameNode->isActive_ = true;
    frameNode->GetOrCreateEventHub<EventHub>()->SetEnabled(true);
    SystemProperties::debugEnabled_ = true;

    /**
     * @tc.steps: step2. set drag preview options and call GetDragPreviewOption.
     * @tc.expected: expect GetDragPreviewOption return apply .
     */
    auto geometryNode = frameNode->GetGeometryNode();
    geometryNode->SetFrameSize(CONTAINER_SIZE_HUGE);
    NG::DragPreviewOption previewOption;
    previewOption.onApply = [](WeakPtr<NG::FrameNode> frameNode) {};
    frameNode->SetDragPreviewOptions(previewOption);
    EXPECT_NE(frameNode->GetDragPreviewOption().onApply, nullptr);
}

/**
 * @tc.name: FrameNodeTestNg_GetPreviewScaleVal003
 * @tc.desc: Test frame node method GetPreviewScaleVal
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, GetPreviewScaleVal003, TestSize.Level1)
{
    auto frameNode = FRAME_NODE_WEB_ETS_TAG;
    /**
     * @tc.steps: step1. initialize parameters.
     */
    frameNode->isActive_ = true;
    frameNode->GetOrCreateEventHub<EventHub>()->SetEnabled(true);
    SystemProperties::debugEnabled_ = true;

    /**
     * @tc.steps: step2. call GetPreviewScaleVal
     * @tc.expected: expect GetPreviewScaleVal return scale value.
     */
    auto geometryNode = frameNode->GetGeometryNode();
    geometryNode->SetFrameSize(CONTAINER_SIZE_HUGE);

    EXPECT_FLOAT_EQ(frameNode->GetPreviewScaleVal(), 1.0f);
}

/**
 * @tc.name: FrameNodeTestNg_IsPreviewNeedScale001
 * @tc.desc: Test frame node method IsPreviewNeedScale
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, IsPreviewNeedScale001, TestSize.Level1)
{
    auto frameNode = FRAME_NODE;
    /**
     * @tc.steps: step1. initialize parameters.
     */
    FRAME_NODE->isActive_ = true;
    FRAME_NODE->GetOrCreateEventHub<EventHub>()->SetEnabled(true);
    SystemProperties::debugEnabled_ = true;

    /**
     * @tc.steps: step2. call IsPreviewNeedScale
     * @tc.expected: expect IsPreviewNeedScale return false.
     */
    auto geometryNode = frameNode->GetGeometryNode();
    geometryNode->SetFrameSize(CONTAINER_SIZE_SMALL);
    EXPECT_FALSE(FRAME_NODE->IsPreviewNeedScale());

    /**
     * @tc.steps: step2. set a large size and call IsPreviewNeedScale.
     * @tc.expected: expect IsPreviewNeedScale return true.
     */
    geometryNode->SetFrameSize(CONTAINER_SIZE_HUGE);
    EXPECT_TRUE(FRAME_NODE->IsPreviewNeedScale());
}

/**
 * @tc.name: FrameNodeTestNg_GetOffsetInScreen001
 * @tc.desc: Test frame node method GetOffsetInScreen
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, GetOffsetInScreen001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. initialize parameters.
     */
    FRAME_NODE->isActive_ = true;
    FRAME_NODE->GetOrCreateEventHub<EventHub>()->SetEnabled(true);
    SystemProperties::debugEnabled_ = true;
    auto mockRenderContext = AceType::MakeRefPtr<MockRenderContext>();
    ASSERT_NE(mockRenderContext, nullptr);
    mockRenderContext->rect_ = RectF(DEFAULT_X, DEFAULT_Y, DEFAULT_X, DEFAULT_Y);
    FRAME_NODE->renderContext_ = mockRenderContext;

    /**
     * @tc.steps: step2. call GetOffsetInScreen.
     * @tc.expected: expect GetOffsetInScreen return the result which is not (0, 0).
     */
    EXPECT_EQ(FRAME_NODE->GetOffsetInScreen(), OffsetF(0.0f, 0.0f));
}

/**
 * @tc.name: FrameNodeTestNg_GetPixelMap001
 * @tc.desc: Test frame node method GetPixelMap
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, GetPixelMap001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. initialize parameters.
     */
    FRAME_NODE->isActive_ = true;
    FRAME_NODE->GetOrCreateEventHub<EventHub>()->SetEnabled(true);
    SystemProperties::debugEnabled_ = true;
    auto gestureHub = FRAME_NODE->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);
    auto mockRenderContext = AceType::MakeRefPtr<MockRenderContext>();
    ASSERT_NE(mockRenderContext, nullptr);
    FRAME_NODE->renderContext_ = mockRenderContext;

    /**
     * @tc.steps: step2. Don't initialize pixelMap and rosenNode.
     * @tc.expected: expect GetPixelMap() == nullptr.
     */
    EXPECT_EQ(FRAME_NODE->GetDragPixelMap(), nullptr);

    /**
     * @tc.steps: step3. set a pixelMap of gestureHub, and call GetPixelMap.
     * @tc.expected: expect GetPixelMap() != nullptr.
     */
    void* voidPtr = static_cast<void*>(new char[0]);
    RefPtr<PixelMap> pixelMap = PixelMap::CreatePixelMap(voidPtr);
    ASSERT_NE(pixelMap, nullptr);
    gestureHub->SetPixelMap(pixelMap);
    EXPECT_NE(FRAME_NODE->GetDragPixelMap(), nullptr);

    /**
     * @tc.steps: step4. set a pixelMap of the renderContext, and call GetPixelMap.
     * @tc.expected: expect GetPixelMap() != nullptr.
     */
    gestureHub->SetPixelMap(nullptr);
    EXPECT_EQ(FRAME_NODE->GetDragPixelMap(), nullptr);
}

/**
 * @tc.name: FindChildByNameTest001
 * @tc.desc: Test FindChildByName with one tree
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FindChildByNameTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and set the parent and children.
     */
    const std::string parentNodeName = "nodeParent";
    const std::string thisNodeName = "nodeThis";
    const std::string childrenNodeName = "nodeChildren";
    const std::string testChildNodeName = "test";
    auto nodeParent = FrameNode::CreateFrameNode(parentNodeName, 10, AceType::MakeRefPtr<Pattern>(), true);
    auto nodeThis = FrameNode::CreateFrameNode(thisNodeName, 20, AceType::MakeRefPtr<Pattern>());
    auto nodeChildren = FrameNode::CreateFrameNode(childrenNodeName, 30, AceType::MakeRefPtr<Pattern>());

    /**
     * @tc.steps: step1. Set the node's relation.
     */
    nodeParent->AddChild(nodeThis);
    nodeParent->AddChild(nodeChildren);

    /**
     * @tc.steps: step3. Init inspectorId.
     */
    nodeParent->UpdateInspectorId(parentNodeName);
    nodeChildren->UpdateInspectorId(childrenNodeName);
    nodeThis->UpdateInspectorId(thisNodeName);

    /**
     * @tc.steps: step4. Traversal the frameNodeTree.
     */
    auto finalResult = FrameNode::FindChildByName(nodeParent, childrenNodeName);
    EXPECT_EQ(finalResult, nodeChildren);

    auto noChildResult = FrameNode::FindChildByName(nodeParent, testChildNodeName);
    EXPECT_EQ(noChildResult, nullptr);

    nodeParent->Clean();
    auto noHaveResult = FrameNode::FindChildByName(nodeParent, childrenNodeName);
    EXPECT_EQ(noHaveResult, nullptr);
}

/**
 * @tc.name: FindChildByNameTest002
 * @tc.desc: Test FindChildByName with two tree
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FindChildByNameTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and set the parent and children.
     */
    const std::string parentNodeName = "nodeParent";
    const std::string nodeOneName = "nodeOne";
    const std::string nodeOneChildName = "nodeOneChildren";
    const std::string nodeTwoName = "nodeTwo";
    const std::string nodeTwoChildName = "nodeTwoChildren";
    const std::string testChildNodeName = "test";
    auto nodeParent = FrameNode::CreateFrameNode(parentNodeName, 10, AceType::MakeRefPtr<Pattern>(), true);
    auto nodeOne = FrameNode::CreateFrameNode(nodeOneName, 20, AceType::MakeRefPtr<Pattern>());
    auto nodeOneChildren = FrameNode::CreateFrameNode(nodeOneChildName, 30, AceType::MakeRefPtr<Pattern>());
    auto nodeTwo = FrameNode::CreateFrameNode(nodeTwoName, 40, AceType::MakeRefPtr<Pattern>());
    auto nodeTwoChildren = FrameNode::CreateFrameNode(nodeTwoChildName, 50, AceType::MakeRefPtr<Pattern>());

    /**
     * @tc.steps: step1. Set the node's relation.
     */
    nodeParent->AddChild(nodeOne);
    nodeParent->AddChild(nodeTwo);
    nodeOne->AddChild(nodeOneChildren);
    nodeTwo->AddChild(nodeTwoChildren);

    /**
     * @tc.steps: step3. Init inspectorId.
     */
    nodeParent->UpdateInspectorId(parentNodeName);
    nodeOne->UpdateInspectorId(nodeOneName);
    nodeOneChildren->UpdateInspectorId(nodeOneChildName);
    nodeTwo->UpdateInspectorId(nodeTwoName);
    nodeTwoChildren->UpdateInspectorId(nodeTwoChildName);

    /**
     * @tc.steps: step4. Traversal the frameNodeTree.
     */
    auto finalResult = FrameNode::FindChildByName(nodeParent, nodeOneChildName);
    EXPECT_EQ(finalResult, nodeOneChildren);

    auto noChildResult = FrameNode::FindChildByName(nodeParent, testChildNodeName);
    EXPECT_EQ(noChildResult, nullptr);

    nodeParent->Clean();
    auto noHaveResult = FrameNode::FindChildByName(nodeParent, nodeTwoChildName);
    EXPECT_EQ(noHaveResult, nullptr);
}

/**
 * @tc.name: SetOnSizeChangeCallback001
 * @tc.desc: Test SetOnSizeChangeCallback
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, SetOnSizeChangeCallback001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build a object to SetOnSizeChangeCallback
     * @tc.expected: expect cover branch lastFrameNodeRect_ non null and function is run ok.
     */
    OnSizeChangedFunc callback = [](const RectF& oldRect, const RectF& rect) {};
    FRAME_NODE2->SetOnSizeChangeCallback(std::move(callback));
    EXPECT_NE(FRAME_NODE2->lastFrameNodeRect_, nullptr);
    auto eventHub = FRAME_NODE2->GetOrCreateEventHub<NG::EventHub>();
    EXPECT_NE(eventHub, nullptr);
    EXPECT_TRUE(eventHub->HasOnSizeChanged());

    /**
     * @tc.steps: step2.test while callback is nullptr
     * @tc.expected:expect cover branch lastFrameNodeRect_ non null and function is run ok.
     */
    FRAME_NODE2->lastFrameNodeRect_ = std::make_unique<RectF>();
    FRAME_NODE2->SetOnSizeChangeCallback(nullptr);
    EXPECT_NE(FRAME_NODE2->lastFrameNodeRect_, nullptr);
    EXPECT_NE(eventHub, nullptr);
    EXPECT_FALSE(eventHub->HasOnSizeChanged());
}

/**
 * @tc.name: TriggerOnSizeChangeCallback001
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, TriggerOnSizeChangeCallback001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set a flag and init a callback(onSizeChanged)
     */
    bool flag = false;
    OnSizeChangedFunc onSizeChanged = [&flag](const RectF& oldRect, const RectF& rect) { flag = !flag; };

    /**
     * @tc.steps: step2. call TriggerOnSizeChangeCallback before set callback
     * @tc.expected: expect flag is still false
     */
    FRAME_NODE2->TriggerOnSizeChangeCallback();
    EXPECT_FALSE(flag);

    /**
     * @tc.steps: step3.set callback and release lastFrameNodeRect_
     * @tc.expected: expect flag is still false
     */
    FRAME_NODE2->GetOrCreateEventHub<EventHub>()->SetOnSizeChanged(std::move(onSizeChanged));
    FRAME_NODE2->lastFrameNodeRect_ = nullptr;
    FRAME_NODE2->TriggerOnSizeChangeCallback();
    EXPECT_FALSE(flag);

    /**
     * @tc.steps: step4.set lastFrameNodeRect_
     * @tc.expected: expect flag is still false
     */
    FRAME_NODE2->lastFrameNodeRect_ = std::make_unique<RectF>();
    FRAME_NODE2->TriggerOnSizeChangeCallback();
    EXPECT_FALSE(flag);
}

/**
 * @tc.name: OnTouchInterceptTest001
 * @tc.desc: Test onTouchIntercept method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, OnTouchInterceptTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct TouchTest parameters.
     */
    PointF globalPoint;
    PointF parentLocalPoint;
    TouchRestrict touchRestrict;
    TouchTestResult result;
    ResponseLinkResult responseLinkResult;

    /**
     * @tc.steps: step2. create node and set callback.
     */
    auto childNode = FrameNode::CreateFrameNode("main", 2, AceType::MakeRefPtr<Pattern>(), true);
    childNode->SetExclusiveEventForChild(true);
    auto mockRenderContextforChild = AceType::MakeRefPtr<MockRenderContext>();
    childNode->renderContext_ = mockRenderContextforChild;
    auto localPoint = PointF(10, 10);
    mockRenderContextforChild->rect_ = RectF(0, 0, 100, 100);
    EXPECT_CALL(*mockRenderContextforChild, GetPointWithTransform(_))
        .WillRepeatedly(DoAll(SetArgReferee<0>(localPoint)));
    auto childEventHub = childNode->GetOrCreateGestureEventHub();
    childEventHub->SetHitTestMode(HitTestMode::HTMBLOCK);
    childNode->SetActive(true);
    EXPECT_NE(childNode->GetOrCreateEventHub<EventHub>()->GetGestureEventHub(), nullptr);
    auto callback = [](TouchEventInfo& event) -> HitTestMode { return HitTestMode::HTMNONE; };
    childEventHub->SetOnTouchIntercept(callback);

    /**
     * @tc.steps: step3. trigger touch test.
     * @tc.expected: expect the touch test mode is correct.
     */
    HitTestMode hitTestModeofChilds[] = { HitTestMode::HTMDEFAULT, HitTestMode::HTMBLOCK, HitTestMode::HTMTRANSPARENT,
        HitTestMode::HTMNONE, HitTestMode::HTMTRANSPARENT_SELF };
    int32_t i = 0;
    for (auto hitTestModeofChild : hitTestModeofChilds) {
        childEventHub->SetHitTestMode(hitTestModeofChild);
        childNode->TouchTest(
            globalPoint, parentLocalPoint, parentLocalPoint, touchRestrict, result, 1, responseLinkResult);
        auto mode = childEventHub->GetHitTestMode();
        EXPECT_EQ(mode, hitTestModeofChilds[i++]);
    }

    /**
     * @tc.steps: step4. modify callback and trigger touch test.
     * @tc.expected: expect the touch test mode is correct.
     */
    i = 0;
    auto blockCallback = [](TouchEventInfo& event) -> HitTestMode { return HitTestMode::HTMBLOCK; };
    childEventHub->SetOnTouchIntercept(blockCallback);
    for (auto hitTestModeofChild : hitTestModeofChilds) {
        childEventHub->SetHitTestMode(hitTestModeofChild);
        childNode->TouchTest(
            globalPoint, parentLocalPoint, parentLocalPoint, touchRestrict, result, 1, responseLinkResult);
        auto mode = childEventHub->GetHitTestMode();
        EXPECT_EQ(mode, hitTestModeofChilds[i++]);
    }
}

/**
 * @tc.name: FrameNodeTestNg0040
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNg0040, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    std::set<std::string> allowDropSet;
    frameNode->SetAllowDrop(allowDropSet);
    std::set<std::string> allowDrop = frameNode->GetAllowDrop();
    EXPECT_TRUE(allowDrop.empty());
}

/**
 * @tc.name: FrameNodeTestNg0050
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNg0050, TestSize.Level1)
{
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto node = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(node, nullptr);
    node->GetOrCreateGestureEventHub();
    node->AttachContext(AceType::RawPtr(context));
    auto mockRenderContext = AceType::MakeRefPtr<MockRenderContext>();
    node->renderContext_ = mockRenderContext;
    EXPECT_EQ(node->context_, AceType::RawPtr(context));

    node->DetachContext(true);
    EXPECT_EQ(node->context_, nullptr);
}

/**
 * @tc.name: FrameNodeTestNg_GetPositionToScreen001
 * @tc.desc: Test frame node method GetPositionToScreen
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, GetPositionToScreen001, TestSize.Level1)
{
    OffsetF Offset = { 0, 0 };
    FRAME_NODE2->SetParent(FRAME_NODE3);
    auto screenOffset = FRAME_NODE2->GetPositionToScreen();
    EXPECT_EQ(screenOffset, Offset);
}

/**
 * @tc.name: FrameNodeTestNg_GetPositionToParentWithTransform001
 * @tc.desc: Test frame node method GetPositionToParentWithTransform
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, GetPositionToParentWithTransform001, TestSize.Level1)
{
    OffsetF Offset = { 0, 0 };
    FRAME_NODE2->SetParent(FRAME_NODE3);
    auto parentOffsetWithTransform = FRAME_NODE2->GetPositionToParentWithTransform();
    EXPECT_EQ(parentOffsetWithTransform, Offset);
}

/**
 * @tc.name: FrameNodeTestNg_GetPositionToParentWithTransform001
 * @tc.desc: Test frame node method GetPositionToParentWithTransform
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, GetPositionToScreenWithTransform001, TestSize.Level1)
{
    OffsetF Offset = { 0, 0 };
    FRAME_NODE2->SetParent(FRAME_NODE3);
    auto screenOffsetWithTransform = FRAME_NODE2->GetPositionToScreenWithTransform();
    EXPECT_EQ(screenOffsetWithTransform, Offset);
}

/**
 * @tc.name: FrameNodeTestNg_GetPositionToWindowWithTransform001
 * @tc.desc: Test frame node method GetPositionToWindowWithTransform
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, GetPositionToWindowWithTransform001, TestSize.Level1)
{
    OffsetF Offset = { 0, 0 };
    FRAME_NODE2->SetParent(FRAME_NODE3);
    auto windowOffsetWithTransform = FRAME_NODE2->GetPositionToWindowWithTransform();
    EXPECT_EQ(windowOffsetWithTransform, Offset);
}

/**
 * @tc.name: GetPreviewOptionFromModifier001
 * @tc.desc: Test UpdatePreviewOptionFromModifier
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(FrameNodeTestNg, GetPreviewOptionFromModifier001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FrameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    EXPECT_NE(frameNode, nullptr);
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    auto dragEventActuator = AceType::MakeRefPtr<DragEventActuator>(
        AceType::WeakClaim(AceType::RawPtr(gestureEventHub)), DRAG_DIRECTION, FINGERS_NUMBER, DISTANCE);
    /**
     * @tc.steps: step2. get DragPreviewOption.
     */
    auto dragPreviewOption = frameNode->GetDragPreviewOption();
    /**
     * @tc.steps: step3. set opacity.
     */
    dragPreviewOption.options.opacity = -50.0f;
    frameNode->SetDragPreviewOptions(dragPreviewOption);
    /**
     * @tc.steps: step4. call UpdatePreviewOptionFromModifier
     * @tc.expected: opacity in DragPreviewOption is equal to 0.95f.
     */
    dragEventActuator->UpdatePreviewOptionFromModifier(frameNode);
    dragPreviewOption = frameNode->GetDragPreviewOption();
    EXPECT_EQ(dragPreviewOption.options.opacity, 0.95f);
}

/**
 * @tc.name: GetPreviewOptionFromModifier002
 * @tc.desc: Test UpdatePreviewOptionFromModifier
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(FrameNodeTestNg, GetPreviewOptionFromModifier002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FrameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    EXPECT_NE(frameNode, nullptr);
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    auto dragEventActuator = AceType::MakeRefPtr<DragEventActuator>(
        AceType::WeakClaim(AceType::RawPtr(gestureEventHub)), DRAG_DIRECTION, FINGERS_NUMBER, DISTANCE);
    /**
     * @tc.steps: step2. get DragPreviewOption.
     */
    NG::DragPreviewOption previewOption;
    previewOption.onApply = [](WeakPtr<NG::FrameNode> frameNode) {
        auto node = frameNode.Upgrade();
        CHECK_NULL_VOID(node);
        if ((PARA_OPACITY_VALUE_1 <= MAX_OPACITY) && (PARA_OPACITY_VALUE_1 > MIN_OPACITY)) {
            node->GetRenderContext()->UpdateOpacity(PARA_OPACITY_VALUE_1);
        } else {
            node->GetRenderContext()->UpdateOpacity(DEFAULT_OPACITY);
        }
    };
    /**
     * @tc.steps: step3. set opacity.
     */
    frameNode->SetDragPreviewOptions(previewOption);
    /**
     * @tc.steps: step4. call UpdatePreviewOptionFromModifier
     * @tc.expected: opacity in DragPreviewOption is equal to 0.1f.
     */
    dragEventActuator->UpdatePreviewOptionFromModifier(frameNode);
    EXPECT_EQ(frameNode->GetDragPreviewOption().options.opacity, 0.1f);
}

/**
 * @tc.name: GetPreviewOptionFromModifier003
 * @tc.desc: Test UpdatePreviewOptionFromModifier
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(FrameNodeTestNg, GetPreviewOptionFromModifier003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FrameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    EXPECT_NE(frameNode, nullptr);
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    auto dragEventActuator = AceType::MakeRefPtr<DragEventActuator>(
        AceType::WeakClaim(AceType::RawPtr(gestureEventHub)), DRAG_DIRECTION, FINGERS_NUMBER, DISTANCE);
    /**
     * @tc.steps: step2. get DragPreviewOption.
     */
    NG::DragPreviewOption previewOption;
    previewOption.onApply = [](WeakPtr<NG::FrameNode> frameNode) {
        auto node = frameNode.Upgrade();
        CHECK_NULL_VOID(node);
        if ((PARA_OPACITY_VALUE_2 <= MAX_OPACITY) && (PARA_OPACITY_VALUE_2 > MIN_OPACITY)) {
            node->GetRenderContext()->UpdateOpacity(PARA_OPACITY_VALUE_2);
        } else {
            node->GetRenderContext()->UpdateOpacity(DEFAULT_OPACITY);
        }
    };
    /**
     * @tc.steps: step3. set opacity.
     */
    frameNode->SetDragPreviewOptions(previewOption);
    /**
     * @tc.steps: step4. call UpdatePreviewOptionFromModifier
     * @tc.expected: opacity in DragPreviewOption is equal to 0.2f.
     */
    dragEventActuator->UpdatePreviewOptionFromModifier(frameNode);
    EXPECT_EQ(frameNode->GetDragPreviewOption().options.opacity, 0.2f);
}

/**
 * @tc.name: GetPreviewOptionFromModifier004
 * @tc.desc: Test UpdatePreviewOptionFromModifier
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(FrameNodeTestNg, GetPreviewOptionFromModifier004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FrameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    EXPECT_NE(frameNode, nullptr);
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    auto dragEventActuator = AceType::MakeRefPtr<DragEventActuator>(
        AceType::WeakClaim(AceType::RawPtr(gestureEventHub)), DRAG_DIRECTION, FINGERS_NUMBER, DISTANCE);
    /**
     * @tc.steps: step2. get DragPreviewOption.
     */
    auto dragPreviewOption = frameNode->GetDragPreviewOption();
    /**
     * @tc.steps: step3. set opacity.
     */
    dragPreviewOption.options.opacity = 0.0f;
    frameNode->SetDragPreviewOptions(dragPreviewOption);
    /**
     * @tc.steps: step4. call UpdatePreviewOptionFromModifier
     * @tc.expected: opacity in DragPreviewOption is equal to 0.95f.
     */
    dragEventActuator->UpdatePreviewOptionFromModifier(frameNode);
    dragPreviewOption = frameNode->GetDragPreviewOption();
    EXPECT_EQ(dragPreviewOption.options.opacity, 0.95f);
}

/**
 * @tc.name: GetPreviewOptionFromModifier005
 * @tc.desc: Test UpdatePreviewOptionFromModifier
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(FrameNodeTestNg, GetPreviewOptionFromModifier005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FrameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    EXPECT_NE(frameNode, nullptr);
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    auto dragEventActuator = AceType::MakeRefPtr<DragEventActuator>(
        AceType::WeakClaim(AceType::RawPtr(gestureEventHub)), DRAG_DIRECTION, FINGERS_NUMBER, DISTANCE);
    /**
     * @tc.steps: step2. get DragPreviewOption.
     */
    NG::DragPreviewOption previewOption;
    previewOption.onApply = [](WeakPtr<NG::FrameNode> frameNode) {
        auto node = frameNode.Upgrade();
        CHECK_NULL_VOID(node);
        if ((PARA_OPACITY_VALUE_3 <= MAX_OPACITY) && (PARA_OPACITY_VALUE_3 > MIN_OPACITY)) {
            node->GetRenderContext()->UpdateOpacity(PARA_OPACITY_VALUE_3);
        } else {
            node->GetRenderContext()->UpdateOpacity(DEFAULT_OPACITY);
        }
    };
    /**
     * @tc.steps: step3. set opacity.
     */
    frameNode->SetDragPreviewOptions(previewOption);
    /**
     * @tc.steps: step4. call UpdatePreviewOptionFromModifier
     * @tc.expected: opacity in DragPreviewOption is equal to 0.3f.
     */
    dragEventActuator->UpdatePreviewOptionFromModifier(frameNode);
    EXPECT_EQ(frameNode->GetDragPreviewOption().options.opacity, 0.3f);
}

/**
 * @tc.name: GetPreviewOptionFromModifier006
 * @tc.desc: Test UpdatePreviewOptionFromModifier
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(FrameNodeTestNg, GetPreviewOptionFromModifier006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FrameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    EXPECT_NE(frameNode, nullptr);
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    auto dragEventActuator = AceType::MakeRefPtr<DragEventActuator>(
        AceType::WeakClaim(AceType::RawPtr(gestureEventHub)), DRAG_DIRECTION, FINGERS_NUMBER, DISTANCE);
    /**
     * @tc.steps: step2. get DragPreviewOption.
     */
    NG::DragPreviewOption previewOption;
    previewOption.onApply = [](WeakPtr<NG::FrameNode> frameNode) {
        auto node = frameNode.Upgrade();
        CHECK_NULL_VOID(node);
        if ((PARA_OPACITY_VALUE_4 <= MAX_OPACITY) && (PARA_OPACITY_VALUE_4 > MIN_OPACITY)) {
            node->GetRenderContext()->UpdateOpacity(PARA_OPACITY_VALUE_4);
        } else {
            node->GetRenderContext()->UpdateOpacity(DEFAULT_OPACITY);
        }
    };
    /**
     * @tc.steps: step3. set opacity.
     */
    frameNode->SetDragPreviewOptions(previewOption);
    /**
     * @tc.steps: step4. call UpdatePreviewOptionFromModifier
     * @tc.expected: opacity in DragPreviewOption is equal to 0.4f.
     */
    dragEventActuator->UpdatePreviewOptionFromModifier(frameNode);
    EXPECT_EQ(frameNode->GetDragPreviewOption().options.opacity, 0.4f);
}

/**
 * @tc.name: GetPreviewOptionFromModifier007
 * @tc.desc: Test UpdatePreviewOptionFromModifier
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(FrameNodeTestNg, GetPreviewOptionFromModifier007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FrameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    EXPECT_NE(frameNode, nullptr);
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    auto dragEventActuator = AceType::MakeRefPtr<DragEventActuator>(
        AceType::WeakClaim(AceType::RawPtr(gestureEventHub)), DRAG_DIRECTION, FINGERS_NUMBER, DISTANCE);
    /**
     * @tc.steps: step2. get DragPreviewOption.
     */
    NG::DragPreviewOption previewOption;
    previewOption.onApply = [](WeakPtr<NG::FrameNode> frameNode) {
        auto node = frameNode.Upgrade();
        CHECK_NULL_VOID(node);
        if ((PARA_OPACITY_VALUE_5 <= MAX_OPACITY) && (PARA_OPACITY_VALUE_5 > MIN_OPACITY)) {
            node->GetRenderContext()->UpdateOpacity(PARA_OPACITY_VALUE_5);
        } else {
            node->GetRenderContext()->UpdateOpacity(DEFAULT_OPACITY);
        }
    };
    /**
     * @tc.steps: step3. set opacity.
     */
    frameNode->SetDragPreviewOptions(previewOption);
    /**
     * @tc.steps: step4. call UpdatePreviewOptionFromModifier
     * @tc.expected: opacity in DragPreviewOption is equal to 0.5f.
     */
    dragEventActuator->UpdatePreviewOptionFromModifier(frameNode);
    EXPECT_EQ(frameNode->GetDragPreviewOption().options.opacity, 0.5f);
}

/**
 * @tc.name: GetPreviewOptionFromModifier008
 * @tc.desc: Test UpdatePreviewOptionFromModifier
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(FrameNodeTestNg, GetPreviewOptionFromModifier008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FrameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    EXPECT_NE(frameNode, nullptr);
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    auto dragEventActuator = AceType::MakeRefPtr<DragEventActuator>(
        AceType::WeakClaim(AceType::RawPtr(gestureEventHub)), DRAG_DIRECTION, FINGERS_NUMBER, DISTANCE);
    /**
     * @tc.steps: step2. get DragPreviewOption.
     */
    NG::DragPreviewOption previewOption;
    previewOption.onApply = [](WeakPtr<NG::FrameNode> frameNode) {
        auto node = frameNode.Upgrade();
        CHECK_NULL_VOID(node);
        if ((PARA_OPACITY_VALUE_6 <= MAX_OPACITY) && (PARA_OPACITY_VALUE_6 > MIN_OPACITY)) {
            node->GetRenderContext()->UpdateOpacity(PARA_OPACITY_VALUE_6);
        } else {
            node->GetRenderContext()->UpdateOpacity(DEFAULT_OPACITY);
        }
    };
    /**
     * @tc.steps: step3. set opacity.
     */
    frameNode->SetDragPreviewOptions(previewOption);
    /**
     * @tc.steps: step4. call UpdatePreviewOptionFromModifier
     * @tc.expected: opacity in DragPreviewOption is equal to 0.6f.
     */
    dragEventActuator->UpdatePreviewOptionFromModifier(frameNode);
    EXPECT_EQ(frameNode->GetDragPreviewOption().options.opacity, 0.6f);
}

/**
 * @tc.name: GetPreviewOptionFromModifier009
 * @tc.desc: Test UpdatePreviewOptionFromModifier
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(FrameNodeTestNg, GetPreviewOptionFromModifier009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FrameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    EXPECT_NE(frameNode, nullptr);
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    auto dragEventActuator = AceType::MakeRefPtr<DragEventActuator>(
        AceType::WeakClaim(AceType::RawPtr(gestureEventHub)), DRAG_DIRECTION, FINGERS_NUMBER, DISTANCE);
    /**
     * @tc.steps: step2. get DragPreviewOption.
     */
    NG::DragPreviewOption previewOption;
    previewOption.onApply = [](WeakPtr<NG::FrameNode> frameNode) {
        auto node = frameNode.Upgrade();
        CHECK_NULL_VOID(node);
        if ((PARA_OPACITY_VALUE_7 <= MAX_OPACITY) && (PARA_OPACITY_VALUE_7 > MIN_OPACITY)) {
            node->GetRenderContext()->UpdateOpacity(PARA_OPACITY_VALUE_7);
        } else {
            node->GetRenderContext()->UpdateOpacity(DEFAULT_OPACITY);
        }
    };
    /**
     * @tc.steps: step3. set opacity.
     */
    frameNode->SetDragPreviewOptions(previewOption);
    /**
     * @tc.steps: step4. call UpdatePreviewOptionFromModifier
     * @tc.expected: opacity in DragPreviewOption is equal to 0.7f.
     */
    dragEventActuator->UpdatePreviewOptionFromModifier(frameNode);
    EXPECT_EQ(frameNode->GetDragPreviewOption().options.opacity, 0.7f);
}

/**
 * @tc.name: GetPreviewOptionFromModifier010
 * @tc.desc: Test UpdatePreviewOptionFromModifier
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(FrameNodeTestNg, GetPreviewOptionFromModifier010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FrameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    EXPECT_NE(frameNode, nullptr);
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    auto dragEventActuator = AceType::MakeRefPtr<DragEventActuator>(
        AceType::WeakClaim(AceType::RawPtr(gestureEventHub)), DRAG_DIRECTION, FINGERS_NUMBER, DISTANCE);
    /**
     * @tc.steps: step2. get DragPreviewOption.
     */
    NG::DragPreviewOption previewOption;
    previewOption.onApply = [](WeakPtr<NG::FrameNode> frameNode) {
        auto node = frameNode.Upgrade();
        CHECK_NULL_VOID(node);
        if ((PARA_OPACITY_VALUE_8 <= MAX_OPACITY) && (PARA_OPACITY_VALUE_8 > MIN_OPACITY)) {
            node->GetRenderContext()->UpdateOpacity(PARA_OPACITY_VALUE_8);
        } else {
            node->GetRenderContext()->UpdateOpacity(DEFAULT_OPACITY);
        }
    };
    /**
     * @tc.steps: step3. set opacity.
     */
    frameNode->SetDragPreviewOptions(previewOption);
    /**
     * @tc.steps: step4. call UpdatePreviewOptionFromModifier
     * @tc.expected: opacity in DragPreviewOption is equal to 1.0f.
     */
    dragEventActuator->UpdatePreviewOptionFromModifier(frameNode);
    EXPECT_EQ(frameNode->GetDragPreviewOption().options.opacity, 1.0f);
}

/**
 * @tc.name: GetPreviewOptionFromModifier011
 * @tc.desc: Test UpdatePreviewOptionFromModifier
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(FrameNodeTestNg, GetPreviewOptionFromModifier011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FrameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    EXPECT_NE(frameNode, nullptr);
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    auto dragEventActuator = AceType::MakeRefPtr<DragEventActuator>(
        AceType::WeakClaim(AceType::RawPtr(gestureEventHub)), DRAG_DIRECTION, FINGERS_NUMBER, DISTANCE);
    /**
     * @tc.steps: step2. get DragPreviewOption.
     */
    auto dragPreviewOption = frameNode->GetDragPreviewOption();
    /**
     * @tc.steps: step3. set opacity.
     */
    dragPreviewOption.options.opacity = 2.0f;
    frameNode->SetDragPreviewOptions(dragPreviewOption);
    /**
     * @tc.steps: step4. call UpdatePreviewOptionFromModifier
     * @tc.expected: opacity in DragPreviewOption is equal to 0.95f.
     */
    dragEventActuator->UpdatePreviewOptionFromModifier(frameNode);
    dragPreviewOption = frameNode->GetDragPreviewOption();
    EXPECT_EQ(dragPreviewOption.options.opacity, 0.95f);
}

/**
 * @tc.name: GetPreviewOptionFromModifier012
 * @tc.desc: Test UpdatePreviewOptionFromModifier
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(FrameNodeTestNg, GetPreviewOptionFromModifier012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FrameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    EXPECT_NE(frameNode, nullptr);
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    auto dragEventActuator = AceType::MakeRefPtr<DragEventActuator>(
        AceType::WeakClaim(AceType::RawPtr(gestureEventHub)), DRAG_DIRECTION, FINGERS_NUMBER, DISTANCE);
    /**
     * @tc.steps: step2. get DragPreviewOption.
     */
    auto dragPreviewOption = frameNode->GetDragPreviewOption();
    /**
     * @tc.steps: step3. set opacity.
     */
    dragPreviewOption.options.opacity = 50.0f;
    frameNode->SetDragPreviewOptions(dragPreviewOption);
    /**
     * @tc.steps: step4. call UpdatePreviewOptionFromModifier
     * @tc.expected: opacity in DragPreviewOption is equal to 0.95f.
     */
    dragEventActuator->UpdatePreviewOptionFromModifier(frameNode);
    dragPreviewOption = frameNode->GetDragPreviewOption();
    EXPECT_EQ(dragPreviewOption.options.opacity, 0.95f);
}

/**
 * @tc.name: GetPreviewOptionFromModifier013
 * @tc.desc: Test UpdatePreviewOptionFromModifier
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(FrameNodeTestNg, GetPreviewOptionFromModifier013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FrameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    EXPECT_NE(frameNode, nullptr);
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    auto dragEventActuator = AceType::MakeRefPtr<DragEventActuator>(
        AceType::WeakClaim(AceType::RawPtr(gestureEventHub)), DRAG_DIRECTION, FINGERS_NUMBER, DISTANCE);
    /**
     * @tc.steps: step2. get DragPreviewOption.
     */
    auto dragPreviewOption = frameNode->GetDragPreviewOption();
    /**
     * @tc.steps: step3. set opacity.
     */
    dragPreviewOption.options.opacity = 60.0f;
    frameNode->SetDragPreviewOptions(dragPreviewOption);
    /**
     * @tc.steps: step4. call UpdatePreviewOptionFromModifier
     * @tc.expected: opacity in DragPreviewOption is equal to 0.95f.
     */
    dragEventActuator->UpdatePreviewOptionFromModifier(frameNode);
    dragPreviewOption = frameNode->GetDragPreviewOption();
    EXPECT_EQ(dragPreviewOption.options.opacity, 0.95f);
}

/**
 * @tc.name: GetPreviewOptionFromModifier014
 * @tc.desc: Test UpdatePreviewOptionFromModifier
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(FrameNodeTestNg, GetPreviewOptionFromModifier014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FrameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    EXPECT_NE(frameNode, nullptr);
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    auto dragEventActuator = AceType::MakeRefPtr<DragEventActuator>(
        AceType::WeakClaim(AceType::RawPtr(gestureEventHub)), DRAG_DIRECTION, FINGERS_NUMBER, DISTANCE);
    /**
     * @tc.steps: step2. get DragPreviewOption.
     */
    auto dragPreviewOption = frameNode->GetDragPreviewOption();
    /**
     * @tc.steps: step3. set opacity.
     */
    dragPreviewOption.options.opacity = -60.0f;
    frameNode->SetDragPreviewOptions(dragPreviewOption);
    /**
     * @tc.steps: step4. call UpdatePreviewOptionFromModifier
     * @tc.expected: opacity in DragPreviewOption is equal to 0.95f.
     */
    dragEventActuator->UpdatePreviewOptionFromModifier(frameNode);
    dragPreviewOption = frameNode->GetDragPreviewOption();
    EXPECT_EQ(dragPreviewOption.options.opacity, 0.95f);
}

/**
 * @tc.name: GetPreviewOptionFromModifier015
 * @tc.desc: Test UpdatePreviewOptionFromModifier
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(FrameNodeTestNg, GetPreviewOptionFromModifier015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FrameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    EXPECT_NE(frameNode, nullptr);
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    auto dragEventActuator = AceType::MakeRefPtr<DragEventActuator>(
        AceType::WeakClaim(AceType::RawPtr(gestureEventHub)), DRAG_DIRECTION, FINGERS_NUMBER, DISTANCE);
    /**
     * @tc.steps: step2. get DragPreviewOption.
     */
    auto dragPreviewOption = frameNode->GetDragPreviewOption();
    /**
     * @tc.steps: step3. set auto scrolling when drag to the edge of scrollable component.
     */
    dragPreviewOption.enableEdgeAutoScroll = false;
    frameNode->SetDragPreviewOptions(dragPreviewOption);
    /**
     * @tc.steps: step4. call UpdatePreviewOptionFromModifier
     * @tc.expected: enableEdgeAutoScroll is false.
     */
    dragEventActuator->UpdatePreviewOptionFromModifier(frameNode);
    dragPreviewOption = frameNode->GetDragPreviewOption();
    EXPECT_EQ(dragPreviewOption.enableEdgeAutoScroll, false);
}

/**
 * @tc.name: FrameNodeJSCustomProperty
 * @tc.desc: Test JSCustomProperty.
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeJSCustomProperty, TestSize.Level1)
{
    /**
     * @tc.steps: step1. initialize parameters.
     */
    auto frameNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    std::string value;
    /**
     * @tc.steps: step2. set isCNode true
     * @tc.expected: expect result updateFlag is false.
     */
    frameNode->setIsCNode(true);
    std::function<bool()> func = []() -> bool { return true; };
    std::function<std::string(const std::string&)> getFuncA = [](const std::string& key) -> std::string {
        return "getFuncA";
    };
    frameNode->SetJSCustomProperty(func, getFuncA);
    bool updateFlagValue = frameNode->GetCapiCustomProperty("updateFlag", value);
    EXPECT_EQ(updateFlagValue, false);

    /**
     * @tc.steps: step3. set isCNode false and func true.
     * @tc.expected: expect result updateFlag is true.
     */
    frameNode->setIsCNode(false);
    func = []() -> bool { return true; };
    getFuncA = [](const std::string& key) -> std::string {
        return "getFuncA";
    };
    frameNode->SetJSCustomProperty(func, getFuncA);
    frameNode->setIsCNode(true);
    std::string flagValue;
    bool updateFlagValue1 = frameNode->GetCapiCustomProperty("updateFlag", flagValue);
    EXPECT_EQ(updateFlagValue1, true);
    EXPECT_EQ(flagValue, "1");

    /**
     * @tc.steps: step4. set isCNode false and func false.
     * @tc.expected: expect result updateFlag is false.
     */
    frameNode->setIsCNode(false);
    func = []() -> bool { return false; };
    getFuncA = [](const std::string& key) -> std::string {
        return "getFuncA";
    };
    frameNode->SetJSCustomProperty(func, getFuncA);
    frameNode->setIsCNode(true);
    std::string flagValue1;
    bool updateFlagValue2 = frameNode->GetCapiCustomProperty("updateFlag", flagValue1);
    EXPECT_EQ(updateFlagValue2, true);

    /**
     * @tc.steps: step5. set getCustomProperty_ value getFuncA.
     * @tc.expected: expect result value getFuncA.
     */
    func = []() -> bool { return true; };
    getFuncA = [](const std::string& key) -> std::string {
        return "getFuncA";
    };
    frameNode->SetJSCustomProperty(func, getFuncA);
    std::string getValue;
    bool result = frameNode->GetJSCustomProperty("key", getValue);
    EXPECT_EQ(result, true);
    EXPECT_EQ(getValue, "getFuncA");
}

/**
 * @tc.name: FrameNodeJSCustomProperty001
 * @tc.desc: Test JSCustomProperty.
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeJSCustomProperty001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. initialize parameters.
     */
    auto frameNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);

    /**
     * @tc.steps: step2. set isCNode false
     * @tc.expected: expect result updateFlag is false.
     */
    frameNode->setIsCNode(false);
    std::function<bool()> func = []() -> bool { return true; };
    std::function<std::string(const std::string&)> getFuncAFromJS = [](const std::string& key) -> std::string {
        return "getFuncAFromJS";
    };
    std::function<std::string()> getFuncBFromJS = []() -> std::string { return "getFuncBFromJS"; };
    frameNode->SetJSCustomProperty(func, getFuncAFromJS, std::move(getFuncBFromJS));

    InspectorFilter filter;
    auto jsonValue = JsonUtil::Create(true);
    frameNode->ToJsonValue(jsonValue, filter);
    EXPECT_EQ(jsonValue->GetString("customProperty"), "getFuncBFromJS");

    /**
     * @tc.steps: step3. set isCNode ture
     * @tc.expected: expect result updateFlag is false.
     */
    frameNode->setIsCNode(true);
    frameNode->SetJSCustomProperty(func, getFuncAFromJS, std::move(getFuncBFromJS));
    std::string flagValue;
    bool updateFlagValue1 = frameNode->GetCapiCustomProperty("updateFlag", flagValue);
    auto jsonValueIsCNode = JsonUtil::Create(true);
    frameNode->ToJsonValue(jsonValueIsCNode, filter);
    EXPECT_EQ(updateFlagValue1, true);
    EXPECT_EQ(flagValue, "1");
    EXPECT_NE(jsonValueIsCNode->GetString("customProperty"), "getFuncBFromJS");

    /**
     * @tc.steps: step4. Remove updateFlag value and set isCNode false. Then add custom property.
     * @tc.expected: expect the custom property can be set.
     */
    frameNode->RemoveCustomProperty("updateFlag");
    frameNode->setIsCNode(false);
    frameNode->AddCustomProperty("key", "value1");
    bool result = frameNode->GetCapiCustomProperty("key", flagValue);
    EXPECT_EQ(result, false);
    result = frameNode->GetCustomPropertyByKey("key", flagValue);
    EXPECT_EQ(result, true);
    EXPECT_EQ(flagValue, "value1");
}

/**
 * @tc.name: FrameNodeCapiCustomProperty
 * @tc.desc: Test CapiCustomProperty.
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeCapiCustomProperty, TestSize.Level1)
{
    /**
     * @tc.steps: step1. initialize parameters.
     */
    auto frameNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    std::string value;
    
    /**
     * @tc.steps: step2. GetCapiCustomProperty
     * @tc.expected: expect result value false.
     */
    frameNode->setIsCNode(false);
    bool result = frameNode->GetCapiCustomProperty("key", value);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step3. add the key value as value1.
     * @tc.expected: expect result value1.
     */
    frameNode->setIsCNode(true);
    frameNode->AddCustomProperty("key", "value1");
    result = frameNode->GetCapiCustomProperty("key", value);
    EXPECT_EQ(result, true);
    EXPECT_EQ(value, "value1");

    /**
     * @tc.steps: step4. set key is value1
     * @tc.expected: expect result value.
     */
    frameNode->setIsCNode(true);
    frameNode->AddCustomProperty("key", "value1");
    result = frameNode->GetCapiCustomProperty("key1", value);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step5. set key is value1, remove key.
     * @tc.expected: expect result false.
     */
    frameNode->setIsCNode(true);
    frameNode->AddCustomProperty("key", "value1");
    frameNode->RemoveCustomProperty("key");
    result = frameNode->GetCapiCustomProperty("key", value);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: FrameNodeCapiCustomProperty
 * @tc.desc: Test CapiCustomProperty.
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameDumpOnSizeChangeInfo, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     * @tc.expected: expect is not nullptr.
     */
    auto frameNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    EXPECT_NE(frameNode, nullptr);
 
    /**
     * @tc.steps: step2. onSizeChangeDumpInfos push_back.
     * @tc.expected: expect is not nullptr.
     */
    frameNode->onSizeChangeDumpInfos.clear();
    frameNode->onSizeChangeDumpInfos.push_back({1625491200, RectF{}, RectF{}});
    frameNode->onSizeChangeDumpInfos.push_back({1625494800, RectF{}, RectF{}});
    EXPECT_EQ(frameNode->onSizeChangeDumpInfos.size(), 2);
    
    /**
     * @tc.steps: step3. create json.
     * @tc.expected: expect is not nullptr.
     */
    std::unique_ptr<JsonValue> json = JsonUtil::Create(true);
    EXPECT_NE(json, nullptr);

    /**
     * @tc.steps: step4. test DumpOnSizeChangeInfo.
     * @tc.expected: expect is "".
     */
    frameNode->DumpOnSizeChangeInfo(json);
    EXPECT_EQ(json->GetString(), "");
}

/**
 * @tc.name: FrameNodeDumpOverlayInfo001
 * @tc.desc: Test DumpOverlayInfo.
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameDumpOverlayInfo001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     * @tc.expected: expect is nullptr.
     */
    auto frameNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. create json.
     * @tc.expected: expect is nullptr.
     */
    std::unique_ptr<JsonValue> json = JsonUtil::Create(true);
    EXPECT_NE(json, nullptr);

    /**
     * @tc.steps: step3. test DumpOverlayInfo.
     * @tc.expected: expect is FALSE.
     */
    frameNode->DumpOverlayInfo(json);
    const auto& valueNode = json->GetValue("IsOverlayNode");
    bool hasKeyNode = !(valueNode->IsNull());
    EXPECT_FALSE(hasKeyNode);

    const auto& valueOffset = json->GetValue("OverlayOffset");
    bool hasKeyOffset = !(valueNode->IsNull());
    EXPECT_FALSE(hasKeyOffset);
}

/**
 * @tc.name: FrameNodeDumpOverlayInfo002
 * @tc.desc: Test DumpOverlayInfo.
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameDumpOverlayInfo002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     * @tc.expected: expect is nullptr.
     */
    auto frameNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. create json.
     * @tc.expected: expect is nullptr.
     */
    std::unique_ptr<JsonValue> json = JsonUtil::Create(true);
    EXPECT_NE(json, nullptr);

    /**
     * @tc.steps: step3. set layoutProperty.
     * @tc.expected: expect is TRUE.
     */
    auto layoutProperty = frameNode->GetLayoutProperty();
    layoutProperty->SetIsOverlayNode(true);
    
    /**
     * @tc.steps: step4. test DumpOverlayInfo.
     * @tc.expected: expect is TRUE.
     */
    frameNode->DumpOverlayInfo(json);
    const auto& valueNode = json->GetValue("IsOverlayNode");
    bool hasKeyNode = !(valueNode->IsNull());
    EXPECT_TRUE(hasKeyNode);

    const auto& valueOffset = json->GetValue("OverlayOffset");
    bool hasKeyOffset = !(valueOffset->IsNull());
    EXPECT_TRUE(hasKeyOffset);
}

/**
 * @tc.name: FrameNodeDumpDragInfo
 * @tc.desc: Test DumpDragInfo.
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameDumpOverlayInfo, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     * @tc.expected: expect is nullptr.
     */
    auto frameNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. create json.
     * @tc.expected: expect is nullptr.
     */
    std::unique_ptr<JsonValue> json = JsonUtil::Create(true);
    EXPECT_NE(json, nullptr);

    /**
     * @tc.steps: step3. test DumpDragInfo.
     * @tc.expected: expect is TRUE.
     */
    frameNode->DumpDragInfo(json);
    const auto& valueDrag = json->GetValue("Draggable");
    bool hasKeyDrag = !(valueDrag->IsNull());
    EXPECT_TRUE(hasKeyDrag);

    const auto& valueUser = json->GetValue("UserSet");
    bool hasKeyUser = !(valueUser->IsNull());
    EXPECT_TRUE(hasKeyUser);

    const auto& valueCustomer = json->GetValue("CustomerSet");
    bool hasKeyCustomer = !(valueCustomer->IsNull());
    EXPECT_TRUE(hasKeyCustomer);

    const auto& valuePreview = json->GetValue("DragPreview");
    bool hasKeyPreview = !(valuePreview->IsNull());
    EXPECT_TRUE(hasKeyPreview);

    const auto& valueEvent = json->GetValue("Event");
    bool hasKeyEvent = !(valueEvent->IsNull());
    EXPECT_TRUE(hasKeyEvent);
}

/**
 * @tc.name: FrameNodeDumpAlignRulesInfo
 * @tc.desc: Test DumpAlignRulesInfo.
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeDumpAlignRulesInfo, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     * @tc.expected: expect is nullptr.
     */
    auto frameNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. create json.
     * @tc.expected: expect is nullptr.
     */
    std::unique_ptr<JsonValue> json = JsonUtil::Create(true);
    EXPECT_NE(json, nullptr);

    /**
     * @tc.steps: step3. set layoutProperty.
     * @tc.expected: expect is TRUE.
     */
    auto layoutProperty = frameNode->GetLayoutProperty();

    /**
     * @tc.steps: step5. test DumpAlignRulesInfo.
     * @tc.expected: expect is FALSE.
     */
    frameNode->DumpAlignRulesInfo(json);
    const auto& valueAlignRules = json->GetValue("AlignRules");
    bool hasKeyAlignRules = !(valueAlignRules->IsNull());
    EXPECT_FALSE(hasKeyAlignRules);
}

/**
 * @tc.name: FrameNodeDumpSafeAreaInfo
 * @tc.desc: Test DumpSafeAreaInfo.
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeDumpSafeAreaInfo, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     * @tc.expected: expect is nullptr.
     */
    auto frameNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. create json.
     * @tc.expected: expect is nullptr.
     */
    std::unique_ptr<JsonValue> json = JsonUtil::Create(true);
    EXPECT_NE(json, nullptr);
    
    /**
     * @tc.steps: step3. set layoutProperty.
     * @tc.expected: expect is TRUE.
     */
    auto layoutProperty = frameNode->GetLayoutProperty();

    /**
     * @tc.steps: step5. test DumpSafeAreaInfo.
     * @tc.expected: expect is FALSE.
     */
    frameNode->DumpSafeAreaInfo(json);

    SafeAreaExpandOpts opts;
    opts.switchToNone = true;
    frameNode->GetLayoutProperty()->UpdateSafeAreaExpandOpts(opts);
    SafeAreaInsets safeArea;
    frameNode->GetLayoutProperty()->UpdateSafeAreaInsets(safeArea);
    frameNode->DumpSafeAreaInfo(json);

    /**
     * @tc.steps: step6. safeAreaExpandOpts_ is nullptr.
     * @tc.expected: expect is FALSE.
     */
    const auto& valueExpandOpts = json->GetValue("SafeAreaExpandOpts");
    bool hasKeyExpandOpts = !(valueExpandOpts->IsNull());
    EXPECT_TRUE(hasKeyExpandOpts);
    
    /**
     * @tc.steps: step7. safeAreaInsets_ is nullptr.
     * @tc.expected: expect is FALSE.
     */
    const auto& valueInsets = json->GetValue("SafeAreaInsets");
    bool hasKeyInsets = !(valueInsets->IsNull());
    EXPECT_TRUE(hasKeyInsets);

    /**
     * @tc.steps: step8. OrParentExpansive_ is nullptr.
     * @tc.expected: expect is FALSE.
     */
    const auto& valueSelf = json->GetValue("selfAdjust");
    bool hasKeySelf = !(valueSelf->IsNull());
    EXPECT_FALSE(hasKeySelf);

    const auto& valueParent = json->GetValue("parentAdjust");
    bool hasKeyParent = !(valueParent->IsNull());
    EXPECT_FALSE(hasKeyParent);

    /**
     * @tc.steps: step9. safeSafeAreaManager_ is nullptr.
     * @tc.expected: expect is FALSE.
     */
    const auto& valueIgnore = json->GetValue("ignoreSafeArea");
    bool hasKeyIgnore = !(valueIgnore->IsNull());
    EXPECT_FALSE(hasKeyIgnore);

    const auto& valueNeedAvoid = json->GetValue("isNeedAvoidWindow");
    bool hasKeyNeedAvoid = !(valueNeedAvoid->IsNull());
    EXPECT_FALSE(hasKeyNeedAvoid);

    const auto& valueFullScreen = json->GetValue("isFullScreen");
    bool hasKeyFullScreen = !(valueFullScreen->IsNull());
    EXPECT_FALSE(hasKeyFullScreen);

    const auto& valueKeyboard = json->GetValue("isKeyboardAvoidMode");
    bool hasKeyKeyboard = !(valueKeyboard->IsNull());
    EXPECT_FALSE(hasKeyKeyboard);

    const auto& valueUseCutout = json->GetValue("isUseCutout");
    bool hasKeyUseCutout = !(valueUseCutout->IsNull());
    EXPECT_FALSE(hasKeyUseCutout);
}

/**
 * @tc.name: FrameNodeBuildLayoutInfo
 * @tc.desc: Test BuildLayoutInfo.
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeBuildLayoutInfo, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     * @tc.expected: expect is nullptr.
     */
    auto frameNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. create json.
     * @tc.expected: expect is nullptr.
     */
    std::unique_ptr<JsonValue> json = JsonUtil::Create(true);
    EXPECT_NE(json, nullptr);
    
    /**
     * @tc.steps: step3. set layoutProperty.
     * @tc.expected: expect is TRUE.
     */
    auto layoutProperty = frameNode->GetLayoutProperty();

    /**
     * @tc.steps: step4. set geometryNode.
     * @tc.expected: expect is TRUE.
     */
    auto geometryNode = frameNode->GetGeometryNode();

    /**
     * @tc.steps: step5. test BuildLayoutInfo.
     * @tc.expected: expect is FALSE.
     */
    frameNode->BuildLayoutInfo(json);

    auto layoutConstraintF_ = LayoutConstraintF();
    layoutConstraintF_.maxSize = CONTAINER_SIZE;
    layoutConstraintF_.percentReference = CONTAINER_SIZE;
    frameNode->geometryNode_->SetParentLayoutConstraint(layoutConstraintF_);
    frameNode->geometryNode_->SetFrameOffset(OffsetF(1.0f, 0.0f));
    frameNode->layoutProperty_->UpdateVisibility(VisibleType::INVISIBLE);
    PaddingProperty padding;
    padding.left = CalcLength(0.0f);
    padding.right = CalcLength(0.0f);
    padding.top = CalcLength(0.0f);
    padding.bottom = CalcLength(0.0f);
    frameNode->layoutProperty_->UpdatePadding(padding);
    frameNode->layoutProperty_->UpdateSafeAreaPadding(padding);
    BorderWidthProperty overCountBorderWidth;
    overCountBorderWidth.SetBorderWidth(Dimension(10, DimensionUnit::VP));
    frameNode->layoutProperty_->UpdateBorderWidth(overCountBorderWidth);
    MarginProperty marginProperty;
    frameNode->layoutProperty_->UpdateMargin(marginProperty);
    NG::RectF testRect = { 10.0f, 10.0f, 10.0f, 10.0f };
    frameNode->layoutProperty_->SetLayoutRect(testRect);
    frameNode->BuildLayoutInfo(json);

    /**
     * @tc.steps: step5. ParentLayoutConstraint is nullptr.
     * @tc.expected: expect is FALSE.
     */
    const auto& valueConstraint = json->GetValue("ParentLayoutConstraint");
    bool hasKeyConstraint = !(valueConstraint->IsNull());
    EXPECT_TRUE(hasKeyConstraint);

    const auto& valuetop = json->GetValue("top");
    bool hasKeytop = !(valuetop->IsNull());
    EXPECT_TRUE(hasKeytop);

    const auto& valueleft = json->GetValue("left");
    bool hasKeyleft = !(valueleft->IsNull());
    EXPECT_TRUE(hasKeyleft);

    const auto& valueActive = json->GetValue("Active");
    bool hasKeyActive = !(valueActive->IsNull());
    EXPECT_TRUE(hasKeyActive);

    const auto& valueVisible = json->GetValue("Visible");
    bool hasKeyVisible = !(valueVisible->IsNull());
    EXPECT_TRUE(hasKeyVisible);

    const auto& valuePadding = json->GetValue("Padding");
    bool hasKeyPadding = !(valuePadding->IsNull());
    EXPECT_TRUE(hasKeyPadding);

    const auto& valueBorder = json->GetValue("Border");
    bool hasKeyBorder = !(valueBorder->IsNull());
    EXPECT_TRUE(hasKeyBorder);

    const auto& valueMargin = json->GetValue("Margin");
    bool hasKeyMargin = !(valueMargin->IsNull());
    EXPECT_TRUE(hasKeyMargin);

    const auto& valueLayout = json->GetValue("LayoutRect");
    bool hasKeyLayout = !(valueLayout->IsNull());
    EXPECT_TRUE(hasKeyLayout);
}

/**
 * @tc.name: FrameNodeMarkRemoving001
 * @tc.desc: Test MarkRemoving.
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeMarkRemoving001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     * @tc.expected: expect is nullptr.
     */
    auto frameNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. test MarkRemoving.
     * @tc.expected: expect is false.
     */
    auto pendingRemove = frameNode->MarkRemoving();
    EXPECT_FALSE(pendingRemove);
}

/**
 * @tc.name: FrameNodeMarkRemoving002
 * @tc.desc: Test MarkRemoving.
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeMarkRemoving002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     * @tc.expected: expect is nullptr.
     */
    auto frameNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. set layoutProperty.
     * @tc.expected: expect is nullptr.
     */
    auto layoutProperty = frameNode->GetLayoutProperty();

    /**
     * @tc.steps: step3. test MarkRemoving.
     * @tc.expected: expect is false.
     */
    auto pendingRemove = frameNode->MarkRemoving();
    EXPECT_FALSE(pendingRemove);
}

/**
 * @tc.name: FrameNodeMarkRemoving003
 * @tc.desc: Test MarkRemoving.
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeMarkRemoving003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     * @tc.expected: expect is nullptr.
     */
    auto frameNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. set geometryNode.
     * @tc.expected: expect is nullptr.
     */
    auto geometryNode = frameNode->GetGeometryNode();
    
    /**
     * @tc.steps: step3. test MarkRemoving.
     * @tc.expected: expect is false.
     */
    auto pendingRemove = frameNode->MarkRemoving();
    EXPECT_FALSE(pendingRemove);
}

/**
 * @tc.name: FrameNodeMarkRemoving004
 * @tc.desc: Test MarkRemoving.
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeMarkRemoving004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     * @tc.expected: expect is nullptr.
     */
    auto frameNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. set geometryNode and layoutProperty.
     * @tc.expected: expect is nullptr.
     */
    auto geometryNode = frameNode->GetGeometryNode();
    auto layoutProperty = frameNode->GetLayoutProperty();

    /**
     * @tc.steps: step3. test MarkRemoving.
     * @tc.expected: expect is false.
     */
    auto pendingRemove = frameNode->MarkRemoving();
    EXPECT_FALSE(pendingRemove);
}

/**
 * @tc.name: FrameNodeOnConfigurationUpdate
 * @tc.desc: Test of OnConfigurationUpdate
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeOnConfigurationUpdate, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create childNode and itemNode
     * @tc.expected: childNode and itemNode is not null
     */
    auto childNode = FrameNode::CreateFrameNode(
        "child", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    auto itemNode = FrameNode::CreateFrameNode(
        "itemNode", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    childNode->AddChild(itemNode);

    /**
     * @tc.steps: step2. create configurationChange.
     */
    ConfigurationChange configurationChange;

    /**
     * @tc.steps: step3. childNode Update Configuration.
     * @tc.expected: update success
     */
    childNode->OnConfigurationUpdate(configurationChange);

    /**
     * @tc.steps: step4. set languageUpdate is true.
     * @tc.expected: update success
     */
    configurationChange.languageUpdate = true;
    childNode->OnConfigurationUpdate(configurationChange);

    /**
     * @tc.steps: step5. set colorModeUpdate is true
     * @tc.expected: update success
     */
    configurationChange.colorModeUpdate = true;
    childNode->OnConfigurationUpdate(configurationChange);

    /**
     * @tc.steps: step6. set directionUpdate is true
     * @tc.expected: update success
     */
    configurationChange.directionUpdate = true;
    childNode->OnConfigurationUpdate(configurationChange);

    /**
     * @tc.steps: step7. set dpiUpdate is true
     * @tc.expected: update success
     */
    configurationChange.dpiUpdate = true;
    childNode->OnConfigurationUpdate(configurationChange);

    /**
     * @tc.steps: step8. set fontUpdate is true
     * @tc.expected: update success
     */
    configurationChange.fontUpdate = true;
    configurationChange.iconUpdate = true;
    configurationChange.skinUpdate = true;
    configurationChange.fontWeightScaleUpdate = true;
    childNode->OnConfigurationUpdate(configurationChange);

    /**
     * @tc.steps: step9. set fontScaleUpdate is true
     * @tc.expected: update success
     */
    configurationChange.fontScaleUpdate = true;
    childNode->OnConfigurationUpdate(configurationChange);

    childNode->SetBackgroundLayoutConstraint(itemNode);
    childNode->ForceUpdateLayoutPropertyFlag(PROPERTY_UPDATE_MEASURE_SELF);
    childNode->GetPaintRectWithTransform();
    childNode->GetTransformScale();
    childNode->SetJSViewActive(true);

    /**
     * @tc.steps: step10. create layoutProperty
     * @tc.expected: layoutProperty is nullptr
     */
    auto layoutProperty = childNode->GetLayoutProperty();
    EXPECT_FALSE(layoutProperty->IsOverlayNode());
    layoutProperty->SetIsOverlayNode(true);
    childNode->DumpOverlayInfo();
    EXPECT_TRUE(layoutProperty->IsOverlayNode());
}

/**
 * @tc.name: FrameNodeOnRemoveFromParent001
 * @tc.desc: Test OnRemoveFromParent.
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeOnRemoveFromParent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     * @tc.expected: expect is nullptr.
     */
    auto frameNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. set allowTransition.
     * @tc.expected: expect is true.
     */
    auto allowTransition = true;

    /**
     * @tc.steps: step3. test OnRemoveFromParent.
     * @tc.expected: expect is true.
     */
    auto removeFrom = frameNode->OnRemoveFromParent(allowTransition);
    EXPECT_TRUE(removeFrom);
}

/**
 * @tc.name: FrameNodeOnRemoveFromParent002
 * @tc.desc: Test OnRemoveFromParent.
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeOnRemoveFromParent002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     * @tc.expected: expect is nullptr.
     */
    auto frameNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. set allowTransition.
     * @tc.expected: expect is false.
     */
    auto allowTransition = false;

    /**
     * @tc.steps: step3. test OnRemoveFromParent.
     * @tc.expected: expect is true.
     */
    auto removeFrom = frameNode->OnRemoveFromParent(allowTransition);
    EXPECT_TRUE(removeFrom);
}

/**
 * @tc.name: FrameNodeFindChildByName
 * @tc.desc: Test FindChildByName.
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeFindChildByName, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     * @tc.expected: expect is not nullptr.
     */
    const std::string parentName = "Parent";
    const std::string oneName = "One";
    const std::string oneChildName = "OneChild";
    const std::string twoName = "Two";
    const std::string twoChildName = "TwoChild";
    const std::string testName = "test";
    auto parent = FrameNode::CreateFrameNode(parentName, 10, AceType::MakeRefPtr<Pattern>(), true);
    auto one = FrameNode::CreateFrameNode(oneName, 20, AceType::MakeRefPtr<Pattern>());
    auto oneChild = FrameNode::CreateFrameNode(oneChildName, 30, AceType::MakeRefPtr<Pattern>());
    auto two = FrameNode::CreateFrameNode(twoName, 40, AceType::MakeRefPtr<Pattern>());
    auto twoChild = FrameNode::CreateFrameNode(twoChildName, 50, AceType::MakeRefPtr<Pattern>());

    EXPECT_NE(parent, nullptr);
    EXPECT_NE(one, nullptr);
    EXPECT_NE(oneChild, nullptr);
    EXPECT_NE(two, nullptr);
    EXPECT_NE(twoChild, nullptr);

    /**
     * @tc.steps: step1. Set the node's relation.
     * @tc.expected: expect is null nullptr.
     */
    parent->AddChild(one);
    parent->AddChild(two);
    one->AddChild(oneChild);
    two->AddChild(twoChild);

    EXPECT_NE(parent, nullptr);
    EXPECT_NE(one, nullptr);
    EXPECT_NE(two, nullptr);

    /**
     * @tc.steps: step3. update InspectorId.
     * @tc.expected: update success
     */
    parent->UpdateInspectorId(parentName);
    one->UpdateInspectorId(oneName);
    oneChild->UpdateInspectorId(oneChildName);
    two->UpdateInspectorId(twoName);
    twoChild->UpdateInspectorId(twoChildName);

    /**
     * @tc.steps: step3. find oneChild.
     * @tc.expected: success
     */
    auto finalResult = FrameNode::FindChildByName(parent, oneName);
    EXPECT_NE(finalResult, oneChild);

    /**
     * @tc.steps: step3. find testName.
     * @tc.expected: fail
     */
    auto noChildResult = FrameNode::FindChildByName(parent, testName);
    EXPECT_EQ(noChildResult, nullptr);

    /**
     * @tc.steps: step3. clear parent to find twoChild.
     * @tc.expected: fail
     */
    parent->Clean();
    auto noHaveResult = FrameNode::FindChildByName(parent, twoChildName);
    EXPECT_EQ(noHaveResult, nullptr);
}

/**
 * @tc.name: FrameNodeSwapDirty
 * @tc.desc: Test SwapDirtyLayoutWrapperOnMainThread
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeSwapDirty001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. creat frameNode and layoutProperty
     */
    RefPtr<LayoutWrapper> layoutWrapper = FRAME_NODE2->CreateLayoutWrapper(true, true);
    auto frameNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto layoutProperty = frameNode->GetLayoutProperty<LayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step2. setBorderWidth and updateBorderWidth.
     * @tc.expected: expect borderWidth property is not nullptr.
     */
    BorderWidthProperty overCountBorderWidth;
    overCountBorderWidth.SetBorderWidth(Dimension(10, DimensionUnit::VP));
    layoutProperty->UpdateBorderWidth(overCountBorderWidth);
    frameNode->SetLayoutProperty(layoutProperty);

    /**
     * @tc.steps: step3. callback SwapDirtyLayoutWrapperOnMainThread
     * @tc.expected: expect GetBorderWidthProperty is not nullptr.
     */
    frameNode->SwapDirtyLayoutWrapperOnMainThread(layoutWrapper);
    EXPECT_NE(layoutProperty->GetBorderWidthProperty(), nullptr);
}

/**
 * @tc.name: FrameNodeSwapDirty
 * @tc.desc: Test SwapDirtyLayoutWrapperOnMainThread
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeSwapDirty002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. creat frameNode and layoutProperty
     */
    RefPtr<LayoutWrapper> layoutWrapper = FRAME_NODE2->CreateLayoutWrapper(true, true);
    auto frameNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto layoutProperty = frameNode->GetLayoutProperty<LayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step2. setBorderWidth and updateBorderWidth.
     * @tc.expected: expect borderWidth property is not nullptr.
     */
    BorderWidthProperty overCountBorderWidth;
    overCountBorderWidth.SetBorderWidth(Dimension(10, DimensionUnit::VP));
    layoutProperty->UpdateBorderWidth(overCountBorderWidth);
    frameNode->SetLayoutProperty(layoutProperty);

    /**
     * @tc.steps: step3. updatae layoutConstraint and set eventHub_.
     * @tc.expected: nullptr.
     */
    auto layoutConstraintF_ = LayoutConstraintF();
    layoutConstraintF_.maxSize = CONTAINER_SIZE;
    layoutConstraintF_.percentReference = CONTAINER_SIZE;
    frameNode->geometryNode_->SetParentLayoutConstraint(layoutConstraintF_);
    layoutProperty->UpdateLayoutConstraint(layoutConstraintF_);

    frameNode->GetOrCreateEventHub<EventHub>()->GetOrCreateFocusHub();
    frameNode->SwapDirtyLayoutWrapperOnMainThread(layoutWrapper);
    EXPECT_NE(frameNode->eventHub_, nullptr);
}

/**
 * @tc.name: FrameNodeSwapDirty
 * @tc.desc: Test SwapDirtyLayoutWrapperOnMainThread
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeSwapDirty003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. creat frameNode and layoutProperty
     */
    RefPtr<LayoutWrapper> layoutWrapper = FRAME_NODE2->CreateLayoutWrapper(true, true);
    auto frameNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto layoutProperty = frameNode->GetLayoutProperty<LayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step2. setBorderWidth and updateBorderWidth.
     * @tc.expected: expect borderWidth property is not nullptr.
     */
    BorderWidthProperty overCountBorderWidth;
    overCountBorderWidth.SetBorderWidth(Dimension(10, DimensionUnit::VP));
    layoutProperty->UpdateBorderWidth(overCountBorderWidth);
    frameNode->SetLayoutProperty(layoutProperty);

    /**
     * @tc.steps: step5. set currentFocus_ is true and call SwapDirtyLayoutWrapperOnMainThread.
     * @tc.expected: expect cover branch IsCurrentFocus() is true and function is run ok .
     */
    auto layoutConstraintF_ = LayoutConstraintF();
    layoutConstraintF_.maxSize = CONTAINER_SIZE;
    layoutConstraintF_.percentReference = CONTAINER_SIZE;
    frameNode->geometryNode_->SetParentLayoutConstraint(layoutConstraintF_);
    layoutProperty->UpdateLayoutConstraint(layoutConstraintF_);

    frameNode->GetOrCreateEventHub<EventHub>()->GetOrCreateFocusHub()->currentFocus_ = true;
    frameNode->SwapDirtyLayoutWrapperOnMainThread(layoutWrapper);
    EXPECT_TRUE(frameNode->GetOrCreateEventHub<EventHub>()->GetOrCreateFocusHub()->IsCurrentFocus());
}

/**
 * @tc.name: FrameNodeGeometryNodeToJsonValue
 * @tc.desc: Test method GeometryNodeToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeGeometryNodeToJsonValue, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create value.
     */
    auto value = JsonUtil::Create(true);

    /**
     * @tc.steps: step2. construct parameters.
     * @tc.expected: expect cover branch layoutProperty_ is nullptr.
     */
    auto frameNode = FrameNode::CreateFrameNode("frameNode", 2, AceType::MakeRefPtr<Pattern>());
    InspectorFilter filter;
    frameNode->GeometryNodeToJsonValue(value, filter);
    EXPECT_NE(frameNode->layoutProperty_, nullptr);

    /**
     * @tc.steps: step3. set layoutProperty_ and call GeometryNodeToJsonValue.
     * @tc.expected: expect cover branch layoutProperty_ is not nullptr.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    frameNode->layoutProperty_ = layoutProperty;
    frameNode->GeometryNodeToJsonValue(value, filter);
    EXPECT_NE(frameNode->layoutProperty_, nullptr);

    /**
     * @tc.steps: step4. set calcLayoutConstraint_ and call GeometryNodeToJsonValue.
     * @tc.expected: expect cover branch calcLayoutConstraint_ is not nullptr.
     */
    frameNode->layoutProperty_->calcLayoutConstraint_ = std::make_unique<MeasureProperty>();

    frameNode->GeometryNodeToJsonValue(value, filter);
    EXPECT_NE(frameNode->layoutProperty_->calcLayoutConstraint_, nullptr);

    /**
     * @tc.steps: step5. set selfIdealSize and call GeometryNodeToJsonValue.
     * @tc.expected: expect cover branch selfIdealSize has value.
     */
    std::optional<CalcLength> len = CalcLength("auto");
    frameNode->layoutProperty_->calcLayoutConstraint_->selfIdealSize = CalcSize(len, len);
    frameNode->GeometryNodeToJsonValue(value, filter);
    EXPECT_NE(frameNode->renderContext_, nullptr);
}

/**
 * @tc.name: FrameNodeDumpSimplifyCommonInfo
 * @tc.desc: Test DumpSimplifyCommonInfo.
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeDumpSimplifyCommonInfo, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     * @tc.expected: expect is nullptr.
     */
    auto frameNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. create json.
     * @tc.expected: expect is nullptr.
     */
    std::unique_ptr<JsonValue> json = JsonUtil::Create(true);
    EXPECT_NE(json, nullptr);

    /**
     * @tc.steps: step3. test DumpOverlayInfo.
     * @tc.expected: expect is FALSE.
     */
    frameNode->DumpSimplifyCommonInfo(json);
    const auto& valueFrameRect = json->GetValue("FrameRect");
    bool hasvalueFrameRect = !(valueFrameRect->IsNull());
    EXPECT_FALSE(hasvalueFrameRect);

    const auto& valueTransform = json->GetValue("PaintRectWithoutTransform");
    bool hasKeyTransform = !(valueTransform->IsNull());
    EXPECT_FALSE(hasKeyTransform);

    const auto& valueColor = json->GetValue("BackgroundColor");
    bool hasKeyColor = !(valueColor->IsNull());
    EXPECT_FALSE(hasKeyColor);

    const auto& valueOffset = json->GetValue("Offset");
    bool hasKeyOffset = !(valueOffset->IsNull());
    EXPECT_FALSE(hasKeyOffset);

    const auto& valueVisible = json->GetValue("Visible");
    bool hasKeyVisible = !(valueVisible->IsNull());
    EXPECT_FALSE(hasKeyVisible);

    const auto& valueLayoutRect = json->GetValue("LayoutRect");
    bool hasKeyLayoutRect = !(valueLayoutRect->IsNull());
    EXPECT_FALSE(hasKeyLayoutRect);

    const auto& valueConstraint = json->GetValue("UserDefinedConstraint");
    bool hasKeyConstraint = !(valueConstraint->IsNull());
    EXPECT_FALSE(hasKeyConstraint);

    const auto& valueContent = json->GetValue("ContentConstraint");
    bool hasKeyContent = !(valueContent->IsNull());
    EXPECT_FALSE(hasKeyContent);

    const auto& valueParentLayout = json->GetValue("ParentLayoutConstraint");
    bool hasKeyParentLayout = !(valueParentLayout->IsNull());
    EXPECT_FALSE(hasKeyParentLayout);
}

/**
 * @tc.name: FrameNodeDumpSimplifySafeAreaInfo
 * @tc.desc: Test DumpSimplifySafeAreaInfo.
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeDumpSimplifySafeAreaInfo, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     * @tc.expected: expect is nullptr.
     */
    auto frameNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. create json.
     * @tc.expected: expect is nullptr.
     */
    std::unique_ptr<JsonValue> json = JsonUtil::Create(true);
    EXPECT_NE(json, nullptr);

    /**
     * @tc.steps: step3. test DumpSimplifySafeAreaInfo.
     * @tc.expected: expect is FALSE.
     */
    frameNode->DumpSimplifySafeAreaInfo(json);
    const auto& valueExpandOpts = json->GetValue("SafeAreaExpandOpts");
    bool hasvalueExpandOpts = !(valueExpandOpts->IsNull());
    EXPECT_FALSE(hasvalueExpandOpts);

    const auto& valueInsets = json->GetValue("SafeAreaInsets");
    bool hasKeyInsets = !(valueInsets->IsNull());
    EXPECT_FALSE(hasKeyInsets);

    const auto& valueSelfAdjust = json->GetValue("SelfAdjust");
    bool hasKeySelfAdjust = !(valueSelfAdjust->IsNull());
    EXPECT_FALSE(hasKeySelfAdjust);

    const auto& valueParentSelfAdjust = json->GetValue("ParentSelfAdjust");
    bool hasKeyParentSelfAdjust = !(valueParentSelfAdjust->IsNull());
    EXPECT_FALSE(hasKeyParentSelfAdjust);

    const auto& valueIgnore = json->GetValue("IgnoreSafeArea");
    bool hasKeyIgnore = !(valueIgnore->IsNull());
    EXPECT_FALSE(hasKeyIgnore);

    const auto& valueAvoidWindow = json->GetValue("IsNeedAvoidWindow");
    bool hasKeyAvoidWindow = !(valueAvoidWindow->IsNull());
    EXPECT_FALSE(hasKeyAvoidWindow);

    const auto& valueIsFullScreen = json->GetValue("IsFullScreen");
    bool hasKeyIsFullScreen = !(valueIsFullScreen->IsNull());
    EXPECT_FALSE(hasKeyIsFullScreen);

    const auto& valueIsKeyboard = json->GetValue("IsKeyboardAvoidMode");
    bool hasKeyIsKeyboard = !(valueIsKeyboard->IsNull());
    EXPECT_FALSE(hasKeyIsKeyboard);

    const auto& valueIsUseCutout = json->GetValue("IsUseCutout");
    bool hasKeyIsUseCutout = !(valueIsUseCutout->IsNull());
    EXPECT_FALSE(hasKeyIsUseCutout);
}

/**
 * @tc.name: FrameNodeDumpCommonInfo
 * @tc.desc: Test DumpCommonInfo.
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeDumpCommonInfo, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     * @tc.expected: expect is nullptr.
     */
    auto frameNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. create json.
     * @tc.expected: expect is nullptr.
     */
    std::unique_ptr<JsonValue> json = JsonUtil::Create(true);
    EXPECT_NE(json, nullptr);

    /**
     * @tc.steps: step3. test DumpCommonInfo.
     * @tc.expected: expect is FALSE.
     */
    frameNode->DumpCommonInfo(json);

    frameNode->renderContext_->UpdateBackgroundColor(Color::BLUE);
    MeasureProperty constraint;
    frameNode->layoutProperty_->UpdateCalcLayoutProperty(constraint);
    frameNode->propInspectorId_ = "test";
    frameNode->DumpCommonInfo(json);
    MarginProperty marginProperty;
    frameNode->layoutProperty_->UpdateMargin(marginProperty);
    frameNode->DumpCommonInfo(json);
    BorderWidthProperty overCountBorderWidth;
    overCountBorderWidth.SetBorderWidth(Dimension(10, DimensionUnit::VP));
    frameNode->layoutProperty_->UpdateBorderWidth(overCountBorderWidth);
    frameNode->DumpCommonInfo(json);
    PaddingProperty padding;
    frameNode->layoutProperty_->UpdatePadding(padding);
    frameNode->DumpCommonInfo(json);

    const auto& valueFrameRect = json->GetValue("FrameRect");
    bool hasvalueFrameRect = !(valueFrameRect->IsNull());
    EXPECT_TRUE(hasvalueFrameRect);

    const auto& valuePaintRect = json->GetValue("PaintRect without transform");
    bool hasvaluePaintRect = !(valuePaintRect->IsNull());
    EXPECT_TRUE(hasvaluePaintRect);

    const auto& valueBackgroundColor= json->GetValue("BackgroundColor");
    bool hasvalueBackgroundColor = !(valueBackgroundColor->IsNull());
    EXPECT_TRUE(hasvalueBackgroundColor);

    frameNode->DumpInfo(json);
    frameNode->DumpAdvanceInfo(json);
    const auto& valueConstraint = json->GetValue("ParentLayoutConstraint");
    bool hasKeyConstraint = !(valueConstraint->IsNull());
    EXPECT_FALSE(hasKeyConstraint);
}

/**
 * @tc.name: FrameNodeGetJSCustomProperty001
 * @tc.desc: Test GetJSCustomProperty.
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeGetJSCustomProperty001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     * @tc.expected: expect is not nullptr.
     */
    auto frameNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. test GetJSCustomProperty.
     * @tc.expected: expect false.
     */
    const std::string key  = "testKey";
    std::string value = "testValue";
    auto hasKey = frameNode->GetJSCustomProperty(key, value);

    EXPECT_FALSE(hasKey);
}

/**
 * @tc.name: FrameNodeGetJSCustomProperty002
 * @tc.desc: Test GetJSCustomProperty
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeGetJSCustomProperty002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     * @tc.expected: expect is not nullptr.
     */
    auto frameNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. set getCustomProperty_ value test.
     * @tc.expected: expect result value test.
     */
    std::function<bool()> func = []() -> bool { return true; };
    std::function<std::string(const std::string&)> getFunc = [](const std::string& key) -> std::string {
        return "test";};
    frameNode->SetJSCustomProperty(func, getFunc);

    /**
     * @tc.steps: step2. test GetJSCustomProperty.
     * @tc.expected: expect true.
     */
    const std::string key  = "testKey";
    std::string value = "testValue";
    auto hasKey = frameNode->GetJSCustomProperty(key, value);

    EXPECT_TRUE(hasKey);
    EXPECT_EQ(value, "test");
}

/**
 * @tc.name: FrameNodeGetCapiCustomProperty001
 * @tc.desc: Test GetCapiCustomProperty.
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeGetCapiCustomProperty001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     * @tc.expected: expect is not nullptr.
     */
    auto frameNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. GetCapiCustomProperty
     * @tc.expected: expect result value false.
     */
    frameNode->setIsCNode(false);
    std::string value;
    bool hasKey = frameNode->GetCapiCustomProperty("key", value);
    EXPECT_FALSE(hasKey);
}

/**
 * @tc.name: FrameNodeGetCapiCustomProperty002
 * @tc.desc: Test GetCapiCustomProperty.
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeGetCapiCustomProperty002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     * @tc.expected: expect is not nullptr.
     */
    auto frameNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. GetCapiCustomProperty.
     * @tc.expected: expect result true.
     */
    frameNode->setIsCNode(true);
    frameNode->AddCustomProperty("key", "value");
    std::string value;
    bool result = frameNode->GetCapiCustomProperty("key", value);
    EXPECT_TRUE(result);
    EXPECT_EQ(value, "value");
}
} // namespace OHOS::Ace::NG