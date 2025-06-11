/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
#include "core/interfaces/native/node/web_modifier.h"

#include "bridge/common/utils/utils.h"
#include "core/components_ng/pattern/web/web_model_ng.h"
#include "core/interfaces/native/node/node_drag_modifier.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr bool DEFAULT_JS_ACCESS_ENABLED = true;
constexpr bool DEFAULT_FILE_ACCESS_ENABLED = false;
constexpr bool DEFAULT_DOM_STORAGE_ACCESS_ENABLED = false;
constexpr MixedModeContent DEFAULT_MIXED_MODE = MixedModeContent::MIXED_CONTENT_NEVER_ALLOW;
constexpr int32_t DEFAULT_ZOOM_ACCESS_ENABLED = true;
constexpr WebCacheMode DEFAULT_CACHE_MODE = WebCacheMode::DEFAULT;
constexpr WebDarkMode DEFAULT_DARK_MODE = WebDarkMode::Off;
constexpr int32_t DEFAULT_MULTIWINDOW_ACCESS_ENABLED = false;
constexpr int32_t DEFAULT_ALLOW_WINDOWOPEN_METHOD = false;
constexpr WebKeyboardAvoidMode DEFAULT_KEYBOAED_AVIOD_MODE = WebKeyboardAvoidMode::RESIZE_CONTENT;
constexpr bool DEFAULT_VERTICALSCROLL_BAR_ACCESS_ENABLED = true;
constexpr bool DEFAULT_HORIZONTALSCROLL_BAR_ACCESS_ENABLED = true;
constexpr int32_t DEFAULT_TEXT_ZOOM_RATIO = 100;
constexpr float DEFAULT_INITIAL_SCALE = 100.0f;
constexpr bool DEFAULT_GEOLOCATION_ACCESS_ENABLED = true;
constexpr bool DEFAULT_DATABASE_ACCESS_ENABLED = false;
constexpr bool DEFAULT_OVERVIEWMODE_ACCESS_ENABLED = true;
constexpr bool DEFAULT_FORCEDARK_ACCESS_ENABLED = false;
constexpr bool DEFAULT_PINCH_SMOOTH_ENABLED = false;
constexpr bool DEFAULT_META_VIEWPORT_ENABLED = true;
constexpr bool DEFAULT_ENABLE_FOLLOW_SYSTEM_FONT_WEIGHT = false;
constexpr bool DEFAULT_NATIVE_EMBED_MODE_ENABLE = false;
constexpr int32_t DEFAULT_MINFONT_SIZE = 8;
constexpr int32_t DEFAULT_DEFAULTFONT_SIZE = 16;
constexpr int32_t DEFAULT_DEFAULTFIXEDFONT_SIZE = 13;
constexpr int32_t DEFAULT_MINLOGICALFONT_SIZE = 8;
constexpr char DEFAULT_WEBSTANDARD_FONT[] = "sans serif";
constexpr char DEFAULT_WEBSERIF_FONT[] = "serif";
constexpr char DEFAULT_WEBSANSSERIF_FONT[] = "sans-serif";
constexpr char DEFAULT_WEBFIXED_FONT[] = "monospace";
constexpr char DEFAULT_WEBFANTASY_FONT[] = "fantasy";
constexpr char DEFAULT_WEBCURSIVE_FONT[] = "cursive";
constexpr WebLayoutMode DEFAULT_LAYOUT_MODE = WebLayoutMode::NONE;
constexpr bool DEFAULT_NATIVE_EMBED_OPTIONS = false;
constexpr bool DEFAULT_IMAGE_ACCESS_ENABLED = true;
constexpr bool DEFAULT_ONLINEIMAGE_ACCESS_ENABLED = true;
constexpr bool MEDIA_PLAY_GESTURE_ACCESS_ENABLED = true;
constexpr bool DEFAULT_MEDIA_OPTIONS_ENABLED = true;
constexpr int32_t DEFAULT_RESUMEINTERVAL = 0;
constexpr CopyOptions DEFAULT_COPY_OPTIONS_VALUE = CopyOptions::Local;
constexpr bool DEFAULT_BLOCK_NETWORK_ENABLED = false;
constexpr OverScrollMode DEFAULT_OVERSCROLL_MODE = OverScrollMode::NEVER;
} // namespace

void SetJavaScriptAccess(ArkUINodeHandle node, ArkUI_Bool value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetJsEnabled(frameNode, value);
}

void ResetJavaScriptAccess(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetJsEnabled(frameNode, DEFAULT_JS_ACCESS_ENABLED);
}

void SetFileAccessEnabled(ArkUINodeHandle node, ArkUI_Bool value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetFileAccessEnabled(frameNode, value);
}

void ResetFileAccessEnabled(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetFileAccessEnabled(frameNode, DEFAULT_FILE_ACCESS_ENABLED);
}

void SetDomStorageAccessEnabled(ArkUINodeHandle node, ArkUI_Bool value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetDomStorageAccessEnabled(frameNode, value);
}

void ResetDomStorageAccessEnabled(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetDomStorageAccessEnabled(frameNode, DEFAULT_DOM_STORAGE_ACCESS_ENABLED);
}

void SetMixedMode(ArkUINodeHandle node, ArkUI_Int32 value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto mixedContentMode = MixedModeContent::MIXED_CONTENT_NEVER_ALLOW;
    switch (value) {
        case 0:
            mixedContentMode = MixedModeContent::MIXED_CONTENT_ALWAYS_ALLOW;
            break;
        case 1:
            mixedContentMode = MixedModeContent::MIXED_CONTENT_COMPATIBILITY_MODE;
            break;
        default:
            mixedContentMode = MixedModeContent::MIXED_CONTENT_NEVER_ALLOW;
            break;
    }
    WebModelNG::SetMixedMode(frameNode, MixedModeContent(mixedContentMode));
}

void ResetMixedMode(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetMixedMode(frameNode, DEFAULT_MIXED_MODE);
}

void SetZoomAccessEnabled(ArkUINodeHandle node, ArkUI_Bool value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetZoomAccessEnabled(frameNode, value);
}

void ResetZoomAccessEnabled(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetZoomAccessEnabled(frameNode, DEFAULT_ZOOM_ACCESS_ENABLED);
}

void SetCacheMode(ArkUINodeHandle node, ArkUI_Int32 value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetCacheMode(frameNode, WebCacheMode(value));
}

void ResetCacheMode(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetCacheMode(frameNode, DEFAULT_CACHE_MODE);
}

void SetDarkMode(ArkUINodeHandle node, ArkUI_Int32 value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetDarkMode(frameNode, WebDarkMode(value));
}

void ResetDarkMode(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetDarkMode(frameNode, DEFAULT_DARK_MODE);
}

void SetMultiWindowAccessEnabled(ArkUINodeHandle node, ArkUI_Bool value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetMultiWindowAccessEnabled(frameNode, value);
}

void ResetMultiWindowAccessEnabled(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetMultiWindowAccessEnabled(frameNode, DEFAULT_MULTIWINDOW_ACCESS_ENABLED);
}

void SetAllowWindowOpenMethod(ArkUINodeHandle node, ArkUI_Bool value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetAllowWindowOpenMethod(frameNode, value);
}

void ResetAllowWindowOpenMethod(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetAllowWindowOpenMethod(frameNode, DEFAULT_ALLOW_WINDOWOPEN_METHOD);
}

void SetKeyboardAvoidMode(ArkUINodeHandle node, ArkUI_Int32 value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetKeyboardAvoidMode(frameNode, WebKeyboardAvoidMode(value));
}

void ResetKeyboardAvoidMode(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetKeyboardAvoidMode(frameNode, DEFAULT_KEYBOAED_AVIOD_MODE);
}

void SetOnControllerAttached(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (extraParam) {
        auto onControllerAttached = reinterpret_cast<std::function<void()>*>(extraParam);
        WebModelNG::SetOnControllerAttached(frameNode, std::move(*onControllerAttached));
    } else {
        WebModelNG::SetOnControllerAttached(frameNode, nullptr);
    }
}

void ResetOnControllerAttached(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetOnControllerAttached(frameNode, nullptr);
}

void SetVerticalScrollBarAccessEnabled(ArkUINodeHandle node, ArkUI_Bool value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetVerticalScrollBarAccessEnabled(frameNode, value);
}

void ResetVerticalScrollBarAccessEnabled(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetVerticalScrollBarAccessEnabled(frameNode, DEFAULT_VERTICALSCROLL_BAR_ACCESS_ENABLED);
}

void SetHorizontalScrollBarAccessEnabled(ArkUINodeHandle node, ArkUI_Bool value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetHorizontalScrollBarAccessEnabled(frameNode, value);
}

void ResetHorizontalScrollBarAccessEnabled(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetHorizontalScrollBarAccessEnabled(frameNode, DEFAULT_HORIZONTALSCROLL_BAR_ACCESS_ENABLED);
}

void SetTextZoomRatio(ArkUINodeHandle node, ArkUI_Int32 value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetTextZoomRatio(frameNode, value);
}

void ResetTextZoomRatio(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetTextZoomRatio(frameNode, DEFAULT_TEXT_ZOOM_RATIO);
}

void SetInitialScale(ArkUINodeHandle node, ArkUI_Float32 value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::InitialScale(frameNode, value);
}

void ResetInitialScale(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::InitialScale(frameNode, DEFAULT_INITIAL_SCALE);
}

void SetOnScrollCallBack(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (extraParam) {
        auto* onScrollPtr = reinterpret_cast<std::function<void(WebOnScrollEvent&)>*>(extraParam);
        CHECK_NULL_VOID(onScrollPtr);
        auto callback = [onScrollCallback = *onScrollPtr](const BaseEventInfo* event) {
            if (auto scrollEvent = static_cast<const WebOnScrollEvent*>(event)) {
                auto& nonConstEvent = const_cast<WebOnScrollEvent&>(*scrollEvent);
                onScrollCallback(nonConstEvent);
            }
        };
        WebModelNG::SetOnScroll(frameNode, std::move(callback));
    } else {
        WebModelNG::SetOnScroll(frameNode, nullptr);
    }
}

void ResetOnScrollCallBack(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetOnScroll(frameNode, nullptr);
}

void SetOnOverScrollCallBack(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (extraParam) {
        auto* onOverScrollkPtr = reinterpret_cast<std::function<void(WebOnOverScrollEvent&)>*>(extraParam);
        CHECK_NULL_VOID(onOverScrollkPtr);
        auto callback = [onOverScrollkCallback = *onOverScrollkPtr](const BaseEventInfo* event) {
            if (auto overScrollEvent = static_cast<const WebOnOverScrollEvent*>(event)) {
                auto& nonConstEvent = const_cast<WebOnOverScrollEvent&>(*overScrollEvent);
                onOverScrollkCallback(nonConstEvent);
            }
        };
        WebModelNG::SetOnOverScroll(frameNode, std::move(callback));
    } else {
        WebModelNG::SetOnOverScroll(frameNode, nullptr);
    }
}

void ResetOnOverScrollCallBack(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetOnOverScroll(frameNode, nullptr);
}

void SetOnScaleChangeCallBack(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (extraParam) {
        auto* scaleChangePtr = reinterpret_cast<std::function<void(ScaleChangeEvent&)>*>(extraParam);
        CHECK_NULL_VOID(scaleChangePtr);
        auto callback = [scaleChangeCallback = *scaleChangePtr](const BaseEventInfo* event) {
            if (auto scaleChangeEvent = static_cast<const ScaleChangeEvent*>(event)) {
                auto& nonConstEvent = const_cast<ScaleChangeEvent&>(*scaleChangeEvent);
                scaleChangeCallback(nonConstEvent);
            }
        };
        WebModelNG::SetOnScaleChange(frameNode, std::move(callback));
    } else {
        WebModelNG::SetOnScaleChange(frameNode, nullptr);
    }
}

void ResetOnScaleChangeCallBack(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetOnScaleChange(frameNode, nullptr);
}

void SetOnRequestSelectedCallBack(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (extraParam) {
        auto* originalCallbackPtr = reinterpret_cast<std::function<void()>*>(extraParam);
        CHECK_NULL_VOID(originalCallbackPtr);
        auto callback = [originalCallback = *originalCallbackPtr](const BaseEventInfo*) { originalCallback(); };
        WebModelNG::SetOnRequestFocus(frameNode, std::move(callback));
    } else {
        WebModelNG::SetOnRequestFocus(frameNode, nullptr);
    }
}

void ResetOnRequestSelectedCallBack(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetOnRequestFocus(frameNode, nullptr);
}

void SetOnContextMenuHideCallBack(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (extraParam) {
        auto* originalCallbackPtr = reinterpret_cast<std::function<void()>*>(extraParam);
        CHECK_NULL_VOID(originalCallbackPtr);
        auto callback = [originalCallback = *originalCallbackPtr](const BaseEventInfo*) { originalCallback(); };
        WebModelNG::SetOnContextMenuHide(frameNode, std::move(callback));
    } else {
        WebModelNG::SetOnContextMenuHide(frameNode, nullptr);
    }
}

void ResetOnContextMenuHideCallBack(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetOnContextMenuHide(frameNode, nullptr);
}

void SetGeolocationAccess(ArkUINodeHandle node, ArkUI_Bool value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetGeolocationAccessEnabled(frameNode, value);
}

void ResetGeolocationAccess(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetGeolocationAccessEnabled(frameNode, DEFAULT_GEOLOCATION_ACCESS_ENABLED);
}

void SetOnGeolocationShow(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (extraParam) {
        auto* originalCallbackPtr = reinterpret_cast<std::function<void(LoadWebGeolocationShowEvent&)>*>(extraParam);
        std::function<void(const BaseEventInfo*)> adaptedCallback;
        if (originalCallbackPtr) {
            adaptedCallback = [originalCallback = *originalCallbackPtr](const BaseEventInfo* event) {
                if (auto geoLocationEvent = static_cast<const LoadWebGeolocationShowEvent*>(event)) {
                    auto& onGeolocationShow = const_cast<LoadWebGeolocationShowEvent&>(*geoLocationEvent);
                    originalCallback(onGeolocationShow);
                }
            };
        }
        WebModelNG::SetOnGeolocationShow(frameNode, std::move(adaptedCallback));
    } else {
        WebModelNG::SetOnGeolocationShow(frameNode, nullptr);
    }
}

void ResetOnGeolocationShow(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetOnGeolocationShow(frameNode, nullptr);
}

void SetDatabaseAccess(ArkUINodeHandle node, ArkUI_Bool value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetDatabaseAccessEnabled(frameNode, value);
}

void ResetDatabaseAccess(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetDatabaseAccessEnabled(frameNode, DEFAULT_DATABASE_ACCESS_ENABLED);
}

void SetOverviewModeAccess(ArkUINodeHandle node, ArkUI_Bool value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetOverviewModeAccessEnabled(frameNode, value);
}

void ResetOverviewModeAccess(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetOverviewModeAccessEnabled(frameNode, DEFAULT_OVERVIEWMODE_ACCESS_ENABLED);
}

void SetForceDarkAccess(ArkUINodeHandle node, ArkUI_Bool value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetForceDarkAccess(frameNode, value);
}

void ResetForceDarkAccess(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetForceDarkAccess(frameNode, DEFAULT_FORCEDARK_ACCESS_ENABLED);
}

void SetPinchSmooth(ArkUINodeHandle node, ArkUI_Bool value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetPinchSmoothModeEnabled(frameNode, value);
}

void ResetPinchSmooth(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetPinchSmoothModeEnabled(frameNode, DEFAULT_PINCH_SMOOTH_ENABLED);
}

void SetMetaViewport(ArkUINodeHandle node, ArkUI_Bool value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetMetaViewport(frameNode, value);
}

void ResetMetaViewport(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetMetaViewport(frameNode, DEFAULT_META_VIEWPORT_ENABLED);
}

void SetEnableFollowSystemFontWeight(ArkUINodeHandle node, ArkUI_Bool value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetEnableFollowSystemFontWeight(frameNode, value);
}

void ResetEnableFollowSystemFontWeight(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetEnableFollowSystemFontWeight(frameNode, DEFAULT_ENABLE_FOLLOW_SYSTEM_FONT_WEIGHT);
}

void SetEnableNativeEmbedMode(ArkUINodeHandle node, ArkUI_Bool value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetNativeEmbedModeEnabled(frameNode, value);
}

void ResetEnableNativeEmbedMode(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetNativeEmbedModeEnabled(frameNode, DEFAULT_NATIVE_EMBED_MODE_ENABLE);
}

void SetMinFontSize(ArkUINodeHandle node, ArkUI_Int32 value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetMinFontSize(frameNode, value);
}

void ResetMinFontSize(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetMinFontSize(frameNode, DEFAULT_MINFONT_SIZE);
}

void SetDefaultFontSize(ArkUINodeHandle node, ArkUI_Int32 value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetDefaultFontSize(frameNode, value);
}

void ResetDefaultFontSize(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetDefaultFontSize(frameNode, DEFAULT_DEFAULTFONT_SIZE);
}

void SetDefaultFixedFontSize(ArkUINodeHandle node, ArkUI_Int32 value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetDefaultFixedFontSize(frameNode, value);
}

void ResetDefaultFixedFontSize(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetDefaultFixedFontSize(frameNode, DEFAULT_DEFAULTFIXEDFONT_SIZE);
}

void SetMinLogicalFontSize(ArkUINodeHandle node, ArkUI_Int32 value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetMinLogicalFontSize(frameNode, value);
}

void ResetMinLogicalFontSize(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetMinLogicalFontSize(frameNode, DEFAULT_MINLOGICALFONT_SIZE);
}

void SetWebStandardFont(ArkUINodeHandle node, ArkUI_CharPtr value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetWebStandardFont(frameNode, std::string(value));
}

void ResetWebStandardFont(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetWebStandardFont(frameNode, DEFAULT_WEBSTANDARD_FONT);
}

void SetWebSerifFont(ArkUINodeHandle node, ArkUI_CharPtr value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetWebSerifFont(frameNode, std::string(value));
}

void ResetWebSerifFont(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetWebSerifFont(frameNode, DEFAULT_WEBSERIF_FONT);
}

void SetWebSansSerifFont(ArkUINodeHandle node, ArkUI_CharPtr value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetWebSansSerifFont(frameNode, std::string(value));
}

void ResetWebSansSerifFont(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetWebSansSerifFont(frameNode, DEFAULT_WEBSANSSERIF_FONT);
}

void SetWebFixedFont(ArkUINodeHandle node, ArkUI_CharPtr value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetWebFixedFont(frameNode, std::string(value));
}

void ResetWebFixedFont(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetWebFixedFont(frameNode, DEFAULT_WEBFIXED_FONT);
}

void SetWebFantasyFont(ArkUINodeHandle node, ArkUI_CharPtr value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetWebFantasyFont(frameNode, std::string(value));
}

void ResetWebFantasyFont(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetWebFantasyFont(frameNode, DEFAULT_WEBFANTASY_FONT);
}

void SetWebCursiveFont(ArkUINodeHandle node, ArkUI_CharPtr value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetWebCursiveFont(frameNode, std::string(value));
}

void ResetWebCursiveFont(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetWebCursiveFont(frameNode, DEFAULT_WEBCURSIVE_FONT);
}

void SetLayoutMode(ArkUINodeHandle node, ArkUI_Int32 value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetLayoutMode(frameNode, WebLayoutMode(value));
}

void ResetLayoutMode(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetLayoutMode(frameNode, DEFAULT_LAYOUT_MODE);
}

void SetOnNativeEmbedLifecycleChange(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto* originalCallbackPtr = reinterpret_cast<std::function<void(NativeEmbedDataInfo&)>*>(extraParam);
    CHECK_NULL_VOID(originalCallbackPtr);
    if (extraParam) {
        auto adaptedCallback = [originalCallback = *originalCallbackPtr](const BaseEventInfo* event) {
            if (auto changeEvent = static_cast<const NativeEmbedDataInfo*>(event)) {
                auto& onNativeEmbedLifecycleChange = const_cast<NativeEmbedDataInfo&>(*changeEvent);
                originalCallback(onNativeEmbedLifecycleChange);
            }
        };
        WebModelNG::SetNativeEmbedLifecycleChangeId(frameNode, std::move(adaptedCallback));
    } else {
        WebModelNG::SetNativeEmbedLifecycleChangeId(frameNode, nullptr);
    }
}

void ResetOnNativeEmbedLifecycleChange(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetNativeEmbedLifecycleChangeId(frameNode, nullptr);
}

void SetOnNativeEmbedGestureEvent(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto* originalCallbackPtr = reinterpret_cast<std::function<void(NativeEmbeadTouchInfo&)>*>(extraParam);
    CHECK_NULL_VOID(originalCallbackPtr);
    if (extraParam) {
        auto adaptedCallback = [originalCallback = *originalCallbackPtr](const BaseEventInfo* event) {
            if (auto gestureEvent = static_cast<const NativeEmbeadTouchInfo*>(event)) {
                auto& onNativeEmbedGesture = const_cast<NativeEmbeadTouchInfo&>(*gestureEvent);
                originalCallback(onNativeEmbedGesture);
            }
        };
        WebModelNG::SetNativeEmbedGestureEventId(frameNode, std::move(adaptedCallback));
    } else {
        WebModelNG::SetNativeEmbedGestureEventId(frameNode, nullptr);
    }
}

void ResetOnNativeEmbedGestureEvent(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetNativeEmbedGestureEventId(frameNode, nullptr);
}

void SetRegisterNativeEmbedRule(ArkUINodeHandle node, ArkUI_CharPtr tag, ArkUI_CharPtr type)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::RegisterNativeEmbedRule(frameNode, tag, type);
}

void ResetRegisterNativeEmbedRule(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::RegisterNativeEmbedRule(frameNode, nullptr, nullptr);
}

void SetNativeEmbedOptions(ArkUINodeHandle node, ArkUI_Bool value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetIntrinsicSizeEnabled(frameNode, value);
}

void ResetNativeEmbedOptions(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetIntrinsicSizeEnabled(frameNode, DEFAULT_NATIVE_EMBED_OPTIONS);
}

void SetOnFirstContentfulPaint(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto* originalCallbackPtr = reinterpret_cast<std::function<void(AudioStateChangedEvent&)>*>(extraParam);
    CHECK_NULL_VOID(originalCallbackPtr);
    if (extraParam) {
        auto adaptedCallback = [originalCallback = *originalCallbackPtr](const std::shared_ptr<BaseEventInfo>& event) {
            auto* onFirstContentfulPaint = static_cast<AudioStateChangedEvent*>(event.get());
            if (onFirstContentfulPaint != nullptr) {
                originalCallback(*onFirstContentfulPaint);
            }
        };
        WebModelNG::SetFirstContentfulPaintId(frameNode, std::move(adaptedCallback));
    } else {
        WebModelNG::SetFirstContentfulPaintId(frameNode, nullptr);
    }
}

void ResetOnFirstContentfulPaint(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetFirstContentfulPaintId(frameNode, nullptr);
}

void SetOnAudioStateChanged(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto* originalCallbackPtr = reinterpret_cast<std::function<void(AudioStateChangedEvent&)>*>(extraParam);
    CHECK_NULL_VOID(originalCallbackPtr);
    if (extraParam) {
        auto adaptedCallback = [originalCallback = *originalCallbackPtr](const std::shared_ptr<BaseEventInfo>& event) {
            auto* onAudioStateChanged = static_cast<AudioStateChangedEvent*>(event.get());
            if (onAudioStateChanged != nullptr) {
                originalCallback(*onAudioStateChanged);
            }
        };
        WebModelNG::SetAudioStateChangedId(frameNode, std::move(adaptedCallback));
    } else {
        WebModelNG::SetAudioStateChangedId(frameNode, nullptr);
    }
}

void ResetOnAudioStateChanged(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetAudioStateChangedId(frameNode, nullptr);
}

void SetOnFullScreenExit(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (extraParam) {
        auto* originalCallbackPtr = reinterpret_cast<std::function<void()>*>(extraParam);
        CHECK_NULL_VOID(originalCallbackPtr);
        auto adaptedCallback = [originalCallback = *originalCallbackPtr](const BaseEventInfo*) { originalCallback(); };
        WebModelNG::SetOnFullScreenExit(frameNode, std::move(adaptedCallback));
    } else {
        WebModelNG::SetOnFullScreenExit(frameNode, nullptr);
    }
}


void ResetOnFullScreenExit(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetOnFullScreenExit(frameNode, nullptr);
}

void SetImageAccess(ArkUINodeHandle node, ArkUI_Bool value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetImageAccessEnabled(frameNode, value);
}

void ResetImageAccess(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetImageAccessEnabled(frameNode, DEFAULT_IMAGE_ACCESS_ENABLED);
}

void SetOnlineImageAccess(ArkUINodeHandle node, ArkUI_Bool value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetOnLineImageAccessEnabled(frameNode, value);
}

void ResetOnlineImageAccess(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetOnLineImageAccessEnabled(frameNode, DEFAULT_ONLINEIMAGE_ACCESS_ENABLED);
}

void SetMediaPlayGestureAccess(ArkUINodeHandle node, ArkUI_Bool value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetMediaPlayGestureAccess(frameNode, value);
}

void ResetMediaPlayGestureAccess(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetMediaPlayGestureAccess(frameNode, MEDIA_PLAY_GESTURE_ACCESS_ENABLED);
}

void SetMediaOptions(ArkUINodeHandle node, ArkUI_Int32 resumeInterval, ArkUI_Bool audioExclusive)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetAudioResumeInterval(frameNode, resumeInterval);
    WebModelNG::SetAudioExclusive(frameNode, audioExclusive);
}

void ResetMediaOptions(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetAudioResumeInterval(frameNode, DEFAULT_RESUMEINTERVAL);
    WebModelNG::SetAudioExclusive(frameNode, DEFAULT_MEDIA_OPTIONS_ENABLED);
}
void SetOnPageEnd(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto* originalCallbackPtr = reinterpret_cast<std::function<void(LoadWebPageFinishEvent&)>*>(extraParam);
    std::function<void(const BaseEventInfo*)> adaptedCallback;
    if (extraParam) {
        if (originalCallbackPtr) {
        adaptedCallback = [originalCallback = *originalCallbackPtr](const BaseEventInfo* event) {
            if (auto changeEvent = static_cast<const LoadWebPageFinishEvent*>(event)) {
                auto& nativeEmbedEvent = const_cast<LoadWebPageFinishEvent&>(*changeEvent);
                originalCallback(nativeEmbedEvent);
            }
        };
        }
        WebModelNG::SetOnPageFinish(frameNode, std::move(adaptedCallback));
    } else {
        WebModelNG::SetOnPageFinish(frameNode, nullptr);
    }
}

void ResetOnPageEnd(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetOnPageFinish(frameNode, nullptr);
}

void SetOnPageBegin(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto* originalCallbackPtr = reinterpret_cast<std::function<void(LoadWebPageStartEvent&)>*>(extraParam);
    std::function<void(const BaseEventInfo*)> adaptedCallback;
    if (extraParam) {
        if (originalCallbackPtr) {
        adaptedCallback = [originalCallback = *originalCallbackPtr](const BaseEventInfo* event) {
            if (auto changeEvent = static_cast<const LoadWebPageStartEvent*>(event)) {
                auto& nativeEmbedEvent = const_cast<LoadWebPageStartEvent&>(*changeEvent);
                originalCallback(nativeEmbedEvent);
            }
        };
        }
        WebModelNG::SetOnPageStart(frameNode, std::move(adaptedCallback));
    } else {
        WebModelNG::SetOnPageStart(frameNode, nullptr);
    }
}

void ResetOnPageBegin(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetOnPageStart(frameNode, nullptr);
}

void SetOnProgressChange(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto* originalCallbackPtr = reinterpret_cast<std::function<void(LoadWebProgressChangeEvent&)>*>(extraParam);
    std::function<void(const BaseEventInfo*)> adaptedCallback;
    if (extraParam) {
        if (originalCallbackPtr) {
        adaptedCallback = [originalCallback = *originalCallbackPtr](const BaseEventInfo* event) {
            if (auto changeEvent = static_cast<const LoadWebProgressChangeEvent*>(event)) {
                auto& nativeEmbedEvent = const_cast<LoadWebProgressChangeEvent&>(*changeEvent);
                originalCallback(nativeEmbedEvent);
            }
        };
        }
        WebModelNG::SetOnProgressChange(frameNode, std::move(adaptedCallback));
    } else {
        WebModelNG::SetOnProgressChange(frameNode, nullptr);
    }
}

void ResetOnProgressChange(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetOnProgressChange(frameNode, nullptr);
}

void SetOnTitleReceive(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto* originalCallbackPtr = reinterpret_cast<std::function<void(LoadWebTitleReceiveEvent&)>*>(extraParam);
    std::function<void(const BaseEventInfo*)> adaptedCallback;
    if (extraParam) {
        if (originalCallbackPtr) {
        adaptedCallback = [originalCallback = *originalCallbackPtr](const BaseEventInfo* event) {
            if (auto changeEvent = static_cast<const LoadWebTitleReceiveEvent*>(event)) {
                auto& nativeEmbedEvent = const_cast<LoadWebTitleReceiveEvent&>(*changeEvent);
                originalCallback(nativeEmbedEvent);
            }
        };
        }
        WebModelNG::SetOnTitleReceive(frameNode, std::move(adaptedCallback));
    } else {
        WebModelNG::SetOnTitleReceive(frameNode, nullptr);
    }
}

void ResetOnTitleReceive(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetOnTitleReceive(frameNode, nullptr);
}

void SetOnDownloadStart(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto* originalCallbackPtr = reinterpret_cast<std::function<void(DownloadStartEvent&)>*>(extraParam);
    std::function<void(const BaseEventInfo*)> adaptedCallback;
    if (extraParam) {
        if (originalCallbackPtr) {
        adaptedCallback = [originalCallback = *originalCallbackPtr](const BaseEventInfo* event) {
            if (auto changeEvent = static_cast<const DownloadStartEvent*>(event)) {
                auto& nativeEmbedEvent = const_cast<DownloadStartEvent&>(*changeEvent);
                originalCallback(nativeEmbedEvent);
            }
        };
        }
        WebModelNG::SetOnDownloadStart(frameNode, std::move(adaptedCallback));
    } else {
        WebModelNG::SetOnDownloadStart(frameNode, nullptr);
    }
}

void ResetOnDownloadStart(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetOnDownloadStart(frameNode, nullptr);
}

void SetJavaScriptOnDocumentStart(ArkUINodeHandle node, ArkUI_ScriptItemArray* values, ArkUI_Int32 size)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ScriptItems SecriptInfos;
    for (int32_t i = 0; i < size; ++i) {
        std::string script;
        ScriptItemsByOrder scriptRules;
        std::string scriptStr(values[i].script);
        script = scriptStr;
        auto scriptRulesChar = values[i].scriptRules;
        auto scriptRulesSize = values[i].scriptRulesSize;
        ScriptItemsByOrder tmp;
        for (int32_t j = 0; j < scriptRulesSize; ++j) {
            std::string sc(scriptRulesChar[j]);
            tmp.push_back(sc);
        }
        scriptRules = tmp;
        SecriptInfos.insert(std::make_pair(script, scriptRules));
    }
    WebModelNG::JavaScriptOnDocumentStart(frameNode, SecriptInfos);
}

void ResetJavaScriptOnDocumentStart(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::JavaScriptOnDocumentStart(frameNode ,ScriptItems());
}

void SetJavaScriptOnDocumentEnd(ArkUINodeHandle node, ArkUI_ScriptItemArray* values, ArkUI_Int32 size)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ScriptItems SecriptInfos;
    for (int32_t i = 0; i < size; ++i) {
        std::string script;
        ScriptItemsByOrder scriptRules;
        std::string scriptStr(values[i].script);
        script = scriptStr;
        auto scriptRulesChar = values[i].scriptRules;
        auto scriptRulesSize = values[i].scriptRulesSize;
        ScriptItemsByOrder tmp;
        for (int32_t j = 0; j < scriptRulesSize; ++j) {
            std::string sc(scriptRulesChar[j]);
            tmp.push_back(sc);
        }
        scriptRules = tmp;
        SecriptInfos.insert(std::make_pair(script, scriptRules));
    }
    WebModelNG::JavaScriptOnDocumentEnd(frameNode, SecriptInfos);
}

void ResetJavaScriptOnDocumentEnd(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::JavaScriptOnDocumentEnd(frameNode ,ScriptItems());
}

void SetCopyOptionMode(ArkUINodeHandle node, ArkUI_Int32 value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto copyOptions = CopyOptions::Local;
    copyOptions = static_cast<CopyOptions>(value);
    WebModelNG::SetCopyOptionMode(frameNode, static_cast<CopyOptions>(copyOptions));
}

void ResetCopyOptionMode(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetCopyOptionMode(frameNode, DEFAULT_COPY_OPTIONS_VALUE);
}

void SetRenderProcessNotResponding(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto* originalCallbackPtr = reinterpret_cast<std::function<void(RenderProcessNotRespondingEvent&)>*>(extraParam);
    std::function<void(const BaseEventInfo*)> adaptedCallback;
    if (extraParam) {
        if (originalCallbackPtr) {
        adaptedCallback = [originalCallback = *originalCallbackPtr](const BaseEventInfo* event) {
            if (auto changeEvent = static_cast<const RenderProcessNotRespondingEvent*>(event)) {
                auto& nativeEmbedEvent = const_cast<RenderProcessNotRespondingEvent&>(*changeEvent);
                originalCallback(nativeEmbedEvent);
            }
        };
        }
        WebModelNG::SetRenderProcessNotRespondingId(frameNode, std::move(adaptedCallback));
    } else {
        WebModelNG::SetRenderProcessNotRespondingId(frameNode, nullptr);
    }
}

void ResetRenderProcessNotResponding(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetRenderProcessNotRespondingId(frameNode, nullptr);
}

void SetOnPageVisibleCallBack(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (extraParam) {
        auto* originalCallbackPtr = reinterpret_cast<std::function<void(PageVisibleEvent&)>*>(extraParam);
        CHECK_NULL_VOID(originalCallbackPtr);
        auto callback = [originalCallback = *originalCallbackPtr](const std::shared_ptr<BaseEventInfo>& event) {
            auto* concreteEvent = static_cast<PageVisibleEvent*>(event.get());
            CHECK_NULL_VOID(originalCallback);
            originalCallback(*concreteEvent);
        };
        WebModelNG::SetOnPageVisible(frameNode, std::move(callback));
    } else {
        WebModelNG::SetOnPageVisible(frameNode, nullptr);
    }
}

void ResetOnPageVisibleCallBack(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetOnPageVisible(frameNode, nullptr);
}

void SetOnRenderExitedCallBack(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (extraParam) {
        auto* renderExitedPtr = reinterpret_cast<std::function<void(RenderExitedEvent&)>*>(extraParam);
        std::function<void(const BaseEventInfo*)> callback;
        CHECK_NULL_VOID(renderExitedPtr);
        callback = [renderExitedPtrCallback = *renderExitedPtr](const BaseEventInfo* event) {
            if (auto renderExitedEvent = static_cast<const RenderExitedEvent*>(event)) {
                auto& nonConstEvent = const_cast<RenderExitedEvent&>(*renderExitedEvent);
                renderExitedPtrCallback(nonConstEvent);
            }
        };
        WebModelNG::SetOnRenderExited(frameNode, std::move(callback));
    } else {
        WebModelNG::SetOnRenderExited(frameNode, nullptr);
    }
}

void ResetOnRenderExitedCallBack(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetOnRenderExited(frameNode, nullptr);
}

void SetBlockNetwork(ArkUINodeHandle node, ArkUI_Bool value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetBlockNetwork(frameNode, value);
}

void ResetBlockNetwork(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetBlockNetwork(frameNode, DEFAULT_BLOCK_NETWORK_ENABLED);
}

void SetOnResourceLoadCallBack(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (extraParam) {
        auto* resourceLoadPtr = reinterpret_cast<std::function<void(ResourceLoadEvent&)>*>(extraParam);
        CHECK_NULL_VOID(resourceLoadPtr);
        auto callback = [resourceLoadCallback = *resourceLoadPtr](const BaseEventInfo* event) {
            if (auto scrollEvent = static_cast<const ResourceLoadEvent*>(event)) {
                auto& nonConstEvent = const_cast<ResourceLoadEvent&>(*scrollEvent);
                resourceLoadCallback(nonConstEvent);
            }
        };
        WebModelNG::SetOnResourceLoad(frameNode, std::move(callback));
    } else {
        WebModelNG::SetOnResourceLoad(frameNode, nullptr);
    }
}

void ResetOnResourceLoadCallBack(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetOnResourceLoad(frameNode, nullptr);
}

void SetOnRefreshAccessedHistoryCallBack(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (extraParam) {
        auto* refreshAccessedHistoryPtr =
            reinterpret_cast<std::function<void(RefreshAccessedHistoryEvent&)>*>(extraParam);
        CHECK_NULL_VOID(refreshAccessedHistoryPtr);
        auto callback = [refreshAccessedHistoryCallback = *refreshAccessedHistoryPtr](const BaseEventInfo* event) {
            if (auto scrollEvent = static_cast<const RefreshAccessedHistoryEvent*>(event)) {
                auto& nonConstEvent = const_cast<RefreshAccessedHistoryEvent&>(*scrollEvent);
                refreshAccessedHistoryCallback(nonConstEvent);
            }
        };
        WebModelNG::SetOnRefreshAccessedHistory(frameNode, std::move(callback));
    } else {
        WebModelNG::SetOnRefreshAccessedHistory(frameNode, nullptr);
    }
}

void ResetOnRefreshAccessedHistoryCallBack(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetOnRefreshAccessedHistory(frameNode, nullptr);
}

void SetOnNavigationEntryCommittedCallBack(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (extraParam) {
        auto* originalCallbackPtr = reinterpret_cast<std::function<void(NavigationEntryCommittedEvent&)>*>(extraParam);
        CHECK_NULL_VOID(originalCallbackPtr);
        auto callback = [originalCallback = *originalCallbackPtr](const std::shared_ptr<BaseEventInfo>& event) {
            auto* concreteEvent = static_cast<NavigationEntryCommittedEvent*>(event.get());
            CHECK_NULL_VOID(originalCallback);
            originalCallback(*concreteEvent);
        };
        WebModelNG::SetOnNavigationEntryCommitted(frameNode, std::move(callback));
    } else {
        WebModelNG::SetOnNavigationEntryCommitted(frameNode, nullptr);
    }
}

void ResetOnNavigationEntryCommittedCallBack(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetOnNavigationEntryCommitted(frameNode, nullptr);
}

void SetOnSearchResultReceiveCallBack(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (extraParam) {
        auto* searchResultReceivePtr = reinterpret_cast<std::function<void(SearchResultReceiveEvent&)>*>(extraParam);
        CHECK_NULL_VOID(searchResultReceivePtr);
        auto callback = [searchResultReceiveCallback = *searchResultReceivePtr](const BaseEventInfo* event) {
            if (auto scrollEvent = static_cast<const SearchResultReceiveEvent*>(event)) {
                auto& nonConstEvent = const_cast<SearchResultReceiveEvent&>(*scrollEvent);
                searchResultReceiveCallback(nonConstEvent);
            }
        };
        WebModelNG::SetOnSearchResultReceive(frameNode, std::move(callback));
    } else {
        WebModelNG::SetOnSearchResultReceive(frameNode, nullptr);
    }
}

void ResetOnSearchResultReceiveCallBack(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetOnSearchResultReceive(frameNode, nullptr);
}


void SetOverScrollMode(ArkUINodeHandle node, ArkUI_Int32 value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetOverScrollMode(frameNode, OverScrollMode(value));
}

void ResetOverScrollMode(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetOverScrollMode(frameNode, DEFAULT_OVERSCROLL_MODE);
}

void SetOnTouchIconUrlReceivedCallBack(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (extraParam) {
        auto* originalCallbackPtr = reinterpret_cast<std::function<void(TouchIconUrlEvent&)>*>(extraParam);
        CHECK_NULL_VOID(originalCallbackPtr);
        auto callback = [originalCallback = *originalCallbackPtr](const std::shared_ptr<BaseEventInfo>& event) {
            auto* concreteEvent = static_cast<TouchIconUrlEvent*>(event.get());
            CHECK_NULL_VOID(originalCallback);
            originalCallback(*concreteEvent);
        };
        WebModelNG::SetOnTouchIconUrlReceived(frameNode, std::move(callback));
    } else {
        WebModelNG::SetOnTouchIconUrlReceived(frameNode, nullptr);
    }
}

void ResetOnTouchIconUrlReceivedCallBack(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetOnTouchIconUrlReceived(frameNode, nullptr);
}

void SetOnRenderProcessRespondingCallBack(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (extraParam) {
        auto* originalCallbackPtr = reinterpret_cast<std::function<void()>*>(extraParam);
        CHECK_NULL_VOID(originalCallbackPtr);
        auto callback = [originalCallback = *originalCallbackPtr](const BaseEventInfo*) { originalCallback(); };
        WebModelNG::SetOnRenderProcessResponding(frameNode, std::move(callback));
    } else {
        WebModelNG::SetOnRenderProcessResponding(frameNode, nullptr);
    }
}

void ResetOnRenderProcessRespondingCallBack(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetOnRenderProcessResponding(frameNode, nullptr);
}

void SetOnWindowNew(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto* originalCallbackPtr = reinterpret_cast<std::function<void(WebWindowNewEvent&)>*>(extraParam);
    CHECK_NULL_VOID(originalCallbackPtr);
    if (extraParam) {
        auto adaptedCallback = [originalCallback = *originalCallbackPtr](const std::shared_ptr<BaseEventInfo>& event) {
            auto* onWindowNew = static_cast<WebWindowNewEvent*>(event.get());
            if (onWindowNew != nullptr) {
                originalCallback(*onWindowNew);
            }
        };
        WebModelNG::SetWindowNewEvent(frameNode, std::move(adaptedCallback));
    } else {
        WebModelNG::SetWindowNewEvent(frameNode, nullptr);
    }
}

void ResetOnWindowNew(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetWindowNewEvent(frameNode, nullptr);
}

void SetOnPermissionRequest(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (extraParam) {
        auto* eventPtr = reinterpret_cast<std::function<void(WebPermissionRequestEvent&)>*>(extraParam);
        CHECK_NULL_VOID(eventPtr);
        auto callback = [webPermissionRequestEventCallback = *eventPtr](const BaseEventInfo* event) {
            if (auto webPermissionRequestEvent = static_cast<const WebPermissionRequestEvent*>(event)) {
                auto& nonConstEvent = const_cast<WebPermissionRequestEvent&>(*webPermissionRequestEvent);
                webPermissionRequestEventCallback(nonConstEvent);
            }
        };
        WebModelNG::SetPermissionRequestEventId(frameNode, std::move(callback));
    } else {
        WebModelNG::SetPermissionRequestEventId(frameNode, nullptr);
    }
}

void ResetOnPermissionRequest(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetPermissionRequestEventId(frameNode, nullptr);
}

void SetOnScreenCaptureRequest(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (extraParam) {
        auto* eventPtr = reinterpret_cast<std::function<void(WebScreenCaptureRequestEvent&)>*>(extraParam);
        CHECK_NULL_VOID(eventPtr);
        auto callback = [webScreenCaptureRequestEventCallback = *eventPtr](const BaseEventInfo* event) {
            if (auto webPermissionRequestEvent = static_cast<const WebScreenCaptureRequestEvent*>(event)) {
                auto& nonConstEvent = const_cast<WebScreenCaptureRequestEvent&>(*webPermissionRequestEvent);
                webScreenCaptureRequestEventCallback(nonConstEvent);
            }
        };
        WebModelNG::SetScreenCaptureRequestEventId(frameNode, std::move(callback));
    } else {
        WebModelNG::SetScreenCaptureRequestEventId(frameNode, nullptr);
    }
}

void ResetOnScreenCaptureRequest(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetScreenCaptureRequestEventId(frameNode, nullptr);
}

void SetOnFullScreenEnter(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (extraParam) {
        auto* originalCallbackPtr = reinterpret_cast<std::function<void(FullScreenEnterEvent&)>*>(extraParam);
        CHECK_NULL_VOID(originalCallbackPtr);
        auto callback = [originalCallback = *originalCallbackPtr](const BaseEventInfo* event) {
            if (auto scrollEvent = static_cast<const FullScreenEnterEvent*>(event)) {
                auto& nonConstEvent = const_cast<FullScreenEnterEvent&>(*scrollEvent);
                originalCallback(nonConstEvent);
                return true;
            }
            return false;
        };
        WebModelNG::SetOnFullScreenEnter(frameNode, std::move(callback));
    } else {
        WebModelNG::SetOnFullScreenEnter(frameNode, nullptr);
    }
}

void ResetOnFullScreenEnter(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetOnFullScreenEnter(frameNode, nullptr);
}

void SetOnWindowExit(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (extraParam) {
        auto* OnWindowExit = reinterpret_cast<std::function<void()>*>(extraParam);
        std::function<void(const BaseEventInfo*)> adaptedCallback;
        if (OnWindowExit) {
            adaptedCallback = [originalCallback = *OnWindowExit](const BaseEventInfo*) { originalCallback(); };
        }
        WebModelNG::SetWindowExitEventId(frameNode, std::move(adaptedCallback));
    } else {
        WebModelNG::SetWindowExitEventId(frameNode, nullptr);
    }
}

void ResetOnWindowExit(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetWindowExitEventId(frameNode, nullptr);
}

void SetOnAlertlCallBack(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (extraParam) {
        auto* webDialogEventPtr = reinterpret_cast<std::function<bool(WebDialogEvent&)>*>(extraParam);
        CHECK_NULL_VOID(webDialogEventPtr);
        auto callback = [webDialogEventCallback = *webDialogEventPtr](const BaseEventInfo* event) {
            CHECK_NULL_RETURN(event, false);
            if (auto webDialogEvent = static_cast<const WebDialogEvent*>(event)) {
                auto& nonConstEvent = const_cast<WebDialogEvent&>(*webDialogEvent);
                return webDialogEventCallback(nonConstEvent);
            }
            return false;
        };
        WebModelNG::SetOnAlert(frameNode, std::move(callback), DialogEventType::DIALOG_EVENT_ALERT);
    } else {
        WebModelNG::SetOnAlert(frameNode, nullptr, DialogEventType::DIALOG_EVENT_ALERT);
    }
}

void ResetOnAlertlCallBack(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetOnAlert(frameNode, nullptr, DialogEventType::DIALOG_EVENT_ALERT);
}

void SetOnConfirmCallBack(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (extraParam) {
        auto* webDialogEventPtr = reinterpret_cast<std::function<bool(WebDialogEvent&)>*>(extraParam);
        CHECK_NULL_VOID(webDialogEventPtr);
        auto callback = [webDialogEventCallback = *webDialogEventPtr](const BaseEventInfo* event) {
            CHECK_NULL_RETURN(event, false);
            if (auto webDialogEvent = static_cast<const WebDialogEvent*>(event)) {
                auto& nonConstEvent = const_cast<WebDialogEvent&>(*webDialogEvent);
                return webDialogEventCallback(nonConstEvent);
                // return true;
            }
            return false;
        };
        WebModelNG::SetOnConfirm(frameNode, std::move(callback), DialogEventType::DIALOG_EVENT_CONFIRM);
    } else {
        WebModelNG::SetOnConfirm(frameNode, nullptr, DialogEventType::DIALOG_EVENT_CONFIRM);
    }
}

void ResetOnConfirmCallBack(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetOnConfirm(frameNode, nullptr, DialogEventType::DIALOG_EVENT_CONFIRM);
}

void SetOnPromptCallBack(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (extraParam) {
        auto* webDialogEventPtr = reinterpret_cast<std::function<bool(WebDialogEvent&)>*>(extraParam);
        CHECK_NULL_VOID(webDialogEventPtr);
        auto callback = [webDialogEventCallback = *webDialogEventPtr](const BaseEventInfo* event) {
            CHECK_NULL_RETURN(event, false);
            auto webDialogEvent = static_cast<const WebDialogEvent*>(event);
            if (webDialogEvent) {
                auto& nonConstEvent = const_cast<WebDialogEvent&>(*webDialogEvent);
                return webDialogEventCallback(nonConstEvent);
            }
            return false;
        };
        WebModelNG::SetOnPrompt(frameNode, std::move(callback), DialogEventType::DIALOG_EVENT_PROMPT);
    } else {
        WebModelNG::SetOnPrompt(frameNode, nullptr, DialogEventType::DIALOG_EVENT_PROMPT);
    }
}

void ResetOnPromptCallBack(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetOnPrompt(frameNode, nullptr, DialogEventType::DIALOG_EVENT_PROMPT);
}

void SetOnShowFileSelector(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (extraParam) {
        auto* fileSelectorPtr = reinterpret_cast<std::function<bool(FileSelectorEvent&)>*>(extraParam);
        CHECK_NULL_VOID(fileSelectorPtr);
        auto callback = [fileSelectorCallback = *fileSelectorPtr](const BaseEventInfo* event) {
            if (auto scrollEvent = static_cast<const FileSelectorEvent*>(event)) {
                auto& nonConstEvent = const_cast<FileSelectorEvent&>(*scrollEvent);
                auto ret = fileSelectorCallback(nonConstEvent);
                return ret;
            }
            return false;
        };
        WebModelNG::SetOnShowFileSelector(frameNode, std::move(callback));
    } else {
        WebModelNG::SetOnShowFileSelector(frameNode, nullptr);
    }
}

void ResetOnShowFileSelector(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetOnShowFileSelector(frameNode, nullptr);
}

void SetOnContextMenuShow(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (extraParam) {
        auto* contextMenuShowPtr = reinterpret_cast<std::function<bool(ContextMenuEvent&)>*>(extraParam);
        CHECK_NULL_VOID(contextMenuShowPtr);
        auto callback = [contextMenuShowCallback = *contextMenuShowPtr](const BaseEventInfo* event) {
            if (auto scrollEvent = static_cast<const ContextMenuEvent*>(event)) {
                auto& nonConstEvent = const_cast<ContextMenuEvent&>(*scrollEvent);
                return contextMenuShowCallback(nonConstEvent);
            }
            return false;
        };
        WebModelNG::SetOnContextMenuShow(frameNode, std::move(callback));
    } else {
        WebModelNG::SetOnContextMenuShow(frameNode, nullptr);
    }
}

void ResetOnContextMenuShow(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetOnContextMenuShow(frameNode, nullptr);
}

void SetOnSafeBrowsingCheckResultCallBack(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (extraParam) {
        auto* originalCallbackPtr = reinterpret_cast<std::function<void(SafeBrowsingCheckResultEvent&)>*>(extraParam);
        CHECK_NULL_VOID(originalCallbackPtr);
        auto callback = [originalCallback = *originalCallbackPtr](const std::shared_ptr<BaseEventInfo>& event) {
            auto* concreteEvent = static_cast<SafeBrowsingCheckResultEvent*>(event.get());
            CHECK_NULL_VOID(originalCallback);
            originalCallback(*concreteEvent);
        };
        WebModelNG::SetOnSafeBrowsingCheckResult(frameNode, std::move(callback));
    } else {
        WebModelNG::SetOnSafeBrowsingCheckResult(frameNode, nullptr);
    }
}

void ResetOnSafeBrowsingCheckResultCallBack(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetOnSafeBrowsingCheckResult(frameNode, nullptr);
}

void SetWebNestedScrollExt(
    ArkUINodeHandle node, ArkUI_Int32 scrollUp, ArkUI_Int32 scrollDown, ArkUI_Int32 scrollLeft, ArkUI_Int32 scrollRight)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NestedScrollOptionsExt nestedOpt = {
        .scrollUp = NestedScrollMode::SELF_FIRST,
        .scrollDown = NestedScrollMode::SELF_FIRST,
        .scrollLeft = NestedScrollMode::SELF_FIRST,
        .scrollRight = NestedScrollMode::SELF_FIRST,
    };
    nestedOpt.scrollUp = static_cast<NestedScrollMode>(scrollUp);
    nestedOpt.scrollDown = static_cast<NestedScrollMode>(scrollDown);
    nestedOpt.scrollLeft = static_cast<NestedScrollMode>(scrollLeft);
    nestedOpt.scrollRight = static_cast<NestedScrollMode>(scrollRight);
    WebModelNG::SetNestedScrollExt(frameNode, nestedOpt);
}

void ResetWebNestedScrollExt(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    const NestedScrollOptionsExt nestedOpt = {
        .scrollUp = NestedScrollMode::SELF_FIRST,
        .scrollDown = NestedScrollMode::SELF_FIRST,
        .scrollLeft = NestedScrollMode::SELF_FIRST,
        .scrollRight = NestedScrollMode::SELF_FIRST,
    };
    WebModelNG::SetNestedScrollExt(frameNode, nestedOpt);
}

void SetOnInterceptKeyEventCallBack(ArkUINodeHandle node, void* callback)
{
    auto* eventFunc = reinterpret_cast<std::function<bool(KeyEventInfo&)>*>(callback);
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    WeakPtr<NG::FrameNode> weak = AceType::WeakClaim(frameNode);
    auto onKeyEvent = [func = *eventFunc, weak](KeyEventInfo& keyEventInfo) -> bool {
        auto frameNode = weak.Upgrade();
        int32_t instanceId = INSTANCE_ID_UNDEFINED;
        if (frameNode) {
            instanceId = frameNode->GetInstanceId();
        } else {
            instanceId = Container::CurrentIdSafely();
        }

        ContainerScope scope(instanceId);
        auto context = PipelineBase::GetCurrentContext();
        bool result = false;
        CHECK_NULL_RETURN(context, result);

        context->PostSyncEvent(
            [func, &keyEventInfo, &result]() { result = func(keyEventInfo); }, "ArkUIWebInterceptKeyEventCallback");
        return result;
    };
    WebModelNG::SetOnInterceptKeyEvent(frameNode, std::move(onKeyEvent));
}

void ResetOnInterceptKeyEventCallBack(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetOnInterceptKeyEvent(frameNode, nullptr);
}

void SetOnErrorReceive(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (extraParam) {
        auto* originalCallbackPtr = reinterpret_cast<std::function<void(ReceivedErrorEvent&)>*>(extraParam);
        CHECK_NULL_VOID(originalCallbackPtr);
        auto callback = [originalCallback = *originalCallbackPtr](const BaseEventInfo* event) {
            if (auto scrollEvent = static_cast<const ReceivedErrorEvent*>(event)) {
                auto& nonConstEvent = const_cast<ReceivedErrorEvent&>(*scrollEvent);
                originalCallback(nonConstEvent);
                return true;
            }
            return false;
        };
        WebModelNG::SetOnErrorReceive(frameNode, std::move(callback));
    } else {
        WebModelNG::SetOnErrorReceive(frameNode, nullptr);
    }
}

void ResetOnErrorReceive(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetOnErrorReceive(frameNode, nullptr);
}

void SetOnLoadIntercept(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (extraParam) {
        auto* originalCallbackPtr = reinterpret_cast<std::function<bool(LoadInterceptEvent&)>*>(extraParam);
        CHECK_NULL_VOID(originalCallbackPtr);
        auto callback = [originalCallback = *originalCallbackPtr](const BaseEventInfo* event) {
            if (auto scrollEvent = static_cast<const LoadInterceptEvent*>(event)) {
                auto& nonConstEvent = const_cast<LoadInterceptEvent&>(*scrollEvent);
                return originalCallback(nonConstEvent);
            }
            return false;
        };
        WebModelNG::SetOnLoadIntercept(frameNode, std::move(callback));
    } else {
        WebModelNG::SetOnLoadIntercept(frameNode, nullptr);
    }
}

void ResetOnLoadIntercept(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetOnLoadIntercept(frameNode, nullptr);
}

void SetOnHttpErrorReceive(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (extraParam) {
        auto* originalCallbackPtr = reinterpret_cast<std::function<void(ReceivedHttpErrorEvent&)>*>(extraParam);
        CHECK_NULL_VOID(originalCallbackPtr);
        auto callback = [originalCallback = *originalCallbackPtr](const BaseEventInfo* event) {
            if (auto scrollEvent = static_cast<const ReceivedHttpErrorEvent*>(event)) {
                auto& nonConstEvent = const_cast<ReceivedHttpErrorEvent&>(*scrollEvent);
                originalCallback(nonConstEvent);
                return true;
            }
            return false;
        };
        WebModelNG::SetOnHttpErrorReceive(frameNode, std::move(callback));
    } else {
        WebModelNG::SetOnHttpErrorReceive(frameNode, nullptr);
    }
}

void ResetOnHttpErrorReceive(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetOnHttpErrorReceive(frameNode, nullptr);
}

void SetOnOverrideUrlLoading(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (extraParam) {
        auto* originalCallbackPtr = reinterpret_cast<std::function<bool(LoadOverrideEvent&)>*>(extraParam);
        CHECK_NULL_VOID(originalCallbackPtr);
        auto callback = [originalCallback = *originalCallbackPtr](const BaseEventInfo* event) {
            if (auto scrollEvent = static_cast<const LoadOverrideEvent*>(event)) {
                auto& nonConstEvent = const_cast<LoadOverrideEvent&>(*scrollEvent);
                return originalCallback(nonConstEvent);
            }
            return false;
        };
        WebModelNG::SetOnOverrideUrlLoading(frameNode, std::move(callback));
    } else {
        WebModelNG::SetOnOverrideUrlLoading(frameNode, nullptr);
    }
}

void ResetOnOverrideUrlLoading(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetOnOverrideUrlLoading(frameNode, nullptr);
}

void SetOnHttpAuthRequest(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (extraParam) {
        auto* originalCallbackPtr = reinterpret_cast<std::function<bool(WebHttpAuthEvent&)>*>(extraParam);
        CHECK_NULL_VOID(originalCallbackPtr);
        auto callback = [originalCallback = *originalCallbackPtr](const BaseEventInfo* event) {
            if (auto scrollEvent = static_cast<const WebHttpAuthEvent*>(event)) {
                auto& nonConstEvent = const_cast<WebHttpAuthEvent&>(*scrollEvent);
                return originalCallback(nonConstEvent);
            }
            return false;
        };
        WebModelNG::SetOnHttpAuthRequest(frameNode, std::move(callback));
    } else {
        WebModelNG::SetOnHttpAuthRequest(frameNode, nullptr);
    }
}

void ResetOnHttpAuthRequest(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetOnHttpAuthRequest(frameNode, nullptr);
}

void SetOnConsole(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (extraParam) {
        auto* loadWebConsoleLogEventPtr = reinterpret_cast<std::function<bool(LoadWebConsoleLogEvent&)>*>(extraParam);
        CHECK_NULL_VOID(loadWebConsoleLogEventPtr);
        auto callback = [loadWebConsoleLogEventCallback = *loadWebConsoleLogEventPtr](const BaseEventInfo* event) {
            CHECK_NULL_RETURN(event, false);
            auto loadWebConsoleLogEvent = static_cast<const LoadWebConsoleLogEvent*>(event);
            if (loadWebConsoleLogEvent) {
                auto& nonConstEvent = const_cast<LoadWebConsoleLogEvent&>(*loadWebConsoleLogEvent);
                return loadWebConsoleLogEventCallback(nonConstEvent);
            }
            return false;
        };
        WebModelNG::SetOnConsole(frameNode, std::move(callback));
    } else {
        WebModelNG::SetOnConsole(frameNode, nullptr);
    }
}

void ResetOnConsole(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetOnConsole(frameNode, nullptr);
}

void SetOnSslErrorEvent(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (extraParam) {
        auto* originalCallback = static_cast<std::function<void(WebAllSslErrorEvent&)>*>(extraParam);
        CHECK_NULL_VOID(originalCallback);

        auto callback = [originalFunc = *originalCallback](const BaseEventInfo* event) -> bool {
            CHECK_NULL_RETURN(event, false);
            auto* sslEvent = static_cast<const WebAllSslErrorEvent*>(event);
            originalFunc(const_cast<WebAllSslErrorEvent&>(*sslEvent));
            return true;
        };
        WebModelNG::SetOnSslErrorEvent(frameNode, std::move(callback));
    } else {
        WebModelNG::SetOnSslErrorEvent(frameNode, nullptr);
    }
}

void ResetOnSslErrorEvent(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetOnSslErrorEvent(frameNode, nullptr);
}

void SetOnDataResubmitted(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (extraParam) {
        auto* originalCallbackPtr = reinterpret_cast<std::function<void(DataResubmittedEvent&)>*>(extraParam);
        CHECK_NULL_VOID(originalCallbackPtr);
        auto callback = [originalCallback = *originalCallbackPtr](const std::shared_ptr<BaseEventInfo>& event) {
            auto* concreteEvent = static_cast<DataResubmittedEvent*>(event.get());
            CHECK_NULL_VOID(originalCallback);
            originalCallback(*concreteEvent);
        };
        WebModelNG::SetOnDataResubmitted(frameNode, std::move(callback));
    } else {
        WebModelNG::SetOnDataResubmitted(frameNode, nullptr);
    }
}

void ResetOnDataResubmitted(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetOnDataResubmitted(frameNode, nullptr);
}

namespace NodeModifier {
const ArkUIWebModifier* GetWebModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIWebModifier modifier = {
        .getWebController = nullptr,
        .getWebviewController = nullptr,
        .setWebOptions = nullptr,
        .setWebSrcResources = nullptr,
        .setJavaScriptAccess = SetJavaScriptAccess,
        .resetJavaScriptAccess = ResetJavaScriptAccess,
        .setFileAccessEnabled = SetFileAccessEnabled,
        .resetFileAccessEnabled = ResetFileAccessEnabled,
        .setDomStorageAccessEnabled = SetDomStorageAccessEnabled,
        .resetDomStorageAccessEnabled = ResetDomStorageAccessEnabled,
        .setMixedMode = SetMixedMode,
        .resetMixedMode = ResetMixedMode,
        .setZoomAccessEnabled = SetZoomAccessEnabled,
        .resetZoomAccessEnabled = ResetZoomAccessEnabled,
        .setCacheMode = SetCacheMode,
        .resetCacheMode = ResetCacheMode,
        .setDarkMode = SetDarkMode,
        .resetDarkMode = ResetDarkMode,
        .setMultiWindowAccessEnabled = SetMultiWindowAccessEnabled,
        .resetMultiWindowAccessEnabled = ResetMultiWindowAccessEnabled,
        .setAllowWindowOpenMethod = SetAllowWindowOpenMethod,
        .resetAllowWindowOpenMethod = ResetAllowWindowOpenMethod,
        .setKeyboardAvoidMode = SetKeyboardAvoidMode,
        .resetKeyboardAvoidMode = ResetKeyboardAvoidMode,
        .setOnControllerAttached = SetOnControllerAttached,
        .resetOnControllerAttached = ResetOnControllerAttached,
        .setVerticalScrollBarAccessEnabled = SetVerticalScrollBarAccessEnabled,
        .resetVerticalScrollBarAccessEnabled = ResetVerticalScrollBarAccessEnabled,
        .setHorizontalScrollBarAccessEnabled = SetHorizontalScrollBarAccessEnabled,
        .resetHorizontalScrollBarAccessEnabled = ResetHorizontalScrollBarAccessEnabled,
        .setTextZoomRatio = SetTextZoomRatio,
        .resetTextZoomRatio = ResetTextZoomRatio,
        .setInitialScale = SetInitialScale,
        .resetInitialScale = ResetInitialScale,
        .setOnScrollCallBack = SetOnScrollCallBack,
        .resetOnScrollCallBack = ResetOnScrollCallBack,
        .setOnOverScrollCallBack = SetOnOverScrollCallBack,
        .resetOnOverScrollCallBack = ResetOnOverScrollCallBack,
        .setOnScaleChangeCallBack = SetOnScaleChangeCallBack,
        .resetOnScaleChangeCallBack = ResetOnScaleChangeCallBack,
        .setOnRequestSelectedCallBack = SetOnRequestSelectedCallBack,
        .resetOnRequestSelectedCallBack = ResetOnRequestSelectedCallBack,
        .setOnContextMenuHideCallBack = SetOnContextMenuHideCallBack,
        .resetOnContextMenuHideCallBack = ResetOnContextMenuHideCallBack,
        .setGeolocationAccess = SetGeolocationAccess,
        .resetGeolocationAccess = ResetGeolocationAccess,
        .setDatabaseAccess = SetDatabaseAccess,
        .resetDatabaseAccess = ResetDatabaseAccess,
        .setOverviewModeAccess = SetOverviewModeAccess,
        .resetOverviewModeAccess = ResetOverviewModeAccess,
        .setForceDarkAccess = SetForceDarkAccess,
        .resetForceDarkAccess = ResetForceDarkAccess,
        .setPinchSmooth = SetPinchSmooth,
        .resetPinchSmooth = ResetPinchSmooth,
        .setMetaViewport = SetMetaViewport,
        .resetMetaViewport = ResetMetaViewport,
        .setEnableFollowSystemFontWeight = SetEnableFollowSystemFontWeight,
        .resetEnableFollowSystemFontWeight = ResetEnableFollowSystemFontWeight,
        .setEnableNativeEmbedMode = SetEnableNativeEmbedMode,
        .resetEnableNativeEmbedMode = ResetEnableNativeEmbedMode,
        .setMinFontSize = SetMinFontSize,
        .resetMinFontSize = ResetMinFontSize,
        .setDefaultFontSize = SetDefaultFontSize,
        .resetDefaultFontSize = ResetDefaultFontSize,
        .setDefaultFixedFontSize = SetDefaultFixedFontSize,
        .resetDefaultFixedFontSize = ResetDefaultFixedFontSize,
        .setMinLogicalFontSize = SetMinLogicalFontSize,
        .resetMinLogicalFontSize = ResetMinLogicalFontSize,
        .setWebStandardFont = SetWebStandardFont,
        .resetWebStandardFont = ResetWebStandardFont,
        .setWebSerifFont = SetWebSerifFont,
        .resetWebSerifFont = ResetWebSerifFont,
        .setWebSansSerifFont = SetWebSansSerifFont,
        .resetWebSansSerifFont = ResetWebSansSerifFont,
        .setWebFixedFont = SetWebFixedFont,
        .resetWebFixedFont = ResetWebFixedFont,
        .setWebFantasyFont = SetWebFantasyFont,
        .resetWebFantasyFont = ResetWebFantasyFont,
        .setWebCursiveFont = SetWebCursiveFont,
        .resetWebCursiveFont = ResetWebCursiveFont,
        .setLayoutMode = SetLayoutMode,
        .resetLayoutMode = ResetLayoutMode,
        .setOnNativeEmbedLifecycleChange = SetOnNativeEmbedLifecycleChange,
        .resetOnNativeEmbedLifecycleChange = ResetOnNativeEmbedLifecycleChange,
        .setOnNativeEmbedGestureEvent = SetOnNativeEmbedGestureEvent,
        .resetOnNativeEmbedGestureEvent = ResetOnNativeEmbedGestureEvent,
        .setRegisterNativeEmbedRule = SetRegisterNativeEmbedRule,
        .resetRegisterNativeEmbedRule = ResetRegisterNativeEmbedRule,
        .setNativeEmbedOptions = SetNativeEmbedOptions,
        .resetNativeEmbedOptions = ResetNativeEmbedOptions,
        .setOnFirstContentfulPaint = SetOnFirstContentfulPaint,
        .resetOnFirstContentfulPaint = ResetOnFirstContentfulPaint,
        .setOnAudioStateChanged = SetOnAudioStateChanged,
        .resetOnAudioStateChanged = ResetOnAudioStateChanged,
        .setOnFullScreenExit = SetOnFullScreenExit,
        .resetOnFullScreenExit = ResetOnFullScreenExit,
        .setImageAccess = SetImageAccess,
        .resetImageAccess = ResetImageAccess,
        .setOnlineImageAccess = SetOnlineImageAccess,
        .resetOnlineImageAccess = ResetOnlineImageAccess,
        .setMediaPlayGestureAccess = SetMediaPlayGestureAccess,
        .resetMediaPlayGestureAccess = ResetMediaPlayGestureAccess,
        .setMediaOptions = SetMediaOptions,
        .resetMediaOptions = ResetMediaOptions,
        .setOnPageEnd = SetOnPageEnd,
        .resetOnPageEnd = ResetOnPageEnd,
        .setOnPageBegin = SetOnPageBegin,
        .resetOnPageBegin = ResetOnPageBegin,
        .setOnProgressChange = SetOnProgressChange,
        .resetOnProgressChange = ResetOnProgressChange,
        .setOnTitleReceive = SetOnTitleReceive,
        .resetOnTitleReceive = ResetOnTitleReceive,
        .setOnDownloadStart = SetOnDownloadStart,
        .resetOnDownloadStart = ResetOnDownloadStart,
        .setJavaScriptOnDocumentStart = SetJavaScriptOnDocumentStart,
        .resetJavaScriptOnDocumentStart = ResetJavaScriptOnDocumentStart,
        .setJavaScriptOnDocumentEnd = SetJavaScriptOnDocumentEnd,
        .resetJavaScriptOnDocumentEnd = ResetJavaScriptOnDocumentEnd,
        .setCopyOptionMode = SetCopyOptionMode,
        .resetCopyOptionMode = ResetCopyOptionMode,
        .setRenderProcessNotResponding = SetRenderProcessNotResponding,
        .resetRenderProcessNotResponding = ResetRenderProcessNotResponding,
        .setOnPageVisibleCallBack = SetOnPageVisibleCallBack,
        .resetOnPageVisibleCallBack = ResetOnPageVisibleCallBack,
        .setOnRenderExitedCallBack = SetOnRenderExitedCallBack,
        .resetOnRenderExitedCallBack = ResetOnRenderExitedCallBack,
        .setBlockNetwork = SetBlockNetwork,
        .resetBlockNetwork = ResetBlockNetwork,
        .setOnResourceLoadCallBack = SetOnResourceLoadCallBack,
        .resetOnResourceLoadCallBack = ResetOnResourceLoadCallBack,
        .setOnRefreshAccessedHistoryCallBack = SetOnRefreshAccessedHistoryCallBack,
        .resetOnRefreshAccessedHistoryCallBack = ResetOnRefreshAccessedHistoryCallBack,
        .setOnNavigationEntryCommittedCallBack = SetOnNavigationEntryCommittedCallBack,
        .resetOnNavigationEntryCommittedCallBack = ResetOnNavigationEntryCommittedCallBack,
        .setOnSearchResultReceiveCallBack = SetOnSearchResultReceiveCallBack,
        .resetOnSearchResultReceiveCallBack = ResetOnSearchResultReceiveCallBack,
        .setOverScrollMode = SetOverScrollMode,
        .resetOverScrollMode = ResetOverScrollMode,
        .setOnTouchIconUrlReceivedCallBack = SetOnTouchIconUrlReceivedCallBack,
        .resetOnTouchIconUrlReceivedCallBack = ResetOnTouchIconUrlReceivedCallBack,
        .setOnRenderProcessRespondingCallBack = SetOnRenderProcessRespondingCallBack,
        .resetOnRenderProcessRespondingCallBack = ResetOnRenderProcessRespondingCallBack,
        .setOnWindowNew = SetOnWindowNew,
        .resetOnWindowNew = ResetOnWindowNew,
        .setOnGeolocationShow = SetOnGeolocationShow,
        .resetOnGeolocationShow = ResetOnGeolocationShow,
        .setOnPermissionRequest = SetOnPermissionRequest,
        .resetOnPermissionRequest = ResetOnPermissionRequest,
        .setOnScreenCaptureRequest = SetOnScreenCaptureRequest,
        .resetOnScreenCaptureRequest = ResetOnScreenCaptureRequest,
        .setOnFullScreenEnter = SetOnFullScreenEnter,
        .resetOnFullScreenEnter = ResetOnFullScreenEnter,
        .setOnWindowExit = SetOnWindowExit,
        .resetOnWindowExit = ResetOnWindowExit,
        .setOnAlertlCallBack = SetOnAlertlCallBack,
        .resetOnAlertlCallBack = ResetOnAlertlCallBack,
        .setOnConfirmCallBack = SetOnConfirmCallBack,
        .resetOnConfirmCallBack = ResetOnConfirmCallBack,
        .setOnPromptCallBack = SetOnPromptCallBack,
        .resetOnPromptCallBack = ResetOnPromptCallBack,
        .setOnShowFileSelector = SetOnShowFileSelector,
        .resetOnShowFileSelector = ResetOnShowFileSelector,
        .setOnContextMenuShow = SetOnContextMenuShow,
        .resetOnContextMenuShow = ResetOnContextMenuShow,
        .setOnSafeBrowsingCheckResultCallBack = SetOnSafeBrowsingCheckResultCallBack,
        .resetOnSafeBrowsingCheckResultCallBack = ResetOnSafeBrowsingCheckResultCallBack,
        .setWebNestedScrollExt = SetWebNestedScrollExt,
        .resetWebNestedScrollExt = ResetWebNestedScrollExt,
        .setOnInterceptKeyEventCallBack = SetOnInterceptKeyEventCallBack,
        .resetOnInterceptKeyEventCallBack = ResetOnInterceptKeyEventCallBack,
        .setOnErrorReceive = SetOnErrorReceive,
        .resetOnErrorReceive = ResetOnErrorReceive,
        .setOnLoadIntercept = SetOnLoadIntercept,
        .resetOnLoadIntercept = ResetOnLoadIntercept,
        .setOnHttpErrorReceive = SetOnHttpErrorReceive,
        .resetOnHttpErrorReceive = ResetOnHttpErrorReceive,
        .setOnOverrideUrlLoading = SetOnOverrideUrlLoading,
        .resetOnOverrideUrlLoading = ResetOnOverrideUrlLoading,
        .setOnHttpAuthRequest = SetOnHttpAuthRequest,
        .resetOnHttpAuthRequest = ResetOnHttpAuthRequest,
        .setOnConsole = SetOnConsole,
        .resetOnConsole = ResetOnConsole,
        .setOnSslErrorEvent = SetOnSslErrorEvent,
        .resetOnSslErrorEvent = ResetOnSslErrorEvent,
        .setOnDataResubmitted = SetOnDataResubmitted,
        .resetOnDataResubmitted = ResetOnDataResubmitted,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}

const CJUIWebModifier* GetCJUIWebModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUIWebModifier modifier = {
        .getWebController = nullptr,
        .getWebviewController = nullptr,
        .setWebOptions = nullptr,
        .setWebSrcResources = nullptr,
        .setJavaScriptAccess = SetJavaScriptAccess,
        .resetJavaScriptAccess = ResetJavaScriptAccess,
        .setFileAccessEnabled = SetFileAccessEnabled,
        .resetFileAccessEnabled = ResetFileAccessEnabled,
        .setDomStorageAccessEnabled = SetDomStorageAccessEnabled,
        .resetDomStorageAccessEnabled = ResetDomStorageAccessEnabled,
        .setMixedMode = SetMixedMode,
        .resetMixedMode = ResetMixedMode,
        .setZoomAccessEnabled = SetZoomAccessEnabled,
        .resetZoomAccessEnabled = ResetZoomAccessEnabled,
        .setCacheMode = SetCacheMode,
        .resetCacheMode = ResetCacheMode,
        .setDarkMode = SetDarkMode,
        .resetDarkMode = ResetDarkMode,
        .setMultiWindowAccessEnabled = SetMultiWindowAccessEnabled,
        .resetMultiWindowAccessEnabled = ResetMultiWindowAccessEnabled,
        .setAllowWindowOpenMethod = SetAllowWindowOpenMethod,
        .resetAllowWindowOpenMethod = ResetAllowWindowOpenMethod,
        .setKeyboardAvoidMode = SetKeyboardAvoidMode,
        .resetKeyboardAvoidMode = ResetKeyboardAvoidMode,
        .setOnControllerAttached = SetOnControllerAttached,
        .resetOnControllerAttached = ResetOnControllerAttached,
        .setVerticalScrollBarAccessEnabled = SetVerticalScrollBarAccessEnabled,
        .resetVerticalScrollBarAccessEnabled = ResetVerticalScrollBarAccessEnabled,
        .setHorizontalScrollBarAccessEnabled = SetHorizontalScrollBarAccessEnabled,
        .resetHorizontalScrollBarAccessEnabled = ResetHorizontalScrollBarAccessEnabled,
        .setTextZoomRatio = SetTextZoomRatio,
        .resetTextZoomRatio = ResetTextZoomRatio,
        .setInitialScale = SetInitialScale,
        .resetInitialScale = ResetInitialScale,
        .setOnScrollCallBack = SetOnScrollCallBack,
        .resetOnScrollCallBack = ResetOnScrollCallBack,
        .setOnOverScrollCallBack = SetOnOverScrollCallBack,
        .resetOnOverScrollCallBack = ResetOnOverScrollCallBack,
        .setOnScaleChangeCallBack = SetOnScaleChangeCallBack,
        .resetOnScaleChangeCallBack = ResetOnScaleChangeCallBack,
        .setOnRequestSelectedCallBack = SetOnRequestSelectedCallBack,
        .resetOnRequestSelectedCallBack = ResetOnRequestSelectedCallBack,
        .setOnContextMenuHideCallBack = SetOnContextMenuHideCallBack,
        .resetOnContextMenuHideCallBack = ResetOnContextMenuHideCallBack,
        .setGeolocationAccess = SetGeolocationAccess,
        .resetGeolocationAccess = ResetGeolocationAccess,
        .setDatabaseAccess = SetDatabaseAccess,
        .resetDatabaseAccess = ResetDatabaseAccess,
        .setOverviewModeAccess = SetOverviewModeAccess,
        .resetOverviewModeAccess = ResetOverviewModeAccess,
        .setForceDarkAccess = SetForceDarkAccess,
        .resetForceDarkAccess = ResetForceDarkAccess,
        .setPinchSmooth = SetPinchSmooth,
        .resetPinchSmooth = ResetPinchSmooth,
        .setMetaViewport = SetMetaViewport,
        .resetMetaViewport = ResetMetaViewport,
        .setEnableFollowSystemFontWeight = SetEnableFollowSystemFontWeight,
        .resetEnableFollowSystemFontWeight = ResetEnableFollowSystemFontWeight,
        .setEnableNativeEmbedMode = SetEnableNativeEmbedMode,
        .resetEnableNativeEmbedMode = ResetEnableNativeEmbedMode,
        .setMinFontSize = SetMinFontSize,
        .resetMinFontSize = ResetMinFontSize,
        .setDefaultFontSize = SetDefaultFontSize,
        .resetDefaultFontSize = ResetDefaultFontSize,
        .setDefaultFixedFontSize = SetDefaultFixedFontSize,
        .resetDefaultFixedFontSize = ResetDefaultFixedFontSize,
        .setMinLogicalFontSize = SetMinLogicalFontSize,
        .resetMinLogicalFontSize = ResetMinLogicalFontSize,
        .setWebStandardFont = SetWebStandardFont,
        .resetWebStandardFont = ResetWebStandardFont,
        .setWebSerifFont = SetWebSerifFont,
        .resetWebSerifFont = ResetWebSerifFont,
        .setWebSansSerifFont = SetWebSansSerifFont,
        .resetWebSansSerifFont = ResetWebSansSerifFont,
        .setWebFixedFont = SetWebFixedFont,
        .resetWebFixedFont = ResetWebFixedFont,
        .setWebFantasyFont = SetWebFantasyFont,
        .resetWebFantasyFont = ResetWebFantasyFont,
        .setWebCursiveFont = SetWebCursiveFont,
        .resetWebCursiveFont = ResetWebCursiveFont,
        .setLayoutMode = SetLayoutMode,
        .resetLayoutMode = ResetLayoutMode,
        .setOnNativeEmbedLifecycleChange = SetOnNativeEmbedLifecycleChange,
        .resetOnNativeEmbedLifecycleChange = ResetOnNativeEmbedLifecycleChange,
        .setOnNativeEmbedGestureEvent = SetOnNativeEmbedGestureEvent,
        .resetOnNativeEmbedGestureEvent = ResetOnNativeEmbedGestureEvent,
        .setRegisterNativeEmbedRule = SetRegisterNativeEmbedRule,
        .resetRegisterNativeEmbedRule = ResetRegisterNativeEmbedRule,
        .setNativeEmbedOptions = SetNativeEmbedOptions,
        .resetNativeEmbedOptions = ResetNativeEmbedOptions,
        .setOnFirstContentfulPaint = SetOnFirstContentfulPaint,
        .resetOnFirstContentfulPaint = ResetOnFirstContentfulPaint,
        .setOnAudioStateChanged = SetOnAudioStateChanged,
        .resetOnAudioStateChanged = ResetOnAudioStateChanged,
        .setOnFullScreenExit = SetOnFullScreenExit,
        .resetOnFullScreenExit = ResetOnFullScreenExit,
        .setImageAccess = SetImageAccess,
        .resetImageAccess = ResetImageAccess,
        .setOnlineImageAccess = SetOnlineImageAccess,
        .resetOnlineImageAccess = ResetOnlineImageAccess,
        .setMediaPlayGestureAccess = SetMediaPlayGestureAccess,
        .resetMediaPlayGestureAccess = ResetMediaPlayGestureAccess,
        .setMediaOptions = SetMediaOptions,
        .resetMediaOptions = ResetMediaOptions,
        .setOnPageEnd = SetOnPageEnd,
        .resetOnPageEnd = ResetOnPageEnd,
        .setOnPageBegin = SetOnPageBegin,
        .resetOnPageBegin = ResetOnPageBegin,
        .setOnProgressChange = SetOnProgressChange,
        .resetOnProgressChange = ResetOnProgressChange,
        .setOnTitleReceive = SetOnTitleReceive,
        .resetOnTitleReceive = ResetOnTitleReceive,
        .setOnDownloadStart = SetOnDownloadStart,
        .resetOnDownloadStart = ResetOnDownloadStart,
        .setJavaScriptOnDocumentStart = SetJavaScriptOnDocumentStart,
        .resetJavaScriptOnDocumentStart = ResetJavaScriptOnDocumentStart,
        .setJavaScriptOnDocumentEnd = SetJavaScriptOnDocumentEnd,
        .resetJavaScriptOnDocumentEnd = ResetJavaScriptOnDocumentEnd,
        .setCopyOptionMode = SetCopyOptionMode,
        .resetCopyOptionMode = ResetCopyOptionMode,
        .setRenderProcessNotResponding = SetRenderProcessNotResponding,
        .resetRenderProcessNotResponding = ResetRenderProcessNotResponding,
        .setOnPageVisibleCallBack = SetOnPageVisibleCallBack,
        .resetOnPageVisibleCallBack = ResetOnPageVisibleCallBack,
        .setOnRenderExitedCallBack = SetOnRenderExitedCallBack,
        .resetOnRenderExitedCallBack = ResetOnRenderExitedCallBack,
        .setBlockNetwork = SetBlockNetwork,
        .resetBlockNetwork = ResetBlockNetwork,
        .setOnResourceLoadCallBack = SetOnResourceLoadCallBack,
        .resetOnResourceLoadCallBack = ResetOnResourceLoadCallBack,
        .setOnRefreshAccessedHistoryCallBack = SetOnRefreshAccessedHistoryCallBack,
        .resetOnRefreshAccessedHistoryCallBack = ResetOnRefreshAccessedHistoryCallBack,
        .setOnNavigationEntryCommittedCallBack = SetOnNavigationEntryCommittedCallBack,
        .resetOnNavigationEntryCommittedCallBack = ResetOnNavigationEntryCommittedCallBack,
        .setOnSearchResultReceiveCallBack = SetOnSearchResultReceiveCallBack,
        .resetOnSearchResultReceiveCallBack = ResetOnSearchResultReceiveCallBack,
        .setOverScrollMode = SetOverScrollMode,
        .resetOverScrollMode = ResetOverScrollMode,
        .setOnTouchIconUrlReceivedCallBack = SetOnTouchIconUrlReceivedCallBack,
        .resetOnTouchIconUrlReceivedCallBack = ResetOnTouchIconUrlReceivedCallBack,
        .setOnRenderProcessRespondingCallBack = SetOnRenderProcessRespondingCallBack,
        .resetOnRenderProcessRespondingCallBack = ResetOnRenderProcessRespondingCallBack,
        .setOnWindowNew = SetOnWindowNew,
        .resetOnWindowNew = ResetOnWindowNew,
        .setOnGeolocationShow = SetOnGeolocationShow,
        .resetOnGeolocationShow = ResetOnGeolocationShow,
        .setOnPermissionRequest = SetOnPermissionRequest,
        .resetOnPermissionRequest = ResetOnPermissionRequest,
        .setOnScreenCaptureRequest = SetOnScreenCaptureRequest,
        .resetOnScreenCaptureRequest = ResetOnScreenCaptureRequest,
        .setOnFullScreenEnter = SetOnFullScreenEnter,
        .resetOnFullScreenEnter = ResetOnFullScreenEnter,
        .setOnWindowExit = SetOnWindowExit,
        .resetOnWindowExit = ResetOnWindowExit,
        .setOnAlertlCallBack = SetOnAlertlCallBack,
        .resetOnAlertlCallBack = ResetOnAlertlCallBack,
        .setOnConfirmCallBack = SetOnConfirmCallBack,
        .resetOnConfirmCallBack = ResetOnConfirmCallBack,
        .setOnPromptCallBack = SetOnPromptCallBack,
        .resetOnPromptCallBack = ResetOnPromptCallBack,
        .setOnShowFileSelector = SetOnShowFileSelector,
        .resetOnShowFileSelector = ResetOnShowFileSelector,
        .setOnContextMenuShow = SetOnContextMenuShow,
        .resetOnContextMenuShow = ResetOnContextMenuShow,
        .setOnSafeBrowsingCheckResultCallBack = SetOnSafeBrowsingCheckResultCallBack,
        .resetOnSafeBrowsingCheckResultCallBack = ResetOnSafeBrowsingCheckResultCallBack,
        .setWebNestedScrollExt = SetWebNestedScrollExt,
        .resetWebNestedScrollExt = ResetWebNestedScrollExt,
        .setOnInterceptKeyEventCallBack = SetOnInterceptKeyEventCallBack,
        .resetOnInterceptKeyEventCallBack = ResetOnInterceptKeyEventCallBack,
        .setOnErrorReceive = SetOnErrorReceive,
        .resetOnErrorReceive = ResetOnErrorReceive,
        .setOnLoadIntercept = SetOnLoadIntercept,
        .resetOnLoadIntercept = ResetOnLoadIntercept,
        .setOnHttpErrorReceive = SetOnHttpErrorReceive,
        .resetOnHttpErrorReceive = ResetOnHttpErrorReceive,
        .setOnOverrideUrlLoading = SetOnOverrideUrlLoading,
        .resetOnOverrideUrlLoading = ResetOnOverrideUrlLoading,
        .setOnHttpAuthRequest = SetOnHttpAuthRequest,
        .resetOnHttpAuthRequest = ResetOnHttpAuthRequest,
        .setOnConsole = SetOnConsole,
        .resetOnConsole = ResetOnConsole,
        .setOnSslErrorEvent = SetOnSslErrorEvent,
        .resetOnSslErrorEvent = ResetOnSslErrorEvent,
        .setOnDataResubmitted = SetOnDataResubmitted,
        .resetOnDataResubmitted = ResetOnDataResubmitted,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG