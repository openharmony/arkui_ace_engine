/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/text_field/text_selector.h"

#ifdef WEB_SUPPORTED
#include "arkweb_utils.h"
#include "core/components_ng/pattern/web/ani/web_model_static.h"
#include "core/interfaces/native/implementation/webview_controller_peer_impl.h"
#include "core/interfaces/native/implementation/web_modifier_callbacks.h"
#include "core/interfaces/native/implementation/controller_handler_peer_impl.h"
#include "core/interfaces/native/generated/interface/arkoala_api_generated.h"
#endif // WEB_SUPPORTED
#include "core/interfaces/native/utility/ace_engine_types.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/callback_helper.h"

using namespace OHOS::Ace::NG::Converter;

namespace OHOS::Ace {
using ScriptItem = std::pair<std::string, std::vector<std::string>>;
namespace {
#ifdef WEB_SUPPORTED
constexpr Dimension PREVIEW_MENU_MARGIN_LEFT = 16.0_vp;
constexpr Dimension PREVIEW_MENU_MARGIN_RIGHT = 16.0_vp;

void EraseSpace(std::string& data)
{
    auto iter = data.begin();
    while (iter != data.end()) {
        if (isspace(*iter)) {
            iter = data.erase(iter);
        } else {
            ++iter;
        }
    }
}
const std::vector<double> BLANK_SCREEN_DETECTION_DEFAULT_TIMING = { 1.0, 3.0, 5.0 };
#endif // WEB_SUPPORTED
} // namespace
} // namespace OHOS::Ace

namespace OHOS::Ace::NG::Converter {
#ifdef WEB_SUPPORTED
template<>
ScriptItem Convert(const Ark_ScriptItem& src)
{
    ScriptItem item = std::make_pair(
        Converter::Convert<std::string>(src.script),
        Converter::Convert<std::vector<std::string>>(src.scriptRules)
    );
    return item;
}

template<>
ScriptItems Convert(const Array_ScriptItem& src)
{
    auto items = Converter::Convert<std::vector<ScriptItem>>(src);
    ScriptItems scriptItems;
    for (auto item : items) {
        if (scriptItems.find(item.first) == scriptItems.end()) {
            scriptItems.insert(item);
        }
    }
    return scriptItems;
}

template<>
ScriptItemsByOrder Convert(const Array_ScriptItem& src)
{
    auto items = Converter::Convert<std::vector<ScriptItem>>(src);
    ScriptItemsByOrder scriptItemsByOrder;
    std::unordered_set<std::string> temp;
    for (auto item : items) {

        if (temp.insert(item.first).second) {
            scriptItemsByOrder.push_back(item.first);
        }
    }
    return scriptItemsByOrder;
}

template<>
ScriptRegexItems Convert(const Array_ScriptItem& src)
{
    ScriptRegexItems scriptRegexItems;
    auto convScriptItem = Converter::OptConvert<std::vector<Ark_ScriptItem>>(src);
    if (!convScriptItem) {
        // Implement Reset value
        return scriptRegexItems;
    }
    for (auto scriptItem : *convScriptItem) {
        auto script = Converter::Convert<std::string>(scriptItem.script);
        std::vector<std::pair<std::string, std::string>> regexRules;
        auto urlRegexRules = Converter::OptConvert<std::vector<Ark_UrlRegexRule>>(scriptItem.urlRegexRules)
            .value_or(std::vector<Ark_UrlRegexRule>{});
        for (auto regexRule : urlRegexRules) {
            auto secondLevelDomain = Converter::Convert<std::string>(regexRule.secondLevelDomain);
            auto rule = Converter::Convert<std::string>(regexRule.rule);
            regexRules.push_back(std::make_pair(secondLevelDomain, rule));
        }
        if (scriptRegexItems.find(script) == scriptRegexItems.end()) {
            scriptRegexItems.insert(std::make_pair(script, regexRules));
        }
    }

    return scriptRegexItems;
}

template<>
NestedScrollOptionsExt Convert(const Ark_NestedScrollOptionsExt& src)
{
    NestedScrollOptionsExt nestedOpt = {
        .scrollUp = NestedScrollMode::SELF_FIRST,
        .scrollDown = NestedScrollMode::SELF_FIRST,
        .scrollLeft = NestedScrollMode::SELF_FIRST,
        .scrollRight = NestedScrollMode::SELF_FIRST,
    };
    nestedOpt.scrollDown = Converter::OptConvert<NestedScrollMode>(src.scrollDown).value_or(nestedOpt.scrollDown);
    nestedOpt.scrollRight = Converter::OptConvert<NestedScrollMode>(src.scrollRight).value_or(nestedOpt.scrollRight);
    nestedOpt.scrollUp = Converter::OptConvert<NestedScrollMode>(src.scrollUp).value_or(nestedOpt.scrollUp);
    nestedOpt.scrollLeft = Converter::OptConvert<NestedScrollMode>(src.scrollLeft).value_or(nestedOpt.scrollLeft);
    return nestedOpt;
}

template<>
NestedScrollOptionsExt Convert(const Ark_NestedScrollOptions& src)
{
    NestedScrollOptionsExt nestedOpt = {
        .scrollUp = NestedScrollMode::SELF_FIRST,
        .scrollDown = NestedScrollMode::SELF_FIRST,
        .scrollLeft = NestedScrollMode::SELF_FIRST,
        .scrollRight = NestedScrollMode::SELF_FIRST,
    };
    nestedOpt.scrollDown = Converter::OptConvert<NestedScrollMode>(src.scrollForward)
        .value_or(nestedOpt.scrollDown);
    nestedOpt.scrollRight = Converter::OptConvert<NestedScrollMode>(src.scrollForward)
        .value_or(nestedOpt.scrollRight);
    nestedOpt.scrollUp = Converter::OptConvert<NestedScrollMode>(src.scrollBackward)
        .value_or(nestedOpt.scrollUp);
    nestedOpt.scrollLeft = Converter::OptConvert<NestedScrollMode>(src.scrollBackward)
        .value_or(nestedOpt.scrollLeft);
    return nestedOpt;
}

#ifdef WRONG_SDK
template<>
MenuOptionsParam Convert(const Ark_ExpandedMenuItemOptions& src)
{
    MenuOptionsParam menuOption;
    menuOption.content = Converter::OptConvert<std::string>(src.content);
    menuOption.icon = Converter::OptConvert<std::string>(src.startIcon);
    return menuOption;
}
#endif

void AssignArkValue(Ark_NativeEmbedInfo& dst, const EmbedInfo& src)
{
    dst.width = Converter::ArkValue<Opt_Int32>(src.width);
    dst.height = Converter::ArkValue<Opt_Int32>(src.height);
    dst.id = Converter::ArkValue<Opt_String>(src.id);
    dst.src = Converter::ArkValue<Opt_String>(src.src);
    dst.tag = Converter::ArkValue<Opt_String>(src.tag);
    dst.type = Converter::ArkValue<Opt_String>(src.type);
    dst.url = Converter::ArkValue<Opt_String>(src.url);
    Ark_Position position;
    position.x = Converter::ArkValue<Opt_Length>((float)src.x);
    position.y = Converter::ArkValue<Opt_Length>((float)src.y);
    dst.position = Converter::ArkValue<Opt_Position>(position);
}

void AssignArkValue(Ark_WebNavigationType& dst, const NavigationType& src)
{
    switch (src) {
        case NavigationType::NAVIGATION_TYPE_UNKNOWN: dst =
            Ark_WebNavigationType::ARK_WEB_NAVIGATION_TYPE_UNKNOWN; break;
        case NavigationType::NAVIGATION_TYPE_MAIN_FRAME_NEW_ENTRY: dst =
            Ark_WebNavigationType::ARK_WEB_NAVIGATION_TYPE_MAIN_FRAME_NEW_ENTRY; break;
        case NavigationType::NAVIGATION_TYPE_MAIN_FRAME_EXISTING_ENTRY: dst =
            Ark_WebNavigationType::ARK_WEB_NAVIGATION_TYPE_MAIN_FRAME_EXISTING_ENTRY; break;
        case NavigationType::NAVIGATION_TYPE_NEW_SUBFRAME: dst =
            Ark_WebNavigationType::ARK_WEB_NAVIGATION_TYPE_NAVIGATION_TYPE_NEW_SUBFRAME; break;
        case NavigationType::NAVIGATION_TYPE_AUTO_SUBFRAME: dst =
            Ark_WebNavigationType::ARK_WEB_NAVIGATION_TYPE_NAVIGATION_TYPE_AUTO_SUBFRAME; break;
        default: dst = static_cast<Ark_WebNavigationType>(-1);
            LOGE("Unexpected enum value in NavigationType: %{public}d", src);
    }
}

void AssignArkValue(Ark_ViewportFit& dst, const ViewportFit& src)
{
    switch (src) {
        case ViewportFit::AUTO: dst = ARK_VIEWPORT_FIT_AUTO; break;
        case ViewportFit::CONTAINS: dst = ARK_VIEWPORT_FIT_CONTAINS; break;
        case ViewportFit::COVER: dst = ARK_VIEWPORT_FIT_COVER; break;
        default: dst = static_cast<Ark_ViewportFit>(-1);
            LOGE("Unexpected enum value in ViewportFit: %{public}d", src);
    }
}

void AssignArkValue(Ark_ThreatType& dst, const ThreatType& src)
{
    switch (src) {
        case ThreatType::ILLEGAL: dst = Ark_ThreatType::ARK_THREAT_TYPE_THREAT_ILLEGAL; break;
        case ThreatType::FRAUD: dst = Ark_ThreatType::ARK_THREAT_TYPE_THREAT_FRAUD; break;
        case ThreatType::RISK: dst = Ark_ThreatType::ARK_THREAT_TYPE_THREAT_RISK; break;
        case ThreatType::WARNING: dst = Ark_ThreatType::ARK_THREAT_TYPE_THREAT_WARNING; break;
        case ThreatType::NONE: dst = Ark_ThreatType::ARK_THREAT_TYPE_THREAT_NONE; break;
        case ThreatType::UNPROCESSED: dst = Ark_ThreatType::ARK_THREAT_TYPE_THREAT_UNPROCESSED; break;
        default: dst = static_cast<Ark_ThreatType>(-1);
            LOGE("Unexpected enum value in ThreatType: %{public}d", src);
    }
}
#endif // WEB_SUPPORTED
} // namespace OHOS::Ace::NG::Converter

namespace OHOS::Ace::NG::GeneratedModifier {
namespace WebModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
#ifdef WEB_SUPPORTED
    auto frameNode = WebModelStatic::CreateFrameNode(id);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
#else
    return {};
#endif // WEB_SUPPORTED
}
} // WebModifier
namespace WebInterfaceModifier {
void SetWebOptionsImpl(Ark_NativePointer node,
                       const Ark_WebOptions* value)
{
#ifdef WEB_SUPPORTED
    LOGI("SetWebOptionsImpl set options");
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto webSrc = Converter::OptConvert<std::string>(value->src);
    WebModelStatic::SetWebSrc(frameNode, webSrc);
    auto controller = value->controller;
    if (controller) {
        if (controller->getNativePtrFunc) {
            int32_t parentNWebId = -1;
            bool isPopup = ControllerHandlerPeer::ExistController(
                controller->getNativePtrFunc(), parentNWebId);
            WebModelStatic::SetPopup(frameNode, isPopup, parentNWebId);
        }
        WebModelStatic::SetWebIdCallback(frameNode, std::move(controller->setWebIdFunc));
        WebModelStatic::SetHapPathCallback(frameNode, std::move(controller->setHapPathFunc));
        WebModelStatic::SetWebDetachCallback(frameNode, std::move(controller->setWebDetachFunc));
        auto fileSelectorShowFromUserCallback = [callback = std::move(controller->defaultOnShowFileSelectorFunc),
                                                    weakNode = AceType::WeakClaim(frameNode),
                                                    instanceId = Container::CurrentId()](const BaseEventInfo* info) {
            WebAttributeModifier::DefaultOnShowFileSelector(std::move(callback), weakNode, instanceId, info);
        };
        WebModelStatic::SetDefaultFileSelectorShow(frameNode, std::move(fileSelectorShowFromUserCallback));
        auto requestPermissionsFromUserCallback = [callback = std::move(controller->defaultPermissionClipboardFunc),
                                                      weakNode = AceType::WeakClaim(frameNode),
                                                      instanceId = Container::CurrentId()](const BaseEventInfo* info) {
            WebAttributeModifier::DefaultPermissionClipboard(std::move(callback), weakNode, instanceId, info);
        };
        WebModelStatic::SetPermissionClipboard(frameNode, std::move(requestPermissionsFromUserCallback));
        /* This controller is only used to pass the hook function for initializing the webviewController.
         * After passing, the corresponding memory needs to be released.
         */
        delete controller;
    } else {
        LOGE("SetWebOptionsImpl controller is nullptr");
    }
    auto renderMode = Converter::OptConvert<RenderMode>(value->renderMode);
    WebModelStatic::SetRenderMode(frameNode, renderMode);
    auto incognitoMode = Converter::OptConvert<bool>(value->incognitoMode);
    WebModelStatic::SetIncognitoMode(frameNode, incognitoMode);
    auto sharedRenderProcessToken = Converter::OptConvert<std::string>(value->sharedRenderProcessToken);
    WebModelStatic::SetSharedRenderProcessToken(frameNode, sharedRenderProcessToken);
    auto emulateTouchFromMouseEvent = Converter::OptConvert<bool>(value->emulateTouchFromMouseEvent);
    WebModelStatic::SetEmulateTouchFromMouseEvent(frameNode, emulateTouchFromMouseEvent);
#endif // WEB_SUPPORTED
}
} // WebInterfaceModifier
namespace WebAttributeModifier {
void SetJavaScriptAccessImpl(Ark_NativePointer node,
                             const Opt_Boolean* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    if (!convValue) {
        // Implement Reset value
        return;
    }
    WebModelStatic::SetJsEnabled(frameNode, *convValue);
#endif // WEB_SUPPORTED
}
void SetFileAccessImpl(Ark_NativePointer node,
                       const Opt_Boolean* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    if (!convValue) {
        // Implement Reset value
        return;
    }
    WebModelStatic::SetFileAccessEnabled(frameNode, *convValue);
#endif // WEB_SUPPORTED
}
void SetOnlineImageAccessImpl(Ark_NativePointer node,
                              const Opt_Boolean* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    if (!convValue) {
        // Implement Reset value
        return;
    }
    WebModelStatic::SetOnLineImageAccessEnabled(frameNode, *convValue);
#endif // WEB_SUPPORTED
}
void SetDomStorageAccessImpl(Ark_NativePointer node,
                             const Opt_Boolean* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    if (!convValue) {
        // Implement Reset value
        return;
    }
    WebModelStatic::SetDomStorageAccessEnabled(frameNode, *convValue);
#endif // WEB_SUPPORTED
}
void SetImageAccessImpl(Ark_NativePointer node,
                        const Opt_Boolean* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    if (!convValue) {
        // Implement Reset value
        return;
    }
    WebModelStatic::SetImageAccessEnabled(frameNode, *convValue);
#endif // WEB_SUPPORTED
}
void SetMixedModeImpl(Ark_NativePointer node,
                      const Opt_MixedMode* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<MixedModeContent>(*value);
    WebModelStatic::SetMixedMode(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void SetZoomAccessImpl(Ark_NativePointer node,
                       const Opt_Boolean* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    if (!convValue) {
        // Implement Reset value
        return;
    }
    WebModelStatic::SetZoomAccessEnabled(frameNode, *convValue);
#endif // WEB_SUPPORTED
}
void SetGeolocationAccessImpl(Ark_NativePointer node,
                              const Opt_Boolean* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    if (!convValue) {
        // Implement Reset value
        return;
    }
    WebModelStatic::SetGeolocationAccessEnabled(frameNode, *convValue);
#endif // WEB_SUPPORTED
}
void SetJavaScriptProxyImpl(Ark_NativePointer node,
                            const Opt_JavaScriptProxy* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    LOGE("WebInterfaceModifier::JavaScriptProxyImpl method is not implemented");
}
void SetCacheModeImpl(Ark_NativePointer node,
                      const Opt_CacheMode* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<WebCacheMode>(*value);
    WebModelStatic::SetCacheMode(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void SetDarkModeImpl(Ark_NativePointer node,
                     const Opt_WebDarkMode* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<WebDarkMode>(*value);
    WebModelStatic::SetDarkMode(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void SetForceDarkAccessImpl(Ark_NativePointer node,
                            const Opt_Boolean* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    if (!convValue) {
        // Implement Reset value
        return;
    }
    WebModelStatic::SetForceDarkAccess(frameNode, *convValue);
#endif // WEB_SUPPORTED
}
void SetMediaOptionsImpl(Ark_NativePointer node,
                         const Opt_WebMediaOptions* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        return;
    }
    WebModelStatic::SetAudioResumeInterval(frameNode, Converter::OptConvert<int32_t>(optValue->resumeInterval));
    WebModelStatic::SetAudioExclusive(frameNode, Converter::OptConvert<bool>(optValue->audioExclusive));
    WebModelStatic::SetAudioSessionType(frameNode,
                                        Converter::OptConvert<WebAudioSessionType>(optValue->audioSessionType));
#endif // WEB_SUPPORTED
}
void SetOverviewModeAccessImpl(Ark_NativePointer node,
                               const Opt_Boolean* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    if (!convValue) {
        // Implement Reset value
        return;
    }
    WebModelStatic::SetOverviewModeAccessEnabled(frameNode, *convValue);
#endif // WEB_SUPPORTED
}
void SetOverScrollModeImpl(Ark_NativePointer node,
                           const Opt_OverScrollMode* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<OverScrollMode>(*value);
    WebModelStatic::SetOverScrollMode(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void SetBlurOnKeyboardHideModeImpl(Ark_NativePointer node,
                                   const Opt_BlurOnKeyboardHideMode* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<BlurOnKeyboardHideMode>(*value);
    WebModelStatic::SetBlurOnKeyboardHideMode(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void SetTextZoomRatioImpl(Ark_NativePointer node,
                          const Opt_Int32* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<int32_t>(*value);
    if (!convValue) {
        // Implement Reset value
        return;
    }
    WebModelStatic::SetTextZoomRatio(frameNode, *convValue);
#endif // WEB_SUPPORTED
}
void SetDatabaseAccessImpl(Ark_NativePointer node,
                           const Opt_Boolean* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    if (!convValue) {
        // Implement Reset value
        return;
    }
    WebModelStatic::SetDatabaseAccessEnabled(frameNode, *convValue);
#endif // WEB_SUPPORTED
}
void SetInitialScaleImpl(Ark_NativePointer node,
                         const Opt_Float64* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<float>(*value);
    if (!convValue) {
        // Implement Reset value
        return;
    }
    WebModelStatic::InitialScale(frameNode, *convValue);
#endif // WEB_SUPPORTED
}
void UserAgentImpl(Ark_NativePointer node,
                   const Opt_String* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<std::string>(*value);
    if (!convValue) {
        // Implement Reset value
        return;
    }
    WebModelStatic::SetUserAgent(frameNode, *convValue);
#endif // WEB_SUPPORTED
}
void SetMetaViewportImpl(Ark_NativePointer node,
                         const Opt_Boolean* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    if (!convValue) {
        // Implement Reset value
        return;
    }
    WebModelStatic::SetMetaViewport(frameNode, *convValue);
#endif // WEB_SUPPORTED
}
void SetOnPageEndImpl(Ark_NativePointer node,
                      const Opt_Callback_OnPageEndEvent_Void* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        return;
    }
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onPageEnd = [callback = CallbackHelper(*optValue), weakNode, instanceId](
        const BaseEventInfo* info) {
        OnPageEnd(callback, weakNode, instanceId, info);
    };
    WebModelStatic::SetOnPageFinish(frameNode, std::move(onPageEnd));
#endif // WEB_SUPPORTED
}
void SetOnPageBeginImpl(Ark_NativePointer node,
                        const Opt_Callback_OnPageBeginEvent_Void* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        return;
    }
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onPageBegin = [callback = CallbackHelper(*optValue), weakNode, instanceId](
        const BaseEventInfo* info) {
        OnPageBegin(callback, weakNode, instanceId, info);
    };
    WebModelStatic::SetOnPageStart(frameNode, onPageBegin);
#endif // WEB_SUPPORTED
}
void SetOnLoadStartedImpl(Ark_NativePointer node,
                          const Opt_Callback_OnLoadStartedEvent_Void* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        return;
    }
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onLoadStarted = [callback = CallbackHelper(*optValue), weakNode, instanceId](
        const BaseEventInfo* info) {
        OnLoadStarted(callback, weakNode, instanceId, info);
    };
    WebModelStatic::SetOnLoadStarted(frameNode, onLoadStarted);
#endif // WEB_SUPPORTED
}
void SetOnLoadFinishedImpl(Ark_NativePointer node,
                           const Opt_Callback_OnLoadFinishedEvent_Void* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        return;
    }
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onLoadFinished = [callback = CallbackHelper(*optValue), weakNode, instanceId](
        const BaseEventInfo* info) {
        OnLoadFinished(callback, weakNode, instanceId, info);
    };
    WebModelStatic::SetOnLoadFinished(frameNode, onLoadFinished);
#endif // WEB_SUPPORTED
}
void SetOnProgressChangeImpl(Ark_NativePointer node,
                             const Opt_Callback_OnProgressChangeEvent_Void* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        return;
    }
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onProgressChange = [callback = CallbackHelper(*optValue), weakNode, instanceId](
        const BaseEventInfo* info) {
        OnProgressChange(callback, weakNode, instanceId, info);
    };
    WebModelStatic::SetOnProgressChange(frameNode, onProgressChange);
#endif // WEB_SUPPORTED
}
void SetOnTitleReceiveImpl(Ark_NativePointer node,
                           const Opt_Callback_OnTitleReceiveEvent_Void* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        return;
    }
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onTitleReceive = [callback = CallbackHelper(*optValue), weakNode, instanceId](
        const BaseEventInfo* info) {
        OnTitleReceive(callback, weakNode, instanceId, info);
    };
    WebModelStatic::SetOnTitleReceive(frameNode, onTitleReceive);
#endif // WEB_SUPPORTED
}
void SetOnGeolocationHideImpl(Ark_NativePointer node,
                              const Opt_Callback_Void* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        return;
    }
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onGeolocationHide = [callback = CallbackHelper(*optValue), weakNode, instanceId](
        const BaseEventInfo* info) {
        OnGeolocationHide(callback, weakNode, instanceId, info);
    };
    WebModelStatic::SetOnGeolocationHide(frameNode, onGeolocationHide);
#endif // WEB_SUPPORTED
}
void SetOnGeolocationShowImpl(Ark_NativePointer node,
                              const Opt_Callback_OnGeolocationShowEvent_Void* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        return;
    }
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onGeolocationShow = [callback = CallbackHelper(*optValue), weakNode, instanceId](
        const BaseEventInfo* info) {
        OnGeolocationShow(callback, weakNode, instanceId, info);
    };
    WebModelStatic::SetOnGeolocationShow(frameNode, onGeolocationShow);
#endif // WEB_SUPPORTED
}
void SetOnRequestSelectedImpl(Ark_NativePointer node,
                              const Opt_Callback_Void* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        return;
    }
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onRequestSelected = [callback = CallbackHelper(*optValue), weakNode](
        const BaseEventInfo* info) {
        OnRequestSelected(callback, weakNode, info);
    };
    WebModelStatic::SetOnRequestFocus(frameNode, onRequestSelected);
#endif // WEB_SUPPORTED
}
void SetOnAlertImpl(Ark_NativePointer node,
                    const Opt_Callback_OnAlertEvent_Boolean* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        return;
    }
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onAlert = [callback = CallbackHelper(*optValue), weakNode, instanceId](
        const BaseEventInfo* info) -> bool {
        return OnAlert(callback, weakNode, instanceId, info);
    };
    WebModelStatic::SetOnCommonDialog(frameNode, onAlert, DialogEventType::DIALOG_EVENT_ALERT);
#endif // WEB_SUPPORTED
}
void SetOnBeforeUnloadImpl(Ark_NativePointer node,
                           const Opt_Callback_OnBeforeUnloadEvent_Boolean* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        return;
    }
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onBeforeUnload = [callback = CallbackHelper(*optValue), weakNode, instanceId](
        const BaseEventInfo* info) -> bool {
        return OnBeforeUnload(callback, weakNode, instanceId, info);
    };
    WebModelStatic::SetOnCommonDialog(frameNode, onBeforeUnload, DialogEventType::DIALOG_EVENT_BEFORE_UNLOAD);
#endif // WEB_SUPPORTED
}
void SetOnConfirmImpl(Ark_NativePointer node,
                      const Opt_Callback_OnConfirmEvent_Boolean* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        return;
    }
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onConfirm = [callback = CallbackHelper(*optValue), weakNode, instanceId](
        const BaseEventInfo* info) -> bool {
        return OnConfirm(callback, weakNode, instanceId, info);
    };
    WebModelStatic::SetOnCommonDialog(frameNode, onConfirm, DialogEventType::DIALOG_EVENT_CONFIRM);
#endif // WEB_SUPPORTED
}
void SetOnPromptImpl(Ark_NativePointer node,
                     const Opt_Callback_OnPromptEvent_Boolean* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        return;
    }
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onPrompt = [callback = CallbackHelper(*optValue), weakNode, instanceId](
        const BaseEventInfo* info) -> bool {
        return OnPrompt(callback, weakNode, instanceId, info);
    };
    WebModelStatic::SetOnCommonDialog(frameNode, onPrompt, DialogEventType::DIALOG_EVENT_PROMPT);
#endif // WEB_SUPPORTED
}
void SetOnConsoleImpl(Ark_NativePointer node,
                      const Opt_Callback_OnConsoleEvent_Boolean* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        return;
    }
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onConsole = [callback = CallbackHelper(*optValue), weakNode](
        const BaseEventInfo* info) -> bool {
        return OnConsole(callback, weakNode, info);
    };
    WebModelStatic::SetOnConsoleLog(frameNode, onConsole);
#endif // WEB_SUPPORTED
}
void SetOnErrorReceiveImpl(Ark_NativePointer node,
                           const Opt_Callback_OnErrorReceiveEvent_Void* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        return;
    }
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onErrorReceive = [callback = CallbackHelper(*optValue), weakNode, instanceId](
        const BaseEventInfo* info) {
        OnErrorReceive(callback, weakNode, instanceId, info);
    };
    WebModelStatic::SetOnErrorReceive(frameNode, onErrorReceive);
#endif // WEB_SUPPORTED
}
void SetOnHttpErrorReceiveImpl(Ark_NativePointer node,
                               const Opt_Callback_OnHttpErrorReceiveEvent_Void* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        return;
    }
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onHttpErrorReceive = [callback = CallbackHelper(*optValue), weakNode, instanceId](
        const BaseEventInfo* info) {
        OnHttpErrorReceive(callback, weakNode, instanceId, info);
    };
    WebModelStatic::SetOnHttpErrorReceive(frameNode, onHttpErrorReceive);
#endif // WEB_SUPPORTED
}
void SetOnDownloadStartImpl(Ark_NativePointer node,
                            const Opt_Callback_OnDownloadStartEvent_Void* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        return;
    }
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onDownloadStart = [callback = CallbackHelper(*optValue), weakNode, instanceId](
        const BaseEventInfo* info) {
        OnDownloadStart(callback, weakNode, instanceId, info);
    };
    WebModelStatic::SetOnDownloadStart(frameNode, onDownloadStart);
#endif // WEB_SUPPORTED
}
void SetOnRefreshAccessedHistoryImpl(Ark_NativePointer node,
                                     const Opt_Callback_OnRefreshAccessedHistoryEvent_Void* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        return;
    }
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onRefreshAccessedHistory = [callback = CallbackHelper(*optValue), weakNode, instanceId](
        const BaseEventInfo* info) {
        OnRefreshAccessedHistory(callback, weakNode, instanceId, info);
    };
    WebModelStatic::SetRefreshAccessedHistoryId(frameNode, onRefreshAccessedHistory);
#endif // WEB_SUPPORTED
}
void SetOnRenderExitedImpl(Ark_NativePointer node,
                           const Opt_Callback_OnRenderExitedEvent_Void* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        return;
    }
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onRenderExited = [callback = CallbackHelper(*optValue), weakNode, instanceId](
        const BaseEventInfo* info) {
        OnRenderExited(callback, weakNode, instanceId, info);
    };
    WebModelStatic::SetRenderExitedId(frameNode, onRenderExited);
#endif // WEB_SUPPORTED
}
void SetOnShowFileSelectorImpl(Ark_NativePointer node,
                               const Opt_Callback_OnShowFileSelectorEvent_Boolean* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        return;
    }
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onShowFileSelector = [callback = CallbackHelper(*optValue), weakNode, instanceId](
        const BaseEventInfo* info) -> bool {
        return OnShowFileSelector(callback, weakNode, instanceId, info);
    };
    WebModelStatic::SetOnFileSelectorShow(frameNode, onShowFileSelector);
#endif // WEB_SUPPORTED
}
void SetOnResourceLoadImpl(Ark_NativePointer node,
                           const Opt_Callback_OnResourceLoadEvent_Void* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        return;
    }
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onResourceLoad = [callback = CallbackHelper(*optValue), weakNode, instanceId](
        const BaseEventInfo* info) {
        OnResourceLoad(callback, weakNode, instanceId, info);
    };
    WebModelStatic::SetResourceLoadId(frameNode, onResourceLoad);
#endif // WEB_SUPPORTED
}
void SetOnFullScreenExitImpl(Ark_NativePointer node,
                             const Opt_Callback_Void* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        return;
    }
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onFullScreenExit = [callback = CallbackHelper(*optValue), weakNode, instanceId](
        const BaseEventInfo* info) {
        OnFullScreenExit(callback, weakNode, instanceId, info);
    };
    WebModelStatic::SetOnFullScreenExit(frameNode, onFullScreenExit);
#endif // WEB_SUPPORTED
}
void SetOnFullScreenEnterImpl(Ark_NativePointer node,
                              const Opt_OnFullScreenEnterCallback* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        return;
    }
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onFullScreenEnter = [callback = CallbackHelper(*optValue), weakNode, instanceId](
        const BaseEventInfo* info) {
        OnFullScreenEnter(callback, weakNode, instanceId, info);
    };
    WebModelStatic::SetOnFullScreenEnter(frameNode, onFullScreenEnter);
#endif // WEB_SUPPORTED
}
void SetOnScaleChangeImpl(Ark_NativePointer node,
                          const Opt_Callback_OnScaleChangeEvent_Void* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        return;
    }
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onScaleChange = [callback = CallbackHelper(*optValue), weakNode, instanceId](
        const BaseEventInfo* info) {
        OnScaleChange(callback, weakNode, instanceId, info);
    };
    WebModelStatic::SetScaleChangeId(frameNode, onScaleChange);
#endif // WEB_SUPPORTED
}
void SetOnHttpAuthRequestImpl(Ark_NativePointer node,
                              const Opt_Callback_OnHttpAuthRequestEvent_Boolean* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        return;
    }
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onHttpAuthRequest = [callback = CallbackHelper(*optValue), weakNode, instanceId](
        const BaseEventInfo* info) -> bool {
        return OnHttpAuthRequest(callback, weakNode, instanceId, info);
    };
    WebModelStatic::SetOnHttpAuthRequest(frameNode, onHttpAuthRequest);
#endif // WEB_SUPPORTED
}
void SetOnInterceptRequestImpl(Ark_NativePointer node,
                               const Opt_Type_WebAttribute_onInterceptRequest* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        return;
    }
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onInterceptRequest = [callback = CallbackHelper(*optValue), weakNode, instanceId](
        const BaseEventInfo* info) -> RefPtr<WebResponse> {
        return OnInterceptRequest(callback, weakNode, instanceId, info);
    };
    WebModelStatic::SetOnInterceptRequest(frameNode, onInterceptRequest);
#endif // WEB_SUPPORTED
}
void SetOnPermissionRequestImpl(Ark_NativePointer node,
                                const Opt_Callback_OnPermissionRequestEvent_Void* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        return;
    }
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onPermissionRequest = [callback = CallbackHelper(*optValue), weakNode, instanceId](
        const BaseEventInfo* info) {
        OnPermissionRequest(callback, weakNode, instanceId, info);
    };
    WebModelStatic::SetPermissionRequestEventId(frameNode, onPermissionRequest);
#endif // WEB_SUPPORTED
}
void SetOnScreenCaptureRequestImpl(Ark_NativePointer node,
                                   const Opt_Callback_OnScreenCaptureRequestEvent_Void* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        return;
    }
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onScreenCaptureRequest = [callback = CallbackHelper(*optValue), weakNode, instanceId](
        const BaseEventInfo* info) {
        OnScreenCaptureRequest(callback, weakNode, instanceId, info);
    };
    WebModelStatic::SetScreenCaptureRequestEventId(frameNode, onScreenCaptureRequest);
#endif // WEB_SUPPORTED
}
void SetOnContextMenuShowImpl(Ark_NativePointer node,
                              const Opt_Callback_OnContextMenuShowEvent_Boolean* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        return;
    }
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onContextMenuShow = [callback = CallbackHelper(*optValue), weakNode, instanceId](
        const BaseEventInfo* info) -> bool {
        return OnContextMenuShow(callback, weakNode, instanceId, info);
    };
    WebModelStatic::SetOnContextMenuShow(frameNode, onContextMenuShow);
#endif // WEB_SUPPORTED
}
void SetOnContextMenuHideImpl(Ark_NativePointer node,
                              const Opt_OnContextMenuHideCallback* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        return;
    }
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onContextMenuHide = [callback = CallbackHelper(*optValue), weakNode, instanceId](
        const BaseEventInfo* info) {
        OnContextMenuHide(callback, weakNode, instanceId, info);
    };
    WebModelStatic::SetOnContextMenuHide(frameNode, onContextMenuHide);
#endif // WEB_SUPPORTED
}
void SetMediaPlayGestureAccessImpl(Ark_NativePointer node,
                                   const Opt_Boolean* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    if (!convValue) {
        // Implement Reset value
        return;
    }
    WebModelStatic::SetMediaPlayGestureAccess(frameNode, *convValue);
#endif // WEB_SUPPORTED
}
void SetOnSearchResultReceiveImpl(Ark_NativePointer node,
                                  const Opt_Callback_OnSearchResultReceiveEvent_Void* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        return;
    }
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onSearchResultReceive = [callback = CallbackHelper(*optValue), weakNode, instanceId](
        const BaseEventInfo* info) {
        OnSearchResultReceive(callback, weakNode, instanceId, info);
    };
    WebModelStatic::SetSearchResultReceiveEventId(frameNode, onSearchResultReceive);
#endif // WEB_SUPPORTED
}
void SetOnScrollImpl(Ark_NativePointer node,
                     const Opt_Callback_OnScrollEvent_Void* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        return;
    }
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onScroll = [callback = CallbackHelper(*optValue), weakNode, instanceId](
        const BaseEventInfo* info) {
        OnScroll(callback, weakNode, instanceId, info);
    };
    WebModelStatic::SetScrollId(frameNode, onScroll);
#endif // WEB_SUPPORTED
}
void SetOnSslErrorEventReceiveImpl(Ark_NativePointer node,
                                   const Opt_Callback_OnSslErrorEventReceiveEvent_Void* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        return;
    }
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onSslErrorEventReceive = [callback = CallbackHelper(*optValue), weakNode, instanceId](
        const BaseEventInfo* info) -> bool {
        return OnSslErrorEventReceive(callback, weakNode, instanceId, info);
    };
    WebModelStatic::SetOnSslErrorRequest(frameNode, onSslErrorEventReceive);
#endif // WEB_SUPPORTED
}
void SetOnSslErrorEventImpl(Ark_NativePointer node,
                            const Opt_OnSslErrorEventCallback* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        return;
    }
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onSslErrorEvent = [callback = CallbackHelper(*optValue), weakNode, instanceId](
        const BaseEventInfo* info) -> bool {
        return OnSslError(callback, weakNode, instanceId, info);
    };
    WebModelStatic::SetOnAllSslErrorRequest(frameNode, onSslErrorEvent);
#endif // WEB_SUPPORTED
}
void SetOnClientAuthenticationRequestImpl(Ark_NativePointer node,
                                          const Opt_Callback_OnClientAuthenticationEvent_Void* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        return;
    }
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onClientAuthenticationRequest = [callback = CallbackHelper(*optValue), weakNode, instanceId](
        const BaseEventInfo* info) -> bool {
        return OnClientAuthentication(callback, weakNode, instanceId, info);
    };
    WebModelStatic::SetOnSslSelectCertRequest(frameNode, onClientAuthenticationRequest);
#endif // WEB_SUPPORTED
}
void SetOnWindowNewImpl(Ark_NativePointer node,
                        const Opt_Callback_OnWindowNewEvent_Void* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        return;
    }
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onWindowNew = [callback = CallbackHelper(*optValue), weakNode, instanceId](
        const std::shared_ptr<BaseEventInfo>& info) {
        OnWindowNew(callback, weakNode, instanceId, info);
    };
    WebModelStatic::SetWindowNewEvent(frameNode, onWindowNew);
#endif // WEB_SUPPORTED
}
void SetOnWindowNewExtImpl(Ark_NativePointer node,
                           const Opt_Callback_OnWindowNewExtEvent_Void* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        return;
    }
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onWindowNewExt = [callback = CallbackHelper(*optValue), weakNode, instanceId](
        const std::shared_ptr<BaseEventInfo>& info) {
        OnWindowNewExt(callback, weakNode, instanceId, info);
    };
    WebModelStatic::SetWindowNewExtEvent(frameNode, onWindowNewExt);
#endif // WEB_SUPPORTED
}
void SetOnWindowExitImpl(Ark_NativePointer node,
                         const Opt_Callback_Void* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        return;
    }
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onWindowExit = [callback = CallbackHelper(*optValue), weakNode, instanceId](
        const BaseEventInfo* info) {
        OnWindowExit(callback, weakNode, instanceId, info);
    };
    WebModelStatic::SetWindowExitEventId(frameNode, onWindowExit);
#endif // WEB_SUPPORTED
}
void SetMultiWindowAccessImpl(Ark_NativePointer node,
                              const Opt_Boolean* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    if (!convValue) {
        // Implement Reset value
        return;
    }
    WebModelStatic::SetMultiWindowAccessEnabled(frameNode, *convValue);
#endif // WEB_SUPPORTED
}
void SetOnInterceptKeyEventImpl(Ark_NativePointer node,
                                const Opt_Callback_KeyEvent_Boolean* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        return;
    }
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onInterceptKeyEvent = [callback = CallbackHelper(*optValue), weakNode](
        KeyEventInfo& keyEventInfo) -> bool {
        return OnInterceptKey(callback, weakNode, keyEventInfo);
    };
    WebModelStatic::SetOnInterceptKeyEventCallback(frameNode, onInterceptKeyEvent);
#endif // WEB_SUPPORTED
}
void SetWebStandardFontImpl(Ark_NativePointer node,
                            const Opt_String* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<std::string>(*value);
    if (!convValue) {
        // Implement Reset value
        return;
    }
    WebModelStatic::SetWebStandardFont(frameNode, *convValue);
#endif // WEB_SUPPORTED
}
void SetWebSerifFontImpl(Ark_NativePointer node,
                         const Opt_String* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<std::string>(*value);
    if (!convValue) {
        // Implement Reset value
        return;
    }
    WebModelStatic::SetWebSerifFont(frameNode, *convValue);
#endif // WEB_SUPPORTED
}
void SetWebSansSerifFontImpl(Ark_NativePointer node,
                             const Opt_String* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<std::string>(*value);
    if (!convValue) {
        // Implement Reset value
        return;
    }
    WebModelStatic::SetWebSansSerifFont(frameNode, *convValue);
#endif // WEB_SUPPORTED
}
void SetWebFixedFontImpl(Ark_NativePointer node,
                         const Opt_String* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<std::string>(*value);
    if (!convValue) {
        // Implement Reset value
        return;
    }
    WebModelStatic::SetWebFixedFont(frameNode, *convValue);
#endif // WEB_SUPPORTED
}
void SetWebFantasyFontImpl(Ark_NativePointer node,
                           const Opt_String* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<std::string>(*value);
    if (!convValue) {
        // Implement Reset value
        return;
    }
    WebModelStatic::SetWebFantasyFont(frameNode, *convValue);
#endif // WEB_SUPPORTED
}
void SetWebCursiveFontImpl(Ark_NativePointer node,
                           const Opt_String* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<std::string>(*value);
    if (!convValue) {
        // Implement Reset value
        return;
    }
    WebModelStatic::SetWebCursiveFont(frameNode, *convValue);
#endif // WEB_SUPPORTED
}
void SetDefaultFixedFontSizeImpl(Ark_NativePointer node,
                                 const Opt_Int32* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<int32_t>(*value);
    if (!convValue) {
        // Implement Reset value
        return;
    }
    WebModelStatic::SetDefaultFixedFontSize(frameNode, *convValue);
#endif // WEB_SUPPORTED
}
void SetDefaultFontSizeImpl(Ark_NativePointer node,
                            const Opt_Int32* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<int32_t>(*value);
    if (!convValue) {
        // Implement Reset value
        return;
    }
    WebModelStatic::SetDefaultFontSize(frameNode, *convValue);
#endif // WEB_SUPPORTED
}
void SetMinFontSizeImpl(Ark_NativePointer node,
                        const Opt_Int32* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<int32_t>(*value);
    if (!convValue) {
        // Implement Reset value
        return;
    }
    WebModelStatic::SetMinFontSize(frameNode, *convValue);
#endif // WEB_SUPPORTED
}
void SetMinLogicalFontSizeImpl(Ark_NativePointer node,
                               const Opt_Int32* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<int32_t>(*value);
    if (!convValue) {
        // Implement Reset value
        return;
    }
    WebModelStatic::SetMinLogicalFontSize(frameNode, *convValue);
#endif // WEB_SUPPORTED
}
void SetDefaultTextEncodingFormatImpl(Ark_NativePointer node,
                                      const Opt_String* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<std::string>(*value);
    if (!convValue) {
        // Implement Reset value
        return;
    }
    EraseSpace(*convValue);
    WebModelStatic::SetDefaultTextEncodingFormat(frameNode, *convValue);
#endif // WEB_SUPPORTED
}
void SetForceDisplayScrollBarImpl(Ark_NativePointer node,
                                  const Opt_Boolean* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    if (!convValue) {
        // Implement Reset value
        return;
    }
    WebModelStatic::SetOverlayScrollbarEnabled(frameNode, *convValue);
#endif // WEB_SUPPORTED
}
void SetBlockNetworkImpl(Ark_NativePointer node,
                         const Opt_Boolean* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    if (!convValue) {
        // Implement Reset value
        return;
    }
    WebModelStatic::SetBlockNetwork(frameNode, *convValue);
#endif // WEB_SUPPORTED
}
void SetHorizontalScrollBarAccessImpl(Ark_NativePointer node,
                                      const Opt_Boolean* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    if (!convValue) {
        // Implement Reset value
        return;
    }
    WebModelStatic::SetHorizontalScrollBarAccessEnabled(frameNode, *convValue);
#endif // WEB_SUPPORTED
}
void SetVerticalScrollBarAccessImpl(Ark_NativePointer node,
                                    const Opt_Boolean* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    if (!convValue) {
        // Implement Reset value
        return;
    }
    WebModelStatic::SetVerticalScrollBarAccessEnabled(frameNode, *convValue);
#endif // WEB_SUPPORTED
}
void SetOnTouchIconUrlReceivedImpl(Ark_NativePointer node,
                                   const Opt_Callback_OnTouchIconUrlReceivedEvent_Void* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        return;
    }
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onTouchIconUrlReceived = [callback = CallbackHelper(*optValue), weakNode, instanceId](
        const std::shared_ptr<BaseEventInfo>& info) {
        OnTouchIconUrlReceived(callback, weakNode, instanceId, info);
    };
    WebModelStatic::SetTouchIconUrlId(frameNode, onTouchIconUrlReceived);
#endif // WEB_SUPPORTED
}
void SetOnFaviconReceivedImpl(Ark_NativePointer node,
                              const Opt_Callback_OnFaviconReceivedEvent_Void* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        return;
    }
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onFaviconReceived = [callback = CallbackHelper(*optValue), weakNode, instanceId](
        const std::shared_ptr<BaseEventInfo>& info) {
        OnFaviconReceived(callback, weakNode, instanceId, info);
    };
    WebModelStatic::SetFaviconReceivedId(frameNode, onFaviconReceived);
#endif // WEB_SUPPORTED
}
void SetOnPageVisibleImpl(Ark_NativePointer node,
                          const Opt_Callback_OnPageVisibleEvent_Void* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        return;
    }
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onPageVisible = [callback = CallbackHelper(*optValue), weakNode, instanceId](
        const std::shared_ptr<BaseEventInfo>& info) {
        OnPageVisible(callback, weakNode, instanceId, info);
    };
    WebModelStatic::SetPageVisibleId(frameNode, std::move(onPageVisible));
#endif // WEB_SUPPORTED
}
void SetOnDataResubmittedImpl(Ark_NativePointer node,
                              const Opt_Callback_OnDataResubmittedEvent_Void* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        return;
    }
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onDataResubmitted = [callback = CallbackHelper(*optValue), weakNode, instanceId](
        const std::shared_ptr<BaseEventInfo>& info) {
        OnDataResubmitted(callback, weakNode, instanceId, info);
    };
    WebModelStatic::SetOnDataResubmitted(frameNode, onDataResubmitted);
#endif // WEB_SUPPORTED
}
void SetPinchSmoothImpl(Ark_NativePointer node,
                        const Opt_Boolean* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    if (!convValue) {
        // Implement Reset value
        return;
    }
    WebModelStatic::SetPinchSmoothModeEnabled(frameNode, *convValue);
#endif // WEB_SUPPORTED
}
void SetAllowWindowOpenMethodImpl(Ark_NativePointer node,
                                  const Opt_Boolean* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    if (!convValue) {
        // Implement Reset value
        return;
    }
    WebModelStatic::SetAllowWindowOpenMethod(frameNode, *convValue);
#endif // WEB_SUPPORTED
}
void SetOnAudioStateChangedImpl(Ark_NativePointer node,
                                const Opt_Callback_OnAudioStateChangedEvent_Void* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        return;
    }
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onAudioStateChanged = [callback = CallbackHelper(*optValue), weakNode, instanceId](
        const std::shared_ptr<BaseEventInfo>& info) {
        OnAudioStateChanged(callback, weakNode, instanceId, info);
    };
    WebModelStatic::SetAudioStateChangedId(frameNode, onAudioStateChanged);
#endif // WEB_SUPPORTED
}
void SetOnFirstContentfulPaintImpl(Ark_NativePointer node,
                                   const Opt_Callback_OnFirstContentfulPaintEvent_Void* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        return;
    }
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onFirstContentfulPaint = [callback = CallbackHelper(*optValue), weakNode, instanceId](
        const std::shared_ptr<BaseEventInfo>& info) {
        OnFirstContentfulPaint(callback, weakNode, instanceId, info);
    };
    WebModelStatic::SetFirstContentfulPaintId(frameNode, std::move(onFirstContentfulPaint));
#endif // WEB_SUPPORTED
}
void SetOnFirstMeaningfulPaintImpl(Ark_NativePointer node,
                                   const Opt_OnFirstMeaningfulPaintCallback* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        return;
    }
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onFirstMeaningfulPaint = [callback = CallbackHelper(*optValue), weakNode, instanceId](
        const std::shared_ptr<BaseEventInfo>& info) {
        OnFirstMeaningfulPaint(callback, weakNode, instanceId, info);
    };
    WebModelStatic::SetFirstMeaningfulPaintId(frameNode, std::move(onFirstMeaningfulPaint));
#endif // WEB_SUPPORTED
}
void SetOnLargestContentfulPaintImpl(Ark_NativePointer node,
                                     const Opt_OnLargestContentfulPaintCallback* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        return;
    }
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onLargestContentfulPaint = [callback = CallbackHelper(*optValue), weakNode, instanceId](
        const std::shared_ptr<BaseEventInfo>& info) {
        OnLargestContentfulPaint(callback, weakNode, instanceId, info);
    };
    WebModelStatic::SetLargestContentfulPaintId(frameNode, std::move(onLargestContentfulPaint));
#endif // WEB_SUPPORTED
}
void SetOnLoadInterceptImpl(Ark_NativePointer node,
                            const Opt_Callback_OnLoadInterceptEvent_Boolean* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        return;
    }
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onLoadIntercept = [callback = CallbackHelper(*optValue), weakNode, instanceId](
        const BaseEventInfo* info) -> bool {
        return OnLoadIntercept(callback, weakNode, instanceId, info);
    };
    WebModelStatic::SetOnLoadIntercept(frameNode, std::move(onLoadIntercept));
#endif // WEB_SUPPORTED
}
void SetOnControllerAttachedImpl(Ark_NativePointer node,
                                 const Opt_Callback_Void* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        return;
    }
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onControllerAttached = [callback = CallbackHelper(*optValue), weakNode, instanceId]() {
        OnControllerAttached(callback, weakNode, instanceId);
    };
    WebModelStatic::SetOnControllerAttached(frameNode, std::move(onControllerAttached));
#endif // WEB_SUPPORTED
}
void SetOnOverScrollImpl(Ark_NativePointer node,
                         const Opt_Callback_OnOverScrollEvent_Void* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        return;
    }
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onOverScroll = [callback = CallbackHelper(*optValue), weakNode, instanceId](
        const BaseEventInfo* info) {
        OnOverScroll(callback, weakNode, instanceId, info);
    };
    WebModelStatic::SetOverScrollId(frameNode, onOverScroll);
#endif // WEB_SUPPORTED
}
void SetOnSafeBrowsingCheckResultImpl(Ark_NativePointer node,
                                      const Opt_OnSafeBrowsingCheckResultCallback* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        return;
    }
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onSafeBrowsingCheckResult = [callback = CallbackHelper(*optValue), weakNode, instanceId](
        const std::shared_ptr<BaseEventInfo>& info) {
        OnSafeBrowsingCheckResult(callback, weakNode, instanceId, info);
    };
    WebModelStatic::SetSafeBrowsingCheckResultId(frameNode, std::move(onSafeBrowsingCheckResult));
#endif // WEB_SUPPORTED
}
void SetOnNavigationEntryCommittedImpl(Ark_NativePointer node,
                                       const Opt_OnNavigationEntryCommittedCallback* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        return;
    }
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onNavigationEntryCommitted = [callback = CallbackHelper(*optValue), weakNode, instanceId](
        const std::shared_ptr<BaseEventInfo>& info) {
        OnNavigationEntryCommitted(callback, weakNode, instanceId, info);
    };
    WebModelStatic::SetNavigationEntryCommittedId(frameNode, std::move(onNavigationEntryCommitted));
#endif // WEB_SUPPORTED
}
void SetOnIntelligentTrackingPreventionResultImpl(Ark_NativePointer node,
                                                  const Opt_OnIntelligentTrackingPreventionCallback* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        return;
    }
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onIntelligentTrackingPreventionResult = [callback = CallbackHelper(*optValue), weakNode, instanceId](
        const std::shared_ptr<BaseEventInfo>& info) {
        OnIntelligentTrackingPrevention(callback, weakNode, instanceId, info);
    };
    WebModelStatic::SetIntelligentTrackingPreventionResultId(frameNode,
                                                             std::move(onIntelligentTrackingPreventionResult));
#endif // WEB_SUPPORTED
}
void SetJavaScriptOnDocumentStartImpl(Ark_NativePointer node,
                                      const Opt_Array_ScriptItem* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<ScriptItems>(*value);
    if (!convValue) {
        // Implement Reset value
        return;
    }
    WebModelStatic::JavaScriptOnDocumentStart(frameNode, *convValue);
#endif // WEB_SUPPORTED
}
void SetJavaScriptOnDocumentEndImpl(Ark_NativePointer node,
                                    const Opt_Array_ScriptItem* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<ScriptItems>(*value);
    if (!convValue) {
        // Implement Reset value
        return;
    }
    WebModelStatic::JavaScriptOnDocumentEnd(frameNode, *convValue);
#endif // WEB_SUPPORTED
}
void SetLayoutModeImpl(Ark_NativePointer node,
                       const Opt_WebLayoutMode* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<WebLayoutMode>(*value);
    WebModelStatic::SetLayoutMode(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void SetNestedScrollImpl(Ark_NativePointer node,
                         const Opt_Union_NestedScrollOptions_NestedScrollOptionsExt* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<NestedScrollOptionsExt>(*value);
    WebModelStatic::SetNestedScrollExt(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void SetEnableNativeEmbedModeImpl(Ark_NativePointer node,
                                  const Opt_Boolean* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    if (!convValue) {
        // Implement Reset value
        return;
    }
    WebModelStatic::SetNativeEmbedModeEnabled(frameNode, *convValue);
#endif // WEB_SUPPORTED
}
void SetOnNativeEmbedLifecycleChangeImpl(Ark_NativePointer node,
                                         const Opt_Callback_NativeEmbedDataInfo_Void* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        return;
    }
    auto instanceId = Container::CurrentId();
    auto onNativeEmbedLifecycleChange = [callback = CallbackHelper(*optValue), instanceId](
        const BaseEventInfo* info) {
        OnNativeEmbedDataInfo(callback, instanceId, info);
    };
    WebModelStatic::SetNativeEmbedLifecycleChangeId(frameNode, onNativeEmbedLifecycleChange);
#endif // WEB_SUPPORTED
}
void SetOnNativeEmbedVisibilityChangeImpl(Ark_NativePointer node,
                                          const Opt_OnNativeEmbedVisibilityChangeCallback* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        return;
    }
    auto instanceId = Container::CurrentId();
    auto onNativeEmbedVisibilityChange = [callback = CallbackHelper(*optValue), instanceId](
        const BaseEventInfo* info) {
        OnNativeEmbedVisibilityChange(callback, instanceId, info);
    };
    WebModelStatic::SetNativeEmbedVisibilityChangeId(frameNode, onNativeEmbedVisibilityChange);
#endif // WEB_SUPPORTED
}
void SetOnNativeEmbedGestureEventImpl(Ark_NativePointer node,
                                      const Opt_Callback_NativeEmbedTouchInfo_Void* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        return;
    }
    auto instanceId = Container::CurrentId();
    auto onNativeEmbedGestureEvent = [callback = CallbackHelper(*optValue), instanceId](
        const BaseEventInfo* info) {
        OnNativeEmbedTouchInfo(callback, instanceId, info);
    };
    WebModelStatic::SetNativeEmbedGestureEventId(frameNode, onNativeEmbedGestureEvent);
#endif // WEB_SUPPORTED
}
void SetCopyOptionsImpl(Ark_NativePointer node,
                        const Opt_CopyOptions* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<CopyOptions>(*value);
    WebModelStatic::SetCopyOptionMode(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void SetOnOverrideUrlLoadingImpl(Ark_NativePointer node,
                                 const Opt_OnOverrideUrlLoadingCallback* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        return;
    }
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onOverrideUrlLoading = [callback = CallbackHelper(*optValue), weakNode, instanceId](
        const BaseEventInfo* info) -> bool {
        return OnOverrideUrlLoading(callback, weakNode, instanceId, info);
    };
    WebModelStatic::SetOnOverrideUrlLoading(frameNode, std::move(onOverrideUrlLoading));
#endif // WEB_SUPPORTED
}
void SetTextAutosizingImpl(Ark_NativePointer node,
                           const Opt_Boolean* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    if (!convValue) {
        // Implement Reset value
        return;
    }
    WebModelStatic::SetTextAutosizing(frameNode, *convValue);
#endif // WEB_SUPPORTED
}
void SetEnableNativeMediaPlayerImpl(Ark_NativePointer node,
                                    const Opt_NativeMediaPlayerConfig* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        return;
    }
    auto enable = Converter::Convert<bool>(optValue->enable);
    auto shouldOverlay = Converter::Convert<bool>(optValue->shouldOverlay);
    WebModelStatic::SetNativeVideoPlayerConfig(frameNode, enable, shouldOverlay);
#endif // WEB_SUPPORTED
}
void SetOnRenderProcessNotRespondingImpl(Ark_NativePointer node,
                                         const Opt_OnRenderProcessNotRespondingCallback* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        return;
    }
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onRenderProcessNotResponding = [callback = CallbackHelper(*optValue), weakNode, instanceId](
        const BaseEventInfo* info) {
        OnRenderProcessNotResponding(callback, weakNode, instanceId, info);
    };
    WebModelStatic::SetRenderProcessNotRespondingId(frameNode, onRenderProcessNotResponding);
#endif // WEB_SUPPORTED
}
void SetOnRenderProcessRespondingImpl(Ark_NativePointer node,
                                      const Opt_OnRenderProcessRespondingCallback* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        return;
    }
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onRenderProcessResponding = [callback = CallbackHelper(*optValue), weakNode, instanceId](
        const BaseEventInfo* info) {
        OnRenderProcessResponding(callback, weakNode, instanceId, info);
    };
    WebModelStatic::SetRenderProcessRespondingId(frameNode, onRenderProcessResponding);
#endif // WEB_SUPPORTED
}
#ifdef WRONG_SDK
void SelectionMenuOptionsImpl(Ark_NativePointer node,
                              const Opt_Array_ExpandedMenuItemOptions* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<std::vector<Ark_ExpandedMenuItemOptions>>(*value)
        .value_or(std::vector<Ark_ExpandedMenuItemOptions>{});
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    WebMenuOptionsParam optionParam;
    for (auto menuOption : convValue) {
        auto option = Converter::Convert<MenuOptionsParam>(menuOption);
        auto action = [arkCallback = CallbackHelper(menuOption.action), weakNode](
                const std::string selectInfo) {
            auto webNode = weakNode.Upgrade();
            CHECK_NULL_VOID(webNode);
            ContainerScope scope(webNode->GetInstanceId());
            auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
            if (pipelineContext) {
                pipelineContext->UpdateCurrentActiveNode(weakNode);
                pipelineContext->SetCallBackNode(weakNode);
            }
            Ark_Literal_String_plainText parameter;
            parameter.plainText = Converter::ArkValue<Ark_String>(selectInfo);
            arkCallback.InvokeSync(parameter);
        };
        option.action = std::move(action);
        optionParam.menuOption.push_back(option);
    }
    WebModelStatic::SetSelectionMenuOptions(frameNode, optionParam);
#endif // WEB_SUPPORTED
}
#endif
void SetOnViewportFitChangedImpl(Ark_NativePointer node,
                                 const Opt_OnViewportFitChangedCallback* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        return;
    }
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onViewportFitChanged = [callback = CallbackHelper(*optValue), weakNode, instanceId](
        const BaseEventInfo* info) {
        OnViewportFitChanged(callback, weakNode, instanceId, info);
    };
    WebModelStatic::SetViewportFitChangedId(frameNode, onViewportFitChanged);
#endif // WEB_SUPPORTED
}
void SetOnInterceptKeyboardAttachImpl(Ark_NativePointer node,
                                      const Opt_WebKeyboardCallback* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        return;
    }
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onInterceptKeyboardAttach = [callback = CallbackHelper(*optValue), weakNode, instanceId](
        const BaseEventInfo* info) -> WebKeyboardOption {
        return OnWebKeyboard(callback, weakNode, instanceId, info);
    };
    WebModelStatic::SetOnInterceptKeyboardAttach(frameNode, std::move(onInterceptKeyboardAttach));
#endif // WEB_SUPPORTED
}
void SetOnAdsBlockedImpl(Ark_NativePointer node,
                         const Opt_OnAdsBlockedCallback* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        return;
    }
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onAdsBlocked = [callback = CallbackHelper(*optValue), weakNode, instanceId](
        const BaseEventInfo* info) {
        OnAdsBlocked(callback, weakNode, instanceId, info);
    };
    WebModelStatic::SetAdsBlockedEventId(frameNode, onAdsBlocked);
#endif // WEB_SUPPORTED
}
void SetKeyboardAvoidModeImpl(Ark_NativePointer node,
                              const Opt_WebKeyboardAvoidMode* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<WebKeyboardAvoidMode>(*value);
    WebModelStatic::SetKeyboardAvoidMode(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void SetEditMenuOptionsImpl(Ark_NativePointer node,
                            const Opt_EditMenuOptions* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        return;
    }
    auto createMenuCallback = Converter::GetOpt(optValue->onCreateMenu);
    std::function<std::vector<NG::MenuOptionsParam>(const std::vector<NG::MenuItemParam>&)> onCreateMenuCallback =
        nullptr;
    if (createMenuCallback) {
        onCreateMenuCallback =
            [arkCreateMenu = CallbackHelper(*createMenuCallback)](
                const std::vector<NG::MenuItemParam>& systemMenuItems) -> std::vector<NG::MenuOptionsParam> {
            auto menuItems = Converter::ArkValue<Array_TextMenuItem>(systemMenuItems, Converter::FC);
            auto result = arkCreateMenu.InvokeWithOptConvertResult<std::vector<NG::MenuOptionsParam>,
                Array_TextMenuItem, Callback_Array_TextMenuItem_Void>(menuItems);
            return result.value_or(std::vector<NG::MenuOptionsParam>());
        };
    }
    auto menuItemClickCallback = Converter::GetOpt(optValue->onMenuItemClick);
    std::function<bool(NG::MenuItemParam)> onMenuItemClickCallback = nullptr;
    if (menuItemClickCallback) {
        onMenuItemClickCallback = [arkMenuItemClick = CallbackHelper(*menuItemClickCallback)](
                                      NG::MenuItemParam menuOptionsParam) -> bool {
            TextRange range { .start = menuOptionsParam.start, .end = menuOptionsParam.end };
            auto menuItem = Converter::ArkValue<Ark_TextMenuItem>(menuOptionsParam);
            auto arkRange = Converter::ArkValue<Ark_TextRange>(range);
            auto arkResult =
                arkMenuItemClick.InvokeWithObtainResult<Ark_Boolean, Callback_Boolean_Void>(menuItem, arkRange);
            return Converter::Convert<bool>(arkResult);
        };
    }
    WebModelStatic::SetEditMenuOptions(frameNode, std::move(onCreateMenuCallback), std::move(onMenuItemClickCallback));
#endif // WEB_SUPPORTED
}
void SetEnableHapticFeedbackImpl(Ark_NativePointer node,
                                 const Opt_Boolean* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    if (!convValue) {
        // Implement Reset value
        return;
    }
    WebModelStatic::SetEnabledHapticFeedback(frameNode, *convValue);
#endif // WEB_SUPPORTED
}
void SetOptimizeParserBudgetImpl(Ark_NativePointer node,
                                 const Opt_Boolean* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    WebModelStatic::SetOptimizeParserBudgetEnabled(frameNode, convValue);
#endif
}
void SetEnableFollowSystemFontWeightImpl(Ark_NativePointer node,
                                         const Opt_Boolean* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    WebModelStatic::SetEnableFollowSystemFontWeight(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void SetEnableWebAVSessionImpl(Ark_NativePointer node,
                               const Opt_Boolean* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    WebModelStatic::SetWebMediaAVSessionEnabled(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void SetRunJavaScriptOnDocumentStartImpl(Ark_NativePointer node,
                                         const Opt_Array_ScriptItem* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<ScriptItems>(*value);
    if (!convValue) {
        // Implement Reset value
        return;
    }
    auto convValueByOrder = Converter::OptConvert<ScriptItemsByOrder>(*value);
    if (!convValueByOrder) {
        // Implement Reset value
        return;
    }

    auto convRegexRulesValue = Converter::OptConvert<ScriptRegexItems>(*value);
    if (!convRegexRulesValue) {
        // Implement Reset value
        return;
    }
    WebModelStatic::JavaScriptOnDocumentStartByOrder(
        frameNode, *convValue, *convRegexRulesValue, *convValueByOrder);
#endif // WEB_SUPPORTED
}
void SetRunJavaScriptOnDocumentEndImpl(Ark_NativePointer node,
                                       const Opt_Array_ScriptItem* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<ScriptItems>(*value);
    if (!convValue) {
        // Implement Reset value
        return;
    }
    auto convValueByOrder = Converter::OptConvert<ScriptItemsByOrder>(*value);
    if (!convValueByOrder) {
        // Implement Reset value
        return;
    }

    auto convRegexRulesValue = Converter::OptConvert<ScriptRegexItems>(*value);
    if (!convRegexRulesValue) {
        // Implement Reset value
        return;
    }
    WebModelStatic::JavaScriptOnDocumentEndByOrder(
        frameNode, *convValue, *convRegexRulesValue, *convValueByOrder);
#endif // WEB_SUPPORTED
}
void SetRunJavaScriptOnHeadEndImpl(Ark_NativePointer node,
                                   const Opt_Array_ScriptItem* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<ScriptItems>(*value);
    if (!convValue) {
        // Implement Reset value
        return;
    }
    auto convValueByOrder = Converter::OptConvert<ScriptItemsByOrder>(*value);
    if (!convValueByOrder) {
        // Implement Reset value
        return;
    }
    auto convRegexRulesValue = Converter::OptConvert<ScriptRegexItems>(*value);
    if (!convRegexRulesValue) {
        // Implement Reset value
        return;
    }

    WebModelStatic::JavaScriptOnHeadEnd(frameNode, *convValue, *convRegexRulesValue, *convValueByOrder);
#endif // WEB_SUPPORTED
}
void SetNativeEmbedOptionsImpl(Ark_NativePointer node,
                               const Opt_EmbedOptions* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<Ark_EmbedOptions>(*value);
    if (!convValue) {
        // Implement Reset value
        return;
    }
    auto supportDefaultIntrinsicSize = Converter::OptConvert<bool>(convValue.value().supportDefaultIntrinsicSize);
    auto supportCssDisplayChange = Converter::OptConvert<bool>(convValue.value().supportCssDisplayChange);
    if (supportCssDisplayChange.has_value()) {
        RETURN_IF_CALLING_FROM_M114();
    }

    WebModelStatic::SetNativeEmbedOptions(frameNode, *supportDefaultIntrinsicSize, *supportCssDisplayChange);
#endif // WEB_SUPPORTED
}
void SetRegisterNativeEmbedRuleImpl(Ark_NativePointer node,
                                    const Opt_String* tag,
                                    const Opt_String* type)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValueTag = Converter::OptConvert<std::string>(*tag);
    if (!convValueTag) {
        // Implement Reset value
        return;
    }
    auto convValueType = Converter::OptConvert<std::string>(*type);
    if (!convValueType) {
        // Implement Reset value
        return;
    }
    WebModelStatic::RegisterNativeEmbedRule(frameNode, *convValueTag, *convValueType);
#endif // WEB_SUPPORTED
}

#ifdef WEB_SUPPORTED
void InitCallbackParams_(FrameNode* frameNode,
    const std::shared_ptr<WebPreviewSelectionMenuParam>& dst, const Ark_SelectionMenuOptionsExt& options)
{
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto arkOnDisappear = Converter::OptConvert<VoidCallback>(options.onDisappear);
    if (arkOnDisappear) {
        auto onDisappear = [arkCallback = CallbackHelper(arkOnDisappear.value()), weakNode]() {
            PipelineContext::SetCallBackNode(weakNode);
            arkCallback.InvokeSync();
        };
        dst->menuParam.onDisappear = std::move(onDisappear);
    }
    auto arkOnAppear = Converter::OptConvert<VoidCallback>(options.onAppear);
    if (arkOnAppear) {
        auto onAppear = [arkCallback = CallbackHelper(arkOnAppear.value()), weakNode]() {
            PipelineContext::SetCallBackNode(weakNode);
            arkCallback.InvokeSync();
        };
        dst->menuParam.onAppear = std::move(onAppear);
    }
    auto arkOnMenuShow = Converter::OptConvert<VoidCallback>(options.onMenuShow);
    if (arkOnMenuShow) {
        dst->onMenuShow = [arkCallback = CallbackHelper(arkOnMenuShow.value()), weakNode]() {
            PipelineContext::SetCallBackNode(weakNode);
            arkCallback.InvokeSync();
        };
    }
    auto arkOnMenuHide = Converter::OptConvert<VoidCallback>(options.onMenuHide);
    if (arkOnMenuHide) {
        dst->onMenuHide = [arkCallback = CallbackHelper(arkOnMenuHide.value()), weakNode]() {
            PipelineContext::SetCallBackNode(weakNode);
            arkCallback.InvokeSync();
        };
    }
}

std::function<void(const std::shared_ptr<WebPreviewSelectionMenuParam>&)> GetPreviewHandler(
    Ark_NativePointer node, const CustomNodeBuilder& preview)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    std::function<void(const std::shared_ptr<WebPreviewSelectionMenuParam>&)> previewHandler =
        [callback = CallbackHelper(preview), node, frameNode](
            const std::shared_ptr<WebPreviewSelectionMenuParam>& param) {
            callback.BuildAsync([param, frameNode](const RefPtr<UINode>& uiNode) {
                std::function<void()> previewNodeBuilder = [uiNode]() {
                    NG::ViewStackProcessor::GetInstance()->Push(uiNode);
                };
                param->previewBuilder = previewNodeBuilder;
                WebModelStatic::SetPreviewSelectionMenu(frameNode, param);
                }, node);
        };
    return previewHandler;
}

bool InitSelectMenuParam(const std::shared_ptr<WebPreviewSelectionMenuParam>& selectMenuParam,
    const Opt_WebElementType* elementType, const Opt_WebResponseType* responseType)
{
    auto elType = Converter::OptConvert<WebElementType>(*elementType);
    CHECK_EQUAL_RETURN(elType.has_value(), false, false);
    auto resType = Converter::OptConvert<ResponseType>(*responseType);
    CHECK_EQUAL_RETURN(resType.has_value(), false, false);
    selectMenuParam->type = elType.value();
    selectMenuParam->responseType = resType.value();

    MenuParam& menuParam = selectMenuParam->menuParam;
    menuParam.contextMenuRegisterType = NG::ContextMenuRegisterType::CUSTOM_TYPE;
    menuParam.type = NG::MenuType::CONTEXT_MENU;
    NG::PaddingProperty paddings;
    paddings.start = NG::CalcLength(PREVIEW_MENU_MARGIN_LEFT);
    paddings.end = NG::CalcLength(PREVIEW_MENU_MARGIN_RIGHT);
    menuParam.layoutRegionMargin = paddings;
    menuParam.disappearScaleToTarget = true;
    menuParam.isPreviewContainScale = (selectMenuParam->type == WebElementType::IMAGE);
    if (selectMenuParam->responseType == ResponseType::RIGHT_CLICK) {
        menuParam.menuBindType = MenuBindingType::RIGHT_CLICK;
    } else if (selectMenuParam->responseType == ResponseType::LONG_PRESS) {
        menuParam.menuBindType = MenuBindingType::LONG_PRESS;
    }
    menuParam.isShow = true;
    return true;
}

std::function<void(const std::shared_ptr<WebPreviewSelectionMenuParam>&)> ParseSelectionMenuOptionsExt(
    Ark_NativePointer node, const std::shared_ptr<WebPreviewSelectionMenuParam>& dst,
    const Ark_SelectionMenuOptionsExt& options)
{
    MenuParam& menuParam = dst->menuParam;
    InitCallbackParams_(reinterpret_cast<FrameNode *>(node), dst, options);
    auto menuType =
        Converter::OptConvert<SelectionMenuType>(options.menuType).value_or(SelectionMenuType::SELECTION_MENU);
    CHECK_NE_RETURN(menuType, SelectionMenuType::PREVIEW_MENU, nullptr);
    if (dst->responseType == ResponseType::LONG_PRESS) {
        menuParam.previewMode = MenuPreviewMode::CUSTOM;
    }
    auto previewMenuOptions = Converter::OptConvert<NG::PreviewMenuOptions>(options.previewMenuOptions);
    if (previewMenuOptions.has_value()) {
        menuParam.hapticFeedbackMode = previewMenuOptions.value().hapticFeedbackMode;
    }
    auto preview = Converter::OptConvert<CustomNodeBuilder>(options.preview);
    CHECK_EQUAL_RETURN(preview.has_value(), false, nullptr);
    return GetPreviewHandler(node, preview.value());
}
#endif // WEB_SUPPORTED

void SetBindSelectionMenuImpl(Ark_NativePointer node,
                              const Opt_WebElementType* elementType,
                              const Opt_CustomNodeBuilder* content,
                              const Opt_WebResponseType* responseType,
                              const Opt_SelectionMenuOptionsExt* options)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto selectMenuParam = std::make_shared<WebPreviewSelectionMenuParam>();
    CHECK_NULL_VOID(selectMenuParam);
    CHECK_EQUAL_VOID(InitSelectMenuParam(selectMenuParam, elementType, responseType), false);
    if (selectMenuParam->type != WebElementType::IMAGE || selectMenuParam->responseType != ResponseType::LONG_PRESS) {
        RETURN_IF_CALLING_FROM_M114();
    }
    auto arkOptions = options ? Converter::OptConvert<Ark_SelectionMenuOptionsExt>(*options) : std::nullopt;
    std::function<void(const std::shared_ptr<WebPreviewSelectionMenuParam>&)> previewHandler = nullptr;
    if (arkOptions) {
        previewHandler = ParseSelectionMenuOptionsExt(node, selectMenuParam, arkOptions.value());
    }
    auto optContent = Converter::GetOptPtr(content);
    if (!optContent) {
        // Implement Reset value
        return;
    }
    WebModelStatic::SetNewDragStyle(frameNode, true);
    CallbackHelper(*optContent).BuildAsync([frameNode, selectMenuParam,
        previewHandler = std::move(previewHandler)](const RefPtr<UINode>& uiNode) {
        selectMenuParam->menuBuilder = [uiNode]() {
            NG::ViewStackProcessor::GetInstance()->Push(uiNode);
        };
        if (previewHandler) {
            previewHandler(selectMenuParam);
        } else {
            WebModelStatic::SetPreviewSelectionMenu(frameNode, selectMenuParam);
        }
        }, node);
#endif // WEB_SUPPORTED
}

void SetRotateRenderEffectImpl(Ark_NativePointer node,
                               const Opt_WebRotateEffect* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<WebRotateEffect>(*value);
    WebModelStatic::SetRotateRenderEffect(frameNode, convValue);
#endif // WEB_SUPPORTED
}

void SetOnOverrideErrorPageImpl(Ark_NativePointer node,
                                const Opt_OnOverrideErrorPageCallback* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        return;
    }
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onOverrideErrorPage = [callback = CallbackHelper(*optValue), weakNode, instanceId](
        const BaseEventInfo* info) -> std::string {
        return OnOverrideErrorPage(callback, weakNode, instanceId, info);
    };
    WebModelStatic::SetOnOverrideErrorPage(frameNode, onOverrideErrorPage);
#endif // WEB_SUPPORTED
}

void SetOnPdfScrollAtBottomImpl(Ark_NativePointer node,
                                const Opt_Callback_OnPdfScrollEvent_Void* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        return;
    }
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onPdfScrollAtBottom = [callback = CallbackHelper(*optValue), weakNode, instanceId](
        const BaseEventInfo* info) {
        OnPdfScrollAtBottom(callback, weakNode, instanceId, info);
    };
    WebModelStatic::SetOnPdfScrollAtBottom(frameNode, std::move(onPdfScrollAtBottom));
#endif // WEB_SUPPORTED
}

void SetOnPdfLoadEventImpl(Ark_NativePointer node,
                           const Opt_Callback_OnPdfLoadEvent_Void* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        return;
    }
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onPdfLoadEvent = [callback = CallbackHelper(*optValue), weakNode, instanceId](
        const BaseEventInfo* info) {
        OnPdfLoadEvent(callback, weakNode, instanceId, info);
    };
    WebModelStatic::SetOnPdfLoadEvent(frameNode, std::move(onPdfLoadEvent));
#endif // WEB_SUPPORTED
}

void SetOnSafeBrowsingCheckFinishImpl(Ark_NativePointer node,
                                      const Opt_OnSafeBrowsingCheckResultCallback* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        return;
    }
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onSafeBrowsingCheckFinish = [callback = CallbackHelper(*optValue), weakNode, instanceId](
        const std::shared_ptr<BaseEventInfo>& info) {
        OnSafeBrowsingCheckFinish(callback, weakNode, instanceId, info);
    };
    WebModelStatic::SetSafeBrowsingCheckFinishId(frameNode, std::move(onSafeBrowsingCheckFinish));
#endif // WEB_SUPPORTED
}

void SetOnNativeEmbedMouseEventImpl(Ark_NativePointer node,
                                    const Opt_MouseInfoCallback* value)
{
#ifdef WEB_SUPPORTED
    RETURN_IF_CALLING_FROM_M114();
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        return;
    }
    auto instanceId = Container::CurrentId();
    auto onNativeEmbedMouseEvent = [callback = CallbackHelper(*optValue), instanceId](
        const BaseEventInfo* info) {
        OnNativeEmbedMouseInfo(callback, instanceId, info);
    };
    WebModelStatic::SetNativeEmbedMouseEventId(frameNode, onNativeEmbedMouseEvent);
#endif // WEB_SUPPORTED
}

void SetOnNativeEmbedObjectParamChangeImpl(Ark_NativePointer node,
                                           const Opt_OnNativeEmbedObjectParamChangeCallback* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        return;
    }
    auto instanceId = Container::CurrentId();
    auto onNativeEmbedObjectParamChange = [callback = CallbackHelper(*optValue), instanceId](
        const BaseEventInfo* info) {
        OnNativeEmbedObjectParamChange(callback, instanceId, info);
    };
    WebModelStatic::SetNativeEmbedObjectParamChangeId(frameNode, onNativeEmbedObjectParamChange);
#endif // WEB_SUPPORTED
}

void SetEnableDataDetectorImpl(Ark_NativePointer node,
                               const Opt_Boolean* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    WebModelStatic::SetEnableDataDetector(frameNode, convValue.value_or(false));
#endif // WEB_SUPPORTED
}

void SetDataDetectorConfigImpl(Ark_NativePointer node,
                               const Opt_TextDataDetectorConfig* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<TextDetectConfig>(*value);
    if (!convValue) {
        return;
    }
    WebModelStatic::SetDataDetectorConfig(frameNode, *convValue);
#endif // WEB_SUPPORTED
}

void SetOnActivateContentImpl(Ark_NativePointer node,
                           const Opt_VoidCallback* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onActivateContent = [callback = CallbackHelper(*optValue), weakNode, instanceId](
        const BaseEventInfo* info) {
        OnActivateContent(callback, weakNode, instanceId, info);
    };
    WebModelStatic::SetActivateContentEventId(frameNode, onActivateContent);
#endif // WEB_SUPPORTED
}

void SetBypassVsyncConditionImpl(Ark_NativePointer node,
                                 const Opt_WebBypassVsyncCondition* value)
{
#ifdef WEB_SUPPORTED
    RETURN_IF_CALLING_FROM_M114();
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<WebBypassVsyncCondition>(*value);
    WebModelStatic::SetBypassVsyncCondition(frameNode, convValue.value_or(WebBypassVsyncCondition::NONE));
#endif // WEB_SUPPORTED
}

void SetGestureFocusModeImpl(Ark_NativePointer node,
                             const Opt_GestureFocusMode* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<GestureFocusMode>(*value);
    CHECK_EQUAL_VOID(convValue.has_value(), false);
    WebModelStatic::SetGestureFocusMode(frameNode, convValue.value());
#endif // WEB_SUPPORTED
}

void SetForceEnableZoomImpl(Ark_NativePointer node,
                            const Opt_Boolean* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    if (!convValue) {
        // Implement Reset value
        return;
    }
    WebModelStatic::SetForceEnableZoom(frameNode, *convValue);
#endif // WEB_SUPPORTED
}

void SetBackToTopImpl(Ark_NativePointer node,
                      const Opt_Boolean* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    if (!convValue) {
        WebModelStatic::SetBackToTop(frameNode, false);
        return;
    }
    WebModelStatic::SetBackToTop(frameNode, *convValue);
#endif // WEB_SUPPORTED
}

void SetOnDetectedBlankScreenImpl(Ark_NativePointer node,
                                  const Opt_OnDetectBlankScreenCallback* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        return;
    }
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onDetectedBlankScreen = [callback = CallbackHelper(*optValue), weakNode, instanceId](
        const BaseEventInfo* info) -> void {
        OnDetectedBlankScreen(callback, weakNode, instanceId, info);
    };
    WebModelStatic::SetOnDetectedBlankScreen(frameNode, onDetectedBlankScreen);
#endif // WEB_SUPPORTED
}

void SetBlankScreenDetectionConfigImpl(Ark_NativePointer node,
                                       const Opt_BlankScreenDetectionConfig* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        return;
    }
    auto enable = Converter::Convert<bool>(optValue->enable);
    std::vector<double> detectionTiming;
    std::vector<int32_t> detectionMethods;
    auto arkDetectionTiming = Converter::OptConvert<std::vector<Ark_Float64>>(optValue->detectionTiming)
                                  .value_or(std::vector<Ark_Float64> {});
    auto arkDetectionMethods =
        Converter::OptConvert<std::vector<Ark_BlankScreenDetectionMethod>>(optValue->detectionMethods)
            .value_or(std::vector<Ark_BlankScreenDetectionMethod> {});
    for (auto timing : arkDetectionTiming) {
        auto time = Converter::Convert<double>(timing);
        if (time > 0.0) {
            detectionTiming.push_back(time);
        }
    }
    if (detectionTiming.size() > 0) {
        std::sort(detectionTiming.begin(), detectionTiming.end());
    } else {
        detectionTiming = BLANK_SCREEN_DETECTION_DEFAULT_TIMING;
    }
    for (auto method : arkDetectionMethods) {
        if (method == ARK_BLANK_SCREEN_DETECTION_METHOD_DETECTION_CONTENTFUL_NODES_SEVENTEEN) {
            detectionMethods.push_back(method);
        }
    }
    if (detectionMethods.size() == 0) {
        detectionMethods = { 0 };
    }
    auto contentfulNodesCountThreshold =
        Converter::OptConvert<int32_t>(optValue->contentfulNodesCountThreshold).value_or(0);
    contentfulNodesCountThreshold = contentfulNodesCountThreshold < 0 ? 0 : contentfulNodesCountThreshold;

    BlankScreenDetectionConfig config{enable, detectionTiming, detectionMethods, contentfulNodesCountThreshold};
    WebModelStatic::SetBlankScreenDetectionConfig(frameNode, config);
#endif // WEB_SUPPORTED
}

void SetZoomControlAccessImpl(Ark_NativePointer node,
                              const Opt_Boolean* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    if (!convValue) {
        WebModelStatic::SetZoomControlAccess(frameNode, false);
        return;
    }
    WebModelStatic::SetZoomControlAccess(frameNode, *convValue);
#endif // WEB_SUPPORTED
}

void SetEnableSelectedDataDetectorImpl(Ark_NativePointer node,
                                       const Opt_Boolean* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    if (!convValue) {
        WebModelStatic::SetEnableSelectedDataDetector(frameNode, true);
        return;
    }
    WebModelStatic::SetEnableSelectedDataDetector(frameNode, *convValue);
#endif // WEB_SUPPORTED
}

void SetOnTextSelectionChangeImpl(Ark_NativePointer node,
                                  const Opt_TextSelectionChangeCallback* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        return;
    }
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onTextSelectionChange = [callback = CallbackHelper(*optValue), weakNode, instanceId](
        const BaseEventInfo* info) -> void {
        OnTextSelectionChange(callback, weakNode, instanceId, info);
    };
    WebModelStatic::SetOnTextSelectionChange(frameNode, onTextSelectionChange);
#endif // WEB_SUPPORTED
}

void SetEnableImageAnalyzerImpl(Ark_NativePointer node,
                                 const Opt_Boolean* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    WebModelStatic::SetEnableImageAnalyzer(frameNode, convValue.value_or(true));
#endif // WEB_SUPPORTED
}

void SetEnableAutoFillImpl(Ark_NativePointer node,
                                 const Opt_Boolean* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    WebModelStatic::SetEnableAutoFill(frameNode, convValue.value_or(true));
#endif // WEB_SUPPORTED
}
void SetOnMicrophoneCaptureStateChangeImpl(Ark_NativePointer node,
                                           const Opt_OnMicrophoneCaptureStateChangeCallback* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        return;
    }
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onMicrophoneCaptureStateChange = [callback = CallbackHelper(*optValue), weakNode, instanceId](
        const BaseEventInfo* info) {
        OnMicrophoneCaptureStateChange(callback, weakNode, instanceId, info);
    };
    WebModelStatic::SetMicrophoneCaptureStateChangedId(frameNode, onMicrophoneCaptureStateChange);
#endif // WEB_SUPPORTED
}

void SetOnCameraCaptureStateChangeImpl(Ark_NativePointer node,
                                       const Opt_OnCameraCaptureStateChangeCallback* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        return;
    }
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onCameraCaptureStateChange = [callback = CallbackHelper(*optValue), weakNode, instanceId](
        const BaseEventInfo* info) {
        OnCameraCaptureStateChange(callback, weakNode, instanceId, info);
    };
    WebModelStatic::SetCameraCaptureStateChangedId(frameNode, onCameraCaptureStateChange);
#endif // WEB_SUPPORTED
}
} // WebAttributeModifier
const GENERATED_ArkUIWebModifier* GetWebModifier()
{
    static const GENERATED_ArkUIWebModifier ArkUIWebModifierImpl {
        WebModifier::ConstructImpl,
        WebInterfaceModifier::SetWebOptionsImpl,
        WebAttributeModifier::SetJavaScriptAccessImpl,
        WebAttributeModifier::SetFileAccessImpl,
        WebAttributeModifier::SetOnlineImageAccessImpl,
        WebAttributeModifier::SetDomStorageAccessImpl,
        WebAttributeModifier::SetImageAccessImpl,
        WebAttributeModifier::SetMixedModeImpl,
        WebAttributeModifier::SetZoomAccessImpl,
        WebAttributeModifier::SetRotateRenderEffectImpl,
        WebAttributeModifier::SetGeolocationAccessImpl,
        WebAttributeModifier::SetJavaScriptProxyImpl,
        WebAttributeModifier::SetCacheModeImpl,
        WebAttributeModifier::SetDarkModeImpl,
        WebAttributeModifier::SetForceDarkAccessImpl,
        WebAttributeModifier::SetMediaOptionsImpl,
        WebAttributeModifier::SetOverviewModeAccessImpl,
        WebAttributeModifier::SetOverScrollModeImpl,
        WebAttributeModifier::SetBlurOnKeyboardHideModeImpl,
        WebAttributeModifier::SetTextZoomRatioImpl,
        WebAttributeModifier::SetDatabaseAccessImpl,
        WebAttributeModifier::SetInitialScaleImpl,
        WebAttributeModifier::SetMetaViewportImpl,
        WebAttributeModifier::SetOnPageEndImpl,
        WebAttributeModifier::SetOnPageBeginImpl,
        WebAttributeModifier::SetOnLoadStartedImpl,
        WebAttributeModifier::SetOnLoadFinishedImpl,
        WebAttributeModifier::SetOnProgressChangeImpl,
        WebAttributeModifier::SetOnTitleReceiveImpl,
        WebAttributeModifier::SetOnGeolocationHideImpl,
        WebAttributeModifier::SetOnGeolocationShowImpl,
        WebAttributeModifier::SetOnRequestSelectedImpl,
        WebAttributeModifier::SetOnAlertImpl,
        WebAttributeModifier::SetOnBeforeUnloadImpl,
        WebAttributeModifier::SetOnConfirmImpl,
        WebAttributeModifier::SetOnPromptImpl,
        WebAttributeModifier::SetOnConsoleImpl,
        WebAttributeModifier::SetOnErrorReceiveImpl,
        WebAttributeModifier::SetOnHttpErrorReceiveImpl,
        WebAttributeModifier::SetOnOverrideErrorPageImpl,
        WebAttributeModifier::SetOnDownloadStartImpl,
        WebAttributeModifier::SetOnRefreshAccessedHistoryImpl,
        WebAttributeModifier::SetOnRenderExitedImpl,
        WebAttributeModifier::SetOnShowFileSelectorImpl,
        WebAttributeModifier::SetOnResourceLoadImpl,
        WebAttributeModifier::SetOnFullScreenExitImpl,
        WebAttributeModifier::SetOnFullScreenEnterImpl,
        WebAttributeModifier::SetOnScaleChangeImpl,
        WebAttributeModifier::SetOnHttpAuthRequestImpl,
        WebAttributeModifier::SetOnInterceptRequestImpl,
        WebAttributeModifier::SetOnPermissionRequestImpl,
        WebAttributeModifier::SetOnScreenCaptureRequestImpl,
        WebAttributeModifier::SetOnContextMenuShowImpl,
        WebAttributeModifier::SetOnContextMenuHideImpl,
        WebAttributeModifier::SetMediaPlayGestureAccessImpl,
        WebAttributeModifier::SetOnSearchResultReceiveImpl,
        WebAttributeModifier::SetOnScrollImpl,
        WebAttributeModifier::SetOnSslErrorEventReceiveImpl,
        WebAttributeModifier::SetOnSslErrorEventImpl,
        WebAttributeModifier::SetOnClientAuthenticationRequestImpl,
        WebAttributeModifier::SetOnWindowNewImpl,
        WebAttributeModifier::SetOnWindowNewExtImpl,
        WebAttributeModifier::SetOnWindowExitImpl,
        WebAttributeModifier::SetMultiWindowAccessImpl,
        WebAttributeModifier::SetOnInterceptKeyEventImpl,
        WebAttributeModifier::SetWebStandardFontImpl,
        WebAttributeModifier::SetWebSerifFontImpl,
        WebAttributeModifier::SetWebSansSerifFontImpl,
        WebAttributeModifier::SetWebFixedFontImpl,
        WebAttributeModifier::SetWebFantasyFontImpl,
        WebAttributeModifier::SetWebCursiveFontImpl,
        WebAttributeModifier::SetDefaultFixedFontSizeImpl,
        WebAttributeModifier::SetDefaultFontSizeImpl,
        WebAttributeModifier::SetMinFontSizeImpl,
        WebAttributeModifier::SetMinLogicalFontSizeImpl,
        WebAttributeModifier::SetDefaultTextEncodingFormatImpl,
        WebAttributeModifier::SetForceDisplayScrollBarImpl,
        WebAttributeModifier::SetBlockNetworkImpl,
        WebAttributeModifier::SetHorizontalScrollBarAccessImpl,
        WebAttributeModifier::SetVerticalScrollBarAccessImpl,
        WebAttributeModifier::SetOnTouchIconUrlReceivedImpl,
        WebAttributeModifier::SetOnFaviconReceivedImpl,
        WebAttributeModifier::SetOnPageVisibleImpl,
        WebAttributeModifier::SetOnDataResubmittedImpl,
        WebAttributeModifier::SetPinchSmoothImpl,
        WebAttributeModifier::SetAllowWindowOpenMethodImpl,
        WebAttributeModifier::SetOnAudioStateChangedImpl,
        WebAttributeModifier::SetOnFirstContentfulPaintImpl,
        WebAttributeModifier::SetOnFirstMeaningfulPaintImpl,
        WebAttributeModifier::SetOnLargestContentfulPaintImpl,
        WebAttributeModifier::SetOnLoadInterceptImpl,
        WebAttributeModifier::SetOnControllerAttachedImpl,
        WebAttributeModifier::SetOnOverScrollImpl,
        WebAttributeModifier::SetOnPdfScrollAtBottomImpl,
        WebAttributeModifier::SetOnPdfLoadEventImpl,
        WebAttributeModifier::SetOnSafeBrowsingCheckResultImpl,
        WebAttributeModifier::SetOnSafeBrowsingCheckFinishImpl,
        WebAttributeModifier::SetOnNavigationEntryCommittedImpl,
        WebAttributeModifier::SetOnIntelligentTrackingPreventionResultImpl,
        WebAttributeModifier::SetJavaScriptOnDocumentStartImpl,
        WebAttributeModifier::SetJavaScriptOnDocumentEndImpl,
        WebAttributeModifier::SetLayoutModeImpl,
        WebAttributeModifier::SetNestedScrollImpl,
        WebAttributeModifier::SetEnableNativeEmbedModeImpl,
        WebAttributeModifier::SetOnNativeEmbedLifecycleChangeImpl,
        WebAttributeModifier::SetOnNativeEmbedVisibilityChangeImpl,
        WebAttributeModifier::SetOnNativeEmbedGestureEventImpl,
        WebAttributeModifier::SetOnNativeEmbedMouseEventImpl,
        WebAttributeModifier::SetOnNativeEmbedObjectParamChangeImpl,
        WebAttributeModifier::SetCopyOptionsImpl,
        WebAttributeModifier::SetOnOverrideUrlLoadingImpl,
        WebAttributeModifier::SetTextAutosizingImpl,
        WebAttributeModifier::SetEnableNativeMediaPlayerImpl,
        WebAttributeModifier::SetOnRenderProcessNotRespondingImpl,
        WebAttributeModifier::SetOnRenderProcessRespondingImpl,
        WebAttributeModifier::SetOnViewportFitChangedImpl,
        WebAttributeModifier::SetOnInterceptKeyboardAttachImpl,
        WebAttributeModifier::SetOnAdsBlockedImpl,
        WebAttributeModifier::SetKeyboardAvoidModeImpl,
        WebAttributeModifier::SetEditMenuOptionsImpl,
        WebAttributeModifier::SetEnableHapticFeedbackImpl,
        WebAttributeModifier::SetOptimizeParserBudgetImpl,
        WebAttributeModifier::SetEnableFollowSystemFontWeightImpl,
        WebAttributeModifier::SetEnableWebAVSessionImpl,
        WebAttributeModifier::SetRunJavaScriptOnDocumentStartImpl,
        WebAttributeModifier::SetRunJavaScriptOnDocumentEndImpl,
        WebAttributeModifier::SetRunJavaScriptOnHeadEndImpl,
        WebAttributeModifier::SetNativeEmbedOptionsImpl,
        WebAttributeModifier::SetEnableDataDetectorImpl,
        WebAttributeModifier::SetDataDetectorConfigImpl,
        WebAttributeModifier::SetOnActivateContentImpl,
        WebAttributeModifier::SetBypassVsyncConditionImpl,
        WebAttributeModifier::SetGestureFocusModeImpl,
        WebAttributeModifier::SetForceEnableZoomImpl,
        WebAttributeModifier::SetBackToTopImpl,
        WebAttributeModifier::SetOnDetectedBlankScreenImpl,
        WebAttributeModifier::SetBlankScreenDetectionConfigImpl,
        WebAttributeModifier::SetZoomControlAccessImpl,
        WebAttributeModifier::SetEnableSelectedDataDetectorImpl,
        WebAttributeModifier::SetOnTextSelectionChangeImpl,
        WebAttributeModifier::SetEnableImageAnalyzerImpl,
        WebAttributeModifier::SetEnableAutoFillImpl,
        WebAttributeModifier::SetOnMicrophoneCaptureStateChangeImpl,
        WebAttributeModifier::SetOnCameraCaptureStateChangeImpl,
        WebAttributeModifier::SetRegisterNativeEmbedRuleImpl,
        WebAttributeModifier::SetBindSelectionMenuImpl,
    };
    return &ArkUIWebModifierImpl;
}

}

