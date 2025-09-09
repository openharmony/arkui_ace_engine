/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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
#include "core/components_ng/pattern/ui_extension/isolated_component/isolated_pattern.h"
#include "core/components_ng/pattern/ui_extension/security_ui_extension_component/security_ui_extension_pattern.h"
#include "core/components_ng/pattern/ui_extension/session_wrapper.h"
#include "core/components_ng/pattern/ui_extension/session_wrapper_factory.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_component/modal_ui_extension_proxy_impl.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_component/session_wrapper_impl.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_component/ui_extension_touch_delegate.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_component/ui_extension_node.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_component/ui_extension_pattern.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_component/ui_extension_proxy.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_config.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_model.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_model_ng.h"
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

#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/common/mock_container.h"

#include "core/components_ng/render/adapter/rosen_window.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/render/mock_render_context.h"
#include "test/mock/core/render/mock_rosen_render_context.h"
#include "frameworks/core/components_ng/pattern/ui_extension/platform_event_proxy.h"
#include "test/unittest/core/pattern/ui_extension/mock/mock_window_scene_helper.h"
#include "../mock/mock_accessibility_child_tree_callback.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
    const std::string UI_EXTENSION_COMPONENT_ETS_TAG = "UIExtensionComponent";
    const int32_t IGNORE_POSITION_TRANSITION_SWITCH = -990;
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

void UIExtensionComponentTestTwoNg::SetUp() {}

void UIExtensionComponentTestTwoNg::TearDown() {}

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
        UI_EXTENSION_COMPONENT_ETS_TAG, uiExtensionNodeId, []() {
            return AceType::MakeRefPtr<UIExtensionPattern>();
        });
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
        UI_EXTENSION_COMPONENT_ETS_TAG, uiExtensionNodeId, []() {
            return AceType::MakeRefPtr<UIExtensionPattern>();
        });
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
        UI_EXTENSION_COMPONENT_ETS_TAG, uiExtensionNodeId, []() {
            return AceType::MakeRefPtr<UIExtensionPattern>();
        });
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
        UI_EXTENSION_COMPONENT_ETS_TAG, uiExtensionNodeId, []() {
            return AceType::MakeRefPtr<UIExtensionPattern>();
        });
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
        UI_EXTENSION_COMPONENT_ETS_TAG, uiExtensionNodeId, []() {
            return AceType::MakeRefPtr<UIExtensionPattern>();
        });
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
        UI_EXTENSION_COMPONENT_ETS_TAG, uiExtensionNodeId, []() {
            return AceType::MakeRefPtr<UIExtensionPattern>();
        });
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

/**
 * @tc.name: UIExtensionComponentTestTwoNg
 * @tc.desc: Test the method of pattern RegisterEventProxyFlagCallback
 * @tc.type: FUNC
 */
HWTEST_F(UIExtensionComponentTestTwoNg, RegisterEventProxyFlagCallbackTest002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a UIExtensionComponent Node
     */
    auto uiExtensionNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto uiExtensionNode = FrameNode::GetOrCreateFrameNode(
        UI_EXTENSION_COMPONENT_ETS_TAG, uiExtensionNodeId, []() {
            return AceType::MakeRefPtr<UIExtensionPattern>();
        });
    ASSERT_NE(uiExtensionNode, nullptr);
    EXPECT_EQ(uiExtensionNode->GetTag(), V2::UI_EXTENSION_COMPONENT_ETS_TAG);
    auto pattern = uiExtensionNode->GetPattern<UIExtensionPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. test RegisterEventProxyFlagCallback
     */
    pattern->RegisterEventProxyFlagCallback();
    AAFwk::Want want;
    auto ret = pattern->businessDataUECConsumeCallbacks_.at(UIContentBusinessCode::EVENT_PROXY)(want);
    EXPECT_EQ(ret, -1);

    std::string type = "OccupyEvents";
    want.SetParam("type", type);
    ret = pattern->businessDataUECConsumeCallbacks_.at(UIContentBusinessCode::EVENT_PROXY)(want);
    EXPECT_EQ(ret, 0);
#endif
}

/**
 * @tc.name: UIExtensionComponentTestTwoNg
 * @tc.desc: Test the method of pattern RegisterReceivePageModeRequestCallback
 * @tc.type: FUNC
 */
HWTEST_F(UIExtensionComponentTestTwoNg, RegisterReceivePageModeRequestCallbackTest001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a UIExtensionComponent Node
     */
    auto uiExtensionNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto uiExtensionNode = FrameNode::GetOrCreateFrameNode(
        UI_EXTENSION_COMPONENT_ETS_TAG, uiExtensionNodeId, []() {
            return AceType::MakeRefPtr<UIExtensionPattern>();
        });
    ASSERT_NE(uiExtensionNode, nullptr);
    EXPECT_EQ(uiExtensionNode->GetTag(), V2::UI_EXTENSION_COMPONENT_ETS_TAG);
    auto pattern = uiExtensionNode->GetPattern<UIExtensionPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. test RegisterReceivePageModeRequestCallback
     */
    EXPECT_EQ(pattern->businessDataUECConsumeCallbacks_.size(), 0);
    pattern->RegisterReceivePageModeRequestCallback();
    EXPECT_EQ(pattern->businessDataUECConsumeCallbacks_.size(), 1);
#endif
}

/**
 * @tc.name: UIExtensionComponentTestTwoNg
 * @tc.desc: Test the method of pattern RegisterReceivePageModeRequestCallback
 * @tc.type: FUNC
 */
HWTEST_F(UIExtensionComponentTestTwoNg, RegisterReceivePageModeRequestCallbackTest002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a UIExtensionComponent Node
     */
    auto uiExtensionNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto uiExtensionNode = FrameNode::GetOrCreateFrameNode(
        UI_EXTENSION_COMPONENT_ETS_TAG, uiExtensionNodeId, []() {
            return AceType::MakeRefPtr<UIExtensionPattern>();
        });
    ASSERT_NE(uiExtensionNode, nullptr);
    EXPECT_EQ(uiExtensionNode->GetTag(), V2::UI_EXTENSION_COMPONENT_ETS_TAG);
    auto pattern = uiExtensionNode->GetPattern<UIExtensionPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. test RegisterReceivePageModeRequestCallback
     */
    pattern->RegisterReceivePageModeRequestCallback();
    AAFwk::Want want;
    auto ret = pattern->businessDataUECConsumeCallbacks_.at(UIContentBusinessCode::SEND_PAGE_MODE_REQUEST)(want);
    EXPECT_EQ(ret, -1);

    std::string value = "testuec";
    AAFwk::Want want2;
    want2.SetParam("requestPageMode", value);
    ret = pattern->businessDataUECConsumeCallbacks_.at(UIContentBusinessCode::SEND_PAGE_MODE_REQUEST)(want);
    EXPECT_EQ(ret, -1);

    want.SetParam("requestPageMode", value);
    ret = pattern->businessDataUECConsumeCallbacks_.at(UIContentBusinessCode::SEND_PAGE_MODE_REQUEST)(want);
    EXPECT_EQ(ret, 0);
#endif
}

/**
 * @tc.name: UIExtensionComponentTestTwoNg
 * @tc.desc: Test the method of pattern SendBusinessDataSyncReply
 * @tc.type: FUNC
 */
HWTEST_F(UIExtensionComponentTestTwoNg, SendBusinessDataSyncReplyTest001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a UIExtensionComponent Node
     */
    auto uiExtensionNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto uiExtensionNode = FrameNode::GetOrCreateFrameNode(
        UI_EXTENSION_COMPONENT_ETS_TAG, uiExtensionNodeId, []() {
            return AceType::MakeRefPtr<UIExtensionPattern>();
        });
    ASSERT_NE(uiExtensionNode, nullptr);
    EXPECT_EQ(uiExtensionNode->GetTag(), V2::UI_EXTENSION_COMPONENT_ETS_TAG);
    auto pattern = uiExtensionNode->GetPattern<UIExtensionPattern>();
    ASSERT_NE(pattern, nullptr);
    ASSERT_NE(pattern->sessionWrapper_, nullptr);

    /**
     * @tc.steps: step2. test SendBusinessDataSyncReply
     */
    UIContentBusinessCode code = UIContentBusinessCode::SEND_PAGE_MODE_REQUEST;
    AAFwk::Want want;
    AAFwk::Want reply;
    auto ret = pattern->SendBusinessDataSyncReply(code, want, reply);
    ASSERT_EQ(ret, false);
    
    pattern->sessionWrapper_ = nullptr;
    ret = pattern->SendBusinessDataSyncReply(code, want, reply);
    ASSERT_EQ(ret, false);
#endif
}

/**
 * @tc.name: UIExtensionComponentTestTwoNg
 * @tc.desc: Test the method of pattern SendBusinessData
 * @tc.type: FUNC
 */
HWTEST_F(UIExtensionComponentTestTwoNg, SendBusinessDataTest001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a UIExtensionComponent Node
     */
    auto uiExtensionNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto uiExtensionNode = FrameNode::GetOrCreateFrameNode(
        UI_EXTENSION_COMPONENT_ETS_TAG, uiExtensionNodeId, []() {
            return AceType::MakeRefPtr<UIExtensionPattern>();
        });
    ASSERT_NE(uiExtensionNode, nullptr);
    EXPECT_EQ(uiExtensionNode->GetTag(), V2::UI_EXTENSION_COMPONENT_ETS_TAG);
    auto pattern = uiExtensionNode->GetPattern<UIExtensionPattern>();
    ASSERT_NE(pattern, nullptr);
    ASSERT_NE(pattern->sessionWrapper_, nullptr);

    /**
     * @tc.steps: step2. test SendBusinessData
     */
    UIContentBusinessCode code = UIContentBusinessCode::SEND_PAGE_MODE_REQUEST;
    AAFwk::Want want;
    BusinessDataSendType type = BusinessDataSendType::ASYNC;
    auto ret = pattern->SendBusinessData(code, want, type);
    ASSERT_EQ(ret, false);
    
    pattern->sessionWrapper_ = nullptr;
    ret = pattern->SendBusinessData(code, want, type);
    ASSERT_EQ(ret, false);
#endif
}

/**
 * @tc.name: UIExtensionComponentTestTwoNg
 * @tc.desc: Test the method of pattern OnUIExtBusinessReceiveReply
 * @tc.type: FUNC
 */
HWTEST_F(UIExtensionComponentTestTwoNg, OnUIExtBusinessReceiveReplyTest001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a UIExtensionComponent Node
     */
    auto uiExtensionNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto uiExtensionNode = FrameNode::GetOrCreateFrameNode(
        UI_EXTENSION_COMPONENT_ETS_TAG, uiExtensionNodeId, []() {
            return AceType::MakeRefPtr<UIExtensionPattern>();
        });
    ASSERT_NE(uiExtensionNode, nullptr);
    EXPECT_EQ(uiExtensionNode->GetTag(), V2::UI_EXTENSION_COMPONENT_ETS_TAG);
    auto pattern = uiExtensionNode->GetPattern<UIExtensionPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. test OnUIExtBusinessReceiveReply
     */
    UIContentBusinessCode code = UIContentBusinessCode::SEND_PAGE_MODE_REQUEST;
    AAFwk::Want data;
    std::string value = "testuec";
    data.SetParam("requestPageMode", value);
    std::optional<AAFwk::Want> reply;
    AAFwk::Want want2;
    want2.SetParam("requestPageMode", value);
    reply = want2;
    pattern->OnUIExtBusinessReceiveReply(code, data, reply);
    EXPECT_EQ(reply->HasParameter("pageMode"), false);

    auto callback = [](const AAFwk::Want& data, std::optional<AAFwk::Want>& reply) -> int32_t {
        if (reply.has_value() && data.HasParameter("requestPageMode")) {
            reply->SetParam("pageMode", std::string("yes"));
            return 0;
        }
        return -1;
    };
    pattern->RegisterUIExtBusinessConsumeReplyCallback(code, callback);
    pattern->OnUIExtBusinessReceiveReply(code, data, reply);
    EXPECT_EQ(reply->HasParameter("pageMode"), true);
#endif
}

/**
 * @tc.name: UIExtensionComponentTestTwoNg
 * @tc.desc: Test the method of pattern OnUIExtBusinessReceive
 * @tc.type: FUNC
 */
HWTEST_F(UIExtensionComponentTestTwoNg, OnUIExtBusinessReceiveTest001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a UIExtensionComponent Node
     */
    auto uiExtensionNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto uiExtensionNode = FrameNode::GetOrCreateFrameNode(
        UI_EXTENSION_COMPONENT_ETS_TAG, uiExtensionNodeId, []() {
            return AceType::MakeRefPtr<UIExtensionPattern>();
        });
    ASSERT_NE(uiExtensionNode, nullptr);
    EXPECT_EQ(uiExtensionNode->GetTag(), V2::UI_EXTENSION_COMPONENT_ETS_TAG);
    auto pattern = uiExtensionNode->GetPattern<UIExtensionPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. test OnUIExtBusinessReceive
     */
    UIContentBusinessCode code = UIContentBusinessCode::SEND_PAGE_MODE_REQUEST;
    AAFwk::Want data;
    pattern->OnUIExtBusinessReceive(code, data);

    auto callback = [](const AAFwk::Want& data) -> int32_t {
        return -1;
    };
    pattern->RegisterUIExtBusinessConsumeCallback(code, callback);
    pattern->OnUIExtBusinessReceive(code, data);
#endif
}

/**
 * @tc.name: UIExtensionComponentTestTwoNg
 * @tc.desc: Test the method of pattern NotifyHostWindowMode and NotifyHostWindowMode
 * @tc.type: FUNC
 */
HWTEST_F(UIExtensionComponentTestTwoNg, NotifyHostWindowModeTest001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a UIExtensionComponent Node
     */
    auto uiExtensionNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto uiExtensionNode = FrameNode::GetOrCreateFrameNode(
        UI_EXTENSION_COMPONENT_ETS_TAG, uiExtensionNodeId, []() {
            return AceType::MakeRefPtr<UIExtensionPattern>();
        });
    ASSERT_NE(uiExtensionNode, nullptr);
    EXPECT_EQ(uiExtensionNode->GetTag(), V2::UI_EXTENSION_COMPONENT_ETS_TAG);
    auto pattern = uiExtensionNode->GetPattern<UIExtensionPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. test NotifyHostWindowMode and NotifyHostWindowMode
     */
    Rosen::WindowMode mode = Rosen::WindowMode::WINDOW_MODE_UNDEFINED;
    pattern->isWindowModeFollowHost_ = false;
    pattern->NotifyHostWindowMode(mode);

    pattern->isWindowModeFollowHost_ = true;
    pattern->NotifyHostWindowMode(mode);

    mode = Rosen::WindowMode::WINDOW_MODE_SPLIT_PRIMARY;
    pattern->NotifyHostWindowMode(mode);

    pattern->sessionWrapper_ = nullptr;
    pattern->NotifyHostWindowMode(mode);
#endif
}

/**
 * @tc.name: UIExtensionComponentTestTwoNg
 * @tc.desc: Test the method of pattern OnFrameNodeChanged
 * @tc.type: FUNC
 */
HWTEST_F(UIExtensionComponentTestTwoNg, OnFrameNodeChangedTest001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a UIExtensionComponent Node
     */
    auto uiExtensionNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto uiExtensionNode = FrameNode::GetOrCreateFrameNode(
        UI_EXTENSION_COMPONENT_ETS_TAG, uiExtensionNodeId, []() {
            return AceType::MakeRefPtr<UIExtensionPattern>();
        });
    ASSERT_NE(uiExtensionNode, nullptr);
    EXPECT_EQ(uiExtensionNode->GetTag(), V2::UI_EXTENSION_COMPONENT_ETS_TAG);
    auto pattern = uiExtensionNode->GetPattern<UIExtensionPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. test OnFrameNodeChanged
     */
    bool isAncestorNodeGeometryChange = false;
    bool isAncestorNodeTransformChange = false;
    FrameNodeChangeInfoFlag flag = FRAME_NODE_CHANGE_GEOMETRY_CHANGE;
    pattern->OnFrameNodeChanged(flag);
    isAncestorNodeGeometryChange = pattern->IsAncestorNodeGeometryChange(flag);
    isAncestorNodeTransformChange = pattern->IsAncestorNodeTransformChange(flag);
    ASSERT_TRUE(isAncestorNodeGeometryChange);
    ASSERT_FALSE(isAncestorNodeTransformChange);

    flag = FRAME_NODE_CHANGE_INFO_NONE;
    pattern->OnFrameNodeChanged(flag);
    isAncestorNodeGeometryChange = pattern->IsAncestorNodeGeometryChange(flag);
    isAncestorNodeTransformChange = pattern->IsAncestorNodeTransformChange(flag);
    ASSERT_FALSE(isAncestorNodeGeometryChange);
    ASSERT_FALSE(isAncestorNodeTransformChange);

    flag = FRAME_NODE_CHANGE_START_SCROLL;
    pattern->OnFrameNodeChanged(flag);
    isAncestorNodeGeometryChange = pattern->IsAncestorNodeGeometryChange(flag);
    isAncestorNodeTransformChange = pattern->IsAncestorNodeTransformChange(flag);
    ASSERT_FALSE(isAncestorNodeGeometryChange);
    ASSERT_FALSE(isAncestorNodeTransformChange);

    flag = FRAME_NODE_CHANGE_END_SCROLL;
    pattern->OnFrameNodeChanged(flag);
    isAncestorNodeGeometryChange = pattern->IsAncestorNodeGeometryChange(flag);
    isAncestorNodeTransformChange = pattern->IsAncestorNodeTransformChange(flag);
    ASSERT_FALSE(isAncestorNodeGeometryChange);
    ASSERT_FALSE(isAncestorNodeTransformChange);
#endif
}

/**
 * @tc.name: UIExtensionComponentTestTwoNg
 * @tc.desc: Test the method of pattern OnFrameNodeChanged
 * @tc.type: FUNC
 */
HWTEST_F(UIExtensionComponentTestTwoNg, OnFrameNodeChangedTest002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a UIExtensionComponent Node
     */
    auto uiExtensionNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto uiExtensionNode = FrameNode::GetOrCreateFrameNode(
        UI_EXTENSION_COMPONENT_ETS_TAG, uiExtensionNodeId, []() {
            return AceType::MakeRefPtr<UIExtensionPattern>();
        });
    ASSERT_NE(uiExtensionNode, nullptr);
    EXPECT_EQ(uiExtensionNode->GetTag(), V2::UI_EXTENSION_COMPONENT_ETS_TAG);
    auto pattern = uiExtensionNode->GetPattern<UIExtensionPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. test OnFrameNodeChanged
     */
    bool isAncestorNodeGeometryChange = false;
    bool isAncestorNodeTransformChange = false;
    FrameNodeChangeInfoFlag flag = FRAME_NODE_CHANGE_TRANSFORM_CHANGE;
    pattern->OnFrameNodeChanged(flag);
    isAncestorNodeGeometryChange = pattern->IsAncestorNodeGeometryChange(flag);
    isAncestorNodeTransformChange = pattern->IsAncestorNodeTransformChange(flag);
    ASSERT_FALSE(isAncestorNodeGeometryChange);
    ASSERT_TRUE(isAncestorNodeTransformChange);

    flag = FRAME_NODE_CHANGE_TRANSITION_START;
    pattern->OnFrameNodeChanged(flag);
    isAncestorNodeGeometryChange = pattern->IsAncestorNodeGeometryChange(flag);
    isAncestorNodeTransformChange = pattern->IsAncestorNodeTransformChange(flag);
    ASSERT_FALSE(isAncestorNodeGeometryChange);
    ASSERT_FALSE(isAncestorNodeTransformChange);

    flag = FRAME_NODE_CONTENT_CLIP_CHANGE;
    pattern->OnFrameNodeChanged(flag);
    isAncestorNodeGeometryChange = pattern->IsAncestorNodeGeometryChange(flag);
    isAncestorNodeTransformChange = pattern->IsAncestorNodeTransformChange(flag);
    ASSERT_FALSE(isAncestorNodeGeometryChange);
    ASSERT_FALSE(isAncestorNodeTransformChange);

    flag = FRAME_NODE_CHANGE_START_ANIMATION;
    pattern->OnFrameNodeChanged(flag);
    isAncestorNodeGeometryChange = pattern->IsAncestorNodeGeometryChange(flag);
    isAncestorNodeTransformChange = pattern->IsAncestorNodeTransformChange(flag);
    ASSERT_FALSE(isAncestorNodeGeometryChange);
    ASSERT_FALSE(isAncestorNodeTransformChange);
#endif
}

/**
 * @tc.name: UIExtensionComponentTestTwoNg
 * @tc.desc: Test the method of pattern GetAccessibilityRectInfo
 * @tc.type: FUNC
 */
HWTEST_F(UIExtensionComponentTestTwoNg, GetAccessibilityRectInfoTest001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a UIExtensionComponent Node
     */
    auto uiExtensionNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto uiExtensionNode = FrameNode::GetOrCreateFrameNode(
        UI_EXTENSION_COMPONENT_ETS_TAG, uiExtensionNodeId, []() {
            return AceType::MakeRefPtr<UIExtensionPattern>();
        });
    ASSERT_NE(uiExtensionNode, nullptr);
    EXPECT_EQ(uiExtensionNode->GetTag(), V2::UI_EXTENSION_COMPONENT_ETS_TAG);
    auto pattern = uiExtensionNode->GetPattern<UIExtensionPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. test GetAccessibilityRectInfo
     */
    auto context = NG::PipelineContext::GetCurrentContext();
    context->instanceId_ = IGNORE_POSITION_TRANSITION_SWITCH;
    auto rectInfo = pattern->GetAccessibilityRectInfo();
    EXPECT_EQ(rectInfo.left, 0);
    EXPECT_EQ(rectInfo.top, 0);
    EXPECT_EQ(rectInfo.scaleX, 1.0f);
    EXPECT_EQ(rectInfo.scaleY, 1.0f);
#endif
}

/**
 * @tc.name: UIExtensionComponentTestTwoNg
 * @tc.desc: Test the method of pattern TransferAccessibilityRectInfo
 * @tc.type: FUNC
 */
HWTEST_F(UIExtensionComponentTestTwoNg, TransferAccessibilityRectInfoTest001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a UIExtensionComponent Node
     */
    auto uiExtensionNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto uiExtensionNode = FrameNode::GetOrCreateFrameNode(
        UI_EXTENSION_COMPONENT_ETS_TAG, uiExtensionNodeId, []() {
            return AceType::MakeRefPtr<UIExtensionPattern>();
        });
    ASSERT_NE(uiExtensionNode, nullptr);
    EXPECT_EQ(uiExtensionNode->GetTag(), V2::UI_EXTENSION_COMPONENT_ETS_TAG);
    auto pattern = uiExtensionNode->GetPattern<UIExtensionPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. test TransferAccessibilityRectInfo
     */
    pattern->TransferAccessibilityRectInfo();
#endif
}

HWTEST_F(UIExtensionComponentTestTwoNg, UIExtensionComponentTwoTest001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto uiExtensionNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto uiExtensionNode = FrameNode::GetOrCreateFrameNode(
        UI_EXTENSION_COMPONENT_ETS_TAG, uiExtensionNodeId, []() {
            return AceType::MakeRefPtr<UIExtensionPattern>();
        });
    ASSERT_NE(uiExtensionNode, nullptr);
    EXPECT_EQ(uiExtensionNode->GetTag(), V2::UI_EXTENSION_COMPONENT_ETS_TAG);
    auto pattern = uiExtensionNode->GetPattern<UIExtensionPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->OnWindowSceneVisibleChange(true);
    pattern->OnWindowSceneVisibleChange(false);
    UIExtCallbackEventId eventId = UIExtCallbackEventId::ON_DRAW_FIRST;
    pattern->onDrawReadyCallback_ = nullptr;
    pattern->OnExtensionEvent(eventId);
    UIExtCallbackEventId eventId2 = static_cast<UIExtCallbackEventId>(-1);
    pattern->OnExtensionEvent(eventId2);

    int32_t instanceId = 1;
    pattern->UnRegisterUIExtensionManagerEvent(instanceId);
    auto host = pattern->GetHost();
    host->GetFocusHub()->SetCurrentFocus(true);
    pattern->UnRegisterUIExtensionManagerEvent(instanceId);
    pattern->UnRegisterEvent(instanceId);
    EXPECT_EQ(pattern->hasDetachContext_, true);
#endif
}

HWTEST_F(UIExtensionComponentTestTwoNg, UIExtensionComponentTwoTest002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto uiExtensionNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto uiExtensionNode = FrameNode::GetOrCreateFrameNode(
        UI_EXTENSION_COMPONENT_ETS_TAG, uiExtensionNodeId, []() {
            return AceType::MakeRefPtr<UIExtensionPattern>();
        });
    ASSERT_NE(uiExtensionNode, nullptr);
    EXPECT_EQ(uiExtensionNode->GetTag(), V2::UI_EXTENSION_COMPONENT_ETS_TAG);
    auto pattern = uiExtensionNode->GetPattern<UIExtensionPattern>();
    ASSERT_NE(pattern, nullptr);

    auto context = NG::PipelineContext::GetCurrentContext();
    PipelineContext* rawContext = AceType::RawPtr(context);
    auto instanceId = context->GetInstanceId();
    pattern->instanceId_ = context->GetInstanceId();
    pattern->OnDetachContext(rawContext);
    EXPECT_EQ(pattern->hasDetachContext_, true);
    
    pattern->OnDetachContext(rawContext);
    pattern->hasDetachContext_ = false;
    auto host = pattern->GetHost();
    host->setIsMoving(true);
    EXPECT_EQ(pattern->IsMoving(), true);
    pattern->OnDetachContext(rawContext);
    EXPECT_EQ(pattern->hasDetachContext_, false);
    pattern->instanceId_ += 1;
    pattern->OnDetachContext(rawContext);
    EXPECT_EQ(pattern->hasDetachContext_, false);
#endif
}

HWTEST_F(UIExtensionComponentTestTwoNg, UIExtensionComponentTwoTest003, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto uiExtensionNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto uiExtensionNode = FrameNode::GetOrCreateFrameNode(
        UI_EXTENSION_COMPONENT_ETS_TAG, uiExtensionNodeId, []() {
            return AceType::MakeRefPtr<UIExtensionPattern>();
        });
    ASSERT_NE(uiExtensionNode, nullptr);
    EXPECT_EQ(uiExtensionNode->GetTag(), V2::UI_EXTENSION_COMPONENT_ETS_TAG);
    auto pattern = uiExtensionNode->GetPattern<UIExtensionPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->AttachToFrameNode(uiExtensionNode);
    pattern->OnModifyDone();
    pattern->OnModifyDone();
    EXPECT_NE(pattern->touchEvent_, nullptr);

    auto focusHub = uiExtensionNode->GetFocusHub();
    pattern->InitKeyEventOnKeyEvent(focusHub);
    KeyEvent keyEvent;
    pattern->SetForceProcessOnKeyEventInternal(false);
    keyEvent.pressedCodes.push_back(KeyCode::KEY_TAB);
    keyEvent.isPreIme = true;
    focusHub->onKeyEventsInternal_[OnKeyEventType::DEFAULT].operator()(keyEvent);
    EXPECT_EQ(pattern->GetForceProcessOnKeyEventInternal(), false);

    auto onError = [](int32_t code, const std::string& name, const std::string& message) {};
    pattern->lastError_.code = 1;
    pattern->SetOnErrorCallback(std::move(onError));
    pattern->onSyncOnCallbackList_ = {nullptr, nullptr};
    pattern->FireSyncCallbacks();
    pattern->onAsyncOnCallbackList_ = {nullptr, nullptr};
    pattern->FireAsyncCallbacks();
    auto host = pattern->GetHost();
    host->setIsMoving(true);
    pattern->HandleVisibleAreaChange(false, 0.0);
    EXPECT_EQ(pattern->IsMoving(), true);
#endif
}

/**
 * @tc.name: UIExtensionComponentTestTwoNg
 * @tc.desc: Test the method of pattern OnAttachContext
 * @tc.type: FUNC
 */
HWTEST_F(UIExtensionComponentTestTwoNg, OnAttachContext001, TestSize.Level1)
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
     * @tc.steps: step2. test OnAttachContext
     */
    auto pipelineContext = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipelineContext, nullptr);
    auto newInstanceId = pipelineContext->GetInstanceId();
    ASSERT_NE(newInstanceId, pattern->instanceId_);
    pipelineContext->uiExtensionManager_ = nullptr;
    pattern->OnAttachContext(AceType::RawPtr(pipelineContext));
    ASSERT_EQ(newInstanceId, pattern->instanceId_);
#endif
}


/**
 * @tc.name: UIExtensionComponentTestTwoNg
 * @tc.desc: Test the method of pattern OnAttachContext
 * @tc.type: FUNC
 */
HWTEST_F(UIExtensionComponentTestTwoNg, OnAttachContext002, TestSize.Level1)
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
     * @tc.steps: step2. test OnAttachContext
     */
    auto pipelineContext = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->uiExtensionManager_ = nullptr;
    auto newInstanceId = pipelineContext->GetInstanceId();
    ASSERT_NE(newInstanceId, pattern->instanceId_);
    pattern->UnRegisterEvent(newInstanceId);
    ASSERT_EQ(pattern->hasDetachContext_, true);
    pattern->OnAttachContext(AceType::RawPtr(pipelineContext));
    ASSERT_EQ(pattern->hasDetachContext_, false);
#endif
}

/**
 * @tc.name: UIExtensionComponentTestTwoNg
 * @tc.desc: Test the method of pattern UpdateSessionInstanceId
 * @tc.type: FUNC
 */
HWTEST_F(UIExtensionComponentTestTwoNg, UpdateSessionInstanceId001, TestSize.Level1)
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
    ASSERT_NE(pattern->sessionWrapper_, nullptr);

    /**
     * @tc.steps: step2. test UpdateSessionInstanceId
     */
    int32_t instanceId = 100;
    auto sessionWrapperImpl = AceType::DynamicCast<SessionWrapperImpl>(pattern->sessionWrapper_);
    ASSERT_NE(sessionWrapperImpl, nullptr);
    ASSERT_NE(sessionWrapperImpl->instanceId_, instanceId);
    pattern->UpdateSessionInstanceId(instanceId);
    ASSERT_NE(sessionWrapperImpl->instanceId_, instanceId);
    pattern->sessionWrapper_ = nullptr;
    pattern->UpdateSessionInstanceId(instanceId);
#endif
}

/**
 * @tc.name: UIExtensionComponentTestTwoNg
 * @tc.desc: Test the method of pattern RegisterEvent
 * @tc.type: FUNC
 */
HWTEST_F(UIExtensionComponentTestTwoNg, RegisterEvent001, TestSize.Level1)
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
    pattern->hasDetachContext_ = true;

    /**
     * @tc.steps: step2. test RegisterEvent
     */
    int32_t instanceId = 100;
    pattern->RegisterEvent(instanceId);
    ASSERT_FALSE(pattern->hasDetachContext_);
#endif
}

/**
 * @tc.name: UIExtensionComponentTestTwoNg
 * @tc.desc: Test the method of pattern RegisterUIExtensionManagerEvent
 * @tc.type: FUNC
 */
HWTEST_F(UIExtensionComponentTestTwoNg, RegisterUIExtensionManagerEvent001, TestSize.Level1)
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
     * @tc.steps: step2. test RegisterUIExtensionManagerEvent
     */
    pattern->frameNode_ = uiExtensionNode;
    ASSERT_NE(pattern->GetHost(), nullptr);
    int32_t instanceId = 100;
    auto pipelineContext = PipelineContext::GetContextByContainerId(instanceId);
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->uiExtensionManager_ = AceType::MakeRefPtr<UIExtensionManager>();
    auto uiExtensionManager = pipelineContext->GetUIExtensionManager();
    ASSERT_NE(uiExtensionManager, nullptr);

    auto focusHub = pattern->GetHost()->GetFocusHub();
    EXPECT_NE(focusHub, nullptr);
    focusHub->currentFocus_ = false;
    EXPECT_FALSE(focusHub->IsCurrentFocus());
    pattern->RegisterUIExtensionManagerEvent(instanceId);

    focusHub->currentFocus_ = true;
    EXPECT_NE(focusHub, nullptr);
    EXPECT_TRUE(focusHub->IsCurrentFocus());
    pattern->RegisterUIExtensionManagerEvent(instanceId);
#endif
}

/**
 * @tc.name: UIExtensionComponentTestTwoNg
 * @tc.desc: Test UIExtensionComponent tab focus
 * @tc.type: FUNC
 */
HWTEST_F(UIExtensionComponentTestTwoNg, UIExtensionComponentTabFocus, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto uiExtensionNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto uiExtensionNode = FrameNode::GetOrCreateFrameNode(
        UI_EXTENSION_COMPONENT_ETS_TAG, uiExtensionNodeId, []() {
            return AceType::MakeRefPtr<UIExtensionPattern>();
        });
    ASSERT_NE(uiExtensionNode, nullptr);
    EXPECT_EQ(uiExtensionNode->GetTag(), V2::UI_EXTENSION_COMPONENT_ETS_TAG);
    auto pattern = uiExtensionNode->GetPattern<UIExtensionPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_EQ(pattern->GetForceProcessOnKeyEventInternal(), false);
    EXPECT_EQ(pattern->canFocusSendToUIExtension_, true);

    pattern->AttachToFrameNode(uiExtensionNode);
    pattern->OnModifyDone();

    auto pipeline = uiExtensionNode->GetContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->isFocusingByTab_ = false;
    EXPECT_EQ(pipeline->GetIsFocusingByTab(), false);
    pattern->HandleFocusEvent();
    EXPECT_EQ(pattern->GetForceProcessOnKeyEventInternal(), true);

    auto focusHub = uiExtensionNode->GetFocusHub();
    pattern->InitKeyEventOnKeyEvent(focusHub);
    KeyEvent keyEvent;
    pattern->SetForceProcessOnKeyEventInternal(false);
    keyEvent.pressedCodes.push_back(KeyCode::KEY_TAB);
    keyEvent.isPreIme = false;
    focusHub->onKeyEventsInternal_[OnKeyEventType::DEFAULT].operator()(keyEvent);
    EXPECT_EQ(pattern->GetForceProcessOnKeyEventInternal(), false);

    pipeline->isFocusingByTab_ = false;
    EXPECT_EQ(pipeline->GetIsFocusingByTab(), false);
    pattern->HandleFocusEvent();
    EXPECT_EQ(pattern->GetForceProcessOnKeyEventInternal(), true);

    pattern->HandleBlurEvent();
    EXPECT_EQ(pattern->GetForceProcessOnKeyEventInternal(), false);
#endif
}

/**
 * @tc.name: UIExtensionComponentTestTwoNg
 * @tc.desc: Test the method of pattern HandleTouch
 * @tc.type: FUNC
 */
HWTEST_F(UIExtensionComponentTestTwoNg, UIExtensionComponentHandleTouch, TestSize.Level1)
{
    /**
    * @tc.steps: step1. construct UIExtensionNode
    */
    auto uiextensionNode = UIExtensionNode::GetOrCreateUIExtensionNode(V2::UI_EXTENSION_COMPONENT_ETS_TAG, 1,
        []() { return AceType::MakeRefPtr<UIExtensionPattern>(); });
    ASSERT_NE(uiextensionNode, nullptr);
    auto pattern = uiextensionNode->GetPattern<UIExtensionPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
    * @tc.steps: step2. attach PipelineContext and FocusHub
    */
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(uiextensionNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    uiextensionNode->focusHub_ = focusHub;
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    context->SetEventManager(AceType::MakeRefPtr<EventManager>());
    EXPECT_NE(context->GetEventManager(), nullptr);
    uiextensionNode->context_ = AceType::RawPtr(context);
    /**
    * @tc.steps: step3. Test HandleTouchEvent
    */
    TouchEventInfo touchEventInfo("onTouch");
    touchEventInfo.SetSourceDevice(SourceType::MOUSE);
    pattern->HandleTouchEvent(touchEventInfo);
    touchEventInfo.SetSourceDevice(SourceType::TOUCH);
    context->onFocus_ = false;
    pattern->HandleTouchEvent(touchEventInfo);
    EXPECT_EQ(pattern->canFocusSendToUIExtension_, true);
    context->onFocus_ = true;
    focusHub->currentFocus_ = true;
    pattern->HandleTouchEvent(touchEventInfo);
    EXPECT_EQ(pattern->canFocusSendToUIExtension_, true);
    focusHub->currentFocus_ = false;
    pattern->HandleTouchEvent(touchEventInfo);
    EXPECT_EQ(pattern->canFocusSendToUIExtension_, true);
    touchEventInfo.SetPointerEvent(nullptr);
    pattern->HandleTouchEvent(touchEventInfo);
    std::shared_ptr<MMI::PointerEvent> pointerEvent = std::make_shared<MMI::PointerEvent>(1);
    pointerEvent->SetPointerAction(MMI::PointerEvent::POINTER_ACTION_UP);
    touchEventInfo.SetPointerEvent(pointerEvent);
    pattern->needReSendFocusToUIExtension_ = true;
    pattern->HandleTouchEvent(touchEventInfo);
    EXPECT_EQ(pattern->needReSendFocusToUIExtension_, false);
}

/**
 * @tc.name: UIExtensionComponentTestTwoNg
 * @tc.desc: Test the method of pattern HandleOcclusionScene
 * @tc.type: FUNC
 */
HWTEST_F(UIExtensionComponentTestTwoNg, OnHandleOcclusionScene001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
    * @tc.steps: step1. construct a UIExtensionComponent Node
    */
    auto uiExtensionNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto uiExtensionNode = FrameNode::GetOrCreateFrameNode(
        UI_EXTENSION_COMPONENT_ETS_TAG, uiExtensionNodeId, []() {
            return AceType::MakeRefPtr<UIExtensionPattern>();
        });
    ASSERT_NE(uiExtensionNode, nullptr);
    EXPECT_EQ(uiExtensionNode->GetTag(), V2::UI_EXTENSION_COMPONENT_ETS_TAG);
    auto pattern = uiExtensionNode->GetPattern<UIExtensionPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
    * @tc.steps: step2. test HandleOcclusionScene
    */
    pattern->frameNode_ = uiExtensionNode;
    ASSERT_NE(pattern->frameNode_.Upgrade(), nullptr);
    auto host = pattern->GetHost();
    ASSERT_NE(host, nullptr);
    ASSERT_NE(WindowSceneHelper::FindWindowScene(host), nullptr);
    pattern->HandleOcclusionScene(host, false);
    std::string id = host->GetInspectorId().value_or("");
    host->UpdateInspectorId(id.append("_occlusion"));
    pattern->HandleOcclusionScene(host, false);
#endif
}

/**
 * @tc.name: UIExtensionComponentTestTwoNg
 * @tc.desc: Test UIExtensionComponent UIExtensionNode
 * @tc.type: FUNC
 */
HWTEST_F(UIExtensionComponentTestTwoNg, UIExtensionComponentUIExtensionNode, TestSize.Level1)
{
    /**
    * @tc.steps: step1. construct UIExtensionNode
    */
    auto uiExtensionNodeId1 = ElementRegister::GetInstance()->MakeUniqueId();
    auto uiExtensionNode1 = UIExtensionNode::GetOrCreateUIExtensionNode(
        UI_EXTENSION_COMPONENT_ETS_TAG, uiExtensionNodeId1, []() {
            return AceType::MakeRefPtr<UIExtensionPattern>();
        });
    ASSERT_NE(uiExtensionNode1, nullptr);
    auto uiExtensionNodeId2 = ElementRegister::GetInstance()->MakeUniqueId();
    auto uiExtensionNode2 = UIExtensionNode::GetOrCreateUIExtensionNode(
        UI_EXTENSION_COMPONENT_ETS_TAG, uiExtensionNodeId2, []() {
            return AceType::MakeRefPtr<UIExtensionPattern>();
        });
    ASSERT_NE(uiExtensionNode2, nullptr);
    uiExtensionNode1->MountToParent(uiExtensionNode2);
    EXPECT_EQ(uiExtensionNode1->GetId(), uiExtensionNodeId1);
    /**
    * @tc.steps: step2. test UIExtensionNode diff tag
    */
    auto uiExtensionNode3 = UIExtensionNode::GetOrCreateUIExtensionNode(
        UI_EXTENSION_COMPONENT_ETS_TAG, uiExtensionNodeId1, []() {
            return AceType::MakeRefPtr<UIExtensionPattern>();
        });
    ASSERT_NE(uiExtensionNode3, nullptr);
    EXPECT_EQ(uiExtensionNode3->GetId(), uiExtensionNodeId1);
    auto uiExtensionNode4 = UIExtensionNode::GetOrCreateUIExtensionNode(
        "tag", uiExtensionNodeId1, []() {
            return AceType::MakeRefPtr<UIExtensionPattern>();
        });
    ASSERT_NE(uiExtensionNode4, nullptr);
    EXPECT_EQ(uiExtensionNode4->GetId(), uiExtensionNodeId1);
}

/**
 * @tc.name: UIExtensionComponentTestTwoNg
 * @tc.desc: Test UIExtensionComponent Touch Delegate
 * @tc.type: FUNC
 */
HWTEST_F(UIExtensionComponentTestTwoNg, UIExtensionComponentTouchDelegate, TestSize.Level1)
{
    /**
    * @tc.steps: step1. construct pointer event
    */
    PointF globalPoint;
    PointF parentLocalPoint;
    PointF parentRevertPoint;
    TouchRestrict touchRestrict;
    touchRestrict.hitTestType = SourceType::TOUCH;
    TouchTestResult result;
    int32_t touchId = 0;
    ResponseLinkResult responseLinkResult;
    bool isDispatch = false;
    /**
    * @tc.steps: step2. construct UIExtensionNode
    */
    auto uiextensionNode = UIExtensionNode::GetOrCreateUIExtensionNode(V2::UI_EXTENSION_COMPONENT_ETS_TAG, 1,
        []() { return AceType::MakeRefPtr<UIExtensionPattern>(); });
    ASSERT_NE(uiextensionNode, nullptr);
    /**
    * @tc.steps: step3. test UIExtensionNode TouchTest
    */
    auto res = uiextensionNode->TouchTest(globalPoint, parentLocalPoint,
        parentRevertPoint, touchRestrict, result, touchId, responseLinkResult, isDispatch);
    EXPECT_EQ(res, HitTestResult::OUT_OF_REGION);
    auto pattern = uiextensionNode->GetPattern<UIExtensionPattern>();
    EXPECT_NE(pattern, nullptr);
    /**
    * @tc.steps: step4. construct uiExtensionTouchDelegate by UIExtensionNode pattern
    */
    UIExtensionTouchDelegate uiExtensionTouchDelegate(pattern);
    /**
    * @tc.steps: step5. test DelegateTouchEvent
    */
    TouchEvent touchEvent;
    uiExtensionTouchDelegate.DelegateTouchEvent(touchEvent);
    EXPECT_EQ(uiExtensionTouchDelegate.pattern_.Upgrade(), pattern);
}

/**
 * @tc.name: UIExtensionComponentTestTwoNg
 * @tc.desc: Test UIExtension HandleMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(UIExtensionComponentTestTwoNg, UIExtensionHandleMouseEvent, TestSize.Level1)
{
    /**
    * @tc.steps: step1. construct UIExtensionNode and get pattern
    */
    auto uiextensionNode = UIExtensionNode::GetOrCreateUIExtensionNode(V2::UI_EXTENSION_COMPONENT_ETS_TAG, 1,
        []() { return AceType::MakeRefPtr<UIExtensionPattern>(); });
    ASSERT_NE(uiextensionNode, nullptr);
    auto pattern = uiextensionNode->GetPattern<UIExtensionPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. call HandleMouseEvent.
     * @tc.expected: test HandleTouchEvent with different action.
     */
    MouseInfo mouseInfo;
    mouseInfo.SetSourceDevice(SourceType::NONE);
    std::shared_ptr<MMI::PointerEvent> pointerEvent = std::make_shared<MMI::PointerEvent>(1);
    mouseInfo.SetPointerEvent(pointerEvent);
    pattern->HandleMouseEvent(mouseInfo);
    EXPECT_FALSE(pattern->lastPointerEvent_);
 
    mouseInfo.SetSourceDevice(SourceType::MOUSE);
    mouseInfo.SetPullAction(MouseAction::PULL_MOVE);
    pattern->HandleMouseEvent(mouseInfo);
    EXPECT_FALSE(pattern->lastPointerEvent_);
 
    mouseInfo.SetPullAction(MouseAction::PULL_UP);
    pattern->HandleMouseEvent(mouseInfo);
    EXPECT_FALSE(pattern->lastPointerEvent_);
 
    mouseInfo.SetPullAction(MouseAction::PRESS);
    pattern->HandleMouseEvent(mouseInfo);
    EXPECT_TRUE(pattern->lastPointerEvent_);
 
    mouseInfo.SetPullAction(MouseAction::RELEASE);
    pattern->HandleMouseEvent(mouseInfo);
    EXPECT_TRUE(pattern->lastPointerEvent_);
}

/**
 * @tc.name: UIExtensionComponentTestTwoNg
 * @tc.desc: Test UIExtension HandleTouch pull and mouse
 * @tc.type: FUNC
 */
HWTEST_F(UIExtensionComponentTestTwoNg, UIExtensionHandleTouchPullAndMouse, TestSize.Level1)
{
    /**
    * @tc.steps: step1. construct UIExtensionNode and get pattern
    */
    auto uiextensionNode = UIExtensionNode::GetOrCreateUIExtensionNode(V2::UI_EXTENSION_COMPONENT_ETS_TAG, 1,
        []() { return AceType::MakeRefPtr<UIExtensionPattern>(); });
    ASSERT_NE(uiextensionNode, nullptr);
    auto pattern = uiextensionNode->GetPattern<UIExtensionPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
    * @tc.steps: step2. Test UIExtension pattern HandleTouch
    */
    std::shared_ptr<MMI::PointerEvent> pointerEvent = std::make_shared<MMI::PointerEvent>(1);

    pointerEvent->SetSourceType(OHOS::MMI::PointerEvent::SOURCE_TYPE_MOUSE);
    auto ret = pattern->HandleTouchEvent(pointerEvent);
    EXPECT_FALSE(ret);

    pointerEvent->SetSourceType(OHOS::MMI::PointerEvent::SOURCE_TYPE_TOUCHSCREEN);

    pointerEvent->SetPointerAction(OHOS::MMI::PointerEvent::POINTER_ACTION_PULL_MOVE);
    ret = pattern->HandleTouchEvent(pointerEvent);
    EXPECT_FALSE(ret);

    pointerEvent->SetPointerAction(OHOS::MMI::PointerEvent::POINTER_ACTION_PULL_UP);
    ret = pattern->HandleTouchEvent(pointerEvent);
    EXPECT_FALSE(ret);

    pointerEvent->SetPointerAction(OHOS::MMI::PointerEvent::POINTER_ACTION_UP);
    ret = pattern->HandleTouchEvent(pointerEvent);
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: InitBusinessDataHandleCallback001
 * @tc.desc: Test Func InitBusinessDataHandleCallback
 * @tc.type: FUNC
 */
HWTEST_F(UIExtensionComponentTestTwoNg, InitBusinessDataHandleCallback001, TestSize.Level1)
{
    /**
    * @tc.steps: step1. construct UIExtensionNode and get pattern
    */
    auto uiextensionNode = UIExtensionNode::GetOrCreateUIExtensionNode(V2::UI_EXTENSION_COMPONENT_ETS_TAG, 1,
        []() { return AceType::MakeRefPtr<UIExtensionPattern>(); });
    ASSERT_NE(uiextensionNode, nullptr);
    auto pattern = uiextensionNode->GetPattern<UIExtensionPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
    * @tc.steps: step2. Test Func InitBusinessDataHandleCallback
    */
    pattern->InitBusinessDataHandleCallback();
    EXPECT_GT(pattern->businessDataUECConsumeCallbacks_.count(UIContentBusinessCode::SEND_PAGE_MODE_REQUEST), 0);
}

HWTEST_F(UIExtensionComponentTestTwoNg, OnAttachContextTest, TestSize.Level1)
{
    auto uiExtensionNodeId1 = ElementRegister::GetInstance()->MakeUniqueId();
    auto uiExtensionNode1 = FrameNode::GetOrCreateFrameNode(
        UI_EXTENSION_COMPONENT_ETS_TAG, uiExtensionNodeId1, []() { return AceType::MakeRefPtr<UIExtensionPattern>(); });
    ASSERT_NE(uiExtensionNode1, nullptr);
    EXPECT_EQ(uiExtensionNode1->GetTag(), V2::UI_EXTENSION_COMPONENT_ETS_TAG);
    auto pattern1 = uiExtensionNode1->GetPattern<UIExtensionPattern>();
    ASSERT_NE(pattern1, nullptr);
    EXPECT_EQ(pattern1->hasAttachContext_, false);

    auto uiExtensionNodeId2 = ElementRegister::GetInstance()->MakeUniqueId();
    auto uiExtensionNode2 = FrameNode::GetOrCreateFrameNode(
        UI_EXTENSION_COMPONENT_ETS_TAG, uiExtensionNodeId2, []() { return AceType::MakeRefPtr<UIExtensionPattern>(); });
    ASSERT_NE(uiExtensionNode2, nullptr);
    EXPECT_EQ(uiExtensionNode2->GetTag(), V2::UI_EXTENSION_COMPONENT_ETS_TAG);
    auto pattern2 = uiExtensionNode2->GetPattern<UIExtensionPattern>();
    ASSERT_NE(pattern2, nullptr);
    EXPECT_EQ(pattern2->hasAttachContext_, false);

    auto context = NG::PipelineContext::GetCurrentContext();
    pattern1->instanceId_ = context->GetInstanceId();
    pattern1->curWant_ = AceType::MakeRefPtr<WantWrapOhos>("123", "123");
    pattern2->instanceId_ = context->GetInstanceId();
    pattern2->curWant_ = AceType::MakeRefPtr<WantWrapOhos>("123", "123");

    context->frontendType_ = FrontendType::ARK_TS;
    PipelineContext* rawContext = AceType::RawPtr(context);
    pattern1->OnAttachContext(rawContext);
    EXPECT_EQ(pattern1->hasAttachContext_, true);

    context->frontendType_ = FrontendType::DECLARATIVE_JS;
    pattern2->OnAttachContext(rawContext);
    EXPECT_EQ(pattern2->hasAttachContext_, false);
}
} // namespace OHOS::Ace::NG
