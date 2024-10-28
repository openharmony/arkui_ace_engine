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

#include "core/components_ng/pattern/web/web_model_ng.h"

#if !defined(ANDROID_PLATFORM) && !defined(IOS_PLATFORM)
#include "core/components_ng/pattern/web/web_pattern.h"
#else
#include "core/components_ng/pattern/web/cross_platform/web_pattern.h"
#endif

namespace OHOS::Ace::NG {
RefPtr<FrameNode> WebModelNG::CreateFrameNode(int32_t nodeId)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    auto webPattern = frameNode->GetPattern<WebPattern>();
    CHECK_NULL_RETURN(webPattern, frameNode);
    webPattern->SetNestedScrollExt(NestedScrollOptionsExt({
        .scrollUp = NestedScrollMode::SELF_FIRST,
        .scrollDown = NestedScrollMode::SELF_FIRST,
        .scrollLeft = NestedScrollMode::SELF_FIRST,
        .scrollRight = NestedScrollMode::SELF_FIRST,
    }));
    return frameNode;
}

void WebModelNG::SetWebSrc(FrameNode* frameNode, const std::optional<std::string>& webSrc)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = AceType::DynamicCast<WebPattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPattern);
    webPattern->SetWebSrc(webSrc.value_or(""));
}

void WebModelNG::SetRenderMode(FrameNode* frameNode, const std::optional<RenderMode>& renderMode)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = AceType::DynamicCast<WebPattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPattern);
    auto rm = RenderMode::ASYNC_RENDER;
    if (renderMode) {
        rm = renderMode.value();
    }
    std::string debugRenderMode = SystemProperties::GetWebDebugRenderMode();
    if (debugRenderMode != "none") {
        if (debugRenderMode == "async") {
            rm = RenderMode::ASYNC_RENDER;
        } else if (debugRenderMode == "sync") {
            rm = RenderMode::SYNC_RENDER;
        } else {
            TAG_LOGW(AceLogTag::ACE_WEB, "WebModelNG::SetRenderMode unsupport debug render mode: %{public}s",
                debugRenderMode.c_str());
        }
        TAG_LOGI(AceLogTag::ACE_WEB, "WebModelNG::SetRenderMode use debug render mode: %{public}s",
            debugRenderMode.c_str());
    }
    webPattern->SetRenderMode(rm);
}

void WebModelNG::SetIncognitoMode(FrameNode* frameNode, const std::optional<bool>& incognitoMode)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = AceType::DynamicCast<WebPattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPattern);
    webPattern->SetIncognitoMode(incognitoMode.value_or(false));
}

void WebModelNG::SetSharedRenderProcessToken(FrameNode* frameNode,
    const std::optional<std::string>& sharedRenderProcessToken)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = AceType::DynamicCast<WebPattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPattern);
    webPattern->SetSharedRenderProcessToken(sharedRenderProcessToken.value_or(""));
}

void WebModelNG::SetJsEnabled(FrameNode* frameNode, bool isJsEnabled)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = AceType::DynamicCast<WebPattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateJsEnabled(isJsEnabled);
}

void WebModelNG::SetFileAccessEnabled(FrameNode* frameNode, bool isFileAccessEnabled)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = AceType::DynamicCast<WebPattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateFileAccessEnabled(isFileAccessEnabled);
}

void WebModelNG::SetOnLineImageAccessEnabled(FrameNode* frameNode, bool isOnLineImageAccessEnabled)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = AceType::DynamicCast<WebPattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateOnLineImageAccessEnabled(isOnLineImageAccessEnabled);
}

void WebModelNG::SetDomStorageAccessEnabled(FrameNode* frameNode, bool isDomStorageAccessEnabled)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = AceType::DynamicCast<WebPattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateDomStorageAccessEnabled(isDomStorageAccessEnabled);
}

void WebModelNG::SetImageAccessEnabled(FrameNode* frameNode, bool isImageAccessEnabled)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = AceType::DynamicCast<WebPattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateImageAccessEnabled(isImageAccessEnabled);
}

void WebModelNG::SetZoomAccessEnabled(FrameNode* frameNode, bool isZoomAccessEnabled)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = AceType::DynamicCast<WebPattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateZoomAccessEnabled(isZoomAccessEnabled);
}

void WebModelNG::SetGeolocationAccessEnabled(FrameNode* frameNode, bool isGeolocationAccessEnabled)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = AceType::DynamicCast<WebPattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateGeolocationAccessEnabled(isGeolocationAccessEnabled);
}

void WebModelNG::SetForceDarkAccess(FrameNode* frameNode, bool access)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = AceType::DynamicCast<WebPattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateForceDarkAccess(access);
}

void WebModelNG::SetOverviewModeAccessEnabled(FrameNode* frameNode, bool isOverviewModeAccessEnabled)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = AceType::DynamicCast<WebPattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateOverviewModeAccessEnabled(isOverviewModeAccessEnabled);
}

void WebModelNG::SetDatabaseAccessEnabled(FrameNode* frameNode, bool isDatabaseAccessEnabled)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = AceType::DynamicCast<WebPattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateDatabaseAccessEnabled(isDatabaseAccessEnabled);
}

void WebModelNG::SetMetaViewport(FrameNode* frameNode, bool enabled)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = AceType::DynamicCast<WebPattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateMetaViewport(enabled);
}

void WebModelNG::SetMediaPlayGestureAccess(FrameNode* frameNode, bool isNeedGestureAccess)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = AceType::DynamicCast<WebPattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateMediaPlayGestureAccess(isNeedGestureAccess);
}

void WebModelNG::SetMultiWindowAccessEnabled(FrameNode* frameNode, bool isMultiWindowAccessEnable)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = AceType::DynamicCast<WebPattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateMultiWindowAccessEnabled(isMultiWindowAccessEnable);
}

void WebModelNG::SetOverlayScrollbarEnabled(FrameNode* frameNode, bool isEnabled)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = AceType::DynamicCast<WebPattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateOverlayScrollbarEnabled(isEnabled);
}

void WebModelNG::SetBlockNetwork(FrameNode* frameNode, bool isNetworkBlocked)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = AceType::DynamicCast<WebPattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateBlockNetwork(isNetworkBlocked);
}

void WebModelNG::SetHorizontalScrollBarAccessEnabled(FrameNode* frameNode, bool isHorizontalScrollBarAccessEnabled)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = AceType::DynamicCast<WebPattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateHorizontalScrollBarAccessEnabled(isHorizontalScrollBarAccessEnabled);
}

void WebModelNG::SetVerticalScrollBarAccessEnabled(FrameNode* frameNode, bool isVerticalScrollBarAccessEnabled)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = AceType::DynamicCast<WebPattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateVerticalScrollBarAccessEnabled(isVerticalScrollBarAccessEnabled);
}

void WebModelNG::SetPinchSmoothModeEnabled(FrameNode* frameNode, bool isPinchSmoothModeEnabled)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = AceType::DynamicCast<WebPattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdatePinchSmoothModeEnabled(isPinchSmoothModeEnabled);
}

void WebModelNG::SetAllowWindowOpenMethod(FrameNode* frameNode, bool isAllowWindowOpenMethod)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = AceType::DynamicCast<WebPattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateAllowWindowOpenMethod(isAllowWindowOpenMethod);
}

void WebModelNG::SetNativeEmbedModeEnabled(FrameNode* frameNode, bool isEmbedModeEnabled)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = AceType::DynamicCast<WebPattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateNativeEmbedModeEnabled(isEmbedModeEnabled);
}

void WebModelNG::SetTextAutosizing(FrameNode* frameNode, bool isTextAutosizing)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = AceType::DynamicCast<WebPattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateTextAutosizing(isTextAutosizing);
}

void WebModelNG::SetSmoothDragResizeEnabled(FrameNode* frameNode, bool isSmoothDragResizeEnabled)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = AceType::DynamicCast<WebPattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateSmoothDragResizeEnabled(isSmoothDragResizeEnabled);
}

void WebModelNG::SetEnabledHapticFeedback(FrameNode* frameNode, bool isEnabled)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = AceType::DynamicCast<WebPattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateEnabledHapticFeedback(isEnabled);
}

void WebModelNG::SetMixedMode(FrameNode* frameNode, const std::optional<MixedModeContent>& mixedContentMode)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = AceType::DynamicCast<WebPattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPattern);
    if (mixedContentMode) {
        webPattern->UpdateMixedMode(mixedContentMode.value());
    } else {
        webPattern->ResetMixedMode();
    }
}

void WebModelNG::SetCacheMode(FrameNode* frameNode, const std::optional<WebCacheMode>& cacheMode)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = AceType::DynamicCast<WebPattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPattern);
    if (cacheMode) {
        webPattern->UpdateCacheMode(cacheMode.value());
    } else {
        webPattern->ResetCacheMode();
    }
}

void WebModelNG::SetDarkMode(FrameNode* frameNode, const std::optional<WebDarkMode>& mode)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = AceType::DynamicCast<WebPattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPattern);
    if (mode) {
        webPattern->UpdateDarkMode(mode.value());
    } else {
        webPattern->ResetDarkMode();
    }
}

void WebModelNG::SetOverScrollMode(FrameNode* frameNode, const std::optional<OverScrollMode>& mode)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = AceType::DynamicCast<WebPattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPattern);
    if (mode) {
        webPattern->UpdateOverScrollMode(mode.value());
    } else {
        webPattern->ResetOverScrollMode();
    }
}

void WebModelNG::SetLayoutMode(FrameNode* frameNode, const std::optional<WebLayoutMode>& mode)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = AceType::DynamicCast<WebPattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPattern);
    webPattern->SetLayoutMode(mode.value_or(WebLayoutMode::NONE));
}

void WebModelNG::SetCopyOptionMode(FrameNode* frameNode, const std::optional<CopyOptions>& mode)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = AceType::DynamicCast<WebPattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPattern);
    if (mode) {
        webPattern->UpdateCopyOptionMode(static_cast<int32_t>(mode.value()));
    } else {
        webPattern->ResetCopyOptionMode();
    }
}

void WebModelNG::SetKeyboardAvoidMode(FrameNode* frameNode, const std::optional<WebKeyboardAvoidMode>& mode)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = AceType::DynamicCast<WebPattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPattern);
    if (mode) {
        webPattern->UpdateKeyboardAvoidMode(mode.value());
    } else {
        webPattern->ResetKeyboardAvoidMode();
    }
}

void WebModelNG::SetAudioResumeInterval(FrameNode* frameNode, const std::optional<int32_t>& resumeInterval)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = AceType::DynamicCast<WebPattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPattern);
    if (resumeInterval) {
        webPattern->UpdateAudioResumeInterval(resumeInterval.value());
    } else {
        webPattern->ResetAudioResumeInterval();
    }
}

void WebModelNG::SetAudioExclusive(FrameNode* frameNode, const std::optional<bool>& audioExclusive)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = AceType::DynamicCast<WebPattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPattern);
    if (audioExclusive) {
        webPattern->UpdateAudioExclusive(audioExclusive.value());
    } else {
        webPattern->ResetAudioExclusive();
    }
}

void WebModelNG::SetTextZoomRatio(FrameNode* frameNode, int32_t textZoomRatioNum)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = AceType::DynamicCast<WebPattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateTextZoomRatio(textZoomRatioNum);
}

void WebModelNG::InitialScale(FrameNode* frameNode, float scale)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = AceType::DynamicCast<WebPattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateInitialScale(scale);
}

void WebModelNG::SetUserAgent(FrameNode* frameNode, const std::string& userAgent)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = AceType::DynamicCast<WebPattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateUserAgent(userAgent);
}

void WebModelNG::SetWebStandardFont(FrameNode* frameNode, const std::string& standardFontFamily)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = AceType::DynamicCast<WebPattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateWebStandardFont(standardFontFamily);
}

void WebModelNG::SetWebSerifFont(FrameNode* frameNode, const std::string& serifFontFamily)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = AceType::DynamicCast<WebPattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateWebSerifFont(serifFontFamily);
}

void WebModelNG::SetWebSansSerifFont(FrameNode* frameNode, const std::string& sansSerifFontFamily)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = AceType::DynamicCast<WebPattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateWebSansSerifFont(sansSerifFontFamily);
}

void WebModelNG::SetWebFixedFont(FrameNode* frameNode, const std::string& fixedFontFamily)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = AceType::DynamicCast<WebPattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateWebFixedFont(fixedFontFamily);
}

void WebModelNG::SetWebFantasyFont(FrameNode* frameNode, const std::string& fantasyFontFamily)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = AceType::DynamicCast<WebPattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateWebFantasyFont(fantasyFontFamily);
}

void WebModelNG::SetWebCursiveFont(FrameNode* frameNode, const std::string& cursiveFontFamily)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = AceType::DynamicCast<WebPattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateWebCursiveFont(cursiveFontFamily);
}

void WebModelNG::SetDefaultFixedFontSize(FrameNode* frameNode, int32_t defaultFixedFontSize)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = AceType::DynamicCast<WebPattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateDefaultFixedFontSize(defaultFixedFontSize);
}

void WebModelNG::SetDefaultFontSize(FrameNode* frameNode, int32_t defaultFontSize)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = AceType::DynamicCast<WebPattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateDefaultFontSize(defaultFontSize);
}

void WebModelNG::SetMinFontSize(FrameNode* frameNode, int32_t minFontSize)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = AceType::DynamicCast<WebPattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateMinFontSize(minFontSize);
}

void WebModelNG::SetMinLogicalFontSize(FrameNode* frameNode, int32_t minLogicalFontSize)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = AceType::DynamicCast<WebPattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateMinLogicalFontSize(minLogicalFontSize);
}

void WebModelNG::SetDefaultTextEncodingFormat(FrameNode* frameNode, const std::string& textEncodingFormat)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = AceType::DynamicCast<WebPattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPattern);
    if (textEncodingFormat.empty()) {
        webPattern->ResetDefaultTextEncodingFormat();
    } else {
        webPattern->UpdateDefaultTextEncodingFormat(textEncodingFormat);
    }
}

void WebModelNG::RegisterNativeEmbedRule(FrameNode* frameNode, const std::string& tag, const std::string& type)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = AceType::DynamicCast<WebPattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateNativeEmbedRuleTag(tag);
    webPattern->UpdateNativeEmbedRuleType(type);
}

void WebModelNG::SetNativeVideoPlayerConfig(FrameNode* frameNode, bool enable, bool shouldOverlay)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = AceType::DynamicCast<WebPattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateNativeVideoPlayerConfig(std::make_tuple(enable, shouldOverlay));
}

void WebModelNG::JavaScriptOnDocumentStart(FrameNode* frameNode, const ScriptItems& scriptItems)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = AceType::DynamicCast<WebPattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPattern);
    webPattern->JavaScriptOnDocumentStart(scriptItems);
}

void WebModelNG::JavaScriptOnDocumentEnd(FrameNode* frameNode, const ScriptItems& scriptItems)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = AceType::DynamicCast<WebPattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPattern);
    webPattern->JavaScriptOnDocumentEnd(scriptItems);
}

void WebModelNG::SetNestedScrollExt(FrameNode* frameNode, const std::optional<NestedScrollOptionsExt>& nestedOpt)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = AceType::DynamicCast<WebPattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPattern);
    if (nestedOpt) {
        webPattern->SetNestedScrollExt(nestedOpt.value());
    } else {
        NestedScrollOptionsExt defaultNestedOpt = {
            .scrollUp = NestedScrollMode::SELF_FIRST,
            .scrollDown = NestedScrollMode::SELF_FIRST,
            .scrollLeft = NestedScrollMode::SELF_FIRST,
            .scrollRight = NestedScrollMode::SELF_FIRST,
        };
        webPattern->SetNestedScrollExt(defaultNestedOpt);
    }
}
} // namespace OHOS::Ace::NG