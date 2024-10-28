/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#include "core/components/web/web_property.h"
#include "core/components_ng/pattern/scrollable/scrollable_properties.h"

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_WEB_MOCK_WEB_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_WEB_MOCK_WEB_PATTERN_H

namespace OHOS::Ace::NG {
class WebPattern {
WebPattern();
void Backward();
void OnWebSrcUpdate();
void SetNestedScrollExt(NestedScrollOptionsExt const&);
void SetRenderMode(RenderMode);
void OnJsEnabledUpdate(bool);
void OnFileAccessEnabledUpdate(bool);
void OnOnLineImageAccessEnabledUpdate(bool);
void OnDomStorageAccessEnabledUpdate(bool);
void OnImageAccessEnabledUpdate(bool);
void OnZoomAccessEnabledUpdate(bool);
void OnGeolocationAccessEnabledUpdate(bool);
void OnForceDarkAccessUpdate(bool);
void OnOverviewModeAccessEnabledUpdate(bool);
void OnDatabaseAccessEnabledUpdate(bool);
void OnMetaViewportUpdate(bool);
void OnMediaPlayGestureAccessUpdate(bool);
void OnMultiWindowAccessEnabledUpdate(bool);
void OnOverlayScrollbarEnabledUpdate(bool);
void OnBlockNetworkUpdate(bool);
void OnHorizontalScrollBarAccessEnabledUpdate(bool);
void OnVerticalScrollBarAccessEnabledUpdate(bool);
void OnPinchSmoothModeEnabledUpdate(bool);
void OnAllowWindowOpenMethodUpdate(bool);
void OnNativeEmbedModeEnabledUpdate(bool);
void OnTextAutosizingUpdate(bool);
void OnSmoothDragResizeEnabledUpdate(bool);
void OnEnabledHapticFeedbackUpdate(bool);
void OnMixedModeUpdate(MixedModeContent);
void OnCacheModeUpdate(WebCacheMode);
void OnDarkModeUpdate(WebDarkMode);
void OnOverScrollModeUpdate(int);
void SetLayoutMode(WebLayoutMode);
void OnCopyOptionModeUpdate(int);
void OnKeyboardAvoidModeUpdate(WebKeyboardAvoidMode const&);
void OnAudioResumeIntervalUpdate(int);
void OnAudioExclusiveUpdate(bool);
void OnTextZoomRatioUpdate(int);
void OnInitialScaleUpdate(float);
void OnUserAgentUpdate(const std::string&);
void OnWebStandardFontUpdate(const std::string&);
void OnWebSerifFontUpdate(const std::string&);
void OnWebSansSerifFontUpdate(const std::string&);
void OnWebFixedFontUpdate(const std::string&);
void OnWebFantasyFontUpdate(const std::string&);
void OnWebCursiveFontUpdate(const std::string&);
void OnDefaultFixedFontSizeUpdate(int);
void OnDefaultFontSizeUpdate(int);
void OnMinFontSizeUpdate(int);
void OnMinLogicalFontSizeUpdate(int);
void OnDefaultTextEncodingFormatUpdate(const std::string&);
void OnNativeEmbedRuleTagUpdate(const std::string&);
void OnNativeEmbedRuleTypeUpdate(const std::string&);
void OnNativeVideoPlayerConfigUpdate(std::tuple<bool, bool> const&);
void JavaScriptOnDocumentStart(const ScriptItems&);
void JavaScriptOnDocumentEnd(const ScriptItems&);
};
} // namespace OHOS::Ace::NG
#endif