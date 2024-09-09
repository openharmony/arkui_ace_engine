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
} // namespace

class UIExtensionComponentTestNg : public testing::Test {
public:
    void SetUp() override;
    void TearDown() override;
    static void SetUpTestSuite()
    {
        MockPipelineContext::SetUp();
        MockContainer::SetUp();
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
    };

    OHOS::AAFwk::Want want;
    want.SetElementName("123", "123", "123");
    auto uiExtNode = UIExtensionModelNG::Create(want, callbacks);
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
    };

    RefPtr<WantWrap> want = AceType::MakeRefPtr<WantWrapOhos>("123", "123");
    UIExtensionModelNG uecNG;
    std::map<PlaceholderType, RefPtr<NG::FrameNode>> placeholderMap;
    uecNG.Create(want, placeholderMap);
    uecNG.SetOnError(onError);
    uecNG.SetOnError(onError, NG::SessionType::SECURITY_UI_EXTENSION_ABILITY);
    uecNG.SetOnReceive(onReceive);
    uecNG.SetOnReceive(onReceive, NG::SessionType::SECURITY_UI_EXTENSION_ABILITY);
    uecNG.SetOnTerminated(std::move(onTerminated));
    uecNG.SetOnTerminated(std::move(onTerminated), NG::SessionType::SECURITY_UI_EXTENSION_ABILITY);

    UIExtensionConfig config;
    config.sessionType = NG::SessionType::UI_EXTENSION_ABILITY;
    uecNG.Create(config);
    config.sessionType = NG::SessionType::SECURITY_UI_EXTENSION_ABILITY;
    uecNG.Create(config);
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

    // Fire CallBack
    pattern->state_ = OHOS::Ace::NG::UIExtensionPattern::AbilityState::DESTRUCTION;
    FireCallbacks(pattern);
    pattern->state_ = OHOS::Ace::NG::UIExtensionPattern::AbilityState::FOREGROUND;
    InValidSessionWrapper(pattern);
    EXPECT_EQ(pattern->sessionWrapper_, nullptr);
    FireCallbacks(pattern);
    ValidSession(pattern);
    FireCallbacks(pattern);
    InValidSession(pattern);
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
    EXPECT_EQ(pattern->CheckConstraint(), false);
    pattern->UpdateWant(want2);
    pattern->NotifyBackground();
    EXPECT_EQ(pattern->state_, OHOS::Ace::NG::UIExtensionPattern::AbilityState::BACKGROUND);
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

    OHOS::AAFwk::Want want;
    want.SetElementName("123", "456", "123");
    InValidSession(pattern);
    pattern->UpdateWant(want);
    ValidSession(pattern);
    pattern->state_ = OHOS::Ace::NG::UIExtensionPattern::AbilityState::BACKGROUND;
    pattern->UpdateWant(want);
    EXPECT_EQ(pattern->state_, OHOS::Ace::NG::UIExtensionPattern::AbilityState::BACKGROUND);
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
    auto uiExtensionNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto uiExtensionNode = FrameNode::GetOrCreateFrameNode(
        UI_EXTENSION_COMPONENT_ETS_TAG, uiExtensionNodeId, []() { return AceType::MakeRefPtr<UIExtensionPattern>(); });
    ASSERT_NE(uiExtensionNode, nullptr);
    EXPECT_EQ(uiExtensionNode->GetTag(), V2::UI_EXTENSION_COMPONENT_ETS_TAG);
    auto pattern = uiExtensionNode->GetPattern<UIExtensionPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->AttachToFrameNode(uiExtensionNode);
    ContainerScope scope(pattern->instanceId_);
    auto contentNode_ = FrameNode::CreateFrameNode(V2::UI_EXTENSION_SURFACE_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<UIExtensionPattern>());
    contentNode_->GetLayoutProperty()->UpdateMeasureType(MeasureType::MATCH_PARENT);
    contentNode_->SetHitTestMode(HitTestMode::HTMNONE);
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
    InValidSession(pattern);
    pattern->OnConnect();
    ValidSession(pattern);
    pattern->OnConnect();
    pattern->isModal_ = false;
    pattern->OnConnect();
    pattern->isModal_ = true;
    pattern->OnConnect();
    auto focusHub = uiExtensionNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->currentFocus_ = true;
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pattern->OnConnect();
    focusHub->currentFocus_ = true;
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
    auto uiExtNode = CreateUecNode();
    ASSERT_NE(uiExtNode, nullptr);
    auto pattern = uiExtNode->GetPattern<UIExtensionPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->AttachToFrameNode(uiExtNode);
    ValidSession(pattern);
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
    auto uiExtNode = CreateUecNode();
    ASSERT_NE(uiExtNode, nullptr);
    auto pattern = uiExtNode->GetPattern<UIExtensionPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->AttachToFrameNode(uiExtNode);
    ValidSession(pattern);
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
    pattern->OnAreaUpdated();
    EXPECT_EQ(pattern->IsShowPlaceholder(), false);
    pattern->MountPlaceholderNode(PlaceholderType::ROTATION);
    EXPECT_EQ(pattern->IsShowPlaceholder(), true);
    EXPECT_EQ(pattern->curPlaceholderType_, PlaceholderType::ROTATION);
    pattern->RemovePlaceholderNode();
    EXPECT_EQ(pattern->IsShowPlaceholder(), false);
    pattern->RemovePlaceholderNode();
    EXPECT_EQ(pattern->IsShowPlaceholder(), false);
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
#endif
}
} // namespace OHOS::Ace::NG
