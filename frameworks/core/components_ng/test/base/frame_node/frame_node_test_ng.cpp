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
#include "base/log/dump_log.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/animation/geometry_transition.h"
#include "base/memory/referenced.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/components_ng/syntax/if_else_model_ng.h"
#include "base/utils/system_properties.h"
#include "core/common/ace_application_info.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const RefPtr<FrameNode> FRAME_NODE_PARENT =
    FrameNode::CreateFrameNode("parent", 0, AceType::MakeRefPtr<Pattern>(), true);
const RefPtr<FrameNode> FRAME_NODE = FrameNode::CreateFrameNode("one", 1, AceType::MakeRefPtr<Pattern>());
const RefPtr<FrameNode> FRAME_NODE2 = FrameNode::CreateFrameNode("two", 2, AceType::MakeRefPtr<Pattern>());
const RefPtr<FrameNode> FRAME_NODE3 = FrameNode::CreateFrameNode("three", 3, AceType::MakeRefPtr<Pattern>());
std::string srcimages = "";
} // namespace
class FrameNodeTestNg : public testing::Test {
public:
    static void SetUpTestCase() {}
    static void TearDownTestCase() {}
    void SetUp() {}
    void TearDown() {}
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

/**
 * @tc.name: FrameNodeTestNg005
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNg005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build CreateFrameNodeWithTree to the obj
     * @tc.expected: step1. expect obj is not same with nullptr
     */
    auto one = FrameNode::CreateFrameNodeWithTree("main", 10, AceType::MakeRefPtr<Pattern>());
    EXPECT_NE(one, nullptr);
}

/**
 * @tc.name: FrameNodeTestNg006
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNg006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. callback DumpInfo
     * @tc.expected: step1. expect The function is run ok.
     */
    FrameNode frameNode("main", 10, AceType::MakeRefPtr<Pattern>(), true);
    LayoutProperty layoutProperty;
    frameNode.DumpInfo();

    frameNode.layoutProperty_->UpdatePadding(PaddingPropertyT<CalcLength>());
    frameNode.layoutProperty_->GetPaddingProperty();
    frameNode.DumpInfo();
    EXPECT_EQ(layoutProperty.padding_, nullptr);

    frameNode.layoutProperty_->UpdateMargin(PaddingProperty());
    frameNode.layoutProperty_->GetMarginProperty();
    frameNode.DumpInfo();
    EXPECT_EQ(layoutProperty.margin_, nullptr);

    frameNode.layoutProperty_->UpdateBorderWidth(BorderWidthPropertyT<Dimension>());
    frameNode.layoutProperty_->GetBorderWidthProperty();
    frameNode.DumpInfo();
    EXPECT_EQ(layoutProperty.borderWidth_, nullptr);
}

/**
 * @tc.name: FrameNodeTestNg007
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNg007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build a object to jsonValue
     * @tc.expected: step1. expect The function is run ok.
     */
    FrameNode frameNode("main", 10, AceType::MakeRefPtr<Pattern>(), true);
    auto jsonValue = JsonUtil::Create(true);
    frameNode.ToJsonValue(jsonValue);
    EXPECT_TRUE(jsonValue);
}

/**
 * @tc.name: FrameNodeTestNg008
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNg008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build a object to OnAttachToMainTree
     * @tc.expected: step1. expect The function is run ok.
     */
    FRAME_NODE2->IsResponseRegion();
    FRAME_NODE2->OnAttachToMainTree();

    auto request = FRAME_NODE2->hasPendingRequest_ = true;
    FRAME_NODE2->OnAttachToMainTree();
    EXPECT_TRUE(request);
}

/**
 * @tc.name: FrameNodeTestNg009
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNg009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build a object to OnVisibleChange
     * @tc.expected: step1. expect The function is run ok.
     */
    FRAME_NODE2->AddChild(FRAME_NODE3);
    FRAME_NODE2->OnVisibleChange(false);
    FRAME_NODE2->Clean();
    EXPECT_NE(FRAME_NODE2, nullptr);
}

/**
 * @tc.name: FrameNodeTestNg0010
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNg0010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build a object to SwapDirtyLayoutWrapperOnMainThread
     * @tc.expected: step1. expect The function is run ok.
     */
    RefPtr<LayoutWrapper> layoutWrapper = FRAME_NODE2->CreateLayoutWrapper(true, true);
    /**
     * @tc.expected: step2. expect layoutWrapper is not nullptr.
     */
    FRAME_NODE2->SwapDirtyLayoutWrapperOnMainThread(layoutWrapper);
    EXPECT_NE(layoutWrapper, nullptr);
    layoutWrapper->SetActive(true);
    auto test = FRAME_NODE2->IsActive();

    /**
     * @tc.expected: step3. expect isActive_ is false.
     */
    FRAME_NODE2->SwapDirtyLayoutWrapperOnMainThread(layoutWrapper);
    EXPECT_FALSE(test);
}

/**
 * @tc.name: FrameNodeTestNg0011
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNg0011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build a object to AdjustGridOffset
     * @tc.expected: step1. expect The function is run ok.
     */
    FRAME_NODE2->SetActive(true);
    bool active = FRAME_NODE2->IsActive();
    FRAME_NODE2->AdjustGridOffset();
    EXPECT_TRUE(active);

    FRAME_NODE2->SetParent(FRAME_NODE_PARENT);
    FRAME_NODE2->GetAncestorNodeOfFrame();

    FRAME_NODE2->SetActive(false);

    bool active1 = FRAME_NODE2->IsActive();
    FRAME_NODE2->AdjustGridOffset();
    EXPECT_FALSE(active1);
}

/**
 * @tc.name: FrameNodeTestNg0012
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNg0012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build a object to SetOnAreaChangeCallback
     * @tc.expected: step1. expect The function is run ok.
     */
    OnAreaChangedFunc callback;
    FRAME_NODE2->SetOnAreaChangeCallback(std::move(callback));
    EXPECT_NE(FRAME_NODE2->lastFrameRect_, nullptr);
    EXPECT_NE(FRAME_NODE2->lastParentOffsetToWindow_, nullptr);
}

/**
 * @tc.name: FrameNodeTestNg0013
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNg0013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build a object to TriggerOnAreaChangeCallback
     * @tc.expected: step1. expect The function is run ok.
     */
    OnAreaChangedFunc onAreaChanged;
    FRAME_NODE2->eventHub_->SetOnAreaChanged(std::move(onAreaChanged));
    auto test = FRAME_NODE2->eventHub_->HasOnAreaChanged();
    FRAME_NODE2->TriggerOnAreaChangeCallback();
    EXPECT_FALSE(test);
}

/**
 * @tc.name: FrameNodeTestNg0014
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNg0014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build a object to TriggerVisibleAreaChangeCallback
     * @tc.expected: step1. expect The function is run ok.
     */
    std::list<VisibleCallbackInfo> visibleCallbackInfo;

    FRAME_NODE2->TriggerVisibleAreaChangeCallback(visibleCallbackInfo);

    /**
     * @tc.steps: step1. callback SetParent
     * @tc.expected: step1. expect parent is same with parentNode.
     */
    auto parentNode = AceType::MakeRefPtr<FrameNode>("test", -1, AceType::MakeRefPtr<Pattern>(), false);
    FRAME_NODE2->SetParent(FRAME_NODE3);
    FRAME_NODE2->TriggerVisibleAreaChangeCallback(visibleCallbackInfo);
    auto parent = FRAME_NODE2->GetParent();
    EXPECT_EQ(parent, 1);


    auto parentNode1 = FrameNode::CreateFrameNode("parent", 2, AceType::MakeRefPtr<Pattern>());
    RefPtr<FrameNode> frameNodes[3] = { parentNode1, nullptr, nullptr };
    FRAME_NODE2->TriggerVisibleAreaChangeCallback(visibleCallbackInfo);
    auto parent1 = FRAME_NODE2->GetParent();
    EXPECT_EQ(parent1, 1);

    FRAME_NODE2->lastVisibleRatio_ = 1.0;
    FRAME_NODE2->TriggerVisibleAreaChangeCallback(visibleCallbackInfo);
}

/**
 * @tc.name: FrameNodeTestNg0015
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNg0015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build a object to CreateLayoutTask
     * @tc.expected: step1. expect The function is run ok.
     */
    FrameNode frameNode("main", 10, AceType::MakeRefPtr<Pattern>(), true);
    frameNode.isLayoutDirtyMarked_ = true;
    frameNode.CreateLayoutTask(true);
    EXPECT_FALSE(frameNode.isLayoutDirtyMarked_);

    frameNode.CreateLayoutTask(true);

    frameNode.isLayoutDirtyMarked_ = true;
    frameNode.CreateLayoutTask(false);
    EXPECT_FALSE(frameNode.isLayoutDirtyMarked_);
}

/**
 * @tc.name: FrameNodeTestNg0016
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNg0016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build a object to CreateRenderTask
     * @tc.expected: step1. expect The function is run ok.
     */
    FrameNode frameNode("main", 10, AceType::MakeRefPtr<Pattern>(), true);
    frameNode.isRenderDirtyMarked_ = true;
    frameNode.CreateRenderTask(true);
    EXPECT_FALSE(frameNode.isRenderDirtyMarked_);

    frameNode.isRenderDirtyMarked_ = true;
    frameNode.CreateRenderTask(false);

    frameNode.CreateRenderTask(true);
    EXPECT_FALSE(frameNode.isRenderDirtyMarked_);
}

/**
 * @tc.name: FrameNodeTestNg0017
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNg0017, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build a object to GetParentGlobalOffset
     * @tc.expected: step1. expect The function is run ok.
     */
    FrameNode frameNode("main", 10, AceType::MakeRefPtr<Pattern>(), true);
    frameNode.GetParentGlobalOffset();

    frameNode.SetParent(FRAME_NODE_PARENT);
    auto parent = frameNode.GetAncestorNodeOfFrame();
    frameNode.GetParentGlobalOffset();
    EXPECT_EQ(parent, 1);
}

/**
 * @tc.name: FrameNodeTestNg0018
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNg0018, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build a object to UpdateLayoutPropertyFlag
     * @tc.expected: step1. expect The function is run ok.
     */
    FrameNode frameNode("main", 10, AceType::MakeRefPtr<Pattern>(), true);

    /**
     * @tc.expected: step1. expect selfFlag is same with PROPERTY_UPDATE_BY_CHILD_REQUEST.
     */
    frameNode.layoutProperty_->propertyChangeFlag_ = PROPERTY_UPDATE_BY_CHILD_REQUEST;
    auto selfFlag = frameNode.layoutProperty_->GetPropertyChangeFlag();
    frameNode.UpdateLayoutPropertyFlag();
    EXPECT_EQ(selfFlag, PROPERTY_UPDATE_BY_CHILD_REQUEST);

    FRAME_NODE2->layoutProperty_->propertyChangeFlag_ = PROPERTY_UPDATE_BY_CHILD_REQUEST;
    FRAME_NODE2->AddChild(FRAME_NODE3);
    FRAME_NODE2->UpdateLayoutPropertyFlag();
    FRAME_NODE2->Clean();
}

/**
 * @tc.name: FrameNodeTestNg0019
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNg0019, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build a object to UpdateLayoutPropertyFlag
     * @tc.expected: step1. expect The function is run ok.
     */
    FrameNode frameNode("main", 10, AceType::MakeRefPtr<Pattern>(), true);

    FRAME_NODE2->AddChild(FRAME_NODE3);

    FRAME_NODE2->UpdateChildrenLayoutWrapper(FRAME_NODE2->UpdateLayoutWrapper(nullptr, true, true), true, true);
    FRAME_NODE2->Clean();
    EXPECT_TRUE(FRAME_NODE2->UpdateLayoutWrapper(nullptr, true, true));
}

/**
 * @tc.name: FrameNodeTestNg0020
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNg0020, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build a object to AdjustLayoutWrapperTree
     * @tc.expected: step1. expect The function is run ok.
     */
    FrameNode frameNode("main", 10, AceType::MakeRefPtr<Pattern>(), true);
    auto test = frameNode.CreatePaintWrapper();
    EXPECT_EQ(test, nullptr);
}

/**
 * @tc.name: FrameNodeTestNg0021
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNg0021, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build a object to PostTask
     * @tc.expected: step1. expect The function is run ok.
     */
    auto callback = []() {
        srcimages = "test";
    };
    TaskExecutor::TaskType taskType {1};

    FrameNode frameNode("main", 10, AceType::MakeRefPtr<Pattern>(), true);
    frameNode.PostTask(callback, std::move(taskType));
    EXPECT_EQ(taskType, TaskExecutor::TaskType::UI);
}

/**
 * @tc.name: FrameNodeTestNg0022
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNg0022, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build a object to UpdateLayoutConstraint
     * @tc.expected: step1. expect The function is run ok.
     */
    FrameNode frameNode("main", 10, AceType::MakeRefPtr<Pattern>(), true);
    MeasureProperty calcLayoutConstraint;
    frameNode.UpdateLayoutConstraint(std::move(calcLayoutConstraint));
    EXPECT_EQ(FRAME_NODE2->layoutProperty_->propertyChangeFlag_, 35);
}

/**
 * @tc.name: FrameNodeTestNg0023
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNg0023, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build a object to RebuildRenderContextTree
     * @tc.expected: step1. expect The function is run ok.
     */
    FrameNode frameNode("main", 10, AceType::MakeRefPtr<Pattern>(), true);
    frameNode.needSyncRenderTree_ = true;
    frameNode.RebuildRenderContextTree();
    EXPECT_FALSE(frameNode.needSyncRenderTree_);
}

/**
 * @tc.name: FrameNodeTestNg0024
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNg0024, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build a object to MarkModifyDone.
     * @tc.expected: step1. expect The function is run ok.
     */
    FrameNode frameNode("main", 10, AceType::MakeRefPtr<Pattern>(), true);
    frameNode.MarkModifyDone();
    EXPECT_NE(frameNode.pattern_, nullptr);
}

/**
 * @tc.name: FrameNodeTestNg0025
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNg0025, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build a object to OnMountToParentDone.
     * @tc.expected: step1. expect The function is run ok.
     */
    FrameNode frameNode("main", 10, AceType::MakeRefPtr<Pattern>(), true);
    frameNode.OnMountToParentDone();
    EXPECT_NE(frameNode.pattern_, nullptr);
}

/**
 * @tc.name: FrameNodeTestNg0026
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNg0026, TestSize.Level1)
{
    /**
     * @tc.steps: step1. callback FlushUpdateAndMarkDirty.
     * @tc.expected: step1. expect The function is run ok.
     */
    FRAME_NODE2->FlushUpdateAndMarkDirty();

    PropertyChangeFlag extraFlag = PROPERTY_UPDATE_RENDER;
    CheckMeasureFlag(PROPERTY_UPDATE_EVENT);
    FRAME_NODE2->MarkDirtyNode(extraFlag);
    EXPECT_EQ(extraFlag, PROPERTY_UPDATE_RENDER);

    FRAME_NODE2->SetParent(FRAME_NODE_PARENT);
    auto parent = FRAME_NODE2->GetAncestorNodeOfFrame();
    FRAME_NODE2->MarkDirtyNode(extraFlag);
    EXPECT_EQ(parent, FRAME_NODE_PARENT);
}

/**
 * @tc.name: FrameNodeTestNg0027
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNg0027, TestSize.Level1)
{
    /**
     * @tc.steps: step1. callback MarkNeedRenderOnly.
     * @tc.expected: step1. expect The function is run ok.
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
 * @tc.name: FrameNodeTestNg0028
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNg0028, TestSize.Level1)
{
    /**
     * @tc.steps: step1. callback IsNeedRequestParentMeasure.
     * @tc.expected: step1. expect The function is run ok.
     * @tc.expected: step2. expect The function return value is true.
     */
    auto test = FRAME_NODE2->IsNeedRequestParentMeasure();
    EXPECT_FALSE(test);

    FRAME_NODE2->layoutProperty_->propertyChangeFlag_ = PROPERTY_UPDATE_BY_CHILD_REQUEST;
    FRAME_NODE2->IsNeedRequestParentMeasure();

    FRAME_NODE2->layoutProperty_->propertyChangeFlag_ = PROPERTY_UPDATE_BY_CHILD_REQUEST;
    FRAME_NODE2->layoutProperty_->calcLayoutConstraint_ = std::make_unique<MeasureProperty>();
    auto test1 = FRAME_NODE2->IsNeedRequestParentMeasure();
    EXPECT_TRUE(test1);
}

/**
 * @tc.name: FrameNodeTestNg0029
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNg0029, TestSize.Level1)
{
    /**
     * @tc.steps: step1. callback OnGenerateOneDepthVisibleFrame.
     * @tc.expected: step1. expect The function is run ok.
     */
    std::list<RefPtr<FrameNode>> visibleList;
    FRAME_NODE2->OnGenerateOneDepthVisibleFrame(visibleList);

    FRAME_NODE2->isActive_ = true;
    auto test = FRAME_NODE2->IsVisible();
    FRAME_NODE2->OnGenerateOneDepthVisibleFrame(visibleList);
    EXPECT_TRUE(test);
}

/**
 * @tc.name: FrameNodeTestNg0030
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNg0030, TestSize.Level1)
{
    /**
     * @tc.steps: step1. callback OnGenerateOneDepthAllFrame.
     * @tc.expected: step1. expect The function is run ok.
     */
    std::list<RefPtr<FrameNode>> visibleList;
    FRAME_NODE2->OnGenerateOneDepthAllFrame(visibleList);
    EXPECT_EQ(visibleList.size(), 1);
}

/**
 * @tc.name: FrameNodeTestNg0031
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNg0031, TestSize.Level1)
{
    /**
     * @tc.steps: step1. callback IsMeasureBoundary.
     * @tc.expected: step1. expect The function return value is true.
     */
    auto test = FRAME_NODE2->IsMeasureBoundary();
    EXPECT_FALSE(test);
}

/**
 * @tc.name: FrameNodeTestNg0032
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNg0032, TestSize.Level1)
{
    /**
     * @tc.steps: step1. callback IsRenderBoundary.
     * @tc.expected: step1. expect The function return value is true.
     */
    auto test = FRAME_NODE2->IsRenderBoundary();
    EXPECT_TRUE(test);
}

/**
 * @tc.name: FrameNodeTestNg0033
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNg0033, TestSize.Level1)
{
    /**
     * @tc.steps: step1. callback GetPattern.
     * @tc.expected: step1. expect The function return value is true.
     */
    auto test = FRAME_NODE2->GetPattern();
    EXPECT_EQ(test, 1);
}

/**
 * @tc.name: FrameNodeTestNg0034
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNg0034, TestSize.Level1)
{
    /**
     * @tc.steps: step1. callback IsAtomicNode.
     * @tc.expected: step1. expect The function return value is true.
     */
    auto test = FRAME_NODE2->IsAtomicNode();
    EXPECT_TRUE(test);
}

/**
 * @tc.name: FrameNodeTestNg0035
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNg0035, TestSize.Level1)
{
    /**
     * @tc.steps: step1. callback GetHitTestMode.
     * @tc.expected: step1. expect The function return value is HTMDEFAULT.
     */
    auto test = FRAME_NODE2->GetHitTestMode();
    EXPECT_EQ(test, HitTestMode::HTMDEFAULT);
}

/**
 * @tc.name: FrameNodeTestNg0036
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNg0036, TestSize.Level1)
{
    /**
     * @tc.steps: step1. callback IsAtomicNode.
     * @tc.expected: step1. expect The function return value is true.
     */
    auto test = FRAME_NODE2->GetTouchable();
    EXPECT_TRUE(test);
}

/**
 * @tc.name: FrameNodeTestNg0037
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNg0037, TestSize.Level1)
{
    /**
     * @tc.steps: step1. callback MarkResponseRegion.
     * @tc.expected: step1. expect The function return value is true.
     */
    FRAME_NODE2->MarkResponseRegion(true);
    EXPECT_NE(FRAME_NODE2->eventHub_->gestureEventHub_, nullptr);
}

/**
 * @tc.name: FrameNodeTestNg0038
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNg0038, TestSize.Level1)
{
    /**
     * @tc.steps: step1. callback IsOutOfTouchTestRegion.
     * @tc.expected: step1. expect The function return value is true.
     */
    PointF pointF;
    std::vector<RectF> rectF;
    auto test = FRAME_NODE2->IsOutOfTouchTestRegion(std::move(pointF));
    EXPECT_FALSE(test);

    auto test1 = FRAME_NODE2->InResponseRegionList(pointF, rectF);
    auto test2 = FRAME_NODE2->IsOutOfTouchTestRegion(std::move(pointF));
    EXPECT_FALSE(test1);
    EXPECT_FALSE(test2);
}

/**
 * @tc.name: FrameNodeTestNg0039
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNg0039, TestSize.Level1)
{
    /**
     * @tc.steps: step1. callback TouchTest.
     * @tc.expected: step1. expect The function return value is true.
     */
    PointF globalPoint;
    PointF parentLocalPoint;
    TouchRestrict touchRestrict;
    TouchTestResult result;
    SystemProperties::debugEnabled_ = true;
    FRAME_NODE2->TouchTest(globalPoint, parentLocalPoint, touchRestrict, result, 1);

    SystemProperties::debugEnabled_ = false;
    FRAME_NODE2->TouchTest(globalPoint, parentLocalPoint, touchRestrict, result, 1);

    /**
     * @tc.steps: step1. set isActive_ and IsEnabled is false.
     * @tc.expected: step1. expect The function return value is OUT_OF_REGION.
     */
    FRAME_NODE2->isActive_ = false;
    FRAME_NODE2->eventHub_->SetEnabled(false);
    auto test = FRAME_NODE2->TouchTest(globalPoint, parentLocalPoint, touchRestrict, result, 1);
    EXPECT_EQ(test, HitTestResult::OUT_OF_REGION);
}

/**
 * @tc.name: FrameNodeTestNg0040
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNg0040, TestSize.Level1)
{
    /**
     * @tc.steps: step1. callback MouseTest.
     * @tc.expected: step1. expect The function return value is BUBBLING.
     */
    const PointF globalPoint;
    const PointF parentLocalPoint;
    MouseTestResult onMouseResult;
    MouseTestResult onHoverResult;
    RefPtr<FrameNode> hoverNode;
    auto test = FRAME_NODE2->MouseTest(globalPoint, parentLocalPoint, onMouseResult, onHoverResult, hoverNode);
    EXPECT_EQ(test, HitTestResult::BUBBLING);
}

/**
 * @tc.name: FrameNodeTestNg0041
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNg0041, TestSize.Level1)
{
    /**
     * @tc.steps: step1. callback AxisTest.
     * @tc.expected: step1. expect The function is run ok.
     */
    const PointF globalPoint;
    const PointF parentLocalPoint;
    AxisTestResult onAxisResult;
    FRAME_NODE2->eventHub_->GetOrCreateInputEventHub();
    FRAME_NODE2->AxisTest(globalPoint, parentLocalPoint, onAxisResult);
    EXPECT_NE(FRAME_NODE2->eventHub_->inputEventHub_, nullptr);
}

/**
 * @tc.name: FrameNodeTestNg0042
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNg0042, TestSize.Level1)
{
    /**
     * @tc.steps: step1. callback GetOrCreateFocusHub.
     * @tc.expected: step1. expect The function return value is nullptr.
     */
    auto test = FRAME_NODE2->GetOrCreateFocusHub();
    EXPECT_EQ(test, 1);
}

/**
 * @tc.name: FrameNodeTestNg0043
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNg0043, TestSize.Level1)
{
    /**
     * @tc.steps: step1. callback OnWindowShow.
     * @tc.expected: step1. expect The function is run ok.
     */
    FRAME_NODE2->OnWindowShow();
    EXPECT_NE(FRAME_NODE2->pattern_, nullptr);
}

/**
 * @tc.name: FrameNodeTestNg0044
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNg0044, TestSize.Level1)
{
    /**
     * @tc.steps: step1. callback OnWindowHide.
     * @tc.expected: step1. expect The function is run ok.
     */
    FRAME_NODE2->OnWindowHide();
    EXPECT_NE(FRAME_NODE2->pattern_, nullptr);
}

/**
 * @tc.name: FrameNodeTestNg0045
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNg0045, TestSize.Level1)
{
    /**
     * @tc.steps: step1. callback OnWindowFocused.
     * @tc.expected: step1. expect The function is run ok.
     */
    FRAME_NODE2->OnWindowFocused();
    EXPECT_NE(FRAME_NODE2->pattern_, nullptr);
}

/**
 * @tc.name: FrameNodeTestNg0046
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNg0046, TestSize.Level1)
{
    /**
     * @tc.steps: step1. callback OnWindowUnfocused.
     * @tc.expected: step1. expect The function is run ok.
     */
    FRAME_NODE2->OnWindowUnfocused();
    EXPECT_NE(FRAME_NODE2->pattern_, nullptr);
}

/**
 * @tc.name: FrameNodeTestNg0047
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNg0047, TestSize.Level1)
{
    /**
     * @tc.steps: step1. callback OnWindowSizeChanged.
     * @tc.expected: step1. expect The function is run ok.
     */
    FRAME_NODE2->OnWindowSizeChanged(1, 1, WindowSizeChangeReason::CUSTOM_ANIMATION);
    EXPECT_NE(FRAME_NODE2->pattern_, nullptr);
}

/**
 * @tc.name: FrameNodeTestNg0048
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNg0048, TestSize.Level1)
{
    /**
     * @tc.steps: step1. callback GetOffsetRelativeToWindow.
     * @tc.expected: step1. expect The function is run ok.
     */
    OffsetF Offset = {0, 0};
    FRAME_NODE2->layoutProperty_->positionProperty_ = std::make_unique<PositionProperty>();
    auto test = FRAME_NODE2->GetOffsetRelativeToWindow();
    FRAME_NODE2->SetParent(FRAME_NODE_PARENT);
    EXPECT_EQ(test, Offset);
}

/**
 * @tc.name: FrameNodeTestNg0049
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNg0049, TestSize.Level1)
{
    /**
     * @tc.steps: step1. callback GetTransformRelativeOffset.
     * @tc.expected: step1. expect The function is run ok.
     */
    OffsetF Offset = {0, 0};
    auto test = FRAME_NODE2->GetTransformRelativeOffset();
    FRAME_NODE2->SetParent(FRAME_NODE_PARENT);
    EXPECT_EQ(test, Offset);
}

/**
 * @tc.name: FrameNodeTestNg0050
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNg0050, TestSize.Level1)
{
    /**
     * @tc.steps: step1. callback GetPaintRectOffset.
     * @tc.expected: step1. expect The function is run ok.
     */
    OffsetF Offset = {0, 0};
    auto test = FRAME_NODE2->GetPaintRectOffset(true);
    FRAME_NODE2->SetParent(FRAME_NODE_PARENT);
    EXPECT_EQ(test, Offset);
}

/**
 * @tc.name: FrameNodeTestNg0051
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNg0051, TestSize.Level1)
{
    /**
     * @tc.steps: step1. callback OnNotifyMemoryLevel.
     * @tc.expected: step1. expect The function is run ok.
     */
    FRAME_NODE2->OnNotifyMemoryLevel(true);
    EXPECT_NE(FRAME_NODE2->pattern_, nullptr);
}

/**
 * @tc.name: FrameNodeTestNg0052
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNg0052, TestSize.Level1)
{
    /**
     * @tc.steps: step1. callback GetAllDepthChildrenCount.
     * @tc.expected: step1. expect The function return value is 1.
     */
    auto test = FRAME_NODE2->GetAllDepthChildrenCount();
    EXPECT_EQ(test, 1);
}

/**
 * @tc.name: FrameNodeTestNg0053
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNg0053, TestSize.Level1)
{
    /**
     * @tc.steps: step1. callback OnAccessibilityEvent.
     * @tc.expected: step1. expect The function is run ok.
     */
    auto test = AceApplicationInfo::GetInstance().isAccessibilityEnabled_ = true;
    FRAME_NODE2->OnAccessibilityEvent(AccessibilityEventType::ACCESSIBILITY_FOCUSED);
    EXPECT_TRUE(test);

    auto test1 = AceApplicationInfo::GetInstance().isAccessibilityEnabled_ = false;
    FRAME_NODE2->OnAccessibilityEvent(AccessibilityEventType::ACCESSIBILITY_FOCUSED);
    EXPECT_FALSE(test1);
}

/**
 * @tc.name: FrameNodeTestNg0054
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNg0054, TestSize.Level1)
{
    /**
     * @tc.steps: step1. callback MarkRemoving.
     * @tc.expected: step1. expect The function return value is true.
     */
    FRAME_NODE2->AddChild(FRAME_NODE3);
    FRAME_NODE2->layoutProperty_->UpdateGeometryTransition("id");
    auto test = FRAME_NODE2->MarkRemoving();
    FRAME_NODE2->Clean();
    EXPECT_FALSE(test);
}

/**
 * @tc.name: FrameNodeTestNg0055
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNg0055, TestSize.Level1)
{
    /**
     * @tc.steps: step1. callback AddHotZoneRect.
     * @tc.expected: step1. expect The function is run ok.
     */
    DimensionRect dimensionRect;
    FRAME_NODE2->AddHotZoneRect(dimensionRect);
    EXPECT_NE(FRAME_NODE2->eventHub_, nullptr);
}

/**
 * @tc.name: FrameNodeTestNg0056
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNg0056, TestSize.Level1)
{
    /**
     * @tc.steps: step1. callback RemoveLastHotZoneRect.
     * @tc.expected: step1. expect The function is run ok.
     */
    FRAME_NODE2->RemoveLastHotZoneRect();
    EXPECT_NE(FRAME_NODE2->eventHub_, nullptr);
}

/**
 * @tc.name: FrameNodeTestNg0057
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNg0057, TestSize.Level1)
{
    /**
     * @tc.steps: step1. callback RemoveLastHotZoneRect.
     * @tc.expected: step1. expect The function is run ok.
     */
    const RectF visibleRect;
    const RectF renderRect;
    FRAME_NODE2->CalculateCurrentVisibleRatio(visibleRect, renderRect);
    EXPECT_EQ(visibleRect.Width(), 0);
    EXPECT_EQ(renderRect.Width(), 0);
}

/**
 * @tc.name: FrameNodeTestNg0058
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeTestNg0058, TestSize.Level1)
{
    /**
     * @tc.steps: step1. callback RemoveLastHotZoneRect.
     * @tc.expected: step1. expect The function is run ok.
     */
    VisibleCallbackInfo callbackInfo;
    FRAME_NODE2->OnVisibleAreaChangeCallback(callbackInfo, true, 1.0);
    EXPECT_TRUE(callbackInfo.isCurrentVisible);
}
} // namespace OHOS::Ace::NG