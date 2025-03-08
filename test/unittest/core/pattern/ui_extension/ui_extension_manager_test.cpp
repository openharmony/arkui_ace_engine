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
#include "adapter/ohos/osal/want_wrap_ohos.h"
#include "core/components_ng/pattern/ui_extension/security_ui_extension_component/security_ui_extension_pattern.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_component/ui_extension_pattern.h"
#include "core/components_ng/pattern/ui_extension/session_wrapper.h"
#include "core/components_ng/pattern/ui_extension/session_wrapper_factory.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_component/session_wrapper_impl.h"
#include "frameworks/core/accessibility/accessibility_manager.h"
#include "frameworks/core/components_ng/pattern/ui_extension/ui_extension_manager.h"
#include "frameworks/core/common/window_animation_config.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include <ui/rs_surface_node.h>
#include <ui/rs_ui_director.h>

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
    const std::string PLATFORM_PATTERN_ETS_TAG = "PlatformPattern";
    const int32_t CODE = 10001;
    const std::string NAME = "Test name";
    const std::string MSG = "Test msg";
    const std::string TAG = "Test node tag";
    int32_t platformId = 1;
} // namespace

class UIExtensionManagerNg : public testing::Test {
public:
    void SetUp() override;
    void TearDown() override;
};

void UIExtensionManagerNg::SetUp()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->pipelineContext_ = PipelineBase::GetCurrentContext();
}

void UIExtensionManagerNg::TearDown()
{
    MockContainer::Current()->pipelineContext_ = nullptr;
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: UIExtensionManager001
 * @tc.desc: Test UIExtensionManager RegisterUIExtensionInFocus/OnBackPressed/GetFocusUiExtensionNode/
    RegisterSecurityUIExtensionInFocus
 * @tc.type: FUNC
 */
HWTEST_F(UIExtensionManagerNg, UIExtensionManager001, TestSize.Level1)
{
    #ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct UIExtensionManager
     */
    auto uiExtensionManager = AceType::MakeRefPtr<UIExtensionManager>();
    ASSERT_NE(uiExtensionManager, nullptr);

    /**
     * @tc.steps: step2. call RegisterUIExtensionInFocus
     * @tc.expected: expect uiExtensionFocused_ and sessionWrapper_ is not nullptr
     */
    auto uiExtensionFocused = WeakPtr<UIExtensionPattern>();
    auto sessionWrapper = WeakPtr<SessionWrapper>();
    uiExtensionManager->RegisterUIExtensionInFocus(uiExtensionFocused, sessionWrapper);
    ASSERT_EQ(uiExtensionManager->securityUiExtensionFocused_.Upgrade(), nullptr);
    ASSERT_EQ(uiExtensionManager->uiExtensionFocused_.Upgrade(), nullptr);
    ASSERT_EQ(uiExtensionManager->sessionWrapper_.Upgrade(), nullptr);

    /**
     * @tc.steps: step3. call OnBackPressed.
     * @tc.expected: expect result is nullptr
     */
    auto onBackPressed = uiExtensionManager->OnBackPressed();
    ASSERT_FALSE(onBackPressed);

    /**
     * @tc.steps: step4. call GetFocusUiExtensionNode.
     * @tc.expected: expect focusType is NODE.
     * @tc.expected: expect focusable is false.
     * @tc.expected: expect styleType is FORCE_NONE.
     */
    auto focusUiExtensionNode = uiExtensionManager->GetFocusUiExtensionNode();
    ASSERT_EQ(focusUiExtensionNode, nullptr);

    /**
     * @tc.steps: step5. get RegisterSecurityUIExtensionInFocus
     * @tc.expected: expect securityUiExtensionFocused_ and sessionWrapper_ is not nullptr
     */
    auto securityUIExtensionPattern = WeakPtr<SecurityUIExtensionPattern>();
    uiExtensionManager->RegisterSecurityUIExtensionInFocus(securityUIExtensionPattern, sessionWrapper);
    ASSERT_EQ(uiExtensionManager->uiExtensionFocused_.Upgrade(), nullptr);
    ASSERT_EQ(uiExtensionManager->securityUiExtensionFocused_.Upgrade(), nullptr);
    ASSERT_EQ(uiExtensionManager->sessionWrapper_.Upgrade(), nullptr);
    #endif
}

/**
 * @tc.name: UIExtensionManager002
 * @tc.desc: Test UIExtensionManager IsWrapExtensionAbilityId/SendAccessibilityEventInfo/
    UnWrapExtensionAbilityId/ApplyExtensionId/RecycleExtensionId
 * @tc.type: FUNC
 */
HWTEST_F(UIExtensionManagerNg, UIExtensionManager002, TestSize.Level1)
{
    #ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct UIExtensionManager
     */
    auto uiExtensionManager = AceType::MakeRefPtr<UIExtensionManager>();
    ASSERT_NE(uiExtensionManager, nullptr);

    /**
     * @tc.steps: step2. call IsWrapExtensionAbilityId
     */
    int64_t elementId = 1;
    auto isWrapExtensionAbilityId = uiExtensionManager->IsWrapExtensionAbilityId(elementId);
    ASSERT_FALSE(isWrapExtensionAbilityId);
    elementId = 10000000001;
    isWrapExtensionAbilityId = uiExtensionManager->IsWrapExtensionAbilityId(elementId);
    ASSERT_TRUE(isWrapExtensionAbilityId);

    /**
     * @tc.steps: step4. call UnWrapExtensionAbilityId.
     */
    int64_t extensionOffset = 0;
    elementId = 1;
    auto pair = uiExtensionManager->UnWrapExtensionAbilityId(extensionOffset, elementId);
    ASSERT_EQ(pair.first, 0);
    ASSERT_EQ(pair.second, 0);
    extensionOffset = 1;
    pair = uiExtensionManager->UnWrapExtensionAbilityId(extensionOffset, elementId);
    ASSERT_EQ(pair.first, 1);
    ASSERT_EQ(pair.second, 0);

    /**
     * @tc.steps: step5. call ApplyExtensionId.
     * @tc.expected: expect result is not equal to UI_EXTENSION_UNKNOW_ID.
     */
    ASSERT_NE(uiExtensionManager->ApplyExtensionId(), UI_EXTENSION_UNKNOW_ID);

     /**
     * @tc.steps: step5. call RecycleExtensionId.
     */
    uiExtensionManager->RecycleExtensionId(1);
    #endif
}

/**
 * @tc.name: UIExtensionManager003
 * @tc.desc: Test UIExtensionManager AddAliveUIExtension/AddAliveUIExtension/
    IsShowPlaceholder/RemoveDestroyedUIExtension/NotifySizeChangeReason
 * @tc.type: FUNC
 */
HWTEST_F(UIExtensionManagerNg, UIExtensionManager003, TestSize.Level1)
{
    #ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct UIExtensionManager
     */
    auto uiExtensionManager = AceType::MakeRefPtr<UIExtensionManager>();
    ASSERT_NE(uiExtensionManager, nullptr);

    /**
     * @tc.steps: step2. call AddAliveUIExtension
     * @tc.expected: size of aliveUIExtensions_ is 1.
     */
    WeakPtr<UIExtensionPattern> platformPattern;
    int32_t nodeId = 1;
    uiExtensionManager->AddAliveUIExtension(nodeId, platformPattern);
    ASSERT_EQ(uiExtensionManager->aliveUIExtensions_.size(), 1);

    /**
     * @tc.steps: step3. call AddAliveUIExtension.
     * @tc.expected: size of aliveSecurityUIExtensions_ is 1.
     */
    WeakPtr<SecurityUIExtensionPattern> securityUIExtensionPattern;
    uiExtensionManager->AddAliveUIExtension(nodeId, securityUIExtensionPattern);
    ASSERT_EQ(uiExtensionManager->aliveSecurityUIExtensions_.size(), 1);

    /**
     * @tc.steps: step4. call IsShowPlaceholder.
     * @tc.expected: result is true.
     */
    ASSERT_TRUE(uiExtensionManager->IsShowPlaceholder(nodeId));

    /**
     * @tc.steps: step5. call NotifySizeChangeReason.
     */
    std::shared_ptr<Rosen::RSTransaction> rsTransaction;
    uiExtensionManager->NotifySizeChangeReason(WindowSizeChangeReason::RESIZE, rsTransaction);

    /**
     * @tc.steps: step6. call RemoveDestroyedUIExtension.
     * @tc.expected: size of aliveUIExtensions_ is 0.
     * @tc.expected: size of aliveSecurityUIExtensions_ is 0.
     */
    uiExtensionManager->RemoveDestroyedUIExtension(nodeId);
    ASSERT_EQ(uiExtensionManager->aliveSecurityUIExtensions_.size(), 0);
    ASSERT_EQ(uiExtensionManager->aliveSecurityUIExtensions_.size(), 0);
    #endif
}

/**
 * @tc.name: UIExtensionManager004
 * @tc.desc: Test UIExtensionManager UIExtBusinessDataSendValid/RegisterBusinessSendToHostReply/
 *  RegisterBusinessSendToHost/SendBusinessToHost/SendBusinessToHostSyncReply
 * @tc.type: FUNC
 */
HWTEST_F(UIExtensionManagerNg, UIExtensionManager004, TestSize.Level1)
{
    #ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct UIExtensionManager.
     */
    auto uiExtensionManager = AceType::MakeRefPtr<UIExtensionManager>();
    ASSERT_NE(uiExtensionManager, nullptr);
    bool called0 = false;
    bool called1 = false;
    OHOS::AAFwk::Want want;
    OHOS::AAFwk::Want reply;
    BusinessDataSendType type = BusinessDataSendType::SYNC;
    UIContentBusinessCode code = UIContentBusinessCode::UNDEFINED;

    /**
     * @tc.steps: step2. test UIExtBusinessDataSendValid/SendBusinessToHost/SendBusinessToHostSyncReply.
     * @tc.expected: result is false.
     */
    EXPECT_FALSE(uiExtensionManager->UIExtBusinessDataSendValid());
    EXPECT_FALSE(uiExtensionManager->SendBusinessToHost(code, want, type));
    EXPECT_FALSE(uiExtensionManager->SendBusinessToHostSyncReply(code, want, reply));

    /**
     * @tc.steps: step3. RegisterBusinessSendToHostReply/RegisterBusinessSendToHost.
     */
    UIExtBusinessSendToHostReplyFunc func0 = [&](uint32_t code, const AAFwk::Want& req, AAFwk::Want& reply) {
        called0 = true;
        return true;
    };
    uiExtensionManager->RegisterBusinessSendToHostReply(func0);
    EXPECT_FALSE(uiExtensionManager->UIExtBusinessDataSendValid());
    UIExtBusinessSendToHostFunc func1 = [&](uint32_t code, const AAFwk::Want& req, BusinessDataSendType sendType) {
        called1 = true;
        return true;
    };
    uiExtensionManager->RegisterBusinessSendToHost(func1);
    EXPECT_TRUE(uiExtensionManager->UIExtBusinessDataSendValid());

    /**
     * @tc.steps: step4. test UIExtBusinessDataSendValid/SendBusinessToHost/SendBusinessToHostSyncReply.
     * @tc.expected: result is true.
     */
    EXPECT_TRUE(uiExtensionManager->SendBusinessToHostSyncReply(code, want, reply));
    EXPECT_TRUE(called0);
    EXPECT_TRUE(uiExtensionManager->SendBusinessToHost(code, want, type));
    EXPECT_TRUE(called1);
    #endif
}

/**
 * @tc.name: UIExtensionManager005
 * @tc.desc: Test UIExtensionManager RegisterBusinessDataConsumeReplyCallback/DispatchBusinessDataConsumeReply/
 *  UnRegisterBusinessDataConsumeReplyCallback
 * @tc.type: FUNC
 */
HWTEST_F(UIExtensionManagerNg, UIExtensionManager005, TestSize.Level1)
{
    #ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct UIExtensionManager.
     */
    auto uiExtensionManager = AceType::MakeRefPtr<UIExtensionManager>();
    ASSERT_NE(uiExtensionManager, nullptr);
    OHOS::AAFwk::Want want;
    std::optional<OHOS::AAFwk::Want> replyData;
    UIContentBusinessCode code = UIContentBusinessCode::UNDEFINED;
    bool called = false;

    /**
     * @tc.steps: step2. test RegisterBusinessDataConsumeReplyCallback.
     * @tc.expected: size of businessDataConsumeReplyCallbacks_ is 1.
     */
    UIExtBusinessDataConsumeReplyCallback callback = [&](const AAFwk::Want& data, std::optional<AAFwk::Want>& reply) {
        called = true;
        return 20;
    };
    uiExtensionManager->RegisterBusinessDataConsumeReplyCallback(code, callback);
    ASSERT_EQ(uiExtensionManager->businessDataConsumeReplyCallbacks_.size(), 1);
    EXPECT_FALSE(called);

    /**
     * @tc.steps: step3. test DispatchBusinessDataConsumeReply.
     * @tc.expected: result is true.
     */
    uiExtensionManager->DispatchBusinessDataConsumeReply(code, want, replyData);
    ASSERT_EQ(uiExtensionManager->businessDataConsumeReplyCallbacks_.size(), 1);
    EXPECT_TRUE(called);

    /**
     * @tc.steps: step4. test UnRegisterBusinessDataConsumeReplyCallback.
     * @tc.expected: result is true.
     */
    uiExtensionManager->UnRegisterBusinessDataConsumeReplyCallback(code);
    ASSERT_EQ(uiExtensionManager->businessDataConsumeReplyCallbacks_.size(), 0);

    /**
     * @tc.steps: step5. test DispatchBusinessDataConsumeReply.
     * @tc.expected: size of businessDataConsumeReplyCallbacks_ is 0.
     */
    called = false;
    uiExtensionManager->DispatchBusinessDataConsumeReply(code, want, replyData);
    ASSERT_EQ(uiExtensionManager->businessDataConsumeReplyCallbacks_.size(), 0);
    EXPECT_FALSE(called);

    /**
     * @tc.steps: step6. test UnRegisterBusinessDataConsumeReplyCallback.
     * @tc.expected: should not crash.
     */
    uiExtensionManager->UnRegisterBusinessDataConsumeReplyCallback(code);
    ASSERT_EQ(uiExtensionManager->businessDataConsumeReplyCallbacks_.size(), 0);
    #endif
}

/**
 * @tc.name: UIExtensionManager006
 * @tc.desc: Test UIExtensionManager RegisterBusinessDataConsumeCallback/DispatchBusinessDataConsume/
 *  UnRegisterBusinessDataConsumeCallback
 * @tc.type: FUNC
 */
HWTEST_F(UIExtensionManagerNg, UIExtensionManager006, TestSize.Level1)
{
    #ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct UIExtensionManager.
     */
    auto uiExtensionManager = AceType::MakeRefPtr<UIExtensionManager>();
    ASSERT_NE(uiExtensionManager, nullptr);
    OHOS::AAFwk::Want want;
    UIContentBusinessCode code = UIContentBusinessCode::UNDEFINED;
    bool called = false;

    /**
     * @tc.steps: step2. test RegisterBusinessDataConsumeCallback.
     * @tc.expected: size of businessDataConsumeCallbacks_ is 1.
     */
    UIExtBusinessDataConsumeCallback callback = [&](const AAFwk::Want& want) {
        called = true;
        return 20;
    };
    uiExtensionManager->RegisterBusinessDataConsumeCallback(code, callback);
    ASSERT_EQ(uiExtensionManager->businessDataConsumeCallbacks_.size(), 1);
    EXPECT_FALSE(called);

    /**
     * @tc.steps: step3. test DispatchBusinessDataConsume.
     * @tc.expected: result is true.
     */
    uiExtensionManager->DispatchBusinessDataConsume(code, want);
    ASSERT_EQ(uiExtensionManager->businessDataConsumeCallbacks_.size(), 1);
    EXPECT_TRUE(called);

    /**
     * @tc.steps: step4. test UnRegisterBusinessDataConsumeCallback.
     * @tc.expected: result is true.
     */
    uiExtensionManager->UnRegisterBusinessDataConsumeCallback(code);
    ASSERT_EQ(uiExtensionManager->businessDataConsumeCallbacks_.size(), 0);

    /**
     * @tc.steps: step5. test DispatchBusinessDataConsume.
     * @tc.expected: size of businessDataConsumeCallbacks_ is 0.
     */
    called = false;
    uiExtensionManager->DispatchBusinessDataConsume(code, want);
    ASSERT_EQ(uiExtensionManager->businessDataConsumeCallbacks_.size(), 0);
    EXPECT_FALSE(called);

    /**
     * @tc.steps: step6. test UnRegisterBusinessDataConsumeCallback.
     * @tc.expected: should not crash.
     */
    uiExtensionManager->UnRegisterBusinessDataConsumeCallback(code);
    ASSERT_EQ(uiExtensionManager->businessDataConsumeCallbacks_.size(), 0);
    #endif
}

/**
 * @tc.name: UIExtensionManager007
 * @tc.desc: Test UIExtensionManager RegisterBusinessDataSendCallback/UnRegisterBusinessDataSendCallback/
 *  TriggerBusinessDataSend
 * @tc.type: FUNC
 */
HWTEST_F(UIExtensionManagerNg, UIExtensionManager007, TestSize.Level1)
{
    #ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct UIExtensionManager.
     */
    auto uiExtensionManager = AceType::MakeRefPtr<UIExtensionManager>();
    ASSERT_NE(uiExtensionManager, nullptr);
    OHOS::AAFwk::Want want;
    std::optional<OHOS::AAFwk::Want> replyData;
    BusinessDataSendType type = BusinessDataSendType::SYNC;
    UIContentBusinessCode code = UIContentBusinessCode::UNDEFINED;
    RSSubsystemId id = RSSubsystemId::WM_UIEXT;
    bool called = false;

    /**
     * @tc.steps: step2. test RegisterBusinessDataSendCallback.
     * @tc.expected: size of businessDataSendCallbacks_ is 1.
     */
    UIExtBusinessDataSendCallback callback = [&](WeakPtr<FrameNode> node) {
        called = true;
        return std::optional<OHOS::AAFwk::Want>(want);
    };
    uiExtensionManager->RegisterBusinessDataSendCallback(code, type, callback, id);
    ASSERT_EQ(uiExtensionManager->businessDataSendCallbacks_.size(), 1);
    EXPECT_FALSE(called);

    /**
     * @tc.steps: step3. test TriggerBusinessDataSend.
     * @tc.expected: result is false.
     */
    uiExtensionManager->TriggerBusinessDataSend(code);
    ASSERT_EQ(uiExtensionManager->businessDataSendCallbacks_.size(), 1);
    EXPECT_FALSE(called);

    /**
     * @tc.steps: step4. test UnRegisterBusinessDataSendCallback.
     * @tc.expected: size of businessDataSendCallbacks_ is 0.
     */
    uiExtensionManager->UnRegisterBusinessDataSendCallback(code);
    ASSERT_EQ(uiExtensionManager->businessDataSendCallbacks_.size(), 0);
    #endif
}

/**
 * @tc.name: UIExtensionManager008
 * @tc.desc: Test UIExtensionManager TransferOriginAvoidArea/NotifyOccupiedAreaChangeInfo
 * @tc.type: FUNC
 */
HWTEST_F(UIExtensionManagerNg, UIExtensionManager008, TestSize.Level1)
{
    #ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct UIExtensionManager.
     */
    auto uiExtensionManager = AceType::MakeRefPtr<UIExtensionManager>();
    ASSERT_NE(uiExtensionManager, nullptr);

    /**
     * @tc.steps: step2. call AddAliveUIExtension.
     * @tc.expected: size of aliveUIExtensions_ is 1.
     */
    WeakPtr<UIExtensionPattern> platformPattern;
    int32_t nodeId = 1;
    uiExtensionManager->AddAliveUIExtension(nodeId, platformPattern);
    ASSERT_EQ(uiExtensionManager->aliveUIExtensions_.size(), 1);

    /**
     * @tc.steps: step3. call AddAliveUIExtension.
     * @tc.expected: size of aliveSecurityUIExtensions_ is 1.
     */
    WeakPtr<SecurityUIExtensionPattern> securityUIExtensionPattern;
    uiExtensionManager->AddAliveUIExtension(nodeId, securityUIExtensionPattern);
    ASSERT_EQ(uiExtensionManager->aliveSecurityUIExtensions_.size(), 1);

    /**
     * @tc.steps: step4. test TransferOriginAvoidArea.
     */
    Rosen::AvoidArea avoidArea;
    uint32_t type = 1;
    uiExtensionManager->TransferOriginAvoidArea(avoidArea, type);

    /**
     * @tc.steps: step5. test NotifyOccupiedAreaChangeInfo.
     */
    auto info = sptr<Rosen::OccupiedAreaChangeInfo>(new Rosen::OccupiedAreaChangeInfo());
    info->rect_.height_ = 100;
    auto sessionWrapper = WeakPtr<SessionWrapper>();
    uiExtensionManager->sessionWrapper_ = sessionWrapper;
    bool result = uiExtensionManager->NotifyOccupiedAreaChangeInfo(info);
    EXPECT_FALSE(result);

    /**
     * @tc.steps: step6. call RemoveDestroyedUIExtension.
     * @tc.expected: size of aliveUIExtensions_ is 0.
     * @tc.expected: size of aliveSecurityUIExtensions_ is 0.
     */
    uiExtensionManager->RemoveDestroyedUIExtension(nodeId);
    ASSERT_EQ(uiExtensionManager->aliveSecurityUIExtensions_.size(), 0);
    ASSERT_EQ(uiExtensionManager->aliveSecurityUIExtensions_.size(), 0);
    #endif
}
}