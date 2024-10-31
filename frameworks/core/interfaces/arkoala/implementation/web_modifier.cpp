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
#endif
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
#endif
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
#endif
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
    LOGE("WebInterfaceModifier::SetWebOptionsImpl controller option is not supported");
#endif
}
} // WebInterfaceModifier
namespace WebAttributeModifier {
void JavaScriptAccessImpl(Ark_NativePointer node,
                          Ark_Boolean javaScriptAccess)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(javaScriptAccess);
    WebModelNG::SetJsEnabled(frameNode, convValue);
#endif
}
void FileAccessImpl(Ark_NativePointer node,
                    Ark_Boolean fileAccess)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(fileAccess);
    WebModelNG::SetFileAccessEnabled(frameNode, convValue);
#endif
}
void OnlineImageAccessImpl(Ark_NativePointer node,
                           Ark_Boolean onlineImageAccess)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(onlineImageAccess);
    WebModelNG::SetOnLineImageAccessEnabled(frameNode, convValue);
#endif
}
void DomStorageAccessImpl(Ark_NativePointer node,
                          Ark_Boolean domStorageAccess)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(domStorageAccess);
    WebModelNG::SetDomStorageAccessEnabled(frameNode, convValue);
#endif
}
void ImageAccessImpl(Ark_NativePointer node,
                     Ark_Boolean imageAccess)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(imageAccess);
    WebModelNG::SetImageAccessEnabled(frameNode, convValue);
#endif
}
void MixedModeImpl(Ark_NativePointer node,
                   Ark_MixedMode mixedMode)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<MixedModeContent>(mixedMode);
    WebModelNG::SetMixedMode(frameNode, convValue);
#endif
}
void ZoomAccessImpl(Ark_NativePointer node,
                    Ark_Boolean zoomAccess)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(zoomAccess);
    WebModelNG::SetZoomAccessEnabled(frameNode, convValue);
#endif
}
void GeolocationAccessImpl(Ark_NativePointer node,
                           Ark_Boolean geolocationAccess)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(geolocationAccess);
    WebModelNG::SetGeolocationAccessEnabled(frameNode, convValue);
#endif
}
void JavaScriptProxyImpl(Ark_NativePointer node,
                         const Ark_JavaScriptProxy* javaScriptProxy)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(javaScriptProxy);
    LOGE("WebInterfaceModifier::JavaScriptProxyImpl method is not implemented");
}
void PasswordImpl(Ark_NativePointer node,
                  Ark_Boolean password)
{
    // deprecated
}
void CacheModeImpl(Ark_NativePointer node,
                   Ark_CacheMode cacheMode)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<WebCacheMode>(cacheMode);
    WebModelNG::SetCacheMode(frameNode, convValue);
#endif
}
void DarkModeImpl(Ark_NativePointer node,
                  Ark_WebDarkMode mode)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<WebDarkMode>(mode);
    WebModelNG::SetDarkMode(frameNode, convValue);
#endif
}
void ForceDarkAccessImpl(Ark_NativePointer node,
                         Ark_Boolean access)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(access);
    WebModelNG::SetForceDarkAccess(frameNode, convValue);
#endif
}
void MediaOptionsImpl(Ark_NativePointer node,
                      const Ark_WebMediaOptions* options)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(options);
    WebModelNG::SetAudioResumeInterval(frameNode, Converter::OptConvert<int32_t>(options->resumeInterval));
    WebModelNG::SetAudioExclusive(frameNode, Converter::OptConvert<bool>(options->audioExclusive));
#endif
}
void TableDataImpl(Ark_NativePointer node,
                   Ark_Boolean tableData)
{
    // deprecated
}
void WideViewModeAccessImpl(Ark_NativePointer node,
                            Ark_Boolean wideViewModeAccess)
{
    // deprecated
}
void OverviewModeAccessImpl(Ark_NativePointer node,
                            Ark_Boolean overviewModeAccess)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(overviewModeAccess);
    WebModelNG::SetOverviewModeAccessEnabled(frameNode, convValue);
#endif
}
void OverScrollModeImpl(Ark_NativePointer node,
                        Ark_OverScrollMode mode)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<OverScrollMode>(mode);
    WebModelNG::SetOverScrollMode(frameNode, convValue);
#endif
}
void TextZoomAtioImpl(Ark_NativePointer node,
                      const Ark_Number* textZoomAtio)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(textZoomAtio);
    auto convValue = Converter::Convert<int32_t>(*textZoomAtio);
    WebModelNG::SetTextZoomRatio(frameNode, convValue);
#endif
}
void TextZoomRatioImpl(Ark_NativePointer node,
                       const Ark_Number* textZoomRatio)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(textZoomRatio);
    auto convValue = Converter::Convert<int32_t>(*textZoomRatio);
    WebModelNG::SetTextZoomRatio(frameNode, convValue);
#endif
}
void DatabaseAccessImpl(Ark_NativePointer node,
                        Ark_Boolean databaseAccess)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(databaseAccess);
    WebModelNG::SetDatabaseAccessEnabled(frameNode, convValue);
#endif
}
void InitialScaleImpl(Ark_NativePointer node,
                      const Ark_Number* percent)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(percent);
    auto convValue = Converter::Convert<float>(*percent);
    WebModelNG::InitialScale(frameNode, convValue);
#endif
}
void UserAgentImpl(Ark_NativePointer node,
                   const Ark_String* userAgent)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(userAgent);
    auto convValue = Converter::Convert<std::string>(*userAgent);
    WebModelNG::SetUserAgent(frameNode, convValue);
#endif
}
void MetaViewportImpl(Ark_NativePointer node,
                      Ark_Boolean enabled)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(enabled);
    WebModelNG::SetMetaViewport(frameNode, convValue);
#endif
}
void OnPageEndImpl(Ark_NativePointer node,
                   Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnPageEnd(frameNode, convValue);
}
void OnPageBeginImpl(Ark_NativePointer node,
                     Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnPageBegin(frameNode, convValue);
}
void OnProgressChangeImpl(Ark_NativePointer node,
                          Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnProgressChange(frameNode, convValue);
}
void OnTitleReceiveImpl(Ark_NativePointer node,
                        Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnTitleReceive(frameNode, convValue);
}
void OnGeolocationHideImpl(Ark_NativePointer node,
                           Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnGeolocationHide(frameNode, convValue);
}
void OnGeolocationShowImpl(Ark_NativePointer node,
                           Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnGeolocationShow(frameNode, convValue);
}
void OnRequestSelectedImpl(Ark_NativePointer node,
                           Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnRequestSelected(frameNode, convValue);
}
void OnAlertImpl(Ark_NativePointer node,
                 Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnAlert(frameNode, convValue);
}
void OnBeforeUnloadImpl(Ark_NativePointer node,
                        Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnBeforeUnload(frameNode, convValue);
}
void OnConfirmImpl(Ark_NativePointer node,
                   Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnConfirm(frameNode, convValue);
}
void OnPromptImpl(Ark_NativePointer node,
                  Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnPrompt(frameNode, convValue);
}
void OnConsoleImpl(Ark_NativePointer node,
                   Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnConsole(frameNode, convValue);
}
void OnErrorReceiveImpl(Ark_NativePointer node,
                        Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnErrorReceive(frameNode, convValue);
}
void OnHttpErrorReceiveImpl(Ark_NativePointer node,
                            Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnHttpErrorReceive(frameNode, convValue);
}
void OnDownloadStartImpl(Ark_NativePointer node,
                         Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnDownloadStart(frameNode, convValue);
}
void OnRefreshAccessedHistoryImpl(Ark_NativePointer node,
                                  Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnRefreshAccessedHistory(frameNode, convValue);
}
void OnUrlLoadInterceptImpl(Ark_NativePointer node,
                            Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnUrlLoadIntercept(frameNode, convValue);
}
void OnSslErrorReceiveImpl(Ark_NativePointer node,
                           Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnSslErrorReceive(frameNode, convValue);
}
void OnRenderExited0Impl(Ark_NativePointer node,
                         Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnRenderExited0(frameNode, convValue);
}
void OnShowFileSelectorImpl(Ark_NativePointer node,
                            Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnShowFileSelector(frameNode, convValue);
}
void OnRenderExited1Impl(Ark_NativePointer node,
                         Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnRenderExited1(frameNode, convValue);
}
void OnFileSelectorShowImpl(Ark_NativePointer node,
                            Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnFileSelectorShow(frameNode, convValue);
}
void OnResourceLoadImpl(Ark_NativePointer node,
                        Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnResourceLoad(frameNode, convValue);
}
void OnFullScreenExitImpl(Ark_NativePointer node,
                          Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnFullScreenExit(frameNode, convValue);
}
void OnFullScreenEnterImpl(Ark_NativePointer node,
                           Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnFullScreenEnter(frameNode, convValue);
}
void OnScaleChangeImpl(Ark_NativePointer node,
                       Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnScaleChange(frameNode, convValue);
}
void OnHttpAuthRequestImpl(Ark_NativePointer node,
                           Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnHttpAuthRequest(frameNode, convValue);
}
void OnInterceptRequestImpl(Ark_NativePointer node,
                            Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnInterceptRequest(frameNode, convValue);
}
void OnPermissionRequestImpl(Ark_NativePointer node,
                             Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnPermissionRequest(frameNode, convValue);
}
void OnScreenCaptureRequestImpl(Ark_NativePointer node,
                                Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnScreenCaptureRequest(frameNode, convValue);
}
void OnContextMenuShowImpl(Ark_NativePointer node,
                           Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnContextMenuShow(frameNode, convValue);
}
void OnContextMenuHideImpl(Ark_NativePointer node,
                           Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnContextMenuHide(frameNode, convValue);
}
void MediaPlayGestureAccessImpl(Ark_NativePointer node,
                                Ark_Boolean access)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(access);
    WebModelNG::SetMediaPlayGestureAccess(frameNode, convValue);
#endif
}
void OnSearchResultReceiveImpl(Ark_NativePointer node,
                               Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnSearchResultReceive(frameNode, convValue);
}
void OnScrollImpl(Ark_NativePointer node,
                  Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnScroll(frameNode, convValue);
}
void OnSslErrorEventReceiveImpl(Ark_NativePointer node,
                                Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnSslErrorEventReceive(frameNode, convValue);
}
void OnSslErrorEventImpl(Ark_NativePointer node,
                         Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnSslErrorEvent(frameNode, convValue);
}
void OnClientAuthenticationRequestImpl(Ark_NativePointer node,
                                       Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnClientAuthenticationRequest(frameNode, convValue);
}
void OnWindowNewImpl(Ark_NativePointer node,
                     Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnWindowNew(frameNode, convValue);
}
void OnWindowExitImpl(Ark_NativePointer node,
                      Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnWindowExit(frameNode, convValue);
}
void MultiWindowAccessImpl(Ark_NativePointer node,
                           Ark_Boolean multiWindow)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(multiWindow);
    WebModelNG::SetMultiWindowAccessEnabled(frameNode, convValue);
#endif
}
void OnInterceptKeyEventImpl(Ark_NativePointer node,
                             Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnInterceptKeyEvent(frameNode, convValue);
}
void WebStandardFontImpl(Ark_NativePointer node,
                         const Ark_String* family)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(family);
    auto convValue = Converter::Convert<std::string>(*family);
    WebModelNG::SetWebStandardFont(frameNode, convValue);
#endif
}
void WebSerifFontImpl(Ark_NativePointer node,
                      const Ark_String* family)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(family);
    auto convValue = Converter::Convert<std::string>(*family);
    WebModelNG::SetWebSerifFont(frameNode, convValue);
#endif
}
void WebSansSerifFontImpl(Ark_NativePointer node,
                          const Ark_String* family)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(family);
    auto convValue = Converter::Convert<std::string>(*family);
    WebModelNG::SetWebSansSerifFont(frameNode, convValue);
#endif
}
void WebFixedFontImpl(Ark_NativePointer node,
                      const Ark_String* family)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(family);
    auto convValue = Converter::Convert<std::string>(*family);
    WebModelNG::SetWebFixedFont(frameNode, convValue);
#endif
}
void WebFantasyFontImpl(Ark_NativePointer node,
                        const Ark_String* family)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(family);
    auto convValue = Converter::Convert<std::string>(*family);
    WebModelNG::SetWebFantasyFont(frameNode, convValue);
#endif
}
void WebCursiveFontImpl(Ark_NativePointer node,
                        const Ark_String* family)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(family);
    auto convValue = Converter::Convert<std::string>(*family);
    WebModelNG::SetWebCursiveFont(frameNode, convValue);
#endif
}
void DefaultFixedFontSizeImpl(Ark_NativePointer node,
                              const Ark_Number* size)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(size);
    auto convValue = Converter::Convert<int32_t>(*size);
    WebModelNG::SetDefaultFixedFontSize(frameNode, convValue);
#endif
}
void DefaultFontSizeImpl(Ark_NativePointer node,
                         const Ark_Number* size)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(size);
    auto convValue = Converter::Convert<int32_t>(*size);
    WebModelNG::SetDefaultFontSize(frameNode, convValue);
#endif
}
void MinFontSizeImpl(Ark_NativePointer node,
                     const Ark_Number* size)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(size);
    auto convValue = Converter::Convert<int32_t>(*size);
    WebModelNG::SetMinFontSize(frameNode, convValue);
#endif
}
void MinLogicalFontSizeImpl(Ark_NativePointer node,
                            const Ark_Number* size)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(size);
    auto convValue = Converter::Convert<int32_t>(*size);
    WebModelNG::SetMinLogicalFontSize(frameNode, convValue);
#endif
}
void DefaultTextEncodingFormatImpl(Ark_NativePointer node,
                                   const Ark_String* textEncodingFormat)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(textEncodingFormat);
    auto convValue = Converter::Convert<std::string>(*textEncodingFormat);
    EraseSpace(convValue);
    WebModelNG::SetDefaultTextEncodingFormat(frameNode, convValue);
#endif
}
void ForceDisplayScrollBarImpl(Ark_NativePointer node,
                               Ark_Boolean enabled)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(enabled);
    WebModelNG::SetOverlayScrollbarEnabled(frameNode, convValue);
#endif
}
void BlockNetworkImpl(Ark_NativePointer node,
                      Ark_Boolean block)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(block);
    WebModelNG::SetBlockNetwork(frameNode, convValue);
#endif
}
void HorizontalScrollBarAccessImpl(Ark_NativePointer node,
                                   Ark_Boolean horizontalScrollBar)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(horizontalScrollBar);
    WebModelNG::SetHorizontalScrollBarAccessEnabled(frameNode, convValue);
#endif
}
void VerticalScrollBarAccessImpl(Ark_NativePointer node,
                                 Ark_Boolean verticalScrollBar)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(verticalScrollBar);
    WebModelNG::SetVerticalScrollBarAccessEnabled(frameNode, convValue);
#endif
}
void OnTouchIconUrlReceivedImpl(Ark_NativePointer node,
                                Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnTouchIconUrlReceived(frameNode, convValue);
}
void OnFaviconReceivedImpl(Ark_NativePointer node,
                           Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnFaviconReceived(frameNode, convValue);
}
void OnPageVisibleImpl(Ark_NativePointer node,
                       Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnPageVisible(frameNode, convValue);
}
void OnDataResubmittedImpl(Ark_NativePointer node,
                           Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnDataResubmitted(frameNode, convValue);
}
void PinchSmoothImpl(Ark_NativePointer node,
                     Ark_Boolean isEnabled)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(isEnabled);
    WebModelNG::SetPinchSmoothModeEnabled(frameNode, convValue);
#endif
}
void AllowWindowOpenMethodImpl(Ark_NativePointer node,
                               Ark_Boolean flag)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(flag);
    WebModelNG::SetAllowWindowOpenMethod(frameNode, convValue);
#endif
}
void OnAudioStateChangedImpl(Ark_NativePointer node,
                             Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnAudioStateChanged(frameNode, convValue);
}
void OnFirstContentfulPaintImpl(Ark_NativePointer node,
                                Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnFirstContentfulPaint(frameNode, convValue);
}
void OnFirstMeaningfulPaintImpl(Ark_NativePointer node,
                                Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnFirstMeaningfulPaint(frameNode, convValue);
}
void OnLargestContentfulPaintImpl(Ark_NativePointer node,
                                  Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnLargestContentfulPaint(frameNode, convValue);
}
void OnLoadInterceptImpl(Ark_NativePointer node,
                         Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnLoadIntercept(frameNode, convValue);
}
void OnControllerAttachedImpl(Ark_NativePointer node,
                              Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnControllerAttached(frameNode, convValue);
}
void OnOverScrollImpl(Ark_NativePointer node,
                      Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnOverScroll(frameNode, convValue);
}
void OnSafeBrowsingCheckResultImpl(Ark_NativePointer node,
                                   Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnSafeBrowsingCheckResult(frameNode, convValue);
}
void OnNavigationEntryCommittedImpl(Ark_NativePointer node,
                                    Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnNavigationEntryCommitted(frameNode, convValue);
}
void OnIntelligentTrackingPreventionResultImpl(Ark_NativePointer node,
                                               Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnIntelligentTrackingPreventionResult(frameNode, convValue);
}
void JavaScriptOnDocumentStartImpl(Ark_NativePointer node,
                                   const Array_ScriptItem* scripts)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(scripts);
    auto convValue = Converter::Convert<ScriptItems>(*scripts);
    WebModelNG::JavaScriptOnDocumentStart(frameNode, convValue);
#endif
}
void JavaScriptOnDocumentEndImpl(Ark_NativePointer node,
                                 const Array_ScriptItem* scripts)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(scripts);
    auto convValue = Converter::Convert<ScriptItems>(*scripts);
    WebModelNG::JavaScriptOnDocumentEnd(frameNode, convValue);
#endif
}
void LayoutModeImpl(Ark_NativePointer node,
                    Ark_WebLayoutMode mode)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<WebLayoutMode>(mode);
    WebModelNG::SetLayoutMode(frameNode, convValue);
#endif
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
#endif
}
void EnableNativeEmbedModeImpl(Ark_NativePointer node,
                               Ark_Boolean mode)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(mode);
    WebModelNG::SetNativeEmbedModeEnabled(frameNode, convValue);
#endif
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
#endif
}
void OnNativeEmbedLifecycleChangeImpl(Ark_NativePointer node,
                                      Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnNativeEmbedLifecycleChange(frameNode, convValue);
}
void OnNativeEmbedVisibilityChangeImpl(Ark_NativePointer node,
                                       Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnNativeEmbedVisibilityChange(frameNode, convValue);
}
void OnNativeEmbedGestureEventImpl(Ark_NativePointer node,
                                   Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
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
#endif
}
void OnOverrideUrlLoadingImpl(Ark_NativePointer node,
                              Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnOverrideUrlLoading(frameNode, convValue);
}
void TextAutosizingImpl(Ark_NativePointer node,
                        Ark_Boolean textAutosizing)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(textAutosizing);
    WebModelNG::SetTextAutosizing(frameNode, convValue);
#endif
}
void EnableNativeMediaPlayerImpl(Ark_NativePointer node,
                                 const Ark_NativeMediaPlayerConfig* config)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(config);
    auto enable = Converter::Convert<bool>(config->enable);
    auto shouldOverlay = Converter::Convert<bool>(config->shouldOverlay);
    WebModelNG::SetNativeVideoPlayerConfig(frameNode, enable, shouldOverlay);
#endif
}
void EnableSmoothDragResizeImpl(Ark_NativePointer node,
                                Ark_Boolean mode)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(mode);
    WebModelNG::SetSmoothDragResizeEnabled(frameNode, convValue);
#endif
}
void OnRenderProcessNotRespondingImpl(Ark_NativePointer node,
                                      Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnRenderProcessNotResponding(frameNode, convValue);
}
void OnRenderProcessRespondingImpl(Ark_NativePointer node,
                                   Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnRenderProcessResponding(frameNode, convValue);
}
void SelectionMenuOptionsImpl(Ark_NativePointer node,
                              const Array_ExpandedMenuItemOptions* expandedMenuOptions)
{   // hard
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(expandedMenuOptions);
    //auto convValue = Converter::OptConvert<type_name>(*expandedMenuOptions);
    //WebModelNG::SetSelectionMenuOptions(frameNode, convValue);
}
void OnViewportFitChangedImpl(Ark_NativePointer node,
                              Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnViewportFitChanged(frameNode, convValue);
}
void OnInterceptKeyboardAttachImpl(Ark_NativePointer node,
                                   Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnInterceptKeyboardAttach(frameNode, convValue);
}
void OnAdsBlockedImpl(Ark_NativePointer node,
                      Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //WebModelNG::SetOnAdsBlocked(frameNode, convValue);
}
void KeyboardAvoidModeImpl(Ark_NativePointer node,
                           Ark_WebKeyboardAvoidMode mode)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<WebKeyboardAvoidMode>(mode);
    WebModelNG::SetKeyboardAvoidMode(frameNode, convValue);
#endif
}
void EditMenuOptionsImpl(Ark_NativePointer node,
                         const Ark_Materialized* editMenu)
{   // hard
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(editMenu);
    //auto convValue = Converter::OptConvert<type_name>(*editMenu);
    //WebModelNG::SetEditMenuOptions(frameNode, convValue);
}
void EnableHapticFeedbackImpl(Ark_NativePointer node,
                              Ark_Boolean enabled)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(enabled);
    WebModelNG::SetEnabledHapticFeedback(frameNode, convValue);
#endif
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
        WebAttributeModifier::RegisterNativeEmbedRuleImpl,
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
    };
    return &ArkUIWebModifierImpl;
}

}
