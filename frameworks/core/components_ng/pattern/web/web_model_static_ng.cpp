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

#include <climits>
#include <functional>

#include "core/components_ng/pattern/web/web_model_ng.h"

#ifdef ARKUI_CAPI_UNITTEST
#include "test/unittest/capi/stubs/mock_nweb_helper.h"
#include "test/unittest/capi/stubs/mock_web_pattern.h"
#else
#if !defined(ANDROID_PLATFORM) && !defined(IOS_PLATFORM)
#include "core/components_ng/pattern/web/web_pattern.h"
#else
#include "core/components_ng/pattern/web/cross_platform/web_pattern.h"
#endif // !defined(ANDROID_PLATFORM) && !defined(IOS_PLATFORM)
#include "nweb_helper.h"
#endif // ARKUI_CAPI_UNITTEST

#include "core/components_ng/pattern/web/web_event_hub.h"

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

void WebModelNG::SetWebIdCallback(FrameNode* frameNode, std::function<void(int32_t)>&& webIdCallback)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = AceType::DynamicCast<WebPattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPattern);
    webPattern->SetSetWebIdCallback(std::move(webIdCallback));
}

void WebModelNG::SetHapPathCallback(FrameNode* frameNode, std::function<void(const std::string&)>&& hapPathCallback)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = AceType::DynamicCast<WebPattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPattern);
    webPattern->SetSetHapPathCallback(std::move(hapPathCallback));
}

void WebModelNG::SetWebSrc(FrameNode* frameNode, const std::optional<std::string>& webSrc)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = AceType::DynamicCast<WebPattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPattern);
    webPattern->SetWebSrcStatic(webSrc.value_or(""));
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

void WebModelNG::SetWebController(FrameNode* frameNode, const RefPtr<WebController>& webController)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = AceType::DynamicCast<WebPattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPattern);
    webPattern->SetWebController(webController);
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

void WebModelNG::SetSelectionMenuOptions(FrameNode* frameNode, const WebMenuOptionsParam& webMenuOption)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = AceType::DynamicCast<WebPattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateSelectionMenuOptions(std::move(webMenuOption));
}

void WebModelNG::SetNewDragStyle(FrameNode* frameNode, bool isNewDragStyle)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = AceType::DynamicCast<WebPattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPattern);
    webPattern->SetNewDragStyle(isNewDragStyle);
}

void WebModelNG::SetPreviewSelectionMenu(
    FrameNode* frameNode, const std::shared_ptr<WebPreviewSelectionMenuParam>& param)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = AceType::DynamicCast<WebPattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPattern);
    webPattern->SetPreviewSelectionMenu(param);
}

void WebModelNG::SetOnPageFinish(FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto uiCallback = [func = callback](const std::shared_ptr<BaseEventInfo>& info) { func(info.get()); };
    auto webEventHub = frameNode->GetEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnPageFinishedEvent(std::move(uiCallback));
}

void WebModelNG::SetOnPageStart(FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto uiCallback = [func = callback](const std::shared_ptr<BaseEventInfo>& info) { func(info.get()); };
    auto webEventHub = frameNode->GetEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnPageStartedEvent(std::move(uiCallback));
}

void WebModelNG::SetOnProgressChange(FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto uiCallback = [func = callback](const std::shared_ptr<BaseEventInfo>& info) { func(info.get()); };
    auto webEventHub = frameNode->GetEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnProgressChangeEvent(std::move(uiCallback));
}

void WebModelNG::SetOnTitleReceive(FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto uiCallback = [func = callback](const std::shared_ptr<BaseEventInfo>& info) { func(info.get()); };
    auto webEventHub = frameNode->GetEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnTitleReceiveEvent(std::move(uiCallback));
}

void WebModelNG::SetOnGeolocationHide(
    FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto uiCallback = [func = callback](const std::shared_ptr<BaseEventInfo>& info) { func(info.get()); };
    auto webEventHub = frameNode->GetEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnGeolocationHideEvent(std::move(uiCallback));
}

void WebModelNG::SetOnGeolocationShow(
    FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto uiCallback = [func = callback](const std::shared_ptr<BaseEventInfo>& info) { func(info.get()); };
    auto webEventHub = frameNode->GetEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnGeolocationShowEvent(std::move(uiCallback));
}

void WebModelNG::SetOnRequestFocus(FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& callback)
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
    auto webEventHub = frameNode->GetEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnRequestFocusEvent(std::move(uiCallback));
}

void WebModelNG::SetOnCommonDialog(
    FrameNode* frameNode, std::function<bool(const BaseEventInfo* info)>&& callback, int dialogEventType)
{
    CHECK_NULL_VOID(frameNode);
    auto uiCallback = [func = callback](const std::shared_ptr<BaseEventInfo>& info) -> bool {
        return func(info.get());
    };
    auto webEventHub = frameNode->GetEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnCommonDialogEvent(std::move(uiCallback), static_cast<DialogEventType>(dialogEventType));
}

void WebModelNG::SetOnConsoleLog(FrameNode* frameNode, std::function<bool(const BaseEventInfo* info)>&& callback)
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
    auto webEventHub = frameNode->GetEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnConsoleEvent(std::move(onConsole));
}

void WebModelNG::SetOnErrorReceive(FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto uiCallback = [func = callback](const std::shared_ptr<BaseEventInfo>& info) { func(info.get()); };
    auto webEventHub = frameNode->GetEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnErrorReceiveEvent(std::move(uiCallback));
}

void WebModelNG::SetOnHttpErrorReceive(
    FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto uiCallback = [func = callback](const std::shared_ptr<BaseEventInfo>& info) { func(info.get()); };
    auto webEventHub = frameNode->GetEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnHttpErrorReceiveEvent(std::move(uiCallback));
}

void WebModelNG::SetOnDownloadStart(FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto uiCallback = [func = callback](const std::shared_ptr<BaseEventInfo>& info) { func(info.get()); };
    auto webEventHub = frameNode->GetEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnDownloadStartEvent(std::move(uiCallback));
}

void WebModelNG::SetRefreshAccessedHistoryId(
    FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto uiCallback = [func = callback](const std::shared_ptr<BaseEventInfo>& info) { func(info.get()); };
    auto webEventHub = frameNode->GetEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnRefreshAccessedHistoryEvent(std::move(uiCallback));
}

void WebModelNG::SetOnUrlLoadIntercept(
    FrameNode* frameNode, std::function<bool(const BaseEventInfo* info)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto uiCallback = [func = callback](const std::shared_ptr<BaseEventInfo>& info) -> bool {
        return func(info.get());
    };
    auto webEventHub = frameNode->GetEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnUrlLoadInterceptEvent(std::move(uiCallback));
}

void WebModelNG::SetRenderExitedId(FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto uiCallback = [func = callback](const std::shared_ptr<BaseEventInfo>& info) { func(info.get()); };
    auto webEventHub = frameNode->GetEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnRenderExitedEvent(std::move(uiCallback));
}

void WebModelNG::SetOnFileSelectorShow(
    FrameNode* frameNode, std::function<bool(const BaseEventInfo* info)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto uiCallback = [func = callback](const std::shared_ptr<BaseEventInfo>& info) -> bool {
        return func(info.get());
    };
    auto webEventHub = frameNode->GetEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnFileSelectorShowEvent(std::move(uiCallback));
}

void WebModelNG::SetResourceLoadId(FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto uiCallback = [func = callback](const std::shared_ptr<BaseEventInfo>& info) { func(info.get()); };
    auto webEventHub = frameNode->GetEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnResourceLoadEvent(std::move(uiCallback));
}

void WebModelNG::SetOnFullScreenExit(
    FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto uiCallback = [func = callback](const std::shared_ptr<BaseEventInfo>& info) { func(info.get()); };
    auto webEventHub = frameNode->GetEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnFullScreenExitEvent(std::move(uiCallback));
}

void WebModelNG::SetOnFullScreenEnter(
    FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto uiCallback = [func = callback](const std::shared_ptr<BaseEventInfo>& info) { func(info.get()); };
    auto webEventHub = frameNode->GetEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnFullScreenEnterEvent(std::move(uiCallback));
}

void WebModelNG::SetScaleChangeId(FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto uiCallback = [func = callback](const std::shared_ptr<BaseEventInfo>& info) { func(info.get()); };
    auto webEventHub = frameNode->GetEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnScaleChangeEvent(std::move(uiCallback));
}

void WebModelNG::SetOnHttpAuthRequest(
    FrameNode* frameNode, std::function<bool(const BaseEventInfo* info)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto uiCallback = [func = callback](const std::shared_ptr<BaseEventInfo>& info) -> bool {
        return func(info.get());
    };
    auto webEventHub = frameNode->GetEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnHttpAuthRequestEvent(std::move(uiCallback));
}

void WebModelNG::SetOnInterceptRequest(
    FrameNode* frameNode, std::function<RefPtr<WebResponse>(const BaseEventInfo* info)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto uiCallback = [func = callback](const std::shared_ptr<BaseEventInfo>& info) -> RefPtr<WebResponse> {
        return func(info.get());
    };
    auto webEventHub = frameNode->GetEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnInterceptRequestEvent(std::move(uiCallback));
}

void WebModelNG::SetPermissionRequestEventId(
    FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto uiCallback = [func = callback](const std::shared_ptr<BaseEventInfo>& info) { func(info.get()); };
    auto webEventHub = frameNode->GetEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnPermissionRequestEvent(std::move(uiCallback));
}

void WebModelNG::SetScreenCaptureRequestEventId(
    FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto uiCallback = [func = callback](const std::shared_ptr<BaseEventInfo>& info) { func(info.get()); };
    auto webEventHub = frameNode->GetEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnScreenCaptureRequestEvent(std::move(uiCallback));
}

void WebModelNG::SetOnContextMenuShow(
    FrameNode* frameNode, std::function<bool(const BaseEventInfo* info)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto uiCallback = [func = callback](const std::shared_ptr<BaseEventInfo>& info) -> bool {
        return func(info.get());
    };
    auto webEventHub = frameNode->GetEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnContextMenuShowEvent(std::move(uiCallback));
}

void WebModelNG::SetOnContextMenuHide(
    FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto uiCallback = [func = callback](const std::shared_ptr<BaseEventInfo>& info) { func(info.get()); };
    auto webEventHub = frameNode->GetEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnContextMenuHideEvent(std::move(uiCallback));
}

void WebModelNG::SetSearchResultReceiveEventId(
    FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto uiCallback = [func = callback](const std::shared_ptr<BaseEventInfo>& info) { func(info.get()); };
    auto webEventHub = frameNode->GetEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnSearchResultReceiveEvent(std::move(uiCallback));
}

void WebModelNG::SetScrollId(FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto uiCallback = [func = callback](const std::shared_ptr<BaseEventInfo>& info) { func(info.get()); };
    CHECK_NULL_VOID(frameNode);
    auto webEventHub = frameNode->GetEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnScrollEvent(std::move(uiCallback));
}

void WebModelNG::SetOnSslErrorRequest(
    FrameNode* frameNode, std::function<bool(const BaseEventInfo* info)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto uiCallback = [func = callback](const std::shared_ptr<BaseEventInfo>& info) -> bool {
        return func(info.get());
    };
    auto webEventHub = frameNode->GetEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnSslErrorRequestEvent(std::move(uiCallback));
}

void WebModelNG::SetOnAllSslErrorRequest(
    FrameNode* frameNode, std::function<bool(const BaseEventInfo* info)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto uiCallback = [func = callback](const std::shared_ptr<BaseEventInfo>& info) -> bool {
        return func(info.get());
    };
    auto webEventHub = frameNode->GetEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnAllSslErrorRequestEvent(std::move(uiCallback));
}

void WebModelNG::SetOnSslSelectCertRequest(
    FrameNode* frameNode, std::function<bool(const BaseEventInfo* info)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto uiCallback = [func = callback](const std::shared_ptr<BaseEventInfo>& info) -> bool {
        return func(info.get());
    };
    auto webEventHub = frameNode->GetEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnSslSelectCertRequestEvent(std::move(uiCallback));
}

void WebModelNG::SetWindowNewEvent(
    FrameNode* frameNode, std::function<void(const std::shared_ptr<BaseEventInfo>& info)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto webEventHub = frameNode->GetEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnWindowNewEvent(std::move(callback));
}

void WebModelNG::SetWindowExitEventId(
    FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto uiCallback = [func = callback](const std::shared_ptr<BaseEventInfo>& info) { func(info.get()); };
    auto webEventHub = frameNode->GetEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnWindowExitEvent(std::move(uiCallback));
}

void WebModelNG::SetOnInterceptKeyEventCallback(
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
    auto webEventHub = frameNode->GetEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnPreKeyEvent(std::move(onConsole));
}

void WebModelNG::SetTouchIconUrlId(FrameNode* frameNode, OnWebAsyncFunc&& touchIconUrlId)
{
    CHECK_NULL_VOID(frameNode);
    auto webEventHub = frameNode->GetEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnTouchIconUrlEvent(std::move(touchIconUrlId));
}

void WebModelNG::SetFaviconReceivedId(FrameNode* frameNode, OnWebAsyncFunc&& faviconReceivedId)
{
    CHECK_NULL_VOID(frameNode);
    auto webEventHub = frameNode->GetEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnFaviconReceivedEvent(std::move(faviconReceivedId));
}

void WebModelNG::SetPageVisibleId(FrameNode* frameNode, OnWebAsyncFunc&& pageVisibleId)
{
    CHECK_NULL_VOID(frameNode);
    auto webEventHub = frameNode->GetEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnPageVisibleEvent(std::move(pageVisibleId));
}

void WebModelNG::SetOnDataResubmitted(
    FrameNode* frameNode, std::function<void(const std::shared_ptr<BaseEventInfo>& info)>&& dataResubmittedId)
{
    CHECK_NULL_VOID(frameNode);
    auto webEventHub = frameNode->GetEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnDataResubmittedEvent(std::move(dataResubmittedId));
}

void WebModelNG::SetAudioStateChangedId(
    FrameNode* frameNode, std::function<void(const std::shared_ptr<BaseEventInfo>& info)>&& audioStateChanged)
{
    CHECK_NULL_VOID(frameNode);
    auto webEventHub = frameNode->GetEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnAudioStateChangedEvent(std::move(audioStateChanged));
}

void WebModelNG::SetFirstContentfulPaintId(
    FrameNode* frameNode, std::function<void(const std::shared_ptr<BaseEventInfo>& info)>&& firstContentfulPaintId)
{
    CHECK_NULL_VOID(frameNode);
    auto webEventHub = frameNode->GetEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnFirstContentfulPaintEvent(std::move(firstContentfulPaintId));
}

void WebModelNG::SetFirstMeaningfulPaintId(
    FrameNode* frameNode, std::function<void(const std::shared_ptr<BaseEventInfo>& info)>&& firstMeaningfulPaintId)
{
    CHECK_NULL_VOID(frameNode);
    auto webEventHub = frameNode->GetEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnFirstMeaningfulPaintEvent(std::move(firstMeaningfulPaintId));
}

void WebModelNG::SetLargestContentfulPaintId(
    FrameNode* frameNode, std::function<void(const std::shared_ptr<BaseEventInfo>& info)>&& largestContentfulPaintId)
{
    CHECK_NULL_VOID(frameNode);
    auto webEventHub = frameNode->GetEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnLargestContentfulPaintEvent(std::move(largestContentfulPaintId));
}

void WebModelNG::SetOnLoadIntercept(FrameNode* frameNode, std::function<bool(const BaseEventInfo* info)>&& сallback)
{
    CHECK_NULL_VOID(frameNode);
    auto uiCallback = [func = сallback](const std::shared_ptr<BaseEventInfo>& info) -> bool {
        return func(info.get());
    };
    auto webEventHub = frameNode->GetEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnLoadInterceptEvent(std::move(uiCallback));
}

void WebModelNG::SetOnControllerAttached(FrameNode* frameNode, std::function<void()>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = AceType::DynamicCast<WebPattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(webPattern);
    webPattern->SetOnControllerAttachedCallback(std::move(callback));
}

void WebModelNG::SetOverScrollId(FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto uiCallback = [func = callback](const std::shared_ptr<BaseEventInfo>& info) { func(info.get()); };
    auto webEventHub = frameNode->GetEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnOverScrollEvent(std::move(uiCallback));
}

void WebModelNG::SetSafeBrowsingCheckResultId(FrameNode* frameNode,
    std::function<void(const std::shared_ptr<BaseEventInfo>& info)>&& safeBrowsingCheckResultId)
{
    CHECK_NULL_VOID(frameNode);
    auto webEventHub = frameNode->GetEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnSafeBrowsingCheckResultEvent(std::move(safeBrowsingCheckResultId));
}

void WebModelNG::SetNavigationEntryCommittedId(FrameNode* frameNode,
    std::function<void(const std::shared_ptr<BaseEventInfo>& info)>&& navigationEntryCommittedId)
{
    CHECK_NULL_VOID(frameNode);
    auto webEventHub = frameNode->GetEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnNavigationEntryCommittedEvent(std::move(navigationEntryCommittedId));
}

void WebModelNG::SetIntelligentTrackingPreventionResultId(FrameNode* frameNode,
    std::function<void(const std::shared_ptr<BaseEventInfo>& info)>&& intelligentTrackingPreventionResultId)
{
    CHECK_NULL_VOID(frameNode);
    auto webEventHub = frameNode->GetEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnIntelligentTrackingPreventionResultEvent(std::move(intelligentTrackingPreventionResultId));
}

void WebModelNG::SetNativeEmbedLifecycleChangeId(
    FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto uiCallback = [func = callback](const std::shared_ptr<BaseEventInfo>& info) { func(info.get()); };
    CHECK_NULL_VOID(frameNode);
    auto webEventHub = frameNode->GetEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnNativeEmbedLifecycleChangeEvent(std::move(uiCallback));
}

void WebModelNG::SetNativeEmbedVisibilityChangeId(
    FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto uiCallback = [func = callback](const std::shared_ptr<BaseEventInfo>& info) { func(info.get()); };
    auto webEventHub = frameNode->GetEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnNativeEmbedVisibilityChangeEvent(std::move(uiCallback));
}

void WebModelNG::SetNativeEmbedGestureEventId(
    FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto uiCallback = [func = callback](const std::shared_ptr<BaseEventInfo>& info) { func(info.get()); };
    auto webEventHub = frameNode->GetEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnNativeEmbedGestureEvent(std::move(uiCallback));
}

void WebModelNG::SetOnOverrideUrlLoading(
    FrameNode* frameNode, std::function<bool(const BaseEventInfo* info)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto uiCallback = [func = callback](const std::shared_ptr<BaseEventInfo>& info) -> bool {
        return func(info.get());
    };
    auto webEventHub = frameNode->GetEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnOverrideUrlLoadingEvent(std::move(uiCallback));
}

void WebModelNG::SetRenderProcessNotRespondingId(
    FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto uiCallback = [func = callback](const std::shared_ptr<BaseEventInfo>& info) { func(info.get()); };
    auto webEventHub = frameNode->GetEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnRenderProcessNotRespondingEvent(std::move(uiCallback));
}

void WebModelNG::SetRenderProcessRespondingId(
    FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto uiCallback = [func = callback](const std::shared_ptr<BaseEventInfo>& info) { func(info.get()); };
    auto webEventHub = frameNode->GetEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnRenderProcessRespondingEvent(std::move(uiCallback));
}

void WebModelNG::SetViewportFitChangedId(
    FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto uiCallback = [func = callback](const std::shared_ptr<BaseEventInfo>& info) { func(info.get()); };
    auto webEventHub = frameNode->GetEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnViewportFitChangedEvent(std::move(uiCallback));
}

void WebModelNG::SetOnInterceptKeyboardAttach(
    FrameNode* frameNode, std::function<WebKeyboardOption(const BaseEventInfo* info)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto uiCallback = [func = callback](const std::shared_ptr<BaseEventInfo>& info) -> WebKeyboardOption {
        return func(info.get());
    };
    auto webEventHub = frameNode->GetEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnInterceptKeyboardAttachEvent(std::move(uiCallback));
}

void WebModelNG::SetAdsBlockedEventId(
    FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto uiCallback = [func = callback](const std::shared_ptr<BaseEventInfo>& info) { func(info.get()); };
    auto webEventHub = frameNode->GetEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnAdsBlockedEvent(std::move(uiCallback));
}

void WebModelNG::NotifyPopupWindowResultStatic(int32_t webId, bool result)
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
} // namespace OHOS::Ace::NG
