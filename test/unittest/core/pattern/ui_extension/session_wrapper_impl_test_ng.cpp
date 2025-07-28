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
#include "adapter/ohos/entrance/ace_container.h"

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

class SessionWrapperImplTestNg : public testing::Test {
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
    RefPtr<SessionWrapperImpl> GenerateSessionWrapperImpl();
};

void SessionWrapperImplTestNg::SetUp() {
}

void SessionWrapperImplTestNg::TearDown() {
}

RefPtr<SessionWrapperImpl> SessionWrapperImplTestNg::GenerateSessionWrapperImpl()
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
 * @tc.name: SessionWrapperImplTestNg001
 * @tc.desc: Test the method SendBusinessDataSyncReply and SendDataSync
 * @tc.type: FUNC
 */
HWTEST_F(SessionWrapperImplTestNg, SessionWrapperImplTestNg001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a SessionWrapperImpl
     */
    auto sessionWrapper = GenerateSessionWrapperImpl();

    /**
     * @tc.steps: step2. test SendBusinessDataSyncReply
     */
    UIContentBusinessCode code = UIContentBusinessCode::UNDEFINED;
    AAFwk::Want want;
    AAFwk::Want reply;
    auto ret = sessionWrapper->SendBusinessDataSyncReply(code, want, reply, RSSubsystemId::WM_UIEXT);
    EXPECT_FALSE(ret);

    code = UIContentBusinessCode::SEND_PAGE_MODE_REQUEST;
    ret = sessionWrapper->SendBusinessDataSyncReply(code, want, reply, RSSubsystemId::WM_UIEXT);
    EXPECT_FALSE(ret);

    /**
     * @tc.steps: step2. test SendDataSync
     */
    AAFwk::WantParams wantParams;
    AAFwk::WantParams reWantParams;
    ASSERT_EQ(sessionWrapper->session_, nullptr);
    sessionWrapper->SendDataSync(wantParams, reWantParams);

    Rosen::SessionInfo sessionInfo;
    sessionWrapper->session_ = new Rosen::ExtensionSession(sessionInfo);
    sessionWrapper->SendDataSync(wantParams, reWantParams);
#endif
}

/**
 * @tc.name: SessionWrapperImplTestNg002
 * @tc.desc: Test the method InnerNotifyOccupiedAreaChangeInfo
 * @tc.type: FUNC
 */
HWTEST_F(SessionWrapperImplTestNg, SessionWrapperImplTestNg002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a SessionWrapperImpl
     */
    auto sessionWrapper = GenerateSessionWrapperImpl();

    /**
     * @tc.steps: step2. test InnerNotifyOccupiedAreaChangeInfo
     */
    UIContentBusinessCode code = UIContentBusinessCode::UNDEFINED;
    AAFwk::Want want;
    AAFwk::Want reply;
    auto ret = sessionWrapper->SendBusinessDataSyncReply(code, want, reply, RSSubsystemId::WM_UIEXT);
    EXPECT_FALSE(ret);

    code = UIContentBusinessCode::SEND_PAGE_MODE_REQUEST;
    ret = sessionWrapper->SendBusinessDataSyncReply(code, want, reply, RSSubsystemId::WM_UIEXT);
    EXPECT_FALSE(ret);

    /**
     * @tc.steps: step2. test SendDataSync
     */
    AAFwk::WantParams wantParams;
    AAFwk::WantParams reWantParams;
    ASSERT_EQ(sessionWrapper->session_, nullptr);
    sessionWrapper->SendDataSync(wantParams, reWantParams);

    Rosen::SessionInfo sessionInfo;
    sessionWrapper->session_ = new Rosen::ExtensionSession(sessionInfo);
    sessionWrapper->SendDataSync(wantParams, reWantParams);
#endif
}

/**
 * @tc.name: SessionWrapperImplTestNg003
 * @tc.desc: Test the method NotifySizeChangeReason
 * @tc.type: FUNC
 */
HWTEST_F(SessionWrapperImplTestNg, SessionWrapperImplTestNg003, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a SessionWrapperImpl
     */
    auto sessionWrapper = GenerateSessionWrapperImpl();

    /**
     * @tc.steps: step2. test NotifySizeChangeReason
     */
    sessionWrapper->NotifySizeChangeReason(WindowSizeChangeReason::RESIZE, nullptr);
    ASSERT_EQ(sessionWrapper->transaction_.lock(), nullptr);

    Rosen::SessionInfo sessionInfo;
    sessionWrapper->session_ = new Rosen::ExtensionSession(sessionInfo);
    sessionWrapper->NotifySizeChangeReason(WindowSizeChangeReason::RESIZE, nullptr);
    ASSERT_EQ(sessionWrapper->transaction_.lock(), nullptr);

    std::shared_ptr<Rosen::RSTransaction> rsTransaction;
    sessionWrapper->NotifySizeChangeReason(WindowSizeChangeReason::RESIZE, rsTransaction);
    ASSERT_EQ(sessionWrapper->transaction_.lock(), nullptr);

    sessionWrapper->NotifySizeChangeReason(WindowSizeChangeReason::ROTATION, rsTransaction);
    ASSERT_EQ(sessionWrapper->transaction_.lock(), nullptr);
#endif
}

/**
 * @tc.name: SessionWrapperImplTestNg004
 * @tc.desc: Test the method NotifyKeyEventAsync and NotifyPointerEventAsync
 * @tc.type: FUNC
 */
HWTEST_F(SessionWrapperImplTestNg, SessionWrapperImplTestNg004, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a SessionWrapperImpl
     */
    auto sessionWrapper = GenerateSessionWrapperImpl();
    ASSERT_EQ(sessionWrapper->session_, nullptr);

    /**
     * @tc.steps: step2. test NotifyKeyEventAsync and NotifyPointerEventAsync
     */
    EXPECT_FALSE(sessionWrapper->NotifyKeyEventAsync(nullptr));
    EXPECT_FALSE(sessionWrapper->NotifyKeyEventAsync(nullptr));

    Rosen::SessionInfo sessionInfo;
    sessionWrapper->session_ = new Rosen::ExtensionSession(sessionInfo);
    EXPECT_FALSE(sessionWrapper->NotifyKeyEventAsync(nullptr));
    EXPECT_FALSE(sessionWrapper->NotifyKeyEventAsync(nullptr));

    std::shared_ptr<OHOS::MMI::KeyEvent> keyEvent;
    EXPECT_FALSE(sessionWrapper->NotifyKeyEventAsync(keyEvent));
    EXPECT_FALSE(sessionWrapper->NotifyKeyEventAsync(keyEvent));
#endif
}

/**
 * @tc.name: SessionWrapperImplTestNg005
 * @tc.desc: Test the method ReDispatchWantParams
 * @tc.type: FUNC
 */
HWTEST_F(SessionWrapperImplTestNg, SessionWrapperImplTestNg005, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a SecuritySessionWrapperImpl
     */
    auto sessionWrapper = GenerateSessionWrapperImpl();
    Rosen::SessionInfo sessionInfo;
    sessionWrapper->session_ = new Rosen::ExtensionSession(sessionInfo);
    EXPECT_NE(sessionWrapper->session_->GetExtensionDataHandler(), nullptr);
    auto container = Platform::AceContainer::GetContainer(sessionWrapper->instanceId_);
    EXPECT_NE(container, nullptr);

    /**
     * @tc.steps: step2. test ReDispatchWantParams
     */
    RefPtr<WantWrap> wantWrap = AceType::MakeRefPtr<WantWrapOhos>("123", "123");
    auto wantWrapOhos = AceType::DynamicCast<WantWrapOhos>(wantWrap);
    auto want = wantWrapOhos->GetWant();
    want.SetParam("type", std::string("test type"));
    sessionWrapper->customWant_ = std::make_shared<AAFwk::Want>(want);
    sessionWrapper->ReDispatchWantParams();
#endif
}

/**
 * @tc.name: SessionWrapperImplTestNg007
 * @tc.desc: Test the method GetWant
 * @tc.type: FUNC
 */
HWTEST_F(SessionWrapperImplTestNg, SessionWrapperImplTestNg007, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a SessionWrapperImpl
     */
    auto sessionWrapper = GenerateSessionWrapperImpl();
    EXPECT_EQ(sessionWrapper->session_, nullptr);

    /**
     * @tc.steps: step2. test GetWant
     */
    EXPECT_EQ(sessionWrapper->GetWant(), nullptr);
    Rosen::SessionInfo sessionInfo;
    sessionWrapper->session_ = new Rosen::ExtensionSession(sessionInfo);
    EXPECT_EQ(sessionWrapper->GetWant(), sessionWrapper->customWant_);
#endif
}

/**
 * @tc.name: SessionWrapperImplTestNg008
 * @tc.desc: Test the method NotifyBackPressedSync
 * @tc.type: FUNC
 */
HWTEST_F(SessionWrapperImplTestNg, SessionWrapperImplTestNg008, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a SessionWrapperImpl
     */
    auto sessionWrapper = GenerateSessionWrapperImpl();
    EXPECT_EQ(sessionWrapper->session_, nullptr);

    /**
     * @tc.steps: step2. test NotifyBackPressedSync
     */
    EXPECT_FALSE(sessionWrapper->NotifyBackPressedSync());
    Rosen::SessionInfo sessionInfo;
    sessionWrapper->session_ = new Rosen::ExtensionSession(sessionInfo);
    EXPECT_FALSE(sessionWrapper->NotifyBackPressedSync());
#endif
}

/**
 * @tc.name: SessionWrapperImplTestNg009
 * @tc.desc: Test the method NotifyKeyEventAsync
 * @tc.type: FUNC
 */
HWTEST_F(SessionWrapperImplTestNg, SessionWrapperImplTestNg009, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a SessionWrapperImpl
     */
    auto sessionWrapper = GenerateSessionWrapperImpl();
    EXPECT_EQ(sessionWrapper->session_, nullptr);

    /**
     * @tc.steps: step2. test NotifyKeyEventAsync
     */
    std::shared_ptr<OHOS::MMI::KeyEvent> keyEvent;
    EXPECT_FALSE(sessionWrapper->NotifyKeyEventAsync(keyEvent, false));
    Rosen::SessionInfo sessionInfo;
    sessionWrapper->session_ = new Rosen::ExtensionSession(sessionInfo);
    EXPECT_TRUE(sessionWrapper->NotifyKeyEventAsync(keyEvent, false));
#endif
}

/**
 * @tc.name: SessionWrapperImplTestNg010
 * @tc.desc: Test the method NotifyFocusEventAsync
 * @tc.type: FUNC
 */
HWTEST_F(SessionWrapperImplTestNg, SessionWrapperImplTestNg010, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a SessionWrapperImpl
     */
    auto sessionWrapper = GenerateSessionWrapperImpl();
    EXPECT_EQ(sessionWrapper->session_, nullptr);

    /**
     * @tc.steps: step2. test NotifyFocusEventAsync
     */
    EXPECT_FALSE(sessionWrapper->NotifyFocusEventAsync(false));
    Rosen::SessionInfo sessionInfo;
    sessionWrapper->session_ = new Rosen::ExtensionSession(sessionInfo);
    EXPECT_TRUE(sessionWrapper->NotifyFocusEventAsync(false));
#endif
}

/**
 * @tc.name: SessionWrapperImplTestNg011
 * @tc.desc: Test the method NotifyFocusStateAsync
 * @tc.type: FUNC
 */
HWTEST_F(SessionWrapperImplTestNg, SessionWrapperImplTestNg011, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a SessionWrapperImpl
     */
    auto sessionWrapper = GenerateSessionWrapperImpl();
    EXPECT_EQ(sessionWrapper->session_, nullptr);

    /**
     * @tc.steps: step2. test NotifyFocusStateAsync
     */
    EXPECT_FALSE(sessionWrapper->NotifyFocusStateAsync(false));
    Rosen::SessionInfo sessionInfo;
    sessionWrapper->session_ = new Rosen::ExtensionSession(sessionInfo);
    EXPECT_TRUE(sessionWrapper->NotifyFocusStateAsync(false));
#endif
}
} // namespace OHOS::Ace::NG
