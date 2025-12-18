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

import { CommonMethodModifier } from './CommonMethodModifier'
import { AttributeModifier, hookJavaScriptProxy } from '#handwritten'
import { AttributeUpdaterFlag } from './AttributeUpdaterFlag'
import { PeerNode } from './PeerNode'
import { ArkWebPeer, MixedMode, JavaScriptProxy, CacheMode, WebDarkMode, WebMediaOptions, OverScrollMode, BlurOnKeyboardHideMode, OnPageBeginEvent, OnPageEndEvent, OnLoadStartedEvent, OnLoadFinishedEvent, OnProgressChangeEvent, OnTitleReceiveEvent, OnGeolocationShowEvent, OnAlertEvent, OnBeforeUnloadEvent, OnConfirmEvent, OnPromptEvent, OnConsoleEvent, OnErrorReceiveEvent, OnHttpErrorReceiveEvent, OnDownloadStartEvent, OnRefreshAccessedHistoryEvent, OnRenderExitedEvent, OnShowFileSelectorEvent, OnResourceLoadEvent, OnFullScreenEnterCallback, FullScreenEnterEvent, OnScaleChangeEvent, OnHttpAuthRequestEvent, OnInterceptRequestEvent, WebResourceResponse, OnPermissionRequestEvent, OnScreenCaptureRequestEvent, OnContextMenuShowEvent, OnContextMenuHideCallback, OnSearchResultReceiveEvent, OnScrollEvent, OnSslErrorEventReceiveEvent, OnSslErrorEventCallback, SslErrorEvent, OnClientAuthenticationEvent, OnWindowNewEvent, OnTouchIconUrlReceivedEvent, OnFaviconReceivedEvent, OnPageVisibleEvent, OnDataResubmittedEvent, OnAudioStateChangedEvent, OnFirstContentfulPaintEvent, OnFirstMeaningfulPaintCallback, FirstMeaningfulPaint, OnLargestContentfulPaintCallback, LargestContentfulPaint, OnLoadInterceptEvent, OnOverScrollEvent, OnSafeBrowsingCheckResultCallback, ThreatType, OnNavigationEntryCommittedCallback, LoadCommittedDetails, OnIntelligentTrackingPreventionCallback, IntelligentTrackingPreventionDetails, ScriptItem, WebLayoutMode, NestedScrollOptionsExt, NativeEmbedDataInfo, OnNativeEmbedVisibilityChangeCallback, NativeEmbedVisibilityInfo, NativeEmbedTouchInfo, OnOverrideUrlLoadingCallback, WebResourceRequest, NativeMediaPlayerConfig, OnRenderProcessNotRespondingCallback, RenderProcessNotRespondingData, OnRenderProcessRespondingCallback, OnViewportFitChangedCallback, ViewportFit, WebKeyboardCallback, WebKeyboardCallbackInfo, OnAdsBlockedCallback, AdsBlockedDetails, WebKeyboardAvoidMode, EmbedOptions, WebAttribute, WebElementType, WebResponseType, SelectionMenuOptionsExt } from './component/web'
import { int32, int64 } from '@koalaui/common'
import { ModifierState } from './CommonModifier'
import { CommonMethod, Callback as arkui_component_common_Callback, KeyEvent, NestedScrollOptions } from './component/common'
import { CopyOptions } from './component/enums'
import { EditMenuOptions } from './component/textCommon'
import { CustomBuilder } from './component/builder'
export class WebModifier extends CommonMethodModifier implements WebAttribute,AttributeModifier<WebAttribute> {
    _instanceId: number = -1;
    _state: ModifierState = new ModifierState;
    _addr: ArrayBuffer = new ArrayBuffer(4096);
    _flagArray: Uint8Array = new Uint8Array(this._addr);
    constructor() {
        super();
        this._flagArray.fill(0);
    }
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: WebAttribute): void { }
    applyPressedAttribute(instance: WebAttribute): void { }
    applyFocusedAttribute(instance: WebAttribute): void { }
    applyDisabledAttribute(instance: WebAttribute): void { }
    applySelectedAttribute(instance: WebAttribute): void { }
    public _javaScriptAccess_0_0value?: boolean | undefined
    public _fileAccess_0_0value?: boolean | undefined
    public _onlineImageAccess_0_0value?: boolean | undefined
    public _domStorageAccess_0_0value?: boolean | undefined
    public _imageAccess_0_0value?: boolean | undefined
    public _mixedMode_0_0value?: MixedMode | undefined
    public _zoomAccess_0_0value?: boolean | undefined
    public _geolocationAccess_0_0value?: boolean | undefined
    public _javaScriptProxy_0_0value?: JavaScriptProxy | undefined
    public _cacheMode_0_0value?: CacheMode | undefined
    public _darkMode_0_0value?: WebDarkMode | undefined
    public _forceDarkAccess_0_0value?: boolean | undefined
    public _mediaOptions_0_0value?: WebMediaOptions | undefined
    public _overviewModeAccess_0_0value?: boolean | undefined
    public _overScrollMode_0_0value?: OverScrollMode | undefined
    public _blurOnKeyboardHideMode_0_0value?: BlurOnKeyboardHideMode | undefined
    public _textZoomRatio_0_0value?: int32 | undefined
    public _databaseAccess_0_0value?: boolean | undefined
    public _initialScale_0_0value?: double | undefined
    public _metaViewport_0_0value?: boolean | undefined
    public _onPageBegin_0_0value?: arkui_component_common_Callback<OnPageBeginEvent, void> | undefined
    public _onPageEnd_0_0value?: arkui_component_common_Callback<OnPageEndEvent, void> | undefined
    public _onLoadStarted_0_0value?: arkui_component_common_Callback<OnLoadStartedEvent, void> | undefined
    public _onLoadFinished_0_0value?: arkui_component_common_Callback<OnLoadFinishedEvent, void> | undefined
    public _onProgressChange_0_0value?: arkui_component_common_Callback<OnProgressChangeEvent, void> | undefined
    public _onTitleReceive_0_0value?: arkui_component_common_Callback<OnTitleReceiveEvent, void> | undefined
    public _onGeolocationHide_0_0value?: (() => void) | undefined
    public _onGeolocationShow_0_0value?: arkui_component_common_Callback<OnGeolocationShowEvent, void> | undefined
    public _onRequestSelected_0_0value?: (() => void) | undefined
    public _onAlert_0_0value?: arkui_component_common_Callback<OnAlertEvent, boolean> | undefined
    public _onBeforeUnload_0_0value?: arkui_component_common_Callback<OnBeforeUnloadEvent, boolean> | undefined
    public _onConfirm_0_0value?: arkui_component_common_Callback<OnConfirmEvent, boolean> | undefined
    public _onPrompt_0_0value?: arkui_component_common_Callback<OnPromptEvent, boolean> | undefined
    public _onConsole_0_0value?: arkui_component_common_Callback<OnConsoleEvent, boolean> | undefined
    public _onErrorReceive_0_0value?: arkui_component_common_Callback<OnErrorReceiveEvent, void> | undefined
    public _onHttpErrorReceive_0_0value?: arkui_component_common_Callback<OnHttpErrorReceiveEvent, void> | undefined
    public _onDownloadStart_0_0value?: arkui_component_common_Callback<OnDownloadStartEvent, void> | undefined
    public _onRefreshAccessedHistory_0_0value?: arkui_component_common_Callback<OnRefreshAccessedHistoryEvent, void> | undefined
    public _onRenderExited_0_0value?: arkui_component_common_Callback<OnRenderExitedEvent, void> | undefined
    public _onShowFileSelector_0_0value?: arkui_component_common_Callback<OnShowFileSelectorEvent, boolean> | undefined
    public _onResourceLoad_0_0value?: arkui_component_common_Callback<OnResourceLoadEvent, void> | undefined
    public _onFullScreenExit_0_0value?: (() => void) | undefined
    public _onFullScreenEnter_0_0value?: OnFullScreenEnterCallback | undefined
    public _onScaleChange_0_0value?: arkui_component_common_Callback<OnScaleChangeEvent, void> | undefined
    public _onHttpAuthRequest_0_0value?: arkui_component_common_Callback<OnHttpAuthRequestEvent, boolean> | undefined
    public _onInterceptRequest_0_0value?: arkui_component_common_Callback<OnInterceptRequestEvent, WebResourceResponse | null> | undefined
    public _onPermissionRequest_0_0value?: arkui_component_common_Callback<OnPermissionRequestEvent, void> | undefined
    public _onScreenCaptureRequest_0_0value?: arkui_component_common_Callback<OnScreenCaptureRequestEvent, void> | undefined
    public _onContextMenuShow_0_0value?: arkui_component_common_Callback<OnContextMenuShowEvent, boolean> | undefined
    public _onContextMenuHide_0_0value?: OnContextMenuHideCallback | undefined
    public _mediaPlayGestureAccess_0_0value?: boolean | undefined
    public _onSearchResultReceive_0_0value?: arkui_component_common_Callback<OnSearchResultReceiveEvent, void> | undefined
    public _onScroll_0_0value?: arkui_component_common_Callback<OnScrollEvent, void> | undefined
    public _onSslErrorEventReceive_0_0value?: arkui_component_common_Callback<OnSslErrorEventReceiveEvent, void> | undefined
    public _onSslErrorEvent_0_0value?: OnSslErrorEventCallback | undefined
    public _onClientAuthenticationRequest_0_0value?: arkui_component_common_Callback<OnClientAuthenticationEvent, void> | undefined
    public _onWindowNew_0_0value?: arkui_component_common_Callback<OnWindowNewEvent, void> | undefined
    public _onWindowExit_0_0value?: (() => void) | undefined
    public _multiWindowAccess_0_0value?: boolean | undefined
    public _onInterceptKeyEvent_0_0value?: ((event: KeyEvent) => boolean) | undefined
    public _webStandardFont_0_0value?: string | undefined
    public _webSerifFont_0_0value?: string | undefined
    public _webSansSerifFont_0_0value?: string | undefined
    public _webFixedFont_0_0value?: string | undefined
    public _webFantasyFont_0_0value?: string | undefined
    public _webCursiveFont_0_0value?: string | undefined
    public _defaultFixedFontSize_0_0value?: int32 | undefined
    public _defaultFontSize_0_0value?: int32 | undefined
    public _minFontSize_0_0value?: int32 | undefined
    public _minLogicalFontSize_0_0value?: int32 | undefined
    public _defaultTextEncodingFormat_0_0value?: string | undefined
    public _forceDisplayScrollBar_0_0value?: boolean | undefined
    public _blockNetwork_0_0value?: boolean | undefined
    public _horizontalScrollBarAccess_0_0value?: boolean | undefined
    public _verticalScrollBarAccess_0_0value?: boolean | undefined
    public _onTouchIconUrlReceived_0_0value?: arkui_component_common_Callback<OnTouchIconUrlReceivedEvent, void> | undefined
    public _onFaviconReceived_0_0value?: arkui_component_common_Callback<OnFaviconReceivedEvent, void> | undefined
    public _onPageVisible_0_0value?: arkui_component_common_Callback<OnPageVisibleEvent, void> | undefined
    public _onDataResubmitted_0_0value?: arkui_component_common_Callback<OnDataResubmittedEvent, void> | undefined
    public _pinchSmooth_0_0value?: boolean | undefined
    public _allowWindowOpenMethod_0_0value?: boolean | undefined
    public _onAudioStateChanged_0_0value?: arkui_component_common_Callback<OnAudioStateChangedEvent, void> | undefined
    public _onFirstContentfulPaint_0_0value?: arkui_component_common_Callback<OnFirstContentfulPaintEvent, void> | undefined
    public _onFirstMeaningfulPaint_0_0value?: OnFirstMeaningfulPaintCallback | undefined
    public _onLargestContentfulPaint_0_0value?: OnLargestContentfulPaintCallback | undefined
    public _onLoadIntercept_0_0value?: arkui_component_common_Callback<OnLoadInterceptEvent, boolean> | undefined
    public _onControllerAttached_0_0value?: (() => void) | undefined
    public _onOverScroll_0_0value?: arkui_component_common_Callback<OnOverScrollEvent, void> | undefined
    public _onSafeBrowsingCheckResult_0_0value?: OnSafeBrowsingCheckResultCallback | undefined
    public _onNavigationEntryCommitted_0_0value?: OnNavigationEntryCommittedCallback | undefined
    public _onIntelligentTrackingPreventionResult_0_0value?: OnIntelligentTrackingPreventionCallback | undefined
    public _javaScriptOnDocumentStart_0_0value?: Array<ScriptItem> | undefined
    public _javaScriptOnDocumentEnd_0_0value?: Array<ScriptItem> | undefined
    public _layoutMode_0_0value?: WebLayoutMode | undefined
    public _nestedScroll_0_0value?: NestedScrollOptions | NestedScrollOptionsExt | undefined
    public _enableNativeEmbedMode_0_0value?: boolean | undefined
    public _onNativeEmbedLifecycleChange_0_0value?: ((event: NativeEmbedDataInfo) => void) | undefined
    public _onNativeEmbedVisibilityChange_0_0value?: OnNativeEmbedVisibilityChangeCallback | undefined
    public _onNativeEmbedGestureEvent_0_0value?: ((event: NativeEmbedTouchInfo) => void) | undefined
    public _copyOptions_0_0value?: CopyOptions | undefined
    public _onOverrideUrlLoading_0_0value?: OnOverrideUrlLoadingCallback | undefined
    public _textAutosizing_0_0value?: boolean | undefined
    public _enableNativeMediaPlayer_0_0value?: NativeMediaPlayerConfig | undefined
    public _onRenderProcessNotResponding_0_0value?: OnRenderProcessNotRespondingCallback | undefined
    public _onRenderProcessResponding_0_0value?: OnRenderProcessRespondingCallback | undefined
    public _onViewportFitChanged_0_0value?: OnViewportFitChangedCallback | undefined
    public _onInterceptKeyboardAttach_0_0value?: WebKeyboardCallback | undefined
    public _onAdsBlocked_0_0value?: OnAdsBlockedCallback | undefined
    public _keyboardAvoidMode_0_0value?: WebKeyboardAvoidMode | undefined
    public _editMenuOptions_0_0value?: EditMenuOptions | undefined
    public _enableHapticFeedback_0_0value?: boolean | undefined
    public _enableFollowSystemFontWeight_0_0value?: boolean | undefined
    public _enableWebAVSession_0_0value?: boolean | undefined
    public _optimizeParserBudget_0_0value?: boolean | undefined
    public _runJavaScriptOnDocumentStart_0_0value?: Array<ScriptItem> | undefined
    public _runJavaScriptOnDocumentEnd_0_0value?: Array<ScriptItem> | undefined
    public _runJavaScriptOnHeadEnd_0_0value?: Array<ScriptItem> | undefined
    public _nativeEmbedOptions_0_0value?: EmbedOptions | undefined
    public _registerNativeEmbedRule_0_0value?: string | undefined
    public _registerNativeEmbedRule_0_1value?: string | undefined
    public _bindSelectionMenu_0_0value?: WebElementType | undefined
    public _bindSelectionMenu_0_1value?: CustomBuilder | undefined
    public _bindSelectionMenu_0_2value?: WebResponseType | undefined
    public _bindSelectionMenu_0_3value?: SelectionMenuOptionsExt | undefined
    applyModifierPatch(node: object): void {
        super.applyModifierPatch(node)
        this._state.addRef()
        const peer = node as ArkWebPeer;
        const flagArray = this._flagArray;
        this.applyModifierPatch0(peer, flagArray);
        this.applyModifierPatch1(peer, flagArray);
        this.applyModifierPatch2(peer, flagArray);
        this.applyModifierPatch3(peer, flagArray);
        this.applyModifierPatch4(peer, flagArray);
        this.applyModifierPatch5(peer, flagArray);
    }
    applyModifierPatch0(peer: ArkWebPeer, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1: {
                    peer.setJavaScriptAccessAttribute((this._javaScriptAccess_0_0value as boolean | undefined));
                    flagArray[0] = 2;
                    break;
                }
                case 3: {
                    flagArray[0] = 2;
                    break;
                }
                default: {
                    flagArray[0] = 0;
                    peer.setJavaScriptAccessAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1: {
                    peer.setFileAccessAttribute((this._fileAccess_0_0value as boolean | undefined));
                    flagArray[1] = 2;
                    break;
                }
                case 3: {
                    flagArray[1] = 2;
                    break;
                }
                default: {
                    flagArray[1] = 0;
                    peer.setFileAccessAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1: {
                    peer.setOnlineImageAccessAttribute((this._onlineImageAccess_0_0value as boolean | undefined));
                    flagArray[2] = 2;
                    break;
                }
                case 3: {
                    flagArray[2] = 2;
                    break;
                }
                default: {
                    flagArray[2] = 0;
                    peer.setOnlineImageAccessAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[3] != 0) {
            switch (flagArray[3]) {
                case 1: {
                    peer.setDomStorageAccessAttribute((this._domStorageAccess_0_0value as boolean | undefined));
                    flagArray[3] = 2;
                    break;
                }
                case 3: {
                    flagArray[3] = 2;
                    break;
                }
                default: {
                    flagArray[3] = 0;
                    peer.setDomStorageAccessAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[4] != 0) {
            switch (flagArray[4]) {
                case 1: {
                    peer.setImageAccessAttribute((this._imageAccess_0_0value as boolean | undefined));
                    flagArray[4] = 2;
                    break;
                }
                case 3: {
                    flagArray[4] = 2;
                    break;
                }
                default: {
                    flagArray[4] = 0;
                    peer.setImageAccessAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[5] != 0) {
            switch (flagArray[5]) {
                case 1: {
                    peer.setMixedModeAttribute((this._mixedMode_0_0value as MixedMode | undefined));
                    flagArray[5] = 2;
                    break;
                }
                case 3: {
                    flagArray[5] = 2;
                    break;
                }
                default: {
                    flagArray[5] = 0;
                    peer.setMixedModeAttribute((undefined as MixedMode | undefined));
                }
            }
        }
        if (flagArray[6] != 0) {
            switch (flagArray[6]) {
                case 1: {
                    peer.setZoomAccessAttribute((this._zoomAccess_0_0value as boolean | undefined));
                    flagArray[6] = 2;
                    break;
                }
                case 3: {
                    flagArray[6] = 2;
                    break;
                }
                default: {
                    flagArray[6] = 0;
                    peer.setZoomAccessAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[7] != 0) {
            switch (flagArray[7]) {
                case 1: {
                    peer.setGeolocationAccessAttribute((this._geolocationAccess_0_0value as boolean | undefined));
                    flagArray[7] = 2;
                    break;
                }
                case 3: {
                    flagArray[7] = 2;
                    break;
                }
                default: {
                    flagArray[7] = 0;
                    peer.setGeolocationAccessAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[8] != 0) {
            switch (flagArray[8]) {
                case 1: {
                    hookJavaScriptProxy(peer, (this._javaScriptProxy_0_0value as JavaScriptProxy | undefined));
                    flagArray[8] = 2;
                    break;
                }
                case 3: {
                    flagArray[8] = 2;
                    break;
                }
                default: {
                    flagArray[8] = 0;
                    hookJavaScriptProxy(peer, (undefined as JavaScriptProxy | undefined));
                }
            }
        }
        if (flagArray[9] != 0) {
            switch (flagArray[9]) {
                case 1: {
                    peer.setCacheModeAttribute((this._cacheMode_0_0value as CacheMode | undefined));
                    flagArray[9] = 2;
                    break;
                }
                case 3: {
                    flagArray[9] = 2;
                    break;
                }
                default: {
                    flagArray[9] = 0;
                    peer.setCacheModeAttribute((undefined as CacheMode | undefined));
                }
            }
        }
        if (flagArray[10] != 0) {
            switch (flagArray[10]) {
                case 1: {
                    peer.setDarkModeAttribute((this._darkMode_0_0value as WebDarkMode | undefined));
                    flagArray[10] = 2;
                    break;
                }
                case 3: {
                    flagArray[10] = 2;
                    break;
                }
                default: {
                    flagArray[10] = 0;
                    peer.setDarkModeAttribute((undefined as WebDarkMode | undefined));
                }
            }
        }
        if (flagArray[11] != 0) {
            switch (flagArray[11]) {
                case 1: {
                    peer.setForceDarkAccessAttribute((this._forceDarkAccess_0_0value as boolean | undefined));
                    flagArray[11] = 2;
                    break;
                }
                case 3: {
                    flagArray[11] = 2;
                    break;
                }
                default: {
                    flagArray[11] = 0;
                    peer.setForceDarkAccessAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[12] != 0) {
            switch (flagArray[12]) {
                case 1: {
                    peer.setMediaOptionsAttribute((this._mediaOptions_0_0value as WebMediaOptions | undefined));
                    flagArray[12] = 2;
                    break;
                }
                case 3: {
                    flagArray[12] = 2;
                    break;
                }
                default: {
                    flagArray[12] = 0;
                    peer.setMediaOptionsAttribute((undefined as WebMediaOptions | undefined));
                }
            }
        }
        if (flagArray[13] != 0) {
            switch (flagArray[13]) {
                case 1: {
                    peer.setOverviewModeAccessAttribute((this._overviewModeAccess_0_0value as boolean | undefined));
                    flagArray[13] = 2;
                    break;
                }
                case 3: {
                    flagArray[13] = 2;
                    break;
                }
                default: {
                    flagArray[13] = 0;
                    peer.setOverviewModeAccessAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[14] != 0) {
            switch (flagArray[14]) {
                case 1: {
                    peer.setOverScrollModeAttribute((this._overScrollMode_0_0value as OverScrollMode | undefined));
                    flagArray[14] = 2;
                    break;
                }
                case 3: {
                    flagArray[14] = 2;
                    break;
                }
                default: {
                    flagArray[14] = 0;
                    peer.setOverScrollModeAttribute((undefined as OverScrollMode | undefined));
                }
            }
        }
        if (flagArray[15] != 0) {
            switch (flagArray[15]) {
                case 1: {
                    peer.setBlurOnKeyboardHideModeAttribute((this._blurOnKeyboardHideMode_0_0value as BlurOnKeyboardHideMode | undefined));
                    flagArray[15] = 2;
                    break;
                }
                case 3: {
                    flagArray[15] = 2;
                    break;
                }
                default: {
                    flagArray[15] = 0;
                    peer.setBlurOnKeyboardHideModeAttribute((undefined as BlurOnKeyboardHideMode | undefined));
                }
            }
        }
        if (flagArray[16] != 0) {
            switch (flagArray[16]) {
                case 1: {
                    peer.setTextZoomRatioAttribute((this._textZoomRatio_0_0value as int32 | undefined));
                    flagArray[16] = 2;
                    break;
                }
                case 3: {
                    flagArray[16] = 2;
                    break;
                }
                default: {
                    flagArray[16] = 0;
                    peer.setTextZoomRatioAttribute((undefined as int32 | undefined));
                }
            }
        }
        if (flagArray[17] != 0) {
            switch (flagArray[17]) {
                case 1: {
                    peer.setDatabaseAccessAttribute((this._databaseAccess_0_0value as boolean | undefined));
                    flagArray[17] = 2;
                    break;
                }
                case 3: {
                    flagArray[17] = 2;
                    break;
                }
                default: {
                    flagArray[17] = 0;
                    peer.setDatabaseAccessAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[18] != 0) {
            switch (flagArray[18]) {
                case 1: {
                    peer.setInitialScaleAttribute((this._initialScale_0_0value as double | undefined));
                    flagArray[18] = 2;
                    break;
                }
                case 3: {
                    flagArray[18] = 2;
                    break;
                }
                default: {
                    flagArray[18] = 0;
                    peer.setInitialScaleAttribute((undefined as double | undefined));
                }
            }
        }
        if (flagArray[19] != 0) {
            switch (flagArray[19]) {
                case 1: {
                    peer.setMetaViewportAttribute((this._metaViewport_0_0value as boolean | undefined));
                    flagArray[19] = 2;
                    break;
                }
                case 3: {
                    flagArray[19] = 2;
                    break;
                }
                default: {
                    flagArray[19] = 0;
                    peer.setMetaViewportAttribute((undefined as boolean | undefined));
                }
            }
        }
    }
    applyModifierPatch1(peer: ArkWebPeer, flagArray: Uint8Array): void {
        if (flagArray[20] != 0) {
            switch (flagArray[20]) {
                case 1: {
                    peer.setOnPageBeginAttribute((this._onPageBegin_0_0value as arkui_component_common_Callback<OnPageBeginEvent, void> | undefined));
                    flagArray[20] = 2;
                    break;
                }
                case 3: {
                    flagArray[20] = 2;
                    break;
                }
                default: {
                    flagArray[20] = 0;
                    peer.setOnPageBeginAttribute((undefined as arkui_component_common_Callback<OnPageBeginEvent, void> | undefined));
                }
            }
        }
        if (flagArray[21] != 0) {
            switch (flagArray[21]) {
                case 1: {
                    peer.setOnPageEndAttribute((this._onPageEnd_0_0value as arkui_component_common_Callback<OnPageEndEvent, void> | undefined));
                    flagArray[21] = 2;
                    break;
                }
                case 3: {
                    flagArray[21] = 2;
                    break;
                }
                default: {
                    flagArray[21] = 0;
                    peer.setOnPageEndAttribute((undefined as arkui_component_common_Callback<OnPageEndEvent, void> | undefined));
                }
            }
        }
        if (flagArray[22] != 0) {
            switch (flagArray[22]) {
                case 1: {
                    peer.setOnLoadStartedAttribute((this._onLoadStarted_0_0value as arkui_component_common_Callback<OnLoadStartedEvent, void> | undefined));
                    flagArray[22] = 2;
                    break;
                }
                case 3: {
                    flagArray[22] = 2;
                    break;
                }
                default: {
                    flagArray[22] = 0;
                    peer.setOnLoadStartedAttribute((undefined as arkui_component_common_Callback<OnLoadStartedEvent, void> | undefined));
                }
            }
        }
        if (flagArray[23] != 0) {
            switch (flagArray[23]) {
                case 1: {
                    peer.setOnLoadFinishedAttribute((this._onLoadFinished_0_0value as arkui_component_common_Callback<OnLoadFinishedEvent, void> | undefined));
                    flagArray[23] = 2;
                    break;
                }
                case 3: {
                    flagArray[23] = 2;
                    break;
                }
                default: {
                    flagArray[23] = 0;
                    peer.setOnLoadFinishedAttribute((undefined as arkui_component_common_Callback<OnLoadFinishedEvent, void> | undefined));
                }
            }
        }
        if (flagArray[24] != 0) {
            switch (flagArray[24]) {
                case 1: {
                    peer.setOnProgressChangeAttribute((this._onProgressChange_0_0value as arkui_component_common_Callback<OnProgressChangeEvent, void> | undefined));
                    flagArray[24] = 2;
                    break;
                }
                case 3: {
                    flagArray[24] = 2;
                    break;
                }
                default: {
                    flagArray[24] = 0;
                    peer.setOnProgressChangeAttribute((undefined as arkui_component_common_Callback<OnProgressChangeEvent, void> | undefined));
                }
            }
        }
        if (flagArray[25] != 0) {
            switch (flagArray[25]) {
                case 1: {
                    peer.setOnTitleReceiveAttribute((this._onTitleReceive_0_0value as arkui_component_common_Callback<OnTitleReceiveEvent, void> | undefined));
                    flagArray[25] = 2;
                    break;
                }
                case 3: {
                    flagArray[25] = 2;
                    break;
                }
                default: {
                    flagArray[25] = 0;
                    peer.setOnTitleReceiveAttribute((undefined as arkui_component_common_Callback<OnTitleReceiveEvent, void> | undefined));
                }
            }
        }
        if (flagArray[26] != 0) {
            switch (flagArray[26]) {
                case 1: {
                    peer.setOnGeolocationHideAttribute((this._onGeolocationHide_0_0value as (() => void) | undefined));
                    flagArray[26] = 2;
                    break;
                }
                case 3: {
                    flagArray[26] = 2;
                    break;
                }
                default: {
                    flagArray[26] = 0;
                    peer.setOnGeolocationHideAttribute((undefined as (() => void) | undefined));
                }
            }
        }
        if (flagArray[27] != 0) {
            switch (flagArray[27]) {
                case 1: {
                    peer.setOnGeolocationShowAttribute((this._onGeolocationShow_0_0value as arkui_component_common_Callback<OnGeolocationShowEvent, void> | undefined));
                    flagArray[27] = 2;
                    break;
                }
                case 3: {
                    flagArray[27] = 2;
                    break;
                }
                default: {
                    flagArray[27] = 0;
                    peer.setOnGeolocationShowAttribute((undefined as arkui_component_common_Callback<OnGeolocationShowEvent, void> | undefined));
                }
            }
        }
        if (flagArray[28] != 0) {
            switch (flagArray[28]) {
                case 1: {
                    peer.setOnRequestSelectedAttribute((this._onRequestSelected_0_0value as (() => void) | undefined));
                    flagArray[28] = 2;
                    break;
                }
                case 3: {
                    flagArray[28] = 2;
                    break;
                }
                default: {
                    flagArray[28] = 0;
                    peer.setOnRequestSelectedAttribute((undefined as (() => void) | undefined));
                }
            }
        }
        if (flagArray[29] != 0) {
            switch (flagArray[29]) {
                case 1: {
                    peer.setOnAlertAttribute((this._onAlert_0_0value as arkui_component_common_Callback<OnAlertEvent, boolean> | undefined));
                    flagArray[29] = 2;
                    break;
                }
                case 3: {
                    flagArray[29] = 2;
                    break;
                }
                default: {
                    flagArray[29] = 0;
                    peer.setOnAlertAttribute((undefined as arkui_component_common_Callback<OnAlertEvent, boolean> | undefined));
                }
            }
        }
        if (flagArray[30] != 0) {
            switch (flagArray[30]) {
                case 1: {
                    peer.setOnBeforeUnloadAttribute((this._onBeforeUnload_0_0value as arkui_component_common_Callback<OnBeforeUnloadEvent, boolean> | undefined));
                    flagArray[30] = 2;
                    break;
                }
                case 3: {
                    flagArray[30] = 2;
                    break;
                }
                default: {
                    flagArray[30] = 0;
                    peer.setOnBeforeUnloadAttribute((undefined as arkui_component_common_Callback<OnBeforeUnloadEvent, boolean> | undefined));
                }
            }
        }
        if (flagArray[31] != 0) {
            switch (flagArray[31]) {
                case 1: {
                    peer.setOnConfirmAttribute((this._onConfirm_0_0value as arkui_component_common_Callback<OnConfirmEvent, boolean> | undefined));
                    flagArray[31] = 2;
                    break;
                }
                case 3: {
                    flagArray[31] = 2;
                    break;
                }
                default: {
                    flagArray[31] = 0;
                    peer.setOnConfirmAttribute((undefined as arkui_component_common_Callback<OnConfirmEvent, boolean> | undefined));
                }
            }
        }
        if (flagArray[32] != 0) {
            switch (flagArray[32]) {
                case 1: {
                    peer.setOnPromptAttribute((this._onPrompt_0_0value as arkui_component_common_Callback<OnPromptEvent, boolean> | undefined));
                    flagArray[32] = 2;
                    break;
                }
                case 3: {
                    flagArray[32] = 2;
                    break;
                }
                default: {
                    flagArray[32] = 0;
                    peer.setOnPromptAttribute((undefined as arkui_component_common_Callback<OnPromptEvent, boolean> | undefined));
                }
            }
        }
        if (flagArray[33] != 0) {
            switch (flagArray[33]) {
                case 1: {
                    peer.setOnConsoleAttribute((this._onConsole_0_0value as arkui_component_common_Callback<OnConsoleEvent, boolean> | undefined));
                    flagArray[33] = 2;
                    break;
                }
                case 3: {
                    flagArray[33] = 2;
                    break;
                }
                default: {
                    flagArray[33] = 0;
                    peer.setOnConsoleAttribute((undefined as arkui_component_common_Callback<OnConsoleEvent, boolean> | undefined));
                }
            }
        }
        if (flagArray[34] != 0) {
            switch (flagArray[34]) {
                case 1: {
                    peer.setOnErrorReceiveAttribute((this._onErrorReceive_0_0value as arkui_component_common_Callback<OnErrorReceiveEvent, void> | undefined));
                    flagArray[34] = 2;
                    break;
                }
                case 3: {
                    flagArray[34] = 2;
                    break;
                }
                default: {
                    flagArray[34] = 0;
                    peer.setOnErrorReceiveAttribute((undefined as arkui_component_common_Callback<OnErrorReceiveEvent, void> | undefined));
                }
            }
        }
        if (flagArray[35] != 0) {
            switch (flagArray[35]) {
                case 1: {
                    peer.setOnHttpErrorReceiveAttribute((this._onHttpErrorReceive_0_0value as arkui_component_common_Callback<OnHttpErrorReceiveEvent, void> | undefined));
                    flagArray[35] = 2;
                    break;
                }
                case 3: {
                    flagArray[35] = 2;
                    break;
                }
                default: {
                    flagArray[35] = 0;
                    peer.setOnHttpErrorReceiveAttribute((undefined as arkui_component_common_Callback<OnHttpErrorReceiveEvent, void> | undefined));
                }
            }
        }
        if (flagArray[36] != 0) {
            switch (flagArray[36]) {
                case 1: {
                    peer.setOnDownloadStartAttribute((this._onDownloadStart_0_0value as arkui_component_common_Callback<OnDownloadStartEvent, void> | undefined));
                    flagArray[36] = 2;
                    break;
                }
                case 3: {
                    flagArray[36] = 2;
                    break;
                }
                default: {
                    flagArray[36] = 0;
                    peer.setOnDownloadStartAttribute((undefined as arkui_component_common_Callback<OnDownloadStartEvent, void> | undefined));
                }
            }
        }
        if (flagArray[37] != 0) {
            switch (flagArray[37]) {
                case 1: {
                    peer.setOnRefreshAccessedHistoryAttribute((this._onRefreshAccessedHistory_0_0value as arkui_component_common_Callback<OnRefreshAccessedHistoryEvent, void> | undefined));
                    flagArray[37] = 2;
                    break;
                }
                case 3: {
                    flagArray[37] = 2;
                    break;
                }
                default: {
                    flagArray[37] = 0;
                    peer.setOnRefreshAccessedHistoryAttribute((undefined as arkui_component_common_Callback<OnRefreshAccessedHistoryEvent, void> | undefined));
                }
            }
        }
        if (flagArray[38] != 0) {
            switch (flagArray[38]) {
                case 1: {
                    peer.setOnRenderExitedAttribute((this._onRenderExited_0_0value as arkui_component_common_Callback<OnRenderExitedEvent, void> | undefined));
                    flagArray[38] = 2;
                    break;
                }
                case 3: {
                    flagArray[38] = 2;
                    break;
                }
                default: {
                    flagArray[38] = 0;
                    peer.setOnRenderExitedAttribute((undefined as arkui_component_common_Callback<OnRenderExitedEvent, void> | undefined));
                }
            }
        }
        if (flagArray[39] != 0) {
            switch (flagArray[39]) {
                case 1: {
                    peer.setOnShowFileSelectorAttribute((this._onShowFileSelector_0_0value as arkui_component_common_Callback<OnShowFileSelectorEvent, boolean> | undefined));
                    flagArray[39] = 2;
                    break;
                }
                case 3: {
                    flagArray[39] = 2;
                    break;
                }
                default: {
                    flagArray[39] = 0;
                    peer.setOnShowFileSelectorAttribute((undefined as arkui_component_common_Callback<OnShowFileSelectorEvent, boolean> | undefined));
                }
            }
        }
    }
    applyModifierPatch2(peer: ArkWebPeer, flagArray: Uint8Array): void {
        if (flagArray[40] != 0) {
            switch (flagArray[40]) {
                case 1: {
                    peer.setOnResourceLoadAttribute((this._onResourceLoad_0_0value as arkui_component_common_Callback<OnResourceLoadEvent, void> | undefined));
                    flagArray[40] = 2;
                    break;
                }
                case 3: {
                    flagArray[40] = 2;
                    break;
                }
                default: {
                    flagArray[40] = 0;
                    peer.setOnResourceLoadAttribute((undefined as arkui_component_common_Callback<OnResourceLoadEvent, void> | undefined));
                }
            }
        }
        if (flagArray[41] != 0) {
            switch (flagArray[41]) {
                case 1: {
                    peer.setOnFullScreenExitAttribute((this._onFullScreenExit_0_0value as (() => void) | undefined));
                    flagArray[41] = 2;
                    break;
                }
                case 3: {
                    flagArray[41] = 2;
                    break;
                }
                default: {
                    flagArray[41] = 0;
                    peer.setOnFullScreenExitAttribute((undefined as (() => void) | undefined));
                }
            }
        }
        if (flagArray[42] != 0) {
            switch (flagArray[42]) {
                case 1: {
                    peer.setOnFullScreenEnterAttribute((this._onFullScreenEnter_0_0value as OnFullScreenEnterCallback | undefined));
                    flagArray[42] = 2;
                    break;
                }
                case 3: {
                    flagArray[42] = 2;
                    break;
                }
                default: {
                    flagArray[42] = 0;
                    peer.setOnFullScreenEnterAttribute((undefined as OnFullScreenEnterCallback | undefined));
                }
            }
        }
        if (flagArray[43] != 0) {
            switch (flagArray[43]) {
                case 1: {
                    peer.setOnScaleChangeAttribute((this._onScaleChange_0_0value as arkui_component_common_Callback<OnScaleChangeEvent, void> | undefined));
                    flagArray[43] = 2;
                    break;
                }
                case 3: {
                    flagArray[43] = 2;
                    break;
                }
                default: {
                    flagArray[43] = 0;
                    peer.setOnScaleChangeAttribute((undefined as arkui_component_common_Callback<OnScaleChangeEvent, void> | undefined));
                }
            }
        }
        if (flagArray[44] != 0) {
            switch (flagArray[44]) {
                case 1: {
                    peer.setOnHttpAuthRequestAttribute((this._onHttpAuthRequest_0_0value as arkui_component_common_Callback<OnHttpAuthRequestEvent, boolean> | undefined));
                    flagArray[44] = 2;
                    break;
                }
                case 3: {
                    flagArray[44] = 2;
                    break;
                }
                default: {
                    flagArray[44] = 0;
                    peer.setOnHttpAuthRequestAttribute((undefined as arkui_component_common_Callback<OnHttpAuthRequestEvent, boolean> | undefined));
                }
            }
        }
        if (flagArray[45] != 0) {
            switch (flagArray[45]) {
                case 1: {
                    peer.setOnInterceptRequestAttribute((this._onInterceptRequest_0_0value as arkui_component_common_Callback<OnInterceptRequestEvent, WebResourceResponse | null> | undefined));
                    flagArray[45] = 2;
                    break;
                }
                case 3: {
                    flagArray[45] = 2;
                    break;
                }
                default: {
                    flagArray[45] = 0;
                    peer.setOnInterceptRequestAttribute((undefined as arkui_component_common_Callback<OnInterceptRequestEvent, WebResourceResponse | null> | undefined));
                }
            }
        }
        if (flagArray[46] != 0) {
            switch (flagArray[46]) {
                case 1: {
                    peer.setOnPermissionRequestAttribute((this._onPermissionRequest_0_0value as arkui_component_common_Callback<OnPermissionRequestEvent, void> | undefined));
                    flagArray[46] = 2;
                    break;
                }
                case 3: {
                    flagArray[46] = 2;
                    break;
                }
                default: {
                    flagArray[46] = 0;
                    peer.setOnPermissionRequestAttribute((undefined as arkui_component_common_Callback<OnPermissionRequestEvent, void> | undefined));
                }
            }
        }
        if (flagArray[47] != 0) {
            switch (flagArray[47]) {
                case 1: {
                    peer.setOnScreenCaptureRequestAttribute((this._onScreenCaptureRequest_0_0value as arkui_component_common_Callback<OnScreenCaptureRequestEvent, void> | undefined));
                    flagArray[47] = 2;
                    break;
                }
                case 3: {
                    flagArray[47] = 2;
                    break;
                }
                default: {
                    flagArray[47] = 0;
                    peer.setOnScreenCaptureRequestAttribute((undefined as arkui_component_common_Callback<OnScreenCaptureRequestEvent, void> | undefined));
                }
            }
        }
        if (flagArray[48] != 0) {
            switch (flagArray[48]) {
                case 1: {
                    peer.setOnContextMenuShowAttribute((this._onContextMenuShow_0_0value as arkui_component_common_Callback<OnContextMenuShowEvent, boolean> | undefined));
                    flagArray[48] = 2;
                    break;
                }
                case 3: {
                    flagArray[48] = 2;
                    break;
                }
                default: {
                    flagArray[48] = 0;
                    peer.setOnContextMenuShowAttribute((undefined as arkui_component_common_Callback<OnContextMenuShowEvent, boolean> | undefined));
                }
            }
        }
        if (flagArray[49] != 0) {
            switch (flagArray[49]) {
                case 1: {
                    peer.setOnContextMenuHideAttribute((this._onContextMenuHide_0_0value as OnContextMenuHideCallback | undefined));
                    flagArray[49] = 2;
                    break;
                }
                case 3: {
                    flagArray[49] = 2;
                    break;
                }
                default: {
                    flagArray[49] = 0;
                    peer.setOnContextMenuHideAttribute((undefined as OnContextMenuHideCallback | undefined));
                }
            }
        }
        if (flagArray[50] != 0) {
            switch (flagArray[50]) {
                case 1: {
                    peer.setMediaPlayGestureAccessAttribute((this._mediaPlayGestureAccess_0_0value as boolean | undefined));
                    flagArray[50] = 2;
                    break;
                }
                case 3: {
                    flagArray[50] = 2;
                    break;
                }
                default: {
                    flagArray[50] = 0;
                    peer.setMediaPlayGestureAccessAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[51] != 0) {
            switch (flagArray[51]) {
                case 1: {
                    peer.setOnSearchResultReceiveAttribute((this._onSearchResultReceive_0_0value as arkui_component_common_Callback<OnSearchResultReceiveEvent, void> | undefined));
                    flagArray[51] = 2;
                    break;
                }
                case 3: {
                    flagArray[51] = 2;
                    break;
                }
                default: {
                    flagArray[51] = 0;
                    peer.setOnSearchResultReceiveAttribute((undefined as arkui_component_common_Callback<OnSearchResultReceiveEvent, void> | undefined));
                }
            }
        }
        if (flagArray[52] != 0) {
            switch (flagArray[52]) {
                case 1: {
                    peer.setOnScrollAttribute((this._onScroll_0_0value as arkui_component_common_Callback<OnScrollEvent, void> | undefined));
                    flagArray[52] = 2;
                    break;
                }
                case 3: {
                    flagArray[52] = 2;
                    break;
                }
                default: {
                    flagArray[52] = 0;
                    peer.setOnScrollAttribute((undefined as arkui_component_common_Callback<OnScrollEvent, void> | undefined));
                }
            }
        }
        if (flagArray[53] != 0) {
            switch (flagArray[53]) {
                case 1: {
                    peer.setOnSslErrorEventReceiveAttribute((this._onSslErrorEventReceive_0_0value as arkui_component_common_Callback<OnSslErrorEventReceiveEvent, void> | undefined));
                    flagArray[53] = 2;
                    break;
                }
                case 3: {
                    flagArray[53] = 2;
                    break;
                }
                default: {
                    flagArray[53] = 0;
                    peer.setOnSslErrorEventReceiveAttribute((undefined as arkui_component_common_Callback<OnSslErrorEventReceiveEvent, void> | undefined));
                }
            }
        }
        if (flagArray[54] != 0) {
            switch (flagArray[54]) {
                case 1: {
                    peer.setOnSslErrorEventAttribute((this._onSslErrorEvent_0_0value as OnSslErrorEventCallback | undefined));
                    flagArray[54] = 2;
                    break;
                }
                case 3: {
                    flagArray[54] = 2;
                    break;
                }
                default: {
                    flagArray[54] = 0;
                    peer.setOnSslErrorEventAttribute((undefined as OnSslErrorEventCallback | undefined));
                }
            }
        }
        if (flagArray[55] != 0) {
            switch (flagArray[55]) {
                case 1: {
                    peer.setOnClientAuthenticationRequestAttribute((this._onClientAuthenticationRequest_0_0value as arkui_component_common_Callback<OnClientAuthenticationEvent, void> | undefined));
                    flagArray[55] = 2;
                    break;
                }
                case 3: {
                    flagArray[55] = 2;
                    break;
                }
                default: {
                    flagArray[55] = 0;
                    peer.setOnClientAuthenticationRequestAttribute((undefined as arkui_component_common_Callback<OnClientAuthenticationEvent, void> | undefined));
                }
            }
        }
        if (flagArray[56] != 0) {
            switch (flagArray[56]) {
                case 1: {
                    peer.setOnWindowNewAttribute((this._onWindowNew_0_0value as arkui_component_common_Callback<OnWindowNewEvent, void> | undefined));
                    flagArray[56] = 2;
                    break;
                }
                case 3: {
                    flagArray[56] = 2;
                    break;
                }
                default: {
                    flagArray[56] = 0;
                    peer.setOnWindowNewAttribute((undefined as arkui_component_common_Callback<OnWindowNewEvent, void> | undefined));
                }
            }
        }
        if (flagArray[57] != 0) {
            switch (flagArray[57]) {
                case 1: {
                    peer.setOnWindowExitAttribute((this._onWindowExit_0_0value as (() => void) | undefined));
                    flagArray[57] = 2;
                    break;
                }
                case 3: {
                    flagArray[57] = 2;
                    break;
                }
                default: {
                    flagArray[57] = 0;
                    peer.setOnWindowExitAttribute((undefined as (() => void) | undefined));
                }
            }
        }
        if (flagArray[58] != 0) {
            switch (flagArray[58]) {
                case 1: {
                    peer.setMultiWindowAccessAttribute((this._multiWindowAccess_0_0value as boolean | undefined));
                    flagArray[58] = 2;
                    break;
                }
                case 3: {
                    flagArray[58] = 2;
                    break;
                }
                default: {
                    flagArray[58] = 0;
                    peer.setMultiWindowAccessAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[59] != 0) {
            switch (flagArray[59]) {
                case 1: {
                    peer.setOnInterceptKeyEventAttribute((this._onInterceptKeyEvent_0_0value as ((event: KeyEvent) => boolean) | undefined));
                    flagArray[59] = 2;
                    break;
                }
                case 3: {
                    flagArray[59] = 2;
                    break;
                }
                default: {
                    flagArray[59] = 0;
                    peer.setOnInterceptKeyEventAttribute((undefined as ((event: KeyEvent) => boolean) | undefined));
                }
            }
        }
    }
    applyModifierPatch3(peer: ArkWebPeer, flagArray: Uint8Array): void {
        if (flagArray[60] != 0) {
            switch (flagArray[60]) {
                case 1: {
                    peer.setWebStandardFontAttribute((this._webStandardFont_0_0value as string | undefined));
                    flagArray[60] = 2;
                    break;
                }
                case 3: {
                    flagArray[60] = 2;
                    break;
                }
                default: {
                    flagArray[60] = 0;
                    peer.setWebStandardFontAttribute((undefined as string | undefined));
                }
            }
        }
        if (flagArray[61] != 0) {
            switch (flagArray[61]) {
                case 1: {
                    peer.setWebSerifFontAttribute((this._webSerifFont_0_0value as string | undefined));
                    flagArray[61] = 2;
                    break;
                }
                case 3: {
                    flagArray[61] = 2;
                    break;
                }
                default: {
                    flagArray[61] = 0;
                    peer.setWebSerifFontAttribute((undefined as string | undefined));
                }
            }
        }
        if (flagArray[62] != 0) {
            switch (flagArray[62]) {
                case 1: {
                    peer.setWebSansSerifFontAttribute((this._webSansSerifFont_0_0value as string | undefined));
                    flagArray[62] = 2;
                    break;
                }
                case 3: {
                    flagArray[62] = 2;
                    break;
                }
                default: {
                    flagArray[62] = 0;
                    peer.setWebSansSerifFontAttribute((undefined as string | undefined));
                }
            }
        }
        if (flagArray[63] != 0) {
            switch (flagArray[63]) {
                case 1: {
                    peer.setWebFixedFontAttribute((this._webFixedFont_0_0value as string | undefined));
                    flagArray[63] = 2;
                    break;
                }
                case 3: {
                    flagArray[63] = 2;
                    break;
                }
                default: {
                    flagArray[63] = 0;
                    peer.setWebFixedFontAttribute((undefined as string | undefined));
                }
            }
        }
        if (flagArray[64] != 0) {
            switch (flagArray[64]) {
                case 1: {
                    peer.setWebFantasyFontAttribute((this._webFantasyFont_0_0value as string | undefined));
                    flagArray[64] = 2;
                    break;
                }
                case 3: {
                    flagArray[64] = 2;
                    break;
                }
                default: {
                    flagArray[64] = 0;
                    peer.setWebFantasyFontAttribute((undefined as string | undefined));
                }
            }
        }
        if (flagArray[65] != 0) {
            switch (flagArray[65]) {
                case 1: {
                    peer.setWebCursiveFontAttribute((this._webCursiveFont_0_0value as string | undefined));
                    flagArray[65] = 2;
                    break;
                }
                case 3: {
                    flagArray[65] = 2;
                    break;
                }
                default: {
                    flagArray[65] = 0;
                    peer.setWebCursiveFontAttribute((undefined as string | undefined));
                }
            }
        }
        if (flagArray[66] != 0) {
            switch (flagArray[66]) {
                case 1: {
                    peer.setDefaultFixedFontSizeAttribute((this._defaultFixedFontSize_0_0value as int32 | undefined));
                    flagArray[66] = 2;
                    break;
                }
                case 3: {
                    flagArray[66] = 2;
                    break;
                }
                default: {
                    flagArray[66] = 0;
                    peer.setDefaultFixedFontSizeAttribute((undefined as int32 | undefined));
                }
            }
        }
        if (flagArray[67] != 0) {
            switch (flagArray[67]) {
                case 1: {
                    peer.setDefaultFontSizeAttribute((this._defaultFontSize_0_0value as int32 | undefined));
                    flagArray[67] = 2;
                    break;
                }
                case 3: {
                    flagArray[67] = 2;
                    break;
                }
                default: {
                    flagArray[67] = 0;
                    peer.setDefaultFontSizeAttribute((undefined as int32 | undefined));
                }
            }
        }
        if (flagArray[68] != 0) {
            switch (flagArray[68]) {
                case 1: {
                    peer.setMinFontSizeAttribute((this._minFontSize_0_0value as int32 | undefined));
                    flagArray[68] = 2;
                    break;
                }
                case 3: {
                    flagArray[68] = 2;
                    break;
                }
                default: {
                    flagArray[68] = 0;
                    peer.setMinFontSizeAttribute((undefined as int32 | undefined));
                }
            }
        }
        if (flagArray[69] != 0) {
            switch (flagArray[69]) {
                case 1: {
                    peer.setMinLogicalFontSizeAttribute((this._minLogicalFontSize_0_0value as int32 | undefined));
                    flagArray[69] = 2;
                    break;
                }
                case 3: {
                    flagArray[69] = 2;
                    break;
                }
                default: {
                    flagArray[69] = 0;
                    peer.setMinLogicalFontSizeAttribute((undefined as int32 | undefined));
                }
            }
        }
        if (flagArray[70] != 0) {
            switch (flagArray[70]) {
                case 1: {
                    peer.setDefaultTextEncodingFormatAttribute((this._defaultTextEncodingFormat_0_0value as string | undefined));
                    flagArray[70] = 2;
                    break;
                }
                case 3: {
                    flagArray[70] = 2;
                    break;
                }
                default: {
                    flagArray[70] = 0;
                    peer.setDefaultTextEncodingFormatAttribute((undefined as string | undefined));
                }
            }
        }
        if (flagArray[71] != 0) {
            switch (flagArray[71]) {
                case 1: {
                    peer.setForceDisplayScrollBarAttribute((this._forceDisplayScrollBar_0_0value as boolean | undefined));
                    flagArray[71] = 2;
                    break;
                }
                case 3: {
                    flagArray[71] = 2;
                    break;
                }
                default: {
                    flagArray[71] = 0;
                    peer.setForceDisplayScrollBarAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[72] != 0) {
            switch (flagArray[72]) {
                case 1: {
                    peer.setBlockNetworkAttribute((this._blockNetwork_0_0value as boolean | undefined));
                    flagArray[72] = 2;
                    break;
                }
                case 3: {
                    flagArray[72] = 2;
                    break;
                }
                default: {
                    flagArray[72] = 0;
                    peer.setBlockNetworkAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[73] != 0) {
            switch (flagArray[73]) {
                case 1: {
                    peer.setHorizontalScrollBarAccessAttribute((this._horizontalScrollBarAccess_0_0value as boolean | undefined));
                    flagArray[73] = 2;
                    break;
                }
                case 3: {
                    flagArray[73] = 2;
                    break;
                }
                default: {
                    flagArray[73] = 0;
                    peer.setHorizontalScrollBarAccessAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[74] != 0) {
            switch (flagArray[74]) {
                case 1: {
                    peer.setVerticalScrollBarAccessAttribute((this._verticalScrollBarAccess_0_0value as boolean | undefined));
                    flagArray[74] = 2;
                    break;
                }
                case 3: {
                    flagArray[74] = 2;
                    break;
                }
                default: {
                    flagArray[74] = 0;
                    peer.setVerticalScrollBarAccessAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[75] != 0) {
            switch (flagArray[75]) {
                case 1: {
                    peer.setOnTouchIconUrlReceivedAttribute((this._onTouchIconUrlReceived_0_0value as arkui_component_common_Callback<OnTouchIconUrlReceivedEvent, void> | undefined));
                    flagArray[75] = 2;
                    break;
                }
                case 3: {
                    flagArray[75] = 2;
                    break;
                }
                default: {
                    flagArray[75] = 0;
                    peer.setOnTouchIconUrlReceivedAttribute((undefined as arkui_component_common_Callback<OnTouchIconUrlReceivedEvent, void> | undefined));
                }
            }
        }
        if (flagArray[76] != 0) {
            switch (flagArray[76]) {
                case 1: {
                    peer.setOnFaviconReceivedAttribute((this._onFaviconReceived_0_0value as arkui_component_common_Callback<OnFaviconReceivedEvent, void> | undefined));
                    flagArray[76] = 2;
                    break;
                }
                case 3: {
                    flagArray[76] = 2;
                    break;
                }
                default: {
                    flagArray[76] = 0;
                    peer.setOnFaviconReceivedAttribute((undefined as arkui_component_common_Callback<OnFaviconReceivedEvent, void> | undefined));
                }
            }
        }
        if (flagArray[77] != 0) {
            switch (flagArray[77]) {
                case 1: {
                    peer.setOnPageVisibleAttribute((this._onPageVisible_0_0value as arkui_component_common_Callback<OnPageVisibleEvent, void> | undefined));
                    flagArray[77] = 2;
                    break;
                }
                case 3: {
                    flagArray[77] = 2;
                    break;
                }
                default: {
                    flagArray[77] = 0;
                    peer.setOnPageVisibleAttribute((undefined as arkui_component_common_Callback<OnPageVisibleEvent, void> | undefined));
                }
            }
        }
        if (flagArray[78] != 0) {
            switch (flagArray[78]) {
                case 1: {
                    peer.setOnDataResubmittedAttribute((this._onDataResubmitted_0_0value as arkui_component_common_Callback<OnDataResubmittedEvent, void> | undefined));
                    flagArray[78] = 2;
                    break;
                }
                case 3: {
                    flagArray[78] = 2;
                    break;
                }
                default: {
                    flagArray[78] = 0;
                    peer.setOnDataResubmittedAttribute((undefined as arkui_component_common_Callback<OnDataResubmittedEvent, void> | undefined));
                }
            }
        }
        if (flagArray[79] != 0) {
            switch (flagArray[79]) {
                case 1: {
                    peer.setPinchSmoothAttribute((this._pinchSmooth_0_0value as boolean | undefined));
                    flagArray[79] = 2;
                    break;
                }
                case 3: {
                    flagArray[79] = 2;
                    break;
                }
                default: {
                    flagArray[79] = 0;
                    peer.setPinchSmoothAttribute((undefined as boolean | undefined));
                }
            }
        }
    }
    applyModifierPatch4(peer: ArkWebPeer, flagArray: Uint8Array): void {
        if (flagArray[80] != 0) {
            switch (flagArray[80]) {
                case 1: {
                    peer.setAllowWindowOpenMethodAttribute((this._allowWindowOpenMethod_0_0value as boolean | undefined));
                    flagArray[80] = 2;
                    break;
                }
                case 3: {
                    flagArray[80] = 2;
                    break;
                }
                default: {
                    flagArray[80] = 0;
                    peer.setAllowWindowOpenMethodAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[81] != 0) {
            switch (flagArray[81]) {
                case 1: {
                    peer.setOnAudioStateChangedAttribute((this._onAudioStateChanged_0_0value as arkui_component_common_Callback<OnAudioStateChangedEvent, void> | undefined));
                    flagArray[81] = 2;
                    break;
                }
                case 3: {
                    flagArray[81] = 2;
                    break;
                }
                default: {
                    flagArray[81] = 0;
                    peer.setOnAudioStateChangedAttribute((undefined as arkui_component_common_Callback<OnAudioStateChangedEvent, void> | undefined));
                }
            }
        }
        if (flagArray[82] != 0) {
            switch (flagArray[82]) {
                case 1: {
                    peer.setOnFirstContentfulPaintAttribute((this._onFirstContentfulPaint_0_0value as arkui_component_common_Callback<OnFirstContentfulPaintEvent, void> | undefined));
                    flagArray[82] = 2;
                    break;
                }
                case 3: {
                    flagArray[82] = 2;
                    break;
                }
                default: {
                    flagArray[82] = 0;
                    peer.setOnFirstContentfulPaintAttribute((undefined as arkui_component_common_Callback<OnFirstContentfulPaintEvent, void> | undefined));
                }
            }
        }
        if (flagArray[83] != 0) {
            switch (flagArray[83]) {
                case 1: {
                    peer.setOnFirstMeaningfulPaintAttribute((this._onFirstMeaningfulPaint_0_0value as OnFirstMeaningfulPaintCallback | undefined));
                    flagArray[83] = 2;
                    break;
                }
                case 3: {
                    flagArray[83] = 2;
                    break;
                }
                default: {
                    flagArray[83] = 0;
                    peer.setOnFirstMeaningfulPaintAttribute((undefined as OnFirstMeaningfulPaintCallback | undefined));
                }
            }
        }
        if (flagArray[84] != 0) {
            switch (flagArray[84]) {
                case 1: {
                    peer.setOnLargestContentfulPaintAttribute((this._onLargestContentfulPaint_0_0value as OnLargestContentfulPaintCallback | undefined));
                    flagArray[84] = 2;
                    break;
                }
                case 3: {
                    flagArray[84] = 2;
                    break;
                }
                default: {
                    flagArray[84] = 0;
                    peer.setOnLargestContentfulPaintAttribute((undefined as OnLargestContentfulPaintCallback | undefined));
                }
            }
        }
        if (flagArray[85] != 0) {
            switch (flagArray[85]) {
                case 1: {
                    peer.setOnLoadInterceptAttribute((this._onLoadIntercept_0_0value as arkui_component_common_Callback<OnLoadInterceptEvent, boolean> | undefined));
                    flagArray[85] = 2;
                    break;
                }
                case 3: {
                    flagArray[85] = 2;
                    break;
                }
                default: {
                    flagArray[85] = 0;
                    peer.setOnLoadInterceptAttribute((undefined as arkui_component_common_Callback<OnLoadInterceptEvent, boolean> | undefined));
                }
            }
        }
        if (flagArray[86] != 0) {
            switch (flagArray[86]) {
                case 1: {
                    peer.setOnControllerAttachedAttribute((this._onControllerAttached_0_0value as (() => void) | undefined));
                    flagArray[86] = 2;
                    break;
                }
                case 3: {
                    flagArray[86] = 2;
                    break;
                }
                default: {
                    flagArray[86] = 0;
                    peer.setOnControllerAttachedAttribute((undefined as (() => void) | undefined));
                }
            }
        }
        if (flagArray[87] != 0) {
            switch (flagArray[87]) {
                case 1: {
                    peer.setOnOverScrollAttribute((this._onOverScroll_0_0value as arkui_component_common_Callback<OnOverScrollEvent, void> | undefined));
                    flagArray[87] = 2;
                    break;
                }
                case 3: {
                    flagArray[87] = 2;
                    break;
                }
                default: {
                    flagArray[87] = 0;
                    peer.setOnOverScrollAttribute((undefined as arkui_component_common_Callback<OnOverScrollEvent, void> | undefined));
                }
            }
        }
        if (flagArray[88] != 0) {
            switch (flagArray[88]) {
                case 1: {
                    peer.setOnSafeBrowsingCheckResultAttribute((this._onSafeBrowsingCheckResult_0_0value as OnSafeBrowsingCheckResultCallback | undefined));
                    flagArray[88] = 2;
                    break;
                }
                case 3: {
                    flagArray[88] = 2;
                    break;
                }
                default: {
                    flagArray[88] = 0;
                    peer.setOnSafeBrowsingCheckResultAttribute((undefined as OnSafeBrowsingCheckResultCallback | undefined));
                }
            }
        }
        if (flagArray[89] != 0) {
            switch (flagArray[89]) {
                case 1: {
                    peer.setOnNavigationEntryCommittedAttribute((this._onNavigationEntryCommitted_0_0value as OnNavigationEntryCommittedCallback | undefined));
                    flagArray[89] = 2;
                    break;
                }
                case 3: {
                    flagArray[89] = 2;
                    break;
                }
                default: {
                    flagArray[89] = 0;
                    peer.setOnNavigationEntryCommittedAttribute((undefined as OnNavigationEntryCommittedCallback | undefined));
                }
            }
        }
        if (flagArray[90] != 0) {
            switch (flagArray[90]) {
                case 1: {
                    peer.setOnIntelligentTrackingPreventionResultAttribute((this._onIntelligentTrackingPreventionResult_0_0value as OnIntelligentTrackingPreventionCallback | undefined));
                    flagArray[90] = 2;
                    break;
                }
                case 3: {
                    flagArray[90] = 2;
                    break;
                }
                default: {
                    flagArray[90] = 0;
                    peer.setOnIntelligentTrackingPreventionResultAttribute((undefined as OnIntelligentTrackingPreventionCallback | undefined));
                }
            }
        }
        if (flagArray[91] != 0) {
            switch (flagArray[91]) {
                case 1: {
                    peer.setJavaScriptOnDocumentStartAttribute((this._javaScriptOnDocumentStart_0_0value as Array<ScriptItem> | undefined));
                    flagArray[91] = 2;
                    break;
                }
                case 3: {
                    flagArray[91] = 2;
                    break;
                }
                default: {
                    flagArray[91] = 0;
                    peer.setJavaScriptOnDocumentStartAttribute((undefined as Array<ScriptItem> | undefined));
                }
            }
        }
        if (flagArray[92] != 0) {
            switch (flagArray[92]) {
                case 1: {
                    peer.setJavaScriptOnDocumentEndAttribute((this._javaScriptOnDocumentEnd_0_0value as Array<ScriptItem> | undefined));
                    flagArray[92] = 2;
                    break;
                }
                case 3: {
                    flagArray[92] = 2;
                    break;
                }
                default: {
                    flagArray[92] = 0;
                    peer.setJavaScriptOnDocumentEndAttribute((undefined as Array<ScriptItem> | undefined));
                }
            }
        }
        if (flagArray[93] != 0) {
            switch (flagArray[93]) {
                case 1: {
                    peer.setLayoutModeAttribute((this._layoutMode_0_0value as WebLayoutMode | undefined));
                    flagArray[93] = 2;
                    break;
                }
                case 3: {
                    flagArray[93] = 2;
                    break;
                }
                default: {
                    flagArray[93] = 0;
                    peer.setLayoutModeAttribute((undefined as WebLayoutMode | undefined));
                }
            }
        }
        if (flagArray[94] != 0) {
            switch (flagArray[94]) {
                case 1: {
                    peer.setNestedScrollAttribute((this._nestedScroll_0_0value as NestedScrollOptions | NestedScrollOptionsExt | undefined));
                    flagArray[94] = 2;
                    break;
                }
                case 3: {
                    flagArray[94] = 2;
                    break;
                }
                default: {
                    flagArray[94] = 0;
                    peer.setNestedScrollAttribute((undefined as NestedScrollOptions | NestedScrollOptionsExt | undefined));
                }
            }
        }
        if (flagArray[95] != 0) {
            switch (flagArray[95]) {
                case 1: {
                    peer.setEnableNativeEmbedModeAttribute((this._enableNativeEmbedMode_0_0value as boolean | undefined));
                    flagArray[95] = 2;
                    break;
                }
                case 3: {
                    flagArray[95] = 2;
                    break;
                }
                default: {
                    flagArray[95] = 0;
                    peer.setEnableNativeEmbedModeAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[96] != 0) {
            switch (flagArray[96]) {
                case 1: {
                    peer.setOnNativeEmbedLifecycleChangeAttribute((this._onNativeEmbedLifecycleChange_0_0value as ((event: NativeEmbedDataInfo) => void) | undefined));
                    flagArray[96] = 2;
                    break;
                }
                case 3: {
                    flagArray[96] = 2;
                    break;
                }
                default: {
                    flagArray[96] = 0;
                    peer.setOnNativeEmbedLifecycleChangeAttribute((undefined as ((event: NativeEmbedDataInfo) => void) | undefined));
                }
            }
        }
        if (flagArray[97] != 0) {
            switch (flagArray[97]) {
                case 1: {
                    peer.setOnNativeEmbedVisibilityChangeAttribute((this._onNativeEmbedVisibilityChange_0_0value as OnNativeEmbedVisibilityChangeCallback | undefined));
                    flagArray[97] = 2;
                    break;
                }
                case 3: {
                    flagArray[97] = 2;
                    break;
                }
                default: {
                    flagArray[97] = 0;
                    peer.setOnNativeEmbedVisibilityChangeAttribute((undefined as OnNativeEmbedVisibilityChangeCallback | undefined));
                }
            }
        }
        if (flagArray[98] != 0) {
            switch (flagArray[98]) {
                case 1: {
                    peer.setOnNativeEmbedGestureEventAttribute((this._onNativeEmbedGestureEvent_0_0value as ((event: NativeEmbedTouchInfo) => void) | undefined));
                    flagArray[98] = 2;
                    break;
                }
                case 3: {
                    flagArray[98] = 2;
                    break;
                }
                default: {
                    flagArray[98] = 0;
                    peer.setOnNativeEmbedGestureEventAttribute((undefined as ((event: NativeEmbedTouchInfo) => void) | undefined));
                }
            }
        }
        if (flagArray[99] != 0) {
            switch (flagArray[99]) {
                case 1: {
                    peer.setCopyOptionsAttribute((this._copyOptions_0_0value as CopyOptions | undefined));
                    flagArray[99] = 2;
                    break;
                }
                case 3: {
                    flagArray[99] = 2;
                    break;
                }
                default: {
                    flagArray[99] = 0;
                    peer.setCopyOptionsAttribute((undefined as CopyOptions | undefined));
                }
            }
        }
    }
    applyModifierPatch5(peer: ArkWebPeer, flagArray: Uint8Array): void {
        if (flagArray[100] != 0) {
            switch (flagArray[100]) {
                case 1: {
                    peer.setOnOverrideUrlLoadingAttribute((this._onOverrideUrlLoading_0_0value as OnOverrideUrlLoadingCallback | undefined));
                    flagArray[100] = 2;
                    break;
                }
                case 3: {
                    flagArray[100] = 2;
                    break;
                }
                default: {
                    flagArray[100] = 0;
                    peer.setOnOverrideUrlLoadingAttribute((undefined as OnOverrideUrlLoadingCallback | undefined));
                }
            }
        }
        if (flagArray[101] != 0) {
            switch (flagArray[101]) {
                case 1: {
                    peer.setTextAutosizingAttribute((this._textAutosizing_0_0value as boolean | undefined));
                    flagArray[101] = 2;
                    break;
                }
                case 3: {
                    flagArray[101] = 2;
                    break;
                }
                default: {
                    flagArray[101] = 0;
                    peer.setTextAutosizingAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[102] != 0) {
            switch (flagArray[102]) {
                case 1: {
                    peer.setEnableNativeMediaPlayerAttribute((this._enableNativeMediaPlayer_0_0value as NativeMediaPlayerConfig | undefined));
                    flagArray[102] = 2;
                    break;
                }
                case 3: {
                    flagArray[102] = 2;
                    break;
                }
                default: {
                    flagArray[102] = 0;
                    peer.setEnableNativeMediaPlayerAttribute((undefined as NativeMediaPlayerConfig | undefined));
                }
            }
        }
        if (flagArray[103] != 0) {
            switch (flagArray[103]) {
                case 1: {
                    peer.setOnRenderProcessNotRespondingAttribute((this._onRenderProcessNotResponding_0_0value as OnRenderProcessNotRespondingCallback | undefined));
                    flagArray[103] = 2;
                    break;
                }
                case 3: {
                    flagArray[103] = 2;
                    break;
                }
                default: {
                    flagArray[103] = 0;
                    peer.setOnRenderProcessNotRespondingAttribute((undefined as OnRenderProcessNotRespondingCallback | undefined));
                }
            }
        }
        if (flagArray[104] != 0) {
            switch (flagArray[104]) {
                case 1: {
                    peer.setOnRenderProcessRespondingAttribute((this._onRenderProcessResponding_0_0value as OnRenderProcessRespondingCallback | undefined));
                    flagArray[104] = 2;
                    break;
                }
                case 3: {
                    flagArray[104] = 2;
                    break;
                }
                default: {
                    flagArray[104] = 0;
                    peer.setOnRenderProcessRespondingAttribute((undefined as OnRenderProcessRespondingCallback | undefined));
                }
            }
        }
        if (flagArray[105] != 0) {
            switch (flagArray[105]) {
                case 1: {
                    peer.setOnViewportFitChangedAttribute((this._onViewportFitChanged_0_0value as OnViewportFitChangedCallback | undefined));
                    flagArray[105] = 2;
                    break;
                }
                case 3: {
                    flagArray[105] = 2;
                    break;
                }
                default: {
                    flagArray[105] = 0;
                    peer.setOnViewportFitChangedAttribute((undefined as OnViewportFitChangedCallback | undefined));
                }
            }
        }
        if (flagArray[106] != 0) {
            switch (flagArray[106]) {
                case 1: {
                    peer.setOnInterceptKeyboardAttachAttribute((this._onInterceptKeyboardAttach_0_0value as WebKeyboardCallback | undefined));
                    flagArray[106] = 2;
                    break;
                }
                case 3: {
                    flagArray[106] = 2;
                    break;
                }
                default: {
                    flagArray[106] = 0;
                    peer.setOnInterceptKeyboardAttachAttribute((undefined as WebKeyboardCallback | undefined));
                }
            }
        }
        if (flagArray[107] != 0) {
            switch (flagArray[107]) {
                case 1: {
                    peer.setOnAdsBlockedAttribute((this._onAdsBlocked_0_0value as OnAdsBlockedCallback | undefined));
                    flagArray[107] = 2;
                    break;
                }
                case 3: {
                    flagArray[107] = 2;
                    break;
                }
                default: {
                    flagArray[107] = 0;
                    peer.setOnAdsBlockedAttribute((undefined as OnAdsBlockedCallback | undefined));
                }
            }
        }
        if (flagArray[108] != 0) {
            switch (flagArray[108]) {
                case 1: {
                    peer.setKeyboardAvoidModeAttribute((this._keyboardAvoidMode_0_0value as WebKeyboardAvoidMode | undefined));
                    flagArray[108] = 2;
                    break;
                }
                case 3: {
                    flagArray[108] = 2;
                    break;
                }
                default: {
                    flagArray[108] = 0;
                    peer.setKeyboardAvoidModeAttribute((undefined as WebKeyboardAvoidMode | undefined));
                }
            }
        }
        if (flagArray[109] != 0) {
            switch (flagArray[109]) {
                case 1: {
                    peer.setEditMenuOptionsAttribute((this._editMenuOptions_0_0value as EditMenuOptions | undefined));
                    flagArray[109] = 2;
                    break;
                }
                case 3: {
                    flagArray[109] = 2;
                    break;
                }
                default: {
                    flagArray[109] = 0;
                    peer.setEditMenuOptionsAttribute((undefined as EditMenuOptions | undefined));
                }
            }
        }
        if (flagArray[110] != 0) {
            switch (flagArray[110]) {
                case 1: {
                    peer.setEnableHapticFeedbackAttribute((this._enableHapticFeedback_0_0value as boolean | undefined));
                    flagArray[110] = 2;
                    break;
                }
                case 3: {
                    flagArray[110] = 2;
                    break;
                }
                default: {
                    flagArray[110] = 0;
                    peer.setEnableHapticFeedbackAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[111] != 0) {
            switch (flagArray[111]) {
                case 1: {
                    peer.setEnableFollowSystemFontWeightAttribute((this._enableFollowSystemFontWeight_0_0value as boolean | undefined));
                    flagArray[111] = 2;
                    break;
                }
                case 3: {
                    flagArray[111] = 2;
                    break;
                }
                default: {
                    flagArray[111] = 0;
                    peer.setEnableFollowSystemFontWeightAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[112] != 0) {
            switch (flagArray[112]) {
                case 1: {
                    peer.setEnableWebAVSessionAttribute((this._enableWebAVSession_0_0value as boolean | undefined));
                    flagArray[112] = 2;
                    break;
                }
                case 3: {
                    flagArray[112] = 2;
                    break;
                }
                default: {
                    flagArray[112] = 0;
                    peer.setEnableWebAVSessionAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[113] != 0) {
            switch (flagArray[113]) {
                case 1: {
                    peer.setOptimizeParserBudgetAttribute((this._optimizeParserBudget_0_0value as boolean | undefined));
                    flagArray[113] = 2;
                    break;
                }
                case 3: {
                    flagArray[113] = 2;
                    break;
                }
                default: {
                    flagArray[113] = 0;
                    peer.setOptimizeParserBudgetAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[114] != 0) {
            switch (flagArray[114]) {
                case 1: {
                    peer.setRunJavaScriptOnDocumentStartAttribute((this._runJavaScriptOnDocumentStart_0_0value as Array<ScriptItem> | undefined));
                    flagArray[114] = 2;
                    break;
                }
                case 3: {
                    flagArray[114] = 2;
                    break;
                }
                default: {
                    flagArray[114] = 0;
                    peer.setRunJavaScriptOnDocumentStartAttribute((undefined as Array<ScriptItem> | undefined));
                }
            }
        }
        if (flagArray[115] != 0) {
            switch (flagArray[115]) {
                case 1: {
                    peer.setRunJavaScriptOnDocumentEndAttribute((this._runJavaScriptOnDocumentEnd_0_0value as Array<ScriptItem> | undefined));
                    flagArray[115] = 2;
                    break;
                }
                case 3: {
                    flagArray[115] = 2;
                    break;
                }
                default: {
                    flagArray[115] = 0;
                    peer.setRunJavaScriptOnDocumentEndAttribute((undefined as Array<ScriptItem> | undefined));
                }
            }
        }
        if (flagArray[116] != 0) {
            switch (flagArray[116]) {
                case 1: {
                    peer.setRunJavaScriptOnHeadEndAttribute((this._runJavaScriptOnHeadEnd_0_0value as Array<ScriptItem> | undefined));
                    flagArray[116] = 2;
                    break;
                }
                case 3: {
                    flagArray[116] = 2;
                    break;
                }
                default: {
                    flagArray[116] = 0;
                    peer.setRunJavaScriptOnHeadEndAttribute((undefined as Array<ScriptItem> | undefined));
                }
            }
        }
        if (flagArray[117] != 0) {
            switch (flagArray[117]) {
                case 1: {
                    peer.setNativeEmbedOptionsAttribute((this._nativeEmbedOptions_0_0value as EmbedOptions | undefined));
                    flagArray[117] = 2;
                    break;
                }
                case 3: {
                    flagArray[117] = 2;
                    break;
                }
                default: {
                    flagArray[117] = 0;
                    peer.setNativeEmbedOptionsAttribute((undefined as EmbedOptions | undefined));
                }
            }
        }
        if (flagArray[118] != 0) {
            switch (flagArray[118]) {
                case 1: {
                    peer.setRegisterNativeEmbedRuleAttribute((this._registerNativeEmbedRule_0_0value as string | undefined), (this._registerNativeEmbedRule_0_1value as string | undefined));
                    flagArray[118] = 2;
                    break;
                }
                case 3: {
                    flagArray[118] = 2;
                    break;
                }
                default: {
                    flagArray[118] = 0;
                    peer.setRegisterNativeEmbedRuleAttribute((undefined as string | undefined), (undefined as string | undefined));
                }
            }
        }
        if (flagArray[119] != 0) {
            switch (flagArray[119]) {
                case 1: {
                    peer.setBindSelectionMenuAttribute((this._bindSelectionMenu_0_0value as WebElementType | undefined), (this._bindSelectionMenu_0_1value as CustomBuilder | undefined), (this._bindSelectionMenu_0_2value as WebResponseType | undefined), (this._bindSelectionMenu_0_3value as SelectionMenuOptionsExt | undefined | undefined));
                    flagArray[119] = 2;
                    break;
                }
                case 3: {
                    flagArray[119] = 2;
                    break;
                }
                default: {
                    flagArray[119] = 0;
                    peer.setBindSelectionMenuAttribute((undefined as WebElementType | undefined), (undefined as CustomBuilder | undefined), (undefined as WebResponseType | undefined), (undefined as SelectionMenuOptionsExt | undefined | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: WebModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        const flagArray = modifier._flagArray;
        this.mergeModifier0(modifier, flagArray);
        this.mergeModifier1(modifier, flagArray);
        this.mergeModifier2(modifier, flagArray);
        this.mergeModifier3(modifier, flagArray);
        this.mergeModifier4(modifier, flagArray);
        this.mergeModifier5(modifier, flagArray);
    }
    mergeModifier0(modifier: WebModifier, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1:
                case 3: {
                    this.javaScriptAccess(modifier._javaScriptAccess_0_0value);
                    break;
                }
                default: {
                    this.javaScriptAccess((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1:
                case 3: {
                    this.fileAccess(modifier._fileAccess_0_0value);
                    break;
                }
                default: {
                    this.fileAccess((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1:
                case 3: {
                    this.onlineImageAccess(modifier._onlineImageAccess_0_0value);
                    break;
                }
                default: {
                    this.onlineImageAccess((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[3] != 0) {
            switch (flagArray[3]) {
                case 1:
                case 3: {
                    this.domStorageAccess(modifier._domStorageAccess_0_0value);
                    break;
                }
                default: {
                    this.domStorageAccess((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[4] != 0) {
            switch (flagArray[4]) {
                case 1:
                case 3: {
                    this.imageAccess(modifier._imageAccess_0_0value);
                    break;
                }
                default: {
                    this.imageAccess((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[5] != 0) {
            switch (flagArray[5]) {
                case 1:
                case 3: {
                    this.mixedMode(modifier._mixedMode_0_0value);
                    break;
                }
                default: {
                    this.mixedMode((undefined as MixedMode | undefined));
                }
            }
        }
        if (flagArray[6] != 0) {
            switch (flagArray[6]) {
                case 1:
                case 3: {
                    this.zoomAccess(modifier._zoomAccess_0_0value);
                    break;
                }
                default: {
                    this.zoomAccess((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[7] != 0) {
            switch (flagArray[7]) {
                case 1:
                case 3: {
                    this.geolocationAccess(modifier._geolocationAccess_0_0value);
                    break;
                }
                default: {
                    this.geolocationAccess((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[8] != 0) {
            switch (flagArray[8]) {
                case 1:
                case 3: {
                    this.javaScriptProxy(modifier._javaScriptProxy_0_0value);
                    break;
                }
                default: {
                    this.javaScriptProxy((undefined as JavaScriptProxy | undefined));
                }
            }
        }
        if (flagArray[9] != 0) {
            switch (flagArray[9]) {
                case 1:
                case 3: {
                    this.cacheMode(modifier._cacheMode_0_0value);
                    break;
                }
                default: {
                    this.cacheMode((undefined as CacheMode | undefined));
                }
            }
        }
        if (flagArray[10] != 0) {
            switch (flagArray[10]) {
                case 1:
                case 3: {
                    this.darkMode(modifier._darkMode_0_0value);
                    break;
                }
                default: {
                    this.darkMode((undefined as WebDarkMode | undefined));
                }
            }
        }
        if (flagArray[11] != 0) {
            switch (flagArray[11]) {
                case 1:
                case 3: {
                    this.forceDarkAccess(modifier._forceDarkAccess_0_0value);
                    break;
                }
                default: {
                    this.forceDarkAccess((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[12] != 0) {
            switch (flagArray[12]) {
                case 1:
                case 3: {
                    this.mediaOptions(modifier._mediaOptions_0_0value);
                    break;
                }
                default: {
                    this.mediaOptions((undefined as WebMediaOptions | undefined));
                }
            }
        }
        if (flagArray[13] != 0) {
            switch (flagArray[13]) {
                case 1:
                case 3: {
                    this.overviewModeAccess(modifier._overviewModeAccess_0_0value);
                    break;
                }
                default: {
                    this.overviewModeAccess((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[14] != 0) {
            switch (flagArray[14]) {
                case 1:
                case 3: {
                    this.overScrollMode(modifier._overScrollMode_0_0value);
                    break;
                }
                default: {
                    this.overScrollMode((undefined as OverScrollMode | undefined));
                }
            }
        }
        if (flagArray[15] != 0) {
            switch (flagArray[15]) {
                case 1:
                case 3: {
                    this.blurOnKeyboardHideMode(modifier._blurOnKeyboardHideMode_0_0value);
                    break;
                }
                default: {
                    this.blurOnKeyboardHideMode((undefined as BlurOnKeyboardHideMode | undefined));
                }
            }
        }
        if (flagArray[16] != 0) {
            switch (flagArray[16]) {
                case 1:
                case 3: {
                    this.textZoomRatio(modifier._textZoomRatio_0_0value);
                    break;
                }
                default: {
                    this.textZoomRatio((undefined as int32 | undefined));
                }
            }
        }
        if (flagArray[17] != 0) {
            switch (flagArray[17]) {
                case 1:
                case 3: {
                    this.databaseAccess(modifier._databaseAccess_0_0value);
                    break;
                }
                default: {
                    this.databaseAccess((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[18] != 0) {
            switch (flagArray[18]) {
                case 1:
                case 3: {
                    this.initialScale(modifier._initialScale_0_0value);
                    break;
                }
                default: {
                    this.initialScale((undefined as double | undefined));
                }
            }
        }
        if (flagArray[19] != 0) {
            switch (flagArray[19]) {
                case 1:
                case 3: {
                    this.metaViewport(modifier._metaViewport_0_0value);
                    break;
                }
                default: {
                    this.metaViewport((undefined as boolean | undefined));
                }
            }
        }
    }
    mergeModifier1(modifier: WebModifier, flagArray: Uint8Array): void {
        if (flagArray[20] != 0) {
            switch (flagArray[20]) {
                case 1:
                case 3: {
                    this.onPageBegin(modifier._onPageBegin_0_0value);
                    break;
                }
                default: {
                    this.onPageBegin((undefined as arkui_component_common_Callback<OnPageBeginEvent, void> | undefined));
                }
            }
        }
        if (flagArray[21] != 0) {
            switch (flagArray[21]) {
                case 1:
                case 3: {
                    this.onPageEnd(modifier._onPageEnd_0_0value);
                    break;
                }
                default: {
                    this.onPageEnd((undefined as arkui_component_common_Callback<OnPageEndEvent, void> | undefined));
                }
            }
        }
        if (flagArray[22] != 0) {
            switch (flagArray[22]) {
                case 1:
                case 3: {
                    this.onLoadStarted(modifier._onLoadStarted_0_0value);
                    break;
                }
                default: {
                    this.onLoadStarted((undefined as arkui_component_common_Callback<OnLoadStartedEvent, void> | undefined));
                }
            }
        }
        if (flagArray[23] != 0) {
            switch (flagArray[23]) {
                case 1:
                case 3: {
                    this.onLoadFinished(modifier._onLoadFinished_0_0value);
                    break;
                }
                default: {
                    this.onLoadFinished((undefined as arkui_component_common_Callback<OnLoadFinishedEvent, void> | undefined));
                }
            }
        }
        if (flagArray[24] != 0) {
            switch (flagArray[24]) {
                case 1:
                case 3: {
                    this.onProgressChange(modifier._onProgressChange_0_0value);
                    break;
                }
                default: {
                    this.onProgressChange((undefined as arkui_component_common_Callback<OnProgressChangeEvent, void> | undefined));
                }
            }
        }
        if (flagArray[25] != 0) {
            switch (flagArray[25]) {
                case 1:
                case 3: {
                    this.onTitleReceive(modifier._onTitleReceive_0_0value);
                    break;
                }
                default: {
                    this.onTitleReceive((undefined as arkui_component_common_Callback<OnTitleReceiveEvent, void> | undefined));
                }
            }
        }
        if (flagArray[26] != 0) {
            switch (flagArray[26]) {
                case 1:
                case 3: {
                    this.onGeolocationHide(modifier._onGeolocationHide_0_0value);
                    break;
                }
                default: {
                    this.onGeolocationHide((undefined as (() => void) | undefined));
                }
            }
        }
        if (flagArray[27] != 0) {
            switch (flagArray[27]) {
                case 1:
                case 3: {
                    this.onGeolocationShow(modifier._onGeolocationShow_0_0value);
                    break;
                }
                default: {
                    this.onGeolocationShow((undefined as arkui_component_common_Callback<OnGeolocationShowEvent, void> | undefined));
                }
            }
        }
        if (flagArray[28] != 0) {
            switch (flagArray[28]) {
                case 1:
                case 3: {
                    this.onRequestSelected(modifier._onRequestSelected_0_0value);
                    break;
                }
                default: {
                    this.onRequestSelected((undefined as (() => void) | undefined));
                }
            }
        }
        if (flagArray[29] != 0) {
            switch (flagArray[29]) {
                case 1:
                case 3: {
                    this.onAlert(modifier._onAlert_0_0value);
                    break;
                }
                default: {
                    this.onAlert((undefined as arkui_component_common_Callback<OnAlertEvent, boolean> | undefined));
                }
            }
        }
        if (flagArray[30] != 0) {
            switch (flagArray[30]) {
                case 1:
                case 3: {
                    this.onBeforeUnload(modifier._onBeforeUnload_0_0value);
                    break;
                }
                default: {
                    this.onBeforeUnload((undefined as arkui_component_common_Callback<OnBeforeUnloadEvent, boolean> | undefined));
                }
            }
        }
        if (flagArray[31] != 0) {
            switch (flagArray[31]) {
                case 1:
                case 3: {
                    this.onConfirm(modifier._onConfirm_0_0value);
                    break;
                }
                default: {
                    this.onConfirm((undefined as arkui_component_common_Callback<OnConfirmEvent, boolean> | undefined));
                }
            }
        }
        if (flagArray[32] != 0) {
            switch (flagArray[32]) {
                case 1:
                case 3: {
                    this.onPrompt(modifier._onPrompt_0_0value);
                    break;
                }
                default: {
                    this.onPrompt((undefined as arkui_component_common_Callback<OnPromptEvent, boolean> | undefined));
                }
            }
        }
        if (flagArray[33] != 0) {
            switch (flagArray[33]) {
                case 1:
                case 3: {
                    this.onConsole(modifier._onConsole_0_0value);
                    break;
                }
                default: {
                    this.onConsole((undefined as arkui_component_common_Callback<OnConsoleEvent, boolean> | undefined));
                }
            }
        }
        if (flagArray[34] != 0) {
            switch (flagArray[34]) {
                case 1:
                case 3: {
                    this.onErrorReceive(modifier._onErrorReceive_0_0value);
                    break;
                }
                default: {
                    this.onErrorReceive((undefined as arkui_component_common_Callback<OnErrorReceiveEvent, void> | undefined));
                }
            }
        }
        if (flagArray[35] != 0) {
            switch (flagArray[35]) {
                case 1:
                case 3: {
                    this.onHttpErrorReceive(modifier._onHttpErrorReceive_0_0value);
                    break;
                }
                default: {
                    this.onHttpErrorReceive((undefined as arkui_component_common_Callback<OnHttpErrorReceiveEvent, void> | undefined));
                }
            }
        }
        if (flagArray[36] != 0) {
            switch (flagArray[36]) {
                case 1:
                case 3: {
                    this.onDownloadStart(modifier._onDownloadStart_0_0value);
                    break;
                }
                default: {
                    this.onDownloadStart((undefined as arkui_component_common_Callback<OnDownloadStartEvent, void> | undefined));
                }
            }
        }
        if (flagArray[37] != 0) {
            switch (flagArray[37]) {
                case 1:
                case 3: {
                    this.onRefreshAccessedHistory(modifier._onRefreshAccessedHistory_0_0value);
                    break;
                }
                default: {
                    this.onRefreshAccessedHistory((undefined as arkui_component_common_Callback<OnRefreshAccessedHistoryEvent, void> | undefined));
                }
            }
        }
        if (flagArray[38] != 0) {
            switch (flagArray[38]) {
                case 1:
                case 3: {
                    this.onRenderExited(modifier._onRenderExited_0_0value);
                    break;
                }
                default: {
                    this.onRenderExited((undefined as arkui_component_common_Callback<OnRenderExitedEvent, void> | undefined));
                }
            }
        }
        if (flagArray[39] != 0) {
            switch (flagArray[39]) {
                case 1:
                case 3: {
                    this.onShowFileSelector(modifier._onShowFileSelector_0_0value);
                    break;
                }
                default: {
                    this.onShowFileSelector((undefined as arkui_component_common_Callback<OnShowFileSelectorEvent, boolean> | undefined));
                }
            }
        }
    }
    mergeModifier2(modifier: WebModifier, flagArray: Uint8Array): void {
        if (flagArray[40] != 0) {
            switch (flagArray[40]) {
                case 1:
                case 3: {
                    this.onResourceLoad(modifier._onResourceLoad_0_0value);
                    break;
                }
                default: {
                    this.onResourceLoad((undefined as arkui_component_common_Callback<OnResourceLoadEvent, void> | undefined));
                }
            }
        }
        if (flagArray[41] != 0) {
            switch (flagArray[41]) {
                case 1:
                case 3: {
                    this.onFullScreenExit(modifier._onFullScreenExit_0_0value);
                    break;
                }
                default: {
                    this.onFullScreenExit((undefined as (() => void) | undefined));
                }
            }
        }
        if (flagArray[42] != 0) {
            switch (flagArray[42]) {
                case 1:
                case 3: {
                    this.onFullScreenEnter(modifier._onFullScreenEnter_0_0value);
                    break;
                }
                default: {
                    this.onFullScreenEnter((undefined as OnFullScreenEnterCallback | undefined));
                }
            }
        }
        if (flagArray[43] != 0) {
            switch (flagArray[43]) {
                case 1:
                case 3: {
                    this.onScaleChange(modifier._onScaleChange_0_0value);
                    break;
                }
                default: {
                    this.onScaleChange((undefined as arkui_component_common_Callback<OnScaleChangeEvent, void> | undefined));
                }
            }
        }
        if (flagArray[44] != 0) {
            switch (flagArray[44]) {
                case 1:
                case 3: {
                    this.onHttpAuthRequest(modifier._onHttpAuthRequest_0_0value);
                    break;
                }
                default: {
                    this.onHttpAuthRequest((undefined as arkui_component_common_Callback<OnHttpAuthRequestEvent, boolean> | undefined));
                }
            }
        }
        if (flagArray[45] != 0) {
            switch (flagArray[45]) {
                case 1:
                case 3: {
                    this.onInterceptRequest(modifier._onInterceptRequest_0_0value);
                    break;
                }
                default: {
                    this.onInterceptRequest((undefined as arkui_component_common_Callback<OnInterceptRequestEvent, WebResourceResponse | null> | undefined));
                }
            }
        }
        if (flagArray[46] != 0) {
            switch (flagArray[46]) {
                case 1:
                case 3: {
                    this.onPermissionRequest(modifier._onPermissionRequest_0_0value);
                    break;
                }
                default: {
                    this.onPermissionRequest((undefined as arkui_component_common_Callback<OnPermissionRequestEvent, void> | undefined));
                }
            }
        }
        if (flagArray[47] != 0) {
            switch (flagArray[47]) {
                case 1:
                case 3: {
                    this.onScreenCaptureRequest(modifier._onScreenCaptureRequest_0_0value);
                    break;
                }
                default: {
                    this.onScreenCaptureRequest((undefined as arkui_component_common_Callback<OnScreenCaptureRequestEvent, void> | undefined));
                }
            }
        }
        if (flagArray[48] != 0) {
            switch (flagArray[48]) {
                case 1:
                case 3: {
                    this.onContextMenuShow(modifier._onContextMenuShow_0_0value);
                    break;
                }
                default: {
                    this.onContextMenuShow((undefined as arkui_component_common_Callback<OnContextMenuShowEvent, boolean> | undefined));
                }
            }
        }
        if (flagArray[49] != 0) {
            switch (flagArray[49]) {
                case 1:
                case 3: {
                    this.onContextMenuHide(modifier._onContextMenuHide_0_0value);
                    break;
                }
                default: {
                    this.onContextMenuHide((undefined as OnContextMenuHideCallback | undefined));
                }
            }
        }
        if (flagArray[50] != 0) {
            switch (flagArray[50]) {
                case 1:
                case 3: {
                    this.mediaPlayGestureAccess(modifier._mediaPlayGestureAccess_0_0value);
                    break;
                }
                default: {
                    this.mediaPlayGestureAccess((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[51] != 0) {
            switch (flagArray[51]) {
                case 1:
                case 3: {
                    this.onSearchResultReceive(modifier._onSearchResultReceive_0_0value);
                    break;
                }
                default: {
                    this.onSearchResultReceive((undefined as arkui_component_common_Callback<OnSearchResultReceiveEvent, void> | undefined));
                }
            }
        }
        if (flagArray[52] != 0) {
            switch (flagArray[52]) {
                case 1:
                case 3: {
                    this.onScroll(modifier._onScroll_0_0value);
                    break;
                }
                default: {
                    this.onScroll((undefined as arkui_component_common_Callback<OnScrollEvent, void> | undefined));
                }
            }
        }
        if (flagArray[53] != 0) {
            switch (flagArray[53]) {
                case 1:
                case 3: {
                    this.onSslErrorEventReceive(modifier._onSslErrorEventReceive_0_0value);
                    break;
                }
                default: {
                    this.onSslErrorEventReceive((undefined as arkui_component_common_Callback<OnSslErrorEventReceiveEvent, void> | undefined));
                }
            }
        }
        if (flagArray[54] != 0) {
            switch (flagArray[54]) {
                case 1:
                case 3: {
                    this.onSslErrorEvent(modifier._onSslErrorEvent_0_0value);
                    break;
                }
                default: {
                    this.onSslErrorEvent((undefined as OnSslErrorEventCallback | undefined));
                }
            }
        }
        if (flagArray[55] != 0) {
            switch (flagArray[55]) {
                case 1:
                case 3: {
                    this.onClientAuthenticationRequest(modifier._onClientAuthenticationRequest_0_0value);
                    break;
                }
                default: {
                    this.onClientAuthenticationRequest((undefined as arkui_component_common_Callback<OnClientAuthenticationEvent, void> | undefined));
                }
            }
        }
        if (flagArray[56] != 0) {
            switch (flagArray[56]) {
                case 1:
                case 3: {
                    this.onWindowNew(modifier._onWindowNew_0_0value);
                    break;
                }
                default: {
                    this.onWindowNew((undefined as arkui_component_common_Callback<OnWindowNewEvent, void> | undefined));
                }
            }
        }
        if (flagArray[57] != 0) {
            switch (flagArray[57]) {
                case 1:
                case 3: {
                    this.onWindowExit(modifier._onWindowExit_0_0value);
                    break;
                }
                default: {
                    this.onWindowExit((undefined as (() => void) | undefined));
                }
            }
        }
        if (flagArray[58] != 0) {
            switch (flagArray[58]) {
                case 1:
                case 3: {
                    this.multiWindowAccess(modifier._multiWindowAccess_0_0value);
                    break;
                }
                default: {
                    this.multiWindowAccess((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[59] != 0) {
            switch (flagArray[59]) {
                case 1:
                case 3: {
                    this.onInterceptKeyEvent(modifier._onInterceptKeyEvent_0_0value);
                    break;
                }
                default: {
                    this.onInterceptKeyEvent((undefined as ((event: KeyEvent) => boolean) | undefined));
                }
            }
        }
    }
    mergeModifier3(modifier: WebModifier, flagArray: Uint8Array): void {
        if (flagArray[60] != 0) {
            switch (flagArray[60]) {
                case 1:
                case 3: {
                    this.webStandardFont(modifier._webStandardFont_0_0value);
                    break;
                }
                default: {
                    this.webStandardFont((undefined as string | undefined));
                }
            }
        }
        if (flagArray[61] != 0) {
            switch (flagArray[61]) {
                case 1:
                case 3: {
                    this.webSerifFont(modifier._webSerifFont_0_0value);
                    break;
                }
                default: {
                    this.webSerifFont((undefined as string | undefined));
                }
            }
        }
        if (flagArray[62] != 0) {
            switch (flagArray[62]) {
                case 1:
                case 3: {
                    this.webSansSerifFont(modifier._webSansSerifFont_0_0value);
                    break;
                }
                default: {
                    this.webSansSerifFont((undefined as string | undefined));
                }
            }
        }
        if (flagArray[63] != 0) {
            switch (flagArray[63]) {
                case 1:
                case 3: {
                    this.webFixedFont(modifier._webFixedFont_0_0value);
                    break;
                }
                default: {
                    this.webFixedFont((undefined as string | undefined));
                }
            }
        }
        if (flagArray[64] != 0) {
            switch (flagArray[64]) {
                case 1:
                case 3: {
                    this.webFantasyFont(modifier._webFantasyFont_0_0value);
                    break;
                }
                default: {
                    this.webFantasyFont((undefined as string | undefined));
                }
            }
        }
        if (flagArray[65] != 0) {
            switch (flagArray[65]) {
                case 1:
                case 3: {
                    this.webCursiveFont(modifier._webCursiveFont_0_0value);
                    break;
                }
                default: {
                    this.webCursiveFont((undefined as string | undefined));
                }
            }
        }
        if (flagArray[66] != 0) {
            switch (flagArray[66]) {
                case 1:
                case 3: {
                    this.defaultFixedFontSize(modifier._defaultFixedFontSize_0_0value);
                    break;
                }
                default: {
                    this.defaultFixedFontSize((undefined as int32 | undefined));
                }
            }
        }
        if (flagArray[67] != 0) {
            switch (flagArray[67]) {
                case 1:
                case 3: {
                    this.defaultFontSize(modifier._defaultFontSize_0_0value);
                    break;
                }
                default: {
                    this.defaultFontSize((undefined as int32 | undefined));
                }
            }
        }
        if (flagArray[68] != 0) {
            switch (flagArray[68]) {
                case 1:
                case 3: {
                    this.minFontSize(modifier._minFontSize_0_0value);
                    break;
                }
                default: {
                    this.minFontSize((undefined as int32 | undefined));
                }
            }
        }
        if (flagArray[69] != 0) {
            switch (flagArray[69]) {
                case 1:
                case 3: {
                    this.minLogicalFontSize(modifier._minLogicalFontSize_0_0value);
                    break;
                }
                default: {
                    this.minLogicalFontSize((undefined as int32 | undefined));
                }
            }
        }
        if (flagArray[70] != 0) {
            switch (flagArray[70]) {
                case 1:
                case 3: {
                    this.defaultTextEncodingFormat(modifier._defaultTextEncodingFormat_0_0value);
                    break;
                }
                default: {
                    this.defaultTextEncodingFormat((undefined as string | undefined));
                }
            }
        }
        if (flagArray[71] != 0) {
            switch (flagArray[71]) {
                case 1:
                case 3: {
                    this.forceDisplayScrollBar(modifier._forceDisplayScrollBar_0_0value);
                    break;
                }
                default: {
                    this.forceDisplayScrollBar((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[72] != 0) {
            switch (flagArray[72]) {
                case 1:
                case 3: {
                    this.blockNetwork(modifier._blockNetwork_0_0value);
                    break;
                }
                default: {
                    this.blockNetwork((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[73] != 0) {
            switch (flagArray[73]) {
                case 1:
                case 3: {
                    this.horizontalScrollBarAccess(modifier._horizontalScrollBarAccess_0_0value);
                    break;
                }
                default: {
                    this.horizontalScrollBarAccess((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[74] != 0) {
            switch (flagArray[74]) {
                case 1:
                case 3: {
                    this.verticalScrollBarAccess(modifier._verticalScrollBarAccess_0_0value);
                    break;
                }
                default: {
                    this.verticalScrollBarAccess((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[75] != 0) {
            switch (flagArray[75]) {
                case 1:
                case 3: {
                    this.onTouchIconUrlReceived(modifier._onTouchIconUrlReceived_0_0value);
                    break;
                }
                default: {
                    this.onTouchIconUrlReceived((undefined as arkui_component_common_Callback<OnTouchIconUrlReceivedEvent, void> | undefined));
                }
            }
        }
        if (flagArray[76] != 0) {
            switch (flagArray[76]) {
                case 1:
                case 3: {
                    this.onFaviconReceived(modifier._onFaviconReceived_0_0value);
                    break;
                }
                default: {
                    this.onFaviconReceived((undefined as arkui_component_common_Callback<OnFaviconReceivedEvent, void> | undefined));
                }
            }
        }
        if (flagArray[77] != 0) {
            switch (flagArray[77]) {
                case 1:
                case 3: {
                    this.onPageVisible(modifier._onPageVisible_0_0value);
                    break;
                }
                default: {
                    this.onPageVisible((undefined as arkui_component_common_Callback<OnPageVisibleEvent, void> | undefined));
                }
            }
        }
        if (flagArray[78] != 0) {
            switch (flagArray[78]) {
                case 1:
                case 3: {
                    this.onDataResubmitted(modifier._onDataResubmitted_0_0value);
                    break;
                }
                default: {
                    this.onDataResubmitted((undefined as arkui_component_common_Callback<OnDataResubmittedEvent, void> | undefined));
                }
            }
        }
        if (flagArray[79] != 0) {
            switch (flagArray[79]) {
                case 1:
                case 3: {
                    this.pinchSmooth(modifier._pinchSmooth_0_0value);
                    break;
                }
                default: {
                    this.pinchSmooth((undefined as boolean | undefined));
                }
            }
        }
    }
    mergeModifier4(modifier: WebModifier, flagArray: Uint8Array): void {
        if (flagArray[80] != 0) {
            switch (flagArray[80]) {
                case 1:
                case 3: {
                    this.allowWindowOpenMethod(modifier._allowWindowOpenMethod_0_0value);
                    break;
                }
                default: {
                    this.allowWindowOpenMethod((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[81] != 0) {
            switch (flagArray[81]) {
                case 1:
                case 3: {
                    this.onAudioStateChanged(modifier._onAudioStateChanged_0_0value);
                    break;
                }
                default: {
                    this.onAudioStateChanged((undefined as arkui_component_common_Callback<OnAudioStateChangedEvent, void> | undefined));
                }
            }
        }
        if (flagArray[82] != 0) {
            switch (flagArray[82]) {
                case 1:
                case 3: {
                    this.onFirstContentfulPaint(modifier._onFirstContentfulPaint_0_0value);
                    break;
                }
                default: {
                    this.onFirstContentfulPaint((undefined as arkui_component_common_Callback<OnFirstContentfulPaintEvent, void> | undefined));
                }
            }
        }
        if (flagArray[83] != 0) {
            switch (flagArray[83]) {
                case 1:
                case 3: {
                    this.onFirstMeaningfulPaint(modifier._onFirstMeaningfulPaint_0_0value);
                    break;
                }
                default: {
                    this.onFirstMeaningfulPaint((undefined as OnFirstMeaningfulPaintCallback | undefined));
                }
            }
        }
        if (flagArray[84] != 0) {
            switch (flagArray[84]) {
                case 1:
                case 3: {
                    this.onLargestContentfulPaint(modifier._onLargestContentfulPaint_0_0value);
                    break;
                }
                default: {
                    this.onLargestContentfulPaint((undefined as OnLargestContentfulPaintCallback | undefined));
                }
            }
        }
        if (flagArray[85] != 0) {
            switch (flagArray[85]) {
                case 1:
                case 3: {
                    this.onLoadIntercept(modifier._onLoadIntercept_0_0value);
                    break;
                }
                default: {
                    this.onLoadIntercept((undefined as arkui_component_common_Callback<OnLoadInterceptEvent, boolean> | undefined));
                }
            }
        }
        if (flagArray[86] != 0) {
            switch (flagArray[86]) {
                case 1:
                case 3: {
                    this.onControllerAttached(modifier._onControllerAttached_0_0value);
                    break;
                }
                default: {
                    this.onControllerAttached((undefined as (() => void) | undefined));
                }
            }
        }
        if (flagArray[87] != 0) {
            switch (flagArray[87]) {
                case 1:
                case 3: {
                    this.onOverScroll(modifier._onOverScroll_0_0value);
                    break;
                }
                default: {
                    this.onOverScroll((undefined as arkui_component_common_Callback<OnOverScrollEvent, void> | undefined));
                }
            }
        }
        if (flagArray[88] != 0) {
            switch (flagArray[88]) {
                case 1:
                case 3: {
                    this.onSafeBrowsingCheckResult(modifier._onSafeBrowsingCheckResult_0_0value);
                    break;
                }
                default: {
                    this.onSafeBrowsingCheckResult((undefined as OnSafeBrowsingCheckResultCallback | undefined));
                }
            }
        }
        if (flagArray[89] != 0) {
            switch (flagArray[89]) {
                case 1:
                case 3: {
                    this.onNavigationEntryCommitted(modifier._onNavigationEntryCommitted_0_0value);
                    break;
                }
                default: {
                    this.onNavigationEntryCommitted((undefined as OnNavigationEntryCommittedCallback | undefined));
                }
            }
        }
        if (flagArray[90] != 0) {
            switch (flagArray[90]) {
                case 1:
                case 3: {
                    this.onIntelligentTrackingPreventionResult(modifier._onIntelligentTrackingPreventionResult_0_0value);
                    break;
                }
                default: {
                    this.onIntelligentTrackingPreventionResult((undefined as OnIntelligentTrackingPreventionCallback | undefined));
                }
            }
        }
        if (flagArray[91] != 0) {
            switch (flagArray[91]) {
                case 1:
                case 3: {
                    this.javaScriptOnDocumentStart(modifier._javaScriptOnDocumentStart_0_0value);
                    break;
                }
                default: {
                    this.javaScriptOnDocumentStart((undefined as Array<ScriptItem> | undefined));
                }
            }
        }
        if (flagArray[92] != 0) {
            switch (flagArray[92]) {
                case 1:
                case 3: {
                    this.javaScriptOnDocumentEnd(modifier._javaScriptOnDocumentEnd_0_0value);
                    break;
                }
                default: {
                    this.javaScriptOnDocumentEnd((undefined as Array<ScriptItem> | undefined));
                }
            }
        }
        if (flagArray[93] != 0) {
            switch (flagArray[93]) {
                case 1:
                case 3: {
                    this.layoutMode(modifier._layoutMode_0_0value);
                    break;
                }
                default: {
                    this.layoutMode((undefined as WebLayoutMode | undefined));
                }
            }
        }
        if (flagArray[94] != 0) {
            switch (flagArray[94]) {
                case 1:
                case 3: {
                    this.nestedScroll(modifier._nestedScroll_0_0value);
                    break;
                }
                default: {
                    this.nestedScroll((undefined as NestedScrollOptions | NestedScrollOptionsExt | undefined));
                }
            }
        }
        if (flagArray[95] != 0) {
            switch (flagArray[95]) {
                case 1:
                case 3: {
                    this.enableNativeEmbedMode(modifier._enableNativeEmbedMode_0_0value);
                    break;
                }
                default: {
                    this.enableNativeEmbedMode((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[96] != 0) {
            switch (flagArray[96]) {
                case 1:
                case 3: {
                    this.onNativeEmbedLifecycleChange(modifier._onNativeEmbedLifecycleChange_0_0value);
                    break;
                }
                default: {
                    this.onNativeEmbedLifecycleChange((undefined as ((event: NativeEmbedDataInfo) => void) | undefined));
                }
            }
        }
        if (flagArray[97] != 0) {
            switch (flagArray[97]) {
                case 1:
                case 3: {
                    this.onNativeEmbedVisibilityChange(modifier._onNativeEmbedVisibilityChange_0_0value);
                    break;
                }
                default: {
                    this.onNativeEmbedVisibilityChange((undefined as OnNativeEmbedVisibilityChangeCallback | undefined));
                }
            }
        }
        if (flagArray[98] != 0) {
            switch (flagArray[98]) {
                case 1:
                case 3: {
                    this.onNativeEmbedGestureEvent(modifier._onNativeEmbedGestureEvent_0_0value);
                    break;
                }
                default: {
                    this.onNativeEmbedGestureEvent((undefined as ((event: NativeEmbedTouchInfo) => void) | undefined));
                }
            }
        }
        if (flagArray[99] != 0) {
            switch (flagArray[99]) {
                case 1:
                case 3: {
                    this.copyOptions(modifier._copyOptions_0_0value);
                    break;
                }
                default: {
                    this.copyOptions((undefined as CopyOptions | undefined));
                }
            }
        }
    }
    mergeModifier5(modifier: WebModifier, flagArray: Uint8Array): void {
        if (flagArray[100] != 0) {
            switch (flagArray[100]) {
                case 1:
                case 3: {
                    this.onOverrideUrlLoading(modifier._onOverrideUrlLoading_0_0value);
                    break;
                }
                default: {
                    this.onOverrideUrlLoading((undefined as OnOverrideUrlLoadingCallback | undefined));
                }
            }
        }
        if (flagArray[101] != 0) {
            switch (flagArray[101]) {
                case 1:
                case 3: {
                    this.textAutosizing(modifier._textAutosizing_0_0value);
                    break;
                }
                default: {
                    this.textAutosizing((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[102] != 0) {
            switch (flagArray[102]) {
                case 1:
                case 3: {
                    this.enableNativeMediaPlayer(modifier._enableNativeMediaPlayer_0_0value);
                    break;
                }
                default: {
                    this.enableNativeMediaPlayer((undefined as NativeMediaPlayerConfig | undefined));
                }
            }
        }
        if (flagArray[103] != 0) {
            switch (flagArray[103]) {
                case 1:
                case 3: {
                    this.onRenderProcessNotResponding(modifier._onRenderProcessNotResponding_0_0value);
                    break;
                }
                default: {
                    this.onRenderProcessNotResponding((undefined as OnRenderProcessNotRespondingCallback | undefined));
                }
            }
        }
        if (flagArray[104] != 0) {
            switch (flagArray[104]) {
                case 1:
                case 3: {
                    this.onRenderProcessResponding(modifier._onRenderProcessResponding_0_0value);
                    break;
                }
                default: {
                    this.onRenderProcessResponding((undefined as OnRenderProcessRespondingCallback | undefined));
                }
            }
        }
        if (flagArray[105] != 0) {
            switch (flagArray[105]) {
                case 1:
                case 3: {
                    this.onViewportFitChanged(modifier._onViewportFitChanged_0_0value);
                    break;
                }
                default: {
                    this.onViewportFitChanged((undefined as OnViewportFitChangedCallback | undefined));
                }
            }
        }
        if (flagArray[106] != 0) {
            switch (flagArray[106]) {
                case 1:
                case 3: {
                    this.onInterceptKeyboardAttach(modifier._onInterceptKeyboardAttach_0_0value);
                    break;
                }
                default: {
                    this.onInterceptKeyboardAttach((undefined as WebKeyboardCallback | undefined));
                }
            }
        }
        if (flagArray[107] != 0) {
            switch (flagArray[107]) {
                case 1:
                case 3: {
                    this.onAdsBlocked(modifier._onAdsBlocked_0_0value);
                    break;
                }
                default: {
                    this.onAdsBlocked((undefined as OnAdsBlockedCallback | undefined));
                }
            }
        }
        if (flagArray[108] != 0) {
            switch (flagArray[108]) {
                case 1:
                case 3: {
                    this.keyboardAvoidMode(modifier._keyboardAvoidMode_0_0value);
                    break;
                }
                default: {
                    this.keyboardAvoidMode((undefined as WebKeyboardAvoidMode | undefined));
                }
            }
        }
        if (flagArray[109] != 0) {
            switch (flagArray[109]) {
                case 1:
                case 3: {
                    this.editMenuOptions(modifier._editMenuOptions_0_0value);
                    break;
                }
                default: {
                    this.editMenuOptions((undefined as EditMenuOptions | undefined));
                }
            }
        }
        if (flagArray[110] != 0) {
            switch (flagArray[110]) {
                case 1:
                case 3: {
                    this.enableHapticFeedback(modifier._enableHapticFeedback_0_0value);
                    break;
                }
                default: {
                    this.enableHapticFeedback((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[111] != 0) {
            switch (flagArray[111]) {
                case 1:
                case 3: {
                    this.enableFollowSystemFontWeight(modifier._enableFollowSystemFontWeight_0_0value);
                    break;
                }
                default: {
                    this.enableFollowSystemFontWeight((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[112] != 0) {
            switch (flagArray[112]) {
                case 1:
                case 3: {
                    this.enableWebAVSession(modifier._enableWebAVSession_0_0value);
                    break;
                }
                default: {
                    this.enableWebAVSession((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[113] != 0) {
            switch (flagArray[113]) {
                case 1:
                case 3: {
                    this.optimizeParserBudget(modifier._optimizeParserBudget_0_0value);
                    break;
                }
                default: {
                    this.optimizeParserBudget((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[114] != 0) {
            switch (flagArray[114]) {
                case 1:
                case 3: {
                    this.runJavaScriptOnDocumentStart(modifier._runJavaScriptOnDocumentStart_0_0value);
                    break;
                }
                default: {
                    this.runJavaScriptOnDocumentStart((undefined as Array<ScriptItem> | undefined));
                }
            }
        }
        if (flagArray[115] != 0) {
            switch (flagArray[115]) {
                case 1:
                case 3: {
                    this.runJavaScriptOnDocumentEnd(modifier._runJavaScriptOnDocumentEnd_0_0value);
                    break;
                }
                default: {
                    this.runJavaScriptOnDocumentEnd((undefined as Array<ScriptItem> | undefined));
                }
            }
        }
        if (flagArray[116] != 0) {
            switch (flagArray[116]) {
                case 1:
                case 3: {
                    this.runJavaScriptOnHeadEnd(modifier._runJavaScriptOnHeadEnd_0_0value);
                    break;
                }
                default: {
                    this.runJavaScriptOnHeadEnd((undefined as Array<ScriptItem> | undefined));
                }
            }
        }
        if (flagArray[117] != 0) {
            switch (flagArray[117]) {
                case 1:
                case 3: {
                    this.nativeEmbedOptions(modifier._nativeEmbedOptions_0_0value);
                    break;
                }
                default: {
                    this.nativeEmbedOptions((undefined as EmbedOptions | undefined));
                }
            }
        }
        if (flagArray[118] != 0) {
            switch (flagArray[118]) {
                case 1:
                case 3: {
                    this.registerNativeEmbedRule(modifier._registerNativeEmbedRule_0_0value, modifier._registerNativeEmbedRule_0_1value);
                    break;
                }
                default: {
                    this.registerNativeEmbedRule((undefined as string | undefined), (undefined as string | undefined));
                }
            }
        }
        if (flagArray[119] != 0) {
            switch (flagArray[119]) {
                case 1:
                case 3: {
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
        if (((this._flagArray[0]) == (0)) || ((this._javaScriptAccess_0_0value) !== (value))) {
            this._flagArray[0] = 1
            this._javaScriptAccess_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[0] = 3
        }
        return this
    }
    fileAccess(value: boolean | undefined): this {
        if (((this._flagArray[1]) == (0)) || ((this._fileAccess_0_0value) !== (value))) {
            this._flagArray[1] = 1
            this._fileAccess_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[1] = 3
        }
        return this
    }
    onlineImageAccess(value: boolean | undefined): this {
        if (((this._flagArray[2]) == (0)) || ((this._onlineImageAccess_0_0value) !== (value))) {
            this._flagArray[2] = 1
            this._onlineImageAccess_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[2] = 3
        }
        return this
    }
    domStorageAccess(value: boolean | undefined): this {
        if (((this._flagArray[3]) == (0)) || ((this._domStorageAccess_0_0value) !== (value))) {
            this._flagArray[3] = 1
            this._domStorageAccess_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[3] = 3
        }
        return this
    }
    imageAccess(value: boolean | undefined): this {
        if (((this._flagArray[4]) == (0)) || ((this._imageAccess_0_0value) !== (value))) {
            this._flagArray[4] = 1
            this._imageAccess_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[4] = 3
        }
        return this
    }
    mixedMode(value: MixedMode | undefined): this {
        if (((this._flagArray[5]) == (0)) || (true)) {
            this._flagArray[5] = 1
            this._mixedMode_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[5] = 3
        }
        return this
    }
    zoomAccess(value: boolean | undefined): this {
        if (((this._flagArray[6]) == (0)) || ((this._zoomAccess_0_0value) !== (value))) {
            this._flagArray[6] = 1
            this._zoomAccess_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[6] = 3
        }
        return this
    }
    geolocationAccess(value: boolean | undefined): this {
        if (((this._flagArray[7]) == (0)) || ((this._geolocationAccess_0_0value) !== (value))) {
            this._flagArray[7] = 1
            this._geolocationAccess_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[7] = 3
        }
        return this
    }
    javaScriptProxy(value: JavaScriptProxy | undefined): this {
        if (((this._flagArray[8]) == (0)) || (true)) {
            this._flagArray[8] = 1
            this._javaScriptProxy_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[8] = 3
        }
        return this
    }
    cacheMode(value: CacheMode | undefined): this {
        if (((this._flagArray[9]) == (0)) || (true)) {
            this._flagArray[9] = 1
            this._cacheMode_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[9] = 3
        }
        return this
    }
    darkMode(value: WebDarkMode | undefined): this {
        if (((this._flagArray[10]) == (0)) || (true)) {
            this._flagArray[10] = 1
            this._darkMode_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[10] = 3
        }
        return this
    }
    forceDarkAccess(value: boolean | undefined): this {
        if (((this._flagArray[11]) == (0)) || ((this._forceDarkAccess_0_0value) !== (value))) {
            this._flagArray[11] = 1
            this._forceDarkAccess_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[11] = 3
        }
        return this
    }
    mediaOptions(value: WebMediaOptions | undefined): this {
        if (((this._flagArray[12]) == (0)) || (true)) {
            this._flagArray[12] = 1
            this._mediaOptions_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[12] = 3
        }
        return this
    }
    overviewModeAccess(value: boolean | undefined): this {
        if (((this._flagArray[13]) == (0)) || ((this._overviewModeAccess_0_0value) !== (value))) {
            this._flagArray[13] = 1
            this._overviewModeAccess_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[13] = 3
        }
        return this
    }
    overScrollMode(value: OverScrollMode | undefined): this {
        if (((this._flagArray[14]) == (0)) || (true)) {
            this._flagArray[14] = 1
            this._overScrollMode_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[14] = 3
        }
        return this
    }
    blurOnKeyboardHideMode(value: BlurOnKeyboardHideMode | undefined): this {
        if (((this._flagArray[15]) == (0)) || (true)) {
            this._flagArray[15] = 1
            this._blurOnKeyboardHideMode_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[15] = 3
        }
        return this
    }
    textZoomRatio(value: int32 | undefined): this {
        if (((this._flagArray[16]) == (0)) || ((this._textZoomRatio_0_0value) !== (value))) {
            this._flagArray[16] = 1
            this._textZoomRatio_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[16] = 3
        }
        return this
    }
    databaseAccess(value: boolean | undefined): this {
        if (((this._flagArray[17]) == (0)) || ((this._databaseAccess_0_0value) !== (value))) {
            this._flagArray[17] = 1
            this._databaseAccess_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[17] = 3
        }
        return this
    }
    initialScale(value: double | undefined): this {
        if (((this._flagArray[18]) == (0)) || ((this._initialScale_0_0value) !== (value))) {
            this._flagArray[18] = 1
            this._initialScale_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[18] = 3
        }
        return this
    }
    metaViewport(value: boolean | undefined): this {
        if (((this._flagArray[19]) == (0)) || ((this._metaViewport_0_0value) !== (value))) {
            this._flagArray[19] = 1
            this._metaViewport_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[19] = 3
        }
        return this
    }
    onPageBegin(value: arkui_component_common_Callback<OnPageBeginEvent, void> | undefined): this {
        if (((this._flagArray[20]) == (0)) || (true)) {
            this._flagArray[20] = 1
            this._onPageBegin_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[20] = 3
        }
        return this
    }
    onPageEnd(value: arkui_component_common_Callback<OnPageEndEvent, void> | undefined): this {
        if (((this._flagArray[21]) == (0)) || (true)) {
            this._flagArray[21] = 1
            this._onPageEnd_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[21] = 3
        }
        return this
    }
    onLoadStarted(value: arkui_component_common_Callback<OnLoadStartedEvent, void> | undefined): this {
        if (((this._flagArray[22]) == (0)) || (true)) {
            this._flagArray[22] = 1
            this._onLoadStarted_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[22] = 3
        }
        return this
    }
    onLoadFinished(value: arkui_component_common_Callback<OnLoadFinishedEvent, void> | undefined): this {
        if (((this._flagArray[23]) == (0)) || (true)) {
            this._flagArray[23] = 1
            this._onLoadFinished_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[23] = 3
        }
        return this
    }
    onProgressChange(value: arkui_component_common_Callback<OnProgressChangeEvent, void> | undefined): this {
        if (((this._flagArray[24]) == (0)) || (true)) {
            this._flagArray[24] = 1
            this._onProgressChange_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[24] = 3
        }
        return this
    }
    onTitleReceive(value: arkui_component_common_Callback<OnTitleReceiveEvent, void> | undefined): this {
        if (((this._flagArray[25]) == (0)) || (true)) {
            this._flagArray[25] = 1
            this._onTitleReceive_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[25] = 3
        }
        return this
    }
    onGeolocationHide(value: (() => void) | undefined): this {
        if (((this._flagArray[26]) == (0)) || (true)) {
            this._flagArray[26] = 1
            this._onGeolocationHide_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[26] = 3
        }
        return this
    }
    onGeolocationShow(value: arkui_component_common_Callback<OnGeolocationShowEvent, void> | undefined): this {
        if (((this._flagArray[27]) == (0)) || (true)) {
            this._flagArray[27] = 1
            this._onGeolocationShow_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[27] = 3
        }
        return this
    }
    onRequestSelected(value: (() => void) | undefined): this {
        if (((this._flagArray[28]) == (0)) || (true)) {
            this._flagArray[28] = 1
            this._onRequestSelected_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[28] = 3
        }
        return this
    }
    onAlert(value: arkui_component_common_Callback<OnAlertEvent, boolean> | undefined): this {
        if (((this._flagArray[29]) == (0)) || (true)) {
            this._flagArray[29] = 1
            this._onAlert_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[29] = 3
        }
        return this
    }
    onBeforeUnload(value: arkui_component_common_Callback<OnBeforeUnloadEvent, boolean> | undefined): this {
        if (((this._flagArray[30]) == (0)) || (true)) {
            this._flagArray[30] = 1
            this._onBeforeUnload_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[30] = 3
        }
        return this
    }
    onConfirm(value: arkui_component_common_Callback<OnConfirmEvent, boolean> | undefined): this {
        if (((this._flagArray[31]) == (0)) || (true)) {
            this._flagArray[31] = 1
            this._onConfirm_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[31] = 3
        }
        return this
    }
    onPrompt(value: arkui_component_common_Callback<OnPromptEvent, boolean> | undefined): this {
        if (((this._flagArray[32]) == (0)) || (true)) {
            this._flagArray[32] = 1
            this._onPrompt_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[32] = 3
        }
        return this
    }
    onConsole(value: arkui_component_common_Callback<OnConsoleEvent, boolean> | undefined): this {
        if (((this._flagArray[33]) == (0)) || (true)) {
            this._flagArray[33] = 1
            this._onConsole_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[33] = 3
        }
        return this
    }
    onErrorReceive(value: arkui_component_common_Callback<OnErrorReceiveEvent, void> | undefined): this {
        if (((this._flagArray[34]) == (0)) || (true)) {
            this._flagArray[34] = 1
            this._onErrorReceive_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[34] = 3
        }
        return this
    }
    onHttpErrorReceive(value: arkui_component_common_Callback<OnHttpErrorReceiveEvent, void> | undefined): this {
        if (((this._flagArray[35]) == (0)) || (true)) {
            this._flagArray[35] = 1
            this._onHttpErrorReceive_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[35] = 3
        }
        return this
    }
    onDownloadStart(value: arkui_component_common_Callback<OnDownloadStartEvent, void> | undefined): this {
        if (((this._flagArray[36]) == (0)) || (true)) {
            this._flagArray[36] = 1
            this._onDownloadStart_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[36] = 3
        }
        return this
    }
    onRefreshAccessedHistory(value: arkui_component_common_Callback<OnRefreshAccessedHistoryEvent, void> | undefined): this {
        if (((this._flagArray[37]) == (0)) || (true)) {
            this._flagArray[37] = 1
            this._onRefreshAccessedHistory_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[37] = 3
        }
        return this
    }
    onRenderExited(value: arkui_component_common_Callback<OnRenderExitedEvent, void> | undefined): this {
        if (((this._flagArray[38]) == (0)) || (true)) {
            this._flagArray[38] = 1
            this._onRenderExited_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[38] = 3
        }
        return this
    }
    onShowFileSelector(value: arkui_component_common_Callback<OnShowFileSelectorEvent, boolean> | undefined): this {
        if (((this._flagArray[39]) == (0)) || (true)) {
            this._flagArray[39] = 1
            this._onShowFileSelector_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[39] = 3
        }
        return this
    }
    onResourceLoad(value: arkui_component_common_Callback<OnResourceLoadEvent, void> | undefined): this {
        if (((this._flagArray[40]) == (0)) || (true)) {
            this._flagArray[40] = 1
            this._onResourceLoad_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[40] = 3
        }
        return this
    }
    onFullScreenExit(value: (() => void) | undefined): this {
        if (((this._flagArray[41]) == (0)) || (true)) {
            this._flagArray[41] = 1
            this._onFullScreenExit_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[41] = 3
        }
        return this
    }
    onFullScreenEnter(value: OnFullScreenEnterCallback | undefined): this {
        if (((this._flagArray[42]) == (0)) || (true)) {
            this._flagArray[42] = 1
            this._onFullScreenEnter_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[42] = 3
        }
        return this
    }
    onScaleChange(value: arkui_component_common_Callback<OnScaleChangeEvent, void> | undefined): this {
        if (((this._flagArray[43]) == (0)) || (true)) {
            this._flagArray[43] = 1
            this._onScaleChange_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[43] = 3
        }
        return this
    }
    onHttpAuthRequest(value: arkui_component_common_Callback<OnHttpAuthRequestEvent, boolean> | undefined): this {
        if (((this._flagArray[44]) == (0)) || (true)) {
            this._flagArray[44] = 1
            this._onHttpAuthRequest_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[44] = 3
        }
        return this
    }
    onInterceptRequest(value: arkui_component_common_Callback<OnInterceptRequestEvent, WebResourceResponse | null> | undefined): this {
        if (((this._flagArray[45]) == (0)) || (true)) {
            this._flagArray[45] = 1
            this._onInterceptRequest_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[45] = 3
        }
        return this
    }
    onPermissionRequest(value: arkui_component_common_Callback<OnPermissionRequestEvent, void> | undefined): this {
        if (((this._flagArray[46]) == (0)) || (true)) {
            this._flagArray[46] = 1
            this._onPermissionRequest_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[46] = 3
        }
        return this
    }
    onScreenCaptureRequest(value: arkui_component_common_Callback<OnScreenCaptureRequestEvent, void> | undefined): this {
        if (((this._flagArray[47]) == (0)) || (true)) {
            this._flagArray[47] = 1
            this._onScreenCaptureRequest_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[47] = 3
        }
        return this
    }
    onContextMenuShow(value: arkui_component_common_Callback<OnContextMenuShowEvent, boolean> | undefined): this {
        if (((this._flagArray[48]) == (0)) || (true)) {
            this._flagArray[48] = 1
            this._onContextMenuShow_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[48] = 3
        }
        return this
    }
    onContextMenuHide(value: OnContextMenuHideCallback | undefined): this {
        if (((this._flagArray[49]) == (0)) || (true)) {
            this._flagArray[49] = 1
            this._onContextMenuHide_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[49] = 3
        }
        return this
    }
    mediaPlayGestureAccess(value: boolean | undefined): this {
        if (((this._flagArray[50]) == (0)) || ((this._mediaPlayGestureAccess_0_0value) !== (value))) {
            this._flagArray[50] = 1
            this._mediaPlayGestureAccess_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[50] = 3
        }
        return this
    }
    onSearchResultReceive(value: arkui_component_common_Callback<OnSearchResultReceiveEvent, void> | undefined): this {
        if (((this._flagArray[51]) == (0)) || (true)) {
            this._flagArray[51] = 1
            this._onSearchResultReceive_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[51] = 3
        }
        return this
    }
    onScroll(value: arkui_component_common_Callback<OnScrollEvent, void> | undefined): this {
        if (((this._flagArray[52]) == (0)) || (true)) {
            this._flagArray[52] = 1
            this._onScroll_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[52] = 3
        }
        return this
    }
    onSslErrorEventReceive(value: arkui_component_common_Callback<OnSslErrorEventReceiveEvent, void> | undefined): this {
        if (((this._flagArray[53]) == (0)) || (true)) {
            this._flagArray[53] = 1
            this._onSslErrorEventReceive_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[53] = 3
        }
        return this
    }
    onSslErrorEvent(value: OnSslErrorEventCallback | undefined): this {
        if (((this._flagArray[54]) == (0)) || (true)) {
            this._flagArray[54] = 1
            this._onSslErrorEvent_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[54] = 3
        }
        return this
    }
    onClientAuthenticationRequest(value: arkui_component_common_Callback<OnClientAuthenticationEvent, void> | undefined): this {
        if (((this._flagArray[55]) == (0)) || (true)) {
            this._flagArray[55] = 1
            this._onClientAuthenticationRequest_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[55] = 3
        }
        return this
    }
    onWindowNew(value: arkui_component_common_Callback<OnWindowNewEvent, void> | undefined): this {
        if (((this._flagArray[56]) == (0)) || (true)) {
            this._flagArray[56] = 1
            this._onWindowNew_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[56] = 3
        }
        return this
    }
    onWindowExit(value: (() => void) | undefined): this {
        if (((this._flagArray[57]) == (0)) || (true)) {
            this._flagArray[57] = 1
            this._onWindowExit_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[57] = 3
        }
        return this
    }
    multiWindowAccess(value: boolean | undefined): this {
        if (((this._flagArray[58]) == (0)) || ((this._multiWindowAccess_0_0value) !== (value))) {
            this._flagArray[58] = 1
            this._multiWindowAccess_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[58] = 3
        }
        return this
    }
    onInterceptKeyEvent(value: ((event: KeyEvent) => boolean) | undefined): this {
        if (((this._flagArray[59]) == (0)) || (true)) {
            this._flagArray[59] = 1
            this._onInterceptKeyEvent_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[59] = 3
        }
        return this
    }
    webStandardFont(value: string | undefined): this {
        if (((this._flagArray[60]) == (0)) || ((this._webStandardFont_0_0value) !== (value))) {
            this._flagArray[60] = 1
            this._webStandardFont_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[60] = 3
        }
        return this
    }
    webSerifFont(value: string | undefined): this {
        if (((this._flagArray[61]) == (0)) || ((this._webSerifFont_0_0value) !== (value))) {
            this._flagArray[61] = 1
            this._webSerifFont_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[61] = 3
        }
        return this
    }
    webSansSerifFont(value: string | undefined): this {
        if (((this._flagArray[62]) == (0)) || ((this._webSansSerifFont_0_0value) !== (value))) {
            this._flagArray[62] = 1
            this._webSansSerifFont_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[62] = 3
        }
        return this
    }
    webFixedFont(value: string | undefined): this {
        if (((this._flagArray[63]) == (0)) || ((this._webFixedFont_0_0value) !== (value))) {
            this._flagArray[63] = 1
            this._webFixedFont_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[63] = 3
        }
        return this
    }
    webFantasyFont(value: string | undefined): this {
        if (((this._flagArray[64]) == (0)) || ((this._webFantasyFont_0_0value) !== (value))) {
            this._flagArray[64] = 1
            this._webFantasyFont_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[64] = 3
        }
        return this
    }
    webCursiveFont(value: string | undefined): this {
        if (((this._flagArray[65]) == (0)) || ((this._webCursiveFont_0_0value) !== (value))) {
            this._flagArray[65] = 1
            this._webCursiveFont_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[65] = 3
        }
        return this
    }
    defaultFixedFontSize(value: int32 | undefined): this {
        if (((this._flagArray[66]) == (0)) || ((this._defaultFixedFontSize_0_0value) !== (value))) {
            this._flagArray[66] = 1
            this._defaultFixedFontSize_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[66] = 3
        }
        return this
    }
    defaultFontSize(value: int32 | undefined): this {
        if (((this._flagArray[67]) == (0)) || ((this._defaultFontSize_0_0value) !== (value))) {
            this._flagArray[67] = 1
            this._defaultFontSize_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[67] = 3
        }
        return this
    }
    minFontSize(value: int32 | undefined): this {
        if (((this._flagArray[68]) == (0)) || ((this._minFontSize_0_0value) !== (value))) {
            this._flagArray[68] = 1
            this._minFontSize_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[68] = 3
        }
        return this
    }
    minLogicalFontSize(value: int32 | undefined): this {
        if (((this._flagArray[69]) == (0)) || ((this._minLogicalFontSize_0_0value) !== (value))) {
            this._flagArray[69] = 1
            this._minLogicalFontSize_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[69] = 3
        }
        return this
    }
    defaultTextEncodingFormat(value: string | undefined): this {
        if (((this._flagArray[70]) == (0)) || ((this._defaultTextEncodingFormat_0_0value) !== (value))) {
            this._flagArray[70] = 1
            this._defaultTextEncodingFormat_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[70] = 3
        }
        return this
    }
    forceDisplayScrollBar(value: boolean | undefined): this {
        if (((this._flagArray[71]) == (0)) || ((this._forceDisplayScrollBar_0_0value) !== (value))) {
            this._flagArray[71] = 1
            this._forceDisplayScrollBar_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[71] = 3
        }
        return this
    }
    blockNetwork(value: boolean | undefined): this {
        if (((this._flagArray[72]) == (0)) || ((this._blockNetwork_0_0value) !== (value))) {
            this._flagArray[72] = 1
            this._blockNetwork_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[72] = 3
        }
        return this
    }
    horizontalScrollBarAccess(value: boolean | undefined): this {
        if (((this._flagArray[73]) == (0)) || ((this._horizontalScrollBarAccess_0_0value) !== (value))) {
            this._flagArray[73] = 1
            this._horizontalScrollBarAccess_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[73] = 3
        }
        return this
    }
    verticalScrollBarAccess(value: boolean | undefined): this {
        if (((this._flagArray[74]) == (0)) || ((this._verticalScrollBarAccess_0_0value) !== (value))) {
            this._flagArray[74] = 1
            this._verticalScrollBarAccess_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[74] = 3
        }
        return this
    }
    onTouchIconUrlReceived(value: arkui_component_common_Callback<OnTouchIconUrlReceivedEvent, void> | undefined): this {
        if (((this._flagArray[75]) == (0)) || (true)) {
            this._flagArray[75] = 1
            this._onTouchIconUrlReceived_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[75] = 3
        }
        return this
    }
    onFaviconReceived(value: arkui_component_common_Callback<OnFaviconReceivedEvent, void> | undefined): this {
        if (((this._flagArray[76]) == (0)) || (true)) {
            this._flagArray[76] = 1
            this._onFaviconReceived_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[76] = 3
        }
        return this
    }
    onPageVisible(value: arkui_component_common_Callback<OnPageVisibleEvent, void> | undefined): this {
        if (((this._flagArray[77]) == (0)) || (true)) {
            this._flagArray[77] = 1
            this._onPageVisible_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[77] = 3
        }
        return this
    }
    onDataResubmitted(value: arkui_component_common_Callback<OnDataResubmittedEvent, void> | undefined): this {
        if (((this._flagArray[78]) == (0)) || (true)) {
            this._flagArray[78] = 1
            this._onDataResubmitted_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[78] = 3
        }
        return this
    }
    pinchSmooth(value: boolean | undefined): this {
        if (((this._flagArray[79]) == (0)) || ((this._pinchSmooth_0_0value) !== (value))) {
            this._flagArray[79] = 1
            this._pinchSmooth_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[79] = 3
        }
        return this
    }
    allowWindowOpenMethod(value: boolean | undefined): this {
        if (((this._flagArray[80]) == (0)) || ((this._allowWindowOpenMethod_0_0value) !== (value))) {
            this._flagArray[80] = 1
            this._allowWindowOpenMethod_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[80] = 3
        }
        return this
    }
    onAudioStateChanged(value: arkui_component_common_Callback<OnAudioStateChangedEvent, void> | undefined): this {
        if (((this._flagArray[81]) == (0)) || (true)) {
            this._flagArray[81] = 1
            this._onAudioStateChanged_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[81] = 3
        }
        return this
    }
    onFirstContentfulPaint(value: arkui_component_common_Callback<OnFirstContentfulPaintEvent, void> | undefined): this {
        if (((this._flagArray[82]) == (0)) || (true)) {
            this._flagArray[82] = 1
            this._onFirstContentfulPaint_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[82] = 3
        }
        return this
    }
    onFirstMeaningfulPaint(value: OnFirstMeaningfulPaintCallback | undefined): this {
        if (((this._flagArray[83]) == (0)) || (true)) {
            this._flagArray[83] = 1
            this._onFirstMeaningfulPaint_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[83] = 3
        }
        return this
    }
    onLargestContentfulPaint(value: OnLargestContentfulPaintCallback | undefined): this {
        if (((this._flagArray[84]) == (0)) || (true)) {
            this._flagArray[84] = 1
            this._onLargestContentfulPaint_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[84] = 3
        }
        return this
    }
    onLoadIntercept(value: arkui_component_common_Callback<OnLoadInterceptEvent, boolean> | undefined): this {
        if (((this._flagArray[85]) == (0)) || (true)) {
            this._flagArray[85] = 1
            this._onLoadIntercept_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[85] = 3
        }
        return this
    }
    onControllerAttached(value: (() => void) | undefined): this {
        if (((this._flagArray[86]) == (0)) || (true)) {
            this._flagArray[86] = 1
            this._onControllerAttached_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[86] = 3
        }
        return this
    }
    onOverScroll(value: arkui_component_common_Callback<OnOverScrollEvent, void> | undefined): this {
        if (((this._flagArray[87]) == (0)) || (true)) {
            this._flagArray[87] = 1
            this._onOverScroll_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[87] = 3
        }
        return this
    }
    onSafeBrowsingCheckResult(value: OnSafeBrowsingCheckResultCallback | undefined): this {
        if (((this._flagArray[88]) == (0)) || (true)) {
            this._flagArray[88] = 1
            this._onSafeBrowsingCheckResult_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[88] = 3
        }
        return this
    }
    onNavigationEntryCommitted(value: OnNavigationEntryCommittedCallback | undefined): this {
        if (((this._flagArray[89]) == (0)) || (true)) {
            this._flagArray[89] = 1
            this._onNavigationEntryCommitted_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[89] = 3
        }
        return this
    }
    onIntelligentTrackingPreventionResult(value: OnIntelligentTrackingPreventionCallback | undefined): this {
        if (((this._flagArray[90]) == (0)) || (true)) {
            this._flagArray[90] = 1
            this._onIntelligentTrackingPreventionResult_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[90] = 3
        }
        return this
    }
    javaScriptOnDocumentStart(value: Array<ScriptItem> | undefined): this {
        if (((this._flagArray[91]) == (0)) || (true)) {
            this._flagArray[91] = 1
            this._javaScriptOnDocumentStart_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[91] = 3
        }
        return this
    }
    javaScriptOnDocumentEnd(value: Array<ScriptItem> | undefined): this {
        if (((this._flagArray[92]) == (0)) || (true)) {
            this._flagArray[92] = 1
            this._javaScriptOnDocumentEnd_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[92] = 3
        }
        return this
    }
    layoutMode(value: WebLayoutMode | undefined): this {
        if (((this._flagArray[93]) == (0)) || (true)) {
            this._flagArray[93] = 1
            this._layoutMode_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[93] = 3
        }
        return this
    }
    nestedScroll(value: NestedScrollOptions | NestedScrollOptionsExt | undefined): this {
        if (((this._flagArray[94]) == (0)) || (true)) {
            this._flagArray[94] = 1
            this._nestedScroll_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[94] = 3
        }
        return this
    }
    enableNativeEmbedMode(value: boolean | undefined): this {
        if (((this._flagArray[95]) == (0)) || ((this._enableNativeEmbedMode_0_0value) !== (value))) {
            this._flagArray[95] = 1
            this._enableNativeEmbedMode_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[95] = 3
        }
        return this
    }
    onNativeEmbedLifecycleChange(value: ((event: NativeEmbedDataInfo) => void) | undefined): this {
        if (((this._flagArray[96]) == (0)) || (true)) {
            this._flagArray[96] = 1
            this._onNativeEmbedLifecycleChange_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[96] = 3
        }
        return this
    }
    onNativeEmbedVisibilityChange(value: OnNativeEmbedVisibilityChangeCallback | undefined): this {
        if (((this._flagArray[97]) == (0)) || (true)) {
            this._flagArray[97] = 1
            this._onNativeEmbedVisibilityChange_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[97] = 3
        }
        return this
    }
    onNativeEmbedGestureEvent(value: ((event: NativeEmbedTouchInfo) => void) | undefined): this {
        if (((this._flagArray[98]) == (0)) || (true)) {
            this._flagArray[98] = 1
            this._onNativeEmbedGestureEvent_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[98] = 3
        }
        return this
    }
    copyOptions(value: CopyOptions | undefined): this {
        if (((this._flagArray[99]) == (0)) || (true)) {
            this._flagArray[99] = 1
            this._copyOptions_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[99] = 3
        }
        return this
    }
    onOverrideUrlLoading(value: OnOverrideUrlLoadingCallback | undefined): this {
        if (((this._flagArray[100]) == (0)) || (true)) {
            this._flagArray[100] = 1
            this._onOverrideUrlLoading_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[100] = 3
        }
        return this
    }
    textAutosizing(value: boolean | undefined): this {
        if (((this._flagArray[101]) == (0)) || ((this._textAutosizing_0_0value) !== (value))) {
            this._flagArray[101] = 1
            this._textAutosizing_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[101] = 3
        }
        return this
    }
    enableNativeMediaPlayer(value: NativeMediaPlayerConfig | undefined): this {
        if (((this._flagArray[102]) == (0)) || (true)) {
            this._flagArray[102] = 1
            this._enableNativeMediaPlayer_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[102] = 3
        }
        return this
    }
    onRenderProcessNotResponding(value: OnRenderProcessNotRespondingCallback | undefined): this {
        if (((this._flagArray[103]) == (0)) || (true)) {
            this._flagArray[103] = 1
            this._onRenderProcessNotResponding_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[103] = 3
        }
        return this
    }
    onRenderProcessResponding(value: OnRenderProcessRespondingCallback | undefined): this {
        if (((this._flagArray[104]) == (0)) || (true)) {
            this._flagArray[104] = 1
            this._onRenderProcessResponding_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[104] = 3
        }
        return this
    }
    onViewportFitChanged(value: OnViewportFitChangedCallback | undefined): this {
        if (((this._flagArray[105]) == (0)) || (true)) {
            this._flagArray[105] = 1
            this._onViewportFitChanged_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[105] = 3
        }
        return this
    }
    onInterceptKeyboardAttach(value: WebKeyboardCallback | undefined): this {
        if (((this._flagArray[106]) == (0)) || (true)) {
            this._flagArray[106] = 1
            this._onInterceptKeyboardAttach_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[106] = 3
        }
        return this
    }
    onAdsBlocked(value: OnAdsBlockedCallback | undefined): this {
        if (((this._flagArray[107]) == (0)) || (true)) {
            this._flagArray[107] = 1
            this._onAdsBlocked_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[107] = 3
        }
        return this
    }
    keyboardAvoidMode(value: WebKeyboardAvoidMode | undefined): this {
        if (((this._flagArray[108]) == (0)) || (true)) {
            this._flagArray[108] = 1
            this._keyboardAvoidMode_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[108] = 3
        }
        return this
    }
    editMenuOptions(value: EditMenuOptions | undefined): this {
        if (((this._flagArray[109]) == (0)) || (true)) {
            this._flagArray[109] = 1
            this._editMenuOptions_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[109] = 3
        }
        return this
    }
    enableHapticFeedback(value: boolean | undefined): this {
        if (((this._flagArray[110]) == (0)) || ((this._enableHapticFeedback_0_0value) !== (value))) {
            this._flagArray[110] = 1
            this._enableHapticFeedback_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[110] = 3
        }
        return this
    }
    enableFollowSystemFontWeight(value: boolean | undefined): this {
        if (((this._flagArray[111]) == (0)) || ((this._enableFollowSystemFontWeight_0_0value) !== (value))) {
            this._flagArray[111] = 1
            this._enableFollowSystemFontWeight_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[111] = 3
        }
        return this
    }
    enableWebAVSession(value: boolean | undefined): this {
        if (((this._flagArray[112]) == (0)) || ((this._enableWebAVSession_0_0value) !== (value))) {
            this._flagArray[112] = 1
            this._enableWebAVSession_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[112] = 3
        }
        return this
    }
    optimizeParserBudget(value: boolean | undefined): this {
        if (((this._flagArray[113]) == (0)) || ((this._optimizeParserBudget_0_0value) !== (value))) {
            this._flagArray[113] = 1
            this._optimizeParserBudget_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[113] = 3
        }
        return this
    }
    runJavaScriptOnDocumentStart(value: Array<ScriptItem> | undefined): this {
        if (((this._flagArray[114]) == (0)) || (true)) {
            this._flagArray[114] = 1
            this._runJavaScriptOnDocumentStart_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[114] = 3
        }
        return this
    }
    runJavaScriptOnDocumentEnd(value: Array<ScriptItem> | undefined): this {
        if (((this._flagArray[115]) == (0)) || (true)) {
            this._flagArray[115] = 1
            this._runJavaScriptOnDocumentEnd_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[115] = 3
        }
        return this
    }
    runJavaScriptOnHeadEnd(value: Array<ScriptItem> | undefined): this {
        if (((this._flagArray[116]) == (0)) || (true)) {
            this._flagArray[116] = 1
            this._runJavaScriptOnHeadEnd_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[116] = 3
        }
        return this
    }
    nativeEmbedOptions(value: EmbedOptions | undefined): this {
        if (((this._flagArray[117]) == (0)) || (true)) {
            this._flagArray[117] = 1
            this._nativeEmbedOptions_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[117] = 3
        }
        return this
    }
    registerNativeEmbedRule(tag: string | undefined, type: string | undefined): this {
        if (((this._flagArray[118]) == (0)) || ((this._registerNativeEmbedRule_0_0value) !== (tag)) || ((this._registerNativeEmbedRule_0_1value) !== (type))) {
            this._flagArray[118] = 1
            this._registerNativeEmbedRule_0_0value = tag
            this._registerNativeEmbedRule_0_1value = type
            this._state.fireChange()
        } else {
            this._flagArray[118] = 3
        }
        return this
    }
    bindSelectionMenu(elementType: WebElementType | undefined, content: CustomBuilder | undefined, responseType: WebResponseType | undefined, options?: SelectionMenuOptionsExt): this {
        if (((this._flagArray[119]) == (0)) || (true) || (true) || (true) || (true)) {
            this._flagArray[119] = 1
            this._bindSelectionMenu_0_0value = elementType
            this._bindSelectionMenu_0_1value = content
            this._bindSelectionMenu_0_2value = responseType
            this._bindSelectionMenu_0_3value = options
            this._state.fireChange()
        } else {
            this._flagArray[119] = 3
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<WebAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Not implemented')
    }
}
