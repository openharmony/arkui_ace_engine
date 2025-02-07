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
#include "core/interfaces/native/implementation/event_result_peer_impl.h"
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
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "test/unittest/capi/stubs/mock_web_entities.h"
#include "test/unittest/capi/stubs/mock_web_pattern.h"
#include "arkoala_api_generated.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::NG::Converter;

namespace OHOS::Ace::NG {

class WebModifierTest2 : public ModifierTestBase<GENERATED_ArkUIWebModifier,
    &GENERATED_ArkUINodeModifiers::getWebModifier, GENERATED_ARKUI_WEB> {
};

/*
 * @tc.name: onOverScrollTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest2, onOverScrollTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto webEventHub = frameNode->GetEventHub<WebEventHub>();
    double xOffset = 6.6f;
    double yOffset = 8.9f;

    struct CheckEvent {
        int32_t resourceId;
        double xOffset;
        double yOffset;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    static constexpr int32_t contextId = 123;
    auto checkCallback = [](const Ark_Int32 resourceId, const Ark_OnOverScrollEvent parameter) {
        checkEvent = {
            .resourceId = resourceId,
            .xOffset = static_cast<double>(Converter::Convert<float>(parameter.xOffset)),
            .yOffset = static_cast<double>(Converter::Convert<float>(parameter.yOffset))
        };
    };

    Callback_OnOverScrollEvent_Void arkCallback =
        Converter::ArkValue<Callback_OnOverScrollEvent_Void>(checkCallback, contextId);

    modifier_->setOnOverScroll(node_, &arkCallback);

    EXPECT_EQ(checkEvent.has_value(), false);
    webEventHub->FireOnOverScrollEvent(std::make_shared<WebOnOverScrollEvent>(xOffset, yOffset));
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->resourceId, contextId);
    EXPECT_NEAR(checkEvent->xOffset, xOffset, FLT_EPSILON);
    EXPECT_NEAR(checkEvent->yOffset, yOffset, FLT_EPSILON);
}

/*
 * @tc.name: onSafeBrowsingCheckResultTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest2, onSafeBrowsingCheckResultTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto webEventHub = frameNode->GetEventHub<WebEventHub>();
    ThreatType type = ThreatType::RISK;

    struct CheckEvent {
        int32_t resourceId;
        ThreatType type;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    static constexpr int32_t contextId = 123;
    auto checkCallback = [](const Ark_Int32 resourceId, const Ark_ThreatType parameter) {
        checkEvent = {
            .resourceId = resourceId,
            .type = Converter::OptConvert<ThreatType>(parameter).value_or(ThreatType::ILLEGAL)
        };
    };

    OnSafeBrowsingCheckResultCallback arkCallback =
        Converter::ArkValue<OnSafeBrowsingCheckResultCallback>(checkCallback, contextId);

    modifier_->setOnSafeBrowsingCheckResult(node_, &arkCallback);

    EXPECT_EQ(checkEvent.has_value(), false);
    webEventHub->FireOnSafeBrowsingCheckResultEvent(
        std::make_shared<SafeBrowsingCheckResultEvent>(static_cast<int>(type)));
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->resourceId, contextId);
    EXPECT_EQ(checkEvent->type, type);
}

/*
 * @tc.name: onNavigationEntryCommittedTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest2, onNavigationEntryCommittedTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto webEventHub = frameNode->GetEventHub<WebEventHub>();
    std::string url = "url";
    NavigationType type = NavigationType::NAVIGATION_TYPE_NEW_SUBFRAME;
    bool isMainFrame = true;
    bool isSameDocument = true;
    bool didReplaceEntry = true;

    struct CheckEvent {
        int32_t resourceId;
        std::string url;
        NavigationType type;
        bool isMainFrame;
        bool isSameDocument;
        bool didReplaceEntry;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    static constexpr int32_t contextId = 123;
    auto checkCallback = [](const Ark_Int32 resourceId, const Ark_LoadCommittedDetails data) {
        checkEvent = {
            .resourceId = resourceId,
            .url = Converter::Convert<std::string>(data.url),
            .type = Converter::OptConvert<NavigationType>(data.navigationType)
                .value_or(NavigationType::NAVIGATION_TYPE_UNKNOWN),
            .isMainFrame = Converter::Convert<bool>(data.isMainFrame),
            .isSameDocument = Converter::Convert<bool>(data.isSameDocument),
            .didReplaceEntry = Converter::Convert<bool>(data.didReplaceEntry)
        };
    };

    OnNavigationEntryCommittedCallback arkCallback =
        Converter::ArkValue<OnNavigationEntryCommittedCallback>(checkCallback, contextId);

    modifier_->setOnNavigationEntryCommitted(node_, &arkCallback);

    EXPECT_EQ(checkEvent.has_value(), false);
    webEventHub->FireOnNavigationEntryCommittedEvent(
        std::make_shared<NavigationEntryCommittedEvent>(url, type, isMainFrame, isSameDocument, didReplaceEntry));
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->resourceId, contextId);
    EXPECT_EQ(checkEvent->url, url);
    EXPECT_EQ(checkEvent->type, type);
    EXPECT_EQ(checkEvent->isMainFrame, isMainFrame);
    EXPECT_EQ(checkEvent->isSameDocument, isSameDocument);
    EXPECT_EQ(checkEvent->didReplaceEntry, didReplaceEntry);
}

/*
 * @tc.name: onIntelligentTrackingPreventionResultTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest2, onIntelligentTrackingPreventionResultTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto webEventHub = frameNode->GetEventHub<WebEventHub>();
    std::string host = "host";
    std::string trackerHost = "trackerHost";

    struct CheckEvent {
        int32_t resourceId;
        std::string host;
        std::string trackerHost;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    static constexpr int32_t contextId = 123;
    auto checkCallback = [](const Ark_Int32 resourceId, const Ark_IntelligentTrackingPreventionDetails data) {
        checkEvent = {
            .resourceId = resourceId,
            .host = Converter::Convert<std::string>(data.host),
            .trackerHost = Converter::Convert<std::string>(data.trackerHost)
        };
    };

    OnIntelligentTrackingPreventionCallback arkCallback =
        Converter::ArkValue<OnIntelligentTrackingPreventionCallback>(checkCallback, contextId);

    modifier_->setOnIntelligentTrackingPreventionResult(node_, &arkCallback);

    EXPECT_EQ(checkEvent.has_value(), false);
    webEventHub->FireOnIntelligentTrackingPreventionResultEvent(
        std::make_shared<IntelligentTrackingPreventionResultEvent>(host, trackerHost));
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->resourceId, contextId);
    EXPECT_EQ(checkEvent->host, host);
    EXPECT_EQ(checkEvent->trackerHost, trackerHost);
}

/*
 * @tc.name: onNativeEmbedVisibilityChangeTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest2, onNativeEmbedVisibilityChangeTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto webEventHub = frameNode->GetEventHub<WebEventHub>();
    bool visibility = true;
    std::string embedId = "embed_id";

    struct CheckEvent {
        int32_t resourceId;
        bool visibility;
        std::string embedId;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    static constexpr int32_t contextId = 123;
    auto checkCallback = [](const Ark_Int32 resourceId, const Ark_NativeEmbedVisibilityInfo data) {
        checkEvent = {
            .resourceId = resourceId,
            .embedId = Converter::Convert<std::string>(data.embedId),
            .visibility = Converter::Convert<bool>(data.visibility)
        };
    };

    OnNativeEmbedVisibilityChangeCallback arkCallback =
        Converter::ArkValue<OnNativeEmbedVisibilityChangeCallback>(checkCallback, contextId);

    modifier_->setOnNativeEmbedVisibilityChange(node_, &arkCallback);

    EXPECT_EQ(checkEvent.has_value(), false);
    webEventHub->FireOnNativeEmbedVisibilityChangeEvent(std::make_shared<NativeEmbedVisibilityInfo>(
        visibility, embedId));
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->resourceId, contextId);
    EXPECT_EQ(checkEvent->visibility, visibility);
    EXPECT_EQ(checkEvent->embedId, embedId);
}

/*
 * @tc.name: onOverrideUrlLoadingTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest2, onOverrideUrlLoadingTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto webEventHub = frameNode->GetEventHub<WebEventHub>();
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
    auto checkCallback = [](const Ark_Int32 resourceId,
        const Ark_WebResourceRequest parameter, const Callback_Boolean_Void continuation) {
        checkEvent = {
            .resourceId = resourceId,
            .peer = reinterpret_cast<WebResourceRequestPeer*>(parameter.ptr)
        };
    };

    OnOverrideUrlLoadingCallback arkCallback =
        Converter::ArkValue<OnOverrideUrlLoadingCallback>(checkCallback, contextId);

    modifier_->setOnOverrideUrlLoading(node_, &arkCallback);

    EXPECT_EQ(checkEvent.has_value(), false);
    webEventHub->FireOnOverrideUrlLoadingEvent(std::make_shared<LoadOverrideEvent>(webRequest));
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->resourceId, contextId);
    EXPECT_EQ(checkEvent->peer->webRequest, webRequest);
    delete checkEvent->peer;
}

/*
 * @tc.name: onRenderProcessNotRespondingTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest2, onRenderProcessNotRespondingTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto webEventHub = frameNode->GetEventHub<WebEventHub>();
    std::string jsStack = "jsStack";
    int pid = 5;
    RenderProcessNotRespondingReason reason = RenderProcessNotRespondingReason::NAVIGATION_COMMIT_TIMEOUT;

    struct CheckEvent {
        int32_t resourceId;
        std::string jsStack;
        int pid;
        RenderProcessNotRespondingReason reason;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    static constexpr int32_t contextId = 123;
    auto checkCallback = [](const Ark_Int32 resourceId, const Ark_RenderProcessNotRespondingData data) {
        checkEvent = {
            .resourceId = resourceId,
            .jsStack = Converter::Convert<std::string>(data.jsStack),
            .pid = Converter::Convert<int>(data.pid),
            .reason = Converter::OptConvert<RenderProcessNotRespondingReason>(data.reason)
                .value_or(RenderProcessNotRespondingReason::INPUT_TIMEOUT)
        };
    };

    OnRenderProcessNotRespondingCallback arkCallback =
        Converter::ArkValue<OnRenderProcessNotRespondingCallback>(checkCallback, contextId);

    modifier_->setOnRenderProcessNotResponding(node_, &arkCallback);

    EXPECT_EQ(checkEvent.has_value(), false);
    webEventHub->FireOnRenderProcessNotRespondingEvent(std::make_shared<RenderProcessNotRespondingEvent>(
        jsStack, pid, static_cast<int>(reason)));
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->resourceId, contextId);
    EXPECT_EQ(checkEvent->jsStack, jsStack);
    EXPECT_EQ(checkEvent->pid, pid);
    EXPECT_EQ(checkEvent->reason, reason);
}

/*
 * @tc.name: onRenderProcessRespondingTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest2, onRenderProcessRespondingTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto webEventHub = frameNode->GetEventHub<WebEventHub>();
    std::string type = "onRenderProcessResponding";

    struct CheckEvent {
        int32_t resourceId;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    static constexpr int32_t contextId = 123;
    auto checkCallback = [](const Ark_Int32 resourceId) {
        checkEvent = {
            .resourceId = resourceId
        };
    };

    OnRenderProcessRespondingCallback arkCallback =
        Converter::ArkValue<OnRenderProcessRespondingCallback>(checkCallback, contextId);

    modifier_->setOnRenderProcessResponding(node_, &arkCallback);

    EXPECT_EQ(checkEvent.has_value(), false);
    webEventHub->FireOnRenderProcessRespondingEvent(std::make_shared<BaseEventInfo>(type));
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->resourceId, contextId);
}

/*
 * @tc.name: onViewportFitChangedTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest2, onViewportFitChangedTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto webEventHub = frameNode->GetEventHub<WebEventHub>();
    ViewportFit viewportFit = ViewportFit::CONTAINS;

    struct CheckEvent {
        int32_t resourceId;
        ViewportFit viewportFit;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    static constexpr int32_t contextId = 123;
    auto checkCallback = [](const Ark_Int32 resourceId, const Ark_ViewportFit parameter) {
        checkEvent = {
            .resourceId = resourceId,
            .viewportFit = Converter::OptConvert<ViewportFit>(parameter).value_or(ViewportFit::AUTO),
        };
    };

    OnViewportFitChangedCallback arkCallback =
        Converter::ArkValue<OnViewportFitChangedCallback>(checkCallback, contextId);

    modifier_->setOnViewportFitChanged(node_, &arkCallback);

    EXPECT_EQ(checkEvent.has_value(), false);
    webEventHub->FireOnViewportFitChangedEvent(std::make_shared<ViewportFitChangedEvent>(
        static_cast<int32_t>(viewportFit)));
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->resourceId, contextId);
    EXPECT_EQ(checkEvent->viewportFit, viewportFit);
}

/*
 * @tc.name: onInterceptKeyboardAttachTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest2, onInterceptKeyboardAttachTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto webEventHub = frameNode->GetEventHub<WebEventHub>();
    RefPtr<WebCustomKeyboardHandler> customKeyboardHandler = Referenced::MakeRefPtr<MockWebCustomKeyboardHandler>();
    std::map<std::string, std::string> attributes = {{"key1", "value1"}, {"key2", "value2"}};

    struct CheckEvent {
        int32_t resourceId;
        WebKeyboardControllerPeer* peer;
        std::map<std::string, std::string> attributes;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    static constexpr int32_t contextId = 123;
    auto checkCallback = [](const Ark_Int32 resourceId, const Ark_WebKeyboardCallbackInfo parameter,
        const Callback_WebKeyboardOptions_Void continuation) {
        checkEvent = {
            .resourceId = resourceId,
            .peer = reinterpret_cast<WebKeyboardControllerPeer*>(parameter.controller.ptr),
            .attributes = Converter::Convert<std::map<std::string, std::string>>(parameter.attributes)
        };
    };

    WebKeyboardCallback arkCallback = Converter::ArkValue<WebKeyboardCallback>(checkCallback, contextId);

    modifier_->setOnInterceptKeyboardAttach(node_, &arkCallback);

    EXPECT_EQ(checkEvent.has_value(), false);
    webEventHub->FireOnInterceptKeyboardAttachEvent(std::make_shared<InterceptKeyboardEvent>(
        customKeyboardHandler, attributes));
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->resourceId, contextId);
    EXPECT_EQ(checkEvent->peer->handler, customKeyboardHandler);
    EXPECT_EQ(checkEvent->attributes, attributes);
    delete checkEvent->peer;
}

/*
 * @tc.name: onAdsBlockedTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest2, onAdsBlockedTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto webEventHub = frameNode->GetEventHub<WebEventHub>();
    std::string url = "url";
    std::vector<std::string> adsBlocked = { "item1", "item2" };

    struct CheckEvent {
        int32_t resourceId;
        std::string url;
        std::vector<std::string> adsBlocked;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    static constexpr int32_t contextId = 123;
    auto checkCallback = [](const Ark_Int32 resourceId, const Ark_AdsBlockedDetails parameter) {
        checkEvent = {
            .resourceId = resourceId,
            .url = Converter::Convert<std::string>(parameter.url),
            .adsBlocked = Converter::Convert<std::vector<std::string>>(parameter.adsBlocked)
        };
    };

    OnAdsBlockedCallback arkCallback = Converter::ArkValue<OnAdsBlockedCallback>(checkCallback, contextId);

    modifier_->setOnAdsBlocked(node_, &arkCallback);

    EXPECT_EQ(checkEvent.has_value(), false);
    webEventHub->FireOnAdsBlockedEvent(std::make_shared<AdsBlockedEvent>(url, adsBlocked));
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->resourceId, contextId);
    EXPECT_EQ(checkEvent->url, url);
    EXPECT_EQ(checkEvent->adsBlocked, adsBlocked);
}

} // namespace OHOS::Ace::NG