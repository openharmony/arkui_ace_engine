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
#include "core/interfaces/native/utility/converter.h"
#include "arkoala_api_generated.h"

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
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //WebModelNG::SetSetWebOptions(frameNode, convValue);
}
} // WebInterfaceModifier
namespace WebAttributeModifier {
void JavaScriptAccessImpl(Ark_NativePointer node,
                          const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetJavaScriptAccess(frameNode, convValue);
}
void FileAccessImpl(Ark_NativePointer node,
                    const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetFileAccess(frameNode, convValue);
}
void OnlineImageAccessImpl(Ark_NativePointer node,
                           const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetOnlineImageAccess(frameNode, convValue);
}
void DomStorageAccessImpl(Ark_NativePointer node,
                          const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetDomStorageAccess(frameNode, convValue);
}
void ImageAccessImpl(Ark_NativePointer node,
                     const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetImageAccess(frameNode, convValue);
}
void MixedModeImpl(Ark_NativePointer node,
                   const Opt_MixedMode* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetMixedMode(frameNode, convValue);
}
void ZoomAccessImpl(Ark_NativePointer node,
                    const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetZoomAccess(frameNode, convValue);
}
void GeolocationAccessImpl(Ark_NativePointer node,
                           const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetGeolocationAccess(frameNode, convValue);
}
void JavaScriptProxyImpl(Ark_NativePointer node,
                         const Opt_JavaScriptProxy* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetJavaScriptProxy(frameNode, convValue);
}
void CacheModeImpl(Ark_NativePointer node,
                   const Opt_CacheMode* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetCacheMode(frameNode, convValue);
}
void DarkModeImpl(Ark_NativePointer node,
                  const Opt_WebDarkMode* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetDarkMode(frameNode, convValue);
}
void ForceDarkAccessImpl(Ark_NativePointer node,
                         const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetForceDarkAccess(frameNode, convValue);
}
void MediaOptionsImpl(Ark_NativePointer node,
                      const Opt_WebMediaOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetMediaOptions(frameNode, convValue);
}
void OverviewModeAccessImpl(Ark_NativePointer node,
                            const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetOverviewModeAccess(frameNode, convValue);
}
void OverScrollModeImpl(Ark_NativePointer node,
                        const Opt_OverScrollMode* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetOverScrollMode(frameNode, convValue);
}
void BlurOnKeyboardHideModeImpl(Ark_NativePointer node,
                                const Opt_BlurOnKeyboardHideMode* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetBlurOnKeyboardHideMode(frameNode, convValue);
}
void TextZoomRatioImpl(Ark_NativePointer node,
                       const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetTextZoomRatio(frameNode, convValue);
}
void DatabaseAccessImpl(Ark_NativePointer node,
                        const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetDatabaseAccess(frameNode, convValue);
}
void InitialScaleImpl(Ark_NativePointer node,
                      const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetInitialScale(frameNode, convValue);
}
void MetaViewportImpl(Ark_NativePointer node,
                      const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetMetaViewport(frameNode, convValue);
}
void OnPageEndImpl(Ark_NativePointer node,
                   const Opt_Callback_OnPageEndEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetOnPageEnd(frameNode, convValue);
}
void OnPageBeginImpl(Ark_NativePointer node,
                     const Opt_Callback_OnPageBeginEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetOnPageBegin(frameNode, convValue);
}
void OnProgressChangeImpl(Ark_NativePointer node,
                          const Opt_Callback_OnProgressChangeEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetOnProgressChange(frameNode, convValue);
}
void OnTitleReceiveImpl(Ark_NativePointer node,
                        const Opt_Callback_OnTitleReceiveEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetOnTitleReceive(frameNode, convValue);
}
void OnGeolocationHideImpl(Ark_NativePointer node,
                           const Opt_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetOnGeolocationHide(frameNode, convValue);
}
void OnGeolocationShowImpl(Ark_NativePointer node,
                           const Opt_Callback_OnGeolocationShowEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetOnGeolocationShow(frameNode, convValue);
}
void OnRequestSelectedImpl(Ark_NativePointer node,
                           const Opt_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetOnRequestSelected(frameNode, convValue);
}
void OnAlertImpl(Ark_NativePointer node,
                 const Opt_Callback_OnAlertEvent_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetOnAlert(frameNode, convValue);
}
void OnBeforeUnloadImpl(Ark_NativePointer node,
                        const Opt_Callback_OnBeforeUnloadEvent_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetOnBeforeUnload(frameNode, convValue);
}
void OnConfirmImpl(Ark_NativePointer node,
                   const Opt_Callback_OnConfirmEvent_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetOnConfirm(frameNode, convValue);
}
void OnPromptImpl(Ark_NativePointer node,
                  const Opt_Callback_OnPromptEvent_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetOnPrompt(frameNode, convValue);
}
void OnConsoleImpl(Ark_NativePointer node,
                   const Opt_Callback_OnConsoleEvent_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetOnConsole(frameNode, convValue);
}
void OnErrorReceiveImpl(Ark_NativePointer node,
                        const Opt_Callback_OnErrorReceiveEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetOnErrorReceive(frameNode, convValue);
}
void OnHttpErrorReceiveImpl(Ark_NativePointer node,
                            const Opt_Callback_OnHttpErrorReceiveEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetOnHttpErrorReceive(frameNode, convValue);
}
void OnDownloadStartImpl(Ark_NativePointer node,
                         const Opt_Callback_OnDownloadStartEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetOnDownloadStart(frameNode, convValue);
}
void OnRefreshAccessedHistoryImpl(Ark_NativePointer node,
                                  const Opt_Callback_OnRefreshAccessedHistoryEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetOnRefreshAccessedHistory(frameNode, convValue);
}
void OnRenderExitedImpl(Ark_NativePointer node,
                        const Opt_Callback_OnRenderExitedEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetOnRenderExited(frameNode, convValue);
}
void OnShowFileSelectorImpl(Ark_NativePointer node,
                            const Opt_Callback_OnShowFileSelectorEvent_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetOnShowFileSelector(frameNode, convValue);
}
void OnResourceLoadImpl(Ark_NativePointer node,
                        const Opt_Callback_OnResourceLoadEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetOnResourceLoad(frameNode, convValue);
}
void OnFullScreenExitImpl(Ark_NativePointer node,
                          const Opt_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetOnFullScreenExit(frameNode, convValue);
}
void OnFullScreenEnterImpl(Ark_NativePointer node,
                           const Opt_OnFullScreenEnterCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetOnFullScreenEnter(frameNode, convValue);
}
void OnScaleChangeImpl(Ark_NativePointer node,
                       const Opt_Callback_OnScaleChangeEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetOnScaleChange(frameNode, convValue);
}
void OnHttpAuthRequestImpl(Ark_NativePointer node,
                           const Opt_Callback_OnHttpAuthRequestEvent_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetOnHttpAuthRequest(frameNode, convValue);
}
void OnInterceptRequestImpl(Ark_NativePointer node,
                            const Opt_Callback_OnInterceptRequestEvent_WebResourceResponse* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetOnInterceptRequest(frameNode, convValue);
}
void OnPermissionRequestImpl(Ark_NativePointer node,
                             const Opt_Callback_OnPermissionRequestEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetOnPermissionRequest(frameNode, convValue);
}
void OnScreenCaptureRequestImpl(Ark_NativePointer node,
                                const Opt_Callback_OnScreenCaptureRequestEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetOnScreenCaptureRequest(frameNode, convValue);
}
void OnContextMenuShowImpl(Ark_NativePointer node,
                           const Opt_Callback_OnContextMenuShowEvent_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetOnContextMenuShow(frameNode, convValue);
}
void OnContextMenuHideImpl(Ark_NativePointer node,
                           const Opt_OnContextMenuHideCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetOnContextMenuHide(frameNode, convValue);
}
void MediaPlayGestureAccessImpl(Ark_NativePointer node,
                                const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetMediaPlayGestureAccess(frameNode, convValue);
}
void OnSearchResultReceiveImpl(Ark_NativePointer node,
                               const Opt_Callback_OnSearchResultReceiveEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetOnSearchResultReceive(frameNode, convValue);
}
void OnScrollImpl(Ark_NativePointer node,
                  const Opt_Callback_OnScrollEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetOnScroll(frameNode, convValue);
}
void OnSslErrorEventReceiveImpl(Ark_NativePointer node,
                                const Opt_Callback_OnSslErrorEventReceiveEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetOnSslErrorEventReceive(frameNode, convValue);
}
void OnSslErrorEventImpl(Ark_NativePointer node,
                         const Opt_OnSslErrorEventCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetOnSslErrorEvent(frameNode, convValue);
}
void OnClientAuthenticationRequestImpl(Ark_NativePointer node,
                                       const Opt_Callback_OnClientAuthenticationEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetOnClientAuthenticationRequest(frameNode, convValue);
}
void OnWindowNewImpl(Ark_NativePointer node,
                     const Opt_Callback_OnWindowNewEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetOnWindowNew(frameNode, convValue);
}
void OnWindowExitImpl(Ark_NativePointer node,
                      const Opt_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetOnWindowExit(frameNode, convValue);
}
void MultiWindowAccessImpl(Ark_NativePointer node,
                           const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetMultiWindowAccess(frameNode, convValue);
}
void OnInterceptKeyEventImpl(Ark_NativePointer node,
                             const Opt_Callback_KeyEvent_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetOnInterceptKeyEvent(frameNode, convValue);
}
void WebStandardFontImpl(Ark_NativePointer node,
                         const Opt_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetWebStandardFont(frameNode, convValue);
}
void WebSerifFontImpl(Ark_NativePointer node,
                      const Opt_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetWebSerifFont(frameNode, convValue);
}
void WebSansSerifFontImpl(Ark_NativePointer node,
                          const Opt_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetWebSansSerifFont(frameNode, convValue);
}
void WebFixedFontImpl(Ark_NativePointer node,
                      const Opt_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetWebFixedFont(frameNode, convValue);
}
void WebFantasyFontImpl(Ark_NativePointer node,
                        const Opt_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetWebFantasyFont(frameNode, convValue);
}
void WebCursiveFontImpl(Ark_NativePointer node,
                        const Opt_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetWebCursiveFont(frameNode, convValue);
}
void DefaultFixedFontSizeImpl(Ark_NativePointer node,
                              const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetDefaultFixedFontSize(frameNode, convValue);
}
void DefaultFontSizeImpl(Ark_NativePointer node,
                         const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetDefaultFontSize(frameNode, convValue);
}
void MinFontSizeImpl(Ark_NativePointer node,
                     const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetMinFontSize(frameNode, convValue);
}
void MinLogicalFontSizeImpl(Ark_NativePointer node,
                            const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetMinLogicalFontSize(frameNode, convValue);
}
void DefaultTextEncodingFormatImpl(Ark_NativePointer node,
                                   const Opt_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetDefaultTextEncodingFormat(frameNode, convValue);
}
void ForceDisplayScrollBarImpl(Ark_NativePointer node,
                               const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetForceDisplayScrollBar(frameNode, convValue);
}
void BlockNetworkImpl(Ark_NativePointer node,
                      const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetBlockNetwork(frameNode, convValue);
}
void HorizontalScrollBarAccessImpl(Ark_NativePointer node,
                                   const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetHorizontalScrollBarAccess(frameNode, convValue);
}
void VerticalScrollBarAccessImpl(Ark_NativePointer node,
                                 const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetVerticalScrollBarAccess(frameNode, convValue);
}
void OnTouchIconUrlReceivedImpl(Ark_NativePointer node,
                                const Opt_Callback_OnTouchIconUrlReceivedEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetOnTouchIconUrlReceived(frameNode, convValue);
}
void OnFaviconReceivedImpl(Ark_NativePointer node,
                           const Opt_Callback_OnFaviconReceivedEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetOnFaviconReceived(frameNode, convValue);
}
void OnPageVisibleImpl(Ark_NativePointer node,
                       const Opt_Callback_OnPageVisibleEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetOnPageVisible(frameNode, convValue);
}
void OnDataResubmittedImpl(Ark_NativePointer node,
                           const Opt_Callback_OnDataResubmittedEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetOnDataResubmitted(frameNode, convValue);
}
void PinchSmoothImpl(Ark_NativePointer node,
                     const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetPinchSmooth(frameNode, convValue);
}
void AllowWindowOpenMethodImpl(Ark_NativePointer node,
                               const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetAllowWindowOpenMethod(frameNode, convValue);
}
void OnAudioStateChangedImpl(Ark_NativePointer node,
                             const Opt_Callback_OnAudioStateChangedEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetOnAudioStateChanged(frameNode, convValue);
}
void OnFirstContentfulPaintImpl(Ark_NativePointer node,
                                const Opt_Callback_OnFirstContentfulPaintEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetOnFirstContentfulPaint(frameNode, convValue);
}
void OnFirstMeaningfulPaintImpl(Ark_NativePointer node,
                                const Opt_OnFirstMeaningfulPaintCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetOnFirstMeaningfulPaint(frameNode, convValue);
}
void OnLargestContentfulPaintImpl(Ark_NativePointer node,
                                  const Opt_OnLargestContentfulPaintCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetOnLargestContentfulPaint(frameNode, convValue);
}
void OnLoadInterceptImpl(Ark_NativePointer node,
                         const Opt_Callback_OnLoadInterceptEvent_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetOnLoadIntercept(frameNode, convValue);
}
void OnControllerAttachedImpl(Ark_NativePointer node,
                              const Opt_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetOnControllerAttached(frameNode, convValue);
}
void OnOverScrollImpl(Ark_NativePointer node,
                      const Opt_Callback_OnOverScrollEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetOnOverScroll(frameNode, convValue);
}
void OnSafeBrowsingCheckResultImpl(Ark_NativePointer node,
                                   const Opt_OnSafeBrowsingCheckResultCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetOnSafeBrowsingCheckResult(frameNode, convValue);
}
void OnNavigationEntryCommittedImpl(Ark_NativePointer node,
                                    const Opt_OnNavigationEntryCommittedCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetOnNavigationEntryCommitted(frameNode, convValue);
}
void OnIntelligentTrackingPreventionResultImpl(Ark_NativePointer node,
                                               const Opt_OnIntelligentTrackingPreventionCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetOnIntelligentTrackingPreventionResult(frameNode, convValue);
}
void JavaScriptOnDocumentStartImpl(Ark_NativePointer node,
                                   const Opt_Array_ScriptItem* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetJavaScriptOnDocumentStart(frameNode, convValue);
}
void JavaScriptOnDocumentEndImpl(Ark_NativePointer node,
                                 const Opt_Array_ScriptItem* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetJavaScriptOnDocumentEnd(frameNode, convValue);
}
void LayoutModeImpl(Ark_NativePointer node,
                    const Opt_WebLayoutMode* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetLayoutMode(frameNode, convValue);
}
void NestedScrollImpl(Ark_NativePointer node,
                      const Opt_Union_NestedScrollOptions_NestedScrollOptionsExt* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetNestedScroll(frameNode, convValue);
}
void EnableNativeEmbedModeImpl(Ark_NativePointer node,
                               const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetEnableNativeEmbedMode(frameNode, convValue);
}
void OnNativeEmbedLifecycleChangeImpl(Ark_NativePointer node,
                                      const Opt_Callback_NativeEmbedDataInfo_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetOnNativeEmbedLifecycleChange(frameNode, convValue);
}
void OnNativeEmbedVisibilityChangeImpl(Ark_NativePointer node,
                                       const Opt_OnNativeEmbedVisibilityChangeCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetOnNativeEmbedVisibilityChange(frameNode, convValue);
}
void OnNativeEmbedGestureEventImpl(Ark_NativePointer node,
                                   const Opt_Callback_NativeEmbedTouchInfo_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetOnNativeEmbedGestureEvent(frameNode, convValue);
}
void CopyOptionsImpl(Ark_NativePointer node,
                     const Opt_CopyOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetCopyOptions(frameNode, convValue);
}
void OnOverrideUrlLoadingImpl(Ark_NativePointer node,
                              const Opt_OnOverrideUrlLoadingCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetOnOverrideUrlLoading(frameNode, convValue);
}
void TextAutosizingImpl(Ark_NativePointer node,
                        const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetTextAutosizing(frameNode, convValue);
}
void EnableNativeMediaPlayerImpl(Ark_NativePointer node,
                                 const Opt_NativeMediaPlayerConfig* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetEnableNativeMediaPlayer(frameNode, convValue);
}
void OnRenderProcessNotRespondingImpl(Ark_NativePointer node,
                                      const Opt_OnRenderProcessNotRespondingCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetOnRenderProcessNotResponding(frameNode, convValue);
}
void OnRenderProcessRespondingImpl(Ark_NativePointer node,
                                   const Opt_OnRenderProcessRespondingCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetOnRenderProcessResponding(frameNode, convValue);
}
void OnViewportFitChangedImpl(Ark_NativePointer node,
                              const Opt_OnViewportFitChangedCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetOnViewportFitChanged(frameNode, convValue);
}
void OnInterceptKeyboardAttachImpl(Ark_NativePointer node,
                                   const Opt_WebKeyboardCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetOnInterceptKeyboardAttach(frameNode, convValue);
}
void OnAdsBlockedImpl(Ark_NativePointer node,
                      const Opt_OnAdsBlockedCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetOnAdsBlocked(frameNode, convValue);
}
void KeyboardAvoidModeImpl(Ark_NativePointer node,
                           const Opt_WebKeyboardAvoidMode* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetKeyboardAvoidMode(frameNode, convValue);
}
void EditMenuOptionsImpl(Ark_NativePointer node,
                         const Opt_EditMenuOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetEditMenuOptions(frameNode, convValue);
}
void EnableHapticFeedbackImpl(Ark_NativePointer node,
                              const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetEnableHapticFeedback(frameNode, convValue);
}
void OptimizeParserBudgetImpl(Ark_NativePointer node,
                              const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetOptimizeParserBudget(frameNode, convValue);
}
void EnableFollowSystemFontWeightImpl(Ark_NativePointer node,
                                      const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetEnableFollowSystemFontWeight(frameNode, convValue);
}
void EnableWebAVSessionImpl(Ark_NativePointer node,
                            const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetEnableWebAVSession(frameNode, convValue);
}
void RunJavaScriptOnDocumentStartImpl(Ark_NativePointer node,
                                      const Opt_Array_ScriptItem* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetRunJavaScriptOnDocumentStart(frameNode, convValue);
}
void RunJavaScriptOnDocumentEndImpl(Ark_NativePointer node,
                                    const Opt_Array_ScriptItem* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetRunJavaScriptOnDocumentEnd(frameNode, convValue);
}
void RunJavaScriptOnHeadEndImpl(Ark_NativePointer node,
                                const Opt_Array_ScriptItem* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetRunJavaScriptOnHeadEnd(frameNode, convValue);
}
void NativeEmbedOptionsImpl(Ark_NativePointer node,
                            const Opt_EmbedOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WebModelNG::SetNativeEmbedOptions(frameNode, convValue);
}
void RegisterNativeEmbedRuleImpl(Ark_NativePointer node,
                                 const Opt_String* tag,
                                 const Opt_String* type)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(tag);
    //auto convValue = Converter::OptConvert<type>(tag); // for enums
    //WebModelNG::SetRegisterNativeEmbedRule(frameNode, convValue);
}
void BindSelectionMenuImpl(Ark_NativePointer node,
                           const Opt_WebElementType* elementType,
                           const Opt_CustomNodeBuilder* content,
                           const Opt_WebResponseType* responseType,
                           const Opt_SelectionMenuOptionsExt* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(elementType);
    //auto convValue = Converter::OptConvert<type>(elementType); // for enums
    //WebModelNG::SetBindSelectionMenu(frameNode, convValue);
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
        WebAttributeModifier::CacheModeImpl,
        WebAttributeModifier::DarkModeImpl,
        WebAttributeModifier::ForceDarkAccessImpl,
        WebAttributeModifier::MediaOptionsImpl,
        WebAttributeModifier::OverviewModeAccessImpl,
        WebAttributeModifier::OverScrollModeImpl,
        WebAttributeModifier::BlurOnKeyboardHideModeImpl,
        WebAttributeModifier::TextZoomRatioImpl,
        WebAttributeModifier::DatabaseAccessImpl,
        WebAttributeModifier::InitialScaleImpl,
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
        WebAttributeModifier::OnRenderExitedImpl,
        WebAttributeModifier::OnShowFileSelectorImpl,
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
