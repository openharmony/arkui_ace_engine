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

import { CallbackKind } from "./CallbackKind"
import { Deserializer } from "./Deserializer"
import { int32, float32, int64 } from "@koalaui/common"
import { ResourceHolder, KInt, KStringPtr, wrapSystemCallback, KPointer, RuntimeType } from "@koalaui/interop"
import { CallbackTransformer } from "./CallbackTransformer"
import { AccessibilityCallback, EventTarget, SourceType, SourceTool, TouchTestInfo, TouchResult, RectResult, TouchTestStrategy, CustomBuilder, DismissContentCoverAction, DismissReason, DismissPopupAction, DismissSheetAction, DragItemInfo, DragBehavior, Summary, DragResult, Rectangle, CommonMethod, PixelRoundPolicy, BackgroundEffectOptions, ForegroundEffectOptions, VisualEffect, Filter, BorderImageOption, OutlineStyle, AnimateParam, TransitionOptions, MotionBlurOptions, InvertOptions, TranslateOptions, ScaleOptions, RotateOptions, AlignRuleOption, LocalizedAlignRuleOptions, ClickEffect, UniformDataType, MotionPathOptions, ShadowOptions, ShadowStyle, StateStyles, PixelStretchEffectOptions, BackgroundBrightnessOptions, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, SizeChangeCallback, SafeAreaType, SafeAreaEdge, BlurStyle, BackgroundBlurStyleOptions, ForegroundBlurStyleOptions, TransitionFinishCallback, BlurOptions, LinearGradientBlurOptions, EffectType, sharedTransitionOptions, ChainStyle, DragPreviewOptions, DragInteractionOptions, ComponentContent, OverlayOptions, BlendMode, BlendApplyType, Blender, GeometryTransitionOptions, PopupOptions, CustomPopupOptions, MenuElement, MenuOptions, ContextMenuOptions, ModalTransition, ContentCoverOptions, SheetOptions, VisibleAreaChangeCallback, DrawContext, AdaptiveColor, BlurStyleActivePolicy, RepeatMode, LinearGradient_common, FinishCallbackType, ExpectedFrameRateRange, TransitionEffects, TransitionEdge, MotionBlurAnchor, LocalizedHorizontalAlignParam, LocalizedVerticalAlignParam, PreDragStatus, ShadowType, UIGestureEvent, BlurStyleOptions, ThemeColorMode, FractionStop, DragPreviewMode, ImageModifier, OverlayOffset, TransitionHierarchyStrategy, PopupMessageOptions, SymbolGlyphModifier, MenuPreviewMode, ContextMenuAnimationOptions, BindOptions, SheetSize, SheetType, SheetTitleOptions, SheetMode, ScrollSizeMode, UIContext, SheetKeyboardAvoidMode, TouchObject, HistoricalPoint, IntentionCode, SheetDismiss, SpringBackAction, ItemDragInfo, HoverCallback, OnMoveHandler, OnScrollCallback } from "./../ArkCommonInterfaces"
import { AccessibilityHoverEvent } from "./../ArkAccessibilityHoverEventMaterialized"
import { BaseEvent } from "./../ArkBaseEventMaterialized"
import { AccessibilityHoverType, HitTestMode, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Color, Visibility, ItemAlign, Direction, GradientDirection, ObscuredReasons, RenderFit, ImageRepeat, Axis, ResponseType, FunctionKey, ModifierKey, PixelRoundCalcPolicy, Curve, PlayMode, TransitionType, HorizontalAlign, VerticalAlign, ClickEffectLevel, SharedTransitionEffectType, Placement, ArrowPointPosition, MouseButton, MouseAction, TouchType, KeyType, KeySource, FontWeight, FontStyle, ImageSpanAlignment, ImageFit, TextDecorationType, TextDecorationStyle, TextAlign, TextOverflow, WordBreak, LineBreakStrategy, FoldStatus, AppRotation, Edge, ScrollSource } from "./../ArkEnumsInterfaces"
import { Area, Length, Position, SizeOptions, ConstraintSizeOptions, ChainWeightOptions, Padding, LocalizedPadding, Margin, LocalizedMargin, ResourceColor, BorderOptions, EdgeStyles, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, Dimension, EdgeOutlineWidths, OutlineRadiuses, Edges, LocalizedEdges, LocalizedPosition, ResourceStr, AccessibilityOptions, PX, VP, FP, LPX, Percentage, Bias, Font, VoidCallback } from "./../ArkUnitsInterfaces"
import { Resource } from "./../ArkResourceInterfaces"
import { PixelMap } from "./../ArkPixelMapMaterialized"
import { ButtonTriggerClickCallback } from "./../ArkButtonInterfaces"
import { HoverEvent } from "./../ArkHoverEventMaterialized"
import { CalendarRequestedData, CalendarSelectedDate } from "./../ArkCalendarInterfaces"
import { ClickEvent } from "./../ArkClickEventMaterialized"
import { LocationButtonOnClickResult } from "./../ArkLocationButtonInterfaces"
import { PasteButtonOnClickResult } from "./../ArkPasteButtonInterfaces"
import { SaveButtonOnClickResult } from "./../ArkSaveButtonInterfaces"
import { ComputedBarAttribute } from "./../ArkGridInterfaces"
import { CopyEvent, CutEvent, LeadingMarginPlaceholder, RichEditorChangeValue, RichEditorTextSpanResult, RichEditorImageSpanResult, RichEditorSpanPosition, RichEditorTextStyleResult, RichEditorSymbolSpanStyle, RichEditorParagraphStyle, RichEditorImageSpanStyleResult, RichEditorLayoutStyle, RichEditorDeleteValue, RichEditorDeleteDirection, RichEditorInsertValue, RichEditorRange, RichEditorSelection, PasteEvent, MenuOnAppearCallback, PasteEventCallback, SubmitCallback } from "./../ArkRichEditorInterfaces"
import { DatePickerResult } from "./../ArkDatePickerInterfaces"
import { DeleteValue, TextDeleteDirection, InsertValue, TextRange, DecorationStyleResult, StyledStringChangeValue, EditableTextOnChangeCallback, PreviewText, OnDidChangeCallback } from "./../ArkTextCommonInterfaces"
import { DismissDialogAction } from "./../ArkActionSheetInterfaces"
import { DragEvent } from "./../ArkDragEventMaterialized"
import { UnifiedData } from "./../ArkUnifiedDataMaterialized"
import { EnterKeyType, OnContentScrollCallback, OnPasteCallback, OnSubmitCallback, OnTextSelectionChangeCallback } from "./../ArkTextInputInterfaces"
import { Callback_Extender_OnFinish, Callback_Extender_OnProgress } from "./../ArkAnimationExtenderInterfaces"
import { FormCallbackInfo } from "./../ArkFormComponentInterfaces"
import { FullscreenInfo, PlaybackInfo, PreparedInfo } from "./../ArkVideoInterfaces"
import { GestureEvent } from "./../ArkGestureEventMaterialized"
import { FingerInfo, GestureInfo, GestureJudgeResult, GestureRecognizerState, GestureType, GestureMask, GestureInterface, TapGestureParameters, PanDirection, SwipeDirection, GestureMode, GestureHandler, GesturePriority } from "./../ArkGestureInterfaces"
import { BaseGestureEvent } from "./../ArkBaseGestureEventMaterialized"
import { GestureControl } from "./../ArkGestureControlNamespace"
import { GestureRecognizer } from "./../ArkGestureRecognizerMaterialized"
import { EventTargetInfo } from "./../ArkEventTargetInfoMaterialized"
import { IsolatedComponentAttribute, IsolatedComponentInterface, IsolatedOptions, RestrictedWorker } from "./../ArkIsolatedComponentInterfaces"
import { DrawModifier } from "./../ArkDrawModifierMaterialized"
import { LengthMetrics } from "./../ArkLengthMetricsMaterialized"
import { ResizableOptions, DrawingLattice, ImageErrorCallback, ImageError } from "./../ArkImageInterfaces"
import { FocusBoxStyle, FocusPriority } from "./../ArkFocusInterfaces"
import { TransitionEffect } from "./../ArkTransitionEffectMaterialized"
import { CircleShape } from "./../ArkCircleShapeMaterialized"
import { EllipseShape } from "./../ArkEllipseShapeMaterialized"
import { PathShape } from "./../ArkPathShapeMaterialized"
import { RectShape } from "./../ArkRectShapeMaterialized"
import { ProgressMask } from "./../ArkProgressMaskMaterialized"
import { AttributeModifier } from "./../../handwritten"
import { GestureModifier } from "./../ArkGestureModifierMaterialized"
import { TapGestureInterface } from "./../ArkTapGestureInterfaceMaterialized"
import { LongPressGestureInterface } from "./../ArkLongPressGestureInterfaceMaterialized"
import { PanGestureInterface } from "./../ArkPanGestureInterfaceMaterialized"
import { PinchGestureInterface } from "./../ArkPinchGestureInterfaceMaterialized"
import { SwipeGestureInterface } from "./../ArkSwipeGestureInterfaceMaterialized"
import { RotationGestureInterface } from "./../ArkRotationGestureInterfaceMaterialized"
import { GestureGroupInterface } from "./../ArkGestureGroupInterfaceMaterialized"
import { LengthUnit, ShapeSize, PathShapeOptions, RectShapeOptions, RoundRectShapeOptions, ErrorCallback, Want, WebHeader } from "./../ArkArkuiExternalInterfaces"
import { MouseEvent } from "./../ArkMouseEventMaterialized"
import { TouchEvent } from "./../ArkTouchEventMaterialized"
import { KeyEvent } from "./../ArkKeyEventMaterialized"
import { ColorMetrics } from "./../ArkColorMetricsMaterialized"
import { ICurve } from "./../ArkICurveMaterialized"
import { PanGestureOptions } from "./../ArkPanGestureOptionsMaterialized"
import { NativeEmbedDataInfo, NativeEmbedStatus, NativeEmbedInfo, NativeEmbedTouchInfo, OnAlertEvent, OnAudioStateChangedEvent, OnBeforeUnloadEvent, OnClientAuthenticationEvent, OnConfirmEvent, OnConsoleEvent, MessageLevel, OnContextMenuShowEvent, ContextMenuMediaType, ContextMenuSourceType, ContextMenuInputFieldType, OnDataResubmittedEvent, OnDownloadStartEvent, OnErrorReceiveEvent, Header, OnFaviconReceivedEvent, OnFirstContentfulPaintEvent, OnGeolocationShowEvent, OnHttpAuthRequestEvent, OnHttpErrorReceiveEvent, OnInterceptRequestEvent, OnLoadInterceptEvent, OnOverScrollEvent, OnPageBeginEvent, OnPageEndEvent, OnPageVisibleEvent, OnPermissionRequestEvent, OnProgressChangeEvent, OnPromptEvent, OnRefreshAccessedHistoryEvent, OnRenderExitedEvent, RenderExitReason, OnResourceLoadEvent, OnScaleChangeEvent, OnScreenCaptureRequestEvent, ScreenCaptureConfig, WebCaptureMode, OnScrollEvent, OnSearchResultReceiveEvent, OnShowFileSelectorEvent, FileSelectorMode, OnSslErrorEventReceiveEvent, SslError, OnTitleReceiveEvent, OnTouchIconUrlReceivedEvent, OnWindowNewEvent, WebKeyboardOptions, OnAdsBlockedCallback, AdsBlockedDetails, OnContextMenuHideCallback, OnFirstMeaningfulPaintCallback, FirstMeaningfulPaint, OnFullScreenEnterCallback, FullScreenEnterEvent, OnIntelligentTrackingPreventionCallback, IntelligentTrackingPreventionDetails, OnLargestContentfulPaintCallback, LargestContentfulPaint, OnNativeEmbedVisibilityChangeCallback, NativeEmbedVisibilityInfo, OnNavigationEntryCommittedCallback, LoadCommittedDetails, WebNavigationType, OnOverrideUrlLoadingCallback, OnRenderProcessNotRespondingCallback, RenderProcessNotRespondingData, RenderProcessNotRespondingReason, OnRenderProcessRespondingCallback, OnSafeBrowsingCheckResultCallback, ThreatType, OnSslErrorEventCallback, SslErrorEvent, OnViewportFitChangedCallback, ViewportFit, WebKeyboardCallback, WebKeyboardCallbackInfo } from "./../ArkWebInterfaces"
import { EventResult } from "./../ArkEventResultMaterialized"
import { NavDestinationContext } from "./../ArkNavDestinationContextMaterialized"
import { NavPathInfo } from "./../ArkNavPathInfoMaterialized"
import { NavPathStack } from "./../ArkNavPathStackMaterialized"
import { RouteMapConfig, NavDestinationMode } from "./../ArkNavDestinationInterfaces"
import { NavigationOptions, NavigationInterception, PopInfo, LaunchMode, InterceptionShowCallback, InterceptionModeCallback, NavigationMode, NavigationTitleMode, NavContentInfo, NavigationAnimatedTransition, NavBar, NavigationOperation } from "./../ArkNavigationInterfaces"
import { NavigationTransitionProxy } from "./../ArkNavigationTransitionProxyMaterialized"
import { PanelMode } from "./../ArkPanelInterfaces"
import { ScrollState, OnScrollVisibleContentChangeCallback, VisibleListContentInfo, ListItemGroupArea } from "./../ArkListInterfaces"
import { SliderChangeMode, SliderTriggerChangeCallback } from "./../ArkSliderInterfaces"
import { OffsetResult, OnScrollFrameBeginHandlerResult, OnScrollEdgeCallback, OnScrollFrameBeginCallback, ScrollOnScrollCallback, ScrollOnWillScrollCallback } from "./../ArkScrollInterfaces"
import { JsResult } from "./../ArkJsResultMaterialized"
import { ClientAuthenticationHandler } from "./../ArkClientAuthenticationHandlerMaterialized"
import { ConsoleMessage } from "./../ArkConsoleMessageMaterialized"
import { WebContextMenuParam } from "./../ArkWebContextMenuParamMaterialized"
import { WebContextMenuResult } from "./../ArkWebContextMenuResultMaterialized"
import { DataResubmissionHandler } from "./../ArkDataResubmissionHandlerMaterialized"
import { WebResourceRequest } from "./../ArkWebResourceRequestMaterialized"
import { WebResourceError } from "./../ArkWebResourceErrorMaterialized"
import { JsGeolocation } from "./../ArkJsGeolocationMaterialized"
import { HttpAuthHandler } from "./../ArkHttpAuthHandlerMaterialized"
import { WebResourceResponse } from "./../ArkWebResourceResponseMaterialized"
import { PermissionRequest } from "./../ArkPermissionRequestMaterialized"
import { ScreenCaptureHandler } from "./../ArkScreenCaptureHandlerMaterialized"
import { FileSelectorResult } from "./../ArkFileSelectorResultMaterialized"
import { FileSelectorParam } from "./../ArkFileSelectorParamMaterialized"
import { SslErrorHandler } from "./../ArkSslErrorHandlerMaterialized"
import { ControllerHandler } from "./../ArkControllerHandlerMaterialized"
import { WebviewController } from "./../ArkWebviewControllerMaterialized"
import { StyledString } from "./../ArkStyledStringMaterialized"
import { ImageAttachment } from "./../ArkImageAttachmentMaterialized"
import { CustomSpan } from "./../ArkCustomSpanMaterialized"
import { StyleOptions, StyledStringKey, SpanStyle, ImageAttachmentLayoutStyle, ImageAttachmentInterface, CustomSpanMeasureInfo, CustomSpanMetrics, CustomSpanDrawInfo, StyledStringValue, UserDataSpan, TextStyleInterface, DecorationStyleInterface, GestureStyleInterface, ParagraphStyleInterface } from "./../ArkStyledStringInterfaces"
import { TextStyle_styled_string } from "./../ArkTextStyleStyledStringMaterialized"
import { DecorationStyle } from "./../ArkDecorationStyleMaterialized"
import { BaselineOffsetStyle } from "./../ArkBaselineOffsetStyleMaterialized"
import { LetterSpacingStyle } from "./../ArkLetterSpacingStyleMaterialized"
import { TextShadowStyle } from "./../ArkTextShadowStyleMaterialized"
import { GestureStyle } from "./../ArkGestureStyleMaterialized"
import { ParagraphStyle } from "./../ArkParagraphStyleMaterialized"
import { LineHeightStyle } from "./../ArkLineHeightStyleMaterialized"
import { UrlStyle } from "./../ArkUrlStyleMaterialized"
import { BackgroundColorStyle } from "./../ArkBackgroundColorStyleMaterialized"
import { TextBackgroundStyle } from "./../ArkSpanInterfaces"
import { TabContentAnimatedTransition, OnTabsAnimationEndCallback, TabsAnimationEvent, OnTabsAnimationStartCallback, OnTabsContentWillChangeCallback, OnTabsGestureSwipeCallback, TabsCustomContentTransitionCallback } from "./../ArkTabsInterfaces"
import { TabContentTransitionProxy } from "./../ArkTabContentTransitionProxyMaterialized"
import { Callback_RangeUpdate } from "./../ArkArkuiCustomInterfaces"
import { RefreshStatus } from "./../ArkRefreshInterfaces"
import { SymbolEffectStrategy, SymbolRenderingStrategy } from "./../ArkSymbolglyphInterfaces"
import { SwipeActionState } from "./../ArkListItemInterfaces"
import { SwiperContentTransitionProxy } from "./../ArkSwiperContentTransitionProxyMaterialized"
import { TerminationInfo } from "./../ArkEmbeddedComponentInterfaces"
import { TextPickerResult } from "./../ArkTextPickerInterfaces"
import { TimePickerResult } from "./../ArkTimePickerInterfaces"
import { UIExtensionProxy } from "./../ArkUIExtensionProxyMaterialized"
import { WithThemeAttribute, WithThemeInterface, WithThemeOptions, CustomTheme } from "./../ArkWithThemeInterfaces"
import { ContentDidScrollCallback, OnSwiperAnimationEndCallback, SwiperAnimationEvent, OnSwiperAnimationStartCallback, OnSwiperGestureSwipeCallback } from "./../ArkSwiperInterfaces"
import { CustomNodeBuilder } from "./../ArkCustomBuilderInterfaces"
import { BusinessError } from "./../ArkBaseInterfaces"
import { GetItemMainSizeByIndex } from "./../ArkWaterFlowInterfaces"
import { ImageCompleteCallback, ImageLoadResult } from "./../ArkImageSpanInterfaces"
import { NavExtender_OnUpdateStack } from "./../ArkNavigationExtenderInterfaces"
import { OnAlphabetIndexerPopupSelectCallback, OnAlphabetIndexerRequestPopupDataCallback, OnAlphabetIndexerSelectCallback } from "./../ArkAlphabetIndexerInterfaces"
import { OnCheckboxChangeCallback } from "./../ArkCheckboxInterfaces"
import { OnCheckboxGroupChangeCallback, CheckboxGroupResult, SelectStatus } from "./../ArkCheckboxgroupInterfaces"
import { OnFoldStatusChangeCallback, OnFoldStatusChangeInfo, OnHoverStatusChangeCallback, HoverEventParam, WindowStatusType } from "./../ArkFolderStackInterfaces"
import { FullScreenExitHandler } from "./../ArkFullScreenExitHandlerMaterialized"
import { OnLinearIndicatorChangeCallback } from "./../ArkLinearindicatorInterfaces"
import { OnNativeLoadCallback } from "./../ArkXcomponentInterfaces"
import { SubmitEvent } from "./../ArkSubmitEventMaterialized"
import { PageTransitionCallback, RouteType } from "./../ArkPageTransitionInterfaces"
import { PluginErrorCallback, PluginErrorData } from "./../ArkPluginComponentInterfaces"
import { SearchSubmitCallback } from "./../ArkSearchInterfaces"
import { TextAreaSubmitCallback } from "./../ArkTextAreaInterfaces"
import { WebKeyboardController } from "./../ArkWebKeyboardControllerMaterialized"
import { DotIndicator } from "./../ArkDotIndicatorBuilder"
import { DigitIndicator } from "./../ArkDigitIndicatorBuilder"
import { SubTabBarStyle } from "./../ArkSubTabBarStyleBuilder"
import { BottomTabBarStyle } from "./../ArkBottomTabBarStyleBuilder"

export function deserializeAndCallAccessibilityCallback(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as AccessibilityCallback)
    let isHover: boolean = thisDeserializer.readBoolean()
    let event: AccessibilityHoverEvent = (thisDeserializer.readAccessibilityHoverEvent() as AccessibilityHoverEvent)
    _call(isHover, event)
}
export function deserializeAndCallAsyncCallback_image_PixelMap_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((result: PixelMap) => void))
    let result: PixelMap = (thisDeserializer.readPixelMap() as PixelMap)
    _call(result)
}
export function deserializeAndCallButtonTriggerClickCallback(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ButtonTriggerClickCallback)
    let xPos: number = (thisDeserializer.readNumber() as number)
    let yPos: number = (thisDeserializer.readNumber() as number)
    _call(xPos, yPos)
}
export function deserializeAndCallCallback_Any_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((info: any) => void))
    let info: any = (thisDeserializer.readCustomObject("Any") as Object)
    _call(info)
}
export function deserializeAndCallCallback_Area_Area_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((oldValue: Area, newValue: Area) => void))
    let oldValue: Area = thisDeserializer.readArea()
    let newValue: Area = thisDeserializer.readArea()
    _call(oldValue, newValue)
}
export function deserializeAndCallCallback_Array_Number_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((input: Array<number>) => void))
    const input_buf_length: int32 = thisDeserializer.readInt32()
    let input_buf: Array<number> = new Array<number>(input_buf_length)
    for (let input_buf_i = 0; input_buf_i < input_buf_length; input_buf_i++) {
        input_buf[input_buf_i] = (thisDeserializer.readNumber() as number)
    }
    let input: Array<number> = input_buf
    _call(input)
}
export function deserializeAndCallCallback_Array_String_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((value: Array<string>) => void))
    const value_buf_length: int32 = thisDeserializer.readInt32()
    let value_buf: Array<string> = new Array<string>(value_buf_length)
    for (let value_buf_i = 0; value_buf_i < value_buf_length; value_buf_i++) {
        value_buf[value_buf_i] = (thisDeserializer.readString() as string)
    }
    let value: Array<string> = value_buf
    _call(value)
}
export function deserializeAndCallCallback_Array_TouchTestInfo_TouchResult(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((value: Array<TouchTestInfo>) => TouchResult))
    const value_buf_length: int32 = thisDeserializer.readInt32()
    let value_buf: Array<TouchTestInfo> = new Array<TouchTestInfo>(value_buf_length)
    for (let value_buf_i = 0; value_buf_i < value_buf_length; value_buf_i++) {
        value_buf[value_buf_i] = thisDeserializer.readTouchTestInfo()
    }
    let value: Array<TouchTestInfo> = value_buf
    let _continuation: ((value: TouchResult) => void) = thisDeserializer.readCallback_TouchResult_Void(true)
    const _callResult = _call(value)
    _continuation(_callResult)
}
export function deserializeAndCallCallback_Boolean(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as (() => boolean))
    let _continuation: ((parameter: boolean) => void) = thisDeserializer.readCallback_Boolean_Void(true)
    const _callResult = _call()
    _continuation(_callResult)
}
export function deserializeAndCallCallback_Boolean_HoverEvent_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((isHover: boolean, event: HoverEvent) => void))
    let isHover: boolean = thisDeserializer.readBoolean()
    let event: HoverEvent = (thisDeserializer.readHoverEvent() as HoverEvent)
    _call(isHover, event)
}
export function deserializeAndCallCallback_Boolean_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((parameter: boolean) => void))
    let parameter: boolean = thisDeserializer.readBoolean()
    _call(parameter)
}
export function deserializeAndCallCallback_CalendarRequestedData_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((event: CalendarRequestedData) => void))
    let event: CalendarRequestedData = thisDeserializer.readCalendarRequestedData()
    _call(event)
}
export function deserializeAndCallCallback_CalendarSelectedDate_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((event: CalendarSelectedDate) => void))
    let event: CalendarSelectedDate = thisDeserializer.readCalendarSelectedDate()
    _call(event)
}
export function deserializeAndCallCallback_ClickEvent_LocationButtonOnClickResult_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((event: ClickEvent, result: LocationButtonOnClickResult) => void))
    let event: ClickEvent = (thisDeserializer.readClickEvent() as ClickEvent)
    let result: LocationButtonOnClickResult = (thisDeserializer.readInt32() as LocationButtonOnClickResult)
    _call(event, result)
}
export function deserializeAndCallCallback_ClickEvent_PasteButtonOnClickResult_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((event: ClickEvent, result: PasteButtonOnClickResult) => void))
    let event: ClickEvent = (thisDeserializer.readClickEvent() as ClickEvent)
    let result: PasteButtonOnClickResult = (thisDeserializer.readInt32() as PasteButtonOnClickResult)
    _call(event, result)
}
export function deserializeAndCallCallback_ClickEvent_SaveButtonOnClickResult_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((event: ClickEvent, result: SaveButtonOnClickResult) => void))
    let event: ClickEvent = (thisDeserializer.readClickEvent() as ClickEvent)
    let result: SaveButtonOnClickResult = (thisDeserializer.readInt32() as SaveButtonOnClickResult)
    _call(event, result)
}
export function deserializeAndCallCallback_ClickEvent_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((event: ClickEvent) => void))
    let event: ClickEvent = (thisDeserializer.readClickEvent() as ClickEvent)
    _call(event)
}
export function deserializeAndCallCallback_ComputedBarAttribute_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((value: ComputedBarAttribute) => void))
    let value: ComputedBarAttribute = thisDeserializer.readComputedBarAttribute()
    _call(value)
}
export function deserializeAndCallCallback_CopyEvent_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((parameter: CopyEvent) => void))
    let parameter: CopyEvent = thisDeserializer.readCopyEvent()
    _call(parameter)
}
export function deserializeAndCallCallback_CustomBuilder_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((value: CustomBuilder) => void))
    let value: CustomBuilder = CallbackTransformer.transformToCustomBuilder(thisDeserializer.readCustomNodeBuilder())
    _call(value)
}
export function deserializeAndCallCallback_CutEvent_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((parameter: CutEvent) => void))
    let parameter: CutEvent = thisDeserializer.readCutEvent()
    _call(parameter)
}
export function deserializeAndCallCallback_Date_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((parameter: Date) => void))
    let parameter: Date = new Date(thisDeserializer.readInt64())
    _call(parameter)
}
export function deserializeAndCallCallback_DatePickerResult_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((value: DatePickerResult) => void))
    let value: DatePickerResult = thisDeserializer.readDatePickerResult()
    _call(value)
}
export function deserializeAndCallCallback_DeleteValue_Boolean(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((parameter: DeleteValue) => boolean))
    let parameter: DeleteValue = thisDeserializer.readDeleteValue()
    let _continuation: ((parameter: boolean) => void) = thisDeserializer.readCallback_Boolean_Void(true)
    const _callResult = _call(parameter)
    _continuation(_callResult)
}
export function deserializeAndCallCallback_DeleteValue_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((parameter: DeleteValue) => void))
    let parameter: DeleteValue = thisDeserializer.readDeleteValue()
    _call(parameter)
}
export function deserializeAndCallCallback_DismissContentCoverAction_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((parameter: DismissContentCoverAction) => void))
    let parameter: DismissContentCoverAction = thisDeserializer.readDismissContentCoverAction()
    _call(parameter)
}
export function deserializeAndCallCallback_DismissDialogAction_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((parameter: DismissDialogAction) => void))
    let parameter: DismissDialogAction = thisDeserializer.readDismissDialogAction()
    _call(parameter)
}
export function deserializeAndCallCallback_DismissPopupAction_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((parameter: DismissPopupAction) => void))
    let parameter: DismissPopupAction = thisDeserializer.readDismissPopupAction()
    _call(parameter)
}
export function deserializeAndCallCallback_DismissSheetAction_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((parameter: DismissSheetAction) => void))
    let parameter: DismissSheetAction = thisDeserializer.readDismissSheetAction()
    _call(parameter)
}
export function deserializeAndCallCallback_DragEvent_String_Union_CustomBuilder_DragItemInfo(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((event: DragEvent, extraParams?: string) => CustomBuilder | DragItemInfo))
    let event: DragEvent = (thisDeserializer.readDragEvent() as DragEvent)
    const extraParams_buf_runtimeType = (thisDeserializer.readInt8() as int32)
    let extraParams_buf: string | undefined|undefined 
    if ((RuntimeType.UNDEFINED) != (extraParams_buf_runtimeType))
    {
        extraParams_buf = (thisDeserializer.readString() as string)
    }
    let extraParams: string | undefined|undefined = extraParams_buf
    let _continuation: ((value: CustomBuilder | DragItemInfo) => void) = thisDeserializer.readCallback_Union_CustomBuilder_DragItemInfo_Void(true)
    const _callResult = _call(event, extraParams)
    _continuation(_callResult)
}
export function deserializeAndCallCallback_DragEvent_String_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((event: DragEvent, extraParams?: string) => void))
    let event: DragEvent = (thisDeserializer.readDragEvent() as DragEvent)
    const extraParams_buf_runtimeType = (thisDeserializer.readInt8() as int32)
    let extraParams_buf: string | undefined|undefined 
    if ((RuntimeType.UNDEFINED) != (extraParams_buf_runtimeType))
    {
        extraParams_buf = (thisDeserializer.readString() as string)
    }
    let extraParams: string | undefined|undefined = extraParams_buf
    _call(event, extraParams)
}
export function deserializeAndCallCallback_EnterKeyType_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((enterKey: EnterKeyType) => void))
    let enterKey: EnterKeyType = (thisDeserializer.readInt32() as EnterKeyType)
    _call(enterKey)
}
export function deserializeAndCallCallback_Extender_OnFinish(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as Callback_Extender_OnFinish)
    _call()
}
export function deserializeAndCallCallback_Extender_OnProgress(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as Callback_Extender_OnProgress)
    let value: float32 = thisDeserializer.readFloat32()
    _call(value)
}
export function deserializeAndCallCallback_FormCallbackInfo_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((parameter: FormCallbackInfo) => void))
    let parameter: FormCallbackInfo = thisDeserializer.readFormCallbackInfo()
    _call(parameter)
}
export function deserializeAndCallCallback_FullscreenInfo_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((parameter: FullscreenInfo) => void))
    let parameter: FullscreenInfo = thisDeserializer.readFullscreenInfo()
    _call(parameter)
}
export function deserializeAndCallCallback_GestureEvent_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((event: GestureEvent) => void))
    let event: GestureEvent = (thisDeserializer.readGestureEvent() as GestureEvent)
    _call(event)
}
export function deserializeAndCallCallback_GestureInfo_BaseGestureEvent_GestureJudgeResult(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((gestureInfo: GestureInfo, event: BaseGestureEvent) => GestureJudgeResult))
    let gestureInfo: GestureInfo = thisDeserializer.readGestureInfo()
    let event: BaseGestureEvent = (thisDeserializer.readBaseGestureEvent() as BaseGestureEvent)
    let _continuation: ((value: GestureJudgeResult) => void) = thisDeserializer.readCallback_GestureJudgeResult_Void(true)
    const _callResult = _call(gestureInfo, event)
    _continuation(_callResult)
}
export function deserializeAndCallCallback_GestureJudgeResult_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((value: GestureJudgeResult) => void))
    let value: GestureJudgeResult = (thisDeserializer.readInt32() as GestureJudgeResult)
    _call(value)
}
export function deserializeAndCallCallback_GestureRecognizer_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((value: GestureRecognizer) => void))
    let value: GestureRecognizer = (thisDeserializer.readGestureRecognizer() as GestureRecognizer)
    _call(value)
}
export function deserializeAndCallCallback_HitTestMode_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((value: HitTestMode) => void))
    let value: HitTestMode = (thisDeserializer.readInt32() as HitTestMode)
    _call(value)
}
export function deserializeAndCallCallback_InsertValue_Boolean(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((parameter: InsertValue) => boolean))
    let parameter: InsertValue = thisDeserializer.readInsertValue()
    let _continuation: ((parameter: boolean) => void) = thisDeserializer.readCallback_Boolean_Void(true)
    const _callResult = _call(parameter)
    _continuation(_callResult)
}
export function deserializeAndCallCallback_InsertValue_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((parameter: InsertValue) => void))
    let parameter: InsertValue = thisDeserializer.readInsertValue()
    _call(parameter)
}
export function deserializeAndCallCallback_IsolatedComponentAttribute_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((value: IsolatedComponentAttribute) => void))
    let value: IsolatedComponentAttribute = thisDeserializer.readIsolatedComponentAttribute()
    _call(value)
}
export function deserializeAndCallCallback_ItemDragInfo_Number_Number_Boolean_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((event: ItemDragInfo, itemIndex: number, insertIndex: number, isSuccess: boolean) => void))
    let event: ItemDragInfo = thisDeserializer.readItemDragInfo()
    let itemIndex: number = (thisDeserializer.readNumber() as number)
    let insertIndex: number = (thisDeserializer.readNumber() as number)
    let isSuccess: boolean = thisDeserializer.readBoolean()
    _call(event, itemIndex, insertIndex, isSuccess)
}
export function deserializeAndCallCallback_ItemDragInfo_Number_Number_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((event: ItemDragInfo, itemIndex: number, insertIndex: number) => void))
    let event: ItemDragInfo = thisDeserializer.readItemDragInfo()
    let itemIndex: number = (thisDeserializer.readNumber() as number)
    let insertIndex: number = (thisDeserializer.readNumber() as number)
    _call(event, itemIndex, insertIndex)
}
export function deserializeAndCallCallback_ItemDragInfo_Number_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((event: ItemDragInfo, itemIndex: number) => void))
    let event: ItemDragInfo = thisDeserializer.readItemDragInfo()
    let itemIndex: number = (thisDeserializer.readNumber() as number)
    _call(event, itemIndex)
}
export function deserializeAndCallCallback_ItemDragInfo_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((event: ItemDragInfo) => void))
    let event: ItemDragInfo = thisDeserializer.readItemDragInfo()
    _call(event)
}
export function deserializeAndCallCallback_KeyEvent_Boolean(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((parameter: KeyEvent) => boolean))
    let parameter: KeyEvent = (thisDeserializer.readKeyEvent() as KeyEvent)
    let _continuation: ((parameter: boolean) => void) = thisDeserializer.readCallback_Boolean_Void(true)
    const _callResult = _call(parameter)
    _continuation(_callResult)
}
export function deserializeAndCallCallback_KeyEvent_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((event: KeyEvent) => void))
    let event: KeyEvent = (thisDeserializer.readKeyEvent() as KeyEvent)
    _call(event)
}
export function deserializeAndCallCallback_Literal_Boolean_isVisible_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((event: { isVisible: boolean }) => void))
    const event_buf_isVisible: boolean = thisDeserializer.readBoolean()
    let event: { isVisible: boolean } = ({isVisible: event_buf_isVisible} as { isVisible: boolean })
    _call(event)
}
export function deserializeAndCallCallback_Literal_Function_handler_Object_error_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((event?: { handler: Function, error: Object }) => void))
    const event_buf_runtimeType = (thisDeserializer.readInt8() as int32)
    let event_buf: { handler: Function, error: Object } | undefined|undefined 
    if ((RuntimeType.UNDEFINED) != (event_buf_runtimeType))
    {
        const event_buf__handler: Function = (thisDeserializer.readFunction() as Function)
        const event_buf__error: Object = (thisDeserializer.readCustomObject("Object") as Object)
        event_buf = ({handler: event_buf__handler, error: event_buf__error} as { handler: Function, error: Object })
    }
    let event: { handler: Function, error: Object } | undefined|undefined = event_buf
    _call(event)
}
export function deserializeAndCallCallback_Literal_Number_code_Want_want_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((parameter: { code: number, want?: Want }) => void))
    const parameter_buf_code: number = (thisDeserializer.readNumber() as number)
    const parameter_buf_want_buf_runtimeType = (thisDeserializer.readInt8() as int32)
    let parameter_buf_want_buf: Want | undefined|undefined 
    if ((RuntimeType.UNDEFINED) != (parameter_buf_want_buf_runtimeType))
    {
        parameter_buf_want_buf = thisDeserializer.readWant()
    }
    const parameter_buf_want: undefined | Want = parameter_buf_want_buf
    let parameter: { code: number, want?: Want } = ({code: parameter_buf_code, want: parameter_buf_want} as { code: number, want?: Want })
    _call(parameter)
}
export function deserializeAndCallCallback_Literal_Number_errcode_String_msg_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((info: { errcode: number, msg: string }) => void))
    const info_buf_errcode: number = (thisDeserializer.readNumber() as number)
    const info_buf_msg: string = (thisDeserializer.readString() as string)
    let info: { errcode: number, msg: string } = ({errcode: info_buf_errcode, msg: info_buf_msg} as { errcode: number, msg: string })
    _call(info)
}
export function deserializeAndCallCallback_Literal_Number_offsetRemain_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((value: { offsetRemain: number }) => void))
    const value_buf_offsetRemain: number = (thisDeserializer.readNumber() as number)
    let value: { offsetRemain: number } = ({offsetRemain: value_buf_offsetRemain} as { offsetRemain: number })
    _call(value)
}
export function deserializeAndCallCallback_Literal_Object_detail_Boolean(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((event?: { detail: Object }) => boolean))
    const event_buf_runtimeType = (thisDeserializer.readInt8() as int32)
    let event_buf: { detail: Object } | undefined|undefined 
    if ((RuntimeType.UNDEFINED) != (event_buf_runtimeType))
    {
        const event_buf__detail: Object = (thisDeserializer.readCustomObject("Object") as Object)
        event_buf = ({detail: event_buf__detail} as { detail: Object })
    }
    let event: { detail: Object } | undefined|undefined = event_buf
    let _continuation: ((parameter: boolean) => void) = thisDeserializer.readCallback_Boolean_Void(true)
    const _callResult = _call(event)
    _continuation(_callResult)
}
export function deserializeAndCallCallback_Literal_String_plainText_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((selectedText: { plainText: string }) => void))
    const selectedText_buf_plainText: string = (thisDeserializer.readString() as string)
    let selectedText: { plainText: string } = ({plainText: selectedText_buf_plainText} as { plainText: string })
    _call(selectedText)
}
export function deserializeAndCallCallback_MouseEvent_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((event: MouseEvent) => void))
    let event: MouseEvent = (thisDeserializer.readMouseEvent() as MouseEvent)
    _call(event)
}
export function deserializeAndCallCallback_NativeEmbedDataInfo_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((event: NativeEmbedDataInfo) => void))
    let event: NativeEmbedDataInfo = thisDeserializer.readNativeEmbedDataInfo()
    _call(event)
}
export function deserializeAndCallCallback_NativeEmbedTouchInfo_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((event: NativeEmbedTouchInfo) => void))
    let event: NativeEmbedTouchInfo = thisDeserializer.readNativeEmbedTouchInfo()
    _call(event)
}
export function deserializeAndCallCallback_NavDestinationContext_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((parameter: NavDestinationContext) => void))
    let parameter: NavDestinationContext = (thisDeserializer.readNavDestinationContext() as NavDestinationContext)
    _call(parameter)
}
export function deserializeAndCallCallback_NavigationMode_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((mode: NavigationMode) => void))
    let mode: NavigationMode = (thisDeserializer.readInt32() as NavigationMode)
    _call(mode)
}
export function deserializeAndCallCallback_NavigationTitleMode_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((titleMode: NavigationTitleMode) => void))
    let titleMode: NavigationTitleMode = (thisDeserializer.readInt32() as NavigationTitleMode)
    _call(titleMode)
}
export function deserializeAndCallCallback_NavigationTransitionProxy_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((transitionProxy: NavigationTransitionProxy) => void))
    let transitionProxy: NavigationTransitionProxy = (thisDeserializer.readNavigationTransitionProxy() as NavigationTransitionProxy)
    _call(transitionProxy)
}
export function deserializeAndCallCallback_Number_Boolean(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((index: number) => boolean))
    let index: number = (thisDeserializer.readNumber() as number)
    let _continuation: ((parameter: boolean) => void) = thisDeserializer.readCallback_Boolean_Void(true)
    const _callResult = _call(index)
    _continuation(_callResult)
}
export function deserializeAndCallCallback_Number_Number_Boolean(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((from: number, to: number) => boolean))
    let from: number = (thisDeserializer.readNumber() as number)
    let to: number = (thisDeserializer.readNumber() as number)
    let _continuation: ((parameter: boolean) => void) = thisDeserializer.readCallback_Boolean_Void(true)
    const _callResult = _call(from, to)
    _continuation(_callResult)
}
export function deserializeAndCallCallback_Number_Number_ComputedBarAttribute(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((index: number, offset: number) => ComputedBarAttribute))
    let index: number = (thisDeserializer.readNumber() as number)
    let offset: number = (thisDeserializer.readNumber() as number)
    let _continuation: ((value: ComputedBarAttribute) => void) = thisDeserializer.readCallback_ComputedBarAttribute_Void(true)
    const _callResult = _call(index, offset)
    _continuation(_callResult)
}
export function deserializeAndCallCallback_Number_Number_Number_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((start: number, end: number, center: number) => void))
    let start: number = (thisDeserializer.readNumber() as number)
    let end: number = (thisDeserializer.readNumber() as number)
    let center: number = (thisDeserializer.readNumber() as number)
    _call(start, end, center)
}
export function deserializeAndCallCallback_Number_Number_PanelMode_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((width: number, height: number, mode: PanelMode) => void))
    let width: number = (thisDeserializer.readNumber() as number)
    let height: number = (thisDeserializer.readNumber() as number)
    let mode: PanelMode = (thisDeserializer.readInt32() as PanelMode)
    _call(width, height, mode)
}
export function deserializeAndCallCallback_Number_Number_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((first: number, last: number) => void))
    let first: number = (thisDeserializer.readNumber() as number)
    let last: number = (thisDeserializer.readNumber() as number)
    _call(first, last)
}
export function deserializeAndCallCallback_Number_ScrollState_Literal_Number_offsetRemain(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((offset: number, state: ScrollState) => { offsetRemain: number }))
    let offset: number = (thisDeserializer.readNumber() as number)
    let state: ScrollState = (thisDeserializer.readInt32() as ScrollState)
    let _continuation: ((value: { offsetRemain: number }) => void) = thisDeserializer.readCallback_Literal_Number_offsetRemain_Void(true)
    const _callResult = _call(offset, state)
    _continuation(_callResult)
}
export function deserializeAndCallCallback_Number_SliderChangeMode_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((value: number, mode: SliderChangeMode) => void))
    let value: number = (thisDeserializer.readNumber() as number)
    let mode: SliderChangeMode = (thisDeserializer.readInt32() as SliderChangeMode)
    _call(value, mode)
}
export function deserializeAndCallCallback_Number_String_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((index: number, value: string) => void))
    let index: number = (thisDeserializer.readNumber() as number)
    let value: string = (thisDeserializer.readString() as string)
    _call(index, value)
}
export function deserializeAndCallCallback_Number_Tuple_Number_Number(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((index: number) => [ number, number ]))
    let index: number = (thisDeserializer.readNumber() as number)
    let _continuation: ((value: [ number, number ]) => void) = thisDeserializer.readCallback_Tuple_Number_Number_Void(true)
    const _callResult = _call(index)
    _continuation(_callResult)
}
export function deserializeAndCallCallback_Number_Tuple_Number_Number_Number_Number(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((index: number) => [ number, number, number, number ]))
    let index: number = (thisDeserializer.readNumber() as number)
    let _continuation: ((value: [ number, number, number, number ]) => void) = thisDeserializer.readCallback_Tuple_Number_Number_Number_Number_Void(true)
    const _callResult = _call(index)
    _continuation(_callResult)
}
export function deserializeAndCallCallback_Number_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((index: number) => void))
    let index: number = (thisDeserializer.readNumber() as number)
    _call(index)
}
export function deserializeAndCallCallback_OffsetResult_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((value: OffsetResult) => void))
    let value: OffsetResult = thisDeserializer.readOffsetResult()
    _call(value)
}
export function deserializeAndCallCallback_ScrollResult_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((value: ScrollResult) => void))
    let value: ScrollResult = thisDeserializer.readScrollResult()
    _call(value)
}
export function deserializeAndCallCallback_OnAlertEvent_Boolean(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((parameter: OnAlertEvent) => boolean))
    let parameter: OnAlertEvent = thisDeserializer.readOnAlertEvent()
    let _continuation: ((parameter: boolean) => void) = thisDeserializer.readCallback_Boolean_Void(true)
    const _callResult = _call(parameter)
    _continuation(_callResult)
}
export function deserializeAndCallCallback_OnAudioStateChangedEvent_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((parameter: OnAudioStateChangedEvent) => void))
    let parameter: OnAudioStateChangedEvent = thisDeserializer.readOnAudioStateChangedEvent()
    _call(parameter)
}
export function deserializeAndCallCallback_OnBeforeUnloadEvent_Boolean(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((parameter: OnBeforeUnloadEvent) => boolean))
    let parameter: OnBeforeUnloadEvent = thisDeserializer.readOnBeforeUnloadEvent()
    let _continuation: ((parameter: boolean) => void) = thisDeserializer.readCallback_Boolean_Void(true)
    const _callResult = _call(parameter)
    _continuation(_callResult)
}
export function deserializeAndCallCallback_OnClientAuthenticationEvent_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((parameter: OnClientAuthenticationEvent) => void))
    let parameter: OnClientAuthenticationEvent = thisDeserializer.readOnClientAuthenticationEvent()
    _call(parameter)
}
export function deserializeAndCallCallback_OnConfirmEvent_Boolean(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((parameter: OnConfirmEvent) => boolean))
    let parameter: OnConfirmEvent = thisDeserializer.readOnConfirmEvent()
    let _continuation: ((parameter: boolean) => void) = thisDeserializer.readCallback_Boolean_Void(true)
    const _callResult = _call(parameter)
    _continuation(_callResult)
}
export function deserializeAndCallCallback_OnConsoleEvent_Boolean(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((parameter: OnConsoleEvent) => boolean))
    let parameter: OnConsoleEvent = thisDeserializer.readOnConsoleEvent()
    let _continuation: ((parameter: boolean) => void) = thisDeserializer.readCallback_Boolean_Void(true)
    const _callResult = _call(parameter)
    _continuation(_callResult)
}
export function deserializeAndCallCallback_OnContextMenuShowEvent_Boolean(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((parameter: OnContextMenuShowEvent) => boolean))
    let parameter: OnContextMenuShowEvent = thisDeserializer.readOnContextMenuShowEvent()
    let _continuation: ((parameter: boolean) => void) = thisDeserializer.readCallback_Boolean_Void(true)
    const _callResult = _call(parameter)
    _continuation(_callResult)
}
export function deserializeAndCallCallback_OnDataResubmittedEvent_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((parameter: OnDataResubmittedEvent) => void))
    let parameter: OnDataResubmittedEvent = thisDeserializer.readOnDataResubmittedEvent()
    _call(parameter)
}
export function deserializeAndCallCallback_OnDownloadStartEvent_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((parameter: OnDownloadStartEvent) => void))
    let parameter: OnDownloadStartEvent = thisDeserializer.readOnDownloadStartEvent()
    _call(parameter)
}
export function deserializeAndCallCallback_OnErrorReceiveEvent_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((parameter: OnErrorReceiveEvent) => void))
    let parameter: OnErrorReceiveEvent = thisDeserializer.readOnErrorReceiveEvent()
    _call(parameter)
}
export function deserializeAndCallCallback_OnFaviconReceivedEvent_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((parameter: OnFaviconReceivedEvent) => void))
    let parameter: OnFaviconReceivedEvent = thisDeserializer.readOnFaviconReceivedEvent()
    _call(parameter)
}
export function deserializeAndCallCallback_OnFirstContentfulPaintEvent_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((parameter: OnFirstContentfulPaintEvent) => void))
    let parameter: OnFirstContentfulPaintEvent = thisDeserializer.readOnFirstContentfulPaintEvent()
    _call(parameter)
}
export function deserializeAndCallCallback_OnGeolocationShowEvent_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((parameter: OnGeolocationShowEvent) => void))
    let parameter: OnGeolocationShowEvent = thisDeserializer.readOnGeolocationShowEvent()
    _call(parameter)
}
export function deserializeAndCallCallback_OnHttpAuthRequestEvent_Boolean(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((parameter: OnHttpAuthRequestEvent) => boolean))
    let parameter: OnHttpAuthRequestEvent = thisDeserializer.readOnHttpAuthRequestEvent()
    let _continuation: ((parameter: boolean) => void) = thisDeserializer.readCallback_Boolean_Void(true)
    const _callResult = _call(parameter)
    _continuation(_callResult)
}
export function deserializeAndCallCallback_OnHttpErrorReceiveEvent_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((parameter: OnHttpErrorReceiveEvent) => void))
    let parameter: OnHttpErrorReceiveEvent = thisDeserializer.readOnHttpErrorReceiveEvent()
    _call(parameter)
}
export function deserializeAndCallCallback_OnInterceptRequestEvent_WebResourceResponse(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((parameter: OnInterceptRequestEvent) => WebResourceResponse))
    let parameter: OnInterceptRequestEvent = thisDeserializer.readOnInterceptRequestEvent()
    let _continuation: ((value: WebResourceResponse) => void) = thisDeserializer.readCallback_WebResourceResponse_Void(true)
    const _callResult = _call(parameter)
    _continuation(_callResult)
}
export function deserializeAndCallCallback_OnLoadInterceptEvent_Boolean(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((parameter: OnLoadInterceptEvent) => boolean))
    let parameter: OnLoadInterceptEvent = thisDeserializer.readOnLoadInterceptEvent()
    let _continuation: ((parameter: boolean) => void) = thisDeserializer.readCallback_Boolean_Void(true)
    const _callResult = _call(parameter)
    _continuation(_callResult)
}
export function deserializeAndCallCallback_OnOverScrollEvent_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((parameter: OnOverScrollEvent) => void))
    let parameter: OnOverScrollEvent = thisDeserializer.readOnOverScrollEvent()
    _call(parameter)
}
export function deserializeAndCallCallback_OnPageBeginEvent_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((parameter: OnPageBeginEvent) => void))
    let parameter: OnPageBeginEvent = thisDeserializer.readOnPageBeginEvent()
    _call(parameter)
}
export function deserializeAndCallCallback_OnPageEndEvent_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((parameter: OnPageEndEvent) => void))
    let parameter: OnPageEndEvent = thisDeserializer.readOnPageEndEvent()
    _call(parameter)
}
export function deserializeAndCallCallback_OnPageVisibleEvent_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((parameter: OnPageVisibleEvent) => void))
    let parameter: OnPageVisibleEvent = thisDeserializer.readOnPageVisibleEvent()
    _call(parameter)
}
export function deserializeAndCallCallback_OnPermissionRequestEvent_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((parameter: OnPermissionRequestEvent) => void))
    let parameter: OnPermissionRequestEvent = thisDeserializer.readOnPermissionRequestEvent()
    _call(parameter)
}
export function deserializeAndCallCallback_OnProgressChangeEvent_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((parameter: OnProgressChangeEvent) => void))
    let parameter: OnProgressChangeEvent = thisDeserializer.readOnProgressChangeEvent()
    _call(parameter)
}
export function deserializeAndCallCallback_OnPromptEvent_Boolean(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((parameter: OnPromptEvent) => boolean))
    let parameter: OnPromptEvent = thisDeserializer.readOnPromptEvent()
    let _continuation: ((parameter: boolean) => void) = thisDeserializer.readCallback_Boolean_Void(true)
    const _callResult = _call(parameter)
    _continuation(_callResult)
}
export function deserializeAndCallCallback_OnRefreshAccessedHistoryEvent_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((parameter: OnRefreshAccessedHistoryEvent) => void))
    let parameter: OnRefreshAccessedHistoryEvent = thisDeserializer.readOnRefreshAccessedHistoryEvent()
    _call(parameter)
}
export function deserializeAndCallCallback_OnRenderExitedEvent_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((parameter: OnRenderExitedEvent) => void))
    let parameter: OnRenderExitedEvent = thisDeserializer.readOnRenderExitedEvent()
    _call(parameter)
}
export function deserializeAndCallCallback_OnResourceLoadEvent_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((parameter: OnResourceLoadEvent) => void))
    let parameter: OnResourceLoadEvent = thisDeserializer.readOnResourceLoadEvent()
    _call(parameter)
}
export function deserializeAndCallCallback_OnScaleChangeEvent_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((parameter: OnScaleChangeEvent) => void))
    let parameter: OnScaleChangeEvent = thisDeserializer.readOnScaleChangeEvent()
    _call(parameter)
}
export function deserializeAndCallCallback_OnScreenCaptureRequestEvent_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((parameter: OnScreenCaptureRequestEvent) => void))
    let parameter: OnScreenCaptureRequestEvent = thisDeserializer.readOnScreenCaptureRequestEvent()
    _call(parameter)
}
export function deserializeAndCallCallback_OnScrollEvent_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((parameter: OnScrollEvent) => void))
    let parameter: OnScrollEvent = thisDeserializer.readOnScrollEvent()
    _call(parameter)
}
export function deserializeAndCallCallback_OnScrollFrameBeginHandlerResult_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((value: OnScrollFrameBeginHandlerResult) => void))
    let value: OnScrollFrameBeginHandlerResult = thisDeserializer.readOnScrollFrameBeginHandlerResult()
    _call(value)
}
export function deserializeAndCallCallback_OnSearchResultReceiveEvent_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((parameter: OnSearchResultReceiveEvent) => void))
    let parameter: OnSearchResultReceiveEvent = thisDeserializer.readOnSearchResultReceiveEvent()
    _call(parameter)
}
export function deserializeAndCallCallback_OnShowFileSelectorEvent_Boolean(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((parameter: OnShowFileSelectorEvent) => boolean))
    let parameter: OnShowFileSelectorEvent = thisDeserializer.readOnShowFileSelectorEvent()
    let _continuation: ((parameter: boolean) => void) = thisDeserializer.readCallback_Boolean_Void(true)
    const _callResult = _call(parameter)
    _continuation(_callResult)
}
export function deserializeAndCallCallback_OnSslErrorEventReceiveEvent_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((parameter: OnSslErrorEventReceiveEvent) => void))
    let parameter: OnSslErrorEventReceiveEvent = thisDeserializer.readOnSslErrorEventReceiveEvent()
    _call(parameter)
}
export function deserializeAndCallCallback_OnTitleReceiveEvent_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((parameter: OnTitleReceiveEvent) => void))
    let parameter: OnTitleReceiveEvent = thisDeserializer.readOnTitleReceiveEvent()
    _call(parameter)
}
export function deserializeAndCallCallback_OnTouchIconUrlReceivedEvent_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((parameter: OnTouchIconUrlReceivedEvent) => void))
    let parameter: OnTouchIconUrlReceivedEvent = thisDeserializer.readOnTouchIconUrlReceivedEvent()
    _call(parameter)
}
export function deserializeAndCallCallback_OnWindowNewEvent_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((parameter: OnWindowNewEvent) => void))
    let parameter: OnWindowNewEvent = thisDeserializer.readOnWindowNewEvent()
    _call(parameter)
}
export function deserializeAndCallCallback_Opt_Array_String_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((error?: Array<string> | undefined) => void))
    const error_buf_runtimeType = (thisDeserializer.readInt8() as int32)
    let error_buf: Array<string> | undefined|undefined 
    if ((RuntimeType.UNDEFINED) != (error_buf_runtimeType))
    {
        const error_buf__length: int32 = thisDeserializer.readInt32()
        let error_buf_: Array<string> = new Array<string>(error_buf__length)
        for (let error_buf__i = 0; error_buf__i < error_buf__length; error_buf__i++) {
            error_buf_[error_buf__i] = (thisDeserializer.readString() as string)
        }
        error_buf = error_buf_
    }
    let error: Array<string> | undefined|undefined = error_buf
    _call(error)
}
export function deserializeAndCallCallback_Opt_NavigationAnimatedTransition_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((value: NavigationAnimatedTransition | undefined) => void))
    const value_buf_runtimeType = (thisDeserializer.readInt8() as int32)
    let value_buf: NavigationAnimatedTransition | undefined|undefined 
    if ((RuntimeType.UNDEFINED) != (value_buf_runtimeType))
    {
        value_buf = thisDeserializer.readNavigationAnimatedTransition()
    }
    let value: NavigationAnimatedTransition | undefined|undefined = value_buf
    _call(value)
}
export function deserializeAndCallCallback_Opt_StyledString_Opt_Array_String_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((value?: StyledString | undefined, error?: Array<string> | undefined) => void))
    const value_buf_runtimeType = (thisDeserializer.readInt8() as int32)
    let value_buf: StyledString | undefined|undefined 
    if ((RuntimeType.UNDEFINED) != (value_buf_runtimeType))
    {
        value_buf = (thisDeserializer.readStyledString() as StyledString)
    }
    let value: StyledString | undefined|undefined = value_buf
    const error_buf_runtimeType = (thisDeserializer.readInt8() as int32)
    let error_buf: Array<string> | undefined|undefined 
    if ((RuntimeType.UNDEFINED) != (error_buf_runtimeType))
    {
        const error_buf__length: int32 = thisDeserializer.readInt32()
        let error_buf_: Array<string> = new Array<string>(error_buf__length)
        for (let error_buf__i = 0; error_buf__i < error_buf__length; error_buf__i++) {
            error_buf_[error_buf__i] = (thisDeserializer.readString() as string)
        }
        error_buf = error_buf_
    }
    let error: Array<string> | undefined|undefined = error_buf
    _call(value, error)
}
export function deserializeAndCallCallback_Opt_TabContentAnimatedTransition_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((value: TabContentAnimatedTransition | undefined) => void))
    const value_buf_runtimeType = (thisDeserializer.readInt8() as int32)
    let value_buf: TabContentAnimatedTransition | undefined|undefined 
    if ((RuntimeType.UNDEFINED) != (value_buf_runtimeType))
    {
        value_buf = thisDeserializer.readTabContentAnimatedTransition()
    }
    let value: TabContentAnimatedTransition | undefined|undefined = value_buf
    _call(value)
}
export function deserializeAndCallCallback_PanelMode_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((mode: PanelMode) => void))
    let mode: PanelMode = (thisDeserializer.readInt32() as PanelMode)
    _call(mode)
}
export function deserializeAndCallCallback_PlaybackInfo_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((parameter: PlaybackInfo) => void))
    let parameter: PlaybackInfo = thisDeserializer.readPlaybackInfo()
    _call(parameter)
}
export function deserializeAndCallCallback_Pointer_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((value: KPointer) => void))
    let value: KPointer = thisDeserializer.readPointer()
    _call(value)
}
export function deserializeAndCallCallback_PopInfo_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((parameter: PopInfo) => void))
    let parameter: PopInfo = thisDeserializer.readPopInfo()
    _call(parameter)
}
export function deserializeAndCallCallback_PreDragStatus_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((parameter: PreDragStatus) => void))
    let parameter: PreDragStatus = (thisDeserializer.readInt32() as PreDragStatus)
    _call(parameter)
}
export function deserializeAndCallCallback_PreparedInfo_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((parameter: PreparedInfo) => void))
    let parameter: PreparedInfo = thisDeserializer.readPreparedInfo()
    _call(parameter)
}
export function deserializeAndCallCallback_RangeUpdate(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as Callback_RangeUpdate)
    let index: int32 = thisDeserializer.readInt32()
    let mark: KPointer = thisDeserializer.readPointer()
    let end: int32 = thisDeserializer.readInt32()
    _call(index, mark, end)
}
export function deserializeAndCallCallback_RefreshStatus_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((state: RefreshStatus) => void))
    let state: RefreshStatus = (thisDeserializer.readInt32() as RefreshStatus)
    _call(state)
}
export function deserializeAndCallCallback_ResourceStr_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((value: ResourceStr) => void))
    const value_buf_selector: number = thisDeserializer.readInt8()
    let value_buf: string | Resource | undefined|undefined 
    if (value_buf_selector == 0) {
        value_buf = (thisDeserializer.readString() as string)
    }
    else if (value_buf_selector == 1) {
        value_buf = thisDeserializer.readResource()
    }
    else {
        throw new Error("One of the branches for value_buf has to be chosen through deserialisation.")
    }
    let value: ResourceStr = (value_buf as string | Resource)
    _call(value)
}
export function deserializeAndCallCallback_RichEditorChangeValue_Boolean(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((parameter: RichEditorChangeValue) => boolean))
    let parameter: RichEditorChangeValue = thisDeserializer.readRichEditorChangeValue()
    let _continuation: ((parameter: boolean) => void) = thisDeserializer.readCallback_Boolean_Void(true)
    const _callResult = _call(parameter)
    _continuation(_callResult)
}
export function deserializeAndCallCallback_RichEditorDeleteValue_Boolean(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((parameter: RichEditorDeleteValue) => boolean))
    let parameter: RichEditorDeleteValue = thisDeserializer.readRichEditorDeleteValue()
    let _continuation: ((parameter: boolean) => void) = thisDeserializer.readCallback_Boolean_Void(true)
    const _callResult = _call(parameter)
    _continuation(_callResult)
}
export function deserializeAndCallCallback_RichEditorInsertValue_Boolean(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((parameter: RichEditorInsertValue) => boolean))
    let parameter: RichEditorInsertValue = thisDeserializer.readRichEditorInsertValue()
    let _continuation: ((parameter: boolean) => void) = thisDeserializer.readCallback_Boolean_Void(true)
    const _callResult = _call(parameter)
    _continuation(_callResult)
}
export function deserializeAndCallCallback_RichEditorRange_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((parameter: RichEditorRange) => void))
    let parameter: RichEditorRange = thisDeserializer.readRichEditorRange()
    _call(parameter)
}
export function deserializeAndCallCallback_RichEditorSelection_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((parameter: RichEditorSelection) => void))
    let parameter: RichEditorSelection = thisDeserializer.readRichEditorSelection()
    _call(parameter)
}
export function deserializeAndCallCallback_RichEditorTextSpanResult_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((parameter: RichEditorTextSpanResult) => void))
    let parameter: RichEditorTextSpanResult = thisDeserializer.readRichEditorTextSpanResult()
    _call(parameter)
}
export function deserializeAndCallCallback_SheetDismiss_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((sheetDismiss: SheetDismiss) => void))
    let sheetDismiss: SheetDismiss = thisDeserializer.readSheetDismiss()
    _call(sheetDismiss)
}
export function deserializeAndCallCallback_SheetType_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((parameter: SheetType) => void))
    let parameter: SheetType = (thisDeserializer.readInt32() as SheetType)
    _call(parameter)
}
export function deserializeAndCallCallback_SpringBackAction_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((parameter: SpringBackAction) => void))
    let parameter: SpringBackAction = thisDeserializer.readSpringBackAction()
    _call(parameter)
}
export function deserializeAndCallCallback_String_Number_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((value: string, index: number) => void))
    let value: string = (thisDeserializer.readString() as string)
    let index: number = (thisDeserializer.readNumber() as number)
    _call(value, index)
}
export function deserializeAndCallCallback_String_PasteEvent_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((value: string, event: PasteEvent) => void))
    let value: string = (thisDeserializer.readString() as string)
    let event: PasteEvent = thisDeserializer.readPasteEvent()
    _call(value, event)
}
export function deserializeAndCallCallback_String_Unknown_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((name: string, param: unknown) => void))
    let name: string = (thisDeserializer.readString() as string)
    let param: unknown = (thisDeserializer.readCustomObject("Any") as Object)
    _call(name, param)
}
export function deserializeAndCallCallback_String_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((breakpoints: string) => void))
    let breakpoints: string = (thisDeserializer.readString() as string)
    _call(breakpoints)
}
export function deserializeAndCallCallback_StyledStringChangeValue_Boolean(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((parameter: StyledStringChangeValue) => boolean))
    let parameter: StyledStringChangeValue = thisDeserializer.readStyledStringChangeValue()
    let _continuation: ((parameter: boolean) => void) = thisDeserializer.readCallback_Boolean_Void(true)
    const _callResult = _call(parameter)
    _continuation(_callResult)
}
export function deserializeAndCallCallback_SwipeActionState_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((state: SwipeActionState) => void))
    let state: SwipeActionState = (thisDeserializer.readInt32() as SwipeActionState)
    _call(state)
}
export function deserializeAndCallCallback_SwiperContentTransitionProxy_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((parameter: SwiperContentTransitionProxy) => void))
    let parameter: SwiperContentTransitionProxy = (thisDeserializer.readSwiperContentTransitionProxy() as SwiperContentTransitionProxy)
    _call(parameter)
}
export function deserializeAndCallCallback_TabContentTransitionProxy_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((parameter: TabContentTransitionProxy) => void))
    let parameter: TabContentTransitionProxy = (thisDeserializer.readTabContentTransitionProxy() as TabContentTransitionProxy)
    _call(parameter)
}
export function deserializeAndCallCallback_TerminationInfo_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((parameter: TerminationInfo) => void))
    let parameter: TerminationInfo = thisDeserializer.readTerminationInfo()
    _call(parameter)
}
export function deserializeAndCallCallback_TextPickerResult_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((value: TextPickerResult) => void))
    let value: TextPickerResult = thisDeserializer.readTextPickerResult()
    _call(value)
}
export function deserializeAndCallCallback_TextRange_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((parameter: TextRange) => void))
    let parameter: TextRange = thisDeserializer.readTextRange()
    _call(parameter)
}
export function deserializeAndCallCallback_TimePickerResult_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((value: TimePickerResult) => void))
    let value: TimePickerResult = thisDeserializer.readTimePickerResult()
    _call(value)
}
export function deserializeAndCallCallback_TouchEvent_HitTestMode(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((parameter: TouchEvent) => HitTestMode))
    let parameter: TouchEvent = (thisDeserializer.readTouchEvent() as TouchEvent)
    let _continuation: ((value: HitTestMode) => void) = thisDeserializer.readCallback_HitTestMode_Void(true)
    const _callResult = _call(parameter)
    _continuation(_callResult)
}
export function deserializeAndCallCallback_TouchEvent_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((event: TouchEvent) => void))
    let event: TouchEvent = (thisDeserializer.readTouchEvent() as TouchEvent)
    _call(event)
}
export function deserializeAndCallCallback_TouchResult_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((value: TouchResult) => void))
    let value: TouchResult = thisDeserializer.readTouchResult()
    _call(value)
}
export function deserializeAndCallCallback_Tuple_Number_Number_Number_Number_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((value: [ number, number, number, number ]) => void))
    const value_buf_value0: number = (thisDeserializer.readNumber() as number)
    const value_buf_value1: number = (thisDeserializer.readNumber() as number)
    const value_buf_value2: number = (thisDeserializer.readNumber() as number)
    const value_buf_value3: number = (thisDeserializer.readNumber() as number)
    let value: [ number, number, number, number ] = ([value_buf_value0, value_buf_value1, value_buf_value2, value_buf_value3] as [ number, number, number, number ])
    _call(value)
}
export function deserializeAndCallCallback_Tuple_Number_Number_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((value: [ number, number ]) => void))
    const value_buf_value0: number = (thisDeserializer.readNumber() as number)
    const value_buf_value1: number = (thisDeserializer.readNumber() as number)
    let value: [ number, number ] = ([value_buf_value0, value_buf_value1] as [ number, number ])
    _call(value)
}
export function deserializeAndCallCallback_Type_ImageAttribute_onComplete_callback_event_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((event?: { width: number, height: number, componentWidth: number, componentHeight: number, loadingStatus: number, contentWidth: number, contentHeight: number, contentOffsetX: number, contentOffsetY: number }) => void))
    const event_buf_runtimeType = (thisDeserializer.readInt8() as int32)
    let event_buf: { width: number, height: number, componentWidth: number, componentHeight: number, loadingStatus: number, contentWidth: number, contentHeight: number, contentOffsetX: number, contentOffsetY: number } | undefined|undefined 
    if ((RuntimeType.UNDEFINED) != (event_buf_runtimeType))
    {
        const event_buf__width: number = (thisDeserializer.readNumber() as number)
        const event_buf__height: number = (thisDeserializer.readNumber() as number)
        const event_buf__componentWidth: number = (thisDeserializer.readNumber() as number)
        const event_buf__componentHeight: number = (thisDeserializer.readNumber() as number)
        const event_buf__loadingStatus: number = (thisDeserializer.readNumber() as number)
        const event_buf__contentWidth: number = (thisDeserializer.readNumber() as number)
        const event_buf__contentHeight: number = (thisDeserializer.readNumber() as number)
        const event_buf__contentOffsetX: number = (thisDeserializer.readNumber() as number)
        const event_buf__contentOffsetY: number = (thisDeserializer.readNumber() as number)
        event_buf = ({width: event_buf__width, height: event_buf__height, componentWidth: event_buf__componentWidth, componentHeight: event_buf__componentHeight, loadingStatus: event_buf__loadingStatus, contentWidth: event_buf__contentWidth, contentHeight: event_buf__contentHeight, contentOffsetX: event_buf__contentOffsetX, contentOffsetY: event_buf__contentOffsetY} as { width: number, height: number, componentWidth: number, componentHeight: number, loadingStatus: number, contentWidth: number, contentHeight: number, contentOffsetX: number, contentOffsetY: number })
    }
    let event: { width: number, height: number, componentWidth: number, componentHeight: number, loadingStatus: number, contentWidth: number, contentHeight: number, contentOffsetX: number, contentOffsetY: number } | undefined|undefined = event_buf
    _call(event)
}
export function deserializeAndCallCallback_UIExtensionProxy_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((parameter: UIExtensionProxy) => void))
    let parameter: UIExtensionProxy = (thisDeserializer.readUIExtensionProxy() as UIExtensionProxy)
    _call(parameter)
}
export function deserializeAndCallCallback_Union_CustomBuilder_DragItemInfo_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((value: CustomBuilder | DragItemInfo) => void))
    const value_buf_selector: number = thisDeserializer.readInt8()
    let value_buf: CustomBuilder | DragItemInfo | undefined|undefined 
    if (value_buf_selector == 0) {
        value_buf = CallbackTransformer.transformToCustomBuilder(thisDeserializer.readCustomNodeBuilder())
    }
    else if (value_buf_selector == 1) {
        value_buf = thisDeserializer.readDragItemInfo()
    }
    else {
        throw new Error("One of the branches for value_buf has to be chosen through deserialisation.")
    }
    let value: CustomBuilder | DragItemInfo = (value_buf as CustomBuilder | DragItemInfo)
    _call(value)
}
export function deserializeAndCallCallback_Union_Number_Array_Number_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((selected: number | Array<number>) => void))
    const selected_buf_selector: number = thisDeserializer.readInt8()
    let selected_buf: number | Array<number> | undefined|undefined 
    if (selected_buf_selector == 0) {
        selected_buf = (thisDeserializer.readNumber() as number)
    }
    else if (selected_buf_selector == 1) {
        const selected_buf_u_length: int32 = thisDeserializer.readInt32()
        let selected_buf_u: Array<number> = new Array<number>(selected_buf_u_length)
        for (let selected_buf_u_i = 0; selected_buf_u_i < selected_buf_u_length; selected_buf_u_i++) {
            selected_buf_u[selected_buf_u_i] = (thisDeserializer.readNumber() as number)
        }
        selected_buf = selected_buf_u
    }
    else {
        throw new Error("One of the branches for selected_buf has to be chosen through deserialisation.")
    }
    let selected: number | Array<number> = (selected_buf as number | Array<number>)
    _call(selected)
}
export function deserializeAndCallCallback_Union_Number_Resource_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((selected: number | Resource) => void))
    const selected_buf_selector: number = thisDeserializer.readInt8()
    let selected_buf: number | Resource | undefined|undefined 
    if (selected_buf_selector == 0) {
        selected_buf = (thisDeserializer.readNumber() as number)
    }
    else if (selected_buf_selector == 1) {
        selected_buf = thisDeserializer.readResource()
    }
    else {
        throw new Error("One of the branches for selected_buf has to be chosen through deserialisation.")
    }
    let selected: number | Resource = (selected_buf as number | Resource)
    _call(selected)
}
export function deserializeAndCallCallback_Union_String_Array_String_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((value: string | Array<string>) => void))
    const value_buf_selector: number = thisDeserializer.readInt8()
    let value_buf: string | Array<string> | undefined|undefined 
    if (value_buf_selector == 0) {
        value_buf = (thisDeserializer.readString() as string)
    }
    else if (value_buf_selector == 1) {
        const value_buf_u_length: int32 = thisDeserializer.readInt32()
        let value_buf_u: Array<string> = new Array<string>(value_buf_u_length)
        for (let value_buf_u_i = 0; value_buf_u_i < value_buf_u_length; value_buf_u_i++) {
            value_buf_u[value_buf_u_i] = (thisDeserializer.readString() as string)
        }
        value_buf = value_buf_u
    }
    else {
        throw new Error("One of the branches for value_buf has to be chosen through deserialisation.")
    }
    let value: string | Array<string> = (value_buf as string | Array<string>)
    _call(value)
}
export function deserializeAndCallCallback_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as (() => void))
    _call()
}
export function deserializeAndCallCallback_WebKeyboardOptions_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((value: WebKeyboardOptions) => void))
    let value: WebKeyboardOptions = thisDeserializer.readWebKeyboardOptions()
    _call(value)
}
export function deserializeAndCallCallback_WebResourceResponse_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((value: WebResourceResponse) => void))
    let value: WebResourceResponse = (thisDeserializer.readWebResourceResponse() as WebResourceResponse)
    _call(value)
}
export function deserializeAndCallCallback_WithThemeAttribute_Void(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((value: WithThemeAttribute) => void))
    let value: WithThemeAttribute = thisDeserializer.readWithThemeAttribute()
    _call(value)
}
export function deserializeAndCallContentDidScrollCallback(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ContentDidScrollCallback)
    let selectedIndex: number = (thisDeserializer.readNumber() as number)
    let index: number = (thisDeserializer.readNumber() as number)
    let position: number = (thisDeserializer.readNumber() as number)
    let mainAxisLength: number = (thisDeserializer.readNumber() as number)
    _call(selectedIndex, index, position, mainAxisLength)
}
export function deserializeAndCallCustomNodeBuilder(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as CustomNodeBuilder)
    let parentNode: KPointer = thisDeserializer.readPointer()
    let _continuation: ((value: KPointer) => void) = thisDeserializer.readCallback_Pointer_Void(true)
    const _callResult = _call(parentNode)
    _continuation(_callResult)
}
export function deserializeAndCallEditableTextOnChangeCallback(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as EditableTextOnChangeCallback)
    let value: string = (thisDeserializer.readString() as string)
    const previewText_buf_runtimeType = (thisDeserializer.readInt8() as int32)
    let previewText_buf: PreviewText | undefined|undefined 
    if ((RuntimeType.UNDEFINED) != (previewText_buf_runtimeType))
    {
        previewText_buf = thisDeserializer.readPreviewText()
    }
    let previewText: PreviewText | undefined|undefined = previewText_buf
    _call(value, previewText)
}
export function deserializeAndCallErrorCallback(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ErrorCallback)
    let err: BusinessError = thisDeserializer.readBusinessError()
    _call(err)
}
export function deserializeAndCallGestureRecognizerJudgeBeginCallback(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as GestureRecognizerJudgeBeginCallback)
    let event: BaseGestureEvent = (thisDeserializer.readBaseGestureEvent() as BaseGestureEvent)
    let current: GestureRecognizer = (thisDeserializer.readGestureRecognizer() as GestureRecognizer)
    const recognizers_buf_length: int32 = thisDeserializer.readInt32()
    let recognizers_buf: Array<GestureRecognizer> = new Array<GestureRecognizer>(recognizers_buf_length)
    for (let recognizers_buf_i = 0; recognizers_buf_i < recognizers_buf_length; recognizers_buf_i++) {
        recognizers_buf[recognizers_buf_i] = (thisDeserializer.readGestureRecognizer() as GestureRecognizer)
    }
    let recognizers: Array<GestureRecognizer> = recognizers_buf
    let _continuation: ((value: GestureJudgeResult) => void) = thisDeserializer.readCallback_GestureJudgeResult_Void(true)
    const _callResult = _call(event, current, recognizers)
    _continuation(_callResult)
}
export function deserializeAndCallGetItemMainSizeByIndex(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as GetItemMainSizeByIndex)
    let index: number = (thisDeserializer.readNumber() as number)
    let _continuation: ((index: number) => void) = thisDeserializer.readCallback_Number_Void(true)
    const _callResult = _call(index)
    _continuation(_callResult)
}
export function deserializeAndCallHoverCallback(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as HoverCallback)
    let isHover: boolean = thisDeserializer.readBoolean()
    let event: HoverEvent = (thisDeserializer.readHoverEvent() as HoverEvent)
    _call(isHover, event)
}
export function deserializeAndCallImageCompleteCallback(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ImageCompleteCallback)
    let result: ImageLoadResult = thisDeserializer.readImageLoadResult()
    _call(result)
}
export function deserializeAndCallImageErrorCallback(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ImageErrorCallback)
    let error: ImageError = thisDeserializer.readImageError()
    _call(error)
}
export function deserializeAndCallInterceptionModeCallback(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as InterceptionModeCallback)
    let mode: NavigationMode = (thisDeserializer.readInt32() as NavigationMode)
    _call(mode)
}
export function deserializeAndCallInterceptionShowCallback(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as InterceptionShowCallback)
    const from_buf_selector: number = thisDeserializer.readInt8()
    let from_buf: NavDestinationContext | NavBar | undefined|undefined 
    if (from_buf_selector == 0) {
        from_buf = (thisDeserializer.readNavDestinationContext() as NavDestinationContext)
    }
    else if (from_buf_selector == 1) {
        from_buf = (thisDeserializer.readString() as string)
    }
    else {
        throw new Error("One of the branches for from_buf has to be chosen through deserialisation.")
    }
    let from: NavDestinationContext | NavBar = (from_buf as NavDestinationContext | NavBar)
    const to_buf_selector: number = thisDeserializer.readInt8()
    let to_buf: NavDestinationContext | NavBar | undefined|undefined 
    if (to_buf_selector == 0) {
        to_buf = (thisDeserializer.readNavDestinationContext() as NavDestinationContext)
    }
    else if (to_buf_selector == 1) {
        to_buf = (thisDeserializer.readString() as string)
    }
    else {
        throw new Error("One of the branches for to_buf has to be chosen through deserialisation.")
    }
    let to: NavDestinationContext | NavBar = (to_buf as NavDestinationContext | NavBar)
    let operation: NavigationOperation = (thisDeserializer.readInt32() as NavigationOperation)
    let isAnimated: boolean = thisDeserializer.readBoolean()
    _call(from, to, operation, isAnimated)
}
export function deserializeAndCallIsolatedComponentInterface(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as IsolatedComponentInterface)
    let options: IsolatedOptions = thisDeserializer.readIsolatedOptions()
    let _continuation: ((value: IsolatedComponentAttribute) => void) = thisDeserializer.readCallback_IsolatedComponentAttribute_Void(true)
    const _callResult = _call(options)
    _continuation(_callResult)
}
export function deserializeAndCallMenuOnAppearCallback(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as MenuOnAppearCallback)
    let start: number = (thisDeserializer.readNumber() as number)
    let end: number = (thisDeserializer.readNumber() as number)
    _call(start, end)
}
export function deserializeAndCallNavExtender_OnUpdateStack(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as NavExtender_OnUpdateStack)
    _call()
}
export function deserializeAndCallOnAdsBlockedCallback(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as OnAdsBlockedCallback)
    let details: AdsBlockedDetails = thisDeserializer.readAdsBlockedDetails()
    _call(details)
}
export function deserializeAndCallOnAlphabetIndexerPopupSelectCallback(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as OnAlphabetIndexerPopupSelectCallback)
    let index: number = (thisDeserializer.readNumber() as number)
    _call(index)
}
export function deserializeAndCallOnAlphabetIndexerRequestPopupDataCallback(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as OnAlphabetIndexerRequestPopupDataCallback)
    let index: number = (thisDeserializer.readNumber() as number)
    let _continuation: ((value: Array<string>) => void) = thisDeserializer.readCallback_Array_String_Void(true)
    const _callResult = _call(index)
    _continuation(_callResult)
}
export function deserializeAndCallOnAlphabetIndexerSelectCallback(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as OnAlphabetIndexerSelectCallback)
    let index: number = (thisDeserializer.readNumber() as number)
    _call(index)
}
export function deserializeAndCallOnCheckboxChangeCallback(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as OnCheckboxChangeCallback)
    let value: boolean = thisDeserializer.readBoolean()
    _call(value)
}
export function deserializeAndCallOnCheckboxGroupChangeCallback(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as OnCheckboxGroupChangeCallback)
    let value: CheckboxGroupResult = thisDeserializer.readCheckboxGroupResult()
    _call(value)
}
export function deserializeAndCallOnContentScrollCallback(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as OnContentScrollCallback)
    let totalOffsetX: number = (thisDeserializer.readNumber() as number)
    let totalOffsetY: number = (thisDeserializer.readNumber() as number)
    _call(totalOffsetX, totalOffsetY)
}
export function deserializeAndCallOnContextMenuHideCallback(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as OnContextMenuHideCallback)
    _call()
}
export function deserializeAndCallOnDidChangeCallback(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as OnDidChangeCallback)
    let rangeBefore: TextRange = thisDeserializer.readTextRange()
    let rangeAfter: TextRange = thisDeserializer.readTextRange()
    _call(rangeBefore, rangeAfter)
}
export function deserializeAndCallOnFirstMeaningfulPaintCallback(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as OnFirstMeaningfulPaintCallback)
    let firstMeaningfulPaint: FirstMeaningfulPaint = thisDeserializer.readFirstMeaningfulPaint()
    _call(firstMeaningfulPaint)
}
export function deserializeAndCallOnFoldStatusChangeCallback(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as OnFoldStatusChangeCallback)
    let event: OnFoldStatusChangeInfo = thisDeserializer.readOnFoldStatusChangeInfo()
    _call(event)
}
export function deserializeAndCallOnFullScreenEnterCallback(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as OnFullScreenEnterCallback)
    let event: FullScreenEnterEvent = thisDeserializer.readFullScreenEnterEvent()
    _call(event)
}
export function deserializeAndCallOnHoverStatusChangeCallback(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as OnHoverStatusChangeCallback)
    let param: HoverEventParam = thisDeserializer.readHoverEventParam()
    _call(param)
}
export function deserializeAndCallOnIntelligentTrackingPreventionCallback(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as OnIntelligentTrackingPreventionCallback)
    let details: IntelligentTrackingPreventionDetails = thisDeserializer.readIntelligentTrackingPreventionDetails()
    _call(details)
}
export function deserializeAndCallonItemDragStart_event_type(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((event: ItemDragInfo, itemIndex: number) => CustomBuilder))
    let event: ItemDragInfo = thisDeserializer.readItemDragInfo()
    let itemIndex: number = (thisDeserializer.readNumber() as number)
    let _continuation: ((value: CustomBuilder) => void) = thisDeserializer.readCallback_CustomBuilder_Void(true)
    const _callResult = _call(event, itemIndex)
    _continuation(_callResult)
}
export function deserializeAndCallOnLargestContentfulPaintCallback(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as OnLargestContentfulPaintCallback)
    let largestContentfulPaint: LargestContentfulPaint = thisDeserializer.readLargestContentfulPaint()
    _call(largestContentfulPaint)
}
export function deserializeAndCallOnLinearIndicatorChangeCallback(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as OnLinearIndicatorChangeCallback)
    let index: number = (thisDeserializer.readNumber() as number)
    let progress: number = (thisDeserializer.readNumber() as number)
    _call(index, progress)
}
export function deserializeAndCallOnMoveHandler(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as OnMoveHandler)
    let from: number = (thisDeserializer.readNumber() as number)
    let to: number = (thisDeserializer.readNumber() as number)
    _call(from, to)
}
export function deserializeAndCallOnNativeEmbedVisibilityChangeCallback(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as OnNativeEmbedVisibilityChangeCallback)
    let nativeEmbedVisibilityInfo: NativeEmbedVisibilityInfo = thisDeserializer.readNativeEmbedVisibilityInfo()
    _call(nativeEmbedVisibilityInfo)
}
export function deserializeAndCallOnNativeLoadCallback(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as OnNativeLoadCallback)
    const event_buf_runtimeType = (thisDeserializer.readInt8() as int32)
    let event_buf: Object | undefined|undefined 
    if ((RuntimeType.UNDEFINED) != (event_buf_runtimeType))
    {
        event_buf = (thisDeserializer.readCustomObject("Object") as Object)
    }
    let event: Object | undefined|undefined = event_buf
    _call(event)
}
export function deserializeAndCallOnNavigationEntryCommittedCallback(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as OnNavigationEntryCommittedCallback)
    let loadCommittedDetails: LoadCommittedDetails = thisDeserializer.readLoadCommittedDetails()
    _call(loadCommittedDetails)
}
export function deserializeAndCallOnOverrideUrlLoadingCallback(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as OnOverrideUrlLoadingCallback)
    let webResourceRequest: WebResourceRequest = (thisDeserializer.readWebResourceRequest() as WebResourceRequest)
    let _continuation: ((parameter: boolean) => void) = thisDeserializer.readCallback_Boolean_Void(true)
    const _callResult = _call(webResourceRequest)
    _continuation(_callResult)
}
export function deserializeAndCallOnPasteCallback(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as OnPasteCallback)
    let content: string = (thisDeserializer.readString() as string)
    let event: PasteEvent = thisDeserializer.readPasteEvent()
    _call(content, event)
}
export function deserializeAndCallOnRenderProcessNotRespondingCallback(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as OnRenderProcessNotRespondingCallback)
    let data: RenderProcessNotRespondingData = thisDeserializer.readRenderProcessNotRespondingData()
    _call(data)
}
export function deserializeAndCallOnRenderProcessRespondingCallback(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as OnRenderProcessRespondingCallback)
    _call()
}
export function deserializeAndCallOnSafeBrowsingCheckResultCallback(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as OnSafeBrowsingCheckResultCallback)
    let threatType: ThreatType = (thisDeserializer.readInt32() as ThreatType)
    _call(threatType)
}
export function deserializeAndCallOnScrollCallback(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as OnScrollCallback)
    let scrollOffset: number = (thisDeserializer.readNumber() as number)
    let scrollState: ScrollState = (thisDeserializer.readInt32() as ScrollState)
    _call(scrollOffset, scrollState)
}
export function deserializeAndCallOnWillScrollCallback(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as OnWillScrollCallback)
    let scrollOffset: number = (thisDeserializer.readNumber() as number)
    let scrollState: ScrollState = (thisDeserializer.readInt32() as ScrollState)
    let scrollSource: ScrollSource = (thisDeserializer.readInt32() as ScrollSource)
    let _continuation: ((value: ScrollResult) => void) = thisDeserializer.readCallback_ScrollResult_Void(true)
    const _callResult = _call(scrollOffset, scrollState, scrollSource)
    _continuation(_callResult)
}
export function deserializeAndCallOnScrollEdgeCallback(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as OnScrollEdgeCallback)
    let side: Edge = (thisDeserializer.readInt32() as Edge)
    _call(side)
}
export function deserializeAndCallOnScrollFrameBeginCallback(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as OnScrollFrameBeginCallback)
    let offset: number = (thisDeserializer.readNumber() as number)
    let state: ScrollState = (thisDeserializer.readInt32() as ScrollState)
    let _continuation: ((value: OnScrollFrameBeginHandlerResult) => void) = thisDeserializer.readCallback_OnScrollFrameBeginHandlerResult_Void(true)
    const _callResult = _call(offset, state)
    _continuation(_callResult)
}
export function deserializeAndCallOnScrollVisibleContentChangeCallback(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as OnScrollVisibleContentChangeCallback)
    let start: VisibleListContentInfo = thisDeserializer.readVisibleListContentInfo()
    let end: VisibleListContentInfo = thisDeserializer.readVisibleListContentInfo()
    _call(start, end)
}
export function deserializeAndCallOnSslErrorEventCallback(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as OnSslErrorEventCallback)
    let sslErrorEvent: SslErrorEvent = thisDeserializer.readSslErrorEvent()
    _call(sslErrorEvent)
}
export function deserializeAndCallOnSubmitCallback(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as OnSubmitCallback)
    let enterKey: EnterKeyType = (thisDeserializer.readInt32() as EnterKeyType)
    let event: SubmitEvent = (thisDeserializer.readSubmitEvent() as SubmitEvent)
    _call(enterKey, event)
}
export function deserializeAndCallOnSwiperAnimationEndCallback(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as OnSwiperAnimationEndCallback)
    let index: number = (thisDeserializer.readNumber() as number)
    let extraInfo: SwiperAnimationEvent = thisDeserializer.readSwiperAnimationEvent()
    _call(index, extraInfo)
}
export function deserializeAndCallOnSwiperAnimationStartCallback(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as OnSwiperAnimationStartCallback)
    let index: number = (thisDeserializer.readNumber() as number)
    let targetIndex: number = (thisDeserializer.readNumber() as number)
    let extraInfo: SwiperAnimationEvent = thisDeserializer.readSwiperAnimationEvent()
    _call(index, targetIndex, extraInfo)
}
export function deserializeAndCallOnSwiperGestureSwipeCallback(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as OnSwiperGestureSwipeCallback)
    let index: number = (thisDeserializer.readNumber() as number)
    let extraInfo: SwiperAnimationEvent = thisDeserializer.readSwiperAnimationEvent()
    _call(index, extraInfo)
}
export function deserializeAndCallOnTabsAnimationEndCallback(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as OnTabsAnimationEndCallback)
    let index: number = (thisDeserializer.readNumber() as number)
    let extraInfo: TabsAnimationEvent = thisDeserializer.readTabsAnimationEvent()
    _call(index, extraInfo)
}
export function deserializeAndCallOnTabsAnimationStartCallback(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as OnTabsAnimationStartCallback)
    let index: number = (thisDeserializer.readNumber() as number)
    let targetIndex: number = (thisDeserializer.readNumber() as number)
    let extraInfo: TabsAnimationEvent = thisDeserializer.readTabsAnimationEvent()
    _call(index, targetIndex, extraInfo)
}
export function deserializeAndCallOnTabsContentWillChangeCallback(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as OnTabsContentWillChangeCallback)
    let currentIndex: number = (thisDeserializer.readNumber() as number)
    let comingIndex: number = (thisDeserializer.readNumber() as number)
    let _continuation: ((parameter: boolean) => void) = thisDeserializer.readCallback_Boolean_Void(true)
    const _callResult = _call(currentIndex, comingIndex)
    _continuation(_callResult)
}
export function deserializeAndCallOnTabsGestureSwipeCallback(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as OnTabsGestureSwipeCallback)
    let index: number = (thisDeserializer.readNumber() as number)
    let extraInfo: TabsAnimationEvent = thisDeserializer.readTabsAnimationEvent()
    _call(index, extraInfo)
}
export function deserializeAndCallOnTextSelectionChangeCallback(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as OnTextSelectionChangeCallback)
    let selectionStart: number = (thisDeserializer.readNumber() as number)
    let selectionEnd: number = (thisDeserializer.readNumber() as number)
    _call(selectionStart, selectionEnd)
}
export function deserializeAndCallOnViewportFitChangedCallback(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as OnViewportFitChangedCallback)
    let viewportFit: ViewportFit = (thisDeserializer.readInt32() as ViewportFit)
    _call(viewportFit)
}
export function deserializeAndCallPageTransitionCallback(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as PageTransitionCallback)
    let type: RouteType = (thisDeserializer.readInt32() as RouteType)
    let progress: number = (thisDeserializer.readNumber() as number)
    _call(type, progress)
}
export function deserializeAndCallPasteEventCallback(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as PasteEventCallback)
    const event_buf_runtimeType = (thisDeserializer.readInt8() as int32)
    let event_buf: PasteEvent | undefined|undefined 
    if ((RuntimeType.UNDEFINED) != (event_buf_runtimeType))
    {
        event_buf = thisDeserializer.readPasteEvent()
    }
    let event: PasteEvent | undefined|undefined = event_buf
    _call(event)
}
export function deserializeAndCallPluginErrorCallback(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as PluginErrorCallback)
    let info: PluginErrorData = thisDeserializer.readPluginErrorData()
    _call(info)
}
export function deserializeAndCallScrollOnScrollCallback(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ScrollOnScrollCallback)
    let xOffset: number = (thisDeserializer.readNumber() as number)
    let yOffset: number = (thisDeserializer.readNumber() as number)
    let scrollState: ScrollState = (thisDeserializer.readInt32() as ScrollState)
    _call(xOffset, yOffset, scrollState)
}
export function deserializeAndCallScrollOnWillScrollCallback(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ScrollOnWillScrollCallback)
    let xOffset: number = (thisDeserializer.readNumber() as number)
    let yOffset: number = (thisDeserializer.readNumber() as number)
    let scrollState: ScrollState = (thisDeserializer.readInt32() as ScrollState)
    let scrollSource: ScrollSource = (thisDeserializer.readInt32() as ScrollSource)
    let _continuation: ((value: OffsetResult) => void) = thisDeserializer.readCallback_OffsetResult_Void(true)
    const _callResult = _call(xOffset, yOffset, scrollState, scrollSource)
    _continuation(_callResult)
}
export function deserializeAndCallSearchSubmitCallback(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as SearchSubmitCallback)
    let searchContent: string = (thisDeserializer.readString() as string)
    const event_buf_runtimeType = (thisDeserializer.readInt8() as int32)
    let event_buf: SubmitEvent | undefined|undefined 
    if ((RuntimeType.UNDEFINED) != (event_buf_runtimeType))
    {
        event_buf = (thisDeserializer.readSubmitEvent() as SubmitEvent)
    }
    let event: SubmitEvent | undefined|undefined = event_buf
    _call(searchContent, event)
}
export function deserializeAndCallShouldBuiltInRecognizerParallelWithCallback(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ShouldBuiltInRecognizerParallelWithCallback)
    let current: GestureRecognizer = (thisDeserializer.readGestureRecognizer() as GestureRecognizer)
    const others_buf_length: int32 = thisDeserializer.readInt32()
    let others_buf: Array<GestureRecognizer> = new Array<GestureRecognizer>(others_buf_length)
    for (let others_buf_i = 0; others_buf_i < others_buf_length; others_buf_i++) {
        others_buf[others_buf_i] = (thisDeserializer.readGestureRecognizer() as GestureRecognizer)
    }
    let others: Array<GestureRecognizer> = others_buf
    let _continuation: ((value: GestureRecognizer) => void) = thisDeserializer.readCallback_GestureRecognizer_Void(true)
    const _callResult = _call(current, others)
    _continuation(_callResult)
}
export function deserializeAndCallSizeChangeCallback(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as SizeChangeCallback)
    let oldValue: SizeOptions = thisDeserializer.readSizeOptions()
    let newValue: SizeOptions = thisDeserializer.readSizeOptions()
    _call(oldValue, newValue)
}
export function deserializeAndCallSliderTriggerChangeCallback(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as SliderTriggerChangeCallback)
    let value: number = (thisDeserializer.readNumber() as number)
    let mode: SliderChangeMode = (thisDeserializer.readInt32() as SliderChangeMode)
    _call(value, mode)
}
export function deserializeAndCallSubmitCallback(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as SubmitCallback)
    let enterKey: EnterKeyType = (thisDeserializer.readInt32() as EnterKeyType)
    let event: SubmitEvent = (thisDeserializer.readSubmitEvent() as SubmitEvent)
    _call(enterKey, event)
}
export function deserializeAndCallTabsCustomContentTransitionCallback(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as TabsCustomContentTransitionCallback)
    let from: number = (thisDeserializer.readNumber() as number)
    let to: number = (thisDeserializer.readNumber() as number)
    let _continuation: ((value: TabContentAnimatedTransition | undefined) => void) = thisDeserializer.readCallback_Opt_TabContentAnimatedTransition_Void(true)
    const _callResult = _call(from, to)
    _continuation(_callResult)
}
export function deserializeAndCallTextAreaSubmitCallback(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as TextAreaSubmitCallback)
    let enterKeyType: EnterKeyType = (thisDeserializer.readInt32() as EnterKeyType)
    const event_buf_runtimeType = (thisDeserializer.readInt8() as int32)
    let event_buf: SubmitEvent | undefined|undefined 
    if ((RuntimeType.UNDEFINED) != (event_buf_runtimeType))
    {
        event_buf = (thisDeserializer.readSubmitEvent() as SubmitEvent)
    }
    let event: SubmitEvent | undefined|undefined = event_buf
    _call(enterKeyType, event)
}
export function deserializeAndCallTransitionFinishCallback(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as TransitionFinishCallback)
    let transitionIn: boolean = thisDeserializer.readBoolean()
    _call(transitionIn)
}
export function deserializeAndCallType_NavigationAttribute_customNavContentTransition_delegate(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((from: NavContentInfo, to: NavContentInfo, operation: NavigationOperation) => NavigationAnimatedTransition | undefined))
    let from: NavContentInfo = thisDeserializer.readNavContentInfo()
    let to: NavContentInfo = thisDeserializer.readNavContentInfo()
    let operation: NavigationOperation = (thisDeserializer.readInt32() as NavigationOperation)
    let _continuation: ((value: NavigationAnimatedTransition | undefined) => void) = thisDeserializer.readCallback_Opt_NavigationAnimatedTransition_Void(true)
    const _callResult = _call(from, to, operation)
    _continuation(_callResult)
}
export function deserializeAndCallType_TextPickerAttribute_onChange_callback(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((value: string | Array<string>, index: number | Array<number>) => void))
    const value_buf_selector: number = thisDeserializer.readInt8()
    let value_buf: string | Array<string> | undefined|undefined 
    if (value_buf_selector == 0) {
        value_buf = (thisDeserializer.readString() as string)
    }
    else if (value_buf_selector == 1) {
        const value_buf_u_length: int32 = thisDeserializer.readInt32()
        let value_buf_u: Array<string> = new Array<string>(value_buf_u_length)
        for (let value_buf_u_i = 0; value_buf_u_i < value_buf_u_length; value_buf_u_i++) {
            value_buf_u[value_buf_u_i] = (thisDeserializer.readString() as string)
        }
        value_buf = value_buf_u
    }
    else {
        throw new Error("One of the branches for value_buf has to be chosen through deserialisation.")
    }
    let value: string | Array<string> = (value_buf as string | Array<string>)
    const index_buf_selector: number = thisDeserializer.readInt8()
    let index_buf: number | Array<number> | undefined|undefined 
    if (index_buf_selector == 0) {
        index_buf = (thisDeserializer.readNumber() as number)
    }
    else if (index_buf_selector == 1) {
        const index_buf_u_length: int32 = thisDeserializer.readInt32()
        let index_buf_u: Array<number> = new Array<number>(index_buf_u_length)
        for (let index_buf_u_i = 0; index_buf_u_i < index_buf_u_length; index_buf_u_i++) {
            index_buf_u[index_buf_u_i] = (thisDeserializer.readNumber() as number)
        }
        index_buf = index_buf_u
    }
    else {
        throw new Error("One of the branches for index_buf has to be chosen through deserialisation.")
    }
    let index: number | Array<number> = (index_buf as number | Array<number>)
    _call(value, index)
}
export function deserializeAndCallType_WebAttribute_onFileSelectorShow_callback(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((event?: { callback_: Function, fileSelector: Object }) => void))
    const event_buf_runtimeType = (thisDeserializer.readInt8() as int32)
    let event_buf: { callback_: Function, fileSelector: Object } | undefined|undefined 
    if ((RuntimeType.UNDEFINED) != (event_buf_runtimeType))
    {
        const event_buf__callback_: Function = (thisDeserializer.readFunction() as Function)
        const event_buf__fileSelector: Object = (thisDeserializer.readCustomObject("Object") as Object)
        event_buf = ({callback_: event_buf__callback_, fileSelector: event_buf__fileSelector} as { callback_: Function, fileSelector: Object })
    }
    let event: { callback_: Function, fileSelector: Object } | undefined|undefined = event_buf
    _call(event)
}
export function deserializeAndCallType_WebAttribute_onUrlLoadIntercept_callback(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as ((event?: { data: string | WebResourceRequest }) => boolean))
    const event_buf_runtimeType = (thisDeserializer.readInt8() as int32)
    let event_buf: { data: string | WebResourceRequest } | undefined|undefined 
    if ((RuntimeType.UNDEFINED) != (event_buf_runtimeType))
    {
        const event_buf__data_buf_selector: number = thisDeserializer.readInt8()
        let event_buf__data_buf: string | WebResourceRequest | undefined|undefined 
        if (event_buf__data_buf_selector == 0) {
            event_buf__data_buf = (thisDeserializer.readString() as string)
        }
        else if (event_buf__data_buf_selector == 1) {
            event_buf__data_buf = (thisDeserializer.readWebResourceRequest() as WebResourceRequest)
        }
        else {
            throw new Error("One of the branches for event_buf__data_buf has to be chosen through deserialisation.")
        }
        const event_buf__data: string | WebResourceRequest = (event_buf__data_buf as string | WebResourceRequest)
        event_buf = ({data: event_buf__data} as { data: string | WebResourceRequest })
    }
    let event: { data: string | WebResourceRequest } | undefined|undefined = event_buf
    let _continuation: ((parameter: boolean) => void) = thisDeserializer.readCallback_Boolean_Void(true)
    const _callResult = _call(event)
    _continuation(_callResult)
}
export function deserializeAndCallVisibleAreaChangeCallback(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as VisibleAreaChangeCallback)
    let isExpanding: boolean = thisDeserializer.readBoolean()
    let currentRatio: number = (thisDeserializer.readNumber() as number)
    _call(isExpanding, currentRatio)
}
export function deserializeAndCallVoidCallback(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as VoidCallback)
    _call()
}
export function deserializeAndCallWebKeyboardCallback(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as WebKeyboardCallback)
    let keyboardCallbackInfo: WebKeyboardCallbackInfo = thisDeserializer.readWebKeyboardCallbackInfo()
    let _continuation: ((value: WebKeyboardOptions) => void) = thisDeserializer.readCallback_WebKeyboardOptions_Void(true)
    const _callResult = _call(keyboardCallbackInfo)
    _continuation(_callResult)
}
export function deserializeAndCallWithThemeInterface(thisDeserializer: Deserializer): void {
    const _resourceId: int32 = thisDeserializer.readInt32()
    const _call = (ResourceHolder.instance().get(_resourceId) as WithThemeInterface)
    let options: WithThemeOptions = thisDeserializer.readWithThemeOptions()
    let _continuation: ((value: WithThemeAttribute) => void) = thisDeserializer.readCallback_WithThemeAttribute_Void(true)
    const _callResult = _call(options)
    _continuation(_callResult)
}
export function deserializeAndCallCallback_String_SurfaceRect_Void(thisDeserializer: Deserializer): void {
    const _resourceId : int32 = thisDeserializer.readInt32()
    const _call  = (ResourceHolder.instance().get(_resourceId) as ((surfaceId: string,rect: SurfaceRect) => void))
    let surfaceId : string = (thisDeserializer.readString() as string)
    let rect : SurfaceRect = thisDeserializer.readSurfaceRect()
    _call(surfaceId, rect)
}
export function deserializeAndCallCallback(thisDeserializer: Deserializer): void {
    const kind: int32 = thisDeserializer.readInt32()
    switch (kind) {
        case 589030517/*CallbackKind.Kind_AccessibilityCallback*/: return deserializeAndCallAccessibilityCallback(thisDeserializer);
        case 1289587365/*CallbackKind.Kind_AsyncCallback_image_PixelMap_Void*/: return deserializeAndCallAsyncCallback_image_PixelMap_Void(thisDeserializer);
        case -1964292933/*CallbackKind.Kind_ButtonTriggerClickCallback*/: return deserializeAndCallButtonTriggerClickCallback(thisDeserializer);
        case 197193081/*CallbackKind.Kind_Callback_Any_Void*/: return deserializeAndCallCallback_Any_Void(thisDeserializer);
        case -2024393616/*CallbackKind.Kind_Callback_Area_Area_Void*/: return deserializeAndCallCallback_Area_Area_Void(thisDeserializer);
        case 582384234/*CallbackKind.Kind_Callback_Array_Number_Void*/: return deserializeAndCallCallback_Array_Number_Void(thisDeserializer);
        case -440782244/*CallbackKind.Kind_Callback_Array_String_Void*/: return deserializeAndCallCallback_Array_String_Void(thisDeserializer);
        case -547276916/*CallbackKind.Kind_Callback_Array_TouchTestInfo_TouchResult*/: return deserializeAndCallCallback_Array_TouchTestInfo_TouchResult(thisDeserializer);
        case -1541107680/*CallbackKind.Kind_Callback_Boolean*/: return deserializeAndCallCallback_Boolean(thisDeserializer);
        case -916602978/*CallbackKind.Kind_Callback_Boolean_HoverEvent_Void*/: return deserializeAndCallCallback_Boolean_HoverEvent_Void(thisDeserializer);
        case 313269291/*CallbackKind.Kind_Callback_Boolean_Void*/: return deserializeAndCallCallback_Boolean_Void(thisDeserializer);
        case 1074619005/*CallbackKind.Kind_Callback_CalendarRequestedData_Void*/: return deserializeAndCallCallback_CalendarRequestedData_Void(thisDeserializer);
        case -289198976/*CallbackKind.Kind_Callback_CalendarSelectedDate_Void*/: return deserializeAndCallCallback_CalendarSelectedDate_Void(thisDeserializer);
        case -1189087745/*CallbackKind.Kind_Callback_ClickEvent_LocationButtonOnClickResult_Void*/: return deserializeAndCallCallback_ClickEvent_LocationButtonOnClickResult_Void(thisDeserializer);
        case 659292561/*CallbackKind.Kind_Callback_ClickEvent_PasteButtonOnClickResult_Void*/: return deserializeAndCallCallback_ClickEvent_PasteButtonOnClickResult_Void(thisDeserializer);
        case 846787331/*CallbackKind.Kind_Callback_ClickEvent_SaveButtonOnClickResult_Void*/: return deserializeAndCallCallback_ClickEvent_SaveButtonOnClickResult_Void(thisDeserializer);
        case 1097178637/*CallbackKind.Kind_Callback_ClickEvent_Void*/: return deserializeAndCallCallback_ClickEvent_Void(thisDeserializer);
        case -1270343661/*CallbackKind.Kind_Callback_ComputedBarAttribute_Void*/: return deserializeAndCallCallback_ComputedBarAttribute_Void(thisDeserializer);
        case -120437466/*CallbackKind.Kind_Callback_CopyEvent_Void*/: return deserializeAndCallCallback_CopyEvent_Void(thisDeserializer);
        case -721106019/*CallbackKind.Kind_Callback_CustomBuilder_Void*/: return deserializeAndCallCallback_CustomBuilder_Void(thisDeserializer);
        case -1875695871/*CallbackKind.Kind_Callback_CutEvent_Void*/: return deserializeAndCallCallback_CutEvent_Void(thisDeserializer);
        case 1405382363/*CallbackKind.Kind_Callback_Date_Void*/: return deserializeAndCallCallback_Date_Void(thisDeserializer);
        case 1280920532/*CallbackKind.Kind_Callback_DatePickerResult_Void*/: return deserializeAndCallCallback_DatePickerResult_Void(thisDeserializer);
        case -1357792883/*CallbackKind.Kind_Callback_DeleteValue_Boolean*/: return deserializeAndCallCallback_DeleteValue_Boolean(thisDeserializer);
        case -126251459/*CallbackKind.Kind_Callback_DeleteValue_Void*/: return deserializeAndCallCallback_DeleteValue_Void(thisDeserializer);
        case -1283506641/*CallbackKind.Kind_Callback_DismissContentCoverAction_Void*/: return deserializeAndCallCallback_DismissContentCoverAction_Void(thisDeserializer);
        case -2095828093/*CallbackKind.Kind_Callback_DismissDialogAction_Void*/: return deserializeAndCallCallback_DismissDialogAction_Void(thisDeserializer);
        case -2004166751/*CallbackKind.Kind_Callback_DismissPopupAction_Void*/: return deserializeAndCallCallback_DismissPopupAction_Void(thisDeserializer);
        case 889549796/*CallbackKind.Kind_Callback_DismissSheetAction_Void*/: return deserializeAndCallCallback_DismissSheetAction_Void(thisDeserializer);
        case 480978023/*CallbackKind.Kind_Callback_DragEvent_String_Union_CustomBuilder_DragItemInfo*/: return deserializeAndCallCallback_DragEvent_String_Union_CustomBuilder_DragItemInfo(thisDeserializer);
        case -17167687/*CallbackKind.Kind_Callback_DragEvent_String_Void*/: return deserializeAndCallCallback_DragEvent_String_Void(thisDeserializer);
        case -1802605016/*CallbackKind.Kind_Callback_EnterKeyType_Void*/: return deserializeAndCallCallback_EnterKeyType_Void(thisDeserializer);
        case -733525640/*CallbackKind.Kind_Callback_Extender_OnFinish*/: return deserializeAndCallCallback_Extender_OnFinish(thisDeserializer);
        case 1264236374/*CallbackKind.Kind_Callback_Extender_OnProgress*/: return deserializeAndCallCallback_Extender_OnProgress(thisDeserializer);
        case 758395742/*CallbackKind.Kind_Callback_FormCallbackInfo_Void*/: return deserializeAndCallCallback_FormCallbackInfo_Void(thisDeserializer);
        case 583294398/*CallbackKind.Kind_Callback_FullscreenInfo_Void*/: return deserializeAndCallCallback_FullscreenInfo_Void(thisDeserializer);
        case -1143194492/*CallbackKind.Kind_Callback_GestureEvent_Void*/: return deserializeAndCallCallback_GestureEvent_Void(thisDeserializer);
        case 1319043556/*CallbackKind.Kind_Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult*/: return deserializeAndCallCallback_GestureInfo_BaseGestureEvent_GestureJudgeResult(thisDeserializer);
        case -684588584/*CallbackKind.Kind_Callback_GestureJudgeResult_Void*/: return deserializeAndCallCallback_GestureJudgeResult_Void(thisDeserializer);
        case 776202910/*CallbackKind.Kind_Callback_GestureRecognizer_Void*/: return deserializeAndCallCallback_GestureRecognizer_Void(thisDeserializer);
        case -1755111025/*CallbackKind.Kind_Callback_HitTestMode_Void*/: return deserializeAndCallCallback_HitTestMode_Void(thisDeserializer);
        case -383025085/*CallbackKind.Kind_Callback_InsertValue_Boolean*/: return deserializeAndCallCallback_InsertValue_Boolean(thisDeserializer);
        case -1121207885/*CallbackKind.Kind_Callback_InsertValue_Void*/: return deserializeAndCallCallback_InsertValue_Void(thisDeserializer);
        case 719029905/*CallbackKind.Kind_Callback_IsolatedComponentAttribute_Void*/: return deserializeAndCallCallback_IsolatedComponentAttribute_Void(thisDeserializer);
        case -1627362945/*CallbackKind.Kind_Callback_ItemDragInfo_Number_Number_Boolean_Void*/: return deserializeAndCallCallback_ItemDragInfo_Number_Number_Boolean_Void(thisDeserializer);
        case -918805852/*CallbackKind.Kind_Callback_ItemDragInfo_Number_Number_Void*/: return deserializeAndCallCallback_ItemDragInfo_Number_Number_Void(thisDeserializer);
        case 296908152/*CallbackKind.Kind_Callback_ItemDragInfo_Number_Void*/: return deserializeAndCallCallback_ItemDragInfo_Number_Void(thisDeserializer);
        case 137353252/*CallbackKind.Kind_Callback_ItemDragInfo_Void*/: return deserializeAndCallCallback_ItemDragInfo_Void(thisDeserializer);
        case -2061548092/*CallbackKind.Kind_Callback_KeyEvent_Boolean*/: return deserializeAndCallCallback_KeyEvent_Boolean(thisDeserializer);
        case 707696468/*CallbackKind.Kind_Callback_KeyEvent_Void*/: return deserializeAndCallCallback_KeyEvent_Void(thisDeserializer);
        case -1561407084/*CallbackKind.Kind_Callback_Literal_Boolean_isVisible_Void*/: return deserializeAndCallCallback_Literal_Boolean_isVisible_Void(thisDeserializer);
        case 361012115/*CallbackKind.Kind_Callback_Literal_Function_handler_Object_error_Void*/: return deserializeAndCallCallback_Literal_Function_handler_Object_error_Void(thisDeserializer);
        case -582934742/*CallbackKind.Kind_Callback_Literal_Number_code_Want_want_Void*/: return deserializeAndCallCallback_Literal_Number_code_Want_want_Void(thisDeserializer);
        case 1321277443/*CallbackKind.Kind_Callback_Literal_Number_errcode_String_msg_Void*/: return deserializeAndCallCallback_Literal_Number_errcode_String_msg_Void(thisDeserializer);
        case -251706058/*CallbackKind.Kind_Callback_Literal_Number_offsetRemain_Void*/: return deserializeAndCallCallback_Literal_Number_offsetRemain_Void(thisDeserializer);
        case 222742448/*CallbackKind.Kind_Callback_Literal_Object_detail_Boolean*/: return deserializeAndCallCallback_Literal_Object_detail_Boolean(thisDeserializer);
        case -122223466/*CallbackKind.Kind_Callback_Literal_String_plainText_Void*/: return deserializeAndCallCallback_Literal_String_plainText_Void(thisDeserializer);
        case -1382640094/*CallbackKind.Kind_Callback_MouseEvent_Void*/: return deserializeAndCallCallback_MouseEvent_Void(thisDeserializer);
        case 477481563/*CallbackKind.Kind_Callback_NativeEmbedDataInfo_Void*/: return deserializeAndCallCallback_NativeEmbedDataInfo_Void(thisDeserializer);
        case -1090303858/*CallbackKind.Kind_Callback_NativeEmbedTouchInfo_Void*/: return deserializeAndCallCallback_NativeEmbedTouchInfo_Void(thisDeserializer);
        case -1642725259/*CallbackKind.Kind_Callback_NavDestinationContext_Void*/: return deserializeAndCallCallback_NavDestinationContext_Void(thisDeserializer);
        case 960690982/*CallbackKind.Kind_Callback_NavigationMode_Void*/: return deserializeAndCallCallback_NavigationMode_Void(thisDeserializer);
        case 1685437830/*CallbackKind.Kind_Callback_NavigationTitleMode_Void*/: return deserializeAndCallCallback_NavigationTitleMode_Void(thisDeserializer);
        case -1375731066/*CallbackKind.Kind_Callback_NavigationTransitionProxy_Void*/: return deserializeAndCallCallback_NavigationTransitionProxy_Void(thisDeserializer);
        case 1054099324/*CallbackKind.Kind_Callback_Number_Boolean*/: return deserializeAndCallCallback_Number_Boolean(thisDeserializer);
        case -1427334496/*CallbackKind.Kind_Callback_Number_Number_Boolean*/: return deserializeAndCallCallback_Number_Number_Boolean(thisDeserializer);
        case -3987624/*CallbackKind.Kind_Callback_Number_Number_ComputedBarAttribute*/: return deserializeAndCallCallback_Number_Number_ComputedBarAttribute(thisDeserializer);
        case -352942292/*CallbackKind.Kind_Callback_Number_Number_Number_Void*/: return deserializeAndCallCallback_Number_Number_Number_Void(thisDeserializer);
        case 1613628570/*CallbackKind.Kind_Callback_Number_Number_PanelMode_Void*/: return deserializeAndCallCallback_Number_Number_PanelMode_Void(thisDeserializer);
        case 1894574320/*CallbackKind.Kind_Callback_Number_Number_Void*/: return deserializeAndCallCallback_Number_Number_Void(thisDeserializer);
        case 2012829508/*CallbackKind.Kind_Callback_Number_ScrollState_Literal_Number_offsetRemain*/: return deserializeAndCallCallback_Number_ScrollState_Literal_Number_offsetRemain(thisDeserializer);
        case 88697971/*CallbackKind.Kind_Callback_Number_SliderChangeMode_Void*/: return deserializeAndCallCallback_Number_SliderChangeMode_Void(thisDeserializer);
        case 794065478/*CallbackKind.Kind_Callback_Number_String_Void*/: return deserializeAndCallCallback_Number_String_Void(thisDeserializer);
        case 1602877440/*CallbackKind.Kind_Callback_Number_Tuple_Number_Number*/: return deserializeAndCallCallback_Number_Tuple_Number_Number(thisDeserializer);
        case 1618565120/*CallbackKind.Kind_Callback_Number_Tuple_Number_Number_Number_Number*/: return deserializeAndCallCallback_Number_Tuple_Number_Number_Number_Number(thisDeserializer);
        case 36519084/*CallbackKind.Kind_Callback_Number_Void*/: return deserializeAndCallCallback_Number_Void(thisDeserializer);
        case 1295952075/*CallbackKind.Kind_Callback_OffsetResult_Void*/: return deserializeAndCallCallback_OffsetResult_Void(thisDeserializer);
        case 1385252075/*CallbackKind.Kind_Callback_ScrollResult_Void*/: return deserializeAndCallCallback_ScrollResult_Void(thisDeserializer);
        case 806070428/*CallbackKind.Kind_Callback_OnAlertEvent_Boolean*/: return deserializeAndCallCallback_OnAlertEvent_Boolean(thisDeserializer);
        case -1559789631/*CallbackKind.Kind_Callback_OnAudioStateChangedEvent_Void*/: return deserializeAndCallCallback_OnAudioStateChangedEvent_Void(thisDeserializer);
        case -873162122/*CallbackKind.Kind_Callback_OnBeforeUnloadEvent_Boolean*/: return deserializeAndCallCallback_OnBeforeUnloadEvent_Boolean(thisDeserializer);
        case 608991355/*CallbackKind.Kind_Callback_OnClientAuthenticationEvent_Void*/: return deserializeAndCallCallback_OnClientAuthenticationEvent_Void(thisDeserializer);
        case 317864672/*CallbackKind.Kind_Callback_OnConfirmEvent_Boolean*/: return deserializeAndCallCallback_OnConfirmEvent_Boolean(thisDeserializer);
        case 893367077/*CallbackKind.Kind_Callback_OnConsoleEvent_Boolean*/: return deserializeAndCallCallback_OnConsoleEvent_Boolean(thisDeserializer);
        case 332449533/*CallbackKind.Kind_Callback_OnContextMenuShowEvent_Boolean*/: return deserializeAndCallCallback_OnContextMenuShowEvent_Boolean(thisDeserializer);
        case 118631204/*CallbackKind.Kind_Callback_OnDataResubmittedEvent_Void*/: return deserializeAndCallCallback_OnDataResubmittedEvent_Void(thisDeserializer);
        case 1834611702/*CallbackKind.Kind_Callback_OnDownloadStartEvent_Void*/: return deserializeAndCallCallback_OnDownloadStartEvent_Void(thisDeserializer);
        case -1792851375/*CallbackKind.Kind_Callback_OnErrorReceiveEvent_Void*/: return deserializeAndCallCallback_OnErrorReceiveEvent_Void(thisDeserializer);
        case -243916553/*CallbackKind.Kind_Callback_OnFaviconReceivedEvent_Void*/: return deserializeAndCallCallback_OnFaviconReceivedEvent_Void(thisDeserializer);
        case -1852060212/*CallbackKind.Kind_Callback_OnFirstContentfulPaintEvent_Void*/: return deserializeAndCallCallback_OnFirstContentfulPaintEvent_Void(thisDeserializer);
        case -941896815/*CallbackKind.Kind_Callback_OnGeolocationShowEvent_Void*/: return deserializeAndCallCallback_OnGeolocationShowEvent_Void(thisDeserializer);
        case 780282803/*CallbackKind.Kind_Callback_OnHttpAuthRequestEvent_Boolean*/: return deserializeAndCallCallback_OnHttpAuthRequestEvent_Boolean(thisDeserializer);
        case -2066745559/*CallbackKind.Kind_Callback_OnHttpErrorReceiveEvent_Void*/: return deserializeAndCallCallback_OnHttpErrorReceiveEvent_Void(thisDeserializer);
        case 1442698200/*CallbackKind.Kind_Callback_OnInterceptRequestEvent_WebResourceResponse*/: return deserializeAndCallCallback_OnInterceptRequestEvent_WebResourceResponse(thisDeserializer);
        case 1231444306/*CallbackKind.Kind_Callback_OnLoadInterceptEvent_Boolean*/: return deserializeAndCallCallback_OnLoadInterceptEvent_Boolean(thisDeserializer);
        case -860386431/*CallbackKind.Kind_Callback_OnOverScrollEvent_Void*/: return deserializeAndCallCallback_OnOverScrollEvent_Void(thisDeserializer);
        case -2040193994/*CallbackKind.Kind_Callback_OnPageBeginEvent_Void*/: return deserializeAndCallCallback_OnPageBeginEvent_Void(thisDeserializer);
        case -130135362/*CallbackKind.Kind_Callback_OnPageEndEvent_Void*/: return deserializeAndCallCallback_OnPageEndEvent_Void(thisDeserializer);
        case 1805946367/*CallbackKind.Kind_Callback_OnPageVisibleEvent_Void*/: return deserializeAndCallCallback_OnPageVisibleEvent_Void(thisDeserializer);
        case 529980696/*CallbackKind.Kind_Callback_OnPermissionRequestEvent_Void*/: return deserializeAndCallCallback_OnPermissionRequestEvent_Void(thisDeserializer);
        case 1018740377/*CallbackKind.Kind_Callback_OnProgressChangeEvent_Void*/: return deserializeAndCallCallback_OnProgressChangeEvent_Void(thisDeserializer);
        case -1826742986/*CallbackKind.Kind_Callback_OnPromptEvent_Boolean*/: return deserializeAndCallCallback_OnPromptEvent_Boolean(thisDeserializer);
        case 1978364344/*CallbackKind.Kind_Callback_OnRefreshAccessedHistoryEvent_Void*/: return deserializeAndCallCallback_OnRefreshAccessedHistoryEvent_Void(thisDeserializer);
        case -1413785559/*CallbackKind.Kind_Callback_OnRenderExitedEvent_Void*/: return deserializeAndCallCallback_OnRenderExitedEvent_Void(thisDeserializer);
        case 793995118/*CallbackKind.Kind_Callback_OnResourceLoadEvent_Void*/: return deserializeAndCallCallback_OnResourceLoadEvent_Void(thisDeserializer);
        case -1782102148/*CallbackKind.Kind_Callback_OnScaleChangeEvent_Void*/: return deserializeAndCallCallback_OnScaleChangeEvent_Void(thisDeserializer);
        case -1972321573/*CallbackKind.Kind_Callback_OnScreenCaptureRequestEvent_Void*/: return deserializeAndCallCallback_OnScreenCaptureRequestEvent_Void(thisDeserializer);
        case -172908881/*CallbackKind.Kind_Callback_OnScrollEvent_Void*/: return deserializeAndCallCallback_OnScrollEvent_Void(thisDeserializer);
        case 1637092936/*CallbackKind.Kind_Callback_OnScrollFrameBeginHandlerResult_Void*/: return deserializeAndCallCallback_OnScrollFrameBeginHandlerResult_Void(thisDeserializer);
        case -1495570/*CallbackKind.Kind_Callback_OnSearchResultReceiveEvent_Void*/: return deserializeAndCallCallback_OnSearchResultReceiveEvent_Void(thisDeserializer);
        case -636069598/*CallbackKind.Kind_Callback_OnShowFileSelectorEvent_Boolean*/: return deserializeAndCallCallback_OnShowFileSelectorEvent_Boolean(thisDeserializer);
        case 1624791665/*CallbackKind.Kind_Callback_OnSslErrorEventReceiveEvent_Void*/: return deserializeAndCallCallback_OnSslErrorEventReceiveEvent_Void(thisDeserializer);
        case -318085495/*CallbackKind.Kind_Callback_OnTitleReceiveEvent_Void*/: return deserializeAndCallCallback_OnTitleReceiveEvent_Void(thisDeserializer);
        case 1657893064/*CallbackKind.Kind_Callback_OnTouchIconUrlReceivedEvent_Void*/: return deserializeAndCallCallback_OnTouchIconUrlReceivedEvent_Void(thisDeserializer);
        case -2052382574/*CallbackKind.Kind_Callback_OnWindowNewEvent_Void*/: return deserializeAndCallCallback_OnWindowNewEvent_Void(thisDeserializer);
        case -543655128/*CallbackKind.Kind_Callback_Opt_Array_String_Void*/: return deserializeAndCallCallback_Opt_Array_String_Void(thisDeserializer);
        case -2035339519/*CallbackKind.Kind_Callback_Opt_NavigationAnimatedTransition_Void*/: return deserializeAndCallCallback_Opt_NavigationAnimatedTransition_Void(thisDeserializer);
        case -756319131/*CallbackKind.Kind_Callback_Opt_StyledString_Opt_Array_String_Void*/: return deserializeAndCallCallback_Opt_StyledString_Opt_Array_String_Void(thisDeserializer);
        case -143931627/*CallbackKind.Kind_Callback_Opt_TabContentAnimatedTransition_Void*/: return deserializeAndCallCallback_Opt_TabContentAnimatedTransition_Void(thisDeserializer);
        case 388680218/*CallbackKind.Kind_Callback_PanelMode_Void*/: return deserializeAndCallCallback_PanelMode_Void(thisDeserializer);
        case -2058966418/*CallbackKind.Kind_Callback_PlaybackInfo_Void*/: return deserializeAndCallCallback_PlaybackInfo_Void(thisDeserializer);
        case 721562324/*CallbackKind.Kind_Callback_Pointer_Void*/: return deserializeAndCallCallback_Pointer_Void(thisDeserializer);
        case 624053870/*CallbackKind.Kind_Callback_PopInfo_Void*/: return deserializeAndCallCallback_PopInfo_Void(thisDeserializer);
        case 463894668/*CallbackKind.Kind_Callback_PreDragStatus_Void*/: return deserializeAndCallCallback_PreDragStatus_Void(thisDeserializer);
        case 1300890372/*CallbackKind.Kind_Callback_PreparedInfo_Void*/: return deserializeAndCallCallback_PreparedInfo_Void(thisDeserializer);
        case 797834474/*CallbackKind.Kind_Callback_RangeUpdate*/: return deserializeAndCallCallback_RangeUpdate(thisDeserializer);
        case 934309126/*CallbackKind.Kind_Callback_RefreshStatus_Void*/: return deserializeAndCallCallback_RefreshStatus_Void(thisDeserializer);
        case 188373904/*CallbackKind.Kind_Callback_ResourceStr_Void*/: return deserializeAndCallCallback_ResourceStr_Void(thisDeserializer);
        case 1465860515/*CallbackKind.Kind_Callback_RichEditorChangeValue_Boolean*/: return deserializeAndCallCallback_RichEditorChangeValue_Boolean(thisDeserializer);
        case 667698748/*CallbackKind.Kind_Callback_RichEditorDeleteValue_Boolean*/: return deserializeAndCallCallback_RichEditorDeleteValue_Boolean(thisDeserializer);
        case -319221262/*CallbackKind.Kind_Callback_RichEditorInsertValue_Boolean*/: return deserializeAndCallCallback_RichEditorInsertValue_Boolean(thisDeserializer);
        case -62253375/*CallbackKind.Kind_Callback_RichEditorRange_Void*/: return deserializeAndCallCallback_RichEditorRange_Void(thisDeserializer);
        case -963852514/*CallbackKind.Kind_Callback_RichEditorSelection_Void*/: return deserializeAndCallCallback_RichEditorSelection_Void(thisDeserializer);
        case 1980824326/*CallbackKind.Kind_Callback_RichEditorTextSpanResult_Void*/: return deserializeAndCallCallback_RichEditorTextSpanResult_Void(thisDeserializer);
        case 22609082/*CallbackKind.Kind_Callback_SheetDismiss_Void*/: return deserializeAndCallCallback_SheetDismiss_Void(thisDeserializer);
        case -224451112/*CallbackKind.Kind_Callback_SheetType_Void*/: return deserializeAndCallCallback_SheetType_Void(thisDeserializer);
        case 1536231691/*CallbackKind.Kind_Callback_SpringBackAction_Void*/: return deserializeAndCallCallback_SpringBackAction_Void(thisDeserializer);
        case -879490874/*CallbackKind.Kind_Callback_String_Number_Void*/: return deserializeAndCallCallback_String_Number_Void(thisDeserializer);
        case -683652998/*CallbackKind.Kind_Callback_String_PasteEvent_Void*/: return deserializeAndCallCallback_String_PasteEvent_Void(thisDeserializer);
        case -1493806035/*CallbackKind.Kind_Callback_String_Unknown_Void*/: return deserializeAndCallCallback_String_Unknown_Void(thisDeserializer);
        case 814634522/*CallbackKind.Kind_Callback_String_Void*/: return deserializeAndCallCallback_String_Void(thisDeserializer);
        case 2116745428/*CallbackKind.Kind_Callback_StyledStringChangeValue_Boolean*/: return deserializeAndCallCallback_StyledStringChangeValue_Boolean(thisDeserializer);
        case -301561698/*CallbackKind.Kind_Callback_SwipeActionState_Void*/: return deserializeAndCallCallback_SwipeActionState_Void(thisDeserializer);
        case -416053361/*CallbackKind.Kind_Callback_SwiperContentTransitionProxy_Void*/: return deserializeAndCallCallback_SwiperContentTransitionProxy_Void(thisDeserializer);
        case -1223938478/*CallbackKind.Kind_Callback_TabContentTransitionProxy_Void*/: return deserializeAndCallCallback_TabContentTransitionProxy_Void(thisDeserializer);
        case 691098197/*CallbackKind.Kind_Callback_TerminationInfo_Void*/: return deserializeAndCallCallback_TerminationInfo_Void(thisDeserializer);
        case 1290504509/*CallbackKind.Kind_Callback_TextPickerResult_Void*/: return deserializeAndCallCallback_TextPickerResult_Void(thisDeserializer);
        case 811915501/*CallbackKind.Kind_Callback_TextRange_Void*/: return deserializeAndCallCallback_TextRange_Void(thisDeserializer);
        case 1557859605/*CallbackKind.Kind_Callback_TimePickerResult_Void*/: return deserializeAndCallCallback_TimePickerResult_Void(thisDeserializer);
        case -274419246/*CallbackKind.Kind_Callback_TouchEvent_HitTestMode*/: return deserializeAndCallCallback_TouchEvent_HitTestMode(thisDeserializer);
        case -1676021850/*CallbackKind.Kind_Callback_TouchEvent_Void*/: return deserializeAndCallCallback_TouchEvent_Void(thisDeserializer);
        case 1943507619/*CallbackKind.Kind_Callback_TouchResult_Void*/: return deserializeAndCallCallback_TouchResult_Void(thisDeserializer);
        case 148489367/*CallbackKind.Kind_Callback_Tuple_Number_Number_Number_Number_Void*/: return deserializeAndCallCallback_Tuple_Number_Number_Number_Number_Void(thisDeserializer);
        case -607365481/*CallbackKind.Kind_Callback_Tuple_Number_Number_Void*/: return deserializeAndCallCallback_Tuple_Number_Number_Void(thisDeserializer);
        case -1352745727/*CallbackKind.Kind_Callback_Type_ImageAttribute_onComplete_callback_event_Void*/: return deserializeAndCallCallback_Type_ImageAttribute_onComplete_callback_event_Void(thisDeserializer);
        case -1063506522/*CallbackKind.Kind_Callback_UIExtensionProxy_Void*/: return deserializeAndCallCallback_UIExtensionProxy_Void(thisDeserializer);
        case -620935067/*CallbackKind.Kind_Callback_Union_CustomBuilder_DragItemInfo_Void*/: return deserializeAndCallCallback_Union_CustomBuilder_DragItemInfo_Void(thisDeserializer);
        case -1111620998/*CallbackKind.Kind_Callback_Union_Number_Array_Number_Void*/: return deserializeAndCallCallback_Union_Number_Array_Number_Void(thisDeserializer);
        case -956455499/*CallbackKind.Kind_Callback_Union_Number_Resource_Void*/: return deserializeAndCallCallback_Union_Number_Resource_Void(thisDeserializer);
        case -720435526/*CallbackKind.Kind_Callback_Union_String_Array_String_Void*/: return deserializeAndCallCallback_Union_String_Array_String_Void(thisDeserializer);
        case -1867723152/*CallbackKind.Kind_Callback_Void*/: return deserializeAndCallCallback_Void(thisDeserializer);
        case -1376223390/*CallbackKind.Kind_Callback_WebKeyboardOptions_Void*/: return deserializeAndCallCallback_WebKeyboardOptions_Void(thisDeserializer);
        case 831645046/*CallbackKind.Kind_Callback_WebResourceResponse_Void*/: return deserializeAndCallCallback_WebResourceResponse_Void(thisDeserializer);
        case 1436479104/*CallbackKind.Kind_Callback_WithThemeAttribute_Void*/: return deserializeAndCallCallback_WithThemeAttribute_Void(thisDeserializer);
        case 1532328438/*CallbackKind.Kind_ContentDidScrollCallback*/: return deserializeAndCallContentDidScrollCallback(thisDeserializer);
        case 1766817632/*CallbackKind.Kind_CustomNodeBuilder*/: return deserializeAndCallCustomNodeBuilder(thisDeserializer);
        case -1729563209/*CallbackKind.Kind_EditableTextOnChangeCallback*/: return deserializeAndCallEditableTextOnChangeCallback(thisDeserializer);
        case -1936519453/*CallbackKind.Kind_ErrorCallback*/: return deserializeAndCallErrorCallback(thisDeserializer);
        case -2119548940/*CallbackKind.Kind_GestureRecognizerJudgeBeginCallback*/: return deserializeAndCallGestureRecognizerJudgeBeginCallback(thisDeserializer);
        case -2076995110/*CallbackKind.Kind_GetItemMainSizeByIndex*/: return deserializeAndCallGetItemMainSizeByIndex(thisDeserializer);
        case 68560477/*CallbackKind.Kind_HoverCallback*/: return deserializeAndCallHoverCallback(thisDeserializer);
        case -1180567691/*CallbackKind.Kind_ImageCompleteCallback*/: return deserializeAndCallImageCompleteCallback(thisDeserializer);
        case 1906248580/*CallbackKind.Kind_ImageErrorCallback*/: return deserializeAndCallImageErrorCallback(thisDeserializer);
        case 1502213270/*CallbackKind.Kind_InterceptionModeCallback*/: return deserializeAndCallInterceptionModeCallback(thisDeserializer);
        case 1852781814/*CallbackKind.Kind_InterceptionShowCallback*/: return deserializeAndCallInterceptionShowCallback(thisDeserializer);
        case 2139680213/*CallbackKind.Kind_IsolatedComponentInterface*/: return deserializeAndCallIsolatedComponentInterface(thisDeserializer);
        case -614475458/*CallbackKind.Kind_MenuOnAppearCallback*/: return deserializeAndCallMenuOnAppearCallback(thisDeserializer);
        case -588228933/*CallbackKind.Kind_NavExtender_OnUpdateStack*/: return deserializeAndCallNavExtender_OnUpdateStack(thisDeserializer);
        case 1572284740/*CallbackKind.Kind_OnAdsBlockedCallback*/: return deserializeAndCallOnAdsBlockedCallback(thisDeserializer);
        case 726938390/*CallbackKind.Kind_OnAlphabetIndexerPopupSelectCallback*/: return deserializeAndCallOnAlphabetIndexerPopupSelectCallback(thisDeserializer);
        case -1956514817/*CallbackKind.Kind_OnAlphabetIndexerRequestPopupDataCallback*/: return deserializeAndCallOnAlphabetIndexerRequestPopupDataCallback(thisDeserializer);
        case -1189721220/*CallbackKind.Kind_OnAlphabetIndexerSelectCallback*/: return deserializeAndCallOnAlphabetIndexerSelectCallback(thisDeserializer);
        case -1198592337/*CallbackKind.Kind_OnCheckboxChangeCallback*/: return deserializeAndCallOnCheckboxChangeCallback(thisDeserializer);
        case -1053064240/*CallbackKind.Kind_OnCheckboxGroupChangeCallback*/: return deserializeAndCallOnCheckboxGroupChangeCallback(thisDeserializer);
        case -419979106/*CallbackKind.Kind_OnContentScrollCallback*/: return deserializeAndCallOnContentScrollCallback(thisDeserializer);
        case 1788572278/*CallbackKind.Kind_OnContextMenuHideCallback*/: return deserializeAndCallOnContextMenuHideCallback(thisDeserializer);
        case 1648184341/*CallbackKind.Kind_OnDidChangeCallback*/: return deserializeAndCallOnDidChangeCallback(thisDeserializer);
        case 767275770/*CallbackKind.Kind_OnFirstMeaningfulPaintCallback*/: return deserializeAndCallOnFirstMeaningfulPaintCallback(thisDeserializer);
        case 2050387049/*CallbackKind.Kind_OnFoldStatusChangeCallback*/: return deserializeAndCallOnFoldStatusChangeCallback(thisDeserializer);
        case 81230317/*CallbackKind.Kind_OnFullScreenEnterCallback*/: return deserializeAndCallOnFullScreenEnterCallback(thisDeserializer);
        case 9040430/*CallbackKind.Kind_OnHoverStatusChangeCallback*/: return deserializeAndCallOnHoverStatusChangeCallback(thisDeserializer);
        case -1377876844/*CallbackKind.Kind_OnIntelligentTrackingPreventionCallback*/: return deserializeAndCallOnIntelligentTrackingPreventionCallback(thisDeserializer);
        case 1340995650/*CallbackKind.Kind_onItemDragStart_event_type*/: return deserializeAndCallonItemDragStart_event_type(thisDeserializer);
        case 1390640532/*CallbackKind.Kind_OnLargestContentfulPaintCallback*/: return deserializeAndCallOnLargestContentfulPaintCallback(thisDeserializer);
        case -968773856/*CallbackKind.Kind_OnLinearIndicatorChangeCallback*/: return deserializeAndCallOnLinearIndicatorChangeCallback(thisDeserializer);
        case -1200281222/*CallbackKind.Kind_OnMoveHandler*/: return deserializeAndCallOnMoveHandler(thisDeserializer);
        case -1641338704/*CallbackKind.Kind_OnNativeEmbedVisibilityChangeCallback*/: return deserializeAndCallOnNativeEmbedVisibilityChangeCallback(thisDeserializer);
        case -823037763/*CallbackKind.Kind_OnNativeLoadCallback*/: return deserializeAndCallOnNativeLoadCallback(thisDeserializer);
        case -398722176/*CallbackKind.Kind_OnNavigationEntryCommittedCallback*/: return deserializeAndCallOnNavigationEntryCommittedCallback(thisDeserializer);
        case 865258467/*CallbackKind.Kind_OnOverrideUrlLoadingCallback*/: return deserializeAndCallOnOverrideUrlLoadingCallback(thisDeserializer);
        case 1738363337/*CallbackKind.Kind_OnPasteCallback*/: return deserializeAndCallOnPasteCallback(thisDeserializer);
        case 47282303/*CallbackKind.Kind_OnRenderProcessNotRespondingCallback*/: return deserializeAndCallOnRenderProcessNotRespondingCallback(thisDeserializer);
        case 1334389194/*CallbackKind.Kind_OnRenderProcessRespondingCallback*/: return deserializeAndCallOnRenderProcessRespondingCallback(thisDeserializer);
        case -1099824577/*CallbackKind.Kind_OnSafeBrowsingCheckResultCallback*/: return deserializeAndCallOnSafeBrowsingCheckResultCallback(thisDeserializer);
        case -160015401/*CallbackKind.Kind_OnScrollCallback*/: return deserializeAndCallOnScrollCallback(thisDeserializer);
        case -150015401/*CallbackKind.Kind_OnWillScrollCallback*/: return deserializeAndCallOnWillScrollCallback(thisDeserializer);
        case -1259214476/*CallbackKind.Kind_OnScrollEdgeCallback*/: return deserializeAndCallOnScrollEdgeCallback(thisDeserializer);
        case -2133791987/*CallbackKind.Kind_OnScrollFrameBeginCallback*/: return deserializeAndCallOnScrollFrameBeginCallback(thisDeserializer);
        case 625641334/*CallbackKind.Kind_OnScrollVisibleContentChangeCallback*/: return deserializeAndCallOnScrollVisibleContentChangeCallback(thisDeserializer);
        case -399603614/*CallbackKind.Kind_OnSslErrorEventCallback*/: return deserializeAndCallOnSslErrorEventCallback(thisDeserializer);
        case -1961646162/*CallbackKind.Kind_OnSubmitCallback*/: return deserializeAndCallOnSubmitCallback(thisDeserializer);
        case -143686583/*CallbackKind.Kind_OnSwiperAnimationEndCallback*/: return deserializeAndCallOnSwiperAnimationEndCallback(thisDeserializer);
        case 876602502/*CallbackKind.Kind_OnSwiperAnimationStartCallback*/: return deserializeAndCallOnSwiperAnimationStartCallback(thisDeserializer);
        case 606029871/*CallbackKind.Kind_OnSwiperGestureSwipeCallback*/: return deserializeAndCallOnSwiperGestureSwipeCallback(thisDeserializer);
        case 1942856551/*CallbackKind.Kind_OnTabsAnimationEndCallback*/: return deserializeAndCallOnTabsAnimationEndCallback(thisDeserializer);
        case -147408344/*CallbackKind.Kind_OnTabsAnimationStartCallback*/: return deserializeAndCallOnTabsAnimationStartCallback(thisDeserializer);
        case -349727249/*CallbackKind.Kind_OnTabsContentWillChangeCallback*/: return deserializeAndCallOnTabsContentWillChangeCallback(thisDeserializer);
        case 253696833/*CallbackKind.Kind_OnTabsGestureSwipeCallback*/: return deserializeAndCallOnTabsGestureSwipeCallback(thisDeserializer);
        case 695228737/*CallbackKind.Kind_OnTextSelectionChangeCallback*/: return deserializeAndCallOnTextSelectionChangeCallback(thisDeserializer);
        case 1847083191/*CallbackKind.Kind_OnViewportFitChangedCallback*/: return deserializeAndCallOnViewportFitChangedCallback(thisDeserializer);
        case 1627123591/*CallbackKind.Kind_PageTransitionCallback*/: return deserializeAndCallPageTransitionCallback(thisDeserializer);
        case 919057028/*CallbackKind.Kind_PasteEventCallback*/: return deserializeAndCallPasteEventCallback(thisDeserializer);
        case -1992671958/*CallbackKind.Kind_PluginErrorCallback*/: return deserializeAndCallPluginErrorCallback(thisDeserializer);
        case -1265626662/*CallbackKind.Kind_ScrollOnScrollCallback*/: return deserializeAndCallScrollOnScrollCallback(thisDeserializer);
        case -721521596/*CallbackKind.Kind_ScrollOnWillScrollCallback*/: return deserializeAndCallScrollOnWillScrollCallback(thisDeserializer);
        case 1717691617/*CallbackKind.Kind_SearchSubmitCallback*/: return deserializeAndCallSearchSubmitCallback(thisDeserializer);
        case -250780276/*CallbackKind.Kind_ShouldBuiltInRecognizerParallelWithCallback*/: return deserializeAndCallShouldBuiltInRecognizerParallelWithCallback(thisDeserializer);
        case -1716637992/*CallbackKind.Kind_SizeChangeCallback*/: return deserializeAndCallSizeChangeCallback(thisDeserializer);
        case 711649376/*CallbackKind.Kind_SliderTriggerChangeCallback*/: return deserializeAndCallSliderTriggerChangeCallback(thisDeserializer);
        case -712186065/*CallbackKind.Kind_SubmitCallback*/: return deserializeAndCallSubmitCallback(thisDeserializer);
        case 221706282/*CallbackKind.Kind_TabsCustomContentTransitionCallback*/: return deserializeAndCallTabsCustomContentTransitionCallback(thisDeserializer);
        case -401980571/*CallbackKind.Kind_TextAreaSubmitCallback*/: return deserializeAndCallTextAreaSubmitCallback(thisDeserializer);
        case -1878458553/*CallbackKind.Kind_TransitionFinishCallback*/: return deserializeAndCallTransitionFinishCallback(thisDeserializer);
        case 1044833488/*CallbackKind.Kind_Type_NavigationAttribute_customNavContentTransition_delegate*/: return deserializeAndCallType_NavigationAttribute_customNavContentTransition_delegate(thisDeserializer);
        case -1078223620/*CallbackKind.Kind_Type_TextPickerAttribute_onChange_callback*/: return deserializeAndCallType_TextPickerAttribute_onChange_callback(thisDeserializer);
        case 1962174977/*CallbackKind.Kind_Type_WebAttribute_onFileSelectorShow_callback*/: return deserializeAndCallType_WebAttribute_onFileSelectorShow_callback(thisDeserializer);
        case -985284966/*CallbackKind.Kind_Type_WebAttribute_onUrlLoadIntercept_callback*/: return deserializeAndCallType_WebAttribute_onUrlLoadIntercept_callback(thisDeserializer);
        case 541663396/*CallbackKind.Kind_VisibleAreaChangeCallback*/: return deserializeAndCallVisibleAreaChangeCallback(thisDeserializer);
        case -2038961969/*CallbackKind.Kind_VoidCallback*/: return deserializeAndCallVoidCallback(thisDeserializer);
        case -1829763354/*CallbackKind.Kind_WebKeyboardCallback*/: return deserializeAndCallWebKeyboardCallback(thisDeserializer);
        case 219587748/*CallbackKind.Kind_WithThemeInterface*/: return deserializeAndCallWithThemeInterface(thisDeserializer);
        case -1736208400/*CallbackKind.Kind_Callback_String_SurfaceRect_Void*/: return deserializeAndCallCallback_String_SurfaceRect_Void(thisDeserializer);
    }
    console.log("Unknown callback kind")
}
wrapSystemCallback(1, (buff:Uint8Array, len:int32) => { deserializeAndCallCallback(new Deserializer(buff.buffer, len)); return 0 })