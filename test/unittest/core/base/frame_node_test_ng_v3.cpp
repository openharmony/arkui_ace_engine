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

#include "core/common/recorder/exposure_processor.h"
#include "core/event/touch_event.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {} // namespace

/**
 * @tc.name: ResetLayoutAlgorithmTest1
 * @tc.desc: Test the function ResetLayoutAlgorithm with default param
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, ResetLayoutAlgorithmTest1, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode1 = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto frameNode2 = FrameNode::CreateFrameNode("framenode", 2, AceType::MakeRefPtr<Pattern>());
    auto frameNode3 = FrameNode::CreateFrameNode("framenode", 3, AceType::MakeRefPtr<Pattern>());
    /**
     * @tc.steps: step2. mount nodes and create layoutAlgorithm
     */
    frameNode2->MountToParent(frameNode1);
    frameNode3->MountToParent(frameNode2);
    EXPECT_NE(frameNode1->GetLayoutAlgorithm(), nullptr);
    EXPECT_NE(frameNode2->GetLayoutAlgorithm(), nullptr);
    EXPECT_NE(frameNode3->GetLayoutAlgorithm(), nullptr);
    /**
     * @tc.steps: step2. start to clear. layoutAlgo of frameNode1 will not not be cleared
     */
    frameNode1->ClearSubtreeLayoutAlgorithm(false);
    EXPECT_TRUE(frameNode1->HasLayoutAlgorithm());
    EXPECT_FALSE(frameNode2->HasLayoutAlgorithm());
    EXPECT_FALSE(frameNode3->HasLayoutAlgorithm());
}

/**
 * @tc.name: ResetLayoutAlgorithmTest2
 * @tc.desc: Test the function ResetLayoutAlgorithm with default param
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, ResetLayoutAlgorithmTest2, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode1 = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto frameNode2 = FrameNode::CreateFrameNode("framenode", 2, AceType::MakeRefPtr<Pattern>());
    auto frameNode3 = FrameNode::CreateFrameNode("framenode", 3, AceType::MakeRefPtr<Pattern>());

    /**
     * @tc.steps: step2. mount nodes and create layoutAlgorithm
     */
    frameNode2->MountToParent(frameNode1);
    frameNode3->MountToParent(frameNode2);
    EXPECT_NE(frameNode1->GetLayoutAlgorithm(), nullptr);
    EXPECT_NE(frameNode2->GetLayoutAlgorithm(), nullptr);
    EXPECT_NE(frameNode3->GetLayoutAlgorithm(), nullptr);
    /**
     * @tc.steps: step3. start to clear. layoutAlgo of frameNode1 will not not be cleared
     */
    frameNode1->ClearSubtreeLayoutAlgorithm(true);
    EXPECT_FALSE(frameNode1->HasLayoutAlgorithm());
    EXPECT_FALSE(frameNode2->HasLayoutAlgorithm());
    EXPECT_FALSE(frameNode3->HasLayoutAlgorithm());
}

/**
 * @tc.name: ResetLayoutAlgorithmTest3
 * @tc.desc: Test the function ResetLayoutAlgorithm and node3 should still have layoutAlgorithm
 * because chain broke at node2
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, ResetLayoutAlgorithmTest3, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode1 = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto frameNode2 = FrameNode::CreateFrameNode("framenode", 2, AceType::MakeRefPtr<Pattern>());
    auto frameNode3 = FrameNode::CreateFrameNode("framenode", 3, AceType::MakeRefPtr<Pattern>());
    /**
     * @tc.steps: step2. mount nodes and create layoutAlgorithm
     */
    frameNode2->MountToParent(frameNode1);
    frameNode3->MountToParent(frameNode2);
    EXPECT_NE(frameNode1->GetLayoutAlgorithm(), nullptr);
    EXPECT_NE(frameNode3->GetLayoutAlgorithm(), nullptr);
    /**
     * @tc.steps: step3. start to clear. layoutAlgo of frameNode1 will not not be cleared
     */
    frameNode1->ClearSubtreeLayoutAlgorithm(true);
    EXPECT_FALSE(frameNode1->HasLayoutAlgorithm());
    EXPECT_FALSE(frameNode2->HasLayoutAlgorithm());
    EXPECT_TRUE(frameNode3->HasLayoutAlgorithm());
}

/**
 * @tc.name: ResetLayoutAlgorithmTest4
 * @tc.desc: Test the function ResetLayoutAlgorithm with clearing the whole tree
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, ResetLayoutAlgorithmTest4, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode1 = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto frameNode2 = FrameNode::CreateFrameNode("framenode", 2, AceType::MakeRefPtr<Pattern>());
    auto frameNode3 = FrameNode::CreateFrameNode("framenode", 3, AceType::MakeRefPtr<Pattern>());
    /**
     * @tc.steps: step2. mount nodes and create layoutAlgorithm
     */
    frameNode2->MountToParent(frameNode1);
    frameNode3->MountToParent(frameNode2);
    EXPECT_NE(frameNode1->GetLayoutAlgorithm(), nullptr);
    EXPECT_NE(frameNode3->GetLayoutAlgorithm(), nullptr);
    /**
     * @tc.steps: step3. start to clear. layoutAlgo of frameNode1 will not not be cleared
     */
    frameNode1->ClearSubtreeLayoutAlgorithm(true, true);
    EXPECT_FALSE(frameNode1->HasLayoutAlgorithm());
    EXPECT_FALSE(frameNode2->HasLayoutAlgorithm());
    EXPECT_FALSE(frameNode3->HasLayoutAlgorithm());
}
/**
 * @tc.name: FrameNodeGetExtraCustomProperty001
 * @tc.desc: Test GetExtraCustomProperty.
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeGetExtraCustomProperty001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. initialize parameters.
     */
    auto frameNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    char value[7]= "value1";
    /**
     * @tc.steps: step2. set key is value1
     * @tc.expected: expect result value.
     */
    frameNode->setIsCNode(true);
    frameNode->AddExtraCustomProperty("key", value);
    bool result = frameNode->GetExtraCustomProperty("key1");
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: FrameNodeGetExtraCustomProperty002
 * @tc.desc: Test GetExtraCustomProperty.
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeGetExtraCustomProperty002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. initialize parameters.
     */
    auto frameNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);

    /**
     * @tc.steps: step2. set key is value
     * @tc.expected: expect result value.
     */
    char value[7]= "value1";
    frameNode->setIsCNode(true);
    frameNode->AddExtraCustomProperty("key", value);
    bool result = frameNode->GetExtraCustomProperty("key");
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: FrameNodeRemoveExtraCustomProperty001
 * @tc.desc: Test RemoveExtraCustomProperty.
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeRemoveExtraCustomProperty001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. initialize parameters.
     */
    auto frameNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);

    /**
     * @tc.steps: step2. set key is value1, remove key.
     * @tc.expected: expect result false.
     */
    char value[7]= "value1";
    frameNode->setIsCNode(true);
    frameNode->AddExtraCustomProperty("key", value);
    frameNode->RemoveExtraCustomProperty("key");
    bool result = frameNode->GetExtraCustomProperty("key");
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: FrameTestNg100
 * @tc.desc: Test CollectSelfAxisResult.
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNg100, TestSize.Level1)
{
    /**
     * @tc.steps: step1. initialize parameters.
     */
    auto frameNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    PointF globalPoint;
    PointF localPoint;
    PointF parentRevertPoint;
    AxisTestResult onAxisResult;
    HitTestResult testResult;
    TouchRestrict touchRestrict;
    bool isConsumed = true;
    bool isPreventBubbling = false;
    SystemProperties::debugEnabled_ = true;
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    gestureEventHub->SetHitTestMode(HitTestMode::HTMNONE);
    eventHub->SetGestureEventHub(gestureEventHub);
    frameNode->eventHub_ = eventHub;
    frameNode->CollectSelfAxisResult(globalPoint, localPoint, isConsumed, parentRevertPoint,
            onAxisResult, isPreventBubbling, testResult, touchRestrict, false);
    EXPECT_EQ(testResult, HitTestResult::BUBBLING);
    gestureEventHub->SetHitTestMode(HitTestMode::HTMBLOCK);
    isConsumed = false;
    frameNode->CollectSelfAxisResult(globalPoint, localPoint, isConsumed, parentRevertPoint,
            onAxisResult, isPreventBubbling, testResult, touchRestrict, false);
    EXPECT_EQ(testResult, HitTestResult::STOP_BUBBLING);
}

/**
 * @tc.name: FrameTestNg101
 * @tc.desc: Test GetOrCreateFocusHub.
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNg101, TestSize.Level1)
{
    /**
     * @tc.steps: step1. initialize parameters.
     */
    auto frameNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    frameNode->focusHub_ = nullptr;
    frameNode->pattern_ = nullptr;
    auto focusHub = frameNode->GetOrCreateFocusHub();
    EXPECT_NE(focusHub, nullptr);
    auto focusHub2 = frameNode->GetOrCreateFocusHub();
    EXPECT_NE(focusHub2, nullptr);
    frameNode->focusHub_ = nullptr;
    frameNode->pattern_ = AceType::MakeRefPtr<Pattern>();
    auto focusHub3 = frameNode->GetOrCreateFocusHub();
    EXPECT_NE(focusHub3, nullptr);
    FocusPattern focusPattern = { FocusType::NODE, false };
    auto focusHub4 = frameNode->GetOrCreateFocusHub(focusPattern);
    EXPECT_NE(focusHub4, nullptr);
    frameNode->focusHub_ = nullptr;
    frameNode->pattern_ = nullptr;
    auto focusHub5 = frameNode->GetOrCreateFocusHub(focusPattern);
    frameNode->pattern_ = AceType::MakeRefPtr<Pattern>();
    EXPECT_NE(focusHub5, nullptr);
}

/**
 * @tc.name: FrameTestNg102
 * @tc.desc: Test Window state and position.
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNg102, TestSize.Level1)
{
    /**
     * @tc.steps: step1. initialize parameters.
     */
    auto frameNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    frameNode->OnWindowActivated();
    frameNode->OnWindowDeactivated();
    frameNode->GetPositionToScreen();
    frameNode->GetPositionToScreenWithTransform();
    EXPECT_NE(frameNode->renderContext_, nullptr);
    auto parent = FrameNode::CreateFrameNode("Parent", 10, AceType::MakeRefPtr<Pattern>(), true);
    auto one = FrameNode::CreateFrameNode("One", 20, AceType::MakeRefPtr<Pattern>());
    parent->AddChild(one);
    parent->topWindowBoundary_ = false;
    one->GetPaintRectOffsetNG(true, false);
    EXPECT_NE(one->renderContext_, nullptr);
}

/**
 * @tc.name: FrameTestNg103
 * @tc.desc: Test GetPaintRectToWindowWithTransform.
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNg103, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto child = FrameNode::CreateFrameNode("child", 20, AceType::MakeRefPtr<Pattern>());
    frameNode->AddChild(child);
    child->GetPaintRectToWindowWithTransform();
    EXPECT_NE(child->geometryNode_, nullptr);
}

/**
 * @tc.name: FrameTestNg104
 * @tc.desc: Test UpdateAccessibilityNodeRect.
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNg104, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    AceApplicationInfo::GetInstance().SetAccessibilityScreenReadEnabled(true);
    frameNode->OnAccessibilityEvent(AccessibilityEventType::CLICK, "");
    frameNode->UpdateAccessibilityNodeRect();
    EXPECT_NE(frameNode->renderContext_, nullptr);

    AceApplicationInfo::GetInstance().SetAccessibilityScreenReadEnabled(false);
    frameNode->UpdateAccessibilityNodeRect();
    EXPECT_NE(frameNode->renderContext_, nullptr);
}

/**
 * @tc.name: FrameTestNg105
 * @tc.desc: Test OnAutoEventParamUpdate.
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNg105, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto jsonValue = std::make_unique<JsonValue>();
    jsonValue->Put(Recorder::ORIGIN_PARAM, "ORIGIN_PARAM");
    frameNode->exposureProcessor_ = nullptr;
    auto exposureCfg = std::make_unique<JsonValue>();
    exposureCfg->Put(Recorder::EXPOSURE_CONFIG_RATIO, 2.2f);
    exposureCfg->Put(Recorder::EXPOSURE_CONFIG_DURATION, 5);
    jsonValue->Put(Recorder::EXPOSURE_CONFIG_PARAM, exposureCfg);
    frameNode->OnAutoEventParamUpdate(jsonValue->ToString());
    EXPECT_EQ(frameNode->exposureProcessor_, nullptr);
    auto ep = AceType::MakeRefPtr<Recorder::ExposureProcessor>("test", "0");
    frameNode->SetExposureProcessor(ep);
    EXPECT_NE(frameNode->exposureProcessor_, nullptr);
    RectF visibleRect;
    RectF frameRect;
    frameNode->GetVisibleRect(visibleRect, frameRect);
    EXPECT_NE(frameNode->renderContext_, nullptr);
}

/**
 * @tc.name: FrameTestNg106
 * @tc.desc: Test GetVisibleRectWithClip.
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNg106, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    RectF visibleRect, visibleInnerRect, frameRect;
    frameNode->GetVisibleRectWithClip(visibleRect, visibleInnerRect, frameRect);
    auto parent = FrameNode::CreateFrameNode("parent", 20, AceType::MakeRefPtr<Pattern>());
    parent->AddChild(frameNode);
    frameNode->isWindowBoundary_ = false;
    frameNode->onMainTree_ = true;
    frameNode->GetVisibleRectWithClip(visibleRect, visibleInnerRect, frameRect);
    EXPECT_FALSE(frameNode->isWindowBoundary_);
}

/**
 * @tc.name: GetGlobalPositionOnDisplay001
 * @tc.desc: Test frame node method GetGlobalPositionOnDisplay
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, GetGlobalPositionOnDisplay001, TestSize.Level1)
{
    OffsetF Offset = { 0, 0 };
    FRAME_NODE2->SetParent(FRAME_NODE3);
    auto globalDisplayOffset = FRAME_NODE2->GetGlobalPositionOnDisplay();
    EXPECT_EQ(globalDisplayOffset, Offset);
}

/**
 * @tc.name: GetCacheVisibleRectTest
 * @tc.desc: Test GetCacheVisibleRectTest.
 * @tc.type: FUNC
 */
 HWTEST_F(FrameNodeTestNg, GetCacheVisibleRectTest001, TestSize.Level1)
 {
    /**
     * @tc.steps: step1. initialize parameters.
     */
    auto frameNode = FrameNode::CreateFrameNode("test", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto parentNode = FrameNode::CreateFrameNode("testParent", 1, AceType::MakeRefPtr<Pattern>(), true);
    parentNode->AddChild(frameNode);
    /**
     * @tc.steps: step2. set key is value1, remove key.
     * @tc.expected: expect result false.
     */
    auto result = frameNode->GetCacheVisibleRect(0, false);
    EXPECT_EQ(result.cumulativeScale.x, 1.0);
    parentNode->GetRenderContext()->UpdateClipEdge(true);
    result = frameNode->GetCacheVisibleRect(1, true);
    EXPECT_EQ(result.cumulativeScale.x, 1.0);
    frameNode->isWindowBoundary_ = true;
    result = frameNode->GetCacheVisibleRect(1, true);
    EXPECT_EQ(result.cumulativeScale.x, 1.0);
}

/**
 * @tc.name: DumpSafeAreaInfoTest
 * @tc.desc: Test DumpSafeAreaInfo.
 * @tc.type: FUNC
 */
 HWTEST_F(FrameNodeTestNg, DumpSafeAreaInfoTest001, TestSize.Level1)
 {
    /**
     * @tc.steps: step1. initialize parameters.
     */
    auto frameNode = FrameNode::CreateFrameNode("test", 1, AceType::MakeRefPtr<Pattern>(), true);
    std::unique_ptr<JsonValue> json = JsonUtil::Create(true);
    /**
     * @tc.steps: step2. set key is value1, remove key.
     * @tc.expected: expect result false.
     */
    frameNode->DumpExtensionHandlerInfo(json);
    
    RefPtr<NG::DrawModifier> drawModifier = AceType::MakeRefPtr<NG::DrawModifier>();
    ASSERT_NE(drawModifier, nullptr);
    frameNode->SetDrawModifier(drawModifier);

    frameNode->DumpExtensionHandlerInfo(json);
    EXPECT_FALSE(json->GetValue("HasCustomerMeasure")->GetBool());
}

/**
 * @tc.name: GetCurrentPageRootNodeTest001
 * @tc.desc: Test GetCurrentPageRootNode.
 * @tc.type: FUNC
 */
 HWTEST_F(FrameNodeTestNg, GetCurrentPageRootNodeTest001, TestSize.Level1)
 {
    /**
     * @tc.steps: step1. initialize parameters.
     */
    auto frameNode = FrameNode::CreateFrameNode("page", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto child = FrameNode::CreateFrameNode(V2::JS_VIEW_ETS_TAG, 3, AceType::MakeRefPtr<Pattern>(), true);
    frameNode->AddChild(child);
    EXPECT_FALSE(frameNode->GetCurrentPageRootNode() != nullptr);
}

/**
 * @tc.name: GetCurrentPageRootNodeTest002
 * @tc.desc: Test GetCurrentPageRootNode.
 * @tc.type: FUNC
 */
 HWTEST_F(FrameNodeTestNg, GetCurrentPageRootNodeTest002, TestSize.Level1)
 {
    /**
     * @tc.steps: step1. initialize parameters.
     */
    auto frameNode = FrameNode::CreateFrameNode("page", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto child = FrameNode::CreateFrameNode("text", 3, AceType::MakeRefPtr<Pattern>(), true);
    frameNode->AddChild(child);
    EXPECT_TRUE(frameNode->GetCurrentPageRootNode() != nullptr);
}

/**
 * @tc.name: TriggerVisibleAreaChangeCallback100
 * @tc.desc: Test TriggerVisibleAreaChangeCallback.
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, TriggerVisibleAreaChangeCallback100, TestSize.Level1)
{
    /**
     * @tc.steps: step1. initialize parameters.
     */
    auto frameNode = FrameNode::CreateFrameNode("page", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto child = FrameNode::CreateFrameNode("column", 3, AceType::MakeRefPtr<Pattern>(), false);
    frameNode->SetActive(true);
    child->SetActive(true);
    frameNode->AddChild(child);
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    context->onShow_ = true;
    frameNode->AttachContext(AceType::RawPtr(context));
    child->AttachContext(AceType::RawPtr(context));

    RectF rect = RectF(0, 0, 100, 100);
    child->renderContext_->UpdatePaintRect(rect);
    frameNode->renderContext_->UpdatePaintRect(rect);
    auto eventHub = child->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto onVisibleChange = [](bool visible, double ratio) {};
    std::vector<double> ratioList = { 0.0, 1.0 };
    VisibleCallbackInfo addInfo;
    addInfo.callback = std::move(onVisibleChange);
    addInfo.isCurrentVisible = false;
    child->SetVisibleAreaUserCallback(ratioList, addInfo);
    auto& visibleAreaUserCallback = eventHub->GetVisibleAreaCallback(true);
    child->TriggerVisibleAreaChangeCallback(1, false);
    EXPECT_FALSE(visibleAreaUserCallback.measureFromViewport);
    visibleAreaUserCallback.measureFromViewport = true;
    child->TriggerVisibleAreaChangeCallback(2, false);
    EXPECT_TRUE(visibleAreaUserCallback.measureFromViewport);
}

/**
 * @tc.name: ConvertPointTest
 * @tc.desc: Test ConvertPoint.
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, ConvertPointTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. initialize parameters.
     */
    auto frameNode = FrameNode::CreateFrameNode("page", 1, AceType::MakeRefPtr<Pattern>(), true);
    frameNode->SetActive(true);

    /**
     * @tc.steps: step2. test the input null pointer.
     */
    OffsetF position = { 10, 10 };
    auto resultOfNullptr = frameNode->ConvertPoint(position, nullptr);
    EXPECT_EQ(resultOfNullptr, position);

    /**
     * @tc.steps: step3. test the input itself.
     */
    auto resultOfItself = frameNode->ConvertPoint(position, frameNode);
    EXPECT_EQ(resultOfItself, position);

    /**
     * @tc.steps: step4. test the input right parameter.
     */
    auto targetNode = FrameNode::CreateFrameNode("page", 2, AceType::MakeRefPtr<Pattern>(), true);
    targetNode->SetActive(true);
    auto child = FrameNode::CreateFrameNode("column", 3, AceType::MakeRefPtr<Pattern>(), false);
    child->SetActive(true);
    frameNode->AddChild(child);
    auto result = child->ConvertPoint(position, targetNode);
    EXPECT_EQ(position, result);
}

/**
 * @tc.name: FindSameParentComponentTest
 * @tc.desc: Test FindSameParentComponent.
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FindSameParentComponentTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. initialize parameters.
     */
    auto frameNode = FrameNode::CreateFrameNode("page", 1, AceType::MakeRefPtr<Pattern>(), true);
    frameNode->SetActive(true);

    auto child = FrameNode::CreateFrameNode("column", 3, AceType::MakeRefPtr<Pattern>(), false);
    ASSERT_NE(child, nullptr);
    child->SetActive(true);
    frameNode->AddChild(child);

    /**
     * @tc.steps: step2. test return nullptr.
     */
    EXPECT_FALSE(FindSameParentComponent(child, nullptr));
    EXPECT_FALSE(FindSameParentComponent(nullptr, child));

    /**
     * @tc.steps: step3. test the input right parameter.
     */
    auto result = FindSameParentComponent(frameNode, child);
    EXPECT_EQ(result, frameNode);
}

/**
 * @tc.name: FrameProxyChildrenTest001
 * @tc.desc: Test FrameProxy children handling when there are no children
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameProxyChildrenTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode instance without children.
     */
    auto frameNode = FrameNode::CreateFrameNode("testNode", 1, AceType::MakeRefPtr<Pattern>(), true);

    /**
     * @tc.steps: step2. Check initial child count.
     * @tc.expected: Child count should be zero.
     */
    EXPECT_EQ(frameNode->GetChildTrueTotalCount(), 0u);
}

/**
 * @tc.name: FrameProxyChildrenTest002
 * @tc.desc: Test FrameProxy children handling with single child
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameProxyChildrenTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode instance with one child.
     */
    auto frameNode = FrameNode::CreateFrameNode("testNode", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto childNode = FrameNode::CreateFrameNode("childNode", 2, AceType::MakeRefPtr<Pattern>());
    childNode->MountToParent(frameNode);

    /**
     * @tc.steps: step2. Check child count.
     * @tc.expected: Child count should be one.
     */
    EXPECT_EQ(frameNode->GetChildTrueTotalCount(), 0);

    /**
     * @tc.steps: step3. Check child index.
     * @tc.expected: Child index should be 0.
     */
    EXPECT_EQ(frameNode->GetChildTrueIndex(childNode), -1);
}

/**
 * @tc.name: FrameProxyChildrenTest003
 * @tc.desc: Test FrameProxy children handling with multiple children
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameProxyChildrenTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode instance with multiple children.
     */
    auto frameNode = FrameNode::CreateFrameNode("testNode", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto childNode1 = FrameNode::CreateFrameNode("childNode1", 2, AceType::MakeRefPtr<Pattern>());
    auto childNode2 = FrameNode::CreateFrameNode("childNode2", 3, AceType::MakeRefPtr<Pattern>());
    auto childNode3 = FrameNode::CreateFrameNode("childNode3", 4, AceType::MakeRefPtr<Pattern>());

    childNode1->MountToParent(frameNode);
    childNode2->MountToParent(frameNode);
    childNode3->MountToParent(frameNode);

    /**
     * @tc.steps: step2. Check total child count.
     * @tc.expected: Child count should be three.
     */
    EXPECT_EQ(frameNode->GetChildTrueTotalCount(), 0);

    /**
     * @tc.steps: step3. Check child indexes.
     * @tc.expected: Child indexes should be 0, 1, and 2 respectively.
     */
    EXPECT_EQ(frameNode->GetChildTrueIndex(childNode1), -1);
    EXPECT_EQ(frameNode->GetChildTrueIndex(childNode2), -1);
    EXPECT_EQ(frameNode->GetChildTrueIndex(childNode3), -1);
}

/**
 * @tc.name: FrameProxyResetChildrenTest001
 * @tc.desc: Test ResetChildren when inUse is false and needResetChild is false
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameProxyResetChildrenTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode with children.
     */
    auto frameNode = FrameNode::CreateFrameNode("testNode", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto childNode1 = FrameNode::CreateFrameNode("childNode1", 2, AceType::MakeRefPtr<Pattern>());
    auto childNode2 = FrameNode::CreateFrameNode("childNode2", 3, AceType::MakeRefPtr<Pattern>());

    childNode1->MountToParent(frameNode);
    childNode2->MountToParent(frameNode);

    /**
     * @tc.steps: step2. Verify initial state.
     */
    EXPECT_EQ(frameNode->GetChildTrueTotalCount(), 0);
    EXPECT_EQ(frameNode->GetChildTrueIndex(childNode1), -1);
    EXPECT_EQ(frameNode->GetChildTrueIndex(childNode2), -1);

    /**
     * @tc.steps: step3. Call GetAllChildrenWithBuild to initialize frameProxy internal structures.
     */
    auto children = frameNode->GetAllChildrenWithBuild();
    EXPECT_FALSE(children.empty());

    /**
     * @tc.steps: step4. Reset children with needResetChild = false.
     * @tc.expected: Children list should remain, but other structures should be cleared.
     */
    frameNode->RemoveAllChildInRenderTree();
    EXPECT_EQ(frameNode->GetChildTrueTotalCount(), 0);
}

/**
 * @tc.name: FrameProxySetActiveChildRangeTest001
 * @tc.desc: Test SetActiveChildRange when activeChildSets has no value
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameProxySetActiveChildRangeTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode instance.
     */
    auto frameNode = FrameNode::CreateFrameNode("testNode", 1, AceType::MakeRefPtr<Pattern>(), true);

    /**
     * @tc.steps: step2. Call SetActiveChildRange with empty activeChildSets.
     * @tc.expected: Function should return early without any processing.
     */
    std::optional<ActiveChildSets> activeChildSets = std::nullopt;
    std::optional<ActiveChildRange> activeChildRange = std::nullopt;

    frameNode->SetActiveChildRange(activeChildSets, activeChildRange);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: FrameProxySetActiveChildRangeTest002
 * @tc.desc: Test SetActiveChildRange with active items that match existing children
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameProxySetActiveChildRangeTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode with children and initialize frameProxy.
     */
    auto frameNode = FrameNode::CreateFrameNode("testNode", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto childNode1 = FrameNode::CreateFrameNode("childNode1", 2, AceType::MakeRefPtr<Pattern>());
    auto childNode2 = FrameNode::CreateFrameNode("childNode2", 3, AceType::MakeRefPtr<Pattern>());

    childNode1->MountToParent(frameNode);
    childNode2->MountToParent(frameNode);

    /**
     * @tc.steps: step2. Initialize frameProxy internal structures by getting children.
     */
    auto childrenBefore = frameNode->GetAllChildrenWithBuild();
    EXPECT_FALSE(childrenBefore.empty());
    EXPECT_EQ(frameNode->GetChildTrueTotalCount(), 2u);

    /**
     * @tc.steps: step3. Call SetActiveChildRange with activeChildSets that match existing children.
     * @tc.expected: Matching children should remain in partFrameNodeChildren_.
     */
    ActiveChildSets activeChildSets;
    activeChildSets.activeItems = { 0 };

    frameNode->SetActiveChildRange(activeChildSets, std::nullopt);

    auto child0 = frameNode->GetChildByIndex(0);
    auto child1 = frameNode->GetChildByIndex(1);

    EXPECT_NE(child0, nullptr);
    EXPECT_EQ(child1, 1);
}

/**
 * @tc.name: FrameProxySetActiveChildRangeTest003
 * @tc.desc: Test SetActiveChildRange with active items that don't match any children
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameProxySetActiveChildRangeTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode with children and initialize frameProxy.
     */
    auto frameNode = FrameNode::CreateFrameNode("testNode", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto childNode1 = FrameNode::CreateFrameNode("childNode1", 2, AceType::MakeRefPtr<Pattern>());
    auto childNode2 = FrameNode::CreateFrameNode("childNode2", 3, AceType::MakeRefPtr<Pattern>());

    childNode1->MountToParent(frameNode);
    childNode2->MountToParent(frameNode);

    /**
     * @tc.steps: step2. Initialize frameProxy internal structures.
     */
    auto childrenBefore = frameNode->GetAllChildrenWithBuild();
    EXPECT_FALSE(childrenBefore.empty());
    EXPECT_EQ(frameNode->GetChildTrueTotalCount(), 2u);

    /**
     * @tc.steps: step3. Call SetActiveChildRange with activeChildSets that don't match any existing children.
     * @tc.expected: All children in partFrameNodeChildren_ should be removed.
     */
    ActiveChildSets activeChildSets;
    activeChildSets.activeItems = { 10, 11, 12 };

    frameNode->SetActiveChildRange(activeChildSets, std::nullopt);

    auto child0 = frameNode->GetChildByIndex(0);
    auto child1 = frameNode->GetChildByIndex(1);

    EXPECT_EQ(child0, 1);
    EXPECT_EQ(child1, 1);
}

/**
 * @tc.name: FrameProxySetActiveChildRangeTest004
 * @tc.desc: Test SetActiveChildRange with activeChildRange but no JS_REPEAT child
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameProxySetActiveChildRangeTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode with normal children.
     */
    auto frameNode = FrameNode::CreateFrameNode("testNode", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto childNode = FrameNode::CreateFrameNode("childNode", 2, AceType::MakeRefPtr<Pattern>());
    childNode->MountToParent(frameNode);

    /**
     * @tc.steps: step2. Setup activeChildRange and call SetActiveChildRange.
     * @tc.expected: Should properly select the branch for non-JS_REPEAT children.
     */
    ActiveChildRange activeChildRange;
    activeChildRange.start = 0;
    activeChildRange.end = 5;
    activeChildRange.cacheStart = 1;
    activeChildRange.cacheEnd = 2;

    frameNode->SetActiveChildRange(std::nullopt, activeChildRange);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: FrameProxySetActiveChildRangeTest005
 * @tc.desc: Test SetActiveChildRange with both activeChildSets and activeChildRange
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameProxySetActiveChildRangeTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode with children.
     */
    auto frameNode = FrameNode::CreateFrameNode("testNode", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto childNode = FrameNode::CreateFrameNode("childNode", 2, AceType::MakeRefPtr<Pattern>());
    childNode->MountToParent(frameNode);

    /**
     * @tc.steps: step2. Setup both activeChildSets and activeChildRange.
     * @tc.expected: Should process both parameters correctly.
     */
    ActiveChildSets activeChildSets;
    activeChildSets.activeItems = { 0, 1 };
    activeChildSets.cachedItems = { 2, 3 };

    ActiveChildRange activeChildRange;
    activeChildRange.start = 0;
    activeChildRange.end = 10;
    activeChildRange.cacheStart = 1;
    activeChildRange.cacheEnd = 2;

    frameNode->SetActiveChildRange(activeChildSets, activeChildRange);
    EXPECT_TRUE(true);

    auto child = frameNode->GetChildByIndex(0);
    EXPECT_NE(child, nullptr);
}

/**
 * @tc.name: FrameProxyDumpTest001
 * @tc.desc: Test Dump when totalCount is 0
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameProxyDumpTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode without children.
     */
    auto frameNode = FrameNode::CreateFrameNode("testNode", 1, AceType::MakeRefPtr<Pattern>(), true);

    /**
     * @tc.steps: step2. Check Dump output through public interface.
     * @tc.expected: Should return "totalCount is 0" when no children exist.
     */
    frameNode->DumpInfo();

    auto json = JsonUtil::Create(true);
    frameNode->DumpInfo(json);

    EXPECT_NE(json, nullptr);
}

/**
 * @tc.name: FrameProxyDumpTest002
 * @tc.desc: Test Dump contains correct child information
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameProxyDumpTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode with children.
     */
    auto frameNode = FrameNode::CreateFrameNode("parentNode", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto childNode1 = FrameNode::CreateFrameNode("childNode1", 10, AceType::MakeRefPtr<Pattern>());
    auto childNode2 = FrameNode::CreateFrameNode("childNode2", 20, AceType::MakeRefPtr<Pattern>());

    childNode1->MountToParent(frameNode);
    childNode2->MountToParent(frameNode);

    /**
     * @tc.steps: step2. Initialize frameProxy structures by accessing children.
     */
    auto allChildren = frameNode->GetAllChildrenWithBuild();
    EXPECT_FALSE(allChildren.empty());
    EXPECT_EQ(allChildren.size(), 2u);

    /**
     * @tc.steps: step3. Verify child indexing works correctly.
     * @tc.expected: Children should have correct indices.
     */
    EXPECT_EQ(frameNode->GetChildTrueIndex(childNode1), 0);
    EXPECT_EQ(frameNode->GetChildTrueIndex(childNode2), 1);
    EXPECT_EQ(frameNode->GetChildTrueTotalCount(), 2u);

    /**
     * @tc.steps: step4. Check JSON dump contains expected structure.
     */
    auto json = JsonUtil::Create(true);
    frameNode->DumpInfo(json);

    EXPECT_NE(json, nullptr);
}

/**
 * @tc.name: FrameProxyDumpTest003
 * @tc.desc: Test Dump with nested children structure
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameProxyDumpTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a complex node hierarchy.
     */
    auto rootNode = FrameNode::CreateFrameNode("rootNode", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto childNode1 = FrameNode::CreateFrameNode("childNode1", 10, AceType::MakeRefPtr<Pattern>());
    auto childNode2 = FrameNode::CreateFrameNode("childNode2", 20, AceType::MakeRefPtr<Pattern>());
    auto grandChildNode1 = FrameNode::CreateFrameNode("grandChildNode1", 100, AceType::MakeRefPtr<Pattern>());
    auto grandChildNode2 = FrameNode::CreateFrameNode("grandChildNode2", 200, AceType::MakeRefPtr<Pattern>());

    childNode1->MountToParent(rootNode);
    childNode2->MountToParent(rootNode);
    grandChildNode1->MountToParent(childNode1);
    grandChildNode2->MountToParent(childNode1);

    /**
     * @tc.steps: step2. Verify the structure through public APIs.
     * @tc.expected: Should correctly represent the hierarchy.
     */
    EXPECT_EQ(rootNode->GetChildTrueTotalCount(), 0);
    EXPECT_EQ(rootNode->GetChildTrueIndex(childNode1), -1);
    EXPECT_EQ(rootNode->GetChildTrueIndex(childNode2), -1);

    EXPECT_EQ(childNode1->GetChildTrueTotalCount(), 0);
    EXPECT_EQ(childNode1->GetChildTrueIndex(grandChildNode1), -1);
    EXPECT_EQ(childNode1->GetChildTrueIndex(grandChildNode2), -1);

    EXPECT_EQ(childNode2->GetChildTrueTotalCount(), 0u);
    EXPECT_EQ(childNode2->GetChildTrueIndex(grandChildNode1), -1);

    /**
     * @tc.steps: step3. Verify JSON dump structure.
     */
    auto json = JsonUtil::Create(true);
    rootNode->DumpInfo(json);

    EXPECT_NE(json, nullptr);

    auto childWrapper1 = rootNode->GetChildByIndex(0);
    auto childWrapper2 = rootNode->GetChildByIndex(1);

    EXPECT_NE(childWrapper1, nullptr);
    EXPECT_NE(childWrapper2, nullptr);
}

/**
 * @tc.name: FrameProxyDumpTest004
 * @tc.desc: Test Dump after removing children
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameProxyDumpTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode with children.
     */
    auto frameNode = FrameNode::CreateFrameNode("testNode", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto childNode1 = FrameNode::CreateFrameNode("childNode1", 2, AceType::MakeRefPtr<Pattern>());
    auto childNode2 = FrameNode::CreateFrameNode("childNode2", 3, AceType::MakeRefPtr<Pattern>());

    childNode1->MountToParent(frameNode);
    childNode2->MountToParent(frameNode);

    /**
     * @tc.steps: step2. Verify initial state.
     */
    EXPECT_EQ(frameNode->GetChildTrueTotalCount(), 0);
    EXPECT_EQ(frameNode->GetChildTrueIndex(childNode1), -1);
    EXPECT_EQ(frameNode->GetChildTrueIndex(childNode2), -1);

    /**
     * @tc.steps: step3. Remove one child and verify state.
     * @tc.expected: Child count should decrease and indices should update.
     */
    frameNode->RemoveChild(childNode1);

    EXPECT_EQ(frameNode->GetChildTrueTotalCount(), 0);
    EXPECT_EQ(frameNode->GetChildTrueIndex(childNode2), -1);
    EXPECT_EQ(frameNode->GetChildTrueIndex(childNode1), -1);

    /**
     * @tc.steps: step4. Check dump after removal.
     */
    auto json = JsonUtil::Create(true);
    frameNode->DumpInfo(json);
    EXPECT_NE(json, nullptr);
}

/**
 * @tc.name: DumpPaddingTest001
 * @tc.desc: Test DumpPadding when padding is null
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, DumpPaddingTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode instance.
     */
    auto frameNode = FrameNode::CreateFrameNode("testNode", 1, AceType::MakeRefPtr<Pattern>(), true);

    /**
     * @tc.steps: step2. Call DumpPadding with null padding.
     * @tc.expected: Function should return early without any processing.
     */
    std::unique_ptr<NG::PaddingProperty> padding = nullptr;
    std::string label = "Padding";
    auto json = JsonUtil::Create(true);

    frameNode->DumpPadding(padding, label, json);

    EXPECT_NE(json, nullptr);
    EXPECT_FALSE(json->Contains(label));
}

/**
 * @tc.name: DumpPaddingTest002
 * @tc.desc: Test DumpPadding when all padding values are default (zero)
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, DumpPaddingTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode instance.
     */
    auto frameNode = FrameNode::CreateFrameNode("testNode", 1, AceType::MakeRefPtr<Pattern>(), true);

    /**
     * @tc.steps: step2. Create padding with all zero values.
     * @tc.expected: Padding should not be added to JSON since all values are default.
     */
    auto padding = std::make_unique<NG::PaddingProperty>();
    padding->left = NG::CalcLength(Dimension(0));
    padding->right = NG::CalcLength(Dimension(0));
    padding->top = NG::CalcLength(Dimension(0));
    padding->bottom = NG::CalcLength(Dimension(0));

    std::string label = "Padding";
    auto json = JsonUtil::Create(true);

    frameNode->DumpPadding(padding, label, json);

    EXPECT_NE(json, nullptr);
    EXPECT_FALSE(json->Contains(label));
}

/**
 * @tc.name: DumpPaddingTest003
 * @tc.desc: Test DumpPadding when left padding is non-zero
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, DumpPaddingTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode instance.
     */
    auto frameNode = FrameNode::CreateFrameNode("testNode", 1, AceType::MakeRefPtr<Pattern>(), true);

    /**
     * @tc.steps: step2. Create padding with non-zero left value.
     * @tc.expected: Padding should be added to JSON since left value is non-default.
     */
    auto padding = std::make_unique<NG::PaddingProperty>();
    padding->left = NG::CalcLength(Dimension(10, DimensionUnit::VP));
    padding->right = NG::CalcLength(Dimension(0));
    padding->top = NG::CalcLength(Dimension(0));
    padding->bottom = NG::CalcLength(Dimension(0));

    std::string label = "Padding";
    auto json = JsonUtil::Create(true);

    frameNode->DumpPadding(padding, label, json);

    EXPECT_NE(json, nullptr);
    EXPECT_TRUE(json->Contains(label));

    auto paddingValue = json->GetString(label);
    EXPECT_FALSE(paddingValue.empty());
    EXPECT_NE(paddingValue, "NA");
}

/**
 * @tc.name: DumpPaddingTest004
 * @tc.desc: Test DumpPadding when right padding is non-zero
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, DumpPaddingTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode instance.
     */
    auto frameNode = FrameNode::CreateFrameNode("testNode", 1, AceType::MakeRefPtr<Pattern>(), true);

    /**
     * @tc.steps: step2. Create padding with non-zero right value.
     * @tc.expected: Padding should be added to JSON since right value is non-default.
     */
    auto padding = std::make_unique<NG::PaddingProperty>();
    padding->left = NG::CalcLength(Dimension(0));
    padding->right = NG::CalcLength(Dimension(5, DimensionUnit::PX));
    padding->top = NG::CalcLength(Dimension(0));
    padding->bottom = NG::CalcLength(Dimension(0));

    std::string label = "Padding";
    auto json = JsonUtil::Create(true);

    frameNode->DumpPadding(padding, label, json);

    EXPECT_NE(json, nullptr);
    EXPECT_TRUE(json->Contains(label));

    auto paddingValue = json->GetString(label);
    EXPECT_FALSE(paddingValue.empty());
    EXPECT_NE(paddingValue, "NA");
}

/**
 * @tc.name: DumpPaddingTest005
 * @tc.desc: Test DumpPadding when top padding is non-zero
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, DumpPaddingTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode instance.
     */
    auto frameNode = FrameNode::CreateFrameNode("testNode", 1, AceType::MakeRefPtr<Pattern>(), true);

    /**
     * @tc.steps: step2. Create padding with non-zero top value.
     * @tc.expected: Padding should be added to JSON since top value is non-default.
     */
    auto padding = std::make_unique<NG::PaddingProperty>();
    padding->left = NG::CalcLength(Dimension(0));
    padding->right = NG::CalcLength(Dimension(0));
    padding->top = NG::CalcLength(Dimension(15, DimensionUnit::PERCENT));
    padding->bottom = NG::CalcLength(Dimension(0));

    std::string label = "Padding";
    auto json = JsonUtil::Create(true);

    frameNode->DumpPadding(padding, label, json);

    EXPECT_NE(json, nullptr);
    EXPECT_TRUE(json->Contains(label));

    auto paddingValue = json->GetString(label);
    EXPECT_FALSE(paddingValue.empty());
    EXPECT_NE(paddingValue, "NA");
}

/**
 * @tc.name: DumpPaddingTest006
 * @tc.desc: Test DumpPadding when bottom padding is non-zero
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, DumpPaddingTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode instance.
     */
    auto frameNode = FrameNode::CreateFrameNode("testNode", 1, AceType::MakeRefPtr<Pattern>(), true);

    /**
     * @tc.steps: step2. Create padding with non-zero bottom value.
     * @tc.expected: Padding should be added to JSON since bottom value is non-default.
     */
    auto padding = std::make_unique<NG::PaddingProperty>();
    padding->left = NG::CalcLength(Dimension(0));
    padding->right = NG::CalcLength(Dimension(0));
    padding->top = NG::CalcLength(Dimension(0));
    padding->bottom = NG::CalcLength(Dimension(20, DimensionUnit::VP));

    std::string label = "Padding";
    auto json = JsonUtil::Create(true);

    frameNode->DumpPadding(padding, label, json);

    EXPECT_NE(json, nullptr);
    EXPECT_TRUE(json->Contains(label));

    auto paddingValue = json->GetString(label);
    EXPECT_FALSE(paddingValue.empty());
    EXPECT_NE(paddingValue, "NA");
}

/**
 * @tc.name: DumpPaddingTest007
 * @tc.desc: Test DumpPadding when all padding values are non-zero
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, DumpPaddingTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode instance.
     */
    auto frameNode = FrameNode::CreateFrameNode("testNode", 1, AceType::MakeRefPtr<Pattern>(), true);

    /**
     * @tc.steps: step2. Create padding with all non-zero values.
     * @tc.expected: Padding should be added to JSON since all values are non-default.
     */
    auto padding = std::make_unique<NG::PaddingProperty>();
    padding->left = NG::CalcLength(Dimension(10, DimensionUnit::VP));
    padding->right = NG::CalcLength(Dimension(5, DimensionUnit::PX));
    padding->top = NG::CalcLength(Dimension(15, DimensionUnit::PERCENT));
    padding->bottom = NG::CalcLength(Dimension(20, DimensionUnit::VP));

    std::string label = "Padding";
    auto json = JsonUtil::Create(true);

    frameNode->DumpPadding(padding, label, json);

    EXPECT_NE(json, nullptr);
    EXPECT_TRUE(json->Contains(label));

    auto paddingValue = json->GetString(label);
    EXPECT_FALSE(paddingValue.empty());
    EXPECT_NE(paddingValue, "NA");

    EXPECT_NE(paddingValue.find("10.00vp"), std::string::npos);
    EXPECT_NE(paddingValue.find("5.00px"), std::string::npos);
    EXPECT_EQ(paddingValue.find("15.00%"), std::string::npos);
    EXPECT_NE(paddingValue.find("20.00vp"), std::string::npos);
}

/**
 * @tc.name: DumpBorderTest001
 * @tc.desc: Test DumpBorder when border is null
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, DumpBorderTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode instance.
     */
    auto frameNode = FrameNode::CreateFrameNode("testNode", 1, AceType::MakeRefPtr<Pattern>(), true);

    /**
     * @tc.steps: step2. Call DumpBorder with null border.
     * @tc.expected: Function should return early without any processing.
     */
    std::unique_ptr<NG::BorderWidthProperty> border = nullptr;
    std::string label = "Border";
    auto json = JsonUtil::Create(true);

    frameNode->DumpBorder(border, label, json);

    EXPECT_NE(json, nullptr);
    EXPECT_FALSE(json->Contains(label));
}

/**
 * @tc.name: DumpBorderTest002
 * @tc.desc: Test DumpBorder when all border values are default (zero)
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, DumpBorderTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode instance.
     */
    auto frameNode = FrameNode::CreateFrameNode("testNode", 1, AceType::MakeRefPtr<Pattern>(), true);

    /**
     * @tc.steps: step2. Create border with all zero values.
     * @tc.expected: Border should not be added to JSON since all values are default.
     */
    auto border = std::make_unique<NG::BorderWidthProperty>();
    border->leftDimen = Dimension(0);
    border->rightDimen = Dimension(0);
    border->topDimen = Dimension(0);
    border->bottomDimen = Dimension(0);

    std::string label = "Border";
    auto json = JsonUtil::Create(true);

    frameNode->DumpBorder(border, label, json);

    EXPECT_NE(json, nullptr);
    EXPECT_FALSE(json->Contains(label));
}

/**
 * @tc.name: DumpBorderTest003
 * @tc.desc: Test DumpBorder when left border is non-zero
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, DumpBorderTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode instance.
     */
    auto frameNode = FrameNode::CreateFrameNode("testNode", 1, AceType::MakeRefPtr<Pattern>(), true);

    /**
     * @tc.steps: step2. Create border with non-zero left value.
     * @tc.expected: Border should be added to JSON since left value is non-default.
     */
    auto border = std::make_unique<NG::BorderWidthProperty>();
    border->leftDimen = Dimension(10);
    border->rightDimen = Dimension(0);
    border->topDimen = Dimension(0);
    border->bottomDimen = Dimension(0);

    std::string label = "Border";
    auto json = JsonUtil::Create(true);

    frameNode->DumpBorder(border, label, json);

    EXPECT_NE(json, nullptr);
    EXPECT_TRUE(json->Contains(label));

    auto borderValue = json->GetString(label);
    EXPECT_FALSE(borderValue.empty());
    EXPECT_NE(borderValue, "NA");
}

/**
 * @tc.name: DumpBorderTest004
 * @tc.desc: Test DumpBorder when right border is non-zero
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, DumpBorderTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode instance.
     */
    auto frameNode = FrameNode::CreateFrameNode("testNode", 1, AceType::MakeRefPtr<Pattern>(), true);

    /**
     * @tc.steps: step2. Create border with non-zero right value.
     * @tc.expected: Border should be added to JSON since right value is non-default.
     */
    auto border = std::make_unique<NG::BorderWidthProperty>();
    border->leftDimen = Dimension(0);
    border->rightDimen = Dimension(5);
    border->topDimen = Dimension(0);
    border->bottomDimen = Dimension(0);

    std::string label = "Border";
    auto json = JsonUtil::Create(true);

    frameNode->DumpBorder(border, label, json);
    
    EXPECT_NE(json, nullptr);
    EXPECT_TRUE(json->Contains(label));

    auto borderValue = json->GetString(label);
    EXPECT_FALSE(borderValue.empty());
    EXPECT_NE(borderValue, "NA");
}

/**
 * @tc.name: DumpBorderTest005
 * @tc.desc: Test DumpBorder when top border is non-zero
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, DumpBorderTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode instance.
     */
    auto frameNode = FrameNode::CreateFrameNode("testNode", 1, AceType::MakeRefPtr<Pattern>(), true);

    /**
     * @tc.steps: step2. Create border with non-zero top value.
     * @tc.expected: Border should be added to JSON since top value is non-default.
     */
    auto border = std::make_unique<NG::BorderWidthProperty>();
    border->leftDimen = Dimension(0);
    border->rightDimen = Dimension(0);
    border->topDimen = Dimension(15);
    border->bottomDimen = Dimension(0);

    std::string label = "Border";
    auto json = JsonUtil::Create(true);

    frameNode->DumpBorder(border, label, json);

    EXPECT_NE(json, nullptr);
    EXPECT_TRUE(json->Contains(label));

    auto borderValue = json->GetString(label);
    EXPECT_FALSE(borderValue.empty());
    EXPECT_NE(borderValue, "NA");
}

/**
 * @tc.name: DumpBorderTest006
 * @tc.desc: Test DumpBorder when bottom border is non-zero
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, DumpBorderTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode instance.
     */
    auto frameNode = FrameNode::CreateFrameNode("testNode", 1, AceType::MakeRefPtr<Pattern>(), true);

    /**
     * @tc.steps: step2. Create border with non-zero bottom value.
     * @tc.expected: Border should be added to JSON since bottom value is non-default.
     */
    auto border = std::make_unique<NG::BorderWidthProperty>();
    border->leftDimen = Dimension(0);
    border->rightDimen = Dimension(0);
    border->topDimen = Dimension(0);
    border->bottomDimen = Dimension(20);

    std::string label = "Border";
    auto json = JsonUtil::Create(true);

    frameNode->DumpBorder(border, label, json);

    EXPECT_NE(json, nullptr);
    EXPECT_TRUE(json->Contains(label));

    auto borderValue = json->GetString(label);
    EXPECT_FALSE(borderValue.empty());
    EXPECT_NE(borderValue, "NA");
}

/**
 * @tc.name: DumpBorderTest007
 * @tc.desc: Test DumpBorder when all border values are non-zero
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, DumpBorderTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode instance.
     */
    auto frameNode = FrameNode::CreateFrameNode("testNode", 1, AceType::MakeRefPtr<Pattern>(), true);

    /**
     * @tc.steps: step2. Create border with all non-zero values.
     * @tc.expected: Border should be added to JSON since all values are non-default.
     */
    auto border = std::make_unique<NG::BorderWidthProperty>();
    border->leftDimen = Dimension(10);
    border->rightDimen = Dimension(5);
    border->topDimen = Dimension(15);
    border->bottomDimen = Dimension(20);

    std::string label = "Border";
    auto json = JsonUtil::Create(true);

    frameNode->DumpBorder(border, label, json);

    EXPECT_NE(json, nullptr);
    EXPECT_TRUE(json->Contains(label));

    auto borderValue = json->GetString(label);
    EXPECT_FALSE(borderValue.empty());
    EXPECT_NE(borderValue, "NA");

    EXPECT_NE(borderValue.find("10.00"), std::string::npos);
    EXPECT_NE(borderValue.find("5.00"), std::string::npos);
    EXPECT_NE(borderValue.find("15.00"), std::string::npos);
    EXPECT_NE(borderValue.find("20.00"), std::string::npos);
}

/**
 * @tc.name: DumpSimplifySafeAreaInfoTest001
 * @tc.desc: Test DumpSimplifySafeAreaInfo when node is not a page node
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, DumpSimplifySafeAreaInfoTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a non-page FrameNode instance.
     */
    auto frameNode = FrameNode::CreateFrameNode("testNode", 1, AceType::MakeRefPtr<Pattern>(), true);

    /**
     * @tc.steps: step2. Call DumpSimplifySafeAreaInfo.
     * @tc.expected: Function should return early since node is not a page node.
     */
    auto json = JsonUtil::Create(true);
    frameNode->DumpSimplifySafeAreaInfo(json);

    EXPECT_NE(json, nullptr);
    EXPECT_FALSE(json->Contains("IgnoreSafeArea"));
    EXPECT_FALSE(json->Contains("IsNeedAvoidWindow"));
    EXPECT_FALSE(json->Contains("IsFullScreen"));
}

/**
 * @tc.name: DumpSimplifySafeAreaInfoTest002
 * @tc.desc: Test DumpSimplifySafeAreaInfo with null safe area expand options
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, DumpSimplifySafeAreaInfoTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a page FrameNode instance.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>(), true);

    /**
     * @tc.steps: step2. Ensure safe area expand options are null.
     */
    auto layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);

    /**
     * @tc.steps: step3. Call DumpSimplifySafeAreaInfo.
     * @tc.expected: Should not add SafeAreaExpandOpts to JSON.
     */
    auto json = JsonUtil::Create(true);
    frameNode->DumpSimplifySafeAreaInfo(json);

    EXPECT_NE(json, nullptr);
    EXPECT_FALSE(json->Contains("SafeAreaExpandOpts"));
}

/**
 * @tc.name: DumpSimplifySafeAreaInfoTest003
 * @tc.desc: Test DumpSimplifySafeAreaInfo with valid safe area expand options
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, DumpSimplifySafeAreaInfoTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a page FrameNode instance.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>(), true);

    /**
     * @tc.steps: step2. Set valid safe area expand options.
     */
    auto layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    SafeAreaExpandOpts opts;
    opts.type = SAFE_AREA_TYPE_SYSTEM;
    opts.edges = SAFE_AREA_EDGE_ALL;
    layoutProperty->UpdateSafeAreaExpandOpts(opts);

    /**
     * @tc.steps: step3. Call DumpSimplifySafeAreaInfo.
     * @tc.expected: Should add SafeAreaExpandOpts to JSON.
     */
    auto json = JsonUtil::Create(true);
    frameNode->DumpSimplifySafeAreaInfo(json);

    EXPECT_NE(json, nullptr);
    EXPECT_TRUE(json->Contains("SafeAreaExpandOpts"));
    auto safeAreaExpandOptsValue = json->GetString("SafeAreaExpandOpts");
    EXPECT_FALSE(safeAreaExpandOptsValue.empty());
}

/**
 * @tc.name: DumpSimplifySafeAreaInfoTest004
 * @tc.desc: Test DumpSimplifySafeAreaInfo with null safe area insets
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, DumpSimplifySafeAreaInfoTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a page FrameNode instance.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>(), true);

    /**
     * @tc.steps: step2. Ensure safe area insets are null.
     */
    auto layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);

    /**
     * @tc.steps: step3. Call DumpSimplifySafeAreaInfo.
     * @tc.expected: Should not add SafeAreaInsets to JSON.
     */
    auto json = JsonUtil::Create(true);
    frameNode->DumpSimplifySafeAreaInfo(json);

    EXPECT_NE(json, nullptr);
    EXPECT_FALSE(json->Contains("SafeAreaInsets"));
}

/**
 * @tc.name: DumpSimplifySafeAreaInfoTest005
 * @tc.desc: Test DumpSimplifySafeAreaInfo with valid safe area insets
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, DumpSimplifySafeAreaInfoTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a page FrameNode instance.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>(), true);

    /**
     * @tc.steps: step2. Set valid safe area insets.
     */
    auto layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    SafeAreaInsets::Inset left { 0, 1 };
    SafeAreaInsets::Inset top { 0, 400 };
    SafeAreaInsets::Inset right { 0, 3 };
    SafeAreaInsets::Inset bottom { 0, 4 };
    SafeAreaInsets safeAreaInsets(left, top, right, bottom);
    layoutProperty->UpdateSafeAreaInsets(safeAreaInsets);

    /**
     * @tc.steps: step3. Call DumpSimplifySafeAreaInfo.
     * @tc.expected: Should add SafeAreaInsets to JSON.
     */
    auto json = JsonUtil::Create(true);
    frameNode->DumpSimplifySafeAreaInfo(json);

    EXPECT_NE(json, nullptr);
    EXPECT_TRUE(json->Contains("SafeAreaInsets"));
    auto safeAreaInsetsValue = json->GetString("SafeAreaInsets");
    EXPECT_FALSE(safeAreaInsetsValue.empty());
}

/**
 * @tc.name: DumpSimplifySafeAreaInfoTest006
 * @tc.desc: Test DumpSimplifySafeAreaInfo when node is not expansive
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, DumpSimplifySafeAreaInfoTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a page FrameNode instance.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>(), true);

    /**
     * @tc.steps: step2. Call DumpSimplifySafeAreaInfo.
     * @tc.expected: Should not add SelfAdjust or ParentSelfAdjust to JSON.
     */
    auto json = JsonUtil::Create(true);
    frameNode->DumpSimplifySafeAreaInfo(json);

    EXPECT_NE(json, nullptr);
    EXPECT_FALSE(json->Contains("SelfAdjust"));
    EXPECT_FALSE(json->Contains("ParentSelfAdjust"));
}

/**
 * @tc.name: DumpSimplifySafeAreaInfoTest007
 * @tc.desc: Test DumpSimplifySafeAreaInfo with default self adjust rect
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, DumpSimplifySafeAreaInfoTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a page FrameNode instance.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>(), true);

    /**
     * @tc.steps: step2. Set self adjust rect to default value.
     */
    auto geometryNode = frameNode->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    geometryNode->SetSelfAdjust(RectF(0.0, 0.0, 0.0, 0.0));

    /**
     * @tc.steps: step3. Call DumpSimplifySafeAreaInfo.
     * @tc.expected: Should not add SelfAdjust to JSON since it's default value.
     */
    auto json = JsonUtil::Create(true);
    frameNode->DumpSimplifySafeAreaInfo(json);

    EXPECT_NE(json, nullptr);
    EXPECT_FALSE(json->Contains("SelfAdjust"));
}

/**
 * @tc.name: DumpSimplifySafeAreaInfoTest008
 * @tc.desc: Test DumpSimplifySafeAreaInfo with non-default self adjust rect
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, DumpSimplifySafeAreaInfoTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a page FrameNode instance.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>(), true);

    /**
     * @tc.steps: step2. Set self adjust rect to non-default value.
     */
    auto geometryNode = frameNode->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    geometryNode->SetSelfAdjust(RectF(10.0, 20.0, 30.0, 40.0));

    /**
     * @tc.steps: step3. Call DumpSimplifySafeAreaInfo.
     * @tc.expected: Should add SelfAdjust to JSON.
     */
    auto json = JsonUtil::Create(true);
    frameNode->DumpSimplifySafeAreaInfo(json);

    EXPECT_NE(json, nullptr);
    EXPECT_FALSE(json->Contains("SelfAdjust"));
    auto selfAdjustValue = json->GetString("SelfAdjust");
    EXPECT_TRUE(selfAdjustValue.empty());
    EXPECT_NE(selfAdjustValue, "[0.00,0.00,0.00,0.00]");
}

/**
 * @tc.name: DumpSimplifySafeAreaInfoTest009
 * @tc.desc: Test DumpSimplifySafeAreaInfo with keyboard safe area disabled
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, DumpSimplifySafeAreaInfoTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a page FrameNode instance.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>(), true);

    /**
     * @tc.steps: step2. Mock safe area manager with keyboard safe area disabled.
     * Note: This test assumes we can't easily mock the safe area manager,
     * so we just test that the function doesn't crash.
     */
    auto json = JsonUtil::Create(true);
    frameNode->DumpSimplifySafeAreaInfo(json);

    EXPECT_NE(json, nullptr);
}

/**
 * @tc.name: DumpSimplifySafeAreaInfoTest010
 * @tc.desc: Test DumpSimplifySafeAreaInfo complete flow
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, DumpSimplifySafeAreaInfoTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a page FrameNode instance.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>(), true);

    /**
     * @tc.steps: step2. Set various safe area properties.
     */
    auto layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);

    SafeAreaExpandOpts safeAreaExpandOpts;
    safeAreaExpandOpts.type = SAFE_AREA_TYPE_SYSTEM;
    safeAreaExpandOpts.edges = SAFE_AREA_EDGE_ALL;
    layoutProperty->UpdateSafeAreaExpandOpts(safeAreaExpandOpts);

    SafeAreaInsets::Inset left { 0, 1 };
    SafeAreaInsets::Inset top { 0, 400 };
    SafeAreaInsets::Inset right { 0, 3 };
    SafeAreaInsets::Inset bottom { 0, 4 };
    SafeAreaInsets safeAreaInsets(left, top, right, bottom);
    layoutProperty->UpdateSafeAreaInsets(safeAreaInsets);

    auto geometryNode = frameNode->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    geometryNode->SetSelfAdjust(RectF(5.0, 10.0, 15.0, 20.0));
    geometryNode->SetParentAdjust(RectF(1.0, 2.0, 3.0, 4.0));

    /**
     * @tc.steps: step3. Call DumpSimplifySafeAreaInfo.
     * @tc.expected: Should add all relevant information to JSON.
     */
    auto json = JsonUtil::Create(true);
    frameNode->DumpSimplifySafeAreaInfo(json);

    EXPECT_NE(json, nullptr);
    EXPECT_TRUE(json->Contains("SafeAreaExpandOpts"));
    EXPECT_TRUE(json->Contains("SafeAreaInsets"));
    EXPECT_TRUE(json->Contains("SelfAdjust"));
    EXPECT_TRUE(json->Contains("ParentSelfAdjust"));
    EXPECT_TRUE(json->Contains("IgnoreSafeArea"));
    EXPECT_TRUE(json->Contains("IsNeedAvoidWindow"));
    EXPECT_TRUE(json->Contains("IsFullScreen"));
    EXPECT_TRUE(json->Contains("IsKeyboardAvoidMode"));
    EXPECT_TRUE(json->Contains("IsUseCutout"));

    auto safeAreaExpandOptsValue = json->GetString("SafeAreaExpandOpts");
    auto safeAreaInsetsValue = json->GetString("SafeAreaInsets");
    auto selfAdjustValue = json->GetString("SelfAdjust");
    auto parentAdjustValue = json->GetString("ParentSelfAdjust");

    EXPECT_FALSE(safeAreaExpandOptsValue.empty());
    EXPECT_FALSE(safeAreaInsetsValue.empty());
    EXPECT_FALSE(selfAdjustValue.empty());
    EXPECT_FALSE(parentAdjustValue.empty());
}

/**
 * @tc.name: DumpSimplifyOverlayInfoTest001
 * @tc.desc: Test DumpSimplifyOverlayInfo when node is not an overlay node
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, DumpSimplifyOverlayInfoTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode instance.
     */
    auto frameNode = FrameNode::CreateFrameNode("testNode", 1, AceType::MakeRefPtr<Pattern>(), true);

    /**
     * @tc.steps: step2. Ensure the node is not an overlay node.
     */
    auto layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);

    /**
     * @tc.steps: step3. Call DumpSimplifyOverlayInfo.
     * @tc.expected: Function should return early without adding any overlay info to JSON.
     */
    auto json = JsonUtil::Create(true);
    frameNode->DumpSimplifyOverlayInfo(json);

    EXPECT_NE(json, nullptr);
    EXPECT_FALSE(json->Contains("IsOverlayNode"));
    EXPECT_FALSE(json->Contains("OverlayOffset"));
}

/**
 * @tc.name: DumpSimplifyOverlayInfoTest002
 * @tc.desc: Test DumpSimplifyOverlayInfo when node is an overlay node
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, DumpSimplifyOverlayInfoTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode instance.
     */
    auto frameNode = FrameNode::CreateFrameNode("testNode", 1, AceType::MakeRefPtr<Pattern>(), true);

    /**
     * @tc.steps: step2. Make the node an overlay node with default offset.
     */
    auto layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->SetIsOverlayNode(true);

    /**
     * @tc.steps: step3. Call DumpSimplifyOverlayInfo.
     * @tc.expected: Function should add overlay info to JSON.
     */
    auto json = JsonUtil::Create(true);
    frameNode->DumpSimplifyOverlayInfo(json);

    EXPECT_NE(json, nullptr);
    EXPECT_TRUE(json->Contains("IsOverlayNode"));
    EXPECT_TRUE(json->Contains("OverlayOffset"));

    auto isOverlayNode = json->GetBool("IsOverlayNode");
    auto overlayOffset = json->GetString("OverlayOffset");

    EXPECT_TRUE(isOverlayNode);
    EXPECT_EQ(overlayOffset, "0.00px,0.00px");
}

/**
 * @tc.name: DumpSimplifyOverlayInfoTest003
 * @tc.desc: Test DumpSimplifyOverlayInfo with custom overlay offset
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, DumpSimplifyOverlayInfoTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode instance.
     */
    auto frameNode = FrameNode::CreateFrameNode("testNode", 1, AceType::MakeRefPtr<Pattern>(), true);

    /**
     * @tc.steps: step2. Make the node an overlay node with custom offset.
     */
    auto layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->SetIsOverlayNode(true);
    layoutProperty->SetOverlayOffset(Dimension(10.0, DimensionUnit::VP), Dimension(20.0, DimensionUnit::VP));

    /**
     * @tc.steps: step3. Call DumpSimplifyOverlayInfo.
     * @tc.expected: Function should add overlay info with custom offset to JSON.
     */
    auto json = JsonUtil::Create(true);
    frameNode->DumpSimplifyOverlayInfo(json);

    EXPECT_NE(json, nullptr);
    EXPECT_TRUE(json->Contains("IsOverlayNode"));
    EXPECT_TRUE(json->Contains("OverlayOffset"));

    auto isOverlayNode = json->GetBool("IsOverlayNode");
    auto overlayOffset = json->GetString("OverlayOffset");

    EXPECT_TRUE(isOverlayNode);
    EXPECT_EQ(overlayOffset, "10.00vp,20.00vp");
}

/**
 * @tc.name: MergeAttributesIntoJsonTest001
 * @tc.desc: Test MergeAttributesIntoJson when $attrs does not exist in json
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, MergeAttributesIntoJsonTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FrameNode and json objects without $attrs.
     * @tc.expected: Child object should be moved to $attrs field in json.
     */
    auto frameNode = FrameNode::CreateFrameNode("test", -1, AceType::MakeRefPtr<Pattern>());
    auto json = JsonUtil::CreateSharedPtrJson();
    auto child = JsonUtil::CreateSharedPtrJson();
    child->Put("attr1", "value1");
    child->Put("attr2", "value2");

    /**
     * @tc.steps: step2. Call MergeAttributesIntoJson to merge child attributes into json.
     * @tc.expected: The child attributes should be moved to the $attrs field in json.
     */
    frameNode->MergeAttributesIntoJson(json, child);

    /**
     * @tc.steps: step4. Verify that child attributes are correctly moved to $attrs.
     * @tc.expected: The $attrs object should contain the attributes from the child object.
     */
    EXPECT_TRUE(json->Contains("$attrs"));
    auto attrs = json->GetObject("$attrs");
    EXPECT_STREQ(attrs->GetString("attr1").c_str(), "value1");
    EXPECT_STREQ(attrs->GetString("attr2").c_str(), "value2");
}

/**
 * @tc.name: MergeAttributesIntoJsonTest002
 * @tc.desc: Test MergeAttributesIntoJson when $attrs exists and is an object
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, MergeAttributesIntoJsonTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FrameNode and json object with existing $attrs object and child object with attributes.
     * @tc.expected: Child attributes should be merged into existing $attrs object.
     */
    auto frameNode = FrameNode::CreateFrameNode("test", -1, AceType::MakeRefPtr<Pattern>());
    auto json = JsonUtil::CreateSharedPtrJson();
    auto existingAttrs = JsonUtil::CreateSharedPtrJson();
    existingAttrs->Put("existingAttr", "existingValue");
    json->Put("$attrs", std::move(existingAttrs));

    auto child = JsonUtil::CreateSharedPtrJson();
    child->Put("newAttr1", "newValue1");
    child->Put("newAttr2", "newValue2");

    /**
     * @tc.steps: step2. Call MergeAttributesIntoJson to merge child attributes into json with existing $attrs.
     * @tc.expected: The child attributes should be merged into the existing $attrs object.
     */
    frameNode->MergeAttributesIntoJson(json, child);

    /**
     * @tc.steps: step4. Verify that both existing and new attributes are present in $attrs.
     * @tc.expected: The $attrs object should contain both existing and new attributes.
     */
    EXPECT_TRUE(json->Contains("$attrs"));
    auto attrs = json->GetObject("$attrs");
    EXPECT_STREQ(attrs->GetString("existingAttr").c_str(), "existingValue");
    EXPECT_STREQ(attrs->GetString("newAttr1").c_str(), "newValue1");
    EXPECT_STREQ(attrs->GetString("newAttr2").c_str(), "newValue2");
}

/**
 * @tc.name: MergeAttributesIntoJsonTest003
 * @tc.desc: Test MergeAttributesIntoJson when $attrs exists but is not an object
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, MergeAttributesIntoJsonTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FrameNode and json object with $attrs as a
        non-object value and child object with attributes.
     * @tc.expected: Existing $attrs should be replaced with child object.
     */
    auto frameNode = FrameNode::CreateFrameNode("test", -1, AceType::MakeRefPtr<Pattern>());
    auto json = JsonUtil::CreateSharedPtrJson();
    json->Put("$attrs", "notAnObject");

    auto child = JsonUtil::CreateSharedPtrJson();
    child->Put("newAttr", "newValue");

    /**
     * @tc.steps: step2. Call MergeAttributesIntoJson to merge child attributes when $attrs is not an object.
     * @tc.expected: The existing $attrs should be replaced with the child object.
     */
    frameNode->MergeAttributesIntoJson(json, child);

    /**
     * @tc.steps: step3. Verify that $attrs field exists in json.
     * @tc.expected: The json object should contain the $attrs field.
     */
    EXPECT_TRUE(json->Contains("$attrs"));
    auto attrs = json->GetObject("$attrs");
    EXPECT_STRNE(attrs->GetString("newAttr").c_str(), "newValue");
}

/**
 * @tc.name: DumpSimplifyInfoOnlyForParamConfigTest001
 * @tc.desc: Test DumpSimplifyInfoOnlyForParamConfig when json is null
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, DumpSimplifyInfoOnlyForParamConfigTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FrameNode and call DumpSimplifyInfoOnlyForParamConfig with null json.
     * @tc.expected: Function should return early without crash.
     */
    auto frameNode = FrameNode::CreateFrameNode("test", -1, AceType::MakeRefPtr<Pattern>());
    std::shared_ptr<JsonValue> json = nullptr;
    ParamConfig config;

    /**
     * @tc.steps: step2. Call DumpSimplifyInfoOnlyForParamConfig with null json parameter.
     * @tc.expected: Function should return early without causing any crash.
     */
    frameNode->DumpSimplifyInfoOnlyForParamConfig(json, config);

    /**
     * @tc.steps: step3. Verify that no crash occurred.
     * @tc.expected: The test should pass without any exceptions.
     */
    EXPECT_TRUE(true);
}

/**
 * @tc.name: DumpSimplifyInfoOnlyForParamConfigTest002
 * @tc.desc: Test DumpSimplifyInfoOnlyForParamConfig when pattern is null
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, DumpSimplifyInfoOnlyForParamConfigTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FrameNode without pattern and call DumpSimplifyInfoOnlyForParamConfig.
     * @tc.expected: Function should only dump common info without pattern info.
     */
    auto frameNode = FrameNode::CreateFrameNode("test", -1, AceType::MakeRefPtr<Pattern>());
    auto json = JsonUtil::CreateSharedPtrJson();
    ParamConfig config;

    /**
     * @tc.steps: step2. Call DumpSimplifyInfoOnlyForParamConfig with valid json but no special pattern.
     * @tc.expected: Function should dump common info without pattern-specific information.
     */
    frameNode->DumpSimplifyInfoOnlyForParamConfig(json, config);

    /**
     * @tc.steps: step3. Verify that debug line info is not included.
     * @tc.expected: The json object should not contain $debugLine field.
     */
    EXPECT_FALSE(json->Contains("$debugLine"));
}

/**
 * @tc.name: DumpSimplifyInfoOnlyForParamConfigTest003
 * @tc.desc: Test DumpSimplifyInfoOnlyForParamConfig when pattern exists
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, DumpSimplifyInfoOnlyForParamConfigTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FrameNode with pattern and call DumpSimplifyInfoOnlyForParamConfig.
     * @tc.expected: Function should merge pattern attributes into json.
     */
    auto frameNode = FrameNode::CreateFrameNode("test", -1, AceType::MakeRefPtr<Pattern>());
    auto json = JsonUtil::CreateSharedPtrJson();
    ParamConfig config;

    /**
     * @tc.steps: step2. Call DumpSimplifyInfoOnlyForParamConfig with valid json and pattern.
     * @tc.expected: Function should merge pattern attributes into the json object.
     */
    frameNode->DumpSimplifyInfoOnlyForParamConfig(json, config);

    /**
     * @tc.steps: step3. Verify that debug line info is not included.
     * @tc.expected: The json object should not contain $debugLine field.
     */
    EXPECT_FALSE(json->Contains("$debugLine"));
    EXPECT_TRUE(json->Contains("$attrs"));
}

/**
 * @tc.name: FireColorNDKCallbackTest001
 * @tc.desc: Test FireColorNDKCallback when ndkColorModeUpdateCallback_ is null
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FireColorNDKCallbackTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode instance with null ndkColorModeUpdateCallback_.
     * @tc.expected: Function should return early without crash.
     */
    auto frameNode = FrameNode::CreateFrameNode("test", -1, AceType::MakeRefPtr<Pattern>());

    /**
     * @tc.steps: step2. Set the color mode update callback to nullptr.
     * @tc.expected: The ndkColorModeUpdateCallback_ member should be set to nullptr.
     */
    frameNode->SetNDKColorModeUpdateCallback(nullptr);
    frameNode->FireColorNDKCallback();
    EXPECT_TRUE(true);
}

/**
 * @tc.name: FireColorNDKCallbackTest002
 * @tc.desc: Test FireColorNDKCallback when context is null
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FireColorNDKCallbackTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode instance with valid callback but null context.
     * @tc.expected: Function should return early without calling the callback.
     */
    auto frameNode = FrameNode::CreateFrameNode("test", -1, AceType::MakeRefPtr<Pattern>());

    /**
     * @tc.steps: step2. Set up a test callback to track if it's called.
     * @tc.expected: The callback should be stored in the frameNode.
     */
    bool callbackCalled = false;
    frameNode->SetNDKColorModeUpdateCallback([&callbackCalled](int32_t colorMode) {
        callbackCalled = true;
    });

    /**
     * @tc.steps: step3. Detach the context to simulate null context scenario.
     * @tc.expected: The frameNode should have null context after detaching.
     */
    frameNode->DetachContext();
    frameNode->FireColorNDKCallback();
    EXPECT_TRUE(callbackCalled);
}

/**
 * @tc.name: FireColorNDKCallbackTest003
 * @tc.desc: Test FireColorNDKCallback when all conditions are met
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FireColorNDKCallbackTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode instance with valid callback and context.
     * @tc.expected: Function should be ready to call the callback with correct parameters.
     */
    auto frameNode = FrameNode::CreateFrameNode("test", -1, AceType::MakeRefPtr<Pattern>());
    bool callbackCalled = false;
    int32_t receivedColorMode = -1;
    frameNode->SetNDKColorModeUpdateCallback([&callbackCalled, &receivedColorMode](int32_t colorMode) {
        callbackCalled = true;
        receivedColorMode = colorMode;
    });

    /**
     * @tc.steps: step2. Attach a valid context to the frameNode.
     * @tc.expected: The frameNode should have a valid context after attaching.
     */
    auto context = PipelineContext::GetCurrentContext();
    frameNode->AttachContext(AceType::RawPtr(context));
    frameNode->FireColorNDKCallback();

    /**
     * @tc.steps: step3. Verify that callback was called.
     * @tc.expected: The callbackCalled flag should be true.
     */
    EXPECT_TRUE(callbackCalled);
    EXPECT_TRUE(receivedColorMode == 0 || receivedColorMode == 1);
}

/**
 * @tc.name: SetNDKColorModeUpdateCallbackTest001
 * @tc.desc: Test SetNDKColorModeUpdateCallback when context is null
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, SetNDKColorModeUpdateCallbackTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode instance and detach context.
     * @tc.expected: The frameNode should have null context after detaching.
     */
    auto frameNode = FrameNode::CreateFrameNode("test", -1, AceType::MakeRefPtr<Pattern>());
    frameNode->DetachContext();

    /**
     * @tc.steps: step2. Set color mode update callback with null context.
     * @tc.expected: Function should handle null context gracefully without crash.
     */
    bool callbackCalled = false;
    frameNode->SetNDKColorModeUpdateCallback([&callbackCalled](int32_t colorMode) {
        callbackCalled = true;
    });

    /**
     * @tc.steps: step3. Verify that callback is set correctly.
     * @tc.expected: The ndkColorModeUpdateCallback_ should not be nullptr.
     */
    EXPECT_NE(frameNode->ndkColorModeUpdateCallback_, nullptr);
    EXPECT_FALSE(callbackCalled);
    EXPECT_EQ(frameNode->colorMode_, ColorMode::LIGHT);
}

/**
 * @tc.name: SetNDKColorModeUpdateCallbackTest002
 * @tc.desc: Test SetNDKColorModeUpdateCallback when context is valid
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, SetNDKColorModeUpdateCallbackTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode instance with valid context.
     * @tc.expected: The frameNode should be created successfully.
     */
    auto frameNode = FrameNode::CreateFrameNode("test", -1, AceType::MakeRefPtr<Pattern>());
    auto context = PipelineContext::GetCurrentContext();
    frameNode->AttachContext(AceType::RawPtr(context));

    /**
     * @tc.steps: step2. Set color mode update callback with valid context.
     * @tc.expected: Callback should be set and colorMode_ should be updated from context.
     */
    bool callbackCalled = false;
    frameNode->SetNDKColorModeUpdateCallback([&callbackCalled](int32_t colorMode) {
        callbackCalled = true;
    });

    /**
     * @tc.steps: step3. Verify that callback is set correctly.
     * @tc.expected: The ndkColorModeUpdateCallback_ should not be nullptr.
     */
    EXPECT_NE(frameNode->ndkColorModeUpdateCallback_, nullptr);
    EXPECT_FALSE(callbackCalled);
    EXPECT_EQ(frameNode->colorMode_, context->GetColorMode());
}

/**
 * @tc.name: SetNDKColorModeUpdateCallbackTest003
 * @tc.desc: Test SetNDKColorModeUpdateCallback with null callback
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, SetNDKColorModeUpdateCallbackTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode instance with valid context.
     * @tc.expected: The frameNode should be created successfully.
     */
    auto frameNode = FrameNode::CreateFrameNode("test", -1, AceType::MakeRefPtr<Pattern>());
    auto context = PipelineContext::GetCurrentContext();
    frameNode->AttachContext(AceType::RawPtr(context));

    /**
     * @tc.steps: step2. Set color mode update callback to nullptr.
     * @tc.expected: Callback should be set to nullptr and colorMode_ should still be updated from context.
     */
    std::function<void(int32_t)> nullCallback = nullptr;
    frameNode->SetNDKColorModeUpdateCallback(std::move(nullCallback));

    /**
     * @tc.steps: step3. Verify that callback is set to nullptr.
     * @tc.expected: The ndkColorModeUpdateCallback_ should be nullptr.
     */
    EXPECT_EQ(frameNode->ndkColorModeUpdateCallback_, nullptr);
    EXPECT_EQ(frameNode->colorMode_, context->GetColorMode());
}

/**
 * @tc.name: SetNDKColorModeUpdateCallbackTest004
 * @tc.desc: Test SetNDKColorModeUpdateCallback thread safety
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, SetNDKColorModeUpdateCallbackTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode instance with valid context.
     * @tc.expected: The frameNode should be created successfully.
     */
    auto frameNode = FrameNode::CreateFrameNode("test", -1, AceType::MakeRefPtr<Pattern>());
    auto context = PipelineContext::GetCurrentContext();
    frameNode->AttachContext(AceType::RawPtr(context));

    /**
     * @tc.steps: step2. Set color mode update callback multiple times to test thread safety.
     * @tc.expected: Function should handle concurrent access properly without crash.
     */
    for (int i = 0; i < 10; i++) {
        bool callbackCalled = false;
        frameNode->SetNDKColorModeUpdateCallback([i, &callbackCalled](int32_t colorMode) {
            callbackCalled = true;
        });
        EXPECT_NE(frameNode->ndkColorModeUpdateCallback_, nullptr);
        EXPECT_FALSE(callbackCalled);
    }

    /**
     * @tc.steps: step3. Verify that color mode is consistent with context after multiple operations.
     * @tc.expected: The colorMode_ should match the context's color mode.
     */
    EXPECT_EQ(frameNode->colorMode_, context->GetColorMode());
}

/**
 * @tc.name: DumpVisibleAreaInfo001
 * @tc.desc: Test DumpVisibleAreaInfo
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, DumpVisibleAreaInfo001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("test", -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    std::unique_ptr<JsonValue> json = JsonUtil::Create(true);
    ASSERT_NE(json, nullptr);
    frameNode->DumpVisibleAreaInfo();
    frameNode->DumpVisibleAreaInfo(json);
    /**
     * @tc.steps: step1. register userCallback.
     */
    std::vector<double> ratios = { 0.0, 1.0 };
    auto jsCallback1 = [](bool, double) {};
    VisibleCallbackInfo callbackInfo;
    callbackInfo.callback = std::move(jsCallback1);
    callbackInfo.isCurrentVisible = false;
    callbackInfo.period = static_cast<uint32_t>(0);
    callbackInfo.measureFromViewport = true;
    frameNode->SetVisibleAreaUserCallback(ratios, callbackInfo);
    /**
     * @tc.steps: step2. register innerCallback.
     */
    std::vector<double> ratios2 = { 0.0, 1.0 };
    auto jsCallback2 = [](bool, double) {};
    VisibleCallbackInfo callbackInfo2;
    callbackInfo2.callback = std::move(jsCallback2);
    callbackInfo2.isCurrentVisible = false;
    callbackInfo2.period = static_cast<uint32_t>(0);
    callbackInfo2.measureFromViewport = true;
    frameNode->SetVisibleAreaInnerCallback(ratios2, callbackInfo2);
    /**
     * @tc.steps: step3. register throttledCallback.
     */
    std::vector<double> ratios3 = { 0.0, 1.0 };
    auto jsCallback3 = [](bool, double) {};
    VisibleCallbackInfo callbackInfo3;
    callbackInfo3.callback = std::move(jsCallback3);
    callbackInfo3.isCurrentVisible = false;
    callbackInfo3.period = static_cast<uint32_t>(500);
    callbackInfo3.measureFromViewport = true;
    frameNode->SetVisibleAreaUserCallback(ratios3, callbackInfo3);
    frameNode->DumpVisibleAreaInfo();
    frameNode->DumpVisibleAreaInfo(json);
    EXPECT_TRUE(eventHub->HasVisibleAreaCallback(false));
    EXPECT_TRUE(eventHub->HasVisibleAreaCallback(true));
    EXPECT_TRUE(eventHub->HasThrottledVisibleAreaCallback());
}
} // namespace OHOS::Ace::NG