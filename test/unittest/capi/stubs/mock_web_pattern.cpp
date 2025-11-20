/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "mock_web_pattern.h"

namespace OHOS::Ace::NG {
WebPattern::WebPattern() = default;

WebPattern::~WebPattern()
{
}

void WebPattern::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    Pattern::ToJsonValue(json, filter);
    /* no fixed attr below, just return */
    if (filter.IsFastFilter()) {
        return;
    }
    json->PutExtAttr("mixedMode", GetMixedModeAsString().c_str(), filter);
    json->PutExtAttr("cacheMode", GetCacheModeAsString().c_str(), filter);
    json->PutExtAttr("darkMode", GetDarkModeAsString().c_str(), filter);
    json->PutExtAttr("overScrollMode", GetOverScrollModeAsString().c_str(), filter);
    json->PutExtAttr("textZoomAtio", std::to_string(GetTextZoomRatioValue(DEFAULT_TEXT_ZOOM_RATIO)).c_str(), filter);
    json->PutExtAttr("textZoomRatio", std::to_string(GetTextZoomRatioValue(DEFAULT_TEXT_ZOOM_RATIO)).c_str(), filter);
    json->PutExtAttr("initialScale", GetInitialScaleAsString().c_str(), filter);
    json->PutExtAttr("userAgent", GetUserAgentValue("").c_str(), filter);
    json->PutExtAttr("metaViewport", GetMetaViewportAsString().c_str(), filter);
    json->PutExtAttr("webStandardFont", GetWebStandardFontValue(DEFAULT_STANDARD_FONT_FAMILY).c_str(), filter);
    json->PutExtAttr("webSerifFont", GetWebSerifFontValue(DEFAULT_SERIF_FONT_FAMILY).c_str(), filter);
    json->PutExtAttr("webSansSerifFont", GetWebSansSerifFontValue(DEFAULT_SANS_SERIF_FONT_FAMILY).c_str(), filter);
    json->PutExtAttr("webFixedFont", GetWebFixedFontValue(DEFAULT_FIXED_fONT_FAMILY).c_str(), filter);
    json->PutExtAttr("webFantasyFont", GetWebFantasyFontValue(DEFAULT_FANTASY_FONT_FAMILY).c_str(), filter);
    json->PutExtAttr("webCursiveFont", GetWebCursiveFontValue(DEFAULT_CURSIVE_FONT_FAMILY).c_str(), filter);
    json->PutExtAttr("defaultFixedFontSize", GetDefaultFixedFontSizeAsString().c_str(), filter);
    json->PutExtAttr("defaultFontSize", std::to_string(GetDefaultFontSizeValue(DEFAULT_FONT_SIZE)).c_str(), filter);
    json->PutExtAttr("minFontSize", std::to_string(GetMinFontSizeValue(DEFAULT_MINIMUM_FONT_SIZE)).c_str(), filter);
    json->PutExtAttr("minLogicalFontSize", GetMinLogicalFontSizeAsString().c_str(), filter);
    json->PutExtAttr("defaultTextEncodingFormat", GetDefaultTextEncodingFormatAsString().c_str(), filter);
    json->PutExtAttr("horizontalScrollBarAccess", GetHorizontalScrollBarAccessEnabledAsString().c_str(), filter);
    json->PutExtAttr("verticalScrollBarAccess", GetVerticalScrollBarAccessEnabledAsString().c_str(), filter);
    json->PutExtAttr("layoutMode", GetLayoutModeAsString().c_str(), filter);
    json->PutExtAttr("copyOptions", GetCopyOptionModeAsString().c_str(), filter);
    json->PutExtAttr("keyboardAvoidMode", GetKeyboardAvoidModeAsString().c_str(), filter);
    json->PutExtAttr("enableHapticFeedback", GetEnabledHapticFeedbackAsString().c_str(), filter);
    json->PutExtAttr("blockNetwork", GetBlockNetworkAsString().c_str(), filter);

    BoolWebPropertiesToJsonValue(json, filter);
    NestedScrollExtToJsonValue(json, filter);
    NativeVideoPlayerConfigToJsonValue(json, filter);
    NativeEmbedRuleToJsonValue(json, filter);
    MediaOptionsToJsonValue(json, filter);
}

void WebPattern::BoolWebPropertiesToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    json->PutExtAttr("javaScriptAccess", GetJsEnabledValue(true) ? "true" : "false", filter);
    json->PutExtAttr("mediaPlayGestureAccess", GetMediaPlayGestureAccessValue(true) ? "true" : "false", filter);
    json->PutExtAttr("fileAccess", GetFileAccessEnabledValue(false) ? "true" : "false", filter);
    json->PutExtAttr("onlineImageAccess", GetOnLineImageAccessEnabledValue(true) ? "true" : "false", filter);
    json->PutExtAttr("domStorageAccess", GetDomStorageAccessEnabledValue(false) ? "true" : "false", filter);
    json->PutExtAttr("imageAccess", GetImageAccessEnabledValue(true) ? "true" : "false", filter);
    json->PutExtAttr("zoomAccess", GetZoomAccessEnabledValue(true) ? "true" : "false", filter);
    json->PutExtAttr("geolocationAccess", GetGeolocationAccessEnabledValue(true) ? "true" : "false", filter);
    json->PutExtAttr("forceDarkAccess", GetForceDarkAccessValue(false) ? "true" : "false", filter);
    json->PutExtAttr("overviewModeAccess", GetOverviewModeAccessEnabledValue(true) ? "true" : "false", filter);
    json->PutExtAttr("databaseAccess", GetDatabaseAccessEnabledValue(false) ? "true" : "false", filter);
    json->PutExtAttr("multiWindowAccess", GetMultiWindowAccessEnabledValue(false) ? "true" : "false", filter);
    json->PutExtAttr("forceDisplayScrollBar", GetOverlayScrollbarEnabledValue(false) ? "true" : "false", filter);
    json->PutExtAttr("pinchSmooth", GetPinchSmoothModeEnabledValue(false) ? "true" : "false", filter);
    json->PutExtAttr("allowWindowOpenMethod", GetAllowWindowOpenMethodValue(false) ? "true" : "false", filter);
    json->PutExtAttr("enableNativeEmbedMode", GetNativeEmbedModeEnabledValue(false) ? "true" : "false", filter);
    json->PutExtAttr("textAutosizing", GetTextAutosizingValue(true) ? "true" : "false", filter);
}

void WebPattern::NestedScrollExtToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    auto jsonValue = JsonUtil::Create(true);
    jsonValue->Put("scrollUp", GetNestedScrollModeAsString(nestedScroll_.scrollUp).c_str());
    jsonValue->Put("scrollDown", GetNestedScrollModeAsString(nestedScroll_.scrollDown).c_str());
    jsonValue->Put("scrollRight", GetNestedScrollModeAsString(nestedScroll_.scrollRight).c_str());
    jsonValue->Put("scrollLeft", GetNestedScrollModeAsString(nestedScroll_.scrollLeft).c_str());
    json->PutExtAttr("nestedScroll", jsonValue, filter);
}

void WebPattern::NativeVideoPlayerConfigToJsonValue(
    std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    auto jsonValue = JsonUtil::Create(true);
    std::tuple<bool, bool> config = GetNativeVideoPlayerConfigValue({false, false});
    jsonValue->Put("enable", std::get<0>(config) ? "true" : "false");
    jsonValue->Put("shouldOverlay", std::get<1>(config) ? "true" : "false");
    json->PutExtAttr("enableNativeMediaPlayer", jsonValue, filter);
}

void WebPattern::NativeEmbedRuleToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    auto jsonValue = JsonUtil::Create(true);
    jsonValue->Put("tag", GetNativeEmbedRuleTagValue("").c_str());
    jsonValue->Put("type", GetNativeEmbedRuleTypeValue("").c_str());
    json->PutExtAttr("registerNativeEmbedRule", jsonValue, filter);
}

void WebPattern::MediaOptionsToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    auto jsonValue = JsonUtil::Create(true);
    jsonValue->Put("resumeInterval", std::to_string(GetAudioResumeIntervalValue(-1)).c_str());
    jsonValue->Put("audioExclusive", GetAudioExclusiveValue(true) ? "true" : "false");
    json->PutExtAttr("mediaOptions", jsonValue, filter);
}

std::string WebPattern::GetMixedModeAsString() const
{
    std::string str = "MixedMode.None";
    switch (GetMixedModeValue(MixedModeContent::MIXED_CONTENT_NEVER_ALLOW)) {
        case MixedModeContent::MIXED_CONTENT_ALWAYS_ALLOW:
            str = "MixedMode.All";
            break;
        case MixedModeContent::MIXED_CONTENT_NEVER_ALLOW:
            str = "MixedMode.None";
            break;
        case MixedModeContent::MIXED_CONTENT_COMPATIBILITY_MODE:
            str = "MixedMode.Compatible";
            break;
        default:
            break;
    }
    return str;
}

std::string WebPattern::GetCacheModeAsString() const
{
    std::string str = "CacheMode.Default";
    switch (GetCacheModeValue(WebCacheMode::DEFAULT)) {
        case WebCacheMode::USE_CACHE_ELSE_NETWORK:
            str = "CacheMode.None";
            break;
        case WebCacheMode::USE_CACHE_ONLY:
            str = "CacheMode.Only";
            break;
        case WebCacheMode::USE_NO_CACHE:
            str = "CacheMode.Online";
            break;
        case WebCacheMode::DEFAULT:
            str = "CacheMode.Default";
            break;
        default:
            break;
    }
    return str;
}

std::string WebPattern::GetDarkModeAsString() const
{
    std::string str = "WebDarkMode.Off";
    switch (GetDarkModeValue(WebDarkMode::Off)) {
        case WebDarkMode::Auto:
            str = "WebDarkMode.Auto";
            break;
        case WebDarkMode::On:
            str = "WebDarkMode.On";
            break;
        case WebDarkMode::Off:
            str = "WebDarkMode.Off";
            break;
        default:
            break;
    }
    return str;
}

std::string WebPattern::GetOverScrollModeAsString() const
{
    std::string str = "OverScrollMode.NEVER";
    switch (GetOverScrollModeValue(OverScrollMode::NEVER)) {
        case OverScrollMode::NEVER:
            str = "OverScrollMode.NEVER";
            break;
        case OverScrollMode::ALWAYS:
            str = "OverScrollMode.ALWAYS";
            break;
        default:
            break;
    }
    return str;
}

std::string WebPattern::GetMetaViewportAsString() const
{
    auto metaViewPort = GetMetaViewport();
    if (metaViewPort) {
        return metaViewPort.value() ? "true" : "false";
    }
    return "empty";
}

std::string WebPattern::GetLayoutModeAsString() const
{
    std::string str = "WebLayoutMode.NONE";
    switch (layoutMode_) {
        case WebLayoutMode::FIT_CONTENT:
            str = "WebLayoutMode.FIT_CONTENT";
            break;
        case WebLayoutMode::NONE:
            str = "WebLayoutMode.NONE";
            break;
        default:
            break;
    }
    return str;
}

std::string WebPattern::GetNestedScrollModeAsString(const NestedScrollMode& scrollMode) const
{
    std::string str = "NestedScrollMode.SELF_FIRST";
    switch (scrollMode) {
        case NestedScrollMode::PARALLEL:
            str = "NestedScrollMode.PARALLEL";
            break;
        case NestedScrollMode::PARENT_FIRST:
            str = "NestedScrollMode.PARENT_FIRST";
            break;
        case NestedScrollMode::SELF_FIRST:
            str = "NestedScrollMode.SELF_FIRST";
            break;
        case NestedScrollMode::SELF_ONLY:
            str = "NestedScrollMode.SELF_ONLY";
            break;
        default:
            break;
    }
    return str;
}

std::string WebPattern::GetInitialScaleAsString() const
{
    auto initialScale = GetInitialScale();
    if (initialScale) {
        return std::to_string(initialScale.value());
    }
    return "empty";
}

std::string WebPattern::GetCopyOptionModeAsString() const
{
    std::string str = "CopyOptions.CROSS_DEVICE";
    auto value = static_cast<CopyOptions>(GetCopyOptionModeValue(static_cast<int32_t>(CopyOptions::Distributed)));
    switch (value) {
        case CopyOptions::None:
            str = "CopyOptions.None";
            break;
        case CopyOptions::InApp:
            str = "CopyOptions.InApp";
            break;
        case CopyOptions::Local:
            str = "CopyOptions.LocalDevice";
            break;
        case CopyOptions::Distributed:
            str = "CopyOptions.CROSS_DEVICE";
            break;
        default:
            break;
    }
    return str;
}

std::string WebPattern::GetKeyboardAvoidModeAsString() const
{
    std::string str = "empty";
    auto keyboardAvoidMode = GetKeyboardAvoidMode();
    if (!keyboardAvoidMode.has_value()) {
        return str;
    }
    switch (GetKeyboardAvoidMode().value()) {
        case WebKeyboardAvoidMode::RESIZE_VISUAL:
            str = "WebKeyboardAvoidMode.RESIZE_VISUAL";
            break;
        case WebKeyboardAvoidMode::RESIZE_CONTENT:
            str = "WebKeyboardAvoidMode.RESIZE_CONTENT";
            break;
        case WebKeyboardAvoidMode::OVERLAYS_CONTENT:
            str = "WebKeyboardAvoidMode.OVERLAYS_CONTENT";
            break;
        default:
            break;
    }
    return str;
}

std::string WebPattern::GetEnabledHapticFeedbackAsString() const
{
    auto enabledHapticFeedback = GetEnabledHapticFeedback();
    if (enabledHapticFeedback) {
        return enabledHapticFeedback.value() ? "true" : "false";
    }
    return "empty";
}

std::string WebPattern::GetBlockNetworkAsString() const
{
    auto blockNetwork = GetBlockNetwork();
    if (blockNetwork) {
        return blockNetwork.value() ? "true" : "false";
    }
    return "empty";
}

std::string WebPattern::GetMinLogicalFontSizeAsString() const
{
    return std::to_string(GetMinLogicalFontSizeValue(DEFAULT_MINIMUM_LOGICAL_FONT_SIZE));
}

std::string WebPattern::GetDefaultFixedFontSizeAsString() const
{
    return std::to_string(GetDefaultFixedFontSizeValue(DEFAULT_FIXED_FONT_SIZE));
}

std::string WebPattern::GetDefaultTextEncodingFormatAsString() const
{
    return GetDefaultTextEncodingFormatValue(DEFAULT_WEB_TEXT_ENCODING_FORMAT);
}

std::string WebPattern::GetHorizontalScrollBarAccessEnabledAsString() const
{
    return GetHorizontalScrollBarAccessEnabledValue(true) ? "true" : "false";
}

std::string WebPattern::GetVerticalScrollBarAccessEnabledAsString() const
{
    return GetVerticalScrollBarAccessEnabledValue(true) ? "true" : "false";
}

void WebPattern::SetWebSrc(const std::string &webSrc)
{
}

void WebPattern::SetWebSrcStatic(const std::string &webSrc)
{
}

void WebPattern::SetWebData(const std::string& webData)
{
    webData_ = webData;
}

void WebPattern::SetIncognitoMode(bool incognitoMode)
{
}

void WebPattern::SetSharedRenderProcessToken(const std::string& sharedRenderProcessToken)
{
}

void WebPattern::SetNestedScrollExt(NestedScrollOptionsExt const& nestedScroll)
{
    nestedScroll_ = nestedScroll;
}

void WebPattern::SetRenderMode(RenderMode)
{
}

void WebPattern::SetLayoutMode(WebLayoutMode mode)
{
    layoutMode_ = mode;
}

void WebPattern::JavaScriptOnDocumentStart(const ScriptItems&)
{
}

void WebPattern::JavaScriptOnDocumentEnd(const ScriptItems&)
{
}

void WebPattern::JavaScriptOnHeadReadyByOrder(const ScriptItems&, const ScriptItemsByOrder&)
{
}

void WebPattern::SetWebController(const RefPtr<WebController>& webController)
{
    webController_ = webController;
}

RefPtr<WebController> WebPattern::GetWebController() const
{
    return webController_;
}

void WebPattern::SetOnControllerAttachedCallback(OnControllerAttachedCallback&& callback)
{
    onControllerAttachedCallback_ = std::move(callback);
}

WebPattern::OnControllerAttachedCallback WebPattern::GetOnControllerAttachedCallback()
{
    return onControllerAttachedCallback_;
}
} // namespace OHOS::Ace::NG
