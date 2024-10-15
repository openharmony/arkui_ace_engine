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
#include "core/interfaces/arkoala/utility/converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
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
                          Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    [[maybe_unused]]
    auto convValue = Converter::Convert<bool>(value);
    //WebModelNG::SetJavaScriptAccess(frameNode, convValue);
}
void FileAccessImpl(Ark_NativePointer node,
                    Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    [[maybe_unused]]
    auto convValue = Converter::Convert<bool>(value);
    //WebModelNG::SetFileAccess(frameNode, convValue);
}
void OnlineImageAccessImpl(Ark_NativePointer node,
                           Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    [[maybe_unused]]
    auto convValue = Converter::Convert<bool>(value);
    //WebModelNG::SetOnlineImageAccess(frameNode, convValue);
}
void DomStorageAccessImpl(Ark_NativePointer node,
                          Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    [[maybe_unused]]
    auto convValue = Converter::Convert<bool>(value);
    //WebModelNG::SetDomStorageAccess(frameNode, convValue);
}
void ImageAccessImpl(Ark_NativePointer node,
                     Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    [[maybe_unused]]
    auto convValue = Converter::Convert<bool>(value);
    //WebModelNG::SetImageAccess(frameNode, convValue);
}
void MixedModeImpl(Ark_NativePointer node,
                   Ark_MixedMode value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //WebModelNG::SetMixedMode(frameNode, convValue);
}
void ZoomAccessImpl(Ark_NativePointer node,
                    Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    [[maybe_unused]]
    auto convValue = Converter::Convert<bool>(value);
    //WebModelNG::SetZoomAccess(frameNode, convValue);
}
void GeolocationAccessImpl(Ark_NativePointer node,
                           Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    [[maybe_unused]]
    auto convValue = Converter::Convert<bool>(value);
    //WebModelNG::SetGeolocationAccess(frameNode, convValue);
}
void JavaScriptProxyImpl(Ark_NativePointer node,
                         const Ark_JavaScriptProxy* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //WebModelNG::SetJavaScriptProxy(frameNode, convValue);
}
void PasswordImpl(Ark_NativePointer node,
                  Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    [[maybe_unused]]
    auto convValue = Converter::Convert<bool>(value);
    //WebModelNG::SetPassword(frameNode, convValue);
}
void CacheModeImpl(Ark_NativePointer node,
                   Ark_CacheMode value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //WebModelNG::SetCacheMode(frameNode, convValue);
}
void DarkModeImpl(Ark_NativePointer node,
                  Ark_WebDarkMode value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //WebModelNG::SetDarkMode(frameNode, convValue);
}
void ForceDarkAccessImpl(Ark_NativePointer node,
                         Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    [[maybe_unused]]
    auto convValue = Converter::Convert<bool>(value);
    //WebModelNG::SetForceDarkAccess(frameNode, convValue);
}
void MediaOptionsImpl(Ark_NativePointer node,
                      const Ark_WebMediaOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //WebModelNG::SetMediaOptions(frameNode, convValue);
}
void TableDataImpl(Ark_NativePointer node,
                   Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    [[maybe_unused]]
    auto convValue = Converter::Convert<bool>(value);
    //WebModelNG::SetTableData(frameNode, convValue);
}
void WideViewModeAccessImpl(Ark_NativePointer node,
                            Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    [[maybe_unused]]
    auto convValue = Converter::Convert<bool>(value);
    //WebModelNG::SetWideViewModeAccess(frameNode, convValue);
}
void OverviewModeAccessImpl(Ark_NativePointer node,
                            Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    [[maybe_unused]]
    auto convValue = Converter::Convert<bool>(value);
    //WebModelNG::SetOverviewModeAccess(frameNode, convValue);
}
void OverScrollModeImpl(Ark_NativePointer node,
                        Ark_OverScrollMode value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //WebModelNG::SetOverScrollMode(frameNode, convValue);
}
void TextZoomAtioImpl(Ark_NativePointer node,
                      const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //WebModelNG::SetTextZoomAtio(frameNode, convValue);
}
void TextZoomRatioImpl(Ark_NativePointer node,
                       const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //WebModelNG::SetTextZoomRatio(frameNode, convValue);
}
void DatabaseAccessImpl(Ark_NativePointer node,
                        Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    [[maybe_unused]]
    auto convValue = Converter::Convert<bool>(value);
    //WebModelNG::SetDatabaseAccess(frameNode, convValue);
}
void InitialScaleImpl(Ark_NativePointer node,
                      const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //WebModelNG::SetInitialScale(frameNode, convValue);
}
void UserAgentImpl(Ark_NativePointer node,
                   const Ark_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    [[maybe_unused]]
    auto convValue = Converter::Convert<std::string>(*value);
    //WebModelNG::SetUserAgent(frameNode, convValue);
}
void MetaViewportImpl(Ark_NativePointer node,
                      Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    [[maybe_unused]]
    auto convValue = Converter::Convert<bool>(value);
    //WebModelNG::SetMetaViewport(frameNode, convValue);
}
void OnPageEndImpl(Ark_NativePointer node,
                   Ark_Function value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnPageEnd(frameNode, convValue);
}
void OnPageBeginImpl(Ark_NativePointer node,
                     Ark_Function value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnPageBegin(frameNode, convValue);
}
void OnProgressChangeImpl(Ark_NativePointer node,
                          Ark_Function value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnProgressChange(frameNode, convValue);
}
void OnTitleReceiveImpl(Ark_NativePointer node,
                        Ark_Function value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnTitleReceive(frameNode, convValue);
}
void OnGeolocationHideImpl(Ark_NativePointer node,
                           Ark_Function value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnGeolocationHide(frameNode, convValue);
}
void OnGeolocationShowImpl(Ark_NativePointer node,
                           Ark_Function value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnGeolocationShow(frameNode, convValue);
}
void OnRequestSelectedImpl(Ark_NativePointer node,
                           Ark_Function value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnRequestSelected(frameNode, convValue);
}
void OnAlertImpl(Ark_NativePointer node,
                 Ark_Function value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnAlert(frameNode, convValue);
}
void OnBeforeUnloadImpl(Ark_NativePointer node,
                        Ark_Function value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnBeforeUnload(frameNode, convValue);
}
void OnConfirmImpl(Ark_NativePointer node,
                   Ark_Function value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnConfirm(frameNode, convValue);
}
void OnPromptImpl(Ark_NativePointer node,
                  Ark_Function value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnPrompt(frameNode, convValue);
}
void OnConsoleImpl(Ark_NativePointer node,
                   Ark_Function value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnConsole(frameNode, convValue);
}
void OnErrorReceiveImpl(Ark_NativePointer node,
                        Ark_Function value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnErrorReceive(frameNode, convValue);
}
void OnHttpErrorReceiveImpl(Ark_NativePointer node,
                            Ark_Function value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnHttpErrorReceive(frameNode, convValue);
}
void OnDownloadStartImpl(Ark_NativePointer node,
                         Ark_Function value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnDownloadStart(frameNode, convValue);
}
void OnRefreshAccessedHistoryImpl(Ark_NativePointer node,
                                  Ark_Function value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnRefreshAccessedHistory(frameNode, convValue);
}
void OnUrlLoadInterceptImpl(Ark_NativePointer node,
                            Ark_Function value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnUrlLoadIntercept(frameNode, convValue);
}
void OnSslErrorReceiveImpl(Ark_NativePointer node,
                           Ark_Function value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnSslErrorReceive(frameNode, convValue);
}
void OnRenderExited0Impl(Ark_NativePointer node,
                         Ark_Function value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnRenderExited0(frameNode, convValue);
}
void OnShowFileSelectorImpl(Ark_NativePointer node,
                            Ark_Function value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnShowFileSelector(frameNode, convValue);
}
void OnRenderExited1Impl(Ark_NativePointer node,
                         Ark_Function value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnRenderExited1(frameNode, convValue);
}
void OnFileSelectorShowImpl(Ark_NativePointer node,
                            Ark_Function value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnFileSelectorShow(frameNode, convValue);
}
void OnResourceLoadImpl(Ark_NativePointer node,
                        Ark_Function value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnResourceLoad(frameNode, convValue);
}
void OnFullScreenExitImpl(Ark_NativePointer node,
                          Ark_Function value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnFullScreenExit(frameNode, convValue);
}
void OnFullScreenEnterImpl(Ark_NativePointer node,
                           Ark_Function value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnFullScreenEnter(frameNode, convValue);
}
void OnScaleChangeImpl(Ark_NativePointer node,
                       Ark_Function value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnScaleChange(frameNode, convValue);
}
void OnHttpAuthRequestImpl(Ark_NativePointer node,
                           Ark_Function value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnHttpAuthRequest(frameNode, convValue);
}
void OnInterceptRequestImpl(Ark_NativePointer node,
                            Ark_Function value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnInterceptRequest(frameNode, convValue);
}
void OnPermissionRequestImpl(Ark_NativePointer node,
                             Ark_Function value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnPermissionRequest(frameNode, convValue);
}
void OnScreenCaptureRequestImpl(Ark_NativePointer node,
                                Ark_Function value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnScreenCaptureRequest(frameNode, convValue);
}
void OnContextMenuShowImpl(Ark_NativePointer node,
                           Ark_Function value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnContextMenuShow(frameNode, convValue);
}
void OnContextMenuHideImpl(Ark_NativePointer node,
                           Ark_Function value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnContextMenuHide(frameNode, convValue);
}
void MediaPlayGestureAccessImpl(Ark_NativePointer node,
                                Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    [[maybe_unused]]
    auto convValue = Converter::Convert<bool>(value);
    //WebModelNG::SetMediaPlayGestureAccess(frameNode, convValue);
}
void OnSearchResultReceiveImpl(Ark_NativePointer node,
                               Ark_Function value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnSearchResultReceive(frameNode, convValue);
}
void OnScrollImpl(Ark_NativePointer node,
                  Ark_Function value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnScroll(frameNode, convValue);
}
void OnSslErrorEventReceiveImpl(Ark_NativePointer node,
                                Ark_Function value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnSslErrorEventReceive(frameNode, convValue);
}
void OnSslErrorEventImpl(Ark_NativePointer node,
                         Ark_Function value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnSslErrorEvent(frameNode, convValue);
}
void OnClientAuthenticationRequestImpl(Ark_NativePointer node,
                                       Ark_Function value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnClientAuthenticationRequest(frameNode, convValue);
}
void OnWindowNewImpl(Ark_NativePointer node,
                     Ark_Function value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnWindowNew(frameNode, convValue);
}
void OnWindowExitImpl(Ark_NativePointer node,
                      Ark_Function value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnWindowExit(frameNode, convValue);
}
void MultiWindowAccessImpl(Ark_NativePointer node,
                           Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    [[maybe_unused]]
    auto convValue = Converter::Convert<bool>(value);
    //WebModelNG::SetMultiWindowAccess(frameNode, convValue);
}
void OnInterceptKeyEventImpl(Ark_NativePointer node,
                             Ark_Function value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnInterceptKeyEvent(frameNode, convValue);
}
void WebStandardFontImpl(Ark_NativePointer node,
                         const Ark_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    [[maybe_unused]]
    auto convValue = Converter::Convert<std::string>(*value);
    //WebModelNG::SetWebStandardFont(frameNode, convValue);
}
void WebSerifFontImpl(Ark_NativePointer node,
                      const Ark_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    [[maybe_unused]]
    auto convValue = Converter::Convert<std::string>(*value);
    //WebModelNG::SetWebSerifFont(frameNode, convValue);
}
void WebSansSerifFontImpl(Ark_NativePointer node,
                          const Ark_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    [[maybe_unused]]
    auto convValue = Converter::Convert<std::string>(*value);
    //WebModelNG::SetWebSansSerifFont(frameNode, convValue);
}
void WebFixedFontImpl(Ark_NativePointer node,
                      const Ark_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    [[maybe_unused]]
    auto convValue = Converter::Convert<std::string>(*value);
    //WebModelNG::SetWebFixedFont(frameNode, convValue);
}
void WebFantasyFontImpl(Ark_NativePointer node,
                        const Ark_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    [[maybe_unused]]
    auto convValue = Converter::Convert<std::string>(*value);
    //WebModelNG::SetWebFantasyFont(frameNode, convValue);
}
void WebCursiveFontImpl(Ark_NativePointer node,
                        const Ark_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    [[maybe_unused]]
    auto convValue = Converter::Convert<std::string>(*value);
    //WebModelNG::SetWebCursiveFont(frameNode, convValue);
}
void DefaultFixedFontSizeImpl(Ark_NativePointer node,
                              const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //WebModelNG::SetDefaultFixedFontSize(frameNode, convValue);
}
void DefaultFontSizeImpl(Ark_NativePointer node,
                         const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //WebModelNG::SetDefaultFontSize(frameNode, convValue);
}
void MinFontSizeImpl(Ark_NativePointer node,
                     const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //WebModelNG::SetMinFontSize(frameNode, convValue);
}
void MinLogicalFontSizeImpl(Ark_NativePointer node,
                            const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //WebModelNG::SetMinLogicalFontSize(frameNode, convValue);
}
void DefaultTextEncodingFormatImpl(Ark_NativePointer node,
                                   const Ark_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    [[maybe_unused]]
    auto convValue = Converter::Convert<std::string>(*value);
    //WebModelNG::SetDefaultTextEncodingFormat(frameNode, convValue);
}
void ForceDisplayScrollBarImpl(Ark_NativePointer node,
                               Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    [[maybe_unused]]
    auto convValue = Converter::Convert<bool>(value);
    //WebModelNG::SetForceDisplayScrollBar(frameNode, convValue);
}
void BlockNetworkImpl(Ark_NativePointer node,
                      Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    [[maybe_unused]]
    auto convValue = Converter::Convert<bool>(value);
    //WebModelNG::SetBlockNetwork(frameNode, convValue);
}
void HorizontalScrollBarAccessImpl(Ark_NativePointer node,
                                   Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    [[maybe_unused]]
    auto convValue = Converter::Convert<bool>(value);
    //WebModelNG::SetHorizontalScrollBarAccess(frameNode, convValue);
}
void VerticalScrollBarAccessImpl(Ark_NativePointer node,
                                 Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    [[maybe_unused]]
    auto convValue = Converter::Convert<bool>(value);
    //WebModelNG::SetVerticalScrollBarAccess(frameNode, convValue);
}
void OnTouchIconUrlReceivedImpl(Ark_NativePointer node,
                                Ark_Function value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnTouchIconUrlReceived(frameNode, convValue);
}
void OnFaviconReceivedImpl(Ark_NativePointer node,
                           Ark_Function value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnFaviconReceived(frameNode, convValue);
}
void OnPageVisibleImpl(Ark_NativePointer node,
                       Ark_Function value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnPageVisible(frameNode, convValue);
}
void OnDataResubmittedImpl(Ark_NativePointer node,
                           Ark_Function value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnDataResubmitted(frameNode, convValue);
}
void PinchSmoothImpl(Ark_NativePointer node,
                     Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    [[maybe_unused]]
    auto convValue = Converter::Convert<bool>(value);
    //WebModelNG::SetPinchSmooth(frameNode, convValue);
}
void AllowWindowOpenMethodImpl(Ark_NativePointer node,
                               Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    [[maybe_unused]]
    auto convValue = Converter::Convert<bool>(value);
    //WebModelNG::SetAllowWindowOpenMethod(frameNode, convValue);
}
void OnAudioStateChangedImpl(Ark_NativePointer node,
                             Ark_Function value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnAudioStateChanged(frameNode, convValue);
}
void OnFirstContentfulPaintImpl(Ark_NativePointer node,
                                Ark_Function value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnFirstContentfulPaint(frameNode, convValue);
}
void OnFirstMeaningfulPaintImpl(Ark_NativePointer node,
                                Ark_Function value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnFirstMeaningfulPaint(frameNode, convValue);
}
void OnLargestContentfulPaintImpl(Ark_NativePointer node,
                                  Ark_Function value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnLargestContentfulPaint(frameNode, convValue);
}
void OnLoadInterceptImpl(Ark_NativePointer node,
                         Ark_Function value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnLoadIntercept(frameNode, convValue);
}
void OnControllerAttachedImpl(Ark_NativePointer node,
                              Ark_Function value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnControllerAttached(frameNode, convValue);
}
void OnOverScrollImpl(Ark_NativePointer node,
                      Ark_Function value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnOverScroll(frameNode, convValue);
}
void OnSafeBrowsingCheckResultImpl(Ark_NativePointer node,
                                   Ark_Function value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnSafeBrowsingCheckResult(frameNode, convValue);
}
void OnNavigationEntryCommittedImpl(Ark_NativePointer node,
                                    Ark_Function value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnNavigationEntryCommitted(frameNode, convValue);
}
void OnIntelligentTrackingPreventionResultImpl(Ark_NativePointer node,
                                               Ark_Function value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnIntelligentTrackingPreventionResult(frameNode, convValue);
}
void JavaScriptOnDocumentStartImpl(Ark_NativePointer node,
                                   const Array_ScriptItem* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //WebModelNG::SetJavaScriptOnDocumentStart(frameNode, convValue);
}
void JavaScriptOnDocumentEndImpl(Ark_NativePointer node,
                                 const Array_ScriptItem* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //WebModelNG::SetJavaScriptOnDocumentEnd(frameNode, convValue);
}
void LayoutModeImpl(Ark_NativePointer node,
                    Ark_WebLayoutMode value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //WebModelNG::SetLayoutMode(frameNode, convValue);
}
void NestedScrollImpl(Ark_NativePointer node,
                      const Ark_Union_NestedScrollOptions_NestedScrollOptionsExt* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //WebModelNG::SetNestedScroll(frameNode, convValue);
}
void EnableNativeEmbedModeImpl(Ark_NativePointer node,
                               Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    [[maybe_unused]]
    auto convValue = Converter::Convert<bool>(value);
    //WebModelNG::SetEnableNativeEmbedMode(frameNode, convValue);
}
void OnNativeEmbedLifecycleChangeImpl(Ark_NativePointer node,
                                      Ark_Function value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnNativeEmbedLifecycleChange(frameNode, convValue);
}
void OnNativeEmbedVisibilityChangeImpl(Ark_NativePointer node,
                                       Ark_Function value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnNativeEmbedVisibilityChange(frameNode, convValue);
}
void OnNativeEmbedGestureEventImpl(Ark_NativePointer node,
                                   Ark_Function value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnNativeEmbedGestureEvent(frameNode, convValue);
}
void CopyOptionsImpl(Ark_NativePointer node,
                     Ark_CopyOptions value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //WebModelNG::SetCopyOptions(frameNode, convValue);
}
void OnOverrideUrlLoadingImpl(Ark_NativePointer node,
                              Ark_Function value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnOverrideUrlLoading(frameNode, convValue);
}
void TextAutosizingImpl(Ark_NativePointer node,
                        Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    [[maybe_unused]]
    auto convValue = Converter::Convert<bool>(value);
    //WebModelNG::SetTextAutosizing(frameNode, convValue);
}
void EnableNativeMediaPlayerImpl(Ark_NativePointer node,
                                 const Ark_NativeMediaPlayerConfig* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //WebModelNG::SetEnableNativeMediaPlayer(frameNode, convValue);
}
void EnableSmoothDragResizeImpl(Ark_NativePointer node,
                                Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    [[maybe_unused]]
    auto convValue = Converter::Convert<bool>(value);
    //WebModelNG::SetEnableSmoothDragResize(frameNode, convValue);
}
void OnRenderProcessNotRespondingImpl(Ark_NativePointer node,
                                      Ark_Function value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnRenderProcessNotResponding(frameNode, convValue);
}
void OnRenderProcessRespondingImpl(Ark_NativePointer node,
                                   Ark_Function value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnRenderProcessResponding(frameNode, convValue);
}
void SelectionMenuOptionsImpl(Ark_NativePointer node,
                              const Array_ExpandedMenuItemOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //WebModelNG::SetSelectionMenuOptions(frameNode, convValue);
}
void OnViewportFitChangedImpl(Ark_NativePointer node,
                              Ark_Function value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnViewportFitChanged(frameNode, convValue);
}
void OnInterceptKeyboardAttachImpl(Ark_NativePointer node,
                                   Ark_Function value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnInterceptKeyboardAttach(frameNode, convValue);
}
void OnAdsBlockedImpl(Ark_NativePointer node,
                      Ark_Function value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnAdsBlocked(frameNode, convValue);
}
void KeyboardAvoidModeImpl(Ark_NativePointer node,
                           Ark_WebKeyboardAvoidMode value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //WebModelNG::SetKeyboardAvoidMode(frameNode, convValue);
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
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    [[maybe_unused]]
    auto convValue = Converter::Convert<bool>(value);
    //WebModelNG::SetEnableHapticFeedback(frameNode, convValue);
}
void RegisterNativeEmbedRuleImpl(Ark_NativePointer node,
                                 const Ark_String* tag,
                                 const Ark_String* type)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(tag);
    //auto convValue = Converter::OptConvert<type>(tag); // for enums
    //WebModelNG::SetRegisterNativeEmbedRule(frameNode, convValue);
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
        WebAttributeModifier::OnShowFileSelectorImpl,
        WebAttributeModifier::OnRenderExited1Impl,
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
