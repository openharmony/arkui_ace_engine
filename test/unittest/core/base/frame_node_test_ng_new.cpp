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
    FRAME_NODE2->eventHub_->SetEnabled(true);
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
    FRAME_NODE2->eventHub_->SetEnabled(true);
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
    FRAME_NODE2->eventHub_->SetEnabled(true);
    SystemProperties::debugEnabled_ = true;
    auto gestureJudgeFunc = [](const RefPtr<GestureInfo>& gestureInfo, const std::shared_ptr<BaseGestureEvent>& info) {
        return GestureJudgeResult::REJECT;
    };
    auto gestureEventHub = FRAME_NODE2->eventHub_->GetOrCreateGestureEventHub();
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
    FRAME_NODE2->eventHub_->SetEnabled(true);
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
    FRAME_NODE2->eventHub_->SetEnabled(true);
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
    FRAME_NODE2->eventHub_->SetEnabled(true);
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
    FRAME_NODE2->eventHub_->SetEnabled(true);
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
    FRAME_NODE2->eventHub_->SetEnabled(true);

    DimensionRect responseRect(Dimension(0), Dimension(0), DimensionOffset(OFFSETF));
    std::vector<DimensionRect> mouseResponseRegion;
    mouseResponseRegion.emplace_back(responseRect);

    /**
     * @tc.steps: step2. call GetResponseRegionList.
     * @tc.expected: expect MouseResponseRegion is not empty.
     */
    auto gestureEventHub = FRAME_NODE2->eventHub_->GetOrCreateGestureEventHub();
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
    auto gestureEventHub = FRAME_NODE2->eventHub_->GetOrCreateGestureEventHub();
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
    FRAME_NODE3->eventHub_->SetEnabled(true);
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
    frameNode->eventHub_->SetEnabled(true);
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
    frameNode->eventHub_->SetEnabled(true);
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
    frameNode->eventHub_->SetEnabled(true);
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
    frameNode->eventHub_->SetEnabled(true);
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
    FRAME_NODE->eventHub_->SetEnabled(true);
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
    FRAME_NODE->eventHub_->SetEnabled(true);
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
    FRAME_NODE->eventHub_->SetEnabled(true);
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
    EXPECT_EQ(FRAME_NODE->GetPixelMap(), nullptr);

    /**
     * @tc.steps: step3. set a pixelMap of gestureHub, and call GetPixelMap.
     * @tc.expected: expect GetPixelMap() != nullptr.
     */
    void* voidPtr = static_cast<void*>(new char[0]);
    RefPtr<PixelMap> pixelMap = PixelMap::CreatePixelMap(voidPtr);
    ASSERT_NE(pixelMap, nullptr);
    gestureHub->SetPixelMap(pixelMap);
    EXPECT_NE(FRAME_NODE->GetPixelMap(), nullptr);

    /**
     * @tc.steps: step4. set a pixelMap of the renderContext, and call GetPixelMap.
     * @tc.expected: expect GetPixelMap() != nullptr.
     */
    gestureHub->SetPixelMap(nullptr);
    EXPECT_EQ(FRAME_NODE->GetPixelMap(), nullptr);
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
    auto eventHub = FRAME_NODE2->GetEventHub<NG::EventHub>();
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
    FRAME_NODE2->eventHub_->SetOnSizeChanged(std::move(onSizeChanged));
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
    EXPECT_NE(childNode->eventHub_->GetGestureEventHub(), nullptr);
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
} // namespace OHOS::Ace::NG