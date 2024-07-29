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

#include "core/components/form/resource/form_manager_delegate.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/form/form_node.h"
#include "core/components_ng/pattern/form/form_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
constexpr int32_t MAX_CLICK_DURATION = 500000000; // ns
constexpr int32_t FORM_SHAPE_CIRCLE = 2;
// constexpr char FORM_RENDERER_DISPATCHER[] = "ohos.extra.param.key.process_on_form_renderer_dispatcher";
}
class FormPatternTest : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
protected:
    static RefPtr<FormNode> CreateFromNode();
};

void FormPatternTest::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void FormPatternTest::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
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
    auto taskExecutor = pipeline->GetTaskExecutor();
    EXPECT_EQ(taskExecutor, nullptr);
    pattern->HandleSnapshot(delayTime);
    pipeline->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    EXPECT_NE(pipeline->taskExecutor_, nullptr);
    taskExecutor = pipeline->GetTaskExecutor();
    uint32_t taskNum = taskExecutor->GetTotalTaskNum(TaskExecutor::TaskType::UI);
    EXPECT_EQ(taskNum, 0);

    WeakPtr<FormPattern> weak = Referenced::WeakClaim(Referenced::RawPtr(pattern));
    RefCounter* refBak = pattern->refCounter_;
    weak.refCounter_ = nullptr;
    pattern->HandleSnapshot(delayTime);
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
 * @tc.name: FormPatternTest_013
 * @tc.desc: HandleOnSnapshot
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest, FormPatternTest_013, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);

    pattern->HandleOnSnapshot(nullptr);
    EXPECT_FALSE(pattern->isSnapshot_);

    std::shared_ptr<Media::PixelMap>  pixelMap = std::make_shared<Media::PixelMap>();
    EXPECT_NE(pixelMap, nullptr);
    pattern->HandleOnSnapshot(pixelMap);
    EXPECT_EQ(pattern->isSnapshot_, true);
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
} // namespace OHOS::Ace::NG