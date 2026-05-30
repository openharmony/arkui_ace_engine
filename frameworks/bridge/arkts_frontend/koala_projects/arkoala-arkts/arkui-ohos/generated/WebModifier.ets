/*
 * Copyright (c) 2024-2026 Huawei Device Co., Ltd.
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
import { AttributeModifier } from '#handwritten'
import { AttributeUpdaterFlag } from './AttributeUpdaterFlag'
import { PeerNode } from './PeerNode'
import { ArkWebPeer, MixedMode, JavaScriptProxy, CacheMode, WebDarkMode, WebMediaOptions, OverScrollMode, BlurOnKeyboardHideMode, OnPageBeginEvent, OnPageEndEvent, OnLoadStartedEvent, OnLoadFinishedEvent, OnProgressChangeEvent, OnTitleReceiveEvent, OnGeolocationShowEvent, OnAlertEvent, OnBeforeUnloadEvent, OnConfirmEvent, OnPromptEvent, OnConsoleEvent, OnErrorReceiveEvent, OnHttpErrorReceiveEvent, OnDownloadStartEvent, OnRefreshAccessedHistoryEvent, OnRenderExitedEvent, OnShowFileSelectorEvent, OnResourceLoadEvent, OnFullScreenEnterCallback, FullScreenEnterEvent, OnScaleChangeEvent, OnHttpAuthRequestEvent, OnInterceptRequestEvent, WebResourceResponse, OnPermissionRequestEvent, OnScreenCaptureRequestEvent, OnContextMenuShowEvent, OnContextMenuHideCallback, OnSearchResultReceiveEvent, OnScrollEvent, OnSslErrorEventReceiveEvent, OnSslErrorEventCallback, SslErrorEvent, OnClientAuthenticationEvent, OnVerifyPinCallback, VerifyPinEvent, OnWindowNewEvent, OnWindowNewExtEvent, OnTouchIconUrlReceivedEvent, OnFaviconReceivedEvent, OnPageVisibleEvent, OnDataResubmittedEvent, OnAudioStateChangedEvent, OnFirstContentfulPaintEvent, OnFirstMeaningfulPaintCallback, FirstMeaningfulPaint, OnLargestContentfulPaintCallback, LargestContentfulPaint, OnLoadInterceptEvent, OnOverScrollEvent, OnPdfScrollEvent, OnPdfLoadEvent, OnSafeBrowsingCheckResultCallback, ThreatType, OnNavigationEntryCommittedCallback, LoadCommittedDetails, OnIntelligentTrackingPreventionCallback, IntelligentTrackingPreventionDetails, ScriptItem, WebLayoutMode, NestedScrollOptionsExt, NativeEmbedDataInfo, OnNativeEmbedVisibilityChangeCallback, NativeEmbedVisibilityInfo, NativeEmbedTouchInfo, MouseInfoCallback, NativeEmbedMouseInfo, OnOverrideUrlLoadingCallback, WebResourceRequest, OnOverrideErrorPageCallback, NativeMediaPlayerConfig, OnRenderProcessNotRespondingCallback, RenderProcessNotRespondingData, OnRenderProcessRespondingCallback, OnViewportFitChangedCallback, ViewportFit, WebKeyboardCallback, WebKeyboardCallbackInfo, OnAdsBlockedCallback, AdsBlockedDetails, WebKeyboardAvoidMode, EmbedOptions, WebBypassVsyncCondition, GestureFocusMode, OnNativeEmbedObjectParamChangeCallback, NativeEmbedParamDataInfo, WebRotateEffect, OnDetectBlankScreenCallback, BlankScreenDetectionEventInfo, BlankScreenDetectionConfig, OnFirstScreenPaintCallback, FirstScreenPaint, TextSelectionChangeCallback, OnCameraCaptureStateChangeCallback, CameraCaptureStateChangeInfo, OnMicrophoneCaptureStateChangeCallback, MicrophoneCaptureStateChangeInfo, ScrollbarLayoutPolicy, AISessionEvent, WebAttribute, WebKeyboardAppearanceMode, OnInputmethodAttachedCallback, WebElementType, WebResponseType, SelectionMenuOptionsExt, ScrollDirectionalLockType } from './component/web'
import { int32, int64 } from '@koalaui/common'
import { ModifierState } from './CommonModifier'
import { CommonMethod, Callback as arkui_component_common_Callback, KeyEvent, NestedScrollOptions } from './component/common'
import { CopyOptions } from './component/enums'
import { EditMenuOptions, TextDataDetectorConfig } from './component/textCommon'
import { VoidCallback } from './component/units'
import { CustomBuilder } from './component/builder'
export class WebModifier extends CommonMethodModifier implements WebAttribute,AttributeModifier<WebAttribute> {
    _Web_addr: ArrayBuffer = new ArrayBuffer(4096);
    _Web_flagArray: Uint8Array = new Uint8Array(this._Web_addr);
    constructor() {
        super();
        this._Web_flagArray.fill(0);
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: WebAttribute): void { }
    applyPressedAttribute(instance: WebAttribute): void { }
    applyFocusedAttribute(instance: WebAttribute): void { }
    applyDisabledAttribute(instance: WebAttribute): void { }
    applySelectedAttribute(instance: WebAttribute): void { }
    public _Web_javaScriptAccess_0_0value?: boolean | undefined
    public _Web_fileAccess_0_0value?: boolean | undefined
    public _Web_onlineImageAccess_0_0value?: boolean | undefined
    public _Web_domStorageAccess_0_0value?: boolean | undefined
    public _Web_imageAccess_0_0value?: boolean | undefined
    public _Web_mixedMode_0_0value?: MixedMode | undefined
    public _Web_zoomAccess_0_0value?: boolean | undefined
    public _Web_geolocationAccess_0_0value?: boolean | undefined
    public _Web_javaScriptProxy_0_0value?: JavaScriptProxy | undefined
    public _Web_cacheMode_0_0value?: CacheMode | undefined
    public _Web_darkMode_0_0value?: WebDarkMode | undefined
    public _Web_forceDarkAccess_0_0value?: boolean | undefined
    public _Web_mediaOptions_0_0value?: WebMediaOptions | undefined
    public _Web_overviewModeAccess_0_0value?: boolean | undefined
    public _Web_overScrollMode_0_0value?: OverScrollMode | undefined
    public _Web_blurOnKeyboardHideMode_0_0value?: BlurOnKeyboardHideMode | undefined
    public _Web_textZoomRatio_0_0value?: int32 | undefined
    public _Web_databaseAccess_0_0value?: boolean | undefined
    public _Web_initialScale_0_0value?: double | undefined
    public _Web_metaViewport_0_0value?: boolean | undefined
    public _Web_onPageBegin_0_0value?: arkui_component_common_Callback<OnPageBeginEvent, void> | undefined
    public _Web_onPageEnd_0_0value?: arkui_component_common_Callback<OnPageEndEvent, void> | undefined
    public _Web_onLoadStarted_0_0value?: arkui_component_common_Callback<OnLoadStartedEvent, void> | undefined
    public _Web_onLoadFinished_0_0value?: arkui_component_common_Callback<OnLoadFinishedEvent, void> | undefined
    public _Web_onProgressChange_0_0value?: arkui_component_common_Callback<OnProgressChangeEvent, void> | undefined
    public _Web_onTitleReceive_0_0value?: arkui_component_common_Callback<OnTitleReceiveEvent, void> | undefined
    public _Web_onGeolocationHide_0_0value?: (() => void) | undefined
    public _Web_onGeolocationShow_0_0value?: arkui_component_common_Callback<OnGeolocationShowEvent, void> | undefined
    public _Web_onRequestSelected_0_0value?: (() => void) | undefined
    public _Web_onAlert_0_0value?: arkui_component_common_Callback<OnAlertEvent, boolean> | undefined
    public _Web_onBeforeUnload_0_0value?: arkui_component_common_Callback<OnBeforeUnloadEvent, boolean> | undefined
    public _Web_onConfirm_0_0value?: arkui_component_common_Callback<OnConfirmEvent, boolean> | undefined
    public _Web_onPrompt_0_0value?: arkui_component_common_Callback<OnPromptEvent, boolean> | undefined
    public _Web_onConsole_0_0value?: arkui_component_common_Callback<OnConsoleEvent, boolean> | undefined
    public _Web_onErrorReceive_0_0value?: arkui_component_common_Callback<OnErrorReceiveEvent, void> | undefined
    public _Web_onHttpErrorReceive_0_0value?: arkui_component_common_Callback<OnHttpErrorReceiveEvent, void> | undefined
    public _Web_onDownloadStart_0_0value?: arkui_component_common_Callback<OnDownloadStartEvent, void> | undefined
    public _Web_onRefreshAccessedHistory_0_0value?: arkui_component_common_Callback<OnRefreshAccessedHistoryEvent, void> | undefined
    public _Web_onRenderExited_0_0value?: arkui_component_common_Callback<OnRenderExitedEvent, void> | undefined
    public _Web_onShowFileSelector_0_0value?: arkui_component_common_Callback<OnShowFileSelectorEvent, boolean> | undefined
    public _Web_onResourceLoad_0_0value?: arkui_component_common_Callback<OnResourceLoadEvent, void> | undefined
    public _Web_onFullScreenExit_0_0value?: (() => void) | undefined
    public _Web_onFullScreenEnter_0_0value?: OnFullScreenEnterCallback | undefined
    public _Web_onScaleChange_0_0value?: arkui_component_common_Callback<OnScaleChangeEvent, void> | undefined
    public _Web_onHttpAuthRequest_0_0value?: arkui_component_common_Callback<OnHttpAuthRequestEvent, boolean> | undefined
    public _Web_onInterceptRequest_0_0value?: arkui_component_common_Callback<OnInterceptRequestEvent, WebResourceResponse | null> | undefined
    public _Web_onPermissionRequest_0_0value?: arkui_component_common_Callback<OnPermissionRequestEvent, void> | undefined
    public _Web_onScreenCaptureRequest_0_0value?: arkui_component_common_Callback<OnScreenCaptureRequestEvent, void> | undefined
    public _Web_onContextMenuShow_0_0value?: arkui_component_common_Callback<OnContextMenuShowEvent, boolean> | undefined
    public _Web_onContextMenuHide_0_0value?: OnContextMenuHideCallback | undefined
    public _Web_mediaPlayGestureAccess_0_0value?: boolean | undefined
    public _Web_onSearchResultReceive_0_0value?: arkui_component_common_Callback<OnSearchResultReceiveEvent, void> | undefined
    public _Web_onScroll_0_0value?: arkui_component_common_Callback<OnScrollEvent, void> | undefined
    public _Web_onSslErrorEventReceive_0_0value?: arkui_component_common_Callback<OnSslErrorEventReceiveEvent, void> | undefined
    public _Web_onSslErrorEvent_0_0value?: OnSslErrorEventCallback | undefined
    public _Web_onClientAuthenticationRequest_0_0value?: arkui_component_common_Callback<OnClientAuthenticationEvent, void> | undefined
    public _Web_onVerifyPin_0_0value?: OnVerifyPinCallback | undefined
    public _Web_onWindowNew_0_0value?: arkui_component_common_Callback<OnWindowNewEvent, void> | undefined
    public _Web_onWindowNewExt_0_0value?: arkui_component_common_Callback<OnWindowNewExtEvent, void> | undefined
    public _Web_onWindowExit_0_0value?: (() => void) | undefined
    public _Web_multiWindowAccess_0_0value?: boolean | undefined
    public _Web_onInterceptKeyEvent_0_0value?: ((event: KeyEvent) => boolean) | undefined
    public _Web_webStandardFont_0_0value?: string | undefined
    public _Web_webSerifFont_0_0value?: string | undefined
    public _Web_webSansSerifFont_0_0value?: string | undefined
    public _Web_webFixedFont_0_0value?: string | undefined
    public _Web_webFantasyFont_0_0value?: string | undefined
    public _Web_webCursiveFont_0_0value?: string | undefined
    public _Web_defaultFixedFontSize_0_0value?: int32 | undefined
    public _Web_defaultFontSize_0_0value?: int32 | undefined
    public _Web_minFontSize_0_0value?: int32 | undefined
    public _Web_minLogicalFontSize_0_0value?: int32 | undefined
    public _Web_defaultTextEncodingFormat_0_0value?: string | undefined
    public _Web_forceDisplayScrollBar_0_0value?: boolean | undefined
    public _Web_blockNetwork_0_0value?: boolean | undefined
    public _Web_horizontalScrollBarAccess_0_0value?: boolean | undefined
    public _Web_verticalScrollBarAccess_0_0value?: boolean | undefined
    public _Web_onTouchIconUrlReceived_0_0value?: arkui_component_common_Callback<OnTouchIconUrlReceivedEvent, void> | undefined
    public _Web_onFaviconReceived_0_0value?: arkui_component_common_Callback<OnFaviconReceivedEvent, void> | undefined
    public _Web_onPageVisible_0_0value?: arkui_component_common_Callback<OnPageVisibleEvent, void> | undefined
    public _Web_onDataResubmitted_0_0value?: arkui_component_common_Callback<OnDataResubmittedEvent, void> | undefined
    public _Web_pinchSmooth_0_0value?: boolean | undefined
    public _Web_allowWindowOpenMethod_0_0value?: boolean | undefined
    public _Web_onAudioStateChanged_0_0value?: arkui_component_common_Callback<OnAudioStateChangedEvent, void> | undefined
    public _Web_onFirstContentfulPaint_0_0value?: arkui_component_common_Callback<OnFirstContentfulPaintEvent, void> | undefined
    public _Web_onFirstMeaningfulPaint_0_0value?: OnFirstMeaningfulPaintCallback | undefined
    public _Web_onLargestContentfulPaint_0_0value?: OnLargestContentfulPaintCallback | undefined
    public _Web_onLoadIntercept_0_0value?: arkui_component_common_Callback<OnLoadInterceptEvent, boolean> | undefined
    public _Web_onControllerAttached_0_0value?: (() => void) | undefined
    public _Web_onOverScroll_0_0value?: arkui_component_common_Callback<OnOverScrollEvent, void> | undefined
    public _Web_onPdfScrollAtBottom_0_0value?: arkui_component_common_Callback<OnPdfScrollEvent, void> | undefined
    public _Web_onPdfLoadEvent_0_0value?: arkui_component_common_Callback<OnPdfLoadEvent, void> | undefined
    public _Web_onSafeBrowsingCheckResult_0_0value?: OnSafeBrowsingCheckResultCallback | undefined
    public _Web_onSafeBrowsingCheckFinish_0_0value?: OnSafeBrowsingCheckResultCallback | undefined
    public _Web_onNavigationEntryCommitted_0_0value?: OnNavigationEntryCommittedCallback | undefined
    public _Web_onIntelligentTrackingPreventionResult_0_0value?: OnIntelligentTrackingPreventionCallback | undefined
    public _Web_javaScriptOnDocumentStart_0_0value?: Array<ScriptItem> | undefined
    public _Web_javaScriptOnDocumentEnd_0_0value?: Array<ScriptItem> | undefined
    public _Web_layoutMode_0_0value?: WebLayoutMode | undefined
    public _Web_nestedScroll_0_0value?: NestedScrollOptions | NestedScrollOptionsExt | undefined
    public _Web_enableNativeEmbedMode_0_0value?: boolean | undefined
    public _Web_onNativeEmbedLifecycleChange_0_0value?: ((event: NativeEmbedDataInfo) => void) | undefined
    public _Web_onNativeEmbedVisibilityChange_0_0value?: OnNativeEmbedVisibilityChangeCallback | undefined
    public _Web_onNativeEmbedGestureEvent_0_0value?: ((event: NativeEmbedTouchInfo) => void) | undefined
    public _Web_onNativeEmbedMouseEvent_0_0value?: MouseInfoCallback | undefined
    public _Web_copyOptions_0_0value?: CopyOptions | undefined
    public _Web_onOverrideUrlLoading_0_0value?: OnOverrideUrlLoadingCallback | undefined
    public _Web_onOverrideErrorPage_0_0value?: OnOverrideErrorPageCallback | undefined
    public _Web_textAutosizing_0_0value?: boolean | undefined
    public _Web_enableNativeMediaPlayer_0_0value?: NativeMediaPlayerConfig | undefined
    public _Web_onRenderProcessNotResponding_0_0value?: OnRenderProcessNotRespondingCallback | undefined
    public _Web_onRenderProcessResponding_0_0value?: OnRenderProcessRespondingCallback | undefined
    public _Web_onViewportFitChanged_0_0value?: OnViewportFitChangedCallback | undefined
    public _Web_onInterceptKeyboardAttach_0_0value?: WebKeyboardCallback | undefined
    public _Web_onAdsBlocked_0_0value?: OnAdsBlockedCallback | undefined
    public _Web_keyboardAvoidMode_0_0value?: WebKeyboardAvoidMode | undefined
    public _Web_editMenuOptions_0_0value?: EditMenuOptions | undefined
    public _Web_enableHapticFeedback_0_0value?: boolean | undefined
    public _Web_enableFollowSystemFontWeight_0_0value?: boolean | undefined
    public _Web_enableWebAVSession_0_0value?: boolean | undefined
    public _Web_optimizeParserBudget_0_0value?: boolean | undefined
    public _Web_runJavaScriptOnDocumentStart_0_0value?: Array<ScriptItem> | undefined
    public _Web_runJavaScriptOnDocumentEnd_0_0value?: Array<ScriptItem> | undefined
    public _Web_runJavaScriptOnHeadEnd_0_0value?: Array<ScriptItem> | undefined
    public _Web_nativeEmbedOptions_0_0value?: EmbedOptions | undefined
    public _Web_enableDataDetector_0_0value?: boolean | undefined
    public _Web_dataDetectorConfig_0_0value?: TextDataDetectorConfig | undefined
    public _Web_onActivateContent_0_0value?: VoidCallback | undefined
    public _Web_bypassVsyncCondition_0_0value?: WebBypassVsyncCondition | undefined
    public _Web_gestureFocusMode_0_0value?: GestureFocusMode | undefined
    public _Web_forceEnableZoom_0_0value?: boolean | undefined
    public _Web_onNativeEmbedObjectParamChange_0_0value?: OnNativeEmbedObjectParamChangeCallback | undefined
    public _Web_rotateRenderEffect_0_0value?: WebRotateEffect | undefined
    public _Web_zoomControlAccess_0_0value?: boolean | undefined
    public _Web_onDetectedBlankScreen_0_0value?: OnDetectBlankScreenCallback | undefined
    public _Web_blankScreenDetectionConfig_0_0value?: BlankScreenDetectionConfig | undefined
    public _Web_backToTop_0_0value?: boolean | undefined
    public _Web_enableSelectedDataDetector_0_0value?: boolean | undefined
    public _Web_onFirstScreenPaint_0_0value?: OnFirstScreenPaintCallback | undefined
    public _Web_enableAutoFill_0_0value?: boolean | undefined
    public _Web_onTextSelectionChange_0_0value?: TextSelectionChangeCallback | undefined
    public _Web_enableImageAnalyzer_0_0value?: boolean | undefined
    public _Web_onCameraCaptureStateChange_0_0value?: OnCameraCaptureStateChangeCallback | undefined
    public _Web_onMicrophoneCaptureStateChange_0_0value?: OnMicrophoneCaptureStateChangeCallback | undefined
    public _Web_enableDefaultContextMenu_0_0value?: boolean | undefined
    public _Web_enableDrag_0_0value?: boolean | undefined
    public _Web_scrollbarLayoutPolicy_0_0value?: ScrollbarLayoutPolicy | undefined
    public _Web_aiSessionOptions_0_0value?: Array<AISessionEvent> | undefined
    public _Web_keyboardAppearance_0_0value?: WebKeyboardAppearanceMode | undefined
    public _Web_onInputmethodAttached_0_0value?: OnInputmethodAttachedCallback | undefined
    public _Web_registerNativeEmbedRule_0_0value?: string | undefined
    public _Web_registerNativeEmbedRule_0_1value?: string | undefined
    public _Web_bindSelectionMenu_0_0value?: WebElementType | undefined
    public _Web_bindSelectionMenu_0_1value?: CustomBuilder | undefined
    public _Web_bindSelectionMenu_0_2value?: WebResponseType | undefined
    public _Web_bindSelectionMenu_0_3value?: SelectionMenuOptionsExt | undefined
    public _Web_enableScrollDirectionalLock_0_0value?: boolean | undefined
    public _Web_enableScrollDirectionalLock_0_1value?: ScrollDirectionalLockType | undefined
    applyModifierPatch(node: object): void {
        super.applyModifierPatch(node)
        this._state.addRef()
        const peer = node as ArkWebPeer;
        const flagArray = this._Web_flagArray;
        this.applyModifierPatch0(peer, flagArray);
        this.applyModifierPatch1(peer, flagArray);
        this.applyModifierPatch2(peer, flagArray);
        this.applyModifierPatch3(peer, flagArray);
        this.applyModifierPatch4(peer, flagArray);
        this.applyModifierPatch5(peer, flagArray);
        this.applyModifierPatch6(peer, flagArray);
        this.applyModifierPatch7(peer, flagArray);
    }
    applyModifierPatch0(peer: ArkWebPeer, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1: {
                    peer.setJavaScriptAccessAttribute((this._Web_javaScriptAccess_0_0value as boolean | undefined));
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
                    peer.setFileAccessAttribute((this._Web_fileAccess_0_0value as boolean | undefined));
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
                    peer.setOnlineImageAccessAttribute((this._Web_onlineImageAccess_0_0value as boolean | undefined));
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
                    peer.setDomStorageAccessAttribute((this._Web_domStorageAccess_0_0value as boolean | undefined));
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
                    peer.setImageAccessAttribute((this._Web_imageAccess_0_0value as boolean | undefined));
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
                    peer.setMixedModeAttribute((this._Web_mixedMode_0_0value as MixedMode | undefined));
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
                    peer.setZoomAccessAttribute((this._Web_zoomAccess_0_0value as boolean | undefined));
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
                    peer.setGeolocationAccessAttribute((this._Web_geolocationAccess_0_0value as boolean | undefined));
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
                    peer.setJavaScriptProxyAttribute((this._Web_javaScriptProxy_0_0value as JavaScriptProxy | undefined));
                    flagArray[8] = 2;
                    break;
                }
                case 3: {
                    flagArray[8] = 2;
                    break;
                }
                default: {
                    flagArray[8] = 0;
                    peer.setJavaScriptProxyAttribute((undefined as JavaScriptProxy | undefined));
                }
            }
        }
        if (flagArray[9] != 0) {
            switch (flagArray[9]) {
                case 1: {
                    peer.setCacheModeAttribute((this._Web_cacheMode_0_0value as CacheMode | undefined));
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
                    peer.setDarkModeAttribute((this._Web_darkMode_0_0value as WebDarkMode | undefined));
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
                    peer.setForceDarkAccessAttribute((this._Web_forceDarkAccess_0_0value as boolean | undefined));
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
                    peer.setMediaOptionsAttribute((this._Web_mediaOptions_0_0value as WebMediaOptions | undefined));
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
                    peer.setOverviewModeAccessAttribute((this._Web_overviewModeAccess_0_0value as boolean | undefined));
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
                    peer.setOverScrollModeAttribute((this._Web_overScrollMode_0_0value as OverScrollMode | undefined));
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
                    peer.setBlurOnKeyboardHideModeAttribute((this._Web_blurOnKeyboardHideMode_0_0value as BlurOnKeyboardHideMode | undefined));
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
                    peer.setTextZoomRatioAttribute((this._Web_textZoomRatio_0_0value as int32 | undefined));
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
                    peer.setDatabaseAccessAttribute((this._Web_databaseAccess_0_0value as boolean | undefined));
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
                    peer.setInitialScaleAttribute((this._Web_initialScale_0_0value as double | undefined));
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
                    peer.setMetaViewportAttribute((this._Web_metaViewport_0_0value as boolean | undefined));
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
                    peer.setOnPageBeginAttribute((this._Web_onPageBegin_0_0value as arkui_component_common_Callback<OnPageBeginEvent, void> | undefined));
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
                    peer.setOnPageEndAttribute((this._Web_onPageEnd_0_0value as arkui_component_common_Callback<OnPageEndEvent, void> | undefined));
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
                    peer.setOnLoadStartedAttribute((this._Web_onLoadStarted_0_0value as arkui_component_common_Callback<OnLoadStartedEvent, void> | undefined));
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
                    peer.setOnLoadFinishedAttribute((this._Web_onLoadFinished_0_0value as arkui_component_common_Callback<OnLoadFinishedEvent, void> | undefined));
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
                    peer.setOnProgressChangeAttribute((this._Web_onProgressChange_0_0value as arkui_component_common_Callback<OnProgressChangeEvent, void> | undefined));
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
                    peer.setOnTitleReceiveAttribute((this._Web_onTitleReceive_0_0value as arkui_component_common_Callback<OnTitleReceiveEvent, void> | undefined));
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
                    peer.setOnGeolocationHideAttribute((this._Web_onGeolocationHide_0_0value as (() => void) | undefined));
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
                    peer.setOnGeolocationShowAttribute((this._Web_onGeolocationShow_0_0value as arkui_component_common_Callback<OnGeolocationShowEvent, void> | undefined));
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
                    peer.setOnRequestSelectedAttribute((this._Web_onRequestSelected_0_0value as (() => void) | undefined));
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
                    peer.setOnAlertAttribute((this._Web_onAlert_0_0value as arkui_component_common_Callback<OnAlertEvent, boolean> | undefined));
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
                    peer.setOnBeforeUnloadAttribute((this._Web_onBeforeUnload_0_0value as arkui_component_common_Callback<OnBeforeUnloadEvent, boolean> | undefined));
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
                    peer.setOnConfirmAttribute((this._Web_onConfirm_0_0value as arkui_component_common_Callback<OnConfirmEvent, boolean> | undefined));
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
                    peer.setOnPromptAttribute((this._Web_onPrompt_0_0value as arkui_component_common_Callback<OnPromptEvent, boolean> | undefined));
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
                    peer.setOnConsoleAttribute((this._Web_onConsole_0_0value as arkui_component_common_Callback<OnConsoleEvent, boolean> | undefined));
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
                    peer.setOnErrorReceiveAttribute((this._Web_onErrorReceive_0_0value as arkui_component_common_Callback<OnErrorReceiveEvent, void> | undefined));
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
                    peer.setOnHttpErrorReceiveAttribute((this._Web_onHttpErrorReceive_0_0value as arkui_component_common_Callback<OnHttpErrorReceiveEvent, void> | undefined));
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
                    peer.setOnDownloadStartAttribute((this._Web_onDownloadStart_0_0value as arkui_component_common_Callback<OnDownloadStartEvent, void> | undefined));
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
                    peer.setOnRefreshAccessedHistoryAttribute((this._Web_onRefreshAccessedHistory_0_0value as arkui_component_common_Callback<OnRefreshAccessedHistoryEvent, void> | undefined));
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
                    peer.setOnRenderExitedAttribute((this._Web_onRenderExited_0_0value as arkui_component_common_Callback<OnRenderExitedEvent, void> | undefined));
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
                    peer.setOnShowFileSelectorAttribute((this._Web_onShowFileSelector_0_0value as arkui_component_common_Callback<OnShowFileSelectorEvent, boolean> | undefined));
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
                    peer.setOnResourceLoadAttribute((this._Web_onResourceLoad_0_0value as arkui_component_common_Callback<OnResourceLoadEvent, void> | undefined));
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
                    peer.setOnFullScreenExitAttribute((this._Web_onFullScreenExit_0_0value as (() => void) | undefined));
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
                    peer.setOnFullScreenEnterAttribute((this._Web_onFullScreenEnter_0_0value as OnFullScreenEnterCallback | undefined));
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
                    peer.setOnScaleChangeAttribute((this._Web_onScaleChange_0_0value as arkui_component_common_Callback<OnScaleChangeEvent, void> | undefined));
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
                    peer.setOnHttpAuthRequestAttribute((this._Web_onHttpAuthRequest_0_0value as arkui_component_common_Callback<OnHttpAuthRequestEvent, boolean> | undefined));
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
                    peer.setOnInterceptRequestAttribute((this._Web_onInterceptRequest_0_0value as arkui_component_common_Callback<OnInterceptRequestEvent, WebResourceResponse | null> | undefined));
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
                    peer.setOnPermissionRequestAttribute((this._Web_onPermissionRequest_0_0value as arkui_component_common_Callback<OnPermissionRequestEvent, void> | undefined));
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
                    peer.setOnScreenCaptureRequestAttribute((this._Web_onScreenCaptureRequest_0_0value as arkui_component_common_Callback<OnScreenCaptureRequestEvent, void> | undefined));
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
                    peer.setOnContextMenuShowAttribute((this._Web_onContextMenuShow_0_0value as arkui_component_common_Callback<OnContextMenuShowEvent, boolean> | undefined));
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
                    peer.setOnContextMenuHideAttribute((this._Web_onContextMenuHide_0_0value as OnContextMenuHideCallback | undefined));
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
                    peer.setMediaPlayGestureAccessAttribute((this._Web_mediaPlayGestureAccess_0_0value as boolean | undefined));
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
                    peer.setOnSearchResultReceiveAttribute((this._Web_onSearchResultReceive_0_0value as arkui_component_common_Callback<OnSearchResultReceiveEvent, void> | undefined));
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
                    peer.setOnScrollAttribute((this._Web_onScroll_0_0value as arkui_component_common_Callback<OnScrollEvent, void> | undefined));
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
                    peer.setOnSslErrorEventReceiveAttribute((this._Web_onSslErrorEventReceive_0_0value as arkui_component_common_Callback<OnSslErrorEventReceiveEvent, void> | undefined));
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
                    peer.setOnSslErrorEventAttribute((this._Web_onSslErrorEvent_0_0value as OnSslErrorEventCallback | undefined));
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
                    peer.setOnClientAuthenticationRequestAttribute((this._Web_onClientAuthenticationRequest_0_0value as arkui_component_common_Callback<OnClientAuthenticationEvent, void> | undefined));
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
                    peer.setOnVerifyPinAttribute((this._Web_onVerifyPin_0_0value as OnVerifyPinCallback | undefined));
                    flagArray[56] = 2;
                    break;
                }
                case 3: {
                    flagArray[56] = 2;
                    break;
                }
                default: {
                    flagArray[56] = 0;
                    peer.setOnVerifyPinAttribute((undefined as OnVerifyPinCallback | undefined));
                }
            }
        }
        if (flagArray[57] != 0) {
            switch (flagArray[57]) {
                case 1: {
                    peer.setOnWindowNewAttribute((this._Web_onWindowNew_0_0value as arkui_component_common_Callback<OnWindowNewEvent, void> | undefined));
                    flagArray[57] = 2;
                    break;
                }
                case 3: {
                    flagArray[57] = 2;
                    break;
                }
                default: {
                    flagArray[57] = 0;
                    peer.setOnWindowNewAttribute((undefined as arkui_component_common_Callback<OnWindowNewEvent, void> | undefined));
                }
            }
        }
        if (flagArray[58] != 0) {
            switch (flagArray[58]) {
                case 1: {
                    peer.setOnWindowNewExtAttribute((this._Web_onWindowNewExt_0_0value as arkui_component_common_Callback<OnWindowNewExtEvent, void> | undefined));
                    flagArray[58] = 2;
                    break;
                }
                case 3: {
                    flagArray[58] = 2;
                    break;
                }
                default: {
                    flagArray[58] = 0;
                    peer.setOnWindowNewExtAttribute((undefined as arkui_component_common_Callback<OnWindowNewExtEvent, void> | undefined));
                }
            }
        }
        if (flagArray[59] != 0) {
            switch (flagArray[59]) {
                case 1: {
                    peer.setOnWindowExitAttribute((this._Web_onWindowExit_0_0value as (() => void) | undefined));
                    flagArray[59] = 2;
                    break;
                }
                case 3: {
                    flagArray[59] = 2;
                    break;
                }
                default: {
                    flagArray[59] = 0;
                    peer.setOnWindowExitAttribute((undefined as (() => void) | undefined));
                }
            }
        }
    }
    applyModifierPatch3(peer: ArkWebPeer, flagArray: Uint8Array): void {
        if (flagArray[60] != 0) {
            switch (flagArray[60]) {
                case 1: {
                    peer.setMultiWindowAccessAttribute((this._Web_multiWindowAccess_0_0value as boolean | undefined));
                    flagArray[60] = 2;
                    break;
                }
                case 3: {
                    flagArray[60] = 2;
                    break;
                }
                default: {
                    flagArray[60] = 0;
                    peer.setMultiWindowAccessAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[61] != 0) {
            switch (flagArray[61]) {
                case 1: {
                    peer.setOnInterceptKeyEventAttribute((this._Web_onInterceptKeyEvent_0_0value as ((event: KeyEvent) => boolean) | undefined));
                    flagArray[61] = 2;
                    break;
                }
                case 3: {
                    flagArray[61] = 2;
                    break;
                }
                default: {
                    flagArray[61] = 0;
                    peer.setOnInterceptKeyEventAttribute((undefined as ((event: KeyEvent) => boolean) | undefined));
                }
            }
        }
        if (flagArray[62] != 0) {
            switch (flagArray[62]) {
                case 1: {
                    peer.setWebStandardFontAttribute((this._Web_webStandardFont_0_0value as string | undefined));
                    flagArray[62] = 2;
                    break;
                }
                case 3: {
                    flagArray[62] = 2;
                    break;
                }
                default: {
                    flagArray[62] = 0;
                    peer.setWebStandardFontAttribute((undefined as string | undefined));
                }
            }
        }
        if (flagArray[63] != 0) {
            switch (flagArray[63]) {
                case 1: {
                    peer.setWebSerifFontAttribute((this._Web_webSerifFont_0_0value as string | undefined));
                    flagArray[63] = 2;
                    break;
                }
                case 3: {
                    flagArray[63] = 2;
                    break;
                }
                default: {
                    flagArray[63] = 0;
                    peer.setWebSerifFontAttribute((undefined as string | undefined));
                }
            }
        }
        if (flagArray[64] != 0) {
            switch (flagArray[64]) {
                case 1: {
                    peer.setWebSansSerifFontAttribute((this._Web_webSansSerifFont_0_0value as string | undefined));
                    flagArray[64] = 2;
                    break;
                }
                case 3: {
                    flagArray[64] = 2;
                    break;
                }
                default: {
                    flagArray[64] = 0;
                    peer.setWebSansSerifFontAttribute((undefined as string | undefined));
                }
            }
        }
        if (flagArray[65] != 0) {
            switch (flagArray[65]) {
                case 1: {
                    peer.setWebFixedFontAttribute((this._Web_webFixedFont_0_0value as string | undefined));
                    flagArray[65] = 2;
                    break;
                }
                case 3: {
                    flagArray[65] = 2;
                    break;
                }
                default: {
                    flagArray[65] = 0;
                    peer.setWebFixedFontAttribute((undefined as string | undefined));
                }
            }
        }
        if (flagArray[66] != 0) {
            switch (flagArray[66]) {
                case 1: {
                    peer.setWebFantasyFontAttribute((this._Web_webFantasyFont_0_0value as string | undefined));
                    flagArray[66] = 2;
                    break;
                }
                case 3: {
                    flagArray[66] = 2;
                    break;
                }
                default: {
                    flagArray[66] = 0;
                    peer.setWebFantasyFontAttribute((undefined as string | undefined));
                }
            }
        }
        if (flagArray[67] != 0) {
            switch (flagArray[67]) {
                case 1: {
                    peer.setWebCursiveFontAttribute((this._Web_webCursiveFont_0_0value as string | undefined));
                    flagArray[67] = 2;
                    break;
                }
                case 3: {
                    flagArray[67] = 2;
                    break;
                }
                default: {
                    flagArray[67] = 0;
                    peer.setWebCursiveFontAttribute((undefined as string | undefined));
                }
            }
        }
        if (flagArray[68] != 0) {
            switch (flagArray[68]) {
                case 1: {
                    peer.setDefaultFixedFontSizeAttribute((this._Web_defaultFixedFontSize_0_0value as int32 | undefined));
                    flagArray[68] = 2;
                    break;
                }
                case 3: {
                    flagArray[68] = 2;
                    break;
                }
                default: {
                    flagArray[68] = 0;
                    peer.setDefaultFixedFontSizeAttribute((undefined as int32 | undefined));
                }
            }
        }
        if (flagArray[69] != 0) {
            switch (flagArray[69]) {
                case 1: {
                    peer.setDefaultFontSizeAttribute((this._Web_defaultFontSize_0_0value as int32 | undefined));
                    flagArray[69] = 2;
                    break;
                }
                case 3: {
                    flagArray[69] = 2;
                    break;
                }
                default: {
                    flagArray[69] = 0;
                    peer.setDefaultFontSizeAttribute((undefined as int32 | undefined));
                }
            }
        }
        if (flagArray[70] != 0) {
            switch (flagArray[70]) {
                case 1: {
                    peer.setMinFontSizeAttribute((this._Web_minFontSize_0_0value as int32 | undefined));
                    flagArray[70] = 2;
                    break;
                }
                case 3: {
                    flagArray[70] = 2;
                    break;
                }
                default: {
                    flagArray[70] = 0;
                    peer.setMinFontSizeAttribute((undefined as int32 | undefined));
                }
            }
        }
        if (flagArray[71] != 0) {
            switch (flagArray[71]) {
                case 1: {
                    peer.setMinLogicalFontSizeAttribute((this._Web_minLogicalFontSize_0_0value as int32 | undefined));
                    flagArray[71] = 2;
                    break;
                }
                case 3: {
                    flagArray[71] = 2;
                    break;
                }
                default: {
                    flagArray[71] = 0;
                    peer.setMinLogicalFontSizeAttribute((undefined as int32 | undefined));
                }
            }
        }
        if (flagArray[72] != 0) {
            switch (flagArray[72]) {
                case 1: {
                    peer.setDefaultTextEncodingFormatAttribute((this._Web_defaultTextEncodingFormat_0_0value as string | undefined));
                    flagArray[72] = 2;
                    break;
                }
                case 3: {
                    flagArray[72] = 2;
                    break;
                }
                default: {
                    flagArray[72] = 0;
                    peer.setDefaultTextEncodingFormatAttribute((undefined as string | undefined));
                }
            }
        }
        if (flagArray[73] != 0) {
            switch (flagArray[73]) {
                case 1: {
                    peer.setForceDisplayScrollBarAttribute((this._Web_forceDisplayScrollBar_0_0value as boolean | undefined));
                    flagArray[73] = 2;
                    break;
                }
                case 3: {
                    flagArray[73] = 2;
                    break;
                }
                default: {
                    flagArray[73] = 0;
                    peer.setForceDisplayScrollBarAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[74] != 0) {
            switch (flagArray[74]) {
                case 1: {
                    peer.setBlockNetworkAttribute((this._Web_blockNetwork_0_0value as boolean | undefined));
                    flagArray[74] = 2;
                    break;
                }
                case 3: {
                    flagArray[74] = 2;
                    break;
                }
                default: {
                    flagArray[74] = 0;
                    peer.setBlockNetworkAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[75] != 0) {
            switch (flagArray[75]) {
                case 1: {
                    peer.setHorizontalScrollBarAccessAttribute((this._Web_horizontalScrollBarAccess_0_0value as boolean | undefined));
                    flagArray[75] = 2;
                    break;
                }
                case 3: {
                    flagArray[75] = 2;
                    break;
                }
                default: {
                    flagArray[75] = 0;
                    peer.setHorizontalScrollBarAccessAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[76] != 0) {
            switch (flagArray[76]) {
                case 1: {
                    peer.setVerticalScrollBarAccessAttribute((this._Web_verticalScrollBarAccess_0_0value as boolean | undefined));
                    flagArray[76] = 2;
                    break;
                }
                case 3: {
                    flagArray[76] = 2;
                    break;
                }
                default: {
                    flagArray[76] = 0;
                    peer.setVerticalScrollBarAccessAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[77] != 0) {
            switch (flagArray[77]) {
                case 1: {
                    peer.setOnTouchIconUrlReceivedAttribute((this._Web_onTouchIconUrlReceived_0_0value as arkui_component_common_Callback<OnTouchIconUrlReceivedEvent, void> | undefined));
                    flagArray[77] = 2;
                    break;
                }
                case 3: {
                    flagArray[77] = 2;
                    break;
                }
                default: {
                    flagArray[77] = 0;
                    peer.setOnTouchIconUrlReceivedAttribute((undefined as arkui_component_common_Callback<OnTouchIconUrlReceivedEvent, void> | undefined));
                }
            }
        }
        if (flagArray[78] != 0) {
            switch (flagArray[78]) {
                case 1: {
                    peer.setOnFaviconReceivedAttribute((this._Web_onFaviconReceived_0_0value as arkui_component_common_Callback<OnFaviconReceivedEvent, void> | undefined));
                    flagArray[78] = 2;
                    break;
                }
                case 3: {
                    flagArray[78] = 2;
                    break;
                }
                default: {
                    flagArray[78] = 0;
                    peer.setOnFaviconReceivedAttribute((undefined as arkui_component_common_Callback<OnFaviconReceivedEvent, void> | undefined));
                }
            }
        }
        if (flagArray[79] != 0) {
            switch (flagArray[79]) {
                case 1: {
                    peer.setOnPageVisibleAttribute((this._Web_onPageVisible_0_0value as arkui_component_common_Callback<OnPageVisibleEvent, void> | undefined));
                    flagArray[79] = 2;
                    break;
                }
                case 3: {
                    flagArray[79] = 2;
                    break;
                }
                default: {
                    flagArray[79] = 0;
                    peer.setOnPageVisibleAttribute((undefined as arkui_component_common_Callback<OnPageVisibleEvent, void> | undefined));
                }
            }
        }
    }
    applyModifierPatch4(peer: ArkWebPeer, flagArray: Uint8Array): void {
        if (flagArray[80] != 0) {
            switch (flagArray[80]) {
                case 1: {
                    peer.setOnDataResubmittedAttribute((this._Web_onDataResubmitted_0_0value as arkui_component_common_Callback<OnDataResubmittedEvent, void> | undefined));
                    flagArray[80] = 2;
                    break;
                }
                case 3: {
                    flagArray[80] = 2;
                    break;
                }
                default: {
                    flagArray[80] = 0;
                    peer.setOnDataResubmittedAttribute((undefined as arkui_component_common_Callback<OnDataResubmittedEvent, void> | undefined));
                }
            }
        }
        if (flagArray[81] != 0) {
            switch (flagArray[81]) {
                case 1: {
                    peer.setPinchSmoothAttribute((this._Web_pinchSmooth_0_0value as boolean | undefined));
                    flagArray[81] = 2;
                    break;
                }
                case 3: {
                    flagArray[81] = 2;
                    break;
                }
                default: {
                    flagArray[81] = 0;
                    peer.setPinchSmoothAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[82] != 0) {
            switch (flagArray[82]) {
                case 1: {
                    peer.setAllowWindowOpenMethodAttribute((this._Web_allowWindowOpenMethod_0_0value as boolean | undefined));
                    flagArray[82] = 2;
                    break;
                }
                case 3: {
                    flagArray[82] = 2;
                    break;
                }
                default: {
                    flagArray[82] = 0;
                    peer.setAllowWindowOpenMethodAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[83] != 0) {
            switch (flagArray[83]) {
                case 1: {
                    peer.setOnAudioStateChangedAttribute((this._Web_onAudioStateChanged_0_0value as arkui_component_common_Callback<OnAudioStateChangedEvent, void> | undefined));
                    flagArray[83] = 2;
                    break;
                }
                case 3: {
                    flagArray[83] = 2;
                    break;
                }
                default: {
                    flagArray[83] = 0;
                    peer.setOnAudioStateChangedAttribute((undefined as arkui_component_common_Callback<OnAudioStateChangedEvent, void> | undefined));
                }
            }
        }
        if (flagArray[84] != 0) {
            switch (flagArray[84]) {
                case 1: {
                    peer.setOnFirstContentfulPaintAttribute((this._Web_onFirstContentfulPaint_0_0value as arkui_component_common_Callback<OnFirstContentfulPaintEvent, void> | undefined));
                    flagArray[84] = 2;
                    break;
                }
                case 3: {
                    flagArray[84] = 2;
                    break;
                }
                default: {
                    flagArray[84] = 0;
                    peer.setOnFirstContentfulPaintAttribute((undefined as arkui_component_common_Callback<OnFirstContentfulPaintEvent, void> | undefined));
                }
            }
        }
        if (flagArray[85] != 0) {
            switch (flagArray[85]) {
                case 1: {
                    peer.setOnFirstMeaningfulPaintAttribute((this._Web_onFirstMeaningfulPaint_0_0value as OnFirstMeaningfulPaintCallback | undefined));
                    flagArray[85] = 2;
                    break;
                }
                case 3: {
                    flagArray[85] = 2;
                    break;
                }
                default: {
                    flagArray[85] = 0;
                    peer.setOnFirstMeaningfulPaintAttribute((undefined as OnFirstMeaningfulPaintCallback | undefined));
                }
            }
        }
        if (flagArray[86] != 0) {
            switch (flagArray[86]) {
                case 1: {
                    peer.setOnLargestContentfulPaintAttribute((this._Web_onLargestContentfulPaint_0_0value as OnLargestContentfulPaintCallback | undefined));
                    flagArray[86] = 2;
                    break;
                }
                case 3: {
                    flagArray[86] = 2;
                    break;
                }
                default: {
                    flagArray[86] = 0;
                    peer.setOnLargestContentfulPaintAttribute((undefined as OnLargestContentfulPaintCallback | undefined));
                }
            }
        }
        if (flagArray[87] != 0) {
            switch (flagArray[87]) {
                case 1: {
                    peer.setOnLoadInterceptAttribute((this._Web_onLoadIntercept_0_0value as arkui_component_common_Callback<OnLoadInterceptEvent, boolean> | undefined));
                    flagArray[87] = 2;
                    break;
                }
                case 3: {
                    flagArray[87] = 2;
                    break;
                }
                default: {
                    flagArray[87] = 0;
                    peer.setOnLoadInterceptAttribute((undefined as arkui_component_common_Callback<OnLoadInterceptEvent, boolean> | undefined));
                }
            }
        }
        if (flagArray[88] != 0) {
            switch (flagArray[88]) {
                case 1: {
                    peer.setOnControllerAttachedAttribute((this._Web_onControllerAttached_0_0value as (() => void) | undefined));
                    flagArray[88] = 2;
                    break;
                }
                case 3: {
                    flagArray[88] = 2;
                    break;
                }
                default: {
                    flagArray[88] = 0;
                    peer.setOnControllerAttachedAttribute((undefined as (() => void) | undefined));
                }
            }
        }
        if (flagArray[89] != 0) {
            switch (flagArray[89]) {
                case 1: {
                    peer.setOnOverScrollAttribute((this._Web_onOverScroll_0_0value as arkui_component_common_Callback<OnOverScrollEvent, void> | undefined));
                    flagArray[89] = 2;
                    break;
                }
                case 3: {
                    flagArray[89] = 2;
                    break;
                }
                default: {
                    flagArray[89] = 0;
                    peer.setOnOverScrollAttribute((undefined as arkui_component_common_Callback<OnOverScrollEvent, void> | undefined));
                }
            }
        }
        if (flagArray[90] != 0) {
            switch (flagArray[90]) {
                case 1: {
                    peer.setOnPdfScrollAtBottomAttribute((this._Web_onPdfScrollAtBottom_0_0value as arkui_component_common_Callback<OnPdfScrollEvent, void> | undefined));
                    flagArray[90] = 2;
                    break;
                }
                case 3: {
                    flagArray[90] = 2;
                    break;
                }
                default: {
                    flagArray[90] = 0;
                    peer.setOnPdfScrollAtBottomAttribute((undefined as arkui_component_common_Callback<OnPdfScrollEvent, void> | undefined));
                }
            }
        }
        if (flagArray[91] != 0) {
            switch (flagArray[91]) {
                case 1: {
                    peer.setOnPdfLoadEventAttribute((this._Web_onPdfLoadEvent_0_0value as arkui_component_common_Callback<OnPdfLoadEvent, void> | undefined));
                    flagArray[91] = 2;
                    break;
                }
                case 3: {
                    flagArray[91] = 2;
                    break;
                }
                default: {
                    flagArray[91] = 0;
                    peer.setOnPdfLoadEventAttribute((undefined as arkui_component_common_Callback<OnPdfLoadEvent, void> | undefined));
                }
            }
        }
        if (flagArray[92] != 0) {
            switch (flagArray[92]) {
                case 1: {
                    peer.setOnSafeBrowsingCheckResultAttribute((this._Web_onSafeBrowsingCheckResult_0_0value as OnSafeBrowsingCheckResultCallback | undefined));
                    flagArray[92] = 2;
                    break;
                }
                case 3: {
                    flagArray[92] = 2;
                    break;
                }
                default: {
                    flagArray[92] = 0;
                    peer.setOnSafeBrowsingCheckResultAttribute((undefined as OnSafeBrowsingCheckResultCallback | undefined));
                }
            }
        }
        if (flagArray[93] != 0) {
            switch (flagArray[93]) {
                case 1: {
                    peer.setOnSafeBrowsingCheckFinishAttribute((this._Web_onSafeBrowsingCheckFinish_0_0value as OnSafeBrowsingCheckResultCallback | undefined));
                    flagArray[93] = 2;
                    break;
                }
                case 3: {
                    flagArray[93] = 2;
                    break;
                }
                default: {
                    flagArray[93] = 0;
                    peer.setOnSafeBrowsingCheckFinishAttribute((undefined as OnSafeBrowsingCheckResultCallback | undefined));
                }
            }
        }
        if (flagArray[94] != 0) {
            switch (flagArray[94]) {
                case 1: {
                    peer.setOnNavigationEntryCommittedAttribute((this._Web_onNavigationEntryCommitted_0_0value as OnNavigationEntryCommittedCallback | undefined));
                    flagArray[94] = 2;
                    break;
                }
                case 3: {
                    flagArray[94] = 2;
                    break;
                }
                default: {
                    flagArray[94] = 0;
                    peer.setOnNavigationEntryCommittedAttribute((undefined as OnNavigationEntryCommittedCallback | undefined));
                }
            }
        }
        if (flagArray[95] != 0) {
            switch (flagArray[95]) {
                case 1: {
                    peer.setOnIntelligentTrackingPreventionResultAttribute((this._Web_onIntelligentTrackingPreventionResult_0_0value as OnIntelligentTrackingPreventionCallback | undefined));
                    flagArray[95] = 2;
                    break;
                }
                case 3: {
                    flagArray[95] = 2;
                    break;
                }
                default: {
                    flagArray[95] = 0;
                    peer.setOnIntelligentTrackingPreventionResultAttribute((undefined as OnIntelligentTrackingPreventionCallback | undefined));
                }
            }
        }
        if (flagArray[96] != 0) {
            switch (flagArray[96]) {
                case 1: {
                    peer.setJavaScriptOnDocumentStartAttribute((this._Web_javaScriptOnDocumentStart_0_0value as Array<ScriptItem> | undefined));
                    flagArray[96] = 2;
                    break;
                }
                case 3: {
                    flagArray[96] = 2;
                    break;
                }
                default: {
                    flagArray[96] = 0;
                    peer.setJavaScriptOnDocumentStartAttribute((undefined as Array<ScriptItem> | undefined));
                }
            }
        }
        if (flagArray[97] != 0) {
            switch (flagArray[97]) {
                case 1: {
                    peer.setJavaScriptOnDocumentEndAttribute((this._Web_javaScriptOnDocumentEnd_0_0value as Array<ScriptItem> | undefined));
                    flagArray[97] = 2;
                    break;
                }
                case 3: {
                    flagArray[97] = 2;
                    break;
                }
                default: {
                    flagArray[97] = 0;
                    peer.setJavaScriptOnDocumentEndAttribute((undefined as Array<ScriptItem> | undefined));
                }
            }
        }
        if (flagArray[98] != 0) {
            switch (flagArray[98]) {
                case 1: {
                    peer.setLayoutModeAttribute((this._Web_layoutMode_0_0value as WebLayoutMode | undefined));
                    flagArray[98] = 2;
                    break;
                }
                case 3: {
                    flagArray[98] = 2;
                    break;
                }
                default: {
                    flagArray[98] = 0;
                    peer.setLayoutModeAttribute((undefined as WebLayoutMode | undefined));
                }
            }
        }
        if (flagArray[99] != 0) {
            switch (flagArray[99]) {
                case 1: {
                    peer.setNestedScrollAttribute((this._Web_nestedScroll_0_0value as NestedScrollOptions | NestedScrollOptionsExt | undefined));
                    flagArray[99] = 2;
                    break;
                }
                case 3: {
                    flagArray[99] = 2;
                    break;
                }
                default: {
                    flagArray[99] = 0;
                    peer.setNestedScrollAttribute((undefined as NestedScrollOptions | NestedScrollOptionsExt | undefined));
                }
            }
        }
    }
    applyModifierPatch5(peer: ArkWebPeer, flagArray: Uint8Array): void {
        if (flagArray[100] != 0) {
            switch (flagArray[100]) {
                case 1: {
                    peer.setEnableNativeEmbedModeAttribute((this._Web_enableNativeEmbedMode_0_0value as boolean | undefined));
                    flagArray[100] = 2;
                    break;
                }
                case 3: {
                    flagArray[100] = 2;
                    break;
                }
                default: {
                    flagArray[100] = 0;
                    peer.setEnableNativeEmbedModeAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[101] != 0) {
            switch (flagArray[101]) {
                case 1: {
                    peer.setOnNativeEmbedLifecycleChangeAttribute((this._Web_onNativeEmbedLifecycleChange_0_0value as ((event: NativeEmbedDataInfo) => void) | undefined));
                    flagArray[101] = 2;
                    break;
                }
                case 3: {
                    flagArray[101] = 2;
                    break;
                }
                default: {
                    flagArray[101] = 0;
                    peer.setOnNativeEmbedLifecycleChangeAttribute((undefined as ((event: NativeEmbedDataInfo) => void) | undefined));
                }
            }
        }
        if (flagArray[102] != 0) {
            switch (flagArray[102]) {
                case 1: {
                    peer.setOnNativeEmbedVisibilityChangeAttribute((this._Web_onNativeEmbedVisibilityChange_0_0value as OnNativeEmbedVisibilityChangeCallback | undefined));
                    flagArray[102] = 2;
                    break;
                }
                case 3: {
                    flagArray[102] = 2;
                    break;
                }
                default: {
                    flagArray[102] = 0;
                    peer.setOnNativeEmbedVisibilityChangeAttribute((undefined as OnNativeEmbedVisibilityChangeCallback | undefined));
                }
            }
        }
        if (flagArray[103] != 0) {
            switch (flagArray[103]) {
                case 1: {
                    peer.setOnNativeEmbedGestureEventAttribute((this._Web_onNativeEmbedGestureEvent_0_0value as ((event: NativeEmbedTouchInfo) => void) | undefined));
                    flagArray[103] = 2;
                    break;
                }
                case 3: {
                    flagArray[103] = 2;
                    break;
                }
                default: {
                    flagArray[103] = 0;
                    peer.setOnNativeEmbedGestureEventAttribute((undefined as ((event: NativeEmbedTouchInfo) => void) | undefined));
                }
            }
        }
        if (flagArray[104] != 0) {
            switch (flagArray[104]) {
                case 1: {
                    peer.setOnNativeEmbedMouseEventAttribute((this._Web_onNativeEmbedMouseEvent_0_0value as MouseInfoCallback | undefined));
                    flagArray[104] = 2;
                    break;
                }
                case 3: {
                    flagArray[104] = 2;
                    break;
                }
                default: {
                    flagArray[104] = 0;
                    peer.setOnNativeEmbedMouseEventAttribute((undefined as MouseInfoCallback | undefined));
                }
            }
        }
        if (flagArray[105] != 0) {
            switch (flagArray[105]) {
                case 1: {
                    peer.setCopyOptionsAttribute((this._Web_copyOptions_0_0value as CopyOptions | undefined));
                    flagArray[105] = 2;
                    break;
                }
                case 3: {
                    flagArray[105] = 2;
                    break;
                }
                default: {
                    flagArray[105] = 0;
                    peer.setCopyOptionsAttribute((undefined as CopyOptions | undefined));
                }
            }
        }
        if (flagArray[106] != 0) {
            switch (flagArray[106]) {
                case 1: {
                    peer.setOnOverrideUrlLoadingAttribute((this._Web_onOverrideUrlLoading_0_0value as OnOverrideUrlLoadingCallback | undefined));
                    flagArray[106] = 2;
                    break;
                }
                case 3: {
                    flagArray[106] = 2;
                    break;
                }
                default: {
                    flagArray[106] = 0;
                    peer.setOnOverrideUrlLoadingAttribute((undefined as OnOverrideUrlLoadingCallback | undefined));
                }
            }
        }
        if (flagArray[107] != 0) {
            switch (flagArray[107]) {
                case 1: {
                    peer.setOnOverrideErrorPageAttribute((this._Web_onOverrideErrorPage_0_0value as OnOverrideErrorPageCallback | undefined));
                    flagArray[107] = 2;
                    break;
                }
                case 3: {
                    flagArray[107] = 2;
                    break;
                }
                default: {
                    flagArray[107] = 0;
                    peer.setOnOverrideErrorPageAttribute((undefined as OnOverrideErrorPageCallback | undefined));
                }
            }
        }
        if (flagArray[108] != 0) {
            switch (flagArray[108]) {
                case 1: {
                    peer.setTextAutosizingAttribute((this._Web_textAutosizing_0_0value as boolean | undefined));
                    flagArray[108] = 2;
                    break;
                }
                case 3: {
                    flagArray[108] = 2;
                    break;
                }
                default: {
                    flagArray[108] = 0;
                    peer.setTextAutosizingAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[109] != 0) {
            switch (flagArray[109]) {
                case 1: {
                    peer.setEnableNativeMediaPlayerAttribute((this._Web_enableNativeMediaPlayer_0_0value as NativeMediaPlayerConfig | undefined));
                    flagArray[109] = 2;
                    break;
                }
                case 3: {
                    flagArray[109] = 2;
                    break;
                }
                default: {
                    flagArray[109] = 0;
                    peer.setEnableNativeMediaPlayerAttribute((undefined as NativeMediaPlayerConfig | undefined));
                }
            }
        }
        if (flagArray[110] != 0) {
            switch (flagArray[110]) {
                case 1: {
                    peer.setOnRenderProcessNotRespondingAttribute((this._Web_onRenderProcessNotResponding_0_0value as OnRenderProcessNotRespondingCallback | undefined));
                    flagArray[110] = 2;
                    break;
                }
                case 3: {
                    flagArray[110] = 2;
                    break;
                }
                default: {
                    flagArray[110] = 0;
                    peer.setOnRenderProcessNotRespondingAttribute((undefined as OnRenderProcessNotRespondingCallback | undefined));
                }
            }
        }
        if (flagArray[111] != 0) {
            switch (flagArray[111]) {
                case 1: {
                    peer.setOnRenderProcessRespondingAttribute((this._Web_onRenderProcessResponding_0_0value as OnRenderProcessRespondingCallback | undefined));
                    flagArray[111] = 2;
                    break;
                }
                case 3: {
                    flagArray[111] = 2;
                    break;
                }
                default: {
                    flagArray[111] = 0;
                    peer.setOnRenderProcessRespondingAttribute((undefined as OnRenderProcessRespondingCallback | undefined));
                }
            }
        }
        if (flagArray[112] != 0) {
            switch (flagArray[112]) {
                case 1: {
                    peer.setOnViewportFitChangedAttribute((this._Web_onViewportFitChanged_0_0value as OnViewportFitChangedCallback | undefined));
                    flagArray[112] = 2;
                    break;
                }
                case 3: {
                    flagArray[112] = 2;
                    break;
                }
                default: {
                    flagArray[112] = 0;
                    peer.setOnViewportFitChangedAttribute((undefined as OnViewportFitChangedCallback | undefined));
                }
            }
        }
        if (flagArray[113] != 0) {
            switch (flagArray[113]) {
                case 1: {
                    peer.setOnInterceptKeyboardAttachAttribute((this._Web_onInterceptKeyboardAttach_0_0value as WebKeyboardCallback | undefined));
                    flagArray[113] = 2;
                    break;
                }
                case 3: {
                    flagArray[113] = 2;
                    break;
                }
                default: {
                    flagArray[113] = 0;
                    peer.setOnInterceptKeyboardAttachAttribute((undefined as WebKeyboardCallback | undefined));
                }
            }
        }
        if (flagArray[114] != 0) {
            switch (flagArray[114]) {
                case 1: {
                    peer.setOnAdsBlockedAttribute((this._Web_onAdsBlocked_0_0value as OnAdsBlockedCallback | undefined));
                    flagArray[114] = 2;
                    break;
                }
                case 3: {
                    flagArray[114] = 2;
                    break;
                }
                default: {
                    flagArray[114] = 0;
                    peer.setOnAdsBlockedAttribute((undefined as OnAdsBlockedCallback | undefined));
                }
            }
        }
        if (flagArray[115] != 0) {
            switch (flagArray[115]) {
                case 1: {
                    peer.setKeyboardAvoidModeAttribute((this._Web_keyboardAvoidMode_0_0value as WebKeyboardAvoidMode | undefined));
                    flagArray[115] = 2;
                    break;
                }
                case 3: {
                    flagArray[115] = 2;
                    break;
                }
                default: {
                    flagArray[115] = 0;
                    peer.setKeyboardAvoidModeAttribute((undefined as WebKeyboardAvoidMode | undefined));
                }
            }
        }
        if (flagArray[116] != 0) {
            switch (flagArray[116]) {
                case 1: {
                    peer.setEditMenuOptionsAttribute((this._Web_editMenuOptions_0_0value as EditMenuOptions | undefined));
                    flagArray[116] = 2;
                    break;
                }
                case 3: {
                    flagArray[116] = 2;
                    break;
                }
                default: {
                    flagArray[116] = 0;
                    peer.setEditMenuOptionsAttribute((undefined as EditMenuOptions | undefined));
                }
            }
        }
        if (flagArray[117] != 0) {
            switch (flagArray[117]) {
                case 1: {
                    peer.setEnableHapticFeedbackAttribute((this._Web_enableHapticFeedback_0_0value as boolean | undefined));
                    flagArray[117] = 2;
                    break;
                }
                case 3: {
                    flagArray[117] = 2;
                    break;
                }
                default: {
                    flagArray[117] = 0;
                    peer.setEnableHapticFeedbackAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[118] != 0) {
            switch (flagArray[118]) {
                case 1: {
                    peer.setEnableFollowSystemFontWeightAttribute((this._Web_enableFollowSystemFontWeight_0_0value as boolean | undefined));
                    flagArray[118] = 2;
                    break;
                }
                case 3: {
                    flagArray[118] = 2;
                    break;
                }
                default: {
                    flagArray[118] = 0;
                    peer.setEnableFollowSystemFontWeightAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[119] != 0) {
            switch (flagArray[119]) {
                case 1: {
                    peer.setEnableWebAVSessionAttribute((this._Web_enableWebAVSession_0_0value as boolean | undefined));
                    flagArray[119] = 2;
                    break;
                }
                case 3: {
                    flagArray[119] = 2;
                    break;
                }
                default: {
                    flagArray[119] = 0;
                    peer.setEnableWebAVSessionAttribute((undefined as boolean | undefined));
                }
            }
        }
    }
    applyModifierPatch6(peer: ArkWebPeer, flagArray: Uint8Array): void {
        if (flagArray[120] != 0) {
            switch (flagArray[120]) {
                case 1: {
                    peer.setOptimizeParserBudgetAttribute((this._Web_optimizeParserBudget_0_0value as boolean | undefined));
                    flagArray[120] = 2;
                    break;
                }
                case 3: {
                    flagArray[120] = 2;
                    break;
                }
                default: {
                    flagArray[120] = 0;
                    peer.setOptimizeParserBudgetAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[121] != 0) {
            switch (flagArray[121]) {
                case 1: {
                    peer.setRunJavaScriptOnDocumentStartAttribute((this._Web_runJavaScriptOnDocumentStart_0_0value as Array<ScriptItem> | undefined));
                    flagArray[121] = 2;
                    break;
                }
                case 3: {
                    flagArray[121] = 2;
                    break;
                }
                default: {
                    flagArray[121] = 0;
                    peer.setRunJavaScriptOnDocumentStartAttribute((undefined as Array<ScriptItem> | undefined));
                }
            }
        }
        if (flagArray[122] != 0) {
            switch (flagArray[122]) {
                case 1: {
                    peer.setRunJavaScriptOnDocumentEndAttribute((this._Web_runJavaScriptOnDocumentEnd_0_0value as Array<ScriptItem> | undefined));
                    flagArray[122] = 2;
                    break;
                }
                case 3: {
                    flagArray[122] = 2;
                    break;
                }
                default: {
                    flagArray[122] = 0;
                    peer.setRunJavaScriptOnDocumentEndAttribute((undefined as Array<ScriptItem> | undefined));
                }
            }
        }
        if (flagArray[123] != 0) {
            switch (flagArray[123]) {
                case 1: {
                    peer.setRunJavaScriptOnHeadEndAttribute((this._Web_runJavaScriptOnHeadEnd_0_0value as Array<ScriptItem> | undefined));
                    flagArray[123] = 2;
                    break;
                }
                case 3: {
                    flagArray[123] = 2;
                    break;
                }
                default: {
                    flagArray[123] = 0;
                    peer.setRunJavaScriptOnHeadEndAttribute((undefined as Array<ScriptItem> | undefined));
                }
            }
        }
        if (flagArray[124] != 0) {
            switch (flagArray[124]) {
                case 1: {
                    peer.setNativeEmbedOptionsAttribute((this._Web_nativeEmbedOptions_0_0value as EmbedOptions | undefined));
                    flagArray[124] = 2;
                    break;
                }
                case 3: {
                    flagArray[124] = 2;
                    break;
                }
                default: {
                    flagArray[124] = 0;
                    peer.setNativeEmbedOptionsAttribute((undefined as EmbedOptions | undefined));
                }
            }
        }
        if (flagArray[125] != 0) {
            switch (flagArray[125]) {
                case 1: {
                    peer.setEnableDataDetectorAttribute((this._Web_enableDataDetector_0_0value as boolean | undefined));
                    flagArray[125] = 2;
                    break;
                }
                case 3: {
                    flagArray[125] = 2;
                    break;
                }
                default: {
                    flagArray[125] = 0;
                    peer.setEnableDataDetectorAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[126] != 0) {
            switch (flagArray[126]) {
                case 1: {
                    peer.setDataDetectorConfigAttribute((this._Web_dataDetectorConfig_0_0value as TextDataDetectorConfig | undefined));
                    flagArray[126] = 2;
                    break;
                }
                case 3: {
                    flagArray[126] = 2;
                    break;
                }
                default: {
                    flagArray[126] = 0;
                    peer.setDataDetectorConfigAttribute((undefined as TextDataDetectorConfig | undefined));
                }
            }
        }
        if (flagArray[127] != 0) {
            switch (flagArray[127]) {
                case 1: {
                    peer.setOnActivateContentAttribute((this._Web_onActivateContent_0_0value as VoidCallback | undefined));
                    flagArray[127] = 2;
                    break;
                }
                case 3: {
                    flagArray[127] = 2;
                    break;
                }
                default: {
                    flagArray[127] = 0;
                    peer.setOnActivateContentAttribute((undefined as VoidCallback | undefined));
                }
            }
        }
        if (flagArray[128] != 0) {
            switch (flagArray[128]) {
                case 1: {
                    peer.setBypassVsyncConditionAttribute((this._Web_bypassVsyncCondition_0_0value as WebBypassVsyncCondition | undefined));
                    flagArray[128] = 2;
                    break;
                }
                case 3: {
                    flagArray[128] = 2;
                    break;
                }
                default: {
                    flagArray[128] = 0;
                    peer.setBypassVsyncConditionAttribute((undefined as WebBypassVsyncCondition | undefined));
                }
            }
        }
        if (flagArray[129] != 0) {
            switch (flagArray[129]) {
                case 1: {
                    peer.setGestureFocusModeAttribute((this._Web_gestureFocusMode_0_0value as GestureFocusMode | undefined));
                    flagArray[129] = 2;
                    break;
                }
                case 3: {
                    flagArray[129] = 2;
                    break;
                }
                default: {
                    flagArray[129] = 0;
                    peer.setGestureFocusModeAttribute((undefined as GestureFocusMode | undefined));
                }
            }
        }
        if (flagArray[130] != 0) {
            switch (flagArray[130]) {
                case 1: {
                    peer.setForceEnableZoomAttribute((this._Web_forceEnableZoom_0_0value as boolean | undefined));
                    flagArray[130] = 2;
                    break;
                }
                case 3: {
                    flagArray[130] = 2;
                    break;
                }
                default: {
                    flagArray[130] = 0;
                    peer.setForceEnableZoomAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[131] != 0) {
            switch (flagArray[131]) {
                case 1: {
                    peer.setOnNativeEmbedObjectParamChangeAttribute((this._Web_onNativeEmbedObjectParamChange_0_0value as OnNativeEmbedObjectParamChangeCallback | undefined));
                    flagArray[131] = 2;
                    break;
                }
                case 3: {
                    flagArray[131] = 2;
                    break;
                }
                default: {
                    flagArray[131] = 0;
                    peer.setOnNativeEmbedObjectParamChangeAttribute((undefined as OnNativeEmbedObjectParamChangeCallback | undefined));
                }
            }
        }
        if (flagArray[132] != 0) {
            switch (flagArray[132]) {
                case 1: {
                    peer.setRotateRenderEffectAttribute((this._Web_rotateRenderEffect_0_0value as WebRotateEffect | undefined));
                    flagArray[132] = 2;
                    break;
                }
                case 3: {
                    flagArray[132] = 2;
                    break;
                }
                default: {
                    flagArray[132] = 0;
                    peer.setRotateRenderEffectAttribute((undefined as WebRotateEffect | undefined));
                }
            }
        }
        if (flagArray[133] != 0) {
            switch (flagArray[133]) {
                case 1: {
                    peer.setZoomControlAccessAttribute((this._Web_zoomControlAccess_0_0value as boolean | undefined));
                    flagArray[133] = 2;
                    break;
                }
                case 3: {
                    flagArray[133] = 2;
                    break;
                }
                default: {
                    flagArray[133] = 0;
                    peer.setZoomControlAccessAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[134] != 0) {
            switch (flagArray[134]) {
                case 1: {
                    peer.setOnDetectedBlankScreenAttribute((this._Web_onDetectedBlankScreen_0_0value as OnDetectBlankScreenCallback | undefined));
                    flagArray[134] = 2;
                    break;
                }
                case 3: {
                    flagArray[134] = 2;
                    break;
                }
                default: {
                    flagArray[134] = 0;
                    peer.setOnDetectedBlankScreenAttribute((undefined as OnDetectBlankScreenCallback | undefined));
                }
            }
        }
        if (flagArray[135] != 0) {
            switch (flagArray[135]) {
                case 1: {
                    peer.setBlankScreenDetectionConfigAttribute((this._Web_blankScreenDetectionConfig_0_0value as BlankScreenDetectionConfig | undefined));
                    flagArray[135] = 2;
                    break;
                }
                case 3: {
                    flagArray[135] = 2;
                    break;
                }
                default: {
                    flagArray[135] = 0;
                    peer.setBlankScreenDetectionConfigAttribute((undefined as BlankScreenDetectionConfig | undefined));
                }
            }
        }
        if (flagArray[136] != 0) {
            switch (flagArray[136]) {
                case 1: {
                    peer.setBackToTopAttribute((this._Web_backToTop_0_0value as boolean | undefined));
                    flagArray[136] = 2;
                    break;
                }
                case 3: {
                    flagArray[136] = 2;
                    break;
                }
                default: {
                    flagArray[136] = 0;
                    peer.setBackToTopAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[137] != 0) {
            switch (flagArray[137]) {
                case 1: {
                    peer.setEnableSelectedDataDetectorAttribute((this._Web_enableSelectedDataDetector_0_0value as boolean | undefined));
                    flagArray[137] = 2;
                    break;
                }
                case 3: {
                    flagArray[137] = 2;
                    break;
                }
                default: {
                    flagArray[137] = 0;
                    peer.setEnableSelectedDataDetectorAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[138] != 0) {
            switch (flagArray[138]) {
                case 1: {
                    peer.setOnFirstScreenPaintAttribute((this._Web_onFirstScreenPaint_0_0value as OnFirstScreenPaintCallback | undefined));
                    flagArray[138] = 2;
                    break;
                }
                case 3: {
                    flagArray[138] = 2;
                    break;
                }
                default: {
                    flagArray[138] = 0;
                    peer.setOnFirstScreenPaintAttribute((undefined as OnFirstScreenPaintCallback | undefined));
                }
            }
        }
        if (flagArray[139] != 0) {
            switch (flagArray[139]) {
                case 1: {
                    peer.setEnableAutoFillAttribute((this._Web_enableAutoFill_0_0value as boolean | undefined));
                    flagArray[139] = 2;
                    break;
                }
                case 3: {
                    flagArray[139] = 2;
                    break;
                }
                default: {
                    flagArray[139] = 0;
                    peer.setEnableAutoFillAttribute((undefined as boolean | undefined));
                }
            }
        }
    }
    applyModifierPatch7(peer: ArkWebPeer, flagArray: Uint8Array): void {
        if (flagArray[140] != 0) {
            switch (flagArray[140]) {
                case 1: {
                    peer.setOnTextSelectionChangeAttribute((this._Web_onTextSelectionChange_0_0value as TextSelectionChangeCallback | undefined));
                    flagArray[140] = 2;
                    break;
                }
                case 3: {
                    flagArray[140] = 2;
                    break;
                }
                default: {
                    flagArray[140] = 0;
                    peer.setOnTextSelectionChangeAttribute((undefined as TextSelectionChangeCallback | undefined));
                }
            }
        }
        if (flagArray[141] != 0) {
            switch (flagArray[141]) {
                case 1: {
                    peer.setEnableImageAnalyzerAttribute((this._Web_enableImageAnalyzer_0_0value as boolean | undefined));
                    flagArray[141] = 2;
                    break;
                }
                case 3: {
                    flagArray[141] = 2;
                    break;
                }
                default: {
                    flagArray[141] = 0;
                    peer.setEnableImageAnalyzerAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[142] != 0) {
            switch (flagArray[142]) {
                case 1: {
                    peer.setOnCameraCaptureStateChangeAttribute((this._Web_onCameraCaptureStateChange_0_0value as OnCameraCaptureStateChangeCallback | undefined));
                    flagArray[142] = 2;
                    break;
                }
                case 3: {
                    flagArray[142] = 2;
                    break;
                }
                default: {
                    flagArray[142] = 0;
                    peer.setOnCameraCaptureStateChangeAttribute((undefined as OnCameraCaptureStateChangeCallback | undefined));
                }
            }
        }
        if (flagArray[143] != 0) {
            switch (flagArray[143]) {
                case 1: {
                    peer.setOnMicrophoneCaptureStateChangeAttribute((this._Web_onMicrophoneCaptureStateChange_0_0value as OnMicrophoneCaptureStateChangeCallback | undefined));
                    flagArray[143] = 2;
                    break;
                }
                case 3: {
                    flagArray[143] = 2;
                    break;
                }
                default: {
                    flagArray[143] = 0;
                    peer.setOnMicrophoneCaptureStateChangeAttribute((undefined as OnMicrophoneCaptureStateChangeCallback | undefined));
                }
            }
        }
        if (flagArray[144] != 0) {
            switch (flagArray[144]) {
                case 1: {
                    peer.setEnableDefaultContextMenuAttribute((this._Web_enableDefaultContextMenu_0_0value as boolean | undefined));
                    flagArray[144] = 2;
                    break;
                }
                case 3: {
                    flagArray[144] = 2;
                    break;
                }
                default: {
                    flagArray[144] = 0;
                    peer.setEnableDefaultContextMenuAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[145] != 0) {
            switch (flagArray[145]) {
                case 1: {
                    peer.setEnableDragAttribute((this._Web_enableDrag_0_0value as boolean | undefined));
                    flagArray[145] = 2;
                    break;
                }
                case 3: {
                    flagArray[145] = 2;
                    break;
                }
                default: {
                    flagArray[145] = 0;
                    peer.setEnableDragAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[146] != 0) {
            switch (flagArray[146]) {
                case 1: {
                    peer.setScrollbarLayoutPolicyAttribute((this._Web_scrollbarLayoutPolicy_0_0value as ScrollbarLayoutPolicy | undefined));
                    flagArray[146] = 2;
                    break;
                }
                case 3: {
                    flagArray[146] = 2;
                    break;
                }
                default: {
                    flagArray[146] = 0;
                    peer.setScrollbarLayoutPolicyAttribute((undefined as ScrollbarLayoutPolicy | undefined));
                }
            }
        }
        if (flagArray[147] != 0) {
            switch (flagArray[147]) {
                case 1: {
                    peer.setAiSessionOptionsAttribute((this._Web_aiSessionOptions_0_0value as Array<AISessionEvent> | undefined));
                    flagArray[147] = 2;
                    break;
                }
                case 3: {
                    flagArray[147] = 2;
                    break;
                }
                default: {
                    flagArray[147] = 0;
                    peer.setAiSessionOptionsAttribute((undefined as Array<AISessionEvent> | undefined));
                }
            }
        }
        if (flagArray[148] != 0) {
            switch (flagArray[148]) {
                case 1: {
                    peer.setKeyboardAppearanceAttribute((this._Web_keyboardAppearance_0_0value as WebKeyboardAppearanceMode | undefined));
                    flagArray[148] = 2;
                    break;
                }
                case 3: {
                    flagArray[148] = 2;
                    break;
                }
                default: {
                    flagArray[148] = 0;
                    peer.setKeyboardAppearanceAttribute((undefined as WebKeyboardAppearanceMode | undefined));
                }
            }
        }
        if (flagArray[149] != 0) {
            switch (flagArray[149]) {
                case 1: {
                    peer.setOnInputmethodAttachedAttribute((this._Web_onInputmethodAttached_0_0value as OnInputmethodAttachedCallback | undefined));
                    flagArray[149] = 2;
                    break;
                }
                case 3: {
                    flagArray[149] = 2;
                    break;
                }
                default: {
                    flagArray[149] = 0;
                    peer.setOnInputmethodAttachedAttribute((undefined as OnInputmethodAttachedCallback | undefined));
                }
            }
        }
        if (flagArray[150] != 0) {
            switch (flagArray[150]) {
                case 1: {
                    peer.setRegisterNativeEmbedRuleAttribute((this._Web_registerNativeEmbedRule_0_0value as string | undefined), (this._Web_registerNativeEmbedRule_0_1value as string | undefined));
                    flagArray[150] = 2;
                    break;
                }
                case 3: {
                    flagArray[150] = 2;
                    break;
                }
                default: {
                    flagArray[150] = 0;
                    peer.setRegisterNativeEmbedRuleAttribute((undefined as string | undefined), (undefined as string | undefined));
                }
            }
        }
        if (flagArray[151] != 0) {
            switch (flagArray[151]) {
                case 1: {
                    peer.setBindSelectionMenuAttribute((this._Web_bindSelectionMenu_0_0value as WebElementType | undefined), (this._Web_bindSelectionMenu_0_1value as CustomBuilder | undefined), (this._Web_bindSelectionMenu_0_2value as WebResponseType | undefined), (this._Web_bindSelectionMenu_0_3value as SelectionMenuOptionsExt | undefined | undefined));
                    flagArray[151] = 2;
                    break;
                }
                case 3: {
                    flagArray[151] = 2;
                    break;
                }
                default: {
                    flagArray[151] = 0;
                    peer.setBindSelectionMenuAttribute((undefined as WebElementType | undefined), (undefined as CustomBuilder | undefined), (undefined as WebResponseType | undefined), (undefined as SelectionMenuOptionsExt | undefined | undefined));
                }
            }
        }
        if (flagArray[152] != 0) {
            switch (flagArray[152]) {
                case 1: {
                    peer.setEnableScrollDirectionalLockAttribute((this._Web_enableScrollDirectionalLock_0_0value as boolean | undefined), (this._Web_enableScrollDirectionalLock_0_1value as ScrollDirectionalLockType | undefined));
                    flagArray[152] = 2;
                    break;
                }
                case 3: {
                    flagArray[152] = 2;
                    break;
                }
                default: {
                    flagArray[152] = 0;
                    peer.setEnableScrollDirectionalLockAttribute((undefined as boolean | undefined), (undefined as ScrollDirectionalLockType | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: WebModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        const flagArray = modifier._Web_flagArray;
        this.mergeModifier0(modifier, flagArray);
        this.mergeModifier1(modifier, flagArray);
        this.mergeModifier2(modifier, flagArray);
        this.mergeModifier3(modifier, flagArray);
        this.mergeModifier4(modifier, flagArray);
        this.mergeModifier5(modifier, flagArray);
        this.mergeModifier6(modifier, flagArray);
        this.mergeModifier7(modifier, flagArray);
    }
    mergeModifier0(modifier: WebModifier, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1:
                case 3: {
                    this.javaScriptAccess((modifier._Web_javaScriptAccess_0_0value as boolean | undefined));
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
                    this.fileAccess((modifier._Web_fileAccess_0_0value as boolean | undefined));
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
                    this.onlineImageAccess((modifier._Web_onlineImageAccess_0_0value as boolean | undefined));
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
                    this.domStorageAccess((modifier._Web_domStorageAccess_0_0value as boolean | undefined));
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
                    this.imageAccess((modifier._Web_imageAccess_0_0value as boolean | undefined));
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
                    this.mixedMode((modifier._Web_mixedMode_0_0value as MixedMode | undefined));
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
                    this.zoomAccess((modifier._Web_zoomAccess_0_0value as boolean | undefined));
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
                    this.geolocationAccess((modifier._Web_geolocationAccess_0_0value as boolean | undefined));
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
                    this.javaScriptProxy((modifier._Web_javaScriptProxy_0_0value as JavaScriptProxy | undefined));
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
                    this.cacheMode((modifier._Web_cacheMode_0_0value as CacheMode | undefined));
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
                    this.darkMode((modifier._Web_darkMode_0_0value as WebDarkMode | undefined));
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
                    this.forceDarkAccess((modifier._Web_forceDarkAccess_0_0value as boolean | undefined));
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
                    this.mediaOptions((modifier._Web_mediaOptions_0_0value as WebMediaOptions | undefined));
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
                    this.overviewModeAccess((modifier._Web_overviewModeAccess_0_0value as boolean | undefined));
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
                    this.overScrollMode((modifier._Web_overScrollMode_0_0value as OverScrollMode | undefined));
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
                    this.blurOnKeyboardHideMode((modifier._Web_blurOnKeyboardHideMode_0_0value as BlurOnKeyboardHideMode | undefined));
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
                    this.textZoomRatio((modifier._Web_textZoomRatio_0_0value as int32 | undefined));
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
                    this.databaseAccess((modifier._Web_databaseAccess_0_0value as boolean | undefined));
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
                    this.initialScale((modifier._Web_initialScale_0_0value as double | undefined));
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
                    this.metaViewport((modifier._Web_metaViewport_0_0value as boolean | undefined));
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
                    this.onPageBegin((modifier._Web_onPageBegin_0_0value as arkui_component_common_Callback<OnPageBeginEvent, void> | undefined));
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
                    this.onPageEnd((modifier._Web_onPageEnd_0_0value as arkui_component_common_Callback<OnPageEndEvent, void> | undefined));
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
                    this.onLoadStarted((modifier._Web_onLoadStarted_0_0value as arkui_component_common_Callback<OnLoadStartedEvent, void> | undefined));
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
                    this.onLoadFinished((modifier._Web_onLoadFinished_0_0value as arkui_component_common_Callback<OnLoadFinishedEvent, void> | undefined));
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
                    this.onProgressChange((modifier._Web_onProgressChange_0_0value as arkui_component_common_Callback<OnProgressChangeEvent, void> | undefined));
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
                    this.onTitleReceive((modifier._Web_onTitleReceive_0_0value as arkui_component_common_Callback<OnTitleReceiveEvent, void> | undefined));
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
                    this.onGeolocationHide((modifier._Web_onGeolocationHide_0_0value as (() => void) | undefined));
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
                    this.onGeolocationShow((modifier._Web_onGeolocationShow_0_0value as arkui_component_common_Callback<OnGeolocationShowEvent, void> | undefined));
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
                    this.onRequestSelected((modifier._Web_onRequestSelected_0_0value as (() => void) | undefined));
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
                    this.onAlert((modifier._Web_onAlert_0_0value as arkui_component_common_Callback<OnAlertEvent, boolean> | undefined));
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
                    this.onBeforeUnload((modifier._Web_onBeforeUnload_0_0value as arkui_component_common_Callback<OnBeforeUnloadEvent, boolean> | undefined));
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
                    this.onConfirm((modifier._Web_onConfirm_0_0value as arkui_component_common_Callback<OnConfirmEvent, boolean> | undefined));
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
                    this.onPrompt((modifier._Web_onPrompt_0_0value as arkui_component_common_Callback<OnPromptEvent, boolean> | undefined));
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
                    this.onConsole((modifier._Web_onConsole_0_0value as arkui_component_common_Callback<OnConsoleEvent, boolean> | undefined));
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
                    this.onErrorReceive((modifier._Web_onErrorReceive_0_0value as arkui_component_common_Callback<OnErrorReceiveEvent, void> | undefined));
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
                    this.onHttpErrorReceive((modifier._Web_onHttpErrorReceive_0_0value as arkui_component_common_Callback<OnHttpErrorReceiveEvent, void> | undefined));
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
                    this.onDownloadStart((modifier._Web_onDownloadStart_0_0value as arkui_component_common_Callback<OnDownloadStartEvent, void> | undefined));
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
                    this.onRefreshAccessedHistory((modifier._Web_onRefreshAccessedHistory_0_0value as arkui_component_common_Callback<OnRefreshAccessedHistoryEvent, void> | undefined));
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
                    this.onRenderExited((modifier._Web_onRenderExited_0_0value as arkui_component_common_Callback<OnRenderExitedEvent, void> | undefined));
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
                    this.onShowFileSelector((modifier._Web_onShowFileSelector_0_0value as arkui_component_common_Callback<OnShowFileSelectorEvent, boolean> | undefined));
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
                    this.onResourceLoad((modifier._Web_onResourceLoad_0_0value as arkui_component_common_Callback<OnResourceLoadEvent, void> | undefined));
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
                    this.onFullScreenExit((modifier._Web_onFullScreenExit_0_0value as (() => void) | undefined));
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
                    this.onFullScreenEnter((modifier._Web_onFullScreenEnter_0_0value as OnFullScreenEnterCallback | undefined));
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
                    this.onScaleChange((modifier._Web_onScaleChange_0_0value as arkui_component_common_Callback<OnScaleChangeEvent, void> | undefined));
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
                    this.onHttpAuthRequest((modifier._Web_onHttpAuthRequest_0_0value as arkui_component_common_Callback<OnHttpAuthRequestEvent, boolean> | undefined));
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
                    this.onInterceptRequest((modifier._Web_onInterceptRequest_0_0value as arkui_component_common_Callback<OnInterceptRequestEvent, WebResourceResponse | null> | undefined));
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
                    this.onPermissionRequest((modifier._Web_onPermissionRequest_0_0value as arkui_component_common_Callback<OnPermissionRequestEvent, void> | undefined));
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
                    this.onScreenCaptureRequest((modifier._Web_onScreenCaptureRequest_0_0value as arkui_component_common_Callback<OnScreenCaptureRequestEvent, void> | undefined));
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
                    this.onContextMenuShow((modifier._Web_onContextMenuShow_0_0value as arkui_component_common_Callback<OnContextMenuShowEvent, boolean> | undefined));
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
                    this.onContextMenuHide((modifier._Web_onContextMenuHide_0_0value as OnContextMenuHideCallback | undefined));
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
                    this.mediaPlayGestureAccess((modifier._Web_mediaPlayGestureAccess_0_0value as boolean | undefined));
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
                    this.onSearchResultReceive((modifier._Web_onSearchResultReceive_0_0value as arkui_component_common_Callback<OnSearchResultReceiveEvent, void> | undefined));
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
                    this.onScroll((modifier._Web_onScroll_0_0value as arkui_component_common_Callback<OnScrollEvent, void> | undefined));
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
                    this.onSslErrorEventReceive((modifier._Web_onSslErrorEventReceive_0_0value as arkui_component_common_Callback<OnSslErrorEventReceiveEvent, void> | undefined));
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
                    this.onSslErrorEvent((modifier._Web_onSslErrorEvent_0_0value as OnSslErrorEventCallback | undefined));
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
                    this.onClientAuthenticationRequest((modifier._Web_onClientAuthenticationRequest_0_0value as arkui_component_common_Callback<OnClientAuthenticationEvent, void> | undefined));
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
                    this.onVerifyPin((modifier._Web_onVerifyPin_0_0value as OnVerifyPinCallback | undefined));
                    break;
                }
                default: {
                    this.onVerifyPin((undefined as OnVerifyPinCallback | undefined));
                }
            }
        }
        if (flagArray[57] != 0) {
            switch (flagArray[57]) {
                case 1:
                case 3: {
                    this.onWindowNew((modifier._Web_onWindowNew_0_0value as arkui_component_common_Callback<OnWindowNewEvent, void> | undefined));
                    break;
                }
                default: {
                    this.onWindowNew((undefined as arkui_component_common_Callback<OnWindowNewEvent, void> | undefined));
                }
            }
        }
        if (flagArray[58] != 0) {
            switch (flagArray[58]) {
                case 1:
                case 3: {
                    this.onWindowNewExt((modifier._Web_onWindowNewExt_0_0value as arkui_component_common_Callback<OnWindowNewExtEvent, void> | undefined));
                    break;
                }
                default: {
                    this.onWindowNewExt((undefined as arkui_component_common_Callback<OnWindowNewExtEvent, void> | undefined));
                }
            }
        }
        if (flagArray[59] != 0) {
            switch (flagArray[59]) {
                case 1:
                case 3: {
                    this.onWindowExit((modifier._Web_onWindowExit_0_0value as (() => void) | undefined));
                    break;
                }
                default: {
                    this.onWindowExit((undefined as (() => void) | undefined));
                }
            }
        }
    }
    mergeModifier3(modifier: WebModifier, flagArray: Uint8Array): void {
        if (flagArray[60] != 0) {
            switch (flagArray[60]) {
                case 1:
                case 3: {
                    this.multiWindowAccess((modifier._Web_multiWindowAccess_0_0value as boolean | undefined));
                    break;
                }
                default: {
                    this.multiWindowAccess((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[61] != 0) {
            switch (flagArray[61]) {
                case 1:
                case 3: {
                    this.onInterceptKeyEvent((modifier._Web_onInterceptKeyEvent_0_0value as ((event: KeyEvent) => boolean) | undefined));
                    break;
                }
                default: {
                    this.onInterceptKeyEvent((undefined as ((event: KeyEvent) => boolean) | undefined));
                }
            }
        }
        if (flagArray[62] != 0) {
            switch (flagArray[62]) {
                case 1:
                case 3: {
                    this.webStandardFont((modifier._Web_webStandardFont_0_0value as string | undefined));
                    break;
                }
                default: {
                    this.webStandardFont((undefined as string | undefined));
                }
            }
        }
        if (flagArray[63] != 0) {
            switch (flagArray[63]) {
                case 1:
                case 3: {
                    this.webSerifFont((modifier._Web_webSerifFont_0_0value as string | undefined));
                    break;
                }
                default: {
                    this.webSerifFont((undefined as string | undefined));
                }
            }
        }
        if (flagArray[64] != 0) {
            switch (flagArray[64]) {
                case 1:
                case 3: {
                    this.webSansSerifFont((modifier._Web_webSansSerifFont_0_0value as string | undefined));
                    break;
                }
                default: {
                    this.webSansSerifFont((undefined as string | undefined));
                }
            }
        }
        if (flagArray[65] != 0) {
            switch (flagArray[65]) {
                case 1:
                case 3: {
                    this.webFixedFont((modifier._Web_webFixedFont_0_0value as string | undefined));
                    break;
                }
                default: {
                    this.webFixedFont((undefined as string | undefined));
                }
            }
        }
        if (flagArray[66] != 0) {
            switch (flagArray[66]) {
                case 1:
                case 3: {
                    this.webFantasyFont((modifier._Web_webFantasyFont_0_0value as string | undefined));
                    break;
                }
                default: {
                    this.webFantasyFont((undefined as string | undefined));
                }
            }
        }
        if (flagArray[67] != 0) {
            switch (flagArray[67]) {
                case 1:
                case 3: {
                    this.webCursiveFont((modifier._Web_webCursiveFont_0_0value as string | undefined));
                    break;
                }
                default: {
                    this.webCursiveFont((undefined as string | undefined));
                }
            }
        }
        if (flagArray[68] != 0) {
            switch (flagArray[68]) {
                case 1:
                case 3: {
                    this.defaultFixedFontSize((modifier._Web_defaultFixedFontSize_0_0value as int32 | undefined));
                    break;
                }
                default: {
                    this.defaultFixedFontSize((undefined as int32 | undefined));
                }
            }
        }
        if (flagArray[69] != 0) {
            switch (flagArray[69]) {
                case 1:
                case 3: {
                    this.defaultFontSize((modifier._Web_defaultFontSize_0_0value as int32 | undefined));
                    break;
                }
                default: {
                    this.defaultFontSize((undefined as int32 | undefined));
                }
            }
        }
        if (flagArray[70] != 0) {
            switch (flagArray[70]) {
                case 1:
                case 3: {
                    this.minFontSize((modifier._Web_minFontSize_0_0value as int32 | undefined));
                    break;
                }
                default: {
                    this.minFontSize((undefined as int32 | undefined));
                }
            }
        }
        if (flagArray[71] != 0) {
            switch (flagArray[71]) {
                case 1:
                case 3: {
                    this.minLogicalFontSize((modifier._Web_minLogicalFontSize_0_0value as int32 | undefined));
                    break;
                }
                default: {
                    this.minLogicalFontSize((undefined as int32 | undefined));
                }
            }
        }
        if (flagArray[72] != 0) {
            switch (flagArray[72]) {
                case 1:
                case 3: {
                    this.defaultTextEncodingFormat((modifier._Web_defaultTextEncodingFormat_0_0value as string | undefined));
                    break;
                }
                default: {
                    this.defaultTextEncodingFormat((undefined as string | undefined));
                }
            }
        }
        if (flagArray[73] != 0) {
            switch (flagArray[73]) {
                case 1:
                case 3: {
                    this.forceDisplayScrollBar((modifier._Web_forceDisplayScrollBar_0_0value as boolean | undefined));
                    break;
                }
                default: {
                    this.forceDisplayScrollBar((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[74] != 0) {
            switch (flagArray[74]) {
                case 1:
                case 3: {
                    this.blockNetwork((modifier._Web_blockNetwork_0_0value as boolean | undefined));
                    break;
                }
                default: {
                    this.blockNetwork((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[75] != 0) {
            switch (flagArray[75]) {
                case 1:
                case 3: {
                    this.horizontalScrollBarAccess((modifier._Web_horizontalScrollBarAccess_0_0value as boolean | undefined));
                    break;
                }
                default: {
                    this.horizontalScrollBarAccess((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[76] != 0) {
            switch (flagArray[76]) {
                case 1:
                case 3: {
                    this.verticalScrollBarAccess((modifier._Web_verticalScrollBarAccess_0_0value as boolean | undefined));
                    break;
                }
                default: {
                    this.verticalScrollBarAccess((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[77] != 0) {
            switch (flagArray[77]) {
                case 1:
                case 3: {
                    this.onTouchIconUrlReceived((modifier._Web_onTouchIconUrlReceived_0_0value as arkui_component_common_Callback<OnTouchIconUrlReceivedEvent, void> | undefined));
                    break;
                }
                default: {
                    this.onTouchIconUrlReceived((undefined as arkui_component_common_Callback<OnTouchIconUrlReceivedEvent, void> | undefined));
                }
            }
        }
        if (flagArray[78] != 0) {
            switch (flagArray[78]) {
                case 1:
                case 3: {
                    this.onFaviconReceived((modifier._Web_onFaviconReceived_0_0value as arkui_component_common_Callback<OnFaviconReceivedEvent, void> | undefined));
                    break;
                }
                default: {
                    this.onFaviconReceived((undefined as arkui_component_common_Callback<OnFaviconReceivedEvent, void> | undefined));
                }
            }
        }
        if (flagArray[79] != 0) {
            switch (flagArray[79]) {
                case 1:
                case 3: {
                    this.onPageVisible((modifier._Web_onPageVisible_0_0value as arkui_component_common_Callback<OnPageVisibleEvent, void> | undefined));
                    break;
                }
                default: {
                    this.onPageVisible((undefined as arkui_component_common_Callback<OnPageVisibleEvent, void> | undefined));
                }
            }
        }
    }
    mergeModifier4(modifier: WebModifier, flagArray: Uint8Array): void {
        if (flagArray[80] != 0) {
            switch (flagArray[80]) {
                case 1:
                case 3: {
                    this.onDataResubmitted((modifier._Web_onDataResubmitted_0_0value as arkui_component_common_Callback<OnDataResubmittedEvent, void> | undefined));
                    break;
                }
                default: {
                    this.onDataResubmitted((undefined as arkui_component_common_Callback<OnDataResubmittedEvent, void> | undefined));
                }
            }
        }
        if (flagArray[81] != 0) {
            switch (flagArray[81]) {
                case 1:
                case 3: {
                    this.pinchSmooth((modifier._Web_pinchSmooth_0_0value as boolean | undefined));
                    break;
                }
                default: {
                    this.pinchSmooth((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[82] != 0) {
            switch (flagArray[82]) {
                case 1:
                case 3: {
                    this.allowWindowOpenMethod((modifier._Web_allowWindowOpenMethod_0_0value as boolean | undefined));
                    break;
                }
                default: {
                    this.allowWindowOpenMethod((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[83] != 0) {
            switch (flagArray[83]) {
                case 1:
                case 3: {
                    this.onAudioStateChanged((modifier._Web_onAudioStateChanged_0_0value as arkui_component_common_Callback<OnAudioStateChangedEvent, void> | undefined));
                    break;
                }
                default: {
                    this.onAudioStateChanged((undefined as arkui_component_common_Callback<OnAudioStateChangedEvent, void> | undefined));
                }
            }
        }
        if (flagArray[84] != 0) {
            switch (flagArray[84]) {
                case 1:
                case 3: {
                    this.onFirstContentfulPaint((modifier._Web_onFirstContentfulPaint_0_0value as arkui_component_common_Callback<OnFirstContentfulPaintEvent, void> | undefined));
                    break;
                }
                default: {
                    this.onFirstContentfulPaint((undefined as arkui_component_common_Callback<OnFirstContentfulPaintEvent, void> | undefined));
                }
            }
        }
        if (flagArray[85] != 0) {
            switch (flagArray[85]) {
                case 1:
                case 3: {
                    this.onFirstMeaningfulPaint((modifier._Web_onFirstMeaningfulPaint_0_0value as OnFirstMeaningfulPaintCallback | undefined));
                    break;
                }
                default: {
                    this.onFirstMeaningfulPaint((undefined as OnFirstMeaningfulPaintCallback | undefined));
                }
            }
        }
        if (flagArray[86] != 0) {
            switch (flagArray[86]) {
                case 1:
                case 3: {
                    this.onLargestContentfulPaint((modifier._Web_onLargestContentfulPaint_0_0value as OnLargestContentfulPaintCallback | undefined));
                    break;
                }
                default: {
                    this.onLargestContentfulPaint((undefined as OnLargestContentfulPaintCallback | undefined));
                }
            }
        }
        if (flagArray[87] != 0) {
            switch (flagArray[87]) {
                case 1:
                case 3: {
                    this.onLoadIntercept((modifier._Web_onLoadIntercept_0_0value as arkui_component_common_Callback<OnLoadInterceptEvent, boolean> | undefined));
                    break;
                }
                default: {
                    this.onLoadIntercept((undefined as arkui_component_common_Callback<OnLoadInterceptEvent, boolean> | undefined));
                }
            }
        }
        if (flagArray[88] != 0) {
            switch (flagArray[88]) {
                case 1:
                case 3: {
                    this.onControllerAttached((modifier._Web_onControllerAttached_0_0value as (() => void) | undefined));
                    break;
                }
                default: {
                    this.onControllerAttached((undefined as (() => void) | undefined));
                }
            }
        }
        if (flagArray[89] != 0) {
            switch (flagArray[89]) {
                case 1:
                case 3: {
                    this.onOverScroll((modifier._Web_onOverScroll_0_0value as arkui_component_common_Callback<OnOverScrollEvent, void> | undefined));
                    break;
                }
                default: {
                    this.onOverScroll((undefined as arkui_component_common_Callback<OnOverScrollEvent, void> | undefined));
                }
            }
        }
        if (flagArray[90] != 0) {
            switch (flagArray[90]) {
                case 1:
                case 3: {
                    this.onPdfScrollAtBottom((modifier._Web_onPdfScrollAtBottom_0_0value as arkui_component_common_Callback<OnPdfScrollEvent, void> | undefined));
                    break;
                }
                default: {
                    this.onPdfScrollAtBottom((undefined as arkui_component_common_Callback<OnPdfScrollEvent, void> | undefined));
                }
            }
        }
        if (flagArray[91] != 0) {
            switch (flagArray[91]) {
                case 1:
                case 3: {
                    this.onPdfLoadEvent((modifier._Web_onPdfLoadEvent_0_0value as arkui_component_common_Callback<OnPdfLoadEvent, void> | undefined));
                    break;
                }
                default: {
                    this.onPdfLoadEvent((undefined as arkui_component_common_Callback<OnPdfLoadEvent, void> | undefined));
                }
            }
        }
        if (flagArray[92] != 0) {
            switch (flagArray[92]) {
                case 1:
                case 3: {
                    this.onSafeBrowsingCheckResult((modifier._Web_onSafeBrowsingCheckResult_0_0value as OnSafeBrowsingCheckResultCallback | undefined));
                    break;
                }
                default: {
                    this.onSafeBrowsingCheckResult((undefined as OnSafeBrowsingCheckResultCallback | undefined));
                }
            }
        }
        if (flagArray[93] != 0) {
            switch (flagArray[93]) {
                case 1:
                case 3: {
                    this.onSafeBrowsingCheckFinish((modifier._Web_onSafeBrowsingCheckFinish_0_0value as OnSafeBrowsingCheckResultCallback | undefined));
                    break;
                }
                default: {
                    this.onSafeBrowsingCheckFinish((undefined as OnSafeBrowsingCheckResultCallback | undefined));
                }
            }
        }
        if (flagArray[94] != 0) {
            switch (flagArray[94]) {
                case 1:
                case 3: {
                    this.onNavigationEntryCommitted((modifier._Web_onNavigationEntryCommitted_0_0value as OnNavigationEntryCommittedCallback | undefined));
                    break;
                }
                default: {
                    this.onNavigationEntryCommitted((undefined as OnNavigationEntryCommittedCallback | undefined));
                }
            }
        }
        if (flagArray[95] != 0) {
            switch (flagArray[95]) {
                case 1:
                case 3: {
                    this.onIntelligentTrackingPreventionResult((modifier._Web_onIntelligentTrackingPreventionResult_0_0value as OnIntelligentTrackingPreventionCallback | undefined));
                    break;
                }
                default: {
                    this.onIntelligentTrackingPreventionResult((undefined as OnIntelligentTrackingPreventionCallback | undefined));
                }
            }
        }
        if (flagArray[96] != 0) {
            switch (flagArray[96]) {
                case 1:
                case 3: {
                    this.javaScriptOnDocumentStart((modifier._Web_javaScriptOnDocumentStart_0_0value as Array<ScriptItem> | undefined));
                    break;
                }
                default: {
                    this.javaScriptOnDocumentStart((undefined as Array<ScriptItem> | undefined));
                }
            }
        }
        if (flagArray[97] != 0) {
            switch (flagArray[97]) {
                case 1:
                case 3: {
                    this.javaScriptOnDocumentEnd((modifier._Web_javaScriptOnDocumentEnd_0_0value as Array<ScriptItem> | undefined));
                    break;
                }
                default: {
                    this.javaScriptOnDocumentEnd((undefined as Array<ScriptItem> | undefined));
                }
            }
        }
        if (flagArray[98] != 0) {
            switch (flagArray[98]) {
                case 1:
                case 3: {
                    this.layoutMode((modifier._Web_layoutMode_0_0value as WebLayoutMode | undefined));
                    break;
                }
                default: {
                    this.layoutMode((undefined as WebLayoutMode | undefined));
                }
            }
        }
        if (flagArray[99] != 0) {
            switch (flagArray[99]) {
                case 1:
                case 3: {
                    this.nestedScroll((modifier._Web_nestedScroll_0_0value as NestedScrollOptions | NestedScrollOptionsExt | undefined));
                    break;
                }
                default: {
                    this.nestedScroll((undefined as NestedScrollOptions | NestedScrollOptionsExt | undefined));
                }
            }
        }
    }
    mergeModifier5(modifier: WebModifier, flagArray: Uint8Array): void {
        if (flagArray[100] != 0) {
            switch (flagArray[100]) {
                case 1:
                case 3: {
                    this.enableNativeEmbedMode((modifier._Web_enableNativeEmbedMode_0_0value as boolean | undefined));
                    break;
                }
                default: {
                    this.enableNativeEmbedMode((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[101] != 0) {
            switch (flagArray[101]) {
                case 1:
                case 3: {
                    this.onNativeEmbedLifecycleChange((modifier._Web_onNativeEmbedLifecycleChange_0_0value as ((event: NativeEmbedDataInfo) => void) | undefined));
                    break;
                }
                default: {
                    this.onNativeEmbedLifecycleChange((undefined as ((event: NativeEmbedDataInfo) => void) | undefined));
                }
            }
        }
        if (flagArray[102] != 0) {
            switch (flagArray[102]) {
                case 1:
                case 3: {
                    this.onNativeEmbedVisibilityChange((modifier._Web_onNativeEmbedVisibilityChange_0_0value as OnNativeEmbedVisibilityChangeCallback | undefined));
                    break;
                }
                default: {
                    this.onNativeEmbedVisibilityChange((undefined as OnNativeEmbedVisibilityChangeCallback | undefined));
                }
            }
        }
        if (flagArray[103] != 0) {
            switch (flagArray[103]) {
                case 1:
                case 3: {
                    this.onNativeEmbedGestureEvent((modifier._Web_onNativeEmbedGestureEvent_0_0value as ((event: NativeEmbedTouchInfo) => void) | undefined));
                    break;
                }
                default: {
                    this.onNativeEmbedGestureEvent((undefined as ((event: NativeEmbedTouchInfo) => void) | undefined));
                }
            }
        }
        if (flagArray[104] != 0) {
            switch (flagArray[104]) {
                case 1:
                case 3: {
                    this.onNativeEmbedMouseEvent((modifier._Web_onNativeEmbedMouseEvent_0_0value as MouseInfoCallback | undefined));
                    break;
                }
                default: {
                    this.onNativeEmbedMouseEvent((undefined as MouseInfoCallback | undefined));
                }
            }
        }
        if (flagArray[105] != 0) {
            switch (flagArray[105]) {
                case 1:
                case 3: {
                    this.copyOptions((modifier._Web_copyOptions_0_0value as CopyOptions | undefined));
                    break;
                }
                default: {
                    this.copyOptions((undefined as CopyOptions | undefined));
                }
            }
        }
        if (flagArray[106] != 0) {
            switch (flagArray[106]) {
                case 1:
                case 3: {
                    this.onOverrideUrlLoading((modifier._Web_onOverrideUrlLoading_0_0value as OnOverrideUrlLoadingCallback | undefined));
                    break;
                }
                default: {
                    this.onOverrideUrlLoading((undefined as OnOverrideUrlLoadingCallback | undefined));
                }
            }
        }
        if (flagArray[107] != 0) {
            switch (flagArray[107]) {
                case 1:
                case 3: {
                    this.onOverrideErrorPage((modifier._Web_onOverrideErrorPage_0_0value as OnOverrideErrorPageCallback | undefined));
                    break;
                }
                default: {
                    this.onOverrideErrorPage((undefined as OnOverrideErrorPageCallback | undefined));
                }
            }
        }
        if (flagArray[108] != 0) {
            switch (flagArray[108]) {
                case 1:
                case 3: {
                    this.textAutosizing((modifier._Web_textAutosizing_0_0value as boolean | undefined));
                    break;
                }
                default: {
                    this.textAutosizing((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[109] != 0) {
            switch (flagArray[109]) {
                case 1:
                case 3: {
                    this.enableNativeMediaPlayer((modifier._Web_enableNativeMediaPlayer_0_0value as NativeMediaPlayerConfig | undefined));
                    break;
                }
                default: {
                    this.enableNativeMediaPlayer((undefined as NativeMediaPlayerConfig | undefined));
                }
            }
        }
        if (flagArray[110] != 0) {
            switch (flagArray[110]) {
                case 1:
                case 3: {
                    this.onRenderProcessNotResponding((modifier._Web_onRenderProcessNotResponding_0_0value as OnRenderProcessNotRespondingCallback | undefined));
                    break;
                }
                default: {
                    this.onRenderProcessNotResponding((undefined as OnRenderProcessNotRespondingCallback | undefined));
                }
            }
        }
        if (flagArray[111] != 0) {
            switch (flagArray[111]) {
                case 1:
                case 3: {
                    this.onRenderProcessResponding((modifier._Web_onRenderProcessResponding_0_0value as OnRenderProcessRespondingCallback | undefined));
                    break;
                }
                default: {
                    this.onRenderProcessResponding((undefined as OnRenderProcessRespondingCallback | undefined));
                }
            }
        }
        if (flagArray[112] != 0) {
            switch (flagArray[112]) {
                case 1:
                case 3: {
                    this.onViewportFitChanged((modifier._Web_onViewportFitChanged_0_0value as OnViewportFitChangedCallback | undefined));
                    break;
                }
                default: {
                    this.onViewportFitChanged((undefined as OnViewportFitChangedCallback | undefined));
                }
            }
        }
        if (flagArray[113] != 0) {
            switch (flagArray[113]) {
                case 1:
                case 3: {
                    this.onInterceptKeyboardAttach((modifier._Web_onInterceptKeyboardAttach_0_0value as WebKeyboardCallback | undefined));
                    break;
                }
                default: {
                    this.onInterceptKeyboardAttach((undefined as WebKeyboardCallback | undefined));
                }
            }
        }
        if (flagArray[114] != 0) {
            switch (flagArray[114]) {
                case 1:
                case 3: {
                    this.onAdsBlocked((modifier._Web_onAdsBlocked_0_0value as OnAdsBlockedCallback | undefined));
                    break;
                }
                default: {
                    this.onAdsBlocked((undefined as OnAdsBlockedCallback | undefined));
                }
            }
        }
        if (flagArray[115] != 0) {
            switch (flagArray[115]) {
                case 1:
                case 3: {
                    this.keyboardAvoidMode((modifier._Web_keyboardAvoidMode_0_0value as WebKeyboardAvoidMode | undefined));
                    break;
                }
                default: {
                    this.keyboardAvoidMode((undefined as WebKeyboardAvoidMode | undefined));
                }
            }
        }
        if (flagArray[116] != 0) {
            switch (flagArray[116]) {
                case 1:
                case 3: {
                    this.editMenuOptions((modifier._Web_editMenuOptions_0_0value as EditMenuOptions | undefined));
                    break;
                }
                default: {
                    this.editMenuOptions((undefined as EditMenuOptions | undefined));
                }
            }
        }
        if (flagArray[117] != 0) {
            switch (flagArray[117]) {
                case 1:
                case 3: {
                    this.enableHapticFeedback((modifier._Web_enableHapticFeedback_0_0value as boolean | undefined));
                    break;
                }
                default: {
                    this.enableHapticFeedback((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[118] != 0) {
            switch (flagArray[118]) {
                case 1:
                case 3: {
                    this.enableFollowSystemFontWeight((modifier._Web_enableFollowSystemFontWeight_0_0value as boolean | undefined));
                    break;
                }
                default: {
                    this.enableFollowSystemFontWeight((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[119] != 0) {
            switch (flagArray[119]) {
                case 1:
                case 3: {
                    this.enableWebAVSession((modifier._Web_enableWebAVSession_0_0value as boolean | undefined));
                    break;
                }
                default: {
                    this.enableWebAVSession((undefined as boolean | undefined));
                }
            }
        }
    }
    mergeModifier6(modifier: WebModifier, flagArray: Uint8Array): void {
        if (flagArray[120] != 0) {
            switch (flagArray[120]) {
                case 1:
                case 3: {
                    this.optimizeParserBudget((modifier._Web_optimizeParserBudget_0_0value as boolean | undefined));
                    break;
                }
                default: {
                    this.optimizeParserBudget((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[121] != 0) {
            switch (flagArray[121]) {
                case 1:
                case 3: {
                    this.runJavaScriptOnDocumentStart((modifier._Web_runJavaScriptOnDocumentStart_0_0value as Array<ScriptItem> | undefined));
                    break;
                }
                default: {
                    this.runJavaScriptOnDocumentStart((undefined as Array<ScriptItem> | undefined));
                }
            }
        }
        if (flagArray[122] != 0) {
            switch (flagArray[122]) {
                case 1:
                case 3: {
                    this.runJavaScriptOnDocumentEnd((modifier._Web_runJavaScriptOnDocumentEnd_0_0value as Array<ScriptItem> | undefined));
                    break;
                }
                default: {
                    this.runJavaScriptOnDocumentEnd((undefined as Array<ScriptItem> | undefined));
                }
            }
        }
        if (flagArray[123] != 0) {
            switch (flagArray[123]) {
                case 1:
                case 3: {
                    this.runJavaScriptOnHeadEnd((modifier._Web_runJavaScriptOnHeadEnd_0_0value as Array<ScriptItem> | undefined));
                    break;
                }
                default: {
                    this.runJavaScriptOnHeadEnd((undefined as Array<ScriptItem> | undefined));
                }
            }
        }
        if (flagArray[124] != 0) {
            switch (flagArray[124]) {
                case 1:
                case 3: {
                    this.nativeEmbedOptions((modifier._Web_nativeEmbedOptions_0_0value as EmbedOptions | undefined));
                    break;
                }
                default: {
                    this.nativeEmbedOptions((undefined as EmbedOptions | undefined));
                }
            }
        }
        if (flagArray[125] != 0) {
            switch (flagArray[125]) {
                case 1:
                case 3: {
                    this.enableDataDetector((modifier._Web_enableDataDetector_0_0value as boolean | undefined));
                    break;
                }
                default: {
                    this.enableDataDetector((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[126] != 0) {
            switch (flagArray[126]) {
                case 1:
                case 3: {
                    this.dataDetectorConfig((modifier._Web_dataDetectorConfig_0_0value as TextDataDetectorConfig | undefined));
                    break;
                }
                default: {
                    this.dataDetectorConfig((undefined as TextDataDetectorConfig | undefined));
                }
            }
        }
        if (flagArray[127] != 0) {
            switch (flagArray[127]) {
                case 1:
                case 3: {
                    this.onActivateContent((modifier._Web_onActivateContent_0_0value as VoidCallback | undefined));
                    break;
                }
                default: {
                    this.onActivateContent((undefined as VoidCallback | undefined));
                }
            }
        }
        if (flagArray[128] != 0) {
            switch (flagArray[128]) {
                case 1:
                case 3: {
                    this.bypassVsyncCondition((modifier._Web_bypassVsyncCondition_0_0value as WebBypassVsyncCondition | undefined));
                    break;
                }
                default: {
                    this.bypassVsyncCondition((undefined as WebBypassVsyncCondition | undefined));
                }
            }
        }
        if (flagArray[129] != 0) {
            switch (flagArray[129]) {
                case 1:
                case 3: {
                    this.gestureFocusMode((modifier._Web_gestureFocusMode_0_0value as GestureFocusMode | undefined));
                    break;
                }
                default: {
                    this.gestureFocusMode((undefined as GestureFocusMode | undefined));
                }
            }
        }
        if (flagArray[130] != 0) {
            switch (flagArray[130]) {
                case 1:
                case 3: {
                    this.forceEnableZoom((modifier._Web_forceEnableZoom_0_0value as boolean | undefined));
                    break;
                }
                default: {
                    this.forceEnableZoom((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[131] != 0) {
            switch (flagArray[131]) {
                case 1:
                case 3: {
                    this.onNativeEmbedObjectParamChange((modifier._Web_onNativeEmbedObjectParamChange_0_0value as OnNativeEmbedObjectParamChangeCallback | undefined));
                    break;
                }
                default: {
                    this.onNativeEmbedObjectParamChange((undefined as OnNativeEmbedObjectParamChangeCallback | undefined));
                }
            }
        }
        if (flagArray[132] != 0) {
            switch (flagArray[132]) {
                case 1:
                case 3: {
                    this.rotateRenderEffect((modifier._Web_rotateRenderEffect_0_0value as WebRotateEffect | undefined));
                    break;
                }
                default: {
                    this.rotateRenderEffect((undefined as WebRotateEffect | undefined));
                }
            }
        }
        if (flagArray[133] != 0) {
            switch (flagArray[133]) {
                case 1:
                case 3: {
                    this.zoomControlAccess((modifier._Web_zoomControlAccess_0_0value as boolean | undefined));
                    break;
                }
                default: {
                    this.zoomControlAccess((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[134] != 0) {
            switch (flagArray[134]) {
                case 1:
                case 3: {
                    this.onDetectedBlankScreen((modifier._Web_onDetectedBlankScreen_0_0value as OnDetectBlankScreenCallback | undefined));
                    break;
                }
                default: {
                    this.onDetectedBlankScreen((undefined as OnDetectBlankScreenCallback | undefined));
                }
            }
        }
        if (flagArray[135] != 0) {
            switch (flagArray[135]) {
                case 1:
                case 3: {
                    this.blankScreenDetectionConfig((modifier._Web_blankScreenDetectionConfig_0_0value as BlankScreenDetectionConfig | undefined));
                    break;
                }
                default: {
                    this.blankScreenDetectionConfig((undefined as BlankScreenDetectionConfig | undefined));
                }
            }
        }
        if (flagArray[136] != 0) {
            switch (flagArray[136]) {
                case 1:
                case 3: {
                    this.backToTop((modifier._Web_backToTop_0_0value as boolean | undefined));
                    break;
                }
                default: {
                    this.backToTop((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[137] != 0) {
            switch (flagArray[137]) {
                case 1:
                case 3: {
                    this.enableSelectedDataDetector((modifier._Web_enableSelectedDataDetector_0_0value as boolean | undefined));
                    break;
                }
                default: {
                    this.enableSelectedDataDetector((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[138] != 0) {
            switch (flagArray[138]) {
                case 1:
                case 3: {
                    this.onFirstScreenPaint((modifier._Web_onFirstScreenPaint_0_0value as OnFirstScreenPaintCallback | undefined));
                    break;
                }
                default: {
                    this.onFirstScreenPaint((undefined as OnFirstScreenPaintCallback | undefined));
                }
            }
        }
        if (flagArray[139] != 0) {
            switch (flagArray[139]) {
                case 1:
                case 3: {
                    this.enableAutoFill((modifier._Web_enableAutoFill_0_0value as boolean | undefined));
                    break;
                }
                default: {
                    this.enableAutoFill((undefined as boolean | undefined));
                }
            }
        }
    }
    mergeModifier7(modifier: WebModifier, flagArray: Uint8Array): void {
        if (flagArray[140] != 0) {
            switch (flagArray[140]) {
                case 1:
                case 3: {
                    this.onTextSelectionChange((modifier._Web_onTextSelectionChange_0_0value as TextSelectionChangeCallback | undefined));
                    break;
                }
                default: {
                    this.onTextSelectionChange((undefined as TextSelectionChangeCallback | undefined));
                }
            }
        }
        if (flagArray[141] != 0) {
            switch (flagArray[141]) {
                case 1:
                case 3: {
                    this.enableImageAnalyzer((modifier._Web_enableImageAnalyzer_0_0value as boolean | undefined));
                    break;
                }
                default: {
                    this.enableImageAnalyzer((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[142] != 0) {
            switch (flagArray[142]) {
                case 1:
                case 3: {
                    this.onCameraCaptureStateChange((modifier._Web_onCameraCaptureStateChange_0_0value as OnCameraCaptureStateChangeCallback | undefined));
                    break;
                }
                default: {
                    this.onCameraCaptureStateChange((undefined as OnCameraCaptureStateChangeCallback | undefined));
                }
            }
        }
        if (flagArray[143] != 0) {
            switch (flagArray[143]) {
                case 1:
                case 3: {
                    this.onMicrophoneCaptureStateChange((modifier._Web_onMicrophoneCaptureStateChange_0_0value as OnMicrophoneCaptureStateChangeCallback | undefined));
                    break;
                }
                default: {
                    this.onMicrophoneCaptureStateChange((undefined as OnMicrophoneCaptureStateChangeCallback | undefined));
                }
            }
        }
        if (flagArray[144] != 0) {
            switch (flagArray[144]) {
                case 1:
                case 3: {
                    this.enableDefaultContextMenu((modifier._Web_enableDefaultContextMenu_0_0value as boolean | undefined));
                    break;
                }
                default: {
                    this.enableDefaultContextMenu((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[145] != 0) {
            switch (flagArray[145]) {
                case 1:
                case 3: {
                    this.enableDrag((modifier._Web_enableDrag_0_0value as boolean | undefined));
                    break;
                }
                default: {
                    this.enableDrag((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[146] != 0) {
            switch (flagArray[146]) {
                case 1:
                case 3: {
                    this.scrollbarLayoutPolicy((modifier._Web_scrollbarLayoutPolicy_0_0value as ScrollbarLayoutPolicy | undefined));
                    break;
                }
                default: {
                    this.scrollbarLayoutPolicy((undefined as ScrollbarLayoutPolicy | undefined));
                }
            }
        }
        if (flagArray[147] != 0) {
            switch (flagArray[147]) {
                case 1:
                case 3: {
                    this.aiSessionOptions((modifier._Web_aiSessionOptions_0_0value as Array<AISessionEvent> | undefined));
                    break;
                }
                default: {
                    this.aiSessionOptions((undefined as Array<AISessionEvent> | undefined));
                }
            }
        }
        if (flagArray[148] != 0) {
            switch (flagArray[148]) {
                case 1:
                case 3: {
                    this.keyboardAppearance((modifier._Web_keyboardAppearance_0_0value as WebKeyboardAppearanceMode | undefined));
                    break;
                }
                default: {
                    this.keyboardAppearance((undefined as WebKeyboardAppearanceMode | undefined));
                }
            }
        }
        if (flagArray[149] != 0) {
            switch (flagArray[149]) {
                case 1:
                case 3: {
                    this.onInputmethodAttached((modifier._Web_onInputmethodAttached_0_0value as OnInputmethodAttachedCallback | undefined));
                    break;
                }
                default: {
                    this.onInputmethodAttached((undefined as OnInputmethodAttachedCallback | undefined));
                }
            }
        }
        if (flagArray[150] != 0) {
            switch (flagArray[150]) {
                case 1:
                case 3: {
                    this.registerNativeEmbedRule((modifier._Web_registerNativeEmbedRule_0_0value as string | undefined), (modifier._Web_registerNativeEmbedRule_0_1value as string | undefined));
                    break;
                }
                default: {
                    this.registerNativeEmbedRule((undefined as string | undefined), (undefined as string | undefined));
                }
            }
        }
        if (flagArray[151] != 0) {
            switch (flagArray[151]) {
                case 1:
                case 3: {
                    this.bindSelectionMenu((modifier._Web_bindSelectionMenu_0_0value as WebElementType | undefined), (modifier._Web_bindSelectionMenu_0_1value as CustomBuilder | undefined), (modifier._Web_bindSelectionMenu_0_2value as WebResponseType | undefined), (modifier._Web_bindSelectionMenu_0_3value as SelectionMenuOptionsExt | undefined));
                    break;
                }
                default: {
                    this.bindSelectionMenu((undefined as WebElementType | undefined), (undefined as CustomBuilder | undefined), (undefined as WebResponseType | undefined), (undefined as SelectionMenuOptionsExt | undefined | undefined));
                }
            }
        }
        if (flagArray[152] != 0) {
            switch (flagArray[152]) {
                case 1:
                case 3: {
                    this.enableScrollDirectionalLock((modifier._Web_enableScrollDirectionalLock_0_0value as boolean | undefined), (modifier._Web_enableScrollDirectionalLock_0_1value as ScrollDirectionalLockType | undefined));
                    break;
                }
                default: {
                    this.enableScrollDirectionalLock((undefined as boolean | undefined), (undefined as ScrollDirectionalLockType | undefined));
                }
            }
        }
    }
    javaScriptAccess(value: boolean | undefined): this {
        if (((this._Web_flagArray[0]) == (0)) || ((this._Web_javaScriptAccess_0_0value) !== (value))) {
            this._Web_flagArray[0] = 1
            this._Web_javaScriptAccess_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[0] = 3
        }
        return this
    }
    fileAccess(value: boolean | undefined): this {
        if (((this._Web_flagArray[1]) == (0)) || ((this._Web_fileAccess_0_0value) !== (value))) {
            this._Web_flagArray[1] = 1
            this._Web_fileAccess_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[1] = 3
        }
        return this
    }
    onlineImageAccess(value: boolean | undefined): this {
        if (((this._Web_flagArray[2]) == (0)) || ((this._Web_onlineImageAccess_0_0value) !== (value))) {
            this._Web_flagArray[2] = 1
            this._Web_onlineImageAccess_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[2] = 3
        }
        return this
    }
    domStorageAccess(value: boolean | undefined): this {
        if (((this._Web_flagArray[3]) == (0)) || ((this._Web_domStorageAccess_0_0value) !== (value))) {
            this._Web_flagArray[3] = 1
            this._Web_domStorageAccess_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[3] = 3
        }
        return this
    }
    imageAccess(value: boolean | undefined): this {
        if (((this._Web_flagArray[4]) == (0)) || ((this._Web_imageAccess_0_0value) !== (value))) {
            this._Web_flagArray[4] = 1
            this._Web_imageAccess_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[4] = 3
        }
        return this
    }
    mixedMode(value: MixedMode | undefined): this {
        if (((this._Web_flagArray[5]) == (0)) || (true)) {
            this._Web_flagArray[5] = 1
            this._Web_mixedMode_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[5] = 3
        }
        return this
    }
    zoomAccess(value: boolean | undefined): this {
        if (((this._Web_flagArray[6]) == (0)) || ((this._Web_zoomAccess_0_0value) !== (value))) {
            this._Web_flagArray[6] = 1
            this._Web_zoomAccess_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[6] = 3
        }
        return this
    }
    geolocationAccess(value: boolean | undefined): this {
        if (((this._Web_flagArray[7]) == (0)) || ((this._Web_geolocationAccess_0_0value) !== (value))) {
            this._Web_flagArray[7] = 1
            this._Web_geolocationAccess_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[7] = 3
        }
        return this
    }
    javaScriptProxy(value: JavaScriptProxy | undefined): this {
        if (((this._Web_flagArray[8]) == (0)) || (true)) {
            this._Web_flagArray[8] = 1
            this._Web_javaScriptProxy_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[8] = 3
        }
        return this
    }
    cacheMode(value: CacheMode | undefined): this {
        if (((this._Web_flagArray[9]) == (0)) || (true)) {
            this._Web_flagArray[9] = 1
            this._Web_cacheMode_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[9] = 3
        }
        return this
    }
    darkMode(value: WebDarkMode | undefined): this {
        if (((this._Web_flagArray[10]) == (0)) || (true)) {
            this._Web_flagArray[10] = 1
            this._Web_darkMode_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[10] = 3
        }
        return this
    }
    forceDarkAccess(value: boolean | undefined): this {
        if (((this._Web_flagArray[11]) == (0)) || ((this._Web_forceDarkAccess_0_0value) !== (value))) {
            this._Web_flagArray[11] = 1
            this._Web_forceDarkAccess_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[11] = 3
        }
        return this
    }
    mediaOptions(value: WebMediaOptions | undefined): this {
        if (((this._Web_flagArray[12]) == (0)) || (true)) {
            this._Web_flagArray[12] = 1
            this._Web_mediaOptions_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[12] = 3
        }
        return this
    }
    overviewModeAccess(value: boolean | undefined): this {
        if (((this._Web_flagArray[13]) == (0)) || ((this._Web_overviewModeAccess_0_0value) !== (value))) {
            this._Web_flagArray[13] = 1
            this._Web_overviewModeAccess_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[13] = 3
        }
        return this
    }
    overScrollMode(value: OverScrollMode | undefined): this {
        if (((this._Web_flagArray[14]) == (0)) || (true)) {
            this._Web_flagArray[14] = 1
            this._Web_overScrollMode_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[14] = 3
        }
        return this
    }
    blurOnKeyboardHideMode(value: BlurOnKeyboardHideMode | undefined): this {
        if (((this._Web_flagArray[15]) == (0)) || (true)) {
            this._Web_flagArray[15] = 1
            this._Web_blurOnKeyboardHideMode_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[15] = 3
        }
        return this
    }
    textZoomRatio(value: int32 | undefined): this {
        if (((this._Web_flagArray[16]) == (0)) || ((this._Web_textZoomRatio_0_0value) !== (value))) {
            this._Web_flagArray[16] = 1
            this._Web_textZoomRatio_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[16] = 3
        }
        return this
    }
    databaseAccess(value: boolean | undefined): this {
        if (((this._Web_flagArray[17]) == (0)) || ((this._Web_databaseAccess_0_0value) !== (value))) {
            this._Web_flagArray[17] = 1
            this._Web_databaseAccess_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[17] = 3
        }
        return this
    }
    initialScale(value: double | undefined): this {
        if (((this._Web_flagArray[18]) == (0)) || ((this._Web_initialScale_0_0value) !== (value))) {
            this._Web_flagArray[18] = 1
            this._Web_initialScale_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[18] = 3
        }
        return this
    }
    metaViewport(value: boolean | undefined): this {
        if (((this._Web_flagArray[19]) == (0)) || ((this._Web_metaViewport_0_0value) !== (value))) {
            this._Web_flagArray[19] = 1
            this._Web_metaViewport_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[19] = 3
        }
        return this
    }
    onPageBegin(value: arkui_component_common_Callback<OnPageBeginEvent, void> | undefined): this {
        if (((this._Web_flagArray[20]) == (0)) || (true)) {
            this._Web_flagArray[20] = 1
            this._Web_onPageBegin_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[20] = 3
        }
        return this
    }
    onPageEnd(value: arkui_component_common_Callback<OnPageEndEvent, void> | undefined): this {
        if (((this._Web_flagArray[21]) == (0)) || (true)) {
            this._Web_flagArray[21] = 1
            this._Web_onPageEnd_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[21] = 3
        }
        return this
    }
    onLoadStarted(value: arkui_component_common_Callback<OnLoadStartedEvent, void> | undefined): this {
        if (((this._Web_flagArray[22]) == (0)) || (true)) {
            this._Web_flagArray[22] = 1
            this._Web_onLoadStarted_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[22] = 3
        }
        return this
    }
    onLoadFinished(value: arkui_component_common_Callback<OnLoadFinishedEvent, void> | undefined): this {
        if (((this._Web_flagArray[23]) == (0)) || (true)) {
            this._Web_flagArray[23] = 1
            this._Web_onLoadFinished_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[23] = 3
        }
        return this
    }
    onProgressChange(value: arkui_component_common_Callback<OnProgressChangeEvent, void> | undefined): this {
        if (((this._Web_flagArray[24]) == (0)) || (true)) {
            this._Web_flagArray[24] = 1
            this._Web_onProgressChange_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[24] = 3
        }
        return this
    }
    onTitleReceive(value: arkui_component_common_Callback<OnTitleReceiveEvent, void> | undefined): this {
        if (((this._Web_flagArray[25]) == (0)) || (true)) {
            this._Web_flagArray[25] = 1
            this._Web_onTitleReceive_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[25] = 3
        }
        return this
    }
    onGeolocationHide(value: (() => void) | undefined): this {
        if (((this._Web_flagArray[26]) == (0)) || (true)) {
            this._Web_flagArray[26] = 1
            this._Web_onGeolocationHide_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[26] = 3
        }
        return this
    }
    onGeolocationShow(value: arkui_component_common_Callback<OnGeolocationShowEvent, void> | undefined): this {
        if (((this._Web_flagArray[27]) == (0)) || (true)) {
            this._Web_flagArray[27] = 1
            this._Web_onGeolocationShow_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[27] = 3
        }
        return this
    }
    onRequestSelected(value: (() => void) | undefined): this {
        if (((this._Web_flagArray[28]) == (0)) || (true)) {
            this._Web_flagArray[28] = 1
            this._Web_onRequestSelected_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[28] = 3
        }
        return this
    }
    onAlert(value: arkui_component_common_Callback<OnAlertEvent, boolean> | undefined): this {
        if (((this._Web_flagArray[29]) == (0)) || (true)) {
            this._Web_flagArray[29] = 1
            this._Web_onAlert_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[29] = 3
        }
        return this
    }
    onBeforeUnload(value: arkui_component_common_Callback<OnBeforeUnloadEvent, boolean> | undefined): this {
        if (((this._Web_flagArray[30]) == (0)) || (true)) {
            this._Web_flagArray[30] = 1
            this._Web_onBeforeUnload_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[30] = 3
        }
        return this
    }
    onConfirm(value: arkui_component_common_Callback<OnConfirmEvent, boolean> | undefined): this {
        if (((this._Web_flagArray[31]) == (0)) || (true)) {
            this._Web_flagArray[31] = 1
            this._Web_onConfirm_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[31] = 3
        }
        return this
    }
    onPrompt(value: arkui_component_common_Callback<OnPromptEvent, boolean> | undefined): this {
        if (((this._Web_flagArray[32]) == (0)) || (true)) {
            this._Web_flagArray[32] = 1
            this._Web_onPrompt_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[32] = 3
        }
        return this
    }
    onConsole(value: arkui_component_common_Callback<OnConsoleEvent, boolean> | undefined): this {
        if (((this._Web_flagArray[33]) == (0)) || (true)) {
            this._Web_flagArray[33] = 1
            this._Web_onConsole_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[33] = 3
        }
        return this
    }
    onErrorReceive(value: arkui_component_common_Callback<OnErrorReceiveEvent, void> | undefined): this {
        if (((this._Web_flagArray[34]) == (0)) || (true)) {
            this._Web_flagArray[34] = 1
            this._Web_onErrorReceive_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[34] = 3
        }
        return this
    }
    onHttpErrorReceive(value: arkui_component_common_Callback<OnHttpErrorReceiveEvent, void> | undefined): this {
        if (((this._Web_flagArray[35]) == (0)) || (true)) {
            this._Web_flagArray[35] = 1
            this._Web_onHttpErrorReceive_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[35] = 3
        }
        return this
    }
    onDownloadStart(value: arkui_component_common_Callback<OnDownloadStartEvent, void> | undefined): this {
        if (((this._Web_flagArray[36]) == (0)) || (true)) {
            this._Web_flagArray[36] = 1
            this._Web_onDownloadStart_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[36] = 3
        }
        return this
    }
    onRefreshAccessedHistory(value: arkui_component_common_Callback<OnRefreshAccessedHistoryEvent, void> | undefined): this {
        if (((this._Web_flagArray[37]) == (0)) || (true)) {
            this._Web_flagArray[37] = 1
            this._Web_onRefreshAccessedHistory_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[37] = 3
        }
        return this
    }
    onRenderExited(value: arkui_component_common_Callback<OnRenderExitedEvent, void> | undefined): this {
        if (((this._Web_flagArray[38]) == (0)) || (true)) {
            this._Web_flagArray[38] = 1
            this._Web_onRenderExited_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[38] = 3
        }
        return this
    }
    onShowFileSelector(value: arkui_component_common_Callback<OnShowFileSelectorEvent, boolean> | undefined): this {
        if (((this._Web_flagArray[39]) == (0)) || (true)) {
            this._Web_flagArray[39] = 1
            this._Web_onShowFileSelector_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[39] = 3
        }
        return this
    }
    onResourceLoad(value: arkui_component_common_Callback<OnResourceLoadEvent, void> | undefined): this {
        if (((this._Web_flagArray[40]) == (0)) || (true)) {
            this._Web_flagArray[40] = 1
            this._Web_onResourceLoad_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[40] = 3
        }
        return this
    }
    onFullScreenExit(value: (() => void) | undefined): this {
        if (((this._Web_flagArray[41]) == (0)) || (true)) {
            this._Web_flagArray[41] = 1
            this._Web_onFullScreenExit_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[41] = 3
        }
        return this
    }
    onFullScreenEnter(value: OnFullScreenEnterCallback | undefined): this {
        if (((this._Web_flagArray[42]) == (0)) || (true)) {
            this._Web_flagArray[42] = 1
            this._Web_onFullScreenEnter_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[42] = 3
        }
        return this
    }
    onScaleChange(value: arkui_component_common_Callback<OnScaleChangeEvent, void> | undefined): this {
        if (((this._Web_flagArray[43]) == (0)) || (true)) {
            this._Web_flagArray[43] = 1
            this._Web_onScaleChange_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[43] = 3
        }
        return this
    }
    onHttpAuthRequest(value: arkui_component_common_Callback<OnHttpAuthRequestEvent, boolean> | undefined): this {
        if (((this._Web_flagArray[44]) == (0)) || (true)) {
            this._Web_flagArray[44] = 1
            this._Web_onHttpAuthRequest_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[44] = 3
        }
        return this
    }
    onInterceptRequest(value: arkui_component_common_Callback<OnInterceptRequestEvent, WebResourceResponse | null> | undefined): this {
        if (((this._Web_flagArray[45]) == (0)) || (true)) {
            this._Web_flagArray[45] = 1
            this._Web_onInterceptRequest_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[45] = 3
        }
        return this
    }
    onPermissionRequest(value: arkui_component_common_Callback<OnPermissionRequestEvent, void> | undefined): this {
        if (((this._Web_flagArray[46]) == (0)) || (true)) {
            this._Web_flagArray[46] = 1
            this._Web_onPermissionRequest_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[46] = 3
        }
        return this
    }
    onScreenCaptureRequest(value: arkui_component_common_Callback<OnScreenCaptureRequestEvent, void> | undefined): this {
        if (((this._Web_flagArray[47]) == (0)) || (true)) {
            this._Web_flagArray[47] = 1
            this._Web_onScreenCaptureRequest_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[47] = 3
        }
        return this
    }
    onContextMenuShow(value: arkui_component_common_Callback<OnContextMenuShowEvent, boolean> | undefined): this {
        if (((this._Web_flagArray[48]) == (0)) || (true)) {
            this._Web_flagArray[48] = 1
            this._Web_onContextMenuShow_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[48] = 3
        }
        return this
    }
    onContextMenuHide(value: OnContextMenuHideCallback | undefined): this {
        if (((this._Web_flagArray[49]) == (0)) || (true)) {
            this._Web_flagArray[49] = 1
            this._Web_onContextMenuHide_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[49] = 3
        }
        return this
    }
    mediaPlayGestureAccess(value: boolean | undefined): this {
        if (((this._Web_flagArray[50]) == (0)) || ((this._Web_mediaPlayGestureAccess_0_0value) !== (value))) {
            this._Web_flagArray[50] = 1
            this._Web_mediaPlayGestureAccess_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[50] = 3
        }
        return this
    }
    onSearchResultReceive(value: arkui_component_common_Callback<OnSearchResultReceiveEvent, void> | undefined): this {
        if (((this._Web_flagArray[51]) == (0)) || (true)) {
            this._Web_flagArray[51] = 1
            this._Web_onSearchResultReceive_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[51] = 3
        }
        return this
    }
    onScroll(value: arkui_component_common_Callback<OnScrollEvent, void> | undefined): this {
        if (((this._Web_flagArray[52]) == (0)) || (true)) {
            this._Web_flagArray[52] = 1
            this._Web_onScroll_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[52] = 3
        }
        return this
    }
    onSslErrorEventReceive(value: arkui_component_common_Callback<OnSslErrorEventReceiveEvent, void> | undefined): this {
        if (((this._Web_flagArray[53]) == (0)) || (true)) {
            this._Web_flagArray[53] = 1
            this._Web_onSslErrorEventReceive_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[53] = 3
        }
        return this
    }
    onSslErrorEvent(value: OnSslErrorEventCallback | undefined): this {
        if (((this._Web_flagArray[54]) == (0)) || (true)) {
            this._Web_flagArray[54] = 1
            this._Web_onSslErrorEvent_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[54] = 3
        }
        return this
    }
    onClientAuthenticationRequest(value: arkui_component_common_Callback<OnClientAuthenticationEvent, void> | undefined): this {
        if (((this._Web_flagArray[55]) == (0)) || (true)) {
            this._Web_flagArray[55] = 1
            this._Web_onClientAuthenticationRequest_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[55] = 3
        }
        return this
    }
    onVerifyPin(value: OnVerifyPinCallback | undefined): this {
        if (((this._Web_flagArray[56]) == (0)) || (true)) {
            this._Web_flagArray[56] = 1
            this._Web_onVerifyPin_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[56] = 3
        }
        return this
    }
    onWindowNew(value: arkui_component_common_Callback<OnWindowNewEvent, void> | undefined): this {
        if (((this._Web_flagArray[57]) == (0)) || (true)) {
            this._Web_flagArray[57] = 1
            this._Web_onWindowNew_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[57] = 3
        }
        return this
    }
    onWindowNewExt(value: arkui_component_common_Callback<OnWindowNewExtEvent, void> | undefined): this {
        if (((this._Web_flagArray[58]) == (0)) || (true)) {
            this._Web_flagArray[58] = 1
            this._Web_onWindowNewExt_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[58] = 3
        }
        return this
    }
    onWindowExit(value: (() => void) | undefined): this {
        if (((this._Web_flagArray[59]) == (0)) || (true)) {
            this._Web_flagArray[59] = 1
            this._Web_onWindowExit_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[59] = 3
        }
        return this
    }
    multiWindowAccess(value: boolean | undefined): this {
        if (((this._Web_flagArray[60]) == (0)) || ((this._Web_multiWindowAccess_0_0value) !== (value))) {
            this._Web_flagArray[60] = 1
            this._Web_multiWindowAccess_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[60] = 3
        }
        return this
    }
    onInterceptKeyEvent(value: ((event: KeyEvent) => boolean) | undefined): this {
        if (((this._Web_flagArray[61]) == (0)) || (true)) {
            this._Web_flagArray[61] = 1
            this._Web_onInterceptKeyEvent_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[61] = 3
        }
        return this
    }
    webStandardFont(value: string | undefined): this {
        if (((this._Web_flagArray[62]) == (0)) || ((this._Web_webStandardFont_0_0value) !== (value))) {
            this._Web_flagArray[62] = 1
            this._Web_webStandardFont_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[62] = 3
        }
        return this
    }
    webSerifFont(value: string | undefined): this {
        if (((this._Web_flagArray[63]) == (0)) || ((this._Web_webSerifFont_0_0value) !== (value))) {
            this._Web_flagArray[63] = 1
            this._Web_webSerifFont_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[63] = 3
        }
        return this
    }
    webSansSerifFont(value: string | undefined): this {
        if (((this._Web_flagArray[64]) == (0)) || ((this._Web_webSansSerifFont_0_0value) !== (value))) {
            this._Web_flagArray[64] = 1
            this._Web_webSansSerifFont_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[64] = 3
        }
        return this
    }
    webFixedFont(value: string | undefined): this {
        if (((this._Web_flagArray[65]) == (0)) || ((this._Web_webFixedFont_0_0value) !== (value))) {
            this._Web_flagArray[65] = 1
            this._Web_webFixedFont_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[65] = 3
        }
        return this
    }
    webFantasyFont(value: string | undefined): this {
        if (((this._Web_flagArray[66]) == (0)) || ((this._Web_webFantasyFont_0_0value) !== (value))) {
            this._Web_flagArray[66] = 1
            this._Web_webFantasyFont_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[66] = 3
        }
        return this
    }
    webCursiveFont(value: string | undefined): this {
        if (((this._Web_flagArray[67]) == (0)) || ((this._Web_webCursiveFont_0_0value) !== (value))) {
            this._Web_flagArray[67] = 1
            this._Web_webCursiveFont_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[67] = 3
        }
        return this
    }
    defaultFixedFontSize(value: int32 | undefined): this {
        if (((this._Web_flagArray[68]) == (0)) || ((this._Web_defaultFixedFontSize_0_0value) !== (value))) {
            this._Web_flagArray[68] = 1
            this._Web_defaultFixedFontSize_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[68] = 3
        }
        return this
    }
    defaultFontSize(value: int32 | undefined): this {
        if (((this._Web_flagArray[69]) == (0)) || ((this._Web_defaultFontSize_0_0value) !== (value))) {
            this._Web_flagArray[69] = 1
            this._Web_defaultFontSize_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[69] = 3
        }
        return this
    }
    minFontSize(value: int32 | undefined): this {
        if (((this._Web_flagArray[70]) == (0)) || ((this._Web_minFontSize_0_0value) !== (value))) {
            this._Web_flagArray[70] = 1
            this._Web_minFontSize_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[70] = 3
        }
        return this
    }
    minLogicalFontSize(value: int32 | undefined): this {
        if (((this._Web_flagArray[71]) == (0)) || ((this._Web_minLogicalFontSize_0_0value) !== (value))) {
            this._Web_flagArray[71] = 1
            this._Web_minLogicalFontSize_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[71] = 3
        }
        return this
    }
    defaultTextEncodingFormat(value: string | undefined): this {
        if (((this._Web_flagArray[72]) == (0)) || ((this._Web_defaultTextEncodingFormat_0_0value) !== (value))) {
            this._Web_flagArray[72] = 1
            this._Web_defaultTextEncodingFormat_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[72] = 3
        }
        return this
    }
    forceDisplayScrollBar(value: boolean | undefined): this {
        if (((this._Web_flagArray[73]) == (0)) || ((this._Web_forceDisplayScrollBar_0_0value) !== (value))) {
            this._Web_flagArray[73] = 1
            this._Web_forceDisplayScrollBar_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[73] = 3
        }
        return this
    }
    blockNetwork(value: boolean | undefined): this {
        if (((this._Web_flagArray[74]) == (0)) || ((this._Web_blockNetwork_0_0value) !== (value))) {
            this._Web_flagArray[74] = 1
            this._Web_blockNetwork_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[74] = 3
        }
        return this
    }
    horizontalScrollBarAccess(value: boolean | undefined): this {
        if (((this._Web_flagArray[75]) == (0)) || ((this._Web_horizontalScrollBarAccess_0_0value) !== (value))) {
            this._Web_flagArray[75] = 1
            this._Web_horizontalScrollBarAccess_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[75] = 3
        }
        return this
    }
    verticalScrollBarAccess(value: boolean | undefined): this {
        if (((this._Web_flagArray[76]) == (0)) || ((this._Web_verticalScrollBarAccess_0_0value) !== (value))) {
            this._Web_flagArray[76] = 1
            this._Web_verticalScrollBarAccess_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[76] = 3
        }
        return this
    }
    onTouchIconUrlReceived(value: arkui_component_common_Callback<OnTouchIconUrlReceivedEvent, void> | undefined): this {
        if (((this._Web_flagArray[77]) == (0)) || (true)) {
            this._Web_flagArray[77] = 1
            this._Web_onTouchIconUrlReceived_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[77] = 3
        }
        return this
    }
    onFaviconReceived(value: arkui_component_common_Callback<OnFaviconReceivedEvent, void> | undefined): this {
        if (((this._Web_flagArray[78]) == (0)) || (true)) {
            this._Web_flagArray[78] = 1
            this._Web_onFaviconReceived_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[78] = 3
        }
        return this
    }
    onPageVisible(value: arkui_component_common_Callback<OnPageVisibleEvent, void> | undefined): this {
        if (((this._Web_flagArray[79]) == (0)) || (true)) {
            this._Web_flagArray[79] = 1
            this._Web_onPageVisible_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[79] = 3
        }
        return this
    }
    onDataResubmitted(value: arkui_component_common_Callback<OnDataResubmittedEvent, void> | undefined): this {
        if (((this._Web_flagArray[80]) == (0)) || (true)) {
            this._Web_flagArray[80] = 1
            this._Web_onDataResubmitted_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[80] = 3
        }
        return this
    }
    pinchSmooth(value: boolean | undefined): this {
        if (((this._Web_flagArray[81]) == (0)) || ((this._Web_pinchSmooth_0_0value) !== (value))) {
            this._Web_flagArray[81] = 1
            this._Web_pinchSmooth_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[81] = 3
        }
        return this
    }
    allowWindowOpenMethod(value: boolean | undefined): this {
        if (((this._Web_flagArray[82]) == (0)) || ((this._Web_allowWindowOpenMethod_0_0value) !== (value))) {
            this._Web_flagArray[82] = 1
            this._Web_allowWindowOpenMethod_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[82] = 3
        }
        return this
    }
    onAudioStateChanged(value: arkui_component_common_Callback<OnAudioStateChangedEvent, void> | undefined): this {
        if (((this._Web_flagArray[83]) == (0)) || (true)) {
            this._Web_flagArray[83] = 1
            this._Web_onAudioStateChanged_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[83] = 3
        }
        return this
    }
    onFirstContentfulPaint(value: arkui_component_common_Callback<OnFirstContentfulPaintEvent, void> | undefined): this {
        if (((this._Web_flagArray[84]) == (0)) || (true)) {
            this._Web_flagArray[84] = 1
            this._Web_onFirstContentfulPaint_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[84] = 3
        }
        return this
    }
    onFirstMeaningfulPaint(value: OnFirstMeaningfulPaintCallback | undefined): this {
        if (((this._Web_flagArray[85]) == (0)) || (true)) {
            this._Web_flagArray[85] = 1
            this._Web_onFirstMeaningfulPaint_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[85] = 3
        }
        return this
    }
    onLargestContentfulPaint(value: OnLargestContentfulPaintCallback | undefined): this {
        if (((this._Web_flagArray[86]) == (0)) || (true)) {
            this._Web_flagArray[86] = 1
            this._Web_onLargestContentfulPaint_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[86] = 3
        }
        return this
    }
    onLoadIntercept(value: arkui_component_common_Callback<OnLoadInterceptEvent, boolean> | undefined): this {
        if (((this._Web_flagArray[87]) == (0)) || (true)) {
            this._Web_flagArray[87] = 1
            this._Web_onLoadIntercept_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[87] = 3
        }
        return this
    }
    onControllerAttached(value: (() => void) | undefined): this {
        if (((this._Web_flagArray[88]) == (0)) || (true)) {
            this._Web_flagArray[88] = 1
            this._Web_onControllerAttached_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[88] = 3
        }
        return this
    }
    onOverScroll(value: arkui_component_common_Callback<OnOverScrollEvent, void> | undefined): this {
        if (((this._Web_flagArray[89]) == (0)) || (true)) {
            this._Web_flagArray[89] = 1
            this._Web_onOverScroll_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[89] = 3
        }
        return this
    }
    onPdfScrollAtBottom(value: arkui_component_common_Callback<OnPdfScrollEvent, void> | undefined): this {
        if (((this._Web_flagArray[90]) == (0)) || (true)) {
            this._Web_flagArray[90] = 1
            this._Web_onPdfScrollAtBottom_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[90] = 3
        }
        return this
    }
    onPdfLoadEvent(value: arkui_component_common_Callback<OnPdfLoadEvent, void> | undefined): this {
        if (((this._Web_flagArray[91]) == (0)) || (true)) {
            this._Web_flagArray[91] = 1
            this._Web_onPdfLoadEvent_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[91] = 3
        }
        return this
    }
    onSafeBrowsingCheckResult(value: OnSafeBrowsingCheckResultCallback | undefined): this {
        if (((this._Web_flagArray[92]) == (0)) || (true)) {
            this._Web_flagArray[92] = 1
            this._Web_onSafeBrowsingCheckResult_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[92] = 3
        }
        return this
    }
    onSafeBrowsingCheckFinish(value: OnSafeBrowsingCheckResultCallback | undefined): this {
        if (((this._Web_flagArray[93]) == (0)) || (true)) {
            this._Web_flagArray[93] = 1
            this._Web_onSafeBrowsingCheckFinish_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[93] = 3
        }
        return this
    }
    onNavigationEntryCommitted(value: OnNavigationEntryCommittedCallback | undefined): this {
        if (((this._Web_flagArray[94]) == (0)) || (true)) {
            this._Web_flagArray[94] = 1
            this._Web_onNavigationEntryCommitted_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[94] = 3
        }
        return this
    }
    onIntelligentTrackingPreventionResult(value: OnIntelligentTrackingPreventionCallback | undefined): this {
        if (((this._Web_flagArray[95]) == (0)) || (true)) {
            this._Web_flagArray[95] = 1
            this._Web_onIntelligentTrackingPreventionResult_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[95] = 3
        }
        return this
    }
    javaScriptOnDocumentStart(value: Array<ScriptItem> | undefined): this {
        if (((this._Web_flagArray[96]) == (0)) || (true)) {
            this._Web_flagArray[96] = 1
            this._Web_javaScriptOnDocumentStart_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[96] = 3
        }
        return this
    }
    javaScriptOnDocumentEnd(value: Array<ScriptItem> | undefined): this {
        if (((this._Web_flagArray[97]) == (0)) || (true)) {
            this._Web_flagArray[97] = 1
            this._Web_javaScriptOnDocumentEnd_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[97] = 3
        }
        return this
    }
    layoutMode(value: WebLayoutMode | undefined): this {
        if (((this._Web_flagArray[98]) == (0)) || (true)) {
            this._Web_flagArray[98] = 1
            this._Web_layoutMode_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[98] = 3
        }
        return this
    }
    nestedScroll(value: NestedScrollOptions | NestedScrollOptionsExt | undefined): this {
        if (((this._Web_flagArray[99]) == (0)) || (true)) {
            this._Web_flagArray[99] = 1
            this._Web_nestedScroll_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[99] = 3
        }
        return this
    }
    enableNativeEmbedMode(value: boolean | undefined): this {
        if (((this._Web_flagArray[100]) == (0)) || ((this._Web_enableNativeEmbedMode_0_0value) !== (value))) {
            this._Web_flagArray[100] = 1
            this._Web_enableNativeEmbedMode_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[100] = 3
        }
        return this
    }
    onNativeEmbedLifecycleChange(value: ((event: NativeEmbedDataInfo) => void) | undefined): this {
        if (((this._Web_flagArray[101]) == (0)) || (true)) {
            this._Web_flagArray[101] = 1
            this._Web_onNativeEmbedLifecycleChange_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[101] = 3
        }
        return this
    }
    onNativeEmbedVisibilityChange(value: OnNativeEmbedVisibilityChangeCallback | undefined): this {
        if (((this._Web_flagArray[102]) == (0)) || (true)) {
            this._Web_flagArray[102] = 1
            this._Web_onNativeEmbedVisibilityChange_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[102] = 3
        }
        return this
    }
    onNativeEmbedGestureEvent(value: ((event: NativeEmbedTouchInfo) => void) | undefined): this {
        if (((this._Web_flagArray[103]) == (0)) || (true)) {
            this._Web_flagArray[103] = 1
            this._Web_onNativeEmbedGestureEvent_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[103] = 3
        }
        return this
    }
    onNativeEmbedMouseEvent(value: MouseInfoCallback | undefined): this {
        if (((this._Web_flagArray[104]) == (0)) || (true)) {
            this._Web_flagArray[104] = 1
            this._Web_onNativeEmbedMouseEvent_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[104] = 3
        }
        return this
    }
    copyOptions(value: CopyOptions | undefined): this {
        if (((this._Web_flagArray[105]) == (0)) || (true)) {
            this._Web_flagArray[105] = 1
            this._Web_copyOptions_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[105] = 3
        }
        return this
    }
    onOverrideUrlLoading(value: OnOverrideUrlLoadingCallback | undefined): this {
        if (((this._Web_flagArray[106]) == (0)) || (true)) {
            this._Web_flagArray[106] = 1
            this._Web_onOverrideUrlLoading_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[106] = 3
        }
        return this
    }
    onOverrideErrorPage(value: OnOverrideErrorPageCallback | undefined): this {
        if (((this._Web_flagArray[107]) == (0)) || (true)) {
            this._Web_flagArray[107] = 1
            this._Web_onOverrideErrorPage_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[107] = 3
        }
        return this
    }
    textAutosizing(value: boolean | undefined): this {
        if (((this._Web_flagArray[108]) == (0)) || ((this._Web_textAutosizing_0_0value) !== (value))) {
            this._Web_flagArray[108] = 1
            this._Web_textAutosizing_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[108] = 3
        }
        return this
    }
    enableNativeMediaPlayer(value: NativeMediaPlayerConfig | undefined): this {
        if (((this._Web_flagArray[109]) == (0)) || (true)) {
            this._Web_flagArray[109] = 1
            this._Web_enableNativeMediaPlayer_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[109] = 3
        }
        return this
    }
    onRenderProcessNotResponding(value: OnRenderProcessNotRespondingCallback | undefined): this {
        if (((this._Web_flagArray[110]) == (0)) || (true)) {
            this._Web_flagArray[110] = 1
            this._Web_onRenderProcessNotResponding_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[110] = 3
        }
        return this
    }
    onRenderProcessResponding(value: OnRenderProcessRespondingCallback | undefined): this {
        if (((this._Web_flagArray[111]) == (0)) || (true)) {
            this._Web_flagArray[111] = 1
            this._Web_onRenderProcessResponding_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[111] = 3
        }
        return this
    }
    onViewportFitChanged(value: OnViewportFitChangedCallback | undefined): this {
        if (((this._Web_flagArray[112]) == (0)) || (true)) {
            this._Web_flagArray[112] = 1
            this._Web_onViewportFitChanged_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[112] = 3
        }
        return this
    }
    onInterceptKeyboardAttach(value: WebKeyboardCallback | undefined): this {
        if (((this._Web_flagArray[113]) == (0)) || (true)) {
            this._Web_flagArray[113] = 1
            this._Web_onInterceptKeyboardAttach_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[113] = 3
        }
        return this
    }
    onAdsBlocked(value: OnAdsBlockedCallback | undefined): this {
        if (((this._Web_flagArray[114]) == (0)) || (true)) {
            this._Web_flagArray[114] = 1
            this._Web_onAdsBlocked_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[114] = 3
        }
        return this
    }
    keyboardAvoidMode(value: WebKeyboardAvoidMode | undefined): this {
        if (((this._Web_flagArray[115]) == (0)) || (true)) {
            this._Web_flagArray[115] = 1
            this._Web_keyboardAvoidMode_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[115] = 3
        }
        return this
    }
    editMenuOptions(value: EditMenuOptions | undefined): this {
        if (((this._Web_flagArray[116]) == (0)) || (true)) {
            this._Web_flagArray[116] = 1
            this._Web_editMenuOptions_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[116] = 3
        }
        return this
    }
    enableHapticFeedback(value: boolean | undefined): this {
        if (((this._Web_flagArray[117]) == (0)) || ((this._Web_enableHapticFeedback_0_0value) !== (value))) {
            this._Web_flagArray[117] = 1
            this._Web_enableHapticFeedback_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[117] = 3
        }
        return this
    }
    enableFollowSystemFontWeight(value: boolean | undefined): this {
        if (((this._Web_flagArray[118]) == (0)) || ((this._Web_enableFollowSystemFontWeight_0_0value) !== (value))) {
            this._Web_flagArray[118] = 1
            this._Web_enableFollowSystemFontWeight_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[118] = 3
        }
        return this
    }
    enableWebAVSession(value: boolean | undefined): this {
        if (((this._Web_flagArray[119]) == (0)) || ((this._Web_enableWebAVSession_0_0value) !== (value))) {
            this._Web_flagArray[119] = 1
            this._Web_enableWebAVSession_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[119] = 3
        }
        return this
    }
    optimizeParserBudget(value: boolean | undefined): this {
        if (((this._Web_flagArray[120]) == (0)) || ((this._Web_optimizeParserBudget_0_0value) !== (value))) {
            this._Web_flagArray[120] = 1
            this._Web_optimizeParserBudget_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[120] = 3
        }
        return this
    }
    runJavaScriptOnDocumentStart(value: Array<ScriptItem> | undefined): this {
        if (((this._Web_flagArray[121]) == (0)) || (true)) {
            this._Web_flagArray[121] = 1
            this._Web_runJavaScriptOnDocumentStart_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[121] = 3
        }
        return this
    }
    runJavaScriptOnDocumentEnd(value: Array<ScriptItem> | undefined): this {
        if (((this._Web_flagArray[122]) == (0)) || (true)) {
            this._Web_flagArray[122] = 1
            this._Web_runJavaScriptOnDocumentEnd_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[122] = 3
        }
        return this
    }
    runJavaScriptOnHeadEnd(value: Array<ScriptItem> | undefined): this {
        if (((this._Web_flagArray[123]) == (0)) || (true)) {
            this._Web_flagArray[123] = 1
            this._Web_runJavaScriptOnHeadEnd_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[123] = 3
        }
        return this
    }
    nativeEmbedOptions(value: EmbedOptions | undefined): this {
        if (((this._Web_flagArray[124]) == (0)) || (true)) {
            this._Web_flagArray[124] = 1
            this._Web_nativeEmbedOptions_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[124] = 3
        }
        return this
    }
    enableDataDetector(value: boolean | undefined): this {
        if (((this._Web_flagArray[125]) == (0)) || ((this._Web_enableDataDetector_0_0value) !== (value))) {
            this._Web_flagArray[125] = 1
            this._Web_enableDataDetector_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[125] = 3
        }
        return this
    }
    dataDetectorConfig(value: TextDataDetectorConfig | undefined): this {
        if (((this._Web_flagArray[126]) == (0)) || (true)) {
            this._Web_flagArray[126] = 1
            this._Web_dataDetectorConfig_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[126] = 3
        }
        return this
    }
    onActivateContent(value: VoidCallback | undefined): this {
        if (((this._Web_flagArray[127]) == (0)) || (true)) {
            this._Web_flagArray[127] = 1
            this._Web_onActivateContent_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[127] = 3
        }
        return this
    }
    bypassVsyncCondition(value: WebBypassVsyncCondition | undefined): this {
        if (((this._Web_flagArray[128]) == (0)) || (true)) {
            this._Web_flagArray[128] = 1
            this._Web_bypassVsyncCondition_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[128] = 3
        }
        return this
    }
    gestureFocusMode(value: GestureFocusMode | undefined): this {
        if (((this._Web_flagArray[129]) == (0)) || (true)) {
            this._Web_flagArray[129] = 1
            this._Web_gestureFocusMode_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[129] = 3
        }
        return this
    }
    forceEnableZoom(value: boolean | undefined): this {
        if (((this._Web_flagArray[130]) == (0)) || ((this._Web_forceEnableZoom_0_0value) !== (value))) {
            this._Web_flagArray[130] = 1
            this._Web_forceEnableZoom_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[130] = 3
        }
        return this
    }
    onNativeEmbedObjectParamChange(value: OnNativeEmbedObjectParamChangeCallback | undefined): this {
        if (((this._Web_flagArray[131]) == (0)) || (true)) {
            this._Web_flagArray[131] = 1
            this._Web_onNativeEmbedObjectParamChange_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[131] = 3
        }
        return this
    }
    rotateRenderEffect(value: WebRotateEffect | undefined): this {
        if (((this._Web_flagArray[132]) == (0)) || (true)) {
            this._Web_flagArray[132] = 1
            this._Web_rotateRenderEffect_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[132] = 3
        }
        return this
    }
    zoomControlAccess(value: boolean | undefined): this {
        if (((this._Web_flagArray[133]) == (0)) || ((this._Web_zoomControlAccess_0_0value) !== (value))) {
            this._Web_flagArray[133] = 1
            this._Web_zoomControlAccess_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[133] = 3
        }
        return this
    }
    onDetectedBlankScreen(value: OnDetectBlankScreenCallback | undefined): this {
        if (((this._Web_flagArray[134]) == (0)) || (true)) {
            this._Web_flagArray[134] = 1
            this._Web_onDetectedBlankScreen_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[134] = 3
        }
        return this
    }
    blankScreenDetectionConfig(value: BlankScreenDetectionConfig | undefined): this {
        if (((this._Web_flagArray[135]) == (0)) || (true)) {
            this._Web_flagArray[135] = 1
            this._Web_blankScreenDetectionConfig_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[135] = 3
        }
        return this
    }
    backToTop(value: boolean | undefined): this {
        if (((this._Web_flagArray[136]) == (0)) || ((this._Web_backToTop_0_0value) !== (value))) {
            this._Web_flagArray[136] = 1
            this._Web_backToTop_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[136] = 3
        }
        return this
    }
    enableSelectedDataDetector(value: boolean | undefined): this {
        if (((this._Web_flagArray[137]) == (0)) || ((this._Web_enableSelectedDataDetector_0_0value) !== (value))) {
            this._Web_flagArray[137] = 1
            this._Web_enableSelectedDataDetector_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[137] = 3
        }
        return this
    }
    onFirstScreenPaint(value: OnFirstScreenPaintCallback | undefined): this {
        if (((this._Web_flagArray[138]) == (0)) || (true)) {
            this._Web_flagArray[138] = 1
            this._Web_onFirstScreenPaint_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[138] = 3
        }
        return this
    }
    enableAutoFill(value: boolean | undefined): this {
        if (((this._Web_flagArray[139]) == (0)) || ((this._Web_enableAutoFill_0_0value) !== (value))) {
            this._Web_flagArray[139] = 1
            this._Web_enableAutoFill_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[139] = 3
        }
        return this
    }
    onTextSelectionChange(value: TextSelectionChangeCallback | undefined): this {
        if (((this._Web_flagArray[140]) == (0)) || (true)) {
            this._Web_flagArray[140] = 1
            this._Web_onTextSelectionChange_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[140] = 3
        }
        return this
    }
    enableImageAnalyzer(value: boolean | undefined): this {
        if (((this._Web_flagArray[141]) == (0)) || ((this._Web_enableImageAnalyzer_0_0value) !== (value))) {
            this._Web_flagArray[141] = 1
            this._Web_enableImageAnalyzer_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[141] = 3
        }
        return this
    }
    onCameraCaptureStateChange(value: OnCameraCaptureStateChangeCallback | undefined): this {
        if (((this._Web_flagArray[142]) == (0)) || (true)) {
            this._Web_flagArray[142] = 1
            this._Web_onCameraCaptureStateChange_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[142] = 3
        }
        return this
    }
    onMicrophoneCaptureStateChange(value: OnMicrophoneCaptureStateChangeCallback | undefined): this {
        if (((this._Web_flagArray[143]) == (0)) || (true)) {
            this._Web_flagArray[143] = 1
            this._Web_onMicrophoneCaptureStateChange_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[143] = 3
        }
        return this
    }
    enableDefaultContextMenu(value: boolean | undefined): this {
        if (((this._Web_flagArray[144]) == (0)) || ((this._Web_enableDefaultContextMenu_0_0value) !== (value))) {
            this._Web_flagArray[144] = 1
            this._Web_enableDefaultContextMenu_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[144] = 3
        }
        return this
    }
    enableDrag(value: boolean | undefined): this {
        if (((this._Web_flagArray[145]) == (0)) || ((this._Web_enableDrag_0_0value) !== (value))) {
            this._Web_flagArray[145] = 1
            this._Web_enableDrag_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[145] = 3
        }
        return this
    }
    scrollbarLayoutPolicy(value: ScrollbarLayoutPolicy | undefined): this {
        if (((this._Web_flagArray[146]) == (0)) || (true)) {
            this._Web_flagArray[146] = 1
            this._Web_scrollbarLayoutPolicy_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[146] = 3
        }
        return this
    }
    aiSessionOptions(value: Array<AISessionEvent> | undefined): this {
        if (((this._Web_flagArray[147]) == (0)) || (true)) {
            this._Web_flagArray[147] = 1
            this._Web_aiSessionOptions_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[147] = 3
        }
        return this
    }
    keyboardAppearance(value: WebKeyboardAppearanceMode | undefined): this {
        if (((this._Web_flagArray[148]) == (0)) || (true)) {
            this._Web_flagArray[148] = 1
            this._Web_keyboardAppearance_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[148] = 3
        }
        return this
    }
    onInputmethodAttached(value: OnInputmethodAttachedCallback | undefined): this {
        if (((this._Web_flagArray[149]) == (0)) || (true)) {
            this._Web_flagArray[149] = 1
            this._Web_onInputmethodAttached_0_0value = value
            this._state.fireChange()
        } else {
            this._Web_flagArray[149] = 3
        }
        return this
    }
    registerNativeEmbedRule(tag: string | undefined, type: string | undefined): this {
        if (((this._Web_flagArray[150]) == (0)) || ((this._Web_registerNativeEmbedRule_0_0value) !== (tag)) || ((this._Web_registerNativeEmbedRule_0_1value) !== (type))) {
            this._Web_flagArray[150] = 1
            this._Web_registerNativeEmbedRule_0_0value = tag
            this._Web_registerNativeEmbedRule_0_1value = type
            this._state.fireChange()
        } else {
            this._Web_flagArray[150] = 3
        }
        return this
    }
    bindSelectionMenu(elementType: WebElementType | undefined, content: CustomBuilder | undefined, responseType: WebResponseType | undefined, options?: SelectionMenuOptionsExt): this {
        if (((this._Web_flagArray[151]) == (0)) || (true) || (true) || (true) || (true)) {
            this._Web_flagArray[151] = 1
            this._Web_bindSelectionMenu_0_0value = elementType
            this._Web_bindSelectionMenu_0_1value = content
            this._Web_bindSelectionMenu_0_2value = responseType
            this._Web_bindSelectionMenu_0_3value = options
            this._state.fireChange()
        } else {
            this._Web_flagArray[151] = 3
        }
        return this
    }
    enableScrollDirectionalLock(value: boolean | undefined, type: ScrollDirectionalLockType | undefined): this {
        if (((this._Web_flagArray[152]) == (0)) || ((this._Web_enableScrollDirectionalLock_0_0value) !== (value)) || (true)) {
            this._Web_flagArray[152] = 1
            this._Web_enableScrollDirectionalLock_0_0value = value
            this._Web_enableScrollDirectionalLock_0_1value = type
            this._state.fireChange()
        } else {
            this._Web_flagArray[152] = 3
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<WebAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Not implemented')
    }
}
