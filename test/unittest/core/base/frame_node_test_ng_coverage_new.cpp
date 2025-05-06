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
 * @tc.name: FrameNodeOnGenerateOneDepthVisibleFrameWithOffset01
 * @tc.desc: Test the function OnGenerateOneDepthVisibleFrameWithOffset
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeOnGenerateOneDepthVisibleFrameWithOffset01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto childNode = FrameNode::CreateFrameNode("childNode", 1, AceType::MakeRefPtr<Pattern>(), true);
    frameNode->isLayoutNode_ = true;
    frameNode->isActive_ = true;
    frameNode->overlayNode_ = nullptr;
    EXPECT_EQ(frameNode->overlayNode_, nullptr);
    /**
     * @tc.steps: step2. call the function OnGenerateOneDepthVisibleFrameWithOffset.
     */
    OffsetF Offset = { 0.0, 0.0 };
    std::list<RefPtr<FrameNode>> children;
    children.push_back(childNode);
    frameNode->OnGenerateOneDepthVisibleFrameWithOffset(children, Offset);
    frameNode->overlayNode_ = AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>());
    frameNode->OnGenerateOneDepthVisibleFrameWithOffset(children, Offset);
    EXPECT_NE(frameNode->overlayNode_, nullptr);
    EXPECT_EQ(frameNode->overlayNode_->GetNodeName(), "");
}

/**
 * @tc.name: FrameNodeOnGenerateOneDepthVisibleFrameWithOffset02
 * @tc.desc: Test the function OnGenerateOneDepthVisibleFrameWithOffset
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeOnGenerateOneDepthVisibleFrameWithOffset02, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto childNode = FrameNode::CreateFrameNode("childNode", 1, AceType::MakeRefPtr<Pattern>(), true);
    frameNode->isLayoutNode_ = false;
    frameNode->isActive_ = true;
    frameNode->overlayNode_ = AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>());
    EXPECT_NE(frameNode->overlayNode_, nullptr);
    EXPECT_EQ(frameNode->overlayNode_->GetNodeName(), "");
    /**
     * @tc.steps: step2. call the function OnGenerateOneDepthVisibleFrameWithOffset.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    layoutProperty->propVisibility_ = VisibleType::INVISIBLE;
    OffsetF Offset = { 0.0, 0.0 };
    std::list<RefPtr<FrameNode>> children;
    children.push_back(childNode);
    frameNode->SetLayoutProperty(layoutProperty);
    frameNode->OnGenerateOneDepthVisibleFrameWithOffset(children, Offset);
    EXPECT_EQ(frameNode->GetLayoutProperty(), layoutProperty);
}

/**
 * @tc.name: FrameNodeOnGenerateOneDepthVisibleFrameWithOffset03
 * @tc.desc: Test the function OnGenerateOneDepthVisibleFrameWithOffset
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeOnGenerateOneDepthVisibleFrameWithOffset03, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto childNode = FrameNode::CreateFrameNode("childNode", 1, AceType::MakeRefPtr<Pattern>(), true);
    frameNode->isLayoutNode_ = false;
    frameNode->isActive_ = true;
    frameNode->overlayNode_ = AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>());
    EXPECT_NE(frameNode->overlayNode_, nullptr);
    EXPECT_EQ(frameNode->overlayNode_->GetNodeName(), "");
    /**
     * @tc.steps: step2. call the function OnGenerateOneDepthVisibleFrameWithOffset.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    layoutProperty->propVisibility_ = VisibleType::VISIBLE;
    OffsetF Offset = { 0.0, 0.0 };
    std::list<RefPtr<FrameNode>> children;
    children.push_back(childNode);
    frameNode->SetLayoutProperty(layoutProperty);
    frameNode->OnGenerateOneDepthVisibleFrameWithOffset(children, Offset);
    EXPECT_EQ(frameNode->layoutProperty_->propVisibility_, layoutProperty->propVisibility_);
}

/**
 * @tc.name: FrameNodeOnGenerateOneDepthVisibleFrameWithOffset04
 * @tc.desc: Test the function OnGenerateOneDepthVisibleFrameWithOffset
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeOnGenerateOneDepthVisibleFrameWithOffset04, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto childNode = FrameNode::CreateFrameNode("childNode", 1, AceType::MakeRefPtr<Pattern>(), true);
    frameNode->isLayoutNode_ = false;
    frameNode->isActive_ = false;
    frameNode->overlayNode_ = AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>());
    EXPECT_NE(frameNode->overlayNode_, nullptr);
    EXPECT_EQ(frameNode->overlayNode_->GetNodeName(), "");
    /**
     * @tc.steps: step2. call the function OnGenerateOneDepthVisibleFrameWithOffset.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    layoutProperty->propVisibility_ = VisibleType::VISIBLE;
    OffsetF Offset = { 0.0, 0.0 };
    std::list<RefPtr<FrameNode>> children;
    children.push_back(childNode);
    frameNode->SetLayoutProperty(layoutProperty);
    frameNode->OnGenerateOneDepthVisibleFrameWithOffset(children, Offset);
    EXPECT_EQ(frameNode->GetLayoutProperty(), layoutProperty);
}

/**
 * @tc.name: FrameNodeIsOutOfTouchTestRegion01
 * @tc.desc: Test the function IsOutOfTouchTestRegion
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeIsOutOfTouchTestRegion01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto testNode = FrameNode::CreateFrameNode("testNode", 1, AceType::MakeRefPtr<Pattern>(), true);

    /**
     * @tc.steps: step2. call the function IsOutOfTouchTestRegion.
     */
    NG::PointF point { 1.0, 1.0 };
    frameNode->renderContext_->UpdateClipEdge(true);
    TouchEvent touchEvent;
    touchEvent.sourceType = static_cast<SourceType>(1);
    EXPECT_TRUE(frameNode->IsOutOfTouchTestRegion(point, touchEvent));
    testNode->renderContext_->UpdateClipEdge(false);
    EXPECT_TRUE(testNode->IsOutOfTouchTestRegion(point, touchEvent));
}

/**
 * @tc.name: FrameNodeAddJudgeToTargetComponent01
 * @tc.desc: Test the function AddJudgeToTargetComponent
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeAddJudgeToTargetComponent01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);

    /**
     * @tc.steps: step2. call the function AddJudgeToTargetComponent.
     */
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    auto gestureJudgeFunc = [](const RefPtr<GestureInfo>& gestureInfo,
                                const std::shared_ptr<BaseGestureEvent>&) -> GestureJudgeResult {
        return GestureJudgeResult(1);
    };
    gestureHub->SetOnGestureJudgeNativeBegin(gestureJudgeFunc);
    RefPtr<TargetComponent> targetComponent = AceType::MakeRefPtr<TargetComponent>();
    frameNode->AddJudgeToTargetComponent(targetComponent);
    EXPECT_NE(frameNode, nullptr);
}

/**
 * @tc.name: FrameNodeAddJudgeToTargetComponent02
 * @tc.desc: Test the function AddJudgeToTargetComponent
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeAddJudgeToTargetComponent02, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);

    /**
     * @tc.steps: step2. call the function AddJudgeToTargetComponent.
     */
    frameNode->GetOrCreateEventHub<EventHub>()->gestureEventHub_ = nullptr;
    RefPtr<TargetComponent> targetComponent = AceType::MakeRefPtr<TargetComponent>();
    frameNode->AddJudgeToTargetComponent(targetComponent);
    EXPECT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetOrCreateEventHub<EventHub>()->gestureEventHub_, nullptr);
}

/**
 * @tc.name: TriggerShouldParallelInnerWithTest01
 * @tc.desc: Test the function TriggerShouldParallelInnerWith
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, TriggerShouldParallelInnerWithTest01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto gestureHub = frameNode->GetOrCreateEventHub<EventHub>()->GetOrCreateGestureEventHub();
    ShouldBuiltInRecognizerParallelWithFunc shouldBuiltInRecognizerParallelWithFunc =
        [](RefPtr<NGGestureRecognizer> target, std::vector<RefPtr<NGGestureRecognizer>> targets) {
            return RefPtr<NGGestureRecognizer>();
        };
    gestureHub->SetShouldBuildinRecognizerParallelWithFunc(std::move(shouldBuiltInRecognizerParallelWithFunc));
    ResponseLinkResult currentRecognizers;
    ResponseLinkResult responseLinkRecognizers;
    auto recognizer = AceType::MakeRefPtr<ClickRecognizer>();
    recognizer->SetRecognizerType(GestureTypeName::PAN_GESTURE);
    recognizer->GetGestureInfo()->SetIsSystemGesture(true);
    currentRecognizers.emplace_back(recognizer);
    responseLinkRecognizers.emplace_back(recognizer);
    currentRecognizers.emplace_back(AceType::MakeRefPtr<ClickRecognizer>());

    auto recognizer1 = AceType::MakeRefPtr<ClickRecognizer>();
    recognizer1->SetRecognizerType(GestureTypeName::UNKNOWN);
    recognizer1->GetGestureInfo()->SetIsSystemGesture(true);
    currentRecognizers.emplace_back(recognizer1);

    auto recognizer2 = AceType::MakeRefPtr<ClickRecognizer>();
    recognizer2->SetRecognizerType(GestureTypeName::PAN_GESTURE);
    recognizer2->GetGestureInfo()->SetIsSystemGesture(true);
    TouchEvent touchEvent;
    TouchEvent touchEvent1;
    recognizer2->touchPoints_[touchEvent.id] = touchEvent;
    recognizer2->touchPoints_[touchEvent1.id] = touchEvent1;
    currentRecognizers.emplace_back(recognizer2);
    /**
     * @tc.steps: step2. call the function TriggerShouldParallelInnerWith.
     */
    frameNode->TriggerShouldParallelInnerWith(currentRecognizers, responseLinkRecognizers);
    EXPECT_FALSE(recognizer->IsBridgeMode());
}

/**
 * @tc.name: OnSyncGeometryFrameFinishTest
 * @tc.desc: Test the function OnSyncGeometryFrameFinish
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, OnSyncGeometryFrameFinishTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    RectF paintRect = { 10.0f, 10.0f, 10.0f, 10.0f };
    /**
     * @tc.steps: step2. call the function TriggerShouldParallelInnerWith.
     */
    frameNode->OnSyncGeometryFrameFinish(paintRect);
    EXPECT_TRUE(frameNode->syncedFramePaintRect_.has_value());
    frameNode->OnSyncGeometryFrameFinish(paintRect);
    RectF paintRect1 = { 20.0f, 20.0f, 20.0f, 20.0f };
    frameNode->OnSyncGeometryFrameFinish(paintRect1);
    EXPECT_EQ(frameNode->syncedFramePaintRect_, paintRect1);
}

/**
 * @tc.name: IsContextTransparentTest001
 * @tc.desc: Test the function IsContextTransparent
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, IsContextTransparentTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);

    /**
     * @tc.steps: step2. call the function IsContextTransparent.
     */
    EXPECT_TRUE(frameNode->IsContextTransparent());
    frameNode->GetRenderContext()->UpdateOpacity(0.0);
    EXPECT_TRUE(frameNode->IsContextTransparent());
    frameNode->GetRenderContext()->UpdateOpacity(10.0);
    EXPECT_TRUE(frameNode->IsContextTransparent());
    auto mockRenderContext = AceType::DynamicCast<MockRenderContext>(frameNode->GetRenderContext());
    mockRenderContext->SetPaintRectWithTransform(RectF(10.0f, 10.0f, 10.0f, 0.0f));
    EXPECT_TRUE(frameNode->IsContextTransparent());
    mockRenderContext->SetPaintRectWithTransform(RectF(10.0f, 10.0f, 10.0f, 10.0f));
    EXPECT_FALSE(frameNode->IsContextTransparent());
    frameNode->layoutProperty_->propVisibility_ = VisibleType::INVISIBLE;
    EXPECT_TRUE(frameNode->IsContextTransparent());
}

/**
 * @tc.name: IsContextTransparentTest002
 * @tc.desc: Test the function IsContextTransparent
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, IsContextTransparentTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode("Flex", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto frameNode1 = FrameNode::CreateFrameNode("framenode", 2, AceType::MakeRefPtr<Pattern>(), true);
    frameNode->AddChild(frameNode1);
    /**
     * @tc.steps: step2. call the function IsContextTransparent.
     */
    EXPECT_TRUE(frameNode->IsContextTransparent());
    auto mockRenderContext = AceType::DynamicCast<MockRenderContext>(frameNode->GetRenderContext());
    mockRenderContext->SetPaintRectWithTransform(RectF(10.0f, 10.0f, 10.0f, 0.0f));
    auto mockRenderContext1 = AceType::DynamicCast<MockRenderContext>(frameNode1->GetRenderContext());
    mockRenderContext1->SetPaintRectWithTransform(RectF(10.0f, 10.0f, 10.0f, 10.0f));
    EXPECT_FALSE(frameNode->IsContextTransparent());
    mockRenderContext->SetPaintRectWithTransform(RectF(10.0f, 10.0f, 10.0f, 10.0f));
    EXPECT_FALSE(frameNode->IsContextTransparent());
    frameNode->layoutProperty_->propVisibility_ = VisibleType::INVISIBLE;
    EXPECT_FALSE(frameNode->IsContextTransparent());
    frameNode->layoutProperty_->propVisibility_ = VisibleType::VISIBLE;
    frameNode->GetRenderContext()->UpdateBackgroundColor(Color::BLUE);
    EXPECT_FALSE(frameNode->IsContextTransparent());
}

/**
 * @tc.name: AddTouchEventAllFingersInfoTest
 * @tc.desc: Test the function AddTouchEventAllFingersInfo
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, AddTouchEventAllFingersInfoTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    /**
     * @tc.steps: step2. call the function AddTouchEventAllFingersInfoTest.
     */
    TouchEventInfo touchEventInfo("touch");
    TouchEvent touchEvent;
    TouchPoint touchPoint;
    touchEvent.pointers.emplace_back(touchPoint);
    TouchPoint touchPoint1;
    touchPoint1.tiltX = 10.0;
    touchPoint1.tiltY = 10.0;
    touchEvent.pointers.emplace_back(touchPoint1);
    frameNode->AddTouchEventAllFingersInfo(touchEventInfo, touchEvent);
    EXPECT_EQ(touchEventInfo.touches_.size(), 2);
}

/**
 * @tc.name: TriggerOnTouchInterceptTest
 * @tc.desc: Test the function TriggerOnTouchIntercept
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, TriggerOnTouchInterceptTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    /**
     * @tc.steps: step2. call the function AddTouchEventAllFingersInfoTest.
     */
    auto gestureHub = frameNode->GetOrCreateEventHub<EventHub>()->GetOrCreateGestureEventHub();
    TouchInterceptFunc touchInterceptFunc = [](TouchEventInfo& touchEventInfo) { return HitTestMode::HTMBLOCK; };
    gestureHub->SetOnTouchIntercept(std::move(touchInterceptFunc));
    TouchEventInfo touchEventInfo("touch");
    TouchEvent touchEvent;
    EXPECT_EQ(frameNode->TriggerOnTouchIntercept(touchEvent), HitTestMode::HTMBLOCK);
    touchEvent.tiltX = 10.0;
    touchEvent.tiltY = 10.0;
    EXPECT_EQ(frameNode->TriggerOnTouchIntercept(touchEvent), HitTestMode::HTMBLOCK);
}

/**
 * @tc.name: CalculateCachedTransformRelativeOffsetTest
 * @tc.desc: Test the function CalculateCachedTransformRelativeOffset
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, CalculateCachedTransformRelativeOffsetTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    /**
     * @tc.steps: step2. call the function CalculateCachedTransformRelativeOffset.
     */
    frameNode->CalculateCachedTransformRelativeOffset(0);
    auto child = FrameNode::CreateFrameNode("child", 2, AceType::MakeRefPtr<Pattern>(), true);
    frameNode->AddChild(child);
    child->CalculateCachedTransformRelativeOffset(0);
    frameNode->exposureProcessor_ = AceType::MakeRefPtr<Recorder::ExposureProcessor>("test", "0");
    frameNode->RecordExposureInner();
    EXPECT_EQ(child->CalculateCachedTransformRelativeOffset(0), OffsetF(0, 0));
    EXPECT_EQ(child->CalculateCachedTransformRelativeOffset(10), OffsetF(0, 0));
}

/**
 * @tc.name: ProcessVisibleAreaChangeEventTest
 * @tc.desc: Test the function ProcessVisibleAreaChangeEvent
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, ProcessVisibleAreaChangeEventTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    RectF visibleRect = { 10.0, 10.0, 10.0, 10.0 };
    RectF frameRect = { 10.0, 10.0, 10.0, 10.0 };
    std::vector<double> visibleAreaRatios = { 0.0, 0.0 };
    VisibleCallbackInfo visibleAreaCallback;

    /**
     * @tc.steps: step2. call the function ProcessVisibleAreaChangeEvent.
     */
    // !NearEqual
    frameNode->ProcessVisibleAreaChangeEvent(visibleRect, frameRect, visibleAreaRatios, visibleAreaCallback, true);
    // NearEqual
    frameNode->ProcessVisibleAreaChangeEvent(visibleRect, frameRect, visibleAreaRatios, visibleAreaCallback, true);
    EXPECT_EQ(frameNode->lastVisibleRatio_, 1.0);
    // !NearEqual
    frameNode->ProcessVisibleAreaChangeEvent(visibleRect, frameRect, visibleAreaRatios, visibleAreaCallback, false);
    // NearEqual
    frameNode->ProcessVisibleAreaChangeEvent(visibleRect, frameRect, visibleAreaRatios, visibleAreaCallback, false);
    EXPECT_EQ(frameNode->lastInnerVisibleRatio_, 1.0);
}

/**
 * @tc.name: FrameNodeTestNg_AxisTest001
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeAxisTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. callback AxisTest.
     * @tc.expected: expect isActive_ is flase and.
     */
    PointF globalPoint;
    PointF parentLocalPoint;
    PointF parentRevertPoint;
    TouchRestrict touchRestrict;
    AxisTestResult onAxisResult;
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(frameNode, nullptr);
    frameNode->isActive_ = false;
    /**
     * @tc.steps: step2. callback AxisTest.
     * @tc.expected: expect eventHub_ is nullptr.
     */
    ASSERT_EQ(frameNode->eventHub_, nullptr);
    auto result = frameNode->AxisTest(globalPoint, parentLocalPoint, parentRevertPoint, touchRestrict, onAxisResult);
    EXPECT_EQ(result, HitTestResult::OUT_OF_REGION);
    /**
     * @tc.steps: step3. callback AxisTest.
     * @tc.expected: expect eventHub_ is not nullptr and enabled_ is false.
     */
    frameNode->eventHub_ = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(frameNode->eventHub_, nullptr);
    auto eventHub_ = frameNode->eventHub_;
    eventHub_->enabled_ = false;
    result = frameNode->AxisTest(globalPoint, parentLocalPoint, parentRevertPoint, touchRestrict, onAxisResult);
    EXPECT_EQ(result, HitTestResult::OUT_OF_REGION);
    /**
     * @tc.steps: step4. callback AxisTest.
     * @tc.expected: expect eventHub_ is not nullptr and enabled_ is true.
     */
    eventHub_->enabled_ = true;
    result = frameNode->AxisTest(globalPoint, parentLocalPoint, parentRevertPoint, touchRestrict, onAxisResult);
    EXPECT_EQ(result, HitTestResult::OUT_OF_REGION);
}

/**
 * @tc.name: FrameNodeTestNg_AxisTest002
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeAxisTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. callback AxisTest.
     * @tc.expected: expect isActive_ is true and.
     */
    PointF globalPoint;
    PointF parentLocalPoint;
    PointF parentRevertPoint;
    TouchRestrict touchRestrict;
    AxisTestResult onAxisResult;
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_TRUE(frameNode->IsOutOfTouchTestRegion(parentRevertPoint, touchRestrict.touchEvent));
    frameNode->isActive_ = true;
    /**
     * @tc.steps: step2. callback AxisTest.
     * @tc.expected: expect eventHub_ is nullptr.
     */
    ASSERT_EQ(frameNode->eventHub_, nullptr);
    auto result = frameNode->AxisTest(globalPoint, parentLocalPoint, parentRevertPoint, touchRestrict, onAxisResult);
    EXPECT_EQ(result, HitTestResult::OUT_OF_REGION);
    /**
     * @tc.steps: step3. callback AxisTest.
     * @tc.expected: expect eventHub_ is not nullptr and enabled_ is false.
     */
    frameNode->eventHub_ = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(frameNode->eventHub_, nullptr);
    auto eventHub_ = frameNode->eventHub_;
    eventHub_->enabled_ = false;
    result = frameNode->AxisTest(globalPoint, parentLocalPoint, parentRevertPoint, touchRestrict, onAxisResult);
    EXPECT_EQ(result, HitTestResult::OUT_OF_REGION);
    /**
     * @tc.steps: step4. callback AxisTest.
     * @tc.expected: expect eventHub_ is not nullptr and enabled_ is true.
     */
    eventHub_->enabled_ = true;
    result = frameNode->AxisTest(globalPoint, parentLocalPoint, parentRevertPoint, touchRestrict, onAxisResult);
    EXPECT_EQ(result, HitTestResult::OUT_OF_REGION);
}

/**
 * @tc.name: FrameNodeTestNg_AxisTest003
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeAxisTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. callback AxisTest.
     * @tc.expected: expect isActive_ is true and.
     */
    PointF globalPoint;
    PointF parentLocalPoint = { 1.0f, 1.0f };
    PointF parentRevertPoint = { 1.0f, 1.0f };
    TouchRestrict touchRestrict;
    AxisTestResult onAxisResult;
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(frameNode, nullptr);
    frameNode->isActive_ = true;
    auto eventHub_ = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub_, nullptr);
    frameNode->eventHub_ = eventHub_;
    eventHub_->enabled_ = true;
    /**
     * @tc.steps: step2. callback AxisTest.
     * @tc.expected: expect IsOutOfTouchTestRegion(parentRevertPoint, touchRestrict.touchEvent) is false.
     */
    auto renderContext_ = AceType::MakeRefPtr<MockRenderContext>();
    ASSERT_NE(renderContext_, nullptr);
    frameNode->renderContext_ = renderContext_;
    renderContext_->paintRect_ = { 1.0f, 1.0f, 1.0f, 1.0f };
    frameNode->GetOrRefreshMatrixFromCache().paintRectWithTransform = { 1.0f, 1.0f, 1.0f, 1.0f };
    EXPECT_FALSE(frameNode->IsOutOfTouchTestRegion(parentRevertPoint, touchRestrict.touchEvent));
    /**
     * @tc.steps: step3. callback AxisTest.
     * @tc.expected: expect consumed is false.
     */
    auto result = frameNode->AxisTest(globalPoint, parentLocalPoint, parentRevertPoint, touchRestrict, onAxisResult);
    EXPECT_EQ(result, HitTestResult::BUBBLING);
}

/**
 * @tc.name: FrameNodeTestNg_AxisTest004
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeAxisTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. callback AxisTest.
     * @tc.expected: expect isActive_ is true and.
     */
    PointF globalPoint;
    PointF parentLocalPoint = { 1.0f, 1.0f };
    PointF parentRevertPoint = { 1.0f, 1.0f };
    TouchRestrict touchRestrict;
    AxisTestResult onAxisResult;
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(frameNode, nullptr);
    frameNode->isActive_ = true;
    auto eventHub_ = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub_, nullptr);
    frameNode->eventHub_ = eventHub_;
    eventHub_->enabled_ = true;
    /**
     * @tc.steps: step2. callback AxisTest.
     * @tc.expected: expect IsOutOfTouchTestRegion(parentRevertPoint, touchRestrict.touchEvent) is false.
     */
    auto renderContext_ = AceType::MakeRefPtr<MockRenderContext>();
    ASSERT_NE(renderContext_, nullptr);
    frameNode->renderContext_ = renderContext_;
    renderContext_->paintRect_ = { 1.0f, 1.0f, 1.0f, 1.0f };
    frameNode->GetOrRefreshMatrixFromCache().paintRectWithTransform = { 1.0f, 1.0f, 1.0f, 1.0f };
    auto childNode = FrameNode::CreateFrameNode("childNode", 2, AceType::MakeRefPtr<Pattern>(), true);
    /**
     * @tc.steps: step3. callback AxisTest.
     * @tc.expected: expect GetHitTestMode() == HitTestMode::HTMBLOCK is false.
     */
    std::list<RefPtr<FrameNode>> children;
    children.push_back(childNode);
    frameNode->frameChildren_ = { children.begin(), children.end() };
    EXPECT_FALSE(frameNode->IsOutOfTouchTestRegion(parentRevertPoint, touchRestrict.touchEvent));
    /**
     * @tc.steps: step5. callback AxisTest.
     * @tc.expected: expect consumed is true.
     */
    auto gestureHub = eventHub_->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);
    gestureHub->hitTestMode_ = HitTestMode::HTMNONE;
    auto result = frameNode->AxisTest(globalPoint, parentLocalPoint, parentRevertPoint, touchRestrict, onAxisResult);
    EXPECT_EQ(result, HitTestResult::OUT_OF_REGION);
}

/**
 * @tc.name: FrameNodeTestNg_AxisTest005
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeAxisTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. callback AxisTest.
     * @tc.expected: expect isActive_ is true and.
     */
    PointF globalPoint;
    PointF parentLocalPoint = { 1.0f, 1.0f };
    PointF parentRevertPoint = { 1.0f, 1.0f };
    TouchRestrict touchRestrict;
    AxisTestResult onAxisResult;
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(frameNode, nullptr);
    frameNode->isActive_ = true;
    auto eventHub_ = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub_, nullptr);
    frameNode->eventHub_ = eventHub_;
    eventHub_->enabled_ = true;
    /**
     * @tc.steps: step2. callback AxisTest.
     * @tc.expected: expect IsOutOfTouchTestRegion(parentRevertPoint, touchRestrict.touchEvent) is false.
     */
    auto renderContext_ = AceType::MakeRefPtr<MockRenderContext>();
    ASSERT_NE(renderContext_, nullptr);
    frameNode->renderContext_ = renderContext_;
    renderContext_->paintRect_ = { 1.0f, 1.0f, 1.0f, 1.0f };
    frameNode->GetOrRefreshMatrixFromCache().paintRectWithTransform = { 1.0f, 1.0f, 1.0f, 1.0f };
    auto childNode = FrameNode::CreateFrameNode("childNode", 2, AceType::MakeRefPtr<Pattern>(), true);
    /**
     * @tc.steps: step3. callback AxisTest.
     * @tc.expected: expect GetHitTestMode() == HitTestMode::HTMBLOCK is true.
     */
    std::list<RefPtr<FrameNode>> children;
    children.push_back(childNode);
    frameNode->frameChildren_ = { children.begin(), children.end() };
    EXPECT_FALSE(frameNode->IsOutOfTouchTestRegion(parentRevertPoint, touchRestrict.touchEvent));
    auto gestureHub = eventHub_->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);
    gestureHub->hitTestMode_ = HitTestMode::HTMBLOCK;
    auto result = frameNode->AxisTest(globalPoint, parentLocalPoint, parentRevertPoint, touchRestrict, onAxisResult);
    EXPECT_EQ(result, HitTestResult::BUBBLING);
}

/**
 * @tc.name: FrameNodeTestNg_AxisTest006
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeAxisTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. callback AxisTest.
     * @tc.expected: expect isActive_ is true and.
     */
    PointF globalPoint;
    PointF parentLocalPoint = { 1.0f, 1.0f };
    PointF parentRevertPoint = { 1.0f, 1.0f };
    TouchRestrict touchRestrict;
    AxisTestResult onAxisResult;
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(frameNode, nullptr);
    frameNode->isActive_ = true;
    auto eventHub_ = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub_, nullptr);
    frameNode->eventHub_ = eventHub_;
    eventHub_->enabled_ = true;
    /**
     * @tc.steps: step2. callback AxisTest.
     * @tc.expected: expect IsOutOfTouchTestRegion(parentRevertPoint, touchRestrict.touchEvent) is false.
     */
    auto renderContext_ = AceType::MakeRefPtr<MockRenderContext>();
    ASSERT_NE(renderContext_, nullptr);
    frameNode->renderContext_ = renderContext_;
    renderContext_->paintRect_ = { 1.0f, 1.0f, 1.0f, 1.0f };
    frameNode->GetOrRefreshMatrixFromCache().paintRectWithTransform = { 1.0f, 1.0f, 1.0f, 1.0f };
    /**
     * @tc.steps: step3. callback AxisTest.
     * @tc.expected: expect !child is true.
     */
    auto childNode = nullptr;
    std::list<RefPtr<FrameNode>> children;
    children.push_back(childNode);
    frameNode->frameChildren_ = { children.begin(), children.end() };
    EXPECT_FALSE(frameNode->IsOutOfTouchTestRegion(parentRevertPoint, touchRestrict.touchEvent));
    auto gestureHub = eventHub_->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);
    gestureHub->hitTestMode_ = HitTestMode::HTMNONE;
    auto result = frameNode->AxisTest(globalPoint, parentLocalPoint, parentRevertPoint, touchRestrict, onAxisResult);
    EXPECT_EQ(result, HitTestResult::OUT_OF_REGION);
}

/**
 * @tc.name: FrameNodeTestNg_AxisTest007
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeAxisTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. callback AxisTest.
     * @tc.expected: expect isActive_ is true and.
     */
    PointF globalPoint;
    PointF parentLocalPoint = { 3.0f, 3.0f };
    PointF parentRevertPoint = { 2.0f, 2.0f };
    TouchRestrict touchRestrict;
    AxisTestResult onAxisResult;
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(frameNode, nullptr);
    frameNode->isActive_ = true;
    auto eventHub_ = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub_, nullptr);
    frameNode->eventHub_ = eventHub_;
    eventHub_->enabled_ = true;
    /**
     * @tc.steps: step2. callback AxisTest.
     * @tc.expected: expect IsOutOfTouchTestRegion(parentRevertPoint, touchRestrict.touchEvent) is false.
     */
    auto renderContext_ = AceType::MakeRefPtr<MockRenderContext>();
    ASSERT_NE(renderContext_, nullptr);
    frameNode->renderContext_ = renderContext_;
    renderContext_->paintRect_ = { 1.0f, 1.0f, 1.0f, 1.0f };
    frameNode->GetOrRefreshMatrixFromCache().paintRectWithTransform = { 1.0f, 1.0f, 1.0f, 1.0f };
    auto childNode = FrameNode::CreateFrameNode("childNode", 2, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(childNode, nullptr);
    /**
     * @tc.steps: step3. callback AxisTest.
     * @tc.expected: expect CheckChildHitTestReslut is true.
     */
    childNode->isActive_ = true;
    auto childEventHub_ = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(childEventHub_, nullptr);
    childNode->eventHub_ = childEventHub_;
    childEventHub_->enabled_ = true;
    auto childRenderContext_ = AceType::MakeRefPtr<MockRenderContext>();
    ASSERT_NE(childRenderContext_, nullptr);
    childNode->renderContext_ = childRenderContext_;
    childRenderContext_->paintRect_ = { 1.0f, 1.0f, 1.0f, 1.0f };
    childNode->GetOrRefreshMatrixFromCache().paintRectWithTransform = { 1.0f, 1.0f, 1.0f, 1.0f };
    auto childGestureHub = childEventHub_->GetOrCreateGestureEventHub();
    childGestureHub->hitTestMode_ = HitTestMode::HTMDEFAULT;
    std::list<RefPtr<FrameNode>> children;
    children.push_back(childNode);
    frameNode->frameChildren_ = { children.begin(), children.end() };
    EXPECT_FALSE(frameNode->IsOutOfTouchTestRegion(parentRevertPoint, touchRestrict.touchEvent));
    auto gestureHub = eventHub_->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);
    gestureHub->hitTestMode_ = HitTestMode::HTMNONE;
    auto result = frameNode->AxisTest(globalPoint, parentLocalPoint, parentRevertPoint, touchRestrict, onAxisResult);
    EXPECT_EQ(result, HitTestResult::BUBBLING);
}
} // namespace OHOS::Ace::NG