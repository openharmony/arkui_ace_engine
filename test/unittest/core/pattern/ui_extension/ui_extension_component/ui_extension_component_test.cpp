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
#include "test/mock/core/render/mock_rosen_render_context.h"
#include "test/unittest/core/pattern/ui_extension/mock/mock_accessibility_child_tree_callback.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
    const std::string UI_EXTENSION_COMPONENT_ETS_TAG = "UIExtensionComponent";
    const int32_t CODE = 10001;
    const std::string NAME = "Test name";
    const std::string MSG = "Test msg";
    constexpr char ABILITY_KEY_IS_MODAL[] = "ability.want.params.IsModal";
    constexpr char ATOMIC_SERVICE_PREFIX[] = "com.atomicservice.";
    constexpr double SHOW_START = 0.0;
    constexpr double SHOW_FULL = 1.0;
} // namespace

class UIExtensionComponentTestNg : public testing::Test {
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
    void ValidSession(RefPtr<UIExtensionPattern> pattern);
    void InValidSession(RefPtr<UIExtensionPattern> pattern);
    void InValidSessionWrapper(RefPtr<UIExtensionPattern> pattern);
    void ValidSessionWrapper(RefPtr<UIExtensionPattern> pattern);
    RefPtr<FrameNode> CreateUecNode();
    void ClearCallbacks(RefPtr<UIExtensionPattern> pattern);
    void SetCallbacks(RefPtr<UIExtensionPattern> pattern);
    void FireCallbacks(RefPtr<UIExtensionPattern> pattern);
    void SetPlaceholder(RefPtr<UIExtensionPattern> pattern);
};

void UIExtensionComponentTestNg::SetUp() {
}

void UIExtensionComponentTestNg::TearDown() {
}

void UIExtensionComponentTestNg::InValidSession(RefPtr<UIExtensionPattern> pattern)
{
    CHECK_NULL_VOID(pattern);
    auto sessionWrapper = AceType::DynamicCast<SessionWrapperImpl>(pattern->sessionWrapper_);
    CHECK_NULL_VOID(sessionWrapper);
    sessionWrapper->session_ = nullptr;
}

void UIExtensionComponentTestNg::ValidSession(RefPtr<UIExtensionPattern> pattern)
{
    CHECK_NULL_VOID(pattern);
    ValidSessionWrapper(pattern);
    auto sessionWrapper = AceType::DynamicCast<SessionWrapperImpl>(pattern->sessionWrapper_);
    CHECK_NULL_VOID(sessionWrapper);
    Rosen::SessionInfo sessionInfo;
    sessionWrapper->session_ = new OHOS::Rosen::ExtensionSession(sessionInfo);
}

void UIExtensionComponentTestNg::InValidSessionWrapper(RefPtr<UIExtensionPattern> pattern)
{
    CHECK_NULL_VOID(pattern);
    pattern->sessionWrapper_ = nullptr;
}

void UIExtensionComponentTestNg::ValidSessionWrapper(RefPtr<UIExtensionPattern> pattern)
{
    CHECK_NULL_VOID(pattern);
    pattern->sessionWrapper_ =
        AceType::MakeRefPtr<SessionWrapperImpl>(pattern, pattern->instanceId_, 1, SessionType::UI_EXTENSION_ABILITY);
}

RefPtr<FrameNode> UIExtensionComponentTestNg::CreateUecNode()
{
    auto onRelease = [](int32_t code) {};
    auto onResult = [](int32_t code, const AAFwk::Want& wantRes) {};
    auto onReceive = [](const AAFwk::WantParams& wantParams) {};
    auto onError = [](int32_t code, const std::string& name, const std::string& message) {};
    auto onModalRemoteReady = [](const std::shared_ptr<Ace::ModalUIExtensionProxy>& proxy) {};
    auto onDestroy = []() {};
    auto onRemoteReady = [](const RefPtr<NG::UIExtensionProxy>&) {};
    auto onModalDestroy = []() {};
    auto onTerminated = [](int32_t code, const RefPtr<WantWrap>&) {};
    auto onDrawReady = []() {};
    std::list<std::function<void(const RefPtr<UIExtensionProxy>&)>> onSyncOnCallbackList;
    auto onSyncOnCallback = [](const RefPtr<UIExtensionProxy>&) {};
    onSyncOnCallbackList.emplace_back(onSyncOnCallback);
    auto bindModalCallback = []() {};

    ModalUIExtensionCallbacks callbacks = {
        .onRelease = onRelease,
        .onResult = onResult,
        .onReceive = onReceive,
        .onError = onError,
        .onRemoteReady = onModalRemoteReady,
        .onDestroy = onDestroy,
        .onDrawReady = onDrawReady,
    };

    OHOS::AAFwk::Want want;
    want.SetElementName("123", "123", "123");
    InnerModalUIExtensionConfig config;
    auto uiExtNode = UIExtensionModelNG::Create(want, callbacks, config);
    return uiExtNode;
}

void UIExtensionComponentTestNg::ClearCallbacks(RefPtr<UIExtensionPattern> pattern)
{
    pattern->onRemoteReadyCallback_=  nullptr;
    pattern->onModalRemoteReadyCallback_=  nullptr;
    pattern->onReleaseCallback_=  nullptr;
    pattern->onResultCallback_=  nullptr;
    pattern->onReceiveCallback_=  nullptr;
    pattern->onErrorCallback_ = nullptr;
    pattern->onModalDestroy_ = nullptr;
    pattern->onTerminatedCallback_ = nullptr;
    pattern->bindModalCallback_ = nullptr;
    pattern->onDrawReadyCallback_ = nullptr;
}
void UIExtensionComponentTestNg::SetCallbacks(RefPtr<UIExtensionPattern> pattern)
{
    CHECK_NULL_VOID(pattern);
    auto onRelease = [](int32_t code) {};
    auto onResult = [](int32_t code, const AAFwk::Want& wantRes) {};
    auto onReceive = [](const AAFwk::WantParams& wantParams) {};
    auto onError = [](int32_t code, const std::string& name, const std::string& message) {};
    auto onModalRemoteReady = [](const std::shared_ptr<Ace::ModalUIExtensionProxy>& proxy) {};
    auto onDestroy = []() {};
    auto onRemoteReady = [](const RefPtr<NG::UIExtensionProxy>&) {};
    auto onModalDestroy = []() {};
    auto onTerminated = [](int32_t code, const RefPtr<WantWrap>&) {};
    auto onDrawReady = []() {};
    std::list<std::function<void(const RefPtr<UIExtensionProxy>&)>> onSyncOnCallbackList;
    auto onSyncOnCallback = [](const RefPtr<UIExtensionProxy>&) {};
    onSyncOnCallbackList.emplace_back(onSyncOnCallback);
    auto bindModalCallback = []() {};

    pattern->SetOnRemoteReadyCallback(onRemoteReady);
    pattern->SetModalOnDestroy(onDestroy);
    pattern->SetOnReleaseCallback(onRelease);
    pattern->SetOnErrorCallback(onError);
    pattern->SetOnResultCallback(onResult);
    pattern->SetOnTerminatedCallback(onTerminated);
    pattern->SetOnDrawReadyCallback(onDrawReady);
    pattern->SetOnReceiveCallback(onReceive);
    pattern->SetSyncCallbacks(std::move(onSyncOnCallbackList));
    pattern->SetAsyncCallbacks(std::move(onSyncOnCallbackList));
    pattern->SetBindModalCallback(bindModalCallback);
}

void UIExtensionComponentTestNg::FireCallbacks(RefPtr<UIExtensionPattern> pattern)
{
    CHECK_NULL_VOID(pattern);
    RefPtr<WantWrap> wantWrapPtr = AceType::MakeRefPtr<WantWrapOhos>("123", "123");
    AAFwk::WantParams wantParams;
    OHOS::AAFwk::Want want;
    pattern->FireOnRemoteReadyCallback();
    pattern->FireModalOnDestroy();
    pattern->FireOnReleaseCallback(1);
    pattern->FireOnErrorCallback(1, "123", "123");
    pattern->FireOnResultCallback(1, want);
    pattern->FireOnTerminatedCallback(1, wantWrapPtr);
    pattern->FireOnReceiveCallback(wantParams);
    pattern->FireSyncCallbacks();
    pattern->FireAsyncCallbacks();
    pattern->FireBindModalCallback();
    pattern->FireOnDrawReadyCallback();
}

void UIExtensionComponentTestNg::SetPlaceholder(RefPtr<UIExtensionPattern> pattern)
{
    auto placeholderInitialId = ElementRegister::GetInstance()->MakeUniqueId();
    auto placeholderInitial = FrameNode::GetOrCreateFrameNode(
        "placeholderInitial", placeholderInitialId, []() { return AceType::MakeRefPtr<Pattern>(); });
    auto placeholderRotationId = ElementRegister::GetInstance()->MakeUniqueId();
    auto placeholderRotation = FrameNode::GetOrCreateFrameNode(
        "placeholderRotation", placeholderRotationId, []() { return AceType::MakeRefPtr<Pattern>(); });
    auto placeholderFoldId = ElementRegister::GetInstance()->MakeUniqueId();
    auto placeholderFold = FrameNode::GetOrCreateFrameNode(
        "placeholderFold", placeholderFoldId, []() { return AceType::MakeRefPtr<Pattern>(); });
    std::map<PlaceholderType, RefPtr<NG::FrameNode>> placeholderMap = {
        { PlaceholderType::INITIAL, placeholderInitial },
        { PlaceholderType::ROTATION, placeholderRotation },
        { PlaceholderType::FOLD_TO_EXPAND, placeholderFold }
    };
    pattern->SetPlaceholderMap(placeholderMap);
}


/**
 * @tc.name: UIExtensionComponentNgTest
 * @tc.desc: Test UIExtensionComponentNg
 * @tc.type: FUNC
 */
HWTEST_F(UIExtensionComponentTestNg, UIExtensionComponentNgTest, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto onRelease = [](int32_t code) {};
    auto onResult = [](int32_t code, const AAFwk::Want& wantRes) {};
    auto onReceive = [](const AAFwk::WantParams& wantParams) {};
    auto onError = [](int32_t code, const std::string& name, const std::string& message) {};
    auto onModalRemoteReady = [](const std::shared_ptr<Ace::ModalUIExtensionProxy>& proxy) {};
    auto onDestroy = []() {};
    auto onRemoteReady = [](const RefPtr<NG::UIExtensionProxy>&) {};
    auto onModalDestroy = []() {};
    auto onTerminated = [](int32_t code, const RefPtr<WantWrap>&) {};
    auto onDrawReady = []() {};
    std::list<std::function<void(const RefPtr<UIExtensionProxy>&)>> onSyncOnCallbackList;
    auto onSyncOnCallback = [](const RefPtr<UIExtensionProxy>&) {};
    onSyncOnCallbackList.emplace_back(onSyncOnCallback);
    auto bindModalCallback = []() {};

    ModalUIExtensionCallbacks callbacks = {
        .onRelease = onRelease,
        .onResult = onResult,
        .onReceive = onReceive,
        .onError = onError,
        .onRemoteReady = onModalRemoteReady,
        .onDestroy = onDestroy,
        .onDrawReady = onDrawReady,
    };

    RefPtr<WantWrap> want = AceType::MakeRefPtr<WantWrapOhos>("123", "123");
    RefPtr<WantWrap> want2 = AceType::MakeRefPtr<WantWrapOhos>("1234", "1234");
    UIExtensionModelNG uecNG;
    std::map<PlaceholderType, RefPtr<NG::FrameNode>> placeholderMap;
    /**
     * @tc.steps: step1. test Create without return
     */
    uecNG.Create(want, placeholderMap);
    uecNG.Create(want2, placeholderMap);
    uecNG.SetOnError(onError);
    uecNG.SetOnError(onError, NG::SessionType::SECURITY_UI_EXTENSION_ABILITY);
    uecNG.SetOnReceive(onReceive);
    uecNG.SetOnReceive(onReceive, NG::SessionType::SECURITY_UI_EXTENSION_ABILITY);
    uecNG.SetOnTerminated(std::move(onTerminated));
    uecNG.SetOnTerminated(std::move(onTerminated), NG::SessionType::SECURITY_UI_EXTENSION_ABILITY);
    uecNG.SetOnDrawReady(std::move(onDrawReady));

    UIExtensionConfig config;
    config.sessionType = NG::SessionType::UI_EXTENSION_ABILITY;
    uecNG.Create(config);
    config.sessionType = NG::SessionType::SECURITY_UI_EXTENSION_ABILITY;
    uecNG.Create(config);
    /**
     * @tc.steps: step2. test Create with return FrameNode
     */
    OHOS::AAFwk::Want want3;
    want3.SetElementName("com.example", "testuea");
    want3.SetParam("ability.want.params.uiExtensionType", std::string("sys/CommonUI"));
    InnerModalUIExtensionConfig innerConfig;
    EXPECT_NE(uecNG.Create(want3, callbacks, innerConfig), nullptr);
#endif
}

/**
 * @tc.name: patternTest001
 * @tc.desc: Test pattern Test Basic
 * @tc.type: FUNC
 */
HWTEST_F(UIExtensionComponentTestNg, UIExtensionPatternCallbackTest, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto uiExtNode = CreateUecNode();
    ASSERT_NE(uiExtNode, nullptr);
    auto pattern = uiExtNode->GetPattern<UIExtensionPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->AttachToFrameNode(uiExtNode);
    auto sessionWrapper = AceType::DynamicCast<SessionWrapperImpl>(pattern->sessionWrapper_);
    ASSERT_NE(sessionWrapper, nullptr);
    EXPECT_EQ(pattern->instanceId_, Container::CurrentId());
    EXPECT_EQ(pattern->instanceId_, sessionWrapper->instanceId_);
    EXPECT_EQ(sessionWrapper->IsSessionValid(), true);

    SetCallbacks(pattern);
    EXPECT_NE(pattern->onRemoteReadyCallback_, nullptr);
    EXPECT_NE(pattern->onModalRemoteReadyCallback_, nullptr);
    EXPECT_NE(pattern->onReleaseCallback_, nullptr);
    EXPECT_NE(pattern->onResultCallback_, nullptr);
    EXPECT_NE(pattern->onReceiveCallback_, nullptr);
    EXPECT_NE(pattern->onErrorCallback_, nullptr);
    EXPECT_NE(pattern->onModalDestroy_, nullptr);
    EXPECT_NE(pattern->onDrawReadyCallback_, nullptr);
    // Fire CallBack
    pattern->state_ = OHOS::Ace::NG::UIExtensionPattern::AbilityState::DESTRUCTION;
    OHOS::AAFwk::Want want;
    pattern->FireOnResultCallback(1, want);
    FireCallbacks(pattern);
    pattern->state_ = OHOS::Ace::NG::UIExtensionPattern::AbilityState::FOREGROUND;
    InValidSessionWrapper(pattern);
    EXPECT_EQ(pattern->sessionWrapper_, nullptr);
    FireCallbacks(pattern);
    ValidSession(pattern);
    FireCallbacks(pattern);
    InValidSession(pattern);
    FireCallbacks(pattern);

    pattern->onResultCallback_ = nullptr;
    pattern->onReceiveCallback_ = nullptr;
    pattern->bindModalCallback_ = nullptr;
    pattern->onModalRemoteReadyCallback_ = nullptr;
    pattern->onRemoteReadyCallback_ = nullptr;
    pattern->onReleaseCallback_ = nullptr;
    FireCallbacks(pattern);

    EXPECT_EQ(pattern->ToString(OHOS::Ace::NG::UIExtensionPattern::AbilityState::FOREGROUND), "FOREGROUND");
    EXPECT_EQ(pattern->ToString(OHOS::Ace::NG::UIExtensionPattern::AbilityState::BACKGROUND), "BACKGROUND");
    EXPECT_EQ(pattern->ToString(OHOS::Ace::NG::UIExtensionPattern::AbilityState::DESTRUCTION), "DESTRUCTION");
    EXPECT_EQ(pattern->ToString(OHOS::Ace::NG::UIExtensionPattern::AbilityState::NONE), "NONE");
#endif
}

HWTEST_F(UIExtensionComponentTestNg, UIExtensionPatternValidSessionTest, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto uiExtNode = CreateUecNode();
    ASSERT_NE(uiExtNode, nullptr);
    auto pattern = uiExtNode->GetPattern<UIExtensionPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->AttachToFrameNode(uiExtNode);

    pattern->OnVisibleChange(true);
    pattern->OnVisibleChange(false);
    pattern->isVisible_ = true;
    pattern->SetDensityDpi(true);
    EXPECT_EQ(pattern->GetDensityDpi(), true);
    pattern->OnDpiConfigurationUpdate();
    EXPECT_EQ(pattern->GetDensityDpi(), true);
    pattern->OnWindowShow();
    pattern->OnWindowHide();
    const DirtySwapConfig config;
    pattern->OnSyncGeometryNode(config);
    pattern->state_ = OHOS::Ace::NG::UIExtensionPattern::AbilityState::NONE;
    pattern->NotifyForeground();
    EXPECT_EQ(pattern->state_, OHOS::Ace::NG::UIExtensionPattern::AbilityState::FOREGROUND);
    OHOS::AAFwk::Want want2;
    want2.SetElementName("123", "456", "");
    pattern->instanceId_= 2;
    EXPECT_EQ(pattern->CheckConstraint(), true);
    pattern->UpdateWant(want2);
    pattern->NotifyBackground();
    EXPECT_EQ(pattern->state_, OHOS::Ace::NG::UIExtensionPattern::AbilityState::BACKGROUND);
    pattern->NotifyBackground();
    OHOS::AAFwk::Want want3;
    want3.SetElementName("123", "789", "");
    pattern->UpdateWant(want3);
    pattern->isModal_ = true;
    pattern->NotifyDestroy();
    EXPECT_EQ(pattern->state_, OHOS::Ace::NG::UIExtensionPattern::AbilityState::DESTRUCTION);
#endif
}

HWTEST_F(UIExtensionComponentTestNg, UIExtensionPatternInValidSessionTest, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto uiExtNode = CreateUecNode();
    ASSERT_NE(uiExtNode, nullptr);
    auto pattern = uiExtNode->GetPattern<UIExtensionPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->AttachToFrameNode(uiExtNode);
    InValidSessionWrapper(pattern);
    pattern->OnVisibleChange(true);
    pattern->OnVisibleChange(false);
    pattern->isVisible_ = true;
    pattern->SetDensityDpi(true);
    EXPECT_EQ(pattern->GetDensityDpi(), true);
    pattern->OnDpiConfigurationUpdate();
    EXPECT_EQ(pattern->GetDensityDpi(), true);
    pattern->OnWindowShow();
    pattern->OnWindowHide();
    const DirtySwapConfig config;
    pattern->OnSyncGeometryNode(config);
    pattern->state_ = OHOS::Ace::NG::UIExtensionPattern::AbilityState::NONE;
    pattern->NotifyForeground();
    EXPECT_EQ(pattern->state_, OHOS::Ace::NG::UIExtensionPattern::AbilityState::NONE);
    OHOS::AAFwk::Want want2;
    want2.SetElementName("123", "456", "");
    pattern->instanceId_= 1;
    EXPECT_EQ(pattern->CheckConstraint(), false);
    pattern->UpdateWant(want2);
    pattern->NotifyBackground();
    EXPECT_EQ(pattern->state_, OHOS::Ace::NG::UIExtensionPattern::AbilityState::NONE);
    OHOS::AAFwk::Want want3;
    want3.SetElementName("123", "789", "");
    pattern->UpdateWant(want3);
    pattern->isModal_ = true;
    pattern->NotifyDestroy();
    EXPECT_EQ(pattern->state_, OHOS::Ace::NG::UIExtensionPattern::AbilityState::NONE);
#endif
}

HWTEST_F(UIExtensionComponentTestNg, UIExtensionUpdateWantTest1, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto uiExtNode = CreateUecNode();
    ASSERT_NE(uiExtNode, nullptr);
    auto pattern = uiExtNode->GetPattern<UIExtensionPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->UpdateWant(nullptr);
    RefPtr<WantWrap> wantOhos = AceType::MakeRefPtr<WantWrapOhos>("123", "123");
    pattern->UpdateWant(wantOhos);
    auto wantOhos2 = AceType::DynamicCast<WantWrap>(wantOhos);
    pattern->UpdateWant(wantOhos2);
#endif
}

HWTEST_F(UIExtensionComponentTestNg, UIExtensionUpdateWantTest2, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto uiExtNode = CreateUecNode();
    ASSERT_NE(uiExtNode, nullptr);
    auto pattern = uiExtNode->GetPattern<UIExtensionPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->instanceId_= 2;
    OHOS::AAFwk::Want want;
    want.SetElementName("123", "456", "123");
    InValidSession(pattern);
    pattern->UpdateWant(want);
    ValidSession(pattern);
    pattern->state_ = OHOS::Ace::NG::UIExtensionPattern::AbilityState::BACKGROUND;
    pattern->UpdateWant(want);
    EXPECT_EQ(pattern->state_, OHOS::Ace::NG::UIExtensionPattern::AbilityState::DESTRUCTION);
    pattern->state_ = OHOS::Ace::NG::UIExtensionPattern::AbilityState::FOREGROUND;
    pattern->UpdateWant(want);
    EXPECT_EQ(pattern->state_, OHOS::Ace::NG::UIExtensionPattern::AbilityState::FOREGROUND);
#endif
}

/**
 * @tc.name: UIExtensionUsageTest
 * @tc.desc: Test pattern GetUIExtensionUsage
 * @tc.type: FUNC
 */
HWTEST_F(UIExtensionComponentTestNg, UIExtensionUsageTest, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto uiExtensionNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto uiExtensionNode = FrameNode::GetOrCreateFrameNode(
        UI_EXTENSION_COMPONENT_ETS_TAG, uiExtensionNodeId, []() { return AceType::MakeRefPtr<UIExtensionPattern>(); });
    ASSERT_NE(uiExtensionNode, nullptr);
    EXPECT_EQ(uiExtensionNode->GetTag(), V2::UI_EXTENSION_COMPONENT_ETS_TAG);

    /**
     * @tc.steps: step2. get pattern
     */
    auto pattern = uiExtensionNode->GetPattern<UIExtensionPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->AttachToFrameNode(uiExtensionNode);
    pattern->OnModifyDone();
    uiExtensionNode->nodeStatus_ = NodeStatus::NORMAL_NODE;
    pattern->OnMountToParentDone();
    uiExtensionNode->nodeStatus_ = NodeStatus::BUILDER_NODE_ON_MAINTREE;;
    pattern->OnMountToParentDone();
    OHOS::AAFwk::Want want;
    pattern->sessionType_ = SessionType::EMBEDDED_UI_EXTENSION;
    EXPECT_EQ(pattern->GetUIExtensionUsage(want), UIExtensionUsage::EMBEDDED);

    pattern->sessionType_ = SessionType::UI_EXTENSION_ABILITY;
    pattern->isModal_ = true;
    EXPECT_EQ(pattern->GetUIExtensionUsage(want), UIExtensionUsage::MODAL);

    pattern->sessionType_ = SessionType::UI_EXTENSION_ABILITY;
    pattern->isModal_ = false;

    want.SetParam(ABILITY_KEY_IS_MODAL, true);
    want.SetElementName("123", ATOMIC_SERVICE_PREFIX, "123");
    EXPECT_EQ(pattern->GetUIExtensionUsage(want), UIExtensionUsage::MODAL);

    want.SetElementName("123", "123", "123");
    EXPECT_EQ(pattern->GetUIExtensionUsage(want), UIExtensionUsage::EMBEDDED);

    want.SetParam(ABILITY_KEY_IS_MODAL, false);
    EXPECT_EQ(pattern->GetUIExtensionUsage(want), UIExtensionUsage::EMBEDDED);

    want.SetElementName("123", "123", "123");
    EXPECT_EQ(pattern->GetUIExtensionUsage(want), UIExtensionUsage::EMBEDDED);

    want.SetElementName("", "", "");
    EXPECT_EQ(pattern->GetUIExtensionUsage(want), UIExtensionUsage::EMBEDDED);
#endif
}

/**
 * @tc.name: UIExtensionUsageTest
 * @tc.desc: Test pattern GetUIExtensionUsage
 * @tc.type: FUNC
 */
HWTEST_F(UIExtensionComponentTestNg, AccessibilityTest001, TestSize.Level1)
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

    /**
     * @tc.steps: step2. get pattern
     */
    auto pattern = uiExtensionNode->GetPattern<UIExtensionPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->AttachToFrameNode(uiExtensionNode);
    pattern->OnModifyDone();

    /**
     * @tc.steps: step3. prepare focusHub and test func
     */
    auto focusHub = uiExtensionNode->GetFocusHub();
    pattern->InitKeyEvent(focusHub);
    focusHub->onFocusInternal_(focusHub->focusReason_);
    focusHub->onBlurInternal_();
    focusHub->onClearFocusStateCallback_();
    focusHub->onPaintFocusStateCallback_();
    KeyEvent keyEvent;
    focusHub->onKeyEventsInternal_[OnKeyEventType::DEFAULT].operator()(keyEvent);

    ASSERT_NE(pattern->mouseEvent_, nullptr);
    MouseInfo info;
    info.SetButton(MouseButton::RIGHT_BUTTON);
    info.SetAction(MouseAction::PRESS);
    pattern->mouseEvent_->GetOnMouseEventFunc()(info);

    ASSERT_NE(pattern->hoverEvent_, nullptr);
    pattern->hoverEvent_->GetOnHoverEventFunc()(false);

    pattern->OnModifyDone();

    pattern = nullptr;
    uiExtensionNode->pattern_ = nullptr;
    focusHub->onFocusInternal_(focusHub->focusReason_);
    focusHub->onBlurInternal_();
    focusHub->onClearFocusStateCallback_();
    focusHub->onPaintFocusStateCallback_();
    focusHub->onKeyEventsInternal_[OnKeyEventType::DEFAULT].operator()(keyEvent);
    uiExtensionNode->pattern_ = AceType::MakeRefPtr<UIExtensionPattern>();
    ASSERT_NE(uiExtensionNode->pattern_, nullptr);
#endif
}

/**
 * @tc.name: UIExtensionUsageTest
 * @tc.desc: Test pattern GetUIExtensionUsage
 * @tc.type: FUNC
 */
HWTEST_F(UIExtensionComponentTestNg, AccessibilityTest002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto uiExtensionNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto uiExtensionNode = FrameNode::GetOrCreateFrameNode(
        UI_EXTENSION_COMPONENT_ETS_TAG, uiExtensionNodeId, []() { return AceType::MakeRefPtr<UIExtensionPattern>(); });
    ASSERT_NE(uiExtensionNode, nullptr);
    EXPECT_EQ(uiExtensionNode->GetTag(), V2::UI_EXTENSION_COMPONENT_ETS_TAG);
    auto pattern = uiExtensionNode->GetPattern<UIExtensionPattern>();
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
    InValidSessionWrapper(pattern);
    pattern->InitializeAccessibility();
    pattern->OnSetAccessibilityChildTree(1, 1);
    pattern->OnAccessibilityChildTreeRegister(1, 1, 1);
    pattern->OnAccessibilityChildTreeDeregister();
    std::vector<std::string> params;
    std::vector<std::string> info;
    pattern->OnAccessibilityDumpChildInfo(params, info);
    EXPECT_EQ(params.size(), 0);
    pattern->accessibilityChildTreeCallback_ = std::make_shared<UIExtensionAccessibilityChildTreeCallback>(pattern, 1);
    pattern->InitializeAccessibility();
#endif
}

/**
 * @tc.name: UIExtensionOnConnect
 * @tc.desc: Test pattern OnConnect
 * @tc.type: FUNC
 */
HWTEST_F(UIExtensionComponentTestNg, UIExtensionOnConnectTest, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a UIExtensionComponent Node
     */
    auto uiExtensionNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto uiExtensionNode = FrameNode::GetOrCreateFrameNode(
        UI_EXTENSION_COMPONENT_ETS_TAG, uiExtensionNodeId, []() { return AceType::MakeRefPtr<UIExtensionPattern>(); });
    EXPECT_EQ(uiExtensionNode->GetTag(), V2::UI_EXTENSION_COMPONENT_ETS_TAG);
    auto pattern = uiExtensionNode->GetPattern<UIExtensionPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->AttachToFrameNode(uiExtensionNode);
    ContainerScope scope(pattern->instanceId_);
    auto contentNode_ = FrameNode::CreateFrameNode(V2::UI_EXTENSION_SURFACE_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<UIExtensionPattern>());
    contentNode_->GetLayoutProperty()->UpdateMeasureType(MeasureType::MATCH_PARENT);
    contentNode_->SetHitTestMode(HitTestMode::HTMNONE);

    /**
     * @tc.steps: step2. test OnConnect
     */
    auto host = pattern->GetHost();
    EXPECT_NE(host, nullptr);
    auto&& opts = host->GetLayoutProperty()->GetSafeAreaExpandOpts();
    auto surfaceNode = pattern->sessionWrapper_->GetSurfaceNode();
    EXPECT_NE(surfaceNode, nullptr);
    auto layoutProperty = uiExtensionNode->GetLayoutProperty();
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

    pattern->usage_ = UIExtensionUsage::MODAL;
    auto focusHub = uiExtensionNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->currentFocus_ = true;
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pattern->OnConnect();

    pattern->usage_ = UIExtensionUsage::CONSTRAINED_EMBEDDED;
    pattern->OnConnect();

    focusHub->currentFocus_ = false;
    pattern->OnConnect();

    focusHub = nullptr;
    pattern->OnConnect();

    pattern->sessionWrapper_  = nullptr;
    pattern->OnConnect();
#endif
}

/**
 * @tc.name: UIExtensionHandleEventTest
 * @tc.desc: Test pattern KeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(UIExtensionComponentTestNg, UIExtensionHandleKeyEventValidSession, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto uiExtNode = CreateUecNode();
    ASSERT_NE(uiExtNode, nullptr);
    auto pattern = uiExtNode->GetPattern<UIExtensionPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->AttachToFrameNode(uiExtNode);
    ValidSession(pattern);
    KeyEvent event;
    pattern->HandleKeyEvent(event);
    pattern->DispatchKeyEvent(event);
    pattern->isKeyAsync_ = true;
    EXPECT_EQ(pattern->DispatchKeyEventSync(event), true);
    pattern->isKeyAsync_ = false;
    EXPECT_EQ(pattern->DispatchKeyEventSync(event), true);
    pattern->canFocusSendToUIExtension_ = false;
    pattern->HandleFocusEvent();
    pattern->DispatchFocusActiveEvent(true);
    pattern->DispatchFocusState(true);
    EXPECT_EQ(pattern->canFocusSendToUIExtension_, true);
    pattern->canFocusSendToUIExtension_ = true;
    pattern->HandleFocusEvent();
    pattern->DispatchFocusActiveEvent(true);
    pattern->DispatchFocusState(true);
    EXPECT_EQ(pattern->canFocusSendToUIExtension_, true);
    pattern->HandleBlurEvent();
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto focusManager = pipeline->GetOrCreateFocusManager();
    ASSERT_NE(focusManager, nullptr);
    focusManager->isFocusActive_ = true;
    ASSERT_TRUE(pipeline->GetIsFocusActive());
    pattern->HandleFocusEvent();
    pattern->isKeyAsync_ = true;
    event.code = { KeyCode::KEY_TAB };
    pattern->DispatchKeyEventSync(event);
    event.code = { KeyCode::KEY_SPACE };
    pattern->DispatchKeyEventSync(event);
#endif
}

HWTEST_F(UIExtensionComponentTestNg, UIExtensionHandleKeyEventInValidSession, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto uiExtNode = CreateUecNode();
    ASSERT_NE(uiExtNode, nullptr);
    auto pattern = uiExtNode->GetPattern<UIExtensionPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->AttachToFrameNode(uiExtNode);
    InValidSession(pattern);
    KeyEvent event;
    pattern->HandleKeyEvent(event);
    pattern->DispatchKeyEvent(event);
    pattern->isKeyAsync_ = true;
    EXPECT_EQ(pattern->DispatchKeyEventSync(event), true);
    pattern->isKeyAsync_ = false;
    EXPECT_EQ(pattern->DispatchKeyEventSync(event), true);
    pattern->canFocusSendToUIExtension_ = false;
    pattern->HandleFocusEvent();
    pattern->DispatchFocusActiveEvent(true);
    pattern->DispatchFocusState(true);
    EXPECT_EQ(pattern->canFocusSendToUIExtension_, true);
    pattern->canFocusSendToUIExtension_ = true;
    pattern->HandleFocusEvent();
    pattern->DispatchFocusActiveEvent(true);
    pattern->DispatchFocusState(true);
    EXPECT_EQ(pattern->canFocusSendToUIExtension_, true);
    pattern->HandleBlurEvent();
#endif
}

/**
 * @tc.name: UIExtensionHandleEventTest
 * @tc.desc: Test pattern TouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(UIExtensionComponentTestNg, UIExtensionHandleTouchEventValidSession, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a UIExtensionComponent Node
     */
    auto uiExtNode = CreateUecNode();
    ASSERT_NE(uiExtNode, nullptr);
    auto pattern = uiExtNode->GetPattern<UIExtensionPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->AttachToFrameNode(uiExtNode);
    ValidSession(pattern);
    pattern->canFocusSendToUIExtension_ = true;
    pattern->needReSendFocusToUIExtension_ = false;

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
    auto focusHub = uiExtNode->GetFocusHub();
    focusHub->currentFocus_ = true;
    pattern->HandleTouchEvent(touchEventInfo);
    focusHub->currentFocus_ = false;
    pattern->HandleTouchEvent(touchEventInfo);

    pattern->needReSendFocusToUIExtension_ = true;
    pattern->HandleTouchEvent(touchEventInfo);

    pointerEvent->SetPointerAction(MMI::PointerEvent::POINTER_ACTION_AXIS_BEGIN);
    pattern->HandleTouchEvent(touchEventInfo);
    pointerEvent->SetPointerAction(MMI::PointerEvent::POINTER_ACTION_LEAVE_WINDOW);
    pattern->HandleTouchEvent(touchEventInfo);
    pattern->DispatchPointerEvent(pointerEvent);
    EXPECT_EQ(pattern->canFocusSendToUIExtension_, true);
#endif
}

HWTEST_F(UIExtensionComponentTestNg, UIExtensionHandleTouchEventInValidSession, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto uiExtNode = CreateUecNode();
    ASSERT_NE(uiExtNode, nullptr);
    auto pattern = uiExtNode->GetPattern<UIExtensionPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->AttachToFrameNode(uiExtNode);
    InValidSession(pattern);
    pattern->canFocusSendToUIExtension_ = true;
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
    auto focusHub = uiExtNode->GetFocusHub();
    focusHub->currentFocus_ = false;
    pattern->HandleTouchEvent(touchEventInfo);
    focusHub->currentFocus_ = true;
    pattern->needReSendFocusToUIExtension_ = false;
    pattern->HandleTouchEvent(touchEventInfo);
    pattern->needReSendFocusToUIExtension_ = true;
    pattern->HandleTouchEvent(touchEventInfo);
    pointerEvent->SetPointerAction(MMI::PointerEvent::POINTER_ACTION_LEAVE_WINDOW);
    pattern->HandleTouchEvent(touchEventInfo);
    pattern->DispatchPointerEvent(pointerEvent);
    EXPECT_EQ(pattern->canFocusSendToUIExtension_, true);
#endif
}

HWTEST_F(UIExtensionComponentTestNg, UIExtensionHandleMouseEventValidSession, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a UIExtensionComponent Node
     */
    auto uiExtNode = CreateUecNode();
    ASSERT_NE(uiExtNode, nullptr);
    auto pattern = uiExtNode->GetPattern<UIExtensionPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->AttachToFrameNode(uiExtNode);
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
    EXPECT_EQ(pattern->canFocusSendToUIExtension_, true);
    pattern->displayArea_ = RectF(0.0, 0.0, 0.0, 0.0);
    pattern->DispatchDisplayArea(true);
    pattern->DispatchDisplayArea(false);
    pattern->displayArea_ = RectF(100.0, 100.0, 100.0, 100.0);
    pattern->DispatchDisplayArea(true);
    pattern->DispatchDisplayArea(false);
    EXPECT_EQ(pattern->canFocusSendToUIExtension_, true);
    auto sessionWrapper = AceType::DynamicCast<SessionWrapperImpl>(pattern->sessionWrapper_);
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

HWTEST_F(UIExtensionComponentTestNg, UIExtensionHandleMouseEventInValidSession, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto uiExtNode = CreateUecNode();
    ASSERT_NE(uiExtNode, nullptr);
    auto pattern = uiExtNode->GetPattern<UIExtensionPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->AttachToFrameNode(uiExtNode);
    InValidSession(pattern);
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
    EXPECT_EQ(pattern->canFocusSendToUIExtension_, true);
    pattern->displayArea_ = RectF(0.0, 0.0, 0.0, 0.0);
    pattern->DispatchDisplayArea(true);
    pattern->DispatchDisplayArea(false);
    pattern->displayArea_ = RectF(100.0, 100.0, 100.0, 100.0);
    pattern->DispatchDisplayArea(true);
    pattern->DispatchDisplayArea(false);
    EXPECT_EQ(pattern->canFocusSendToUIExtension_, true);
    auto sessionWrapper = AceType::DynamicCast<SessionWrapperImpl>(pattern->sessionWrapper_);
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
 * @tc.name: UIExtensionPlaceholderTest
 * @tc.desc: Test pattern SetPlaceholder/MountPlaceholder/RemovePlaceholder
 * @tc.type: FUNC
 */
HWTEST_F(UIExtensionComponentTestNg, UIExtensionPlaceholderTest, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto uiExtensionNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto uiExtensionNode = FrameNode::GetOrCreateFrameNode(
        UI_EXTENSION_COMPONENT_ETS_TAG, uiExtensionNodeId, []() { return AceType::MakeRefPtr<UIExtensionPattern>(); });
    ASSERT_NE(uiExtensionNode, nullptr);
    EXPECT_EQ(uiExtensionNode->GetTag(), V2::UI_EXTENSION_COMPONENT_ETS_TAG);
    auto pattern = uiExtensionNode->GetPattern<UIExtensionPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_EQ(pattern->IsShowPlaceholder(), false);
    pattern->AttachToFrameNode(uiExtensionNode);
    pattern->OnModifyDone();
    EXPECT_EQ(pattern->IsShowPlaceholder(), false);
    pattern->MountPlaceholderNode(PlaceholderType::INITIAL);
    EXPECT_EQ(pattern->IsShowPlaceholder(), false);
    pattern->RemovePlaceholderNode();
    EXPECT_EQ(pattern->IsShowPlaceholder(), false);
    SetPlaceholder(pattern);
    pattern->MountPlaceholderNode(PlaceholderType::UNDEFINED);
    EXPECT_EQ(pattern->IsShowPlaceholder(), false);
    pattern->MountPlaceholderNode(PlaceholderType::INITIAL);
    EXPECT_EQ(pattern->IsShowPlaceholder(), true);
    EXPECT_EQ(pattern->curPlaceholderType_, PlaceholderType::INITIAL);
    pattern->MountPlaceholderNode(PlaceholderType::ROTATION);
    EXPECT_EQ(pattern->IsShowPlaceholder(), true);
    EXPECT_EQ(pattern->curPlaceholderType_, PlaceholderType::INITIAL);
    pattern->ReplacePlaceholderByContent();
    EXPECT_EQ(pattern->IsShowPlaceholder(), false);
    pattern->MountPlaceholderNode(PlaceholderType::ROTATION);
    EXPECT_EQ(pattern->IsShowPlaceholder(), true);
    EXPECT_EQ(pattern->curPlaceholderType_, PlaceholderType::ROTATION);
    pattern->RemovePlaceholderNode();
    EXPECT_EQ(pattern->IsShowPlaceholder(), false);
    pattern->RemovePlaceholderNode();
    EXPECT_EQ(pattern->IsShowPlaceholder(), false);
    pattern->curPlaceholderType_ = PlaceholderType::NONE;
    pattern->ReplacePlaceholderByContent();
#endif
}

/**
 * @tc.name: UIExtensionComponentTest002
 * @tc.desc: Test pattern SetDensityDpi function
 * @tc.type: FUNC
 */
HWTEST_F(UIExtensionComponentTestNg, UIExtensionComponentTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a UIExtensionComponent Node
     */
    auto uiExtensionNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto uiExtensionNode = FrameNode::GetOrCreateFrameNode(
        UI_EXTENSION_COMPONENT_ETS_TAG, uiExtensionNodeId, []() { return AceType::MakeRefPtr<UIExtensionPattern>(); });
    ASSERT_NE(uiExtensionNode, nullptr);
    EXPECT_EQ(uiExtensionNode->GetTag(), V2::UI_EXTENSION_COMPONENT_ETS_TAG);

    /**
     * @tc.steps: step2. get pattern
     */
    auto pattern = uiExtensionNode->GetPattern<UIExtensionPattern>();
    ASSERT_NE(pattern, nullptr);
    bool densityDpi = pattern->GetDensityDpi();
    EXPECT_FALSE(densityDpi);

    /**
     * @tc.steps: step3. SetDensityDpi false
     */
    pattern->SetDensityDpi(false);
    densityDpi = pattern->GetDensityDpi();
    EXPECT_FALSE(densityDpi);

    /**
     * @tc.steps: step4. SetDensityDpi true
     */
    pattern->SetDensityDpi(true);
    densityDpi = pattern->GetDensityDpi();
    EXPECT_TRUE(densityDpi);
}

/**
 * @tc.name: UIExtensionComponentTest003
 * @tc.desc: Test pattern OnTerminated
 * @tc.type: FUNC
 */
HWTEST_F(UIExtensionComponentTestNg, UIExtensionComponentTest003, TestSize.Level1)
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
    /**
     * @tc.steps: step2. Get pattern
     */
    auto pattern = uiExtensionNode->GetPattern<UIExtensionPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step3. Test not compatible oldVersion and OnTerminated
     */
    auto onTerminatedFuntion =
        [](int32_t code, const RefPtr<WantWrap>& wantWrap) { EXPECT_EQ(code, CODE); };
    pattern->SetOnTerminatedCallback(onTerminatedFuntion);
    pattern->FireOnTerminatedCallback(CODE, nullptr);
    EXPECT_FALSE(pattern->IsCompatibleOldVersion());
    /**
     * @tc.steps: step3. Test compatible oldVersion
     */
    pattern->SetOnTerminatedCallback(nullptr);
    pattern->FireOnTerminatedCallback(CODE, nullptr);
    EXPECT_TRUE(pattern->IsCompatibleOldVersion());
    /**
     * @tc.steps: step4. Test onError
     */
    auto onError =
        [](int32_t code, const std::string& name, const std::string& message) {
            EXPECT_EQ(code, CODE);
            EXPECT_EQ(name, NAME);
            EXPECT_EQ(message, MSG);
        };
    pattern->SetOnErrorCallback(std::move(onError));
    pattern->FireOnErrorCallback(CODE, NAME, MSG);
    auto onError2 =
        [](int32_t code, const std::string& name, const std::string& message) {
            EXPECT_EQ(code, 0);
            EXPECT_EQ(name, "extension_node_transparent");
            EXPECT_EQ(message, MSG);
        };
    pattern->SetOnErrorCallback(std::move(onError2));
    pattern->onReleaseCallback_ = nullptr;
    pattern->curPlaceholderType_ = PlaceholderType::UNDEFINED;
    pattern->lastError_.code = 0;
    pattern->FireOnErrorCallback(0, "extension_node_transparent", MSG);
#endif
}

/**
 * @tc.name: UIExtensionComponentTest004
 * @tc.desc: Test UIExtensionAccessibilityChildTreeCallback
 * @tc.type: FUNC
 */
HWTEST_F(UIExtensionComponentTestNg, UIExtensionComponentTest004, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct an UIExtensionAccessibilityChildTreeCallback
     */
    auto uiExtensionNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto uiExtensionNode = FrameNode::GetOrCreateFrameNode(
        UI_EXTENSION_COMPONENT_ETS_TAG, uiExtensionNodeId, []() { return AceType::MakeRefPtr<UIExtensionPattern>(); });
    ASSERT_NE(uiExtensionNode, nullptr);
    EXPECT_EQ(uiExtensionNode->GetTag(), V2::UI_EXTENSION_COMPONENT_ETS_TAG);
    auto pattern = uiExtensionNode->GetPattern<UIExtensionPattern>();
    ASSERT_NE(pattern, nullptr);
    ASSERT_NE(pattern->GetAccessibilitySessionAdapter(), nullptr);
    ASSERT_NE(pattern->CreateLayoutAlgorithm(), nullptr);
    ASSERT_FALSE(pattern->IsModalUec());
    pattern->usage_ = UIExtensionUsage::MODAL;
    ASSERT_TRUE(pattern->IsModalUec());
    ASSERT_FALSE(pattern->IsForeground());
    pattern->state_ = OHOS::Ace::NG::UIExtensionPattern::AbilityState::FOREGROUND;
    ASSERT_TRUE(pattern->IsForeground());
    UIExtensionAccessibilityChildTreeCallback callback = UIExtensionAccessibilityChildTreeCallback(pattern, 1);
    ASSERT_FALSE(callback.isReg_);

    /**
     * @tc.steps: step2. Test OnRegister
     */
    ASSERT_TRUE(callback.OnRegister(1, 1));
    ASSERT_TRUE(callback.isReg_);
    ASSERT_TRUE(callback.OnRegister(1, 1));
    auto weakPtr = WeakPtr<UIExtensionPattern>(nullptr);
    UIExtensionAccessibilityChildTreeCallback callbackNull = UIExtensionAccessibilityChildTreeCallback(weakPtr, 1);
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
 * @tc.name: UIExtensionComponentTest005
 * @tc.desc: Test pattern Test DumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(UIExtensionComponentTestNg, UIExtensionComponentTest005, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a UIExtensionComponent Node
     */
    auto uiExtNode = CreateUecNode();
    ASSERT_NE(uiExtNode, nullptr);
    auto pattern = uiExtNode->GetPattern<UIExtensionPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->AttachToFrameNode(uiExtNode);
    auto sessionWrapper = AceType::DynamicCast<SessionWrapperImpl>(pattern->sessionWrapper_);
    ASSERT_NE(sessionWrapper, nullptr);

    /**
     * @tc.steps: step2. Test DumpInfo
     */
    pattern->platformEventProxy_ = nullptr;
    ASSERT_EQ(pattern->platformEventProxy_, nullptr);
    pattern->DumpInfo();

    pattern->platformEventProxy_ = AceType::MakeRefPtr<PlatformEventProxy>();
    ASSERT_NE(pattern->platformEventProxy_, nullptr);
    pattern->DumpInfo();

    std::string testJson = "";
    std::unique_ptr<JsonValue> testValue = JsonUtil::ParseJsonString(testJson);
    pattern->DumpInfo(testValue);

    /**
     * @tc.steps: step3. Test WrapExtensionAbilityId
     */
    ASSERT_EQ(pattern->WrapExtensionAbilityId(0, 0), 0);

    /**
     * @tc.steps: step4. Test SetWantWrap
     */
    RefPtr<WantWrap> wantOhos = AceType::MakeRefPtr<WantWrapOhos>("123", "123");
    pattern->SetWantWrap(wantOhos);
    ASSERT_NE(pattern->GetWantWrap(), nullptr);

    /**
     * @tc.steps: step5. Test DispatchOriginAvoidArea
     */
    Rosen::AvoidArea avoidArea;
    pattern->DispatchOriginAvoidArea(avoidArea, 1);
    pattern->OnColorConfigurationUpdate();
    pattern->OnLanguageConfigurationUpdate();
#endif
}

/**
 * @tc.name: UIExtensionComponentTest006
 * @tc.desc: Test pattern Test UpdateWant
 * @tc.type: FUNC
 */
HWTEST_F(UIExtensionComponentTestNg, UIExtensionComponentTest006, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a UIExtensionComponent Node
     */
    auto uiExtNode = CreateUecNode();
    ASSERT_NE(uiExtNode, nullptr);
    auto pattern = uiExtNode->GetPattern<UIExtensionPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->AttachToFrameNode(uiExtNode);

    /**
     * @tc.steps: step2. prepare the param
     */
    OHOS::AAFwk::Want want;
    want.SetElementName("123", "456", "");

    RefPtr<WantWrap> wantWrap = AceType::MakeRefPtr<WantWrapOhos>("123", "123");
    auto wantWrapOhos = AceType::DynamicCast<WantWrapOhos>(wantWrap);
    auto want2 = wantWrapOhos->GetWant();

    pattern->instanceId_ = 1;
    ASSERT_FALSE(pattern->CheckConstraint());
    ASSERT_NE(pattern->sessionWrapper_, nullptr);

    /**
     * @tc.steps: step3. test UpdateWant
     */
    pattern->UpdateWant(want);
    pattern->instanceId_ = 2;
    ASSERT_TRUE(pattern->CheckConstraint());

    ASSERT_TRUE(pattern->sessionWrapper_->IsSessionValid());
    ASSERT_TRUE(pattern->sessionWrapper_->GetWant()->IsEquals(want2));
    pattern->UpdateWant(want);
    ASSERT_FALSE(pattern->sessionWrapper_->GetWant()->IsEquals(want));
    pattern->UpdateWant(want2);

    InValidSession(pattern);
    ASSERT_FALSE(pattern->sessionWrapper_->IsSessionValid());

    pattern->state_ = OHOS::Ace::NG::UIExtensionPattern::AbilityState::BACKGROUND;
    pattern->UpdateWant(want);
    EXPECT_EQ(pattern->state_, OHOS::Ace::NG::UIExtensionPattern::AbilityState::BACKGROUND);

    pattern->state_ = OHOS::Ace::NG::UIExtensionPattern::AbilityState::FOREGROUND;
    pattern->UpdateWant(want);
    EXPECT_EQ(pattern->state_, OHOS::Ace::NG::UIExtensionPattern::AbilityState::FOREGROUND);

    pattern->instanceId_ = 6;
    pattern->UpdateWant(want);

    pattern->sessionType_ = SessionType::EMBEDDED_UI_EXTENSION;
    pattern->hasMountToParent_ = true;
    pattern->UpdateWant(want);

    pattern->sessionType_ = SessionType::EMBEDDED_UI_EXTENSION;
    pattern->hasMountToParent_ = false;
    pattern->UpdateWant(want);
#endif
}

/**
 * @tc.name: UIExtensionComponentTest007
 * @tc.desc: Test pattern Test AfterMountToParent
 * @tc.type: FUNC
 */
HWTEST_F(UIExtensionComponentTestNg, UIExtensionComponentTest007, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a UIExtensionComponent Node
     */
    auto uiExtNode = CreateUecNode();
    ASSERT_NE(uiExtNode, nullptr);
    auto pattern = uiExtNode->GetPattern<UIExtensionPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->AttachToFrameNode(uiExtNode);
    ASSERT_NE(pattern->sessionWrapper_, nullptr);

    std::vector<std::string> params;
    std::vector<std::string> info;
    pattern->OnAccessibilityDumpChildInfo(params, info);

    ASSERT_FALSE(pattern->needReNotifyForeground_);
    pattern->AfterMountToParent();

    DirtySwapConfig config;
    pattern->OnSyncGeometryNode(config);
    pattern->needReDispatchDisplayArea_ = true;
    pattern->ReDispatchDisplayArea();
    ASSERT_FALSE(pattern->needReDispatchDisplayArea_);
    pattern->ReDispatchDisplayArea();

    pattern->needReNotifyForeground_= true;
    pattern->AfterMountToParent();

    pattern->needReNotifyForeground_= true;
    pattern->OnSyncGeometryNode(config);

    /**
     * @tc.steps: step2. test OnMountToParentDone
     */
    ASSERT_FALSE(pattern->needReNotifyForeground_);
    pattern->OnMountToParentDone();
    ASSERT_FALSE(pattern->needReNotifyForeground_);
    pattern->OnMountToParentDone();

    /**
     * @tc.steps: step3. test HandleVisibleAreaChange
     */
    pattern->curVisible_ = true;
    pattern->HandleVisibleAreaChange(true, SHOW_FULL);
    pattern->HandleVisibleAreaChange(true, SHOW_START);
    pattern->HandleVisibleAreaChange(false, SHOW_FULL);
    pattern->HandleVisibleAreaChange(false, SHOW_START);

    /**
     * @tc.steps: step4. test DispatchPointerEvent
     */
    std::shared_ptr<MMI::PointerEvent> pointerEvent = nullptr;
    pattern->DispatchPointerEvent(pointerEvent);

    pointerEvent = std::make_shared<MMI::PointerEvent>(1);
    ASSERT_NE(pattern->sessionWrapper_, nullptr);
    pattern->DispatchPointerEvent(pointerEvent);

    pattern->sessionWrapper_ = nullptr;
    ASSERT_EQ(pattern->sessionWrapper_, nullptr);
    pattern->DispatchPointerEvent(pointerEvent);
#endif
}

/**
 * @tc.name: UIExtensionComponentTest008
 * @tc.desc: Test pattern Test GetSizeChangeReason, DumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(UIExtensionComponentTestNg, UIExtensionComponentTest008, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a UIExtensionComponent Node
     */
    auto uiExtNode = CreateUecNode();
    ASSERT_NE(uiExtNode, nullptr);
    auto pattern = uiExtNode->GetPattern<UIExtensionPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->AttachToFrameNode(uiExtNode);
    ASSERT_NE(pattern->sessionWrapper_, nullptr);

    /**
     * @tc.steps: step2. test GetSizeChangeReason
     */
    pattern->isFoldStatusChanged_ = false;
    pattern->isRotateStatusChanged_ = true;
    ASSERT_EQ(pattern->GetSizeChangeReason(), PlaceholderType::ROTATION);
    pattern->isRotateStatusChanged_ = false;
    ASSERT_EQ(pattern->GetSizeChangeReason(), PlaceholderType::UNDEFINED);
    pattern->isFoldStatusChanged_ = true;
    ASSERT_EQ(pattern->GetSizeChangeReason(), PlaceholderType::FOLD_TO_EXPAND);

    pattern->OnWindowSizeChanged(0, 0, OHOS::Ace::WindowSizeChangeReason::UNDEFINED);
    pattern->OnWindowSizeChanged(0, 0, WindowSizeChangeReason::ROTATION);

    /**
     * @tc.steps: step3. test DumpInfo
     */
    std::string testJson = "[0, 1, 2, 3, 4, 5, 6, 7, 8, 9]";
    std::unique_ptr<JsonValue> arrayValue = JsonUtil::ParseJsonString(testJson);
    pattern->instanceId_ = 2;
    pattern->DumpInfo();
    pattern->DumpInfo(arrayValue);
    pattern->instanceId_ = 1;
    pattern->DumpInfo();
    pattern->DumpInfo(arrayValue);
    pattern->instanceId_ = 4;
    pattern->DumpInfo();
    pattern->DumpInfo(arrayValue);
    pattern->instanceId_ = 3;
    pattern->DumpInfo();
    pattern->DumpInfo(arrayValue);
#endif
}

/**
 * @tc.name: UIExtensionComponentTest009
 * @tc.desc: Test pattern Test UpdateWant
 * @tc.type: FUNC
 */
HWTEST_F(UIExtensionComponentTestNg, UIExtensionComponentTest009, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a UIExtensionComponent Node
     */
    auto uiExtNode = CreateUecNode();
    ASSERT_NE(uiExtNode, nullptr);
    auto pattern = uiExtNode->GetPattern<UIExtensionPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->AttachToFrameNode(uiExtNode);
    ASSERT_NE(pattern->sessionWrapper_, nullptr);

    /**
     * @tc.steps: step2. prepare the param
     */
    OHOS::AAFwk::Want want;
    want.SetElementName("123", "456", "");

    /**
     * @tc.steps: step3. test UpdateWant
     */
    ASSERT_TRUE(pattern->CheckConstraint());
    InValidSession(pattern);
    ASSERT_FALSE(pattern->sessionWrapper_->IsSessionValid());

    pattern->state_ = OHOS::Ace::NG::UIExtensionPattern::AbilityState::BACKGROUND;
    EXPECT_EQ(pattern->state_, OHOS::Ace::NG::UIExtensionPattern::AbilityState::BACKGROUND);

    pattern->state_ = OHOS::Ace::NG::UIExtensionPattern::AbilityState::FOREGROUND;
    EXPECT_EQ(pattern->state_, OHOS::Ace::NG::UIExtensionPattern::AbilityState::FOREGROUND);

    pattern->instanceId_ = 6;

    pattern->sessionType_ = SessionType::EMBEDDED_UI_EXTENSION;
    pattern->hasMountToParent_ = true;

    pattern->sessionType_ = SessionType::EMBEDDED_UI_EXTENSION;
    pattern->hasMountToParent_ = false;

    pattern->sessionType_ = SessionType::UI_EXTENSION_ABILITY;
    pattern->isModal_ = true;
    pattern->hasMountToParent_ = true;
    pattern->UpdateWant(want);

    pattern->sessionType_ = SessionType::UI_EXTENSION_ABILITY;
    pattern->isModal_ = false;
    pattern->hasMountToParent_ = true;
    pattern->UpdateWant(want);

    pattern->sessionType_ = SessionType::UI_EXTENSION_ABILITY;
    pattern->isModal_ = true;
    pattern->hasMountToParent_ = false;
    pattern->UpdateWant(want);

    pattern->instanceId_ = -2;
    pattern->UpdateWant(want);
#endif
}

/**
 * @tc.name: SecurityUIExtensionComponentNgTest001
 * @tc.desc: Test the method of GetUiExtensionType in UIExtensionModelNG and SecurityUIExtensionPattern
 * @tc.type: FUNC
 */
HWTEST_F(UIExtensionComponentTestNg, SecurityUIExtensionComponentNgTest001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a SecurityUIExtensionComponent Node
     */
    UIExtensionModelNG uecNG;
    UIExtensionConfig config;
    OHOS::AAFwk::Want want;
    want.SetElementName("com.example", "testuea");
    want.SetParam("ability.want.params.uiExtensionType", std::string("sys/CommonUI"));
    config.sessionType = NG::SessionType::SECURITY_UI_EXTENSION_ABILITY;
    auto placeholderId = ElementRegister::GetInstance()->MakeUniqueId();
    auto placeholderNode =
        FrameNode::GetOrCreateFrameNode("placeholder", placeholderId, []() { return AceType::MakeRefPtr<Pattern>(); });
    config.placeholderNode = placeholderNode;
    config.wantWrap = AceType::MakeRefPtr<WantWrapOhos>(want);
    config.sessionType = NG::SessionType::SECURITY_UI_EXTENSION_ABILITY;
    uecNG.Create(config);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    /**
     * @tc.steps: step2. Expected SecurityUIExtension Node create success
     */
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::UI_EXTENSION_COMPONENT_ETS_TAG);
    /**
     * @tc.steps: step3. Expect UiExtensionType to get successfully under different SessionType
     */
    EXPECT_EQ(uecNG.GetUiExtensionType(SessionType::SECURITY_UI_EXTENSION_ABILITY), "sys/CommonUI");
    EXPECT_EQ(uecNG.GetUiExtensionType(SessionType::EMBEDDED_UI_EXTENSION), "");
#endif
}

/**
 * @tc.name: UIExtensionComponentNgTest
 * @tc.desc: Test the method of pattern CheckConstraint
 * @tc.type: FUNC
 */
HWTEST_F(UIExtensionComponentTestNg, SecurityUIExtensionComponentNgTest002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a SecurityUIExtensionComponent Node
     */
    UIExtensionModelNG uecNG;
    UIExtensionConfig config;
    OHOS::AAFwk::Want want;
    want.SetElementName("com.example", "testuea");
    want.SetParam("ability.want.params.uiExtensionType", std::string("sysPicker/PhotoPicker"));
    config.sessionType = NG::SessionType::SECURITY_UI_EXTENSION_ABILITY;
    auto placeholderId = ElementRegister::GetInstance()->MakeUniqueId();
    auto placeholderNode =
        FrameNode::GetOrCreateFrameNode("placeholder", placeholderId, []() { return AceType::MakeRefPtr<Pattern>(); });
    config.placeholderNode = placeholderNode;
    config.wantWrap = AceType::MakeRefPtr<WantWrapOhos>(want);
    config.sessionType = NG::SessionType::SECURITY_UI_EXTENSION_ABILITY;
    uecNG.Create(config);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    /**
     * @tc.steps: step2. Expected CheckConstraint false under container type in SECURITY_UI_EXTENSION
     */
    auto pattern = frameNode->GetPattern<SecurityUIExtensionPattern>();
    pattern->instanceId_ = 1;
    EXPECT_EQ(pattern->CheckConstraint(), false);
    /**
     * @tc.steps: step3. Expected CheckConstraint true under container type not in SECURITY_UI_EXTENSION and
     * IsUIExtensionWindow is false
     */
    pattern->instanceId_ = 2;
    EXPECT_EQ(pattern->CheckConstraint(), true);
    /**
     * @tc.steps: step4. Expected CheckConstraint false under PREVIEW
     */
    #ifdef PREVIEW
    EXPECT_EQ(pattern->CheckConstraint(), false);
    #endif
    /**
     * @tc.steps: step5. Expected CheckConstraint false IsUIExtensionWindow is true
     */
    pattern->instanceId_ = 4;
    EXPECT_EQ(pattern->CheckConstraint(), false);
#endif
}

/**
 * @tc.name: UIExtensionComponentTest010
 * @tc.desc: Test pattern Test OnExtensionEvent, OnUeaAccessibilityEventAsync, OnExtensionDetachToDisplay
 * @tc.type: FUNC
 */
HWTEST_F(UIExtensionComponentTestNg, UIExtensionComponentTest010, TestSize.Level1)
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
        UI_EXTENSION_COMPONENT_ETS_TAG, uiExtensionNodeId, []() { return AceType::MakeRefPtr<UIExtensionPattern>(); });
    ASSERT_NE(uiExtensionNode, nullptr);
    EXPECT_EQ(uiExtensionNode->GetTag(), V2::UI_EXTENSION_COMPONENT_ETS_TAG);
    auto pattern = uiExtensionNode->GetPattern<UIExtensionPattern>();
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
    ASSERT_NE(pattern->sessionWrapper_, nullptr);
    ASSERT_EQ(pattern->accessibilityChildTreeCallback_, nullptr);
    pattern->OnUeaAccessibilityEventAsync();

    pattern->accessibilityChildTreeCallback_ = std::make_shared<UIExtensionAccessibilityChildTreeCallback>(pattern, 1);
    ASSERT_NE(pattern->accessibilityChildTreeCallback_, nullptr);

    auto frameNode = pattern->frameNode_.Upgrade();
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

    /**
     * @tc.steps: step4. test OnExtensionDetachToDisplay
     */
    pattern->contentNode_ = FrameNode::CreateFrameNode(V2::UI_EXTENSION_SURFACE_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<UIExtensionPattern>());
    ASSERT_NE(pattern->contentNode_, nullptr);
    pattern->OnExtensionDetachToDisplay();

    pattern->contentNode_ = nullptr;
    ASSERT_EQ(pattern->contentNode_, nullptr);
    pattern->OnExtensionDetachToDisplay();
#endif
}

/**
 * @tc.name: UIExtensionComponentTest011
 * @tc.desc: Test pattern Test DumpOthers
 * @tc.type: FUNC
 */
HWTEST_F(UIExtensionComponentTestNg, UIExtensionComponentTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a UIExtensionComponent Node
     */
    auto uiExtNode = CreateUecNode();
    ASSERT_NE(uiExtNode, nullptr);
    auto pattern = uiExtNode->GetPattern<UIExtensionPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. test DumpOthers
     */
    pattern->AttachToFrameNode(uiExtNode);
    auto sessionWrapper = AceType::DynamicCast<SessionWrapperImpl>(pattern->sessionWrapper_);
    ASSERT_NE(sessionWrapper, nullptr);
    pattern->DumpOthers();

    pattern->instanceId_ = 2;
    pattern->DumpOthers();
}

/**
 * @tc.name: UIExtensionComponentTest012
 * @tc.desc: Test pattern Test GetUiExtensionId/GetInstanceId
 * @tc.type: FUNC
 */
HWTEST_F(UIExtensionComponentTestNg, UIExtensionComponentTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a UIExtensionComponent Node
     */
    auto uiExtNode = CreateUecNode();
    ASSERT_NE(uiExtNode, nullptr);
    auto pattern = uiExtNode->GetPattern<UIExtensionPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->AttachToFrameNode(uiExtNode);
    ValidSession(pattern);

    /**
     * @tc.steps: step2. test GetUiExtensionId
     */
    auto uiExtensionId = pattern->uiExtensionId_;
    ASSERT_EQ(pattern->GetUiExtensionId(), uiExtensionId);

     /**
     * @tc.steps: step2. test GetInstanceId
     */
    auto instanceId = pattern->instanceId_;
    ASSERT_EQ(pattern->GetInstanceId(), instanceId);
}

/**
 * @tc.name: UIExtensionComponentTest013
 * @tc.desc: Test pattern Test OnDisconnect/NotifySizeChangeReason/RegisterVisibleAreaChange
 * @tc.type: FUNC
 */
HWTEST_F(UIExtensionComponentTestNg, UIExtensionComponentTest013, TestSize.Level1)
{
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
    pattern->OnDisconnect(true);

    /**
     * @tc.steps: step3. test NotifySizeChangeReason
     */
    std::shared_ptr<Rosen::RSTransaction> rsTransaction;
    pattern->NotifySizeChangeReason(WindowSizeChangeReason::RESIZE, rsTransaction);

    /**
     * @tc.steps: step4. test RegisterVisibleAreaChange
     */
    pattern->RegisterVisibleAreaChange();
}

/**
 * @tc.name: UIExtensionComponentTestNotifyWindowMode
 * @tc.desc: Test pattern SetIsWindowModeFollowHost/GetIsWindowModeFollowHost function
 * @tc.type: FUNC
 */
HWTEST_F(UIExtensionComponentTestNg, UIExtensionComponentTestNotifyWindowMode, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a UIExtensionComponent Node
     */
    auto uiExtensionNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto uiExtensionNode = FrameNode::GetOrCreateFrameNode(
        UI_EXTENSION_COMPONENT_ETS_TAG, uiExtensionNodeId, []() { return AceType::MakeRefPtr<UIExtensionPattern>(); });
    ASSERT_NE(uiExtensionNode, nullptr);
    EXPECT_EQ(uiExtensionNode->GetTag(), V2::UI_EXTENSION_COMPONENT_ETS_TAG);

    /**
     * @tc.steps: step2. default false
     */
    auto pattern = uiExtensionNode->GetPattern<UIExtensionPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_FALSE(pattern->GetIsWindowModeFollowHost());

    /**
     * @tc.steps: step3. SetIsWindowModeFollowHost false
     */
    pattern->SetIsWindowModeFollowHost(false);
    EXPECT_FALSE(pattern->GetIsWindowModeFollowHost());

    /**
     * @tc.steps: step4. SetIsWindowModeFollowHost true
     */
    pattern->SetIsWindowModeFollowHost(true);
    EXPECT_TRUE(pattern->GetIsWindowModeFollowHost());
}


/**
 * @tc.name: UIExtensionComponentTest014
 * @tc.desc: Test pattern OnAttachToMainTree OnDetachFromMainTree
 * @tc.type: FUNC
 */
HWTEST_F(UIExtensionComponentTestNg, UIExtensionComponentTest014, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. test OnAttachToMainTree
     */
    auto uiExtNode = CreateUecNode();
    ASSERT_NE(uiExtNode, nullptr);
    auto pattern = uiExtNode->GetPattern<UIExtensionPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->OnAttachToMainTree();

    /**
     * @tc.steps: step2. test OnDetachFromMainTree
     */
    pattern->OnDetachFromMainTree();
#endif
}

/**
 * @tc.name: UIExtensionComponentTest015
 * @tc.desc: Test pattern OnAttachContext
 * @tc.type: FUNC
 */
HWTEST_F(UIExtensionComponentTestNg, UIExtensionComponentTest015, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. Create UIExtensionPattern and set initial instanceId.
     */
    auto uiExtNode = CreateUecNode();
    ASSERT_NE(uiExtNode, nullptr);
    auto pattern = uiExtNode->GetPattern<UIExtensionPattern>();
    ASSERT_NE(pattern, nullptr);
    int oldInstanceId = 123;
    pattern->instanceId_ = oldInstanceId;

    /**
     * @tc.steps: step2. Call OnAttachContext with nullptr context.
     */
    pattern->OnAttachContext(nullptr);

    /**
     * @tc.expected: instanceId_ remains unchanged.
     */
    EXPECT_EQ(pattern->instanceId_, oldInstanceId);
#endif
}

/**
 * @tc.name: UIExtensionComponentTest016
 * @tc.desc: Test pattern RegisterPipelineEvent/UnRegisterPipelineEvent
 * @tc.type: FUNC
 */
HWTEST_F(UIExtensionComponentTestNg, UIExtensionComponentTest016, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. get UIExtensionPattern.
     */
    auto uiExtNode = CreateUecNode();
    ASSERT_NE(uiExtNode, nullptr);
    auto pattern = uiExtNode->GetPattern<UIExtensionPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->OnAttachToMainTree();

    /**
     * @tc.steps: step2. test RegisterPipelineEvent.
     */
    int32_t instanceId = 1;
    pattern->RegisterPipelineEvent(instanceId);

    /**
     * @tc.steps: step3. test UnRegisterPipelineEvent.
     */
    pattern->UnRegisterPipelineEvent(instanceId);
#endif
}

/**
 * @tc.name: UIExtensionComponentOnDrawReadyTestNg
 * @tc.desc: Test pattern OnDrawReady
 * @tc.type: FUNC
 */
HWTEST_F(UIExtensionComponentTestNg, UIExtensionComponentOnDrawReadyTestNg, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. get UIExtensionPattern.
     */
    auto uiExtNode = CreateUecNode();
    ASSERT_NE(uiExtNode, nullptr);
    auto pattern = uiExtNode->GetPattern<UIExtensionPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->OnAttachToMainTree();
    ValidSessionWrapper(pattern);
    ValidSession(pattern);
    /**
     * @tc.steps: step2. set placeholder.
     */
    SetPlaceholder(pattern);
    /**
     * @tc.steps: step3. test UnRegisterPipelineEvent.
     */
    pattern->MountPlaceholderNode(PlaceholderType::INITIAL);
    EXPECT_TRUE(pattern->IsShowPlaceholder());
    EXPECT_EQ(pattern->curPlaceholderType_, PlaceholderType::INITIAL);
    /**
     * @tc.steps: step4. fire OnConnect.
     */
    pattern->OnConnect();
    EXPECT_TRUE(pattern->IsShowPlaceholder());
    EXPECT_EQ(pattern->curPlaceholderType_, PlaceholderType::INITIAL);
    /**
     * @tc.steps: step4. fire OnDrawReadyCallback.
     */
    pattern->FireOnDrawReadyCallback();
    EXPECT_FALSE(pattern->IsShowPlaceholder());
    EXPECT_EQ(pattern->curPlaceholderType_, PlaceholderType::NONE);
#endif
}
} // namespace OHOS::Ace::NG
