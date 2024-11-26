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

#include <cstddef>
#include <optional>
#include <memory>

#include "gtest/gtest.h"

#define protected public
#define private public

#include "mock/mock_form_utils.h"
#include "mock/mock_sub_container.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_render_context.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/form/form_node.h"
#include "core/components_ng/pattern/form/form_pattern.h"
#include "core/pipeline/pipeline_base.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
class FormNodeTest : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
protected:
    static RefPtr<FormNode> CreateFromNode();
};

void FormNodeTest::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void FormNodeTest::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

RefPtr<FormNode> FormNodeTest::CreateFromNode()
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto formNode = FormNode::GetOrCreateFormNode(
        "FormComponent", stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<FormPattern>(); });
    auto pattern = formNode->GetPattern<FormPattern>();
    pattern->frameNode_ = formNode;
    return formNode;
}

/**
 * @tc.name: FormNodeTest_001
 * @tc.desc: TouchTest
 * @tc.type: FUNC
 */
HWTEST_F(FormNodeTest, FormNodeTest_001, TestSize.Level1)
{
    PointF globalPoint;
    PointF parentLocalPoint;
    PointF parentRevertPoint;
    TouchRestrict touchRestrict;
    touchRestrict.hitTestType = SourceType::MOUSE;
    TouchTestResult result;
    int32_t touchId = 0;
    ResponseLinkResult responseLinkResult;
    bool isDispatch = false;
    auto formNode = CreateFromNode();
    auto res = formNode->TouchTest(globalPoint, parentLocalPoint,
        parentRevertPoint, touchRestrict, result, touchId, responseLinkResult, isDispatch);
    EXPECT_EQ(res, HitTestResult::OUT_OF_REGION);
  
    touchRestrict.hitTestType = SourceType::NONE;
    res = formNode->TouchTest(globalPoint, parentLocalPoint,
        parentRevertPoint, touchRestrict, result, touchId, responseLinkResult, isDispatch);
    EXPECT_EQ(res, HitTestResult::OUT_OF_REGION);

    PipelineContext* contextBak = formNode->GetContext();
    formNode->context_ = nullptr;
    res = formNode->TouchTest(globalPoint, parentLocalPoint,
        parentRevertPoint, touchRestrict, result, touchId, responseLinkResult, isDispatch);
    EXPECT_EQ(res, HitTestResult::OUT_OF_REGION);
    formNode->context_ = contextBak;

    auto patternBak = formNode->GetPattern<FormPattern>();
    formNode->pattern_ = nullptr;
    res = formNode->TouchTest(globalPoint, parentLocalPoint,
        parentRevertPoint, touchRestrict, result, touchId, responseLinkResult, isDispatch);
    EXPECT_EQ(res, HitTestResult::OUT_OF_REGION);
    formNode->pattern_ = patternBak;

    auto pattern = formNode->GetPattern<FormPattern>();
    WeakPtr<PipelineContext> context = WeakPtr<PipelineContext>();
    auto subContainer = AceType::MakeRefPtr<MockSubContainer>(context);
    ASSERT_NE(subContainer, nullptr);
    subContainer->instanceId_ = 0;

    EXPECT_EQ(pattern->subContainer_, nullptr);
    res = formNode->TouchTest(globalPoint, parentLocalPoint,
        parentRevertPoint, touchRestrict, result, touchId, responseLinkResult, isDispatch);
    EXPECT_EQ(res, HitTestResult::OUT_OF_REGION);
    pattern->subContainer_ = subContainer;

    FrontendType uiSyntaxBak = FrontendType::JS_CARD;
    pattern->subContainer_->uiSyntax_ = FrontendType::ETS_CARD;
    res = formNode->TouchTest(globalPoint, parentLocalPoint,
        parentRevertPoint, touchRestrict, result, touchId, responseLinkResult, isDispatch);
    EXPECT_EQ(res, HitTestResult::OUT_OF_REGION);
    pattern->subContainer_->uiSyntax_ = uiSyntaxBak;

    res = formNode->TouchTest(globalPoint, parentLocalPoint,
        parentRevertPoint, touchRestrict, result, touchId, responseLinkResult, isDispatch);
    EXPECT_EQ(res, HitTestResult::OUT_OF_REGION);
}

/**
 * @tc.name: FormNodeTest_002
 * @tc.desc: OnAccessibilityDumpChildInfo
 * @tc.type: FUNC
 */
HWTEST_F(FormNodeTest, FormNodeTest_002, TestSize.Level1)
{
    RefPtr<FrameNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    ASSERT_NE(pattern, nullptr);

    std::vector<std::string> params;
    std::vector<std::string> info;
    pattern->OnAccessibilityDumpChildInfo(params, info);
    ASSERT_NE(pattern->formManagerBridge_, nullptr);
    pattern->UpdateStaticCard();
    auto retRef = pattern->GetAccessibilitySessionAdapter();
    ASSERT_NE(retRef, nullptr);
}

/**
 * @tc.name: FormNodeTest_003
 * @tc.desc: GetFormOffset
 * @tc.type: FUNC
 */
HWTEST_F(FormNodeTest, FormNodeTest_003, TestSize.Level1)
{
    auto formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    auto host = pattern->GetHost();
    RefPtr<RenderContext> renderContext = formNode->GetRenderContext();

    formNode->renderContext_ = nullptr;
    OffsetF res = formNode->GetFormOffset();
    EXPECT_EQ(res, OffsetF());
    formNode->renderContext_ = renderContext;
    
    formNode->SetParent(nullptr);
    res = formNode->GetFormOffset();
    EXPECT_EQ(res, OffsetF());
}

/**
 * @tc.name: FormNodeTest_004
 * @tc.desc: OnAccessibilityChildTreeRegister
 * @tc.type: FUNC
 */
HWTEST_F(FormNodeTest, FormNodeTest_004, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);

    formNode->pattern_ = nullptr;
    formNode->OnAccessibilityChildTreeRegister(0, 0);
    EXPECT_NE(pattern->formManagerBridge_, nullptr);
    formNode->pattern_ = pattern;

    std::vector<std::string> infos;
    std::string tmpStr = "action";
    infos.emplace_back(tmpStr);
    pattern->SetFormLinkInfos(infos);
    uint32_t windowId = 0;
    int32_t treeId = 0;
    formNode->OnAccessibilityChildTreeRegister(windowId, treeId);
    ASSERT_NE(pattern->formManagerBridge_, nullptr);

    formNode->OnAccessibilityChildTreeDeregister();
    ASSERT_NE(pattern->formManagerBridge_, nullptr);
}

/**
 * @tc.name: FormNodeTest_005
 * @tc.desc: OnDetachFromMainTree
 * @tc.type: FUNC
 */
HWTEST_F(FormNodeTest, FormNodeTest_005, TestSize.Level1)
{
    auto formNode = CreateFromNode();
    auto focusHub = formNode->GetFocusHub();
    EXPECT_EQ(focusHub, nullptr);

    auto formNode1 = CreateFromNode();
    formNode->AddChild(formNode1);
    formNode1->OnDetachFromMainTree(true);
    auto root = formNode1->GetParent();
    EXPECT_EQ(root, 1);

    auto formNode2 = CreateFromNode();
    formNode->AddChild(formNode2);
    formNode2->OnDetachFromMainTree(false);
    root = formNode2->GetParent();
    EXPECT_NE(root, 0);
}

/**
 * @tc.name: FormNodeTest_006
 * @tc.desc: OnSetAccessibilityChildTree
 * @tc.type: FUNC
 */
HWTEST_F(FormNodeTest, FormNodeTest_006, TestSize.Level1)
{
    auto formNode = CreateFromNode();
    int32_t childWindowId = 1;
    int32_t childTreeId = 2;
    formNode->OnSetAccessibilityChildTree(childWindowId, childTreeId);
    auto accessibilityProperty = formNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetChildWindowId(), childWindowId);
    EXPECT_EQ(accessibilityProperty->GetChildTreeId(), childTreeId);
}

/**
 * @tc.name: FormNodeTest_007
 * @tc.desc: OnAccessibilityDumpChildInfo
 * @tc.type: FUNC
 */
HWTEST_F(FormNodeTest, FormNodeTest_007, TestSize.Level1)
{
    RefPtr<FrameNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    ASSERT_NE(pattern, nullptr);

    std::vector<std::string> params;
    std::vector<std::string> info;
    pattern->OnAccessibilityDumpChildInfo(params, info);
    ASSERT_NE(pattern->formManagerBridge_, nullptr);
}

/**
 * @tc.name: FormNodeTest_008
 * @tc.desc: DispatchPointerEvent
 * @tc.type: FUNC
 */
HWTEST_F(FormNodeTest, FormNodeTest_008, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);

    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipelineContext, nullptr);
    pipelineContext->GetEventManager()->SetInnerFlag(false);
    TouchEvent touchEvent;
    SerializedGesture serializedGesture;

    formNode->pattern_ = nullptr;
    formNode->DispatchPointerEvent(touchEvent, serializedGesture);
    EXPECT_FALSE(pipelineContext->GetEventManager()->GetInnerFlag());
    formNode->pattern_ = pattern;
}

/**
 * @tc.name: FormNodeTest_009
 * @tc.desc: InitializeFormAccessibility
 * @tc.type: FUNC
 */
HWTEST_F(FormNodeTest, FormNodeTest_009, TestSize.Level1)
{
    ContainerScope scope(-1);
    auto formNode = CreateFromNode();
    formNode->InitializeFormAccessibility();
    EXPECT_NE(formNode->accessibilityChildTreeCallback_, nullptr);
    ContainerScope scope1(1);

    auto pipeline = PipelineContext::GetCurrentContext();
    RefCounter* refCounter = pipeline->weakFrontend_.refCounter_;
    pipeline->weakFrontend_.refCounter_ = nullptr;
    formNode->InitializeFormAccessibility();
    EXPECT_NE(formNode->accessibilityChildTreeCallback_, nullptr);
    pipeline->weakFrontend_.refCounter_ = refCounter;

    formNode->InitializeFormAccessibility();
    EXPECT_NE(formNode->accessibilityChildTreeCallback_, nullptr);
}

/**
 * @tc.name: FormNodeTest_010
 * @tc.desc: NotifyAccessibilityChildTreeRegister
 * @tc.type: FUNC
 */
HWTEST_F(FormNodeTest, FormNodeTest_010, TestSize.Level1)
{
    ContainerScope scope(-1);
    auto formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    formNode->NotifyAccessibilityChildTreeRegister();
    EXPECT_NE(formNode->accessibilityChildTreeCallback_, nullptr);
    ContainerScope scope1(1);

    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    RefCounter* refCounter = pipeline->weakFrontend_.refCounter_;
    pipeline->weakFrontend_.refCounter_ = nullptr;
    formNode->NotifyAccessibilityChildTreeRegister();
    EXPECT_NE(formNode->accessibilityChildTreeCallback_, nullptr);
    pipeline->weakFrontend_.refCounter_ = refCounter;
}

/**
 * @tc.name: FormNodeTest_011
 * @tc.desc: OnAccessibilityChildTreeDeregister
 * @tc.type: FUNC
 */
HWTEST_F(FormNodeTest, FormNodeTest_011, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    ASSERT_NE(pattern, nullptr);

    formNode->pattern_ = nullptr;
    formNode->OnAccessibilityChildTreeDeregister();
    EXPECT_EQ(formNode->GetPattern<FormPattern>(), nullptr);
    formNode->pattern_ = pattern;

    std::vector<std::string> infos;
    std::string tmpStr = "action";
    infos.emplace_back(tmpStr);
    pattern->SetFormLinkInfos(infos);
    uint32_t windowId = 0;
    int32_t treeId = 0;
    formNode->OnAccessibilityChildTreeRegister(windowId, treeId);
    EXPECT_NE(pattern->formManagerBridge_, nullptr);

    formNode->OnAccessibilityChildTreeDeregister();
    EXPECT_NE(pattern->formManagerBridge_, nullptr);
}

/**
 * @tc.name: FormNodeTest_012
 * @tc.desc: OnSetAccessibilityChildTree
 * @tc.type: FUNC
 */
HWTEST_F(FormNodeTest, FormNodeTest_012, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    ASSERT_NE(pattern, nullptr);

    int32_t childWindowId = 2;
    int32_t childTreeId = 1;
    auto accessibilityProperty = formNode->accessibilityProperty_;
    ASSERT_NE(accessibilityProperty, nullptr);
    formNode->accessibilityProperty_ = nullptr;
    formNode->OnSetAccessibilityChildTree(childWindowId, childTreeId);
    EXPECT_NE(pattern->formManagerBridge_, nullptr);
    formNode->accessibilityProperty_ = accessibilityProperty;

    formNode->OnSetAccessibilityChildTree(childWindowId, childTreeId);
    EXPECT_NE(pattern->formManagerBridge_, nullptr);
    EXPECT_EQ(formNode->accessibilityProperty_->childWindowId_, 2);
    EXPECT_EQ(formNode->accessibilityProperty_->childTreeId_, 1);
}

/**
 * @tc.name: FormNodeTest_013
 * @tc.desc: OnAccessibilityDumpChildInfo
 * @tc.type: FUNC
 */
HWTEST_F(FormNodeTest, FormNodeTest_013, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    ASSERT_NE(pattern, nullptr);

    std::vector<std::string> params;
    std::vector<std::string> info;
    pattern->OnAccessibilityDumpChildInfo(params, info);
    EXPECT_NE(pattern->formManagerBridge_, nullptr);
    pattern->UpdateStaticCard();
    auto retRef = pattern->GetAccessibilitySessionAdapter();
    EXPECT_NE(retRef, nullptr);
}

#ifdef FORM_MOUSE_AXIS_SUPPORT
/**
 * @tc.name: FormNodeTest_014
 * @tc.desc: AxisTest
 * @tc.type: FUNC
 */
HWTEST_F(FormNodeTest, FormNodeTest_014, TestSize.Level1)
{
    PointF globalPoint;
    PointF parentLocalPoint;
    PointF parentRevertPoint;
    TouchRestrict touchRestrict;
    touchRestrict.sourceType = SourceType::MOUSE;
    touchRestrict.hitTestType = SourceType::MOUSE;
    touchRestrict.inputEventType = InputEventType::AXIS;
    touchRestrict.touchEvent.sourceType = SourceType::MOUSE;
    touchRestrict.touchEvent.sourceTool = SourceTool::MOUSE;
    AxisTestResult result;
    auto formNode = CreateFromNode();

    touchRestrict.hitTestType = SourceType::NONE;
    auto res = formNode->AxisTest(globalPoint, parentLocalPoint, parentRevertPoint, touchRestrict, result);
    EXPECT_EQ(res, HitTestResult::OUT_OF_REGION);

    PipelineContext* contextBak = formNode->GetContext();
    formNode->context_ = nullptr;
    res = formNode->AxisTest(globalPoint, parentLocalPoint, parentRevertPoint, touchRestrict, result);
    EXPECT_EQ(res, HitTestResult::OUT_OF_REGION);
    formNode->context_ = contextBak;

    auto patternBak = formNode->GetPattern<FormPattern>();
    formNode->pattern_ = nullptr;
    res = formNode->AxisTest(globalPoint, parentLocalPoint, parentRevertPoint, touchRestrict, result);
    EXPECT_EQ(res, HitTestResult::OUT_OF_REGION);
    formNode->pattern_ = patternBak;

    auto pattern = formNode->GetPattern<FormPattern>();
    WeakPtr<PipelineContext> context = WeakPtr<PipelineContext>();
    auto subContainer = AceType::MakeRefPtr<MockSubContainer>(context);
    ASSERT_NE(subContainer, nullptr);
    subContainer->instanceId_ = 0;

    EXPECT_EQ(pattern->subContainer_, nullptr);
    res = formNode->AxisTest(globalPoint, parentLocalPoint, parentRevertPoint, touchRestrict, result);
    EXPECT_EQ(res, HitTestResult::OUT_OF_REGION);
    pattern->subContainer_ = subContainer;
}
#endif
} // namespace OHOS::Ace::NG
