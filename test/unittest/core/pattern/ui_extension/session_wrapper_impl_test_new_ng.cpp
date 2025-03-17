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
} // namespace OHOS::Ace::NG