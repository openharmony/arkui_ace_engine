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
#include "core/components_ng/pattern/ui_extension/isolated_component/isolated_pattern.h"
#include "core/components_ng/pattern/ui_extension/security_ui_extension_component/security_ui_extension_pattern.h"
#include "core/components_ng/pattern/ui_extension/session_wrapper.h"
#include "core/components_ng/pattern/ui_extension/session_wrapper_factory.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_component/modal_ui_extension_proxy_impl.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_component/session_wrapper_impl.h"
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

#include "mock/mock_accessibility_child_tree_callback.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/common/mock_container.h"

#include "core/components_ng/render/adapter/rosen_window.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/render/mock_rosen_render_context.h"
#include "frameworks/core/components_ng/pattern/ui_extension/platform_event_proxy.h"
#include "test/unittest/core/pattern/ui_extension/mock/mock_window_scene_helper.h"

#include "adapter/ohos/entrance/ace_container.h"
#include "accessibility_event_info.h"
#include "transaction/rs_sync_transaction_controller.h"
#include "transaction/rs_transaction.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
    const std::string UI_EXTENSION_COMPONENT_ETS_TAG = "UIExtensionComponent";
    constexpr char UI_EXTENSION_TYPE_KEY[] = "ability.want.params.uiExtensionType";
    const std::string EMBEDDED_UI("embeddedUI");
} // namespace

class SessionWrapperImplNewTestNg : public testing::Test {
public:
    void SetUp() override;
    void TearDown() override;
    static void SetUpTestSuite()
    {
        MockPipelineContext::SetUp();
        MockContainer::SetUp();
        MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
        MockContainer::Current()->pipelineContext_->taskExecutor_ = MockContainer::Current()->taskExecutor_;
        MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    }
    static void TearDownTestSuite()
    {
        MockPipelineContext::TearDown();
        MockContainer::TearDown();
    }
    RefPtr<SessionWrapperImpl> GenerateSessionWrapperImpl();
};

void SessionWrapperImplNewTestNg::SetUp() {
}

void SessionWrapperImplNewTestNg::TearDown() {
}

RefPtr<SessionWrapperImpl> SessionWrapperImplNewTestNg::GenerateSessionWrapperImpl()
{
    auto uiExtensionNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto uiExtensionNode = FrameNode::GetOrCreateFrameNode(
        UI_EXTENSION_COMPONENT_ETS_TAG, uiExtensionNodeId, []() { return AceType::MakeRefPtr<UIExtensionPattern>(); });
    auto pattern = uiExtensionNode->GetPattern<UIExtensionPattern>();
    auto sessionWrapper =
        AceType::MakeRefPtr<SessionWrapperImpl>(pattern, pattern->instanceId_, 1, SessionType::UI_EXTENSION_ABILITY);
    return sessionWrapper;
}

/**
 * @tc.name: SessionWrapperImplNewTestNg001
 * @tc.desc: Test the method InitForegroundCallback.
 * @tc.type: FUNC
 */
HWTEST_F(SessionWrapperImplNewTestNg, SessionWrapperImplNewTestNg001, TestSize.Level1)
{
    auto sessionWrapper = GenerateSessionWrapperImpl();
    EXPECT_EQ(sessionWrapper->session_, nullptr);
    sessionWrapper->InitForegroundCallback();
    EXPECT_EQ(sessionWrapper->foregroundCallback_, nullptr);
    
    Rosen::SessionInfo sessionInfo;
    sessionWrapper->session_ = new Rosen::ExtensionSession(sessionInfo);
    sessionWrapper->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    EXPECT_NE(sessionWrapper->session_, nullptr);
    EXPECT_NE(sessionWrapper->taskExecutor_, nullptr);
    sessionWrapper->hostPattern_ = nullptr;
    
    sessionWrapper->InitForegroundCallback();
    OHOS::Rosen::WSError errcode = OHOS::Rosen::WSError::WS_DO_NOTHING;
    sessionWrapper->foregroundCallback_(errcode);

    errcode = OHOS::Rosen::WSError::WS_OK;
    sessionWrapper->foregroundCallback_(errcode);

    errcode = OHOS::Rosen::WSError::WS_DO_NOTHING;
    sessionWrapper->taskExecutor_ = nullptr;
    sessionWrapper->foregroundCallback_(errcode);

    errcode = OHOS::Rosen::WSError::WS_DO_NOTHING;
    sessionWrapper->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    sessionWrapper->foregroundCallback_(errcode);

    auto uiExtensionNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto uiExtensionNode = FrameNode::GetOrCreateFrameNode(
        UI_EXTENSION_COMPONENT_ETS_TAG, uiExtensionNodeId, []() { return AceType::MakeRefPtr<UIExtensionPattern>(); });
    auto pattern = uiExtensionNode->GetPattern<UIExtensionPattern>();

    auto weak = AceType::WeakClaim(AceType::RawPtr(pattern));
    sessionWrapper->hostPattern_ = weak;
    errcode = OHOS::Rosen::WSError::WS_DO_NOTHING;
    sessionWrapper->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    sessionWrapper->InitForegroundCallback();
    sessionWrapper->foregroundCallback_(errcode);
    EXPECT_NE(sessionWrapper->foregroundCallback_, nullptr);
    
    sessionWrapper->session_->persistentId_ = 0;
    sessionWrapper->InitForegroundCallback();
    sessionWrapper->foregroundCallback_(errcode);
    EXPECT_NE(sessionWrapper->foregroundCallback_, nullptr);
    EXPECT_TRUE(pattern->IsCompatibleOldVersion());
}

/**
 * @tc.name: SessionWrapperImplNewTestNg002
 * @tc.desc: Test the method InitBackgroundCallback.
 * @tc.type: FUNC
 */
HWTEST_F(SessionWrapperImplNewTestNg, SessionWrapperImplNewTestNg002, TestSize.Level1)
{
    auto sessionWrapper = GenerateSessionWrapperImpl();
    EXPECT_EQ(sessionWrapper->session_, nullptr);
    sessionWrapper->InitBackgroundCallback();
    EXPECT_EQ(sessionWrapper->backgroundCallback_, nullptr);
    
    Rosen::SessionInfo sessionInfo;
    sessionWrapper->session_ = new Rosen::ExtensionSession(sessionInfo);
    sessionWrapper->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    EXPECT_NE(sessionWrapper->session_, nullptr);
    EXPECT_NE(sessionWrapper->taskExecutor_, nullptr);
    sessionWrapper->hostPattern_ = nullptr;
    
    sessionWrapper->InitBackgroundCallback();
    OHOS::Rosen::WSError errcode = OHOS::Rosen::WSError::WS_DO_NOTHING;
    sessionWrapper->backgroundCallback_(errcode);

    errcode = OHOS::Rosen::WSError::WS_OK;
    sessionWrapper->backgroundCallback_(errcode);

    errcode = OHOS::Rosen::WSError::WS_DO_NOTHING;
    sessionWrapper->taskExecutor_ = nullptr;
    sessionWrapper->backgroundCallback_(errcode);

    errcode = OHOS::Rosen::WSError::WS_DO_NOTHING;
    sessionWrapper->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    sessionWrapper->backgroundCallback_(errcode);

    auto uiExtensionNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto uiExtensionNode = FrameNode::GetOrCreateFrameNode(
        UI_EXTENSION_COMPONENT_ETS_TAG, uiExtensionNodeId, []() { return AceType::MakeRefPtr<UIExtensionPattern>(); });
    auto pattern = uiExtensionNode->GetPattern<UIExtensionPattern>();

    auto weak = AceType::WeakClaim(AceType::RawPtr(pattern));
    sessionWrapper->hostPattern_ = weak;
    errcode = OHOS::Rosen::WSError::WS_DO_NOTHING;
    sessionWrapper->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    sessionWrapper->InitBackgroundCallback();
    sessionWrapper->backgroundCallback_(errcode);
    EXPECT_NE(sessionWrapper->backgroundCallback_, nullptr);
    
    sessionWrapper->session_->persistentId_ = 0;
    sessionWrapper->InitBackgroundCallback();
    sessionWrapper->backgroundCallback_(errcode);
    EXPECT_NE(sessionWrapper->backgroundCallback_, nullptr);
    EXPECT_TRUE(pattern->IsCompatibleOldVersion());
}

/**
 * @tc.name: SessionWrapperImplNewTestNg003
 * @tc.desc: Test the method InitDestructionCallback.
 * @tc.type: FUNC
 */
HWTEST_F(SessionWrapperImplNewTestNg, SessionWrapperImplNewTestNg003, TestSize.Level1)
{
    auto sessionWrapper = GenerateSessionWrapperImpl();
    EXPECT_EQ(sessionWrapper->session_, nullptr);
    sessionWrapper->InitDestructionCallback();
    EXPECT_EQ(sessionWrapper->destructionCallback_, nullptr);
    
    Rosen::SessionInfo sessionInfo;
    sessionWrapper->session_ = new Rosen::ExtensionSession(sessionInfo);
    sessionWrapper->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    EXPECT_NE(sessionWrapper->session_, nullptr);
    EXPECT_NE(sessionWrapper->taskExecutor_, nullptr);
    sessionWrapper->hostPattern_ = nullptr;
    
    sessionWrapper->InitDestructionCallback();
    OHOS::Rosen::WSError errcode = OHOS::Rosen::WSError::WS_DO_NOTHING;
    sessionWrapper->destructionCallback_(errcode);

    errcode = OHOS::Rosen::WSError::WS_OK;
    sessionWrapper->destructionCallback_(errcode);

    errcode = OHOS::Rosen::WSError::WS_DO_NOTHING;
    sessionWrapper->taskExecutor_ = nullptr;
    sessionWrapper->destructionCallback_(errcode);

    errcode = OHOS::Rosen::WSError::WS_DO_NOTHING;
    sessionWrapper->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    sessionWrapper->destructionCallback_(errcode);

    auto uiExtensionNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto uiExtensionNode = FrameNode::GetOrCreateFrameNode(
        UI_EXTENSION_COMPONENT_ETS_TAG, uiExtensionNodeId, []() { return AceType::MakeRefPtr<UIExtensionPattern>(); });
    auto pattern = uiExtensionNode->GetPattern<UIExtensionPattern>();

    auto weak = AceType::WeakClaim(AceType::RawPtr(pattern));
    sessionWrapper->hostPattern_ = weak;
    errcode = OHOS::Rosen::WSError::WS_DO_NOTHING;
    sessionWrapper->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    sessionWrapper->InitDestructionCallback();
    sessionWrapper->destructionCallback_(errcode);
    EXPECT_NE(sessionWrapper->destructionCallback_, nullptr);
    
    sessionWrapper->session_->persistentId_ = 0;
    sessionWrapper->InitDestructionCallback();
    sessionWrapper->destructionCallback_(errcode);
    EXPECT_NE(sessionWrapper->destructionCallback_, nullptr);
    EXPECT_TRUE(pattern->IsCompatibleOldVersion());
}

/**
 * @tc.name: SessionWrapperImplNewTestNg004
 * @tc.desc: Test the method InitTransferAbilityResultFunc.
 * @tc.type: FUNC
 */
HWTEST_F(SessionWrapperImplNewTestNg, SessionWrapperImplNewTestNg004, TestSize.Level1)
{
    auto sessionWrapper = GenerateSessionWrapperImpl();
    EXPECT_EQ(sessionWrapper->session_, nullptr);
    sessionWrapper->InitTransferAbilityResultFunc();
    
    Rosen::SessionInfo sessionInfo;
    sessionWrapper->session_ = new Rosen::ExtensionSession(sessionInfo);
    sessionWrapper->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    EXPECT_NE(sessionWrapper->session_, nullptr);
    EXPECT_NE(sessionWrapper->taskExecutor_, nullptr);
    sessionWrapper->InitTransferAbilityResultFunc();

    auto sessionCallbacks = sessionWrapper->session_->GetExtensionSessionEventCallback();
    int32_t code = 0;
    AAFwk::Want want;

    auto uiExtensionNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto uiExtensionNode = FrameNode::GetOrCreateFrameNode(
        UI_EXTENSION_COMPONENT_ETS_TAG, uiExtensionNodeId, []() { return AceType::MakeRefPtr<UIExtensionPattern>(); });
    auto pattern = uiExtensionNode->GetPattern<UIExtensionPattern>();
    auto weak = AceType::WeakClaim(AceType::RawPtr(pattern));
    sessionWrapper->hostPattern_ = weak;

    sessionWrapper->taskExecutor_ = nullptr;
    sessionWrapper->InitTransferAbilityResultFunc();
    sessionCallbacks->transferAbilityResultFunc_(code, want);
    EXPECT_NE(sessionCallbacks->transferAbilityResultFunc_, nullptr);
    
    sessionWrapper->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    sessionWrapper->InitTransferAbilityResultFunc();
    sessionCallbacks->transferAbilityResultFunc_(code, want);
    EXPECT_NE(sessionCallbacks->transferAbilityResultFunc_, nullptr);

    sessionWrapper->session_->persistentId_ = 0;
    sessionWrapper->InitTransferAbilityResultFunc();
    sessionCallbacks->transferAbilityResultFunc_(code, want);
    EXPECT_NE(sessionCallbacks->transferAbilityResultFunc_, nullptr);

    sessionWrapper->sessionType_ = SessionType::INVALID_TYPE;
    sessionWrapper->InitTransferAbilityResultFunc();
    sessionCallbacks->transferAbilityResultFunc_(code, want);
    EXPECT_NE(sessionCallbacks->transferAbilityResultFunc_, nullptr);
}

/**
 * @tc.name: SessionWrapperImplNewTestNg005
 * @tc.desc: Test the method InitTransferExtensionDataFunc.
 * @tc.type: FUNC
 */
HWTEST_F(SessionWrapperImplNewTestNg, SessionWrapperImplNewTestNg005, TestSize.Level1)
{
    auto sessionWrapper = GenerateSessionWrapperImpl();
    EXPECT_EQ(sessionWrapper->session_, nullptr);
    sessionWrapper->InitTransferExtensionDataFunc();
    
    Rosen::SessionInfo sessionInfo;
    sessionWrapper->session_ = new Rosen::ExtensionSession(sessionInfo);
    sessionWrapper->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    EXPECT_NE(sessionWrapper->session_, nullptr);
    EXPECT_NE(sessionWrapper->taskExecutor_, nullptr);
    sessionWrapper->InitTransferExtensionDataFunc();

    auto sessionCallbacks = sessionWrapper->session_->GetExtensionSessionEventCallback();
    AAFwk::WantParams params;

    auto uiExtensionNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto uiExtensionNode = FrameNode::GetOrCreateFrameNode(
        UI_EXTENSION_COMPONENT_ETS_TAG, uiExtensionNodeId, []() { return AceType::MakeRefPtr<UIExtensionPattern>(); });
    auto pattern = uiExtensionNode->GetPattern<UIExtensionPattern>();
    auto weak = AceType::WeakClaim(AceType::RawPtr(pattern));
    sessionWrapper->hostPattern_ = weak;

    sessionWrapper->taskExecutor_ = nullptr;
    sessionWrapper->InitTransferExtensionDataFunc();
    sessionCallbacks->transferExtensionDataFunc_(params);
    EXPECT_NE(sessionCallbacks->transferExtensionDataFunc_, nullptr);
    
    sessionWrapper->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    sessionWrapper->InitTransferExtensionDataFunc();
    sessionCallbacks->transferExtensionDataFunc_(params);
    EXPECT_NE(sessionCallbacks->transferExtensionDataFunc_, nullptr);

    sessionWrapper->session_->persistentId_ = 0;
    sessionWrapper->InitTransferExtensionDataFunc();
    sessionCallbacks->transferExtensionDataFunc_(params);
    EXPECT_NE(sessionCallbacks->transferExtensionDataFunc_, nullptr);
}

/**
 * @tc.name: SessionWrapperImplNewTestNg006
 * @tc.desc: Test the method InitNotifyRemoteReadyFunc.
 * @tc.type: FUNC
 */
HWTEST_F(SessionWrapperImplNewTestNg, SessionWrapperImplNewTestNg006, TestSize.Level1)
{
    auto sessionWrapper = GenerateSessionWrapperImpl();
    EXPECT_EQ(sessionWrapper->session_, nullptr);
    sessionWrapper->InitNotifyRemoteReadyFunc();
    
    Rosen::SessionInfo sessionInfo;
    sessionWrapper->session_ = new Rosen::ExtensionSession(sessionInfo);
    sessionWrapper->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    EXPECT_NE(sessionWrapper->session_, nullptr);
    EXPECT_NE(sessionWrapper->taskExecutor_, nullptr);
    sessionWrapper->InitNotifyRemoteReadyFunc();

    auto sessionCallbacks = sessionWrapper->session_->GetExtensionSessionEventCallback();
    auto uiExtensionNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto uiExtensionNode = FrameNode::GetOrCreateFrameNode(
        UI_EXTENSION_COMPONENT_ETS_TAG, uiExtensionNodeId, []() { return AceType::MakeRefPtr<UIExtensionPattern>(); });
    auto pattern = uiExtensionNode->GetPattern<UIExtensionPattern>();
    auto weak = AceType::WeakClaim(AceType::RawPtr(pattern));
    sessionWrapper->hostPattern_ = weak;

    sessionWrapper->taskExecutor_ = nullptr;
    sessionWrapper->InitNotifyRemoteReadyFunc();
    sessionCallbacks->notifyRemoteReadyFunc_();
    EXPECT_NE(sessionCallbacks->notifyRemoteReadyFunc_, nullptr);
    
    sessionWrapper->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    sessionWrapper->InitNotifyRemoteReadyFunc();
    sessionCallbacks->notifyRemoteReadyFunc_();
    EXPECT_NE(sessionCallbacks->notifyRemoteReadyFunc_, nullptr);

    sessionWrapper->session_->persistentId_ = 0;
    sessionWrapper->InitNotifyRemoteReadyFunc();
    sessionCallbacks->notifyRemoteReadyFunc_();
    EXPECT_NE(sessionCallbacks->notifyRemoteReadyFunc_, nullptr);
}

/**
 * @tc.name: SessionWrapperImplNewTestNg007
 * @tc.desc: Test the method InitNotifySyncOnFunc.
 * @tc.type: FUNC
 */
HWTEST_F(SessionWrapperImplNewTestNg, SessionWrapperImplNewTestNg007, TestSize.Level1)
{
    auto sessionWrapper = GenerateSessionWrapperImpl();
    EXPECT_EQ(sessionWrapper->session_, nullptr);
    sessionWrapper->InitNotifySyncOnFunc();
    
    Rosen::SessionInfo sessionInfo;
    sessionWrapper->session_ = new Rosen::ExtensionSession(sessionInfo);
    sessionWrapper->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    EXPECT_NE(sessionWrapper->session_, nullptr);
    EXPECT_NE(sessionWrapper->taskExecutor_, nullptr);
    sessionWrapper->InitNotifySyncOnFunc();

    auto sessionCallbacks = sessionWrapper->session_->GetExtensionSessionEventCallback();
    auto uiExtensionNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto uiExtensionNode = FrameNode::GetOrCreateFrameNode(
        UI_EXTENSION_COMPONENT_ETS_TAG, uiExtensionNodeId, []() { return AceType::MakeRefPtr<UIExtensionPattern>(); });
    auto pattern = uiExtensionNode->GetPattern<UIExtensionPattern>();
    auto weak = AceType::WeakClaim(AceType::RawPtr(pattern));
    sessionWrapper->hostPattern_ = weak;

    sessionWrapper->taskExecutor_ = nullptr;
    sessionWrapper->InitNotifySyncOnFunc();
    sessionCallbacks->notifySyncOnFunc_();
    EXPECT_NE(sessionCallbacks->notifySyncOnFunc_, nullptr);
    
    sessionWrapper->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    sessionWrapper->InitNotifySyncOnFunc();
    sessionCallbacks->notifySyncOnFunc_();
    EXPECT_NE(sessionCallbacks->notifySyncOnFunc_, nullptr);

    sessionWrapper->session_->persistentId_ = 0;
    sessionWrapper->InitNotifySyncOnFunc();
    sessionCallbacks->notifySyncOnFunc_();
    EXPECT_NE(sessionCallbacks->notifySyncOnFunc_, nullptr);
}

/**
 * @tc.name: SessionWrapperImplNewTestNg008
 * @tc.desc: Test the method InitNotifyAsyncOnFunc.
 * @tc.type: FUNC
 */
HWTEST_F(SessionWrapperImplNewTestNg, SessionWrapperImplNewTestNg008, TestSize.Level1)
{
    auto sessionWrapper = GenerateSessionWrapperImpl();
    EXPECT_EQ(sessionWrapper->session_, nullptr);
    sessionWrapper->InitNotifyAsyncOnFunc();
    
    Rosen::SessionInfo sessionInfo;
    sessionWrapper->session_ = new Rosen::ExtensionSession(sessionInfo);
    sessionWrapper->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    EXPECT_NE(sessionWrapper->session_, nullptr);
    EXPECT_NE(sessionWrapper->taskExecutor_, nullptr);
    sessionWrapper->InitNotifyAsyncOnFunc();

    auto sessionCallbacks = sessionWrapper->session_->GetExtensionSessionEventCallback();
    auto uiExtensionNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto uiExtensionNode = FrameNode::GetOrCreateFrameNode(
        UI_EXTENSION_COMPONENT_ETS_TAG, uiExtensionNodeId, []() { return AceType::MakeRefPtr<UIExtensionPattern>(); });
    auto pattern = uiExtensionNode->GetPattern<UIExtensionPattern>();
    auto weak = AceType::WeakClaim(AceType::RawPtr(pattern));
    sessionWrapper->hostPattern_ = weak;

    sessionWrapper->taskExecutor_ = nullptr;
    sessionWrapper->InitNotifyAsyncOnFunc();
    sessionCallbacks->notifyAsyncOnFunc_();
    EXPECT_NE(sessionCallbacks->notifyAsyncOnFunc_, nullptr);
    
    sessionWrapper->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    sessionWrapper->InitNotifyAsyncOnFunc();
    sessionCallbacks->notifyAsyncOnFunc_();
    EXPECT_NE(sessionCallbacks->notifyAsyncOnFunc_, nullptr);

    sessionWrapper->session_->persistentId_ = 0;
    sessionWrapper->InitNotifyAsyncOnFunc();
    sessionCallbacks->notifyAsyncOnFunc_();
    EXPECT_NE(sessionCallbacks->notifyAsyncOnFunc_, nullptr);
}

/**
 * @tc.name: SessionWrapperImplNewTestNg009
 * @tc.desc: Test the method InitNotifyBindModalFunc.
 * @tc.type: FUNC
 */
HWTEST_F(SessionWrapperImplNewTestNg, SessionWrapperImplNewTestNg009, TestSize.Level1)
{
    auto sessionWrapper = GenerateSessionWrapperImpl();
    EXPECT_EQ(sessionWrapper->session_, nullptr);
    sessionWrapper->InitNotifyBindModalFunc();
    
    Rosen::SessionInfo sessionInfo;
    sessionWrapper->session_ = new Rosen::ExtensionSession(sessionInfo);
    sessionWrapper->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    EXPECT_NE(sessionWrapper->session_, nullptr);
    EXPECT_NE(sessionWrapper->taskExecutor_, nullptr);
    sessionWrapper->InitNotifyBindModalFunc();

    auto sessionCallbacks = sessionWrapper->session_->GetExtensionSessionEventCallback();
    auto uiExtensionNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto uiExtensionNode = FrameNode::GetOrCreateFrameNode(
        UI_EXTENSION_COMPONENT_ETS_TAG, uiExtensionNodeId, []() { return AceType::MakeRefPtr<UIExtensionPattern>(); });
    auto pattern = uiExtensionNode->GetPattern<UIExtensionPattern>();
    auto weak = AceType::WeakClaim(AceType::RawPtr(pattern));
    sessionWrapper->hostPattern_ = weak;

    sessionWrapper->taskExecutor_ = nullptr;
    sessionWrapper->InitNotifyBindModalFunc();
    sessionCallbacks->notifyBindModalFunc_();
    EXPECT_NE(sessionCallbacks->notifyBindModalFunc_, nullptr);
    
    sessionWrapper->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    sessionWrapper->InitNotifyBindModalFunc();
    sessionCallbacks->notifyBindModalFunc_();
    EXPECT_NE(sessionCallbacks->notifyBindModalFunc_, nullptr);

    sessionWrapper->session_->persistentId_ = 0;
    sessionWrapper->InitNotifyBindModalFunc();
    sessionCallbacks->notifyBindModalFunc_();
    EXPECT_NE(sessionCallbacks->notifyBindModalFunc_, nullptr);
}

/**
 * @tc.name: SessionWrapperImplNewTestNg010
 * @tc.desc: Test the method InitNotifyGetAvoidAreaByTypeFunc.
 * @tc.type: FUNC
 */
HWTEST_F(SessionWrapperImplNewTestNg, SessionWrapperImplNewTestNg010, TestSize.Level1)
{
    auto sessionWrapper = GenerateSessionWrapperImpl();
    EXPECT_EQ(sessionWrapper->session_, nullptr);
    sessionWrapper->InitNotifyGetAvoidAreaByTypeFunc();
    
    Rosen::SessionInfo sessionInfo;
    sessionWrapper->session_ = new Rosen::ExtensionSession(sessionInfo);
    EXPECT_NE(sessionWrapper->session_, nullptr);
    sessionWrapper->InitNotifyGetAvoidAreaByTypeFunc();

    auto sessionCallbacks = sessionWrapper->session_->GetExtensionSessionEventCallback();
    Rosen::AvoidAreaType type = Rosen::AvoidAreaType::TYPE_SYSTEM;
    int32_t apiVersion = 12;
    int32_t instanceId = 100;
    sessionWrapper->instanceId_ = 100;
    auto container = Platform::AceContainer::GetContainer(instanceId);
    Rosen::AvoidArea avoidArea = container->GetAvoidAreaByType(type, apiVersion);

    sessionWrapper->InitNotifyGetAvoidAreaByTypeFunc();
    auto ret = sessionCallbacks->notifyGetAvoidAreaByTypeFunc_(type, apiVersion);
    EXPECT_EQ(ret, avoidArea);
}

/**
 * @tc.name: SessionWrapperImplNewTestNg011
 * @tc.desc: Test the method InitNotifyExtensionEventFunc.
 * @tc.type: FUNC
 */
HWTEST_F(SessionWrapperImplNewTestNg, SessionWrapperImplNewTestNg011, TestSize.Level1)
{
    auto sessionWrapper = GenerateSessionWrapperImpl();
    EXPECT_EQ(sessionWrapper->session_, nullptr);
    sessionWrapper->InitNotifyExtensionEventFunc();
    
    Rosen::SessionInfo sessionInfo;
    sessionWrapper->session_ = new Rosen::ExtensionSession(sessionInfo);
    sessionWrapper->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    EXPECT_NE(sessionWrapper->session_, nullptr);
    EXPECT_NE(sessionWrapper->taskExecutor_, nullptr);
    sessionWrapper->InitNotifyExtensionEventFunc();

    uint32_t eventId = 100;
    auto sessionCallbacks = sessionWrapper->session_->GetExtensionSessionEventCallback();
    auto uiExtensionNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto uiExtensionNode = FrameNode::GetOrCreateFrameNode(
        UI_EXTENSION_COMPONENT_ETS_TAG, uiExtensionNodeId, []() { return AceType::MakeRefPtr<UIExtensionPattern>(); });
    auto pattern = uiExtensionNode->GetPattern<UIExtensionPattern>();
    auto weak = AceType::WeakClaim(AceType::RawPtr(pattern));
    sessionWrapper->hostPattern_ = weak;

    sessionWrapper->taskExecutor_ = nullptr;
    sessionWrapper->InitNotifyExtensionEventFunc();
    sessionCallbacks->notifyExtensionEventFunc_(eventId);
    EXPECT_NE(sessionCallbacks->notifyExtensionEventFunc_, nullptr);
    
    sessionWrapper->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    sessionWrapper->InitNotifyExtensionEventFunc();
    sessionCallbacks->notifyExtensionEventFunc_(eventId);
    EXPECT_NE(sessionCallbacks->notifyExtensionEventFunc_, nullptr);

    sessionWrapper->session_->persistentId_ = 0;
    sessionWrapper->InitNotifyExtensionEventFunc();
    sessionCallbacks->notifyExtensionEventFunc_(eventId);
    EXPECT_NE(sessionCallbacks->notifyExtensionEventFunc_, nullptr);
}

/**
 * @tc.name: SessionWrapperImplNewTestNg012
 * @tc.desc: Test the method InitGetStatusBarHeightFunc.
 * @tc.type: FUNC
 */
HWTEST_F(SessionWrapperImplNewTestNg, SessionWrapperImplNewTestNg012, TestSize.Level1)
{
    auto sessionWrapper = GenerateSessionWrapperImpl();
    EXPECT_EQ(sessionWrapper->session_, nullptr);
    sessionWrapper->InitGetStatusBarHeightFunc();
    
    Rosen::SessionInfo sessionInfo;
    sessionWrapper->session_ = new Rosen::ExtensionSession(sessionInfo);
    EXPECT_NE(sessionWrapper->session_, nullptr);
    sessionWrapper->InitGetStatusBarHeightFunc();

    auto sessionCallbacks = sessionWrapper->session_->GetExtensionSessionEventCallback();
    int32_t instanceId = 100;
    auto container = Platform::AceContainer::GetContainer(instanceId);
    auto getStatusBarHeight = container->GetStatusBarHeight();

    sessionWrapper->InitGetStatusBarHeightFunc();
    auto ret = sessionCallbacks->getStatusBarHeightFunc_();
    EXPECT_EQ(ret, getStatusBarHeight);
}

/**
 * @tc.name: SessionWrapperImplNewTestNg013
 * @tc.desc: Test the method UpdateInstanceId.
 * @tc.type: FUNC
 */
HWTEST_F(SessionWrapperImplNewTestNg, SessionWrapperImplNewTestNg013, TestSize.Level1)
{
    auto sessionWrapper = GenerateSessionWrapperImpl();
    int32_t instanceId = 100;
    sessionWrapper->instanceId_ = 100;

    sessionWrapper->UpdateInstanceId(instanceId);
    
    instanceId = 100;
    sessionWrapper->instanceId_ = 200;
    auto container = Container::GetContainer(instanceId);
    EXPECT_NE(container, nullptr);
    sessionWrapper->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    sessionWrapper->UpdateInstanceId(instanceId);
    EXPECT_EQ(instanceId, sessionWrapper->instanceId_);
}

/**
 * @tc.name: SessionWrapperImplNewTestNg014
 * @tc.desc: Test the method CreateSession.
 * @tc.type: FUNC
 */
HWTEST_F(SessionWrapperImplNewTestNg, SessionWrapperImplNewTestNg014, TestSize.Level1)
{
    auto sessionWrapper = GenerateSessionWrapperImpl();
    AAFwk::Want want;
    SessionConfig config;
    sessionWrapper->instanceId_ = 3;
    auto container = Platform::AceContainer::GetContainer(sessionWrapper->instanceId_);
    EXPECT_NE(container, nullptr);
    container->pipelineContext_ = AceType::MakeRefPtr<PipelineContext>();
    auto pipeline = container->GetPipelineContext();
    EXPECT_NE(pipeline, nullptr);
    uint32_t parentWindowType = 0;

    sessionWrapper->sessionType_ = SessionType::UI_EXTENSION_ABILITY;
    auto wantPtr = std::make_shared<Want>(want);
    container->SetUIExtensionAbilityHost(true);
    container->SetUIExtensionSubWindow(true);
    EXPECT_TRUE(container->IsUIExtensionAbilityHost());
    EXPECT_TRUE(container->IsUIExtensionSubWindow());
    sessionWrapper->CreateSession(want, config);
    EXPECT_EQ(parentWindowType, container->GetParentWindowType());
    
    sessionWrapper->sessionType_ = SessionType::EMBEDDED_UI_EXTENSION;
    sessionWrapper->CreateSession(want, config);

    sessionWrapper->instanceId_ = 2;
    sessionWrapper->sessionType_ = SessionType::UI_EXTENSION_ABILITY;
    sessionWrapper->CreateSession(want, config);
    EXPECT_EQ(parentWindowType, container->GetWindowType());
}

/**
 * @tc.name: SessionWrapperImplNewTestNg015
 * @tc.desc: Test the method DestroySession.
 * @tc.type: FUNC
 */
HWTEST_F(SessionWrapperImplNewTestNg, SessionWrapperImplNewTestNg015, TestSize.Level1)
{
    auto sessionWrapper = GenerateSessionWrapperImpl();
    EXPECT_EQ(sessionWrapper->session_, nullptr);
    Rosen::SessionInfo sessionInfo;
    sessionWrapper->session_ = new Rosen::ExtensionSession(sessionInfo);

    auto dataHandler = sessionWrapper->session_->GetExtensionDataHandler();
    EXPECT_NE(dataHandler, nullptr);
    sessionWrapper->DestroySession();
    EXPECT_EQ(sessionWrapper->customWant_, nullptr);
    EXPECT_EQ(sessionWrapper->session_, nullptr);
}

/**
 * @tc.name: SessionWrapperImplNewTestNg016
 * @tc.desc: Test the method GetInstanceId.
 * @tc.type: FUNC
 */
HWTEST_F(SessionWrapperImplNewTestNg, SessionWrapperImplNewTestNg016, TestSize.Level1)
{
    auto sessionWrapper = GenerateSessionWrapperImpl();

    auto uiExtensionNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto uiExtensionNode = FrameNode::GetOrCreateFrameNode(
        UI_EXTENSION_COMPONENT_ETS_TAG, uiExtensionNodeId, []() { return AceType::MakeRefPtr<UIExtensionPattern>(); });
    auto pattern = uiExtensionNode->GetPattern<UIExtensionPattern>();
    sessionWrapper->hostPattern_ = AceType::WeakClaim(AceType::RawPtr(pattern));
    auto patternUpgrade = sessionWrapper->hostPattern_.Upgrade();

    auto instanceId = pattern->GetInstanceIdFromHost();
    sessionWrapper->instanceId_ = 200;
    sessionWrapper->UpdateInstanceId(instanceId);
    auto ret = sessionWrapper->GetInstanceId();
    EXPECT_EQ(ret, instanceId);
}

/**
 * @tc.name: SessionWrapperImplNewTestNg017
 * @tc.desc: Test the method NotifyKeyEventSync.
 * @tc.type: FUNC
 */
HWTEST_F(SessionWrapperImplNewTestNg, SessionWrapperImplNewTestNg017, TestSize.Level1)
{
    auto sessionWrapper = GenerateSessionWrapperImpl();
    std::shared_ptr<OHOS::MMI::KeyEvent> keyEvent;
    bool isPreIme = false;
    Rosen::SessionInfo sessionInfo;
    sessionWrapper->session_ = new Rosen::ExtensionSession(sessionInfo);
    EXPECT_NE(sessionWrapper->session_, nullptr);
    auto uiExtensionNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto uiExtensionNode = FrameNode::GetOrCreateFrameNode(
        UI_EXTENSION_COMPONENT_ETS_TAG, uiExtensionNodeId, []() { return AceType::MakeRefPtr<UIExtensionPattern>(); });
    auto pattern = uiExtensionNode->GetPattern<UIExtensionPattern>();
    sessionWrapper->hostPattern_ = AceType::WeakClaim(AceType::RawPtr(pattern));
    auto patternUpgrade = sessionWrapper->hostPattern_.Upgrade();
    EXPECT_NE(patternUpgrade, nullptr);

    bool isTimeout = false;
    bool isConsumed = false;
    sessionWrapper->session_->TransferKeyEventForConsumed(keyEvent, isConsumed, isTimeout, isPreIme);
    bool ret = sessionWrapper->NotifyKeyEventSync(keyEvent, isPreIme);
    EXPECT_EQ(ret, isConsumed);
}

/**
 * @tc.name: SessionWrapperImplNewTestNg018
 * @tc.desc: Test the method NotifyPointerEventAsync.
 * @tc.type: FUNC
 */
HWTEST_F(SessionWrapperImplNewTestNg, SessionWrapperImplNewTestNg018, TestSize.Level1)
{
    auto sessionWrapper = GenerateSessionWrapperImpl();
    std::shared_ptr<OHOS::MMI::PointerEvent> pointerEvent = std::make_shared<OHOS::MMI::PointerEvent>(1);
    Rosen::SessionInfo sessionInfo;
    sessionWrapper->session_ = new Rosen::ExtensionSession(sessionInfo);
    EXPECT_NE(sessionWrapper->session_, nullptr);
    bool ret = sessionWrapper->NotifyPointerEventAsync(pointerEvent);
    EXPECT_EQ(ret, false);

    pointerEvent = nullptr;
    ret = sessionWrapper->NotifyPointerEventAsync(pointerEvent);
    EXPECT_EQ(ret, false);

    pointerEvent = std::make_shared<OHOS::MMI::PointerEvent>(1);
    sessionWrapper->session_ = nullptr;
    ret = sessionWrapper->NotifyPointerEventAsync(pointerEvent);
    EXPECT_EQ(ret, false);
}

/**
 * @tc.name: SessionWrapperImplNewTestNg019
 * @tc.desc: Test the method NotifyKeyEventAsync.
 * @tc.type: FUNC
 */
HWTEST_F(SessionWrapperImplNewTestNg, SessionWrapperImplNewTestNg019, TestSize.Level1)
{
    auto sessionWrapper = GenerateSessionWrapperImpl();
    std::shared_ptr<OHOS::MMI::KeyEvent> keyEvent;
    Rosen::SessionInfo sessionInfo;
    sessionWrapper->session_ = new Rosen::ExtensionSession(sessionInfo);
    EXPECT_NE(sessionWrapper->session_, nullptr);
    bool ret = sessionWrapper->NotifyKeyEventAsync(keyEvent);
    EXPECT_EQ(ret, false);

    keyEvent = std::make_shared<OHOS::MMI::KeyEvent>(2);
    ret = sessionWrapper->NotifyKeyEventAsync(keyEvent);
    EXPECT_EQ(ret, false);
}

/**
 * @tc.name: SessionWrapperImplNewTestNg020
 * @tc.desc: Test the method NotifyForeground.
 * @tc.type: FUNC
 */
HWTEST_F(SessionWrapperImplNewTestNg, SessionWrapperImplNewTestNg020, TestSize.Level1)
{
    auto sessionWrapper = GenerateSessionWrapperImpl();
    sessionWrapper->instanceId_ = 3;
    Rosen::SessionInfo sessionInfo;
    sessionWrapper->session_ = new Rosen::ExtensionSession(sessionInfo);
    auto container = Platform::AceContainer::GetContainer(sessionWrapper->instanceId_);
    auto pipeline = PipelineBase::GetCurrentContext();
    auto hostWindowId = pipeline->GetFocusWindowId();
    EXPECT_NE(sessionWrapper->session_, nullptr);
    EXPECT_NE(container, nullptr);
    EXPECT_NE(pipeline, nullptr);

    auto uiExtensionNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto uiExtensionNode = FrameNode::GetOrCreateFrameNode(
        UI_EXTENSION_COMPONENT_ETS_TAG, uiExtensionNodeId, []() { return AceType::MakeRefPtr<UIExtensionPattern>(); });
    auto pattern = uiExtensionNode->GetPattern<UIExtensionPattern>();
    auto weak = AceType::WeakClaim(AceType::RawPtr(pattern));
    sessionWrapper->hostPattern_ = weak;
    auto patternUpgrade = sessionWrapper->hostPattern_.Upgrade();
    EXPECT_NE(patternUpgrade, nullptr);
    patternUpgrade->viewportConfigChanged_ = true;

    sessionWrapper->NotifyForeground();
    EXPECT_TRUE(container->IsSceneBoardWindow());
}

/**
 * @tc.name: SessionWrapperImplNewTestNg021
 * @tc.desc: Test the method NotifyBackground.
 * @tc.type: FUNC
 */
HWTEST_F(SessionWrapperImplNewTestNg, SessionWrapperImplNewTestNg021, TestSize.Level1)
{
    auto sessionWrapper = GenerateSessionWrapperImpl();
    bool isHandleError = true;
    Rosen::SessionInfo sessionInfo;
    sessionWrapper->session_ = new Rosen::ExtensionSession(sessionInfo);
    sessionWrapper->NotifyBackground(isHandleError);
    
    isHandleError = false;
    sessionWrapper->NotifyBackground(isHandleError);
    EXPECT_NE(sessionWrapper->session_, nullptr);
}

/**
 * @tc.name: SessionWrapperImplNewTestNg022
 * @tc.desc: Test the method NotifyDestroy.
 * @tc.type: FUNC
 */
HWTEST_F(SessionWrapperImplNewTestNg, SessionWrapperImplNewTestNg022, TestSize.Level1)
{
    auto sessionWrapper = GenerateSessionWrapperImpl();
    bool isHandleError = true;
    Rosen::SessionInfo sessionInfo;
    sessionWrapper->session_ = new Rosen::ExtensionSession(sessionInfo);
    sessionWrapper->NotifyDestroy(isHandleError);
    
    isHandleError = false;
    sessionWrapper->NotifyDestroy(isHandleError);
    EXPECT_NE(sessionWrapper->session_, nullptr);
}

/**
 * @tc.name: SessionWrapperImplNewTestNg023
 * @tc.desc: Test the method OnConnect.
 * @tc.type: FUNC
 */
HWTEST_F(SessionWrapperImplNewTestNg, SessionWrapperImplNewTestNg023, TestSize.Level1)
{
    auto sessionWrapper = GenerateSessionWrapperImpl();
    
    auto uiExtensionNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto uiExtensionNode = FrameNode::GetOrCreateFrameNode(
        UI_EXTENSION_COMPONENT_ETS_TAG, uiExtensionNodeId, []() { return AceType::MakeRefPtr<UIExtensionPattern>(); });
    auto pattern = uiExtensionNode->GetPattern<UIExtensionPattern>();
    sessionWrapper->hostPattern_ = AceType::WeakClaim(AceType::RawPtr(pattern));
    auto patternUpgrade = sessionWrapper->hostPattern_.Upgrade();
    EXPECT_NE(patternUpgrade, nullptr);

    Rosen::SessionInfo sessionInfo;
    sessionWrapper->session_ = new Rosen::ExtensionSession(sessionInfo);
    int32_t callSessionId = sessionWrapper->GetSessionId();
    sessionWrapper->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    sessionWrapper->OnConnect();
    EXPECT_NE(patternUpgrade, nullptr);
}

/**
 * @tc.name: SessionWrapperImplNewTestNg024
 * @tc.desc: Test the method OnDisconnect.
 * @tc.type: FUNC
 */
HWTEST_F(SessionWrapperImplNewTestNg, SessionWrapperImplNewTestNg024, TestSize.Level1)
{
    auto sessionWrapper = GenerateSessionWrapperImpl();
    bool isAbnormal = false;
    
    auto uiExtensionNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto uiExtensionNode = FrameNode::GetOrCreateFrameNode(
        UI_EXTENSION_COMPONENT_ETS_TAG, uiExtensionNodeId, []() { return AceType::MakeRefPtr<UIExtensionPattern>(); });
    auto pattern = uiExtensionNode->GetPattern<UIExtensionPattern>();
    sessionWrapper->hostPattern_ = AceType::WeakClaim(AceType::RawPtr(pattern));
    auto patternUpgrade = sessionWrapper->hostPattern_.Upgrade();
    EXPECT_NE(patternUpgrade, nullptr);

    sessionWrapper->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    sessionWrapper->OnDisconnect(isAbnormal);
    sessionWrapper->sessionType_ = SessionType::INVALID_TYPE;
    sessionWrapper->OnDisconnect(isAbnormal);
    isAbnormal = true;
    sessionWrapper->OnDisconnect(isAbnormal);
    Rosen::SessionInfo sessionInfo;
    sessionWrapper->session_ = new Rosen::ExtensionSession(sessionInfo);
    sessionWrapper->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    sessionWrapper->OnDisconnect(isAbnormal);
    EXPECT_NE(patternUpgrade, nullptr);
}

/**
 * @tc.name: SessionWrapperImplNewTestNg025
 * @tc.desc: Test the method OnExtensionTimeout.
 * @tc.type: FUNC
 */
HWTEST_F(SessionWrapperImplNewTestNg, SessionWrapperImplNewTestNg025, TestSize.Level1)
{
    auto sessionWrapper = GenerateSessionWrapperImpl();
    int32_t errorCode = 1;
    
    auto uiExtensionNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto uiExtensionNode = FrameNode::GetOrCreateFrameNode(
        UI_EXTENSION_COMPONENT_ETS_TAG, uiExtensionNodeId, []() { return AceType::MakeRefPtr<UIExtensionPattern>(); });
    auto pattern = uiExtensionNode->GetPattern<UIExtensionPattern>();
    sessionWrapper->hostPattern_ = AceType::WeakClaim(AceType::RawPtr(pattern));
    auto patternUpgrade = sessionWrapper->hostPattern_.Upgrade();
    EXPECT_NE(patternUpgrade, nullptr);

    Rosen::SessionInfo sessionInfo;
    sessionWrapper->session_ = new Rosen::ExtensionSession(sessionInfo);
    int32_t callSessionId = sessionWrapper->GetSessionId();
    sessionWrapper->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    sessionWrapper->OnExtensionTimeout(errorCode);
    EXPECT_NE(patternUpgrade, nullptr);
}

/**
 * @tc.name: SessionWrapperImplNewTestNg026
 * @tc.desc: Test the method OnExtensionDetachToDisplay.
 * @tc.type: FUNC
 */
HWTEST_F(SessionWrapperImplNewTestNg, SessionWrapperImplNewTestNg026, TestSize.Level1)
{
    auto sessionWrapper = GenerateSessionWrapperImpl();
    
    auto uiExtensionNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto uiExtensionNode = FrameNode::GetOrCreateFrameNode(
        UI_EXTENSION_COMPONENT_ETS_TAG, uiExtensionNodeId, []() { return AceType::MakeRefPtr<UIExtensionPattern>(); });
    auto pattern = uiExtensionNode->GetPattern<UIExtensionPattern>();
    sessionWrapper->hostPattern_ = AceType::WeakClaim(AceType::RawPtr(pattern));
    auto patternUpgrade = sessionWrapper->hostPattern_.Upgrade();
    EXPECT_NE(patternUpgrade, nullptr);

    sessionWrapper->OnExtensionDetachToDisplay();

    Rosen::SessionInfo sessionInfo;
    sessionWrapper->session_ = new Rosen::ExtensionSession(sessionInfo);
    int32_t callSessionId = sessionWrapper->GetSessionId();
    sessionWrapper->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    sessionWrapper->OnExtensionDetachToDisplay();
    EXPECT_NE(patternUpgrade, nullptr);
}

/**
 * @tc.name: SessionWrapperImplNewTestNg027
 * @tc.desc: Test the method NotifyOccupiedAreaChangeInfo.
 * @tc.type: FUNC
 */
HWTEST_F(SessionWrapperImplNewTestNg, SessionWrapperImplNewTestNg027, TestSize.Level1)
{
    auto sessionWrapper = GenerateSessionWrapperImpl();
    auto info = sptr<Rosen::OccupiedAreaChangeInfo>(new Rosen::OccupiedAreaChangeInfo());
    bool needWaitLayout = true;

    Rosen::SessionInfo sessionInfo;
    sessionWrapper->session_ = new Rosen::ExtensionSession(sessionInfo);
    sessionWrapper->isNotifyOccupiedAreaChange_ = true;
    sessionWrapper->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();

    auto pipeline = PipelineBase::GetCurrentContext();
    EXPECT_NE(pipeline, nullptr);
    auto curWindow = pipeline->GetCurrentWindowRect();
    EXPECT_NE(sessionWrapper->displayAreaWindow_, curWindow);

    auto uiExtensionNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto uiExtensionNode = FrameNode::GetOrCreateFrameNode(
        UI_EXTENSION_COMPONENT_ETS_TAG, uiExtensionNodeId, []() { return AceType::MakeRefPtr<UIExtensionPattern>(); });
    auto pattern = uiExtensionNode->GetPattern<UIExtensionPattern>();
    sessionWrapper->hostPattern_ = AceType::WeakClaim(AceType::RawPtr(pattern));
    auto patternUpgrade = sessionWrapper->hostPattern_.Upgrade();
    EXPECT_NE(patternUpgrade, nullptr);

    sessionWrapper->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto ret = sessionWrapper->NotifyOccupiedAreaChangeInfo(info, needWaitLayout);
    EXPECT_NE(patternUpgrade, nullptr);
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: SessionWrapperImplNewTestNg028
 * @tc.desc: Test the method InnerNotifyOccupiedAreaChangeInfo.
 * @tc.type: FUNC
 */
HWTEST_F(SessionWrapperImplNewTestNg, SessionWrapperImplNewTestNg028, TestSize.Level1)
{
    auto sessionWrapper = GenerateSessionWrapperImpl();
    auto info = sptr<Rosen::OccupiedAreaChangeInfo>(new Rosen::OccupiedAreaChangeInfo());
    bool isWaitTask = true;
    int64_t occupiedAreaTime = 1;
    sessionWrapper->lastOccupiedAreaTime_ = 10;
    auto ret = sessionWrapper->InnerNotifyOccupiedAreaChangeInfo(info, isWaitTask, occupiedAreaTime);
    EXPECT_FALSE(ret);

    isWaitTask = false;
    occupiedAreaTime = 20;
    Rosen::SessionInfo sessionInfo;
    sessionWrapper->session_ = new Rosen::ExtensionSession(sessionInfo);
    sessionWrapper->isNotifyOccupiedAreaChange_ = true;
    auto pipeline = PipelineBase::GetCurrentContext();
    auto container = Platform::AceContainer::GetContainer(sessionWrapper->GetInstanceId());
    info->rect_.height_ = 10;
    int32_t keyboardHeight = static_cast<int32_t>(info->rect_.height_);
    auto displayArea = sessionWrapper->GetDisplayAreaWithWindowScene();

    ret = sessionWrapper->InnerNotifyOccupiedAreaChangeInfo(info, isWaitTask, occupiedAreaTime);
    EXPECT_EQ(sessionWrapper->lastOccupiedAreaTime_, occupiedAreaTime);
}

/**
 * @tc.name: SessionWrapperImplNewTestNg029
 * @tc.desc: Test the method SendDataSync.
 * @tc.type: FUNC
 */
HWTEST_F(SessionWrapperImplNewTestNg, SessionWrapperImplNewTestNg029, TestSize.Level1)
{
    auto sessionWrapper = GenerateSessionWrapperImpl();
    AAFwk::WantParams wantParams;
    AAFwk::WantParams reWantParams;
    Rosen::WSErrorCode transferCode = Rosen::WSErrorCode::WS_ERROR_TRANSFER_DATA_FAILED;
    Rosen::SessionInfo sessionInfo;
    sessionWrapper->session_ = new Rosen::ExtensionSession(sessionInfo);

    auto ret = sessionWrapper->SendDataSync(wantParams, reWantParams);
    EXPECT_EQ(transferCode, sessionWrapper->session_->TransferComponentDataSync(wantParams, reWantParams));
    EXPECT_EQ(ret, static_cast<int32_t>(transferCode));
}

/**
 * @tc.name: SessionWrapperImplNewTestNg030
 * @tc.desc: Test the method SendBusinessDataSyncReply.
 * @tc.type: FUNC
 */
HWTEST_F(SessionWrapperImplNewTestNg, SessionWrapperImplNewTestNg030, TestSize.Level1)
{
    auto sessionWrapper = GenerateSessionWrapperImpl();
    UIContentBusinessCode code;
    AAFwk::Want data;
    AAFwk::Want reply;

    code = UIContentBusinessCode::UNDEFINED;
    bool ret = sessionWrapper->SendBusinessDataSyncReply(code, data, reply, RSSubsystemId::WM_UIEXT);
    EXPECT_FALSE(ret);
    
    code = UIContentBusinessCode::EVENT_PROXY;
    Rosen::SessionInfo sessionInfo;
    sessionWrapper->session_ = new Rosen::ExtensionSession(sessionInfo);
    auto dataHandler = sessionWrapper->session_->GetExtensionDataHandler();
    auto result = dataHandler->SendDataSync(static_cast<OHOS::Rosen::SubSystemId>(RSSubsystemId::WM_UIEXT),
        static_cast<uint32_t>(code), data, reply);
    ret = sessionWrapper->SendBusinessDataSyncReply(code, data, reply, RSSubsystemId::WM_UIEXT);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: SessionWrapperImplNewTestNg031
 * @tc.desc: Test the method SendBusinessData.
 * @tc.type: FUNC
 */
HWTEST_F(SessionWrapperImplNewTestNg, SessionWrapperImplNewTestNg031, TestSize.Level1)
{
    auto sessionWrapper = GenerateSessionWrapperImpl();
    UIContentBusinessCode code;
    AAFwk::Want data;
    BusinessDataSendType type;
    RSSubsystemId subSystemId;

    code = UIContentBusinessCode::UNDEFINED;
    type = BusinessDataSendType::ASYNC;
    subSystemId = RSSubsystemId::WM_UIEXT;
    bool ret = sessionWrapper->SendBusinessData(code, data, type, subSystemId);
    EXPECT_FALSE(ret);

    code = UIContentBusinessCode::EVENT_PROXY;
    Rosen::SessionInfo sessionInfo;
    sessionWrapper->session_ = new Rosen::ExtensionSession(sessionInfo);
    auto dataHandler = sessionWrapper->session_->GetExtensionDataHandler();
    ret = sessionWrapper->SendBusinessData(code, data, type, subSystemId);
    EXPECT_TRUE(ret);

    type = BusinessDataSendType::SYNC;
    auto result = dataHandler->SendDataSync(static_cast<OHOS::Rosen::SubSystemId>(subSystemId),
        static_cast<uint32_t>(code), data);
    ret = sessionWrapper->SendBusinessData(code, data, type, subSystemId);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: SessionWrapperImplNewTestNg032
 * @tc.desc: Test the method PostBusinessDataConsumeAsync.
 * @tc.type: FUNC
 */
HWTEST_F(SessionWrapperImplNewTestNg, SessionWrapperImplNewTestNg032, TestSize.Level1)
{
    auto sessionWrapper = GenerateSessionWrapperImpl();
    uint32_t customId = 1;
    AAFwk::Want data;

    auto uiExtensionNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto uiExtensionNode = FrameNode::GetOrCreateFrameNode(
        UI_EXTENSION_COMPONENT_ETS_TAG, uiExtensionNodeId, []() { return AceType::MakeRefPtr<UIExtensionPattern>(); });
    auto pattern = uiExtensionNode->GetPattern<UIExtensionPattern>();
    sessionWrapper->hostPattern_ = AceType::WeakClaim(AceType::RawPtr(pattern));
    auto patternUpgrade = sessionWrapper->hostPattern_.Upgrade();
    EXPECT_NE(patternUpgrade, nullptr);

    Rosen::SessionInfo sessionInfo;
    sessionWrapper->session_ = new Rosen::ExtensionSession(sessionInfo);
    int32_t callSessionId = sessionWrapper->GetSessionId();
    sessionWrapper->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();

    sessionWrapper->PostBusinessDataConsumeAsync(customId, data);
}

/**
 * @tc.name: SessionWrapperImplNewTestNg033
 * @tc.desc: Test the method PostBusinessDataConsumeSyncReply.
 * @tc.type: FUNC
 */
HWTEST_F(SessionWrapperImplNewTestNg, SessionWrapperImplNewTestNg033, TestSize.Level1)
{
    auto sessionWrapper = GenerateSessionWrapperImpl();
    uint32_t customId = 1;
    AAFwk::Want data;
    std::optional<AAFwk::Want> reply;

    auto uiExtensionNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto uiExtensionNode = FrameNode::GetOrCreateFrameNode(
        UI_EXTENSION_COMPONENT_ETS_TAG, uiExtensionNodeId, []() { return AceType::MakeRefPtr<UIExtensionPattern>(); });
    auto pattern = uiExtensionNode->GetPattern<UIExtensionPattern>();
    sessionWrapper->hostPattern_ = AceType::WeakClaim(AceType::RawPtr(pattern));
    auto patternUpgrade = sessionWrapper->hostPattern_.Upgrade();
    EXPECT_NE(patternUpgrade, nullptr);

    Rosen::SessionInfo sessionInfo;
    sessionWrapper->session_ = new Rosen::ExtensionSession(sessionInfo);
    int32_t callSessionId = sessionWrapper->GetSessionId();
    sessionWrapper->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    sessionWrapper->PostBusinessDataConsumeSyncReply(customId, data, reply);
    EXPECT_NE(patternUpgrade, nullptr);
}

/**
 * @tc.name: SessionWrapperImplNewTestNg034
 * @tc.desc: Test the method InitAllCallback.
 * @tc.type: FUNC
 */
HWTEST_F(SessionWrapperImplNewTestNg, SessionWrapperImplNewTestNg034, TestSize.Level1)
{
    auto sessionWrapper = GenerateSessionWrapperImpl();
    Rosen::SessionInfo sessionInfo;
    sessionWrapper->session_ = new Rosen::ExtensionSession(sessionInfo);

    sessionWrapper->taskExecutor_ = nullptr;
    sessionWrapper->InitAllCallback();

    sessionWrapper->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto sessionCallbacks = sessionWrapper->session_->GetExtensionSessionEventCallback();
    sessionWrapper->InitAllCallback();
    EXPECT_NE(sessionCallbacks, nullptr);
}

/**
 * @tc.name: SessionWrapperImplNewTestNg035
 * @tc.desc: Test the method OnAccessibilityEvent.
 * @tc.type: FUNC
 */
HWTEST_F(SessionWrapperImplNewTestNg, SessionWrapperImplNewTestNg035, TestSize.Level1)
{
    auto sessionWrapper = GenerateSessionWrapperImpl();
    Accessibility::AccessibilityEventInfo info;
    int64_t offset = 1;
    int32_t callSessionId = sessionWrapper->GetSessionId();
    sessionWrapper->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();

    auto uiExtensionNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto uiExtensionNode = FrameNode::GetOrCreateFrameNode(
        UI_EXTENSION_COMPONENT_ETS_TAG, uiExtensionNodeId, []() { return AceType::MakeRefPtr<UIExtensionPattern>(); });
    auto pattern = uiExtensionNode->GetPattern<UIExtensionPattern>();
    sessionWrapper->hostPattern_ = AceType::WeakClaim(AceType::RawPtr(pattern));
    auto patternUpgrade = sessionWrapper->hostPattern_.Upgrade();

    sessionWrapper->OnAccessibilityEvent(info, offset);
    EXPECT_EQ(callSessionId, patternUpgrade->GetSessionId());
}

/**
 * @tc.name: SessionWrapperImplNewTestNg036
 * @tc.desc: Test the method NotifyDisplayArea.
 * @tc.type: FUNC
 */
HWTEST_F(SessionWrapperImplNewTestNg, SessionWrapperImplNewTestNg036, TestSize.Level1)
{
    auto sessionWrapper = GenerateSessionWrapperImpl();
    RectF displayArea(100.0, 100.0, 100.0, 100.0);

    Rosen::SessionInfo sessionInfo;
    sessionWrapper->session_ = new Rosen::ExtensionSession(sessionInfo);
    auto pipeline = PipelineBase::GetCurrentContext();

    sessionWrapper->session_->reason_ = Rosen::SizeChangeReason::UNDEFINED;
    sessionWrapper->NotifyDisplayArea(displayArea);

    std::shared_ptr<Rosen::RSTransaction> transaction;
    auto transactionController = Rosen::RSSyncTransactionController::GetInstance();
    sessionWrapper->session_->reason_ = Rosen::SizeChangeReason::ROTATION;
    sessionWrapper->NotifyDisplayArea(displayArea);
    EXPECT_EQ(transaction, transactionController->GetRSTransaction());

    std::shared_ptr<Rosen::RSTransaction> sharedTransaction = std::make_shared<Rosen::RSTransaction>();
    sessionWrapper->transaction_ = sharedTransaction;
    sessionWrapper->NotifyDisplayArea(displayArea);
    EXPECT_EQ(transaction, sessionWrapper->transaction_.lock());

    transactionController->Destroy();
    sessionWrapper->NotifyDisplayArea(displayArea);
}

/**
 * @tc.name: SessionWrapperImplNewTestNg037
 * @tc.desc: Test the method SendDataAsync.
 * @tc.type: FUNC
 */
HWTEST_F(SessionWrapperImplNewTestNg, SessionWrapperImplNewTestNg037, TestSize.Level1)
{
    auto sessionWrapper = GenerateSessionWrapperImpl();
    AAFwk::WantParams params;

    Rosen::SessionInfo sessionInfo;
    sessionWrapper->session_ = nullptr;
    sessionWrapper->SendDataAsync(params);

    sessionWrapper->session_ = new Rosen::ExtensionSession(sessionInfo);
    sessionWrapper->SendDataAsync(params);
    EXPECT_NE(sessionWrapper->session_, nullptr);
}

/**
 * @tc.name: SessionWrapperImplNewTestNg038
 * @tc.desc: Test the method RegisterDataConsumer.
 * @tc.type: FUNC
 */
HWTEST_F(SessionWrapperImplNewTestNg, SessionWrapperImplNewTestNg038, TestSize.Level1)
{
    auto sessionWrapper = GenerateSessionWrapperImpl();
    Rosen::SessionInfo sessionInfo;
    sessionWrapper->session_ = new Rosen::ExtensionSession(sessionInfo);
    auto dataHandler = sessionWrapper->session_->GetExtensionDataHandler();

    bool ret = sessionWrapper->RegisterDataConsumer();
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: SessionWrapperImplNewTestNg039
 * @tc.desc: Test the method DispatchExtensionDataToHostWindow.
 * @tc.type: FUNC
 */
HWTEST_F(SessionWrapperImplNewTestNg, SessionWrapperImplNewTestNg039, TestSize.Level1)
{
    auto sessionWrapper = GenerateSessionWrapperImpl();
    uint32_t customId = 1;
    AAFwk::Want data;
    std::optional<AAFwk::Want> reply;

    auto uiExtensionNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto uiExtensionNode = FrameNode::GetOrCreateFrameNode(
        UI_EXTENSION_COMPONENT_ETS_TAG, uiExtensionNodeId, []() { return AceType::MakeRefPtr<UIExtensionPattern>(); });
    auto pattern = uiExtensionNode->GetPattern<UIExtensionPattern>();
    sessionWrapper->hostPattern_ = AceType::WeakClaim(AceType::RawPtr(pattern));
    auto patternUpgrade = sessionWrapper->hostPattern_.Upgrade();
    EXPECT_NE(patternUpgrade, nullptr);

    Rosen::SessionInfo sessionInfo;
    sessionWrapper->session_ = new Rosen::ExtensionSession(sessionInfo);
    int32_t callSessionId = sessionWrapper->GetSessionId();
    sessionWrapper->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    sessionWrapper->DispatchExtensionDataToHostWindow(customId, data);
    EXPECT_NE(patternUpgrade, nullptr);
    customId = static_cast<uint32_t>(UIContentBusinessCode::WINDOW_CODE_BEGIN);
    sessionWrapper->DispatchExtensionDataToHostWindow(customId, data);
    EXPECT_NE(patternUpgrade, nullptr);
}
} // namespace OHOS::Ace::NG