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
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG