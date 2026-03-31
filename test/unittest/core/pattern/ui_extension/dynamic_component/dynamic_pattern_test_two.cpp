/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "gtest/gtest.h"
#include "base/memory/ace_type.h"
#define private public
#define protected public
#include "accessibility_element_info.h"
#include "adapter/ohos/entrance/dynamic_component/dynamic_component_renderer_impl.h"
#include "adapter/ohos/entrance/mmi_event_convertor.h"
#include "adapter/ohos/osal/want_wrap_ohos.h"
#include "core/common/window.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/ui_extension/dynamic_component/dynamic_pattern.h"
#include "core/components_ng/pattern/ui_extension/session_wrapper.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_model.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_model_ng.h"
#include "frameworks/core/components_ng/pattern/ui_extension/platform_pattern.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_manager.h"
#include "frameworks/core/event/pointer_event.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/common/mock_frontend.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
    const std::string DYNAMIC_COMPONENT_ETS_TAG = "DynamicComponent";
    const std::string TAG = "Test node tag";
} // namespace

class DynamicPatternTestNgTwo : public testing::Test {
public:
    void SetUp() override;
    void TearDown() override;
    void JsonExpect(std::unique_ptr<JsonValue>& json,
        RefPtr<DynamicPattern> dynamicPattern);
};

void DynamicPatternTestNgTwo::SetUp()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->pipelineContext_ = PipelineBase::GetCurrentContext();
}

void DynamicPatternTestNgTwo::TearDown()
{
    MockContainer::Current()->pipelineContext_ = nullptr;
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: DynamicPatternTest001
 * @tc.desc: Test DynamicPattern OnFrameNodeChanged
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgTwo, DynamicPatternTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get DynamicPattern
     */
    auto dynamicNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto dynamicNode = FrameNode::GetOrCreateFrameNode(
        DYNAMIC_COMPONENT_ETS_TAG, dynamicNodeId, []() {
            return AceType::MakeRefPtr<DynamicPattern>();
        });
    EXPECT_NE(dynamicNode, nullptr);
    EXPECT_EQ(dynamicNode->GetTag(), V2::DYNAMIC_COMPONENT_ETS_TAG);
    auto dynamicPattern = dynamicNode->GetPattern<DynamicPattern>();
    EXPECT_NE(dynamicPattern, nullptr);

    /**
     * @tc.steps: step2. call OnFrameNodeChanged.
     */
    FrameNodeChangeInfoFlag flag = FRAME_NODE_CHANGE_INFO_NONE;
    dynamicPattern->OnFrameNodeChanged(flag);
    EXPECT_EQ(dynamicPattern->rectInfo_.left, dynamicPattern->GetAccessibilityRectInfo().left);
    EXPECT_EQ(dynamicPattern->rectInfo_.scaleX, dynamicPattern->GetAccessibilityRectInfo().scaleX);

    flag = FRAME_NODE_CHANGE_START_SCROLL;
    dynamicPattern->OnFrameNodeChanged(flag);
    EXPECT_EQ(dynamicPattern->rectInfo_.left, dynamicPattern->GetAccessibilityRectInfo().left);
    EXPECT_EQ(dynamicPattern->rectInfo_.scaleX, dynamicPattern->GetAccessibilityRectInfo().scaleX);

    flag = FRAME_NODE_CHANGE_END_SCROLL;
    dynamicPattern->OnFrameNodeChanged(flag);
    EXPECT_EQ(dynamicPattern->rectInfo_.left, dynamicPattern->GetAccessibilityRectInfo().left);
    EXPECT_EQ(dynamicPattern->rectInfo_.scaleX, dynamicPattern->GetAccessibilityRectInfo().scaleX);

    flag = FRAME_NODE_CHANGE_START_ANIMATION;
    dynamicPattern->OnFrameNodeChanged(flag);
    EXPECT_EQ(dynamicPattern->rectInfo_.left, dynamicPattern->GetAccessibilityRectInfo().left);
    EXPECT_EQ(dynamicPattern->rectInfo_.scaleX, dynamicPattern->GetAccessibilityRectInfo().scaleX);

    flag = FRAME_NODE_CHANGE_GEOMETRY_CHANGE;
    dynamicPattern->OnFrameNodeChanged(flag);
    EXPECT_EQ(dynamicPattern->rectInfo_.left, dynamicPattern->GetAccessibilityRectInfo().left);
    EXPECT_EQ(dynamicPattern->rectInfo_.scaleX, dynamicPattern->GetAccessibilityRectInfo().scaleX);

    flag = FRAME_NODE_CHANGE_TRANSFORM_CHANGE;
    dynamicPattern->OnFrameNodeChanged(flag);
    EXPECT_EQ(dynamicPattern->rectInfo_.left, dynamicPattern->GetAccessibilityRectInfo().left);
    EXPECT_EQ(dynamicPattern->rectInfo_.scaleX, dynamicPattern->GetAccessibilityRectInfo().scaleX);

    flag = FRAME_NODE_CHANGE_TRANSITION_START;
    dynamicPattern->OnFrameNodeChanged(flag);
    EXPECT_EQ(dynamicPattern->rectInfo_.left, dynamicPattern->GetAccessibilityRectInfo().left);
    EXPECT_EQ(dynamicPattern->rectInfo_.scaleX, dynamicPattern->GetAccessibilityRectInfo().scaleX);

    flag = FRAME_NODE_CONTENT_CLIP_CHANGE;
    dynamicPattern->OnFrameNodeChanged(flag);
    EXPECT_EQ(dynamicPattern->rectInfo_.left, dynamicPattern->GetAccessibilityRectInfo().left);
    EXPECT_EQ(dynamicPattern->rectInfo_.scaleX, dynamicPattern->GetAccessibilityRectInfo().scaleX);
}

/**
 * @tc.name: DynamicPatternTest002
 * @tc.desc: Test DynamicPattern IsAncestorNodeGeometryChange
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgTwo, DynamicPatternTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get DynamicPattern
     */
    auto dynamicNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto dynamicNode = FrameNode::GetOrCreateFrameNode(
        DYNAMIC_COMPONENT_ETS_TAG, dynamicNodeId, []() {
            return AceType::MakeRefPtr<DynamicPattern>();
        });
    EXPECT_NE(dynamicNode, nullptr);
    EXPECT_EQ(dynamicNode->GetTag(), V2::DYNAMIC_COMPONENT_ETS_TAG);
    auto dynamicPattern = dynamicNode->GetPattern<DynamicPattern>();
    EXPECT_NE(dynamicPattern, nullptr);

    /**
     * @tc.steps: step2. call IsAncestorNodeGeometryChange.
     */
    FrameNodeChangeInfoFlag flag = FRAME_NODE_CHANGE_GEOMETRY_CHANGE | FRAME_NODE_CHANGE_TRANSFORM_CHANGE;
    bool result = dynamicPattern->IsAncestorNodeGeometryChange(flag);
    EXPECT_TRUE(result);

    flag = FRAME_NODE_CHANGE_TRANSFORM_CHANGE;
    result = dynamicPattern->IsAncestorNodeGeometryChange(flag);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: DynamicPatternTest003
 * @tc.desc: Test DynamicPattern IsAncestorNodeTransformChange
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgTwo, DynamicPatternTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get DynamicPattern
     */
    auto dynamicNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto dynamicNode = FrameNode::GetOrCreateFrameNode(
        DYNAMIC_COMPONENT_ETS_TAG, dynamicNodeId, []() {
            return AceType::MakeRefPtr<DynamicPattern>();
        });
    EXPECT_NE(dynamicNode, nullptr);
    EXPECT_EQ(dynamicNode->GetTag(), V2::DYNAMIC_COMPONENT_ETS_TAG);
    auto dynamicPattern = dynamicNode->GetPattern<DynamicPattern>();
    EXPECT_NE(dynamicPattern, nullptr);

    /**
     * @tc.steps: step2. call IsAncestorNodeTransformChange.
     */
    FrameNodeChangeInfoFlag flag = FRAME_NODE_CHANGE_TRANSFORM_CHANGE | FRAME_NODE_CHANGE_GEOMETRY_CHANGE;
    bool result = dynamicPattern->IsAncestorNodeTransformChange(flag);
    EXPECT_TRUE(result);

    flag = FRAME_NODE_CHANGE_GEOMETRY_CHANGE;
    result = dynamicPattern->IsAncestorNodeTransformChange(flag);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: DynamicPatternTest004
 * @tc.desc: Test DynamicPattern OnDetachContext
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgTwo, DynamicPatternTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get DynamicPattern
     */
    auto dynamicNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto dynamicNode = FrameNode::GetOrCreateFrameNode(
        DYNAMIC_COMPONENT_ETS_TAG, dynamicNodeId, []() {
            return AceType::MakeRefPtr<DynamicPattern>();
        });
    EXPECT_NE(dynamicNode, nullptr);
    EXPECT_EQ(dynamicNode->GetTag(), V2::DYNAMIC_COMPONENT_ETS_TAG);
    auto dynamicPattern = dynamicNode->GetPattern<DynamicPattern>();
    EXPECT_NE(dynamicPattern, nullptr);
    auto pipeline = MockPipelineContext::GetCurrent();
    EXPECT_NE(pipeline, nullptr);

    /**
     * @tc.steps: step2. call OnDetachContext.
     */
    auto host = dynamicPattern->GetHost();
    EXPECT_NE(host, nullptr);
    pipeline->SetInstanceId(123);
    auto rawPipeline = reinterpret_cast<PipelineContext*>(Referenced::RawPtr(pipeline));
    dynamicPattern->OnDetachContext(rawPipeline);
    dynamicPattern->OnDetachContext(nullptr);

    dynamicPattern->host_ = nullptr;
    dynamicPattern->OnDetachContext(rawPipeline);
    dynamicPattern->OnDetachContext(nullptr);
}

/**
 * @tc.name: DynamicPatternTest005
 * @tc.desc: Test DynamicPattern UnregisterSingleHandTransformChangedCallback
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgTwo, DynamicPatternTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get DynamicPattern
     */
    auto dynamicNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto dynamicNode = FrameNode::GetOrCreateFrameNode(
        DYNAMIC_COMPONENT_ETS_TAG, dynamicNodeId, []() {
            return AceType::MakeRefPtr<DynamicPattern>();
        });
    EXPECT_NE(dynamicNode, nullptr);
    EXPECT_EQ(dynamicNode->GetTag(), V2::DYNAMIC_COMPONENT_ETS_TAG);
    auto dynamicPattern = dynamicNode->GetPattern<DynamicPattern>();
    EXPECT_NE(dynamicPattern, nullptr);
    auto pipeline = MockPipelineContext::GetCurrent();
    EXPECT_NE(pipeline, nullptr);

    /**
     * @tc.steps: step2. call UnregisterSingleHandTransformChangedCallback.
     */
    auto host = dynamicPattern->GetHost();
    EXPECT_NE(host, nullptr);
    int32_t instanceId = 1;
    dynamicPattern->UnRegisterSingleHandTransformChangedCallback(instanceId);

    dynamicPattern->host_ = nullptr;
    dynamicPattern->UnRegisterSingleHandTransformChangedCallback(instanceId);
}

/**
 * @tc.name: DynamicPatternTest006
 * @tc.desc: Test DynamicPattern UnRegisterAccessibilitySAObserverCallback
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgTwo, DynamicPatternTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get DynamicPattern
     */
    auto dynamicNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto dynamicNode = FrameNode::GetOrCreateFrameNode(
        DYNAMIC_COMPONENT_ETS_TAG, dynamicNodeId, []() {
            return AceType::MakeRefPtr<DynamicPattern>();
        });
    EXPECT_NE(dynamicNode, nullptr);
    EXPECT_EQ(dynamicNode->GetTag(), V2::DYNAMIC_COMPONENT_ETS_TAG);
    auto dynamicPattern = dynamicNode->GetPattern<DynamicPattern>();
    EXPECT_NE(dynamicPattern, nullptr);
    auto pipeline = MockPipelineContext::GetCurrent();
    EXPECT_NE(pipeline, nullptr);

    /**
     * @tc.steps: step2. call UnRegisterAccessibilitySAObserverCallback.
     */
    auto host = dynamicPattern->GetHost();
    EXPECT_NE(host, nullptr);
    int32_t instanceId = 1;
    auto frontend = pipeline->GetFrontend();
    EXPECT_EQ(frontend, nullptr);
    frontend = AceType::MakeRefPtr<MockFrontend>();
    pipeline->weakFrontend_ = frontend;
    dynamicPattern->UnRegisterAccessibilitySAObserverCallback(instanceId);

    pipeline->weakFrontend_ = nullptr;
    dynamicPattern->host_ = nullptr;
    dynamicPattern->UnRegisterAccessibilitySAObserverCallback(instanceId);
}

/**
 * @tc.name: DynamicPatternTest007
 * @tc.desc: Test DynamicPattern RegisterPipelineEvent
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgTwo, DynamicPatternTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get DynamicPattern
     */
    auto dynamicNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto dynamicNode = FrameNode::GetOrCreateFrameNode(
        DYNAMIC_COMPONENT_ETS_TAG, dynamicNodeId, []() {
            return AceType::MakeRefPtr<DynamicPattern>();
        });
    EXPECT_NE(dynamicNode, nullptr);
    EXPECT_EQ(dynamicNode->GetTag(), V2::DYNAMIC_COMPONENT_ETS_TAG);
    auto dynamicPattern = dynamicNode->GetPattern<DynamicPattern>();
    EXPECT_NE(dynamicPattern, nullptr);

    /**
     * @tc.steps: step2. call RegisterPipelineEvent.
     */
    EXPECT_NE(dynamicPattern->frameNode_.Upgrade(), nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::DYNAMIC_COMPONENT_TAG, 0, dynamicPattern);
    dynamicPattern->host_ = frameNode;
    int32_t instanceId = 1;
    auto context = PipelineContext::GetContextByContainerId(instanceId);
    CHECK_NULL_VOID(context);
    auto uiExtManager = context->GetUIExtensionManager();
    CHECK_NULL_VOID(uiExtManager);
    context->uiExtensionManager_ = nullptr;
    dynamicPattern->RegisterPipelineEvent(instanceId);

    EXPECT_NE(dynamicPattern->host_.Upgrade(), nullptr);
    dynamicPattern->RegisterSingleHandTransformChangedCallback(instanceId);
}

/**
 * @tc.name: DynamicPatternTest008
 * @tc.desc: Test DynamicPattern ResetAccessibilityChildTreeCallback
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgTwo, DynamicPatternTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get DynamicPattern
     */
    auto dynamicNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto dynamicNode = FrameNode::GetOrCreateFrameNode(
        DYNAMIC_COMPONENT_ETS_TAG, dynamicNodeId, []() {
            return AceType::MakeRefPtr<DynamicPattern>();
        });
    EXPECT_NE(dynamicNode, nullptr);
    EXPECT_EQ(dynamicNode->GetTag(), V2::DYNAMIC_COMPONENT_ETS_TAG);
    auto dynamicPattern = dynamicNode->GetPattern<DynamicPattern>();
    EXPECT_NE(dynamicPattern, nullptr);
    dynamicPattern->accessibilityChildTreeCallback_ =
        std::make_shared<PlatformAccessibilityChildTreeCallback>(dynamicPattern, 1);
    dynamicPattern->instanceId_ = 1;
    auto host = dynamicPattern->GetHost();
    EXPECT_NE(host, nullptr);
    EXPECT_NE(dynamicPattern->accessibilityChildTreeCallback_, nullptr);
    auto pipeline = NG::PipelineContext::GetCurrentContext();
    EXPECT_NE(pipeline, nullptr);
    auto frontend = pipeline->GetFrontend();
    EXPECT_EQ(frontend, nullptr);
    frontend = AceType::MakeRefPtr<MockFrontend>();
    /**
     * @tc.steps: step2. call ResetAccessibilityChildTreeCallback.
     */
    dynamicPattern->ResetAccessibilityChildTreeCallback();
    EXPECT_NE(dynamicPattern->accessibilityChildTreeCallback_, nullptr);

    dynamicPattern->accessibilityChildTreeCallback_ =
        std::make_shared<PlatformAccessibilityChildTreeCallback>(dynamicPattern, 1);

    dynamicPattern->host_ = nullptr;
    dynamicPattern->ResetAccessibilityChildTreeCallback();
    EXPECT_NE(dynamicPattern->accessibilityChildTreeCallback_, nullptr);
}

/**
 * @tc.name: DynamicPatternTest009
 * @tc.desc: Test DynamicPattern AddToPageEventController
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgTwo, DynamicPatternTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get DynamicPattern
     */
    auto dynamicNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto dynamicNode = FrameNode::GetOrCreateFrameNode(
        DYNAMIC_COMPONENT_ETS_TAG, dynamicNodeId, []() {
            return AceType::MakeRefPtr<DynamicPattern>();
        });
    EXPECT_NE(dynamicNode, nullptr);
    EXPECT_EQ(dynamicNode->GetTag(), V2::DYNAMIC_COMPONENT_ETS_TAG);
    auto dynamicPattern = dynamicNode->GetPattern<DynamicPattern>();
    EXPECT_NE(dynamicPattern, nullptr);
    auto host = dynamicPattern->GetHost();
    EXPECT_NE(host, nullptr);
    dynamicPattern->instanceId_ = 100000;

    /**
     * @tc.steps: step2. call ResetAccessibilityChildTreeCallback.
     */
    auto pipeline = host->GetContext();
    EXPECT_NE(pipeline, nullptr);
    auto frontend = pipeline->GetFrontend();
    EXPECT_EQ(frontend, nullptr);
    frontend = AceType::MakeRefPtr<MockFrontend>();
    pipeline->weakFrontend_ = frontend;
    dynamicPattern->AddToPageEventController();

    dynamicPattern->host_ = nullptr;
    dynamicPattern->AddToPageEventController();
}

void DynamicPatternTestNgTwo::JsonExpect(std::unique_ptr<JsonValue>& json, RefPtr<DynamicPattern> dynamicPattern)
{
    EXPECT_NE(dynamicPattern->dynamicComponentRenderer_, nullptr);
    dynamicPattern->DumpInfo(json);

    const auto& dynamicId = json->GetValue("dynamicId");
    bool hasDynamicId = !(dynamicId->IsNull());
    EXPECT_FALSE(hasDynamicId);

    const auto& resourcePath = json->GetValue("resourcePath");
    bool hasResourcePath = !(resourcePath->IsNull());
    EXPECT_FALSE(hasResourcePath);

    const auto& entryPoint = json->GetValue("entryPoint");
    bool hasEntryPoint = !(entryPoint->IsNull());
    EXPECT_FALSE(hasEntryPoint);

    const auto& createLimitedWorkerTime = json->GetValue("createLimitedWorkerTime");
    bool hasCreateLimitedWorkerTime = !(createLimitedWorkerTime->IsNull());
    EXPECT_FALSE(hasCreateLimitedWorkerTime);

    const auto& createUiContenTime = json->GetValue("createUiContenTime");
    bool hasCreateUiContenTime = !(createUiContenTime->IsNull());
    EXPECT_FALSE(hasCreateUiContenTime);

    const auto& limitedWorkerInitTime = json->GetValue("limitedWorkerInitTime");
    bool hasLimitedWorkerInitTime = !(limitedWorkerInitTime->IsNull());
    EXPECT_FALSE(hasLimitedWorkerInitTime);

    const auto& loadAbcTime = json->GetValue("loadAbcTime");
    bool hasLoadAbcTime = !(loadAbcTime->IsNull());
    EXPECT_FALSE(hasLoadAbcTime);

    const auto& isReportFrameEvent = json->GetValue("isReportFrameEvent");
    bool hasIsReportFrameEvent = !(isReportFrameEvent->IsNull());
    EXPECT_FALSE(hasIsReportFrameEvent);
}

/**
 * @tc.name: DynamicPatternTest010
 * @tc.desc: Test DynamicPattern DumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgTwo, DynamicPatternTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get DynamicPattern
     */
    auto dynamicNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto dynamicNode = FrameNode::GetOrCreateFrameNode(
        DYNAMIC_COMPONENT_ETS_TAG, dynamicNodeId, []() {
            return AceType::MakeRefPtr<DynamicPattern>();
        });
    EXPECT_NE(dynamicNode, nullptr);
    EXPECT_EQ(dynamicNode->GetTag(), V2::DYNAMIC_COMPONENT_ETS_TAG);
    auto dynamicPattern = dynamicNode->GetPattern<DynamicPattern>();
    EXPECT_NE(dynamicPattern, nullptr);

    std::unique_ptr<JsonValue> json = std::make_unique<JsonValue>();
    dynamicPattern->platformId_ = 123;
    dynamicPattern->curDynamicInfo_.resourcePath = "test/path";
    dynamicPattern->curDynamicInfo_.entryPoint = "test/entry";
    dynamicPattern->dynamicDumpInfo_.createLimitedWorkerTime = 100;
    dynamicPattern->hostConfig_.isReportFrameEvent = true;
    IsolatedInfo curIsolatedInfo;
    void* runtime = nullptr;
    dynamicPattern->dynamicComponentRenderer_ = DynamicComponentRenderer::Create(
        dynamicNode, runtime, curIsolatedInfo);
    RendererDumpInfo rendererDumpInfo;
    rendererDumpInfo.createUiContenTime = 200;
    rendererDumpInfo.limitedWorkerInitTime = 300;
    rendererDumpInfo.loadAbcTime = 400;

    /**
     * @tc.steps: step2. call DumpInfo.
     */
    JsonExpect(json, dynamicPattern);
}

/**
 * @tc.name: DynamicPatternTest011
 * @tc.desc: Test DynamicPattern DumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgTwo, DynamicPatternTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get DynamicPattern
     */
    auto dynamicNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto dynamicNode = FrameNode::GetOrCreateFrameNode(
        DYNAMIC_COMPONENT_ETS_TAG, dynamicNodeId, []() {
            return AceType::MakeRefPtr<DynamicPattern>();
        });
    EXPECT_NE(dynamicNode, nullptr);
    EXPECT_EQ(dynamicNode->GetTag(), V2::DYNAMIC_COMPONENT_ETS_TAG);
    auto dynamicPattern = dynamicNode->GetPattern<DynamicPattern>();
    EXPECT_NE(dynamicPattern, nullptr);

    dynamicPattern->platformId_ = 123;
    dynamicPattern->curDynamicInfo_.entryPoint = "test/entry";
    dynamicPattern->dynamicDumpInfo_.createLimitedWorkerTime = 100;
    dynamicPattern->hostConfig_.isReportFrameEvent = true;
    IsolatedInfo curIsolatedInfo;
    void* runtime = nullptr;
    dynamicPattern->dynamicComponentRenderer_ = DynamicComponentRenderer::Create(
        dynamicNode, runtime, curIsolatedInfo);
    RendererDumpInfo rendererDumpInfo;
    rendererDumpInfo.createUiContenTime = 200;
    rendererDumpInfo.limitedWorkerInitTime = 300;
    rendererDumpInfo.loadAbcTime = 400;

    /**
     * @tc.steps: step2. call DumpInfo.
     */
    EXPECT_NE(dynamicPattern->dynamicComponentRenderer_, nullptr);
    dynamicPattern->DumpInfo();

    ASSERT_EQ(DumpLog::GetInstance().description_.size(), 7);
    EXPECT_EQ(DumpLog::GetInstance().description_[0], "dynamicId: 123\n");
    EXPECT_EQ(DumpLog::GetInstance().description_[1], "entryPoint: test/entry\n");
    EXPECT_EQ(DumpLog::GetInstance().description_[2], "createLimitedWorkerTime: 100\n");
    EXPECT_EQ(DumpLog::GetInstance().description_[3], "createUiContenTime: 0\n");
    EXPECT_EQ(DumpLog::GetInstance().description_[4], "limitedWorkerInitTime: 0\n");
    EXPECT_EQ(DumpLog::GetInstance().description_[5], "loadAbcTime: 0\n");
    EXPECT_EQ(DumpLog::GetInstance().description_[6], "isReportFrameEvent: true\n");
}

/**
 * @tc.name: DynamicPatternTest012
 * @tc.desc: Test DynamicPattern OnAttachContext
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgTwo, DynamicPatternTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create DynamicPattern and set initial instanceId.
     */
    auto dynamicNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto dynamicNode = FrameNode::GetOrCreateFrameNode(
        DYNAMIC_COMPONENT_ETS_TAG, dynamicNodeId, []() {
            return AceType::MakeRefPtr<DynamicPattern>();
        });
    EXPECT_NE(dynamicNode, nullptr);
    EXPECT_EQ(dynamicNode->GetTag(), V2::DYNAMIC_COMPONENT_ETS_TAG);
    auto dynamicPattern = dynamicNode->GetPattern<DynamicPattern>();
    EXPECT_NE(dynamicPattern, nullptr);

    int oldInstanceId = 123;
    int newInstanceId = 124;
    dynamicPattern->instanceId_ = oldInstanceId;
    auto pipeline = MockPipelineContext::GetCurrent();
    EXPECT_NE(pipeline, nullptr);
    pipeline->SetInstanceId(124);

    /**
     * @tc.steps: step2. Call OnAttachContext with nullptr context.
     */
    pipeline->uiExtensionManager_ = nullptr;
    auto rawPipeline = reinterpret_cast<PipelineContext*>(Referenced::RawPtr(pipeline));
    dynamicPattern->OnAttachContext(nullptr);
    EXPECT_EQ(dynamicPattern->instanceId_, oldInstanceId);

    dynamicPattern->OnAttachContext(rawPipeline);
    EXPECT_NE(dynamicPattern->instanceId_, oldInstanceId);
    EXPECT_EQ(dynamicPattern->instanceId_, newInstanceId);
}

/**
 * @tc.name: DynamicPatternTest013
 * @tc.desc: Test DynamicPattern SetIsReportFrameEvent
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgTwo, DynamicPatternTest013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create DynamicPattern and set initial instanceId.
     */
    auto dynamicNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto dynamicNode = FrameNode::GetOrCreateFrameNode(
        DYNAMIC_COMPONENT_ETS_TAG, dynamicNodeId, []() {
            return AceType::MakeRefPtr<DynamicPattern>();
        });
    EXPECT_NE(dynamicNode, nullptr);
    EXPECT_EQ(dynamicNode->GetTag(), V2::DYNAMIC_COMPONENT_ETS_TAG);
    auto dynamicPattern = dynamicNode->GetPattern<DynamicPattern>();
    EXPECT_NE(dynamicPattern, nullptr);
    EXPECT_FALSE(dynamicPattern->hostConfig_.isReportFrameEvent);

    /**
     * @tc.steps: step2. Call SetIsReportFrameEvent
     */
    dynamicPattern->SetIsReportFrameEvent(true);
    EXPECT_TRUE(dynamicPattern->hostConfig_.isReportFrameEvent);
}

/**
 * @tc.name: DynamicPatternTest014
 * @tc.desc: Test DynamicPattern GetDynamicComponentRenderer and allowOccupied state
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgTwo, DynamicPatternTest014, TestSize.Level1)
{
    auto dynamicNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto dynamicNode = FrameNode::GetOrCreateFrameNode(
        DYNAMIC_COMPONENT_ETS_TAG, dynamicNodeId, []() {
            return AceType::MakeRefPtr<DynamicPattern>();
        });
    ASSERT_NE(dynamicNode, nullptr);
    auto dynamicPattern = dynamicNode->GetPattern<DynamicPattern>();
    ASSERT_NE(dynamicPattern, nullptr);

    EXPECT_FALSE(dynamicPattern->GetAllowOccupied());
    EXPECT_EQ(dynamicPattern->GetDynamicComponentRenderer(), nullptr);

    dynamicPattern->SetAllowOccupied(true);
    EXPECT_TRUE(dynamicPattern->GetAllowOccupied());

    IsolatedInfo isolatedInfo;
    void* runtime = nullptr;
    dynamicPattern->dynamicComponentRenderer_ = DynamicComponentRenderer::Create(dynamicNode, runtime, isolatedInfo);
    ASSERT_NE(dynamicPattern->GetDynamicComponentRenderer(), nullptr);

    auto rendererImpl = AceType::DynamicCast<DynamicComponentRendererImpl>(dynamicPattern->GetDynamicComponentRenderer());
    ASSERT_NE(rendererImpl, nullptr);
    EXPECT_EQ(rendererImpl->GetUIContent(), nullptr);
}

/**
 * @tc.name: DynamicPatternTest015
 * @tc.desc: Test UIExtensionModelNG CreateDynamicComponent sync allowOccupied config
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgTwo, DynamicPatternTest015, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    stack->ClearStack();

    UIExtensionConfig config;
    config.sessionType = SessionType::DYNAMIC_COMPONENT;
    config.backgroundTransparent = false;
    config.allowOccupied = true;

    UIExtensionModelNG modelNg;
    modelNg.Create(config);

    auto frameNode = stack->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::DYNAMIC_COMPONENT_ETS_TAG);

    auto dynamicPattern = frameNode->GetPattern<DynamicPattern>();
    ASSERT_NE(dynamicPattern, nullptr);
    EXPECT_FALSE(dynamicPattern->backgroundTransparent_);
    EXPECT_TRUE(dynamicPattern->GetAllowOccupied());

    stack->ClearStack();
}

/**
 * @tc.name: DynamicPatternTest016
 * @tc.desc: Test DynamicPattern OnAttachContext and OnDetachContext update aliveDynamics
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgTwo, DynamicPatternTest016, TestSize.Level1)
{
    auto dynamicNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto dynamicNode = FrameNode::GetOrCreateFrameNode(
        DYNAMIC_COMPONENT_ETS_TAG, dynamicNodeId, []() {
            return AceType::MakeRefPtr<DynamicPattern>();
        });
    ASSERT_NE(dynamicNode, nullptr);
    auto dynamicPattern = dynamicNode->GetPattern<DynamicPattern>();
    ASSERT_NE(dynamicPattern, nullptr);

    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    pipeline->SetInstanceId(TEST_INSTANCE_ID);
    auto manager = pipeline->GetDynamicComponentSafeManager();
    ASSERT_NE(manager, nullptr);
    manager->aliveDynamics_.clear();
    dynamicPattern->instanceId_ = TEST_INSTANCE_ID;

    auto rawPipeline = reinterpret_cast<PipelineContext*>(Referenced::RawPtr(pipeline));
    dynamicPattern->OnAttachContext(rawPipeline);

    auto host = dynamicPattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto iter = manager->aliveDynamics_.find(host->GetId());
    ASSERT_NE(iter, manager->aliveDynamics_.end());
    auto storedPattern = AceType::DynamicCast<DynamicPattern>(iter->second.Upgrade());
    EXPECT_EQ(storedPattern, dynamicPattern);

    dynamicPattern->OnDetachContext(rawPipeline);
    EXPECT_EQ(manager->aliveDynamics_.count(host->GetId()), 0UL);
}

/**
 * @tc.name: DynamicPatternTest017
 * @tc.desc: Test DynamicPattern OnAttachContext skips aliveDynamics update when host is null
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgTwo, DynamicPatternTest017, TestSize.Level1)
{
    auto dynamicNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto dynamicNode = FrameNode::GetOrCreateFrameNode(
        DYNAMIC_COMPONENT_ETS_TAG, dynamicNodeId, []() {
            return AceType::MakeRefPtr<DynamicPattern>();
        });
    ASSERT_NE(dynamicNode, nullptr);
    auto dynamicPattern = dynamicNode->GetPattern<DynamicPattern>();
    ASSERT_NE(dynamicPattern, nullptr);

    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    auto manager = pipeline->GetDynamicComponentSafeManager();
    ASSERT_NE(manager, nullptr);
    manager->aliveDynamics_.clear();
    dynamicPattern->instanceId_ = pipeline->GetInstanceId();
    dynamicPattern->host_ = nullptr;

    auto rawPipeline = reinterpret_cast<PipelineContext*>(Referenced::RawPtr(pipeline));
    dynamicPattern->OnAttachContext(rawPipeline);
    EXPECT_TRUE(manager->aliveDynamics_.empty());
}

/**
 * @tc.name: DynamicPatternTest018
 * @tc.desc: Test PipelineContext UpdateAvoidArea and DynamicComponentSafeManager GetAvoidArea
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgTwo, DynamicPatternTest018, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    auto manager = pipeline->GetDynamicComponentSafeManager();
    ASSERT_NE(manager, nullptr);
    manager->avoidAreas_.clear();

    Rosen::AvoidArea avoidArea;
    avoidArea.topRect_ = { TEST_RECT_POS_X, TEST_RECT_POS_Y, TEST_RECT_WIDTH, TEST_RECT_HEIGHT };
    avoidArea.leftRect_ = { TEST_RECT_POS_Y, TEST_RECT_POS_X, TEST_RECT_HEIGHT, TEST_RECT_WIDTH };
    std::map<Rosen::AvoidAreaType, Rosen::AvoidArea> avoidAreas;
    avoidAreas.emplace(Rosen::AvoidAreaType::TYPE_SYSTEM, avoidArea);

    pipeline->UpdateAvoidArea(avoidAreas);
    auto result = manager->GetAvoidArea();
    ASSERT_EQ(result.size(), 1UL);
    auto iter = result.find(Rosen::AvoidAreaType::TYPE_SYSTEM);
    ASSERT_NE(iter, result.end());
    EXPECT_EQ(iter->second.topRect_.posX_, TEST_RECT_POS_X);
    EXPECT_EQ(iter->second.topRect_.posY_, TEST_RECT_POS_Y);
    EXPECT_EQ(iter->second.topRect_.width_, TEST_RECT_WIDTH);
    EXPECT_EQ(iter->second.topRect_.height_, TEST_RECT_HEIGHT);
    EXPECT_EQ(iter->second.leftRect_.posX_, TEST_RECT_POS_Y);
    EXPECT_EQ(iter->second.leftRect_.posY_, TEST_RECT_POS_X);
}

/**
 * @tc.name: DynamicPatternTest019
 * @tc.desc: Test DynamicComponentSafeManager occupied area info round trip
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgTwo, DynamicPatternTest019, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    auto manager = pipeline->GetDynamicComponentSafeManager();
    ASSERT_NE(manager, nullptr);

    manager->occupiedAreaChangeInfo_ = nullptr;
    manager->SetOccupiedAreaChangeInfo(nullptr);
    EXPECT_EQ(manager->occupiedAreaChangeInfo_, nullptr);

    sptr<Rosen::OccupiedAreaChangeInfo> info = new Rosen::OccupiedAreaChangeInfo();
    info->type_ = Rosen::OccupiedAreaType::TYPE_INPUT;
    info->safeHeight_ = TEST_SAFE_HEIGHT;
    info->textFieldPositionY_ = TEST_TEXT_FIELD_POSITION_Y;
    info->textFieldHeight_ = TEST_TEXT_FIELD_HEIGHT;
    info->rect_ = { TEST_RECT_POS_X, TEST_RECT_POS_Y, TEST_RECT_WIDTH, TEST_RECT_HEIGHT };

    manager->SetOccupiedAreaChangeInfo(info);
    auto copiedInfo = manager->GetOccupiedAreaChangeInfo();
    ASSERT_NE(copiedInfo, nullptr);
    EXPECT_EQ(copiedInfo->type_, Rosen::OccupiedAreaType::TYPE_INPUT);
    EXPECT_EQ(copiedInfo->safeHeight_, TEST_SAFE_HEIGHT);
    EXPECT_DOUBLE_EQ(copiedInfo->textFieldPositionY_, TEST_TEXT_FIELD_POSITION_Y);
    EXPECT_DOUBLE_EQ(copiedInfo->textFieldHeight_, TEST_TEXT_FIELD_HEIGHT);
    EXPECT_EQ(copiedInfo->rect_.posX_, TEST_RECT_POS_X);
    EXPECT_EQ(copiedInfo->rect_.posY_, TEST_RECT_POS_Y);
    EXPECT_EQ(copiedInfo->rect_.width_, TEST_RECT_WIDTH);
    EXPECT_EQ(copiedInfo->rect_.height_, TEST_RECT_HEIGHT);
}

/**
 * @tc.name: DynamicPatternTest020
 * @tc.desc: Test DynamicComponentSafeManager UpdateAllDCAvoidArea and UpdateDynamicKeyBoardAvoid early branch
 * @tc.type: FUNC
 */
HWTEST_F(DynamicPatternTestNgTwo, DynamicPatternTest020, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    auto manager = pipeline->GetDynamicComponentSafeManager();
    ASSERT_NE(manager, nullptr);
    manager->aliveDynamics_.clear();
    manager->avoidAreas_.clear();

    Rosen::AvoidArea avoidArea;
    avoidArea.bottomRect_ = { TEST_RECT_POS_X, TEST_RECT_POS_Y, TEST_RECT_WIDTH, TEST_RECT_HEIGHT };
    manager->UpdateAllDCAvoidArea(TEST_DYNAMIC_COMPONENT_ID, avoidArea, Rosen::AvoidAreaType::TYPE_SYSTEM);

    auto avoidAreas = manager->GetAvoidArea();
    auto iter = avoidAreas.find(Rosen::AvoidAreaType::TYPE_SYSTEM);
    ASSERT_NE(iter, avoidAreas.end());
    EXPECT_EQ(iter->second.bottomRect_.posX_, TEST_RECT_POS_X);
    EXPECT_EQ(iter->second.bottomRect_.height_, TEST_RECT_HEIGHT);

    sptr<Rosen::OccupiedAreaChangeInfo> info = new Rosen::OccupiedAreaChangeInfo();
    info->type_ = Rosen::OccupiedAreaType::TYPE_INPUT;
    info->rect_ = { TEST_RECT_POS_X, TEST_RECT_POS_Y, TEST_RECT_WIDTH, TEST_RECT_HEIGHT };
    bool result = manager->UpdateDynamicKeyBoardAvoid(
        pipeline, Rosen::WindowSizeChangeReason::OCCUPIED_AREA_CHANGE, info, nullptr, avoidAreas);
    EXPECT_FALSE(result);
}
} // namespace OHOS::Ace::NG
