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
#include "core/components_ng/pattern/ui_extension/security_ui_extension_component/security_session_wrapper_impl.h"
#include "core/components_ng/pattern/ui_extension/security_ui_extension_component/security_ui_extension_pattern.h"
#include "core/components_ng/pattern/ui_extension/preview_ui_extension_component/preview_session_wrapper_impl.h"
#include "core/components_ng/pattern/ui_extension/preview_ui_extension_component/preview_ui_extension_pattern.h"
#include "core/components_ng/pattern/ui_extension/preview_ui_extension_component/preview_ui_extension_adapter.h"
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
    const std::string PREVIEW_UI_EXTENSION_COMPONENT_ETS_TAG = "PreviewUIExtensionComponent";
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

class PreviewUIExtensionComponentTestNg : public testing::Test {
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
    RefPtr<PreviewUIExtensionPattern> CreatePreviewUEC();
    RefPtr<PreviewUIExtensionPattern> CreatePreviewUEC(NG::UIExtensionConfig config);
    void InvalidSession(RefPtr<PreviewUIExtensionPattern> pattern);
    void ValidSession(RefPtr<PreviewUIExtensionPattern> pattern);
    void InvalidSessionWrapper(RefPtr<PreviewUIExtensionPattern> pattern);
    void ValidSessionWrapper(RefPtr<PreviewUIExtensionPattern> pattern);
    void FireCallbacks(RefPtr<PreviewUIExtensionPattern> pattern);
    RefPtr<FrameNode> frameNode_ = nullptr;
};

void PreviewUIExtensionComponentTestNg::SetUp()
{
}

void PreviewUIExtensionComponentTestNg::TearDown()
{
    // clear stack after each test
    auto* stack = ViewStackProcessor::GetInstance();
    stack->ClearStack();
}

RefPtr<PreviewUIExtensionPattern> PreviewUIExtensionComponentTestNg::CreatePreviewUEC()
{
    // construct config of PreviewUEC
    OHOS::AAFwk::Want want;
    want.SetElementName(BOUNDLE_NAME, ABILITY_NAME);
    want.SetParam(ABILITY_KEY_UIEXTENSIONTYPE, ABILITY_VALUE_UIEXTENSIONTYPE);

    auto placeholderId = ElementRegister::GetInstance()->MakeUniqueId();
    auto placeholderNode = FrameNode::GetOrCreateFrameNode(
        "placeholderNode", placeholderId, []() { return AceType::MakeRefPtr<Pattern>(); });
    
    NG::UIExtensionConfig config;
    config.wantWrap = AceType::MakeRefPtr<WantWrapOhos>(want);
    config.placeholderNode = placeholderNode;
    config.sessionType = SessionType::UI_EXTENSION_ABILITY;
    config.transferringCaller = true;
    config.densityDpi = true;
    // create PreviewUEC
    PreviewUIExtensionAdapter previewAdapter;
    frameNode_ = previewAdapter.CreatePreviewUIExtensionNode(config);
    CHECK_NULL_RETURN(frameNode_, nullptr);
    EXPECT_EQ(frameNode_->GetTag(), V2::UI_EXTENSION_COMPONENT_ETS_TAG);
    previewAdapter.UpdatePreviewUIExtensionConfig(frameNode_, config);
    // set callbacks
    auto onReceive = [](const AAFwk::WantParams& wantParams) {};
    auto onError = [](int32_t code, const std::string& name, const std::string& message) {};
    auto onRemoteReady = [](const RefPtr<SecurityUIExtensionProxy>&) {};
    auto onTerminated = [](int32_t code, const RefPtr<WantWrap>&) {};
    previewAdapter.SetOnReceive(frameNode_, onReceive);
    previewAdapter.SetOnError(frameNode_, onError);
    previewAdapter.SetOnRemoteReady(frameNode_, onRemoteReady);
    previewAdapter.SetOnTerminated(frameNode_, onTerminated);
    // get pattern
    auto pattern = frameNode_->GetPattern<PreviewUIExtensionPattern>();
    return pattern;
}

RefPtr<PreviewUIExtensionPattern> PreviewUIExtensionComponentTestNg::CreatePreviewUEC(NG::UIExtensionConfig config)
{
    // create PreviewUEC
    PreviewUIExtensionAdapter previewAdapter;
    config.sessionType = SessionType::UI_EXTENSION_ABILITY;
    frameNode_ = previewAdapter.CreatePreviewUIExtensionNode(config);
    CHECK_NULL_RETURN(frameNode_, nullptr);
    EXPECT_EQ(frameNode_->GetTag(), V2::UI_EXTENSION_COMPONENT_ETS_TAG);
    previewAdapter.UpdatePreviewUIExtensionConfig(frameNode_, config);
    // set callbacks
    auto onReceive = [](const AAFwk::WantParams& wantParams) {};
    auto onError = [](int32_t code, const std::string& name, const std::string& message) {};
    auto onRemoteReady = [](const RefPtr<SecurityUIExtensionProxy>&) {};
    auto onTerminated = [](int32_t code, const RefPtr<WantWrap>&) {};
    previewAdapter.SetOnReceive(frameNode_, onReceive);
    previewAdapter.SetOnError(frameNode_, onError);
    previewAdapter.SetOnRemoteReady(frameNode_, onRemoteReady);
    previewAdapter.SetOnTerminated(frameNode_, onTerminated);
    // get pattern
    auto pattern = frameNode_->GetPattern<PreviewUIExtensionPattern>();
    return pattern;
}

void PreviewUIExtensionComponentTestNg::InvalidSession(RefPtr<PreviewUIExtensionPattern> pattern)
{
    CHECK_NULL_VOID(pattern);
    ValidSessionWrapper(pattern);
    auto sessionWrapper = AceType::DynamicCast<PreviewSessionWrapperImpl>(pattern->sessionWrapper_);
    CHECK_NULL_VOID(sessionWrapper);
    sessionWrapper->session_ = nullptr;
}

void PreviewUIExtensionComponentTestNg::ValidSession(RefPtr<PreviewUIExtensionPattern> pattern)
{
    CHECK_NULL_VOID(pattern);
    ValidSessionWrapper(pattern);
    auto sessionWrapper = AceType::DynamicCast<PreviewSessionWrapperImpl>(pattern->sessionWrapper_);
    CHECK_NULL_VOID(sessionWrapper);
    Rosen::SessionInfo sessionInfo;
    sessionWrapper->session_ = new Rosen::ExtensionSession(sessionInfo);
}

void PreviewUIExtensionComponentTestNg::InvalidSessionWrapper(RefPtr<PreviewUIExtensionPattern> pattern)
{
    CHECK_NULL_VOID(pattern);
    pattern->sessionWrapper_ = nullptr;
}

void PreviewUIExtensionComponentTestNg::ValidSessionWrapper(RefPtr<PreviewUIExtensionPattern> pattern)
{
    CHECK_NULL_VOID(pattern);
    pattern->sessionWrapper_ =
        AceType::MakeRefPtr<PreviewSessionWrapperImpl>(pattern, pattern->instanceId_, false,
        SessionType::UI_EXTENSION_ABILITY);
}

void PreviewUIExtensionComponentTestNg::FireCallbacks(RefPtr<PreviewUIExtensionPattern> pattern)
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
 * @tc.name: PreviewUIExtensionComponentCreateSuccessTest
 * @tc.desc: Test create PreviewUIExtensionComponent successfully
 * @tc.type: FUNC
 */
HWTEST_F(PreviewUIExtensionComponentTestNg, PreviewUIExtensionComponentCreateSuccessTest, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewUEC();

    ASSERT_EQ(pattern->densityDpi_, true);
    ASSERT_EQ(pattern->sessionType_, SessionType::PREVIEW_UI_EXTENSION_ABILITY);
#endif
}

/**
 * @tc.name: PreviewUIExtensionCallbackTest
 * @tc.desc: Test callbacks
 * @tc.type: FUNC
 */
HWTEST_F(PreviewUIExtensionComponentTestNg, PreviewUIExtensionCallbackTest, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a PreviewUIExtensionComponent node and get pattern
     */
    auto pattern = CreatePreviewUEC();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. check sessionWrapper
     */
    auto sessionWrapper = AceType::DynamicCast<PreviewSessionWrapperImpl>(pattern->sessionWrapper_);
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
    pattern->state_ = PreviewUIExtensionPattern::AbilityState::DESTRUCTION;
    FireCallbacks(pattern);

    pattern->state_ = PreviewUIExtensionPattern::AbilityState::FOREGROUND;
    InvalidSessionWrapper(pattern);
    FireCallbacks(pattern);

    ValidSession(pattern);
    FireCallbacks(pattern);

    InvalidSession(pattern);
    FireCallbacks(pattern);
#endif
}

/**
 * @tc.name: PreviewUIExtensionInvalidSessionTest
 * @tc.desc: Invalid session, test NotifyForeground/NotifyBackground/NotifyDestroy
 * @tc.type: FUNC
 */
HWTEST_F(PreviewUIExtensionComponentTestNg, PreviewUIExtensionInvalidSessionTest, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a PreviewUIExtensionComponent node and set invalid sessionWrapper
     */
    auto pattern = CreatePreviewUEC();
    InvalidSessionWrapper(pattern);

    /**
     * @tc.steps: step2. set component visibile and sync gemometry node
     */
    pattern->isVisible_ = true;
    const DirtySwapConfig config;
    pattern->OnSyncGeometryNode(config);

    /**
     * @tc.steps: step3. test NotifyDestroy, state not change
     */
    pattern->NotifyDestroy();
    EXPECT_EQ(pattern->state_, PreviewUIExtensionPattern::AbilityState::NONE);
#endif
}

/**
 * @tc.name: PreviewUIExtensionOnConnectTest
 * @tc.desc: Test pattern OnConnect
 * @tc.type: FUNC
 */
HWTEST_F(PreviewUIExtensionComponentTestNg, PreviewUIExtensionOnConnectTest, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a PreviewUIExtensionComponent Node
     */
    auto pattern = CreatePreviewUEC();
    EXPECT_EQ(frameNode_->GetTag(), V2::UI_EXTENSION_COMPONENT_ETS_TAG);

    /**
     * @tc.steps: step2. test OnConnect
     */
    auto host = pattern->GetHost();
    EXPECT_NE(host, nullptr);
    auto&& opts = host->GetLayoutProperty()->GetSafeAreaExpandOpts();
    auto surfaceNode = pattern->sessionWrapper_->GetSurfaceNode();
    EXPECT_NE(surfaceNode, nullptr);
    auto layoutProperty = frameNode_->GetLayoutProperty();
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

    auto focusHub = frameNode_->GetFocusHub();
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
 * @tc.name: PreviewUIExtensionOnErrorTest
 * @tc.desc: Test pattern OnError
 * @tc.type: FUNC
 */
HWTEST_F(PreviewUIExtensionComponentTestNg, PreviewUIExtensionOnErrorTest, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a PreviewUIExtensionComponent Node
     */
    auto pattern = CreatePreviewUEC();
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
    EXPECT_EQ(pattern->state_, PreviewUIExtensionPattern::AbilityState::NONE);
#endif
}

/**
 * @tc.name: PreviewUIExtensionHandleKeyEventValidSession
 * @tc.desc: Valid session, test pattern KeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(PreviewUIExtensionComponentTestNg, PreviewUIExtensionHandleKeyEventValidSession, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a PreviewUIExtensionComponent node and create valid session
     */
    auto pattern = CreatePreviewUEC();
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
 * @tc.name: PreviewUIExtensionHandleKeyEventInvalidSession
 * @tc.desc: Invalid session, test pattern KeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(PreviewUIExtensionComponentTestNg, PreviewUIExtensionHandleKeyEventInvalidSession, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a PreviewUIExtensionComponent node and create invali session
     */
    auto pattern = CreatePreviewUEC();
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
 * @tc.name: PreviewUIExtensionHandleMouseEventValidSession
 * @tc.desc: Valid session, test pattern MouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(PreviewUIExtensionComponentTestNg, PreviewUIExtensionHandleMouseEventValidSession, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a PreviewUIExtensionComponent node and create valid session
     */
    auto pattern = CreatePreviewUEC();
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
    auto sessionWrapper = AceType::DynamicCast<PreviewSessionWrapperImpl>(pattern->sessionWrapper_);
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
 * @tc.name: PreviewUIExtensionHandleMouseEventInvalidSession
 * @tc.desc: Invalid session, test pattern MouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(PreviewUIExtensionComponentTestNg, PreviewUIExtensionHandleMouseEventInvalidSession, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a PreviewUIExtensionComponent node and create invalid session
     */
    auto pattern = CreatePreviewUEC();
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
    auto sessionWrapper = AceType::DynamicCast<PreviewSessionWrapperImpl>(pattern->sessionWrapper_);
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
 * @tc.name: PreviewUIExtensionPlaceholderTest
 * @tc.desc: Test pattern SetPlaceholder/MountPlaceholder/RemovePlaceholder
 * @tc.type: FUNC
 */
HWTEST_F(PreviewUIExtensionComponentTestNg, PreviewUIExtensionPlaceholderTest, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a PreviewUIExtensionComponent node
     */
    auto uiExtensionNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto uiExtensionNode = FrameNode::GetOrCreateFrameNode(
        V2::UI_EXTENSION_COMPONENT_ETS_TAG, uiExtensionNodeId,
        []() { return AceType::MakeRefPtr<PreviewUIExtensionPattern>(); });
    ASSERT_NE(uiExtensionNode, nullptr);
    EXPECT_EQ(uiExtensionNode->GetTag(), V2::UI_EXTENSION_COMPONENT_ETS_TAG);
    auto pattern = uiExtensionNode->GetPattern<PreviewUIExtensionPattern>();
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
 * @tc.name: PreviewUIExtensionDpiTest
 * @tc.desc: Test pattern SetDensityDpi/GetDensityDpi function
 * @tc.type: FUNC
 */
HWTEST_F(PreviewUIExtensionComponentTestNg, PreviewUIExtensionDpiTest, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a PreviewUIExtensionComponent node and get pattern
     */
    auto pattern = CreatePreviewUEC();

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
 * @tc.name: PreviewUIExtensionDpiTest
 * @tc.desc: Test pattern Initialize and CreateLayoutAlgorithm
 * @tc.type: FUNC
 */
HWTEST_F(PreviewUIExtensionComponentTestNg, InitializeTest001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a PreviewUIExtensionComponent node and get pattern
     */
    auto pattern = CreatePreviewUEC();
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
        AceType::MakeRefPtr<PreviewSessionWrapperImpl>(pattern, pattern->instanceId_, false,
        SessionType::UI_EXTENSION_ABILITY);
    ASSERT_NE(pattern->sessionWrapper_, nullptr);
    pattern->Initialize(config);

    /**
     * @tc.steps: step4. test CreateLayoutAlgorithm
     */
    ASSERT_NE(pattern->CreateLayoutAlgorithm(), nullptr);
#endif
}

/**
 * @tc.name: PreviewUIExtensionDpiTest
 * @tc.desc: Test pattern OnExtensionDetachToDisplay
 * @tc.type: FUNC
 */
HWTEST_F(PreviewUIExtensionComponentTestNg, OnExtensionDetachToDisplayTest001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a PreviewUIExtensionComponent node and get pattern
     */
    auto pattern = CreatePreviewUEC();

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
 * @tc.name: PreviewUIExtensionDpiTest
 * @tc.desc: Test pattern DispatchFollowHostDensity and OnDpiConfigurationUpdate
 * @tc.type: FUNC
 */
HWTEST_F(PreviewUIExtensionComponentTestNg, DispatchFollowHostDensityTest001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a PreviewUIExtensionComponent node and get pattern
     */
    auto pattern = CreatePreviewUEC();

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
 * @tc.name: PreviewUIExtensionDpiTest
 * @tc.desc: Test pattern OnLanguageConfigurationUpdate, OnColorConfigurationUpdate and GetSessionId
 * @tc.type: FUNC
 */
HWTEST_F(PreviewUIExtensionComponentTestNg, OnLanguageConfigurationUpdateTest001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a PreviewUIExtensionComponent node and get pattern
     */
    auto pattern = CreatePreviewUEC();
    pattern->sessionWrapper_ = nullptr;
    ASSERT_EQ(pattern->sessionWrapper_, nullptr);

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
        AceType::MakeRefPtr<PreviewSessionWrapperImpl>(pattern, pattern->instanceId_, false,
        SessionType::UI_EXTENSION_ABILITY);
    ASSERT_NE(pattern->sessionWrapper_, nullptr);
    pattern->OnLanguageConfigurationUpdate();
    pattern->OnColorConfigurationUpdate();
    ASSERT_EQ(pattern->GetSessionId(), pattern->sessionWrapper_->GetSessionId());
#endif
}

/**
 * @tc.name: PreviewUIExtensionDpiTest
 * @tc.desc: Test pattern DumpInfo and DumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(PreviewUIExtensionComponentTestNg, DumpInfoTest001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a PreviewUIExtensionComponent node and get pattern
     */
    auto pattern = CreatePreviewUEC();

    /**
     * @tc.steps: step2. test DumpInfo
     */
    pattern->platformEventProxy_ = nullptr;
    ASSERT_EQ(pattern->platformEventProxy_, nullptr);
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
    ASSERT_EQ(pattern->platformEventProxy_, nullptr);
    pattern->DumpInfo(testValue);

    pattern->platformEventProxy_ = AceType::MakeRefPtr<PlatformEventProxy>();
    ASSERT_NE(pattern->platformEventProxy_, nullptr);
    pattern->DumpInfo(testValue);
#endif
}

/**
 * @tc.name: PreviewUIExtensionEventTest
 * @tc.desc: Test pattern Test OnExtensionEvent, OnUeaAccessibilityEventAsync
 * @tc.type: FUNC
 */
HWTEST_F(PreviewUIExtensionComponentTestNg, PreviewUIExtensionEventTest, TestSize.Level1)
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
        []() { return AceType::MakeRefPtr<PreviewUIExtensionPattern>(); });
    ASSERT_NE(uiExtensionNode, nullptr);
    EXPECT_EQ(uiExtensionNode->GetTag(), V2::UI_EXTENSION_COMPONENT_ETS_TAG);
    auto pattern = uiExtensionNode->GetPattern<PreviewUIExtensionPattern>();
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
    config.sessionType = SessionType::UI_EXTENSION_ABILITY;
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
 * @tc.name: PreviewUIExtensionChildTreeTest
 * @tc.desc: Test pattern about child tree
 * @tc.type: FUNC
 */
HWTEST_F(PreviewUIExtensionComponentTestNg, PreviewUIExtensionChildTreeTest, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto uiExtensionNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto uiExtensionNode = FrameNode::GetOrCreateFrameNode(
        V2::UI_EXTENSION_COMPONENT_ETS_TAG, uiExtensionNodeId,
        []() { return AceType::MakeRefPtr<PreviewUIExtensionPattern>(); });
    ASSERT_NE(uiExtensionNode, nullptr);
    EXPECT_EQ(uiExtensionNode->GetTag(), V2::UI_EXTENSION_COMPONENT_ETS_TAG);
    auto pattern = uiExtensionNode->GetPattern<PreviewUIExtensionPattern>();
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
 * @tc.name: PreviewUIExtensionChildTreeCallbackTest
 * @tc.desc: Test OnRegister, OnDeregister, OnSetChildTree, OnDumpChildInfo, OnClearRegisterFlag
 * @tc.type: FUNC
 */
HWTEST_F(PreviewUIExtensionComponentTestNg, PreviewUIExtensionChildTreeCallbackTest, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct an PlatformAccessibilityChildTreeCallback
     */
    auto uiExtensionNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto uiExtensionNode = FrameNode::GetOrCreateFrameNode(
        V2::UI_EXTENSION_COMPONENT_ETS_TAG, uiExtensionNodeId,
        []() { return AceType::MakeRefPtr<PreviewUIExtensionPattern>(); });
    ASSERT_NE(uiExtensionNode, nullptr);
    EXPECT_EQ(uiExtensionNode->GetTag(), V2::UI_EXTENSION_COMPONENT_ETS_TAG);
    auto pattern = uiExtensionNode->GetPattern<PreviewUIExtensionPattern>();
    NG::UIExtensionConfig config;
    config.sessionType = SessionType::UI_EXTENSION_ABILITY;
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
    auto weakPtr = WeakPtr<PreviewUIExtensionPattern>(nullptr);
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
 * @tc.name: PreviewUIExtensionComponentTestNg
 * @tc.desc: Test the method of pattern RegisterEventProxyFlagCallback
 * @tc.type: FUNC
 */
HWTEST_F(PreviewUIExtensionComponentTestNg, RegisterEventProxyFlagCallback, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a UIExtensionComponent Node
     */
    auto uiExtensionNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto uiExtensionNode = FrameNode::GetOrCreateFrameNode(
        V2::UI_EXTENSION_COMPONENT_ETS_TAG, uiExtensionNodeId,
        []() { return AceType::MakeRefPtr<PreviewUIExtensionPattern>(); });
    ASSERT_NE(uiExtensionNode, nullptr);
    EXPECT_EQ(uiExtensionNode->GetTag(), V2::UI_EXTENSION_COMPONENT_ETS_TAG);
    auto pattern = uiExtensionNode->GetPattern<PreviewUIExtensionPattern>();
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
* @tc.name: PreviewUIExtensionComponentTestNg
* @tc.desc: Test the method of pattern GetAccessibilityRectInfo
* @tc.type: FUNC
*/
HWTEST_F(PreviewUIExtensionComponentTestNg, GetAccessibilityRectInfo, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
    * @tc.steps: step1. construct a UIExtensionComponent Node
    */
    auto uiExtensionNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto uiExtensionNode = FrameNode::GetOrCreateFrameNode(
        V2::UI_EXTENSION_COMPONENT_ETS_TAG, uiExtensionNodeId,
        []() { return AceType::MakeRefPtr<PreviewUIExtensionPattern>(); });
    ASSERT_NE(uiExtensionNode, nullptr);
    EXPECT_EQ(uiExtensionNode->GetTag(), V2::UI_EXTENSION_COMPONENT_ETS_TAG);
    auto pattern = uiExtensionNode->GetPattern<PreviewUIExtensionPattern>();
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
 * @tc.name: PreviewUIExtensionComponentTestNg001
 * @tc.desc: Test the method of pattern UpdateWMSUIExtProperty
 * @tc.type: FUNC
 */
HWTEST_F(PreviewUIExtensionComponentTestNg, PreviewUIExtensionComponentTestNg001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a UIExtensionComponent Node
     */
    auto uiExtensionNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto uiExtensionNode = FrameNode::GetOrCreateFrameNode(V2::UI_EXTENSION_COMPONENT_ETS_TAG, uiExtensionNodeId,
        []() { return AceType::MakeRefPtr<PreviewUIExtensionPattern>(); });
    ASSERT_NE(uiExtensionNode, nullptr);
    EXPECT_EQ(uiExtensionNode->GetTag(), V2::UI_EXTENSION_COMPONENT_ETS_TAG);
    auto pattern = uiExtensionNode->GetPattern<PreviewUIExtensionPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. test UpdateWMSUIExtProperty
     */
    UIContentBusinessCode code = UIContentBusinessCode::UNDEFINED;
    AAFwk::Want data;
    RSSubsystemId id = RSSubsystemId::ARKUI_UIEXT;
    pattern->UpdateWMSUIExtProperty(code, data, id);
    pattern->state_ = PreviewUIExtensionPattern::AbilityState::FOREGROUND;
    pattern->UpdateWMSUIExtProperty(code, data, id);
#endif
}

/**
 * @tc.name: PreviewUIExtensionComponentTestNg002
 * @tc.desc: Test the method of pattern GetInstanceIdFromHost
 * @tc.type: FUNC
 */
HWTEST_F(PreviewUIExtensionComponentTestNg, PreviewUIExtensionComponentTestNg002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a UIExtensionComponent Node
     */
    auto uiExtensionNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto uiExtensionNode = FrameNode::GetOrCreateFrameNode(V2::UI_EXTENSION_COMPONENT_ETS_TAG, uiExtensionNodeId,
        []() { return AceType::MakeRefPtr<PreviewUIExtensionPattern>(); });
    ASSERT_NE(uiExtensionNode, nullptr);
    EXPECT_EQ(uiExtensionNode->GetTag(), V2::UI_EXTENSION_COMPONENT_ETS_TAG);
    auto pattern = uiExtensionNode->GetPattern<PreviewUIExtensionPattern>();
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
 * @tc.name: PreviewUIExtensionComponentTestNg003
 * @tc.desc: Test the method of pattern OnUIExtBusinessReceiveReply and OnUIExtBusinessReceive
 * @tc.type: FUNC
 */
HWTEST_F(PreviewUIExtensionComponentTestNg, PreviewUIExtensionComponentTestNg003, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a UIExtensionComponent Node
     */
    auto uiExtensionNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto uiExtensionNode = FrameNode::GetOrCreateFrameNode(V2::UI_EXTENSION_COMPONENT_ETS_TAG, uiExtensionNodeId,
        []() { return AceType::MakeRefPtr<PreviewUIExtensionPattern>(); });
    ASSERT_NE(uiExtensionNode, nullptr);
    EXPECT_EQ(uiExtensionNode->GetTag(), V2::UI_EXTENSION_COMPONENT_ETS_TAG);
    auto pattern = uiExtensionNode->GetPattern<PreviewUIExtensionPattern>();
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
 * @tc.name: PreviewUIExtensionComponentTestNg004
 * @tc.desc: Test the method of pattern RegisterEventProxyFlagCallback
 * @tc.type: FUNC
 */
HWTEST_F(PreviewUIExtensionComponentTestNg, PreviewUIExtensionComponentTestNg004, TestSize.Level1)
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
 * @tc.name: PreviewUIExtensionComponentTestNg005
 * @tc.desc: Test the method of pattern RegisterEventProxyFlagCallback
 * @tc.type: FUNC
 */
HWTEST_F(PreviewUIExtensionComponentTestNg, PreviewUIExtensionComponentTestNg005, TestSize.Level1)
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
 * @tc.name: PreviewUIExtensionComponentTestNg006
 * @tc.desc: Test pattern SetEventProxyFlag
 * @tc.type: FUNC
 */
HWTEST_F(PreviewUIExtensionComponentTestNg, PreviewUIExtensionComponentTestNg006, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a PreviewUIExtensionComponent Node
     */
    auto pattern = CreatePreviewUEC();
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
 * @tc.name: PreviewUIExtensionComponentTestNg007
 * @tc.desc: Test pattern HandleKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(PreviewUIExtensionComponentTestNg, PreviewUIExtensionComponentTestNg007, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a PreviewUIExtensionComponent Node
     */
    auto pattern = CreatePreviewUEC();
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
 * @tc.name: PreviewUIExtensionComponentMemberVariablesTestNg
 * @tc.desc: Test PreviewUIExtension pattern base member variables
 * @tc.type: FUNC
 */
HWTEST_F(PreviewUIExtensionComponentTestNg, PreviewUIExtensionComponentMemberVariablesTestNg, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a PreviewUIExtensionComponent Node
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
    config.transferringCaller = true;
    config.densityDpi = true;
    auto pattern = CreatePreviewUEC(config);
    ValidSessionWrapper(pattern);
    /**
     * @tc.steps: step2. test base member variables
     */
    ASSERT_NE(pattern, nullptr);
    EXPECT_EQ(pattern->isVisible_, true);
    EXPECT_NE(pattern->placeholderNode_, nullptr);
    EXPECT_EQ(pattern->sessionType_, SessionType::PREVIEW_UI_EXTENSION_ABILITY);
    EXPECT_EQ(pattern->densityDpi_, config.densityDpi);
    EXPECT_EQ(pattern->contentNode_, nullptr);
#endif
}

/**
 * @tc.name: PreviewUIExtensionComponentLifeCycleTestNg_2
 * @tc.desc: Test PreviewUIExtension pattern life cycle FireOnErrorCallback
 * @tc.type: FUNC
 */
HWTEST_F(PreviewUIExtensionComponentTestNg, PreviewUIExtensionComponentLifeCycleTestNg_2, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a PreviewUIExtensionComponent Node
     */
    OHOS::AAFwk::Want want1;
    want1.SetElementName(BOUNDLE_NAME, ABILITY_NAME);
    want1.SetParam(ABILITY_KEY_UIEXTENSIONTYPE, ABILITY_VALUE_UIEXTENSIONTYPE);
    NG::UIExtensionConfig config;
    config.wantWrap = AceType::MakeRefPtr<WantWrapOhos>(want1);
    auto pattern = CreatePreviewUEC(config);
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
     * @tc.steps: step3. test Life Cycle OnTerminated
     */
    pattern->FireOnErrorCallback(0, "123", "123");
    EXPECT_EQ(pattern->state_, PreviewUIExtensionPattern::AbilityState::NONE);
    EXPECT_EQ(host->TotalChildCount(), 0);
    /**
     * @tc.steps: step4. test Life Cycle OnDisconnect
     */
    pattern->OnDisconnect(true);
    EXPECT_EQ(host->TotalChildCount(), 0);
#endif
}

/**
 * @tc.name: AfterMountToParent001
 * @tc.desc: Test PreviewUIExtension pattern AfterMountToParent
 * @tc.type: FUNC
 */
HWTEST_F(PreviewUIExtensionComponentTestNg, AfterMountToParent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a PreviewUIExtensionComponent Node
     */
    auto pattern = CreatePreviewUEC();
    ASSERT_NE(pattern, nullptr);
    ValidSessionWrapper(pattern);
    ASSERT_NE(pattern->sessionWrapper_, nullptr);

    /**
     * @tc.steps: step2. test AfterMountToParent
     */
    pattern->hasAttachContext_ = false;
    pattern->AfterMountToParent();
    EXPECT_TRUE(pattern->hasMountToParent_);

    pattern->needReNotifyForeground_ = true;
    pattern->hasAttachContext_ = false;
    pattern->AfterMountToParent();
    EXPECT_TRUE(pattern->hasMountToParent_);

    pattern->hasAttachContext_ = true;
    pattern->AfterMountToParent();
    EXPECT_FALSE(pattern->needReNotifyForeground_);
}

/**
 * @tc.name: OnAttachContext001
 * @tc.desc: Test PreviewUIExtension pattern OnAttachContext
 * @tc.type: FUNC
 */
HWTEST_F(PreviewUIExtensionComponentTestNg, OnAttachContext001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a PreviewUIExtensionComponent Node
     */
    auto pattern = CreatePreviewUEC();
    ASSERT_NE(pattern, nullptr);
    ValidSessionWrapper(pattern);
    ASSERT_NE(pattern->sessionWrapper_, nullptr);

    /**
     * @tc.steps: step2. test OnAttachContext
     */
    pattern->hasAttachContext_ = false;
    pattern->OnAttachContext(nullptr);
    EXPECT_FALSE(pattern->hasAttachContext_);

    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pattern->instanceId_ = 1;
    pipeline->instanceId_ = 2;
    pattern->OnAttachContext(AceType::RawPtr(pipeline));
    EXPECT_EQ(pattern->instanceId_, pipeline->instanceId_);

    pattern->instanceId_ = 1;
    pipeline->instanceId_ = 1;
    pattern->needReNotifyForeground_ = false;
    pattern->hasMountToParent_ = true;
    ASSERT_NE(pattern, nullptr);
    pattern->OnAttachContext(AceType::RawPtr(pipeline));
    EXPECT_FALSE(pattern->needReNotifyForeground_);

    pattern->needReNotifyForeground_ = true;
    pattern->hasMountToParent_ = false;
    ASSERT_NE(pattern, nullptr);
    pattern->OnAttachContext(AceType::RawPtr(pipeline));
    EXPECT_TRUE(pattern->needReNotifyForeground_);
    pattern->needReNotifyForeground_ = true;
    pattern->hasMountToParent_ = true;
    ASSERT_NE(pattern, nullptr);
    pattern->OnAttachContext(AceType::RawPtr(pipeline));
    EXPECT_EQ(pattern->state_, PreviewUIExtensionPattern::AbilityState::FOREGROUND);
}

/**
 * @tc.name: UpdateSessionInstanceId
 * @tc.desc: Test PreviewUIExtension pattern UpdateSessionInstanceId001
 * @tc.type: FUNC
 */
HWTEST_F(PreviewUIExtensionComponentTestNg, UpdateSessionInstanceId001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a PreviewUIExtensionComponent Node
     */
    auto pattern = CreatePreviewUEC();
    ASSERT_NE(pattern, nullptr);
    pattern->instanceId_ = 1;
    ValidSessionWrapper(pattern);
    ASSERT_NE(pattern->sessionWrapper_, nullptr);

    /**
     * @tc.steps: step2. test UpdateSessionInstanceId
     */
    pattern->hasAttachContext_ = false;
    pattern->UpdateSessionInstanceId(1);
    EXPECT_NE(pattern->sessionWrapper_, nullptr);

    InvalidSessionWrapper(pattern);
    pattern->UpdateSessionInstanceId(1);
    EXPECT_EQ(pattern->sessionWrapper_, nullptr);
}

/**
 * @tc.name: NotifyDestroy001
 * @tc.desc: Test the method NotifyDestroy
 * @tc.type: FUNC
 */
HWTEST_F(PreviewUIExtensionComponentTestNg, NotifyDestroy001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a PreviewSessionWrapperImpl
     */
    auto pattern = CreatePreviewUEC();
    ASSERT_NE(pattern, nullptr);
    pattern->instanceId_ = 1;
    ValidSessionWrapper(pattern);
    auto sessionWrapper = pattern->sessionWrapper_;
    ASSERT_NE(sessionWrapper, nullptr);
    ValidSession(pattern);

    /**
     * @tc.steps: step2. test NotifyDestroy
     */
    bool isHandleError = true;
    sessionWrapper->NotifyDestroy(isHandleError);
    EXPECT_EQ(isHandleError, true);

    isHandleError = false;
    sessionWrapper->NotifyDestroy(isHandleError);
    EXPECT_EQ(isHandleError, false);
}
} //namespace OHOS::Ace::NG