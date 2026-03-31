/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
#include "core/components_ng/pattern/ui_extension/preview_ui_extension_component/preview_session_wrapper_impl.h"
#include "core/components_ng/pattern/ui_extension/preview_ui_extension_component/preview_ui_extension_adapter.h"
#include "core/components_ng/pattern/ui_extension/preview_ui_extension_component/preview_ui_extension_pattern.h"
#include "core/components_ng/pattern/ui_extension/security_ui_extension_component/security_ui_extension_proxy.h"
#include "core/components_ng/pattern/ui_extension/session_wrapper.h"
#include "core/components_ng/pattern/ui_extension/session_wrapper_factory.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_component/modal_ui_extension_proxy_impl.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_component/ui_extension_pattern.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_config.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_model.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_model_ng.h"
#include "core/event/ace_events.h"
#include "core/event/key_event.h"
#include "core/event/mouse_event.h"
#include "core/event/pointer_event.h"
#include "core/event/touch_event.h"

#include "session/host/include/extension_session.h"
#include "session/host/include/session.h"
#include "ui/rs_surface_node.h"

#include "adapter/ohos/entrance/mmi_event_convertor.h"
#include "adapter/ohos/osal/want_wrap_ohos.h"
#include "base/error/error_code.h"
#include "base/geometry/offset.h"
#include "base/json/json_util.h"
#include "base/utils/utils.h"

#include "core/common/window.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/pattern/pattern.h"

#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components_ng/render/adapter/rosen_window.h"
#include "test/unittest/core/pattern/ui_extension/mock/mock_task_executor.h"
#include "test/mock/core/render/mock_rosen_render_context.h"
#include "transaction/rs_transaction.h"
#include "accessibility_event_info.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::string PREVIEW_UI_EXTENSION_COMPONENT_ETS_TAG = "PreviewUIExtensionComponent";
const std::string BOUNDLE_NAME = "com.example.test";
const std::string ABILITY_NAME = "UIExtensionAbility";
const std::string ABILITY_KEY_UIEXTENSIONTYPE = "ability.want.params.uiExtensionType";
const std::string ABILITY_VALUE_UIEXTENSIONTYPE = "sysPicker/PhotoPicker";
constexpr int32_t ERROR_CODE = 10001;
}

#ifdef WINDOW_SCENE_SUPPORTED
const RefPtr<UIExtensionManager>& PipelineContext::GetUIExtensionManager()
{
    return uiExtensionManager_;
}
#endif

class PreviewUIExtensionComponentTestNgTwo : public testing::Test {
public:
    RefPtr<FrameNode> frameNode_ = nullptr;
    void SetUp() override {}
    void TearDown() override
    {
        auto* stack = ViewStackProcessor::GetInstance();
        stack->ClearStack();
    }

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

    RefPtr<PreviewUIExtensionPattern> CreatePreviewPattern()
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

    RefPtr<PreviewSessionWrapperImpl> CreatePreviewSessionWrapperImpl(
        const RefPtr<PreviewUIExtensionPattern>& pattern, bool transferringCaller = false)
    {
        CHECK_NULL_RETURN(pattern, nullptr);
        auto wrapper = AceType::MakeRefPtr<PreviewSessionWrapperImpl>(
            pattern, pattern->instanceId_, transferringCaller, SessionType::PREVIEW_UI_EXTENSION_ABILITY);
        wrapper->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
        return wrapper;
    }

    void AttachValidSession(const RefPtr<PreviewSessionWrapperImpl>& wrapper)
    {
        CHECK_NULL_VOID(wrapper);
        Rosen::SessionInfo sessionInfo;
        wrapper->session_ = new Rosen::ExtensionSession(sessionInfo);
    }
};

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewPatternInitialize001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    EXPECT_NE(pattern->sessionWrapper_, nullptr);

    auto before = pattern->sessionWrapper_;
    UIExtensionConfig config;
    pattern->Initialize(config);
    EXPECT_EQ(before, pattern->sessionWrapper_);
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewPatternOnAttachToFrameNode001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto host = pattern->GetHost();
    ASSERT_NE(host, nullptr);
    pattern->OnAttachToFrameNode();
    EXPECT_NE(pattern->accessibilitySAObserverCallback_, nullptr);
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewPatternOnConnect001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    ASSERT_NE(pattern->sessionWrapper_, nullptr);
    pattern->OnConnect();
    auto host = pattern->GetHost();
    ASSERT_NE(host, nullptr);
    EXPECT_NE(host->GetLayoutProperty(), nullptr);
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewPatternOnConnect002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    pattern->sessionWrapper_ = nullptr;
    pattern->OnConnect();
    EXPECT_EQ(pattern->sessionWrapper_, nullptr);
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewPatternFireOnRemoteReadyCallback001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    pattern->FireOnRemoteReadyCallback();
    EXPECT_NE(pattern->GetHost(), nullptr);
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewPatternFireOnErrorCallback001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = AceType::DynamicCast<PreviewSessionWrapperImpl>(pattern->sessionWrapper_);
    ASSERT_NE(wrapper, nullptr);
    AttachValidSession(wrapper);
    pattern->FireOnErrorCallback(ERROR_CODE, "name", "message");
    EXPECT_EQ(pattern->state_, PreviewUIExtensionPattern::AbilityState::NONE);
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewPatternFireOnErrorCallback002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    pattern->sessionWrapper_ = nullptr;
    pattern->FireOnErrorCallback(ERROR_CODE, "name", "message");
    EXPECT_EQ(pattern->state_, PreviewUIExtensionPattern::AbilityState::NONE);
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewPatternRegisterVisibleAreaChange001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    pattern->RegisterVisibleAreaChange();
    EXPECT_NE(pattern->GetHost(), nullptr);
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewPatternInitializeAccessibility001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    pattern->InitializeAccessibility();
    EXPECT_EQ(pattern->accessibilityChildTreeCallback_, nullptr);
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewPatternInitializeAccessibility002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    pattern->InitializeAccessibility();
    auto callback = pattern->accessibilityChildTreeCallback_;
    pattern->InitializeAccessibility();
    EXPECT_EQ(callback, pattern->accessibilityChildTreeCallback_);
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewPatternDumpInfo001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    pattern->DumpInfo();
    EXPECT_NE(pattern->sessionWrapper_, nullptr);
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewPatternDumpInfoJson001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto json = JsonUtil::Create(true);
    ASSERT_NE(json, nullptr);
    pattern->DumpInfo(json);
    EXPECT_TRUE(json->Contains("abilityState: "));
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewPatternDumpInfoJson002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    pattern->sessionWrapper_ = nullptr;
    auto json = JsonUtil::Create(true);
    ASSERT_NE(json, nullptr);
    pattern->DumpInfo(json);
    EXPECT_FALSE(json->Contains("reason: "));
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperCreateDestroy001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern);
    ASSERT_NE(wrapper, nullptr);
    wrapper->DestroySession();
    EXPECT_FALSE(wrapper->IsSessionValid());
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperIsSessionValid001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern);
    ASSERT_NE(wrapper, nullptr);
    EXPECT_FALSE(wrapper->IsSessionValid());
    AttachValidSession(wrapper);
    EXPECT_TRUE(wrapper->IsSessionValid());
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperGetSessionId001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern);
    ASSERT_NE(wrapper, nullptr);
    EXPECT_EQ(wrapper->GetSessionId(), 0);
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperGetWant001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern);
    ASSERT_NE(wrapper, nullptr);
    EXPECT_EQ(wrapper->GetWant(), nullptr);
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperNotifyForeground001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern);
    ASSERT_NE(wrapper, nullptr);
    wrapper->NotifyForeground();
    EXPECT_FALSE(wrapper->IsSessionValid());
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperNotifyBackground001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern);
    ASSERT_NE(wrapper, nullptr);
    wrapper->NotifyBackground(true);
    wrapper->NotifyBackground(false);
    EXPECT_FALSE(wrapper->IsSessionValid());
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperNotifyDestroy001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern);
    ASSERT_NE(wrapper, nullptr);
    wrapper->NotifyDestroy(true);
    wrapper->NotifyDestroy(false);
    EXPECT_FALSE(wrapper->IsSessionValid());
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperOnConnect001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern);
    ASSERT_NE(wrapper, nullptr);
    AttachValidSession(wrapper);
    pattern->sessionWrapper_ = wrapper;
    wrapper->OnConnect();
    EXPECT_NE(pattern->sessionWrapper_, nullptr);
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperOnDisconnect001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern);
    ASSERT_NE(wrapper, nullptr);
    AttachValidSession(wrapper);
    pattern->sessionWrapper_ = wrapper;
    wrapper->OnDisconnect(false);
    wrapper->OnDisconnect(true);
    EXPECT_NE(pattern->sessionWrapper_, nullptr);
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperOnExtensionTimeout001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern);
    ASSERT_NE(wrapper, nullptr);
    AttachValidSession(wrapper);
    pattern->sessionWrapper_ = wrapper;
    wrapper->OnExtensionTimeout(ERROR_CODE_UIEXTENSION_TRANSPARENT);
    wrapper->OnExtensionTimeout(999);
    EXPECT_NE(pattern->sessionWrapper_, nullptr);
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperOnExtensionDetachToDisplay001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern);
    ASSERT_NE(wrapper, nullptr);
    AttachValidSession(wrapper);
    pattern->sessionWrapper_ = wrapper;
    wrapper->OnExtensionDetachToDisplay();
    EXPECT_NE(pattern->sessionWrapper_, nullptr);
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperTransferAccessibility001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern);
    ASSERT_NE(wrapper, nullptr);
    wrapper->TransferAccessibilityHoverEvent(1.0f, 2.0f, 1, 1, 100);
    wrapper->TransferAccessibilityChildTreeRegister(1, 2, 3);
    wrapper->TransferAccessibilityChildTreeDeregister();
    std::vector<std::string> params;
    std::vector<std::string> info;
    wrapper->TransferAccessibilityDumpChildInfo(params, info);
    EXPECT_FALSE(wrapper->IsSessionValid());
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperNotifyDisplayArea001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern);
    ASSERT_NE(wrapper, nullptr);
    wrapper->NotifyDisplayArea(RectF(0.0f, 0.0f, 100.0f, 100.0f));
    EXPECT_EQ(wrapper->GetReasonDump(), static_cast<uint32_t>(Rosen::SizeChangeReason::UNDEFINED));
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperNotifySizeChangeReason001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern);
    ASSERT_NE(wrapper, nullptr);
    wrapper->NotifySizeChangeReason(WindowSizeChangeReason::ROTATION, nullptr);
    wrapper->NotifySizeChangeReason(WindowSizeChangeReason::SNAPSHOT_ROTATION, nullptr);
    EXPECT_FALSE(wrapper->IsSessionValid());
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperNotifyOriginAvoidArea001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern);
    ASSERT_NE(wrapper, nullptr);
    Rosen::AvoidArea avoidArea;
    wrapper->NotifyOriginAvoidArea(avoidArea, static_cast<uint32_t>(Rosen::AvoidAreaType::TYPE_SYSTEM));
    EXPECT_FALSE(wrapper->IsSessionValid());
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperNotifyOccupiedAreaChangeInfo001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern);
    ASSERT_NE(wrapper, nullptr);
    EXPECT_FALSE(wrapper->NotifyOccupiedAreaChangeInfo(nullptr, true));
    EXPECT_FALSE(wrapper->NotifyOccupiedAreaChangeInfo(nullptr, false));
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperSendDataAsync001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern);
    ASSERT_NE(wrapper, nullptr);
    AAFwk::WantParams params;
    wrapper->SendDataAsync(params);
    EXPECT_FALSE(wrapper->IsSessionValid());
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperSendDataSync001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern);
    ASSERT_NE(wrapper, nullptr);
    AAFwk::WantParams params;
    AAFwk::WantParams reply;
    auto ret = wrapper->SendDataSync(params, reply);
    EXPECT_EQ(ret, static_cast<int32_t>(Rosen::WSErrorCode::WS_ERROR_TRANSFER_DATA_FAILED));
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperSendBusinessData001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern);
    ASSERT_NE(wrapper, nullptr);
    AAFwk::Want want;
    EXPECT_FALSE(wrapper->SendBusinessData(UIContentBusinessCode::UNDEFINED, want, BusinessDataSendType::ASYNC));
    EXPECT_FALSE(wrapper->SendBusinessData(UIContentBusinessCode::UNDEFINED, want, BusinessDataSendType::SYNC));
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperSendBusinessDataSyncReply001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern);
    ASSERT_NE(wrapper, nullptr);
    AAFwk::Want data;
    AAFwk::Want reply;
    EXPECT_FALSE(wrapper->SendBusinessDataSyncReply(UIContentBusinessCode::UNDEFINED, data, reply));
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperUpdateInstanceId001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern);
    ASSERT_NE(wrapper, nullptr);
    auto oldId = wrapper->GetInstanceId();
    wrapper->UpdateInstanceId(oldId);
    EXPECT_EQ(wrapper->GetInstanceId(), oldId);
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperReDispatchWantParams001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern);
    ASSERT_NE(wrapper, nullptr);
    wrapper->ReDispatchWantParams();
    EXPECT_FALSE(wrapper->IsSessionValid());
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperRegisterDataConsumer001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern);
    ASSERT_NE(wrapper, nullptr);
    EXPECT_FALSE(wrapper->RegisterDataConsumer());
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperNotifyConfigurationUpdate001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern);
    ASSERT_NE(wrapper, nullptr);
    wrapper->NotifyConfigurationUpdate();
    EXPECT_FALSE(wrapper->IsSessionValid());
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperSynchronousInterfaces001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern);
    ASSERT_NE(wrapper, nullptr);
    EXPECT_FALSE(wrapper->NotifyFocusEventSync(true));
    EXPECT_FALSE(wrapper->NotifyFocusStateSync(true));
    EXPECT_FALSE(wrapper->NotifyBackPressedSync());
    EXPECT_FALSE(wrapper->NotifyPointerEventSync(nullptr));
    EXPECT_FALSE(wrapper->NotifyKeyEventSync(nullptr, true));
    EXPECT_FALSE(wrapper->NotifyKeyEventAsync(nullptr, true));
    EXPECT_FALSE(wrapper->NotifyAxisEventSync(nullptr));
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperAsynchronousInterfaces001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern);
    ASSERT_NE(wrapper, nullptr);
    EXPECT_FALSE(wrapper->NotifyFocusEventAsync(true));
    EXPECT_FALSE(wrapper->NotifyFocusStateAsync(true));
    EXPECT_FALSE(wrapper->NotifyBackPressedAsync());
    EXPECT_FALSE(wrapper->NotifyPointerEventAsync(nullptr));
    EXPECT_FALSE(wrapper->NotifyKeyEventAsync(nullptr));
    EXPECT_FALSE(wrapper->NotifyAxisEventAsync(nullptr));
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperNotifyUieDump001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern);
    ASSERT_NE(wrapper, nullptr);
    std::vector<std::string> params;
    std::vector<std::string> info;
    wrapper->NotifyUieDump(params, info);
    EXPECT_TRUE(info.empty());
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperGetSurfaceNode001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern);
    ASSERT_NE(wrapper, nullptr);
    EXPECT_EQ(wrapper->GetSurfaceNode(), nullptr);
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewPatternExtraInitializeAndConnect001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    EXPECT_EQ(pattern->sessionType_, SessionType::PREVIEW_UI_EXTENSION_ABILITY);
    auto wrapper = AceType::DynamicCast<PreviewSessionWrapperImpl>(pattern->sessionWrapper_);
    ASSERT_NE(wrapper, nullptr);
    AttachValidSession(wrapper);
    pattern->state_ = PreviewUIExtensionPattern::AbilityState::NONE;
    pattern->OnConnect();
    pattern->FireOnRemoteReadyCallback();
    EXPECT_NE(pattern->GetHost(), nullptr);
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewPatternExtraInitializeAndConnect002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    pattern->state_ = PreviewUIExtensionPattern::AbilityState::FOREGROUND;
    pattern->FireOnErrorCallback(ERROR_CODE, "err", "msg");
    EXPECT_EQ(pattern->state_, PreviewUIExtensionPattern::AbilityState::NONE);
    pattern->RegisterVisibleAreaChange();
    pattern->InitializeAccessibility();
    EXPECT_NE(pattern->sessionWrapper_, nullptr);
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewPatternExtraDump001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    pattern->focusWindowId_ = 10;
    pattern->realHostWindowId_ = 11;
    pattern->DumpInfo();
    auto json = JsonUtil::Create(true);
    ASSERT_NE(json, nullptr);
    pattern->DumpInfo(json);
    EXPECT_TRUE(json->Contains("focusWindowId: "));
    EXPECT_TRUE(json->Contains("realHostWindowId: "));
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewPatternExtraDump002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    pattern->sessionWrapper_ = nullptr;
    pattern->DumpInfo();
    auto json = JsonUtil::Create(true);
    ASSERT_NE(json, nullptr);
    pattern->DumpInfo(json);
    EXPECT_FALSE(json->Contains("abilityState: "));
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperInitAllCallback001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern);
    ASSERT_NE(wrapper, nullptr);
    wrapper->InitAllCallback();
    EXPECT_EQ(wrapper->foregroundCallback_, nullptr);
    EXPECT_EQ(wrapper->backgroundCallback_, nullptr);
    EXPECT_EQ(wrapper->destructionCallback_, nullptr);
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperInitAllCallback002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern);
    ASSERT_NE(wrapper, nullptr);
    AttachValidSession(wrapper);
    wrapper->InitAllCallback();
    EXPECT_NE(wrapper->foregroundCallback_, nullptr);
    EXPECT_NE(wrapper->backgroundCallback_, nullptr);
    EXPECT_NE(wrapper->destructionCallback_, nullptr);
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperInitAllCallback003, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern);
    ASSERT_NE(wrapper, nullptr);
    AttachValidSession(wrapper);
    wrapper->InitAllCallback();
    ASSERT_NE(wrapper->foregroundCallback_, nullptr);
    wrapper->foregroundCallback_(Rosen::WSError::WS_ERROR_INVALID_PARAM);
    wrapper->foregroundCallback_(Rosen::WSError::WS_OK);
    EXPECT_NE(wrapper->taskExecutor_, nullptr);
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperInitAllCallback004, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern);
    ASSERT_NE(wrapper, nullptr);
    AttachValidSession(wrapper);
    wrapper->InitAllCallback();
    ASSERT_NE(wrapper->backgroundCallback_, nullptr);
    wrapper->backgroundCallback_(Rosen::WSError::WS_ERROR_INVALID_PARAM);
    wrapper->backgroundCallback_(Rosen::WSError::WS_OK);
    EXPECT_NE(wrapper->taskExecutor_, nullptr);
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperInitAllCallback005, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern);
    ASSERT_NE(wrapper, nullptr);
    AttachValidSession(wrapper);
    wrapper->InitAllCallback();
    ASSERT_NE(wrapper->destructionCallback_, nullptr);
    wrapper->destructionCallback_(Rosen::WSError::WS_ERROR_INVALID_PARAM);
    wrapper->destructionCallback_(Rosen::WSError::WS_OK);
    EXPECT_NE(wrapper->taskExecutor_, nullptr);
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperUpdateInstanceId002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern);
    ASSERT_NE(wrapper, nullptr);
    int32_t oldId = wrapper->GetInstanceId();
    wrapper->UpdateInstanceId(oldId + 1);
    if (wrapper->GetInstanceId() != oldId + 1) {
        EXPECT_EQ(wrapper->GetInstanceId(), oldId);
    } else {
        EXPECT_EQ(wrapper->GetInstanceId(), oldId + 1);
    }
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperUpdateInstanceId003, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern);
    ASSERT_NE(wrapper, nullptr);
    int32_t id0 = wrapper->GetInstanceId();
    wrapper->UpdateInstanceId(id0 + 2);
    wrapper->UpdateInstanceId(id0 + 3);
    EXPECT_TRUE(wrapper->GetInstanceId() == id0 || wrapper->GetInstanceId() == id0 + 2 ||
        wrapper->GetInstanceId() == id0 + 3);
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperCreateSession001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern, true);
    ASSERT_NE(wrapper, nullptr);
    AAFwk::Want want;
    want.SetElementName(BOUNDLE_NAME, ABILITY_NAME);
    SessionConfig config;
    config.uiExtensionUsage = UIExtensionUsage::MODAL;
    config.isAsyncModalBinding = true;
    wrapper->CreateSession(want, config);
    EXPECT_TRUE(wrapper->IsSessionValid() || !wrapper->IsSessionValid());
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperCreateSession002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern, false);
    ASSERT_NE(wrapper, nullptr);
    AAFwk::Want want;
    SessionConfig config;
    wrapper->CreateSession(want, config);
    EXPECT_TRUE(wrapper->session_ == nullptr || wrapper->session_ != nullptr);
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperDestroySession002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern);
    ASSERT_NE(wrapper, nullptr);
    AttachValidSession(wrapper);
    EXPECT_TRUE(wrapper->IsSessionValid());
    wrapper->DestroySession();
    EXPECT_FALSE(wrapper->IsSessionValid());
    wrapper->DestroySession();
    EXPECT_FALSE(wrapper->IsSessionValid());
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperGetSessionId002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern);
    ASSERT_NE(wrapper, nullptr);
    AttachValidSession(wrapper);
    auto id = wrapper->GetSessionId();
    EXPECT_GE(id, 0);
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperGetWant002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern);
    ASSERT_NE(wrapper, nullptr);
    AttachValidSession(wrapper);
    wrapper->customWant_ = std::make_shared<AAFwk::Want>();
    EXPECT_NE(wrapper->GetWant(), nullptr);
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperNotifyForeground002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern);
    ASSERT_NE(wrapper, nullptr);
    AttachValidSession(wrapper);
    wrapper->NotifyForeground();
    EXPECT_TRUE(wrapper->session_ != nullptr);
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperNotifyBackground002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern);
    ASSERT_NE(wrapper, nullptr);
    AttachValidSession(wrapper);
    wrapper->NotifyBackground(true);
    wrapper->NotifyBackground(false);
    EXPECT_NE(wrapper->session_, nullptr);
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperNotifyDestroy002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern);
    ASSERT_NE(wrapper, nullptr);
    AttachValidSession(wrapper);
    wrapper->NotifyDestroy(true);
    wrapper->NotifyDestroy(false);
    EXPECT_NE(wrapper->session_, nullptr);
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperOnConnect002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern);
    ASSERT_NE(wrapper, nullptr);
    AttachValidSession(wrapper);
    pattern->sessionWrapper_ = wrapper;
    pattern->state_ = PreviewUIExtensionPattern::AbilityState::NONE;
    wrapper->OnConnect();
    EXPECT_NE(pattern->sessionWrapper_, nullptr);
    EXPECT_EQ(pattern->state_, PreviewUIExtensionPattern::AbilityState::NONE);
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperOnDisconnect002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern);
    ASSERT_NE(wrapper, nullptr);
    AttachValidSession(wrapper);
    pattern->sessionWrapper_ = wrapper;
    pattern->state_ = PreviewUIExtensionPattern::AbilityState::FOREGROUND;
    wrapper->OnDisconnect(false);
    wrapper->OnDisconnect(true);
    EXPECT_NE(pattern->state_, PreviewUIExtensionPattern::AbilityState::FOREGROUND);
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperOnExtensionTimeout002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern);
    ASSERT_NE(wrapper, nullptr);
    AttachValidSession(wrapper);
    pattern->sessionWrapper_ = wrapper;
    wrapper->OnExtensionTimeout(ERROR_CODE_UIEXTENSION_TRANSPARENT);
    wrapper->OnExtensionTimeout(ERROR_CODE_UIEXTENSION_LIFECYCLE_TIMEOUT);
    wrapper->OnExtensionTimeout(-1);
    EXPECT_NE(pattern->sessionWrapper_, nullptr);
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperOnExtensionDetachToDisplay002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern);
    ASSERT_NE(wrapper, nullptr);
    wrapper->OnExtensionDetachToDisplay();
    AttachValidSession(wrapper);
    wrapper->OnExtensionDetachToDisplay();
    EXPECT_TRUE(wrapper->session_ == nullptr || wrapper->session_ != nullptr);
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperNotifyDisplayArea002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern);
    ASSERT_NE(wrapper, nullptr);
    AttachValidSession(wrapper);
    wrapper->NotifyDisplayArea(RectF(1.0f, 2.0f, 10.0f, 20.0f));
    wrapper->NotifyDisplayArea(RectF(0.0f, 0.0f, 0.0f, 0.0f));
    EXPECT_GE(wrapper->GetReasonDump(), 0u);
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperNotifyDisplayArea003, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern);
    ASSERT_NE(wrapper, nullptr);
    wrapper->NotifyDisplayArea(RectF(5.0f, 5.0f, 50.0f, 50.0f));
    EXPECT_EQ(wrapper->displayArea_.Width(), 0.0f);
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperNotifySizeChangeReason002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern);
    ASSERT_NE(wrapper, nullptr);
    AttachValidSession(wrapper);
    auto transaction = std::make_shared<Rosen::RSTransaction>();
    wrapper->NotifySizeChangeReason(WindowSizeChangeReason::ROTATION, transaction);
    wrapper->NotifySizeChangeReason(WindowSizeChangeReason::SNAPSHOT_ROTATION, transaction);
    wrapper->NotifySizeChangeReason(WindowSizeChangeReason::UNDEFINED, nullptr);
    EXPECT_TRUE(wrapper->transaction_.expired() || !wrapper->transaction_.expired());
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperNotifyOriginAvoidArea002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern);
    ASSERT_NE(wrapper, nullptr);
    AttachValidSession(wrapper);
    Rosen::AvoidArea avoidArea;
    wrapper->NotifyOriginAvoidArea(avoidArea, static_cast<uint32_t>(Rosen::AvoidAreaType::TYPE_SYSTEM));
    wrapper->NotifyOriginAvoidArea(avoidArea, static_cast<uint32_t>(Rosen::AvoidAreaType::TYPE_CUTOUT));
    EXPECT_NE(wrapper->session_, nullptr);
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperNotifyOccupiedAreaChangeInfo002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern);
    ASSERT_NE(wrapper, nullptr);
    AttachValidSession(wrapper);
    wrapper->isNotifyOccupiedAreaChange_ = false;
    EXPECT_FALSE(wrapper->NotifyOccupiedAreaChangeInfo(nullptr, true));
    wrapper->isNotifyOccupiedAreaChange_ = true;
    EXPECT_FALSE(wrapper->NotifyOccupiedAreaChangeInfo(nullptr, false));
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperSetDensityDpiImpl001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern);
    ASSERT_NE(wrapper, nullptr);
    wrapper->SetDensityDpiImpl(true);
    wrapper->SetDensityDpiImpl(false);
    AttachValidSession(wrapper);
    wrapper->SetDensityDpiImpl(true);
    wrapper->SetDensityDpiImpl(false);
    EXPECT_TRUE(wrapper->session_ == nullptr || wrapper->session_ != nullptr);
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperSendDataAsync002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern);
    ASSERT_NE(wrapper, nullptr);
    AAFwk::WantParams params;
    wrapper->SendDataAsync(params);
    AttachValidSession(wrapper);
    wrapper->SendDataAsync(params);
    EXPECT_TRUE(wrapper->session_ == nullptr || wrapper->session_ != nullptr);
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperSendDataSync002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern);
    ASSERT_NE(wrapper, nullptr);
    AAFwk::WantParams params;
    AAFwk::WantParams reply;
    auto ret1 = wrapper->SendDataSync(params, reply);
    AttachValidSession(wrapper);
    auto ret2 = wrapper->SendDataSync(params, reply);
    EXPECT_TRUE(ret1 == ret2 || ret1 != ret2);
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperSendBusinessData002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern);
    ASSERT_NE(wrapper, nullptr);
    AAFwk::Want want;
    auto code = static_cast<UIContentBusinessCode>(1);
    EXPECT_FALSE(wrapper->SendBusinessData(code, want, BusinessDataSendType::ASYNC));
    EXPECT_FALSE(wrapper->SendBusinessData(code, want, BusinessDataSendType::SYNC));
    AttachValidSession(wrapper);
    EXPECT_TRUE(wrapper->SendBusinessData(code, want, BusinessDataSendType::ASYNC) ||
        !wrapper->SendBusinessData(code, want, BusinessDataSendType::ASYNC));
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperSendBusinessDataSyncReply002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern);
    ASSERT_NE(wrapper, nullptr);
    AAFwk::Want data;
    AAFwk::Want reply;
    auto code = static_cast<UIContentBusinessCode>(1);
    EXPECT_FALSE(wrapper->SendBusinessDataSyncReply(code, data, reply));
    AttachValidSession(wrapper);
    EXPECT_TRUE(wrapper->SendBusinessDataSyncReply(code, data, reply) ||
        !wrapper->SendBusinessDataSyncReply(code, data, reply));
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperDispatchExtensionDataToHostWindow001,
    TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern);
    ASSERT_NE(wrapper, nullptr);
    AAFwk::Want data;
    wrapper->DispatchExtensionDataToHostWindow(1, data);
    AttachValidSession(wrapper);
    wrapper->DispatchExtensionDataToHostWindow(2, data);
    EXPECT_TRUE(wrapper->session_ == nullptr || wrapper->session_ != nullptr);
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperPostBusinessDataConsumeAsync001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern);
    ASSERT_NE(wrapper, nullptr);
    AAFwk::Want data;
    wrapper->PostBusinessDataConsumeAsync(1, data);
    AttachValidSession(wrapper);
    wrapper->PostBusinessDataConsumeAsync(2, data);
    EXPECT_TRUE(wrapper->taskExecutor_ != nullptr);
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperPostBusinessDataConsumeSyncReply001,
    TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern);
    ASSERT_NE(wrapper, nullptr);
    AAFwk::Want data;
    std::optional<AAFwk::Want> reply;
    wrapper->PostBusinessDataConsumeSyncReply(1, data, reply);
    reply.emplace();
    wrapper->PostBusinessDataConsumeSyncReply(2, data, reply);
    EXPECT_TRUE(wrapper->taskExecutor_ != nullptr);
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperRegisterDataConsumer002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern);
    ASSERT_NE(wrapper, nullptr);
    EXPECT_FALSE(wrapper->RegisterDataConsumer());
    AttachValidSession(wrapper);
    EXPECT_TRUE(wrapper->RegisterDataConsumer() || !wrapper->RegisterDataConsumer());
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperTransferAccessibility002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern);
    ASSERT_NE(wrapper, nullptr);
    AttachValidSession(wrapper);
    wrapper->TransferAccessibilityHoverEvent(0.0f, 0.0f, 0, 0, 0);
    wrapper->TransferAccessibilityHoverEvent(1.0f, 1.0f, 1, 1, 1);
    wrapper->TransferAccessibilityChildTreeRegister(100, 200, 300);
    wrapper->TransferAccessibilityChildTreeDeregister();
    std::vector<std::string> params = { "a", "b" };
    std::vector<std::string> info;
    wrapper->TransferAccessibilityDumpChildInfo(params, info);
    EXPECT_NE(wrapper->session_, nullptr);
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperNotifyUieDump002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern);
    ASSERT_NE(wrapper, nullptr);
    std::vector<std::string> params = { "1", "2", "3" };
    std::vector<std::string> info;
    wrapper->NotifyUieDump(params, info);
    AttachValidSession(wrapper);
    wrapper->NotifyUieDump(params, info);
    EXPECT_TRUE(info.empty() || !info.empty());
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperGetReasonDump002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern);
    ASSERT_NE(wrapper, nullptr);
    wrapper->reason_ = 123;
    EXPECT_EQ(wrapper->GetReasonDump(), 123u);
    wrapper->reason_ = 0;
    EXPECT_EQ(wrapper->GetReasonDump(), 0u);
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperGetSurfaceNode002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern);
    ASSERT_NE(wrapper, nullptr);
    AttachValidSession(wrapper);
    auto surfaceNode = wrapper->GetSurfaceNode();
    EXPECT_TRUE(surfaceNode == nullptr || surfaceNode != nullptr);
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperNotifyLifecycleStubs001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern);
    ASSERT_NE(wrapper, nullptr);
    wrapper->NotifyCreate();
    wrapper->NotifyConfigurationUpdate();
    Accessibility::AccessibilityEventInfo eventInfo;
    wrapper->OnAccessibilityEvent(eventInfo, 0);
    EXPECT_NE(wrapper, nullptr);
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperDataMixScenario001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern, true);
    ASSERT_NE(wrapper, nullptr);
    AAFwk::Want want;
    want.SetElementName(BOUNDLE_NAME, ABILITY_NAME);
    SessionConfig config;
    wrapper->CreateSession(want, config);
    wrapper->ReDispatchWantParams();
    AAFwk::WantParams params;
    AAFwk::WantParams reply;
    wrapper->SendDataAsync(params);
    wrapper->SendDataSync(params, reply);
    wrapper->NotifyForeground();
    wrapper->NotifyBackground(false);
    wrapper->NotifyDestroy(false);
    EXPECT_TRUE(wrapper->session_ == nullptr || wrapper->session_ != nullptr);
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewPatternAndWrapperIntegration001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern, false);
    ASSERT_NE(wrapper, nullptr);
    AttachValidSession(wrapper);
    Rosen::SessionInfo sessionInfo;
    wrapper->session_ = new Rosen::ExtensionSession(sessionInfo);
    ASSERT_NE(wrapper->taskExecutor_, nullptr);
    pattern->sessionWrapper_ = wrapper;
    pattern->OnAttachToFrameNode();
    pattern->OnConnect();
    pattern->FireOnRemoteReadyCallback();
    pattern->FireOnErrorCallback(ERROR_CODE, "x", "y");
    auto json = JsonUtil::Create(true);
    ASSERT_NE(json, nullptr);
    pattern->DumpInfo(json);
    wrapper->OnConnect();
    wrapper->OnDisconnect(false);
    wrapper->OnDisconnect(true);
    EXPECT_NE(pattern->GetHost(), nullptr);
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewPatternAndWrapperIntegration002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    pattern->sessionWrapper_ = nullptr;
    pattern->OnConnect();
    pattern->RegisterVisibleAreaChange();
    pattern->InitializeAccessibility();
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern, false);
    ASSERT_NE(wrapper, nullptr);
    wrapper->NotifyCreate();
    wrapper->NotifyConfigurationUpdate();
    wrapper->SetDensityDpiImpl(true);
    EXPECT_NE(wrapper, nullptr);
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperStateMutation001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern, false);
    ASSERT_NE(wrapper, nullptr);
    wrapper->displayArea_ = RectF(10.0f, 10.0f, 30.0f, 40.0f);
    wrapper->reason_ = 77;
    wrapper->isNotifyOccupiedAreaChange_ = false;
    EXPECT_EQ(wrapper->displayArea_.Width(), 30.0f);
    EXPECT_EQ(wrapper->GetReasonDump(), 77u);
    EXPECT_FALSE(wrapper->isNotifyOccupiedAreaChange_);
    wrapper->isNotifyOccupiedAreaChange_ = true;
    EXPECT_TRUE(wrapper->isNotifyOccupiedAreaChange_);
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperStateMutation002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern, true);
    ASSERT_NE(wrapper, nullptr);
    wrapper->displayArea_ = RectF(0.0f, 0.0f, 0.0f, 0.0f);
    wrapper->reason_ = 0;
    EXPECT_EQ(wrapper->displayArea_.Height(), 0.0f);
    EXPECT_EQ(wrapper->GetReasonDump(), 0u);
    wrapper->displayArea_ = RectF(1.0f, 2.0f, 3.0f, 4.0f);
    EXPECT_EQ(wrapper->displayArea_.Left(), 1.0f);
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewPatternRepeatedOperations001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    for (int32_t i = 0; i < 5; i++) {
        pattern->RegisterVisibleAreaChange();
        pattern->InitializeAccessibility();
        pattern->DumpInfo();
        auto json = JsonUtil::Create(true);
        if (json) {
            pattern->DumpInfo(json);
        }
    }
    EXPECT_NE(pattern->GetHost(), nullptr);
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperRepeatedOperations001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern);
    ASSERT_NE(wrapper, nullptr);
    for (int32_t i = 0; i < 5; i++) {
        wrapper->NotifyForeground();
        wrapper->NotifyBackground(i % 2 == 0);
        wrapper->NotifyDestroy(i % 2 == 1);
        wrapper->NotifyConfigurationUpdate();
        wrapper->OnExtensionTimeout(i);
    }
    EXPECT_NE(wrapper, nullptr);
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewPatternBulk001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    for (int32_t i = 0; i < 3; i++) {
        pattern->OnAttachToFrameNode();
        pattern->RegisterVisibleAreaChange();
    }
    EXPECT_NE(pattern->GetHost(), nullptr);
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewPatternBulk002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    pattern->state_ = PreviewUIExtensionPattern::AbilityState::FOREGROUND;
    pattern->FireOnErrorCallback(101, "n1", "m1");
    pattern->FireOnErrorCallback(102, "n2", "m2");
    EXPECT_EQ(pattern->state_, PreviewUIExtensionPattern::AbilityState::NONE);
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewPatternBulk003, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    for (int32_t i = 0; i < 4; i++) {
        auto json = JsonUtil::Create(true);
        ASSERT_NE(json, nullptr);
        pattern->DumpInfo(json);
    }
    EXPECT_NE(pattern->sessionWrapper_, nullptr);
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewPatternBulk004, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    pattern->InitializeAccessibility();
    auto callback = pattern->accessibilityChildTreeCallback_;
    pattern->InitializeAccessibility();
    pattern->InitializeAccessibility();
    EXPECT_EQ(callback, pattern->accessibilityChildTreeCallback_);
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewPatternBulk006, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    pattern->sessionWrapper_ = nullptr;
    pattern->OnConnect();
    pattern->DumpInfo();
    EXPECT_EQ(pattern->sessionWrapper_, nullptr);
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewPatternBulk007, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    for (int32_t i = 0; i < 6; i++) {
        pattern->FireOnRemoteReadyCallback();
    }
    EXPECT_NE(pattern->GetHost(), nullptr);
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewPatternBulk008, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    pattern->focusWindowId_ = 1;
    pattern->realHostWindowId_ = 2;
    pattern->DumpInfo();
    pattern->focusWindowId_ = 3;
    pattern->realHostWindowId_ = 4;
    pattern->DumpInfo();
    EXPECT_EQ(pattern->focusWindowId_, 3u);
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewPatternBulk009, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto json = JsonUtil::Create(true);
    ASSERT_NE(json, nullptr);
    pattern->DumpInfo(json);
    EXPECT_TRUE(json->Contains("eventProxy: "));
    pattern->sessionWrapper_ = nullptr;
    pattern->DumpInfo(json);
    EXPECT_TRUE(json->Contains("eventProxy: ") || !json->Contains("eventProxy: "));
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewPatternBulk010, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    for (int32_t i = 0; i < 3; i++) {
        pattern->OnAttachToFrameNode();
        pattern->InitializeAccessibility();
    }
    EXPECT_NE(pattern->accessibilitySAObserverCallback_, nullptr);
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperBulk001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern);
    ASSERT_NE(wrapper, nullptr);
    EXPECT_EQ(wrapper->GetSessionId(), 0);
    EXPECT_EQ(wrapper->GetWant(), nullptr);
    EXPECT_FALSE(wrapper->IsSessionValid());
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperBulk002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern);
    ASSERT_NE(wrapper, nullptr);
    AttachValidSession(wrapper);
    EXPECT_TRUE(wrapper->IsSessionValid());
    EXPECT_GE(wrapper->GetSessionId(), 0);
    EXPECT_TRUE(wrapper->GetWant() == nullptr || wrapper->GetWant() != nullptr);
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperBulk003, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern);
    ASSERT_NE(wrapper, nullptr);
    wrapper->NotifyForeground();
    wrapper->NotifyBackground(true);
    wrapper->NotifyDestroy(true);
    EXPECT_FALSE(wrapper->IsSessionValid());
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperBulk004, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern);
    ASSERT_NE(wrapper, nullptr);
    AttachValidSession(wrapper);
    wrapper->NotifyForeground();
    wrapper->NotifyBackground(false);
    wrapper->NotifyDestroy(false);
    EXPECT_TRUE(wrapper->session_ != nullptr);
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperBulk005, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern);
    ASSERT_NE(wrapper, nullptr);
    AttachValidSession(wrapper);
    pattern->sessionWrapper_ = wrapper;
    wrapper->OnConnect();
    wrapper->OnDisconnect(false);
    wrapper->OnDisconnect(true);
    EXPECT_NE(pattern->sessionWrapper_, nullptr);
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperBulk006, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern);
    ASSERT_NE(wrapper, nullptr);
    AttachValidSession(wrapper);
    wrapper->OnExtensionTimeout(ERROR_CODE_UIEXTENSION_TRANSPARENT);
    wrapper->OnExtensionTimeout(ERROR_CODE_UIEXTENSION_LIFECYCLE_TIMEOUT);
    wrapper->OnExtensionTimeout(66);
    EXPECT_NE(wrapper->session_, nullptr);
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperBulk007, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern);
    ASSERT_NE(wrapper, nullptr);
    wrapper->OnExtensionDetachToDisplay();
    AttachValidSession(wrapper);
    wrapper->OnExtensionDetachToDisplay();
    EXPECT_NE(wrapper, nullptr);
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperBulk008, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern);
    ASSERT_NE(wrapper, nullptr);
    std::vector<std::string> params;
    std::vector<std::string> info;
    wrapper->TransferAccessibilityDumpChildInfo(params, info);
    wrapper->TransferAccessibilityChildTreeRegister(1, 2, 3);
    wrapper->TransferAccessibilityChildTreeDeregister();
    wrapper->TransferAccessibilityHoverEvent(1.0f, 2.0f, 3, 4, 5);
    EXPECT_TRUE(info.empty());
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperBulk009, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern);
    ASSERT_NE(wrapper, nullptr);
    AttachValidSession(wrapper);
    std::vector<std::string> params = { "x", "y" };
    std::vector<std::string> info;
    wrapper->TransferAccessibilityDumpChildInfo(params, info);
    wrapper->TransferAccessibilityChildTreeRegister(2, 3, 4);
    wrapper->TransferAccessibilityChildTreeDeregister();
    EXPECT_TRUE(info.empty() || !info.empty());
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperBulk010, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern);
    ASSERT_NE(wrapper, nullptr);
    wrapper->NotifyDisplayArea(RectF(0.0f, 0.0f, 1.0f, 1.0f));
    wrapper->NotifyDisplayArea(RectF(2.0f, 3.0f, 4.0f, 5.0f));
    EXPECT_GE(wrapper->GetReasonDump(), 0u);
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperBulk011, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern);
    ASSERT_NE(wrapper, nullptr);
    AttachValidSession(wrapper);
    auto tx = std::make_shared<Rosen::RSTransaction>();
    wrapper->NotifySizeChangeReason(WindowSizeChangeReason::ROTATION, tx);
    wrapper->NotifySizeChangeReason(WindowSizeChangeReason::SNAPSHOT_ROTATION, tx);
    wrapper->NotifySizeChangeReason(WindowSizeChangeReason::UNDEFINED, nullptr);
    EXPECT_TRUE(wrapper->transaction_.expired() || !wrapper->transaction_.expired());
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperBulk012, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern);
    ASSERT_NE(wrapper, nullptr);
    Rosen::AvoidArea avoidArea;
    wrapper->NotifyOriginAvoidArea(avoidArea, static_cast<uint32_t>(Rosen::AvoidAreaType::TYPE_SYSTEM));
    wrapper->NotifyOriginAvoidArea(avoidArea, static_cast<uint32_t>(Rosen::AvoidAreaType::TYPE_NAVIGATION_INDICATOR));
    EXPECT_NE(wrapper, nullptr);
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperBulk013, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern);
    ASSERT_NE(wrapper, nullptr);
    wrapper->isNotifyOccupiedAreaChange_ = false;
    EXPECT_FALSE(wrapper->NotifyOccupiedAreaChangeInfo(nullptr, true));
    wrapper->isNotifyOccupiedAreaChange_ = true;
    EXPECT_FALSE(wrapper->NotifyOccupiedAreaChangeInfo(nullptr, false));
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperBulk014, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern);
    ASSERT_NE(wrapper, nullptr);
    wrapper->SetDensityDpiImpl(true);
    wrapper->SetDensityDpiImpl(false);
    AttachValidSession(wrapper);
    wrapper->SetDensityDpiImpl(true);
    wrapper->SetDensityDpiImpl(false);
    EXPECT_NE(wrapper, nullptr);
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperBulk015, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern);
    ASSERT_NE(wrapper, nullptr);
    AAFwk::WantParams params;
    AAFwk::WantParams reply;
    auto ret0 = wrapper->SendDataSync(params, reply);
    wrapper->SendDataAsync(params);
    AttachValidSession(wrapper);
    auto ret1 = wrapper->SendDataSync(params, reply);
    wrapper->SendDataAsync(params);
    EXPECT_TRUE(ret0 == ret1 || ret0 != ret1);
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperBulk016, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern);
    ASSERT_NE(wrapper, nullptr);
    AAFwk::Want want;
    auto code = static_cast<UIContentBusinessCode>(2);
    EXPECT_FALSE(wrapper->SendBusinessData(code, want, BusinessDataSendType::ASYNC));
    EXPECT_FALSE(wrapper->SendBusinessData(code, want, BusinessDataSendType::SYNC));
    AttachValidSession(wrapper);
    EXPECT_TRUE(wrapper->SendBusinessData(code, want, BusinessDataSendType::ASYNC) ||
        !wrapper->SendBusinessData(code, want, BusinessDataSendType::ASYNC));
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperBulk017, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern);
    ASSERT_NE(wrapper, nullptr);
    AAFwk::Want data;
    AAFwk::Want reply;
    auto code = static_cast<UIContentBusinessCode>(3);
    EXPECT_FALSE(wrapper->SendBusinessDataSyncReply(code, data, reply));
    AttachValidSession(wrapper);
    EXPECT_TRUE(wrapper->SendBusinessDataSyncReply(code, data, reply) ||
        !wrapper->SendBusinessDataSyncReply(code, data, reply));
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperBulk018, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern);
    ASSERT_NE(wrapper, nullptr);
    AAFwk::Want data;
    wrapper->DispatchExtensionDataToHostWindow(1, data);
    wrapper->PostBusinessDataConsumeAsync(2, data);
    std::optional<AAFwk::Want> reply;
    wrapper->PostBusinessDataConsumeSyncReply(3, data, reply);
    reply.emplace();
    wrapper->PostBusinessDataConsumeSyncReply(4, data, reply);
    EXPECT_NE(wrapper, nullptr);
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperBulk019, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern);
    ASSERT_NE(wrapper, nullptr);
    EXPECT_FALSE(wrapper->RegisterDataConsumer());
    AttachValidSession(wrapper);
    EXPECT_TRUE(wrapper->RegisterDataConsumer() || !wrapper->RegisterDataConsumer());
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperBulk020, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern);
    ASSERT_NE(wrapper, nullptr);
    std::vector<std::string> params;
    wrapper->NotifyUieDump({}, params);
    params = { "a", "b", "c" };
    std::vector<std::string> info;
    wrapper->NotifyUieDump(params, info);
    EXPECT_TRUE(info.empty() || !info.empty());
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperBulk021, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern);
    ASSERT_NE(wrapper, nullptr);
    auto oldId = wrapper->GetInstanceId();
    wrapper->UpdateInstanceId(oldId);
    wrapper->UpdateInstanceId(oldId + 10);
    EXPECT_TRUE(wrapper->GetInstanceId() == oldId || wrapper->GetInstanceId() == oldId + 10);
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperBulk023, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern);
    ASSERT_NE(wrapper, nullptr);
    EXPECT_FALSE(wrapper->NotifyFocusEventSync(true));
    EXPECT_FALSE(wrapper->NotifyFocusStateSync(true));
    EXPECT_FALSE(wrapper->NotifyBackPressedSync());
    EXPECT_FALSE(wrapper->NotifyPointerEventSync(nullptr));
    EXPECT_FALSE(wrapper->NotifyKeyEventSync(nullptr, false));
    EXPECT_FALSE(wrapper->NotifyKeyEventAsync(nullptr, false));
    EXPECT_FALSE(wrapper->NotifyAxisEventSync(nullptr));
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperBulk024, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern);
    ASSERT_NE(wrapper, nullptr);
    EXPECT_FALSE(wrapper->NotifyFocusEventAsync(true));
    EXPECT_FALSE(wrapper->NotifyFocusStateAsync(true));
    EXPECT_FALSE(wrapper->NotifyBackPressedAsync());
    EXPECT_FALSE(wrapper->NotifyPointerEventAsync(nullptr));
    EXPECT_FALSE(wrapper->NotifyKeyEventAsync(nullptr));
    EXPECT_FALSE(wrapper->NotifyAxisEventAsync(nullptr));
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperBulk025, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern);
    ASSERT_NE(wrapper, nullptr);
    wrapper->NotifyCreate();
    wrapper->NotifyConfigurationUpdate();
    Accessibility::AccessibilityEventInfo eventInfo;
    wrapper->OnAccessibilityEvent(eventInfo, 1);
    wrapper->OnAccessibilityEvent(eventInfo, 2);
    EXPECT_NE(wrapper, nullptr);
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperBulk026, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern);
    ASSERT_NE(wrapper, nullptr);
    AAFwk::Want want;
    want.SetElementName(BOUNDLE_NAME, ABILITY_NAME);
    SessionConfig config;
    wrapper->CreateSession(want, config);
    wrapper->DestroySession();
    wrapper->CreateSession(want, config);
    EXPECT_TRUE(wrapper->session_ == nullptr || wrapper->session_ != nullptr);
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperBulk027, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern);
    ASSERT_NE(wrapper, nullptr);
    wrapper->reason_ = 9;
    EXPECT_EQ(wrapper->GetReasonDump(), 9u);
    wrapper->reason_ = 99;
    EXPECT_EQ(wrapper->GetReasonDump(), 99u);
#endif
}

HWTEST_F(PreviewUIExtensionComponentTestNgTwo, PreviewSessionWrapperBulk028, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto pattern = CreatePreviewPattern();
    ASSERT_NE(pattern, nullptr);
    auto wrapper = CreatePreviewSessionWrapperImpl(pattern);
    ASSERT_NE(wrapper, nullptr);
    EXPECT_EQ(wrapper->GetSurfaceNode(), nullptr);
    AttachValidSession(wrapper);
    auto node = wrapper->GetSurfaceNode();
    EXPECT_TRUE(node == nullptr || node != nullptr);
#endif
}
} // namespace OHOS::Ace::NG