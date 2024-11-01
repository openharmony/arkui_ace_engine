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
#include "test/mock/base/mock_pixel_map.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_render_context.h"
#include "test/mock/core/render/mock_rosen_render_context.h"

#include "base/utils/utils.h"
#include "base/want/want_wrap.h"
#include "core/components/form/resource/form_manager_delegate.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/form/form_node.h"
#include "core/components_ng/pattern/form/form_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/common/form_manager.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
constexpr int32_t MAX_CLICK_DURATION = 500000000; // ns
constexpr int32_t FORM_SHAPE_CIRCLE = 2;
const Dimension ZERO { 0.0, DimensionUnit::PX };
DirtySwapConfig config;
RequestFormInfo formInfo;
const std::string INIT_VALUE_1 = "hello1";
constexpr double ARC_RADIUS_TO_DIAMETER = 2.0;
constexpr double TRANSPARENT_VAL = 0;
}
class FormPatternTest : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
protected:
    static RefPtr<FormNode> CreateFromNode();
};

void FormPatternTest::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->pipelineContext_ = NG::MockPipelineContext::GetCurrent();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockContainer::Current()->pipelineContext_->taskExecutor_ = MockContainer::Current()->taskExecutor_;
}

void FormPatternTest::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void FormPatternTest::SetUp()
{
    formInfo.id = 1;
    formInfo.cardName = "defalut";
    formInfo.bundleName = "bundle";
    formInfo.abilityName = "ability";
    formInfo.moduleName = "module";
    formInfo.allowUpdate = true;
}

RefPtr<FormNode> FormPatternTest::CreateFromNode()
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto formNode = FormNode::GetOrCreateFormNode(
        "FormComponent", stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<FormPattern>(); });
    auto pattern = formNode->GetPattern<FormPattern>();
    pattern->AttachToFrameNode(formNode);
    return formNode;
}

/**
 * @tc.name: FormPatternTest_001
 * @tc.desc: OnAttachToFrameNode
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest, FormPatternTest_001, TestSize.Level1)
{
    RefPtr<FormNode> frameNode = CreateFromNode();
    auto pattern = frameNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);
    
    EXPECT_EQ(pattern->scopeId_, 0);
    auto  host = pattern->GetHost();
    EXPECT_NE(host, nullptr);
    pattern->frameNode_ = nullptr;
    pattern->OnAttachToFrameNode();
    EXPECT_EQ(pattern->scopeId_, 0);
    pattern->frameNode_ = host;

    auto eventHub = host->GetEventHub<FormEventHub>();
    host->eventHub_ = nullptr;
    pattern->OnAttachToFrameNode();
    EXPECT_EQ(pattern->scopeId_, 0);
    host->eventHub_ = eventHub;

    host = pattern->GetHost();
    pattern->frameNode_ = nullptr;
    pattern->OnAttachToFrameNode();
    EXPECT_EQ(pattern->scopeId_, 0);
    pattern->frameNode_ = host;


    RefPtr<SubContainer> subContainer = pattern->subContainer_;
    pattern->subContainer_ = nullptr;
    pattern->OnAttachToFrameNode();
    EXPECT_EQ(pattern->scopeId_, 0);
    pattern->subContainer_ = subContainer;
}


/**
 * @tc.name: FormPatternTest_003
 * @tc.desc: HandleTouchDownEvent
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest, FormPatternTest_003, TestSize.Level1)
{
    RefPtr<FormNode> frameNode = CreateFromNode();
    auto pattern = frameNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);
    
    auto host = pattern->GetHost();
    EXPECT_NE(host, nullptr);
    pattern->OnAttachToFrameNode();
    pattern->InitClickEvent();

    TouchEventInfo event("onTouchDown");
    std::list<TouchLocationInfo> touchesBak = event.GetTouches();
    EXPECT_EQ(touchesBak.empty(), true);
    std::list<TouchLocationInfo> touches;
    event.touches_ = std::move(touches);
    pattern->HandleTouchDownEvent(event);
    EXPECT_EQ(pattern->lastTouchLocation_, Offset());

    TouchLocationInfo touchLocationInfo(1);
    touchLocationInfo.SetTouchType(TouchType::DOWN);
    event.AddTouchLocationInfo(std::move(touchLocationInfo));
    pattern->HandleUnTrustForm();
    pattern->UpdateBackgroundColorWhenUnTrustForm();
    pattern->HandleTouchDownEvent(event);
    EXPECT_EQ(event.GetTouches().empty(), false);
}

/**
 * @tc.name: FormPatternTest_004
 * @tc.desc: HandleTouchUpEvent
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest, FormPatternTest_004, TestSize.Level1)
{
    RefPtr<FormNode> frameNode = CreateFromNode();
    auto pattern = frameNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);
    
    EXPECT_FALSE(pattern->shouldResponseClick_);
    auto host = pattern->GetHost();
    EXPECT_NE(host, nullptr);
    pattern->OnAttachToFrameNode();
    pattern->InitClickEvent();

    pattern->shouldResponseClick_ = true;
    TouchEventInfo event("onTouchUp");
    TimeStamp timeStamp = event.timeStamp_;
    std::chrono::duration<long, std::ratio<1, 1000>> millisecondDuration(MAX_CLICK_DURATION/1000000 + 10);
    event.timeStamp_ = pattern->touchDownTime_ +  millisecondDuration;
    TouchLocationInfo touchLocationInfo(1);
    touchLocationInfo.SetTouchType(TouchType::UP);
    event.AddTouchLocationInfo(std::move(touchLocationInfo));
    pattern->HandleTouchUpEvent(event);
    EXPECT_EQ(pattern->shouldResponseClick_, false);
    event.timeStamp_ = timeStamp;
    pattern->shouldResponseClick_ = true;

    std::list<TouchLocationInfo> newTouches;
    std::list<TouchLocationInfo> touches = event.GetTouches();
    EXPECT_EQ(touches.empty(), false);
    event.touches_ = std::move(newTouches);
    pattern->HandleTouchUpEvent(event);
    EXPECT_EQ(pattern->shouldResponseClick_, true);
    event.touches_ = touches;
    pattern->shouldResponseClick_ = true;

    event.touches_.begin()->screenLocation_ += Offset(30, 30);
    pattern->HandleTouchUpEvent(event);
    EXPECT_EQ(pattern->shouldResponseClick_, false);
    pattern->shouldResponseClick_ = true;

    event.touches_.begin()->screenLocation_ -= Offset(30, 30);
    pattern->HandleTouchUpEvent(event);
    EXPECT_EQ(pattern->shouldResponseClick_, true);
    pattern->shouldResponseClick_ = false;
}

/**
 * @tc.name: FormPatternTest_005
 * @tc.desc: HandleUnTrustForm
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest, FormPatternTest_005, TestSize.Level1)
{
    RefPtr<FormNode> frameNode = CreateFromNode();
    auto pattern = frameNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);
    
    TouchEventInfo event("onTouchDown");
    TouchLocationInfo touchLocationInfo(1);
    touchLocationInfo.SetTouchType(TouchType::DOWN);
    event.AddTouchLocationInfo(std::move(touchLocationInfo));
    pattern->HandleUnTrustForm();
    pattern->UpdateBackgroundColorWhenUnTrustForm();
    pattern->HandleTouchDownEvent(event);
    EXPECT_EQ(event.GetTouches().empty(), false);
}

/**
 * @tc.name: FormPatternTest_007
 * @tc.desc: HandleSnapshot
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest, FormPatternTest_007, TestSize.Level1)
{
    RefPtr<FormNode> frameNode = CreateFromNode();
    auto pattern = frameNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);

    auto pipeline = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipeline, nullptr);
    int32_t delayTime = 0;
    pipeline->taskExecutor_ = nullptr;
    auto taskExecutor = pipeline->GetTaskExecutor();
    EXPECT_EQ(taskExecutor, nullptr);
    pattern->HandleSnapshot(delayTime, "1");
    pipeline->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    EXPECT_NE(pipeline->taskExecutor_, nullptr);
    taskExecutor = pipeline->GetTaskExecutor();
    uint32_t taskNum = taskExecutor->GetTotalTaskNum(TaskExecutor::TaskType::UI);
    EXPECT_EQ(taskNum, 0);

    WeakPtr<FormPattern> weak = Referenced::WeakClaim(Referenced::RawPtr(pattern));
    RefCounter* refBak = pattern->refCounter_;
    weak.refCounter_ = nullptr;
    pattern->HandleSnapshot(delayTime, "1");
    uint32_t taskNum1 = taskExecutor->GetTotalTaskNum(TaskExecutor::TaskType::UI);
    EXPECT_EQ(taskNum, taskNum1);

    weak.refCounter_ = refBak;
    pattern->refCounter_ = refBak;
    int64_t currentTime = GetCurrentTimestamp();
    auto form = weak.Upgrade();
    int64_t diff = currentTime - form->snapshotTimestamp_;
    EXPECT_EQ(diff, 0);
    delayTime = 1;
    EXPECT_LT(diff, delayTime);
    taskNum1 = taskExecutor->GetTotalTaskNum(TaskExecutor::TaskType::UI);
    EXPECT_EQ(taskNum, taskNum1);
}

/**
 * @tc.name: FormPatternTest_008
 * @tc.desc: HandleStaticFormEvent
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest, FormPatternTest_008, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);

    PointF touchPoint;
    touchPoint.SetX(-5.0f);
    touchPoint.SetY(5.0f);
    std::vector<std::string> infos;
    pattern->SetFormLinkInfos(infos);
    pattern->HandleStaticFormEvent(touchPoint);
    EXPECT_EQ(pattern->formLinkInfos_.empty(), true);
    EXPECT_TRUE(pattern->isDynamic_);
    EXPECT_FALSE(pattern->shouldResponseClick_);

    pattern->isDynamic_ = false;
    pattern->SetFormLinkInfos(infos);
    EXPECT_TRUE(pattern->formLinkInfos_.empty());

    pattern->shouldResponseClick_ = false;
    pattern->HandleStaticFormEvent(touchPoint);
    EXPECT_EQ(pattern->formLinkInfos_.empty(), true);

    std::string tmpStr = "action";
    infos.emplace_back(tmpStr);
    pattern->SetFormLinkInfos(infos);
    pattern->shouldResponseClick_ = true;
    pattern->HandleStaticFormEvent(touchPoint);
    EXPECT_EQ(pattern->formLinkInfos_.empty(), false);
}

/**
 * @tc.name: FormPatternTest_009
 * @tc.desc: HandleEnableForm
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest, FormPatternTest_009, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);

    auto* stack = ViewStackProcessor::GetInstance();
    auto formNode1 = FormNode::GetOrCreateFormNode(
        "FormComponent", stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<FormPattern>(); });

    std::vector<std::string> infos;
    std::string tmpStr = "action";
    infos.emplace_back(tmpStr);
    RequestFormInfo info;
    info.shape = FORM_SHAPE_CIRCLE;
    EXPECT_NE(pattern->formManagerBridge_, nullptr);
    pattern->SetFormLinkInfos(infos);
    pattern->HandleEnableForm(true);

    RefPtr<FrameNode> textNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    EXPECT_NE(textNode, nullptr);
    RefPtr<FrameNode> columnNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<OHOS::Ace::NG::LinearLayoutPattern>(true));
    EXPECT_NE(columnNode, nullptr);
    pattern->AddFormChildNode(FormChildNodeType::FORM_FORBIDDEN_ROOT_NODE, columnNode);
    pattern->AddFormChildNode(FormChildNodeType::FORM_FORBIDDEN_TEXT_NODE, textNode);
    EXPECT_EQ(pattern->formChildrenNodeMap_.size(), 2);
    pattern->HandleEnableForm(true);
    EXPECT_EQ(pattern->formChildrenNodeMap_.size(), 0);

    RefPtr<FrameNode> textNode2 = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    EXPECT_NE(textNode2, nullptr);
    RefPtr<FrameNode> columnNode2 = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<OHOS::Ace::NG::LinearLayoutPattern>(true));
    EXPECT_NE(columnNode2, nullptr);
    pattern->AddFormChildNode(FormChildNodeType::FORM_FORBIDDEN_ROOT_NODE, columnNode2);
    pattern->AddFormChildNode(FormChildNodeType::FORM_FORBIDDEN_TEXT_NODE, textNode2);
    pattern->HandleEnableForm(false);
    EXPECT_EQ(pattern->formChildrenNodeMap_.size(), 2);
}

/**
 * @tc.name: FormPatternTest_010
 * @tc.desc: TakeSurfaceCaptureForUI
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest, FormPatternTest_010, TestSize.Level1)
{
    RefPtr<FrameNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);

    auto host = pattern->GetHost();
    EXPECT_NE(host, nullptr);

    std::vector<std::string> infos;
    std::string tmpStr = "action";
    infos.emplace_back(tmpStr);
    pattern->SetFormLinkInfos(infos);
    pattern->HandleEnableForm(true);

    pattern->isFrsNodeDetached_ = true;
    pattern->isDynamic_ = true;
    pattern->TakeSurfaceCaptureForUI();
    EXPECT_EQ(pattern->formLinkInfos_.empty(), false);

    pattern->isFrsNodeDetached_ = false;
    pattern->isDynamic_ = true;
    pattern->TakeSurfaceCaptureForUI();
    EXPECT_EQ(pattern->formLinkInfos_.empty(), true);
}

/**
 * @tc.name: FormPatternTest_011
 * @tc.desc: SnapshotSurfaceNode
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest, FormPatternTest_011, TestSize.Level1)
{
    RefPtr<FrameNode> frameNode = CreateFromNode();
    auto pattern = frameNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);
    
    auto host = pattern->GetHost();
    pattern->SnapshotSurfaceNode();
    EXPECT_NE(host, nullptr);
}

/**
 * @tc.name: FormPatternTest_012
 * @tc.desc: OnSnapshot
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest, FormPatternTest_012, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);

    auto host = pattern->GetHost();

    pattern->frameNode_ = nullptr;
    pattern->OnSnapshot(nullptr);
    EXPECT_FALSE(pattern->isSnapshot_);

    pattern->frameNode_ = formNode;
    std::shared_ptr<Media::PixelMap> pixelMap = nullptr;
    pattern->OnSnapshot(pixelMap);
    EXPECT_FALSE(pattern->isSnapshot_);

    WeakPtr<FormPattern> weak = Referenced::WeakClaim(Referenced::RawPtr(pattern));
    RefCounter* refBak = pattern->refCounter_;
    weak.refCounter_ = nullptr;
    pattern->OnSnapshot(pixelMap);
    EXPECT_EQ(pattern->isSnapshot_, false);
    weak.refCounter_ = refBak;
}


/**
 * @tc.name: FormPatternTest_014
 * @tc.desc: OnAccessibilityChildTreeRegister OnAccessibilityChildTreeDeregister
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest, FormPatternTest_014, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);

    std::vector<std::string> infos;
    std::string tmpStr = "action";
    infos.emplace_back(tmpStr);
    pattern->SetFormLinkInfos(infos);
    uint32_t windowId = 0;
    int32_t treeId = 0;
    int64_t accessibilityId = 0;
    pattern->OnAccessibilityChildTreeRegister(windowId, treeId, accessibilityId);
    EXPECT_NE(pattern->formManagerBridge_, nullptr);

    pattern->OnAccessibilityChildTreeDeregister();
    EXPECT_NE(pattern->formManagerBridge_, nullptr);
}

/**
 * @tc.name: FormPatternTest_015
 * @tc.desc: OnAccessibilityDumpChildInfo
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest, FormPatternTest_015, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);

    std::vector<std::string> infos;
    std::string tmpStr = "action";
    infos.emplace_back(tmpStr);
    std::vector<std::string> params;
    pattern->OnAccessibilityDumpChildInfo(params, infos);
    EXPECT_NE(pattern->formManagerBridge_, nullptr);
    pattern->UpdateStaticCard();
    auto retRef = pattern->GetAccessibilitySessionAdapter();
    EXPECT_NE(retRef, nullptr);
}

/**
 * @tc.name: FormPatternTest_016
 * @tc.desc: DeleteImageNodeAfterRecover
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest, FormPatternTest_016, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);
    pattern->InitFormManagerDelegate();

    pattern->frameNode_ = nullptr;
    bool isPropertyDiffMarked = formNode->isPropertyDiffMarked_;
    pattern->DeleteImageNodeAfterRecover(false);
    EXPECT_EQ(formNode->isPropertyDiffMarked_, isPropertyDiffMarked);
    pattern->frameNode_ = formNode;

    RefPtr<RenderContext> renderContext = formNode->GetRenderContext();
    formNode->renderContext_ = nullptr;
    pattern->DeleteImageNodeAfterRecover(false);
    EXPECT_EQ(formNode->isPropertyDiffMarked_, isPropertyDiffMarked);
    formNode->renderContext_ = renderContext;

    EXPECT_FALSE(formNode->isPropertyDiffMarked_);
    RefPtr<FormManagerDelegate> formManagerBridge = pattern->formManagerBridge_;
    RefPtr<FrameNode> childNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    pattern->AddFormChildNode(FormChildNodeType::FORM_STATIC_IMAGE_NODE, childNode);
    pattern->formManagerBridge_ = nullptr;
    pattern->DeleteImageNodeAfterRecover(true);;
    EXPECT_EQ(formNode->GetTotalChildCount(), 0);
    EXPECT_FALSE(childNode->isPropertyDiffMarked_);

    pattern->formManagerBridge_ = formManagerBridge;
    pattern->DeleteImageNodeAfterRecover(true);
    EXPECT_FALSE(formNode->isPropertyDiffMarked_);
    pattern->formManagerBridge_ = formManagerBridge;
    EXPECT_EQ(pattern->formManagerBridge_->pointerEventCache_.size(), 0);

    RefPtr<FrameNode> columnNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    EXPECT_NE(columnNode, nullptr);
    pattern->AddFormChildNode(FormChildNodeType::FORM_FORBIDDEN_ROOT_NODE, columnNode);
    pattern->DeleteImageNodeAfterRecover(false);
    EXPECT_FALSE(columnNode->isPropertyDiffMarked_);
    EXPECT_EQ(formNode->GetTotalChildCount(), 0);
}

/**
 * @tc.name: FormPatternTest_017
 * @tc.desc: CreateImageNode
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest, FormPatternTest_017, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);

    pattern->frameNode_ = nullptr;
    RefPtr<FrameNode> result = pattern->CreateImageNode();
    EXPECT_EQ(result, nullptr);result = pattern->CreateImageNode();
    EXPECT_EQ(result, nullptr);
    pattern->AttachToFrameNode(formNode);

    result = pattern->CreateImageNode();
    EXPECT_NE(result, nullptr);
    int32_t num = formNode->GetTotalChildCount();
    EXPECT_EQ(num, 1);
    
    result = pattern->CreateImageNode();
    num = formNode->GetTotalChildCount();
    EXPECT_EQ(num, 2);
    EXPECT_NE(result, nullptr);
}

/**
 * @tc.name: FormPatternTest_018
 * @tc.desc: RemoveFrsNode
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest, FormPatternTest_018, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = FormNode::GetOrCreateFormNode(
        "FormComponent", stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<FormPattern>(); });
    auto pattern = frameNode->GetPattern<FormPattern>();
    stack->Push(frameNode);

    RefPtr<RenderContext> externalRenderContext = pattern->GetExternalRenderContext();
    EXPECT_NE(externalRenderContext, nullptr);
    pattern->externalRenderContext_ = nullptr;
    pattern->RemoveFrsNode();
    EXPECT_FALSE(ContainerScope::CurrentId() == pattern->scopeId_);
    pattern->externalRenderContext_ = externalRenderContext;

    pattern->RemoveFrsNode();
    EXPECT_FALSE(ContainerScope::CurrentId() == pattern->scopeId_);
}

/**
 * @tc.name: FormPatternTest_019
 * @tc.desc: ReleaseRenderer
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest, FormPatternTest_019, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);
    EXPECT_NE(pattern->formManagerBridge_, nullptr);
    EXPECT_NE(ContainerScope::CurrentId, nullptr);

    RefPtr<FormManagerDelegate> formManagerBridge = pattern->formManagerBridge_;
    EXPECT_NE(formManagerBridge, nullptr);

    pattern->formManagerBridge_ = nullptr;
    pattern->ReleaseRenderer();
    EXPECT_NE(formManagerBridge, nullptr);
    pattern->formManagerBridge_ = formManagerBridge;

    pattern->ReleaseRenderer();
    EXPECT_EQ(formManagerBridge->formRendererDispatcher_, nullptr);
}

/**
 * @tc.name: FormPatternTest_020
 * @tc.desc: OnRebuildFrame
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest, FormPatternTest_020, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);

    auto renderContext = formNode->GetRenderContext();
    EXPECT_NE(renderContext, nullptr);
    int32_t num = renderContext->GetHost()->GetChildren().size();
    pattern->OnRebuildFrame();
    EXPECT_EQ(num, 0);
    
    pattern->isSnapshot_ = true;
    pattern->frameNode_ = nullptr;
    pattern->OnRebuildFrame();
    EXPECT_EQ(num, 0);
    pattern->frameNode_ = formNode;

    EXPECT_NE(renderContext, nullptr);
    formNode->renderContext_ = nullptr;
    pattern->OnRebuildFrame();
    EXPECT_EQ(num, 0);
    formNode->renderContext_ = renderContext;

    std::shared_ptr<Media::PixelMap> pixelMap = std::make_shared<Media::PixelMap>();
    pattern->OnSnapshot(pixelMap);
    pattern->HandleOnSnapshot(pixelMap);
    pattern->OnRebuildFrame();
    EXPECT_EQ(pattern->isSnapshot_, true);
    EXPECT_EQ(renderContext->GetHost()->GetChildren().size(), 1);
}

/**
 * @tc.name: FormPatternTest_021
 * @tc.desc: OnVisibleChange
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest, FormPatternTest_021, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);

    pattern->OnVisibleChange(true);
    EXPECT_EQ(pattern->isVisible_, true);

    pattern->OnVisibleChange(false);
    EXPECT_EQ(pattern->isVisible_, false);
}

/**
 * @tc.name: FormPatternTest_002
 * @tc.desc: OnModifyDone
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest, FormPatternTest_002, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);

    pattern->OnModifyDone();
    EXPECT_FALSE(pattern->isSnapshot_);

    auto host = pattern->GetHost();

    auto gestureEventHub = formNode->GetOrCreateGestureEventHub();
    formNode->eventHub_->gestureEventHub_ = nullptr;
    pattern->OnModifyDone();
    EXPECT_FALSE(pattern->isSnapshot_);
    formNode->eventHub_->gestureEventHub_ = gestureEventHub;

    pattern->OnModifyDone();
    EXPECT_EQ(formNode->eventHub_->gestureEventHub_->clickEventActuator_->userCallback_, nullptr);

    host = pattern->GetHost();
    auto layoutProperty = host->layoutProperty_;
    EXPECT_NE(layoutProperty, nullptr);
    host->layoutProperty_ = nullptr;
    pattern->OnModifyDone();
    EXPECT_EQ(formNode->eventHub_->gestureEventHub_->clickEventActuator_->userCallback_, nullptr);
    host->layoutProperty_ = layoutProperty;

    auto &&layoutConstraint = layoutProperty->calcLayoutConstraint_;
    std::unique_ptr<MeasureProperty> calcLayoutConstraint = std::make_unique<MeasureProperty>();
    CalcSize idealSize = { CalcLength(ZERO), CalcLength(ZERO) };
    calcLayoutConstraint->minSize = idealSize;
    calcLayoutConstraint->maxSize = idealSize;

    pattern->OnModifyDone();
    EXPECT_EQ(formNode->eventHub_->gestureEventHub_->clickEventActuator_->userCallback_, nullptr);
    layoutConstraint = std::move(calcLayoutConstraint);
    EXPECT_NE(layoutProperty->calcLayoutConstraint_, nullptr);

    auto size = layoutConstraint->selfIdealSize;
    host->layoutProperty_->calcLayoutConstraint_->selfIdealSize = CalcSize();
    pattern->OnModifyDone();
    EXPECT_EQ(formNode->eventHub_->gestureEventHub_->clickEventActuator_->userCallback_, nullptr);
    host->layoutProperty_->calcLayoutConstraint_->selfIdealSize = size;

    auto sizeWidth = size->Width();
    host->layoutProperty_->calcLayoutConstraint_->selfIdealSize->width_.reset();
    pattern->OnModifyDone();
    EXPECT_EQ(formNode->eventHub_->gestureEventHub_->clickEventActuator_->userCallback_, nullptr);
    host->layoutProperty_->calcLayoutConstraint_->selfIdealSize->width_ = sizeWidth;
}

/**
 * @tc.name: FormPatternTest_006
 * @tc.desc: OnModifyDone
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest, FormPatternTest_006, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);

    auto host = pattern->GetHost();
    auto layoutProperty = host->layoutProperty_;
    auto &&layoutConstraint = layoutProperty->calcLayoutConstraint_;
    layoutConstraint = std::make_unique<MeasureProperty>();
    auto size = layoutConstraint->selfIdealSize;
    auto sizeHeight = size->Height();
    host->layoutProperty_->calcLayoutConstraint_->selfIdealSize->height_.reset();
    pattern->OnModifyDone();
    EXPECT_NE(formNode->eventHub_->gestureEventHub_->clickEventActuator_, nullptr);
    host->layoutProperty_->calcLayoutConstraint_->selfIdealSize->height_ = sizeHeight;

    host->layoutProperty_->calcLayoutConstraint_->selfIdealSize->width_->dimension_.unit_ = DimensionUnit::PERCENT;
    pattern->OnModifyDone();
    EXPECT_NE(formNode->eventHub_->gestureEventHub_->clickEventActuator_, nullptr);
    host->layoutProperty_->calcLayoutConstraint_->selfIdealSize->width_->dimension_.unit_ = DimensionUnit::PX;

    host->layoutProperty_->borderWidth_ = std::make_unique<BorderWidthProperty>();
    std::unique_ptr<BorderWidthProperty>  &&borderWidthProperty = std::move(host->layoutProperty_->borderWidth_);
    EXPECT_NE(borderWidthProperty, nullptr);
    std::optional<Dimension> topDimen = borderWidthProperty->topDimen;
    borderWidthProperty->topDimen->Reset();
    pattern->OnModifyDone();
    EXPECT_NE(formNode->eventHub_->gestureEventHub_->clickEventActuator_, nullptr);
    borderWidthProperty->topDimen = topDimen;

    float borderWidth = 0.0f;
    pattern->OnModifyDone();
    EXPECT_DOUBLE_EQ(borderWidthProperty->topDimen->ConvertToPx(), borderWidth);
}

/**
 * @tc.name: FormPatternTest_013
 * @tc.desc: OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest, FormPatternTest_013, TestSize.Level1)
{
    RefPtr<FrameNode> frameNode = CreateFromNode();
    auto pattern = frameNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(100.0f, 100.0f));
    geometryNode->SetFrameOffset(OffsetF(0, 0));
    RefPtr<LayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<LayoutAlgorithm>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, nullptr);
    EXPECT_NE(layoutWrapper, nullptr);
    auto host = pattern->GetHost();
    EXPECT_NE(host, nullptr);
    pattern->OnAttachToFrameNode();

    config.skipMeasure = true;
    config.skipLayout = true;
    auto layoutAlgorithmWrapper = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm, config.skipMeasure);
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);
    bool isSwap = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_EQ(isSwap, false);

    pattern->frameNode_ = nullptr;
    isSwap = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_EQ(isSwap, false);
    pattern->frameNode_ = frameNode;

    RefPtr<FormLayoutProperty> layoutProperty = host->GetLayoutProperty<FormLayoutProperty>();
    host->layoutProperty_ = nullptr;
    isSwap = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_EQ(isSwap, false);
    host->layoutProperty_ = layoutProperty;

    auto borderWidthProperty = std::make_unique<BorderWidthProperty>();;
    EXPECT_NE(borderWidthProperty, nullptr);
    borderWidthProperty->topDimen->SetValue(1.0);
    isSwap = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_EQ(isSwap, false);
    EXPECT_EQ(pattern->isBeenLayout_, false);

    borderWidthProperty->topDimen->Reset();
    isSwap = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_EQ(isSwap, false);
}

/**
 * @tc.name: FormPatternTest_022
 * @tc.desc: HandleFormComponent
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest, FormPatternTest_022, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);

    auto host = pattern->GetHost();
    auto layoutProperty = host->GetLayoutProperty<FormLayoutProperty>();
    auto info = layoutProperty->GetRequestFormInfo().value_or(RequestFormInfo());
    // info.bundleName != cardInfo_.bundleName
    RequestFormInfo info1;
    info1.bundleName = "cardName";
    pattern->AddFormComponent(info1);
    EXPECT_TRUE(pattern->isJsCard_);

    RequestFormInfo info2;
    info2.bundleName = "cardName2";
    info.allowUpdate = false;
    pattern->HandleFormComponent(info2);
    EXPECT_TRUE(pattern->isJsCard_);

    pattern->HandleFormComponent(info);
    EXPECT_TRUE(pattern->isJsCard_);
    EXPECT_EQ(pattern->cardInfo_.allowUpdate, info.allowUpdate);
}


/**
 * @tc.name: FormPatternTest_023
 * @tc.desc: AddFormComponent
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest, FormPatternTest_023, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    pattern->frameNode_ = formNode;
    EXPECT_NE(pattern, nullptr);

    pattern->isJsCard_ = false;

    RequestFormInfo info;
    pattern->frameNode_ = nullptr;
    pattern->AddFormComponent(info);
    EXPECT_FALSE(pattern->isJsCard_);
    pattern->frameNode_ = formNode;

    pattern->AddFormComponent(info);
    EXPECT_FALSE(pattern->isJsCard_);

    info.width.SetValue(-1.0);
    pattern->AddFormComponent(info);
    EXPECT_FALSE(pattern->isJsCard_);

    info.width.SetValue(1.0);
    info.height.SetValue(1.0);
    pattern->AddFormComponent(info);
    EXPECT_TRUE(pattern->isJsCard_);

    info.shape = FORM_SHAPE_CIRCLE;
    pattern->AddFormComponent(info);
    EXPECT_TRUE(pattern->isJsCard_);

    auto host = pattern->GetHost();
    auto eventHub = host->GetEventHub<EventHub>();
    auto dragStart = [](const RefPtr<OHOS::Ace::DragEvent>& event, const std::string& extraParams) -> NG::DragDropInfo {
        NG::DragDropInfo info;
        info.extraInfo = INIT_VALUE_1;
        return info;
    };
    eventHub->SetOnDragStart(std::move(dragStart));
    pattern->AddFormComponent(info);
    EXPECT_TRUE(eventHub->HasOnDragStart());

    auto context = host->GetContextRefPtr();
    EXPECT_NE(context, nullptr);

    RefPtr<FormManagerDelegate> formManagerBridge = pattern->formManagerBridge_;
    EXPECT_NE(formManagerBridge, nullptr);
    pattern->formManagerBridge_ = nullptr;
    pattern->AddFormComponent(info);
    EXPECT_TRUE(pattern->isJsCard_);

    host->SetLayoutProperty(pattern->CreateLayoutProperty());
    auto layoutProperty = host->GetLayoutProperty<FormLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    auto visible = layoutProperty->GetVisibleType().value_or(VisibleType::VISIBLE);
    EXPECT_NE(visible, VisibleType::GONE);
    pattern->AddFormComponent(info);
    EXPECT_TRUE(pattern->isJsCard_);
}

/**
 * @tc.name: FormPatternTest_024
 * @tc.desc: UpdateFormComponent
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest, FormPatternTest_024, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    pattern->frameNode_ = formNode;
    EXPECT_NE(pattern, nullptr);

    auto host = pattern->GetHost();

    RequestFormInfo info;
    pattern->frameNode_ = nullptr;
    pattern->UpdateFormComponent(info);
    EXPECT_EQ(pattern->cardInfo_.allowUpdate, info.allowUpdate);
    pattern->frameNode_ = formNode;

    RefPtr<LayoutProperty> layoutProperty = pattern->CreateLayoutProperty();
    host->layoutProperty_ = nullptr;
    EXPECT_NE(layoutProperty, nullptr);
    pattern->UpdateFormComponent(info);
    EXPECT_EQ(pattern->cardInfo_.allowUpdate, info.allowUpdate);
    host->layoutProperty_ = layoutProperty;

    info.allowUpdate = !pattern->cardInfo_.allowUpdate;
    pattern->UpdateFormComponent(info);
    EXPECT_EQ(pattern->cardInfo_.allowUpdate, info.allowUpdate);

    EXPECT_EQ(pattern->GetSubContainer(), nullptr);

    WeakPtr<PipelineContext> context = WeakPtr<PipelineContext>();
    auto subContainer = AceType::MakeRefPtr<MockSubContainer>(context);
    pattern->subContainer_ = subContainer;
    pattern->UpdateFormComponent(info);
    EXPECT_NE(pattern->GetSubContainer()->allowUpdate_, pattern->cardInfo_.allowUpdate);


    EXPECT_NE(pattern-> formManagerBridge_, nullptr);
    pattern->InitFormManagerDelegate();
    pattern->UpdateFormComponent(info);
    EXPECT_NE(pattern->subContainer_->allowUpdate_, pattern->cardInfo_.allowUpdate);

    info.width = pattern->cardInfo_.width;
    pattern->UpdateFormComponent(info);
    EXPECT_EQ(pattern->cardInfo_.width, info.width);

    info.obscuredMode  = !pattern->cardInfo_.obscuredMode;
    pattern->UpdateFormComponent(info);
    EXPECT_EQ(pattern->cardInfo_.obscuredMode, info.obscuredMode);

    pattern->formManagerBridge_ = nullptr;
    pattern->UpdateFormComponent(info);
    EXPECT_EQ(pattern->cardInfo_.obscuredMode, info.obscuredMode);
}


/**
 * @tc.name: FormPatternTest_025
 * @tc.desc: UpdateFormComponentSize
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest, FormPatternTest_025, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    pattern->frameNode_ = formNode;
    EXPECT_NE(pattern, nullptr);

    auto host = pattern->GetHost();
    RequestFormInfo info;
    info.width.SetValue(100);
    EXPECT_NE(pattern->formManagerBridge_, nullptr);
    RefPtr<FormManagerDelegate> formManagerBridge = pattern->formManagerBridge_;
    pattern->formManagerBridge_ = nullptr;
    pattern->UpdateFormComponentSize(info);
    EXPECT_EQ(pattern->cardInfo_.width, info.width);

    pattern->formManagerBridge_ = formManagerBridge;
    pattern->UpdateFormComponentSize(info);
    EXPECT_EQ(pattern->cardInfo_.width, info.width);
    EXPECT_NE(host, nullptr);

    RefPtr<FrameNode> columnNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    EXPECT_NE(columnNode, nullptr);
    pattern->AddFormChildNode(FormChildNodeType::FORM_FORBIDDEN_ROOT_NODE, columnNode);
    pattern->UpdateFormComponentSize(info);
    int32_t num = host->GetTotalChildCount();
    EXPECT_EQ(num, 0);

    RefPtr<FrameNode> childNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    pattern->AddFormChildNode(FormChildNodeType::FORM_STATIC_IMAGE_NODE, childNode);
    pattern->UpdateFormComponentSize(info);
    num = host->GetTotalChildCount();
    EXPECT_EQ(num, 0);

    auto columnNode2 = pattern->CreateColumnNode(FormChildNodeType::FORM_SKELETON_NODE);
    EXPECT_EQ(host->GetLastChild(), columnNode2);
    pattern->UpdateFormComponentSize(info);
    num = host->GetTotalChildCount();
    EXPECT_EQ(num, 1);

    host->RemoveChild(columnNode2);
    info.dimension = static_cast<int32_t>(OHOS::AppExecFwk::Constants::Dimension::DIMENSION_1_1);
    BorderRadiusProperty borderRadius;
    Dimension diameter = std::min(info.width, info.height);
    borderRadius.SetRadius(diameter / ARC_RADIUS_TO_DIAMETER);
    pattern->UpdateFormComponentSize(info);
    num = host->GetTotalChildCount();
    EXPECT_EQ(num, 0);

    WeakPtr<PipelineContext> context = WeakPtr<PipelineContext>();
    auto subContainer = AceType::MakeRefPtr<MockSubContainer>(context);
    pattern->subContainer_ = subContainer;
    pattern->UpdateFormComponentSize(info);
    num = host->GetTotalChildCount();
    EXPECT_EQ(num, 0);
}

/**
 * @tc.name: FormPatternTest_026
 * @tc.desc: UpdateTimeLimitFontCfg
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest, FormPatternTest_026, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    pattern->frameNode_ = formNode;
    EXPECT_NE(pattern, nullptr);

    auto host = pattern->GetHost();
    RequestFormInfo info;
    info.width.SetValue(100);
    pattern->UpdateTimeLimitFontCfg();
    int32_t num = host->GetTotalChildCount();
    EXPECT_EQ(num, 0);

    RefPtr<FrameNode> columnNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    EXPECT_NE(columnNode, nullptr);
    pattern->AddFormChildNode(FormChildNodeType::FORM_FORBIDDEN_ROOT_NODE, columnNode);
    RefPtr<RenderContext> renderContext = columnNode->GetRenderContext();
    columnNode->renderContext_ = nullptr;
    pattern->UpdateTimeLimitFontCfg();
    num = host->GetChildren().size();
    EXPECT_EQ(num, 0);
    columnNode->renderContext_ = renderContext;

    pattern->UpdateTimeLimitFontCfg();
    num = host->GetTotalChildCount();
    EXPECT_EQ(num, 0);

    RefPtr<FrameNode> textNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    pattern->AddFormChildNode(FormChildNodeType::FORM_FORBIDDEN_TEXT_NODE, textNode);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    textNode->layoutProperty_ = nullptr;
    pattern->UpdateTimeLimitFontCfg();
    num = host->GetTotalChildCount();
    EXPECT_EQ(num, 0);

    textNode->layoutProperty_ = textLayoutProperty;
    pattern->UpdateTimeLimitFontCfg();
    num = host->GetTotalChildCount();
    EXPECT_EQ(num, 0);

    pattern->UpdateTimeLimitFontCfg();
    num = host->GetTotalChildCount();
    EXPECT_EQ(num, 0);
}

/**
 * @tc.name: FormPatternTest_027
 * @tc.desc: LoadDisableFormStyle
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest, FormPatternTest_027, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    pattern->frameNode_ = formNode;
    EXPECT_NE(pattern, nullptr);

    RequestFormInfo info;
    auto host = pattern->GetHost();
    info.shape = FORM_SHAPE_CIRCLE;
    RefPtr<FormManagerDelegate> formManagerBridge = pattern->formManagerBridge_;
    EXPECT_NE(formManagerBridge, nullptr);
    pattern->formManagerBridge_ = nullptr;
    pattern->LoadDisableFormStyle(info, false);
    int32_t num = host->GetTotalChildCount();
    EXPECT_EQ(num, 0);

    pattern->formManagerBridge_ = formManagerBridge;
    pattern->LoadDisableFormStyle(info, false);
    num = host->GetTotalChildCount();
    EXPECT_EQ(num, 0);

    info.shape = -1;
    RefPtr<FrameNode> textNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    RefPtr<FrameNode> columnNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    EXPECT_NE(columnNode, nullptr);
    pattern->AddFormChildNode(FormChildNodeType::FORM_FORBIDDEN_ROOT_NODE, columnNode);
    pattern->AddFormChildNode(FormChildNodeType::FORM_FORBIDDEN_TEXT_NODE, textNode);
    pattern->LoadDisableFormStyle(info, false);
    num = host->GetTotalChildCount();
    EXPECT_EQ(num, 0);

    int32_t dimension = pattern->cardInfo_.dimension;
    pattern->cardInfo_.dimension = 0;
    pattern->LoadDisableFormStyle(info, true);
    num = host->GetTotalChildCount();
    EXPECT_EQ(num, 0);

    pattern->cardInfo_.dimension = dimension + 1;
    pattern->LoadDisableFormStyle(info, true);
    num = host->GetTotalChildCount();
    EXPECT_EQ(num, 0);

    pattern->frameNode_ = nullptr;
    pattern->LoadDisableFormStyle(info, true);
    num = host->GetTotalChildCount();
    EXPECT_EQ(num, 0);
    pattern->frameNode_ = formNode;
    pattern->OnAttachToFrameNode();

    pattern->LoadDisableFormStyle(info, true);
    num = host->GetTotalChildCount();
    EXPECT_EQ(num, 0);
}

/**
 * @tc.name: FormPatternTest_028
 * @tc.desc: RemoveDisableFormStyle
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest, FormPatternTest_028, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    pattern->frameNode_ = formNode;
    EXPECT_NE(pattern, nullptr);

    RefPtr<FrameNode> textNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    pattern->AddFormChildNode(FormChildNodeType::FORM_FORBIDDEN_TEXT_NODE, textNode);
    RequestFormInfo info;
    auto host = pattern->GetHost();
    pattern->RemoveDisableFormStyle(info);
    int32_t num = host->GetTotalChildCount();
    EXPECT_EQ(num, 0);

    info.dimension = static_cast<int32_t>(OHOS::AppExecFwk::Constants::Dimension::DIMENSION_1_1);
    RefPtr<FormManagerDelegate> formManagerBridge = pattern->formManagerBridge_;
    EXPECT_NE(formManagerBridge, nullptr);
    pattern->formManagerBridge_ = nullptr;
    pattern->RemoveDisableFormStyle(info);
    num = host->GetTotalChildCount();
    EXPECT_EQ(num, 0);

    pattern->formManagerBridge_ = formManagerBridge;
    pattern->RemoveDisableFormStyle(info);
    num = host->GetTotalChildCount();
    EXPECT_EQ(num, 0);
}


/**
 * @tc.name: FormPatternTest_029
 * @tc.desc: LoadFormSkeleton
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest, FormPatternTest_029, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    pattern->frameNode_ = formNode;
    EXPECT_NE(pattern, nullptr);

    auto columnNode = pattern->CreateColumnNode(FormChildNodeType::FORM_SKELETON_NODE);
    auto host = pattern->GetHost();
    EXPECT_EQ(host->GetLastChild(), columnNode);
    pattern->LoadFormSkeleton(false);
    int32_t num = host->GetTotalChildCount();
    EXPECT_EQ(num, 1);

    int32_t dimension = pattern->cardInfo_.dimension;
    pattern->cardInfo_.dimension = 0;
    pattern->LoadFormSkeleton(true);
    num = host->GetTotalChildCount();
    EXPECT_EQ(num, 1);
    pattern->cardInfo_.dimension = dimension + 1;

    pattern->LoadFormSkeleton(true);
    num = host->GetTotalChildCount();
    EXPECT_EQ(num, 1);
}

/**
 * @tc.name: FormPatternTest_030
 * @tc.desc: ShouldLoadFormSkeleton
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest, FormPatternTest_030, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    pattern->frameNode_ = formNode;
    EXPECT_NE(pattern, nullptr);

    bool isTransparencyEnabled = false;
    RequestFormInfo info;
    pattern->isUnTrust_ = true;
    bool ret = pattern->ShouldLoadFormSkeleton(isTransparencyEnabled, info);
    EXPECT_EQ(ret, true);

    pattern->isUnTrust_ = false;
    ret = pattern->ShouldLoadFormSkeleton(isTransparencyEnabled, info);
    EXPECT_EQ(ret, false);

    ret = pattern->ShouldLoadFormSkeleton(isTransparencyEnabled, info);
    EXPECT_EQ(ret, false);

    std::string bundleName = "bundleName";
    std::string abilityName = "abilityName";
    auto wantWrap = info.wantWrap;
    info.wantWrap = nullptr;
    isTransparencyEnabled = true;
    ret = pattern->ShouldLoadFormSkeleton(isTransparencyEnabled, info);
    EXPECT_EQ(ret, false);
    info.wantWrap = wantWrap;

    isTransparencyEnabled = false;
    info.renderingMode = static_cast<int32_t>(OHOS::AppExecFwk::Constants::RenderingMode::FULL_COLOR);
    ret = pattern->ShouldLoadFormSkeleton(isTransparencyEnabled, info);
    EXPECT_EQ(ret, false);
}

/**
 * @tc.name: FormPatternTest_031
 * @tc.desc: GetFormDimensionHeight
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest, FormPatternTest_031, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);

    int32_t dimensionHeight = pattern->GetFormDimensionHeight(0);
    EXPECT_EQ(dimensionHeight, 0);

    dimensionHeight = pattern->GetFormDimensionHeight(0xFFFFFFFF);
    EXPECT_EQ(dimensionHeight, 0);

    pattern->cardInfo_.dimension = static_cast<int32_t>(OHOS::AppExecFwk::Constants::Dimension::DIMENSION_1_1);
    dimensionHeight = pattern->GetFormDimensionHeight(pattern->cardInfo_.dimension);
    EXPECT_EQ(dimensionHeight, 1);

    pattern->cardInfo_.dimension = static_cast<int32_t>(OHOS::AppExecFwk::Constants::Dimension::DIMENSION_1_2);
    dimensionHeight = pattern->GetFormDimensionHeight(pattern->cardInfo_.dimension);
    EXPECT_EQ(dimensionHeight, 1);

    pattern->cardInfo_.dimension = static_cast<int32_t>(OHOS::AppExecFwk::Constants::Dimension::DIMENSION_2_2);
    dimensionHeight = pattern->GetFormDimensionHeight(pattern->cardInfo_.dimension);
    EXPECT_EQ(dimensionHeight, 2);

    pattern->cardInfo_.dimension = static_cast<int32_t>(OHOS::AppExecFwk::Constants::Dimension::DIMENSION_2_4);
    dimensionHeight = pattern->GetFormDimensionHeight(pattern->cardInfo_.dimension);
    EXPECT_EQ(dimensionHeight, 2);

    pattern->cardInfo_.dimension = static_cast<int32_t>(OHOS::AppExecFwk::Constants::Dimension::DIMENSION_4_4);
    dimensionHeight = pattern->GetFormDimensionHeight(pattern->cardInfo_.dimension);
    EXPECT_EQ(dimensionHeight, 4);

    pattern->cardInfo_.dimension = static_cast<int32_t>(OHOS::AppExecFwk::Constants::Dimension::DIMENSION_6_4);
    dimensionHeight = pattern->GetFormDimensionHeight(pattern->cardInfo_.dimension);
    EXPECT_EQ(dimensionHeight, 6);
}

/**
 * @tc.name: FormPatternTest_032
 * @tc.desc: CreateTimeLimitNode
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest, FormPatternTest_032, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);

    int32_t num = formNode->GetTotalChildCount();
    pattern->frameNode_ = nullptr;
    RefPtr<FrameNode> node = pattern->CreateTimeLimitNode();
    EXPECT_EQ(node, nullptr);
    pattern->frameNode_ = formNode;

    node = pattern->CreateTimeLimitNode();
    EXPECT_EQ(node, nullptr);
    EXPECT_EQ(num, 0);
}

/**
 * @tc.name: FormPatternTest_033
 * @tc.desc: CreateSkeletonView CreateRectNode
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest, FormPatternTest_033, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);

    pattern->cardInfo_.dimension = static_cast<int32_t>(OHOS::AppExecFwk::Constants::Dimension::DIMENSION_1_1);
    int32_t dimension = pattern->cardInfo_.dimension;
    int32_t dimensionHeight = pattern->GetFormDimensionHeight(dimension);
    EXPECT_GT(dimensionHeight, 0);


    pattern->RemoveFormChildNode(FormChildNodeType::FORM_SKELETON_NODE);
    auto columnNode = pattern->CreateColumnNode(FormChildNodeType::FORM_SKELETON_NODE);
    EXPECT_NE(columnNode, nullptr);

    double cardWidth = pattern->cardInfo_.width.Value();
    double cardHeight = pattern->cardInfo_.height.Value();
    auto colorMode = SystemProperties::GetColorMode();
    bool isDarkMode = colorMode == ColorMode::DARK;
    std::shared_ptr<FormSkeletonParams> params = std::make_shared<FormSkeletonParams>(cardWidth,
        cardHeight, dimension, dimensionHeight, isDarkMode);
    pattern->CreateSkeletonView(columnNode, params, dimensionHeight);
    int32_t num = formNode->GetTotalChildCount();
    EXPECT_GT(num, 0);

    pattern->RemoveFormChildNode(FormChildNodeType::FORM_SKELETON_NODE);
    num = formNode->GetTotalChildCount();
    EXPECT_EQ(num, 0);

    pattern->cardInfo_.dimension = static_cast<int32_t>(OHOS::AppExecFwk::Constants::Dimension::DIMENSION_2_2);
    dimensionHeight = pattern->GetFormDimensionHeight(pattern->cardInfo_.dimension);
    pattern->CreateSkeletonView(columnNode, params, dimensionHeight);
    int32_t num1 = formNode->GetTotalChildCount();
    EXPECT_EQ(num1, num);
}

/**
 * @tc.name: FormPatternTest_034
 * @tc.desc: CreateColumnNode
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest, FormPatternTest_034, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);

    pattern->frameNode_ = nullptr;
    auto res = pattern->CreateColumnNode(FormChildNodeType::FORM_SKELETON_NODE);
    EXPECT_EQ(res, nullptr);
    pattern->frameNode_ = formNode;

    res = pattern->CreateColumnNode(FormChildNodeType::FORM_SKELETON_NODE);
    EXPECT_NE(res, nullptr);
    EXPECT_EQ(res->GetTag(), "Column");
}

/**
 * @tc.name: FormPatternTest_035
 * @tc.desc: InitFormManagerDelegate
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest, FormPatternTest_035, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto formNode = FormNode::GetOrCreateFormNode(
        "FormComponent", stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<FormPattern>(); });
    auto pattern = formNode->GetPattern<FormPattern>();
    pattern->frameNode_ = formNode;
    EXPECT_NE(pattern->formManagerBridge_, nullptr);

    auto host = pattern->GetHost();
    auto context = host->GetContextRefPtr();
    // pattern->formManagerBridge_ = AceType::MakeRefPtr<FormManagerDelegate>(context);
    pattern->InitFormManagerDelegate();
    EXPECT_NE(pattern->accessibilitySessionAdapter_, nullptr);
    pattern->formManagerBridge_ = nullptr;

    pattern->frameNode_ = nullptr;
    pattern->InitFormManagerDelegate();
    EXPECT_EQ(pattern->formManagerBridge_, nullptr);

    pattern->frameNode_ = formNode;
    host = pattern->GetHost();

    FormManager::GetInstance().SetFormUtils(nullptr);
    pattern->InitFormManagerDelegate();
    EXPECT_EQ(pattern->formManagerBridge_->formUtils_, nullptr);

    auto formUtils = std::make_shared<MockFormUtils>();
    FormManager::GetInstance().SetFormUtils(formUtils);
    pattern->formManagerBridge_ = AceType::MakeRefPtr<FormManagerDelegate>(context);
    pattern->InitFormManagerDelegate();
    EXPECT_EQ(pattern->formManagerBridge_->formUtils_, nullptr);
}

/**
 * @tc.name: FormPatternTest_036
 * @tc.desc: GetRectRelativeToWindow
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest, FormPatternTest_036, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);

    int32_t top = 0;
    int32_t lef = 0;
    pattern->frameNode_ = nullptr;
    pattern->GetRectRelativeToWindow(top, lef);
    EXPECT_EQ(top, 0);
    EXPECT_EQ(lef, 0);

    pattern->frameNode_ = formNode;
    pattern->GetRectRelativeToWindow(top, lef);
    EXPECT_EQ(top, 0);
    EXPECT_EQ(lef, 0);
}

/**
 * @tc.name: FormPatternTest_037
 * @tc.desc: ProcDeleteImageNode
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest, FormPatternTest_037, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);

    RefPtr<FrameNode> childNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    pattern->AddFormChildNode(FormChildNodeType::FORM_STATIC_IMAGE_NODE, childNode);
    AAFwk::Want want;

    pattern->ProcDeleteImageNode(want);
    int32_t num = formNode->GetTotalChildCount();
    EXPECT_EQ(num, 0);

    want.SetParam(OHOS::AppExecFwk::Constants::FORM_IS_RECOVER_FORM, false);
    pattern->AddFormChildNode(FormChildNodeType::FORM_STATIC_IMAGE_NODE, childNode);
    pattern->ProcDeleteImageNode(want);
    num = formNode->GetTotalChildCount();
    EXPECT_EQ(num, 0);
}

/**
 * @tc.name: FormPatternTest_038
 * @tc.desc: AttachRSNode
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest, FormPatternTest_038, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);

    std::shared_ptr<Rosen::RSSurfaceNode> node;
    AAFwk::Want want;
    node->CreateNodeInRenderThread();

    pattern->frameNode_ = nullptr;
    pattern->AttachRSNode(node, want);
    EXPECT_FALSE(pattern->isBeenLayout_);

    pattern->frameNode_ = formNode;
    RefPtr<RenderContext> externalRenderContext = pattern->GetExternalRenderContext();
    pattern->externalRenderContext_ = nullptr;
    pattern->AttachRSNode(node, want);
    EXPECT_FALSE(pattern->isBeenLayout_);

    pattern->externalRenderContext_ = externalRenderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(100.0f, 100.0f));
    geometryNode->SetFrameOffset(OffsetF(0, 0));
    RefPtr<LayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<LayoutAlgorithm>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(formNode, geometryNode, nullptr);
    pattern->OnAttachToFrameNode();
    config.skipMeasure = false;
    ASSERT_NE(pattern->formManagerBridge_, nullptr);
    pattern->cardInfo_.allowUpdate = !formInfo.allowUpdate;
    auto isSwap = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_EQ(pattern->cardInfo_.allowUpdate, formInfo.allowUpdate);
    EXPECT_EQ(isSwap, true);
    EXPECT_TRUE(pattern->isBeenLayout_);

    auto host = pattern->GetHost();
    geometryNode = host->GetGeometryNode();
    auto renderContext = host->GetRenderContext();
    EXPECT_NE(renderContext, nullptr);

    int32_t num = host->GetTotalChildCount();
    pattern->AttachRSNode(node, want);
    int32_t num1 = host->GetTotalChildCount();
    EXPECT_EQ(num, num1);

    host->geometryNode_ = geometryNode;
    pattern->AttachRSNode(node, want);
    num1 = host->GetTotalChildCount();
    EXPECT_EQ(num, num1);

    want.SetParam(OHOS::AppExecFwk::Constants::FORM_IS_RECOVER_FORM, true);
    pattern->AttachRSNode(node, want);
    num = host->GetTotalChildCount();
    EXPECT_EQ(num, num1);
}

/**
 * @tc.name: FormPatternTest_039
 * @tc.desc: AttachRSNode
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest, FormPatternTest_039, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);

    auto host = pattern->GetHost();
    std::shared_ptr<Rosen::RSSurfaceNode> node;
    AAFwk::Want want;
    node->CreateNodeInRenderThread();

    want.SetParam(OHOS::AppExecFwk::Constants::FORM_IS_RECOVER_FORM, true);
    pattern->AttachRSNode(node, want);
    int32_t num = host->GetTotalChildCount();
    EXPECT_EQ(num, 0);

    auto renderContext = host->GetRenderContext();
    host->renderContext_ = nullptr;
    pattern->AttachRSNode(node, want);
    int32_t num1 = host->GetTotalChildCount();
    EXPECT_EQ(num, num1);

    host->renderContext_ = renderContext;
    pattern->AttachRSNode(node, want);
    num1 = host->GetTotalChildCount();
    EXPECT_EQ(num, num1);
}


/**
 * @tc.name: FormPatternTest_040
 * @tc.desc: FireFormSurfaceNodeCallback
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest, FormPatternTest_040, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);

    std::shared_ptr<Rosen::RSSurfaceNode> node;
    std::string surfaceNodeName = "ArkTSCardNode";
    struct Rosen::RSSurfaceNodeConfig surfaceNodeConfig = { .SurfaceNodeName = surfaceNodeName };
    node = std::make_shared<OHOS::Rosen::RSSurfaceNode>(surfaceNodeConfig, true);
    AAFwk::Want want;

    want.SetParam(OHOS::AppExecFwk::Constants::FORM_IS_DYNAMIC, true);
    want.SetParam(OHOS::AppExecFwk::Constants::FORM_IS_RECOVER_FORM, false);
    pattern->FireFormSurfaceNodeCallback(nullptr, want);
    EXPECT_FALSE(pattern->isLoaded_);

    pattern->frameNode_ = nullptr;
    pattern->FireFormSurfaceNodeCallback(node, want);
    EXPECT_FALSE(pattern->isLoaded_);

    pattern->frameNode_ = formNode;
    auto host = pattern->GetHost();
    auto layoutProperty = host->GetLayoutProperty<FormLayoutProperty>();
    host->layoutProperty_ = layoutProperty;

    auto parent = host->GetParent();
    host->parent_ = nullptr;
    pattern->FireFormSurfaceNodeCallback(node, want);
    EXPECT_TRUE(pattern->isLoaded_);
    host->parent_ = parent;

    auto renderContext = host->GetRenderContext();
    host->renderContext_ = nullptr;
    pattern->FireFormSurfaceNodeCallback(node, want);
    EXPECT_TRUE(pattern->isLoaded_);
    host->renderContext_ = renderContext;

    auto formNode1 = AceType::DynamicCast<FormNode>(host);
    pattern->frameNode_ = nullptr;
    pattern->FireFormSurfaceNodeCallback(node, want);
    EXPECT_TRUE(pattern->isLoaded_);
    pattern->frameNode_ = formNode1;

    pattern->FireFormSurfaceNodeCallback(node, want);
    EXPECT_TRUE(pattern->isLoaded_);
}

/**
 * @tc.name: FormPatternTest_041
 * @tc.desc: DelayDeleteImageNode
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest, FormPatternTest_041, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);

    pattern->frameNode_ = nullptr;
    pattern->DelayDeleteImageNode(false);
    pattern->frameNode_ = formNode;

    auto host = pattern->GetHost();
    auto context = host->GetContext();
    host->context_ = nullptr;
    pattern->DelayDeleteImageNode(false);
    host->context_ = context;
}

/**
 * @tc.name: FormPatternTest_042
 * @tc.desc: FireFormSurfaceChangeCallback
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest, FormPatternTest_042, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: FormPatternTest_043
 * @tc.desc: FireFormSurfaceDetachCallback
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest, FormPatternTest_043, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);
    
    pattern->FireFormSurfaceDetachCallback();
    EXPECT_TRUE(pattern->isFrsNodeDetached_);
}

/**
 * @tc.name: FormPatternTest_044
 * @tc.desc: CreateCardContainer
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest, FormPatternTest_044, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();

    auto host = pattern->GetHost();
    pattern->subContainer_ = nullptr;
    pattern->frameNode_ = nullptr;
    pattern->CreateCardContainer();
    EXPECT_EQ(pattern->subContainer_, nullptr);

    pattern->frameNode_ = formNode;
    auto context = host->GetContextRefPtr();
    host->context_ = nullptr;
    pattern->CreateCardContainer();
    EXPECT_NE(pattern->subContainer_, nullptr);

    auto layoutProperty = host->GetLayoutProperty<FormLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    host->layoutProperty_ = nullptr;
    pattern->CreateCardContainer();
    EXPECT_NE(pattern->subContainer_, nullptr);

    host->layoutProperty_ = layoutProperty;
    pattern->cardInfo_.id = 0;
    pattern->CreateCardContainer();
    EXPECT_NE(pattern->subContainer_, nullptr);

    auto subContainer = AceType::MakeRefPtr<MockSubContainer>(context);
    subContainer->instanceId_ = 0;
    pattern->subContainer_ = subContainer;
    pattern->cardInfo_.id = 1;
    RefPtr<Container> conainer = Container::Current();
    conainer->SetUseNewPipeline();
    EXPECT_EQ(Container::IsCurrentUseNewPipeline(), true);
    pattern->CreateCardContainer();
    EXPECT_NE(pattern->subContainer_, nullptr);

    pattern->subContainer_ = subContainer;
    EXPECT_EQ(pattern->subContainer_, subContainer);
    pattern->CreateCardContainer();
    EXPECT_NE(pattern->subContainer_, subContainer);

    FormManager::GetInstance().AddSubContainer(1, subContainer);
    EXPECT_EQ(Container::IsCurrentUseNewPipeline(), true);
    EXPECT_EQ(
        formNode->GetContextRefPtr()->GetInstanceId(), FormManager::GetInstance().GetSubContainer(1)->GetInstanceId());
    pattern->CreateCardContainer();
    EXPECT_EQ(FormManager::GetInstance().GetSubContainer(1), nullptr);
}

/**
 * @tc.name: FormPatternTest_045
 * @tc.desc: CreateCardContainer
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest, FormPatternTest_045, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);

    auto host = pattern->GetHost();
    auto context = host->GetContextRefPtr();
    auto subContainer = AceType::MakeRefPtr<MockSubContainer>(context);
    FormManager::GetInstance().AddSubContainer(1, subContainer);
    pattern->subContainer_ = nullptr;
    subContainer->cardType_ = FrontendType::ETS_CARD;
    pattern->CreateCardContainer();
    EXPECT_EQ(FormManager::GetInstance().GetSubContainer(1), subContainer);
    EXPECT_NE(pattern->subContainer_, subContainer);

    pattern->subContainer_ = nullptr;
    subContainer->cardType_ = FrontendType::JS_CARD;
    subContainer->instanceId_ = 2;
    pattern->CreateCardContainer();
    EXPECT_EQ(FormManager::GetInstance().GetSubContainer(1), subContainer);
    EXPECT_NE(pattern->subContainer_, subContainer);
}

/**
 * @tc.name: FormPatternTest_046
 * @tc.desc: FireOnErrorEvent
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest, FormPatternTest_046, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);
    const std::string code = "errcode";
    const std::string msg = "hello";

    pattern->frameNode_ = nullptr;

    pattern->FireOnErrorEvent(code, msg);
    EXPECT_EQ(pattern->GetHost(), nullptr);
    pattern->frameNode_ = formNode;

    auto host = pattern->GetHost();
    auto eventHub = formNode->GetEventHub<FormEventHub>();
    host->eventHub_ = nullptr;
    pattern->FireOnErrorEvent(code, msg);
    EXPECT_FALSE(pattern->isSnapshot_);

    host->eventHub_ = eventHub;
    pattern->FireOnErrorEvent(code, msg);
    EXPECT_FALSE(pattern->isSnapshot_);
}

/**
 * @tc.name: FormPatternTest_047
 * @tc.desc: FireOnUninstallEvent
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest, FormPatternTest_047, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);

    pattern->frameNode_ = nullptr;
    int64_t id = 1;
    pattern->FireOnUninstallEvent(id);
    EXPECT_EQ(pattern->GetHost(), nullptr);
    pattern->frameNode_ = formNode;

    auto host = pattern->GetHost();
    auto eventHub = formNode->GetEventHub<FormEventHub>();
    host->eventHub_ = nullptr;
    pattern->FireOnUninstallEvent(id);
    EXPECT_FALSE(pattern->isSnapshot_);

    host->eventHub_ = eventHub;
    pattern->FireOnUninstallEvent(id);
    EXPECT_FALSE(pattern->isSnapshot_);
}

/**
 * @tc.name: FormPatternTest_048
 * @tc.desc: FireOnAcquiredEvent
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest, FormPatternTest_048, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);

    pattern->frameNode_ = nullptr;
    int64_t id = 1;

    pattern->FireOnAcquiredEvent(id);
    EXPECT_EQ(pattern->GetHost(), nullptr);
    pattern->frameNode_ = formNode;

    auto host = pattern->GetHost();
    auto eventHub = formNode->GetEventHub<FormEventHub>();
    host->eventHub_ = nullptr;
    pattern->FireOnAcquiredEvent(id);
    EXPECT_FALSE(pattern->isSnapshot_);

    host->eventHub_ = eventHub;
    pattern->FireOnAcquiredEvent(id);
    EXPECT_FALSE(pattern->isSnapshot_);
}

/**
 * @tc.name: FormPatternTest_049
 * @tc.desc: FireOnRouterEvent
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest, FormPatternTest_049, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);

    std::string action = "{\"action\":\"router\"}";
    auto json = JsonUtil::Create(true);
    json->Put("action", "message");
    pattern->frameNode_ = nullptr;
    pattern->FireOnRouterEvent(json);
    auto eventAction = JsonUtil::ParseJsonString(action);
    pattern->frameNode_ = nullptr;
    pattern->FireOnRouterEvent(eventAction);
    EXPECT_EQ(pattern->GetHost(), nullptr);
    pattern->frameNode_ = formNode;

    auto host = pattern->GetHost();
    auto eventHub = formNode->GetEventHub<FormEventHub>();
    host->eventHub_ = nullptr;
    pattern->FireOnRouterEvent(eventAction);
    EXPECT_FALSE(pattern->isSnapshot_);

    host->eventHub_ = eventHub;
    pattern->FireOnRouterEvent(eventAction);
    EXPECT_FALSE(pattern->isSnapshot_);
}

/**
 * @tc.name: FormPatternTest_050
 * @tc.desc: FireOnLoadEvent
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest, FormPatternTest_050, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);

    pattern->frameNode_ = nullptr;
    pattern->FireOnLoadEvent();
    EXPECT_EQ(pattern->GetHost(), nullptr);
    pattern->frameNode_ = formNode;

    auto host = pattern->GetHost();
    auto eventHub = formNode->GetEventHub<FormEventHub>();
    host->eventHub_ = nullptr;
    pattern->FireOnLoadEvent();
    EXPECT_FALSE(pattern->isSnapshot_);

    host->eventHub_ = eventHub;
    eventHub->SetOnLoad([](const std::string& string) { ASSERT_EQ(string, ""); });
    pattern->FireOnLoadEvent();
    EXPECT_FALSE(pattern->isSnapshot_);
}

/**
 * @tc.name: FormPatternTest_051
 * @tc.desc: GetDrawDelegate
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest, FormPatternTest_051, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);

    auto drawRSFrame = pattern->GetDrawDelegate();
    EXPECT_NE(drawRSFrame, nullptr);
}

/**
 * @tc.name: FormPatternTest_052
 * @tc.desc: SetNonTransparentAfterRecover
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest, FormPatternTest_052, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);
    pattern->frameNode_ = formNode;
    RefPtr<RenderContext> externalRenderContext = pattern->GetExternalRenderContext();
    externalRenderContext->SetOpacity(TRANSPARENT_VAL);
    pattern->SetNonTransparentAfterRecover();
    EXPECT_EQ(formNode->GetTotalChildCount(), 0);
}
} // namespace OHOS::Ace::NG
