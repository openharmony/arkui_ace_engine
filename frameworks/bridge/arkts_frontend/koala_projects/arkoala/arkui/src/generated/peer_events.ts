import { int32, float32 } from "@koalaui/common"
import { KStringPtr, KPointer, RuntimeType } from "@koalaui/interop"
import { Deserializer } from "./peers/Deserializer"
import { OnAlphabetIndexerSelectCallback, OnAlphabetIndexerRequestPopupDataCallback, OnAlphabetIndexerPopupSelectCallback } from "./ArkAlphabetIndexerInterfaces"
import { CalendarSelectedDate, CalendarRequestedData } from "./ArkCalendarInterfaces"
import { VoidCallback, Area, Length, Position, SizeOptions, ResourceStr, ResourceColor, Dimension, Margin, BorderRadiuses } from "./ArkUnitsInterfaces"
import { OnCheckboxChangeCallback } from "./ArkCheckboxInterfaces"
import { OnCheckboxGroupChangeCallback, CheckboxGroupResult, SelectStatus } from "./ArkCheckboxgroupInterfaces"
import { TouchTestInfo, TouchResult, RectResult, TouchTestStrategy, EventTarget, SourceType, SourceTool, AccessibilityCallback, TouchObject, HistoricalPoint, IntentionCode, CustomBuilder, DragItemInfo, DragBehavior, Summary, DragResult, Rectangle, PreDragStatus, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, SizeChangeCallback, VisibleAreaChangeCallback, ItemDragInfo, ShadowOptions, ShadowType } from "./ArkCommonInterfaces"
import { ClickEvent } from "./ArkClickEventMaterialized"
import { BaseEvent } from "./ArkBaseEventMaterialized"
import { Resource } from "./ArkResourceInterfaces"
import { HoverEvent } from "./ArkHoverEventMaterialized"
import { AccessibilityHoverEvent } from "./ArkAccessibilityHoverEventMaterialized"
import { AccessibilityHoverType, MouseButton, MouseAction, TouchType, KeyType, KeySource, HitTestMode, FoldStatus, AppRotation, FontStyle, FontWeight, TextAlign, WordBreak, LineBreakStrategy, ImageSpanAlignment, ImageFit, TextDecorationType, TextDecorationStyle, Color, ColoringStrategy, Edge } from "./ArkEnumsInterfaces"
import { MouseEvent } from "./ArkMouseEventMaterialized"
import { TouchEvent } from "./ArkTouchEventMaterialized"
import { KeyEvent } from "./ArkKeyEventMaterialized"
import { DragEvent } from "./ArkDragEventMaterialized"
import { UnifiedData } from "./ArkUnifiedDataMaterialized"
import { PixelMap } from "./ArkPixelMapMaterialized"
import { GestureInfo, GestureJudgeResult, FingerInfo, GestureRecognizerState } from "./ArkGestureInterfaces"
import { BaseGestureEvent } from "./ArkBaseGestureEventMaterialized"
import { GestureControl } from "./ArkGestureControlNamespace"
import { GestureRecognizer } from "./ArkGestureRecognizerMaterialized"
import { EventTargetInfo } from "./ArkEventTargetInfoMaterialized"
import { ScrollOnScrollCallback, OnScrollEdgeCallback, OnScrollFrameBeginCallback, OnScrollFrameBeginHandlerResult } from "./ArkScrollInterfaces"
import { ScrollState, OnScrollVisibleContentChangeCallback, VisibleListContentInfo, ListItemGroupArea } from "./ArkListInterfaces"
import { DatePickerResult } from "./ArkDatePickerInterfaces"
import { TerminationInfo } from "./ArkEmbeddedComponentInterfaces"
import { Want, ErrorCallback, BusinessError, WebHeader } from "./ArkArkuiExternalInterfaces"
import { OnFoldStatusChangeCallback, OnFoldStatusChangeInfo, OnHoverStatusChangeCallback, HoverEventParam, WindowStatusType } from "./ArkFolderStackInterfaces"
import { FormCallbackInfo } from "./ArkFormComponentInterfaces"
import { ComputedBarAttribute } from "./ArkGridInterfaces"
import { ImageErrorCallback, ImageError } from "./ArkImageInterfaces"
import { ImageCompleteCallback, ImageLoadResult } from "./ArkImageSpanInterfaces"
import { LocationButtonOnClickResult } from "./ArkLocationButtonInterfaces"
import { NavDestinationContext } from "./ArkNavDestinationContextMaterialized"
import { NavPathInfo } from "./ArkNavPathInfoMaterialized"
import { NavPathStack } from "./ArkNavPathStackMaterialized"
import { RouteMapConfig } from "./ArkNavDestinationInterfaces"
import { NavigationOptions, NavigationInterception, PopInfo, LaunchMode, InterceptionShowCallback, InterceptionModeCallback } from "./ArkNavigationInterfaces"
import { PanelMode } from "./ArkPanelInterfaces"
import { PasteButtonOnClickResult } from "./ArkPasteButtonInterfaces"
import { PluginErrorCallback, PluginErrorData } from "./ArkPluginComponentInterfaces"
import { RefreshStatus } from "./ArkRefreshInterfaces"
import { RichEditorSelection, RichEditorTextSpanResult, RichEditorImageSpanResult, RichEditorSpanPosition, RichEditorTextStyleResult, RichEditorSymbolSpanStyle, RichEditorParagraphStyle, RichEditorImageSpanStyleResult, LeadingMarginPlaceholder, RichEditorLayoutStyle, RichEditorRange, RichEditorInsertValue, RichEditorDeleteValue, RichEditorDeleteDirection, PasteEventCallback, PasteEvent, SubmitCallback, RichEditorChangeValue, CutEvent, CopyEvent } from "./ArkRichEditorInterfaces"
import { DecorationStyleResult, TextRange, OnDidChangeCallback, EditableTextOnChangeCallback, PreviewText, InsertValue, DeleteValue, TextDeleteDirection } from "./ArkTextCommonInterfaces"
import { SymbolEffectStrategy, SymbolRenderingStrategy } from "./ArkSymbolglyphInterfaces"
import { EnterKeyType, OnTextSelectionChangeCallback, OnContentScrollCallback, OnPasteCallback, OnSubmitCallback } from "./ArkTextInputInterfaces"
import { SubmitEvent } from "./ArkSubmitEventMaterialized"
import { SaveButtonOnClickResult } from "./ArkSaveButtonInterfaces"
import { SearchSubmitCallback } from "./ArkSearchInterfaces"
import { SliderChangeMode } from "./ArkSliderInterfaces"
import { OnSwiperAnimationStartCallback, SwiperAnimationEvent, OnSwiperAnimationEndCallback, OnSwiperGestureSwipeCallback, ContentDidScrollCallback } from "./ArkSwiperInterfaces"
import { OnTabsAnimationStartCallback, TabsAnimationEvent, OnTabsAnimationEndCallback, OnTabsGestureSwipeCallback, TabsCustomContentTransitionCallback, TabContentAnimatedTransition, OnTabsContentWillChangeCallback } from "./ArkTabsInterfaces"
import { TabContentTransitionProxy } from "./ArkTabContentTransitionProxyMaterialized"
import { TextAreaSubmitCallback } from "./ArkTextAreaInterfaces"
import { TimePickerResult } from "./ArkTimePickerInterfaces"
import { FullscreenInfo, PreparedInfo, PlaybackInfo } from "./ArkVideoInterfaces"
import { OnPageEndEvent, OnPageBeginEvent, OnProgressChangeEvent, OnTitleReceiveEvent, OnGeolocationShowEvent, OnAlertEvent, OnBeforeUnloadEvent, OnConfirmEvent, OnPromptEvent, OnConsoleEvent, MessageLevel, OnErrorReceiveEvent, Header, OnHttpErrorReceiveEvent, OnDownloadStartEvent, OnRefreshAccessedHistoryEvent, OnRenderExitedEvent, RenderExitReason, OnShowFileSelectorEvent, FileSelectorMode, OnResourceLoadEvent, OnFullScreenEnterCallback, FullScreenEnterEvent, OnScaleChangeEvent, OnHttpAuthRequestEvent, OnInterceptRequestEvent, OnPermissionRequestEvent, OnScreenCaptureRequestEvent, ScreenCaptureConfig, WebCaptureMode, OnContextMenuShowEvent, ContextMenuMediaType, ContextMenuSourceType, ContextMenuInputFieldType, OnContextMenuHideCallback, OnSearchResultReceiveEvent, OnScrollEvent, OnSslErrorEventReceiveEvent, SslError, OnSslErrorEventCallback, SslErrorEvent, OnClientAuthenticationEvent, OnWindowNewEvent, OnTouchIconUrlReceivedEvent, OnFaviconReceivedEvent, OnPageVisibleEvent, OnDataResubmittedEvent, OnAudioStateChangedEvent, OnFirstContentfulPaintEvent, OnFirstMeaningfulPaintCallback, FirstMeaningfulPaint, OnLargestContentfulPaintCallback, LargestContentfulPaint, OnLoadInterceptEvent, OnOverScrollEvent, OnSafeBrowsingCheckResultCallback, ThreatType, OnNavigationEntryCommittedCallback, LoadCommittedDetails, WebNavigationType, OnIntelligentTrackingPreventionCallback, IntelligentTrackingPreventionDetails, NativeEmbedDataInfo, NativeEmbedStatus, NativeEmbedInfo, OnNativeEmbedVisibilityChangeCallback, NativeEmbedVisibilityInfo, NativeEmbedTouchInfo, OnOverrideUrlLoadingCallback, OnRenderProcessNotRespondingCallback, RenderProcessNotRespondingData, RenderProcessNotRespondingReason, OnRenderProcessRespondingCallback, OnViewportFitChangedCallback, ViewportFit, WebKeyboardCallback, WebKeyboardCallbackInfo, WebKeyboardOptions, OnAdsBlockedCallback, AdsBlockedDetails } from "./ArkWebInterfaces"
import { JsGeolocation } from "./ArkJsGeolocationMaterialized"
import { JsResult } from "./ArkJsResultMaterialized"
import { ConsoleMessage } from "./ArkConsoleMessageMaterialized"
import { WebResourceRequest } from "./ArkWebResourceRequestMaterialized"
import { WebResourceError } from "./ArkWebResourceErrorMaterialized"
import { WebResourceResponse } from "./ArkWebResourceResponseMaterialized"
import { FileSelectorResult } from "./ArkFileSelectorResultMaterialized"
import { FileSelectorParam } from "./ArkFileSelectorParamMaterialized"
import { FullScreenExitHandler } from "./ArkFullScreenExitHandlerMaterialized"
import { HttpAuthHandler } from "./ArkHttpAuthHandlerMaterialized"
import { PermissionRequest } from "./ArkPermissionRequestMaterialized"
import { ScreenCaptureHandler } from "./ArkScreenCaptureHandlerMaterialized"
import { WebContextMenuParam } from "./ArkWebContextMenuParamMaterialized"
import { WebContextMenuResult } from "./ArkWebContextMenuResultMaterialized"
import { SslErrorHandler } from "./ArkSslErrorHandlerMaterialized"
import { ClientAuthenticationHandler } from "./ArkClientAuthenticationHandlerMaterialized"
import { ControllerHandler } from "./ArkControllerHandlerMaterialized"
import { WebviewController } from "./ArkWebviewControllerMaterialized"
import { DataResubmissionHandler } from "./ArkDataResubmissionHandlerMaterialized"
import { EventResult } from "./ArkEventResultMaterialized"
import { WebKeyboardController } from "./ArkWebKeyboardControllerMaterialized"
import { OnNativeLoadCallback } from "./ArkXcomponentInterfaces"
import { UIExtensionProxy } from "./ArkUIExtensionProxyMaterialized"
export enum PeerEventKind {
    AbilityComponent_onConnect = 0,
    AbilityComponent_onDisconnect = 1,
    AlphabetIndexer_onSelected = 2,
    AlphabetIndexer_onSelect = 3,
    AlphabetIndexer_onRequestPopupData = 4,
    AlphabetIndexer_onPopupSelect = 5,
    AlphabetIndexer__onChangeEvent_selected = 6,
    Animator_onStart = 7,
    Animator_onPause = 8,
    Animator_onRepeat = 9,
    Animator_onCancel = 10,
    Animator_onFinish = 11,
    Animator_onFrame = 12,
    Calendar_onSelectChange = 13,
    Calendar_onRequestData = 14,
    CalendarPicker_onChange = 15,
    Canvas_onReady = 16,
    Checkbox_onChange = 17,
    Checkbox__onChangeEvent_select = 18,
    CheckboxGroup_onChange = 19,
    CheckboxGroup__onChangeEvent_selectAll = 20,
    CommonMethod_onChildTouchTest = 21,
    CommonMethod_onClick0 = 22,
    CommonMethod_onClick1 = 23,
    CommonMethod_onHover = 24,
    CommonMethod_onAccessibilityHover = 25,
    CommonMethod_onMouse = 26,
    CommonMethod_onTouch = 27,
    CommonMethod_onKeyEvent = 28,
    CommonMethod_onKeyPreIme = 29,
    CommonMethod_onFocus = 30,
    CommonMethod_onBlur = 31,
    CommonMethod_onAppear = 32,
    CommonMethod_onDisAppear = 33,
    CommonMethod_onAttach = 34,
    CommonMethod_onDetach = 35,
    CommonMethod_onAreaChange = 36,
    CommonMethod_onDragStart = 37,
    CommonMethod_onDragEnter = 38,
    CommonMethod_onDragMove = 39,
    CommonMethod_onDragLeave = 40,
    CommonMethod_onDrop = 41,
    CommonMethod_onDragEnd = 42,
    CommonMethod_onPreDrag = 43,
    CommonMethod_accessibilityVirtualNode = 44,
    CommonMethod_onGestureJudgeBegin = 45,
    CommonMethod_onGestureRecognizerJudgeBegin0 = 46,
    CommonMethod_onGestureRecognizerJudgeBegin1 = 47,
    CommonMethod_shouldBuiltInRecognizerParallelWith = 48,
    CommonMethod_onTouchIntercept = 49,
    CommonMethod_onSizeChange = 50,
    CommonMethod_background = 51,
    CommonMethod_bindContextMenu0 = 52,
    CommonMethod_bindContextMenu1 = 53,
    CommonMethod_bindContentCover0 = 54,
    CommonMethod_bindContentCover1 = 55,
    CommonMethod_bindSheet = 56,
    CommonMethod_onVisibleAreaChange = 57,
    ScrollableCommonMethod_onScroll = 58,
    ScrollableCommonMethod_onDidScroll = 59,
    ScrollableCommonMethod_onReachStart = 60,
    ScrollableCommonMethod_onReachEnd = 61,
    ScrollableCommonMethod_onScrollStart = 62,
    ScrollableCommonMethod_onScrollStop = 63,
    Counter_onInc = 64,
    Counter_onDec = 65,
    DatePicker_onChange = 66,
    DatePicker_onDateChange = 67,
    DatePicker__onChangeEvent_selected = 68,
    EmbeddedComponent_onTerminated = 69,
    EmbeddedComponent_onError = 70,
    FolderStack_onFolderStateChange = 71,
    FolderStack_onHoverStatusChange = 72,
    FormComponent_onAcquired = 73,
    FormComponent_onError = 74,
    FormComponent_onRouter = 75,
    FormComponent_onUninstall = 76,
    FormComponent_onLoad = 77,
    Gauge_description = 78,
    Grid_onScrollBarUpdate = 79,
    Grid_onScrollIndex = 80,
    Grid_onItemDragStart = 81,
    Grid_onItemDragEnter = 82,
    Grid_onItemDragMove = 83,
    Grid_onItemDragLeave = 84,
    Grid_onItemDrop = 85,
    Grid_onScroll = 86,
    Grid_onReachStart = 87,
    Grid_onReachEnd = 88,
    Grid_onScrollStart = 89,
    Grid_onScrollStop = 90,
    Grid_onScrollFrameBegin = 91,
    GridItem_onSelect = 92,
    GridItem__onChangeEvent_selected = 93,
    GridRow_onBreakpointChange = 94,
    Image_onComplete = 95,
    Image_onError = 96,
    Image_onFinish = 97,
    ImageAnimator_onStart = 98,
    ImageAnimator_onPause = 99,
    ImageAnimator_onRepeat = 100,
    ImageAnimator_onCancel = 101,
    ImageAnimator_onFinish = 102,
    ImageSpan_onComplete = 103,
    ImageSpan_onError = 104,
    List_onScroll = 105,
    List_onScrollIndex = 106,
    List_onScrollVisibleContentChange = 107,
    List_onReachStart = 108,
    List_onReachEnd = 109,
    List_onScrollStart = 110,
    List_onScrollStop = 111,
    List_onItemDelete = 112,
    List_onItemMove = 113,
    List_onItemDragStart = 114,
    List_onItemDragEnter = 115,
    List_onItemDragMove = 116,
    List_onItemDragLeave = 117,
    List_onItemDrop = 118,
    List_onScrollFrameBegin = 119,
    ListItem_onSelect = 120,
    ListItem__onChangeEvent_selected = 121,
    LocationButton_onClick = 122,
    Marquee_onStart = 123,
    Marquee_onBounce = 124,
    Marquee_onFinish = 125,
    MenuItem_onChange = 126,
    MenuItem__onChangeEvent_selected = 127,
    NavDestination_onShown = 128,
    NavDestination_onHidden = 129,
    NavDestination_onBackPressed = 130,
    NavDestination_onReady = 131,
    NavDestination_onWillAppear = 132,
    NavDestination_onWillDisappear = 133,
    NavDestination_onWillShow = 134,
    NavDestination_onWillHide = 135,
    NavRouter_onStateChange = 136,
    Panel_onChange = 137,
    Panel_onHeightChange = 138,
    Panel__onChangeEvent_mode = 139,
    PasteButton_onClick = 140,
    PatternLock_onPatternComplete = 141,
    PatternLock_onDotConnect = 142,
    PluginComponent_onComplete = 143,
    PluginComponent_onError = 144,
    Radio_onChange = 145,
    Radio__onChangeEvent_checked = 146,
    Rating_onChange = 147,
    Rating__onChangeEvent_rating = 148,
    Refresh_onStateChange = 149,
    Refresh_onRefreshing = 150,
    Refresh_onOffsetChange = 151,
    Refresh__onChangeEvent_refreshing = 152,
    RichEditor_onReady = 153,
    RichEditor_onSelect = 154,
    RichEditor_onSelectionChange = 155,
    RichEditor_aboutToIMEInput = 156,
    RichEditor_onIMEInputComplete = 157,
    RichEditor_onDidIMEInput = 158,
    RichEditor_aboutToDelete = 159,
    RichEditor_onDeleteComplete = 160,
    RichEditor_onPaste = 161,
    RichEditor_onEditingChange = 162,
    RichEditor_onSubmit = 163,
    RichEditor_onWillChange = 164,
    RichEditor_onDidChange = 165,
    RichEditor_onCut = 166,
    RichEditor_onCopy = 167,
    RichEditor_bindSelectionMenu = 168,
    RichEditor_customKeyboard = 169,
    RichText_onStart = 170,
    RichText_onComplete = 171,
    SaveButton_onClick = 172,
    Scroll_onScroll = 173,
    Scroll_onDidScroll = 174,
    Scroll_onScrollEdge = 175,
    Scroll_onScrollStart = 176,
    Scroll_onScrollEnd = 177,
    Scroll_onScrollStop = 178,
    Scroll_onScrollFrameBegin = 179,
    Search_onEditChange = 180,
    Search_onSubmit0 = 181,
    Search_onSubmit1 = 182,
    Search_onChange = 183,
    Search_onTextSelectionChange = 184,
    Search_onContentScroll = 185,
    Search_onCopy = 186,
    Search_onCut = 187,
    Search_onPaste = 188,
    Search_onWillInsert = 189,
    Search_onDidInsert = 190,
    Search_onWillDelete = 191,
    Search_onDidDelete = 192,
    Search_customKeyboard = 193,
    Search__onChangeEvent_value = 194,
    Select_onSelect = 195,
    Select__onChangeEvent_selected = 196,
    Select__onChangeEvent_value = 197,
    Slider_onChange = 198,
    Slider__onChangeEvent_value = 199,
    Stepper_onFinish = 200,
    Stepper_onSkip = 201,
    Stepper_onChange = 202,
    Stepper_onNext = 203,
    Stepper_onPrevious = 204,
    Stepper__onChangeEvent_index = 205,
    Swiper_onChange = 206,
    Swiper_onAnimationStart = 207,
    Swiper_onAnimationEnd = 208,
    Swiper_onGestureSwipe = 209,
    Swiper_onContentDidScroll = 210,
    Swiper__onChangeEvent_index = 211,
    IndicatorComponent_onChange = 212,
    Tabs_onChange = 213,
    Tabs_onTabBarClick = 214,
    Tabs_onAnimationStart = 215,
    Tabs_onAnimationEnd = 216,
    Tabs_onGestureSwipe = 217,
    Tabs_customContentTransition = 218,
    Tabs_onContentWillChange = 219,
    Tabs__onChangeEvent_index = 220,
    TabContent_onWillShow = 221,
    TabContent_onWillHide = 222,
    Text_onCopy = 223,
    Text_onTextSelectionChange = 224,
    Text_bindSelectionMenu = 225,
    TextArea_onSubmit0 = 226,
    TextArea_onSubmit1 = 227,
    TextArea_onChange = 228,
    TextArea_onTextSelectionChange = 229,
    TextArea_onContentScroll = 230,
    TextArea_onEditChange = 231,
    TextArea_onCopy = 232,
    TextArea_onCut = 233,
    TextArea_onPaste = 234,
    TextArea_onWillInsert = 235,
    TextArea_onDidInsert = 236,
    TextArea_onWillDelete = 237,
    TextArea_onDidDelete = 238,
    TextArea_customKeyboard = 239,
    TextArea__onChangeEvent_text = 240,
    TextClock_onDateChange = 241,
    TextInput_onEditChanged = 242,
    TextInput_onEditChange = 243,
    TextInput_onSubmit = 244,
    TextInput_onChange = 245,
    TextInput_onTextSelectionChange = 246,
    TextInput_onContentScroll = 247,
    TextInput_onCopy = 248,
    TextInput_onCut = 249,
    TextInput_onPaste = 250,
    TextInput_showUnit = 251,
    TextInput_onSecurityStateChange = 252,
    TextInput_onWillInsert = 253,
    TextInput_onDidInsert = 254,
    TextInput_onWillDelete = 255,
    TextInput_onDidDelete = 256,
    TextInput_customKeyboard = 257,
    TextInput__onChangeEvent_text = 258,
    TextPicker_onAccept = 259,
    TextPicker_onCancel = 260,
    TextPicker_onChange = 261,
    TextPicker__onChangeEvent_selected = 262,
    TextPicker__onChangeEvent_value = 263,
    TextTimer_onTimer = 264,
    TimePicker_onChange = 265,
    TimePicker__onChangeEvent_selected = 266,
    Toggle_onChange = 267,
    Toggle__onChangeEvent_isOn = 268,
    Video_onStart = 269,
    Video_onPause = 270,
    Video_onFinish = 271,
    Video_onFullscreenChange = 272,
    Video_onPrepared = 273,
    Video_onSeeking = 274,
    Video_onSeeked = 275,
    Video_onUpdate = 276,
    Video_onError = 277,
    Video_onStop = 278,
    Web_onPageEnd = 279,
    Web_onPageBegin = 280,
    Web_onProgressChange = 281,
    Web_onTitleReceive = 282,
    Web_onGeolocationHide = 283,
    Web_onGeolocationShow = 284,
    Web_onRequestSelected = 285,
    Web_onAlert = 286,
    Web_onBeforeUnload = 287,
    Web_onConfirm = 288,
    Web_onPrompt = 289,
    Web_onConsole = 290,
    Web_onErrorReceive = 291,
    Web_onHttpErrorReceive = 292,
    Web_onDownloadStart = 293,
    Web_onRefreshAccessedHistory = 294,
    Web_onUrlLoadIntercept = 295,
    Web_onSslErrorReceive = 296,
    Web_onRenderExited0 = 297,
    Web_onRenderExited1 = 298,
    Web_onShowFileSelector = 299,
    Web_onFileSelectorShow = 300,
    Web_onResourceLoad = 301,
    Web_onFullScreenExit = 302,
    Web_onFullScreenEnter = 303,
    Web_onScaleChange = 304,
    Web_onHttpAuthRequest = 305,
    Web_onInterceptRequest = 306,
    Web_onPermissionRequest = 307,
    Web_onScreenCaptureRequest = 308,
    Web_onContextMenuShow = 309,
    Web_onContextMenuHide = 310,
    Web_onSearchResultReceive = 311,
    Web_onScroll = 312,
    Web_onSslErrorEventReceive = 313,
    Web_onSslErrorEvent = 314,
    Web_onClientAuthenticationRequest = 315,
    Web_onWindowNew = 316,
    Web_onWindowExit = 317,
    Web_onInterceptKeyEvent = 318,
    Web_onTouchIconUrlReceived = 319,
    Web_onFaviconReceived = 320,
    Web_onPageVisible = 321,
    Web_onDataResubmitted = 322,
    Web_onAudioStateChanged = 323,
    Web_onFirstContentfulPaint = 324,
    Web_onFirstMeaningfulPaint = 325,
    Web_onLargestContentfulPaint = 326,
    Web_onLoadIntercept = 327,
    Web_onControllerAttached = 328,
    Web_onOverScroll = 329,
    Web_onSafeBrowsingCheckResult = 330,
    Web_onNavigationEntryCommitted = 331,
    Web_onIntelligentTrackingPreventionResult = 332,
    Web_onNativeEmbedLifecycleChange = 333,
    Web_onNativeEmbedVisibilityChange = 334,
    Web_onNativeEmbedGestureEvent = 335,
    Web_onOverrideUrlLoading = 336,
    Web_onRenderProcessNotResponding = 337,
    Web_onRenderProcessResponding = 338,
    Web_onViewportFitChanged = 339,
    Web_onInterceptKeyboardAttach = 340,
    Web_onAdsBlocked = 341,
    Web_bindSelectionMenu = 342,
    XComponent_onLoad = 343,
    XComponent_onDestroy = 344,
    SideBarContainer_onChange = 345,
    SideBarContainer__onChangeEvent_showSideBar = 346,
    WaterFlow_onReachStart = 347,
    WaterFlow_onReachEnd = 348,
    WaterFlow_onScrollFrameBegin = 349,
    WaterFlow_onScrollIndex = 350,
    UIExtensionComponent_onRemoteReady = 351,
    UIExtensionComponent_onResult = 352,
    UIExtensionComponent_onRelease = 353,
    UIExtensionComponent_onError = 354,
    UIExtensionComponent_onTerminated = 355,
}

interface PeerEvent {
    readonly kind: PeerEventKind
    readonly nodeId: number
}

export interface AbilityComponent_onConnect_event extends PeerEvent {
    readonly kind: PeerEventKind.AbilityComponent_onConnect
}
export interface AbilityComponent_onDisconnect_event extends PeerEvent {
    readonly kind: PeerEventKind.AbilityComponent_onDisconnect
}
export interface AlphabetIndexer_onSelected_event extends PeerEvent {
    readonly kind: PeerEventKind.AlphabetIndexer_onSelected
    readonly index: number
}
export interface AlphabetIndexer_onSelect_event extends PeerEvent {
    readonly kind: PeerEventKind.AlphabetIndexer_onSelect
    readonly index: number
}
export interface AlphabetIndexer_onRequestPopupData_event extends PeerEvent {
    readonly kind: PeerEventKind.AlphabetIndexer_onRequestPopupData
    readonly index: number
}
export interface AlphabetIndexer_onPopupSelect_event extends PeerEvent {
    readonly kind: PeerEventKind.AlphabetIndexer_onPopupSelect
    readonly index: number
}
export interface AlphabetIndexer__onChangeEvent_selected_event extends PeerEvent {
    readonly kind: PeerEventKind.AlphabetIndexer__onChangeEvent_selected
    readonly index: number
}
export interface Animator_onStart_event extends PeerEvent {
    readonly kind: PeerEventKind.Animator_onStart
}
export interface Animator_onPause_event extends PeerEvent {
    readonly kind: PeerEventKind.Animator_onPause
}
export interface Animator_onRepeat_event extends PeerEvent {
    readonly kind: PeerEventKind.Animator_onRepeat
}
export interface Animator_onCancel_event extends PeerEvent {
    readonly kind: PeerEventKind.Animator_onCancel
}
export interface Animator_onFinish_event extends PeerEvent {
    readonly kind: PeerEventKind.Animator_onFinish
}
export interface Animator_onFrame_event extends PeerEvent {
    readonly kind: PeerEventKind.Animator_onFrame
    readonly index: number
}
export interface Calendar_onSelectChange_event extends PeerEvent {
    readonly kind: PeerEventKind.Calendar_onSelectChange
    readonly event: CalendarSelectedDate
}
export interface Calendar_onRequestData_event extends PeerEvent {
    readonly kind: PeerEventKind.Calendar_onRequestData
    readonly event: CalendarRequestedData
}
export interface CalendarPicker_onChange_event extends PeerEvent {
    readonly kind: PeerEventKind.CalendarPicker_onChange
    readonly parameter: Date
}
export interface Canvas_onReady_event extends PeerEvent {
    readonly kind: PeerEventKind.Canvas_onReady
}
export interface Checkbox_onChange_event extends PeerEvent {
    readonly kind: PeerEventKind.Checkbox_onChange
    readonly value: boolean
}
export interface Checkbox__onChangeEvent_select_event extends PeerEvent {
    readonly kind: PeerEventKind.Checkbox__onChangeEvent_select
    readonly parameter: boolean
}
export interface CheckboxGroup_onChange_event extends PeerEvent {
    readonly kind: PeerEventKind.CheckboxGroup_onChange
    readonly value: CheckboxGroupResult
}
export interface CheckboxGroup__onChangeEvent_selectAll_event extends PeerEvent {
    readonly kind: PeerEventKind.CheckboxGroup__onChangeEvent_selectAll
    readonly parameter: boolean
}
export interface CommonMethod_onChildTouchTest_event extends PeerEvent {
    readonly kind: PeerEventKind.CommonMethod_onChildTouchTest
    readonly value: Array<TouchTestInfo>
}
export interface CommonMethod_onClick0_event extends PeerEvent {
    readonly kind: PeerEventKind.CommonMethod_onClick0
    readonly event: ClickEvent
}
export interface CommonMethod_onClick1_event extends PeerEvent {
    readonly kind: PeerEventKind.CommonMethod_onClick1
    readonly event: ClickEvent
}
export interface CommonMethod_onHover_event extends PeerEvent {
    readonly kind: PeerEventKind.CommonMethod_onHover
    readonly isHover: boolean
    readonly event: HoverEvent
}
export interface CommonMethod_onAccessibilityHover_event extends PeerEvent {
    readonly kind: PeerEventKind.CommonMethod_onAccessibilityHover
    readonly isHover: boolean
    readonly event: AccessibilityHoverEvent
}
export interface CommonMethod_onMouse_event extends PeerEvent {
    readonly kind: PeerEventKind.CommonMethod_onMouse
    readonly event: MouseEvent
}
export interface CommonMethod_onTouch_event extends PeerEvent {
    readonly kind: PeerEventKind.CommonMethod_onTouch
    readonly event: TouchEvent
}
export interface CommonMethod_onKeyEvent_event extends PeerEvent {
    readonly kind: PeerEventKind.CommonMethod_onKeyEvent
    readonly event: KeyEvent
}
export interface CommonMethod_onKeyPreIme_event extends PeerEvent {
    readonly kind: PeerEventKind.CommonMethod_onKeyPreIme
    readonly parameter: KeyEvent
}
export interface CommonMethod_onFocus_event extends PeerEvent {
    readonly kind: PeerEventKind.CommonMethod_onFocus
}
export interface CommonMethod_onBlur_event extends PeerEvent {
    readonly kind: PeerEventKind.CommonMethod_onBlur
}
export interface CommonMethod_onAppear_event extends PeerEvent {
    readonly kind: PeerEventKind.CommonMethod_onAppear
}
export interface CommonMethod_onDisAppear_event extends PeerEvent {
    readonly kind: PeerEventKind.CommonMethod_onDisAppear
}
export interface CommonMethod_onAttach_event extends PeerEvent {
    readonly kind: PeerEventKind.CommonMethod_onAttach
}
export interface CommonMethod_onDetach_event extends PeerEvent {
    readonly kind: PeerEventKind.CommonMethod_onDetach
}
export interface CommonMethod_onAreaChange_event extends PeerEvent {
    readonly kind: PeerEventKind.CommonMethod_onAreaChange
    readonly oldValue: Area
    readonly newValue: Area
}
export interface CommonMethod_onDragStart_event extends PeerEvent {
    readonly kind: PeerEventKind.CommonMethod_onDragStart
    readonly event: DragEvent
    readonly extraParams?: string | undefined
}
export interface CommonMethod_onDragEnter_event extends PeerEvent {
    readonly kind: PeerEventKind.CommonMethod_onDragEnter
    readonly event: DragEvent
    readonly extraParams?: string | undefined
}
export interface CommonMethod_onDragMove_event extends PeerEvent {
    readonly kind: PeerEventKind.CommonMethod_onDragMove
    readonly event: DragEvent
    readonly extraParams?: string | undefined
}
export interface CommonMethod_onDragLeave_event extends PeerEvent {
    readonly kind: PeerEventKind.CommonMethod_onDragLeave
    readonly event: DragEvent
    readonly extraParams?: string | undefined
}
export interface CommonMethod_onDrop_event extends PeerEvent {
    readonly kind: PeerEventKind.CommonMethod_onDrop
    readonly event: DragEvent
    readonly extraParams?: string | undefined
}
export interface CommonMethod_onDragEnd_event extends PeerEvent {
    readonly kind: PeerEventKind.CommonMethod_onDragEnd
    readonly event: DragEvent
    readonly extraParams?: string | undefined
}
export interface CommonMethod_onPreDrag_event extends PeerEvent {
    readonly kind: PeerEventKind.CommonMethod_onPreDrag
    readonly parameter: PreDragStatus
}
export interface CommonMethod_accessibilityVirtualNode_event extends PeerEvent {
    readonly kind: PeerEventKind.CommonMethod_accessibilityVirtualNode
}
export interface CommonMethod_onGestureJudgeBegin_event extends PeerEvent {
    readonly kind: PeerEventKind.CommonMethod_onGestureJudgeBegin
    readonly gestureInfo: GestureInfo
    readonly event: BaseGestureEvent
}
export interface CommonMethod_onGestureRecognizerJudgeBegin0_event extends PeerEvent {
    readonly kind: PeerEventKind.CommonMethod_onGestureRecognizerJudgeBegin0
    readonly event: BaseGestureEvent
    readonly current: GestureRecognizer
    readonly recognizers: Array<GestureRecognizer>
}
export interface CommonMethod_onGestureRecognizerJudgeBegin1_event extends PeerEvent {
    readonly kind: PeerEventKind.CommonMethod_onGestureRecognizerJudgeBegin1
    readonly event: BaseGestureEvent
    readonly current: GestureRecognizer
    readonly recognizers: Array<GestureRecognizer>
}
export interface CommonMethod_shouldBuiltInRecognizerParallelWith_event extends PeerEvent {
    readonly kind: PeerEventKind.CommonMethod_shouldBuiltInRecognizerParallelWith
    readonly current: GestureRecognizer
    readonly others: Array<GestureRecognizer>
}
export interface CommonMethod_onTouchIntercept_event extends PeerEvent {
    readonly kind: PeerEventKind.CommonMethod_onTouchIntercept
    readonly parameter: TouchEvent
}
export interface CommonMethod_onSizeChange_event extends PeerEvent {
    readonly kind: PeerEventKind.CommonMethod_onSizeChange
    readonly oldValue: SizeOptions
    readonly newValue: SizeOptions
}
export interface CommonMethod_background_event extends PeerEvent {
    readonly kind: PeerEventKind.CommonMethod_background
}
export interface CommonMethod_bindContextMenu0_event extends PeerEvent {
    readonly kind: PeerEventKind.CommonMethod_bindContextMenu0
}
export interface CommonMethod_bindContextMenu1_event extends PeerEvent {
    readonly kind: PeerEventKind.CommonMethod_bindContextMenu1
}
export interface CommonMethod_bindContentCover0_event extends PeerEvent {
    readonly kind: PeerEventKind.CommonMethod_bindContentCover0
}
export interface CommonMethod_bindContentCover1_event extends PeerEvent {
    readonly kind: PeerEventKind.CommonMethod_bindContentCover1
}
export interface CommonMethod_bindSheet_event extends PeerEvent {
    readonly kind: PeerEventKind.CommonMethod_bindSheet
}
export interface CommonMethod_onVisibleAreaChange_event extends PeerEvent {
    readonly kind: PeerEventKind.CommonMethod_onVisibleAreaChange
    readonly isExpanding: boolean
    readonly currentRatio: number
}
export interface ScrollableCommonMethod_onScroll_event extends PeerEvent {
    readonly kind: PeerEventKind.ScrollableCommonMethod_onScroll
    readonly first: number
    readonly last: number
}
export interface ScrollableCommonMethod_onDidScroll_event extends PeerEvent {
    readonly kind: PeerEventKind.ScrollableCommonMethod_onDidScroll
    readonly xOffset: number
    readonly yOffset: number
    readonly scrollState: ScrollState
}
export interface ScrollableCommonMethod_onReachStart_event extends PeerEvent {
    readonly kind: PeerEventKind.ScrollableCommonMethod_onReachStart
}
export interface ScrollableCommonMethod_onReachEnd_event extends PeerEvent {
    readonly kind: PeerEventKind.ScrollableCommonMethod_onReachEnd
}
export interface ScrollableCommonMethod_onScrollStart_event extends PeerEvent {
    readonly kind: PeerEventKind.ScrollableCommonMethod_onScrollStart
}
export interface ScrollableCommonMethod_onScrollStop_event extends PeerEvent {
    readonly kind: PeerEventKind.ScrollableCommonMethod_onScrollStop
}
export interface Counter_onInc_event extends PeerEvent {
    readonly kind: PeerEventKind.Counter_onInc
}
export interface Counter_onDec_event extends PeerEvent {
    readonly kind: PeerEventKind.Counter_onDec
}
export interface DatePicker_onChange_event extends PeerEvent {
    readonly kind: PeerEventKind.DatePicker_onChange
    readonly value: DatePickerResult
}
export interface DatePicker_onDateChange_event extends PeerEvent {
    readonly kind: PeerEventKind.DatePicker_onDateChange
    readonly parameter: Date
}
export interface DatePicker__onChangeEvent_selected_event extends PeerEvent {
    readonly kind: PeerEventKind.DatePicker__onChangeEvent_selected
    readonly parameter: Date
}
export interface EmbeddedComponent_onTerminated_event extends PeerEvent {
    readonly kind: PeerEventKind.EmbeddedComponent_onTerminated
    readonly parameter: TerminationInfo
}
export interface EmbeddedComponent_onError_event extends PeerEvent {
    readonly kind: PeerEventKind.EmbeddedComponent_onError
    readonly err: BusinessError
}
export interface FolderStack_onFolderStateChange_event extends PeerEvent {
    readonly kind: PeerEventKind.FolderStack_onFolderStateChange
    readonly event: OnFoldStatusChangeInfo
}
export interface FolderStack_onHoverStatusChange_event extends PeerEvent {
    readonly kind: PeerEventKind.FolderStack_onHoverStatusChange
    readonly param: HoverEventParam
}
export interface FormComponent_onAcquired_event extends PeerEvent {
    readonly kind: PeerEventKind.FormComponent_onAcquired
    readonly parameter: FormCallbackInfo
}
export interface FormComponent_onError_event extends PeerEvent {
    readonly kind: PeerEventKind.FormComponent_onError
    readonly info: { errcode: number, msg: string }
}
export interface FormComponent_onRouter_event extends PeerEvent {
    readonly kind: PeerEventKind.FormComponent_onRouter
    readonly info: any
}
export interface FormComponent_onUninstall_event extends PeerEvent {
    readonly kind: PeerEventKind.FormComponent_onUninstall
    readonly parameter: FormCallbackInfo
}
export interface FormComponent_onLoad_event extends PeerEvent {
    readonly kind: PeerEventKind.FormComponent_onLoad
}
export interface Gauge_description_event extends PeerEvent {
    readonly kind: PeerEventKind.Gauge_description
}
export interface Grid_onScrollBarUpdate_event extends PeerEvent {
    readonly kind: PeerEventKind.Grid_onScrollBarUpdate
    readonly index: number
    readonly offset: number
}
export interface Grid_onScrollIndex_event extends PeerEvent {
    readonly kind: PeerEventKind.Grid_onScrollIndex
    readonly first: number
    readonly last: number
}
export interface Grid_onItemDragStart_event extends PeerEvent {
    readonly kind: PeerEventKind.Grid_onItemDragStart
    readonly event: ItemDragInfo
    readonly itemIndex: number
}
export interface Grid_onItemDragEnter_event extends PeerEvent {
    readonly kind: PeerEventKind.Grid_onItemDragEnter
    readonly event: ItemDragInfo
}
export interface Grid_onItemDragMove_event extends PeerEvent {
    readonly kind: PeerEventKind.Grid_onItemDragMove
    readonly event: ItemDragInfo
    readonly itemIndex: number
    readonly insertIndex: number
}
export interface Grid_onItemDragLeave_event extends PeerEvent {
    readonly kind: PeerEventKind.Grid_onItemDragLeave
    readonly event: ItemDragInfo
    readonly itemIndex: number
}
export interface Grid_onItemDrop_event extends PeerEvent {
    readonly kind: PeerEventKind.Grid_onItemDrop
    readonly event: ItemDragInfo
    readonly itemIndex: number
    readonly insertIndex: number
    readonly isSuccess: boolean
}
export interface Grid_onScroll_event extends PeerEvent {
    readonly kind: PeerEventKind.Grid_onScroll
    readonly first: number
    readonly last: number
}
export interface Grid_onReachStart_event extends PeerEvent {
    readonly kind: PeerEventKind.Grid_onReachStart
}
export interface Grid_onReachEnd_event extends PeerEvent {
    readonly kind: PeerEventKind.Grid_onReachEnd
}
export interface Grid_onScrollStart_event extends PeerEvent {
    readonly kind: PeerEventKind.Grid_onScrollStart
}
export interface Grid_onScrollStop_event extends PeerEvent {
    readonly kind: PeerEventKind.Grid_onScrollStop
}
export interface Grid_onScrollFrameBegin_event extends PeerEvent {
    readonly kind: PeerEventKind.Grid_onScrollFrameBegin
    readonly offset: number
    readonly state: ScrollState
}
export interface GridItem_onSelect_event extends PeerEvent {
    readonly kind: PeerEventKind.GridItem_onSelect
    readonly parameter: boolean
}
export interface GridItem__onChangeEvent_selected_event extends PeerEvent {
    readonly kind: PeerEventKind.GridItem__onChangeEvent_selected
    readonly parameter: boolean
}
export interface GridRow_onBreakpointChange_event extends PeerEvent {
    readonly kind: PeerEventKind.GridRow_onBreakpointChange
    readonly breakpoints: string
}
export interface Image_onComplete_event extends PeerEvent {
    readonly kind: PeerEventKind.Image_onComplete
    readonly event?: { width: number, height: number, componentWidth: number, componentHeight: number, loadingStatus: number, contentWidth: number, contentHeight: number, contentOffsetX: number, contentOffsetY: number } | undefined
}
export interface Image_onError_event extends PeerEvent {
    readonly kind: PeerEventKind.Image_onError
    readonly error: ImageError
}
export interface Image_onFinish_event extends PeerEvent {
    readonly kind: PeerEventKind.Image_onFinish
}
export interface ImageAnimator_onStart_event extends PeerEvent {
    readonly kind: PeerEventKind.ImageAnimator_onStart
}
export interface ImageAnimator_onPause_event extends PeerEvent {
    readonly kind: PeerEventKind.ImageAnimator_onPause
}
export interface ImageAnimator_onRepeat_event extends PeerEvent {
    readonly kind: PeerEventKind.ImageAnimator_onRepeat
}
export interface ImageAnimator_onCancel_event extends PeerEvent {
    readonly kind: PeerEventKind.ImageAnimator_onCancel
}
export interface ImageAnimator_onFinish_event extends PeerEvent {
    readonly kind: PeerEventKind.ImageAnimator_onFinish
}
export interface ImageSpan_onComplete_event extends PeerEvent {
    readonly kind: PeerEventKind.ImageSpan_onComplete
    readonly result: ImageLoadResult
}
export interface ImageSpan_onError_event extends PeerEvent {
    readonly kind: PeerEventKind.ImageSpan_onError
    readonly error: ImageError
}
export interface List_onScroll_event extends PeerEvent {
    readonly kind: PeerEventKind.List_onScroll
    readonly first: number
    readonly last: number
}
export interface List_onScrollIndex_event extends PeerEvent {
    readonly kind: PeerEventKind.List_onScrollIndex
    readonly start: number
    readonly end: number
    readonly center: number
}
export interface List_onScrollVisibleContentChange_event extends PeerEvent {
    readonly kind: PeerEventKind.List_onScrollVisibleContentChange
    readonly start: VisibleListContentInfo
    readonly end: VisibleListContentInfo
}
export interface List_onReachStart_event extends PeerEvent {
    readonly kind: PeerEventKind.List_onReachStart
}
export interface List_onReachEnd_event extends PeerEvent {
    readonly kind: PeerEventKind.List_onReachEnd
}
export interface List_onScrollStart_event extends PeerEvent {
    readonly kind: PeerEventKind.List_onScrollStart
}
export interface List_onScrollStop_event extends PeerEvent {
    readonly kind: PeerEventKind.List_onScrollStop
}
export interface List_onItemDelete_event extends PeerEvent {
    readonly kind: PeerEventKind.List_onItemDelete
    readonly index: number
}
export interface List_onItemMove_event extends PeerEvent {
    readonly kind: PeerEventKind.List_onItemMove
    readonly from: number
    readonly to: number
}
export interface List_onItemDragStart_event extends PeerEvent {
    readonly kind: PeerEventKind.List_onItemDragStart
    readonly event: ItemDragInfo
    readonly itemIndex: number
}
export interface List_onItemDragEnter_event extends PeerEvent {
    readonly kind: PeerEventKind.List_onItemDragEnter
    readonly event: ItemDragInfo
}
export interface List_onItemDragMove_event extends PeerEvent {
    readonly kind: PeerEventKind.List_onItemDragMove
    readonly event: ItemDragInfo
    readonly itemIndex: number
    readonly insertIndex: number
}
export interface List_onItemDragLeave_event extends PeerEvent {
    readonly kind: PeerEventKind.List_onItemDragLeave
    readonly event: ItemDragInfo
    readonly itemIndex: number
}
export interface List_onItemDrop_event extends PeerEvent {
    readonly kind: PeerEventKind.List_onItemDrop
    readonly event: ItemDragInfo
    readonly itemIndex: number
    readonly insertIndex: number
    readonly isSuccess: boolean
}
export interface List_onScrollFrameBegin_event extends PeerEvent {
    readonly kind: PeerEventKind.List_onScrollFrameBegin
    readonly offset: number
    readonly state: ScrollState
}
export interface ListItem_onSelect_event extends PeerEvent {
    readonly kind: PeerEventKind.ListItem_onSelect
    readonly parameter: boolean
}
export interface ListItem__onChangeEvent_selected_event extends PeerEvent {
    readonly kind: PeerEventKind.ListItem__onChangeEvent_selected
    readonly parameter: boolean
}
export interface LocationButton_onClick_event extends PeerEvent {
    readonly kind: PeerEventKind.LocationButton_onClick
    readonly event: ClickEvent
    readonly result: LocationButtonOnClickResult
}
export interface Marquee_onStart_event extends PeerEvent {
    readonly kind: PeerEventKind.Marquee_onStart
}
export interface Marquee_onBounce_event extends PeerEvent {
    readonly kind: PeerEventKind.Marquee_onBounce
}
export interface Marquee_onFinish_event extends PeerEvent {
    readonly kind: PeerEventKind.Marquee_onFinish
}
export interface MenuItem_onChange_event extends PeerEvent {
    readonly kind: PeerEventKind.MenuItem_onChange
    readonly parameter: boolean
}
export interface MenuItem__onChangeEvent_selected_event extends PeerEvent {
    readonly kind: PeerEventKind.MenuItem__onChangeEvent_selected
    readonly parameter: boolean
}
export interface NavDestination_onShown_event extends PeerEvent {
    readonly kind: PeerEventKind.NavDestination_onShown
}
export interface NavDestination_onHidden_event extends PeerEvent {
    readonly kind: PeerEventKind.NavDestination_onHidden
}
export interface NavDestination_onBackPressed_event extends PeerEvent {
    readonly kind: PeerEventKind.NavDestination_onBackPressed
}
export interface NavDestination_onReady_event extends PeerEvent {
    readonly kind: PeerEventKind.NavDestination_onReady
    readonly parameter: NavDestinationContext
}
export interface NavDestination_onWillAppear_event extends PeerEvent {
    readonly kind: PeerEventKind.NavDestination_onWillAppear
}
export interface NavDestination_onWillDisappear_event extends PeerEvent {
    readonly kind: PeerEventKind.NavDestination_onWillDisappear
}
export interface NavDestination_onWillShow_event extends PeerEvent {
    readonly kind: PeerEventKind.NavDestination_onWillShow
}
export interface NavDestination_onWillHide_event extends PeerEvent {
    readonly kind: PeerEventKind.NavDestination_onWillHide
}
export interface NavRouter_onStateChange_event extends PeerEvent {
    readonly kind: PeerEventKind.NavRouter_onStateChange
    readonly parameter: boolean
}
export interface Panel_onChange_event extends PeerEvent {
    readonly kind: PeerEventKind.Panel_onChange
    readonly width: number
    readonly height: number
    readonly mode: PanelMode
}
export interface Panel_onHeightChange_event extends PeerEvent {
    readonly kind: PeerEventKind.Panel_onHeightChange
    readonly index: number
}
export interface Panel__onChangeEvent_mode_event extends PeerEvent {
    readonly kind: PeerEventKind.Panel__onChangeEvent_mode
    readonly mode: PanelMode
}
export interface PasteButton_onClick_event extends PeerEvent {
    readonly kind: PeerEventKind.PasteButton_onClick
    readonly event: ClickEvent
    readonly result: PasteButtonOnClickResult
}
export interface PatternLock_onPatternComplete_event extends PeerEvent {
    readonly kind: PeerEventKind.PatternLock_onPatternComplete
    readonly input: Array<number>
}
export interface PatternLock_onDotConnect_event extends PeerEvent {
    readonly kind: PeerEventKind.PatternLock_onDotConnect
    readonly index: number
}
export interface PluginComponent_onComplete_event extends PeerEvent {
    readonly kind: PeerEventKind.PluginComponent_onComplete
}
export interface PluginComponent_onError_event extends PeerEvent {
    readonly kind: PeerEventKind.PluginComponent_onError
    readonly info: PluginErrorData
}
export interface Radio_onChange_event extends PeerEvent {
    readonly kind: PeerEventKind.Radio_onChange
    readonly parameter: boolean
}
export interface Radio__onChangeEvent_checked_event extends PeerEvent {
    readonly kind: PeerEventKind.Radio__onChangeEvent_checked
    readonly parameter: boolean
}
export interface Rating_onChange_event extends PeerEvent {
    readonly kind: PeerEventKind.Rating_onChange
    readonly index: number
}
export interface Rating__onChangeEvent_rating_event extends PeerEvent {
    readonly kind: PeerEventKind.Rating__onChangeEvent_rating
    readonly index: number
}
export interface Refresh_onStateChange_event extends PeerEvent {
    readonly kind: PeerEventKind.Refresh_onStateChange
    readonly state: RefreshStatus
}
export interface Refresh_onRefreshing_event extends PeerEvent {
    readonly kind: PeerEventKind.Refresh_onRefreshing
}
export interface Refresh_onOffsetChange_event extends PeerEvent {
    readonly kind: PeerEventKind.Refresh_onOffsetChange
    readonly index: number
}
export interface Refresh__onChangeEvent_refreshing_event extends PeerEvent {
    readonly kind: PeerEventKind.Refresh__onChangeEvent_refreshing
    readonly parameter: boolean
}
export interface RichEditor_onReady_event extends PeerEvent {
    readonly kind: PeerEventKind.RichEditor_onReady
}
export interface RichEditor_onSelect_event extends PeerEvent {
    readonly kind: PeerEventKind.RichEditor_onSelect
    readonly parameter: RichEditorSelection
}
export interface RichEditor_onSelectionChange_event extends PeerEvent {
    readonly kind: PeerEventKind.RichEditor_onSelectionChange
    readonly parameter: RichEditorRange
}
export interface RichEditor_aboutToIMEInput_event extends PeerEvent {
    readonly kind: PeerEventKind.RichEditor_aboutToIMEInput
    readonly parameter: RichEditorInsertValue
}
export interface RichEditor_onIMEInputComplete_event extends PeerEvent {
    readonly kind: PeerEventKind.RichEditor_onIMEInputComplete
    readonly parameter: RichEditorTextSpanResult
}
export interface RichEditor_onDidIMEInput_event extends PeerEvent {
    readonly kind: PeerEventKind.RichEditor_onDidIMEInput
    readonly parameter: TextRange
}
export interface RichEditor_aboutToDelete_event extends PeerEvent {
    readonly kind: PeerEventKind.RichEditor_aboutToDelete
    readonly parameter: RichEditorDeleteValue
}
export interface RichEditor_onDeleteComplete_event extends PeerEvent {
    readonly kind: PeerEventKind.RichEditor_onDeleteComplete
}
export interface RichEditor_onPaste_event extends PeerEvent {
    readonly kind: PeerEventKind.RichEditor_onPaste
    readonly event?: PasteEvent | undefined
}
export interface RichEditor_onEditingChange_event extends PeerEvent {
    readonly kind: PeerEventKind.RichEditor_onEditingChange
    readonly parameter: boolean
}
export interface RichEditor_onSubmit_event extends PeerEvent {
    readonly kind: PeerEventKind.RichEditor_onSubmit
    readonly enterKey: EnterKeyType
    readonly event: SubmitEvent
}
export interface RichEditor_onWillChange_event extends PeerEvent {
    readonly kind: PeerEventKind.RichEditor_onWillChange
    readonly parameter: RichEditorChangeValue
}
export interface RichEditor_onDidChange_event extends PeerEvent {
    readonly kind: PeerEventKind.RichEditor_onDidChange
    readonly rangeBefore: TextRange
    readonly rangeAfter: TextRange
}
export interface RichEditor_onCut_event extends PeerEvent {
    readonly kind: PeerEventKind.RichEditor_onCut
    readonly parameter: CutEvent
}
export interface RichEditor_onCopy_event extends PeerEvent {
    readonly kind: PeerEventKind.RichEditor_onCopy
    readonly parameter: CopyEvent
}
export interface RichEditor_bindSelectionMenu_event extends PeerEvent {
    readonly kind: PeerEventKind.RichEditor_bindSelectionMenu
}
export interface RichEditor_customKeyboard_event extends PeerEvent {
    readonly kind: PeerEventKind.RichEditor_customKeyboard
}
export interface RichText_onStart_event extends PeerEvent {
    readonly kind: PeerEventKind.RichText_onStart
}
export interface RichText_onComplete_event extends PeerEvent {
    readonly kind: PeerEventKind.RichText_onComplete
}
export interface SaveButton_onClick_event extends PeerEvent {
    readonly kind: PeerEventKind.SaveButton_onClick
    readonly event: ClickEvent
    readonly result: SaveButtonOnClickResult
}
export interface Scroll_onScroll_event extends PeerEvent {
    readonly kind: PeerEventKind.Scroll_onScroll
    readonly first: number
    readonly last: number
}
export interface Scroll_onDidScroll_event extends PeerEvent {
    readonly kind: PeerEventKind.Scroll_onDidScroll
    readonly xOffset: number
    readonly yOffset: number
    readonly scrollState: ScrollState
}
export interface Scroll_onScrollEdge_event extends PeerEvent {
    readonly kind: PeerEventKind.Scroll_onScrollEdge
    readonly side: Edge
}
export interface Scroll_onScrollStart_event extends PeerEvent {
    readonly kind: PeerEventKind.Scroll_onScrollStart
}
export interface Scroll_onScrollEnd_event extends PeerEvent {
    readonly kind: PeerEventKind.Scroll_onScrollEnd
}
export interface Scroll_onScrollStop_event extends PeerEvent {
    readonly kind: PeerEventKind.Scroll_onScrollStop
}
export interface Scroll_onScrollFrameBegin_event extends PeerEvent {
    readonly kind: PeerEventKind.Scroll_onScrollFrameBegin
    readonly offset: number
    readonly state: ScrollState
}
export interface Search_onEditChange_event extends PeerEvent {
    readonly kind: PeerEventKind.Search_onEditChange
    readonly parameter: boolean
}
export interface Search_onSubmit0_event extends PeerEvent {
    readonly kind: PeerEventKind.Search_onSubmit0
    readonly breakpoints: string
}
export interface Search_onSubmit1_event extends PeerEvent {
    readonly kind: PeerEventKind.Search_onSubmit1
    readonly searchContent: string
    readonly event?: SubmitEvent | undefined
}
export interface Search_onChange_event extends PeerEvent {
    readonly kind: PeerEventKind.Search_onChange
    readonly value: string
    readonly previewText?: PreviewText | undefined
}
export interface Search_onTextSelectionChange_event extends PeerEvent {
    readonly kind: PeerEventKind.Search_onTextSelectionChange
    readonly selectionStart: number
    readonly selectionEnd: number
}
export interface Search_onContentScroll_event extends PeerEvent {
    readonly kind: PeerEventKind.Search_onContentScroll
    readonly totalOffsetX: number
    readonly totalOffsetY: number
}
export interface Search_onCopy_event extends PeerEvent {
    readonly kind: PeerEventKind.Search_onCopy
    readonly breakpoints: string
}
export interface Search_onCut_event extends PeerEvent {
    readonly kind: PeerEventKind.Search_onCut
    readonly breakpoints: string
}
export interface Search_onPaste_event extends PeerEvent {
    readonly kind: PeerEventKind.Search_onPaste
    readonly content: string
    readonly event: PasteEvent
}
export interface Search_onWillInsert_event extends PeerEvent {
    readonly kind: PeerEventKind.Search_onWillInsert
    readonly parameter: InsertValue
}
export interface Search_onDidInsert_event extends PeerEvent {
    readonly kind: PeerEventKind.Search_onDidInsert
    readonly parameter: InsertValue
}
export interface Search_onWillDelete_event extends PeerEvent {
    readonly kind: PeerEventKind.Search_onWillDelete
    readonly parameter: DeleteValue
}
export interface Search_onDidDelete_event extends PeerEvent {
    readonly kind: PeerEventKind.Search_onDidDelete
    readonly parameter: DeleteValue
}
export interface Search_customKeyboard_event extends PeerEvent {
    readonly kind: PeerEventKind.Search_customKeyboard
}
export interface Search__onChangeEvent_value_event extends PeerEvent {
    readonly kind: PeerEventKind.Search__onChangeEvent_value
    readonly breakpoints: string
}
export interface Select_onSelect_event extends PeerEvent {
    readonly kind: PeerEventKind.Select_onSelect
    readonly index: number
    readonly value: string
}
export interface Select__onChangeEvent_selected_event extends PeerEvent {
    readonly kind: PeerEventKind.Select__onChangeEvent_selected
    readonly selected: number | Resource
}
export interface Select__onChangeEvent_value_event extends PeerEvent {
    readonly kind: PeerEventKind.Select__onChangeEvent_value
    readonly value: ResourceStr
}
export interface Slider_onChange_event extends PeerEvent {
    readonly kind: PeerEventKind.Slider_onChange
    readonly value: number
    readonly mode: SliderChangeMode
}
export interface Slider__onChangeEvent_value_event extends PeerEvent {
    readonly kind: PeerEventKind.Slider__onChangeEvent_value
    readonly index: number
}
export interface Stepper_onFinish_event extends PeerEvent {
    readonly kind: PeerEventKind.Stepper_onFinish
}
export interface Stepper_onSkip_event extends PeerEvent {
    readonly kind: PeerEventKind.Stepper_onSkip
}
export interface Stepper_onChange_event extends PeerEvent {
    readonly kind: PeerEventKind.Stepper_onChange
    readonly first: number
    readonly last: number
}
export interface Stepper_onNext_event extends PeerEvent {
    readonly kind: PeerEventKind.Stepper_onNext
    readonly first: number
    readonly last: number
}
export interface Stepper_onPrevious_event extends PeerEvent {
    readonly kind: PeerEventKind.Stepper_onPrevious
    readonly first: number
    readonly last: number
}
export interface Stepper__onChangeEvent_index_event extends PeerEvent {
    readonly kind: PeerEventKind.Stepper__onChangeEvent_index
    readonly index: number
}
export interface Swiper_onChange_event extends PeerEvent {
    readonly kind: PeerEventKind.Swiper_onChange
    readonly index: number
}
export interface Swiper_onAnimationStart_event extends PeerEvent {
    readonly kind: PeerEventKind.Swiper_onAnimationStart
    readonly index: number
    readonly targetIndex: number
    readonly extraInfo: SwiperAnimationEvent
}
export interface Swiper_onAnimationEnd_event extends PeerEvent {
    readonly kind: PeerEventKind.Swiper_onAnimationEnd
    readonly index: number
    readonly extraInfo: SwiperAnimationEvent
}
export interface Swiper_onGestureSwipe_event extends PeerEvent {
    readonly kind: PeerEventKind.Swiper_onGestureSwipe
    readonly index: number
    readonly extraInfo: SwiperAnimationEvent
}
export interface Swiper_onContentDidScroll_event extends PeerEvent {
    readonly kind: PeerEventKind.Swiper_onContentDidScroll
    readonly selectedIndex: number
    readonly index: number
    readonly position: number
    readonly mainAxisLength: number
}
export interface Swiper__onChangeEvent_index_event extends PeerEvent {
    readonly kind: PeerEventKind.Swiper__onChangeEvent_index
    readonly index: number
}
export interface IndicatorComponent_onChange_event extends PeerEvent {
    readonly kind: PeerEventKind.IndicatorComponent_onChange
    readonly index: number
}
export interface Tabs_onChange_event extends PeerEvent {
    readonly kind: PeerEventKind.Tabs_onChange
    readonly index: number
}
export interface Tabs_onTabBarClick_event extends PeerEvent {
    readonly kind: PeerEventKind.Tabs_onTabBarClick
    readonly index: number
}
export interface Tabs_onAnimationStart_event extends PeerEvent {
    readonly kind: PeerEventKind.Tabs_onAnimationStart
    readonly index: number
    readonly targetIndex: number
    readonly extraInfo: TabsAnimationEvent
}
export interface Tabs_onAnimationEnd_event extends PeerEvent {
    readonly kind: PeerEventKind.Tabs_onAnimationEnd
    readonly index: number
    readonly extraInfo: TabsAnimationEvent
}
export interface Tabs_onGestureSwipe_event extends PeerEvent {
    readonly kind: PeerEventKind.Tabs_onGestureSwipe
    readonly index: number
    readonly extraInfo: TabsAnimationEvent
}
export interface Tabs_customContentTransition_event extends PeerEvent {
    readonly kind: PeerEventKind.Tabs_customContentTransition
    readonly from: number
    readonly to: number
}
export interface Tabs_onContentWillChange_event extends PeerEvent {
    readonly kind: PeerEventKind.Tabs_onContentWillChange
    readonly currentIndex: number
    readonly comingIndex: number
}
export interface Tabs__onChangeEvent_index_event extends PeerEvent {
    readonly kind: PeerEventKind.Tabs__onChangeEvent_index
    readonly index: number
}
export interface TabContent_onWillShow_event extends PeerEvent {
    readonly kind: PeerEventKind.TabContent_onWillShow
}
export interface TabContent_onWillHide_event extends PeerEvent {
    readonly kind: PeerEventKind.TabContent_onWillHide
}
export interface Text_onCopy_event extends PeerEvent {
    readonly kind: PeerEventKind.Text_onCopy
    readonly breakpoints: string
}
export interface Text_onTextSelectionChange_event extends PeerEvent {
    readonly kind: PeerEventKind.Text_onTextSelectionChange
    readonly first: number
    readonly last: number
}
export interface Text_bindSelectionMenu_event extends PeerEvent {
    readonly kind: PeerEventKind.Text_bindSelectionMenu
}
export interface TextArea_onSubmit0_event extends PeerEvent {
    readonly kind: PeerEventKind.TextArea_onSubmit0
    readonly enterKey: EnterKeyType
}
export interface TextArea_onSubmit1_event extends PeerEvent {
    readonly kind: PeerEventKind.TextArea_onSubmit1
    readonly enterKeyType: EnterKeyType
    readonly event?: SubmitEvent | undefined
}
export interface TextArea_onChange_event extends PeerEvent {
    readonly kind: PeerEventKind.TextArea_onChange
    readonly value: string
    readonly previewText?: PreviewText | undefined
}
export interface TextArea_onTextSelectionChange_event extends PeerEvent {
    readonly kind: PeerEventKind.TextArea_onTextSelectionChange
    readonly first: number
    readonly last: number
}
export interface TextArea_onContentScroll_event extends PeerEvent {
    readonly kind: PeerEventKind.TextArea_onContentScroll
    readonly first: number
    readonly last: number
}
export interface TextArea_onEditChange_event extends PeerEvent {
    readonly kind: PeerEventKind.TextArea_onEditChange
    readonly parameter: boolean
}
export interface TextArea_onCopy_event extends PeerEvent {
    readonly kind: PeerEventKind.TextArea_onCopy
    readonly breakpoints: string
}
export interface TextArea_onCut_event extends PeerEvent {
    readonly kind: PeerEventKind.TextArea_onCut
    readonly breakpoints: string
}
export interface TextArea_onPaste_event extends PeerEvent {
    readonly kind: PeerEventKind.TextArea_onPaste
    readonly value: string
    readonly event: PasteEvent
}
export interface TextArea_onWillInsert_event extends PeerEvent {
    readonly kind: PeerEventKind.TextArea_onWillInsert
    readonly parameter: InsertValue
}
export interface TextArea_onDidInsert_event extends PeerEvent {
    readonly kind: PeerEventKind.TextArea_onDidInsert
    readonly parameter: InsertValue
}
export interface TextArea_onWillDelete_event extends PeerEvent {
    readonly kind: PeerEventKind.TextArea_onWillDelete
    readonly parameter: DeleteValue
}
export interface TextArea_onDidDelete_event extends PeerEvent {
    readonly kind: PeerEventKind.TextArea_onDidDelete
    readonly parameter: DeleteValue
}
export interface TextArea_customKeyboard_event extends PeerEvent {
    readonly kind: PeerEventKind.TextArea_customKeyboard
}
export interface TextArea__onChangeEvent_text_event extends PeerEvent {
    readonly kind: PeerEventKind.TextArea__onChangeEvent_text
    readonly value: ResourceStr
}
export interface TextClock_onDateChange_event extends PeerEvent {
    readonly kind: PeerEventKind.TextClock_onDateChange
    readonly index: number
}
export interface TextInput_onEditChanged_event extends PeerEvent {
    readonly kind: PeerEventKind.TextInput_onEditChanged
    readonly parameter: boolean
}
export interface TextInput_onEditChange_event extends PeerEvent {
    readonly kind: PeerEventKind.TextInput_onEditChange
    readonly parameter: boolean
}
export interface TextInput_onSubmit_event extends PeerEvent {
    readonly kind: PeerEventKind.TextInput_onSubmit
    readonly enterKey: EnterKeyType
    readonly event: SubmitEvent
}
export interface TextInput_onChange_event extends PeerEvent {
    readonly kind: PeerEventKind.TextInput_onChange
    readonly value: string
    readonly previewText?: PreviewText | undefined
}
export interface TextInput_onTextSelectionChange_event extends PeerEvent {
    readonly kind: PeerEventKind.TextInput_onTextSelectionChange
    readonly selectionStart: number
    readonly selectionEnd: number
}
export interface TextInput_onContentScroll_event extends PeerEvent {
    readonly kind: PeerEventKind.TextInput_onContentScroll
    readonly totalOffsetX: number
    readonly totalOffsetY: number
}
export interface TextInput_onCopy_event extends PeerEvent {
    readonly kind: PeerEventKind.TextInput_onCopy
    readonly breakpoints: string
}
export interface TextInput_onCut_event extends PeerEvent {
    readonly kind: PeerEventKind.TextInput_onCut
    readonly breakpoints: string
}
export interface TextInput_onPaste_event extends PeerEvent {
    readonly kind: PeerEventKind.TextInput_onPaste
    readonly content: string
    readonly event: PasteEvent
}
export interface TextInput_showUnit_event extends PeerEvent {
    readonly kind: PeerEventKind.TextInput_showUnit
}
export interface TextInput_onSecurityStateChange_event extends PeerEvent {
    readonly kind: PeerEventKind.TextInput_onSecurityStateChange
    readonly parameter: boolean
}
export interface TextInput_onWillInsert_event extends PeerEvent {
    readonly kind: PeerEventKind.TextInput_onWillInsert
    readonly parameter: InsertValue
}
export interface TextInput_onDidInsert_event extends PeerEvent {
    readonly kind: PeerEventKind.TextInput_onDidInsert
    readonly parameter: InsertValue
}
export interface TextInput_onWillDelete_event extends PeerEvent {
    readonly kind: PeerEventKind.TextInput_onWillDelete
    readonly parameter: DeleteValue
}
export interface TextInput_onDidDelete_event extends PeerEvent {
    readonly kind: PeerEventKind.TextInput_onDidDelete
    readonly parameter: DeleteValue
}
export interface TextInput_customKeyboard_event extends PeerEvent {
    readonly kind: PeerEventKind.TextInput_customKeyboard
}
export interface TextInput__onChangeEvent_text_event extends PeerEvent {
    readonly kind: PeerEventKind.TextInput__onChangeEvent_text
    readonly value: ResourceStr
}
export interface TextPicker_onAccept_event extends PeerEvent {
    readonly kind: PeerEventKind.TextPicker_onAccept
    readonly value: string
    readonly index: number
}
export interface TextPicker_onCancel_event extends PeerEvent {
    readonly kind: PeerEventKind.TextPicker_onCancel
}
export interface TextPicker_onChange_event extends PeerEvent {
    readonly kind: PeerEventKind.TextPicker_onChange
    readonly value: string | Array<string>
    readonly index: number | Array<number>
}
export interface TextPicker__onChangeEvent_selected_event extends PeerEvent {
    readonly kind: PeerEventKind.TextPicker__onChangeEvent_selected
    readonly selected: number | Array<number>
}
export interface TextPicker__onChangeEvent_value_event extends PeerEvent {
    readonly kind: PeerEventKind.TextPicker__onChangeEvent_value
    readonly value: string | Array<string>
}
export interface TextTimer_onTimer_event extends PeerEvent {
    readonly kind: PeerEventKind.TextTimer_onTimer
    readonly first: number
    readonly last: number
}
export interface TimePicker_onChange_event extends PeerEvent {
    readonly kind: PeerEventKind.TimePicker_onChange
    readonly value: TimePickerResult
}
export interface TimePicker__onChangeEvent_selected_event extends PeerEvent {
    readonly kind: PeerEventKind.TimePicker__onChangeEvent_selected
    readonly parameter: Date
}
export interface Toggle_onChange_event extends PeerEvent {
    readonly kind: PeerEventKind.Toggle_onChange
    readonly parameter: boolean
}
export interface Toggle__onChangeEvent_isOn_event extends PeerEvent {
    readonly kind: PeerEventKind.Toggle__onChangeEvent_isOn
    readonly parameter: boolean
}
export interface Video_onStart_event extends PeerEvent {
    readonly kind: PeerEventKind.Video_onStart
}
export interface Video_onPause_event extends PeerEvent {
    readonly kind: PeerEventKind.Video_onPause
}
export interface Video_onFinish_event extends PeerEvent {
    readonly kind: PeerEventKind.Video_onFinish
}
export interface Video_onFullscreenChange_event extends PeerEvent {
    readonly kind: PeerEventKind.Video_onFullscreenChange
    readonly parameter: FullscreenInfo
}
export interface Video_onPrepared_event extends PeerEvent {
    readonly kind: PeerEventKind.Video_onPrepared
    readonly parameter: PreparedInfo
}
export interface Video_onSeeking_event extends PeerEvent {
    readonly kind: PeerEventKind.Video_onSeeking
    readonly parameter: PlaybackInfo
}
export interface Video_onSeeked_event extends PeerEvent {
    readonly kind: PeerEventKind.Video_onSeeked
    readonly parameter: PlaybackInfo
}
export interface Video_onUpdate_event extends PeerEvent {
    readonly kind: PeerEventKind.Video_onUpdate
    readonly parameter: PlaybackInfo
}
export interface Video_onError_event extends PeerEvent {
    readonly kind: PeerEventKind.Video_onError
}
export interface Video_onStop_event extends PeerEvent {
    readonly kind: PeerEventKind.Video_onStop
}
export interface Web_onPageEnd_event extends PeerEvent {
    readonly kind: PeerEventKind.Web_onPageEnd
    readonly parameter: OnPageEndEvent
}
export interface Web_onPageBegin_event extends PeerEvent {
    readonly kind: PeerEventKind.Web_onPageBegin
    readonly parameter: OnPageBeginEvent
}
export interface Web_onProgressChange_event extends PeerEvent {
    readonly kind: PeerEventKind.Web_onProgressChange
    readonly parameter: OnProgressChangeEvent
}
export interface Web_onTitleReceive_event extends PeerEvent {
    readonly kind: PeerEventKind.Web_onTitleReceive
    readonly parameter: OnTitleReceiveEvent
}
export interface Web_onGeolocationHide_event extends PeerEvent {
    readonly kind: PeerEventKind.Web_onGeolocationHide
}
export interface Web_onGeolocationShow_event extends PeerEvent {
    readonly kind: PeerEventKind.Web_onGeolocationShow
    readonly parameter: OnGeolocationShowEvent
}
export interface Web_onRequestSelected_event extends PeerEvent {
    readonly kind: PeerEventKind.Web_onRequestSelected
}
export interface Web_onAlert_event extends PeerEvent {
    readonly kind: PeerEventKind.Web_onAlert
    readonly parameter: OnAlertEvent
}
export interface Web_onBeforeUnload_event extends PeerEvent {
    readonly kind: PeerEventKind.Web_onBeforeUnload
    readonly parameter: OnBeforeUnloadEvent
}
export interface Web_onConfirm_event extends PeerEvent {
    readonly kind: PeerEventKind.Web_onConfirm
    readonly parameter: OnConfirmEvent
}
export interface Web_onPrompt_event extends PeerEvent {
    readonly kind: PeerEventKind.Web_onPrompt
    readonly parameter: OnPromptEvent
}
export interface Web_onConsole_event extends PeerEvent {
    readonly kind: PeerEventKind.Web_onConsole
    readonly parameter: OnConsoleEvent
}
export interface Web_onErrorReceive_event extends PeerEvent {
    readonly kind: PeerEventKind.Web_onErrorReceive
    readonly parameter: OnErrorReceiveEvent
}
export interface Web_onHttpErrorReceive_event extends PeerEvent {
    readonly kind: PeerEventKind.Web_onHttpErrorReceive
    readonly parameter: OnHttpErrorReceiveEvent
}
export interface Web_onDownloadStart_event extends PeerEvent {
    readonly kind: PeerEventKind.Web_onDownloadStart
    readonly parameter: OnDownloadStartEvent
}
export interface Web_onRefreshAccessedHistory_event extends PeerEvent {
    readonly kind: PeerEventKind.Web_onRefreshAccessedHistory
    readonly parameter: OnRefreshAccessedHistoryEvent
}
export interface Web_onUrlLoadIntercept_event extends PeerEvent {
    readonly kind: PeerEventKind.Web_onUrlLoadIntercept
    readonly event?: { data: string | WebResourceRequest } | undefined
}
export interface Web_onSslErrorReceive_event extends PeerEvent {
    readonly kind: PeerEventKind.Web_onSslErrorReceive
    readonly event?: { handler: Function, error: Object } | undefined
}
export interface Web_onRenderExited0_event extends PeerEvent {
    readonly kind: PeerEventKind.Web_onRenderExited0
    readonly parameter: OnRenderExitedEvent
}
export interface Web_onRenderExited1_event extends PeerEvent {
    readonly kind: PeerEventKind.Web_onRenderExited1
    readonly event?: { detail: Object } | undefined
}
export interface Web_onShowFileSelector_event extends PeerEvent {
    readonly kind: PeerEventKind.Web_onShowFileSelector
    readonly parameter: OnShowFileSelectorEvent
}
export interface Web_onFileSelectorShow_event extends PeerEvent {
    readonly kind: PeerEventKind.Web_onFileSelectorShow
    readonly event?: { callback_: Function, fileSelector: Object } | undefined
}
export interface Web_onResourceLoad_event extends PeerEvent {
    readonly kind: PeerEventKind.Web_onResourceLoad
    readonly parameter: OnResourceLoadEvent
}
export interface Web_onFullScreenExit_event extends PeerEvent {
    readonly kind: PeerEventKind.Web_onFullScreenExit
}
export interface Web_onFullScreenEnter_event extends PeerEvent {
    readonly kind: PeerEventKind.Web_onFullScreenEnter
    readonly event: FullScreenEnterEvent
}
export interface Web_onScaleChange_event extends PeerEvent {
    readonly kind: PeerEventKind.Web_onScaleChange
    readonly parameter: OnScaleChangeEvent
}
export interface Web_onHttpAuthRequest_event extends PeerEvent {
    readonly kind: PeerEventKind.Web_onHttpAuthRequest
    readonly parameter: OnHttpAuthRequestEvent
}
export interface Web_onInterceptRequest_event extends PeerEvent {
    readonly kind: PeerEventKind.Web_onInterceptRequest
    readonly parameter: OnInterceptRequestEvent
}
export interface Web_onPermissionRequest_event extends PeerEvent {
    readonly kind: PeerEventKind.Web_onPermissionRequest
    readonly parameter: OnPermissionRequestEvent
}
export interface Web_onScreenCaptureRequest_event extends PeerEvent {
    readonly kind: PeerEventKind.Web_onScreenCaptureRequest
    readonly parameter: OnScreenCaptureRequestEvent
}
export interface Web_onContextMenuShow_event extends PeerEvent {
    readonly kind: PeerEventKind.Web_onContextMenuShow
    readonly parameter: OnContextMenuShowEvent
}
export interface Web_onContextMenuHide_event extends PeerEvent {
    readonly kind: PeerEventKind.Web_onContextMenuHide
}
export interface Web_onSearchResultReceive_event extends PeerEvent {
    readonly kind: PeerEventKind.Web_onSearchResultReceive
    readonly parameter: OnSearchResultReceiveEvent
}
export interface Web_onScroll_event extends PeerEvent {
    readonly kind: PeerEventKind.Web_onScroll
    readonly parameter: OnScrollEvent
}
export interface Web_onSslErrorEventReceive_event extends PeerEvent {
    readonly kind: PeerEventKind.Web_onSslErrorEventReceive
    readonly parameter: OnSslErrorEventReceiveEvent
}
export interface Web_onSslErrorEvent_event extends PeerEvent {
    readonly kind: PeerEventKind.Web_onSslErrorEvent
    readonly sslErrorEvent: SslErrorEvent
}
export interface Web_onClientAuthenticationRequest_event extends PeerEvent {
    readonly kind: PeerEventKind.Web_onClientAuthenticationRequest
    readonly parameter: OnClientAuthenticationEvent
}
export interface Web_onWindowNew_event extends PeerEvent {
    readonly kind: PeerEventKind.Web_onWindowNew
    readonly parameter: OnWindowNewEvent
}
export interface Web_onWindowExit_event extends PeerEvent {
    readonly kind: PeerEventKind.Web_onWindowExit
}
export interface Web_onInterceptKeyEvent_event extends PeerEvent {
    readonly kind: PeerEventKind.Web_onInterceptKeyEvent
    readonly parameter: KeyEvent
}
export interface Web_onTouchIconUrlReceived_event extends PeerEvent {
    readonly kind: PeerEventKind.Web_onTouchIconUrlReceived
    readonly parameter: OnTouchIconUrlReceivedEvent
}
export interface Web_onFaviconReceived_event extends PeerEvent {
    readonly kind: PeerEventKind.Web_onFaviconReceived
    readonly parameter: OnFaviconReceivedEvent
}
export interface Web_onPageVisible_event extends PeerEvent {
    readonly kind: PeerEventKind.Web_onPageVisible
    readonly parameter: OnPageVisibleEvent
}
export interface Web_onDataResubmitted_event extends PeerEvent {
    readonly kind: PeerEventKind.Web_onDataResubmitted
    readonly parameter: OnDataResubmittedEvent
}
export interface Web_onAudioStateChanged_event extends PeerEvent {
    readonly kind: PeerEventKind.Web_onAudioStateChanged
    readonly parameter: OnAudioStateChangedEvent
}
export interface Web_onFirstContentfulPaint_event extends PeerEvent {
    readonly kind: PeerEventKind.Web_onFirstContentfulPaint
    readonly parameter: OnFirstContentfulPaintEvent
}
export interface Web_onFirstMeaningfulPaint_event extends PeerEvent {
    readonly kind: PeerEventKind.Web_onFirstMeaningfulPaint
    readonly firstMeaningfulPaint: FirstMeaningfulPaint
}
export interface Web_onLargestContentfulPaint_event extends PeerEvent {
    readonly kind: PeerEventKind.Web_onLargestContentfulPaint
    readonly largestContentfulPaint: LargestContentfulPaint
}
export interface Web_onLoadIntercept_event extends PeerEvent {
    readonly kind: PeerEventKind.Web_onLoadIntercept
    readonly parameter: OnLoadInterceptEvent
}
export interface Web_onControllerAttached_event extends PeerEvent {
    readonly kind: PeerEventKind.Web_onControllerAttached
}
export interface Web_onOverScroll_event extends PeerEvent {
    readonly kind: PeerEventKind.Web_onOverScroll
    readonly parameter: OnOverScrollEvent
}
export interface Web_onSafeBrowsingCheckResult_event extends PeerEvent {
    readonly kind: PeerEventKind.Web_onSafeBrowsingCheckResult
    readonly threatType: ThreatType
}
export interface Web_onNavigationEntryCommitted_event extends PeerEvent {
    readonly kind: PeerEventKind.Web_onNavigationEntryCommitted
    readonly loadCommittedDetails: LoadCommittedDetails
}
export interface Web_onIntelligentTrackingPreventionResult_event extends PeerEvent {
    readonly kind: PeerEventKind.Web_onIntelligentTrackingPreventionResult
    readonly details: IntelligentTrackingPreventionDetails
}
export interface Web_onNativeEmbedLifecycleChange_event extends PeerEvent {
    readonly kind: PeerEventKind.Web_onNativeEmbedLifecycleChange
    readonly event: NativeEmbedDataInfo
}
export interface Web_onNativeEmbedVisibilityChange_event extends PeerEvent {
    readonly kind: PeerEventKind.Web_onNativeEmbedVisibilityChange
    readonly nativeEmbedVisibilityInfo: NativeEmbedVisibilityInfo
}
export interface Web_onNativeEmbedGestureEvent_event extends PeerEvent {
    readonly kind: PeerEventKind.Web_onNativeEmbedGestureEvent
    readonly event: NativeEmbedTouchInfo
}
export interface Web_onOverrideUrlLoading_event extends PeerEvent {
    readonly kind: PeerEventKind.Web_onOverrideUrlLoading
    readonly webResourceRequest: WebResourceRequest
}
export interface Web_onRenderProcessNotResponding_event extends PeerEvent {
    readonly kind: PeerEventKind.Web_onRenderProcessNotResponding
    readonly data: RenderProcessNotRespondingData
}
export interface Web_onRenderProcessResponding_event extends PeerEvent {
    readonly kind: PeerEventKind.Web_onRenderProcessResponding
}
export interface Web_onViewportFitChanged_event extends PeerEvent {
    readonly kind: PeerEventKind.Web_onViewportFitChanged
    readonly viewportFit: ViewportFit
}
export interface Web_onInterceptKeyboardAttach_event extends PeerEvent {
    readonly kind: PeerEventKind.Web_onInterceptKeyboardAttach
    readonly keyboardCallbackInfo: WebKeyboardCallbackInfo
}
export interface Web_onAdsBlocked_event extends PeerEvent {
    readonly kind: PeerEventKind.Web_onAdsBlocked
    readonly details: AdsBlockedDetails
}
export interface Web_bindSelectionMenu_event extends PeerEvent {
    readonly kind: PeerEventKind.Web_bindSelectionMenu
}
export interface XComponent_onLoad_event extends PeerEvent {
    readonly kind: PeerEventKind.XComponent_onLoad
    readonly event?: Object | undefined
}
export interface XComponent_onDestroy_event extends PeerEvent {
    readonly kind: PeerEventKind.XComponent_onDestroy
}
export interface SideBarContainer_onChange_event extends PeerEvent {
    readonly kind: PeerEventKind.SideBarContainer_onChange
    readonly parameter: boolean
}
export interface SideBarContainer__onChangeEvent_showSideBar_event extends PeerEvent {
    readonly kind: PeerEventKind.SideBarContainer__onChangeEvent_showSideBar
    readonly parameter: boolean
}
export interface WaterFlow_onReachStart_event extends PeerEvent {
    readonly kind: PeerEventKind.WaterFlow_onReachStart
}
export interface WaterFlow_onReachEnd_event extends PeerEvent {
    readonly kind: PeerEventKind.WaterFlow_onReachEnd
}
export interface WaterFlow_onScrollFrameBegin_event extends PeerEvent {
    readonly kind: PeerEventKind.WaterFlow_onScrollFrameBegin
    readonly offset: number
    readonly state: ScrollState
}
export interface WaterFlow_onScrollIndex_event extends PeerEvent {
    readonly kind: PeerEventKind.WaterFlow_onScrollIndex
    readonly first: number
    readonly last: number
}
export interface UIExtensionComponent_onRemoteReady_event extends PeerEvent {
    readonly kind: PeerEventKind.UIExtensionComponent_onRemoteReady
    readonly parameter: UIExtensionProxy
}
export interface UIExtensionComponent_onResult_event extends PeerEvent {
    readonly kind: PeerEventKind.UIExtensionComponent_onResult
    readonly parameter: { code: number, want?: Want }
}
export interface UIExtensionComponent_onRelease_event extends PeerEvent {
    readonly kind: PeerEventKind.UIExtensionComponent_onRelease
    readonly index: number
}
export interface UIExtensionComponent_onError_event extends PeerEvent {
    readonly kind: PeerEventKind.UIExtensionComponent_onError
    readonly err: BusinessError
}
export interface UIExtensionComponent_onTerminated_event extends PeerEvent {
    readonly kind: PeerEventKind.UIExtensionComponent_onTerminated
    readonly parameter: TerminationInfo
}
export function getEventNameByKind(kind: PeerEventKind): string {
    switch (kind) {
        case PeerEventKind.AbilityComponent_onConnect: return "AbilityComponent_onConnect"
        case PeerEventKind.AbilityComponent_onDisconnect: return "AbilityComponent_onDisconnect"
        case PeerEventKind.AlphabetIndexer_onSelected: return "AlphabetIndexer_onSelected"
        case PeerEventKind.AlphabetIndexer_onSelect: return "AlphabetIndexer_onSelect"
        case PeerEventKind.AlphabetIndexer_onRequestPopupData: return "AlphabetIndexer_onRequestPopupData"
        case PeerEventKind.AlphabetIndexer_onPopupSelect: return "AlphabetIndexer_onPopupSelect"
        case PeerEventKind.AlphabetIndexer__onChangeEvent_selected: return "AlphabetIndexer__onChangeEvent_selected"
        case PeerEventKind.Animator_onStart: return "Animator_onStart"
        case PeerEventKind.Animator_onPause: return "Animator_onPause"
        case PeerEventKind.Animator_onRepeat: return "Animator_onRepeat"
        case PeerEventKind.Animator_onCancel: return "Animator_onCancel"
        case PeerEventKind.Animator_onFinish: return "Animator_onFinish"
        case PeerEventKind.Animator_onFrame: return "Animator_onFrame"
        case PeerEventKind.Calendar_onSelectChange: return "Calendar_onSelectChange"
        case PeerEventKind.Calendar_onRequestData: return "Calendar_onRequestData"
        case PeerEventKind.CalendarPicker_onChange: return "CalendarPicker_onChange"
        case PeerEventKind.Canvas_onReady: return "Canvas_onReady"
        case PeerEventKind.Checkbox_onChange: return "Checkbox_onChange"
        case PeerEventKind.Checkbox__onChangeEvent_select: return "Checkbox__onChangeEvent_select"
        case PeerEventKind.CheckboxGroup_onChange: return "CheckboxGroup_onChange"
        case PeerEventKind.CheckboxGroup__onChangeEvent_selectAll: return "CheckboxGroup__onChangeEvent_selectAll"
        case PeerEventKind.CommonMethod_onChildTouchTest: return "CommonMethod_onChildTouchTest"
        case PeerEventKind.CommonMethod_onClick0: return "CommonMethod_onClick0"
        case PeerEventKind.CommonMethod_onClick1: return "CommonMethod_onClick1"
        case PeerEventKind.CommonMethod_onHover: return "CommonMethod_onHover"
        case PeerEventKind.CommonMethod_onAccessibilityHover: return "CommonMethod_onAccessibilityHover"
        case PeerEventKind.CommonMethod_onMouse: return "CommonMethod_onMouse"
        case PeerEventKind.CommonMethod_onTouch: return "CommonMethod_onTouch"
        case PeerEventKind.CommonMethod_onKeyEvent: return "CommonMethod_onKeyEvent"
        case PeerEventKind.CommonMethod_onKeyPreIme: return "CommonMethod_onKeyPreIme"
        case PeerEventKind.CommonMethod_onFocus: return "CommonMethod_onFocus"
        case PeerEventKind.CommonMethod_onBlur: return "CommonMethod_onBlur"
        case PeerEventKind.CommonMethod_onAppear: return "CommonMethod_onAppear"
        case PeerEventKind.CommonMethod_onDisAppear: return "CommonMethod_onDisAppear"
        case PeerEventKind.CommonMethod_onAttach: return "CommonMethod_onAttach"
        case PeerEventKind.CommonMethod_onDetach: return "CommonMethod_onDetach"
        case PeerEventKind.CommonMethod_onAreaChange: return "CommonMethod_onAreaChange"
        case PeerEventKind.CommonMethod_onDragStart: return "CommonMethod_onDragStart"
        case PeerEventKind.CommonMethod_onDragEnter: return "CommonMethod_onDragEnter"
        case PeerEventKind.CommonMethod_onDragMove: return "CommonMethod_onDragMove"
        case PeerEventKind.CommonMethod_onDragLeave: return "CommonMethod_onDragLeave"
        case PeerEventKind.CommonMethod_onDrop: return "CommonMethod_onDrop"
        case PeerEventKind.CommonMethod_onDragEnd: return "CommonMethod_onDragEnd"
        case PeerEventKind.CommonMethod_onPreDrag: return "CommonMethod_onPreDrag"
        case PeerEventKind.CommonMethod_accessibilityVirtualNode: return "CommonMethod_accessibilityVirtualNode"
        case PeerEventKind.CommonMethod_onGestureJudgeBegin: return "CommonMethod_onGestureJudgeBegin"
        case PeerEventKind.CommonMethod_onGestureRecognizerJudgeBegin0: return "CommonMethod_onGestureRecognizerJudgeBegin0"
        case PeerEventKind.CommonMethod_onGestureRecognizerJudgeBegin1: return "CommonMethod_onGestureRecognizerJudgeBegin1"
        case PeerEventKind.CommonMethod_shouldBuiltInRecognizerParallelWith: return "CommonMethod_shouldBuiltInRecognizerParallelWith"
        case PeerEventKind.CommonMethod_onTouchIntercept: return "CommonMethod_onTouchIntercept"
        case PeerEventKind.CommonMethod_onSizeChange: return "CommonMethod_onSizeChange"
        case PeerEventKind.CommonMethod_background: return "CommonMethod_background"
        case PeerEventKind.CommonMethod_bindContextMenu0: return "CommonMethod_bindContextMenu0"
        case PeerEventKind.CommonMethod_bindContextMenu1: return "CommonMethod_bindContextMenu1"
        case PeerEventKind.CommonMethod_bindContentCover0: return "CommonMethod_bindContentCover0"
        case PeerEventKind.CommonMethod_bindContentCover1: return "CommonMethod_bindContentCover1"
        case PeerEventKind.CommonMethod_bindSheet: return "CommonMethod_bindSheet"
        case PeerEventKind.CommonMethod_onVisibleAreaChange: return "CommonMethod_onVisibleAreaChange"
        case PeerEventKind.ScrollableCommonMethod_onScroll: return "ScrollableCommonMethod_onScroll"
        case PeerEventKind.ScrollableCommonMethod_onDidScroll: return "ScrollableCommonMethod_onDidScroll"
        case PeerEventKind.ScrollableCommonMethod_onReachStart: return "ScrollableCommonMethod_onReachStart"
        case PeerEventKind.ScrollableCommonMethod_onReachEnd: return "ScrollableCommonMethod_onReachEnd"
        case PeerEventKind.ScrollableCommonMethod_onScrollStart: return "ScrollableCommonMethod_onScrollStart"
        case PeerEventKind.ScrollableCommonMethod_onScrollStop: return "ScrollableCommonMethod_onScrollStop"
        case PeerEventKind.Counter_onInc: return "Counter_onInc"
        case PeerEventKind.Counter_onDec: return "Counter_onDec"
        case PeerEventKind.DatePicker_onChange: return "DatePicker_onChange"
        case PeerEventKind.DatePicker_onDateChange: return "DatePicker_onDateChange"
        case PeerEventKind.DatePicker__onChangeEvent_selected: return "DatePicker__onChangeEvent_selected"
        case PeerEventKind.EmbeddedComponent_onTerminated: return "EmbeddedComponent_onTerminated"
        case PeerEventKind.EmbeddedComponent_onError: return "EmbeddedComponent_onError"
        case PeerEventKind.FolderStack_onFolderStateChange: return "FolderStack_onFolderStateChange"
        case PeerEventKind.FolderStack_onHoverStatusChange: return "FolderStack_onHoverStatusChange"
        case PeerEventKind.FormComponent_onAcquired: return "FormComponent_onAcquired"
        case PeerEventKind.FormComponent_onError: return "FormComponent_onError"
        case PeerEventKind.FormComponent_onRouter: return "FormComponent_onRouter"
        case PeerEventKind.FormComponent_onUninstall: return "FormComponent_onUninstall"
        case PeerEventKind.FormComponent_onLoad: return "FormComponent_onLoad"
        case PeerEventKind.Gauge_description: return "Gauge_description"
        case PeerEventKind.Grid_onScrollBarUpdate: return "Grid_onScrollBarUpdate"
        case PeerEventKind.Grid_onScrollIndex: return "Grid_onScrollIndex"
        case PeerEventKind.Grid_onItemDragStart: return "Grid_onItemDragStart"
        case PeerEventKind.Grid_onItemDragEnter: return "Grid_onItemDragEnter"
        case PeerEventKind.Grid_onItemDragMove: return "Grid_onItemDragMove"
        case PeerEventKind.Grid_onItemDragLeave: return "Grid_onItemDragLeave"
        case PeerEventKind.Grid_onItemDrop: return "Grid_onItemDrop"
        case PeerEventKind.Grid_onScroll: return "Grid_onScroll"
        case PeerEventKind.Grid_onReachStart: return "Grid_onReachStart"
        case PeerEventKind.Grid_onReachEnd: return "Grid_onReachEnd"
        case PeerEventKind.Grid_onScrollStart: return "Grid_onScrollStart"
        case PeerEventKind.Grid_onScrollStop: return "Grid_onScrollStop"
        case PeerEventKind.Grid_onScrollFrameBegin: return "Grid_onScrollFrameBegin"
        case PeerEventKind.GridItem_onSelect: return "GridItem_onSelect"
        case PeerEventKind.GridItem__onChangeEvent_selected: return "GridItem__onChangeEvent_selected"
        case PeerEventKind.GridRow_onBreakpointChange: return "GridRow_onBreakpointChange"
        case PeerEventKind.Image_onComplete: return "Image_onComplete"
        case PeerEventKind.Image_onError: return "Image_onError"
        case PeerEventKind.Image_onFinish: return "Image_onFinish"
        case PeerEventKind.ImageAnimator_onStart: return "ImageAnimator_onStart"
        case PeerEventKind.ImageAnimator_onPause: return "ImageAnimator_onPause"
        case PeerEventKind.ImageAnimator_onRepeat: return "ImageAnimator_onRepeat"
        case PeerEventKind.ImageAnimator_onCancel: return "ImageAnimator_onCancel"
        case PeerEventKind.ImageAnimator_onFinish: return "ImageAnimator_onFinish"
        case PeerEventKind.ImageSpan_onComplete: return "ImageSpan_onComplete"
        case PeerEventKind.ImageSpan_onError: return "ImageSpan_onError"
        case PeerEventKind.List_onScroll: return "List_onScroll"
        case PeerEventKind.List_onScrollIndex: return "List_onScrollIndex"
        case PeerEventKind.List_onScrollVisibleContentChange: return "List_onScrollVisibleContentChange"
        case PeerEventKind.List_onReachStart: return "List_onReachStart"
        case PeerEventKind.List_onReachEnd: return "List_onReachEnd"
        case PeerEventKind.List_onScrollStart: return "List_onScrollStart"
        case PeerEventKind.List_onScrollStop: return "List_onScrollStop"
        case PeerEventKind.List_onItemDelete: return "List_onItemDelete"
        case PeerEventKind.List_onItemMove: return "List_onItemMove"
        case PeerEventKind.List_onItemDragStart: return "List_onItemDragStart"
        case PeerEventKind.List_onItemDragEnter: return "List_onItemDragEnter"
        case PeerEventKind.List_onItemDragMove: return "List_onItemDragMove"
        case PeerEventKind.List_onItemDragLeave: return "List_onItemDragLeave"
        case PeerEventKind.List_onItemDrop: return "List_onItemDrop"
        case PeerEventKind.List_onScrollFrameBegin: return "List_onScrollFrameBegin"
        case PeerEventKind.ListItem_onSelect: return "ListItem_onSelect"
        case PeerEventKind.ListItem__onChangeEvent_selected: return "ListItem__onChangeEvent_selected"
        case PeerEventKind.LocationButton_onClick: return "LocationButton_onClick"
        case PeerEventKind.Marquee_onStart: return "Marquee_onStart"
        case PeerEventKind.Marquee_onBounce: return "Marquee_onBounce"
        case PeerEventKind.Marquee_onFinish: return "Marquee_onFinish"
        case PeerEventKind.MenuItem_onChange: return "MenuItem_onChange"
        case PeerEventKind.MenuItem__onChangeEvent_selected: return "MenuItem__onChangeEvent_selected"
        case PeerEventKind.NavDestination_onShown: return "NavDestination_onShown"
        case PeerEventKind.NavDestination_onHidden: return "NavDestination_onHidden"
        case PeerEventKind.NavDestination_onBackPressed: return "NavDestination_onBackPressed"
        case PeerEventKind.NavDestination_onReady: return "NavDestination_onReady"
        case PeerEventKind.NavDestination_onWillAppear: return "NavDestination_onWillAppear"
        case PeerEventKind.NavDestination_onWillDisappear: return "NavDestination_onWillDisappear"
        case PeerEventKind.NavDestination_onWillShow: return "NavDestination_onWillShow"
        case PeerEventKind.NavDestination_onWillHide: return "NavDestination_onWillHide"
        case PeerEventKind.NavRouter_onStateChange: return "NavRouter_onStateChange"
        case PeerEventKind.Panel_onChange: return "Panel_onChange"
        case PeerEventKind.Panel_onHeightChange: return "Panel_onHeightChange"
        case PeerEventKind.Panel__onChangeEvent_mode: return "Panel__onChangeEvent_mode"
        case PeerEventKind.PasteButton_onClick: return "PasteButton_onClick"
        case PeerEventKind.PatternLock_onPatternComplete: return "PatternLock_onPatternComplete"
        case PeerEventKind.PatternLock_onDotConnect: return "PatternLock_onDotConnect"
        case PeerEventKind.PluginComponent_onComplete: return "PluginComponent_onComplete"
        case PeerEventKind.PluginComponent_onError: return "PluginComponent_onError"
        case PeerEventKind.Radio_onChange: return "Radio_onChange"
        case PeerEventKind.Radio__onChangeEvent_checked: return "Radio__onChangeEvent_checked"
        case PeerEventKind.Rating_onChange: return "Rating_onChange"
        case PeerEventKind.Rating__onChangeEvent_rating: return "Rating__onChangeEvent_rating"
        case PeerEventKind.Refresh_onStateChange: return "Refresh_onStateChange"
        case PeerEventKind.Refresh_onRefreshing: return "Refresh_onRefreshing"
        case PeerEventKind.Refresh_onOffsetChange: return "Refresh_onOffsetChange"
        case PeerEventKind.Refresh__onChangeEvent_refreshing: return "Refresh__onChangeEvent_refreshing"
        case PeerEventKind.RichEditor_onReady: return "RichEditor_onReady"
        case PeerEventKind.RichEditor_onSelect: return "RichEditor_onSelect"
        case PeerEventKind.RichEditor_onSelectionChange: return "RichEditor_onSelectionChange"
        case PeerEventKind.RichEditor_aboutToIMEInput: return "RichEditor_aboutToIMEInput"
        case PeerEventKind.RichEditor_onIMEInputComplete: return "RichEditor_onIMEInputComplete"
        case PeerEventKind.RichEditor_onDidIMEInput: return "RichEditor_onDidIMEInput"
        case PeerEventKind.RichEditor_aboutToDelete: return "RichEditor_aboutToDelete"
        case PeerEventKind.RichEditor_onDeleteComplete: return "RichEditor_onDeleteComplete"
        case PeerEventKind.RichEditor_onPaste: return "RichEditor_onPaste"
        case PeerEventKind.RichEditor_onEditingChange: return "RichEditor_onEditingChange"
        case PeerEventKind.RichEditor_onSubmit: return "RichEditor_onSubmit"
        case PeerEventKind.RichEditor_onWillChange: return "RichEditor_onWillChange"
        case PeerEventKind.RichEditor_onDidChange: return "RichEditor_onDidChange"
        case PeerEventKind.RichEditor_onCut: return "RichEditor_onCut"
        case PeerEventKind.RichEditor_onCopy: return "RichEditor_onCopy"
        case PeerEventKind.RichEditor_bindSelectionMenu: return "RichEditor_bindSelectionMenu"
        case PeerEventKind.RichEditor_customKeyboard: return "RichEditor_customKeyboard"
        case PeerEventKind.RichText_onStart: return "RichText_onStart"
        case PeerEventKind.RichText_onComplete: return "RichText_onComplete"
        case PeerEventKind.SaveButton_onClick: return "SaveButton_onClick"
        case PeerEventKind.Scroll_onScroll: return "Scroll_onScroll"
        case PeerEventKind.Scroll_onDidScroll: return "Scroll_onDidScroll"
        case PeerEventKind.Scroll_onScrollEdge: return "Scroll_onScrollEdge"
        case PeerEventKind.Scroll_onScrollStart: return "Scroll_onScrollStart"
        case PeerEventKind.Scroll_onScrollEnd: return "Scroll_onScrollEnd"
        case PeerEventKind.Scroll_onScrollStop: return "Scroll_onScrollStop"
        case PeerEventKind.Scroll_onScrollFrameBegin: return "Scroll_onScrollFrameBegin"
        case PeerEventKind.Search_onEditChange: return "Search_onEditChange"
        case PeerEventKind.Search_onSubmit0: return "Search_onSubmit0"
        case PeerEventKind.Search_onSubmit1: return "Search_onSubmit1"
        case PeerEventKind.Search_onChange: return "Search_onChange"
        case PeerEventKind.Search_onTextSelectionChange: return "Search_onTextSelectionChange"
        case PeerEventKind.Search_onContentScroll: return "Search_onContentScroll"
        case PeerEventKind.Search_onCopy: return "Search_onCopy"
        case PeerEventKind.Search_onCut: return "Search_onCut"
        case PeerEventKind.Search_onPaste: return "Search_onPaste"
        case PeerEventKind.Search_onWillInsert: return "Search_onWillInsert"
        case PeerEventKind.Search_onDidInsert: return "Search_onDidInsert"
        case PeerEventKind.Search_onWillDelete: return "Search_onWillDelete"
        case PeerEventKind.Search_onDidDelete: return "Search_onDidDelete"
        case PeerEventKind.Search_customKeyboard: return "Search_customKeyboard"
        case PeerEventKind.Search__onChangeEvent_value: return "Search__onChangeEvent_value"
        case PeerEventKind.Select_onSelect: return "Select_onSelect"
        case PeerEventKind.Select__onChangeEvent_selected: return "Select__onChangeEvent_selected"
        case PeerEventKind.Select__onChangeEvent_value: return "Select__onChangeEvent_value"
        case PeerEventKind.Slider_onChange: return "Slider_onChange"
        case PeerEventKind.Slider__onChangeEvent_value: return "Slider__onChangeEvent_value"
        case PeerEventKind.Stepper_onFinish: return "Stepper_onFinish"
        case PeerEventKind.Stepper_onSkip: return "Stepper_onSkip"
        case PeerEventKind.Stepper_onChange: return "Stepper_onChange"
        case PeerEventKind.Stepper_onNext: return "Stepper_onNext"
        case PeerEventKind.Stepper_onPrevious: return "Stepper_onPrevious"
        case PeerEventKind.Stepper__onChangeEvent_index: return "Stepper__onChangeEvent_index"
        case PeerEventKind.Swiper_onChange: return "Swiper_onChange"
        case PeerEventKind.Swiper_onAnimationStart: return "Swiper_onAnimationStart"
        case PeerEventKind.Swiper_onAnimationEnd: return "Swiper_onAnimationEnd"
        case PeerEventKind.Swiper_onGestureSwipe: return "Swiper_onGestureSwipe"
        case PeerEventKind.Swiper_onContentDidScroll: return "Swiper_onContentDidScroll"
        case PeerEventKind.Swiper__onChangeEvent_index: return "Swiper__onChangeEvent_index"
        case PeerEventKind.IndicatorComponent_onChange: return "IndicatorComponent_onChange"
        case PeerEventKind.Tabs_onChange: return "Tabs_onChange"
        case PeerEventKind.Tabs_onTabBarClick: return "Tabs_onTabBarClick"
        case PeerEventKind.Tabs_onAnimationStart: return "Tabs_onAnimationStart"
        case PeerEventKind.Tabs_onAnimationEnd: return "Tabs_onAnimationEnd"
        case PeerEventKind.Tabs_onGestureSwipe: return "Tabs_onGestureSwipe"
        case PeerEventKind.Tabs_customContentTransition: return "Tabs_customContentTransition"
        case PeerEventKind.Tabs_onContentWillChange: return "Tabs_onContentWillChange"
        case PeerEventKind.Tabs__onChangeEvent_index: return "Tabs__onChangeEvent_index"
        case PeerEventKind.TabContent_onWillShow: return "TabContent_onWillShow"
        case PeerEventKind.TabContent_onWillHide: return "TabContent_onWillHide"
        case PeerEventKind.Text_onCopy: return "Text_onCopy"
        case PeerEventKind.Text_onTextSelectionChange: return "Text_onTextSelectionChange"
        case PeerEventKind.Text_bindSelectionMenu: return "Text_bindSelectionMenu"
        case PeerEventKind.TextArea_onSubmit0: return "TextArea_onSubmit0"
        case PeerEventKind.TextArea_onSubmit1: return "TextArea_onSubmit1"
        case PeerEventKind.TextArea_onChange: return "TextArea_onChange"
        case PeerEventKind.TextArea_onTextSelectionChange: return "TextArea_onTextSelectionChange"
        case PeerEventKind.TextArea_onContentScroll: return "TextArea_onContentScroll"
        case PeerEventKind.TextArea_onEditChange: return "TextArea_onEditChange"
        case PeerEventKind.TextArea_onCopy: return "TextArea_onCopy"
        case PeerEventKind.TextArea_onCut: return "TextArea_onCut"
        case PeerEventKind.TextArea_onPaste: return "TextArea_onPaste"
        case PeerEventKind.TextArea_onWillInsert: return "TextArea_onWillInsert"
        case PeerEventKind.TextArea_onDidInsert: return "TextArea_onDidInsert"
        case PeerEventKind.TextArea_onWillDelete: return "TextArea_onWillDelete"
        case PeerEventKind.TextArea_onDidDelete: return "TextArea_onDidDelete"
        case PeerEventKind.TextArea_customKeyboard: return "TextArea_customKeyboard"
        case PeerEventKind.TextArea__onChangeEvent_text: return "TextArea__onChangeEvent_text"
        case PeerEventKind.TextClock_onDateChange: return "TextClock_onDateChange"
        case PeerEventKind.TextInput_onEditChanged: return "TextInput_onEditChanged"
        case PeerEventKind.TextInput_onEditChange: return "TextInput_onEditChange"
        case PeerEventKind.TextInput_onSubmit: return "TextInput_onSubmit"
        case PeerEventKind.TextInput_onChange: return "TextInput_onChange"
        case PeerEventKind.TextInput_onTextSelectionChange: return "TextInput_onTextSelectionChange"
        case PeerEventKind.TextInput_onContentScroll: return "TextInput_onContentScroll"
        case PeerEventKind.TextInput_onCopy: return "TextInput_onCopy"
        case PeerEventKind.TextInput_onCut: return "TextInput_onCut"
        case PeerEventKind.TextInput_onPaste: return "TextInput_onPaste"
        case PeerEventKind.TextInput_showUnit: return "TextInput_showUnit"
        case PeerEventKind.TextInput_onSecurityStateChange: return "TextInput_onSecurityStateChange"
        case PeerEventKind.TextInput_onWillInsert: return "TextInput_onWillInsert"
        case PeerEventKind.TextInput_onDidInsert: return "TextInput_onDidInsert"
        case PeerEventKind.TextInput_onWillDelete: return "TextInput_onWillDelete"
        case PeerEventKind.TextInput_onDidDelete: return "TextInput_onDidDelete"
        case PeerEventKind.TextInput_customKeyboard: return "TextInput_customKeyboard"
        case PeerEventKind.TextInput__onChangeEvent_text: return "TextInput__onChangeEvent_text"
        case PeerEventKind.TextPicker_onAccept: return "TextPicker_onAccept"
        case PeerEventKind.TextPicker_onCancel: return "TextPicker_onCancel"
        case PeerEventKind.TextPicker_onChange: return "TextPicker_onChange"
        case PeerEventKind.TextPicker__onChangeEvent_selected: return "TextPicker__onChangeEvent_selected"
        case PeerEventKind.TextPicker__onChangeEvent_value: return "TextPicker__onChangeEvent_value"
        case PeerEventKind.TextTimer_onTimer: return "TextTimer_onTimer"
        case PeerEventKind.TimePicker_onChange: return "TimePicker_onChange"
        case PeerEventKind.TimePicker__onChangeEvent_selected: return "TimePicker__onChangeEvent_selected"
        case PeerEventKind.Toggle_onChange: return "Toggle_onChange"
        case PeerEventKind.Toggle__onChangeEvent_isOn: return "Toggle__onChangeEvent_isOn"
        case PeerEventKind.Video_onStart: return "Video_onStart"
        case PeerEventKind.Video_onPause: return "Video_onPause"
        case PeerEventKind.Video_onFinish: return "Video_onFinish"
        case PeerEventKind.Video_onFullscreenChange: return "Video_onFullscreenChange"
        case PeerEventKind.Video_onPrepared: return "Video_onPrepared"
        case PeerEventKind.Video_onSeeking: return "Video_onSeeking"
        case PeerEventKind.Video_onSeeked: return "Video_onSeeked"
        case PeerEventKind.Video_onUpdate: return "Video_onUpdate"
        case PeerEventKind.Video_onError: return "Video_onError"
        case PeerEventKind.Video_onStop: return "Video_onStop"
        case PeerEventKind.Web_onPageEnd: return "Web_onPageEnd"
        case PeerEventKind.Web_onPageBegin: return "Web_onPageBegin"
        case PeerEventKind.Web_onProgressChange: return "Web_onProgressChange"
        case PeerEventKind.Web_onTitleReceive: return "Web_onTitleReceive"
        case PeerEventKind.Web_onGeolocationHide: return "Web_onGeolocationHide"
        case PeerEventKind.Web_onGeolocationShow: return "Web_onGeolocationShow"
        case PeerEventKind.Web_onRequestSelected: return "Web_onRequestSelected"
        case PeerEventKind.Web_onAlert: return "Web_onAlert"
        case PeerEventKind.Web_onBeforeUnload: return "Web_onBeforeUnload"
        case PeerEventKind.Web_onConfirm: return "Web_onConfirm"
        case PeerEventKind.Web_onPrompt: return "Web_onPrompt"
        case PeerEventKind.Web_onConsole: return "Web_onConsole"
        case PeerEventKind.Web_onErrorReceive: return "Web_onErrorReceive"
        case PeerEventKind.Web_onHttpErrorReceive: return "Web_onHttpErrorReceive"
        case PeerEventKind.Web_onDownloadStart: return "Web_onDownloadStart"
        case PeerEventKind.Web_onRefreshAccessedHistory: return "Web_onRefreshAccessedHistory"
        case PeerEventKind.Web_onUrlLoadIntercept: return "Web_onUrlLoadIntercept"
        case PeerEventKind.Web_onSslErrorReceive: return "Web_onSslErrorReceive"
        case PeerEventKind.Web_onRenderExited0: return "Web_onRenderExited0"
        case PeerEventKind.Web_onRenderExited1: return "Web_onRenderExited1"
        case PeerEventKind.Web_onShowFileSelector: return "Web_onShowFileSelector"
        case PeerEventKind.Web_onFileSelectorShow: return "Web_onFileSelectorShow"
        case PeerEventKind.Web_onResourceLoad: return "Web_onResourceLoad"
        case PeerEventKind.Web_onFullScreenExit: return "Web_onFullScreenExit"
        case PeerEventKind.Web_onFullScreenEnter: return "Web_onFullScreenEnter"
        case PeerEventKind.Web_onScaleChange: return "Web_onScaleChange"
        case PeerEventKind.Web_onHttpAuthRequest: return "Web_onHttpAuthRequest"
        case PeerEventKind.Web_onInterceptRequest: return "Web_onInterceptRequest"
        case PeerEventKind.Web_onPermissionRequest: return "Web_onPermissionRequest"
        case PeerEventKind.Web_onScreenCaptureRequest: return "Web_onScreenCaptureRequest"
        case PeerEventKind.Web_onContextMenuShow: return "Web_onContextMenuShow"
        case PeerEventKind.Web_onContextMenuHide: return "Web_onContextMenuHide"
        case PeerEventKind.Web_onSearchResultReceive: return "Web_onSearchResultReceive"
        case PeerEventKind.Web_onScroll: return "Web_onScroll"
        case PeerEventKind.Web_onSslErrorEventReceive: return "Web_onSslErrorEventReceive"
        case PeerEventKind.Web_onSslErrorEvent: return "Web_onSslErrorEvent"
        case PeerEventKind.Web_onClientAuthenticationRequest: return "Web_onClientAuthenticationRequest"
        case PeerEventKind.Web_onWindowNew: return "Web_onWindowNew"
        case PeerEventKind.Web_onWindowExit: return "Web_onWindowExit"
        case PeerEventKind.Web_onInterceptKeyEvent: return "Web_onInterceptKeyEvent"
        case PeerEventKind.Web_onTouchIconUrlReceived: return "Web_onTouchIconUrlReceived"
        case PeerEventKind.Web_onFaviconReceived: return "Web_onFaviconReceived"
        case PeerEventKind.Web_onPageVisible: return "Web_onPageVisible"
        case PeerEventKind.Web_onDataResubmitted: return "Web_onDataResubmitted"
        case PeerEventKind.Web_onAudioStateChanged: return "Web_onAudioStateChanged"
        case PeerEventKind.Web_onFirstContentfulPaint: return "Web_onFirstContentfulPaint"
        case PeerEventKind.Web_onFirstMeaningfulPaint: return "Web_onFirstMeaningfulPaint"
        case PeerEventKind.Web_onLargestContentfulPaint: return "Web_onLargestContentfulPaint"
        case PeerEventKind.Web_onLoadIntercept: return "Web_onLoadIntercept"
        case PeerEventKind.Web_onControllerAttached: return "Web_onControllerAttached"
        case PeerEventKind.Web_onOverScroll: return "Web_onOverScroll"
        case PeerEventKind.Web_onSafeBrowsingCheckResult: return "Web_onSafeBrowsingCheckResult"
        case PeerEventKind.Web_onNavigationEntryCommitted: return "Web_onNavigationEntryCommitted"
        case PeerEventKind.Web_onIntelligentTrackingPreventionResult: return "Web_onIntelligentTrackingPreventionResult"
        case PeerEventKind.Web_onNativeEmbedLifecycleChange: return "Web_onNativeEmbedLifecycleChange"
        case PeerEventKind.Web_onNativeEmbedVisibilityChange: return "Web_onNativeEmbedVisibilityChange"
        case PeerEventKind.Web_onNativeEmbedGestureEvent: return "Web_onNativeEmbedGestureEvent"
        case PeerEventKind.Web_onOverrideUrlLoading: return "Web_onOverrideUrlLoading"
        case PeerEventKind.Web_onRenderProcessNotResponding: return "Web_onRenderProcessNotResponding"
        case PeerEventKind.Web_onRenderProcessResponding: return "Web_onRenderProcessResponding"
        case PeerEventKind.Web_onViewportFitChanged: return "Web_onViewportFitChanged"
        case PeerEventKind.Web_onInterceptKeyboardAttach: return "Web_onInterceptKeyboardAttach"
        case PeerEventKind.Web_onAdsBlocked: return "Web_onAdsBlocked"
        case PeerEventKind.Web_bindSelectionMenu: return "Web_bindSelectionMenu"
        case PeerEventKind.XComponent_onLoad: return "XComponent_onLoad"
        case PeerEventKind.XComponent_onDestroy: return "XComponent_onDestroy"
        case PeerEventKind.SideBarContainer_onChange: return "SideBarContainer_onChange"
        case PeerEventKind.SideBarContainer__onChangeEvent_showSideBar: return "SideBarContainer__onChangeEvent_showSideBar"
        case PeerEventKind.WaterFlow_onReachStart: return "WaterFlow_onReachStart"
        case PeerEventKind.WaterFlow_onReachEnd: return "WaterFlow_onReachEnd"
        case PeerEventKind.WaterFlow_onScrollFrameBegin: return "WaterFlow_onScrollFrameBegin"
        case PeerEventKind.WaterFlow_onScrollIndex: return "WaterFlow_onScrollIndex"
        case PeerEventKind.UIExtensionComponent_onRemoteReady: return "UIExtensionComponent_onRemoteReady"
        case PeerEventKind.UIExtensionComponent_onResult: return "UIExtensionComponent_onResult"
        case PeerEventKind.UIExtensionComponent_onRelease: return "UIExtensionComponent_onRelease"
        case PeerEventKind.UIExtensionComponent_onError: return "UIExtensionComponent_onError"
        case PeerEventKind.UIExtensionComponent_onTerminated: return "UIExtensionComponent_onTerminated"
        default: throw new Error(`Unknown kind ${kind}`)
    }
}
export function deserializePeerEvent(eventDeserializer: Deserializer): PeerEvent {
    const kind: PeerEventKind = eventDeserializer.readInt32()
    const nodeId: number = eventDeserializer.readInt32()
    if ((kind) === (PeerEventKind.AbilityComponent_onConnect)) {
        const event: { kind?: number, nodeId?: PeerEventKind } = {}
        event.kind = kind
        event.nodeId = nodeId
        return (event as AbilityComponent_onConnect_event)
    }
    else if ((kind) === (PeerEventKind.AbilityComponent_onDisconnect)) {
        const event: { kind?: number, nodeId?: PeerEventKind } = {}
        event.kind = kind
        event.nodeId = nodeId
        return (event as AbilityComponent_onDisconnect_event)
    }
    else if ((kind) === (PeerEventKind.AlphabetIndexer_onSelected)) {
        const event: { kind?: number, nodeId?: PeerEventKind, index?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.index = (eventDeserializer.readNumber() as number)
        return (event as AlphabetIndexer_onSelected_event)
    }
    else if ((kind) === (PeerEventKind.AlphabetIndexer_onSelect)) {
        const event: { kind?: number, nodeId?: PeerEventKind, index?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.index = (eventDeserializer.readNumber() as number)
        return (event as AlphabetIndexer_onSelect_event)
    }
    else if ((kind) === (PeerEventKind.AlphabetIndexer_onRequestPopupData)) {
        const event: { kind?: number, nodeId?: PeerEventKind, index?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.index = (eventDeserializer.readNumber() as number)
        return (event as AlphabetIndexer_onRequestPopupData_event)
    }
    else if ((kind) === (PeerEventKind.AlphabetIndexer_onPopupSelect)) {
        const event: { kind?: number, nodeId?: PeerEventKind, index?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.index = (eventDeserializer.readNumber() as number)
        return (event as AlphabetIndexer_onPopupSelect_event)
    }
    else if ((kind) === (PeerEventKind.AlphabetIndexer__onChangeEvent_selected)) {
        const event: { kind?: number, nodeId?: PeerEventKind, index?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.index = (eventDeserializer.readNumber() as number)
        return (event as AlphabetIndexer__onChangeEvent_selected_event)
    }
    else if ((kind) === (PeerEventKind.Animator_onStart)) {
        const event: { kind?: number, nodeId?: PeerEventKind } = {}
        event.kind = kind
        event.nodeId = nodeId
        return (event as Animator_onStart_event)
    }
    else if ((kind) === (PeerEventKind.Animator_onPause)) {
        const event: { kind?: number, nodeId?: PeerEventKind } = {}
        event.kind = kind
        event.nodeId = nodeId
        return (event as Animator_onPause_event)
    }
    else if ((kind) === (PeerEventKind.Animator_onRepeat)) {
        const event: { kind?: number, nodeId?: PeerEventKind } = {}
        event.kind = kind
        event.nodeId = nodeId
        return (event as Animator_onRepeat_event)
    }
    else if ((kind) === (PeerEventKind.Animator_onCancel)) {
        const event: { kind?: number, nodeId?: PeerEventKind } = {}
        event.kind = kind
        event.nodeId = nodeId
        return (event as Animator_onCancel_event)
    }
    else if ((kind) === (PeerEventKind.Animator_onFinish)) {
        const event: { kind?: number, nodeId?: PeerEventKind } = {}
        event.kind = kind
        event.nodeId = nodeId
        return (event as Animator_onFinish_event)
    }
    else if ((kind) === (PeerEventKind.Animator_onFrame)) {
        const event: { kind?: number, nodeId?: PeerEventKind, index?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.index = (eventDeserializer.readNumber() as number)
        return (event as Animator_onFrame_event)
    }
    else if ((kind) === (PeerEventKind.Calendar_onSelectChange)) {
        const event: { kind?: number, nodeId?: PeerEventKind, event?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.event = eventDeserializer.readCalendarSelectedDate()
        return (event as Calendar_onSelectChange_event)
    }
    else if ((kind) === (PeerEventKind.Calendar_onRequestData)) {
        const event: { kind?: number, nodeId?: PeerEventKind, event?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.event = eventDeserializer.readCalendarRequestedData()
        return (event as Calendar_onRequestData_event)
    }
    else if ((kind) === (PeerEventKind.CalendarPicker_onChange)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = new Date(eventDeserializer.readInt64())
        return (event as CalendarPicker_onChange_event)
    }
    else if ((kind) === (PeerEventKind.Canvas_onReady)) {
        const event: { kind?: number, nodeId?: PeerEventKind } = {}
        event.kind = kind
        event.nodeId = nodeId
        return (event as Canvas_onReady_event)
    }
    else if ((kind) === (PeerEventKind.Checkbox_onChange)) {
        const event: { kind?: number, nodeId?: PeerEventKind, value?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.value = eventDeserializer.readBoolean()
        return (event as Checkbox_onChange_event)
    }
    else if ((kind) === (PeerEventKind.Checkbox__onChangeEvent_select)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = eventDeserializer.readBoolean()
        return (event as Checkbox__onChangeEvent_select_event)
    }
    else if ((kind) === (PeerEventKind.CheckboxGroup_onChange)) {
        const event: { kind?: number, nodeId?: PeerEventKind, value?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.value = eventDeserializer.readCheckboxGroupResult()
        return (event as CheckboxGroup_onChange_event)
    }
    else if ((kind) === (PeerEventKind.CheckboxGroup__onChangeEvent_selectAll)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = eventDeserializer.readBoolean()
        return (event as CheckboxGroup__onChangeEvent_selectAll_event)
    }
    else if ((kind) === (PeerEventKind.CommonMethod_onChildTouchTest)) {
        const event: { kind?: number, nodeId?: PeerEventKind, value?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        const value_buf_length: int32 = eventDeserializer.readInt32()
        let value_buf: Array<TouchTestInfo> = new Array<TouchTestInfo>()
        for (let value_buf_i = 0; value_buf_i < value_buf_length; value_buf_i++) {
            value_buf[value_buf_i] = eventDeserializer.readTouchTestInfo()
        }
        event.value = value_buf
        return (event as CommonMethod_onChildTouchTest_event)
    }
    else if ((kind) === (PeerEventKind.CommonMethod_onClick0)) {
        const event: { kind?: number, nodeId?: PeerEventKind, event?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.event = (eventDeserializer.readClickEvent() as ClickEvent)
        return (event as CommonMethod_onClick0_event)
    }
    else if ((kind) === (PeerEventKind.CommonMethod_onClick1)) {
        const event: { kind?: number, nodeId?: PeerEventKind, event?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.event = (eventDeserializer.readClickEvent() as ClickEvent)
        return (event as CommonMethod_onClick1_event)
    }
    else if ((kind) === (PeerEventKind.CommonMethod_onHover)) {
        const event: { kind?: number, nodeId?: PeerEventKind, isHover?: any, event?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.isHover = eventDeserializer.readBoolean()
        event.event = (eventDeserializer.readHoverEvent() as HoverEvent)
        return (event as CommonMethod_onHover_event)
    }
    else if ((kind) === (PeerEventKind.CommonMethod_onAccessibilityHover)) {
        const event: { kind?: number, nodeId?: PeerEventKind, isHover?: any, event?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.isHover = eventDeserializer.readBoolean()
        event.event = (eventDeserializer.readAccessibilityHoverEvent() as AccessibilityHoverEvent)
        return (event as CommonMethod_onAccessibilityHover_event)
    }
    else if ((kind) === (PeerEventKind.CommonMethod_onMouse)) {
        const event: { kind?: number, nodeId?: PeerEventKind, event?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.event = (eventDeserializer.readMouseEvent() as MouseEvent)
        return (event as CommonMethod_onMouse_event)
    }
    else if ((kind) === (PeerEventKind.CommonMethod_onTouch)) {
        const event: { kind?: number, nodeId?: PeerEventKind, event?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.event = (eventDeserializer.readTouchEvent() as TouchEvent)
        return (event as CommonMethod_onTouch_event)
    }
    else if ((kind) === (PeerEventKind.CommonMethod_onKeyEvent)) {
        const event: { kind?: number, nodeId?: PeerEventKind, event?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.event = (eventDeserializer.readKeyEvent() as KeyEvent)
        return (event as CommonMethod_onKeyEvent_event)
    }
    else if ((kind) === (PeerEventKind.CommonMethod_onKeyPreIme)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = (eventDeserializer.readKeyEvent() as KeyEvent)
        return (event as CommonMethod_onKeyPreIme_event)
    }
    else if ((kind) === (PeerEventKind.CommonMethod_onFocus)) {
        const event: { kind?: number, nodeId?: PeerEventKind } = {}
        event.kind = kind
        event.nodeId = nodeId
        return (event as CommonMethod_onFocus_event)
    }
    else if ((kind) === (PeerEventKind.CommonMethod_onBlur)) {
        const event: { kind?: number, nodeId?: PeerEventKind } = {}
        event.kind = kind
        event.nodeId = nodeId
        return (event as CommonMethod_onBlur_event)
    }
    else if ((kind) === (PeerEventKind.CommonMethod_onAppear)) {
        const event: { kind?: number, nodeId?: PeerEventKind } = {}
        event.kind = kind
        event.nodeId = nodeId
        return (event as CommonMethod_onAppear_event)
    }
    else if ((kind) === (PeerEventKind.CommonMethod_onDisAppear)) {
        const event: { kind?: number, nodeId?: PeerEventKind } = {}
        event.kind = kind
        event.nodeId = nodeId
        return (event as CommonMethod_onDisAppear_event)
    }
    else if ((kind) === (PeerEventKind.CommonMethod_onAttach)) {
        const event: { kind?: number, nodeId?: PeerEventKind } = {}
        event.kind = kind
        event.nodeId = nodeId
        return (event as CommonMethod_onAttach_event)
    }
    else if ((kind) === (PeerEventKind.CommonMethod_onDetach)) {
        const event: { kind?: number, nodeId?: PeerEventKind } = {}
        event.kind = kind
        event.nodeId = nodeId
        return (event as CommonMethod_onDetach_event)
    }
    else if ((kind) === (PeerEventKind.CommonMethod_onAreaChange)) {
        const event: { kind?: number, nodeId?: PeerEventKind, oldValue?: any, newValue?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.oldValue = eventDeserializer.readArea()
        event.newValue = eventDeserializer.readArea()
        return (event as CommonMethod_onAreaChange_event)
    }
    else if ((kind) === (PeerEventKind.CommonMethod_onDragStart)) {
        const event: { kind?: number, nodeId?: PeerEventKind, event?: any, extraParams?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.event = (eventDeserializer.readDragEvent() as DragEvent)
        const extraParams_buf_runtimeType = (eventDeserializer.readInt8() as int32)
        let extraParams_buf: string | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (extraParams_buf_runtimeType))
        {
            extraParams_buf = (eventDeserializer.readString() as string)
        }
        event.extraParams = extraParams_buf
        return (event as CommonMethod_onDragStart_event)
    }
    else if ((kind) === (PeerEventKind.CommonMethod_onDragEnter)) {
        const event: { kind?: number, nodeId?: PeerEventKind, event?: any, extraParams?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.event = (eventDeserializer.readDragEvent() as DragEvent)
        const extraParams_buf_runtimeType = (eventDeserializer.readInt8() as int32)
        let extraParams_buf: string | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (extraParams_buf_runtimeType))
        {
            extraParams_buf = (eventDeserializer.readString() as string)
        }
        event.extraParams = extraParams_buf
        return (event as CommonMethod_onDragEnter_event)
    }
    else if ((kind) === (PeerEventKind.CommonMethod_onDragMove)) {
        const event: { kind?: number, nodeId?: PeerEventKind, event?: any, extraParams?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.event = (eventDeserializer.readDragEvent() as DragEvent)
        const extraParams_buf_runtimeType = (eventDeserializer.readInt8() as int32)
        let extraParams_buf: string | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (extraParams_buf_runtimeType))
        {
            extraParams_buf = (eventDeserializer.readString() as string)
        }
        event.extraParams = extraParams_buf
        return (event as CommonMethod_onDragMove_event)
    }
    else if ((kind) === (PeerEventKind.CommonMethod_onDragLeave)) {
        const event: { kind?: number, nodeId?: PeerEventKind, event?: any, extraParams?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.event = (eventDeserializer.readDragEvent() as DragEvent)
        const extraParams_buf_runtimeType = (eventDeserializer.readInt8() as int32)
        let extraParams_buf: string | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (extraParams_buf_runtimeType))
        {
            extraParams_buf = (eventDeserializer.readString() as string)
        }
        event.extraParams = extraParams_buf
        return (event as CommonMethod_onDragLeave_event)
    }
    else if ((kind) === (PeerEventKind.CommonMethod_onDrop)) {
        const event: { kind?: number, nodeId?: PeerEventKind, event?: any, extraParams?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.event = (eventDeserializer.readDragEvent() as DragEvent)
        const extraParams_buf_runtimeType = (eventDeserializer.readInt8() as int32)
        let extraParams_buf: string | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (extraParams_buf_runtimeType))
        {
            extraParams_buf = (eventDeserializer.readString() as string)
        }
        event.extraParams = extraParams_buf
        return (event as CommonMethod_onDrop_event)
    }
    else if ((kind) === (PeerEventKind.CommonMethod_onDragEnd)) {
        const event: { kind?: number, nodeId?: PeerEventKind, event?: any, extraParams?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.event = (eventDeserializer.readDragEvent() as DragEvent)
        const extraParams_buf_runtimeType = (eventDeserializer.readInt8() as int32)
        let extraParams_buf: string | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (extraParams_buf_runtimeType))
        {
            extraParams_buf = (eventDeserializer.readString() as string)
        }
        event.extraParams = extraParams_buf
        return (event as CommonMethod_onDragEnd_event)
    }
    else if ((kind) === (PeerEventKind.CommonMethod_onPreDrag)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = (eventDeserializer.readInt32() as PreDragStatus)
        return (event as CommonMethod_onPreDrag_event)
    }
    else if ((kind) === (PeerEventKind.CommonMethod_accessibilityVirtualNode)) {
        const event: { kind?: number, nodeId?: PeerEventKind } = {}
        event.kind = kind
        event.nodeId = nodeId
        return (event as CommonMethod_accessibilityVirtualNode_event)
    }
    else if ((kind) === (PeerEventKind.CommonMethod_onGestureJudgeBegin)) {
        const event: { kind?: number, nodeId?: PeerEventKind, gestureInfo?: any, event?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.gestureInfo = eventDeserializer.readGestureInfo()
        event.event = (eventDeserializer.readBaseGestureEvent() as BaseGestureEvent)
        return (event as CommonMethod_onGestureJudgeBegin_event)
    }
    else if ((kind) === (PeerEventKind.CommonMethod_onGestureRecognizerJudgeBegin0)) {
        const event: { kind?: number, nodeId?: PeerEventKind, event?: any, current?: any, recognizers?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.event = (eventDeserializer.readBaseGestureEvent() as BaseGestureEvent)
        event.current = (eventDeserializer.readGestureRecognizer() as GestureRecognizer)
        const recognizers_buf_length: int32 = eventDeserializer.readInt32()
        let recognizers_buf: Array<GestureRecognizer> = new Array<GestureRecognizer>()
        for (let recognizers_buf_i = 0; recognizers_buf_i < recognizers_buf_length; recognizers_buf_i++) {
            recognizers_buf[recognizers_buf_i] = (eventDeserializer.readGestureRecognizer() as GestureRecognizer)
        }
        event.recognizers = recognizers_buf
        return (event as CommonMethod_onGestureRecognizerJudgeBegin0_event)
    }
    else if ((kind) === (PeerEventKind.CommonMethod_onGestureRecognizerJudgeBegin1)) {
        const event: { kind?: number, nodeId?: PeerEventKind, event?: any, current?: any, recognizers?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.event = (eventDeserializer.readBaseGestureEvent() as BaseGestureEvent)
        event.current = (eventDeserializer.readGestureRecognizer() as GestureRecognizer)
        const recognizers_buf_length: int32 = eventDeserializer.readInt32()
        let recognizers_buf: Array<GestureRecognizer> = new Array<GestureRecognizer>()
        for (let recognizers_buf_i = 0; recognizers_buf_i < recognizers_buf_length; recognizers_buf_i++) {
            recognizers_buf[recognizers_buf_i] = (eventDeserializer.readGestureRecognizer() as GestureRecognizer)
        }
        event.recognizers = recognizers_buf
        return (event as CommonMethod_onGestureRecognizerJudgeBegin1_event)
    }
    else if ((kind) === (PeerEventKind.CommonMethod_shouldBuiltInRecognizerParallelWith)) {
        const event: { kind?: number, nodeId?: PeerEventKind, current?: any, others?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.current = (eventDeserializer.readGestureRecognizer() as GestureRecognizer)
        const others_buf_length: int32 = eventDeserializer.readInt32()
        let others_buf: Array<GestureRecognizer> = new Array<GestureRecognizer>()
        for (let others_buf_i = 0; others_buf_i < others_buf_length; others_buf_i++) {
            others_buf[others_buf_i] = (eventDeserializer.readGestureRecognizer() as GestureRecognizer)
        }
        event.others = others_buf
        return (event as CommonMethod_shouldBuiltInRecognizerParallelWith_event)
    }
    else if ((kind) === (PeerEventKind.CommonMethod_onTouchIntercept)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = (eventDeserializer.readTouchEvent() as TouchEvent)
        return (event as CommonMethod_onTouchIntercept_event)
    }
    else if ((kind) === (PeerEventKind.CommonMethod_onSizeChange)) {
        const event: { kind?: number, nodeId?: PeerEventKind, oldValue?: any, newValue?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.oldValue = eventDeserializer.readSizeOptions()
        event.newValue = eventDeserializer.readSizeOptions()
        return (event as CommonMethod_onSizeChange_event)
    }
    else if ((kind) === (PeerEventKind.CommonMethod_background)) {
        const event: { kind?: number, nodeId?: PeerEventKind } = {}
        event.kind = kind
        event.nodeId = nodeId
        return (event as CommonMethod_background_event)
    }
    else if ((kind) === (PeerEventKind.CommonMethod_bindContextMenu0)) {
        const event: { kind?: number, nodeId?: PeerEventKind } = {}
        event.kind = kind
        event.nodeId = nodeId
        return (event as CommonMethod_bindContextMenu0_event)
    }
    else if ((kind) === (PeerEventKind.CommonMethod_bindContextMenu1)) {
        const event: { kind?: number, nodeId?: PeerEventKind } = {}
        event.kind = kind
        event.nodeId = nodeId
        return (event as CommonMethod_bindContextMenu1_event)
    }
    else if ((kind) === (PeerEventKind.CommonMethod_bindContentCover0)) {
        const event: { kind?: number, nodeId?: PeerEventKind } = {}
        event.kind = kind
        event.nodeId = nodeId
        return (event as CommonMethod_bindContentCover0_event)
    }
    else if ((kind) === (PeerEventKind.CommonMethod_bindContentCover1)) {
        const event: { kind?: number, nodeId?: PeerEventKind } = {}
        event.kind = kind
        event.nodeId = nodeId
        return (event as CommonMethod_bindContentCover1_event)
    }
    else if ((kind) === (PeerEventKind.CommonMethod_bindSheet)) {
        const event: { kind?: number, nodeId?: PeerEventKind } = {}
        event.kind = kind
        event.nodeId = nodeId
        return (event as CommonMethod_bindSheet_event)
    }
    else if ((kind) === (PeerEventKind.CommonMethod_onVisibleAreaChange)) {
        const event: { kind?: number, nodeId?: PeerEventKind, isExpanding?: any, currentRatio?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.isExpanding = eventDeserializer.readBoolean()
        event.currentRatio = (eventDeserializer.readNumber() as number)
        return (event as CommonMethod_onVisibleAreaChange_event)
    }
    else if ((kind) === (PeerEventKind.ScrollableCommonMethod_onScroll)) {
        const event: { kind?: number, nodeId?: PeerEventKind, first?: any, last?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.first = (eventDeserializer.readNumber() as number)
        event.last = (eventDeserializer.readNumber() as number)
        return (event as ScrollableCommonMethod_onScroll_event)
    }
    else if ((kind) === (PeerEventKind.ScrollableCommonMethod_onDidScroll)) {
        const event: { kind?: number, nodeId?: PeerEventKind, xOffset?: any, yOffset?: any, scrollState?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.xOffset = (eventDeserializer.readNumber() as number)
        event.yOffset = (eventDeserializer.readNumber() as number)
        event.scrollState = (eventDeserializer.readInt32() as ScrollState)
        return (event as ScrollableCommonMethod_onDidScroll_event)
    }
    else if ((kind) === (PeerEventKind.ScrollableCommonMethod_onReachStart)) {
        const event: { kind?: number, nodeId?: PeerEventKind } = {}
        event.kind = kind
        event.nodeId = nodeId
        return (event as ScrollableCommonMethod_onReachStart_event)
    }
    else if ((kind) === (PeerEventKind.ScrollableCommonMethod_onReachEnd)) {
        const event: { kind?: number, nodeId?: PeerEventKind } = {}
        event.kind = kind
        event.nodeId = nodeId
        return (event as ScrollableCommonMethod_onReachEnd_event)
    }
    else if ((kind) === (PeerEventKind.ScrollableCommonMethod_onScrollStart)) {
        const event: { kind?: number, nodeId?: PeerEventKind } = {}
        event.kind = kind
        event.nodeId = nodeId
        return (event as ScrollableCommonMethod_onScrollStart_event)
    }
    else if ((kind) === (PeerEventKind.ScrollableCommonMethod_onScrollStop)) {
        const event: { kind?: number, nodeId?: PeerEventKind } = {}
        event.kind = kind
        event.nodeId = nodeId
        return (event as ScrollableCommonMethod_onScrollStop_event)
    }
    else if ((kind) === (PeerEventKind.Counter_onInc)) {
        const event: { kind?: number, nodeId?: PeerEventKind } = {}
        event.kind = kind
        event.nodeId = nodeId
        return (event as Counter_onInc_event)
    }
    else if ((kind) === (PeerEventKind.Counter_onDec)) {
        const event: { kind?: number, nodeId?: PeerEventKind } = {}
        event.kind = kind
        event.nodeId = nodeId
        return (event as Counter_onDec_event)
    }
    else if ((kind) === (PeerEventKind.DatePicker_onChange)) {
        const event: { kind?: number, nodeId?: PeerEventKind, value?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.value = eventDeserializer.readDatePickerResult()
        return (event as DatePicker_onChange_event)
    }
    else if ((kind) === (PeerEventKind.DatePicker_onDateChange)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = new Date(eventDeserializer.readInt64())
        return (event as DatePicker_onDateChange_event)
    }
    else if ((kind) === (PeerEventKind.DatePicker__onChangeEvent_selected)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = new Date(eventDeserializer.readInt64())
        return (event as DatePicker__onChangeEvent_selected_event)
    }
    else if ((kind) === (PeerEventKind.EmbeddedComponent_onTerminated)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = eventDeserializer.readTerminationInfo()
        return (event as EmbeddedComponent_onTerminated_event)
    }
    else if ((kind) === (PeerEventKind.EmbeddedComponent_onError)) {
        const event: { kind?: number, nodeId?: PeerEventKind, err?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.err = eventDeserializer.readBusinessError()
        return (event as EmbeddedComponent_onError_event)
    }
    else if ((kind) === (PeerEventKind.FolderStack_onFolderStateChange)) {
        const event: { kind?: number, nodeId?: PeerEventKind, event?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.event = eventDeserializer.readOnFoldStatusChangeInfo()
        return (event as FolderStack_onFolderStateChange_event)
    }
    else if ((kind) === (PeerEventKind.FolderStack_onHoverStatusChange)) {
        const event: { kind?: number, nodeId?: PeerEventKind, param?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.param = eventDeserializer.readHoverEventParam()
        return (event as FolderStack_onHoverStatusChange_event)
    }
    else if ((kind) === (PeerEventKind.FormComponent_onAcquired)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = eventDeserializer.readFormCallbackInfo()
        return (event as FormComponent_onAcquired_event)
    }
    else if ((kind) === (PeerEventKind.FormComponent_onError)) {
        const event: { kind?: number, nodeId?: PeerEventKind, info?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        const info_buf_errcode: number = (eventDeserializer.readNumber() as number)
        const info_buf_msg: string = (eventDeserializer.readString() as string)
        event.info = ({errcode: info_buf_errcode, msg: info_buf_msg} as { errcode: number, msg: string })
        return (event as FormComponent_onError_event)
    }
    else if ((kind) === (PeerEventKind.FormComponent_onRouter)) {
        const event: { kind?: number, nodeId?: PeerEventKind, info?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.info = (eventDeserializer.readCustomObject("Any") as Object)
        return (event as FormComponent_onRouter_event)
    }
    else if ((kind) === (PeerEventKind.FormComponent_onUninstall)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = eventDeserializer.readFormCallbackInfo()
        return (event as FormComponent_onUninstall_event)
    }
    else if ((kind) === (PeerEventKind.FormComponent_onLoad)) {
        const event: { kind?: number, nodeId?: PeerEventKind } = {}
        event.kind = kind
        event.nodeId = nodeId
        return (event as FormComponent_onLoad_event)
    }
    else if ((kind) === (PeerEventKind.Gauge_description)) {
        const event: { kind?: number, nodeId?: PeerEventKind } = {}
        event.kind = kind
        event.nodeId = nodeId
        return (event as Gauge_description_event)
    }
    else if ((kind) === (PeerEventKind.Grid_onScrollBarUpdate)) {
        const event: { kind?: number, nodeId?: PeerEventKind, index?: any, offset?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.index = (eventDeserializer.readNumber() as number)
        event.offset = (eventDeserializer.readNumber() as number)
        return (event as Grid_onScrollBarUpdate_event)
    }
    else if ((kind) === (PeerEventKind.Grid_onScrollIndex)) {
        const event: { kind?: number, nodeId?: PeerEventKind, first?: any, last?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.first = (eventDeserializer.readNumber() as number)
        event.last = (eventDeserializer.readNumber() as number)
        return (event as Grid_onScrollIndex_event)
    }
    else if ((kind) === (PeerEventKind.Grid_onItemDragStart)) {
        const event: { kind?: number, nodeId?: PeerEventKind, event?: any, itemIndex?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.event = eventDeserializer.readItemDragInfo()
        event.itemIndex = (eventDeserializer.readNumber() as number)
        return (event as Grid_onItemDragStart_event)
    }
    else if ((kind) === (PeerEventKind.Grid_onItemDragEnter)) {
        const event: { kind?: number, nodeId?: PeerEventKind, event?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.event = eventDeserializer.readItemDragInfo()
        return (event as Grid_onItemDragEnter_event)
    }
    else if ((kind) === (PeerEventKind.Grid_onItemDragMove)) {
        const event: { kind?: number, nodeId?: PeerEventKind, event?: any, itemIndex?: any, insertIndex?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.event = eventDeserializer.readItemDragInfo()
        event.itemIndex = (eventDeserializer.readNumber() as number)
        event.insertIndex = (eventDeserializer.readNumber() as number)
        return (event as Grid_onItemDragMove_event)
    }
    else if ((kind) === (PeerEventKind.Grid_onItemDragLeave)) {
        const event: { kind?: number, nodeId?: PeerEventKind, event?: any, itemIndex?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.event = eventDeserializer.readItemDragInfo()
        event.itemIndex = (eventDeserializer.readNumber() as number)
        return (event as Grid_onItemDragLeave_event)
    }
    else if ((kind) === (PeerEventKind.Grid_onItemDrop)) {
        const event: { kind?: number, nodeId?: PeerEventKind, event?: any, itemIndex?: any, insertIndex?: any, isSuccess?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.event = eventDeserializer.readItemDragInfo()
        event.itemIndex = (eventDeserializer.readNumber() as number)
        event.insertIndex = (eventDeserializer.readNumber() as number)
        event.isSuccess = eventDeserializer.readBoolean()
        return (event as Grid_onItemDrop_event)
    }
    else if ((kind) === (PeerEventKind.Grid_onScroll)) {
        const event: { kind?: number, nodeId?: PeerEventKind, first?: any, last?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.first = (eventDeserializer.readNumber() as number)
        event.last = (eventDeserializer.readNumber() as number)
        return (event as Grid_onScroll_event)
    }
    else if ((kind) === (PeerEventKind.Grid_onReachStart)) {
        const event: { kind?: number, nodeId?: PeerEventKind } = {}
        event.kind = kind
        event.nodeId = nodeId
        return (event as Grid_onReachStart_event)
    }
    else if ((kind) === (PeerEventKind.Grid_onReachEnd)) {
        const event: { kind?: number, nodeId?: PeerEventKind } = {}
        event.kind = kind
        event.nodeId = nodeId
        return (event as Grid_onReachEnd_event)
    }
    else if ((kind) === (PeerEventKind.Grid_onScrollStart)) {
        const event: { kind?: number, nodeId?: PeerEventKind } = {}
        event.kind = kind
        event.nodeId = nodeId
        return (event as Grid_onScrollStart_event)
    }
    else if ((kind) === (PeerEventKind.Grid_onScrollStop)) {
        const event: { kind?: number, nodeId?: PeerEventKind } = {}
        event.kind = kind
        event.nodeId = nodeId
        return (event as Grid_onScrollStop_event)
    }
    else if ((kind) === (PeerEventKind.Grid_onScrollFrameBegin)) {
        const event: { kind?: number, nodeId?: PeerEventKind, offset?: any, state?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.offset = (eventDeserializer.readNumber() as number)
        event.state = (eventDeserializer.readInt32() as ScrollState)
        return (event as Grid_onScrollFrameBegin_event)
    }
    else if ((kind) === (PeerEventKind.GridItem_onSelect)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = eventDeserializer.readBoolean()
        return (event as GridItem_onSelect_event)
    }
    else if ((kind) === (PeerEventKind.GridItem__onChangeEvent_selected)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = eventDeserializer.readBoolean()
        return (event as GridItem__onChangeEvent_selected_event)
    }
    else if ((kind) === (PeerEventKind.GridRow_onBreakpointChange)) {
        const event: { kind?: number, nodeId?: PeerEventKind, breakpoints?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.breakpoints = (eventDeserializer.readString() as string)
        return (event as GridRow_onBreakpointChange_event)
    }
    else if ((kind) === (PeerEventKind.Image_onComplete)) {
        const event: { kind?: number, nodeId?: PeerEventKind, event?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        const event_buf_runtimeType = (eventDeserializer.readInt8() as int32)
        let event_buf: { width: number, height: number, componentWidth: number, componentHeight: number, loadingStatus: number, contentWidth: number, contentHeight: number, contentOffsetX: number, contentOffsetY: number } | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (event_buf_runtimeType))
        {
            const event_buf__width: number = (eventDeserializer.readNumber() as number)
            const event_buf__height: number = (eventDeserializer.readNumber() as number)
            const event_buf__componentWidth: number = (eventDeserializer.readNumber() as number)
            const event_buf__componentHeight: number = (eventDeserializer.readNumber() as number)
            const event_buf__loadingStatus: number = (eventDeserializer.readNumber() as number)
            const event_buf__contentWidth: number = (eventDeserializer.readNumber() as number)
            const event_buf__contentHeight: number = (eventDeserializer.readNumber() as number)
            const event_buf__contentOffsetX: number = (eventDeserializer.readNumber() as number)
            const event_buf__contentOffsetY: number = (eventDeserializer.readNumber() as number)
            event_buf = ({width: event_buf__width, height: event_buf__height, componentWidth: event_buf__componentWidth, componentHeight: event_buf__componentHeight, loadingStatus: event_buf__loadingStatus, contentWidth: event_buf__contentWidth, contentHeight: event_buf__contentHeight, contentOffsetX: event_buf__contentOffsetX, contentOffsetY: event_buf__contentOffsetY} as { width: number, height: number, componentWidth: number, componentHeight: number, loadingStatus: number, contentWidth: number, contentHeight: number, contentOffsetX: number, contentOffsetY: number })
        }
        event.event = event_buf
        return (event as Image_onComplete_event)
    }
    else if ((kind) === (PeerEventKind.Image_onError)) {
        const event: { kind?: number, nodeId?: PeerEventKind, error?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.error = eventDeserializer.readImageError()
        return (event as Image_onError_event)
    }
    else if ((kind) === (PeerEventKind.Image_onFinish)) {
        const event: { kind?: number, nodeId?: PeerEventKind } = {}
        event.kind = kind
        event.nodeId = nodeId
        return (event as Image_onFinish_event)
    }
    else if ((kind) === (PeerEventKind.ImageAnimator_onStart)) {
        const event: { kind?: number, nodeId?: PeerEventKind } = {}
        event.kind = kind
        event.nodeId = nodeId
        return (event as ImageAnimator_onStart_event)
    }
    else if ((kind) === (PeerEventKind.ImageAnimator_onPause)) {
        const event: { kind?: number, nodeId?: PeerEventKind } = {}
        event.kind = kind
        event.nodeId = nodeId
        return (event as ImageAnimator_onPause_event)
    }
    else if ((kind) === (PeerEventKind.ImageAnimator_onRepeat)) {
        const event: { kind?: number, nodeId?: PeerEventKind } = {}
        event.kind = kind
        event.nodeId = nodeId
        return (event as ImageAnimator_onRepeat_event)
    }
    else if ((kind) === (PeerEventKind.ImageAnimator_onCancel)) {
        const event: { kind?: number, nodeId?: PeerEventKind } = {}
        event.kind = kind
        event.nodeId = nodeId
        return (event as ImageAnimator_onCancel_event)
    }
    else if ((kind) === (PeerEventKind.ImageAnimator_onFinish)) {
        const event: { kind?: number, nodeId?: PeerEventKind } = {}
        event.kind = kind
        event.nodeId = nodeId
        return (event as ImageAnimator_onFinish_event)
    }
    else if ((kind) === (PeerEventKind.ImageSpan_onComplete)) {
        const event: { kind?: number, nodeId?: PeerEventKind, result?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.result = eventDeserializer.readImageLoadResult()
        return (event as ImageSpan_onComplete_event)
    }
    else if ((kind) === (PeerEventKind.ImageSpan_onError)) {
        const event: { kind?: number, nodeId?: PeerEventKind, error?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.error = eventDeserializer.readImageError()
        return (event as ImageSpan_onError_event)
    }
    else if ((kind) === (PeerEventKind.List_onScroll)) {
        const event: { kind?: number, nodeId?: PeerEventKind, first?: any, last?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.first = (eventDeserializer.readNumber() as number)
        event.last = (eventDeserializer.readNumber() as number)
        return (event as List_onScroll_event)
    }
    else if ((kind) === (PeerEventKind.List_onScrollIndex)) {
        const event: { kind?: number, nodeId?: PeerEventKind, start?: any, end?: any, center?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.start = (eventDeserializer.readNumber() as number)
        event.end = (eventDeserializer.readNumber() as number)
        event.center = (eventDeserializer.readNumber() as number)
        return (event as List_onScrollIndex_event)
    }
    else if ((kind) === (PeerEventKind.List_onScrollVisibleContentChange)) {
        const event: { kind?: number, nodeId?: PeerEventKind, start?: any, end?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.start = eventDeserializer.readVisibleListContentInfo()
        event.end = eventDeserializer.readVisibleListContentInfo()
        return (event as List_onScrollVisibleContentChange_event)
    }
    else if ((kind) === (PeerEventKind.List_onReachStart)) {
        const event: { kind?: number, nodeId?: PeerEventKind } = {}
        event.kind = kind
        event.nodeId = nodeId
        return (event as List_onReachStart_event)
    }
    else if ((kind) === (PeerEventKind.List_onReachEnd)) {
        const event: { kind?: number, nodeId?: PeerEventKind } = {}
        event.kind = kind
        event.nodeId = nodeId
        return (event as List_onReachEnd_event)
    }
    else if ((kind) === (PeerEventKind.List_onScrollStart)) {
        const event: { kind?: number, nodeId?: PeerEventKind } = {}
        event.kind = kind
        event.nodeId = nodeId
        return (event as List_onScrollStart_event)
    }
    else if ((kind) === (PeerEventKind.List_onScrollStop)) {
        const event: { kind?: number, nodeId?: PeerEventKind } = {}
        event.kind = kind
        event.nodeId = nodeId
        return (event as List_onScrollStop_event)
    }
    else if ((kind) === (PeerEventKind.List_onItemDelete)) {
        const event: { kind?: number, nodeId?: PeerEventKind, index?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.index = (eventDeserializer.readNumber() as number)
        return (event as List_onItemDelete_event)
    }
    else if ((kind) === (PeerEventKind.List_onItemMove)) {
        const event: { kind?: number, nodeId?: PeerEventKind, from?: any, to?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.from = (eventDeserializer.readNumber() as number)
        event.to = (eventDeserializer.readNumber() as number)
        return (event as List_onItemMove_event)
    }
    else if ((kind) === (PeerEventKind.List_onItemDragStart)) {
        const event: { kind?: number, nodeId?: PeerEventKind, event?: any, itemIndex?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.event = eventDeserializer.readItemDragInfo()
        event.itemIndex = (eventDeserializer.readNumber() as number)
        return (event as List_onItemDragStart_event)
    }
    else if ((kind) === (PeerEventKind.List_onItemDragEnter)) {
        const event: { kind?: number, nodeId?: PeerEventKind, event?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.event = eventDeserializer.readItemDragInfo()
        return (event as List_onItemDragEnter_event)
    }
    else if ((kind) === (PeerEventKind.List_onItemDragMove)) {
        const event: { kind?: number, nodeId?: PeerEventKind, event?: any, itemIndex?: any, insertIndex?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.event = eventDeserializer.readItemDragInfo()
        event.itemIndex = (eventDeserializer.readNumber() as number)
        event.insertIndex = (eventDeserializer.readNumber() as number)
        return (event as List_onItemDragMove_event)
    }
    else if ((kind) === (PeerEventKind.List_onItemDragLeave)) {
        const event: { kind?: number, nodeId?: PeerEventKind, event?: any, itemIndex?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.event = eventDeserializer.readItemDragInfo()
        event.itemIndex = (eventDeserializer.readNumber() as number)
        return (event as List_onItemDragLeave_event)
    }
    else if ((kind) === (PeerEventKind.List_onItemDrop)) {
        const event: { kind?: number, nodeId?: PeerEventKind, event?: any, itemIndex?: any, insertIndex?: any, isSuccess?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.event = eventDeserializer.readItemDragInfo()
        event.itemIndex = (eventDeserializer.readNumber() as number)
        event.insertIndex = (eventDeserializer.readNumber() as number)
        event.isSuccess = eventDeserializer.readBoolean()
        return (event as List_onItemDrop_event)
    }
    else if ((kind) === (PeerEventKind.List_onScrollFrameBegin)) {
        const event: { kind?: number, nodeId?: PeerEventKind, offset?: any, state?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.offset = (eventDeserializer.readNumber() as number)
        event.state = (eventDeserializer.readInt32() as ScrollState)
        return (event as List_onScrollFrameBegin_event)
    }
    else if ((kind) === (PeerEventKind.ListItem_onSelect)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = eventDeserializer.readBoolean()
        return (event as ListItem_onSelect_event)
    }
    else if ((kind) === (PeerEventKind.ListItem__onChangeEvent_selected)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = eventDeserializer.readBoolean()
        return (event as ListItem__onChangeEvent_selected_event)
    }
    else if ((kind) === (PeerEventKind.LocationButton_onClick)) {
        const event: { kind?: number, nodeId?: PeerEventKind, event?: any, result?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.event = (eventDeserializer.readClickEvent() as ClickEvent)
        event.result = (eventDeserializer.readInt32() as LocationButtonOnClickResult)
        return (event as LocationButton_onClick_event)
    }
    else if ((kind) === (PeerEventKind.Marquee_onStart)) {
        const event: { kind?: number, nodeId?: PeerEventKind } = {}
        event.kind = kind
        event.nodeId = nodeId
        return (event as Marquee_onStart_event)
    }
    else if ((kind) === (PeerEventKind.Marquee_onBounce)) {
        const event: { kind?: number, nodeId?: PeerEventKind } = {}
        event.kind = kind
        event.nodeId = nodeId
        return (event as Marquee_onBounce_event)
    }
    else if ((kind) === (PeerEventKind.Marquee_onFinish)) {
        const event: { kind?: number, nodeId?: PeerEventKind } = {}
        event.kind = kind
        event.nodeId = nodeId
        return (event as Marquee_onFinish_event)
    }
    else if ((kind) === (PeerEventKind.MenuItem_onChange)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = eventDeserializer.readBoolean()
        return (event as MenuItem_onChange_event)
    }
    else if ((kind) === (PeerEventKind.MenuItem__onChangeEvent_selected)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = eventDeserializer.readBoolean()
        return (event as MenuItem__onChangeEvent_selected_event)
    }
    else if ((kind) === (PeerEventKind.NavDestination_onShown)) {
        const event: { kind?: number, nodeId?: PeerEventKind } = {}
        event.kind = kind
        event.nodeId = nodeId
        return (event as NavDestination_onShown_event)
    }
    else if ((kind) === (PeerEventKind.NavDestination_onHidden)) {
        const event: { kind?: number, nodeId?: PeerEventKind } = {}
        event.kind = kind
        event.nodeId = nodeId
        return (event as NavDestination_onHidden_event)
    }
    else if ((kind) === (PeerEventKind.NavDestination_onBackPressed)) {
        const event: { kind?: number, nodeId?: PeerEventKind } = {}
        event.kind = kind
        event.nodeId = nodeId
        return (event as NavDestination_onBackPressed_event)
    }
    else if ((kind) === (PeerEventKind.NavDestination_onReady)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = (eventDeserializer.readNavDestinationContext() as NavDestinationContext)
        return (event as NavDestination_onReady_event)
    }
    else if ((kind) === (PeerEventKind.NavDestination_onWillAppear)) {
        const event: { kind?: number, nodeId?: PeerEventKind } = {}
        event.kind = kind
        event.nodeId = nodeId
        return (event as NavDestination_onWillAppear_event)
    }
    else if ((kind) === (PeerEventKind.NavDestination_onWillDisappear)) {
        const event: { kind?: number, nodeId?: PeerEventKind } = {}
        event.kind = kind
        event.nodeId = nodeId
        return (event as NavDestination_onWillDisappear_event)
    }
    else if ((kind) === (PeerEventKind.NavDestination_onWillShow)) {
        const event: { kind?: number, nodeId?: PeerEventKind } = {}
        event.kind = kind
        event.nodeId = nodeId
        return (event as NavDestination_onWillShow_event)
    }
    else if ((kind) === (PeerEventKind.NavDestination_onWillHide)) {
        const event: { kind?: number, nodeId?: PeerEventKind } = {}
        event.kind = kind
        event.nodeId = nodeId
        return (event as NavDestination_onWillHide_event)
    }
    else if ((kind) === (PeerEventKind.NavRouter_onStateChange)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = eventDeserializer.readBoolean()
        return (event as NavRouter_onStateChange_event)
    }
    else if ((kind) === (PeerEventKind.Panel_onChange)) {
        const event: { kind?: number, nodeId?: PeerEventKind, width?: any, height?: any, mode?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.width = (eventDeserializer.readNumber() as number)
        event.height = (eventDeserializer.readNumber() as number)
        event.mode = (eventDeserializer.readInt32() as PanelMode)
        return (event as Panel_onChange_event)
    }
    else if ((kind) === (PeerEventKind.Panel_onHeightChange)) {
        const event: { kind?: number, nodeId?: PeerEventKind, index?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.index = (eventDeserializer.readNumber() as number)
        return (event as Panel_onHeightChange_event)
    }
    else if ((kind) === (PeerEventKind.Panel__onChangeEvent_mode)) {
        const event: { kind?: number, nodeId?: PeerEventKind, mode?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.mode = (eventDeserializer.readInt32() as PanelMode)
        return (event as Panel__onChangeEvent_mode_event)
    }
    else if ((kind) === (PeerEventKind.PasteButton_onClick)) {
        const event: { kind?: number, nodeId?: PeerEventKind, event?: any, result?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.event = (eventDeserializer.readClickEvent() as ClickEvent)
        event.result = (eventDeserializer.readInt32() as PasteButtonOnClickResult)
        return (event as PasteButton_onClick_event)
    }
    else if ((kind) === (PeerEventKind.PatternLock_onPatternComplete)) {
        const event: { kind?: number, nodeId?: PeerEventKind, input?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        const input_buf_length: int32 = eventDeserializer.readInt32()
        let input_buf: Array<number> = new Array<number>()
        for (let input_buf_i = 0; input_buf_i < input_buf_length; input_buf_i++) {
            input_buf[input_buf_i] = (eventDeserializer.readNumber() as number)
        }
        event.input = input_buf
        return (event as PatternLock_onPatternComplete_event)
    }
    else if ((kind) === (PeerEventKind.PatternLock_onDotConnect)) {
        const event: { kind?: number, nodeId?: PeerEventKind, index?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.index = (eventDeserializer.readNumber() as number)
        return (event as PatternLock_onDotConnect_event)
    }
    else if ((kind) === (PeerEventKind.PluginComponent_onComplete)) {
        const event: { kind?: number, nodeId?: PeerEventKind } = {}
        event.kind = kind
        event.nodeId = nodeId
        return (event as PluginComponent_onComplete_event)
    }
    else if ((kind) === (PeerEventKind.PluginComponent_onError)) {
        const event: { kind?: number, nodeId?: PeerEventKind, info?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.info = eventDeserializer.readPluginErrorData()
        return (event as PluginComponent_onError_event)
    }
    else if ((kind) === (PeerEventKind.Radio_onChange)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = eventDeserializer.readBoolean()
        return (event as Radio_onChange_event)
    }
    else if ((kind) === (PeerEventKind.Radio__onChangeEvent_checked)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = eventDeserializer.readBoolean()
        return (event as Radio__onChangeEvent_checked_event)
    }
    else if ((kind) === (PeerEventKind.Rating_onChange)) {
        const event: { kind?: number, nodeId?: PeerEventKind, index?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.index = (eventDeserializer.readNumber() as number)
        return (event as Rating_onChange_event)
    }
    else if ((kind) === (PeerEventKind.Rating__onChangeEvent_rating)) {
        const event: { kind?: number, nodeId?: PeerEventKind, index?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.index = (eventDeserializer.readNumber() as number)
        return (event as Rating__onChangeEvent_rating_event)
    }
    else if ((kind) === (PeerEventKind.Refresh_onStateChange)) {
        const event: { kind?: number, nodeId?: PeerEventKind, state?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.state = (eventDeserializer.readInt32() as RefreshStatus)
        return (event as Refresh_onStateChange_event)
    }
    else if ((kind) === (PeerEventKind.Refresh_onRefreshing)) {
        const event: { kind?: number, nodeId?: PeerEventKind } = {}
        event.kind = kind
        event.nodeId = nodeId
        return (event as Refresh_onRefreshing_event)
    }
    else if ((kind) === (PeerEventKind.Refresh_onOffsetChange)) {
        const event: { kind?: number, nodeId?: PeerEventKind, index?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.index = (eventDeserializer.readNumber() as number)
        return (event as Refresh_onOffsetChange_event)
    }
    else if ((kind) === (PeerEventKind.Refresh__onChangeEvent_refreshing)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = eventDeserializer.readBoolean()
        return (event as Refresh__onChangeEvent_refreshing_event)
    }
    else if ((kind) === (PeerEventKind.RichEditor_onReady)) {
        const event: { kind?: number, nodeId?: PeerEventKind } = {}
        event.kind = kind
        event.nodeId = nodeId
        return (event as RichEditor_onReady_event)
    }
    else if ((kind) === (PeerEventKind.RichEditor_onSelect)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = eventDeserializer.readRichEditorSelection()
        return (event as RichEditor_onSelect_event)
    }
    else if ((kind) === (PeerEventKind.RichEditor_onSelectionChange)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = eventDeserializer.readRichEditorRange()
        return (event as RichEditor_onSelectionChange_event)
    }
    else if ((kind) === (PeerEventKind.RichEditor_aboutToIMEInput)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = eventDeserializer.readRichEditorInsertValue()
        return (event as RichEditor_aboutToIMEInput_event)
    }
    else if ((kind) === (PeerEventKind.RichEditor_onIMEInputComplete)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = eventDeserializer.readRichEditorTextSpanResult()
        return (event as RichEditor_onIMEInputComplete_event)
    }
    else if ((kind) === (PeerEventKind.RichEditor_onDidIMEInput)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = eventDeserializer.readTextRange()
        return (event as RichEditor_onDidIMEInput_event)
    }
    else if ((kind) === (PeerEventKind.RichEditor_aboutToDelete)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = eventDeserializer.readRichEditorDeleteValue()
        return (event as RichEditor_aboutToDelete_event)
    }
    else if ((kind) === (PeerEventKind.RichEditor_onDeleteComplete)) {
        const event: { kind?: number, nodeId?: PeerEventKind } = {}
        event.kind = kind
        event.nodeId = nodeId
        return (event as RichEditor_onDeleteComplete_event)
    }
    else if ((kind) === (PeerEventKind.RichEditor_onPaste)) {
        const event: { kind?: number, nodeId?: PeerEventKind, event?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        const event_buf_runtimeType = (eventDeserializer.readInt8() as int32)
        let event_buf: PasteEvent | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (event_buf_runtimeType))
        {
            event_buf = eventDeserializer.readPasteEvent()
        }
        event.event = event_buf
        return (event as RichEditor_onPaste_event)
    }
    else if ((kind) === (PeerEventKind.RichEditor_onEditingChange)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = eventDeserializer.readBoolean()
        return (event as RichEditor_onEditingChange_event)
    }
    else if ((kind) === (PeerEventKind.RichEditor_onSubmit)) {
        const event: { kind?: number, nodeId?: PeerEventKind, enterKey?: any, event?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.enterKey = (eventDeserializer.readInt32() as EnterKeyType)
        event.event = (eventDeserializer.readSubmitEvent() as SubmitEvent)
        return (event as RichEditor_onSubmit_event)
    }
    else if ((kind) === (PeerEventKind.RichEditor_onWillChange)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = eventDeserializer.readRichEditorChangeValue()
        return (event as RichEditor_onWillChange_event)
    }
    else if ((kind) === (PeerEventKind.RichEditor_onDidChange)) {
        const event: { kind?: number, nodeId?: PeerEventKind, rangeBefore?: any, rangeAfter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.rangeBefore = eventDeserializer.readTextRange()
        event.rangeAfter = eventDeserializer.readTextRange()
        return (event as RichEditor_onDidChange_event)
    }
    else if ((kind) === (PeerEventKind.RichEditor_onCut)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = eventDeserializer.readCutEvent()
        return (event as RichEditor_onCut_event)
    }
    else if ((kind) === (PeerEventKind.RichEditor_onCopy)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = eventDeserializer.readCopyEvent()
        return (event as RichEditor_onCopy_event)
    }
    else if ((kind) === (PeerEventKind.RichEditor_bindSelectionMenu)) {
        const event: { kind?: number, nodeId?: PeerEventKind } = {}
        event.kind = kind
        event.nodeId = nodeId
        return (event as RichEditor_bindSelectionMenu_event)
    }
    else if ((kind) === (PeerEventKind.RichEditor_customKeyboard)) {
        const event: { kind?: number, nodeId?: PeerEventKind } = {}
        event.kind = kind
        event.nodeId = nodeId
        return (event as RichEditor_customKeyboard_event)
    }
    else if ((kind) === (PeerEventKind.RichText_onStart)) {
        const event: { kind?: number, nodeId?: PeerEventKind } = {}
        event.kind = kind
        event.nodeId = nodeId
        return (event as RichText_onStart_event)
    }
    else if ((kind) === (PeerEventKind.RichText_onComplete)) {
        const event: { kind?: number, nodeId?: PeerEventKind } = {}
        event.kind = kind
        event.nodeId = nodeId
        return (event as RichText_onComplete_event)
    }
    else if ((kind) === (PeerEventKind.SaveButton_onClick)) {
        const event: { kind?: number, nodeId?: PeerEventKind, event?: any, result?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.event = (eventDeserializer.readClickEvent() as ClickEvent)
        event.result = (eventDeserializer.readInt32() as SaveButtonOnClickResult)
        return (event as SaveButton_onClick_event)
    }
    else if ((kind) === (PeerEventKind.Scroll_onScroll)) {
        const event: { kind?: number, nodeId?: PeerEventKind, first?: any, last?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.first = (eventDeserializer.readNumber() as number)
        event.last = (eventDeserializer.readNumber() as number)
        return (event as Scroll_onScroll_event)
    }
    else if ((kind) === (PeerEventKind.Scroll_onDidScroll)) {
        const event: { kind?: number, nodeId?: PeerEventKind, xOffset?: any, yOffset?: any, scrollState?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.xOffset = (eventDeserializer.readNumber() as number)
        event.yOffset = (eventDeserializer.readNumber() as number)
        event.scrollState = (eventDeserializer.readInt32() as ScrollState)
        return (event as Scroll_onDidScroll_event)
    }
    else if ((kind) === (PeerEventKind.Scroll_onScrollEdge)) {
        const event: { kind?: number, nodeId?: PeerEventKind, side?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.side = (eventDeserializer.readInt32() as Edge)
        return (event as Scroll_onScrollEdge_event)
    }
    else if ((kind) === (PeerEventKind.Scroll_onScrollStart)) {
        const event: { kind?: number, nodeId?: PeerEventKind } = {}
        event.kind = kind
        event.nodeId = nodeId
        return (event as Scroll_onScrollStart_event)
    }
    else if ((kind) === (PeerEventKind.Scroll_onScrollEnd)) {
        const event: { kind?: number, nodeId?: PeerEventKind } = {}
        event.kind = kind
        event.nodeId = nodeId
        return (event as Scroll_onScrollEnd_event)
    }
    else if ((kind) === (PeerEventKind.Scroll_onScrollStop)) {
        const event: { kind?: number, nodeId?: PeerEventKind } = {}
        event.kind = kind
        event.nodeId = nodeId
        return (event as Scroll_onScrollStop_event)
    }
    else if ((kind) === (PeerEventKind.Scroll_onScrollFrameBegin)) {
        const event: { kind?: number, nodeId?: PeerEventKind, offset?: any, state?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.offset = (eventDeserializer.readNumber() as number)
        event.state = (eventDeserializer.readInt32() as ScrollState)
        return (event as Scroll_onScrollFrameBegin_event)
    }
    else if ((kind) === (PeerEventKind.Search_onEditChange)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = eventDeserializer.readBoolean()
        return (event as Search_onEditChange_event)
    }
    else if ((kind) === (PeerEventKind.Search_onSubmit0)) {
        const event: { kind?: number, nodeId?: PeerEventKind, breakpoints?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.breakpoints = (eventDeserializer.readString() as string)
        return (event as Search_onSubmit0_event)
    }
    else if ((kind) === (PeerEventKind.Search_onSubmit1)) {
        const event: { kind?: number, nodeId?: PeerEventKind, searchContent?: any, event?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.searchContent = (eventDeserializer.readString() as string)
        const event_buf_runtimeType = (eventDeserializer.readInt8() as int32)
        let event_buf: SubmitEvent | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (event_buf_runtimeType))
        {
            event_buf = (eventDeserializer.readSubmitEvent() as SubmitEvent)
        }
        event.event = event_buf
        return (event as Search_onSubmit1_event)
    }
    else if ((kind) === (PeerEventKind.Search_onChange)) {
        const event: { kind?: number, nodeId?: PeerEventKind, value?: any, previewText?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.value = (eventDeserializer.readString() as string)
        const previewText_buf_runtimeType = (eventDeserializer.readInt8() as int32)
        let previewText_buf: PreviewText | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (previewText_buf_runtimeType))
        {
            previewText_buf = eventDeserializer.readPreviewText()
        }
        event.previewText = previewText_buf
        return (event as Search_onChange_event)
    }
    else if ((kind) === (PeerEventKind.Search_onTextSelectionChange)) {
        const event: { kind?: number, nodeId?: PeerEventKind, selectionStart?: any, selectionEnd?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.selectionStart = (eventDeserializer.readNumber() as number)
        event.selectionEnd = (eventDeserializer.readNumber() as number)
        return (event as Search_onTextSelectionChange_event)
    }
    else if ((kind) === (PeerEventKind.Search_onContentScroll)) {
        const event: { kind?: number, nodeId?: PeerEventKind, totalOffsetX?: any, totalOffsetY?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.totalOffsetX = (eventDeserializer.readNumber() as number)
        event.totalOffsetY = (eventDeserializer.readNumber() as number)
        return (event as Search_onContentScroll_event)
    }
    else if ((kind) === (PeerEventKind.Search_onCopy)) {
        const event: { kind?: number, nodeId?: PeerEventKind, breakpoints?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.breakpoints = (eventDeserializer.readString() as string)
        return (event as Search_onCopy_event)
    }
    else if ((kind) === (PeerEventKind.Search_onCut)) {
        const event: { kind?: number, nodeId?: PeerEventKind, breakpoints?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.breakpoints = (eventDeserializer.readString() as string)
        return (event as Search_onCut_event)
    }
    else if ((kind) === (PeerEventKind.Search_onPaste)) {
        const event: { kind?: number, nodeId?: PeerEventKind, content?: any, event?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.content = (eventDeserializer.readString() as string)
        event.event = eventDeserializer.readPasteEvent()
        return (event as Search_onPaste_event)
    }
    else if ((kind) === (PeerEventKind.Search_onWillInsert)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = eventDeserializer.readInsertValue()
        return (event as Search_onWillInsert_event)
    }
    else if ((kind) === (PeerEventKind.Search_onDidInsert)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = eventDeserializer.readInsertValue()
        return (event as Search_onDidInsert_event)
    }
    else if ((kind) === (PeerEventKind.Search_onWillDelete)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = eventDeserializer.readDeleteValue()
        return (event as Search_onWillDelete_event)
    }
    else if ((kind) === (PeerEventKind.Search_onDidDelete)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = eventDeserializer.readDeleteValue()
        return (event as Search_onDidDelete_event)
    }
    else if ((kind) === (PeerEventKind.Search_customKeyboard)) {
        const event: { kind?: number, nodeId?: PeerEventKind } = {}
        event.kind = kind
        event.nodeId = nodeId
        return (event as Search_customKeyboard_event)
    }
    else if ((kind) === (PeerEventKind.Search__onChangeEvent_value)) {
        const event: { kind?: number, nodeId?: PeerEventKind, breakpoints?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.breakpoints = (eventDeserializer.readString() as string)
        return (event as Search__onChangeEvent_value_event)
    }
    else if ((kind) === (PeerEventKind.Select_onSelect)) {
        const event: { kind?: number, nodeId?: PeerEventKind, index?: any, value?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.index = (eventDeserializer.readNumber() as number)
        event.value = (eventDeserializer.readString() as string)
        return (event as Select_onSelect_event)
    }
    else if ((kind) === (PeerEventKind.Select__onChangeEvent_selected)) {
        const event: { kind?: number, nodeId?: PeerEventKind, selected?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        const selected_buf_selector: number = eventDeserializer.readInt8()
        let selected_buf: number | Resource | undefined|undefined 
        if (selected_buf_selector == 0) {
            selected_buf = (eventDeserializer.readNumber() as number)
        }
        else if (selected_buf_selector == 1) {
            selected_buf = eventDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for selected_buf has to be chosen through deserialisation.")
        }
        event.selected = (selected_buf as number | Resource)
        return (event as Select__onChangeEvent_selected_event)
    }
    else if ((kind) === (PeerEventKind.Select__onChangeEvent_value)) {
        const event: { kind?: number, nodeId?: PeerEventKind, value?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        const value_buf_selector: number = eventDeserializer.readInt8()
        let value_buf: string | Resource | undefined|undefined 
        if (value_buf_selector == 0) {
            value_buf = (eventDeserializer.readString() as string)
        }
        else if (value_buf_selector == 1) {
            value_buf = eventDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for value_buf has to be chosen through deserialisation.")
        }
        event.value = (value_buf as string | Resource)
        return (event as Select__onChangeEvent_value_event)
    }
    else if ((kind) === (PeerEventKind.Slider_onChange)) {
        const event: { kind?: number, nodeId?: PeerEventKind, value?: any, mode?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.value = (eventDeserializer.readNumber() as number)
        event.mode = (eventDeserializer.readInt32() as SliderChangeMode)
        return (event as Slider_onChange_event)
    }
    else if ((kind) === (PeerEventKind.Slider__onChangeEvent_value)) {
        const event: { kind?: number, nodeId?: PeerEventKind, index?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.index = (eventDeserializer.readNumber() as number)
        return (event as Slider__onChangeEvent_value_event)
    }
    else if ((kind) === (PeerEventKind.Stepper_onFinish)) {
        const event: { kind?: number, nodeId?: PeerEventKind } = {}
        event.kind = kind
        event.nodeId = nodeId
        return (event as Stepper_onFinish_event)
    }
    else if ((kind) === (PeerEventKind.Stepper_onSkip)) {
        const event: { kind?: number, nodeId?: PeerEventKind } = {}
        event.kind = kind
        event.nodeId = nodeId
        return (event as Stepper_onSkip_event)
    }
    else if ((kind) === (PeerEventKind.Stepper_onChange)) {
        const event: { kind?: number, nodeId?: PeerEventKind, first?: any, last?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.first = (eventDeserializer.readNumber() as number)
        event.last = (eventDeserializer.readNumber() as number)
        return (event as Stepper_onChange_event)
    }
    else if ((kind) === (PeerEventKind.Stepper_onNext)) {
        const event: { kind?: number, nodeId?: PeerEventKind, first?: any, last?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.first = (eventDeserializer.readNumber() as number)
        event.last = (eventDeserializer.readNumber() as number)
        return (event as Stepper_onNext_event)
    }
    else if ((kind) === (PeerEventKind.Stepper_onPrevious)) {
        const event: { kind?: number, nodeId?: PeerEventKind, first?: any, last?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.first = (eventDeserializer.readNumber() as number)
        event.last = (eventDeserializer.readNumber() as number)
        return (event as Stepper_onPrevious_event)
    }
    else if ((kind) === (PeerEventKind.Stepper__onChangeEvent_index)) {
        const event: { kind?: number, nodeId?: PeerEventKind, index?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.index = (eventDeserializer.readNumber() as number)
        return (event as Stepper__onChangeEvent_index_event)
    }
    else if ((kind) === (PeerEventKind.Swiper_onChange)) {
        const event: { kind?: number, nodeId?: PeerEventKind, index?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.index = (eventDeserializer.readNumber() as number)
        return (event as Swiper_onChange_event)
    }
    else if ((kind) === (PeerEventKind.Swiper_onAnimationStart)) {
        const event: { kind?: number, nodeId?: PeerEventKind, index?: any, targetIndex?: any, extraInfo?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.index = (eventDeserializer.readNumber() as number)
        event.targetIndex = (eventDeserializer.readNumber() as number)
        event.extraInfo = eventDeserializer.readSwiperAnimationEvent()
        return (event as Swiper_onAnimationStart_event)
    }
    else if ((kind) === (PeerEventKind.Swiper_onAnimationEnd)) {
        const event: { kind?: number, nodeId?: PeerEventKind, index?: any, extraInfo?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.index = (eventDeserializer.readNumber() as number)
        event.extraInfo = eventDeserializer.readSwiperAnimationEvent()
        return (event as Swiper_onAnimationEnd_event)
    }
    else if ((kind) === (PeerEventKind.Swiper_onGestureSwipe)) {
        const event: { kind?: number, nodeId?: PeerEventKind, index?: any, extraInfo?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.index = (eventDeserializer.readNumber() as number)
        event.extraInfo = eventDeserializer.readSwiperAnimationEvent()
        return (event as Swiper_onGestureSwipe_event)
    }
    else if ((kind) === (PeerEventKind.Swiper_onContentDidScroll)) {
        const event: { kind?: number, nodeId?: PeerEventKind, selectedIndex?: any, index?: any, position?: any, mainAxisLength?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.selectedIndex = (eventDeserializer.readNumber() as number)
        event.index = (eventDeserializer.readNumber() as number)
        event.position = (eventDeserializer.readNumber() as number)
        event.mainAxisLength = (eventDeserializer.readNumber() as number)
        return (event as Swiper_onContentDidScroll_event)
    }
    else if ((kind) === (PeerEventKind.Swiper__onChangeEvent_index)) {
        const event: { kind?: number, nodeId?: PeerEventKind, index?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.index = (eventDeserializer.readNumber() as number)
        return (event as Swiper__onChangeEvent_index_event)
    }
    else if ((kind) === (PeerEventKind.IndicatorComponent_onChange)) {
        const event: { kind?: number, nodeId?: PeerEventKind, index?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.index = (eventDeserializer.readNumber() as number)
        return (event as IndicatorComponent_onChange_event)
    }
    else if ((kind) === (PeerEventKind.Tabs_onChange)) {
        const event: { kind?: number, nodeId?: PeerEventKind, index?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.index = (eventDeserializer.readNumber() as number)
        return (event as Tabs_onChange_event)
    }
    else if ((kind) === (PeerEventKind.Tabs_onTabBarClick)) {
        const event: { kind?: number, nodeId?: PeerEventKind, index?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.index = (eventDeserializer.readNumber() as number)
        return (event as Tabs_onTabBarClick_event)
    }
    else if ((kind) === (PeerEventKind.Tabs_onAnimationStart)) {
        const event: { kind?: number, nodeId?: PeerEventKind, index?: any, targetIndex?: any, extraInfo?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.index = (eventDeserializer.readNumber() as number)
        event.targetIndex = (eventDeserializer.readNumber() as number)
        event.extraInfo = eventDeserializer.readTabsAnimationEvent()
        return (event as Tabs_onAnimationStart_event)
    }
    else if ((kind) === (PeerEventKind.Tabs_onAnimationEnd)) {
        const event: { kind?: number, nodeId?: PeerEventKind, index?: any, extraInfo?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.index = (eventDeserializer.readNumber() as number)
        event.extraInfo = eventDeserializer.readTabsAnimationEvent()
        return (event as Tabs_onAnimationEnd_event)
    }
    else if ((kind) === (PeerEventKind.Tabs_onGestureSwipe)) {
        const event: { kind?: number, nodeId?: PeerEventKind, index?: any, extraInfo?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.index = (eventDeserializer.readNumber() as number)
        event.extraInfo = eventDeserializer.readTabsAnimationEvent()
        return (event as Tabs_onGestureSwipe_event)
    }
    else if ((kind) === (PeerEventKind.Tabs_customContentTransition)) {
        const event: { kind?: number, nodeId?: PeerEventKind, from?: any, to?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.from = (eventDeserializer.readNumber() as number)
        event.to = (eventDeserializer.readNumber() as number)
        return (event as Tabs_customContentTransition_event)
    }
    else if ((kind) === (PeerEventKind.Tabs_onContentWillChange)) {
        const event: { kind?: number, nodeId?: PeerEventKind, currentIndex?: any, comingIndex?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.currentIndex = (eventDeserializer.readNumber() as number)
        event.comingIndex = (eventDeserializer.readNumber() as number)
        return (event as Tabs_onContentWillChange_event)
    }
    else if ((kind) === (PeerEventKind.Tabs__onChangeEvent_index)) {
        const event: { kind?: number, nodeId?: PeerEventKind, index?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.index = (eventDeserializer.readNumber() as number)
        return (event as Tabs__onChangeEvent_index_event)
    }
    else if ((kind) === (PeerEventKind.TabContent_onWillShow)) {
        const event: { kind?: number, nodeId?: PeerEventKind } = {}
        event.kind = kind
        event.nodeId = nodeId
        return (event as TabContent_onWillShow_event)
    }
    else if ((kind) === (PeerEventKind.TabContent_onWillHide)) {
        const event: { kind?: number, nodeId?: PeerEventKind } = {}
        event.kind = kind
        event.nodeId = nodeId
        return (event as TabContent_onWillHide_event)
    }
    else if ((kind) === (PeerEventKind.Text_onCopy)) {
        const event: { kind?: number, nodeId?: PeerEventKind, breakpoints?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.breakpoints = (eventDeserializer.readString() as string)
        return (event as Text_onCopy_event)
    }
    else if ((kind) === (PeerEventKind.Text_onTextSelectionChange)) {
        const event: { kind?: number, nodeId?: PeerEventKind, first?: any, last?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.first = (eventDeserializer.readNumber() as number)
        event.last = (eventDeserializer.readNumber() as number)
        return (event as Text_onTextSelectionChange_event)
    }
    else if ((kind) === (PeerEventKind.Text_bindSelectionMenu)) {
        const event: { kind?: number, nodeId?: PeerEventKind } = {}
        event.kind = kind
        event.nodeId = nodeId
        return (event as Text_bindSelectionMenu_event)
    }
    else if ((kind) === (PeerEventKind.TextArea_onSubmit0)) {
        const event: { kind?: number, nodeId?: PeerEventKind, enterKey?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.enterKey = (eventDeserializer.readInt32() as EnterKeyType)
        return (event as TextArea_onSubmit0_event)
    }
    else if ((kind) === (PeerEventKind.TextArea_onSubmit1)) {
        const event: { kind?: number, nodeId?: PeerEventKind, enterKeyType?: any, event?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.enterKeyType = (eventDeserializer.readInt32() as EnterKeyType)
        const event_buf_runtimeType = (eventDeserializer.readInt8() as int32)
        let event_buf: SubmitEvent | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (event_buf_runtimeType))
        {
            event_buf = (eventDeserializer.readSubmitEvent() as SubmitEvent)
        }
        event.event = event_buf
        return (event as TextArea_onSubmit1_event)
    }
    else if ((kind) === (PeerEventKind.TextArea_onChange)) {
        const event: { kind?: number, nodeId?: PeerEventKind, value?: any, previewText?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.value = (eventDeserializer.readString() as string)
        const previewText_buf_runtimeType = (eventDeserializer.readInt8() as int32)
        let previewText_buf: PreviewText | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (previewText_buf_runtimeType))
        {
            previewText_buf = eventDeserializer.readPreviewText()
        }
        event.previewText = previewText_buf
        return (event as TextArea_onChange_event)
    }
    else if ((kind) === (PeerEventKind.TextArea_onTextSelectionChange)) {
        const event: { kind?: number, nodeId?: PeerEventKind, first?: any, last?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.first = (eventDeserializer.readNumber() as number)
        event.last = (eventDeserializer.readNumber() as number)
        return (event as TextArea_onTextSelectionChange_event)
    }
    else if ((kind) === (PeerEventKind.TextArea_onContentScroll)) {
        const event: { kind?: number, nodeId?: PeerEventKind, first?: any, last?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.first = (eventDeserializer.readNumber() as number)
        event.last = (eventDeserializer.readNumber() as number)
        return (event as TextArea_onContentScroll_event)
    }
    else if ((kind) === (PeerEventKind.TextArea_onEditChange)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = eventDeserializer.readBoolean()
        return (event as TextArea_onEditChange_event)
    }
    else if ((kind) === (PeerEventKind.TextArea_onCopy)) {
        const event: { kind?: number, nodeId?: PeerEventKind, breakpoints?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.breakpoints = (eventDeserializer.readString() as string)
        return (event as TextArea_onCopy_event)
    }
    else if ((kind) === (PeerEventKind.TextArea_onCut)) {
        const event: { kind?: number, nodeId?: PeerEventKind, breakpoints?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.breakpoints = (eventDeserializer.readString() as string)
        return (event as TextArea_onCut_event)
    }
    else if ((kind) === (PeerEventKind.TextArea_onPaste)) {
        const event: { kind?: number, nodeId?: PeerEventKind, value?: any, event?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.value = (eventDeserializer.readString() as string)
        event.event = eventDeserializer.readPasteEvent()
        return (event as TextArea_onPaste_event)
    }
    else if ((kind) === (PeerEventKind.TextArea_onWillInsert)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = eventDeserializer.readInsertValue()
        return (event as TextArea_onWillInsert_event)
    }
    else if ((kind) === (PeerEventKind.TextArea_onDidInsert)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = eventDeserializer.readInsertValue()
        return (event as TextArea_onDidInsert_event)
    }
    else if ((kind) === (PeerEventKind.TextArea_onWillDelete)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = eventDeserializer.readDeleteValue()
        return (event as TextArea_onWillDelete_event)
    }
    else if ((kind) === (PeerEventKind.TextArea_onDidDelete)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = eventDeserializer.readDeleteValue()
        return (event as TextArea_onDidDelete_event)
    }
    else if ((kind) === (PeerEventKind.TextArea_customKeyboard)) {
        const event: { kind?: number, nodeId?: PeerEventKind } = {}
        event.kind = kind
        event.nodeId = nodeId
        return (event as TextArea_customKeyboard_event)
    }
    else if ((kind) === (PeerEventKind.TextArea__onChangeEvent_text)) {
        const event: { kind?: number, nodeId?: PeerEventKind, value?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        const value_buf_selector: number = eventDeserializer.readInt8()
        let value_buf: string | Resource | undefined|undefined 
        if (value_buf_selector == 0) {
            value_buf = (eventDeserializer.readString() as string)
        }
        else if (value_buf_selector == 1) {
            value_buf = eventDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for value_buf has to be chosen through deserialisation.")
        }
        event.value = (value_buf as string | Resource)
        return (event as TextArea__onChangeEvent_text_event)
    }
    else if ((kind) === (PeerEventKind.TextClock_onDateChange)) {
        const event: { kind?: number, nodeId?: PeerEventKind, index?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.index = (eventDeserializer.readNumber() as number)
        return (event as TextClock_onDateChange_event)
    }
    else if ((kind) === (PeerEventKind.TextInput_onEditChanged)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = eventDeserializer.readBoolean()
        return (event as TextInput_onEditChanged_event)
    }
    else if ((kind) === (PeerEventKind.TextInput_onEditChange)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = eventDeserializer.readBoolean()
        return (event as TextInput_onEditChange_event)
    }
    else if ((kind) === (PeerEventKind.TextInput_onSubmit)) {
        const event: { kind?: number, nodeId?: PeerEventKind, enterKey?: any, event?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.enterKey = (eventDeserializer.readInt32() as EnterKeyType)
        event.event = (eventDeserializer.readSubmitEvent() as SubmitEvent)
        return (event as TextInput_onSubmit_event)
    }
    else if ((kind) === (PeerEventKind.TextInput_onChange)) {
        const event: { kind?: number, nodeId?: PeerEventKind, value?: any, previewText?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.value = (eventDeserializer.readString() as string)
        const previewText_buf_runtimeType = (eventDeserializer.readInt8() as int32)
        let previewText_buf: PreviewText | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (previewText_buf_runtimeType))
        {
            previewText_buf = eventDeserializer.readPreviewText()
        }
        event.previewText = previewText_buf
        return (event as TextInput_onChange_event)
    }
    else if ((kind) === (PeerEventKind.TextInput_onTextSelectionChange)) {
        const event: { kind?: number, nodeId?: PeerEventKind, selectionStart?: any, selectionEnd?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.selectionStart = (eventDeserializer.readNumber() as number)
        event.selectionEnd = (eventDeserializer.readNumber() as number)
        return (event as TextInput_onTextSelectionChange_event)
    }
    else if ((kind) === (PeerEventKind.TextInput_onContentScroll)) {
        const event: { kind?: number, nodeId?: PeerEventKind, totalOffsetX?: any, totalOffsetY?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.totalOffsetX = (eventDeserializer.readNumber() as number)
        event.totalOffsetY = (eventDeserializer.readNumber() as number)
        return (event as TextInput_onContentScroll_event)
    }
    else if ((kind) === (PeerEventKind.TextInput_onCopy)) {
        const event: { kind?: number, nodeId?: PeerEventKind, breakpoints?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.breakpoints = (eventDeserializer.readString() as string)
        return (event as TextInput_onCopy_event)
    }
    else if ((kind) === (PeerEventKind.TextInput_onCut)) {
        const event: { kind?: number, nodeId?: PeerEventKind, breakpoints?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.breakpoints = (eventDeserializer.readString() as string)
        return (event as TextInput_onCut_event)
    }
    else if ((kind) === (PeerEventKind.TextInput_onPaste)) {
        const event: { kind?: number, nodeId?: PeerEventKind, content?: any, event?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.content = (eventDeserializer.readString() as string)
        event.event = eventDeserializer.readPasteEvent()
        return (event as TextInput_onPaste_event)
    }
    else if ((kind) === (PeerEventKind.TextInput_showUnit)) {
        const event: { kind?: number, nodeId?: PeerEventKind } = {}
        event.kind = kind
        event.nodeId = nodeId
        return (event as TextInput_showUnit_event)
    }
    else if ((kind) === (PeerEventKind.TextInput_onSecurityStateChange)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = eventDeserializer.readBoolean()
        return (event as TextInput_onSecurityStateChange_event)
    }
    else if ((kind) === (PeerEventKind.TextInput_onWillInsert)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = eventDeserializer.readInsertValue()
        return (event as TextInput_onWillInsert_event)
    }
    else if ((kind) === (PeerEventKind.TextInput_onDidInsert)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = eventDeserializer.readInsertValue()
        return (event as TextInput_onDidInsert_event)
    }
    else if ((kind) === (PeerEventKind.TextInput_onWillDelete)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = eventDeserializer.readDeleteValue()
        return (event as TextInput_onWillDelete_event)
    }
    else if ((kind) === (PeerEventKind.TextInput_onDidDelete)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = eventDeserializer.readDeleteValue()
        return (event as TextInput_onDidDelete_event)
    }
    else if ((kind) === (PeerEventKind.TextInput_customKeyboard)) {
        const event: { kind?: number, nodeId?: PeerEventKind } = {}
        event.kind = kind
        event.nodeId = nodeId
        return (event as TextInput_customKeyboard_event)
    }
    else if ((kind) === (PeerEventKind.TextInput__onChangeEvent_text)) {
        const event: { kind?: number, nodeId?: PeerEventKind, value?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        const value_buf_selector: number = eventDeserializer.readInt8()
        let value_buf: string | Resource | undefined|undefined 
        if (value_buf_selector == 0) {
            value_buf = (eventDeserializer.readString() as string)
        }
        else if (value_buf_selector == 1) {
            value_buf = eventDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for value_buf has to be chosen through deserialisation.")
        }
        event.value = (value_buf as string | Resource)
        return (event as TextInput__onChangeEvent_text_event)
    }
    else if ((kind) === (PeerEventKind.TextPicker_onAccept)) {
        const event: { kind?: number, nodeId?: PeerEventKind, value?: any, index?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.value = (eventDeserializer.readString() as string)
        event.index = (eventDeserializer.readNumber() as number)
        return (event as TextPicker_onAccept_event)
    }
    else if ((kind) === (PeerEventKind.TextPicker_onCancel)) {
        const event: { kind?: number, nodeId?: PeerEventKind } = {}
        event.kind = kind
        event.nodeId = nodeId
        return (event as TextPicker_onCancel_event)
    }
    else if ((kind) === (PeerEventKind.TextPicker_onChange)) {
        const event: { kind?: number, nodeId?: PeerEventKind, value?: any, index?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        const value_buf_selector: number = eventDeserializer.readInt8()
        let value_buf: string | Array<string> | undefined|undefined 
        if (value_buf_selector == 0) {
            value_buf = (eventDeserializer.readString() as string)
        }
        else if (value_buf_selector == 1) {
            const value_buf_u_length: int32 = eventDeserializer.readInt32()
            let value_buf_u: Array<string> = new Array<string>()
            for (let value_buf_u_i = 0; value_buf_u_i < value_buf_u_length; value_buf_u_i++) {
                value_buf_u[value_buf_u_i] = (eventDeserializer.readString() as string)
            }
            value_buf = value_buf_u
        }
        else {
            throw new Error("One of the branches for value_buf has to be chosen through deserialisation.")
        }
        event.value = (value_buf as string | Array<string>)
        const index_buf_selector: number = eventDeserializer.readInt8()
        let index_buf: number | Array<number> | undefined|undefined 
        if (index_buf_selector == 0) {
            index_buf = (eventDeserializer.readNumber() as number)
        }
        else if (index_buf_selector == 1) {
            const index_buf_u_length: int32 = eventDeserializer.readInt32()
            let index_buf_u: Array<number> = new Array<number>()
            for (let index_buf_u_i = 0; index_buf_u_i < index_buf_u_length; index_buf_u_i++) {
                index_buf_u[index_buf_u_i] = (eventDeserializer.readNumber() as number)
            }
            index_buf = index_buf_u
        }
        else {
            throw new Error("One of the branches for index_buf has to be chosen through deserialisation.")
        }
        event.index = (index_buf as number | Array<number>)
        return (event as TextPicker_onChange_event)
    }
    else if ((kind) === (PeerEventKind.TextPicker__onChangeEvent_selected)) {
        const event: { kind?: number, nodeId?: PeerEventKind, selected?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        const selected_buf_selector: number = eventDeserializer.readInt8()
        let selected_buf: number | Array<number> | undefined|undefined 
        if (selected_buf_selector == 0) {
            selected_buf = (eventDeserializer.readNumber() as number)
        }
        else if (selected_buf_selector == 1) {
            const selected_buf_u_length: int32 = eventDeserializer.readInt32()
            let selected_buf_u: Array<number> = new Array<number>()
            for (let selected_buf_u_i = 0; selected_buf_u_i < selected_buf_u_length; selected_buf_u_i++) {
                selected_buf_u[selected_buf_u_i] = (eventDeserializer.readNumber() as number)
            }
            selected_buf = selected_buf_u
        }
        else {
            throw new Error("One of the branches for selected_buf has to be chosen through deserialisation.")
        }
        event.selected = (selected_buf as number | Array<number>)
        return (event as TextPicker__onChangeEvent_selected_event)
    }
    else if ((kind) === (PeerEventKind.TextPicker__onChangeEvent_value)) {
        const event: { kind?: number, nodeId?: PeerEventKind, value?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        const value_buf_selector: number = eventDeserializer.readInt8()
        let value_buf: string | Array<string> | undefined|undefined 
        if (value_buf_selector == 0) {
            value_buf = (eventDeserializer.readString() as string)
        }
        else if (value_buf_selector == 1) {
            const value_buf_u_length: int32 = eventDeserializer.readInt32()
            let value_buf_u: Array<string> = new Array<string>()
            for (let value_buf_u_i = 0; value_buf_u_i < value_buf_u_length; value_buf_u_i++) {
                value_buf_u[value_buf_u_i] = (eventDeserializer.readString() as string)
            }
            value_buf = value_buf_u
        }
        else {
            throw new Error("One of the branches for value_buf has to be chosen through deserialisation.")
        }
        event.value = (value_buf as string | Array<string>)
        return (event as TextPicker__onChangeEvent_value_event)
    }
    else if ((kind) === (PeerEventKind.TextTimer_onTimer)) {
        const event: { kind?: number, nodeId?: PeerEventKind, first?: any, last?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.first = (eventDeserializer.readNumber() as number)
        event.last = (eventDeserializer.readNumber() as number)
        return (event as TextTimer_onTimer_event)
    }
    else if ((kind) === (PeerEventKind.TimePicker_onChange)) {
        const event: { kind?: number, nodeId?: PeerEventKind, value?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.value = eventDeserializer.readTimePickerResult()
        return (event as TimePicker_onChange_event)
    }
    else if ((kind) === (PeerEventKind.TimePicker__onChangeEvent_selected)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = new Date(eventDeserializer.readInt64())
        return (event as TimePicker__onChangeEvent_selected_event)
    }
    else if ((kind) === (PeerEventKind.Toggle_onChange)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = eventDeserializer.readBoolean()
        return (event as Toggle_onChange_event)
    }
    else if ((kind) === (PeerEventKind.Toggle__onChangeEvent_isOn)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = eventDeserializer.readBoolean()
        return (event as Toggle__onChangeEvent_isOn_event)
    }
    else if ((kind) === (PeerEventKind.Video_onStart)) {
        const event: { kind?: number, nodeId?: PeerEventKind } = {}
        event.kind = kind
        event.nodeId = nodeId
        return (event as Video_onStart_event)
    }
    else if ((kind) === (PeerEventKind.Video_onPause)) {
        const event: { kind?: number, nodeId?: PeerEventKind } = {}
        event.kind = kind
        event.nodeId = nodeId
        return (event as Video_onPause_event)
    }
    else if ((kind) === (PeerEventKind.Video_onFinish)) {
        const event: { kind?: number, nodeId?: PeerEventKind } = {}
        event.kind = kind
        event.nodeId = nodeId
        return (event as Video_onFinish_event)
    }
    else if ((kind) === (PeerEventKind.Video_onFullscreenChange)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = eventDeserializer.readFullscreenInfo()
        return (event as Video_onFullscreenChange_event)
    }
    else if ((kind) === (PeerEventKind.Video_onPrepared)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = eventDeserializer.readPreparedInfo()
        return (event as Video_onPrepared_event)
    }
    else if ((kind) === (PeerEventKind.Video_onSeeking)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = eventDeserializer.readPlaybackInfo()
        return (event as Video_onSeeking_event)
    }
    else if ((kind) === (PeerEventKind.Video_onSeeked)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = eventDeserializer.readPlaybackInfo()
        return (event as Video_onSeeked_event)
    }
    else if ((kind) === (PeerEventKind.Video_onUpdate)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = eventDeserializer.readPlaybackInfo()
        return (event as Video_onUpdate_event)
    }
    else if ((kind) === (PeerEventKind.Video_onError)) {
        const event: { kind?: number, nodeId?: PeerEventKind } = {}
        event.kind = kind
        event.nodeId = nodeId
        return (event as Video_onError_event)
    }
    else if ((kind) === (PeerEventKind.Video_onStop)) {
        const event: { kind?: number, nodeId?: PeerEventKind } = {}
        event.kind = kind
        event.nodeId = nodeId
        return (event as Video_onStop_event)
    }
    else if ((kind) === (PeerEventKind.Web_onPageEnd)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = eventDeserializer.readOnPageEndEvent()
        return (event as Web_onPageEnd_event)
    }
    else if ((kind) === (PeerEventKind.Web_onPageBegin)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = eventDeserializer.readOnPageBeginEvent()
        return (event as Web_onPageBegin_event)
    }
    else if ((kind) === (PeerEventKind.Web_onProgressChange)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = eventDeserializer.readOnProgressChangeEvent()
        return (event as Web_onProgressChange_event)
    }
    else if ((kind) === (PeerEventKind.Web_onTitleReceive)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = eventDeserializer.readOnTitleReceiveEvent()
        return (event as Web_onTitleReceive_event)
    }
    else if ((kind) === (PeerEventKind.Web_onGeolocationHide)) {
        const event: { kind?: number, nodeId?: PeerEventKind } = {}
        event.kind = kind
        event.nodeId = nodeId
        return (event as Web_onGeolocationHide_event)
    }
    else if ((kind) === (PeerEventKind.Web_onGeolocationShow)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = eventDeserializer.readOnGeolocationShowEvent()
        return (event as Web_onGeolocationShow_event)
    }
    else if ((kind) === (PeerEventKind.Web_onRequestSelected)) {
        const event: { kind?: number, nodeId?: PeerEventKind } = {}
        event.kind = kind
        event.nodeId = nodeId
        return (event as Web_onRequestSelected_event)
    }
    else if ((kind) === (PeerEventKind.Web_onAlert)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = eventDeserializer.readOnAlertEvent()
        return (event as Web_onAlert_event)
    }
    else if ((kind) === (PeerEventKind.Web_onBeforeUnload)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = eventDeserializer.readOnBeforeUnloadEvent()
        return (event as Web_onBeforeUnload_event)
    }
    else if ((kind) === (PeerEventKind.Web_onConfirm)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = eventDeserializer.readOnConfirmEvent()
        return (event as Web_onConfirm_event)
    }
    else if ((kind) === (PeerEventKind.Web_onPrompt)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = eventDeserializer.readOnPromptEvent()
        return (event as Web_onPrompt_event)
    }
    else if ((kind) === (PeerEventKind.Web_onConsole)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = eventDeserializer.readOnConsoleEvent()
        return (event as Web_onConsole_event)
    }
    else if ((kind) === (PeerEventKind.Web_onErrorReceive)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = eventDeserializer.readOnErrorReceiveEvent()
        return (event as Web_onErrorReceive_event)
    }
    else if ((kind) === (PeerEventKind.Web_onHttpErrorReceive)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = eventDeserializer.readOnHttpErrorReceiveEvent()
        return (event as Web_onHttpErrorReceive_event)
    }
    else if ((kind) === (PeerEventKind.Web_onDownloadStart)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = eventDeserializer.readOnDownloadStartEvent()
        return (event as Web_onDownloadStart_event)
    }
    else if ((kind) === (PeerEventKind.Web_onRefreshAccessedHistory)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = eventDeserializer.readOnRefreshAccessedHistoryEvent()
        return (event as Web_onRefreshAccessedHistory_event)
    }
    else if ((kind) === (PeerEventKind.Web_onUrlLoadIntercept)) {
        const event: { kind?: number, nodeId?: PeerEventKind, event?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        const event_buf_runtimeType = (eventDeserializer.readInt8() as int32)
        let event_buf: { data: string | WebResourceRequest } | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (event_buf_runtimeType))
        {
            const event_buf__data_buf_selector: number = eventDeserializer.readInt8()
            let event_buf__data_buf: string | WebResourceRequest | undefined|undefined 
            if (event_buf__data_buf_selector == 0) {
                event_buf__data_buf = (eventDeserializer.readString() as string)
            }
            else if (event_buf__data_buf_selector == 1) {
                event_buf__data_buf = (eventDeserializer.readWebResourceRequest() as WebResourceRequest)
            }
            else {
                throw new Error("One of the branches for event_buf__data_buf has to be chosen through deserialisation.")
            }
            const event_buf__data: string | WebResourceRequest = (event_buf__data_buf as string | WebResourceRequest)
            event_buf = ({data: event_buf__data} as { data: string | WebResourceRequest })
        }
        event.event = event_buf
        return (event as Web_onUrlLoadIntercept_event)
    }
    else if ((kind) === (PeerEventKind.Web_onSslErrorReceive)) {
        const event: { kind?: number, nodeId?: PeerEventKind, event?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        const event_buf_runtimeType = (eventDeserializer.readInt8() as int32)
        let event_buf: { handler: Function, error: Object } | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (event_buf_runtimeType))
        {
            const event_buf__handler: Function = (eventDeserializer.readFunction() as Function)
            const event_buf__error: Object = (eventDeserializer.readCustomObject("Object") as Object)
            event_buf = ({handler: event_buf__handler, error: event_buf__error} as { handler: Function, error: Object })
        }
        event.event = event_buf
        return (event as Web_onSslErrorReceive_event)
    }
    else if ((kind) === (PeerEventKind.Web_onRenderExited0)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = eventDeserializer.readOnRenderExitedEvent()
        return (event as Web_onRenderExited0_event)
    }
    else if ((kind) === (PeerEventKind.Web_onRenderExited1)) {
        const event: { kind?: number, nodeId?: PeerEventKind, event?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        const event_buf_runtimeType = (eventDeserializer.readInt8() as int32)
        let event_buf: { detail: Object } | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (event_buf_runtimeType))
        {
            const event_buf__detail: Object = (eventDeserializer.readCustomObject("Object") as Object)
            event_buf = ({detail: event_buf__detail} as { detail: Object })
        }
        event.event = event_buf
        return (event as Web_onRenderExited1_event)
    }
    else if ((kind) === (PeerEventKind.Web_onShowFileSelector)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = eventDeserializer.readOnShowFileSelectorEvent()
        return (event as Web_onShowFileSelector_event)
    }
    else if ((kind) === (PeerEventKind.Web_onFileSelectorShow)) {
        const event: { kind?: number, nodeId?: PeerEventKind, event?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        const event_buf_runtimeType = (eventDeserializer.readInt8() as int32)
        let event_buf: { callback_: Function, fileSelector: Object } | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (event_buf_runtimeType))
        {
            const event_buf__callback_: Function = (eventDeserializer.readFunction() as Function)
            const event_buf__fileSelector: Object = (eventDeserializer.readCustomObject("Object") as Object)
            event_buf = ({callback_: event_buf__callback_, fileSelector: event_buf__fileSelector} as { callback_: Function, fileSelector: Object })
        }
        event.event = event_buf
        return (event as Web_onFileSelectorShow_event)
    }
    else if ((kind) === (PeerEventKind.Web_onResourceLoad)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = eventDeserializer.readOnResourceLoadEvent()
        return (event as Web_onResourceLoad_event)
    }
    else if ((kind) === (PeerEventKind.Web_onFullScreenExit)) {
        const event: { kind?: number, nodeId?: PeerEventKind } = {}
        event.kind = kind
        event.nodeId = nodeId
        return (event as Web_onFullScreenExit_event)
    }
    else if ((kind) === (PeerEventKind.Web_onFullScreenEnter)) {
        const event: { kind?: number, nodeId?: PeerEventKind, event?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.event = eventDeserializer.readFullScreenEnterEvent()
        return (event as Web_onFullScreenEnter_event)
    }
    else if ((kind) === (PeerEventKind.Web_onScaleChange)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = eventDeserializer.readOnScaleChangeEvent()
        return (event as Web_onScaleChange_event)
    }
    else if ((kind) === (PeerEventKind.Web_onHttpAuthRequest)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = eventDeserializer.readOnHttpAuthRequestEvent()
        return (event as Web_onHttpAuthRequest_event)
    }
    else if ((kind) === (PeerEventKind.Web_onInterceptRequest)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = eventDeserializer.readOnInterceptRequestEvent()
        return (event as Web_onInterceptRequest_event)
    }
    else if ((kind) === (PeerEventKind.Web_onPermissionRequest)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = eventDeserializer.readOnPermissionRequestEvent()
        return (event as Web_onPermissionRequest_event)
    }
    else if ((kind) === (PeerEventKind.Web_onScreenCaptureRequest)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = eventDeserializer.readOnScreenCaptureRequestEvent()
        return (event as Web_onScreenCaptureRequest_event)
    }
    else if ((kind) === (PeerEventKind.Web_onContextMenuShow)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = eventDeserializer.readOnContextMenuShowEvent()
        return (event as Web_onContextMenuShow_event)
    }
    else if ((kind) === (PeerEventKind.Web_onContextMenuHide)) {
        const event: { kind?: number, nodeId?: PeerEventKind } = {}
        event.kind = kind
        event.nodeId = nodeId
        return (event as Web_onContextMenuHide_event)
    }
    else if ((kind) === (PeerEventKind.Web_onSearchResultReceive)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = eventDeserializer.readOnSearchResultReceiveEvent()
        return (event as Web_onSearchResultReceive_event)
    }
    else if ((kind) === (PeerEventKind.Web_onScroll)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = eventDeserializer.readOnScrollEvent()
        return (event as Web_onScroll_event)
    }
    else if ((kind) === (PeerEventKind.Web_onSslErrorEventReceive)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = eventDeserializer.readOnSslErrorEventReceiveEvent()
        return (event as Web_onSslErrorEventReceive_event)
    }
    else if ((kind) === (PeerEventKind.Web_onSslErrorEvent)) {
        const event: { kind?: number, nodeId?: PeerEventKind, sslErrorEvent?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.sslErrorEvent = eventDeserializer.readSslErrorEvent()
        return (event as Web_onSslErrorEvent_event)
    }
    else if ((kind) === (PeerEventKind.Web_onClientAuthenticationRequest)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = eventDeserializer.readOnClientAuthenticationEvent()
        return (event as Web_onClientAuthenticationRequest_event)
    }
    else if ((kind) === (PeerEventKind.Web_onWindowNew)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = eventDeserializer.readOnWindowNewEvent()
        return (event as Web_onWindowNew_event)
    }
    else if ((kind) === (PeerEventKind.Web_onWindowExit)) {
        const event: { kind?: number, nodeId?: PeerEventKind } = {}
        event.kind = kind
        event.nodeId = nodeId
        return (event as Web_onWindowExit_event)
    }
    else if ((kind) === (PeerEventKind.Web_onInterceptKeyEvent)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = (eventDeserializer.readKeyEvent() as KeyEvent)
        return (event as Web_onInterceptKeyEvent_event)
    }
    else if ((kind) === (PeerEventKind.Web_onTouchIconUrlReceived)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = eventDeserializer.readOnTouchIconUrlReceivedEvent()
        return (event as Web_onTouchIconUrlReceived_event)
    }
    else if ((kind) === (PeerEventKind.Web_onFaviconReceived)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = eventDeserializer.readOnFaviconReceivedEvent()
        return (event as Web_onFaviconReceived_event)
    }
    else if ((kind) === (PeerEventKind.Web_onPageVisible)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = eventDeserializer.readOnPageVisibleEvent()
        return (event as Web_onPageVisible_event)
    }
    else if ((kind) === (PeerEventKind.Web_onDataResubmitted)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = eventDeserializer.readOnDataResubmittedEvent()
        return (event as Web_onDataResubmitted_event)
    }
    else if ((kind) === (PeerEventKind.Web_onAudioStateChanged)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = eventDeserializer.readOnAudioStateChangedEvent()
        return (event as Web_onAudioStateChanged_event)
    }
    else if ((kind) === (PeerEventKind.Web_onFirstContentfulPaint)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = eventDeserializer.readOnFirstContentfulPaintEvent()
        return (event as Web_onFirstContentfulPaint_event)
    }
    else if ((kind) === (PeerEventKind.Web_onFirstMeaningfulPaint)) {
        const event: { kind?: number, nodeId?: PeerEventKind, firstMeaningfulPaint?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.firstMeaningfulPaint = eventDeserializer.readFirstMeaningfulPaint()
        return (event as Web_onFirstMeaningfulPaint_event)
    }
    else if ((kind) === (PeerEventKind.Web_onLargestContentfulPaint)) {
        const event: { kind?: number, nodeId?: PeerEventKind, largestContentfulPaint?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.largestContentfulPaint = eventDeserializer.readLargestContentfulPaint()
        return (event as Web_onLargestContentfulPaint_event)
    }
    else if ((kind) === (PeerEventKind.Web_onLoadIntercept)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = eventDeserializer.readOnLoadInterceptEvent()
        return (event as Web_onLoadIntercept_event)
    }
    else if ((kind) === (PeerEventKind.Web_onControllerAttached)) {
        const event: { kind?: number, nodeId?: PeerEventKind } = {}
        event.kind = kind
        event.nodeId = nodeId
        return (event as Web_onControllerAttached_event)
    }
    else if ((kind) === (PeerEventKind.Web_onOverScroll)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = eventDeserializer.readOnOverScrollEvent()
        return (event as Web_onOverScroll_event)
    }
    else if ((kind) === (PeerEventKind.Web_onSafeBrowsingCheckResult)) {
        const event: { kind?: number, nodeId?: PeerEventKind, threatType?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.threatType = (eventDeserializer.readInt32() as ThreatType)
        return (event as Web_onSafeBrowsingCheckResult_event)
    }
    else if ((kind) === (PeerEventKind.Web_onNavigationEntryCommitted)) {
        const event: { kind?: number, nodeId?: PeerEventKind, loadCommittedDetails?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.loadCommittedDetails = eventDeserializer.readLoadCommittedDetails()
        return (event as Web_onNavigationEntryCommitted_event)
    }
    else if ((kind) === (PeerEventKind.Web_onIntelligentTrackingPreventionResult)) {
        const event: { kind?: number, nodeId?: PeerEventKind, details?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.details = eventDeserializer.readIntelligentTrackingPreventionDetails()
        return (event as Web_onIntelligentTrackingPreventionResult_event)
    }
    else if ((kind) === (PeerEventKind.Web_onNativeEmbedLifecycleChange)) {
        const event: { kind?: number, nodeId?: PeerEventKind, event?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.event = eventDeserializer.readNativeEmbedDataInfo()
        return (event as Web_onNativeEmbedLifecycleChange_event)
    }
    else if ((kind) === (PeerEventKind.Web_onNativeEmbedVisibilityChange)) {
        const event: { kind?: number, nodeId?: PeerEventKind, nativeEmbedVisibilityInfo?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.nativeEmbedVisibilityInfo = eventDeserializer.readNativeEmbedVisibilityInfo()
        return (event as Web_onNativeEmbedVisibilityChange_event)
    }
    else if ((kind) === (PeerEventKind.Web_onNativeEmbedGestureEvent)) {
        const event: { kind?: number, nodeId?: PeerEventKind, event?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.event = eventDeserializer.readNativeEmbedTouchInfo()
        return (event as Web_onNativeEmbedGestureEvent_event)
    }
    else if ((kind) === (PeerEventKind.Web_onOverrideUrlLoading)) {
        const event: { kind?: number, nodeId?: PeerEventKind, webResourceRequest?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.webResourceRequest = (eventDeserializer.readWebResourceRequest() as WebResourceRequest)
        return (event as Web_onOverrideUrlLoading_event)
    }
    else if ((kind) === (PeerEventKind.Web_onRenderProcessNotResponding)) {
        const event: { kind?: number, nodeId?: PeerEventKind, data?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.data = eventDeserializer.readRenderProcessNotRespondingData()
        return (event as Web_onRenderProcessNotResponding_event)
    }
    else if ((kind) === (PeerEventKind.Web_onRenderProcessResponding)) {
        const event: { kind?: number, nodeId?: PeerEventKind } = {}
        event.kind = kind
        event.nodeId = nodeId
        return (event as Web_onRenderProcessResponding_event)
    }
    else if ((kind) === (PeerEventKind.Web_onViewportFitChanged)) {
        const event: { kind?: number, nodeId?: PeerEventKind, viewportFit?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.viewportFit = (eventDeserializer.readInt32() as ViewportFit)
        return (event as Web_onViewportFitChanged_event)
    }
    else if ((kind) === (PeerEventKind.Web_onInterceptKeyboardAttach)) {
        const event: { kind?: number, nodeId?: PeerEventKind, keyboardCallbackInfo?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.keyboardCallbackInfo = eventDeserializer.readWebKeyboardCallbackInfo()
        return (event as Web_onInterceptKeyboardAttach_event)
    }
    else if ((kind) === (PeerEventKind.Web_onAdsBlocked)) {
        const event: { kind?: number, nodeId?: PeerEventKind, details?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.details = eventDeserializer.readAdsBlockedDetails()
        return (event as Web_onAdsBlocked_event)
    }
    else if ((kind) === (PeerEventKind.Web_bindSelectionMenu)) {
        const event: { kind?: number, nodeId?: PeerEventKind } = {}
        event.kind = kind
        event.nodeId = nodeId
        return (event as Web_bindSelectionMenu_event)
    }
    else if ((kind) === (PeerEventKind.XComponent_onLoad)) {
        const event: { kind?: number, nodeId?: PeerEventKind, event?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        const event_buf_runtimeType = (eventDeserializer.readInt8() as int32)
        let event_buf: Object | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (event_buf_runtimeType))
        {
            event_buf = (eventDeserializer.readCustomObject("Object") as Object)
        }
        event.event = event_buf
        return (event as XComponent_onLoad_event)
    }
    else if ((kind) === (PeerEventKind.XComponent_onDestroy)) {
        const event: { kind?: number, nodeId?: PeerEventKind } = {}
        event.kind = kind
        event.nodeId = nodeId
        return (event as XComponent_onDestroy_event)
    }
    else if ((kind) === (PeerEventKind.SideBarContainer_onChange)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = eventDeserializer.readBoolean()
        return (event as SideBarContainer_onChange_event)
    }
    else if ((kind) === (PeerEventKind.SideBarContainer__onChangeEvent_showSideBar)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = eventDeserializer.readBoolean()
        return (event as SideBarContainer__onChangeEvent_showSideBar_event)
    }
    else if ((kind) === (PeerEventKind.WaterFlow_onReachStart)) {
        const event: { kind?: number, nodeId?: PeerEventKind } = {}
        event.kind = kind
        event.nodeId = nodeId
        return (event as WaterFlow_onReachStart_event)
    }
    else if ((kind) === (PeerEventKind.WaterFlow_onReachEnd)) {
        const event: { kind?: number, nodeId?: PeerEventKind } = {}
        event.kind = kind
        event.nodeId = nodeId
        return (event as WaterFlow_onReachEnd_event)
    }
    else if ((kind) === (PeerEventKind.WaterFlow_onScrollFrameBegin)) {
        const event: { kind?: number, nodeId?: PeerEventKind, offset?: any, state?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.offset = (eventDeserializer.readNumber() as number)
        event.state = (eventDeserializer.readInt32() as ScrollState)
        return (event as WaterFlow_onScrollFrameBegin_event)
    }
    else if ((kind) === (PeerEventKind.WaterFlow_onScrollIndex)) {
        const event: { kind?: number, nodeId?: PeerEventKind, first?: any, last?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.first = (eventDeserializer.readNumber() as number)
        event.last = (eventDeserializer.readNumber() as number)
        return (event as WaterFlow_onScrollIndex_event)
    }
    else if ((kind) === (PeerEventKind.UIExtensionComponent_onRemoteReady)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = (eventDeserializer.readUIExtensionProxy() as UIExtensionProxy)
        return (event as UIExtensionComponent_onRemoteReady_event)
    }
    else if ((kind) === (PeerEventKind.UIExtensionComponent_onResult)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        const parameter_buf_code: number = (eventDeserializer.readNumber() as number)
        const parameter_buf_want_buf_runtimeType = (eventDeserializer.readInt8() as int32)
        let parameter_buf_want_buf: Want | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (parameter_buf_want_buf_runtimeType))
        {
            parameter_buf_want_buf = eventDeserializer.readWant()
        }
        const parameter_buf_want: undefined | Want = parameter_buf_want_buf
        event.parameter = ({code: parameter_buf_code, want: parameter_buf_want} as { code: number, want?: Want })
        return (event as UIExtensionComponent_onResult_event)
    }
    else if ((kind) === (PeerEventKind.UIExtensionComponent_onRelease)) {
        const event: { kind?: number, nodeId?: PeerEventKind, index?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.index = (eventDeserializer.readNumber() as number)
        return (event as UIExtensionComponent_onRelease_event)
    }
    else if ((kind) === (PeerEventKind.UIExtensionComponent_onError)) {
        const event: { kind?: number, nodeId?: PeerEventKind, err?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.err = eventDeserializer.readBusinessError()
        return (event as UIExtensionComponent_onError_event)
    }
    else if ((kind) === (PeerEventKind.UIExtensionComponent_onTerminated)) {
        const event: { kind?: number, nodeId?: PeerEventKind, parameter?: any } = {}
        event.kind = kind
        event.nodeId = nodeId
        event.parameter = eventDeserializer.readTerminationInfo()
        return (event as UIExtensionComponent_onTerminated_event)
    }
    else {
        throw `Unknown kind ${kind}`
    }
}
export interface PeerEventsProperties {
    AbilityComponent_onConnect?: (() => void)
    AbilityComponent_onDisconnect?: (() => void)
    AlphabetIndexer_onSelected?: ((index: number) => void)
    AlphabetIndexer_onSelect?: OnAlphabetIndexerSelectCallback
    AlphabetIndexer_onRequestPopupData?: OnAlphabetIndexerRequestPopupDataCallback
    AlphabetIndexer_onPopupSelect?: OnAlphabetIndexerPopupSelectCallback
    AlphabetIndexer__onChangeEvent_selected?: ((index: number) => void)
    Animator_onStart?: (() => void)
    Animator_onPause?: (() => void)
    Animator_onRepeat?: (() => void)
    Animator_onCancel?: (() => void)
    Animator_onFinish?: (() => void)
    Animator_onFrame?: ((index: number) => void)
    Calendar_onSelectChange?: ((event: CalendarSelectedDate) => void)
    Calendar_onRequestData?: ((event: CalendarRequestedData) => void)
    CalendarPicker_onChange?: ((parameter: Date) => void)
    Canvas_onReady?: VoidCallback
    Checkbox_onChange?: OnCheckboxChangeCallback
    Checkbox__onChangeEvent_select?: ((parameter: boolean) => void)
    CheckboxGroup_onChange?: OnCheckboxGroupChangeCallback
    CheckboxGroup__onChangeEvent_selectAll?: ((parameter: boolean) => void)
    CommonMethod_onChildTouchTest?: ((value: Array<TouchTestInfo>) => TouchResult)
    CommonMethod_onClick0?: ((event: ClickEvent) => void)
    CommonMethod_onClick1?: ((event: ClickEvent) => void)
    CommonMethod_onHover?: ((isHover: boolean, event: HoverEvent) => void)
    CommonMethod_onAccessibilityHover?: AccessibilityCallback
    CommonMethod_onMouse?: ((event: MouseEvent) => void)
    CommonMethod_onTouch?: ((event: TouchEvent) => void)
    CommonMethod_onKeyEvent?: ((event: KeyEvent) => void)
    CommonMethod_onKeyPreIme?: ((parameter: KeyEvent) => boolean)
    CommonMethod_onFocus?: (() => void)
    CommonMethod_onBlur?: (() => void)
    CommonMethod_onAppear?: (() => void)
    CommonMethod_onDisAppear?: (() => void)
    CommonMethod_onAttach?: (() => void)
    CommonMethod_onDetach?: (() => void)
    CommonMethod_onAreaChange?: ((oldValue: Area, newValue: Area) => void)
    CommonMethod_onDragStart?: ((event: DragEvent, extraParams?: string) => CustomBuilder | DragItemInfo)
    CommonMethod_onDragEnter?: ((event: DragEvent, extraParams?: string) => void)
    CommonMethod_onDragMove?: ((event: DragEvent, extraParams?: string) => void)
    CommonMethod_onDragLeave?: ((event: DragEvent, extraParams?: string) => void)
    CommonMethod_onDrop?: ((event: DragEvent, extraParams?: string) => void)
    CommonMethod_onDragEnd?: ((event: DragEvent, extraParams?: string) => void)
    CommonMethod_onPreDrag?: ((parameter: PreDragStatus) => void)
    CommonMethod_accessibilityVirtualNode?: CustomBuilder
    CommonMethod_onGestureJudgeBegin?: ((gestureInfo: GestureInfo, event: BaseGestureEvent) => GestureJudgeResult)
    CommonMethod_onGestureRecognizerJudgeBegin0?: GestureRecognizerJudgeBeginCallback
    CommonMethod_onGestureRecognizerJudgeBegin1?: GestureRecognizerJudgeBeginCallback
    CommonMethod_shouldBuiltInRecognizerParallelWith?: ShouldBuiltInRecognizerParallelWithCallback
    CommonMethod_onTouchIntercept?: ((parameter: TouchEvent) => HitTestMode)
    CommonMethod_onSizeChange?: SizeChangeCallback
    CommonMethod_background?: CustomBuilder
    CommonMethod_bindContextMenu0?: CustomBuilder
    CommonMethod_bindContextMenu1?: CustomBuilder
    CommonMethod_bindContentCover0?: CustomBuilder
    CommonMethod_bindContentCover1?: CustomBuilder
    CommonMethod_bindSheet?: CustomBuilder
    CommonMethod_onVisibleAreaChange?: VisibleAreaChangeCallback
    ScrollableCommonMethod_onScroll?: ((first: number, last: number) => void)
    ScrollableCommonMethod_onDidScroll?: ScrollOnScrollCallback
    ScrollableCommonMethod_onReachStart?: (() => void)
    ScrollableCommonMethod_onReachEnd?: (() => void)
    ScrollableCommonMethod_onScrollStart?: (() => void)
    ScrollableCommonMethod_onScrollStop?: (() => void)
    Counter_onInc?: VoidCallback
    Counter_onDec?: VoidCallback
    DatePicker_onChange?: ((value: DatePickerResult) => void)
    DatePicker_onDateChange?: ((parameter: Date) => void)
    DatePicker__onChangeEvent_selected?: ((parameter: Date) => void)
    EmbeddedComponent_onTerminated?: ((parameter: TerminationInfo) => void)
    EmbeddedComponent_onError?: ErrorCallback
    FolderStack_onFolderStateChange?: OnFoldStatusChangeCallback
    FolderStack_onHoverStatusChange?: OnHoverStatusChangeCallback
    FormComponent_onAcquired?: ((parameter: FormCallbackInfo) => void)
    FormComponent_onError?: ((info: { errcode: number, msg: string }) => void)
    FormComponent_onRouter?: ((info: any) => void)
    FormComponent_onUninstall?: ((parameter: FormCallbackInfo) => void)
    FormComponent_onLoad?: (() => void)
    Gauge_description?: CustomBuilder
    Grid_onScrollBarUpdate?: ((index: number, offset: number) => ComputedBarAttribute)
    Grid_onScrollIndex?: ((first: number, last: number) => void)
    Grid_onItemDragStart?: ((event: ItemDragInfo, itemIndex: number) => CustomBuilder)
    Grid_onItemDragEnter?: ((event: ItemDragInfo) => void)
    Grid_onItemDragMove?: ((event: ItemDragInfo, itemIndex: number, insertIndex: number) => void)
    Grid_onItemDragLeave?: ((event: ItemDragInfo, itemIndex: number) => void)
    Grid_onItemDrop?: ((event: ItemDragInfo, itemIndex: number, insertIndex: number, isSuccess: boolean) => void)
    Grid_onScroll?: ((first: number, last: number) => void)
    Grid_onReachStart?: (() => void)
    Grid_onReachEnd?: (() => void)
    Grid_onScrollStart?: (() => void)
    Grid_onScrollStop?: (() => void)
    Grid_onScrollFrameBegin?: ((offset: number, state: ScrollState) => { offsetRemain: number })
    GridItem_onSelect?: ((parameter: boolean) => void)
    GridItem__onChangeEvent_selected?: ((parameter: boolean) => void)
    GridRow_onBreakpointChange?: ((breakpoints: string) => void)
    Image_onComplete?: ((event?: { width: number, height: number, componentWidth: number, componentHeight: number, loadingStatus: number, contentWidth: number, contentHeight: number, contentOffsetX: number, contentOffsetY: number }) => void)
    Image_onError?: ImageErrorCallback
    Image_onFinish?: (() => void)
    ImageAnimator_onStart?: (() => void)
    ImageAnimator_onPause?: (() => void)
    ImageAnimator_onRepeat?: (() => void)
    ImageAnimator_onCancel?: (() => void)
    ImageAnimator_onFinish?: (() => void)
    ImageSpan_onComplete?: ImageCompleteCallback
    ImageSpan_onError?: ImageErrorCallback
    List_onScroll?: ((first: number, last: number) => void)
    List_onScrollIndex?: ((start: number, end: number, center: number) => void)
    List_onScrollVisibleContentChange?: OnScrollVisibleContentChangeCallback
    List_onReachStart?: (() => void)
    List_onReachEnd?: (() => void)
    List_onScrollStart?: (() => void)
    List_onScrollStop?: (() => void)
    List_onItemDelete?: ((index: number) => boolean)
    List_onItemMove?: ((from: number, to: number) => boolean)
    List_onItemDragStart?: ((event: ItemDragInfo, itemIndex: number) => CustomBuilder)
    List_onItemDragEnter?: ((event: ItemDragInfo) => void)
    List_onItemDragMove?: ((event: ItemDragInfo, itemIndex: number, insertIndex: number) => void)
    List_onItemDragLeave?: ((event: ItemDragInfo, itemIndex: number) => void)
    List_onItemDrop?: ((event: ItemDragInfo, itemIndex: number, insertIndex: number, isSuccess: boolean) => void)
    List_onScrollFrameBegin?: ((offset: number, state: ScrollState) => { offsetRemain: number })
    ListItem_onSelect?: ((parameter: boolean) => void)
    ListItem__onChangeEvent_selected?: ((parameter: boolean) => void)
    LocationButton_onClick?: ((event: ClickEvent, result: LocationButtonOnClickResult) => void)
    Marquee_onStart?: (() => void)
    Marquee_onBounce?: (() => void)
    Marquee_onFinish?: (() => void)
    MenuItem_onChange?: ((parameter: boolean) => void)
    MenuItem__onChangeEvent_selected?: ((parameter: boolean) => void)
    NavDestination_onShown?: (() => void)
    NavDestination_onHidden?: (() => void)
    NavDestination_onBackPressed?: (() => boolean)
    NavDestination_onReady?: ((parameter: NavDestinationContext) => void)
    NavDestination_onWillAppear?: (() => void)
    NavDestination_onWillDisappear?: (() => void)
    NavDestination_onWillShow?: (() => void)
    NavDestination_onWillHide?: (() => void)
    NavRouter_onStateChange?: ((parameter: boolean) => void)
    Panel_onChange?: ((width: number, height: number, mode: PanelMode) => void)
    Panel_onHeightChange?: ((index: number) => void)
    Panel__onChangeEvent_mode?: ((mode: PanelMode) => void)
    PasteButton_onClick?: ((event: ClickEvent, result: PasteButtonOnClickResult) => void)
    PatternLock_onPatternComplete?: ((input: Array<number>) => void)
    PatternLock_onDotConnect?: ((index: number) => void)
    PluginComponent_onComplete?: VoidCallback
    PluginComponent_onError?: PluginErrorCallback
    Radio_onChange?: ((parameter: boolean) => void)
    Radio__onChangeEvent_checked?: ((parameter: boolean) => void)
    Rating_onChange?: ((index: number) => void)
    Rating__onChangeEvent_rating?: ((index: number) => void)
    Refresh_onStateChange?: ((state: RefreshStatus) => void)
    Refresh_onRefreshing?: (() => void)
    Refresh_onOffsetChange?: ((index: number) => void)
    Refresh__onChangeEvent_refreshing?: ((parameter: boolean) => void)
    RichEditor_onReady?: (() => void)
    RichEditor_onSelect?: ((parameter: RichEditorSelection) => void)
    RichEditor_onSelectionChange?: ((parameter: RichEditorRange) => void)
    RichEditor_aboutToIMEInput?: ((parameter: RichEditorInsertValue) => boolean)
    RichEditor_onIMEInputComplete?: ((parameter: RichEditorTextSpanResult) => void)
    RichEditor_onDidIMEInput?: ((parameter: TextRange) => void)
    RichEditor_aboutToDelete?: ((parameter: RichEditorDeleteValue) => boolean)
    RichEditor_onDeleteComplete?: (() => void)
    RichEditor_onPaste?: PasteEventCallback
    RichEditor_onEditingChange?: ((parameter: boolean) => void)
    RichEditor_onSubmit?: SubmitCallback
    RichEditor_onWillChange?: ((parameter: RichEditorChangeValue) => boolean)
    RichEditor_onDidChange?: OnDidChangeCallback
    RichEditor_onCut?: ((parameter: CutEvent) => void)
    RichEditor_onCopy?: ((parameter: CopyEvent) => void)
    RichEditor_bindSelectionMenu?: CustomBuilder
    RichEditor_customKeyboard?: CustomBuilder
    RichText_onStart?: (() => void)
    RichText_onComplete?: (() => void)
    SaveButton_onClick?: ((event: ClickEvent, result: SaveButtonOnClickResult) => void)
    Scroll_onScroll?: ((first: number, last: number) => void)
    Scroll_onDidScroll?: ScrollOnScrollCallback
    Scroll_onScrollEdge?: OnScrollEdgeCallback
    Scroll_onScrollStart?: VoidCallback
    Scroll_onScrollEnd?: (() => void)
    Scroll_onScrollStop?: VoidCallback
    Scroll_onScrollFrameBegin?: OnScrollFrameBeginCallback
    Search_onEditChange?: ((parameter: boolean) => void)
    Search_onSubmit0?: ((breakpoints: string) => void)
    Search_onSubmit1?: SearchSubmitCallback
    Search_onChange?: EditableTextOnChangeCallback
    Search_onTextSelectionChange?: OnTextSelectionChangeCallback
    Search_onContentScroll?: OnContentScrollCallback
    Search_onCopy?: ((breakpoints: string) => void)
    Search_onCut?: ((breakpoints: string) => void)
    Search_onPaste?: OnPasteCallback
    Search_onWillInsert?: ((parameter: InsertValue) => boolean)
    Search_onDidInsert?: ((parameter: InsertValue) => void)
    Search_onWillDelete?: ((parameter: DeleteValue) => boolean)
    Search_onDidDelete?: ((parameter: DeleteValue) => void)
    Search_customKeyboard?: CustomBuilder
    Search__onChangeEvent_value?: ((breakpoints: string) => void)
    Select_onSelect?: ((index: number, value: string) => void)
    Select__onChangeEvent_selected?: ((selected: number | Resource) => void)
    Select__onChangeEvent_value?: ((value: ResourceStr) => void)
    Slider_onChange?: ((value: number, mode: SliderChangeMode) => void)
    Slider__onChangeEvent_value?: ((index: number) => void)
    Stepper_onFinish?: (() => void)
    Stepper_onSkip?: (() => void)
    Stepper_onChange?: ((first: number, last: number) => void)
    Stepper_onNext?: ((first: number, last: number) => void)
    Stepper_onPrevious?: ((first: number, last: number) => void)
    Stepper__onChangeEvent_index?: ((index: number) => void)
    Swiper_onChange?: ((index: number) => void)
    Swiper_onAnimationStart?: OnSwiperAnimationStartCallback
    Swiper_onAnimationEnd?: OnSwiperAnimationEndCallback
    Swiper_onGestureSwipe?: OnSwiperGestureSwipeCallback
    Swiper_onContentDidScroll?: ContentDidScrollCallback
    Swiper__onChangeEvent_index?: ((index: number) => void)
    IndicatorComponent_onChange?: ((index: number) => void)
    Tabs_onChange?: ((index: number) => void)
    Tabs_onTabBarClick?: ((index: number) => void)
    Tabs_onAnimationStart?: OnTabsAnimationStartCallback
    Tabs_onAnimationEnd?: OnTabsAnimationEndCallback
    Tabs_onGestureSwipe?: OnTabsGestureSwipeCallback
    Tabs_customContentTransition?: TabsCustomContentTransitionCallback
    Tabs_onContentWillChange?: OnTabsContentWillChangeCallback
    Tabs__onChangeEvent_index?: ((index: number) => void)
    TabContent_onWillShow?: VoidCallback
    TabContent_onWillHide?: VoidCallback
    Text_onCopy?: ((breakpoints: string) => void)
    Text_onTextSelectionChange?: ((first: number, last: number) => void)
    Text_bindSelectionMenu?: CustomBuilder
    TextArea_onSubmit0?: ((enterKey: EnterKeyType) => void)
    TextArea_onSubmit1?: TextAreaSubmitCallback
    TextArea_onChange?: EditableTextOnChangeCallback
    TextArea_onTextSelectionChange?: ((first: number, last: number) => void)
    TextArea_onContentScroll?: ((first: number, last: number) => void)
    TextArea_onEditChange?: ((parameter: boolean) => void)
    TextArea_onCopy?: ((breakpoints: string) => void)
    TextArea_onCut?: ((breakpoints: string) => void)
    TextArea_onPaste?: ((value: string, event: PasteEvent) => void)
    TextArea_onWillInsert?: ((parameter: InsertValue) => boolean)
    TextArea_onDidInsert?: ((parameter: InsertValue) => void)
    TextArea_onWillDelete?: ((parameter: DeleteValue) => boolean)
    TextArea_onDidDelete?: ((parameter: DeleteValue) => void)
    TextArea_customKeyboard?: CustomBuilder
    TextArea__onChangeEvent_text?: ((value: ResourceStr) => void)
    TextClock_onDateChange?: ((index: number) => void)
    TextInput_onEditChanged?: ((parameter: boolean) => void)
    TextInput_onEditChange?: ((parameter: boolean) => void)
    TextInput_onSubmit?: OnSubmitCallback
    TextInput_onChange?: EditableTextOnChangeCallback
    TextInput_onTextSelectionChange?: OnTextSelectionChangeCallback
    TextInput_onContentScroll?: OnContentScrollCallback
    TextInput_onCopy?: ((breakpoints: string) => void)
    TextInput_onCut?: ((breakpoints: string) => void)
    TextInput_onPaste?: OnPasteCallback
    TextInput_showUnit?: CustomBuilder
    TextInput_onSecurityStateChange?: ((parameter: boolean) => void)
    TextInput_onWillInsert?: ((parameter: InsertValue) => boolean)
    TextInput_onDidInsert?: ((parameter: InsertValue) => void)
    TextInput_onWillDelete?: ((parameter: DeleteValue) => boolean)
    TextInput_onDidDelete?: ((parameter: DeleteValue) => void)
    TextInput_customKeyboard?: CustomBuilder
    TextInput__onChangeEvent_text?: ((value: ResourceStr) => void)
    TextPicker_onAccept?: ((value: string, index: number) => void)
    TextPicker_onCancel?: (() => void)
    TextPicker_onChange?: ((value: string | Array<string>, index: number | Array<number>) => void)
    TextPicker__onChangeEvent_selected?: ((selected: number | Array<number>) => void)
    TextPicker__onChangeEvent_value?: ((value: string | Array<string>) => void)
    TextTimer_onTimer?: ((first: number, last: number) => void)
    TimePicker_onChange?: ((value: TimePickerResult) => void)
    TimePicker__onChangeEvent_selected?: ((parameter: Date) => void)
    Toggle_onChange?: ((parameter: boolean) => void)
    Toggle__onChangeEvent_isOn?: ((parameter: boolean) => void)
    Video_onStart?: VoidCallback
    Video_onPause?: VoidCallback
    Video_onFinish?: VoidCallback
    Video_onFullscreenChange?: ((parameter: FullscreenInfo) => void)
    Video_onPrepared?: ((parameter: PreparedInfo) => void)
    Video_onSeeking?: ((parameter: PlaybackInfo) => void)
    Video_onSeeked?: ((parameter: PlaybackInfo) => void)
    Video_onUpdate?: ((parameter: PlaybackInfo) => void)
    Video_onError?: (() => void)
    Video_onStop?: (() => void)
    Web_onPageEnd?: ((parameter: OnPageEndEvent) => void)
    Web_onPageBegin?: ((parameter: OnPageBeginEvent) => void)
    Web_onProgressChange?: ((parameter: OnProgressChangeEvent) => void)
    Web_onTitleReceive?: ((parameter: OnTitleReceiveEvent) => void)
    Web_onGeolocationHide?: (() => void)
    Web_onGeolocationShow?: ((parameter: OnGeolocationShowEvent) => void)
    Web_onRequestSelected?: (() => void)
    Web_onAlert?: ((parameter: OnAlertEvent) => boolean)
    Web_onBeforeUnload?: ((parameter: OnBeforeUnloadEvent) => boolean)
    Web_onConfirm?: ((parameter: OnConfirmEvent) => boolean)
    Web_onPrompt?: ((parameter: OnPromptEvent) => boolean)
    Web_onConsole?: ((parameter: OnConsoleEvent) => boolean)
    Web_onErrorReceive?: ((parameter: OnErrorReceiveEvent) => void)
    Web_onHttpErrorReceive?: ((parameter: OnHttpErrorReceiveEvent) => void)
    Web_onDownloadStart?: ((parameter: OnDownloadStartEvent) => void)
    Web_onRefreshAccessedHistory?: ((parameter: OnRefreshAccessedHistoryEvent) => void)
    Web_onUrlLoadIntercept?: ((event?: { data: string | WebResourceRequest }) => boolean)
    Web_onSslErrorReceive?: ((event?: { handler: Function, error: Object }) => void)
    Web_onRenderExited0?: ((parameter: OnRenderExitedEvent) => void)
    Web_onRenderExited1?: ((event?: { detail: Object }) => boolean)
    Web_onShowFileSelector?: ((parameter: OnShowFileSelectorEvent) => boolean)
    Web_onFileSelectorShow?: ((event?: { callback_: Function, fileSelector: Object }) => void)
    Web_onResourceLoad?: ((parameter: OnResourceLoadEvent) => void)
    Web_onFullScreenExit?: (() => void)
    Web_onFullScreenEnter?: OnFullScreenEnterCallback
    Web_onScaleChange?: ((parameter: OnScaleChangeEvent) => void)
    Web_onHttpAuthRequest?: ((parameter: OnHttpAuthRequestEvent) => boolean)
    Web_onInterceptRequest?: ((parameter: OnInterceptRequestEvent) => WebResourceResponse)
    Web_onPermissionRequest?: ((parameter: OnPermissionRequestEvent) => void)
    Web_onScreenCaptureRequest?: ((parameter: OnScreenCaptureRequestEvent) => void)
    Web_onContextMenuShow?: ((parameter: OnContextMenuShowEvent) => boolean)
    Web_onContextMenuHide?: OnContextMenuHideCallback
    Web_onSearchResultReceive?: ((parameter: OnSearchResultReceiveEvent) => void)
    Web_onScroll?: ((parameter: OnScrollEvent) => void)
    Web_onSslErrorEventReceive?: ((parameter: OnSslErrorEventReceiveEvent) => void)
    Web_onSslErrorEvent?: OnSslErrorEventCallback
    Web_onClientAuthenticationRequest?: ((parameter: OnClientAuthenticationEvent) => void)
    Web_onWindowNew?: ((parameter: OnWindowNewEvent) => void)
    Web_onWindowExit?: (() => void)
    Web_onInterceptKeyEvent?: ((parameter: KeyEvent) => boolean)
    Web_onTouchIconUrlReceived?: ((parameter: OnTouchIconUrlReceivedEvent) => void)
    Web_onFaviconReceived?: ((parameter: OnFaviconReceivedEvent) => void)
    Web_onPageVisible?: ((parameter: OnPageVisibleEvent) => void)
    Web_onDataResubmitted?: ((parameter: OnDataResubmittedEvent) => void)
    Web_onAudioStateChanged?: ((parameter: OnAudioStateChangedEvent) => void)
    Web_onFirstContentfulPaint?: ((parameter: OnFirstContentfulPaintEvent) => void)
    Web_onFirstMeaningfulPaint?: OnFirstMeaningfulPaintCallback
    Web_onLargestContentfulPaint?: OnLargestContentfulPaintCallback
    Web_onLoadIntercept?: ((parameter: OnLoadInterceptEvent) => boolean)
    Web_onControllerAttached?: (() => void)
    Web_onOverScroll?: ((parameter: OnOverScrollEvent) => void)
    Web_onSafeBrowsingCheckResult?: OnSafeBrowsingCheckResultCallback
    Web_onNavigationEntryCommitted?: OnNavigationEntryCommittedCallback
    Web_onIntelligentTrackingPreventionResult?: OnIntelligentTrackingPreventionCallback
    Web_onNativeEmbedLifecycleChange?: ((event: NativeEmbedDataInfo) => void)
    Web_onNativeEmbedVisibilityChange?: OnNativeEmbedVisibilityChangeCallback
    Web_onNativeEmbedGestureEvent?: ((event: NativeEmbedTouchInfo) => void)
    Web_onOverrideUrlLoading?: OnOverrideUrlLoadingCallback
    Web_onRenderProcessNotResponding?: OnRenderProcessNotRespondingCallback
    Web_onRenderProcessResponding?: OnRenderProcessRespondingCallback
    Web_onViewportFitChanged?: OnViewportFitChangedCallback
    Web_onInterceptKeyboardAttach?: WebKeyboardCallback
    Web_onAdsBlocked?: OnAdsBlockedCallback
    Web_bindSelectionMenu?: CustomBuilder
    XComponent_onLoad?: OnNativeLoadCallback
    XComponent_onDestroy?: VoidCallback
    SideBarContainer_onChange?: ((parameter: boolean) => void)
    SideBarContainer__onChangeEvent_showSideBar?: ((parameter: boolean) => void)
    WaterFlow_onReachStart?: (() => void)
    WaterFlow_onReachEnd?: (() => void)
    WaterFlow_onScrollFrameBegin?: ((offset: number, state: ScrollState) => { offsetRemain: number })
    WaterFlow_onScrollIndex?: ((first: number, last: number) => void)
    UIExtensionComponent_onRemoteReady?: ((parameter: UIExtensionProxy) => void)
    UIExtensionComponent_onResult?: ((parameter: { code: number, want?: Want }) => void)
    UIExtensionComponent_onRelease?: ((index: number) => void)
    UIExtensionComponent_onError?: ErrorCallback
    UIExtensionComponent_onTerminated?: ((parameter: TerminationInfo) => void)
}
export function deliverGeneratedPeerEvent(event: PeerEvent, properties: PeerEventsProperties): void {
    switch (event.kind) {
        case PeerEventKind.AbilityComponent_onConnect: properties.AbilityComponent_onConnect?.(); break
        case PeerEventKind.AbilityComponent_onDisconnect: properties.AbilityComponent_onDisconnect?.(); break
        case PeerEventKind.AlphabetIndexer_onSelected: properties.AlphabetIndexer_onSelected?.((event as AlphabetIndexer_onSelected_event).index); break
        case PeerEventKind.AlphabetIndexer_onSelect: properties.AlphabetIndexer_onSelect?.((event as AlphabetIndexer_onSelect_event).index); break
        case PeerEventKind.AlphabetIndexer_onRequestPopupData: properties.AlphabetIndexer_onRequestPopupData?.((event as AlphabetIndexer_onRequestPopupData_event).index); break
        case PeerEventKind.AlphabetIndexer_onPopupSelect: properties.AlphabetIndexer_onPopupSelect?.((event as AlphabetIndexer_onPopupSelect_event).index); break
        case PeerEventKind.AlphabetIndexer__onChangeEvent_selected: properties.AlphabetIndexer__onChangeEvent_selected?.((event as AlphabetIndexer__onChangeEvent_selected_event).index); break
        case PeerEventKind.Animator_onStart: properties.Animator_onStart?.(); break
        case PeerEventKind.Animator_onPause: properties.Animator_onPause?.(); break
        case PeerEventKind.Animator_onRepeat: properties.Animator_onRepeat?.(); break
        case PeerEventKind.Animator_onCancel: properties.Animator_onCancel?.(); break
        case PeerEventKind.Animator_onFinish: properties.Animator_onFinish?.(); break
        case PeerEventKind.Animator_onFrame: properties.Animator_onFrame?.((event as Animator_onFrame_event).index); break
        case PeerEventKind.Calendar_onSelectChange: properties.Calendar_onSelectChange?.((event as Calendar_onSelectChange_event).event); break
        case PeerEventKind.Calendar_onRequestData: properties.Calendar_onRequestData?.((event as Calendar_onRequestData_event).event); break
        case PeerEventKind.CalendarPicker_onChange: properties.CalendarPicker_onChange?.((event as CalendarPicker_onChange_event).parameter); break
        case PeerEventKind.Canvas_onReady: properties.Canvas_onReady?.(); break
        case PeerEventKind.Checkbox_onChange: properties.Checkbox_onChange?.((event as Checkbox_onChange_event).value); break
        case PeerEventKind.Checkbox__onChangeEvent_select: properties.Checkbox__onChangeEvent_select?.((event as Checkbox__onChangeEvent_select_event).parameter); break
        case PeerEventKind.CheckboxGroup_onChange: properties.CheckboxGroup_onChange?.((event as CheckboxGroup_onChange_event).value); break
        case PeerEventKind.CheckboxGroup__onChangeEvent_selectAll: properties.CheckboxGroup__onChangeEvent_selectAll?.((event as CheckboxGroup__onChangeEvent_selectAll_event).parameter); break
        case PeerEventKind.CommonMethod_onChildTouchTest: properties.CommonMethod_onChildTouchTest?.((event as CommonMethod_onChildTouchTest_event).value); break
        case PeerEventKind.CommonMethod_onClick0: properties.CommonMethod_onClick0?.((event as CommonMethod_onClick0_event).event); break
        case PeerEventKind.CommonMethod_onClick1: properties.CommonMethod_onClick1?.((event as CommonMethod_onClick1_event).event); break
        case PeerEventKind.CommonMethod_onHover: properties.CommonMethod_onHover?.((event as CommonMethod_onHover_event).isHover, (event as CommonMethod_onHover_event).event); break
        case PeerEventKind.CommonMethod_onAccessibilityHover: properties.CommonMethod_onAccessibilityHover?.((event as CommonMethod_onAccessibilityHover_event).isHover, (event as CommonMethod_onAccessibilityHover_event).event); break
        case PeerEventKind.CommonMethod_onMouse: properties.CommonMethod_onMouse?.((event as CommonMethod_onMouse_event).event); break
        case PeerEventKind.CommonMethod_onTouch: properties.CommonMethod_onTouch?.((event as CommonMethod_onTouch_event).event); break
        case PeerEventKind.CommonMethod_onKeyEvent: properties.CommonMethod_onKeyEvent?.((event as CommonMethod_onKeyEvent_event).event); break
        case PeerEventKind.CommonMethod_onKeyPreIme: properties.CommonMethod_onKeyPreIme?.((event as CommonMethod_onKeyPreIme_event).parameter); break
        case PeerEventKind.CommonMethod_onFocus: properties.CommonMethod_onFocus?.(); break
        case PeerEventKind.CommonMethod_onBlur: properties.CommonMethod_onBlur?.(); break
        case PeerEventKind.CommonMethod_onAppear: properties.CommonMethod_onAppear?.(); break
        case PeerEventKind.CommonMethod_onDisAppear: properties.CommonMethod_onDisAppear?.(); break
        case PeerEventKind.CommonMethod_onAttach: properties.CommonMethod_onAttach?.(); break
        case PeerEventKind.CommonMethod_onDetach: properties.CommonMethod_onDetach?.(); break
        case PeerEventKind.CommonMethod_onAreaChange: properties.CommonMethod_onAreaChange?.((event as CommonMethod_onAreaChange_event).oldValue, (event as CommonMethod_onAreaChange_event).newValue); break
        case PeerEventKind.CommonMethod_onDragStart: properties.CommonMethod_onDragStart?.((event as CommonMethod_onDragStart_event).event, (event as CommonMethod_onDragStart_event).extraParams); break
        case PeerEventKind.CommonMethod_onDragEnter: properties.CommonMethod_onDragEnter?.((event as CommonMethod_onDragEnter_event).event, (event as CommonMethod_onDragEnter_event).extraParams); break
        case PeerEventKind.CommonMethod_onDragMove: properties.CommonMethod_onDragMove?.((event as CommonMethod_onDragMove_event).event, (event as CommonMethod_onDragMove_event).extraParams); break
        case PeerEventKind.CommonMethod_onDragLeave: properties.CommonMethod_onDragLeave?.((event as CommonMethod_onDragLeave_event).event, (event as CommonMethod_onDragLeave_event).extraParams); break
        case PeerEventKind.CommonMethod_onDrop: properties.CommonMethod_onDrop?.((event as CommonMethod_onDrop_event).event, (event as CommonMethod_onDrop_event).extraParams); break
        case PeerEventKind.CommonMethod_onDragEnd: properties.CommonMethod_onDragEnd?.((event as CommonMethod_onDragEnd_event).event, (event as CommonMethod_onDragEnd_event).extraParams); break
        case PeerEventKind.CommonMethod_onPreDrag: properties.CommonMethod_onPreDrag?.((event as CommonMethod_onPreDrag_event).parameter); break
        case PeerEventKind.CommonMethod_accessibilityVirtualNode: properties.CommonMethod_accessibilityVirtualNode?.(); break
        case PeerEventKind.CommonMethod_onGestureJudgeBegin: properties.CommonMethod_onGestureJudgeBegin?.((event as CommonMethod_onGestureJudgeBegin_event).gestureInfo, (event as CommonMethod_onGestureJudgeBegin_event).event); break
        case PeerEventKind.CommonMethod_onGestureRecognizerJudgeBegin0: properties.CommonMethod_onGestureRecognizerJudgeBegin0?.((event as CommonMethod_onGestureRecognizerJudgeBegin0_event).event, (event as CommonMethod_onGestureRecognizerJudgeBegin0_event).current, (event as CommonMethod_onGestureRecognizerJudgeBegin0_event).recognizers); break
        case PeerEventKind.CommonMethod_onGestureRecognizerJudgeBegin1: properties.CommonMethod_onGestureRecognizerJudgeBegin1?.((event as CommonMethod_onGestureRecognizerJudgeBegin1_event).event, (event as CommonMethod_onGestureRecognizerJudgeBegin1_event).current, (event as CommonMethod_onGestureRecognizerJudgeBegin1_event).recognizers); break
        case PeerEventKind.CommonMethod_shouldBuiltInRecognizerParallelWith: properties.CommonMethod_shouldBuiltInRecognizerParallelWith?.((event as CommonMethod_shouldBuiltInRecognizerParallelWith_event).current, (event as CommonMethod_shouldBuiltInRecognizerParallelWith_event).others); break
        case PeerEventKind.CommonMethod_onTouchIntercept: properties.CommonMethod_onTouchIntercept?.((event as CommonMethod_onTouchIntercept_event).parameter); break
        case PeerEventKind.CommonMethod_onSizeChange: properties.CommonMethod_onSizeChange?.((event as CommonMethod_onSizeChange_event).oldValue, (event as CommonMethod_onSizeChange_event).newValue); break
        case PeerEventKind.CommonMethod_background: properties.CommonMethod_background?.(); break
        case PeerEventKind.CommonMethod_bindContextMenu0: properties.CommonMethod_bindContextMenu0?.(); break
        case PeerEventKind.CommonMethod_bindContextMenu1: properties.CommonMethod_bindContextMenu1?.(); break
        case PeerEventKind.CommonMethod_bindContentCover0: properties.CommonMethod_bindContentCover0?.(); break
        case PeerEventKind.CommonMethod_bindContentCover1: properties.CommonMethod_bindContentCover1?.(); break
        case PeerEventKind.CommonMethod_bindSheet: properties.CommonMethod_bindSheet?.(); break
        case PeerEventKind.CommonMethod_onVisibleAreaChange: properties.CommonMethod_onVisibleAreaChange?.((event as CommonMethod_onVisibleAreaChange_event).isExpanding, (event as CommonMethod_onVisibleAreaChange_event).currentRatio); break
        case PeerEventKind.ScrollableCommonMethod_onScroll: properties.ScrollableCommonMethod_onScroll?.((event as ScrollableCommonMethod_onScroll_event).first, (event as ScrollableCommonMethod_onScroll_event).last); break
        case PeerEventKind.ScrollableCommonMethod_onDidScroll: properties.ScrollableCommonMethod_onDidScroll?.((event as ScrollableCommonMethod_onDidScroll_event).xOffset, (event as ScrollableCommonMethod_onDidScroll_event).yOffset, (event as ScrollableCommonMethod_onDidScroll_event).scrollState); break
        case PeerEventKind.ScrollableCommonMethod_onReachStart: properties.ScrollableCommonMethod_onReachStart?.(); break
        case PeerEventKind.ScrollableCommonMethod_onReachEnd: properties.ScrollableCommonMethod_onReachEnd?.(); break
        case PeerEventKind.ScrollableCommonMethod_onScrollStart: properties.ScrollableCommonMethod_onScrollStart?.(); break
        case PeerEventKind.ScrollableCommonMethod_onScrollStop: properties.ScrollableCommonMethod_onScrollStop?.(); break
        case PeerEventKind.Counter_onInc: properties.Counter_onInc?.(); break
        case PeerEventKind.Counter_onDec: properties.Counter_onDec?.(); break
        case PeerEventKind.DatePicker_onChange: properties.DatePicker_onChange?.((event as DatePicker_onChange_event).value); break
        case PeerEventKind.DatePicker_onDateChange: properties.DatePicker_onDateChange?.((event as DatePicker_onDateChange_event).parameter); break
        case PeerEventKind.DatePicker__onChangeEvent_selected: properties.DatePicker__onChangeEvent_selected?.((event as DatePicker__onChangeEvent_selected_event).parameter); break
        case PeerEventKind.EmbeddedComponent_onTerminated: properties.EmbeddedComponent_onTerminated?.((event as EmbeddedComponent_onTerminated_event).parameter); break
        case PeerEventKind.EmbeddedComponent_onError: properties.EmbeddedComponent_onError?.((event as EmbeddedComponent_onError_event).err); break
        case PeerEventKind.FolderStack_onFolderStateChange: properties.FolderStack_onFolderStateChange?.((event as FolderStack_onFolderStateChange_event).event); break
        case PeerEventKind.FolderStack_onHoverStatusChange: properties.FolderStack_onHoverStatusChange?.((event as FolderStack_onHoverStatusChange_event).param); break
        case PeerEventKind.FormComponent_onAcquired: properties.FormComponent_onAcquired?.((event as FormComponent_onAcquired_event).parameter); break
        case PeerEventKind.FormComponent_onError: properties.FormComponent_onError?.((event as FormComponent_onError_event).info); break
        case PeerEventKind.FormComponent_onRouter: properties.FormComponent_onRouter?.((event as FormComponent_onRouter_event).info); break
        case PeerEventKind.FormComponent_onUninstall: properties.FormComponent_onUninstall?.((event as FormComponent_onUninstall_event).parameter); break
        case PeerEventKind.FormComponent_onLoad: properties.FormComponent_onLoad?.(); break
        case PeerEventKind.Gauge_description: properties.Gauge_description?.(); break
        case PeerEventKind.Grid_onScrollBarUpdate: properties.Grid_onScrollBarUpdate?.((event as Grid_onScrollBarUpdate_event).index, (event as Grid_onScrollBarUpdate_event).offset); break
        case PeerEventKind.Grid_onScrollIndex: properties.Grid_onScrollIndex?.((event as Grid_onScrollIndex_event).first, (event as Grid_onScrollIndex_event).last); break
        case PeerEventKind.Grid_onItemDragStart: properties.Grid_onItemDragStart?.((event as Grid_onItemDragStart_event).event, (event as Grid_onItemDragStart_event).itemIndex); break
        case PeerEventKind.Grid_onItemDragEnter: properties.Grid_onItemDragEnter?.((event as Grid_onItemDragEnter_event).event); break
        case PeerEventKind.Grid_onItemDragMove: properties.Grid_onItemDragMove?.((event as Grid_onItemDragMove_event).event, (event as Grid_onItemDragMove_event).itemIndex, (event as Grid_onItemDragMove_event).insertIndex); break
        case PeerEventKind.Grid_onItemDragLeave: properties.Grid_onItemDragLeave?.((event as Grid_onItemDragLeave_event).event, (event as Grid_onItemDragLeave_event).itemIndex); break
        case PeerEventKind.Grid_onItemDrop: properties.Grid_onItemDrop?.((event as Grid_onItemDrop_event).event, (event as Grid_onItemDrop_event).itemIndex, (event as Grid_onItemDrop_event).insertIndex, (event as Grid_onItemDrop_event).isSuccess); break
        case PeerEventKind.Grid_onScroll: properties.Grid_onScroll?.((event as Grid_onScroll_event).first, (event as Grid_onScroll_event).last); break
        case PeerEventKind.Grid_onReachStart: properties.Grid_onReachStart?.(); break
        case PeerEventKind.Grid_onReachEnd: properties.Grid_onReachEnd?.(); break
        case PeerEventKind.Grid_onScrollStart: properties.Grid_onScrollStart?.(); break
        case PeerEventKind.Grid_onScrollStop: properties.Grid_onScrollStop?.(); break
        case PeerEventKind.Grid_onScrollFrameBegin: properties.Grid_onScrollFrameBegin?.((event as Grid_onScrollFrameBegin_event).offset, (event as Grid_onScrollFrameBegin_event).state); break
        case PeerEventKind.GridItem_onSelect: properties.GridItem_onSelect?.((event as GridItem_onSelect_event).parameter); break
        case PeerEventKind.GridItem__onChangeEvent_selected: properties.GridItem__onChangeEvent_selected?.((event as GridItem__onChangeEvent_selected_event).parameter); break
        case PeerEventKind.GridRow_onBreakpointChange: properties.GridRow_onBreakpointChange?.((event as GridRow_onBreakpointChange_event).breakpoints); break
        case PeerEventKind.Image_onComplete: properties.Image_onComplete?.((event as Image_onComplete_event).event); break
        case PeerEventKind.Image_onError: properties.Image_onError?.((event as Image_onError_event).error); break
        case PeerEventKind.Image_onFinish: properties.Image_onFinish?.(); break
        case PeerEventKind.ImageAnimator_onStart: properties.ImageAnimator_onStart?.(); break
        case PeerEventKind.ImageAnimator_onPause: properties.ImageAnimator_onPause?.(); break
        case PeerEventKind.ImageAnimator_onRepeat: properties.ImageAnimator_onRepeat?.(); break
        case PeerEventKind.ImageAnimator_onCancel: properties.ImageAnimator_onCancel?.(); break
        case PeerEventKind.ImageAnimator_onFinish: properties.ImageAnimator_onFinish?.(); break
        case PeerEventKind.ImageSpan_onComplete: properties.ImageSpan_onComplete?.((event as ImageSpan_onComplete_event).result); break
        case PeerEventKind.ImageSpan_onError: properties.ImageSpan_onError?.((event as ImageSpan_onError_event).error); break
        case PeerEventKind.List_onScroll: properties.List_onScroll?.((event as List_onScroll_event).first, (event as List_onScroll_event).last); break
        case PeerEventKind.List_onScrollIndex: properties.List_onScrollIndex?.((event as List_onScrollIndex_event).start, (event as List_onScrollIndex_event).end, (event as List_onScrollIndex_event).center); break
        case PeerEventKind.List_onScrollVisibleContentChange: properties.List_onScrollVisibleContentChange?.((event as List_onScrollVisibleContentChange_event).start, (event as List_onScrollVisibleContentChange_event).end); break
        case PeerEventKind.List_onReachStart: properties.List_onReachStart?.(); break
        case PeerEventKind.List_onReachEnd: properties.List_onReachEnd?.(); break
        case PeerEventKind.List_onScrollStart: properties.List_onScrollStart?.(); break
        case PeerEventKind.List_onScrollStop: properties.List_onScrollStop?.(); break
        case PeerEventKind.List_onItemDelete: properties.List_onItemDelete?.((event as List_onItemDelete_event).index); break
        case PeerEventKind.List_onItemMove: properties.List_onItemMove?.((event as List_onItemMove_event).from, (event as List_onItemMove_event).to); break
        case PeerEventKind.List_onItemDragStart: properties.List_onItemDragStart?.((event as List_onItemDragStart_event).event, (event as List_onItemDragStart_event).itemIndex); break
        case PeerEventKind.List_onItemDragEnter: properties.List_onItemDragEnter?.((event as List_onItemDragEnter_event).event); break
        case PeerEventKind.List_onItemDragMove: properties.List_onItemDragMove?.((event as List_onItemDragMove_event).event, (event as List_onItemDragMove_event).itemIndex, (event as List_onItemDragMove_event).insertIndex); break
        case PeerEventKind.List_onItemDragLeave: properties.List_onItemDragLeave?.((event as List_onItemDragLeave_event).event, (event as List_onItemDragLeave_event).itemIndex); break
        case PeerEventKind.List_onItemDrop: properties.List_onItemDrop?.((event as List_onItemDrop_event).event, (event as List_onItemDrop_event).itemIndex, (event as List_onItemDrop_event).insertIndex, (event as List_onItemDrop_event).isSuccess); break
        case PeerEventKind.List_onScrollFrameBegin: properties.List_onScrollFrameBegin?.((event as List_onScrollFrameBegin_event).offset, (event as List_onScrollFrameBegin_event).state); break
        case PeerEventKind.ListItem_onSelect: properties.ListItem_onSelect?.((event as ListItem_onSelect_event).parameter); break
        case PeerEventKind.ListItem__onChangeEvent_selected: properties.ListItem__onChangeEvent_selected?.((event as ListItem__onChangeEvent_selected_event).parameter); break
        case PeerEventKind.LocationButton_onClick: properties.LocationButton_onClick?.((event as LocationButton_onClick_event).event, (event as LocationButton_onClick_event).result); break
        case PeerEventKind.Marquee_onStart: properties.Marquee_onStart?.(); break
        case PeerEventKind.Marquee_onBounce: properties.Marquee_onBounce?.(); break
        case PeerEventKind.Marquee_onFinish: properties.Marquee_onFinish?.(); break
        case PeerEventKind.MenuItem_onChange: properties.MenuItem_onChange?.((event as MenuItem_onChange_event).parameter); break
        case PeerEventKind.MenuItem__onChangeEvent_selected: properties.MenuItem__onChangeEvent_selected?.((event as MenuItem__onChangeEvent_selected_event).parameter); break
        case PeerEventKind.NavDestination_onShown: properties.NavDestination_onShown?.(); break
        case PeerEventKind.NavDestination_onHidden: properties.NavDestination_onHidden?.(); break
        case PeerEventKind.NavDestination_onBackPressed: properties.NavDestination_onBackPressed?.(); break
        case PeerEventKind.NavDestination_onReady: properties.NavDestination_onReady?.((event as NavDestination_onReady_event).parameter); break
        case PeerEventKind.NavDestination_onWillAppear: properties.NavDestination_onWillAppear?.(); break
        case PeerEventKind.NavDestination_onWillDisappear: properties.NavDestination_onWillDisappear?.(); break
        case PeerEventKind.NavDestination_onWillShow: properties.NavDestination_onWillShow?.(); break
        case PeerEventKind.NavDestination_onWillHide: properties.NavDestination_onWillHide?.(); break
        case PeerEventKind.NavRouter_onStateChange: properties.NavRouter_onStateChange?.((event as NavRouter_onStateChange_event).parameter); break
        case PeerEventKind.Panel_onChange: properties.Panel_onChange?.((event as Panel_onChange_event).width, (event as Panel_onChange_event).height, (event as Panel_onChange_event).mode); break
        case PeerEventKind.Panel_onHeightChange: properties.Panel_onHeightChange?.((event as Panel_onHeightChange_event).index); break
        case PeerEventKind.Panel__onChangeEvent_mode: properties.Panel__onChangeEvent_mode?.((event as Panel__onChangeEvent_mode_event).mode); break
        case PeerEventKind.PasteButton_onClick: properties.PasteButton_onClick?.((event as PasteButton_onClick_event).event, (event as PasteButton_onClick_event).result); break
        case PeerEventKind.PatternLock_onPatternComplete: properties.PatternLock_onPatternComplete?.((event as PatternLock_onPatternComplete_event).input); break
        case PeerEventKind.PatternLock_onDotConnect: properties.PatternLock_onDotConnect?.((event as PatternLock_onDotConnect_event).index); break
        case PeerEventKind.PluginComponent_onComplete: properties.PluginComponent_onComplete?.(); break
        case PeerEventKind.PluginComponent_onError: properties.PluginComponent_onError?.((event as PluginComponent_onError_event).info); break
        case PeerEventKind.Radio_onChange: properties.Radio_onChange?.((event as Radio_onChange_event).parameter); break
        case PeerEventKind.Radio__onChangeEvent_checked: properties.Radio__onChangeEvent_checked?.((event as Radio__onChangeEvent_checked_event).parameter); break
        case PeerEventKind.Rating_onChange: properties.Rating_onChange?.((event as Rating_onChange_event).index); break
        case PeerEventKind.Rating__onChangeEvent_rating: properties.Rating__onChangeEvent_rating?.((event as Rating__onChangeEvent_rating_event).index); break
        case PeerEventKind.Refresh_onStateChange: properties.Refresh_onStateChange?.((event as Refresh_onStateChange_event).state); break
        case PeerEventKind.Refresh_onRefreshing: properties.Refresh_onRefreshing?.(); break
        case PeerEventKind.Refresh_onOffsetChange: properties.Refresh_onOffsetChange?.((event as Refresh_onOffsetChange_event).index); break
        case PeerEventKind.Refresh__onChangeEvent_refreshing: properties.Refresh__onChangeEvent_refreshing?.((event as Refresh__onChangeEvent_refreshing_event).parameter); break
        case PeerEventKind.RichEditor_onReady: properties.RichEditor_onReady?.(); break
        case PeerEventKind.RichEditor_onSelect: properties.RichEditor_onSelect?.((event as RichEditor_onSelect_event).parameter); break
        case PeerEventKind.RichEditor_onSelectionChange: properties.RichEditor_onSelectionChange?.((event as RichEditor_onSelectionChange_event).parameter); break
        case PeerEventKind.RichEditor_aboutToIMEInput: properties.RichEditor_aboutToIMEInput?.((event as RichEditor_aboutToIMEInput_event).parameter); break
        case PeerEventKind.RichEditor_onIMEInputComplete: properties.RichEditor_onIMEInputComplete?.((event as RichEditor_onIMEInputComplete_event).parameter); break
        case PeerEventKind.RichEditor_onDidIMEInput: properties.RichEditor_onDidIMEInput?.((event as RichEditor_onDidIMEInput_event).parameter); break
        case PeerEventKind.RichEditor_aboutToDelete: properties.RichEditor_aboutToDelete?.((event as RichEditor_aboutToDelete_event).parameter); break
        case PeerEventKind.RichEditor_onDeleteComplete: properties.RichEditor_onDeleteComplete?.(); break
        case PeerEventKind.RichEditor_onPaste: properties.RichEditor_onPaste?.((event as RichEditor_onPaste_event).event); break
        case PeerEventKind.RichEditor_onEditingChange: properties.RichEditor_onEditingChange?.((event as RichEditor_onEditingChange_event).parameter); break
        case PeerEventKind.RichEditor_onSubmit: properties.RichEditor_onSubmit?.((event as RichEditor_onSubmit_event).enterKey, (event as RichEditor_onSubmit_event).event); break
        case PeerEventKind.RichEditor_onWillChange: properties.RichEditor_onWillChange?.((event as RichEditor_onWillChange_event).parameter); break
        case PeerEventKind.RichEditor_onDidChange: properties.RichEditor_onDidChange?.((event as RichEditor_onDidChange_event).rangeBefore, (event as RichEditor_onDidChange_event).rangeAfter); break
        case PeerEventKind.RichEditor_onCut: properties.RichEditor_onCut?.((event as RichEditor_onCut_event).parameter); break
        case PeerEventKind.RichEditor_onCopy: properties.RichEditor_onCopy?.((event as RichEditor_onCopy_event).parameter); break
        case PeerEventKind.RichEditor_bindSelectionMenu: properties.RichEditor_bindSelectionMenu?.(); break
        case PeerEventKind.RichEditor_customKeyboard: properties.RichEditor_customKeyboard?.(); break
        case PeerEventKind.RichText_onStart: properties.RichText_onStart?.(); break
        case PeerEventKind.RichText_onComplete: properties.RichText_onComplete?.(); break
        case PeerEventKind.SaveButton_onClick: properties.SaveButton_onClick?.((event as SaveButton_onClick_event).event, (event as SaveButton_onClick_event).result); break
        case PeerEventKind.Scroll_onScroll: properties.Scroll_onScroll?.((event as Scroll_onScroll_event).first, (event as Scroll_onScroll_event).last); break
        case PeerEventKind.Scroll_onDidScroll: properties.Scroll_onDidScroll?.((event as Scroll_onDidScroll_event).xOffset, (event as Scroll_onDidScroll_event).yOffset, (event as Scroll_onDidScroll_event).scrollState); break
        case PeerEventKind.Scroll_onScrollEdge: properties.Scroll_onScrollEdge?.((event as Scroll_onScrollEdge_event).side); break
        case PeerEventKind.Scroll_onScrollStart: properties.Scroll_onScrollStart?.(); break
        case PeerEventKind.Scroll_onScrollEnd: properties.Scroll_onScrollEnd?.(); break
        case PeerEventKind.Scroll_onScrollStop: properties.Scroll_onScrollStop?.(); break
        case PeerEventKind.Scroll_onScrollFrameBegin: properties.Scroll_onScrollFrameBegin?.((event as Scroll_onScrollFrameBegin_event).offset, (event as Scroll_onScrollFrameBegin_event).state); break
        case PeerEventKind.Search_onEditChange: properties.Search_onEditChange?.((event as Search_onEditChange_event).parameter); break
        case PeerEventKind.Search_onSubmit0: properties.Search_onSubmit0?.((event as Search_onSubmit0_event).breakpoints); break
        case PeerEventKind.Search_onSubmit1: properties.Search_onSubmit1?.((event as Search_onSubmit1_event).searchContent, (event as Search_onSubmit1_event).event); break
        case PeerEventKind.Search_onChange: properties.Search_onChange?.((event as Search_onChange_event).value, (event as Search_onChange_event).previewText); break
        case PeerEventKind.Search_onTextSelectionChange: properties.Search_onTextSelectionChange?.((event as Search_onTextSelectionChange_event).selectionStart, (event as Search_onTextSelectionChange_event).selectionEnd); break
        case PeerEventKind.Search_onContentScroll: properties.Search_onContentScroll?.((event as Search_onContentScroll_event).totalOffsetX, (event as Search_onContentScroll_event).totalOffsetY); break
        case PeerEventKind.Search_onCopy: properties.Search_onCopy?.((event as Search_onCopy_event).breakpoints); break
        case PeerEventKind.Search_onCut: properties.Search_onCut?.((event as Search_onCut_event).breakpoints); break
        case PeerEventKind.Search_onPaste: properties.Search_onPaste?.((event as Search_onPaste_event).content, (event as Search_onPaste_event).event); break
        case PeerEventKind.Search_onWillInsert: properties.Search_onWillInsert?.((event as Search_onWillInsert_event).parameter); break
        case PeerEventKind.Search_onDidInsert: properties.Search_onDidInsert?.((event as Search_onDidInsert_event).parameter); break
        case PeerEventKind.Search_onWillDelete: properties.Search_onWillDelete?.((event as Search_onWillDelete_event).parameter); break
        case PeerEventKind.Search_onDidDelete: properties.Search_onDidDelete?.((event as Search_onDidDelete_event).parameter); break
        case PeerEventKind.Search_customKeyboard: properties.Search_customKeyboard?.(); break
        case PeerEventKind.Search__onChangeEvent_value: properties.Search__onChangeEvent_value?.((event as Search__onChangeEvent_value_event).breakpoints); break
        case PeerEventKind.Select_onSelect: properties.Select_onSelect?.((event as Select_onSelect_event).index, (event as Select_onSelect_event).value); break
        case PeerEventKind.Select__onChangeEvent_selected: properties.Select__onChangeEvent_selected?.((event as Select__onChangeEvent_selected_event).selected); break
        case PeerEventKind.Select__onChangeEvent_value: properties.Select__onChangeEvent_value?.((event as Select__onChangeEvent_value_event).value); break
        case PeerEventKind.Slider_onChange: properties.Slider_onChange?.((event as Slider_onChange_event).value, (event as Slider_onChange_event).mode); break
        case PeerEventKind.Slider__onChangeEvent_value: properties.Slider__onChangeEvent_value?.((event as Slider__onChangeEvent_value_event).index); break
        case PeerEventKind.Stepper_onFinish: properties.Stepper_onFinish?.(); break
        case PeerEventKind.Stepper_onSkip: properties.Stepper_onSkip?.(); break
        case PeerEventKind.Stepper_onChange: properties.Stepper_onChange?.((event as Stepper_onChange_event).first, (event as Stepper_onChange_event).last); break
        case PeerEventKind.Stepper_onNext: properties.Stepper_onNext?.((event as Stepper_onNext_event).first, (event as Stepper_onNext_event).last); break
        case PeerEventKind.Stepper_onPrevious: properties.Stepper_onPrevious?.((event as Stepper_onPrevious_event).first, (event as Stepper_onPrevious_event).last); break
        case PeerEventKind.Stepper__onChangeEvent_index: properties.Stepper__onChangeEvent_index?.((event as Stepper__onChangeEvent_index_event).index); break
        case PeerEventKind.Swiper_onChange: properties.Swiper_onChange?.((event as Swiper_onChange_event).index); break
        case PeerEventKind.Swiper_onAnimationStart: properties.Swiper_onAnimationStart?.((event as Swiper_onAnimationStart_event).index, (event as Swiper_onAnimationStart_event).targetIndex, (event as Swiper_onAnimationStart_event).extraInfo); break
        case PeerEventKind.Swiper_onAnimationEnd: properties.Swiper_onAnimationEnd?.((event as Swiper_onAnimationEnd_event).index, (event as Swiper_onAnimationEnd_event).extraInfo); break
        case PeerEventKind.Swiper_onGestureSwipe: properties.Swiper_onGestureSwipe?.((event as Swiper_onGestureSwipe_event).index, (event as Swiper_onGestureSwipe_event).extraInfo); break
        case PeerEventKind.Swiper_onContentDidScroll: properties.Swiper_onContentDidScroll?.((event as Swiper_onContentDidScroll_event).selectedIndex, (event as Swiper_onContentDidScroll_event).index, (event as Swiper_onContentDidScroll_event).position, (event as Swiper_onContentDidScroll_event).mainAxisLength); break
        case PeerEventKind.Swiper__onChangeEvent_index: properties.Swiper__onChangeEvent_index?.((event as Swiper__onChangeEvent_index_event).index); break
        case PeerEventKind.IndicatorComponent_onChange: properties.IndicatorComponent_onChange?.((event as IndicatorComponent_onChange_event).index); break
        case PeerEventKind.Tabs_onChange: properties.Tabs_onChange?.((event as Tabs_onChange_event).index); break
        case PeerEventKind.Tabs_onTabBarClick: properties.Tabs_onTabBarClick?.((event as Tabs_onTabBarClick_event).index); break
        case PeerEventKind.Tabs_onAnimationStart: properties.Tabs_onAnimationStart?.((event as Tabs_onAnimationStart_event).index, (event as Tabs_onAnimationStart_event).targetIndex, (event as Tabs_onAnimationStart_event).extraInfo); break
        case PeerEventKind.Tabs_onAnimationEnd: properties.Tabs_onAnimationEnd?.((event as Tabs_onAnimationEnd_event).index, (event as Tabs_onAnimationEnd_event).extraInfo); break
        case PeerEventKind.Tabs_onGestureSwipe: properties.Tabs_onGestureSwipe?.((event as Tabs_onGestureSwipe_event).index, (event as Tabs_onGestureSwipe_event).extraInfo); break
        case PeerEventKind.Tabs_customContentTransition: properties.Tabs_customContentTransition?.((event as Tabs_customContentTransition_event).from, (event as Tabs_customContentTransition_event).to); break
        case PeerEventKind.Tabs_onContentWillChange: properties.Tabs_onContentWillChange?.((event as Tabs_onContentWillChange_event).currentIndex, (event as Tabs_onContentWillChange_event).comingIndex); break
        case PeerEventKind.Tabs__onChangeEvent_index: properties.Tabs__onChangeEvent_index?.((event as Tabs__onChangeEvent_index_event).index); break
        case PeerEventKind.TabContent_onWillShow: properties.TabContent_onWillShow?.(); break
        case PeerEventKind.TabContent_onWillHide: properties.TabContent_onWillHide?.(); break
        case PeerEventKind.Text_onCopy: properties.Text_onCopy?.((event as Text_onCopy_event).breakpoints); break
        case PeerEventKind.Text_onTextSelectionChange: properties.Text_onTextSelectionChange?.((event as Text_onTextSelectionChange_event).first, (event as Text_onTextSelectionChange_event).last); break
        case PeerEventKind.Text_bindSelectionMenu: properties.Text_bindSelectionMenu?.(); break
        case PeerEventKind.TextArea_onSubmit0: properties.TextArea_onSubmit0?.((event as TextArea_onSubmit0_event).enterKey); break
        case PeerEventKind.TextArea_onSubmit1: properties.TextArea_onSubmit1?.((event as TextArea_onSubmit1_event).enterKeyType, (event as TextArea_onSubmit1_event).event); break
        case PeerEventKind.TextArea_onChange: properties.TextArea_onChange?.((event as TextArea_onChange_event).value, (event as TextArea_onChange_event).previewText); break
        case PeerEventKind.TextArea_onTextSelectionChange: properties.TextArea_onTextSelectionChange?.((event as TextArea_onTextSelectionChange_event).first, (event as TextArea_onTextSelectionChange_event).last); break
        case PeerEventKind.TextArea_onContentScroll: properties.TextArea_onContentScroll?.((event as TextArea_onContentScroll_event).first, (event as TextArea_onContentScroll_event).last); break
        case PeerEventKind.TextArea_onEditChange: properties.TextArea_onEditChange?.((event as TextArea_onEditChange_event).parameter); break
        case PeerEventKind.TextArea_onCopy: properties.TextArea_onCopy?.((event as TextArea_onCopy_event).breakpoints); break
        case PeerEventKind.TextArea_onCut: properties.TextArea_onCut?.((event as TextArea_onCut_event).breakpoints); break
        case PeerEventKind.TextArea_onPaste: properties.TextArea_onPaste?.((event as TextArea_onPaste_event).value, (event as TextArea_onPaste_event).event); break
        case PeerEventKind.TextArea_onWillInsert: properties.TextArea_onWillInsert?.((event as TextArea_onWillInsert_event).parameter); break
        case PeerEventKind.TextArea_onDidInsert: properties.TextArea_onDidInsert?.((event as TextArea_onDidInsert_event).parameter); break
        case PeerEventKind.TextArea_onWillDelete: properties.TextArea_onWillDelete?.((event as TextArea_onWillDelete_event).parameter); break
        case PeerEventKind.TextArea_onDidDelete: properties.TextArea_onDidDelete?.((event as TextArea_onDidDelete_event).parameter); break
        case PeerEventKind.TextArea_customKeyboard: properties.TextArea_customKeyboard?.(); break
        case PeerEventKind.TextArea__onChangeEvent_text: properties.TextArea__onChangeEvent_text?.((event as TextArea__onChangeEvent_text_event).value); break
        case PeerEventKind.TextClock_onDateChange: properties.TextClock_onDateChange?.((event as TextClock_onDateChange_event).index); break
        case PeerEventKind.TextInput_onEditChanged: properties.TextInput_onEditChanged?.((event as TextInput_onEditChanged_event).parameter); break
        case PeerEventKind.TextInput_onEditChange: properties.TextInput_onEditChange?.((event as TextInput_onEditChange_event).parameter); break
        case PeerEventKind.TextInput_onSubmit: properties.TextInput_onSubmit?.((event as TextInput_onSubmit_event).enterKey, (event as TextInput_onSubmit_event).event); break
        case PeerEventKind.TextInput_onChange: properties.TextInput_onChange?.((event as TextInput_onChange_event).value, (event as TextInput_onChange_event).previewText); break
        case PeerEventKind.TextInput_onTextSelectionChange: properties.TextInput_onTextSelectionChange?.((event as TextInput_onTextSelectionChange_event).selectionStart, (event as TextInput_onTextSelectionChange_event).selectionEnd); break
        case PeerEventKind.TextInput_onContentScroll: properties.TextInput_onContentScroll?.((event as TextInput_onContentScroll_event).totalOffsetX, (event as TextInput_onContentScroll_event).totalOffsetY); break
        case PeerEventKind.TextInput_onCopy: properties.TextInput_onCopy?.((event as TextInput_onCopy_event).breakpoints); break
        case PeerEventKind.TextInput_onCut: properties.TextInput_onCut?.((event as TextInput_onCut_event).breakpoints); break
        case PeerEventKind.TextInput_onPaste: properties.TextInput_onPaste?.((event as TextInput_onPaste_event).content, (event as TextInput_onPaste_event).event); break
        case PeerEventKind.TextInput_showUnit: properties.TextInput_showUnit?.(); break
        case PeerEventKind.TextInput_onSecurityStateChange: properties.TextInput_onSecurityStateChange?.((event as TextInput_onSecurityStateChange_event).parameter); break
        case PeerEventKind.TextInput_onWillInsert: properties.TextInput_onWillInsert?.((event as TextInput_onWillInsert_event).parameter); break
        case PeerEventKind.TextInput_onDidInsert: properties.TextInput_onDidInsert?.((event as TextInput_onDidInsert_event).parameter); break
        case PeerEventKind.TextInput_onWillDelete: properties.TextInput_onWillDelete?.((event as TextInput_onWillDelete_event).parameter); break
        case PeerEventKind.TextInput_onDidDelete: properties.TextInput_onDidDelete?.((event as TextInput_onDidDelete_event).parameter); break
        case PeerEventKind.TextInput_customKeyboard: properties.TextInput_customKeyboard?.(); break
        case PeerEventKind.TextInput__onChangeEvent_text: properties.TextInput__onChangeEvent_text?.((event as TextInput__onChangeEvent_text_event).value); break
        case PeerEventKind.TextPicker_onAccept: properties.TextPicker_onAccept?.((event as TextPicker_onAccept_event).value, (event as TextPicker_onAccept_event).index); break
        case PeerEventKind.TextPicker_onCancel: properties.TextPicker_onCancel?.(); break
        case PeerEventKind.TextPicker_onChange: properties.TextPicker_onChange?.((event as TextPicker_onChange_event).value, (event as TextPicker_onChange_event).index); break
        case PeerEventKind.TextPicker__onChangeEvent_selected: properties.TextPicker__onChangeEvent_selected?.((event as TextPicker__onChangeEvent_selected_event).selected); break
        case PeerEventKind.TextPicker__onChangeEvent_value: properties.TextPicker__onChangeEvent_value?.((event as TextPicker__onChangeEvent_value_event).value); break
        case PeerEventKind.TextTimer_onTimer: properties.TextTimer_onTimer?.((event as TextTimer_onTimer_event).first, (event as TextTimer_onTimer_event).last); break
        case PeerEventKind.TimePicker_onChange: properties.TimePicker_onChange?.((event as TimePicker_onChange_event).value); break
        case PeerEventKind.TimePicker__onChangeEvent_selected: properties.TimePicker__onChangeEvent_selected?.((event as TimePicker__onChangeEvent_selected_event).parameter); break
        case PeerEventKind.Toggle_onChange: properties.Toggle_onChange?.((event as Toggle_onChange_event).parameter); break
        case PeerEventKind.Toggle__onChangeEvent_isOn: properties.Toggle__onChangeEvent_isOn?.((event as Toggle__onChangeEvent_isOn_event).parameter); break
        case PeerEventKind.Video_onStart: properties.Video_onStart?.(); break
        case PeerEventKind.Video_onPause: properties.Video_onPause?.(); break
        case PeerEventKind.Video_onFinish: properties.Video_onFinish?.(); break
        case PeerEventKind.Video_onFullscreenChange: properties.Video_onFullscreenChange?.((event as Video_onFullscreenChange_event).parameter); break
        case PeerEventKind.Video_onPrepared: properties.Video_onPrepared?.((event as Video_onPrepared_event).parameter); break
        case PeerEventKind.Video_onSeeking: properties.Video_onSeeking?.((event as Video_onSeeking_event).parameter); break
        case PeerEventKind.Video_onSeeked: properties.Video_onSeeked?.((event as Video_onSeeked_event).parameter); break
        case PeerEventKind.Video_onUpdate: properties.Video_onUpdate?.((event as Video_onUpdate_event).parameter); break
        case PeerEventKind.Video_onError: properties.Video_onError?.(); break
        case PeerEventKind.Video_onStop: properties.Video_onStop?.(); break
        case PeerEventKind.Web_onPageEnd: properties.Web_onPageEnd?.((event as Web_onPageEnd_event).parameter); break
        case PeerEventKind.Web_onPageBegin: properties.Web_onPageBegin?.((event as Web_onPageBegin_event).parameter); break
        case PeerEventKind.Web_onProgressChange: properties.Web_onProgressChange?.((event as Web_onProgressChange_event).parameter); break
        case PeerEventKind.Web_onTitleReceive: properties.Web_onTitleReceive?.((event as Web_onTitleReceive_event).parameter); break
        case PeerEventKind.Web_onGeolocationHide: properties.Web_onGeolocationHide?.(); break
        case PeerEventKind.Web_onGeolocationShow: properties.Web_onGeolocationShow?.((event as Web_onGeolocationShow_event).parameter); break
        case PeerEventKind.Web_onRequestSelected: properties.Web_onRequestSelected?.(); break
        case PeerEventKind.Web_onAlert: properties.Web_onAlert?.((event as Web_onAlert_event).parameter); break
        case PeerEventKind.Web_onBeforeUnload: properties.Web_onBeforeUnload?.((event as Web_onBeforeUnload_event).parameter); break
        case PeerEventKind.Web_onConfirm: properties.Web_onConfirm?.((event as Web_onConfirm_event).parameter); break
        case PeerEventKind.Web_onPrompt: properties.Web_onPrompt?.((event as Web_onPrompt_event).parameter); break
        case PeerEventKind.Web_onConsole: properties.Web_onConsole?.((event as Web_onConsole_event).parameter); break
        case PeerEventKind.Web_onErrorReceive: properties.Web_onErrorReceive?.((event as Web_onErrorReceive_event).parameter); break
        case PeerEventKind.Web_onHttpErrorReceive: properties.Web_onHttpErrorReceive?.((event as Web_onHttpErrorReceive_event).parameter); break
        case PeerEventKind.Web_onDownloadStart: properties.Web_onDownloadStart?.((event as Web_onDownloadStart_event).parameter); break
        case PeerEventKind.Web_onRefreshAccessedHistory: properties.Web_onRefreshAccessedHistory?.((event as Web_onRefreshAccessedHistory_event).parameter); break
        case PeerEventKind.Web_onUrlLoadIntercept: properties.Web_onUrlLoadIntercept?.((event as Web_onUrlLoadIntercept_event).event); break
        case PeerEventKind.Web_onSslErrorReceive: properties.Web_onSslErrorReceive?.((event as Web_onSslErrorReceive_event).event); break
        case PeerEventKind.Web_onRenderExited0: properties.Web_onRenderExited0?.((event as Web_onRenderExited0_event).parameter); break
        case PeerEventKind.Web_onRenderExited1: properties.Web_onRenderExited1?.((event as Web_onRenderExited1_event).event); break
        case PeerEventKind.Web_onShowFileSelector: properties.Web_onShowFileSelector?.((event as Web_onShowFileSelector_event).parameter); break
        case PeerEventKind.Web_onFileSelectorShow: properties.Web_onFileSelectorShow?.((event as Web_onFileSelectorShow_event).event); break
        case PeerEventKind.Web_onResourceLoad: properties.Web_onResourceLoad?.((event as Web_onResourceLoad_event).parameter); break
        case PeerEventKind.Web_onFullScreenExit: properties.Web_onFullScreenExit?.(); break
        case PeerEventKind.Web_onFullScreenEnter: properties.Web_onFullScreenEnter?.((event as Web_onFullScreenEnter_event).event); break
        case PeerEventKind.Web_onScaleChange: properties.Web_onScaleChange?.((event as Web_onScaleChange_event).parameter); break
        case PeerEventKind.Web_onHttpAuthRequest: properties.Web_onHttpAuthRequest?.((event as Web_onHttpAuthRequest_event).parameter); break
        case PeerEventKind.Web_onInterceptRequest: properties.Web_onInterceptRequest?.((event as Web_onInterceptRequest_event).parameter); break
        case PeerEventKind.Web_onPermissionRequest: properties.Web_onPermissionRequest?.((event as Web_onPermissionRequest_event).parameter); break
        case PeerEventKind.Web_onScreenCaptureRequest: properties.Web_onScreenCaptureRequest?.((event as Web_onScreenCaptureRequest_event).parameter); break
        case PeerEventKind.Web_onContextMenuShow: properties.Web_onContextMenuShow?.((event as Web_onContextMenuShow_event).parameter); break
        case PeerEventKind.Web_onContextMenuHide: properties.Web_onContextMenuHide?.(); break
        case PeerEventKind.Web_onSearchResultReceive: properties.Web_onSearchResultReceive?.((event as Web_onSearchResultReceive_event).parameter); break
        case PeerEventKind.Web_onScroll: properties.Web_onScroll?.((event as Web_onScroll_event).parameter); break
        case PeerEventKind.Web_onSslErrorEventReceive: properties.Web_onSslErrorEventReceive?.((event as Web_onSslErrorEventReceive_event).parameter); break
        case PeerEventKind.Web_onSslErrorEvent: properties.Web_onSslErrorEvent?.((event as Web_onSslErrorEvent_event).sslErrorEvent); break
        case PeerEventKind.Web_onClientAuthenticationRequest: properties.Web_onClientAuthenticationRequest?.((event as Web_onClientAuthenticationRequest_event).parameter); break
        case PeerEventKind.Web_onWindowNew: properties.Web_onWindowNew?.((event as Web_onWindowNew_event).parameter); break
        case PeerEventKind.Web_onWindowExit: properties.Web_onWindowExit?.(); break
        case PeerEventKind.Web_onInterceptKeyEvent: properties.Web_onInterceptKeyEvent?.((event as Web_onInterceptKeyEvent_event).parameter); break
        case PeerEventKind.Web_onTouchIconUrlReceived: properties.Web_onTouchIconUrlReceived?.((event as Web_onTouchIconUrlReceived_event).parameter); break
        case PeerEventKind.Web_onFaviconReceived: properties.Web_onFaviconReceived?.((event as Web_onFaviconReceived_event).parameter); break
        case PeerEventKind.Web_onPageVisible: properties.Web_onPageVisible?.((event as Web_onPageVisible_event).parameter); break
        case PeerEventKind.Web_onDataResubmitted: properties.Web_onDataResubmitted?.((event as Web_onDataResubmitted_event).parameter); break
        case PeerEventKind.Web_onAudioStateChanged: properties.Web_onAudioStateChanged?.((event as Web_onAudioStateChanged_event).parameter); break
        case PeerEventKind.Web_onFirstContentfulPaint: properties.Web_onFirstContentfulPaint?.((event as Web_onFirstContentfulPaint_event).parameter); break
        case PeerEventKind.Web_onFirstMeaningfulPaint: properties.Web_onFirstMeaningfulPaint?.((event as Web_onFirstMeaningfulPaint_event).firstMeaningfulPaint); break
        case PeerEventKind.Web_onLargestContentfulPaint: properties.Web_onLargestContentfulPaint?.((event as Web_onLargestContentfulPaint_event).largestContentfulPaint); break
        case PeerEventKind.Web_onLoadIntercept: properties.Web_onLoadIntercept?.((event as Web_onLoadIntercept_event).parameter); break
        case PeerEventKind.Web_onControllerAttached: properties.Web_onControllerAttached?.(); break
        case PeerEventKind.Web_onOverScroll: properties.Web_onOverScroll?.((event as Web_onOverScroll_event).parameter); break
        case PeerEventKind.Web_onSafeBrowsingCheckResult: properties.Web_onSafeBrowsingCheckResult?.((event as Web_onSafeBrowsingCheckResult_event).threatType); break
        case PeerEventKind.Web_onNavigationEntryCommitted: properties.Web_onNavigationEntryCommitted?.((event as Web_onNavigationEntryCommitted_event).loadCommittedDetails); break
        case PeerEventKind.Web_onIntelligentTrackingPreventionResult: properties.Web_onIntelligentTrackingPreventionResult?.((event as Web_onIntelligentTrackingPreventionResult_event).details); break
        case PeerEventKind.Web_onNativeEmbedLifecycleChange: properties.Web_onNativeEmbedLifecycleChange?.((event as Web_onNativeEmbedLifecycleChange_event).event); break
        case PeerEventKind.Web_onNativeEmbedVisibilityChange: properties.Web_onNativeEmbedVisibilityChange?.((event as Web_onNativeEmbedVisibilityChange_event).nativeEmbedVisibilityInfo); break
        case PeerEventKind.Web_onNativeEmbedGestureEvent: properties.Web_onNativeEmbedGestureEvent?.((event as Web_onNativeEmbedGestureEvent_event).event); break
        case PeerEventKind.Web_onOverrideUrlLoading: properties.Web_onOverrideUrlLoading?.((event as Web_onOverrideUrlLoading_event).webResourceRequest); break
        case PeerEventKind.Web_onRenderProcessNotResponding: properties.Web_onRenderProcessNotResponding?.((event as Web_onRenderProcessNotResponding_event).data); break
        case PeerEventKind.Web_onRenderProcessResponding: properties.Web_onRenderProcessResponding?.(); break
        case PeerEventKind.Web_onViewportFitChanged: properties.Web_onViewportFitChanged?.((event as Web_onViewportFitChanged_event).viewportFit); break
        case PeerEventKind.Web_onInterceptKeyboardAttach: properties.Web_onInterceptKeyboardAttach?.((event as Web_onInterceptKeyboardAttach_event).keyboardCallbackInfo); break
        case PeerEventKind.Web_onAdsBlocked: properties.Web_onAdsBlocked?.((event as Web_onAdsBlocked_event).details); break
        case PeerEventKind.Web_bindSelectionMenu: properties.Web_bindSelectionMenu?.(); break
        case PeerEventKind.XComponent_onLoad: properties.XComponent_onLoad?.((event as XComponent_onLoad_event).event); break
        case PeerEventKind.XComponent_onDestroy: properties.XComponent_onDestroy?.(); break
        case PeerEventKind.SideBarContainer_onChange: properties.SideBarContainer_onChange?.((event as SideBarContainer_onChange_event).parameter); break
        case PeerEventKind.SideBarContainer__onChangeEvent_showSideBar: properties.SideBarContainer__onChangeEvent_showSideBar?.((event as SideBarContainer__onChangeEvent_showSideBar_event).parameter); break
        case PeerEventKind.WaterFlow_onReachStart: properties.WaterFlow_onReachStart?.(); break
        case PeerEventKind.WaterFlow_onReachEnd: properties.WaterFlow_onReachEnd?.(); break
        case PeerEventKind.WaterFlow_onScrollFrameBegin: properties.WaterFlow_onScrollFrameBegin?.((event as WaterFlow_onScrollFrameBegin_event).offset, (event as WaterFlow_onScrollFrameBegin_event).state); break
        case PeerEventKind.WaterFlow_onScrollIndex: properties.WaterFlow_onScrollIndex?.((event as WaterFlow_onScrollIndex_event).first, (event as WaterFlow_onScrollIndex_event).last); break
        case PeerEventKind.UIExtensionComponent_onRemoteReady: properties.UIExtensionComponent_onRemoteReady?.((event as UIExtensionComponent_onRemoteReady_event).parameter); break
        case PeerEventKind.UIExtensionComponent_onResult: properties.UIExtensionComponent_onResult?.((event as UIExtensionComponent_onResult_event).parameter); break
        case PeerEventKind.UIExtensionComponent_onRelease: properties.UIExtensionComponent_onRelease?.((event as UIExtensionComponent_onRelease_event).index); break
        case PeerEventKind.UIExtensionComponent_onError: properties.UIExtensionComponent_onError?.((event as UIExtensionComponent_onError_event).err); break
        case PeerEventKind.UIExtensionComponent_onTerminated: properties.UIExtensionComponent_onTerminated?.((event as UIExtensionComponent_onTerminated_event).parameter); break
        default: throw new Error(`Unknown kind ${event.kind}`)
    }
}