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
        .setOnContextMenuHideCallBack= SetOnContextMenuHideCallBack,
        .resetOnContextMenuHideCallBack= ResetOnContextMenuHideCallBack,
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
        .setOnContextMenuHideCallBack= SetOnContextMenuHideCallBack,
        .resetOnContextMenuHideCallBack= ResetOnContextMenuHideCallBack,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG