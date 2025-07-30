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

import { int32, int64, float32 } from "@koalaui/common"
import { KInt, KPointer, KBoolean, KStringPtr, wrapCallback, NativeBuffer } from "@koalaui/interop"
import { NodeAttach, remember } from "@koalaui/runtime"
import { WebResourceRequest } from "./ArkWebResourceRequestMaterialized"
import { CustomBuilder, CommonMethod, Rectangle, TouchTestInfo, TouchResult, PixelRoundPolicy, BackgroundEffectOptions, ForegroundEffectOptions, VisualEffect, Filter, BorderImageOption, OutlineStyle, AccessibilityCallback, AnimateParam, TransitionOptions, MotionBlurOptions, InvertOptions, TranslateOptions, ScaleOptions, RotateOptions, AlignRuleOption, LocalizedAlignRuleOptions, ClickEffect, DragItemInfo, UniformDataType, PreDragStatus, MotionPathOptions, ShadowOptions, ShadowStyle, StateStyles, PixelStretchEffectOptions, BackgroundBrightnessOptions, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, SizeChangeCallback, SafeAreaType, SafeAreaEdge, BlurStyle, BackgroundBlurStyleOptions, ForegroundBlurStyleOptions, TransitionFinishCallback, BlurOptions, LinearGradientBlurOptions, EffectType, sharedTransitionOptions, ChainStyle, DragPreviewOptions, DragInteractionOptions, ComponentContent, OverlayOptions, BlendMode, BlendApplyType, Blender, GeometryTransitionOptions, PopupOptions, CustomPopupOptions, MenuElement, MenuOptions, ContextMenuOptions, ModalTransition, ContentCoverOptions, SheetOptions, VisibleAreaChangeCallback, NestedScrollOptions } from "./ArkCommonInterfaces"
import { WebKeyboardController } from "./ArkWebKeyboardControllerMaterialized"
import { FullScreenExitHandler } from "./ArkFullScreenExitHandlerMaterialized"
import { Resource } from "./ArkResourceInterfaces"
import { WebController } from "./ArkWebControllerMaterialized"
import { WebviewController } from "./ArkWebviewControllerMaterialized"
import { Position, Length, SizeOptions, ConstraintSizeOptions, ChainWeightOptions, Padding, LocalizedPadding, Margin, LocalizedMargin, ResourceColor, BorderOptions, EdgeStyles, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, Dimension, EdgeOutlineWidths, OutlineRadiuses, Area, Edges, LocalizedEdges, LocalizedPosition, ResourceStr, AccessibilityOptions } from "./ArkUnitsInterfaces"
import { TouchEvent } from "./ArkTouchEventMaterialized"
import { EventResult } from "./ArkEventResultMaterialized"
import { JsGeolocation } from "./ArkJsGeolocationMaterialized"
import { JsResult } from "./ArkJsResultMaterialized"
import { ConsoleMessage } from "./ArkConsoleMessageMaterialized"
import { WebResourceError } from "./ArkWebResourceErrorMaterialized"
import { WebResourceResponse } from "./ArkWebResourceResponseMaterialized"
import { FileSelectorResult } from "./ArkFileSelectorResultMaterialized"
import { FileSelectorParam } from "./ArkFileSelectorParamMaterialized"
import { HttpAuthHandler } from "./ArkHttpAuthHandlerMaterialized"
import { PermissionRequest } from "./ArkPermissionRequestMaterialized"
import { ScreenCaptureHandler } from "./ArkScreenCaptureHandlerMaterialized"
import { WebContextMenuParam } from "./ArkWebContextMenuParamMaterialized"
import { WebContextMenuResult } from "./ArkWebContextMenuResultMaterialized"
import { SslErrorHandler } from "./ArkSslErrorHandlerMaterialized"
import { ClientAuthenticationHandler } from "./ArkClientAuthenticationHandlerMaterialized"
import { ControllerHandler } from "./ArkControllerHandlerMaterialized"
import { PixelMap } from "./ArkPixelMapMaterialized"
import { DataResubmissionHandler } from "./ArkDataResubmissionHandlerMaterialized"
import { Callback_Void, Callback_Array_TouchTestInfo_TouchResult, Callback_ClickEvent_Void, Callback_Boolean_HoverEvent_Void, Callback_MouseEvent_Void, Callback_TouchEvent_Void, Callback_KeyEvent_Void, Callback_KeyEvent_Boolean, Callback_Area_Area_Void, Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs, Literal_Number_offset_span, Callback_DragEvent_String_Union_CustomBuilder_DragItemInfo, Callback_DragEvent_String_Void, Callback_PreDragStatus_Void, Type_CommonMethod_linearGradient_value, Tuple_ResourceColor_Number, Type_CommonMethod_sweepGradient_value, Tuple_Length_Length, Type_CommonMethod_radialGradient_value, Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult, Callback_TouchEvent_HitTestMode, Literal_Alignment_align, Callback_OnPageEndEvent_Void, Callback_OnPageBeginEvent_Void, Callback_OnProgressChangeEvent_Void, Callback_OnTitleReceiveEvent_Void, Callback_OnGeolocationShowEvent_Void, Callback_OnAlertEvent_Boolean, Callback_OnBeforeUnloadEvent_Boolean, Callback_OnConfirmEvent_Boolean, Callback_OnPromptEvent_Boolean, Callback_OnConsoleEvent_Boolean, Callback_OnErrorReceiveEvent_Void, Callback_OnHttpErrorReceiveEvent_Void, Callback_OnDownloadStartEvent_Void, Callback_OnRefreshAccessedHistoryEvent_Void, Type_WebAttribute_onUrlLoadIntercept_callback, Literal_Union_String_WebResourceRequest_data, Callback_Literal_Function_handler_Object_error_Void, Literal_Function_handler_Object_error, Callback_OnRenderExitedEvent_Void, Callback_OnShowFileSelectorEvent_Boolean, Callback_Literal_Object_detail_Boolean, Literal_Object_detail, Type_WebAttribute_onFileSelectorShow_callback, Literal_Function_callback__Object_fileSelector, Callback_OnResourceLoadEvent_Void, Callback_OnScaleChangeEvent_Void, Callback_OnHttpAuthRequestEvent_Boolean, Callback_OnInterceptRequestEvent_WebResourceResponse, Callback_OnPermissionRequestEvent_Void, Callback_OnScreenCaptureRequestEvent_Void, Callback_OnContextMenuShowEvent_Boolean, Callback_OnSearchResultReceiveEvent_Void, Callback_OnScrollEvent_Void, Callback_OnSslErrorEventReceiveEvent_Void, Callback_OnClientAuthenticationEvent_Void, Callback_OnWindowNewEvent_Void, Callback_OnTouchIconUrlReceivedEvent_Void, Callback_OnFaviconReceivedEvent_Void, Callback_OnPageVisibleEvent_Void, Callback_OnDataResubmittedEvent_Void, Callback_OnAudioStateChangedEvent_Void, Callback_OnFirstContentfulPaintEvent_Void, Callback_OnLoadInterceptEvent_Boolean, Callback_OnOverScrollEvent_Void, Callback_NativeEmbedDataInfo_Void, Callback_NativeEmbedTouchInfo_Void, Callback_Literal_String_plainText_Void, Literal_String_plainText } from "./SyntheticDeclarations"
import { MenuType } from "./ArkTextCommonInterfaces"
import { DrawModifier } from "./ArkDrawModifierMaterialized"
import { HitTestMode, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Color, Visibility, ItemAlign, Direction, GradientDirection, ObscuredReasons, RenderFit, ImageRepeat, Axis, ResponseType, FunctionKey, ModifierKey, CopyOptions, NestedScrollMode } from "./ArkEnumsInterfaces"
import { LengthMetrics } from "./ArkLengthMetricsMaterialized"
import { ResizableOptions } from "./ArkImageInterfaces"
import { ClickEvent } from "./ArkClickEventMaterialized"
import { HoverEvent } from "./ArkHoverEventMaterialized"
import { MouseEvent } from "./ArkMouseEventMaterialized"
import { KeyEvent } from "./ArkKeyEventMaterialized"
import { FocusBoxStyle, FocusPriority } from "./ArkFocusInterfaces"
import { TransitionEffect } from "./ArkTransitionEffectMaterialized"
import { DragEvent } from "./ArkDragEventMaterialized"
import { CircleShape } from "./ArkCircleShapeMaterialized"
import { EllipseShape } from "./ArkEllipseShapeMaterialized"
import { PathShape } from "./ArkPathShapeMaterialized"
import { RectShape } from "./ArkRectShapeMaterialized"
import { ProgressMask } from "./ArkProgressMaskMaterialized"
import { AttributeModifier } from "./../handwritten"
import { GestureModifier } from "./ArkGestureModifierMaterialized"
import { GestureInfo, GestureJudgeResult, GestureType, GestureMask } from "./ArkGestureInterfaces"
import { BaseGestureEvent } from "./ArkBaseGestureEventMaterialized"
import { EditMenuOptions } from "./ArkEditMenuOptionsMaterialized"
export type OnNavigationEntryCommittedCallback = (loadCommittedDetails: LoadCommittedDetails) => void;
export type OnSslErrorEventCallback = (sslErrorEvent: SslErrorEvent) => void;
export type OnLargestContentfulPaintCallback = (largestContentfulPaint: LargestContentfulPaint) => void;
export type OnFirstMeaningfulPaintCallback = (firstMeaningfulPaint: FirstMeaningfulPaint) => void;
export type OnOverrideUrlLoadingCallback = (webResourceRequest: WebResourceRequest) => boolean;
export type OnIntelligentTrackingPreventionCallback = (details: IntelligentTrackingPreventionDetails) => void;
export type OnNativeEmbedVisibilityChangeCallback = (nativeEmbedVisibilityInfo: NativeEmbedVisibilityInfo) => void;
export interface NativeMediaPlayerConfig {
    enable: boolean;
    shouldOverlay: boolean;
}
export type OnRenderProcessNotRespondingCallback = (data: RenderProcessNotRespondingData) => void;
export type OnRenderProcessRespondingCallback = () => void;
export type OnViewportFitChangedCallback = (viewportFit: ViewportFit) => void;
export type OnAdsBlockedCallback = (details: AdsBlockedDetails) => void;
export interface AdsBlockedDetails {
    url: string;
    adsBlocked: Array<string>;
}
export interface WebKeyboardOptions {
    useSystemKeyboard: boolean;
    enterKeyType?: number;
    customKeyboard?: CustomBuilder;
}
export interface WebKeyboardCallbackInfo {
    controller: WebKeyboardController;
    attributes: Map<string, string>;
}
export type WebKeyboardCallback = (keyboardCallbackInfo: WebKeyboardCallbackInfo) => WebKeyboardOptions;
export enum MessageLevel {
    DEBUG = 0,
    Debug = 0,
    ERROR = 1,
    Error = 1,
    INFO = 2,
    Info = 2,
    LOG = 3,
    Log = 3,
    WARN = 4,
    Warn = 4
}
export enum MixedMode {
    ALL = 0,
    All = 0,
    COMPATIBLE = 1,
    Compatible = 1,
    NONE = 2,
    None = 2
}
export type OnSafeBrowsingCheckResultCallback = (threatType: ThreatType) => void;
export enum HitTestType {
    EDIT_TEXT = 0,
    EditText = 0,
    EMAIL = 1,
    Email = 1,
    HTTP_ANCHOR = 2,
    HttpAnchor = 2,
    HTTP_ANCHOR_IMG = 3,
    HttpAnchorImg = 3,
    IMG = 4,
    Img = 4,
    MAP = 5,
    Map = 5,
    PHONE = 6,
    Phone = 6,
    UNKNOWN = 7,
    Unknown = 7
}
export enum CacheMode {
    DEFAULT = 0,
    Default = 0,
    NONE = 1,
    None = 1,
    ONLINE = 2,
    Online = 2,
    ONLY = 3,
    Only = 3
}
export enum OverScrollMode {
    NEVER = 0,
    ALWAYS = 1
}
export enum WebDarkMode {
    OFF = 0,
    Off = 0,
    ON = 1,
    On = 1,
    AUTO = 2,
    Auto = 2
}
export enum WebCaptureMode {
    HOME_SCREEN = 0
}
export enum ThreatType {
    THREAT_ILLEGAL = 0,
    THREAT_FRAUD = 1,
    THREAT_RISK = 2,
    THREAT_WARNING = 3
}
export interface WebMediaOptions {
    resumeInterval?: number;
    audioExclusive?: boolean;
}
export interface ScreenCaptureConfig {
    captureMode: WebCaptureMode;
}
export interface FullScreenEnterEvent {
    handler: FullScreenExitHandler;
    videoWidth?: number;
    videoHeight?: number;
}
export type OnFullScreenEnterCallback = (event: FullScreenEnterEvent) => void;
export enum RenderExitReason {
    PROCESS_ABNORMAL_TERMINATION = 0,
    ProcessAbnormalTermination = 0,
    PROCESS_WAS_KILLED = 1,
    ProcessWasKilled = 1,
    PROCESS_CRASHED = 2,
    ProcessCrashed = 2,
    PROCESS_OOM = 3,
    ProcessOom = 3,
    PROCESS_EXIT_UNKNOWN = 4,
    ProcessExitUnknown = 4
}
export type OnContextMenuHideCallback = () => void;
export enum SslError {
    INVALID = 0,
    Invalid = 0,
    HOST_MISMATCH = 1,
    HostMismatch = 1,
    DATE_INVALID = 2,
    DateInvalid = 2,
    UNTRUSTED = 3,
    Untrusted = 3
}
export enum FileSelectorMode {
    FILE_OPEN_MODE = 0,
    FileOpenMode = 0,
    FILE_OPEN_MULTIPLE_MODE = 1,
    FileOpenMultipleMode = 1,
    FILE_OPEN_FOLDER_MODE = 2,
    FileOpenFolderMode = 2,
    FILE_SAVE_MODE = 3,
    FileSaveMode = 3
}
export enum WebLayoutMode {
    NONE = 0,
    FIT_CONTENT = 1
}
export enum RenderProcessNotRespondingReason {
    INPUT_TIMEOUT = 0,
    NAVIGATION_COMMIT_TIMEOUT = 1
}
export enum ProtectedResourceType {
    MIDI_SYSEX = "TYPE_MIDI_SYSEX",
    MidiSysex = "TYPE_MIDI_SYSEX",
    VIDEO_CAPTURE = "TYPE_VIDEO_CAPTURE",
    AUDIO_CAPTURE = "TYPE_AUDIO_CAPTURE",
    SENSOR = "TYPE_SENSOR"
}
export enum ContextMenuSourceType {
    NONE = 0,
    None = 0,
    MOUSE = 1,
    Mouse = 1,
    LONG_PRESS = 2,
    LongPress = 2
}
export enum ContextMenuMediaType {
    NONE = 0,
    None = 0,
    IMAGE = 1,
    Image = 1
}
export enum ContextMenuInputFieldType {
    NONE = 0,
    None = 0,
    PLAIN_TEXT = 1,
    PlainText = 1,
    PASSWORD = 2,
    Password = 2,
    NUMBER = 3,
    Number = 3,
    TELEPHONE = 4,
    Telephone = 4,
    OTHER = 5,
    Other = 5
}
export enum NativeEmbedStatus {
    CREATE = 0,
    UPDATE = 1,
    DESTROY = 2,
    ENTER_BFCACHE = 3,
    LEAVE_BFCACHE = 4
}
export enum ContextMenuEditStateFlags {
    NONE = 0,
    CAN_CUT = 1,
    CAN_COPY = 2,
    CAN_PASTE = 4,
    CAN_SELECT_ALL = 8
}
export enum WebNavigationType {
    UNKNOWN = 0,
    MAIN_FRAME_NEW_ENTRY = 1,
    MAIN_FRAME_EXISTING_ENTRY = 2,
    NAVIGATION_TYPE_NEW_SUBFRAME = 4,
    NAVIGATION_TYPE_AUTO_SUBFRAME = 5
}
export enum RenderMode {
    ASYNC_RENDER = 0,
    SYNC_RENDER = 1
}
export enum ViewportFit {
    AUTO = 0,
    CONTAINS = 1,
    COVER = 2
}
export interface Header {
    headerKey: string;
    headerValue: string;
}
export interface WebOptions {
    src: string | Resource;
    controller: WebController | WebviewController;
    renderMode?: RenderMode;
    incognitoMode?: boolean;
    sharedRenderProcessToken?: string;
}
export interface ScriptItem {
    script: string;
    scriptRules: Array<string>;
}
export interface LoadCommittedDetails {
    isMainFrame: boolean;
    isSameDocument: boolean;
    didReplaceEntry: boolean;
    navigationType: WebNavigationType;
    url: string;
}
export interface IntelligentTrackingPreventionDetails {
    host: string;
    trackerHost: string;
}
export type WebInterface = (value: WebOptions) => WebAttribute;
export interface NativeEmbedInfo {
    id?: string;
    type?: string;
    src?: string;
    position?: Position;
    width?: number;
    height?: number;
    url?: string;
    tag?: string;
    params?: Map<string, string>;
}
export interface NativeEmbedDataInfo {
    status?: NativeEmbedStatus;
    surfaceId?: string;
    embedId?: string;
    info?: NativeEmbedInfo;
}
export interface NativeEmbedVisibilityInfo {
    visibility: boolean;
    embedId: string;
}
export interface NativeEmbedTouchInfo {
    embedId?: string;
    touchEvent?: TouchEvent;
    result?: EventResult;
}
export interface FirstMeaningfulPaint {
    navigationStartTime?: number;
    firstMeaningfulPaintTime?: number;
}
export interface LargestContentfulPaint {
    navigationStartTime?: number;
    largestImagePaintTime?: number;
    largestTextPaintTime?: number;
    imageBPP?: number;
    largestImageLoadStartTime?: number;
    largestImageLoadEndTime?: number;
}
export interface RenderProcessNotRespondingData {
    jsStack: string;
    pid: number;
    reason: RenderProcessNotRespondingReason;
}
export interface OnPageEndEvent {
    url: string;
}
export interface OnPageBeginEvent {
    url: string;
}
export interface OnProgressChangeEvent {
    newProgress: number;
}
export interface OnTitleReceiveEvent {
    title: string;
}
export interface OnGeolocationShowEvent {
    origin: string;
    geolocation: JsGeolocation;
}
export interface OnAlertEvent {
    url: string;
    message: string;
    result: JsResult;
}
export interface OnBeforeUnloadEvent {
    url: string;
    message: string;
    result: JsResult;
}
export interface OnConfirmEvent {
    url: string;
    message: string;
    result: JsResult;
}
export interface OnPromptEvent {
    url: string;
    message: string;
    value: string;
    result: JsResult;
}
export interface OnConsoleEvent {
    message: ConsoleMessage;
}
export interface OnErrorReceiveEvent {
    request: WebResourceRequest;
    error: WebResourceError;
}
export interface OnHttpErrorReceiveEvent {
    request: WebResourceRequest;
    response: WebResourceResponse;
}
export interface OnDownloadStartEvent {
    url: string;
    userAgent: string;
    contentDisposition: string;
    mimetype: string;
    contentLength: number;
}
export interface OnRefreshAccessedHistoryEvent {
    url: string;
    isRefreshed: boolean;
}
export interface OnRenderExitedEvent {
    renderExitReason: RenderExitReason;
}
export interface OnShowFileSelectorEvent {
    result: FileSelectorResult;
    fileSelector: FileSelectorParam;
}
export interface OnResourceLoadEvent {
    url: string;
}
export interface OnScaleChangeEvent {
    oldScale: number;
    newScale: number;
}
export interface OnHttpAuthRequestEvent {
    handler: HttpAuthHandler;
    host: string;
    realm: string;
}
export interface OnInterceptRequestEvent {
    request: WebResourceRequest;
}
export interface OnPermissionRequestEvent {
    request: PermissionRequest;
}
export interface OnScreenCaptureRequestEvent {
    handler: ScreenCaptureHandler;
}
export interface OnContextMenuShowEvent {
    param: WebContextMenuParam;
    result: WebContextMenuResult;
}
export interface OnSearchResultReceiveEvent {
    activeMatchOrdinal: number;
    numberOfMatches: number;
    isDoneCounting: boolean;
}
export interface OnScrollEvent {
    xOffset: number;
    yOffset: number;
}
export interface OnSslErrorEventReceiveEvent {
    handler: SslErrorHandler;
    error: SslError;
    certChainData?: Array<NativeBuffer>;
}
export interface OnClientAuthenticationEvent {
    handler: ClientAuthenticationHandler;
    host: string;
    port: number;
    keyTypes: Array<string>;
    issuers: Array<string>;
}
export interface OnWindowNewEvent {
    isAlert: boolean;
    isUserTrigger: boolean;
    targetUrl: string;
    handler: ControllerHandler;
}
export interface OnTouchIconUrlReceivedEvent {
    url: string;
    precomposed: boolean;
}
export interface OnFaviconReceivedEvent {
    favicon: PixelMap;
}
export interface OnPageVisibleEvent {
    url: string;
}
export interface OnDataResubmittedEvent {
    handler: DataResubmissionHandler;
}
export interface OnAudioStateChangedEvent {
    playing: boolean;
}
export interface OnFirstContentfulPaintEvent {
    navigationStartTick: number;
    firstContentfulPaintMs: number;
}
export interface OnLoadInterceptEvent {
    data: WebResourceRequest;
}
export interface OnOverScrollEvent {
    xOffset: number;
    yOffset: number;
}
export interface JavaScriptProxy {
    object_: Object;
    name: string;
    methodList: Array<string>;
    controller: WebController | WebviewController;
    asyncMethodList?: Array<string>;
    permission?: string;
}
export enum WebKeyboardAvoidMode {
    RESIZE_VISUAL = 0,
    RESIZE_CONTENT = 1,
    OVERLAYS_CONTENT = 2
}
export enum WebElementType {
    IMAGE = 1
}
export enum WebResponseType {
    LONG_PRESS = 1
}
export interface SelectionMenuOptionsExt {
    onAppear?: (() => void);
    onDisappear?: (() => void);
    preview?: CustomBuilder;
    menuType?: MenuType;
}
export interface WebAttribute extends CommonMethod<WebAttribute> {
    javaScriptAccess: boolean;
    fileAccess: boolean;
    onlineImageAccess: boolean;
    domStorageAccess: boolean;
    imageAccess: boolean;
    mixedMode: MixedMode;
    zoomAccess: boolean;
    geolocationAccess: boolean;
    javaScriptProxy: JavaScriptProxy;
    password: boolean;
    cacheMode: CacheMode;
    darkMode: WebDarkMode;
    forceDarkAccess: boolean;
    mediaOptions: WebMediaOptions;
    tableData: boolean;
    wideViewModeAccess: boolean;
    overviewModeAccess: boolean;
    overScrollMode: OverScrollMode;
    textZoomAtio: number;
    textZoomRatio: number;
    databaseAccess: boolean;
    initialScale: number;
    userAgent: string;
    metaViewport: boolean;
    onPageEnd: ((parameter: OnPageEndEvent) => void);
    onPageBegin: ((parameter: OnPageBeginEvent) => void);
    onProgressChange: ((parameter: OnProgressChangeEvent) => void);
    onTitleReceive: ((parameter: OnTitleReceiveEvent) => void);
    onGeolocationHide: (() => void);
    onGeolocationShow: ((parameter: OnGeolocationShowEvent) => void);
    onRequestSelected: (() => void);
    onAlert: ((parameter: OnAlertEvent) => boolean);
    onBeforeUnload: ((parameter: OnBeforeUnloadEvent) => boolean);
    onConfirm: ((parameter: OnConfirmEvent) => boolean);
    onPrompt: ((parameter: OnPromptEvent) => boolean);
    onConsole: ((parameter: OnConsoleEvent) => boolean);
    onErrorReceive: ((parameter: OnErrorReceiveEvent) => void);
    onHttpErrorReceive: ((parameter: OnHttpErrorReceiveEvent) => void);
    onDownloadStart: ((parameter: OnDownloadStartEvent) => void);
    onRefreshAccessedHistory: ((parameter: OnRefreshAccessedHistoryEvent) => void);
    onUrlLoadIntercept: ((event?: Literal_Union_String_WebResourceRequest_data) => boolean);
    onSslErrorReceive: ((event?: Literal_Function_handler_Object_error) => void);
    onRenderExited: ((parameter: OnRenderExitedEvent) => void);
    onShowFileSelector: ((parameter: OnShowFileSelectorEvent) => boolean);

    onFileSelectorShow: ((event?: Literal_Function_callback__Object_fileSelector) => void);
    onResourceLoad: ((parameter: OnResourceLoadEvent) => void);
    onFullScreenExit: (() => void);
    onFullScreenEnter: OnFullScreenEnterCallback;
    onScaleChange: ((parameter: OnScaleChangeEvent) => void);
    onHttpAuthRequest: ((parameter: OnHttpAuthRequestEvent) => boolean);
    onInterceptRequest: ((parameter: OnInterceptRequestEvent) => WebResourceResponse);
    onPermissionRequest: ((parameter: OnPermissionRequestEvent) => void);
    onScreenCaptureRequest: ((parameter: OnScreenCaptureRequestEvent) => void);
    onContextMenuShow: ((parameter: OnContextMenuShowEvent) => boolean);
    onContextMenuHide: OnContextMenuHideCallback;
    mediaPlayGestureAccess: boolean;
    onSearchResultReceive: ((parameter: OnSearchResultReceiveEvent) => void);
    onScroll: ((parameter: OnScrollEvent) => void);
    onSslErrorEventReceive: ((parameter: OnSslErrorEventReceiveEvent) => void);
    onSslErrorEvent: OnSslErrorEventCallback;
    onClientAuthenticationRequest: ((parameter: OnClientAuthenticationEvent) => void);
    onWindowNew: ((parameter: OnWindowNewEvent) => void);
    onWindowExit: (() => void);
    multiWindowAccess: boolean;
    onInterceptKeyEvent: ((parameter: KeyEvent) => boolean);
    webStandardFont: string;
    webSerifFont: string;
    webSansSerifFont: string;
    webFixedFont: string;
    webFantasyFont: string;
    webCursiveFont: string;
    defaultFixedFontSize: number;
    defaultFontSize: number;
    minFontSize: number;
    minLogicalFontSize: number;
    defaultTextEncodingFormat: string;
    forceDisplayScrollBar: boolean;
    blockNetwork: boolean;
    horizontalScrollBarAccess: boolean;
    verticalScrollBarAccess: boolean;
    onTouchIconUrlReceived: ((parameter: OnTouchIconUrlReceivedEvent) => void);
    onFaviconReceived: ((parameter: OnFaviconReceivedEvent) => void);
    onPageVisible: ((parameter: OnPageVisibleEvent) => void);
    onDataResubmitted: ((parameter: OnDataResubmittedEvent) => void);
    pinchSmooth: boolean;
    allowWindowOpenMethod: boolean;
    onAudioStateChanged: ((parameter: OnAudioStateChangedEvent) => void);
    onFirstContentfulPaint: ((parameter: OnFirstContentfulPaintEvent) => void);
    onFirstMeaningfulPaint: OnFirstMeaningfulPaintCallback;
    onLargestContentfulPaint: OnLargestContentfulPaintCallback;
    onLoadIntercept: ((parameter: OnLoadInterceptEvent) => boolean);
    onControllerAttached: (() => void);
    onOverScroll: ((parameter: OnOverScrollEvent) => void);
    onSafeBrowsingCheckResult: OnSafeBrowsingCheckResultCallback;
    onNavigationEntryCommitted: OnNavigationEntryCommittedCallback;
    onIntelligentTrackingPreventionResult: OnIntelligentTrackingPreventionCallback;
    javaScriptOnDocumentStart: Array<ScriptItem>;
    javaScriptOnDocumentEnd: Array<ScriptItem>;
    layoutMode: WebLayoutMode;
    nestedScroll: NestedScrollOptions | NestedScrollOptionsExt;
    enableNativeEmbedMode: boolean;
    onNativeEmbedLifecycleChange: ((event: NativeEmbedDataInfo) => void);
    onNativeEmbedVisibilityChange: OnNativeEmbedVisibilityChangeCallback;
    onNativeEmbedGestureEvent: ((event: NativeEmbedTouchInfo) => void);
    copyOptions: CopyOptions;
    onOverrideUrlLoading: OnOverrideUrlLoadingCallback;
    textAutosizing: boolean;
    enableNativeMediaPlayer: NativeMediaPlayerConfig;
    enableSmoothDragResize: boolean;
    onRenderProcessNotResponding: OnRenderProcessNotRespondingCallback;
    onRenderProcessResponding: OnRenderProcessRespondingCallback;
    selectionMenuOptions: Array<ExpandedMenuItemOptions>;
    onViewportFitChanged: OnViewportFitChangedCallback;
    onInterceptKeyboardAttach: WebKeyboardCallback;
    onAdsBlocked: OnAdsBlockedCallback;
    keyboardAvoidMode: WebKeyboardAvoidMode;
    editMenuOptions: EditMenuOptions;
    enableHapticFeedback: boolean;
}
export interface SslErrorEvent {
    handler: SslErrorHandler;
    error: SslError;
    url: string;
    originalUrl: string;
    referrer: string;
    isFatalError: boolean;
    isMainFrame: boolean;
}
export interface ExpandedMenuItemOptions {
    content: ResourceStr;
    startIcon?: ResourceStr;
    action: ((selectedText: Literal_String_plainText) => void);
}
export interface NestedScrollOptionsExt {
    scrollUp?: NestedScrollMode;
    scrollDown?: NestedScrollMode;
    scrollRight?: NestedScrollMode;
    scrollLeft?: NestedScrollMode;
}
