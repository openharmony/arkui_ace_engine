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
} // namespace OHOS::Ace::NG