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
#ifndef CAPI_STUBS_MOCK_WEB_PATTERN_H
#define CAPI_STUBS_MOCK_WEB_PATTERN_H

#include "core/components/web/web_property.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_property.h"
#include "core/components_ng/pattern/scrollable/scrollable_properties.h"
#include "core/components_ng/pattern/web/web_event_hub.h"
#include "core/components_ng/pattern/web/web_model_ng.h"
#include "core/components_ng/pattern/web/web_pattern_property.h"

namespace OHOS::Ace::NG {
const std::string DEFAULT_WEB_TEXT_ENCODING_FORMAT = "UTF-8";

class WebPattern : public Pattern {
    DECLARE_ACE_TYPE(WebPattern, Pattern);
public:
    using SetWebDetachCallback = std::function<void(int32_t)>;
    using OnControllerAttachedCallback = std::function<void()>;
    using DefaultFileSelectorShowCallback = std::function<void(const std::shared_ptr<BaseEventInfo>&)>;
    WebPattern();
    ~WebPattern() override;

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override;

    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<WebEventHub>();
    }

    ACE_DEFINE_PROPERTY_GROUP(WebProperty, WebPatternProperty);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, JsEnabled, bool);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, FileAccessEnabled, bool);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, OnLineImageAccessEnabled, bool);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, DomStorageAccessEnabled, bool);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, ImageAccessEnabled, bool);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, ZoomAccessEnabled, bool);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, GeolocationAccessEnabled, bool);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, ForceDarkAccess, bool);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, OverviewModeAccessEnabled, bool);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, DatabaseAccessEnabled, bool);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, MetaViewport, bool);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, MediaPlayGestureAccess, bool);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, MultiWindowAccessEnabled, bool);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, OverlayScrollbarEnabled, bool);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, WebMediaAVSessionEnabled, bool);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, BlockNetwork, bool);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, HorizontalScrollBarAccessEnabled, bool);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, VerticalScrollBarAccessEnabled, bool);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, PinchSmoothModeEnabled, bool);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, AllowWindowOpenMethod, bool);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, NativeEmbedModeEnabled, bool);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, TextAutosizing, bool);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, EnabledHapticFeedback, bool);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, IntrinsicSizeEnabled, bool);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, OptimizeParserBudgetEnabled, bool);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, EnableFollowSystemFontWeight, bool);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, MixedMode, MixedModeContent);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, CacheMode, WebCacheMode);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, DarkMode, WebDarkMode);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, OverScrollMode, int32_t);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, CopyOptionMode, int32_t);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, AudioResumeInterval, int32_t);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, AudioExclusive, bool);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, KeyboardAvoidMode, WebKeyboardAvoidMode);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, TextZoomRatio, int32_t);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, InitialScale, float);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, UserAgent, std::string);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, WebStandardFont, std::string);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, WebSerifFont, std::string);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, WebSansSerifFont, std::string);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, WebFixedFont, std::string);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, WebFantasyFont, std::string);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, WebCursiveFont, std::string);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, DefaultFixedFontSize, int32_t);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, DefaultFontSize, int32_t);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, MinFontSize, int32_t);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, MinLogicalFontSize, int32_t);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, BlurOnKeyboardHideMode, int32_t);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, DefaultTextEncodingFormat, std::string);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, NativeEmbedRuleTag, std::string);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, NativeEmbedRuleType, std::string);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, EnableDataDetector, bool);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, CssDisplayChangeEnabled, bool);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, BypassVsyncCondition, WebBypassVsyncCondition);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, AudioSessionType, WebAudioSessionType);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, BlankScreenDetectionConfig, BlankScreenDetectionConfig);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, RotateRenderEffect, WebRotateEffect);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, ForceEnableZoom, bool);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, BackToTop, bool);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, EnableSelectedDataDetector, bool);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, ZoomControlAccess, bool);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, GestureFocusMode, GestureFocusMode);
    using NativeVideoPlayerConfigType = std::tuple<bool, bool>;
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, NativeVideoPlayerConfig, NativeVideoPlayerConfigType);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, SelectionMenuOptions, WebMenuOptionsParam);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, EnableImageAnalyzer, bool);

    void SetWebSrc(const std::string &webSrc);
    void SetWebSrcStatic(const std::string &webSrc);
    void SetWebData(const std::string& webData);
    const std::optional<std::string>& GetWebData() const
    {
        return webData_;
    }
    void SetIncognitoMode(bool incognitoMode);
    void SetSharedRenderProcessToken(const std::string& sharedRenderProcessToken);
    void SetNestedScrollExt(NestedScrollOptionsExt const& nestedScroll);
    void SetRenderMode(RenderMode);
    void SetLayoutMode(WebLayoutMode mode);

    void JavaScriptOnDocumentStart(const ScriptItems&);
    void JavaScriptOnDocumentEnd(const ScriptItems&);
    void JavaScriptOnDocumentStartByOrder(const ScriptItems& scriptItems,
        const ScriptRegexItems& scriptRegexItems, const ScriptItemsByOrder& scriptItemsByOrder) {}
    void JavaScriptOnDocumentEndByOrder(const ScriptItems& scriptItems,
        const ScriptRegexItems& scriptRegexItems, const ScriptItemsByOrder& scriptItemsByOrder) {}
    void JavaScriptOnHeadReadyByOrder(const ScriptItems& scriptItems,
        const ScriptRegexItems& scriptRegexItems, const ScriptItemsByOrder& scriptItemsByOrder) {}

    void SetWebController(const RefPtr<WebController>& webController);
    RefPtr<WebController> GetWebController() const;

    void SetNewDragStyle(bool isNewDragStyle)
    {
        isNewDragStyle_ = isNewDragStyle;
    }

    void SetPreviewSelectionMenu(const std::shared_ptr<WebPreviewSelectionMenuParam>& param) {}
    void SetDefaultFileSelectorShowCallback(DefaultFileSelectorShowCallback&& Callback) {}

    void SetOnControllerAttachedCallback(OnControllerAttachedCallback&& callback);
    OnControllerAttachedCallback GetOnControllerAttachedCallback();
    void SetSetWebIdCallback(std::function<void(int32_t)>&& SetIdCallback) {}
    void SetSetHapPathCallback(std::function<void(const std::string&)>&& callback) {}
    void UpdateEditMenuOptions(const NG::OnCreateMenuCallback&& onCreateMenuCallback,
        const NG::OnMenuItemClickCallback&& onMenuItemClick, const NG::OnPrepareMenuCallback&& onPrepareMenuCallback)
    {
        onCreateMenuCallback_ = std::move(onCreateMenuCallback);
        onMenuItemClick_ = std::move(onMenuItemClick);
    }
    void OnUpdateOnCreateMenuCallback(SelectOverlayInfo& selectInfo)
    {
        selectInfo.onCreateCallback.onCreateMenuCallback = onCreateMenuCallback_;
        selectInfo.onCreateCallback.onMenuItemClick = onMenuItemClick_;
    }

    void SetSetWebDetachCallback(SetWebDetachCallback&& callback) {}
    void SetEmulateTouchFromMouseEvent(bool emulateTouchFromMouseEvent) {}
    void UpdateDataDetectorConfig(const TextDetectConfig& config) {}
    void SetJsProxyCallback(JsProxyCallback&& jsProxyCallback) {}

private:
    std::string GetMixedModeAsString() const;
    std::string GetCacheModeAsString() const;
    std::string GetDarkModeAsString() const;
    std::string GetOverScrollModeAsString() const;
    std::string GetMetaViewportAsString() const;
    std::string GetLayoutModeAsString() const;
    std::string GetInitialScaleAsString() const;
    std::string GetCopyOptionModeAsString() const;
    std::string GetKeyboardAvoidModeAsString() const;
    std::string GetEnabledHapticFeedbackAsString() const;
    std::string GetBlockNetworkAsString() const;
    std::string GetMinLogicalFontSizeAsString() const;
    std::string GetDefaultFixedFontSizeAsString() const;
    std::string GetDefaultTextEncodingFormatAsString() const;
    std::string GetHorizontalScrollBarAccessEnabledAsString() const;
    std::string GetVerticalScrollBarAccessEnabledAsString() const;
    std::string GetNestedScrollModeAsString(const NestedScrollMode& scrollMode) const;

    void BoolWebPropertiesToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const;

    void NestedScrollExtToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const;
    void NativeVideoPlayerConfigToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const;
    void NativeEmbedRuleToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const;
    void MediaOptionsToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const;

    void OnJsEnabledUpdate(bool) {}
    void OnFileAccessEnabledUpdate(bool) {}
    void OnOnLineImageAccessEnabledUpdate(bool) {}
    void OnDomStorageAccessEnabledUpdate(bool) {}
    void OnImageAccessEnabledUpdate(bool) {}
    void OnZoomAccessEnabledUpdate(bool) {}
    void OnGeolocationAccessEnabledUpdate(bool) {}
    void OnForceDarkAccessUpdate(bool) {}
    void OnOverviewModeAccessEnabledUpdate(bool) {}
    void OnDatabaseAccessEnabledUpdate(bool) {}
    void OnMetaViewportUpdate(bool) {}
    void OnMediaPlayGestureAccessUpdate(bool) {}
    void OnMultiWindowAccessEnabledUpdate(bool) {}
    void OnOverlayScrollbarEnabledUpdate(bool) {}
    void OnBlockNetworkUpdate(bool) {}
    void OnHorizontalScrollBarAccessEnabledUpdate(bool) {}
    void OnVerticalScrollBarAccessEnabledUpdate(bool) {}
    void OnPinchSmoothModeEnabledUpdate(bool) {}
    void OnAllowWindowOpenMethodUpdate(bool) {}
    void OnNativeEmbedModeEnabledUpdate(bool) {}
    void OnTextAutosizingUpdate(bool) {}
    void OnSmoothDragResizeEnabledUpdate(bool) {}
    void OnEnabledHapticFeedbackUpdate(bool) {}
    void OnOptimizeParserBudgetEnabledUpdate(bool) {}
    void OnEnableFollowSystemFontWeightUpdate(bool) {}
    void OnMixedModeUpdate(MixedModeContent) {}
    void OnCacheModeUpdate(WebCacheMode) {}
    void OnDarkModeUpdate(WebDarkMode) {}
    void OnOverScrollModeUpdate(int) {}
    void OnCopyOptionModeUpdate(int) {}
    void OnKeyboardAvoidModeUpdate(WebKeyboardAvoidMode const&) {}
    void OnAudioResumeIntervalUpdate(int) {}
    void OnAudioExclusiveUpdate(bool) {}
    void OnTextZoomRatioUpdate(int) {}
    void OnInitialScaleUpdate(float) {}
    void OnUserAgentUpdate(const std::string&) {}
    void OnWebStandardFontUpdate(const std::string&) {}
    void OnWebSerifFontUpdate(const std::string&) {}
    void OnWebSansSerifFontUpdate(const std::string&) {}
    void OnWebFixedFontUpdate(const std::string&) {}
    void OnWebFantasyFontUpdate(const std::string&) {}
    void OnWebCursiveFontUpdate(const std::string&) {}
    void OnDefaultFixedFontSizeUpdate(int) {}
    void OnDefaultFontSizeUpdate(int) {}
    void OnMinFontSizeUpdate(int) {}
    void OnMinLogicalFontSizeUpdate(int) {}
    void OnDefaultTextEncodingFormatUpdate(const std::string&) {}
    void OnNativeEmbedRuleTagUpdate(const std::string&) {}
    void OnNativeEmbedRuleTypeUpdate(const std::string&) {}
    void OnNativeVideoPlayerConfigUpdate(std::tuple<bool, bool> const&) {}
    void OnSelectionMenuOptionsUpdate(const WebMenuOptionsParam& webMenuOption) {}
    void OnBlurOnKeyboardHideModeUpdate(int) {}
    void OnIntrinsicSizeEnabledUpdate(bool) {}
    void OnWebMediaAVSessionEnabledUpdate(bool) {}
    void OnEnableDataDetectorUpdate(bool enable) {}
    void OnCssDisplayChangeEnabledUpdate(bool value) {}
    void OnBypassVsyncConditionUpdate(WebBypassVsyncCondition condition) {}
    void OnAudioSessionTypeUpdate(WebAudioSessionType value) {}
    void OnBlankScreenDetectionConfigUpdate(const BlankScreenDetectionConfig &config) {}
    void OnRotateRenderEffectUpdate(WebRotateEffect effect) {}
    void OnForceEnableZoomUpdate(bool value) {}
    void OnBackToTopUpdate(bool isBackToTop) {}
    void OnEnableSelectedDataDetectorUpdate(bool enable) {}
    void OnZoomControlAccessUpdate(bool zoomControlAccess) {}
    void OnGestureFocusModeUpdate(GestureFocusMode mode) {}
    void OnEnableImageAnalyzerUpdate(bool isEnabled) {}

    WebLayoutMode layoutMode_ = WebLayoutMode::NONE;
    NestedScrollOptionsExt nestedScroll_ = {
        .scrollUp = NestedScrollMode::SELF_ONLY,
        .scrollDown = NestedScrollMode::SELF_ONLY,
        .scrollLeft = NestedScrollMode::SELF_ONLY,
        .scrollRight = NestedScrollMode::SELF_ONLY,
    };
    RefPtr<WebController> webController_;
    std::optional<std::string> webData_;
    bool isNewDragStyle_ = false;
    OnControllerAttachedCallback onControllerAttachedCallback_ = nullptr;
    OnCreateMenuCallback onCreateMenuCallback_ = nullptr;
    OnMenuItemClickCallback onMenuItemClick_ = nullptr;
};
} // namespace OHOS::Ace::NG
#endif // CAPI_STUBS_MOCK_WEB_PATTERN_H
