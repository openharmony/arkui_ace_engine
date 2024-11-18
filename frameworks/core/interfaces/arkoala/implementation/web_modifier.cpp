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

#include "core/components_ng/base/frame_node.h"
#ifdef WEB_SUPPORTED
#include "core/components_ng/pattern/web/web_model_ng.h"
#endif // WEB_SUPPORTED
#include "core/interfaces/arkoala/implementation/web_controller_peer_impl.h"
#include "core/interfaces/arkoala/utility/converter.h"
#include "arkoala_api_generated.h"

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
void AssignCast(std::optional<MixedModeContent>& dst, const Ark_MixedMode& src)
{
    switch (src) {
        case ARK_MIXED_MODE_ALL: dst = MixedModeContent::MIXED_CONTENT_ALWAYS_ALLOW; break;
        case ARK_MIXED_MODE_COMPATIBLE: dst = MixedModeContent::MIXED_CONTENT_COMPATIBILITY_MODE; break;
        case ARK_MIXED_MODE_NONE: dst = MixedModeContent::MIXED_CONTENT_NEVER_ALLOW; break;
        default: LOGE("Unexpected enum value in Ark_MixedMode: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<WebCacheMode>& dst, const Ark_CacheMode& src)
{
    switch (src) {
        case ARK_CACHE_MODE_DEFAULT: dst = WebCacheMode::DEFAULT; break;
        case ARK_CACHE_MODE_NONE: dst = WebCacheMode::USE_CACHE_ELSE_NETWORK; break;
        case ARK_CACHE_MODE_ONLINE: dst = WebCacheMode::USE_NO_CACHE; break;
        case ARK_CACHE_MODE_ONLY: dst = WebCacheMode::USE_CACHE_ONLY; break;
        default: LOGE("Unexpected enum value in Ark_CacheMode: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<WebDarkMode>& dst, const Ark_WebDarkMode& src)
{
    switch (src) {
        case ARK_WEB_DARK_MODE_OFF: dst = WebDarkMode::Off; break;
        case ARK_WEB_DARK_MODE_ON: dst = WebDarkMode::On; break;
        case ARK_WEB_DARK_MODE_AUTO: dst = WebDarkMode::Auto; break;
        default: LOGE("Unexpected enum value in Ark_WebDarkMode: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<OverScrollMode>& dst, const Ark_OverScrollMode& src)
{
    switch (src) {
        case ARK_OVER_SCROLL_MODE_NEVER: dst = OverScrollMode::NEVER; break;
        case ARK_OVER_SCROLL_MODE_ALWAYS: dst = OverScrollMode::ALWAYS; break;
        default: LOGE("Unexpected enum value in Ark_OverScrollMode: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<WebLayoutMode>& dst, const Ark_WebLayoutMode& src)
{
    switch (src) {
        case ARK_WEB_LAYOUT_MODE_NONE: dst = WebLayoutMode::NONE; break;
        case ARK_WEB_LAYOUT_MODE_FIT_CONTENT: dst = WebLayoutMode::FIT_CONTENT; break;
        default: LOGE("Unexpected enum value in Ark_WebLayoutMode: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<WebKeyboardAvoidMode>& dst, const Ark_WebKeyboardAvoidMode& src)
{
    switch (src) {
        case ARK_WEB_KEYBOARD_AVOID_MODE_RESIZE_VISUAL: dst = WebKeyboardAvoidMode::RESIZE_VISUAL; break;
        case ARK_WEB_KEYBOARD_AVOID_MODE_RESIZE_CONTENT: dst = WebKeyboardAvoidMode::RESIZE_CONTENT; break;
        case ARK_WEB_KEYBOARD_AVOID_MODE_OVERLAYS_CONTENT: dst = WebKeyboardAvoidMode::OVERLAYS_CONTENT; break;
        default: LOGE("Unexpected enum value in Ark_WebKeyboardAvoidMode: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<RenderMode>& dst, const Ark_RenderMode& src)
{
    switch (src) {
        case ARK_RENDER_MODE_ASYNC_RENDER: dst = RenderMode::ASYNC_RENDER; break;
        case ARK_RENDER_MODE_SYNC_RENDER: dst = RenderMode::SYNC_RENDER; break;
        default: LOGE("Unexpected enum value in Ark_RenderMode: %{public}d", src);
    }
}

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
    LOGE("Converter ExpandedMenuItemOptions `action` property supporting is not implemented yet");
    return menuOption;
}
#endif // WEB_SUPPORTED
} // namespace OHOS::Ace::NG::Converter

namespace OHOS::Ace::NG::GeneratedModifier {
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
            auto peerImplPtr = reinterpret_cast<GeneratedModifier::WebControllerPeerImpl *>(controller.ptr);
            CHECK_NULL_VOID(peerImplPtr);
            WebModelNG::SetWebController(frameNode, peerImplPtr->GetController());
        },
        [](const auto& value) {
            LOGE("WebInterfaceModifier::SetWebOptionsImpl WebviewController option is not supported");
        },
        []() {}
    );
#endif // WEB_SUPPORTED
}
} // WebInterfaceModifier
namespace WebAttributeModifier {
void JavaScriptAccessImpl(Ark_NativePointer node,
                          Ark_Boolean value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    WebModelNG::SetJsEnabled(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void FileAccessImpl(Ark_NativePointer node,
                    Ark_Boolean value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    WebModelNG::SetFileAccessEnabled(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void OnlineImageAccessImpl(Ark_NativePointer node,
                           Ark_Boolean value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    WebModelNG::SetOnLineImageAccessEnabled(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void DomStorageAccessImpl(Ark_NativePointer node,
                          Ark_Boolean value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    WebModelNG::SetDomStorageAccessEnabled(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void ImageAccessImpl(Ark_NativePointer node,
                     Ark_Boolean value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    WebModelNG::SetImageAccessEnabled(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void MixedModeImpl(Ark_NativePointer node,
                   Ark_MixedMode value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<MixedModeContent>(value);
    WebModelNG::SetMixedMode(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void ZoomAccessImpl(Ark_NativePointer node,
                    Ark_Boolean value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    WebModelNG::SetZoomAccessEnabled(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void GeolocationAccessImpl(Ark_NativePointer node,
                           Ark_Boolean value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    WebModelNG::SetGeolocationAccessEnabled(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void JavaScriptProxyImpl(Ark_NativePointer node,
                         const Ark_JavaScriptProxy* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    LOGE("WebInterfaceModifier::JavaScriptProxyImpl method is not implemented");
}
void PasswordImpl(Ark_NativePointer node,
                  Ark_Boolean value)
{
    // deprecated
}
void CacheModeImpl(Ark_NativePointer node,
                   Ark_CacheMode value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<WebCacheMode>(value);
    WebModelNG::SetCacheMode(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void DarkModeImpl(Ark_NativePointer node,
                  Ark_WebDarkMode value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<WebDarkMode>(value);
    WebModelNG::SetDarkMode(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void ForceDarkAccessImpl(Ark_NativePointer node,
                         Ark_Boolean value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    WebModelNG::SetForceDarkAccess(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void MediaOptionsImpl(Ark_NativePointer node,
                      const Ark_WebMediaOptions* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    WebModelNG::SetAudioResumeInterval(frameNode, Converter::OptConvert<int32_t>(value->resumeInterval));
    WebModelNG::SetAudioExclusive(frameNode, Converter::OptConvert<bool>(value->audioExclusive));
#endif // WEB_SUPPORTED
}
void TableDataImpl(Ark_NativePointer node,
                   Ark_Boolean value)
{
    // deprecated
}
void WideViewModeAccessImpl(Ark_NativePointer node,
                            Ark_Boolean value)
{
    // deprecated
}
void OverviewModeAccessImpl(Ark_NativePointer node,
                            Ark_Boolean value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    WebModelNG::SetOverviewModeAccessEnabled(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void OverScrollModeImpl(Ark_NativePointer node,
                        Ark_OverScrollMode value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<OverScrollMode>(value);
    WebModelNG::SetOverScrollMode(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void TextZoomAtioImpl(Ark_NativePointer node,
                      const Ark_Number* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::Convert<int32_t>(*value);
    WebModelNG::SetTextZoomRatio(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void TextZoomRatioImpl(Ark_NativePointer node,
                       const Ark_Number* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::Convert<int32_t>(*value);
    WebModelNG::SetTextZoomRatio(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void DatabaseAccessImpl(Ark_NativePointer node,
                        Ark_Boolean value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    WebModelNG::SetDatabaseAccessEnabled(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void InitialScaleImpl(Ark_NativePointer node,
                      const Ark_Number* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::Convert<float>(*value);
    WebModelNG::InitialScale(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void UserAgentImpl(Ark_NativePointer node,
                   const Ark_String* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::Convert<std::string>(*value);
    WebModelNG::SetUserAgent(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void MetaViewportImpl(Ark_NativePointer node,
                      Ark_Boolean value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    WebModelNG::SetMetaViewport(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void OnPageEndImpl(Ark_NativePointer node,
                   const Callback_OnPageEndEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //WebModelNG::SetOnPageEnd(frameNode, convValue);
}
void OnPageBeginImpl(Ark_NativePointer node,
                     const Callback_OnPageBeginEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //WebModelNG::SetOnPageBegin(frameNode, convValue);
}
void OnProgressChangeImpl(Ark_NativePointer node,
                          const Callback_OnProgressChangeEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //WebModelNG::SetOnProgressChange(frameNode, convValue);
}
void OnTitleReceiveImpl(Ark_NativePointer node,
                        const Callback_OnTitleReceiveEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //WebModelNG::SetOnTitleReceive(frameNode, convValue);
}
void OnGeolocationHideImpl(Ark_NativePointer node,
                           const Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //WebModelNG::SetOnGeolocationHide(frameNode, convValue);
}
void OnGeolocationShowImpl(Ark_NativePointer node,
                           const Callback_OnGeolocationShowEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //WebModelNG::SetOnGeolocationShow(frameNode, convValue);
}
void OnRequestSelectedImpl(Ark_NativePointer node,
                           const Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //WebModelNG::SetOnRequestSelected(frameNode, convValue);
}
void OnAlertImpl(Ark_NativePointer node,
                 const Callback_OnAlertEvent_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //WebModelNG::SetOnAlert(frameNode, convValue);
}
void OnBeforeUnloadImpl(Ark_NativePointer node,
                        const Callback_OnBeforeUnloadEvent_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //WebModelNG::SetOnBeforeUnload(frameNode, convValue);
}
void OnConfirmImpl(Ark_NativePointer node,
                   const Callback_OnConfirmEvent_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //WebModelNG::SetOnConfirm(frameNode, convValue);
}
void OnPromptImpl(Ark_NativePointer node,
                  const Callback_OnPromptEvent_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //WebModelNG::SetOnPrompt(frameNode, convValue);
}
void OnConsoleImpl(Ark_NativePointer node,
                   const Callback_OnConsoleEvent_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //WebModelNG::SetOnConsole(frameNode, convValue);
}
void OnErrorReceiveImpl(Ark_NativePointer node,
                        const Callback_OnErrorReceiveEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //WebModelNG::SetOnErrorReceive(frameNode, convValue);
}
void OnHttpErrorReceiveImpl(Ark_NativePointer node,
                            const Callback_OnHttpErrorReceiveEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //WebModelNG::SetOnHttpErrorReceive(frameNode, convValue);
}
void OnDownloadStartImpl(Ark_NativePointer node,
                         const Callback_OnDownloadStartEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //WebModelNG::SetOnDownloadStart(frameNode, convValue);
}
void OnRefreshAccessedHistoryImpl(Ark_NativePointer node,
                                  const Callback_OnRefreshAccessedHistoryEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //WebModelNG::SetOnRefreshAccessedHistory(frameNode, convValue);
}
void OnUrlLoadInterceptImpl(Ark_NativePointer node,
                            const Type_WebAttribute_onUrlLoadIntercept_callback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //WebModelNG::SetOnUrlLoadIntercept(frameNode, convValue);
}
void OnSslErrorReceiveImpl(Ark_NativePointer node,
                           const Callback_Literal_Function_handler_Object_error_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //WebModelNG::SetOnSslErrorReceive(frameNode, convValue);
}
void OnRenderExited0Impl(Ark_NativePointer node,
                         const Callback_OnRenderExitedEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //WebModelNG::SetOnRenderExited0(frameNode, convValue);
}
void OnRenderExited1Impl(Ark_NativePointer node,
                         const Callback_Literal_Object_detail_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //WebModelNG::SetOnRenderExited1(frameNode, convValue);
}
void OnShowFileSelectorImpl(Ark_NativePointer node,
                            const Callback_OnShowFileSelectorEvent_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //WebModelNG::SetOnShowFileSelector(frameNode, convValue);
}
void OnFileSelectorShowImpl(Ark_NativePointer node,
                            const Callback_Literal_Function_callback_Object_fileSelector_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //WebModelNG::SetOnFileSelectorShow(frameNode, convValue);
}
void OnResourceLoadImpl(Ark_NativePointer node,
                        const Callback_OnResourceLoadEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //WebModelNG::SetOnResourceLoad(frameNode, convValue);
}
void OnFullScreenExitImpl(Ark_NativePointer node,
                          const Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //WebModelNG::SetOnFullScreenExit(frameNode, convValue);
}
void OnFullScreenEnterImpl(Ark_NativePointer node,
                           const OnFullScreenEnterCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //WebModelNG::SetOnFullScreenEnter(frameNode, convValue);
}
void OnScaleChangeImpl(Ark_NativePointer node,
                       const Callback_OnScaleChangeEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //WebModelNG::SetOnScaleChange(frameNode, convValue);
}
void OnHttpAuthRequestImpl(Ark_NativePointer node,
                           const Callback_OnHttpAuthRequestEvent_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //WebModelNG::SetOnHttpAuthRequest(frameNode, convValue);
}
void OnInterceptRequestImpl(Ark_NativePointer node,
                            const Callback_OnInterceptRequestEvent_WebResourceResponse* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //WebModelNG::SetOnInterceptRequest(frameNode, convValue);
}
void OnPermissionRequestImpl(Ark_NativePointer node,
                             const Callback_OnPermissionRequestEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //WebModelNG::SetOnPermissionRequest(frameNode, convValue);
}
void OnScreenCaptureRequestImpl(Ark_NativePointer node,
                                const Callback_OnScreenCaptureRequestEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //WebModelNG::SetOnScreenCaptureRequest(frameNode, convValue);
}
void OnContextMenuShowImpl(Ark_NativePointer node,
                           const Callback_OnContextMenuShowEvent_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //WebModelNG::SetOnContextMenuShow(frameNode, convValue);
}
void OnContextMenuHideImpl(Ark_NativePointer node,
                           const OnContextMenuHideCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //WebModelNG::SetOnContextMenuHide(frameNode, convValue);
}
void MediaPlayGestureAccessImpl(Ark_NativePointer node,
                                Ark_Boolean value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    WebModelNG::SetMediaPlayGestureAccess(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void OnSearchResultReceiveImpl(Ark_NativePointer node,
                               const Callback_OnSearchResultReceiveEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //WebModelNG::SetOnSearchResultReceive(frameNode, convValue);
}
void OnScrollImpl(Ark_NativePointer node,
                  const Callback_OnScrollEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //WebModelNG::SetOnScroll(frameNode, convValue);
}
void OnSslErrorEventReceiveImpl(Ark_NativePointer node,
                                const Callback_OnSslErrorEventReceiveEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //WebModelNG::SetOnSslErrorEventReceive(frameNode, convValue);
}
void OnSslErrorEventImpl(Ark_NativePointer node,
                         const OnSslErrorEventCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //WebModelNG::SetOnSslErrorEvent(frameNode, convValue);
}
void OnClientAuthenticationRequestImpl(Ark_NativePointer node,
                                       const Callback_OnClientAuthenticationEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //WebModelNG::SetOnClientAuthenticationRequest(frameNode, convValue);
}
void OnWindowNewImpl(Ark_NativePointer node,
                     const Callback_OnWindowNewEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //WebModelNG::SetOnWindowNew(frameNode, convValue);
}
void OnWindowExitImpl(Ark_NativePointer node,
                      const Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //WebModelNG::SetOnWindowExit(frameNode, convValue);
}
void MultiWindowAccessImpl(Ark_NativePointer node,
                           Ark_Boolean value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    WebModelNG::SetMultiWindowAccessEnabled(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void OnInterceptKeyEventImpl(Ark_NativePointer node,
                             const Callback_KeyEvent_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //WebModelNG::SetOnInterceptKeyEvent(frameNode, convValue);
}
void WebStandardFontImpl(Ark_NativePointer node,
                         const Ark_String* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::Convert<std::string>(*value);
    WebModelNG::SetWebStandardFont(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void WebSerifFontImpl(Ark_NativePointer node,
                      const Ark_String* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::Convert<std::string>(*value);
    WebModelNG::SetWebSerifFont(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void WebSansSerifFontImpl(Ark_NativePointer node,
                          const Ark_String* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::Convert<std::string>(*value);
    WebModelNG::SetWebSansSerifFont(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void WebFixedFontImpl(Ark_NativePointer node,
                      const Ark_String* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::Convert<std::string>(*value);
    WebModelNG::SetWebFixedFont(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void WebFantasyFontImpl(Ark_NativePointer node,
                        const Ark_String* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::Convert<std::string>(*value);
    WebModelNG::SetWebFantasyFont(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void WebCursiveFontImpl(Ark_NativePointer node,
                        const Ark_String* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::Convert<std::string>(*value);
    WebModelNG::SetWebCursiveFont(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void DefaultFixedFontSizeImpl(Ark_NativePointer node,
                              const Ark_Number* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::Convert<int32_t>(*value);
    WebModelNG::SetDefaultFixedFontSize(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void DefaultFontSizeImpl(Ark_NativePointer node,
                         const Ark_Number* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::Convert<int32_t>(*value);
    WebModelNG::SetDefaultFontSize(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void MinFontSizeImpl(Ark_NativePointer node,
                     const Ark_Number* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::Convert<int32_t>(*value);
    WebModelNG::SetMinFontSize(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void MinLogicalFontSizeImpl(Ark_NativePointer node,
                            const Ark_Number* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::Convert<int32_t>(*value);
    WebModelNG::SetMinLogicalFontSize(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void DefaultTextEncodingFormatImpl(Ark_NativePointer node,
                                   const Ark_String* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::Convert<std::string>(*value);
    EraseSpace(convValue);
    WebModelNG::SetDefaultTextEncodingFormat(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void ForceDisplayScrollBarImpl(Ark_NativePointer node,
                               Ark_Boolean value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    WebModelNG::SetOverlayScrollbarEnabled(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void BlockNetworkImpl(Ark_NativePointer node,
                      Ark_Boolean value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    WebModelNG::SetBlockNetwork(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void HorizontalScrollBarAccessImpl(Ark_NativePointer node,
                                   Ark_Boolean value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    WebModelNG::SetHorizontalScrollBarAccessEnabled(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void VerticalScrollBarAccessImpl(Ark_NativePointer node,
                                 Ark_Boolean value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    WebModelNG::SetVerticalScrollBarAccessEnabled(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void OnTouchIconUrlReceivedImpl(Ark_NativePointer node,
                                const Callback_OnTouchIconUrlReceivedEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //WebModelNG::SetOnTouchIconUrlReceived(frameNode, convValue);
}
void OnFaviconReceivedImpl(Ark_NativePointer node,
                           const Callback_OnFaviconReceivedEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //WebModelNG::SetOnFaviconReceived(frameNode, convValue);
}
void OnPageVisibleImpl(Ark_NativePointer node,
                       const Callback_OnPageVisibleEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //WebModelNG::SetOnPageVisible(frameNode, convValue);
}
void OnDataResubmittedImpl(Ark_NativePointer node,
                           const Callback_OnDataResubmittedEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //WebModelNG::SetOnDataResubmitted(frameNode, convValue);
}
void PinchSmoothImpl(Ark_NativePointer node,
                     Ark_Boolean value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    WebModelNG::SetPinchSmoothModeEnabled(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void AllowWindowOpenMethodImpl(Ark_NativePointer node,
                               Ark_Boolean value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    WebModelNG::SetAllowWindowOpenMethod(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void OnAudioStateChangedImpl(Ark_NativePointer node,
                             const Callback_OnAudioStateChangedEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //WebModelNG::SetOnAudioStateChanged(frameNode, convValue);
}
void OnFirstContentfulPaintImpl(Ark_NativePointer node,
                                const Callback_OnFirstContentfulPaintEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //WebModelNG::SetOnFirstContentfulPaint(frameNode, convValue);
}
void OnFirstMeaningfulPaintImpl(Ark_NativePointer node,
                                const OnFirstMeaningfulPaintCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //WebModelNG::SetOnFirstMeaningfulPaint(frameNode, convValue);
}
void OnLargestContentfulPaintImpl(Ark_NativePointer node,
                                  const OnLargestContentfulPaintCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //WebModelNG::SetOnLargestContentfulPaint(frameNode, convValue);
}
void OnLoadInterceptImpl(Ark_NativePointer node,
                         const Callback_OnLoadInterceptEvent_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //WebModelNG::SetOnLoadIntercept(frameNode, convValue);
}
void OnControllerAttachedImpl(Ark_NativePointer node,
                              const Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //WebModelNG::SetOnControllerAttached(frameNode, convValue);
}
void OnOverScrollImpl(Ark_NativePointer node,
                      const Callback_OnOverScrollEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //WebModelNG::SetOnOverScroll(frameNode, convValue);
}
void OnSafeBrowsingCheckResultImpl(Ark_NativePointer node,
                                   const OnSafeBrowsingCheckResultCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //WebModelNG::SetOnSafeBrowsingCheckResult(frameNode, convValue);
}
void OnNavigationEntryCommittedImpl(Ark_NativePointer node,
                                    const OnNavigationEntryCommittedCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //WebModelNG::SetOnNavigationEntryCommitted(frameNode, convValue);
}
void OnIntelligentTrackingPreventionResultImpl(Ark_NativePointer node,
                                               const OnIntelligentTrackingPreventionCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //WebModelNG::SetOnIntelligentTrackingPreventionResult(frameNode, convValue);
}
void JavaScriptOnDocumentStartImpl(Ark_NativePointer node,
                                   const Array_ScriptItem* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::Convert<ScriptItems>(*value);
    WebModelNG::JavaScriptOnDocumentStart(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void JavaScriptOnDocumentEndImpl(Ark_NativePointer node,
                                 const Array_ScriptItem* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::Convert<ScriptItems>(*value);
    WebModelNG::JavaScriptOnDocumentEnd(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void LayoutModeImpl(Ark_NativePointer node,
                    Ark_WebLayoutMode value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<WebLayoutMode>(value);
    WebModelNG::SetLayoutMode(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void NestedScrollImpl(Ark_NativePointer node,
                      const Ark_Union_NestedScrollOptions_NestedScrollOptionsExt* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::OptConvert<NestedScrollOptionsExt>(*value);
    WebModelNG::SetNestedScrollExt(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void EnableNativeEmbedModeImpl(Ark_NativePointer node,
                               Ark_Boolean value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    WebModelNG::SetNativeEmbedModeEnabled(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void OnNativeEmbedLifecycleChangeImpl(Ark_NativePointer node,
                                      const Callback_NativeEmbedDataInfo_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //WebModelNG::SetOnNativeEmbedLifecycleChange(frameNode, convValue);
}
void OnNativeEmbedVisibilityChangeImpl(Ark_NativePointer node,
                                       const OnNativeEmbedVisibilityChangeCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //WebModelNG::SetOnNativeEmbedVisibilityChange(frameNode, convValue);
}
void OnNativeEmbedGestureEventImpl(Ark_NativePointer node,
                                   const Callback_NativeEmbedTouchInfo_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //WebModelNG::SetOnNativeEmbedGestureEvent(frameNode, convValue);
}
void CopyOptionsImpl(Ark_NativePointer node,
                     Ark_CopyOptions value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<CopyOptions>(value);
    WebModelNG::SetCopyOptionMode(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void OnOverrideUrlLoadingImpl(Ark_NativePointer node,
                              const OnOverrideUrlLoadingCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //WebModelNG::SetOnOverrideUrlLoading(frameNode, convValue);
}
void TextAutosizingImpl(Ark_NativePointer node,
                        Ark_Boolean value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    WebModelNG::SetTextAutosizing(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void EnableNativeMediaPlayerImpl(Ark_NativePointer node,
                                 const Ark_NativeMediaPlayerConfig* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto enable = Converter::Convert<bool>(value->enable);
    auto shouldOverlay = Converter::Convert<bool>(value->shouldOverlay);
    WebModelNG::SetNativeVideoPlayerConfig(frameNode, enable, shouldOverlay);
#endif // WEB_SUPPORTED
}
void EnableSmoothDragResizeImpl(Ark_NativePointer node,
                                Ark_Boolean value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    WebModelNG::SetSmoothDragResizeEnabled(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void OnRenderProcessNotRespondingImpl(Ark_NativePointer node,
                                      const OnRenderProcessNotRespondingCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //WebModelNG::SetOnRenderProcessNotResponding(frameNode, convValue);
}
void OnRenderProcessRespondingImpl(Ark_NativePointer node,
                                   const OnRenderProcessRespondingCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //WebModelNG::SetOnRenderProcessResponding(frameNode, convValue);
}
void SelectionMenuOptionsImpl(Ark_NativePointer node,
                              const Array_ExpandedMenuItemOptions* value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::Convert<std::vector<MenuOptionsParam>>(*value);
    WebMenuOptionsParam optionParam;
    for (auto menuOption : convValue) {
        optionParam.menuOption.push_back(menuOption);
    }
    LOGE("WebInterfaceModifier::SelectionMenuOptionsImpl `action` property supporting is not implemented yet");
    WebModelNG::SetSelectionMenuOptions(frameNode, optionParam);
#endif // WEB_SUPPORTED
}
void OnViewportFitChangedImpl(Ark_NativePointer node,
                              const OnViewportFitChangedCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //WebModelNG::SetOnViewportFitChanged(frameNode, convValue);
}
void OnInterceptKeyboardAttachImpl(Ark_NativePointer node,
                                   const WebKeyboardCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //WebModelNG::SetOnInterceptKeyboardAttach(frameNode, convValue);
}
void OnAdsBlockedImpl(Ark_NativePointer node,
                      const OnAdsBlockedCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //WebModelNG::SetOnAdsBlocked(frameNode, convValue);
}
void KeyboardAvoidModeImpl(Ark_NativePointer node,
                           Ark_WebKeyboardAvoidMode value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<WebKeyboardAvoidMode>(value);
    WebModelNG::SetKeyboardAvoidMode(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void EditMenuOptionsImpl(Ark_NativePointer node,
                         const Ark_Materialized* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //WebModelNG::SetEditMenuOptions(frameNode, convValue);
}
void EnableHapticFeedbackImpl(Ark_NativePointer node,
                              Ark_Boolean value)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    WebModelNG::SetEnabledHapticFeedback(frameNode, convValue);
#endif // WEB_SUPPORTED
}
void RegisterNativeEmbedRuleImpl(Ark_NativePointer node,
                                 const Ark_String* tag,
                                 const Ark_String* type)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(tag);
    CHECK_NULL_VOID(type);
    auto convValueTag = Converter::Convert<std::string>(*tag);
    auto convValueType = Converter::Convert<std::string>(*type);
    WebModelNG::RegisterNativeEmbedRule(frameNode, convValueTag, convValueType);
#endif // WEB_SUPPORTED
}
} // WebAttributeModifier
const GENERATED_ArkUIWebModifier* GetWebModifier()
{
    static const GENERATED_ArkUIWebModifier ArkUIWebModifierImpl {
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
        WebAttributeModifier::EnableSmoothDragResizeImpl,
        WebAttributeModifier::OnRenderProcessNotRespondingImpl,
        WebAttributeModifier::OnRenderProcessRespondingImpl,
        WebAttributeModifier::SelectionMenuOptionsImpl,
        WebAttributeModifier::OnViewportFitChangedImpl,
        WebAttributeModifier::OnInterceptKeyboardAttachImpl,
        WebAttributeModifier::OnAdsBlockedImpl,
        WebAttributeModifier::KeyboardAvoidModeImpl,
        WebAttributeModifier::EditMenuOptionsImpl,
        WebAttributeModifier::EnableHapticFeedbackImpl,
        WebAttributeModifier::RegisterNativeEmbedRuleImpl,
    };
    return &ArkUIWebModifierImpl;
}

}
