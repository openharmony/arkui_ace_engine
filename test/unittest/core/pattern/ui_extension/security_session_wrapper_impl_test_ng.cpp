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
#include "session/host/include/extension_session.h"
#include "session/host/include/session.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_rosen_render_context.h"
#include "test/unittest/core/pattern/ui_extension/mock/mock_data_handler.h"
#include "test/unittest/core/pattern/ui_extension/mock/mock_window_scene_helper.h"
#include "ui/rs_surface_node.h"

#include "adapter/ohos/entrance/ace_container.h"
#include "adapter/ohos/entrance/mmi_event_convertor.h"
#include "adapter/ohos/osal/want_wrap_ohos.h"
#include "base/error/error_code.h"
#include "base/geometry/offset.h"
#include "base/utils/utils.h"
#include "core/common/window.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/ui_extension/isolated_component/isolated_pattern.h"
#include "core/components_ng/pattern/ui_extension/security_ui_extension_component/security_session_wrapper_impl.h"
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
#include "core/components_ng/render/adapter/rosen_window.h"
#include "core/event/ace_events.h"
#include "core/event/key_event.h"
#include "core/event/mouse_event.h"
#include "core/event/pointer_event.h"
#include "core/event/touch_event.h"
#include "frameworks/core/components_ng/pattern/ui_extension/platform_event_proxy.h"
#include "transaction/rs_transaction.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::string UI_EXTENSION_COMPONENT_ETS_TAG = "UIExtensionComponent";
} // namespace

class SecuritySessionWrapperImplTestNg : public testing::Test {
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
    RefPtr<SecuritySessionWrapperImpl> GenerateSecuritySessionWrapperImpl();
    WeakPtr<SecurityUIExtensionPattern> CreateSecurityUEC();
};

void SecuritySessionWrapperImplTestNg::SetUp() {}

void SecuritySessionWrapperImplTestNg::TearDown() {}

RefPtr<SecuritySessionWrapperImpl> SecuritySessionWrapperImplTestNg::GenerateSecuritySessionWrapperImpl()
{
    auto uiExtensionNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto uiExtensionNode = FrameNode::GetOrCreateFrameNode(UI_EXTENSION_COMPONENT_ETS_TAG, uiExtensionNodeId,
        []() { return AceType::MakeRefPtr<SecurityUIExtensionPattern>(); });
    auto pattern = uiExtensionNode->GetPattern<SecurityUIExtensionPattern>();
    auto sessionWrapper = AceType::MakeRefPtr<SecuritySessionWrapperImpl>(
        AceType::WeakClaim(AceType::RawPtr(pattern)), pattern->instanceId_, false, SessionType::UI_EXTENSION_ABILITY);
    sessionWrapper->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    return sessionWrapper;
}

WeakPtr<SecurityUIExtensionPattern> SecuritySessionWrapperImplTestNg::CreateSecurityUEC()
{
    // construct config of SecurityUEC
    OHOS::AAFwk::Want want;

    auto placeholderId = ElementRegister::GetInstance()->MakeUniqueId();
    auto placeholderNode = FrameNode::GetOrCreateFrameNode(
        "placeholderNode", placeholderId, []() { return AceType::MakeRefPtr<Pattern>(); });

    NG::UIExtensionConfig config;
    config.wantWrap = AceType::MakeRefPtr<WantWrapOhos>(want);
    config.placeholderNode = placeholderNode;
    config.sessionType = SessionType::SECURITY_UI_EXTENSION_ABILITY;
    config.transferringCaller = true;
    config.densityDpi = true;

    // create SecurityUEC
    UIExtensionModelNG uecNG;
    uecNG.Create(config);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_RETURN(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::UI_EXTENSION_COMPONENT_ETS_TAG);

    // set callbacks
    auto onReceive = [](const AAFwk::WantParams& wantParams) {};
    auto onError = [](int32_t code, const std::string& name, const std::string& message) {};
    auto onRemoteReady = [](const RefPtr<SecurityUIExtensionProxy>&) {};
    auto onTerminated = [](int32_t code, const RefPtr<WantWrap>&) {};

    uecNG.SetOnReceive(onReceive, SessionType::SECURITY_UI_EXTENSION_ABILITY);
    uecNG.SetOnError(onError, SessionType::SECURITY_UI_EXTENSION_ABILITY);
    uecNG.SetSecurityOnRemoteReady(onRemoteReady);
    uecNG.SetOnTerminated(onTerminated, SessionType::SECURITY_UI_EXTENSION_ABILITY);

    // get pattern
    auto pattern = frameNode->GetPattern<SecurityUIExtensionPattern>();
    auto weak = AceType::WeakClaim(AceType::RawPtr(pattern));
    return weak;
}

/**
 * @tc.name: SecuritySessionWrapperImplTestNg001
 * @tc.desc: Test the method InitAllCallback
 * @tc.type: FUNC
 */
HWTEST_F(SecuritySessionWrapperImplTestNg, SecuritySessionWrapperImplTestNg001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a SecuritySessionWrapperImpl
     */
    auto sessionWrapper = GenerateSecuritySessionWrapperImpl();
    ASSERT_EQ(sessionWrapper->session_, nullptr);
    sessionWrapper->InitAllCallback();

    Rosen::SessionInfo sessionInfo;
    sessionWrapper->session_ = new Rosen::ExtensionSession(sessionInfo);
    ASSERT_NE(sessionWrapper->session_, nullptr);
    ASSERT_NE(sessionWrapper->taskExecutor_, nullptr);
    sessionWrapper->hostPattern_ = nullptr;
    sessionWrapper->InitAllCallback();

    /**
     * @tc.steps: step2. test Callback for errcode != OHOS::Rosen::WSError::WS_OK
     */
    OHOS::Rosen::WSError errcode = OHOS::Rosen::WSError::WS_DO_NOTHING;
    AAFwk::Want want;
    AAFwk::WantParams params;
    auto sessionCallbacks = sessionWrapper->session_->GetExtensionSessionEventCallback();
    sessionWrapper->foregroundCallback_(errcode);
    sessionWrapper->backgroundCallback_(errcode);
    sessionWrapper->destructionCallback_(errcode);
    sessionCallbacks->transferAbilityResultFunc_(0, want);
    sessionCallbacks->transferExtensionDataFunc_(params);
    sessionCallbacks->notifyRemoteReadyFunc_();
    sessionCallbacks->notifySyncOnFunc_();
    sessionCallbacks->notifyAsyncOnFunc_();
    sessionCallbacks->notifyBindModalFunc_();
    sessionCallbacks->notifyGetAvoidAreaByTypeFunc_(Rosen::AvoidAreaType::TYPE_SYSTEM, 0);
    sessionCallbacks->notifyExtensionEventFunc_(0);

    errcode = OHOS::Rosen::WSError::WS_OK;
    sessionWrapper->foregroundCallback_(errcode);
    sessionWrapper->backgroundCallback_(errcode);
    sessionWrapper->destructionCallback_(errcode);
    sessionCallbacks->transferAbilityResultFunc_(0, want);
    sessionCallbacks->transferExtensionDataFunc_(params);
    sessionCallbacks->notifyRemoteReadyFunc_();
    sessionCallbacks->notifySyncOnFunc_();
    sessionCallbacks->notifyAsyncOnFunc_();
    sessionCallbacks->notifyBindModalFunc_();
    sessionCallbacks->notifyGetAvoidAreaByTypeFunc_(Rosen::AvoidAreaType::TYPE_SYSTEM, 0);
    sessionCallbacks->notifyExtensionEventFunc_(0);

    sessionWrapper->taskExecutor_ = nullptr;
    sessionWrapper->InitAllCallback();
#endif
}

/**
 * @tc.name: SecuritySessionWrapperImplTestNg002
 * @tc.desc: Test the method InitAllCallback
 * @tc.type: FUNC
 */
HWTEST_F(SecuritySessionWrapperImplTestNg, SecuritySessionWrapperImplTestNg002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a SecuritySessionWrapperImpl
     */
    auto sessionWrapper = GenerateSecuritySessionWrapperImpl();
    Rosen::SessionInfo sessionInfo;
    sessionWrapper->session_ = new Rosen::ExtensionSession(sessionInfo);
    sessionWrapper->session_->persistentId_ = 1;
    ASSERT_NE(sessionWrapper->taskExecutor_, nullptr);

    sessionWrapper->hostPattern_ = CreateSecurityUEC();
    ASSERT_NE(sessionWrapper->hostPattern_.Upgrade(), nullptr);
    ASSERT_NE(sessionWrapper->hostPattern_.Upgrade()->GetSessionId(), sessionWrapper->GetSessionId());
    sessionWrapper->InitAllCallback();

    /**
     * @tc.steps: step2. test Callback for callSessionId != pattern->GetSessionId()
     */
    OHOS::Rosen::WSError errcode = OHOS::Rosen::WSError::WS_OK;
    AAFwk::Want want;
    AAFwk::WantParams params;
    auto sessionCallbacks = sessionWrapper->session_->GetExtensionSessionEventCallback();
    sessionWrapper->foregroundCallback_(errcode);
    sessionWrapper->backgroundCallback_(errcode);
    sessionWrapper->destructionCallback_(errcode);
    sessionCallbacks->transferAbilityResultFunc_(0, want);
    sessionCallbacks->transferExtensionDataFunc_(params);
    sessionCallbacks->notifyRemoteReadyFunc_();
    sessionCallbacks->notifySyncOnFunc_();
    sessionCallbacks->notifyAsyncOnFunc_();
    sessionCallbacks->notifyBindModalFunc_();
    sessionCallbacks->notifyGetAvoidAreaByTypeFunc_(Rosen::AvoidAreaType::TYPE_SYSTEM, 0);
    sessionCallbacks->notifyExtensionEventFunc_(0);

    errcode = OHOS::Rosen::WSError::WS_OK;
    sessionWrapper->foregroundCallback_(errcode);
    sessionWrapper->backgroundCallback_(errcode);
    sessionWrapper->destructionCallback_(errcode);
    sessionCallbacks->transferAbilityResultFunc_(0, want);
    sessionCallbacks->transferExtensionDataFunc_(params);
    sessionCallbacks->notifyRemoteReadyFunc_();
    sessionCallbacks->notifySyncOnFunc_();
    sessionCallbacks->notifyAsyncOnFunc_();
    sessionCallbacks->notifyBindModalFunc_();
    sessionCallbacks->notifyGetAvoidAreaByTypeFunc_(Rosen::AvoidAreaType::TYPE_SYSTEM, 0);
    sessionCallbacks->notifyExtensionEventFunc_(0);
#endif
}

/**
 * @tc.name: SecuritySessionWrapperImplTestNg003
 * @tc.desc: Test the method InitAllCallback
 * @tc.type: FUNC
 */
HWTEST_F(SecuritySessionWrapperImplTestNg, SecuritySessionWrapperImplTestNg003, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a SecuritySessionWrapperImpl
     */
    auto sessionWrapper = GenerateSecuritySessionWrapperImpl();
    Rosen::SessionInfo sessionInfo;
    sessionWrapper->session_ = new Rosen::ExtensionSession(sessionInfo);
    ASSERT_NE(sessionWrapper->taskExecutor_, nullptr);

    sessionWrapper->hostPattern_ = CreateSecurityUEC();
    ASSERT_NE(sessionWrapper->hostPattern_.Upgrade(), nullptr);
    ASSERT_EQ(sessionWrapper->hostPattern_.Upgrade()->GetSessionId(), sessionWrapper->GetSessionId());
    sessionWrapper->InitAllCallback();

    /**
     * @tc.steps: step2. test Callback for callSessionId == pattern->GetSessionId()
     */
    OHOS::Rosen::WSError errcode = OHOS::Rosen::WSError::WS_OK;
    AAFwk::Want want;
    AAFwk::WantParams params;
    auto sessionCallbacks = sessionWrapper->session_->GetExtensionSessionEventCallback();
    sessionWrapper->foregroundCallback_(errcode);
    sessionWrapper->backgroundCallback_(errcode);
    sessionWrapper->destructionCallback_(errcode);
    sessionCallbacks->transferAbilityResultFunc_(0, want);
    sessionCallbacks->transferExtensionDataFunc_(params);
    sessionCallbacks->notifyRemoteReadyFunc_();
    sessionCallbacks->notifySyncOnFunc_();
    sessionCallbacks->notifyAsyncOnFunc_();
    sessionCallbacks->notifyBindModalFunc_();
    sessionCallbacks->notifyGetAvoidAreaByTypeFunc_(Rosen::AvoidAreaType::TYPE_SYSTEM, 0);
    sessionCallbacks->notifyExtensionEventFunc_(0);

    errcode = OHOS::Rosen::WSError::WS_OK;
    sessionWrapper->foregroundCallback_(errcode);
    sessionWrapper->backgroundCallback_(errcode);
    sessionWrapper->destructionCallback_(errcode);
    sessionCallbacks->transferAbilityResultFunc_(0, want);
    sessionCallbacks->transferExtensionDataFunc_(params);
    sessionCallbacks->notifyRemoteReadyFunc_();
    sessionCallbacks->notifySyncOnFunc_();
    sessionCallbacks->notifyAsyncOnFunc_();
    sessionCallbacks->notifyBindModalFunc_();
    sessionCallbacks->notifyGetAvoidAreaByTypeFunc_(Rosen::AvoidAreaType::TYPE_SYSTEM, 0);
    sessionCallbacks->notifyExtensionEventFunc_(0);
#endif
}

/**
 * @tc.name: SecuritySessionWrapperImplTestNg004
 * @tc.desc: Test the method CreateSession and DestroySession
 * @tc.type: FUNC
 */
HWTEST_F(SecuritySessionWrapperImplTestNg, SecuritySessionWrapperImplTestNg004, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a SecuritySessionWrapperImpl
     */
    auto sessionWrapper = GenerateSecuritySessionWrapperImpl();
    Rosen::SessionInfo sessionInfo;
    sessionWrapper->session_ = new Rosen::ExtensionSession(sessionInfo);
    EXPECT_NE(sessionWrapper->taskExecutor_, nullptr);

    sessionWrapper->hostPattern_ = CreateSecurityUEC();
    EXPECT_NE(sessionWrapper->hostPattern_.Upgrade(), nullptr);
    EXPECT_EQ(sessionWrapper->hostPattern_.Upgrade()->GetSessionId(), sessionWrapper->GetSessionId());
    sessionWrapper->InitAllCallback();

    /**
     * @tc.steps: step2. test CreateSession
     */
    auto container = Platform::AceContainer::GetContainer(sessionWrapper->instanceId_);
    EXPECT_NE(container, nullptr);
    sessionWrapper->sessionType_ = SessionType::UI_EXTENSION_ABILITY;
    SessionConfig config;
    AAFwk::Want want;
    sessionWrapper->CreateSession(want, config);

    sessionWrapper->sessionType_ = SessionType::SECURITY_UI_EXTENSION_ABILITY;
    sessionWrapper->CreateSession(want, config);

    sessionWrapper->instanceId_ = 2;
    container = Platform::AceContainer::GetContainer(sessionWrapper->instanceId_);
    EXPECT_FALSE(container->IsUIExtensionWindow());
    sessionWrapper->CreateSession(want, config);

    sessionWrapper->instanceId_ = 1;
    container = Platform::AceContainer::GetContainer(sessionWrapper->instanceId_);
    EXPECT_TRUE(container->IsUIExtensionWindow());
    sessionWrapper->CreateSession(want, config);

    /**
     * @tc.steps: step3. test DestroySession
     */
    EXPECT_NE(sessionWrapper->session_, nullptr);
    EXPECT_NE(sessionWrapper->session_->GetExtensionDataHandler(), nullptr);
    sessionWrapper->DestroySession();

    sessionWrapper->session_ = new Rosen::ExtensionSession(sessionInfo);
    sessionWrapper->session_->dataHandler_ = nullptr;
    sessionWrapper->DestroySession();
#endif
}

/**
 * @tc.name: SecuritySessionWrapperImplTestNg005
 * @tc.desc: Test the method NotifyKeyEventSync
 * @tc.type: FUNC
 */
HWTEST_F(SecuritySessionWrapperImplTestNg, SecuritySessionWrapperImplTestNg005, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a SecuritySessionWrapperImpl
     */
    auto sessionWrapper = GenerateSecuritySessionWrapperImpl();
    Rosen::SessionInfo sessionInfo;
    sessionWrapper->session_ = new Rosen::ExtensionSession(sessionInfo);

    /**
     * @tc.steps: step2. test NotifyKeyEventSync
     */
    std::shared_ptr<OHOS::MMI::KeyEvent> keyEvent;
    EXPECT_EQ(sessionWrapper->hostPattern_.Upgrade(), nullptr);
    EXPECT_FALSE(sessionWrapper->NotifyKeyEventSync(keyEvent, false));

    EXPECT_FALSE(sessionWrapper->NotifyKeyEventSync(keyEvent, true));

    sessionWrapper->hostPattern_ = CreateSecurityUEC();
    EXPECT_NE(sessionWrapper->hostPattern_.Upgrade(), nullptr);
    EXPECT_FALSE(sessionWrapper->NotifyKeyEventSync(keyEvent, true));
#endif
}

/**
 * @tc.name: SecuritySessionWrapperImplTestNg006
 * @tc.desc: Test the method NotifySizeChangeReason
 * @tc.type: FUNC
 */
HWTEST_F(SecuritySessionWrapperImplTestNg, SecuritySessionWrapperImplTestNg006, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a SecuritySessionWrapperImpl
     */
    auto sessionWrapper = GenerateSecuritySessionWrapperImpl();
    Rosen::SessionInfo sessionInfo;
    sessionWrapper->session_ = new Rosen::ExtensionSession(sessionInfo);

    /**
     * @tc.steps: step2. test NotifySizeChangeReason
     */
    auto type = OHOS::Ace::WindowSizeChangeReason::UNDEFINED;
    Parcel parcel;
    parcel.WriteUint64(123456);
    parcel.WriteInt32(100);
    parcel.WriteInt32(999);
    parcel.WriteBool(true);
    auto* rawTransaction = Rosen::RSTransaction::Unmarshalling(parcel);
    std::shared_ptr<Rosen::RSTransaction> rsTransaction(rawTransaction);
    EXPECT_NE(rsTransaction, nullptr);
    sessionWrapper->NotifySizeChangeReason(type, nullptr);
    EXPECT_EQ(sessionWrapper->session_->reason_, Rosen::SizeChangeReason::UNDEFINED);

    sessionWrapper->NotifySizeChangeReason(type, rsTransaction);
    EXPECT_TRUE(sessionWrapper->transaction_.expired());

    type = OHOS::Ace::WindowSizeChangeReason::ROTATION;
    sessionWrapper->NotifySizeChangeReason(type, rsTransaction);
    EXPECT_FALSE(sessionWrapper->transaction_.expired());
#endif
}

/**
 * @tc.name: SecuritySessionWrapperImplTestNg007
 * @tc.desc: Test the method NotifyOccupiedAreaChangeInfo, SetDensityDpiImpl and SendDataSync
 * @tc.type: FUNC
 */
HWTEST_F(SecuritySessionWrapperImplTestNg, SecuritySessionWrapperImplTestNg007, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a SecuritySessionWrapperImpl
     */
    auto sessionWrapper = GenerateSecuritySessionWrapperImpl();
    Rosen::SessionInfo sessionInfo;
    sessionWrapper->session_ = new Rosen::ExtensionSession(sessionInfo);

    /**
     * @tc.steps: step2. test NotifyOccupiedAreaChangeInfo
     */
    sptr<Rosen::OccupiedAreaChangeInfo> info = sptr<Rosen::OccupiedAreaChangeInfo>::MakeSptr();
    EXPECT_NE(info, nullptr);
    EXPECT_EQ(sessionWrapper->isNotifyOccupiedAreaChange_, true);
    info->rect_ = { 0, 0, 0, -1 };
    EXPECT_TRUE(sessionWrapper->NotifyOccupiedAreaChangeInfo(info, false));
    info->rect_ = { 0, 0, 0, 2 };
    EXPECT_TRUE(sessionWrapper->NotifyOccupiedAreaChangeInfo(info, false));

    /**
     * @tc.steps: step3. test SetDensityDpiImpl
     */
    sessionWrapper->SetDensityDpiImpl(true);
    sessionWrapper->SetDensityDpiImpl(false);

    /**
     * @tc.steps: step4. test SendDataSync
     */
    AAFwk::WantParams wantParams;
    AAFwk::WantParams reWantParams;
    sessionWrapper->SendDataSync(wantParams, reWantParams);

    sessionWrapper->session_ = nullptr;
    sessionWrapper->SendDataSync(wantParams, reWantParams);
#endif
}

/**
 * @tc.name: SecuritySessionWrapperImplTestNg008
 * @tc.desc: Test the method GetInstanceIdFromHost
 * @tc.type: FUNC
 */
HWTEST_F(SecuritySessionWrapperImplTestNg, SecuritySessionWrapperImplTestNg008, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a SecuritySessionWrapperImpl
     */
    auto sessionWrapper = GenerateSecuritySessionWrapperImpl();
    Rosen::SessionInfo sessionInfo;
    sessionWrapper->session_ = new Rosen::ExtensionSession(sessionInfo);
    sessionWrapper->hostPattern_ = CreateSecurityUEC();

    /**
     * @tc.steps: step2. test GetInstanceIdFromHost
     */
    sessionWrapper->instanceId_ = 1;
    EXPECT_NE(sessionWrapper->instanceId_, sessionWrapper->hostPattern_.Upgrade()->GetInstanceIdFromHost());
    sessionWrapper->GetInstanceIdFromHost();
    sessionWrapper->instanceId_ = sessionWrapper->hostPattern_.Upgrade()->GetInstanceIdFromHost();
    sessionWrapper->GetInstanceIdFromHost();

    sessionWrapper->hostPattern_ = nullptr;
    sessionWrapper->GetInstanceIdFromHost();
#endif
}

/**
 * @tc.name: SecuritySessionWrapperImplTestNg009
 * @tc.desc: Test the method PostBusinessDataConsumeSyncReply and so on
 * @tc.type: FUNC
 */
HWTEST_F(SecuritySessionWrapperImplTestNg, SecuritySessionWrapperImplTestNg009, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a SecuritySessionWrapperImpl
     */
    auto sessionWrapper = GenerateSecuritySessionWrapperImpl();
    Rosen::SessionInfo sessionInfo;
    sessionWrapper->session_ = new Rosen::ExtensionSession(sessionInfo);
    ASSERT_NE(sessionWrapper->taskExecutor_, nullptr);
    sessionWrapper->hostPattern_ = CreateSecurityUEC();
    ASSERT_NE(sessionWrapper->hostPattern_.Upgrade(), nullptr);
    ASSERT_EQ(sessionWrapper->hostPattern_.Upgrade()->GetSessionId(), sessionWrapper->GetSessionId());

    /**
     * @tc.steps: step2. test PostBusinessDataConsumeSyncReply and so on
     */
    AAFwk::Want data;
    std::optional<AAFwk::Want> reply;
    sessionWrapper->OnExtensionDetachToDisplay();
    sessionWrapper->OnExtensionTimeout(0);
    sessionWrapper->PostBusinessDataConsumeAsync(1, data);
    sessionWrapper->PostBusinessDataConsumeSyncReply(1, data, reply);
    sessionWrapper->OnConnect();

    sessionWrapper->session_->persistentId_ = 1;
    ASSERT_NE(sessionWrapper->hostPattern_.Upgrade()->GetSessionId(), sessionWrapper->GetSessionId());
    sessionWrapper->OnExtensionDetachToDisplay();
    sessionWrapper->OnExtensionTimeout(0);
    sessionWrapper->PostBusinessDataConsumeAsync(1, data);
    sessionWrapper->PostBusinessDataConsumeSyncReply(1, data, reply);
    sessionWrapper->OnDisconnect(true);
    sessionWrapper->OnDisconnect(false);
    sessionWrapper->OnConnect();
#endif
}

/**
 * @tc.name: SecuritySessionWrapperImplTestNg010
 * @tc.desc: Test the method NotifyDisplayArea
 * @tc.type: FUNC
 */
HWTEST_F(SecuritySessionWrapperImplTestNg, SecuritySessionWrapperImplTestNg010, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a SecuritySessionWrapperImpl
     */
    auto sessionWrapper = GenerateSecuritySessionWrapperImpl();
    Rosen::SessionInfo sessionInfo;
    sessionWrapper->session_ = new Rosen::ExtensionSession(sessionInfo);
    ASSERT_NE(sessionWrapper->taskExecutor_, nullptr);

    /**
     * @tc.steps: step2. test NotifyDisplayArea
     */
    sessionWrapper->session_->parentSession_ = nullptr;
    std::shared_ptr<Rosen::RSTransaction> rsTransaction;
    sessionWrapper->transaction_ = rsTransaction;
    RectF paintRect = { 10.0f, 10.0f, 10.0f, 10.0f };
    sessionWrapper->NotifyDisplayArea(paintRect);

    sessionWrapper->session_->reason_ = Rosen::SizeChangeReason::ROTATION;
    sessionWrapper->NotifyDisplayArea(paintRect);
#endif
}

/**
 * @tc.name: SecuritySessionWrapperImplTestNg011
 * @tc.desc: Test the method SendBusinessData and SendBusinessDataSyncReply
 * @tc.type: FUNC
 */
HWTEST_F(SecuritySessionWrapperImplTestNg, SecuritySessionWrapperImplTestNg011, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a SecuritySessionWrapperImpl
     */
    auto sessionWrapper = GenerateSecuritySessionWrapperImpl();
    Rosen::SessionInfo sessionInfo;
    sessionWrapper->session_ = new Rosen::ExtensionSession(sessionInfo);
    EXPECT_NE(sessionWrapper->session_->GetExtensionDataHandler(), nullptr);

    /**
     * @tc.steps: step2. test SendBusinessData and SendBusinessDataSyncReply
     */
    UIContentBusinessCode code = UIContentBusinessCode::UNDEFINED;
    AAFwk::Want data;
    AAFwk::Want reply;
    RSSubsystemId id = RSSubsystemId::ARKUI_UIEXT;
    BusinessDataSendType type = NG::BusinessDataSendType::ASYNC;
    auto ret = sessionWrapper->SendBusinessData(code, data, type, id);
    EXPECT_EQ(ret, false);
    ret = sessionWrapper->SendBusinessDataSyncReply(code, data, reply, id);
    EXPECT_EQ(ret, false);

    code = UIContentBusinessCode::EVENT_PROXY;
    ret = sessionWrapper->SendBusinessData(code, data, type, id);
    EXPECT_NE(ret, false);
    ret = sessionWrapper->SendBusinessDataSyncReply(code, data, reply, id);
    EXPECT_NE(ret, false);
#endif
}

/**
 * @tc.name: SecuritySessionWrapperImplTestNg012
 * @tc.desc: Test the method DispatchExtensionDataToHostWindow
 * @tc.type: FUNC
 */
HWTEST_F(SecuritySessionWrapperImplTestNg, SecuritySessionWrapperImplTestNg012, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a SecuritySessionWrapperImpl
     */
    auto sessionWrapper = GenerateSecuritySessionWrapperImpl();
    Rosen::SessionInfo sessionInfo;
    sessionWrapper->session_ = new Rosen::ExtensionSession(sessionInfo);
    ASSERT_NE(sessionWrapper->taskExecutor_, nullptr);
    sessionWrapper->hostPattern_ = CreateSecurityUEC();
    ASSERT_NE(sessionWrapper->hostPattern_.Upgrade(), nullptr);
    ASSERT_EQ(sessionWrapper->hostPattern_.Upgrade()->GetSessionId(), sessionWrapper->GetSessionId());

    /**
     * @tc.steps: step2. test DispatchExtensionDataToHostWindow and so on
     */
    AAFwk::Want data;
    std::optional<AAFwk::Want> reply;
    uint32_t customId = 1;
    sessionWrapper->OnExtensionDetachToDisplay();
    sessionWrapper->OnExtensionTimeout(0);
    sessionWrapper->DispatchExtensionDataToHostWindow(customId, data);
    sessionWrapper->OnConnect();

    sessionWrapper->session_->persistentId_ = 1;
    ASSERT_NE(sessionWrapper->hostPattern_.Upgrade()->GetSessionId(), sessionWrapper->GetSessionId());
    sessionWrapper->OnExtensionDetachToDisplay();
    sessionWrapper->OnExtensionTimeout(0);
    customId = static_cast<uint32_t>(UIContentBusinessCode::WINDOW_CODE_BEGIN);
    sessionWrapper->DispatchExtensionDataToHostWindow(customId, data);
    sessionWrapper->OnDisconnect(true);
    sessionWrapper->OnDisconnect(false);
    sessionWrapper->OnConnect();
#endif
}
} // namespace OHOS::Ace::NG
