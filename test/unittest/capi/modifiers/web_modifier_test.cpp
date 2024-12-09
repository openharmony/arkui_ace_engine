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
#include "core/interfaces/native/implementation/js_geolocation_peer_impl.h"
#include "core/interfaces/native/implementation/js_result_peer_impl.h"
#include "core/interfaces/native/implementation/web_controller_peer_impl.h"
#include "core/interfaces/native/implementation/web_resource_error_peer_impl.h"
#include "core/interfaces/native/implementation/web_resource_request_peer_impl.h"
#include "core/interfaces/native/implementation/web_resource_response_peer_impl.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "test/unittest/capi/stubs/mock_web_entities.h"
#include "test/unittest/capi/stubs/mock_web_pattern.h"
#include "arkoala_api_generated.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class WebModifierTest : public ModifierTestBase<GENERATED_ArkUIWebModifier,
    &GENERATED_ArkUINodeModifiers::getWebModifier, GENERATED_ARKUI_WEB> {
};

/*
 * @tc.name: setOptionsWebControllerTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
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

    Ark_WebController arkController;
    arkController.ptr = controllerPtr;
    options.controller =
        Converter::ArkUnion<Ark_Union_WebController_WebviewController, Ark_WebController>(arkController);

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

/*
 * @tc.name: onPageEndTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, onPageEndTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto webEventHub = frameNode->GetEventHub<WebEventHub>();
    std::string url = "url";

    struct CheckEvent {
        int32_t resourceId;
        std::string url;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    static constexpr int32_t contextId = 123;
    auto checkCallback = [](const Ark_Int32 resourceId, const Ark_OnPageEndEvent parameter) {
        checkEvent = {
            .resourceId = resourceId,
            .url = Converter::Convert<std::string>(parameter.url)
        };
    };

    Callback_OnPageEndEvent_Void arkCallback =
        Converter::ArkValue<Callback_OnPageEndEvent_Void>(checkCallback, contextId);

    modifier_->setOnPageEnd(node_, &arkCallback);

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
    auto webEventHub = frameNode->GetEventHub<WebEventHub>();
    std::string url = "url";

    struct CheckEvent {
        int32_t resourceId;
        std::string url;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    static constexpr int32_t contextId = 123;
    auto checkCallback = [](const Ark_Int32 resourceId, const Ark_OnPageBeginEvent parameter) {
        checkEvent = {
            .resourceId = resourceId,
            .url = Converter::Convert<std::string>(parameter.url)
        };
    };

    Callback_OnPageBeginEvent_Void arkCallback =
        Converter::ArkValue<Callback_OnPageBeginEvent_Void>(checkCallback, contextId);

    modifier_->setOnPageBegin(node_, &arkCallback);

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
    auto webEventHub = frameNode->GetEventHub<WebEventHub>();
    int32_t newProgress = 99;

    struct CheckEvent {
        int32_t resourceId;
        int32_t progress;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    static constexpr int32_t contextId = 123;
    auto checkCallback = [](const Ark_Int32 resourceId, const Ark_OnProgressChangeEvent parameter) {
        checkEvent = {
            .resourceId = resourceId,
            .progress = Converter::Convert<int32_t>(parameter.newProgress)
        };
    };

    Callback_OnProgressChangeEvent_Void arkCallback =
        Converter::ArkValue<Callback_OnProgressChangeEvent_Void>(checkCallback, contextId);

    modifier_->setOnProgressChange(node_, &arkCallback);

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
    auto webEventHub = frameNode->GetEventHub<WebEventHub>();
    std::string title = "title";

    struct CheckEvent {
        int32_t resourceId;
        std::string title;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    static constexpr int32_t contextId = 123;
    auto checkCallback = [](const Ark_Int32 resourceId, const Ark_OnTitleReceiveEvent parameter) {
        checkEvent = {
            .resourceId = resourceId,
            .title = Converter::Convert<std::string>(parameter.title)
        };
    };

    Callback_OnTitleReceiveEvent_Void arkCallback =
        Converter::ArkValue<Callback_OnTitleReceiveEvent_Void>(checkCallback, contextId);

    modifier_->setOnTitleReceive(node_, &arkCallback);

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
    auto webEventHub = frameNode->GetEventHub<WebEventHub>();
    std::string origin = "origin";

    struct CheckEvent {
        int32_t resourceId;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    static constexpr int32_t contextId = 123;
    auto checkCallback = [](const Ark_Int32 resourceId) {
        checkEvent = {
            .resourceId = resourceId,
        };
    };

    Callback_Void arkCallback =
        Converter::ArkValue<Callback_Void>(checkCallback, contextId);

    modifier_->setOnGeolocationHide(node_, &arkCallback);

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
    auto webEventHub = frameNode->GetEventHub<WebEventHub>();
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
        checkEvent = {
            .resourceId = resourceId,
            .origin = Converter::Convert<std::string>(parameter.origin),
            .peer = reinterpret_cast<JsGeolocationPeer*>(parameter.geolocation.ptr)
        };
    };

    Callback_OnGeolocationShowEvent_Void arkCallback =
        Converter::ArkValue<Callback_OnGeolocationShowEvent_Void>(checkCallback, contextId);

    modifier_->setOnGeolocationShow(node_, &arkCallback);

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
    auto webEventHub = frameNode->GetEventHub<WebEventHub>();
    std::string type = "onRequestSelected";

    struct CheckEvent {
        int32_t resourceId;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    static constexpr int32_t contextId = 123;
    auto checkCallback = [](const Ark_Int32 resourceId) {
        checkEvent = {
            .resourceId = resourceId,
        };
    };

    Callback_Void arkCallback =
        Converter::ArkValue<Callback_Void>(checkCallback, contextId);

    modifier_->setOnRequestSelected(node_, &arkCallback);

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
    auto webEventHub = frameNode->GetEventHub<WebEventHub>();
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
    auto checkCallback = [](const Ark_Int32 resourceId, const Ark_OnAlertEvent parameter,
        const Callback_Boolean_Void continuation) {
        checkEvent = {
            .resourceId = resourceId,
            .url = Converter::Convert<std::string>(parameter.url),
            .message = Converter::Convert<std::string>(parameter.message),
            .peer = reinterpret_cast<JsResultPeer*>(parameter.result.ptr)
        };
    };

    Callback_OnAlertEvent_Boolean arkCallback =
        Converter::ArkValue<Callback_OnAlertEvent_Boolean>(checkCallback, contextId);

    modifier_->setOnAlert(node_, &arkCallback);

    EXPECT_EQ(checkEvent.has_value(), false);
    webEventHub->FireOnCommonDialogEvent(std::make_shared<WebDialogEvent>(url, message, value, type, result), type);
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->resourceId, contextId);
    EXPECT_EQ(checkEvent->url, url);
    EXPECT_EQ(checkEvent->message, message);
    EXPECT_EQ(checkEvent->peer->result, result);
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
    auto webEventHub = frameNode->GetEventHub<WebEventHub>();
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
    auto checkCallback = [](const Ark_Int32 resourceId, const Ark_OnBeforeUnloadEvent parameter,
        const Callback_Boolean_Void continuation) {
        checkEvent = {
            .resourceId = resourceId,
            .url = Converter::Convert<std::string>(parameter.url),
            .message = Converter::Convert<std::string>(parameter.message),
            .peer = reinterpret_cast<JsResultPeer*>(parameter.result.ptr)
        };
    };

    Callback_OnBeforeUnloadEvent_Boolean arkCallback =
        Converter::ArkValue<Callback_OnBeforeUnloadEvent_Boolean>(checkCallback, contextId);

    modifier_->setOnBeforeUnload(node_, &arkCallback);

    EXPECT_EQ(checkEvent.has_value(), false);
    webEventHub->FireOnCommonDialogEvent(std::make_shared<WebDialogEvent>(url, message, value, type, result), type);
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->resourceId, contextId);
    EXPECT_EQ(checkEvent->url, url);
    EXPECT_EQ(checkEvent->message, message);
    EXPECT_EQ(checkEvent->peer->result, result);
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
    auto webEventHub = frameNode->GetEventHub<WebEventHub>();
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
    auto checkCallback = [](const Ark_Int32 resourceId, const Ark_OnConfirmEvent parameter,
        const Callback_Boolean_Void continuation) {
        checkEvent = {
            .resourceId = resourceId,
            .url = Converter::Convert<std::string>(parameter.url),
            .message = Converter::Convert<std::string>(parameter.message),
            .peer = reinterpret_cast<JsResultPeer*>(parameter.result.ptr)
        };
    };

    Callback_OnConfirmEvent_Boolean arkCallback =
        Converter::ArkValue<Callback_OnConfirmEvent_Boolean>(checkCallback, contextId);

    modifier_->setOnConfirm(node_, &arkCallback);

    EXPECT_EQ(checkEvent.has_value(), false);
    webEventHub->FireOnCommonDialogEvent(std::make_shared<WebDialogEvent>(url, message, value, type, result), type);
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->resourceId, contextId);
    EXPECT_EQ(checkEvent->url, url);
    EXPECT_EQ(checkEvent->message, message);
    EXPECT_EQ(checkEvent->peer->result, result);
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
    auto webEventHub = frameNode->GetEventHub<WebEventHub>();
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
    auto checkCallback = [](const Ark_Int32 resourceId, const Ark_OnPromptEvent parameter,
        const Callback_Boolean_Void continuation) {
        checkEvent = {
            .resourceId = resourceId,
            .url = Converter::Convert<std::string>(parameter.url),
            .message = Converter::Convert<std::string>(parameter.message),
            .peer = reinterpret_cast<JsResultPeer*>(parameter.result.ptr)
        };
    };

    Callback_OnPromptEvent_Boolean arkCallback =
        Converter::ArkValue<Callback_OnPromptEvent_Boolean>(checkCallback, contextId);

    modifier_->setOnPrompt(node_, &arkCallback);

    EXPECT_EQ(checkEvent.has_value(), false);
    webEventHub->FireOnCommonDialogEvent(std::make_shared<WebDialogEvent>(url, message, value, type, result), type);
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->resourceId, contextId);
    EXPECT_EQ(checkEvent->url, url);
    EXPECT_EQ(checkEvent->message, message);
    EXPECT_EQ(checkEvent->peer->result, result);
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
    auto webEventHub = frameNode->GetEventHub<WebEventHub>();
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
    auto checkCallback = [](const Ark_Int32 resourceId, const Ark_OnConsoleEvent parameter,
        const Callback_Boolean_Void continuation) {
        checkEvent = {
            .resourceId = resourceId,
            .peer = reinterpret_cast<ConsoleMessagePeer*>(parameter.message.ptr)
        };
    };

    Callback_OnConsoleEvent_Boolean arkCallback =
        Converter::ArkValue<Callback_OnConsoleEvent_Boolean>(checkCallback, contextId);

    modifier_->setOnConsole(node_, &arkCallback);

    EXPECT_EQ(checkEvent.has_value(), false);
    webEventHub->FireOnConsoleEvent(std::make_shared<LoadWebConsoleLogEvent>(param));
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->peer->webConsoleLog, param);
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
    auto webEventHub = frameNode->GetEventHub<WebEventHub>();
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
        checkEvent = {
            .resourceId = resourceId,
            .errorPeer = reinterpret_cast<WebResourceErrorPeer*>(parameter.error.ptr),
            .requestPeer = reinterpret_cast<WebResourceRequestPeer*>(parameter.request.ptr)
        };
    };

    Callback_OnErrorReceiveEvent_Void arkCallback =
        Converter::ArkValue<Callback_OnErrorReceiveEvent_Void>(checkCallback, contextId);

    modifier_->setOnErrorReceive(node_, &arkCallback);

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
    auto webEventHub = frameNode->GetEventHub<WebEventHub>();
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
        checkEvent = {
            .resourceId = resourceId,
            .responsePeer = reinterpret_cast<WebResourceResponsePeer*>(parameter.response.ptr),
            .requestPeer = reinterpret_cast<WebResourceRequestPeer*>(parameter.request.ptr)
        };
    };

    Callback_OnHttpErrorReceiveEvent_Void arkCallback =
        Converter::ArkValue<Callback_OnHttpErrorReceiveEvent_Void>(checkCallback, contextId);

    modifier_->setOnHttpErrorReceive(node_, &arkCallback);

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
    auto webEventHub = frameNode->GetEventHub<WebEventHub>();
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
        checkEvent = {
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

    modifier_->setOnDownloadStart(node_, &arkCallback);

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
    auto webEventHub = frameNode->GetEventHub<WebEventHub>();
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
        checkEvent = {
            .resourceId = resourceId,
            .url = Converter::Convert<std::string>(parameter.url),
            .isRefreshed = Converter::Convert<bool>(parameter.isRefreshed)
        };
    };

    Callback_OnRefreshAccessedHistoryEvent_Void arkCallback =
        Converter::ArkValue<Callback_OnRefreshAccessedHistoryEvent_Void>(checkCallback, contextId);

    modifier_->setOnRefreshAccessedHistory(node_, &arkCallback);

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
    auto webEventHub = frameNode->GetEventHub<WebEventHub>();
    std::string dataStr = "data";

    struct CheckEvent {
        int32_t resourceId;
        std::string data;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    static constexpr int32_t contextId = 123;
    auto checkCallback = [](const Ark_Int32 resourceId,
        const Opt_Literal_Union_String_WebResourceRequest_data parameter, const Callback_Boolean_Void continuation) {
        auto dataOpt = Converter::OptConvert<Ark_Literal_Union_String_WebResourceRequest_data>(parameter);
        if (dataOpt) {
            Converter::VisitUnion(dataOpt.value().data,
                [resourceId](const Ark_String& str) {
                    checkEvent = {
                        .resourceId = resourceId,
                        .data = Converter::Convert<std::string>(str)
                    };
                },
                [](const auto& value) {},
                []() {}
            );
        }
    };

    Type_WebAttribute_onUrlLoadIntercept_callback arkCallback =
        Converter::ArkValue<Type_WebAttribute_onUrlLoadIntercept_callback>(checkCallback, contextId);

    modifier_->setOnUrlLoadIntercept(node_, &arkCallback);

    EXPECT_EQ(checkEvent.has_value(), false);
    webEventHub->FireOnUrlLoadInterceptEvent(std::make_shared<UrlLoadInterceptEvent>(dataStr));
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->resourceId, contextId);
    EXPECT_EQ(checkEvent->data, dataStr);
}

} // namespace OHOS::Ace::NG
