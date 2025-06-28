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

using namespace OHOS::Ace::NG::Converter;

namespace OHOS::Ace {
using ScriptItem = std::pair<std::string, std::vector<std::string>>;
} // namespace OHOS::Ace

namespace OHOS::Ace::NG::Converter {
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
} // namespace OHOS::Ace::NG::Converter

namespace OHOS::Ace::NG::GeneratedModifier {
namespace WebModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    return {};
}
} // WebModifier
namespace WebInterfaceModifier {
void SetWebOptionsImpl(Ark_NativePointer node,
                       const Ark_WebOptions* value)
{
}
} // WebInterfaceModifier
namespace WebAttributeModifier {
void JavaScriptAccessImpl(Ark_NativePointer node,
                          Ark_Boolean value)
{
}
void FileAccessImpl(Ark_NativePointer node,
                    Ark_Boolean value)
{
}
void OnlineImageAccessImpl(Ark_NativePointer node,
                           Ark_Boolean value)
{
}
void DomStorageAccessImpl(Ark_NativePointer node,
                          Ark_Boolean value)
{
}
void ImageAccessImpl(Ark_NativePointer node,
                     Ark_Boolean value)
{
}
void MixedModeImpl(Ark_NativePointer node,
                   Ark_MixedMode value)
{
}
void ZoomAccessImpl(Ark_NativePointer node,
                    Ark_Boolean value)
{
}
void GeolocationAccessImpl(Ark_NativePointer node,
                           Ark_Boolean value)
{
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
}
void DarkModeImpl(Ark_NativePointer node,
                  Ark_WebDarkMode value)
{
}
void ForceDarkAccessImpl(Ark_NativePointer node,
                         Ark_Boolean value)
{
}
void MediaOptionsImpl(Ark_NativePointer node,
                      const Ark_WebMediaOptions* value)
{
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
}
void OverScrollModeImpl(Ark_NativePointer node,
                        Ark_OverScrollMode value)
{
}
void TextZoomAtioImpl(Ark_NativePointer node,
                      const Ark_Number* value)
{
}
void TextZoomRatioImpl(Ark_NativePointer node,
                       const Ark_Number* value)
{
}
void DatabaseAccessImpl(Ark_NativePointer node,
                        Ark_Boolean value)
{
}
void InitialScaleImpl(Ark_NativePointer node,
                      const Ark_Number* value)
{
}
void UserAgentImpl(Ark_NativePointer node,
                   const Ark_String* value)
{
}
void MetaViewportImpl(Ark_NativePointer node,
                      Ark_Boolean value)
{
}
void OnPageEndImpl(Ark_NativePointer node,
                   const Callback_OnPageEndEvent_Void* value)
{
}
void OnPageBeginImpl(Ark_NativePointer node,
                     const Callback_OnPageBeginEvent_Void* value)
{
}
void OnProgressChangeImpl(Ark_NativePointer node,
                          const Callback_OnProgressChangeEvent_Void* value)
{
}
void OnTitleReceiveImpl(Ark_NativePointer node,
                        const Callback_OnTitleReceiveEvent_Void* value)
{
}
void OnGeolocationHideImpl(Ark_NativePointer node,
                           const Callback_Void* value)
{
}
void OnGeolocationShowImpl(Ark_NativePointer node,
                           const Callback_OnGeolocationShowEvent_Void* value)
{
}
void OnRequestSelectedImpl(Ark_NativePointer node,
                           const Callback_Void* value)
{
}
void OnAlertImpl(Ark_NativePointer node,
                 const Callback_OnAlertEvent_Boolean* value)
{
}
void OnBeforeUnloadImpl(Ark_NativePointer node,
                        const Callback_OnBeforeUnloadEvent_Boolean* value)
{
}
void OnConfirmImpl(Ark_NativePointer node,
                   const Callback_OnConfirmEvent_Boolean* value)
{
}
void OnPromptImpl(Ark_NativePointer node,
                  const Callback_OnPromptEvent_Boolean* value)
{
}
void OnConsoleImpl(Ark_NativePointer node,
                   const Callback_OnConsoleEvent_Boolean* value)
{
}
void OnErrorReceiveImpl(Ark_NativePointer node,
                        const Callback_OnErrorReceiveEvent_Void* value)
{
}
void OnHttpErrorReceiveImpl(Ark_NativePointer node,
                            const Callback_OnHttpErrorReceiveEvent_Void* value)
{
}
void OnDownloadStartImpl(Ark_NativePointer node,
                         const Callback_OnDownloadStartEvent_Void* value)
{
}
void OnRefreshAccessedHistoryImpl(Ark_NativePointer node,
                                  const Callback_OnRefreshAccessedHistoryEvent_Void* value)
{
}
void OnUrlLoadInterceptImpl(Ark_NativePointer node,
                            const Type_WebAttribute_onUrlLoadIntercept_callback* value)
{
}
void OnSslErrorReceiveImpl(Ark_NativePointer node,
                           const Callback_Literal_Function_handler_Object_error_Void* value)
{
}
void OnRenderExited0Impl(Ark_NativePointer node,
                         const Callback_OnRenderExitedEvent_Void* value)
{
}
void OnRenderExited1Impl(Ark_NativePointer node,
                         const Callback_Literal_Object_detail_Boolean* value)
{
}
void OnShowFileSelectorImpl(Ark_NativePointer node,
                            const Callback_OnShowFileSelectorEvent_Boolean* value)
{
}
void OnFileSelectorShowImpl(Ark_NativePointer node,
                            const Type_WebAttribute_onFileSelectorShow_callback* value)
{
}
void OnResourceLoadImpl(Ark_NativePointer node,
                        const Callback_OnResourceLoadEvent_Void* value)
{
}
void OnFullScreenExitImpl(Ark_NativePointer node,
                          const Callback_Void* value)
{
}
void OnFullScreenEnterImpl(Ark_NativePointer node,
                           const OnFullScreenEnterCallback* value)
{
}
void OnScaleChangeImpl(Ark_NativePointer node,
                       const Callback_OnScaleChangeEvent_Void* value)
{
}
void OnHttpAuthRequestImpl(Ark_NativePointer node,
                           const Callback_OnHttpAuthRequestEvent_Boolean* value)
{
}
void OnInterceptRequestImpl(Ark_NativePointer node,
                            const Callback_OnInterceptRequestEvent_WebResourceResponse* value)
{
}
void OnPermissionRequestImpl(Ark_NativePointer node,
                             const Callback_OnPermissionRequestEvent_Void* value)
{
}
void OnScreenCaptureRequestImpl(Ark_NativePointer node,
                                const Callback_OnScreenCaptureRequestEvent_Void* value)
{
}
void OnContextMenuShowImpl(Ark_NativePointer node,
                           const Callback_OnContextMenuShowEvent_Boolean* value)
{
}
void OnContextMenuHideImpl(Ark_NativePointer node,
                           const OnContextMenuHideCallback* value)
{
}
void MediaPlayGestureAccessImpl(Ark_NativePointer node,
                                Ark_Boolean value)
{
}
void OnSearchResultReceiveImpl(Ark_NativePointer node,
                               const Callback_OnSearchResultReceiveEvent_Void* value)
{
}
void OnScrollImpl(Ark_NativePointer node,
                  const Callback_OnScrollEvent_Void* value)
{
}
void OnSslErrorEventReceiveImpl(Ark_NativePointer node,
                                const Callback_OnSslErrorEventReceiveEvent_Void* value)
{
}
void OnSslErrorEventImpl(Ark_NativePointer node,
                         const OnSslErrorEventCallback* value)
{
}
void OnClientAuthenticationRequestImpl(Ark_NativePointer node,
                                       const Callback_OnClientAuthenticationEvent_Void* value)
{
}
void OnWindowNewImpl(Ark_NativePointer node,
                     const Callback_OnWindowNewEvent_Void* value)
{
}
void OnWindowExitImpl(Ark_NativePointer node,
                      const Callback_Void* value)
{
}
void MultiWindowAccessImpl(Ark_NativePointer node,
                           Ark_Boolean value)
{
}
void OnInterceptKeyEventImpl(Ark_NativePointer node,
                             const Callback_KeyEvent_Boolean* value)
{
}
void WebStandardFontImpl(Ark_NativePointer node,
                         const Ark_String* value)
{
}
void WebSerifFontImpl(Ark_NativePointer node,
                      const Ark_String* value)
{
}
void WebSansSerifFontImpl(Ark_NativePointer node,
                          const Ark_String* value)
{
}
void WebFixedFontImpl(Ark_NativePointer node,
                      const Ark_String* value)
{
}
void WebFantasyFontImpl(Ark_NativePointer node,
                        const Ark_String* value)
{
}
void WebCursiveFontImpl(Ark_NativePointer node,
                        const Ark_String* value)
{
}
void DefaultFixedFontSizeImpl(Ark_NativePointer node,
                              const Ark_Number* value)
{
}
void DefaultFontSizeImpl(Ark_NativePointer node,
                         const Ark_Number* value)
{
}
void MinFontSizeImpl(Ark_NativePointer node,
                     const Ark_Number* value)
{
}
void MinLogicalFontSizeImpl(Ark_NativePointer node,
                            const Ark_Number* value)
{
}
void DefaultTextEncodingFormatImpl(Ark_NativePointer node,
                                   const Ark_String* value)
{
}
void ForceDisplayScrollBarImpl(Ark_NativePointer node,
                               Ark_Boolean value)
{
}
void BlockNetworkImpl(Ark_NativePointer node,
                      Ark_Boolean value)
{
}
void HorizontalScrollBarAccessImpl(Ark_NativePointer node,
                                   Ark_Boolean value)
{
}
void VerticalScrollBarAccessImpl(Ark_NativePointer node,
                                 Ark_Boolean value)
{
}
void OnTouchIconUrlReceivedImpl(Ark_NativePointer node,
                                const Callback_OnTouchIconUrlReceivedEvent_Void* value)
{
}
void OnFaviconReceivedImpl(Ark_NativePointer node,
                           const Callback_OnFaviconReceivedEvent_Void* value)
{
}
void OnPageVisibleImpl(Ark_NativePointer node,
                       const Callback_OnPageVisibleEvent_Void* value)
{
}
void OnDataResubmittedImpl(Ark_NativePointer node,
                           const Callback_OnDataResubmittedEvent_Void* value)
{
}
void PinchSmoothImpl(Ark_NativePointer node,
                     Ark_Boolean value)
{
}
void AllowWindowOpenMethodImpl(Ark_NativePointer node,
                               Ark_Boolean value)
{
}
void OnAudioStateChangedImpl(Ark_NativePointer node,
                             const Callback_OnAudioStateChangedEvent_Void* value)
{
}
void OnFirstContentfulPaintImpl(Ark_NativePointer node,
                                const Callback_OnFirstContentfulPaintEvent_Void* value)
{
}
void OnFirstMeaningfulPaintImpl(Ark_NativePointer node,
                                const OnFirstMeaningfulPaintCallback* value)
{
}
void OnLargestContentfulPaintImpl(Ark_NativePointer node,
                                  const OnLargestContentfulPaintCallback* value)
{
}
void OnLoadInterceptImpl(Ark_NativePointer node,
                         const Callback_OnLoadInterceptEvent_Boolean* value)
{
}
void OnControllerAttachedImpl(Ark_NativePointer node,
                              const Callback_Void* value)
{
}
void OnOverScrollImpl(Ark_NativePointer node,
                      const Callback_OnOverScrollEvent_Void* value)
{
}
void OnSafeBrowsingCheckResultImpl(Ark_NativePointer node,
                                   const OnSafeBrowsingCheckResultCallback* value)
{
}
void OnNavigationEntryCommittedImpl(Ark_NativePointer node,
                                    const OnNavigationEntryCommittedCallback* value)
{
}
void OnIntelligentTrackingPreventionResultImpl(Ark_NativePointer node,
                                               const OnIntelligentTrackingPreventionCallback* value)
{
}
void JavaScriptOnDocumentStartImpl(Ark_NativePointer node,
                                   const Array_ScriptItem* value)
{
}
void JavaScriptOnDocumentEndImpl(Ark_NativePointer node,
                                 const Array_ScriptItem* value)
{
}
void LayoutModeImpl(Ark_NativePointer node,
                    Ark_WebLayoutMode value)
{
}
void NestedScrollImpl(Ark_NativePointer node,
                      const Ark_Union_NestedScrollOptions_NestedScrollOptionsExt* value)
{
}
void EnableNativeEmbedModeImpl(Ark_NativePointer node,
                               Ark_Boolean value)
{
}
void OnNativeEmbedLifecycleChangeImpl(Ark_NativePointer node,
                                      const Callback_NativeEmbedDataInfo_Void* value)
{
}
void OnNativeEmbedVisibilityChangeImpl(Ark_NativePointer node,
                                       const OnNativeEmbedVisibilityChangeCallback* value)
{
}
void OnNativeEmbedGestureEventImpl(Ark_NativePointer node,
                                   const Callback_NativeEmbedTouchInfo_Void* value)
{
}
void CopyOptionsImpl(Ark_NativePointer node,
                     Ark_CopyOptions value)
{
}
void OnOverrideUrlLoadingImpl(Ark_NativePointer node,
                              const OnOverrideUrlLoadingCallback* value)
{
}
void TextAutosizingImpl(Ark_NativePointer node,
                        Ark_Boolean value)
{
}
void EnableNativeMediaPlayerImpl(Ark_NativePointer node,
                                 const Ark_NativeMediaPlayerConfig* value)
{
}
void EnableSmoothDragResizeImpl(Ark_NativePointer node,
                                Ark_Boolean value)
{
}
void OnRenderProcessNotRespondingImpl(Ark_NativePointer node,
                                      const OnRenderProcessNotRespondingCallback* value)
{
}
void OnRenderProcessRespondingImpl(Ark_NativePointer node,
                                   const OnRenderProcessRespondingCallback* value)
{
}
void SelectionMenuOptionsImpl(Ark_NativePointer node,
                              const Array_ExpandedMenuItemOptions* value)
{
}
void OnViewportFitChangedImpl(Ark_NativePointer node,
                              const OnViewportFitChangedCallback* value)
{
}
void OnInterceptKeyboardAttachImpl(Ark_NativePointer node,
                                   const WebKeyboardCallback* value)
{
}
void OnAdsBlockedImpl(Ark_NativePointer node,
                      const OnAdsBlockedCallback* value)
{
}
void KeyboardAvoidModeImpl(Ark_NativePointer node,
                           Ark_WebKeyboardAvoidMode value)
{
}
void EditMenuOptionsImpl(Ark_NativePointer node,
                         Ark_EditMenuOptions value)
{
}
void EnableHapticFeedbackImpl(Ark_NativePointer node,
                              Ark_Boolean value)
{
}
void RegisterNativeEmbedRuleImpl(Ark_NativePointer node,
                                 const Ark_String* tag,
                                 const Ark_String* type)
{
}
void InitCallbackParams_(FrameNode* frameNode, MenuParam& dst, const Opt_Callback_Void& onAppear,
                         const Opt_Callback_Void& onDisappear)
{
}
void BindSelectionMenuImpl(Ark_NativePointer node,
                           Ark_WebElementType elementType,
                           const CustomNodeBuilder* content,
                           Ark_WebResponseType responseType,
                           const Opt_SelectionMenuOptionsExt* options)
{
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
        WebAttributeModifier::BindSelectionMenuImpl,
    };
    return &ArkUIWebModifierImpl;
}

}
