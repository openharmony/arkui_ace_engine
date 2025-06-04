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
#include "core/components_ng/pattern/ui_extension/security_ui_extension_component/security_session_wrapper_impl.h"
#include "core/components_ng/pattern/ui_extension/security_ui_extension_component/security_ui_extension_pattern.h"
#include "core/components_ng/pattern/ui_extension/security_ui_extension_component/security_ui_extension_proxy.h"
#include "core/components_ng/pattern/ui_extension/session_wrapper.h"
#include "core/components_ng/pattern/ui_extension/session_wrapper_factory.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_component/modal_ui_extension_proxy_impl.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_component/ui_extension_pattern.h"
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
#include "test/mock/core/render/mock_rosen_render_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
    const std::string SECURITY_UI_EXTENSION_COMPONENT_ETS_TAG = "SecurityUIExtensionComponent";
    const int32_t CODE = 10001;
    const std::string NAME = "Test name";
    const std::string MSG = "Test msg";
    const std::string BOUNDLE_NAME = "com.example.test";
    const std::string ABILITY_NAME = "UIExtensionAbility";
    const std::string BOUNDLE_NAME_NEW = "com.example.test.new";
    const std::string ABILITY_NAME_NEW = "UIExtensionAbilityNew";
    const std::string ABILITY_KEY_UIEXTENSIONTYPE = "ability.want.params.uiExtensionType";
    const std::string ABILITY_VALUE_UIEXTENSIONTYPE = "sysPicker/PhotoPicker";
    const char UEC_ERROR_NAME_1[] = "UEC Error Name 1";
    const char UEC_ERROR_MSG_1[] = "UEC Error Msg 1";
} // namespace

class SecurityUIExtensionComponentTestNg : public testing::Test {
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
    RefPtr<SecurityUIExtensionPattern> CreateSecurityUEC();
    RefPtr<SecurityUIExtensionPattern> CreateSecurityUEC(NG::UIExtensionConfig config);
    void InvalidSession(RefPtr<SecurityUIExtensionPattern> pattern);
    void ValidSession(RefPtr<SecurityUIExtensionPattern> pattern);
    void InvalidSessionWrapper(RefPtr<SecurityUIExtensionPattern> pattern);
    void ValidSessionWrapper(RefPtr<SecurityUIExtensionPattern> pattern);
    void FireCallbacks(RefPtr<SecurityUIExtensionPattern> pattern);
};

void SecurityUIExtensionComponentTestNg::SetUp()
{
}

void SecurityUIExtensionComponentTestNg::TearDown()
{
    // clear stack after each test
    auto* stack = ViewStackProcessor::GetInstance();
    stack->ClearStack();
}

RefPtr<SecurityUIExtensionPattern> SecurityUIExtensionComponentTestNg::CreateSecurityUEC()
{
    // construct config of SecurityUEC
    OHOS::AAFwk::Want want;
    want.SetElementName(BOUNDLE_NAME, ABILITY_NAME);
    want.SetParam(ABILITY_KEY_UIEXTENSIONTYPE, ABILITY_VALUE_UIEXTENSIONTYPE);

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

    return pattern;
}

RefPtr<SecurityUIExtensionPattern> SecurityUIExtensionComponentTestNg::CreateSecurityUEC(NG::UIExtensionConfig config)
{
    // create SecurityUEC
    UIExtensionModelNG uecNG;
    config.sessionType = SessionType::SECURITY_UI_EXTENSION_ABILITY;
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
    return pattern;
}

void SecurityUIExtensionComponentTestNg::InvalidSession(RefPtr<SecurityUIExtensionPattern> pattern)
{
    CHECK_NULL_VOID(pattern);
    ValidSessionWrapper(pattern);
    auto sessionWrapper = AceType::DynamicCast<SecuritySessionWrapperImpl>(pattern->sessionWrapper_);
    CHECK_NULL_VOID(sessionWrapper);
    sessionWrapper->session_ = nullptr;
}

void SecurityUIExtensionComponentTestNg::ValidSession(RefPtr<SecurityUIExtensionPattern> pattern)
{
    CHECK_NULL_VOID(pattern);
    ValidSessionWrapper(pattern);
    auto sessionWrapper = AceType::DynamicCast<SecuritySessionWrapperImpl>(pattern->sessionWrapper_);
    CHECK_NULL_VOID(sessionWrapper);
    Rosen::SessionInfo sessionInfo;
    sessionWrapper->session_ = new Rosen::ExtensionSession(sessionInfo);
}

void SecurityUIExtensionComponentTestNg::InvalidSessionWrapper(RefPtr<SecurityUIExtensionPattern> pattern)
{
    CHECK_NULL_VOID(pattern);
    pattern->sessionWrapper_ = nullptr;
}

void SecurityUIExtensionComponentTestNg::ValidSessionWrapper(RefPtr<SecurityUIExtensionPattern> pattern)
{
    CHECK_NULL_VOID(pattern);
    pattern->sessionWrapper_ =
        AceType::MakeRefPtr<SecuritySessionWrapperImpl>(pattern, pattern->instanceId_, false,
        SessionType::SECURITY_UI_EXTENSION_ABILITY);
}

void SecurityUIExtensionComponentTestNg::FireCallbacks(RefPtr<SecurityUIExtensionPattern> pattern)
{
    CHECK_NULL_VOID(pattern);
    RefPtr<WantWrap> wantWrapPtr = AceType::MakeRefPtr<WantWrapOhos>("123", "123");
    AAFwk::WantParams wantParams;
    OHOS::AAFwk::Want want;
    pattern->FireOnRemoteReadyCallback();
    pattern->FireOnErrorCallback(1, "123", "123");
    pattern->FireOnTerminatedCallback(1, wantWrapPtr);
    pattern->FireOnReceiveCallback(wantParams);
    pattern->FireSyncCallbacks();
    pattern->FireAsyncCallbacks();
    pattern->FireBindModalCallback();
}

/**
 * @tc.name: SecurityUIExtensionComponentCreateSuccessTest
 * @tc.desc: Test create SecurityUIExtensionComponent successfully
 * @tc.type: FUNC
 */
HWTEST_F(SecurityUIExtensionComponentTestNg, SecurityUIExtensionComponentCreateSuccessTest, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreateSecurityUEC();

    ASSERT_EQ(pattern->densityDpi_, true);
    ASSERT_EQ(pattern->sessionType_, SessionType::SECURITY_UI_EXTENSION_ABILITY);
#endif
}

/**
 * @tc.name: SecurityUIExtensionComponentCreateFailedTest
 * @tc.desc: Test create SecurityUIExtensionComponent failed
 * @tc.type: FUNC
 */
HWTEST_F(SecurityUIExtensionComponentTestNg, SecurityUIExtensionComponentCreateFailedTest, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    NG::UIExtensionConfig config;
    config.sessionType = SessionType::UI_EXTENSION_ABILITY;
    UIExtensionModelNG uecNG;
    uecNG.Create(config);

    // sessionType only support SECURITY_UI_EXTENSION_ABILITY
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_EQ(frameNode, nullptr);
#endif
}

/**
 * @tc.name: SecurityUIExtensionCallbackTest
 * @tc.desc: Test callbacks
 * @tc.type: FUNC
 */
HWTEST_F(SecurityUIExtensionComponentTestNg, SecurityUIExtensionCallbackTest, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a SecurityUIExtensionComponent node and get pattern
     */
    auto pattern = CreateSecurityUEC();

    /**
     * @tc.steps: step2. check sessionWrapper
     */
    auto sessionWrapper = AceType::DynamicCast<SecuritySessionWrapperImpl>(pattern->sessionWrapper_);
    ASSERT_NE(sessionWrapper, nullptr);
    EXPECT_EQ(pattern->instanceId_, Container::CurrentId());
    EXPECT_EQ(pattern->instanceId_, sessionWrapper->instanceId_);
    EXPECT_EQ(sessionWrapper->IsSessionValid(), true);

    /**
     * @tc.steps: step3. set callbacks
     */
    std::list<std::function<void(const RefPtr<SecurityUIExtensionProxy>&)>> onSyncOnCallbackList;
    auto onSyncOnCallback = [](const RefPtr<SecurityUIExtensionProxy>&) {};
    onSyncOnCallbackList.emplace_back(onSyncOnCallback);
    pattern->SetSyncCallbacks(std::move(onSyncOnCallbackList));
    pattern->SetAsyncCallbacks(std::move(onSyncOnCallbackList));

    /**
     * @tc.steps: step4. fire callbacks
     */
    pattern->state_ = SecurityUIExtensionPattern::AbilityState::DESTRUCTION;
    FireCallbacks(pattern);

    pattern->state_ = SecurityUIExtensionPattern::AbilityState::FOREGROUND;
    InvalidSessionWrapper(pattern);
    FireCallbacks(pattern);

    ValidSession(pattern);
    FireCallbacks(pattern);

    InvalidSession(pattern);
    FireCallbacks(pattern);
#endif
}

/**
 * @tc.name: SecurityUIExtensionSessionValidTest
 * @tc.desc: Valid session, test NotifyForeground/NotifyBackground/NotifyDestroy
 * @tc.type: FUNC
 */
HWTEST_F(SecurityUIExtensionComponentTestNg, SecurityUIExtensionSessionValidTest, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a SecurityUIExtensionComponent node and get pattern
     */
    auto pattern = CreateSecurityUEC();

    /**
     * @tc.steps: step2. set component visibile and sync gemometry node
     */
    pattern->isVisible_ = true;
    const DirtySwapConfig config;
    pattern->OnSyncGeometryNode(config);

    /**
     * @tc.steps: step3. test NotifyBackground
     */
    pattern->state_ = SecurityUIExtensionPattern::AbilityState::NONE;
    pattern->NotifyBackground();
    EXPECT_EQ(pattern->state_, SecurityUIExtensionPattern::AbilityState::NONE);

    pattern->state_ = SecurityUIExtensionPattern::AbilityState::FOREGROUND;
    pattern->NotifyBackground();
    EXPECT_EQ(pattern->state_, SecurityUIExtensionPattern::AbilityState::BACKGROUND);

    /**
     * @tc.steps: step4. test NotifyForeground
     */
    pattern->NotifyForeground();
    EXPECT_EQ(pattern->state_, SecurityUIExtensionPattern::AbilityState::FOREGROUND);

    /**
     * @tc.steps: step5. when state is FOREGROUND, invoke UpdateWant, state change to FOREGROUND
     */
    OHOS::AAFwk::Want want;
    want.SetElementName("123", "456", "");
    pattern->instanceId_= 2;
    EXPECT_EQ(pattern->CheckConstraint(), true);
    pattern->UpdateWant(want);
    EXPECT_EQ(pattern->state_, SecurityUIExtensionPattern::AbilityState::FOREGROUND);

    /**
     * @tc.steps: step6. when state is BACKGROUND, invoke UpdateWant, state change to DESTRUCTION
     */
    OHOS::AAFwk::Want want2;
    want2.SetElementName("123", "789", "");
    pattern->NotifyBackground();
    pattern->UpdateWant(want2);
    EXPECT_EQ(pattern->state_, SecurityUIExtensionPattern::AbilityState::DESTRUCTION);

    /**
     * @tc.steps: step7. test NotifyDestroy, when state is not NONE or DESTRUCTION, state change to DESTRUCTION
     */
    pattern->state_ = SecurityUIExtensionPattern::AbilityState::NONE;
    pattern->NotifyDestroy();
    EXPECT_EQ(pattern->state_, SecurityUIExtensionPattern::AbilityState::NONE);

    pattern->state_ = SecurityUIExtensionPattern::AbilityState::FOREGROUND;
    pattern->NotifyDestroy();
    EXPECT_EQ(pattern->state_, SecurityUIExtensionPattern::AbilityState::DESTRUCTION);

    /**
     * @tc.steps: step8. test ToString
     */
    EXPECT_EQ(pattern->ToString(SecurityUIExtensionPattern::AbilityState::FOREGROUND), "FOREGROUND");
    EXPECT_EQ(pattern->ToString(SecurityUIExtensionPattern::AbilityState::BACKGROUND), "BACKGROUND");
    EXPECT_EQ(pattern->ToString(SecurityUIExtensionPattern::AbilityState::DESTRUCTION), "DESTRUCTION");
    EXPECT_EQ(pattern->ToString(SecurityUIExtensionPattern::AbilityState::NONE), "NONE");
#endif
}

/**
 * @tc.name: SecurityUIExtensionInvalidSessionTest
 * @tc.desc: Invalid session, test NotifyForeground/NotifyBackground/NotifyDestroy
 * @tc.type: FUNC
 */
HWTEST_F(SecurityUIExtensionComponentTestNg, SecurityUIExtensionInvalidSessionTest, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a SecurityUIExtensionComponent node and set invalid sessionWrapper
     */
    auto pattern = CreateSecurityUEC();
    InvalidSessionWrapper(pattern);

    /**
     * @tc.steps: step2. set component visibile and sync gemometry node
     */
    pattern->isVisible_ = true;
    const DirtySwapConfig config;
    pattern->OnSyncGeometryNode(config);

    /**
     * @tc.steps: step3. test NotifyBackground and NotifyForeground, state not change
     */
    pattern->state_ = SecurityUIExtensionPattern::AbilityState::NONE;
    pattern->NotifyForeground();
    EXPECT_EQ(pattern->state_, SecurityUIExtensionPattern::AbilityState::NONE);
    pattern->NotifyBackground();
    EXPECT_EQ(pattern->state_, SecurityUIExtensionPattern::AbilityState::NONE);

    /**
     * @tc.steps: step4. UpdateWant has not effect, state not change
     */
    OHOS::AAFwk::Want want;
    want.SetElementName("123", "456", "");
    pattern->instanceId_= 1;
    EXPECT_EQ(pattern->CheckConstraint(), false);
    pattern->UpdateWant(want);
    EXPECT_EQ(pattern->state_, SecurityUIExtensionPattern::AbilityState::NONE);

    /**
     * @tc.steps: step5. test NotifyDestroy, state not change
     */
    pattern->NotifyDestroy();
    EXPECT_EQ(pattern->state_, SecurityUIExtensionPattern::AbilityState::NONE);
#endif
}

/**
 * @tc.name: SecurityUIExtensionOnConnectTest
 * @tc.desc: Test pattern OnConnect
 * @tc.type: FUNC
 */
HWTEST_F(SecurityUIExtensionComponentTestNg, SecurityUIExtensionOnConnectTest, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a SecurityUIExtensionComponent Node
     */
    auto pattern = CreateSecurityUEC();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();

    /**
     * @tc.steps: step2. test OnConnect
     */
    auto host = pattern->GetHost();
    EXPECT_NE(host, nullptr);
    auto&& opts = host->GetLayoutProperty()->GetSafeAreaExpandOpts();
    auto surfaceNode = pattern->sessionWrapper_->GetSurfaceNode();
    EXPECT_NE(surfaceNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->safeAreaExpandOpts_ = nullptr;
    pattern->OnConnect();

    layoutProperty->safeAreaExpandOpts_ = std::make_unique<SafeAreaExpandOpts>();
    ASSERT_NE(opts, nullptr);
    EXPECT_EQ(opts->Expansive(), false);
    pattern->OnConnect();

    layoutProperty->safeAreaExpandOpts_->type = SAFE_AREA_TYPE_SYSTEM;
    layoutProperty->safeAreaExpandOpts_->edges = SAFE_AREA_EDGE_ALL;
    EXPECT_EQ(opts->Expansive(), true);
    pattern->OnConnect();

    ValidSession(pattern);
    pattern->OnConnect();

    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->currentFocus_ = true;
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pattern->OnConnect();

    focusHub->currentFocus_ = false;
    pattern->OnConnect();

    focusHub = nullptr;
    pattern->OnConnect();

    pattern->sessionWrapper_ = nullptr;
    pattern->OnConnect();
#endif
}

/**
 * @tc.name: SecurityUIExtensionOnErrorTest
 * @tc.desc: Test pattern OnError
 * @tc.type: FUNC
 */
HWTEST_F(SecurityUIExtensionComponentTestNg, SecurityUIExtensionOnErrorTest, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a SecurityUIExtensionComponent Node
     */
    auto pattern = CreateSecurityUEC();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    /**
     * @tc.steps: step2. Test onError
     */
    auto onError =
        [](int32_t code, const std::string& name, const std::string& message) {
            EXPECT_EQ(code, CODE);
            EXPECT_EQ(name, NAME);
            EXPECT_EQ(message, MSG);
        };
    pattern->SetOnErrorCallback(std::move(onError));
    pattern->FireOnErrorCallback(CODE, NAME, MSG);
    EXPECT_EQ(pattern->state_, SecurityUIExtensionPattern::AbilityState::NONE);
#endif
}

/**
 * @tc.name: SecurityUIExtensionHandleKeyEventValidSession
 * @tc.desc: Valid session, test pattern KeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(SecurityUIExtensionComponentTestNg, SecurityUIExtensionHandleKeyEventValidSession, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a SecurityUIExtensionComponent node and create valid session
     */
    auto pattern = CreateSecurityUEC();
    ValidSession(pattern);

    /**
     * @tc.steps: step2. handle event
     */
    KeyEvent event;
    pattern->HandleKeyEvent(event);
    pattern->HandleFocusEvent();
    pattern->DispatchFocusActiveEvent(true);
    pattern->DispatchFocusState(true);
    pattern->DispatchFocusActiveEvent(true);
    pattern->DispatchFocusState(true);
    pattern->HandleBlurEvent();
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto focusManager = pipeline->GetOrCreateFocusManager();
    ASSERT_NE(focusManager, nullptr);
    focusManager->isFocusActive_ = true;
    ASSERT_TRUE(pipeline->GetIsFocusActive());
    pattern->HandleFocusEvent();
#endif
}

/**
 * @tc.name: SeucurityUIExtensionHandleKeyEventInvalidSession
 * @tc.desc: Invalid session, test pattern KeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(SecurityUIExtensionComponentTestNg, SeucurityUIExtensionHandleKeyEventInvalidSession, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a SecurityUIExtensionComponent node and create invali session
     */
    auto pattern = CreateSecurityUEC();
    InvalidSession(pattern);

    /**
     * @tc.steps: step2. handle event
     */
    KeyEvent event;
    pattern->HandleKeyEvent(event);
    pattern->HandleFocusEvent();
    pattern->DispatchFocusActiveEvent(true);
    pattern->DispatchFocusState(true);
    pattern->DispatchFocusActiveEvent(true);
    pattern->DispatchFocusState(true);
    pattern->HandleBlurEvent();
#endif
}

/**
 * @tc.name: SecurityUIExtensionHandleTouchEventValidSession
 * @tc.desc: Valid session, test pattern TouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(SecurityUIExtensionComponentTestNg, SecurityUIExtensionHandleTouchEventValidSession, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a SecurityUIExtensionComponent node and create valid session
     */
    auto pattern = CreateSecurityUEC();
    ValidSession(pattern);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();

    /**
     * @tc.steps: step2. test HandleTouchEvent
     */
    TouchEventInfo touchEventInfo("onTouch");
    touchEventInfo.SetSourceDevice(SourceType::MOUSE);
    pattern->HandleTouchEvent(touchEventInfo);
    touchEventInfo.SetSourceDevice(SourceType::TOUCH);
    touchEventInfo.SetPointerEvent(nullptr);
    pattern->HandleTouchEvent(touchEventInfo);
    std::shared_ptr<MMI::PointerEvent> pointerEvent = std::make_shared<MMI::PointerEvent>(1);
    pointerEvent->SetPointerAction(MMI::PointerEvent::POINTER_ACTION_UP);
    touchEventInfo.SetPointerEvent(pointerEvent);
    pattern->HandleTouchEvent(touchEventInfo);

    auto pipeline = PipelineBase::GetCurrentContext();
    pipeline->onFocus_ = false;
    ASSERT_NE(pipeline, nullptr);
    pipeline->window_ = nullptr;
    ASSERT_FALSE(pipeline->IsWindowFocused());
    pattern->HandleTouchEvent(touchEventInfo);

    pipeline->onFocus_ = true;
    ASSERT_TRUE(pipeline->IsWindowFocused());
    auto focusHub = frameNode->GetFocusHub();
    focusHub->currentFocus_ = true;
    pattern->HandleTouchEvent(touchEventInfo);
    focusHub->currentFocus_ = false;
    pattern->HandleTouchEvent(touchEventInfo);
    
    pointerEvent->SetPointerAction(MMI::PointerEvent::POINTER_ACTION_AXIS_BEGIN);
    pattern->HandleTouchEvent(touchEventInfo);
    pointerEvent->SetPointerAction(MMI::PointerEvent::POINTER_ACTION_LEAVE_WINDOW);
    pattern->HandleTouchEvent(touchEventInfo);
    pattern->DispatchPointerEvent(pointerEvent);
#endif
}

/**
 * @tc.name: SecurityUIExtensionHandleTouchEventInvalidSession
 * @tc.desc: Invalid session, test pattern TouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(SecurityUIExtensionComponentTestNg, SecurityUIExtensionHandleTouchEventInvalidSession, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a SecurityUIExtensionComponent node and create invalid session
     */
    auto pattern = CreateSecurityUEC();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    InvalidSession(pattern);

    /**
     * @tc.steps: step2. test HandleTouchEvent
     */
    TouchEventInfo touchEventInfo("onTouch");
    touchEventInfo.SetSourceDevice(SourceType::MOUSE);
    pattern->HandleTouchEvent(touchEventInfo);
    touchEventInfo.SetSourceDevice(SourceType::TOUCH);
    touchEventInfo.SetPointerEvent(nullptr);
    pattern->HandleTouchEvent(touchEventInfo);
    std::shared_ptr<MMI::PointerEvent> pointerEvent = std::make_shared<MMI::PointerEvent>(1);
    pointerEvent->SetPointerAction(MMI::PointerEvent::POINTER_ACTION_UP);
    touchEventInfo.SetPointerEvent(pointerEvent);
    pattern->HandleTouchEvent(touchEventInfo);
    auto pipeline = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->window_ = nullptr;
    pattern->HandleTouchEvent(touchEventInfo);
    pipeline->onFocus_ = false;
    pattern->HandleTouchEvent(touchEventInfo);
    pipeline->onFocus_ = true;
    pattern->HandleTouchEvent(touchEventInfo);
    auto focusHub = frameNode->GetFocusHub();
    focusHub->currentFocus_ = false;
    pattern->HandleTouchEvent(touchEventInfo);
    focusHub->currentFocus_ = true;
    pointerEvent->SetPointerAction(MMI::PointerEvent::POINTER_ACTION_LEAVE_WINDOW);
    pattern->HandleTouchEvent(touchEventInfo);
    pattern->DispatchPointerEvent(pointerEvent);
#endif
}

/**
 * @tc.name: SeucurityUIExtensionHandleMouseEventValidSession
 * @tc.desc: Valid session, test pattern MouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(SecurityUIExtensionComponentTestNg, SeucurityUIExtensionHandleMouseEventValidSession, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a SecurityUIExtensionComponent node and create valid session
     */
    auto pattern = CreateSecurityUEC();
    ValidSession(pattern);

    /**
     * @tc.steps: step2. test HandleMouseEvent
     */
    MouseInfo mouseInfo;
    mouseInfo.SetSourceDevice(SourceType::TOUCH);
    pattern->HandleMouseEvent(mouseInfo);
    mouseInfo.SetSourceDevice(SourceType::MOUSE);
    pattern->HandleMouseEvent(mouseInfo);
    mouseInfo.SetPullAction(MouseAction::PULL_MOVE);
    pattern->HandleMouseEvent(mouseInfo);
    mouseInfo.SetPullAction(MouseAction::PULL_UP);
    pattern->HandleMouseEvent(mouseInfo);
    mouseInfo.SetPullAction(MouseAction::PRESS);
    pattern->HandleMouseEvent(mouseInfo);

    std::shared_ptr<MMI::PointerEvent> pointerEvent = std::make_shared<MMI::PointerEvent>(1);
    mouseInfo.SetPointerEvent(pointerEvent);
    pattern->HandleMouseEvent(mouseInfo);

    mouseInfo.SetAction(MouseAction::HOVER);
    pattern->HandleMouseEvent(mouseInfo);
    mouseInfo.SetAction(MouseAction::PRESS);
    pattern->HandleMouseEvent(mouseInfo);

    /**
     * @tc.steps: step3. test DispatchDisplayArea
     */
    pattern->HandleHoverEvent(true);
    pattern->HandleHoverEvent(false);
    pattern->displayArea_ = RectF(0.0, 0.0, 0.0, 0.0);
    pattern->DispatchDisplayArea(true);
    pattern->DispatchDisplayArea(false);
    pattern->displayArea_ = RectF(100.0, 100.0, 100.0, 100.0);
    pattern->DispatchDisplayArea(true);
    pattern->DispatchDisplayArea(false);
    auto sessionWrapper = AceType::DynamicCast<SecuritySessionWrapperImpl>(pattern->sessionWrapper_);
    EXPECT_NE(sessionWrapper, nullptr);
    pattern->isVisible_ = true;
    pattern->OnWindowHide();
    pattern->OnWindowShow();
    pattern->isVisible_ = false;
    pattern->OnWindowHide();
    pattern->OnWindowShow();
    DirtySwapConfig config;
    pattern->OnSyncGeometryNode(config);
#endif
}

/**
 * @tc.name: SeucurityUIExtensionHandleMouseEventInvalidSession
 * @tc.desc: Invalid session, test pattern MouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(SecurityUIExtensionComponentTestNg, SeucurityUIExtensionHandleMouseEventInvalidSession, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a SecurityUIExtensionComponent node and create invalid session
     */
    auto pattern = CreateSecurityUEC();
    InvalidSession(pattern);

    /**
     * @tc.steps: step2. handle mouse event
     */
    MouseInfo mouseInfo;
    mouseInfo.SetSourceDevice(SourceType::MOUSE);
    pattern->HandleMouseEvent(mouseInfo);
    mouseInfo.SetSourceDevice(SourceType::TOUCH);
    pattern->HandleMouseEvent(mouseInfo);
    mouseInfo.SetPullAction(MouseAction::PULL_MOVE);
    pattern->HandleMouseEvent(mouseInfo);
    mouseInfo.SetPullAction(MouseAction::PULL_UP);
    pattern->HandleMouseEvent(mouseInfo);
    mouseInfo.SetPullAction(MouseAction::PRESS);
    pattern->HandleMouseEvent(mouseInfo);
    pattern->HandleHoverEvent(true);
    pattern->HandleHoverEvent(false);
    pattern->displayArea_ = RectF(0.0, 0.0, 0.0, 0.0);
    pattern->DispatchDisplayArea(true);
    pattern->DispatchDisplayArea(false);
    pattern->displayArea_ = RectF(100.0, 100.0, 100.0, 100.0);
    pattern->DispatchDisplayArea(true);
    pattern->DispatchDisplayArea(false);
    auto sessionWrapper = AceType::DynamicCast<SecuritySessionWrapperImpl>(pattern->sessionWrapper_);
    EXPECT_NE(sessionWrapper, nullptr);
    pattern->isVisible_ = true;
    pattern->OnWindowHide();
    pattern->OnWindowShow();
    pattern->isVisible_ = false;
    pattern->OnWindowHide();
    pattern->OnWindowShow();
#endif
}

/**
 * @tc.name: SecurityUIExtensionPlaceholderTest
 * @tc.desc: Test pattern SetPlaceholder/MountPlaceholder/RemovePlaceholder
 * @tc.type: FUNC
 */
HWTEST_F(SecurityUIExtensionComponentTestNg, SecurityUIExtensionPlaceholderTest, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a SecurityUIExtensionComponent node
     */
    auto uiExtensionNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto uiExtensionNode = FrameNode::GetOrCreateFrameNode(
        V2::UI_EXTENSION_COMPONENT_ETS_TAG, uiExtensionNodeId,
        []() { return AceType::MakeRefPtr<SecurityUIExtensionPattern>(); });
    ASSERT_NE(uiExtensionNode, nullptr);
    EXPECT_EQ(uiExtensionNode->GetTag(), V2::UI_EXTENSION_COMPONENT_ETS_TAG);
    auto pattern = uiExtensionNode->GetPattern<SecurityUIExtensionPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_EQ(pattern->isShowPlaceholder_, false);
    pattern->AttachToFrameNode(uiExtensionNode);

    /**
     * @tc.steps: step2. placeholderNode not set, isShowPlaceholder_ always false
     */
    pattern->OnModifyDone();
    EXPECT_EQ(pattern->isShowPlaceholder_, false);
    pattern->MountPlaceholderNode();
    EXPECT_EQ(pattern->isShowPlaceholder_, false);
    pattern->RemovePlaceholderNode();
    EXPECT_EQ(pattern->isShowPlaceholder_, false);

    /**
     * @tc.steps: step3. set placeholderNode, and test MountPlaceholderNode and RemovePlaceholderNode
     */
    auto placeholderId = ElementRegister::GetInstance()->MakeUniqueId();
    auto placeholderNode = FrameNode::GetOrCreateFrameNode(
        "placeholderNode", placeholderId, []() { return AceType::MakeRefPtr<Pattern>(); });
    pattern->SetPlaceholderNode(placeholderNode);
    pattern->MountPlaceholderNode();
    EXPECT_EQ(pattern->isShowPlaceholder_, true);
    pattern->RemovePlaceholderNode();
    EXPECT_EQ(pattern->isShowPlaceholder_, false);
    pattern->RemovePlaceholderNode();
    EXPECT_EQ(pattern->isShowPlaceholder_, false);
#endif
}

/**
 * @tc.name: SecurityUIExtensionUpdateWantTest
 * @tc.desc: Test pattern UpdateWant function
 * @tc.type: FUNC
 */
HWTEST_F(SecurityUIExtensionComponentTestNg, SecurityUIExtensionUpdateWantTest, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a SecurityUIExtensionComponent node and get pattern
     */
    auto pattern = CreateSecurityUEC();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. test UpdateWant
     */
    pattern->UpdateWant(nullptr);
    RefPtr<WantWrap> wantOhos = AceType::MakeRefPtr<WantWrapOhos>("123", "123");
    pattern->UpdateWant(wantOhos);
    auto wantOhos2 = AceType::DynamicCast<WantWrap>(wantOhos);
    pattern->UpdateWant(wantOhos2);
    EXPECT_NE(pattern, nullptr);
#endif
}

/**
 * @tc.name: SecurityUIExtensionOnWindowTest
 * @tc.desc: Test pattern onWindowShow/onWindowHide function
 * @tc.type: FUNC
 */
HWTEST_F(SecurityUIExtensionComponentTestNg, SecurityUIExtensionOnWindowTest, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a SecurityUIExtensionComponent node and get pattern
     */
    auto pattern = CreateSecurityUEC();

    /**
     * @tc.steps: step2. component is visible, OnWindowShow change to FOREGROUND; OnWindowHide change to BACKGROUND
     */
    pattern->isVisible_ = true;
    pattern->state_ = SecurityUIExtensionPattern::AbilityState::BACKGROUND;
    pattern->OnWindowShow();
    ASSERT_EQ(pattern->state_, SecurityUIExtensionPattern::AbilityState::FOREGROUND);
    pattern->OnWindowHide();
    ASSERT_EQ(pattern->state_, SecurityUIExtensionPattern::AbilityState::BACKGROUND);

    /**
     * @tc.steps: step3. component is not visible, OnWindowShow/OnWindowHide, state not change
     */
    pattern->isVisible_ = false;
    pattern->OnWindowShow();
    ASSERT_EQ(pattern->state_, SecurityUIExtensionPattern::AbilityState::BACKGROUND);
    pattern->state_ = SecurityUIExtensionPattern::AbilityState::FOREGROUND;
    pattern->OnWindowHide();
    ASSERT_EQ(pattern->state_, SecurityUIExtensionPattern::AbilityState::FOREGROUND);
#endif
}

/**
 * @tc.name: SecurityUIExtensionVisibleTest
 * @tc.desc: Test pattern onVisibleChange function
 * @tc.type: FUNC
 */
HWTEST_F(SecurityUIExtensionComponentTestNg, SecurityUIExtensionVisibleTest, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a SecurityUIExtensionComponent node and get pattern
     */
    auto pattern = CreateSecurityUEC();

    /**
     * @tc.steps: step2. OnVisibleChange false, state change to BACKGROUND
     */
    pattern->state_ = SecurityUIExtensionPattern::AbilityState::FOREGROUND;
    pattern->OnVisibleChange(false);
    EXPECT_FALSE(pattern->isVisible_);
    ASSERT_EQ(pattern->state_, SecurityUIExtensionPattern::AbilityState::BACKGROUND);

    /**
     * @tc.steps: step3. OnVisibleChange true, state change to FOREGROUND
     */
    pattern->OnVisibleChange(true);
    EXPECT_TRUE(pattern->isVisible_);
    ASSERT_EQ(pattern->state_, SecurityUIExtensionPattern::AbilityState::FOREGROUND);
#endif
}

/**
 * @tc.name: SecurityUIExtensionDpiTest
 * @tc.desc: Test pattern SetDensityDpi/GetDensityDpi function
 * @tc.type: FUNC
 */
HWTEST_F(SecurityUIExtensionComponentTestNg, SecurityUIExtensionDpiTest, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a SecurityUIExtensionComponent node and get pattern
     */
    auto pattern = CreateSecurityUEC();

    /**
     * @tc.steps: step2. SetDensityDpi false
     */
    pattern->SetDensityDpi(false);
    EXPECT_FALSE(pattern->GetDensityDpi());

    /**
     * @tc.steps: step3. SetDensityDpi true
     */
    pattern->SetDensityDpi(true);
    EXPECT_TRUE(pattern->GetDensityDpi());
#endif
}

/**
 * @tc.name: SecurityUIExtensionDpiTest
 * @tc.desc: Test pattern Initialize and CreateLayoutAlgorithm
 * @tc.type: FUNC
 */
HWTEST_F(SecurityUIExtensionComponentTestNg, InitializeTest001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a SecurityUIExtensionComponent node and get pattern
     */
    auto pattern = CreateSecurityUEC();
    NG::UIExtensionConfig config;

    /**
     * @tc.steps: step2. sessionWrapper_ is null ptr
     */
    pattern->sessionWrapper_ = nullptr;
    pattern->Initialize(config);

    /**
     * @tc.steps: step3. sessionWrapper_ is not null ptr
     */
    pattern->sessionWrapper_ =
        AceType::MakeRefPtr<SecuritySessionWrapperImpl>(pattern, pattern->instanceId_, false,
        SessionType::SECURITY_UI_EXTENSION_ABILITY);
    ASSERT_NE(pattern->sessionWrapper_, nullptr);
    pattern->Initialize(config);

    /**
     * @tc.steps: step3. test CreateLayoutAlgorithm
     */
    ASSERT_NE(pattern->CreateLayoutAlgorithm(), nullptr);
#endif
}

/**
 * @tc.name: SecurityUIExtensionDpiTest
 * @tc.desc: Test pattern OnExtensionDetachToDisplay
 * @tc.type: FUNC
 */
HWTEST_F(SecurityUIExtensionComponentTestNg, OnExtensionDetachToDisplayTest001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a SecurityUIExtensionComponent node and get pattern
     */
    auto pattern = CreateSecurityUEC();

    /**
     * @tc.steps: step2. contentNode_  is null ptr
     */
    pattern->contentNode_  = nullptr;
    pattern->OnExtensionDetachToDisplay();

    /**
     * @tc.steps: step3. contentNode_  is not null ptr
     */
    auto placeholderId = ElementRegister::GetInstance()->MakeUniqueId();
    auto placeholderNode = FrameNode::GetOrCreateFrameNode(
        "placeholderNode", placeholderId, []() { return AceType::MakeRefPtr<Pattern>(); });
    pattern->contentNode_  = placeholderNode;
    ASSERT_NE(pattern->contentNode_, nullptr);
    pattern->OnExtensionDetachToDisplay();
#endif
}

/**
 * @tc.name: SecurityUIExtensionDpiTest
 * @tc.desc: Test pattern DispatchFollowHostDensity and OnDpiConfigurationUpdate
 * @tc.type: FUNC
 */
HWTEST_F(SecurityUIExtensionComponentTestNg, DispatchFollowHostDensityTest001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a SecurityUIExtensionComponent node and get pattern
     */
    auto pattern = CreateSecurityUEC();

    /**
     * @tc.steps: step2. test DispatchFollowHostDensity
     */
    bool densityDpi = true;
    pattern->densityDpi_ = false;
    pattern->DispatchFollowHostDensity(densityDpi);
    ASSERT_TRUE(pattern->densityDpi_);

    densityDpi = false;
    pattern->DispatchFollowHostDensity(densityDpi);
    ASSERT_FALSE(pattern->densityDpi_);

    /**
     * @tc.steps: step3. test OnDpiConfigurationUpdate
     */
    ASSERT_FALSE(pattern->GetDensityDpi());
    pattern->OnDpiConfigurationUpdate();

    densityDpi = true;
    pattern->DispatchFollowHostDensity(densityDpi);
    ASSERT_TRUE(pattern->GetDensityDpi());
    pattern->OnDpiConfigurationUpdate();
#endif
}

/**
 * @tc.name: SecurityUIExtensionDpiTest
 * @tc.desc: Test pattern OnLanguageConfigurationUpdate, OnColorConfigurationUpdate and GetSessionId
 * @tc.type: FUNC
 */
HWTEST_F(SecurityUIExtensionComponentTestNg, OnLanguageConfigurationUpdateTest001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a SecurityUIExtensionComponent node and get pattern
     */
    auto pattern = CreateSecurityUEC();
    pattern->sessionWrapper_ = nullptr;

    /**
     * @tc.steps: step2. sessionWrapper_ is nullptr
     */
    pattern->OnLanguageConfigurationUpdate();
    pattern->OnColorConfigurationUpdate();
    ASSERT_EQ(pattern->GetSessionId(), 0);

    /**
     * @tc.steps: step3. sessionWrapper_ is not nullptr
     */
    pattern->sessionWrapper_ =
        AceType::MakeRefPtr<SecuritySessionWrapperImpl>(pattern, pattern->instanceId_, false,
        SessionType::SECURITY_UI_EXTENSION_ABILITY);
    ASSERT_NE(pattern->sessionWrapper_, nullptr);
    pattern->OnLanguageConfigurationUpdate();
    pattern->OnColorConfigurationUpdate();
    ASSERT_EQ(pattern->GetSessionId(), pattern->sessionWrapper_->GetSessionId());
#endif
}

/**
 * @tc.name: SecurityUIExtensionDpiTest
 * @tc.desc: Test pattern DumpInfo and DumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(SecurityUIExtensionComponentTestNg, DumpInfoTest001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a SecurityUIExtensionComponent node and get pattern
     */
    auto pattern = CreateSecurityUEC();

    /**
     * @tc.steps: step2. test DumpInfo
     */
    pattern->platformEventProxy_ = nullptr;
    pattern->DumpInfo();

    pattern->platformEventProxy_ = AceType::MakeRefPtr<PlatformEventProxy>();
    ASSERT_NE(pattern->platformEventProxy_, nullptr);
    pattern->DumpInfo();

    /**
     * @tc.steps: step3. test DumpInfo with one param
     */
    std::string testJson = "";
    std::unique_ptr<JsonValue> testValue = JsonUtil::ParseJsonString(testJson);

    pattern->platformEventProxy_ = nullptr;
    pattern->DumpInfo(testValue);

    pattern->platformEventProxy_ = AceType::MakeRefPtr<PlatformEventProxy>();
    ASSERT_NE(pattern->platformEventProxy_, nullptr);
    pattern->DumpInfo(testValue);
#endif
}

/**
 * @tc.name: SecurityUIExtensionEventTest
 * @tc.desc: Test pattern Test OnExtensionEvent, OnUeaAccessibilityEventAsync
 * @tc.type: FUNC
 */
HWTEST_F(SecurityUIExtensionComponentTestNg, SecurityUIExtensionEventTest, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    const int32_t IGNORE_POSITION_TRANSITION_SWITCH = -990;
    auto context = NG::PipelineContext::GetCurrentContext();
    context->instanceId_ = IGNORE_POSITION_TRANSITION_SWITCH;
    /**
     * @tc.steps: step1. construct a UIExtensionComponent Node
     */
    auto uiExtensionNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto uiExtensionNode = FrameNode::GetOrCreateFrameNode(
        V2::UI_EXTENSION_COMPONENT_ETS_TAG, uiExtensionNodeId,
        []() { return AceType::MakeRefPtr<SecurityUIExtensionPattern>(); });
    ASSERT_NE(uiExtensionNode, nullptr);
    EXPECT_EQ(uiExtensionNode->GetTag(), V2::UI_EXTENSION_COMPONENT_ETS_TAG);
    auto pattern = uiExtensionNode->GetPattern<SecurityUIExtensionPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. test OnExtensionEvent
     */
    UIExtCallbackEventId eventId = UIExtCallbackEventId::ON_AREA_CHANGED;
    pattern->OnExtensionEvent(eventId);
    eventId = UIExtCallbackEventId::ON_UEA_ACCESSIBILITY_READY;
    pattern->OnExtensionEvent(eventId);

    /**
     * @tc.steps: step3. test OnUeaAccessibilityEventAsync
     */
    pattern->AttachToFrameNode(uiExtensionNode);
    NG::UIExtensionConfig config;
    config.sessionType = SessionType::SECURITY_UI_EXTENSION_ABILITY;
    config.transferringCaller = true;
    config.densityDpi = true;
    pattern->Initialize(config);
    ASSERT_NE(pattern->sessionWrapper_, nullptr);
    ASSERT_EQ(pattern->accessibilityChildTreeCallback_, nullptr);
    pattern->OnUeaAccessibilityEventAsync();

    pattern->accessibilityChildTreeCallback_ = std::make_shared<PlatformAccessibilityChildTreeCallback>(pattern, 1);
    ASSERT_NE(pattern->accessibilityChildTreeCallback_, nullptr);

    auto frameNode = pattern->frameNode_.Upgrade();
    ASSERT_NE(frameNode, nullptr);
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    ASSERT_EQ(accessibilityProperty->GetChildTreeId(), -1);
    pattern->OnUeaAccessibilityEventAsync();

    pattern->InitializeAccessibility();
    pattern->OnSetAccessibilityChildTree(1, 1);
    pattern->OnAccessibilityChildTreeRegister(1, 1, 1);
    pattern->OnAccessibilityChildTreeDeregister();
    EXPECT_EQ(accessibilityProperty->GetChildTreeId(), 1);
    pattern->OnUeaAccessibilityEventAsync();

    pattern->frameNode_ = nullptr;
    ASSERT_EQ(pattern->frameNode_.Upgrade(), nullptr);
    pattern->OnUeaAccessibilityEventAsync();
#endif
}

/**
 * @tc.name: SecurityUIExtensionChildTreeTest
 * @tc.desc: Test pattern about child tree
 * @tc.type: FUNC
 */
HWTEST_F(SecurityUIExtensionComponentTestNg, SecurityUIExtensionChildTreeTest, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto uiExtensionNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto uiExtensionNode = FrameNode::GetOrCreateFrameNode(
        V2::UI_EXTENSION_COMPONENT_ETS_TAG, uiExtensionNodeId,
        []() { return AceType::MakeRefPtr<SecurityUIExtensionPattern>(); });
    ASSERT_NE(uiExtensionNode, nullptr);
    EXPECT_EQ(uiExtensionNode->GetTag(), V2::UI_EXTENSION_COMPONENT_ETS_TAG);
    auto pattern = uiExtensionNode->GetPattern<SecurityUIExtensionPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->AttachToFrameNode(uiExtensionNode);
    pattern->OnModifyDone();
    auto property = uiExtensionNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(property, nullptr);
    pattern->InitializeAccessibility();
    pattern->OnSetAccessibilityChildTree(1, 1);
    pattern->OnAccessibilityChildTreeRegister(1, 1, 1);
    pattern->OnAccessibilityChildTreeDeregister();
    EXPECT_EQ(property->GetChildWindowId(), 1);
    EXPECT_EQ(property->GetChildTreeId(), 1);

    uiExtensionNode->accessibilityProperty_ = nullptr;
    InvalidSessionWrapper(pattern);
    pattern->InitializeAccessibility();
    pattern->OnSetAccessibilityChildTree(1, 1);
    pattern->OnAccessibilityChildTreeRegister(1, 1, 1);
    pattern->OnAccessibilityChildTreeDeregister();
    std::vector<std::string> params;
    std::vector<std::string> info;
    pattern->OnAccessibilityDumpChildInfo(params, info);
    EXPECT_EQ(params.size(), 0);
    pattern->accessibilityChildTreeCallback_ = std::make_shared<PlatformAccessibilityChildTreeCallback>(pattern, 1);
    pattern->InitializeAccessibility();
#endif
}

/**
 * @tc.name: SecurityUIExtensionChildTreeCallbackTest
 * @tc.desc: Test OnRegister, OnDeregister, OnSetChildTree, OnDumpChildInfo, OnClearRegisterFlag
 * @tc.type: FUNC
 */
HWTEST_F(SecurityUIExtensionComponentTestNg, SecurityUIExtensionChildTreeCallbackTest, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct an PlatformAccessibilityChildTreeCallback
     */
    auto uiExtensionNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto uiExtensionNode = FrameNode::GetOrCreateFrameNode(
        V2::UI_EXTENSION_COMPONENT_ETS_TAG, uiExtensionNodeId,
        []() { return AceType::MakeRefPtr<SecurityUIExtensionPattern>(); });
    ASSERT_NE(uiExtensionNode, nullptr);
    EXPECT_EQ(uiExtensionNode->GetTag(), V2::UI_EXTENSION_COMPONENT_ETS_TAG);
    auto pattern = uiExtensionNode->GetPattern<SecurityUIExtensionPattern>();
    NG::UIExtensionConfig config;
    config.sessionType = SessionType::SECURITY_UI_EXTENSION_ABILITY;
    config.transferringCaller = true;
    config.densityDpi = true;
    pattern->Initialize(config);
    ASSERT_NE(pattern, nullptr);
    ASSERT_NE(pattern->GetAccessibilitySessionAdapter(), nullptr);
    ASSERT_NE(pattern->CreateLayoutAlgorithm(), nullptr);
    PlatformAccessibilityChildTreeCallback callback = PlatformAccessibilityChildTreeCallback(pattern, 1);
    ASSERT_FALSE(callback.isReg_);

    /**
     * @tc.steps: step2. Test OnRegister
     */
    ASSERT_TRUE(callback.OnRegister(1, 1));
    ASSERT_TRUE(callback.isReg_);
    ASSERT_TRUE(callback.OnRegister(1, 1));
    auto weakPtr = WeakPtr<SecurityUIExtensionPattern>(nullptr);
    PlatformAccessibilityChildTreeCallback callbackNull = PlatformAccessibilityChildTreeCallback(weakPtr, 1);
    ASSERT_FALSE(callbackNull.OnRegister(1, 1));

    /**
     * @tc.steps: step3. Test OnDeregister
     */
    ASSERT_FALSE(callbackNull.OnDeregister());
    ASSERT_TRUE(callback.OnDeregister());
    ASSERT_FALSE(callbackNull.isReg_);
    ASSERT_TRUE(callback.OnDeregister());

    /**
     * @tc.steps: step4. Test OnSetChildTree
     */
    ASSERT_FALSE(callbackNull.OnSetChildTree(1, 1));
    ASSERT_TRUE(callback.OnSetChildTree(1, 1));

    /**
     * @tc.steps: step5. Test OnDumpChildInfo
     */
    std::vector<std::string> params;
    std::vector<std::string> info;
    ASSERT_FALSE(callbackNull.OnDumpChildInfo(params, info));
    ASSERT_TRUE(callback.OnDumpChildInfo(params, info));

    /**
     * @tc.steps: step6. Test OnClearRegisterFlag
     */
    callbackNull.OnClearRegisterFlag();
    callback.OnClearRegisterFlag();
    ASSERT_FALSE(callback.isReg_);
#endif
}

/**
 * @tc.name: SecurityUIExtensionComponentTestNg
 * @tc.desc: Test the method of pattern RegisterEventProxyFlagCallback
 * @tc.type: FUNC
 */
HWTEST_F(SecurityUIExtensionComponentTestNg, RegisterEventProxyFlagCallback, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a UIExtensionComponent Node
     */
    auto uiExtensionNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto uiExtensionNode = FrameNode::GetOrCreateFrameNode(
        V2::UI_EXTENSION_COMPONENT_ETS_TAG, uiExtensionNodeId,
        []() { return AceType::MakeRefPtr<SecurityUIExtensionPattern>(); });
    ASSERT_NE(uiExtensionNode, nullptr);
    EXPECT_EQ(uiExtensionNode->GetTag(), V2::UI_EXTENSION_COMPONENT_ETS_TAG);
    auto pattern = uiExtensionNode->GetPattern<SecurityUIExtensionPattern>();
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
* @tc.name: SecurityUIExtensionComponentTestNg
* @tc.desc: Test the method of pattern GetAccessibilityRectInfo
* @tc.type: FUNC
*/
HWTEST_F(SecurityUIExtensionComponentTestNg, GetAccessibilityRectInfo, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
    * @tc.steps: step1. construct a UIExtensionComponent Node
    */
    auto uiExtensionNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto uiExtensionNode = FrameNode::GetOrCreateFrameNode(
        V2::UI_EXTENSION_COMPONENT_ETS_TAG, uiExtensionNodeId,
        []() { return AceType::MakeRefPtr<SecurityUIExtensionPattern>(); });
    ASSERT_NE(uiExtensionNode, nullptr);
    EXPECT_EQ(uiExtensionNode->GetTag(), V2::UI_EXTENSION_COMPONENT_ETS_TAG);
    auto pattern = uiExtensionNode->GetPattern<SecurityUIExtensionPattern>();
    ASSERT_NE(pattern, nullptr);
 
    /**
      * @tc.steps: step2. test RegisterEventProxyFlagCallback
    */
    auto rectInfo = pattern->GetAccessibilityRectInfo();
    EXPECT_EQ(rectInfo.left, 0);
    pattern->TransferAccessibilityRectInfo(true);
    pattern->TransferAccessibilityRectInfo(false);

    bool isAncestorNodeGeometryChange = false;
    bool isAncestorNodeTransformChange = false;
    FrameNodeChangeInfoFlag flag = FRAME_NODE_CHANGE_GEOMETRY_CHANGE;
    pattern->OnFrameNodeChanged(flag);
    isAncestorNodeGeometryChange = pattern->IsAncestorNodeGeometryChange(flag);
    isAncestorNodeTransformChange = pattern->IsAncestorNodeTransformChange(flag);
    ASSERT_TRUE(isAncestorNodeGeometryChange);
    ASSERT_FALSE(isAncestorNodeTransformChange);
#endif
}

/**
 * @tc.name: SecurityUIExtensionComponentTestNg001
 * @tc.desc: Test the method of pattern UpdateWMSUIExtProperty
 * @tc.type: FUNC
 */
HWTEST_F(SecurityUIExtensionComponentTestNg, SecurityUIExtensionComponentTestNg001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a UIExtensionComponent Node
     */
    auto uiExtensionNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto uiExtensionNode = FrameNode::GetOrCreateFrameNode(V2::UI_EXTENSION_COMPONENT_ETS_TAG, uiExtensionNodeId,
        []() { return AceType::MakeRefPtr<SecurityUIExtensionPattern>(); });
    ASSERT_NE(uiExtensionNode, nullptr);
    EXPECT_EQ(uiExtensionNode->GetTag(), V2::UI_EXTENSION_COMPONENT_ETS_TAG);
    auto pattern = uiExtensionNode->GetPattern<SecurityUIExtensionPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. test UpdateWMSUIExtProperty
     */
    UIContentBusinessCode code = UIContentBusinessCode::UNDEFINED;
    AAFwk::Want data;
    RSSubsystemId id = RSSubsystemId::ARKUI_UIEXT;
    pattern->UpdateWMSUIExtProperty(code, data, id);
    pattern->state_ = SecurityUIExtensionPattern::AbilityState::FOREGROUND;
    pattern->UpdateWMSUIExtProperty(code, data, id);
#endif
}

/**
 * @tc.name: SecurityUIExtensionComponentTestNg002
 * @tc.desc: Test the method of pattern GetInstanceIdFromHost
 * @tc.type: FUNC
 */
HWTEST_F(SecurityUIExtensionComponentTestNg, SecurityUIExtensionComponentTestNg002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a UIExtensionComponent Node
     */
    auto uiExtensionNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto uiExtensionNode = FrameNode::GetOrCreateFrameNode(V2::UI_EXTENSION_COMPONENT_ETS_TAG, uiExtensionNodeId,
        []() { return AceType::MakeRefPtr<SecurityUIExtensionPattern>(); });
    ASSERT_NE(uiExtensionNode, nullptr);
    EXPECT_EQ(uiExtensionNode->GetTag(), V2::UI_EXTENSION_COMPONENT_ETS_TAG);
    auto pattern = uiExtensionNode->GetPattern<SecurityUIExtensionPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. test GetInstanceIdFromHost
     */
    pattern->instanceId_ = -999;
    EXPECT_EQ(pattern->GetInstanceIdFromHost(), pattern->GetHostInstanceId());
    pattern->instanceId_ = pattern->GetHostInstanceId();
    EXPECT_EQ(pattern->GetInstanceIdFromHost(), pattern->GetHostInstanceId());
#endif
}

/**
 * @tc.name: SecurityUIExtensionComponentTestNg003
 * @tc.desc: Test the method of pattern OnUIExtBusinessReceiveReply and OnUIExtBusinessReceive
 * @tc.type: FUNC
 */
HWTEST_F(SecurityUIExtensionComponentTestNg, SecurityUIExtensionComponentTestNg003, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a UIExtensionComponent Node
     */
    auto uiExtensionNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto uiExtensionNode = FrameNode::GetOrCreateFrameNode(V2::UI_EXTENSION_COMPONENT_ETS_TAG, uiExtensionNodeId,
        []() { return AceType::MakeRefPtr<SecurityUIExtensionPattern>(); });
    ASSERT_NE(uiExtensionNode, nullptr);
    EXPECT_EQ(uiExtensionNode->GetTag(), V2::UI_EXTENSION_COMPONENT_ETS_TAG);
    auto pattern = uiExtensionNode->GetPattern<SecurityUIExtensionPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. test OnUIExtBusinessReceiveReply and OnUIExtBusinessReceive
     */
    AAFwk::Want data;
    std::optional<AAFwk::Want> reply;
    auto callback = [](const AAFwk::Want& data, std::optional<AAFwk::Want>& reply) -> int32_t { return -1; };
    pattern->RegisterUIExtBusinessConsumeReplyCallback(UIContentBusinessCode::TRANSFORM_PARAM, callback);
    pattern->OnUIExtBusinessReceiveReply(UIContentBusinessCode::UNDEFINED, data, reply);
    pattern->OnUIExtBusinessReceive(UIContentBusinessCode::UNDEFINED, data);
    pattern->OnUIExtBusinessReceiveReply(UIContentBusinessCode::TRANSFORM_PARAM, data, reply);
    pattern->OnUIExtBusinessReceive(UIContentBusinessCode::TRANSFORM_PARAM, data);
#endif
}

/**
 * @tc.name: SecurityUIExtensionComponentTestNg004
 * @tc.desc: Test the method of pattern RegisterEventProxyFlagCallback
 * @tc.type: FUNC
 */
HWTEST_F(SecurityUIExtensionComponentTestNg, SecurityUIExtensionComponentTestNg004, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a UIExtensionComponent Node
     */
    auto uiExtensionNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto uiExtensionNode = FrameNode::GetOrCreateFrameNode(V2::UI_EXTENSION_COMPONENT_ETS_TAG, uiExtensionNodeId,
        []() { return AceType::MakeRefPtr<UIExtensionPattern>(); });
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

    want.SetParam("type", std::string("OccupyEvents"));
    ret = pattern->businessDataUECConsumeCallbacks_.at(UIContentBusinessCode::EVENT_PROXY)(want);
    EXPECT_EQ(ret, 0);

    want.SetParam("eventFlags", std::string("eventFlags"));
    ret = pattern->businessDataUECConsumeCallbacks_.at(UIContentBusinessCode::EVENT_PROXY)(want);
    EXPECT_EQ(ret, 0);
#endif
}

/**
 * @tc.name: SecurityUIExtensionComponentTestNg005
 * @tc.desc: Test the method of pattern RegisterEventProxyFlagCallback
 * @tc.type: FUNC
 */
HWTEST_F(SecurityUIExtensionComponentTestNg, SecurityUIExtensionComponentTestNg005, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a UIExtensionComponent Node
     */
    auto uiExtensionNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto uiExtensionNode = FrameNode::GetOrCreateFrameNode(V2::UI_EXTENSION_COMPONENT_ETS_TAG, uiExtensionNodeId,
        []() { return AceType::MakeRefPtr<UIExtensionPattern>(); });
    ASSERT_NE(uiExtensionNode, nullptr);
    EXPECT_EQ(uiExtensionNode->GetTag(), V2::UI_EXTENSION_COMPONENT_ETS_TAG);
    auto pattern = uiExtensionNode->GetPattern<UIExtensionPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. test RegisterEventProxyFlagCallback
     */
    pattern->frameNode_ = uiExtensionNode;
    ASSERT_NE(pattern->frameNode_.Upgrade(), nullptr);
    ASSERT_EQ(pattern->frameNode_.Upgrade()->GetNodeStatus(), NodeStatus::NORMAL_NODE);
    pattern->OnMountToParentDone();

    pattern->frameNode_.Upgrade()->nodeStatus_ = NodeStatus::BUILDER_NODE_OFF_MAINTREE;
    ASSERT_NE(pattern->frameNode_.Upgrade()->GetNodeStatus(), NodeStatus::NORMAL_NODE);
    pattern->OnMountToParentDone();
#endif
}

/**
 * @tc.name: SecurityUIExtensionComponentTestNg006
 * @tc.desc: Test pattern SetEventProxyFlag
 * @tc.type: FUNC
 */
HWTEST_F(SecurityUIExtensionComponentTestNg, SecurityUIExtensionComponentTestNg006, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a SecurityUIExtensionComponent Node
     */
    auto pattern = CreateSecurityUEC();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();

    /**
     * @tc.steps: step2. test SetEventProxyFlag
     */
    auto host = pattern->GetHost();
    EXPECT_NE(host, nullptr);
    pattern->platformEventProxy_ = nullptr;
    pattern->SetEventProxyFlag(static_cast<int32_t>(EventProxyFlag::EVENT_NONE));

    pattern->platformEventProxy_ = AceType::MakeRefPtr<PlatformEventProxy>();
    ASSERT_NE(pattern->platformEventProxy_, nullptr);
    pattern->SetEventProxyFlag(static_cast<int32_t>(EventProxyFlag::EVENT_PAN_GESTURE_LEFT));

    pattern->platformEventProxy_ = nullptr;
    pattern->SetEventProxyFlag(static_cast<int32_t>(EventProxyFlag::EVENT_PAN_GESTURE_LEFT));
#endif
}

/**
 * @tc.name: SecurityUIExtensionComponentTestNg007
 * @tc.desc: Test pattern HandleKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(SecurityUIExtensionComponentTestNg, SecurityUIExtensionComponentTestNg007, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a SecurityUIExtensionComponent Node
     */
    auto pattern = CreateSecurityUEC();
    ValidSessionWrapper(pattern);

    /**
     * @tc.steps: step2. test HandleKeyEvent
     */
    KeyEvent event;
    pattern->HandleKeyEvent(event);

    event.code = KeyCode::KEY_DPAD_LEFT;
    event.pressedCodes = { KeyCode::KEY_TAB, KeyCode::KEY_MOVE_HOME, KeyCode::KEY_MOVE_END };
    EXPECT_TRUE(event.IsDirectionalKey());
    EXPECT_TRUE(event.IsKey({ KeyCode::KEY_MOVE_END }));
    pattern->HandleKeyEvent(event);

    event.pressedCodes = { KeyCode::KEY_TAB, KeyCode::KEY_MOVE_END, KeyCode::KEY_MOVE_HOME };
    EXPECT_TRUE(event.IsKey({ KeyCode::KEY_MOVE_HOME }));
    pattern->HandleKeyEvent(event);

    event.pressedCodes = { KeyCode::KEY_MOVE_HOME, KeyCode::KEY_MOVE_END, KeyCode::KEY_TAB };
    EXPECT_TRUE(event.IsKey({ KeyCode::KEY_TAB }));
    pattern->HandleKeyEvent(event);

    event.pressedCodes = { KeyCode::KEY_SHIFT_LEFT, KeyCode::KEY_TAB };
    EXPECT_TRUE(event.IsShiftWith(KeyCode::KEY_TAB));
    pattern->HandleKeyEvent(event);

    event.code = KeyCode::KEY_ESCAPE;
    EXPECT_TRUE(event.IsEscapeKey());
    pattern->HandleKeyEvent(event);
#endif
}

/**
 * @tc.name: SecurityUIExtensionComponentMemberVariablesTestNg
 * @tc.desc: Test securityUIExtension pattern base member variables
 * @tc.type: FUNC
 */
HWTEST_F(SecurityUIExtensionComponentTestNg, SecurityUIExtensionComponentMemberVariablesTestNg, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a SecurityUIExtensionComponent Node
     */
    OHOS::AAFwk::Want want;
    want.SetElementName(BOUNDLE_NAME, ABILITY_NAME);
    want.SetParam(ABILITY_KEY_UIEXTENSIONTYPE, ABILITY_VALUE_UIEXTENSIONTYPE);
    auto placeholderId = ElementRegister::GetInstance()->MakeUniqueId();
    auto placeholderNode = FrameNode::GetOrCreateFrameNode(
        "placeholderNode", placeholderId, []() { return AceType::MakeRefPtr<Pattern>(); });
    NG::UIExtensionConfig config;
    config.wantWrap = AceType::MakeRefPtr<WantWrapOhos>(want);
    config.placeholderNode = placeholderNode;
    config.sessionType = SessionType::SECURITY_UI_EXTENSION_ABILITY;
    config.transferringCaller = true;
    config.densityDpi = true;
    auto pattern = CreateSecurityUEC(config);
    ValidSessionWrapper(pattern);
    /**
     * @tc.steps: step2. test base member variables
     */
    ASSERT_NE(pattern, nullptr);
    EXPECT_EQ(pattern->isVisible_, true);
    EXPECT_NE(pattern->placeholderNode_, nullptr);
    EXPECT_EQ(pattern->sessionType_, config.sessionType);
    EXPECT_EQ(pattern->densityDpi_, config.densityDpi);
    EXPECT_EQ(pattern->contentNode_, nullptr);
#endif
}

/**
 * @tc.name: SecurityUIExtensionComponentLifeCycleTestNg_1
 * @tc.desc: Test securityUIExtension pattern life cycle OnTerminated
 * @tc.type: FUNC
 */
HWTEST_F(SecurityUIExtensionComponentTestNg, SecurityUIExtensionComponentLifeCycleTestNg_1, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a SecurityUIExtensionComponent Node
     */
    auto pattern = CreateSecurityUEC();
    ValidSessionWrapper(pattern);
    auto host = pattern->GetHost();
    ASSERT_NE(host, nullptr);
    /**
     * @tc.steps: step2. test Life Cycle OnConnect
     */
    pattern->OnConnect();
    EXPECT_NE(pattern->contentNode_, nullptr);
    ASSERT_NE(pattern->sessionWrapper_, nullptr);
    EXPECT_TRUE(pattern->sessionWrapper_->IsSessionValid());
    /**
     * @tc.steps: step3. test Life Cycle NotifyForeground
     */
    pattern->NotifyForeground();
    EXPECT_EQ(pattern->state_, SecurityUIExtensionPattern::AbilityState::FOREGROUND);
    /**
     * @tc.steps: step4. test Life Cycle OnWindowHide
     */
    pattern->OnWindowHide();
    EXPECT_EQ(pattern->state_, SecurityUIExtensionPattern::AbilityState::BACKGROUND);
    /**
     * @tc.steps: step5. test Life Cycle OnWindowShow
     */
    pattern->OnWindowShow();
    EXPECT_EQ(pattern->state_, SecurityUIExtensionPattern::AbilityState::FOREGROUND);
    /**
     * @tc.steps: step6. test Life Cycle OnVisibleChange false
     */
    pattern->OnVisibleChange(false);
    EXPECT_EQ(pattern->state_, SecurityUIExtensionPattern::AbilityState::BACKGROUND);
    /**
     * @tc.steps: step7. test Life Cycle OnVisibleChange true
     */
    pattern->OnVisibleChange(true);
    EXPECT_EQ(pattern->state_, SecurityUIExtensionPattern::AbilityState::FOREGROUND);
    /**
     * @tc.steps: step8. test Life Cycle OnTerminated
     */
    pattern->FireOnTerminatedCallback(0, nullptr);
    EXPECT_EQ(pattern->state_, SecurityUIExtensionPattern::AbilityState::DESTRUCTION);
    EXPECT_EQ(host->TotalChildCount(), 0);
#endif
}

/**
 * @tc.name: SecurityUIExtensionComponentLifeCycleTestNg_2
 * @tc.desc: Test securityUIExtension pattern life cycle FireOnErrorCallback
 * @tc.type: FUNC
 */
HWTEST_F(SecurityUIExtensionComponentTestNg, SecurityUIExtensionComponentLifeCycleTestNg_2, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a SecurityUIExtensionComponent Node
     */
    OHOS::AAFwk::Want want1;
    want1.SetElementName(BOUNDLE_NAME, ABILITY_NAME);
    want1.SetParam(ABILITY_KEY_UIEXTENSIONTYPE, ABILITY_VALUE_UIEXTENSIONTYPE);
    NG::UIExtensionConfig config;
    config.wantWrap = AceType::MakeRefPtr<WantWrapOhos>(want1);
    auto pattern = CreateSecurityUEC(config);
    ValidSessionWrapper(pattern);
    ValidSession(pattern);
    auto host = pattern->GetHost();
    ASSERT_NE(host, nullptr);
    /**
     * @tc.steps: step2. test Life Cycle OnConnect
     */
    pattern->OnConnect();
    EXPECT_NE(pattern->contentNode_, nullptr);
    ASSERT_NE(pattern->sessionWrapper_, nullptr);
    EXPECT_TRUE(pattern->sessionWrapper_->IsSessionValid());
    /**
     * @tc.steps: step4. test Life Cycle NotifyForeground
     */
    pattern->NotifyForeground();
    EXPECT_EQ(pattern->state_, SecurityUIExtensionPattern::AbilityState::FOREGROUND);
    /**
     * @tc.steps: step5. test Life Cycle OnTerminated
     */
    pattern->FireOnErrorCallback(0, "123", "123");
    EXPECT_EQ(pattern->state_, SecurityUIExtensionPattern::AbilityState::NONE);
    EXPECT_EQ(host->TotalChildCount(), 0);
    /**
     * @tc.steps: step6. test Life Cycle UpdateWant
     */
    OHOS::AAFwk::Want want2;
    want2.SetElementName(BOUNDLE_NAME_NEW, ABILITY_NAME_NEW);
    pattern->instanceId_ = 2;
    EXPECT_EQ(pattern->CheckConstraint(), true);
    pattern->UpdateWant(want2);
    EXPECT_EQ(pattern->state_, SecurityUIExtensionPattern::AbilityState::FOREGROUND);
    pattern->OnConnect();
    EXPECT_NE(pattern->contentNode_, nullptr);
    ASSERT_NE(pattern->sessionWrapper_, nullptr);
    EXPECT_TRUE(pattern->sessionWrapper_->IsSessionValid());
    /**
     * @tc.steps: step7. test Life Cycle OnDisconnect
     */
    pattern->OnDisconnect(true);
    EXPECT_EQ(host->TotalChildCount(), 0);
#endif
}
} //namespace OHOS::Ace::NG