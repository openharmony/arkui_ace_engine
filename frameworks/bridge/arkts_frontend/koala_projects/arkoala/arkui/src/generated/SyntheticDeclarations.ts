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
import { PixelMap } from "./ArkPixelMapMaterialized"
import { Want, LengthUnit, WebHeader } from "./ArkArkuiExternalInterfaces"
import { DismissDialogAction } from "./ArkActionSheetInterfaces"
import { DismissReason, TransitionEffects, TranslateOptions, RotateOptions, ScaleOptions, TransitionEdge, AnimateParam, FinishCallbackType, ExpectedFrameRateRange, DismissContentCoverAction, SheetSize, SheetDismiss, DismissSheetAction, SpringBackAction, SheetType, DismissPopupAction, TouchTestInfo, TouchResult, RectResult, TouchTestStrategy, EventTarget, SourceType, SourceTool, TouchObject, HistoricalPoint, IntentionCode, CustomBuilder, DragItemInfo, DragBehavior, Summary, DragResult, Rectangle, PreDragStatus, ItemDragInfo, ShadowOptions, ShadowType, DrawContext } from "./ArkCommonInterfaces"
import { MonthData, CalendarDay, CalendarSelectedDate, CalendarRequestedData } from "./ArkCalendarInterfaces"
import { CalendarController } from "./ArkCalendarControllerMaterialized"
import { HorizontalAlign, VerticalAlign, Curve, PlayMode, MouseButton, MouseAction, TouchType, KeyType, KeySource, GradientDirection, HitTestMode, Alignment, FontStyle, FontWeight, TextAlign, WordBreak, LineBreakStrategy, ImageSpanAlignment, ImageFit, TextDecorationType, TextDecorationStyle, Color, ColoringStrategy, Axis } from "./ArkEnumsInterfaces"
import { TransitionEffect } from "./ArkTransitionEffectMaterialized"
import { ICurve } from "./ArkICurveMaterialized"
import { Length, ResourceColor, Area, Position, Dimension, ResourceStr, Margin, BorderRadiuses, SizeOptions, Padding } from "./ArkUnitsInterfaces"
import { ClickEvent } from "./ArkClickEventMaterialized"
import { BaseEvent } from "./ArkBaseEventMaterialized"
import { HoverEvent } from "./ArkHoverEventMaterialized"
import { MouseEvent } from "./ArkMouseEventMaterialized"
import { TouchEvent } from "./ArkTouchEventMaterialized"
import { KeyEvent } from "./ArkKeyEventMaterialized"
import { DragEvent } from "./ArkDragEventMaterialized"
import { UnifiedData } from "./ArkUnifiedDataMaterialized"
import { GestureInfo, GestureJudgeResult, FingerInfo, PanDirection, SwipeDirection } from "./ArkGestureInterfaces"
import { BaseGestureEvent } from "./ArkBaseGestureEventMaterialized"
import { GestureControl } from "./ArkGestureControlNamespace"
import { DatePickerResult } from "./ArkDatePickerInterfaces"
import { TerminationInfo } from "./ArkEmbeddedComponentInterfaces"
import { FormCallbackInfo } from "./ArkFormComponentInterfaces"
import { LinearGradient } from "./ArkLinearGradientMaterialized"
import { ColorStop } from "./ArkDataPanelInterfaces"
import { GestureEvent } from "./ArkGestureEventMaterialized"
import { ComputedBarAttribute } from "./ArkGridInterfaces"
import { ScrollState } from "./ArkListInterfaces"
import { SwipeActionState } from "./ArkListItemInterfaces"
import { LocationButtonOnClickResult } from "./ArkLocationButtonInterfaces"
import { NavDestinationContext } from "./ArkNavDestinationContextMaterialized"
import { NavPathInfo } from "./ArkNavPathInfoMaterialized"
import { NavPathStack } from "./ArkNavPathStackMaterialized"
import { RouteMapConfig, NavDestinationMode } from "./ArkNavDestinationInterfaces"
import { NavigationOptions, NavigationInterception, PopInfo, LaunchMode, InterceptionShowCallback, InterceptionModeCallback, NavigationTitleMode, NavigationMode, NavContentInfo, NavigationOperation, NavigationAnimatedTransition } from "./ArkNavigationInterfaces"
import { NavigationTransitionProxy } from "./ArkNavigationTransitionProxyMaterialized"
import { NavigationType } from "./ArkNavigatorInterfaces"
import { PanelMode } from "./ArkPanelInterfaces"
import { PasteButtonOnClickResult } from "./ArkPasteButtonInterfaces"
import { RefreshStatus } from "./ArkRefreshInterfaces"
import { RichEditorSelection, RichEditorTextSpanResult, RichEditorImageSpanResult, RichEditorSpanPosition, RichEditorTextStyleResult, RichEditorSymbolSpanStyle, RichEditorParagraphStyle, RichEditorImageSpanStyleResult, LeadingMarginPlaceholder, RichEditorLayoutStyle, RichEditorRange, RichEditorInsertValue, RichEditorDeleteValue, RichEditorDeleteDirection, RichEditorChangeValue, CutEvent, CopyEvent, PasteEvent } from "./ArkRichEditorInterfaces"
import { Resource } from "./ArkResourceInterfaces"
import { DecorationStyleResult, TextRange, InsertValue, DeleteValue, TextDeleteDirection, StyledStringChangeValue } from "./ArkTextCommonInterfaces"
import { SymbolEffectStrategy, SymbolRenderingStrategy } from "./ArkSymbolglyphInterfaces"
import { SaveButtonOnClickResult } from "./ArkSaveButtonInterfaces"
import { SliderChangeMode } from "./ArkSliderInterfaces"
import { SwiperContentTransitionProxy } from "./ArkSwiperContentTransitionProxyMaterialized"
import { TabContentTransitionProxy } from "./ArkTabContentTransitionProxyMaterialized"
import { EnterKeyType } from "./ArkTextInputInterfaces"
import { StyledString } from "./ArkStyledStringMaterialized"
import { ImageAttachment } from "./ArkImageAttachmentMaterialized"
import { CustomSpan } from "./ArkCustomSpanMaterialized"
import { StyleOptions, StyledStringKey, SpanStyle, ImageAttachmentLayoutStyle, ImageAttachmentInterface, CustomSpanMeasureInfo, CustomSpanMetrics, CustomSpanDrawInfo, StyledStringValue } from "./ArkStyledStringInterfaces"
import { LengthMetrics } from "./ArkLengthMetricsMaterialized"
import { TextPickerResult } from "./ArkTextPickerInterfaces"
import { TimePickerResult } from "./ArkTimePickerInterfaces"
import { FullscreenInfo, PreparedInfo, PlaybackInfo } from "./ArkVideoInterfaces"
import { Header, OnPageEndEvent, OnPageBeginEvent, OnProgressChangeEvent, OnTitleReceiveEvent, OnGeolocationShowEvent, OnAlertEvent, OnBeforeUnloadEvent, OnConfirmEvent, OnPromptEvent, OnConsoleEvent, MessageLevel, OnErrorReceiveEvent, OnHttpErrorReceiveEvent, OnDownloadStartEvent, OnRefreshAccessedHistoryEvent, OnRenderExitedEvent, RenderExitReason, OnShowFileSelectorEvent, FileSelectorMode, OnResourceLoadEvent, OnScaleChangeEvent, OnHttpAuthRequestEvent, OnInterceptRequestEvent, OnPermissionRequestEvent, OnScreenCaptureRequestEvent, ScreenCaptureConfig, WebCaptureMode, OnContextMenuShowEvent, ContextMenuMediaType, ContextMenuSourceType, ContextMenuInputFieldType, OnSearchResultReceiveEvent, OnScrollEvent, OnSslErrorEventReceiveEvent, SslError, OnClientAuthenticationEvent, OnWindowNewEvent, OnTouchIconUrlReceivedEvent, OnFaviconReceivedEvent, OnPageVisibleEvent, OnDataResubmittedEvent, OnAudioStateChangedEvent, OnFirstContentfulPaintEvent, OnLoadInterceptEvent, OnOverScrollEvent, NativeEmbedDataInfo, NativeEmbedStatus, NativeEmbedInfo, NativeEmbedTouchInfo } from "./ArkWebInterfaces"
import { JsGeolocation } from "./ArkJsGeolocationMaterialized"
import { JsResult } from "./ArkJsResultMaterialized"
import { ConsoleMessage } from "./ArkConsoleMessageMaterialized"
import { WebResourceRequest } from "./ArkWebResourceRequestMaterialized"
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
import { WebviewController } from "./ArkWebviewControllerMaterialized"
import { DataResubmissionHandler } from "./ArkDataResubmissionHandlerMaterialized"
import { EventResult } from "./ArkEventResultMaterialized"
import { XComponentController } from "./ArkXComponentControllerMaterialized"
import { SurfaceRect, SurfaceRotationOptions } from "./ArkXcomponentInterfaces"
import { ImageAnalyzerConfig, ImageAnalyzerType } from "./ArkImageCommonInterfaces"
import { UIExtensionProxy } from "./ArkUIExtensionProxyMaterialized"
export type AsyncCallback_image_PixelMap_Void = (result: PixelMap) => void;
export interface Literal_Want_want {
    want: Want;
}
export type Callback_Void = () => void;
export type Callback_DismissDialogAction_Void = (parameter: DismissDialogAction) => void;
export type Callback_Number_Void = (index: number) => void;
export interface Literal_Number_day_month_year {
    year: number;
    month: number;
    day: number;
}
export interface Type_CalendarInterface_value {
    date: { year: number, month: number, day: number };
    currentData: MonthData;
    preData: MonthData;
    nextData: MonthData;
    controller?: CalendarController;
}
export type Callback_CalendarSelectedDate_Void = (event: CalendarSelectedDate) => void;
export type Callback_CalendarRequestedData_Void = (event: CalendarRequestedData) => void;
export type Callback_Date_Void = (parameter: Date) => void;
export type Callback_Boolean_Void = (parameter: boolean) => void;
export interface Literal_String_anchor_HorizontalAlign_align {
    anchor: string;
    align: HorizontalAlign;
}
export interface Literal_String_anchor_VerticalAlign_align {
    anchor: string;
    align: VerticalAlign;
}
export interface Literal_TransitionEffect_appear_disappear {
    appear: TransitionEffect;
    disappear: TransitionEffect;
}
export type Tuple_Number_Number = [
    number,
    number
]
export type Callback_DismissContentCoverAction_Void = (parameter: DismissContentCoverAction) => void;
export type Type_SheetOptions_detents = [
    SheetSize | Length,
    SheetSize | Length | undefined,
    SheetSize | Length | undefined
]
export type Callback_SheetDismiss_Void = (sheetDismiss: SheetDismiss) => void;
export type Callback_DismissSheetAction_Void = (parameter: DismissSheetAction) => void;
export type Callback_SpringBackAction_Void = (parameter: SpringBackAction) => void;
export type Callback_SheetType_Void = (parameter: SheetType) => void;
export interface Literal_String_value_Callback_Void_action {
    value: string;
    action: (() => void);
}
export interface Literal_Boolean_isVisible {
    isVisible: boolean;
}
export type Callback_Literal_Boolean_isVisible_Void = (event: { isVisible: boolean }) => void;
export interface Literal_ResourceColor_color {
    color: ResourceColor;
}
export type Callback_DismissPopupAction_Void = (parameter: DismissPopupAction) => void;
export type AnimationRange_Number = [
    number,
    number
]
export type Callback_Array_TouchTestInfo_TouchResult = (value: Array<TouchTestInfo>) => TouchResult;
export type Callback_ClickEvent_Void = (event: ClickEvent) => void;
export type Callback_Boolean_HoverEvent_Void = (isHover: boolean, event: HoverEvent) => void;
export type Callback_MouseEvent_Void = (event: MouseEvent) => void;
export type Callback_TouchEvent_Void = (event: TouchEvent) => void;
export type Callback_KeyEvent_Void = (event: KeyEvent) => void;
export type Callback_KeyEvent_Boolean = (parameter: KeyEvent) => boolean;
export type Callback_Area_Area_Void = (oldValue: Area, newValue: Area) => void;
export interface Literal_Number_offset_span {
    span: number;
    offset: number;
}
export interface Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs {
    xs?: number | { span: number, offset: number };
    sm?: number | { span: number, offset: number };
    md?: number | { span: number, offset: number };
    lg?: number | { span: number, offset: number };
}
export type Callback_DragEvent_String_Union_CustomBuilder_DragItemInfo = (event: DragEvent, extraParams?: string) => CustomBuilder | DragItemInfo;
export type Callback_DragEvent_String_Void = (event: DragEvent, extraParams?: string) => void;
export type Callback_PreDragStatus_Void = (parameter: PreDragStatus) => void;
export type Tuple_ResourceColor_Number = [
    ResourceColor,
    number
]
export interface Type_CommonMethod_linearGradient_value {
    angle?: number | string;
    direction?: GradientDirection;
    colors: Array<[ ResourceColor, number ]>;
    repeating?: boolean;
}
export type Tuple_Length_Length = [
    Length,
    Length
]
export interface Type_CommonMethod_sweepGradient_value {
    center: [ Length, Length ];
    start?: number | string;
    end?: number | string;
    rotation?: number | string;
    colors: Array<[ ResourceColor, number ]>;
    repeating?: boolean;
}
export interface Type_CommonMethod_radialGradient_value {
    center: [ Length, Length ];
    radius: number | string;
    colors: Array<[ ResourceColor, number ]>;
    repeating?: boolean;
}
export type Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult = (gestureInfo: GestureInfo, event: BaseGestureEvent) => GestureJudgeResult;
export type Callback_TouchEvent_HitTestMode = (parameter: TouchEvent) => HitTestMode;
export interface Literal_Alignment_align {
    align?: Alignment;
}
export interface Literal_Empty {
}
export interface Literal_String_key_Any_defaultValue {
    key: string;
    defaultValue: any;
}
export type Callback_DatePickerResult_Void = (value: DatePickerResult) => void;
export type Callback_TerminationInfo_Void = (parameter: TerminationInfo) => void;
export type Callback_FormCallbackInfo_Void = (parameter: FormCallbackInfo) => void;
export interface Literal_Number_errcode_String_msg {
    errcode: number;
    msg: string;
}
export type Callback_Literal_Number_errcode_String_msg_Void = (info: { errcode: number, msg: string }) => void;
export type Callback_Any_Void = (info: any) => void;
export type Tuple_Union_ResourceColor_LinearGradient_Number = [
    ResourceColor | LinearGradient,
    number
]
export type Callback_GestureEvent_Void = (event: GestureEvent) => void;
export interface Literal_Number_duration_fingers_Boolean_repeat {
    fingers?: number;
    repeat?: boolean;
    duration?: number;
}
export interface Literal_Number_distance_fingers_PanDirection_direction {
    fingers?: number;
    direction?: PanDirection;
    distance?: number;
}
export interface Literal_Number_fingers_speed_SwipeDirection_direction {
    fingers?: number;
    direction?: SwipeDirection;
    speed?: number;
}
export interface Literal_Number_distance_fingers {
    fingers?: number;
    distance?: number;
}
export interface Literal_Number_angle_fingers {
    fingers?: number;
    angle?: number;
}
export type Callback_Number_Tuple_Number_Number = (index: number) => [ number, number ];
export type Tuple_Number_Number_Number_Number = [
    number,
    number,
    number,
    number
]
export type Callback_Number_Tuple_Number_Number_Number_Number = (index: number) => [ number, number, number, number ];
export type Callback_Number_Number_ComputedBarAttribute = (index: number, offset: number) => ComputedBarAttribute;
export type Callback_Number_Number_Void = (first: number, last: number) => void;
export type onItemDragStart_event_type = (event: ItemDragInfo, itemIndex: number) => CustomBuilder;
export type Callback_ItemDragInfo_Void = (event: ItemDragInfo) => void;
export type Callback_ItemDragInfo_Number_Number_Void = (event: ItemDragInfo, itemIndex: number, insertIndex: number) => void;
export type Callback_ItemDragInfo_Number_Void = (event: ItemDragInfo, itemIndex: number) => void;
export type Callback_ItemDragInfo_Number_Number_Boolean_Void = (event: ItemDragInfo, itemIndex: number, insertIndex: number, isSuccess: boolean) => void;
export interface Literal_Number_offsetRemain {
    offsetRemain: number;
}
export type Callback_Number_ScrollState_Literal_Number_offsetRemain = (offset: number, state: ScrollState) => { offsetRemain: number };
export type Callback_String_Void = (breakpoints: string) => void;
export interface Type_ImageAttribute_onComplete_callback_event {
    width: number;
    height: number;
    componentWidth: number;
    componentHeight: number;
    loadingStatus: number;
    contentWidth: number;
    contentHeight: number;
    contentOffsetX: number;
    contentOffsetY: number;
}
export type Callback_Type_ImageAttribute_onComplete_callback_event_Void = (event?: { width: number, height: number, componentWidth: number, componentHeight: number, loadingStatus: number, contentWidth: number, contentHeight: number, contentOffsetX: number, contentOffsetY: number }) => void;
export type Callback_Number_Number_Number_Void = (start: number, end: number, center: number) => void;
export type Callback_Number_Boolean = (index: number) => boolean;
export type Callback_Number_Number_Boolean = (from: number, to: number) => boolean;
export type Callback_SwipeActionState_Void = (state: SwipeActionState) => void;
export type Callback_ClickEvent_LocationButtonOnClickResult_Void = (event: ClickEvent, result: LocationButtonOnClickResult) => void;
export type Callback_Boolean = () => boolean;
export type Callback_NavDestinationContext_Void = (parameter: NavDestinationContext) => void;
export type Callback_PopInfo_Void = (parameter: PopInfo) => void;
export type Tuple_Dimension_Dimension = [
    Dimension,
    Dimension
]
export type Callback_NavigationTitleMode_Void = (titleMode: NavigationTitleMode) => void;
export type Callback_NavigationMode_Void = (mode: NavigationMode) => void;
export type Callback_String_Unknown_Void = (name: string, param: unknown) => void;
export type Type_NavigationAttribute_customNavContentTransition_delegate = (from: NavContentInfo, to: NavContentInfo, operation: NavigationOperation) => NavigationAnimatedTransition | undefined;
export type Callback_NavigationTransitionProxy_Void = (transitionProxy: NavigationTransitionProxy) => void;
export interface Literal_String_target_NavigationType_type {
    target: string;
    type?: NavigationType;
}
export type Callback_Number_Number_PanelMode_Void = (width: number, height: number, mode: PanelMode) => void;
export type Callback_PanelMode_Void = (mode: PanelMode) => void;
export type Callback_ClickEvent_PasteButtonOnClickResult_Void = (event: ClickEvent, result: PasteButtonOnClickResult) => void;
export type Callback_Array_Number_Void = (input: Array<number>) => void;
export type Callback_RefreshStatus_Void = (state: RefreshStatus) => void;
export type Callback_RichEditorSelection_Void = (parameter: RichEditorSelection) => void;
export type Callback_RichEditorRange_Void = (parameter: RichEditorRange) => void;
export type Callback_RichEditorInsertValue_Boolean = (parameter: RichEditorInsertValue) => boolean;
export type Callback_RichEditorTextSpanResult_Void = (parameter: RichEditorTextSpanResult) => void;
export type Callback_TextRange_Void = (parameter: TextRange) => void;
export type Callback_RichEditorDeleteValue_Boolean = (parameter: RichEditorDeleteValue) => boolean;
export type Callback_RichEditorChangeValue_Boolean = (parameter: RichEditorChangeValue) => boolean;
export type Callback_CutEvent_Void = (parameter: CutEvent) => void;
export type Callback_CopyEvent_Void = (parameter: CopyEvent) => void;
export type Callback_ClickEvent_SaveButtonOnClickResult_Void = (event: ClickEvent, result: SaveButtonOnClickResult) => void;
export interface Literal_Boolean_next_Axis_direction {
    next: boolean;
    direction?: Axis;
}
export type Callback_InsertValue_Boolean = (parameter: InsertValue) => boolean;
export type Callback_InsertValue_Void = (parameter: InsertValue) => void;
export type Callback_DeleteValue_Boolean = (parameter: DeleteValue) => boolean;
export type Callback_DeleteValue_Void = (parameter: DeleteValue) => void;
export type Callback_Number_String_Void = (index: number, value: string) => void;
export type Callback_Union_Number_Resource_Void = (selected: number | Resource) => void;
export type Callback_ResourceStr_Void = (value: ResourceStr) => void;
export type Callback_Number_SliderChangeMode_Void = (value: number, mode: SliderChangeMode) => void;
export interface Literal_Number_index {
    index?: number;
}
export type Callback_SwiperContentTransitionProxy_Void = (parameter: SwiperContentTransitionProxy) => void;
export type Callback_TabContentTransitionProxy_Void = (parameter: TabContentTransitionProxy) => void;
export type Callback_EnterKeyType_Void = (enterKey: EnterKeyType) => void;
export type Callback_String_PasteEvent_Void = (value: string, event: PasteEvent) => void;
export type Callback_StyledStringChangeValue_Boolean = (parameter: StyledStringChangeValue) => boolean;
export type Callback_String_Number_Void = (value: string, index: number) => void;
export type Type_TextPickerAttribute_onChange_callback = (value: string | Array<string>, index: number | Array<number>) => void;
export type Callback_Union_Number_Array_Number_Void = (selected: number | Array<number>) => void;
export type Callback_Union_String_Array_String_Void = (value: string | Array<string>) => void;
export type Callback_TextPickerResult_Void = (value: TextPickerResult) => void;
export type Callback_TimePickerResult_Void = (value: TimePickerResult) => void;
export type Callback_FullscreenInfo_Void = (parameter: FullscreenInfo) => void;
export type Callback_PreparedInfo_Void = (parameter: PreparedInfo) => void;
export type Callback_PlaybackInfo_Void = (parameter: PlaybackInfo) => void;
export interface Literal_String_script_Callback_String_Void_callback_ {
    script: string;
    callback_?: ((breakpoints: string) => void);
}
export interface Literal_String_baseUrl_data_encoding_historyUrl_mimeType {
    data: string;
    mimeType: string;
    encoding: string;
    baseUrl?: string;
    historyUrl?: string;
}
export interface Literal_Union_String_Resource_url_Array_Header_headers {
    url: string | Resource;
    headers?: Array<Header>;
}
export interface Literal_Object_object__String_name_Array_String_methodList {
    object_: Object;
    name: string;
    methodList: Array<string>;
}
export type Callback_OnPageEndEvent_Void = (parameter: OnPageEndEvent) => void;
export type Callback_OnPageBeginEvent_Void = (parameter: OnPageBeginEvent) => void;
export type Callback_OnProgressChangeEvent_Void = (parameter: OnProgressChangeEvent) => void;
export type Callback_OnTitleReceiveEvent_Void = (parameter: OnTitleReceiveEvent) => void;
export type Callback_OnGeolocationShowEvent_Void = (parameter: OnGeolocationShowEvent) => void;
export type Callback_OnAlertEvent_Boolean = (parameter: OnAlertEvent) => boolean;
export type Callback_OnBeforeUnloadEvent_Boolean = (parameter: OnBeforeUnloadEvent) => boolean;
export type Callback_OnConfirmEvent_Boolean = (parameter: OnConfirmEvent) => boolean;
export type Callback_OnPromptEvent_Boolean = (parameter: OnPromptEvent) => boolean;
export type Callback_OnConsoleEvent_Boolean = (parameter: OnConsoleEvent) => boolean;
export type Callback_OnErrorReceiveEvent_Void = (parameter: OnErrorReceiveEvent) => void;
export type Callback_OnHttpErrorReceiveEvent_Void = (parameter: OnHttpErrorReceiveEvent) => void;
export type Callback_OnDownloadStartEvent_Void = (parameter: OnDownloadStartEvent) => void;
export type Callback_OnRefreshAccessedHistoryEvent_Void = (parameter: OnRefreshAccessedHistoryEvent) => void;
export interface Literal_Union_String_WebResourceRequest_data {
    data: string | WebResourceRequest;
}
export type Type_WebAttribute_onUrlLoadIntercept_callback = (event?: { data: string | WebResourceRequest }) => boolean;
export interface Literal_Function_handler_Object_error {
    handler: Function;
    error: Object;
}
export type Callback_Literal_Function_handler_Object_error_Void = (event?: { handler: Function, error: Object }) => void;
export type Callback_OnRenderExitedEvent_Void = (parameter: OnRenderExitedEvent) => void;
export type Callback_OnShowFileSelectorEvent_Boolean = (parameter: OnShowFileSelectorEvent) => boolean;
export interface Literal_Object_detail {
    detail: Object;
}
export type Callback_Literal_Object_detail_Boolean = (event?: { detail: Object }) => boolean;
export interface Literal_Function_callback__Object_fileSelector {
    callback_: Function;
    fileSelector: Object;
}
export type Type_WebAttribute_onFileSelectorShow_callback = (event?: { callback_: Function, fileSelector: Object }) => void;
export type Callback_OnResourceLoadEvent_Void = (parameter: OnResourceLoadEvent) => void;
export type Callback_OnScaleChangeEvent_Void = (parameter: OnScaleChangeEvent) => void;
export type Callback_OnHttpAuthRequestEvent_Boolean = (parameter: OnHttpAuthRequestEvent) => boolean;
export type Callback_OnInterceptRequestEvent_WebResourceResponse = (parameter: OnInterceptRequestEvent) => WebResourceResponse;
export type Callback_OnPermissionRequestEvent_Void = (parameter: OnPermissionRequestEvent) => void;
export type Callback_OnScreenCaptureRequestEvent_Void = (parameter: OnScreenCaptureRequestEvent) => void;
export type Callback_OnContextMenuShowEvent_Boolean = (parameter: OnContextMenuShowEvent) => boolean;
export type Callback_OnSearchResultReceiveEvent_Void = (parameter: OnSearchResultReceiveEvent) => void;
export type Callback_OnScrollEvent_Void = (parameter: OnScrollEvent) => void;
export type Callback_OnSslErrorEventReceiveEvent_Void = (parameter: OnSslErrorEventReceiveEvent) => void;
export type Callback_OnClientAuthenticationEvent_Void = (parameter: OnClientAuthenticationEvent) => void;
export type Callback_OnWindowNewEvent_Void = (parameter: OnWindowNewEvent) => void;
export type Callback_OnTouchIconUrlReceivedEvent_Void = (parameter: OnTouchIconUrlReceivedEvent) => void;
export type Callback_OnFaviconReceivedEvent_Void = (parameter: OnFaviconReceivedEvent) => void;
export type Callback_OnPageVisibleEvent_Void = (parameter: OnPageVisibleEvent) => void;
export type Callback_OnDataResubmittedEvent_Void = (parameter: OnDataResubmittedEvent) => void;
export type Callback_OnAudioStateChangedEvent_Void = (parameter: OnAudioStateChangedEvent) => void;
export type Callback_OnFirstContentfulPaintEvent_Void = (parameter: OnFirstContentfulPaintEvent) => void;
export type Callback_OnLoadInterceptEvent_Boolean = (parameter: OnLoadInterceptEvent) => boolean;
export type Callback_OnOverScrollEvent_Void = (parameter: OnOverScrollEvent) => void;
export type Callback_NativeEmbedDataInfo_Void = (event: NativeEmbedDataInfo) => void;
export type Callback_NativeEmbedTouchInfo_Void = (event: NativeEmbedTouchInfo) => void;
export interface Literal_String_plainText {
    plainText: string;
}
export type Callback_Literal_String_plainText_Void = (selectedText: { plainText: string }) => void;
export interface Literal_Number_surfaceHeight_surfaceWidth {
    surfaceWidth: number;
    surfaceHeight: number;
}
export interface Type_XComponentInterface_value {
    id: string;
    type: string;
    libraryname?: string;
    controller?: XComponentController;
}
export type Callback_UIExtensionProxy_Void = (parameter: UIExtensionProxy) => void;
export interface Literal_Number_code_Want_want {
    code: number;
    want?: Want;
}
export type Callback_Literal_Number_code_Want_want_Void = (parameter: { code: number, want?: Want }) => void;
