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
#include "test/unittest/core/base/frame_node_test_ng.h"
#include "gtest/gtest.h"
#include "core/components_ng/pattern/marquee/marquee_paint_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "interfaces/inner_api/ace_kit/src/view/frame_node_impl.h"
#include "core/components_ng/pattern/linear_layout/column_model_ng.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
void FrameNodeTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
}

void FrameNodeTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

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

    /**
     * @tc.steps: step2. create FrameNode and set a callback
     * @tc.expect: call DestroyCallback while object is destroyed
     */
    bool flag = false;
    auto three = FrameNode::GetOrCreateFrameNode("one", 1, nullptr);
    ASSERT_NE(three, nullptr);
    three->PushDestroyCallbackWithTag([&flag]() { flag = !flag; }, "");
    three = nullptr;
    EXPECT_TRUE(flag);
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
 * @tc.name: FrameNodeTestNg004
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNg004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create framenode and initialize the params used in Test.
     */
    auto node = FrameNode::CreateFrameNode("childNode", 10, AceType::MakeRefPtr<Pattern>(), true);
    node->AttachToMainTree();
    node->GetRenderContext()->RequestNextFrame();
    EXPECT_TRUE(node->IsOnMainTree());

    int32_t nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    const RefPtr<FrameNode> parentNode =
        FrameNode::CreateFrameNode("RelativeContainer", nodeId, AceType::MakeRefPtr<Pattern>(), true);
    node->SetParent(AceType::WeakClaim(AceType::RawPtr(parentNode)));

    /**
     * @tc.steps: step2. call OnInspectorIdUpdate .
     * @tc.expect: this parentNode is MarkDirtyNode, but this Tag() != "RelativeContainer"
     * this parentNode is not MarkDirtyNode
     */
    node->OnInspectorIdUpdate("RelativeContainer");
    EXPECT_EQ(parentNode->GetTag(), "RelativeContainer");
}

/**
 * @tc.name: FrameNodeTestNg007
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNg007, TestSize.Level1)
{
    /**
     * @tc.steps: step 1. create framenode and initialize the params used in Test.
     */
    auto node = FrameNode::CreateFrameNode("childNode", 10, AceType::MakeRefPtr<Pattern>(), true);

    int32_t nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    const RefPtr<FrameNode> parentNode =
        FrameNode::CreateFrameNode("parent", nodeId, AceType::MakeRefPtr<Pattern>(), true);
    node->SetParent(AceType::WeakClaim(AceType::RawPtr(parentNode)));

    const RefPtr<FrameNode> overlayNode =
        FrameNode::CreateFrameNode("overlayNode", nodeId, AceType::MakeRefPtr<Pattern>(), true);

    /**
     * @tc.steps: step 2. call OnInspectorIdUpdate .
     * @tc.expect: this parentNode is MarkDirtyNode, but this Tag() != "RelativeContainer"
     * this parentNode is not MarkDirtyNode
     */

    node->SetParent(AceType::WeakClaim(AceType::RawPtr(parentNode)));
    node->OnInspectorIdUpdate("RelativeContainer");
    EXPECT_EQ(parentNode->GetTag(), "parent");

    /**
     * @tc.steps: step 3. call LayoutOverlay .
     * @tc.expect: FrameRect of overlayNode is 0.
     */
    node->SetOverlayNode(overlayNode);
    node->LayoutOverlay();

    auto layoutProperty = overlayNode->GetLayoutProperty();
    layoutProperty->positionProperty_ = std::make_unique<PositionProperty>();
    node->LayoutOverlay();
    EXPECT_EQ(overlayNode->GetGeometryNode()->GetFrameRect().GetX(), 0);

    /**
     * @tc.steps: step 4. call GetFrameChildByIndex .
     * @tc.expect: index == 0 return uiNode, index != 0 return null
     */
    EXPECT_TRUE(node->GetFrameChildByIndex(0, false));
    EXPECT_FALSE(node->GetFrameChildByIndex(1, false));

    /**
     * @tc.steps: step 5. call GetBaselineDistance .
     * @tc.expect: node has not child return 0. if node has child return  childBaseline of child
     */
    EXPECT_EQ(node->GetBaselineDistance(), 0);
    node->AddChild(FRAME_NODE);
    EXPECT_EQ(node->GetBaselineDistance(), 0);
    auto nodeLayoutProperty = node->GetLayoutProperty();
    nodeLayoutProperty->geometryTransition_ =
        ElementRegister::GetInstance()->GetOrCreateGeometryTransition("test", false, true);
    node->Layout();
    EXPECT_FALSE(node->IsRootMeasureNode());
    node->SetRootMeasureNode();
    node->Layout();
    EXPECT_TRUE(node->IsRootMeasureNode());
}

/**
 * @tc.name: FrameNodeTestNg008
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNg008, TestSize.Level1)
{
    /**
     * @tc.steps: step 1. create framenode and initialize the params used in Test.
     */
    RefPtr<NG::DrawModifier> drawModifier = AceType::MakeRefPtr<NG::DrawModifier>();
    ASSERT_NE(drawModifier, nullptr);

    /**
     * @tc.steps: step 2. call get function .
     * @tc.expect: expect the return value to be correct.
     */
    EXPECT_TRUE(FRAME_NODE->IsSupportDrawModifier());

    /**
     * @tc.steps: step 3. call GetContentModifier when drawModifier is null.
     * @tc.expect: expect the return value to be correct.
     */
    EXPECT_EQ(FRAME_NODE->GetContentModifier(), nullptr);

    /**
     * @tc.steps: step 4. Nodes created by virtual classes, call GetContentModifier when drawModifier is null.
     * @tc.expect: expect the return value to be correct.
     */
    FRAME_NODE->SetDrawModifier(drawModifier);
    EXPECT_EQ(FRAME_NODE->GetContentModifier(), nullptr);

    /**
     * @tc.steps: step 5. Nodes created by virtual classes, call SetRemoveCustomProperties.
     * @tc.expect: expect call successfully.
     */
    FRAME_NODE->SetRemoveCustomProperties([]() -> void {});
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
    ResponseLinkResult responseLinkResult;

    mockRenderContext->rect_ = RectF(0, 0, 100, 100);
    EXPECT_CALL(*mockRenderContext, GetPointWithTransform(_)).WillRepeatedly(DoAll(SetArgReferee<0>(localPoint)));

    /**
     * @tc.steps: step2. create childnode
     */
    auto childNode = FrameNode::CreateFrameNode("main", 2, AceType::MakeRefPtr<Pattern>(), true);
    childNode->SetExclusiveEventForChild(true);
    auto mockRenderContextforChild = AceType::MakeRefPtr<MockRenderContext>();
    childNode->renderContext_ = mockRenderContextforChild;
    mockRenderContext->rect_ = RectF(0, 0, 100, 100);
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
    mockRenderContext->rect_ = RectF(0, 0, 100, 100);
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
                auto result = childNode->TouchTest(globalPoint, parentLocalPointOne, parentLocalPointOne, touchRestrict,
                    touchTestResult, 0, responseLinkResult, true);
                result = node->TouchTest(globalPoint, parentLocalPointOne, parentLocalPointOne, touchRestrict,
                    touchTestResult, 0, responseLinkResult, true);
            }
        }
    }
}

/**
 * @tc.name: FrameNodeTestNg005
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNg005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. callback function.
     * @tc.expected: expect The function is run ok.
     */
    auto one = FrameNode::CreateFrameNodeWithTree("main", 10, AceType::MakeRefPtr<Pattern>());
    EXPECT_NE(one, nullptr);

    MeasureProperty calcLayoutConstraint;
    FRAME_NODE->UpdateLayoutConstraint(std::move(calcLayoutConstraint));
    EXPECT_EQ(FRAME_NODE2->layoutProperty_->propertyChangeFlag_, 1);

    FRAME_NODE2->needSyncRenderTree_ = true;
    FRAME_NODE2->RebuildRenderContextTree();
    EXPECT_FALSE(FRAME_NODE2->needSyncRenderTree_);

    /**
     * @tc.steps: step 2. create and set overlayNode.
     * @tc.expect:cover branch overlayNode is not null and function is run ok.
     */
    int32_t nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    const RefPtr<FrameNode> overlayNode =
        FrameNode::CreateFrameNode("overlayNode", nodeId, AceType::MakeRefPtr<Pattern>(), true);
    FRAME_NODE2->SetOverlayNode(overlayNode);
    FRAME_NODE2->RebuildRenderContextTree();
    EXPECT_FALSE(FRAME_NODE2->needSyncRenderTree_);

    FRAME_NODE2->OnMountToParentDone();

    FRAME_NODE2->FlushUpdateAndMarkDirty();

    std::list<RefPtr<FrameNode>> visibleList;
    FRAME_NODE2->isActive_ = true;
    FRAME_NODE2->OnGenerateOneDepthVisibleFrame(visibleList);
    EXPECT_TRUE(FRAME_NODE2->IsVisible());

    FRAME_NODE2->OnGenerateOneDepthAllFrame(visibleList);
    EXPECT_EQ(visibleList.size(), 2);

    auto pattern = FRAME_NODE2->GetPattern();
    EXPECT_EQ(pattern, 1);

    auto atomicNode = FRAME_NODE2->IsAtomicNode();
    EXPECT_TRUE(atomicNode);

    auto hitTestMode = FRAME_NODE2->GetHitTestMode();
    EXPECT_EQ(hitTestMode, HitTestMode::HTMDEFAULT);

    auto touchable = FRAME_NODE2->GetTouchable();
    EXPECT_TRUE(touchable);

    const PointF globalPoint;
    const PointF parentLocalPoint;
    MouseTestResult onMouseResult;
    MouseTestResult onHoverResult;
    RefPtr<FrameNode> hoverNode;
    auto mouse = FRAME_NODE2->MouseTest(globalPoint, parentLocalPoint, onMouseResult, onHoverResult, hoverNode);
    EXPECT_EQ(mouse, HitTestResult::BUBBLING);
}

/**
 * @tc.name: FrameNodeTestNg006
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNg006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. callback function.
     * @tc.expected: expect The function is run ok.
     */
    FRAME_NODE2->OnWindowShow();
    FRAME_NODE2->OnWindowHide();
    FRAME_NODE2->OnWindowFocused();
    FRAME_NODE2->OnWindowUnfocused();
    FRAME_NODE2->OnWindowSizeChanged(1, 1, WindowSizeChangeReason::CUSTOM_ANIMATION);

    OffsetF Offset = { 0, 0 };
    FRAME_NODE2->SetParent(FRAME_NODE3);
    auto relativeOffset = FRAME_NODE2->GetTransformRelativeOffset();
    EXPECT_EQ(relativeOffset, Offset);

    FRAME_NODE2->SetParent(FRAME_NODE3);
    auto rectOffset = FRAME_NODE2->GetPaintRectOffset(true);
    EXPECT_EQ(rectOffset, Offset);

    FRAME_NODE2->OnNotifyMemoryLevel(true);

    auto childrenCount = FRAME_NODE2->GetAllDepthChildrenCount();
    EXPECT_EQ(childrenCount, 1);

    DimensionRect dimensionRect;
    FRAME_NODE2->AddHotZoneRect(dimensionRect);
    FRAME_NODE2->RemoveLastHotZoneRect();
    EXPECT_NE(FRAME_NODE2->GetOrCreateEventHub<EventHub>(), nullptr);

    FRAME_NODE->ProcessOffscreenNode(FRAME_NODE3);
    FRAME_NODE->GetTransformRectRelativeToWindow();
    FRAME_NODE->GetPaintRectOffsetToPage();

    float x = 1.0;
    float y = 1.0;
    auto Position = FRAME_NODE->FindChildByPosition(x, y);
    EXPECT_EQ(Position, nullptr);

    FRAME_NODE->ProvideRestoreInfo();
    auto immediately = FRAME_NODE->RemoveImmediately();
    EXPECT_TRUE(immediately);
}

/**
 * @tc.name: FrameNodeTestNg_DumpInfo006
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeDumpInfo006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. callback DumpInfo
     * @tc.expected: expect The function is run ok.
     */
    LayoutProperty layoutProperty;
    FRAME_NODE->DumpInfo();

    FRAME_NODE->layoutProperty_->UpdatePadding(PaddingPropertyT<CalcLength>());
    FRAME_NODE->layoutProperty_->GetPaddingProperty();
    FRAME_NODE->DumpInfo();
    EXPECT_EQ(layoutProperty.padding_, nullptr);

    FRAME_NODE->layoutProperty_->UpdateMargin(PaddingProperty());
    FRAME_NODE->layoutProperty_->GetMarginProperty();
    FRAME_NODE->DumpInfo();
    EXPECT_EQ(layoutProperty.margin_, nullptr);

    FRAME_NODE->layoutProperty_->UpdateBorderWidth(BorderWidthPropertyT<Dimension>());
    FRAME_NODE->layoutProperty_->GetBorderWidthProperty();
    FRAME_NODE->DumpInfo();
    EXPECT_EQ(layoutProperty.borderWidth_, nullptr);

    /**
     * @tc.steps: step2. set layoutConstraintF_ an geometryNode_'sParentLayoutConstraint
                and call DumpInfo
     * @tc.expected: expect The function is run ok.
     */
    FRAME_NODE->layoutProperty_->calcLayoutConstraint_ = std::make_unique<MeasureProperty>();
    auto layoutConstraintF_ = LayoutConstraintF();
    FRAME_NODE->geometryNode_->SetParentLayoutConstraint(layoutConstraintF_);
    FRAME_NODE->DumpInfo();
    EXPECT_EQ(layoutProperty.calcLayoutConstraint_, nullptr);
}

/**
 * @tc.name: FrameNodeTestNg_ToJsonValue007
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeToJsonValue007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build a object to jsonValue
     * @tc.expected: expect The function is run ok.
     */
    auto gestureEventHub = FRAME_NODE->GetOrCreateGestureEventHub();

    std::vector<DimensionRect> responseRegion;
    responseRegion.push_back(DimensionRect());
    gestureEventHub->SetResponseRegion(responseRegion);

    auto jsonValue = JsonUtil::Create(true);
    FRAME_NODE->ToJsonValue(jsonValue, filter);
    EXPECT_TRUE(jsonValue);

    /**
     * @tc.steps: step2. build a object to jsonValue and call FromJson
     * @tc.expected: expect The function is run ok.
     */
    FRAME_NODE->FromJson(jsonValue);
    FRAME_NODE->renderContext_ = nullptr;
    FRAME_NODE->focusHub_ = nullptr;
    auto jsonValue2 = JsonUtil::Create(true);
    FRAME_NODE->ToJsonValue(jsonValue2, filter);
    FRAME_NODE->FromJson(jsonValue2);
    EXPECT_TRUE(jsonValue2);
}

/**
 * @tc.name: FrameNodeTestNg_OnAttachToMainTree008
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeOnAttachToMainTree008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build a object to OnAttachToMainTree
     * @tc.expected: expect The function is run ok.
     */
    FRAME_NODE2->OnAttachToMainTree(true);

    auto request = FRAME_NODE2->hasPendingRequest_ = true;
    FRAME_NODE2->OnAttachToMainTree(true);
    EXPECT_TRUE(request);

    /**
     * @tc.steps: step2 set PositionProperty of FRAME_NODE2 and call OnAttachToMainTree
     * @tc.expected: expect The function is run ok.
     */
    auto& posProperty = FRAME_NODE2->renderContext_->GetOrCreatePositionProperty();
    posProperty->UpdateOffset(OffsetT<Dimension>()); // OffsetT<Dimension>
    FRAME_NODE2->SetParent(FRAME_NODE_PARENT);
    auto testNode_ = TestNode::CreateTestNode(100);
    FRAME_NODE_PARENT->SetParent(testNode_);
    FRAME_NODE2->OnAttachToMainTree(true);
    EXPECT_TRUE(request);
}

/**
 * @tc.name: FrameNodeTestNg_NotifyVisibleChange009
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeNotifyVisibleChange009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build a object to NotifyVisibleChange
     * @tc.expected: expect The FRAME_NODE2 is not nullptr.
     */
    FRAME_NODE2->AddChild(FRAME_NODE3);
    FRAME_NODE2->NotifyVisibleChange(VisibleType::VISIBLE, VisibleType::INVISIBLE);
    FRAME_NODE2->Clean();
    EXPECT_NE(FRAME_NODE2, nullptr);
}

/**
 * @tc.name: FrameNodeTestNg_SwapDirtyLayoutWrapperOnMainThread0010
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeSwapDirtyLayoutWrapperOnMainThread0010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build a object to SwapDirtyLayoutWrapperOnMainThread
     */
    RefPtr<LayoutWrapper> layoutWrapper = FRAME_NODE2->CreateLayoutWrapper(true, true);

    /**
     * @tc.steps: step2. callback SwapDirtyLayoutWrapperOnMainThread
     * @tc.expected: expect layoutWrapper is not nullptr.
     */
    FRAME_NODE2->SwapDirtyLayoutWrapperOnMainThread(layoutWrapper);
    EXPECT_NE(layoutWrapper, nullptr);
    layoutWrapper->SetActive(true);
    auto test = FRAME_NODE2->IsActive();

    /**
     * @tc.steps: step3. callback SwapDirtyLayoutWrapperOnMainThread
     * @tc.expected: expect isActive_ is false.
     */
    FRAME_NODE2->SwapDirtyLayoutWrapperOnMainThread(layoutWrapper);
    EXPECT_TRUE(test);
}

/**
 * @tc.name: FrameNodeTestNg_AdjustGridOffset0011
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeAdjustGridOffset0011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build a object to AdjustGridOffset
     * @tc.expected: expect active is true.
     */
    FRAME_NODE2->SetActive(true);
    bool active = FRAME_NODE2->IsActive();
    FRAME_NODE2->AdjustGridOffset();
    EXPECT_TRUE(active);

    FRAME_NODE2->SetParent(FRAME_NODE_PARENT);
    FRAME_NODE2->GetAncestorNodeOfFrame(false);

    FRAME_NODE2->SetActive(false);

    /**
     * @tc.steps: step2. build a object to AdjustGridOffset
     * @tc.expected: expect active1 is false.
     */
    bool active1 = FRAME_NODE2->IsActive();
    FRAME_NODE2->AdjustGridOffset();
    EXPECT_FALSE(active1);
}

/**
 * @tc.name: FrameNodeTestNg_SetOnAreaChangeCallback0012
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeSetOnAreaChangeCallback0012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build a object to SetOnAreaChangeCallback
     * @tc.expected: expect The function is run ok.
     */
    OnAreaChangedFunc callback = [](const RectF& oldRect, const OffsetF& oldOrigin, const RectF& rect,
                                     const OffsetF& origin) {};
    FRAME_NODE2->SetOnAreaChangeCallback(std::move(callback));
    EXPECT_NE(FRAME_NODE2->lastFrameRect_, nullptr);
    EXPECT_NE(FRAME_NODE2->lastParentOffsetToWindow_, nullptr);

    /**
     * @tc.steps: step2.test while callback is nullptr
     * @tc.expected:expect The function is run ok.
     */
    FRAME_NODE2->lastFrameRect_ = nullptr;
    FRAME_NODE2->lastParentOffsetToWindow_ = nullptr;
    FRAME_NODE2->SetOnAreaChangeCallback(nullptr);
    EXPECT_NE(FRAME_NODE2->lastFrameRect_, nullptr);
    EXPECT_NE(FRAME_NODE2->lastParentOffsetToWindow_, nullptr);
}

/**
 * @tc.name: FrameNodeTestNg_TriggerOnAreaChangeCallback0013
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTriggerOnAreaChangeCallback0013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set a flag and init a callback(onAreaChanged)
     */
    bool flag = false;
    OnAreaChangedFunc onAreaChanged = [&flag](const RectF& oldRect, const OffsetF& oldOrigin, const RectF& rect,
                                          const OffsetF& origin) { flag = !flag; };

    /**
     * @tc.steps: step2. call TriggerOnAreaChangeCallback before set callback
     * @tc.expected: expect flag is still false
     */
    FRAME_NODE2->TriggerOnAreaChangeCallback(TIMESTAMP_1);
    EXPECT_FALSE(flag);

    /**
     * @tc.steps: step3.set callback and release lastParentOffsetToWindow_
     * @tc.expected: expect flag is still false
     */
    FRAME_NODE2->GetOrCreateEventHub<EventHub>()->SetOnAreaChanged(std::move(onAreaChanged));
    FRAME_NODE2->lastParentOffsetToWindow_ = nullptr;
    FRAME_NODE2->TriggerOnAreaChangeCallback(TIMESTAMP_2);
    EXPECT_FALSE(flag);

    /**
     * @tc.steps: step4. release lastFrameRect_
     * @tc.expected: expect flag is still false
     */
    FRAME_NODE2->lastFrameRect_ = nullptr;
    FRAME_NODE2->TriggerOnAreaChangeCallback(TIMESTAMP_3);
    EXPECT_FALSE(flag);

    /**
     * @tc.steps: step5.set lastParentOffsetToWindow_ and lastFrameRect_
     * @tc.expected: expect flag is still false
     */
    FRAME_NODE2->lastParentOffsetToWindow_ = std::make_unique<OffsetF>();
    FRAME_NODE2->lastFrameRect_ = std::make_unique<RectF>();
    FRAME_NODE2->TriggerOnAreaChangeCallback(TIMESTAMP_4);
    EXPECT_FALSE(flag);
}

/**
 * @tc.name: FrameNodeTestNg_TriggerVisibleAreaChangeCallback0014
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTriggerVisibleAreaChangeCallback0014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build a object to TriggerVisibleAreaChangeCallback
     * @tc.expected: expect The function is run ok.
     */
    VisibleCallbackInfo callbackInfo;
    FRAME_NODE2->SetVisibleAreaUserCallback({ 0.0f }, callbackInfo);
    FRAME_NODE2->TriggerVisibleAreaChangeCallback(1);

    /**
     * @tc.steps: step2. callback SetParent
     * @tc.expected: expect parent is same with parentNode.
     */
    auto parentNode = AceType::MakeRefPtr<FrameNode>("test", -1, AceType::MakeRefPtr<Pattern>(), false);
    FRAME_NODE2->SetParent(FRAME_NODE3);
    FRAME_NODE2->TriggerVisibleAreaChangeCallback(2);
    auto parent = FRAME_NODE2->GetParent();
    EXPECT_EQ(parent, 1);

    auto parentNode1 = FrameNode::CreateFrameNode("parent", 2, AceType::MakeRefPtr<Pattern>());
    RefPtr<FrameNode> frameNodes[3] = { parentNode1, nullptr, nullptr };
    FRAME_NODE2->TriggerVisibleAreaChangeCallback(3);
    auto parent1 = FRAME_NODE2->GetParent();
    EXPECT_EQ(parent1, 1);

    FRAME_NODE2->lastVisibleRatio_ = 1.0;
    FRAME_NODE2->TriggerVisibleAreaChangeCallback(4);

    /**
     * @tc.steps: step3. set onShow_ and call TriggerVisibleAreaChangeCallback
     * @tc.expected: expect GetOnShow is true and lastVisibleRatio_ is zero.
     */
    auto context = PipelineContext::GetCurrentContext();
    context->onShow_ = true;
    FRAME_NODE2->TriggerVisibleAreaChangeCallback(5);
    auto testNode_ = TestNode::CreateTestNode(101);
    FRAME_NODE3->SetParent(testNode_);
    FRAME_NODE3->isActive_ = true;
    FRAME_NODE2->TriggerVisibleAreaChangeCallback(6);
    FRAME_NODE3->layoutProperty_->UpdateVisibility(VisibleType::INVISIBLE);
    FRAME_NODE2->layoutProperty_->UpdateVisibility(VisibleType::VISIBLE);
    FRAME_NODE2->isActive_ = true;
    FRAME_NODE2->TriggerVisibleAreaChangeCallback(7);
    FRAME_NODE3->layoutProperty_->UpdateVisibility(VisibleType::VISIBLE);
    FRAME_NODE2->TriggerVisibleAreaChangeCallback(8);
    EXPECT_TRUE(context->GetOnShow());
    EXPECT_EQ(FRAME_NODE2->lastVisibleRatio_, 1);
}

/**
 * @tc.name: FrameNodeTestNg_CreateLayoutTask0015
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeCreateLayoutTask0015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build a object to CreateLayoutTask
     * @tc.expected: expect The function is run ok.
     */
    FRAME_NODE2->isLayoutDirtyMarked_ = true;
    FRAME_NODE2->CreateLayoutTask(true);
    EXPECT_FALSE(FRAME_NODE2->isLayoutDirtyMarked_);

    FRAME_NODE2->CreateLayoutTask(true);

    FRAME_NODE2->isLayoutDirtyMarked_ = true;
    FRAME_NODE2->CreateLayoutTask(false);
    EXPECT_FALSE(FRAME_NODE2->isLayoutDirtyMarked_);
}

/**
 * @tc.name: FrameNodeTestNg_CreateRenderTask0016
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeCreateRenderTask0016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build a object to CreateRenderTask
     * @tc.expected: expect The isRenderDirtyMarked_ is false.
     */
    FRAME_NODE2->isRenderDirtyMarked_ = true;
    FRAME_NODE2->CreateRenderTask(true);
    EXPECT_FALSE(FRAME_NODE2->isRenderDirtyMarked_);

    FRAME_NODE2->isRenderDirtyMarked_ = true;
    FRAME_NODE2->CreateRenderTask(false);

    FRAME_NODE2->CreateRenderTask(true);
    EXPECT_FALSE(FRAME_NODE2->isRenderDirtyMarked_);
}

/**
 * @tc.name: FrameNodeTestNg_UpdateLayoutPropertyFlag0018
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeUpdateLayoutPropertyFlag0018, TestSize.Level1)
{
    /**
     * @tc.steps: step1.call back UpdateLayoutPropertyFlag.
     * @tc.expected: expect selfFlag is same with PROPERTY_UPDATE_BY_CHILD_REQUEST.
     */
    FRAME_NODE2->layoutProperty_->propertyChangeFlag_ = PROPERTY_UPDATE_BY_CHILD_REQUEST;
    auto selfFlag = FRAME_NODE2->layoutProperty_->GetPropertyChangeFlag();
    FRAME_NODE2->UpdateLayoutPropertyFlag();
    EXPECT_EQ(selfFlag, PROPERTY_UPDATE_BY_CHILD_REQUEST);

    FRAME_NODE2->layoutProperty_->propertyChangeFlag_ = PROPERTY_UPDATE_BY_CHILD_REQUEST;
    FRAME_NODE2->AddChild(FRAME_NODE3);
    FRAME_NODE2->UpdateLayoutPropertyFlag();
    FRAME_NODE2->Clean();
}

/**
 * @tc.name: FrameNodeTestNg_UpdateChildrenLayoutWrapper0019
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeUpdateChildrenLayoutWrapper0019, TestSize.Level1)
{
    /**
     * @tc.steps: step1. AddChild for FRAME_NODE2 and callback UpdateChildrenLayoutWrapper.
     * @tc.expected: expect The UpdateLayoutWrapper is true.
     */
    FRAME_NODE2->AddChild(FRAME_NODE3);
    FRAME_NODE2->UpdateChildrenLayoutWrapper(FRAME_NODE2->UpdateLayoutWrapper(nullptr, true, true), true, true);
    FRAME_NODE2->Clean();
    EXPECT_TRUE(FRAME_NODE2->UpdateLayoutWrapper(nullptr, true, true));
}

/**
 * @tc.name: FrameNodeTestNg_MarkModifyDone0021
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeMarkModifyDone0021, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build a object to MarkModifyDone.
     * @tc.expected:expect The function is run ok.
     */
    FRAME_NODE2->MarkModifyDone();
    EXPECT_TRUE(FRAME_NODE2->isRestoreInfoUsed_);
    FRAME_NODE2->isRestoreInfoUsed_ = true;
    FRAME_NODE2->MarkModifyDone();
    EXPECT_TRUE(FRAME_NODE2->isRestoreInfoUsed_);
}

/**
 * @tc.name: FrameNodeTestNg_MarkNeedRender0022
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeMarkNeedRender0022, TestSize.Level1)
{
    /**
     * @tc.steps: step1. callback MarkNeedRenderOnly.
     * @tc.expected: expect The function is run ok.
     */
    FRAME_NODE2->MarkNeedRenderOnly();
    auto test = FRAME_NODE2->isRenderDirtyMarked_ = false;
    auto test1 = FRAME_NODE2->isLayoutDirtyMarked_ = false;
    FRAME_NODE2->MarkNeedRender(false);
    FRAME_NODE2->MarkNeedRender(true);
    EXPECT_FALSE(test);
    EXPECT_FALSE(test1);
}

/**
 * @tc.name: FrameNodeTestNg_IsNeedRequestParentMeasure0023
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeIsNeedRequestParentMeasure0023, TestSize.Level1)
{
    /**
     * @tc.steps: step1. callback IsNeedRequestParentMeasure.
     * @tc.expected: expect The function return value is true.
     */
    auto test = FRAME_NODE2->IsNeedRequestParentMeasure();
    EXPECT_TRUE(test);

    FRAME_NODE2->layoutProperty_->propertyChangeFlag_ = PROPERTY_UPDATE_BY_CHILD_REQUEST;
    FRAME_NODE2->IsNeedRequestParentMeasure();

    FRAME_NODE2->layoutProperty_->propertyChangeFlag_ = PROPERTY_UPDATE_BY_CHILD_REQUEST;
    FRAME_NODE2->layoutProperty_->calcLayoutConstraint_ = std::make_unique<MeasureProperty>();
    auto test1 = FRAME_NODE2->IsNeedRequestParentMeasure();
    EXPECT_TRUE(test1);
}

/**
 * @tc.name: FrameNodeTestNg_OnGenerateOneDepthVisibleFrameWithTransition0024
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeOnGenerateOneDepthVisibleFrameWithTransition0024, TestSize.Level1)
{
    /**
     * @tc.steps: step1. callback OnGenerateOneDepthVisibleFrameWithTransition.
     * @tc.expected: expect The function is run ok.
     */
    std::list<RefPtr<FrameNode>> visibleList;
    FRAME_NODE2->OnGenerateOneDepthVisibleFrameWithTransition(visibleList);

    /**
     * @tc.steps: step2.push the framenode to visibleList and callback OnGenerateOneDepthVisibleFrameWithTransition
     * @tc.expected: expect visibleList.size is 3.
     */
    visibleList.push_back(FRAME_NODE);
    FRAME_NODE3->OnGenerateOneDepthVisibleFrameWithTransition(visibleList);
    EXPECT_EQ(visibleList.size(), 3);
}

/**
 * @tc.name: FrameNodeTestNg_IsOutOfTouchTestRegion0025
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeIsOutOfTouchTestRegion0025, TestSize.Level1)
{
    /**
     * @tc.steps: step1. callback IsOutOfTouchTestRegion.
     * @tc.expected: expect The function return value is true.
     */
    PointF pointF;
    std::vector<RectF> rectF;
    TouchEvent touchEvent;
    auto test = FRAME_NODE2->IsOutOfTouchTestRegion(std::move(pointF), touchEvent);
    EXPECT_TRUE(test);

    auto test1 = FRAME_NODE2->InResponseRegionList(pointF, rectF);
    auto test2 = FRAME_NODE2->IsOutOfTouchTestRegion(std::move(pointF), touchEvent);
    EXPECT_FALSE(test1);
    EXPECT_TRUE(test2);
}

/**
 * @tc.name: FrameNodeTestNg_TouchTest0026
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTouchTest0026, TestSize.Level1)
{
    /**
     * @tc.steps: step1. callback TouchTest.
     * @tc.expected: expect The function return value is true.
     */
    PointF globalPoint;
    PointF parentLocalPoint;
    TouchRestrict touchRestrict;
    TouchTestResult result;
    ResponseLinkResult responseLinkResult;
    SystemProperties::debugEnabled_ = true;
    FRAME_NODE2->TouchTest(
        globalPoint, parentLocalPoint, parentLocalPoint, touchRestrict, result, 1, responseLinkResult);

    SystemProperties::debugEnabled_ = false;
    FRAME_NODE2->TouchTest(
        globalPoint, parentLocalPoint, parentLocalPoint, touchRestrict, result, 1, responseLinkResult);

    /**
     * @tc.steps: step2. set isActive_ and IsEnabled is false.
     * @tc.expected: expect The function return value is OUT_OF_REGION.
     */
    FRAME_NODE2->isActive_ = false;
    FRAME_NODE2->GetOrCreateEventHub<EventHub>()->SetEnabled(false);
    auto test = FRAME_NODE2->TouchTest(
        globalPoint, parentLocalPoint, parentLocalPoint, touchRestrict, result, 1, responseLinkResult);
    EXPECT_EQ(test, HitTestResult::OUT_OF_REGION);
}

/**
 * @tc.name: FrameNodeTestNg_AxisTest0027
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeAxisTest0027, TestSize.Level1)
{
    /**
     * @tc.steps: step1. callback AxisTest.
     * @tc.expected: expect inputEventHub_ is run not null.
     */
    const PointF globalPoint;
    const PointF parentLocalPoint;
    const PointF parentRevertPoint;
    TouchRestrict touchRestrict;
    AxisTestResult onAxisResult;
    FRAME_NODE2->GetOrCreateEventHub<EventHub>()->GetOrCreateInputEventHub();
    FRAME_NODE2->AxisTest(globalPoint, parentLocalPoint, parentRevertPoint, touchRestrict, onAxisResult);
    EXPECT_NE(FRAME_NODE2->GetOrCreateEventHub<EventHub>()->inputEventHub_, nullptr);
}

/**
 * @tc.name: FrameNodeTestNg0028
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeOnAccessibilityEvent0028, TestSize.Level1)
{
    /**
     * @tc.steps: step1. callback OnAccessibilityEvent.
     * @tc.expected: expect The function is true.
     */
    auto test = AceApplicationInfo::GetInstance().isAccessibilityEnabled_ = true;
    FRAME_NODE2->OnAccessibilityEvent(
        AccessibilityEventType::CHANGE, WindowsContentChangeTypes::CONTENT_CHANGE_TYPE_SUBTREE);
    FRAME_NODE2->OnAccessibilityEvent(AccessibilityEventType::TEXT_CHANGE, "", "");
    EXPECT_TRUE(test);

    /**
     * @tc.steps: step2. callback OnAccessibilityEvent.
     * @tc.expected: expect The function is false.
     */
    auto test1 = AceApplicationInfo::GetInstance().isAccessibilityEnabled_ = false;
    FRAME_NODE2->OnAccessibilityEvent(AccessibilityEventType::ACCESSIBILITY_FOCUSED);
    EXPECT_FALSE(test1);
}

/**
 * @tc.name: FrameNodeTestNg0029
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeOnAccessibilityEventForVirtualNode0029, TestSize.Level1)
{
    /**
     * @tc.steps: step1. callback OnAccessibilityEventForVirtualNode.
     * @tc.expected: expect The function is true.
     */
    AccessibilityEvent event;
    auto accessibilityId = 1;
    auto test = AceApplicationInfo::GetInstance().isAccessibilityEnabled_ = true;
    FRAME_NODE2->OnAccessibilityEventForVirtualNode(AccessibilityEventType::CHANGE, accessibilityId);
    EXPECT_TRUE(test);

    /**
     * @tc.steps: step2. callback OnAccessibilityEventForVirtualNode.
     * @tc.expected: expect The function is false.
     */
    auto test1 = AceApplicationInfo::GetInstance().isAccessibilityEnabled_ = false;
    FRAME_NODE2->OnAccessibilityEventForVirtualNode(AccessibilityEventType::FOCUS, accessibilityId);
    EXPECT_FALSE(test1);
}

/**
 * @tc.name: FrameNodeTestNg_MarkRemoving0029
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeMarkRemoving0029, TestSize.Level1)
{
    /**
     * @tc.steps: step1. callback MarkRemoving.
     * @tc.expected: expect The function return value is true.
     */
    FRAME_NODE2->SetParent(FRAME_NODE_PARENT);
    FRAME_NODE2->AddChild(FRAME_NODE3);
    FRAME_NODE2->layoutProperty_->UpdateGeometryTransition("id");
    auto mark = FRAME_NODE2->MarkRemoving();
    FRAME_NODE2->Clean();
    EXPECT_TRUE(mark);

    FRAME_NODE2->layoutProperty_ = nullptr;
    auto mark1 = FRAME_NODE2->MarkRemoving();
    EXPECT_FALSE(mark1);
}

/**
 * @tc.name: FrameNodeTestNg_CalculateCurrentVisibleRatio0030
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeCalculateCurrentVisibleRatio0030, TestSize.Level1)
{
    /**
     * @tc.steps: step1. callback RemoveLastHotZoneRect.
     * @tc.expected: step1. expect The function is run ok.
     */
    RectF visibleRect;
    RectF renderRect;
    FRAME_NODE2->CalculateCurrentVisibleRatio(visibleRect, renderRect);
    EXPECT_EQ(visibleRect.Width(), 0);
    EXPECT_EQ(renderRect.Width(), 0);

    /**
     * @tc.steps: step2. set wrong value and call CalculateCurrentVisibleRatio
     * @tc.expected: expect The function returns 0.
     */
    renderRect.SetWidth(-1);
    EXPECT_EQ(FRAME_NODE2->CalculateCurrentVisibleRatio(visibleRect, renderRect), 0);
    visibleRect.SetWidth(-1);
    EXPECT_EQ(FRAME_NODE2->CalculateCurrentVisibleRatio(visibleRect, renderRect), 0);
}

/**
 * @tc.name: FrameNodeTestNg_InitializePatternAndContext0032
 * @tc.desc: Test InitializePatternAndContext
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeInitializePatternAndContext0032, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create a node and set onMainTree_=false, then call InitializePatternAndContext
            and trigger the callback
     * @tc.expected: hasPendingRequest_ is true
     */
    auto one = FrameNode::GetOrCreateFrameNode("one", 11, []() { return AceType::MakeRefPtr<Pattern>(); });
    one->onMainTree_ = false;
    one->InitializePatternAndContext();
    auto renderContext_ = one->renderContext_;
    renderContext_->RequestNextFrame();
    EXPECT_TRUE(one->hasPendingRequest_);
}

/**
 * @tc.name: FrameNodeTestNg_ProcessAllVisibleCallback0033
 * @tc.desc: Test ProcessAllVisibleCallback
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeProcessAllVisibleCallback0033, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create a node and init a vector for preparing for args, then set a flag
     */
    auto one = FrameNode::GetOrCreateFrameNode("one", 11, []() { return AceType::MakeRefPtr<Pattern>(); });
    std::vector<double> visibleAreaRatios { 0.2, 0.8, 0.21, 0.79, 0.5 };
    int flag = 0;
    auto defaultCallback = [&flag](bool input1, double input2) { flag += 1; };
    VisibleCallbackInfo callbackInfo { defaultCallback, 1.0, false };

    /**
     * @tc.steps: step2. call ProcessAllVisibleCallback with 0.5 from 0
     * @tc.expected: flag is 1
     */
    one->ProcessAllVisibleCallback(visibleAreaRatios, callbackInfo, 0.5, 0);
    EXPECT_EQ(flag, 1);

    /**
     * @tc.steps: step3. call ProcessAllVisibleCallback with 0 from 0.5
     * @tc.expected: flag is 2
     */
    one->ProcessAllVisibleCallback(visibleAreaRatios, callbackInfo, 0, 0.5);
    EXPECT_EQ(flag, 2);

    /**
     * @tc.steps: step4. call ProcessAllVisibleCallback with 0 from 0
     * @tc.expected: flag is 2
     */
    one->ProcessAllVisibleCallback(visibleAreaRatios, callbackInfo, 0, 0);
    EXPECT_EQ(flag, 2);

    /**
     * @tc.steps: step5. call ProcessAllVisibleCallback with 1 from 0
     * @tc.expected: flag is 3
     */
    one->ProcessAllVisibleCallback(visibleAreaRatios, callbackInfo, 1, 0);
    EXPECT_EQ(flag, 3);

    /**
     * @tc.steps: step6. call ProcessAllVisibleCallback with 1 from 1
     * @tc.expected: flag is 3
     */
    one->ProcessAllVisibleCallback(visibleAreaRatios, callbackInfo, 1, 1);
    EXPECT_EQ(flag, 3);
}

/**
 * @tc.name: FrameNodeTestNg_AnimateHoverEffect0034
 * @tc.desc: Test AnimateHoverEffect
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeAnimateHoverEffect0034, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create a frame node and release inputEventHub_, then
            change hoverEffectType_ and call AnimateHoverEffect
     * @tc.expected: AnimateHoverEffectScale has been called
     */
    auto one = FrameNode::GetOrCreateFrameNode("one", 12, []() { return AceType::MakeRefPtr<Pattern>(); });
    one->GetOrCreateEventHub<EventHub>()->inputEventHub_ = nullptr;
    auto renderContext = AceType::DynamicCast<MockRenderContext>(one->renderContext_);
    EXPECT_CALL(*renderContext, AnimateHoverEffectScale(_));
    one->AnimateHoverEffect(false);
    auto inputEventHub = one->GetOrCreateEventHub<EventHub>()->GetOrCreateInputEventHub();
    inputEventHub->hoverEffectType_ = HoverEffectType::UNKNOWN;
    one->AnimateHoverEffect(false);
    inputEventHub->hoverEffectType_ = HoverEffectType::AUTO;
    one->AnimateHoverEffect(false);
    inputEventHub->hoverEffectType_ = HoverEffectType::SCALE;
    one->AnimateHoverEffect(false);
    inputEventHub->hoverEffectType_ = HoverEffectType::BOARD;
    one->AnimateHoverEffect(false);
    inputEventHub->hoverEffectType_ = HoverEffectType::OPACITY;
    one->AnimateHoverEffect(false);
    inputEventHub->hoverEffectType_ = HoverEffectType::NONE;
    one->AnimateHoverEffect(false);
}

/**
 * @tc.name: FrameNodeTestNg_CreateAnimatablePropertyFloat0035
 * @tc.desc: Test AnimateHoverEffect
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeCreateAnimatablePropertyFloat0035, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call CreateAnimatablePropertyFloat.
     * @tc.expected: expect GetRenderContext is not null.
     */
    FRAME_NODE->CreateAnimatablePropertyFloat(NAME, value, onCallbackEvent);

    FRAME_NODE->renderContext_ = AceType::MakeRefPtr<MockRenderContext>();
    FRAME_NODE->CreateAnimatablePropertyFloat(NAME, value, onCallbackEvent);

    /**
     * @tc.steps: step2. put value to map and call CreateAnimatablePropertyFloat.
     * @tc.expected: expect iter is not equal map.
     */
    FRAME_NODE->nodeAnimatablePropertyMap_.emplace("test", AceType::MakeRefPtr<NodeAnimatablePropertyBase>());
    FRAME_NODE->CreateAnimatablePropertyFloat(NAME, value, onCallbackEvent);
    auto iter = FRAME_NODE->nodeAnimatablePropertyMap_.find(NAME);
    auto map = FRAME_NODE->nodeAnimatablePropertyMap_.end();
    EXPECT_NE(iter, map);
}

/**
 * @tc.name: FrameNodeTestNg_UpdateAnimatablePropertyFloat0036
 * @tc.desc: Test AnimateHoverEffect
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeUpdateAnimatablePropertyFloat0036, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call UpdateAnimatablePropertyFloat.
     * @tc.expected: expect iter is not equal map.
     */
    FRAME_NODE->UpdateAnimatablePropertyFloat(NAME, value);
    FRAME_NODE->nodeAnimatablePropertyMap_.clear();
    FRAME_NODE->nodeAnimatablePropertyMap_.emplace("propertyName", AceType::MakeRefPtr<NodeAnimatablePropertyBase>());
    FRAME_NODE->UpdateAnimatablePropertyFloat(NAME, value);
    auto iter = FRAME_NODE->nodeAnimatablePropertyMap_.find(NAME);
    auto map = FRAME_NODE->nodeAnimatablePropertyMap_.end();
    EXPECT_NE(iter, map);

    /**
     * @tc.steps: step2. call UpdateAnimatablePropertyFloat and clear nodeAnimatablePropertyMap_.
     * @tc.expected: expect property is nullptr.
     */
    FRAME_NODE->nodeAnimatablePropertyMap_.clear();
    FRAME_NODE->UpdateAnimatablePropertyFloat(NAME, value);
    auto property = AceType::DynamicCast<NodeAnimatablePropertyFloat>(iter->second);
    EXPECT_EQ(property, nullptr);
}

/**
 * @tc.name: FrameNodeTestNg_CreateAnimatableArithmeticProperty0037
 * @tc.desc: Test AnimateHoverEffect
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeCreateAnimatableArithmeticProperty0037, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call CreateAnimatableArithmeticProperty.
     * @tc.expected: expect iter is not equal map.
     */
    RefPtr<CustomAnimatableArithmetic> value = AceType::MakeRefPtr<CustomAnimatableArithmetic>();
    std::function<void(const RefPtr<NG::CustomAnimatableArithmetic>&)> onCallbackEvent;
    FRAME_NODE->CreateAnimatableArithmeticProperty(NAME, value, onCallbackEvent);
    FRAME_NODE->nodeAnimatablePropertyMap_.emplace("test", AceType::MakeRefPtr<NodeAnimatablePropertyBase>());
    FRAME_NODE->CreateAnimatableArithmeticProperty(NAME, value, onCallbackEvent);
    auto iter = FRAME_NODE->nodeAnimatablePropertyMap_.find(NAME);
    auto map = FRAME_NODE->nodeAnimatablePropertyMap_.end();
    EXPECT_NE(iter, map);
}

/**
 * @tc.name: FrameNodeTestNg_UpdateAnimatableArithmeticProperty0038
 * @tc.desc: Test AnimateHoverEffect
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeUpdateAnimatableArithmeticProperty0038, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call UpdateAnimatableArithmeticProperty.
     * @tc.expected: expect iter is not equal map.
     */
    RefPtr<CustomAnimatableArithmetic> value = AceType::MakeRefPtr<CustomAnimatableArithmetic>();
    FRAME_NODE->UpdateAnimatableArithmeticProperty(NAME, value);
    FRAME_NODE->nodeAnimatablePropertyMap_.clear();

    FRAME_NODE->nodeAnimatablePropertyMap_.emplace("propertyName", AceType::MakeRefPtr<NodeAnimatablePropertyBase>());
    FRAME_NODE->UpdateAnimatableArithmeticProperty(NAME, value);
    auto iter = FRAME_NODE->nodeAnimatablePropertyMap_.find(NAME);
    auto map = FRAME_NODE->nodeAnimatablePropertyMap_.end();
    EXPECT_NE(iter, map);

    /**
     * @tc.steps: step2. call UpdateAnimatablePropertyFloat and clear nodeAnimatablePropertyMap_.
     * @tc.expected: expect property is nullptr.
     */
    FRAME_NODE->nodeAnimatablePropertyMap_.clear();
    FRAME_NODE->UpdateAnimatableArithmeticProperty("", value);
    auto property = AceType::DynamicCast<NodeAnimatableArithmeticProperty>(iter->second);
    EXPECT_EQ(property, nullptr);
}

/**
 * @tc.name: FrameNodeTestNg0039
 * @tc.desc: Test of FrameProxy
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNg0039, TestSize.Level1)
{
    /**
     * @tc.steps: step1. creat childNode、create LazyForEachNode
     * @tc.expected: childNode is not null
     */
    auto childNode = FrameNode::CreateFrameNode(
        "child", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    auto itemNode = FrameNode::CreateFrameNode(
        "itemNode", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    childNode->AddChild(itemNode);
    /**
     * @tc.steps: step2. call SetIsOverlayNode.
     * @tc.expected: change IsOverlayNode().
     */
    ConfigurationChange configurationChange;
    childNode->OnConfigurationUpdate(configurationChange);
    configurationChange.languageUpdate = true;
    childNode->OnConfigurationUpdate(configurationChange);
    configurationChange.colorModeUpdate = true;
    childNode->OnConfigurationUpdate(configurationChange);
    configurationChange.directionUpdate = true;
    childNode->OnConfigurationUpdate(configurationChange);
    configurationChange.dpiUpdate = true;
    childNode->OnConfigurationUpdate(configurationChange);
    configurationChange.fontUpdate = true;
    configurationChange.iconUpdate = true;
    configurationChange.skinUpdate = true;
    configurationChange.fontWeightScaleUpdate = true;
    childNode->OnConfigurationUpdate(configurationChange);
    configurationChange.fontScaleUpdate = true;
    childNode->OnConfigurationUpdate(configurationChange);

    childNode->SetBackgroundLayoutConstraint(itemNode);
    childNode->ForceUpdateLayoutPropertyFlag(PROPERTY_UPDATE_MEASURE_SELF);
    childNode->GetPaintRectWithTransform();
    childNode->GetTransformScale();
    childNode->SetJSViewActive(true);
    auto layoutProperty = childNode->GetLayoutProperty();
    EXPECT_FALSE(layoutProperty->IsOverlayNode());
    layoutProperty->SetIsOverlayNode(true);
    childNode->DumpOverlayInfo();
    EXPECT_TRUE(layoutProperty->IsOverlayNode());
}

/**
 * @tc.name: FrameNodeTestNg_SetOnAreaChangeCallback040
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, SetOnAreaChangeCallback040, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build a object to SetOnAreaChangeCallback
     * @tc.expected: expect cover branch lastFrameRect_ non null and function is run ok.
     */
    OnAreaChangedFunc callback = [](const RectF& oldRect, const OffsetF& oldOrigin, const RectF& rect,
                                     const OffsetF& origin) {};
    FRAME_NODE2->lastFrameRect_ = std::make_unique<RectF>();
    FRAME_NODE2->SetOnAreaChangeCallback(std::move(callback));
    EXPECT_NE(FRAME_NODE2->lastFrameRect_, nullptr);

    /**
     * @tc.steps: step2.test while callback is nullptr
     * @tc.expected:expect cover branch lastParentOffsetToWindow_ non null and function is run ok.
     */

    FRAME_NODE2->lastParentOffsetToWindow_ = std::make_unique<OffsetF>();
    FRAME_NODE2->SetOnAreaChangeCallback(nullptr);
    EXPECT_NE(FRAME_NODE2->lastParentOffsetToWindow_, nullptr);
}

/**
 * @tc.name: FrameNodeTestNg_SwapDirtyLayoutWrapperOnMainThread040
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, SwapDirtyLayoutWrapperOnMainThread040, TestSize.Level1)
{
    /**
     * @tc.steps: step1. creat frameNode and layoutProperty
     */
    RefPtr<LayoutWrapper> layoutWrapper = FRAME_NODE2->CreateLayoutWrapper(true, true);
    auto frameNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto layoutProperty = frameNode->GetLayoutProperty<LayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

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

    /**
     * @tc.steps: step4. updatae layoutConstraint and set eventHub_.
     * @tc.expected: expect cover branch eventHub_ non null and function is run ok .
     */
    auto layoutConstraintF_ = LayoutConstraintF();
    layoutConstraintF_.maxSize = CONTAINER_SIZE;
    layoutConstraintF_.percentReference = CONTAINER_SIZE;
    frameNode->geometryNode_->SetParentLayoutConstraint(layoutConstraintF_);
    layoutProperty->UpdateLayoutConstraint(layoutConstraintF_);

    frameNode->GetOrCreateEventHub<EventHub>()->GetOrCreateFocusHub();
    frameNode->SwapDirtyLayoutWrapperOnMainThread(layoutWrapper);
    EXPECT_NE(frameNode->eventHub_, nullptr);

    /**
     * @tc.steps: step5. set currentFocus_ is true and call SwapDirtyLayoutWrapperOnMainThread.
     * @tc.expected: expect cover branch IsCurrentFocus() is true and function is run ok .
     */
    frameNode->GetOrCreateEventHub<EventHub>()->GetOrCreateFocusHub()->currentFocus_ = true;
    frameNode->SwapDirtyLayoutWrapperOnMainThread(layoutWrapper);
    EXPECT_TRUE(frameNode->GetOrCreateEventHub<EventHub>()->GetOrCreateFocusHub()->IsCurrentFocus());
}

/**
 * @tc.name: FrameNodeTouchTest047
 * @tc.desc: Test method GeometryNodeToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTouchTest047, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct parameters.
     */
    std::unique_ptr<JsonValue> value = JsonUtil::Create(true);

    /**
     * @tc.steps: step2. construct parameters.
     * @tc.expected: expect cover branch layoutProperty_ is nullptr.
     */
    FRAME_NODE2->GeometryNodeToJsonValue(value, filter);
    EXPECT_EQ(FRAME_NODE2->layoutProperty_, nullptr);

    /**
     * @tc.steps: step3. set layoutProperty_ and call GeometryNodeToJsonValue.
     * @tc.expected: expect cover branch layoutProperty_ is not nullptr.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    FRAME_NODE2->layoutProperty_ = layoutProperty;
    FRAME_NODE2->GeometryNodeToJsonValue(value, filter);
    EXPECT_NE(FRAME_NODE2->layoutProperty_, nullptr);

    /**
     * @tc.steps: step4. set calcLayoutConstraint_ and call GeometryNodeToJsonValue.
     * @tc.expected: expect cover branch calcLayoutConstraint_ is not nullptr.
     */
    FRAME_NODE2->layoutProperty_->calcLayoutConstraint_ = std::make_unique<MeasureProperty>();

    FRAME_NODE2->GeometryNodeToJsonValue(value, filter);
    EXPECT_NE(FRAME_NODE2->layoutProperty_->calcLayoutConstraint_, nullptr);

    /**
     * @tc.steps: step5. set selfIdealSize and call GeometryNodeToJsonValue.
     * @tc.expected: expect cover branch selfIdealSize has value.
     */
    std::optional<CalcLength> len = CalcLength("auto");
    FRAME_NODE2->layoutProperty_->calcLayoutConstraint_->selfIdealSize = CalcSize(len, len);
    FRAME_NODE2->GeometryNodeToJsonValue(value, filter);
    EXPECT_NE(FRAME_NODE2->renderContext_, nullptr);

    FRAME_NODE2->layoutProperty_ = nullptr;
}

/**
 * @tc.name: FrameNodeTestNg_TriggerVisibleAreaChangeCallback048
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTriggerVisibleAreaChangeCallback048, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build a object to TriggerVisibleAreaChangeCallback
     * @tc.expected: expect The function is run ok.
     */
    VisibleCallbackInfo callbackInfo;
    constexpr uint32_t minInterval = 100; // 100ms
    int flag = 0;
    callbackInfo.callback = [&flag](bool input1, double input2) { flag += 1; };
    callbackInfo.period = minInterval;
    FRAME_NODE2->SetVisibleAreaUserCallback({ 0.2, 0.8, 0.21, 0.79, 0.5 }, callbackInfo);
    FRAME_NODE2->ProcessThrottledVisibleCallback(false);
    EXPECT_EQ(FRAME_NODE2->throttledCallbackOnTheWay_, false);
}

/**
 * @tc.name: FrameNodeTestNg_TriggerVisibleAreaChangeCallback049
 * @tc.desc: Test the function GetValidLeafChildNumber
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTriggerVisibleAreaChangeCallback049, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build a object to TriggerVisibleAreaChangeCallback
     * @tc.expected: expect The function is run ok.
     */
    int32_t nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    const RefPtr<FrameNode> node =
        FrameNode::CreateFrameNode("TriggerVisibleAreaChangeCallback001", nodeId, AceType::MakeRefPtr<Pattern>(), true);

    /**
     * @tc.steps2: Call the function GetValidLeafChildNumber.
     * @tc.expected: Value returned as expected.
     */
    EXPECT_EQ(FRAME_NODE2->GetValidLeafChildNumber(node, 1), 1);
    const RefPtr<FrameNode> GET_CHILD1 = FrameNode::CreateFrameNode("child1", 5, AceType::MakeRefPtr<Pattern>(), true);
    GET_CHILD1->UpdateInspectorId("child1");
    node->AddChild(GET_CHILD1);
    EXPECT_EQ(FRAME_NODE2->GetValidLeafChildNumber(node, 1), 1);

    const RefPtr<FrameNode> GET_CHILD2 = FrameNode::CreateFrameNode("child2", 6, AceType::MakeRefPtr<Pattern>(), true);
    GET_CHILD2->UpdateInspectorId("child2");
    node->AddChild(GET_CHILD2);
    EXPECT_EQ(FRAME_NODE2->GetValidLeafChildNumber(node, 3), 2);
}

/**
 * @tc.name: FrameNodeTestNg_TriggerVisibleAreaChangeCallback050
 * @tc.desc: Test the function MarkAndCheckNewOpIncNode
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTriggerVisibleAreaChangeCallback050, TestSize.Level1)
{
    /**
     * @tc.steps: step1. creat node and generate a node tree.
     */
    RefPtr<FrameNode> GET_PARENT = FrameNode::CreateFrameNode("parent", 4, AceType::MakeRefPtr<Pattern>());
    RefPtr<FrameNode> GET_CHILD1 = FrameNode::CreateFrameNode("child1", 5, AceType::MakeRefPtr<Pattern>());
    RefPtr<FrameNode> GET_CHILD2 = FrameNode::CreateFrameNode("child2", 6, AceType::MakeRefPtr<Pattern>());
    GET_PARENT->AddChild(GET_CHILD1);
    GET_PARENT->AddChild(GET_CHILD2);
    GET_CHILD1->MarkAndCheckNewOpIncNode(Axis::VERTICAL);
    EXPECT_FALSE(GET_PARENT->GetSuggestOpIncActivatedOnce());

    /**
     * @tc.steps2: set suggestOpIncByte_ and call the function MarkAndCheckNewOpIncNode.
     * @tc.expected: Value returned as expected.
     */
    GET_PARENT->suggestOpIncByte_ = 7;
    GET_CHILD1->SetSuggestOpIncActivatedOnce();
    GET_PARENT->SetSuggestOpIncActivatedOnce();
    GET_CHILD1->MarkAndCheckNewOpIncNode(Axis::VERTICAL);
    EXPECT_TRUE(GET_PARENT->GetSuggestOpIncActivatedOnce());
    GET_CHILD1->suggestOpIncByte_ = 1;
    GET_CHILD1->MarkAndCheckNewOpIncNode(Axis::VERTICAL);
}

/**
 * @tc.name: FrameNodeTouchTest051
 * @tc.desc: Test frameNode FindSuggestOpIncNode
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTouchTest051, TestSize.Level1)
{
    /**
     * @tc.steps: step1. initialize parameters.
     */
    std::string tag = "test";
    auto frameNode = FrameNode::CreateFrameNode(tag, 1, AceType::MakeRefPtr<Pattern>(), true);
    auto frameNode1 = FrameNode::CreateFrameNode("test1", 2, AceType::MakeRefPtr<Pattern>(), true);
    frameNode->AddChild(frameNode1);
    frameNode->GetBaselineDistance();

    /**
     * @tc.steps: step2. set frame size and call FindSuggestOpIncNode
     * @tc.expected: expect result value.
     */
    frameNode->geometryNode_->SetFrameSize(SizeF(20, 20));
    auto result = frameNode->FindSuggestOpIncNode(tag, SizeF(0, 0), 1, Axis::VERTICAL);
    EXPECT_EQ(result, 0);
    result = frameNode->FindSuggestOpIncNode(tag, SizeF(0, 0), 1, Axis::VERTICAL);
    EXPECT_EQ(result, 2);
    SystemProperties::debugEnabled_ = true;
    frameNode->suggestOpIncByte_ = 0;
    result = frameNode->FindSuggestOpIncNode(tag, SizeF(0, 0), 1, Axis::VERTICAL);
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: FrameNodeTestNg_TriggerVisibleAreaChangeCallback052
 * @tc.desc: Test the function IsOpIncValidNode
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTriggerVisibleAreaChangeCallback052, TestSize.Level1)
{
    /**
     * @tc.steps: step1. initialize parameters.
     */

    SizeF boundary(1, 1);
    int32_t childNumber = 2;

    /**
     * @tc.steps2: call the function IsOpIncValidNode.
     * @tc.expected: Value returned as expected.
     */
    auto result = FRAME_NODE2->IsOpIncValidNode(boundary, Axis::VERTICAL, childNumber);
    EXPECT_EQ(result, 0);

    FRAME_NODE2->geometryNode_->SetFrameSize(SizeF(20, 20));
    result = FRAME_NODE2->IsOpIncValidNode(boundary, Axis::VERTICAL, childNumber);
    EXPECT_EQ(result, 0);

    SizeF boundary1(40, 40);
    FRAME_NODE2->geometryNode_->SetFrameSize(SizeF(20, 20));
    result = FRAME_NODE2->IsOpIncValidNode(boundary1, Axis::VERTICAL, childNumber);
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: FrameNodeTestNg_TriggerVisibleAreaChangeCallback053
 * @tc.desc: Test the function MarkSuggestOpIncGroup
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTriggerVisibleAreaChangeCallback053, TestSize.Level1)
{
    /**
     * @tc.steps1: call the function MarkSuggestOpIncGroup.
     * @tc.expected: Value returned as expected.
     */
    EXPECT_TRUE(FRAME_NODE2->MarkSuggestOpIncGroup(true, true));

    FRAME_NODE2->SetCanSuggestOpInc(true);
    FRAME_NODE2->SetSuggestOpIncMarked(true);
    FRAME_NODE2->SetOpIncGroupCheckedThrough(true);
    EXPECT_TRUE(FRAME_NODE2->MarkSuggestOpIncGroup(true, true));

    FRAME_NODE2->SetSuggestOpIncMarked(false);
    FRAME_NODE2->SetCanSuggestOpInc(false);
    FRAME_NODE2->SetOpIncGroupCheckedThrough(false);
    EXPECT_TRUE(FRAME_NODE2->MarkSuggestOpIncGroup(true, true));
}

/**
 * @tc.name: FrameNodeTestNg_IsPaintRectWithTransformValid054
 * @tc.desc: Test frame node method IsPaintRectWithTransformValid
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeIsPaintRectWithTransformValid054, TestSize.Level1)
{
    /**
     * @tc.steps: step1. callback IsPaintRectWithTransformValid.
     * @tc.expected: expect The function return value is true when width or height is nearZero.
     */
    auto node = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto mockRenderContext = AceType::MakeRefPtr<MockRenderContext>();
    node->renderContext_ = mockRenderContext;

    mockRenderContext->rect_ = RectF(0, 0, 0, 10);
    mockRenderContext->paintRect_ = RectF(0, 0, 0, 10);
    auto test1 = node->IsPaintRectWithTransformValid();
    EXPECT_TRUE(test1);

    mockRenderContext->rect_ = RectF(0, 0, 10, 0);
    mockRenderContext->paintRect_ = RectF(0, 0, 10, 0);
    auto test2 = node->IsPaintRectWithTransformValid();
    EXPECT_TRUE(test2);

    mockRenderContext->rect_ = RectF(0, 0, 10, 10);
    mockRenderContext->paintRect_ = RectF(0, 0, 10, 10);
    auto test3 = node->IsPaintRectWithTransformValid();
    EXPECT_FALSE(test3);

    mockRenderContext->rect_ = RectF(0, 0, 0, 0);
    mockRenderContext->paintRect_ = RectF(0, 0, 0, 0);
    auto test4 = node->IsPaintRectWithTransformValid();
    EXPECT_TRUE(test4);
}

/**
 * @tc.name: FrameNodeTestNg_Predict001
 * @tc.desc: Test frame node method ResetPredictNodes
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodePredict001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. add predictNode to main node and delete main node.
     * @tc.expected: expect the predictNode is not layout dirty marked after main node desconstructed.
     */
    auto node = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto predictNode = FrameNode::CreateFrameNode("predict", 1, AceType::MakeRefPtr<Pattern>(), false);
    predictNode->SetLayoutDirtyMarked(true);
    node->AddPredictLayoutNode(predictNode);
    node.Reset();
    EXPECT_FALSE(predictNode->IsLayoutDirtyMarked());
}

/**
 * @tc.name: FrameNodeSetJSCustomProperty055
 * @tc.desc: Test SetJSCustomProperty isCNode true, expect result is false.
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeSetJSCustomProperty055, TestSize.Level1)
{
    /**
     * @tc.steps: step1. initialize parameters.
     */
    auto frameNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);

    /**
     * @tc.steps: step2. set isCNode true.
     * @tc.expected: expect result is false.
     */
    frameNode->setIsCNode(true);
    std::function<bool()> func = []() -> bool { return true; };
    std::function<std::string(const std::string&)> getFuncA = [](const std::string& key) -> std::string {
        return "getFuncA";
    };
    frameNode->SetJSCustomProperty(func, getFuncA);
    std::string getValue;
    bool result = frameNode->GetCapiCustomProperty("key", getValue);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: FrameNodeSetJSCustomProperty056
 * @tc.desc: Test SetJSCustomProperty isCNode false, expect result is false.
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeSetJSCustomProperty056, TestSize.Level1)
{
    /**
     * @tc.steps: step1. initialize parameters.
     */
    auto frameNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);

    /**
     * @tc.steps: step2. set isCNode false.
     * @tc.expected: expect result is false.
     */
    frameNode->setIsCNode(false);
    std::function<bool()> func = []() -> bool { return true; };
    std::function<std::string(const std::string&)> getFuncA = [](const std::string& key) -> std::string {
        return "getFuncA";
    };
    frameNode->SetJSCustomProperty(func, getFuncA);
    frameNode->setIsCNode(true);
    std::string getValue;
    bool result = frameNode->GetCapiCustomProperty("key", getValue);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: FrameNodeGetJSCustomProperty058
 * @tc.desc: Test GetJSCustomProperty getCustomProperty_ value getFuncA, expect result value getFuncA.
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeGetJSCustomProperty058, TestSize.Level1)
{
    /**
     * @tc.steps: step1. initialize parameters.
     */
    auto frameNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);

    /**
     * @tc.steps: step2. set getCustomProperty_ value getFuncA.
     * @tc.expected: expect result value getFuncA.
     */
    std::function<bool()> func = []() -> bool { return true; };
    std::function<std::string(const std::string&)> getFuncA = [](const std::string& key) -> std::string {
        return "getFuncA";
    };
    frameNode->SetJSCustomProperty(func, getFuncA);
    frameNode->SetCustomPropertyMapFlagByKey("key");
    std::string getValue;
    bool result = frameNode->GetJSCustomProperty("key", getValue);
    EXPECT_EQ(result, true);
    EXPECT_EQ(getValue, "getFuncA");
}

/**
 * @tc.name: FrameNodeGetJSCustomProperty059
 * @tc.desc: Test GetJSCustomProperty getCustomProperty_ nullptr
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeGetJSCustomProperty059, TestSize.Level1)
{
    /**
     * @tc.steps: step1. initialize parameters.
     */
    auto frameNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);

    /**
     * @tc.steps: step2. set getCustomProperty_ nullptr
     * @tc.expected: expect result GetJSCustomProperty false.
     */
    std::function<bool()> func = []() -> bool { return true; };
    frameNode->SetJSCustomProperty(func, nullptr);
    frameNode->SetCustomPropertyMapFlagByKey("key");
    std::string getValue;
    bool result = frameNode->GetJSCustomProperty("key", getValue);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: FrameNodeGetCapiCustomProperty060
 * @tc.desc: Test GetCapiCustomProperty no key value value value added.
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeGetCapiCustomProperty060, TestSize.Level1)
{
    /**
     * @tc.steps: step1. initialize parameters.
     */
    auto frameNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);

    /**
     * @tc.steps: step2. GetCapiCustomProperty
     * @tc.expected: expect result value false.
     */
    frameNode->setIsCNode(false);
    std::string value;
    bool result = frameNode->GetCapiCustomProperty("key", value);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: FrameNodeGetCapiCustomProperty061
 * @tc.desc: Test GetCapiCustomProperty the key value value value exists.
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeGetCapiCustomProperty061, TestSize.Level1)
{
    /**
     * @tc.steps: step1. initialize parameters.
     */
    auto frameNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);

    /**
     * @tc.steps: step2. add the key value as value1.
     * @tc.expected: expect result value1.
     */
    frameNode->setIsCNode(true);
    frameNode->AddCustomProperty("key", "value1");
    std::string value;
    bool result = frameNode->GetCapiCustomProperty("key", value);
    EXPECT_EQ(result, true);
    EXPECT_EQ(value, "value1");
}

/**
 * @tc.name: FrameNodeGetCapiCustomProperty062
 * @tc.desc: Test GetCapiCustomProperty the key value does not exist.
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeGetCapiCustomProperty062, TestSize.Level1)
{
    /**
     * @tc.steps: step1. initialize parameters.
     */
    auto frameNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);

    /**
     * @tc.steps: step2. set key is value1
     * @tc.expected: expect result value.
     */
    frameNode->setIsCNode(true);
    frameNode->AddCustomProperty("key", "value1");
    std::string value;
    bool result = frameNode->GetCapiCustomProperty("key1", value);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: FrameNodeRemoveCustomProperty063
 * @tc.desc: Test RemoveCustomProperty.
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeRemoveCustomProperty063, TestSize.Level1)
{
    /**
     * @tc.steps: step1. initialize parameters.
     */
    auto frameNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);

    /**
     * @tc.steps: step2. set key is value1, remove key.
     * @tc.expected: expect result false.
     */
    frameNode->setIsCNode(true);
    frameNode->AddCustomProperty("key", "value1");
    frameNode->RemoveCustomProperty("key");
    std::string value;
    bool result = frameNode->GetCapiCustomProperty("key", value);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: FrameNodeTestNg_OnAutoEventParamUpdate
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNg_OnAutoEventParamUpdate, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create framenode and initialize the params used in Test.
     */
    auto node = FrameNode::CreateFrameNode("childNode", 10, AceType::MakeRefPtr<Pattern>(), true);
    node->AttachToMainTree();
    node->GetRenderContext()->RequestNextFrame();
    EXPECT_TRUE(node->IsOnMainTree());

    int32_t nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    const RefPtr<FrameNode> parentNode =
        FrameNode::CreateFrameNode("RelativeContainer", nodeId, AceType::MakeRefPtr<Pattern>(), true);
    node->SetParent(AceType::WeakClaim(AceType::RawPtr(parentNode)));

    /**
     * @tc.steps: step2. call OnAutoEventParamUpdate.
     * @tc.expect: this parentNode is MarkDirtyNode, but this Tag() != "RelativeContainer"
     * this parentNode is not MarkDirtyNode
     */
    node->OnAutoEventParamUpdate("{\"$origin\":\"Tom\",\"$exposureCfg\":{\"ratio\":0.8,\"duration\":3000}}");
    EXPECT_EQ(parentNode->GetTag(), "RelativeContainer");
}

/**
 * @tc.name: FrameNodeTestNg065
 * @tc.desc: Test GetIsLayoutNode.
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNg065, TestSize.Level1)
{
    auto frameNode =
        FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    bool isLayoutNode = false;
    frameNode->isLayoutNode_ = isLayoutNode;
    bool result = frameNode->GetIsLayoutNode();
    EXPECT_EQ(result, isLayoutNode);

    isLayoutNode = false;
    frameNode->isLayoutNode_ = isLayoutNode;
    result = frameNode->GetIsLayoutNode();
    EXPECT_EQ(result, isLayoutNode);
}

/**
 * @tc.name: FrameNodeTestNg066
 * @tc.desc: Test GetIsFind.
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNg066, TestSize.Level1)
{
    auto frameNode =
        FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    bool isFind = true;
    frameNode->isFind_ = isFind;
    bool result = frameNode->GetIsFind();
    EXPECT_EQ(result, isFind);

    isFind = false;
    frameNode->isFind_ = isFind;
    result = frameNode->GetIsFind();
    EXPECT_EQ(result, isFind);
}

/**
 * @tc.name: FrameNodeTestNg067
 * @tc.desc: Test SetIsFind.
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNg067, TestSize.Level1)
{
    auto frameNode =
        FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    bool isFind = true;
    frameNode->SetIsFind(isFind);
    bool result = frameNode->GetIsFind();
    EXPECT_EQ(result, isFind);

    isFind = false;
    frameNode->SetIsFind(isFind);
    result = frameNode->GetIsFind();
    EXPECT_EQ(result, isFind);
}

/**
 * @tc.name: FrameNodeTestNg069
 * @tc.desc: Test CheckAutoSave.
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNg069, TestSize.Level1)
{
    auto frameNode =
        FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);

    auto pattern_ = frameNode->GetPattern();
    EXPECT_NE(pattern_, nullptr);
    bool result = frameNode->CheckAutoSave();
    EXPECT_EQ(result, pattern_->CheckAutoSave());

    pattern_ = nullptr;
    result = frameNode->CheckAutoSave();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: FrameNodeTestNg070
 * @tc.desc: Test RenderCustomChild.
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNg070, TestSize.Level1)
{
    auto frameNode =
        FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);

    int64_t deadline = 1;
    bool result = frameNode->RenderCustomChild(deadline);
    bool res = frameNode->UINode::RenderCustomChild(deadline);
    EXPECT_EQ(result, res);
}

/**
 * @tc.name: FrameNodeTestNg081
 * @tc.desc: Test GetOrCreateCommonNode.
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNg081, TestSize.Level1)
{
    bool isLayoutNode = true;
    auto commonOne =
        FrameNode::GetOrCreateCommonNode("commonOne", 1, isLayoutNode, []() { return AceType::MakeRefPtr<Pattern>(); });
    auto commonTwo = FrameNode::GetFrameNode("commonTwo", 1);
    EXPECT_NE(commonOne, nullptr);
    EXPECT_EQ(commonTwo, nullptr);

    /**
     * @tc.steps: step2. create FrameNode and set a callback
     * @tc.expect: call DestroyCallback while object is destroyed
     */
    bool flag = true;
    auto commonThree = FrameNode::GetOrCreateFrameNode("commonOne", 1, nullptr);
    ASSERT_NE(commonThree, nullptr);
    commonThree->PushDestroyCallbackWithTag([&flag]() { flag = !flag; }, "");
    commonThree = nullptr;
    EXPECT_FALSE(flag);
}

/**
 * @tc.name: FrameNodeTestNg082
 * @tc.desc: Test CreateCommonNode.
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNg082, TestSize.Level1)
{
    /* @tc.steps: step1. create commonNode and initialize the params used in Test.
      */
    bool isLayoutNode = false;
    auto commonNode =
        FrameNode::CreateCommonNode("CommonChildNode", 20, isLayoutNode, AceType::MakeRefPtr<Pattern>(), true);
    commonNode->AttachToMainTree();
    commonNode->GetRenderContext()->RequestNextFrame();
    EXPECT_TRUE(commonNode->IsOnMainTree());

    int32_t commonNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    const RefPtr<FrameNode> commonParentNode =
        FrameNode::CreateCommonNode("CommonRelativeContainer", commonNodeId, isLayoutNode,
        AceType::MakeRefPtr<Pattern>(), true);
    commonNode->SetParent(AceType::WeakClaim(AceType::RawPtr(commonParentNode)));

    /**
     * @tc.steps: step2. call OnInspectorIdUpdate .
     * @tc.expect: this commonParentNode is MarkDirtyNode, but this Tag() != "RelativeContainer"
     * this commonParentNode is not MarkDirtyNode
     */
    commonNode->OnInspectorIdUpdate("CommonRelativeContainer");
    EXPECT_EQ(commonParentNode->GetTag(), "CommonRelativeContainer");
}

/**
 * @tc.name: FrameNodeTestNg083
 * @tc.desc: Test RequestParentDirty.
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNg083, TestSize.Level1)
{
    /* @tc.steps: step1. create frameNodeTemp and initialize the params used in Test.
    */
    auto frameNodeTemp =
        FrameNode::CreateFrameNode("root", 2, AceType::MakeRefPtr<Pattern>(), true);

    /**
     * @tc.steps: step2. frameNodeTemp is a root node
     * @tc.expect: frameNodeTemp call RequestParentDirty
    */
    bool result = frameNodeTemp->FrameNode::RequestParentDirty();
    EXPECT_FALSE(result);

    /**
     * @tc.steps: step3. create childNode and  added to frameNodeTemp
     * @tc.expect: childNode call RequestParentDirty
     */
    auto childNode =
        FrameNode::CreateFrameNode("main", 3, AceType::MakeRefPtr<Pattern>(), false);
    frameNodeTemp->AddChild(childNode);
    result = childNode->FrameNode::RequestParentDirty();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: FrameNodeTestNg084
 * @tc.desc: Test AddCustomProperty.
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNg084, TestSize.Level1)
{
    /* @tc.steps: step1. create frameNode and initialize the params used in Test.
    */
    auto frameNode =
        FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    /**
     * @tc.steps: step2. setIsCNode true
     * @tc.expect: frameNode call AddCustomProperty
    */
    frameNode->setIsCNode(true);
    frameNode->AddCustomProperty("key1", "value1");
    std::string value;
    bool result = frameNode->GetCapiCustomProperty("key1", value);
    EXPECT_EQ(result, true);
    EXPECT_EQ(value, "value1");
}

/**
 * @tc.name: FrameNodeTestNg085
 * @tc.desc: Test GetActiveChildren.
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNg085, TestSize.Level1)
{
    /* @tc.steps: step1. create frameNode and initialize the params used in Test.
    */
    auto frameNode =
        FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    /**
     * @tc.steps: step2. create childNode1 and added to frameNode
     * @tc.expect: childNode1 setActive true
    */
    auto childNode1 =
        FrameNode::CreateFrameNode("main", 2, AceType::MakeRefPtr<Pattern>(), false);
    frameNode->AddChild(childNode1);
    childNode1->SetActive(true);
    /**
     * @tc.steps: step3. create childNode2 and added to frameNode
     * @tc.expect: childNode2 setActive false
    */
    auto childNode2 =
        FrameNode::CreateFrameNode("main", 3, AceType::MakeRefPtr<Pattern>(), false);
    frameNode->AddChild(childNode2);
    childNode2->SetActive(false);

    std::list<RefPtr<FrameNode>> list = frameNode->FrameNode::GetActiveChildren();
    EXPECT_EQ(list.size(), 1);
}

/**
 * @tc.name: FrameNodeTestNg086
 * @tc.desc: Test ChildrenUpdatedFrom.
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNg086, TestSize.Level1)
{
    /* @tc.steps: step1. create frameNode and initialize the params used in Test.
    */
    auto frameNode =
        FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    /**
     * @tc.steps: step2. childrenUpdatedFrom_ >= 0 and index > childrenUpdatedFrom_
     * @tc.expect: childrenUpdatedFrom_ do not change
    */
    frameNode->childrenUpdatedFrom_ = 0;
    int32_t index = 2;
    frameNode->FrameNode::ChildrenUpdatedFrom(index);
    int32_t currentIndex = frameNode->childrenUpdatedFrom_;
    EXPECT_EQ(currentIndex, 0);

    /**
     * @tc.steps: step3. childrenUpdatedFrom_ >= 0 and index < childrenUpdatedFrom_
     * @tc.expect: childrenUpdatedFrom_ is set to index
    */
    frameNode->childrenUpdatedFrom_ = 3;
    frameNode->FrameNode::ChildrenUpdatedFrom(index);
    currentIndex = frameNode->childrenUpdatedFrom_;
    EXPECT_EQ(currentIndex, 2);

    /**
     * @tc.steps: step3. childrenUpdatedFrom_ < 0
     * @tc.expect: childrenUpdatedFrom_ is set to index
    */
    frameNode->childrenUpdatedFrom_ = -1;
    frameNode->FrameNode::ChildrenUpdatedFrom(index);
    currentIndex = frameNode->childrenUpdatedFrom_;
    EXPECT_EQ(currentIndex, 2);
}

/**
 * @tc.name: FrameNodeTestNg091
 * @tc.desc: Test AddFrameNodeChangeInfoFlag
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNg091, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    frameNode->AddFrameNodeChangeInfoFlag(1 << 5);
    EXPECT_EQ(frameNode->GetChangeInfoFlag(), 1 << 5);
}

/**
 * @tc.name: FrameNodeTestNg092
 * @tc.desc: Test AddFrameNodeChangeInfoFlag
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNg092, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    frameNode->AddFrameNodeChangeInfoFlag(0);
    EXPECT_EQ(frameNode->GetChangeInfoFlag(), 0);
}

/**
 * @tc.name: FrameNodeTestNg093
 * @tc.desc: Test SetPaintNode
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNg093, TestSize.Level1)
{
    auto paintNode = FrameNode::CreateFrameNode("paintNodeTag", 2, AceType::MakeRefPtr<Pattern>(), true);
    auto frameNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    frameNode->SetPaintNode(paintNode);
    EXPECT_EQ(frameNode->GetPaintNode(), paintNode);
}

/**
 * @tc.name: FrameNodeTestNg094
 * @tc.desc: Test GetPaintNode
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNg094, TestSize.Level1)
{
    RefPtr<Pattern> pattern = AceType::MakeRefPtr<Pattern>();
    FrameNode frameNode("testTag", 1, pattern);
    RefPtr<FrameNode> paintNode = AceType::MakeRefPtr<FrameNode>("paintNodeTag", 2, pattern);
    frameNode.SetPaintNode(paintNode);
    const RefPtr<FrameNode>& result = frameNode.GetPaintNode();
    ASSERT_EQ(result, paintNode);
}

/**
 * @tc.name: FrameNodeTestNg095
 * @tc.desc: Test SetFocusPaintNode
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNg095, TestSize.Level1)
{
    auto focusPaintNode = FrameNode::CreateFrameNode("focusTag", 2, AceType::MakeRefPtr<Pattern>(), true);
    auto frameNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    frameNode->SetFocusPaintNode(focusPaintNode);
    EXPECT_EQ(frameNode->GetFocusPaintNode(), focusPaintNode);
}

/**
 * @tc.name: FrameNodeTestNg096
 * @tc.desc: Test GetFocusPaintNode
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNg096, TestSize.Level1)
{
    auto focusPaintNode = FrameNode::CreateFrameNode("focusPaintNode", 2, AceType::MakeRefPtr<Pattern>(), true);
    auto frameNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    frameNode->SetFocusPaintNode(focusPaintNode);
    EXPECT_EQ(frameNode->GetFocusPaintNode(), focusPaintNode);
}

/**
 * @tc.name: FrameNodeTestNg097
 * @tc.desc: Test IsDrawFocusOnTop
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNg097, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    EXPECT_FALSE(frameNode->IsDrawFocusOnTop());
}

/**
 * @tc.name: FrameNodeTestNg098
 * @tc.desc: Test IsDrawFocusOnTop true value
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNg098, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<NG::AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    accessibilityProperty->SetFocusDrawLevel(static_cast<int32_t>(FocusDrawLevel::TOP));
    EXPECT_TRUE(frameNode->IsDrawFocusOnTop());
}

/**
 * @tc.name: FrameNodeGetOrCreate001
 * @tc.desc: Test FrameNodeGetOrCreate001.
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeGetOrCreate001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create root node.
     * @tc.expected: expect is not nullptr.
     */
    auto frameNode1 = FrameNode::CreateFrameNodeWithTree("Column", 1, AceType::MakeRefPtr<Pattern>());
    EXPECT_NE(frameNode1, nullptr);
    EXPECT_EQ(frameNode1->GetId(), 1);

     /**
     * @tc.steps: step2. attach node to main tree.
     * @tc.expected: expect IsOnMainTree is true.
     */
    EXPECT_EQ(frameNode1->IsOnMainTree(), false);
    frameNode1->AttachToMainTree();
    EXPECT_EQ(frameNode1->IsOnMainTree(), true);
    auto pattern = [] {return AceType::MakeRefPtr<Pattern>();};
    /**
     * @tc.steps: step3. create child node.
     * @tc.expected: expect is not nullptr.
     */
    auto frameNode2 = FrameNode::GetOrCreateFrameNode("Column", 2, pattern);
    EXPECT_NE(frameNode2, nullptr);
    EXPECT_EQ(frameNode2->GetId(), 2);
    /**
     * @tc.steps: step4. create same node.
     * @tc.expected: node2 == node 3.
     */
    auto frameNode3 = FrameNode::GetOrCreateFrameNode("Column", 2, pattern);
    EXPECT_EQ(frameNode3, frameNode2);
    /**
     * @tc.steps: step5. create child node.
     * @tc.expected: expect is not nullptr.
     */
    frameNode1->AddChild(frameNode2, 1, true);
    auto children = frameNode1->GetChildren();
    EXPECT_EQ(children.size(), 1);
}

/**
 * @tc.name: FrameNodeGetOrCreate002
 * @tc.desc: Test FrameNodeGetOrCreate002.
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeGetOrCreate002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create root node.
     * @tc.expected: expect is not nullptr.
     */
    auto frameNode1 = FrameNode::CreateFrameNodeWithTree("Row", 1, AceType::MakeRefPtr<Pattern>());
    EXPECT_NE(frameNode1, nullptr);
    EXPECT_EQ(frameNode1->GetId(), 1);
    /**
     * @tc.steps: step2. create child node.
     * @tc.expected: expect is not nullptr.
     */
    auto frameNode2 = FrameNode::GetOrCreateFrameNode("Row", 2, []() { return AceType::MakeRefPtr<Pattern>(); });

    EXPECT_NE(frameNode2, nullptr);
    EXPECT_EQ(frameNode2->GetId(), 2);
    frameNode1->AddChild(frameNode2, 1, true);
    /**
     * @tc.steps: step3. create child node.
     * @tc.expected: expect is not nullptr.
     */
    auto frameNode3 = FrameNode::GetOrCreateFrameNode("Row", 3, []() { return AceType::MakeRefPtr<Pattern>(); });
    EXPECT_NE(frameNode2, nullptr);
    EXPECT_EQ(frameNode2->GetId(), 2);
    frameNode2->AddChild(frameNode2, 1, true);
    /**
     * @tc.steps: step4. test GetFrameNodeOnly
     * @tc.expected: expect is not nullptr.
     */
    auto frameNode4 = FrameNode::GetFrameNodeOnly("Row", 3);
    EXPECT_NE(frameNode4, nullptr);
    /**
     * @tc.steps: step5. test GetFrameNodeChildByIndex
     * @tc.expected: expect is not nullptr.
     */
    auto frameNode5 = frameNode1->GetFrameNodeChildByIndex(0);
    EXPECT_NE(frameNode5, nullptr);
    auto frameNode6 = frameNode2->GetFrameNodeChildByIndex(0);
    EXPECT_EQ(frameNode6, nullptr);
    /**
     * @tc.steps: step6. test FrameCount
     * @tc.expected: expect is not nullptr.
     */
    auto frameCount = frameNode1->FrameCount();
    EXPECT_EQ(frameCount, 1);
}

/**
 * @tc.name: FrameNodeTestNG089
 * @tc.desc: Test DumpSimplifyCommonInfo.
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNG089, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    const NG::RectF rect = { 10.0f, 20.0f, 30.0f, 40.0f };
    frameNode->GetGeometryNode()->frame_.rect_ = rect;
    frameNode->GetRenderContext()->UpdateBackgroundColor(Color::BLUE);
    frameNode->GetLayoutProperty()->UpdateVisibility(VisibleType::INVISIBLE);
    frameNode->GetLayoutProperty()->SetLayoutRect(rect);
    frameNode->GetLayoutProperty()->calcLayoutConstraint_ = std::make_unique<MeasureProperty>();
    frameNode->GetLayoutProperty()->padding_ = std::make_unique<PaddingProperty>();
    LayoutConstraintF constraint;
    constraint.selfIdealSize.SetHeight(30.0f);
    constraint.selfIdealSize.SetWidth(20.0f);
    frameNode->GetLayoutProperty()->contentConstraint_ = constraint;
    LayoutConstraintF layoutConstraint;
    layoutConstraint.percentReference.SetWidth(10.0f);
    frameNode->GetGeometryNode()->SetParentLayoutConstraint(layoutConstraint);
    std::unique_ptr<JsonValue> json = JsonUtil::Create(true);
    frameNode->DumpInfo(json);
    std::string res = json->ToString();

    EXPECT_EQ(res.length() < 9000, true);
}

/**
 * @tc.name: FrameNodeTestNG300
 * @tc.desc: Test GetPatternTypeName.
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNG300, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     * @tc.expected: expect is not nullptr.
     */
    auto frameNode =
        FrameNode::GetOrCreateFrameNode("one", 1, []() { return AceType::MakeRefPtr<Pattern>(); });
    EXPECT_NE(frameNode, nullptr);
    /**
     * @tc.steps: step2. create pattern_.
     * @tc.expected: make sure pattern_ is not nullptr.
     */
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    frameNode->pattern_ = textPattern;
    auto res = frameNode->GetPatternTypeName();
    EXPECT_NE(res, nullptr);
}

/**
 * @tc.name: FrameNodeTestNG301
 * @tc.desc: Test GetLayoutPropertyTypeName.
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNG301, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     * @tc.expected: expect is not nullptr.
     */
    auto frameNode =
        FrameNode::CreateFrameNode("page", 1, AceType::MakeRefPtr<Pattern>(), true);
    EXPECT_NE(frameNode, nullptr);
    /**
     * @tc.steps: step2. create layoutProperty_ is nullptr.
     * @tc.expected: expect is not nullptr.
     */
    frameNode->layoutProperty_ = nullptr;
    auto res = frameNode->GetLayoutPropertyTypeName();
    EXPECT_EQ(res, nullptr);
}

/**
 * @tc.name: FrameNodeTestNG302
 * @tc.desc: Test GetLayoutPropertyTypeName.
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNG302, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     * @tc.expected: expect is not nullptr.
     */
    auto frameNode =
        FrameNode::CreateFrameNode("page", 1,  AceType::MakeRefPtr<Pattern>(), true);
    EXPECT_NE(frameNode, nullptr);
    /**
     * @tc.steps: step2. create layoutProperty_ is nullptr.
     * @tc.expected: expect is not nullptr.
     */
    frameNode->layoutProperty_->UpdateVisibility(VisibleType::VISIBLE);
    auto res = frameNode->GetLayoutPropertyTypeName();
    EXPECT_NE(res, nullptr);
}

/**
 * @tc.name: FrameNodeTestNG303
 * @tc.desc: Test GetLayoutPropertyTypeName.
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNG303, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     * @tc.expected: expect is not nullptr.
     */
    auto frameNode =
        FrameNode::CreateFrameNode("page", 1,  AceType::MakeRefPtr<Pattern>(), true);
    EXPECT_NE(frameNode, nullptr);
    /**
     * @tc.steps: step2. create layoutProperty_ is nullptr.
     * @tc.expected: expect is not nullptr.
     */
    BorderWidthProperty overCountBorderWidth;
    overCountBorderWidth.SetBorderWidth(Dimension(10, DimensionUnit::VP));
    frameNode->layoutProperty_->UpdateBorderWidth(overCountBorderWidth);
    auto res = frameNode->GetLayoutPropertyTypeName();
    EXPECT_NE(res, nullptr);
}

/**
 * @tc.name: FrameNodeTestNG304
 * @tc.desc: Test GetPaintPropertyTypeName.
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNG304, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     * @tc.expected: expect is not nullptr.
     */
    auto frameNode =
        FrameNode::CreateFrameNode("page", 1,  AceType::MakeRefPtr<Pattern>(), true);
    EXPECT_NE(frameNode, nullptr);
    /**
     * @tc.steps: step2. create paintProperty_ is nullptr.
     * @tc.expected: expect is not nullptr.
     */
    frameNode->paintProperty_ = nullptr;
    auto res = frameNode->GetPaintPropertyTypeName();
    EXPECT_EQ(res, nullptr);
}

/**
 * @tc.name: FrameNodeTestNG305
 * @tc.desc: Test GetPaintPropertyTypeName.
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNG305, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     * @tc.expected: expect is not nullptr.
     */
    auto frameNode =
        FrameNode::CreateFrameNode("page", 1,  AceType::MakeRefPtr<Pattern>(), true);
    EXPECT_NE(frameNode, nullptr);
    /**
     * @tc.steps: step2. create paintProperty_ is nullptr.
     * @tc.expected: expect is not nullptr.
     */
    RefPtr<MarqueePaintProperty> marqueePaintProperty = AceType::MakeRefPtr<MarqueePaintProperty>();
    frameNode->paintProperty_ = marqueePaintProperty;
    auto res = frameNode->GetPaintPropertyTypeName();
    EXPECT_NE(res, nullptr);
}

/**
 * @tc.name: FrameNodeTestNG306
 * @tc.desc: Test GetKitNode.
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNG306, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     * @tc.expected: expect is not nullptr.
     */
    auto frameNode =
        FrameNode::CreateFrameNode("page", 1,  AceType::MakeRefPtr<Pattern>(), true);
    EXPECT_NE(frameNode, nullptr);
    /**
     * @tc.steps: step2. create kitNode_ is nullptr.
     * @tc.expected: expect is nullptr.
     */
    frameNode->kitNode_ = nullptr;
    auto res = frameNode->GetKitNode();
    EXPECT_EQ(res, nullptr);
}

/**
 * @tc.name: FrameNodeTestNG307
 * @tc.desc: Test GetKitNode.
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNG307, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     * @tc.expected: expect is not nullptr.
     */
    auto frameNode =
        FrameNode::CreateFrameNode("page", 1,  AceType::MakeRefPtr<Pattern>(), true);
    EXPECT_NE(frameNode, nullptr);
    /**
     * @tc.steps: step2. create kitNode_ is nullptr.
     * @tc.expected: expect is nullptr.
     */
    auto kitNode = frameNode->GetKitNode();
    auto kitNodeToFrameNode = AceType::DynamicCast<Kit::FrameNodeImpl>(kitNode);
    frameNode->SetKitNode(kitNodeToFrameNode);
    auto res = frameNode->GetKitNode();
    EXPECT_EQ(res, kitNodeToFrameNode);
}

/**
 * @tc.name: FrameNodeTestNG308
 * @tc.desc: Test GetKitNode.
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNG308, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     * @tc.expected: expect is not nullptr.
     */
    auto frameNode =
        FrameNode::CreateFrameNode("page", 1,  AceType::MakeRefPtr<Pattern>(), true);
    EXPECT_NE(frameNode, nullptr);
    /**
     * @tc.steps: step2. create kitNode_ is not nullptr.
     * @tc.expected: expect is not nullptr.
     */
    auto pattern = AceType::MakeRefPtr<Pattern>();
    int32_t nodeId = 1;
    auto kitNode = NG::ColumnModelNG::CreateFrameNode(nodeId);
    auto kitNodeToFrameNode = AceType::DynamicCast<Kit::FrameNodeImpl>(kitNode);
    frameNode->SetKitNode(kitNodeToFrameNode);
    auto res = frameNode->GetKitNode();
    EXPECT_EQ(res, kitNodeToFrameNode);
}

/**
 * @tc.name: FrameNodeTestNG309
 * @tc.desc: Test GetKitNode.
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNG309, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     * @tc.expected: expect is not nullptr.
     */
    auto frameNode =
        FrameNode::CreateFrameNode("page", 1,  AceType::MakeRefPtr<Pattern>(), true);
    EXPECT_NE(frameNode, nullptr);
    /**
     * @tc.steps: step2. create geometryNode_ is nullptr.
     * @tc.expected: expect is nullptr.
     */
    auto geometryNode= nullptr;
    frameNode->SetGeometryNode(geometryNode);
    auto res = frameNode->GetGeometryNode();
    EXPECT_EQ(res, nullptr);
}

/**
 * @tc.name: FrameNodeTestNG310
 * @tc.desc: Test GetKitNode.
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNG310, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     * @tc.expected: expect is not nullptr.
     */
    auto frameNode =
        FrameNode::CreateFrameNode("page", 1,  AceType::MakeRefPtr<Pattern>(), true);
    EXPECT_NE(frameNode, nullptr);
    /**
     * @tc.steps: step2. create geometryNode_ is nullptr.
     * @tc.expected: expect is nullptr.
     */
    auto geometryNode= AceType::MakeRefPtr<GeometryNode>();
    frameNode->SetGeometryNode(geometryNode);
    auto res = frameNode->GetGeometryNode();
    EXPECT_NE(res, nullptr);
    EXPECT_EQ(res, geometryNode);
}

/**
 * @tc.name: FrameNodeTestNg311
 * @tc.desc: Test OnAttachAtapter.
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNg311, TestSize.Level1)
{
    auto frameNode =
        FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto childNode1 =
        FrameNode::CreateFrameNode("main", 2, AceType::MakeRefPtr<Pattern>(), false);
    auto pattern_ = frameNode->GetPattern();
    EXPECT_NE(pattern_, nullptr);
    bool result = pattern_->OnAttachAtapter(frameNode, childNode1);
    EXPECT_EQ(result, false);
    pattern_ = nullptr;
}
} // namespace OHOS::Ace::NG
