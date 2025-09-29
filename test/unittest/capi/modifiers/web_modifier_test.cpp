/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <gtest/gtest.h>

#include "modifier_test_base.h"
#include "modifiers_test_utils.h"
#include "core/interfaces/native/implementation/console_message_peer_impl.h"
#include "core/interfaces/native/implementation/controller_handler_peer_impl.h"
#include "core/interfaces/native/implementation/client_authentication_handler_peer_impl.h"
#include "core/interfaces/native/implementation/data_resubmission_handler_peer_impl.h"
#include "core/interfaces/native/implementation/file_selector_param_peer_impl.h"
#include "core/interfaces/native/implementation/file_selector_result_peer_impl.h"
#include "core/interfaces/native/implementation/full_screen_exit_handler_peer_impl.h"
#include "core/interfaces/native/implementation/js_geolocation_peer_impl.h"
#include "core/interfaces/native/implementation/js_result_peer_impl.h"
#include "core/interfaces/native/implementation/http_auth_handler_peer_impl.h"
#include "core/interfaces/native/implementation/permission_request_peer_impl.h"
#include "core/interfaces/native/implementation/screen_capture_handler_peer_impl.h"
#include "core/interfaces/native/implementation/ssl_error_handler_peer_impl.h"
#include "core/interfaces/native/implementation/web_context_menu_param_peer_impl.h"
#include "core/interfaces/native/implementation/web_context_menu_result_peer_impl.h"
#include "core/interfaces/native/implementation/web_controller_peer_impl.h"
#include "core/interfaces/native/implementation/web_keyboard_controller_peer_impl.h"
#include "core/interfaces/native/implementation/web_resource_error_peer_impl.h"
#include "core/interfaces/native/implementation/web_resource_request_peer_impl.h"
#include "core/interfaces/native/implementation/web_resource_response_peer_impl.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "test/unittest/capi/stubs/mock_web_entities.h"
#include "test/unittest/capi/stubs/mock_web_pattern.h"
#include "arkoala_api_generated.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::NG::Converter;

namespace OHOS::Ace::NG {

namespace Converter {

template<>
void AssignCast(std::optional<RenderExitReason>& dst, const Ark_RenderExitReason& src)
{
    switch (src) {
        case ARK_RENDER_EXIT_REASON_PROCESS_ABNORMAL_TERMINATION: dst = RenderExitReason::ABNORMAL_TERMINATION; break;
        case ARK_RENDER_EXIT_REASON_PROCESS_WAS_KILLED: dst = RenderExitReason::WAS_KILLED; break;
        case ARK_RENDER_EXIT_REASON_PROCESS_CRASHED: dst = RenderExitReason::CRASHED; break;
        case ARK_RENDER_EXIT_REASON_PROCESS_OOM: dst = RenderExitReason::OOM; break;
        case ARK_RENDER_EXIT_REASON_PROCESS_EXIT_UNKNOWN: dst = RenderExitReason::EXIT_UNKNOWN; break;
        default: LOGE("Unexpected enum value in Ark_RenderExitReason: %{public}d", src);
    }
}

} // namespace Converter

class WebModifierTest : public ModifierTestBase<GENERATED_ArkUIWebModifier,
    &GENERATED_ArkUINodeModifiers::getWebModifier, GENERATED_ARKUI_WEB> {
};

/*
 * @tc.name: setOptionsWebControllerTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
#ifdef WRONG_UNION
HWTEST_F(WebModifierTest, setOptionsWebControllerTestValidValues, TestSize.Level1)
{
    Ark_WebOptions options;
    options.incognitoMode = Converter::ArkValue<Opt_Boolean>(Ark_Empty());
    options.renderMode = Converter::ArkValue<Opt_RenderMode>(Ark_Empty());
    options.sharedRenderProcessToken = Converter::ArkValue<Opt_String>(Ark_Empty());
    options.src = Converter::ArkUnion<Ark_Union_String_Resource, Ark_String>("src");

    Ark_NativePointer controllerPtr =
        fullAPI_->getAccessors()->getWebControllerAccessor()->ctor();
    auto peerImplPtr = reinterpret_cast<GeneratedModifier::WebControllerPeerImpl*>(controllerPtr);
    EXPECT_NE(peerImplPtr, nullptr);

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<WebPattern>();
    EXPECT_NE(pattern, nullptr);

    options.controller =
        Converter::ArkUnion<Ark_Union_WebController_WebviewController, Ark_WebController>(controllerPtr);

    RefPtr<WebController> controller = pattern->GetWebController();
    EXPECT_EQ(controller, nullptr);

    modifier_->setWebOptions(node_, &options);

    controller = pattern->GetWebController();
    EXPECT_NE(controller, nullptr);
    EXPECT_EQ(peerImplPtr->GetController(), controller);

    Ark_NativePointer finalizerPtr =
        fullAPI_->getAccessors()->getWebControllerAccessor()->getFinalizer();
    auto finalyzer = reinterpret_cast<void (*)(WebControllerPeer *)>(finalizerPtr);
    EXPECT_NE(finalyzer, nullptr);
    finalyzer(reinterpret_cast<WebControllerPeer *>(controllerPtr));
}
#endif

/*
 * @tc.name: onPageEndTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, onPageEndTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    std::string url = "url";

    struct CheckEvent {
        int32_t resourceId;
        std::string url;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    static constexpr int32_t contextId = 123;
    auto checkCallback = [](const Ark_Int32 resourceId, const Ark_OnPageEndEvent parameter) {
        checkEvent = CheckEvent{
            .resourceId = resourceId,
            .url = Converter::Convert<std::string>(parameter.url)
        };
    };

    Callback_OnPageEndEvent_Void arkCallback =
        Converter::ArkValue<Callback_OnPageEndEvent_Void>(checkCallback, contextId);

    auto optCallback = Converter::ArkValue<Opt_Callback_OnPageEndEvent_Void>(arkCallback);
    modifier_->setOnPageEnd(node_, &optCallback);

    EXPECT_EQ(checkEvent.has_value(), false);
    webEventHub->FireOnPageFinishedEvent(std::make_shared<LoadWebPageFinishEvent>(url));
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->resourceId, contextId);
    EXPECT_EQ(checkEvent->url, url);
}

/*
 * @tc.name: onPageBeginTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, onPageBeginTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    std::string url = "url";

    struct CheckEvent {
        int32_t resourceId;
        std::string url;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    static constexpr int32_t contextId = 123;
    auto checkCallback = [](const Ark_Int32 resourceId, const Ark_OnPageBeginEvent parameter) {
        checkEvent = CheckEvent{
            .resourceId = resourceId,
            .url = Converter::Convert<std::string>(parameter.url)
        };
    };

    Callback_OnPageBeginEvent_Void arkCallback =
        Converter::ArkValue<Callback_OnPageBeginEvent_Void>(checkCallback, contextId);

    auto optCallback = Converter::ArkValue<Opt_Callback_OnPageBeginEvent_Void>(arkCallback);
    modifier_->setOnPageBegin(node_, &optCallback);

    EXPECT_EQ(checkEvent.has_value(), false);
    webEventHub->FireOnPageStartedEvent(std::make_shared<LoadWebPageStartEvent>(url));
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->resourceId, contextId);
    EXPECT_EQ(checkEvent->url, url);
}

/*
 * @tc.name: onProgressChangeTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, onProgressChangeTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    int32_t newProgress = 99;

    struct CheckEvent {
        int32_t resourceId;
        int32_t progress;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    static constexpr int32_t contextId = 123;
    auto checkCallback = [](const Ark_Int32 resourceId, const Ark_OnProgressChangeEvent parameter) {
        checkEvent = CheckEvent{
            .resourceId = resourceId,
            .progress = Converter::Convert<int32_t>(parameter.newProgress)
        };
    };

    Callback_OnProgressChangeEvent_Void arkCallback =
        Converter::ArkValue<Callback_OnProgressChangeEvent_Void>(checkCallback, contextId);

    auto optCallback = Converter::ArkValue<Opt_Callback_OnProgressChangeEvent_Void>(arkCallback);
    modifier_->setOnProgressChange(node_, &optCallback);

    EXPECT_EQ(checkEvent.has_value(), false);
    webEventHub->FireOnProgressChangeEvent(std::make_shared<LoadWebProgressChangeEvent>(newProgress));
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->resourceId, contextId);
    EXPECT_EQ(checkEvent->progress, newProgress);
}

/*
 * @tc.name: onTitleReceiveTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, onTitleReceiveTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    std::string title = "title";

    struct CheckEvent {
        int32_t resourceId;
        std::string title;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    static constexpr int32_t contextId = 123;
    auto checkCallback = [](const Ark_Int32 resourceId, const Ark_OnTitleReceiveEvent parameter) {
        checkEvent = CheckEvent{
            .resourceId = resourceId,
            .title = Converter::Convert<std::string>(parameter.title)
        };
    };

    Callback_OnTitleReceiveEvent_Void arkCallback =
        Converter::ArkValue<Callback_OnTitleReceiveEvent_Void>(checkCallback, contextId);

    auto optCallback = Converter::ArkValue<Opt_Callback_OnTitleReceiveEvent_Void>(arkCallback);
    modifier_->setOnTitleReceive(node_, &optCallback);

    EXPECT_EQ(checkEvent.has_value(), false);
    webEventHub->FireOnTitleReceiveEvent(std::make_shared<LoadWebTitleReceiveEvent>(title));
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->resourceId, contextId);
    EXPECT_EQ(checkEvent->title, title);
}

/*
 * @tc.name: onGeolocationHideTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, onGeolocationHideTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    std::string origin = "origin";

    struct CheckEvent {
        int32_t resourceId;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    static constexpr int32_t contextId = 123;
    auto checkCallback = [](const Ark_Int32 resourceId) {
        checkEvent = CheckEvent{
            .resourceId = resourceId,
        };
    };

    Callback_Void arkCallback =
        Converter::ArkValue<Callback_Void>(checkCallback, contextId);

    auto optCallback = Converter::ArkValue<Opt_Callback_Void>(arkCallback);
    modifier_->setOnGeolocationHide(node_, &optCallback);

    EXPECT_EQ(checkEvent.has_value(), false);
    webEventHub->FireOnGeolocationHideEvent(std::make_shared<LoadWebGeolocationHideEvent>(origin));
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->resourceId, contextId);
}

/*
 * @tc.name: onGeolocationShowTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, onGeolocationShowTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    std::string origin = "origin";
    RefPtr<WebGeolocation> webGeolocation = Referenced::MakeRefPtr<MockWebGeolocation>();

    struct CheckEvent {
        int32_t resourceId;
        std::string origin;
        JsGeolocationPeer* peer;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    static constexpr int32_t contextId = 123;
    auto checkCallback = [](const Ark_Int32 resourceId, const Ark_OnGeolocationShowEvent parameter) {
        checkEvent = CheckEvent{
            .resourceId = resourceId,
            .origin = Converter::Convert<std::string>(parameter.origin),
            .peer = parameter.geolocation,
        };
    };

    Callback_OnGeolocationShowEvent_Void arkCallback =
        Converter::ArkValue<Callback_OnGeolocationShowEvent_Void>(checkCallback, contextId);

    auto optCallback = Converter::ArkValue<Opt_Callback_OnGeolocationShowEvent_Void>(arkCallback);
    modifier_->setOnGeolocationShow(node_, &optCallback);

    EXPECT_EQ(checkEvent.has_value(), false);
    webEventHub->FireOnGeolocationShowEvent(std::make_shared<LoadWebGeolocationShowEvent>(origin, webGeolocation));
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->resourceId, contextId);
    EXPECT_EQ(checkEvent->origin, origin);
    EXPECT_EQ(checkEvent->peer->webGeolocation, webGeolocation);
    delete checkEvent->peer;
}

/*
 * @tc.name: onRequestSelectedTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, onRequestSelectedTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    std::string type = "onRequestSelected";

    struct CheckEvent {
        int32_t resourceId;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    static constexpr int32_t contextId = 123;
    auto checkCallback = [](const Ark_Int32 resourceId) {
        checkEvent = CheckEvent{
            .resourceId = resourceId,
        };
    };

    Callback_Void arkCallback =
        Converter::ArkValue<Callback_Void>(checkCallback, contextId);

    auto optCallback = Converter::ArkValue<Opt_Callback_Void>(arkCallback);
    modifier_->setOnRequestSelected(node_, &optCallback);

    EXPECT_EQ(checkEvent.has_value(), false);
    webEventHub->FireOnRequestFocusEvent(std::make_shared<BaseEventInfo>(type));
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->resourceId, contextId);
}

/*
 * @tc.name: onAlertTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, onAlertTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    std::string url = "url";
    std::string message = "message";
    std::string value = "value";
    DialogEventType type = DialogEventType::DIALOG_EVENT_ALERT;
    RefPtr<Result> result = Referenced::MakeRefPtr<MockResult>();

    struct CheckEvent {
        int32_t resourceId;
        std::string url;
        std::string message;
        JsResultPeer* peer;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    static constexpr int32_t contextId = 123;
    static auto callResult = false;
    auto checkCallback = [](Ark_VMContext context, const Ark_Int32 resourceId, const Ark_OnAlertEvent parameter,
        const Callback_Boolean_Void continuation) {
        checkEvent = CheckEvent{
            .resourceId = resourceId,
            .url = Converter::Convert<std::string>(parameter.url),
            .message = Converter::Convert<std::string>(parameter.message),
            .peer = parameter.result,
        };
        CallbackHelper(continuation).InvokeSync(Converter::ArkValue<Ark_Boolean>(callResult));
    };

    Callback_OnAlertEvent_Boolean arkCallback =
        Converter::ArkValue<Callback_OnAlertEvent_Boolean>(nullptr, checkCallback, contextId);

    auto optCallback = Converter::ArkValue<Opt_Callback_OnAlertEvent_Boolean>(arkCallback);
    modifier_->setOnAlert(node_, &optCallback);

    EXPECT_FALSE(checkEvent.has_value());
    EXPECT_FALSE(webEventHub->FireOnCommonDialogEvent(
        std::make_shared<WebDialogEvent>(url, message, value, type, result), type));
    EXPECT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->resourceId, contextId);
    EXPECT_EQ(checkEvent->url, url);
    EXPECT_EQ(checkEvent->message, message);
    EXPECT_EQ(checkEvent->peer->result, result);
    delete checkEvent->peer;
    callResult = true;
    EXPECT_TRUE(webEventHub->FireOnCommonDialogEvent(
        std::make_shared<WebDialogEvent>(url, message, value, type, result), type));
    delete checkEvent->peer;
}

/*
 * @tc.name: onBeforeUnloadTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, onBeforeUnloadTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    std::string url = "url";
    std::string message = "message";
    std::string value = "value";
    DialogEventType type = DialogEventType::DIALOG_EVENT_BEFORE_UNLOAD;
    RefPtr<Result> result = Referenced::MakeRefPtr<MockResult>();

    struct CheckEvent {
        int32_t resourceId;
        std::string url;
        std::string message;
        JsResultPeer* peer;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    static constexpr int32_t contextId = 123;
    static auto callResult = false;
    auto checkCallback = [](Ark_VMContext context, const Ark_Int32 resourceId, const Ark_OnBeforeUnloadEvent parameter,
        const Callback_Boolean_Void continuation) {
        checkEvent = CheckEvent{
            .resourceId = resourceId,
            .url = Converter::Convert<std::string>(parameter.url),
            .message = Converter::Convert<std::string>(parameter.message),
            .peer = parameter.result,
        };
        CallbackHelper(continuation).InvokeSync(Converter::ArkValue<Ark_Boolean>(callResult));
    };

    Callback_OnBeforeUnloadEvent_Boolean arkCallback =
        Converter::ArkValue<Callback_OnBeforeUnloadEvent_Boolean>(nullptr, checkCallback, contextId);

    auto optCallback = Converter::ArkValue<Opt_Callback_OnBeforeUnloadEvent_Boolean>(arkCallback);
    modifier_->setOnBeforeUnload(node_, &optCallback);

    EXPECT_FALSE(checkEvent.has_value());
    EXPECT_FALSE(webEventHub->FireOnCommonDialogEvent(
        std::make_shared<WebDialogEvent>(url, message, value, type, result), type));
    EXPECT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->resourceId, contextId);
    EXPECT_EQ(checkEvent->url, url);
    EXPECT_EQ(checkEvent->message, message);
    EXPECT_EQ(checkEvent->peer->result, result);
    delete checkEvent->peer;
    callResult = true;
    EXPECT_TRUE(webEventHub->FireOnCommonDialogEvent(
        std::make_shared<WebDialogEvent>(url, message, value, type, result), type));
    delete checkEvent->peer;
}

/*
 * @tc.name: onConfirmTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, onConfirmTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    std::string url = "url";
    std::string message = "message";
    std::string value = "value";
    DialogEventType type = DialogEventType::DIALOG_EVENT_CONFIRM;
    RefPtr<Result> result = Referenced::MakeRefPtr<MockResult>();

    struct CheckEvent {
        int32_t resourceId;
        std::string url;
        std::string message;
        JsResultPeer* peer;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    static constexpr int32_t contextId = 123;
    static auto callResult = false;
    auto checkCallback = [](Ark_VMContext context, const Ark_Int32 resourceId, const Ark_OnConfirmEvent parameter,
        const Callback_Boolean_Void continuation) {
        checkEvent = CheckEvent{
            .resourceId = resourceId,
            .url = Converter::Convert<std::string>(parameter.url),
            .message = Converter::Convert<std::string>(parameter.message),
            .peer = parameter.result,
        };
        CallbackHelper(continuation).InvokeSync(Converter::ArkValue<Ark_Boolean>(callResult));
    };

    Callback_OnConfirmEvent_Boolean arkCallback =
        Converter::ArkValue<Callback_OnConfirmEvent_Boolean>(nullptr, checkCallback, contextId);

    auto optCallback = Converter::ArkValue<Opt_Callback_OnConfirmEvent_Boolean>(arkCallback);
    modifier_->setOnConfirm(node_, &optCallback);

    EXPECT_FALSE(checkEvent.has_value());
    EXPECT_FALSE(webEventHub->FireOnCommonDialogEvent(
        std::make_shared<WebDialogEvent>(url, message, value, type, result), type));
    EXPECT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->resourceId, contextId);
    EXPECT_EQ(checkEvent->url, url);
    EXPECT_EQ(checkEvent->message, message);
    EXPECT_EQ(checkEvent->peer->result, result);
    delete checkEvent->peer;
    callResult = true;
    EXPECT_TRUE(webEventHub->FireOnCommonDialogEvent(
        std::make_shared<WebDialogEvent>(url, message, value, type, result), type));
    delete checkEvent->peer;
}

/*
 * @tc.name: onPromptTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, onPromptTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    std::string url = "url";
    std::string message = "message";
    std::string value = "value";
    DialogEventType type = DialogEventType::DIALOG_EVENT_PROMPT;
    RefPtr<Result> result = Referenced::MakeRefPtr<MockResult>();

    struct CheckEvent {
        int32_t resourceId;
        std::string url;
        std::string message;
        JsResultPeer* peer;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    static constexpr int32_t contextId = 123;
    static auto callResult = false;
    auto checkCallback = [](Ark_VMContext context, const Ark_Int32 resourceId, const Ark_OnPromptEvent parameter,
        const Callback_Boolean_Void continuation) {
        checkEvent = CheckEvent{
            .resourceId = resourceId,
            .url = Converter::Convert<std::string>(parameter.url),
            .message = Converter::Convert<std::string>(parameter.message),
            .peer = parameter.result,
        };
        CallbackHelper(continuation).InvokeSync(Converter::ArkValue<Ark_Boolean>(callResult));
    };

    Callback_OnPromptEvent_Boolean arkCallback =
        Converter::ArkValue<Callback_OnPromptEvent_Boolean>(nullptr, checkCallback, contextId);

    auto optCallback = Converter::ArkValue<Opt_Callback_OnPromptEvent_Boolean>(arkCallback);
    modifier_->setOnPrompt(node_, &optCallback);

    EXPECT_FALSE(checkEvent.has_value());
    EXPECT_FALSE(webEventHub->FireOnCommonDialogEvent(
        std::make_shared<WebDialogEvent>(url, message, value, type, result), type));
    EXPECT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->resourceId, contextId);
    EXPECT_EQ(checkEvent->url, url);
    EXPECT_EQ(checkEvent->message, message);
    EXPECT_EQ(checkEvent->peer->result, result);
    delete checkEvent->peer;
    callResult = true;
    EXPECT_TRUE(webEventHub->FireOnCommonDialogEvent(
        std::make_shared<WebDialogEvent>(url, message, value, type, result), type));
    delete checkEvent->peer;
}

/*
 * @tc.name: onConsoleTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, onConsoleTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    std::string message = "message";
    std::string sourceId = "sourceId";
    int lineNumber = 5;
    int messageLevel = 2;
    RefPtr<WebConsoleLog> param = Referenced::MakeRefPtr<WebConsoleMessageParam>(
        message, sourceId, lineNumber, messageLevel);

    struct CheckEvent {
        int32_t resourceId;
        ConsoleMessagePeer* peer;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    static constexpr int32_t contextId = 123;
    static auto callResult = false;
    auto checkCallback = [](Ark_VMContext context, const Ark_Int32 resourceId, const Ark_OnConsoleEvent parameter,
        const Callback_Boolean_Void continuation) {
        checkEvent = CheckEvent{
            .resourceId = resourceId,
            .peer = parameter.message,
        };
        CallbackHelper(continuation).InvokeSync(Converter::ArkValue<Ark_Boolean>(callResult));
    };

    Callback_OnConsoleEvent_Boolean arkCallback =
        Converter::ArkValue<Callback_OnConsoleEvent_Boolean>(nullptr, checkCallback, contextId);

    auto optCallback = Converter::ArkValue<Opt_Callback_OnConsoleEvent_Boolean>(arkCallback);
    modifier_->setOnConsole(node_, &optCallback);

    EXPECT_FALSE(checkEvent.has_value());
    const auto event = webEventHub->GetOnConsoleEvent();
    ASSERT_NE(event, nullptr);
    EXPECT_FALSE(event(std::make_shared<LoadWebConsoleLogEvent>(param)));
    EXPECT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->peer->webConsoleLog, param);
    delete checkEvent->peer;
    callResult = true;
    EXPECT_TRUE(event(std::make_shared<LoadWebConsoleLogEvent>(param)));
    delete checkEvent->peer;
}

/*
 * @tc.name: onErrorReceiveTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, onErrorReceiveTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    std::string errorInfo = "errorInfo";
    int errorCode = 5;
    RefPtr<WebError> webError = Referenced::MakeRefPtr<WebError>(errorInfo, errorCode);
    std::map<std::string, std::string> headers = {};
    std::string method = "method";
    std::string url = "url";
    bool hasGesture = true;
    bool isMainFrame = true;
    bool isRedirect = true;
    RefPtr<WebRequest> webRequest = Referenced::MakeRefPtr<WebRequest>(
        headers, method, url, hasGesture, isMainFrame, isRedirect);

    struct CheckEvent {
        int32_t resourceId;
        WebResourceErrorPeer* errorPeer;
        WebResourceRequestPeer* requestPeer;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    static constexpr int32_t contextId = 123;
    auto checkCallback = [](const Ark_Int32 resourceId, const Ark_OnErrorReceiveEvent parameter) {
        checkEvent = CheckEvent{
            .resourceId = resourceId,
            .errorPeer = parameter.error,
            .requestPeer = parameter.request,
        };
    };

    Callback_OnErrorReceiveEvent_Void arkCallback =
        Converter::ArkValue<Callback_OnErrorReceiveEvent_Void>(checkCallback, contextId);

    auto optCallback = Converter::ArkValue<Opt_Callback_OnErrorReceiveEvent_Void>(arkCallback);
    modifier_->setOnErrorReceive(node_, &optCallback);

    EXPECT_EQ(checkEvent.has_value(), false);
    webEventHub->FireOnErrorReceiveEvent(std::make_shared<ReceivedErrorEvent>(webRequest, webError));
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->errorPeer->handler, webError);
    EXPECT_EQ(checkEvent->requestPeer->webRequest, webRequest);
    delete checkEvent->errorPeer;
    delete checkEvent->requestPeer;
}

/*
 * @tc.name: onHttpErrorReceiveTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, onHttpErrorReceiveTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    RefPtr<WebResponse> webResponse = Referenced::MakeRefPtr<WebResponse>();
    std::map<std::string, std::string> headers = {};
    std::string method = "method";
    std::string url = "url";
    bool hasGesture = true;
    bool isMainFrame = true;
    bool isRedirect = true;
    RefPtr<WebRequest> webRequest = Referenced::MakeRefPtr<WebRequest>(
        headers, method, url, hasGesture, isMainFrame, isRedirect);

    struct CheckEvent {
        int32_t resourceId;
        WebResourceResponsePeer* responsePeer;
        WebResourceRequestPeer* requestPeer;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    static constexpr int32_t contextId = 123;
    auto checkCallback = [](const Ark_Int32 resourceId, const Ark_OnHttpErrorReceiveEvent parameter) {
        checkEvent = CheckEvent{
            .resourceId = resourceId,
            .responsePeer = parameter.response,
            .requestPeer = parameter.request,
        };
    };

    Callback_OnHttpErrorReceiveEvent_Void arkCallback =
        Converter::ArkValue<Callback_OnHttpErrorReceiveEvent_Void>(checkCallback, contextId);

    auto optCallback = Converter::ArkValue<Opt_Callback_OnHttpErrorReceiveEvent_Void>(arkCallback);
    modifier_->setOnHttpErrorReceive(node_, &optCallback);

    EXPECT_EQ(checkEvent.has_value(), false);
    webEventHub->FireOnHttpErrorReceiveEvent(std::make_shared<ReceivedHttpErrorEvent>(webRequest, webResponse));
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->responsePeer->handler, webResponse);
    EXPECT_EQ(checkEvent->requestPeer->webRequest, webRequest);
    delete checkEvent->responsePeer;
    delete checkEvent->requestPeer;
}

/*
 * @tc.name: onDownloadStartTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, onDownloadStartTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    std::string url = "url";
    std::string userAgent = "userAgent";
    std::string contentDisposition = "contentDisposition";
    std::string mimetype = "mimetype";
    long contentLength = 2000;

    struct CheckEvent {
        int32_t resourceId;
        std::string url;
        std::string userAgent;
        std::string contentDisposition;
        std::string mimetype;
        long contentLength;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    static constexpr int32_t contextId = 123;
    auto checkCallback = [](const Ark_Int32 resourceId, const Ark_OnDownloadStartEvent parameter) {
        checkEvent = CheckEvent{
            .resourceId = resourceId,
            .url = Converter::Convert<std::string>(parameter.url),
            .userAgent = Converter::Convert<std::string>(parameter.userAgent),
            .contentDisposition = Converter::Convert<std::string>(parameter.contentDisposition),
            .mimetype = Converter::Convert<std::string>(parameter.mimetype),
            .contentLength = Converter::Convert<long>(parameter.contentLength)
        };
    };

    Callback_OnDownloadStartEvent_Void arkCallback =
        Converter::ArkValue<Callback_OnDownloadStartEvent_Void>(checkCallback, contextId);

    auto optCallback = Converter::ArkValue<Opt_Callback_OnDownloadStartEvent_Void>(arkCallback);
    modifier_->setOnDownloadStart(node_, &optCallback);

    EXPECT_EQ(checkEvent.has_value(), false);
    webEventHub->FireOnDownloadStartEvent(
        std::make_shared<DownloadStartEvent>(url, userAgent, contentDisposition, mimetype, contentLength));
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->resourceId, contextId);
    EXPECT_EQ(checkEvent->url, url);
    EXPECT_EQ(checkEvent->userAgent, userAgent);
    EXPECT_EQ(checkEvent->contentDisposition, contentDisposition);
    EXPECT_EQ(checkEvent->mimetype, mimetype);
    EXPECT_EQ(checkEvent->contentLength, contentLength);
}

/*
 * @tc.name: onRefreshAccessedHistoryTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, onRefreshAccessedHistoryTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    std::string url = "url";
    bool isRefreshed = true;

    struct CheckEvent {
        int32_t resourceId;
        std::string url;
        bool isRefreshed;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    static constexpr int32_t contextId = 123;
    auto checkCallback = [](const Ark_Int32 resourceId, const Ark_OnRefreshAccessedHistoryEvent parameter) {
        checkEvent = CheckEvent{
            .resourceId = resourceId,
            .url = Converter::Convert<std::string>(parameter.url),
            .isRefreshed = Converter::Convert<bool>(parameter.isRefreshed)
        };
    };

    Callback_OnRefreshAccessedHistoryEvent_Void arkCallback =
        Converter::ArkValue<Callback_OnRefreshAccessedHistoryEvent_Void>(checkCallback, contextId);

    auto optCallback = Converter::ArkValue<Opt_Callback_OnRefreshAccessedHistoryEvent_Void>(arkCallback);
    modifier_->setOnRefreshAccessedHistory(node_, &optCallback);

    EXPECT_EQ(checkEvent.has_value(), false);
    webEventHub->FireOnRefreshAccessedHistoryEvent(std::make_shared<RefreshAccessedHistoryEvent>(url, isRefreshed));
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->resourceId, contextId);
    EXPECT_EQ(checkEvent->url, url);
    EXPECT_EQ(checkEvent->isRefreshed, isRefreshed);
}

/*
 * @tc.name: onUrlLoadInterceptTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, onUrlLoadInterceptTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    std::string dataStr = "data";

    struct CheckEvent {
        int32_t resourceId;
        std::string data;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    static constexpr int32_t contextId = 123;
    static auto callResult = false;
    auto checkCallback = [](Ark_VMContext context, const Ark_Int32 resourceId,
        const Opt_Literal_Union_String_WebResourceRequest_data parameter, const Callback_Boolean_Void continuation) {
        auto dataOpt = Converter::OptConvert<Ark_Literal_Union_String_WebResourceRequest_data>(parameter);
        if (dataOpt) {
            Converter::VisitUnion(dataOpt.value().data,
                [resourceId](const Ark_String& str) {
                    checkEvent = CheckEvent{
                        .resourceId = resourceId,
                        .data = Converter::Convert<std::string>(str)
                    };
                },
                [](const auto& value) {},
                []() {}
            );
        }
        CallbackHelper(continuation).InvokeSync(Converter::ArkValue<Ark_Boolean>(callResult));
    };

    Type_WebAttribute_onUrlLoadIntercept_callback arkCallback =
        Converter::ArkValue<Type_WebAttribute_onUrlLoadIntercept_callback>(nullptr, checkCallback, contextId);

    auto optCallback = Converter::ArkValue<Opt_Type_WebAttribute_onUrlLoadIntercept_callback>(arkCallback);
    modifier_->setOnUrlLoadIntercept(node_, &optCallback);

    EXPECT_FALSE(checkEvent.has_value());
    const auto event = webEventHub->GetOnUrlLoadInterceptEvent();
    ASSERT_NE(event, nullptr);
    EXPECT_FALSE(event(std::make_shared<UrlLoadInterceptEvent>(dataStr)));
    EXPECT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->resourceId, contextId);
    EXPECT_EQ(checkEvent->data, dataStr);
    callResult = true;
    EXPECT_TRUE(event(std::make_shared<UrlLoadInterceptEvent>(dataStr)));
}

/*
 * @tc.name: onRenderExitedTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, onRenderExitedTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    RenderExitReason exitedReason = RenderExitReason::CRASHED;

    struct CheckEvent {
        int32_t resourceId;
        RenderExitReason exitedReason;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    static constexpr int32_t contextId = 123;
    auto checkCallback = [](const Ark_Int32 resourceId, const Ark_OnRenderExitedEvent parameter) {
        checkEvent = CheckEvent{
            .resourceId = resourceId,
            .exitedReason = Converter::OptConvert<RenderExitReason>(parameter.renderExitReason)
                .value_or(RenderExitReason::EXIT_UNKNOWN),
        };
    };

    Callback_OnRenderExitedEvent_Void arkCallback =
        Converter::ArkValue<Callback_OnRenderExitedEvent_Void>(checkCallback, contextId);

    auto optCallback = Converter::ArkValue<Opt_Callback_OnRenderExitedEvent_Void>(arkCallback);
    modifier_->setOnRenderExited(node_, &optCallback);

    EXPECT_EQ(checkEvent.has_value(), false);
    webEventHub->FireOnRenderExitedEvent(std::make_shared<RenderExitedEvent>(
        static_cast<int32_t>(exitedReason)));
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->resourceId, contextId);
    EXPECT_EQ(checkEvent->exitedReason, exitedReason);
}

/*
 * @tc.name: onShowFileSelectorTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, onShowFileSelectorTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    RefPtr<WebFileSelectorParam> param = Referenced::MakeRefPtr<MockWebFileSelectorParam>();
    RefPtr<FileSelectorResult> result = Referenced::MakeRefPtr<MockFileSelectorResult>();

    struct CheckEvent {
        int32_t resourceId;
        FileSelectorResultPeer* resultPeer;
        FileSelectorParamPeer* paramPeer;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    static constexpr int32_t contextId = 123;
    static auto callResult = false;
    auto checkCallback = [](Ark_VMContext context, const Ark_Int32 resourceId,
        const Ark_OnShowFileSelectorEvent parameter, const Callback_Boolean_Void continuation) {
        checkEvent = CheckEvent{
            .resourceId = resourceId,
            .resultPeer = parameter.result,
            .paramPeer = parameter.fileSelector,
        };
        CallbackHelper(continuation).InvokeSync(Converter::ArkValue<Ark_Boolean>(callResult));
    };

    Callback_OnShowFileSelectorEvent_Boolean arkCallback =
        Converter::ArkValue<Callback_OnShowFileSelectorEvent_Boolean>(nullptr, checkCallback, contextId);

    auto optCallback = Converter::ArkValue<Opt_Callback_OnShowFileSelectorEvent_Boolean>(arkCallback);
    modifier_->setOnShowFileSelector(node_, &optCallback);

    EXPECT_FALSE(checkEvent.has_value());
    const auto event = webEventHub->GetOnFileSelectorShowEvent();
    ASSERT_NE(event, nullptr);
    EXPECT_FALSE(event(std::make_shared<FileSelectorEvent>(param, result)));
    EXPECT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->resultPeer->handler, result);
    EXPECT_EQ(checkEvent->paramPeer->handler, param);
    delete checkEvent->resultPeer;
    delete checkEvent->paramPeer;
    callResult = true;
    EXPECT_TRUE(event(std::make_shared<FileSelectorEvent>(param, result)));
    delete checkEvent->resultPeer;
    delete checkEvent->paramPeer;
}

/*
 * @tc.name: onResourceLoadTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, onResourceLoadTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    std::string url = "url";

    struct CheckEvent {
        int32_t resourceId;
        std::string url;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    static constexpr int32_t contextId = 123;
    auto checkCallback = [](const Ark_Int32 resourceId, const Ark_OnResourceLoadEvent parameter) {
        checkEvent = CheckEvent{
            .resourceId = resourceId,
            .url = Converter::Convert<std::string>(parameter.url)
        };
    };

    Callback_OnResourceLoadEvent_Void arkCallback =
        Converter::ArkValue<Callback_OnResourceLoadEvent_Void>(checkCallback, contextId);

    auto optCallback = Converter::ArkValue<Opt_Callback_OnResourceLoadEvent_Void>(arkCallback);
    modifier_->setOnResourceLoad(node_, &optCallback);

    EXPECT_EQ(checkEvent.has_value(), false);
    webEventHub->FireOnResourceLoadEvent(std::make_shared<ResourceLoadEvent>(url));
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->resourceId, contextId);
    EXPECT_EQ(checkEvent->url, url);
}

/*
 * @tc.name: onFullScreenExitTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, onFullScreenExitTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    std::string type = "onFullScreenExit";

    struct CheckEvent {
        int32_t resourceId;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    static constexpr int32_t contextId = 123;
    auto checkCallback = [](const Ark_Int32 resourceId) {
        checkEvent = CheckEvent{
            .resourceId = resourceId
        };
    };

    Callback_Void arkCallback =
        Converter::ArkValue<Callback_Void>(checkCallback, contextId);

    auto optCallback = Converter::ArkValue<Opt_Callback_Void>(arkCallback);
    modifier_->setOnFullScreenExit(node_, &optCallback);

    EXPECT_EQ(checkEvent.has_value(), false);
    webEventHub->FireOnFullScreenExitEvent(std::make_shared<BaseEventInfo>(type));
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->resourceId, contextId);
}

/*
 * @tc.name: onFullScreenEnterTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, onFullScreenEnterTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    RefPtr<FullScreenExitHandler> handler = Referenced::MakeRefPtr<MockFullScreenExitHandler>();
    int width = 600;
    int height = 800;

    struct CheckEvent {
        int32_t resourceId;
        FullScreenExitHandlerPeer* peer;
        int width;
        int height;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    static constexpr int32_t contextId = 123;
    auto checkCallback = [](const Ark_Int32 resourceId, const Ark_FullScreenEnterEvent parameter) {
        checkEvent = CheckEvent{
            .resourceId = resourceId,
            .peer = parameter.handler,
            .width = Converter::OptConvert<int>(parameter.videoWidth).value_or(0),
            .height = Converter::OptConvert<int>(parameter.videoHeight).value_or(0)
        };
    };

    OnFullScreenEnterCallback arkCallback =
        Converter::ArkValue<OnFullScreenEnterCallback>(checkCallback, contextId);

    auto optCallback = Converter::ArkValue<Opt_OnFullScreenEnterCallback>(arkCallback);
    modifier_->setOnFullScreenEnter(node_, &optCallback);

    EXPECT_EQ(checkEvent.has_value(), false);
    webEventHub->FireOnFullScreenEnterEvent(std::make_shared<FullScreenEnterEvent>(handler, width, height));
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->resourceId, contextId);
    EXPECT_EQ(checkEvent->peer->handler, handler);
    EXPECT_EQ(checkEvent->width, width);
    EXPECT_EQ(checkEvent->height, height);
    delete checkEvent->peer;
}

/*
 * @tc.name: onScaleChangeTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, onScaleChangeTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    float oldScale = 2.5f;
    float newScale = 3.5f;

    struct CheckEvent {
        int32_t resourceId;
        float oldScale;
        float newScale;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    static constexpr int32_t contextId = 123;
    auto checkCallback = [](const Ark_Int32 resourceId, const Ark_OnScaleChangeEvent parameter) {
        checkEvent = CheckEvent{
            .resourceId = resourceId,
            .oldScale = Converter::Convert<float>(parameter.oldScale),
            .newScale = Converter::Convert<float>(parameter.newScale)
        };
    };

    Callback_OnScaleChangeEvent_Void arkCallback =
        Converter::ArkValue<Callback_OnScaleChangeEvent_Void>(checkCallback, contextId);

    auto optCallback = Converter::ArkValue<Opt_Callback_OnScaleChangeEvent_Void>(arkCallback);
    modifier_->setOnScaleChange(node_, &optCallback);

    EXPECT_EQ(checkEvent.has_value(), false);
    webEventHub->FireOnScaleChangeEvent(std::make_shared<ScaleChangeEvent>(oldScale, newScale));
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->resourceId, contextId);
    EXPECT_NEAR(checkEvent->oldScale, oldScale, FLT_EPSILON);
    EXPECT_NEAR(checkEvent->newScale, newScale, FLT_EPSILON);
}

/*
 * @tc.name: onHttpAuthRequestTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, onHttpAuthRequestTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    RefPtr<AuthResult> result = Referenced::MakeRefPtr<MockAuthResult>();
    std::string host = "host";
    std::string realm = "realm";

    struct CheckEvent {
        int32_t resourceId;
        HttpAuthHandlerPeer* peer;
        std::string host;
        std::string realm;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    static constexpr int32_t contextId = 123;
    static auto callResult = false;
    auto checkCallback = [](Ark_VMContext context, const Ark_Int32 resourceId,
        const Ark_OnHttpAuthRequestEvent parameter, const Callback_Boolean_Void continuation) {
        checkEvent = CheckEvent{
            .resourceId = resourceId,
            .peer = parameter.handler,
            .host = Converter::Convert<std::string>(parameter.host),
            .realm = Converter::Convert<std::string>(parameter.realm)
        };
        CallbackHelper(continuation).InvokeSync(Converter::ArkValue<Ark_Boolean>(callResult));
    };

    Callback_OnHttpAuthRequestEvent_Boolean arkCallback =
        Converter::ArkValue<Callback_OnHttpAuthRequestEvent_Boolean>(nullptr, checkCallback, contextId);

    auto optCallback = Converter::ArkValue<Opt_Callback_OnHttpAuthRequestEvent_Boolean>(arkCallback);
    modifier_->setOnHttpAuthRequest(node_, &optCallback);

    EXPECT_FALSE(checkEvent.has_value());
    const auto event = webEventHub->GetOnHttpAuthRequestEvent();
    ASSERT_NE(event, nullptr);
    EXPECT_FALSE(event(std::make_shared<WebHttpAuthEvent>(result, host, realm)));
    EXPECT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->resourceId, contextId);
    EXPECT_EQ(checkEvent->peer->handler, result);
    EXPECT_EQ(checkEvent->host, host);
    EXPECT_EQ(checkEvent->realm, realm);
    delete checkEvent->peer;
    callResult = true;
    EXPECT_TRUE(event(std::make_shared<WebHttpAuthEvent>(result, host, realm)));
    delete checkEvent->peer;
}

/*
 * @tc.name: onInterceptRequestTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, onInterceptRequestTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    std::map<std::string, std::string> headers = {};
    RefPtr<WebRequest> webRequest = Referenced::MakeRefPtr<WebRequest>(
        headers, "method", "url", true, true, true);

    struct CheckEvent {
        int32_t resourceId;
        WebResourceRequestPeer* peer;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    static constexpr int32_t contextId = 123;
    static auto callResult = new WebResourceResponsePeer {
        .handler = Referenced::MakeRefPtr<WebResponse>()
    };
    callResult->handler->SetStatusCode(404);
    auto checkCallback = [](Ark_VMContext context, const Ark_Int32 resourceId,
        const Ark_OnInterceptRequestEvent parameter, const Callback_WebResourceResponse_Void continuation) {
        checkEvent = CheckEvent{
            .resourceId = resourceId,
            .peer = parameter.request,
        };
        CallbackHelper(continuation).InvokeSync(callResult);
    };

    Callback_OnInterceptRequestEvent_WebResourceResponse arkCallback =
        Converter::ArkValue<Callback_OnInterceptRequestEvent_WebResourceResponse>(nullptr, checkCallback, contextId);
    auto optCallback = Converter::ArkValue<Opt_Callback_OnInterceptRequestEvent_WebResourceResponse>(arkCallback);
    modifier_->setOnInterceptRequest(node_, &optCallback);

    EXPECT_FALSE(checkEvent.has_value());
    const auto event = webEventHub->GetOnInterceptRequestEvent();
    ASSERT_NE(event, nullptr);
    auto result = event(std::make_shared<OnInterceptRequestEvent>(webRequest));
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->GetStatusCode(), 404);
    EXPECT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->resourceId, contextId);
    EXPECT_EQ(checkEvent->peer->webRequest, webRequest);
    delete checkEvent->peer;
    delete callResult;
    callResult = new WebResourceResponsePeer {
        .handler = Referenced::MakeRefPtr<WebResponse>()
    };
    result = event(std::make_shared<OnInterceptRequestEvent>(webRequest));
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->GetStatusCode(), 0);
    delete checkEvent->peer;
    delete callResult;
}

/*
 * @tc.name: onPermissionRequestTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, onPermissionRequestTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    RefPtr<WebPermissionRequest> webPermissionRequest = Referenced::MakeRefPtr<MockWebPermissionRequest>();

    struct CheckEvent {
        int32_t resourceId;
        PermissionRequestPeer* peer;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    static constexpr int32_t contextId = 123;
    auto checkCallback = [](const Ark_Int32 resourceId, const Ark_OnPermissionRequestEvent parameter) {
        checkEvent = CheckEvent{
            .resourceId = resourceId,
            .peer = parameter.request,
        };
    };

    Callback_OnPermissionRequestEvent_Void arkCallback =
        Converter::ArkValue<Callback_OnPermissionRequestEvent_Void>(checkCallback, contextId);
    auto optCallback = Converter::ArkValue<Opt_Callback_OnPermissionRequestEvent_Void>(arkCallback);
    modifier_->setOnPermissionRequest(node_, &optCallback);

    EXPECT_EQ(checkEvent.has_value(), false);
    webEventHub->FireOnPermissionRequestEvent(std::make_shared<WebPermissionRequestEvent>(webPermissionRequest));
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->resourceId, contextId);
    EXPECT_EQ(checkEvent->peer->handler, webPermissionRequest);
    delete checkEvent->peer;
}

/*
 * @tc.name: onScreenCaptureRequestTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, onScreenCaptureRequestTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    RefPtr<WebScreenCaptureRequest> request = Referenced::MakeRefPtr<MockWebScreenCaptureRequest>();

    struct CheckEvent {
        int32_t resourceId;
        ScreenCaptureHandlerPeer* peer;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    static constexpr int32_t contextId = 123;
    auto checkCallback = [](const Ark_Int32 resourceId, const Ark_OnScreenCaptureRequestEvent parameter) {
        checkEvent = CheckEvent{
            .resourceId = resourceId,
            .peer = parameter.handler,
        };
    };

    Callback_OnScreenCaptureRequestEvent_Void arkCallback =
        Converter::ArkValue<Callback_OnScreenCaptureRequestEvent_Void>(checkCallback, contextId);
    auto optCallback = Converter::ArkValue<Opt_Callback_OnScreenCaptureRequestEvent_Void>(arkCallback);
    modifier_->setOnScreenCaptureRequest(node_, &optCallback);

    EXPECT_EQ(checkEvent.has_value(), false);
    webEventHub->FireOnScreenCaptureRequestEvent(std::make_shared<WebScreenCaptureRequestEvent>(request));
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->resourceId, contextId);
    EXPECT_EQ(checkEvent->peer->handler, request);
    delete checkEvent->peer;
}

/*
 * @tc.name: onContextMenuShowTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, onContextMenuShowTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    RefPtr<WebContextMenuParam> param = Referenced::MakeRefPtr<MockWebContextMenuParam>();
    RefPtr<ContextMenuResult> result = Referenced::MakeRefPtr<MockContextMenuResult>();

    struct CheckEvent {
        int32_t resourceId;
        WebContextMenuParamPeer* paramPeer;
        WebContextMenuResultPeer* resultPeer;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    static constexpr int32_t contextId = 123;
    static auto callResult = false;
    auto checkCallback = [](Ark_VMContext context, const Ark_Int32 resourceId,
        const Ark_OnContextMenuShowEvent parameter, const Callback_Boolean_Void continuation) {
        checkEvent = CheckEvent{
            .resourceId = resourceId,
            .paramPeer = parameter.param,
            .resultPeer = parameter.result,
        };
        CallbackHelper(continuation).InvokeSync(Converter::ArkValue<Ark_Boolean>(callResult));
    };

    Callback_OnContextMenuShowEvent_Boolean arkCallback =
        Converter::ArkValue<Callback_OnContextMenuShowEvent_Boolean>(nullptr, checkCallback, contextId);
    auto optCallback = Converter::ArkValue<Opt_Callback_OnContextMenuShowEvent_Boolean>(arkCallback);
    modifier_->setOnContextMenuShow(node_, &optCallback);

    EXPECT_FALSE(checkEvent.has_value());
    const auto event = webEventHub->GetOnContextMenuShowEvent();
    ASSERT_NE(event, nullptr);
    EXPECT_FALSE(event(std::make_shared<ContextMenuEvent>(param, result)));
    EXPECT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->resourceId, contextId);
    EXPECT_EQ(checkEvent->paramPeer->handler, param);
    EXPECT_EQ(checkEvent->resultPeer->handler, result);
    delete checkEvent->paramPeer;
    delete checkEvent->resultPeer;
    callResult = true;
    EXPECT_TRUE(event(std::make_shared<ContextMenuEvent>(param, result)));
    delete checkEvent->paramPeer;
    delete checkEvent->resultPeer;
}

/*
 * @tc.name: onContextMenuHideTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, onContextMenuHideTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    std::string type = "onContextMenuHide";

    struct CheckEvent {
        int32_t resourceId;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    static constexpr int32_t contextId = 123;
    auto checkCallback = [](const Ark_Int32 resourceId) {
        checkEvent = CheckEvent{
            .resourceId = resourceId
        };
    };

    OnContextMenuHideCallback arkCallback =
        Converter::ArkValue<OnContextMenuHideCallback>(checkCallback, contextId);
    auto optCallback = Converter::ArkValue<Opt_OnContextMenuHideCallback>(arkCallback);
    modifier_->setOnContextMenuHide(node_, &optCallback);

    EXPECT_EQ(checkEvent.has_value(), false);
    webEventHub->FireOnContextMenuHideEvent(std::make_shared<BaseEventInfo>(type));
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->resourceId, contextId);
}

/*
 * @tc.name: onSearchResultReceiveTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, onSearchResultReceiveTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    int activeMatchOrdina = 5;
    int numberOfMatches = 2;
    bool isDoneCounting = true;

    struct CheckEvent {
        int32_t resourceId;
        int activeMatchOrdina;
        int numberOfMatches;
        bool isDoneCounting;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    static constexpr int32_t contextId = 123;
    auto checkCallback = [](const Ark_Int32 resourceId, const Ark_OnSearchResultReceiveEvent parameter) {
        checkEvent = CheckEvent{
            .resourceId = resourceId,
            .activeMatchOrdina = Converter::Convert<int>(parameter.activeMatchOrdinal),
            .numberOfMatches = Converter::Convert<int>(parameter.numberOfMatches),
            .isDoneCounting = Converter::Convert<bool>(parameter.isDoneCounting)
        };
    };

    Callback_OnSearchResultReceiveEvent_Void arkCallback =
        Converter::ArkValue<Callback_OnSearchResultReceiveEvent_Void>(checkCallback, contextId);
    auto optCallback = Converter::ArkValue<Opt_Callback_OnSearchResultReceiveEvent_Void>(arkCallback);
    modifier_->setOnSearchResultReceive(node_, &optCallback);

    EXPECT_EQ(checkEvent.has_value(), false);
    webEventHub->FireOnSearchResultReceiveEvent(std::make_shared<SearchResultReceiveEvent>(
        activeMatchOrdina, numberOfMatches, isDoneCounting));
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->resourceId, contextId);
    EXPECT_EQ(checkEvent->activeMatchOrdina, activeMatchOrdina);
    EXPECT_EQ(checkEvent->numberOfMatches, numberOfMatches);
    EXPECT_EQ(checkEvent->isDoneCounting, isDoneCounting);
}

/*
 * @tc.name: onScrollTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, onScrollTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    double xOffset = 6.6f;
    double yOffset = 8.9f;

    struct CheckEvent {
        int32_t resourceId;
        double xOffset;
        double yOffset;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    static constexpr int32_t contextId = 123;
    auto checkCallback = [](const Ark_Int32 resourceId, const Ark_OnScrollEvent parameter) {
        checkEvent = CheckEvent{
            .resourceId = resourceId,
            .xOffset = static_cast<double>(Converter::Convert<float>(parameter.xOffset)),
            .yOffset = static_cast<double>(Converter::Convert<float>(parameter.yOffset))
        };
    };

    Callback_OnScrollEvent_Void arkCallback =
        Converter::ArkValue<Callback_OnScrollEvent_Void>(checkCallback, contextId);
    auto optCallback = Converter::ArkValue<Opt_Callback_OnScrollEvent_Void>(arkCallback);
    modifier_->setOnScroll(node_, &optCallback);

    EXPECT_EQ(checkEvent.has_value(), false);
    webEventHub->FireOnScrollEvent(std::make_shared<WebOnScrollEvent>(xOffset, yOffset));
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->resourceId, contextId);
    EXPECT_NEAR(checkEvent->xOffset, xOffset, FLT_EPSILON);
    EXPECT_NEAR(checkEvent->yOffset, yOffset, FLT_EPSILON);
}

/*
 * @tc.name: onSslErrorEventReceiveTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, onSslErrorEventReceiveTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();

    RefPtr<SslErrorResult> result = Referenced::MakeRefPtr<MockSslErrorResult>();
    SslError error = SslError::DATE_INVALID;
    std::vector<std::string> certChainData { "cert1", "cert2" };

    struct CheckEvent {
        int32_t resourceId;
        SslErrorHandlerPeer* peer;
        SslError error;
        std::optional<std::vector<std::string>> certChainData;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    static constexpr int32_t contextId = 123;
    auto checkCallback = [](const Ark_Int32 resourceId, const Ark_OnSslErrorEventReceiveEvent parameter) {
        checkEvent = CheckEvent{
            .resourceId = resourceId,
            .peer = parameter.handler,
            .error = Converter::OptConvert<SslError>(parameter.error).value_or(SslError::INVALID),
            .certChainData = Converter::OptConvert<std::vector<std::string>>(parameter.certChainData)
        };
    };

    Callback_OnSslErrorEventReceiveEvent_Void arkCallback =
        Converter::ArkValue<Callback_OnSslErrorEventReceiveEvent_Void>(checkCallback, contextId);
    auto optCallback = Converter::ArkValue<Opt_Callback_OnSslErrorEventReceiveEvent_Void>(arkCallback);
    modifier_->setOnSslErrorEventReceive(node_, &optCallback);

    EXPECT_EQ(checkEvent.has_value(), false);
    webEventHub->FireOnSslErrorRequestEvent(std::make_shared<WebSslErrorEvent>(
        result, static_cast<int32_t>(error), certChainData));
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->resourceId, contextId);
    EXPECT_EQ(checkEvent->peer->handler, result);
    EXPECT_EQ(checkEvent->error, error);
    EXPECT_EQ(checkEvent->certChainData.has_value(), true);
    EXPECT_EQ(checkEvent->certChainData.value(), certChainData);
    delete checkEvent->peer;
}

/*
 * @tc.name: onSslErrorEventTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, onSslErrorEventTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();

    RefPtr<AllSslErrorResult> result = Referenced::MakeRefPtr<MockSslErrorResult>();
    SslError error = SslError::DATE_INVALID;
    std::string url = "url";
    std::string originalUrl = "originalUrl";
    std::string referrer = "referrer";
    bool isFatalError = true, isMainFrame = true;

    struct CheckEvent {
        int32_t resourceId;
        SslErrorHandlerPeer* peer;
        SslError error;
        std::string url;
        std::string originalUrl;
        std::string referrer;
        bool isFatalError;
        bool isMainFrame;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    static constexpr int32_t contextId = 123;
    auto checkCallback = [](const Ark_Int32 resourceId, const Ark_SslErrorEvent parameter) {
        checkEvent = CheckEvent{
            .resourceId = resourceId,
            .peer = parameter.handler,
            .error = Converter::OptConvert<SslError>(parameter.error).value_or(SslError::INVALID),
            .url = Converter::Convert<std::string>(parameter.url),
            .originalUrl = Converter::Convert<std::string>(parameter.originalUrl),
            .referrer = Converter::Convert<std::string>(parameter.referrer),
            .isFatalError = Converter::Convert<bool>(parameter.isFatalError),
            .isMainFrame = Converter::Convert<bool>(parameter.isMainFrame)
        };
    };

    OnSslErrorEventCallback arkCallback = Converter::ArkValue<OnSslErrorEventCallback>(checkCallback, contextId);
    auto optCallback = Converter::ArkValue<Opt_OnSslErrorEventCallback>(arkCallback);
    modifier_->setOnSslErrorEvent(node_, &optCallback);

    EXPECT_EQ(checkEvent.has_value(), false);
    webEventHub->FireOnAllSslErrorRequestEvent(std::make_shared<WebAllSslErrorEvent>(
        result, static_cast<int32_t>(error), url, originalUrl, referrer, isFatalError, isMainFrame));
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->resourceId, contextId);
    EXPECT_EQ(checkEvent->peer->handler, result);
    EXPECT_EQ(checkEvent->error, error);
    EXPECT_EQ(checkEvent->url, url);
    EXPECT_EQ(checkEvent->originalUrl, originalUrl);
    EXPECT_EQ(checkEvent->referrer, referrer);
    EXPECT_EQ(checkEvent->isFatalError, isFatalError);
    EXPECT_EQ(checkEvent->isMainFrame, isMainFrame);
    delete checkEvent->peer;
}

/*
 * @tc.name: onClientAuthenticationRequestTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, onClientAuthenticationRequestTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    RefPtr<SslSelectCertResult> handler = Referenced::MakeRefPtr<MockSslSelectCertResult>();
    std::string host = "host";
    int32_t port = 80;
    std::vector<std::string> keyTypes = { "keyType1", "keyType2" };
    std::vector<std::string> issuers = { "issuer1", "issuer2" };

    struct CheckEvent {
        int32_t resourceId;
        ClientAuthenticationHandlerPeer* peer;
        std::string host;
        int32_t port;
        std::vector<std::string> keyTypes;
        std::vector<std::string> issuers;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    static constexpr int32_t contextId = 123;
    auto checkCallback = [](const Ark_Int32 resourceId, const Ark_OnClientAuthenticationEvent parameter) {
        checkEvent = CheckEvent{
            .resourceId = resourceId,
            .peer = parameter.handler,
            .host = Converter::Convert<std::string>(parameter.host),
            .port = Converter::Convert<int32_t>(parameter.port),
            .keyTypes = Converter::Convert<std::vector<std::string>>(parameter.keyTypes),
            .issuers = Converter::Convert<std::vector<std::string>>(parameter.issuers)
        };
    };

    Callback_OnClientAuthenticationEvent_Void arkCallback =
        Converter::ArkValue<Callback_OnClientAuthenticationEvent_Void>(checkCallback, contextId);
    auto optCallback = Converter::ArkValue<Opt_Callback_OnClientAuthenticationEvent_Void>(arkCallback);
    modifier_->setOnClientAuthenticationRequest(node_, &optCallback);

    EXPECT_EQ(checkEvent.has_value(), false);
    webEventHub->FireOnSslSelectCertRequestEvent(std::make_shared<WebSslSelectCertEvent>(
        handler, host, port, keyTypes, issuers));
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->resourceId, contextId);
    EXPECT_EQ(checkEvent->peer->handler, handler);
    EXPECT_EQ(checkEvent->host, host);
    EXPECT_EQ(checkEvent->port, port);
    EXPECT_EQ(checkEvent->keyTypes, keyTypes);
    EXPECT_EQ(checkEvent->issuers, issuers);
    delete checkEvent->peer;
}

/*
 * @tc.name: onWindowNewTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, onWindowNewTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    std::string targetUrl = "targetUrl";
    bool isAlert = true;
    bool isUserTrigger = true;
    RefPtr<WebWindowNewHandler> handler = Referenced::MakeRefPtr<MockWebWindowNewHandler>();

    struct CheckEvent {
        int32_t resourceId;
        ControllerHandlerPeer* peer;
        std::string targetUrl;
        bool isAlert;
        bool isUserTrigger;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    static constexpr int32_t contextId = 123;
    auto checkCallback = [](const Ark_Int32 resourceId, const Ark_OnWindowNewEvent parameter) {
        checkEvent = CheckEvent{
            .resourceId = resourceId,
            .peer = parameter.handler,
            .targetUrl = Converter::Convert<std::string>(parameter.targetUrl),
            .isAlert = Converter::Convert<bool>(parameter.isAlert),
            .isUserTrigger = Converter::Convert<bool>(parameter.isUserTrigger)
        };
    };

    Callback_OnWindowNewEvent_Void arkCallback =
        Converter::ArkValue<Callback_OnWindowNewEvent_Void>(checkCallback, contextId);
    auto optCallback = Converter::ArkValue<Opt_Callback_OnWindowNewEvent_Void>(arkCallback);
    modifier_->setOnWindowNew(node_, &optCallback);

    EXPECT_EQ(checkEvent.has_value(), false);
    webEventHub->FireOnWindowNewEvent(std::make_shared<WebWindowNewEvent>(
        targetUrl, isAlert, isUserTrigger, handler));
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->resourceId, contextId);
    EXPECT_EQ(checkEvent->peer->handler, handler);
    EXPECT_EQ(checkEvent->targetUrl, targetUrl);
    EXPECT_EQ(checkEvent->isAlert, isAlert);
    EXPECT_EQ(checkEvent->isUserTrigger, isUserTrigger);
    delete checkEvent->peer;
}

/*
 * @tc.name: onWindowExitTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, onWindowExitTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    std::string type = "onWindowExit";

    struct CheckEvent {
        int32_t resourceId;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    static constexpr int32_t contextId = 123;
    auto checkCallback = [](const Ark_Int32 resourceId) {
        checkEvent = CheckEvent{
            .resourceId = resourceId
        };
    };

    Callback_Void arkCallback =
        Converter::ArkValue<Callback_Void>(checkCallback, contextId);
    auto optCallback = Converter::ArkValue<Opt_Callback_Void>(arkCallback);
    modifier_->setOnWindowExit(node_, &optCallback);

    EXPECT_EQ(checkEvent.has_value(), false);
    webEventHub->FireOnWindowExitEvent(std::make_shared<BaseEventInfo>(type));
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->resourceId, contextId);
}

/*
 * @tc.name: onTouchIconUrlReceivedTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, onTouchIconUrlReceivedTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    std::string url = "url";
    bool precomposed = true;

    struct CheckEvent {
        int32_t resourceId;
        std::string url;
        bool precomposed;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    static constexpr int32_t contextId = 123;
    auto checkCallback = [](const Ark_Int32 resourceId, const Ark_OnTouchIconUrlReceivedEvent parameter) {
        checkEvent = CheckEvent{
            .resourceId = resourceId,
            .url = Converter::Convert<std::string>(parameter.url),
            .precomposed = Converter::Convert<bool>(parameter.precomposed)
        };
    };

    Callback_OnTouchIconUrlReceivedEvent_Void arkCallback =
        Converter::ArkValue<Callback_OnTouchIconUrlReceivedEvent_Void>(checkCallback, contextId);
    auto optCallback = Converter::ArkValue<Opt_Callback_OnTouchIconUrlReceivedEvent_Void>(arkCallback);
    modifier_->setOnTouchIconUrlReceived(node_, &optCallback);

    EXPECT_EQ(checkEvent.has_value(), false);
    webEventHub->FireOnTouchIconUrlEvent(std::make_shared<TouchIconUrlEvent>(url, precomposed));
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->resourceId, contextId);
    EXPECT_EQ(checkEvent->url, url);
    EXPECT_EQ(checkEvent->precomposed, precomposed);
}

/*
 * @tc.name: onPageVisibleTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, onPageVisibleTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    std::string url = "url";

    struct CheckEvent {
        int32_t resourceId;
        std::string url;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    static constexpr int32_t contextId = 123;
    auto checkCallback = [](const Ark_Int32 resourceId, const Ark_OnPageVisibleEvent parameter) {
        checkEvent = CheckEvent{
            .resourceId = resourceId,
            .url = Converter::Convert<std::string>(parameter.url)
        };
    };

    Callback_OnPageVisibleEvent_Void arkCallback =
        Converter::ArkValue<Callback_OnPageVisibleEvent_Void>(checkCallback, contextId);
    auto optCallback = Converter::ArkValue<Opt_Callback_OnPageVisibleEvent_Void>(arkCallback);
    modifier_->setOnPageVisible(node_, &optCallback);

    EXPECT_EQ(checkEvent.has_value(), false);
    webEventHub->FireOnPageVisibleEvent(std::make_shared<PageVisibleEvent>(url));
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->resourceId, contextId);
    EXPECT_EQ(checkEvent->url, url);
}

/*
 * @tc.name: onDataResubmittedTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, onDataResubmittedTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    RefPtr<DataResubmitted> handler = Referenced::MakeRefPtr<MockDataResubmitted>();

    struct CheckEvent {
        int32_t resourceId;
        DataResubmissionHandlerPeer* peer;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    static constexpr int32_t contextId = 123;
    auto checkCallback = [](const Ark_Int32 resourceId, const Ark_OnDataResubmittedEvent parameter) {
        checkEvent = CheckEvent{
            .resourceId = resourceId,
            .peer = parameter.handler,
        };
    };

    Callback_OnDataResubmittedEvent_Void arkCallback =
        Converter::ArkValue<Callback_OnDataResubmittedEvent_Void>(checkCallback, contextId);
    auto optCallback = Converter::ArkValue<Opt_Callback_OnDataResubmittedEvent_Void>(arkCallback);
    modifier_->setOnDataResubmitted(node_, &optCallback);

    EXPECT_EQ(checkEvent.has_value(), false);
    webEventHub->FireOnDataResubmittedEvent(std::make_shared<DataResubmittedEvent>(handler));
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->resourceId, contextId);
    EXPECT_EQ(checkEvent->peer->handler, handler);
    delete checkEvent->peer;
}

/*
 * @tc.name: onAudioStateChangedTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, onAudioStateChangedTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    bool playing = true;

    struct CheckEvent {
        int32_t resourceId;
        bool playing;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    static constexpr int32_t contextId = 123;
    auto checkCallback = [](const Ark_Int32 resourceId, const Ark_OnAudioStateChangedEvent parameter) {
        checkEvent = CheckEvent{
            .resourceId = resourceId,
            .playing = Converter::Convert<bool>(parameter.playing)
        };
    };

    Callback_OnAudioStateChangedEvent_Void arkCallback =
        Converter::ArkValue<Callback_OnAudioStateChangedEvent_Void>(checkCallback, contextId);
    auto optCallback = Converter::ArkValue<Opt_Callback_OnAudioStateChangedEvent_Void>(arkCallback);
    modifier_->setOnAudioStateChanged(node_, &optCallback);

    EXPECT_EQ(checkEvent.has_value(), false);
    webEventHub->FireOnAudioStateChangedEvent(std::make_shared<AudioStateChangedEvent>(playing));
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->resourceId, contextId);
    EXPECT_EQ(checkEvent->playing, playing);
}

/*
 * @tc.name: onFirstContentfulPaintTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, onFirstContentfulPaintTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    int64_t navigationStartTick = 1000;
    int64_t firstContentfulPaintMs = 4000;

    struct CheckEvent {
        int32_t resourceId;
        int64_t navigationStartTick;
        int64_t firstContentfulPaintMs;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    static constexpr int32_t contextId = 123;
    auto checkCallback = [](const Ark_Int32 resourceId, const Ark_OnFirstContentfulPaintEvent parameter) {
        checkEvent = CheckEvent{
            .resourceId = resourceId,
            .navigationStartTick = Converter::Convert<int64_t>(parameter.navigationStartTick),
            .firstContentfulPaintMs = Converter::Convert<int64_t>(parameter.firstContentfulPaintMs)
        };
    };

    Callback_OnFirstContentfulPaintEvent_Void arkCallback =
        Converter::ArkValue<Callback_OnFirstContentfulPaintEvent_Void>(checkCallback, contextId);
    auto optCallback = Converter::ArkValue<Opt_Callback_OnFirstContentfulPaintEvent_Void>(arkCallback);
    modifier_->setOnFirstContentfulPaint(node_, &optCallback);

    EXPECT_EQ(checkEvent.has_value(), false);
    webEventHub->FireOnFirstContentfulPaintEvent(std::make_shared<FirstContentfulPaintEvent>(
        navigationStartTick, firstContentfulPaintMs));
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->navigationStartTick, navigationStartTick);
    EXPECT_EQ(checkEvent->firstContentfulPaintMs, firstContentfulPaintMs);
}

/*
 * @tc.name: onFirstMeaningfulPaintTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, onFirstMeaningfulPaintTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    int64_t navigationStartTime = 1000;
    int64_t firstMeaningfulPaintTime = 4000;

    struct CheckEvent {
        int32_t resourceId;
        int64_t navigationStartTime;
        int64_t firstMeaningfulPaintTime;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    static constexpr int32_t contextId = 123;
    auto checkCallback = [](const Ark_Int32 resourceId, const Ark_FirstMeaningfulPaint parameter) {
        checkEvent = CheckEvent{
            .resourceId = resourceId,
            .navigationStartTime = Converter::OptConvert<int64_t>(parameter.navigationStartTime)
                .value_or(0),
            .firstMeaningfulPaintTime = Converter::OptConvert<int64_t>(parameter.firstMeaningfulPaintTime)
                .value_or(0)
        };
    };

    OnFirstMeaningfulPaintCallback arkCallback =
        Converter::ArkValue<OnFirstMeaningfulPaintCallback>(checkCallback, contextId);
    auto optCallback = Converter::ArkValue<Opt_OnFirstMeaningfulPaintCallback>(arkCallback);
    modifier_->setOnFirstMeaningfulPaint(node_, &optCallback);

    EXPECT_EQ(checkEvent.has_value(), false);
    webEventHub->FireOnFirstMeaningfulPaintEvent(std::make_shared<FirstMeaningfulPaintEvent>(
        navigationStartTime, firstMeaningfulPaintTime));
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->navigationStartTime, navigationStartTime);
    EXPECT_EQ(checkEvent->firstMeaningfulPaintTime, firstMeaningfulPaintTime);
}

/*
 * @tc.name: onLargestContentfulPaintTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, onLargestContentfulPaintTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    int64_t navigationStartTime = 5000;
    int64_t largestImagePaintTime = 6000;
    int64_t largestTextPaintTime = 7000;
    int64_t largestImageLoadStartTime = 8000;
    int64_t largestImageLoadEndTime = 9000;
    double_t imageBPP = 5.5;

    struct CheckEvent {
        int32_t resourceId;
        int64_t navigationStartTime;
        int64_t largestImagePaintTime;
        int64_t largestTextPaintTime;
        int64_t largestImageLoadStartTime;
        int64_t largestImageLoadEndTime;
        double_t imageBPP;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    static constexpr int32_t contextId = 123;
    auto checkCallback = [](const Ark_Int32 resourceId, const Ark_LargestContentfulPaint parameter) {
        checkEvent = CheckEvent{
            .resourceId = resourceId,
            .navigationStartTime = Converter::OptConvert<int64_t>(parameter.navigationStartTime).value_or(0),
            .largestImagePaintTime = Converter::OptConvert<int64_t>(parameter.largestImagePaintTime).value_or(0),
            .largestTextPaintTime = Converter::OptConvert<int64_t>(parameter.largestTextPaintTime).value_or(0),
            .largestImageLoadStartTime = Converter::OptConvert<int64_t>(parameter.largestImageLoadStartTime)
                .value_or(0),
            .largestImageLoadEndTime = Converter::OptConvert<int64_t>(parameter.largestImageLoadEndTime).value_or(0),
            .imageBPP = Converter::OptConvert<float>(parameter.imageBPP).value_or(2)
        };
    };

    auto arkCallback = Converter::ArkValue<OnLargestContentfulPaintCallback>(checkCallback, contextId);
    auto optCallback = Converter::ArkValue<Opt_OnLargestContentfulPaintCallback>(arkCallback);
    modifier_->setOnLargestContentfulPaint(node_, &optCallback);

    EXPECT_EQ(checkEvent.has_value(), false);
    webEventHub->FireOnLargestContentfulPaintEvent(std::make_shared<LargestContentfulPaintEvent>(navigationStartTime,
        largestImagePaintTime, largestTextPaintTime, largestImageLoadStartTime, largestImageLoadEndTime, imageBPP));
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->navigationStartTime, navigationStartTime);
    EXPECT_EQ(checkEvent->largestImagePaintTime, largestImagePaintTime);
    EXPECT_EQ(checkEvent->largestTextPaintTime, largestTextPaintTime);
    EXPECT_EQ(checkEvent->largestImageLoadStartTime, largestImageLoadStartTime);
    EXPECT_EQ(checkEvent->largestImageLoadEndTime, largestImageLoadEndTime);
    EXPECT_DOUBLE_EQ(checkEvent->imageBPP, imageBPP);
}

/*
 * @tc.name: onLoadInterceptTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, onLoadInterceptTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    std::map<std::string, std::string> headers = {};
    std::string method = "method";
    std::string url = "url";
    bool hasGesture = true;
    bool isMainFrame = true;
    bool isRedirect = true;
    RefPtr<WebRequest> webRequest = Referenced::MakeRefPtr<WebRequest>(
        headers, method, url, hasGesture, isMainFrame, isRedirect);

    struct CheckEvent {
        int32_t resourceId;
        WebResourceRequestPeer* peer;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    static constexpr int32_t contextId = 123;
    static auto callResult = false;
    auto checkCallback = [](Ark_VMContext context, const Ark_Int32 resourceId,
        const Ark_OnLoadInterceptEvent parameter, const Callback_Boolean_Void continuation) {
        checkEvent = CheckEvent{
            .resourceId = resourceId,
            .peer = parameter.data,
        };
        CallbackHelper(continuation).InvokeSync(Converter::ArkValue<Ark_Boolean>(callResult));
    };

    Callback_OnLoadInterceptEvent_Boolean arkCallback =
        Converter::ArkValue<Callback_OnLoadInterceptEvent_Boolean>(nullptr, checkCallback, contextId);
    auto optCallback = Converter::ArkValue<Opt_Callback_OnLoadInterceptEvent_Boolean>(arkCallback);
    modifier_->setOnLoadIntercept(node_, &optCallback);

    EXPECT_FALSE(checkEvent.has_value());
    const auto event = webEventHub->GetOnLoadInterceptEvent();
    ASSERT_NE(event, nullptr);
    EXPECT_FALSE(event(std::make_shared<LoadInterceptEvent>(webRequest)));
    EXPECT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->resourceId, contextId);
    EXPECT_EQ(checkEvent->peer->webRequest, webRequest);
    delete checkEvent->peer;
    callResult = true;
    EXPECT_TRUE(event(std::make_shared<LoadInterceptEvent>(webRequest)));
    delete checkEvent->peer;
}

/*
 * @tc.name: onControllerAttachedTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, onControllerAttachedTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto webPattern = frameNode->GetPattern<WebPattern>();

    struct CheckEvent {
        int32_t resourceId;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    static constexpr int32_t contextId = 123;
    auto checkCallback = [](const Ark_Int32 resourceId) {
        checkEvent = CheckEvent{
            .resourceId = resourceId
        };
    };

    Callback_Void arkCallback =
        Converter::ArkValue<Callback_Void>(checkCallback, contextId);
    auto optCallback = Converter::ArkValue<Opt_Callback_Void>(arkCallback);
    modifier_->setOnControllerAttached(node_, &optCallback);

    EXPECT_EQ(checkEvent.has_value(), false);
    auto callback = webPattern->GetOnControllerAttachedCallback();
    callback();
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->resourceId, contextId);
}

} // namespace OHOS::Ace::NG
