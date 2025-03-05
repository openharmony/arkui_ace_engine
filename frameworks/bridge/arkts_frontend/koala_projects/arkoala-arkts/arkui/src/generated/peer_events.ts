import { int32, float32 } from "@koalaui/common"
import { KStringPtr, KPointer, RuntimeType } from "@koalaui/interop"
import { Callback_Void, Callback_Number_Void, Callback_CalendarSelectedDate_Void, Callback_CalendarRequestedData_Void, Callback_Date_Void, Callback_Boolean_Void, Callback_Array_TouchTestInfo_TouchResult, Callback_ClickEvent_Void, Callback_Boolean_HoverEvent_Void, Callback_MouseEvent_Void, Callback_TouchEvent_Void, Callback_KeyEvent_Void, Callback_KeyEvent_Boolean, Callback_Area_Area_Void, Callback_DragEvent_String_Union_CustomBuilder_DragItemInfo, Callback_DragEvent_String_Void, Callback_PreDragStatus_Void, Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult, Callback_TouchEvent_HitTestMode, Callback_Number_Number_Void, Callback_DatePickerResult_Void, Callback_TerminationInfo_Void, Callback_FormCallbackInfo_Void, Callback_Literal_Number_errcode_String_msg_Void, Literal_Number_errcode_String_msg, Callback_Any_Void, Callback_Number_Number_ComputedBarAttribute, Callback_ItemDragInfo_Number_CustomBuilder, Callback_ItemDragInfo_Void, Callback_ItemDragInfo_Number_Number_Void, Callback_ItemDragInfo_Number_Void, Callback_ItemDragInfo_Number_Number_Boolean_Void, Callback_Number_ScrollState_Literal_Number_offsetRemain, Literal_Number_offsetRemain, Callback_String_Void, Callback_Type_ImageAttribute_onComplete_callback_event_Void, Type_ImageAttribute_onComplete_callback_event, Callback_Number_Number_Number_Void, Callback_Number_Boolean, Callback_Number_Number_Boolean, Callback_ClickEvent_LocationButtonOnClickResult_Void, Callback_Boolean, Callback_NavDestinationContext_Void, Callback_Number_Number_PanelMode_Void, Callback_PanelMode_Void, Callback_ClickEvent_PasteButtonOnClickResult_Void, Callback_Array_Number_Void, Callback_RefreshStatus_Void, Callback_RichEditorSelection_Void, Callback_RichEditorRange_Void, Callback_RichEditorInsertValue_Boolean, Callback_RichEditorTextSpanResult_Void, Callback_TextRange_Void, Callback_RichEditorDeleteValue_Boolean, Callback_RichEditorChangeValue_Boolean, Callback_CutEvent_Void, Callback_CopyEvent_Void, Callback_ClickEvent_SaveButtonOnClickResult_Void, Callback_InsertValue_Boolean, Callback_InsertValue_Void, Callback_DeleteValue_Boolean, Callback_DeleteValue_Void, Callback_Number_String_Void, Callback_Union_Number_Resource_Void, Callback_ResourceStr_Void, Callback_Number_SliderChangeMode_Void, Callback_EnterKeyType_Void, Callback_String_PasteEvent_Void, Callback_String_Number_Void, Type_TextPickerAttribute_onChange_callback, Callback_Union_Number_Array_Number_Void, Callback_Union_String_Array_String_Void, Callback_TimePickerResult_Void, Callback_FullscreenInfo_Void, Callback_PreparedInfo_Void, Callback_PlaybackInfo_Void, Callback_OnPageEndEvent_Void, Callback_OnPageBeginEvent_Void, Callback_OnProgressChangeEvent_Void, Callback_OnTitleReceiveEvent_Void, Callback_OnGeolocationShowEvent_Void, Callback_OnAlertEvent_Boolean, Callback_OnBeforeUnloadEvent_Boolean, Callback_OnConfirmEvent_Boolean, Callback_OnPromptEvent_Boolean, Callback_OnConsoleEvent_Boolean, Callback_OnErrorReceiveEvent_Void, Callback_OnHttpErrorReceiveEvent_Void, Callback_OnDownloadStartEvent_Void, Callback_OnRefreshAccessedHistoryEvent_Void, Type_WebAttribute_onUrlLoadIntercept_callback, Literal_Union_String_WebResourceRequest_data, Callback_Literal_Function_handler_Object_error_Void, Literal_Function_handler_Object_error, Callback_OnRenderExitedEvent_Void, Callback_Literal_Object_detail_Boolean, Literal_Object_detail, Callback_OnShowFileSelectorEvent_Boolean, Type_WebAttribute_onFileSelectorShow_callback, Literal_Function_callback__Object_fileSelector, Callback_OnResourceLoadEvent_Void, Callback_OnScaleChangeEvent_Void, Callback_OnHttpAuthRequestEvent_Boolean, Callback_OnInterceptRequestEvent_WebResourceResponse, Callback_OnPermissionRequestEvent_Void, Callback_OnScreenCaptureRequestEvent_Void, Callback_OnContextMenuShowEvent_Boolean, Callback_OnSearchResultReceiveEvent_Void, Callback_OnScrollEvent_Void, Callback_OnSslErrorEventReceiveEvent_Void, Callback_OnClientAuthenticationEvent_Void, Callback_OnWindowNewEvent_Void, Callback_OnTouchIconUrlReceivedEvent_Void, Callback_OnFaviconReceivedEvent_Void, Callback_OnPageVisibleEvent_Void, Callback_OnDataResubmittedEvent_Void, Callback_OnAudioStateChangedEvent_Void, Callback_OnFirstContentfulPaintEvent_Void, Callback_OnLoadInterceptEvent_Boolean, Callback_OnOverScrollEvent_Void, Callback_NativeEmbedDataInfo_Void, Callback_NativeEmbedTouchInfo_Void, Callback_UIExtensionProxy_Void, Callback_Literal_Number_code_Want_want_Void, Literal_Number_code_Want_want } from "./SyntheticDeclarations"
import { OnAlphabetIndexerSelectCallback, OnAlphabetIndexerRequestPopupDataCallback, OnAlphabetIndexerPopupSelectCallback } from "./ArkAlphabetIndexerInterfaces"
import { CalendarSelectedDate, CalendarRequestedData } from "./ArkCalendarInterfaces"
import { VoidCallback, Area, SizeOptions, ResourceStr } from "./ArkUnitsInterfaces"
import { OnCheckboxChangeCallback } from "./ArkCheckboxInterfaces"
import { OnCheckboxGroupChangeCallback, CheckboxGroupResult } from "./ArkCheckboxgroupInterfaces"
import { TouchTestInfo, TouchResult, AccessibilityCallback, CustomBuilder, DragItemInfo, PreDragStatus, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, SizeChangeCallback, VisibleAreaChangeCallback, ItemDragInfo } from "./ArkCommonInterfaces"
import { ClickEvent } from "./ArkClickEventMaterialized"
import { HoverEvent } from "./ArkHoverEventMaterialized"
import { AccessibilityHoverEvent } from "./ArkAccessibilityHoverEventMaterialized"
import { MouseEvent } from "./ArkMouseEventMaterialized"
import { TouchEvent } from "./ArkTouchEventMaterialized"
import { KeyEvent } from "./ArkKeyEventMaterialized"
import { DragEvent } from "./ArkDragEventMaterialized"
import { GestureInfo, GestureJudgeResult } from "./ArkGestureInterfaces"
import { BaseGestureEvent } from "./ArkBaseGestureEventMaterialized"
import { GestureRecognizer } from "./ArkGestureRecognizerMaterialized"
import { HitTestMode, Edge } from "./ArkEnumsInterfaces"
import { ScrollOnScrollCallback, OnScrollEdgeCallback, OnScrollFrameBeginCallback, OnScrollFrameBeginHandlerResult } from "./ArkScrollInterfaces"
import { ScrollState, OnScrollVisibleContentChangeCallback, VisibleListContentInfo } from "./ArkListInterfaces"
import { DatePickerResult } from "./ArkDatePickerInterfaces"
import { TerminationInfo } from "./ArkEmbeddedComponentInterfaces"
import { ErrorCallback, BusinessError, Want } from "./ArkArkuiExternalInterfaces"
import { OnFoldStatusChangeCallback, OnFoldStatusChangeInfo, OnHoverStatusChangeCallback, HoverEventParam } from "./ArkFolderStackInterfaces"
import { FormCallbackInfo } from "./ArkFormComponentInterfaces"
import { ComputedBarAttribute } from "./ArkGridInterfaces"
import { ImageErrorCallback, ImageError } from "./ArkImageInterfaces"
import { ImageCompleteCallback, ImageLoadResult } from "./ArkImageSpanInterfaces"
import { LocationButtonOnClickResult } from "./ArkLocationButtonInterfaces"
import { NavDestinationContext } from "./ArkNavDestinationContextMaterialized"
import { PanelMode } from "./ArkPanelInterfaces"
import { PasteButtonOnClickResult } from "./ArkPasteButtonInterfaces"
import { PluginErrorCallback, PluginErrorData } from "./ArkPluginComponentInterfaces"
import { RefreshStatus } from "./ArkRefreshInterfaces"
import { RichEditorSelection, RichEditorRange, RichEditorInsertValue, RichEditorTextSpanResult, RichEditorDeleteValue, PasteEventCallback, PasteEvent, SubmitCallback, RichEditorChangeValue, CutEvent, CopyEvent } from "./ArkRichEditorInterfaces"
import { TextRange, OnDidChangeCallback, EditableTextOnChangeCallback, PreviewText, InsertValue, DeleteValue } from "./ArkTextCommonInterfaces"
import { EnterKeyType, OnTextSelectionChangeCallback, OnContentScrollCallback, OnPasteCallback, OnSubmitCallback } from "./ArkTextInputInterfaces"
import { SubmitEvent } from "./ArkSubmitEventMaterialized"
import { SaveButtonOnClickResult } from "./ArkSaveButtonInterfaces"
import { SearchSubmitCallback } from "./ArkSearchInterfaces"
import { Resource } from "./ArkResourceInterfaces"
import { SliderChangeMode } from "./ArkSliderInterfaces"
import { OnSwiperAnimationStartCallback, SwiperAnimationEvent, OnSwiperAnimationEndCallback, OnSwiperGestureSwipeCallback, ContentDidScrollCallback } from "./ArkSwiperInterfaces"
import { OnTabsAnimationStartCallback, TabsAnimationEvent, OnTabsAnimationEndCallback, OnTabsGestureSwipeCallback, TabsCustomContentTransitionCallback, TabContentAnimatedTransition, OnTabsContentWillChangeCallback } from "./ArkTabsInterfaces"
import { TextAreaSubmitCallback } from "./ArkTextAreaInterfaces"
import { TimePickerResult } from "./ArkTimePickerInterfaces"
import { FullscreenInfo, PreparedInfo, PlaybackInfo } from "./ArkVideoInterfaces"
import { OnPageEndEvent, OnPageBeginEvent, OnProgressChangeEvent, OnTitleReceiveEvent, OnGeolocationShowEvent, OnAlertEvent, OnBeforeUnloadEvent, OnConfirmEvent, OnPromptEvent, OnConsoleEvent, OnErrorReceiveEvent, OnHttpErrorReceiveEvent, OnDownloadStartEvent, OnRefreshAccessedHistoryEvent, OnRenderExitedEvent, OnShowFileSelectorEvent, OnResourceLoadEvent, OnFullScreenEnterCallback, FullScreenEnterEvent, OnScaleChangeEvent, OnHttpAuthRequestEvent, OnInterceptRequestEvent, OnPermissionRequestEvent, OnScreenCaptureRequestEvent, OnContextMenuShowEvent, OnContextMenuHideCallback, OnSearchResultReceiveEvent, OnScrollEvent, OnSslErrorEventReceiveEvent, OnSslErrorEventCallback, SslErrorEvent, OnClientAuthenticationEvent, OnWindowNewEvent, OnTouchIconUrlReceivedEvent, OnFaviconReceivedEvent, OnPageVisibleEvent, OnDataResubmittedEvent, OnAudioStateChangedEvent, OnFirstContentfulPaintEvent, OnFirstMeaningfulPaintCallback, FirstMeaningfulPaint, OnLargestContentfulPaintCallback, LargestContentfulPaint, OnLoadInterceptEvent, OnOverScrollEvent, OnSafeBrowsingCheckResultCallback, ThreatType, OnNavigationEntryCommittedCallback, LoadCommittedDetails, OnIntelligentTrackingPreventionCallback, IntelligentTrackingPreventionDetails, NativeEmbedDataInfo, OnNativeEmbedVisibilityChangeCallback, NativeEmbedVisibilityInfo, NativeEmbedTouchInfo, OnOverrideUrlLoadingCallback, OnRenderProcessNotRespondingCallback, RenderProcessNotRespondingData, OnRenderProcessRespondingCallback, OnViewportFitChangedCallback, ViewportFit, WebKeyboardCallback, WebKeyboardCallbackInfo, WebKeyboardOptions, OnAdsBlockedCallback, AdsBlockedDetails } from "./ArkWebInterfaces"
import { WebResourceRequest } from "./ArkWebResourceRequestMaterialized"
import { WebResourceResponse } from "./ArkWebResourceResponseMaterialized"
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
    readonly kind: PeerEventKind
}
export interface AbilityComponent_onDisconnect_event extends PeerEvent {
    readonly kind: PeerEventKind
}
export interface AlphabetIndexer_onSelected_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly index: number
}
export interface AlphabetIndexer_onSelect_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly index: number
}
export interface AlphabetIndexer_onRequestPopupData_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly index: number
}
export interface AlphabetIndexer_onPopupSelect_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly index: number
}
export interface AlphabetIndexer__onChangeEvent_selected_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly index: number
}
export interface Animator_onStart_event extends PeerEvent {
    readonly kind: PeerEventKind
}
export interface Animator_onPause_event extends PeerEvent {
    readonly kind: PeerEventKind
}
export interface Animator_onRepeat_event extends PeerEvent {
    readonly kind: PeerEventKind
}
export interface Animator_onCancel_event extends PeerEvent {
    readonly kind: PeerEventKind
}
export interface Animator_onFinish_event extends PeerEvent {
    readonly kind: PeerEventKind
}
export interface Animator_onFrame_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly index: number
}
export interface Calendar_onSelectChange_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly event: CalendarSelectedDate
}
export interface Calendar_onRequestData_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly event: CalendarRequestedData
}
export interface CalendarPicker_onChange_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: Date
}
export interface Canvas_onReady_event extends PeerEvent {
    readonly kind: PeerEventKind
}
export interface Checkbox_onChange_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly value: boolean
}
export interface Checkbox__onChangeEvent_select_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: boolean
}
export interface CheckboxGroup_onChange_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly value: CheckboxGroupResult
}
export interface CheckboxGroup__onChangeEvent_selectAll_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: boolean
}
export interface CommonMethod_onChildTouchTest_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly value: Array<TouchTestInfo>
}
export interface CommonMethod_onClick0_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly event: ClickEvent
}
export interface CommonMethod_onClick1_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly event: ClickEvent
}
export interface CommonMethod_onHover_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly isHover: boolean
    readonly event: HoverEvent
}
export interface CommonMethod_onAccessibilityHover_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly isHover: boolean
    readonly event: AccessibilityHoverEvent
}
export interface CommonMethod_onMouse_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly event: MouseEvent
}
export interface CommonMethod_onTouch_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly event: TouchEvent
}
export interface CommonMethod_onKeyEvent_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly event: KeyEvent
}
export interface CommonMethod_onKeyPreIme_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: KeyEvent
}
export interface CommonMethod_onFocus_event extends PeerEvent {
    readonly kind: PeerEventKind
}
export interface CommonMethod_onBlur_event extends PeerEvent {
    readonly kind: PeerEventKind
}
export interface CommonMethod_onAppear_event extends PeerEvent {
    readonly kind: PeerEventKind
}
export interface CommonMethod_onDisAppear_event extends PeerEvent {
    readonly kind: PeerEventKind
}
export interface CommonMethod_onAttach_event extends PeerEvent {
    readonly kind: PeerEventKind
}
export interface CommonMethod_onDetach_event extends PeerEvent {
    readonly kind: PeerEventKind
}
export interface CommonMethod_onAreaChange_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly oldValue: Area
    readonly newValue: Area
}
export interface CommonMethod_onDragStart_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly event: DragEvent
    readonly extraParams?: string | undefined
}
export interface CommonMethod_onDragEnter_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly event: DragEvent
    readonly extraParams?: string | undefined
}
export interface CommonMethod_onDragMove_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly event: DragEvent
    readonly extraParams?: string | undefined
}
export interface CommonMethod_onDragLeave_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly event: DragEvent
    readonly extraParams?: string | undefined
}
export interface CommonMethod_onDrop_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly event: DragEvent
    readonly extraParams?: string | undefined
}
export interface CommonMethod_onDragEnd_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly event: DragEvent
    readonly extraParams?: string | undefined
}
export interface CommonMethod_onPreDrag_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: PreDragStatus
}
export interface CommonMethod_accessibilityVirtualNode_event extends PeerEvent {
    readonly kind: PeerEventKind
}
export interface CommonMethod_onGestureJudgeBegin_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly gestureInfo: GestureInfo
    readonly event: BaseGestureEvent
}
export interface CommonMethod_onGestureRecognizerJudgeBegin0_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly event: BaseGestureEvent
    readonly current: GestureRecognizer
    readonly recognizers: Array<GestureRecognizer>
}
export interface CommonMethod_onGestureRecognizerJudgeBegin1_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly event: BaseGestureEvent
    readonly current: GestureRecognizer
    readonly recognizers: Array<GestureRecognizer>
}
export interface CommonMethod_shouldBuiltInRecognizerParallelWith_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly current: GestureRecognizer
    readonly others: Array<GestureRecognizer>
}
export interface CommonMethod_onTouchIntercept_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: TouchEvent
}
export interface CommonMethod_onSizeChange_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly oldValue: SizeOptions
    readonly newValue: SizeOptions
}
export interface CommonMethod_background_event extends PeerEvent {
    readonly kind: PeerEventKind
}
export interface CommonMethod_bindContextMenu0_event extends PeerEvent {
    readonly kind: PeerEventKind
}
export interface CommonMethod_bindContextMenu1_event extends PeerEvent {
    readonly kind: PeerEventKind
}
export interface CommonMethod_bindContentCover0_event extends PeerEvent {
    readonly kind: PeerEventKind
}
export interface CommonMethod_bindContentCover1_event extends PeerEvent {
    readonly kind: PeerEventKind
}
export interface CommonMethod_bindSheet_event extends PeerEvent {
    readonly kind: PeerEventKind
}
export interface CommonMethod_onVisibleAreaChange_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly isExpanding: boolean
    readonly currentRatio: number
}
export interface ScrollableCommonMethod_onScroll_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly first: number
    readonly last: number
}
export interface ScrollableCommonMethod_onDidScroll_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly xOffset: number
    readonly yOffset: number
    readonly scrollState: ScrollState
}
export interface ScrollableCommonMethod_onReachStart_event extends PeerEvent {
    readonly kind: PeerEventKind
}
export interface ScrollableCommonMethod_onReachEnd_event extends PeerEvent {
    readonly kind: PeerEventKind
}
export interface ScrollableCommonMethod_onScrollStart_event extends PeerEvent {
    readonly kind: PeerEventKind
}
export interface ScrollableCommonMethod_onScrollStop_event extends PeerEvent {
    readonly kind: PeerEventKind
}
export interface Counter_onInc_event extends PeerEvent {
    readonly kind: PeerEventKind
}
export interface Counter_onDec_event extends PeerEvent {
    readonly kind: PeerEventKind
}
export interface DatePicker_onChange_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly value: DatePickerResult
}
export interface DatePicker_onDateChange_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: Date
}
export interface DatePicker__onChangeEvent_selected_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: Date
}
export interface EmbeddedComponent_onTerminated_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: TerminationInfo
}
export interface EmbeddedComponent_onError_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly err: BusinessError
}
export interface FolderStack_onFolderStateChange_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly event: OnFoldStatusChangeInfo
}
export interface FolderStack_onHoverStatusChange_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly param: HoverEventParam
}
export interface FormComponent_onAcquired_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: FormCallbackInfo
}
export interface FormComponent_onError_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly info: Literal_Number_errcode_String_msg
}
export interface FormComponent_onRouter_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly info: object
}
export interface FormComponent_onUninstall_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: FormCallbackInfo
}
export interface FormComponent_onLoad_event extends PeerEvent {
    readonly kind: PeerEventKind
}
export interface Gauge_description_event extends PeerEvent {
    readonly kind: PeerEventKind
}
export interface Grid_onScrollBarUpdate_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly index: number
    readonly offset: number
}
export interface Grid_onScrollIndex_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly first: number
    readonly last: number
}
export interface Grid_onItemDragStart_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly event: ItemDragInfo
    readonly itemIndex: number
}
export interface Grid_onItemDragEnter_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly event: ItemDragInfo
}
export interface Grid_onItemDragMove_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly event: ItemDragInfo
    readonly itemIndex: number
    readonly insertIndex: number
}
export interface Grid_onItemDragLeave_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly event: ItemDragInfo
    readonly itemIndex: number
}
export interface Grid_onItemDrop_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly event: ItemDragInfo
    readonly itemIndex: number
    readonly insertIndex: number
    readonly isSuccess: boolean
}
export interface Grid_onScroll_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly first: number
    readonly last: number
}
export interface Grid_onReachStart_event extends PeerEvent {
    readonly kind: PeerEventKind
}
export interface Grid_onReachEnd_event extends PeerEvent {
    readonly kind: PeerEventKind
}
export interface Grid_onScrollStart_event extends PeerEvent {
    readonly kind: PeerEventKind
}
export interface Grid_onScrollStop_event extends PeerEvent {
    readonly kind: PeerEventKind
}
export interface Grid_onScrollFrameBegin_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly offset: number
    readonly state: ScrollState
}
export interface GridItem_onSelect_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: boolean
}
export interface GridItem__onChangeEvent_selected_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: boolean
}
export interface GridRow_onBreakpointChange_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly breakpoints: string
}
export interface Image_onComplete_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly event?: Type_ImageAttribute_onComplete_callback_event | undefined
}
export interface Image_onError_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly error: ImageError
}
export interface Image_onFinish_event extends PeerEvent {
    readonly kind: PeerEventKind
}
export interface ImageAnimator_onStart_event extends PeerEvent {
    readonly kind: PeerEventKind
}
export interface ImageAnimator_onPause_event extends PeerEvent {
    readonly kind: PeerEventKind
}
export interface ImageAnimator_onRepeat_event extends PeerEvent {
    readonly kind: PeerEventKind
}
export interface ImageAnimator_onCancel_event extends PeerEvent {
    readonly kind: PeerEventKind
}
export interface ImageAnimator_onFinish_event extends PeerEvent {
    readonly kind: PeerEventKind
}
export interface ImageSpan_onComplete_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly result: ImageLoadResult
}
export interface ImageSpan_onError_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly error: ImageError
}
export interface List_onScroll_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly first: number
    readonly last: number
}
export interface List_onScrollIndex_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly start: number
    readonly end: number
    readonly center: number
}
export interface List_onScrollVisibleContentChange_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly start: VisibleListContentInfo
    readonly end: VisibleListContentInfo
}
export interface List_onReachStart_event extends PeerEvent {
    readonly kind: PeerEventKind
}
export interface List_onReachEnd_event extends PeerEvent {
    readonly kind: PeerEventKind
}
export interface List_onScrollStart_event extends PeerEvent {
    readonly kind: PeerEventKind
}
export interface List_onScrollStop_event extends PeerEvent {
    readonly kind: PeerEventKind
}
export interface List_onItemDelete_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly index: number
}
export interface List_onItemMove_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly from: number
    readonly to: number
}
export interface List_onItemDragStart_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly event: ItemDragInfo
    readonly itemIndex: number
}
export interface List_onItemDragEnter_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly event: ItemDragInfo
}
export interface List_onItemDragMove_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly event: ItemDragInfo
    readonly itemIndex: number
    readonly insertIndex: number
}
export interface List_onItemDragLeave_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly event: ItemDragInfo
    readonly itemIndex: number
}
export interface List_onItemDrop_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly event: ItemDragInfo
    readonly itemIndex: number
    readonly insertIndex: number
    readonly isSuccess: boolean
}
export interface List_onScrollFrameBegin_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly offset: number
    readonly state: ScrollState
}
export interface ListItem_onSelect_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: boolean
}
export interface ListItem__onChangeEvent_selected_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: boolean
}
export interface LocationButton_onClick_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly event: ClickEvent
    readonly result: LocationButtonOnClickResult
}
export interface Marquee_onStart_event extends PeerEvent {
    readonly kind: PeerEventKind
}
export interface Marquee_onBounce_event extends PeerEvent {
    readonly kind: PeerEventKind
}
export interface Marquee_onFinish_event extends PeerEvent {
    readonly kind: PeerEventKind
}
export interface MenuItem_onChange_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: boolean
}
export interface MenuItem__onChangeEvent_selected_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: boolean
}
export interface NavDestination_onShown_event extends PeerEvent {
    readonly kind: PeerEventKind
}
export interface NavDestination_onHidden_event extends PeerEvent {
    readonly kind: PeerEventKind
}
export interface NavDestination_onBackPressed_event extends PeerEvent {
    readonly kind: PeerEventKind
}
export interface NavDestination_onReady_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: NavDestinationContext
}
export interface NavDestination_onWillAppear_event extends PeerEvent {
    readonly kind: PeerEventKind
}
export interface NavDestination_onWillDisappear_event extends PeerEvent {
    readonly kind: PeerEventKind
}
export interface NavDestination_onWillShow_event extends PeerEvent {
    readonly kind: PeerEventKind
}
export interface NavDestination_onWillHide_event extends PeerEvent {
    readonly kind: PeerEventKind
}
export interface NavRouter_onStateChange_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: boolean
}
export interface Panel_onChange_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly width: number
    readonly height: number
    readonly mode: PanelMode
}
export interface Panel_onHeightChange_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly index: number
}
export interface Panel__onChangeEvent_mode_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly mode: PanelMode
}
export interface PasteButton_onClick_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly event: ClickEvent
    readonly result: PasteButtonOnClickResult
}
export interface PatternLock_onPatternComplete_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly input: Array<number>
}
export interface PatternLock_onDotConnect_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly index: number
}
export interface PluginComponent_onComplete_event extends PeerEvent {
    readonly kind: PeerEventKind
}
export interface PluginComponent_onError_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly info: PluginErrorData
}
export interface Radio_onChange_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: boolean
}
export interface Radio__onChangeEvent_checked_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: boolean
}
export interface Rating_onChange_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly index: number
}
export interface Rating__onChangeEvent_rating_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly index: number
}
export interface Refresh_onStateChange_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly state: RefreshStatus
}
export interface Refresh_onRefreshing_event extends PeerEvent {
    readonly kind: PeerEventKind
}
export interface Refresh_onOffsetChange_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly index: number
}
export interface Refresh__onChangeEvent_refreshing_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: boolean
}
export interface RichEditor_onReady_event extends PeerEvent {
    readonly kind: PeerEventKind
}
export interface RichEditor_onSelect_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: RichEditorSelection
}
export interface RichEditor_onSelectionChange_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: RichEditorRange
}
export interface RichEditor_aboutToIMEInput_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: RichEditorInsertValue
}
export interface RichEditor_onIMEInputComplete_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: RichEditorTextSpanResult
}
export interface RichEditor_onDidIMEInput_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: TextRange
}
export interface RichEditor_aboutToDelete_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: RichEditorDeleteValue
}
export interface RichEditor_onDeleteComplete_event extends PeerEvent {
    readonly kind: PeerEventKind
}
export interface RichEditor_onPaste_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly event?: PasteEvent | undefined
}
export interface RichEditor_onEditingChange_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: boolean
}
export interface RichEditor_onSubmit_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly enterKey: EnterKeyType
    readonly event: SubmitEvent
}
export interface RichEditor_onWillChange_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: RichEditorChangeValue
}
export interface RichEditor_onDidChange_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly rangeBefore: TextRange
    readonly rangeAfter: TextRange
}
export interface RichEditor_onCut_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: CutEvent
}
export interface RichEditor_onCopy_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: CopyEvent
}
export interface RichEditor_bindSelectionMenu_event extends PeerEvent {
    readonly kind: PeerEventKind
}
export interface RichEditor_customKeyboard_event extends PeerEvent {
    readonly kind: PeerEventKind
}
export interface RichText_onStart_event extends PeerEvent {
    readonly kind: PeerEventKind
}
export interface RichText_onComplete_event extends PeerEvent {
    readonly kind: PeerEventKind
}
export interface SaveButton_onClick_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly event: ClickEvent
    readonly result: SaveButtonOnClickResult
}
export interface Scroll_onScroll_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly first: number
    readonly last: number
}
export interface Scroll_onDidScroll_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly xOffset: number
    readonly yOffset: number
    readonly scrollState: ScrollState
}
export interface Scroll_onScrollEdge_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly side: Edge
}
export interface Scroll_onScrollStart_event extends PeerEvent {
    readonly kind: PeerEventKind
}
export interface Scroll_onScrollEnd_event extends PeerEvent {
    readonly kind: PeerEventKind
}
export interface Scroll_onScrollStop_event extends PeerEvent {
    readonly kind: PeerEventKind
}
export interface Scroll_onScrollFrameBegin_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly offset: number
    readonly state: ScrollState
}
export interface Search_onEditChange_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: boolean
}
export interface Search_onSubmit0_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly breakpoints: string
}
export interface Search_onSubmit1_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly searchContent: string
    readonly event?: SubmitEvent | undefined
}
export interface Search_onChange_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly value: string
    readonly previewText?: PreviewText | undefined
}
export interface Search_onTextSelectionChange_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly selectionStart: number
    readonly selectionEnd: number
}
export interface Search_onContentScroll_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly totalOffsetX: number
    readonly totalOffsetY: number
}
export interface Search_onCopy_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly breakpoints: string
}
export interface Search_onCut_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly breakpoints: string
}
export interface Search_onPaste_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly content: string
    readonly event: PasteEvent
}
export interface Search_onWillInsert_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: InsertValue
}
export interface Search_onDidInsert_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: InsertValue
}
export interface Search_onWillDelete_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: DeleteValue
}
export interface Search_onDidDelete_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: DeleteValue
}
export interface Search_customKeyboard_event extends PeerEvent {
    readonly kind: PeerEventKind
}
export interface Search__onChangeEvent_value_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly breakpoints: string
}
export interface Select_onSelect_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly index: number
    readonly value: string
}
export interface Select__onChangeEvent_selected_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly selected: number | Resource
}
export interface Select__onChangeEvent_value_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly value: ResourceStr
}
export interface Slider_onChange_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly value: number
    readonly mode: SliderChangeMode
}
export interface Slider__onChangeEvent_value_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly index: number
}
export interface Stepper_onFinish_event extends PeerEvent {
    readonly kind: PeerEventKind
}
export interface Stepper_onSkip_event extends PeerEvent {
    readonly kind: PeerEventKind
}
export interface Stepper_onChange_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly first: number
    readonly last: number
}
export interface Stepper_onNext_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly first: number
    readonly last: number
}
export interface Stepper_onPrevious_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly first: number
    readonly last: number
}
export interface Stepper__onChangeEvent_index_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly index: number
}
export interface Swiper_onChange_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly index: number
}
export interface Swiper_onAnimationStart_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly index: number
    readonly targetIndex: number
    readonly extraInfo: SwiperAnimationEvent
}
export interface Swiper_onAnimationEnd_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly index: number
    readonly extraInfo: SwiperAnimationEvent
}
export interface Swiper_onGestureSwipe_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly index: number
    readonly extraInfo: SwiperAnimationEvent
}
export interface Swiper_onContentDidScroll_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly selectedIndex: number
    readonly index: number
    readonly position: number
    readonly mainAxisLength: number
}
export interface Swiper__onChangeEvent_index_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly index: number
}
export interface IndicatorComponent_onChange_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly index: number
}
export interface Tabs_onChange_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly index: number
}
export interface Tabs_onTabBarClick_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly index: number
}
export interface Tabs_onAnimationStart_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly index: number
    readonly targetIndex: number
    readonly extraInfo: TabsAnimationEvent
}
export interface Tabs_onAnimationEnd_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly index: number
    readonly extraInfo: TabsAnimationEvent
}
export interface Tabs_onGestureSwipe_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly index: number
    readonly extraInfo: TabsAnimationEvent
}
export interface Tabs_customContentTransition_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly from: number
    readonly to: number
}
export interface Tabs_onContentWillChange_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly currentIndex: number
    readonly comingIndex: number
}
export interface Tabs__onChangeEvent_index_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly index: number
}
export interface TabContent_onWillShow_event extends PeerEvent {
    readonly kind: PeerEventKind
}
export interface TabContent_onWillHide_event extends PeerEvent {
    readonly kind: PeerEventKind
}
export interface Text_onCopy_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly breakpoints: string
}
export interface Text_onTextSelectionChange_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly first: number
    readonly last: number
}
export interface Text_bindSelectionMenu_event extends PeerEvent {
    readonly kind: PeerEventKind
}
export interface TextArea_onSubmit0_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly enterKey: EnterKeyType
}
export interface TextArea_onSubmit1_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly enterKeyType: EnterKeyType
    readonly event?: SubmitEvent | undefined
}
export interface TextArea_onChange_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly value: string
    readonly previewText?: PreviewText | undefined
}
export interface TextArea_onTextSelectionChange_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly first: number
    readonly last: number
}
export interface TextArea_onContentScroll_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly first: number
    readonly last: number
}
export interface TextArea_onEditChange_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: boolean
}
export interface TextArea_onCopy_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly breakpoints: string
}
export interface TextArea_onCut_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly breakpoints: string
}
export interface TextArea_onPaste_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly value: string
    readonly event: PasteEvent
}
export interface TextArea_onWillInsert_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: InsertValue
}
export interface TextArea_onDidInsert_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: InsertValue
}
export interface TextArea_onWillDelete_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: DeleteValue
}
export interface TextArea_onDidDelete_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: DeleteValue
}
export interface TextArea_customKeyboard_event extends PeerEvent {
    readonly kind: PeerEventKind
}
export interface TextArea__onChangeEvent_text_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly value: ResourceStr
}
export interface TextClock_onDateChange_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly index: number
}
export interface TextInput_onEditChanged_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: boolean
}
export interface TextInput_onEditChange_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: boolean
}
export interface TextInput_onSubmit_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly enterKey: EnterKeyType
    readonly event: SubmitEvent
}
export interface TextInput_onChange_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly value: string
    readonly previewText?: PreviewText | undefined
}
export interface TextInput_onTextSelectionChange_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly selectionStart: number
    readonly selectionEnd: number
}
export interface TextInput_onContentScroll_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly totalOffsetX: number
    readonly totalOffsetY: number
}
export interface TextInput_onCopy_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly breakpoints: string
}
export interface TextInput_onCut_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly breakpoints: string
}
export interface TextInput_onPaste_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly content: string
    readonly event: PasteEvent
}
export interface TextInput_showUnit_event extends PeerEvent {
    readonly kind: PeerEventKind
}
export interface TextInput_onSecurityStateChange_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: boolean
}
export interface TextInput_onWillInsert_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: InsertValue
}
export interface TextInput_onDidInsert_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: InsertValue
}
export interface TextInput_onWillDelete_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: DeleteValue
}
export interface TextInput_onDidDelete_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: DeleteValue
}
export interface TextInput_customKeyboard_event extends PeerEvent {
    readonly kind: PeerEventKind
}
export interface TextInput__onChangeEvent_text_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly value: ResourceStr
}
export interface TextPicker_onAccept_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly value: string
    readonly index: number
}
export interface TextPicker_onCancel_event extends PeerEvent {
    readonly kind: PeerEventKind
}
export interface TextPicker_onChange_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly value: string | Array<string>
    readonly index: number | Array<number>
}
export interface TextPicker__onChangeEvent_selected_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly selected: number | Array<number>
}
export interface TextPicker__onChangeEvent_value_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly value: string | Array<string>
}
export interface TextTimer_onTimer_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly first: number
    readonly last: number
}
export interface TimePicker_onChange_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly value: TimePickerResult
}
export interface TimePicker__onChangeEvent_selected_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: Date
}
export interface Toggle_onChange_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: boolean
}
export interface Toggle__onChangeEvent_isOn_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: boolean
}
export interface Video_onStart_event extends PeerEvent {
    readonly kind: PeerEventKind
}
export interface Video_onPause_event extends PeerEvent {
    readonly kind: PeerEventKind
}
export interface Video_onFinish_event extends PeerEvent {
    readonly kind: PeerEventKind
}
export interface Video_onFullscreenChange_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: FullscreenInfo
}
export interface Video_onPrepared_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: PreparedInfo
}
export interface Video_onSeeking_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: PlaybackInfo
}
export interface Video_onSeeked_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: PlaybackInfo
}
export interface Video_onUpdate_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: PlaybackInfo
}
export interface Video_onError_event extends PeerEvent {
    readonly kind: PeerEventKind
}
export interface Video_onStop_event extends PeerEvent {
    readonly kind: PeerEventKind
}
export interface Web_onPageEnd_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: OnPageEndEvent
}
export interface Web_onPageBegin_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: OnPageBeginEvent
}
export interface Web_onProgressChange_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: OnProgressChangeEvent
}
export interface Web_onTitleReceive_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: OnTitleReceiveEvent
}
export interface Web_onGeolocationHide_event extends PeerEvent {
    readonly kind: PeerEventKind
}
export interface Web_onGeolocationShow_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: OnGeolocationShowEvent
}
export interface Web_onRequestSelected_event extends PeerEvent {
    readonly kind: PeerEventKind
}
export interface Web_onAlert_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: OnAlertEvent
}
export interface Web_onBeforeUnload_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: OnBeforeUnloadEvent
}
export interface Web_onConfirm_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: OnConfirmEvent
}
export interface Web_onPrompt_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: OnPromptEvent
}
export interface Web_onConsole_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: OnConsoleEvent
}
export interface Web_onErrorReceive_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: OnErrorReceiveEvent
}
export interface Web_onHttpErrorReceive_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: OnHttpErrorReceiveEvent
}
export interface Web_onDownloadStart_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: OnDownloadStartEvent
}
export interface Web_onRefreshAccessedHistory_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: OnRefreshAccessedHistoryEvent
}
export interface Web_onUrlLoadIntercept_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly event?: Literal_Union_String_WebResourceRequest_data | undefined
}
export interface Web_onSslErrorReceive_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly event?: Literal_Function_handler_Object_error | undefined
}
export interface Web_onRenderExited0_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: OnRenderExitedEvent
}
export interface Web_onRenderExited1_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly event?: Literal_Object_detail | undefined
}
export interface Web_onShowFileSelector_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: OnShowFileSelectorEvent
}
export interface Web_onFileSelectorShow_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly event?: Literal_Function_callback__Object_fileSelector | undefined
}
export interface Web_onResourceLoad_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: OnResourceLoadEvent
}
export interface Web_onFullScreenExit_event extends PeerEvent {
    readonly kind: PeerEventKind
}
export interface Web_onFullScreenEnter_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly event: FullScreenEnterEvent
}
export interface Web_onScaleChange_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: OnScaleChangeEvent
}
export interface Web_onHttpAuthRequest_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: OnHttpAuthRequestEvent
}
export interface Web_onInterceptRequest_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: OnInterceptRequestEvent
}
export interface Web_onPermissionRequest_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: OnPermissionRequestEvent
}
export interface Web_onScreenCaptureRequest_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: OnScreenCaptureRequestEvent
}
export interface Web_onContextMenuShow_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: OnContextMenuShowEvent
}
export interface Web_onContextMenuHide_event extends PeerEvent {
    readonly kind: PeerEventKind
}
export interface Web_onSearchResultReceive_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: OnSearchResultReceiveEvent
}
export interface Web_onScroll_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: OnScrollEvent
}
export interface Web_onSslErrorEventReceive_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: OnSslErrorEventReceiveEvent
}
export interface Web_onSslErrorEvent_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly sslErrorEvent: SslErrorEvent
}
export interface Web_onClientAuthenticationRequest_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: OnClientAuthenticationEvent
}
export interface Web_onWindowNew_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: OnWindowNewEvent
}
export interface Web_onWindowExit_event extends PeerEvent {
    readonly kind: PeerEventKind
}
export interface Web_onInterceptKeyEvent_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: KeyEvent
}
export interface Web_onTouchIconUrlReceived_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: OnTouchIconUrlReceivedEvent
}
export interface Web_onFaviconReceived_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: OnFaviconReceivedEvent
}
export interface Web_onPageVisible_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: OnPageVisibleEvent
}
export interface Web_onDataResubmitted_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: OnDataResubmittedEvent
}
export interface Web_onAudioStateChanged_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: OnAudioStateChangedEvent
}
export interface Web_onFirstContentfulPaint_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: OnFirstContentfulPaintEvent
}
export interface Web_onFirstMeaningfulPaint_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly firstMeaningfulPaint: FirstMeaningfulPaint
}
export interface Web_onLargestContentfulPaint_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly largestContentfulPaint: LargestContentfulPaint
}
export interface Web_onLoadIntercept_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: OnLoadInterceptEvent
}
export interface Web_onControllerAttached_event extends PeerEvent {
    readonly kind: PeerEventKind
}
export interface Web_onOverScroll_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: OnOverScrollEvent
}
export interface Web_onSafeBrowsingCheckResult_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly threatType: ThreatType
}
export interface Web_onNavigationEntryCommitted_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly loadCommittedDetails: LoadCommittedDetails
}
export interface Web_onIntelligentTrackingPreventionResult_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly details: IntelligentTrackingPreventionDetails
}
export interface Web_onNativeEmbedLifecycleChange_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly event: NativeEmbedDataInfo
}
export interface Web_onNativeEmbedVisibilityChange_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly nativeEmbedVisibilityInfo: NativeEmbedVisibilityInfo
}
export interface Web_onNativeEmbedGestureEvent_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly event: NativeEmbedTouchInfo
}
export interface Web_onOverrideUrlLoading_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly webResourceRequest: WebResourceRequest
}
export interface Web_onRenderProcessNotResponding_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly data: RenderProcessNotRespondingData
}
export interface Web_onRenderProcessResponding_event extends PeerEvent {
    readonly kind: PeerEventKind
}
export interface Web_onViewportFitChanged_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly viewportFit: ViewportFit
}
export interface Web_onInterceptKeyboardAttach_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly keyboardCallbackInfo: WebKeyboardCallbackInfo
}
export interface Web_onAdsBlocked_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly details: AdsBlockedDetails
}
export interface Web_bindSelectionMenu_event extends PeerEvent {
    readonly kind: PeerEventKind
}
export interface XComponent_onLoad_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly event?: Object | undefined
}
export interface XComponent_onDestroy_event extends PeerEvent {
    readonly kind: PeerEventKind
}
export interface SideBarContainer_onChange_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: boolean
}
export interface SideBarContainer__onChangeEvent_showSideBar_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: boolean
}
export interface WaterFlow_onReachStart_event extends PeerEvent {
    readonly kind: PeerEventKind
}
export interface WaterFlow_onReachEnd_event extends PeerEvent {
    readonly kind: PeerEventKind
}
export interface WaterFlow_onScrollFrameBegin_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly offset: number
    readonly state: ScrollState
}
export interface WaterFlow_onScrollIndex_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly first: number
    readonly last: number
}
export interface UIExtensionComponent_onRemoteReady_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: UIExtensionProxy
}
export interface UIExtensionComponent_onResult_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly parameter: Literal_Number_code_Want_want
}
export interface UIExtensionComponent_onRelease_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly index: number
}
export interface UIExtensionComponent_onError_event extends PeerEvent {
    readonly kind: PeerEventKind
    readonly err: BusinessError
}
export interface UIExtensionComponent_onTerminated_event extends PeerEvent {
    readonly kind: PeerEventKind
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
export class PeerEventsProperties {
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
    CommonMethod_onHover?: ((isHover: boolean,event: HoverEvent) => void)
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
    CommonMethod_onAreaChange?: ((oldValue: Area,newValue: Area) => void)
    CommonMethod_onDragStart?: ((event: DragEvent,extraParams?: string) => CustomBuilder | DragItemInfo)
    CommonMethod_onDragEnter?: ((event: DragEvent,extraParams?: string) => void)
    CommonMethod_onDragMove?: ((event: DragEvent,extraParams?: string) => void)
    CommonMethod_onDragLeave?: ((event: DragEvent,extraParams?: string) => void)
    CommonMethod_onDrop?: ((event: DragEvent,extraParams?: string) => void)
    CommonMethod_onDragEnd?: ((event: DragEvent,extraParams?: string) => void)
    CommonMethod_onPreDrag?: ((parameter: PreDragStatus) => void)
    CommonMethod_accessibilityVirtualNode?: CustomBuilder
    CommonMethod_onGestureJudgeBegin?: ((gestureInfo: GestureInfo,event: BaseGestureEvent) => GestureJudgeResult)
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
    ScrollableCommonMethod_onScroll?: ((first: number,last: number) => void)
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
    FormComponent_onError?: ((info: Literal_Number_errcode_String_msg) => void)
    FormComponent_onRouter?: ((info: object) => void)
    FormComponent_onUninstall?: ((parameter: FormCallbackInfo) => void)
    FormComponent_onLoad?: (() => void)
    Gauge_description?: CustomBuilder
    Grid_onScrollBarUpdate?: ((index: number,offset: number) => ComputedBarAttribute)
    Grid_onScrollIndex?: ((first: number,last: number) => void)
    Grid_onItemDragStart?: ((event: ItemDragInfo,itemIndex: number) => CustomBuilder)
    Grid_onItemDragEnter?: ((event: ItemDragInfo) => void)
    Grid_onItemDragMove?: ((event: ItemDragInfo,itemIndex: number,insertIndex: number) => void)
    Grid_onItemDragLeave?: ((event: ItemDragInfo,itemIndex: number) => void)
    Grid_onItemDrop?: ((event: ItemDragInfo,itemIndex: number,insertIndex: number,isSuccess: boolean) => void)
    Grid_onScroll?: ((first: number,last: number) => void)
    Grid_onReachStart?: (() => void)
    Grid_onReachEnd?: (() => void)
    Grid_onScrollStart?: (() => void)
    Grid_onScrollStop?: (() => void)
    Grid_onScrollFrameBegin?: ((offset: number,state: ScrollState) => Literal_Number_offsetRemain)
    GridItem_onSelect?: ((parameter: boolean) => void)
    GridItem__onChangeEvent_selected?: ((parameter: boolean) => void)
    GridRow_onBreakpointChange?: ((breakpoints: string) => void)
    Image_onComplete?: ((event?: Type_ImageAttribute_onComplete_callback_event) => void)
    Image_onError?: ImageErrorCallback
    Image_onFinish?: (() => void)
    ImageAnimator_onStart?: (() => void)
    ImageAnimator_onPause?: (() => void)
    ImageAnimator_onRepeat?: (() => void)
    ImageAnimator_onCancel?: (() => void)
    ImageAnimator_onFinish?: (() => void)
    ImageSpan_onComplete?: ImageCompleteCallback
    ImageSpan_onError?: ImageErrorCallback
    List_onScroll?: ((first: number,last: number) => void)
    List_onScrollIndex?: ((start: number,end: number,center: number) => void)
    List_onScrollVisibleContentChange?: OnScrollVisibleContentChangeCallback
    List_onReachStart?: (() => void)
    List_onReachEnd?: (() => void)
    List_onScrollStart?: (() => void)
    List_onScrollStop?: (() => void)
    List_onItemDelete?: ((index: number) => boolean)
    List_onItemMove?: ((from: number,to: number) => boolean)
    List_onItemDragStart?: ((event: ItemDragInfo,itemIndex: number) => CustomBuilder)
    List_onItemDragEnter?: ((event: ItemDragInfo) => void)
    List_onItemDragMove?: ((event: ItemDragInfo,itemIndex: number,insertIndex: number) => void)
    List_onItemDragLeave?: ((event: ItemDragInfo,itemIndex: number) => void)
    List_onItemDrop?: ((event: ItemDragInfo,itemIndex: number,insertIndex: number,isSuccess: boolean) => void)
    List_onScrollFrameBegin?: ((offset: number,state: ScrollState) => Literal_Number_offsetRemain)
    ListItem_onSelect?: ((parameter: boolean) => void)
    ListItem__onChangeEvent_selected?: ((parameter: boolean) => void)
    LocationButton_onClick?: ((event: ClickEvent,result: LocationButtonOnClickResult) => void)
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
    Panel_onChange?: ((width: number,height: number,mode: PanelMode) => void)
    Panel_onHeightChange?: ((index: number) => void)
    Panel__onChangeEvent_mode?: ((mode: PanelMode) => void)
    PasteButton_onClick?: ((event: ClickEvent,result: PasteButtonOnClickResult) => void)
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
    SaveButton_onClick?: ((event: ClickEvent,result: SaveButtonOnClickResult) => void)
    Scroll_onScroll?: ((first: number,last: number) => void)
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
    Select_onSelect?: ((index: number,value: string) => void)
    Select__onChangeEvent_selected?: ((selected: number | Resource) => void)
    Select__onChangeEvent_value?: ((value: ResourceStr) => void)
    Slider_onChange?: ((value: number,mode: SliderChangeMode) => void)
    Slider__onChangeEvent_value?: ((index: number) => void)
    Stepper_onFinish?: (() => void)
    Stepper_onSkip?: (() => void)
    Stepper_onChange?: ((first: number,last: number) => void)
    Stepper_onNext?: ((first: number,last: number) => void)
    Stepper_onPrevious?: ((first: number,last: number) => void)
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
    Text_onTextSelectionChange?: ((first: number,last: number) => void)
    Text_bindSelectionMenu?: CustomBuilder
    TextArea_onSubmit0?: ((enterKey: EnterKeyType) => void)
    TextArea_onSubmit1?: TextAreaSubmitCallback
    TextArea_onChange?: EditableTextOnChangeCallback
    TextArea_onTextSelectionChange?: ((first: number,last: number) => void)
    TextArea_onContentScroll?: ((first: number,last: number) => void)
    TextArea_onEditChange?: ((parameter: boolean) => void)
    TextArea_onCopy?: ((breakpoints: string) => void)
    TextArea_onCut?: ((breakpoints: string) => void)
    TextArea_onPaste?: ((value: string,event: PasteEvent) => void)
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
    TextPicker_onAccept?: ((value: string,index: number) => void)
    TextPicker_onCancel?: (() => void)
    TextPicker_onChange?: ((value: string | Array<string>,index: number | Array<number>) => void)
    TextPicker__onChangeEvent_selected?: ((selected: number | Array<number>) => void)
    TextPicker__onChangeEvent_value?: ((value: string | Array<string>) => void)
    TextTimer_onTimer?: ((first: number,last: number) => void)
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
    Web_onUrlLoadIntercept?: ((event?: Literal_Union_String_WebResourceRequest_data) => boolean)
    Web_onSslErrorReceive?: ((event?: Literal_Function_handler_Object_error) => void)
    Web_onRenderExited0?: ((parameter: OnRenderExitedEvent) => void)
    Web_onRenderExited1?: ((event?: Literal_Object_detail) => boolean)
    Web_onShowFileSelector?: ((parameter: OnShowFileSelectorEvent) => boolean)
    Web_onFileSelectorShow?: ((event?: Literal_Function_callback__Object_fileSelector) => void)
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
    WaterFlow_onScrollFrameBegin?: ((offset: number,state: ScrollState) => Literal_Number_offsetRemain)
    WaterFlow_onScrollIndex?: ((first: number,last: number) => void)
    UIExtensionComponent_onRemoteReady?: ((parameter: UIExtensionProxy) => void)
    UIExtensionComponent_onResult?: ((parameter: Literal_Number_code_Want_want) => void)
    UIExtensionComponent_onRelease?: ((index: number) => void)
    UIExtensionComponent_onError?: ErrorCallback
    UIExtensionComponent_onTerminated?: ((parameter: TerminationInfo) => void)
}