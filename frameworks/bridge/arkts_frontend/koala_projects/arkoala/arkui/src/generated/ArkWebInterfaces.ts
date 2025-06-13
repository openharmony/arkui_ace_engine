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
import { KInt, KPointer, KBoolean, KStringPtr, wrapCallback } from "@koalaui/interop"
import { NodeAttach, remember } from "@koalaui/runtime"
import { SslErrorHandler } from "./ArkSslErrorHandlerMaterialized"
import { WebResourceRequest } from "./ArkWebResourceRequestMaterialized"
import { CustomBuilder, CommonMethod, Rectangle, PixelRoundPolicy, BackgroundEffectOptions, ForegroundEffectOptions, VisualEffect, Filter, BorderImageOption, OutlineStyle, AccessibilityCallback, AnimateParam, TransitionOptions, MotionBlurOptions, InvertOptions, TranslateOptions, ScaleOptions, RotateOptions, AlignRuleOption, LocalizedAlignRuleOptions, ClickEffect, UniformDataType, DragItemInfo, MotionPathOptions, ShadowOptions, ShadowStyle, StateStyles, PixelStretchEffectOptions, BackgroundBrightnessOptions, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, SizeChangeCallback, SafeAreaType, SafeAreaEdge, BlurStyle, BackgroundBlurStyleOptions, ForegroundBlurStyleOptions, TransitionFinishCallback, BlurOptions, LinearGradientBlurOptions, EffectType, sharedTransitionOptions, ChainStyle, DragPreviewOptions, DragInteractionOptions, ComponentContent, OverlayOptions, BlendMode, BlendApplyType, Blender, GeometryTransitionOptions, PopupOptions, CustomPopupOptions, MenuElement, MenuOptions, ContextMenuOptions, ModalTransition, ContentCoverOptions, SheetOptions, VisibleAreaChangeCallback, DrawContext, TouchTestInfo, TouchResult, AdaptiveColor, BlurStyleActivePolicy, RepeatMode, LinearGradient_common, FinishCallbackType, ExpectedFrameRateRange, TransitionEffects, TransitionEdge, MotionBlurAnchor, LocalizedHorizontalAlignParam, LocalizedVerticalAlignParam, PreDragStatus, ShadowType, UIGestureEvent, BlurStyleOptions, ThemeColorMode, FractionStop, DragPreviewMode, ImageModifier, OverlayOffset, TransitionHierarchyStrategy, PopupMessageOptions, SymbolGlyphModifier, MenuPreviewMode, ContextMenuAnimationOptions, BindOptions, SheetSize, SheetType, SheetTitleOptions, SheetMode, ScrollSizeMode, UIContext, SheetKeyboardAvoidMode, SourceTool, RectResult, TouchTestStrategy, EventTarget, SourceType, TouchObject, HistoricalPoint, IntentionCode, DragBehavior, Summary, DragResult, DismissPopupAction, DismissContentCoverAction, SheetDismiss, DismissSheetAction, SpringBackAction, DismissReason, NestedScrollOptions } from "./ArkCommonInterfaces"
import { WebKeyboardController } from "./ArkWebKeyboardControllerMaterialized"
import { FullScreenExitHandler } from "./ArkFullScreenExitHandlerMaterialized"
import { Resource } from "./ArkResourceInterfaces"
import { WebController } from "./ArkWebControllerMaterialized"
import { WebviewController } from "./ArkWebviewControllerMaterialized"
import { WebCookie } from "./ArkWebCookieMaterialized"
import { WebHeader, LengthUnit, ShapeSize, PathShapeOptions, RectShapeOptions, RoundRectShapeOptions } from "./ArkArkuiExternalInterfaces"
import { Length, SizeOptions, ConstraintSizeOptions, ChainWeightOptions, Padding, LocalizedPadding, Margin, LocalizedMargin, ResourceColor, Position, BorderOptions, EdgeStyles, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, Dimension, EdgeOutlineWidths, OutlineRadiuses, Edges, LocalizedEdges, LocalizedPosition, ResourceStr, AccessibilityOptions, PX, VP, FP, LPX, Percentage, Area, Bias, Font } from "./ArkUnitsInterfaces"
import { DrawModifier } from "./ArkDrawModifierMaterialized"
import { HitTestMode, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Color, Visibility, ItemAlign, Direction, GradientDirection, ObscuredReasons, RenderFit, ImageRepeat, Axis, ResponseType, FunctionKey, ModifierKey, PixelRoundCalcPolicy, Curve, PlayMode, TransitionType, HorizontalAlign, VerticalAlign, ClickEffectLevel, SharedTransitionEffectType, Placement, ArrowPointPosition, MouseButton, MouseAction, TouchType, KeyType, KeySource, FontWeight, FontStyle, CopyOptions, NestedScrollMode } from "./ArkEnumsInterfaces"
import { LengthMetrics } from "./ArkLengthMetricsMaterialized"
import { ResizableOptions, DrawingLattice } from "./ArkImageInterfaces"
import { FocusBoxStyle, FocusPriority } from "./ArkFocusInterfaces"
import { TransitionEffect } from "./ArkTransitionEffectMaterialized"
import { CircleShape } from "./ArkCircleShapeMaterialized"
import { EllipseShape } from "./ArkEllipseShapeMaterialized"
import { PathShape } from "./ArkPathShapeMaterialized"
import { RectShape } from "./ArkRectShapeMaterialized"
import { ProgressMask } from "./ArkProgressMaskMaterialized"
import { AttributeModifier } from "./../handwritten"
import { GestureModifier } from "./ArkGestureModifierMaterialized"
import { PixelMap } from "./ArkPixelMapMaterialized"
import { GestureType, GestureMask, GestureInfo, GestureJudgeResult, GestureInterface, TapGestureParameters, PanDirection, SwipeDirection, GestureMode, GestureHandler, GesturePriority, FingerInfo } from "./ArkGestureInterfaces"
import { TapGestureInterface } from "./ArkTapGestureInterfaceMaterialized"
import { LongPressGestureInterface } from "./ArkLongPressGestureInterfaceMaterialized"
import { PanGestureInterface } from "./ArkPanGestureInterfaceMaterialized"
import { PinchGestureInterface } from "./ArkPinchGestureInterfaceMaterialized"
import { SwipeGestureInterface } from "./ArkSwipeGestureInterfaceMaterialized"
import { RotationGestureInterface } from "./ArkRotationGestureInterfaceMaterialized"
import { GestureGroupInterface } from "./ArkGestureGroupInterfaceMaterialized"
import { ClickEvent } from "./ArkClickEventMaterialized"
import { HoverEvent } from "./ArkHoverEventMaterialized"
import { MouseEvent } from "./ArkMouseEventMaterialized"
import { TouchEvent } from "./ArkTouchEventMaterialized"
import { KeyEvent } from "./ArkKeyEventMaterialized"
import { ColorMetrics } from "./ArkColorMetricsMaterialized"
import { ICurve } from "./ArkICurveMaterialized"
import { DragEvent } from "./ArkDragEventMaterialized"
import { BaseGestureEvent } from "./ArkBaseGestureEventMaterialized"
import { PanGestureOptions } from "./ArkPanGestureOptionsMaterialized"
import { BaseEvent } from "./ArkBaseEventMaterialized"
import { UnifiedData } from "./ArkUnifiedDataMaterialized"
import { GestureControl } from "./ArkGestureControlNamespace"
import { GestureEvent } from "./ArkGestureEventMaterialized"
import { EditMenuOptions } from "./ArkEditMenuOptionsMaterialized"
import { WebResourceResponse } from "./ArkWebResourceResponseMaterialized"
import { TextMenuItem, TextRange, MenuType } from "./ArkTextCommonInterfaces"
import { JsGeolocation } from "./ArkJsGeolocationMaterialized"
import { JsResult } from "./ArkJsResultMaterialized"
import { ConsoleMessage } from "./ArkConsoleMessageMaterialized"
import { WebResourceError } from "./ArkWebResourceErrorMaterialized"
import { FileSelectorResult } from "./ArkFileSelectorResultMaterialized"
import { FileSelectorParam } from "./ArkFileSelectorParamMaterialized"
import { HttpAuthHandler } from "./ArkHttpAuthHandlerMaterialized"
import { PermissionRequest } from "./ArkPermissionRequestMaterialized"
import { ScreenCaptureHandler } from "./ArkScreenCaptureHandlerMaterialized"
import { WebContextMenuParam } from "./ArkWebContextMenuParamMaterialized"
import { WebContextMenuResult } from "./ArkWebContextMenuResultMaterialized"
import { ClientAuthenticationHandler } from "./ArkClientAuthenticationHandlerMaterialized"
import { ControllerHandler } from "./ArkControllerHandlerMaterialized"
import { DataResubmissionHandler } from "./ArkDataResubmissionHandlerMaterialized"
import { EventResult } from "./ArkEventResultMaterialized"
import { TextMenuItemId } from "./ArkTextMenuItemIdMaterialized"
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
    DEBUG,
    Debug = DEBUG,
    ERROR = 1,
    Error = ERROR,
    INFO = 2,
    Info = INFO,
    LOG = 3,
    Log = LOG,
    WARN = 4,
    Warn = WARN,
}
export enum MixedMode {
    ALL,
    All = ALL,
    COMPATIBLE = 1,
    Compatible = COMPATIBLE,
    NONE = 2,
    None = NONE,
}
export type OnSafeBrowsingCheckResultCallback = (threatType: ThreatType) => void;
export enum HitTestType {
    EDIT_TEXT,
    EditText = EDIT_TEXT,
    EMAIL = 1,
    Email = EMAIL,
    HTTP_ANCHOR = 2,
    HttpAnchor = HTTP_ANCHOR,
    HTTP_ANCHOR_IMG = 3,
    HttpAnchorImg = HTTP_ANCHOR_IMG,
    IMG = 4,
    Img = IMG,
    MAP = 5,
    Map = MAP,
    PHONE = 6,
    Phone = PHONE,
    UNKNOWN = 7,
    Unknown = UNKNOWN,
}
export enum CacheMode {
    DEFAULT,
    Default = DEFAULT,
    NONE = 1,
    None = NONE,
    ONLINE = 2,
    Online = ONLINE,
    ONLY = 3,
    Only = ONLY,
}
export enum OverScrollMode {
    NEVER,
    ALWAYS = 1,
}
export enum WebDarkMode {
    OFF,
    Off = OFF,
    ON = 1,
    On = ON,
    AUTO = 2,
    Auto = AUTO,
}
export enum WebCaptureMode {
    HOME_SCREEN,
}
export enum ThreatType {
    THREAT_ILLEGAL,
    THREAT_FRAUD = 1,
    THREAT_RISK = 2,
    THREAT_WARNING = 3,
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
    PROCESS_ABNORMAL_TERMINATION,
    ProcessAbnormalTermination = PROCESS_ABNORMAL_TERMINATION,
    PROCESS_WAS_KILLED = 1,
    ProcessWasKilled = PROCESS_WAS_KILLED,
    PROCESS_CRASHED = 2,
    ProcessCrashed = PROCESS_CRASHED,
    PROCESS_OOM = 3,
    ProcessOom = PROCESS_OOM,
    PROCESS_EXIT_UNKNOWN = 4,
    ProcessExitUnknown = PROCESS_EXIT_UNKNOWN,
}
export type OnContextMenuHideCallback = () => void;
export enum SslError {
    INVALID,
    Invalid = INVALID,
    HOST_MISMATCH = 1,
    HostMismatch = HOST_MISMATCH,
    DATE_INVALID = 2,
    DateInvalid = DATE_INVALID,
    UNTRUSTED = 3,
    Untrusted = UNTRUSTED,
}
export enum FileSelectorMode {
    FILE_OPEN_MODE,
    FileOpenMode = FILE_OPEN_MODE,
    FILE_OPEN_MULTIPLE_MODE = 1,
    FileOpenMultipleMode = FILE_OPEN_MULTIPLE_MODE,
    FILE_OPEN_FOLDER_MODE = 2,
    FileOpenFolderMode = FILE_OPEN_FOLDER_MODE,
    FILE_SAVE_MODE = 3,
    FileSaveMode = FILE_SAVE_MODE,
}
export enum WebLayoutMode {
    NONE,
    FIT_CONTENT = 1,
}
export enum RenderProcessNotRespondingReason {
    INPUT_TIMEOUT,
    NAVIGATION_COMMIT_TIMEOUT = 1,
}
export enum ProtectedResourceType {
    MIDI_SYSEX = "TYPE_MIDI_SYSEX",
    MidiSysex = MIDI_SYSEX,
    VIDEO_CAPTURE = "TYPE_VIDEO_CAPTURE",
    AUDIO_CAPTURE = "TYPE_AUDIO_CAPTURE",
    SENSOR = "TYPE_SENSOR",
}
export enum ContextMenuSourceType {
    NONE,
    None = NONE,
    MOUSE = 1,
    Mouse = MOUSE,
    LONG_PRESS = 2,
    LongPress = LONG_PRESS,
}
export enum ContextMenuMediaType {
    NONE,
    None = NONE,
    IMAGE = 1,
    Image = IMAGE,
}
export enum ContextMenuInputFieldType {
    NONE,
    None = NONE,
    PLAIN_TEXT = 1,
    PlainText = PLAIN_TEXT,
    PASSWORD = 2,
    Password = PASSWORD,
    NUMBER = 3,
    Number = NUMBER,
    TELEPHONE = 4,
    Telephone = TELEPHONE,
    OTHER = 5,
    Other = OTHER,
}
export enum NativeEmbedStatus {
    CREATE,
    UPDATE = 1,
    DESTROY = 2,
    ENTER_BFCACHE = 3,
    LEAVE_BFCACHE = 4,
}
export enum ContextMenuEditStateFlags {
    NONE,
    CAN_CUT = 1,
    CAN_COPY = 2,
    CAN_PASTE = 4,
    CAN_SELECT_ALL = 8,
}
export enum WebNavigationType {
    UNKNOWN,
    MAIN_FRAME_NEW_ENTRY = 1,
    MAIN_FRAME_EXISTING_ENTRY = 2,
    NAVIGATION_TYPE_NEW_SUBFRAME = 4,
    NAVIGATION_TYPE_AUTO_SUBFRAME = 5,
}
export enum RenderMode {
    ASYNC_RENDER,
    SYNC_RENDER = 1,
}
export enum ViewportFit {
    AUTO,
    CONTAINS = 1,
    COVER = 2,
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
    certChainData?: Array<ArrayBuffer>;
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
    RESIZE_VISUAL,
    RESIZE_CONTENT = 1,
    OVERLAYS_CONTENT = 2,
}
export enum WebElementType {
    IMAGE = 1,
}
export enum WebResponseType {
    LONG_PRESS = 1,
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
    onUrlLoadIntercept: ((event?: { data: string | WebResourceRequest }) => boolean);
    onSslErrorReceive: ((event?: { handler: Function, error: Object }) => void);
    onRenderExited: ((parameter: OnRenderExitedEvent) => void);
    onShowFileSelector: ((parameter: OnShowFileSelectorEvent) => boolean);

    onFileSelectorShow: ((event?: { callback_: Function, fileSelector: Object }) => void);
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
    action: ((selectedText: { plainText: string }) => void);
}
export interface NestedScrollOptionsExt {
    scrollUp?: NestedScrollMode;
    scrollDown?: NestedScrollMode;
    scrollRight?: NestedScrollMode;
    scrollLeft?: NestedScrollMode;
}
