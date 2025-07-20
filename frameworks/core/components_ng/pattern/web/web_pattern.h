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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_WEB_WEB_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_WEB_WEB_PATTERN_H

#include <optional>
#include <string>
#include <tuple>
#include <utility>

#include "base/memory/referenced.h"
#include "base/thread/cancelable_callback.h"
#include "base/utils/utils.h"
#include "base/geometry/axis.h"
#include "base/view_data/hint_to_type_wrap.h"
#include "core/common/ai/data_detector_mgr.h"
#include "core/common/ai/data_detector_adapter.h"
#include "core/common/recorder/web_event_recorder.h"
#include "core/common/udmf/unified_data.h"
#include "core/components/common/layout/constants.h"
#include "core/components/dialog/dialog_properties.h"
#include "core/components/dialog/dialog_theme.h"
#include "core/components/web/web_event.h"
#include "core/components/web/web_property.h"
#include "core/components_ng/gestures/recognizers/pan_recognizer.h"
#include "core/components_ng/manager/select_overlay/select_overlay_manager.h"
#include "core/components_ng/manager/select_overlay/select_overlay_proxy.h"
#include "core/components_ng/manager/select_overlay/selection_host.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/scrollable/nestable_scroll_container.h"
#include "core/components_ng/pattern/web/touch_event_listener.h"
#include "core/components_ng/pattern/web/web_accessibility_property.h"
#include "core/components_ng/pattern/web/web_context_select_overlay.h"
#include "core/components_ng/pattern/web/web_event_hub.h"
#include "core/components_ng/pattern/web/web_layout_algorithm.h"
#include "core/components_ng/pattern/web/web_paint_property.h"
#include "core/components_ng/pattern/web/web_pattern_property.h"
#include "core/components_ng/pattern/web/web_paint_method.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/render/adapter/rosen_render_context.h"
#include "core/components_ng/render/render_surface.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/gestures/pinch_gesture.h"
#include "core/components_ng/pattern/select_overlay/magnifier.h"
#include "core/components_ng/pattern/select_overlay/magnifier_controller.h"
#include "core/components_ng/pattern/web/web_data_detector_adapter.h"
#include "ui/rs_surface_node.h"
#include "core/components_ng/pattern/web/web_select_overlay.h"

namespace OHOS::Ace {
class WebDelegateObserver;
class ImageAnalyzerManager;
}

namespace OHOS::NWeb {
    class NWebQuickMenuParams;
    class NWebQuickMenuCallback;
    class NWebTouchHandleState;
    class NWebCursorInfo;
    class NWebSelectPopupMenuParam;
    class NWebDateTimeChooser;
    class NWebDateTimeSuggestion;
    class NWebSelectPopupMenuCallback;
    class NWebDateTimeChooserCallback;
    class NWebAccessibilityNodeInfo;
    class NWebMessage;
    class NWebKeyEvent;
    class NWebSelectMenuBound;
    class NWebUpdateScrollUpdateData;
    class NWebNestedScrollUpdateDataImpl;
    enum class CursorType;
}
namespace OHOS::Ace::NG {
class WebAccessibilityChildTreeCallback;
class ViewDataCommon;
class TransitionalNodeInfo;

namespace {

struct MouseClickInfo {
    double x = -1;
    double y = -1;
    TimeStamp start;
};

struct TouchInfo {
    double x = -1;
    double y = -1;
    int32_t id = -1;
};
} // namespace

enum class WebInfoType : int32_t {
    TYPE_MOBILE,
    TYPE_TABLET,
    TYPE_2IN1,
    TYPE_UNKNOWN
};

struct PipInfo {
    uint32_t mainWindowId;
    int delegateId;
    int childId;
    int frameRoutingId;
    int width;
    int height;
};

using CursorStyleInfo = std::tuple<OHOS::NWeb::CursorType, std::shared_ptr<OHOS::NWeb::NWebCursorInfo>>;
class WebPattern : public NestableScrollContainer,
                   public TextBase,
                   public Magnifier,
                   public Recorder::WebEventRecorder {
    DECLARE_ACE_TYPE(WebPattern, NestableScrollContainer, TextBase, Magnifier, Recorder::WebEventRecorder);

public:
    using SetWebIdCallback = std::function<void(int32_t)>;
    using SetWebDetachCallback = std::function<void(int32_t)>;
    using SetHapPathCallback = std::function<void(const std::string&)>;
    using JsProxyCallback = std::function<void()>;
    using OnControllerAttachedCallback = std::function<void()>;
    using PermissionClipboardCallback = std::function<void(const std::shared_ptr<BaseEventInfo>&)>;
    using OnOpenAppLinkCallback = std::function<void(const std::shared_ptr<BaseEventInfo>&)>;
    using SetFaviconCallback = std::function<void(const std::shared_ptr<BaseEventInfo>&)>;
    using DefaultFileSelectorShowCallback = std::function<void(const std::shared_ptr<BaseEventInfo>&)>;
    using WebNodeInfoCallback = const std::function<void(std::shared_ptr<JsonValue>& jsonNodeArray, int32_t webId)>;
    using TextBlurCallback = std::function<void(int64_t, const std::string)>;
    using WebComponentClickCallback = std::function<void(int64_t, const std::string)>;
    WebPattern();
    WebPattern(const std::string& webSrc, const RefPtr<WebController>& webController,
               RenderMode type = RenderMode::ASYNC_RENDER, bool incognitoMode = false,
			   const std::string& sharedRenderProcessToken = "");
    WebPattern(const std::string& webSrc, const SetWebIdCallback& setWebIdCallback,
               RenderMode type = RenderMode::ASYNC_RENDER, bool incognitoMode = false,
			   const std::string& sharedRenderProcessToken = "");

    ~WebPattern() override;

    enum class VkState {
        VK_NONE,
        VK_SHOW,
        VK_HIDE
    };

    enum class WebAccessibilityType : int32_t {
        ID = 0,
        SEL_START,
        SEL_END,
        INPUT_TYPE,
        LIVE_REGION,
        HINT,
        CONTENT,
        ERROR,
        CHILD_IDS,
        PARENT_ID,
        GRID_ROWS,
        GRID_COLS,
        GRID_SEL_MODE,
        GRID_ITEM_ROW,
        GRID_ITEM_ROW_SPAN,
        GRID_ITEM_COL,
        GRID_ITEM_COL_SPAN,
        PAGE_ID,
        RECTX,
        RECTY,
        RECT_WIDTH,
        RECT_HEIGHT,
        HEADING,
        CHECKED,
        EDITABLE,
        ENABLED,
        FOCUSED,
        SELECTED,
        CHECKABLE,
        CLICKABLE,
        FOCUSABLE,
        SCROLLABLE,
        PASSWORD,
        VISIBLE,
        PLURAL_LINE,
        POPUP,
        DELETABLE,
        FOCUS,
        NODE_TAG,
    };

    RefPtr<NodePaintMethod> CreateNodePaintMethod() override;

    bool IsAtomicNode() const override
    {
        return true;
    }

    bool NeedSoftKeyboard() const override;

    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<WebEventHub>();
    }

    RefPtr<AccessibilityProperty> CreateAccessibilityProperty() override
    {
        return MakeRefPtr<WebAccessibilityProperty>();
    }


    void OnModifyDone() override;

    void DumpViewDataPageNode(RefPtr<ViewDataWrap> viewDataWrap, bool needsRecordData = false) override;

    void NotifyFillRequestSuccess(RefPtr<ViewDataWrap> viewDataWrap,
        RefPtr<PageNodeInfoWrap> nodeWrap, AceAutoFillType autoFillType) override;

    void NotifyFillRequestFailed(int32_t errCode, const std::string& fillContent = "", bool isPopup = false) override;

    Color GetDefaultBackgroundColor();

    void SetWebSrc(const std::string& webSrc)
    {
        if (webSrc_ != webSrc_) {
            OnWebSrcUpdate();
            webSrc_ = webSrc;
        }
        if (webPaintProperty_) {
            webPaintProperty_->SetWebPaintData(webSrc);
        }
    }

    const std::optional<std::string>& GetWebSrc() const
    {
        return webSrc_;
    }

    void SetPopup(bool popup)
    {
        isPopup_ = popup;
    }

    void SetParentNWebId(int32_t parentNWebId)
    {
        parentNWebId_ = parentNWebId;
    }

    void SetWebData(const std::string& webData)
    {
        if (webData_ != webData) {
            webData_ = webData;
            OnWebDataUpdate();
        }
        if (webPaintProperty_) {
            webPaintProperty_->SetWebPaintData(webData);
        }
    }

    const std::optional<std::string>& GetWebData() const
    {
        return webData_;
    }

    void SetCustomScheme(const std::string& scheme)
    {
        customScheme_ = scheme;
    }

    const std::optional<std::string>& GetCustomScheme() const
    {
        return customScheme_;
    }

    void SetWebController(const RefPtr<WebController>& webController)
    {
        webController_ = webController;
    }

    RefPtr<WebController> GetWebController() const
    {
        return webController_;
    }

    void SetSetWebIdCallback(SetWebIdCallback&& SetIdCallback)
    {
        setWebIdCallback_ = std::move(SetIdCallback);
    }

    SetWebIdCallback GetSetWebIdCallback() const
    {
        return setWebIdCallback_;
    }

    void SetSetWebDetachCallback(SetWebDetachCallback&& callback)
    {
        setWebDetachCallback_ = std::move(callback);
    }

    SetWebDetachCallback GetSetWebDetachCallback() const
    {
        return setWebDetachCallback_;
    }

    void SetPermissionClipboardCallback(PermissionClipboardCallback&& Callback)
    {
        permissionClipboardCallback_ = std::move(Callback);
    }

    void SetDefaultFileSelectorShowCallback(DefaultFileSelectorShowCallback&& Callback)
    {
        defaultFileSelectorShowCallback_ = std::move(Callback);
    }

    DefaultFileSelectorShowCallback GetDefaultFileSelectorShowCallback()
    {
        return defaultFileSelectorShowCallback_;
    }

    PermissionClipboardCallback GetPermissionClipboardCallback() const
    {
        return permissionClipboardCallback_;
    }

    void SetOnOpenAppLinkCallback(OnOpenAppLinkCallback&& callback)
    {
        onOpenAppLinkCallback_ = std::move(callback);
    }

    OnOpenAppLinkCallback GetOnOpenAppLinkCallback() const
    {
        return onOpenAppLinkCallback_;
    }

    void SetFaviconFunction(SetFaviconCallback&& callback)
    {
        setFaviconCallback_ = std::move(callback);
    }

    SetFaviconCallback GetSetFaviconFunction() const
    {
        return setFaviconCallback_;
    }

    void SetRenderMode(RenderMode renderMode);

    RenderMode GetRenderMode()
    {
        return renderMode_;
    }

    void SetIncognitoMode(bool incognitoMode)
    {
        incognitoMode_ = incognitoMode;
    }

    bool GetIncognitoMode() const
    {
        return incognitoMode_;
    }

    void SetSharedRenderProcessToken(const std::string& sharedRenderProcessToken)
    {
        sharedRenderProcessToken_ = sharedRenderProcessToken;
    }

    const std::optional<std::string>& GetSharedRenderProcessToken() const
    {
        return sharedRenderProcessToken_;
    }

    void SetOnControllerAttachedCallback(OnControllerAttachedCallback&& callback)
    {
        onControllerAttachedCallback_ = std::move(callback);
    }

    OnControllerAttachedCallback GetOnControllerAttachedCallback()
    {
        return onControllerAttachedCallback_;
    }

    void SetSetHapPathCallback(SetHapPathCallback&& callback)
    {
        setHapPathCallback_ = std::move(callback);
    }

    SetHapPathCallback GetSetHapPathCallback() const
    {
        return setHapPathCallback_;
    }

    void SetJsProxyCallback(JsProxyCallback&& jsProxyCallback)
    {
        jsProxyCallback_ = std::move(jsProxyCallback);
    }

    void CallJsProxyCallback()
    {
        if (jsProxyCallback_) {
            jsProxyCallback_();
        }
    }

    RefPtr<WebEventHub> GetWebEventHub();

    FocusPattern GetFocusPattern() const override
    {
        FocusPattern focusPattern = { FocusType::NODE, true, FocusStyleType::FORCE_NONE };
        focusPattern.SetIsFocusActiveWhenFocused(true);
        return focusPattern;
    }

    RefPtr<PaintProperty> CreatePaintProperty() override
    {
        if (!webPaintProperty_) {
            webPaintProperty_ = MakeRefPtr<WebPaintProperty>();
            if (!webPaintProperty_) {
            }
        }
        return webPaintProperty_;
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<WebLayoutAlgorithm>();
    }

    bool BetweenSelectedPosition(const Offset& globalOffset) override
    {
        return false;
    }

    int32_t GetDragRecordSize() override
    {
        return 1;
    }

    /**
     *  NestableScrollContainer implementations
     */
    Axis GetAxis() const override
    {
        return axis_;
    }
    ScrollResult HandleScroll(float offset, int32_t source, NestedState state, float velocity = 0.f) override;
    ScrollResult HandleScroll(RefPtr<NestableScrollContainer> parent, float offset, int32_t source, NestedState state);
    bool HandleScrollVelocity(float velocity, const RefPtr<NestableScrollContainer>& child = nullptr) override;
    bool HandleScrollVelocity(RefPtr<NestableScrollContainer> parent, float velocity);
    void OnScrollStartRecursive(WeakPtr<NestableScrollContainer> child, float position, float velocity = 0.f) override;
    void OnScrollStartRecursive(float position);
    void OnScrollEndRecursive(const std::optional<float>& velocity) override;
    void OnAttachToBuilderNode(NodeStatus nodeStatus) override;
    void GetParentAxis();
    RefPtr<NestableScrollContainer> SearchParent() override;
    RefPtr<NestableScrollContainer> SearchParent(Axis scrollAxis);
    /**
     *  End of NestableScrollContainer implementations
     */

    void SetNestedScrollExt(const NestedScrollOptionsExt &nestedScroll);
    NestedScrollOptionsExt GetNestedScrollExt() const
    {
        return nestedScroll_;
    }
    WebBypassVsyncCondition GetWebBypassVsyncCondition() const
    {
        return webBypassVsyncCondition_;
    }
    void OnParentScrollDragEndRecursive(RefPtr<NestableScrollContainer> parent);
    ACE_DEFINE_PROPERTY_GROUP(WebProperty, WebPatternProperty);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, JsEnabled, bool);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, MediaPlayGestureAccess, bool);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, FileAccessEnabled, bool);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, OnLineImageAccessEnabled, bool);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, DomStorageAccessEnabled, bool);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, ImageAccessEnabled, bool);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, MixedMode, MixedModeContent);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, ZoomAccessEnabled, bool);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, GeolocationAccessEnabled, bool);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, UserAgent, std::string);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, CacheMode, WebCacheMode);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, OverviewModeAccessEnabled, bool);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, FileFromUrlAccessEnabled, bool);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, DatabaseAccessEnabled, bool);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, TextZoomRatio, int32_t);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, WebDebuggingAccessEnabledAndPort,
        WebPatternProperty::WebDebuggingConfigType);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, BackgroundColor, int32_t);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, InitialScale, float);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, PinchSmoothModeEnabled, bool);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, MultiWindowAccessEnabled, bool);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, AllowWindowOpenMethod, bool);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, WebCursiveFont, std::string);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, WebFantasyFont, std::string);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, WebFixedFont, std::string);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, WebSansSerifFont, std::string);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, WebSerifFont, std::string);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, WebStandardFont, std::string);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, DefaultFixedFontSize, int32_t);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, DefaultFontSize, int32_t);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, DefaultTextEncodingFormat, std::string);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, MinFontSize, int32_t);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, MinLogicalFontSize, int32_t);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, BlockNetwork, bool);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, DarkMode, WebDarkMode);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, ForceDarkAccess, bool);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, AudioResumeInterval, int32_t);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, AudioExclusive, bool);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, AudioSessionType, WebAudioSessionType);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, HorizontalScrollBarAccessEnabled, bool);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, VerticalScrollBarAccessEnabled, bool);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, ScrollBarColor, std::string);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, OverScrollMode, int32_t);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, BlurOnKeyboardHideMode, int32_t);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, CopyOptionMode, int32_t);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, MetaViewport, bool);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, NativeEmbedModeEnabled, bool);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, IntrinsicSizeEnabled, bool);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, CssDisplayChangeEnabled, bool);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, BypassVsyncCondition, WebBypassVsyncCondition);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, NativeEmbedRuleTag, std::string);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, NativeEmbedRuleType, std::string);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, TextAutosizing, bool);
    using NativeVideoPlayerConfigType = std::tuple<bool, bool>;
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, NativeVideoPlayerConfig, NativeVideoPlayerConfigType);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, SelectionMenuOptions, WebMenuOptionsParam);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, OverlayScrollbarEnabled, bool);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, KeyboardAvoidMode, WebKeyboardAvoidMode);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, EnabledHapticFeedback, bool);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, OptimizeParserBudgetEnabled, bool);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, WebMediaAVSessionEnabled, bool);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, EnableDataDetector, bool);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, EnableFollowSystemFontWeight, bool);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, GestureFocusMode, GestureFocusMode);

    bool IsFocus() const
    {
        return isFocus_;
    }

    void RequestFullScreen();
    void ExitFullScreen();
    bool IsFullScreen() const
    {
        return isFullScreen_;
    }
    void UpdateClippedSelectionBounds(int32_t x, int32_t y, int32_t w, int32_t h);
    bool RunQuickMenu(std::shared_ptr<OHOS::NWeb::NWebQuickMenuParams> params,
        std::shared_ptr<OHOS::NWeb::NWebQuickMenuCallback> callback);
    void OnContextMenuShow(const std::shared_ptr<BaseEventInfo>& info, bool isRichtext = true, bool result = false);
    void OnContextMenuHide();
    void OnQuickMenuDismissed();
    void HideHandleAndQuickMenuIfNecessary(bool hide, bool isScroll = false);
    void ChangeVisibilityOfQuickMenu();
    bool ChangeVisibilityOfQuickMenuV2();
    bool IsQuickMenuShow();
    void OnTouchSelectionChanged(std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> insertHandle,
        std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> startSelectionHandle,
        std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> endSelectionHandle);
    bool OnCursorChange(const OHOS::NWeb::CursorType& type, std::shared_ptr<OHOS::NWeb::NWebCursorInfo> info);
    void UpdateLocalCursorStyle(int32_t windowId, const OHOS::NWeb::CursorType& type);
    void UpdateCustomCursor(int32_t windowId, std::shared_ptr<OHOS::NWeb::NWebCursorInfo> info);
    std::shared_ptr<OHOS::Media::PixelMap> CreatePixelMapFromString(const std::string& filePath);
    void OnSelectPopupMenu(std::shared_ptr<OHOS::NWeb::NWebSelectPopupMenuParam> params,
        std::shared_ptr<OHOS::NWeb::NWebSelectPopupMenuCallback> callback);
    void OnDateTimeChooserPopup(
        std::shared_ptr<OHOS::NWeb::NWebDateTimeChooser> chooser,
        const std::vector<std::shared_ptr<OHOS::NWeb::NWebDateTimeSuggestion>>& suggestions,
        std::shared_ptr<NWeb::NWebDateTimeChooserCallback> callback);
    void OnDateTimeChooserClose();
    void OnShowAutofillPopup(const float offsetX, const float offsetY, const std::vector<std::string>& menu_items);
    void OnShowAutofillPopupV2(const float offsetX, const float offsetY, const float height, const float width,
        const std::vector<std::string>& menu_items);
    void OnHideAutofillPopup();
    RefPtr<FrameNode> CreateDataListFrameNode(const OffsetF& offfset, const float height, const float width);
    void RemoveDataListNode();
    bool IsOverlayCreating()
    {
        return overlayCreating_;
    }
    void SetOverlayCreating(bool overlayCreating)
    {
        overlayCreating_ = overlayCreating;
    }
    void UpdateLocale();
    void SetDrawRect(int32_t x, int32_t y, int32_t width, int32_t height);
    void SetSelectPopupMenuShowing(bool showing)
    {
        selectPopupMenuShowing_ = showing;
    }
    void ParseViewDataNumber(const std::string& key, int32_t value,
        RefPtr<PageNodeInfoWrap> node, RectT<float>& rect, float viewScale);
    void ParseNWebViewDataNode(std::unique_ptr<JsonValue> child,
        std::vector<RefPtr<PageNodeInfoWrap>>& nodeInfos, int32_t nodeId);
    void ParseNWebViewDataCommonField(std::unique_ptr<JsonValue> child,
        const std::shared_ptr<ViewDataCommon>& viewDataCommon);
    void ParseNWebViewDataJson(const std::shared_ptr<OHOS::NWeb::NWebMessage>& viewDataJson,
        std::vector<RefPtr<PageNodeInfoWrap>>& nodeInfos, const std::shared_ptr<ViewDataCommon>& viewDataCommon);
    AceAutoFillType GetFocusedType();
    HintToTypeWrap GetHintTypeAndMetadata(const std::string& attribute, RefPtr<PageNodeInfoWrap> node);
    bool HandleAutoFillEvent(const std::shared_ptr<OHOS::NWeb::NWebMessage>& viewDataJson);
    bool RequestAutoFill(AceAutoFillType autoFillType);
    bool RequestAutoFill(AceAutoFillType autoFillType, const std::vector<RefPtr<PageNodeInfoWrap>>& nodeInfos);
    bool RequestAutoSave();
    bool UpdateAutoFillPopup();
    bool CloseAutoFillPopup();
    void OnCompleteSwapWithNewSize();
    void OnResizeNotWork();
    void UpdateOnFocusTextField(bool isFocus);
    bool OnBackPressed() override;
    bool OnBackPressedForFullScreen() const;
    void SetFullScreenExitHandler(const std::shared_ptr<FullScreenEnterEvent>& fullScreenExitHandler);
    bool NotifyStartDragTask(bool isDelayed = false);
    bool IsImageDrag();
    void UpdateJavaScriptOnDocumentStart();
    void UpdateJavaScriptOnDocumentEnd();
    void JavaScriptOnDocumentStart(const ScriptItems& scriptItems);
    void JavaScriptOnDocumentEnd(const ScriptItems& scriptItems);
    void UpdateJavaScriptOnDocumentStartByOrder();
    void JavaScriptOnDocumentStartByOrder(const ScriptItems& scriptItems,
        const ScriptItemsByOrder& scriptItemsByOrder);
    void UpdateJavaScriptOnDocumentEndByOrder();
    void JavaScriptOnDocumentEndByOrder(const ScriptItems& scriptItems,
        const ScriptItemsByOrder& scriptItemsByOrder);
    void UpdateJavaScriptOnHeadReadyByOrder();
    void JavaScriptOnHeadReadyByOrder(const ScriptItems& scriptItems,
        const ScriptItemsByOrder& scriptItemsByOrder);
    void SetTouchEventInfo(const TouchEvent& touchEvent,
        TouchEventInfo& touchEventInfo, const std::string& embdedId);
    DragRet GetDragAcceptableStatus();
    Offset GetDragOffset() const;
    void RemovePreviewMenuNode();
    void UpdateImagePreviewParam();
    void OnOverScrollFlingVelocity(float xVelocity, float yVelocity, bool isFling);
    void OnScrollState(bool scrollState);
    void OnScrollStart(const float x, const float y);
    void SetLayoutMode(WebLayoutMode mode);
    WebLayoutMode GetLayoutMode() const
    {
        return layoutMode_;
    }
    void OnRootLayerChanged(int width, int height);
    void ReleaseResizeHold();
    bool GetPendingSizeStatus();
    int GetRootLayerWidth() const
    {
        return rootLayerWidth_;
    }
    int GetRootLayerHeight() const
    {
        return rootLayerHeight_;
    }
    Size GetDrawSize() const
    {
        return drawSize_;
    }
    SizeF GetDragPixelMapSize() const;
    bool IsVirtualKeyBoardShow() const
    {
        return isVirtualKeyBoardShow_ == VkState::VK_SHOW;
    }
    bool FilterScrollEvent(const float x, const float y, const float xVelocity, const float yVelocity);
    bool OnNestedScroll(float& x, float& y, float& xVelocity, float& yVelocity, bool& isAvailable);
    std::shared_ptr<OHOS::NWeb::NWebAccessibilityNodeInfo> GetAccessibilityNodeById(int64_t accessibilityId);
    std::shared_ptr<NG::TransitionalNodeInfo> GetFocusedAccessibilityNode(int64_t accessibilityId,
        bool isAccessibilityFocus);
    std::shared_ptr<NG::TransitionalNodeInfo> GetTransitionalNodeById(int64_t accessibilityId);
    std::shared_ptr<NG::TransitionalNodeInfo> GetAccessibilityNodeByFocusMove(int64_t accessibilityId,
        int32_t direction);
    bool ExecuteAction(int64_t accessibilityId, AceAction action,
        const std::map<std::string, std::string>& actionArguments) const;
    void SetAccessibilityState(bool state, bool isDelayed = false);
    void UpdateScrollBarWithBorderRadius();
    void UpdateFocusedAccessibilityId(int64_t accessibilityId = -1);
    void ClearFocusedAccessibilityId();
    void OnTooltip(const std::string& tooltip);
    void OnPopupSize(int32_t x, int32_t y, int32_t width, int32_t height);
    void GetVisibleRectToWeb(int& visibleX, int& visibleY, int& visibleWidth, int& visibleHeight);
    void RestoreRenderFit();
    void OnPopupShow(bool show);
    bool IsDefaultFocusNodeExist();
    bool IsRootNeedExportTexture();
    std::vector<int8_t> GetWordSelection(const std::string& text, int8_t offset);
    bool Backward();
    void OnSelectionMenuOptionsUpdate(const WebMenuOptionsParam& webMenuOption);
    void UpdateEditMenuOptions(const NG::OnCreateMenuCallback&& onCreateMenuCallback,
        const NG::OnMenuItemClickCallback&& onMenuItemClick, const NG::OnPrepareMenuCallback&& onPrepareMenuCallback);
    void UpdateDataDetectorConfig(const TextDetectConfig& config);
    void NotifyForNextTouchEvent() override;
    void CloseKeyboard();
    void CreateOverlay(const RefPtr<OHOS::Ace::PixelMap>& pixelMap, int offsetX, int offsetY, int rectWidth,
        int rectHeight, int pointX, int pointY);
    void OnOverlayStateChanged(int offsetX, int offsetY, int rectWidth, int rectHeight);
    void OnTextSelected();
    void DestroyAnalyzerOverlay();
    WebInfoType GetWebInfoType();
    void RequestFocus();
    bool IsCurrentFocus();
    void SetCustomKeyboardBuilder(std::function<void()> customKeyboardBuilder)
    {
        customKeyboardBuilder_ = customKeyboardBuilder;
    }
    void AttachCustomKeyboard();
    void CloseCustomKeyboard();
    void KeyboardReDispatch(const std::shared_ptr<OHOS::NWeb::NWebKeyEvent>& event, bool isUsed);
    void EnableSecurityLayer(bool isNeedSecurityLayer);
    void OnCursorUpdate(double x, double y, double width, double height)
    {
        cursorInfo_ = RectF(x, y, width, height);
    }
    RectF GetCaretRect() const override
    {
        return cursorInfo_;
    }
    void OnAttachContext(PipelineContext *context) override;
    void OnDetachContext(PipelineContext *context) override;
    void SetUpdateInstanceIdCallback(std::function<void(int32_t)> &&callabck);
    Rosen::NodeId GetWebSurfaceNodeId() const
    {
        auto rosenRenderContext = AceType::DynamicCast<NG::RosenRenderContext>(renderContextForSurface_);
        CHECK_NULL_RETURN(rosenRenderContext, 0);
        auto rsNode = rosenRenderContext->GetRSNode();
        CHECK_NULL_RETURN(rsNode, 0);
        auto surfaceNodeId = rsNode->GetId();
        TAG_LOGD(AceLogTag::ACE_WEB, "Web surfaceNodeId is %{public}" PRIu64 "", surfaceNodeId);
        return surfaceNodeId;
    }
    std::shared_ptr<Rosen::RSNode> GetSurfaceRSNode() const;

    void GetAllWebAccessibilityNodeInfos(WebNodeInfoCallback cb, int32_t webId, bool needFilter = true);
    void OnAccessibilityHoverEvent(
        const NG::PointF& point, SourceType source, NG::AccessibilityHoverEventType eventType, TimeStamp time);
    std::string GetSurfaceIdByHtmlElementId(const std::string& htmlElementId);
    int64_t GetWebAccessibilityIdBySurfaceId(const std::string& surfaceId);
    void RegisterTextBlurCallback(TextBlurCallback&& callback);
    void UnRegisterTextBlurCallback();
    TextBlurCallback GetTextBlurCallback() const
    {
        return textBlurCallback_;
    }
    void RegisterWebComponentClickCallback(WebComponentClickCallback&& callback);
    void UnregisterWebComponentClickCallback();
    WebComponentClickCallback GetWebComponentClickCallback() const { return webComponentClickCallback_; }
    void DumpInfo() override;
    void DumpGpuInfo();
    void DumpSurfaceInfo();
    void OnSetAccessibilityChildTree(int32_t childWindowId, int32_t childTreeId);
    bool OnAccessibilityChildTreeRegister();
    bool OnAccessibilityChildTreeDeregister();
    bool GetActiveStatus() const;
    void StartVibraFeedback(const std::string& vibratorType);
    int32_t GetTreeId()
    {
        return treeId_;
    }
    bool CloseImageOverlaySelection();
    void SetDrawSize(double width, double height);
    void SetImageOverlaySelectedStatus(bool isSelected)
    {
        imageOverlayIsSelected_ = isSelected;
    }
    // The magnifier needs this to know the web's offset
    OffsetF GetTextPaintOffset() const override;
    void OnColorConfigurationUpdate() override;
    void RecordWebEvent(bool isInit = false) override;
    bool RunJavascriptAsync(const std::string& jsCode, std::function<void(const std::string&)>&& callback);

    bool IsPreviewImageNodeExist() const
    {
        return previewImageNodeId_.has_value();
    }

    void SetNewDragStyle(bool isNewDragStyle)
    {
        isNewDragStyle_ = isNewDragStyle;
    }

    bool IsNewDragStyle() const
    {
        return isNewDragStyle_;
    }

    bool isNeedInterceptedTouchEvent_ = false;

    bool IsDragging() const
    {
        return isDragging_;
    }
    bool IsDefaultGestureFocusMode() const
    {
        return gestureFocusMode_ == GestureFocusMode::DEFAULT;
    }

    void SetPreviewSelectionMenu(const std::shared_ptr<WebPreviewSelectionMenuParam>& param);

    std::shared_ptr<WebPreviewSelectionMenuParam> GetPreviewSelectionMenuParams(
        const WebElementType& type, const ResponseType& responseType);

    bool IsPreviewMenuNotNeedShowPreview();

    bool GetAccessibilityVisible(int64_t accessibilityId);

    void OnWebMediaAVSessionEnabledUpdate(bool enable);

    void UpdateImageOverlayTouchInfo(int touchPointX, int touchPointY, TouchType touchType);
    void PushOverlayInfo(float x, float y, int32_t id);
    void WebOverlayRequestFocus();

    std::string GetCurrentLanguage() override;
    void GetTranslateTextCallback(const std::string& result);
    void RegisterTranslateTextJavaScript();
    void InitTranslateText();
    void GetTranslateText(
        std::string extraData, std::function<void(std::string)> callback, bool isContinued) override;
    void SendTranslateResult(std::vector<std::string> results, std::vector<int32_t> ids) override;
    void SendTranslateResult(std::string results) override;
    void EndTranslate() override;
    void RunJsInit();

    RefPtr<AccessibilitySessionAdapter> GetAccessibilitySessionAdapter() override;

    void RegisterSurfaceDensityCallback();
    void SetSurfaceDensity(double density);

    void InitRotationEventCallback();
    void UninitRotationEventCallback();

    std::queue<MouseInfo>& GetMouseInfoQueue()
    {
        return mouseInfoQueue_;
    }

    MouseInfo GetMouseInfo()
    {
        return mouseInfo_;
    }

    // Data Detector funcs
    RefPtr<WebDataDetectorAdapter> GetDataDetectorAdapter();

    bool GetDataDetectorEnable();
    void InitDataDetector();
    void InitAIDetectResult();
    void CloseDataDetectorMenu();

    void SetAILinkMenuShow(bool isAILinkMenuShow)
    {
        isAILinkMenuShow_ = isAILinkMenuShow;
    }

    void CreateSnapshotImageFrameNode(const std::string& snapshotPath);
    void RemoveSnapshotFrameNode();

    void OnPip(int status, int delegateId, int childId, int frameRoutingId, int width, int height);
    void SetPipNativeWindow(int delegateId, int childId, int frameRoutingId, void* window);
    void SendPipEvent(int delegateId, int childId, int frameRoutingId, int event);
    void SetDefaultBackgroundColor();
    bool CheckVisible();

    void UpdateSingleHandleVisible(bool isVisible);
    void OnShowMagnifier();
    void OnHideMagnifier();
    void SetTouchHandleExistState(bool touchHandleExist);
private:
    friend class WebContextSelectOverlay;
    friend class WebSelectOverlay;
    friend class WebDataDetectorAdapter;

    bool Pip(int status, int delegateId, int childId, int frameRoutingId, int width, int height);
    napi_env CreateEnv();
    bool CreatePip(int status, napi_env env, bool& init, uint32_t &pipController, const PipInfo &pipInfo);
    bool RegisterPip(uint32_t pipController);
    bool StartPip(uint32_t pipController);
    void EnablePip(uint32_t pipController);
    bool StopPip(int delegateId, int childId, int frameRoutingId);
    bool PlayPip(int delegateId, int childId, int frameRoutingId);
    bool PausePip(int delegateId, int childId, int frameRoutingId);
    void GetPreviewImageOffsetAndSize(bool isImage, Offset& previewOffset, SizeF& previewSize);
    RefPtr<FrameNode> CreatePreviewImageFrameNode(bool isImage);
    void ShowPreviewMenu(WebElementType type);
    void ShowContextSelectOverlay(const RectF& firstHandle, const RectF& secondHandle,
        TextResponseType responseType = TextResponseType::RIGHT_CLICK, bool handleReverse = false);
    void CloseContextSelectionMenu();
    RectF ComputeMouseClippedSelectionBounds(int32_t x, int32_t y, int32_t w, int32_t h);
    void RegistVirtualKeyBoardListener(const RefPtr<PipelineContext> &context);
    bool IsNeedResizeVisibleViewport();
    bool ProcessVirtualKeyBoardHide(int32_t width, int32_t height, bool safeAreaEnabled);
    bool ProcessVirtualKeyBoardHideAvoidMenu(int32_t width, int32_t height, bool safeAreaEnabled);
    bool ProcessVirtualKeyBoardShow(int32_t width, int32_t height, double keyboard, bool safeAreaEnabled);
    bool ProcessVirtualKeyBoardShowAvoidMenu(int32_t width, int32_t height, double keyboard, bool safeAreaEnabled);
    bool ProcessVirtualKeyBoard(int32_t width, int32_t height, double keyboard, bool isCustomKeyboard = false);
    void UpdateWebLayoutSize(int32_t width, int32_t height, bool isKeyboard, bool isUpdate = true);
    bool UpdateLayoutAfterKeyboard(int32_t width, int32_t height, double keyboard);
    void UpdateLayoutAfterKeyboardShow(int32_t width, int32_t height, double keyboard, double oldWebHeight);
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;
    void BeforeSyncGeometryProperties(const DirtySwapConfig& config) override;
    void OnRebuildFrame() override;

    void OnAttachToFrameNode() override;
    void OnDetachFromFrameNode(FrameNode* frameNode) override;

    void OnWindowShow() override;
    void OnWindowHide() override;
    void OnWindowSizeChanged(int32_t width, int32_t height, WindowSizeChangeReason type) override;
    void OnInActive() override;
    void OnActive() override;
    void OnVisibleAreaChange(bool isVisible);
    void OnAreaChangedInner() override;
    void OnNotifyMemoryLevel(int32_t level) override;
    void OnAttachToMainTree() override;
    void OnDetachFromMainTree() override;

    void OnWebSrcUpdate();
    void OnWebDataUpdate();
    void OnJsEnabledUpdate(bool value);
    void OnMediaPlayGestureAccessUpdate(bool value);
    void OnFileAccessEnabledUpdate(bool value);
    void OnOnLineImageAccessEnabledUpdate(bool value);
    void OnDomStorageAccessEnabledUpdate(bool value);
    void OnImageAccessEnabledUpdate(bool value);
    void OnMixedModeUpdate(MixedModeContent value);
    void OnZoomAccessEnabledUpdate(bool value);
    void OnGeolocationAccessEnabledUpdate(bool value);
    void OnUserAgentUpdate(const std::string& value);
    void OnCacheModeUpdate(WebCacheMode value);
    void OnOverviewModeAccessEnabledUpdate(bool value);
    void OnFileFromUrlAccessEnabledUpdate(bool value);
    void OnDatabaseAccessEnabledUpdate(bool value);
    void OnTextZoomRatioUpdate(int32_t value);
    void OnWebDebuggingAccessEnabledAndPortUpdate(
        const WebPatternProperty::WebDebuggingConfigType& enabled_and_port);
    void OnPinchSmoothModeEnabledUpdate(bool value);
    void OnBackgroundColorUpdate(int32_t value);
    void OnInitialScaleUpdate(float value);
    void OnMultiWindowAccessEnabledUpdate(bool value);
    void OnAllowWindowOpenMethodUpdate(bool value);
    void OnWebCursiveFontUpdate(const std::string& value);
    void OnWebFantasyFontUpdate(const std::string& value);
    void OnWebFixedFontUpdate(const std::string& value);
    void OnWebSerifFontUpdate(const std::string& value);
    void OnWebSansSerifFontUpdate(const std::string& value);
    void OnWebStandardFontUpdate(const std::string& value);
    void OnDefaultFixedFontSizeUpdate(int32_t value);
    void OnDefaultFontSizeUpdate(int32_t value);
    void OnDefaultTextEncodingFormatUpdate(const std::string& value);
    void OnMinFontSizeUpdate(int32_t value);
    void OnMinLogicalFontSizeUpdate(int32_t value);
    void OnBlockNetworkUpdate(bool value);
    void OnDarkModeUpdate(WebDarkMode mode);
    void OnForceDarkAccessUpdate(bool access);
    void OnAudioResumeIntervalUpdate(int32_t resumeInterval);
    void OnAudioExclusiveUpdate(bool audioExclusive);
    void OnAudioSessionTypeUpdate(WebAudioSessionType value);
    void OnHorizontalScrollBarAccessEnabledUpdate(bool value);
    void OnVerticalScrollBarAccessEnabledUpdate(bool value);
    void OnScrollBarColorUpdate(const std::string& value);
    void OnOverScrollModeUpdate(const int32_t value);
    void OnBlurOnKeyboardHideModeUpdate(const int32_t value);
    void OnCopyOptionModeUpdate(const int32_t value);
    void OnMetaViewportUpdate(bool value);
    void OnNativeEmbedModeEnabledUpdate(bool value);
    void OnIntrinsicSizeEnabledUpdate(bool value);
    void OnCssDisplayChangeEnabledUpdate(bool value);
    void OnBypassVsyncConditionUpdate(WebBypassVsyncCondition condition);
    void OnNativeEmbedRuleTagUpdate(const std::string& tag);
    void OnNativeEmbedRuleTypeUpdate(const std::string& type);
    void OnTextAutosizingUpdate(bool isTextAutosizing);
    void OnNativeVideoPlayerConfigUpdate(const std::tuple<bool, bool>& config);
    void WindowDrag(int32_t width, int32_t height);
    void WindowMaximize();
    void OnOverlayScrollbarEnabledUpdate(bool enable);
    void OnKeyboardAvoidModeUpdate(const WebKeyboardAvoidMode& mode);
    void OnEnabledHapticFeedbackUpdate(bool enable);
    void OnOptimizeParserBudgetEnabledUpdate(bool value);
    void OnEnableFollowSystemFontWeightUpdate(bool value);
    void OnEnableDataDetectorUpdate(bool enable);
    void OnGestureFocusModeUpdate(GestureFocusMode mode);

    int GetWebId();

    void InitEvent();
    void InitConfigChangeCallback(const RefPtr<PipelineContext>& context);
    void InitFeatureParam();
    void InitTouchEvent(const RefPtr<GestureEventHub>& gestureHub);
    void InitMouseEvent(const RefPtr<InputEventHub>& inputHub);
    void InitHoverEvent(const RefPtr<InputEventHub>& inputHub);
    void InitCommonDragDropEvent(const RefPtr<GestureEventHub>& gestureHub);
    void InitWebEventHubDragDropStart(const RefPtr<WebEventHub>& eventHub);
    void InitWebEventHubDragDropEnd(const RefPtr<WebEventHub>& eventHub);
    void InitWebEventHubDragMove(const RefPtr<WebEventHub>& eventHub);
    void InitPanEvent(const RefPtr<GestureEventHub>& gestureHub);
    void HandleFlingMove(const GestureEvent& event);
    void HandleDragMove(const GestureEvent& event);
    void InitDragEvent(const RefPtr<GestureEventHub>& gestureHub);
    void HandleDragStart(int32_t x, int32_t y);
    void HandleDragEnd(int32_t x, int32_t y);
    void HandleDragCancel();
    void ClearDragData();
    void SetFakeDragData(const RefPtr<OHOS::Ace::DragEvent>& info);
    bool GenerateDragDropInfo(NG::DragDropInfo& dragDropInfo);
    void HandleMouseEvent(MouseInfo& info);
    void HandleTouchEvent(const TouchEventInfo& info);
    void WebOnMouseEvent(const MouseInfo& info);
    void WebSendMouseEvent(const MouseInfo& info, int32_t clickNum);
    bool HandleDoubleClickEvent(const MouseInfo& info);
    void SendDoubleClickEvent(const MouseClickInfo& info);
    int32_t HandleMouseClickEvent(const MouseInfo& info);
    void InitFocusEvent(const RefPtr<FocusHub>& focusHub);
    void HandleFocusEvent();
    void HandleBlurEvent(const BlurReason& blurReason);
    bool HandleKeyEvent(const KeyEvent& keyEvent);
    bool WebOnKeyEvent(const KeyEvent& keyEvent);
    void WebRequestFocus();
    void ResetDragAction();
    void InitSlideUpdateListener();
    void CalculateHorizontalDrawRect();
    void CalculateVerticalDrawRect();
    void InitPinchEvent(const RefPtr<GestureEventHub>& gestureHub);
    bool CheckZoomStatus(const double& curScale);
    bool ZoomOutAndIn(const double& curScale, double& scale);
    void HandleScaleGestureChange(const GestureEvent& event);
    void HandleScaleGestureStart(const GestureEvent& event);
    void HandleScaleGestureEnd(const GestureEvent& event);
    void HandleScaleGestureCancel(const GestureEvent& event);
    double getZoomOffset(double& scale) const;

    NG::DragDropInfo HandleOnDragStart(const RefPtr<OHOS::Ace::DragEvent>& info);
    void HandleOnDragEnter(const RefPtr<OHOS::Ace::DragEvent>& info);
    void HandleOnDropMove(const RefPtr<OHOS::Ace::DragEvent>& info);
    void HandleOnDragDrop(const RefPtr<OHOS::Ace::DragEvent>& info);
    void HandleOnDragDropFile(RefPtr<UnifiedData> aceData);
    void HandleOnDragDropLink(RefPtr<UnifiedData> aceData);
    void HandleOnDragLeave(int32_t x, int32_t y);
    void HandleOnDragEnd(int32_t x, int32_t y);
    void ResetDragStateValue();
    void InitTouchEventListener();
    void UninitTouchEventListener();
    void OnDragFileNameStart(const RefPtr<UnifiedData>& aceUnifiedData, const std::string& fileName);
    void AdjustRotationRenderFit(WindowSizeChangeReason type);
    void RecoverToTopLeft();
    bool needRestoreMenuForDrag_ = false;
    int32_t dropX_ = 0;
    int32_t dropY_ = 0;
    int onDragMoveCnt = 0;
    bool isDragEndMenuShow_ = false;
    std::chrono::time_point<std::chrono::system_clock> firstMoveInTime;
    std::chrono::time_point<std::chrono::system_clock> preMoveInTime;
    std::chrono::time_point<std::chrono::system_clock> curMoveInTime;
    CancelableCallback<void()> timer_;
    int32_t duration_ = 100; // 100: 100ms
    void DoRepeat();
    void StartRepeatTimer();

    void HandleTouchDown(const TouchEventInfo& info, bool fromOverlay);

    void HandleTouchUp(const TouchEventInfo& info, bool fromOverlay);

    void HandleTouchMove(const TouchEventInfo& info, bool fromOverlay);

    void HandleTouchCancel(const TouchEventInfo& info);

    void HandleTouchClickEventFromOverlay(const GestureEvent& info);
    void SuggestionSelected(int32_t index);
    void InitializeAccessibility();
    void UninitializeAccessibility();
    void CloseSelectOverlay();
    void DelTouchOverlayInfoByTouchId(int32_t touchId);
    std::optional<OffsetF> GetCoordinatePoint();
    static void InitSelectPopupMenuViewOption(const std::vector<RefPtr<FrameNode>>& options,
        const std::shared_ptr<OHOS::NWeb::NWebSelectPopupMenuCallback>& callback,
        const std::shared_ptr<OHOS::NWeb::NWebSelectPopupMenuParam>& params,
        const double& dipScale);
    static void InitSelectPopupMenuView(RefPtr<FrameNode>& menuWrapper,
        std::shared_ptr<OHOS::NWeb::NWebSelectPopupMenuCallback> callback,
        std::shared_ptr<OHOS::NWeb::NWebSelectPopupMenuParam> params,
        const double& dipScale);
    OffsetF GetSelectPopupPostion(std::shared_ptr<OHOS::NWeb::NWebSelectMenuBound> bound);
    bool GetAccessibilityFocusRect(RectT<int32_t>& paintRect, int64_t accessibilityId) const;
    void SetTouchLocationInfo(const TouchEvent& touchEvent, const TouchLocationInfo& changedInfo,
        const TouchEventInfo& tempTouchInfo, TouchEventInfo& touchEventInfo);
    struct TouchInfo {
        float x = -1.0f;
        float y = -1.0f;
        int32_t id = -1;
    };
    static bool ParseTouchInfo(const TouchEventInfo& info, std::list<TouchInfo>& touchInfos);
    void InitEnhanceSurfaceFlag();
    void UpdateBackgroundColorRightNow(int32_t color);
    void UpdateContentOffset(const RefPtr<LayoutWrapper>& dirty);
    DialogProperties GetDialogProperties(const RefPtr<DialogTheme>& theme);
    bool ShowDateTimeDialog(std::shared_ptr<OHOS::NWeb::NWebDateTimeChooser> chooser,
        const std::vector<std::shared_ptr<OHOS::NWeb::NWebDateTimeSuggestion>>& suggestions,
        std::shared_ptr<NWeb::NWebDateTimeChooserCallback> callback);
    bool ShowTimeDialog(std::shared_ptr<OHOS::NWeb::NWebDateTimeChooser> chooser,
        const std::vector<std::shared_ptr<OHOS::NWeb::NWebDateTimeSuggestion>>& suggestions,
        std::shared_ptr<NWeb::NWebDateTimeChooserCallback> callback);
    bool ShowDateTimeSuggestionDialog(std::shared_ptr<OHOS::NWeb::NWebDateTimeChooser> chooser,
        const std::vector<std::shared_ptr<OHOS::NWeb::NWebDateTimeSuggestion>>& suggestions,
        std::shared_ptr<NWeb::NWebDateTimeChooserCallback> callback);
    void PostTaskToUI(const std::function<void()>&& task, const std::string& name) const;
    void LoadUrlInOfflineMode();
    void InitInOfflineMode();
    void OnOverScrollFlingVelocityHandler(float velocity, bool isFling);
    bool FilterScrollEventHandleOffset(float offset);
    bool CheckParentScroll(const float &directValue, const NestedScrollMode &scrollMode);
    bool CheckOverParentScroll(const float &directValue, const NestedScrollMode &scrollMode);
    bool FilterScrollEventHandlevVlocity(const float velocity);
    void CheckAndSetWebNestedScrollExisted();
    void CalculateTooltipOffset(RefPtr<FrameNode>& tooltipNode, OffsetF& tooltipOfffset);
    void HandleShowTooltip(const std::string& tooltip, int64_t tooltipTimestamp);
    bool GetShadowFromTheme(ShadowStyle shadowStyle, Shadow& shadow);
    void ShowTooltip(const std::string& tooltip, int64_t tooltipTimestamp);
    void UpdateTooltipContentColor(const RefPtr<FrameNode>& textNode);
    void RegisterVisibleAreaChangeCallback(const RefPtr<PipelineContext> &context);
    bool CheckSafeAreaIsExpand();
    bool CheckSafeAreaKeyBoard();
    bool IsDialogNested();
    void SelectCancel() const;
    bool IsSelectInfoValid();
    std::optional<RectF> GetViewPort() const;
    std::string GetSelectInfo() const;
    void UpdateRunQuickMenuSelectInfo(SelectOverlayInfo& selectInfo,
        std::shared_ptr<OHOS::NWeb::NWebQuickMenuParams> params,
        std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> insertTouchHandle,
        std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> beginTouchHandle,
        std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> endTouchHandle);
    double GetNewScale(double& scale) const;
    double GetNewOriginScale(double originScale) const;
    void UpdateSlideOffset();
    void ClearKeyEventByKeyCode(int32_t keyCode);
    void SetRotation(uint32_t rotation);
    Color GetSystemColor() const;
    void UpdateTransformHintChangedCallbackId(std::optional<int32_t> id)
    {
        transformHintChangedCallbackId_ = id;
    }

    bool HasTransformHintChangedCallbackId()
    {
        return transformHintChangedCallbackId_.has_value();
    }

    void JsonNodePutDefaultValue(std::unique_ptr<OHOS::Ace::JsonValue>& jsonNode,
        WebAccessibilityType key, int32_t value, int32_t defaultValue);
    void JsonNodePutDefaultValue(std::unique_ptr<OHOS::Ace::JsonValue>& jsonNode,
        WebAccessibilityType key, bool value);
    void JsonNodePutDefaultValue(std::unique_ptr<OHOS::Ace::JsonValue>& jsonNode,
        WebAccessibilityType key, std::string value);
    void WebNodeInfoToJsonValue(std::shared_ptr<OHOS::Ace::JsonValue>& jsonNodeArray,
                                std::shared_ptr<OHOS::NWeb::NWebAccessibilityNodeInfo> webNodeInfo,
                                std::string& nodeTag, bool isArray = false);
    void GetWebAllInfosImpl(WebNodeInfoCallback cb, int32_t webId, bool needFilter = true);
    std::string EnumTypeToString(WebAccessibilityType type);
    std::string VectorIntToString(std::vector<int64_t>&& vec);
    void InitMagnifier();
    void ShowMagnifier(int centerOffsetX, int centerOffsetY);
    void HideMagnifier();
    void OnMagnifierHandleMove(const RectF& handleRect, bool isFirst);
    int32_t GetBufferSizeByDeviceType();
    void SetActiveStatusInner(bool isActive, bool isForce = false);
    void UpdateTouchpadSlidingStatus(const GestureEvent& event);
    CursorStyleInfo GetAndUpdateCursorStyleInfo(
        const OHOS::NWeb::CursorType& type, std::shared_ptr<OHOS::NWeb::NWebCursorInfo> info);
    bool MenuAvoidKeyboard(bool hideOrClose, double height = 0.0f);
    int32_t GetVisibleViewportAvoidHeight();

    std::optional<std::string> webSrc_;
    std::optional<std::string> webData_;
    std::optional<std::string> customScheme_;
    RefPtr<WebController> webController_;
    std::optional<int32_t> transformHintChangedCallbackId_;
    uint32_t rotation_ = 0;
    SetWebIdCallback setWebIdCallback_ = nullptr;
    SetWebDetachCallback setWebDetachCallback_ = nullptr;
    PermissionClipboardCallback permissionClipboardCallback_ = nullptr;
    OnOpenAppLinkCallback onOpenAppLinkCallback_ = nullptr;
    SetFaviconCallback setFaviconCallback_ = nullptr;
    DefaultFileSelectorShowCallback defaultFileSelectorShowCallback_ = nullptr;
    RenderMode renderMode_;
    bool incognitoMode_ = false;
    SetHapPathCallback setHapPathCallback_ = nullptr;
    JsProxyCallback jsProxyCallback_ = nullptr;
    OnControllerAttachedCallback onControllerAttachedCallback_ = nullptr;
    RefPtr<RenderSurface> renderSurface_ = RenderSurface::Create();
    RefPtr<RenderSurface> popupRenderSurface_ = RenderSurface::Create();
    RefPtr<RenderContext> renderContextForSurface_;
    RefPtr<RenderContext> renderContextForPopupSurface_;
    RefPtr<TouchEventImpl> touchEvent_;
    RefPtr<InputEvent> mouseEvent_;
    RefPtr<InputEvent> hoverEvent_;
    RefPtr<PanEvent> panEvent_ = nullptr;
    bool selectTemporarilyHidden_ = false;
    bool selectTemporarilyHiddenByScroll_ = false;
    bool nodeAttach_ = false;
    RefPtr<SelectOverlayProxy> selectOverlayProxy_ = nullptr;
    RefPtr<WebSelectOverlay> webSelectOverlay_ = nullptr;
    RefPtr<WebPaintProperty> webPaintProperty_ = nullptr;
    RefPtr<DragEvent> dragEvent_;
    bool isUrlLoaded_ = false;
    std::queue<MouseClickInfo> mouseClickQueue_;
    bool isFullScreen_ = false;
    std::shared_ptr<FullScreenEnterEvent> fullScreenExitHandler_ = nullptr;
    bool needOnFocus_ = false;
    Size drawSize_;
    Size visibleViewportSize_{-1.0, -1.0};
    bool isKeyboardInSafeArea_ = false;
    WebKeyboardAvoidMode keyBoardAvoidMode_ = WebKeyboardAvoidMode::DEFAULT;
    Size rootLayerChangeSize_;
    Size drawSizeCache_;
    Size areaChangeSize_;
    bool isNeedReDrawRect_ = false;
    bool needUpdateWeb_ = true;
    bool isFocus_ = false;
    VkState isVirtualKeyBoardShow_ { VkState::VK_NONE };
    bool isDragging_ = false;
    bool isReceivedArkDrag_ = false;
    bool isW3cDragEvent_ = false;
    bool isDragStartFromWeb_ = false;
    RefPtr<AccessibilitySessionAdapter> accessibilitySessionAdapter_;

    bool isNewDragStyle_ = false;
    std::map<std::pair<WebElementType, ResponseType>,
        std::shared_ptr<WebPreviewSelectionMenuParam>> previewSelectionMenuMap_;
    std::optional<int32_t> previewImageNodeId_ = std::nullopt;
    std::optional<int32_t> snapshotImageNodeId_ = std::nullopt;
    bool needUpdateImagePreviewParam_ = false;
    WebElementType curElementType_ = WebElementType::NONE;
    ResponseType curResponseType_ = ResponseType::LONG_PRESS;
    bool curContextMenuResult_ = false;

    bool isWindowShow_ = true;
    bool isActive_ = true;
    bool isEnhanceSurface_ = false;
    bool isAllowWindowOpenMethod_ = false;
    bool isShowAutofillPopup_ = false;
    OffsetF webOffset_;
    RefPtr<WebContextSelectOverlay> contextSelectOverlay_ = nullptr;
    RefPtr<WebContextMenuParam> contextMenuParam_ = nullptr;
    RefPtr<ContextMenuResult> contextMenuResult_ = nullptr;
    RectF selectArea_;
    RectF cursorInfo_;
    std::shared_ptr<OHOS::NWeb::NWebQuickMenuCallback> quickMenuCallback_ = nullptr;
    bool selectPopupMenuShowing_ = false;
    std::list<TouchInfo> touchOverlayInfo_;
    bool isPopup_ = false;
    int32_t tooltipId_ = -1;
    int32_t mouseHoveredX_ = -1;
    int32_t mouseHoveredY_ = -1;
    int32_t mouseEventDeviceId_ = -1;
    int64_t tooltipTimestamp_ = -1;
    int32_t parentNWebId_ = -1;
    bool isInWindowDrag_ = false;
    bool isWaiting_ = false;
    bool isDisableDrag_ = false;
    bool isMouseEvent_ = false;
    bool isHoverExit_ = false;
    bool isVisible_ = true;
    bool isVisibleActiveEnable_ = true;
    bool isMemoryLevelEnable_ = true;
    OffsetF fitContentOffset_;
    bool isFirstFlingScrollVelocity_ = true;
    bool isScrollStarted_ = false;
    WebLayoutMode layoutMode_ = WebLayoutMode::NONE;
    bool isEmbedModeEnabled_ = false;
    bool scrollState_ = false;
    Axis axis_ = Axis::FREE;
    Axis syncAxis_ = Axis::NONE;
    Axis expectedScrollAxis_ = Axis::FREE;
    int32_t rootLayerWidth_ = 0;
    int32_t rootLayerHeight_ = 0;
    int32_t drawRectWidth_ = 0;
    int32_t drawRectHeight_ = 0;
    std::unordered_map<Axis, WeakPtr<NestableScrollContainer>> parentsMap_;
    RefPtr<WebDelegate> delegate_;
    RefPtr<WebDelegateObserver> observer_;
    std::optional<ScriptItems> onDocumentStartScriptItems_;
    std::optional<ScriptItems> onDocumentEndScriptItems_;
    std::optional<ScriptItems> onHeadReadyScriptItems_;
    std::optional<ScriptItemsByOrder> onDocumentStartScriptItemsByOrder_;
    std::optional<ScriptItemsByOrder> onDocumentEndScriptItemsByOrder_;
    std::optional<ScriptItemsByOrder> onHeadReadyScriptItemsByOrder_;

    bool isAttachedToMainTree_ = false;
    bool offlineWebInited_ = false;
    bool offlineWebRendered_ = false;
    ACE_DISALLOW_COPY_AND_MOVE(WebPattern);
    bool accessibilityState_ = false;
    TouchEventInfo touchEventInfo_{"touchEvent"};
    std::vector<TouchEventInfo> touchEventInfoList_ {};
    bool isParentReachEdge_ = false;
    RefPtr<PinchGesture> pinchGesture_ = nullptr;
    std::queue<TouchEventInfo> touchEventQueue_;
    std::queue<MouseInfo> mouseInfoQueue_;
    std::vector<NG::MenuOptionsParam> menuOptionParam_ {};
    std::list<KeyEvent> webKeyEvent_ {};
    double startPinchScale_ = -1.0;
    double preScale_ = -1.0;
    double pageScale_ = 1.0;
    double startPageScale_ = 1.0;
    bool isResizeContentAvoid_ = false;
    float heightAfterAvoid_ = 0.0;
    bool zoomOutSwitch_ = false;
    bool isTouchUpEvent_ = false;
    int32_t zoomStatus_ = 0;
    int32_t zoomErrorCount_ = 0;
    std::shared_ptr<ImageAnalyzerManager> imageAnalyzerManager_ = nullptr;
    bool overlayCreating_ = false;
    bool awaitingOnTextSelected_ = false;
    RefPtr<OverlayManager> keyboardOverlay_;
    std::function<void()> customKeyboardBuilder_ = nullptr;
    std::function<void(int32_t)> updateInstanceIdCallback_;
    std::shared_ptr<TouchEventListener> touchEventListener_ = nullptr;
    double lastKeyboardHeight_ = 0.0;
    bool inspectorAccessibilityEnable_ = false;
    std::optional<std::string> sharedRenderProcessToken_;
    bool textBlurAccessibilityEnable_ = false;
    TextBlurCallback textBlurCallback_ = nullptr;
    WebComponentClickCallback webComponentClickCallback_ = nullptr;
    uint32_t autoFillSessionId_ = 0;
    std::unordered_map<int32_t, std::shared_ptr<WebAccessibilityChildTreeCallback>> accessibilityChildTreeCallback_;
    int32_t treeId_ = 0;
    int32_t instanceId_ = -1;
    int64_t focusedAccessibilityId_ = -1;
    std::vector<RefPtr<PageNodeInfoWrap>> pageNodeInfo_;
    bool isRenderModeInit_ = false;
    bool isAutoFillClosing_ = true;
    std::shared_ptr<ViewDataCommon> viewDataCommon_;
    OffsetF requestedWebOffset_;
    bool isPasswordFill_ = false;
    bool isEnabledHapticFeedback_ = true;
    bool isTouchpadSliding_ = false;
    NestedScrollOptionsExt nestedScroll_ = {
        .scrollUp = NestedScrollMode::SELF_ONLY,
        .scrollDown = NestedScrollMode::SELF_ONLY,
        .scrollLeft = NestedScrollMode::SELF_ONLY,
        .scrollRight = NestedScrollMode::SELF_ONLY,
    };
    VisibleType componentVisibility_ = VisibleType::VISIBLE;
    bool imageOverlayIsSelected_ = false;
    bool isLayoutModeChanged_ = false;
    bool isDragEnd_ = false;
    std::shared_ptr<OHOS::NWeb::NWebCursorInfo> nweb_cursorInfo_;
    bool isMouseLocked_ = false;
    OHOS::NWeb::CursorType cursorType_;
    float touchPointX = 0;
    float touchPointY = 0;
    bool isUsingCustomKeyboardAvoid_ = false;
    int64_t lastHeight_ = 0L;
    int64_t lastWidth_ = 0L;
    bool dragWindowFlag_ = false;
    bool isSetMouseDragMonitorState = false;
    double density_ = 0.0;
    int32_t densityCallbackId_ = 0;
    bool keyboardGetready_ = false;
    std::vector<uint32_t> pipController_;
    std::optional<int32_t> dataListNodeId_ = std::nullopt;
    bool isRegisterJsObject_ = false;

    MouseInfo mouseInfo_;

    // properties for AI data detector
    bool isAILinkMenuShow_ = false;
    RefPtr<WebDataDetectorAdapter> webDataDetectorAdapter_ = nullptr;
    TextDataDetectResult textDetectResult_;
    int lastDragOperation_;

    bool isRotating_ {false};
    int32_t rotationEndCallbackId_ = 0;

    WebBypassVsyncCondition webBypassVsyncCondition_ = WebBypassVsyncCondition::NONE;
    bool needSetDefaultBackgroundColor_ = false;
    GestureFocusMode gestureFocusMode_ = GestureFocusMode::DEFAULT;

protected:
    OnCreateMenuCallback onCreateMenuCallback_;
    OnMenuItemClickCallback onMenuItemClick_;
    OnPrepareMenuCallback onPrepareMenuCallback_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_WEB_WEB_PATTERN_H
