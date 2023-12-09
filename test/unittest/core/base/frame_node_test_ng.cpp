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
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

#define protected public
#define private public

#include "base/geometry/dimension.h"
#include "base/geometry/dimension_rect.h"
#include "base/geometry/ng/offset_t.h"
#include "base/json/json_util.h"
#include "base/log/dump_log.h"
#include "base/memory/referenced.h"
#include "base/utils/system_properties.h"
#include "core/common/ace_application_info.h"
#include "core/components_ng/animation/geometry_transition.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/frame_scene_status.h"
#include "core/components_ng/event/focus_hub.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "core/components_ng/syntax/if_else_model_ng.h"
#include "test/mock/core/render/mock_render_context.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/event/mouse_event.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const RefPtr<FrameNode> FRAME_NODE_PARENT =
    FrameNode::CreateFrameNode("parent", 0, AceType::MakeRefPtr<Pattern>(), true);
const RefPtr<FrameNode> FRAME_NODE = FrameNode::CreateFrameNode("one", 1, AceType::MakeRefPtr<Pattern>());
const RefPtr<FrameNode> FRAME_NODE2 = FrameNode::CreateFrameNode("two", 2, AceType::MakeRefPtr<Pattern>());
const RefPtr<FrameNode> FRAME_NODE3 =
    FrameNode::CreateFrameNode("three", 3, AceType::MakeRefPtr<LinearLayoutPattern>(false));
std::string srcimages = "";

const std::string NAME = "propertyName";
float value = 1.0;
const std::function<void(float)> onCallbackEvent = [](float) {};

const float CONTAINER_WIDTH = 600.0f;
const float CONTAINER_HEIGHT = 1000.0f;
const SizeF CONTAINER_SIZE(CONTAINER_WIDTH, CONTAINER_HEIGHT);

const OffsetF OFFSETF { 1.0, 1.0 };
} // namespace
class FrameNodeTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
};

void FrameNodeTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
}

void FrameNodeTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

class TestNode : public UINode {
    DECLARE_ACE_TYPE(TestNode, UINode);

public:
    static RefPtr<TestNode> CreateTestNode(int32_t nodeId)
    {
        auto node = MakeRefPtr<TestNode>(nodeId);
        return node;
    }

    bool IsAtomicNode() const override
    {
        return true;
    }

    explicit TestNode(int32_t nodeId) : UINode("TestNode", nodeId) {}
    ~TestNode() override = default;
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

    /**
     * @tc.steps: step2. create FrameNode and set a callback
     * @tc.expect: call DestroyCallback while object is destroyed
     */
    bool flag = false;
    auto three = FrameNode::GetOrCreateFrameNode("one", 1, nullptr);
    ASSERT_NE(three, nullptr);
    three->PushDestroyCallback([&flag]() { flag = !flag; });
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
        ElementRegister::GetInstance()->GetOrCreateGeometryTransition("test", false);
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
    int32_t nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto node = FrameNode::CreateFrameNode("node", nodeId, AceType::MakeRefPtr<Pattern>(), true);

    auto parentNode = FrameNode::CreateFrameNode("LocationButton", nodeId + 1, AceType::MakeRefPtr<Pattern>(), true);
    /**
     * @tc.steps: step 2. call AddFRCSceneInfo .
     * @tc.expect: rosenContext set scene and speed, no expect
     */
    node->AddFRCSceneInfo("test", 0, SceneStatus::START);
    node->AddFRCSceneInfo("test", 0, SceneStatus::RUNNING);

    /**
     * @tc.steps: step 3. call CheckSecurityComponentStatus .
     * @tc.expect: rect.size ++
     */
    EXPECT_FALSE(node->HaveSecurityComponent());
    std::list<RefPtr<FrameNode>> nodeList;
    nodeList.push_back(parentNode);
    node->frameChildren_ = { nodeList.begin(), nodeList.end() };
    std::vector<RectF> rect;
    node->CheckSecurityComponentStatus(rect);
    EXPECT_EQ(rect.size(), 2);
    rect.clear();
    rect.emplace_back(RectF(0, 0, 0, 0));
    parentNode->CheckSecurityComponentStatus(rect);
    EXPECT_EQ(rect.size(), 2);

    /**
     * @tc.steps: step 3. call HaveSecurityComponent.
     * @tc.expect: Different GetTag() return false or true.
     */
    EXPECT_TRUE(parentNode->HaveSecurityComponent());
    EXPECT_TRUE(node->HaveSecurityComponent());
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
                auto result = childNode->TouchTest(
                    globalPoint, parentLocalPointOne, parentLocalPointOne, touchRestrict, touchTestResult, 0);
                auto expectedResult =
                    (hitTestModeofGrandChild == HitTestMode::HTMBLOCK || hitTestModeofChild == HitTestMode::HTMBLOCK)
                        ? HitTestResult::STOP_BUBBLING
                        : HitTestResult::BUBBLING;
                result = node->TouchTest(
                    globalPoint, parentLocalPointOne, parentLocalPointOne, touchRestrict, touchTestResult, 0);
                EXPECT_NE(result, expectedResult);
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

    auto wrapper = FRAME_NODE->CreatePaintWrapper();
    EXPECT_EQ(wrapper, nullptr);

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
    EXPECT_NE(FRAME_NODE2->eventHub_, nullptr);

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
    FRAME_NODE->ToJsonValue(jsonValue);
    EXPECT_TRUE(jsonValue);

    /**
     * @tc.steps: step2. build a object to jsonValue and call FromJson
     * @tc.expected: expect The function is run ok.
     */
    FRAME_NODE->FromJson(jsonValue);
    FRAME_NODE->renderContext_ = nullptr;
    FRAME_NODE->eventHub_->focusHub_ = nullptr;
    auto jsonValue2 = JsonUtil::Create(true);
    FRAME_NODE->ToJsonValue(jsonValue2);
    FRAME_NODE->eventHub_ = nullptr;
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
    FRAME_NODE2->IsResponseRegion();
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
 * @tc.name: FrameNodeTestNg_OnVisibleChange009
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeOnVisibleChange009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build a object to OnVisibleChange
     * @tc.expected: expect The FRAME_NODE2 is not nullptr.
     */
    FRAME_NODE2->AddChild(FRAME_NODE3);
    FRAME_NODE2->OnVisibleChange(false);
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
    FRAME_NODE2->GetAncestorNodeOfFrame();

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
    FRAME_NODE2->TriggerOnAreaChangeCallback();
    EXPECT_FALSE(flag);

    /**
     * @tc.steps: step3.set callback and release lastParentOffsetToWindow_
     * @tc.expected: expect flag is still false
     */
    FRAME_NODE2->eventHub_->SetOnAreaChanged(std::move(onAreaChanged));
    FRAME_NODE2->lastParentOffsetToWindow_ = nullptr;
    FRAME_NODE2->TriggerOnAreaChangeCallback();
    EXPECT_FALSE(flag);

    /**
     * @tc.steps: step4. release lastFrameRect_
     * @tc.expected: expect flag is still false
     */
    FRAME_NODE2->lastFrameRect_ = nullptr;
    FRAME_NODE2->TriggerOnAreaChangeCallback();
    EXPECT_FALSE(flag);

    /**
     * @tc.steps: step5.set lastParentOffsetToWindow_ and lastFrameRect_
     * @tc.expected: expect flag is still false
     */
    FRAME_NODE2->lastParentOffsetToWindow_ = std::make_unique<OffsetF>();
    FRAME_NODE2->lastFrameRect_ = std::make_unique<RectF>();
    FRAME_NODE2->TriggerOnAreaChangeCallback();
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
    FRAME_NODE2->AddVisibleAreaUserCallback(0.0f, callbackInfo);
    FRAME_NODE2->TriggerVisibleAreaChangeCallback();

    /**
     * @tc.steps: step2. callback SetParent
     * @tc.expected: expect parent is same with parentNode.
     */
    auto parentNode = AceType::MakeRefPtr<FrameNode>("test", -1, AceType::MakeRefPtr<Pattern>(), false);
    FRAME_NODE2->SetParent(FRAME_NODE3);
    FRAME_NODE2->TriggerVisibleAreaChangeCallback();
    auto parent = FRAME_NODE2->GetParent();
    EXPECT_EQ(parent, 1);

    auto parentNode1 = FrameNode::CreateFrameNode("parent", 2, AceType::MakeRefPtr<Pattern>());
    RefPtr<FrameNode> frameNodes[3] = { parentNode1, nullptr, nullptr };
    FRAME_NODE2->TriggerVisibleAreaChangeCallback();
    auto parent1 = FRAME_NODE2->GetParent();
    EXPECT_EQ(parent1, 1);

    FRAME_NODE2->lastVisibleRatio_ = 1.0;
    FRAME_NODE2->TriggerVisibleAreaChangeCallback();

    /**
     * @tc.steps: step3. set onShow_ and call TriggerVisibleAreaChangeCallback
     * @tc.expected: expect GetOnShow is true and lastVisibleRatio_ is zero.
     */
    auto context = PipelineContext::GetCurrentContext();
    context->onShow_ = true;
    FRAME_NODE2->TriggerVisibleAreaChangeCallback();
    auto testNode_ = TestNode::CreateTestNode(101);
    FRAME_NODE3->SetParent(testNode_);
    FRAME_NODE3->isActive_ = true;
    FRAME_NODE2->TriggerVisibleAreaChangeCallback();
    FRAME_NODE3->layoutProperty_->UpdateVisibility(VisibleType::INVISIBLE);
    FRAME_NODE2->layoutProperty_->UpdateVisibility(VisibleType::VISIBLE);
    FRAME_NODE2->isActive_ = true;
    FRAME_NODE2->TriggerVisibleAreaChangeCallback();
    FRAME_NODE3->layoutProperty_->UpdateVisibility(VisibleType::VISIBLE);
    FRAME_NODE2->TriggerVisibleAreaChangeCallback();
    EXPECT_TRUE(context->GetOnShow());
    EXPECT_EQ(FRAME_NODE2->lastVisibleRatio_, 0);
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
 * @tc.name: FrameNodeTestNg_GetParentGlobalOffset0017
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeGetParentGlobalOffset0017, TestSize.Level1)
{
    /**
     * @tc.steps: step1. SetParent for FRAME_NODE2 and callback GetParentGlobalOffset.
     * @tc.expected: expect The parent is same with 1.
     */
    FRAME_NODE2->GetParentGlobalOffset();
    FRAME_NODE2->SetParent(FRAME_NODE_PARENT);
    auto parent = FRAME_NODE2->GetAncestorNodeOfFrame();
    FRAME_NODE2->GetParentGlobalOffset();
    EXPECT_EQ(parent, 1);
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
 * @tc.name: FrameNodeTestNg_PostTask0020
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodePostTask0020, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build a object to PostTask
     * @tc.expected: expect taskTypeis is UI.
     */
    auto callback = []() { srcimages = "test"; };
    TaskExecutor::TaskType taskType { 1 };

    FRAME_NODE2->PostTask(callback, std::move(taskType));
    EXPECT_EQ(taskType, TaskExecutor::TaskType::UI);
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
    auto test = FRAME_NODE2->IsOutOfTouchTestRegion(std::move(pointF), 0);
    EXPECT_FALSE(test);

    auto test1 = FRAME_NODE2->InResponseRegionList(pointF, rectF);
    auto test2 = FRAME_NODE2->IsOutOfTouchTestRegion(std::move(pointF), 0);
    EXPECT_FALSE(test1);
    EXPECT_FALSE(test2);
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
    SystemProperties::debugEnabled_ = true;
    FRAME_NODE2->TouchTest(globalPoint, parentLocalPoint, parentLocalPoint, touchRestrict, result, 1);

    SystemProperties::debugEnabled_ = false;
    FRAME_NODE2->TouchTest(globalPoint, parentLocalPoint, parentLocalPoint, touchRestrict, result, 1);

    /**
     * @tc.steps: step2. set isActive_ and IsEnabled is false.
     * @tc.expected: expect The function return value is OUT_OF_REGION.
     */
    FRAME_NODE2->isActive_ = false;
    FRAME_NODE2->eventHub_->SetEnabled(false);
    auto test = FRAME_NODE2->TouchTest(globalPoint, parentLocalPoint, parentLocalPoint, touchRestrict, result, 1);
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
    AxisTestResult onAxisResult;
    FRAME_NODE2->eventHub_->GetOrCreateInputEventHub();
    FRAME_NODE2->AxisTest(globalPoint, parentLocalPoint, onAxisResult);
    EXPECT_NE(FRAME_NODE2->eventHub_->inputEventHub_, nullptr);
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
 * @tc.name: FrameNodeTestNg00_OnVisibleAreaChangeCallback31
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeOnVisibleAreaChangeCallback31, TestSize.Level1)
{
    /**
     * @tc.steps: step1. callback RemoveLastHotZoneRect.
     * @tc.expected: step1. expect The function is run ok.
     */
    VisibleCallbackInfo callbackInfo;
    bool isHandled = false;
    FRAME_NODE2->OnVisibleAreaChangeCallback(callbackInfo, true, 1.0, isHandled);
    EXPECT_TRUE(callbackInfo.isCurrentVisible);
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
     * @tc.steps: step1. create a node and init a map for preparing for args, then set a flag
     */
    auto one = FrameNode::GetOrCreateFrameNode("one", 11, []() { return AceType::MakeRefPtr<Pattern>(); });
    std::unordered_map<double, VisibleCallbackInfo> visibleAreaCallbacks;
    auto insert = [&visibleAreaCallbacks](double callbackRatio, std::function<void(bool, double)> callback,
                      bool isCurrentVisible = false, double visibleRatio = 1.0) {
        VisibleCallbackInfo callbackInfo { callback, visibleRatio, isCurrentVisible };
        visibleAreaCallbacks.emplace(callbackRatio, callbackInfo);
    };
    bool flag = false;
    auto defaultCallback = [&flag](bool input1, double input2) { flag = !flag; };
    insert(0.2, std::function<void(bool, double)>(defaultCallback), false);
    insert(0.8, std::function<void(bool, double)>(defaultCallback), true);
    insert(0.21, std::function<void(bool, double)>(defaultCallback), true);
    insert(0.79, std::function<void(bool, double)>(defaultCallback), false);
    insert(0.5, std::function<void(bool, double)>(defaultCallback), false);

    /**
     * @tc.steps: step2. call ProcessAllVisibleCallback with .5
     * @tc.expected: flag is true
     */
    one->ProcessAllVisibleCallback(visibleAreaCallbacks, 0.5);
    EXPECT_TRUE(flag);

    /**
     * @tc.steps: step3. call ProcessAllVisibleCallback with 0
     * @tc.expected: flag turns false
     */
    visibleAreaCallbacks.clear();
    insert(0, std::function<void(bool, double)>(defaultCallback), false);
    one->ProcessAllVisibleCallback(visibleAreaCallbacks, 0);
    EXPECT_FALSE(flag);

    /**
     * @tc.steps: step4. call ProcessAllVisibleCallback with 0
     * @tc.expected: flag turns true
     */
    visibleAreaCallbacks.clear();
    insert(0, std::function<void(bool, double)>(defaultCallback), true);
    one->ProcessAllVisibleCallback(visibleAreaCallbacks, 0);
    EXPECT_TRUE(flag);

    /**
     * @tc.steps: step5. call ProcessAllVisibleCallback with 0
     * @tc.expected: flag turns false
     */
    visibleAreaCallbacks.clear();
    insert(1, std::function<void(bool, double)>(defaultCallback), false);
    one->ProcessAllVisibleCallback(visibleAreaCallbacks, 1);
    EXPECT_FALSE(flag);

    /**
     * @tc.steps: step6. call ProcessAllVisibleCallback with 1
     * @tc.expected: flag turns true
     */
    visibleAreaCallbacks.clear();
    insert(1, std::function<void(bool, double)>(defaultCallback), true);
    one->ProcessAllVisibleCallback(visibleAreaCallbacks, 1);
    EXPECT_TRUE(flag);
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
    one->eventHub_->inputEventHub_ = nullptr;
    auto renderContext = AceType::DynamicCast<MockRenderContext>(one->renderContext_);
    EXPECT_CALL(*renderContext, AnimateHoverEffectScale(_));
    one->AnimateHoverEffect(false);
    auto inputEventHub = one->eventHub_->GetOrCreateInputEventHub();
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
 * @tc.desc: Test of FramePorxy
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
    AccessibilityManager::OnConfigurationChange configurationChange;
    childNode->OnConfigurationUpdate(configurationChange);
    configurationChange.languageUpdate = true;
    childNode->OnConfigurationUpdate(configurationChange);
    configurationChange.colorModeUpdate = true;
    childNode->OnConfigurationUpdate(configurationChange);
    configurationChange.directionUpdate = true;
    childNode->OnConfigurationUpdate(configurationChange);
    configurationChange.dpiUpdate = true;
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

    frameNode->eventHub_->GetOrCreateFocusHub();
    frameNode->SwapDirtyLayoutWrapperOnMainThread(layoutWrapper);
    EXPECT_NE(frameNode->eventHub_, nullptr);

    /**
     * @tc.steps: step5. set currentFocus_ is true and call SwapDirtyLayoutWrapperOnMainThread.
     * @tc.expected: expect cover branch IsCurrentFocus() is true and function is run ok .
     */
    frameNode->eventHub_->GetOrCreateFocusHub()->currentFocus_ = true;
    frameNode->SwapDirtyLayoutWrapperOnMainThread(layoutWrapper);
    EXPECT_TRUE(frameNode->eventHub_->GetOrCreateFocusHub()->IsCurrentFocus());
}

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
    /**
     * @tc.steps: step2. set isActive_ and debugEnabled_ is true and FRAME_NODE2 eventHub is HTMBLOCK.
     * @tc.expected: expect The function return value is STOP_BUBBLING.
     */
    FRAME_NODE2->isActive_ = true;
    FRAME_NODE2->eventHub_->SetEnabled(true);
    SystemProperties::debugEnabled_ = true;
    auto eventHub = FRAME_NODE2->GetOrCreateGestureEventHub();
    eventHub->SetHitTestMode(HitTestMode::HTMBLOCK);
    auto test = FRAME_NODE2->TouchTest(globalPoint, parentLocalPoint, parentLocalPoint, touchRestrict, result, 1);
    EXPECT_EQ(test, HitTestResult::STOP_BUBBLING);
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

    /**
     * @tc.steps: step2. set debugEnabled_ is true.
     */
    FRAME_NODE2->isActive_ = true;
    FRAME_NODE2->eventHub_->SetEnabled(true);
    SystemProperties::debugEnabled_ = true;
    auto test = FRAME_NODE2->TouchTest(globalPoint, parentLocalPoint, parentLocalPoint, touchRestrict, result, 1);

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
    test = FRAME_NODE2->TouchTest(globalPoint, parentLocalPoint, parentLocalPoint, touchRestrict, result, 1);
    EXPECT_EQ(test, HitTestResult::STOP_BUBBLING);
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
    auto test = FRAME_NODE2->TouchTest(globalPoint, parentLocalPoint, parentLocalPoint, touchRestrict, result, 1);
    EXPECT_EQ(test, HitTestResult::STOP_BUBBLING);
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
    FRAME_NODE2->GeometryNodeToJsonValue(value);
    EXPECT_EQ(FRAME_NODE2->layoutProperty_, nullptr);

    /**
     * @tc.steps: step3. set layoutProperty_ and call GeometryNodeToJsonValue.
     * @tc.expected: expect cover branch layoutProperty_ is not nullptr.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    FRAME_NODE2->layoutProperty_ = layoutProperty;
    FRAME_NODE2->GeometryNodeToJsonValue(value);
    EXPECT_NE(FRAME_NODE2->layoutProperty_, nullptr);

    /**
     * @tc.steps: step4. set calcLayoutConstraint_ and call GeometryNodeToJsonValue.
     * @tc.expected: expect cover branch calcLayoutConstraint_ is not nullptr.
     */
    FRAME_NODE2->layoutProperty_->calcLayoutConstraint_ = std::make_unique<MeasureProperty>();

    FRAME_NODE2->GeometryNodeToJsonValue(value);
    EXPECT_NE(FRAME_NODE2->layoutProperty_->calcLayoutConstraint_, nullptr);

    /**
     * @tc.steps: step5. set selfIdealSize and call GeometryNodeToJsonValue.
     * @tc.expected: expect cover branch selfIdealSize has value.
     */
    std::optional<CalcLength> len = CalcLength("auto");
    FRAME_NODE2->layoutProperty_->calcLayoutConstraint_->selfIdealSize = CalcSize(len, len);
    FRAME_NODE2->GeometryNodeToJsonValue(value);
    EXPECT_NE(FRAME_NODE2->renderContext_, nullptr);

    FRAME_NODE2->layoutProperty_ = nullptr;
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
 * @tc.name: FrameNodeTestNg_TriggerVisibleAreaChangeCallback001
 * @tc.desc: Test frame node method TriggerVisibleAreaChangeCallback
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, TriggerVisibleAreaChangeCallback001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set onMainTree_ is true
     * @tc.expected: cover branch IsOnMainTree is true.
     */
    FRAME_NODE2->onMainTree_ = true;
    FRAME_NODE2->InitializePatternAndContext();

    /**
     * @tc.steps: step2. set layoutProperty_
     * @tc.expected: cover branch call IsVisible() right.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    FRAME_NODE2->layoutProperty_ = layoutProperty;

    /**
     * @tc.steps: step3. call TriggerVisibleAreaChangeCallback
     * @tc.expected: expect IsOnMainTree is true.
     */
    FRAME_NODE2->TriggerVisibleAreaChangeCallback(false);
    EXPECT_TRUE(FRAME_NODE2->IsOnMainTree());

    /**
     * @tc.steps: step4. set parentNode and set isActive_ is true
     * @tc.expected: expect cover branch parentFrame isActive_ is true.
     */
    auto& posProperty = FRAME_NODE2->renderContext_->GetOrCreatePositionProperty();
    posProperty->UpdateOffset(OffsetT<Dimension>());
    int32_t nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    const RefPtr<FrameNode> parentNode =
        FrameNode::CreateFrameNode("TriggerVisibleAreaChangeCallback001", nodeId, AceType::MakeRefPtr<Pattern>(), true);
    parentNode->isActive_ = true;
    FRAME_NODE2->SetParent(AceType::WeakClaim(AceType::RawPtr(parentNode)));

    /**
     * @tc.steps: step5. call TriggerVisibleAreaChangeCallback
     * @tc.expected: expect parentNode isActive_ is true.
     */
    FRAME_NODE2->TriggerVisibleAreaChangeCallback(false);
    EXPECT_TRUE(parentNode->isActive_);

    /**
     * @tc.steps: step6. set parentNode2 and call TriggerVisibleAreaChangeCallback
     * @tc.expected: expect parentNode FRAME_NODE2 is true.
     */
    const RefPtr<FrameNode> parentNode2 = nullptr;
    FRAME_NODE2->SetParent(AceType::WeakClaim(AceType::RawPtr(parentNode2)));
    FRAME_NODE2->TriggerVisibleAreaChangeCallback(false);
    EXPECT_TRUE(FRAME_NODE2->isActive_);
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
        ElementRegister::GetInstance()->GetOrCreateGeometryTransition("test", false);
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
} // namespace OHOS::Ace::NG
