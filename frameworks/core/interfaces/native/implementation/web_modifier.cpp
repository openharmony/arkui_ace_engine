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

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/text_field/text_selector.h"
#ifdef WEB_SUPPORTED
#include "core/components_ng/pattern/web/web_model_ng.h"
#include "core/interfaces/native/implementation/web_controller_peer_impl.h"
#include "core/interfaces/native/implementation/webview_controller_peer_impl.h"
#include "core/interfaces/native/implementation/web_modifier_callbacks.h"
#endif // WEB_SUPPORTED
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "arkoala_api_generated.h"

using namespace OHOS::Ace::NG::Converter;

namespace {
#ifdef WEB_SUPPORTED
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
#endif // WEB_SUPPORTED
} // namespace

namespace OHOS::Ace {
using ScriptItem = std::pair<std::string, std::vector<std::string>>;
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

template<>
MenuOptionsParam Convert(const Ark_ExpandedMenuItemOptions& src)
{
    MenuOptionsParam menuOption;
    menuOption.content = Converter::OptConvert<std::string>(src.content);
    menuOption.icon = Converter::OptConvert<std::string>(src.startIcon);
    return menuOption;
}

void AssignArkValue(Ark_NativeEmbedInfo& dst, const EmbedInfo& src)
{
    dst.width = Converter::ArkValue<Opt_Number>(src.width);
    dst.height = Converter::ArkValue<Opt_Number>(src.height);
    dst.id = Converter::ArkValue<Opt_String>(src.id);
    dst.src = Converter::ArkValue<Opt_String>(src.src);
    dst.tag = Converter::ArkValue<Opt_String>(src.tag);
    dst.type = Converter::ArkValue<Opt_String>(src.type);
    dst.url = Converter::ArkValue<Opt_String>(src.url);
    Ark_Position position;
    position.x = Converter::ArkValue<Opt_Length>(src.x);
    position.y = Converter::ArkValue<Opt_Length>(src.y);
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
    auto frameNode = WebModelNG::CreateFrameNode(id);
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
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto webSrc = Converter::OptConvert<std::string>(value->src);
    WebModelNG::SetWebSrc(frameNode, webSrc);
    auto renderMode = Converter::OptConvert<RenderMode>(value->renderMode);
    WebModelNG::SetRenderMode(frameNode, renderMode);
    auto incognitoMode = Converter::OptConvert<bool>(value->incognitoMode);
    WebModelNG::SetIncognitoMode(frameNode, incognitoMode);
    auto sharedRenderProcessToken = Converter::OptConvert<std::string>(value->sharedRenderProcessToken);
    WebModelNG::SetSharedRenderProcessToken(frameNode, sharedRenderProcessToken);
    Converter::VisitUnion(value->controller,
        [frameNode](const Ark_WebController& controller) {
            auto peerImplPtr = controller;
            CHECK_NULL_VOID(peerImplPtr);
            WebModelNG::SetWebController(frameNode, peerImplPtr->GetController());
        },
        [frameNode](const Ark_WebviewController& controller) {
            (void)controller;
        },
        []() {}
    );
#endif // WEB_SUPPORTED
}
} // WebInterfaceModifier
namespace WebAttributeModifier {
void JavaScriptAccessImpl(Ark_NativePointer node,
                          const Opt_Boolean* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(transValue);
    WebModelNG::SetJsEnabled(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void FileAccessImpl(Ark_NativePointer node,
                    const Opt_Boolean* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(transValue);
    WebModelNG::SetFileAccessEnabled(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void OnlineImageAccessImpl(Ark_NativePointer node,
                           const Opt_Boolean* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(transValue);
    WebModelNG::SetOnLineImageAccessEnabled(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void DomStorageAccessImpl(Ark_NativePointer node,
                          const Opt_Boolean* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(transValue);
    WebModelNG::SetDomStorageAccessEnabled(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void ImageAccessImpl(Ark_NativePointer node,
                     const Opt_Boolean* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(transValue);
    WebModelNG::SetImageAccessEnabled(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void MixedModeImpl(Ark_NativePointer node,
                   const Opt_MixedMode* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<MixedModeContent>(transValue);
    WebModelNG::SetMixedMode(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void ZoomAccessImpl(Ark_NativePointer node,
                    const Opt_Boolean* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(transValue);
    WebModelNG::SetZoomAccessEnabled(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void GeolocationAccessImpl(Ark_NativePointer node,
                           const Opt_Boolean* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(transValue);
    WebModelNG::SetGeolocationAccessEnabled(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void JavaScriptProxyImpl(Ark_NativePointer node,
                         const Opt_JavaScriptProxy* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    LOGE("WebInterfaceModifier::JavaScriptProxyImpl method is not implemented");
}
void PasswordImpl(Ark_NativePointer node,
                  const Opt_Boolean* value)
{
}
void CacheModeImpl(Ark_NativePointer node,
                   const Opt_CacheMode* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<WebCacheMode>(transValue);
    WebModelNG::SetCacheMode(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void DarkModeImpl(Ark_NativePointer node,
                  const Opt_WebDarkMode* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<WebDarkMode>(transValue);
    WebModelNG::SetDarkMode(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void ForceDarkAccessImpl(Ark_NativePointer node,
                         const Opt_Boolean* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(transValue);
    WebModelNG::SetForceDarkAccess(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void MediaOptionsImpl(Ark_NativePointer node,
                      const Opt_WebMediaOptions* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetAudioResumeInterval(frameNode, Converter::OptConvert<int32_t>(transValue.resumeInterval));
    WebModelNG::SetAudioExclusive(frameNode, Converter::OptConvert<bool>(transValue.audioExclusive));
#endif // WEB_SUPPORTED
}
void TableDataImpl(Ark_NativePointer node,
                   const Opt_Boolean* value)
{
}
void WideViewModeAccessImpl(Ark_NativePointer node,
                            const Opt_Boolean* value)
{
}
void OverviewModeAccessImpl(Ark_NativePointer node,
                            const Opt_Boolean* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(transValue);
    WebModelNG::SetOverviewModeAccessEnabled(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void OverScrollModeImpl(Ark_NativePointer node,
                        const Opt_OverScrollMode* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<OverScrollMode>(transValue);
    WebModelNG::SetOverScrollMode(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void BlurOnKeyboardHideModeImpl(Ark_NativePointer node,
                                const Opt_BlurOnKeyboardHideMode* value)
{
}
void TextZoomAtioImpl(Ark_NativePointer node,
                      const Opt_Number* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<int32_t>(transValue);
    WebModelNG::SetTextZoomRatio(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void TextZoomRatioImpl(Ark_NativePointer node,
                       const Opt_Number* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<int32_t>(transValue);
    WebModelNG::SetTextZoomRatio(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void DatabaseAccessImpl(Ark_NativePointer node,
                        const Opt_Boolean* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(transValue);
    WebModelNG::SetDatabaseAccessEnabled(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void InitialScaleImpl(Ark_NativePointer node,
                      const Opt_Number* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<float>(transValue);
    WebModelNG::InitialScale(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void UserAgentImpl(Ark_NativePointer node,
                   const Opt_String* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<std::string>(transValue);
    WebModelNG::SetUserAgent(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void MetaViewportImpl(Ark_NativePointer node,
                      const Opt_Boolean* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(transValue);
    WebModelNG::SetMetaViewport(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void OnPageEndImpl(Ark_NativePointer node,
                   const Opt_Callback_OnPageEndEvent_Void* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onPageEnd = [callback = CallbackHelper(transValue), weakNode, instanceId] (const BaseEventInfo* info) {
        OnPageEnd(callback, weakNode, instanceId, info);
    };
    WebModelNG::SetOnPageFinish(frameNode, std::move(onPageEnd));
#endif // WEB_SUPPORTED
}
void OnPageBeginImpl(Ark_NativePointer node,
                     const Opt_Callback_OnPageBeginEvent_Void* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onPageBegin = [callback = CallbackHelper(transValue), weakNode, instanceId](const BaseEventInfo* info) {
        OnPageBegin(callback, weakNode, instanceId, info);
    };
    WebModelNG::SetOnPageStart(frameNode, onPageBegin);
#endif // WEB_SUPPORTED
}
void OnProgressChangeImpl(Ark_NativePointer node,
                          const Opt_Callback_OnProgressChangeEvent_Void* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onProgressChange = [callback = CallbackHelper(transValue), weakNode, instanceId](const BaseEventInfo* info) {
        OnProgressChange(callback, weakNode, instanceId, info);
    };
    WebModelNG::SetOnProgressChange(frameNode, onProgressChange);
#endif // WEB_SUPPORTED
}
void OnTitleReceiveImpl(Ark_NativePointer node,
                        const Opt_Callback_OnTitleReceiveEvent_Void* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onTitleReceive = [callback = CallbackHelper(transValue), weakNode, instanceId](const BaseEventInfo* info) {
        OnTitleReceive(callback, weakNode, instanceId, info);
    };
    WebModelNG::SetOnTitleReceive(frameNode, onTitleReceive);
#endif // WEB_SUPPORTED
}
void OnGeolocationHideImpl(Ark_NativePointer node,
                           const Opt_Callback_Void* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onGeolocationHide = [callback = CallbackHelper(transValue), weakNode, instanceId](const BaseEventInfo* info) {
        OnGeolocationHide(callback, weakNode, instanceId, info);
    };
    WebModelNG::SetOnGeolocationHide(frameNode, onGeolocationHide);
#endif // WEB_SUPPORTED
}
void OnGeolocationShowImpl(Ark_NativePointer node,
                           const Opt_Callback_OnGeolocationShowEvent_Void* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onGeolocationShow = [callback = CallbackHelper(transValue), weakNode, instanceId](const BaseEventInfo* info) {
        OnGeolocationShow(callback, weakNode, instanceId, info);
    };
    WebModelNG::SetOnGeolocationShow(frameNode, onGeolocationShow);
#endif // WEB_SUPPORTED
}
void OnRequestSelectedImpl(Ark_NativePointer node,
                           const Opt_Callback_Void* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onRequestSelected = [callback = CallbackHelper(transValue), weakNode](const BaseEventInfo* info) {
        OnRequestSelected(callback, weakNode, info);
    };
    WebModelNG::SetOnRequestFocus(frameNode, onRequestSelected);
#endif // WEB_SUPPORTED
}
void OnAlertImpl(Ark_NativePointer node,
                 const Opt_Callback_OnAlertEvent_Boolean* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onAlert = [callback = CallbackHelper(transValue), weakNode, instanceId](const BaseEventInfo* info) -> bool {
        return OnAlert(callback, weakNode, instanceId, info);
    };
    WebModelNG::SetOnCommonDialog(frameNode, onAlert, DialogEventType::DIALOG_EVENT_ALERT);
#endif // WEB_SUPPORTED
}
void OnBeforeUnloadImpl(Ark_NativePointer node,
                        const Opt_Callback_OnBeforeUnloadEvent_Boolean* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onBeforeUnload = [callback = CallbackHelper(transValue), weakNode, instanceId](
                              const BaseEventInfo* info) -> bool {
        return OnBeforeUnload(callback, weakNode, instanceId, info);
    };
    WebModelNG::SetOnCommonDialog(frameNode, onBeforeUnload, DialogEventType::DIALOG_EVENT_BEFORE_UNLOAD);
#endif // WEB_SUPPORTED
}
void OnConfirmImpl(Ark_NativePointer node,
                   const Opt_Callback_OnConfirmEvent_Boolean* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onConfirm = [callback = CallbackHelper(transValue), weakNode, instanceId](const BaseEventInfo* info) -> bool {
        return OnConfirm(callback, weakNode, instanceId, info);
    };
    WebModelNG::SetOnCommonDialog(frameNode, onConfirm, DialogEventType::DIALOG_EVENT_CONFIRM);
#endif // WEB_SUPPORTED
}
void OnPromptImpl(Ark_NativePointer node,
                  const Opt_Callback_OnPromptEvent_Boolean* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onPrompt = [callback = CallbackHelper(transValue), weakNode, instanceId](const BaseEventInfo* info) -> bool {
        return OnPrompt(callback, weakNode, instanceId, info);
    };
    WebModelNG::SetOnCommonDialog(frameNode, onPrompt, DialogEventType::DIALOG_EVENT_PROMPT);
#endif // WEB_SUPPORTED
}
void OnConsoleImpl(Ark_NativePointer node,
                   const Opt_Callback_OnConsoleEvent_Boolean* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onConsole = [callback = CallbackHelper(transValue), weakNode](const BaseEventInfo* info) -> bool {
        return OnConsole(callback, weakNode, info);
    };
    WebModelNG::SetOnConsoleLog(frameNode, onConsole);
#endif // WEB_SUPPORTED
}
void OnErrorReceiveImpl(Ark_NativePointer node,
                        const Opt_Callback_OnErrorReceiveEvent_Void* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onErrorReceive = [callback = CallbackHelper(transValue), weakNode, instanceId](const BaseEventInfo* info) {
        OnErrorReceive(callback, weakNode, instanceId, info);
    };
    WebModelNG::SetOnErrorReceive(frameNode, onErrorReceive);
#endif // WEB_SUPPORTED
}
void OnHttpErrorReceiveImpl(Ark_NativePointer node,
                            const Opt_Callback_OnHttpErrorReceiveEvent_Void* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onHttpErrorReceive = [callback = CallbackHelper(transValue), weakNode, instanceId](const BaseEventInfo* info) {
        OnHttpErrorReceive(callback, weakNode, instanceId, info);
    };
    WebModelNG::SetOnHttpErrorReceive(frameNode, onHttpErrorReceive);
#endif // WEB_SUPPORTED
}
void OnDownloadStartImpl(Ark_NativePointer node,
                         const Opt_Callback_OnDownloadStartEvent_Void* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onDownloadStart = [callback = CallbackHelper(transValue), weakNode, instanceId](const BaseEventInfo* info) {
        OnDownloadStart(callback, weakNode, instanceId, info);
    };
    WebModelNG::SetOnDownloadStart(frameNode, onDownloadStart);
#endif // WEB_SUPPORTED
}
void OnRefreshAccessedHistoryImpl(Ark_NativePointer node,
                                  const Opt_Callback_OnRefreshAccessedHistoryEvent_Void* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onRefreshAccessedHistory =
        [callback = CallbackHelper(transValue), weakNode, instanceId](const BaseEventInfo* info) {
            OnRefreshAccessedHistory(callback, weakNode, instanceId, info);
        };
    WebModelNG::SetRefreshAccessedHistoryId(frameNode, onRefreshAccessedHistory);
#endif // WEB_SUPPORTED
}
void OnUrlLoadInterceptImpl(Ark_NativePointer node,
                            const Opt_Type_WebAttribute_onUrlLoadIntercept_callback* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onUrlLoadIntercept =
        [callback = CallbackHelper(transValue), weakNode, instanceId](const BaseEventInfo* info) -> bool {
            return OnUrlLoadIntercept(callback, weakNode, instanceId, info);
        };
    WebModelNG::SetOnUrlLoadIntercept(frameNode, onUrlLoadIntercept);
#endif // WEB_SUPPORTED
}
void OnSslErrorReceiveImpl(Ark_NativePointer node,
                           const Opt_Callback_Literal_Function_handler_Object_error_Void* value)
{
}
void OnRenderExited0Impl(Ark_NativePointer node,
                         const Opt_Callback_OnRenderExitedEvent_Void* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onRenderExited = [callback = CallbackHelper(transValue), weakNode, instanceId]
        (const BaseEventInfo* info) {
        OnRenderExited(callback, weakNode, instanceId, info);
    };
    WebModelNG::SetRenderExitedId(frameNode, onRenderExited);
#endif // WEB_SUPPORTED
}
void OnRenderExited1Impl(Ark_NativePointer node,
                         const Opt_Callback_Literal_Object_detail_Boolean* value)
{
}
void OnShowFileSelectorImpl(Ark_NativePointer node,
                            const Opt_Callback_OnShowFileSelectorEvent_Boolean* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onShowFileSelector =
        [callback = CallbackHelper(transValue), weakNode, instanceId](const BaseEventInfo* info) -> bool {
            return OnShowFileSelector(callback, weakNode, instanceId, info);
        };
    WebModelNG::SetOnFileSelectorShow(frameNode, onShowFileSelector);
#endif // WEB_SUPPORTED
}
void OnFileSelectorShowImpl(Ark_NativePointer node,
                            const Opt_Type_WebAttribute_onFileSelectorShow_callback* value)
{
}
void OnResourceLoadImpl(Ark_NativePointer node,
                        const Opt_Callback_OnResourceLoadEvent_Void* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onResourceLoad = [callback = CallbackHelper(transValue), weakNode, instanceId](const BaseEventInfo* info) {
        OnResourceLoad(callback, weakNode, instanceId, info);
    };
    WebModelNG::SetResourceLoadId(frameNode, onResourceLoad);
#endif // WEB_SUPPORTED
}
void OnFullScreenExitImpl(Ark_NativePointer node,
                          const Opt_Callback_Void* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onFullScreenExit = [callback = CallbackHelper(transValue), weakNode, instanceId](const BaseEventInfo* info) {
        OnFullScreenExit(callback, weakNode, instanceId, info);
    };
    WebModelNG::SetOnFullScreenExit(frameNode, onFullScreenExit);
#endif // WEB_SUPPORTED
}
void OnFullScreenEnterImpl(Ark_NativePointer node,
                           const Opt_OnFullScreenEnterCallback* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onFullScreenEnter = [callback = CallbackHelper(transValue), weakNode, instanceId](const BaseEventInfo* info) {
        OnFullScreenEnter(callback, weakNode, instanceId, info);
    };
    WebModelNG::SetOnFullScreenEnter(frameNode, onFullScreenEnter);
#endif // WEB_SUPPORTED
}
void OnScaleChangeImpl(Ark_NativePointer node,
                       const Opt_Callback_OnScaleChangeEvent_Void* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onScaleChange = [callback = CallbackHelper(transValue), weakNode, instanceId](const BaseEventInfo* info) {
        OnScaleChange(callback, weakNode, instanceId, info);
    };
    WebModelNG::SetScaleChangeId(frameNode, onScaleChange);
#endif // WEB_SUPPORTED
}
void OnHttpAuthRequestImpl(Ark_NativePointer node,
                           const Opt_Callback_OnHttpAuthRequestEvent_Boolean* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onHttpAuthRequest =
        [callback = CallbackHelper(transValue), weakNode, instanceId](const BaseEventInfo* info) -> bool {
            return OnHttpAuthRequest(callback, weakNode, instanceId, info);
        };
    WebModelNG::SetOnHttpAuthRequest(frameNode, onHttpAuthRequest);
#endif // WEB_SUPPORTED
}
void OnInterceptRequestImpl(Ark_NativePointer node,
                            const Opt_Callback_OnInterceptRequestEvent_WebResourceResponse* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onInterceptRequest = [callback = CallbackHelper(transValue), weakNode, instanceId](
                                  const BaseEventInfo* info) -> RefPtr<WebResponse> {
        return OnInterceptRequest(callback, weakNode, instanceId, info);
    };
    WebModelNG::SetOnInterceptRequest(frameNode, onInterceptRequest);
#endif // WEB_SUPPORTED
}
void OnPermissionRequestImpl(Ark_NativePointer node,
                             const Opt_Callback_OnPermissionRequestEvent_Void* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onPermissionRequest = [callback = CallbackHelper(transValue), weakNode, instanceId](
                                   const BaseEventInfo* info) {
        OnPermissionRequest(callback, weakNode, instanceId, info);
    };
    WebModelNG::SetPermissionRequestEventId(frameNode, onPermissionRequest);
#endif // WEB_SUPPORTED
}
void OnScreenCaptureRequestImpl(Ark_NativePointer node,
                                const Opt_Callback_OnScreenCaptureRequestEvent_Void* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onScreenCaptureRequest = [callback = CallbackHelper(transValue), weakNode, instanceId](
                                      const BaseEventInfo* info) {
        OnScreenCaptureRequest(callback, weakNode, instanceId, info);
    };
    WebModelNG::SetScreenCaptureRequestEventId(frameNode, onScreenCaptureRequest);
#endif // WEB_SUPPORTED
}
void OnContextMenuShowImpl(Ark_NativePointer node,
                           const Opt_Callback_OnContextMenuShowEvent_Boolean* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onContextMenuShow =
        [callback = CallbackHelper(transValue), weakNode, instanceId](const BaseEventInfo* info) -> bool {
            return OnContextMenuShow(callback, weakNode, instanceId, info);
        };
    WebModelNG::SetOnContextMenuShow(frameNode, onContextMenuShow);
#endif // WEB_SUPPORTED
}
void OnContextMenuHideImpl(Ark_NativePointer node,
                           const Opt_OnContextMenuHideCallback* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onContextMenuHide = [callback = CallbackHelper(transValue), weakNode, instanceId](const BaseEventInfo* info) {
        OnContextMenuHide(callback, weakNode, instanceId, info);
    };
    WebModelNG::SetOnContextMenuHide(frameNode, onContextMenuHide);
#endif // WEB_SUPPORTED
}
void MediaPlayGestureAccessImpl(Ark_NativePointer node,
                                const Opt_Boolean* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(transValue);
    WebModelNG::SetMediaPlayGestureAccess(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void OnSearchResultReceiveImpl(Ark_NativePointer node,
                               const Opt_Callback_OnSearchResultReceiveEvent_Void* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onSearchResultReceive = [callback = CallbackHelper(transValue), weakNode, instanceId](
                                     const BaseEventInfo* info) {
        OnSearchResultReceive(callback, weakNode, instanceId, info);
    };
    WebModelNG::SetSearchResultReceiveEventId(frameNode, onSearchResultReceive);
#endif // WEB_SUPPORTED
}
void OnScrollImpl(Ark_NativePointer node,
                  const Opt_Callback_OnScrollEvent_Void* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onScroll = [callback = CallbackHelper(transValue), weakNode, instanceId](const BaseEventInfo* info) {
        OnScroll(callback, weakNode, instanceId, info);
    };
    WebModelNG::SetScrollId(frameNode, onScroll);
#endif // WEB_SUPPORTED
}
void OnSslErrorEventReceiveImpl(Ark_NativePointer node,
                                const Opt_Callback_OnSslErrorEventReceiveEvent_Void* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onSslErrorEventReceive =
        [callback = CallbackHelper(transValue), weakNode, instanceId](const BaseEventInfo* info) -> bool {
            return OnSslErrorEventReceive(callback, weakNode, instanceId, info);
        };
    WebModelNG::SetOnSslErrorRequest(frameNode, onSslErrorEventReceive);
#endif // WEB_SUPPORTED
}
void OnSslErrorEventImpl(Ark_NativePointer node,
                         const Opt_OnSslErrorEventCallback* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onSslErrorEvent =
        [callback = CallbackHelper(transValue), weakNode, instanceId](const BaseEventInfo* info) -> bool {
            return OnSslError(callback, weakNode, instanceId, info);
        };
    WebModelNG::SetOnAllSslErrorRequest(frameNode, onSslErrorEvent);
#endif // WEB_SUPPORTED
}
void OnClientAuthenticationRequestImpl(Ark_NativePointer node,
                                       const Opt_Callback_OnClientAuthenticationEvent_Void* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onClientAuthenticationRequest =
        [callback = CallbackHelper(transValue), weakNode, instanceId](const BaseEventInfo* info) -> bool {
            return OnClientAuthentication(callback, weakNode, instanceId, info);
        };
    WebModelNG::SetOnSslSelectCertRequest(frameNode, onClientAuthenticationRequest);
#endif // WEB_SUPPORTED
}
void OnWindowNewImpl(Ark_NativePointer node,
                     const Opt_Callback_OnWindowNewEvent_Void* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onWindowNew =
        [callback = CallbackHelper(transValue), weakNode, instanceId](const std::shared_ptr<BaseEventInfo>& info) {
            OnWindowNew(callback, weakNode, instanceId, info);
        };
    WebModelNG::SetWindowNewEvent(frameNode, onWindowNew);
#endif // WEB_SUPPORTED
}
void OnWindowExitImpl(Ark_NativePointer node,
                      const Opt_Callback_Void* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onWindowExit = [callback = CallbackHelper(transValue), weakNode, instanceId](const BaseEventInfo* info) {
        OnWindowExit(callback, weakNode, instanceId, info);
    };
    WebModelNG::SetWindowExitEventId(frameNode, onWindowExit);
#endif // WEB_SUPPORTED
}
void MultiWindowAccessImpl(Ark_NativePointer node,
                           const Opt_Boolean* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(transValue);
    WebModelNG::SetMultiWindowAccessEnabled(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void OnInterceptKeyEventImpl(Ark_NativePointer node,
                             const Opt_Callback_KeyEvent_Boolean* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onInterceptKeyEvent = [callback = CallbackHelper(transValue), weakNode](KeyEventInfo& keyEventInfo) -> bool {
        return OnInterceptKey(callback, weakNode, keyEventInfo);
    };
    WebModelNG::SetOnInterceptKeyEventCallback(frameNode, onInterceptKeyEvent);
#endif // WEB_SUPPORTED
}
void WebStandardFontImpl(Ark_NativePointer node,
                         const Opt_String* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<std::string>(transValue);
    WebModelNG::SetWebStandardFont(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void WebSerifFontImpl(Ark_NativePointer node,
                      const Opt_String* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<std::string>(transValue);
    WebModelNG::SetWebSerifFont(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void WebSansSerifFontImpl(Ark_NativePointer node,
                          const Opt_String* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<std::string>(transValue);
    WebModelNG::SetWebSansSerifFont(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void WebFixedFontImpl(Ark_NativePointer node,
                      const Opt_String* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<std::string>(transValue);
    WebModelNG::SetWebFixedFont(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void WebFantasyFontImpl(Ark_NativePointer node,
                        const Opt_String* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<std::string>(transValue);
    WebModelNG::SetWebFantasyFont(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void WebCursiveFontImpl(Ark_NativePointer node,
                        const Opt_String* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<std::string>(transValue);
    WebModelNG::SetWebCursiveFont(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void DefaultFixedFontSizeImpl(Ark_NativePointer node,
                              const Opt_Number* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<int32_t>(transValue);
    WebModelNG::SetDefaultFixedFontSize(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void DefaultFontSizeImpl(Ark_NativePointer node,
                         const Opt_Number* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<int32_t>(transValue);
    WebModelNG::SetDefaultFontSize(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void MinFontSizeImpl(Ark_NativePointer node,
                     const Opt_Number* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<int32_t>(transValue);
    WebModelNG::SetMinFontSize(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void MinLogicalFontSizeImpl(Ark_NativePointer node,
                            const Opt_Number* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<int32_t>(transValue);
    WebModelNG::SetMinLogicalFontSize(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void DefaultTextEncodingFormatImpl(Ark_NativePointer node,
                                   const Opt_String* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<std::string>(transValue);
    EraseSpace(convValue);
    WebModelNG::SetDefaultTextEncodingFormat(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void ForceDisplayScrollBarImpl(Ark_NativePointer node,
                               const Opt_Boolean* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(transValue);
    WebModelNG::SetOverlayScrollbarEnabled(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void BlockNetworkImpl(Ark_NativePointer node,
                      const Opt_Boolean* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(transValue);
    WebModelNG::SetBlockNetwork(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void HorizontalScrollBarAccessImpl(Ark_NativePointer node,
                                   const Opt_Boolean* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(transValue);
    WebModelNG::SetHorizontalScrollBarAccessEnabled(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void VerticalScrollBarAccessImpl(Ark_NativePointer node,
                                 const Opt_Boolean* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(transValue);
    WebModelNG::SetVerticalScrollBarAccessEnabled(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void OnTouchIconUrlReceivedImpl(Ark_NativePointer node,
                                const Opt_Callback_OnTouchIconUrlReceivedEvent_Void* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onTouchIconUrlReceived =
        [callback = CallbackHelper(transValue), weakNode, instanceId](const std::shared_ptr<BaseEventInfo>& info) {
            OnTouchIconUrlReceived(callback, weakNode, instanceId, info);
        };
    WebModelNG::SetTouchIconUrlId(frameNode, onTouchIconUrlReceived);
#endif // WEB_SUPPORTED
}
void OnFaviconReceivedImpl(Ark_NativePointer node,
                           const Opt_Callback_OnFaviconReceivedEvent_Void* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onFaviconReceived =
        [callback = CallbackHelper(transValue), weakNode, instanceId](const std::shared_ptr<BaseEventInfo>& info) {
            OnFaviconReceived(callback, weakNode, instanceId, info);
        };
    WebModelNG::SetFaviconReceivedId(frameNode, onFaviconReceived);
#endif // WEB_SUPPORTED
}
void OnPageVisibleImpl(Ark_NativePointer node,
                       const Opt_Callback_OnPageVisibleEvent_Void* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onPageVisible =
        [callback = CallbackHelper(transValue), weakNode, instanceId](const std::shared_ptr<BaseEventInfo>& info) {
            OnPageVisible(callback, weakNode, instanceId, info);
        };
    WebModelNG::SetPageVisibleId(frameNode, std::move(onPageVisible));
#endif // WEB_SUPPORTED
}
void OnDataResubmittedImpl(Ark_NativePointer node,
                           const Opt_Callback_OnDataResubmittedEvent_Void* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onDataResubmitted =
        [callback = CallbackHelper(transValue), weakNode, instanceId](const std::shared_ptr<BaseEventInfo>& info) {
            OnDataResubmitted(callback, weakNode, instanceId, info);
        };
    WebModelNG::SetOnDataResubmitted(frameNode, onDataResubmitted);
#endif // WEB_SUPPORTED
}
void PinchSmoothImpl(Ark_NativePointer node,
                     const Opt_Boolean* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(transValue);
    WebModelNG::SetPinchSmoothModeEnabled(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void AllowWindowOpenMethodImpl(Ark_NativePointer node,
                               const Opt_Boolean* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(transValue);
    WebModelNG::SetAllowWindowOpenMethod(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void OnAudioStateChangedImpl(Ark_NativePointer node,
                             const Opt_Callback_OnAudioStateChangedEvent_Void* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onAudioStateChanged =
        [callback = CallbackHelper(transValue), weakNode, instanceId](const std::shared_ptr<BaseEventInfo>& info) {
            OnAudioStateChanged(callback, weakNode, instanceId, info);
        };
    WebModelNG::SetAudioStateChangedId(frameNode, onAudioStateChanged);
#endif // WEB_SUPPORTED
}
void OnFirstContentfulPaintImpl(Ark_NativePointer node,
                                const Opt_Callback_OnFirstContentfulPaintEvent_Void* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onFirstContentfulPaint =
        [callback = CallbackHelper(transValue), weakNode, instanceId](const std::shared_ptr<BaseEventInfo>& info) {
            OnFirstContentfulPaint(callback, weakNode, instanceId, info);
        };
    WebModelNG::SetFirstContentfulPaintId(frameNode, std::move(onFirstContentfulPaint));
#endif // WEB_SUPPORTED
}
void OnFirstMeaningfulPaintImpl(Ark_NativePointer node,
                                const Opt_OnFirstMeaningfulPaintCallback* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onFirstMeaningfulPaint =
        [callback = CallbackHelper(transValue), weakNode, instanceId](const std::shared_ptr<BaseEventInfo>& info) {
            OnFirstMeaningfulPaint(callback, weakNode, instanceId, info);
        };
    WebModelNG::SetFirstMeaningfulPaintId(frameNode, std::move(onFirstMeaningfulPaint));
#endif // WEB_SUPPORTED
}
void OnLargestContentfulPaintImpl(Ark_NativePointer node,
                                  const Opt_OnLargestContentfulPaintCallback* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onLargestContentfulPaint =
        [callback = CallbackHelper(transValue), weakNode, instanceId](const std::shared_ptr<BaseEventInfo>& info) {
            OnLargestContentfulPaint(callback, weakNode, instanceId, info);
        };
    WebModelNG::SetLargestContentfulPaintId(frameNode, std::move(onLargestContentfulPaint));
#endif // WEB_SUPPORTED
}
void OnLoadInterceptImpl(Ark_NativePointer node,
                         const Opt_Callback_OnLoadInterceptEvent_Boolean* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onLoadIntercept =
        [callback = CallbackHelper(transValue), weakNode, instanceId](const BaseEventInfo* info) -> bool {
            return OnLoadIntercept(callback, weakNode, instanceId, info);
        };
    WebModelNG::SetOnLoadIntercept(frameNode, std::move(onLoadIntercept));
#endif // WEB_SUPPORTED
}
void OnControllerAttachedImpl(Ark_NativePointer node,
                              const Opt_Callback_Void* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onControllerAttached = [callback = CallbackHelper(transValue), weakNode, instanceId]() {
        OnControllerAttached(callback, weakNode, instanceId);
    };
    WebModelNG::SetOnControllerAttached(frameNode, std::move(onControllerAttached));
#endif // WEB_SUPPORTED
}
void OnOverScrollImpl(Ark_NativePointer node,
                      const Opt_Callback_OnOverScrollEvent_Void* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onOverScroll = [callback = CallbackHelper(transValue), weakNode, instanceId](const BaseEventInfo* info) {
        OnOverScroll(callback, weakNode, instanceId, info);
    };
    WebModelNG::SetOverScrollId(frameNode, onOverScroll);
#endif // WEB_SUPPORTED
}
void OnSafeBrowsingCheckResultImpl(Ark_NativePointer node,
                                   const Opt_OnSafeBrowsingCheckResultCallback* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onSafeBrowsingCheckResult =
        [callback = CallbackHelper(transValue), weakNode, instanceId](const std::shared_ptr<BaseEventInfo>& info) {
            OnSafeBrowsingCheckResult(callback, weakNode, instanceId, info);
        };
    WebModelNG::SetSafeBrowsingCheckResultId(frameNode, std::move(onSafeBrowsingCheckResult));
#endif // WEB_SUPPORTED
}
void OnNavigationEntryCommittedImpl(Ark_NativePointer node,
                                    const Opt_OnNavigationEntryCommittedCallback* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onNavigationEntryCommitted =
        [callback = CallbackHelper(transValue), weakNode, instanceId](const std::shared_ptr<BaseEventInfo>& info) {
            OnNavigationEntryCommitted(callback, weakNode, instanceId, info);
        };
    WebModelNG::SetNavigationEntryCommittedId(frameNode, std::move(onNavigationEntryCommitted));
#endif // WEB_SUPPORTED
}
void OnIntelligentTrackingPreventionResultImpl(Ark_NativePointer node,
                                               const Opt_OnIntelligentTrackingPreventionCallback* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onIntelligentTrackingPreventionResult = [callback = CallbackHelper(transValue), weakNode, instanceId](
        const std::shared_ptr<BaseEventInfo>& info) {
        OnIntelligentTrackingPrevention(callback, weakNode, instanceId, info);
    };
    WebModelNG::SetIntelligentTrackingPreventionResultId(frameNode, std::move(onIntelligentTrackingPreventionResult));
#endif // WEB_SUPPORTED
}
void JavaScriptOnDocumentStartImpl(Ark_NativePointer node,
                                   const Opt_Array_ScriptItem* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<ScriptItems>(transValue);
    WebModelNG::JavaScriptOnDocumentStart(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void JavaScriptOnDocumentEndImpl(Ark_NativePointer node,
                                 const Opt_Array_ScriptItem* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<ScriptItems>(transValue);
    WebModelNG::JavaScriptOnDocumentEnd(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void LayoutModeImpl(Ark_NativePointer node,
                    const Opt_WebLayoutMode* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<WebLayoutMode>(transValue);
    WebModelNG::SetLayoutMode(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void NestedScrollImpl(Ark_NativePointer node,
                      const Opt_Union_NestedScrollOptions_NestedScrollOptionsExt* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<NestedScrollOptionsExt>(transValue);
    WebModelNG::SetNestedScrollExt(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void EnableNativeEmbedModeImpl(Ark_NativePointer node,
                               const Opt_Boolean* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(transValue);
    WebModelNG::SetNativeEmbedModeEnabled(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void OnNativeEmbedLifecycleChangeImpl(Ark_NativePointer node,
                                      const Opt_Callback_NativeEmbedDataInfo_Void* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto instanceId = Container::CurrentId();
    auto onNativeEmbedLifecycleChange = [callback = CallbackHelper(transValue), instanceId](const BaseEventInfo* info) {
        OnNativeEmbedDataInfo(callback, instanceId, info);
    };
    WebModelNG::SetNativeEmbedLifecycleChangeId(frameNode, onNativeEmbedLifecycleChange);
#endif // WEB_SUPPORTED
}
void OnNativeEmbedVisibilityChangeImpl(Ark_NativePointer node,
                                       const Opt_OnNativeEmbedVisibilityChangeCallback* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto instanceId = Container::CurrentId();
    auto onNativeEmbedVisibilityChange = [callback = CallbackHelper(transValue), instanceId](
                                             const BaseEventInfo* info) {
        OnNativeEmbedVisibilityChange(callback, instanceId, info);
    };
    WebModelNG::SetNativeEmbedVisibilityChangeId(frameNode, onNativeEmbedVisibilityChange);
#endif // WEB_SUPPORTED
}
void OnNativeEmbedGestureEventImpl(Ark_NativePointer node,
                                   const Opt_Callback_NativeEmbedTouchInfo_Void* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto instanceId = Container::CurrentId();
    auto onNativeEmbedGestureEvent = [callback = CallbackHelper(transValue), instanceId](const BaseEventInfo* info) {
        OnNativeEmbedTouchInfo(callback, instanceId, info);
    };
    WebModelNG::SetNativeEmbedGestureEventId(frameNode, onNativeEmbedGestureEvent);
#endif // WEB_SUPPORTED
}
void CopyOptionsImpl(Ark_NativePointer node,
                     const Opt_CopyOptions* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<CopyOptions>(transValue);
    WebModelNG::SetCopyOptionMode(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void OnOverrideUrlLoadingImpl(Ark_NativePointer node,
                              const Opt_OnOverrideUrlLoadingCallback* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onOverrideUrlLoading =
        [callback = CallbackHelper(transValue), weakNode, instanceId](const BaseEventInfo* info) -> bool {
            return OnOverrideUrlLoading(callback, weakNode, instanceId, info);
        };
    WebModelNG::SetOnOverrideUrlLoading(frameNode, std::move(onOverrideUrlLoading));
#endif // WEB_SUPPORTED
}
void TextAutosizingImpl(Ark_NativePointer node,
                        const Opt_Boolean* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(transValue);
    WebModelNG::SetTextAutosizing(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void EnableNativeMediaPlayerImpl(Ark_NativePointer node,
                                 const Opt_NativeMediaPlayerConfig* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto enable = Converter::Convert<bool>(transValue.enable);
    auto shouldOverlay = Converter::Convert<bool>(transValue.shouldOverlay);
    WebModelNG::SetNativeVideoPlayerConfig(frameNode, enable, shouldOverlay);
#endif // WEB_SUPPORTED
}
void OnRenderProcessNotRespondingImpl(Ark_NativePointer node,
                                      const Opt_OnRenderProcessNotRespondingCallback* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onRenderProcessNotResponding =
        [callback = CallbackHelper(transValue), weakNode, instanceId](const BaseEventInfo* info) {
            OnRenderProcessNotResponding(callback, weakNode, instanceId, info);
        };
    WebModelNG::SetRenderProcessNotRespondingId(frameNode, onRenderProcessNotResponding);
#endif // WEB_SUPPORTED
}
void OnRenderProcessRespondingImpl(Ark_NativePointer node,
                                   const Opt_OnRenderProcessRespondingCallback* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onRenderProcessResponding =
        [callback = CallbackHelper(transValue), weakNode, instanceId](const BaseEventInfo* info) {
            OnRenderProcessResponding(callback, weakNode, instanceId, info);
        };
    WebModelNG::SetRenderProcessRespondingId(frameNode, onRenderProcessResponding);
#endif // WEB_SUPPORTED
}
void SelectionMenuOptionsImpl(Ark_NativePointer node,
                              const Opt_Array_ExpandedMenuItemOptions* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<std::vector<Ark_ExpandedMenuItemOptions>>(transValue);
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
            arkCallback.Invoke(parameter);
        };
        option.action = std::move(action);
        optionParam.menuOption.push_back(option);
    }
    WebModelNG::SetSelectionMenuOptions(frameNode, optionParam);
#endif // WEB_SUPPORTED
}
void OnViewportFitChangedImpl(Ark_NativePointer node,
                              const Opt_OnViewportFitChangedCallback* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onViewportFitChanged = [callback = CallbackHelper(transValue), weakNode, instanceId](
                                    const BaseEventInfo* info) {
        OnViewportFitChanged(callback, weakNode, instanceId, info);
    };
    WebModelNG::SetViewportFitChangedId(frameNode, onViewportFitChanged);
#endif // WEB_SUPPORTED
}
void OnInterceptKeyboardAttachImpl(Ark_NativePointer node,
                                   const Opt_WebKeyboardCallback* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onInterceptKeyboardAttach =
        [callback = CallbackHelper(transValue), weakNode, instanceId](const BaseEventInfo* info) -> WebKeyboardOption {
            return OnWebKeyboard(callback, weakNode, instanceId, info);
        };
    WebModelNG::SetOnInterceptKeyboardAttach(frameNode, std::move(onInterceptKeyboardAttach));
#endif // WEB_SUPPORTED
}
void OnAdsBlockedImpl(Ark_NativePointer node,
                      const Opt_OnAdsBlockedCallback* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto instanceId = Container::CurrentId();
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onAdsBlocked = [callback = CallbackHelper(transValue), weakNode, instanceId](const BaseEventInfo* info) {
        OnAdsBlocked(callback, weakNode, instanceId, info);
    };
    WebModelNG::SetAdsBlockedEventId(frameNode, onAdsBlocked);
#endif // WEB_SUPPORTED
}
void KeyboardAvoidModeImpl(Ark_NativePointer node,
                           const Opt_WebKeyboardAvoidMode* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<WebKeyboardAvoidMode>(transValue);
    WebModelNG::SetKeyboardAvoidMode(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void EditMenuOptionsImpl(Ark_NativePointer node,
                         const Opt_EditMenuOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //WebModelNG::SetEditMenuOptions(frameNode, convValue);
}
void EnableHapticFeedbackImpl(Ark_NativePointer node,
                              const Opt_Boolean* value)
{
#ifdef WEB_SUPPORTED
    auto transValue = value->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(transValue);
    WebModelNG::SetEnabledHapticFeedback(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void OptimizeParserBudgetImpl(Ark_NativePointer node,
                              const Opt_Boolean* value)
{
}
void EnableFollowSystemFontWeightImpl(Ark_NativePointer node,
                                      const Opt_Boolean* value)
{
}
void EnableWebAVSessionImpl(Ark_NativePointer node,
                            const Opt_Boolean* value)
{
}
void RunJavaScriptOnDocumentStartImpl(Ark_NativePointer node,
                                      const Opt_Array_ScriptItem* value)
{
}
void RunJavaScriptOnDocumentEndImpl(Ark_NativePointer node,
                                    const Opt_Array_ScriptItem* value)
{
}
void RunJavaScriptOnHeadEndImpl(Ark_NativePointer node,
                                const Opt_Array_ScriptItem* value)
{
}
void NativeEmbedOptionsImpl(Ark_NativePointer node,
                            const Opt_EmbedOptions* value)
{
}
void RegisterNativeEmbedRuleImpl(Ark_NativePointer node,
                                 const Opt_String* tag,
                                 const Opt_String* type)
{
#ifdef WEB_SUPPORTED
    auto transTag = tag->value;
    auto transType = type->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValueTag = Converter::Convert<std::string>(transTag);
    auto convValueType = Converter::Convert<std::string>(transType);
    WebModelNG::RegisterNativeEmbedRule(frameNode, convValueTag, convValueType);
#endif // WEB_SUPPORTED
}
void InitCallbackParams_(FrameNode* frameNode, MenuParam& dst, const Opt_Callback_Void& onAppear,
                         const Opt_Callback_Void& onDisappear)
{
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto arkOnDisappear = Converter::OptConvert<Callback_Void>(onDisappear);
    if (arkOnDisappear) {
        auto onDisappear = [arkCallback = CallbackHelper(arkOnDisappear.value()), weakNode]() {
            PipelineContext::SetCallBackNode(weakNode);
            arkCallback.Invoke();
        };
        dst.onDisappear = std::move(onDisappear);
    }
    auto arkOnAppear = Converter::OptConvert<Callback_Void>(onAppear);
    if (arkOnAppear) {
        auto onAppear = [arkCallback = CallbackHelper(arkOnAppear.value()), weakNode]() {
            PipelineContext::SetCallBackNode(weakNode);
            arkCallback.Invoke();
        };
        dst.onAppear = std::move(onAppear);
    }
}
void BindSelectionMenuImpl(Ark_NativePointer node,
                           const Opt_WebElementType* elementType,
                           const Opt_CustomNodeBuilder* content,
                           const Opt_WebResponseType* responseType,
                           const Opt_SelectionMenuOptionsExt* options)
{
#ifdef WEB_SUPPORTED
    auto transElementType = elementType->value;
    auto transContent = content->value;
    auto transResponseType = responseType->value;
    auto transOptions = options->value;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto elType = Converter::OptConvert<WebElementType>(transElementType);
    CHECK_EQUAL_VOID(elType.has_value(), false);
    MenuParam menuParam;
    auto arkOptions = Converter::OptConvert<Ark_SelectionMenuOptionsExt>(transOptions);
    auto menuType = arkOptions ? Converter::OptConvert<SelectionMenuType>(arkOptions.value().menuType) : std::nullopt;
    std::function<void()> contentNodeBuilder = nullptr;
    std::function<void()> previewNodeBuilder = nullptr;
    if (arkOptions) {
        InitCallbackParams_(frameNode, menuParam, arkOptions.value().onAppear, arkOptions.value().onDisappear);
    }
    if (menuType) {
        menuParam.previewMode = MenuPreviewMode::CUSTOM;
        auto preview = Converter::OptConvert<CustomNodeBuilder>(arkOptions.value().preview);
        if (preview.has_value()) {
            previewNodeBuilder = [callback = CallbackHelper(preview.value()), node]() {
                NG::ViewStackProcessor::GetInstance()->Push(callback.BuildSync(node));
            };
        }
    }
    auto resType = Converter::OptConvert<ResponseType>(transResponseType);
    if (!resType.has_value() || resType.value() != ResponseType::LONG_PRESS) {
        menuParam.previewMode = MenuPreviewMode::NONE;
        menuParam.menuBindType = MenuBindingType::RIGHT_CLICK;
    }
    menuParam.contextMenuRegisterType = NG::ContextMenuRegisterType::CUSTOM_TYPE;
    menuParam.type = NG::MenuType::CONTEXT_MENU;
    menuParam.isShow = true;
    WebModelNG::SetNewDragStyle(frameNode, true);
    contentNodeBuilder = [callback = CallbackHelper(transContent), node]() {
        NG::ViewStackProcessor::GetInstance()->Push(callback.BuildSync(node));
    };
    auto previewSelectionMenuParam = std::make_shared<WebPreviewSelectionMenuParam>(
        elType.value(), resType.value(), contentNodeBuilder, previewNodeBuilder, menuParam);
    WebModelNG::SetPreviewSelectionMenu(frameNode, previewSelectionMenuParam);
#endif // WEB_SUPPORTED
}
} // WebAttributeModifier
const GENERATED_ArkUIWebModifier* GetWebModifier()
{
    static const GENERATED_ArkUIWebModifier ArkUIWebModifierImpl {
        WebModifier::ConstructImpl,
        WebInterfaceModifier::SetWebOptionsImpl,
        WebAttributeModifier::JavaScriptAccessImpl,
        WebAttributeModifier::FileAccessImpl,
        WebAttributeModifier::OnlineImageAccessImpl,
        WebAttributeModifier::DomStorageAccessImpl,
        WebAttributeModifier::ImageAccessImpl,
        WebAttributeModifier::MixedModeImpl,
        WebAttributeModifier::ZoomAccessImpl,
        WebAttributeModifier::GeolocationAccessImpl,
        WebAttributeModifier::JavaScriptProxyImpl,
        WebAttributeModifier::PasswordImpl,
        WebAttributeModifier::CacheModeImpl,
        WebAttributeModifier::DarkModeImpl,
        WebAttributeModifier::ForceDarkAccessImpl,
        WebAttributeModifier::MediaOptionsImpl,
        WebAttributeModifier::TableDataImpl,
        WebAttributeModifier::WideViewModeAccessImpl,
        WebAttributeModifier::OverviewModeAccessImpl,
        WebAttributeModifier::OverScrollModeImpl,
        WebAttributeModifier::BlurOnKeyboardHideModeImpl,
        WebAttributeModifier::TextZoomAtioImpl,
        WebAttributeModifier::TextZoomRatioImpl,
        WebAttributeModifier::DatabaseAccessImpl,
        WebAttributeModifier::InitialScaleImpl,
        WebAttributeModifier::UserAgentImpl,
        WebAttributeModifier::MetaViewportImpl,
        WebAttributeModifier::OnPageEndImpl,
        WebAttributeModifier::OnPageBeginImpl,
        WebAttributeModifier::OnProgressChangeImpl,
        WebAttributeModifier::OnTitleReceiveImpl,
        WebAttributeModifier::OnGeolocationHideImpl,
        WebAttributeModifier::OnGeolocationShowImpl,
        WebAttributeModifier::OnRequestSelectedImpl,
        WebAttributeModifier::OnAlertImpl,
        WebAttributeModifier::OnBeforeUnloadImpl,
        WebAttributeModifier::OnConfirmImpl,
        WebAttributeModifier::OnPromptImpl,
        WebAttributeModifier::OnConsoleImpl,
        WebAttributeModifier::OnErrorReceiveImpl,
        WebAttributeModifier::OnHttpErrorReceiveImpl,
        WebAttributeModifier::OnDownloadStartImpl,
        WebAttributeModifier::OnRefreshAccessedHistoryImpl,
        WebAttributeModifier::OnUrlLoadInterceptImpl,
        WebAttributeModifier::OnSslErrorReceiveImpl,
        WebAttributeModifier::OnRenderExited0Impl,
        WebAttributeModifier::OnRenderExited1Impl,
        WebAttributeModifier::OnShowFileSelectorImpl,
        WebAttributeModifier::OnFileSelectorShowImpl,
        WebAttributeModifier::OnResourceLoadImpl,
        WebAttributeModifier::OnFullScreenExitImpl,
        WebAttributeModifier::OnFullScreenEnterImpl,
        WebAttributeModifier::OnScaleChangeImpl,
        WebAttributeModifier::OnHttpAuthRequestImpl,
        WebAttributeModifier::OnInterceptRequestImpl,
        WebAttributeModifier::OnPermissionRequestImpl,
        WebAttributeModifier::OnScreenCaptureRequestImpl,
        WebAttributeModifier::OnContextMenuShowImpl,
        WebAttributeModifier::OnContextMenuHideImpl,
        WebAttributeModifier::MediaPlayGestureAccessImpl,
        WebAttributeModifier::OnSearchResultReceiveImpl,
        WebAttributeModifier::OnScrollImpl,
        WebAttributeModifier::OnSslErrorEventReceiveImpl,
        WebAttributeModifier::OnSslErrorEventImpl,
        WebAttributeModifier::OnClientAuthenticationRequestImpl,
        WebAttributeModifier::OnWindowNewImpl,
        WebAttributeModifier::OnWindowExitImpl,
        WebAttributeModifier::MultiWindowAccessImpl,
        WebAttributeModifier::OnInterceptKeyEventImpl,
        WebAttributeModifier::WebStandardFontImpl,
        WebAttributeModifier::WebSerifFontImpl,
        WebAttributeModifier::WebSansSerifFontImpl,
        WebAttributeModifier::WebFixedFontImpl,
        WebAttributeModifier::WebFantasyFontImpl,
        WebAttributeModifier::WebCursiveFontImpl,
        WebAttributeModifier::DefaultFixedFontSizeImpl,
        WebAttributeModifier::DefaultFontSizeImpl,
        WebAttributeModifier::MinFontSizeImpl,
        WebAttributeModifier::MinLogicalFontSizeImpl,
        WebAttributeModifier::DefaultTextEncodingFormatImpl,
        WebAttributeModifier::ForceDisplayScrollBarImpl,
        WebAttributeModifier::BlockNetworkImpl,
        WebAttributeModifier::HorizontalScrollBarAccessImpl,
        WebAttributeModifier::VerticalScrollBarAccessImpl,
        WebAttributeModifier::OnTouchIconUrlReceivedImpl,
        WebAttributeModifier::OnFaviconReceivedImpl,
        WebAttributeModifier::OnPageVisibleImpl,
        WebAttributeModifier::OnDataResubmittedImpl,
        WebAttributeModifier::PinchSmoothImpl,
        WebAttributeModifier::AllowWindowOpenMethodImpl,
        WebAttributeModifier::OnAudioStateChangedImpl,
        WebAttributeModifier::OnFirstContentfulPaintImpl,
        WebAttributeModifier::OnFirstMeaningfulPaintImpl,
        WebAttributeModifier::OnLargestContentfulPaintImpl,
        WebAttributeModifier::OnLoadInterceptImpl,
        WebAttributeModifier::OnControllerAttachedImpl,
        WebAttributeModifier::OnOverScrollImpl,
        WebAttributeModifier::OnSafeBrowsingCheckResultImpl,
        WebAttributeModifier::OnNavigationEntryCommittedImpl,
        WebAttributeModifier::OnIntelligentTrackingPreventionResultImpl,
        WebAttributeModifier::JavaScriptOnDocumentStartImpl,
        WebAttributeModifier::JavaScriptOnDocumentEndImpl,
        WebAttributeModifier::LayoutModeImpl,
        WebAttributeModifier::NestedScrollImpl,
        WebAttributeModifier::EnableNativeEmbedModeImpl,
        WebAttributeModifier::OnNativeEmbedLifecycleChangeImpl,
        WebAttributeModifier::OnNativeEmbedVisibilityChangeImpl,
        WebAttributeModifier::OnNativeEmbedGestureEventImpl,
        WebAttributeModifier::CopyOptionsImpl,
        WebAttributeModifier::OnOverrideUrlLoadingImpl,
        WebAttributeModifier::TextAutosizingImpl,
        WebAttributeModifier::EnableNativeMediaPlayerImpl,
        WebAttributeModifier::OnRenderProcessNotRespondingImpl,
        WebAttributeModifier::OnRenderProcessRespondingImpl,
        WebAttributeModifier::SelectionMenuOptionsImpl,
        WebAttributeModifier::OnViewportFitChangedImpl,
        WebAttributeModifier::OnInterceptKeyboardAttachImpl,
        WebAttributeModifier::OnAdsBlockedImpl,
        WebAttributeModifier::KeyboardAvoidModeImpl,
        WebAttributeModifier::EditMenuOptionsImpl,
        WebAttributeModifier::EnableHapticFeedbackImpl,
        WebAttributeModifier::OptimizeParserBudgetImpl,
        WebAttributeModifier::EnableFollowSystemFontWeightImpl,
        WebAttributeModifier::EnableWebAVSessionImpl,
        WebAttributeModifier::RunJavaScriptOnDocumentStartImpl,
        WebAttributeModifier::RunJavaScriptOnDocumentEndImpl,
        WebAttributeModifier::RunJavaScriptOnHeadEndImpl,
        WebAttributeModifier::NativeEmbedOptionsImpl,
        WebAttributeModifier::RegisterNativeEmbedRuleImpl,
        WebAttributeModifier::BindSelectionMenuImpl,
    };
    return &ArkUIWebModifierImpl;
}

}
