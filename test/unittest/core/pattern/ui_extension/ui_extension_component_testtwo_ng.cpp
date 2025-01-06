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

#include "gtest/gtest.h"
#include "base/memory/ace_type.h"
#define private public
#define protected public
#include "core/components_ng/pattern/ui_extension/ui_extension_model.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_model_ng.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_pattern.h"
#include "core/components_ng/pattern/ui_extension/security_ui_extension_pattern.h"
#include "core/components_ng/pattern/ui_extension/session_wrapper.h"
#include "core/components_ng/pattern/ui_extension/session_wrapper_impl.h"
#include "core/components_ng/pattern/ui_extension/session_wrapper_factory.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_proxy.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_config.h"
#include "core/components_ng/pattern/ui_extension/modal_ui_extension_proxy_impl.h"
#include "core/components_ng/pattern/ui_extension/isolated_pattern.h"
#include "core/event/ace_events.h"
#include "core/event/mouse_event.h"
#include "core/event/touch_event.h"
#include "core/event/key_event.h"
#include "core/event/pointer_event.h"

#include "session/host/include/extension_session.h"
#include "session/host/include/session.h"
#include "ui/rs_surface_node.h"

#include "adapter/ohos/entrance/mmi_event_convertor.h"
#include "adapter/ohos/osal/want_wrap_ohos.h"
#include "base/error/error_code.h"
#include "base/geometry/offset.h"
#include "base/utils/utils.h"

#include "core/common/window.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/pattern/pattern.h"

#include "mock/mock_accessibility_child_tree_callback.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/common/mock_container.h"

#include "core/components_ng/render/adapter/rosen_window.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/render/mock_rosen_render_context.h"
#include "frameworks/core/components_ng/pattern/ui_extension/platform_event_proxy.h"
#include "test/unittest/core/pattern/ui_extension/mock/mock_window_scene_helper.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
    const std::string UI_EXTENSION_COMPONENT_ETS_TAG = "UIExtensionComponent";
} // namespace

class UIExtensionComponentTestTwoNg : public testing::Test {
public:
    void SetUp() override;
    void TearDown() override;
    static void SetUpTestSuite()
    {
        MockPipelineContext::SetUp();
        MockContainer::SetUp();
        MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
        MockContainer::Current()->pipelineContext_->taskExecutor_ = MockContainer::Current()->taskExecutor_;
    }
    static void TearDownTestSuite()
    {
        MockPipelineContext::TearDown();
        MockContainer::TearDown();
    }
};

void UIExtensionComponentTestTwoNg::SetUp() {
}

void UIExtensionComponentTestTwoNg::TearDown() {
}

/**
 * @tc.name: UIExtensionComponentTestTwoNg
 * @tc.desc: Test the method of pattern OnDisconnect and GetInstanceId
 * @tc.type: FUNC
 */
HWTEST_F(UIExtensionComponentTestTwoNg, OnAccessibilityEventTest001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a UIExtensionComponent Node
     */
    auto uiExtensionNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto uiExtensionNode = FrameNode::GetOrCreateFrameNode(
        UI_EXTENSION_COMPONENT_ETS_TAG, uiExtensionNodeId, []() { return AceType::MakeRefPtr<UIExtensionPattern>(); });
    ASSERT_NE(uiExtensionNode, nullptr);
    EXPECT_EQ(uiExtensionNode->GetTag(), V2::UI_EXTENSION_COMPONENT_ETS_TAG);
    auto pattern = uiExtensionNode->GetPattern<UIExtensionPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. test OnDisconnect
     */
    EXPECT_EQ(pattern->curPlaceholderType_, PlaceholderType::NONE);
    bool isAbnormal = true;
    pattern->OnDisconnect(isAbnormal);
    EXPECT_EQ(pattern->curPlaceholderType_, PlaceholderType::NONE);
    isAbnormal = false;
    pattern->OnDisconnect(isAbnormal);
    EXPECT_EQ(pattern->curPlaceholderType_, PlaceholderType::NONE);

    /**
     * @tc.steps: step3. test GetInstanceId
     */
    pattern->instanceId_ = 0;
    EXPECT_EQ(pattern->GetInstanceId(), pattern->instanceId_);
    pattern->instanceId_ = 1;
    EXPECT_EQ(pattern->GetInstanceId(), pattern->instanceId_);
#endif
}

/**
 * @tc.name: UIExtensionComponentTestTwoNg
 * @tc.desc: Test the method of pattern SetEventProxyFlag
 * @tc.type: FUNC
 */
HWTEST_F(UIExtensionComponentTestTwoNg, SetEventProxyFlagTest001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a UIExtensionComponent Node
     */
    auto uiExtensionNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto uiExtensionNode = FrameNode::GetOrCreateFrameNode(
        UI_EXTENSION_COMPONENT_ETS_TAG, uiExtensionNodeId, []() { return AceType::MakeRefPtr<UIExtensionPattern>(); });
    ASSERT_NE(uiExtensionNode, nullptr);
    EXPECT_EQ(uiExtensionNode->GetTag(), V2::UI_EXTENSION_COMPONENT_ETS_TAG);
    auto pattern = uiExtensionNode->GetPattern<UIExtensionPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. test SetEventProxyFlag
     */
    // False - False
    int32_t flag = 0X00000000;
    EXPECT_EQ(flag, EventProxyFlag::EVENT_NONE);
    pattern->platformEventProxy_ = nullptr;
    ASSERT_EQ(pattern->platformEventProxy_, nullptr);
    pattern->SetEventProxyFlag(flag);

    // False - True
    pattern->platformEventProxy_ = AceType::MakeRefPtr<PlatformEventProxy>();
    ASSERT_NE(pattern->platformEventProxy_, nullptr);
    pattern->SetEventProxyFlag(flag);

    // True - True
    flag = 0X00000100;
    ASSERT_NE(flag, EventProxyFlag::EVENT_NONE);
    pattern->SetEventProxyFlag(flag);

    // True - False
    pattern->platformEventProxy_ = AceType::MakeRefPtr<PlatformEventProxy>();
    ASSERT_NE(pattern->platformEventProxy_, nullptr);
    pattern->SetEventProxyFlag(flag);
#endif
}

/**
 * @tc.name: UIExtensionComponentTestTwoNg
 * @tc.desc: Test the method of pattern HandleDragEvent
 * @tc.type: FUNC
 */
HWTEST_F(UIExtensionComponentTestTwoNg, HandleDragEventTest001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a UIExtensionComponent Node
     */
    auto uiExtensionNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto uiExtensionNode = FrameNode::GetOrCreateFrameNode(
        UI_EXTENSION_COMPONENT_ETS_TAG, uiExtensionNodeId, []() { return AceType::MakeRefPtr<UIExtensionPattern>(); });
    ASSERT_NE(uiExtensionNode, nullptr);
    EXPECT_EQ(uiExtensionNode->GetTag(), V2::UI_EXTENSION_COMPONENT_ETS_TAG);
    auto pattern = uiExtensionNode->GetPattern<UIExtensionPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. test HandleDragEvent
     */
    DragPointerEvent info(100, 100, 100, 100);;
    ASSERT_EQ(pattern->platformEventProxy_, nullptr);
    pattern->HandleDragEvent(info);

    std::shared_ptr<MMI::PointerEvent> pointerEvent = std::make_shared<MMI::PointerEvent>(1);
    pointerEvent->SetPointerAction(MMI::PointerEvent::POINTER_ACTION_UP);
    info.rawPointerEvent = pointerEvent;
    ASSERT_NE(info.rawPointerEvent, nullptr);
    pattern->HandleDragEvent(info);
#endif
}

/**
 * @tc.name: UIExtensionComponentTestTwoNg
 * @tc.desc: Test the method of pattern OnMountToParentDone and AfterMountToParent
 * @tc.type: FUNC
 */
HWTEST_F(UIExtensionComponentTestTwoNg, OnMountToParentDoneTest001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a UIExtensionComponent Node
     */
    auto uiExtensionNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto uiExtensionNode = FrameNode::GetOrCreateFrameNode(
        UI_EXTENSION_COMPONENT_ETS_TAG, uiExtensionNodeId, []() { return AceType::MakeRefPtr<UIExtensionPattern>(); });
    ASSERT_NE(uiExtensionNode, nullptr);
    EXPECT_EQ(uiExtensionNode->GetTag(), V2::UI_EXTENSION_COMPONENT_ETS_TAG);
    auto pattern = uiExtensionNode->GetPattern<UIExtensionPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. test OnMountToParentDone
     */
    pattern->needReNotifyForeground_= false;
    pattern->OnMountToParentDone();

    pattern->needReNotifyForeground_= true;
    pattern->frameNode_ = nullptr;
    ASSERT_EQ(pattern->frameNode_.Upgrade(), nullptr);
    ASSERT_EQ(pattern->GetHost(), nullptr);
    ASSERT_EQ(WindowSceneHelper::FindWindowScene(pattern->GetHost()), nullptr);
    pattern->OnMountToParentDone();

    pattern->frameNode_ = uiExtensionNode;
    ASSERT_NE(pattern->frameNode_.Upgrade(), nullptr);
    ASSERT_NE(pattern->GetHost(), nullptr);
    ASSERT_NE(WindowSceneHelper::FindWindowScene(pattern->GetHost()), nullptr);
    pattern->OnMountToParentDone();

    /**
     * @tc.steps: step2. test AfterMountToParent
     */
    pattern->needReNotifyForeground_= false;
    pattern->AfterMountToParent();

    pattern->needReNotifyForeground_= true;
    pattern->frameNode_ = nullptr;
    ASSERT_EQ(pattern->frameNode_.Upgrade(), nullptr);
    ASSERT_EQ(pattern->GetHost(), nullptr);
    ASSERT_EQ(WindowSceneHelper::FindWindowScene(pattern->GetHost()), nullptr);
    pattern->AfterMountToParent();

    pattern->frameNode_ = uiExtensionNode;
    ASSERT_NE(pattern->frameNode_.Upgrade(), nullptr);
    ASSERT_NE(pattern->GetHost(), nullptr);
    ASSERT_NE(WindowSceneHelper::FindWindowScene(pattern->GetHost()), nullptr);
    pattern->AfterMountToParent();
#endif
}

/**
 * @tc.name: UIExtensionComponentTestTwoNg
 * @tc.desc: Test the method of pattern RegisterVisibleAreaChange
 * @tc.type: FUNC
 */
HWTEST_F(UIExtensionComponentTestTwoNg, RegisterVisibleAreaChangeTest001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a UIExtensionComponent Node
     */
    auto uiExtensionNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto uiExtensionNode = FrameNode::GetOrCreateFrameNode(
        UI_EXTENSION_COMPONENT_ETS_TAG, uiExtensionNodeId, []() { return AceType::MakeRefPtr<UIExtensionPattern>(); });
    ASSERT_NE(uiExtensionNode, nullptr);
    EXPECT_EQ(uiExtensionNode->GetTag(), V2::UI_EXTENSION_COMPONENT_ETS_TAG);
    auto pattern = uiExtensionNode->GetPattern<UIExtensionPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. test RegisterVisibleAreaChange
     */
    pattern->frameNode_ = nullptr;
    ASSERT_EQ(pattern->frameNode_.Upgrade(), nullptr);
    ASSERT_EQ(pattern->GetHost(), nullptr);
    pattern->RegisterVisibleAreaChange();

    pattern->frameNode_ = uiExtensionNode;
    ASSERT_NE(pattern->frameNode_.Upgrade(), nullptr);
    ASSERT_NE(pattern->GetHost(), nullptr);
    pattern->RegisterVisibleAreaChange();
#endif
}

/**
 * @tc.name: UIExtensionComponentTestTwoNg
 * @tc.desc: Test the method of pattern RegisterEventProxyFlagCallback
 * @tc.type: FUNC
 */
HWTEST_F(UIExtensionComponentTestTwoNg, RegisterEventProxyFlagCallbackTest001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a UIExtensionComponent Node
     */
    auto uiExtensionNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto uiExtensionNode = FrameNode::GetOrCreateFrameNode(
        UI_EXTENSION_COMPONENT_ETS_TAG, uiExtensionNodeId, []() { return AceType::MakeRefPtr<UIExtensionPattern>(); });
    ASSERT_NE(uiExtensionNode, nullptr);
    EXPECT_EQ(uiExtensionNode->GetTag(), V2::UI_EXTENSION_COMPONENT_ETS_TAG);
    auto pattern = uiExtensionNode->GetPattern<UIExtensionPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. test RegisterEventProxyFlagCallback
     */
    EXPECT_EQ(pattern->businessDataUECConsumeCallbacks_.size(), 0);
    pattern->RegisterEventProxyFlagCallback();
    EXPECT_EQ(pattern->businessDataUECConsumeCallbacks_.size(), 1);
#endif
}
} // namespace OHOS::Ace::NG
