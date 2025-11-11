/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


// WARNING! THIS FILE IS AUTO-GENERATED, DO NOT MAKE CHANGES, THEY WILL BE LOST ON NEXT GENERATION!

import { CommonMethodModifier } from "./CommonMethodModifier"
import { AttributeModifier } from "#handwritten"
import { AttributeUpdaterFlag } from "./AttributeUpdaterFlag"
import { PeerNode } from "./PeerNode"
import { ArkWebPeer, MixedMode, JavaScriptProxy, CacheMode, WebDarkMode, WebMediaOptions, OverScrollMode, BlurOnKeyboardHideMode, OnPageEndEvent, OnPageBeginEvent, OnLoadStartedEvent, OnLoadFinishedEvent, OnProgressChangeEvent, OnTitleReceiveEvent, OnGeolocationShowEvent, OnAlertEvent, OnBeforeUnloadEvent, OnConfirmEvent, OnPromptEvent, OnConsoleEvent, OnErrorReceiveEvent, OnHttpErrorReceiveEvent, OnDownloadStartEvent, OnRefreshAccessedHistoryEvent, OnRenderExitedEvent, OnShowFileSelectorEvent, OnResourceLoadEvent, OnFullScreenEnterCallback, FullScreenEnterEvent, OnScaleChangeEvent, OnHttpAuthRequestEvent, OnInterceptRequestEvent, WebResourceResponse, OnPermissionRequestEvent, OnScreenCaptureRequestEvent, OnContextMenuShowEvent, OnContextMenuHideCallback, OnSearchResultReceiveEvent, OnScrollEvent, OnSslErrorEventReceiveEvent, OnSslErrorEventCallback, SslErrorEvent, OnClientAuthenticationEvent, OnWindowNewEvent, OnTouchIconUrlReceivedEvent, OnFaviconReceivedEvent, OnPageVisibleEvent, OnDataResubmittedEvent, OnAudioStateChangedEvent, OnFirstContentfulPaintEvent, OnFirstMeaningfulPaintCallback, FirstMeaningfulPaint, OnLargestContentfulPaintCallback, LargestContentfulPaint, OnLoadInterceptEvent, OnOverScrollEvent, OnSafeBrowsingCheckResultCallback, ThreatType, OnNavigationEntryCommittedCallback, LoadCommittedDetails, OnIntelligentTrackingPreventionCallback, IntelligentTrackingPreventionDetails, ScriptItem, WebLayoutMode, NestedScrollOptionsExt, NativeEmbedDataInfo, OnNativeEmbedVisibilityChangeCallback, NativeEmbedVisibilityInfo, NativeEmbedTouchInfo, OnOverrideUrlLoadingCallback, WebResourceRequest, NativeMediaPlayerConfig, OnRenderProcessNotRespondingCallback, RenderProcessNotRespondingData, OnRenderProcessRespondingCallback, OnViewportFitChangedCallback, ViewportFit, WebKeyboardCallback, WebKeyboardCallbackInfo, OnAdsBlockedCallback, AdsBlockedDetails, WebKeyboardAvoidMode, EmbedOptions, WebAttribute, WebElementType, WebResponseType, SelectionMenuOptionsExt } from "./component/web"
import { int32 } from "@koalaui/common"
import { ModifierState } from "./CommonModifier"
import { CommonMethod, KeyEvent, NestedScrollOptions } from "./component/common"
import { CopyOptions } from "./component/enums"
import { EditMenuOptions } from "./component/textCommon"
import { CustomBuilder } from "./component/builder"
export class WebModifier extends CommonMethodModifier implements WebAttribute,AttributeModifier<WebAttribute> {
    _instanceId: number = -1;
    _state: ModifierState = new ModifierState
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: WebAttribute): void { }
    applyPressedAttribute(instance: WebAttribute): void { }
    applyFocusedAttribute(instance: WebAttribute): void { }
    applyDisabledAttribute(instance: WebAttribute): void { }
    applySelectedAttribute(instance: WebAttribute): void { }
    _javaScriptAccess_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _javaScriptAccess_0_0value?: boolean | undefined
    _fileAccess_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fileAccess_0_0value?: boolean | undefined
    _onlineImageAccess_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onlineImageAccess_0_0value?: boolean | undefined
    _domStorageAccess_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _domStorageAccess_0_0value?: boolean | undefined
    _imageAccess_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _imageAccess_0_0value?: boolean | undefined
    _mixedMode_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _mixedMode_0_0value?: MixedMode | undefined
    _zoomAccess_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _zoomAccess_0_0value?: boolean | undefined
    _geolocationAccess_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _geolocationAccess_0_0value?: boolean | undefined
    _javaScriptProxy_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _javaScriptProxy_0_0value?: JavaScriptProxy | undefined
    _cacheMode_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _cacheMode_0_0value?: CacheMode | undefined
    _darkMode_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _darkMode_0_0value?: WebDarkMode | undefined
    _forceDarkAccess_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _forceDarkAccess_0_0value?: boolean | undefined
    _mediaOptions_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _mediaOptions_0_0value?: WebMediaOptions | undefined
    _overviewModeAccess_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _overviewModeAccess_0_0value?: boolean | undefined
    _overScrollMode_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _overScrollMode_0_0value?: OverScrollMode | undefined
    _blurOnKeyboardHideMode_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _blurOnKeyboardHideMode_0_0value?: BlurOnKeyboardHideMode | undefined
    _textZoomRatio_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _textZoomRatio_0_0value?: int32 | undefined
    _databaseAccess_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _databaseAccess_0_0value?: boolean | undefined
    _initialScale_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _initialScale_0_0value?: double | undefined
    _metaViewport_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _metaViewport_0_0value?: boolean | undefined
    _onPageEnd_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onPageEnd_0_0value?: ((value0: OnPageEndEvent) => void) | undefined
    _onPageBegin_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onPageBegin_0_0value?: ((value0: OnPageBeginEvent) => void) | undefined
    _onLoadStarted_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onLoadStarted_0_0value?: ((value0: OnLoadStartedEvent) => void) | undefined
    _onLoadFinished_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onLoadFinished_0_0value?: ((value0: OnLoadFinishedEvent) => void) | undefined
    _onProgressChange_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onProgressChange_0_0value?: ((value0: OnProgressChangeEvent) => void) | undefined
    _onTitleReceive_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onTitleReceive_0_0value?: ((value0: OnTitleReceiveEvent) => void) | undefined
    _onGeolocationHide_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onGeolocationHide_0_0value?: (() => void) | undefined
    _onGeolocationShow_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onGeolocationShow_0_0value?: ((value0: OnGeolocationShowEvent) => void) | undefined
    _onRequestSelected_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onRequestSelected_0_0value?: (() => void) | undefined
    _onAlert_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onAlert_0_0value?: ((value0: OnAlertEvent) => boolean) | undefined
    _onBeforeUnload_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onBeforeUnload_0_0value?: ((value0: OnBeforeUnloadEvent) => boolean) | undefined
    _onConfirm_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onConfirm_0_0value?: ((value0: OnConfirmEvent) => boolean) | undefined
    _onPrompt_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onPrompt_0_0value?: ((value0: OnPromptEvent) => boolean) | undefined
    _onConsole_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onConsole_0_0value?: ((value0: OnConsoleEvent) => boolean) | undefined
    _onErrorReceive_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onErrorReceive_0_0value?: ((value0: OnErrorReceiveEvent) => void) | undefined
    _onHttpErrorReceive_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onHttpErrorReceive_0_0value?: ((value0: OnHttpErrorReceiveEvent) => void) | undefined
    _onDownloadStart_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onDownloadStart_0_0value?: ((value0: OnDownloadStartEvent) => void) | undefined
    _onRefreshAccessedHistory_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onRefreshAccessedHistory_0_0value?: ((value0: OnRefreshAccessedHistoryEvent) => void) | undefined
    _onRenderExited_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onRenderExited_0_0value?: ((value0: OnRenderExitedEvent) => void) | undefined
    _onShowFileSelector_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onShowFileSelector_0_0value?: ((value0: OnShowFileSelectorEvent) => boolean) | undefined
    _onResourceLoad_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onResourceLoad_0_0value?: ((value0: OnResourceLoadEvent) => void) | undefined
    _onFullScreenExit_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onFullScreenExit_0_0value?: (() => void) | undefined
    _onFullScreenEnter_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onFullScreenEnter_0_0value?: OnFullScreenEnterCallback | undefined
    _onScaleChange_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onScaleChange_0_0value?: ((value0: OnScaleChangeEvent) => void) | undefined
    _onHttpAuthRequest_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onHttpAuthRequest_0_0value?: ((value0: OnHttpAuthRequestEvent) => boolean) | undefined
    _onInterceptRequest_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onInterceptRequest_0_0value?: ((value0: OnInterceptRequestEvent) => WebResourceResponse | null) | undefined
    _onPermissionRequest_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onPermissionRequest_0_0value?: ((value0: OnPermissionRequestEvent) => void) | undefined
    _onScreenCaptureRequest_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onScreenCaptureRequest_0_0value?: ((value0: OnScreenCaptureRequestEvent) => void) | undefined
    _onContextMenuShow_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onContextMenuShow_0_0value?: ((value0: OnContextMenuShowEvent) => boolean) | undefined
    _onContextMenuHide_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onContextMenuHide_0_0value?: OnContextMenuHideCallback | undefined
    _mediaPlayGestureAccess_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _mediaPlayGestureAccess_0_0value?: boolean | undefined
    _onSearchResultReceive_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onSearchResultReceive_0_0value?: ((value0: OnSearchResultReceiveEvent) => void) | undefined
    _onScroll_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onScroll_0_0value?: ((value0: OnScrollEvent) => void) | undefined
    _onSslErrorEventReceive_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onSslErrorEventReceive_0_0value?: ((value0: OnSslErrorEventReceiveEvent) => void) | undefined
    _onSslErrorEvent_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onSslErrorEvent_0_0value?: OnSslErrorEventCallback | undefined
    _onClientAuthenticationRequest_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onClientAuthenticationRequest_0_0value?: ((value0: OnClientAuthenticationEvent) => void) | undefined
    _onWindowNew_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onWindowNew_0_0value?: ((value0: OnWindowNewEvent) => void) | undefined
    _onWindowExit_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onWindowExit_0_0value?: (() => void) | undefined
    _multiWindowAccess_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _multiWindowAccess_0_0value?: boolean | undefined
    _onInterceptKeyEvent_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onInterceptKeyEvent_0_0value?: ((event: KeyEvent) => boolean) | undefined
    _webStandardFont_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _webStandardFont_0_0value?: string | undefined
    _webSerifFont_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _webSerifFont_0_0value?: string | undefined
    _webSansSerifFont_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _webSansSerifFont_0_0value?: string | undefined
    _webFixedFont_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _webFixedFont_0_0value?: string | undefined
    _webFantasyFont_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _webFantasyFont_0_0value?: string | undefined
    _webCursiveFont_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _webCursiveFont_0_0value?: string | undefined
    _defaultFixedFontSize_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _defaultFixedFontSize_0_0value?: int32 | undefined
    _defaultFontSize_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _defaultFontSize_0_0value?: int32 | undefined
    _minFontSize_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _minFontSize_0_0value?: int32 | undefined
    _minLogicalFontSize_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _minLogicalFontSize_0_0value?: int32 | undefined
    _defaultTextEncodingFormat_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _defaultTextEncodingFormat_0_0value?: string | undefined
    _forceDisplayScrollBar_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _forceDisplayScrollBar_0_0value?: boolean | undefined
    _blockNetwork_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _blockNetwork_0_0value?: boolean | undefined
    _horizontalScrollBarAccess_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _horizontalScrollBarAccess_0_0value?: boolean | undefined
    _verticalScrollBarAccess_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _verticalScrollBarAccess_0_0value?: boolean | undefined
    _onTouchIconUrlReceived_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onTouchIconUrlReceived_0_0value?: ((value0: OnTouchIconUrlReceivedEvent) => void) | undefined
    _onFaviconReceived_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onFaviconReceived_0_0value?: ((value0: OnFaviconReceivedEvent) => void) | undefined
    _onPageVisible_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onPageVisible_0_0value?: ((value0: OnPageVisibleEvent) => void) | undefined
    _onDataResubmitted_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onDataResubmitted_0_0value?: ((value0: OnDataResubmittedEvent) => void) | undefined
    _pinchSmooth_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _pinchSmooth_0_0value?: boolean | undefined
    _allowWindowOpenMethod_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _allowWindowOpenMethod_0_0value?: boolean | undefined
    _onAudioStateChanged_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onAudioStateChanged_0_0value?: ((value0: OnAudioStateChangedEvent) => void) | undefined
    _onFirstContentfulPaint_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onFirstContentfulPaint_0_0value?: ((value0: OnFirstContentfulPaintEvent) => void) | undefined
    _onFirstMeaningfulPaint_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onFirstMeaningfulPaint_0_0value?: OnFirstMeaningfulPaintCallback | undefined
    _onLargestContentfulPaint_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onLargestContentfulPaint_0_0value?: OnLargestContentfulPaintCallback | undefined
    _onLoadIntercept_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onLoadIntercept_0_0value?: ((value0: OnLoadInterceptEvent) => boolean) | undefined
    _onControllerAttached_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onControllerAttached_0_0value?: (() => void) | undefined
    _onOverScroll_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onOverScroll_0_0value?: ((value0: OnOverScrollEvent) => void) | undefined
    _onSafeBrowsingCheckResult_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onSafeBrowsingCheckResult_0_0value?: OnSafeBrowsingCheckResultCallback | undefined
    _onNavigationEntryCommitted_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onNavigationEntryCommitted_0_0value?: OnNavigationEntryCommittedCallback | undefined
    _onIntelligentTrackingPreventionResult_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onIntelligentTrackingPreventionResult_0_0value?: OnIntelligentTrackingPreventionCallback | undefined
    _javaScriptOnDocumentStart_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _javaScriptOnDocumentStart_0_0value?: Array<ScriptItem> | undefined
    _javaScriptOnDocumentEnd_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _javaScriptOnDocumentEnd_0_0value?: Array<ScriptItem> | undefined
    _layoutMode_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _layoutMode_0_0value?: WebLayoutMode | undefined
    _nestedScroll_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _nestedScroll_0_0value?: NestedScrollOptions | NestedScrollOptionsExt | undefined
    _enableNativeEmbedMode_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _enableNativeEmbedMode_0_0value?: boolean | undefined
    _onNativeEmbedLifecycleChange_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onNativeEmbedLifecycleChange_0_0value?: ((event: NativeEmbedDataInfo) => void) | undefined
    _onNativeEmbedVisibilityChange_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onNativeEmbedVisibilityChange_0_0value?: OnNativeEmbedVisibilityChangeCallback | undefined
    _onNativeEmbedGestureEvent_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onNativeEmbedGestureEvent_0_0value?: ((event: NativeEmbedTouchInfo) => void) | undefined
    _copyOptions_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _copyOptions_0_0value?: CopyOptions | undefined
    _onOverrideUrlLoading_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onOverrideUrlLoading_0_0value?: OnOverrideUrlLoadingCallback | undefined
    _textAutosizing_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _textAutosizing_0_0value?: boolean | undefined
    _enableNativeMediaPlayer_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _enableNativeMediaPlayer_0_0value?: NativeMediaPlayerConfig | undefined
    _onRenderProcessNotResponding_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onRenderProcessNotResponding_0_0value?: OnRenderProcessNotRespondingCallback | undefined
    _onRenderProcessResponding_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onRenderProcessResponding_0_0value?: OnRenderProcessRespondingCallback | undefined
    _onViewportFitChanged_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onViewportFitChanged_0_0value?: OnViewportFitChangedCallback | undefined
    _onInterceptKeyboardAttach_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onInterceptKeyboardAttach_0_0value?: WebKeyboardCallback | undefined
    _onAdsBlocked_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onAdsBlocked_0_0value?: OnAdsBlockedCallback | undefined
    _keyboardAvoidMode_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _keyboardAvoidMode_0_0value?: WebKeyboardAvoidMode | undefined
    _editMenuOptions_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _editMenuOptions_0_0value?: EditMenuOptions | undefined
    _enableHapticFeedback_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _enableHapticFeedback_0_0value?: boolean | undefined
    _optimizeParserBudget_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _optimizeParserBudget_0_0value?: boolean | undefined
    _enableFollowSystemFontWeight_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _enableFollowSystemFontWeight_0_0value?: boolean | undefined
    _enableWebAVSession_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _enableWebAVSession_0_0value?: boolean | undefined
    _runJavaScriptOnDocumentStart_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _runJavaScriptOnDocumentStart_0_0value?: Array<ScriptItem> | undefined
    _runJavaScriptOnDocumentEnd_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _runJavaScriptOnDocumentEnd_0_0value?: Array<ScriptItem> | undefined
    _runJavaScriptOnHeadEnd_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _runJavaScriptOnHeadEnd_0_0value?: Array<ScriptItem> | undefined
    _nativeEmbedOptions_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _nativeEmbedOptions_0_0value?: EmbedOptions | undefined
    _registerNativeEmbedRule_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _registerNativeEmbedRule_0_0value?: string | undefined
    _registerNativeEmbedRule_0_1value?: string | undefined
    _bindSelectionMenu_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _bindSelectionMenu_0_0value?: WebElementType | undefined
    _bindSelectionMenu_0_1value?: CustomBuilder | undefined
    _bindSelectionMenu_0_2value?: WebResponseType | undefined
    _bindSelectionMenu_0_3value?: SelectionMenuOptionsExt | undefined
    applyModifierPatch(node: PeerNode): void {
        this._state.addRef()
        super.applyModifierPatch(node)
        const peer = node as ArkWebPeer;
        if (this._javaScriptAccess_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._javaScriptAccess_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setJavaScriptAccessAttribute((this._javaScriptAccess_0_0value as boolean | undefined));
                    this._javaScriptAccess_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._javaScriptAccess_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._javaScriptAccess_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setJavaScriptAccessAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._fileAccess_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._fileAccess_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setFileAccessAttribute((this._fileAccess_0_0value as boolean | undefined));
                    this._fileAccess_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._fileAccess_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._fileAccess_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setFileAccessAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._onlineImageAccess_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onlineImageAccess_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnlineImageAccessAttribute((this._onlineImageAccess_0_0value as boolean | undefined));
                    this._onlineImageAccess_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onlineImageAccess_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onlineImageAccess_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnlineImageAccessAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._domStorageAccess_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._domStorageAccess_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setDomStorageAccessAttribute((this._domStorageAccess_0_0value as boolean | undefined));
                    this._domStorageAccess_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._domStorageAccess_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._domStorageAccess_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setDomStorageAccessAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._imageAccess_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._imageAccess_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setImageAccessAttribute((this._imageAccess_0_0value as boolean | undefined));
                    this._imageAccess_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._imageAccess_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._imageAccess_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setImageAccessAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._mixedMode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._mixedMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setMixedModeAttribute((this._mixedMode_0_0value as MixedMode | undefined));
                    this._mixedMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._mixedMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._mixedMode_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setMixedModeAttribute((undefined as MixedMode | undefined));
                }
            }
        }
        if (this._zoomAccess_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._zoomAccess_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setZoomAccessAttribute((this._zoomAccess_0_0value as boolean | undefined));
                    this._zoomAccess_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._zoomAccess_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._zoomAccess_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setZoomAccessAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._geolocationAccess_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._geolocationAccess_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setGeolocationAccessAttribute((this._geolocationAccess_0_0value as boolean | undefined));
                    this._geolocationAccess_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._geolocationAccess_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._geolocationAccess_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setGeolocationAccessAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._javaScriptProxy_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._javaScriptProxy_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setJavaScriptProxyAttribute((this._javaScriptProxy_0_0value as JavaScriptProxy | undefined));
                    this._javaScriptProxy_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._javaScriptProxy_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._javaScriptProxy_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setJavaScriptProxyAttribute((undefined as JavaScriptProxy | undefined));
                }
            }
        }
        if (this._cacheMode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._cacheMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setCacheModeAttribute((this._cacheMode_0_0value as CacheMode | undefined));
                    this._cacheMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._cacheMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._cacheMode_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setCacheModeAttribute((undefined as CacheMode | undefined));
                }
            }
        }
        if (this._darkMode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._darkMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setDarkModeAttribute((this._darkMode_0_0value as WebDarkMode | undefined));
                    this._darkMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._darkMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._darkMode_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setDarkModeAttribute((undefined as WebDarkMode | undefined));
                }
            }
        }
        if (this._forceDarkAccess_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._forceDarkAccess_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setForceDarkAccessAttribute((this._forceDarkAccess_0_0value as boolean | undefined));
                    this._forceDarkAccess_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._forceDarkAccess_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._forceDarkAccess_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setForceDarkAccessAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._mediaOptions_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._mediaOptions_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setMediaOptionsAttribute((this._mediaOptions_0_0value as WebMediaOptions | undefined));
                    this._mediaOptions_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._mediaOptions_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._mediaOptions_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setMediaOptionsAttribute((undefined as WebMediaOptions | undefined));
                }
            }
        }
        if (this._overviewModeAccess_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._overviewModeAccess_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOverviewModeAccessAttribute((this._overviewModeAccess_0_0value as boolean | undefined));
                    this._overviewModeAccess_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._overviewModeAccess_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._overviewModeAccess_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOverviewModeAccessAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._overScrollMode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._overScrollMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOverScrollModeAttribute((this._overScrollMode_0_0value as OverScrollMode | undefined));
                    this._overScrollMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._overScrollMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._overScrollMode_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOverScrollModeAttribute((undefined as OverScrollMode | undefined));
                }
            }
        }
        if (this._blurOnKeyboardHideMode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._blurOnKeyboardHideMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setBlurOnKeyboardHideModeAttribute((this._blurOnKeyboardHideMode_0_0value as BlurOnKeyboardHideMode | undefined));
                    this._blurOnKeyboardHideMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._blurOnKeyboardHideMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._blurOnKeyboardHideMode_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setBlurOnKeyboardHideModeAttribute((undefined as BlurOnKeyboardHideMode | undefined));
                }
            }
        }
        if (this._textZoomRatio_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._textZoomRatio_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setTextZoomRatioAttribute((this._textZoomRatio_0_0value as int32 | undefined));
                    this._textZoomRatio_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._textZoomRatio_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._textZoomRatio_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setTextZoomRatioAttribute((undefined as int32 | undefined));
                }
            }
        }
        if (this._databaseAccess_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._databaseAccess_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setDatabaseAccessAttribute((this._databaseAccess_0_0value as boolean | undefined));
                    this._databaseAccess_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._databaseAccess_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._databaseAccess_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setDatabaseAccessAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._initialScale_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._initialScale_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setInitialScaleAttribute((this._initialScale_0_0value as double | undefined));
                    this._initialScale_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._initialScale_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._initialScale_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setInitialScaleAttribute((undefined as double | undefined));
                }
            }
        }
        if (this._metaViewport_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._metaViewport_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setMetaViewportAttribute((this._metaViewport_0_0value as boolean | undefined));
                    this._metaViewport_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._metaViewport_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._metaViewport_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setMetaViewportAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._onPageEnd_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onPageEnd_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnPageEndAttribute((this._onPageEnd_0_0value as ((value0: OnPageEndEvent) => void) | undefined));
                    this._onPageEnd_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onPageEnd_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onPageEnd_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnPageEndAttribute((undefined as ((value0: OnPageEndEvent) => void) | undefined));
                }
            }
        }
        if (this._onPageBegin_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onPageBegin_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnPageBeginAttribute((this._onPageBegin_0_0value as ((value0: OnPageBeginEvent) => void) | undefined));
                    this._onPageBegin_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onPageBegin_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onPageBegin_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnPageBeginAttribute((undefined as ((value0: OnPageBeginEvent) => void) | undefined));
                }
            }
        }
        if (this._onLoadStarted_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onLoadStarted_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnLoadStartedAttribute((this._onLoadStarted_0_0value as ((value0: OnLoadStartedEvent) => void) | undefined));
                    this._onLoadStarted_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onLoadStarted_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onLoadStarted_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnLoadStartedAttribute((undefined as ((value0: OnLoadStartedEvent) => void) | undefined));
                }
            }
        }
        if (this._onLoadFinished_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onLoadFinished_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnLoadFinishedAttribute((this._onLoadFinished_0_0value as ((value0: OnLoadFinishedEvent) => void) | undefined));
                    this._onLoadFinished_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onLoadFinished_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onLoadFinished_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnLoadFinishedAttribute((undefined as ((value0: OnLoadFinishedEvent) => void) | undefined));
                }
            }
        }
        if (this._onProgressChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onProgressChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnProgressChangeAttribute((this._onProgressChange_0_0value as ((value0: OnProgressChangeEvent) => void) | undefined));
                    this._onProgressChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onProgressChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onProgressChange_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnProgressChangeAttribute((undefined as ((value0: OnProgressChangeEvent) => void) | undefined));
                }
            }
        }
        if (this._onTitleReceive_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onTitleReceive_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnTitleReceiveAttribute((this._onTitleReceive_0_0value as ((value0: OnTitleReceiveEvent) => void) | undefined));
                    this._onTitleReceive_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onTitleReceive_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onTitleReceive_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnTitleReceiveAttribute((undefined as ((value0: OnTitleReceiveEvent) => void) | undefined));
                }
            }
        }
        if (this._onGeolocationHide_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onGeolocationHide_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnGeolocationHideAttribute((this._onGeolocationHide_0_0value as (() => void) | undefined));
                    this._onGeolocationHide_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onGeolocationHide_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onGeolocationHide_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnGeolocationHideAttribute((undefined as (() => void) | undefined));
                }
            }
        }
        if (this._onGeolocationShow_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onGeolocationShow_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnGeolocationShowAttribute((this._onGeolocationShow_0_0value as ((value0: OnGeolocationShowEvent) => void) | undefined));
                    this._onGeolocationShow_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onGeolocationShow_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onGeolocationShow_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnGeolocationShowAttribute((undefined as ((value0: OnGeolocationShowEvent) => void) | undefined));
                }
            }
        }
        if (this._onRequestSelected_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onRequestSelected_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnRequestSelectedAttribute((this._onRequestSelected_0_0value as (() => void) | undefined));
                    this._onRequestSelected_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onRequestSelected_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onRequestSelected_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnRequestSelectedAttribute((undefined as (() => void) | undefined));
                }
            }
        }
        if (this._onAlert_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onAlert_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnAlertAttribute((this._onAlert_0_0value as ((value0: OnAlertEvent) => boolean) | undefined));
                    this._onAlert_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onAlert_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onAlert_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnAlertAttribute((undefined as ((value0: OnAlertEvent) => boolean) | undefined));
                }
            }
        }
        if (this._onBeforeUnload_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onBeforeUnload_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnBeforeUnloadAttribute((this._onBeforeUnload_0_0value as ((value0: OnBeforeUnloadEvent) => boolean) | undefined));
                    this._onBeforeUnload_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onBeforeUnload_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onBeforeUnload_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnBeforeUnloadAttribute((undefined as ((value0: OnBeforeUnloadEvent) => boolean) | undefined));
                }
            }
        }
        if (this._onConfirm_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onConfirm_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnConfirmAttribute((this._onConfirm_0_0value as ((value0: OnConfirmEvent) => boolean) | undefined));
                    this._onConfirm_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onConfirm_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onConfirm_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnConfirmAttribute((undefined as ((value0: OnConfirmEvent) => boolean) | undefined));
                }
            }
        }
        if (this._onPrompt_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onPrompt_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnPromptAttribute((this._onPrompt_0_0value as ((value0: OnPromptEvent) => boolean) | undefined));
                    this._onPrompt_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onPrompt_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onPrompt_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnPromptAttribute((undefined as ((value0: OnPromptEvent) => boolean) | undefined));
                }
            }
        }
        if (this._onConsole_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onConsole_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnConsoleAttribute((this._onConsole_0_0value as ((value0: OnConsoleEvent) => boolean) | undefined));
                    this._onConsole_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onConsole_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onConsole_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnConsoleAttribute((undefined as ((value0: OnConsoleEvent) => boolean) | undefined));
                }
            }
        }
        if (this._onErrorReceive_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onErrorReceive_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnErrorReceiveAttribute((this._onErrorReceive_0_0value as ((value0: OnErrorReceiveEvent) => void) | undefined));
                    this._onErrorReceive_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onErrorReceive_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onErrorReceive_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnErrorReceiveAttribute((undefined as ((value0: OnErrorReceiveEvent) => void) | undefined));
                }
            }
        }
        if (this._onHttpErrorReceive_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onHttpErrorReceive_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnHttpErrorReceiveAttribute((this._onHttpErrorReceive_0_0value as ((value0: OnHttpErrorReceiveEvent) => void) | undefined));
                    this._onHttpErrorReceive_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onHttpErrorReceive_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onHttpErrorReceive_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnHttpErrorReceiveAttribute((undefined as ((value0: OnHttpErrorReceiveEvent) => void) | undefined));
                }
            }
        }
        if (this._onDownloadStart_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onDownloadStart_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnDownloadStartAttribute((this._onDownloadStart_0_0value as ((value0: OnDownloadStartEvent) => void) | undefined));
                    this._onDownloadStart_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onDownloadStart_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onDownloadStart_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnDownloadStartAttribute((undefined as ((value0: OnDownloadStartEvent) => void) | undefined));
                }
            }
        }
        if (this._onRefreshAccessedHistory_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onRefreshAccessedHistory_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnRefreshAccessedHistoryAttribute((this._onRefreshAccessedHistory_0_0value as ((value0: OnRefreshAccessedHistoryEvent) => void) | undefined));
                    this._onRefreshAccessedHistory_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onRefreshAccessedHistory_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onRefreshAccessedHistory_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnRefreshAccessedHistoryAttribute((undefined as ((value0: OnRefreshAccessedHistoryEvent) => void) | undefined));
                }
            }
        }
        if (this._onRenderExited_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onRenderExited_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnRenderExitedAttribute((this._onRenderExited_0_0value as ((value0: OnRenderExitedEvent) => void) | undefined));
                    this._onRenderExited_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onRenderExited_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onRenderExited_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnRenderExitedAttribute((undefined as ((value0: OnRenderExitedEvent) => void) | undefined));
                }
            }
        }
        if (this._onShowFileSelector_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onShowFileSelector_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnShowFileSelectorAttribute((this._onShowFileSelector_0_0value as ((value0: OnShowFileSelectorEvent) => boolean) | undefined));
                    this._onShowFileSelector_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onShowFileSelector_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onShowFileSelector_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnShowFileSelectorAttribute((undefined as ((value0: OnShowFileSelectorEvent) => boolean) | undefined));
                }
            }
        }
        if (this._onResourceLoad_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onResourceLoad_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnResourceLoadAttribute((this._onResourceLoad_0_0value as ((value0: OnResourceLoadEvent) => void) | undefined));
                    this._onResourceLoad_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onResourceLoad_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onResourceLoad_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnResourceLoadAttribute((undefined as ((value0: OnResourceLoadEvent) => void) | undefined));
                }
            }
        }
        if (this._onFullScreenExit_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onFullScreenExit_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnFullScreenExitAttribute((this._onFullScreenExit_0_0value as (() => void) | undefined));
                    this._onFullScreenExit_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onFullScreenExit_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onFullScreenExit_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnFullScreenExitAttribute((undefined as (() => void) | undefined));
                }
            }
        }
        if (this._onFullScreenEnter_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onFullScreenEnter_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnFullScreenEnterAttribute((this._onFullScreenEnter_0_0value as OnFullScreenEnterCallback | undefined));
                    this._onFullScreenEnter_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onFullScreenEnter_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onFullScreenEnter_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnFullScreenEnterAttribute((undefined as OnFullScreenEnterCallback | undefined));
                }
            }
        }
        if (this._onScaleChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onScaleChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnScaleChangeAttribute((this._onScaleChange_0_0value as ((value0: OnScaleChangeEvent) => void) | undefined));
                    this._onScaleChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onScaleChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onScaleChange_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnScaleChangeAttribute((undefined as ((value0: OnScaleChangeEvent) => void) | undefined));
                }
            }
        }
        if (this._onHttpAuthRequest_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onHttpAuthRequest_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnHttpAuthRequestAttribute((this._onHttpAuthRequest_0_0value as ((value0: OnHttpAuthRequestEvent) => boolean) | undefined));
                    this._onHttpAuthRequest_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onHttpAuthRequest_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onHttpAuthRequest_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnHttpAuthRequestAttribute((undefined as ((value0: OnHttpAuthRequestEvent) => boolean) | undefined));
                }
            }
        }
        if (this._onInterceptRequest_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onInterceptRequest_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnInterceptRequestAttribute((this._onInterceptRequest_0_0value as ((value0: OnInterceptRequestEvent) => WebResourceResponse | null) | undefined));
                    this._onInterceptRequest_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onInterceptRequest_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onInterceptRequest_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnInterceptRequestAttribute((undefined as ((value0: OnInterceptRequestEvent) => WebResourceResponse | null) | undefined));
                }
            }
        }
        if (this._onPermissionRequest_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onPermissionRequest_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnPermissionRequestAttribute((this._onPermissionRequest_0_0value as ((value0: OnPermissionRequestEvent) => void) | undefined));
                    this._onPermissionRequest_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onPermissionRequest_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onPermissionRequest_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnPermissionRequestAttribute((undefined as ((value0: OnPermissionRequestEvent) => void) | undefined));
                }
            }
        }
        if (this._onScreenCaptureRequest_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onScreenCaptureRequest_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnScreenCaptureRequestAttribute((this._onScreenCaptureRequest_0_0value as ((value0: OnScreenCaptureRequestEvent) => void) | undefined));
                    this._onScreenCaptureRequest_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onScreenCaptureRequest_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onScreenCaptureRequest_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnScreenCaptureRequestAttribute((undefined as ((value0: OnScreenCaptureRequestEvent) => void) | undefined));
                }
            }
        }
        if (this._onContextMenuShow_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onContextMenuShow_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnContextMenuShowAttribute((this._onContextMenuShow_0_0value as ((value0: OnContextMenuShowEvent) => boolean) | undefined));
                    this._onContextMenuShow_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onContextMenuShow_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onContextMenuShow_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnContextMenuShowAttribute((undefined as ((value0: OnContextMenuShowEvent) => boolean) | undefined));
                }
            }
        }
        if (this._onContextMenuHide_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onContextMenuHide_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnContextMenuHideAttribute((this._onContextMenuHide_0_0value as OnContextMenuHideCallback | undefined));
                    this._onContextMenuHide_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onContextMenuHide_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onContextMenuHide_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnContextMenuHideAttribute((undefined as OnContextMenuHideCallback | undefined));
                }
            }
        }
        if (this._mediaPlayGestureAccess_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._mediaPlayGestureAccess_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setMediaPlayGestureAccessAttribute((this._mediaPlayGestureAccess_0_0value as boolean | undefined));
                    this._mediaPlayGestureAccess_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._mediaPlayGestureAccess_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._mediaPlayGestureAccess_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setMediaPlayGestureAccessAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._onSearchResultReceive_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onSearchResultReceive_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnSearchResultReceiveAttribute((this._onSearchResultReceive_0_0value as ((value0: OnSearchResultReceiveEvent) => void) | undefined));
                    this._onSearchResultReceive_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onSearchResultReceive_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onSearchResultReceive_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnSearchResultReceiveAttribute((undefined as ((value0: OnSearchResultReceiveEvent) => void) | undefined));
                }
            }
        }
        if (this._onScroll_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onScroll_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnScrollAttribute((this._onScroll_0_0value as ((value0: OnScrollEvent) => void) | undefined));
                    this._onScroll_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onScroll_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onScroll_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnScrollAttribute((undefined as ((value0: OnScrollEvent) => void) | undefined));
                }
            }
        }
        if (this._onSslErrorEventReceive_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onSslErrorEventReceive_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnSslErrorEventReceiveAttribute((this._onSslErrorEventReceive_0_0value as ((value0: OnSslErrorEventReceiveEvent) => void) | undefined));
                    this._onSslErrorEventReceive_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onSslErrorEventReceive_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onSslErrorEventReceive_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnSslErrorEventReceiveAttribute((undefined as ((value0: OnSslErrorEventReceiveEvent) => void) | undefined));
                }
            }
        }
        if (this._onSslErrorEvent_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onSslErrorEvent_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnSslErrorEventAttribute((this._onSslErrorEvent_0_0value as OnSslErrorEventCallback | undefined));
                    this._onSslErrorEvent_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onSslErrorEvent_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onSslErrorEvent_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnSslErrorEventAttribute((undefined as OnSslErrorEventCallback | undefined));
                }
            }
        }
        if (this._onClientAuthenticationRequest_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onClientAuthenticationRequest_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnClientAuthenticationRequestAttribute((this._onClientAuthenticationRequest_0_0value as ((value0: OnClientAuthenticationEvent) => void) | undefined));
                    this._onClientAuthenticationRequest_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onClientAuthenticationRequest_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onClientAuthenticationRequest_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnClientAuthenticationRequestAttribute((undefined as ((value0: OnClientAuthenticationEvent) => void) | undefined));
                }
            }
        }
        if (this._onWindowNew_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onWindowNew_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnWindowNewAttribute((this._onWindowNew_0_0value as ((value0: OnWindowNewEvent) => void) | undefined));
                    this._onWindowNew_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onWindowNew_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onWindowNew_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnWindowNewAttribute((undefined as ((value0: OnWindowNewEvent) => void) | undefined));
                }
            }
        }
        if (this._onWindowExit_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onWindowExit_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnWindowExitAttribute((this._onWindowExit_0_0value as (() => void) | undefined));
                    this._onWindowExit_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onWindowExit_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onWindowExit_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnWindowExitAttribute((undefined as (() => void) | undefined));
                }
            }
        }
        if (this._multiWindowAccess_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._multiWindowAccess_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setMultiWindowAccessAttribute((this._multiWindowAccess_0_0value as boolean | undefined));
                    this._multiWindowAccess_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._multiWindowAccess_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._multiWindowAccess_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setMultiWindowAccessAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._onInterceptKeyEvent_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onInterceptKeyEvent_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnInterceptKeyEventAttribute((this._onInterceptKeyEvent_0_0value as ((event: KeyEvent) => boolean) | undefined));
                    this._onInterceptKeyEvent_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onInterceptKeyEvent_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onInterceptKeyEvent_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnInterceptKeyEventAttribute((undefined as ((event: KeyEvent) => boolean) | undefined));
                }
            }
        }
        if (this._webStandardFont_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._webStandardFont_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setWebStandardFontAttribute((this._webStandardFont_0_0value as string | undefined));
                    this._webStandardFont_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._webStandardFont_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._webStandardFont_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setWebStandardFontAttribute((undefined as string | undefined));
                }
            }
        }
        if (this._webSerifFont_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._webSerifFont_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setWebSerifFontAttribute((this._webSerifFont_0_0value as string | undefined));
                    this._webSerifFont_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._webSerifFont_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._webSerifFont_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setWebSerifFontAttribute((undefined as string | undefined));
                }
            }
        }
        if (this._webSansSerifFont_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._webSansSerifFont_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setWebSansSerifFontAttribute((this._webSansSerifFont_0_0value as string | undefined));
                    this._webSansSerifFont_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._webSansSerifFont_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._webSansSerifFont_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setWebSansSerifFontAttribute((undefined as string | undefined));
                }
            }
        }
        if (this._webFixedFont_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._webFixedFont_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setWebFixedFontAttribute((this._webFixedFont_0_0value as string | undefined));
                    this._webFixedFont_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._webFixedFont_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._webFixedFont_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setWebFixedFontAttribute((undefined as string | undefined));
                }
            }
        }
        if (this._webFantasyFont_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._webFantasyFont_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setWebFantasyFontAttribute((this._webFantasyFont_0_0value as string | undefined));
                    this._webFantasyFont_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._webFantasyFont_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._webFantasyFont_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setWebFantasyFontAttribute((undefined as string | undefined));
                }
            }
        }
        if (this._webCursiveFont_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._webCursiveFont_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setWebCursiveFontAttribute((this._webCursiveFont_0_0value as string | undefined));
                    this._webCursiveFont_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._webCursiveFont_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._webCursiveFont_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setWebCursiveFontAttribute((undefined as string | undefined));
                }
            }
        }
        if (this._defaultFixedFontSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._defaultFixedFontSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setDefaultFixedFontSizeAttribute((this._defaultFixedFontSize_0_0value as int32 | undefined));
                    this._defaultFixedFontSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._defaultFixedFontSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._defaultFixedFontSize_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setDefaultFixedFontSizeAttribute((undefined as int32 | undefined));
                }
            }
        }
        if (this._defaultFontSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._defaultFontSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setDefaultFontSizeAttribute((this._defaultFontSize_0_0value as int32 | undefined));
                    this._defaultFontSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._defaultFontSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._defaultFontSize_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setDefaultFontSizeAttribute((undefined as int32 | undefined));
                }
            }
        }
        if (this._minFontSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._minFontSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setMinFontSizeAttribute((this._minFontSize_0_0value as int32 | undefined));
                    this._minFontSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._minFontSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._minFontSize_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setMinFontSizeAttribute((undefined as int32 | undefined));
                }
            }
        }
        if (this._minLogicalFontSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._minLogicalFontSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setMinLogicalFontSizeAttribute((this._minLogicalFontSize_0_0value as int32 | undefined));
                    this._minLogicalFontSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._minLogicalFontSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._minLogicalFontSize_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setMinLogicalFontSizeAttribute((undefined as int32 | undefined));
                }
            }
        }
        if (this._defaultTextEncodingFormat_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._defaultTextEncodingFormat_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setDefaultTextEncodingFormatAttribute((this._defaultTextEncodingFormat_0_0value as string | undefined));
                    this._defaultTextEncodingFormat_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._defaultTextEncodingFormat_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._defaultTextEncodingFormat_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setDefaultTextEncodingFormatAttribute((undefined as string | undefined));
                }
            }
        }
        if (this._forceDisplayScrollBar_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._forceDisplayScrollBar_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setForceDisplayScrollBarAttribute((this._forceDisplayScrollBar_0_0value as boolean | undefined));
                    this._forceDisplayScrollBar_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._forceDisplayScrollBar_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._forceDisplayScrollBar_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setForceDisplayScrollBarAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._blockNetwork_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._blockNetwork_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setBlockNetworkAttribute((this._blockNetwork_0_0value as boolean | undefined));
                    this._blockNetwork_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._blockNetwork_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._blockNetwork_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setBlockNetworkAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._horizontalScrollBarAccess_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._horizontalScrollBarAccess_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setHorizontalScrollBarAccessAttribute((this._horizontalScrollBarAccess_0_0value as boolean | undefined));
                    this._horizontalScrollBarAccess_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._horizontalScrollBarAccess_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._horizontalScrollBarAccess_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setHorizontalScrollBarAccessAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._verticalScrollBarAccess_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._verticalScrollBarAccess_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setVerticalScrollBarAccessAttribute((this._verticalScrollBarAccess_0_0value as boolean | undefined));
                    this._verticalScrollBarAccess_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._verticalScrollBarAccess_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._verticalScrollBarAccess_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setVerticalScrollBarAccessAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._onTouchIconUrlReceived_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onTouchIconUrlReceived_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnTouchIconUrlReceivedAttribute((this._onTouchIconUrlReceived_0_0value as ((value0: OnTouchIconUrlReceivedEvent) => void) | undefined));
                    this._onTouchIconUrlReceived_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onTouchIconUrlReceived_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onTouchIconUrlReceived_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnTouchIconUrlReceivedAttribute((undefined as ((value0: OnTouchIconUrlReceivedEvent) => void) | undefined));
                }
            }
        }
        if (this._onFaviconReceived_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onFaviconReceived_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnFaviconReceivedAttribute((this._onFaviconReceived_0_0value as ((value0: OnFaviconReceivedEvent) => void) | undefined));
                    this._onFaviconReceived_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onFaviconReceived_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onFaviconReceived_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnFaviconReceivedAttribute((undefined as ((value0: OnFaviconReceivedEvent) => void) | undefined));
                }
            }
        }
        if (this._onPageVisible_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onPageVisible_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnPageVisibleAttribute((this._onPageVisible_0_0value as ((value0: OnPageVisibleEvent) => void) | undefined));
                    this._onPageVisible_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onPageVisible_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onPageVisible_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnPageVisibleAttribute((undefined as ((value0: OnPageVisibleEvent) => void) | undefined));
                }
            }
        }
        if (this._onDataResubmitted_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onDataResubmitted_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnDataResubmittedAttribute((this._onDataResubmitted_0_0value as ((value0: OnDataResubmittedEvent) => void) | undefined));
                    this._onDataResubmitted_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onDataResubmitted_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onDataResubmitted_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnDataResubmittedAttribute((undefined as ((value0: OnDataResubmittedEvent) => void) | undefined));
                }
            }
        }
        if (this._pinchSmooth_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._pinchSmooth_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setPinchSmoothAttribute((this._pinchSmooth_0_0value as boolean | undefined));
                    this._pinchSmooth_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._pinchSmooth_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._pinchSmooth_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setPinchSmoothAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._allowWindowOpenMethod_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._allowWindowOpenMethod_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setAllowWindowOpenMethodAttribute((this._allowWindowOpenMethod_0_0value as boolean | undefined));
                    this._allowWindowOpenMethod_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._allowWindowOpenMethod_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._allowWindowOpenMethod_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setAllowWindowOpenMethodAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._onAudioStateChanged_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onAudioStateChanged_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnAudioStateChangedAttribute((this._onAudioStateChanged_0_0value as ((value0: OnAudioStateChangedEvent) => void) | undefined));
                    this._onAudioStateChanged_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onAudioStateChanged_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onAudioStateChanged_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnAudioStateChangedAttribute((undefined as ((value0: OnAudioStateChangedEvent) => void) | undefined));
                }
            }
        }
        if (this._onFirstContentfulPaint_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onFirstContentfulPaint_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnFirstContentfulPaintAttribute((this._onFirstContentfulPaint_0_0value as ((value0: OnFirstContentfulPaintEvent) => void) | undefined));
                    this._onFirstContentfulPaint_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onFirstContentfulPaint_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onFirstContentfulPaint_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnFirstContentfulPaintAttribute((undefined as ((value0: OnFirstContentfulPaintEvent) => void) | undefined));
                }
            }
        }
        if (this._onFirstMeaningfulPaint_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onFirstMeaningfulPaint_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnFirstMeaningfulPaintAttribute((this._onFirstMeaningfulPaint_0_0value as OnFirstMeaningfulPaintCallback | undefined));
                    this._onFirstMeaningfulPaint_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onFirstMeaningfulPaint_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onFirstMeaningfulPaint_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnFirstMeaningfulPaintAttribute((undefined as OnFirstMeaningfulPaintCallback | undefined));
                }
            }
        }
        if (this._onLargestContentfulPaint_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onLargestContentfulPaint_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnLargestContentfulPaintAttribute((this._onLargestContentfulPaint_0_0value as OnLargestContentfulPaintCallback | undefined));
                    this._onLargestContentfulPaint_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onLargestContentfulPaint_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onLargestContentfulPaint_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnLargestContentfulPaintAttribute((undefined as OnLargestContentfulPaintCallback | undefined));
                }
            }
        }
        if (this._onLoadIntercept_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onLoadIntercept_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnLoadInterceptAttribute((this._onLoadIntercept_0_0value as ((value0: OnLoadInterceptEvent) => boolean) | undefined));
                    this._onLoadIntercept_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onLoadIntercept_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onLoadIntercept_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnLoadInterceptAttribute((undefined as ((value0: OnLoadInterceptEvent) => boolean) | undefined));
                }
            }
        }
        if (this._onControllerAttached_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onControllerAttached_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnControllerAttachedAttribute((this._onControllerAttached_0_0value as (() => void) | undefined));
                    this._onControllerAttached_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onControllerAttached_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onControllerAttached_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnControllerAttachedAttribute((undefined as (() => void) | undefined));
                }
            }
        }
        if (this._onOverScroll_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onOverScroll_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnOverScrollAttribute((this._onOverScroll_0_0value as ((value0: OnOverScrollEvent) => void) | undefined));
                    this._onOverScroll_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onOverScroll_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onOverScroll_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnOverScrollAttribute((undefined as ((value0: OnOverScrollEvent) => void) | undefined));
                }
            }
        }
        if (this._onSafeBrowsingCheckResult_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onSafeBrowsingCheckResult_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnSafeBrowsingCheckResultAttribute((this._onSafeBrowsingCheckResult_0_0value as OnSafeBrowsingCheckResultCallback | undefined));
                    this._onSafeBrowsingCheckResult_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onSafeBrowsingCheckResult_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onSafeBrowsingCheckResult_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnSafeBrowsingCheckResultAttribute((undefined as OnSafeBrowsingCheckResultCallback | undefined));
                }
            }
        }
        if (this._onNavigationEntryCommitted_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onNavigationEntryCommitted_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnNavigationEntryCommittedAttribute((this._onNavigationEntryCommitted_0_0value as OnNavigationEntryCommittedCallback | undefined));
                    this._onNavigationEntryCommitted_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onNavigationEntryCommitted_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onNavigationEntryCommitted_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnNavigationEntryCommittedAttribute((undefined as OnNavigationEntryCommittedCallback | undefined));
                }
            }
        }
        if (this._onIntelligentTrackingPreventionResult_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onIntelligentTrackingPreventionResult_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnIntelligentTrackingPreventionResultAttribute((this._onIntelligentTrackingPreventionResult_0_0value as OnIntelligentTrackingPreventionCallback | undefined));
                    this._onIntelligentTrackingPreventionResult_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onIntelligentTrackingPreventionResult_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onIntelligentTrackingPreventionResult_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnIntelligentTrackingPreventionResultAttribute((undefined as OnIntelligentTrackingPreventionCallback | undefined));
                }
            }
        }
        if (this._javaScriptOnDocumentStart_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._javaScriptOnDocumentStart_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setJavaScriptOnDocumentStartAttribute((this._javaScriptOnDocumentStart_0_0value as Array<ScriptItem> | undefined));
                    this._javaScriptOnDocumentStart_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._javaScriptOnDocumentStart_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._javaScriptOnDocumentStart_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setJavaScriptOnDocumentStartAttribute((undefined as Array<ScriptItem> | undefined));
                }
            }
        }
        if (this._javaScriptOnDocumentEnd_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._javaScriptOnDocumentEnd_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setJavaScriptOnDocumentEndAttribute((this._javaScriptOnDocumentEnd_0_0value as Array<ScriptItem> | undefined));
                    this._javaScriptOnDocumentEnd_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._javaScriptOnDocumentEnd_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._javaScriptOnDocumentEnd_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setJavaScriptOnDocumentEndAttribute((undefined as Array<ScriptItem> | undefined));
                }
            }
        }
        if (this._layoutMode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._layoutMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setLayoutModeAttribute((this._layoutMode_0_0value as WebLayoutMode | undefined));
                    this._layoutMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._layoutMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._layoutMode_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setLayoutModeAttribute((undefined as WebLayoutMode | undefined));
                }
            }
        }
        if (this._nestedScroll_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._nestedScroll_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setNestedScrollAttribute((this._nestedScroll_0_0value as NestedScrollOptions | NestedScrollOptionsExt | undefined));
                    this._nestedScroll_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._nestedScroll_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._nestedScroll_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setNestedScrollAttribute((undefined as NestedScrollOptions | NestedScrollOptionsExt | undefined));
                }
            }
        }
        if (this._enableNativeEmbedMode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._enableNativeEmbedMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setEnableNativeEmbedModeAttribute((this._enableNativeEmbedMode_0_0value as boolean | undefined));
                    this._enableNativeEmbedMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._enableNativeEmbedMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._enableNativeEmbedMode_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setEnableNativeEmbedModeAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._onNativeEmbedLifecycleChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onNativeEmbedLifecycleChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnNativeEmbedLifecycleChangeAttribute((this._onNativeEmbedLifecycleChange_0_0value as ((event: NativeEmbedDataInfo) => void) | undefined));
                    this._onNativeEmbedLifecycleChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onNativeEmbedLifecycleChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onNativeEmbedLifecycleChange_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnNativeEmbedLifecycleChangeAttribute((undefined as ((event: NativeEmbedDataInfo) => void) | undefined));
                }
            }
        }
        if (this._onNativeEmbedVisibilityChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onNativeEmbedVisibilityChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnNativeEmbedVisibilityChangeAttribute((this._onNativeEmbedVisibilityChange_0_0value as OnNativeEmbedVisibilityChangeCallback | undefined));
                    this._onNativeEmbedVisibilityChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onNativeEmbedVisibilityChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onNativeEmbedVisibilityChange_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnNativeEmbedVisibilityChangeAttribute((undefined as OnNativeEmbedVisibilityChangeCallback | undefined));
                }
            }
        }
        if (this._onNativeEmbedGestureEvent_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onNativeEmbedGestureEvent_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnNativeEmbedGestureEventAttribute((this._onNativeEmbedGestureEvent_0_0value as ((event: NativeEmbedTouchInfo) => void) | undefined));
                    this._onNativeEmbedGestureEvent_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onNativeEmbedGestureEvent_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onNativeEmbedGestureEvent_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnNativeEmbedGestureEventAttribute((undefined as ((event: NativeEmbedTouchInfo) => void) | undefined));
                }
            }
        }
        if (this._copyOptions_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._copyOptions_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setCopyOptionsAttribute((this._copyOptions_0_0value as CopyOptions | undefined));
                    this._copyOptions_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._copyOptions_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._copyOptions_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setCopyOptionsAttribute((undefined as CopyOptions | undefined));
                }
            }
        }
        if (this._onOverrideUrlLoading_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onOverrideUrlLoading_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnOverrideUrlLoadingAttribute((this._onOverrideUrlLoading_0_0value as OnOverrideUrlLoadingCallback | undefined));
                    this._onOverrideUrlLoading_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onOverrideUrlLoading_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onOverrideUrlLoading_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnOverrideUrlLoadingAttribute((undefined as OnOverrideUrlLoadingCallback | undefined));
                }
            }
        }
        if (this._textAutosizing_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._textAutosizing_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setTextAutosizingAttribute((this._textAutosizing_0_0value as boolean | undefined));
                    this._textAutosizing_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._textAutosizing_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._textAutosizing_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setTextAutosizingAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._enableNativeMediaPlayer_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._enableNativeMediaPlayer_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setEnableNativeMediaPlayerAttribute((this._enableNativeMediaPlayer_0_0value as NativeMediaPlayerConfig | undefined));
                    this._enableNativeMediaPlayer_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._enableNativeMediaPlayer_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._enableNativeMediaPlayer_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setEnableNativeMediaPlayerAttribute((undefined as NativeMediaPlayerConfig | undefined));
                }
            }
        }
        if (this._onRenderProcessNotResponding_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onRenderProcessNotResponding_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnRenderProcessNotRespondingAttribute((this._onRenderProcessNotResponding_0_0value as OnRenderProcessNotRespondingCallback | undefined));
                    this._onRenderProcessNotResponding_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onRenderProcessNotResponding_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onRenderProcessNotResponding_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnRenderProcessNotRespondingAttribute((undefined as OnRenderProcessNotRespondingCallback | undefined));
                }
            }
        }
        if (this._onRenderProcessResponding_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onRenderProcessResponding_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnRenderProcessRespondingAttribute((this._onRenderProcessResponding_0_0value as OnRenderProcessRespondingCallback | undefined));
                    this._onRenderProcessResponding_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onRenderProcessResponding_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onRenderProcessResponding_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnRenderProcessRespondingAttribute((undefined as OnRenderProcessRespondingCallback | undefined));
                }
            }
        }
        if (this._onViewportFitChanged_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onViewportFitChanged_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnViewportFitChangedAttribute((this._onViewportFitChanged_0_0value as OnViewportFitChangedCallback | undefined));
                    this._onViewportFitChanged_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onViewportFitChanged_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onViewportFitChanged_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnViewportFitChangedAttribute((undefined as OnViewportFitChangedCallback | undefined));
                }
            }
        }
        if (this._onInterceptKeyboardAttach_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onInterceptKeyboardAttach_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnInterceptKeyboardAttachAttribute((this._onInterceptKeyboardAttach_0_0value as WebKeyboardCallback | undefined));
                    this._onInterceptKeyboardAttach_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onInterceptKeyboardAttach_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onInterceptKeyboardAttach_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnInterceptKeyboardAttachAttribute((undefined as WebKeyboardCallback | undefined));
                }
            }
        }
        if (this._onAdsBlocked_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onAdsBlocked_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnAdsBlockedAttribute((this._onAdsBlocked_0_0value as OnAdsBlockedCallback | undefined));
                    this._onAdsBlocked_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onAdsBlocked_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onAdsBlocked_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnAdsBlockedAttribute((undefined as OnAdsBlockedCallback | undefined));
                }
            }
        }
        if (this._keyboardAvoidMode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._keyboardAvoidMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setKeyboardAvoidModeAttribute((this._keyboardAvoidMode_0_0value as WebKeyboardAvoidMode | undefined));
                    this._keyboardAvoidMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._keyboardAvoidMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._keyboardAvoidMode_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setKeyboardAvoidModeAttribute((undefined as WebKeyboardAvoidMode | undefined));
                }
            }
        }
        if (this._editMenuOptions_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._editMenuOptions_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setEditMenuOptionsAttribute((this._editMenuOptions_0_0value as EditMenuOptions | undefined));
                    this._editMenuOptions_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._editMenuOptions_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._editMenuOptions_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setEditMenuOptionsAttribute((undefined as EditMenuOptions | undefined));
                }
            }
        }
        if (this._enableHapticFeedback_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._enableHapticFeedback_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setEnableHapticFeedbackAttribute((this._enableHapticFeedback_0_0value as boolean | undefined));
                    this._enableHapticFeedback_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._enableHapticFeedback_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._enableHapticFeedback_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setEnableHapticFeedbackAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._optimizeParserBudget_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._optimizeParserBudget_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOptimizeParserBudgetAttribute((this._optimizeParserBudget_0_0value as boolean | undefined));
                    this._optimizeParserBudget_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._optimizeParserBudget_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._optimizeParserBudget_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOptimizeParserBudgetAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._enableFollowSystemFontWeight_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._enableFollowSystemFontWeight_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setEnableFollowSystemFontWeightAttribute((this._enableFollowSystemFontWeight_0_0value as boolean | undefined));
                    this._enableFollowSystemFontWeight_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._enableFollowSystemFontWeight_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._enableFollowSystemFontWeight_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setEnableFollowSystemFontWeightAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._enableWebAVSession_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._enableWebAVSession_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setEnableWebAVSessionAttribute((this._enableWebAVSession_0_0value as boolean | undefined));
                    this._enableWebAVSession_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._enableWebAVSession_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._enableWebAVSession_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setEnableWebAVSessionAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._runJavaScriptOnDocumentStart_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._runJavaScriptOnDocumentStart_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setRunJavaScriptOnDocumentStartAttribute((this._runJavaScriptOnDocumentStart_0_0value as Array<ScriptItem> | undefined));
                    this._runJavaScriptOnDocumentStart_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._runJavaScriptOnDocumentStart_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._runJavaScriptOnDocumentStart_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setRunJavaScriptOnDocumentStartAttribute((undefined as Array<ScriptItem> | undefined));
                }
            }
        }
        if (this._runJavaScriptOnDocumentEnd_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._runJavaScriptOnDocumentEnd_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setRunJavaScriptOnDocumentEndAttribute((this._runJavaScriptOnDocumentEnd_0_0value as Array<ScriptItem> | undefined));
                    this._runJavaScriptOnDocumentEnd_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._runJavaScriptOnDocumentEnd_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._runJavaScriptOnDocumentEnd_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setRunJavaScriptOnDocumentEndAttribute((undefined as Array<ScriptItem> | undefined));
                }
            }
        }
        if (this._runJavaScriptOnHeadEnd_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._runJavaScriptOnHeadEnd_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setRunJavaScriptOnHeadEndAttribute((this._runJavaScriptOnHeadEnd_0_0value as Array<ScriptItem> | undefined));
                    this._runJavaScriptOnHeadEnd_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._runJavaScriptOnHeadEnd_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._runJavaScriptOnHeadEnd_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setRunJavaScriptOnHeadEndAttribute((undefined as Array<ScriptItem> | undefined));
                }
            }
        }
        if (this._nativeEmbedOptions_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._nativeEmbedOptions_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setNativeEmbedOptionsAttribute((this._nativeEmbedOptions_0_0value as EmbedOptions | undefined));
                    this._nativeEmbedOptions_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._nativeEmbedOptions_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._nativeEmbedOptions_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setNativeEmbedOptionsAttribute((undefined as EmbedOptions | undefined));
                }
            }
        }
        if (this._registerNativeEmbedRule_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._registerNativeEmbedRule_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setRegisterNativeEmbedRuleAttribute((this._registerNativeEmbedRule_0_0value as string | undefined), (this._registerNativeEmbedRule_0_1value as string | undefined));
                    this._registerNativeEmbedRule_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._registerNativeEmbedRule_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._registerNativeEmbedRule_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setRegisterNativeEmbedRuleAttribute((undefined as string | undefined), (undefined as string | undefined));
                }
            }
        }
        if (this._bindSelectionMenu_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._bindSelectionMenu_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setBindSelectionMenuAttribute((this._bindSelectionMenu_0_0value as WebElementType | undefined), (this._bindSelectionMenu_0_1value as CustomBuilder | undefined), (this._bindSelectionMenu_0_2value as WebResponseType | undefined), (this._bindSelectionMenu_0_3value as SelectionMenuOptionsExt | undefined | undefined));
                    this._bindSelectionMenu_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._bindSelectionMenu_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._bindSelectionMenu_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setBindSelectionMenuAttribute((undefined as WebElementType | undefined), (undefined as CustomBuilder | undefined), (undefined as WebResponseType | undefined), (undefined as SelectionMenuOptionsExt | undefined | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: WebModifier): void {
        super.mergeModifier(modifier)
        if (modifier._javaScriptAccess_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._javaScriptAccess_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.javaScriptAccess(modifier._javaScriptAccess_0_0value);
                    break;
                }
                default: {
                    this.javaScriptAccess((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._fileAccess_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._fileAccess_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.fileAccess(modifier._fileAccess_0_0value);
                    break;
                }
                default: {
                    this.fileAccess((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._onlineImageAccess_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onlineImageAccess_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onlineImageAccess(modifier._onlineImageAccess_0_0value);
                    break;
                }
                default: {
                    this.onlineImageAccess((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._domStorageAccess_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._domStorageAccess_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.domStorageAccess(modifier._domStorageAccess_0_0value);
                    break;
                }
                default: {
                    this.domStorageAccess((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._imageAccess_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._imageAccess_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.imageAccess(modifier._imageAccess_0_0value);
                    break;
                }
                default: {
                    this.imageAccess((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._mixedMode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._mixedMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.mixedMode(modifier._mixedMode_0_0value);
                    break;
                }
                default: {
                    this.mixedMode((undefined as MixedMode | undefined));
                }
            }
        }
        if (modifier._zoomAccess_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._zoomAccess_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.zoomAccess(modifier._zoomAccess_0_0value);
                    break;
                }
                default: {
                    this.zoomAccess((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._geolocationAccess_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._geolocationAccess_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.geolocationAccess(modifier._geolocationAccess_0_0value);
                    break;
                }
                default: {
                    this.geolocationAccess((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._javaScriptProxy_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._javaScriptProxy_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.javaScriptProxy(modifier._javaScriptProxy_0_0value);
                    break;
                }
                default: {
                    this.javaScriptProxy((undefined as JavaScriptProxy | undefined));
                }
            }
        }
        if (modifier._cacheMode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._cacheMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.cacheMode(modifier._cacheMode_0_0value);
                    break;
                }
                default: {
                    this.cacheMode((undefined as CacheMode | undefined));
                }
            }
        }
        if (modifier._darkMode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._darkMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.darkMode(modifier._darkMode_0_0value);
                    break;
                }
                default: {
                    this.darkMode((undefined as WebDarkMode | undefined));
                }
            }
        }
        if (modifier._forceDarkAccess_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._forceDarkAccess_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.forceDarkAccess(modifier._forceDarkAccess_0_0value);
                    break;
                }
                default: {
                    this.forceDarkAccess((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._mediaOptions_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._mediaOptions_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.mediaOptions(modifier._mediaOptions_0_0value);
                    break;
                }
                default: {
                    this.mediaOptions((undefined as WebMediaOptions | undefined));
                }
            }
        }
        if (modifier._overviewModeAccess_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._overviewModeAccess_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.overviewModeAccess(modifier._overviewModeAccess_0_0value);
                    break;
                }
                default: {
                    this.overviewModeAccess((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._overScrollMode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._overScrollMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.overScrollMode(modifier._overScrollMode_0_0value);
                    break;
                }
                default: {
                    this.overScrollMode((undefined as OverScrollMode | undefined));
                }
            }
        }
        if (modifier._blurOnKeyboardHideMode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._blurOnKeyboardHideMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.blurOnKeyboardHideMode(modifier._blurOnKeyboardHideMode_0_0value);
                    break;
                }
                default: {
                    this.blurOnKeyboardHideMode((undefined as BlurOnKeyboardHideMode | undefined));
                }
            }
        }
        if (modifier._textZoomRatio_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._textZoomRatio_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.textZoomRatio(modifier._textZoomRatio_0_0value);
                    break;
                }
                default: {
                    this.textZoomRatio((undefined as int32 | undefined));
                }
            }
        }
        if (modifier._databaseAccess_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._databaseAccess_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.databaseAccess(modifier._databaseAccess_0_0value);
                    break;
                }
                default: {
                    this.databaseAccess((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._initialScale_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._initialScale_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.initialScale(modifier._initialScale_0_0value);
                    break;
                }
                default: {
                    this.initialScale((undefined as double | undefined));
                }
            }
        }
        if (modifier._metaViewport_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._metaViewport_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.metaViewport(modifier._metaViewport_0_0value);
                    break;
                }
                default: {
                    this.metaViewport((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._onPageEnd_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onPageEnd_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onPageEnd(modifier._onPageEnd_0_0value);
                    break;
                }
                default: {
                    this.onPageEnd((undefined as ((value0: OnPageEndEvent) => void) | undefined));
                }
            }
        }
        if (modifier._onPageBegin_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onPageBegin_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onPageBegin(modifier._onPageBegin_0_0value);
                    break;
                }
                default: {
                    this.onPageBegin((undefined as ((value0: OnPageBeginEvent) => void) | undefined));
                }
            }
        }
        if (modifier._onLoadStarted_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onLoadStarted_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onLoadStarted(modifier._onLoadStarted_0_0value);
                    break;
                }
                default: {
                    this.onLoadStarted((undefined as ((value0: OnLoadStartedEvent) => void) | undefined));
                }
            }
        }
        if (modifier._onLoadFinished_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onLoadFinished_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onLoadFinished(modifier._onLoadFinished_0_0value);
                    break;
                }
                default: {
                    this.onLoadFinished((undefined as ((value0: OnLoadFinishedEvent) => void) | undefined));
                }
            }
        }
        if (modifier._onProgressChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onProgressChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onProgressChange(modifier._onProgressChange_0_0value);
                    break;
                }
                default: {
                    this.onProgressChange((undefined as ((value0: OnProgressChangeEvent) => void) | undefined));
                }
            }
        }
        if (modifier._onTitleReceive_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onTitleReceive_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onTitleReceive(modifier._onTitleReceive_0_0value);
                    break;
                }
                default: {
                    this.onTitleReceive((undefined as ((value0: OnTitleReceiveEvent) => void) | undefined));
                }
            }
        }
        if (modifier._onGeolocationHide_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onGeolocationHide_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onGeolocationHide(modifier._onGeolocationHide_0_0value);
                    break;
                }
                default: {
                    this.onGeolocationHide((undefined as (() => void) | undefined));
                }
            }
        }
        if (modifier._onGeolocationShow_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onGeolocationShow_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onGeolocationShow(modifier._onGeolocationShow_0_0value);
                    break;
                }
                default: {
                    this.onGeolocationShow((undefined as ((value0: OnGeolocationShowEvent) => void) | undefined));
                }
            }
        }
        if (modifier._onRequestSelected_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onRequestSelected_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onRequestSelected(modifier._onRequestSelected_0_0value);
                    break;
                }
                default: {
                    this.onRequestSelected((undefined as (() => void) | undefined));
                }
            }
        }
        if (modifier._onAlert_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onAlert_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onAlert(modifier._onAlert_0_0value);
                    break;
                }
                default: {
                    this.onAlert((undefined as ((value0: OnAlertEvent) => boolean) | undefined));
                }
            }
        }
        if (modifier._onBeforeUnload_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onBeforeUnload_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onBeforeUnload(modifier._onBeforeUnload_0_0value);
                    break;
                }
                default: {
                    this.onBeforeUnload((undefined as ((value0: OnBeforeUnloadEvent) => boolean) | undefined));
                }
            }
        }
        if (modifier._onConfirm_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onConfirm_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onConfirm(modifier._onConfirm_0_0value);
                    break;
                }
                default: {
                    this.onConfirm((undefined as ((value0: OnConfirmEvent) => boolean) | undefined));
                }
            }
        }
        if (modifier._onPrompt_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onPrompt_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onPrompt(modifier._onPrompt_0_0value);
                    break;
                }
                default: {
                    this.onPrompt((undefined as ((value0: OnPromptEvent) => boolean) | undefined));
                }
            }
        }
        if (modifier._onConsole_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onConsole_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onConsole(modifier._onConsole_0_0value);
                    break;
                }
                default: {
                    this.onConsole((undefined as ((value0: OnConsoleEvent) => boolean) | undefined));
                }
            }
        }
        if (modifier._onErrorReceive_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onErrorReceive_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onErrorReceive(modifier._onErrorReceive_0_0value);
                    break;
                }
                default: {
                    this.onErrorReceive((undefined as ((value0: OnErrorReceiveEvent) => void) | undefined));
                }
            }
        }
        if (modifier._onHttpErrorReceive_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onHttpErrorReceive_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onHttpErrorReceive(modifier._onHttpErrorReceive_0_0value);
                    break;
                }
                default: {
                    this.onHttpErrorReceive((undefined as ((value0: OnHttpErrorReceiveEvent) => void) | undefined));
                }
            }
        }
        if (modifier._onDownloadStart_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onDownloadStart_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onDownloadStart(modifier._onDownloadStart_0_0value);
                    break;
                }
                default: {
                    this.onDownloadStart((undefined as ((value0: OnDownloadStartEvent) => void) | undefined));
                }
            }
        }
        if (modifier._onRefreshAccessedHistory_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onRefreshAccessedHistory_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onRefreshAccessedHistory(modifier._onRefreshAccessedHistory_0_0value);
                    break;
                }
                default: {
                    this.onRefreshAccessedHistory((undefined as ((value0: OnRefreshAccessedHistoryEvent) => void) | undefined));
                }
            }
        }
        if (modifier._onRenderExited_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onRenderExited_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onRenderExited(modifier._onRenderExited_0_0value);
                    break;
                }
                default: {
                    this.onRenderExited((undefined as ((value0: OnRenderExitedEvent) => void) | undefined));
                }
            }
        }
        if (modifier._onShowFileSelector_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onShowFileSelector_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onShowFileSelector(modifier._onShowFileSelector_0_0value);
                    break;
                }
                default: {
                    this.onShowFileSelector((undefined as ((value0: OnShowFileSelectorEvent) => boolean) | undefined));
                }
            }
        }
        if (modifier._onResourceLoad_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onResourceLoad_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onResourceLoad(modifier._onResourceLoad_0_0value);
                    break;
                }
                default: {
                    this.onResourceLoad((undefined as ((value0: OnResourceLoadEvent) => void) | undefined));
                }
            }
        }
        if (modifier._onFullScreenExit_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onFullScreenExit_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onFullScreenExit(modifier._onFullScreenExit_0_0value);
                    break;
                }
                default: {
                    this.onFullScreenExit((undefined as (() => void) | undefined));
                }
            }
        }
        if (modifier._onFullScreenEnter_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onFullScreenEnter_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onFullScreenEnter(modifier._onFullScreenEnter_0_0value);
                    break;
                }
                default: {
                    this.onFullScreenEnter((undefined as OnFullScreenEnterCallback | undefined));
                }
            }
        }
        if (modifier._onScaleChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onScaleChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onScaleChange(modifier._onScaleChange_0_0value);
                    break;
                }
                default: {
                    this.onScaleChange((undefined as ((value0: OnScaleChangeEvent) => void) | undefined));
                }
            }
        }
        if (modifier._onHttpAuthRequest_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onHttpAuthRequest_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onHttpAuthRequest(modifier._onHttpAuthRequest_0_0value);
                    break;
                }
                default: {
                    this.onHttpAuthRequest((undefined as ((value0: OnHttpAuthRequestEvent) => boolean) | undefined));
                }
            }
        }
        if (modifier._onInterceptRequest_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onInterceptRequest_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onInterceptRequest(modifier._onInterceptRequest_0_0value);
                    break;
                }
                default: {
                    this.onInterceptRequest((undefined as ((value0: OnInterceptRequestEvent) => WebResourceResponse | null) | undefined));
                }
            }
        }
        if (modifier._onPermissionRequest_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onPermissionRequest_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onPermissionRequest(modifier._onPermissionRequest_0_0value);
                    break;
                }
                default: {
                    this.onPermissionRequest((undefined as ((value0: OnPermissionRequestEvent) => void) | undefined));
                }
            }
        }
        if (modifier._onScreenCaptureRequest_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onScreenCaptureRequest_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onScreenCaptureRequest(modifier._onScreenCaptureRequest_0_0value);
                    break;
                }
                default: {
                    this.onScreenCaptureRequest((undefined as ((value0: OnScreenCaptureRequestEvent) => void) | undefined));
                }
            }
        }
        if (modifier._onContextMenuShow_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onContextMenuShow_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onContextMenuShow(modifier._onContextMenuShow_0_0value);
                    break;
                }
                default: {
                    this.onContextMenuShow((undefined as ((value0: OnContextMenuShowEvent) => boolean) | undefined));
                }
            }
        }
        if (modifier._onContextMenuHide_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onContextMenuHide_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onContextMenuHide(modifier._onContextMenuHide_0_0value);
                    break;
                }
                default: {
                    this.onContextMenuHide((undefined as OnContextMenuHideCallback | undefined));
                }
            }
        }
        if (modifier._mediaPlayGestureAccess_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._mediaPlayGestureAccess_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.mediaPlayGestureAccess(modifier._mediaPlayGestureAccess_0_0value);
                    break;
                }
                default: {
                    this.mediaPlayGestureAccess((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._onSearchResultReceive_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onSearchResultReceive_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onSearchResultReceive(modifier._onSearchResultReceive_0_0value);
                    break;
                }
                default: {
                    this.onSearchResultReceive((undefined as ((value0: OnSearchResultReceiveEvent) => void) | undefined));
                }
            }
        }
        if (modifier._onScroll_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onScroll_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onScroll(modifier._onScroll_0_0value);
                    break;
                }
                default: {
                    this.onScroll((undefined as ((value0: OnScrollEvent) => void) | undefined));
                }
            }
        }
        if (modifier._onSslErrorEventReceive_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onSslErrorEventReceive_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onSslErrorEventReceive(modifier._onSslErrorEventReceive_0_0value);
                    break;
                }
                default: {
                    this.onSslErrorEventReceive((undefined as ((value0: OnSslErrorEventReceiveEvent) => void) | undefined));
                }
            }
        }
        if (modifier._onSslErrorEvent_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onSslErrorEvent_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onSslErrorEvent(modifier._onSslErrorEvent_0_0value);
                    break;
                }
                default: {
                    this.onSslErrorEvent((undefined as OnSslErrorEventCallback | undefined));
                }
            }
        }
        if (modifier._onClientAuthenticationRequest_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onClientAuthenticationRequest_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onClientAuthenticationRequest(modifier._onClientAuthenticationRequest_0_0value);
                    break;
                }
                default: {
                    this.onClientAuthenticationRequest((undefined as ((value0: OnClientAuthenticationEvent) => void) | undefined));
                }
            }
        }
        if (modifier._onWindowNew_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onWindowNew_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onWindowNew(modifier._onWindowNew_0_0value);
                    break;
                }
                default: {
                    this.onWindowNew((undefined as ((value0: OnWindowNewEvent) => void) | undefined));
                }
            }
        }
        if (modifier._onWindowExit_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onWindowExit_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onWindowExit(modifier._onWindowExit_0_0value);
                    break;
                }
                default: {
                    this.onWindowExit((undefined as (() => void) | undefined));
                }
            }
        }
        if (modifier._multiWindowAccess_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._multiWindowAccess_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.multiWindowAccess(modifier._multiWindowAccess_0_0value);
                    break;
                }
                default: {
                    this.multiWindowAccess((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._onInterceptKeyEvent_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onInterceptKeyEvent_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onInterceptKeyEvent(modifier._onInterceptKeyEvent_0_0value);
                    break;
                }
                default: {
                    this.onInterceptKeyEvent((undefined as ((event: KeyEvent) => boolean) | undefined));
                }
            }
        }
        if (modifier._webStandardFont_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._webStandardFont_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.webStandardFont(modifier._webStandardFont_0_0value);
                    break;
                }
                default: {
                    this.webStandardFont((undefined as string | undefined));
                }
            }
        }
        if (modifier._webSerifFont_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._webSerifFont_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.webSerifFont(modifier._webSerifFont_0_0value);
                    break;
                }
                default: {
                    this.webSerifFont((undefined as string | undefined));
                }
            }
        }
        if (modifier._webSansSerifFont_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._webSansSerifFont_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.webSansSerifFont(modifier._webSansSerifFont_0_0value);
                    break;
                }
                default: {
                    this.webSansSerifFont((undefined as string | undefined));
                }
            }
        }
        if (modifier._webFixedFont_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._webFixedFont_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.webFixedFont(modifier._webFixedFont_0_0value);
                    break;
                }
                default: {
                    this.webFixedFont((undefined as string | undefined));
                }
            }
        }
        if (modifier._webFantasyFont_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._webFantasyFont_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.webFantasyFont(modifier._webFantasyFont_0_0value);
                    break;
                }
                default: {
                    this.webFantasyFont((undefined as string | undefined));
                }
            }
        }
        if (modifier._webCursiveFont_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._webCursiveFont_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.webCursiveFont(modifier._webCursiveFont_0_0value);
                    break;
                }
                default: {
                    this.webCursiveFont((undefined as string | undefined));
                }
            }
        }
        if (modifier._defaultFixedFontSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._defaultFixedFontSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.defaultFixedFontSize(modifier._defaultFixedFontSize_0_0value);
                    break;
                }
                default: {
                    this.defaultFixedFontSize((undefined as int32 | undefined));
                }
            }
        }
        if (modifier._defaultFontSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._defaultFontSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.defaultFontSize(modifier._defaultFontSize_0_0value);
                    break;
                }
                default: {
                    this.defaultFontSize((undefined as int32 | undefined));
                }
            }
        }
        if (modifier._minFontSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._minFontSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.minFontSize(modifier._minFontSize_0_0value);
                    break;
                }
                default: {
                    this.minFontSize((undefined as int32 | undefined));
                }
            }
        }
        if (modifier._minLogicalFontSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._minLogicalFontSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.minLogicalFontSize(modifier._minLogicalFontSize_0_0value);
                    break;
                }
                default: {
                    this.minLogicalFontSize((undefined as int32 | undefined));
                }
            }
        }
        if (modifier._defaultTextEncodingFormat_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._defaultTextEncodingFormat_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.defaultTextEncodingFormat(modifier._defaultTextEncodingFormat_0_0value);
                    break;
                }
                default: {
                    this.defaultTextEncodingFormat((undefined as string | undefined));
                }
            }
        }
        if (modifier._forceDisplayScrollBar_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._forceDisplayScrollBar_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.forceDisplayScrollBar(modifier._forceDisplayScrollBar_0_0value);
                    break;
                }
                default: {
                    this.forceDisplayScrollBar((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._blockNetwork_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._blockNetwork_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.blockNetwork(modifier._blockNetwork_0_0value);
                    break;
                }
                default: {
                    this.blockNetwork((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._horizontalScrollBarAccess_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._horizontalScrollBarAccess_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.horizontalScrollBarAccess(modifier._horizontalScrollBarAccess_0_0value);
                    break;
                }
                default: {
                    this.horizontalScrollBarAccess((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._verticalScrollBarAccess_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._verticalScrollBarAccess_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.verticalScrollBarAccess(modifier._verticalScrollBarAccess_0_0value);
                    break;
                }
                default: {
                    this.verticalScrollBarAccess((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._onTouchIconUrlReceived_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onTouchIconUrlReceived_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onTouchIconUrlReceived(modifier._onTouchIconUrlReceived_0_0value);
                    break;
                }
                default: {
                    this.onTouchIconUrlReceived((undefined as ((value0: OnTouchIconUrlReceivedEvent) => void) | undefined));
                }
            }
        }
        if (modifier._onFaviconReceived_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onFaviconReceived_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onFaviconReceived(modifier._onFaviconReceived_0_0value);
                    break;
                }
                default: {
                    this.onFaviconReceived((undefined as ((value0: OnFaviconReceivedEvent) => void) | undefined));
                }
            }
        }
        if (modifier._onPageVisible_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onPageVisible_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onPageVisible(modifier._onPageVisible_0_0value);
                    break;
                }
                default: {
                    this.onPageVisible((undefined as ((value0: OnPageVisibleEvent) => void) | undefined));
                }
            }
        }
        if (modifier._onDataResubmitted_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onDataResubmitted_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onDataResubmitted(modifier._onDataResubmitted_0_0value);
                    break;
                }
                default: {
                    this.onDataResubmitted((undefined as ((value0: OnDataResubmittedEvent) => void) | undefined));
                }
            }
        }
        if (modifier._pinchSmooth_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._pinchSmooth_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.pinchSmooth(modifier._pinchSmooth_0_0value);
                    break;
                }
                default: {
                    this.pinchSmooth((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._allowWindowOpenMethod_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._allowWindowOpenMethod_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.allowWindowOpenMethod(modifier._allowWindowOpenMethod_0_0value);
                    break;
                }
                default: {
                    this.allowWindowOpenMethod((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._onAudioStateChanged_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onAudioStateChanged_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onAudioStateChanged(modifier._onAudioStateChanged_0_0value);
                    break;
                }
                default: {
                    this.onAudioStateChanged((undefined as ((value0: OnAudioStateChangedEvent) => void) | undefined));
                }
            }
        }
        if (modifier._onFirstContentfulPaint_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onFirstContentfulPaint_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onFirstContentfulPaint(modifier._onFirstContentfulPaint_0_0value);
                    break;
                }
                default: {
                    this.onFirstContentfulPaint((undefined as ((value0: OnFirstContentfulPaintEvent) => void) | undefined));
                }
            }
        }
        if (modifier._onFirstMeaningfulPaint_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onFirstMeaningfulPaint_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onFirstMeaningfulPaint(modifier._onFirstMeaningfulPaint_0_0value);
                    break;
                }
                default: {
                    this.onFirstMeaningfulPaint((undefined as OnFirstMeaningfulPaintCallback | undefined));
                }
            }
        }
        if (modifier._onLargestContentfulPaint_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onLargestContentfulPaint_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onLargestContentfulPaint(modifier._onLargestContentfulPaint_0_0value);
                    break;
                }
                default: {
                    this.onLargestContentfulPaint((undefined as OnLargestContentfulPaintCallback | undefined));
                }
            }
        }
        if (modifier._onLoadIntercept_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onLoadIntercept_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onLoadIntercept(modifier._onLoadIntercept_0_0value);
                    break;
                }
                default: {
                    this.onLoadIntercept((undefined as ((value0: OnLoadInterceptEvent) => boolean) | undefined));
                }
            }
        }
        if (modifier._onControllerAttached_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onControllerAttached_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onControllerAttached(modifier._onControllerAttached_0_0value);
                    break;
                }
                default: {
                    this.onControllerAttached((undefined as (() => void) | undefined));
                }
            }
        }
        if (modifier._onOverScroll_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onOverScroll_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onOverScroll(modifier._onOverScroll_0_0value);
                    break;
                }
                default: {
                    this.onOverScroll((undefined as ((value0: OnOverScrollEvent) => void) | undefined));
                }
            }
        }
        if (modifier._onSafeBrowsingCheckResult_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onSafeBrowsingCheckResult_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onSafeBrowsingCheckResult(modifier._onSafeBrowsingCheckResult_0_0value);
                    break;
                }
                default: {
                    this.onSafeBrowsingCheckResult((undefined as OnSafeBrowsingCheckResultCallback | undefined));
                }
            }
        }
        if (modifier._onNavigationEntryCommitted_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onNavigationEntryCommitted_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onNavigationEntryCommitted(modifier._onNavigationEntryCommitted_0_0value);
                    break;
                }
                default: {
                    this.onNavigationEntryCommitted((undefined as OnNavigationEntryCommittedCallback | undefined));
                }
            }
        }
        if (modifier._onIntelligentTrackingPreventionResult_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onIntelligentTrackingPreventionResult_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onIntelligentTrackingPreventionResult(modifier._onIntelligentTrackingPreventionResult_0_0value);
                    break;
                }
                default: {
                    this.onIntelligentTrackingPreventionResult((undefined as OnIntelligentTrackingPreventionCallback | undefined));
                }
            }
        }
        if (modifier._javaScriptOnDocumentStart_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._javaScriptOnDocumentStart_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.javaScriptOnDocumentStart(modifier._javaScriptOnDocumentStart_0_0value);
                    break;
                }
                default: {
                    this.javaScriptOnDocumentStart((undefined as Array<ScriptItem> | undefined));
                }
            }
        }
        if (modifier._javaScriptOnDocumentEnd_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._javaScriptOnDocumentEnd_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.javaScriptOnDocumentEnd(modifier._javaScriptOnDocumentEnd_0_0value);
                    break;
                }
                default: {
                    this.javaScriptOnDocumentEnd((undefined as Array<ScriptItem> | undefined));
                }
            }
        }
        if (modifier._layoutMode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._layoutMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.layoutMode(modifier._layoutMode_0_0value);
                    break;
                }
                default: {
                    this.layoutMode((undefined as WebLayoutMode | undefined));
                }
            }
        }
        if (modifier._nestedScroll_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._nestedScroll_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.nestedScroll(modifier._nestedScroll_0_0value);
                    break;
                }
                default: {
                    this.nestedScroll((undefined as NestedScrollOptions | NestedScrollOptionsExt | undefined));
                }
            }
        }
        if (modifier._enableNativeEmbedMode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._enableNativeEmbedMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.enableNativeEmbedMode(modifier._enableNativeEmbedMode_0_0value);
                    break;
                }
                default: {
                    this.enableNativeEmbedMode((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._onNativeEmbedLifecycleChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onNativeEmbedLifecycleChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onNativeEmbedLifecycleChange(modifier._onNativeEmbedLifecycleChange_0_0value);
                    break;
                }
                default: {
                    this.onNativeEmbedLifecycleChange((undefined as ((event: NativeEmbedDataInfo) => void) | undefined));
                }
            }
        }
        if (modifier._onNativeEmbedVisibilityChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onNativeEmbedVisibilityChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onNativeEmbedVisibilityChange(modifier._onNativeEmbedVisibilityChange_0_0value);
                    break;
                }
                default: {
                    this.onNativeEmbedVisibilityChange((undefined as OnNativeEmbedVisibilityChangeCallback | undefined));
                }
            }
        }
        if (modifier._onNativeEmbedGestureEvent_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onNativeEmbedGestureEvent_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onNativeEmbedGestureEvent(modifier._onNativeEmbedGestureEvent_0_0value);
                    break;
                }
                default: {
                    this.onNativeEmbedGestureEvent((undefined as ((event: NativeEmbedTouchInfo) => void) | undefined));
                }
            }
        }
        if (modifier._copyOptions_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._copyOptions_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.copyOptions(modifier._copyOptions_0_0value);
                    break;
                }
                default: {
                    this.copyOptions((undefined as CopyOptions | undefined));
                }
            }
        }
        if (modifier._onOverrideUrlLoading_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onOverrideUrlLoading_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onOverrideUrlLoading(modifier._onOverrideUrlLoading_0_0value);
                    break;
                }
                default: {
                    this.onOverrideUrlLoading((undefined as OnOverrideUrlLoadingCallback | undefined));
                }
            }
        }
        if (modifier._textAutosizing_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._textAutosizing_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.textAutosizing(modifier._textAutosizing_0_0value);
                    break;
                }
                default: {
                    this.textAutosizing((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._enableNativeMediaPlayer_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._enableNativeMediaPlayer_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.enableNativeMediaPlayer(modifier._enableNativeMediaPlayer_0_0value);
                    break;
                }
                default: {
                    this.enableNativeMediaPlayer((undefined as NativeMediaPlayerConfig | undefined));
                }
            }
        }
        if (modifier._onRenderProcessNotResponding_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onRenderProcessNotResponding_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onRenderProcessNotResponding(modifier._onRenderProcessNotResponding_0_0value);
                    break;
                }
                default: {
                    this.onRenderProcessNotResponding((undefined as OnRenderProcessNotRespondingCallback | undefined));
                }
            }
        }
        if (modifier._onRenderProcessResponding_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onRenderProcessResponding_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onRenderProcessResponding(modifier._onRenderProcessResponding_0_0value);
                    break;
                }
                default: {
                    this.onRenderProcessResponding((undefined as OnRenderProcessRespondingCallback | undefined));
                }
            }
        }
        if (modifier._onViewportFitChanged_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onViewportFitChanged_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onViewportFitChanged(modifier._onViewportFitChanged_0_0value);
                    break;
                }
                default: {
                    this.onViewportFitChanged((undefined as OnViewportFitChangedCallback | undefined));
                }
            }
        }
        if (modifier._onInterceptKeyboardAttach_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onInterceptKeyboardAttach_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onInterceptKeyboardAttach(modifier._onInterceptKeyboardAttach_0_0value);
                    break;
                }
                default: {
                    this.onInterceptKeyboardAttach((undefined as WebKeyboardCallback | undefined));
                }
            }
        }
        if (modifier._onAdsBlocked_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onAdsBlocked_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onAdsBlocked(modifier._onAdsBlocked_0_0value);
                    break;
                }
                default: {
                    this.onAdsBlocked((undefined as OnAdsBlockedCallback | undefined));
                }
            }
        }
        if (modifier._keyboardAvoidMode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._keyboardAvoidMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.keyboardAvoidMode(modifier._keyboardAvoidMode_0_0value);
                    break;
                }
                default: {
                    this.keyboardAvoidMode((undefined as WebKeyboardAvoidMode | undefined));
                }
            }
        }
        if (modifier._editMenuOptions_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._editMenuOptions_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.editMenuOptions(modifier._editMenuOptions_0_0value);
                    break;
                }
                default: {
                    this.editMenuOptions((undefined as EditMenuOptions | undefined));
                }
            }
        }
        if (modifier._enableHapticFeedback_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._enableHapticFeedback_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.enableHapticFeedback(modifier._enableHapticFeedback_0_0value);
                    break;
                }
                default: {
                    this.enableHapticFeedback((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._optimizeParserBudget_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._optimizeParserBudget_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.optimizeParserBudget(modifier._optimizeParserBudget_0_0value);
                    break;
                }
                default: {
                    this.optimizeParserBudget((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._enableFollowSystemFontWeight_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._enableFollowSystemFontWeight_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.enableFollowSystemFontWeight(modifier._enableFollowSystemFontWeight_0_0value);
                    break;
                }
                default: {
                    this.enableFollowSystemFontWeight((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._enableWebAVSession_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._enableWebAVSession_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.enableWebAVSession(modifier._enableWebAVSession_0_0value);
                    break;
                }
                default: {
                    this.enableWebAVSession((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._runJavaScriptOnDocumentStart_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._runJavaScriptOnDocumentStart_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.runJavaScriptOnDocumentStart(modifier._runJavaScriptOnDocumentStart_0_0value);
                    break;
                }
                default: {
                    this.runJavaScriptOnDocumentStart((undefined as Array<ScriptItem> | undefined));
                }
            }
        }
        if (modifier._runJavaScriptOnDocumentEnd_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._runJavaScriptOnDocumentEnd_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.runJavaScriptOnDocumentEnd(modifier._runJavaScriptOnDocumentEnd_0_0value);
                    break;
                }
                default: {
                    this.runJavaScriptOnDocumentEnd((undefined as Array<ScriptItem> | undefined));
                }
            }
        }
        if (modifier._runJavaScriptOnHeadEnd_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._runJavaScriptOnHeadEnd_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.runJavaScriptOnHeadEnd(modifier._runJavaScriptOnHeadEnd_0_0value);
                    break;
                }
                default: {
                    this.runJavaScriptOnHeadEnd((undefined as Array<ScriptItem> | undefined));
                }
            }
        }
        if (modifier._nativeEmbedOptions_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._nativeEmbedOptions_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.nativeEmbedOptions(modifier._nativeEmbedOptions_0_0value);
                    break;
                }
                default: {
                    this.nativeEmbedOptions((undefined as EmbedOptions | undefined));
                }
            }
        }
        if (modifier._registerNativeEmbedRule_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._registerNativeEmbedRule_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.registerNativeEmbedRule(modifier._registerNativeEmbedRule_0_0value, modifier._registerNativeEmbedRule_0_1value);
                    break;
                }
                default: {
                    this.registerNativeEmbedRule((undefined as string | undefined), (undefined as string | undefined));
                }
            }
        }
        if (modifier._bindSelectionMenu_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._bindSelectionMenu_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.bindSelectionMenu(modifier._bindSelectionMenu_0_0value, modifier._bindSelectionMenu_0_1value, modifier._bindSelectionMenu_0_2value, modifier._bindSelectionMenu_0_3value);
                    break;
                }
                default: {
                    this.bindSelectionMenu((undefined as WebElementType | undefined), (undefined as CustomBuilder | undefined), (undefined as WebResponseType | undefined), (undefined as SelectionMenuOptionsExt | undefined | undefined));
                }
            }
        }
    }
    javaScriptAccess(value: boolean | undefined): this {
        if (((this._javaScriptAccess_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._javaScriptAccess_0_0value) !== (value)))
        {
            this._javaScriptAccess_0_flag = AttributeUpdaterFlag.UPDATE
            this._javaScriptAccess_0_0value = value
            this._state.fireChange()
        } else
        {
            this._javaScriptAccess_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    fileAccess(value: boolean | undefined): this {
        if (((this._fileAccess_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._fileAccess_0_0value) !== (value)))
        {
            this._fileAccess_0_flag = AttributeUpdaterFlag.UPDATE
            this._fileAccess_0_0value = value
            this._state.fireChange()
        } else
        {
            this._fileAccess_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onlineImageAccess(value: boolean | undefined): this {
        if (((this._onlineImageAccess_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._onlineImageAccess_0_0value) !== (value)))
        {
            this._onlineImageAccess_0_flag = AttributeUpdaterFlag.UPDATE
            this._onlineImageAccess_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onlineImageAccess_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    domStorageAccess(value: boolean | undefined): this {
        if (((this._domStorageAccess_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._domStorageAccess_0_0value) !== (value)))
        {
            this._domStorageAccess_0_flag = AttributeUpdaterFlag.UPDATE
            this._domStorageAccess_0_0value = value
            this._state.fireChange()
        } else
        {
            this._domStorageAccess_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    imageAccess(value: boolean | undefined): this {
        if (((this._imageAccess_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._imageAccess_0_0value) !== (value)))
        {
            this._imageAccess_0_flag = AttributeUpdaterFlag.UPDATE
            this._imageAccess_0_0value = value
            this._state.fireChange()
        } else
        {
            this._imageAccess_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    mixedMode(value: MixedMode | undefined): this {
        if (((this._mixedMode_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._mixedMode_0_flag = AttributeUpdaterFlag.UPDATE
            this._mixedMode_0_0value = value
            this._state.fireChange()
        } else
        {
            this._mixedMode_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    zoomAccess(value: boolean | undefined): this {
        if (((this._zoomAccess_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._zoomAccess_0_0value) !== (value)))
        {
            this._zoomAccess_0_flag = AttributeUpdaterFlag.UPDATE
            this._zoomAccess_0_0value = value
            this._state.fireChange()
        } else
        {
            this._zoomAccess_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    geolocationAccess(value: boolean | undefined): this {
        if (((this._geolocationAccess_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._geolocationAccess_0_0value) !== (value)))
        {
            this._geolocationAccess_0_flag = AttributeUpdaterFlag.UPDATE
            this._geolocationAccess_0_0value = value
            this._state.fireChange()
        } else
        {
            this._geolocationAccess_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    javaScriptProxy(value: JavaScriptProxy | undefined): this {
        if (((this._javaScriptProxy_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._javaScriptProxy_0_flag = AttributeUpdaterFlag.UPDATE
            this._javaScriptProxy_0_0value = value
            this._state.fireChange()
        } else
        {
            this._javaScriptProxy_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    cacheMode(value: CacheMode | undefined): this {
        if (((this._cacheMode_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._cacheMode_0_flag = AttributeUpdaterFlag.UPDATE
            this._cacheMode_0_0value = value
            this._state.fireChange()
        } else
        {
            this._cacheMode_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    darkMode(value: WebDarkMode | undefined): this {
        if (((this._darkMode_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._darkMode_0_flag = AttributeUpdaterFlag.UPDATE
            this._darkMode_0_0value = value
            this._state.fireChange()
        } else
        {
            this._darkMode_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    forceDarkAccess(value: boolean | undefined): this {
        if (((this._forceDarkAccess_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._forceDarkAccess_0_0value) !== (value)))
        {
            this._forceDarkAccess_0_flag = AttributeUpdaterFlag.UPDATE
            this._forceDarkAccess_0_0value = value
            this._state.fireChange()
        } else
        {
            this._forceDarkAccess_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    mediaOptions(value: WebMediaOptions | undefined): this {
        if (((this._mediaOptions_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._mediaOptions_0_flag = AttributeUpdaterFlag.UPDATE
            this._mediaOptions_0_0value = value
            this._state.fireChange()
        } else
        {
            this._mediaOptions_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    overviewModeAccess(value: boolean | undefined): this {
        if (((this._overviewModeAccess_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._overviewModeAccess_0_0value) !== (value)))
        {
            this._overviewModeAccess_0_flag = AttributeUpdaterFlag.UPDATE
            this._overviewModeAccess_0_0value = value
            this._state.fireChange()
        } else
        {
            this._overviewModeAccess_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    overScrollMode(value: OverScrollMode | undefined): this {
        if (((this._overScrollMode_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._overScrollMode_0_flag = AttributeUpdaterFlag.UPDATE
            this._overScrollMode_0_0value = value
            this._state.fireChange()
        } else
        {
            this._overScrollMode_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    blurOnKeyboardHideMode(value: BlurOnKeyboardHideMode | undefined): this {
        if (((this._blurOnKeyboardHideMode_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._blurOnKeyboardHideMode_0_flag = AttributeUpdaterFlag.UPDATE
            this._blurOnKeyboardHideMode_0_0value = value
            this._state.fireChange()
        } else
        {
            this._blurOnKeyboardHideMode_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    textZoomRatio(value: int32 | undefined): this {
        if (((this._textZoomRatio_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._textZoomRatio_0_0value) !== (value)))
        {
            this._textZoomRatio_0_flag = AttributeUpdaterFlag.UPDATE
            this._textZoomRatio_0_0value = value
            this._state.fireChange()
        } else
        {
            this._textZoomRatio_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    databaseAccess(value: boolean | undefined): this {
        if (((this._databaseAccess_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._databaseAccess_0_0value) !== (value)))
        {
            this._databaseAccess_0_flag = AttributeUpdaterFlag.UPDATE
            this._databaseAccess_0_0value = value
            this._state.fireChange()
        } else
        {
            this._databaseAccess_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    initialScale(value: double | undefined): this {
        if (((this._initialScale_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._initialScale_0_0value) !== (value)))
        {
            this._initialScale_0_flag = AttributeUpdaterFlag.UPDATE
            this._initialScale_0_0value = value
            this._state.fireChange()
        } else
        {
            this._initialScale_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    metaViewport(value: boolean | undefined): this {
        if (((this._metaViewport_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._metaViewport_0_0value) !== (value)))
        {
            this._metaViewport_0_flag = AttributeUpdaterFlag.UPDATE
            this._metaViewport_0_0value = value
            this._state.fireChange()
        } else
        {
            this._metaViewport_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onPageEnd(value: ((value0: OnPageEndEvent) => void) | undefined): this {
        if (((this._onPageEnd_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onPageEnd_0_flag = AttributeUpdaterFlag.UPDATE
            this._onPageEnd_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onPageEnd_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onPageBegin(value: ((value0: OnPageBeginEvent) => void) | undefined): this {
        if (((this._onPageBegin_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onPageBegin_0_flag = AttributeUpdaterFlag.UPDATE
            this._onPageBegin_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onPageBegin_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onLoadStarted(value: ((value0: OnLoadStartedEvent) => void) | undefined): this {
        if (((this._onLoadStarted_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onLoadStarted_0_flag = AttributeUpdaterFlag.UPDATE
            this._onLoadStarted_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onLoadStarted_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onLoadFinished(value: ((value0: OnLoadFinishedEvent) => void) | undefined): this {
        if (((this._onLoadFinished_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onLoadFinished_0_flag = AttributeUpdaterFlag.UPDATE
            this._onLoadFinished_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onLoadFinished_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onProgressChange(value: ((value0: OnProgressChangeEvent) => void) | undefined): this {
        if (((this._onProgressChange_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onProgressChange_0_flag = AttributeUpdaterFlag.UPDATE
            this._onProgressChange_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onProgressChange_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onTitleReceive(value: ((value0: OnTitleReceiveEvent) => void) | undefined): this {
        if (((this._onTitleReceive_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onTitleReceive_0_flag = AttributeUpdaterFlag.UPDATE
            this._onTitleReceive_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onTitleReceive_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onGeolocationHide(value: (() => void) | undefined): this {
        if (((this._onGeolocationHide_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onGeolocationHide_0_flag = AttributeUpdaterFlag.UPDATE
            this._onGeolocationHide_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onGeolocationHide_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onGeolocationShow(value: ((value0: OnGeolocationShowEvent) => void) | undefined): this {
        if (((this._onGeolocationShow_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onGeolocationShow_0_flag = AttributeUpdaterFlag.UPDATE
            this._onGeolocationShow_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onGeolocationShow_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onRequestSelected(value: (() => void) | undefined): this {
        if (((this._onRequestSelected_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onRequestSelected_0_flag = AttributeUpdaterFlag.UPDATE
            this._onRequestSelected_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onRequestSelected_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onAlert(value: ((value0: OnAlertEvent) => boolean) | undefined): this {
        if (((this._onAlert_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onAlert_0_flag = AttributeUpdaterFlag.UPDATE
            this._onAlert_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onAlert_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onBeforeUnload(value: ((value0: OnBeforeUnloadEvent) => boolean) | undefined): this {
        if (((this._onBeforeUnload_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onBeforeUnload_0_flag = AttributeUpdaterFlag.UPDATE
            this._onBeforeUnload_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onBeforeUnload_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onConfirm(value: ((value0: OnConfirmEvent) => boolean) | undefined): this {
        if (((this._onConfirm_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onConfirm_0_flag = AttributeUpdaterFlag.UPDATE
            this._onConfirm_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onConfirm_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onPrompt(value: ((value0: OnPromptEvent) => boolean) | undefined): this {
        if (((this._onPrompt_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onPrompt_0_flag = AttributeUpdaterFlag.UPDATE
            this._onPrompt_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onPrompt_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onConsole(value: ((value0: OnConsoleEvent) => boolean) | undefined): this {
        if (((this._onConsole_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onConsole_0_flag = AttributeUpdaterFlag.UPDATE
            this._onConsole_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onConsole_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onErrorReceive(value: ((value0: OnErrorReceiveEvent) => void) | undefined): this {
        if (((this._onErrorReceive_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onErrorReceive_0_flag = AttributeUpdaterFlag.UPDATE
            this._onErrorReceive_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onErrorReceive_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onHttpErrorReceive(value: ((value0: OnHttpErrorReceiveEvent) => void) | undefined): this {
        if (((this._onHttpErrorReceive_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onHttpErrorReceive_0_flag = AttributeUpdaterFlag.UPDATE
            this._onHttpErrorReceive_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onHttpErrorReceive_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onDownloadStart(value: ((value0: OnDownloadStartEvent) => void) | undefined): this {
        if (((this._onDownloadStart_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onDownloadStart_0_flag = AttributeUpdaterFlag.UPDATE
            this._onDownloadStart_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onDownloadStart_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onRefreshAccessedHistory(value: ((value0: OnRefreshAccessedHistoryEvent) => void) | undefined): this {
        if (((this._onRefreshAccessedHistory_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onRefreshAccessedHistory_0_flag = AttributeUpdaterFlag.UPDATE
            this._onRefreshAccessedHistory_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onRefreshAccessedHistory_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onRenderExited(value: ((value0: OnRenderExitedEvent) => void) | undefined): this {
        if (((this._onRenderExited_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onRenderExited_0_flag = AttributeUpdaterFlag.UPDATE
            this._onRenderExited_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onRenderExited_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onShowFileSelector(value: ((value0: OnShowFileSelectorEvent) => boolean) | undefined): this {
        if (((this._onShowFileSelector_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onShowFileSelector_0_flag = AttributeUpdaterFlag.UPDATE
            this._onShowFileSelector_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onShowFileSelector_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onResourceLoad(value: ((value0: OnResourceLoadEvent) => void) | undefined): this {
        if (((this._onResourceLoad_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onResourceLoad_0_flag = AttributeUpdaterFlag.UPDATE
            this._onResourceLoad_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onResourceLoad_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onFullScreenExit(value: (() => void) | undefined): this {
        if (((this._onFullScreenExit_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onFullScreenExit_0_flag = AttributeUpdaterFlag.UPDATE
            this._onFullScreenExit_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onFullScreenExit_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onFullScreenEnter(value: OnFullScreenEnterCallback | undefined): this {
        if (((this._onFullScreenEnter_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onFullScreenEnter_0_flag = AttributeUpdaterFlag.UPDATE
            this._onFullScreenEnter_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onFullScreenEnter_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onScaleChange(value: ((value0: OnScaleChangeEvent) => void) | undefined): this {
        if (((this._onScaleChange_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onScaleChange_0_flag = AttributeUpdaterFlag.UPDATE
            this._onScaleChange_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onScaleChange_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onHttpAuthRequest(value: ((value0: OnHttpAuthRequestEvent) => boolean) | undefined): this {
        if (((this._onHttpAuthRequest_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onHttpAuthRequest_0_flag = AttributeUpdaterFlag.UPDATE
            this._onHttpAuthRequest_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onHttpAuthRequest_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onInterceptRequest(value: ((value0: OnInterceptRequestEvent) => WebResourceResponse | null) | undefined): this {
        if (((this._onInterceptRequest_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onInterceptRequest_0_flag = AttributeUpdaterFlag.UPDATE
            this._onInterceptRequest_0_0value = value
        } else
        {
            this._onInterceptRequest_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onPermissionRequest(value: ((value0: OnPermissionRequestEvent) => void) | undefined): this {
        if (((this._onPermissionRequest_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onPermissionRequest_0_flag = AttributeUpdaterFlag.UPDATE
            this._onPermissionRequest_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onPermissionRequest_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onScreenCaptureRequest(value: ((value0: OnScreenCaptureRequestEvent) => void) | undefined): this {
        if (((this._onScreenCaptureRequest_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onScreenCaptureRequest_0_flag = AttributeUpdaterFlag.UPDATE
            this._onScreenCaptureRequest_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onScreenCaptureRequest_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onContextMenuShow(value: ((value0: OnContextMenuShowEvent) => boolean) | undefined): this {
        if (((this._onContextMenuShow_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onContextMenuShow_0_flag = AttributeUpdaterFlag.UPDATE
            this._onContextMenuShow_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onContextMenuShow_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onContextMenuHide(value: OnContextMenuHideCallback | undefined): this {
        if (((this._onContextMenuHide_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onContextMenuHide_0_flag = AttributeUpdaterFlag.UPDATE
            this._onContextMenuHide_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onContextMenuHide_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    mediaPlayGestureAccess(value: boolean | undefined): this {
        if (((this._mediaPlayGestureAccess_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._mediaPlayGestureAccess_0_0value) !== (value)))
        {
            this._mediaPlayGestureAccess_0_flag = AttributeUpdaterFlag.UPDATE
            this._mediaPlayGestureAccess_0_0value = value
            this._state.fireChange()
        } else
        {
            this._mediaPlayGestureAccess_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onSearchResultReceive(value: ((value0: OnSearchResultReceiveEvent) => void) | undefined): this {
        if (((this._onSearchResultReceive_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onSearchResultReceive_0_flag = AttributeUpdaterFlag.UPDATE
            this._onSearchResultReceive_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onSearchResultReceive_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onScroll(value: ((value0: OnScrollEvent) => void) | undefined): this {
        if (((this._onScroll_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onScroll_0_flag = AttributeUpdaterFlag.UPDATE
            this._onScroll_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onScroll_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onSslErrorEventReceive(value: ((value0: OnSslErrorEventReceiveEvent) => void) | undefined): this {
        if (((this._onSslErrorEventReceive_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onSslErrorEventReceive_0_flag = AttributeUpdaterFlag.UPDATE
            this._onSslErrorEventReceive_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onSslErrorEventReceive_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onSslErrorEvent(value: OnSslErrorEventCallback | undefined): this {
        if (((this._onSslErrorEvent_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onSslErrorEvent_0_flag = AttributeUpdaterFlag.UPDATE
            this._onSslErrorEvent_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onSslErrorEvent_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onClientAuthenticationRequest(value: ((value0: OnClientAuthenticationEvent) => void) | undefined): this {
        if (((this._onClientAuthenticationRequest_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onClientAuthenticationRequest_0_flag = AttributeUpdaterFlag.UPDATE
            this._onClientAuthenticationRequest_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onClientAuthenticationRequest_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onWindowNew(value: ((value0: OnWindowNewEvent) => void) | undefined): this {
        if (((this._onWindowNew_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onWindowNew_0_flag = AttributeUpdaterFlag.UPDATE
            this._onWindowNew_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onWindowNew_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onWindowExit(value: (() => void) | undefined): this {
        if (((this._onWindowExit_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onWindowExit_0_flag = AttributeUpdaterFlag.UPDATE
            this._onWindowExit_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onWindowExit_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    multiWindowAccess(value: boolean | undefined): this {
        if (((this._multiWindowAccess_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._multiWindowAccess_0_0value) !== (value)))
        {
            this._multiWindowAccess_0_flag = AttributeUpdaterFlag.UPDATE
            this._multiWindowAccess_0_0value = value
            this._state.fireChange()
        } else
        {
            this._multiWindowAccess_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onInterceptKeyEvent(value: ((event: KeyEvent) => boolean) | undefined): this {
        if (((this._onInterceptKeyEvent_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onInterceptKeyEvent_0_flag = AttributeUpdaterFlag.UPDATE
            this._onInterceptKeyEvent_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onInterceptKeyEvent_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    webStandardFont(value: string | undefined): this {
        if (((this._webStandardFont_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._webStandardFont_0_0value) !== (value)))
        {
            this._webStandardFont_0_flag = AttributeUpdaterFlag.UPDATE
            this._webStandardFont_0_0value = value
            this._state.fireChange()
        } else
        {
            this._webStandardFont_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    webSerifFont(value: string | undefined): this {
        if (((this._webSerifFont_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._webSerifFont_0_0value) !== (value)))
        {
            this._webSerifFont_0_flag = AttributeUpdaterFlag.UPDATE
            this._webSerifFont_0_0value = value
            this._state.fireChange()
        } else
        {
            this._webSerifFont_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    webSansSerifFont(value: string | undefined): this {
        if (((this._webSansSerifFont_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._webSansSerifFont_0_0value) !== (value)))
        {
            this._webSansSerifFont_0_flag = AttributeUpdaterFlag.UPDATE
            this._webSansSerifFont_0_0value = value
            this._state.fireChange()
        } else
        {
            this._webSansSerifFont_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    webFixedFont(value: string | undefined): this {
        if (((this._webFixedFont_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._webFixedFont_0_0value) !== (value)))
        {
            this._webFixedFont_0_flag = AttributeUpdaterFlag.UPDATE
            this._webFixedFont_0_0value = value
            this._state.fireChange()
        } else
        {
            this._webFixedFont_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    webFantasyFont(value: string | undefined): this {
        if (((this._webFantasyFont_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._webFantasyFont_0_0value) !== (value)))
        {
            this._webFantasyFont_0_flag = AttributeUpdaterFlag.UPDATE
            this._webFantasyFont_0_0value = value
            this._state.fireChange()
        } else
        {
            this._webFantasyFont_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    webCursiveFont(value: string | undefined): this {
        if (((this._webCursiveFont_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._webCursiveFont_0_0value) !== (value)))
        {
            this._webCursiveFont_0_flag = AttributeUpdaterFlag.UPDATE
            this._webCursiveFont_0_0value = value
            this._state.fireChange()
        } else
        {
            this._webCursiveFont_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    defaultFixedFontSize(value: int32 | undefined): this {
        if (((this._defaultFixedFontSize_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._defaultFixedFontSize_0_0value) !== (value)))
        {
            this._defaultFixedFontSize_0_flag = AttributeUpdaterFlag.UPDATE
            this._defaultFixedFontSize_0_0value = value
            this._state.fireChange()
        } else
        {
            this._defaultFixedFontSize_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    defaultFontSize(value: int32 | undefined): this {
        if (((this._defaultFontSize_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._defaultFontSize_0_0value) !== (value)))
        {
            this._defaultFontSize_0_flag = AttributeUpdaterFlag.UPDATE
            this._defaultFontSize_0_0value = value
            this._state.fireChange()
        } else
        {
            this._defaultFontSize_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    minFontSize(value: int32 | undefined): this {
        if (((this._minFontSize_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._minFontSize_0_0value) !== (value)))
        {
            this._minFontSize_0_flag = AttributeUpdaterFlag.UPDATE
            this._minFontSize_0_0value = value
            this._state.fireChange()
        } else
        {
            this._minFontSize_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    minLogicalFontSize(value: int32 | undefined): this {
        if (((this._minLogicalFontSize_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._minLogicalFontSize_0_0value) !== (value)))
        {
            this._minLogicalFontSize_0_flag = AttributeUpdaterFlag.UPDATE
            this._minLogicalFontSize_0_0value = value
            this._state.fireChange()
        } else
        {
            this._minLogicalFontSize_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    defaultTextEncodingFormat(value: string | undefined): this {
        if (((this._defaultTextEncodingFormat_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._defaultTextEncodingFormat_0_0value) !== (value)))
        {
            this._defaultTextEncodingFormat_0_flag = AttributeUpdaterFlag.UPDATE
            this._defaultTextEncodingFormat_0_0value = value
            this._state.fireChange()
        } else
        {
            this._defaultTextEncodingFormat_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    forceDisplayScrollBar(value: boolean | undefined): this {
        if (((this._forceDisplayScrollBar_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._forceDisplayScrollBar_0_0value) !== (value)))
        {
            this._forceDisplayScrollBar_0_flag = AttributeUpdaterFlag.UPDATE
            this._forceDisplayScrollBar_0_0value = value
            this._state.fireChange()
        } else
        {
            this._forceDisplayScrollBar_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    blockNetwork(value: boolean | undefined): this {
        if (((this._blockNetwork_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._blockNetwork_0_0value) !== (value)))
        {
            this._blockNetwork_0_flag = AttributeUpdaterFlag.UPDATE
            this._blockNetwork_0_0value = value
            this._state.fireChange()
        } else
        {
            this._blockNetwork_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    horizontalScrollBarAccess(value: boolean | undefined): this {
        if (((this._horizontalScrollBarAccess_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._horizontalScrollBarAccess_0_0value) !== (value)))
        {
            this._horizontalScrollBarAccess_0_flag = AttributeUpdaterFlag.UPDATE
            this._horizontalScrollBarAccess_0_0value = value
            this._state.fireChange()
        } else
        {
            this._horizontalScrollBarAccess_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    verticalScrollBarAccess(value: boolean | undefined): this {
        if (((this._verticalScrollBarAccess_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._verticalScrollBarAccess_0_0value) !== (value)))
        {
            this._verticalScrollBarAccess_0_flag = AttributeUpdaterFlag.UPDATE
            this._verticalScrollBarAccess_0_0value = value
            this._state.fireChange()
        } else
        {
            this._verticalScrollBarAccess_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onTouchIconUrlReceived(value: ((value0: OnTouchIconUrlReceivedEvent) => void) | undefined): this {
        if (((this._onTouchIconUrlReceived_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onTouchIconUrlReceived_0_flag = AttributeUpdaterFlag.UPDATE
            this._onTouchIconUrlReceived_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onTouchIconUrlReceived_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onFaviconReceived(value: ((value0: OnFaviconReceivedEvent) => void) | undefined): this {
        if (((this._onFaviconReceived_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onFaviconReceived_0_flag = AttributeUpdaterFlag.UPDATE
            this._onFaviconReceived_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onFaviconReceived_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onPageVisible(value: ((value0: OnPageVisibleEvent) => void) | undefined): this {
        if (((this._onPageVisible_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onPageVisible_0_flag = AttributeUpdaterFlag.UPDATE
            this._onPageVisible_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onPageVisible_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onDataResubmitted(value: ((value0: OnDataResubmittedEvent) => void) | undefined): this {
        if (((this._onDataResubmitted_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onDataResubmitted_0_flag = AttributeUpdaterFlag.UPDATE
            this._onDataResubmitted_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onDataResubmitted_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    pinchSmooth(value: boolean | undefined): this {
        if (((this._pinchSmooth_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._pinchSmooth_0_0value) !== (value)))
        {
            this._pinchSmooth_0_flag = AttributeUpdaterFlag.UPDATE
            this._pinchSmooth_0_0value = value
            this._state.fireChange()
        } else
        {
            this._pinchSmooth_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    allowWindowOpenMethod(value: boolean | undefined): this {
        if (((this._allowWindowOpenMethod_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._allowWindowOpenMethod_0_0value) !== (value)))
        {
            this._allowWindowOpenMethod_0_flag = AttributeUpdaterFlag.UPDATE
            this._allowWindowOpenMethod_0_0value = value
            this._state.fireChange()
        } else
        {
            this._allowWindowOpenMethod_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onAudioStateChanged(value: ((value0: OnAudioStateChangedEvent) => void) | undefined): this {
        if (((this._onAudioStateChanged_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onAudioStateChanged_0_flag = AttributeUpdaterFlag.UPDATE
            this._onAudioStateChanged_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onAudioStateChanged_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onFirstContentfulPaint(value: ((value0: OnFirstContentfulPaintEvent) => void) | undefined): this {
        if (((this._onFirstContentfulPaint_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onFirstContentfulPaint_0_flag = AttributeUpdaterFlag.UPDATE
            this._onFirstContentfulPaint_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onFirstContentfulPaint_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onFirstMeaningfulPaint(value: OnFirstMeaningfulPaintCallback | undefined): this {
        if (((this._onFirstMeaningfulPaint_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onFirstMeaningfulPaint_0_flag = AttributeUpdaterFlag.UPDATE
            this._onFirstMeaningfulPaint_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onFirstMeaningfulPaint_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onLargestContentfulPaint(value: OnLargestContentfulPaintCallback | undefined): this {
        if (((this._onLargestContentfulPaint_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onLargestContentfulPaint_0_flag = AttributeUpdaterFlag.UPDATE
            this._onLargestContentfulPaint_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onLargestContentfulPaint_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onLoadIntercept(value: ((value0: OnLoadInterceptEvent) => boolean) | undefined): this {
        if (((this._onLoadIntercept_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onLoadIntercept_0_flag = AttributeUpdaterFlag.UPDATE
            this._onLoadIntercept_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onLoadIntercept_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onControllerAttached(value: (() => void) | undefined): this {
        if (((this._onControllerAttached_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onControllerAttached_0_flag = AttributeUpdaterFlag.UPDATE
            this._onControllerAttached_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onControllerAttached_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onOverScroll(value: ((value0: OnOverScrollEvent) => void) | undefined): this {
        if (((this._onOverScroll_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onOverScroll_0_flag = AttributeUpdaterFlag.UPDATE
            this._onOverScroll_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onOverScroll_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onSafeBrowsingCheckResult(value: OnSafeBrowsingCheckResultCallback | undefined): this {
        if (((this._onSafeBrowsingCheckResult_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onSafeBrowsingCheckResult_0_flag = AttributeUpdaterFlag.UPDATE
            this._onSafeBrowsingCheckResult_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onSafeBrowsingCheckResult_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onNavigationEntryCommitted(value: OnNavigationEntryCommittedCallback | undefined): this {
        if (((this._onNavigationEntryCommitted_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onNavigationEntryCommitted_0_flag = AttributeUpdaterFlag.UPDATE
            this._onNavigationEntryCommitted_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onNavigationEntryCommitted_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onIntelligentTrackingPreventionResult(value: OnIntelligentTrackingPreventionCallback | undefined): this {
        if (((this._onIntelligentTrackingPreventionResult_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onIntelligentTrackingPreventionResult_0_flag = AttributeUpdaterFlag.UPDATE
            this._onIntelligentTrackingPreventionResult_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onIntelligentTrackingPreventionResult_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    javaScriptOnDocumentStart(value: Array<ScriptItem> | undefined): this {
        if (((this._javaScriptOnDocumentStart_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._javaScriptOnDocumentStart_0_flag = AttributeUpdaterFlag.UPDATE
            this._javaScriptOnDocumentStart_0_0value = value
            this._state.fireChange()
        } else
        {
            this._javaScriptOnDocumentStart_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    javaScriptOnDocumentEnd(value: Array<ScriptItem> | undefined): this {
        if (((this._javaScriptOnDocumentEnd_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._javaScriptOnDocumentEnd_0_flag = AttributeUpdaterFlag.UPDATE
            this._javaScriptOnDocumentEnd_0_0value = value
            this._state.fireChange()
        } else
        {
            this._javaScriptOnDocumentEnd_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    layoutMode(value: WebLayoutMode | undefined): this {
        if (((this._layoutMode_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._layoutMode_0_flag = AttributeUpdaterFlag.UPDATE
            this._layoutMode_0_0value = value
            this._state.fireChange()
        } else
        {
            this._layoutMode_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    nestedScroll(value: NestedScrollOptions | NestedScrollOptionsExt | undefined): this {
        if (((this._nestedScroll_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._nestedScroll_0_flag = AttributeUpdaterFlag.UPDATE
            this._nestedScroll_0_0value = value
            this._state.fireChange()
        } else
        {
            this._nestedScroll_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    enableNativeEmbedMode(value: boolean | undefined): this {
        if (((this._enableNativeEmbedMode_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._enableNativeEmbedMode_0_0value) !== (value)))
        {
            this._enableNativeEmbedMode_0_flag = AttributeUpdaterFlag.UPDATE
            this._enableNativeEmbedMode_0_0value = value
            this._state.fireChange()
        } else
        {
            this._enableNativeEmbedMode_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onNativeEmbedLifecycleChange(value: ((event: NativeEmbedDataInfo) => void) | undefined): this {
        if (((this._onNativeEmbedLifecycleChange_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onNativeEmbedLifecycleChange_0_flag = AttributeUpdaterFlag.UPDATE
            this._onNativeEmbedLifecycleChange_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onNativeEmbedLifecycleChange_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onNativeEmbedVisibilityChange(value: OnNativeEmbedVisibilityChangeCallback | undefined): this {
        if (((this._onNativeEmbedVisibilityChange_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onNativeEmbedVisibilityChange_0_flag = AttributeUpdaterFlag.UPDATE
            this._onNativeEmbedVisibilityChange_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onNativeEmbedVisibilityChange_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onNativeEmbedGestureEvent(value: ((event: NativeEmbedTouchInfo) => void) | undefined): this {
        if (((this._onNativeEmbedGestureEvent_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onNativeEmbedGestureEvent_0_flag = AttributeUpdaterFlag.UPDATE
            this._onNativeEmbedGestureEvent_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onNativeEmbedGestureEvent_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    copyOptions(value: CopyOptions | undefined): this {
        if (((this._copyOptions_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._copyOptions_0_flag = AttributeUpdaterFlag.UPDATE
            this._copyOptions_0_0value = value
            this._state.fireChange()
        } else
        {
            this._copyOptions_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onOverrideUrlLoading(value: OnOverrideUrlLoadingCallback | undefined): this {
        if (((this._onOverrideUrlLoading_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onOverrideUrlLoading_0_flag = AttributeUpdaterFlag.UPDATE
            this._onOverrideUrlLoading_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onOverrideUrlLoading_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    textAutosizing(value: boolean | undefined): this {
        if (((this._textAutosizing_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._textAutosizing_0_0value) !== (value)))
        {
            this._textAutosizing_0_flag = AttributeUpdaterFlag.UPDATE
            this._textAutosizing_0_0value = value
            this._state.fireChange()
        } else
        {
            this._textAutosizing_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    enableNativeMediaPlayer(value: NativeMediaPlayerConfig | undefined): this {
        if (((this._enableNativeMediaPlayer_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._enableNativeMediaPlayer_0_flag = AttributeUpdaterFlag.UPDATE
            this._enableNativeMediaPlayer_0_0value = value
            this._state.fireChange()
        } else
        {
            this._enableNativeMediaPlayer_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onRenderProcessNotResponding(value: OnRenderProcessNotRespondingCallback | undefined): this {
        if (((this._onRenderProcessNotResponding_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onRenderProcessNotResponding_0_flag = AttributeUpdaterFlag.UPDATE
            this._onRenderProcessNotResponding_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onRenderProcessNotResponding_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onRenderProcessResponding(value: OnRenderProcessRespondingCallback | undefined): this {
        if (((this._onRenderProcessResponding_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onRenderProcessResponding_0_flag = AttributeUpdaterFlag.UPDATE
            this._onRenderProcessResponding_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onRenderProcessResponding_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onViewportFitChanged(value: OnViewportFitChangedCallback | undefined): this {
        if (((this._onViewportFitChanged_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onViewportFitChanged_0_flag = AttributeUpdaterFlag.UPDATE
            this._onViewportFitChanged_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onViewportFitChanged_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onInterceptKeyboardAttach(value: WebKeyboardCallback | undefined): this {
        if (((this._onInterceptKeyboardAttach_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onInterceptKeyboardAttach_0_flag = AttributeUpdaterFlag.UPDATE
            this._onInterceptKeyboardAttach_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onInterceptKeyboardAttach_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onAdsBlocked(value: OnAdsBlockedCallback | undefined): this {
        if (((this._onAdsBlocked_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onAdsBlocked_0_flag = AttributeUpdaterFlag.UPDATE
            this._onAdsBlocked_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onAdsBlocked_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    keyboardAvoidMode(value: WebKeyboardAvoidMode | undefined): this {
        if (((this._keyboardAvoidMode_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._keyboardAvoidMode_0_flag = AttributeUpdaterFlag.UPDATE
            this._keyboardAvoidMode_0_0value = value
            this._state.fireChange()
        } else
        {
            this._keyboardAvoidMode_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    editMenuOptions(value: EditMenuOptions | undefined): this {
        if (((this._editMenuOptions_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._editMenuOptions_0_flag = AttributeUpdaterFlag.UPDATE
            this._editMenuOptions_0_0value = value
            this._state.fireChange()
        } else
        {
            this._editMenuOptions_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    enableHapticFeedback(value: boolean | undefined): this {
        if (((this._enableHapticFeedback_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._enableHapticFeedback_0_0value) !== (value)))
        {
            this._enableHapticFeedback_0_flag = AttributeUpdaterFlag.UPDATE
            this._enableHapticFeedback_0_0value = value
            this._state.fireChange()
        } else
        {
            this._enableHapticFeedback_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    optimizeParserBudget(value: boolean | undefined): this {
        if (((this._optimizeParserBudget_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._optimizeParserBudget_0_0value) !== (value)))
        {
            this._optimizeParserBudget_0_flag = AttributeUpdaterFlag.UPDATE
            this._optimizeParserBudget_0_0value = value
            this._state.fireChange()
        } else
        {
            this._optimizeParserBudget_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    enableFollowSystemFontWeight(value: boolean | undefined): this {
        if (((this._enableFollowSystemFontWeight_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._enableFollowSystemFontWeight_0_0value) !== (value)))
        {
            this._enableFollowSystemFontWeight_0_flag = AttributeUpdaterFlag.UPDATE
            this._enableFollowSystemFontWeight_0_0value = value
            this._state.fireChange()
        } else
        {
            this._enableFollowSystemFontWeight_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    enableWebAVSession(value: boolean | undefined): this {
        if (((this._enableWebAVSession_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._enableWebAVSession_0_0value) !== (value)))
        {
            this._enableWebAVSession_0_flag = AttributeUpdaterFlag.UPDATE
            this._enableWebAVSession_0_0value = value
            this._state.fireChange()
        } else
        {
            this._enableWebAVSession_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    runJavaScriptOnDocumentStart(value: Array<ScriptItem> | undefined): this {
        if (((this._runJavaScriptOnDocumentStart_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._runJavaScriptOnDocumentStart_0_flag = AttributeUpdaterFlag.UPDATE
            this._runJavaScriptOnDocumentStart_0_0value = value
            this._state.fireChange()
        } else
        {
            this._runJavaScriptOnDocumentStart_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    runJavaScriptOnDocumentEnd(value: Array<ScriptItem> | undefined): this {
        if (((this._runJavaScriptOnDocumentEnd_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._runJavaScriptOnDocumentEnd_0_flag = AttributeUpdaterFlag.UPDATE
            this._runJavaScriptOnDocumentEnd_0_0value = value
            this._state.fireChange()
        } else
        {
            this._runJavaScriptOnDocumentEnd_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    runJavaScriptOnHeadEnd(value: Array<ScriptItem> | undefined): this {
        if (((this._runJavaScriptOnHeadEnd_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._runJavaScriptOnHeadEnd_0_flag = AttributeUpdaterFlag.UPDATE
            this._runJavaScriptOnHeadEnd_0_0value = value
            this._state.fireChange()
        } else
        {
            this._runJavaScriptOnHeadEnd_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    nativeEmbedOptions(value: EmbedOptions | undefined): this {
        if (((this._nativeEmbedOptions_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._nativeEmbedOptions_0_flag = AttributeUpdaterFlag.UPDATE
            this._nativeEmbedOptions_0_0value = value
            this._state.fireChange()
        } else
        {
            this._nativeEmbedOptions_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    registerNativeEmbedRule(tag: string | undefined, type: string | undefined): this {
        if (((this._registerNativeEmbedRule_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._registerNativeEmbedRule_0_0value) !== (tag)) || ((this._registerNativeEmbedRule_0_1value) !== (type)))
        {
            this._registerNativeEmbedRule_0_flag = AttributeUpdaterFlag.UPDATE
            this._registerNativeEmbedRule_0_0value = tag
            this._registerNativeEmbedRule_0_1value = type
            this._state.fireChange()
        } else
        {
            this._registerNativeEmbedRule_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    bindSelectionMenu(elementType: WebElementType | undefined, content: CustomBuilder | undefined, responseType: WebResponseType | undefined, options?: SelectionMenuOptionsExt): this {
        if (((this._bindSelectionMenu_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true) || (true) || (true) || (true))
        {
            this._bindSelectionMenu_0_flag = AttributeUpdaterFlag.UPDATE
            this._bindSelectionMenu_0_0value = elementType
            this._bindSelectionMenu_0_1value = content
            this._bindSelectionMenu_0_2value = responseType
            this._bindSelectionMenu_0_3value = options
            this._state.fireChange()
        } else
        {
            this._bindSelectionMenu_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<WebAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
