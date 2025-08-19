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

#include <climits>
#include <functional>

#include "core/components_ng/pattern/web/ani/web_model_static.h"

#ifdef ARKUI_CAPI_UNITTEST
#include "test/unittest/capi/stubs/mock_nweb_helper.h"
#include "test/unittest/capi/stubs/mock_web_pattern_static.h"
#else
#if !defined(ANDROID_PLATFORM) && !defined(IOS_PLATFORM)
#include "core/components_ng/pattern/web/ani/web_pattern_static.h"
#else
#include "core/components_ng/pattern/web/cross_platform/web_pattern.h"
#endif // !defined(ANDROID_PLATFORM) && !defined(IOS_PLATFORM)
#include "nweb_helper.h"
#endif // ARKUI_CAPI_UNITTEST

#include "core/components_ng/pattern/web/web_event_hub.h"

namespace OHOS::Ace::NG {
RefPtr<FrameNode> WebModelStatic::CreateFrameNode(int32_t nodeId)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPatternStatic>(); });
    auto webPatternStatic = frameNode->GetPattern<WebPatternStatic>();
    CHECK_NULL_RETURN(webPatternStatic, frameNode);
    webPatternStatic->SetNestedScrollExt(NestedScrollOptionsExt({
        .scrollUp = NestedScrollMode::SELF_FIRST,
        .scrollDown = NestedScrollMode::SELF_FIRST,
        .scrollLeft = NestedScrollMode::SELF_FIRST,
        .scrollRight = NestedScrollMode::SELF_FIRST,
    }));
    return frameNode;
}

void WebModelStatic::SetPopup(FrameNode* frameNode, bool isPopup, int32_t parentWebId)
{
    CHECK_NULL_VOID(frameNode);
    auto webPatternStatic = AceType::DynamicCast<WebPatternStatic>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPatternStatic);
    webPatternStatic->SetPopup(isPopup);
    webPatternStatic->SetParentNWebId(parentWebId);
    if (isPopup) {
        webPatternStatic->SetWebSrc("");
    }
}

void WebModelStatic::SetWebIdCallback(FrameNode* frameNode, std::function<void(int32_t)>&& webIdCallback)
{
    CHECK_NULL_VOID(frameNode);
    auto webPatternStatic = AceType::DynamicCast<WebPatternStatic>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPatternStatic);
    webPatternStatic->SetSetWebIdCallback(std::move(webIdCallback));
}

void WebModelStatic::SetHapPathCallback(FrameNode* frameNode, std::function<void(const std::string&)>&& hapPathCallback)
{
    CHECK_NULL_VOID(frameNode);
    auto webPatternStatic = AceType::DynamicCast<WebPatternStatic>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPatternStatic);
    webPatternStatic->SetSetHapPathCallback(std::move(hapPathCallback));
}

void WebModelStatic::SetWebSrc(FrameNode* frameNode, const std::optional<std::string>& webSrc)
{
    CHECK_NULL_VOID(frameNode);
    auto webPatternStatic = AceType::DynamicCast<WebPatternStatic>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPatternStatic);
    webPatternStatic->SetWebSrcStatic(webSrc.value_or(""));
}

void WebModelStatic::SetRenderMode(FrameNode* frameNode, const std::optional<RenderMode>& renderMode)
{
    CHECK_NULL_VOID(frameNode);
    auto webPatternStatic = AceType::DynamicCast<WebPatternStatic>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPatternStatic);
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
            TAG_LOGW(AceLogTag::ACE_WEB, "WebModelStatic::SetRenderMode unsupport debug render mode: %{public}s",
                debugRenderMode.c_str());
        }
        TAG_LOGI(AceLogTag::ACE_WEB, "WebModelStatic::SetRenderMode use debug render mode: %{public}s",
            debugRenderMode.c_str());
    }
    webPatternStatic->SetRenderMode(rm);
}

void WebModelStatic::SetIncognitoMode(FrameNode* frameNode, const std::optional<bool>& incognitoMode)
{
    CHECK_NULL_VOID(frameNode);
    auto webPatternStatic = AceType::DynamicCast<WebPatternStatic>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPatternStatic);
    webPatternStatic->SetIncognitoMode(incognitoMode.value_or(false));
}

void WebModelStatic::SetSharedRenderProcessToken(FrameNode* frameNode,
    const std::optional<std::string>& sharedRenderProcessToken)
{
    CHECK_NULL_VOID(frameNode);
    auto webPatternStatic = AceType::DynamicCast<WebPatternStatic>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPatternStatic);
    webPatternStatic->SetSharedRenderProcessToken(sharedRenderProcessToken.value_or(""));
}

void WebModelStatic::SetWebController(FrameNode* frameNode, const RefPtr<WebController>& webController)
{
    CHECK_NULL_VOID(frameNode);
    auto webPatternStatic = AceType::DynamicCast<WebPatternStatic>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPatternStatic);
    webPatternStatic->SetWebController(webController);
}

void WebModelStatic::SetOnLineImageAccessEnabled(FrameNode* frameNode, bool isOnLineImageAccessEnabled)
{
    CHECK_NULL_VOID(frameNode);
    auto webPatternStatic = AceType::DynamicCast<WebPatternStatic>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPatternStatic);
    webPatternStatic->UpdateOnLineImageAccessEnabled(isOnLineImageAccessEnabled);
}

void WebModelStatic::SetImageAccessEnabled(FrameNode* frameNode, bool isImageAccessEnabled)
{
    CHECK_NULL_VOID(frameNode);
    auto webPatternStatic = AceType::DynamicCast<WebPatternStatic>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPatternStatic);
    webPatternStatic->UpdateImageAccessEnabled(isImageAccessEnabled);
}

void WebModelStatic::SetGeolocationAccessEnabled(FrameNode* frameNode, bool isGeolocationAccessEnabled)
{
    CHECK_NULL_VOID(frameNode);
    auto webPatternStatic = AceType::DynamicCast<WebPatternStatic>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPatternStatic);
    webPatternStatic->UpdateGeolocationAccessEnabled(isGeolocationAccessEnabled);
}

void WebModelStatic::SetForceDarkAccess(FrameNode* frameNode, bool access)
{
    CHECK_NULL_VOID(frameNode);
    auto webPatternStatic = AceType::DynamicCast<WebPatternStatic>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPatternStatic);
    webPatternStatic->UpdateForceDarkAccess(access);
}

void WebModelStatic::SetOverviewModeAccessEnabled(FrameNode* frameNode, bool isOverviewModeAccessEnabled)
{
    CHECK_NULL_VOID(frameNode);
    auto webPatternStatic = AceType::DynamicCast<WebPatternStatic>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPatternStatic);
    webPatternStatic->UpdateOverviewModeAccessEnabled(isOverviewModeAccessEnabled);
}

void WebModelStatic::SetDatabaseAccessEnabled(FrameNode* frameNode, bool isDatabaseAccessEnabled)
{
    CHECK_NULL_VOID(frameNode);
    auto webPatternStatic = AceType::DynamicCast<WebPatternStatic>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPatternStatic);
    webPatternStatic->UpdateDatabaseAccessEnabled(isDatabaseAccessEnabled);
}

void WebModelStatic::SetMetaViewport(FrameNode* frameNode, bool enabled)
{
    CHECK_NULL_VOID(frameNode);
    auto webPatternStatic = AceType::DynamicCast<WebPatternStatic>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPatternStatic);
    webPatternStatic->UpdateMetaViewport(enabled);
}

void WebModelStatic::SetMediaPlayGestureAccess(FrameNode* frameNode, bool isNeedGestureAccess)
{
    CHECK_NULL_VOID(frameNode);
    auto webPatternStatic = AceType::DynamicCast<WebPatternStatic>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPatternStatic);
    webPatternStatic->UpdateMediaPlayGestureAccess(isNeedGestureAccess);
}

void WebModelStatic::SetOverlayScrollbarEnabled(FrameNode* frameNode, bool isEnabled)
{
    CHECK_NULL_VOID(frameNode);
    auto webPatternStatic = AceType::DynamicCast<WebPatternStatic>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPatternStatic);
    webPatternStatic->UpdateOverlayScrollbarEnabled(isEnabled);
}

void WebModelStatic::SetBlockNetwork(FrameNode* frameNode, bool isNetworkBlocked)
{
    CHECK_NULL_VOID(frameNode);
    auto webPatternStatic = AceType::DynamicCast<WebPatternStatic>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPatternStatic);
    webPatternStatic->UpdateBlockNetwork(isNetworkBlocked);
}

void WebModelStatic::SetHorizontalScrollBarAccessEnabled(FrameNode* frameNode, bool isHorizontalScrollBarAccessEnabled)
{
    CHECK_NULL_VOID(frameNode);
    auto webPatternStatic = AceType::DynamicCast<WebPatternStatic>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPatternStatic);
    webPatternStatic->UpdateHorizontalScrollBarAccessEnabled(isHorizontalScrollBarAccessEnabled);
}

void WebModelStatic::SetVerticalScrollBarAccessEnabled(FrameNode* frameNode, bool isVerticalScrollBarAccessEnabled)
{
    CHECK_NULL_VOID(frameNode);
    auto webPatternStatic = AceType::DynamicCast<WebPatternStatic>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPatternStatic);
    webPatternStatic->UpdateVerticalScrollBarAccessEnabled(isVerticalScrollBarAccessEnabled);
}

void WebModelStatic::SetPinchSmoothModeEnabled(FrameNode* frameNode, bool isPinchSmoothModeEnabled)
{
    CHECK_NULL_VOID(frameNode);
    auto webPatternStatic = AceType::DynamicCast<WebPatternStatic>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPatternStatic);
    webPatternStatic->UpdatePinchSmoothModeEnabled(isPinchSmoothModeEnabled);
}

void WebModelStatic::SetNativeEmbedModeEnabled(FrameNode* frameNode, bool isEmbedModeEnabled)
{
    CHECK_NULL_VOID(frameNode);
    auto webPatternStatic = AceType::DynamicCast<WebPatternStatic>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPatternStatic);
    webPatternStatic->UpdateNativeEmbedModeEnabled(isEmbedModeEnabled);
}

void WebModelStatic::SetTextAutosizing(FrameNode* frameNode, bool isTextAutosizing)
{
    CHECK_NULL_VOID(frameNode);
    auto webPatternStatic = AceType::DynamicCast<WebPatternStatic>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPatternStatic);
    webPatternStatic->UpdateTextAutosizing(isTextAutosizing);
}

void WebModelStatic::SetEnabledHapticFeedback(FrameNode* frameNode, bool isEnabled)
{
    CHECK_NULL_VOID(frameNode);
    auto webPatternStatic = AceType::DynamicCast<WebPatternStatic>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPatternStatic);
    webPatternStatic->UpdateEnabledHapticFeedback(isEnabled);
}

void WebModelStatic::SetOptimizeParserBudgetEnabled(FrameNode *frameNode, const std::optional<bool>& enable)
{
    (void)frameNode;
    (void)enable;
}

void WebModelStatic::SetEnableFollowSystemFontWeight(FrameNode *frameNode,
    const std::optional<bool>& enableFollowSystemFontWeight)
{
    (void)frameNode;
    (void)enableFollowSystemFontWeight;
}

void WebModelStatic::SetWebMediaAVSessionEnabled(FrameNode *frameNode, const std::optional<bool>& enable)
{
    (void)frameNode;
    (void)enable;
}

void WebModelStatic::JavaScriptOnDocumentStart(FrameNode* frameNode, const ScriptItems& scriptItems)
{
    CHECK_NULL_VOID(frameNode);
    auto webPatternStatic = AceType::DynamicCast<WebPatternStatic>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPatternStatic);
    webPatternStatic->JavaScriptOnDocumentStart(scriptItems);
}

void WebModelStatic::JavaScriptOnDocumentEnd(FrameNode* frameNode, const ScriptItems& scriptItems)
{
    CHECK_NULL_VOID(frameNode);
    auto webPatternStatic = AceType::DynamicCast<WebPatternStatic>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPatternStatic);
    webPatternStatic->JavaScriptOnDocumentEnd(scriptItems);
}

void WebModelStatic::JavaScriptOnHeadEnd(FrameNode *frameNode, const ScriptItems& scriptItems)
{
    (void)frameNode;
    (void)scriptItems;
}

void WebModelStatic::SetNativeEmbedOptions(FrameNode *frameNode, bool supportDefaultIntrinsicSize)
{
    (void)frameNode;
    (void)supportDefaultIntrinsicSize;
}

void WebModelStatic::SetMixedMode(FrameNode* frameNode, const std::optional<MixedModeContent>& mixedContentMode)
{
    CHECK_NULL_VOID(frameNode);
    auto webPatternStatic = AceType::DynamicCast<WebPatternStatic>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPatternStatic);
    if (mixedContentMode) {
        webPatternStatic->UpdateMixedMode(mixedContentMode.value());
    } else {
        webPatternStatic->ResetMixedMode();
    }
}

void WebModelStatic::SetCacheMode(FrameNode* frameNode, const std::optional<WebCacheMode>& cacheMode)
{
    CHECK_NULL_VOID(frameNode);
    auto webPatternStatic = AceType::DynamicCast<WebPatternStatic>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPatternStatic);
    if (cacheMode) {
        webPatternStatic->UpdateCacheMode(cacheMode.value());
    } else {
        webPatternStatic->ResetCacheMode();
    }
}

void WebModelStatic::SetDarkMode(FrameNode* frameNode, const std::optional<WebDarkMode>& mode)
{
    CHECK_NULL_VOID(frameNode);
    auto webPatternStatic = AceType::DynamicCast<WebPatternStatic>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPatternStatic);
    if (mode) {
        webPatternStatic->UpdateDarkMode(mode.value());
    } else {
        webPatternStatic->ResetDarkMode();
    }
}

void WebModelStatic::SetOverScrollMode(FrameNode* frameNode, const std::optional<OverScrollMode>& mode)
{
    CHECK_NULL_VOID(frameNode);
    auto webPatternStatic = AceType::DynamicCast<WebPatternStatic>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPatternStatic);
    if (mode) {
        webPatternStatic->UpdateOverScrollMode(mode.value());
    } else {
        webPatternStatic->ResetOverScrollMode();
    }
}

void WebModelStatic::SetLayoutMode(FrameNode* frameNode, const std::optional<WebLayoutMode>& mode)
{
    CHECK_NULL_VOID(frameNode);
    auto webPatternStatic = AceType::DynamicCast<WebPatternStatic>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPatternStatic);
    webPatternStatic->SetLayoutMode(mode.value_or(WebLayoutMode::NONE));
}

void WebModelStatic::SetCopyOptionMode(FrameNode* frameNode, const std::optional<CopyOptions>& mode)
{
    CHECK_NULL_VOID(frameNode);
    auto webPatternStatic = AceType::DynamicCast<WebPatternStatic>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPatternStatic);
    if (mode) {
        webPatternStatic->UpdateCopyOptionMode(static_cast<int32_t>(mode.value()));
    } else {
        webPatternStatic->ResetCopyOptionMode();
    }
}

void WebModelStatic::SetKeyboardAvoidMode(FrameNode* frameNode, const std::optional<WebKeyboardAvoidMode>& mode)
{
    CHECK_NULL_VOID(frameNode);
    auto webPatternStatic = AceType::DynamicCast<WebPatternStatic>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPatternStatic);
    if (mode) {
        webPatternStatic->UpdateKeyboardAvoidMode(mode.value());
    } else {
        webPatternStatic->ResetKeyboardAvoidMode();
    }
}

void WebModelStatic::SetAudioResumeInterval(FrameNode* frameNode, const std::optional<int32_t>& resumeInterval)
{
    CHECK_NULL_VOID(frameNode);
    auto webPatternStatic = AceType::DynamicCast<WebPatternStatic>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPatternStatic);
    if (resumeInterval) {
        webPatternStatic->UpdateAudioResumeInterval(resumeInterval.value());
    } else {
        webPatternStatic->ResetAudioResumeInterval();
    }
}

void WebModelStatic::SetAudioExclusive(FrameNode* frameNode, const std::optional<bool>& audioExclusive)
{
    CHECK_NULL_VOID(frameNode);
    auto webPatternStatic = AceType::DynamicCast<WebPatternStatic>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPatternStatic);
    if (audioExclusive) {
        webPatternStatic->UpdateAudioExclusive(audioExclusive.value());
    } else {
        webPatternStatic->ResetAudioExclusive();
    }
}

void WebModelStatic::SetBlurOnKeyboardHideMode(FrameNode* frameNode, const std::optional<BlurOnKeyboardHideMode>& mode)
{
    (void)frameNode;
    (void)mode;
}

void WebModelStatic::SetTextZoomRatio(FrameNode* frameNode, int32_t textZoomRatioNum)
{
    CHECK_NULL_VOID(frameNode);
    auto webPatternStatic = AceType::DynamicCast<WebPatternStatic>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPatternStatic);
    webPatternStatic->UpdateTextZoomRatio(textZoomRatioNum);
}

void WebModelStatic::InitialScale(FrameNode* frameNode, float scale)
{
    CHECK_NULL_VOID(frameNode);
    auto webPatternStatic = AceType::DynamicCast<WebPatternStatic>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPatternStatic);
    webPatternStatic->UpdateInitialScale(scale);
}

void WebModelStatic::SetUserAgent(FrameNode* frameNode, const std::string& userAgent)
{
    CHECK_NULL_VOID(frameNode);
    auto webPatternStatic = AceType::DynamicCast<WebPatternStatic>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPatternStatic);
    webPatternStatic->UpdateUserAgent(userAgent);
}

void WebModelStatic::SetWebStandardFont(FrameNode* frameNode, const std::string& standardFontFamily)
{
    CHECK_NULL_VOID(frameNode);
    auto webPatternStatic = AceType::DynamicCast<WebPatternStatic>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPatternStatic);
    webPatternStatic->UpdateWebStandardFont(standardFontFamily);
}

void WebModelStatic::SetWebSerifFont(FrameNode* frameNode, const std::string& serifFontFamily)
{
    CHECK_NULL_VOID(frameNode);
    auto webPatternStatic = AceType::DynamicCast<WebPatternStatic>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPatternStatic);
    webPatternStatic->UpdateWebSerifFont(serifFontFamily);
}

void WebModelStatic::SetWebSansSerifFont(FrameNode* frameNode, const std::string& sansSerifFontFamily)
{
    CHECK_NULL_VOID(frameNode);
    auto webPatternStatic = AceType::DynamicCast<WebPatternStatic>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPatternStatic);
    webPatternStatic->UpdateWebSansSerifFont(sansSerifFontFamily);
}

void WebModelStatic::SetWebFixedFont(FrameNode* frameNode, const std::string& fixedFontFamily)
{
    CHECK_NULL_VOID(frameNode);
    auto webPatternStatic = AceType::DynamicCast<WebPatternStatic>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPatternStatic);
    webPatternStatic->UpdateWebFixedFont(fixedFontFamily);
}

void WebModelStatic::SetWebFantasyFont(FrameNode* frameNode, const std::string& fantasyFontFamily)
{
    CHECK_NULL_VOID(frameNode);
    auto webPatternStatic = AceType::DynamicCast<WebPatternStatic>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPatternStatic);
    webPatternStatic->UpdateWebFantasyFont(fantasyFontFamily);
}

void WebModelStatic::SetWebCursiveFont(FrameNode* frameNode, const std::string& cursiveFontFamily)
{
    CHECK_NULL_VOID(frameNode);
    auto webPatternStatic = AceType::DynamicCast<WebPatternStatic>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPatternStatic);
    webPatternStatic->UpdateWebCursiveFont(cursiveFontFamily);
}

void WebModelStatic::SetDefaultFixedFontSize(FrameNode* frameNode, int32_t defaultFixedFontSize)
{
    CHECK_NULL_VOID(frameNode);
    auto webPatternStatic = AceType::DynamicCast<WebPatternStatic>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPatternStatic);
    webPatternStatic->UpdateDefaultFixedFontSize(defaultFixedFontSize);
}

void WebModelStatic::SetDefaultFontSize(FrameNode* frameNode, int32_t defaultFontSize)
{
    CHECK_NULL_VOID(frameNode);
    auto webPatternStatic = AceType::DynamicCast<WebPatternStatic>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPatternStatic);
    webPatternStatic->UpdateDefaultFontSize(defaultFontSize);
}

void WebModelStatic::SetMinFontSize(FrameNode* frameNode, int32_t minFontSize)
{
    CHECK_NULL_VOID(frameNode);
    auto webPatternStatic = AceType::DynamicCast<WebPatternStatic>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPatternStatic);
    webPatternStatic->UpdateMinFontSize(minFontSize);
}

void WebModelStatic::SetMinLogicalFontSize(FrameNode* frameNode, int32_t minLogicalFontSize)
{
    CHECK_NULL_VOID(frameNode);
    auto webPatternStatic = AceType::DynamicCast<WebPatternStatic>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPatternStatic);
    webPatternStatic->UpdateMinLogicalFontSize(minLogicalFontSize);
}

void WebModelStatic::SetDefaultTextEncodingFormat(FrameNode* frameNode, const std::string& textEncodingFormat)
{
    CHECK_NULL_VOID(frameNode);
    auto webPatternStatic = AceType::DynamicCast<WebPatternStatic>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPatternStatic);
    if (textEncodingFormat.empty()) {
        webPatternStatic->ResetDefaultTextEncodingFormat();
    } else {
        webPatternStatic->UpdateDefaultTextEncodingFormat(textEncodingFormat);
    }
}

void WebModelStatic::RegisterNativeEmbedRule(FrameNode* frameNode, const std::string& tag, const std::string& type)
{
    CHECK_NULL_VOID(frameNode);
    auto webPatternStatic = AceType::DynamicCast<WebPatternStatic>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPatternStatic);
    webPatternStatic->UpdateNativeEmbedRuleTag(tag);
    webPatternStatic->UpdateNativeEmbedRuleType(type);
}

void WebModelStatic::SetNativeVideoPlayerConfig(FrameNode* frameNode, bool enable, bool shouldOverlay)
{
    CHECK_NULL_VOID(frameNode);
    auto webPatternStatic = AceType::DynamicCast<WebPatternStatic>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPatternStatic);
    webPatternStatic->UpdateNativeVideoPlayerConfig(std::make_tuple(enable, shouldOverlay));
}

void WebModelStatic::SetNestedScrollExt(FrameNode* frameNode, const std::optional<NestedScrollOptionsExt>& nestedOpt)
{
    CHECK_NULL_VOID(frameNode);
    auto webPatternStatic = AceType::DynamicCast<WebPatternStatic>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPatternStatic);
    if (nestedOpt) {
        webPatternStatic->SetNestedScrollExt(nestedOpt.value());
    } else {
        NestedScrollOptionsExt defaultNestedOpt = {
            .scrollUp = NestedScrollMode::SELF_FIRST,
            .scrollDown = NestedScrollMode::SELF_FIRST,
            .scrollLeft = NestedScrollMode::SELF_FIRST,
            .scrollRight = NestedScrollMode::SELF_FIRST,
        };
        webPatternStatic->SetNestedScrollExt(defaultNestedOpt);
    }
}

void WebModelStatic::SetSelectionMenuOptions(FrameNode* frameNode, const WebMenuOptionsParam& webMenuOption)
{
    CHECK_NULL_VOID(frameNode);
    auto webPatternStatic = AceType::DynamicCast<WebPatternStatic>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPatternStatic);
    webPatternStatic->UpdateSelectionMenuOptions(std::move(webMenuOption));
}

void WebModelStatic::SetEditMenuOptions(FrameNode* frameNode, const NG::OnCreateMenuCallback&& onCreateMenuCallback,
    const NG::OnMenuItemClickCallback&& onMenuItemClick, const NG::OnPrepareMenuCallback&& onPrepareMenuCallback)
{
    CHECK_NULL_VOID(frameNode);
    auto webPatternStatic = AceType::DynamicCast<WebPatternStatic>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPatternStatic);
    webPatternStatic->UpdateEditMenuOptions(
        std::move(onCreateMenuCallback), std::move(onMenuItemClick), std::move(onPrepareMenuCallback));
}

void WebModelStatic::SetNewDragStyle(FrameNode* frameNode, bool isNewDragStyle)
{
    CHECK_NULL_VOID(frameNode);
    auto webPatternStatic = AceType::DynamicCast<WebPatternStatic>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPatternStatic);
    webPatternStatic->SetNewDragStyle(isNewDragStyle);
}

void WebModelStatic::SetPreviewSelectionMenu(
    FrameNode* frameNode, const std::shared_ptr<WebPreviewSelectionMenuParam>& param)
{
    CHECK_NULL_VOID(frameNode);
    auto webPatternStatic = AceType::DynamicCast<WebPatternStatic>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPatternStatic);
    webPatternStatic->SetPreviewSelectionMenu(param);
}

void WebModelStatic::SetOnPageFinish(FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto uiCallback = [func = callback](const std::shared_ptr<BaseEventInfo>& info) { func(info.get()); };
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnPageFinishedEvent(std::move(uiCallback));
}

void WebModelStatic::SetOnPageStart(FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto uiCallback = [func = callback](const std::shared_ptr<BaseEventInfo>& info) { func(info.get()); };
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnPageStartedEvent(std::move(uiCallback));
}

void WebModelStatic::SetOnProgressChange(FrameNode* frameNode,
    std::function<void(const BaseEventInfo* info)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto uiCallback = [func = callback](const std::shared_ptr<BaseEventInfo>& info) { func(info.get()); };
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnProgressChangeEvent(std::move(uiCallback));
}

void WebModelStatic::SetOnTitleReceive(FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto uiCallback = [func = callback](const std::shared_ptr<BaseEventInfo>& info) { func(info.get()); };
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnTitleReceiveEvent(std::move(uiCallback));
}

void WebModelStatic::SetOnGeolocationHide(
    FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto uiCallback = [func = callback](const std::shared_ptr<BaseEventInfo>& info) { func(info.get()); };
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnGeolocationHideEvent(std::move(uiCallback));
}

void WebModelStatic::SetOnGeolocationShow(
    FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto uiCallback = [func = callback](const std::shared_ptr<BaseEventInfo>& info) { func(info.get()); };
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnGeolocationShowEvent(std::move(uiCallback));
}

void WebModelStatic::SetOnRequestFocus(FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    WeakPtr<NG::FrameNode> weak = AceType::WeakClaim(frameNode);

    auto uiCallback = [func = callback, weak](const std::shared_ptr<BaseEventInfo>& info) {
        auto frameNode = weak.Upgrade();
        int32_t instanceId = INSTANCE_ID_UNDEFINED;
        if (frameNode) {
            instanceId = frameNode->GetInstanceId();
        } else {
            instanceId = Container::CurrentIdSafely();
        }
        ContainerScope scope(instanceId);
        auto context = PipelineBase::GetCurrentContextSafelyWithCheck();
        CHECK_NULL_VOID(context);
#ifdef ARKUI_CAPI_UNITTEST
        func(info.get());
#else
        context->PostAsyncEvent([info, func]() { func(info.get()); }, "ArkUIWebRequestFocusCallback");
#endif // ARKUI_CAPI_UNITTEST
    };
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnRequestFocusEvent(std::move(uiCallback));
}

void WebModelStatic::SetOnCommonDialog(
    FrameNode* frameNode, std::function<bool(const BaseEventInfo* info)>&& callback, int dialogEventType)
{
    CHECK_NULL_VOID(frameNode);
    auto uiCallback = [func = callback](const std::shared_ptr<BaseEventInfo>& info) -> bool {
        return func(info.get());
    };
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnCommonDialogEvent(std::move(uiCallback), static_cast<DialogEventType>(dialogEventType));
}

void WebModelStatic::SetOnConsoleLog(FrameNode* frameNode, std::function<bool(const BaseEventInfo* info)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto onConsole = [func = callback](const std::shared_ptr<BaseEventInfo>& info) -> bool {
        auto context = PipelineBase::GetCurrentContextSafelyWithCheck();
        CHECK_NULL_RETURN(context, false);
        bool result = false;
#ifdef ARKUI_CAPI_UNITTEST
        result = func(info.get());
#else
        context->PostSyncEvent([func, info, &result]() { result = func(info.get()); }, "ArkUIWebConsoleLogCallback");
#endif // ARKUI_CAPI_UNITTEST
        return result;
    };
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnConsoleEvent(std::move(onConsole));
}

void WebModelStatic::SetOnErrorReceive(FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto uiCallback = [func = callback](const std::shared_ptr<BaseEventInfo>& info) { func(info.get()); };
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnErrorReceiveEvent(std::move(uiCallback));
}

void WebModelStatic::SetOnHttpErrorReceive(
    FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto uiCallback = [func = callback](const std::shared_ptr<BaseEventInfo>& info) { func(info.get()); };
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnHttpErrorReceiveEvent(std::move(uiCallback));
}

void WebModelStatic::SetOnDownloadStart(FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto uiCallback = [func = callback](const std::shared_ptr<BaseEventInfo>& info) { func(info.get()); };
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnDownloadStartEvent(std::move(uiCallback));
}

void WebModelStatic::SetRefreshAccessedHistoryId(
    FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto uiCallback = [func = callback](const std::shared_ptr<BaseEventInfo>& info) { func(info.get()); };
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnRefreshAccessedHistoryEvent(std::move(uiCallback));
}

void WebModelStatic::SetOnUrlLoadIntercept(
    FrameNode* frameNode, std::function<bool(const BaseEventInfo* info)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto uiCallback = [func = callback](const std::shared_ptr<BaseEventInfo>& info) -> bool {
        return func(info.get());
    };
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnUrlLoadInterceptEvent(std::move(uiCallback));
}

void WebModelStatic::SetRenderExitedId(FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto uiCallback = [func = callback](const std::shared_ptr<BaseEventInfo>& info) { func(info.get()); };
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnRenderExitedEvent(std::move(uiCallback));
}

void WebModelStatic::SetOnFileSelectorShow(
    FrameNode* frameNode, std::function<bool(const BaseEventInfo* info)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto uiCallback = [func = callback](const std::shared_ptr<BaseEventInfo>& info) -> bool {
        return func(info.get());
    };
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnFileSelectorShowEvent(std::move(uiCallback));
}

void WebModelStatic::SetResourceLoadId(FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto uiCallback = [func = callback](const std::shared_ptr<BaseEventInfo>& info) { func(info.get()); };
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnResourceLoadEvent(std::move(uiCallback));
}

void WebModelStatic::SetOnFullScreenExit(
    FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto uiCallback = [func = callback](const std::shared_ptr<BaseEventInfo>& info) { func(info.get()); };
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnFullScreenExitEvent(std::move(uiCallback));
}

void WebModelStatic::SetOnFullScreenEnter(
    FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto uiCallback = [func = callback](const std::shared_ptr<BaseEventInfo>& info) { func(info.get()); };
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnFullScreenEnterEvent(std::move(uiCallback));
}

void WebModelStatic::SetScaleChangeId(FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto uiCallback = [func = callback](const std::shared_ptr<BaseEventInfo>& info) { func(info.get()); };
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnScaleChangeEvent(std::move(uiCallback));
}

void WebModelStatic::SetOnHttpAuthRequest(
    FrameNode* frameNode, std::function<bool(const BaseEventInfo* info)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto uiCallback = [func = callback](const std::shared_ptr<BaseEventInfo>& info) -> bool {
        return func(info.get());
    };
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnHttpAuthRequestEvent(std::move(uiCallback));
}

void WebModelStatic::SetOnInterceptRequest(
    FrameNode* frameNode, std::function<RefPtr<WebResponse>(const BaseEventInfo* info)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto uiCallback = [func = callback](const std::shared_ptr<BaseEventInfo>& info) -> RefPtr<WebResponse> {
        return func(info.get());
    };
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnInterceptRequestEvent(std::move(uiCallback));
}

void WebModelStatic::SetPermissionRequestEventId(
    FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto uiCallback = [func = callback](const std::shared_ptr<BaseEventInfo>& info) { func(info.get()); };
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnPermissionRequestEvent(std::move(uiCallback));
}

void WebModelStatic::SetScreenCaptureRequestEventId(
    FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto uiCallback = [func = callback](const std::shared_ptr<BaseEventInfo>& info) { func(info.get()); };
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnScreenCaptureRequestEvent(std::move(uiCallback));
}

void WebModelStatic::SetOnContextMenuShow(
    FrameNode* frameNode, std::function<bool(const BaseEventInfo* info)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto uiCallback = [func = callback](const std::shared_ptr<BaseEventInfo>& info) -> bool {
        return func(info.get());
    };
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnContextMenuShowEvent(std::move(uiCallback));
}

void WebModelStatic::SetOnContextMenuHide(
    FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto uiCallback = [func = callback](const std::shared_ptr<BaseEventInfo>& info) { func(info.get()); };
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnContextMenuHideEvent(std::move(uiCallback));
}

void WebModelStatic::SetSearchResultReceiveEventId(
    FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto uiCallback = [func = callback](const std::shared_ptr<BaseEventInfo>& info) { func(info.get()); };
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnSearchResultReceiveEvent(std::move(uiCallback));
}

void WebModelStatic::SetScrollId(FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto uiCallback = [func = callback](const std::shared_ptr<BaseEventInfo>& info) { func(info.get()); };
    CHECK_NULL_VOID(frameNode);
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnScrollEvent(std::move(uiCallback));
}

void WebModelStatic::SetOnSslErrorRequest(
    FrameNode* frameNode, std::function<bool(const BaseEventInfo* info)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto uiCallback = [func = callback](const std::shared_ptr<BaseEventInfo>& info) -> bool {
        return func(info.get());
    };
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnSslErrorRequestEvent(std::move(uiCallback));
}

void WebModelStatic::SetOnAllSslErrorRequest(
    FrameNode* frameNode, std::function<bool(const BaseEventInfo* info)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto uiCallback = [func = callback](const std::shared_ptr<BaseEventInfo>& info) -> bool {
        return func(info.get());
    };
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnAllSslErrorRequestEvent(std::move(uiCallback));
}

void WebModelStatic::SetOnSslSelectCertRequest(
    FrameNode* frameNode, std::function<bool(const BaseEventInfo* info)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto uiCallback = [func = callback](const std::shared_ptr<BaseEventInfo>& info) -> bool {
        return func(info.get());
    };
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnSslSelectCertRequestEvent(std::move(uiCallback));
}

void WebModelStatic::SetWindowNewEvent(
    FrameNode* frameNode, std::function<void(const std::shared_ptr<BaseEventInfo>& info)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnWindowNewEvent(std::move(callback));
}

void WebModelStatic::SetWindowExitEventId(
    FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto uiCallback = [func = callback](const std::shared_ptr<BaseEventInfo>& info) { func(info.get()); };
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnWindowExitEvent(std::move(uiCallback));
}

void WebModelStatic::SetOnInterceptKeyEventCallback(
    FrameNode* frameNode, std::function<bool(KeyEventInfo& keyEventInfo)>&& keyEventInfo)
{
    auto func = keyEventInfo;
    CHECK_NULL_VOID(frameNode);
    WeakPtr<NG::FrameNode> weak = AceType::WeakClaim(frameNode);
    auto onConsole = [func, weak](KeyEventInfo& keyEventInfo) -> bool {
        auto frameNode = weak.Upgrade();
        int32_t instanceId = INSTANCE_ID_UNDEFINED;
        if (frameNode) {
            instanceId = frameNode->GetInstanceId();
        } else {
            instanceId = Container::CurrentIdSafely();
        }
        ContainerScope scope(instanceId);
        auto context = PipelineBase::GetCurrentContextSafelyWithCheck();
        bool result = false;
        CHECK_NULL_RETURN(context, result);
#ifdef ARKUI_CAPI_UNITTEST
        result = func(keyEventInfo);
#else
        context->PostSyncEvent(
            [func, &keyEventInfo, &result]() { result = func(keyEventInfo); }, "ArkUIWebInterceptKeyEventCallback");
#endif // ARKUI_CAPI_UNITTEST
        return result;
    };
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnPreKeyEvent(std::move(onConsole));
}

void WebModelStatic::SetTouchIconUrlId(FrameNode* frameNode, OnWebAsyncFunc&& touchIconUrlId)
{
    CHECK_NULL_VOID(frameNode);
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnTouchIconUrlEvent(std::move(touchIconUrlId));
}

void WebModelStatic::SetFaviconReceivedId(FrameNode* frameNode, OnWebAsyncFunc&& faviconReceivedId)
{
    CHECK_NULL_VOID(frameNode);
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnFaviconReceivedEvent(std::move(faviconReceivedId));
}

void WebModelStatic::SetPageVisibleId(FrameNode* frameNode, OnWebAsyncFunc&& pageVisibleId)
{
    CHECK_NULL_VOID(frameNode);
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnPageVisibleEvent(std::move(pageVisibleId));
}

void WebModelStatic::SetOnDataResubmitted(
    FrameNode* frameNode, std::function<void(const std::shared_ptr<BaseEventInfo>& info)>&& dataResubmittedId)
{
    CHECK_NULL_VOID(frameNode);
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnDataResubmittedEvent(std::move(dataResubmittedId));
}

void WebModelStatic::SetAudioStateChangedId(
    FrameNode* frameNode, std::function<void(const std::shared_ptr<BaseEventInfo>& info)>&& audioStateChanged)
{
    CHECK_NULL_VOID(frameNode);
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnAudioStateChangedEvent(std::move(audioStateChanged));
}

void WebModelStatic::SetFirstContentfulPaintId(
    FrameNode* frameNode, std::function<void(const std::shared_ptr<BaseEventInfo>& info)>&& firstContentfulPaintId)
{
    CHECK_NULL_VOID(frameNode);
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnFirstContentfulPaintEvent(std::move(firstContentfulPaintId));
}

void WebModelStatic::SetFirstMeaningfulPaintId(
    FrameNode* frameNode, std::function<void(const std::shared_ptr<BaseEventInfo>& info)>&& firstMeaningfulPaintId)
{
    CHECK_NULL_VOID(frameNode);
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnFirstMeaningfulPaintEvent(std::move(firstMeaningfulPaintId));
}

void WebModelStatic::SetLargestContentfulPaintId(
    FrameNode* frameNode, std::function<void(const std::shared_ptr<BaseEventInfo>& info)>&& largestContentfulPaintId)
{
    CHECK_NULL_VOID(frameNode);
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnLargestContentfulPaintEvent(std::move(largestContentfulPaintId));
}

void WebModelStatic::SetOnLoadIntercept(FrameNode* frameNode, std::function<bool(const BaseEventInfo* info)>&& сallback)
{
    CHECK_NULL_VOID(frameNode);
    auto uiCallback = [func = сallback](const std::shared_ptr<BaseEventInfo>& info) -> bool {
        return func(info.get());
    };
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnLoadInterceptEvent(std::move(uiCallback));
}

void WebModelStatic::SetOnControllerAttached(FrameNode* frameNode, std::function<void()>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto webPatternStatic = AceType::DynamicCast<WebPatternStatic>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPatternStatic);
    webPatternStatic->SetOnControllerAttachedCallback(std::move(callback));
}

void WebModelStatic::SetOverScrollId(FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto uiCallback = [func = callback](const std::shared_ptr<BaseEventInfo>& info) { func(info.get()); };
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnOverScrollEvent(std::move(uiCallback));
}

void WebModelStatic::SetSafeBrowsingCheckResultId(FrameNode* frameNode,
    std::function<void(const std::shared_ptr<BaseEventInfo>& info)>&& safeBrowsingCheckResultId)
{
    CHECK_NULL_VOID(frameNode);
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnSafeBrowsingCheckResultEvent(std::move(safeBrowsingCheckResultId));
}

void WebModelStatic::SetNavigationEntryCommittedId(FrameNode* frameNode,
    std::function<void(const std::shared_ptr<BaseEventInfo>& info)>&& navigationEntryCommittedId)
{
    CHECK_NULL_VOID(frameNode);
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnNavigationEntryCommittedEvent(std::move(navigationEntryCommittedId));
}

void WebModelStatic::SetIntelligentTrackingPreventionResultId(FrameNode* frameNode,
    std::function<void(const std::shared_ptr<BaseEventInfo>& info)>&& intelligentTrackingPreventionResultId)
{
    CHECK_NULL_VOID(frameNode);
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnIntelligentTrackingPreventionResultEvent(std::move(intelligentTrackingPreventionResultId));
}

void WebModelStatic::SetNativeEmbedLifecycleChangeId(
    FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto uiCallback = [func = callback](const std::shared_ptr<BaseEventInfo>& info) { func(info.get()); };
    CHECK_NULL_VOID(frameNode);
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnNativeEmbedLifecycleChangeEvent(std::move(uiCallback));
}

void WebModelStatic::SetNativeEmbedVisibilityChangeId(
    FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto uiCallback = [func = callback](const std::shared_ptr<BaseEventInfo>& info) { func(info.get()); };
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnNativeEmbedVisibilityChangeEvent(std::move(uiCallback));
}

void WebModelStatic::SetNativeEmbedGestureEventId(
    FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto uiCallback = [func = callback](const std::shared_ptr<BaseEventInfo>& info) { func(info.get()); };
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnNativeEmbedGestureEvent(std::move(uiCallback));
}

void WebModelStatic::SetOnOverrideUrlLoading(
    FrameNode* frameNode, std::function<bool(const BaseEventInfo* info)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto uiCallback = [func = callback](const std::shared_ptr<BaseEventInfo>& info) -> bool {
        return func(info.get());
    };
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnOverrideUrlLoadingEvent(std::move(uiCallback));
}

void WebModelStatic::SetRenderProcessNotRespondingId(
    FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto uiCallback = [func = callback](const std::shared_ptr<BaseEventInfo>& info) { func(info.get()); };
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnRenderProcessNotRespondingEvent(std::move(uiCallback));
}

void WebModelStatic::SetRenderProcessRespondingId(
    FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto uiCallback = [func = callback](const std::shared_ptr<BaseEventInfo>& info) { func(info.get()); };
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnRenderProcessRespondingEvent(std::move(uiCallback));
}

void WebModelStatic::SetViewportFitChangedId(
    FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto uiCallback = [func = callback](const std::shared_ptr<BaseEventInfo>& info) { func(info.get()); };
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnViewportFitChangedEvent(std::move(uiCallback));
}

void WebModelStatic::SetOnInterceptKeyboardAttach(
    FrameNode* frameNode, std::function<WebKeyboardOption(const BaseEventInfo* info)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto uiCallback = [func = callback](const std::shared_ptr<BaseEventInfo>& info) -> WebKeyboardOption {
        return func(info.get());
    };
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnInterceptKeyboardAttachEvent(std::move(uiCallback));
}

void WebModelStatic::SetAdsBlockedEventId(
    FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto uiCallback = [func = callback](const std::shared_ptr<BaseEventInfo>& info) { func(info.get()); };
    auto webEventHub = frameNode->GetOrCreateEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnAdsBlockedEvent(std::move(uiCallback));
}

void WebModelStatic::NotifyPopupWindowResultStatic(int32_t webId, bool result)
{
#if !defined(IOS_PLATFORM) && !defined(ANDROID_PLATFORM)
    if (webId != -1) {
        std::shared_ptr<OHOS::NWeb::NWeb> nweb = OHOS::NWeb::NWebHelper::Instance().GetNWeb(webId);
        if (nweb) {
            nweb->NotifyPopupWindowResult(result);
        }
    }
#endif
}

void WebModelStatic::SetJsEnabled(FrameNode* frameNode, bool isJsEnabled)
{
    CHECK_NULL_VOID(frameNode);
    auto webPatternStatic = AceType::DynamicCast<WebPatternStatic>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPatternStatic);
    webPatternStatic->UpdateJsEnabled(isJsEnabled);
}

void WebModelStatic::SetFileAccessEnabled(FrameNode* frameNode, bool isFileAccessEnabled)
{
    CHECK_NULL_VOID(frameNode);
    auto webPatternStatic = AceType::DynamicCast<WebPatternStatic>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPatternStatic);
    webPatternStatic->UpdateFileAccessEnabled(isFileAccessEnabled);
}

void WebModelStatic::SetDomStorageAccessEnabled(FrameNode* frameNode, bool isDomStorageAccessEnabled)
{
    CHECK_NULL_VOID(frameNode);
    auto webPatternStatic = AceType::DynamicCast<WebPatternStatic>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPatternStatic);
    webPatternStatic->UpdateDomStorageAccessEnabled(isDomStorageAccessEnabled);
}

void WebModelStatic::SetZoomAccessEnabled(FrameNode* frameNode, bool isZoomAccessEnabled)
{
    CHECK_NULL_VOID(frameNode);
    auto webPatternStatic = AceType::DynamicCast<WebPatternStatic>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPatternStatic);
    webPatternStatic->UpdateZoomAccessEnabled(isZoomAccessEnabled);
}

void WebModelStatic::SetMultiWindowAccessEnabled(FrameNode* frameNode, bool isMultiWindowAccessEnable)
{
    CHECK_NULL_VOID(frameNode);
    auto webPatternStatic = AceType::DynamicCast<WebPatternStatic>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPatternStatic);
    webPatternStatic->UpdateMultiWindowAccessEnabled(isMultiWindowAccessEnable);
}

void WebModelStatic::SetAllowWindowOpenMethod(FrameNode* frameNode, bool isAllowWindowOpenMethod)
{
    CHECK_NULL_VOID(frameNode);
    auto webPatternStatic = AceType::DynamicCast<WebPatternStatic>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPatternStatic);
    webPatternStatic->UpdateAllowWindowOpenMethod(isAllowWindowOpenMethod);
}
} // namespace OHOS::Ace::NG
