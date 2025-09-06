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

import { KBoolean, KStringPtr, NativeBuffer, MaterializedBase } from "@koalaui/interop"
import { int32 } from "@koalaui/common"
import { BusinessError } from "./../ArkBaseInterfaces"
import { DoubleAnimationParam, Callback_Extender_OnProgress, Callback_Extender_OnFinish } from "./../ArkAnimationExtenderInterfaces"
import { Curve, FontStyle, FontWeight, TextAlign, TextOverflow, TextCase, WordBreak, HitTestMode, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Color, Visibility, ItemAlign, Direction, GradientDirection, ObscuredReasons, RenderFit, ImageRepeat, Axis, ResponseType, FunctionKey, ModifierKey, DialogButtonStyle, AnimationStatus, FillMode, PlayMode, TextHeightAdaptivePolicy, CheckBoxShape, LineCapStyle, LineJoinStyle, HorizontalAlign, FlexAlign, TextDecorationType, TextDecorationStyle, SharedTransitionEffectType, VerticalAlign, TransitionType, MouseButton, MouseAction, AccessibilityHoverType, TouchType, KeyType, KeySource, Placement, ArrowPointPosition, ClickEffectLevel, NestedScrollMode, PixelRoundCalcPolicy, BarState, EdgeEffect, IlluminatedType, EmbeddedType, ImageFit, Edge, Week, RelateType, FlexDirection, FlexWrap, CopyOptions, TitleHeight, ImageSpanAlignment, TextContentStyle, XComponentType, ScrollSource, LineBreakStrategy, EllipsisMode, OptionWidthMode, FoldStatus, AppRotation, MarqueeUpdateStrategy, TextSelectableMode, WidthBreakpoint, HeightBreakpoint } from "./../ArkEnumsInterfaces"
import { ICurve } from "./../ArkICurveMaterialized"
import { AnimationExtender } from "./../ArkAnimationExtenderMaterialized"
import { AnimateParam, TranslateOptions, UIContext, CommonMethod, Rectangle, TouchTestInfo, TouchResult, PixelRoundPolicy, BackgroundEffectOptions, ForegroundEffectOptions, VisualEffect, Filter, BorderImageOption, OutlineStyle, AccessibilityCallback, TransitionOptions, MotionBlurOptions, InvertOptions, ScaleOptions, RotateOptions, AlignRuleOption, LocalizedAlignRuleOptions, ClickEffect, CustomBuilder, DragItemInfo, UniformDataType, PreDragStatus, MotionPathOptions, ShadowOptions, ShadowStyle, StateStyles, PixelStretchEffectOptions, BackgroundBrightnessOptions, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, SizeChangeCallback, SafeAreaType, SafeAreaEdge, BlurStyle, BackgroundBlurStyleOptions, ForegroundBlurStyleOptions, TransitionFinishCallback, BlurOptions, LinearGradientBlurOptions, EffectType, sharedTransitionOptions, ChainStyle, DragPreviewOptions, DragInteractionOptions, ComponentContent, OverlayOptions, BlendMode, BlendApplyType, Blender, GeometryTransitionOptions, PopupOptions, CustomPopupOptions, MenuElement, MenuOptions, ContextMenuOptions, ModalTransition, ContentCoverOptions, SheetOptions, VisibleAreaChangeCallback, DismissReason, HoverModeAreaType, CommonConfiguration, ContentModifier, PickerTextStyle, PickerDialogButtonStyle, CommonShapeMethod, PointLightStyle, ComponentOptions, InputCounterOptions, TextDecorationOptions, ProvideOptions, AnimatableArithmetic, Context, Configuration, ExpectedFrameRateRange, FinishCallbackType, TouchTestStrategy, TransitionHierarchyStrategy, LocalizedHorizontalAlignParam, LocalizedVerticalAlignParam, TransitionEdge, TransitionEffects, DrawContext, PreviewParams, ItemDragInfo, EventTarget, SourceType, SourceTool, RepeatMode, BlurStyleActivePolicy, ThemeColorMode, AdaptiveColor, BlurStyleOptions, ShadowType, MultiShadowOptions, LayoutSafeAreaType, LayoutSafeAreaEdge, SheetSize, LinearGradient_common, TouchObject, HistoricalPoint, DragBehavior, Summary, DragResult, IntentionCode, BindOptions, DismissContentCoverAction, SheetTitleOptions, SheetType, SheetMode, ScrollSizeMode, SheetKeyboardAvoidMode, SheetDismiss, DismissSheetAction, SpringBackAction, PopupMessageOptions, DismissPopupAction, MenuPreviewMode, ContextMenuAnimationOptions, RectResult, FadingEdgeOptions, NestedScrollOptions, SymbolGlyphModifier, DragPreviewMode, MenuPolicy, ImageModifier, CommonAttribute, CommonInterface, OverlayOffset, FractionStop, MotionBlurAnchor, LayoutBorderInfo, LayoutInfo, LayoutChild, GeometryInfo, SizeResult, Layoutable, MeasureResult, NavDestinationInfo, NavigationInfo, RouterPageInfo, Theme, CaretOffset, ContentClipMode, ScrollableCommonMethod, EdgeEffectOptions, ScrollResult, OnWillScrollCallback, DynamicNode, OnMoveHandler, LightSource, KeyframeAnimateParam, KeyframeState, Callback, VisibleAreaEventOptions, HoverCallback, UIGestureEvent, SelectionOptions, KeyboardAvoidMode } from "./../ArkCommonInterfaces"
import { PointerStyle, Callback_RangeUpdate } from "./../ArkArkuiCustomInterfaces"
import { UnifiedData } from "./../ArkUnifiedDataMaterialized"
import { LazyForEachOps } from "./../ArkLazyForEachOpsMaterialized"
import { SystemOps } from "./../ArkSystemOpsMaterialized"
import { FocusController } from "./../ArkFocusControllerMaterialized"
import { DrawableDescriptor } from "./../ArkDrawableDescriptorMaterialized"
import { PixelMap } from "./../ArkPixelMapMaterialized"
import { LayeredDrawableDescriptor } from "./../ArkLayeredDrawableDescriptorMaterialized"
import { PixelMapDrawableDescriptor } from "./../ArkPixelMapDrawableDescriptorMaterialized"
import { AnimationOptions } from "./../ArkArkuiDrawabledescriptorInterfaces"
import { AnimatedDrawableDescriptor } from "./../ArkAnimatedDrawableDescriptorMaterialized"
import { DrawingCanvas } from "./../ArkDrawingCanvasMaterialized"
import { NodeController, TextModifier, RectWidthStyle, RectHeightStyle, Want, LengthUnit, WebHeader, SnapshotOptions, PerfMonitorActionType, PerfMonitorSourceType, ShapeSize, RectShapeOptions, RoundRectShapeOptions, PathShapeOptions, FontOptions, FontInfo, MeasureOptions, EffectDirection, EffectScope, TouchPoint, ErrorCallback, Affinity } from "./../ArkArkuiExternalInterfaces"
import { LengthMetrics } from "./../ArkLengthMetricsMaterialized"
import { Resource } from "./../ArkResourceInterfaces"
import { ColorMetrics } from "./../ArkColorMetricsMaterialized"
import { ResourceColor, Position, Length, SizeOptions, Dimension, ConstraintSizeOptions, ChainWeightOptions, Padding, LocalizedPadding, Margin, LocalizedMargin, BorderOptions, EdgeStyles, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, EdgeOutlineWidths, OutlineRadiuses, Area, Edges, LocalizedEdges, LocalizedPosition, ResourceStr, AccessibilityOptions, VoidCallback, Offset, Font, LengthMetricsUnit, MarkStyle, Bias, EdgeWidth, DirectionalEdgesT, LengthConstrain, DividerStyleOptions, VP, PX, LPX } from "./../ArkUnitsInterfaces"
import { WebviewController } from "./../ArkWebviewControllerMaterialized"
import { GlobalScope_ohos_arkui_componentSnapshot } from "./../ArkGlobalScopeOhosArkuiComponentSnapshotMaterialized"
import { AsyncCallback_image_PixelMap_Void, Literal_Want_want, Callback_Array_TouchTestInfo_TouchResult, Callback_ClickEvent_Void, Callback_Boolean_HoverEvent_Void, Callback_MouseEvent_Void, Callback_TouchEvent_Void, Callback_KeyEvent_Void, Callback_KeyEvent_Boolean, Callback_Void, Callback_Area_Area_Void, Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs, Literal_Number_offset_span, Callback_DragEvent_String_Union_CustomBuilder_DragItemInfo, Callback_DragEvent_String_Void, Callback_PreDragStatus_Void, Type_CommonMethod_linearGradient_value, Tuple_ResourceColor_Number, Type_CommonMethod_sweepGradient_value, Tuple_Length_Length, Type_CommonMethod_radialGradient_value, Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult, Callback_TouchEvent_HitTestMode, Literal_Alignment_align, Callback_DismissDialogAction_Void, Callback_Number_Void, Literal_Number_day_month_year, Type_CalendarInterface_value, Callback_CalendarSelectedDate_Void, Callback_CalendarRequestedData_Void, Callback_Date_Void, Callback_Boolean_Void, HorizontalAlignOptions, VerticalAlignOptions, Literal_TransitionEffect_appear_disappear, Tuple_Number_Number, Callback_DismissContentCoverAction_Void, Type_SheetOptions_detents, Callback_SheetDismiss_Void, Callback_DismissSheetAction_Void, Callback_SpringBackAction_Void, Callback_SheetType_Void, Literal_String_value_Callback_Void_action, Literal_Boolean_isVisible, Literal_ResourceColor_color, Callback_Literal_Boolean_isVisible_Void, Callback_DismissPopupAction_Void, AnimationRange_Number, Literal_Empty, Callback_Number_Number_Void, Literal_String_key_Any_defaultValue, Callback_DatePickerResult_Void, Callback_TerminationInfo_Void, Literal_Number_errcode_String_msg, Callback_FormCallbackInfo_Void, Callback_Literal_Number_errcode_String_msg_Void, Callback_Any_Void, Tuple_Union_ResourceColor_LinearGradient_Number, Callback_GestureEvent_Void, Literal_Number_duration_fingers_Boolean_repeat, Literal_Number_distance_fingers_PanDirection_direction, Literal_Number_fingers_speed_SwipeDirection_direction, Literal_Number_distance_fingers, Literal_Number_angle_fingers, Callback_Number_Tuple_Number_Number, Callback_Number_Tuple_Number_Number_Number_Number, Tuple_Number_Number_Number_Number, Literal_Number_offsetRemain, Callback_Number_Number_ComputedBarAttribute, onItemDragStart_event_type, Callback_ItemDragInfo_Void, Callback_ItemDragInfo_Number_Number_Void, Callback_ItemDragInfo_Number_Void, Callback_ItemDragInfo_Number_Number_Boolean_Void, Callback_Number_ScrollState_Literal_Number_offsetRemain, Callback_String_Void, Type_ImageAttribute_onComplete_callback_event, Callback_Type_ImageAttribute_onComplete_callback_event_Void, Literal_Boolean_next_Axis_direction, Callback_Number_Number_Number_Void, Callback_Number_Boolean, Callback_Number_Number_Boolean, Callback_SwipeActionState_Void, Callback_ClickEvent_LocationButtonOnClickResult_Void, Callback_Boolean, Callback_NavDestinationContext_Void, Callback_PopInfo_Void, Tuple_Dimension_Dimension, Callback_NavigationTitleMode_Void, Callback_NavigationMode_Void, Callback_String_Unknown_Void, Type_NavigationAttribute_customNavContentTransition_delegate, Callback_NavigationTransitionProxy_Void, Literal_String_target_NavigationType_type, Callback_Number_Number_PanelMode_Void, Callback_PanelMode_Void, Callback_ClickEvent_PasteButtonOnClickResult_Void, Callback_Array_Number_Void, Callback_RefreshStatus_Void, Callback_RichEditorSelection_Void, Callback_RichEditorRange_Void, Callback_RichEditorInsertValue_Boolean, Callback_RichEditorTextSpanResult_Void, Callback_TextRange_Void, Callback_RichEditorDeleteValue_Boolean, Callback_RichEditorChangeValue_Boolean, Callback_CutEvent_Void, Callback_CopyEvent_Void, Callback_ClickEvent_SaveButtonOnClickResult_Void, Callback_InsertValue_Boolean, Callback_InsertValue_Void, Callback_DeleteValue_Boolean, Callback_DeleteValue_Void, Callback_Number_String_Void, Callback_Union_Number_Resource_Void, Callback_ResourceStr_Void, Callback_Number_SliderChangeMode_Void, Literal_Number_index, Callback_SwiperContentTransitionProxy_Void, Callback_TabContentTransitionProxy_Void, Callback_EnterKeyType_Void, Callback_String_PasteEvent_Void, Callback_StyledStringChangeValue_Boolean, Callback_String_Number_Void, Type_TextPickerAttribute_onChange_callback, Callback_Union_Number_Array_Number_Void, Callback_Union_String_Array_String_Void, Callback_TextPickerResult_Void, Callback_TimePickerResult_Void, Callback_FullscreenInfo_Void, Callback_PreparedInfo_Void, Callback_PlaybackInfo_Void, Literal_String_script_Callback_String_Void_callback_, Literal_String_baseUrl_data_encoding_historyUrl_mimeType, Literal_Union_String_Resource_url_Array_Header_headers, Literal_Object_object__String_name_Array_String_methodList, Literal_Union_String_WebResourceRequest_data, Literal_Function_handler_Object_error, Literal_Object_detail, Literal_Function_callback__Object_fileSelector, Callback_OnPageEndEvent_Void, Callback_OnPageBeginEvent_Void, Callback_OnProgressChangeEvent_Void, Callback_OnTitleReceiveEvent_Void, Callback_OnGeolocationShowEvent_Void, Callback_OnAlertEvent_Boolean, Callback_OnBeforeUnloadEvent_Boolean, Callback_OnConfirmEvent_Boolean, Callback_OnPromptEvent_Boolean, Callback_OnConsoleEvent_Boolean, Callback_OnErrorReceiveEvent_Void, Callback_OnHttpErrorReceiveEvent_Void, Callback_OnDownloadStartEvent_Void, Callback_OnRefreshAccessedHistoryEvent_Void, Type_WebAttribute_onUrlLoadIntercept_callback, Callback_Literal_Function_handler_Object_error_Void, Callback_OnRenderExitedEvent_Void, Callback_OnShowFileSelectorEvent_Boolean, Callback_Literal_Object_detail_Boolean, Type_WebAttribute_onFileSelectorShow_callback, Callback_OnResourceLoadEvent_Void, Callback_OnScaleChangeEvent_Void, Callback_OnHttpAuthRequestEvent_Boolean, Callback_OnInterceptRequestEvent_WebResourceResponse, Callback_OnPermissionRequestEvent_Void, Callback_OnScreenCaptureRequestEvent_Void, Callback_OnContextMenuShowEvent_Boolean, Callback_OnSearchResultReceiveEvent_Void, Callback_OnScrollEvent_Void, Callback_OnSslErrorEventReceiveEvent_Void, Callback_OnClientAuthenticationEvent_Void, Callback_OnWindowNewEvent_Void, Callback_OnTouchIconUrlReceivedEvent_Void, Callback_OnFaviconReceivedEvent_Void, Callback_OnPageVisibleEvent_Void, Callback_OnDataResubmittedEvent_Void, Callback_OnAudioStateChangedEvent_Void, Callback_OnFirstContentfulPaintEvent_Void, Callback_OnLoadInterceptEvent_Boolean, Callback_OnOverScrollEvent_Void, Callback_NativeEmbedDataInfo_Void, Callback_NativeEmbedTouchInfo_Void, Literal_String_plainText, Callback_Literal_String_plainText_Void, Literal_Number_surfaceHeight_surfaceWidth, Type_XComponentInterface_value, Callback_UIExtensionProxy_Void, Literal_Number_code_Want_want, Callback_Literal_Number_code_Want_want_Void } from "./../SyntheticDeclarations"
import { GlobalScope_ohos_arkui_performanceMonitor } from "./../ArkGlobalScopeOhosArkuiPerformanceMonitorMaterialized"
import { CommonShape } from "./../ArkCommonShapeMaterialized"
import { BaseShape } from "./../ArkBaseShapeMaterialized"
import { RectShape } from "./../ArkRectShapeMaterialized"
import { CircleShape } from "./../ArkCircleShapeMaterialized"
import { EllipseShape } from "./../ArkEllipseShapeMaterialized"
import { PathShape } from "./../ArkPathShapeMaterialized"
import { GlobalScope_ohos_font } from "./../ArkGlobalScopeOhosFontMaterialized"
import { GlobalScope_ohos_measure_utils } from "./../ArkGlobalScopeOhosMeasureUtilsMaterialized"
import { SymbolEffect } from "./../ArkSymbolEffectMaterialized"
import { ScaleSymbolEffect } from "./../ArkScaleSymbolEffectMaterialized"
import { ReplaceSymbolEffect } from "./../ArkReplaceSymbolEffectMaterialized"
import { FrameNode } from "./../ArkFrameNodeMaterialized"
import { NavExtender } from "./../ArkNavExtenderMaterialized"
import { NavPathStack } from "./../ArkNavPathStackMaterialized"
import { NavExtender_OnUpdateStack } from "./../ArkNavigationExtenderInterfaces"
import { Point } from "./../ArkPointInterfaces"
import { Root, ComponentRoot } from "./../ArkStaticComponentsInterfaces"
import { EventEmulator } from "./../ArkEventEmulatorMaterialized"
import { ClickEvent } from "./../ArkClickEventMaterialized"
import { AbilityComponentInterface, AbilityComponentAttribute } from "./../ArkAbilityComponentInterfaces"
import { DrawModifier } from "./../ArkDrawModifierMaterialized"
import { ResizableOptions, DrawingColorFilter, ResolutionQuality, DrawingLattice, ImageRenderMode, ImageContent, DynamicRangeMode, ImageInterpolation, ImageInterface, ImageAttribute, ImageSourceSize, ImageErrorCallback, ImageError } from "./../ArkImageInterfaces"
import { HoverEvent } from "./../ArkHoverEventMaterialized"
import { MouseEvent } from "./../ArkMouseEventMaterialized"
import { TouchEvent } from "./../ArkTouchEventMaterialized"
import { KeyEvent } from "./../ArkKeyEventMaterialized"
import { FocusBoxStyle, FocusPriority } from "./../ArkFocusInterfaces"
import { TransitionEffect } from "./../ArkTransitionEffectMaterialized"
import { DragEvent } from "./../ArkDragEventMaterialized"
import { ProgressMask } from "./../ArkProgressMaskMaterialized"
import { AttributeModifier, CustomComponent, AbstractProperty, IPropertySubscriber, ISinglePropertyChangeSubscriber, SubscribaleAbstract, NavigationAttribute, CommonTransition, PageTransitionEnterInterface, PageTransitionExitInterface } from "./../../handwritten"
import { GestureModifier } from "./../ArkGestureModifierMaterialized"
import { GestureInfo, GestureJudgeResult, GestureType, GestureMask, GestureHandler, GesturePriority, PanDirection, SwipeDirection, GestureMode, FingerInfo, GestureInterface, TapGestureParameters, TapGestureHandlerOptions, TapGestureHandler, LongPressGestureHandlerOptions, LongPressGestureHandler, PanGestureHandlerOptions, PanGestureHandler, SwipeGestureHandlerOptions, SwipeGestureHandler, PinchGestureHandlerOptions, PinchGestureHandler, RotationGestureHandlerOptions, RotationGestureHandler, GestureGroupGestureHandlerOptions, GestureRecognizerState } from "./../ArkGestureInterfaces"
import { BaseGestureEvent } from "./../ArkBaseGestureEventMaterialized"
import { SheetInfo, DismissDialogAction, ActionSheetButtonOptions, ActionSheetOffset, ActionSheetOptions } from "./../ArkActionSheetInterfaces"
import { DialogAlignment, DialogButtonDirection, AlertDialogButtonBaseOptions, AlertDialogButtonOptions, TextStyle_alert_dialog, AlertDialogParam, AlertDialogParamWithConfirm, AlertDialogParamWithButtons, AlertDialogParamWithOptions } from "./../ArkAlertDialogInterfaces"
import { ActionSheet } from "./../ArkActionSheetMaterialized"
import { AlertDialog } from "./../ArkAlertDialogMaterialized"
import { IndexerAlign, AlphabetIndexerOptions, AlphabetIndexerInterface, AlphabetIndexerAttribute, OnAlphabetIndexerSelectCallback, OnAlphabetIndexerRequestPopupDataCallback, OnAlphabetIndexerPopupSelectCallback } from "./../ArkAlphabetIndexerInterfaces"
import { SpringProp } from "./../ArkSpringPropMaterialized"
import { SpringMotion } from "./../ArkSpringMotionMaterialized"
import { FrictionMotion } from "./../ArkFrictionMotionMaterialized"
import { ScrollMotion } from "./../ArkScrollMotionMaterialized"
import { AnimatorInterface, AnimatorAttribute } from "./../ArkAnimatorInterfaces"
import { BadgePosition, BadgeStyle, BadgeParam, BadgeParamWithNumber, BadgeParamWithString, BadgeInterface, BadgeAttribute } from "./../ArkBadgeInterfaces"
import { BlankInterface, BlankAttribute } from "./../ArkBlankInterfaces"
import { ButtonType, ButtonStyleMode, ButtonRole, ButtonConfiguration, ButtonTriggerClickCallback, ControlSize, ButtonOptions, ButtonInterface, ButtonAttribute, LabelStyle } from "./../ArkButtonInterfaces"
import { CalendarDay, MonthData, CurrentDayStyle, NonCurrentDayStyle, TodayStyle, WeekStyle, WorkStateStyle, CalendarSelectedDate, CalendarRequestedData, CalendarInterface, CalendarAttribute } from "./../ArkCalendarInterfaces"
import { CalendarController } from "./../ArkCalendarControllerMaterialized"
import { CalendarAlign, CalendarOptions, CalendarPickerInterface, CalendarPickerAttribute, CalendarDialogOptions } from "./../ArkCalendarPickerInterfaces"
import { CalendarPickerDialog } from "./../ArkCalendarPickerDialogMaterialized"
import { CanvasGradient } from "./../ArkCanvasGradientMaterialized"
import { CanvasPath } from "./../ArkCanvasPathMaterialized"
import { Path2D } from "./../ArkPath2DMaterialized"
import { Matrix2D } from "./../ArkMatrix2DMaterialized"
import { CanvasPattern } from "./../ArkCanvasPatternMaterialized"
import { TextMetrics, ImageSmoothingQuality, CanvasLineCap, CanvasLineJoin, CanvasDirection, CanvasTextAlign, CanvasTextBaseline, CanvasFillRule, Size, CanvasInterface, CanvasAttribute } from "./../ArkCanvasInterfaces"
import { ImageBitmap } from "./../ArkImageBitmapMaterialized"
import { ImageData } from "./../ArkImageDataMaterialized"
import { RenderingContextSettings } from "./../ArkRenderingContextSettingsMaterialized"
import { CanvasRenderer } from "./../ArkCanvasRendererMaterialized"
import { CanvasRenderingContext2D } from "./../ArkCanvasRenderingContext2DMaterialized"
import { ImageAnalyzerConfig, ImageAIOptions, ImageAnalyzerType } from "./../ArkImageCommonInterfaces"
import { OffscreenCanvasRenderingContext2D } from "./../ArkOffscreenCanvasRenderingContext2DMaterialized"
import { OffscreenCanvas } from "./../ArkOffscreenCanvasMaterialized"
import { DrawingRenderingContext } from "./../ArkDrawingRenderingContextMaterialized"
import { CheckboxOptions, CheckBoxConfiguration, CheckboxInterface, CheckboxAttribute, OnCheckboxChangeCallback } from "./../ArkCheckboxInterfaces"
import { SelectStatus, CheckboxGroupOptions, CheckboxGroupResult, CheckboxGroupInterface, CheckboxGroupAttribute, OnCheckboxGroupChangeCallback } from "./../ArkCheckboxgroupInterfaces"
import { CircleOptions, CircleInterface, CircleAttribute } from "./../ArkCircleInterfaces"
import { ColumnOptions, ColumnInterface, ColumnAttribute } from "./../ArkColumnInterfaces"
import { ColumnSplitInterface, ColumnSplitAttribute, ColumnSplitDividerStyle } from "./../ArkColumnSplitInterfaces"
import { BaseEvent } from "./../ArkBaseEventMaterialized"
import { AccessibilityHoverEvent } from "./../ArkAccessibilityHoverEventMaterialized"
import { PixelMapMock } from "./../ArkPixelMapMockMaterialized"
import { Measurable } from "./../ArkMeasurableMaterialized"
import { View } from "./../ArkViewMaterialized"
import { TextContentControllerBase } from "./../ArkTextContentControllerBaseMaterialized"
import { ChildrenMainSize } from "./../ArkChildrenMainSizeMaterialized"
import { UICommonEvent } from "./../ArkUICommonEventMaterialized"
import { EnvPropsOptions, PersistPropsOptions } from "./../ArkCommonTsEtsApiInterfaces"
import { Scene, ModelType, SceneOptions, Component3DInterface, Component3DAttribute } from "./../ArkComponent3dInterfaces"
import { ContainerSpanInterface, ContainerSpanAttribute } from "./../ArkContainerSpanInterfaces"
import { TextBackgroundStyle, BaseSpan, SpanInterface, SpanAttribute } from "./../ArkSpanInterfaces"
import { Content, ContentSlotAttribute, ContentSlotInterface } from "./../ArkContentSlotInterfaces"
import { ContextMenu } from "./../ArkContextMenuMaterialized"
import { CounterInterface, CounterAttribute } from "./../ArkCounterInterfaces"
import { CustomDialogControllerOptions } from "./../ArkCustomDialogControllerInterfaces"
import { CustomDialogController } from "./../ArkCustomDialogControllerMaterialized"
import { DataPanelType, ColorStop, DataPanelShadowOptions, DataPanelOptions, DataPanelInterface, DataPanelAttribute, DataPanelConfiguration } from "./../ArkDataPanelInterfaces"
import { LinearGradient } from "./../ArkLinearGradientMaterialized"
import { DatePickerResult, DatePickerOptions, DatePickerInterface, DatePickerAttribute, LunarSwitchStyle, DatePickerDialogOptions } from "./../ArkDatePickerInterfaces"
import { DateTimeOptions, TimePickerResult, TimePickerFormat, TimePickerOptions, TimePickerInterface, TimePickerAttribute, TimePickerDialogOptions } from "./../ArkTimePickerInterfaces"
import { DatePickerDialog } from "./../ArkDatePickerDialogMaterialized"
import { DividerInterface, DividerAttribute } from "./../ArkDividerInterfaces"
import { EffectComponentInterface, EffectComponentAttribute } from "./../ArkEffectComponentInterfaces"
import { EllipseOptions, EllipseInterface, EllipseAttribute } from "./../ArkEllipseInterfaces"
import { EmbeddedComponentInterface, EmbeddedComponentAttribute, TerminationInfo } from "./../ArkEmbeddedComponentInterfaces"
import { FlexOptions, FlexSpaceOptions, FlexInterface, FlexAttribute } from "./../ArkFlexInterfaces"
import { FlowItemInterface, FlowItemAttribute } from "./../ArkFlowItemInterfaces"
import { WindowStatusType, FolderStackOptions, FolderStackInterface, FolderStackAttribute, OnFoldStatusChangeInfo, OnFoldStatusChangeCallback, OnHoverStatusChangeCallback, HoverEventParam } from "./../ArkFolderStackInterfaces"
import { FormDimension, FormRenderingMode, FormShape, FormInfo, FormComponentInterface, FormComponentAttribute, FormCallbackInfo } from "./../ArkFormComponentInterfaces"
import { FormLinkOptions, FormLinkInterface, FormLinkAttribute } from "./../ArkFormLinkInterfaces"
import { GaugeOptions, GaugeInterface, GaugeAttribute, GaugeShadowOptions, GaugeIndicatorOptions, GaugeConfiguration } from "./../ArkGaugeInterfaces"
import { GestureControl } from "./../ArkGestureControlNamespace"
import { TapGestureEvent } from "./../ArkTapGestureEventMaterialized"
import { LongPressGestureEvent } from "./../ArkLongPressGestureEventMaterialized"
import { PanGestureEvent } from "./../ArkPanGestureEventMaterialized"
import { PinchGestureEvent } from "./../ArkPinchGestureEventMaterialized"
import { RotationGestureEvent } from "./../ArkRotationGestureEventMaterialized"
import { SwipeGestureEvent } from "./../ArkSwipeGestureEventMaterialized"
import { GestureEvent } from "./../ArkGestureEventMaterialized"
import { TapGestureInterface } from "./../ArkTapGestureInterfaceMaterialized"
import { LongPressGestureInterface } from "./../ArkLongPressGestureInterfaceMaterialized"
import { PanGestureOptions } from "./../ArkPanGestureOptionsMaterialized"
import { PanGestureInterface } from "./../ArkPanGestureInterfaceMaterialized"
import { SwipeGestureInterface } from "./../ArkSwipeGestureInterfaceMaterialized"
import { PinchGestureInterface } from "./../ArkPinchGestureInterfaceMaterialized"
import { RotationGestureInterface } from "./../ArkRotationGestureInterfaceMaterialized"
import { GestureGroupInterface } from "./../ArkGestureGroupInterfaceMaterialized"
import { ScrollableTargetInfo } from "./../ArkScrollableTargetInfoMaterialized"
import { EventTargetInfo } from "./../ArkEventTargetInfoMaterialized"
import { GestureRecognizer } from "./../ArkGestureRecognizerMaterialized"
import { PanRecognizer } from "./../ArkPanRecognizerMaterialized"
import { GridLayoutOptions, GridInterface, GridAttribute, GridDirection, GridItemAlignment, ComputedBarAttribute } from "./../ArkGridInterfaces"
import { Scroller } from "./../ArkScrollerMaterialized"
import { ScrollState, ListItemAlign, ListItemGroupArea, StickyStyle, ChainEdgeEffect, ScrollSnapAlign, ChainAnimationOptions, CloseSwipeActionOptions, VisibleListContentInfo, ListOptions, ListInterface, ListAttribute, ListDividerOptions, OnScrollVisibleContentChangeCallback } from "./../ArkListInterfaces"
import { GridItemStyle, GridItemOptions, GridItemInterface, GridItemAttribute } from "./../ArkGridItemInterfaces"
import { GridColColumnOption, GridColOptions, GridColInterface, GridColAttribute } from "./../ArkGridColInterfaces"
import { SizeType, GridContainerOptions, GridContainerInterface, GridContainerAttribute } from "./../ArkGridContainerInterfaces"
import { GridRowSizeOption, GridRowColumnOption, GutterOption, BreakpointsReference, GridRowDirection, BreakPoints, GridRowOptions, GridRowInterface, GridRowAttribute } from "./../ArkGridRowInterfaces"
import { HyperlinkInterface, HyperlinkAttribute } from "./../ArkHyperlinkInterfaces"
import { ColorFilter } from "./../ArkColorFilterMaterialized"
import { ImageAnimatorInterface, ImageAnimatorAttribute, ImageFrameInfo } from "./../ArkImageAnimatorInterfaces"
import { ImageAnalyzerController } from "./../ArkImageAnalyzerControllerMaterialized"
import { ImageSpanInterface, ImageSpanAttribute, ImageCompleteCallback, ImageLoadResult } from "./../ArkImageSpanInterfaces"
import { DataOperationType, DataAddOperation, DataDeleteOperation, DataChangeOperation, MoveIndex, ExchangeIndex, ExchangeKey, DataMoveOperation, DataExchangeOperation, DataReloadOperation } from "./../ArkLazyForEachInterfaces"
import { LineOptions, LineInterface, LineAttribute } from "./../ArkLineInterfaces"
import { ListScroller } from "./../ArkListScrollerMaterialized"
import { ScrollOptions, ScrollEdgeOptions, ScrollPageOptions, OffsetResult, ScrollAlign, ScrollToIndexOptions, ScrollDirection, ScrollAnimationOptions, OffsetOptions, ScrollSnapOptions, ScrollInterface, ScrollAttribute, OnScrollFrameBeginHandlerResult, ScrollOnWillScrollCallback, ScrollOnScrollCallback, OnScrollEdgeCallback, OnScrollFrameBeginCallback } from "./../ArkScrollInterfaces"
import { Sticky, EditMode, SwipeEdgeEffect, SwipeActionState, SwipeActionItem, SwipeActionOptions, ListItemStyle, ListItemOptions, ListItemInterface, ListItemAttribute } from "./../ArkListItemInterfaces"
import { ListItemGroupStyle, ListItemGroupOptions, ListItemGroupInterface, ListItemGroupAttribute } from "./../ArkListItemGroupInterfaces"
import { LoadingProgressStyle, LoadingProgressInterface, LoadingProgressAttribute, LoadingProgressConfiguration } from "./../ArkLoadingProgressInterfaces"
import { LocationIconStyle, LocationDescription, LocationButtonOptions, LocationButtonOnClickResult, LocationButtonInterface, LocationButtonAttribute } from "./../ArkLocationButtonInterfaces"
import { SecurityComponentMethod, SecurityComponentLayoutDirection } from "./../ArkSecurityComponentInterfaces"
import { MarqueeOptions, MarqueeInterface, MarqueeAttribute } from "./../ArkMarqueeInterfaces"
import { ASTCResource, MediaCachedImageInterface, MediaCachedImageAttribute } from "./../ArkMediaCachedImageInterfaces"
import { MenuInterface, MenuAttribute, SubMenuExpandingMode } from "./../ArkMenuInterfaces"
import { MenuItemOptions, MenuItemInterface, MenuItemAttribute } from "./../ArkMenuItemInterfaces"
import { MenuItemGroupOptions, MenuItemGroupInterface, MenuItemGroupAttribute } from "./../ArkMenuItemGroupInterfaces"
import { NavDestinationCommonTitle, NavDestinationCustomTitle, NavigationSystemTransitionType, NavDestinationMode, NavDestinationInterface, NavDestinationAttribute, RouteMapConfig } from "./../ArkNavDestinationInterfaces"
import { NavDestinationContext } from "./../ArkNavDestinationContextMaterialized"
import { NavPathInfo } from "./../ArkNavPathInfoMaterialized"
import { NavigationMenuItem, SystemBarStyle, NavigationTitleOptions, ToolbarItem, NavigationToolbarOptions, NavigationCommonTitle, NavigationCustomTitle, NavigationMode, NavBarPosition, NavigationTitleMode, PopInfo, LaunchMode, NavigationOptions, NavigationInterception, InterceptionShowCallback, InterceptionModeCallback, NavigationInterface, ToolbarItemStatus, NavigationOperation, BarStyle, NavContentInfo, NavigationAnimatedTransition } from "./../ArkNavigationInterfaces"
import { RouteInfo, NavRouterInterface, NavRouterAttribute, NavRouteMode } from "./../ArkNavRouterInterfaces"
import { NavigationTransitionProxy } from "./../ArkNavigationTransitionProxyMaterialized"
import { NavigationType, NavigatorInterface, NavigatorAttribute } from "./../ArkNavigatorInterfaces"
import { NodeContainerInterface, NodeContainerAttribute } from "./../ArkNodeContainerInterfaces"
import { RouteType, SlideEffect, PageTransitionOptions, PageTransitionCallback } from "./../ArkPageTransitionInterfaces"
import { PanelMode, PanelType, PanelHeight, PanelInterface, PanelAttribute } from "./../ArkPanelInterfaces"
import { VelocityOptions, ParticleTuple, PointParticleParameters, ImageParticleParameters, ParticleConfigs, EmitterProperty, EmitterParticleOptions, ParticlePropertyUpdaterConfigs, ParticleUpdaterOptions, ParticleColorOptions, ParticleColorUpdaterOptions, ParticleColorPropertyUpdaterConfigs, ParticlePropertyAnimation, ParticleType, ParticleEmitterShape, DistributionType, ParticleUpdater, DisturbanceFieldShape } from "./../ArkParticleInterfaces"
import { PasteIconStyle, PasteDescription, PasteButtonOptions, PasteButtonOnClickResult, PasteButtonInterface, PasteButtonAttribute } from "./../ArkPasteButtonInterfaces"
import { PathOptions, PathInterface, PathAttribute } from "./../ArkPathInterfaces"
import { PatternLockChallengeResult, CircleStyleOptions, PatternLockInterface, PatternLockAttribute } from "./../ArkPatternLockInterfaces"
import { PatternLockController } from "./../ArkPatternLockControllerMaterialized"
import { PluginComponentTemplate, PluginComponentOptions, PluginErrorData, PluginComponentInterface, PluginComponentAttribute, PluginErrorCallback } from "./../ArkPluginComponentInterfaces"
import { PolygonOptions, PolygonInterface, PolygonAttribute } from "./../ArkPolygonInterfaces"
import { PolylineOptions, PolylineInterface, PolylineAttribute } from "./../ArkPolylineInterfaces"
import { ProgressOptions, ProgressStyle, ProgressType, ProgressStatus, ProgressStyleOptions, CommonProgressStyleOptions, ScanEffectOptions, EclipseStyleOptions, ScaleRingStyleOptions, RingStyleOptions, LinearStyleOptions, CapsuleStyleOptions, ProgressStyleMap, ProgressInterface, ProgressAttribute, ProgressConfiguration } from "./../ArkProgressInterfaces"
import { QRCodeInterface, QRCodeAttribute } from "./../ArkQrcodeInterfaces"
import { RadioIndicatorType, RadioOptions, RadioStyle, RadioInterface, RadioAttribute, RadioConfiguration } from "./../ArkRadioInterfaces"
import { RatingOptions, StarStyleOptions, RatingInterface, RatingAttribute, RatingConfiguration } from "./../ArkRatingInterfaces"
import { RectOptions, RoundedRectOptions, RectInterface, RectAttribute } from "./../ArkRectInterfaces"
import { RefreshStatus, RefreshOptions, RefreshInterface, RefreshAttribute } from "./../ArkRefreshInterfaces"
import { RelativeContainerInterface, RelativeContainerAttribute, GuideLinePosition, GuideLineStyle, BarrierDirection, LocalizedBarrierDirection, BarrierStyle, LocalizedBarrierStyle } from "./../ArkRelativeContainerInterfaces"
import { VirtualScrollOptions, TemplateOptions } from "./../ArkRepeatInterfaces"
import { RichEditorDeleteDirection, RichEditorSpanType, RichEditorResponseType, RichEditorSpanPosition, RichEditorTextStyle, LeadingMarginPlaceholder, RichEditorParagraphStyle, PasteEvent, RichEditorTextSpan, RichEditorLayoutStyle, RichEditorImageSpanStyle, RichEditorSymbolSpanStyle, RichEditorTextStyleResult, RichEditorParagraphResult, RichEditorSymbolSpanStyleResult, RichEditorTextSpanResult, RichEditorImageSpanStyleResult, RichEditorImageSpanResult, RichEditorImageSpan, RichEditorRange, RichEditorGesture, RichEditorTextSpanOptions, KeyboardOptions, RichEditorImageSpanOptions, RichEditorBuilderSpanOptions, PlaceholderStyle, RichEditorSpanStyleOptions, RichEditorParagraphStyleOptions, RichEditorUpdateTextSpanStyleOptions, RichEditorUpdateImageSpanStyleOptions, RichEditorUpdateSymbolSpanStyleOptions, RichEditorSymbolSpanOptions, RichEditorSelection, RichEditorInsertValue, RichEditorDeleteValue, RichEditorChangeValue, RichEditorOptions, RichEditorStyledStringOptions, SelectionMenuOptions, MenuOnAppearCallback, RichEditorSpan, RichEditorAttribute, PasteEventCallback, SubmitCallback, CutEvent, CopyEvent, RichEditorInterface } from "./../ArkRichEditorInterfaces"
import { DecorationStyleInterface, StyleOptions, StyledStringKey, SpanStyle, StyledStringValue, TextStyleInterface, GestureStyleInterface, ParagraphStyleInterface, ImageAttachmentLayoutStyle, ImageAttachmentInterface, CustomSpanMetrics, CustomSpanDrawInfo, CustomSpanMeasureInfo, UserDataSpan } from "./../ArkStyledStringInterfaces"
import { SymbolEffectStrategy, SymbolRenderingStrategy, SymbolGlyphInterface, SymbolGlyphAttribute, EffectFillStyle } from "./../ArkSymbolglyphInterfaces"
import { DecorationStyleResult, TextRange, MenuType, PreviewText, StyledStringChangedListener, TextDataDetectorConfig, OnDidChangeCallback, CaretStyle, EditableTextOnChangeCallback, InsertValue, DeleteValue, FontSettingOptions, TextDataDetectorType, TextDeleteDirection, StyledStringChangeValue, PositionWithAffinity, LineMetrics, TextBox, TextMenuItem } from "./../ArkTextCommonInterfaces"
import { RichEditorController } from "./../ArkRichEditorControllerMaterialized"
import { RichEditorStyledStringController } from "./../ArkRichEditorStyledStringControllerMaterialized"
import { RichEditorBaseController } from "./../ArkRichEditorBaseControllerMaterialized"
import { TextEditControllerEx } from "./../ArkTextEditControllerExMaterialized"
import { TextBaseController } from "./../ArkTextBaseControllerMaterialized"
import { LayoutManager } from "./../ArkLayoutManagerMaterialized"
import { StyledString } from "./../ArkStyledStringMaterialized"
import { StyledStringController } from "./../ArkStyledStringControllerMaterialized"
import { MutableStyledString } from "./../ArkMutableStyledStringMaterialized"
import { EnterKeyType, OnTextSelectionChangeCallback, OnContentScrollCallback, OnPasteCallback, InputType, UnderlineColor, TextInputOptions, TextInputStyle, TextInputInterface, TextInputAttribute, PasswordIcon, OnSubmitCallback } from "./../ArkTextInputInterfaces"
import { EditMenuOptions } from "./../ArkEditMenuOptionsMaterialized"
import { RichTextInterface, RichTextAttribute } from "./../ArkRichTextInterfaces"
import { RootSceneSession, RootSceneInterface, RootSceneAttribute } from "./../ArkRootSceneInterfaces"
import { RowOptions, RowInterface, RowAttribute } from "./../ArkRowInterfaces"
import { RowSplitInterface, RowSplitAttribute } from "./../ArkRowSplitInterfaces"
import { SaveIconStyle, SaveDescription, SaveButtonOptions, SaveButtonOnClickResult, SaveButtonInterface, SaveButtonAttribute } from "./../ArkSaveButtonInterfaces"
import { ScreenInterface, ScreenAttribute } from "./../ArkScreenInterfaces"
import { ScrollBarDirection, ScrollBarOptions, ScrollBarInterface, ScrollBarAttribute } from "./../ArkScrollBarInterfaces"
import { SearchController } from "./../ArkSearchControllerMaterialized"
import { CancelButtonStyle, SearchType, SearchOptions, SearchInterface, SearchAttribute, IconOptions, SearchButtonOptions, CancelButtonOptions, CancelButtonSymbolOptions, SearchSubmitCallback } from "./../ArkSearchInterfaces"
import { SelectOption, SelectInterface, SelectAttribute, ArrowPosition, MenuAlignType, MenuItemConfiguration } from "./../ArkSelectInterfaces"
import { DividerOptions, TextPickerRangeContent, TextCascadePickerRangeContent, TextPickerOptions, TextPickerInterface, TextPickerAttribute, TextPickerResult, TextPickerDialogOptions } from "./../ArkTextPickerInterfaces"
import { ViewportRect, ShapeInterface, ShapeAttribute } from "./../ArkShapeInterfaces"
import { SliderStyle, SliderChangeMode, SliderInteraction, SlideRange, SliderOptions, SliderBlockType, SliderBlockStyle, SliderConfiguration, SliderTriggerChangeCallback, SliderInterface, SliderAttribute } from "./../ArkSliderInterfaces"
import { StackOptions, StackInterface, StackAttribute } from "./../ArkStackInterfaces"
import { ColorMode, LayoutDirection } from "./../ArkStateManagementInterfaces"
import { StepperInterface, StepperAttribute } from "./../ArkStepperInterfaces"
import { ItemState, StepperItemInterface, StepperItemAttribute } from "./../ArkStepperItemInterfaces"
import { SwiperController } from "./../ArkSwiperControllerMaterialized"
import { Indicator } from "./../ArkIndicatorBuilder"
import { DotIndicator } from "./../ArkDotIndicatorBuilder"
import { DigitIndicator } from "./../ArkDigitIndicatorBuilder"
import { SwiperAutoFill, ArrowStyle, SwiperDisplayMode, SwiperInterface, SwiperAttribute, IndicatorStyle, SwiperAnimationEvent, SwiperNestedScrollMode, OnSwiperAnimationStartCallback, OnSwiperAnimationEndCallback, OnSwiperGestureSwipeCallback, SwiperContentAnimatedTransition, ContentDidScrollCallback } from "./../ArkSwiperInterfaces"
import { IndicatorComponentController } from "./../ArkIndicatorComponentControllerMaterialized"
import { SwiperContentTransitionProxy } from "./../ArkSwiperContentTransitionProxyMaterialized"
import { IndicatorComponentInterface, IndicatorComponentAttribute } from "./../ArkIndicatorcomponentInterfaces"
import { HierarchicalSymbolEffect } from "./../ArkHierarchicalSymbolEffectMaterialized"
import { AppearSymbolEffect } from "./../ArkAppearSymbolEffectMaterialized"
import { DisappearSymbolEffect } from "./../ArkDisappearSymbolEffectMaterialized"
import { BounceSymbolEffect } from "./../ArkBounceSymbolEffectMaterialized"
import { PulseSymbolEffect } from "./../ArkPulseSymbolEffectMaterialized"
import { SymbolSpanInterface, SymbolSpanAttribute } from "./../ArkSymbolSpanInterfaces"
import { BarMode, AnimationMode, BarPosition, LayoutStyle, TabsOptions, TabsInterface, TabsAttribute, DividerStyle, TabsAnimationEvent, BarGridColumnOptions, ScrollableBarModeOptions, OnTabsAnimationStartCallback, OnTabsAnimationEndCallback, OnTabsGestureSwipeCallback, TabsCustomContentTransitionCallback, OnTabsContentWillChangeCallback, TabContentAnimatedTransition } from "./../ArkTabsInterfaces"
import { TabsController } from "./../ArkTabsControllerMaterialized"
import { TabContentTransitionProxy } from "./../ArkTabContentTransitionProxyMaterialized"
import { SelectedMode, LayoutMode, BoardStyle, TabBarIconStyle, TabBarSymbol, TabBarOptions, TabContentInterface, TabContentAttribute } from "./../ArkTabContentInterfaces"
import { SubTabBarStyle } from "./../ArkSubTabBarStyleBuilder"
import { BottomTabBarStyle } from "./../ArkBottomTabBarStyleBuilder"
import { TextOverflowOptions, TextInterface, TextOptions, TextAttribute, TextSpanType, TextResponseType } from "./../ArkTextInterfaces"
import { TextController } from "./../ArkTextControllerMaterialized"
import { TextAreaController } from "./../ArkTextAreaControllerMaterialized"
import { TextAreaOptions, TextAreaInterface, TextAreaAttribute, TextAreaType, ContentType, TextAreaSubmitCallback } from "./../ArkTextAreaInterfaces"
import { TextClockController } from "./../ArkTextClockControllerMaterialized"
import { TextClockConfiguration, TextClockOptions, TextClockInterface, TextClockAttribute } from "./../ArkTextClockInterfaces"
import { TextMenuItemId } from "./../ArkTextMenuItemIdMaterialized"
import { SubmitEvent } from "./../ArkSubmitEventMaterialized"
import { TextInputController } from "./../ArkTextInputControllerMaterialized"
import { TextPickerDialog } from "./../ArkTextPickerDialogMaterialized"
import { TextTimerController } from "./../ArkTextTimerControllerMaterialized"
import { TextTimerConfiguration, TextTimerOptions, TextTimerInterface, TextTimerAttribute } from "./../ArkTextTimerInterfaces"
import { TimePickerDialog } from "./../ArkTimePickerDialogMaterialized"
import { ToggleType, SwitchStyle, ToggleConfiguration, ToggleOptions, ToggleInterface, ToggleAttribute } from "./../ArkToggleInterfaces"
import { CustomTheme, WithThemeOptions, WithThemeAttribute } from "./../ArkWithThemeInterfaces"
import { SeekMode, PlaybackSpeed, FullscreenInfo, PreparedInfo, PlaybackInfo, VideoOptions, VideoInterface, VideoAttribute } from "./../ArkVideoInterfaces"
import { VideoController } from "./../ArkVideoControllerMaterialized"
import { NativeMediaPlayerConfig, AdsBlockedDetails, WebKeyboardOptions, WebKeyboardCallbackInfo, MessageLevel, MixedMode, HitTestType, CacheMode, OverScrollMode, WebDarkMode, WebCaptureMode, ThreatType, WebMediaOptions, ScreenCaptureConfig, FullScreenEnterEvent, RenderExitReason, SslError, FileSelectorMode, WebLayoutMode, RenderProcessNotRespondingReason, ProtectedResourceType, ContextMenuSourceType, ContextMenuMediaType, ContextMenuInputFieldType, NativeEmbedStatus, ContextMenuEditStateFlags, WebNavigationType, RenderMode, ViewportFit, Header, WebOptions, ScriptItem, LoadCommittedDetails, IntelligentTrackingPreventionDetails, WebInterface, WebAttribute, NativeEmbedInfo, NativeEmbedDataInfo, NativeEmbedVisibilityInfo, NativeEmbedTouchInfo, FirstMeaningfulPaint, LargestContentfulPaint, RenderProcessNotRespondingData, OnPageEndEvent, OnPageBeginEvent, OnProgressChangeEvent, OnTitleReceiveEvent, OnGeolocationShowEvent, OnAlertEvent, OnBeforeUnloadEvent, OnConfirmEvent, OnPromptEvent, OnConsoleEvent, OnErrorReceiveEvent, OnHttpErrorReceiveEvent, OnDownloadStartEvent, OnRefreshAccessedHistoryEvent, OnRenderExitedEvent, OnShowFileSelectorEvent, OnResourceLoadEvent, OnScaleChangeEvent, OnHttpAuthRequestEvent, OnInterceptRequestEvent, OnPermissionRequestEvent, OnScreenCaptureRequestEvent, OnContextMenuShowEvent, OnSearchResultReceiveEvent, OnScrollEvent, OnSslErrorEventReceiveEvent, OnClientAuthenticationEvent, OnWindowNewEvent, OnTouchIconUrlReceivedEvent, OnFaviconReceivedEvent, OnPageVisibleEvent, OnDataResubmittedEvent, OnAudioStateChangedEvent, OnFirstContentfulPaintEvent, OnLoadInterceptEvent, OnOverScrollEvent, JavaScriptProxy, WebKeyboardAvoidMode, WebElementType, WebResponseType, SelectionMenuOptionsExt, OnFullScreenEnterCallback, OnContextMenuHideCallback, OnSslErrorEventCallback, OnFirstMeaningfulPaintCallback, OnLargestContentfulPaintCallback, OnSafeBrowsingCheckResultCallback, OnNavigationEntryCommittedCallback, OnIntelligentTrackingPreventionCallback, NestedScrollOptionsExt, OnNativeEmbedVisibilityChangeCallback, OnOverrideUrlLoadingCallback, OnRenderProcessNotRespondingCallback, OnRenderProcessRespondingCallback, ExpandedMenuItemOptions, OnViewportFitChangedCallback, WebKeyboardCallback, OnAdsBlockedCallback, SslErrorEvent } from "./../ArkWebInterfaces"
import { WebKeyboardController } from "./../ArkWebKeyboardControllerMaterialized"
import { FullScreenExitHandler } from "./../ArkFullScreenExitHandlerMaterialized"
import { FileSelectorParam } from "./../ArkFileSelectorParamMaterialized"
import { JsResult } from "./../ArkJsResultMaterialized"
import { FileSelectorResult } from "./../ArkFileSelectorResultMaterialized"
import { HttpAuthHandler } from "./../ArkHttpAuthHandlerMaterialized"
import { SslErrorHandler } from "./../ArkSslErrorHandlerMaterialized"
import { ClientAuthenticationHandler } from "./../ArkClientAuthenticationHandlerMaterialized"
import { PermissionRequest } from "./../ArkPermissionRequestMaterialized"
import { ScreenCaptureHandler } from "./../ArkScreenCaptureHandlerMaterialized"
import { DataResubmissionHandler } from "./../ArkDataResubmissionHandlerMaterialized"
import { ControllerHandler } from "./../ArkControllerHandlerMaterialized"
import { WebContextMenuParam } from "./../ArkWebContextMenuParamMaterialized"
import { WebContextMenuResult } from "./../ArkWebContextMenuResultMaterialized"
import { ConsoleMessage } from "./../ArkConsoleMessageMaterialized"
import { WebResourceRequest } from "./../ArkWebResourceRequestMaterialized"
import { WebResourceResponse } from "./../ArkWebResourceResponseMaterialized"
import { WebResourceError } from "./../ArkWebResourceErrorMaterialized"
import { JsGeolocation } from "./../ArkJsGeolocationMaterialized"
import { WebCookie } from "./../ArkWebCookieMaterialized"
import { EventResult } from "./../ArkEventResultMaterialized"
import { WebController } from "./../ArkWebControllerMaterialized"
import { WindowSceneInterface, WindowSceneAttribute } from "./../ArkWindowSceneInterfaces"
import { SurfaceRect, SurfaceRotationOptions, XComponentOptions, XComponentInterface, XComponentAttribute, OnNativeLoadCallback } from "./../ArkXcomponentInterfaces"
import { XComponentController } from "./../ArkXComponentControllerMaterialized"
import { SideBarContainerType, SideBarPosition, ButtonIconOptions, ButtonStyle, SideBarContainerInterface, SideBarContainerAttribute } from "./../ArkSidebarInterfaces"
import { RRect, WindowAnimationTarget, RemoteWindowInterface, RemoteWindowAttribute } from "./../ArkRemoteWindowInterfaces"
import { SectionOptions, GetItemMainSizeByIndex, WaterFlowLayoutMode, WaterFlowOptions, WaterFlowInterface, WaterFlowAttribute } from "./../ArkWaterFlowInterfaces"
import { WaterFlowSections } from "./../ArkWaterFlowSectionsMaterialized"
import { DpiFollowStrategy, UIExtensionOptions, ReceiveCallback, UIExtensionComponentInterface, UIExtensionComponentAttribute } from "./../ArkUiExtensionComponentInterfaces"
import { UIExtensionProxy } from "./../ArkUIExtensionProxyMaterialized"
import { RestrictedWorker, IsolatedOptions, IsolatedComponentAttribute } from "./../ArkIsolatedComponentInterfaces"
import { ImageAttachment } from "./../ArkImageAttachmentMaterialized"
import { CustomSpan } from "./../ArkCustomSpanMaterialized"
import { TextStyle_styled_string } from "./../ArkTextStyleStyledStringMaterialized"
import { DecorationStyle } from "./../ArkDecorationStyleMaterialized"
import { BaselineOffsetStyle } from "./../ArkBaselineOffsetStyleMaterialized"
import { LetterSpacingStyle } from "./../ArkLetterSpacingStyleMaterialized"
import { TextShadowStyle } from "./../ArkTextShadowStyleMaterialized"
import { BackgroundColorStyle } from "./../ArkBackgroundColorStyleMaterialized"
import { GestureStyle } from "./../ArkGestureStyleMaterialized"
import { ParagraphStyle } from "./../ArkParagraphStyleMaterialized"
import { LineHeightStyle } from "./../ArkLineHeightStyleMaterialized"
import { UrlStyle } from "./../ArkUrlStyleMaterialized"
import { LinearIndicatorController } from "./../ArkLinearIndicatorControllerMaterialized"
import { LinearIndicatorStartOptions, LinearIndicatorStyle, LinearIndicatorInterface, LinearIndicatorAttribute, OnLinearIndicatorChangeCallback } from "./../ArkLinearindicatorInterfaces"
import { RawFileDescriptor } from "./../ArkRawFileDescriptorInterfaces"
export class TypeChecker {
    static typeInstanceOf<T>(value: Object, prop: string): boolean {
        return value.hasOwnProperty(prop)
    }
    static typeCast<T>(value: Object): T {
        return value as unknown as T
    }
    static isNativeBuffer(value: Object): boolean {
        return value instanceof ArrayBuffer
    }
    static isAbilityComponentAttribute(value: object|string|number|undefined|null|boolean, duplicated_onConnect: boolean, duplicated_onDisconnect: boolean): boolean {
        if ((!duplicated_onConnect) && (value?.hasOwnProperty("onConnect"))) {
            return true
        }
        else if ((!duplicated_onDisconnect) && (value?.hasOwnProperty("onDisconnect"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof AbilityComponentAttribute")
        }
    }
    static isAbilityComponentInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof AbilityComponentInterface")
    }
    static isAbstractProperty(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof AbstractProperty")
    }
    static isAccessibilityHoverEvent(value: object|string|number|undefined|null|boolean, duplicated_type: boolean, duplicated_x: boolean, duplicated_y: boolean, duplicated_displayX: boolean, duplicated_displayY: boolean, duplicated_windowX: boolean, duplicated_windowY: boolean): boolean {
        if ((!duplicated_type) && (value?.hasOwnProperty("type"))) {
            return true
        }
        else if ((!duplicated_x) && (value?.hasOwnProperty("x"))) {
            return true
        }
        else if ((!duplicated_y) && (value?.hasOwnProperty("y"))) {
            return true
        }
        else if ((!duplicated_displayX) && (value?.hasOwnProperty("displayX"))) {
            return true
        }
        else if ((!duplicated_displayY) && (value?.hasOwnProperty("displayY"))) {
            return true
        }
        else if ((!duplicated_windowX) && (value?.hasOwnProperty("windowX"))) {
            return true
        }
        else if ((!duplicated_windowY) && (value?.hasOwnProperty("windowY"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof AccessibilityHoverEvent")
        }
    }
    static isAccessibilityHoverType(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (AccessibilityHoverType.HOVER_ENTER)) {
            return true
        }
        else if ((value) === (AccessibilityHoverType.HOVER_MOVE)) {
            return true
        }
        else if ((value) === (AccessibilityHoverType.HOVER_EXIT)) {
            return true
        }
        else if ((value) === (AccessibilityHoverType.HOVER_CANCEL)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof AccessibilityHoverType")
        }
    }
    static isAccessibilityOptions(value: object|string|number|undefined|null|boolean, duplicated_accessibilityPreferred: boolean): boolean {
        if ((!duplicated_accessibilityPreferred) && (value?.hasOwnProperty("accessibilityPreferred"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof AccessibilityOptions")
        }
    }
    static isActionSheet(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof ActionSheet")
    }
    static isActionSheetButtonOptions(value: object|string|number|undefined|null|boolean, duplicated_enabled: boolean, duplicated_defaultFocus: boolean, duplicated_style: boolean, duplicated_value: boolean, duplicated_action: boolean): boolean {
        if ((!duplicated_value) && (value?.hasOwnProperty("value"))) {
            return true
        }
        else if ((!duplicated_action) && (value?.hasOwnProperty("action"))) {
            return true
        }
        else if ((!duplicated_enabled) && (value?.hasOwnProperty("enabled"))) {
            return true
        }
        else if ((!duplicated_defaultFocus) && (value?.hasOwnProperty("defaultFocus"))) {
            return true
        }
        else if ((!duplicated_style) && (value?.hasOwnProperty("style"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ActionSheetButtonOptions")
        }
    }
    static isActionSheetOffset(value: object|string|number|undefined|null|boolean, duplicated_dx: boolean, duplicated_dy: boolean): boolean {
        if ((!duplicated_dx) && (value?.hasOwnProperty("dx"))) {
            return true
        }
        else if ((!duplicated_dy) && (value?.hasOwnProperty("dy"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ActionSheetOffset")
        }
    }
    static isActionSheetOptions(value: object|string|number|undefined|null|boolean, duplicated_title: boolean, duplicated_subtitle: boolean, duplicated_message: boolean, duplicated_confirm: boolean, duplicated_cancel: boolean, duplicated_sheets: boolean, duplicated_autoCancel: boolean, duplicated_alignment: boolean, duplicated_offset: boolean, duplicated_maskRect: boolean, duplicated_showInSubWindow: boolean, duplicated_isModal: boolean, duplicated_backgroundColor: boolean, duplicated_backgroundBlurStyle: boolean, duplicated_onWillDismiss: boolean, duplicated_transition: boolean, duplicated_cornerRadius: boolean, duplicated_width: boolean, duplicated_height: boolean, duplicated_borderWidth: boolean, duplicated_borderColor: boolean, duplicated_borderStyle: boolean, duplicated_shadow: boolean, duplicated_enableHoverMode: boolean, duplicated_hoverModeArea: boolean): boolean {
        if ((!duplicated_title) && (value?.hasOwnProperty("title"))) {
            return true
        }
        else if ((!duplicated_message) && (value?.hasOwnProperty("message"))) {
            return true
        }
        else if ((!duplicated_sheets) && (value?.hasOwnProperty("sheets"))) {
            return true
        }
        else if ((!duplicated_subtitle) && (value?.hasOwnProperty("subtitle"))) {
            return true
        }
        else if ((!duplicated_confirm) && (value?.hasOwnProperty("confirm"))) {
            return true
        }
        else if ((!duplicated_cancel) && (value?.hasOwnProperty("cancel"))) {
            return true
        }
        else if ((!duplicated_autoCancel) && (value?.hasOwnProperty("autoCancel"))) {
            return true
        }
        else if ((!duplicated_alignment) && (value?.hasOwnProperty("alignment"))) {
            return true
        }
        else if ((!duplicated_offset) && (value?.hasOwnProperty("offset"))) {
            return true
        }
        else if ((!duplicated_maskRect) && (value?.hasOwnProperty("maskRect"))) {
            return true
        }
        else if ((!duplicated_showInSubWindow) && (value?.hasOwnProperty("showInSubWindow"))) {
            return true
        }
        else if ((!duplicated_isModal) && (value?.hasOwnProperty("isModal"))) {
            return true
        }
        else if ((!duplicated_backgroundColor) && (value?.hasOwnProperty("backgroundColor"))) {
            return true
        }
        else if ((!duplicated_backgroundBlurStyle) && (value?.hasOwnProperty("backgroundBlurStyle"))) {
            return true
        }
        else if ((!duplicated_onWillDismiss) && (value?.hasOwnProperty("onWillDismiss"))) {
            return true
        }
        else if ((!duplicated_transition) && (value?.hasOwnProperty("transition"))) {
            return true
        }
        else if ((!duplicated_cornerRadius) && (value?.hasOwnProperty("cornerRadius"))) {
            return true
        }
        else if ((!duplicated_width) && (value?.hasOwnProperty("width"))) {
            return true
        }
        else if ((!duplicated_height) && (value?.hasOwnProperty("height"))) {
            return true
        }
        else if ((!duplicated_borderWidth) && (value?.hasOwnProperty("borderWidth"))) {
            return true
        }
        else if ((!duplicated_borderColor) && (value?.hasOwnProperty("borderColor"))) {
            return true
        }
        else if ((!duplicated_borderStyle) && (value?.hasOwnProperty("borderStyle"))) {
            return true
        }
        else if ((!duplicated_shadow) && (value?.hasOwnProperty("shadow"))) {
            return true
        }
        else if ((!duplicated_enableHoverMode) && (value?.hasOwnProperty("enableHoverMode"))) {
            return true
        }
        else if ((!duplicated_hoverModeArea) && (value?.hasOwnProperty("hoverModeArea"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ActionSheetOptions")
        }
    }
    static isAdaptiveColor(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (AdaptiveColor.DEFAULT)) {
            return true
        }
        else if ((value) === (AdaptiveColor.AVERAGE)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof AdaptiveColor")
        }
    }
    static isAdsBlockedDetails(value: object|string|number|undefined|null|boolean, duplicated_url: boolean, duplicated_adsBlocked: boolean): boolean {
        if ((!duplicated_url) && (value?.hasOwnProperty("url"))) {
            return true
        }
        else if ((!duplicated_adsBlocked) && (value?.hasOwnProperty("adsBlocked"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof AdsBlockedDetails")
        }
    }
    static isAffinity(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (Affinity.UPSTREAM)) {
            return true
        }
        else if ((value) === (Affinity.DOWNSTREAM)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof Affinity")
        }
    }
    static isAlertDialog(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof AlertDialog")
    }
    static isAlertDialogButtonBaseOptions(value: object|string|number|undefined|null|boolean, duplicated_enabled: boolean, duplicated_defaultFocus: boolean, duplicated_style: boolean, duplicated_value: boolean, duplicated_fontColor: boolean, duplicated_backgroundColor: boolean, duplicated_action: boolean): boolean {
        if ((!duplicated_value) && (value?.hasOwnProperty("value"))) {
            return true
        }
        else if ((!duplicated_action) && (value?.hasOwnProperty("action"))) {
            return true
        }
        else if ((!duplicated_enabled) && (value?.hasOwnProperty("enabled"))) {
            return true
        }
        else if ((!duplicated_defaultFocus) && (value?.hasOwnProperty("defaultFocus"))) {
            return true
        }
        else if ((!duplicated_style) && (value?.hasOwnProperty("style"))) {
            return true
        }
        else if ((!duplicated_fontColor) && (value?.hasOwnProperty("fontColor"))) {
            return true
        }
        else if ((!duplicated_backgroundColor) && (value?.hasOwnProperty("backgroundColor"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof AlertDialogButtonBaseOptions")
        }
    }
    static isAlertDialogButtonOptions(value: object|string|number|undefined|null|boolean, duplicated_primary: boolean): boolean {
        if ((!duplicated_primary) && (value?.hasOwnProperty("primary"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof AlertDialogButtonOptions")
        }
    }
    static isAlertDialogParam(value: object|string|number|undefined|null|boolean, duplicated_title: boolean, duplicated_subtitle: boolean, duplicated_message: boolean, duplicated_autoCancel: boolean, duplicated_cancel: boolean, duplicated_alignment: boolean, duplicated_offset: boolean, duplicated_gridCount: boolean, duplicated_maskRect: boolean, duplicated_showInSubWindow: boolean, duplicated_isModal: boolean, duplicated_backgroundColor: boolean, duplicated_backgroundBlurStyle: boolean, duplicated_onWillDismiss: boolean, duplicated_transition: boolean, duplicated_cornerRadius: boolean, duplicated_width: boolean, duplicated_height: boolean, duplicated_borderWidth: boolean, duplicated_borderColor: boolean, duplicated_borderStyle: boolean, duplicated_shadow: boolean, duplicated_textStyle: boolean, duplicated_enableHoverMode: boolean, duplicated_hoverModeArea: boolean): boolean {
        if ((!duplicated_message) && (value?.hasOwnProperty("message"))) {
            return true
        }
        else if ((!duplicated_title) && (value?.hasOwnProperty("title"))) {
            return true
        }
        else if ((!duplicated_subtitle) && (value?.hasOwnProperty("subtitle"))) {
            return true
        }
        else if ((!duplicated_autoCancel) && (value?.hasOwnProperty("autoCancel"))) {
            return true
        }
        else if ((!duplicated_cancel) && (value?.hasOwnProperty("cancel"))) {
            return true
        }
        else if ((!duplicated_alignment) && (value?.hasOwnProperty("alignment"))) {
            return true
        }
        else if ((!duplicated_offset) && (value?.hasOwnProperty("offset"))) {
            return true
        }
        else if ((!duplicated_gridCount) && (value?.hasOwnProperty("gridCount"))) {
            return true
        }
        else if ((!duplicated_maskRect) && (value?.hasOwnProperty("maskRect"))) {
            return true
        }
        else if ((!duplicated_showInSubWindow) && (value?.hasOwnProperty("showInSubWindow"))) {
            return true
        }
        else if ((!duplicated_isModal) && (value?.hasOwnProperty("isModal"))) {
            return true
        }
        else if ((!duplicated_backgroundColor) && (value?.hasOwnProperty("backgroundColor"))) {
            return true
        }
        else if ((!duplicated_backgroundBlurStyle) && (value?.hasOwnProperty("backgroundBlurStyle"))) {
            return true
        }
        else if ((!duplicated_onWillDismiss) && (value?.hasOwnProperty("onWillDismiss"))) {
            return true
        }
        else if ((!duplicated_transition) && (value?.hasOwnProperty("transition"))) {
            return true
        }
        else if ((!duplicated_cornerRadius) && (value?.hasOwnProperty("cornerRadius"))) {
            return true
        }
        else if ((!duplicated_width) && (value?.hasOwnProperty("width"))) {
            return true
        }
        else if ((!duplicated_height) && (value?.hasOwnProperty("height"))) {
            return true
        }
        else if ((!duplicated_borderWidth) && (value?.hasOwnProperty("borderWidth"))) {
            return true
        }
        else if ((!duplicated_borderColor) && (value?.hasOwnProperty("borderColor"))) {
            return true
        }
        else if ((!duplicated_borderStyle) && (value?.hasOwnProperty("borderStyle"))) {
            return true
        }
        else if ((!duplicated_shadow) && (value?.hasOwnProperty("shadow"))) {
            return true
        }
        else if ((!duplicated_textStyle) && (value?.hasOwnProperty("textStyle"))) {
            return true
        }
        else if ((!duplicated_enableHoverMode) && (value?.hasOwnProperty("enableHoverMode"))) {
            return true
        }
        else if ((!duplicated_hoverModeArea) && (value?.hasOwnProperty("hoverModeArea"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof AlertDialogParam")
        }
    }
    static isAlertDialogParamWithButtons(value: object|string|number|undefined|null|boolean, duplicated_primaryButton: boolean, duplicated_secondaryButton: boolean): boolean {
        if ((!duplicated_primaryButton) && (value?.hasOwnProperty("primaryButton"))) {
            return true
        }
        else if ((!duplicated_secondaryButton) && (value?.hasOwnProperty("secondaryButton"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof AlertDialogParamWithButtons")
        }
    }
    static isAlertDialogParamWithConfirm(value: object|string|number|undefined|null|boolean, duplicated_confirm: boolean): boolean {
        if ((!duplicated_confirm) && (value?.hasOwnProperty("confirm"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof AlertDialogParamWithConfirm")
        }
    }
    static isAlertDialogParamWithOptions(value: object|string|number|undefined|null|boolean, duplicated_buttons: boolean, duplicated_buttonDirection: boolean): boolean {
        if ((!duplicated_buttons) && (value?.hasOwnProperty("buttons"))) {
            return true
        }
        else if ((!duplicated_buttonDirection) && (value?.hasOwnProperty("buttonDirection"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof AlertDialogParamWithOptions")
        }
    }
    static isAlignment(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (Alignment.TopStart)) {
            return true
        }
        else if ((value) === (Alignment.Top)) {
            return true
        }
        else if ((value) === (Alignment.TopEnd)) {
            return true
        }
        else if ((value) === (Alignment.Start)) {
            return true
        }
        else if ((value) === (Alignment.Center)) {
            return true
        }
        else if ((value) === (Alignment.End)) {
            return true
        }
        else if ((value) === (Alignment.BottomStart)) {
            return true
        }
        else if ((value) === (Alignment.Bottom)) {
            return true
        }
        else if ((value) === (Alignment.BottomEnd)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof Alignment")
        }
    }
    static isAlignRuleOption(value: object|string|number|undefined|null|boolean, duplicated_left: boolean, duplicated_right: boolean, duplicated_middle: boolean, duplicated_top: boolean, duplicated_bottom: boolean, duplicated_center: boolean, duplicated_bias: boolean): boolean {
        if ((!duplicated_left) && (value?.hasOwnProperty("left"))) {
            return true
        }
        else if ((!duplicated_right) && (value?.hasOwnProperty("right"))) {
            return true
        }
        else if ((!duplicated_middle) && (value?.hasOwnProperty("middle"))) {
            return true
        }
        else if ((!duplicated_top) && (value?.hasOwnProperty("top"))) {
            return true
        }
        else if ((!duplicated_bottom) && (value?.hasOwnProperty("bottom"))) {
            return true
        }
        else if ((!duplicated_center) && (value?.hasOwnProperty("center"))) {
            return true
        }
        else if ((!duplicated_bias) && (value?.hasOwnProperty("bias"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof AlignRuleOption")
        }
    }
    static isAlphabetIndexerAttribute(value: object|string|number|undefined|null|boolean, duplicated_onSelected: boolean, duplicated_color: boolean, duplicated_selectedColor: boolean, duplicated_popupColor: boolean, duplicated_selectedBackgroundColor: boolean, duplicated_popupBackground: boolean, duplicated_popupSelectedColor: boolean, duplicated_popupUnselectedColor: boolean, duplicated_popupItemBackgroundColor: boolean, duplicated_usingPopup: boolean, duplicated_selectedFont: boolean, duplicated_popupFont: boolean, duplicated_popupItemFont: boolean, duplicated_itemSize: boolean, duplicated_font: boolean, duplicated_onSelect: boolean, duplicated_onRequestPopupData: boolean, duplicated_onPopupSelect: boolean, duplicated_selected: boolean, duplicated_popupPosition: boolean, duplicated_autoCollapse: boolean, duplicated_popupItemBorderRadius: boolean, duplicated_itemBorderRadius: boolean, duplicated_popupBackgroundBlurStyle: boolean, duplicated_popupTitleBackground: boolean, duplicated_enableHapticFeedback: boolean): boolean {
        if ((!duplicated_onSelected) && (value?.hasOwnProperty("onSelected"))) {
            return true
        }
        else if ((!duplicated_color) && (value?.hasOwnProperty("color"))) {
            return true
        }
        else if ((!duplicated_selectedColor) && (value?.hasOwnProperty("selectedColor"))) {
            return true
        }
        else if ((!duplicated_popupColor) && (value?.hasOwnProperty("popupColor"))) {
            return true
        }
        else if ((!duplicated_selectedBackgroundColor) && (value?.hasOwnProperty("selectedBackgroundColor"))) {
            return true
        }
        else if ((!duplicated_popupBackground) && (value?.hasOwnProperty("popupBackground"))) {
            return true
        }
        else if ((!duplicated_popupSelectedColor) && (value?.hasOwnProperty("popupSelectedColor"))) {
            return true
        }
        else if ((!duplicated_popupUnselectedColor) && (value?.hasOwnProperty("popupUnselectedColor"))) {
            return true
        }
        else if ((!duplicated_popupItemBackgroundColor) && (value?.hasOwnProperty("popupItemBackgroundColor"))) {
            return true
        }
        else if ((!duplicated_usingPopup) && (value?.hasOwnProperty("usingPopup"))) {
            return true
        }
        else if ((!duplicated_selectedFont) && (value?.hasOwnProperty("selectedFont"))) {
            return true
        }
        else if ((!duplicated_popupFont) && (value?.hasOwnProperty("popupFont"))) {
            return true
        }
        else if ((!duplicated_popupItemFont) && (value?.hasOwnProperty("popupItemFont"))) {
            return true
        }
        else if ((!duplicated_itemSize) && (value?.hasOwnProperty("itemSize"))) {
            return true
        }
        else if ((!duplicated_font) && (value?.hasOwnProperty("font"))) {
            return true
        }
        else if ((!duplicated_onSelect) && (value?.hasOwnProperty("onSelect"))) {
            return true
        }
        else if ((!duplicated_onRequestPopupData) && (value?.hasOwnProperty("onRequestPopupData"))) {
            return true
        }
        else if ((!duplicated_onPopupSelect) && (value?.hasOwnProperty("onPopupSelect"))) {
            return true
        }
        else if ((!duplicated_selected) && (value?.hasOwnProperty("selected"))) {
            return true
        }
        else if ((!duplicated_popupPosition) && (value?.hasOwnProperty("popupPosition"))) {
            return true
        }
        else if ((!duplicated_autoCollapse) && (value?.hasOwnProperty("autoCollapse"))) {
            return true
        }
        else if ((!duplicated_popupItemBorderRadius) && (value?.hasOwnProperty("popupItemBorderRadius"))) {
            return true
        }
        else if ((!duplicated_itemBorderRadius) && (value?.hasOwnProperty("itemBorderRadius"))) {
            return true
        }
        else if ((!duplicated_popupBackgroundBlurStyle) && (value?.hasOwnProperty("popupBackgroundBlurStyle"))) {
            return true
        }
        else if ((!duplicated_popupTitleBackground) && (value?.hasOwnProperty("popupTitleBackground"))) {
            return true
        }
        else if ((!duplicated_enableHapticFeedback) && (value?.hasOwnProperty("enableHapticFeedback"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof AlphabetIndexerAttribute")
        }
    }
    static isAlphabetIndexerInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof AlphabetIndexerInterface")
    }
    static isAlphabetIndexerOptions(value: object|string|number|undefined|null|boolean, duplicated_arrayValue: boolean, duplicated_selected: boolean): boolean {
        if ((!duplicated_arrayValue) && (value?.hasOwnProperty("arrayValue"))) {
            return true
        }
        else if ((!duplicated_selected) && (value?.hasOwnProperty("selected"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof AlphabetIndexerOptions")
        }
    }
    static isAnimatableArithmetic(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof AnimatableArithmetic")
    }
    static isAnimatedDrawableDescriptor(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof AnimatedDrawableDescriptor")
    }
    static isAnimateParam(value: object|string|number|undefined|null|boolean, duplicated_duration: boolean, duplicated_tempo: boolean, duplicated_curve: boolean, duplicated_delay: boolean, duplicated_iterations: boolean, duplicated_playMode: boolean, duplicated_onFinish: boolean, duplicated_finishCallbackType: boolean, duplicated_expectedFrameRateRange: boolean): boolean {
        if ((!duplicated_duration) && (value?.hasOwnProperty("duration"))) {
            return true
        }
        else if ((!duplicated_tempo) && (value?.hasOwnProperty("tempo"))) {
            return true
        }
        else if ((!duplicated_curve) && (value?.hasOwnProperty("curve"))) {
            return true
        }
        else if ((!duplicated_delay) && (value?.hasOwnProperty("delay"))) {
            return true
        }
        else if ((!duplicated_iterations) && (value?.hasOwnProperty("iterations"))) {
            return true
        }
        else if ((!duplicated_playMode) && (value?.hasOwnProperty("playMode"))) {
            return true
        }
        else if ((!duplicated_onFinish) && (value?.hasOwnProperty("onFinish"))) {
            return true
        }
        else if ((!duplicated_finishCallbackType) && (value?.hasOwnProperty("finishCallbackType"))) {
            return true
        }
        else if ((!duplicated_expectedFrameRateRange) && (value?.hasOwnProperty("expectedFrameRateRange"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof AnimateParam")
        }
    }
    static isAnimationExtender(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof AnimationExtender")
    }
    static isAnimationMode(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (AnimationMode.CONTENT_FIRST)) {
            return true
        }
        else if ((value) === (AnimationMode.ACTION_FIRST)) {
            return true
        }
        else if ((value) === (AnimationMode.NO_ANIMATION)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof AnimationMode")
        }
    }
    static isAnimationOptions(value: object|string|number|undefined|null|boolean, duplicated_duration: boolean, duplicated_iterations: boolean): boolean {
        if ((!duplicated_duration) && (value?.hasOwnProperty("duration"))) {
            return true
        }
        else if ((!duplicated_iterations) && (value?.hasOwnProperty("iterations"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof AnimationOptions")
        }
    }
    static isAnimationStatus(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (AnimationStatus.Initial)) {
            return true
        }
        else if ((value) === (AnimationStatus.Running)) {
            return true
        }
        else if ((value) === (AnimationStatus.Paused)) {
            return true
        }
        else if ((value) === (AnimationStatus.Stopped)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof AnimationStatus")
        }
    }
    static isAnimatorAttribute(value: object|string|number|undefined|null|boolean, duplicated_state: boolean, duplicated_duration: boolean, duplicated_curve: boolean, duplicated_delay: boolean, duplicated_fillMode: boolean, duplicated_iterations: boolean, duplicated_playMode: boolean, duplicated_motion: boolean, duplicated_onStart: boolean, duplicated_onPause: boolean, duplicated_onRepeat: boolean, duplicated_onCancel: boolean, duplicated_onFinish: boolean, duplicated_onFrame: boolean): boolean {
        if ((!duplicated_state) && (value?.hasOwnProperty("state"))) {
            return true
        }
        else if ((!duplicated_duration) && (value?.hasOwnProperty("duration"))) {
            return true
        }
        else if ((!duplicated_curve) && (value?.hasOwnProperty("curve"))) {
            return true
        }
        else if ((!duplicated_delay) && (value?.hasOwnProperty("delay"))) {
            return true
        }
        else if ((!duplicated_fillMode) && (value?.hasOwnProperty("fillMode"))) {
            return true
        }
        else if ((!duplicated_iterations) && (value?.hasOwnProperty("iterations"))) {
            return true
        }
        else if ((!duplicated_playMode) && (value?.hasOwnProperty("playMode"))) {
            return true
        }
        else if ((!duplicated_motion) && (value?.hasOwnProperty("motion"))) {
            return true
        }
        else if ((!duplicated_onStart) && (value?.hasOwnProperty("onStart"))) {
            return true
        }
        else if ((!duplicated_onPause) && (value?.hasOwnProperty("onPause"))) {
            return true
        }
        else if ((!duplicated_onRepeat) && (value?.hasOwnProperty("onRepeat"))) {
            return true
        }
        else if ((!duplicated_onCancel) && (value?.hasOwnProperty("onCancel"))) {
            return true
        }
        else if ((!duplicated_onFinish) && (value?.hasOwnProperty("onFinish"))) {
            return true
        }
        else if ((!duplicated_onFrame) && (value?.hasOwnProperty("onFrame"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof AnimatorAttribute")
        }
    }
    static isAnimatorInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof AnimatorInterface")
    }
    static isAppearSymbolEffect(value: object|string|number|undefined|null|boolean, duplicated_scope: boolean): boolean {
        if ((!duplicated_scope) && (value?.hasOwnProperty("scope"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof AppearSymbolEffect")
        }
    }
    static isAppRotation(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (AppRotation.ROTATION_0)) {
            return true
        }
        else if ((value) === (AppRotation.ROTATION_90)) {
            return true
        }
        else if ((value) === (AppRotation.ROTATION_180)) {
            return true
        }
        else if ((value) === (AppRotation.ROTATION_270)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof AppRotation")
        }
    }
    static isArea(value: object|string|number|undefined|null|boolean, duplicated_width: boolean, duplicated_height: boolean, duplicated_position: boolean, duplicated_globalPosition: boolean): boolean {
        if ((!duplicated_width) && (value?.hasOwnProperty("width"))) {
            return true
        }
        else if ((!duplicated_height) && (value?.hasOwnProperty("height"))) {
            return true
        }
        else if ((!duplicated_position) && (value?.hasOwnProperty("position"))) {
            return true
        }
        else if ((!duplicated_globalPosition) && (value?.hasOwnProperty("globalPosition"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof Area")
        }
    }
    static isArrowPointPosition(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (ArrowPointPosition.START)) {
            return true
        }
        else if ((value) === (ArrowPointPosition.CENTER)) {
            return true
        }
        else if ((value) === (ArrowPointPosition.END)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ArrowPointPosition")
        }
    }
    static isArrowPosition(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (ArrowPosition.END)) {
            return true
        }
        else if ((value) === (ArrowPosition.START)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ArrowPosition")
        }
    }
    static isArrowStyle(value: object|string|number|undefined|null|boolean, duplicated_showBackground: boolean, duplicated_isSidebarMiddle: boolean, duplicated_backgroundSize: boolean, duplicated_backgroundColor: boolean, duplicated_arrowSize: boolean, duplicated_arrowColor: boolean): boolean {
        if ((!duplicated_showBackground) && (value?.hasOwnProperty("showBackground"))) {
            return true
        }
        else if ((!duplicated_isSidebarMiddle) && (value?.hasOwnProperty("isSidebarMiddle"))) {
            return true
        }
        else if ((!duplicated_backgroundSize) && (value?.hasOwnProperty("backgroundSize"))) {
            return true
        }
        else if ((!duplicated_backgroundColor) && (value?.hasOwnProperty("backgroundColor"))) {
            return true
        }
        else if ((!duplicated_arrowSize) && (value?.hasOwnProperty("arrowSize"))) {
            return true
        }
        else if ((!duplicated_arrowColor) && (value?.hasOwnProperty("arrowColor"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ArrowStyle")
        }
    }
    static isASTCResource(value: object|string|number|undefined|null|boolean, duplicated_sources: boolean, duplicated_column: boolean): boolean {
        if ((!duplicated_sources) && (value?.hasOwnProperty("sources"))) {
            return true
        }
        else if ((!duplicated_column) && (value?.hasOwnProperty("column"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ASTCResource")
        }
    }
    static isAttributeModifier(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof AttributeModifier<object>")
    }
    static isAxis(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (Axis.Vertical)) {
            return true
        }
        else if ((value) === (Axis.Horizontal)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof Axis")
        }
    }
    static isBackgroundBlurStyleOptions(value: object|string|number|undefined|null|boolean, duplicated_policy: boolean, duplicated_inactiveColor: boolean): boolean {
        if ((!duplicated_policy) && (value?.hasOwnProperty("policy"))) {
            return true
        }
        else if ((!duplicated_inactiveColor) && (value?.hasOwnProperty("inactiveColor"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof BackgroundBlurStyleOptions")
        }
    }
    static isBackgroundBrightnessOptions(value: object|string|number|undefined|null|boolean, duplicated_rate: boolean, duplicated_lightUpDegree: boolean): boolean {
        if ((!duplicated_rate) && (value?.hasOwnProperty("rate"))) {
            return true
        }
        else if ((!duplicated_lightUpDegree) && (value?.hasOwnProperty("lightUpDegree"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof BackgroundBrightnessOptions")
        }
    }
    static isBackgroundColorStyle(value: object|string|number|undefined|null|boolean, duplicated_textBackgroundStyle: boolean): boolean {
        if ((!duplicated_textBackgroundStyle) && (value?.hasOwnProperty("textBackgroundStyle"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof BackgroundColorStyle")
        }
    }
    static isBackgroundEffectOptions(value: object|string|number|undefined|null|boolean, duplicated_radius: boolean, duplicated_saturation: boolean, duplicated_brightness: boolean, duplicated_color: boolean, duplicated_adaptiveColor: boolean, duplicated_blurOptions: boolean, duplicated_policy: boolean, duplicated_inactiveColor: boolean): boolean {
        if ((!duplicated_radius) && (value?.hasOwnProperty("radius"))) {
            return true
        }
        else if ((!duplicated_saturation) && (value?.hasOwnProperty("saturation"))) {
            return true
        }
        else if ((!duplicated_brightness) && (value?.hasOwnProperty("brightness"))) {
            return true
        }
        else if ((!duplicated_color) && (value?.hasOwnProperty("color"))) {
            return true
        }
        else if ((!duplicated_adaptiveColor) && (value?.hasOwnProperty("adaptiveColor"))) {
            return true
        }
        else if ((!duplicated_blurOptions) && (value?.hasOwnProperty("blurOptions"))) {
            return true
        }
        else if ((!duplicated_policy) && (value?.hasOwnProperty("policy"))) {
            return true
        }
        else if ((!duplicated_inactiveColor) && (value?.hasOwnProperty("inactiveColor"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof BackgroundEffectOptions")
        }
    }
    static isBadgeAttribute(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof BadgeAttribute")
    }
    static isBadgeInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof BadgeInterface")
    }
    static isBadgeParam(value: object|string|number|undefined|null|boolean, duplicated_position: boolean, duplicated_style: boolean): boolean {
        if ((!duplicated_style) && (value?.hasOwnProperty("style"))) {
            return true
        }
        else if ((!duplicated_position) && (value?.hasOwnProperty("position"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof BadgeParam")
        }
    }
    static isBadgeParamWithNumber(value: object|string|number|undefined|null|boolean, duplicated_count: boolean, duplicated_maxCount: boolean): boolean {
        if ((!duplicated_count) && (value?.hasOwnProperty("count"))) {
            return true
        }
        else if ((!duplicated_maxCount) && (value?.hasOwnProperty("maxCount"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof BadgeParamWithNumber")
        }
    }
    static isBadgeParamWithString(value: object|string|number|undefined|null|boolean, duplicated_value: boolean): boolean {
        if ((!duplicated_value) && (value?.hasOwnProperty("value"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof BadgeParamWithString")
        }
    }
    static isBadgePosition(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (BadgePosition.RightTop)) {
            return true
        }
        else if ((value) === (BadgePosition.Right)) {
            return true
        }
        else if ((value) === (BadgePosition.Left)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof BadgePosition")
        }
    }
    static isBadgeStyle(value: object|string|number|undefined|null|boolean, duplicated_color: boolean, duplicated_fontSize: boolean, duplicated_badgeSize: boolean, duplicated_badgeColor: boolean, duplicated_borderColor: boolean, duplicated_borderWidth: boolean, duplicated_fontWeight: boolean): boolean {
        if ((!duplicated_color) && (value?.hasOwnProperty("color"))) {
            return true
        }
        else if ((!duplicated_fontSize) && (value?.hasOwnProperty("fontSize"))) {
            return true
        }
        else if ((!duplicated_badgeSize) && (value?.hasOwnProperty("badgeSize"))) {
            return true
        }
        else if ((!duplicated_badgeColor) && (value?.hasOwnProperty("badgeColor"))) {
            return true
        }
        else if ((!duplicated_borderColor) && (value?.hasOwnProperty("borderColor"))) {
            return true
        }
        else if ((!duplicated_borderWidth) && (value?.hasOwnProperty("borderWidth"))) {
            return true
        }
        else if ((!duplicated_fontWeight) && (value?.hasOwnProperty("fontWeight"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof BadgeStyle")
        }
    }
    static isBarGridColumnOptions(value: object|string|number|undefined|null|boolean, duplicated_sm: boolean, duplicated_md: boolean, duplicated_lg: boolean, duplicated_margin: boolean, duplicated_gutter: boolean): boolean {
        if ((!duplicated_sm) && (value?.hasOwnProperty("sm"))) {
            return true
        }
        else if ((!duplicated_md) && (value?.hasOwnProperty("md"))) {
            return true
        }
        else if ((!duplicated_lg) && (value?.hasOwnProperty("lg"))) {
            return true
        }
        else if ((!duplicated_margin) && (value?.hasOwnProperty("margin"))) {
            return true
        }
        else if ((!duplicated_gutter) && (value?.hasOwnProperty("gutter"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof BarGridColumnOptions")
        }
    }
    static isBarMode(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (BarMode.Scrollable)) {
            return true
        }
        else if ((value) === (BarMode.Fixed)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof BarMode")
        }
    }
    static isBarPosition(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (BarPosition.Start)) {
            return true
        }
        else if ((value) === (BarPosition.End)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof BarPosition")
        }
    }
    static isBarrierDirection(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (BarrierDirection.LEFT)) {
            return true
        }
        else if ((value) === (BarrierDirection.RIGHT)) {
            return true
        }
        else if ((value) === (BarrierDirection.TOP)) {
            return true
        }
        else if ((value) === (BarrierDirection.BOTTOM)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof BarrierDirection")
        }
    }
    static isBarrierStyle(value: object|string|number|undefined|null|boolean, duplicated_id: boolean, duplicated_direction: boolean, duplicated_referencedId: boolean): boolean {
        if ((!duplicated_id) && (value?.hasOwnProperty("id"))) {
            return true
        }
        else if ((!duplicated_direction) && (value?.hasOwnProperty("direction"))) {
            return true
        }
        else if ((!duplicated_referencedId) && (value?.hasOwnProperty("referencedId"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof BarrierStyle")
        }
    }
    static isBarState(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (BarState.Off)) {
            return true
        }
        else if ((value) === (BarState.Auto)) {
            return true
        }
        else if ((value) === (BarState.On)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof BarState")
        }
    }
    static isBarStyle(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (BarStyle.STANDARD)) {
            return true
        }
        else if ((value) === (BarStyle.STACK)) {
            return true
        }
        else if ((value) === (BarStyle.SAFE_AREA_PADDING)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof BarStyle")
        }
    }
    static isBaseEvent(value: object|string|number|undefined|null|boolean, duplicated_target: boolean, duplicated_timestamp: boolean, duplicated_source: boolean, duplicated_axisHorizontal: boolean, duplicated_axisVertical: boolean, duplicated_axisPinch: boolean, duplicated_pressure: boolean, duplicated_tiltX: boolean, duplicated_tiltY: boolean, duplicated_sourceTool: boolean, duplicated_deviceId: boolean): boolean {
        if ((!duplicated_target) && (value?.hasOwnProperty("target"))) {
            return true
        }
        else if ((!duplicated_timestamp) && (value?.hasOwnProperty("timestamp"))) {
            return true
        }
        else if ((!duplicated_source) && (value?.hasOwnProperty("source"))) {
            return true
        }
        else if ((!duplicated_pressure) && (value?.hasOwnProperty("pressure"))) {
            return true
        }
        else if ((!duplicated_tiltX) && (value?.hasOwnProperty("tiltX"))) {
            return true
        }
        else if ((!duplicated_tiltY) && (value?.hasOwnProperty("tiltY"))) {
            return true
        }
        else if ((!duplicated_sourceTool) && (value?.hasOwnProperty("sourceTool"))) {
            return true
        }
        else if ((!duplicated_axisHorizontal) && (value?.hasOwnProperty("axisHorizontal"))) {
            return true
        }
        else if ((!duplicated_axisVertical) && (value?.hasOwnProperty("axisVertical"))) {
            return true
        }
        else if ((!duplicated_axisPinch) && (value?.hasOwnProperty("axisPinch"))) {
            return true
        }
        else if ((!duplicated_deviceId) && (value?.hasOwnProperty("deviceId"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof BaseEvent")
        }
    }
    static isBaseGestureEvent(value: object|string|number|undefined|null|boolean, duplicated_fingerList: boolean): boolean {
        if ((!duplicated_fingerList) && (value?.hasOwnProperty("fingerList"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof BaseGestureEvent")
        }
    }
    static isBaselineOffsetStyle(value: object|string|number|undefined|null|boolean, duplicated_baselineOffset: boolean): boolean {
        if ((!duplicated_baselineOffset) && (value?.hasOwnProperty("baselineOffset"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof BaselineOffsetStyle")
        }
    }
    static isBaseShape(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof BaseShape")
    }
    static isBaseSpan(value: object|string|number|undefined|null|boolean, duplicated_textBackgroundStyle: boolean, duplicated_baselineOffset: boolean): boolean {
        if ((!duplicated_textBackgroundStyle) && (value?.hasOwnProperty("textBackgroundStyle"))) {
            return true
        }
        else if ((!duplicated_baselineOffset) && (value?.hasOwnProperty("baselineOffset"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof BaseSpan")
        }
    }
    static isBias(value: object|string|number|undefined|null|boolean, duplicated_horizontal: boolean, duplicated_vertical: boolean): boolean {
        if ((!duplicated_horizontal) && (value?.hasOwnProperty("horizontal"))) {
            return true
        }
        else if ((!duplicated_vertical) && (value?.hasOwnProperty("vertical"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof Bias")
        }
    }
    static isBindOptions(value: object|string|number|undefined|null|boolean, duplicated_backgroundColor: boolean, duplicated_onAppear: boolean, duplicated_onDisappear: boolean, duplicated_onWillAppear: boolean, duplicated_onWillDisappear: boolean): boolean {
        if ((!duplicated_backgroundColor) && (value?.hasOwnProperty("backgroundColor"))) {
            return true
        }
        else if ((!duplicated_onAppear) && (value?.hasOwnProperty("onAppear"))) {
            return true
        }
        else if ((!duplicated_onDisappear) && (value?.hasOwnProperty("onDisappear"))) {
            return true
        }
        else if ((!duplicated_onWillAppear) && (value?.hasOwnProperty("onWillAppear"))) {
            return true
        }
        else if ((!duplicated_onWillDisappear) && (value?.hasOwnProperty("onWillDisappear"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof BindOptions")
        }
    }
    static isBlankAttribute(value: object|string|number|undefined|null|boolean, duplicated_color: boolean): boolean {
        if ((!duplicated_color) && (value?.hasOwnProperty("color"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof BlankAttribute")
        }
    }
    static isBlankInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof BlankInterface")
    }
    static isBlendApplyType(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (BlendApplyType.FAST)) {
            return true
        }
        else if ((value) === (BlendApplyType.OFFSCREEN)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof BlendApplyType")
        }
    }
    static isBlender(value: object|string|number|undefined|null|boolean, duplicated__BlenderStub: boolean): boolean {
        if ((!duplicated__BlenderStub) && (value?.hasOwnProperty("_BlenderStub"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof Blender")
        }
    }
    static isBlendMode(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (BlendMode.NONE)) {
            return true
        }
        else if ((value) === (BlendMode.CLEAR)) {
            return true
        }
        else if ((value) === (BlendMode.SRC)) {
            return true
        }
        else if ((value) === (BlendMode.DST)) {
            return true
        }
        else if ((value) === (BlendMode.SRC_OVER)) {
            return true
        }
        else if ((value) === (BlendMode.DST_OVER)) {
            return true
        }
        else if ((value) === (BlendMode.SRC_IN)) {
            return true
        }
        else if ((value) === (BlendMode.DST_IN)) {
            return true
        }
        else if ((value) === (BlendMode.SRC_OUT)) {
            return true
        }
        else if ((value) === (BlendMode.DST_OUT)) {
            return true
        }
        else if ((value) === (BlendMode.SRC_ATOP)) {
            return true
        }
        else if ((value) === (BlendMode.DST_ATOP)) {
            return true
        }
        else if ((value) === (BlendMode.XOR)) {
            return true
        }
        else if ((value) === (BlendMode.PLUS)) {
            return true
        }
        else if ((value) === (BlendMode.MODULATE)) {
            return true
        }
        else if ((value) === (BlendMode.SCREEN)) {
            return true
        }
        else if ((value) === (BlendMode.OVERLAY)) {
            return true
        }
        else if ((value) === (BlendMode.DARKEN)) {
            return true
        }
        else if ((value) === (BlendMode.LIGHTEN)) {
            return true
        }
        else if ((value) === (BlendMode.COLOR_DODGE)) {
            return true
        }
        else if ((value) === (BlendMode.COLOR_BURN)) {
            return true
        }
        else if ((value) === (BlendMode.HARD_LIGHT)) {
            return true
        }
        else if ((value) === (BlendMode.SOFT_LIGHT)) {
            return true
        }
        else if ((value) === (BlendMode.DIFFERENCE)) {
            return true
        }
        else if ((value) === (BlendMode.EXCLUSION)) {
            return true
        }
        else if ((value) === (BlendMode.MULTIPLY)) {
            return true
        }
        else if ((value) === (BlendMode.HUE)) {
            return true
        }
        else if ((value) === (BlendMode.SATURATION)) {
            return true
        }
        else if ((value) === (BlendMode.COLOR)) {
            return true
        }
        else if ((value) === (BlendMode.LUMINOSITY)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof BlendMode")
        }
    }
    static isBlurOptions(value: object|string|number|undefined|null|boolean, duplicated_grayscale: boolean): boolean {
        if ((!duplicated_grayscale) && (value?.hasOwnProperty("grayscale"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof BlurOptions")
        }
    }
    static isBlurStyle(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (BlurStyle.Thin)) {
            return true
        }
        else if ((value) === (BlurStyle.Regular)) {
            return true
        }
        else if ((value) === (BlurStyle.Thick)) {
            return true
        }
        else if ((value) === (BlurStyle.BACKGROUND_THIN)) {
            return true
        }
        else if ((value) === (BlurStyle.BACKGROUND_REGULAR)) {
            return true
        }
        else if ((value) === (BlurStyle.BACKGROUND_THICK)) {
            return true
        }
        else if ((value) === (BlurStyle.BACKGROUND_ULTRA_THICK)) {
            return true
        }
        else if ((value) === (BlurStyle.NONE)) {
            return true
        }
        else if ((value) === (BlurStyle.COMPONENT_ULTRA_THIN)) {
            return true
        }
        else if ((value) === (BlurStyle.COMPONENT_THIN)) {
            return true
        }
        else if ((value) === (BlurStyle.COMPONENT_REGULAR)) {
            return true
        }
        else if ((value) === (BlurStyle.COMPONENT_THICK)) {
            return true
        }
        else if ((value) === (BlurStyle.COMPONENT_ULTRA_THICK)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof BlurStyle")
        }
    }
    static isBlurStyleActivePolicy(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (BlurStyleActivePolicy.FOLLOWS_WINDOW_ACTIVE_STATE)) {
            return true
        }
        else if ((value) === (BlurStyleActivePolicy.ALWAYS_ACTIVE)) {
            return true
        }
        else if ((value) === (BlurStyleActivePolicy.ALWAYS_INACTIVE)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof BlurStyleActivePolicy")
        }
    }
    static isBlurStyleOptions(value: object|string|number|undefined|null|boolean, duplicated_colorMode: boolean, duplicated_adaptiveColor: boolean, duplicated_scale: boolean, duplicated_blurOptions: boolean): boolean {
        if ((!duplicated_colorMode) && (value?.hasOwnProperty("colorMode"))) {
            return true
        }
        else if ((!duplicated_adaptiveColor) && (value?.hasOwnProperty("adaptiveColor"))) {
            return true
        }
        else if ((!duplicated_scale) && (value?.hasOwnProperty("scale"))) {
            return true
        }
        else if ((!duplicated_blurOptions) && (value?.hasOwnProperty("blurOptions"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof BlurStyleOptions")
        }
    }
    static isBoardStyle(value: object|string|number|undefined|null|boolean, duplicated_borderRadius: boolean): boolean {
        if ((!duplicated_borderRadius) && (value?.hasOwnProperty("borderRadius"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof BoardStyle")
        }
    }
    static isBorderImageOption(value: object|string|number|undefined|null|boolean, duplicated_slice: boolean, duplicated_repeat: boolean, duplicated_source: boolean, duplicated_width: boolean, duplicated_outset: boolean, duplicated_fill: boolean): boolean {
        if ((!duplicated_slice) && (value?.hasOwnProperty("slice"))) {
            return true
        }
        else if ((!duplicated_repeat) && (value?.hasOwnProperty("repeat"))) {
            return true
        }
        else if ((!duplicated_source) && (value?.hasOwnProperty("source"))) {
            return true
        }
        else if ((!duplicated_width) && (value?.hasOwnProperty("width"))) {
            return true
        }
        else if ((!duplicated_outset) && (value?.hasOwnProperty("outset"))) {
            return true
        }
        else if ((!duplicated_fill) && (value?.hasOwnProperty("fill"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof BorderImageOption")
        }
    }
    static isBorderOptions(value: object|string|number|undefined|null|boolean, duplicated_width: boolean, duplicated_color: boolean, duplicated_radius: boolean, duplicated_style: boolean, duplicated_dashGap: boolean, duplicated_dashWidth: boolean): boolean {
        if ((!duplicated_width) && (value?.hasOwnProperty("width"))) {
            return true
        }
        else if ((!duplicated_color) && (value?.hasOwnProperty("color"))) {
            return true
        }
        else if ((!duplicated_radius) && (value?.hasOwnProperty("radius"))) {
            return true
        }
        else if ((!duplicated_style) && (value?.hasOwnProperty("style"))) {
            return true
        }
        else if ((!duplicated_dashGap) && (value?.hasOwnProperty("dashGap"))) {
            return true
        }
        else if ((!duplicated_dashWidth) && (value?.hasOwnProperty("dashWidth"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof BorderOptions")
        }
    }
    static isBorderRadiuses(value: object|string|number|undefined|null|boolean, duplicated_topLeft: boolean, duplicated_topRight: boolean, duplicated_bottomLeft: boolean, duplicated_bottomRight: boolean): boolean {
        if ((!duplicated_topLeft) && (value?.hasOwnProperty("topLeft"))) {
            return true
        }
        else if ((!duplicated_topRight) && (value?.hasOwnProperty("topRight"))) {
            return true
        }
        else if ((!duplicated_bottomLeft) && (value?.hasOwnProperty("bottomLeft"))) {
            return true
        }
        else if ((!duplicated_bottomRight) && (value?.hasOwnProperty("bottomRight"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof BorderRadiuses")
        }
    }
    static isBorderStyle(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (BorderStyle.Dotted)) {
            return true
        }
        else if ((value) === (BorderStyle.Dashed)) {
            return true
        }
        else if ((value) === (BorderStyle.Solid)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof BorderStyle")
        }
    }
    static isBottomTabBarStyle(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof BottomTabBarStyle")
    }
    static isBounceSymbolEffect(value: object|string|number|undefined|null|boolean, duplicated_scope: boolean, duplicated_direction: boolean): boolean {
        if ((!duplicated_scope) && (value?.hasOwnProperty("scope"))) {
            return true
        }
        else if ((!duplicated_direction) && (value?.hasOwnProperty("direction"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof BounceSymbolEffect")
        }
    }
    static isBreakPoints(value: object|string|number|undefined|null|boolean, duplicated_value: boolean, duplicated_reference: boolean): boolean {
        if ((!duplicated_value) && (value?.hasOwnProperty("value"))) {
            return true
        }
        else if ((!duplicated_reference) && (value?.hasOwnProperty("reference"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof BreakPoints")
        }
    }
    static isBreakpointsReference(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (BreakpointsReference.WindowSize)) {
            return true
        }
        else if ((value) === (BreakpointsReference.ComponentSize)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof BreakpointsReference")
        }
    }
    static isBusinessError(value: object|string|number|undefined|null|boolean, duplicated_name: boolean, duplicated_message: boolean, duplicated_stack: boolean, duplicated_code: boolean): boolean {
        if ((!duplicated_name) && (value?.hasOwnProperty("name"))) {
            return true
        }
        else if ((!duplicated_message) && (value?.hasOwnProperty("message"))) {
            return true
        }
        else if ((!duplicated_code) && (value?.hasOwnProperty("code"))) {
            return true
        }
        else if ((!duplicated_stack) && (value?.hasOwnProperty("stack"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof BusinessError")
        }
    }
    static isButtonAttribute(value: object|string|number|undefined|null|boolean, duplicated_type: boolean, duplicated_stateEffect: boolean, duplicated_buttonStyle: boolean, duplicated_controlSize: boolean, duplicated_role: boolean, duplicated_fontColor: boolean, duplicated_fontSize: boolean, duplicated_fontWeight: boolean, duplicated_fontStyle: boolean, duplicated_fontFamily: boolean, duplicated_contentModifier: boolean, duplicated_labelStyle: boolean): boolean {
        if ((!duplicated_type) && (value?.hasOwnProperty("type"))) {
            return true
        }
        else if ((!duplicated_stateEffect) && (value?.hasOwnProperty("stateEffect"))) {
            return true
        }
        else if ((!duplicated_buttonStyle) && (value?.hasOwnProperty("buttonStyle"))) {
            return true
        }
        else if ((!duplicated_controlSize) && (value?.hasOwnProperty("controlSize"))) {
            return true
        }
        else if ((!duplicated_role) && (value?.hasOwnProperty("role"))) {
            return true
        }
        else if ((!duplicated_fontColor) && (value?.hasOwnProperty("fontColor"))) {
            return true
        }
        else if ((!duplicated_fontSize) && (value?.hasOwnProperty("fontSize"))) {
            return true
        }
        else if ((!duplicated_fontWeight) && (value?.hasOwnProperty("fontWeight"))) {
            return true
        }
        else if ((!duplicated_fontStyle) && (value?.hasOwnProperty("fontStyle"))) {
            return true
        }
        else if ((!duplicated_fontFamily) && (value?.hasOwnProperty("fontFamily"))) {
            return true
        }
        else if ((!duplicated_contentModifier) && (value?.hasOwnProperty("contentModifier"))) {
            return true
        }
        else if ((!duplicated_labelStyle) && (value?.hasOwnProperty("labelStyle"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ButtonAttribute")
        }
    }
    static isButtonConfiguration(value: object|string|number|undefined|null|boolean, duplicated_label: boolean, duplicated_pressed: boolean, duplicated_triggerClick: boolean): boolean {
        if ((!duplicated_label) && (value?.hasOwnProperty("label"))) {
            return true
        }
        else if ((!duplicated_pressed) && (value?.hasOwnProperty("pressed"))) {
            return true
        }
        else if ((!duplicated_triggerClick) && (value?.hasOwnProperty("triggerClick"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ButtonConfiguration")
        }
    }
    static isButtonIconOptions(value: object|string|number|undefined|null|boolean, duplicated_shown: boolean, duplicated_hidden: boolean, duplicated_switching: boolean): boolean {
        if ((!duplicated_shown) && (value?.hasOwnProperty("shown"))) {
            return true
        }
        else if ((!duplicated_hidden) && (value?.hasOwnProperty("hidden"))) {
            return true
        }
        else if ((!duplicated_switching) && (value?.hasOwnProperty("switching"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ButtonIconOptions")
        }
    }
    static isButtonInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof ButtonInterface")
    }
    static isButtonOptions(value: object|string|number|undefined|null|boolean, duplicated_type: boolean, duplicated_stateEffect: boolean, duplicated_buttonStyle: boolean, duplicated_controlSize: boolean, duplicated_role: boolean): boolean {
        if ((!duplicated_type) && (value?.hasOwnProperty("type"))) {
            return true
        }
        else if ((!duplicated_stateEffect) && (value?.hasOwnProperty("stateEffect"))) {
            return true
        }
        else if ((!duplicated_buttonStyle) && (value?.hasOwnProperty("buttonStyle"))) {
            return true
        }
        else if ((!duplicated_controlSize) && (value?.hasOwnProperty("controlSize"))) {
            return true
        }
        else if ((!duplicated_role) && (value?.hasOwnProperty("role"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ButtonOptions")
        }
    }
    static isButtonRole(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (ButtonRole.NORMAL)) {
            return true
        }
        else if ((value) === (ButtonRole.ERROR)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ButtonRole")
        }
    }
    static isButtonStyle(value: object|string|number|undefined|null|boolean, duplicated_left: boolean, duplicated_top: boolean, duplicated_width: boolean, duplicated_height: boolean, duplicated_icons: boolean): boolean {
        if ((!duplicated_left) && (value?.hasOwnProperty("left"))) {
            return true
        }
        else if ((!duplicated_top) && (value?.hasOwnProperty("top"))) {
            return true
        }
        else if ((!duplicated_width) && (value?.hasOwnProperty("width"))) {
            return true
        }
        else if ((!duplicated_height) && (value?.hasOwnProperty("height"))) {
            return true
        }
        else if ((!duplicated_icons) && (value?.hasOwnProperty("icons"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ButtonStyle")
        }
    }
    static isButtonStyleMode(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (ButtonStyleMode.NORMAL)) {
            return true
        }
        else if ((value) === (ButtonStyleMode.EMPHASIZED)) {
            return true
        }
        else if ((value) === (ButtonStyleMode.TEXTUAL)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ButtonStyleMode")
        }
    }
    static isButtonType(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (ButtonType.Capsule)) {
            return true
        }
        else if ((value) === (ButtonType.Circle)) {
            return true
        }
        else if ((value) === (ButtonType.Normal)) {
            return true
        }
        else if ((value) === (ButtonType.ROUNDED_RECTANGLE)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ButtonType")
        }
    }
    static isCacheMode(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (CacheMode.Default)) {
            return true
        }
        else if ((value) === (CacheMode.None)) {
            return true
        }
        else if ((value) === (CacheMode.Online)) {
            return true
        }
        else if ((value) === (CacheMode.Only)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof CacheMode")
        }
    }
    static isCalendarAlign(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (CalendarAlign.START)) {
            return true
        }
        else if ((value) === (CalendarAlign.CENTER)) {
            return true
        }
        else if ((value) === (CalendarAlign.END)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof CalendarAlign")
        }
    }
    static isCalendarAttribute(value: object|string|number|undefined|null|boolean, duplicated_showLunar: boolean, duplicated_showHoliday: boolean, duplicated_needSlide: boolean, duplicated_startOfWeek: boolean, duplicated_offDays: boolean, duplicated_direction: boolean, duplicated_currentDayStyle: boolean, duplicated_nonCurrentDayStyle: boolean, duplicated_todayStyle: boolean, duplicated_weekStyle: boolean, duplicated_workStateStyle: boolean, duplicated_onSelectChange: boolean, duplicated_onRequestData: boolean): boolean {
        if ((!duplicated_showLunar) && (value?.hasOwnProperty("showLunar"))) {
            return true
        }
        else if ((!duplicated_showHoliday) && (value?.hasOwnProperty("showHoliday"))) {
            return true
        }
        else if ((!duplicated_needSlide) && (value?.hasOwnProperty("needSlide"))) {
            return true
        }
        else if ((!duplicated_startOfWeek) && (value?.hasOwnProperty("startOfWeek"))) {
            return true
        }
        else if ((!duplicated_offDays) && (value?.hasOwnProperty("offDays"))) {
            return true
        }
        else if ((!duplicated_direction) && (value?.hasOwnProperty("direction"))) {
            return true
        }
        else if ((!duplicated_currentDayStyle) && (value?.hasOwnProperty("currentDayStyle"))) {
            return true
        }
        else if ((!duplicated_nonCurrentDayStyle) && (value?.hasOwnProperty("nonCurrentDayStyle"))) {
            return true
        }
        else if ((!duplicated_todayStyle) && (value?.hasOwnProperty("todayStyle"))) {
            return true
        }
        else if ((!duplicated_weekStyle) && (value?.hasOwnProperty("weekStyle"))) {
            return true
        }
        else if ((!duplicated_workStateStyle) && (value?.hasOwnProperty("workStateStyle"))) {
            return true
        }
        else if ((!duplicated_onSelectChange) && (value?.hasOwnProperty("onSelectChange"))) {
            return true
        }
        else if ((!duplicated_onRequestData) && (value?.hasOwnProperty("onRequestData"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof CalendarAttribute")
        }
    }
    static isCalendarController(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof CalendarController")
    }
    static isCalendarDay(value: object|string|number|undefined|null|boolean, duplicated_index: boolean, duplicated_lunarMonth: boolean, duplicated_lunarDay: boolean, duplicated_dayMark: boolean, duplicated_dayMarkValue: boolean, duplicated_year: boolean, duplicated_month: boolean, duplicated_day: boolean, duplicated_isFirstOfLunar: boolean, duplicated_hasSchedule: boolean, duplicated_markLunarDay: boolean): boolean {
        if ((!duplicated_index) && (value?.hasOwnProperty("index"))) {
            return true
        }
        else if ((!duplicated_lunarMonth) && (value?.hasOwnProperty("lunarMonth"))) {
            return true
        }
        else if ((!duplicated_lunarDay) && (value?.hasOwnProperty("lunarDay"))) {
            return true
        }
        else if ((!duplicated_dayMark) && (value?.hasOwnProperty("dayMark"))) {
            return true
        }
        else if ((!duplicated_dayMarkValue) && (value?.hasOwnProperty("dayMarkValue"))) {
            return true
        }
        else if ((!duplicated_year) && (value?.hasOwnProperty("year"))) {
            return true
        }
        else if ((!duplicated_month) && (value?.hasOwnProperty("month"))) {
            return true
        }
        else if ((!duplicated_day) && (value?.hasOwnProperty("day"))) {
            return true
        }
        else if ((!duplicated_isFirstOfLunar) && (value?.hasOwnProperty("isFirstOfLunar"))) {
            return true
        }
        else if ((!duplicated_hasSchedule) && (value?.hasOwnProperty("hasSchedule"))) {
            return true
        }
        else if ((!duplicated_markLunarDay) && (value?.hasOwnProperty("markLunarDay"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof CalendarDay")
        }
    }
    static isCalendarDialogOptions(value: object|string|number|undefined|null|boolean, duplicated_onAccept: boolean, duplicated_onCancel: boolean, duplicated_onChange: boolean, duplicated_backgroundColor: boolean, duplicated_backgroundBlurStyle: boolean, duplicated_acceptButtonStyle: boolean, duplicated_cancelButtonStyle: boolean, duplicated_onDidAppear: boolean, duplicated_onDidDisappear: boolean, duplicated_onWillAppear: boolean, duplicated_onWillDisappear: boolean, duplicated_shadow: boolean, duplicated_enableHoverMode: boolean, duplicated_hoverModeArea: boolean): boolean {
        if ((!duplicated_onAccept) && (value?.hasOwnProperty("onAccept"))) {
            return true
        }
        else if ((!duplicated_onCancel) && (value?.hasOwnProperty("onCancel"))) {
            return true
        }
        else if ((!duplicated_onChange) && (value?.hasOwnProperty("onChange"))) {
            return true
        }
        else if ((!duplicated_backgroundColor) && (value?.hasOwnProperty("backgroundColor"))) {
            return true
        }
        else if ((!duplicated_backgroundBlurStyle) && (value?.hasOwnProperty("backgroundBlurStyle"))) {
            return true
        }
        else if ((!duplicated_acceptButtonStyle) && (value?.hasOwnProperty("acceptButtonStyle"))) {
            return true
        }
        else if ((!duplicated_cancelButtonStyle) && (value?.hasOwnProperty("cancelButtonStyle"))) {
            return true
        }
        else if ((!duplicated_onDidAppear) && (value?.hasOwnProperty("onDidAppear"))) {
            return true
        }
        else if ((!duplicated_onDidDisappear) && (value?.hasOwnProperty("onDidDisappear"))) {
            return true
        }
        else if ((!duplicated_onWillAppear) && (value?.hasOwnProperty("onWillAppear"))) {
            return true
        }
        else if ((!duplicated_onWillDisappear) && (value?.hasOwnProperty("onWillDisappear"))) {
            return true
        }
        else if ((!duplicated_shadow) && (value?.hasOwnProperty("shadow"))) {
            return true
        }
        else if ((!duplicated_enableHoverMode) && (value?.hasOwnProperty("enableHoverMode"))) {
            return true
        }
        else if ((!duplicated_hoverModeArea) && (value?.hasOwnProperty("hoverModeArea"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof CalendarDialogOptions")
        }
    }
    static isCalendarInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof CalendarInterface")
    }
    static isCalendarOptions(value: object|string|number|undefined|null|boolean, duplicated_hintRadius: boolean, duplicated_selected: boolean): boolean {
        if ((!duplicated_hintRadius) && (value?.hasOwnProperty("hintRadius"))) {
            return true
        }
        else if ((!duplicated_selected) && (value?.hasOwnProperty("selected"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof CalendarOptions")
        }
    }
    static isCalendarPickerAttribute(value: object|string|number|undefined|null|boolean, duplicated_textStyle: boolean, duplicated_onChange: boolean): boolean {
        if ((!duplicated_textStyle) && (value?.hasOwnProperty("textStyle"))) {
            return true
        }
        else if ((!duplicated_onChange) && (value?.hasOwnProperty("onChange"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof CalendarPickerAttribute")
        }
    }
    static isCalendarPickerDialog(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof CalendarPickerDialog")
    }
    static isCalendarPickerInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof CalendarPickerInterface")
    }
    static isCalendarRequestedData(value: object|string|number|undefined|null|boolean, duplicated_year: boolean, duplicated_month: boolean, duplicated_currentYear: boolean, duplicated_currentMonth: boolean, duplicated_monthState: boolean): boolean {
        if ((!duplicated_year) && (value?.hasOwnProperty("year"))) {
            return true
        }
        else if ((!duplicated_month) && (value?.hasOwnProperty("month"))) {
            return true
        }
        else if ((!duplicated_currentYear) && (value?.hasOwnProperty("currentYear"))) {
            return true
        }
        else if ((!duplicated_currentMonth) && (value?.hasOwnProperty("currentMonth"))) {
            return true
        }
        else if ((!duplicated_monthState) && (value?.hasOwnProperty("monthState"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof CalendarRequestedData")
        }
    }
    static isCalendarSelectedDate(value: object|string|number|undefined|null|boolean, duplicated_year: boolean, duplicated_month: boolean, duplicated_day: boolean): boolean {
        if ((!duplicated_year) && (value?.hasOwnProperty("year"))) {
            return true
        }
        else if ((!duplicated_month) && (value?.hasOwnProperty("month"))) {
            return true
        }
        else if ((!duplicated_day) && (value?.hasOwnProperty("day"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof CalendarSelectedDate")
        }
    }
    static isCallback(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof Callback")
    }
    static isCancelButtonOptions(value: object|string|number|undefined|null|boolean, duplicated_style: boolean, duplicated_icon: boolean): boolean {
        if ((!duplicated_style) && (value?.hasOwnProperty("style"))) {
            return true
        }
        else if ((!duplicated_icon) && (value?.hasOwnProperty("icon"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof CancelButtonOptions")
        }
    }
    static isCancelButtonStyle(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (CancelButtonStyle.CONSTANT)) {
            return true
        }
        else if ((value) === (CancelButtonStyle.INVISIBLE)) {
            return true
        }
        else if ((value) === (CancelButtonStyle.INPUT)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof CancelButtonStyle")
        }
    }
    static isCancelButtonSymbolOptions(value: object|string|number|undefined|null|boolean, duplicated_style: boolean, duplicated_icon: boolean): boolean {
        if ((!duplicated_style) && (value?.hasOwnProperty("style"))) {
            return true
        }
        else if ((!duplicated_icon) && (value?.hasOwnProperty("icon"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof CancelButtonSymbolOptions")
        }
    }
    static isCanvasAttribute(value: object|string|number|undefined|null|boolean, duplicated_onReady: boolean, duplicated_enableAnalyzer: boolean): boolean {
        if ((!duplicated_onReady) && (value?.hasOwnProperty("onReady"))) {
            return true
        }
        else if ((!duplicated_enableAnalyzer) && (value?.hasOwnProperty("enableAnalyzer"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof CanvasAttribute")
        }
    }
    static isCanvasGradient(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof CanvasGradient")
    }
    static isCanvasInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof CanvasInterface")
    }
    static isCanvasPath(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof CanvasPath")
    }
    static isCanvasPattern(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof CanvasPattern")
    }
    static isCanvasRenderer(value: object|string|number|undefined|null|boolean, duplicated_globalAlpha: boolean, duplicated_globalCompositeOperation: boolean, duplicated_fillStyle: boolean, duplicated_strokeStyle: boolean, duplicated_filter: boolean, duplicated_imageSmoothingEnabled: boolean, duplicated_imageSmoothingQuality: boolean, duplicated_lineCap: boolean, duplicated_lineDashOffset: boolean, duplicated_lineJoin: boolean, duplicated_lineWidth: boolean, duplicated_miterLimit: boolean, duplicated_shadowBlur: boolean, duplicated_shadowColor: boolean, duplicated_shadowOffsetX: boolean, duplicated_shadowOffsetY: boolean, duplicated_direction: boolean, duplicated_font: boolean, duplicated_textAlign: boolean, duplicated_textBaseline: boolean): boolean {
        if ((!duplicated_globalAlpha) && (value?.hasOwnProperty("globalAlpha"))) {
            return true
        }
        else if ((!duplicated_globalCompositeOperation) && (value?.hasOwnProperty("globalCompositeOperation"))) {
            return true
        }
        else if ((!duplicated_fillStyle) && (value?.hasOwnProperty("fillStyle"))) {
            return true
        }
        else if ((!duplicated_strokeStyle) && (value?.hasOwnProperty("strokeStyle"))) {
            return true
        }
        else if ((!duplicated_filter) && (value?.hasOwnProperty("filter"))) {
            return true
        }
        else if ((!duplicated_imageSmoothingEnabled) && (value?.hasOwnProperty("imageSmoothingEnabled"))) {
            return true
        }
        else if ((!duplicated_imageSmoothingQuality) && (value?.hasOwnProperty("imageSmoothingQuality"))) {
            return true
        }
        else if ((!duplicated_lineCap) && (value?.hasOwnProperty("lineCap"))) {
            return true
        }
        else if ((!duplicated_lineDashOffset) && (value?.hasOwnProperty("lineDashOffset"))) {
            return true
        }
        else if ((!duplicated_lineJoin) && (value?.hasOwnProperty("lineJoin"))) {
            return true
        }
        else if ((!duplicated_lineWidth) && (value?.hasOwnProperty("lineWidth"))) {
            return true
        }
        else if ((!duplicated_miterLimit) && (value?.hasOwnProperty("miterLimit"))) {
            return true
        }
        else if ((!duplicated_shadowBlur) && (value?.hasOwnProperty("shadowBlur"))) {
            return true
        }
        else if ((!duplicated_shadowColor) && (value?.hasOwnProperty("shadowColor"))) {
            return true
        }
        else if ((!duplicated_shadowOffsetX) && (value?.hasOwnProperty("shadowOffsetX"))) {
            return true
        }
        else if ((!duplicated_shadowOffsetY) && (value?.hasOwnProperty("shadowOffsetY"))) {
            return true
        }
        else if ((!duplicated_direction) && (value?.hasOwnProperty("direction"))) {
            return true
        }
        else if ((!duplicated_font) && (value?.hasOwnProperty("font"))) {
            return true
        }
        else if ((!duplicated_textAlign) && (value?.hasOwnProperty("textAlign"))) {
            return true
        }
        else if ((!duplicated_textBaseline) && (value?.hasOwnProperty("textBaseline"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof CanvasRenderer")
        }
    }
    static isCanvasRenderingContext2D(value: object|string|number|undefined|null|boolean, duplicated_height: boolean, duplicated_width: boolean, duplicated_canvas: boolean): boolean {
        if ((!duplicated_height) && (value?.hasOwnProperty("height"))) {
            return true
        }
        else if ((!duplicated_width) && (value?.hasOwnProperty("width"))) {
            return true
        }
        else if ((!duplicated_canvas) && (value?.hasOwnProperty("canvas"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof CanvasRenderingContext2D")
        }
    }
    static isCapsuleStyleOptions(value: object|string|number|undefined|null|boolean, duplicated_borderColor: boolean, duplicated_borderWidth: boolean, duplicated_content: boolean, duplicated_font: boolean, duplicated_fontColor: boolean, duplicated_showDefaultPercentage: boolean): boolean {
        if ((!duplicated_borderColor) && (value?.hasOwnProperty("borderColor"))) {
            return true
        }
        else if ((!duplicated_borderWidth) && (value?.hasOwnProperty("borderWidth"))) {
            return true
        }
        else if ((!duplicated_content) && (value?.hasOwnProperty("content"))) {
            return true
        }
        else if ((!duplicated_font) && (value?.hasOwnProperty("font"))) {
            return true
        }
        else if ((!duplicated_fontColor) && (value?.hasOwnProperty("fontColor"))) {
            return true
        }
        else if ((!duplicated_showDefaultPercentage) && (value?.hasOwnProperty("showDefaultPercentage"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof CapsuleStyleOptions")
        }
    }
    static isCaretOffset(value: object|string|number|undefined|null|boolean, duplicated_index: boolean, duplicated_x: boolean, duplicated_y: boolean): boolean {
        if ((!duplicated_index) && (value?.hasOwnProperty("index"))) {
            return true
        }
        else if ((!duplicated_x) && (value?.hasOwnProperty("x"))) {
            return true
        }
        else if ((!duplicated_y) && (value?.hasOwnProperty("y"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof CaretOffset")
        }
    }
    static isCaretStyle(value: object|string|number|undefined|null|boolean, duplicated_width: boolean, duplicated_color: boolean): boolean {
        if ((!duplicated_width) && (value?.hasOwnProperty("width"))) {
            return true
        }
        else if ((!duplicated_color) && (value?.hasOwnProperty("color"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof CaretStyle")
        }
    }
    static isChainAnimationOptions(value: object|string|number|undefined|null|boolean, duplicated_minSpace: boolean, duplicated_maxSpace: boolean, duplicated_conductivity: boolean, duplicated_intensity: boolean, duplicated_edgeEffect: boolean, duplicated_stiffness: boolean, duplicated_damping: boolean): boolean {
        if ((!duplicated_minSpace) && (value?.hasOwnProperty("minSpace"))) {
            return true
        }
        else if ((!duplicated_maxSpace) && (value?.hasOwnProperty("maxSpace"))) {
            return true
        }
        else if ((!duplicated_conductivity) && (value?.hasOwnProperty("conductivity"))) {
            return true
        }
        else if ((!duplicated_intensity) && (value?.hasOwnProperty("intensity"))) {
            return true
        }
        else if ((!duplicated_edgeEffect) && (value?.hasOwnProperty("edgeEffect"))) {
            return true
        }
        else if ((!duplicated_stiffness) && (value?.hasOwnProperty("stiffness"))) {
            return true
        }
        else if ((!duplicated_damping) && (value?.hasOwnProperty("damping"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ChainAnimationOptions")
        }
    }
    static isChainEdgeEffect(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (ChainEdgeEffect.DEFAULT)) {
            return true
        }
        else if ((value) === (ChainEdgeEffect.STRETCH)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ChainEdgeEffect")
        }
    }
    static isChainStyle(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (ChainStyle.SPREAD)) {
            return true
        }
        else if ((value) === (ChainStyle.SPREAD_INSIDE)) {
            return true
        }
        else if ((value) === (ChainStyle.PACKED)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ChainStyle")
        }
    }
    static isChainWeightOptions(value: object|string|number|undefined|null|boolean, duplicated_horizontal: boolean, duplicated_vertical: boolean): boolean {
        if ((!duplicated_horizontal) && (value?.hasOwnProperty("horizontal"))) {
            return true
        }
        else if ((!duplicated_vertical) && (value?.hasOwnProperty("vertical"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ChainWeightOptions")
        }
    }
    static isCheckboxAttribute(value: object|string|number|undefined|null|boolean, duplicated_select: boolean, duplicated_selectedColor: boolean, duplicated_shape: boolean, duplicated_unselectedColor: boolean, duplicated_mark: boolean, duplicated_onChange: boolean, duplicated_contentModifier: boolean): boolean {
        if ((!duplicated_select) && (value?.hasOwnProperty("select"))) {
            return true
        }
        else if ((!duplicated_selectedColor) && (value?.hasOwnProperty("selectedColor"))) {
            return true
        }
        else if ((!duplicated_shape) && (value?.hasOwnProperty("shape"))) {
            return true
        }
        else if ((!duplicated_unselectedColor) && (value?.hasOwnProperty("unselectedColor"))) {
            return true
        }
        else if ((!duplicated_mark) && (value?.hasOwnProperty("mark"))) {
            return true
        }
        else if ((!duplicated_onChange) && (value?.hasOwnProperty("onChange"))) {
            return true
        }
        else if ((!duplicated_contentModifier) && (value?.hasOwnProperty("contentModifier"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof CheckboxAttribute")
        }
    }
    static isCheckBoxConfiguration(value: object|string|number|undefined|null|boolean, duplicated_name: boolean, duplicated_selected: boolean, duplicated_triggerChange: boolean): boolean {
        if ((!duplicated_name) && (value?.hasOwnProperty("name"))) {
            return true
        }
        else if ((!duplicated_selected) && (value?.hasOwnProperty("selected"))) {
            return true
        }
        else if ((!duplicated_triggerChange) && (value?.hasOwnProperty("triggerChange"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof CheckBoxConfiguration")
        }
    }
    static isCheckboxGroupAttribute(value: object|string|number|undefined|null|boolean, duplicated_selectAll: boolean, duplicated_selectedColor: boolean, duplicated_unselectedColor: boolean, duplicated_mark: boolean, duplicated_onChange: boolean, duplicated_checkboxShape: boolean): boolean {
        if ((!duplicated_selectAll) && (value?.hasOwnProperty("selectAll"))) {
            return true
        }
        else if ((!duplicated_selectedColor) && (value?.hasOwnProperty("selectedColor"))) {
            return true
        }
        else if ((!duplicated_unselectedColor) && (value?.hasOwnProperty("unselectedColor"))) {
            return true
        }
        else if ((!duplicated_mark) && (value?.hasOwnProperty("mark"))) {
            return true
        }
        else if ((!duplicated_onChange) && (value?.hasOwnProperty("onChange"))) {
            return true
        }
        else if ((!duplicated_checkboxShape) && (value?.hasOwnProperty("checkboxShape"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof CheckboxGroupAttribute")
        }
    }
    static isCheckboxGroupInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof CheckboxGroupInterface")
    }
    static isCheckboxGroupOptions(value: object|string|number|undefined|null|boolean, duplicated_group: boolean): boolean {
        if ((!duplicated_group) && (value?.hasOwnProperty("group"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof CheckboxGroupOptions")
        }
    }
    static isCheckboxGroupResult(value: object|string|number|undefined|null|boolean, duplicated_name: boolean, duplicated_status: boolean): boolean {
        if ((!duplicated_name) && (value?.hasOwnProperty("name"))) {
            return true
        }
        else if ((!duplicated_status) && (value?.hasOwnProperty("status"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof CheckboxGroupResult")
        }
    }
    static isCheckboxInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof CheckboxInterface")
    }
    static isCheckboxOptions(value: object|string|number|undefined|null|boolean, duplicated_name: boolean, duplicated_group: boolean, duplicated_indicatorBuilder: boolean): boolean {
        if ((!duplicated_name) && (value?.hasOwnProperty("name"))) {
            return true
        }
        else if ((!duplicated_group) && (value?.hasOwnProperty("group"))) {
            return true
        }
        else if ((!duplicated_indicatorBuilder) && (value?.hasOwnProperty("indicatorBuilder"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof CheckboxOptions")
        }
    }
    static isCheckBoxShape(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (CheckBoxShape.CIRCLE)) {
            return true
        }
        else if ((value) === (CheckBoxShape.ROUNDED_SQUARE)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof CheckBoxShape")
        }
    }
    static isChildrenMainSize(value: object|string|number|undefined|null|boolean, duplicated_childDefaultSize: boolean): boolean {
        if ((!duplicated_childDefaultSize) && (value?.hasOwnProperty("childDefaultSize"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ChildrenMainSize")
        }
    }
    static isCircleAttribute(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof CircleAttribute")
    }
    static isCircleInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof CircleInterface")
    }
    static isCircleOptions(value: object|string|number|undefined|null|boolean, duplicated_width: boolean, duplicated_height: boolean): boolean {
        if ((!duplicated_width) && (value?.hasOwnProperty("width"))) {
            return true
        }
        else if ((!duplicated_height) && (value?.hasOwnProperty("height"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof CircleOptions")
        }
    }
    static isCircleShape(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof CircleShape")
    }
    static isCircleStyleOptions(value: object|string|number|undefined|null|boolean, duplicated_color: boolean, duplicated_radius: boolean, duplicated_enableWaveEffect: boolean): boolean {
        if ((!duplicated_color) && (value?.hasOwnProperty("color"))) {
            return true
        }
        else if ((!duplicated_radius) && (value?.hasOwnProperty("radius"))) {
            return true
        }
        else if ((!duplicated_enableWaveEffect) && (value?.hasOwnProperty("enableWaveEffect"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof CircleStyleOptions")
        }
    }
    static isClickEffect(value: object|string|number|undefined|null|boolean, duplicated_level: boolean, duplicated_scale: boolean): boolean {
        if ((!duplicated_level) && (value?.hasOwnProperty("level"))) {
            return true
        }
        else if ((!duplicated_scale) && (value?.hasOwnProperty("scale"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ClickEffect")
        }
    }
    static isClickEffectLevel(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (ClickEffectLevel.LIGHT)) {
            return true
        }
        else if ((value) === (ClickEffectLevel.MIDDLE)) {
            return true
        }
        else if ((value) === (ClickEffectLevel.HEAVY)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ClickEffectLevel")
        }
    }
    static isClickEvent(value: object|string|number|undefined|null|boolean, duplicated_displayX: boolean, duplicated_displayY: boolean, duplicated_windowX: boolean, duplicated_windowY: boolean, duplicated_screenX: boolean, duplicated_screenY: boolean, duplicated_x: boolean, duplicated_y: boolean, duplicated_preventDefault: boolean): boolean {
        if ((!duplicated_displayX) && (value?.hasOwnProperty("displayX"))) {
            return true
        }
        else if ((!duplicated_displayY) && (value?.hasOwnProperty("displayY"))) {
            return true
        }
        else if ((!duplicated_windowX) && (value?.hasOwnProperty("windowX"))) {
            return true
        }
        else if ((!duplicated_windowY) && (value?.hasOwnProperty("windowY"))) {
            return true
        }
        else if ((!duplicated_screenX) && (value?.hasOwnProperty("screenX"))) {
            return true
        }
        else if ((!duplicated_screenY) && (value?.hasOwnProperty("screenY"))) {
            return true
        }
        else if ((!duplicated_x) && (value?.hasOwnProperty("x"))) {
            return true
        }
        else if ((!duplicated_y) && (value?.hasOwnProperty("y"))) {
            return true
        }
        else if ((!duplicated_preventDefault) && (value?.hasOwnProperty("preventDefault"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ClickEvent")
        }
    }
    static isClientAuthenticationHandler(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof ClientAuthenticationHandler")
    }
    static isCloseSwipeActionOptions(value: object|string|number|undefined|null|boolean, duplicated_onFinish: boolean): boolean {
        if ((!duplicated_onFinish) && (value?.hasOwnProperty("onFinish"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof CloseSwipeActionOptions")
        }
    }
    static isColor(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (Color.White)) {
            return true
        }
        else if ((value) === (Color.Black)) {
            return true
        }
        else if ((value) === (Color.Blue)) {
            return true
        }
        else if ((value) === (Color.Brown)) {
            return true
        }
        else if ((value) === (Color.Gray)) {
            return true
        }
        else if ((value) === (Color.Green)) {
            return true
        }
        else if ((value) === (Color.Grey)) {
            return true
        }
        else if ((value) === (Color.Orange)) {
            return true
        }
        else if ((value) === (Color.Pink)) {
            return true
        }
        else if ((value) === (Color.Red)) {
            return true
        }
        else if ((value) === (Color.Yellow)) {
            return true
        }
        else if ((value) === (Color.Transparent)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof Color")
        }
    }
    static isColorFilter(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof ColorFilter")
    }
    static isColoringStrategy(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (ColoringStrategy.INVERT)) {
            return true
        }
        else if ((value) === (ColoringStrategy.AVERAGE)) {
            return true
        }
        else if ((value) === (ColoringStrategy.PRIMARY)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ColoringStrategy")
        }
    }
    static isColorMetrics(value: object|string|number|undefined|null|boolean, duplicated_color: boolean, duplicated_red: boolean, duplicated_green: boolean, duplicated_blue: boolean, duplicated_alpha: boolean): boolean {
        if ((!duplicated_color) && (value?.hasOwnProperty("color"))) {
            return true
        }
        else if ((!duplicated_red) && (value?.hasOwnProperty("red"))) {
            return true
        }
        else if ((!duplicated_green) && (value?.hasOwnProperty("green"))) {
            return true
        }
        else if ((!duplicated_blue) && (value?.hasOwnProperty("blue"))) {
            return true
        }
        else if ((!duplicated_alpha) && (value?.hasOwnProperty("alpha"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ColorMetrics")
        }
    }
    static isColorMode(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (ColorMode.LIGHT)) {
            return true
        }
        else if ((value) === (ColorMode.DARK)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ColorMode")
        }
    }
    static isColorStop(value: object|string|number|undefined|null|boolean, duplicated_color: boolean, duplicated_offset: boolean): boolean {
        if ((!duplicated_color) && (value?.hasOwnProperty("color"))) {
            return true
        }
        else if ((!duplicated_offset) && (value?.hasOwnProperty("offset"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ColorStop")
        }
    }
    static isColumnAttribute(value: object|string|number|undefined|null|boolean, duplicated_alignItems: boolean, duplicated_justifyContent: boolean, duplicated_pointLight: boolean, duplicated_reverse: boolean): boolean {
        if ((!duplicated_alignItems) && (value?.hasOwnProperty("alignItems"))) {
            return true
        }
        else if ((!duplicated_justifyContent) && (value?.hasOwnProperty("justifyContent"))) {
            return true
        }
        else if ((!duplicated_pointLight) && (value?.hasOwnProperty("pointLight"))) {
            return true
        }
        else if ((!duplicated_reverse) && (value?.hasOwnProperty("reverse"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ColumnAttribute")
        }
    }
    static isColumnInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof ColumnInterface")
    }
    static isColumnOptions(value: object|string|number|undefined|null|boolean, duplicated_space: boolean): boolean {
        if ((!duplicated_space) && (value?.hasOwnProperty("space"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ColumnOptions")
        }
    }
    static isColumnSplitAttribute(value: object|string|number|undefined|null|boolean, duplicated_resizeable: boolean, duplicated_divider: boolean): boolean {
        if ((!duplicated_resizeable) && (value?.hasOwnProperty("resizeable"))) {
            return true
        }
        else if ((!duplicated_divider) && (value?.hasOwnProperty("divider"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ColumnSplitAttribute")
        }
    }
    static isColumnSplitDividerStyle(value: object|string|number|undefined|null|boolean, duplicated_startMargin: boolean, duplicated_endMargin: boolean): boolean {
        if ((!duplicated_startMargin) && (value?.hasOwnProperty("startMargin"))) {
            return true
        }
        else if ((!duplicated_endMargin) && (value?.hasOwnProperty("endMargin"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ColumnSplitDividerStyle")
        }
    }
    static isColumnSplitInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof ColumnSplitInterface")
    }
    static isCommonAttribute(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof CommonAttribute")
    }
    static isCommonConfiguration(value: object|string|number|undefined|null|boolean, duplicated_enabled: boolean, duplicated_contentModifier: boolean): boolean {
        if ((!duplicated_enabled) && (value?.hasOwnProperty("enabled"))) {
            return true
        }
        else if ((!duplicated_contentModifier) && (value?.hasOwnProperty("contentModifier"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof CommonConfiguration")
        }
    }
    static isCommonInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof CommonInterface")
    }
    static isCommonMethod(value: object|string|number|undefined|null|boolean, duplicated_width: boolean, duplicated_height: boolean, duplicated_drawModifier: boolean, duplicated_responseRegion: boolean, duplicated_mouseResponseRegion: boolean, duplicated_size: boolean, duplicated_constraintSize: boolean, duplicated_touchable: boolean, duplicated_hitTestBehavior: boolean, duplicated_onChildTouchTest: boolean, duplicated_layoutWeight: boolean, duplicated_chainWeight: boolean, duplicated_padding: boolean, duplicated_safeAreaPadding: boolean, duplicated_margin: boolean, duplicated_backgroundColor: boolean, duplicated_pixelRound: boolean, duplicated_backgroundImageSize: boolean, duplicated_backgroundImagePosition: boolean, duplicated_backgroundEffect: boolean, duplicated_backgroundImageResizable: boolean, duplicated_foregroundEffect: boolean, duplicated_visualEffect: boolean, duplicated_backgroundFilter: boolean, duplicated_foregroundFilter: boolean, duplicated_compositingFilter: boolean, duplicated_opacity: boolean, duplicated_border: boolean, duplicated_borderStyle: boolean, duplicated_borderWidth: boolean, duplicated_borderColor: boolean, duplicated_borderRadius: boolean, duplicated_borderImage: boolean, duplicated_outline: boolean, duplicated_outlineStyle: boolean, duplicated_outlineWidth: boolean, duplicated_outlineColor: boolean, duplicated_outlineRadius: boolean, duplicated_foregroundColor: boolean, duplicated_onClick: boolean, duplicated_onHover: boolean, duplicated_onAccessibilityHover: boolean, duplicated_hoverEffect: boolean, duplicated_onMouse: boolean, duplicated_onTouch: boolean, duplicated_onKeyEvent: boolean, duplicated_onKeyPreIme: boolean, duplicated_focusable: boolean, duplicated_onFocus: boolean, duplicated_onBlur: boolean, duplicated_tabIndex: boolean, duplicated_defaultFocus: boolean, duplicated_groupDefaultFocus: boolean, duplicated_focusOnTouch: boolean, duplicated_focusBox: boolean, duplicated_animation: boolean, duplicated_transition: boolean, duplicated_motionBlur: boolean, duplicated_brightness: boolean, duplicated_contrast: boolean, duplicated_grayscale: boolean, duplicated_colorBlend: boolean, duplicated_saturate: boolean, duplicated_sepia: boolean, duplicated_invert: boolean, duplicated_hueRotate: boolean, duplicated_useShadowBatching: boolean, duplicated_useEffect: boolean, duplicated_renderGroup: boolean, duplicated_freeze: boolean, duplicated_translate: boolean, duplicated_scale: boolean, duplicated_gridSpan: boolean, duplicated_gridOffset: boolean, duplicated_rotate: boolean, duplicated_transform: boolean, duplicated_onAppear: boolean, duplicated_onDisAppear: boolean, duplicated_onAttach: boolean, duplicated_onDetach: boolean, duplicated_onAreaChange: boolean, duplicated_visibility: boolean, duplicated_flexGrow: boolean, duplicated_flexShrink: boolean, duplicated_flexBasis: boolean, duplicated_alignSelf: boolean, duplicated_displayPriority: boolean, duplicated_zIndex: boolean, duplicated_direction: boolean, duplicated_align: boolean, duplicated_position: boolean, duplicated_markAnchor: boolean, duplicated_offset: boolean, duplicated_enabled: boolean, duplicated_useSizeType: boolean, duplicated_alignRules: boolean, duplicated_aspectRatio: boolean, duplicated_clickEffect: boolean, duplicated_onDragStart: boolean, duplicated_onDragEnter: boolean, duplicated_onDragMove: boolean, duplicated_onDragLeave: boolean, duplicated_onDrop: boolean, duplicated_onDragEnd: boolean, duplicated_allowDrop: boolean, duplicated_draggable: boolean, duplicated_dragPreview: boolean, duplicated_onPreDrag: boolean, duplicated_linearGradient: boolean, duplicated_sweepGradient: boolean, duplicated_radialGradient: boolean, duplicated_motionPath: boolean, duplicated_shadow: boolean, duplicated_clip: boolean, duplicated_clipShape: boolean, duplicated_mask: boolean, duplicated_maskShape: boolean, duplicated_key: boolean, duplicated_id: boolean, duplicated_geometryTransition: boolean, duplicated_stateStyles: boolean, duplicated_restoreId: boolean, duplicated_sphericalEffect: boolean, duplicated_lightUpEffect: boolean, duplicated_pixelStretchEffect: boolean, duplicated_accessibilityGroup: boolean, duplicated_accessibilityText: boolean, duplicated_accessibilityTextHint: boolean, duplicated_accessibilityDescription: boolean, duplicated_accessibilityLevel: boolean, duplicated_accessibilityVirtualNode: boolean, duplicated_accessibilityChecked: boolean, duplicated_accessibilitySelected: boolean, duplicated_obscured: boolean, duplicated_reuseId: boolean, duplicated_renderFit: boolean, duplicated_attributeModifier: boolean, duplicated_gestureModifier: boolean, duplicated_backgroundBrightness: boolean, duplicated_onGestureJudgeBegin: boolean, duplicated_onGestureRecognizerJudgeBegin: boolean, duplicated_shouldBuiltInRecognizerParallelWith: boolean, duplicated_monopolizeEvents: boolean, duplicated_onTouchIntercept: boolean, duplicated_onSizeChange: boolean): boolean {
        if ((!duplicated_width) && (value?.hasOwnProperty("width"))) {
            return true
        }
        else if ((!duplicated_height) && (value?.hasOwnProperty("height"))) {
            return true
        }
        else if ((!duplicated_drawModifier) && (value?.hasOwnProperty("drawModifier"))) {
            return true
        }
        else if ((!duplicated_responseRegion) && (value?.hasOwnProperty("responseRegion"))) {
            return true
        }
        else if ((!duplicated_mouseResponseRegion) && (value?.hasOwnProperty("mouseResponseRegion"))) {
            return true
        }
        else if ((!duplicated_size) && (value?.hasOwnProperty("size"))) {
            return true
        }
        else if ((!duplicated_constraintSize) && (value?.hasOwnProperty("constraintSize"))) {
            return true
        }
        else if ((!duplicated_touchable) && (value?.hasOwnProperty("touchable"))) {
            return true
        }
        else if ((!duplicated_hitTestBehavior) && (value?.hasOwnProperty("hitTestBehavior"))) {
            return true
        }
        else if ((!duplicated_onChildTouchTest) && (value?.hasOwnProperty("onChildTouchTest"))) {
            return true
        }
        else if ((!duplicated_layoutWeight) && (value?.hasOwnProperty("layoutWeight"))) {
            return true
        }
        else if ((!duplicated_chainWeight) && (value?.hasOwnProperty("chainWeight"))) {
            return true
        }
        else if ((!duplicated_padding) && (value?.hasOwnProperty("padding"))) {
            return true
        }
        else if ((!duplicated_safeAreaPadding) && (value?.hasOwnProperty("safeAreaPadding"))) {
            return true
        }
        else if ((!duplicated_margin) && (value?.hasOwnProperty("margin"))) {
            return true
        }
        else if ((!duplicated_backgroundColor) && (value?.hasOwnProperty("backgroundColor"))) {
            return true
        }
        else if ((!duplicated_pixelRound) && (value?.hasOwnProperty("pixelRound"))) {
            return true
        }
        else if ((!duplicated_backgroundImageSize) && (value?.hasOwnProperty("backgroundImageSize"))) {
            return true
        }
        else if ((!duplicated_backgroundImagePosition) && (value?.hasOwnProperty("backgroundImagePosition"))) {
            return true
        }
        else if ((!duplicated_backgroundEffect) && (value?.hasOwnProperty("backgroundEffect"))) {
            return true
        }
        else if ((!duplicated_backgroundImageResizable) && (value?.hasOwnProperty("backgroundImageResizable"))) {
            return true
        }
        else if ((!duplicated_foregroundEffect) && (value?.hasOwnProperty("foregroundEffect"))) {
            return true
        }
        else if ((!duplicated_visualEffect) && (value?.hasOwnProperty("visualEffect"))) {
            return true
        }
        else if ((!duplicated_backgroundFilter) && (value?.hasOwnProperty("backgroundFilter"))) {
            return true
        }
        else if ((!duplicated_foregroundFilter) && (value?.hasOwnProperty("foregroundFilter"))) {
            return true
        }
        else if ((!duplicated_compositingFilter) && (value?.hasOwnProperty("compositingFilter"))) {
            return true
        }
        else if ((!duplicated_opacity) && (value?.hasOwnProperty("opacity"))) {
            return true
        }
        else if ((!duplicated_border) && (value?.hasOwnProperty("border"))) {
            return true
        }
        else if ((!duplicated_borderStyle) && (value?.hasOwnProperty("borderStyle"))) {
            return true
        }
        else if ((!duplicated_borderWidth) && (value?.hasOwnProperty("borderWidth"))) {
            return true
        }
        else if ((!duplicated_borderColor) && (value?.hasOwnProperty("borderColor"))) {
            return true
        }
        else if ((!duplicated_borderRadius) && (value?.hasOwnProperty("borderRadius"))) {
            return true
        }
        else if ((!duplicated_borderImage) && (value?.hasOwnProperty("borderImage"))) {
            return true
        }
        else if ((!duplicated_outline) && (value?.hasOwnProperty("outline"))) {
            return true
        }
        else if ((!duplicated_outlineStyle) && (value?.hasOwnProperty("outlineStyle"))) {
            return true
        }
        else if ((!duplicated_outlineWidth) && (value?.hasOwnProperty("outlineWidth"))) {
            return true
        }
        else if ((!duplicated_outlineColor) && (value?.hasOwnProperty("outlineColor"))) {
            return true
        }
        else if ((!duplicated_outlineRadius) && (value?.hasOwnProperty("outlineRadius"))) {
            return true
        }
        else if ((!duplicated_foregroundColor) && (value?.hasOwnProperty("foregroundColor"))) {
            return true
        }
        else if ((!duplicated_onClick) && (value?.hasOwnProperty("onClick"))) {
            return true
        }
        else if ((!duplicated_onHover) && (value?.hasOwnProperty("onHover"))) {
            return true
        }
        else if ((!duplicated_onAccessibilityHover) && (value?.hasOwnProperty("onAccessibilityHover"))) {
            return true
        }
        else if ((!duplicated_hoverEffect) && (value?.hasOwnProperty("hoverEffect"))) {
            return true
        }
        else if ((!duplicated_onMouse) && (value?.hasOwnProperty("onMouse"))) {
            return true
        }
        else if ((!duplicated_onTouch) && (value?.hasOwnProperty("onTouch"))) {
            return true
        }
        else if ((!duplicated_onKeyEvent) && (value?.hasOwnProperty("onKeyEvent"))) {
            return true
        }
        else if ((!duplicated_onKeyPreIme) && (value?.hasOwnProperty("onKeyPreIme"))) {
            return true
        }
        else if ((!duplicated_focusable) && (value?.hasOwnProperty("focusable"))) {
            return true
        }
        else if ((!duplicated_onFocus) && (value?.hasOwnProperty("onFocus"))) {
            return true
        }
        else if ((!duplicated_onBlur) && (value?.hasOwnProperty("onBlur"))) {
            return true
        }
        else if ((!duplicated_tabIndex) && (value?.hasOwnProperty("tabIndex"))) {
            return true
        }
        else if ((!duplicated_defaultFocus) && (value?.hasOwnProperty("defaultFocus"))) {
            return true
        }
        else if ((!duplicated_groupDefaultFocus) && (value?.hasOwnProperty("groupDefaultFocus"))) {
            return true
        }
        else if ((!duplicated_focusOnTouch) && (value?.hasOwnProperty("focusOnTouch"))) {
            return true
        }
        else if ((!duplicated_focusBox) && (value?.hasOwnProperty("focusBox"))) {
            return true
        }
        else if ((!duplicated_animation) && (value?.hasOwnProperty("animation"))) {
            return true
        }
        else if ((!duplicated_transition) && (value?.hasOwnProperty("transition"))) {
            return true
        }
        else if ((!duplicated_motionBlur) && (value?.hasOwnProperty("motionBlur"))) {
            return true
        }
        else if ((!duplicated_brightness) && (value?.hasOwnProperty("brightness"))) {
            return true
        }
        else if ((!duplicated_contrast) && (value?.hasOwnProperty("contrast"))) {
            return true
        }
        else if ((!duplicated_grayscale) && (value?.hasOwnProperty("grayscale"))) {
            return true
        }
        else if ((!duplicated_colorBlend) && (value?.hasOwnProperty("colorBlend"))) {
            return true
        }
        else if ((!duplicated_saturate) && (value?.hasOwnProperty("saturate"))) {
            return true
        }
        else if ((!duplicated_sepia) && (value?.hasOwnProperty("sepia"))) {
            return true
        }
        else if ((!duplicated_invert) && (value?.hasOwnProperty("invert"))) {
            return true
        }
        else if ((!duplicated_hueRotate) && (value?.hasOwnProperty("hueRotate"))) {
            return true
        }
        else if ((!duplicated_useShadowBatching) && (value?.hasOwnProperty("useShadowBatching"))) {
            return true
        }
        else if ((!duplicated_useEffect) && (value?.hasOwnProperty("useEffect"))) {
            return true
        }
        else if ((!duplicated_renderGroup) && (value?.hasOwnProperty("renderGroup"))) {
            return true
        }
        else if ((!duplicated_freeze) && (value?.hasOwnProperty("freeze"))) {
            return true
        }
        else if ((!duplicated_translate) && (value?.hasOwnProperty("translate"))) {
            return true
        }
        else if ((!duplicated_scale) && (value?.hasOwnProperty("scale"))) {
            return true
        }
        else if ((!duplicated_gridSpan) && (value?.hasOwnProperty("gridSpan"))) {
            return true
        }
        else if ((!duplicated_gridOffset) && (value?.hasOwnProperty("gridOffset"))) {
            return true
        }
        else if ((!duplicated_rotate) && (value?.hasOwnProperty("rotate"))) {
            return true
        }
        else if ((!duplicated_transform) && (value?.hasOwnProperty("transform"))) {
            return true
        }
        else if ((!duplicated_onAppear) && (value?.hasOwnProperty("onAppear"))) {
            return true
        }
        else if ((!duplicated_onDisAppear) && (value?.hasOwnProperty("onDisAppear"))) {
            return true
        }
        else if ((!duplicated_onAttach) && (value?.hasOwnProperty("onAttach"))) {
            return true
        }
        else if ((!duplicated_onDetach) && (value?.hasOwnProperty("onDetach"))) {
            return true
        }
        else if ((!duplicated_onAreaChange) && (value?.hasOwnProperty("onAreaChange"))) {
            return true
        }
        else if ((!duplicated_visibility) && (value?.hasOwnProperty("visibility"))) {
            return true
        }
        else if ((!duplicated_flexGrow) && (value?.hasOwnProperty("flexGrow"))) {
            return true
        }
        else if ((!duplicated_flexShrink) && (value?.hasOwnProperty("flexShrink"))) {
            return true
        }
        else if ((!duplicated_flexBasis) && (value?.hasOwnProperty("flexBasis"))) {
            return true
        }
        else if ((!duplicated_alignSelf) && (value?.hasOwnProperty("alignSelf"))) {
            return true
        }
        else if ((!duplicated_displayPriority) && (value?.hasOwnProperty("displayPriority"))) {
            return true
        }
        else if ((!duplicated_zIndex) && (value?.hasOwnProperty("zIndex"))) {
            return true
        }
        else if ((!duplicated_direction) && (value?.hasOwnProperty("direction"))) {
            return true
        }
        else if ((!duplicated_align) && (value?.hasOwnProperty("align"))) {
            return true
        }
        else if ((!duplicated_position) && (value?.hasOwnProperty("position"))) {
            return true
        }
        else if ((!duplicated_markAnchor) && (value?.hasOwnProperty("markAnchor"))) {
            return true
        }
        else if ((!duplicated_offset) && (value?.hasOwnProperty("offset"))) {
            return true
        }
        else if ((!duplicated_enabled) && (value?.hasOwnProperty("enabled"))) {
            return true
        }
        else if ((!duplicated_useSizeType) && (value?.hasOwnProperty("useSizeType"))) {
            return true
        }
        else if ((!duplicated_alignRules) && (value?.hasOwnProperty("alignRules"))) {
            return true
        }
        else if ((!duplicated_aspectRatio) && (value?.hasOwnProperty("aspectRatio"))) {
            return true
        }
        else if ((!duplicated_clickEffect) && (value?.hasOwnProperty("clickEffect"))) {
            return true
        }
        else if ((!duplicated_onDragStart) && (value?.hasOwnProperty("onDragStart"))) {
            return true
        }
        else if ((!duplicated_onDragEnter) && (value?.hasOwnProperty("onDragEnter"))) {
            return true
        }
        else if ((!duplicated_onDragMove) && (value?.hasOwnProperty("onDragMove"))) {
            return true
        }
        else if ((!duplicated_onDragLeave) && (value?.hasOwnProperty("onDragLeave"))) {
            return true
        }
        else if ((!duplicated_onDrop) && (value?.hasOwnProperty("onDrop"))) {
            return true
        }
        else if ((!duplicated_onDragEnd) && (value?.hasOwnProperty("onDragEnd"))) {
            return true
        }
        else if ((!duplicated_allowDrop) && (value?.hasOwnProperty("allowDrop"))) {
            return true
        }
        else if ((!duplicated_draggable) && (value?.hasOwnProperty("draggable"))) {
            return true
        }
        else if ((!duplicated_dragPreview) && (value?.hasOwnProperty("dragPreview"))) {
            return true
        }
        else if ((!duplicated_onPreDrag) && (value?.hasOwnProperty("onPreDrag"))) {
            return true
        }
        else if ((!duplicated_linearGradient) && (value?.hasOwnProperty("linearGradient"))) {
            return true
        }
        else if ((!duplicated_sweepGradient) && (value?.hasOwnProperty("sweepGradient"))) {
            return true
        }
        else if ((!duplicated_radialGradient) && (value?.hasOwnProperty("radialGradient"))) {
            return true
        }
        else if ((!duplicated_motionPath) && (value?.hasOwnProperty("motionPath"))) {
            return true
        }
        else if ((!duplicated_shadow) && (value?.hasOwnProperty("shadow"))) {
            return true
        }
        else if ((!duplicated_clip) && (value?.hasOwnProperty("clip"))) {
            return true
        }
        else if ((!duplicated_clipShape) && (value?.hasOwnProperty("clipShape"))) {
            return true
        }
        else if ((!duplicated_mask) && (value?.hasOwnProperty("mask"))) {
            return true
        }
        else if ((!duplicated_maskShape) && (value?.hasOwnProperty("maskShape"))) {
            return true
        }
        else if ((!duplicated_key) && (value?.hasOwnProperty("key"))) {
            return true
        }
        else if ((!duplicated_id) && (value?.hasOwnProperty("id"))) {
            return true
        }
        else if ((!duplicated_geometryTransition) && (value?.hasOwnProperty("geometryTransition"))) {
            return true
        }
        else if ((!duplicated_stateStyles) && (value?.hasOwnProperty("stateStyles"))) {
            return true
        }
        else if ((!duplicated_restoreId) && (value?.hasOwnProperty("restoreId"))) {
            return true
        }
        else if ((!duplicated_sphericalEffect) && (value?.hasOwnProperty("sphericalEffect"))) {
            return true
        }
        else if ((!duplicated_lightUpEffect) && (value?.hasOwnProperty("lightUpEffect"))) {
            return true
        }
        else if ((!duplicated_pixelStretchEffect) && (value?.hasOwnProperty("pixelStretchEffect"))) {
            return true
        }
        else if ((!duplicated_accessibilityGroup) && (value?.hasOwnProperty("accessibilityGroup"))) {
            return true
        }
        else if ((!duplicated_accessibilityText) && (value?.hasOwnProperty("accessibilityText"))) {
            return true
        }
        else if ((!duplicated_accessibilityTextHint) && (value?.hasOwnProperty("accessibilityTextHint"))) {
            return true
        }
        else if ((!duplicated_accessibilityDescription) && (value?.hasOwnProperty("accessibilityDescription"))) {
            return true
        }
        else if ((!duplicated_accessibilityLevel) && (value?.hasOwnProperty("accessibilityLevel"))) {
            return true
        }
        else if ((!duplicated_accessibilityVirtualNode) && (value?.hasOwnProperty("accessibilityVirtualNode"))) {
            return true
        }
        else if ((!duplicated_accessibilityChecked) && (value?.hasOwnProperty("accessibilityChecked"))) {
            return true
        }
        else if ((!duplicated_accessibilitySelected) && (value?.hasOwnProperty("accessibilitySelected"))) {
            return true
        }
        else if ((!duplicated_obscured) && (value?.hasOwnProperty("obscured"))) {
            return true
        }
        else if ((!duplicated_reuseId) && (value?.hasOwnProperty("reuseId"))) {
            return true
        }
        else if ((!duplicated_renderFit) && (value?.hasOwnProperty("renderFit"))) {
            return true
        }
        else if ((!duplicated_attributeModifier) && (value?.hasOwnProperty("attributeModifier"))) {
            return true
        }
        else if ((!duplicated_gestureModifier) && (value?.hasOwnProperty("gestureModifier"))) {
            return true
        }
        else if ((!duplicated_backgroundBrightness) && (value?.hasOwnProperty("backgroundBrightness"))) {
            return true
        }
        else if ((!duplicated_onGestureJudgeBegin) && (value?.hasOwnProperty("onGestureJudgeBegin"))) {
            return true
        }
        else if ((!duplicated_onGestureRecognizerJudgeBegin) && (value?.hasOwnProperty("onGestureRecognizerJudgeBegin"))) {
            return true
        }
        else if ((!duplicated_shouldBuiltInRecognizerParallelWith) && (value?.hasOwnProperty("shouldBuiltInRecognizerParallelWith"))) {
            return true
        }
        else if ((!duplicated_monopolizeEvents) && (value?.hasOwnProperty("monopolizeEvents"))) {
            return true
        }
        else if ((!duplicated_onTouchIntercept) && (value?.hasOwnProperty("onTouchIntercept"))) {
            return true
        }
        else if ((!duplicated_onSizeChange) && (value?.hasOwnProperty("onSizeChange"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof CommonMethod")
        }
    }
    static isCommonProgressStyleOptions(value: object|string|number|undefined|null|boolean, duplicated_enableSmoothEffect: boolean): boolean {
        if ((!duplicated_enableSmoothEffect) && (value?.hasOwnProperty("enableSmoothEffect"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof CommonProgressStyleOptions")
        }
    }
    static isCommonShape(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof CommonShape")
    }
    static isCommonShapeMethod(value: object|string|number|undefined|null|boolean, duplicated_stroke: boolean, duplicated_fill: boolean, duplicated_strokeDashOffset: boolean, duplicated_strokeLineCap: boolean, duplicated_strokeLineJoin: boolean, duplicated_strokeMiterLimit: boolean, duplicated_strokeOpacity: boolean, duplicated_fillOpacity: boolean, duplicated_strokeWidth: boolean, duplicated_antiAlias: boolean, duplicated_strokeDashArray: boolean): boolean {
        if ((!duplicated_stroke) && (value?.hasOwnProperty("stroke"))) {
            return true
        }
        else if ((!duplicated_fill) && (value?.hasOwnProperty("fill"))) {
            return true
        }
        else if ((!duplicated_strokeDashOffset) && (value?.hasOwnProperty("strokeDashOffset"))) {
            return true
        }
        else if ((!duplicated_strokeLineCap) && (value?.hasOwnProperty("strokeLineCap"))) {
            return true
        }
        else if ((!duplicated_strokeLineJoin) && (value?.hasOwnProperty("strokeLineJoin"))) {
            return true
        }
        else if ((!duplicated_strokeMiterLimit) && (value?.hasOwnProperty("strokeMiterLimit"))) {
            return true
        }
        else if ((!duplicated_strokeOpacity) && (value?.hasOwnProperty("strokeOpacity"))) {
            return true
        }
        else if ((!duplicated_fillOpacity) && (value?.hasOwnProperty("fillOpacity"))) {
            return true
        }
        else if ((!duplicated_strokeWidth) && (value?.hasOwnProperty("strokeWidth"))) {
            return true
        }
        else if ((!duplicated_antiAlias) && (value?.hasOwnProperty("antiAlias"))) {
            return true
        }
        else if ((!duplicated_strokeDashArray) && (value?.hasOwnProperty("strokeDashArray"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof CommonShapeMethod")
        }
    }
    static isCommonTransition(value: object|string|number|undefined|null|boolean, duplicated_slide: boolean, duplicated_translate: boolean, duplicated_scale: boolean, duplicated_opacity: boolean): boolean {
        if ((!duplicated_slide) && (value?.hasOwnProperty("slide"))) {
            return true
        }
        else if ((!duplicated_translate) && (value?.hasOwnProperty("translate"))) {
            return true
        }
        else if ((!duplicated_scale) && (value?.hasOwnProperty("scale"))) {
            return true
        }
        else if ((!duplicated_opacity) && (value?.hasOwnProperty("opacity"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof CommonTransition")
        }
    }
    static isComponent3DAttribute(value: object|string|number|undefined|null|boolean, duplicated_environment: boolean, duplicated_shader: boolean, duplicated_shaderImageTexture: boolean, duplicated_shaderInputBuffer: boolean, duplicated_renderWidth: boolean, duplicated_renderHeight: boolean): boolean {
        if ((!duplicated_environment) && (value?.hasOwnProperty("environment"))) {
            return true
        }
        else if ((!duplicated_shader) && (value?.hasOwnProperty("shader"))) {
            return true
        }
        else if ((!duplicated_shaderImageTexture) && (value?.hasOwnProperty("shaderImageTexture"))) {
            return true
        }
        else if ((!duplicated_shaderInputBuffer) && (value?.hasOwnProperty("shaderInputBuffer"))) {
            return true
        }
        else if ((!duplicated_renderWidth) && (value?.hasOwnProperty("renderWidth"))) {
            return true
        }
        else if ((!duplicated_renderHeight) && (value?.hasOwnProperty("renderHeight"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof Component3DAttribute")
        }
    }
    static isComponent3DInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof Component3DInterface")
    }
    static isComponentContent(value: object|string|number|undefined|null|boolean, duplicated__ComponentContentStub: boolean): boolean {
        if ((!duplicated__ComponentContentStub) && (value?.hasOwnProperty("_ComponentContentStub"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ComponentContent")
        }
    }
    static isComponentOptions(value: object|string|number|undefined|null|boolean, duplicated_freezeWhenInactive: boolean): boolean {
        if ((!duplicated_freezeWhenInactive) && (value?.hasOwnProperty("freezeWhenInactive"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ComponentOptions")
        }
    }
    static isComponentRoot(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof ComponentRoot")
    }
    static isComputedBarAttribute(value: object|string|number|undefined|null|boolean, duplicated_totalOffset: boolean, duplicated_totalLength: boolean): boolean {
        if ((!duplicated_totalOffset) && (value?.hasOwnProperty("totalOffset"))) {
            return true
        }
        else if ((!duplicated_totalLength) && (value?.hasOwnProperty("totalLength"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ComputedBarAttribute")
        }
    }
    static isConfiguration(value: object|string|number|undefined|null|boolean, duplicated_colorMode: boolean, duplicated_fontScale: boolean): boolean {
        if ((!duplicated_colorMode) && (value?.hasOwnProperty("colorMode"))) {
            return true
        }
        else if ((!duplicated_fontScale) && (value?.hasOwnProperty("fontScale"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof Configuration")
        }
    }
    static isConsoleMessage(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof ConsoleMessage")
    }
    static isConstraintSizeOptions(value: object|string|number|undefined|null|boolean, duplicated_minWidth: boolean, duplicated_maxWidth: boolean, duplicated_minHeight: boolean, duplicated_maxHeight: boolean): boolean {
        if ((!duplicated_minWidth) && (value?.hasOwnProperty("minWidth"))) {
            return true
        }
        else if ((!duplicated_maxWidth) && (value?.hasOwnProperty("maxWidth"))) {
            return true
        }
        else if ((!duplicated_minHeight) && (value?.hasOwnProperty("minHeight"))) {
            return true
        }
        else if ((!duplicated_maxHeight) && (value?.hasOwnProperty("maxHeight"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ConstraintSizeOptions")
        }
    }
    static isContainerSpanAttribute(value: object|string|number|undefined|null|boolean, duplicated_textBackgroundStyle: boolean, duplicated_attributeModifier: boolean): boolean {
        if ((!duplicated_textBackgroundStyle) && (value?.hasOwnProperty("textBackgroundStyle"))) {
            return true
        }
        else if ((!duplicated_attributeModifier) && (value?.hasOwnProperty("attributeModifier"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ContainerSpanAttribute")
        }
    }
    static isContainerSpanInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof ContainerSpanInterface")
    }
    static isContent(value: object|string|number|undefined|null|boolean, duplicated__ContentStub: boolean): boolean {
        if ((!duplicated__ContentStub) && (value?.hasOwnProperty("_ContentStub"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof Content")
        }
    }
    static isContentClipMode(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (ContentClipMode.CONTENT_ONLY)) {
            return true
        }
        else if ((value) === (ContentClipMode.BOUNDARY)) {
            return true
        }
        else if ((value) === (ContentClipMode.SAFE_AREA)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ContentClipMode")
        }
    }
    static isContentCoverOptions(value: object|string|number|undefined|null|boolean, duplicated_modalTransition: boolean, duplicated_onWillDismiss: boolean, duplicated_transition: boolean): boolean {
        if ((!duplicated_modalTransition) && (value?.hasOwnProperty("modalTransition"))) {
            return true
        }
        else if ((!duplicated_onWillDismiss) && (value?.hasOwnProperty("onWillDismiss"))) {
            return true
        }
        else if ((!duplicated_transition) && (value?.hasOwnProperty("transition"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ContentCoverOptions")
        }
    }
    static isContentModifier(value: object|string|number|undefined|null|boolean, duplicated_stub: boolean): boolean {
        if ((!duplicated_stub) && (value?.hasOwnProperty("stub"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ContentModifier<object>")
        }
    }
    static isContentSlotAttribute(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof ContentSlotAttribute")
    }
    static isContentSlotInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof ContentSlotInterface")
    }
    static isContentType(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (ContentType.USER_NAME)) {
            return true
        }
        else if ((value) === (ContentType.PASSWORD)) {
            return true
        }
        else if ((value) === (ContentType.NEW_PASSWORD)) {
            return true
        }
        else if ((value) === (ContentType.FULL_STREET_ADDRESS)) {
            return true
        }
        else if ((value) === (ContentType.HOUSE_NUMBER)) {
            return true
        }
        else if ((value) === (ContentType.DISTRICT_ADDRESS)) {
            return true
        }
        else if ((value) === (ContentType.CITY_ADDRESS)) {
            return true
        }
        else if ((value) === (ContentType.PROVINCE_ADDRESS)) {
            return true
        }
        else if ((value) === (ContentType.COUNTRY_ADDRESS)) {
            return true
        }
        else if ((value) === (ContentType.PERSON_FULL_NAME)) {
            return true
        }
        else if ((value) === (ContentType.PERSON_LAST_NAME)) {
            return true
        }
        else if ((value) === (ContentType.PERSON_FIRST_NAME)) {
            return true
        }
        else if ((value) === (ContentType.PHONE_NUMBER)) {
            return true
        }
        else if ((value) === (ContentType.PHONE_COUNTRY_CODE)) {
            return true
        }
        else if ((value) === (ContentType.FULL_PHONE_NUMBER)) {
            return true
        }
        else if ((value) === (ContentType.EMAIL_ADDRESS)) {
            return true
        }
        else if ((value) === (ContentType.BANK_CARD_NUMBER)) {
            return true
        }
        else if ((value) === (ContentType.ID_CARD_NUMBER)) {
            return true
        }
        else if ((value) === (ContentType.NICKNAME)) {
            return true
        }
        else if ((value) === (ContentType.DETAIL_INFO_WITHOUT_STREET)) {
            return true
        }
        else if ((value) === (ContentType.FORMAT_ADDRESS)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ContentType")
        }
    }
    static isContext(value: object|string|number|undefined|null|boolean, duplicated__ContextStub: boolean): boolean {
        if ((!duplicated__ContextStub) && (value?.hasOwnProperty("_ContextStub"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof Context")
        }
    }
    static isContextMenu(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof ContextMenu")
    }
    static isContextMenuAnimationOptions(value: object|string|number|undefined|null|boolean, duplicated_scale: boolean, duplicated_transition: boolean, duplicated_hoverScale: boolean): boolean {
        if ((!duplicated_scale) && (value?.hasOwnProperty("scale"))) {
            return true
        }
        else if ((!duplicated_transition) && (value?.hasOwnProperty("transition"))) {
            return true
        }
        else if ((!duplicated_hoverScale) && (value?.hasOwnProperty("hoverScale"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ContextMenuAnimationOptions")
        }
    }
    static isContextMenuEditStateFlags(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (ContextMenuEditStateFlags.NONE)) {
            return true
        }
        else if ((value) === (ContextMenuEditStateFlags.CAN_CUT)) {
            return true
        }
        else if ((value) === (ContextMenuEditStateFlags.CAN_COPY)) {
            return true
        }
        else if ((value) === (ContextMenuEditStateFlags.CAN_PASTE)) {
            return true
        }
        else if ((value) === (ContextMenuEditStateFlags.CAN_SELECT_ALL)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ContextMenuEditStateFlags")
        }
    }
    static isContextMenuInputFieldType(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (ContextMenuInputFieldType.None)) {
            return true
        }
        else if ((value) === (ContextMenuInputFieldType.PlainText)) {
            return true
        }
        else if ((value) === (ContextMenuInputFieldType.Password)) {
            return true
        }
        else if ((value) === (ContextMenuInputFieldType.Number)) {
            return true
        }
        else if ((value) === (ContextMenuInputFieldType.Telephone)) {
            return true
        }
        else if ((value) === (ContextMenuInputFieldType.Other)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ContextMenuInputFieldType")
        }
    }
    static isContextMenuMediaType(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (ContextMenuMediaType.None)) {
            return true
        }
        else if ((value) === (ContextMenuMediaType.Image)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ContextMenuMediaType")
        }
    }
    static isContextMenuOptions(value: object|string|number|undefined|null|boolean, duplicated_offset: boolean, duplicated_placement: boolean, duplicated_enableArrow: boolean, duplicated_arrowOffset: boolean, duplicated_preview: boolean, duplicated_borderRadius: boolean, duplicated_onAppear: boolean, duplicated_onDisappear: boolean, duplicated_aboutToAppear: boolean, duplicated_aboutToDisappear: boolean, duplicated_layoutRegionMargin: boolean, duplicated_previewAnimationOptions: boolean, duplicated_backgroundColor: boolean, duplicated_backgroundBlurStyle: boolean, duplicated_transition: boolean, duplicated_enableHoverMode: boolean): boolean {
        if ((!duplicated_offset) && (value?.hasOwnProperty("offset"))) {
            return true
        }
        else if ((!duplicated_placement) && (value?.hasOwnProperty("placement"))) {
            return true
        }
        else if ((!duplicated_enableArrow) && (value?.hasOwnProperty("enableArrow"))) {
            return true
        }
        else if ((!duplicated_arrowOffset) && (value?.hasOwnProperty("arrowOffset"))) {
            return true
        }
        else if ((!duplicated_preview) && (value?.hasOwnProperty("preview"))) {
            return true
        }
        else if ((!duplicated_borderRadius) && (value?.hasOwnProperty("borderRadius"))) {
            return true
        }
        else if ((!duplicated_onAppear) && (value?.hasOwnProperty("onAppear"))) {
            return true
        }
        else if ((!duplicated_onDisappear) && (value?.hasOwnProperty("onDisappear"))) {
            return true
        }
        else if ((!duplicated_aboutToAppear) && (value?.hasOwnProperty("aboutToAppear"))) {
            return true
        }
        else if ((!duplicated_aboutToDisappear) && (value?.hasOwnProperty("aboutToDisappear"))) {
            return true
        }
        else if ((!duplicated_layoutRegionMargin) && (value?.hasOwnProperty("layoutRegionMargin"))) {
            return true
        }
        else if ((!duplicated_previewAnimationOptions) && (value?.hasOwnProperty("previewAnimationOptions"))) {
            return true
        }
        else if ((!duplicated_backgroundColor) && (value?.hasOwnProperty("backgroundColor"))) {
            return true
        }
        else if ((!duplicated_backgroundBlurStyle) && (value?.hasOwnProperty("backgroundBlurStyle"))) {
            return true
        }
        else if ((!duplicated_transition) && (value?.hasOwnProperty("transition"))) {
            return true
        }
        else if ((!duplicated_enableHoverMode) && (value?.hasOwnProperty("enableHoverMode"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ContextMenuOptions")
        }
    }
    static isContextMenuSourceType(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (ContextMenuSourceType.None)) {
            return true
        }
        else if ((value) === (ContextMenuSourceType.Mouse)) {
            return true
        }
        else if ((value) === (ContextMenuSourceType.LongPress)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ContextMenuSourceType")
        }
    }
    static isControllerHandler(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof ControllerHandler")
    }
    static isControlSize(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (ControlSize.SMALL)) {
            return true
        }
        else if ((value) === (ControlSize.NORMAL)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ControlSize")
        }
    }
    static isCopyEvent(value: object|string|number|undefined|null|boolean, duplicated_preventDefault: boolean): boolean {
        if ((!duplicated_preventDefault) && (value?.hasOwnProperty("preventDefault"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof CopyEvent")
        }
    }
    static isCopyOptions(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (CopyOptions.None)) {
            return true
        }
        else if ((value) === (CopyOptions.InApp)) {
            return true
        }
        else if ((value) === (CopyOptions.LocalDevice)) {
            return true
        }
        else if ((value) === (CopyOptions.CROSS_DEVICE)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof CopyOptions")
        }
    }
    static isCounterAttribute(value: object|string|number|undefined|null|boolean, duplicated_onInc: boolean, duplicated_onDec: boolean, duplicated_enableDec: boolean, duplicated_enableInc: boolean): boolean {
        if ((!duplicated_onInc) && (value?.hasOwnProperty("onInc"))) {
            return true
        }
        else if ((!duplicated_onDec) && (value?.hasOwnProperty("onDec"))) {
            return true
        }
        else if ((!duplicated_enableDec) && (value?.hasOwnProperty("enableDec"))) {
            return true
        }
        else if ((!duplicated_enableInc) && (value?.hasOwnProperty("enableInc"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof CounterAttribute")
        }
    }
    static isCounterInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof CounterInterface")
    }
    static isCurrentDayStyle(value: object|string|number|undefined|null|boolean, duplicated_dayColor: boolean, duplicated_lunarColor: boolean, duplicated_markLunarColor: boolean, duplicated_dayFontSize: boolean, duplicated_lunarDayFontSize: boolean, duplicated_dayHeight: boolean, duplicated_dayWidth: boolean, duplicated_gregorianCalendarHeight: boolean, duplicated_dayYAxisOffset: boolean, duplicated_lunarDayYAxisOffset: boolean, duplicated_underscoreXAxisOffset: boolean, duplicated_underscoreYAxisOffset: boolean, duplicated_scheduleMarkerXAxisOffset: boolean, duplicated_scheduleMarkerYAxisOffset: boolean, duplicated_colSpace: boolean, duplicated_dailyFiveRowSpace: boolean, duplicated_dailySixRowSpace: boolean, duplicated_lunarHeight: boolean, duplicated_underscoreWidth: boolean, duplicated_underscoreLength: boolean, duplicated_scheduleMarkerRadius: boolean, duplicated_boundaryRowOffset: boolean, duplicated_boundaryColOffset: boolean): boolean {
        if ((!duplicated_dayColor) && (value?.hasOwnProperty("dayColor"))) {
            return true
        }
        else if ((!duplicated_lunarColor) && (value?.hasOwnProperty("lunarColor"))) {
            return true
        }
        else if ((!duplicated_markLunarColor) && (value?.hasOwnProperty("markLunarColor"))) {
            return true
        }
        else if ((!duplicated_dayFontSize) && (value?.hasOwnProperty("dayFontSize"))) {
            return true
        }
        else if ((!duplicated_lunarDayFontSize) && (value?.hasOwnProperty("lunarDayFontSize"))) {
            return true
        }
        else if ((!duplicated_dayHeight) && (value?.hasOwnProperty("dayHeight"))) {
            return true
        }
        else if ((!duplicated_dayWidth) && (value?.hasOwnProperty("dayWidth"))) {
            return true
        }
        else if ((!duplicated_gregorianCalendarHeight) && (value?.hasOwnProperty("gregorianCalendarHeight"))) {
            return true
        }
        else if ((!duplicated_dayYAxisOffset) && (value?.hasOwnProperty("dayYAxisOffset"))) {
            return true
        }
        else if ((!duplicated_lunarDayYAxisOffset) && (value?.hasOwnProperty("lunarDayYAxisOffset"))) {
            return true
        }
        else if ((!duplicated_underscoreXAxisOffset) && (value?.hasOwnProperty("underscoreXAxisOffset"))) {
            return true
        }
        else if ((!duplicated_underscoreYAxisOffset) && (value?.hasOwnProperty("underscoreYAxisOffset"))) {
            return true
        }
        else if ((!duplicated_scheduleMarkerXAxisOffset) && (value?.hasOwnProperty("scheduleMarkerXAxisOffset"))) {
            return true
        }
        else if ((!duplicated_scheduleMarkerYAxisOffset) && (value?.hasOwnProperty("scheduleMarkerYAxisOffset"))) {
            return true
        }
        else if ((!duplicated_colSpace) && (value?.hasOwnProperty("colSpace"))) {
            return true
        }
        else if ((!duplicated_dailyFiveRowSpace) && (value?.hasOwnProperty("dailyFiveRowSpace"))) {
            return true
        }
        else if ((!duplicated_dailySixRowSpace) && (value?.hasOwnProperty("dailySixRowSpace"))) {
            return true
        }
        else if ((!duplicated_lunarHeight) && (value?.hasOwnProperty("lunarHeight"))) {
            return true
        }
        else if ((!duplicated_underscoreWidth) && (value?.hasOwnProperty("underscoreWidth"))) {
            return true
        }
        else if ((!duplicated_underscoreLength) && (value?.hasOwnProperty("underscoreLength"))) {
            return true
        }
        else if ((!duplicated_scheduleMarkerRadius) && (value?.hasOwnProperty("scheduleMarkerRadius"))) {
            return true
        }
        else if ((!duplicated_boundaryRowOffset) && (value?.hasOwnProperty("boundaryRowOffset"))) {
            return true
        }
        else if ((!duplicated_boundaryColOffset) && (value?.hasOwnProperty("boundaryColOffset"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof CurrentDayStyle")
        }
    }
    static isCurve(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (Curve.Linear)) {
            return true
        }
        else if ((value) === (Curve.Ease)) {
            return true
        }
        else if ((value) === (Curve.EaseIn)) {
            return true
        }
        else if ((value) === (Curve.EaseOut)) {
            return true
        }
        else if ((value) === (Curve.EaseInOut)) {
            return true
        }
        else if ((value) === (Curve.FastOutSlowIn)) {
            return true
        }
        else if ((value) === (Curve.LinearOutSlowIn)) {
            return true
        }
        else if ((value) === (Curve.FastOutLinearIn)) {
            return true
        }
        else if ((value) === (Curve.ExtremeDeceleration)) {
            return true
        }
        else if ((value) === (Curve.Sharp)) {
            return true
        }
        else if ((value) === (Curve.Rhythm)) {
            return true
        }
        else if ((value) === (Curve.Smooth)) {
            return true
        }
        else if ((value) === (Curve.Friction)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof Curve")
        }
    }
    static isCustomComponent(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof CustomComponent")
    }
    static isCustomDialogController(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof CustomDialogController")
    }
    static isCustomDialogControllerOptions(value: object|string|number|undefined|null|boolean, duplicated_builder: boolean, duplicated_cancel: boolean, duplicated_autoCancel: boolean, duplicated_alignment: boolean, duplicated_offset: boolean, duplicated_customStyle: boolean, duplicated_gridCount: boolean, duplicated_maskColor: boolean, duplicated_maskRect: boolean, duplicated_openAnimation: boolean, duplicated_closeAnimation: boolean, duplicated_showInSubWindow: boolean, duplicated_backgroundColor: boolean, duplicated_cornerRadius: boolean, duplicated_isModal: boolean, duplicated_onWillDismiss: boolean, duplicated_width: boolean, duplicated_height: boolean, duplicated_borderWidth: boolean, duplicated_borderColor: boolean, duplicated_borderStyle: boolean, duplicated_shadow: boolean, duplicated_backgroundBlurStyle: boolean, duplicated_keyboardAvoidMode: boolean, duplicated_enableHoverMode: boolean, duplicated_hoverModeArea: boolean): boolean {
        if ((!duplicated_builder) && (value?.hasOwnProperty("builder"))) {
            return true
        }
        else if ((!duplicated_cancel) && (value?.hasOwnProperty("cancel"))) {
            return true
        }
        else if ((!duplicated_autoCancel) && (value?.hasOwnProperty("autoCancel"))) {
            return true
        }
        else if ((!duplicated_alignment) && (value?.hasOwnProperty("alignment"))) {
            return true
        }
        else if ((!duplicated_offset) && (value?.hasOwnProperty("offset"))) {
            return true
        }
        else if ((!duplicated_customStyle) && (value?.hasOwnProperty("customStyle"))) {
            return true
        }
        else if ((!duplicated_gridCount) && (value?.hasOwnProperty("gridCount"))) {
            return true
        }
        else if ((!duplicated_maskColor) && (value?.hasOwnProperty("maskColor"))) {
            return true
        }
        else if ((!duplicated_maskRect) && (value?.hasOwnProperty("maskRect"))) {
            return true
        }
        else if ((!duplicated_openAnimation) && (value?.hasOwnProperty("openAnimation"))) {
            return true
        }
        else if ((!duplicated_closeAnimation) && (value?.hasOwnProperty("closeAnimation"))) {
            return true
        }
        else if ((!duplicated_showInSubWindow) && (value?.hasOwnProperty("showInSubWindow"))) {
            return true
        }
        else if ((!duplicated_backgroundColor) && (value?.hasOwnProperty("backgroundColor"))) {
            return true
        }
        else if ((!duplicated_cornerRadius) && (value?.hasOwnProperty("cornerRadius"))) {
            return true
        }
        else if ((!duplicated_isModal) && (value?.hasOwnProperty("isModal"))) {
            return true
        }
        else if ((!duplicated_onWillDismiss) && (value?.hasOwnProperty("onWillDismiss"))) {
            return true
        }
        else if ((!duplicated_width) && (value?.hasOwnProperty("width"))) {
            return true
        }
        else if ((!duplicated_height) && (value?.hasOwnProperty("height"))) {
            return true
        }
        else if ((!duplicated_borderWidth) && (value?.hasOwnProperty("borderWidth"))) {
            return true
        }
        else if ((!duplicated_borderColor) && (value?.hasOwnProperty("borderColor"))) {
            return true
        }
        else if ((!duplicated_borderStyle) && (value?.hasOwnProperty("borderStyle"))) {
            return true
        }
        else if ((!duplicated_shadow) && (value?.hasOwnProperty("shadow"))) {
            return true
        }
        else if ((!duplicated_backgroundBlurStyle) && (value?.hasOwnProperty("backgroundBlurStyle"))) {
            return true
        }
        else if ((!duplicated_keyboardAvoidMode) && (value?.hasOwnProperty("keyboardAvoidMode"))) {
            return true
        }
        else if ((!duplicated_enableHoverMode) && (value?.hasOwnProperty("enableHoverMode"))) {
            return true
        }
        else if ((!duplicated_hoverModeArea) && (value?.hasOwnProperty("hoverModeArea"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof CustomDialogControllerOptions")
        }
    }
    static isCustomPopupOptions(value: object|string|number|undefined|null|boolean, duplicated_builder: boolean, duplicated_placement: boolean, duplicated_maskColor: boolean, duplicated_popupColor: boolean, duplicated_enableArrow: boolean, duplicated_autoCancel: boolean, duplicated_onStateChange: boolean, duplicated_arrowOffset: boolean, duplicated_showInSubWindow: boolean, duplicated_mask: boolean, duplicated_targetSpace: boolean, duplicated_offset: boolean, duplicated_width: boolean, duplicated_arrowPointPosition: boolean, duplicated_arrowWidth: boolean, duplicated_arrowHeight: boolean, duplicated_radius: boolean, duplicated_shadow: boolean, duplicated_backgroundBlurStyle: boolean, duplicated_focusable: boolean, duplicated_transition: boolean, duplicated_onWillDismiss: boolean, duplicated_enableHoverMode: boolean, duplicated_followTransformOfTarget: boolean): boolean {
        if ((!duplicated_builder) && (value?.hasOwnProperty("builder"))) {
            return true
        }
        else if ((!duplicated_placement) && (value?.hasOwnProperty("placement"))) {
            return true
        }
        else if ((!duplicated_maskColor) && (value?.hasOwnProperty("maskColor"))) {
            return true
        }
        else if ((!duplicated_popupColor) && (value?.hasOwnProperty("popupColor"))) {
            return true
        }
        else if ((!duplicated_enableArrow) && (value?.hasOwnProperty("enableArrow"))) {
            return true
        }
        else if ((!duplicated_autoCancel) && (value?.hasOwnProperty("autoCancel"))) {
            return true
        }
        else if ((!duplicated_onStateChange) && (value?.hasOwnProperty("onStateChange"))) {
            return true
        }
        else if ((!duplicated_arrowOffset) && (value?.hasOwnProperty("arrowOffset"))) {
            return true
        }
        else if ((!duplicated_showInSubWindow) && (value?.hasOwnProperty("showInSubWindow"))) {
            return true
        }
        else if ((!duplicated_mask) && (value?.hasOwnProperty("mask"))) {
            return true
        }
        else if ((!duplicated_targetSpace) && (value?.hasOwnProperty("targetSpace"))) {
            return true
        }
        else if ((!duplicated_offset) && (value?.hasOwnProperty("offset"))) {
            return true
        }
        else if ((!duplicated_width) && (value?.hasOwnProperty("width"))) {
            return true
        }
        else if ((!duplicated_arrowPointPosition) && (value?.hasOwnProperty("arrowPointPosition"))) {
            return true
        }
        else if ((!duplicated_arrowWidth) && (value?.hasOwnProperty("arrowWidth"))) {
            return true
        }
        else if ((!duplicated_arrowHeight) && (value?.hasOwnProperty("arrowHeight"))) {
            return true
        }
        else if ((!duplicated_radius) && (value?.hasOwnProperty("radius"))) {
            return true
        }
        else if ((!duplicated_shadow) && (value?.hasOwnProperty("shadow"))) {
            return true
        }
        else if ((!duplicated_backgroundBlurStyle) && (value?.hasOwnProperty("backgroundBlurStyle"))) {
            return true
        }
        else if ((!duplicated_focusable) && (value?.hasOwnProperty("focusable"))) {
            return true
        }
        else if ((!duplicated_transition) && (value?.hasOwnProperty("transition"))) {
            return true
        }
        else if ((!duplicated_onWillDismiss) && (value?.hasOwnProperty("onWillDismiss"))) {
            return true
        }
        else if ((!duplicated_enableHoverMode) && (value?.hasOwnProperty("enableHoverMode"))) {
            return true
        }
        else if ((!duplicated_followTransformOfTarget) && (value?.hasOwnProperty("followTransformOfTarget"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof CustomPopupOptions")
        }
    }
    static isCustomSpan(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof CustomSpan")
    }
    static isCustomSpanDrawInfo(value: object|string|number|undefined|null|boolean, duplicated_x: boolean, duplicated_lineTop: boolean, duplicated_lineBottom: boolean, duplicated_baseline: boolean): boolean {
        if ((!duplicated_x) && (value?.hasOwnProperty("x"))) {
            return true
        }
        else if ((!duplicated_lineTop) && (value?.hasOwnProperty("lineTop"))) {
            return true
        }
        else if ((!duplicated_lineBottom) && (value?.hasOwnProperty("lineBottom"))) {
            return true
        }
        else if ((!duplicated_baseline) && (value?.hasOwnProperty("baseline"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof CustomSpanDrawInfo")
        }
    }
    static isCustomSpanMeasureInfo(value: object|string|number|undefined|null|boolean, duplicated_fontSize: boolean): boolean {
        if ((!duplicated_fontSize) && (value?.hasOwnProperty("fontSize"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof CustomSpanMeasureInfo")
        }
    }
    static isCustomSpanMetrics(value: object|string|number|undefined|null|boolean, duplicated_width: boolean, duplicated_height: boolean): boolean {
        if ((!duplicated_width) && (value?.hasOwnProperty("width"))) {
            return true
        }
        else if ((!duplicated_height) && (value?.hasOwnProperty("height"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof CustomSpanMetrics")
        }
    }
    static isCustomTheme(value: object|string|number|undefined|null|boolean, duplicated__CustomThemeStub: boolean): boolean {
        if ((!duplicated__CustomThemeStub) && (value?.hasOwnProperty("_CustomThemeStub"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof CustomTheme")
        }
    }
    static isCutEvent(value: object|string|number|undefined|null|boolean, duplicated_preventDefault: boolean): boolean {
        if ((!duplicated_preventDefault) && (value?.hasOwnProperty("preventDefault"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof CutEvent")
        }
    }
    static isDataAddOperation(value: object|string|number|undefined|null|boolean, duplicated_type: boolean, duplicated_index: boolean, duplicated_count: boolean, duplicated_key: boolean): boolean {
        if ((!duplicated_type) && (value?.hasOwnProperty("type"))) {
            return true
        }
        else if ((!duplicated_index) && (value?.hasOwnProperty("index"))) {
            return true
        }
        else if ((!duplicated_count) && (value?.hasOwnProperty("count"))) {
            return true
        }
        else if ((!duplicated_key) && (value?.hasOwnProperty("key"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof DataAddOperation")
        }
    }
    static isDataChangeOperation(value: object|string|number|undefined|null|boolean, duplicated_type: boolean, duplicated_index: boolean, duplicated_key: boolean): boolean {
        if ((!duplicated_type) && (value?.hasOwnProperty("type"))) {
            return true
        }
        else if ((!duplicated_index) && (value?.hasOwnProperty("index"))) {
            return true
        }
        else if ((!duplicated_key) && (value?.hasOwnProperty("key"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof DataChangeOperation")
        }
    }
    static isDataDeleteOperation(value: object|string|number|undefined|null|boolean, duplicated_type: boolean, duplicated_index: boolean, duplicated_count: boolean): boolean {
        if ((!duplicated_type) && (value?.hasOwnProperty("type"))) {
            return true
        }
        else if ((!duplicated_index) && (value?.hasOwnProperty("index"))) {
            return true
        }
        else if ((!duplicated_count) && (value?.hasOwnProperty("count"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof DataDeleteOperation")
        }
    }
    static isDataExchangeOperation(value: object|string|number|undefined|null|boolean, duplicated_type: boolean, duplicated_index: boolean, duplicated_key: boolean): boolean {
        if ((!duplicated_type) && (value?.hasOwnProperty("type"))) {
            return true
        }
        else if ((!duplicated_index) && (value?.hasOwnProperty("index"))) {
            return true
        }
        else if ((!duplicated_key) && (value?.hasOwnProperty("key"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof DataExchangeOperation")
        }
    }
    static isDataMoveOperation(value: object|string|number|undefined|null|boolean, duplicated_type: boolean, duplicated_index: boolean, duplicated_key: boolean): boolean {
        if ((!duplicated_type) && (value?.hasOwnProperty("type"))) {
            return true
        }
        else if ((!duplicated_index) && (value?.hasOwnProperty("index"))) {
            return true
        }
        else if ((!duplicated_key) && (value?.hasOwnProperty("key"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof DataMoveOperation")
        }
    }
    static isDataOperationType(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (DataOperationType.ADD)) {
            return true
        }
        else if ((value) === (DataOperationType.DELETE)) {
            return true
        }
        else if ((value) === (DataOperationType.EXCHANGE)) {
            return true
        }
        else if ((value) === (DataOperationType.MOVE)) {
            return true
        }
        else if ((value) === (DataOperationType.CHANGE)) {
            return true
        }
        else if ((value) === (DataOperationType.RELOAD)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof DataOperationType")
        }
    }
    static isDataPanelAttribute(value: object|string|number|undefined|null|boolean, duplicated_closeEffect: boolean, duplicated_valueColors: boolean, duplicated_trackBackgroundColor: boolean, duplicated_strokeWidth: boolean, duplicated_trackShadow: boolean, duplicated_contentModifier: boolean): boolean {
        if ((!duplicated_closeEffect) && (value?.hasOwnProperty("closeEffect"))) {
            return true
        }
        else if ((!duplicated_valueColors) && (value?.hasOwnProperty("valueColors"))) {
            return true
        }
        else if ((!duplicated_trackBackgroundColor) && (value?.hasOwnProperty("trackBackgroundColor"))) {
            return true
        }
        else if ((!duplicated_strokeWidth) && (value?.hasOwnProperty("strokeWidth"))) {
            return true
        }
        else if ((!duplicated_trackShadow) && (value?.hasOwnProperty("trackShadow"))) {
            return true
        }
        else if ((!duplicated_contentModifier) && (value?.hasOwnProperty("contentModifier"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof DataPanelAttribute")
        }
    }
    static isDataPanelConfiguration(value: object|string|number|undefined|null|boolean, duplicated_values: boolean, duplicated_maxValue: boolean): boolean {
        if ((!duplicated_values) && (value?.hasOwnProperty("values"))) {
            return true
        }
        else if ((!duplicated_maxValue) && (value?.hasOwnProperty("maxValue"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof DataPanelConfiguration")
        }
    }
    static isDataPanelInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof DataPanelInterface")
    }
    static isDataPanelOptions(value: object|string|number|undefined|null|boolean, duplicated_values: boolean, duplicated_max: boolean, duplicated_type: boolean): boolean {
        if ((!duplicated_values) && (value?.hasOwnProperty("values"))) {
            return true
        }
        else if ((!duplicated_max) && (value?.hasOwnProperty("max"))) {
            return true
        }
        else if ((!duplicated_type) && (value?.hasOwnProperty("type"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof DataPanelOptions")
        }
    }
    static isDataPanelShadowOptions(value: object|string|number|undefined|null|boolean, duplicated_colors: boolean): boolean {
        if ((!duplicated_colors) && (value?.hasOwnProperty("colors"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof DataPanelShadowOptions")
        }
    }
    static isDataPanelType(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (DataPanelType.Line)) {
            return true
        }
        else if ((value) === (DataPanelType.Circle)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof DataPanelType")
        }
    }
    static isDataReloadOperation(value: object|string|number|undefined|null|boolean, duplicated_type: boolean): boolean {
        if ((!duplicated_type) && (value?.hasOwnProperty("type"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof DataReloadOperation")
        }
    }
    static isDataResubmissionHandler(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof DataResubmissionHandler")
    }
    static isDatePickerAttribute(value: object|string|number|undefined|null|boolean, duplicated_lunar: boolean, duplicated_disappearTextStyle: boolean, duplicated_textStyle: boolean, duplicated_selectedTextStyle: boolean, duplicated_onChange: boolean, duplicated_onDateChange: boolean): boolean {
        if ((!duplicated_lunar) && (value?.hasOwnProperty("lunar"))) {
            return true
        }
        else if ((!duplicated_disappearTextStyle) && (value?.hasOwnProperty("disappearTextStyle"))) {
            return true
        }
        else if ((!duplicated_textStyle) && (value?.hasOwnProperty("textStyle"))) {
            return true
        }
        else if ((!duplicated_selectedTextStyle) && (value?.hasOwnProperty("selectedTextStyle"))) {
            return true
        }
        else if ((!duplicated_onChange) && (value?.hasOwnProperty("onChange"))) {
            return true
        }
        else if ((!duplicated_onDateChange) && (value?.hasOwnProperty("onDateChange"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof DatePickerAttribute")
        }
    }
    static isDatePickerDialog(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof DatePickerDialog")
    }
    static isDatePickerDialogOptions(value: object|string|number|undefined|null|boolean, duplicated_lunar: boolean, duplicated_lunarSwitch: boolean, duplicated_lunarSwitchStyle: boolean, duplicated_showTime: boolean, duplicated_useMilitaryTime: boolean, duplicated_disappearTextStyle: boolean, duplicated_textStyle: boolean, duplicated_acceptButtonStyle: boolean, duplicated_cancelButtonStyle: boolean, duplicated_selectedTextStyle: boolean, duplicated_maskRect: boolean, duplicated_alignment: boolean, duplicated_offset: boolean, duplicated_onAccept: boolean, duplicated_onCancel: boolean, duplicated_onChange: boolean, duplicated_onDateAccept: boolean, duplicated_onDateChange: boolean, duplicated_backgroundColor: boolean, duplicated_backgroundBlurStyle: boolean, duplicated_onDidAppear: boolean, duplicated_onDidDisappear: boolean, duplicated_onWillAppear: boolean, duplicated_onWillDisappear: boolean, duplicated_shadow: boolean, duplicated_dateTimeOptions: boolean, duplicated_enableHoverMode: boolean, duplicated_hoverModeArea: boolean): boolean {
        if ((!duplicated_lunar) && (value?.hasOwnProperty("lunar"))) {
            return true
        }
        else if ((!duplicated_lunarSwitch) && (value?.hasOwnProperty("lunarSwitch"))) {
            return true
        }
        else if ((!duplicated_lunarSwitchStyle) && (value?.hasOwnProperty("lunarSwitchStyle"))) {
            return true
        }
        else if ((!duplicated_showTime) && (value?.hasOwnProperty("showTime"))) {
            return true
        }
        else if ((!duplicated_useMilitaryTime) && (value?.hasOwnProperty("useMilitaryTime"))) {
            return true
        }
        else if ((!duplicated_disappearTextStyle) && (value?.hasOwnProperty("disappearTextStyle"))) {
            return true
        }
        else if ((!duplicated_textStyle) && (value?.hasOwnProperty("textStyle"))) {
            return true
        }
        else if ((!duplicated_acceptButtonStyle) && (value?.hasOwnProperty("acceptButtonStyle"))) {
            return true
        }
        else if ((!duplicated_cancelButtonStyle) && (value?.hasOwnProperty("cancelButtonStyle"))) {
            return true
        }
        else if ((!duplicated_selectedTextStyle) && (value?.hasOwnProperty("selectedTextStyle"))) {
            return true
        }
        else if ((!duplicated_maskRect) && (value?.hasOwnProperty("maskRect"))) {
            return true
        }
        else if ((!duplicated_alignment) && (value?.hasOwnProperty("alignment"))) {
            return true
        }
        else if ((!duplicated_offset) && (value?.hasOwnProperty("offset"))) {
            return true
        }
        else if ((!duplicated_onAccept) && (value?.hasOwnProperty("onAccept"))) {
            return true
        }
        else if ((!duplicated_onCancel) && (value?.hasOwnProperty("onCancel"))) {
            return true
        }
        else if ((!duplicated_onChange) && (value?.hasOwnProperty("onChange"))) {
            return true
        }
        else if ((!duplicated_onDateAccept) && (value?.hasOwnProperty("onDateAccept"))) {
            return true
        }
        else if ((!duplicated_onDateChange) && (value?.hasOwnProperty("onDateChange"))) {
            return true
        }
        else if ((!duplicated_backgroundColor) && (value?.hasOwnProperty("backgroundColor"))) {
            return true
        }
        else if ((!duplicated_backgroundBlurStyle) && (value?.hasOwnProperty("backgroundBlurStyle"))) {
            return true
        }
        else if ((!duplicated_onDidAppear) && (value?.hasOwnProperty("onDidAppear"))) {
            return true
        }
        else if ((!duplicated_onDidDisappear) && (value?.hasOwnProperty("onDidDisappear"))) {
            return true
        }
        else if ((!duplicated_onWillAppear) && (value?.hasOwnProperty("onWillAppear"))) {
            return true
        }
        else if ((!duplicated_onWillDisappear) && (value?.hasOwnProperty("onWillDisappear"))) {
            return true
        }
        else if ((!duplicated_shadow) && (value?.hasOwnProperty("shadow"))) {
            return true
        }
        else if ((!duplicated_dateTimeOptions) && (value?.hasOwnProperty("dateTimeOptions"))) {
            return true
        }
        else if ((!duplicated_enableHoverMode) && (value?.hasOwnProperty("enableHoverMode"))) {
            return true
        }
        else if ((!duplicated_hoverModeArea) && (value?.hasOwnProperty("hoverModeArea"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof DatePickerDialogOptions")
        }
    }
    static isDatePickerInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof DatePickerInterface")
    }
    static isDatePickerOptions(value: object|string|number|undefined|null|boolean, duplicated_start: boolean, duplicated_end: boolean, duplicated_selected: boolean): boolean {
        if ((!duplicated_start) && (value?.hasOwnProperty("start"))) {
            return true
        }
        else if ((!duplicated_end) && (value?.hasOwnProperty("end"))) {
            return true
        }
        else if ((!duplicated_selected) && (value?.hasOwnProperty("selected"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof DatePickerOptions")
        }
    }
    static isDatePickerResult(value: object|string|number|undefined|null|boolean, duplicated_year: boolean, duplicated_month: boolean, duplicated_day: boolean): boolean {
        if ((!duplicated_year) && (value?.hasOwnProperty("year"))) {
            return true
        }
        else if ((!duplicated_month) && (value?.hasOwnProperty("month"))) {
            return true
        }
        else if ((!duplicated_day) && (value?.hasOwnProperty("day"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof DatePickerResult")
        }
    }
    static isDateTimeOptions(value: object|string|number|undefined|null|boolean, duplicated__DateTimeOptionsStub: boolean): boolean {
        if ((!duplicated__DateTimeOptionsStub) && (value?.hasOwnProperty("_DateTimeOptionsStub"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof DateTimeOptions")
        }
    }
    static isDecorationStyle(value: object|string|number|undefined|null|boolean, duplicated_type: boolean, duplicated_color: boolean, duplicated_style: boolean): boolean {
        if ((!duplicated_type) && (value?.hasOwnProperty("type"))) {
            return true
        }
        else if ((!duplicated_color) && (value?.hasOwnProperty("color"))) {
            return true
        }
        else if ((!duplicated_style) && (value?.hasOwnProperty("style"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof DecorationStyle")
        }
    }
    static isDecorationStyleInterface(value: object|string|number|undefined|null|boolean, duplicated_type: boolean, duplicated_color: boolean, duplicated_style: boolean): boolean {
        if ((!duplicated_type) && (value?.hasOwnProperty("type"))) {
            return true
        }
        else if ((!duplicated_color) && (value?.hasOwnProperty("color"))) {
            return true
        }
        else if ((!duplicated_style) && (value?.hasOwnProperty("style"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof DecorationStyleInterface")
        }
    }
    static isDecorationStyleResult(value: object|string|number|undefined|null|boolean, duplicated_type: boolean, duplicated_color: boolean, duplicated_style: boolean): boolean {
        if ((!duplicated_type) && (value?.hasOwnProperty("type"))) {
            return true
        }
        else if ((!duplicated_color) && (value?.hasOwnProperty("color"))) {
            return true
        }
        else if ((!duplicated_style) && (value?.hasOwnProperty("style"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof DecorationStyleResult")
        }
    }
    static isDeleteValue(value: object|string|number|undefined|null|boolean, duplicated_deleteOffset: boolean, duplicated_direction: boolean, duplicated_deleteValue: boolean): boolean {
        if ((!duplicated_deleteOffset) && (value?.hasOwnProperty("deleteOffset"))) {
            return true
        }
        else if ((!duplicated_direction) && (value?.hasOwnProperty("direction"))) {
            return true
        }
        else if ((!duplicated_deleteValue) && (value?.hasOwnProperty("deleteValue"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof DeleteValue")
        }
    }
    static isDialogAlignment(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (DialogAlignment.Top)) {
            return true
        }
        else if ((value) === (DialogAlignment.Center)) {
            return true
        }
        else if ((value) === (DialogAlignment.Bottom)) {
            return true
        }
        else if ((value) === (DialogAlignment.Default)) {
            return true
        }
        else if ((value) === (DialogAlignment.TopStart)) {
            return true
        }
        else if ((value) === (DialogAlignment.TopEnd)) {
            return true
        }
        else if ((value) === (DialogAlignment.CenterStart)) {
            return true
        }
        else if ((value) === (DialogAlignment.CenterEnd)) {
            return true
        }
        else if ((value) === (DialogAlignment.BottomStart)) {
            return true
        }
        else if ((value) === (DialogAlignment.BottomEnd)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof DialogAlignment")
        }
    }
    static isDialogButtonDirection(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (DialogButtonDirection.AUTO)) {
            return true
        }
        else if ((value) === (DialogButtonDirection.HORIZONTAL)) {
            return true
        }
        else if ((value) === (DialogButtonDirection.VERTICAL)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof DialogButtonDirection")
        }
    }
    static isDialogButtonStyle(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (DialogButtonStyle.DEFAULT)) {
            return true
        }
        else if ((value) === (DialogButtonStyle.HIGHLIGHT)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof DialogButtonStyle")
        }
    }
    static isDigitIndicator(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof DigitIndicator")
    }
    static isDirection(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (Direction.Ltr)) {
            return true
        }
        else if ((value) === (Direction.Rtl)) {
            return true
        }
        else if ((value) === (Direction.Auto)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof Direction")
        }
    }
    static isDirectionalEdgesT(value: object|string|number|undefined|null|boolean, duplicated_start: boolean, duplicated_end: boolean, duplicated_top: boolean, duplicated_bottom: boolean): boolean {
        if ((!duplicated_start) && (value?.hasOwnProperty("start"))) {
            return true
        }
        else if ((!duplicated_end) && (value?.hasOwnProperty("end"))) {
            return true
        }
        else if ((!duplicated_top) && (value?.hasOwnProperty("top"))) {
            return true
        }
        else if ((!duplicated_bottom) && (value?.hasOwnProperty("bottom"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof DirectionalEdgesT")
        }
    }
    static isDisappearSymbolEffect(value: object|string|number|undefined|null|boolean, duplicated_scope: boolean): boolean {
        if ((!duplicated_scope) && (value?.hasOwnProperty("scope"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof DisappearSymbolEffect")
        }
    }
    static isDismissContentCoverAction(value: object|string|number|undefined|null|boolean, duplicated_dismiss: boolean, duplicated_reason: boolean): boolean {
        if ((!duplicated_dismiss) && (value?.hasOwnProperty("dismiss"))) {
            return true
        }
        else if ((!duplicated_reason) && (value?.hasOwnProperty("reason"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof DismissContentCoverAction")
        }
    }
    static isDismissDialogAction(value: object|string|number|undefined|null|boolean, duplicated_dismiss: boolean, duplicated_reason: boolean): boolean {
        if ((!duplicated_dismiss) && (value?.hasOwnProperty("dismiss"))) {
            return true
        }
        else if ((!duplicated_reason) && (value?.hasOwnProperty("reason"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof DismissDialogAction")
        }
    }
    static isDismissPopupAction(value: object|string|number|undefined|null|boolean, duplicated_dismiss: boolean, duplicated_reason: boolean): boolean {
        if ((!duplicated_dismiss) && (value?.hasOwnProperty("dismiss"))) {
            return true
        }
        else if ((!duplicated_reason) && (value?.hasOwnProperty("reason"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof DismissPopupAction")
        }
    }
    static isDismissReason(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (DismissReason.PRESS_BACK)) {
            return true
        }
        else if ((value) === (DismissReason.TOUCH_OUTSIDE)) {
            return true
        }
        else if ((value) === (DismissReason.CLOSE_BUTTON)) {
            return true
        }
        else if ((value) === (DismissReason.SLIDE_DOWN)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof DismissReason")
        }
    }
    static isDismissSheetAction(value: object|string|number|undefined|null|boolean, duplicated_dismiss: boolean, duplicated_reason: boolean): boolean {
        if ((!duplicated_dismiss) && (value?.hasOwnProperty("dismiss"))) {
            return true
        }
        else if ((!duplicated_reason) && (value?.hasOwnProperty("reason"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof DismissSheetAction")
        }
    }
    static isDistributionType(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (DistributionType.UNIFORM)) {
            return true
        }
        else if ((value) === (DistributionType.GAUSSIAN)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof DistributionType")
        }
    }
    static isDisturbanceFieldShape(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (DisturbanceFieldShape.RECT)) {
            return true
        }
        else if ((value) === (DisturbanceFieldShape.CIRCLE)) {
            return true
        }
        else if ((value) === (DisturbanceFieldShape.ELLIPSE)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof DisturbanceFieldShape")
        }
    }
    static isDividerAttribute(value: object|string|number|undefined|null|boolean, duplicated_vertical: boolean, duplicated_color: boolean, duplicated_strokeWidth: boolean, duplicated_lineCap: boolean): boolean {
        if ((!duplicated_vertical) && (value?.hasOwnProperty("vertical"))) {
            return true
        }
        else if ((!duplicated_color) && (value?.hasOwnProperty("color"))) {
            return true
        }
        else if ((!duplicated_strokeWidth) && (value?.hasOwnProperty("strokeWidth"))) {
            return true
        }
        else if ((!duplicated_lineCap) && (value?.hasOwnProperty("lineCap"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof DividerAttribute")
        }
    }
    static isDividerInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof DividerInterface")
    }
    static isDividerOptions(value: object|string|number|undefined|null|boolean, duplicated_strokeWidth: boolean, duplicated_color: boolean, duplicated_startMargin: boolean, duplicated_endMargin: boolean): boolean {
        if ((!duplicated_strokeWidth) && (value?.hasOwnProperty("strokeWidth"))) {
            return true
        }
        else if ((!duplicated_color) && (value?.hasOwnProperty("color"))) {
            return true
        }
        else if ((!duplicated_startMargin) && (value?.hasOwnProperty("startMargin"))) {
            return true
        }
        else if ((!duplicated_endMargin) && (value?.hasOwnProperty("endMargin"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof DividerOptions")
        }
    }
    static isDividerStyle(value: object|string|number|undefined|null|boolean, duplicated_strokeWidth: boolean, duplicated_color: boolean, duplicated_startMargin: boolean, duplicated_endMargin: boolean): boolean {
        if ((!duplicated_strokeWidth) && (value?.hasOwnProperty("strokeWidth"))) {
            return true
        }
        else if ((!duplicated_color) && (value?.hasOwnProperty("color"))) {
            return true
        }
        else if ((!duplicated_startMargin) && (value?.hasOwnProperty("startMargin"))) {
            return true
        }
        else if ((!duplicated_endMargin) && (value?.hasOwnProperty("endMargin"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof DividerStyle")
        }
    }
    static isDividerStyleOptions(value: object|string|number|undefined|null|boolean, duplicated_strokeWidth: boolean, duplicated_color: boolean, duplicated_startMargin: boolean, duplicated_endMargin: boolean): boolean {
        if ((!duplicated_strokeWidth) && (value?.hasOwnProperty("strokeWidth"))) {
            return true
        }
        else if ((!duplicated_color) && (value?.hasOwnProperty("color"))) {
            return true
        }
        else if ((!duplicated_startMargin) && (value?.hasOwnProperty("startMargin"))) {
            return true
        }
        else if ((!duplicated_endMargin) && (value?.hasOwnProperty("endMargin"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof DividerStyleOptions")
        }
    }
    static isDotIndicator(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof DotIndicator")
    }
    static isDoubleAnimationParam(value: object|string|number|undefined|null|boolean, duplicated_propertyName: boolean, duplicated_startValue: boolean, duplicated_endValue: boolean, duplicated_duration: boolean, duplicated_delay: boolean, duplicated_curve: boolean, duplicated_onProgress: boolean, duplicated_onFinish: boolean): boolean {
        if ((!duplicated_propertyName) && (value?.hasOwnProperty("propertyName"))) {
            return true
        }
        else if ((!duplicated_startValue) && (value?.hasOwnProperty("startValue"))) {
            return true
        }
        else if ((!duplicated_endValue) && (value?.hasOwnProperty("endValue"))) {
            return true
        }
        else if ((!duplicated_duration) && (value?.hasOwnProperty("duration"))) {
            return true
        }
        else if ((!duplicated_delay) && (value?.hasOwnProperty("delay"))) {
            return true
        }
        else if ((!duplicated_curve) && (value?.hasOwnProperty("curve"))) {
            return true
        }
        else if ((!duplicated_onProgress) && (value?.hasOwnProperty("onProgress"))) {
            return true
        }
        else if ((!duplicated_onFinish) && (value?.hasOwnProperty("onFinish"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof DoubleAnimationParam")
        }
    }
    static isDpiFollowStrategy(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (DpiFollowStrategy.FOLLOW_HOST_DPI)) {
            return true
        }
        else if ((value) === (DpiFollowStrategy.FOLLOW_UI_EXTENSION_ABILITY_DPI)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof DpiFollowStrategy")
        }
    }
    static isDragBehavior(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (DragBehavior.COPY)) {
            return true
        }
        else if ((value) === (DragBehavior.MOVE)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof DragBehavior")
        }
    }
    static isDragEvent(value: object|string|number|undefined|null|boolean, duplicated_dragBehavior: boolean, duplicated_useCustomDropAnimation: boolean): boolean {
        if ((!duplicated_dragBehavior) && (value?.hasOwnProperty("dragBehavior"))) {
            return true
        }
        else if ((!duplicated_useCustomDropAnimation) && (value?.hasOwnProperty("useCustomDropAnimation"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof DragEvent")
        }
    }
    static isDragInteractionOptions(value: object|string|number|undefined|null|boolean, duplicated_isMultiSelectionEnabled: boolean, duplicated_defaultAnimationBeforeLifting: boolean): boolean {
        if ((!duplicated_isMultiSelectionEnabled) && (value?.hasOwnProperty("isMultiSelectionEnabled"))) {
            return true
        }
        else if ((!duplicated_defaultAnimationBeforeLifting) && (value?.hasOwnProperty("defaultAnimationBeforeLifting"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof DragInteractionOptions")
        }
    }
    static isDragItemInfo(value: object|string|number|undefined|null|boolean, duplicated_pixelMap: boolean, duplicated_builder: boolean, duplicated_extraInfo: boolean): boolean {
        if ((!duplicated_pixelMap) && (value?.hasOwnProperty("pixelMap"))) {
            return true
        }
        else if ((!duplicated_builder) && (value?.hasOwnProperty("builder"))) {
            return true
        }
        else if ((!duplicated_extraInfo) && (value?.hasOwnProperty("extraInfo"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof DragItemInfo")
        }
    }
    static isDragPreviewMode(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (DragPreviewMode.AUTO)) {
            return true
        }
        else if ((value) === (DragPreviewMode.DISABLE_SCALE)) {
            return true
        }
        else if ((value) === (DragPreviewMode.ENABLE_DEFAULT_SHADOW)) {
            return true
        }
        else if ((value) === (DragPreviewMode.ENABLE_DEFAULT_RADIUS)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof DragPreviewMode")
        }
    }
    static isDragPreviewOptions(value: object|string|number|undefined|null|boolean, duplicated_mode: boolean, duplicated_modifier: boolean, duplicated_numberBadge: boolean): boolean {
        if ((!duplicated_mode) && (value?.hasOwnProperty("mode"))) {
            return true
        }
        else if ((!duplicated_modifier) && (value?.hasOwnProperty("modifier"))) {
            return true
        }
        else if ((!duplicated_numberBadge) && (value?.hasOwnProperty("numberBadge"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof DragPreviewOptions")
        }
    }
    static isDragResult(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (DragResult.DRAG_SUCCESSFUL)) {
            return true
        }
        else if ((value) === (DragResult.DRAG_FAILED)) {
            return true
        }
        else if ((value) === (DragResult.DRAG_CANCELED)) {
            return true
        }
        else if ((value) === (DragResult.DROP_ENABLED)) {
            return true
        }
        else if ((value) === (DragResult.DROP_DISABLED)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof DragResult")
        }
    }
    static isDrawableDescriptor(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof DrawableDescriptor")
    }
    static isDrawContext(value: object|string|number|undefined|null|boolean, duplicated__DrawContextStub: boolean): boolean {
        if ((!duplicated__DrawContextStub) && (value?.hasOwnProperty("_DrawContextStub"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof DrawContext")
        }
    }
    static isDrawingCanvas(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof DrawingCanvas")
    }
    static isDrawingColorFilter(value: object|string|number|undefined|null|boolean, duplicated__DrawingColorFilterStub: boolean): boolean {
        if ((!duplicated__DrawingColorFilterStub) && (value?.hasOwnProperty("_DrawingColorFilterStub"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof DrawingColorFilter")
        }
    }
    static isDrawingLattice(value: object|string|number|undefined|null|boolean, duplicated__DrawingLatticeStub: boolean): boolean {
        if ((!duplicated__DrawingLatticeStub) && (value?.hasOwnProperty("_DrawingLatticeStub"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof DrawingLattice")
        }
    }
    static isDrawingRenderingContext(value: object|string|number|undefined|null|boolean, duplicated_size: boolean, duplicated_canvas: boolean): boolean {
        if ((!duplicated_size) && (value?.hasOwnProperty("size"))) {
            return true
        }
        else if ((!duplicated_canvas) && (value?.hasOwnProperty("canvas"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof DrawingRenderingContext")
        }
    }
    static isDrawModifier(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof DrawModifier")
    }
    static isDynamicNode(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof DynamicNode")
    }
    static isDynamicRangeMode(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (DynamicRangeMode.HIGH)) {
            return true
        }
        else if ((value) === (DynamicRangeMode.CONSTRAINT)) {
            return true
        }
        else if ((value) === (DynamicRangeMode.STANDARD)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof DynamicRangeMode")
        }
    }
    static isEclipseStyleOptions(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof EclipseStyleOptions")
    }
    static isEdge(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (Edge.Top)) {
            return true
        }
        else if ((value) === (Edge.Center)) {
            return true
        }
        else if ((value) === (Edge.Bottom)) {
            return true
        }
        else if ((value) === (Edge.Baseline)) {
            return true
        }
        else if ((value) === (Edge.Start)) {
            return true
        }
        else if ((value) === (Edge.Middle)) {
            return true
        }
        else if ((value) === (Edge.End)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof Edge")
        }
    }
    static isEdgeColors(value: object|string|number|undefined|null|boolean, duplicated_top: boolean, duplicated_right: boolean, duplicated_bottom: boolean, duplicated_left: boolean): boolean {
        if ((!duplicated_top) && (value?.hasOwnProperty("top"))) {
            return true
        }
        else if ((!duplicated_right) && (value?.hasOwnProperty("right"))) {
            return true
        }
        else if ((!duplicated_bottom) && (value?.hasOwnProperty("bottom"))) {
            return true
        }
        else if ((!duplicated_left) && (value?.hasOwnProperty("left"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof EdgeColors")
        }
    }
    static isEdgeEffect(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (EdgeEffect.Spring)) {
            return true
        }
        else if ((value) === (EdgeEffect.Fade)) {
            return true
        }
        else if ((value) === (EdgeEffect.None)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof EdgeEffect")
        }
    }
    static isEdgeEffectOptions(value: object|string|number|undefined|null|boolean, duplicated_alwaysEnabled: boolean): boolean {
        if ((!duplicated_alwaysEnabled) && (value?.hasOwnProperty("alwaysEnabled"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof EdgeEffectOptions")
        }
    }
    static isEdgeOutlineStyles(value: object|string|number|undefined|null|boolean, duplicated_top: boolean, duplicated_right: boolean, duplicated_bottom: boolean, duplicated_left: boolean): boolean {
        if ((!duplicated_top) && (value?.hasOwnProperty("top"))) {
            return true
        }
        else if ((!duplicated_right) && (value?.hasOwnProperty("right"))) {
            return true
        }
        else if ((!duplicated_bottom) && (value?.hasOwnProperty("bottom"))) {
            return true
        }
        else if ((!duplicated_left) && (value?.hasOwnProperty("left"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof EdgeOutlineStyles")
        }
    }
    static isEdgeOutlineWidths(value: object|string|number|undefined|null|boolean, duplicated_top: boolean, duplicated_right: boolean, duplicated_bottom: boolean, duplicated_left: boolean): boolean {
        if ((!duplicated_top) && (value?.hasOwnProperty("top"))) {
            return true
        }
        else if ((!duplicated_right) && (value?.hasOwnProperty("right"))) {
            return true
        }
        else if ((!duplicated_bottom) && (value?.hasOwnProperty("bottom"))) {
            return true
        }
        else if ((!duplicated_left) && (value?.hasOwnProperty("left"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof EdgeOutlineWidths")
        }
    }
    static isEdges(value: object|string|number|undefined|null|boolean, duplicated_top: boolean, duplicated_left: boolean, duplicated_bottom: boolean, duplicated_right: boolean): boolean {
        if ((!duplicated_top) && (value?.hasOwnProperty("top"))) {
            return true
        }
        else if ((!duplicated_left) && (value?.hasOwnProperty("left"))) {
            return true
        }
        else if ((!duplicated_bottom) && (value?.hasOwnProperty("bottom"))) {
            return true
        }
        else if ((!duplicated_right) && (value?.hasOwnProperty("right"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof Edges")
        }
    }
    static isEdgeStyles(value: object|string|number|undefined|null|boolean, duplicated_top: boolean, duplicated_right: boolean, duplicated_bottom: boolean, duplicated_left: boolean): boolean {
        if ((!duplicated_top) && (value?.hasOwnProperty("top"))) {
            return true
        }
        else if ((!duplicated_right) && (value?.hasOwnProperty("right"))) {
            return true
        }
        else if ((!duplicated_bottom) && (value?.hasOwnProperty("bottom"))) {
            return true
        }
        else if ((!duplicated_left) && (value?.hasOwnProperty("left"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof EdgeStyles")
        }
    }
    static isEdgeWidths(value: object|string|number|undefined|null|boolean, duplicated_top: boolean, duplicated_right: boolean, duplicated_bottom: boolean, duplicated_left: boolean): boolean {
        if ((!duplicated_top) && (value?.hasOwnProperty("top"))) {
            return true
        }
        else if ((!duplicated_right) && (value?.hasOwnProperty("right"))) {
            return true
        }
        else if ((!duplicated_bottom) && (value?.hasOwnProperty("bottom"))) {
            return true
        }
        else if ((!duplicated_left) && (value?.hasOwnProperty("left"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof EdgeWidths")
        }
    }
    static isEditMenuOptions(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof EditMenuOptions")
    }
    static isEditMode(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (EditMode.None)) {
            return true
        }
        else if ((value) === (EditMode.Deletable)) {
            return true
        }
        else if ((value) === (EditMode.Movable)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof EditMode")
        }
    }
    static isEffectComponentAttribute(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof EffectComponentAttribute")
    }
    static isEffectComponentInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof EffectComponentInterface")
    }
    static isEffectDirection(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (EffectDirection.DOWN)) {
            return true
        }
        else if ((value) === (EffectDirection.UP)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof EffectDirection")
        }
    }
    static isEffectFillStyle(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (EffectFillStyle.CUMULATIVE)) {
            return true
        }
        else if ((value) === (EffectFillStyle.ITERATIVE)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof EffectFillStyle")
        }
    }
    static isEffectScope(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (EffectScope.LAYER)) {
            return true
        }
        else if ((value) === (EffectScope.WHOLE)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof EffectScope")
        }
    }
    static isEffectType(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (EffectType.DEFAULT)) {
            return true
        }
        else if ((value) === (EffectType.WINDOW_EFFECT)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof EffectType")
        }
    }
    static isEllipseAttribute(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof EllipseAttribute")
    }
    static isEllipseInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof EllipseInterface")
    }
    static isEllipseOptions(value: object|string|number|undefined|null|boolean, duplicated_width: boolean, duplicated_height: boolean): boolean {
        if ((!duplicated_width) && (value?.hasOwnProperty("width"))) {
            return true
        }
        else if ((!duplicated_height) && (value?.hasOwnProperty("height"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof EllipseOptions")
        }
    }
    static isEllipseShape(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof EllipseShape")
    }
    static isEllipsisMode(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (EllipsisMode.START)) {
            return true
        }
        else if ((value) === (EllipsisMode.CENTER)) {
            return true
        }
        else if ((value) === (EllipsisMode.END)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof EllipsisMode")
        }
    }
    static isEmbeddedComponentAttribute(value: object|string|number|undefined|null|boolean, duplicated_onTerminated: boolean, duplicated_onError: boolean): boolean {
        if ((!duplicated_onTerminated) && (value?.hasOwnProperty("onTerminated"))) {
            return true
        }
        else if ((!duplicated_onError) && (value?.hasOwnProperty("onError"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof EmbeddedComponentAttribute")
        }
    }
    static isEmbeddedComponentInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof EmbeddedComponentInterface")
    }
    static isEmbeddedType(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (EmbeddedType.EMBEDDED_UI_EXTENSION)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof EmbeddedType")
        }
    }
    static isEmitterParticleOptions(value: object|string|number|undefined|null|boolean, duplicated_type: boolean, duplicated_config: boolean, duplicated_count: boolean, duplicated_lifetime: boolean, duplicated_lifetimeRange: boolean): boolean {
        if ((!duplicated_type) && (value?.hasOwnProperty("type"))) {
            return true
        }
        else if ((!duplicated_config) && (value?.hasOwnProperty("config"))) {
            return true
        }
        else if ((!duplicated_count) && (value?.hasOwnProperty("count"))) {
            return true
        }
        else if ((!duplicated_lifetime) && (value?.hasOwnProperty("lifetime"))) {
            return true
        }
        else if ((!duplicated_lifetimeRange) && (value?.hasOwnProperty("lifetimeRange"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof EmitterParticleOptions")
        }
    }
    static isEmitterProperty(value: object|string|number|undefined|null|boolean, duplicated_stub: boolean): boolean {
        if ((!duplicated_stub) && (value?.hasOwnProperty("stub"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof EmitterProperty")
        }
    }
    static isEnterKeyType(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (EnterKeyType.Go)) {
            return true
        }
        else if ((value) === (EnterKeyType.Search)) {
            return true
        }
        else if ((value) === (EnterKeyType.Send)) {
            return true
        }
        else if ((value) === (EnterKeyType.Next)) {
            return true
        }
        else if ((value) === (EnterKeyType.Done)) {
            return true
        }
        else if ((value) === (EnterKeyType.PREVIOUS)) {
            return true
        }
        else if ((value) === (EnterKeyType.NEW_LINE)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof EnterKeyType")
        }
    }
    static isEnvPropsOptions(value: object|string|number|undefined|null|boolean, duplicated_key: boolean, duplicated_defaultValue: boolean): boolean {
        if ((!duplicated_key) && (value?.hasOwnProperty("key"))) {
            return true
        }
        else if ((!duplicated_defaultValue) && (value?.hasOwnProperty("defaultValue"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof EnvPropsOptions")
        }
    }
    static isEventEmulator(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof EventEmulator")
    }
    static isEventResult(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof EventResult")
    }
    static isEventTarget(value: object|string|number|undefined|null|boolean, duplicated_area: boolean): boolean {
        if ((!duplicated_area) && (value?.hasOwnProperty("area"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof EventTarget")
        }
    }
    static isEventTargetInfo(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof EventTargetInfo")
    }
    static isExchangeIndex(value: object|string|number|undefined|null|boolean, duplicated_start: boolean, duplicated_end: boolean): boolean {
        if ((!duplicated_start) && (value?.hasOwnProperty("start"))) {
            return true
        }
        else if ((!duplicated_end) && (value?.hasOwnProperty("end"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ExchangeIndex")
        }
    }
    static isExchangeKey(value: object|string|number|undefined|null|boolean, duplicated_start: boolean, duplicated_end: boolean): boolean {
        if ((!duplicated_start) && (value?.hasOwnProperty("start"))) {
            return true
        }
        else if ((!duplicated_end) && (value?.hasOwnProperty("end"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ExchangeKey")
        }
    }
    static isExpandedMenuItemOptions(value: object|string|number|undefined|null|boolean, duplicated_content: boolean, duplicated_startIcon: boolean, duplicated_action: boolean): boolean {
        if ((!duplicated_content) && (value?.hasOwnProperty("content"))) {
            return true
        }
        else if ((!duplicated_action) && (value?.hasOwnProperty("action"))) {
            return true
        }
        else if ((!duplicated_startIcon) && (value?.hasOwnProperty("startIcon"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ExpandedMenuItemOptions")
        }
    }
    static isExpectedFrameRateRange(value: object|string|number|undefined|null|boolean, duplicated_min: boolean, duplicated_max: boolean, duplicated_expected: boolean): boolean {
        if ((!duplicated_min) && (value?.hasOwnProperty("min"))) {
            return true
        }
        else if ((!duplicated_max) && (value?.hasOwnProperty("max"))) {
            return true
        }
        else if ((!duplicated_expected) && (value?.hasOwnProperty("expected"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ExpectedFrameRateRange")
        }
    }
    static isFadingEdgeOptions(value: object|string|number|undefined|null|boolean, duplicated_fadingEdgeLength: boolean): boolean {
        if ((!duplicated_fadingEdgeLength) && (value?.hasOwnProperty("fadingEdgeLength"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof FadingEdgeOptions")
        }
    }
    static isFileSelectorMode(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (FileSelectorMode.FileOpenMode)) {
            return true
        }
        else if ((value) === (FileSelectorMode.FileOpenMultipleMode)) {
            return true
        }
        else if ((value) === (FileSelectorMode.FileOpenFolderMode)) {
            return true
        }
        else if ((value) === (FileSelectorMode.FileSaveMode)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof FileSelectorMode")
        }
    }
    static isFileSelectorParam(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof FileSelectorParam")
    }
    static isFileSelectorResult(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof FileSelectorResult")
    }
    static isFillMode(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (FillMode.None)) {
            return true
        }
        else if ((value) === (FillMode.Forwards)) {
            return true
        }
        else if ((value) === (FillMode.Backwards)) {
            return true
        }
        else if ((value) === (FillMode.Both)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof FillMode")
        }
    }
    static isFilter(value: object|string|number|undefined|null|boolean, duplicated__FilterStub: boolean): boolean {
        if ((!duplicated__FilterStub) && (value?.hasOwnProperty("_FilterStub"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof Filter")
        }
    }
    static isFingerInfo(value: object|string|number|undefined|null|boolean, duplicated_id: boolean, duplicated_globalX: boolean, duplicated_globalY: boolean, duplicated_localX: boolean, duplicated_localY: boolean, duplicated_displayX: boolean, duplicated_displayY: boolean): boolean {
        if ((!duplicated_id) && (value?.hasOwnProperty("id"))) {
            return true
        }
        else if ((!duplicated_globalX) && (value?.hasOwnProperty("globalX"))) {
            return true
        }
        else if ((!duplicated_globalY) && (value?.hasOwnProperty("globalY"))) {
            return true
        }
        else if ((!duplicated_localX) && (value?.hasOwnProperty("localX"))) {
            return true
        }
        else if ((!duplicated_localY) && (value?.hasOwnProperty("localY"))) {
            return true
        }
        else if ((!duplicated_displayX) && (value?.hasOwnProperty("displayX"))) {
            return true
        }
        else if ((!duplicated_displayY) && (value?.hasOwnProperty("displayY"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof FingerInfo")
        }
    }
    static isFinishCallbackType(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (FinishCallbackType.REMOVED)) {
            return true
        }
        else if ((value) === (FinishCallbackType.LOGICALLY)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof FinishCallbackType")
        }
    }
    static isFirstMeaningfulPaint(value: object|string|number|undefined|null|boolean, duplicated_navigationStartTime: boolean, duplicated_firstMeaningfulPaintTime: boolean): boolean {
        if ((!duplicated_navigationStartTime) && (value?.hasOwnProperty("navigationStartTime"))) {
            return true
        }
        else if ((!duplicated_firstMeaningfulPaintTime) && (value?.hasOwnProperty("firstMeaningfulPaintTime"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof FirstMeaningfulPaint")
        }
    }
    static isFlexAlign(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (FlexAlign.Start)) {
            return true
        }
        else if ((value) === (FlexAlign.Center)) {
            return true
        }
        else if ((value) === (FlexAlign.End)) {
            return true
        }
        else if ((value) === (FlexAlign.SpaceBetween)) {
            return true
        }
        else if ((value) === (FlexAlign.SpaceAround)) {
            return true
        }
        else if ((value) === (FlexAlign.SpaceEvenly)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof FlexAlign")
        }
    }
    static isFlexAttribute(value: object|string|number|undefined|null|boolean, duplicated_pointLight: boolean): boolean {
        if ((!duplicated_pointLight) && (value?.hasOwnProperty("pointLight"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof FlexAttribute")
        }
    }
    static isFlexDirection(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (FlexDirection.Row)) {
            return true
        }
        else if ((value) === (FlexDirection.Column)) {
            return true
        }
        else if ((value) === (FlexDirection.RowReverse)) {
            return true
        }
        else if ((value) === (FlexDirection.ColumnReverse)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof FlexDirection")
        }
    }
    static isFlexInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof FlexInterface")
    }
    static isFlexOptions(value: object|string|number|undefined|null|boolean, duplicated_direction: boolean, duplicated_wrap: boolean, duplicated_justifyContent: boolean, duplicated_alignItems: boolean, duplicated_alignContent: boolean, duplicated_space: boolean): boolean {
        if ((!duplicated_direction) && (value?.hasOwnProperty("direction"))) {
            return true
        }
        else if ((!duplicated_wrap) && (value?.hasOwnProperty("wrap"))) {
            return true
        }
        else if ((!duplicated_justifyContent) && (value?.hasOwnProperty("justifyContent"))) {
            return true
        }
        else if ((!duplicated_alignItems) && (value?.hasOwnProperty("alignItems"))) {
            return true
        }
        else if ((!duplicated_alignContent) && (value?.hasOwnProperty("alignContent"))) {
            return true
        }
        else if ((!duplicated_space) && (value?.hasOwnProperty("space"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof FlexOptions")
        }
    }
    static isFlexSpaceOptions(value: object|string|number|undefined|null|boolean, duplicated_main: boolean, duplicated_cross: boolean): boolean {
        if ((!duplicated_main) && (value?.hasOwnProperty("main"))) {
            return true
        }
        else if ((!duplicated_cross) && (value?.hasOwnProperty("cross"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof FlexSpaceOptions")
        }
    }
    static isFlexWrap(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (FlexWrap.NoWrap)) {
            return true
        }
        else if ((value) === (FlexWrap.Wrap)) {
            return true
        }
        else if ((value) === (FlexWrap.WrapReverse)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof FlexWrap")
        }
    }
    static isFlowItemAttribute(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof FlowItemAttribute")
    }
    static isFlowItemInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof FlowItemInterface")
    }
    static isFocusBoxStyle(value: object|string|number|undefined|null|boolean, duplicated_margin: boolean, duplicated_strokeColor: boolean, duplicated_strokeWidth: boolean): boolean {
        if ((!duplicated_margin) && (value?.hasOwnProperty("margin"))) {
            return true
        }
        else if ((!duplicated_strokeColor) && (value?.hasOwnProperty("strokeColor"))) {
            return true
        }
        else if ((!duplicated_strokeWidth) && (value?.hasOwnProperty("strokeWidth"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof FocusBoxStyle")
        }
    }
    static isFocusController(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof FocusController")
    }
    static isFocusPriority(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (FocusPriority.AUTO)) {
            return true
        }
        else if ((value) === (FocusPriority.PRIOR)) {
            return true
        }
        else if ((value) === (FocusPriority.PREVIOUS)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof FocusPriority")
        }
    }
    static isFolderStackAttribute(value: object|string|number|undefined|null|boolean, duplicated_alignContent: boolean, duplicated_onFolderStateChange: boolean, duplicated_onHoverStatusChange: boolean, duplicated_enableAnimation: boolean, duplicated_autoHalfFold: boolean): boolean {
        if ((!duplicated_alignContent) && (value?.hasOwnProperty("alignContent"))) {
            return true
        }
        else if ((!duplicated_onFolderStateChange) && (value?.hasOwnProperty("onFolderStateChange"))) {
            return true
        }
        else if ((!duplicated_onHoverStatusChange) && (value?.hasOwnProperty("onHoverStatusChange"))) {
            return true
        }
        else if ((!duplicated_enableAnimation) && (value?.hasOwnProperty("enableAnimation"))) {
            return true
        }
        else if ((!duplicated_autoHalfFold) && (value?.hasOwnProperty("autoHalfFold"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof FolderStackAttribute")
        }
    }
    static isFolderStackInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof FolderStackInterface")
    }
    static isFolderStackOptions(value: object|string|number|undefined|null|boolean, duplicated_upperItems: boolean): boolean {
        if ((!duplicated_upperItems) && (value?.hasOwnProperty("upperItems"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof FolderStackOptions")
        }
    }
    static isFoldStatus(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (FoldStatus.FOLD_STATUS_UNKNOWN)) {
            return true
        }
        else if ((value) === (FoldStatus.FOLD_STATUS_EXPANDED)) {
            return true
        }
        else if ((value) === (FoldStatus.FOLD_STATUS_FOLDED)) {
            return true
        }
        else if ((value) === (FoldStatus.FOLD_STATUS_HALF_FOLDED)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof FoldStatus")
        }
    }
    static isFont(value: object|string|number|undefined|null|boolean, duplicated_size: boolean, duplicated_weight: boolean, duplicated_family: boolean, duplicated_style: boolean): boolean {
        if ((!duplicated_size) && (value?.hasOwnProperty("size"))) {
            return true
        }
        else if ((!duplicated_weight) && (value?.hasOwnProperty("weight"))) {
            return true
        }
        else if ((!duplicated_family) && (value?.hasOwnProperty("family"))) {
            return true
        }
        else if ((!duplicated_style) && (value?.hasOwnProperty("style"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof Font")
        }
    }
    static isFontInfo(value: object|string|number|undefined|null|boolean, duplicated_path: boolean, duplicated_postScriptName: boolean, duplicated_fullName: boolean, duplicated_family: boolean, duplicated_subfamily: boolean, duplicated_weight: boolean, duplicated_width: boolean, duplicated_italic: boolean, duplicated_monoSpace: boolean, duplicated_symbolic: boolean): boolean {
        if ((!duplicated_path) && (value?.hasOwnProperty("path"))) {
            return true
        }
        else if ((!duplicated_postScriptName) && (value?.hasOwnProperty("postScriptName"))) {
            return true
        }
        else if ((!duplicated_fullName) && (value?.hasOwnProperty("fullName"))) {
            return true
        }
        else if ((!duplicated_family) && (value?.hasOwnProperty("family"))) {
            return true
        }
        else if ((!duplicated_subfamily) && (value?.hasOwnProperty("subfamily"))) {
            return true
        }
        else if ((!duplicated_weight) && (value?.hasOwnProperty("weight"))) {
            return true
        }
        else if ((!duplicated_width) && (value?.hasOwnProperty("width"))) {
            return true
        }
        else if ((!duplicated_italic) && (value?.hasOwnProperty("italic"))) {
            return true
        }
        else if ((!duplicated_monoSpace) && (value?.hasOwnProperty("monoSpace"))) {
            return true
        }
        else if ((!duplicated_symbolic) && (value?.hasOwnProperty("symbolic"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof FontInfo")
        }
    }
    static isFontOptions(value: object|string|number|undefined|null|boolean, duplicated_familyName: boolean, duplicated_familySrc: boolean): boolean {
        if ((!duplicated_familyName) && (value?.hasOwnProperty("familyName"))) {
            return true
        }
        else if ((!duplicated_familySrc) && (value?.hasOwnProperty("familySrc"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof FontOptions")
        }
    }
    static isFontSettingOptions(value: object|string|number|undefined|null|boolean, duplicated_enableVariableFontWeight: boolean): boolean {
        if ((!duplicated_enableVariableFontWeight) && (value?.hasOwnProperty("enableVariableFontWeight"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof FontSettingOptions")
        }
    }
    static isFontStyle(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (FontStyle.Normal)) {
            return true
        }
        else if ((value) === (FontStyle.Italic)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof FontStyle")
        }
    }
    static isFontWeight(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (FontWeight.Lighter)) {
            return true
        }
        else if ((value) === (FontWeight.Normal)) {
            return true
        }
        else if ((value) === (FontWeight.Regular)) {
            return true
        }
        else if ((value) === (FontWeight.Medium)) {
            return true
        }
        else if ((value) === (FontWeight.Bold)) {
            return true
        }
        else if ((value) === (FontWeight.Bolder)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof FontWeight")
        }
    }
    static isForegroundBlurStyleOptions(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof ForegroundBlurStyleOptions")
    }
    static isForegroundEffectOptions(value: object|string|number|undefined|null|boolean, duplicated_radius: boolean): boolean {
        if ((!duplicated_radius) && (value?.hasOwnProperty("radius"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ForegroundEffectOptions")
        }
    }
    static isFormCallbackInfo(value: object|string|number|undefined|null|boolean, duplicated_id: boolean, duplicated_idString: boolean): boolean {
        if ((!duplicated_id) && (value?.hasOwnProperty("id"))) {
            return true
        }
        else if ((!duplicated_idString) && (value?.hasOwnProperty("idString"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof FormCallbackInfo")
        }
    }
    static isFormComponentAttribute(value: object|string|number|undefined|null|boolean, duplicated_size: boolean, duplicated_moduleName: boolean, duplicated_dimension: boolean, duplicated_allowUpdate: boolean, duplicated_visibility: boolean, duplicated_onAcquired: boolean, duplicated_onError: boolean, duplicated_onRouter: boolean, duplicated_onUninstall: boolean, duplicated_onLoad: boolean): boolean {
        if ((!duplicated_size) && (value?.hasOwnProperty("size"))) {
            return true
        }
        else if ((!duplicated_moduleName) && (value?.hasOwnProperty("moduleName"))) {
            return true
        }
        else if ((!duplicated_dimension) && (value?.hasOwnProperty("dimension"))) {
            return true
        }
        else if ((!duplicated_allowUpdate) && (value?.hasOwnProperty("allowUpdate"))) {
            return true
        }
        else if ((!duplicated_visibility) && (value?.hasOwnProperty("visibility"))) {
            return true
        }
        else if ((!duplicated_onAcquired) && (value?.hasOwnProperty("onAcquired"))) {
            return true
        }
        else if ((!duplicated_onError) && (value?.hasOwnProperty("onError"))) {
            return true
        }
        else if ((!duplicated_onRouter) && (value?.hasOwnProperty("onRouter"))) {
            return true
        }
        else if ((!duplicated_onUninstall) && (value?.hasOwnProperty("onUninstall"))) {
            return true
        }
        else if ((!duplicated_onLoad) && (value?.hasOwnProperty("onLoad"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof FormComponentAttribute")
        }
    }
    static isFormComponentInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof FormComponentInterface")
    }
    static isFormDimension(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (FormDimension.Dimension_1_2)) {
            return true
        }
        else if ((value) === (FormDimension.Dimension_2_2)) {
            return true
        }
        else if ((value) === (FormDimension.Dimension_2_4)) {
            return true
        }
        else if ((value) === (FormDimension.Dimension_4_4)) {
            return true
        }
        else if ((value) === (FormDimension.Dimension_2_1)) {
            return true
        }
        else if ((value) === (FormDimension.DIMENSION_1_1)) {
            return true
        }
        else if ((value) === (FormDimension.DIMENSION_6_4)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof FormDimension")
        }
    }
    static isFormInfo(value: object|string|number|undefined|null|boolean, duplicated_id: boolean, duplicated_name: boolean, duplicated_bundle: boolean, duplicated_ability: boolean, duplicated_module: boolean, duplicated_dimension: boolean, duplicated_temporary: boolean, duplicated_want: boolean, duplicated_renderingMode: boolean, duplicated_shape: boolean): boolean {
        if ((!duplicated_id) && (value?.hasOwnProperty("id"))) {
            return true
        }
        else if ((!duplicated_name) && (value?.hasOwnProperty("name"))) {
            return true
        }
        else if ((!duplicated_bundle) && (value?.hasOwnProperty("bundle"))) {
            return true
        }
        else if ((!duplicated_ability) && (value?.hasOwnProperty("ability"))) {
            return true
        }
        else if ((!duplicated_module) && (value?.hasOwnProperty("module"))) {
            return true
        }
        else if ((!duplicated_dimension) && (value?.hasOwnProperty("dimension"))) {
            return true
        }
        else if ((!duplicated_temporary) && (value?.hasOwnProperty("temporary"))) {
            return true
        }
        else if ((!duplicated_want) && (value?.hasOwnProperty("want"))) {
            return true
        }
        else if ((!duplicated_renderingMode) && (value?.hasOwnProperty("renderingMode"))) {
            return true
        }
        else if ((!duplicated_shape) && (value?.hasOwnProperty("shape"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof FormInfo")
        }
    }
    static isFormLinkAttribute(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof FormLinkAttribute")
    }
    static isFormLinkInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof FormLinkInterface")
    }
    static isFormLinkOptions(value: object|string|number|undefined|null|boolean, duplicated_action: boolean, duplicated_moduleName: boolean, duplicated_bundleName: boolean, duplicated_abilityName: boolean, duplicated_uri: boolean, duplicated_params: boolean): boolean {
        if ((!duplicated_action) && (value?.hasOwnProperty("action"))) {
            return true
        }
        else if ((!duplicated_moduleName) && (value?.hasOwnProperty("moduleName"))) {
            return true
        }
        else if ((!duplicated_bundleName) && (value?.hasOwnProperty("bundleName"))) {
            return true
        }
        else if ((!duplicated_abilityName) && (value?.hasOwnProperty("abilityName"))) {
            return true
        }
        else if ((!duplicated_uri) && (value?.hasOwnProperty("uri"))) {
            return true
        }
        else if ((!duplicated_params) && (value?.hasOwnProperty("params"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof FormLinkOptions")
        }
    }
    static isFormRenderingMode(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (FormRenderingMode.FULL_COLOR)) {
            return true
        }
        else if ((value) === (FormRenderingMode.SINGLE_COLOR)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof FormRenderingMode")
        }
    }
    static isFormShape(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (FormShape.RECT)) {
            return true
        }
        else if ((value) === (FormShape.CIRCLE)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof FormShape")
        }
    }
    static isFrameNode(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof FrameNode")
    }
    static isFrictionMotion(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof FrictionMotion")
    }
    static isFullScreenEnterEvent(value: object|string|number|undefined|null|boolean, duplicated_handler: boolean, duplicated_videoWidth: boolean, duplicated_videoHeight: boolean): boolean {
        if ((!duplicated_handler) && (value?.hasOwnProperty("handler"))) {
            return true
        }
        else if ((!duplicated_videoWidth) && (value?.hasOwnProperty("videoWidth"))) {
            return true
        }
        else if ((!duplicated_videoHeight) && (value?.hasOwnProperty("videoHeight"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof FullScreenEnterEvent")
        }
    }
    static isFullScreenExitHandler(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof FullScreenExitHandler")
    }
    static isFullscreenInfo(value: object|string|number|undefined|null|boolean, duplicated_fullscreen: boolean): boolean {
        if ((!duplicated_fullscreen) && (value?.hasOwnProperty("fullscreen"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof FullscreenInfo")
        }
    }
    static isFunctionKey(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (FunctionKey.ESC)) {
            return true
        }
        else if ((value) === (FunctionKey.F1)) {
            return true
        }
        else if ((value) === (FunctionKey.F2)) {
            return true
        }
        else if ((value) === (FunctionKey.F3)) {
            return true
        }
        else if ((value) === (FunctionKey.F4)) {
            return true
        }
        else if ((value) === (FunctionKey.F5)) {
            return true
        }
        else if ((value) === (FunctionKey.F6)) {
            return true
        }
        else if ((value) === (FunctionKey.F7)) {
            return true
        }
        else if ((value) === (FunctionKey.F8)) {
            return true
        }
        else if ((value) === (FunctionKey.F9)) {
            return true
        }
        else if ((value) === (FunctionKey.F10)) {
            return true
        }
        else if ((value) === (FunctionKey.F11)) {
            return true
        }
        else if ((value) === (FunctionKey.F12)) {
            return true
        }
        else if ((value) === (FunctionKey.TAB)) {
            return true
        }
        else if ((value) === (FunctionKey.DPAD_UP)) {
            return true
        }
        else if ((value) === (FunctionKey.DPAD_DOWN)) {
            return true
        }
        else if ((value) === (FunctionKey.DPAD_LEFT)) {
            return true
        }
        else if ((value) === (FunctionKey.DPAD_RIGHT)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof FunctionKey")
        }
    }
    static isGaugeAttribute(value: object|string|number|undefined|null|boolean, duplicated_value: boolean, duplicated_startAngle: boolean, duplicated_endAngle: boolean, duplicated_colors: boolean, duplicated_strokeWidth: boolean, duplicated_description: boolean, duplicated_trackShadow: boolean, duplicated_indicator: boolean, duplicated_privacySensitive: boolean, duplicated_contentModifier: boolean): boolean {
        if ((!duplicated_value) && (value?.hasOwnProperty("value"))) {
            return true
        }
        else if ((!duplicated_startAngle) && (value?.hasOwnProperty("startAngle"))) {
            return true
        }
        else if ((!duplicated_endAngle) && (value?.hasOwnProperty("endAngle"))) {
            return true
        }
        else if ((!duplicated_colors) && (value?.hasOwnProperty("colors"))) {
            return true
        }
        else if ((!duplicated_strokeWidth) && (value?.hasOwnProperty("strokeWidth"))) {
            return true
        }
        else if ((!duplicated_description) && (value?.hasOwnProperty("description"))) {
            return true
        }
        else if ((!duplicated_trackShadow) && (value?.hasOwnProperty("trackShadow"))) {
            return true
        }
        else if ((!duplicated_indicator) && (value?.hasOwnProperty("indicator"))) {
            return true
        }
        else if ((!duplicated_privacySensitive) && (value?.hasOwnProperty("privacySensitive"))) {
            return true
        }
        else if ((!duplicated_contentModifier) && (value?.hasOwnProperty("contentModifier"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof GaugeAttribute")
        }
    }
    static isGaugeConfiguration(value: object|string|number|undefined|null|boolean, duplicated_value: boolean, duplicated_min: boolean, duplicated_max: boolean): boolean {
        if ((!duplicated_value) && (value?.hasOwnProperty("value"))) {
            return true
        }
        else if ((!duplicated_min) && (value?.hasOwnProperty("min"))) {
            return true
        }
        else if ((!duplicated_max) && (value?.hasOwnProperty("max"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof GaugeConfiguration")
        }
    }
    static isGaugeIndicatorOptions(value: object|string|number|undefined|null|boolean, duplicated_icon: boolean, duplicated_space: boolean): boolean {
        if ((!duplicated_icon) && (value?.hasOwnProperty("icon"))) {
            return true
        }
        else if ((!duplicated_space) && (value?.hasOwnProperty("space"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof GaugeIndicatorOptions")
        }
    }
    static isGaugeInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof GaugeInterface")
    }
    static isGaugeOptions(value: object|string|number|undefined|null|boolean, duplicated_value: boolean, duplicated_min: boolean, duplicated_max: boolean): boolean {
        if ((!duplicated_value) && (value?.hasOwnProperty("value"))) {
            return true
        }
        else if ((!duplicated_min) && (value?.hasOwnProperty("min"))) {
            return true
        }
        else if ((!duplicated_max) && (value?.hasOwnProperty("max"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof GaugeOptions")
        }
    }
    static isGaugeShadowOptions(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof GaugeShadowOptions")
    }
    static isGeometryInfo(value: object|string|number|undefined|null|boolean, duplicated_borderWidth: boolean, duplicated_margin: boolean, duplicated_padding: boolean): boolean {
        if ((!duplicated_borderWidth) && (value?.hasOwnProperty("borderWidth"))) {
            return true
        }
        else if ((!duplicated_margin) && (value?.hasOwnProperty("margin"))) {
            return true
        }
        else if ((!duplicated_padding) && (value?.hasOwnProperty("padding"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof GeometryInfo")
        }
    }
    static isGeometryTransitionOptions(value: object|string|number|undefined|null|boolean, duplicated_follow: boolean, duplicated_hierarchyStrategy: boolean): boolean {
        if ((!duplicated_follow) && (value?.hasOwnProperty("follow"))) {
            return true
        }
        else if ((!duplicated_hierarchyStrategy) && (value?.hasOwnProperty("hierarchyStrategy"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof GeometryTransitionOptions")
        }
    }
    static isGestureControlGestureType(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (GestureControl.GestureType.TAP_GESTURE)) {
            return true
        }
        else if ((value) === (GestureControl.GestureType.LONG_PRESS_GESTURE)) {
            return true
        }
        else if ((value) === (GestureControl.GestureType.PAN_GESTURE)) {
            return true
        }
        else if ((value) === (GestureControl.GestureType.PINCH_GESTURE)) {
            return true
        }
        else if ((value) === (GestureControl.GestureType.SWIPE_GESTURE)) {
            return true
        }
        else if ((value) === (GestureControl.GestureType.ROTATION_GESTURE)) {
            return true
        }
        else if ((value) === (GestureControl.GestureType.DRAG)) {
            return true
        }
        else if ((value) === (GestureControl.GestureType.CLICK)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof GestureControl.GestureType")
        }
    }
    static isGestureEvent(value: object|string|number|undefined|null|boolean, duplicated_repeat: boolean, duplicated_fingerList: boolean, duplicated_offsetX: boolean, duplicated_offsetY: boolean, duplicated_angle: boolean, duplicated_speed: boolean, duplicated_scale: boolean, duplicated_pinchCenterX: boolean, duplicated_pinchCenterY: boolean, duplicated_velocityX: boolean, duplicated_velocityY: boolean, duplicated_velocity: boolean): boolean {
        if ((!duplicated_repeat) && (value?.hasOwnProperty("repeat"))) {
            return true
        }
        else if ((!duplicated_fingerList) && (value?.hasOwnProperty("fingerList"))) {
            return true
        }
        else if ((!duplicated_offsetX) && (value?.hasOwnProperty("offsetX"))) {
            return true
        }
        else if ((!duplicated_offsetY) && (value?.hasOwnProperty("offsetY"))) {
            return true
        }
        else if ((!duplicated_angle) && (value?.hasOwnProperty("angle"))) {
            return true
        }
        else if ((!duplicated_speed) && (value?.hasOwnProperty("speed"))) {
            return true
        }
        else if ((!duplicated_scale) && (value?.hasOwnProperty("scale"))) {
            return true
        }
        else if ((!duplicated_pinchCenterX) && (value?.hasOwnProperty("pinchCenterX"))) {
            return true
        }
        else if ((!duplicated_pinchCenterY) && (value?.hasOwnProperty("pinchCenterY"))) {
            return true
        }
        else if ((!duplicated_velocityX) && (value?.hasOwnProperty("velocityX"))) {
            return true
        }
        else if ((!duplicated_velocityY) && (value?.hasOwnProperty("velocityY"))) {
            return true
        }
        else if ((!duplicated_velocity) && (value?.hasOwnProperty("velocity"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof GestureEvent")
        }
    }
    static isGestureGroupGestureHandlerOptions(value: object|string|number|undefined|null|boolean, duplicated_stub: boolean): boolean {
        if ((!duplicated_stub) && (value?.hasOwnProperty("stub"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof GestureGroupGestureHandlerOptions")
        }
    }
    static isGestureGroupInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof GestureGroupInterface")
    }
    static isGestureHandler(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof GestureHandler")
    }
    static isGestureInfo(value: object|string|number|undefined|null|boolean, duplicated_tag: boolean, duplicated_type: boolean, duplicated_isSystemGesture: boolean): boolean {
        if ((!duplicated_type) && (value?.hasOwnProperty("type"))) {
            return true
        }
        else if ((!duplicated_isSystemGesture) && (value?.hasOwnProperty("isSystemGesture"))) {
            return true
        }
        else if ((!duplicated_tag) && (value?.hasOwnProperty("tag"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof GestureInfo")
        }
    }
    static isGestureInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof GestureInterface")
    }
    static isGestureJudgeResult(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (GestureJudgeResult.CONTINUE)) {
            return true
        }
        else if ((value) === (GestureJudgeResult.REJECT)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof GestureJudgeResult")
        }
    }
    static isGestureMask(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (GestureMask.Normal)) {
            return true
        }
        else if ((value) === (GestureMask.IgnoreInternal)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof GestureMask")
        }
    }
    static isGestureMode(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (GestureMode.Sequence)) {
            return true
        }
        else if ((value) === (GestureMode.Parallel)) {
            return true
        }
        else if ((value) === (GestureMode.Exclusive)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof GestureMode")
        }
    }
    static isGestureModifier(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof GestureModifier")
    }
    static isGesturePriority(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (GesturePriority.NORMAL)) {
            return true
        }
        else if ((value) === (GesturePriority.PRIORITY)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof GesturePriority")
        }
    }
    static isGestureRecognizer(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof GestureRecognizer")
    }
    static isGestureRecognizerState(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (GestureRecognizerState.READY)) {
            return true
        }
        else if ((value) === (GestureRecognizerState.DETECTING)) {
            return true
        }
        else if ((value) === (GestureRecognizerState.PENDING)) {
            return true
        }
        else if ((value) === (GestureRecognizerState.BLOCKED)) {
            return true
        }
        else if ((value) === (GestureRecognizerState.SUCCESSFUL)) {
            return true
        }
        else if ((value) === (GestureRecognizerState.FAILED)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof GestureRecognizerState")
        }
    }
    static isGestureStyle(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof GestureStyle")
    }
    static isGestureStyleInterface(value: object|string|number|undefined|null|boolean, duplicated_onClick: boolean, duplicated_onLongPress: boolean): boolean {
        if ((!duplicated_onClick) && (value?.hasOwnProperty("onClick"))) {
            return true
        }
        else if ((!duplicated_onLongPress) && (value?.hasOwnProperty("onLongPress"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof GestureStyleInterface")
        }
    }
    static isGlobalScope_ohos_arkui_componentSnapshot(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof GlobalScope_ohos_arkui_componentSnapshot")
    }
    static isGlobalScope_ohos_arkui_performanceMonitor(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof GlobalScope_ohos_arkui_performanceMonitor")
    }
    static isGlobalScope_ohos_font(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof GlobalScope_ohos_font")
    }
    static isGlobalScope_ohos_measure_utils(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof GlobalScope_ohos_measure_utils")
    }
    static isGradientDirection(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (GradientDirection.Left)) {
            return true
        }
        else if ((value) === (GradientDirection.Top)) {
            return true
        }
        else if ((value) === (GradientDirection.Right)) {
            return true
        }
        else if ((value) === (GradientDirection.Bottom)) {
            return true
        }
        else if ((value) === (GradientDirection.LeftTop)) {
            return true
        }
        else if ((value) === (GradientDirection.LeftBottom)) {
            return true
        }
        else if ((value) === (GradientDirection.RightTop)) {
            return true
        }
        else if ((value) === (GradientDirection.RightBottom)) {
            return true
        }
        else if ((value) === (GradientDirection.None)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof GradientDirection")
        }
    }
    static isGridAttribute(value: object|string|number|undefined|null|boolean, duplicated_columnsTemplate: boolean, duplicated_rowsTemplate: boolean, duplicated_columnsGap: boolean, duplicated_rowsGap: boolean, duplicated_scrollBarWidth: boolean, duplicated_scrollBarColor: boolean, duplicated_scrollBar: boolean, duplicated_onScrollBarUpdate: boolean, duplicated_onScrollIndex: boolean, duplicated_cachedCount: boolean, duplicated_editMode: boolean, duplicated_multiSelectable: boolean, duplicated_maxCount: boolean, duplicated_minCount: boolean, duplicated_cellLength: boolean, duplicated_layoutDirection: boolean, duplicated_supportAnimation: boolean, duplicated_onItemDragStart: boolean, duplicated_onItemDragEnter: boolean, duplicated_onItemDragMove: boolean, duplicated_onItemDragLeave: boolean, duplicated_onItemDrop: boolean, duplicated_nestedScroll: boolean, duplicated_enableScrollInteraction: boolean, duplicated_friction: boolean, duplicated_alignItems: boolean, duplicated_onScroll: boolean, duplicated_onWillScroll: boolean, duplicated_onDidScroll: boolean, duplicated_onReachStart: boolean, duplicated_onReachEnd: boolean, duplicated_onScrollStart: boolean, duplicated_onScrollStop: boolean, duplicated_onScrollFrameBegin: boolean): boolean {
        if ((!duplicated_columnsTemplate) && (value?.hasOwnProperty("columnsTemplate"))) {
            return true
        }
        else if ((!duplicated_rowsTemplate) && (value?.hasOwnProperty("rowsTemplate"))) {
            return true
        }
        else if ((!duplicated_columnsGap) && (value?.hasOwnProperty("columnsGap"))) {
            return true
        }
        else if ((!duplicated_rowsGap) && (value?.hasOwnProperty("rowsGap"))) {
            return true
        }
        else if ((!duplicated_scrollBarWidth) && (value?.hasOwnProperty("scrollBarWidth"))) {
            return true
        }
        else if ((!duplicated_scrollBarColor) && (value?.hasOwnProperty("scrollBarColor"))) {
            return true
        }
        else if ((!duplicated_scrollBar) && (value?.hasOwnProperty("scrollBar"))) {
            return true
        }
        else if ((!duplicated_onScrollBarUpdate) && (value?.hasOwnProperty("onScrollBarUpdate"))) {
            return true
        }
        else if ((!duplicated_onScrollIndex) && (value?.hasOwnProperty("onScrollIndex"))) {
            return true
        }
        else if ((!duplicated_cachedCount) && (value?.hasOwnProperty("cachedCount"))) {
            return true
        }
        else if ((!duplicated_editMode) && (value?.hasOwnProperty("editMode"))) {
            return true
        }
        else if ((!duplicated_multiSelectable) && (value?.hasOwnProperty("multiSelectable"))) {
            return true
        }
        else if ((!duplicated_maxCount) && (value?.hasOwnProperty("maxCount"))) {
            return true
        }
        else if ((!duplicated_minCount) && (value?.hasOwnProperty("minCount"))) {
            return true
        }
        else if ((!duplicated_cellLength) && (value?.hasOwnProperty("cellLength"))) {
            return true
        }
        else if ((!duplicated_layoutDirection) && (value?.hasOwnProperty("layoutDirection"))) {
            return true
        }
        else if ((!duplicated_supportAnimation) && (value?.hasOwnProperty("supportAnimation"))) {
            return true
        }
        else if ((!duplicated_onItemDragStart) && (value?.hasOwnProperty("onItemDragStart"))) {
            return true
        }
        else if ((!duplicated_onItemDragEnter) && (value?.hasOwnProperty("onItemDragEnter"))) {
            return true
        }
        else if ((!duplicated_onItemDragMove) && (value?.hasOwnProperty("onItemDragMove"))) {
            return true
        }
        else if ((!duplicated_onItemDragLeave) && (value?.hasOwnProperty("onItemDragLeave"))) {
            return true
        }
        else if ((!duplicated_onItemDrop) && (value?.hasOwnProperty("onItemDrop"))) {
            return true
        }
        else if ((!duplicated_nestedScroll) && (value?.hasOwnProperty("nestedScroll"))) {
            return true
        }
        else if ((!duplicated_enableScrollInteraction) && (value?.hasOwnProperty("enableScrollInteraction"))) {
            return true
        }
        else if ((!duplicated_friction) && (value?.hasOwnProperty("friction"))) {
            return true
        }
        else if ((!duplicated_alignItems) && (value?.hasOwnProperty("alignItems"))) {
            return true
        }
        else if ((!duplicated_onScroll) && (value?.hasOwnProperty("onScroll"))) {
            return true
        }
        else if ((!duplicated_onWillScroll) && (value?.hasOwnProperty("onWillScroll"))) {
            return true
        }
        else if ((!duplicated_onDidScroll) && (value?.hasOwnProperty("onDidScroll"))) {
            return true
        }
        else if ((!duplicated_onReachStart) && (value?.hasOwnProperty("onReachStart"))) {
            return true
        }
        else if ((!duplicated_onReachEnd) && (value?.hasOwnProperty("onReachEnd"))) {
            return true
        }
        else if ((!duplicated_onScrollStart) && (value?.hasOwnProperty("onScrollStart"))) {
            return true
        }
        else if ((!duplicated_onScrollStop) && (value?.hasOwnProperty("onScrollStop"))) {
            return true
        }
        else if ((!duplicated_onScrollFrameBegin) && (value?.hasOwnProperty("onScrollFrameBegin"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof GridAttribute")
        }
    }
    static isGridColAttribute(value: object|string|number|undefined|null|boolean, duplicated_span: boolean, duplicated_gridColOffset: boolean, duplicated_order: boolean): boolean {
        if ((!duplicated_span) && (value?.hasOwnProperty("span"))) {
            return true
        }
        else if ((!duplicated_gridColOffset) && (value?.hasOwnProperty("gridColOffset"))) {
            return true
        }
        else if ((!duplicated_order) && (value?.hasOwnProperty("order"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof GridColAttribute")
        }
    }
    static isGridColColumnOption(value: object|string|number|undefined|null|boolean, duplicated_xs: boolean, duplicated_sm: boolean, duplicated_md: boolean, duplicated_lg: boolean, duplicated_xl: boolean, duplicated_xxl: boolean): boolean {
        if ((!duplicated_xs) && (value?.hasOwnProperty("xs"))) {
            return true
        }
        else if ((!duplicated_sm) && (value?.hasOwnProperty("sm"))) {
            return true
        }
        else if ((!duplicated_md) && (value?.hasOwnProperty("md"))) {
            return true
        }
        else if ((!duplicated_lg) && (value?.hasOwnProperty("lg"))) {
            return true
        }
        else if ((!duplicated_xl) && (value?.hasOwnProperty("xl"))) {
            return true
        }
        else if ((!duplicated_xxl) && (value?.hasOwnProperty("xxl"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof GridColColumnOption")
        }
    }
    static isGridColInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof GridColInterface")
    }
    static isGridColOptions(value: object|string|number|undefined|null|boolean, duplicated_span: boolean, duplicated_offset: boolean, duplicated_order: boolean): boolean {
        if ((!duplicated_span) && (value?.hasOwnProperty("span"))) {
            return true
        }
        else if ((!duplicated_offset) && (value?.hasOwnProperty("offset"))) {
            return true
        }
        else if ((!duplicated_order) && (value?.hasOwnProperty("order"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof GridColOptions")
        }
    }
    static isGridContainerAttribute(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof GridContainerAttribute")
    }
    static isGridContainerInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof GridContainerInterface")
    }
    static isGridContainerOptions(value: object|string|number|undefined|null|boolean, duplicated_columns: boolean, duplicated_sizeType: boolean, duplicated_gutter: boolean, duplicated_margin: boolean): boolean {
        if ((!duplicated_columns) && (value?.hasOwnProperty("columns"))) {
            return true
        }
        else if ((!duplicated_sizeType) && (value?.hasOwnProperty("sizeType"))) {
            return true
        }
        else if ((!duplicated_gutter) && (value?.hasOwnProperty("gutter"))) {
            return true
        }
        else if ((!duplicated_margin) && (value?.hasOwnProperty("margin"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof GridContainerOptions")
        }
    }
    static isGridDirection(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (GridDirection.Row)) {
            return true
        }
        else if ((value) === (GridDirection.Column)) {
            return true
        }
        else if ((value) === (GridDirection.RowReverse)) {
            return true
        }
        else if ((value) === (GridDirection.ColumnReverse)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof GridDirection")
        }
    }
    static isGridInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof GridInterface")
    }
    static isGridItemAlignment(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (GridItemAlignment.DEFAULT)) {
            return true
        }
        else if ((value) === (GridItemAlignment.STRETCH)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof GridItemAlignment")
        }
    }
    static isGridItemAttribute(value: object|string|number|undefined|null|boolean, duplicated_rowStart: boolean, duplicated_rowEnd: boolean, duplicated_columnStart: boolean, duplicated_columnEnd: boolean, duplicated_forceRebuild: boolean, duplicated_selectable: boolean, duplicated_selected: boolean, duplicated_onSelect: boolean): boolean {
        if ((!duplicated_rowStart) && (value?.hasOwnProperty("rowStart"))) {
            return true
        }
        else if ((!duplicated_rowEnd) && (value?.hasOwnProperty("rowEnd"))) {
            return true
        }
        else if ((!duplicated_columnStart) && (value?.hasOwnProperty("columnStart"))) {
            return true
        }
        else if ((!duplicated_columnEnd) && (value?.hasOwnProperty("columnEnd"))) {
            return true
        }
        else if ((!duplicated_forceRebuild) && (value?.hasOwnProperty("forceRebuild"))) {
            return true
        }
        else if ((!duplicated_selectable) && (value?.hasOwnProperty("selectable"))) {
            return true
        }
        else if ((!duplicated_selected) && (value?.hasOwnProperty("selected"))) {
            return true
        }
        else if ((!duplicated_onSelect) && (value?.hasOwnProperty("onSelect"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof GridItemAttribute")
        }
    }
    static isGridItemInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof GridItemInterface")
    }
    static isGridItemOptions(value: object|string|number|undefined|null|boolean, duplicated_style: boolean): boolean {
        if ((!duplicated_style) && (value?.hasOwnProperty("style"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof GridItemOptions")
        }
    }
    static isGridItemStyle(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (GridItemStyle.NONE)) {
            return true
        }
        else if ((value) === (GridItemStyle.PLAIN)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof GridItemStyle")
        }
    }
    static isGridLayoutOptions(value: object|string|number|undefined|null|boolean, duplicated_regularSize: boolean, duplicated_irregularIndexes: boolean, duplicated_onGetIrregularSizeByIndex: boolean, duplicated_onGetRectByIndex: boolean): boolean {
        if ((!duplicated_regularSize) && (value?.hasOwnProperty("regularSize"))) {
            return true
        }
        else if ((!duplicated_irregularIndexes) && (value?.hasOwnProperty("irregularIndexes"))) {
            return true
        }
        else if ((!duplicated_onGetIrregularSizeByIndex) && (value?.hasOwnProperty("onGetIrregularSizeByIndex"))) {
            return true
        }
        else if ((!duplicated_onGetRectByIndex) && (value?.hasOwnProperty("onGetRectByIndex"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof GridLayoutOptions")
        }
    }
    static isGridRowAttribute(value: object|string|number|undefined|null|boolean, duplicated_onBreakpointChange: boolean, duplicated_alignItems: boolean): boolean {
        if ((!duplicated_onBreakpointChange) && (value?.hasOwnProperty("onBreakpointChange"))) {
            return true
        }
        else if ((!duplicated_alignItems) && (value?.hasOwnProperty("alignItems"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof GridRowAttribute")
        }
    }
    static isGridRowColumnOption(value: object|string|number|undefined|null|boolean, duplicated_xs: boolean, duplicated_sm: boolean, duplicated_md: boolean, duplicated_lg: boolean, duplicated_xl: boolean, duplicated_xxl: boolean): boolean {
        if ((!duplicated_xs) && (value?.hasOwnProperty("xs"))) {
            return true
        }
        else if ((!duplicated_sm) && (value?.hasOwnProperty("sm"))) {
            return true
        }
        else if ((!duplicated_md) && (value?.hasOwnProperty("md"))) {
            return true
        }
        else if ((!duplicated_lg) && (value?.hasOwnProperty("lg"))) {
            return true
        }
        else if ((!duplicated_xl) && (value?.hasOwnProperty("xl"))) {
            return true
        }
        else if ((!duplicated_xxl) && (value?.hasOwnProperty("xxl"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof GridRowColumnOption")
        }
    }
    static isGridRowDirection(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (GridRowDirection.Row)) {
            return true
        }
        else if ((value) === (GridRowDirection.RowReverse)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof GridRowDirection")
        }
    }
    static isGridRowInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof GridRowInterface")
    }
    static isGridRowOptions(value: object|string|number|undefined|null|boolean, duplicated_gutter: boolean, duplicated_columns: boolean, duplicated_breakpoints: boolean, duplicated_direction: boolean): boolean {
        if ((!duplicated_gutter) && (value?.hasOwnProperty("gutter"))) {
            return true
        }
        else if ((!duplicated_columns) && (value?.hasOwnProperty("columns"))) {
            return true
        }
        else if ((!duplicated_breakpoints) && (value?.hasOwnProperty("breakpoints"))) {
            return true
        }
        else if ((!duplicated_direction) && (value?.hasOwnProperty("direction"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof GridRowOptions")
        }
    }
    static isGridRowSizeOption(value: object|string|number|undefined|null|boolean, duplicated_xs: boolean, duplicated_sm: boolean, duplicated_md: boolean, duplicated_lg: boolean, duplicated_xl: boolean, duplicated_xxl: boolean): boolean {
        if ((!duplicated_xs) && (value?.hasOwnProperty("xs"))) {
            return true
        }
        else if ((!duplicated_sm) && (value?.hasOwnProperty("sm"))) {
            return true
        }
        else if ((!duplicated_md) && (value?.hasOwnProperty("md"))) {
            return true
        }
        else if ((!duplicated_lg) && (value?.hasOwnProperty("lg"))) {
            return true
        }
        else if ((!duplicated_xl) && (value?.hasOwnProperty("xl"))) {
            return true
        }
        else if ((!duplicated_xxl) && (value?.hasOwnProperty("xxl"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof GridRowSizeOption")
        }
    }
    static isGuideLinePosition(value: object|string|number|undefined|null|boolean, duplicated_start: boolean, duplicated_end: boolean): boolean {
        if ((!duplicated_start) && (value?.hasOwnProperty("start"))) {
            return true
        }
        else if ((!duplicated_end) && (value?.hasOwnProperty("end"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof GuideLinePosition")
        }
    }
    static isGuideLineStyle(value: object|string|number|undefined|null|boolean, duplicated_id: boolean, duplicated_direction: boolean, duplicated_position: boolean): boolean {
        if ((!duplicated_id) && (value?.hasOwnProperty("id"))) {
            return true
        }
        else if ((!duplicated_direction) && (value?.hasOwnProperty("direction"))) {
            return true
        }
        else if ((!duplicated_position) && (value?.hasOwnProperty("position"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof GuideLineStyle")
        }
    }
    static isGutterOption(value: object|string|number|undefined|null|boolean, duplicated_x: boolean, duplicated_y: boolean): boolean {
        if ((!duplicated_x) && (value?.hasOwnProperty("x"))) {
            return true
        }
        else if ((!duplicated_y) && (value?.hasOwnProperty("y"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof GutterOption")
        }
    }
    static isHeader(value: object|string|number|undefined|null|boolean, duplicated_headerKey: boolean, duplicated_headerValue: boolean): boolean {
        if ((!duplicated_headerKey) && (value?.hasOwnProperty("headerKey"))) {
            return true
        }
        else if ((!duplicated_headerValue) && (value?.hasOwnProperty("headerValue"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof Header")
        }
    }
    static isHeightBreakpoint(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (HeightBreakpoint.HEIGHT_SM)) {
            return true
        }
        else if ((value) === (HeightBreakpoint.HEIGHT_MD)) {
            return true
        }
        else if ((value) === (HeightBreakpoint.HEIGHT_LG)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof HeightBreakpoint")
        }
    }
    static isHierarchicalSymbolEffect(value: object|string|number|undefined|null|boolean, duplicated_fillStyle: boolean): boolean {
        if ((!duplicated_fillStyle) && (value?.hasOwnProperty("fillStyle"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof HierarchicalSymbolEffect")
        }
    }
    static isHistoricalPoint(value: object|string|number|undefined|null|boolean, duplicated_touchObject: boolean, duplicated_size: boolean, duplicated_force: boolean, duplicated_timestamp: boolean): boolean {
        if ((!duplicated_touchObject) && (value?.hasOwnProperty("touchObject"))) {
            return true
        }
        else if ((!duplicated_size) && (value?.hasOwnProperty("size"))) {
            return true
        }
        else if ((!duplicated_force) && (value?.hasOwnProperty("force"))) {
            return true
        }
        else if ((!duplicated_timestamp) && (value?.hasOwnProperty("timestamp"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof HistoricalPoint")
        }
    }
    static isHitTestMode(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (HitTestMode.Default)) {
            return true
        }
        else if ((value) === (HitTestMode.Block)) {
            return true
        }
        else if ((value) === (HitTestMode.Transparent)) {
            return true
        }
        else if ((value) === (HitTestMode.None)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof HitTestMode")
        }
    }
    static isHitTestType(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (HitTestType.EditText)) {
            return true
        }
        else if ((value) === (HitTestType.Email)) {
            return true
        }
        else if ((value) === (HitTestType.HttpAnchor)) {
            return true
        }
        else if ((value) === (HitTestType.HttpAnchorImg)) {
            return true
        }
        else if ((value) === (HitTestType.Img)) {
            return true
        }
        else if ((value) === (HitTestType.Map)) {
            return true
        }
        else if ((value) === (HitTestType.Phone)) {
            return true
        }
        else if ((value) === (HitTestType.Unknown)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof HitTestType")
        }
    }
    static isHorizontalAlign(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (HorizontalAlign.Start)) {
            return true
        }
        else if ((value) === (HorizontalAlign.Center)) {
            return true
        }
        else if ((value) === (HorizontalAlign.End)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof HorizontalAlign")
        }
    }
    static isHoverEffect(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (HoverEffect.Auto)) {
            return true
        }
        else if ((value) === (HoverEffect.Scale)) {
            return true
        }
        else if ((value) === (HoverEffect.Highlight)) {
            return true
        }
        else if ((value) === (HoverEffect.None)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof HoverEffect")
        }
    }
    static isHoverEvent(value: object|string|number|undefined|null|boolean, duplicated_stopPropagation: boolean): boolean {
        if ((!duplicated_stopPropagation) && (value?.hasOwnProperty("stopPropagation"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof HoverEvent")
        }
    }
    static isHoverEventParam(value: object|string|number|undefined|null|boolean, duplicated_foldStatus: boolean, duplicated_isHoverMode: boolean, duplicated_appRotation: boolean, duplicated_windowStatusType: boolean): boolean {
        if ((!duplicated_foldStatus) && (value?.hasOwnProperty("foldStatus"))) {
            return true
        }
        else if ((!duplicated_isHoverMode) && (value?.hasOwnProperty("isHoverMode"))) {
            return true
        }
        else if ((!duplicated_appRotation) && (value?.hasOwnProperty("appRotation"))) {
            return true
        }
        else if ((!duplicated_windowStatusType) && (value?.hasOwnProperty("windowStatusType"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof HoverEventParam")
        }
    }
    static isHoverModeAreaType(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (HoverModeAreaType.TOP_SCREEN)) {
            return true
        }
        else if ((value) === (HoverModeAreaType.BOTTOM_SCREEN)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof HoverModeAreaType")
        }
    }
    static isHttpAuthHandler(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof HttpAuthHandler")
    }
    static isHyperlinkAttribute(value: object|string|number|undefined|null|boolean, duplicated_color: boolean): boolean {
        if ((!duplicated_color) && (value?.hasOwnProperty("color"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof HyperlinkAttribute")
        }
    }
    static isHyperlinkInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof HyperlinkInterface")
    }
    static isIconOptions(value: object|string|number|undefined|null|boolean, duplicated_size: boolean, duplicated_color: boolean, duplicated_src: boolean): boolean {
        if ((!duplicated_size) && (value?.hasOwnProperty("size"))) {
            return true
        }
        else if ((!duplicated_color) && (value?.hasOwnProperty("color"))) {
            return true
        }
        else if ((!duplicated_src) && (value?.hasOwnProperty("src"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof IconOptions")
        }
    }
    static isICurve(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof ICurve")
    }
    static isIlluminatedType(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (IlluminatedType.NONE)) {
            return true
        }
        else if ((value) === (IlluminatedType.BORDER)) {
            return true
        }
        else if ((value) === (IlluminatedType.CONTENT)) {
            return true
        }
        else if ((value) === (IlluminatedType.BORDER_CONTENT)) {
            return true
        }
        else if ((value) === (IlluminatedType.BLOOM_BORDER)) {
            return true
        }
        else if ((value) === (IlluminatedType.BLOOM_BORDER_CONTENT)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof IlluminatedType")
        }
    }
    static isImageAIOptions(value: object|string|number|undefined|null|boolean, duplicated_types: boolean, duplicated_aiController: boolean): boolean {
        if ((!duplicated_types) && (value?.hasOwnProperty("types"))) {
            return true
        }
        else if ((!duplicated_aiController) && (value?.hasOwnProperty("aiController"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ImageAIOptions")
        }
    }
    static isImageAnalyzerConfig(value: object|string|number|undefined|null|boolean, duplicated_types: boolean): boolean {
        if ((!duplicated_types) && (value?.hasOwnProperty("types"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ImageAnalyzerConfig")
        }
    }
    static isImageAnalyzerController(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof ImageAnalyzerController")
    }
    static isImageAnalyzerType(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (ImageAnalyzerType.SUBJECT)) {
            return true
        }
        else if ((value) === (ImageAnalyzerType.TEXT)) {
            return true
        }
        else if ((value) === (ImageAnalyzerType.OBJECT_LOOKUP)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ImageAnalyzerType")
        }
    }
    static isImageAnimatorAttribute(value: object|string|number|undefined|null|boolean, duplicated_images: boolean, duplicated_state: boolean, duplicated_duration: boolean, duplicated_reverse: boolean, duplicated_fixedSize: boolean, duplicated_preDecode: boolean, duplicated_fillMode: boolean, duplicated_iterations: boolean, duplicated_onStart: boolean, duplicated_onPause: boolean, duplicated_onRepeat: boolean, duplicated_onCancel: boolean, duplicated_onFinish: boolean): boolean {
        if ((!duplicated_images) && (value?.hasOwnProperty("images"))) {
            return true
        }
        else if ((!duplicated_state) && (value?.hasOwnProperty("state"))) {
            return true
        }
        else if ((!duplicated_duration) && (value?.hasOwnProperty("duration"))) {
            return true
        }
        else if ((!duplicated_reverse) && (value?.hasOwnProperty("reverse"))) {
            return true
        }
        else if ((!duplicated_fixedSize) && (value?.hasOwnProperty("fixedSize"))) {
            return true
        }
        else if ((!duplicated_preDecode) && (value?.hasOwnProperty("preDecode"))) {
            return true
        }
        else if ((!duplicated_fillMode) && (value?.hasOwnProperty("fillMode"))) {
            return true
        }
        else if ((!duplicated_iterations) && (value?.hasOwnProperty("iterations"))) {
            return true
        }
        else if ((!duplicated_onStart) && (value?.hasOwnProperty("onStart"))) {
            return true
        }
        else if ((!duplicated_onPause) && (value?.hasOwnProperty("onPause"))) {
            return true
        }
        else if ((!duplicated_onRepeat) && (value?.hasOwnProperty("onRepeat"))) {
            return true
        }
        else if ((!duplicated_onCancel) && (value?.hasOwnProperty("onCancel"))) {
            return true
        }
        else if ((!duplicated_onFinish) && (value?.hasOwnProperty("onFinish"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ImageAnimatorAttribute")
        }
    }
    static isImageAnimatorInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof ImageAnimatorInterface")
    }
    static isImageAttachment(value: object|string|number|undefined|null|boolean, duplicated_value: boolean, duplicated_size: boolean, duplicated_verticalAlign: boolean, duplicated_objectFit: boolean, duplicated_layoutStyle: boolean): boolean {
        if ((!duplicated_value) && (value?.hasOwnProperty("value"))) {
            return true
        }
        else if ((!duplicated_size) && (value?.hasOwnProperty("size"))) {
            return true
        }
        else if ((!duplicated_verticalAlign) && (value?.hasOwnProperty("verticalAlign"))) {
            return true
        }
        else if ((!duplicated_objectFit) && (value?.hasOwnProperty("objectFit"))) {
            return true
        }
        else if ((!duplicated_layoutStyle) && (value?.hasOwnProperty("layoutStyle"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ImageAttachment")
        }
    }
    static isImageAttachmentInterface(value: object|string|number|undefined|null|boolean, duplicated_value: boolean, duplicated_size: boolean, duplicated_verticalAlign: boolean, duplicated_objectFit: boolean, duplicated_layoutStyle: boolean): boolean {
        if ((!duplicated_value) && (value?.hasOwnProperty("value"))) {
            return true
        }
        else if ((!duplicated_size) && (value?.hasOwnProperty("size"))) {
            return true
        }
        else if ((!duplicated_verticalAlign) && (value?.hasOwnProperty("verticalAlign"))) {
            return true
        }
        else if ((!duplicated_objectFit) && (value?.hasOwnProperty("objectFit"))) {
            return true
        }
        else if ((!duplicated_layoutStyle) && (value?.hasOwnProperty("layoutStyle"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ImageAttachmentInterface")
        }
    }
    static isImageAttachmentLayoutStyle(value: object|string|number|undefined|null|boolean, duplicated_margin: boolean, duplicated_padding: boolean, duplicated_borderRadius: boolean): boolean {
        if ((!duplicated_margin) && (value?.hasOwnProperty("margin"))) {
            return true
        }
        else if ((!duplicated_padding) && (value?.hasOwnProperty("padding"))) {
            return true
        }
        else if ((!duplicated_borderRadius) && (value?.hasOwnProperty("borderRadius"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ImageAttachmentLayoutStyle")
        }
    }
    static isImageAttribute(value: object|string|number|undefined|null|boolean, duplicated_alt: boolean, duplicated_matchTextDirection: boolean, duplicated_fitOriginalSize: boolean, duplicated_fillColor: boolean, duplicated_objectFit: boolean, duplicated_objectRepeat: boolean, duplicated_autoResize: boolean, duplicated_renderMode: boolean, duplicated_dynamicRangeMode: boolean, duplicated_interpolation: boolean, duplicated_sourceSize: boolean, duplicated_syncLoad: boolean, duplicated_colorFilter: boolean, duplicated_copyOption: boolean, duplicated_draggable: boolean, duplicated_pointLight: boolean, duplicated_edgeAntialiasing: boolean, duplicated_onComplete: boolean, duplicated_onError: boolean, duplicated_onFinish: boolean, duplicated_enableAnalyzer: boolean, duplicated_analyzerConfig: boolean, duplicated_resizable: boolean, duplicated_privacySensitive: boolean, duplicated_enhancedImageQuality: boolean): boolean {
        if ((!duplicated_alt) && (value?.hasOwnProperty("alt"))) {
            return true
        }
        else if ((!duplicated_matchTextDirection) && (value?.hasOwnProperty("matchTextDirection"))) {
            return true
        }
        else if ((!duplicated_fitOriginalSize) && (value?.hasOwnProperty("fitOriginalSize"))) {
            return true
        }
        else if ((!duplicated_fillColor) && (value?.hasOwnProperty("fillColor"))) {
            return true
        }
        else if ((!duplicated_objectFit) && (value?.hasOwnProperty("objectFit"))) {
            return true
        }
        else if ((!duplicated_objectRepeat) && (value?.hasOwnProperty("objectRepeat"))) {
            return true
        }
        else if ((!duplicated_autoResize) && (value?.hasOwnProperty("autoResize"))) {
            return true
        }
        else if ((!duplicated_renderMode) && (value?.hasOwnProperty("renderMode"))) {
            return true
        }
        else if ((!duplicated_dynamicRangeMode) && (value?.hasOwnProperty("dynamicRangeMode"))) {
            return true
        }
        else if ((!duplicated_interpolation) && (value?.hasOwnProperty("interpolation"))) {
            return true
        }
        else if ((!duplicated_sourceSize) && (value?.hasOwnProperty("sourceSize"))) {
            return true
        }
        else if ((!duplicated_syncLoad) && (value?.hasOwnProperty("syncLoad"))) {
            return true
        }
        else if ((!duplicated_colorFilter) && (value?.hasOwnProperty("colorFilter"))) {
            return true
        }
        else if ((!duplicated_copyOption) && (value?.hasOwnProperty("copyOption"))) {
            return true
        }
        else if ((!duplicated_draggable) && (value?.hasOwnProperty("draggable"))) {
            return true
        }
        else if ((!duplicated_pointLight) && (value?.hasOwnProperty("pointLight"))) {
            return true
        }
        else if ((!duplicated_edgeAntialiasing) && (value?.hasOwnProperty("edgeAntialiasing"))) {
            return true
        }
        else if ((!duplicated_onComplete) && (value?.hasOwnProperty("onComplete"))) {
            return true
        }
        else if ((!duplicated_onError) && (value?.hasOwnProperty("onError"))) {
            return true
        }
        else if ((!duplicated_onFinish) && (value?.hasOwnProperty("onFinish"))) {
            return true
        }
        else if ((!duplicated_enableAnalyzer) && (value?.hasOwnProperty("enableAnalyzer"))) {
            return true
        }
        else if ((!duplicated_analyzerConfig) && (value?.hasOwnProperty("analyzerConfig"))) {
            return true
        }
        else if ((!duplicated_resizable) && (value?.hasOwnProperty("resizable"))) {
            return true
        }
        else if ((!duplicated_privacySensitive) && (value?.hasOwnProperty("privacySensitive"))) {
            return true
        }
        else if ((!duplicated_enhancedImageQuality) && (value?.hasOwnProperty("enhancedImageQuality"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ImageAttribute")
        }
    }
    static isImageBitmap(value: object|string|number|undefined|null|boolean, duplicated_height: boolean, duplicated_width: boolean): boolean {
        if ((!duplicated_height) && (value?.hasOwnProperty("height"))) {
            return true
        }
        else if ((!duplicated_width) && (value?.hasOwnProperty("width"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ImageBitmap")
        }
    }
    static isImageContent(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (ImageContent.EMPTY)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ImageContent")
        }
    }
    static isImageData(value: object|string|number|undefined|null|boolean, duplicated_data: boolean, duplicated_height: boolean, duplicated_width: boolean): boolean {
        if ((!duplicated_data) && (value?.hasOwnProperty("data"))) {
            return true
        }
        else if ((!duplicated_height) && (value?.hasOwnProperty("height"))) {
            return true
        }
        else if ((!duplicated_width) && (value?.hasOwnProperty("width"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ImageData")
        }
    }
    static isImageError(value: object|string|number|undefined|null|boolean, duplicated_componentWidth: boolean, duplicated_componentHeight: boolean, duplicated_message: boolean): boolean {
        if ((!duplicated_componentWidth) && (value?.hasOwnProperty("componentWidth"))) {
            return true
        }
        else if ((!duplicated_componentHeight) && (value?.hasOwnProperty("componentHeight"))) {
            return true
        }
        else if ((!duplicated_message) && (value?.hasOwnProperty("message"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ImageError")
        }
    }
    static isImageFit(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (ImageFit.Contain)) {
            return true
        }
        else if ((value) === (ImageFit.Cover)) {
            return true
        }
        else if ((value) === (ImageFit.Auto)) {
            return true
        }
        else if ((value) === (ImageFit.Fill)) {
            return true
        }
        else if ((value) === (ImageFit.ScaleDown)) {
            return true
        }
        else if ((value) === (ImageFit.None)) {
            return true
        }
        else if ((value) === (ImageFit.TOP_START)) {
            return true
        }
        else if ((value) === (ImageFit.TOP)) {
            return true
        }
        else if ((value) === (ImageFit.TOP_END)) {
            return true
        }
        else if ((value) === (ImageFit.START)) {
            return true
        }
        else if ((value) === (ImageFit.CENTER)) {
            return true
        }
        else if ((value) === (ImageFit.END)) {
            return true
        }
        else if ((value) === (ImageFit.BOTTOM_START)) {
            return true
        }
        else if ((value) === (ImageFit.BOTTOM)) {
            return true
        }
        else if ((value) === (ImageFit.BOTTOM_END)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ImageFit")
        }
    }
    static isImageFrameInfo(value: object|string|number|undefined|null|boolean, duplicated_src: boolean, duplicated_width: boolean, duplicated_height: boolean, duplicated_top: boolean, duplicated_left: boolean, duplicated_duration: boolean): boolean {
        if ((!duplicated_src) && (value?.hasOwnProperty("src"))) {
            return true
        }
        else if ((!duplicated_width) && (value?.hasOwnProperty("width"))) {
            return true
        }
        else if ((!duplicated_height) && (value?.hasOwnProperty("height"))) {
            return true
        }
        else if ((!duplicated_top) && (value?.hasOwnProperty("top"))) {
            return true
        }
        else if ((!duplicated_left) && (value?.hasOwnProperty("left"))) {
            return true
        }
        else if ((!duplicated_duration) && (value?.hasOwnProperty("duration"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ImageFrameInfo")
        }
    }
    static isImageInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof ImageInterface")
    }
    static isImageInterpolation(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (ImageInterpolation.None)) {
            return true
        }
        else if ((value) === (ImageInterpolation.Low)) {
            return true
        }
        else if ((value) === (ImageInterpolation.Medium)) {
            return true
        }
        else if ((value) === (ImageInterpolation.High)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ImageInterpolation")
        }
    }
    static isImageLoadResult(value: object|string|number|undefined|null|boolean, duplicated_width: boolean, duplicated_height: boolean, duplicated_componentWidth: boolean, duplicated_componentHeight: boolean, duplicated_loadingStatus: boolean, duplicated_contentWidth: boolean, duplicated_contentHeight: boolean, duplicated_contentOffsetX: boolean, duplicated_contentOffsetY: boolean): boolean {
        if ((!duplicated_width) && (value?.hasOwnProperty("width"))) {
            return true
        }
        else if ((!duplicated_height) && (value?.hasOwnProperty("height"))) {
            return true
        }
        else if ((!duplicated_componentWidth) && (value?.hasOwnProperty("componentWidth"))) {
            return true
        }
        else if ((!duplicated_componentHeight) && (value?.hasOwnProperty("componentHeight"))) {
            return true
        }
        else if ((!duplicated_loadingStatus) && (value?.hasOwnProperty("loadingStatus"))) {
            return true
        }
        else if ((!duplicated_contentWidth) && (value?.hasOwnProperty("contentWidth"))) {
            return true
        }
        else if ((!duplicated_contentHeight) && (value?.hasOwnProperty("contentHeight"))) {
            return true
        }
        else if ((!duplicated_contentOffsetX) && (value?.hasOwnProperty("contentOffsetX"))) {
            return true
        }
        else if ((!duplicated_contentOffsetY) && (value?.hasOwnProperty("contentOffsetY"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ImageLoadResult")
        }
    }
    static isImageModifier(value: object|string|number|undefined|null|boolean, duplicated__ImageModifierStub: boolean): boolean {
        if ((!duplicated__ImageModifierStub) && (value?.hasOwnProperty("_ImageModifierStub"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ImageModifier")
        }
    }
    static isImageParticleParameters(value: object|string|number|undefined|null|boolean, duplicated_src: boolean, duplicated_size: boolean, duplicated_objectFit: boolean): boolean {
        if ((!duplicated_src) && (value?.hasOwnProperty("src"))) {
            return true
        }
        else if ((!duplicated_size) && (value?.hasOwnProperty("size"))) {
            return true
        }
        else if ((!duplicated_objectFit) && (value?.hasOwnProperty("objectFit"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ImageParticleParameters")
        }
    }
    static isImageRenderMode(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (ImageRenderMode.Original)) {
            return true
        }
        else if ((value) === (ImageRenderMode.Template)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ImageRenderMode")
        }
    }
    static isImageRepeat(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (ImageRepeat.NoRepeat)) {
            return true
        }
        else if ((value) === (ImageRepeat.X)) {
            return true
        }
        else if ((value) === (ImageRepeat.Y)) {
            return true
        }
        else if ((value) === (ImageRepeat.XY)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ImageRepeat")
        }
    }
    static isImageSize(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (ImageSize.Auto)) {
            return true
        }
        else if ((value) === (ImageSize.Cover)) {
            return true
        }
        else if ((value) === (ImageSize.Contain)) {
            return true
        }
        else if ((value) === (ImageSize.FILL)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ImageSize")
        }
    }
    static isImageSourceSize(value: object|string|number|undefined|null|boolean, duplicated_width: boolean, duplicated_height: boolean): boolean {
        if ((!duplicated_width) && (value?.hasOwnProperty("width"))) {
            return true
        }
        else if ((!duplicated_height) && (value?.hasOwnProperty("height"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ImageSourceSize")
        }
    }
    static isImageSpanAlignment(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (ImageSpanAlignment.BASELINE)) {
            return true
        }
        else if ((value) === (ImageSpanAlignment.BOTTOM)) {
            return true
        }
        else if ((value) === (ImageSpanAlignment.CENTER)) {
            return true
        }
        else if ((value) === (ImageSpanAlignment.TOP)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ImageSpanAlignment")
        }
    }
    static isImageSpanAttribute(value: object|string|number|undefined|null|boolean, duplicated_verticalAlign: boolean, duplicated_colorFilter: boolean, duplicated_objectFit: boolean, duplicated_onComplete: boolean, duplicated_onError: boolean, duplicated_alt: boolean): boolean {
        if ((!duplicated_verticalAlign) && (value?.hasOwnProperty("verticalAlign"))) {
            return true
        }
        else if ((!duplicated_colorFilter) && (value?.hasOwnProperty("colorFilter"))) {
            return true
        }
        else if ((!duplicated_objectFit) && (value?.hasOwnProperty("objectFit"))) {
            return true
        }
        else if ((!duplicated_onComplete) && (value?.hasOwnProperty("onComplete"))) {
            return true
        }
        else if ((!duplicated_onError) && (value?.hasOwnProperty("onError"))) {
            return true
        }
        else if ((!duplicated_alt) && (value?.hasOwnProperty("alt"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ImageSpanAttribute")
        }
    }
    static isImageSpanInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof ImageSpanInterface")
    }
    static isIndexerAlign(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (IndexerAlign.Left)) {
            return true
        }
        else if ((value) === (IndexerAlign.Right)) {
            return true
        }
        else if ((value) === (IndexerAlign.START)) {
            return true
        }
        else if ((value) === (IndexerAlign.END)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof IndexerAlign")
        }
    }
    static isIndicator(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof Indicator")
    }
    static isIndicatorComponentAttribute(value: object|string|number|undefined|null|boolean, duplicated_initialIndex: boolean, duplicated_count: boolean, duplicated_style: boolean, duplicated_loop: boolean, duplicated_vertical: boolean, duplicated_onChange: boolean): boolean {
        if ((!duplicated_initialIndex) && (value?.hasOwnProperty("initialIndex"))) {
            return true
        }
        else if ((!duplicated_count) && (value?.hasOwnProperty("count"))) {
            return true
        }
        else if ((!duplicated_style) && (value?.hasOwnProperty("style"))) {
            return true
        }
        else if ((!duplicated_loop) && (value?.hasOwnProperty("loop"))) {
            return true
        }
        else if ((!duplicated_vertical) && (value?.hasOwnProperty("vertical"))) {
            return true
        }
        else if ((!duplicated_onChange) && (value?.hasOwnProperty("onChange"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof IndicatorComponentAttribute")
        }
    }
    static isIndicatorComponentController(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof IndicatorComponentController")
    }
    static isIndicatorComponentInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof IndicatorComponentInterface")
    }
    static isIndicatorStyle(value: object|string|number|undefined|null|boolean, duplicated_left: boolean, duplicated_top: boolean, duplicated_right: boolean, duplicated_bottom: boolean, duplicated_size: boolean, duplicated_mask: boolean, duplicated_color: boolean, duplicated_selectedColor: boolean): boolean {
        if ((!duplicated_left) && (value?.hasOwnProperty("left"))) {
            return true
        }
        else if ((!duplicated_top) && (value?.hasOwnProperty("top"))) {
            return true
        }
        else if ((!duplicated_right) && (value?.hasOwnProperty("right"))) {
            return true
        }
        else if ((!duplicated_bottom) && (value?.hasOwnProperty("bottom"))) {
            return true
        }
        else if ((!duplicated_size) && (value?.hasOwnProperty("size"))) {
            return true
        }
        else if ((!duplicated_mask) && (value?.hasOwnProperty("mask"))) {
            return true
        }
        else if ((!duplicated_color) && (value?.hasOwnProperty("color"))) {
            return true
        }
        else if ((!duplicated_selectedColor) && (value?.hasOwnProperty("selectedColor"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof IndicatorStyle")
        }
    }
    static isInputCounterOptions(value: object|string|number|undefined|null|boolean, duplicated_thresholdPercentage: boolean, duplicated_highlightBorder: boolean): boolean {
        if ((!duplicated_thresholdPercentage) && (value?.hasOwnProperty("thresholdPercentage"))) {
            return true
        }
        else if ((!duplicated_highlightBorder) && (value?.hasOwnProperty("highlightBorder"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof InputCounterOptions")
        }
    }
    static isInputType(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (InputType.Normal)) {
            return true
        }
        else if ((value) === (InputType.Number)) {
            return true
        }
        else if ((value) === (InputType.PhoneNumber)) {
            return true
        }
        else if ((value) === (InputType.Email)) {
            return true
        }
        else if ((value) === (InputType.Password)) {
            return true
        }
        else if ((value) === (InputType.NUMBER_PASSWORD)) {
            return true
        }
        else if ((value) === (InputType.SCREEN_LOCK_PASSWORD)) {
            return true
        }
        else if ((value) === (InputType.USER_NAME)) {
            return true
        }
        else if ((value) === (InputType.NEW_PASSWORD)) {
            return true
        }
        else if ((value) === (InputType.NUMBER_DECIMAL)) {
            return true
        }
        else if ((value) === (InputType.URL)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof InputType")
        }
    }
    static isInsertValue(value: object|string|number|undefined|null|boolean, duplicated_insertOffset: boolean, duplicated_insertValue: boolean): boolean {
        if ((!duplicated_insertOffset) && (value?.hasOwnProperty("insertOffset"))) {
            return true
        }
        else if ((!duplicated_insertValue) && (value?.hasOwnProperty("insertValue"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof InsertValue")
        }
    }
    static isIntelligentTrackingPreventionDetails(value: object|string|number|undefined|null|boolean, duplicated_host: boolean, duplicated_trackerHost: boolean): boolean {
        if ((!duplicated_host) && (value?.hasOwnProperty("host"))) {
            return true
        }
        else if ((!duplicated_trackerHost) && (value?.hasOwnProperty("trackerHost"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof IntelligentTrackingPreventionDetails")
        }
    }
    static isIntentionCode(value: object|string|number|undefined|null|boolean, duplicated__IntentionCodeStub: boolean): boolean {
        if ((!duplicated__IntentionCodeStub) && (value?.hasOwnProperty("_IntentionCodeStub"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof IntentionCode")
        }
    }
    static isInvertOptions(value: object|string|number|undefined|null|boolean, duplicated_low: boolean, duplicated_high: boolean, duplicated_threshold: boolean, duplicated_thresholdRange: boolean): boolean {
        if ((!duplicated_low) && (value?.hasOwnProperty("low"))) {
            return true
        }
        else if ((!duplicated_high) && (value?.hasOwnProperty("high"))) {
            return true
        }
        else if ((!duplicated_threshold) && (value?.hasOwnProperty("threshold"))) {
            return true
        }
        else if ((!duplicated_thresholdRange) && (value?.hasOwnProperty("thresholdRange"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof InvertOptions")
        }
    }
    static isIPropertySubscriber(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof IPropertySubscriber")
    }
    static isISinglePropertyChangeSubscriber(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof ISinglePropertyChangeSubscriber")
    }
    static isIsolatedComponentAttribute(value: object|string|number|undefined|null|boolean, duplicated_onError: boolean): boolean {
        if ((!duplicated_onError) && (value?.hasOwnProperty("onError"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof IsolatedComponentAttribute")
        }
    }
    static isIsolatedOptions(value: object|string|number|undefined|null|boolean, duplicated_want: boolean, duplicated_worker: boolean): boolean {
        if ((!duplicated_want) && (value?.hasOwnProperty("want"))) {
            return true
        }
        else if ((!duplicated_worker) && (value?.hasOwnProperty("worker"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof IsolatedOptions")
        }
    }
    static isItemAlign(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (ItemAlign.Auto)) {
            return true
        }
        else if ((value) === (ItemAlign.Start)) {
            return true
        }
        else if ((value) === (ItemAlign.Center)) {
            return true
        }
        else if ((value) === (ItemAlign.End)) {
            return true
        }
        else if ((value) === (ItemAlign.Baseline)) {
            return true
        }
        else if ((value) === (ItemAlign.Stretch)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ItemAlign")
        }
    }
    static isItemDragInfo(value: object|string|number|undefined|null|boolean, duplicated_x: boolean, duplicated_y: boolean): boolean {
        if ((!duplicated_x) && (value?.hasOwnProperty("x"))) {
            return true
        }
        else if ((!duplicated_y) && (value?.hasOwnProperty("y"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ItemDragInfo")
        }
    }
    static isItemState(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (ItemState.Normal)) {
            return true
        }
        else if ((value) === (ItemState.Disabled)) {
            return true
        }
        else if ((value) === (ItemState.Waiting)) {
            return true
        }
        else if ((value) === (ItemState.Skip)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ItemState")
        }
    }
    static isJavaScriptProxy(value: object|string|number|undefined|null|boolean, duplicated_object_: boolean, duplicated_name: boolean, duplicated_methodList: boolean, duplicated_controller: boolean, duplicated_asyncMethodList: boolean, duplicated_permission: boolean): boolean {
        if ((!duplicated_object_) && (value?.hasOwnProperty("object_"))) {
            return true
        }
        else if ((!duplicated_name) && (value?.hasOwnProperty("name"))) {
            return true
        }
        else if ((!duplicated_methodList) && (value?.hasOwnProperty("methodList"))) {
            return true
        }
        else if ((!duplicated_controller) && (value?.hasOwnProperty("controller"))) {
            return true
        }
        else if ((!duplicated_asyncMethodList) && (value?.hasOwnProperty("asyncMethodList"))) {
            return true
        }
        else if ((!duplicated_permission) && (value?.hasOwnProperty("permission"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof JavaScriptProxy")
        }
    }
    static isJsGeolocation(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof JsGeolocation")
    }
    static isJsResult(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof JsResult")
    }
    static isKeyboardAvoidMode(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (KeyboardAvoidMode.DEFAULT)) {
            return true
        }
        else if ((value) === (KeyboardAvoidMode.NONE)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof KeyboardAvoidMode")
        }
    }
    static isKeyboardOptions(value: object|string|number|undefined|null|boolean, duplicated_supportAvoidance: boolean): boolean {
        if ((!duplicated_supportAvoidance) && (value?.hasOwnProperty("supportAvoidance"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof KeyboardOptions")
        }
    }
    static isKeyEvent(value: object|string|number|undefined|null|boolean, duplicated_type: boolean, duplicated_keyCode: boolean, duplicated_keyText: boolean, duplicated_keySource: boolean, duplicated_deviceId: boolean, duplicated_metaKey: boolean, duplicated_timestamp: boolean, duplicated_stopPropagation: boolean, duplicated_intentionCode: boolean, duplicated_unicode: boolean): boolean {
        if ((!duplicated_type) && (value?.hasOwnProperty("type"))) {
            return true
        }
        else if ((!duplicated_keyCode) && (value?.hasOwnProperty("keyCode"))) {
            return true
        }
        else if ((!duplicated_keyText) && (value?.hasOwnProperty("keyText"))) {
            return true
        }
        else if ((!duplicated_keySource) && (value?.hasOwnProperty("keySource"))) {
            return true
        }
        else if ((!duplicated_deviceId) && (value?.hasOwnProperty("deviceId"))) {
            return true
        }
        else if ((!duplicated_metaKey) && (value?.hasOwnProperty("metaKey"))) {
            return true
        }
        else if ((!duplicated_timestamp) && (value?.hasOwnProperty("timestamp"))) {
            return true
        }
        else if ((!duplicated_stopPropagation) && (value?.hasOwnProperty("stopPropagation"))) {
            return true
        }
        else if ((!duplicated_intentionCode) && (value?.hasOwnProperty("intentionCode"))) {
            return true
        }
        else if ((!duplicated_unicode) && (value?.hasOwnProperty("unicode"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof KeyEvent")
        }
    }
    static isKeyframeAnimateParam(value: object|string|number|undefined|null|boolean, duplicated_delay: boolean, duplicated_iterations: boolean, duplicated_onFinish: boolean): boolean {
        if ((!duplicated_delay) && (value?.hasOwnProperty("delay"))) {
            return true
        }
        else if ((!duplicated_iterations) && (value?.hasOwnProperty("iterations"))) {
            return true
        }
        else if ((!duplicated_onFinish) && (value?.hasOwnProperty("onFinish"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof KeyframeAnimateParam")
        }
    }
    static isKeyframeState(value: object|string|number|undefined|null|boolean, duplicated_duration: boolean, duplicated_curve: boolean, duplicated_event: boolean): boolean {
        if ((!duplicated_duration) && (value?.hasOwnProperty("duration"))) {
            return true
        }
        else if ((!duplicated_event) && (value?.hasOwnProperty("event"))) {
            return true
        }
        else if ((!duplicated_curve) && (value?.hasOwnProperty("curve"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof KeyframeState")
        }
    }
    static isKeySource(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (KeySource.Unknown)) {
            return true
        }
        else if ((value) === (KeySource.Keyboard)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof KeySource")
        }
    }
    static isKeyType(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (KeyType.Down)) {
            return true
        }
        else if ((value) === (KeyType.Up)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof KeyType")
        }
    }
    static isLabelStyle(value: object|string|number|undefined|null|boolean, duplicated_overflow: boolean, duplicated_maxLines: boolean, duplicated_minFontSize: boolean, duplicated_maxFontSize: boolean, duplicated_heightAdaptivePolicy: boolean, duplicated_font: boolean): boolean {
        if ((!duplicated_overflow) && (value?.hasOwnProperty("overflow"))) {
            return true
        }
        else if ((!duplicated_maxLines) && (value?.hasOwnProperty("maxLines"))) {
            return true
        }
        else if ((!duplicated_minFontSize) && (value?.hasOwnProperty("minFontSize"))) {
            return true
        }
        else if ((!duplicated_maxFontSize) && (value?.hasOwnProperty("maxFontSize"))) {
            return true
        }
        else if ((!duplicated_heightAdaptivePolicy) && (value?.hasOwnProperty("heightAdaptivePolicy"))) {
            return true
        }
        else if ((!duplicated_font) && (value?.hasOwnProperty("font"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof LabelStyle")
        }
    }
    static isLargestContentfulPaint(value: object|string|number|undefined|null|boolean, duplicated_navigationStartTime: boolean, duplicated_largestImagePaintTime: boolean, duplicated_largestTextPaintTime: boolean, duplicated_imageBPP: boolean, duplicated_largestImageLoadStartTime: boolean, duplicated_largestImageLoadEndTime: boolean): boolean {
        if ((!duplicated_navigationStartTime) && (value?.hasOwnProperty("navigationStartTime"))) {
            return true
        }
        else if ((!duplicated_largestImagePaintTime) && (value?.hasOwnProperty("largestImagePaintTime"))) {
            return true
        }
        else if ((!duplicated_largestTextPaintTime) && (value?.hasOwnProperty("largestTextPaintTime"))) {
            return true
        }
        else if ((!duplicated_imageBPP) && (value?.hasOwnProperty("imageBPP"))) {
            return true
        }
        else if ((!duplicated_largestImageLoadStartTime) && (value?.hasOwnProperty("largestImageLoadStartTime"))) {
            return true
        }
        else if ((!duplicated_largestImageLoadEndTime) && (value?.hasOwnProperty("largestImageLoadEndTime"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof LargestContentfulPaint")
        }
    }
    static isLaunchMode(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (LaunchMode.STANDARD)) {
            return true
        }
        else if ((value) === (LaunchMode.MOVE_TO_TOP_SINGLETON)) {
            return true
        }
        else if ((value) === (LaunchMode.POP_TO_SINGLETON)) {
            return true
        }
        else if ((value) === (LaunchMode.NEW_INSTANCE)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof LaunchMode")
        }
    }
    static isLayeredDrawableDescriptor(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof LayeredDrawableDescriptor")
    }
    static isLayoutable(value: object|string|number|undefined|null|boolean, duplicated_stub: boolean): boolean {
        if ((!duplicated_stub) && (value?.hasOwnProperty("stub"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof Layoutable")
        }
    }
    static isLayoutBorderInfo(value: object|string|number|undefined|null|boolean, duplicated_borderWidth: boolean, duplicated_margin: boolean, duplicated_padding: boolean): boolean {
        if ((!duplicated_borderWidth) && (value?.hasOwnProperty("borderWidth"))) {
            return true
        }
        else if ((!duplicated_margin) && (value?.hasOwnProperty("margin"))) {
            return true
        }
        else if ((!duplicated_padding) && (value?.hasOwnProperty("padding"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof LayoutBorderInfo")
        }
    }
    static isLayoutChild(value: object|string|number|undefined|null|boolean, duplicated_stub: boolean): boolean {
        if ((!duplicated_stub) && (value?.hasOwnProperty("stub"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof LayoutChild")
        }
    }
    static isLayoutDirection(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (LayoutDirection.LTR)) {
            return true
        }
        else if ((value) === (LayoutDirection.RTL)) {
            return true
        }
        else if ((value) === (LayoutDirection.Auto)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof LayoutDirection")
        }
    }
    static isLayoutInfo(value: object|string|number|undefined|null|boolean, duplicated_position: boolean, duplicated_constraint: boolean): boolean {
        if ((!duplicated_position) && (value?.hasOwnProperty("position"))) {
            return true
        }
        else if ((!duplicated_constraint) && (value?.hasOwnProperty("constraint"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof LayoutInfo")
        }
    }
    static isLayoutManager(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof LayoutManager")
    }
    static isLayoutMode(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (LayoutMode.AUTO)) {
            return true
        }
        else if ((value) === (LayoutMode.VERTICAL)) {
            return true
        }
        else if ((value) === (LayoutMode.HORIZONTAL)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof LayoutMode")
        }
    }
    static isLayoutSafeAreaEdge(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (LayoutSafeAreaEdge.TOP)) {
            return true
        }
        else if ((value) === (LayoutSafeAreaEdge.BOTTOM)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof LayoutSafeAreaEdge")
        }
    }
    static isLayoutSafeAreaType(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (LayoutSafeAreaType.SYSTEM)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof LayoutSafeAreaType")
        }
    }
    static isLayoutStyle(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (LayoutStyle.ALWAYS_CENTER)) {
            return true
        }
        else if ((value) === (LayoutStyle.ALWAYS_AVERAGE_SPLIT)) {
            return true
        }
        else if ((value) === (LayoutStyle.SPACE_BETWEEN_OR_CENTER)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof LayoutStyle")
        }
    }
    static isLazyForEachOps(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof LazyForEachOps")
    }
    static isLeadingMarginPlaceholder(value: object|string|number|undefined|null|boolean, duplicated_pixelMap: boolean, duplicated_size: boolean): boolean {
        if ((!duplicated_pixelMap) && (value?.hasOwnProperty("pixelMap"))) {
            return true
        }
        else if ((!duplicated_size) && (value?.hasOwnProperty("size"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof LeadingMarginPlaceholder")
        }
    }
    static isLengthConstrain(value: object|string|number|undefined|null|boolean, duplicated_minLength: boolean, duplicated_maxLength: boolean): boolean {
        if ((!duplicated_minLength) && (value?.hasOwnProperty("minLength"))) {
            return true
        }
        else if ((!duplicated_maxLength) && (value?.hasOwnProperty("maxLength"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof LengthConstrain")
        }
    }
    static isLengthMetrics(value: object|string|number|undefined|null|boolean, duplicated_unit: boolean, duplicated_value: boolean): boolean {
        if ((!duplicated_unit) && (value?.hasOwnProperty("unit"))) {
            return true
        }
        else if ((!duplicated_value) && (value?.hasOwnProperty("value"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof LengthMetrics")
        }
    }
    static isLengthMetricsUnit(value: object|string|number|undefined|null|boolean, duplicated__LengthMetricsUnitStub: boolean): boolean {
        if ((!duplicated__LengthMetricsUnitStub) && (value?.hasOwnProperty("_LengthMetricsUnitStub"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof LengthMetricsUnit")
        }
    }
    static isLengthUnit(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (LengthUnit.PX)) {
            return true
        }
        else if ((value) === (LengthUnit.VP)) {
            return true
        }
        else if ((value) === (LengthUnit.FP)) {
            return true
        }
        else if ((value) === (LengthUnit.PERCENT)) {
            return true
        }
        else if ((value) === (LengthUnit.LPX)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof LengthUnit")
        }
    }
    static isLetterSpacingStyle(value: object|string|number|undefined|null|boolean, duplicated_letterSpacing: boolean): boolean {
        if ((!duplicated_letterSpacing) && (value?.hasOwnProperty("letterSpacing"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof LetterSpacingStyle")
        }
    }
    static isLightSource(value: object|string|number|undefined|null|boolean, duplicated_positionX: boolean, duplicated_positionY: boolean, duplicated_positionZ: boolean, duplicated_intensity: boolean, duplicated_color: boolean): boolean {
        if ((!duplicated_positionX) && (value?.hasOwnProperty("positionX"))) {
            return true
        }
        else if ((!duplicated_positionY) && (value?.hasOwnProperty("positionY"))) {
            return true
        }
        else if ((!duplicated_positionZ) && (value?.hasOwnProperty("positionZ"))) {
            return true
        }
        else if ((!duplicated_intensity) && (value?.hasOwnProperty("intensity"))) {
            return true
        }
        else if ((!duplicated_color) && (value?.hasOwnProperty("color"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof LightSource")
        }
    }
    static isLinearGradient(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof LinearGradient")
    }
    static isLinearGradient_common(value: object|string|number|undefined|null|boolean, duplicated_angle: boolean, duplicated_direction: boolean, duplicated_colors: boolean, duplicated_repeating: boolean): boolean {
        if ((!duplicated_colors) && (value?.hasOwnProperty("colors"))) {
            return true
        }
        else if ((!duplicated_angle) && (value?.hasOwnProperty("angle"))) {
            return true
        }
        else if ((!duplicated_direction) && (value?.hasOwnProperty("direction"))) {
            return true
        }
        else if ((!duplicated_repeating) && (value?.hasOwnProperty("repeating"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof LinearGradient_common")
        }
    }
    static isLinearGradientBlurOptions(value: object|string|number|undefined|null|boolean, duplicated_fractionStops: boolean, duplicated_direction: boolean): boolean {
        if ((!duplicated_fractionStops) && (value?.hasOwnProperty("fractionStops"))) {
            return true
        }
        else if ((!duplicated_direction) && (value?.hasOwnProperty("direction"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof LinearGradientBlurOptions")
        }
    }
    static isLinearIndicatorAttribute(value: object|string|number|undefined|null|boolean, duplicated_indicatorStyle: boolean, duplicated_indicatorLoop: boolean, duplicated_onChange: boolean): boolean {
        if ((!duplicated_indicatorStyle) && (value?.hasOwnProperty("indicatorStyle"))) {
            return true
        }
        else if ((!duplicated_indicatorLoop) && (value?.hasOwnProperty("indicatorLoop"))) {
            return true
        }
        else if ((!duplicated_onChange) && (value?.hasOwnProperty("onChange"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof LinearIndicatorAttribute")
        }
    }
    static isLinearIndicatorController(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof LinearIndicatorController")
    }
    static isLinearIndicatorInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof LinearIndicatorInterface")
    }
    static isLinearIndicatorStartOptions(value: object|string|number|undefined|null|boolean, duplicated_interval: boolean, duplicated_duration: boolean): boolean {
        if ((!duplicated_interval) && (value?.hasOwnProperty("interval"))) {
            return true
        }
        else if ((!duplicated_duration) && (value?.hasOwnProperty("duration"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof LinearIndicatorStartOptions")
        }
    }
    static isLinearIndicatorStyle(value: object|string|number|undefined|null|boolean, duplicated_space: boolean, duplicated_strokeWidth: boolean, duplicated_strokeRadius: boolean, duplicated_trackBackgroundColor: boolean, duplicated_trackColor: boolean): boolean {
        if ((!duplicated_space) && (value?.hasOwnProperty("space"))) {
            return true
        }
        else if ((!duplicated_strokeWidth) && (value?.hasOwnProperty("strokeWidth"))) {
            return true
        }
        else if ((!duplicated_strokeRadius) && (value?.hasOwnProperty("strokeRadius"))) {
            return true
        }
        else if ((!duplicated_trackBackgroundColor) && (value?.hasOwnProperty("trackBackgroundColor"))) {
            return true
        }
        else if ((!duplicated_trackColor) && (value?.hasOwnProperty("trackColor"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof LinearIndicatorStyle")
        }
    }
    static isLinearStyleOptions(value: object|string|number|undefined|null|boolean, duplicated_strokeWidth: boolean, duplicated_strokeRadius: boolean): boolean {
        if ((!duplicated_strokeWidth) && (value?.hasOwnProperty("strokeWidth"))) {
            return true
        }
        else if ((!duplicated_strokeRadius) && (value?.hasOwnProperty("strokeRadius"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof LinearStyleOptions")
        }
    }
    static isLineAttribute(value: object|string|number|undefined|null|boolean, duplicated_startPoint: boolean, duplicated_endPoint: boolean): boolean {
        if ((!duplicated_startPoint) && (value?.hasOwnProperty("startPoint"))) {
            return true
        }
        else if ((!duplicated_endPoint) && (value?.hasOwnProperty("endPoint"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof LineAttribute")
        }
    }
    static isLineBreakStrategy(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (LineBreakStrategy.GREEDY)) {
            return true
        }
        else if ((value) === (LineBreakStrategy.HIGH_QUALITY)) {
            return true
        }
        else if ((value) === (LineBreakStrategy.BALANCED)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof LineBreakStrategy")
        }
    }
    static isLineCapStyle(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (LineCapStyle.Butt)) {
            return true
        }
        else if ((value) === (LineCapStyle.Round)) {
            return true
        }
        else if ((value) === (LineCapStyle.Square)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof LineCapStyle")
        }
    }
    static isLineHeightStyle(value: object|string|number|undefined|null|boolean, duplicated_lineHeight: boolean): boolean {
        if ((!duplicated_lineHeight) && (value?.hasOwnProperty("lineHeight"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof LineHeightStyle")
        }
    }
    static isLineInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof LineInterface")
    }
    static isLineJoinStyle(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (LineJoinStyle.Miter)) {
            return true
        }
        else if ((value) === (LineJoinStyle.Round)) {
            return true
        }
        else if ((value) === (LineJoinStyle.Bevel)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof LineJoinStyle")
        }
    }
    static isLineMetrics(value: object|string|number|undefined|null|boolean, duplicated__LineMetricsStub: boolean): boolean {
        if ((!duplicated__LineMetricsStub) && (value?.hasOwnProperty("_LineMetricsStub"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof LineMetrics")
        }
    }
    static isLineOptions(value: object|string|number|undefined|null|boolean, duplicated_width: boolean, duplicated_height: boolean): boolean {
        if ((!duplicated_width) && (value?.hasOwnProperty("width"))) {
            return true
        }
        else if ((!duplicated_height) && (value?.hasOwnProperty("height"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof LineOptions")
        }
    }
    static isListAttribute(value: object|string|number|undefined|null|boolean, duplicated_alignListItem: boolean, duplicated_listDirection: boolean, duplicated_scrollBar: boolean, duplicated_contentStartOffset: boolean, duplicated_contentEndOffset: boolean, duplicated_divider: boolean, duplicated_editMode: boolean, duplicated_multiSelectable: boolean, duplicated_cachedCount: boolean, duplicated_chainAnimation: boolean, duplicated_chainAnimationOptions: boolean, duplicated_sticky: boolean, duplicated_scrollSnapAlign: boolean, duplicated_nestedScroll: boolean, duplicated_enableScrollInteraction: boolean, duplicated_friction: boolean, duplicated_childrenMainSize: boolean, duplicated_maintainVisibleContentPosition: boolean, duplicated_onScroll: boolean, duplicated_onScrollIndex: boolean, duplicated_onScrollVisibleContentChange: boolean, duplicated_onWillScroll: boolean, duplicated_onDidScroll: boolean, duplicated_onReachStart: boolean, duplicated_onReachEnd: boolean, duplicated_onScrollStart: boolean, duplicated_onScrollStop: boolean, duplicated_onItemDelete: boolean, duplicated_onItemMove: boolean, duplicated_onItemDragStart: boolean, duplicated_onItemDragEnter: boolean, duplicated_onItemDragMove: boolean, duplicated_onItemDragLeave: boolean, duplicated_onItemDrop: boolean, duplicated_onScrollFrameBegin: boolean): boolean {
        if ((!duplicated_alignListItem) && (value?.hasOwnProperty("alignListItem"))) {
            return true
        }
        else if ((!duplicated_listDirection) && (value?.hasOwnProperty("listDirection"))) {
            return true
        }
        else if ((!duplicated_scrollBar) && (value?.hasOwnProperty("scrollBar"))) {
            return true
        }
        else if ((!duplicated_contentStartOffset) && (value?.hasOwnProperty("contentStartOffset"))) {
            return true
        }
        else if ((!duplicated_contentEndOffset) && (value?.hasOwnProperty("contentEndOffset"))) {
            return true
        }
        else if ((!duplicated_divider) && (value?.hasOwnProperty("divider"))) {
            return true
        }
        else if ((!duplicated_editMode) && (value?.hasOwnProperty("editMode"))) {
            return true
        }
        else if ((!duplicated_multiSelectable) && (value?.hasOwnProperty("multiSelectable"))) {
            return true
        }
        else if ((!duplicated_cachedCount) && (value?.hasOwnProperty("cachedCount"))) {
            return true
        }
        else if ((!duplicated_chainAnimation) && (value?.hasOwnProperty("chainAnimation"))) {
            return true
        }
        else if ((!duplicated_chainAnimationOptions) && (value?.hasOwnProperty("chainAnimationOptions"))) {
            return true
        }
        else if ((!duplicated_sticky) && (value?.hasOwnProperty("sticky"))) {
            return true
        }
        else if ((!duplicated_scrollSnapAlign) && (value?.hasOwnProperty("scrollSnapAlign"))) {
            return true
        }
        else if ((!duplicated_nestedScroll) && (value?.hasOwnProperty("nestedScroll"))) {
            return true
        }
        else if ((!duplicated_enableScrollInteraction) && (value?.hasOwnProperty("enableScrollInteraction"))) {
            return true
        }
        else if ((!duplicated_friction) && (value?.hasOwnProperty("friction"))) {
            return true
        }
        else if ((!duplicated_childrenMainSize) && (value?.hasOwnProperty("childrenMainSize"))) {
            return true
        }
        else if ((!duplicated_maintainVisibleContentPosition) && (value?.hasOwnProperty("maintainVisibleContentPosition"))) {
            return true
        }
        else if ((!duplicated_onScroll) && (value?.hasOwnProperty("onScroll"))) {
            return true
        }
        else if ((!duplicated_onScrollIndex) && (value?.hasOwnProperty("onScrollIndex"))) {
            return true
        }
        else if ((!duplicated_onScrollVisibleContentChange) && (value?.hasOwnProperty("onScrollVisibleContentChange"))) {
            return true
        }
        else if ((!duplicated_onWillScroll) && (value?.hasOwnProperty("onWillScroll"))) {
            return true
        }
        else if ((!duplicated_onDidScroll) && (value?.hasOwnProperty("onDidScroll"))) {
            return true
        }
        else if ((!duplicated_onReachStart) && (value?.hasOwnProperty("onReachStart"))) {
            return true
        }
        else if ((!duplicated_onReachEnd) && (value?.hasOwnProperty("onReachEnd"))) {
            return true
        }
        else if ((!duplicated_onScrollStart) && (value?.hasOwnProperty("onScrollStart"))) {
            return true
        }
        else if ((!duplicated_onScrollStop) && (value?.hasOwnProperty("onScrollStop"))) {
            return true
        }
        else if ((!duplicated_onItemDelete) && (value?.hasOwnProperty("onItemDelete"))) {
            return true
        }
        else if ((!duplicated_onItemMove) && (value?.hasOwnProperty("onItemMove"))) {
            return true
        }
        else if ((!duplicated_onItemDragStart) && (value?.hasOwnProperty("onItemDragStart"))) {
            return true
        }
        else if ((!duplicated_onItemDragEnter) && (value?.hasOwnProperty("onItemDragEnter"))) {
            return true
        }
        else if ((!duplicated_onItemDragMove) && (value?.hasOwnProperty("onItemDragMove"))) {
            return true
        }
        else if ((!duplicated_onItemDragLeave) && (value?.hasOwnProperty("onItemDragLeave"))) {
            return true
        }
        else if ((!duplicated_onItemDrop) && (value?.hasOwnProperty("onItemDrop"))) {
            return true
        }
        else if ((!duplicated_onScrollFrameBegin) && (value?.hasOwnProperty("onScrollFrameBegin"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ListAttribute")
        }
    }
    static isListDividerOptions(value: object|string|number|undefined|null|boolean, duplicated_strokeWidth: boolean, duplicated_color: boolean, duplicated_startMargin: boolean, duplicated_endMargin: boolean): boolean {
        if ((!duplicated_strokeWidth) && (value?.hasOwnProperty("strokeWidth"))) {
            return true
        }
        else if ((!duplicated_color) && (value?.hasOwnProperty("color"))) {
            return true
        }
        else if ((!duplicated_startMargin) && (value?.hasOwnProperty("startMargin"))) {
            return true
        }
        else if ((!duplicated_endMargin) && (value?.hasOwnProperty("endMargin"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ListDividerOptions")
        }
    }
    static isListInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof ListInterface")
    }
    static isListItemAlign(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (ListItemAlign.Start)) {
            return true
        }
        else if ((value) === (ListItemAlign.Center)) {
            return true
        }
        else if ((value) === (ListItemAlign.End)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ListItemAlign")
        }
    }
    static isListItemAttribute(value: object|string|number|undefined|null|boolean, duplicated_sticky: boolean, duplicated_editable: boolean, duplicated_selectable: boolean, duplicated_selected: boolean, duplicated_swipeAction: boolean, duplicated_onSelect: boolean): boolean {
        if ((!duplicated_sticky) && (value?.hasOwnProperty("sticky"))) {
            return true
        }
        else if ((!duplicated_editable) && (value?.hasOwnProperty("editable"))) {
            return true
        }
        else if ((!duplicated_selectable) && (value?.hasOwnProperty("selectable"))) {
            return true
        }
        else if ((!duplicated_selected) && (value?.hasOwnProperty("selected"))) {
            return true
        }
        else if ((!duplicated_swipeAction) && (value?.hasOwnProperty("swipeAction"))) {
            return true
        }
        else if ((!duplicated_onSelect) && (value?.hasOwnProperty("onSelect"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ListItemAttribute")
        }
    }
    static isListItemGroupArea(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (ListItemGroupArea.NONE)) {
            return true
        }
        else if ((value) === (ListItemGroupArea.IN_LIST_ITEM_AREA)) {
            return true
        }
        else if ((value) === (ListItemGroupArea.IN_HEADER_AREA)) {
            return true
        }
        else if ((value) === (ListItemGroupArea.IN_FOOTER_AREA)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ListItemGroupArea")
        }
    }
    static isListItemGroupAttribute(value: object|string|number|undefined|null|boolean, duplicated_divider: boolean, duplicated_childrenMainSize: boolean): boolean {
        if ((!duplicated_divider) && (value?.hasOwnProperty("divider"))) {
            return true
        }
        else if ((!duplicated_childrenMainSize) && (value?.hasOwnProperty("childrenMainSize"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ListItemGroupAttribute")
        }
    }
    static isListItemGroupInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof ListItemGroupInterface")
    }
    static isListItemGroupOptions(value: object|string|number|undefined|null|boolean, duplicated_header: boolean, duplicated_headerComponent: boolean, duplicated_footer: boolean, duplicated_footerComponent: boolean, duplicated_space: boolean, duplicated_style: boolean): boolean {
        if ((!duplicated_header) && (value?.hasOwnProperty("header"))) {
            return true
        }
        else if ((!duplicated_headerComponent) && (value?.hasOwnProperty("headerComponent"))) {
            return true
        }
        else if ((!duplicated_footer) && (value?.hasOwnProperty("footer"))) {
            return true
        }
        else if ((!duplicated_footerComponent) && (value?.hasOwnProperty("footerComponent"))) {
            return true
        }
        else if ((!duplicated_space) && (value?.hasOwnProperty("space"))) {
            return true
        }
        else if ((!duplicated_style) && (value?.hasOwnProperty("style"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ListItemGroupOptions")
        }
    }
    static isListItemGroupStyle(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (ListItemGroupStyle.NONE)) {
            return true
        }
        else if ((value) === (ListItemGroupStyle.CARD)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ListItemGroupStyle")
        }
    }
    static isListItemInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof ListItemInterface")
    }
    static isListItemOptions(value: object|string|number|undefined|null|boolean, duplicated_style: boolean): boolean {
        if ((!duplicated_style) && (value?.hasOwnProperty("style"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ListItemOptions")
        }
    }
    static isListItemStyle(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (ListItemStyle.NONE)) {
            return true
        }
        else if ((value) === (ListItemStyle.CARD)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ListItemStyle")
        }
    }
    static isListOptions(value: object|string|number|undefined|null|boolean, duplicated_initialIndex: boolean, duplicated_space: boolean, duplicated_scroller: boolean): boolean {
        if ((!duplicated_initialIndex) && (value?.hasOwnProperty("initialIndex"))) {
            return true
        }
        else if ((!duplicated_space) && (value?.hasOwnProperty("space"))) {
            return true
        }
        else if ((!duplicated_scroller) && (value?.hasOwnProperty("scroller"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ListOptions")
        }
    }
    static isListScroller(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof ListScroller")
    }
    static isLiteral_Alignment_align(value: object|string|number|undefined|null|boolean, duplicated_align: boolean): boolean {
        if ((!duplicated_align) && (value?.hasOwnProperty("align"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof Literal_Alignment_align")
        }
    }
    static isLiteral_Boolean_isVisible(value: object|string|number|undefined|null|boolean, duplicated_isVisible: boolean): boolean {
        if ((!duplicated_isVisible) && (value?.hasOwnProperty("isVisible"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof Literal_Boolean_isVisible")
        }
    }
    static isLiteral_Boolean_next_Axis_direction(value: object|string|number|undefined|null|boolean, duplicated_next: boolean, duplicated_direction: boolean): boolean {
        if ((!duplicated_next) && (value?.hasOwnProperty("next"))) {
            return true
        }
        else if ((!duplicated_direction) && (value?.hasOwnProperty("direction"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof Literal_Boolean_next_Axis_direction")
        }
    }
    static isLiteral_Empty(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof Literal_Empty")
    }
    static isLiteral_Function_callback__Object_fileSelector(value: object|string|number|undefined|null|boolean, duplicated_callback_: boolean, duplicated_fileSelector: boolean): boolean {
        if ((!duplicated_callback_) && (value?.hasOwnProperty("callback_"))) {
            return true
        }
        else if ((!duplicated_fileSelector) && (value?.hasOwnProperty("fileSelector"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof Literal_Function_callback__Object_fileSelector")
        }
    }
    static isLiteral_Function_handler_Object_error(value: object|string|number|undefined|null|boolean, duplicated_handler: boolean, duplicated_error: boolean): boolean {
        if ((!duplicated_handler) && (value?.hasOwnProperty("handler"))) {
            return true
        }
        else if ((!duplicated_error) && (value?.hasOwnProperty("error"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof Literal_Function_handler_Object_error")
        }
    }
    static isLiteral_Number_angle_fingers(value: object|string|number|undefined|null|boolean, duplicated_fingers: boolean, duplicated_angle: boolean): boolean {
        if ((!duplicated_fingers) && (value?.hasOwnProperty("fingers"))) {
            return true
        }
        else if ((!duplicated_angle) && (value?.hasOwnProperty("angle"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof Literal_Number_angle_fingers")
        }
    }
    static isLiteral_Number_code_Want_want(value: object|string|number|undefined|null|boolean, duplicated_code: boolean, duplicated_want: boolean): boolean {
        if ((!duplicated_code) && (value?.hasOwnProperty("code"))) {
            return true
        }
        else if ((!duplicated_want) && (value?.hasOwnProperty("want"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof Literal_Number_code_Want_want")
        }
    }
    static isLiteral_Number_day_month_year(value: object|string|number|undefined|null|boolean, duplicated_year: boolean, duplicated_month: boolean, duplicated_day: boolean): boolean {
        if ((!duplicated_year) && (value?.hasOwnProperty("year"))) {
            return true
        }
        else if ((!duplicated_month) && (value?.hasOwnProperty("month"))) {
            return true
        }
        else if ((!duplicated_day) && (value?.hasOwnProperty("day"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof Literal_Number_day_month_year")
        }
    }
    static isLiteral_Number_distance_fingers(value: object|string|number|undefined|null|boolean, duplicated_fingers: boolean, duplicated_distance: boolean): boolean {
        if ((!duplicated_fingers) && (value?.hasOwnProperty("fingers"))) {
            return true
        }
        else if ((!duplicated_distance) && (value?.hasOwnProperty("distance"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof Literal_Number_distance_fingers")
        }
    }
    static isLiteral_Number_distance_fingers_PanDirection_direction(value: object|string|number|undefined|null|boolean, duplicated_fingers: boolean, duplicated_direction: boolean, duplicated_distance: boolean): boolean {
        if ((!duplicated_fingers) && (value?.hasOwnProperty("fingers"))) {
            return true
        }
        else if ((!duplicated_direction) && (value?.hasOwnProperty("direction"))) {
            return true
        }
        else if ((!duplicated_distance) && (value?.hasOwnProperty("distance"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof Literal_Number_distance_fingers_PanDirection_direction")
        }
    }
    static isLiteral_Number_duration_fingers_Boolean_repeat(value: object|string|number|undefined|null|boolean, duplicated_fingers: boolean, duplicated_repeat: boolean, duplicated_duration: boolean): boolean {
        if ((!duplicated_fingers) && (value?.hasOwnProperty("fingers"))) {
            return true
        }
        else if ((!duplicated_repeat) && (value?.hasOwnProperty("repeat"))) {
            return true
        }
        else if ((!duplicated_duration) && (value?.hasOwnProperty("duration"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof Literal_Number_duration_fingers_Boolean_repeat")
        }
    }
    static isLiteral_Number_errcode_String_msg(value: object|string|number|undefined|null|boolean, duplicated_errcode: boolean, duplicated_msg: boolean): boolean {
        if ((!duplicated_errcode) && (value?.hasOwnProperty("errcode"))) {
            return true
        }
        else if ((!duplicated_msg) && (value?.hasOwnProperty("msg"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof Literal_Number_errcode_String_msg")
        }
    }
    static isLiteral_Number_fingers_speed_SwipeDirection_direction(value: object|string|number|undefined|null|boolean, duplicated_fingers: boolean, duplicated_direction: boolean, duplicated_speed: boolean): boolean {
        if ((!duplicated_fingers) && (value?.hasOwnProperty("fingers"))) {
            return true
        }
        else if ((!duplicated_direction) && (value?.hasOwnProperty("direction"))) {
            return true
        }
        else if ((!duplicated_speed) && (value?.hasOwnProperty("speed"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof Literal_Number_fingers_speed_SwipeDirection_direction")
        }
    }
    static isLiteral_Number_index(value: object|string|number|undefined|null|boolean, duplicated_index: boolean): boolean {
        if ((!duplicated_index) && (value?.hasOwnProperty("index"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof Literal_Number_index")
        }
    }
    static isLiteral_Number_offset_span(value: object|string|number|undefined|null|boolean, duplicated_span: boolean, duplicated_offset: boolean): boolean {
        if ((!duplicated_span) && (value?.hasOwnProperty("span"))) {
            return true
        }
        else if ((!duplicated_offset) && (value?.hasOwnProperty("offset"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof Literal_Number_offset_span")
        }
    }
    static isLiteral_Number_offsetRemain(value: object|string|number|undefined|null|boolean, duplicated_offsetRemain: boolean): boolean {
        if ((!duplicated_offsetRemain) && (value?.hasOwnProperty("offsetRemain"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof Literal_Number_offsetRemain")
        }
    }
    static isLiteral_Number_surfaceHeight_surfaceWidth(value: object|string|number|undefined|null|boolean, duplicated_surfaceWidth: boolean, duplicated_surfaceHeight: boolean): boolean {
        if ((!duplicated_surfaceWidth) && (value?.hasOwnProperty("surfaceWidth"))) {
            return true
        }
        else if ((!duplicated_surfaceHeight) && (value?.hasOwnProperty("surfaceHeight"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof Literal_Number_surfaceHeight_surfaceWidth")
        }
    }
    static isLiteral_Object_detail(value: object|string|number|undefined|null|boolean, duplicated_detail: boolean): boolean {
        if ((!duplicated_detail) && (value?.hasOwnProperty("detail"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof Literal_Object_detail")
        }
    }
    static isLiteral_Object_object__String_name_Array_String_methodList(value: object|string|number|undefined|null|boolean, duplicated_object_: boolean, duplicated_name: boolean, duplicated_methodList: boolean): boolean {
        if ((!duplicated_object_) && (value?.hasOwnProperty("object_"))) {
            return true
        }
        else if ((!duplicated_name) && (value?.hasOwnProperty("name"))) {
            return true
        }
        else if ((!duplicated_methodList) && (value?.hasOwnProperty("methodList"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof Literal_Object_object__String_name_Array_String_methodList")
        }
    }
    static isLiteral_ResourceColor_color(value: object|string|number|undefined|null|boolean, duplicated_color: boolean): boolean {
        if ((!duplicated_color) && (value?.hasOwnProperty("color"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof Literal_ResourceColor_color")
        }
    }
    static isHorizontalAlignOptions(value: object|string|number|undefined|null|boolean, duplicated_anchor: boolean, duplicated_align: boolean): boolean {
        if ((!duplicated_anchor) && (value?.hasOwnProperty("anchor"))) {
            return true
        }
        else if ((!duplicated_align) && (value?.hasOwnProperty("align"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof HorizontalAlignOptions")
        }
    }
    static isVerticalAlignOptions(value: object|string|number|undefined|null|boolean, duplicated_anchor: boolean, duplicated_align: boolean): boolean {
        if ((!duplicated_anchor) && (value?.hasOwnProperty("anchor"))) {
            return true
        }
        else if ((!duplicated_align) && (value?.hasOwnProperty("align"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof VerticalAlignOptions")
        }
    }
    static isLiteral_String_baseUrl_data_encoding_historyUrl_mimeType(value: object|string|number|undefined|null|boolean, duplicated_data: boolean, duplicated_mimeType: boolean, duplicated_encoding: boolean, duplicated_baseUrl: boolean, duplicated_historyUrl: boolean): boolean {
        if ((!duplicated_data) && (value?.hasOwnProperty("data"))) {
            return true
        }
        else if ((!duplicated_mimeType) && (value?.hasOwnProperty("mimeType"))) {
            return true
        }
        else if ((!duplicated_encoding) && (value?.hasOwnProperty("encoding"))) {
            return true
        }
        else if ((!duplicated_baseUrl) && (value?.hasOwnProperty("baseUrl"))) {
            return true
        }
        else if ((!duplicated_historyUrl) && (value?.hasOwnProperty("historyUrl"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof Literal_String_baseUrl_data_encoding_historyUrl_mimeType")
        }
    }
    static isLiteral_String_key_Any_defaultValue(value: object|string|number|undefined|null|boolean, duplicated_key: boolean, duplicated_defaultValue: boolean): boolean {
        if ((!duplicated_key) && (value?.hasOwnProperty("key"))) {
            return true
        }
        else if ((!duplicated_defaultValue) && (value?.hasOwnProperty("defaultValue"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof Literal_String_key_Any_defaultValue")
        }
    }
    static isLiteral_String_plainText(value: object|string|number|undefined|null|boolean, duplicated_plainText: boolean): boolean {
        if ((!duplicated_plainText) && (value?.hasOwnProperty("plainText"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof Literal_String_plainText")
        }
    }
    static isLiteral_String_script_Callback_String_Void_callback_(value: object|string|number|undefined|null|boolean, duplicated_script: boolean, duplicated_callback_: boolean): boolean {
        if ((!duplicated_script) && (value?.hasOwnProperty("script"))) {
            return true
        }
        else if ((!duplicated_callback_) && (value?.hasOwnProperty("callback_"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof Literal_String_script_Callback_String_Void_callback_")
        }
    }
    static isLiteral_String_target_NavigationType_type(value: object|string|number|undefined|null|boolean, duplicated_target: boolean, duplicated_type: boolean): boolean {
        if ((!duplicated_target) && (value?.hasOwnProperty("target"))) {
            return true
        }
        else if ((!duplicated_type) && (value?.hasOwnProperty("type"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof Literal_String_target_NavigationType_type")
        }
    }
    static isLiteral_String_value_Callback_Void_action(value: object|string|number|undefined|null|boolean, duplicated_value: boolean, duplicated_action: boolean): boolean {
        if ((!duplicated_value) && (value?.hasOwnProperty("value"))) {
            return true
        }
        else if ((!duplicated_action) && (value?.hasOwnProperty("action"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof Literal_String_value_Callback_Void_action")
        }
    }
    static isLiteral_TransitionEffect_appear_disappear(value: object|string|number|undefined|null|boolean, duplicated_appear: boolean, duplicated_disappear: boolean): boolean {
        if ((!duplicated_appear) && (value?.hasOwnProperty("appear"))) {
            return true
        }
        else if ((!duplicated_disappear) && (value?.hasOwnProperty("disappear"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof Literal_TransitionEffect_appear_disappear")
        }
    }
    static isLiteral_Union_Number_Literal_Number_offset_span_lg_md_sm_xs(value: object|string|number|undefined|null|boolean, duplicated_xs: boolean, duplicated_sm: boolean, duplicated_md: boolean, duplicated_lg: boolean): boolean {
        if ((!duplicated_xs) && (value?.hasOwnProperty("xs"))) {
            return true
        }
        else if ((!duplicated_sm) && (value?.hasOwnProperty("sm"))) {
            return true
        }
        else if ((!duplicated_md) && (value?.hasOwnProperty("md"))) {
            return true
        }
        else if ((!duplicated_lg) && (value?.hasOwnProperty("lg"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs")
        }
    }
    static isLiteral_Union_String_Resource_url_Array_Header_headers(value: object|string|number|undefined|null|boolean, duplicated_url: boolean, duplicated_headers: boolean): boolean {
        if ((!duplicated_url) && (value?.hasOwnProperty("url"))) {
            return true
        }
        else if ((!duplicated_headers) && (value?.hasOwnProperty("headers"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof Literal_Union_String_Resource_url_Array_Header_headers")
        }
    }
    static isLiteral_Union_String_WebResourceRequest_data(value: object|string|number|undefined|null|boolean, duplicated_data: boolean): boolean {
        if ((!duplicated_data) && (value?.hasOwnProperty("data"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof Literal_Union_String_WebResourceRequest_data")
        }
    }
    static isLiteral_Want_want(value: object|string|number|undefined|null|boolean, duplicated_want: boolean): boolean {
        if ((!duplicated_want) && (value?.hasOwnProperty("want"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof Literal_Want_want")
        }
    }
    static isLoadCommittedDetails(value: object|string|number|undefined|null|boolean, duplicated_isMainFrame: boolean, duplicated_isSameDocument: boolean, duplicated_didReplaceEntry: boolean, duplicated_navigationType: boolean, duplicated_url: boolean): boolean {
        if ((!duplicated_isMainFrame) && (value?.hasOwnProperty("isMainFrame"))) {
            return true
        }
        else if ((!duplicated_isSameDocument) && (value?.hasOwnProperty("isSameDocument"))) {
            return true
        }
        else if ((!duplicated_didReplaceEntry) && (value?.hasOwnProperty("didReplaceEntry"))) {
            return true
        }
        else if ((!duplicated_navigationType) && (value?.hasOwnProperty("navigationType"))) {
            return true
        }
        else if ((!duplicated_url) && (value?.hasOwnProperty("url"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof LoadCommittedDetails")
        }
    }
    static isLoadingProgressAttribute(value: object|string|number|undefined|null|boolean, duplicated_color: boolean, duplicated_enableLoading: boolean, duplicated_contentModifier: boolean): boolean {
        if ((!duplicated_color) && (value?.hasOwnProperty("color"))) {
            return true
        }
        else if ((!duplicated_enableLoading) && (value?.hasOwnProperty("enableLoading"))) {
            return true
        }
        else if ((!duplicated_contentModifier) && (value?.hasOwnProperty("contentModifier"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof LoadingProgressAttribute")
        }
    }
    static isLoadingProgressConfiguration(value: object|string|number|undefined|null|boolean, duplicated_enableLoading: boolean): boolean {
        if ((!duplicated_enableLoading) && (value?.hasOwnProperty("enableLoading"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof LoadingProgressConfiguration")
        }
    }
    static isLoadingProgressInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof LoadingProgressInterface")
    }
    static isLoadingProgressStyle(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (LoadingProgressStyle.Default)) {
            return true
        }
        else if ((value) === (LoadingProgressStyle.Circular)) {
            return true
        }
        else if ((value) === (LoadingProgressStyle.Orbital)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof LoadingProgressStyle")
        }
    }
    static isLocalizedAlignRuleOptions(value: object|string|number|undefined|null|boolean, duplicated_start: boolean, duplicated_end: boolean, duplicated_middle: boolean, duplicated_top: boolean, duplicated_bottom: boolean, duplicated_center: boolean, duplicated_bias: boolean): boolean {
        if ((!duplicated_start) && (value?.hasOwnProperty("start"))) {
            return true
        }
        else if ((!duplicated_end) && (value?.hasOwnProperty("end"))) {
            return true
        }
        else if ((!duplicated_middle) && (value?.hasOwnProperty("middle"))) {
            return true
        }
        else if ((!duplicated_top) && (value?.hasOwnProperty("top"))) {
            return true
        }
        else if ((!duplicated_bottom) && (value?.hasOwnProperty("bottom"))) {
            return true
        }
        else if ((!duplicated_center) && (value?.hasOwnProperty("center"))) {
            return true
        }
        else if ((!duplicated_bias) && (value?.hasOwnProperty("bias"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof LocalizedAlignRuleOptions")
        }
    }
    static isLocalizedBarrierDirection(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (LocalizedBarrierDirection.START)) {
            return true
        }
        else if ((value) === (LocalizedBarrierDirection.END)) {
            return true
        }
        else if ((value) === (LocalizedBarrierDirection.TOP)) {
            return true
        }
        else if ((value) === (LocalizedBarrierDirection.BOTTOM)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof LocalizedBarrierDirection")
        }
    }
    static isLocalizedBarrierStyle(value: object|string|number|undefined|null|boolean, duplicated_id: boolean, duplicated_localizedDirection: boolean, duplicated_referencedId: boolean): boolean {
        if ((!duplicated_id) && (value?.hasOwnProperty("id"))) {
            return true
        }
        else if ((!duplicated_localizedDirection) && (value?.hasOwnProperty("localizedDirection"))) {
            return true
        }
        else if ((!duplicated_referencedId) && (value?.hasOwnProperty("referencedId"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof LocalizedBarrierStyle")
        }
    }
    static isLocalizedBorderRadiuses(value: object|string|number|undefined|null|boolean, duplicated_topStart: boolean, duplicated_topEnd: boolean, duplicated_bottomStart: boolean, duplicated_bottomEnd: boolean): boolean {
        if ((!duplicated_topStart) && (value?.hasOwnProperty("topStart"))) {
            return true
        }
        else if ((!duplicated_topEnd) && (value?.hasOwnProperty("topEnd"))) {
            return true
        }
        else if ((!duplicated_bottomStart) && (value?.hasOwnProperty("bottomStart"))) {
            return true
        }
        else if ((!duplicated_bottomEnd) && (value?.hasOwnProperty("bottomEnd"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof LocalizedBorderRadiuses")
        }
    }
    static isLocalizedEdgeColors(value: object|string|number|undefined|null|boolean, duplicated_top: boolean, duplicated_end: boolean, duplicated_bottom: boolean, duplicated_start: boolean): boolean {
        if ((!duplicated_top) && (value?.hasOwnProperty("top"))) {
            return true
        }
        else if ((!duplicated_end) && (value?.hasOwnProperty("end"))) {
            return true
        }
        else if ((!duplicated_bottom) && (value?.hasOwnProperty("bottom"))) {
            return true
        }
        else if ((!duplicated_start) && (value?.hasOwnProperty("start"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof LocalizedEdgeColors")
        }
    }
    static isLocalizedEdges(value: object|string|number|undefined|null|boolean, duplicated_top: boolean, duplicated_start: boolean, duplicated_bottom: boolean, duplicated_end: boolean): boolean {
        if ((!duplicated_top) && (value?.hasOwnProperty("top"))) {
            return true
        }
        else if ((!duplicated_start) && (value?.hasOwnProperty("start"))) {
            return true
        }
        else if ((!duplicated_bottom) && (value?.hasOwnProperty("bottom"))) {
            return true
        }
        else if ((!duplicated_end) && (value?.hasOwnProperty("end"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof LocalizedEdges")
        }
    }
    static isLocalizedEdgeWidths(value: object|string|number|undefined|null|boolean, duplicated_top: boolean, duplicated_end: boolean, duplicated_bottom: boolean, duplicated_start: boolean): boolean {
        if ((!duplicated_top) && (value?.hasOwnProperty("top"))) {
            return true
        }
        else if ((!duplicated_end) && (value?.hasOwnProperty("end"))) {
            return true
        }
        else if ((!duplicated_bottom) && (value?.hasOwnProperty("bottom"))) {
            return true
        }
        else if ((!duplicated_start) && (value?.hasOwnProperty("start"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof LocalizedEdgeWidths")
        }
    }
    static isLocalizedHorizontalAlignParam(value: object|string|number|undefined|null|boolean, duplicated_anchor: boolean, duplicated_align: boolean): boolean {
        if ((!duplicated_anchor) && (value?.hasOwnProperty("anchor"))) {
            return true
        }
        else if ((!duplicated_align) && (value?.hasOwnProperty("align"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof LocalizedHorizontalAlignParam")
        }
    }
    static isLocalizedPadding(value: object|string|number|undefined|null|boolean, duplicated_top: boolean, duplicated_end: boolean, duplicated_bottom: boolean, duplicated_start: boolean): boolean {
        if ((!duplicated_top) && (value?.hasOwnProperty("top"))) {
            return true
        }
        else if ((!duplicated_end) && (value?.hasOwnProperty("end"))) {
            return true
        }
        else if ((!duplicated_bottom) && (value?.hasOwnProperty("bottom"))) {
            return true
        }
        else if ((!duplicated_start) && (value?.hasOwnProperty("start"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof LocalizedPadding")
        }
    }
    static isLocalizedPosition(value: object|string|number|undefined|null|boolean, duplicated_start: boolean, duplicated_top: boolean): boolean {
        if ((!duplicated_start) && (value?.hasOwnProperty("start"))) {
            return true
        }
        else if ((!duplicated_top) && (value?.hasOwnProperty("top"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof LocalizedPosition")
        }
    }
    static isLocalizedVerticalAlignParam(value: object|string|number|undefined|null|boolean, duplicated_anchor: boolean, duplicated_align: boolean): boolean {
        if ((!duplicated_anchor) && (value?.hasOwnProperty("anchor"))) {
            return true
        }
        else if ((!duplicated_align) && (value?.hasOwnProperty("align"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof LocalizedVerticalAlignParam")
        }
    }
    static isLocationButtonAttribute(value: object|string|number|undefined|null|boolean, duplicated_onClick: boolean): boolean {
        if ((!duplicated_onClick) && (value?.hasOwnProperty("onClick"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof LocationButtonAttribute")
        }
    }
    static isLocationButtonInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof LocationButtonInterface")
    }
    static isLocationButtonOnClickResult(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (LocationButtonOnClickResult.SUCCESS)) {
            return true
        }
        else if ((value) === (LocationButtonOnClickResult.TEMPORARY_AUTHORIZATION_FAILED)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof LocationButtonOnClickResult")
        }
    }
    static isLocationButtonOptions(value: object|string|number|undefined|null|boolean, duplicated_icon: boolean, duplicated_text: boolean, duplicated_buttonType: boolean): boolean {
        if ((!duplicated_icon) && (value?.hasOwnProperty("icon"))) {
            return true
        }
        else if ((!duplicated_text) && (value?.hasOwnProperty("text"))) {
            return true
        }
        else if ((!duplicated_buttonType) && (value?.hasOwnProperty("buttonType"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof LocationButtonOptions")
        }
    }
    static isLocationDescription(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (LocationDescription.CURRENT_LOCATION)) {
            return true
        }
        else if ((value) === (LocationDescription.ADD_LOCATION)) {
            return true
        }
        else if ((value) === (LocationDescription.SELECT_LOCATION)) {
            return true
        }
        else if ((value) === (LocationDescription.SHARE_LOCATION)) {
            return true
        }
        else if ((value) === (LocationDescription.SEND_LOCATION)) {
            return true
        }
        else if ((value) === (LocationDescription.LOCATING)) {
            return true
        }
        else if ((value) === (LocationDescription.LOCATION)) {
            return true
        }
        else if ((value) === (LocationDescription.SEND_CURRENT_LOCATION)) {
            return true
        }
        else if ((value) === (LocationDescription.RELOCATION)) {
            return true
        }
        else if ((value) === (LocationDescription.PUNCH_IN)) {
            return true
        }
        else if ((value) === (LocationDescription.CURRENT_POSITION)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof LocationDescription")
        }
    }
    static isLocationIconStyle(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (LocationIconStyle.FULL_FILLED)) {
            return true
        }
        else if ((value) === (LocationIconStyle.LINES)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof LocationIconStyle")
        }
    }
    static isLongPressGestureEvent(value: object|string|number|undefined|null|boolean, duplicated_repeat: boolean): boolean {
        if ((!duplicated_repeat) && (value?.hasOwnProperty("repeat"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof LongPressGestureEvent")
        }
    }
    static isLongPressGestureHandler(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof LongPressGestureHandler")
    }
    static isLongPressGestureHandlerOptions(value: object|string|number|undefined|null|boolean, duplicated_fingers: boolean, duplicated_repeat: boolean, duplicated_duration: boolean): boolean {
        if ((!duplicated_fingers) && (value?.hasOwnProperty("fingers"))) {
            return true
        }
        else if ((!duplicated_repeat) && (value?.hasOwnProperty("repeat"))) {
            return true
        }
        else if ((!duplicated_duration) && (value?.hasOwnProperty("duration"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof LongPressGestureHandlerOptions")
        }
    }
    static isLongPressGestureInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof LongPressGestureInterface")
    }
    static isLunarSwitchStyle(value: object|string|number|undefined|null|boolean, duplicated_selectedColor: boolean, duplicated_unselectedColor: boolean, duplicated_strokeColor: boolean): boolean {
        if ((!duplicated_selectedColor) && (value?.hasOwnProperty("selectedColor"))) {
            return true
        }
        else if ((!duplicated_unselectedColor) && (value?.hasOwnProperty("unselectedColor"))) {
            return true
        }
        else if ((!duplicated_strokeColor) && (value?.hasOwnProperty("strokeColor"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof LunarSwitchStyle")
        }
    }
    static isMarkStyle(value: object|string|number|undefined|null|boolean, duplicated_strokeColor: boolean, duplicated_size: boolean, duplicated_strokeWidth: boolean): boolean {
        if ((!duplicated_strokeColor) && (value?.hasOwnProperty("strokeColor"))) {
            return true
        }
        else if ((!duplicated_size) && (value?.hasOwnProperty("size"))) {
            return true
        }
        else if ((!duplicated_strokeWidth) && (value?.hasOwnProperty("strokeWidth"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof MarkStyle")
        }
    }
    static isMarqueeAttribute(value: object|string|number|undefined|null|boolean, duplicated_fontColor: boolean, duplicated_fontSize: boolean, duplicated_allowScale: boolean, duplicated_fontWeight: boolean, duplicated_fontFamily: boolean, duplicated_marqueeUpdateStrategy: boolean, duplicated_onStart: boolean, duplicated_onBounce: boolean, duplicated_onFinish: boolean): boolean {
        if ((!duplicated_fontColor) && (value?.hasOwnProperty("fontColor"))) {
            return true
        }
        else if ((!duplicated_fontSize) && (value?.hasOwnProperty("fontSize"))) {
            return true
        }
        else if ((!duplicated_allowScale) && (value?.hasOwnProperty("allowScale"))) {
            return true
        }
        else if ((!duplicated_fontWeight) && (value?.hasOwnProperty("fontWeight"))) {
            return true
        }
        else if ((!duplicated_fontFamily) && (value?.hasOwnProperty("fontFamily"))) {
            return true
        }
        else if ((!duplicated_marqueeUpdateStrategy) && (value?.hasOwnProperty("marqueeUpdateStrategy"))) {
            return true
        }
        else if ((!duplicated_onStart) && (value?.hasOwnProperty("onStart"))) {
            return true
        }
        else if ((!duplicated_onBounce) && (value?.hasOwnProperty("onBounce"))) {
            return true
        }
        else if ((!duplicated_onFinish) && (value?.hasOwnProperty("onFinish"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof MarqueeAttribute")
        }
    }
    static isMarqueeInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof MarqueeInterface")
    }
    static isMarqueeOptions(value: object|string|number|undefined|null|boolean, duplicated_start: boolean, duplicated_step: boolean, duplicated_loop: boolean, duplicated_fromStart: boolean, duplicated_src: boolean): boolean {
        if ((!duplicated_start) && (value?.hasOwnProperty("start"))) {
            return true
        }
        else if ((!duplicated_src) && (value?.hasOwnProperty("src"))) {
            return true
        }
        else if ((!duplicated_step) && (value?.hasOwnProperty("step"))) {
            return true
        }
        else if ((!duplicated_loop) && (value?.hasOwnProperty("loop"))) {
            return true
        }
        else if ((!duplicated_fromStart) && (value?.hasOwnProperty("fromStart"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof MarqueeOptions")
        }
    }
    static isMarqueeUpdateStrategy(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (MarqueeUpdateStrategy.DEFAULT)) {
            return true
        }
        else if ((value) === (MarqueeUpdateStrategy.PRESERVE_POSITION)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof MarqueeUpdateStrategy")
        }
    }
    static isMatrix2D(value: object|string|number|undefined|null|boolean, duplicated_scaleX: boolean, duplicated_rotateY: boolean, duplicated_rotateX: boolean, duplicated_scaleY: boolean, duplicated_translateX: boolean, duplicated_translateY: boolean): boolean {
        if ((!duplicated_scaleX) && (value?.hasOwnProperty("scaleX"))) {
            return true
        }
        else if ((!duplicated_rotateY) && (value?.hasOwnProperty("rotateY"))) {
            return true
        }
        else if ((!duplicated_rotateX) && (value?.hasOwnProperty("rotateX"))) {
            return true
        }
        else if ((!duplicated_scaleY) && (value?.hasOwnProperty("scaleY"))) {
            return true
        }
        else if ((!duplicated_translateX) && (value?.hasOwnProperty("translateX"))) {
            return true
        }
        else if ((!duplicated_translateY) && (value?.hasOwnProperty("translateY"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof Matrix2D")
        }
    }
    static isMeasurable(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof Measurable")
    }
    static isMeasureOptions(value: object|string|number|undefined|null|boolean, duplicated_textContent: boolean, duplicated_constraintWidth: boolean, duplicated_fontSize: boolean, duplicated_fontStyle: boolean, duplicated_fontWeight: boolean, duplicated_fontFamily: boolean, duplicated_letterSpacing: boolean, duplicated_textAlign: boolean, duplicated_overflow: boolean, duplicated_maxLines: boolean, duplicated_lineHeight: boolean, duplicated_baselineOffset: boolean, duplicated_textCase: boolean, duplicated_textIndent: boolean, duplicated_wordBreak: boolean): boolean {
        if ((!duplicated_textContent) && (value?.hasOwnProperty("textContent"))) {
            return true
        }
        else if ((!duplicated_constraintWidth) && (value?.hasOwnProperty("constraintWidth"))) {
            return true
        }
        else if ((!duplicated_fontSize) && (value?.hasOwnProperty("fontSize"))) {
            return true
        }
        else if ((!duplicated_fontStyle) && (value?.hasOwnProperty("fontStyle"))) {
            return true
        }
        else if ((!duplicated_fontWeight) && (value?.hasOwnProperty("fontWeight"))) {
            return true
        }
        else if ((!duplicated_fontFamily) && (value?.hasOwnProperty("fontFamily"))) {
            return true
        }
        else if ((!duplicated_letterSpacing) && (value?.hasOwnProperty("letterSpacing"))) {
            return true
        }
        else if ((!duplicated_textAlign) && (value?.hasOwnProperty("textAlign"))) {
            return true
        }
        else if ((!duplicated_overflow) && (value?.hasOwnProperty("overflow"))) {
            return true
        }
        else if ((!duplicated_maxLines) && (value?.hasOwnProperty("maxLines"))) {
            return true
        }
        else if ((!duplicated_lineHeight) && (value?.hasOwnProperty("lineHeight"))) {
            return true
        }
        else if ((!duplicated_baselineOffset) && (value?.hasOwnProperty("baselineOffset"))) {
            return true
        }
        else if ((!duplicated_textCase) && (value?.hasOwnProperty("textCase"))) {
            return true
        }
        else if ((!duplicated_textIndent) && (value?.hasOwnProperty("textIndent"))) {
            return true
        }
        else if ((!duplicated_wordBreak) && (value?.hasOwnProperty("wordBreak"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof MeasureOptions")
        }
    }
    static isMeasureResult(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof MeasureResult")
    }
    static isMediaCachedImageAttribute(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof MediaCachedImageAttribute")
    }
    static isMediaCachedImageInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof MediaCachedImageInterface")
    }
    static isMenuAlignType(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (MenuAlignType.START)) {
            return true
        }
        else if ((value) === (MenuAlignType.CENTER)) {
            return true
        }
        else if ((value) === (MenuAlignType.END)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof MenuAlignType")
        }
    }
    static isMenuAttribute(value: object|string|number|undefined|null|boolean, duplicated_fontSize: boolean, duplicated_font: boolean, duplicated_fontColor: boolean, duplicated_radius: boolean, duplicated_menuItemDivider: boolean, duplicated_menuItemGroupDivider: boolean, duplicated_subMenuExpandingMode: boolean): boolean {
        if ((!duplicated_fontSize) && (value?.hasOwnProperty("fontSize"))) {
            return true
        }
        else if ((!duplicated_font) && (value?.hasOwnProperty("font"))) {
            return true
        }
        else if ((!duplicated_fontColor) && (value?.hasOwnProperty("fontColor"))) {
            return true
        }
        else if ((!duplicated_radius) && (value?.hasOwnProperty("radius"))) {
            return true
        }
        else if ((!duplicated_menuItemDivider) && (value?.hasOwnProperty("menuItemDivider"))) {
            return true
        }
        else if ((!duplicated_menuItemGroupDivider) && (value?.hasOwnProperty("menuItemGroupDivider"))) {
            return true
        }
        else if ((!duplicated_subMenuExpandingMode) && (value?.hasOwnProperty("subMenuExpandingMode"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof MenuAttribute")
        }
    }
    static isMenuElement(value: object|string|number|undefined|null|boolean, duplicated_value: boolean, duplicated_icon: boolean, duplicated_symbolIcon: boolean, duplicated_enabled: boolean, duplicated_action: boolean): boolean {
        if ((!duplicated_value) && (value?.hasOwnProperty("value"))) {
            return true
        }
        else if ((!duplicated_action) && (value?.hasOwnProperty("action"))) {
            return true
        }
        else if ((!duplicated_icon) && (value?.hasOwnProperty("icon"))) {
            return true
        }
        else if ((!duplicated_symbolIcon) && (value?.hasOwnProperty("symbolIcon"))) {
            return true
        }
        else if ((!duplicated_enabled) && (value?.hasOwnProperty("enabled"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof MenuElement")
        }
    }
    static isMenuInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof MenuInterface")
    }
    static isMenuItemAttribute(value: object|string|number|undefined|null|boolean, duplicated_selected: boolean, duplicated_selectIcon: boolean, duplicated_onChange: boolean, duplicated_contentFont: boolean, duplicated_contentFontColor: boolean, duplicated_labelFont: boolean, duplicated_labelFontColor: boolean): boolean {
        if ((!duplicated_selected) && (value?.hasOwnProperty("selected"))) {
            return true
        }
        else if ((!duplicated_selectIcon) && (value?.hasOwnProperty("selectIcon"))) {
            return true
        }
        else if ((!duplicated_onChange) && (value?.hasOwnProperty("onChange"))) {
            return true
        }
        else if ((!duplicated_contentFont) && (value?.hasOwnProperty("contentFont"))) {
            return true
        }
        else if ((!duplicated_contentFontColor) && (value?.hasOwnProperty("contentFontColor"))) {
            return true
        }
        else if ((!duplicated_labelFont) && (value?.hasOwnProperty("labelFont"))) {
            return true
        }
        else if ((!duplicated_labelFontColor) && (value?.hasOwnProperty("labelFontColor"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof MenuItemAttribute")
        }
    }
    static isMenuItemConfiguration(value: object|string|number|undefined|null|boolean, duplicated_value: boolean, duplicated_icon: boolean, duplicated_symbolIcon: boolean, duplicated_selected: boolean, duplicated_index: boolean): boolean {
        if ((!duplicated_value) && (value?.hasOwnProperty("value"))) {
            return true
        }
        else if ((!duplicated_selected) && (value?.hasOwnProperty("selected"))) {
            return true
        }
        else if ((!duplicated_index) && (value?.hasOwnProperty("index"))) {
            return true
        }
        else if ((!duplicated_icon) && (value?.hasOwnProperty("icon"))) {
            return true
        }
        else if ((!duplicated_symbolIcon) && (value?.hasOwnProperty("symbolIcon"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof MenuItemConfiguration")
        }
    }
    static isMenuItemGroupAttribute(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof MenuItemGroupAttribute")
    }
    static isMenuItemGroupInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof MenuItemGroupInterface")
    }
    static isMenuItemGroupOptions(value: object|string|number|undefined|null|boolean, duplicated_header: boolean, duplicated_footer: boolean): boolean {
        if ((!duplicated_header) && (value?.hasOwnProperty("header"))) {
            return true
        }
        else if ((!duplicated_footer) && (value?.hasOwnProperty("footer"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof MenuItemGroupOptions")
        }
    }
    static isMenuItemInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof MenuItemInterface")
    }
    static isMenuItemOptions(value: object|string|number|undefined|null|boolean, duplicated_startIcon: boolean, duplicated_symbolStartIcon: boolean, duplicated_content: boolean, duplicated_endIcon: boolean, duplicated_symbolEndIcon: boolean, duplicated_labelInfo: boolean, duplicated_builder: boolean): boolean {
        if ((!duplicated_startIcon) && (value?.hasOwnProperty("startIcon"))) {
            return true
        }
        else if ((!duplicated_symbolStartIcon) && (value?.hasOwnProperty("symbolStartIcon"))) {
            return true
        }
        else if ((!duplicated_content) && (value?.hasOwnProperty("content"))) {
            return true
        }
        else if ((!duplicated_endIcon) && (value?.hasOwnProperty("endIcon"))) {
            return true
        }
        else if ((!duplicated_symbolEndIcon) && (value?.hasOwnProperty("symbolEndIcon"))) {
            return true
        }
        else if ((!duplicated_labelInfo) && (value?.hasOwnProperty("labelInfo"))) {
            return true
        }
        else if ((!duplicated_builder) && (value?.hasOwnProperty("builder"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof MenuItemOptions")
        }
    }
    static isMenuOptions(value: object|string|number|undefined|null|boolean, duplicated_title: boolean, duplicated_showInSubWindow: boolean): boolean {
        if ((!duplicated_title) && (value?.hasOwnProperty("title"))) {
            return true
        }
        else if ((!duplicated_showInSubWindow) && (value?.hasOwnProperty("showInSubWindow"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof MenuOptions")
        }
    }
    static isMenuPolicy(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (MenuPolicy.DEFAULT)) {
            return true
        }
        else if ((value) === (MenuPolicy.HIDE)) {
            return true
        }
        else if ((value) === (MenuPolicy.SHOW)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof MenuPolicy")
        }
    }
    static isMenuPreviewMode(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (MenuPreviewMode.NONE)) {
            return true
        }
        else if ((value) === (MenuPreviewMode.IMAGE)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof MenuPreviewMode")
        }
    }
    static isMenuType(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (MenuType.SELECTION_MENU)) {
            return true
        }
        else if ((value) === (MenuType.PREVIEW_MENU)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof MenuType")
        }
    }
    static isMessageLevel(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (MessageLevel.Debug)) {
            return true
        }
        else if ((value) === (MessageLevel.Error)) {
            return true
        }
        else if ((value) === (MessageLevel.Info)) {
            return true
        }
        else if ((value) === (MessageLevel.Log)) {
            return true
        }
        else if ((value) === (MessageLevel.Warn)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof MessageLevel")
        }
    }
    static isMixedMode(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (MixedMode.All)) {
            return true
        }
        else if ((value) === (MixedMode.Compatible)) {
            return true
        }
        else if ((value) === (MixedMode.None)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof MixedMode")
        }
    }
    static isModalTransition(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (ModalTransition.DEFAULT)) {
            return true
        }
        else if ((value) === (ModalTransition.NONE)) {
            return true
        }
        else if ((value) === (ModalTransition.ALPHA)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ModalTransition")
        }
    }
    static isModelType(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (ModelType.TEXTURE)) {
            return true
        }
        else if ((value) === (ModelType.SURFACE)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ModelType")
        }
    }
    static isModifierKey(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (ModifierKey.CTRL)) {
            return true
        }
        else if ((value) === (ModifierKey.SHIFT)) {
            return true
        }
        else if ((value) === (ModifierKey.ALT)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ModifierKey")
        }
    }
    static isMonthData(value: object|string|number|undefined|null|boolean, duplicated_year: boolean, duplicated_month: boolean, duplicated_data: boolean): boolean {
        if ((!duplicated_year) && (value?.hasOwnProperty("year"))) {
            return true
        }
        else if ((!duplicated_month) && (value?.hasOwnProperty("month"))) {
            return true
        }
        else if ((!duplicated_data) && (value?.hasOwnProperty("data"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof MonthData")
        }
    }
    static isMotionBlurAnchor(value: object|string|number|undefined|null|boolean, duplicated_x: boolean, duplicated_y: boolean): boolean {
        if ((!duplicated_x) && (value?.hasOwnProperty("x"))) {
            return true
        }
        else if ((!duplicated_y) && (value?.hasOwnProperty("y"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof MotionBlurAnchor")
        }
    }
    static isMotionBlurOptions(value: object|string|number|undefined|null|boolean, duplicated_radius: boolean, duplicated_anchor: boolean): boolean {
        if ((!duplicated_radius) && (value?.hasOwnProperty("radius"))) {
            return true
        }
        else if ((!duplicated_anchor) && (value?.hasOwnProperty("anchor"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof MotionBlurOptions")
        }
    }
    static isMotionPathOptions(value: object|string|number|undefined|null|boolean, duplicated_path: boolean, duplicated_from: boolean, duplicated_to: boolean, duplicated_rotatable: boolean): boolean {
        if ((!duplicated_path) && (value?.hasOwnProperty("path"))) {
            return true
        }
        else if ((!duplicated_from) && (value?.hasOwnProperty("from"))) {
            return true
        }
        else if ((!duplicated_to) && (value?.hasOwnProperty("to"))) {
            return true
        }
        else if ((!duplicated_rotatable) && (value?.hasOwnProperty("rotatable"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof MotionPathOptions")
        }
    }
    static isMouseAction(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (MouseAction.Press)) {
            return true
        }
        else if ((value) === (MouseAction.Release)) {
            return true
        }
        else if ((value) === (MouseAction.Move)) {
            return true
        }
        else if ((value) === (MouseAction.Hover)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof MouseAction")
        }
    }
    static isMouseButton(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (MouseButton.Left)) {
            return true
        }
        else if ((value) === (MouseButton.Right)) {
            return true
        }
        else if ((value) === (MouseButton.Middle)) {
            return true
        }
        else if ((value) === (MouseButton.Back)) {
            return true
        }
        else if ((value) === (MouseButton.Forward)) {
            return true
        }
        else if ((value) === (MouseButton.None)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof MouseButton")
        }
    }
    static isMouseEvent(value: object|string|number|undefined|null|boolean, duplicated_button: boolean, duplicated_action: boolean, duplicated_displayX: boolean, duplicated_displayY: boolean, duplicated_windowX: boolean, duplicated_windowY: boolean, duplicated_screenX: boolean, duplicated_screenY: boolean, duplicated_x: boolean, duplicated_y: boolean, duplicated_stopPropagation: boolean): boolean {
        if ((!duplicated_button) && (value?.hasOwnProperty("button"))) {
            return true
        }
        else if ((!duplicated_action) && (value?.hasOwnProperty("action"))) {
            return true
        }
        else if ((!duplicated_displayX) && (value?.hasOwnProperty("displayX"))) {
            return true
        }
        else if ((!duplicated_displayY) && (value?.hasOwnProperty("displayY"))) {
            return true
        }
        else if ((!duplicated_windowX) && (value?.hasOwnProperty("windowX"))) {
            return true
        }
        else if ((!duplicated_windowY) && (value?.hasOwnProperty("windowY"))) {
            return true
        }
        else if ((!duplicated_screenX) && (value?.hasOwnProperty("screenX"))) {
            return true
        }
        else if ((!duplicated_screenY) && (value?.hasOwnProperty("screenY"))) {
            return true
        }
        else if ((!duplicated_x) && (value?.hasOwnProperty("x"))) {
            return true
        }
        else if ((!duplicated_y) && (value?.hasOwnProperty("y"))) {
            return true
        }
        else if ((!duplicated_stopPropagation) && (value?.hasOwnProperty("stopPropagation"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof MouseEvent")
        }
    }
    static isMoveIndex(value: object|string|number|undefined|null|boolean, duplicated_from: boolean, duplicated_to: boolean): boolean {
        if ((!duplicated_from) && (value?.hasOwnProperty("from"))) {
            return true
        }
        else if ((!duplicated_to) && (value?.hasOwnProperty("to"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof MoveIndex")
        }
    }
    static isMultiShadowOptions(value: object|string|number|undefined|null|boolean, duplicated_radius: boolean, duplicated_offsetX: boolean, duplicated_offsetY: boolean): boolean {
        if ((!duplicated_radius) && (value?.hasOwnProperty("radius"))) {
            return true
        }
        else if ((!duplicated_offsetX) && (value?.hasOwnProperty("offsetX"))) {
            return true
        }
        else if ((!duplicated_offsetY) && (value?.hasOwnProperty("offsetY"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof MultiShadowOptions")
        }
    }
    static isMutableStyledString(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof MutableStyledString")
    }
    static isNativeEmbedDataInfo(value: object|string|number|undefined|null|boolean, duplicated_status: boolean, duplicated_surfaceId: boolean, duplicated_embedId: boolean, duplicated_info: boolean): boolean {
        if ((!duplicated_status) && (value?.hasOwnProperty("status"))) {
            return true
        }
        else if ((!duplicated_surfaceId) && (value?.hasOwnProperty("surfaceId"))) {
            return true
        }
        else if ((!duplicated_embedId) && (value?.hasOwnProperty("embedId"))) {
            return true
        }
        else if ((!duplicated_info) && (value?.hasOwnProperty("info"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof NativeEmbedDataInfo")
        }
    }
    static isNativeEmbedInfo(value: object|string|number|undefined|null|boolean, duplicated_id: boolean, duplicated_type: boolean, duplicated_src: boolean, duplicated_position: boolean, duplicated_width: boolean, duplicated_height: boolean, duplicated_url: boolean, duplicated_tag: boolean, duplicated_params: boolean): boolean {
        if ((!duplicated_id) && (value?.hasOwnProperty("id"))) {
            return true
        }
        else if ((!duplicated_type) && (value?.hasOwnProperty("type"))) {
            return true
        }
        else if ((!duplicated_src) && (value?.hasOwnProperty("src"))) {
            return true
        }
        else if ((!duplicated_position) && (value?.hasOwnProperty("position"))) {
            return true
        }
        else if ((!duplicated_width) && (value?.hasOwnProperty("width"))) {
            return true
        }
        else if ((!duplicated_height) && (value?.hasOwnProperty("height"))) {
            return true
        }
        else if ((!duplicated_url) && (value?.hasOwnProperty("url"))) {
            return true
        }
        else if ((!duplicated_tag) && (value?.hasOwnProperty("tag"))) {
            return true
        }
        else if ((!duplicated_params) && (value?.hasOwnProperty("params"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof NativeEmbedInfo")
        }
    }
    static isNativeEmbedStatus(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (NativeEmbedStatus.CREATE)) {
            return true
        }
        else if ((value) === (NativeEmbedStatus.UPDATE)) {
            return true
        }
        else if ((value) === (NativeEmbedStatus.DESTROY)) {
            return true
        }
        else if ((value) === (NativeEmbedStatus.ENTER_BFCACHE)) {
            return true
        }
        else if ((value) === (NativeEmbedStatus.LEAVE_BFCACHE)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof NativeEmbedStatus")
        }
    }
    static isNativeEmbedTouchInfo(value: object|string|number|undefined|null|boolean, duplicated_embedId: boolean, duplicated_touchEvent: boolean, duplicated_result: boolean): boolean {
        if ((!duplicated_embedId) && (value?.hasOwnProperty("embedId"))) {
            return true
        }
        else if ((!duplicated_touchEvent) && (value?.hasOwnProperty("touchEvent"))) {
            return true
        }
        else if ((!duplicated_result) && (value?.hasOwnProperty("result"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof NativeEmbedTouchInfo")
        }
    }
    static isNativeEmbedVisibilityInfo(value: object|string|number|undefined|null|boolean, duplicated_visibility: boolean, duplicated_embedId: boolean): boolean {
        if ((!duplicated_visibility) && (value?.hasOwnProperty("visibility"))) {
            return true
        }
        else if ((!duplicated_embedId) && (value?.hasOwnProperty("embedId"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof NativeEmbedVisibilityInfo")
        }
    }
    static isNativeMediaPlayerConfig(value: object|string|number|undefined|null|boolean, duplicated_enable: boolean, duplicated_shouldOverlay: boolean): boolean {
        if ((!duplicated_enable) && (value?.hasOwnProperty("enable"))) {
            return true
        }
        else if ((!duplicated_shouldOverlay) && (value?.hasOwnProperty("shouldOverlay"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof NativeMediaPlayerConfig")
        }
    }
    static isNavBarPosition(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (NavBarPosition.Start)) {
            return true
        }
        else if ((value) === (NavBarPosition.End)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof NavBarPosition")
        }
    }
    static isNavContentInfo(value: object|string|number|undefined|null|boolean, duplicated_name: boolean, duplicated_index: boolean, duplicated_mode: boolean, duplicated_param: boolean, duplicated_navDestinationId: boolean): boolean {
        if ((!duplicated_index) && (value?.hasOwnProperty("index"))) {
            return true
        }
        else if ((!duplicated_name) && (value?.hasOwnProperty("name"))) {
            return true
        }
        else if ((!duplicated_mode) && (value?.hasOwnProperty("mode"))) {
            return true
        }
        else if ((!duplicated_param) && (value?.hasOwnProperty("param"))) {
            return true
        }
        else if ((!duplicated_navDestinationId) && (value?.hasOwnProperty("navDestinationId"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof NavContentInfo")
        }
    }
    static isNavDestinationAttribute(value: object|string|number|undefined|null|boolean, duplicated_hideTitleBar: boolean, duplicated_onShown: boolean, duplicated_onHidden: boolean, duplicated_onBackPressed: boolean, duplicated_mode: boolean, duplicated_backButtonIcon: boolean, duplicated_menus: boolean, duplicated_onReady: boolean, duplicated_onWillAppear: boolean, duplicated_onWillDisappear: boolean, duplicated_onWillShow: boolean, duplicated_onWillHide: boolean, duplicated_systemBarStyle: boolean, duplicated_recoverable: boolean, duplicated_systemTransition: boolean): boolean {
        if ((!duplicated_hideTitleBar) && (value?.hasOwnProperty("hideTitleBar"))) {
            return true
        }
        else if ((!duplicated_onShown) && (value?.hasOwnProperty("onShown"))) {
            return true
        }
        else if ((!duplicated_onHidden) && (value?.hasOwnProperty("onHidden"))) {
            return true
        }
        else if ((!duplicated_onBackPressed) && (value?.hasOwnProperty("onBackPressed"))) {
            return true
        }
        else if ((!duplicated_mode) && (value?.hasOwnProperty("mode"))) {
            return true
        }
        else if ((!duplicated_backButtonIcon) && (value?.hasOwnProperty("backButtonIcon"))) {
            return true
        }
        else if ((!duplicated_menus) && (value?.hasOwnProperty("menus"))) {
            return true
        }
        else if ((!duplicated_onReady) && (value?.hasOwnProperty("onReady"))) {
            return true
        }
        else if ((!duplicated_onWillAppear) && (value?.hasOwnProperty("onWillAppear"))) {
            return true
        }
        else if ((!duplicated_onWillDisappear) && (value?.hasOwnProperty("onWillDisappear"))) {
            return true
        }
        else if ((!duplicated_onWillShow) && (value?.hasOwnProperty("onWillShow"))) {
            return true
        }
        else if ((!duplicated_onWillHide) && (value?.hasOwnProperty("onWillHide"))) {
            return true
        }
        else if ((!duplicated_systemBarStyle) && (value?.hasOwnProperty("systemBarStyle"))) {
            return true
        }
        else if ((!duplicated_recoverable) && (value?.hasOwnProperty("recoverable"))) {
            return true
        }
        else if ((!duplicated_systemTransition) && (value?.hasOwnProperty("systemTransition"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof NavDestinationAttribute")
        }
    }
    static isNavDestinationCommonTitle(value: object|string|number|undefined|null|boolean, duplicated_main: boolean, duplicated_sub: boolean): boolean {
        if ((!duplicated_main) && (value?.hasOwnProperty("main"))) {
            return true
        }
        else if ((!duplicated_sub) && (value?.hasOwnProperty("sub"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof NavDestinationCommonTitle")
        }
    }
    static isNavDestinationContext(value: object|string|number|undefined|null|boolean, duplicated_pathInfo: boolean, duplicated_pathStack: boolean, duplicated_navDestinationId: boolean): boolean {
        if ((!duplicated_pathInfo) && (value?.hasOwnProperty("pathInfo"))) {
            return true
        }
        else if ((!duplicated_pathStack) && (value?.hasOwnProperty("pathStack"))) {
            return true
        }
        else if ((!duplicated_navDestinationId) && (value?.hasOwnProperty("navDestinationId"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof NavDestinationContext")
        }
    }
    static isNavDestinationCustomTitle(value: object|string|number|undefined|null|boolean, duplicated_builder: boolean, duplicated_height: boolean): boolean {
        if ((!duplicated_builder) && (value?.hasOwnProperty("builder"))) {
            return true
        }
        else if ((!duplicated_height) && (value?.hasOwnProperty("height"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof NavDestinationCustomTitle")
        }
    }
    static isNavDestinationInfo(value: object|string|number|undefined|null|boolean, duplicated__NavDestinationInfoStub: boolean): boolean {
        if ((!duplicated__NavDestinationInfoStub) && (value?.hasOwnProperty("_NavDestinationInfoStub"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof NavDestinationInfo")
        }
    }
    static isNavDestinationInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof NavDestinationInterface")
    }
    static isNavDestinationMode(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (NavDestinationMode.STANDARD)) {
            return true
        }
        else if ((value) === (NavDestinationMode.DIALOG)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof NavDestinationMode")
        }
    }
    static isNavExtender(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof NavExtender")
    }
    static isNavigationAnimatedTransition(value: object|string|number|undefined|null|boolean, duplicated_onTransitionEnd: boolean, duplicated_timeout: boolean, duplicated_isInteractive: boolean, duplicated_transition: boolean): boolean {
        if ((!duplicated_transition) && (value?.hasOwnProperty("transition"))) {
            return true
        }
        else if ((!duplicated_onTransitionEnd) && (value?.hasOwnProperty("onTransitionEnd"))) {
            return true
        }
        else if ((!duplicated_timeout) && (value?.hasOwnProperty("timeout"))) {
            return true
        }
        else if ((!duplicated_isInteractive) && (value?.hasOwnProperty("isInteractive"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof NavigationAnimatedTransition")
        }
    }
    static isNavigationAttribute(value: object|string|number|undefined|null|boolean, duplicated_navBarWidth: boolean, duplicated_navBarPosition: boolean, duplicated_navBarWidthRange: boolean, duplicated_minContentWidth: boolean, duplicated_mode: boolean, duplicated_backButtonIcon: boolean, duplicated_hideNavBar: boolean, duplicated_subTitle: boolean, duplicated_hideTitleBar: boolean, duplicated_hideBackButton: boolean, duplicated_titleMode: boolean, duplicated_menus: boolean, duplicated_toolBar: boolean, duplicated_hideToolBar: boolean, duplicated_onTitleModeChange: boolean, duplicated_onNavBarStateChange: boolean, duplicated_onNavigationModeChange: boolean, duplicated_navDestination: boolean, duplicated_customNavContentTransition: boolean, duplicated_systemBarStyle: boolean, duplicated_recoverable: boolean, duplicated_enableDragBar: boolean): boolean {
        if ((!duplicated_navBarWidth) && (value?.hasOwnProperty("navBarWidth"))) {
            return true
        }
        else if ((!duplicated_navBarPosition) && (value?.hasOwnProperty("navBarPosition"))) {
            return true
        }
        else if ((!duplicated_navBarWidthRange) && (value?.hasOwnProperty("navBarWidthRange"))) {
            return true
        }
        else if ((!duplicated_minContentWidth) && (value?.hasOwnProperty("minContentWidth"))) {
            return true
        }
        else if ((!duplicated_mode) && (value?.hasOwnProperty("mode"))) {
            return true
        }
        else if ((!duplicated_backButtonIcon) && (value?.hasOwnProperty("backButtonIcon"))) {
            return true
        }
        else if ((!duplicated_hideNavBar) && (value?.hasOwnProperty("hideNavBar"))) {
            return true
        }
        else if ((!duplicated_subTitle) && (value?.hasOwnProperty("subTitle"))) {
            return true
        }
        else if ((!duplicated_hideTitleBar) && (value?.hasOwnProperty("hideTitleBar"))) {
            return true
        }
        else if ((!duplicated_hideBackButton) && (value?.hasOwnProperty("hideBackButton"))) {
            return true
        }
        else if ((!duplicated_titleMode) && (value?.hasOwnProperty("titleMode"))) {
            return true
        }
        else if ((!duplicated_menus) && (value?.hasOwnProperty("menus"))) {
            return true
        }
        else if ((!duplicated_toolBar) && (value?.hasOwnProperty("toolBar"))) {
            return true
        }
        else if ((!duplicated_hideToolBar) && (value?.hasOwnProperty("hideToolBar"))) {
            return true
        }
        else if ((!duplicated_onTitleModeChange) && (value?.hasOwnProperty("onTitleModeChange"))) {
            return true
        }
        else if ((!duplicated_onNavBarStateChange) && (value?.hasOwnProperty("onNavBarStateChange"))) {
            return true
        }
        else if ((!duplicated_onNavigationModeChange) && (value?.hasOwnProperty("onNavigationModeChange"))) {
            return true
        }
        else if ((!duplicated_navDestination) && (value?.hasOwnProperty("navDestination"))) {
            return true
        }
        else if ((!duplicated_customNavContentTransition) && (value?.hasOwnProperty("customNavContentTransition"))) {
            return true
        }
        else if ((!duplicated_systemBarStyle) && (value?.hasOwnProperty("systemBarStyle"))) {
            return true
        }
        else if ((!duplicated_recoverable) && (value?.hasOwnProperty("recoverable"))) {
            return true
        }
        else if ((!duplicated_enableDragBar) && (value?.hasOwnProperty("enableDragBar"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof NavigationAttribute")
        }
    }
    static isNavigationCommonTitle(value: object|string|number|undefined|null|boolean, duplicated_main: boolean, duplicated_sub: boolean): boolean {
        if ((!duplicated_main) && (value?.hasOwnProperty("main"))) {
            return true
        }
        else if ((!duplicated_sub) && (value?.hasOwnProperty("sub"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof NavigationCommonTitle")
        }
    }
    static isNavigationCustomTitle(value: object|string|number|undefined|null|boolean, duplicated_builder: boolean, duplicated_height: boolean): boolean {
        if ((!duplicated_builder) && (value?.hasOwnProperty("builder"))) {
            return true
        }
        else if ((!duplicated_height) && (value?.hasOwnProperty("height"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof NavigationCustomTitle")
        }
    }
    static isNavigationInfo(value: object|string|number|undefined|null|boolean, duplicated__NavigationInfoStub: boolean): boolean {
        if ((!duplicated__NavigationInfoStub) && (value?.hasOwnProperty("_NavigationInfoStub"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof NavigationInfo")
        }
    }
    static isNavigationInterception(value: object|string|number|undefined|null|boolean, duplicated_willShow: boolean, duplicated_didShow: boolean, duplicated_modeChange: boolean): boolean {
        if ((!duplicated_willShow) && (value?.hasOwnProperty("willShow"))) {
            return true
        }
        else if ((!duplicated_didShow) && (value?.hasOwnProperty("didShow"))) {
            return true
        }
        else if ((!duplicated_modeChange) && (value?.hasOwnProperty("modeChange"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof NavigationInterception")
        }
    }
    static isNavigationInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof NavigationInterface")
    }
    static isNavigationMenuItem(value: object|string|number|undefined|null|boolean, duplicated_value: boolean, duplicated_icon: boolean, duplicated_symbolIcon: boolean, duplicated_isEnabled: boolean, duplicated_action: boolean): boolean {
        if ((!duplicated_value) && (value?.hasOwnProperty("value"))) {
            return true
        }
        else if ((!duplicated_icon) && (value?.hasOwnProperty("icon"))) {
            return true
        }
        else if ((!duplicated_symbolIcon) && (value?.hasOwnProperty("symbolIcon"))) {
            return true
        }
        else if ((!duplicated_isEnabled) && (value?.hasOwnProperty("isEnabled"))) {
            return true
        }
        else if ((!duplicated_action) && (value?.hasOwnProperty("action"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof NavigationMenuItem")
        }
    }
    static isNavigationMode(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (NavigationMode.Stack)) {
            return true
        }
        else if ((value) === (NavigationMode.Split)) {
            return true
        }
        else if ((value) === (NavigationMode.Auto)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof NavigationMode")
        }
    }
    static isNavigationOperation(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (NavigationOperation.PUSH)) {
            return true
        }
        else if ((value) === (NavigationOperation.POP)) {
            return true
        }
        else if ((value) === (NavigationOperation.REPLACE)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof NavigationOperation")
        }
    }
    static isNavigationOptions(value: object|string|number|undefined|null|boolean, duplicated_launchMode: boolean, duplicated_animated: boolean): boolean {
        if ((!duplicated_launchMode) && (value?.hasOwnProperty("launchMode"))) {
            return true
        }
        else if ((!duplicated_animated) && (value?.hasOwnProperty("animated"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof NavigationOptions")
        }
    }
    static isNavigationSystemTransitionType(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (NavigationSystemTransitionType.DEFAULT)) {
            return true
        }
        else if ((value) === (NavigationSystemTransitionType.NONE)) {
            return true
        }
        else if ((value) === (NavigationSystemTransitionType.TITLE)) {
            return true
        }
        else if ((value) === (NavigationSystemTransitionType.CONTENT)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof NavigationSystemTransitionType")
        }
    }
    static isNavigationTitleMode(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (NavigationTitleMode.Free)) {
            return true
        }
        else if ((value) === (NavigationTitleMode.Full)) {
            return true
        }
        else if ((value) === (NavigationTitleMode.Mini)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof NavigationTitleMode")
        }
    }
    static isNavigationTitleOptions(value: object|string|number|undefined|null|boolean, duplicated_backgroundColor: boolean, duplicated_backgroundBlurStyle: boolean, duplicated_barStyle: boolean, duplicated_paddingStart: boolean, duplicated_paddingEnd: boolean, duplicated_mainTitleModifier: boolean, duplicated_subTitleModifier: boolean, duplicated_enableHoverMode: boolean): boolean {
        if ((!duplicated_backgroundColor) && (value?.hasOwnProperty("backgroundColor"))) {
            return true
        }
        else if ((!duplicated_backgroundBlurStyle) && (value?.hasOwnProperty("backgroundBlurStyle"))) {
            return true
        }
        else if ((!duplicated_barStyle) && (value?.hasOwnProperty("barStyle"))) {
            return true
        }
        else if ((!duplicated_paddingStart) && (value?.hasOwnProperty("paddingStart"))) {
            return true
        }
        else if ((!duplicated_paddingEnd) && (value?.hasOwnProperty("paddingEnd"))) {
            return true
        }
        else if ((!duplicated_mainTitleModifier) && (value?.hasOwnProperty("mainTitleModifier"))) {
            return true
        }
        else if ((!duplicated_subTitleModifier) && (value?.hasOwnProperty("subTitleModifier"))) {
            return true
        }
        else if ((!duplicated_enableHoverMode) && (value?.hasOwnProperty("enableHoverMode"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof NavigationTitleOptions")
        }
    }
    static isNavigationToolbarOptions(value: object|string|number|undefined|null|boolean, duplicated_backgroundColor: boolean, duplicated_backgroundBlurStyle: boolean, duplicated_barStyle: boolean): boolean {
        if ((!duplicated_backgroundColor) && (value?.hasOwnProperty("backgroundColor"))) {
            return true
        }
        else if ((!duplicated_backgroundBlurStyle) && (value?.hasOwnProperty("backgroundBlurStyle"))) {
            return true
        }
        else if ((!duplicated_barStyle) && (value?.hasOwnProperty("barStyle"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof NavigationToolbarOptions")
        }
    }
    static isNavigationTransitionProxy(value: object|string|number|undefined|null|boolean, duplicated_from: boolean, duplicated_to: boolean, duplicated_isInteractive: boolean): boolean {
        if ((!duplicated_from) && (value?.hasOwnProperty("from"))) {
            return true
        }
        else if ((!duplicated_to) && (value?.hasOwnProperty("to"))) {
            return true
        }
        else if ((!duplicated_isInteractive) && (value?.hasOwnProperty("isInteractive"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof NavigationTransitionProxy")
        }
    }
    static isNavigationType(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (NavigationType.Push)) {
            return true
        }
        else if ((value) === (NavigationType.Back)) {
            return true
        }
        else if ((value) === (NavigationType.Replace)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof NavigationType")
        }
    }
    static isNavigatorAttribute(value: object|string|number|undefined|null|boolean, duplicated_active: boolean, duplicated_type: boolean, duplicated_target: boolean, duplicated_params: boolean): boolean {
        if ((!duplicated_active) && (value?.hasOwnProperty("active"))) {
            return true
        }
        else if ((!duplicated_type) && (value?.hasOwnProperty("type"))) {
            return true
        }
        else if ((!duplicated_target) && (value?.hasOwnProperty("target"))) {
            return true
        }
        else if ((!duplicated_params) && (value?.hasOwnProperty("params"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof NavigatorAttribute")
        }
    }
    static isNavigatorInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof NavigatorInterface")
    }
    static isNavPathInfo(value: object|string|number|undefined|null|boolean, duplicated_name: boolean, duplicated_param: boolean, duplicated_onPop: boolean, duplicated_isEntry: boolean): boolean {
        if ((!duplicated_name) && (value?.hasOwnProperty("name"))) {
            return true
        }
        else if ((!duplicated_param) && (value?.hasOwnProperty("param"))) {
            return true
        }
        else if ((!duplicated_onPop) && (value?.hasOwnProperty("onPop"))) {
            return true
        }
        else if ((!duplicated_isEntry) && (value?.hasOwnProperty("isEntry"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof NavPathInfo")
        }
    }
    static isNavPathStack(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof NavPathStack")
    }
    static isNavRouteMode(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (NavRouteMode.PUSH_WITH_RECREATE)) {
            return true
        }
        else if ((value) === (NavRouteMode.PUSH)) {
            return true
        }
        else if ((value) === (NavRouteMode.REPLACE)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof NavRouteMode")
        }
    }
    static isNavRouterAttribute(value: object|string|number|undefined|null|boolean, duplicated_onStateChange: boolean, duplicated_mode: boolean): boolean {
        if ((!duplicated_onStateChange) && (value?.hasOwnProperty("onStateChange"))) {
            return true
        }
        else if ((!duplicated_mode) && (value?.hasOwnProperty("mode"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof NavRouterAttribute")
        }
    }
    static isNavRouterInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof NavRouterInterface")
    }
    static isNestedScrollMode(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (NestedScrollMode.SELF_ONLY)) {
            return true
        }
        else if ((value) === (NestedScrollMode.SELF_FIRST)) {
            return true
        }
        else if ((value) === (NestedScrollMode.PARENT_FIRST)) {
            return true
        }
        else if ((value) === (NestedScrollMode.PARALLEL)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof NestedScrollMode")
        }
    }
    static isNestedScrollOptions(value: object|string|number|undefined|null|boolean, duplicated_scrollForward: boolean, duplicated_scrollBackward: boolean): boolean {
        if ((!duplicated_scrollForward) && (value?.hasOwnProperty("scrollForward"))) {
            return true
        }
        else if ((!duplicated_scrollBackward) && (value?.hasOwnProperty("scrollBackward"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof NestedScrollOptions")
        }
    }
    static isNestedScrollOptionsExt(value: object|string|number|undefined|null|boolean, duplicated_scrollUp: boolean, duplicated_scrollDown: boolean, duplicated_scrollRight: boolean, duplicated_scrollLeft: boolean): boolean {
        if ((!duplicated_scrollUp) && (value?.hasOwnProperty("scrollUp"))) {
            return true
        }
        else if ((!duplicated_scrollDown) && (value?.hasOwnProperty("scrollDown"))) {
            return true
        }
        else if ((!duplicated_scrollRight) && (value?.hasOwnProperty("scrollRight"))) {
            return true
        }
        else if ((!duplicated_scrollLeft) && (value?.hasOwnProperty("scrollLeft"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof NestedScrollOptionsExt")
        }
    }
    static isNodeContainerAttribute(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof NodeContainerAttribute")
    }
    static isNodeContainerInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof NodeContainerInterface")
    }
    static isNodeController(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof NodeController")
    }
    static isNonCurrentDayStyle(value: object|string|number|undefined|null|boolean, duplicated_nonCurrentMonthDayColor: boolean, duplicated_nonCurrentMonthLunarColor: boolean, duplicated_nonCurrentMonthWorkDayMarkColor: boolean, duplicated_nonCurrentMonthOffDayMarkColor: boolean): boolean {
        if ((!duplicated_nonCurrentMonthDayColor) && (value?.hasOwnProperty("nonCurrentMonthDayColor"))) {
            return true
        }
        else if ((!duplicated_nonCurrentMonthLunarColor) && (value?.hasOwnProperty("nonCurrentMonthLunarColor"))) {
            return true
        }
        else if ((!duplicated_nonCurrentMonthWorkDayMarkColor) && (value?.hasOwnProperty("nonCurrentMonthWorkDayMarkColor"))) {
            return true
        }
        else if ((!duplicated_nonCurrentMonthOffDayMarkColor) && (value?.hasOwnProperty("nonCurrentMonthOffDayMarkColor"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof NonCurrentDayStyle")
        }
    }
    static isObscuredReasons(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (ObscuredReasons.PLACEHOLDER)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ObscuredReasons")
        }
    }
    static isOffscreenCanvas(value: object|string|number|undefined|null|boolean, duplicated_height: boolean, duplicated_width: boolean): boolean {
        if ((!duplicated_height) && (value?.hasOwnProperty("height"))) {
            return true
        }
        else if ((!duplicated_width) && (value?.hasOwnProperty("width"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof OffscreenCanvas")
        }
    }
    static isOffscreenCanvasRenderingContext2D(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof OffscreenCanvasRenderingContext2D")
    }
    static isOffset(value: object|string|number|undefined|null|boolean, duplicated_dx: boolean, duplicated_dy: boolean): boolean {
        if ((!duplicated_dx) && (value?.hasOwnProperty("dx"))) {
            return true
        }
        else if ((!duplicated_dy) && (value?.hasOwnProperty("dy"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof Offset")
        }
    }
    static isOffsetOptions(value: object|string|number|undefined|null|boolean, duplicated_xOffset: boolean, duplicated_yOffset: boolean): boolean {
        if ((!duplicated_xOffset) && (value?.hasOwnProperty("xOffset"))) {
            return true
        }
        else if ((!duplicated_yOffset) && (value?.hasOwnProperty("yOffset"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof OffsetOptions")
        }
    }
    static isOffsetResult(value: object|string|number|undefined|null|boolean, duplicated_xOffset: boolean, duplicated_yOffset: boolean): boolean {
        if ((!duplicated_xOffset) && (value?.hasOwnProperty("xOffset"))) {
            return true
        }
        else if ((!duplicated_yOffset) && (value?.hasOwnProperty("yOffset"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof OffsetResult")
        }
    }
    static isOnAlertEvent(value: object|string|number|undefined|null|boolean, duplicated_url: boolean, duplicated_message: boolean, duplicated_result: boolean): boolean {
        if ((!duplicated_url) && (value?.hasOwnProperty("url"))) {
            return true
        }
        else if ((!duplicated_message) && (value?.hasOwnProperty("message"))) {
            return true
        }
        else if ((!duplicated_result) && (value?.hasOwnProperty("result"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof OnAlertEvent")
        }
    }
    static isOnAudioStateChangedEvent(value: object|string|number|undefined|null|boolean, duplicated_playing: boolean): boolean {
        if ((!duplicated_playing) && (value?.hasOwnProperty("playing"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof OnAudioStateChangedEvent")
        }
    }
    static isOnBeforeUnloadEvent(value: object|string|number|undefined|null|boolean, duplicated_url: boolean, duplicated_message: boolean, duplicated_result: boolean): boolean {
        if ((!duplicated_url) && (value?.hasOwnProperty("url"))) {
            return true
        }
        else if ((!duplicated_message) && (value?.hasOwnProperty("message"))) {
            return true
        }
        else if ((!duplicated_result) && (value?.hasOwnProperty("result"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof OnBeforeUnloadEvent")
        }
    }
    static isOnClientAuthenticationEvent(value: object|string|number|undefined|null|boolean, duplicated_handler: boolean, duplicated_host: boolean, duplicated_port: boolean, duplicated_keyTypes: boolean, duplicated_issuers: boolean): boolean {
        if ((!duplicated_handler) && (value?.hasOwnProperty("handler"))) {
            return true
        }
        else if ((!duplicated_host) && (value?.hasOwnProperty("host"))) {
            return true
        }
        else if ((!duplicated_port) && (value?.hasOwnProperty("port"))) {
            return true
        }
        else if ((!duplicated_keyTypes) && (value?.hasOwnProperty("keyTypes"))) {
            return true
        }
        else if ((!duplicated_issuers) && (value?.hasOwnProperty("issuers"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof OnClientAuthenticationEvent")
        }
    }
    static isOnConfirmEvent(value: object|string|number|undefined|null|boolean, duplicated_url: boolean, duplicated_message: boolean, duplicated_result: boolean): boolean {
        if ((!duplicated_url) && (value?.hasOwnProperty("url"))) {
            return true
        }
        else if ((!duplicated_message) && (value?.hasOwnProperty("message"))) {
            return true
        }
        else if ((!duplicated_result) && (value?.hasOwnProperty("result"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof OnConfirmEvent")
        }
    }
    static isOnConsoleEvent(value: object|string|number|undefined|null|boolean, duplicated_message: boolean): boolean {
        if ((!duplicated_message) && (value?.hasOwnProperty("message"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof OnConsoleEvent")
        }
    }
    static isOnContextMenuShowEvent(value: object|string|number|undefined|null|boolean, duplicated_param: boolean, duplicated_result: boolean): boolean {
        if ((!duplicated_param) && (value?.hasOwnProperty("param"))) {
            return true
        }
        else if ((!duplicated_result) && (value?.hasOwnProperty("result"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof OnContextMenuShowEvent")
        }
    }
    static isOnDataResubmittedEvent(value: object|string|number|undefined|null|boolean, duplicated_handler: boolean): boolean {
        if ((!duplicated_handler) && (value?.hasOwnProperty("handler"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof OnDataResubmittedEvent")
        }
    }
    static isOnDownloadStartEvent(value: object|string|number|undefined|null|boolean, duplicated_url: boolean, duplicated_userAgent: boolean, duplicated_contentDisposition: boolean, duplicated_mimetype: boolean, duplicated_contentLength: boolean): boolean {
        if ((!duplicated_url) && (value?.hasOwnProperty("url"))) {
            return true
        }
        else if ((!duplicated_userAgent) && (value?.hasOwnProperty("userAgent"))) {
            return true
        }
        else if ((!duplicated_contentDisposition) && (value?.hasOwnProperty("contentDisposition"))) {
            return true
        }
        else if ((!duplicated_mimetype) && (value?.hasOwnProperty("mimetype"))) {
            return true
        }
        else if ((!duplicated_contentLength) && (value?.hasOwnProperty("contentLength"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof OnDownloadStartEvent")
        }
    }
    static isOnErrorReceiveEvent(value: object|string|number|undefined|null|boolean, duplicated_request: boolean, duplicated_error: boolean): boolean {
        if ((!duplicated_request) && (value?.hasOwnProperty("request"))) {
            return true
        }
        else if ((!duplicated_error) && (value?.hasOwnProperty("error"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof OnErrorReceiveEvent")
        }
    }
    static isOnFaviconReceivedEvent(value: object|string|number|undefined|null|boolean, duplicated_favicon: boolean): boolean {
        if ((!duplicated_favicon) && (value?.hasOwnProperty("favicon"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof OnFaviconReceivedEvent")
        }
    }
    static isOnFirstContentfulPaintEvent(value: object|string|number|undefined|null|boolean, duplicated_navigationStartTick: boolean, duplicated_firstContentfulPaintMs: boolean): boolean {
        if ((!duplicated_navigationStartTick) && (value?.hasOwnProperty("navigationStartTick"))) {
            return true
        }
        else if ((!duplicated_firstContentfulPaintMs) && (value?.hasOwnProperty("firstContentfulPaintMs"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof OnFirstContentfulPaintEvent")
        }
    }
    static isOnFoldStatusChangeInfo(value: object|string|number|undefined|null|boolean, duplicated_foldStatus: boolean): boolean {
        if ((!duplicated_foldStatus) && (value?.hasOwnProperty("foldStatus"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof OnFoldStatusChangeInfo")
        }
    }
    static isOnGeolocationShowEvent(value: object|string|number|undefined|null|boolean, duplicated_origin: boolean, duplicated_geolocation: boolean): boolean {
        if ((!duplicated_origin) && (value?.hasOwnProperty("origin"))) {
            return true
        }
        else if ((!duplicated_geolocation) && (value?.hasOwnProperty("geolocation"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof OnGeolocationShowEvent")
        }
    }
    static isOnHttpAuthRequestEvent(value: object|string|number|undefined|null|boolean, duplicated_handler: boolean, duplicated_host: boolean, duplicated_realm: boolean): boolean {
        if ((!duplicated_handler) && (value?.hasOwnProperty("handler"))) {
            return true
        }
        else if ((!duplicated_host) && (value?.hasOwnProperty("host"))) {
            return true
        }
        else if ((!duplicated_realm) && (value?.hasOwnProperty("realm"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof OnHttpAuthRequestEvent")
        }
    }
    static isOnHttpErrorReceiveEvent(value: object|string|number|undefined|null|boolean, duplicated_request: boolean, duplicated_response: boolean): boolean {
        if ((!duplicated_request) && (value?.hasOwnProperty("request"))) {
            return true
        }
        else if ((!duplicated_response) && (value?.hasOwnProperty("response"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof OnHttpErrorReceiveEvent")
        }
    }
    static isOnInterceptRequestEvent(value: object|string|number|undefined|null|boolean, duplicated_request: boolean): boolean {
        if ((!duplicated_request) && (value?.hasOwnProperty("request"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof OnInterceptRequestEvent")
        }
    }
    static isOnLoadInterceptEvent(value: object|string|number|undefined|null|boolean, duplicated_data: boolean): boolean {
        if ((!duplicated_data) && (value?.hasOwnProperty("data"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof OnLoadInterceptEvent")
        }
    }
    static isOnOverScrollEvent(value: object|string|number|undefined|null|boolean, duplicated_xOffset: boolean, duplicated_yOffset: boolean): boolean {
        if ((!duplicated_xOffset) && (value?.hasOwnProperty("xOffset"))) {
            return true
        }
        else if ((!duplicated_yOffset) && (value?.hasOwnProperty("yOffset"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof OnOverScrollEvent")
        }
    }
    static isOnPageBeginEvent(value: object|string|number|undefined|null|boolean, duplicated_url: boolean): boolean {
        if ((!duplicated_url) && (value?.hasOwnProperty("url"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof OnPageBeginEvent")
        }
    }
    static isOnPageEndEvent(value: object|string|number|undefined|null|boolean, duplicated_url: boolean): boolean {
        if ((!duplicated_url) && (value?.hasOwnProperty("url"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof OnPageEndEvent")
        }
    }
    static isOnPageVisibleEvent(value: object|string|number|undefined|null|boolean, duplicated_url: boolean): boolean {
        if ((!duplicated_url) && (value?.hasOwnProperty("url"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof OnPageVisibleEvent")
        }
    }
    static isOnPermissionRequestEvent(value: object|string|number|undefined|null|boolean, duplicated_request: boolean): boolean {
        if ((!duplicated_request) && (value?.hasOwnProperty("request"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof OnPermissionRequestEvent")
        }
    }
    static isOnProgressChangeEvent(value: object|string|number|undefined|null|boolean, duplicated_newProgress: boolean): boolean {
        if ((!duplicated_newProgress) && (value?.hasOwnProperty("newProgress"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof OnProgressChangeEvent")
        }
    }
    static isOnPromptEvent(value: object|string|number|undefined|null|boolean, duplicated_url: boolean, duplicated_message: boolean, duplicated_value: boolean, duplicated_result: boolean): boolean {
        if ((!duplicated_url) && (value?.hasOwnProperty("url"))) {
            return true
        }
        else if ((!duplicated_message) && (value?.hasOwnProperty("message"))) {
            return true
        }
        else if ((!duplicated_value) && (value?.hasOwnProperty("value"))) {
            return true
        }
        else if ((!duplicated_result) && (value?.hasOwnProperty("result"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof OnPromptEvent")
        }
    }
    static isOnRefreshAccessedHistoryEvent(value: object|string|number|undefined|null|boolean, duplicated_url: boolean, duplicated_isRefreshed: boolean): boolean {
        if ((!duplicated_url) && (value?.hasOwnProperty("url"))) {
            return true
        }
        else if ((!duplicated_isRefreshed) && (value?.hasOwnProperty("isRefreshed"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof OnRefreshAccessedHistoryEvent")
        }
    }
    static isOnRenderExitedEvent(value: object|string|number|undefined|null|boolean, duplicated_renderExitReason: boolean): boolean {
        if ((!duplicated_renderExitReason) && (value?.hasOwnProperty("renderExitReason"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof OnRenderExitedEvent")
        }
    }
    static isOnResourceLoadEvent(value: object|string|number|undefined|null|boolean, duplicated_url: boolean): boolean {
        if ((!duplicated_url) && (value?.hasOwnProperty("url"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof OnResourceLoadEvent")
        }
    }
    static isOnScaleChangeEvent(value: object|string|number|undefined|null|boolean, duplicated_oldScale: boolean, duplicated_newScale: boolean): boolean {
        if ((!duplicated_oldScale) && (value?.hasOwnProperty("oldScale"))) {
            return true
        }
        else if ((!duplicated_newScale) && (value?.hasOwnProperty("newScale"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof OnScaleChangeEvent")
        }
    }
    static isOnScreenCaptureRequestEvent(value: object|string|number|undefined|null|boolean, duplicated_handler: boolean): boolean {
        if ((!duplicated_handler) && (value?.hasOwnProperty("handler"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof OnScreenCaptureRequestEvent")
        }
    }
    static isOnScrollEvent(value: object|string|number|undefined|null|boolean, duplicated_xOffset: boolean, duplicated_yOffset: boolean): boolean {
        if ((!duplicated_xOffset) && (value?.hasOwnProperty("xOffset"))) {
            return true
        }
        else if ((!duplicated_yOffset) && (value?.hasOwnProperty("yOffset"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof OnScrollEvent")
        }
    }
    static isOnScrollFrameBeginHandlerResult(value: object|string|number|undefined|null|boolean, duplicated_offsetRemain: boolean): boolean {
        if ((!duplicated_offsetRemain) && (value?.hasOwnProperty("offsetRemain"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof OnScrollFrameBeginHandlerResult")
        }
    }
    static isOnSearchResultReceiveEvent(value: object|string|number|undefined|null|boolean, duplicated_activeMatchOrdinal: boolean, duplicated_numberOfMatches: boolean, duplicated_isDoneCounting: boolean): boolean {
        if ((!duplicated_activeMatchOrdinal) && (value?.hasOwnProperty("activeMatchOrdinal"))) {
            return true
        }
        else if ((!duplicated_numberOfMatches) && (value?.hasOwnProperty("numberOfMatches"))) {
            return true
        }
        else if ((!duplicated_isDoneCounting) && (value?.hasOwnProperty("isDoneCounting"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof OnSearchResultReceiveEvent")
        }
    }
    static isOnShowFileSelectorEvent(value: object|string|number|undefined|null|boolean, duplicated_result: boolean, duplicated_fileSelector: boolean): boolean {
        if ((!duplicated_result) && (value?.hasOwnProperty("result"))) {
            return true
        }
        else if ((!duplicated_fileSelector) && (value?.hasOwnProperty("fileSelector"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof OnShowFileSelectorEvent")
        }
    }
    static isOnSslErrorEventReceiveEvent(value: object|string|number|undefined|null|boolean, duplicated_handler: boolean, duplicated_error: boolean, duplicated_certChainData: boolean): boolean {
        if ((!duplicated_handler) && (value?.hasOwnProperty("handler"))) {
            return true
        }
        else if ((!duplicated_error) && (value?.hasOwnProperty("error"))) {
            return true
        }
        else if ((!duplicated_certChainData) && (value?.hasOwnProperty("certChainData"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof OnSslErrorEventReceiveEvent")
        }
    }
    static isOnTitleReceiveEvent(value: object|string|number|undefined|null|boolean, duplicated_title: boolean): boolean {
        if ((!duplicated_title) && (value?.hasOwnProperty("title"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof OnTitleReceiveEvent")
        }
    }
    static isOnTouchIconUrlReceivedEvent(value: object|string|number|undefined|null|boolean, duplicated_url: boolean, duplicated_precomposed: boolean): boolean {
        if ((!duplicated_url) && (value?.hasOwnProperty("url"))) {
            return true
        }
        else if ((!duplicated_precomposed) && (value?.hasOwnProperty("precomposed"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof OnTouchIconUrlReceivedEvent")
        }
    }
    static isOnWindowNewEvent(value: object|string|number|undefined|null|boolean, duplicated_isAlert: boolean, duplicated_isUserTrigger: boolean, duplicated_targetUrl: boolean, duplicated_handler: boolean): boolean {
        if ((!duplicated_isAlert) && (value?.hasOwnProperty("isAlert"))) {
            return true
        }
        else if ((!duplicated_isUserTrigger) && (value?.hasOwnProperty("isUserTrigger"))) {
            return true
        }
        else if ((!duplicated_targetUrl) && (value?.hasOwnProperty("targetUrl"))) {
            return true
        }
        else if ((!duplicated_handler) && (value?.hasOwnProperty("handler"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof OnWindowNewEvent")
        }
    }
    static isOptionWidthMode(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (OptionWidthMode.FIT_CONTENT)) {
            return true
        }
        else if ((value) === (OptionWidthMode.FIT_TRIGGER)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof OptionWidthMode")
        }
    }
    static isOutlineOptions(value: object|string|number|undefined|null|boolean, duplicated_width: boolean, duplicated_color: boolean, duplicated_radius: boolean, duplicated_style: boolean): boolean {
        if ((!duplicated_width) && (value?.hasOwnProperty("width"))) {
            return true
        }
        else if ((!duplicated_color) && (value?.hasOwnProperty("color"))) {
            return true
        }
        else if ((!duplicated_radius) && (value?.hasOwnProperty("radius"))) {
            return true
        }
        else if ((!duplicated_style) && (value?.hasOwnProperty("style"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof OutlineOptions")
        }
    }
    static isOutlineRadiuses(value: object|string|number|undefined|null|boolean, duplicated_topLeft: boolean, duplicated_topRight: boolean, duplicated_bottomLeft: boolean, duplicated_bottomRight: boolean): boolean {
        if ((!duplicated_topLeft) && (value?.hasOwnProperty("topLeft"))) {
            return true
        }
        else if ((!duplicated_topRight) && (value?.hasOwnProperty("topRight"))) {
            return true
        }
        else if ((!duplicated_bottomLeft) && (value?.hasOwnProperty("bottomLeft"))) {
            return true
        }
        else if ((!duplicated_bottomRight) && (value?.hasOwnProperty("bottomRight"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof OutlineRadiuses")
        }
    }
    static isOutlineStyle(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (OutlineStyle.SOLID)) {
            return true
        }
        else if ((value) === (OutlineStyle.DASHED)) {
            return true
        }
        else if ((value) === (OutlineStyle.DOTTED)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof OutlineStyle")
        }
    }
    static isOverlayOffset(value: object|string|number|undefined|null|boolean, duplicated_x: boolean, duplicated_y: boolean): boolean {
        if ((!duplicated_x) && (value?.hasOwnProperty("x"))) {
            return true
        }
        else if ((!duplicated_y) && (value?.hasOwnProperty("y"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof OverlayOffset")
        }
    }
    static isOverlayOptions(value: object|string|number|undefined|null|boolean, duplicated_align: boolean, duplicated_offset: boolean): boolean {
        if ((!duplicated_align) && (value?.hasOwnProperty("align"))) {
            return true
        }
        else if ((!duplicated_offset) && (value?.hasOwnProperty("offset"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof OverlayOptions")
        }
    }
    static isOverScrollMode(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (OverScrollMode.NEVER)) {
            return true
        }
        else if ((value) === (OverScrollMode.ALWAYS)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof OverScrollMode")
        }
    }
    static isPadding(value: object|string|number|undefined|null|boolean, duplicated_top: boolean, duplicated_right: boolean, duplicated_bottom: boolean, duplicated_left: boolean): boolean {
        if ((!duplicated_top) && (value?.hasOwnProperty("top"))) {
            return true
        }
        else if ((!duplicated_right) && (value?.hasOwnProperty("right"))) {
            return true
        }
        else if ((!duplicated_bottom) && (value?.hasOwnProperty("bottom"))) {
            return true
        }
        else if ((!duplicated_left) && (value?.hasOwnProperty("left"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof Padding")
        }
    }
    static isPageTransitionEnterInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof PageTransitionEnterInterface")
    }
    static isPageTransitionExitInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof PageTransitionExitInterface")
    }
    static isPageTransitionOptions(value: object|string|number|undefined|null|boolean, duplicated_type: boolean, duplicated_duration: boolean, duplicated_curve: boolean, duplicated_delay: boolean): boolean {
        if ((!duplicated_type) && (value?.hasOwnProperty("type"))) {
            return true
        }
        else if ((!duplicated_duration) && (value?.hasOwnProperty("duration"))) {
            return true
        }
        else if ((!duplicated_curve) && (value?.hasOwnProperty("curve"))) {
            return true
        }
        else if ((!duplicated_delay) && (value?.hasOwnProperty("delay"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof PageTransitionOptions")
        }
    }
    static isPanDirection(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (PanDirection.None)) {
            return true
        }
        else if ((value) === (PanDirection.Horizontal)) {
            return true
        }
        else if ((value) === (PanDirection.Left)) {
            return true
        }
        else if ((value) === (PanDirection.Right)) {
            return true
        }
        else if ((value) === (PanDirection.Vertical)) {
            return true
        }
        else if ((value) === (PanDirection.Up)) {
            return true
        }
        else if ((value) === (PanDirection.Down)) {
            return true
        }
        else if ((value) === (PanDirection.All)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof PanDirection")
        }
    }
    static isPanelAttribute(value: object|string|number|undefined|null|boolean, duplicated_mode: boolean, duplicated_type: boolean, duplicated_dragBar: boolean, duplicated_customHeight: boolean, duplicated_fullHeight: boolean, duplicated_halfHeight: boolean, duplicated_miniHeight: boolean, duplicated_show: boolean, duplicated_backgroundMask: boolean, duplicated_showCloseIcon: boolean, duplicated_onChange: boolean, duplicated_onHeightChange: boolean): boolean {
        if ((!duplicated_mode) && (value?.hasOwnProperty("mode"))) {
            return true
        }
        else if ((!duplicated_type) && (value?.hasOwnProperty("type"))) {
            return true
        }
        else if ((!duplicated_dragBar) && (value?.hasOwnProperty("dragBar"))) {
            return true
        }
        else if ((!duplicated_customHeight) && (value?.hasOwnProperty("customHeight"))) {
            return true
        }
        else if ((!duplicated_fullHeight) && (value?.hasOwnProperty("fullHeight"))) {
            return true
        }
        else if ((!duplicated_halfHeight) && (value?.hasOwnProperty("halfHeight"))) {
            return true
        }
        else if ((!duplicated_miniHeight) && (value?.hasOwnProperty("miniHeight"))) {
            return true
        }
        else if ((!duplicated_show) && (value?.hasOwnProperty("show"))) {
            return true
        }
        else if ((!duplicated_backgroundMask) && (value?.hasOwnProperty("backgroundMask"))) {
            return true
        }
        else if ((!duplicated_showCloseIcon) && (value?.hasOwnProperty("showCloseIcon"))) {
            return true
        }
        else if ((!duplicated_onChange) && (value?.hasOwnProperty("onChange"))) {
            return true
        }
        else if ((!duplicated_onHeightChange) && (value?.hasOwnProperty("onHeightChange"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof PanelAttribute")
        }
    }
    static isPanelHeight(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (PanelHeight.WRAP_CONTENT)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof PanelHeight")
        }
    }
    static isPanelInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof PanelInterface")
    }
    static isPanelMode(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (PanelMode.Mini)) {
            return true
        }
        else if ((value) === (PanelMode.Half)) {
            return true
        }
        else if ((value) === (PanelMode.Full)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof PanelMode")
        }
    }
    static isPanelType(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (PanelType.Minibar)) {
            return true
        }
        else if ((value) === (PanelType.Foldable)) {
            return true
        }
        else if ((value) === (PanelType.Temporary)) {
            return true
        }
        else if ((value) === (PanelType.CUSTOM)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof PanelType")
        }
    }
    static isPanGestureEvent(value: object|string|number|undefined|null|boolean, duplicated_offsetX: boolean, duplicated_offsetY: boolean, duplicated_velocityX: boolean, duplicated_velocityY: boolean, duplicated_velocity: boolean): boolean {
        if ((!duplicated_offsetX) && (value?.hasOwnProperty("offsetX"))) {
            return true
        }
        else if ((!duplicated_offsetY) && (value?.hasOwnProperty("offsetY"))) {
            return true
        }
        else if ((!duplicated_velocityX) && (value?.hasOwnProperty("velocityX"))) {
            return true
        }
        else if ((!duplicated_velocityY) && (value?.hasOwnProperty("velocityY"))) {
            return true
        }
        else if ((!duplicated_velocity) && (value?.hasOwnProperty("velocity"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof PanGestureEvent")
        }
    }
    static isPanGestureHandler(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof PanGestureHandler")
    }
    static isPanGestureHandlerOptions(value: object|string|number|undefined|null|boolean, duplicated_fingers: boolean, duplicated_direction: boolean, duplicated_distance: boolean): boolean {
        if ((!duplicated_fingers) && (value?.hasOwnProperty("fingers"))) {
            return true
        }
        else if ((!duplicated_direction) && (value?.hasOwnProperty("direction"))) {
            return true
        }
        else if ((!duplicated_distance) && (value?.hasOwnProperty("distance"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof PanGestureHandlerOptions")
        }
    }
    static isPanGestureInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof PanGestureInterface")
    }
    static isPanGestureOptions(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof PanGestureOptions")
    }
    static isPanRecognizer(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof PanRecognizer")
    }
    static isParagraphStyle(value: object|string|number|undefined|null|boolean, duplicated_textAlign: boolean, duplicated_textIndent: boolean, duplicated_maxLines: boolean, duplicated_overflow: boolean, duplicated_wordBreak: boolean, duplicated_leadingMargin: boolean): boolean {
        if ((!duplicated_textAlign) && (value?.hasOwnProperty("textAlign"))) {
            return true
        }
        else if ((!duplicated_textIndent) && (value?.hasOwnProperty("textIndent"))) {
            return true
        }
        else if ((!duplicated_maxLines) && (value?.hasOwnProperty("maxLines"))) {
            return true
        }
        else if ((!duplicated_overflow) && (value?.hasOwnProperty("overflow"))) {
            return true
        }
        else if ((!duplicated_wordBreak) && (value?.hasOwnProperty("wordBreak"))) {
            return true
        }
        else if ((!duplicated_leadingMargin) && (value?.hasOwnProperty("leadingMargin"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ParagraphStyle")
        }
    }
    static isParagraphStyleInterface(value: object|string|number|undefined|null|boolean, duplicated_textAlign: boolean, duplicated_textIndent: boolean, duplicated_maxLines: boolean, duplicated_overflow: boolean, duplicated_wordBreak: boolean, duplicated_leadingMargin: boolean): boolean {
        if ((!duplicated_textAlign) && (value?.hasOwnProperty("textAlign"))) {
            return true
        }
        else if ((!duplicated_textIndent) && (value?.hasOwnProperty("textIndent"))) {
            return true
        }
        else if ((!duplicated_maxLines) && (value?.hasOwnProperty("maxLines"))) {
            return true
        }
        else if ((!duplicated_overflow) && (value?.hasOwnProperty("overflow"))) {
            return true
        }
        else if ((!duplicated_wordBreak) && (value?.hasOwnProperty("wordBreak"))) {
            return true
        }
        else if ((!duplicated_leadingMargin) && (value?.hasOwnProperty("leadingMargin"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ParagraphStyleInterface")
        }
    }
    static isParticleColorOptions(value: object|string|number|undefined|null|boolean, duplicated_r: boolean, duplicated_g: boolean, duplicated_b: boolean, duplicated_a: boolean): boolean {
        if ((!duplicated_r) && (value?.hasOwnProperty("r"))) {
            return true
        }
        else if ((!duplicated_g) && (value?.hasOwnProperty("g"))) {
            return true
        }
        else if ((!duplicated_b) && (value?.hasOwnProperty("b"))) {
            return true
        }
        else if ((!duplicated_a) && (value?.hasOwnProperty("a"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ParticleColorOptions")
        }
    }
    static isParticleColorPropertyUpdaterConfigs(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof ParticleColorPropertyUpdaterConfigs")
    }
    static isParticleColorUpdaterOptions(value: object|string|number|undefined|null|boolean, duplicated_type: boolean, duplicated_config: boolean): boolean {
        if ((!duplicated_type) && (value?.hasOwnProperty("type"))) {
            return true
        }
        else if ((!duplicated_config) && (value?.hasOwnProperty("config"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ParticleColorUpdaterOptions")
        }
    }
    static isParticleConfigs(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof ParticleConfigs")
    }
    static isParticleEmitterShape(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (ParticleEmitterShape.RECTANGLE)) {
            return true
        }
        else if ((value) === (ParticleEmitterShape.CIRCLE)) {
            return true
        }
        else if ((value) === (ParticleEmitterShape.ELLIPSE)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ParticleEmitterShape")
        }
    }
    static isParticlePropertyAnimation(value: object|string|number|undefined|null|boolean, duplicated_from: boolean, duplicated_to: boolean, duplicated_startMillis: boolean, duplicated_endMillis: boolean, duplicated_curve: boolean): boolean {
        if ((!duplicated_from) && (value?.hasOwnProperty("from"))) {
            return true
        }
        else if ((!duplicated_to) && (value?.hasOwnProperty("to"))) {
            return true
        }
        else if ((!duplicated_startMillis) && (value?.hasOwnProperty("startMillis"))) {
            return true
        }
        else if ((!duplicated_endMillis) && (value?.hasOwnProperty("endMillis"))) {
            return true
        }
        else if ((!duplicated_curve) && (value?.hasOwnProperty("curve"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ParticlePropertyAnimation")
        }
    }
    static isParticlePropertyUpdaterConfigs(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof ParticlePropertyUpdaterConfigs")
    }
    static isParticleType(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (ParticleType.POINT)) {
            return true
        }
        else if ((value) === (ParticleType.IMAGE)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ParticleType")
        }
    }
    static isParticleUpdater(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (ParticleUpdater.NONE)) {
            return true
        }
        else if ((value) === (ParticleUpdater.RANDOM)) {
            return true
        }
        else if ((value) === (ParticleUpdater.CURVE)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ParticleUpdater")
        }
    }
    static isParticleUpdaterOptions(value: object|string|number|undefined|null|boolean, duplicated_type: boolean, duplicated_config: boolean): boolean {
        if ((!duplicated_type) && (value?.hasOwnProperty("type"))) {
            return true
        }
        else if ((!duplicated_config) && (value?.hasOwnProperty("config"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ParticleUpdaterOptions")
        }
    }
    static isPasswordIcon(value: object|string|number|undefined|null|boolean, duplicated_onIconSrc: boolean, duplicated_offIconSrc: boolean): boolean {
        if ((!duplicated_onIconSrc) && (value?.hasOwnProperty("onIconSrc"))) {
            return true
        }
        else if ((!duplicated_offIconSrc) && (value?.hasOwnProperty("offIconSrc"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof PasswordIcon")
        }
    }
    static isPasteButtonAttribute(value: object|string|number|undefined|null|boolean, duplicated_onClick: boolean): boolean {
        if ((!duplicated_onClick) && (value?.hasOwnProperty("onClick"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof PasteButtonAttribute")
        }
    }
    static isPasteButtonInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof PasteButtonInterface")
    }
    static isPasteButtonOnClickResult(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (PasteButtonOnClickResult.SUCCESS)) {
            return true
        }
        else if ((value) === (PasteButtonOnClickResult.TEMPORARY_AUTHORIZATION_FAILED)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof PasteButtonOnClickResult")
        }
    }
    static isPasteButtonOptions(value: object|string|number|undefined|null|boolean, duplicated_icon: boolean, duplicated_text: boolean, duplicated_buttonType: boolean): boolean {
        if ((!duplicated_icon) && (value?.hasOwnProperty("icon"))) {
            return true
        }
        else if ((!duplicated_text) && (value?.hasOwnProperty("text"))) {
            return true
        }
        else if ((!duplicated_buttonType) && (value?.hasOwnProperty("buttonType"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof PasteButtonOptions")
        }
    }
    static isPasteDescription(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (PasteDescription.PASTE)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof PasteDescription")
        }
    }
    static isPasteEvent(value: object|string|number|undefined|null|boolean, duplicated_preventDefault: boolean): boolean {
        if ((!duplicated_preventDefault) && (value?.hasOwnProperty("preventDefault"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof PasteEvent")
        }
    }
    static isPasteIconStyle(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (PasteIconStyle.LINES)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof PasteIconStyle")
        }
    }
    static isPath2D(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof Path2D")
    }
    static isPathAttribute(value: object|string|number|undefined|null|boolean, duplicated_commands: boolean): boolean {
        if ((!duplicated_commands) && (value?.hasOwnProperty("commands"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof PathAttribute")
        }
    }
    static isPathInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof PathInterface")
    }
    static isPathOptions(value: object|string|number|undefined|null|boolean, duplicated_width: boolean, duplicated_height: boolean, duplicated_commands: boolean): boolean {
        if ((!duplicated_width) && (value?.hasOwnProperty("width"))) {
            return true
        }
        else if ((!duplicated_height) && (value?.hasOwnProperty("height"))) {
            return true
        }
        else if ((!duplicated_commands) && (value?.hasOwnProperty("commands"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof PathOptions")
        }
    }
    static isPathShape(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof PathShape")
    }
    static isPathShapeOptions(value: object|string|number|undefined|null|boolean, duplicated_commands: boolean): boolean {
        if ((!duplicated_commands) && (value?.hasOwnProperty("commands"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof PathShapeOptions")
        }
    }
    static isPatternLockAttribute(value: object|string|number|undefined|null|boolean, duplicated_sideLength: boolean, duplicated_circleRadius: boolean, duplicated_backgroundColor: boolean, duplicated_regularColor: boolean, duplicated_selectedColor: boolean, duplicated_activeColor: boolean, duplicated_pathColor: boolean, duplicated_pathStrokeWidth: boolean, duplicated_onPatternComplete: boolean, duplicated_autoReset: boolean, duplicated_onDotConnect: boolean, duplicated_activateCircleStyle: boolean): boolean {
        if ((!duplicated_sideLength) && (value?.hasOwnProperty("sideLength"))) {
            return true
        }
        else if ((!duplicated_circleRadius) && (value?.hasOwnProperty("circleRadius"))) {
            return true
        }
        else if ((!duplicated_backgroundColor) && (value?.hasOwnProperty("backgroundColor"))) {
            return true
        }
        else if ((!duplicated_regularColor) && (value?.hasOwnProperty("regularColor"))) {
            return true
        }
        else if ((!duplicated_selectedColor) && (value?.hasOwnProperty("selectedColor"))) {
            return true
        }
        else if ((!duplicated_activeColor) && (value?.hasOwnProperty("activeColor"))) {
            return true
        }
        else if ((!duplicated_pathColor) && (value?.hasOwnProperty("pathColor"))) {
            return true
        }
        else if ((!duplicated_pathStrokeWidth) && (value?.hasOwnProperty("pathStrokeWidth"))) {
            return true
        }
        else if ((!duplicated_onPatternComplete) && (value?.hasOwnProperty("onPatternComplete"))) {
            return true
        }
        else if ((!duplicated_autoReset) && (value?.hasOwnProperty("autoReset"))) {
            return true
        }
        else if ((!duplicated_onDotConnect) && (value?.hasOwnProperty("onDotConnect"))) {
            return true
        }
        else if ((!duplicated_activateCircleStyle) && (value?.hasOwnProperty("activateCircleStyle"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof PatternLockAttribute")
        }
    }
    static isPatternLockChallengeResult(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (PatternLockChallengeResult.CORRECT)) {
            return true
        }
        else if ((value) === (PatternLockChallengeResult.WRONG)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof PatternLockChallengeResult")
        }
    }
    static isPatternLockController(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof PatternLockController")
    }
    static isPatternLockInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof PatternLockInterface")
    }
    static isPerfMonitorActionType(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (PerfMonitorActionType.LAST_DOWN)) {
            return true
        }
        else if ((value) === (PerfMonitorActionType.LAST_UP)) {
            return true
        }
        else if ((value) === (PerfMonitorActionType.FIRST_MOVE)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof PerfMonitorActionType")
        }
    }
    static isPerfMonitorSourceType(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (PerfMonitorSourceType.PERF_TOUCH_EVENT)) {
            return true
        }
        else if ((value) === (PerfMonitorSourceType.PERF_MOUSE_EVENT)) {
            return true
        }
        else if ((value) === (PerfMonitorSourceType.PERF_TOUCHPAD_EVENT)) {
            return true
        }
        else if ((value) === (PerfMonitorSourceType.PERF_JOYSTICK_EVENT)) {
            return true
        }
        else if ((value) === (PerfMonitorSourceType.PERF_KEY_EVENT)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof PerfMonitorSourceType")
        }
    }
    static isPermissionRequest(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof PermissionRequest")
    }
    static isPersistPropsOptions(value: object|string|number|undefined|null|boolean, duplicated_key: boolean, duplicated_defaultValue: boolean): boolean {
        if ((!duplicated_key) && (value?.hasOwnProperty("key"))) {
            return true
        }
        else if ((!duplicated_defaultValue) && (value?.hasOwnProperty("defaultValue"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof PersistPropsOptions")
        }
    }
    static isPickerDialogButtonStyle(value: object|string|number|undefined|null|boolean, duplicated_type: boolean, duplicated_style: boolean, duplicated_role: boolean, duplicated_fontSize: boolean, duplicated_fontColor: boolean, duplicated_fontWeight: boolean, duplicated_fontStyle: boolean, duplicated_fontFamily: boolean, duplicated_backgroundColor: boolean, duplicated_borderRadius: boolean, duplicated_primary: boolean): boolean {
        if ((!duplicated_type) && (value?.hasOwnProperty("type"))) {
            return true
        }
        else if ((!duplicated_style) && (value?.hasOwnProperty("style"))) {
            return true
        }
        else if ((!duplicated_role) && (value?.hasOwnProperty("role"))) {
            return true
        }
        else if ((!duplicated_fontSize) && (value?.hasOwnProperty("fontSize"))) {
            return true
        }
        else if ((!duplicated_fontColor) && (value?.hasOwnProperty("fontColor"))) {
            return true
        }
        else if ((!duplicated_fontWeight) && (value?.hasOwnProperty("fontWeight"))) {
            return true
        }
        else if ((!duplicated_fontStyle) && (value?.hasOwnProperty("fontStyle"))) {
            return true
        }
        else if ((!duplicated_fontFamily) && (value?.hasOwnProperty("fontFamily"))) {
            return true
        }
        else if ((!duplicated_backgroundColor) && (value?.hasOwnProperty("backgroundColor"))) {
            return true
        }
        else if ((!duplicated_borderRadius) && (value?.hasOwnProperty("borderRadius"))) {
            return true
        }
        else if ((!duplicated_primary) && (value?.hasOwnProperty("primary"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof PickerDialogButtonStyle")
        }
    }
    static isPickerTextStyle(value: object|string|number|undefined|null|boolean, duplicated_color: boolean, duplicated_font: boolean): boolean {
        if ((!duplicated_color) && (value?.hasOwnProperty("color"))) {
            return true
        }
        else if ((!duplicated_font) && (value?.hasOwnProperty("font"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof PickerTextStyle")
        }
    }
    static isPinchGestureEvent(value: object|string|number|undefined|null|boolean, duplicated_scale: boolean, duplicated_pinchCenterX: boolean, duplicated_pinchCenterY: boolean): boolean {
        if ((!duplicated_scale) && (value?.hasOwnProperty("scale"))) {
            return true
        }
        else if ((!duplicated_pinchCenterX) && (value?.hasOwnProperty("pinchCenterX"))) {
            return true
        }
        else if ((!duplicated_pinchCenterY) && (value?.hasOwnProperty("pinchCenterY"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof PinchGestureEvent")
        }
    }
    static isPinchGestureHandler(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof PinchGestureHandler")
    }
    static isPinchGestureHandlerOptions(value: object|string|number|undefined|null|boolean, duplicated_fingers: boolean, duplicated_distance: boolean): boolean {
        if ((!duplicated_fingers) && (value?.hasOwnProperty("fingers"))) {
            return true
        }
        else if ((!duplicated_distance) && (value?.hasOwnProperty("distance"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof PinchGestureHandlerOptions")
        }
    }
    static isPinchGestureInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof PinchGestureInterface")
    }
    static isPixelMap(value: object|string|number|undefined|null|boolean, duplicated_isEditable: boolean, duplicated_isStrideAlignment: boolean): boolean {
        if ((!duplicated_isEditable) && (value?.hasOwnProperty("isEditable"))) {
            return true
        }
        else if ((!duplicated_isStrideAlignment) && (value?.hasOwnProperty("isStrideAlignment"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof PixelMap")
        }
    }
    static isPixelMapDrawableDescriptor(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof PixelMapDrawableDescriptor")
    }
    static isPixelMapMock(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof PixelMapMock")
    }
    static isPixelRoundCalcPolicy(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (PixelRoundCalcPolicy.NO_FORCE_ROUND)) {
            return true
        }
        else if ((value) === (PixelRoundCalcPolicy.FORCE_CEIL)) {
            return true
        }
        else if ((value) === (PixelRoundCalcPolicy.FORCE_FLOOR)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof PixelRoundCalcPolicy")
        }
    }
    static isPixelRoundPolicy(value: object|string|number|undefined|null|boolean, duplicated_start: boolean, duplicated_top: boolean, duplicated_end: boolean, duplicated_bottom: boolean): boolean {
        if ((!duplicated_start) && (value?.hasOwnProperty("start"))) {
            return true
        }
        else if ((!duplicated_top) && (value?.hasOwnProperty("top"))) {
            return true
        }
        else if ((!duplicated_end) && (value?.hasOwnProperty("end"))) {
            return true
        }
        else if ((!duplicated_bottom) && (value?.hasOwnProperty("bottom"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof PixelRoundPolicy")
        }
    }
    static isPixelStretchEffectOptions(value: object|string|number|undefined|null|boolean, duplicated_top: boolean, duplicated_bottom: boolean, duplicated_left: boolean, duplicated_right: boolean): boolean {
        if ((!duplicated_top) && (value?.hasOwnProperty("top"))) {
            return true
        }
        else if ((!duplicated_bottom) && (value?.hasOwnProperty("bottom"))) {
            return true
        }
        else if ((!duplicated_left) && (value?.hasOwnProperty("left"))) {
            return true
        }
        else if ((!duplicated_right) && (value?.hasOwnProperty("right"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof PixelStretchEffectOptions")
        }
    }
    static isPlaceholderStyle(value: object|string|number|undefined|null|boolean, duplicated_font: boolean, duplicated_fontColor: boolean): boolean {
        if ((!duplicated_font) && (value?.hasOwnProperty("font"))) {
            return true
        }
        else if ((!duplicated_fontColor) && (value?.hasOwnProperty("fontColor"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof PlaceholderStyle")
        }
    }
    static isPlacement(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (Placement.Left)) {
            return true
        }
        else if ((value) === (Placement.Right)) {
            return true
        }
        else if ((value) === (Placement.Top)) {
            return true
        }
        else if ((value) === (Placement.Bottom)) {
            return true
        }
        else if ((value) === (Placement.TopLeft)) {
            return true
        }
        else if ((value) === (Placement.TopRight)) {
            return true
        }
        else if ((value) === (Placement.BottomLeft)) {
            return true
        }
        else if ((value) === (Placement.BottomRight)) {
            return true
        }
        else if ((value) === (Placement.LeftTop)) {
            return true
        }
        else if ((value) === (Placement.LeftBottom)) {
            return true
        }
        else if ((value) === (Placement.RightTop)) {
            return true
        }
        else if ((value) === (Placement.RightBottom)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof Placement")
        }
    }
    static isPlaybackInfo(value: object|string|number|undefined|null|boolean, duplicated_time: boolean): boolean {
        if ((!duplicated_time) && (value?.hasOwnProperty("time"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof PlaybackInfo")
        }
    }
    static isPlaybackSpeed(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (PlaybackSpeed.Speed_Forward_0_75_X)) {
            return true
        }
        else if ((value) === (PlaybackSpeed.Speed_Forward_1_00_X)) {
            return true
        }
        else if ((value) === (PlaybackSpeed.Speed_Forward_1_25_X)) {
            return true
        }
        else if ((value) === (PlaybackSpeed.Speed_Forward_1_75_X)) {
            return true
        }
        else if ((value) === (PlaybackSpeed.Speed_Forward_2_00_X)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof PlaybackSpeed")
        }
    }
    static isPlayMode(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (PlayMode.Normal)) {
            return true
        }
        else if ((value) === (PlayMode.Reverse)) {
            return true
        }
        else if ((value) === (PlayMode.Alternate)) {
            return true
        }
        else if ((value) === (PlayMode.AlternateReverse)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof PlayMode")
        }
    }
    static isPluginComponentAttribute(value: object|string|number|undefined|null|boolean, duplicated_onComplete: boolean, duplicated_onError: boolean): boolean {
        if ((!duplicated_onComplete) && (value?.hasOwnProperty("onComplete"))) {
            return true
        }
        else if ((!duplicated_onError) && (value?.hasOwnProperty("onError"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof PluginComponentAttribute")
        }
    }
    static isPluginComponentInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof PluginComponentInterface")
    }
    static isPluginComponentOptions(value: object|string|number|undefined|null|boolean, duplicated_template: boolean, duplicated_data: boolean): boolean {
        if ((!duplicated_template) && (value?.hasOwnProperty("template"))) {
            return true
        }
        else if ((!duplicated_data) && (value?.hasOwnProperty("data"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof PluginComponentOptions")
        }
    }
    static isPluginComponentTemplate(value: object|string|number|undefined|null|boolean, duplicated_source: boolean, duplicated_bundleName: boolean): boolean {
        if ((!duplicated_source) && (value?.hasOwnProperty("source"))) {
            return true
        }
        else if ((!duplicated_bundleName) && (value?.hasOwnProperty("bundleName"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof PluginComponentTemplate")
        }
    }
    static isPluginErrorData(value: object|string|number|undefined|null|boolean, duplicated_errcode: boolean, duplicated_msg: boolean): boolean {
        if ((!duplicated_errcode) && (value?.hasOwnProperty("errcode"))) {
            return true
        }
        else if ((!duplicated_msg) && (value?.hasOwnProperty("msg"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof PluginErrorData")
        }
    }
    static isPoint(value: object|string|number|undefined|null|boolean, duplicated_x: boolean, duplicated_y: boolean): boolean {
        if ((!duplicated_x) && (value?.hasOwnProperty("x"))) {
            return true
        }
        else if ((!duplicated_y) && (value?.hasOwnProperty("y"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof Point")
        }
    }
    static isPointerStyle(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (PointerStyle.DEFAULT)) {
            return true
        }
        else if ((value) === (PointerStyle.EAST)) {
            return true
        }
        else if ((value) === (PointerStyle.WEST)) {
            return true
        }
        else if ((value) === (PointerStyle.SOUTH)) {
            return true
        }
        else if ((value) === (PointerStyle.NORTH)) {
            return true
        }
        else if ((value) === (PointerStyle.WEST_EAST)) {
            return true
        }
        else if ((value) === (PointerStyle.NORTH_SOUTH)) {
            return true
        }
        else if ((value) === (PointerStyle.NORTH_EAST)) {
            return true
        }
        else if ((value) === (PointerStyle.NORTH_WEST)) {
            return true
        }
        else if ((value) === (PointerStyle.SOUTH_EAST)) {
            return true
        }
        else if ((value) === (PointerStyle.SOUTH_WEST)) {
            return true
        }
        else if ((value) === (PointerStyle.NORTH_EAST_SOUTH_WEST)) {
            return true
        }
        else if ((value) === (PointerStyle.NORTH_WEST_SOUTH_EAST)) {
            return true
        }
        else if ((value) === (PointerStyle.CROSS)) {
            return true
        }
        else if ((value) === (PointerStyle.CURSOR_COPY)) {
            return true
        }
        else if ((value) === (PointerStyle.CURSOR_FORBID)) {
            return true
        }
        else if ((value) === (PointerStyle.COLOR_SUCKER)) {
            return true
        }
        else if ((value) === (PointerStyle.HAND_GRABBING)) {
            return true
        }
        else if ((value) === (PointerStyle.HAND_OPEN)) {
            return true
        }
        else if ((value) === (PointerStyle.HAND_POINTING)) {
            return true
        }
        else if ((value) === (PointerStyle.HELP)) {
            return true
        }
        else if ((value) === (PointerStyle.MOVE)) {
            return true
        }
        else if ((value) === (PointerStyle.RESIZE_LEFT_RIGHT)) {
            return true
        }
        else if ((value) === (PointerStyle.RESIZE_UP_DOWN)) {
            return true
        }
        else if ((value) === (PointerStyle.SCREENSHOT_CHOOSE)) {
            return true
        }
        else if ((value) === (PointerStyle.SCREENSHOT_CURSOR)) {
            return true
        }
        else if ((value) === (PointerStyle.TEXT_CURSOR)) {
            return true
        }
        else if ((value) === (PointerStyle.ZOOM_IN)) {
            return true
        }
        else if ((value) === (PointerStyle.ZOOM_OUT)) {
            return true
        }
        else if ((value) === (PointerStyle.MIDDLE_BTN_EAST)) {
            return true
        }
        else if ((value) === (PointerStyle.MIDDLE_BTN_WEST)) {
            return true
        }
        else if ((value) === (PointerStyle.MIDDLE_BTN_SOUTH)) {
            return true
        }
        else if ((value) === (PointerStyle.MIDDLE_BTN_NORTH)) {
            return true
        }
        else if ((value) === (PointerStyle.MIDDLE_BTN_NORTH_SOUTH)) {
            return true
        }
        else if ((value) === (PointerStyle.MIDDLE_BTN_NORTH_EAST)) {
            return true
        }
        else if ((value) === (PointerStyle.MIDDLE_BTN_NORTH_WEST)) {
            return true
        }
        else if ((value) === (PointerStyle.MIDDLE_BTN_SOUTH_EAST)) {
            return true
        }
        else if ((value) === (PointerStyle.MIDDLE_BTN_SOUTH_WEST)) {
            return true
        }
        else if ((value) === (PointerStyle.MIDDLE_BTN_NORTH_SOUTH_WEST_EAST)) {
            return true
        }
        else if ((value) === (PointerStyle.HORIZONTAL_TEXT_CURSOR)) {
            return true
        }
        else if ((value) === (PointerStyle.CURSOR_CROSS)) {
            return true
        }
        else if ((value) === (PointerStyle.CURSOR_CIRCLE)) {
            return true
        }
        else if ((value) === (PointerStyle.LOADING)) {
            return true
        }
        else if ((value) === (PointerStyle.RUNNING)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof PointerStyle")
        }
    }
    static isPointLightStyle(value: object|string|number|undefined|null|boolean, duplicated_lightSource: boolean, duplicated_illuminated: boolean, duplicated_bloom: boolean): boolean {
        if ((!duplicated_lightSource) && (value?.hasOwnProperty("lightSource"))) {
            return true
        }
        else if ((!duplicated_illuminated) && (value?.hasOwnProperty("illuminated"))) {
            return true
        }
        else if ((!duplicated_bloom) && (value?.hasOwnProperty("bloom"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof PointLightStyle")
        }
    }
    static isPointParticleParameters(value: object|string|number|undefined|null|boolean, duplicated_radius: boolean): boolean {
        if ((!duplicated_radius) && (value?.hasOwnProperty("radius"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof PointParticleParameters")
        }
    }
    static isPolygonAttribute(value: object|string|number|undefined|null|boolean, duplicated_points: boolean): boolean {
        if ((!duplicated_points) && (value?.hasOwnProperty("points"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof PolygonAttribute")
        }
    }
    static isPolygonInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof PolygonInterface")
    }
    static isPolygonOptions(value: object|string|number|undefined|null|boolean, duplicated_width: boolean, duplicated_height: boolean): boolean {
        if ((!duplicated_width) && (value?.hasOwnProperty("width"))) {
            return true
        }
        else if ((!duplicated_height) && (value?.hasOwnProperty("height"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof PolygonOptions")
        }
    }
    static isPolylineAttribute(value: object|string|number|undefined|null|boolean, duplicated_points: boolean): boolean {
        if ((!duplicated_points) && (value?.hasOwnProperty("points"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof PolylineAttribute")
        }
    }
    static isPolylineInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof PolylineInterface")
    }
    static isPolylineOptions(value: object|string|number|undefined|null|boolean, duplicated_width: boolean, duplicated_height: boolean): boolean {
        if ((!duplicated_width) && (value?.hasOwnProperty("width"))) {
            return true
        }
        else if ((!duplicated_height) && (value?.hasOwnProperty("height"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof PolylineOptions")
        }
    }
    static isPopInfo(value: object|string|number|undefined|null|boolean, duplicated_info: boolean, duplicated_result: boolean): boolean {
        if ((!duplicated_info) && (value?.hasOwnProperty("info"))) {
            return true
        }
        else if ((!duplicated_result) && (value?.hasOwnProperty("result"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof PopInfo")
        }
    }
    static isPopupMessageOptions(value: object|string|number|undefined|null|boolean, duplicated_textColor: boolean, duplicated_font: boolean): boolean {
        if ((!duplicated_textColor) && (value?.hasOwnProperty("textColor"))) {
            return true
        }
        else if ((!duplicated_font) && (value?.hasOwnProperty("font"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof PopupMessageOptions")
        }
    }
    static isPopupOptions(value: object|string|number|undefined|null|boolean, duplicated_message: boolean, duplicated_placementOnTop: boolean, duplicated_placement: boolean, duplicated_primaryButton: boolean, duplicated_secondaryButton: boolean, duplicated_onStateChange: boolean, duplicated_arrowOffset: boolean, duplicated_showInSubWindow: boolean, duplicated_mask: boolean, duplicated_messageOptions: boolean, duplicated_targetSpace: boolean, duplicated_enableArrow: boolean, duplicated_offset: boolean, duplicated_popupColor: boolean, duplicated_autoCancel: boolean, duplicated_width: boolean, duplicated_arrowPointPosition: boolean, duplicated_arrowWidth: boolean, duplicated_arrowHeight: boolean, duplicated_radius: boolean, duplicated_shadow: boolean, duplicated_backgroundBlurStyle: boolean, duplicated_transition: boolean, duplicated_onWillDismiss: boolean, duplicated_enableHoverMode: boolean, duplicated_followTransformOfTarget: boolean): boolean {
        if ((!duplicated_message) && (value?.hasOwnProperty("message"))) {
            return true
        }
        else if ((!duplicated_placementOnTop) && (value?.hasOwnProperty("placementOnTop"))) {
            return true
        }
        else if ((!duplicated_placement) && (value?.hasOwnProperty("placement"))) {
            return true
        }
        else if ((!duplicated_primaryButton) && (value?.hasOwnProperty("primaryButton"))) {
            return true
        }
        else if ((!duplicated_secondaryButton) && (value?.hasOwnProperty("secondaryButton"))) {
            return true
        }
        else if ((!duplicated_onStateChange) && (value?.hasOwnProperty("onStateChange"))) {
            return true
        }
        else if ((!duplicated_arrowOffset) && (value?.hasOwnProperty("arrowOffset"))) {
            return true
        }
        else if ((!duplicated_showInSubWindow) && (value?.hasOwnProperty("showInSubWindow"))) {
            return true
        }
        else if ((!duplicated_mask) && (value?.hasOwnProperty("mask"))) {
            return true
        }
        else if ((!duplicated_messageOptions) && (value?.hasOwnProperty("messageOptions"))) {
            return true
        }
        else if ((!duplicated_targetSpace) && (value?.hasOwnProperty("targetSpace"))) {
            return true
        }
        else if ((!duplicated_enableArrow) && (value?.hasOwnProperty("enableArrow"))) {
            return true
        }
        else if ((!duplicated_offset) && (value?.hasOwnProperty("offset"))) {
            return true
        }
        else if ((!duplicated_popupColor) && (value?.hasOwnProperty("popupColor"))) {
            return true
        }
        else if ((!duplicated_autoCancel) && (value?.hasOwnProperty("autoCancel"))) {
            return true
        }
        else if ((!duplicated_width) && (value?.hasOwnProperty("width"))) {
            return true
        }
        else if ((!duplicated_arrowPointPosition) && (value?.hasOwnProperty("arrowPointPosition"))) {
            return true
        }
        else if ((!duplicated_arrowWidth) && (value?.hasOwnProperty("arrowWidth"))) {
            return true
        }
        else if ((!duplicated_arrowHeight) && (value?.hasOwnProperty("arrowHeight"))) {
            return true
        }
        else if ((!duplicated_radius) && (value?.hasOwnProperty("radius"))) {
            return true
        }
        else if ((!duplicated_shadow) && (value?.hasOwnProperty("shadow"))) {
            return true
        }
        else if ((!duplicated_backgroundBlurStyle) && (value?.hasOwnProperty("backgroundBlurStyle"))) {
            return true
        }
        else if ((!duplicated_transition) && (value?.hasOwnProperty("transition"))) {
            return true
        }
        else if ((!duplicated_onWillDismiss) && (value?.hasOwnProperty("onWillDismiss"))) {
            return true
        }
        else if ((!duplicated_enableHoverMode) && (value?.hasOwnProperty("enableHoverMode"))) {
            return true
        }
        else if ((!duplicated_followTransformOfTarget) && (value?.hasOwnProperty("followTransformOfTarget"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof PopupOptions")
        }
    }
    static isPosition(value: object|string|number|undefined|null|boolean, duplicated_x: boolean, duplicated_y: boolean): boolean {
        if ((!duplicated_x) && (value?.hasOwnProperty("x"))) {
            return true
        }
        else if ((!duplicated_y) && (value?.hasOwnProperty("y"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof Position")
        }
    }
    static isPositionWithAffinity(value: object|string|number|undefined|null|boolean, duplicated_position: boolean, duplicated_affinity: boolean): boolean {
        if ((!duplicated_position) && (value?.hasOwnProperty("position"))) {
            return true
        }
        else if ((!duplicated_affinity) && (value?.hasOwnProperty("affinity"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof PositionWithAffinity")
        }
    }
    static isPreDragStatus(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (PreDragStatus.ACTION_DETECTING_STATUS)) {
            return true
        }
        else if ((value) === (PreDragStatus.READY_TO_TRIGGER_DRAG_ACTION)) {
            return true
        }
        else if ((value) === (PreDragStatus.PREVIEW_LIFT_STARTED)) {
            return true
        }
        else if ((value) === (PreDragStatus.PREVIEW_LIFT_FINISHED)) {
            return true
        }
        else if ((value) === (PreDragStatus.PREVIEW_LANDING_STARTED)) {
            return true
        }
        else if ((value) === (PreDragStatus.PREVIEW_LANDING_FINISHED)) {
            return true
        }
        else if ((value) === (PreDragStatus.ACTION_CANCELED_BEFORE_DRAG)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof PreDragStatus")
        }
    }
    static isPreparedInfo(value: object|string|number|undefined|null|boolean, duplicated_duration: boolean): boolean {
        if ((!duplicated_duration) && (value?.hasOwnProperty("duration"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof PreparedInfo")
        }
    }
    static isPreviewParams(value: object|string|number|undefined|null|boolean, duplicated_title: boolean, duplicated_width: boolean, duplicated_height: boolean, duplicated_locale: boolean, duplicated_colorMode: boolean, duplicated_deviceType: boolean, duplicated_dpi: boolean, duplicated_orientation: boolean, duplicated_roundScreen: boolean): boolean {
        if ((!duplicated_title) && (value?.hasOwnProperty("title"))) {
            return true
        }
        else if ((!duplicated_width) && (value?.hasOwnProperty("width"))) {
            return true
        }
        else if ((!duplicated_height) && (value?.hasOwnProperty("height"))) {
            return true
        }
        else if ((!duplicated_locale) && (value?.hasOwnProperty("locale"))) {
            return true
        }
        else if ((!duplicated_colorMode) && (value?.hasOwnProperty("colorMode"))) {
            return true
        }
        else if ((!duplicated_deviceType) && (value?.hasOwnProperty("deviceType"))) {
            return true
        }
        else if ((!duplicated_dpi) && (value?.hasOwnProperty("dpi"))) {
            return true
        }
        else if ((!duplicated_orientation) && (value?.hasOwnProperty("orientation"))) {
            return true
        }
        else if ((!duplicated_roundScreen) && (value?.hasOwnProperty("roundScreen"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof PreviewParams")
        }
    }
    static isPreviewText(value: object|string|number|undefined|null|boolean, duplicated_offset: boolean, duplicated_value: boolean): boolean {
        if ((!duplicated_offset) && (value?.hasOwnProperty("offset"))) {
            return true
        }
        else if ((!duplicated_value) && (value?.hasOwnProperty("value"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof PreviewText")
        }
    }
    static isProgressAttribute(value: object|string|number|undefined|null|boolean, duplicated_value: boolean, duplicated_color: boolean, duplicated_style: boolean, duplicated_privacySensitive: boolean, duplicated_contentModifier: boolean): boolean {
        if ((!duplicated_value) && (value?.hasOwnProperty("value"))) {
            return true
        }
        else if ((!duplicated_color) && (value?.hasOwnProperty("color"))) {
            return true
        }
        else if ((!duplicated_style) && (value?.hasOwnProperty("style"))) {
            return true
        }
        else if ((!duplicated_privacySensitive) && (value?.hasOwnProperty("privacySensitive"))) {
            return true
        }
        else if ((!duplicated_contentModifier) && (value?.hasOwnProperty("contentModifier"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ProgressAttribute")
        }
    }
    static isProgressConfiguration(value: object|string|number|undefined|null|boolean, duplicated_value: boolean, duplicated_total: boolean): boolean {
        if ((!duplicated_value) && (value?.hasOwnProperty("value"))) {
            return true
        }
        else if ((!duplicated_total) && (value?.hasOwnProperty("total"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ProgressConfiguration")
        }
    }
    static isProgressInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof ProgressInterface")
    }
    static isProgressMask(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof ProgressMask")
    }
    static isProgressOptions(value: object|string|number|undefined|null|boolean, duplicated_value: boolean, duplicated_total: boolean, duplicated_style: boolean, duplicated_type: boolean): boolean {
        if ((!duplicated_value) && (value?.hasOwnProperty("value"))) {
            return true
        }
        else if ((!duplicated_total) && (value?.hasOwnProperty("total"))) {
            return true
        }
        else if ((!duplicated_style) && (value?.hasOwnProperty("style"))) {
            return true
        }
        else if ((!duplicated_type) && (value?.hasOwnProperty("type"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ProgressOptions")
        }
    }
    static isProgressStatus(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (ProgressStatus.LOADING)) {
            return true
        }
        else if ((value) === (ProgressStatus.PROGRESSING)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ProgressStatus")
        }
    }
    static isProgressStyle(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (ProgressStyle.Linear)) {
            return true
        }
        else if ((value) === (ProgressStyle.Ring)) {
            return true
        }
        else if ((value) === (ProgressStyle.Eclipse)) {
            return true
        }
        else if ((value) === (ProgressStyle.ScaleRing)) {
            return true
        }
        else if ((value) === (ProgressStyle.Capsule)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ProgressStyle")
        }
    }
    static isProgressStyleMap(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof ProgressStyleMap")
    }
    static isProgressStyleOptions(value: object|string|number|undefined|null|boolean, duplicated_strokeWidth: boolean, duplicated_scaleCount: boolean, duplicated_scaleWidth: boolean): boolean {
        if ((!duplicated_strokeWidth) && (value?.hasOwnProperty("strokeWidth"))) {
            return true
        }
        else if ((!duplicated_scaleCount) && (value?.hasOwnProperty("scaleCount"))) {
            return true
        }
        else if ((!duplicated_scaleWidth) && (value?.hasOwnProperty("scaleWidth"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ProgressStyleOptions")
        }
    }
    static isProgressType(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (ProgressType.Linear)) {
            return true
        }
        else if ((value) === (ProgressType.Ring)) {
            return true
        }
        else if ((value) === (ProgressType.Eclipse)) {
            return true
        }
        else if ((value) === (ProgressType.ScaleRing)) {
            return true
        }
        else if ((value) === (ProgressType.Capsule)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ProgressType")
        }
    }
    static isProtectedResourceType(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (ProtectedResourceType.MidiSysex)) {
            return true
        }
        else if ((value) === (ProtectedResourceType.VIDEO_CAPTURE)) {
            return true
        }
        else if ((value) === (ProtectedResourceType.AUDIO_CAPTURE)) {
            return true
        }
        else if ((value) === (ProtectedResourceType.SENSOR)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ProtectedResourceType")
        }
    }
    static isProvideOptions(value: object|string|number|undefined|null|boolean, duplicated_allowOverride: boolean): boolean {
        if ((!duplicated_allowOverride) && (value?.hasOwnProperty("allowOverride"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ProvideOptions")
        }
    }
    static isPulseSymbolEffect(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof PulseSymbolEffect")
    }
    static isQRCodeAttribute(value: object|string|number|undefined|null|boolean, duplicated_color: boolean, duplicated_backgroundColor: boolean, duplicated_contentOpacity: boolean): boolean {
        if ((!duplicated_color) && (value?.hasOwnProperty("color"))) {
            return true
        }
        else if ((!duplicated_backgroundColor) && (value?.hasOwnProperty("backgroundColor"))) {
            return true
        }
        else if ((!duplicated_contentOpacity) && (value?.hasOwnProperty("contentOpacity"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof QRCodeAttribute")
        }
    }
    static isQRCodeInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof QRCodeInterface")
    }
    static isRadioAttribute(value: object|string|number|undefined|null|boolean, duplicated_checked: boolean, duplicated_onChange: boolean, duplicated_radioStyle: boolean, duplicated_contentModifier: boolean): boolean {
        if ((!duplicated_checked) && (value?.hasOwnProperty("checked"))) {
            return true
        }
        else if ((!duplicated_onChange) && (value?.hasOwnProperty("onChange"))) {
            return true
        }
        else if ((!duplicated_contentModifier) && (value?.hasOwnProperty("contentModifier"))) {
            return true
        }
        else if ((!duplicated_radioStyle) && (value?.hasOwnProperty("radioStyle"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RadioAttribute")
        }
    }
    static isRadioConfiguration(value: object|string|number|undefined|null|boolean, duplicated_value: boolean, duplicated_checked: boolean, duplicated_triggerChange: boolean): boolean {
        if ((!duplicated_value) && (value?.hasOwnProperty("value"))) {
            return true
        }
        else if ((!duplicated_checked) && (value?.hasOwnProperty("checked"))) {
            return true
        }
        else if ((!duplicated_triggerChange) && (value?.hasOwnProperty("triggerChange"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RadioConfiguration")
        }
    }
    static isRadioIndicatorType(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (RadioIndicatorType.TICK)) {
            return true
        }
        else if ((value) === (RadioIndicatorType.DOT)) {
            return true
        }
        else if ((value) === (RadioIndicatorType.CUSTOM)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RadioIndicatorType")
        }
    }
    static isRadioInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof RadioInterface")
    }
    static isRadioOptions(value: object|string|number|undefined|null|boolean, duplicated_group: boolean, duplicated_value: boolean, duplicated_indicatorType: boolean, duplicated_indicatorBuilder: boolean): boolean {
        if ((!duplicated_group) && (value?.hasOwnProperty("group"))) {
            return true
        }
        else if ((!duplicated_value) && (value?.hasOwnProperty("value"))) {
            return true
        }
        else if ((!duplicated_indicatorType) && (value?.hasOwnProperty("indicatorType"))) {
            return true
        }
        else if ((!duplicated_indicatorBuilder) && (value?.hasOwnProperty("indicatorBuilder"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RadioOptions")
        }
    }
    static isRadioStyle(value: object|string|number|undefined|null|boolean, duplicated_checkedBackgroundColor: boolean, duplicated_uncheckedBorderColor: boolean, duplicated_indicatorColor: boolean): boolean {
        if ((!duplicated_checkedBackgroundColor) && (value?.hasOwnProperty("checkedBackgroundColor"))) {
            return true
        }
        else if ((!duplicated_uncheckedBorderColor) && (value?.hasOwnProperty("uncheckedBorderColor"))) {
            return true
        }
        else if ((!duplicated_indicatorColor) && (value?.hasOwnProperty("indicatorColor"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RadioStyle")
        }
    }
    static isRatingAttribute(value: object|string|number|undefined|null|boolean, duplicated_stars: boolean, duplicated_stepSize: boolean, duplicated_starStyle: boolean, duplicated_onChange: boolean, duplicated_contentModifier: boolean): boolean {
        if ((!duplicated_stars) && (value?.hasOwnProperty("stars"))) {
            return true
        }
        else if ((!duplicated_stepSize) && (value?.hasOwnProperty("stepSize"))) {
            return true
        }
        else if ((!duplicated_starStyle) && (value?.hasOwnProperty("starStyle"))) {
            return true
        }
        else if ((!duplicated_onChange) && (value?.hasOwnProperty("onChange"))) {
            return true
        }
        else if ((!duplicated_contentModifier) && (value?.hasOwnProperty("contentModifier"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RatingAttribute")
        }
    }
    static isRatingConfiguration(value: object|string|number|undefined|null|boolean, duplicated_rating: boolean, duplicated_indicator: boolean, duplicated_stars: boolean, duplicated_stepSize: boolean, duplicated_triggerChange: boolean): boolean {
        if ((!duplicated_rating) && (value?.hasOwnProperty("rating"))) {
            return true
        }
        else if ((!duplicated_indicator) && (value?.hasOwnProperty("indicator"))) {
            return true
        }
        else if ((!duplicated_stars) && (value?.hasOwnProperty("stars"))) {
            return true
        }
        else if ((!duplicated_stepSize) && (value?.hasOwnProperty("stepSize"))) {
            return true
        }
        else if ((!duplicated_triggerChange) && (value?.hasOwnProperty("triggerChange"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RatingConfiguration")
        }
    }
    static isRatingInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof RatingInterface")
    }
    static isRatingOptions(value: object|string|number|undefined|null|boolean, duplicated_rating: boolean, duplicated_indicator: boolean): boolean {
        if ((!duplicated_rating) && (value?.hasOwnProperty("rating"))) {
            return true
        }
        else if ((!duplicated_indicator) && (value?.hasOwnProperty("indicator"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RatingOptions")
        }
    }
    static isRawFileDescriptor(value: object|string|number|undefined|null|boolean, duplicated_fd: boolean, duplicated_offset: boolean, duplicated_length: boolean): boolean {
        if ((!duplicated_fd) && (value?.hasOwnProperty("fd"))) {
            return true
        }
        else if ((!duplicated_offset) && (value?.hasOwnProperty("offset"))) {
            return true
        }
        else if ((!duplicated_length) && (value?.hasOwnProperty("length"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RawFileDescriptor")
        }
    }
    static isReceiveCallback(value: object|string|number|undefined|null|boolean, duplicated__ReceiveCallbackStub: boolean): boolean {
        if ((!duplicated__ReceiveCallbackStub) && (value?.hasOwnProperty("_ReceiveCallbackStub"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ReceiveCallback")
        }
    }
    static isRectangle(value: object|string|number|undefined|null|boolean, duplicated_x: boolean, duplicated_y: boolean, duplicated_width: boolean, duplicated_height: boolean): boolean {
        if ((!duplicated_x) && (value?.hasOwnProperty("x"))) {
            return true
        }
        else if ((!duplicated_y) && (value?.hasOwnProperty("y"))) {
            return true
        }
        else if ((!duplicated_width) && (value?.hasOwnProperty("width"))) {
            return true
        }
        else if ((!duplicated_height) && (value?.hasOwnProperty("height"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof Rectangle")
        }
    }
    static isRectAttribute(value: object|string|number|undefined|null|boolean, duplicated_radiusWidth: boolean, duplicated_radiusHeight: boolean, duplicated_radius: boolean): boolean {
        if ((!duplicated_radiusWidth) && (value?.hasOwnProperty("radiusWidth"))) {
            return true
        }
        else if ((!duplicated_radiusHeight) && (value?.hasOwnProperty("radiusHeight"))) {
            return true
        }
        else if ((!duplicated_radius) && (value?.hasOwnProperty("radius"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RectAttribute")
        }
    }
    static isRectHeightStyle(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (RectHeightStyle.TIGHT)) {
            return true
        }
        else if ((value) === (RectHeightStyle.MAX)) {
            return true
        }
        else if ((value) === (RectHeightStyle.INCLUDE_LINE_SPACE_MIDDLE)) {
            return true
        }
        else if ((value) === (RectHeightStyle.INCLUDE_LINE_SPACE_TOP)) {
            return true
        }
        else if ((value) === (RectHeightStyle.INCLUDE_LINE_SPACE_BOTTOM)) {
            return true
        }
        else if ((value) === (RectHeightStyle.STRUT)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RectHeightStyle")
        }
    }
    static isRectInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof RectInterface")
    }
    static isRectOptions(value: object|string|number|undefined|null|boolean, duplicated_width: boolean, duplicated_height: boolean, duplicated_radius: boolean): boolean {
        if ((!duplicated_width) && (value?.hasOwnProperty("width"))) {
            return true
        }
        else if ((!duplicated_height) && (value?.hasOwnProperty("height"))) {
            return true
        }
        else if ((!duplicated_radius) && (value?.hasOwnProperty("radius"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RectOptions")
        }
    }
    static isRectResult(value: object|string|number|undefined|null|boolean, duplicated_x: boolean, duplicated_y: boolean, duplicated_width: boolean, duplicated_height: boolean): boolean {
        if ((!duplicated_x) && (value?.hasOwnProperty("x"))) {
            return true
        }
        else if ((!duplicated_y) && (value?.hasOwnProperty("y"))) {
            return true
        }
        else if ((!duplicated_width) && (value?.hasOwnProperty("width"))) {
            return true
        }
        else if ((!duplicated_height) && (value?.hasOwnProperty("height"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RectResult")
        }
    }
    static isRectShape(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof RectShape")
    }
    static isRectShapeOptions(value: object|string|number|undefined|null|boolean, duplicated_radius: boolean): boolean {
        if ((!duplicated_radius) && (value?.hasOwnProperty("radius"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RectShapeOptions")
        }
    }
    static isRectWidthStyle(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (RectWidthStyle.TIGHT)) {
            return true
        }
        else if ((value) === (RectWidthStyle.MAX)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RectWidthStyle")
        }
    }
    static isRefreshAttribute(value: object|string|number|undefined|null|boolean, duplicated_onStateChange: boolean, duplicated_onRefreshing: boolean, duplicated_refreshOffset: boolean, duplicated_pullToRefresh: boolean, duplicated_onOffsetChange: boolean, duplicated_pullDownRatio: boolean): boolean {
        if ((!duplicated_onStateChange) && (value?.hasOwnProperty("onStateChange"))) {
            return true
        }
        else if ((!duplicated_onRefreshing) && (value?.hasOwnProperty("onRefreshing"))) {
            return true
        }
        else if ((!duplicated_refreshOffset) && (value?.hasOwnProperty("refreshOffset"))) {
            return true
        }
        else if ((!duplicated_pullToRefresh) && (value?.hasOwnProperty("pullToRefresh"))) {
            return true
        }
        else if ((!duplicated_onOffsetChange) && (value?.hasOwnProperty("onOffsetChange"))) {
            return true
        }
        else if ((!duplicated_pullDownRatio) && (value?.hasOwnProperty("pullDownRatio"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RefreshAttribute")
        }
    }
    static isRefreshInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof RefreshInterface")
    }
    static isRefreshOptions(value: object|string|number|undefined|null|boolean, duplicated_refreshing: boolean, duplicated_offset: boolean, duplicated_friction: boolean, duplicated_promptText: boolean, duplicated_builder: boolean, duplicated_refreshingContent: boolean): boolean {
        if ((!duplicated_refreshing) && (value?.hasOwnProperty("refreshing"))) {
            return true
        }
        else if ((!duplicated_offset) && (value?.hasOwnProperty("offset"))) {
            return true
        }
        else if ((!duplicated_friction) && (value?.hasOwnProperty("friction"))) {
            return true
        }
        else if ((!duplicated_promptText) && (value?.hasOwnProperty("promptText"))) {
            return true
        }
        else if ((!duplicated_builder) && (value?.hasOwnProperty("builder"))) {
            return true
        }
        else if ((!duplicated_refreshingContent) && (value?.hasOwnProperty("refreshingContent"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RefreshOptions")
        }
    }
    static isRefreshStatus(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (RefreshStatus.Inactive)) {
            return true
        }
        else if ((value) === (RefreshStatus.Drag)) {
            return true
        }
        else if ((value) === (RefreshStatus.OverDrag)) {
            return true
        }
        else if ((value) === (RefreshStatus.Refresh)) {
            return true
        }
        else if ((value) === (RefreshStatus.Done)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RefreshStatus")
        }
    }
    static isRelateType(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (RelateType.FILL)) {
            return true
        }
        else if ((value) === (RelateType.FIT)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RelateType")
        }
    }
    static isRelativeContainerAttribute(value: object|string|number|undefined|null|boolean, duplicated_guideLine: boolean, duplicated_barrier: boolean): boolean {
        if ((!duplicated_guideLine) && (value?.hasOwnProperty("guideLine"))) {
            return true
        }
        else if ((!duplicated_barrier) && (value?.hasOwnProperty("barrier"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RelativeContainerAttribute")
        }
    }
    static isRelativeContainerInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof RelativeContainerInterface")
    }
    static isRemoteWindowAttribute(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof RemoteWindowAttribute")
    }
    static isRemoteWindowInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof RemoteWindowInterface")
    }
    static isRenderExitReason(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (RenderExitReason.ProcessAbnormalTermination)) {
            return true
        }
        else if ((value) === (RenderExitReason.ProcessWasKilled)) {
            return true
        }
        else if ((value) === (RenderExitReason.ProcessCrashed)) {
            return true
        }
        else if ((value) === (RenderExitReason.ProcessOom)) {
            return true
        }
        else if ((value) === (RenderExitReason.ProcessExitUnknown)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RenderExitReason")
        }
    }
    static isRenderFit(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (RenderFit.CENTER)) {
            return true
        }
        else if ((value) === (RenderFit.TOP)) {
            return true
        }
        else if ((value) === (RenderFit.BOTTOM)) {
            return true
        }
        else if ((value) === (RenderFit.LEFT)) {
            return true
        }
        else if ((value) === (RenderFit.RIGHT)) {
            return true
        }
        else if ((value) === (RenderFit.TOP_LEFT)) {
            return true
        }
        else if ((value) === (RenderFit.TOP_RIGHT)) {
            return true
        }
        else if ((value) === (RenderFit.BOTTOM_LEFT)) {
            return true
        }
        else if ((value) === (RenderFit.BOTTOM_RIGHT)) {
            return true
        }
        else if ((value) === (RenderFit.RESIZE_FILL)) {
            return true
        }
        else if ((value) === (RenderFit.RESIZE_CONTAIN)) {
            return true
        }
        else if ((value) === (RenderFit.RESIZE_CONTAIN_TOP_LEFT)) {
            return true
        }
        else if ((value) === (RenderFit.RESIZE_CONTAIN_BOTTOM_RIGHT)) {
            return true
        }
        else if ((value) === (RenderFit.RESIZE_COVER)) {
            return true
        }
        else if ((value) === (RenderFit.RESIZE_COVER_TOP_LEFT)) {
            return true
        }
        else if ((value) === (RenderFit.RESIZE_COVER_BOTTOM_RIGHT)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RenderFit")
        }
    }
    static isRenderingContextSettings(value: object|string|number|undefined|null|boolean, duplicated_antialias: boolean): boolean {
        if ((!duplicated_antialias) && (value?.hasOwnProperty("antialias"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RenderingContextSettings")
        }
    }
    static isRenderMode(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (RenderMode.ASYNC_RENDER)) {
            return true
        }
        else if ((value) === (RenderMode.SYNC_RENDER)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RenderMode")
        }
    }
    static isRenderProcessNotRespondingData(value: object|string|number|undefined|null|boolean, duplicated_jsStack: boolean, duplicated_pid: boolean, duplicated_reason: boolean): boolean {
        if ((!duplicated_jsStack) && (value?.hasOwnProperty("jsStack"))) {
            return true
        }
        else if ((!duplicated_pid) && (value?.hasOwnProperty("pid"))) {
            return true
        }
        else if ((!duplicated_reason) && (value?.hasOwnProperty("reason"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RenderProcessNotRespondingData")
        }
    }
    static isRenderProcessNotRespondingReason(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (RenderProcessNotRespondingReason.INPUT_TIMEOUT)) {
            return true
        }
        else if ((value) === (RenderProcessNotRespondingReason.NAVIGATION_COMMIT_TIMEOUT)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RenderProcessNotRespondingReason")
        }
    }
    static isRepeatMode(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (RepeatMode.Repeat)) {
            return true
        }
        else if ((value) === (RepeatMode.Stretch)) {
            return true
        }
        else if ((value) === (RepeatMode.Round)) {
            return true
        }
        else if ((value) === (RepeatMode.Space)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RepeatMode")
        }
    }
    static isReplaceSymbolEffect(value: object|string|number|undefined|null|boolean, duplicated_scope: boolean): boolean {
        if ((!duplicated_scope) && (value?.hasOwnProperty("scope"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ReplaceSymbolEffect")
        }
    }
    static isResizableOptions(value: object|string|number|undefined|null|boolean, duplicated_slice: boolean, duplicated_lattice: boolean): boolean {
        if ((!duplicated_slice) && (value?.hasOwnProperty("slice"))) {
            return true
        }
        else if ((!duplicated_lattice) && (value?.hasOwnProperty("lattice"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ResizableOptions")
        }
    }
    static isResolutionQuality(value: object|string|number|undefined|null|boolean, duplicated__ResolutionQualityStub: boolean): boolean {
        if ((!duplicated__ResolutionQualityStub) && (value?.hasOwnProperty("_ResolutionQualityStub"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ResolutionQuality")
        }
    }
    static isResource(value: object|string|number|undefined|null|boolean, duplicated_bundleName: boolean, duplicated_moduleName: boolean, duplicated_id: boolean, duplicated_params: boolean, duplicated_type: boolean): boolean {
        if ((!duplicated_bundleName) && (value?.hasOwnProperty("bundleName"))) {
            return true
        }
        else if ((!duplicated_moduleName) && (value?.hasOwnProperty("moduleName"))) {
            return true
        }
        else if ((!duplicated_id) && (value?.hasOwnProperty("id"))) {
            return true
        }
        else if ((!duplicated_params) && (value?.hasOwnProperty("params"))) {
            return true
        }
        else if ((!duplicated_type) && (value?.hasOwnProperty("type"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof Resource")
        }
    }
    static isResponseType(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (ResponseType.RightClick)) {
            return true
        }
        else if ((value) === (ResponseType.LongPress)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ResponseType")
        }
    }
    static isRestrictedWorker(value: object|string|number|undefined|null|boolean, duplicated__RestrictedWorkerStub: boolean): boolean {
        if ((!duplicated__RestrictedWorkerStub) && (value?.hasOwnProperty("_RestrictedWorkerStub"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RestrictedWorker")
        }
    }
    static isRichEditorAttribute(value: object|string|number|undefined|null|boolean, duplicated_onReady: boolean, duplicated_onSelect: boolean, duplicated_onSelectionChange: boolean, duplicated_aboutToIMEInput: boolean, duplicated_onIMEInputComplete: boolean, duplicated_onDidIMEInput: boolean, duplicated_aboutToDelete: boolean, duplicated_onDeleteComplete: boolean, duplicated_copyOptions: boolean, duplicated_onPaste: boolean, duplicated_enableDataDetector: boolean, duplicated_enablePreviewText: boolean, duplicated_dataDetectorConfig: boolean, duplicated_caretColor: boolean, duplicated_selectedBackgroundColor: boolean, duplicated_onEditingChange: boolean, duplicated_enterKeyType: boolean, duplicated_onSubmit: boolean, duplicated_onWillChange: boolean, duplicated_onDidChange: boolean, duplicated_onCut: boolean, duplicated_onCopy: boolean, duplicated_editMenuOptions: boolean, duplicated_enableKeyboardOnFocus: boolean, duplicated_enableHapticFeedback: boolean, duplicated_barState: boolean): boolean {
        if ((!duplicated_onReady) && (value?.hasOwnProperty("onReady"))) {
            return true
        }
        else if ((!duplicated_onSelect) && (value?.hasOwnProperty("onSelect"))) {
            return true
        }
        else if ((!duplicated_onSelectionChange) && (value?.hasOwnProperty("onSelectionChange"))) {
            return true
        }
        else if ((!duplicated_aboutToIMEInput) && (value?.hasOwnProperty("aboutToIMEInput"))) {
            return true
        }
        else if ((!duplicated_onIMEInputComplete) && (value?.hasOwnProperty("onIMEInputComplete"))) {
            return true
        }
        else if ((!duplicated_onDidIMEInput) && (value?.hasOwnProperty("onDidIMEInput"))) {
            return true
        }
        else if ((!duplicated_aboutToDelete) && (value?.hasOwnProperty("aboutToDelete"))) {
            return true
        }
        else if ((!duplicated_onDeleteComplete) && (value?.hasOwnProperty("onDeleteComplete"))) {
            return true
        }
        else if ((!duplicated_copyOptions) && (value?.hasOwnProperty("copyOptions"))) {
            return true
        }
        else if ((!duplicated_onPaste) && (value?.hasOwnProperty("onPaste"))) {
            return true
        }
        else if ((!duplicated_enableDataDetector) && (value?.hasOwnProperty("enableDataDetector"))) {
            return true
        }
        else if ((!duplicated_enablePreviewText) && (value?.hasOwnProperty("enablePreviewText"))) {
            return true
        }
        else if ((!duplicated_dataDetectorConfig) && (value?.hasOwnProperty("dataDetectorConfig"))) {
            return true
        }
        else if ((!duplicated_caretColor) && (value?.hasOwnProperty("caretColor"))) {
            return true
        }
        else if ((!duplicated_selectedBackgroundColor) && (value?.hasOwnProperty("selectedBackgroundColor"))) {
            return true
        }
        else if ((!duplicated_onEditingChange) && (value?.hasOwnProperty("onEditingChange"))) {
            return true
        }
        else if ((!duplicated_enterKeyType) && (value?.hasOwnProperty("enterKeyType"))) {
            return true
        }
        else if ((!duplicated_onSubmit) && (value?.hasOwnProperty("onSubmit"))) {
            return true
        }
        else if ((!duplicated_onWillChange) && (value?.hasOwnProperty("onWillChange"))) {
            return true
        }
        else if ((!duplicated_onDidChange) && (value?.hasOwnProperty("onDidChange"))) {
            return true
        }
        else if ((!duplicated_onCut) && (value?.hasOwnProperty("onCut"))) {
            return true
        }
        else if ((!duplicated_onCopy) && (value?.hasOwnProperty("onCopy"))) {
            return true
        }
        else if ((!duplicated_editMenuOptions) && (value?.hasOwnProperty("editMenuOptions"))) {
            return true
        }
        else if ((!duplicated_enableKeyboardOnFocus) && (value?.hasOwnProperty("enableKeyboardOnFocus"))) {
            return true
        }
        else if ((!duplicated_enableHapticFeedback) && (value?.hasOwnProperty("enableHapticFeedback"))) {
            return true
        }
        else if ((!duplicated_barState) && (value?.hasOwnProperty("barState"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RichEditorAttribute")
        }
    }
    static isRichEditorBaseController(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof RichEditorBaseController")
    }
    static isRichEditorBuilderSpanOptions(value: object|string|number|undefined|null|boolean, duplicated_offset: boolean): boolean {
        if ((!duplicated_offset) && (value?.hasOwnProperty("offset"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RichEditorBuilderSpanOptions")
        }
    }
    static isRichEditorChangeValue(value: object|string|number|undefined|null|boolean, duplicated_rangeBefore: boolean, duplicated_replacedSpans: boolean, duplicated_replacedImageSpans: boolean, duplicated_replacedSymbolSpans: boolean): boolean {
        if ((!duplicated_rangeBefore) && (value?.hasOwnProperty("rangeBefore"))) {
            return true
        }
        else if ((!duplicated_replacedSpans) && (value?.hasOwnProperty("replacedSpans"))) {
            return true
        }
        else if ((!duplicated_replacedImageSpans) && (value?.hasOwnProperty("replacedImageSpans"))) {
            return true
        }
        else if ((!duplicated_replacedSymbolSpans) && (value?.hasOwnProperty("replacedSymbolSpans"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RichEditorChangeValue")
        }
    }
    static isRichEditorController(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof RichEditorController")
    }
    static isRichEditorDeleteDirection(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (RichEditorDeleteDirection.BACKWARD)) {
            return true
        }
        else if ((value) === (RichEditorDeleteDirection.FORWARD)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RichEditorDeleteDirection")
        }
    }
    static isRichEditorDeleteValue(value: object|string|number|undefined|null|boolean, duplicated_offset: boolean, duplicated_direction: boolean, duplicated_length: boolean, duplicated_richEditorDeleteSpans: boolean): boolean {
        if ((!duplicated_offset) && (value?.hasOwnProperty("offset"))) {
            return true
        }
        else if ((!duplicated_direction) && (value?.hasOwnProperty("direction"))) {
            return true
        }
        else if ((!duplicated_length) && (value?.hasOwnProperty("length"))) {
            return true
        }
        else if ((!duplicated_richEditorDeleteSpans) && (value?.hasOwnProperty("richEditorDeleteSpans"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RichEditorDeleteValue")
        }
    }
    static isRichEditorGesture(value: object|string|number|undefined|null|boolean, duplicated_onClick: boolean, duplicated_onLongPress: boolean): boolean {
        if ((!duplicated_onClick) && (value?.hasOwnProperty("onClick"))) {
            return true
        }
        else if ((!duplicated_onLongPress) && (value?.hasOwnProperty("onLongPress"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RichEditorGesture")
        }
    }
    static isRichEditorImageSpan(value: object|string|number|undefined|null|boolean, duplicated_spanPosition: boolean, duplicated_value: boolean, duplicated_imageStyle: boolean): boolean {
        if ((!duplicated_spanPosition) && (value?.hasOwnProperty("spanPosition"))) {
            return true
        }
        else if ((!duplicated_value) && (value?.hasOwnProperty("value"))) {
            return true
        }
        else if ((!duplicated_imageStyle) && (value?.hasOwnProperty("imageStyle"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RichEditorImageSpan")
        }
    }
    static isRichEditorImageSpanOptions(value: object|string|number|undefined|null|boolean, duplicated_offset: boolean, duplicated_imageStyle: boolean, duplicated_gesture: boolean): boolean {
        if ((!duplicated_offset) && (value?.hasOwnProperty("offset"))) {
            return true
        }
        else if ((!duplicated_imageStyle) && (value?.hasOwnProperty("imageStyle"))) {
            return true
        }
        else if ((!duplicated_gesture) && (value?.hasOwnProperty("gesture"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RichEditorImageSpanOptions")
        }
    }
    static isRichEditorImageSpanResult(value: object|string|number|undefined|null|boolean, duplicated_spanPosition: boolean, duplicated_valuePixelMap: boolean, duplicated_valueResourceStr: boolean, duplicated_imageStyle: boolean, duplicated_offsetInSpan: boolean): boolean {
        if ((!duplicated_spanPosition) && (value?.hasOwnProperty("spanPosition"))) {
            return true
        }
        else if ((!duplicated_imageStyle) && (value?.hasOwnProperty("imageStyle"))) {
            return true
        }
        else if ((!duplicated_offsetInSpan) && (value?.hasOwnProperty("offsetInSpan"))) {
            return true
        }
        else if ((!duplicated_valuePixelMap) && (value?.hasOwnProperty("valuePixelMap"))) {
            return true
        }
        else if ((!duplicated_valueResourceStr) && (value?.hasOwnProperty("valueResourceStr"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RichEditorImageSpanResult")
        }
    }
    static isRichEditorImageSpanStyle(value: object|string|number|undefined|null|boolean, duplicated_size: boolean, duplicated_verticalAlign: boolean, duplicated_objectFit: boolean, duplicated_layoutStyle: boolean): boolean {
        if ((!duplicated_size) && (value?.hasOwnProperty("size"))) {
            return true
        }
        else if ((!duplicated_verticalAlign) && (value?.hasOwnProperty("verticalAlign"))) {
            return true
        }
        else if ((!duplicated_objectFit) && (value?.hasOwnProperty("objectFit"))) {
            return true
        }
        else if ((!duplicated_layoutStyle) && (value?.hasOwnProperty("layoutStyle"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RichEditorImageSpanStyle")
        }
    }
    static isRichEditorImageSpanStyleResult(value: object|string|number|undefined|null|boolean, duplicated_size: boolean, duplicated_verticalAlign: boolean, duplicated_objectFit: boolean, duplicated_layoutStyle: boolean): boolean {
        if ((!duplicated_size) && (value?.hasOwnProperty("size"))) {
            return true
        }
        else if ((!duplicated_verticalAlign) && (value?.hasOwnProperty("verticalAlign"))) {
            return true
        }
        else if ((!duplicated_objectFit) && (value?.hasOwnProperty("objectFit"))) {
            return true
        }
        else if ((!duplicated_layoutStyle) && (value?.hasOwnProperty("layoutStyle"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RichEditorImageSpanStyleResult")
        }
    }
    static isRichEditorInsertValue(value: object|string|number|undefined|null|boolean, duplicated_insertOffset: boolean, duplicated_insertValue: boolean, duplicated_previewText: boolean): boolean {
        if ((!duplicated_insertOffset) && (value?.hasOwnProperty("insertOffset"))) {
            return true
        }
        else if ((!duplicated_insertValue) && (value?.hasOwnProperty("insertValue"))) {
            return true
        }
        else if ((!duplicated_previewText) && (value?.hasOwnProperty("previewText"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RichEditorInsertValue")
        }
    }
    static isRichEditorInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof RichEditorInterface")
    }
    static isRichEditorLayoutStyle(value: object|string|number|undefined|null|boolean, duplicated_margin: boolean, duplicated_borderRadius: boolean): boolean {
        if ((!duplicated_margin) && (value?.hasOwnProperty("margin"))) {
            return true
        }
        else if ((!duplicated_borderRadius) && (value?.hasOwnProperty("borderRadius"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RichEditorLayoutStyle")
        }
    }
    static isRichEditorOptions(value: object|string|number|undefined|null|boolean, duplicated_controller: boolean): boolean {
        if ((!duplicated_controller) && (value?.hasOwnProperty("controller"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RichEditorOptions")
        }
    }
    static isRichEditorParagraphResult(value: object|string|number|undefined|null|boolean, duplicated_style: boolean, duplicated_range: boolean): boolean {
        if ((!duplicated_style) && (value?.hasOwnProperty("style"))) {
            return true
        }
        else if ((!duplicated_range) && (value?.hasOwnProperty("range"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RichEditorParagraphResult")
        }
    }
    static isRichEditorParagraphStyle(value: object|string|number|undefined|null|boolean, duplicated_textAlign: boolean, duplicated_leadingMargin: boolean, duplicated_wordBreak: boolean, duplicated_lineBreakStrategy: boolean): boolean {
        if ((!duplicated_textAlign) && (value?.hasOwnProperty("textAlign"))) {
            return true
        }
        else if ((!duplicated_leadingMargin) && (value?.hasOwnProperty("leadingMargin"))) {
            return true
        }
        else if ((!duplicated_wordBreak) && (value?.hasOwnProperty("wordBreak"))) {
            return true
        }
        else if ((!duplicated_lineBreakStrategy) && (value?.hasOwnProperty("lineBreakStrategy"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RichEditorParagraphStyle")
        }
    }
    static isRichEditorParagraphStyleOptions(value: object|string|number|undefined|null|boolean, duplicated_style: boolean): boolean {
        if ((!duplicated_style) && (value?.hasOwnProperty("style"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RichEditorParagraphStyleOptions")
        }
    }
    static isRichEditorRange(value: object|string|number|undefined|null|boolean, duplicated_start: boolean, duplicated_end: boolean): boolean {
        if ((!duplicated_start) && (value?.hasOwnProperty("start"))) {
            return true
        }
        else if ((!duplicated_end) && (value?.hasOwnProperty("end"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RichEditorRange")
        }
    }
    static isRichEditorResponseType(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (RichEditorResponseType.RIGHT_CLICK)) {
            return true
        }
        else if ((value) === (RichEditorResponseType.LONG_PRESS)) {
            return true
        }
        else if ((value) === (RichEditorResponseType.SELECT)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RichEditorResponseType")
        }
    }
    static isRichEditorSelection(value: object|string|number|undefined|null|boolean, duplicated_selection: boolean, duplicated_spans: boolean): boolean {
        if ((!duplicated_selection) && (value?.hasOwnProperty("selection"))) {
            return true
        }
        else if ((!duplicated_spans) && (value?.hasOwnProperty("spans"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RichEditorSelection")
        }
    }
    static isRichEditorSpanPosition(value: object|string|number|undefined|null|boolean, duplicated_spanIndex: boolean, duplicated_spanRange: boolean): boolean {
        if ((!duplicated_spanIndex) && (value?.hasOwnProperty("spanIndex"))) {
            return true
        }
        else if ((!duplicated_spanRange) && (value?.hasOwnProperty("spanRange"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RichEditorSpanPosition")
        }
    }
    static isRichEditorSpanStyleOptions(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof RichEditorSpanStyleOptions")
    }
    static isRichEditorSpanType(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (RichEditorSpanType.TEXT)) {
            return true
        }
        else if ((value) === (RichEditorSpanType.IMAGE)) {
            return true
        }
        else if ((value) === (RichEditorSpanType.MIXED)) {
            return true
        }
        else if ((value) === (RichEditorSpanType.BUILDER)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RichEditorSpanType")
        }
    }
    static isRichEditorStyledStringController(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof RichEditorStyledStringController")
    }
    static isRichEditorStyledStringOptions(value: object|string|number|undefined|null|boolean, duplicated_controller: boolean): boolean {
        if ((!duplicated_controller) && (value?.hasOwnProperty("controller"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RichEditorStyledStringOptions")
        }
    }
    static isRichEditorSymbolSpanOptions(value: object|string|number|undefined|null|boolean, duplicated_offset: boolean, duplicated_style: boolean): boolean {
        if ((!duplicated_offset) && (value?.hasOwnProperty("offset"))) {
            return true
        }
        else if ((!duplicated_style) && (value?.hasOwnProperty("style"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RichEditorSymbolSpanOptions")
        }
    }
    static isRichEditorSymbolSpanStyle(value: object|string|number|undefined|null|boolean, duplicated_fontSize: boolean, duplicated_fontColor: boolean, duplicated_fontWeight: boolean, duplicated_effectStrategy: boolean, duplicated_renderingStrategy: boolean): boolean {
        if ((!duplicated_fontSize) && (value?.hasOwnProperty("fontSize"))) {
            return true
        }
        else if ((!duplicated_fontColor) && (value?.hasOwnProperty("fontColor"))) {
            return true
        }
        else if ((!duplicated_fontWeight) && (value?.hasOwnProperty("fontWeight"))) {
            return true
        }
        else if ((!duplicated_effectStrategy) && (value?.hasOwnProperty("effectStrategy"))) {
            return true
        }
        else if ((!duplicated_renderingStrategy) && (value?.hasOwnProperty("renderingStrategy"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RichEditorSymbolSpanStyle")
        }
    }
    static isRichEditorSymbolSpanStyleResult(value: object|string|number|undefined|null|boolean, duplicated_fontSize: boolean, duplicated_fontColor: boolean, duplicated_fontWeight: boolean, duplicated_effectStrategy: boolean, duplicated_renderingStrategy: boolean): boolean {
        if ((!duplicated_fontSize) && (value?.hasOwnProperty("fontSize"))) {
            return true
        }
        else if ((!duplicated_fontColor) && (value?.hasOwnProperty("fontColor"))) {
            return true
        }
        else if ((!duplicated_fontWeight) && (value?.hasOwnProperty("fontWeight"))) {
            return true
        }
        else if ((!duplicated_effectStrategy) && (value?.hasOwnProperty("effectStrategy"))) {
            return true
        }
        else if ((!duplicated_renderingStrategy) && (value?.hasOwnProperty("renderingStrategy"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RichEditorSymbolSpanStyleResult")
        }
    }
    static isRichEditorTextSpan(value: object|string|number|undefined|null|boolean, duplicated_spanPosition: boolean, duplicated_value: boolean, duplicated_textStyle: boolean): boolean {
        if ((!duplicated_spanPosition) && (value?.hasOwnProperty("spanPosition"))) {
            return true
        }
        else if ((!duplicated_value) && (value?.hasOwnProperty("value"))) {
            return true
        }
        else if ((!duplicated_textStyle) && (value?.hasOwnProperty("textStyle"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RichEditorTextSpan")
        }
    }
    static isRichEditorTextSpanOptions(value: object|string|number|undefined|null|boolean, duplicated_offset: boolean, duplicated_style: boolean, duplicated_paragraphStyle: boolean, duplicated_gesture: boolean): boolean {
        if ((!duplicated_offset) && (value?.hasOwnProperty("offset"))) {
            return true
        }
        else if ((!duplicated_style) && (value?.hasOwnProperty("style"))) {
            return true
        }
        else if ((!duplicated_paragraphStyle) && (value?.hasOwnProperty("paragraphStyle"))) {
            return true
        }
        else if ((!duplicated_gesture) && (value?.hasOwnProperty("gesture"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RichEditorTextSpanOptions")
        }
    }
    static isRichEditorTextSpanResult(value: object|string|number|undefined|null|boolean, duplicated_spanPosition: boolean, duplicated_value: boolean, duplicated_textStyle: boolean, duplicated_offsetInSpan: boolean, duplicated_symbolSpanStyle: boolean, duplicated_valueResource: boolean, duplicated_paragraphStyle: boolean, duplicated_previewText: boolean): boolean {
        if ((!duplicated_spanPosition) && (value?.hasOwnProperty("spanPosition"))) {
            return true
        }
        else if ((!duplicated_value) && (value?.hasOwnProperty("value"))) {
            return true
        }
        else if ((!duplicated_textStyle) && (value?.hasOwnProperty("textStyle"))) {
            return true
        }
        else if ((!duplicated_offsetInSpan) && (value?.hasOwnProperty("offsetInSpan"))) {
            return true
        }
        else if ((!duplicated_symbolSpanStyle) && (value?.hasOwnProperty("symbolSpanStyle"))) {
            return true
        }
        else if ((!duplicated_valueResource) && (value?.hasOwnProperty("valueResource"))) {
            return true
        }
        else if ((!duplicated_paragraphStyle) && (value?.hasOwnProperty("paragraphStyle"))) {
            return true
        }
        else if ((!duplicated_previewText) && (value?.hasOwnProperty("previewText"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RichEditorTextSpanResult")
        }
    }
    static isRichEditorTextStyle(value: object|string|number|undefined|null|boolean, duplicated_fontColor: boolean, duplicated_fontSize: boolean, duplicated_fontStyle: boolean, duplicated_fontWeight: boolean, duplicated_fontFamily: boolean, duplicated_decoration: boolean, duplicated_textShadow: boolean, duplicated_letterSpacing: boolean, duplicated_lineHeight: boolean, duplicated_fontFeature: boolean): boolean {
        if ((!duplicated_fontColor) && (value?.hasOwnProperty("fontColor"))) {
            return true
        }
        else if ((!duplicated_fontSize) && (value?.hasOwnProperty("fontSize"))) {
            return true
        }
        else if ((!duplicated_fontStyle) && (value?.hasOwnProperty("fontStyle"))) {
            return true
        }
        else if ((!duplicated_fontWeight) && (value?.hasOwnProperty("fontWeight"))) {
            return true
        }
        else if ((!duplicated_fontFamily) && (value?.hasOwnProperty("fontFamily"))) {
            return true
        }
        else if ((!duplicated_decoration) && (value?.hasOwnProperty("decoration"))) {
            return true
        }
        else if ((!duplicated_textShadow) && (value?.hasOwnProperty("textShadow"))) {
            return true
        }
        else if ((!duplicated_letterSpacing) && (value?.hasOwnProperty("letterSpacing"))) {
            return true
        }
        else if ((!duplicated_lineHeight) && (value?.hasOwnProperty("lineHeight"))) {
            return true
        }
        else if ((!duplicated_fontFeature) && (value?.hasOwnProperty("fontFeature"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RichEditorTextStyle")
        }
    }
    static isRichEditorTextStyleResult(value: object|string|number|undefined|null|boolean, duplicated_fontColor: boolean, duplicated_fontSize: boolean, duplicated_fontStyle: boolean, duplicated_fontWeight: boolean, duplicated_fontFamily: boolean, duplicated_decoration: boolean, duplicated_textShadow: boolean, duplicated_letterSpacing: boolean, duplicated_lineHeight: boolean, duplicated_fontFeature: boolean): boolean {
        if ((!duplicated_fontColor) && (value?.hasOwnProperty("fontColor"))) {
            return true
        }
        else if ((!duplicated_fontSize) && (value?.hasOwnProperty("fontSize"))) {
            return true
        }
        else if ((!duplicated_fontStyle) && (value?.hasOwnProperty("fontStyle"))) {
            return true
        }
        else if ((!duplicated_fontWeight) && (value?.hasOwnProperty("fontWeight"))) {
            return true
        }
        else if ((!duplicated_fontFamily) && (value?.hasOwnProperty("fontFamily"))) {
            return true
        }
        else if ((!duplicated_decoration) && (value?.hasOwnProperty("decoration"))) {
            return true
        }
        else if ((!duplicated_textShadow) && (value?.hasOwnProperty("textShadow"))) {
            return true
        }
        else if ((!duplicated_letterSpacing) && (value?.hasOwnProperty("letterSpacing"))) {
            return true
        }
        else if ((!duplicated_lineHeight) && (value?.hasOwnProperty("lineHeight"))) {
            return true
        }
        else if ((!duplicated_fontFeature) && (value?.hasOwnProperty("fontFeature"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RichEditorTextStyleResult")
        }
    }
    static isRichEditorUpdateImageSpanStyleOptions(value: object|string|number|undefined|null|boolean, duplicated_imageStyle: boolean): boolean {
        if ((!duplicated_imageStyle) && (value?.hasOwnProperty("imageStyle"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RichEditorUpdateImageSpanStyleOptions")
        }
    }
    static isRichEditorUpdateSymbolSpanStyleOptions(value: object|string|number|undefined|null|boolean, duplicated_symbolStyle: boolean): boolean {
        if ((!duplicated_symbolStyle) && (value?.hasOwnProperty("symbolStyle"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RichEditorUpdateSymbolSpanStyleOptions")
        }
    }
    static isRichEditorUpdateTextSpanStyleOptions(value: object|string|number|undefined|null|boolean, duplicated_textStyle: boolean): boolean {
        if ((!duplicated_textStyle) && (value?.hasOwnProperty("textStyle"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RichEditorUpdateTextSpanStyleOptions")
        }
    }
    static isRichTextAttribute(value: object|string|number|undefined|null|boolean, duplicated_onStart: boolean, duplicated_onComplete: boolean): boolean {
        if ((!duplicated_onStart) && (value?.hasOwnProperty("onStart"))) {
            return true
        }
        else if ((!duplicated_onComplete) && (value?.hasOwnProperty("onComplete"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RichTextAttribute")
        }
    }
    static isRichTextInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof RichTextInterface")
    }
    static isRingStyleOptions(value: object|string|number|undefined|null|boolean, duplicated_strokeWidth: boolean, duplicated_shadow: boolean, duplicated_status: boolean): boolean {
        if ((!duplicated_strokeWidth) && (value?.hasOwnProperty("strokeWidth"))) {
            return true
        }
        else if ((!duplicated_shadow) && (value?.hasOwnProperty("shadow"))) {
            return true
        }
        else if ((!duplicated_status) && (value?.hasOwnProperty("status"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RingStyleOptions")
        }
    }
    static isRoot(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof Root")
    }
    static isRootSceneAttribute(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof RootSceneAttribute")
    }
    static isRootSceneInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof RootSceneInterface")
    }
    static isRootSceneSession(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof RootSceneSession")
    }
    static isRotateOptions(value: object|string|number|undefined|null|boolean, duplicated_x: boolean, duplicated_y: boolean, duplicated_z: boolean, duplicated_centerX: boolean, duplicated_centerY: boolean, duplicated_centerZ: boolean, duplicated_perspective: boolean, duplicated_angle: boolean): boolean {
        if ((!duplicated_angle) && (value?.hasOwnProperty("angle"))) {
            return true
        }
        else if ((!duplicated_x) && (value?.hasOwnProperty("x"))) {
            return true
        }
        else if ((!duplicated_y) && (value?.hasOwnProperty("y"))) {
            return true
        }
        else if ((!duplicated_z) && (value?.hasOwnProperty("z"))) {
            return true
        }
        else if ((!duplicated_centerX) && (value?.hasOwnProperty("centerX"))) {
            return true
        }
        else if ((!duplicated_centerY) && (value?.hasOwnProperty("centerY"))) {
            return true
        }
        else if ((!duplicated_centerZ) && (value?.hasOwnProperty("centerZ"))) {
            return true
        }
        else if ((!duplicated_perspective) && (value?.hasOwnProperty("perspective"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RotateOptions")
        }
    }
    static isRotationGestureEvent(value: object|string|number|undefined|null|boolean, duplicated_angle: boolean): boolean {
        if ((!duplicated_angle) && (value?.hasOwnProperty("angle"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RotationGestureEvent")
        }
    }
    static isRotationGestureHandler(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof RotationGestureHandler")
    }
    static isRotationGestureHandlerOptions(value: object|string|number|undefined|null|boolean, duplicated_fingers: boolean, duplicated_angle: boolean): boolean {
        if ((!duplicated_fingers) && (value?.hasOwnProperty("fingers"))) {
            return true
        }
        else if ((!duplicated_angle) && (value?.hasOwnProperty("angle"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RotationGestureHandlerOptions")
        }
    }
    static isRotationGestureInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof RotationGestureInterface")
    }
    static isRoundedRectOptions(value: object|string|number|undefined|null|boolean, duplicated_width: boolean, duplicated_height: boolean, duplicated_radiusWidth: boolean, duplicated_radiusHeight: boolean): boolean {
        if ((!duplicated_width) && (value?.hasOwnProperty("width"))) {
            return true
        }
        else if ((!duplicated_height) && (value?.hasOwnProperty("height"))) {
            return true
        }
        else if ((!duplicated_radiusWidth) && (value?.hasOwnProperty("radiusWidth"))) {
            return true
        }
        else if ((!duplicated_radiusHeight) && (value?.hasOwnProperty("radiusHeight"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RoundedRectOptions")
        }
    }
    static isRoundRectShapeOptions(value: object|string|number|undefined|null|boolean, duplicated_radiusWidth: boolean, duplicated_radiusHeight: boolean): boolean {
        if ((!duplicated_radiusWidth) && (value?.hasOwnProperty("radiusWidth"))) {
            return true
        }
        else if ((!duplicated_radiusHeight) && (value?.hasOwnProperty("radiusHeight"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RoundRectShapeOptions")
        }
    }
    static isRouteInfo(value: object|string|number|undefined|null|boolean, duplicated_name: boolean, duplicated_param: boolean): boolean {
        if ((!duplicated_name) && (value?.hasOwnProperty("name"))) {
            return true
        }
        else if ((!duplicated_param) && (value?.hasOwnProperty("param"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RouteInfo")
        }
    }
    static isRouteMapConfig(value: object|string|number|undefined|null|boolean, duplicated_name: boolean, duplicated_pageSourceFile: boolean, duplicated_data: boolean): boolean {
        if ((!duplicated_name) && (value?.hasOwnProperty("name"))) {
            return true
        }
        else if ((!duplicated_pageSourceFile) && (value?.hasOwnProperty("pageSourceFile"))) {
            return true
        }
        else if ((!duplicated_data) && (value?.hasOwnProperty("data"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RouteMapConfig")
        }
    }
    static isRouterPageInfo(value: object|string|number|undefined|null|boolean, duplicated__RouterPageInfoStub: boolean): boolean {
        if ((!duplicated__RouterPageInfoStub) && (value?.hasOwnProperty("_RouterPageInfoStub"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RouterPageInfo")
        }
    }
    static isRouteType(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (RouteType.None)) {
            return true
        }
        else if ((value) === (RouteType.Push)) {
            return true
        }
        else if ((value) === (RouteType.Pop)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RouteType")
        }
    }
    static isRowAttribute(value: object|string|number|undefined|null|boolean, duplicated_alignItems: boolean, duplicated_justifyContent: boolean, duplicated_pointLight: boolean, duplicated_reverse: boolean): boolean {
        if ((!duplicated_alignItems) && (value?.hasOwnProperty("alignItems"))) {
            return true
        }
        else if ((!duplicated_justifyContent) && (value?.hasOwnProperty("justifyContent"))) {
            return true
        }
        else if ((!duplicated_pointLight) && (value?.hasOwnProperty("pointLight"))) {
            return true
        }
        else if ((!duplicated_reverse) && (value?.hasOwnProperty("reverse"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RowAttribute")
        }
    }
    static isRowInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof RowInterface")
    }
    static isRowOptions(value: object|string|number|undefined|null|boolean, duplicated_space: boolean): boolean {
        if ((!duplicated_space) && (value?.hasOwnProperty("space"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RowOptions")
        }
    }
    static isRowSplitAttribute(value: object|string|number|undefined|null|boolean, duplicated_resizeable: boolean): boolean {
        if ((!duplicated_resizeable) && (value?.hasOwnProperty("resizeable"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RowSplitAttribute")
        }
    }
    static isRowSplitInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof RowSplitInterface")
    }
    static isRRect(value: object|string|number|undefined|null|boolean, duplicated_left: boolean, duplicated_top: boolean, duplicated_width: boolean, duplicated_height: boolean, duplicated_radius: boolean): boolean {
        if ((!duplicated_left) && (value?.hasOwnProperty("left"))) {
            return true
        }
        else if ((!duplicated_top) && (value?.hasOwnProperty("top"))) {
            return true
        }
        else if ((!duplicated_width) && (value?.hasOwnProperty("width"))) {
            return true
        }
        else if ((!duplicated_height) && (value?.hasOwnProperty("height"))) {
            return true
        }
        else if ((!duplicated_radius) && (value?.hasOwnProperty("radius"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RRect")
        }
    }
    static isSafeAreaEdge(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (SafeAreaEdge.TOP)) {
            return true
        }
        else if ((value) === (SafeAreaEdge.BOTTOM)) {
            return true
        }
        else if ((value) === (SafeAreaEdge.START)) {
            return true
        }
        else if ((value) === (SafeAreaEdge.END)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SafeAreaEdge")
        }
    }
    static isSafeAreaType(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (SafeAreaType.SYSTEM)) {
            return true
        }
        else if ((value) === (SafeAreaType.CUTOUT)) {
            return true
        }
        else if ((value) === (SafeAreaType.KEYBOARD)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SafeAreaType")
        }
    }
    static isSaveButtonAttribute(value: object|string|number|undefined|null|boolean, duplicated_onClick: boolean): boolean {
        if ((!duplicated_onClick) && (value?.hasOwnProperty("onClick"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SaveButtonAttribute")
        }
    }
    static isSaveButtonInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof SaveButtonInterface")
    }
    static isSaveButtonOnClickResult(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (SaveButtonOnClickResult.SUCCESS)) {
            return true
        }
        else if ((value) === (SaveButtonOnClickResult.TEMPORARY_AUTHORIZATION_FAILED)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SaveButtonOnClickResult")
        }
    }
    static isSaveButtonOptions(value: object|string|number|undefined|null|boolean, duplicated_icon: boolean, duplicated_text: boolean, duplicated_buttonType: boolean): boolean {
        if ((!duplicated_icon) && (value?.hasOwnProperty("icon"))) {
            return true
        }
        else if ((!duplicated_text) && (value?.hasOwnProperty("text"))) {
            return true
        }
        else if ((!duplicated_buttonType) && (value?.hasOwnProperty("buttonType"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SaveButtonOptions")
        }
    }
    static isSaveDescription(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (SaveDescription.DOWNLOAD)) {
            return true
        }
        else if ((value) === (SaveDescription.DOWNLOAD_FILE)) {
            return true
        }
        else if ((value) === (SaveDescription.SAVE)) {
            return true
        }
        else if ((value) === (SaveDescription.SAVE_IMAGE)) {
            return true
        }
        else if ((value) === (SaveDescription.SAVE_FILE)) {
            return true
        }
        else if ((value) === (SaveDescription.DOWNLOAD_AND_SHARE)) {
            return true
        }
        else if ((value) === (SaveDescription.RECEIVE)) {
            return true
        }
        else if ((value) === (SaveDescription.CONTINUE_TO_RECEIVE)) {
            return true
        }
        else if ((value) === (SaveDescription.SAVE_TO_GALLERY)) {
            return true
        }
        else if ((value) === (SaveDescription.EXPORT_TO_GALLERY)) {
            return true
        }
        else if ((value) === (SaveDescription.QUICK_SAVE_TO_GALLERY)) {
            return true
        }
        else if ((value) === (SaveDescription.RESAVE_TO_GALLERY)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SaveDescription")
        }
    }
    static isSaveIconStyle(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (SaveIconStyle.FULL_FILLED)) {
            return true
        }
        else if ((value) === (SaveIconStyle.LINES)) {
            return true
        }
        else if ((value) === (SaveIconStyle.PICTURE)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SaveIconStyle")
        }
    }
    static isScaleOptions(value: object|string|number|undefined|null|boolean, duplicated_x: boolean, duplicated_y: boolean, duplicated_z: boolean, duplicated_centerX: boolean, duplicated_centerY: boolean): boolean {
        if ((!duplicated_x) && (value?.hasOwnProperty("x"))) {
            return true
        }
        else if ((!duplicated_y) && (value?.hasOwnProperty("y"))) {
            return true
        }
        else if ((!duplicated_z) && (value?.hasOwnProperty("z"))) {
            return true
        }
        else if ((!duplicated_centerX) && (value?.hasOwnProperty("centerX"))) {
            return true
        }
        else if ((!duplicated_centerY) && (value?.hasOwnProperty("centerY"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ScaleOptions")
        }
    }
    static isScaleRingStyleOptions(value: object|string|number|undefined|null|boolean, duplicated_strokeWidth: boolean, duplicated_scaleWidth: boolean, duplicated_scaleCount: boolean): boolean {
        if ((!duplicated_strokeWidth) && (value?.hasOwnProperty("strokeWidth"))) {
            return true
        }
        else if ((!duplicated_scaleWidth) && (value?.hasOwnProperty("scaleWidth"))) {
            return true
        }
        else if ((!duplicated_scaleCount) && (value?.hasOwnProperty("scaleCount"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ScaleRingStyleOptions")
        }
    }
    static isScaleSymbolEffect(value: object|string|number|undefined|null|boolean, duplicated_scope: boolean, duplicated_direction: boolean): boolean {
        if ((!duplicated_scope) && (value?.hasOwnProperty("scope"))) {
            return true
        }
        else if ((!duplicated_direction) && (value?.hasOwnProperty("direction"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ScaleSymbolEffect")
        }
    }
    static isScanEffectOptions(value: object|string|number|undefined|null|boolean, duplicated_enableScanEffect: boolean): boolean {
        if ((!duplicated_enableScanEffect) && (value?.hasOwnProperty("enableScanEffect"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ScanEffectOptions")
        }
    }
    static isScene(value: object|string|number|undefined|null|boolean, duplicated__SceneStub: boolean): boolean {
        if ((!duplicated__SceneStub) && (value?.hasOwnProperty("_SceneStub"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof Scene")
        }
    }
    static isSceneOptions(value: object|string|number|undefined|null|boolean, duplicated_scene: boolean, duplicated_modelType: boolean): boolean {
        if ((!duplicated_scene) && (value?.hasOwnProperty("scene"))) {
            return true
        }
        else if ((!duplicated_modelType) && (value?.hasOwnProperty("modelType"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SceneOptions")
        }
    }
    static isScreenAttribute(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof ScreenAttribute")
    }
    static isScreenCaptureConfig(value: object|string|number|undefined|null|boolean, duplicated_captureMode: boolean): boolean {
        if ((!duplicated_captureMode) && (value?.hasOwnProperty("captureMode"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ScreenCaptureConfig")
        }
    }
    static isScreenCaptureHandler(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof ScreenCaptureHandler")
    }
    static isScreenInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof ScreenInterface")
    }
    static isScriptItem(value: object|string|number|undefined|null|boolean, duplicated_script: boolean, duplicated_scriptRules: boolean): boolean {
        if ((!duplicated_script) && (value?.hasOwnProperty("script"))) {
            return true
        }
        else if ((!duplicated_scriptRules) && (value?.hasOwnProperty("scriptRules"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ScriptItem")
        }
    }
    static isScrollableBarModeOptions(value: object|string|number|undefined|null|boolean, duplicated_margin: boolean, duplicated_nonScrollableLayoutStyle: boolean): boolean {
        if ((!duplicated_margin) && (value?.hasOwnProperty("margin"))) {
            return true
        }
        else if ((!duplicated_nonScrollableLayoutStyle) && (value?.hasOwnProperty("nonScrollableLayoutStyle"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ScrollableBarModeOptions")
        }
    }
    static isScrollableCommonMethod(value: object|string|number|undefined|null|boolean, duplicated_scrollBar: boolean, duplicated_scrollBarColor: boolean, duplicated_scrollBarWidth: boolean, duplicated_nestedScroll: boolean, duplicated_enableScrollInteraction: boolean, duplicated_friction: boolean, duplicated_onScroll: boolean, duplicated_onReachStart: boolean, duplicated_onReachEnd: boolean, duplicated_onScrollStart: boolean, duplicated_onScrollStop: boolean, duplicated_flingSpeedLimit: boolean, duplicated_clipContent: boolean): boolean {
        if ((!duplicated_scrollBar) && (value?.hasOwnProperty("scrollBar"))) {
            return true
        }
        else if ((!duplicated_scrollBarColor) && (value?.hasOwnProperty("scrollBarColor"))) {
            return true
        }
        else if ((!duplicated_scrollBarWidth) && (value?.hasOwnProperty("scrollBarWidth"))) {
            return true
        }
        else if ((!duplicated_nestedScroll) && (value?.hasOwnProperty("nestedScroll"))) {
            return true
        }
        else if ((!duplicated_enableScrollInteraction) && (value?.hasOwnProperty("enableScrollInteraction"))) {
            return true
        }
        else if ((!duplicated_friction) && (value?.hasOwnProperty("friction"))) {
            return true
        }
        else if ((!duplicated_onScroll) && (value?.hasOwnProperty("onScroll"))) {
            return true
        }
        else if ((!duplicated_onReachStart) && (value?.hasOwnProperty("onReachStart"))) {
            return true
        }
        else if ((!duplicated_onReachEnd) && (value?.hasOwnProperty("onReachEnd"))) {
            return true
        }
        else if ((!duplicated_onScrollStart) && (value?.hasOwnProperty("onScrollStart"))) {
            return true
        }
        else if ((!duplicated_onScrollStop) && (value?.hasOwnProperty("onScrollStop"))) {
            return true
        }
        else if ((!duplicated_flingSpeedLimit) && (value?.hasOwnProperty("flingSpeedLimit"))) {
            return true
        }
        else if ((!duplicated_clipContent) && (value?.hasOwnProperty("clipContent"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ScrollableCommonMethod")
        }
    }
    static isScrollableTargetInfo(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof ScrollableTargetInfo")
    }
    static isScrollAlign(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (ScrollAlign.START)) {
            return true
        }
        else if ((value) === (ScrollAlign.CENTER)) {
            return true
        }
        else if ((value) === (ScrollAlign.END)) {
            return true
        }
        else if ((value) === (ScrollAlign.AUTO)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ScrollAlign")
        }
    }
    static isScrollAnimationOptions(value: object|string|number|undefined|null|boolean, duplicated_duration: boolean, duplicated_curve: boolean, duplicated_canOverScroll: boolean): boolean {
        if ((!duplicated_duration) && (value?.hasOwnProperty("duration"))) {
            return true
        }
        else if ((!duplicated_curve) && (value?.hasOwnProperty("curve"))) {
            return true
        }
        else if ((!duplicated_canOverScroll) && (value?.hasOwnProperty("canOverScroll"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ScrollAnimationOptions")
        }
    }
    static isScrollAttribute(value: object|string|number|undefined|null|boolean, duplicated_scrollable: boolean, duplicated_onScroll: boolean, duplicated_onWillScroll: boolean, duplicated_onDidScroll: boolean, duplicated_onScrollEdge: boolean, duplicated_onScrollStart: boolean, duplicated_onScrollEnd: boolean, duplicated_onScrollStop: boolean, duplicated_scrollBar: boolean, duplicated_scrollBarColor: boolean, duplicated_scrollBarWidth: boolean, duplicated_onScrollFrameBegin: boolean, duplicated_nestedScroll: boolean, duplicated_enableScrollInteraction: boolean, duplicated_friction: boolean, duplicated_scrollSnap: boolean, duplicated_enablePaging: boolean, duplicated_initialOffset: boolean): boolean {
        if ((!duplicated_scrollable) && (value?.hasOwnProperty("scrollable"))) {
            return true
        }
        else if ((!duplicated_onScroll) && (value?.hasOwnProperty("onScroll"))) {
            return true
        }
        else if ((!duplicated_onWillScroll) && (value?.hasOwnProperty("onWillScroll"))) {
            return true
        }
        else if ((!duplicated_onDidScroll) && (value?.hasOwnProperty("onDidScroll"))) {
            return true
        }
        else if ((!duplicated_onScrollEdge) && (value?.hasOwnProperty("onScrollEdge"))) {
            return true
        }
        else if ((!duplicated_onScrollStart) && (value?.hasOwnProperty("onScrollStart"))) {
            return true
        }
        else if ((!duplicated_onScrollEnd) && (value?.hasOwnProperty("onScrollEnd"))) {
            return true
        }
        else if ((!duplicated_onScrollStop) && (value?.hasOwnProperty("onScrollStop"))) {
            return true
        }
        else if ((!duplicated_scrollBar) && (value?.hasOwnProperty("scrollBar"))) {
            return true
        }
        else if ((!duplicated_scrollBarColor) && (value?.hasOwnProperty("scrollBarColor"))) {
            return true
        }
        else if ((!duplicated_scrollBarWidth) && (value?.hasOwnProperty("scrollBarWidth"))) {
            return true
        }
        else if ((!duplicated_onScrollFrameBegin) && (value?.hasOwnProperty("onScrollFrameBegin"))) {
            return true
        }
        else if ((!duplicated_nestedScroll) && (value?.hasOwnProperty("nestedScroll"))) {
            return true
        }
        else if ((!duplicated_enableScrollInteraction) && (value?.hasOwnProperty("enableScrollInteraction"))) {
            return true
        }
        else if ((!duplicated_friction) && (value?.hasOwnProperty("friction"))) {
            return true
        }
        else if ((!duplicated_scrollSnap) && (value?.hasOwnProperty("scrollSnap"))) {
            return true
        }
        else if ((!duplicated_enablePaging) && (value?.hasOwnProperty("enablePaging"))) {
            return true
        }
        else if ((!duplicated_initialOffset) && (value?.hasOwnProperty("initialOffset"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ScrollAttribute")
        }
    }
    static isScrollBarAttribute(value: object|string|number|undefined|null|boolean, duplicated_enableNestedScroll: boolean): boolean {
        if ((!duplicated_enableNestedScroll) && (value?.hasOwnProperty("enableNestedScroll"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ScrollBarAttribute")
        }
    }
    static isScrollBarDirection(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (ScrollBarDirection.Vertical)) {
            return true
        }
        else if ((value) === (ScrollBarDirection.Horizontal)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ScrollBarDirection")
        }
    }
    static isScrollBarInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof ScrollBarInterface")
    }
    static isScrollBarOptions(value: object|string|number|undefined|null|boolean, duplicated_scroller: boolean, duplicated_direction: boolean, duplicated_state: boolean): boolean {
        if ((!duplicated_scroller) && (value?.hasOwnProperty("scroller"))) {
            return true
        }
        else if ((!duplicated_direction) && (value?.hasOwnProperty("direction"))) {
            return true
        }
        else if ((!duplicated_state) && (value?.hasOwnProperty("state"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ScrollBarOptions")
        }
    }
    static isScrollDirection(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (ScrollDirection.Vertical)) {
            return true
        }
        else if ((value) === (ScrollDirection.Horizontal)) {
            return true
        }
        else if ((value) === (ScrollDirection.Free)) {
            return true
        }
        else if ((value) === (ScrollDirection.None)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ScrollDirection")
        }
    }
    static isScrollEdgeOptions(value: object|string|number|undefined|null|boolean, duplicated_velocity: boolean): boolean {
        if ((!duplicated_velocity) && (value?.hasOwnProperty("velocity"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ScrollEdgeOptions")
        }
    }
    static isScroller(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof Scroller")
    }
    static isScrollInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof ScrollInterface")
    }
    static isScrollMotion(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof ScrollMotion")
    }
    static isScrollOptions(value: object|string|number|undefined|null|boolean, duplicated_xOffset: boolean, duplicated_yOffset: boolean, duplicated_animation: boolean): boolean {
        if ((!duplicated_xOffset) && (value?.hasOwnProperty("xOffset"))) {
            return true
        }
        else if ((!duplicated_yOffset) && (value?.hasOwnProperty("yOffset"))) {
            return true
        }
        else if ((!duplicated_animation) && (value?.hasOwnProperty("animation"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ScrollOptions")
        }
    }
    static isScrollPageOptions(value: object|string|number|undefined|null|boolean, duplicated_next: boolean, duplicated_animation: boolean): boolean {
        if ((!duplicated_next) && (value?.hasOwnProperty("next"))) {
            return true
        }
        else if ((!duplicated_animation) && (value?.hasOwnProperty("animation"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ScrollPageOptions")
        }
    }
    static isScrollResult(value: object|string|number|undefined|null|boolean, duplicated_offsetRemain: boolean): boolean {
        if ((!duplicated_offsetRemain) && (value?.hasOwnProperty("offsetRemain"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ScrollResult")
        }
    }
    static isScrollSizeMode(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (ScrollSizeMode.FOLLOW_DETENT)) {
            return true
        }
        else if ((value) === (ScrollSizeMode.CONTINUOUS)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ScrollSizeMode")
        }
    }
    static isScrollSnapAlign(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (ScrollSnapAlign.NONE)) {
            return true
        }
        else if ((value) === (ScrollSnapAlign.START)) {
            return true
        }
        else if ((value) === (ScrollSnapAlign.CENTER)) {
            return true
        }
        else if ((value) === (ScrollSnapAlign.END)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ScrollSnapAlign")
        }
    }
    static isScrollSnapOptions(value: object|string|number|undefined|null|boolean, duplicated_snapAlign: boolean, duplicated_snapPagination: boolean, duplicated_enableSnapToStart: boolean, duplicated_enableSnapToEnd: boolean): boolean {
        if ((!duplicated_snapAlign) && (value?.hasOwnProperty("snapAlign"))) {
            return true
        }
        else if ((!duplicated_snapPagination) && (value?.hasOwnProperty("snapPagination"))) {
            return true
        }
        else if ((!duplicated_enableSnapToStart) && (value?.hasOwnProperty("enableSnapToStart"))) {
            return true
        }
        else if ((!duplicated_enableSnapToEnd) && (value?.hasOwnProperty("enableSnapToEnd"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ScrollSnapOptions")
        }
    }
    static isScrollSource(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (ScrollSource.DRAG)) {
            return true
        }
        else if ((value) === (ScrollSource.FLING)) {
            return true
        }
        else if ((value) === (ScrollSource.EDGE_EFFECT)) {
            return true
        }
        else if ((value) === (ScrollSource.OTHER_USER_INPUT)) {
            return true
        }
        else if ((value) === (ScrollSource.SCROLL_BAR)) {
            return true
        }
        else if ((value) === (ScrollSource.SCROLL_BAR_FLING)) {
            return true
        }
        else if ((value) === (ScrollSource.SCROLLER)) {
            return true
        }
        else if ((value) === (ScrollSource.SCROLLER_ANIMATION)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ScrollSource")
        }
    }
    static isScrollState(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (ScrollState.Idle)) {
            return true
        }
        else if ((value) === (ScrollState.Scroll)) {
            return true
        }
        else if ((value) === (ScrollState.Fling)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ScrollState")
        }
    }
    static isScrollToIndexOptions(value: object|string|number|undefined|null|boolean, duplicated_extraOffset: boolean): boolean {
        if ((!duplicated_extraOffset) && (value?.hasOwnProperty("extraOffset"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ScrollToIndexOptions")
        }
    }
    static isSearchAttribute(value: object|string|number|undefined|null|boolean, duplicated_fontColor: boolean, duplicated_searchIcon: boolean, duplicated_cancelButton: boolean, duplicated_textIndent: boolean, duplicated_onEditChange: boolean, duplicated_selectedBackgroundColor: boolean, duplicated_caretStyle: boolean, duplicated_placeholderColor: boolean, duplicated_placeholderFont: boolean, duplicated_textFont: boolean, duplicated_enterKeyType: boolean, duplicated_onSubmit: boolean, duplicated_onChange: boolean, duplicated_onTextSelectionChange: boolean, duplicated_onContentScroll: boolean, duplicated_onCopy: boolean, duplicated_onCut: boolean, duplicated_onPaste: boolean, duplicated_copyOption: boolean, duplicated_maxLength: boolean, duplicated_textAlign: boolean, duplicated_enableKeyboardOnFocus: boolean, duplicated_selectionMenuHidden: boolean, duplicated_minFontSize: boolean, duplicated_maxFontSize: boolean, duplicated_decoration: boolean, duplicated_letterSpacing: boolean, duplicated_lineHeight: boolean, duplicated_type: boolean, duplicated_fontFeature: boolean, duplicated_onWillInsert: boolean, duplicated_onDidInsert: boolean, duplicated_onWillDelete: boolean, duplicated_onDidDelete: boolean, duplicated_editMenuOptions: boolean, duplicated_enablePreviewText: boolean, duplicated_enableHapticFeedback: boolean): boolean {
        if ((!duplicated_fontColor) && (value?.hasOwnProperty("fontColor"))) {
            return true
        }
        else if ((!duplicated_searchIcon) && (value?.hasOwnProperty("searchIcon"))) {
            return true
        }
        else if ((!duplicated_cancelButton) && (value?.hasOwnProperty("cancelButton"))) {
            return true
        }
        else if ((!duplicated_textIndent) && (value?.hasOwnProperty("textIndent"))) {
            return true
        }
        else if ((!duplicated_onEditChange) && (value?.hasOwnProperty("onEditChange"))) {
            return true
        }
        else if ((!duplicated_selectedBackgroundColor) && (value?.hasOwnProperty("selectedBackgroundColor"))) {
            return true
        }
        else if ((!duplicated_caretStyle) && (value?.hasOwnProperty("caretStyle"))) {
            return true
        }
        else if ((!duplicated_placeholderColor) && (value?.hasOwnProperty("placeholderColor"))) {
            return true
        }
        else if ((!duplicated_enterKeyType) && (value?.hasOwnProperty("enterKeyType"))) {
            return true
        }
        else if ((!duplicated_onSubmit) && (value?.hasOwnProperty("onSubmit"))) {
            return true
        }
        else if ((!duplicated_onChange) && (value?.hasOwnProperty("onChange"))) {
            return true
        }
        else if ((!duplicated_onTextSelectionChange) && (value?.hasOwnProperty("onTextSelectionChange"))) {
            return true
        }
        else if ((!duplicated_onContentScroll) && (value?.hasOwnProperty("onContentScroll"))) {
            return true
        }
        else if ((!duplicated_onCopy) && (value?.hasOwnProperty("onCopy"))) {
            return true
        }
        else if ((!duplicated_onCut) && (value?.hasOwnProperty("onCut"))) {
            return true
        }
        else if ((!duplicated_onPaste) && (value?.hasOwnProperty("onPaste"))) {
            return true
        }
        else if ((!duplicated_copyOption) && (value?.hasOwnProperty("copyOption"))) {
            return true
        }
        else if ((!duplicated_maxLength) && (value?.hasOwnProperty("maxLength"))) {
            return true
        }
        else if ((!duplicated_textAlign) && (value?.hasOwnProperty("textAlign"))) {
            return true
        }
        else if ((!duplicated_enableKeyboardOnFocus) && (value?.hasOwnProperty("enableKeyboardOnFocus"))) {
            return true
        }
        else if ((!duplicated_selectionMenuHidden) && (value?.hasOwnProperty("selectionMenuHidden"))) {
            return true
        }
        else if ((!duplicated_minFontSize) && (value?.hasOwnProperty("minFontSize"))) {
            return true
        }
        else if ((!duplicated_maxFontSize) && (value?.hasOwnProperty("maxFontSize"))) {
            return true
        }
        else if ((!duplicated_decoration) && (value?.hasOwnProperty("decoration"))) {
            return true
        }
        else if ((!duplicated_letterSpacing) && (value?.hasOwnProperty("letterSpacing"))) {
            return true
        }
        else if ((!duplicated_lineHeight) && (value?.hasOwnProperty("lineHeight"))) {
            return true
        }
        else if ((!duplicated_type) && (value?.hasOwnProperty("type"))) {
            return true
        }
        else if ((!duplicated_fontFeature) && (value?.hasOwnProperty("fontFeature"))) {
            return true
        }
        else if ((!duplicated_onWillInsert) && (value?.hasOwnProperty("onWillInsert"))) {
            return true
        }
        else if ((!duplicated_onDidInsert) && (value?.hasOwnProperty("onDidInsert"))) {
            return true
        }
        else if ((!duplicated_onWillDelete) && (value?.hasOwnProperty("onWillDelete"))) {
            return true
        }
        else if ((!duplicated_onDidDelete) && (value?.hasOwnProperty("onDidDelete"))) {
            return true
        }
        else if ((!duplicated_editMenuOptions) && (value?.hasOwnProperty("editMenuOptions"))) {
            return true
        }
        else if ((!duplicated_enablePreviewText) && (value?.hasOwnProperty("enablePreviewText"))) {
            return true
        }
        else if ((!duplicated_enableHapticFeedback) && (value?.hasOwnProperty("enableHapticFeedback"))) {
            return true
        }
        else if ((!duplicated_placeholderFont) && (value?.hasOwnProperty("placeholderFont"))) {
            return true
        }
        else if ((!duplicated_textFont) && (value?.hasOwnProperty("textFont"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SearchAttribute")
        }
    }
    static isSearchButtonOptions(value: object|string|number|undefined|null|boolean, duplicated_fontSize: boolean, duplicated_fontColor: boolean, duplicated_autoDisable: boolean): boolean {
        if ((!duplicated_fontSize) && (value?.hasOwnProperty("fontSize"))) {
            return true
        }
        else if ((!duplicated_fontColor) && (value?.hasOwnProperty("fontColor"))) {
            return true
        }
        else if ((!duplicated_autoDisable) && (value?.hasOwnProperty("autoDisable"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SearchButtonOptions")
        }
    }
    static isSearchController(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof SearchController")
    }
    static isSearchInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof SearchInterface")
    }
    static isSearchOptions(value: object|string|number|undefined|null|boolean, duplicated_value: boolean, duplicated_placeholder: boolean, duplicated_icon: boolean, duplicated_controller: boolean): boolean {
        if ((!duplicated_value) && (value?.hasOwnProperty("value"))) {
            return true
        }
        else if ((!duplicated_placeholder) && (value?.hasOwnProperty("placeholder"))) {
            return true
        }
        else if ((!duplicated_icon) && (value?.hasOwnProperty("icon"))) {
            return true
        }
        else if ((!duplicated_controller) && (value?.hasOwnProperty("controller"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SearchOptions")
        }
    }
    static isSearchType(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (SearchType.NORMAL)) {
            return true
        }
        else if ((value) === (SearchType.NUMBER)) {
            return true
        }
        else if ((value) === (SearchType.PHONE_NUMBER)) {
            return true
        }
        else if ((value) === (SearchType.EMAIL)) {
            return true
        }
        else if ((value) === (SearchType.NUMBER_DECIMAL)) {
            return true
        }
        else if ((value) === (SearchType.URL)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SearchType")
        }
    }
    static isSectionOptions(value: object|string|number|undefined|null|boolean, duplicated_itemsCount: boolean, duplicated_crossCount: boolean, duplicated_onGetItemMainSizeByIndex: boolean, duplicated_columnsGap: boolean, duplicated_rowsGap: boolean, duplicated_margin: boolean): boolean {
        if ((!duplicated_itemsCount) && (value?.hasOwnProperty("itemsCount"))) {
            return true
        }
        else if ((!duplicated_crossCount) && (value?.hasOwnProperty("crossCount"))) {
            return true
        }
        else if ((!duplicated_onGetItemMainSizeByIndex) && (value?.hasOwnProperty("onGetItemMainSizeByIndex"))) {
            return true
        }
        else if ((!duplicated_columnsGap) && (value?.hasOwnProperty("columnsGap"))) {
            return true
        }
        else if ((!duplicated_rowsGap) && (value?.hasOwnProperty("rowsGap"))) {
            return true
        }
        else if ((!duplicated_margin) && (value?.hasOwnProperty("margin"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SectionOptions")
        }
    }
    static isSecurityComponentLayoutDirection(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (SecurityComponentLayoutDirection.HORIZONTAL)) {
            return true
        }
        else if ((value) === (SecurityComponentLayoutDirection.VERTICAL)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SecurityComponentLayoutDirection")
        }
    }
    static isSecurityComponentMethod(value: object|string|number|undefined|null|boolean, duplicated_iconSize: boolean, duplicated_layoutDirection: boolean, duplicated_position: boolean, duplicated_markAnchor: boolean, duplicated_offset: boolean, duplicated_fontSize: boolean, duplicated_fontStyle: boolean, duplicated_fontWeight: boolean, duplicated_fontFamily: boolean, duplicated_fontColor: boolean, duplicated_iconColor: boolean, duplicated_backgroundColor: boolean, duplicated_borderStyle: boolean, duplicated_borderWidth: boolean, duplicated_borderColor: boolean, duplicated_borderRadius: boolean, duplicated_padding: boolean, duplicated_textIconSpace: boolean, duplicated_key: boolean, duplicated_width: boolean, duplicated_height: boolean, duplicated_size: boolean, duplicated_constraintSize: boolean): boolean {
        if ((!duplicated_iconSize) && (value?.hasOwnProperty("iconSize"))) {
            return true
        }
        else if ((!duplicated_layoutDirection) && (value?.hasOwnProperty("layoutDirection"))) {
            return true
        }
        else if ((!duplicated_position) && (value?.hasOwnProperty("position"))) {
            return true
        }
        else if ((!duplicated_markAnchor) && (value?.hasOwnProperty("markAnchor"))) {
            return true
        }
        else if ((!duplicated_offset) && (value?.hasOwnProperty("offset"))) {
            return true
        }
        else if ((!duplicated_fontSize) && (value?.hasOwnProperty("fontSize"))) {
            return true
        }
        else if ((!duplicated_fontStyle) && (value?.hasOwnProperty("fontStyle"))) {
            return true
        }
        else if ((!duplicated_fontWeight) && (value?.hasOwnProperty("fontWeight"))) {
            return true
        }
        else if ((!duplicated_fontFamily) && (value?.hasOwnProperty("fontFamily"))) {
            return true
        }
        else if ((!duplicated_fontColor) && (value?.hasOwnProperty("fontColor"))) {
            return true
        }
        else if ((!duplicated_iconColor) && (value?.hasOwnProperty("iconColor"))) {
            return true
        }
        else if ((!duplicated_backgroundColor) && (value?.hasOwnProperty("backgroundColor"))) {
            return true
        }
        else if ((!duplicated_borderStyle) && (value?.hasOwnProperty("borderStyle"))) {
            return true
        }
        else if ((!duplicated_borderWidth) && (value?.hasOwnProperty("borderWidth"))) {
            return true
        }
        else if ((!duplicated_borderColor) && (value?.hasOwnProperty("borderColor"))) {
            return true
        }
        else if ((!duplicated_borderRadius) && (value?.hasOwnProperty("borderRadius"))) {
            return true
        }
        else if ((!duplicated_padding) && (value?.hasOwnProperty("padding"))) {
            return true
        }
        else if ((!duplicated_textIconSpace) && (value?.hasOwnProperty("textIconSpace"))) {
            return true
        }
        else if ((!duplicated_key) && (value?.hasOwnProperty("key"))) {
            return true
        }
        else if ((!duplicated_width) && (value?.hasOwnProperty("width"))) {
            return true
        }
        else if ((!duplicated_height) && (value?.hasOwnProperty("height"))) {
            return true
        }
        else if ((!duplicated_size) && (value?.hasOwnProperty("size"))) {
            return true
        }
        else if ((!duplicated_constraintSize) && (value?.hasOwnProperty("constraintSize"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SecurityComponentMethod")
        }
    }
    static isSeekMode(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (SeekMode.PreviousKeyframe)) {
            return true
        }
        else if ((value) === (SeekMode.NextKeyframe)) {
            return true
        }
        else if ((value) === (SeekMode.ClosestKeyframe)) {
            return true
        }
        else if ((value) === (SeekMode.Accurate)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SeekMode")
        }
    }
    static isSelectAttribute(value: object|string|number|undefined|null|boolean, duplicated_selected: boolean, duplicated_value: boolean, duplicated_font: boolean, duplicated_fontColor: boolean, duplicated_selectedOptionBgColor: boolean, duplicated_selectedOptionFont: boolean, duplicated_selectedOptionFontColor: boolean, duplicated_optionBgColor: boolean, duplicated_optionFont: boolean, duplicated_optionFontColor: boolean, duplicated_onSelect: boolean, duplicated_space: boolean, duplicated_arrowPosition: boolean, duplicated_optionWidth: boolean, duplicated_optionHeight: boolean, duplicated_menuBackgroundColor: boolean, duplicated_menuBackgroundBlurStyle: boolean, duplicated_controlSize: boolean, duplicated_menuItemContentModifier: boolean, duplicated_divider: boolean): boolean {
        if ((!duplicated_selected) && (value?.hasOwnProperty("selected"))) {
            return true
        }
        else if ((!duplicated_value) && (value?.hasOwnProperty("value"))) {
            return true
        }
        else if ((!duplicated_font) && (value?.hasOwnProperty("font"))) {
            return true
        }
        else if ((!duplicated_fontColor) && (value?.hasOwnProperty("fontColor"))) {
            return true
        }
        else if ((!duplicated_selectedOptionBgColor) && (value?.hasOwnProperty("selectedOptionBgColor"))) {
            return true
        }
        else if ((!duplicated_selectedOptionFont) && (value?.hasOwnProperty("selectedOptionFont"))) {
            return true
        }
        else if ((!duplicated_selectedOptionFontColor) && (value?.hasOwnProperty("selectedOptionFontColor"))) {
            return true
        }
        else if ((!duplicated_optionBgColor) && (value?.hasOwnProperty("optionBgColor"))) {
            return true
        }
        else if ((!duplicated_optionFont) && (value?.hasOwnProperty("optionFont"))) {
            return true
        }
        else if ((!duplicated_optionFontColor) && (value?.hasOwnProperty("optionFontColor"))) {
            return true
        }
        else if ((!duplicated_onSelect) && (value?.hasOwnProperty("onSelect"))) {
            return true
        }
        else if ((!duplicated_space) && (value?.hasOwnProperty("space"))) {
            return true
        }
        else if ((!duplicated_arrowPosition) && (value?.hasOwnProperty("arrowPosition"))) {
            return true
        }
        else if ((!duplicated_optionWidth) && (value?.hasOwnProperty("optionWidth"))) {
            return true
        }
        else if ((!duplicated_optionHeight) && (value?.hasOwnProperty("optionHeight"))) {
            return true
        }
        else if ((!duplicated_menuBackgroundColor) && (value?.hasOwnProperty("menuBackgroundColor"))) {
            return true
        }
        else if ((!duplicated_menuBackgroundBlurStyle) && (value?.hasOwnProperty("menuBackgroundBlurStyle"))) {
            return true
        }
        else if ((!duplicated_controlSize) && (value?.hasOwnProperty("controlSize"))) {
            return true
        }
        else if ((!duplicated_menuItemContentModifier) && (value?.hasOwnProperty("menuItemContentModifier"))) {
            return true
        }
        else if ((!duplicated_divider) && (value?.hasOwnProperty("divider"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SelectAttribute")
        }
    }
    static isSelectedMode(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (SelectedMode.INDICATOR)) {
            return true
        }
        else if ((value) === (SelectedMode.BOARD)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SelectedMode")
        }
    }
    static isSelectInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof SelectInterface")
    }
    static isSelectionMenuOptions(value: object|string|number|undefined|null|boolean, duplicated_onAppear: boolean, duplicated_onDisappear: boolean, duplicated_menuType: boolean): boolean {
        if ((!duplicated_onAppear) && (value?.hasOwnProperty("onAppear"))) {
            return true
        }
        else if ((!duplicated_onDisappear) && (value?.hasOwnProperty("onDisappear"))) {
            return true
        }
        else if ((!duplicated_menuType) && (value?.hasOwnProperty("menuType"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SelectionMenuOptions")
        }
    }
    static isSelectionMenuOptionsExt(value: object|string|number|undefined|null|boolean, duplicated_onAppear: boolean, duplicated_onDisappear: boolean, duplicated_preview: boolean, duplicated_menuType: boolean): boolean {
        if ((!duplicated_onAppear) && (value?.hasOwnProperty("onAppear"))) {
            return true
        }
        else if ((!duplicated_onDisappear) && (value?.hasOwnProperty("onDisappear"))) {
            return true
        }
        else if ((!duplicated_preview) && (value?.hasOwnProperty("preview"))) {
            return true
        }
        else if ((!duplicated_menuType) && (value?.hasOwnProperty("menuType"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SelectionMenuOptionsExt")
        }
    }
    static isSelectionOptions(value: object|string|number|undefined|null|boolean, duplicated_menuPolicy: boolean): boolean {
        if ((!duplicated_menuPolicy) && (value?.hasOwnProperty("menuPolicy"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SelectionOptions")
        }
    }
    static isSelectOption(value: object|string|number|undefined|null|boolean, duplicated_value: boolean, duplicated_icon: boolean, duplicated_symbolIcon: boolean): boolean {
        if ((!duplicated_value) && (value?.hasOwnProperty("value"))) {
            return true
        }
        else if ((!duplicated_icon) && (value?.hasOwnProperty("icon"))) {
            return true
        }
        else if ((!duplicated_symbolIcon) && (value?.hasOwnProperty("symbolIcon"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SelectOption")
        }
    }
    static isSelectStatus(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (SelectStatus.All)) {
            return true
        }
        else if ((value) === (SelectStatus.Part)) {
            return true
        }
        else if ((value) === (SelectStatus.None)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SelectStatus")
        }
    }
    static isShadowOptions(value: object|string|number|undefined|null|boolean, duplicated_radius: boolean, duplicated_type: boolean, duplicated_color: boolean, duplicated_offsetX: boolean, duplicated_offsetY: boolean, duplicated_fill: boolean): boolean {
        if ((!duplicated_radius) && (value?.hasOwnProperty("radius"))) {
            return true
        }
        else if ((!duplicated_type) && (value?.hasOwnProperty("type"))) {
            return true
        }
        else if ((!duplicated_color) && (value?.hasOwnProperty("color"))) {
            return true
        }
        else if ((!duplicated_offsetX) && (value?.hasOwnProperty("offsetX"))) {
            return true
        }
        else if ((!duplicated_offsetY) && (value?.hasOwnProperty("offsetY"))) {
            return true
        }
        else if ((!duplicated_fill) && (value?.hasOwnProperty("fill"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ShadowOptions")
        }
    }
    static isShadowStyle(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (ShadowStyle.OUTER_DEFAULT_XS)) {
            return true
        }
        else if ((value) === (ShadowStyle.OUTER_DEFAULT_SM)) {
            return true
        }
        else if ((value) === (ShadowStyle.OUTER_DEFAULT_MD)) {
            return true
        }
        else if ((value) === (ShadowStyle.OUTER_DEFAULT_LG)) {
            return true
        }
        else if ((value) === (ShadowStyle.OUTER_FLOATING_SM)) {
            return true
        }
        else if ((value) === (ShadowStyle.OUTER_FLOATING_MD)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ShadowStyle")
        }
    }
    static isShadowType(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (ShadowType.COLOR)) {
            return true
        }
        else if ((value) === (ShadowType.BLUR)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ShadowType")
        }
    }
    static isShapeAttribute(value: object|string|number|undefined|null|boolean, duplicated_viewPort: boolean, duplicated_stroke: boolean, duplicated_fill: boolean, duplicated_strokeDashOffset: boolean, duplicated_strokeDashArray: boolean, duplicated_strokeLineCap: boolean, duplicated_strokeLineJoin: boolean, duplicated_strokeMiterLimit: boolean, duplicated_strokeOpacity: boolean, duplicated_fillOpacity: boolean, duplicated_strokeWidth: boolean, duplicated_antiAlias: boolean): boolean {
        if ((!duplicated_viewPort) && (value?.hasOwnProperty("viewPort"))) {
            return true
        }
        else if ((!duplicated_stroke) && (value?.hasOwnProperty("stroke"))) {
            return true
        }
        else if ((!duplicated_fill) && (value?.hasOwnProperty("fill"))) {
            return true
        }
        else if ((!duplicated_strokeDashOffset) && (value?.hasOwnProperty("strokeDashOffset"))) {
            return true
        }
        else if ((!duplicated_strokeDashArray) && (value?.hasOwnProperty("strokeDashArray"))) {
            return true
        }
        else if ((!duplicated_strokeLineCap) && (value?.hasOwnProperty("strokeLineCap"))) {
            return true
        }
        else if ((!duplicated_strokeLineJoin) && (value?.hasOwnProperty("strokeLineJoin"))) {
            return true
        }
        else if ((!duplicated_strokeMiterLimit) && (value?.hasOwnProperty("strokeMiterLimit"))) {
            return true
        }
        else if ((!duplicated_strokeOpacity) && (value?.hasOwnProperty("strokeOpacity"))) {
            return true
        }
        else if ((!duplicated_fillOpacity) && (value?.hasOwnProperty("fillOpacity"))) {
            return true
        }
        else if ((!duplicated_strokeWidth) && (value?.hasOwnProperty("strokeWidth"))) {
            return true
        }
        else if ((!duplicated_antiAlias) && (value?.hasOwnProperty("antiAlias"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ShapeAttribute")
        }
    }
    static isShapeInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof ShapeInterface")
    }
    static isShapeSize(value: object|string|number|undefined|null|boolean, duplicated_width: boolean, duplicated_height: boolean): boolean {
        if ((!duplicated_width) && (value?.hasOwnProperty("width"))) {
            return true
        }
        else if ((!duplicated_height) && (value?.hasOwnProperty("height"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ShapeSize")
        }
    }
    static isSharedTransitionEffectType(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (SharedTransitionEffectType.Static)) {
            return true
        }
        else if ((value) === (SharedTransitionEffectType.Exchange)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SharedTransitionEffectType")
        }
    }
    static issharedTransitionOptions(value: object|string|number|undefined|null|boolean, duplicated_duration: boolean, duplicated_curve: boolean, duplicated_delay: boolean, duplicated_motionPath: boolean, duplicated_zIndex: boolean, duplicated_type: boolean): boolean {
        if ((!duplicated_duration) && (value?.hasOwnProperty("duration"))) {
            return true
        }
        else if ((!duplicated_curve) && (value?.hasOwnProperty("curve"))) {
            return true
        }
        else if ((!duplicated_delay) && (value?.hasOwnProperty("delay"))) {
            return true
        }
        else if ((!duplicated_motionPath) && (value?.hasOwnProperty("motionPath"))) {
            return true
        }
        else if ((!duplicated_zIndex) && (value?.hasOwnProperty("zIndex"))) {
            return true
        }
        else if ((!duplicated_type) && (value?.hasOwnProperty("type"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof sharedTransitionOptions")
        }
    }
    static isSheetDismiss(value: object|string|number|undefined|null|boolean, duplicated_dismiss: boolean): boolean {
        if ((!duplicated_dismiss) && (value?.hasOwnProperty("dismiss"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SheetDismiss")
        }
    }
    static isSheetInfo(value: object|string|number|undefined|null|boolean, duplicated_title: boolean, duplicated_icon: boolean, duplicated_action: boolean): boolean {
        if ((!duplicated_title) && (value?.hasOwnProperty("title"))) {
            return true
        }
        else if ((!duplicated_action) && (value?.hasOwnProperty("action"))) {
            return true
        }
        else if ((!duplicated_icon) && (value?.hasOwnProperty("icon"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SheetInfo")
        }
    }
    static isSheetKeyboardAvoidMode(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (SheetKeyboardAvoidMode.NONE)) {
            return true
        }
        else if ((value) === (SheetKeyboardAvoidMode.TRANSLATE_AND_RESIZE)) {
            return true
        }
        else if ((value) === (SheetKeyboardAvoidMode.RESIZE_ONLY)) {
            return true
        }
        else if ((value) === (SheetKeyboardAvoidMode.TRANSLATE_AND_SCROLL)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SheetKeyboardAvoidMode")
        }
    }
    static isSheetMode(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (SheetMode.OVERLAY)) {
            return true
        }
        else if ((value) === (SheetMode.EMBEDDED)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SheetMode")
        }
    }
    static isSheetOptions(value: object|string|number|undefined|null|boolean, duplicated_height: boolean, duplicated_dragBar: boolean, duplicated_maskColor: boolean, duplicated_detents: boolean, duplicated_blurStyle: boolean, duplicated_showClose: boolean, duplicated_preferType: boolean, duplicated_title: boolean, duplicated_shouldDismiss: boolean, duplicated_onWillDismiss: boolean, duplicated_onWillSpringBackWhenDismiss: boolean, duplicated_enableOutsideInteractive: boolean, duplicated_width: boolean, duplicated_borderWidth: boolean, duplicated_borderColor: boolean, duplicated_borderStyle: boolean, duplicated_shadow: boolean, duplicated_onHeightDidChange: boolean, duplicated_mode: boolean, duplicated_scrollSizeMode: boolean, duplicated_onDetentsDidChange: boolean, duplicated_onWidthDidChange: boolean, duplicated_onTypeDidChange: boolean, duplicated_uiContext: boolean, duplicated_keyboardAvoidMode: boolean): boolean {
        if ((!duplicated_height) && (value?.hasOwnProperty("height"))) {
            return true
        }
        else if ((!duplicated_dragBar) && (value?.hasOwnProperty("dragBar"))) {
            return true
        }
        else if ((!duplicated_maskColor) && (value?.hasOwnProperty("maskColor"))) {
            return true
        }
        else if ((!duplicated_detents) && (value?.hasOwnProperty("detents"))) {
            return true
        }
        else if ((!duplicated_blurStyle) && (value?.hasOwnProperty("blurStyle"))) {
            return true
        }
        else if ((!duplicated_showClose) && (value?.hasOwnProperty("showClose"))) {
            return true
        }
        else if ((!duplicated_preferType) && (value?.hasOwnProperty("preferType"))) {
            return true
        }
        else if ((!duplicated_title) && (value?.hasOwnProperty("title"))) {
            return true
        }
        else if ((!duplicated_shouldDismiss) && (value?.hasOwnProperty("shouldDismiss"))) {
            return true
        }
        else if ((!duplicated_onWillDismiss) && (value?.hasOwnProperty("onWillDismiss"))) {
            return true
        }
        else if ((!duplicated_onWillSpringBackWhenDismiss) && (value?.hasOwnProperty("onWillSpringBackWhenDismiss"))) {
            return true
        }
        else if ((!duplicated_enableOutsideInteractive) && (value?.hasOwnProperty("enableOutsideInteractive"))) {
            return true
        }
        else if ((!duplicated_width) && (value?.hasOwnProperty("width"))) {
            return true
        }
        else if ((!duplicated_borderWidth) && (value?.hasOwnProperty("borderWidth"))) {
            return true
        }
        else if ((!duplicated_borderColor) && (value?.hasOwnProperty("borderColor"))) {
            return true
        }
        else if ((!duplicated_borderStyle) && (value?.hasOwnProperty("borderStyle"))) {
            return true
        }
        else if ((!duplicated_shadow) && (value?.hasOwnProperty("shadow"))) {
            return true
        }
        else if ((!duplicated_onHeightDidChange) && (value?.hasOwnProperty("onHeightDidChange"))) {
            return true
        }
        else if ((!duplicated_mode) && (value?.hasOwnProperty("mode"))) {
            return true
        }
        else if ((!duplicated_scrollSizeMode) && (value?.hasOwnProperty("scrollSizeMode"))) {
            return true
        }
        else if ((!duplicated_onDetentsDidChange) && (value?.hasOwnProperty("onDetentsDidChange"))) {
            return true
        }
        else if ((!duplicated_onWidthDidChange) && (value?.hasOwnProperty("onWidthDidChange"))) {
            return true
        }
        else if ((!duplicated_onTypeDidChange) && (value?.hasOwnProperty("onTypeDidChange"))) {
            return true
        }
        else if ((!duplicated_uiContext) && (value?.hasOwnProperty("uiContext"))) {
            return true
        }
        else if ((!duplicated_keyboardAvoidMode) && (value?.hasOwnProperty("keyboardAvoidMode"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SheetOptions")
        }
    }
    static isSheetSize(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (SheetSize.MEDIUM)) {
            return true
        }
        else if ((value) === (SheetSize.LARGE)) {
            return true
        }
        else if ((value) === (SheetSize.FIT_CONTENT)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SheetSize")
        }
    }
    static isSheetTitleOptions(value: object|string|number|undefined|null|boolean, duplicated_title: boolean, duplicated_subtitle: boolean): boolean {
        if ((!duplicated_title) && (value?.hasOwnProperty("title"))) {
            return true
        }
        else if ((!duplicated_subtitle) && (value?.hasOwnProperty("subtitle"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SheetTitleOptions")
        }
    }
    static isSheetType(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (SheetType.BOTTOM)) {
            return true
        }
        else if ((value) === (SheetType.CENTER)) {
            return true
        }
        else if ((value) === (SheetType.POPUP)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SheetType")
        }
    }
    static isSideBarContainerAttribute(value: object|string|number|undefined|null|boolean, duplicated_showSideBar: boolean, duplicated_controlButton: boolean, duplicated_showControlButton: boolean, duplicated_onChange: boolean, duplicated_sideBarWidth: boolean, duplicated_minSideBarWidth: boolean, duplicated_maxSideBarWidth: boolean, duplicated_autoHide: boolean, duplicated_sideBarPosition: boolean, duplicated_divider: boolean, duplicated_minContentWidth: boolean): boolean {
        if ((!duplicated_showSideBar) && (value?.hasOwnProperty("showSideBar"))) {
            return true
        }
        else if ((!duplicated_controlButton) && (value?.hasOwnProperty("controlButton"))) {
            return true
        }
        else if ((!duplicated_showControlButton) && (value?.hasOwnProperty("showControlButton"))) {
            return true
        }
        else if ((!duplicated_onChange) && (value?.hasOwnProperty("onChange"))) {
            return true
        }
        else if ((!duplicated_sideBarWidth) && (value?.hasOwnProperty("sideBarWidth"))) {
            return true
        }
        else if ((!duplicated_minSideBarWidth) && (value?.hasOwnProperty("minSideBarWidth"))) {
            return true
        }
        else if ((!duplicated_maxSideBarWidth) && (value?.hasOwnProperty("maxSideBarWidth"))) {
            return true
        }
        else if ((!duplicated_autoHide) && (value?.hasOwnProperty("autoHide"))) {
            return true
        }
        else if ((!duplicated_sideBarPosition) && (value?.hasOwnProperty("sideBarPosition"))) {
            return true
        }
        else if ((!duplicated_divider) && (value?.hasOwnProperty("divider"))) {
            return true
        }
        else if ((!duplicated_minContentWidth) && (value?.hasOwnProperty("minContentWidth"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SideBarContainerAttribute")
        }
    }
    static isSideBarContainerInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof SideBarContainerInterface")
    }
    static isSideBarContainerType(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (SideBarContainerType.Embed)) {
            return true
        }
        else if ((value) === (SideBarContainerType.Overlay)) {
            return true
        }
        else if ((value) === (SideBarContainerType.AUTO)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SideBarContainerType")
        }
    }
    static isSideBarPosition(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (SideBarPosition.Start)) {
            return true
        }
        else if ((value) === (SideBarPosition.End)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SideBarPosition")
        }
    }
    static isSize(value: object|string|number|undefined|null|boolean, duplicated_width: boolean, duplicated_height: boolean): boolean {
        if ((!duplicated_width) && (value?.hasOwnProperty("width"))) {
            return true
        }
        else if ((!duplicated_height) && (value?.hasOwnProperty("height"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof Size")
        }
    }
    static isSizeOptions(value: object|string|number|undefined|null|boolean, duplicated_width: boolean, duplicated_height: boolean): boolean {
        if ((!duplicated_width) && (value?.hasOwnProperty("width"))) {
            return true
        }
        else if ((!duplicated_height) && (value?.hasOwnProperty("height"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SizeOptions")
        }
    }
    static isSizeResult(value: object|string|number|undefined|null|boolean, duplicated_width: boolean, duplicated_height: boolean): boolean {
        if ((!duplicated_width) && (value?.hasOwnProperty("width"))) {
            return true
        }
        else if ((!duplicated_height) && (value?.hasOwnProperty("height"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SizeResult")
        }
    }
    static isSizeType(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (SizeType.Auto)) {
            return true
        }
        else if ((value) === (SizeType.XS)) {
            return true
        }
        else if ((value) === (SizeType.SM)) {
            return true
        }
        else if ((value) === (SizeType.MD)) {
            return true
        }
        else if ((value) === (SizeType.LG)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SizeType")
        }
    }
    static isSlideEffect(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (SlideEffect.Left)) {
            return true
        }
        else if ((value) === (SlideEffect.Right)) {
            return true
        }
        else if ((value) === (SlideEffect.Top)) {
            return true
        }
        else if ((value) === (SlideEffect.Bottom)) {
            return true
        }
        else if ((value) === (SlideEffect.START)) {
            return true
        }
        else if ((value) === (SlideEffect.END)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SlideEffect")
        }
    }
    static isSlideRange(value: object|string|number|undefined|null|boolean, duplicated_from: boolean, duplicated_to: boolean): boolean {
        if ((!duplicated_from) && (value?.hasOwnProperty("from"))) {
            return true
        }
        else if ((!duplicated_to) && (value?.hasOwnProperty("to"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SlideRange")
        }
    }
    static isSliderAttribute(value: object|string|number|undefined|null|boolean, duplicated_blockColor: boolean, duplicated_trackColor: boolean, duplicated_selectedColor: boolean, duplicated_minLabel: boolean, duplicated_maxLabel: boolean, duplicated_showSteps: boolean, duplicated_trackThickness: boolean, duplicated_onChange: boolean, duplicated_blockBorderColor: boolean, duplicated_blockBorderWidth: boolean, duplicated_stepColor: boolean, duplicated_trackBorderRadius: boolean, duplicated_selectedBorderRadius: boolean, duplicated_blockSize: boolean, duplicated_blockStyle: boolean, duplicated_stepSize: boolean, duplicated_sliderInteractionMode: boolean, duplicated_minResponsiveDistance: boolean, duplicated_contentModifier: boolean, duplicated_slideRange: boolean): boolean {
        if ((!duplicated_blockColor) && (value?.hasOwnProperty("blockColor"))) {
            return true
        }
        else if ((!duplicated_trackColor) && (value?.hasOwnProperty("trackColor"))) {
            return true
        }
        else if ((!duplicated_selectedColor) && (value?.hasOwnProperty("selectedColor"))) {
            return true
        }
        else if ((!duplicated_minLabel) && (value?.hasOwnProperty("minLabel"))) {
            return true
        }
        else if ((!duplicated_maxLabel) && (value?.hasOwnProperty("maxLabel"))) {
            return true
        }
        else if ((!duplicated_showSteps) && (value?.hasOwnProperty("showSteps"))) {
            return true
        }
        else if ((!duplicated_trackThickness) && (value?.hasOwnProperty("trackThickness"))) {
            return true
        }
        else if ((!duplicated_onChange) && (value?.hasOwnProperty("onChange"))) {
            return true
        }
        else if ((!duplicated_blockBorderColor) && (value?.hasOwnProperty("blockBorderColor"))) {
            return true
        }
        else if ((!duplicated_blockBorderWidth) && (value?.hasOwnProperty("blockBorderWidth"))) {
            return true
        }
        else if ((!duplicated_stepColor) && (value?.hasOwnProperty("stepColor"))) {
            return true
        }
        else if ((!duplicated_trackBorderRadius) && (value?.hasOwnProperty("trackBorderRadius"))) {
            return true
        }
        else if ((!duplicated_selectedBorderRadius) && (value?.hasOwnProperty("selectedBorderRadius"))) {
            return true
        }
        else if ((!duplicated_blockSize) && (value?.hasOwnProperty("blockSize"))) {
            return true
        }
        else if ((!duplicated_blockStyle) && (value?.hasOwnProperty("blockStyle"))) {
            return true
        }
        else if ((!duplicated_stepSize) && (value?.hasOwnProperty("stepSize"))) {
            return true
        }
        else if ((!duplicated_sliderInteractionMode) && (value?.hasOwnProperty("sliderInteractionMode"))) {
            return true
        }
        else if ((!duplicated_minResponsiveDistance) && (value?.hasOwnProperty("minResponsiveDistance"))) {
            return true
        }
        else if ((!duplicated_contentModifier) && (value?.hasOwnProperty("contentModifier"))) {
            return true
        }
        else if ((!duplicated_slideRange) && (value?.hasOwnProperty("slideRange"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SliderAttribute")
        }
    }
    static isSliderBlockStyle(value: object|string|number|undefined|null|boolean, duplicated_type: boolean, duplicated_image: boolean, duplicated_shape: boolean): boolean {
        if ((!duplicated_type) && (value?.hasOwnProperty("type"))) {
            return true
        }
        else if ((!duplicated_image) && (value?.hasOwnProperty("image"))) {
            return true
        }
        else if ((!duplicated_shape) && (value?.hasOwnProperty("shape"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SliderBlockStyle")
        }
    }
    static isSliderBlockType(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (SliderBlockType.DEFAULT)) {
            return true
        }
        else if ((value) === (SliderBlockType.IMAGE)) {
            return true
        }
        else if ((value) === (SliderBlockType.SHAPE)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SliderBlockType")
        }
    }
    static isSliderChangeMode(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (SliderChangeMode.Begin)) {
            return true
        }
        else if ((value) === (SliderChangeMode.Moving)) {
            return true
        }
        else if ((value) === (SliderChangeMode.End)) {
            return true
        }
        else if ((value) === (SliderChangeMode.Click)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SliderChangeMode")
        }
    }
    static isSliderConfiguration(value: object|string|number|undefined|null|boolean, duplicated_value: boolean, duplicated_min: boolean, duplicated_max: boolean, duplicated_step: boolean, duplicated_triggerChange: boolean): boolean {
        if ((!duplicated_value) && (value?.hasOwnProperty("value"))) {
            return true
        }
        else if ((!duplicated_min) && (value?.hasOwnProperty("min"))) {
            return true
        }
        else if ((!duplicated_max) && (value?.hasOwnProperty("max"))) {
            return true
        }
        else if ((!duplicated_step) && (value?.hasOwnProperty("step"))) {
            return true
        }
        else if ((!duplicated_triggerChange) && (value?.hasOwnProperty("triggerChange"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SliderConfiguration")
        }
    }
    static isSliderInteraction(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (SliderInteraction.SLIDE_AND_CLICK)) {
            return true
        }
        else if ((value) === (SliderInteraction.SLIDE_ONLY)) {
            return true
        }
        else if ((value) === (SliderInteraction.SLIDE_AND_CLICK_UP)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SliderInteraction")
        }
    }
    static isSliderInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof SliderInterface")
    }
    static isSliderOptions(value: object|string|number|undefined|null|boolean, duplicated_value: boolean, duplicated_min: boolean, duplicated_max: boolean, duplicated_step: boolean, duplicated_style: boolean, duplicated_direction: boolean, duplicated_reverse: boolean): boolean {
        if ((!duplicated_value) && (value?.hasOwnProperty("value"))) {
            return true
        }
        else if ((!duplicated_min) && (value?.hasOwnProperty("min"))) {
            return true
        }
        else if ((!duplicated_max) && (value?.hasOwnProperty("max"))) {
            return true
        }
        else if ((!duplicated_step) && (value?.hasOwnProperty("step"))) {
            return true
        }
        else if ((!duplicated_style) && (value?.hasOwnProperty("style"))) {
            return true
        }
        else if ((!duplicated_direction) && (value?.hasOwnProperty("direction"))) {
            return true
        }
        else if ((!duplicated_reverse) && (value?.hasOwnProperty("reverse"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SliderOptions")
        }
    }
    static isSliderStyle(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (SliderStyle.OutSet)) {
            return true
        }
        else if ((value) === (SliderStyle.InSet)) {
            return true
        }
        else if ((value) === (SliderStyle.NONE)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SliderStyle")
        }
    }
    static isSnapshotOptions(value: object|string|number|undefined|null|boolean, duplicated_scale: boolean, duplicated_waitUntilRenderFinished: boolean): boolean {
        if ((!duplicated_scale) && (value?.hasOwnProperty("scale"))) {
            return true
        }
        else if ((!duplicated_waitUntilRenderFinished) && (value?.hasOwnProperty("waitUntilRenderFinished"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SnapshotOptions")
        }
    }
    static isSourceTool(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (SourceTool.Unknown)) {
            return true
        }
        else if ((value) === (SourceTool.Finger)) {
            return true
        }
        else if ((value) === (SourceTool.Pen)) {
            return true
        }
        else if ((value) === (SourceTool.MOUSE)) {
            return true
        }
        else if ((value) === (SourceTool.TOUCHPAD)) {
            return true
        }
        else if ((value) === (SourceTool.JOYSTICK)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SourceTool")
        }
    }
    static isSourceType(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (SourceType.Unknown)) {
            return true
        }
        else if ((value) === (SourceType.Mouse)) {
            return true
        }
        else if ((value) === (SourceType.TouchScreen)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SourceType")
        }
    }
    static isSpanAttribute(value: object|string|number|undefined|null|boolean, duplicated_font: boolean, duplicated_fontColor: boolean, duplicated_fontSize: boolean, duplicated_fontStyle: boolean, duplicated_fontWeight: boolean, duplicated_fontFamily: boolean, duplicated_decoration: boolean, duplicated_letterSpacing: boolean, duplicated_textCase: boolean, duplicated_lineHeight: boolean, duplicated_textShadow: boolean): boolean {
        if ((!duplicated_font) && (value?.hasOwnProperty("font"))) {
            return true
        }
        else if ((!duplicated_fontColor) && (value?.hasOwnProperty("fontColor"))) {
            return true
        }
        else if ((!duplicated_fontSize) && (value?.hasOwnProperty("fontSize"))) {
            return true
        }
        else if ((!duplicated_fontStyle) && (value?.hasOwnProperty("fontStyle"))) {
            return true
        }
        else if ((!duplicated_fontWeight) && (value?.hasOwnProperty("fontWeight"))) {
            return true
        }
        else if ((!duplicated_fontFamily) && (value?.hasOwnProperty("fontFamily"))) {
            return true
        }
        else if ((!duplicated_decoration) && (value?.hasOwnProperty("decoration"))) {
            return true
        }
        else if ((!duplicated_letterSpacing) && (value?.hasOwnProperty("letterSpacing"))) {
            return true
        }
        else if ((!duplicated_textCase) && (value?.hasOwnProperty("textCase"))) {
            return true
        }
        else if ((!duplicated_lineHeight) && (value?.hasOwnProperty("lineHeight"))) {
            return true
        }
        else if ((!duplicated_textShadow) && (value?.hasOwnProperty("textShadow"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SpanAttribute")
        }
    }
    static isSpanInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof SpanInterface")
    }
    static isSpanStyle(value: object|string|number|undefined|null|boolean, duplicated_start: boolean, duplicated_length: boolean, duplicated_styledKey: boolean, duplicated_styledValue: boolean): boolean {
        if ((!duplicated_start) && (value?.hasOwnProperty("start"))) {
            return true
        }
        else if ((!duplicated_length) && (value?.hasOwnProperty("length"))) {
            return true
        }
        else if ((!duplicated_styledKey) && (value?.hasOwnProperty("styledKey"))) {
            return true
        }
        else if ((!duplicated_styledValue) && (value?.hasOwnProperty("styledValue"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SpanStyle")
        }
    }
    static isSpringBackAction(value: object|string|number|undefined|null|boolean, duplicated_springBack: boolean): boolean {
        if ((!duplicated_springBack) && (value?.hasOwnProperty("springBack"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SpringBackAction")
        }
    }
    static isSpringMotion(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof SpringMotion")
    }
    static isSpringProp(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof SpringProp")
    }
    static isSslError(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (SslError.Invalid)) {
            return true
        }
        else if ((value) === (SslError.HostMismatch)) {
            return true
        }
        else if ((value) === (SslError.DateInvalid)) {
            return true
        }
        else if ((value) === (SslError.Untrusted)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SslError")
        }
    }
    static isSslErrorEvent(value: object|string|number|undefined|null|boolean, duplicated_handler: boolean, duplicated_error: boolean, duplicated_url: boolean, duplicated_originalUrl: boolean, duplicated_referrer: boolean, duplicated_isFatalError: boolean, duplicated_isMainFrame: boolean): boolean {
        if ((!duplicated_handler) && (value?.hasOwnProperty("handler"))) {
            return true
        }
        else if ((!duplicated_error) && (value?.hasOwnProperty("error"))) {
            return true
        }
        else if ((!duplicated_url) && (value?.hasOwnProperty("url"))) {
            return true
        }
        else if ((!duplicated_originalUrl) && (value?.hasOwnProperty("originalUrl"))) {
            return true
        }
        else if ((!duplicated_referrer) && (value?.hasOwnProperty("referrer"))) {
            return true
        }
        else if ((!duplicated_isFatalError) && (value?.hasOwnProperty("isFatalError"))) {
            return true
        }
        else if ((!duplicated_isMainFrame) && (value?.hasOwnProperty("isMainFrame"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SslErrorEvent")
        }
    }
    static isSslErrorHandler(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof SslErrorHandler")
    }
    static isStackAttribute(value: object|string|number|undefined|null|boolean, duplicated_alignContent: boolean, duplicated_pointLight: boolean): boolean {
        if ((!duplicated_alignContent) && (value?.hasOwnProperty("alignContent"))) {
            return true
        }
        else if ((!duplicated_pointLight) && (value?.hasOwnProperty("pointLight"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof StackAttribute")
        }
    }
    static isStackInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof StackInterface")
    }
    static isStackOptions(value: object|string|number|undefined|null|boolean, duplicated_alignContent: boolean): boolean {
        if ((!duplicated_alignContent) && (value?.hasOwnProperty("alignContent"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof StackOptions")
        }
    }
    static isStarStyleOptions(value: object|string|number|undefined|null|boolean, duplicated_backgroundUri: boolean, duplicated_foregroundUri: boolean, duplicated_secondaryUri: boolean): boolean {
        if ((!duplicated_backgroundUri) && (value?.hasOwnProperty("backgroundUri"))) {
            return true
        }
        else if ((!duplicated_foregroundUri) && (value?.hasOwnProperty("foregroundUri"))) {
            return true
        }
        else if ((!duplicated_secondaryUri) && (value?.hasOwnProperty("secondaryUri"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof StarStyleOptions")
        }
    }
    static isStateStyles(value: object|string|number|undefined|null|boolean, duplicated_normal: boolean, duplicated_pressed: boolean, duplicated_disabled: boolean, duplicated_focused: boolean, duplicated_clicked: boolean, duplicated_selected: boolean): boolean {
        if ((!duplicated_normal) && (value?.hasOwnProperty("normal"))) {
            return true
        }
        else if ((!duplicated_pressed) && (value?.hasOwnProperty("pressed"))) {
            return true
        }
        else if ((!duplicated_disabled) && (value?.hasOwnProperty("disabled"))) {
            return true
        }
        else if ((!duplicated_focused) && (value?.hasOwnProperty("focused"))) {
            return true
        }
        else if ((!duplicated_clicked) && (value?.hasOwnProperty("clicked"))) {
            return true
        }
        else if ((!duplicated_selected) && (value?.hasOwnProperty("selected"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof StateStyles")
        }
    }
    static isStepperAttribute(value: object|string|number|undefined|null|boolean, duplicated_onFinish: boolean, duplicated_onSkip: boolean, duplicated_onChange: boolean, duplicated_onNext: boolean, duplicated_onPrevious: boolean): boolean {
        if ((!duplicated_onFinish) && (value?.hasOwnProperty("onFinish"))) {
            return true
        }
        else if ((!duplicated_onSkip) && (value?.hasOwnProperty("onSkip"))) {
            return true
        }
        else if ((!duplicated_onChange) && (value?.hasOwnProperty("onChange"))) {
            return true
        }
        else if ((!duplicated_onNext) && (value?.hasOwnProperty("onNext"))) {
            return true
        }
        else if ((!duplicated_onPrevious) && (value?.hasOwnProperty("onPrevious"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof StepperAttribute")
        }
    }
    static isStepperInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof StepperInterface")
    }
    static isStepperItemAttribute(value: object|string|number|undefined|null|boolean, duplicated_prevLabel: boolean, duplicated_nextLabel: boolean, duplicated_status: boolean): boolean {
        if ((!duplicated_prevLabel) && (value?.hasOwnProperty("prevLabel"))) {
            return true
        }
        else if ((!duplicated_nextLabel) && (value?.hasOwnProperty("nextLabel"))) {
            return true
        }
        else if ((!duplicated_status) && (value?.hasOwnProperty("status"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof StepperItemAttribute")
        }
    }
    static isStepperItemInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof StepperItemInterface")
    }
    static isSticky(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (Sticky.None)) {
            return true
        }
        else if ((value) === (Sticky.Normal)) {
            return true
        }
        else if ((value) === (Sticky.Opacity)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof Sticky")
        }
    }
    static isStickyStyle(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (StickyStyle.None)) {
            return true
        }
        else if ((value) === (StickyStyle.Header)) {
            return true
        }
        else if ((value) === (StickyStyle.Footer)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof StickyStyle")
        }
    }
    static isStyledString(value: object|string|number|undefined|null|boolean, duplicated_length: boolean): boolean {
        if ((!duplicated_length) && (value?.hasOwnProperty("length"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof StyledString")
        }
    }
    static isStyledStringChangedListener(value: object|string|number|undefined|null|boolean, duplicated_onWillChange: boolean, duplicated_onDidChange: boolean): boolean {
        if ((!duplicated_onWillChange) && (value?.hasOwnProperty("onWillChange"))) {
            return true
        }
        else if ((!duplicated_onDidChange) && (value?.hasOwnProperty("onDidChange"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof StyledStringChangedListener")
        }
    }
    static isStyledStringChangeValue(value: object|string|number|undefined|null|boolean, duplicated_range: boolean, duplicated_replacementString: boolean, duplicated_previewText: boolean): boolean {
        if ((!duplicated_range) && (value?.hasOwnProperty("range"))) {
            return true
        }
        else if ((!duplicated_replacementString) && (value?.hasOwnProperty("replacementString"))) {
            return true
        }
        else if ((!duplicated_previewText) && (value?.hasOwnProperty("previewText"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof StyledStringChangeValue")
        }
    }
    static isStyledStringController(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof StyledStringController")
    }
    static isStyledStringKey(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (StyledStringKey.FONT)) {
            return true
        }
        else if ((value) === (StyledStringKey.DECORATION)) {
            return true
        }
        else if ((value) === (StyledStringKey.BASELINE_OFFSET)) {
            return true
        }
        else if ((value) === (StyledStringKey.LETTER_SPACING)) {
            return true
        }
        else if ((value) === (StyledStringKey.TEXT_SHADOW)) {
            return true
        }
        else if ((value) === (StyledStringKey.LINE_HEIGHT)) {
            return true
        }
        else if ((value) === (StyledStringKey.BACKGROUND_COLOR)) {
            return true
        }
        else if ((value) === (StyledStringKey.URL)) {
            return true
        }
        else if ((value) === (StyledStringKey.GESTURE)) {
            return true
        }
        else if ((value) === (StyledStringKey.PARAGRAPH_STYLE)) {
            return true
        }
        else if ((value) === (StyledStringKey.IMAGE)) {
            return true
        }
        else if ((value) === (StyledStringKey.CUSTOM_SPAN)) {
            return true
        }
        else if ((value) === (StyledStringKey.USER_DATA)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof StyledStringKey")
        }
    }
    static isStyleOptions(value: object|string|number|undefined|null|boolean, duplicated_start: boolean, duplicated_length: boolean, duplicated_styledKey: boolean, duplicated_styledValue: boolean): boolean {
        if ((!duplicated_styledKey) && (value?.hasOwnProperty("styledKey"))) {
            return true
        }
        else if ((!duplicated_styledValue) && (value?.hasOwnProperty("styledValue"))) {
            return true
        }
        else if ((!duplicated_start) && (value?.hasOwnProperty("start"))) {
            return true
        }
        else if ((!duplicated_length) && (value?.hasOwnProperty("length"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof StyleOptions")
        }
    }
    static isSubMenuExpandingMode(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (SubMenuExpandingMode.SIDE_EXPAND)) {
            return true
        }
        else if ((value) === (SubMenuExpandingMode.EMBEDDED_EXPAND)) {
            return true
        }
        else if ((value) === (SubMenuExpandingMode.STACK_EXPAND)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SubMenuExpandingMode")
        }
    }
    static isSubmitEvent(value: object|string|number|undefined|null|boolean, duplicated_text: boolean): boolean {
        if ((!duplicated_text) && (value?.hasOwnProperty("text"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SubmitEvent")
        }
    }
    static isSubscribaleAbstract(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof SubscribaleAbstract")
    }
    static isSubTabBarStyle(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof SubTabBarStyle")
    }
    static isSummary(value: object|string|number|undefined|null|boolean, duplicated__SummaryStub: boolean): boolean {
        if ((!duplicated__SummaryStub) && (value?.hasOwnProperty("_SummaryStub"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof Summary")
        }
    }
    static isSurfaceRect(value: object|string|number|undefined|null|boolean, duplicated_offsetX: boolean, duplicated_offsetY: boolean, duplicated_surfaceWidth: boolean, duplicated_surfaceHeight: boolean): boolean {
        if ((!duplicated_surfaceWidth) && (value?.hasOwnProperty("surfaceWidth"))) {
            return true
        }
        else if ((!duplicated_surfaceHeight) && (value?.hasOwnProperty("surfaceHeight"))) {
            return true
        }
        else if ((!duplicated_offsetX) && (value?.hasOwnProperty("offsetX"))) {
            return true
        }
        else if ((!duplicated_offsetY) && (value?.hasOwnProperty("offsetY"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SurfaceRect")
        }
    }
    static isSurfaceRotationOptions(value: object|string|number|undefined|null|boolean, duplicated_lock: boolean): boolean {
        if ((!duplicated_lock) && (value?.hasOwnProperty("lock"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SurfaceRotationOptions")
        }
    }
    static isSwipeActionItem(value: object|string|number|undefined|null|boolean, duplicated_builder: boolean, duplicated_actionAreaDistance: boolean, duplicated_onAction: boolean, duplicated_onEnterActionArea: boolean, duplicated_onExitActionArea: boolean, duplicated_onStateChange: boolean): boolean {
        if ((!duplicated_builder) && (value?.hasOwnProperty("builder"))) {
            return true
        }
        else if ((!duplicated_actionAreaDistance) && (value?.hasOwnProperty("actionAreaDistance"))) {
            return true
        }
        else if ((!duplicated_onAction) && (value?.hasOwnProperty("onAction"))) {
            return true
        }
        else if ((!duplicated_onEnterActionArea) && (value?.hasOwnProperty("onEnterActionArea"))) {
            return true
        }
        else if ((!duplicated_onExitActionArea) && (value?.hasOwnProperty("onExitActionArea"))) {
            return true
        }
        else if ((!duplicated_onStateChange) && (value?.hasOwnProperty("onStateChange"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SwipeActionItem")
        }
    }
    static isSwipeActionOptions(value: object|string|number|undefined|null|boolean, duplicated_start: boolean, duplicated_end: boolean, duplicated_edgeEffect: boolean, duplicated_onOffsetChange: boolean): boolean {
        if ((!duplicated_start) && (value?.hasOwnProperty("start"))) {
            return true
        }
        else if ((!duplicated_end) && (value?.hasOwnProperty("end"))) {
            return true
        }
        else if ((!duplicated_edgeEffect) && (value?.hasOwnProperty("edgeEffect"))) {
            return true
        }
        else if ((!duplicated_onOffsetChange) && (value?.hasOwnProperty("onOffsetChange"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SwipeActionOptions")
        }
    }
    static isSwipeActionState(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (SwipeActionState.COLLAPSED)) {
            return true
        }
        else if ((value) === (SwipeActionState.EXPANDED)) {
            return true
        }
        else if ((value) === (SwipeActionState.ACTIONING)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SwipeActionState")
        }
    }
    static isSwipeDirection(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (SwipeDirection.None)) {
            return true
        }
        else if ((value) === (SwipeDirection.Horizontal)) {
            return true
        }
        else if ((value) === (SwipeDirection.Vertical)) {
            return true
        }
        else if ((value) === (SwipeDirection.All)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SwipeDirection")
        }
    }
    static isSwipeEdgeEffect(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (SwipeEdgeEffect.Spring)) {
            return true
        }
        else if ((value) === (SwipeEdgeEffect.None)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SwipeEdgeEffect")
        }
    }
    static isSwipeGestureEvent(value: object|string|number|undefined|null|boolean, duplicated_angle: boolean, duplicated_speed: boolean): boolean {
        if ((!duplicated_angle) && (value?.hasOwnProperty("angle"))) {
            return true
        }
        else if ((!duplicated_speed) && (value?.hasOwnProperty("speed"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SwipeGestureEvent")
        }
    }
    static isSwipeGestureHandler(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof SwipeGestureHandler")
    }
    static isSwipeGestureHandlerOptions(value: object|string|number|undefined|null|boolean, duplicated_fingers: boolean, duplicated_direction: boolean, duplicated_speed: boolean): boolean {
        if ((!duplicated_fingers) && (value?.hasOwnProperty("fingers"))) {
            return true
        }
        else if ((!duplicated_direction) && (value?.hasOwnProperty("direction"))) {
            return true
        }
        else if ((!duplicated_speed) && (value?.hasOwnProperty("speed"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SwipeGestureHandlerOptions")
        }
    }
    static isSwipeGestureInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof SwipeGestureInterface")
    }
    static isSwiperAnimationEvent(value: object|string|number|undefined|null|boolean, duplicated_currentOffset: boolean, duplicated_targetOffset: boolean, duplicated_velocity: boolean): boolean {
        if ((!duplicated_currentOffset) && (value?.hasOwnProperty("currentOffset"))) {
            return true
        }
        else if ((!duplicated_targetOffset) && (value?.hasOwnProperty("targetOffset"))) {
            return true
        }
        else if ((!duplicated_velocity) && (value?.hasOwnProperty("velocity"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SwiperAnimationEvent")
        }
    }
    static isSwiperAttribute(value: object|string|number|undefined|null|boolean, duplicated_index: boolean, duplicated_autoPlay: boolean, duplicated_interval: boolean, duplicated_indicator: boolean, duplicated_loop: boolean, duplicated_duration: boolean, duplicated_vertical: boolean, duplicated_itemSpace: boolean, duplicated_displayMode: boolean, duplicated_cachedCount: boolean, duplicated_effectMode: boolean, duplicated_disableSwipe: boolean, duplicated_curve: boolean, duplicated_onChange: boolean, duplicated_indicatorStyle: boolean, duplicated_onAnimationStart: boolean, duplicated_onAnimationEnd: boolean, duplicated_onGestureSwipe: boolean, duplicated_nestedScroll: boolean, duplicated_customContentTransition: boolean, duplicated_onContentDidScroll: boolean, duplicated_indicatorInteractive: boolean): boolean {
        if ((!duplicated_index) && (value?.hasOwnProperty("index"))) {
            return true
        }
        else if ((!duplicated_autoPlay) && (value?.hasOwnProperty("autoPlay"))) {
            return true
        }
        else if ((!duplicated_interval) && (value?.hasOwnProperty("interval"))) {
            return true
        }
        else if ((!duplicated_indicator) && (value?.hasOwnProperty("indicator"))) {
            return true
        }
        else if ((!duplicated_loop) && (value?.hasOwnProperty("loop"))) {
            return true
        }
        else if ((!duplicated_duration) && (value?.hasOwnProperty("duration"))) {
            return true
        }
        else if ((!duplicated_vertical) && (value?.hasOwnProperty("vertical"))) {
            return true
        }
        else if ((!duplicated_itemSpace) && (value?.hasOwnProperty("itemSpace"))) {
            return true
        }
        else if ((!duplicated_displayMode) && (value?.hasOwnProperty("displayMode"))) {
            return true
        }
        else if ((!duplicated_cachedCount) && (value?.hasOwnProperty("cachedCount"))) {
            return true
        }
        else if ((!duplicated_effectMode) && (value?.hasOwnProperty("effectMode"))) {
            return true
        }
        else if ((!duplicated_disableSwipe) && (value?.hasOwnProperty("disableSwipe"))) {
            return true
        }
        else if ((!duplicated_curve) && (value?.hasOwnProperty("curve"))) {
            return true
        }
        else if ((!duplicated_onChange) && (value?.hasOwnProperty("onChange"))) {
            return true
        }
        else if ((!duplicated_onAnimationStart) && (value?.hasOwnProperty("onAnimationStart"))) {
            return true
        }
        else if ((!duplicated_onAnimationEnd) && (value?.hasOwnProperty("onAnimationEnd"))) {
            return true
        }
        else if ((!duplicated_onGestureSwipe) && (value?.hasOwnProperty("onGestureSwipe"))) {
            return true
        }
        else if ((!duplicated_nestedScroll) && (value?.hasOwnProperty("nestedScroll"))) {
            return true
        }
        else if ((!duplicated_customContentTransition) && (value?.hasOwnProperty("customContentTransition"))) {
            return true
        }
        else if ((!duplicated_onContentDidScroll) && (value?.hasOwnProperty("onContentDidScroll"))) {
            return true
        }
        else if ((!duplicated_indicatorInteractive) && (value?.hasOwnProperty("indicatorInteractive"))) {
            return true
        }
        else if ((!duplicated_indicatorStyle) && (value?.hasOwnProperty("indicatorStyle"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SwiperAttribute")
        }
    }
    static isSwiperAutoFill(value: object|string|number|undefined|null|boolean, duplicated_minSize: boolean): boolean {
        if ((!duplicated_minSize) && (value?.hasOwnProperty("minSize"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SwiperAutoFill")
        }
    }
    static isSwiperContentAnimatedTransition(value: object|string|number|undefined|null|boolean, duplicated_timeout: boolean, duplicated_transition: boolean): boolean {
        if ((!duplicated_transition) && (value?.hasOwnProperty("transition"))) {
            return true
        }
        else if ((!duplicated_timeout) && (value?.hasOwnProperty("timeout"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SwiperContentAnimatedTransition")
        }
    }
    static isSwiperContentTransitionProxy(value: object|string|number|undefined|null|boolean, duplicated_selectedIndex: boolean, duplicated_index: boolean, duplicated_position: boolean, duplicated_mainAxisLength: boolean): boolean {
        if ((!duplicated_selectedIndex) && (value?.hasOwnProperty("selectedIndex"))) {
            return true
        }
        else if ((!duplicated_index) && (value?.hasOwnProperty("index"))) {
            return true
        }
        else if ((!duplicated_position) && (value?.hasOwnProperty("position"))) {
            return true
        }
        else if ((!duplicated_mainAxisLength) && (value?.hasOwnProperty("mainAxisLength"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SwiperContentTransitionProxy")
        }
    }
    static isSwiperController(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof SwiperController")
    }
    static isSwiperDisplayMode(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (SwiperDisplayMode.Stretch)) {
            return true
        }
        else if ((value) === (SwiperDisplayMode.AutoLinear)) {
            return true
        }
        else if ((value) === (SwiperDisplayMode.STRETCH)) {
            return true
        }
        else if ((value) === (SwiperDisplayMode.AUTO_LINEAR)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SwiperDisplayMode")
        }
    }
    static isSwiperInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof SwiperInterface")
    }
    static isSwiperNestedScrollMode(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (SwiperNestedScrollMode.SELF_ONLY)) {
            return true
        }
        else if ((value) === (SwiperNestedScrollMode.SELF_FIRST)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SwiperNestedScrollMode")
        }
    }
    static isSwitchStyle(value: object|string|number|undefined|null|boolean, duplicated_pointRadius: boolean, duplicated_unselectedColor: boolean, duplicated_pointColor: boolean, duplicated_trackBorderRadius: boolean): boolean {
        if ((!duplicated_pointRadius) && (value?.hasOwnProperty("pointRadius"))) {
            return true
        }
        else if ((!duplicated_unselectedColor) && (value?.hasOwnProperty("unselectedColor"))) {
            return true
        }
        else if ((!duplicated_pointColor) && (value?.hasOwnProperty("pointColor"))) {
            return true
        }
        else if ((!duplicated_trackBorderRadius) && (value?.hasOwnProperty("trackBorderRadius"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SwitchStyle")
        }
    }
    static isSymbolEffect(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof SymbolEffect")
    }
    static isSymbolEffectStrategy(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (SymbolEffectStrategy.NONE)) {
            return true
        }
        else if ((value) === (SymbolEffectStrategy.SCALE)) {
            return true
        }
        else if ((value) === (SymbolEffectStrategy.HIERARCHICAL)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SymbolEffectStrategy")
        }
    }
    static isSymbolGlyphAttribute(value: object|string|number|undefined|null|boolean, duplicated_fontSize: boolean, duplicated_fontColor: boolean, duplicated_fontWeight: boolean, duplicated_effectStrategy: boolean, duplicated_renderingStrategy: boolean): boolean {
        if ((!duplicated_fontSize) && (value?.hasOwnProperty("fontSize"))) {
            return true
        }
        else if ((!duplicated_fontColor) && (value?.hasOwnProperty("fontColor"))) {
            return true
        }
        else if ((!duplicated_fontWeight) && (value?.hasOwnProperty("fontWeight"))) {
            return true
        }
        else if ((!duplicated_effectStrategy) && (value?.hasOwnProperty("effectStrategy"))) {
            return true
        }
        else if ((!duplicated_renderingStrategy) && (value?.hasOwnProperty("renderingStrategy"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SymbolGlyphAttribute")
        }
    }
    static isSymbolGlyphInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof SymbolGlyphInterface")
    }
    static isSymbolGlyphModifier(value: object|string|number|undefined|null|boolean, duplicated__SymbolGlyphModifierStub: boolean): boolean {
        if ((!duplicated__SymbolGlyphModifierStub) && (value?.hasOwnProperty("_SymbolGlyphModifierStub"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SymbolGlyphModifier")
        }
    }
    static isSymbolRenderingStrategy(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (SymbolRenderingStrategy.SINGLE)) {
            return true
        }
        else if ((value) === (SymbolRenderingStrategy.MULTIPLE_COLOR)) {
            return true
        }
        else if ((value) === (SymbolRenderingStrategy.MULTIPLE_OPACITY)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SymbolRenderingStrategy")
        }
    }
    static isSymbolSpanAttribute(value: object|string|number|undefined|null|boolean, duplicated_fontSize: boolean, duplicated_fontColor: boolean, duplicated_fontWeight: boolean, duplicated_effectStrategy: boolean, duplicated_renderingStrategy: boolean, duplicated_attributeModifier: boolean): boolean {
        if ((!duplicated_fontSize) && (value?.hasOwnProperty("fontSize"))) {
            return true
        }
        else if ((!duplicated_fontColor) && (value?.hasOwnProperty("fontColor"))) {
            return true
        }
        else if ((!duplicated_fontWeight) && (value?.hasOwnProperty("fontWeight"))) {
            return true
        }
        else if ((!duplicated_effectStrategy) && (value?.hasOwnProperty("effectStrategy"))) {
            return true
        }
        else if ((!duplicated_renderingStrategy) && (value?.hasOwnProperty("renderingStrategy"))) {
            return true
        }
        else if ((!duplicated_attributeModifier) && (value?.hasOwnProperty("attributeModifier"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SymbolSpanAttribute")
        }
    }
    static isSymbolSpanInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof SymbolSpanInterface")
    }
    static isSystemBarStyle(value: object|string|number|undefined|null|boolean, duplicated__SystemBarStyleStub: boolean): boolean {
        if ((!duplicated__SystemBarStyleStub) && (value?.hasOwnProperty("_SystemBarStyleStub"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SystemBarStyle")
        }
    }
    static isSystemOps(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof SystemOps")
    }
    static isTabBarIconStyle(value: object|string|number|undefined|null|boolean, duplicated_selectedColor: boolean, duplicated_unselectedColor: boolean): boolean {
        if ((!duplicated_selectedColor) && (value?.hasOwnProperty("selectedColor"))) {
            return true
        }
        else if ((!duplicated_unselectedColor) && (value?.hasOwnProperty("unselectedColor"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TabBarIconStyle")
        }
    }
    static isTabBarOptions(value: object|string|number|undefined|null|boolean, duplicated_icon: boolean, duplicated_text: boolean): boolean {
        if ((!duplicated_icon) && (value?.hasOwnProperty("icon"))) {
            return true
        }
        else if ((!duplicated_text) && (value?.hasOwnProperty("text"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TabBarOptions")
        }
    }
    static isTabBarSymbol(value: object|string|number|undefined|null|boolean, duplicated_normal: boolean, duplicated_selected: boolean): boolean {
        if ((!duplicated_normal) && (value?.hasOwnProperty("normal"))) {
            return true
        }
        else if ((!duplicated_selected) && (value?.hasOwnProperty("selected"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TabBarSymbol")
        }
    }
    static isTabContentAnimatedTransition(value: object|string|number|undefined|null|boolean, duplicated_timeout: boolean, duplicated_transition: boolean): boolean {
        if ((!duplicated_transition) && (value?.hasOwnProperty("transition"))) {
            return true
        }
        else if ((!duplicated_timeout) && (value?.hasOwnProperty("timeout"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TabContentAnimatedTransition")
        }
    }
    static isTabContentAttribute(value: object|string|number|undefined|null|boolean, duplicated_tabBar: boolean, duplicated_onWillShow: boolean, duplicated_onWillHide: boolean): boolean {
        if ((!duplicated_tabBar) && (value?.hasOwnProperty("tabBar"))) {
            return true
        }
        else if ((!duplicated_onWillShow) && (value?.hasOwnProperty("onWillShow"))) {
            return true
        }
        else if ((!duplicated_onWillHide) && (value?.hasOwnProperty("onWillHide"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TabContentAttribute")
        }
    }
    static isTabContentInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof TabContentInterface")
    }
    static isTabContentTransitionProxy(value: object|string|number|undefined|null|boolean, duplicated_from: boolean, duplicated_to: boolean): boolean {
        if ((!duplicated_from) && (value?.hasOwnProperty("from"))) {
            return true
        }
        else if ((!duplicated_to) && (value?.hasOwnProperty("to"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TabContentTransitionProxy")
        }
    }
    static isTabsAnimationEvent(value: object|string|number|undefined|null|boolean, duplicated_currentOffset: boolean, duplicated_targetOffset: boolean, duplicated_velocity: boolean): boolean {
        if ((!duplicated_currentOffset) && (value?.hasOwnProperty("currentOffset"))) {
            return true
        }
        else if ((!duplicated_targetOffset) && (value?.hasOwnProperty("targetOffset"))) {
            return true
        }
        else if ((!duplicated_velocity) && (value?.hasOwnProperty("velocity"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TabsAnimationEvent")
        }
    }
    static isTabsAttribute(value: object|string|number|undefined|null|boolean, duplicated_vertical: boolean, duplicated_barPosition: boolean, duplicated_scrollable: boolean, duplicated_barMode: boolean, duplicated_barWidth: boolean, duplicated_barHeight: boolean, duplicated_animationDuration: boolean, duplicated_animationMode: boolean, duplicated_edgeEffect: boolean, duplicated_onChange: boolean, duplicated_onTabBarClick: boolean, duplicated_onAnimationStart: boolean, duplicated_onAnimationEnd: boolean, duplicated_onGestureSwipe: boolean, duplicated_fadingEdge: boolean, duplicated_divider: boolean, duplicated_barOverlap: boolean, duplicated_barBackgroundColor: boolean, duplicated_barGridAlign: boolean, duplicated_customContentTransition: boolean, duplicated_barBackgroundBlurStyle: boolean, duplicated_barBackgroundEffect: boolean, duplicated_onContentWillChange: boolean): boolean {
        if ((!duplicated_vertical) && (value?.hasOwnProperty("vertical"))) {
            return true
        }
        else if ((!duplicated_barPosition) && (value?.hasOwnProperty("barPosition"))) {
            return true
        }
        else if ((!duplicated_scrollable) && (value?.hasOwnProperty("scrollable"))) {
            return true
        }
        else if ((!duplicated_barMode) && (value?.hasOwnProperty("barMode"))) {
            return true
        }
        else if ((!duplicated_barWidth) && (value?.hasOwnProperty("barWidth"))) {
            return true
        }
        else if ((!duplicated_barHeight) && (value?.hasOwnProperty("barHeight"))) {
            return true
        }
        else if ((!duplicated_animationDuration) && (value?.hasOwnProperty("animationDuration"))) {
            return true
        }
        else if ((!duplicated_animationMode) && (value?.hasOwnProperty("animationMode"))) {
            return true
        }
        else if ((!duplicated_edgeEffect) && (value?.hasOwnProperty("edgeEffect"))) {
            return true
        }
        else if ((!duplicated_onChange) && (value?.hasOwnProperty("onChange"))) {
            return true
        }
        else if ((!duplicated_onTabBarClick) && (value?.hasOwnProperty("onTabBarClick"))) {
            return true
        }
        else if ((!duplicated_onAnimationStart) && (value?.hasOwnProperty("onAnimationStart"))) {
            return true
        }
        else if ((!duplicated_onAnimationEnd) && (value?.hasOwnProperty("onAnimationEnd"))) {
            return true
        }
        else if ((!duplicated_onGestureSwipe) && (value?.hasOwnProperty("onGestureSwipe"))) {
            return true
        }
        else if ((!duplicated_fadingEdge) && (value?.hasOwnProperty("fadingEdge"))) {
            return true
        }
        else if ((!duplicated_divider) && (value?.hasOwnProperty("divider"))) {
            return true
        }
        else if ((!duplicated_barOverlap) && (value?.hasOwnProperty("barOverlap"))) {
            return true
        }
        else if ((!duplicated_barBackgroundColor) && (value?.hasOwnProperty("barBackgroundColor"))) {
            return true
        }
        else if ((!duplicated_barGridAlign) && (value?.hasOwnProperty("barGridAlign"))) {
            return true
        }
        else if ((!duplicated_customContentTransition) && (value?.hasOwnProperty("customContentTransition"))) {
            return true
        }
        else if ((!duplicated_barBackgroundBlurStyle) && (value?.hasOwnProperty("barBackgroundBlurStyle"))) {
            return true
        }
        else if ((!duplicated_barBackgroundEffect) && (value?.hasOwnProperty("barBackgroundEffect"))) {
            return true
        }
        else if ((!duplicated_onContentWillChange) && (value?.hasOwnProperty("onContentWillChange"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TabsAttribute")
        }
    }
    static isTabsController(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof TabsController")
    }
    static isTabsInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof TabsInterface")
    }
    static isTabsOptions(value: object|string|number|undefined|null|boolean, duplicated_barPosition: boolean, duplicated_index: boolean, duplicated_controller: boolean): boolean {
        if ((!duplicated_barPosition) && (value?.hasOwnProperty("barPosition"))) {
            return true
        }
        else if ((!duplicated_index) && (value?.hasOwnProperty("index"))) {
            return true
        }
        else if ((!duplicated_controller) && (value?.hasOwnProperty("controller"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TabsOptions")
        }
    }
    static isTapGestureEvent(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof TapGestureEvent")
    }
    static isTapGestureHandler(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof TapGestureHandler")
    }
    static isTapGestureHandlerOptions(value: object|string|number|undefined|null|boolean, duplicated_count: boolean, duplicated_fingers: boolean): boolean {
        if ((!duplicated_count) && (value?.hasOwnProperty("count"))) {
            return true
        }
        else if ((!duplicated_fingers) && (value?.hasOwnProperty("fingers"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TapGestureHandlerOptions")
        }
    }
    static isTapGestureInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof TapGestureInterface")
    }
    static isTapGestureParameters(value: object|string|number|undefined|null|boolean, duplicated_count: boolean, duplicated_fingers: boolean, duplicated_distanceThreshold: boolean): boolean {
        if ((!duplicated_count) && (value?.hasOwnProperty("count"))) {
            return true
        }
        else if ((!duplicated_fingers) && (value?.hasOwnProperty("fingers"))) {
            return true
        }
        else if ((!duplicated_distanceThreshold) && (value?.hasOwnProperty("distanceThreshold"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TapGestureParameters")
        }
    }
    static isTemplateOptions(value: object|string|number|undefined|null|boolean, duplicated_cachedCount: boolean): boolean {
        if ((!duplicated_cachedCount) && (value?.hasOwnProperty("cachedCount"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TemplateOptions")
        }
    }
    static isTerminationInfo(value: object|string|number|undefined|null|boolean, duplicated_code: boolean, duplicated_want: boolean): boolean {
        if ((!duplicated_code) && (value?.hasOwnProperty("code"))) {
            return true
        }
        else if ((!duplicated_want) && (value?.hasOwnProperty("want"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TerminationInfo")
        }
    }
    static isTextAlign(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (TextAlign.Center)) {
            return true
        }
        else if ((value) === (TextAlign.Start)) {
            return true
        }
        else if ((value) === (TextAlign.End)) {
            return true
        }
        else if ((value) === (TextAlign.JUSTIFY)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TextAlign")
        }
    }
    static isTextAreaAttribute(value: object|string|number|undefined|null|boolean, duplicated_placeholderColor: boolean, duplicated_placeholderFont: boolean, duplicated_enterKeyType: boolean, duplicated_textAlign: boolean, duplicated_caretColor: boolean, duplicated_fontColor: boolean, duplicated_fontSize: boolean, duplicated_fontStyle: boolean, duplicated_fontWeight: boolean, duplicated_fontFamily: boolean, duplicated_textOverflow: boolean, duplicated_textIndent: boolean, duplicated_caretStyle: boolean, duplicated_selectedBackgroundColor: boolean, duplicated_onSubmit: boolean, duplicated_onChange: boolean, duplicated_onTextSelectionChange: boolean, duplicated_onContentScroll: boolean, duplicated_onEditChange: boolean, duplicated_onCopy: boolean, duplicated_onCut: boolean, duplicated_onPaste: boolean, duplicated_copyOption: boolean, duplicated_enableKeyboardOnFocus: boolean, duplicated_maxLength: boolean, duplicated_style: boolean, duplicated_barState: boolean, duplicated_selectionMenuHidden: boolean, duplicated_minFontSize: boolean, duplicated_maxFontSize: boolean, duplicated_heightAdaptivePolicy: boolean, duplicated_maxLines: boolean, duplicated_wordBreak: boolean, duplicated_lineBreakStrategy: boolean, duplicated_decoration: boolean, duplicated_letterSpacing: boolean, duplicated_lineSpacing: boolean, duplicated_lineHeight: boolean, duplicated_type: boolean, duplicated_enableAutoFill: boolean, duplicated_contentType: boolean, duplicated_fontFeature: boolean, duplicated_onWillInsert: boolean, duplicated_onDidInsert: boolean, duplicated_onWillDelete: boolean, duplicated_onDidDelete: boolean, duplicated_editMenuOptions: boolean, duplicated_enablePreviewText: boolean, duplicated_enableHapticFeedback: boolean): boolean {
        if ((!duplicated_placeholderColor) && (value?.hasOwnProperty("placeholderColor"))) {
            return true
        }
        else if ((!duplicated_placeholderFont) && (value?.hasOwnProperty("placeholderFont"))) {
            return true
        }
        else if ((!duplicated_enterKeyType) && (value?.hasOwnProperty("enterKeyType"))) {
            return true
        }
        else if ((!duplicated_textAlign) && (value?.hasOwnProperty("textAlign"))) {
            return true
        }
        else if ((!duplicated_caretColor) && (value?.hasOwnProperty("caretColor"))) {
            return true
        }
        else if ((!duplicated_fontColor) && (value?.hasOwnProperty("fontColor"))) {
            return true
        }
        else if ((!duplicated_fontSize) && (value?.hasOwnProperty("fontSize"))) {
            return true
        }
        else if ((!duplicated_fontStyle) && (value?.hasOwnProperty("fontStyle"))) {
            return true
        }
        else if ((!duplicated_fontWeight) && (value?.hasOwnProperty("fontWeight"))) {
            return true
        }
        else if ((!duplicated_fontFamily) && (value?.hasOwnProperty("fontFamily"))) {
            return true
        }
        else if ((!duplicated_textOverflow) && (value?.hasOwnProperty("textOverflow"))) {
            return true
        }
        else if ((!duplicated_textIndent) && (value?.hasOwnProperty("textIndent"))) {
            return true
        }
        else if ((!duplicated_caretStyle) && (value?.hasOwnProperty("caretStyle"))) {
            return true
        }
        else if ((!duplicated_selectedBackgroundColor) && (value?.hasOwnProperty("selectedBackgroundColor"))) {
            return true
        }
        else if ((!duplicated_onSubmit) && (value?.hasOwnProperty("onSubmit"))) {
            return true
        }
        else if ((!duplicated_onChange) && (value?.hasOwnProperty("onChange"))) {
            return true
        }
        else if ((!duplicated_onTextSelectionChange) && (value?.hasOwnProperty("onTextSelectionChange"))) {
            return true
        }
        else if ((!duplicated_onContentScroll) && (value?.hasOwnProperty("onContentScroll"))) {
            return true
        }
        else if ((!duplicated_onEditChange) && (value?.hasOwnProperty("onEditChange"))) {
            return true
        }
        else if ((!duplicated_onCopy) && (value?.hasOwnProperty("onCopy"))) {
            return true
        }
        else if ((!duplicated_onCut) && (value?.hasOwnProperty("onCut"))) {
            return true
        }
        else if ((!duplicated_onPaste) && (value?.hasOwnProperty("onPaste"))) {
            return true
        }
        else if ((!duplicated_copyOption) && (value?.hasOwnProperty("copyOption"))) {
            return true
        }
        else if ((!duplicated_enableKeyboardOnFocus) && (value?.hasOwnProperty("enableKeyboardOnFocus"))) {
            return true
        }
        else if ((!duplicated_maxLength) && (value?.hasOwnProperty("maxLength"))) {
            return true
        }
        else if ((!duplicated_style) && (value?.hasOwnProperty("style"))) {
            return true
        }
        else if ((!duplicated_barState) && (value?.hasOwnProperty("barState"))) {
            return true
        }
        else if ((!duplicated_selectionMenuHidden) && (value?.hasOwnProperty("selectionMenuHidden"))) {
            return true
        }
        else if ((!duplicated_minFontSize) && (value?.hasOwnProperty("minFontSize"))) {
            return true
        }
        else if ((!duplicated_maxFontSize) && (value?.hasOwnProperty("maxFontSize"))) {
            return true
        }
        else if ((!duplicated_heightAdaptivePolicy) && (value?.hasOwnProperty("heightAdaptivePolicy"))) {
            return true
        }
        else if ((!duplicated_maxLines) && (value?.hasOwnProperty("maxLines"))) {
            return true
        }
        else if ((!duplicated_wordBreak) && (value?.hasOwnProperty("wordBreak"))) {
            return true
        }
        else if ((!duplicated_lineBreakStrategy) && (value?.hasOwnProperty("lineBreakStrategy"))) {
            return true
        }
        else if ((!duplicated_decoration) && (value?.hasOwnProperty("decoration"))) {
            return true
        }
        else if ((!duplicated_letterSpacing) && (value?.hasOwnProperty("letterSpacing"))) {
            return true
        }
        else if ((!duplicated_lineSpacing) && (value?.hasOwnProperty("lineSpacing"))) {
            return true
        }
        else if ((!duplicated_lineHeight) && (value?.hasOwnProperty("lineHeight"))) {
            return true
        }
        else if ((!duplicated_type) && (value?.hasOwnProperty("type"))) {
            return true
        }
        else if ((!duplicated_enableAutoFill) && (value?.hasOwnProperty("enableAutoFill"))) {
            return true
        }
        else if ((!duplicated_contentType) && (value?.hasOwnProperty("contentType"))) {
            return true
        }
        else if ((!duplicated_fontFeature) && (value?.hasOwnProperty("fontFeature"))) {
            return true
        }
        else if ((!duplicated_onWillInsert) && (value?.hasOwnProperty("onWillInsert"))) {
            return true
        }
        else if ((!duplicated_onDidInsert) && (value?.hasOwnProperty("onDidInsert"))) {
            return true
        }
        else if ((!duplicated_onWillDelete) && (value?.hasOwnProperty("onWillDelete"))) {
            return true
        }
        else if ((!duplicated_onDidDelete) && (value?.hasOwnProperty("onDidDelete"))) {
            return true
        }
        else if ((!duplicated_editMenuOptions) && (value?.hasOwnProperty("editMenuOptions"))) {
            return true
        }
        else if ((!duplicated_enablePreviewText) && (value?.hasOwnProperty("enablePreviewText"))) {
            return true
        }
        else if ((!duplicated_enableHapticFeedback) && (value?.hasOwnProperty("enableHapticFeedback"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TextAreaAttribute")
        }
    }
    static isTextAreaController(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof TextAreaController")
    }
    static isTextAreaInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof TextAreaInterface")
    }
    static isTextAreaOptions(value: object|string|number|undefined|null|boolean, duplicated_placeholder: boolean, duplicated_text: boolean, duplicated_controller: boolean): boolean {
        if ((!duplicated_placeholder) && (value?.hasOwnProperty("placeholder"))) {
            return true
        }
        else if ((!duplicated_text) && (value?.hasOwnProperty("text"))) {
            return true
        }
        else if ((!duplicated_controller) && (value?.hasOwnProperty("controller"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TextAreaOptions")
        }
    }
    static isTextAreaType(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (TextAreaType.NORMAL)) {
            return true
        }
        else if ((value) === (TextAreaType.NUMBER)) {
            return true
        }
        else if ((value) === (TextAreaType.PHONE_NUMBER)) {
            return true
        }
        else if ((value) === (TextAreaType.EMAIL)) {
            return true
        }
        else if ((value) === (TextAreaType.NUMBER_DECIMAL)) {
            return true
        }
        else if ((value) === (TextAreaType.URL)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TextAreaType")
        }
    }
    static isTextAttribute(value: object|string|number|undefined|null|boolean, duplicated_font: boolean, duplicated_fontColor: boolean, duplicated_fontSize: boolean, duplicated_minFontSize: boolean, duplicated_maxFontSize: boolean, duplicated_minFontScale: boolean, duplicated_maxFontScale: boolean, duplicated_fontStyle: boolean, duplicated_fontWeight: boolean, duplicated_lineSpacing: boolean, duplicated_textAlign: boolean, duplicated_lineHeight: boolean, duplicated_textOverflow: boolean, duplicated_fontFamily: boolean, duplicated_maxLines: boolean, duplicated_decoration: boolean, duplicated_letterSpacing: boolean, duplicated_textCase: boolean, duplicated_baselineOffset: boolean, duplicated_copyOption: boolean, duplicated_draggable: boolean, duplicated_textShadow: boolean, duplicated_heightAdaptivePolicy: boolean, duplicated_textIndent: boolean, duplicated_wordBreak: boolean, duplicated_lineBreakStrategy: boolean, duplicated_onCopy: boolean, duplicated_caretColor: boolean, duplicated_selectedBackgroundColor: boolean, duplicated_ellipsisMode: boolean, duplicated_enableDataDetector: boolean, duplicated_dataDetectorConfig: boolean, duplicated_onTextSelectionChange: boolean, duplicated_fontFeature: boolean, duplicated_privacySensitive: boolean, duplicated_textSelectable: boolean, duplicated_editMenuOptions: boolean, duplicated_halfLeading: boolean, duplicated_enableHapticFeedback: boolean): boolean {
        if ((!duplicated_font) && (value?.hasOwnProperty("font"))) {
            return true
        }
        else if ((!duplicated_fontColor) && (value?.hasOwnProperty("fontColor"))) {
            return true
        }
        else if ((!duplicated_fontSize) && (value?.hasOwnProperty("fontSize"))) {
            return true
        }
        else if ((!duplicated_minFontSize) && (value?.hasOwnProperty("minFontSize"))) {
            return true
        }
        else if ((!duplicated_maxFontSize) && (value?.hasOwnProperty("maxFontSize"))) {
            return true
        }
        else if ((!duplicated_minFontScale) && (value?.hasOwnProperty("minFontScale"))) {
            return true
        }
        else if ((!duplicated_maxFontScale) && (value?.hasOwnProperty("maxFontScale"))) {
            return true
        }
        else if ((!duplicated_fontStyle) && (value?.hasOwnProperty("fontStyle"))) {
            return true
        }
        else if ((!duplicated_fontWeight) && (value?.hasOwnProperty("fontWeight"))) {
            return true
        }
        else if ((!duplicated_lineSpacing) && (value?.hasOwnProperty("lineSpacing"))) {
            return true
        }
        else if ((!duplicated_textAlign) && (value?.hasOwnProperty("textAlign"))) {
            return true
        }
        else if ((!duplicated_lineHeight) && (value?.hasOwnProperty("lineHeight"))) {
            return true
        }
        else if ((!duplicated_textOverflow) && (value?.hasOwnProperty("textOverflow"))) {
            return true
        }
        else if ((!duplicated_fontFamily) && (value?.hasOwnProperty("fontFamily"))) {
            return true
        }
        else if ((!duplicated_maxLines) && (value?.hasOwnProperty("maxLines"))) {
            return true
        }
        else if ((!duplicated_decoration) && (value?.hasOwnProperty("decoration"))) {
            return true
        }
        else if ((!duplicated_letterSpacing) && (value?.hasOwnProperty("letterSpacing"))) {
            return true
        }
        else if ((!duplicated_textCase) && (value?.hasOwnProperty("textCase"))) {
            return true
        }
        else if ((!duplicated_baselineOffset) && (value?.hasOwnProperty("baselineOffset"))) {
            return true
        }
        else if ((!duplicated_copyOption) && (value?.hasOwnProperty("copyOption"))) {
            return true
        }
        else if ((!duplicated_draggable) && (value?.hasOwnProperty("draggable"))) {
            return true
        }
        else if ((!duplicated_textShadow) && (value?.hasOwnProperty("textShadow"))) {
            return true
        }
        else if ((!duplicated_heightAdaptivePolicy) && (value?.hasOwnProperty("heightAdaptivePolicy"))) {
            return true
        }
        else if ((!duplicated_textIndent) && (value?.hasOwnProperty("textIndent"))) {
            return true
        }
        else if ((!duplicated_wordBreak) && (value?.hasOwnProperty("wordBreak"))) {
            return true
        }
        else if ((!duplicated_lineBreakStrategy) && (value?.hasOwnProperty("lineBreakStrategy"))) {
            return true
        }
        else if ((!duplicated_onCopy) && (value?.hasOwnProperty("onCopy"))) {
            return true
        }
        else if ((!duplicated_caretColor) && (value?.hasOwnProperty("caretColor"))) {
            return true
        }
        else if ((!duplicated_selectedBackgroundColor) && (value?.hasOwnProperty("selectedBackgroundColor"))) {
            return true
        }
        else if ((!duplicated_ellipsisMode) && (value?.hasOwnProperty("ellipsisMode"))) {
            return true
        }
        else if ((!duplicated_enableDataDetector) && (value?.hasOwnProperty("enableDataDetector"))) {
            return true
        }
        else if ((!duplicated_dataDetectorConfig) && (value?.hasOwnProperty("dataDetectorConfig"))) {
            return true
        }
        else if ((!duplicated_onTextSelectionChange) && (value?.hasOwnProperty("onTextSelectionChange"))) {
            return true
        }
        else if ((!duplicated_fontFeature) && (value?.hasOwnProperty("fontFeature"))) {
            return true
        }
        else if ((!duplicated_privacySensitive) && (value?.hasOwnProperty("privacySensitive"))) {
            return true
        }
        else if ((!duplicated_textSelectable) && (value?.hasOwnProperty("textSelectable"))) {
            return true
        }
        else if ((!duplicated_editMenuOptions) && (value?.hasOwnProperty("editMenuOptions"))) {
            return true
        }
        else if ((!duplicated_halfLeading) && (value?.hasOwnProperty("halfLeading"))) {
            return true
        }
        else if ((!duplicated_enableHapticFeedback) && (value?.hasOwnProperty("enableHapticFeedback"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TextAttribute")
        }
    }
    static isTextBackgroundStyle(value: object|string|number|undefined|null|boolean, duplicated_color: boolean, duplicated_radius: boolean): boolean {
        if ((!duplicated_color) && (value?.hasOwnProperty("color"))) {
            return true
        }
        else if ((!duplicated_radius) && (value?.hasOwnProperty("radius"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TextBackgroundStyle")
        }
    }
    static isTextBaseController(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof TextBaseController")
    }
    static isTextBox(value: object|string|number|undefined|null|boolean, duplicated__TextBoxStub: boolean): boolean {
        if ((!duplicated__TextBoxStub) && (value?.hasOwnProperty("_TextBoxStub"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TextBox")
        }
    }
    static isTextCascadePickerRangeContent(value: object|string|number|undefined|null|boolean, duplicated_text: boolean, duplicated_children: boolean): boolean {
        if ((!duplicated_text) && (value?.hasOwnProperty("text"))) {
            return true
        }
        else if ((!duplicated_children) && (value?.hasOwnProperty("children"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TextCascadePickerRangeContent")
        }
    }
    static isTextCase(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (TextCase.Normal)) {
            return true
        }
        else if ((value) === (TextCase.LowerCase)) {
            return true
        }
        else if ((value) === (TextCase.UpperCase)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TextCase")
        }
    }
    static isTextClockAttribute(value: object|string|number|undefined|null|boolean, duplicated_format: boolean, duplicated_onDateChange: boolean, duplicated_fontColor: boolean, duplicated_fontSize: boolean, duplicated_fontStyle: boolean, duplicated_fontWeight: boolean, duplicated_fontFamily: boolean, duplicated_textShadow: boolean, duplicated_fontFeature: boolean, duplicated_contentModifier: boolean, duplicated_dateTimeOptions: boolean): boolean {
        if ((!duplicated_format) && (value?.hasOwnProperty("format"))) {
            return true
        }
        else if ((!duplicated_onDateChange) && (value?.hasOwnProperty("onDateChange"))) {
            return true
        }
        else if ((!duplicated_fontColor) && (value?.hasOwnProperty("fontColor"))) {
            return true
        }
        else if ((!duplicated_fontSize) && (value?.hasOwnProperty("fontSize"))) {
            return true
        }
        else if ((!duplicated_fontStyle) && (value?.hasOwnProperty("fontStyle"))) {
            return true
        }
        else if ((!duplicated_fontWeight) && (value?.hasOwnProperty("fontWeight"))) {
            return true
        }
        else if ((!duplicated_fontFamily) && (value?.hasOwnProperty("fontFamily"))) {
            return true
        }
        else if ((!duplicated_textShadow) && (value?.hasOwnProperty("textShadow"))) {
            return true
        }
        else if ((!duplicated_fontFeature) && (value?.hasOwnProperty("fontFeature"))) {
            return true
        }
        else if ((!duplicated_contentModifier) && (value?.hasOwnProperty("contentModifier"))) {
            return true
        }
        else if ((!duplicated_dateTimeOptions) && (value?.hasOwnProperty("dateTimeOptions"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TextClockAttribute")
        }
    }
    static isTextClockConfiguration(value: object|string|number|undefined|null|boolean, duplicated_timeZoneOffset: boolean, duplicated_started: boolean, duplicated_timeValue: boolean): boolean {
        if ((!duplicated_timeZoneOffset) && (value?.hasOwnProperty("timeZoneOffset"))) {
            return true
        }
        else if ((!duplicated_started) && (value?.hasOwnProperty("started"))) {
            return true
        }
        else if ((!duplicated_timeValue) && (value?.hasOwnProperty("timeValue"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TextClockConfiguration")
        }
    }
    static isTextClockController(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof TextClockController")
    }
    static isTextClockInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof TextClockInterface")
    }
    static isTextClockOptions(value: object|string|number|undefined|null|boolean, duplicated_timeZoneOffset: boolean, duplicated_controller: boolean): boolean {
        if ((!duplicated_timeZoneOffset) && (value?.hasOwnProperty("timeZoneOffset"))) {
            return true
        }
        else if ((!duplicated_controller) && (value?.hasOwnProperty("controller"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TextClockOptions")
        }
    }
    static isTextContentControllerBase(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof TextContentControllerBase")
    }
    static isTextContentStyle(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (TextContentStyle.DEFAULT)) {
            return true
        }
        else if ((value) === (TextContentStyle.INLINE)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TextContentStyle")
        }
    }
    static isTextController(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof TextController")
    }
    static isTextDataDetectorConfig(value: object|string|number|undefined|null|boolean, duplicated_types: boolean, duplicated_onDetectResultUpdate: boolean, duplicated_color: boolean, duplicated_decoration: boolean): boolean {
        if ((!duplicated_types) && (value?.hasOwnProperty("types"))) {
            return true
        }
        else if ((!duplicated_onDetectResultUpdate) && (value?.hasOwnProperty("onDetectResultUpdate"))) {
            return true
        }
        else if ((!duplicated_color) && (value?.hasOwnProperty("color"))) {
            return true
        }
        else if ((!duplicated_decoration) && (value?.hasOwnProperty("decoration"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TextDataDetectorConfig")
        }
    }
    static isTextDataDetectorType(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (TextDataDetectorType.PHONE_NUMBER)) {
            return true
        }
        else if ((value) === (TextDataDetectorType.URL)) {
            return true
        }
        else if ((value) === (TextDataDetectorType.EMAIL)) {
            return true
        }
        else if ((value) === (TextDataDetectorType.ADDRESS)) {
            return true
        }
        else if ((value) === (TextDataDetectorType.DATE_TIME)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TextDataDetectorType")
        }
    }
    static isTextDecorationOptions(value: object|string|number|undefined|null|boolean, duplicated_type: boolean, duplicated_color: boolean, duplicated_style: boolean): boolean {
        if ((!duplicated_type) && (value?.hasOwnProperty("type"))) {
            return true
        }
        else if ((!duplicated_color) && (value?.hasOwnProperty("color"))) {
            return true
        }
        else if ((!duplicated_style) && (value?.hasOwnProperty("style"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TextDecorationOptions")
        }
    }
    static isTextDecorationStyle(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (TextDecorationStyle.SOLID)) {
            return true
        }
        else if ((value) === (TextDecorationStyle.DOUBLE)) {
            return true
        }
        else if ((value) === (TextDecorationStyle.DOTTED)) {
            return true
        }
        else if ((value) === (TextDecorationStyle.DASHED)) {
            return true
        }
        else if ((value) === (TextDecorationStyle.WAVY)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TextDecorationStyle")
        }
    }
    static isTextDecorationType(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (TextDecorationType.None)) {
            return true
        }
        else if ((value) === (TextDecorationType.Underline)) {
            return true
        }
        else if ((value) === (TextDecorationType.Overline)) {
            return true
        }
        else if ((value) === (TextDecorationType.LineThrough)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TextDecorationType")
        }
    }
    static isTextDeleteDirection(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (TextDeleteDirection.BACKWARD)) {
            return true
        }
        else if ((value) === (TextDeleteDirection.FORWARD)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TextDeleteDirection")
        }
    }
    static isTextEditControllerEx(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof TextEditControllerEx")
    }
    static isTextHeightAdaptivePolicy(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (TextHeightAdaptivePolicy.MAX_LINES_FIRST)) {
            return true
        }
        else if ((value) === (TextHeightAdaptivePolicy.MIN_FONT_SIZE_FIRST)) {
            return true
        }
        else if ((value) === (TextHeightAdaptivePolicy.LAYOUT_CONSTRAINT_FIRST)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TextHeightAdaptivePolicy")
        }
    }
    static isTextInputAttribute(value: object|string|number|undefined|null|boolean, duplicated_type: boolean, duplicated_contentType: boolean, duplicated_placeholderColor: boolean, duplicated_textOverflow: boolean, duplicated_textIndent: boolean, duplicated_placeholderFont: boolean, duplicated_enterKeyType: boolean, duplicated_caretColor: boolean, duplicated_onEditChanged: boolean, duplicated_onEditChange: boolean, duplicated_onSubmit: boolean, duplicated_onChange: boolean, duplicated_onTextSelectionChange: boolean, duplicated_onContentScroll: boolean, duplicated_maxLength: boolean, duplicated_fontColor: boolean, duplicated_fontSize: boolean, duplicated_fontStyle: boolean, duplicated_fontWeight: boolean, duplicated_fontFamily: boolean, duplicated_onCopy: boolean, duplicated_onCut: boolean, duplicated_onPaste: boolean, duplicated_copyOption: boolean, duplicated_showPasswordIcon: boolean, duplicated_textAlign: boolean, duplicated_style: boolean, duplicated_caretStyle: boolean, duplicated_selectedBackgroundColor: boolean, duplicated_caretPosition: boolean, duplicated_enableKeyboardOnFocus: boolean, duplicated_passwordIcon: boolean, duplicated_showError: boolean, duplicated_showUnit: boolean, duplicated_showUnderline: boolean, duplicated_underlineColor: boolean, duplicated_selectionMenuHidden: boolean, duplicated_barState: boolean, duplicated_maxLines: boolean, duplicated_wordBreak: boolean, duplicated_lineBreakStrategy: boolean, duplicated_cancelButton: boolean, duplicated_selectAll: boolean, duplicated_minFontSize: boolean, duplicated_maxFontSize: boolean, duplicated_heightAdaptivePolicy: boolean, duplicated_enableAutoFill: boolean, duplicated_decoration: boolean, duplicated_letterSpacing: boolean, duplicated_lineHeight: boolean, duplicated_passwordRules: boolean, duplicated_fontFeature: boolean, duplicated_showPassword: boolean, duplicated_onSecurityStateChange: boolean, duplicated_onWillInsert: boolean, duplicated_onDidInsert: boolean, duplicated_onWillDelete: boolean, duplicated_onDidDelete: boolean, duplicated_editMenuOptions: boolean, duplicated_enablePreviewText: boolean, duplicated_enableHapticFeedback: boolean): boolean {
        if ((!duplicated_type) && (value?.hasOwnProperty("type"))) {
            return true
        }
        else if ((!duplicated_contentType) && (value?.hasOwnProperty("contentType"))) {
            return true
        }
        else if ((!duplicated_placeholderColor) && (value?.hasOwnProperty("placeholderColor"))) {
            return true
        }
        else if ((!duplicated_textOverflow) && (value?.hasOwnProperty("textOverflow"))) {
            return true
        }
        else if ((!duplicated_textIndent) && (value?.hasOwnProperty("textIndent"))) {
            return true
        }
        else if ((!duplicated_enterKeyType) && (value?.hasOwnProperty("enterKeyType"))) {
            return true
        }
        else if ((!duplicated_caretColor) && (value?.hasOwnProperty("caretColor"))) {
            return true
        }
        else if ((!duplicated_onEditChanged) && (value?.hasOwnProperty("onEditChanged"))) {
            return true
        }
        else if ((!duplicated_onEditChange) && (value?.hasOwnProperty("onEditChange"))) {
            return true
        }
        else if ((!duplicated_onSubmit) && (value?.hasOwnProperty("onSubmit"))) {
            return true
        }
        else if ((!duplicated_onChange) && (value?.hasOwnProperty("onChange"))) {
            return true
        }
        else if ((!duplicated_onTextSelectionChange) && (value?.hasOwnProperty("onTextSelectionChange"))) {
            return true
        }
        else if ((!duplicated_onContentScroll) && (value?.hasOwnProperty("onContentScroll"))) {
            return true
        }
        else if ((!duplicated_maxLength) && (value?.hasOwnProperty("maxLength"))) {
            return true
        }
        else if ((!duplicated_fontColor) && (value?.hasOwnProperty("fontColor"))) {
            return true
        }
        else if ((!duplicated_fontSize) && (value?.hasOwnProperty("fontSize"))) {
            return true
        }
        else if ((!duplicated_fontStyle) && (value?.hasOwnProperty("fontStyle"))) {
            return true
        }
        else if ((!duplicated_fontWeight) && (value?.hasOwnProperty("fontWeight"))) {
            return true
        }
        else if ((!duplicated_fontFamily) && (value?.hasOwnProperty("fontFamily"))) {
            return true
        }
        else if ((!duplicated_onCopy) && (value?.hasOwnProperty("onCopy"))) {
            return true
        }
        else if ((!duplicated_onCut) && (value?.hasOwnProperty("onCut"))) {
            return true
        }
        else if ((!duplicated_onPaste) && (value?.hasOwnProperty("onPaste"))) {
            return true
        }
        else if ((!duplicated_copyOption) && (value?.hasOwnProperty("copyOption"))) {
            return true
        }
        else if ((!duplicated_showPasswordIcon) && (value?.hasOwnProperty("showPasswordIcon"))) {
            return true
        }
        else if ((!duplicated_textAlign) && (value?.hasOwnProperty("textAlign"))) {
            return true
        }
        else if ((!duplicated_style) && (value?.hasOwnProperty("style"))) {
            return true
        }
        else if ((!duplicated_caretStyle) && (value?.hasOwnProperty("caretStyle"))) {
            return true
        }
        else if ((!duplicated_selectedBackgroundColor) && (value?.hasOwnProperty("selectedBackgroundColor"))) {
            return true
        }
        else if ((!duplicated_caretPosition) && (value?.hasOwnProperty("caretPosition"))) {
            return true
        }
        else if ((!duplicated_enableKeyboardOnFocus) && (value?.hasOwnProperty("enableKeyboardOnFocus"))) {
            return true
        }
        else if ((!duplicated_passwordIcon) && (value?.hasOwnProperty("passwordIcon"))) {
            return true
        }
        else if ((!duplicated_showUnit) && (value?.hasOwnProperty("showUnit"))) {
            return true
        }
        else if ((!duplicated_showUnderline) && (value?.hasOwnProperty("showUnderline"))) {
            return true
        }
        else if ((!duplicated_underlineColor) && (value?.hasOwnProperty("underlineColor"))) {
            return true
        }
        else if ((!duplicated_selectionMenuHidden) && (value?.hasOwnProperty("selectionMenuHidden"))) {
            return true
        }
        else if ((!duplicated_barState) && (value?.hasOwnProperty("barState"))) {
            return true
        }
        else if ((!duplicated_maxLines) && (value?.hasOwnProperty("maxLines"))) {
            return true
        }
        else if ((!duplicated_wordBreak) && (value?.hasOwnProperty("wordBreak"))) {
            return true
        }
        else if ((!duplicated_lineBreakStrategy) && (value?.hasOwnProperty("lineBreakStrategy"))) {
            return true
        }
        else if ((!duplicated_cancelButton) && (value?.hasOwnProperty("cancelButton"))) {
            return true
        }
        else if ((!duplicated_selectAll) && (value?.hasOwnProperty("selectAll"))) {
            return true
        }
        else if ((!duplicated_minFontSize) && (value?.hasOwnProperty("minFontSize"))) {
            return true
        }
        else if ((!duplicated_maxFontSize) && (value?.hasOwnProperty("maxFontSize"))) {
            return true
        }
        else if ((!duplicated_heightAdaptivePolicy) && (value?.hasOwnProperty("heightAdaptivePolicy"))) {
            return true
        }
        else if ((!duplicated_enableAutoFill) && (value?.hasOwnProperty("enableAutoFill"))) {
            return true
        }
        else if ((!duplicated_decoration) && (value?.hasOwnProperty("decoration"))) {
            return true
        }
        else if ((!duplicated_letterSpacing) && (value?.hasOwnProperty("letterSpacing"))) {
            return true
        }
        else if ((!duplicated_lineHeight) && (value?.hasOwnProperty("lineHeight"))) {
            return true
        }
        else if ((!duplicated_passwordRules) && (value?.hasOwnProperty("passwordRules"))) {
            return true
        }
        else if ((!duplicated_fontFeature) && (value?.hasOwnProperty("fontFeature"))) {
            return true
        }
        else if ((!duplicated_showPassword) && (value?.hasOwnProperty("showPassword"))) {
            return true
        }
        else if ((!duplicated_onSecurityStateChange) && (value?.hasOwnProperty("onSecurityStateChange"))) {
            return true
        }
        else if ((!duplicated_onWillInsert) && (value?.hasOwnProperty("onWillInsert"))) {
            return true
        }
        else if ((!duplicated_onDidInsert) && (value?.hasOwnProperty("onDidInsert"))) {
            return true
        }
        else if ((!duplicated_onWillDelete) && (value?.hasOwnProperty("onWillDelete"))) {
            return true
        }
        else if ((!duplicated_onDidDelete) && (value?.hasOwnProperty("onDidDelete"))) {
            return true
        }
        else if ((!duplicated_editMenuOptions) && (value?.hasOwnProperty("editMenuOptions"))) {
            return true
        }
        else if ((!duplicated_enablePreviewText) && (value?.hasOwnProperty("enablePreviewText"))) {
            return true
        }
        else if ((!duplicated_enableHapticFeedback) && (value?.hasOwnProperty("enableHapticFeedback"))) {
            return true
        }
        else if ((!duplicated_placeholderFont) && (value?.hasOwnProperty("placeholderFont"))) {
            return true
        }
        else if ((!duplicated_showError) && (value?.hasOwnProperty("showError"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TextInputAttribute")
        }
    }
    static isTextInputController(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof TextInputController")
    }
    static isTextInputInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof TextInputInterface")
    }
    static isTextInputOptions(value: object|string|number|undefined|null|boolean, duplicated_placeholder: boolean, duplicated_text: boolean, duplicated_controller: boolean): boolean {
        if ((!duplicated_placeholder) && (value?.hasOwnProperty("placeholder"))) {
            return true
        }
        else if ((!duplicated_text) && (value?.hasOwnProperty("text"))) {
            return true
        }
        else if ((!duplicated_controller) && (value?.hasOwnProperty("controller"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TextInputOptions")
        }
    }
    static isTextInputStyle(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (TextInputStyle.Default)) {
            return true
        }
        else if ((value) === (TextInputStyle.Inline)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TextInputStyle")
        }
    }
    static isTextInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof TextInterface")
    }
    static isTextMenuItem(value: object|string|number|undefined|null|boolean, duplicated_content: boolean, duplicated_icon: boolean, duplicated_id: boolean): boolean {
        if ((!duplicated_content) && (value?.hasOwnProperty("content"))) {
            return true
        }
        else if ((!duplicated_id) && (value?.hasOwnProperty("id"))) {
            return true
        }
        else if ((!duplicated_icon) && (value?.hasOwnProperty("icon"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TextMenuItem")
        }
    }
    static isTextMenuItemId(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof TextMenuItemId")
    }
    static isTextMetrics(value: object|string|number|undefined|null|boolean, duplicated_actualBoundingBoxAscent: boolean, duplicated_actualBoundingBoxDescent: boolean, duplicated_actualBoundingBoxLeft: boolean, duplicated_actualBoundingBoxRight: boolean, duplicated_alphabeticBaseline: boolean, duplicated_emHeightAscent: boolean, duplicated_emHeightDescent: boolean, duplicated_fontBoundingBoxAscent: boolean, duplicated_fontBoundingBoxDescent: boolean, duplicated_hangingBaseline: boolean, duplicated_ideographicBaseline: boolean, duplicated_width: boolean, duplicated_height: boolean): boolean {
        if ((!duplicated_actualBoundingBoxAscent) && (value?.hasOwnProperty("actualBoundingBoxAscent"))) {
            return true
        }
        else if ((!duplicated_actualBoundingBoxDescent) && (value?.hasOwnProperty("actualBoundingBoxDescent"))) {
            return true
        }
        else if ((!duplicated_actualBoundingBoxLeft) && (value?.hasOwnProperty("actualBoundingBoxLeft"))) {
            return true
        }
        else if ((!duplicated_actualBoundingBoxRight) && (value?.hasOwnProperty("actualBoundingBoxRight"))) {
            return true
        }
        else if ((!duplicated_alphabeticBaseline) && (value?.hasOwnProperty("alphabeticBaseline"))) {
            return true
        }
        else if ((!duplicated_emHeightAscent) && (value?.hasOwnProperty("emHeightAscent"))) {
            return true
        }
        else if ((!duplicated_emHeightDescent) && (value?.hasOwnProperty("emHeightDescent"))) {
            return true
        }
        else if ((!duplicated_fontBoundingBoxAscent) && (value?.hasOwnProperty("fontBoundingBoxAscent"))) {
            return true
        }
        else if ((!duplicated_fontBoundingBoxDescent) && (value?.hasOwnProperty("fontBoundingBoxDescent"))) {
            return true
        }
        else if ((!duplicated_hangingBaseline) && (value?.hasOwnProperty("hangingBaseline"))) {
            return true
        }
        else if ((!duplicated_ideographicBaseline) && (value?.hasOwnProperty("ideographicBaseline"))) {
            return true
        }
        else if ((!duplicated_width) && (value?.hasOwnProperty("width"))) {
            return true
        }
        else if ((!duplicated_height) && (value?.hasOwnProperty("height"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TextMetrics")
        }
    }
    static isTextModifier(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof TextModifier")
    }
    static isTextOptions(value: object|string|number|undefined|null|boolean, duplicated_controller: boolean): boolean {
        if ((!duplicated_controller) && (value?.hasOwnProperty("controller"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TextOptions")
        }
    }
    static isTextOverflow(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (TextOverflow.None)) {
            return true
        }
        else if ((value) === (TextOverflow.Clip)) {
            return true
        }
        else if ((value) === (TextOverflow.Ellipsis)) {
            return true
        }
        else if ((value) === (TextOverflow.MARQUEE)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TextOverflow")
        }
    }
    static isTextOverflowOptions(value: object|string|number|undefined|null|boolean, duplicated_overflow: boolean): boolean {
        if ((!duplicated_overflow) && (value?.hasOwnProperty("overflow"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TextOverflowOptions")
        }
    }
    static isTextPickerAttribute(value: object|string|number|undefined|null|boolean, duplicated_defaultPickerItemHeight: boolean, duplicated_canLoop: boolean, duplicated_disappearTextStyle: boolean, duplicated_textStyle: boolean, duplicated_selectedTextStyle: boolean, duplicated_onAccept: boolean, duplicated_onCancel: boolean, duplicated_onChange: boolean, duplicated_selectedIndex: boolean, duplicated_divider: boolean, duplicated_gradientHeight: boolean): boolean {
        if ((!duplicated_defaultPickerItemHeight) && (value?.hasOwnProperty("defaultPickerItemHeight"))) {
            return true
        }
        else if ((!duplicated_canLoop) && (value?.hasOwnProperty("canLoop"))) {
            return true
        }
        else if ((!duplicated_disappearTextStyle) && (value?.hasOwnProperty("disappearTextStyle"))) {
            return true
        }
        else if ((!duplicated_textStyle) && (value?.hasOwnProperty("textStyle"))) {
            return true
        }
        else if ((!duplicated_selectedTextStyle) && (value?.hasOwnProperty("selectedTextStyle"))) {
            return true
        }
        else if ((!duplicated_onAccept) && (value?.hasOwnProperty("onAccept"))) {
            return true
        }
        else if ((!duplicated_onCancel) && (value?.hasOwnProperty("onCancel"))) {
            return true
        }
        else if ((!duplicated_onChange) && (value?.hasOwnProperty("onChange"))) {
            return true
        }
        else if ((!duplicated_selectedIndex) && (value?.hasOwnProperty("selectedIndex"))) {
            return true
        }
        else if ((!duplicated_divider) && (value?.hasOwnProperty("divider"))) {
            return true
        }
        else if ((!duplicated_gradientHeight) && (value?.hasOwnProperty("gradientHeight"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TextPickerAttribute")
        }
    }
    static isTextPickerDialog(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof TextPickerDialog")
    }
    static isTextPickerDialogOptions(value: object|string|number|undefined|null|boolean, duplicated_defaultPickerItemHeight: boolean, duplicated_canLoop: boolean, duplicated_disappearTextStyle: boolean, duplicated_textStyle: boolean, duplicated_acceptButtonStyle: boolean, duplicated_cancelButtonStyle: boolean, duplicated_selectedTextStyle: boolean, duplicated_onAccept: boolean, duplicated_onCancel: boolean, duplicated_onChange: boolean, duplicated_maskRect: boolean, duplicated_alignment: boolean, duplicated_offset: boolean, duplicated_backgroundColor: boolean, duplicated_backgroundBlurStyle: boolean, duplicated_onDidAppear: boolean, duplicated_onDidDisappear: boolean, duplicated_onWillAppear: boolean, duplicated_onWillDisappear: boolean, duplicated_shadow: boolean, duplicated_enableHoverMode: boolean, duplicated_hoverModeArea: boolean): boolean {
        if ((!duplicated_defaultPickerItemHeight) && (value?.hasOwnProperty("defaultPickerItemHeight"))) {
            return true
        }
        else if ((!duplicated_canLoop) && (value?.hasOwnProperty("canLoop"))) {
            return true
        }
        else if ((!duplicated_disappearTextStyle) && (value?.hasOwnProperty("disappearTextStyle"))) {
            return true
        }
        else if ((!duplicated_textStyle) && (value?.hasOwnProperty("textStyle"))) {
            return true
        }
        else if ((!duplicated_acceptButtonStyle) && (value?.hasOwnProperty("acceptButtonStyle"))) {
            return true
        }
        else if ((!duplicated_cancelButtonStyle) && (value?.hasOwnProperty("cancelButtonStyle"))) {
            return true
        }
        else if ((!duplicated_selectedTextStyle) && (value?.hasOwnProperty("selectedTextStyle"))) {
            return true
        }
        else if ((!duplicated_onAccept) && (value?.hasOwnProperty("onAccept"))) {
            return true
        }
        else if ((!duplicated_onCancel) && (value?.hasOwnProperty("onCancel"))) {
            return true
        }
        else if ((!duplicated_onChange) && (value?.hasOwnProperty("onChange"))) {
            return true
        }
        else if ((!duplicated_maskRect) && (value?.hasOwnProperty("maskRect"))) {
            return true
        }
        else if ((!duplicated_alignment) && (value?.hasOwnProperty("alignment"))) {
            return true
        }
        else if ((!duplicated_offset) && (value?.hasOwnProperty("offset"))) {
            return true
        }
        else if ((!duplicated_backgroundColor) && (value?.hasOwnProperty("backgroundColor"))) {
            return true
        }
        else if ((!duplicated_backgroundBlurStyle) && (value?.hasOwnProperty("backgroundBlurStyle"))) {
            return true
        }
        else if ((!duplicated_onDidAppear) && (value?.hasOwnProperty("onDidAppear"))) {
            return true
        }
        else if ((!duplicated_onDidDisappear) && (value?.hasOwnProperty("onDidDisappear"))) {
            return true
        }
        else if ((!duplicated_onWillAppear) && (value?.hasOwnProperty("onWillAppear"))) {
            return true
        }
        else if ((!duplicated_onWillDisappear) && (value?.hasOwnProperty("onWillDisappear"))) {
            return true
        }
        else if ((!duplicated_shadow) && (value?.hasOwnProperty("shadow"))) {
            return true
        }
        else if ((!duplicated_enableHoverMode) && (value?.hasOwnProperty("enableHoverMode"))) {
            return true
        }
        else if ((!duplicated_hoverModeArea) && (value?.hasOwnProperty("hoverModeArea"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TextPickerDialogOptions")
        }
    }
    static isTextPickerInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof TextPickerInterface")
    }
    static isTextPickerOptions(value: object|string|number|undefined|null|boolean, duplicated_range: boolean, duplicated_value: boolean, duplicated_selected: boolean): boolean {
        if ((!duplicated_range) && (value?.hasOwnProperty("range"))) {
            return true
        }
        else if ((!duplicated_value) && (value?.hasOwnProperty("value"))) {
            return true
        }
        else if ((!duplicated_selected) && (value?.hasOwnProperty("selected"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TextPickerOptions")
        }
    }
    static isTextPickerRangeContent(value: object|string|number|undefined|null|boolean, duplicated_icon: boolean, duplicated_text: boolean): boolean {
        if ((!duplicated_icon) && (value?.hasOwnProperty("icon"))) {
            return true
        }
        else if ((!duplicated_text) && (value?.hasOwnProperty("text"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TextPickerRangeContent")
        }
    }
    static isTextPickerResult(value: object|string|number|undefined|null|boolean, duplicated_value: boolean, duplicated_index: boolean): boolean {
        if ((!duplicated_value) && (value?.hasOwnProperty("value"))) {
            return true
        }
        else if ((!duplicated_index) && (value?.hasOwnProperty("index"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TextPickerResult")
        }
    }
    static isTextRange(value: object|string|number|undefined|null|boolean, duplicated_start: boolean, duplicated_end: boolean): boolean {
        if ((!duplicated_start) && (value?.hasOwnProperty("start"))) {
            return true
        }
        else if ((!duplicated_end) && (value?.hasOwnProperty("end"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TextRange")
        }
    }
    static isTextResponseType(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (TextResponseType.RIGHT_CLICK)) {
            return true
        }
        else if ((value) === (TextResponseType.LONG_PRESS)) {
            return true
        }
        else if ((value) === (TextResponseType.SELECT)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TextResponseType")
        }
    }
    static isTextSelectableMode(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (TextSelectableMode.SELECTABLE_UNFOCUSABLE)) {
            return true
        }
        else if ((value) === (TextSelectableMode.SELECTABLE_FOCUSABLE)) {
            return true
        }
        else if ((value) === (TextSelectableMode.UNSELECTABLE)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TextSelectableMode")
        }
    }
    static isTextShadowStyle(value: object|string|number|undefined|null|boolean, duplicated_textShadow: boolean): boolean {
        if ((!duplicated_textShadow) && (value?.hasOwnProperty("textShadow"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TextShadowStyle")
        }
    }
    static isTextSpanType(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (TextSpanType.TEXT)) {
            return true
        }
        else if ((value) === (TextSpanType.IMAGE)) {
            return true
        }
        else if ((value) === (TextSpanType.MIXED)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TextSpanType")
        }
    }
    static isTextStyle_alert_dialog(value: object|string|number|undefined|null|boolean, duplicated_wordBreak: boolean): boolean {
        if ((!duplicated_wordBreak) && (value?.hasOwnProperty("wordBreak"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TextStyle_alert_dialog")
        }
    }
    static isTextStyle_styled_string(value: object|string|number|undefined|null|boolean, duplicated_fontColor: boolean, duplicated_fontFamily: boolean, duplicated_fontSize: boolean, duplicated_fontWeight: boolean, duplicated_fontStyle: boolean): boolean {
        if ((!duplicated_fontColor) && (value?.hasOwnProperty("fontColor"))) {
            return true
        }
        else if ((!duplicated_fontFamily) && (value?.hasOwnProperty("fontFamily"))) {
            return true
        }
        else if ((!duplicated_fontSize) && (value?.hasOwnProperty("fontSize"))) {
            return true
        }
        else if ((!duplicated_fontWeight) && (value?.hasOwnProperty("fontWeight"))) {
            return true
        }
        else if ((!duplicated_fontStyle) && (value?.hasOwnProperty("fontStyle"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TextStyle_styled_string")
        }
    }
    static isTextStyleInterface(value: object|string|number|undefined|null|boolean, duplicated_fontColor: boolean, duplicated_fontFamily: boolean, duplicated_fontSize: boolean, duplicated_fontWeight: boolean, duplicated_fontStyle: boolean): boolean {
        if ((!duplicated_fontColor) && (value?.hasOwnProperty("fontColor"))) {
            return true
        }
        else if ((!duplicated_fontFamily) && (value?.hasOwnProperty("fontFamily"))) {
            return true
        }
        else if ((!duplicated_fontSize) && (value?.hasOwnProperty("fontSize"))) {
            return true
        }
        else if ((!duplicated_fontWeight) && (value?.hasOwnProperty("fontWeight"))) {
            return true
        }
        else if ((!duplicated_fontStyle) && (value?.hasOwnProperty("fontStyle"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TextStyleInterface")
        }
    }
    static isTextTimerAttribute(value: object|string|number|undefined|null|boolean, duplicated_format: boolean, duplicated_fontColor: boolean, duplicated_fontSize: boolean, duplicated_fontStyle: boolean, duplicated_fontWeight: boolean, duplicated_fontFamily: boolean, duplicated_onTimer: boolean, duplicated_textShadow: boolean, duplicated_contentModifier: boolean): boolean {
        if ((!duplicated_format) && (value?.hasOwnProperty("format"))) {
            return true
        }
        else if ((!duplicated_fontColor) && (value?.hasOwnProperty("fontColor"))) {
            return true
        }
        else if ((!duplicated_fontSize) && (value?.hasOwnProperty("fontSize"))) {
            return true
        }
        else if ((!duplicated_fontStyle) && (value?.hasOwnProperty("fontStyle"))) {
            return true
        }
        else if ((!duplicated_fontWeight) && (value?.hasOwnProperty("fontWeight"))) {
            return true
        }
        else if ((!duplicated_fontFamily) && (value?.hasOwnProperty("fontFamily"))) {
            return true
        }
        else if ((!duplicated_onTimer) && (value?.hasOwnProperty("onTimer"))) {
            return true
        }
        else if ((!duplicated_textShadow) && (value?.hasOwnProperty("textShadow"))) {
            return true
        }
        else if ((!duplicated_contentModifier) && (value?.hasOwnProperty("contentModifier"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TextTimerAttribute")
        }
    }
    static isTextTimerConfiguration(value: object|string|number|undefined|null|boolean, duplicated_count: boolean, duplicated_isCountDown: boolean, duplicated_started: boolean, duplicated_elapsedTime: boolean): boolean {
        if ((!duplicated_count) && (value?.hasOwnProperty("count"))) {
            return true
        }
        else if ((!duplicated_isCountDown) && (value?.hasOwnProperty("isCountDown"))) {
            return true
        }
        else if ((!duplicated_started) && (value?.hasOwnProperty("started"))) {
            return true
        }
        else if ((!duplicated_elapsedTime) && (value?.hasOwnProperty("elapsedTime"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TextTimerConfiguration")
        }
    }
    static isTextTimerController(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof TextTimerController")
    }
    static isTextTimerInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof TextTimerInterface")
    }
    static isTextTimerOptions(value: object|string|number|undefined|null|boolean, duplicated_isCountDown: boolean, duplicated_count: boolean, duplicated_controller: boolean): boolean {
        if ((!duplicated_isCountDown) && (value?.hasOwnProperty("isCountDown"))) {
            return true
        }
        else if ((!duplicated_count) && (value?.hasOwnProperty("count"))) {
            return true
        }
        else if ((!duplicated_controller) && (value?.hasOwnProperty("controller"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TextTimerOptions")
        }
    }
    static isTheme(value: object|string|number|undefined|null|boolean, duplicated__ThemeStub: boolean): boolean {
        if ((!duplicated__ThemeStub) && (value?.hasOwnProperty("_ThemeStub"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof Theme")
        }
    }
    static isThemeColorMode(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (ThemeColorMode.SYSTEM)) {
            return true
        }
        else if ((value) === (ThemeColorMode.LIGHT)) {
            return true
        }
        else if ((value) === (ThemeColorMode.DARK)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ThemeColorMode")
        }
    }
    static isThreatType(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (ThreatType.THREAT_ILLEGAL)) {
            return true
        }
        else if ((value) === (ThreatType.THREAT_FRAUD)) {
            return true
        }
        else if ((value) === (ThreatType.THREAT_RISK)) {
            return true
        }
        else if ((value) === (ThreatType.THREAT_WARNING)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ThreatType")
        }
    }
    static isTimePickerAttribute(value: object|string|number|undefined|null|boolean, duplicated_useMilitaryTime: boolean, duplicated_loop: boolean, duplicated_disappearTextStyle: boolean, duplicated_textStyle: boolean, duplicated_selectedTextStyle: boolean, duplicated_dateTimeOptions: boolean, duplicated_onChange: boolean, duplicated_enableHapticFeedback: boolean): boolean {
        if ((!duplicated_useMilitaryTime) && (value?.hasOwnProperty("useMilitaryTime"))) {
            return true
        }
        else if ((!duplicated_loop) && (value?.hasOwnProperty("loop"))) {
            return true
        }
        else if ((!duplicated_disappearTextStyle) && (value?.hasOwnProperty("disappearTextStyle"))) {
            return true
        }
        else if ((!duplicated_textStyle) && (value?.hasOwnProperty("textStyle"))) {
            return true
        }
        else if ((!duplicated_selectedTextStyle) && (value?.hasOwnProperty("selectedTextStyle"))) {
            return true
        }
        else if ((!duplicated_dateTimeOptions) && (value?.hasOwnProperty("dateTimeOptions"))) {
            return true
        }
        else if ((!duplicated_onChange) && (value?.hasOwnProperty("onChange"))) {
            return true
        }
        else if ((!duplicated_enableHapticFeedback) && (value?.hasOwnProperty("enableHapticFeedback"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TimePickerAttribute")
        }
    }
    static isTimePickerDialog(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof TimePickerDialog")
    }
    static isTimePickerDialogOptions(value: object|string|number|undefined|null|boolean, duplicated_useMilitaryTime: boolean, duplicated_disappearTextStyle: boolean, duplicated_textStyle: boolean, duplicated_acceptButtonStyle: boolean, duplicated_cancelButtonStyle: boolean, duplicated_selectedTextStyle: boolean, duplicated_maskRect: boolean, duplicated_alignment: boolean, duplicated_offset: boolean, duplicated_onAccept: boolean, duplicated_onCancel: boolean, duplicated_onChange: boolean, duplicated_backgroundColor: boolean, duplicated_backgroundBlurStyle: boolean, duplicated_onDidAppear: boolean, duplicated_onDidDisappear: boolean, duplicated_onWillAppear: boolean, duplicated_onWillDisappear: boolean, duplicated_shadow: boolean, duplicated_dateTimeOptions: boolean, duplicated_enableHoverMode: boolean, duplicated_hoverModeArea: boolean): boolean {
        if ((!duplicated_useMilitaryTime) && (value?.hasOwnProperty("useMilitaryTime"))) {
            return true
        }
        else if ((!duplicated_disappearTextStyle) && (value?.hasOwnProperty("disappearTextStyle"))) {
            return true
        }
        else if ((!duplicated_textStyle) && (value?.hasOwnProperty("textStyle"))) {
            return true
        }
        else if ((!duplicated_acceptButtonStyle) && (value?.hasOwnProperty("acceptButtonStyle"))) {
            return true
        }
        else if ((!duplicated_cancelButtonStyle) && (value?.hasOwnProperty("cancelButtonStyle"))) {
            return true
        }
        else if ((!duplicated_selectedTextStyle) && (value?.hasOwnProperty("selectedTextStyle"))) {
            return true
        }
        else if ((!duplicated_maskRect) && (value?.hasOwnProperty("maskRect"))) {
            return true
        }
        else if ((!duplicated_alignment) && (value?.hasOwnProperty("alignment"))) {
            return true
        }
        else if ((!duplicated_offset) && (value?.hasOwnProperty("offset"))) {
            return true
        }
        else if ((!duplicated_onAccept) && (value?.hasOwnProperty("onAccept"))) {
            return true
        }
        else if ((!duplicated_onCancel) && (value?.hasOwnProperty("onCancel"))) {
            return true
        }
        else if ((!duplicated_onChange) && (value?.hasOwnProperty("onChange"))) {
            return true
        }
        else if ((!duplicated_backgroundColor) && (value?.hasOwnProperty("backgroundColor"))) {
            return true
        }
        else if ((!duplicated_backgroundBlurStyle) && (value?.hasOwnProperty("backgroundBlurStyle"))) {
            return true
        }
        else if ((!duplicated_onDidAppear) && (value?.hasOwnProperty("onDidAppear"))) {
            return true
        }
        else if ((!duplicated_onDidDisappear) && (value?.hasOwnProperty("onDidDisappear"))) {
            return true
        }
        else if ((!duplicated_onWillAppear) && (value?.hasOwnProperty("onWillAppear"))) {
            return true
        }
        else if ((!duplicated_onWillDisappear) && (value?.hasOwnProperty("onWillDisappear"))) {
            return true
        }
        else if ((!duplicated_shadow) && (value?.hasOwnProperty("shadow"))) {
            return true
        }
        else if ((!duplicated_dateTimeOptions) && (value?.hasOwnProperty("dateTimeOptions"))) {
            return true
        }
        else if ((!duplicated_enableHoverMode) && (value?.hasOwnProperty("enableHoverMode"))) {
            return true
        }
        else if ((!duplicated_hoverModeArea) && (value?.hasOwnProperty("hoverModeArea"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TimePickerDialogOptions")
        }
    }
    static isTimePickerFormat(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (TimePickerFormat.HOUR_MINUTE)) {
            return true
        }
        else if ((value) === (TimePickerFormat.HOUR_MINUTE_SECOND)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TimePickerFormat")
        }
    }
    static isTimePickerInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof TimePickerInterface")
    }
    static isTimePickerOptions(value: object|string|number|undefined|null|boolean, duplicated_selected: boolean, duplicated_format: boolean): boolean {
        if ((!duplicated_selected) && (value?.hasOwnProperty("selected"))) {
            return true
        }
        else if ((!duplicated_format) && (value?.hasOwnProperty("format"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TimePickerOptions")
        }
    }
    static isTimePickerResult(value: object|string|number|undefined|null|boolean, duplicated_hour: boolean, duplicated_minute: boolean, duplicated_second: boolean): boolean {
        if ((!duplicated_hour) && (value?.hasOwnProperty("hour"))) {
            return true
        }
        else if ((!duplicated_minute) && (value?.hasOwnProperty("minute"))) {
            return true
        }
        else if ((!duplicated_second) && (value?.hasOwnProperty("second"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TimePickerResult")
        }
    }
    static isTitleHeight(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (TitleHeight.MainOnly)) {
            return true
        }
        else if ((value) === (TitleHeight.MainWithSub)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TitleHeight")
        }
    }
    static isTodayStyle(value: object|string|number|undefined|null|boolean, duplicated_focusedDayColor: boolean, duplicated_focusedLunarColor: boolean, duplicated_focusedAreaBackgroundColor: boolean, duplicated_focusedAreaRadius: boolean): boolean {
        if ((!duplicated_focusedDayColor) && (value?.hasOwnProperty("focusedDayColor"))) {
            return true
        }
        else if ((!duplicated_focusedLunarColor) && (value?.hasOwnProperty("focusedLunarColor"))) {
            return true
        }
        else if ((!duplicated_focusedAreaBackgroundColor) && (value?.hasOwnProperty("focusedAreaBackgroundColor"))) {
            return true
        }
        else if ((!duplicated_focusedAreaRadius) && (value?.hasOwnProperty("focusedAreaRadius"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TodayStyle")
        }
    }
    static isToggleAttribute(value: object|string|number|undefined|null|boolean, duplicated_onChange: boolean, duplicated_contentModifier: boolean, duplicated_selectedColor: boolean, duplicated_switchPointColor: boolean, duplicated_switchStyle: boolean): boolean {
        if ((!duplicated_onChange) && (value?.hasOwnProperty("onChange"))) {
            return true
        }
        else if ((!duplicated_contentModifier) && (value?.hasOwnProperty("contentModifier"))) {
            return true
        }
        else if ((!duplicated_selectedColor) && (value?.hasOwnProperty("selectedColor"))) {
            return true
        }
        else if ((!duplicated_switchPointColor) && (value?.hasOwnProperty("switchPointColor"))) {
            return true
        }
        else if ((!duplicated_switchStyle) && (value?.hasOwnProperty("switchStyle"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ToggleAttribute")
        }
    }
    static isToggleConfiguration(value: object|string|number|undefined|null|boolean, duplicated_isOn: boolean, duplicated_enabled: boolean, duplicated_triggerChange: boolean): boolean {
        if ((!duplicated_isOn) && (value?.hasOwnProperty("isOn"))) {
            return true
        }
        else if ((!duplicated_enabled) && (value?.hasOwnProperty("enabled"))) {
            return true
        }
        else if ((!duplicated_triggerChange) && (value?.hasOwnProperty("triggerChange"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ToggleConfiguration")
        }
    }
    static isToggleInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof ToggleInterface")
    }
    static isToggleOptions(value: object|string|number|undefined|null|boolean, duplicated_type: boolean, duplicated_isOn: boolean): boolean {
        if ((!duplicated_type) && (value?.hasOwnProperty("type"))) {
            return true
        }
        else if ((!duplicated_isOn) && (value?.hasOwnProperty("isOn"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ToggleOptions")
        }
    }
    static isToggleType(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (ToggleType.Checkbox)) {
            return true
        }
        else if ((value) === (ToggleType.Switch)) {
            return true
        }
        else if ((value) === (ToggleType.Button)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ToggleType")
        }
    }
    static isToolbarItem(value: object|string|number|undefined|null|boolean, duplicated_value: boolean, duplicated_icon: boolean, duplicated_symbolIcon: boolean, duplicated_action: boolean, duplicated_status: boolean, duplicated_activeIcon: boolean, duplicated_activeSymbolIcon: boolean): boolean {
        if ((!duplicated_value) && (value?.hasOwnProperty("value"))) {
            return true
        }
        else if ((!duplicated_icon) && (value?.hasOwnProperty("icon"))) {
            return true
        }
        else if ((!duplicated_symbolIcon) && (value?.hasOwnProperty("symbolIcon"))) {
            return true
        }
        else if ((!duplicated_action) && (value?.hasOwnProperty("action"))) {
            return true
        }
        else if ((!duplicated_status) && (value?.hasOwnProperty("status"))) {
            return true
        }
        else if ((!duplicated_activeIcon) && (value?.hasOwnProperty("activeIcon"))) {
            return true
        }
        else if ((!duplicated_activeSymbolIcon) && (value?.hasOwnProperty("activeSymbolIcon"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ToolbarItem")
        }
    }
    static isToolbarItemStatus(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (ToolbarItemStatus.NORMAL)) {
            return true
        }
        else if ((value) === (ToolbarItemStatus.DISABLED)) {
            return true
        }
        else if ((value) === (ToolbarItemStatus.ACTIVE)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ToolbarItemStatus")
        }
    }
    static isTouchEvent(value: object|string|number|undefined|null|boolean, duplicated_type: boolean, duplicated_touches: boolean, duplicated_changedTouches: boolean, duplicated_stopPropagation: boolean, duplicated_preventDefault: boolean): boolean {
        if ((!duplicated_type) && (value?.hasOwnProperty("type"))) {
            return true
        }
        else if ((!duplicated_touches) && (value?.hasOwnProperty("touches"))) {
            return true
        }
        else if ((!duplicated_changedTouches) && (value?.hasOwnProperty("changedTouches"))) {
            return true
        }
        else if ((!duplicated_stopPropagation) && (value?.hasOwnProperty("stopPropagation"))) {
            return true
        }
        else if ((!duplicated_preventDefault) && (value?.hasOwnProperty("preventDefault"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TouchEvent")
        }
    }
    static isTouchObject(value: object|string|number|undefined|null|boolean, duplicated_type: boolean, duplicated_id: boolean, duplicated_displayX: boolean, duplicated_displayY: boolean, duplicated_windowX: boolean, duplicated_windowY: boolean, duplicated_screenX: boolean, duplicated_screenY: boolean, duplicated_x: boolean, duplicated_y: boolean): boolean {
        if ((!duplicated_type) && (value?.hasOwnProperty("type"))) {
            return true
        }
        else if ((!duplicated_id) && (value?.hasOwnProperty("id"))) {
            return true
        }
        else if ((!duplicated_displayX) && (value?.hasOwnProperty("displayX"))) {
            return true
        }
        else if ((!duplicated_displayY) && (value?.hasOwnProperty("displayY"))) {
            return true
        }
        else if ((!duplicated_windowX) && (value?.hasOwnProperty("windowX"))) {
            return true
        }
        else if ((!duplicated_windowY) && (value?.hasOwnProperty("windowY"))) {
            return true
        }
        else if ((!duplicated_screenX) && (value?.hasOwnProperty("screenX"))) {
            return true
        }
        else if ((!duplicated_screenY) && (value?.hasOwnProperty("screenY"))) {
            return true
        }
        else if ((!duplicated_x) && (value?.hasOwnProperty("x"))) {
            return true
        }
        else if ((!duplicated_y) && (value?.hasOwnProperty("y"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TouchObject")
        }
    }
    static isTouchPoint(value: object|string|number|undefined|null|boolean, duplicated_x: boolean, duplicated_y: boolean): boolean {
        if ((!duplicated_x) && (value?.hasOwnProperty("x"))) {
            return true
        }
        else if ((!duplicated_y) && (value?.hasOwnProperty("y"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TouchPoint")
        }
    }
    static isTouchResult(value: object|string|number|undefined|null|boolean, duplicated_strategy: boolean, duplicated_id: boolean): boolean {
        if ((!duplicated_strategy) && (value?.hasOwnProperty("strategy"))) {
            return true
        }
        else if ((!duplicated_id) && (value?.hasOwnProperty("id"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TouchResult")
        }
    }
    static isTouchTestInfo(value: object|string|number|undefined|null|boolean, duplicated_windowX: boolean, duplicated_windowY: boolean, duplicated_parentX: boolean, duplicated_parentY: boolean, duplicated_x: boolean, duplicated_y: boolean, duplicated_rect: boolean, duplicated_id: boolean): boolean {
        if ((!duplicated_windowX) && (value?.hasOwnProperty("windowX"))) {
            return true
        }
        else if ((!duplicated_windowY) && (value?.hasOwnProperty("windowY"))) {
            return true
        }
        else if ((!duplicated_parentX) && (value?.hasOwnProperty("parentX"))) {
            return true
        }
        else if ((!duplicated_parentY) && (value?.hasOwnProperty("parentY"))) {
            return true
        }
        else if ((!duplicated_x) && (value?.hasOwnProperty("x"))) {
            return true
        }
        else if ((!duplicated_y) && (value?.hasOwnProperty("y"))) {
            return true
        }
        else if ((!duplicated_rect) && (value?.hasOwnProperty("rect"))) {
            return true
        }
        else if ((!duplicated_id) && (value?.hasOwnProperty("id"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TouchTestInfo")
        }
    }
    static isTouchTestStrategy(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (TouchTestStrategy.DEFAULT)) {
            return true
        }
        else if ((value) === (TouchTestStrategy.FORWARD_COMPETITION)) {
            return true
        }
        else if ((value) === (TouchTestStrategy.FORWARD)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TouchTestStrategy")
        }
    }
    static isTouchType(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (TouchType.Down)) {
            return true
        }
        else if ((value) === (TouchType.Up)) {
            return true
        }
        else if ((value) === (TouchType.Move)) {
            return true
        }
        else if ((value) === (TouchType.Cancel)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TouchType")
        }
    }
    static isTransitionEdge(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (TransitionEdge.TOP)) {
            return true
        }
        else if ((value) === (TransitionEdge.BOTTOM)) {
            return true
        }
        else if ((value) === (TransitionEdge.START)) {
            return true
        }
        else if ((value) === (TransitionEdge.END)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TransitionEdge")
        }
    }
    static isTransitionEffect(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof TransitionEffect")
    }
    static isTransitionEffects(value: object|string|number|undefined|null|boolean, duplicated_identity: boolean, duplicated_opacity: boolean, duplicated_slideSwitch: boolean, duplicated_move: boolean, duplicated_translate: boolean, duplicated_rotate: boolean, duplicated_scale: boolean, duplicated_asymmetric: boolean): boolean {
        if ((!duplicated_identity) && (value?.hasOwnProperty("identity"))) {
            return true
        }
        else if ((!duplicated_opacity) && (value?.hasOwnProperty("opacity"))) {
            return true
        }
        else if ((!duplicated_slideSwitch) && (value?.hasOwnProperty("slideSwitch"))) {
            return true
        }
        else if ((!duplicated_move) && (value?.hasOwnProperty("move"))) {
            return true
        }
        else if ((!duplicated_translate) && (value?.hasOwnProperty("translate"))) {
            return true
        }
        else if ((!duplicated_rotate) && (value?.hasOwnProperty("rotate"))) {
            return true
        }
        else if ((!duplicated_scale) && (value?.hasOwnProperty("scale"))) {
            return true
        }
        else if ((!duplicated_asymmetric) && (value?.hasOwnProperty("asymmetric"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TransitionEffects")
        }
    }
    static isTransitionHierarchyStrategy(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (TransitionHierarchyStrategy.NONE)) {
            return true
        }
        else if ((value) === (TransitionHierarchyStrategy.ADAPTIVE)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TransitionHierarchyStrategy")
        }
    }
    static isTransitionOptions(value: object|string|number|undefined|null|boolean, duplicated_type: boolean, duplicated_opacity: boolean, duplicated_translate: boolean, duplicated_scale: boolean, duplicated_rotate: boolean): boolean {
        if ((!duplicated_type) && (value?.hasOwnProperty("type"))) {
            return true
        }
        else if ((!duplicated_opacity) && (value?.hasOwnProperty("opacity"))) {
            return true
        }
        else if ((!duplicated_translate) && (value?.hasOwnProperty("translate"))) {
            return true
        }
        else if ((!duplicated_scale) && (value?.hasOwnProperty("scale"))) {
            return true
        }
        else if ((!duplicated_rotate) && (value?.hasOwnProperty("rotate"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TransitionOptions")
        }
    }
    static isTransitionType(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (TransitionType.All)) {
            return true
        }
        else if ((value) === (TransitionType.Insert)) {
            return true
        }
        else if ((value) === (TransitionType.Delete)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TransitionType")
        }
    }
    static isTranslateOptions(value: object|string|number|undefined|null|boolean, duplicated_x: boolean, duplicated_y: boolean, duplicated_z: boolean): boolean {
        if ((!duplicated_x) && (value?.hasOwnProperty("x"))) {
            return true
        }
        else if ((!duplicated_y) && (value?.hasOwnProperty("y"))) {
            return true
        }
        else if ((!duplicated_z) && (value?.hasOwnProperty("z"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TranslateOptions")
        }
    }
    static isType_CalendarInterface_value(value: object|string|number|undefined|null|boolean, duplicated_date: boolean, duplicated_currentData: boolean, duplicated_preData: boolean, duplicated_nextData: boolean, duplicated_controller: boolean): boolean {
        if ((!duplicated_date) && (value?.hasOwnProperty("date"))) {
            return true
        }
        else if ((!duplicated_currentData) && (value?.hasOwnProperty("currentData"))) {
            return true
        }
        else if ((!duplicated_preData) && (value?.hasOwnProperty("preData"))) {
            return true
        }
        else if ((!duplicated_nextData) && (value?.hasOwnProperty("nextData"))) {
            return true
        }
        else if ((!duplicated_controller) && (value?.hasOwnProperty("controller"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof Type_CalendarInterface_value")
        }
    }
    static isType_CommonMethod_linearGradient_value(value: object|string|number|undefined|null|boolean, duplicated_angle: boolean, duplicated_direction: boolean, duplicated_colors: boolean, duplicated_repeating: boolean): boolean {
        if ((!duplicated_colors) && (value?.hasOwnProperty("colors"))) {
            return true
        }
        else if ((!duplicated_angle) && (value?.hasOwnProperty("angle"))) {
            return true
        }
        else if ((!duplicated_direction) && (value?.hasOwnProperty("direction"))) {
            return true
        }
        else if ((!duplicated_repeating) && (value?.hasOwnProperty("repeating"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof Type_CommonMethod_linearGradient_value")
        }
    }
    static isType_CommonMethod_radialGradient_value(value: object|string|number|undefined|null|boolean, duplicated_center: boolean, duplicated_radius: boolean, duplicated_colors: boolean, duplicated_repeating: boolean): boolean {
        if ((!duplicated_center) && (value?.hasOwnProperty("center"))) {
            return true
        }
        else if ((!duplicated_radius) && (value?.hasOwnProperty("radius"))) {
            return true
        }
        else if ((!duplicated_colors) && (value?.hasOwnProperty("colors"))) {
            return true
        }
        else if ((!duplicated_repeating) && (value?.hasOwnProperty("repeating"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof Type_CommonMethod_radialGradient_value")
        }
    }
    static isType_CommonMethod_sweepGradient_value(value: object|string|number|undefined|null|boolean, duplicated_center: boolean, duplicated_start: boolean, duplicated_end: boolean, duplicated_rotation: boolean, duplicated_colors: boolean, duplicated_repeating: boolean): boolean {
        if ((!duplicated_center) && (value?.hasOwnProperty("center"))) {
            return true
        }
        else if ((!duplicated_colors) && (value?.hasOwnProperty("colors"))) {
            return true
        }
        else if ((!duplicated_start) && (value?.hasOwnProperty("start"))) {
            return true
        }
        else if ((!duplicated_end) && (value?.hasOwnProperty("end"))) {
            return true
        }
        else if ((!duplicated_rotation) && (value?.hasOwnProperty("rotation"))) {
            return true
        }
        else if ((!duplicated_repeating) && (value?.hasOwnProperty("repeating"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof Type_CommonMethod_sweepGradient_value")
        }
    }
    static isType_ImageAttribute_onComplete_callback_event(value: object|string|number|undefined|null|boolean, duplicated_width: boolean, duplicated_height: boolean, duplicated_componentWidth: boolean, duplicated_componentHeight: boolean, duplicated_loadingStatus: boolean, duplicated_contentWidth: boolean, duplicated_contentHeight: boolean, duplicated_contentOffsetX: boolean, duplicated_contentOffsetY: boolean): boolean {
        if ((!duplicated_width) && (value?.hasOwnProperty("width"))) {
            return true
        }
        else if ((!duplicated_height) && (value?.hasOwnProperty("height"))) {
            return true
        }
        else if ((!duplicated_componentWidth) && (value?.hasOwnProperty("componentWidth"))) {
            return true
        }
        else if ((!duplicated_componentHeight) && (value?.hasOwnProperty("componentHeight"))) {
            return true
        }
        else if ((!duplicated_loadingStatus) && (value?.hasOwnProperty("loadingStatus"))) {
            return true
        }
        else if ((!duplicated_contentWidth) && (value?.hasOwnProperty("contentWidth"))) {
            return true
        }
        else if ((!duplicated_contentHeight) && (value?.hasOwnProperty("contentHeight"))) {
            return true
        }
        else if ((!duplicated_contentOffsetX) && (value?.hasOwnProperty("contentOffsetX"))) {
            return true
        }
        else if ((!duplicated_contentOffsetY) && (value?.hasOwnProperty("contentOffsetY"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof Type_ImageAttribute_onComplete_callback_event")
        }
    }
    static isType_XComponentInterface_value(value: object|string|number|undefined|null|boolean, duplicated_id: boolean, duplicated_type: boolean, duplicated_libraryname: boolean, duplicated_controller: boolean): boolean {
        if ((!duplicated_id) && (value?.hasOwnProperty("id"))) {
            return true
        }
        else if ((!duplicated_type) && (value?.hasOwnProperty("type"))) {
            return true
        }
        else if ((!duplicated_libraryname) && (value?.hasOwnProperty("libraryname"))) {
            return true
        }
        else if ((!duplicated_controller) && (value?.hasOwnProperty("controller"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof Type_XComponentInterface_value")
        }
    }
    static isUICommonEvent(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof UICommonEvent")
    }
    static isUIContext(value: object|string|number|undefined|null|boolean, duplicated__UIContextStub: boolean): boolean {
        if ((!duplicated__UIContextStub) && (value?.hasOwnProperty("_UIContextStub"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof UIContext")
        }
    }
    static isUIExtensionComponentAttribute(value: object|string|number|undefined|null|boolean, duplicated_onRemoteReady: boolean, duplicated_onReceive: boolean, duplicated_onResult: boolean, duplicated_onRelease: boolean, duplicated_onError: boolean, duplicated_onTerminated: boolean): boolean {
        if ((!duplicated_onRemoteReady) && (value?.hasOwnProperty("onRemoteReady"))) {
            return true
        }
        else if ((!duplicated_onReceive) && (value?.hasOwnProperty("onReceive"))) {
            return true
        }
        else if ((!duplicated_onResult) && (value?.hasOwnProperty("onResult"))) {
            return true
        }
        else if ((!duplicated_onRelease) && (value?.hasOwnProperty("onRelease"))) {
            return true
        }
        else if ((!duplicated_onError) && (value?.hasOwnProperty("onError"))) {
            return true
        }
        else if ((!duplicated_onTerminated) && (value?.hasOwnProperty("onTerminated"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof UIExtensionComponentAttribute")
        }
    }
    static isUIExtensionComponentInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof UIExtensionComponentInterface")
    }
    static isUIExtensionOptions(value: object|string|number|undefined|null|boolean, duplicated_isTransferringCaller: boolean, duplicated_placeholder: boolean, duplicated_areaChangePlaceholder: boolean, duplicated_dpiFollowStrategy: boolean): boolean {
        if ((!duplicated_isTransferringCaller) && (value?.hasOwnProperty("isTransferringCaller"))) {
            return true
        }
        else if ((!duplicated_placeholder) && (value?.hasOwnProperty("placeholder"))) {
            return true
        }
        else if ((!duplicated_areaChangePlaceholder) && (value?.hasOwnProperty("areaChangePlaceholder"))) {
            return true
        }
        else if ((!duplicated_dpiFollowStrategy) && (value?.hasOwnProperty("dpiFollowStrategy"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof UIExtensionOptions")
        }
    }
    static isUIExtensionProxy(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof UIExtensionProxy")
    }
    static isUIGestureEvent(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof UIGestureEvent")
    }
    static isUnderlineColor(value: object|string|number|undefined|null|boolean, duplicated_typing: boolean, duplicated_normal: boolean, duplicated_error: boolean, duplicated_disable: boolean): boolean {
        if ((!duplicated_typing) && (value?.hasOwnProperty("typing"))) {
            return true
        }
        else if ((!duplicated_normal) && (value?.hasOwnProperty("normal"))) {
            return true
        }
        else if ((!duplicated_error) && (value?.hasOwnProperty("error"))) {
            return true
        }
        else if ((!duplicated_disable) && (value?.hasOwnProperty("disable"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof UnderlineColor")
        }
    }
    static isUnifiedData(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof UnifiedData")
    }
    static isUniformDataType(value: object|string|number|undefined|null|boolean, duplicated__UniformDataTypeStub: boolean): boolean {
        if ((!duplicated__UniformDataTypeStub) && (value?.hasOwnProperty("_UniformDataTypeStub"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof UniformDataType")
        }
    }
    static isUrlStyle(value: object|string|number|undefined|null|boolean, duplicated_url: boolean): boolean {
        if ((!duplicated_url) && (value?.hasOwnProperty("url"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof UrlStyle")
        }
    }
    static isUserDataSpan(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof UserDataSpan")
    }
    static isVelocityOptions(value: object|string|number|undefined|null|boolean, duplicated_speed: boolean, duplicated_angle: boolean): boolean {
        if ((!duplicated_speed) && (value?.hasOwnProperty("speed"))) {
            return true
        }
        else if ((!duplicated_angle) && (value?.hasOwnProperty("angle"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof VelocityOptions")
        }
    }
    static isVerticalAlign(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (VerticalAlign.Top)) {
            return true
        }
        else if ((value) === (VerticalAlign.Center)) {
            return true
        }
        else if ((value) === (VerticalAlign.Bottom)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof VerticalAlign")
        }
    }
    static isVideoAttribute(value: object|string|number|undefined|null|boolean, duplicated_muted: boolean, duplicated_autoPlay: boolean, duplicated_controls: boolean, duplicated_loop: boolean, duplicated_objectFit: boolean, duplicated_onStart: boolean, duplicated_onPause: boolean, duplicated_onFinish: boolean, duplicated_onFullscreenChange: boolean, duplicated_onPrepared: boolean, duplicated_onSeeking: boolean, duplicated_onSeeked: boolean, duplicated_onUpdate: boolean, duplicated_onError: boolean, duplicated_onStop: boolean, duplicated_enableAnalyzer: boolean, duplicated_analyzerConfig: boolean): boolean {
        if ((!duplicated_muted) && (value?.hasOwnProperty("muted"))) {
            return true
        }
        else if ((!duplicated_autoPlay) && (value?.hasOwnProperty("autoPlay"))) {
            return true
        }
        else if ((!duplicated_controls) && (value?.hasOwnProperty("controls"))) {
            return true
        }
        else if ((!duplicated_loop) && (value?.hasOwnProperty("loop"))) {
            return true
        }
        else if ((!duplicated_objectFit) && (value?.hasOwnProperty("objectFit"))) {
            return true
        }
        else if ((!duplicated_onStart) && (value?.hasOwnProperty("onStart"))) {
            return true
        }
        else if ((!duplicated_onPause) && (value?.hasOwnProperty("onPause"))) {
            return true
        }
        else if ((!duplicated_onFinish) && (value?.hasOwnProperty("onFinish"))) {
            return true
        }
        else if ((!duplicated_onFullscreenChange) && (value?.hasOwnProperty("onFullscreenChange"))) {
            return true
        }
        else if ((!duplicated_onPrepared) && (value?.hasOwnProperty("onPrepared"))) {
            return true
        }
        else if ((!duplicated_onSeeking) && (value?.hasOwnProperty("onSeeking"))) {
            return true
        }
        else if ((!duplicated_onSeeked) && (value?.hasOwnProperty("onSeeked"))) {
            return true
        }
        else if ((!duplicated_onUpdate) && (value?.hasOwnProperty("onUpdate"))) {
            return true
        }
        else if ((!duplicated_onError) && (value?.hasOwnProperty("onError"))) {
            return true
        }
        else if ((!duplicated_onStop) && (value?.hasOwnProperty("onStop"))) {
            return true
        }
        else if ((!duplicated_enableAnalyzer) && (value?.hasOwnProperty("enableAnalyzer"))) {
            return true
        }
        else if ((!duplicated_analyzerConfig) && (value?.hasOwnProperty("analyzerConfig"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof VideoAttribute")
        }
    }
    static isVideoController(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof VideoController")
    }
    static isVideoInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof VideoInterface")
    }
    static isVideoOptions(value: object|string|number|undefined|null|boolean, duplicated_src: boolean, duplicated_currentProgressRate: boolean, duplicated_previewUri: boolean, duplicated_controller: boolean, duplicated_imageAIOptions: boolean): boolean {
        if ((!duplicated_src) && (value?.hasOwnProperty("src"))) {
            return true
        }
        else if ((!duplicated_currentProgressRate) && (value?.hasOwnProperty("currentProgressRate"))) {
            return true
        }
        else if ((!duplicated_previewUri) && (value?.hasOwnProperty("previewUri"))) {
            return true
        }
        else if ((!duplicated_controller) && (value?.hasOwnProperty("controller"))) {
            return true
        }
        else if ((!duplicated_imageAIOptions) && (value?.hasOwnProperty("imageAIOptions"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof VideoOptions")
        }
    }
    static isView(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof View")
    }
    static isViewportFit(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (ViewportFit.AUTO)) {
            return true
        }
        else if ((value) === (ViewportFit.CONTAINS)) {
            return true
        }
        else if ((value) === (ViewportFit.COVER)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ViewportFit")
        }
    }
    static isViewportRect(value: object|string|number|undefined|null|boolean, duplicated_x: boolean, duplicated_y: boolean, duplicated_width: boolean, duplicated_height: boolean): boolean {
        if ((!duplicated_x) && (value?.hasOwnProperty("x"))) {
            return true
        }
        else if ((!duplicated_y) && (value?.hasOwnProperty("y"))) {
            return true
        }
        else if ((!duplicated_width) && (value?.hasOwnProperty("width"))) {
            return true
        }
        else if ((!duplicated_height) && (value?.hasOwnProperty("height"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ViewportRect")
        }
    }
    static isVirtualScrollOptions(value: object|string|number|undefined|null|boolean, duplicated_totalCount: boolean): boolean {
        if ((!duplicated_totalCount) && (value?.hasOwnProperty("totalCount"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof VirtualScrollOptions")
        }
    }
    static isVisibility(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (Visibility.Visible)) {
            return true
        }
        else if ((value) === (Visibility.Hidden)) {
            return true
        }
        else if ((value) === (Visibility.None)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof Visibility")
        }
    }
    static isVisibleAreaEventOptions(value: object|string|number|undefined|null|boolean, duplicated_ratios: boolean, duplicated_expectedUpdateInterval: boolean): boolean {
        if ((!duplicated_ratios) && (value?.hasOwnProperty("ratios"))) {
            return true
        }
        else if ((!duplicated_expectedUpdateInterval) && (value?.hasOwnProperty("expectedUpdateInterval"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof VisibleAreaEventOptions")
        }
    }
    static isVisibleListContentInfo(value: object|string|number|undefined|null|boolean, duplicated_index: boolean, duplicated_itemGroupArea: boolean, duplicated_itemIndexInGroup: boolean): boolean {
        if ((!duplicated_index) && (value?.hasOwnProperty("index"))) {
            return true
        }
        else if ((!duplicated_itemGroupArea) && (value?.hasOwnProperty("itemGroupArea"))) {
            return true
        }
        else if ((!duplicated_itemIndexInGroup) && (value?.hasOwnProperty("itemIndexInGroup"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof VisibleListContentInfo")
        }
    }
    static isVisualEffect(value: object|string|number|undefined|null|boolean, duplicated__VisualEffectStub: boolean): boolean {
        if ((!duplicated__VisualEffectStub) && (value?.hasOwnProperty("_VisualEffectStub"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof VisualEffect")
        }
    }
    static isWant(value: object|string|number|undefined|null|boolean, duplicated_bundleName: boolean, duplicated_abilityName: boolean, duplicated_deviceId: boolean, duplicated_uri: boolean, duplicated_type: boolean, duplicated_flags: boolean, duplicated_action: boolean, duplicated_parameters: boolean, duplicated_entities: boolean, duplicated_moduleName: boolean): boolean {
        if ((!duplicated_bundleName) && (value?.hasOwnProperty("bundleName"))) {
            return true
        }
        else if ((!duplicated_abilityName) && (value?.hasOwnProperty("abilityName"))) {
            return true
        }
        else if ((!duplicated_deviceId) && (value?.hasOwnProperty("deviceId"))) {
            return true
        }
        else if ((!duplicated_uri) && (value?.hasOwnProperty("uri"))) {
            return true
        }
        else if ((!duplicated_type) && (value?.hasOwnProperty("type"))) {
            return true
        }
        else if ((!duplicated_flags) && (value?.hasOwnProperty("flags"))) {
            return true
        }
        else if ((!duplicated_action) && (value?.hasOwnProperty("action"))) {
            return true
        }
        else if ((!duplicated_parameters) && (value?.hasOwnProperty("parameters"))) {
            return true
        }
        else if ((!duplicated_entities) && (value?.hasOwnProperty("entities"))) {
            return true
        }
        else if ((!duplicated_moduleName) && (value?.hasOwnProperty("moduleName"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof Want")
        }
    }
    static isWaterFlowAttribute(value: object|string|number|undefined|null|boolean, duplicated_columnsTemplate: boolean, duplicated_itemConstraintSize: boolean, duplicated_rowsTemplate: boolean, duplicated_columnsGap: boolean, duplicated_rowsGap: boolean, duplicated_layoutDirection: boolean, duplicated_nestedScroll: boolean, duplicated_enableScrollInteraction: boolean, duplicated_friction: boolean, duplicated_cachedCount: boolean, duplicated_onWillScroll: boolean, duplicated_onDidScroll: boolean, duplicated_onReachStart: boolean, duplicated_onReachEnd: boolean, duplicated_onScrollFrameBegin: boolean, duplicated_onScrollIndex: boolean): boolean {
        if ((!duplicated_columnsTemplate) && (value?.hasOwnProperty("columnsTemplate"))) {
            return true
        }
        else if ((!duplicated_itemConstraintSize) && (value?.hasOwnProperty("itemConstraintSize"))) {
            return true
        }
        else if ((!duplicated_rowsTemplate) && (value?.hasOwnProperty("rowsTemplate"))) {
            return true
        }
        else if ((!duplicated_columnsGap) && (value?.hasOwnProperty("columnsGap"))) {
            return true
        }
        else if ((!duplicated_rowsGap) && (value?.hasOwnProperty("rowsGap"))) {
            return true
        }
        else if ((!duplicated_layoutDirection) && (value?.hasOwnProperty("layoutDirection"))) {
            return true
        }
        else if ((!duplicated_nestedScroll) && (value?.hasOwnProperty("nestedScroll"))) {
            return true
        }
        else if ((!duplicated_enableScrollInteraction) && (value?.hasOwnProperty("enableScrollInteraction"))) {
            return true
        }
        else if ((!duplicated_friction) && (value?.hasOwnProperty("friction"))) {
            return true
        }
        else if ((!duplicated_cachedCount) && (value?.hasOwnProperty("cachedCount"))) {
            return true
        }
        else if ((!duplicated_onWillScroll) && (value?.hasOwnProperty("onWillScroll"))) {
            return true
        }
        else if ((!duplicated_onDidScroll) && (value?.hasOwnProperty("onDidScroll"))) {
            return true
        }
        else if ((!duplicated_onReachStart) && (value?.hasOwnProperty("onReachStart"))) {
            return true
        }
        else if ((!duplicated_onReachEnd) && (value?.hasOwnProperty("onReachEnd"))) {
            return true
        }
        else if ((!duplicated_onScrollFrameBegin) && (value?.hasOwnProperty("onScrollFrameBegin"))) {
            return true
        }
        else if ((!duplicated_onScrollIndex) && (value?.hasOwnProperty("onScrollIndex"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof WaterFlowAttribute")
        }
    }
    static isWaterFlowInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof WaterFlowInterface")
    }
    static isWaterFlowLayoutMode(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (WaterFlowLayoutMode.ALWAYS_TOP_DOWN)) {
            return true
        }
        else if ((value) === (WaterFlowLayoutMode.SLIDING_WINDOW)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof WaterFlowLayoutMode")
        }
    }
    static isWaterFlowOptions(value: object|string|number|undefined|null|boolean, duplicated_footer: boolean, duplicated_scroller: boolean, duplicated_sections: boolean, duplicated_layoutMode: boolean): boolean {
        if ((!duplicated_footer) && (value?.hasOwnProperty("footer"))) {
            return true
        }
        else if ((!duplicated_scroller) && (value?.hasOwnProperty("scroller"))) {
            return true
        }
        else if ((!duplicated_sections) && (value?.hasOwnProperty("sections"))) {
            return true
        }
        else if ((!duplicated_layoutMode) && (value?.hasOwnProperty("layoutMode"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof WaterFlowOptions")
        }
    }
    static isWaterFlowSections(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof WaterFlowSections")
    }
    static isWebAttribute(value: object|string|number|undefined|null|boolean, duplicated_javaScriptAccess: boolean, duplicated_fileAccess: boolean, duplicated_onlineImageAccess: boolean, duplicated_domStorageAccess: boolean, duplicated_imageAccess: boolean, duplicated_mixedMode: boolean, duplicated_zoomAccess: boolean, duplicated_geolocationAccess: boolean, duplicated_javaScriptProxy: boolean, duplicated_password: boolean, duplicated_cacheMode: boolean, duplicated_darkMode: boolean, duplicated_forceDarkAccess: boolean, duplicated_mediaOptions: boolean, duplicated_tableData: boolean, duplicated_wideViewModeAccess: boolean, duplicated_overviewModeAccess: boolean, duplicated_overScrollMode: boolean, duplicated_textZoomAtio: boolean, duplicated_textZoomRatio: boolean, duplicated_databaseAccess: boolean, duplicated_initialScale: boolean, duplicated_userAgent: boolean, duplicated_metaViewport: boolean, duplicated_onPageEnd: boolean, duplicated_onPageBegin: boolean, duplicated_onProgressChange: boolean, duplicated_onTitleReceive: boolean, duplicated_onGeolocationHide: boolean, duplicated_onGeolocationShow: boolean, duplicated_onRequestSelected: boolean, duplicated_onAlert: boolean, duplicated_onBeforeUnload: boolean, duplicated_onConfirm: boolean, duplicated_onPrompt: boolean, duplicated_onConsole: boolean, duplicated_onErrorReceive: boolean, duplicated_onHttpErrorReceive: boolean, duplicated_onDownloadStart: boolean, duplicated_onRefreshAccessedHistory: boolean, duplicated_onUrlLoadIntercept: boolean, duplicated_onSslErrorReceive: boolean, duplicated_onRenderExited: boolean, duplicated_onShowFileSelector: boolean, duplicated_onFileSelectorShow: boolean, duplicated_onResourceLoad: boolean, duplicated_onFullScreenExit: boolean, duplicated_onFullScreenEnter: boolean, duplicated_onScaleChange: boolean, duplicated_onHttpAuthRequest: boolean, duplicated_onInterceptRequest: boolean, duplicated_onPermissionRequest: boolean, duplicated_onScreenCaptureRequest: boolean, duplicated_onContextMenuShow: boolean, duplicated_onContextMenuHide: boolean, duplicated_mediaPlayGestureAccess: boolean, duplicated_onSearchResultReceive: boolean, duplicated_onScroll: boolean, duplicated_onSslErrorEventReceive: boolean, duplicated_onSslErrorEvent: boolean, duplicated_onClientAuthenticationRequest: boolean, duplicated_onWindowNew: boolean, duplicated_onWindowExit: boolean, duplicated_multiWindowAccess: boolean, duplicated_onInterceptKeyEvent: boolean, duplicated_webStandardFont: boolean, duplicated_webSerifFont: boolean, duplicated_webSansSerifFont: boolean, duplicated_webFixedFont: boolean, duplicated_webFantasyFont: boolean, duplicated_webCursiveFont: boolean, duplicated_defaultFixedFontSize: boolean, duplicated_defaultFontSize: boolean, duplicated_minFontSize: boolean, duplicated_minLogicalFontSize: boolean, duplicated_defaultTextEncodingFormat: boolean, duplicated_forceDisplayScrollBar: boolean, duplicated_blockNetwork: boolean, duplicated_horizontalScrollBarAccess: boolean, duplicated_verticalScrollBarAccess: boolean, duplicated_onTouchIconUrlReceived: boolean, duplicated_onFaviconReceived: boolean, duplicated_onPageVisible: boolean, duplicated_onDataResubmitted: boolean, duplicated_pinchSmooth: boolean, duplicated_allowWindowOpenMethod: boolean, duplicated_onAudioStateChanged: boolean, duplicated_onFirstContentfulPaint: boolean, duplicated_onFirstMeaningfulPaint: boolean, duplicated_onLargestContentfulPaint: boolean, duplicated_onLoadIntercept: boolean, duplicated_onControllerAttached: boolean, duplicated_onOverScroll: boolean, duplicated_onSafeBrowsingCheckResult: boolean, duplicated_onNavigationEntryCommitted: boolean, duplicated_onIntelligentTrackingPreventionResult: boolean, duplicated_javaScriptOnDocumentStart: boolean, duplicated_javaScriptOnDocumentEnd: boolean, duplicated_layoutMode: boolean, duplicated_nestedScroll: boolean, duplicated_enableNativeEmbedMode: boolean, duplicated_onNativeEmbedLifecycleChange: boolean, duplicated_onNativeEmbedVisibilityChange: boolean, duplicated_onNativeEmbedGestureEvent: boolean, duplicated_copyOptions: boolean, duplicated_onOverrideUrlLoading: boolean, duplicated_textAutosizing: boolean, duplicated_enableNativeMediaPlayer: boolean, duplicated_enableSmoothDragResize: boolean, duplicated_onRenderProcessNotResponding: boolean, duplicated_onRenderProcessResponding: boolean, duplicated_selectionMenuOptions: boolean, duplicated_onViewportFitChanged: boolean, duplicated_onInterceptKeyboardAttach: boolean, duplicated_onAdsBlocked: boolean, duplicated_keyboardAvoidMode: boolean, duplicated_editMenuOptions: boolean, duplicated_enableHapticFeedback: boolean): boolean {
        if ((!duplicated_javaScriptAccess) && (value?.hasOwnProperty("javaScriptAccess"))) {
            return true
        }
        else if ((!duplicated_fileAccess) && (value?.hasOwnProperty("fileAccess"))) {
            return true
        }
        else if ((!duplicated_onlineImageAccess) && (value?.hasOwnProperty("onlineImageAccess"))) {
            return true
        }
        else if ((!duplicated_domStorageAccess) && (value?.hasOwnProperty("domStorageAccess"))) {
            return true
        }
        else if ((!duplicated_imageAccess) && (value?.hasOwnProperty("imageAccess"))) {
            return true
        }
        else if ((!duplicated_mixedMode) && (value?.hasOwnProperty("mixedMode"))) {
            return true
        }
        else if ((!duplicated_zoomAccess) && (value?.hasOwnProperty("zoomAccess"))) {
            return true
        }
        else if ((!duplicated_geolocationAccess) && (value?.hasOwnProperty("geolocationAccess"))) {
            return true
        }
        else if ((!duplicated_javaScriptProxy) && (value?.hasOwnProperty("javaScriptProxy"))) {
            return true
        }
        else if ((!duplicated_password) && (value?.hasOwnProperty("password"))) {
            return true
        }
        else if ((!duplicated_cacheMode) && (value?.hasOwnProperty("cacheMode"))) {
            return true
        }
        else if ((!duplicated_darkMode) && (value?.hasOwnProperty("darkMode"))) {
            return true
        }
        else if ((!duplicated_forceDarkAccess) && (value?.hasOwnProperty("forceDarkAccess"))) {
            return true
        }
        else if ((!duplicated_mediaOptions) && (value?.hasOwnProperty("mediaOptions"))) {
            return true
        }
        else if ((!duplicated_tableData) && (value?.hasOwnProperty("tableData"))) {
            return true
        }
        else if ((!duplicated_wideViewModeAccess) && (value?.hasOwnProperty("wideViewModeAccess"))) {
            return true
        }
        else if ((!duplicated_overviewModeAccess) && (value?.hasOwnProperty("overviewModeAccess"))) {
            return true
        }
        else if ((!duplicated_overScrollMode) && (value?.hasOwnProperty("overScrollMode"))) {
            return true
        }
        else if ((!duplicated_textZoomAtio) && (value?.hasOwnProperty("textZoomAtio"))) {
            return true
        }
        else if ((!duplicated_textZoomRatio) && (value?.hasOwnProperty("textZoomRatio"))) {
            return true
        }
        else if ((!duplicated_databaseAccess) && (value?.hasOwnProperty("databaseAccess"))) {
            return true
        }
        else if ((!duplicated_initialScale) && (value?.hasOwnProperty("initialScale"))) {
            return true
        }
        else if ((!duplicated_userAgent) && (value?.hasOwnProperty("userAgent"))) {
            return true
        }
        else if ((!duplicated_metaViewport) && (value?.hasOwnProperty("metaViewport"))) {
            return true
        }
        else if ((!duplicated_onPageEnd) && (value?.hasOwnProperty("onPageEnd"))) {
            return true
        }
        else if ((!duplicated_onPageBegin) && (value?.hasOwnProperty("onPageBegin"))) {
            return true
        }
        else if ((!duplicated_onProgressChange) && (value?.hasOwnProperty("onProgressChange"))) {
            return true
        }
        else if ((!duplicated_onTitleReceive) && (value?.hasOwnProperty("onTitleReceive"))) {
            return true
        }
        else if ((!duplicated_onGeolocationHide) && (value?.hasOwnProperty("onGeolocationHide"))) {
            return true
        }
        else if ((!duplicated_onGeolocationShow) && (value?.hasOwnProperty("onGeolocationShow"))) {
            return true
        }
        else if ((!duplicated_onRequestSelected) && (value?.hasOwnProperty("onRequestSelected"))) {
            return true
        }
        else if ((!duplicated_onAlert) && (value?.hasOwnProperty("onAlert"))) {
            return true
        }
        else if ((!duplicated_onBeforeUnload) && (value?.hasOwnProperty("onBeforeUnload"))) {
            return true
        }
        else if ((!duplicated_onConfirm) && (value?.hasOwnProperty("onConfirm"))) {
            return true
        }
        else if ((!duplicated_onPrompt) && (value?.hasOwnProperty("onPrompt"))) {
            return true
        }
        else if ((!duplicated_onConsole) && (value?.hasOwnProperty("onConsole"))) {
            return true
        }
        else if ((!duplicated_onErrorReceive) && (value?.hasOwnProperty("onErrorReceive"))) {
            return true
        }
        else if ((!duplicated_onHttpErrorReceive) && (value?.hasOwnProperty("onHttpErrorReceive"))) {
            return true
        }
        else if ((!duplicated_onDownloadStart) && (value?.hasOwnProperty("onDownloadStart"))) {
            return true
        }
        else if ((!duplicated_onRefreshAccessedHistory) && (value?.hasOwnProperty("onRefreshAccessedHistory"))) {
            return true
        }
        else if ((!duplicated_onUrlLoadIntercept) && (value?.hasOwnProperty("onUrlLoadIntercept"))) {
            return true
        }
        else if ((!duplicated_onSslErrorReceive) && (value?.hasOwnProperty("onSslErrorReceive"))) {
            return true
        }
        else if ((!duplicated_onRenderExited) && (value?.hasOwnProperty("onRenderExited"))) {
            return true
        }
        else if ((!duplicated_onShowFileSelector) && (value?.hasOwnProperty("onShowFileSelector"))) {
            return true
        }
        else if ((!duplicated_onFileSelectorShow) && (value?.hasOwnProperty("onFileSelectorShow"))) {
            return true
        }
        else if ((!duplicated_onResourceLoad) && (value?.hasOwnProperty("onResourceLoad"))) {
            return true
        }
        else if ((!duplicated_onFullScreenExit) && (value?.hasOwnProperty("onFullScreenExit"))) {
            return true
        }
        else if ((!duplicated_onFullScreenEnter) && (value?.hasOwnProperty("onFullScreenEnter"))) {
            return true
        }
        else if ((!duplicated_onScaleChange) && (value?.hasOwnProperty("onScaleChange"))) {
            return true
        }
        else if ((!duplicated_onHttpAuthRequest) && (value?.hasOwnProperty("onHttpAuthRequest"))) {
            return true
        }
        else if ((!duplicated_onInterceptRequest) && (value?.hasOwnProperty("onInterceptRequest"))) {
            return true
        }
        else if ((!duplicated_onPermissionRequest) && (value?.hasOwnProperty("onPermissionRequest"))) {
            return true
        }
        else if ((!duplicated_onScreenCaptureRequest) && (value?.hasOwnProperty("onScreenCaptureRequest"))) {
            return true
        }
        else if ((!duplicated_onContextMenuShow) && (value?.hasOwnProperty("onContextMenuShow"))) {
            return true
        }
        else if ((!duplicated_onContextMenuHide) && (value?.hasOwnProperty("onContextMenuHide"))) {
            return true
        }
        else if ((!duplicated_mediaPlayGestureAccess) && (value?.hasOwnProperty("mediaPlayGestureAccess"))) {
            return true
        }
        else if ((!duplicated_onSearchResultReceive) && (value?.hasOwnProperty("onSearchResultReceive"))) {
            return true
        }
        else if ((!duplicated_onScroll) && (value?.hasOwnProperty("onScroll"))) {
            return true
        }
        else if ((!duplicated_onSslErrorEventReceive) && (value?.hasOwnProperty("onSslErrorEventReceive"))) {
            return true
        }
        else if ((!duplicated_onSslErrorEvent) && (value?.hasOwnProperty("onSslErrorEvent"))) {
            return true
        }
        else if ((!duplicated_onClientAuthenticationRequest) && (value?.hasOwnProperty("onClientAuthenticationRequest"))) {
            return true
        }
        else if ((!duplicated_onWindowNew) && (value?.hasOwnProperty("onWindowNew"))) {
            return true
        }
        else if ((!duplicated_onWindowExit) && (value?.hasOwnProperty("onWindowExit"))) {
            return true
        }
        else if ((!duplicated_multiWindowAccess) && (value?.hasOwnProperty("multiWindowAccess"))) {
            return true
        }
        else if ((!duplicated_onInterceptKeyEvent) && (value?.hasOwnProperty("onInterceptKeyEvent"))) {
            return true
        }
        else if ((!duplicated_webStandardFont) && (value?.hasOwnProperty("webStandardFont"))) {
            return true
        }
        else if ((!duplicated_webSerifFont) && (value?.hasOwnProperty("webSerifFont"))) {
            return true
        }
        else if ((!duplicated_webSansSerifFont) && (value?.hasOwnProperty("webSansSerifFont"))) {
            return true
        }
        else if ((!duplicated_webFixedFont) && (value?.hasOwnProperty("webFixedFont"))) {
            return true
        }
        else if ((!duplicated_webFantasyFont) && (value?.hasOwnProperty("webFantasyFont"))) {
            return true
        }
        else if ((!duplicated_webCursiveFont) && (value?.hasOwnProperty("webCursiveFont"))) {
            return true
        }
        else if ((!duplicated_defaultFixedFontSize) && (value?.hasOwnProperty("defaultFixedFontSize"))) {
            return true
        }
        else if ((!duplicated_defaultFontSize) && (value?.hasOwnProperty("defaultFontSize"))) {
            return true
        }
        else if ((!duplicated_minFontSize) && (value?.hasOwnProperty("minFontSize"))) {
            return true
        }
        else if ((!duplicated_minLogicalFontSize) && (value?.hasOwnProperty("minLogicalFontSize"))) {
            return true
        }
        else if ((!duplicated_defaultTextEncodingFormat) && (value?.hasOwnProperty("defaultTextEncodingFormat"))) {
            return true
        }
        else if ((!duplicated_forceDisplayScrollBar) && (value?.hasOwnProperty("forceDisplayScrollBar"))) {
            return true
        }
        else if ((!duplicated_blockNetwork) && (value?.hasOwnProperty("blockNetwork"))) {
            return true
        }
        else if ((!duplicated_horizontalScrollBarAccess) && (value?.hasOwnProperty("horizontalScrollBarAccess"))) {
            return true
        }
        else if ((!duplicated_verticalScrollBarAccess) && (value?.hasOwnProperty("verticalScrollBarAccess"))) {
            return true
        }
        else if ((!duplicated_onTouchIconUrlReceived) && (value?.hasOwnProperty("onTouchIconUrlReceived"))) {
            return true
        }
        else if ((!duplicated_onFaviconReceived) && (value?.hasOwnProperty("onFaviconReceived"))) {
            return true
        }
        else if ((!duplicated_onPageVisible) && (value?.hasOwnProperty("onPageVisible"))) {
            return true
        }
        else if ((!duplicated_onDataResubmitted) && (value?.hasOwnProperty("onDataResubmitted"))) {
            return true
        }
        else if ((!duplicated_pinchSmooth) && (value?.hasOwnProperty("pinchSmooth"))) {
            return true
        }
        else if ((!duplicated_allowWindowOpenMethod) && (value?.hasOwnProperty("allowWindowOpenMethod"))) {
            return true
        }
        else if ((!duplicated_onAudioStateChanged) && (value?.hasOwnProperty("onAudioStateChanged"))) {
            return true
        }
        else if ((!duplicated_onFirstContentfulPaint) && (value?.hasOwnProperty("onFirstContentfulPaint"))) {
            return true
        }
        else if ((!duplicated_onFirstMeaningfulPaint) && (value?.hasOwnProperty("onFirstMeaningfulPaint"))) {
            return true
        }
        else if ((!duplicated_onLargestContentfulPaint) && (value?.hasOwnProperty("onLargestContentfulPaint"))) {
            return true
        }
        else if ((!duplicated_onLoadIntercept) && (value?.hasOwnProperty("onLoadIntercept"))) {
            return true
        }
        else if ((!duplicated_onControllerAttached) && (value?.hasOwnProperty("onControllerAttached"))) {
            return true
        }
        else if ((!duplicated_onOverScroll) && (value?.hasOwnProperty("onOverScroll"))) {
            return true
        }
        else if ((!duplicated_onSafeBrowsingCheckResult) && (value?.hasOwnProperty("onSafeBrowsingCheckResult"))) {
            return true
        }
        else if ((!duplicated_onNavigationEntryCommitted) && (value?.hasOwnProperty("onNavigationEntryCommitted"))) {
            return true
        }
        else if ((!duplicated_onIntelligentTrackingPreventionResult) && (value?.hasOwnProperty("onIntelligentTrackingPreventionResult"))) {
            return true
        }
        else if ((!duplicated_javaScriptOnDocumentStart) && (value?.hasOwnProperty("javaScriptOnDocumentStart"))) {
            return true
        }
        else if ((!duplicated_javaScriptOnDocumentEnd) && (value?.hasOwnProperty("javaScriptOnDocumentEnd"))) {
            return true
        }
        else if ((!duplicated_layoutMode) && (value?.hasOwnProperty("layoutMode"))) {
            return true
        }
        else if ((!duplicated_nestedScroll) && (value?.hasOwnProperty("nestedScroll"))) {
            return true
        }
        else if ((!duplicated_enableNativeEmbedMode) && (value?.hasOwnProperty("enableNativeEmbedMode"))) {
            return true
        }
        else if ((!duplicated_onNativeEmbedLifecycleChange) && (value?.hasOwnProperty("onNativeEmbedLifecycleChange"))) {
            return true
        }
        else if ((!duplicated_onNativeEmbedVisibilityChange) && (value?.hasOwnProperty("onNativeEmbedVisibilityChange"))) {
            return true
        }
        else if ((!duplicated_onNativeEmbedGestureEvent) && (value?.hasOwnProperty("onNativeEmbedGestureEvent"))) {
            return true
        }
        else if ((!duplicated_copyOptions) && (value?.hasOwnProperty("copyOptions"))) {
            return true
        }
        else if ((!duplicated_onOverrideUrlLoading) && (value?.hasOwnProperty("onOverrideUrlLoading"))) {
            return true
        }
        else if ((!duplicated_textAutosizing) && (value?.hasOwnProperty("textAutosizing"))) {
            return true
        }
        else if ((!duplicated_enableNativeMediaPlayer) && (value?.hasOwnProperty("enableNativeMediaPlayer"))) {
            return true
        }
        else if ((!duplicated_enableSmoothDragResize) && (value?.hasOwnProperty("enableSmoothDragResize"))) {
            return true
        }
        else if ((!duplicated_onRenderProcessNotResponding) && (value?.hasOwnProperty("onRenderProcessNotResponding"))) {
            return true
        }
        else if ((!duplicated_onRenderProcessResponding) && (value?.hasOwnProperty("onRenderProcessResponding"))) {
            return true
        }
        else if ((!duplicated_selectionMenuOptions) && (value?.hasOwnProperty("selectionMenuOptions"))) {
            return true
        }
        else if ((!duplicated_onViewportFitChanged) && (value?.hasOwnProperty("onViewportFitChanged"))) {
            return true
        }
        else if ((!duplicated_onInterceptKeyboardAttach) && (value?.hasOwnProperty("onInterceptKeyboardAttach"))) {
            return true
        }
        else if ((!duplicated_onAdsBlocked) && (value?.hasOwnProperty("onAdsBlocked"))) {
            return true
        }
        else if ((!duplicated_keyboardAvoidMode) && (value?.hasOwnProperty("keyboardAvoidMode"))) {
            return true
        }
        else if ((!duplicated_editMenuOptions) && (value?.hasOwnProperty("editMenuOptions"))) {
            return true
        }
        else if ((!duplicated_enableHapticFeedback) && (value?.hasOwnProperty("enableHapticFeedback"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof WebAttribute")
        }
    }
    static isWebCaptureMode(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (WebCaptureMode.HOME_SCREEN)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof WebCaptureMode")
        }
    }
    static isWebContextMenuParam(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof WebContextMenuParam")
    }
    static isWebContextMenuResult(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof WebContextMenuResult")
    }
    static isWebController(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof WebController")
    }
    static isWebCookie(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof WebCookie")
    }
    static isWebDarkMode(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (WebDarkMode.Off)) {
            return true
        }
        else if ((value) === (WebDarkMode.On)) {
            return true
        }
        else if ((value) === (WebDarkMode.Auto)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof WebDarkMode")
        }
    }
    static isWebElementType(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (WebElementType.IMAGE)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof WebElementType")
        }
    }
    static isWebHeader(value: object|string|number|undefined|null|boolean, duplicated_headerKey: boolean, duplicated_headerValue: boolean): boolean {
        if ((!duplicated_headerKey) && (value?.hasOwnProperty("headerKey"))) {
            return true
        }
        else if ((!duplicated_headerValue) && (value?.hasOwnProperty("headerValue"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof WebHeader")
        }
    }
    static isWebInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof WebInterface")
    }
    static isWebKeyboardAvoidMode(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (WebKeyboardAvoidMode.RESIZE_VISUAL)) {
            return true
        }
        else if ((value) === (WebKeyboardAvoidMode.RESIZE_CONTENT)) {
            return true
        }
        else if ((value) === (WebKeyboardAvoidMode.OVERLAYS_CONTENT)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof WebKeyboardAvoidMode")
        }
    }
    static isWebKeyboardCallbackInfo(value: object|string|number|undefined|null|boolean, duplicated_controller: boolean, duplicated_attributes: boolean): boolean {
        if ((!duplicated_controller) && (value?.hasOwnProperty("controller"))) {
            return true
        }
        else if ((!duplicated_attributes) && (value?.hasOwnProperty("attributes"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof WebKeyboardCallbackInfo")
        }
    }
    static isWebKeyboardController(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof WebKeyboardController")
    }
    static isWebKeyboardOptions(value: object|string|number|undefined|null|boolean, duplicated_useSystemKeyboard: boolean, duplicated_enterKeyType: boolean, duplicated_customKeyboard: boolean): boolean {
        if ((!duplicated_useSystemKeyboard) && (value?.hasOwnProperty("useSystemKeyboard"))) {
            return true
        }
        else if ((!duplicated_enterKeyType) && (value?.hasOwnProperty("enterKeyType"))) {
            return true
        }
        else if ((!duplicated_customKeyboard) && (value?.hasOwnProperty("customKeyboard"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof WebKeyboardOptions")
        }
    }
    static isWebLayoutMode(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (WebLayoutMode.NONE)) {
            return true
        }
        else if ((value) === (WebLayoutMode.FIT_CONTENT)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof WebLayoutMode")
        }
    }
    static isWebMediaOptions(value: object|string|number|undefined|null|boolean, duplicated_resumeInterval: boolean, duplicated_audioExclusive: boolean): boolean {
        if ((!duplicated_resumeInterval) && (value?.hasOwnProperty("resumeInterval"))) {
            return true
        }
        else if ((!duplicated_audioExclusive) && (value?.hasOwnProperty("audioExclusive"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof WebMediaOptions")
        }
    }
    static isWebNavigationType(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (WebNavigationType.UNKNOWN)) {
            return true
        }
        else if ((value) === (WebNavigationType.MAIN_FRAME_NEW_ENTRY)) {
            return true
        }
        else if ((value) === (WebNavigationType.MAIN_FRAME_EXISTING_ENTRY)) {
            return true
        }
        else if ((value) === (WebNavigationType.NAVIGATION_TYPE_NEW_SUBFRAME)) {
            return true
        }
        else if ((value) === (WebNavigationType.NAVIGATION_TYPE_AUTO_SUBFRAME)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof WebNavigationType")
        }
    }
    static isWebOptions(value: object|string|number|undefined|null|boolean, duplicated_src: boolean, duplicated_controller: boolean, duplicated_renderMode: boolean, duplicated_incognitoMode: boolean, duplicated_sharedRenderProcessToken: boolean): boolean {
        if ((!duplicated_src) && (value?.hasOwnProperty("src"))) {
            return true
        }
        else if ((!duplicated_controller) && (value?.hasOwnProperty("controller"))) {
            return true
        }
        else if ((!duplicated_renderMode) && (value?.hasOwnProperty("renderMode"))) {
            return true
        }
        else if ((!duplicated_incognitoMode) && (value?.hasOwnProperty("incognitoMode"))) {
            return true
        }
        else if ((!duplicated_sharedRenderProcessToken) && (value?.hasOwnProperty("sharedRenderProcessToken"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof WebOptions")
        }
    }
    static isWebResourceError(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof WebResourceError")
    }
    static isWebResourceRequest(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof WebResourceRequest")
    }
    static isWebResourceResponse(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof WebResourceResponse")
    }
    static isWebResponseType(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (WebResponseType.LONG_PRESS)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof WebResponseType")
        }
    }
    static isWebviewController(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof WebviewController")
    }
    static isWeek(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (Week.Mon)) {
            return true
        }
        else if ((value) === (Week.Tue)) {
            return true
        }
        else if ((value) === (Week.Wed)) {
            return true
        }
        else if ((value) === (Week.Thur)) {
            return true
        }
        else if ((value) === (Week.Fri)) {
            return true
        }
        else if ((value) === (Week.Sat)) {
            return true
        }
        else if ((value) === (Week.Sun)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof Week")
        }
    }
    static isWeekStyle(value: object|string|number|undefined|null|boolean, duplicated_weekColor: boolean, duplicated_weekendDayColor: boolean, duplicated_weekendLunarColor: boolean, duplicated_weekFontSize: boolean, duplicated_weekHeight: boolean, duplicated_weekWidth: boolean, duplicated_weekAndDayRowSpace: boolean): boolean {
        if ((!duplicated_weekColor) && (value?.hasOwnProperty("weekColor"))) {
            return true
        }
        else if ((!duplicated_weekendDayColor) && (value?.hasOwnProperty("weekendDayColor"))) {
            return true
        }
        else if ((!duplicated_weekendLunarColor) && (value?.hasOwnProperty("weekendLunarColor"))) {
            return true
        }
        else if ((!duplicated_weekFontSize) && (value?.hasOwnProperty("weekFontSize"))) {
            return true
        }
        else if ((!duplicated_weekHeight) && (value?.hasOwnProperty("weekHeight"))) {
            return true
        }
        else if ((!duplicated_weekWidth) && (value?.hasOwnProperty("weekWidth"))) {
            return true
        }
        else if ((!duplicated_weekAndDayRowSpace) && (value?.hasOwnProperty("weekAndDayRowSpace"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof WeekStyle")
        }
    }
    static isWidthBreakpoint(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (WidthBreakpoint.WIDTH_XS)) {
            return true
        }
        else if ((value) === (WidthBreakpoint.WIDTH_SM)) {
            return true
        }
        else if ((value) === (WidthBreakpoint.WIDTH_MD)) {
            return true
        }
        else if ((value) === (WidthBreakpoint.WIDTH_LG)) {
            return true
        }
        else if ((value) === (WidthBreakpoint.WIDTH_XL)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof WidthBreakpoint")
        }
    }
    static isWindowAnimationTarget(value: object|string|number|undefined|null|boolean, duplicated_bundleName: boolean, duplicated_abilityName: boolean, duplicated_windowBounds: boolean, duplicated_missionId: boolean): boolean {
        if ((!duplicated_bundleName) && (value?.hasOwnProperty("bundleName"))) {
            return true
        }
        else if ((!duplicated_abilityName) && (value?.hasOwnProperty("abilityName"))) {
            return true
        }
        else if ((!duplicated_windowBounds) && (value?.hasOwnProperty("windowBounds"))) {
            return true
        }
        else if ((!duplicated_missionId) && (value?.hasOwnProperty("missionId"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof WindowAnimationTarget")
        }
    }
    static isWindowSceneAttribute(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof WindowSceneAttribute")
    }
    static isWindowSceneInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof WindowSceneInterface")
    }
    static isWindowStatusType(value: object|string|number|undefined|null|boolean, duplicated__WindowStatusTypeStub: boolean): boolean {
        if ((!duplicated__WindowStatusTypeStub) && (value?.hasOwnProperty("_WindowStatusTypeStub"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof WindowStatusType")
        }
    }
    static isWithThemeAttribute(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof WithThemeAttribute")
    }
    static isWithThemeOptions(value: object|string|number|undefined|null|boolean, duplicated_theme: boolean, duplicated_colorMode: boolean): boolean {
        if ((!duplicated_theme) && (value?.hasOwnProperty("theme"))) {
            return true
        }
        else if ((!duplicated_colorMode) && (value?.hasOwnProperty("colorMode"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof WithThemeOptions")
        }
    }
    static isWordBreak(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (WordBreak.NORMAL)) {
            return true
        }
        else if ((value) === (WordBreak.BREAK_ALL)) {
            return true
        }
        else if ((value) === (WordBreak.BREAK_WORD)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof WordBreak")
        }
    }
    static isWorkStateStyle(value: object|string|number|undefined|null|boolean, duplicated_workDayMarkColor: boolean, duplicated_offDayMarkColor: boolean, duplicated_workDayMarkSize: boolean, duplicated_offDayMarkSize: boolean, duplicated_workStateWidth: boolean, duplicated_workStateHorizontalMovingDistance: boolean, duplicated_workStateVerticalMovingDistance: boolean): boolean {
        if ((!duplicated_workDayMarkColor) && (value?.hasOwnProperty("workDayMarkColor"))) {
            return true
        }
        else if ((!duplicated_offDayMarkColor) && (value?.hasOwnProperty("offDayMarkColor"))) {
            return true
        }
        else if ((!duplicated_workDayMarkSize) && (value?.hasOwnProperty("workDayMarkSize"))) {
            return true
        }
        else if ((!duplicated_offDayMarkSize) && (value?.hasOwnProperty("offDayMarkSize"))) {
            return true
        }
        else if ((!duplicated_workStateWidth) && (value?.hasOwnProperty("workStateWidth"))) {
            return true
        }
        else if ((!duplicated_workStateHorizontalMovingDistance) && (value?.hasOwnProperty("workStateHorizontalMovingDistance"))) {
            return true
        }
        else if ((!duplicated_workStateVerticalMovingDistance) && (value?.hasOwnProperty("workStateVerticalMovingDistance"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof WorkStateStyle")
        }
    }
    static isXComponentAttribute(value: object|string|number|undefined|null|boolean, duplicated_onLoad: boolean, duplicated_onDestroy: boolean, duplicated_enableAnalyzer: boolean, duplicated_enableSecure: boolean): boolean {
        if ((!duplicated_onLoad) && (value?.hasOwnProperty("onLoad"))) {
            return true
        }
        else if ((!duplicated_onDestroy) && (value?.hasOwnProperty("onDestroy"))) {
            return true
        }
        else if ((!duplicated_enableAnalyzer) && (value?.hasOwnProperty("enableAnalyzer"))) {
            return true
        }
        else if ((!duplicated_enableSecure) && (value?.hasOwnProperty("enableSecure"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof XComponentAttribute")
        }
    }
    static isXComponentController(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof XComponentController")
    }
    static isXComponentInterface(value: object|string|number|undefined|null|boolean): boolean {
        throw new Error("Can not discriminate value typeof XComponentInterface")
    }
    static isXComponentOptions(value: object|string|number|undefined|null|boolean, duplicated_type: boolean, duplicated_controller: boolean, duplicated_imageAIOptions: boolean): boolean {
        if ((!duplicated_type) && (value?.hasOwnProperty("type"))) {
            return true
        }
        else if ((!duplicated_controller) && (value?.hasOwnProperty("controller"))) {
            return true
        }
        else if ((!duplicated_imageAIOptions) && (value?.hasOwnProperty("imageAIOptions"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof XComponentOptions")
        }
    }
    static isXComponentType(value: object|string|number|undefined|null|boolean): boolean {
        if ((value) === (XComponentType.SURFACE)) {
            return true
        }
        else if ((value) === (XComponentType.COMPONENT)) {
            return true
        }
        else if ((value) === (XComponentType.TEXTURE)) {
            return true
        }
        else if ((value) === (XComponentType.NODE)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof XComponentType")
        }
    }
    static PointerStyle_ToOrdinal(value: PointerStyle): int32 {
        return value as int32
    }
    static PointerStyle_FromOrdinal(ordinal: int32): PointerStyle {
        return ordinal as PointerStyle
    }
    static RectWidthStyle_ToOrdinal(value: RectWidthStyle): int32 {
        return value as int32
    }
    static RectWidthStyle_FromOrdinal(ordinal: int32): RectWidthStyle {
        return ordinal as RectWidthStyle
    }
    static Affinity_ToOrdinal(value: Affinity): int32 {
        return value as int32
    }
    static Affinity_FromOrdinal(ordinal: int32): Affinity {
        return ordinal as Affinity
    }
    static RectHeightStyle_ToOrdinal(value: RectHeightStyle): int32 {
        return value as int32
    }
    static RectHeightStyle_FromOrdinal(ordinal: int32): RectHeightStyle {
        return ordinal as RectHeightStyle
    }
    static LengthUnit_ToOrdinal(value: LengthUnit): int32 {
        return value as int32
    }
    static LengthUnit_FromOrdinal(ordinal: int32): LengthUnit {
        return ordinal as LengthUnit
    }
    static PerfMonitorActionType_ToOrdinal(value: PerfMonitorActionType): int32 {
        return value as int32
    }
    static PerfMonitorActionType_FromOrdinal(ordinal: int32): PerfMonitorActionType {
        return ordinal as PerfMonitorActionType
    }
    static PerfMonitorSourceType_ToOrdinal(value: PerfMonitorSourceType): int32 {
        return value as int32
    }
    static PerfMonitorSourceType_FromOrdinal(ordinal: int32): PerfMonitorSourceType {
        return ordinal as PerfMonitorSourceType
    }
    static EffectDirection_ToOrdinal(value: EffectDirection): int32 {
        return value as int32
    }
    static EffectDirection_FromOrdinal(ordinal: int32): EffectDirection {
        return ordinal as EffectDirection
    }
    static EffectScope_ToOrdinal(value: EffectScope): int32 {
        return value as int32
    }
    static EffectScope_FromOrdinal(ordinal: int32): EffectScope {
        return ordinal as EffectScope
    }
    static DialogAlignment_ToOrdinal(value: DialogAlignment): int32 {
        return value as int32
    }
    static DialogAlignment_FromOrdinal(ordinal: int32): DialogAlignment {
        return ordinal as DialogAlignment
    }
    static DialogButtonDirection_ToOrdinal(value: DialogButtonDirection): int32 {
        return value as int32
    }
    static DialogButtonDirection_FromOrdinal(ordinal: int32): DialogButtonDirection {
        return ordinal as DialogButtonDirection
    }
    static IndexerAlign_ToOrdinal(value: IndexerAlign): int32 {
        return value as int32
    }
    static IndexerAlign_FromOrdinal(ordinal: int32): IndexerAlign {
        return ordinal as IndexerAlign
    }
    static BadgePosition_ToOrdinal(value: BadgePosition): int32 {
        return value as int32
    }
    static BadgePosition_FromOrdinal(ordinal: int32): BadgePosition {
        return ordinal as BadgePosition
    }
    static ButtonType_ToOrdinal(value: ButtonType): int32 {
        return value as int32
    }
    static ButtonType_FromOrdinal(ordinal: int32): ButtonType {
        return ordinal as ButtonType
    }
    static ButtonStyleMode_ToOrdinal(value: ButtonStyleMode): int32 {
        return value as int32
    }
    static ButtonStyleMode_FromOrdinal(ordinal: int32): ButtonStyleMode {
        return ordinal as ButtonStyleMode
    }
    static ButtonRole_ToOrdinal(value: ButtonRole): int32 {
        return value as int32
    }
    static ButtonRole_FromOrdinal(ordinal: int32): ButtonRole {
        return ordinal as ButtonRole
    }
    static ControlSize_ToOrdinal(value: ControlSize): int32 {
        return value as int32
    }
    static ControlSize_FromOrdinal(ordinal: int32): ControlSize {
        return ordinal as ControlSize
    }
    static CalendarAlign_ToOrdinal(value: CalendarAlign): int32 {
        return value as int32
    }
    static CalendarAlign_FromOrdinal(ordinal: int32): CalendarAlign {
        return ordinal as CalendarAlign
    }
    static SelectStatus_ToOrdinal(value: SelectStatus): int32 {
        return value as int32
    }
    static SelectStatus_FromOrdinal(ordinal: int32): SelectStatus {
        return ordinal as SelectStatus
    }
    static FinishCallbackType_ToOrdinal(value: FinishCallbackType): int32 {
        return value as int32
    }
    static FinishCallbackType_FromOrdinal(ordinal: int32): FinishCallbackType {
        return ordinal as FinishCallbackType
    }
    static TouchTestStrategy_ToOrdinal(value: TouchTestStrategy): int32 {
        return value as int32
    }
    static TouchTestStrategy_FromOrdinal(ordinal: int32): TouchTestStrategy {
        return ordinal as TouchTestStrategy
    }
    static TransitionHierarchyStrategy_ToOrdinal(value: TransitionHierarchyStrategy): int32 {
        return value as int32
    }
    static TransitionHierarchyStrategy_FromOrdinal(ordinal: int32): TransitionHierarchyStrategy {
        return ordinal as TransitionHierarchyStrategy
    }
    static ChainStyle_ToOrdinal(value: ChainStyle): int32 {
        return value as int32
    }
    static ChainStyle_FromOrdinal(ordinal: int32): ChainStyle {
        return ordinal as ChainStyle
    }
    static TransitionEdge_ToOrdinal(value: TransitionEdge): int32 {
        return value as int32
    }
    static TransitionEdge_FromOrdinal(ordinal: int32): TransitionEdge {
        return ordinal as TransitionEdge
    }
    static EffectType_ToOrdinal(value: EffectType): int32 {
        return value as int32
    }
    static EffectType_FromOrdinal(ordinal: int32): EffectType {
        return ordinal as EffectType
    }
    static PreDragStatus_ToOrdinal(value: PreDragStatus): int32 {
        return value as int32
    }
    static PreDragStatus_FromOrdinal(ordinal: int32): PreDragStatus {
        return ordinal as PreDragStatus
    }
    static SourceType_ToOrdinal(value: SourceType): int32 {
        return value as int32
    }
    static SourceType_FromOrdinal(ordinal: int32): SourceType {
        return ordinal as SourceType
    }
    static SourceTool_ToOrdinal(value: SourceTool): int32 {
        return value as int32
    }
    static SourceTool_FromOrdinal(ordinal: int32): SourceTool {
        return ordinal as SourceTool
    }
    static RepeatMode_ToOrdinal(value: RepeatMode): int32 {
        return value as int32
    }
    static RepeatMode_FromOrdinal(ordinal: int32): RepeatMode {
        return ordinal as RepeatMode
    }
    static BlurStyle_ToOrdinal(value: BlurStyle): int32 {
        return value as int32
    }
    static BlurStyle_FromOrdinal(ordinal: int32): BlurStyle {
        return ordinal as BlurStyle
    }
    static BlurStyleActivePolicy_ToOrdinal(value: BlurStyleActivePolicy): int32 {
        return value as int32
    }
    static BlurStyleActivePolicy_FromOrdinal(ordinal: int32): BlurStyleActivePolicy {
        return ordinal as BlurStyleActivePolicy
    }
    static ThemeColorMode_ToOrdinal(value: ThemeColorMode): int32 {
        return value as int32
    }
    static ThemeColorMode_FromOrdinal(ordinal: int32): ThemeColorMode {
        return ordinal as ThemeColorMode
    }
    static AdaptiveColor_ToOrdinal(value: AdaptiveColor): int32 {
        return value as int32
    }
    static AdaptiveColor_FromOrdinal(ordinal: int32): AdaptiveColor {
        return ordinal as AdaptiveColor
    }
    static ModalTransition_ToOrdinal(value: ModalTransition): int32 {
        return value as int32
    }
    static ModalTransition_FromOrdinal(ordinal: int32): ModalTransition {
        return ordinal as ModalTransition
    }
    static ShadowType_ToOrdinal(value: ShadowType): int32 {
        return value as int32
    }
    static ShadowType_FromOrdinal(ordinal: int32): ShadowType {
        return ordinal as ShadowType
    }
    static ShadowStyle_ToOrdinal(value: ShadowStyle): int32 {
        return value as int32
    }
    static ShadowStyle_FromOrdinal(ordinal: int32): ShadowStyle {
        return ordinal as ShadowStyle
    }
    static SafeAreaType_ToOrdinal(value: SafeAreaType): int32 {
        return value as int32
    }
    static SafeAreaType_FromOrdinal(ordinal: int32): SafeAreaType {
        return ordinal as SafeAreaType
    }
    static SafeAreaEdge_ToOrdinal(value: SafeAreaEdge): int32 {
        return value as int32
    }
    static SafeAreaEdge_FromOrdinal(ordinal: int32): SafeAreaEdge {
        return ordinal as SafeAreaEdge
    }
    static LayoutSafeAreaType_ToOrdinal(value: LayoutSafeAreaType): int32 {
        return value as int32
    }
    static LayoutSafeAreaType_FromOrdinal(ordinal: int32): LayoutSafeAreaType {
        return ordinal as LayoutSafeAreaType
    }
    static LayoutSafeAreaEdge_ToOrdinal(value: LayoutSafeAreaEdge): int32 {
        return value as int32
    }
    static LayoutSafeAreaEdge_FromOrdinal(ordinal: int32): LayoutSafeAreaEdge {
        return ordinal as LayoutSafeAreaEdge
    }
    static SheetSize_ToOrdinal(value: SheetSize): int32 {
        return value as int32
    }
    static SheetSize_FromOrdinal(ordinal: int32): SheetSize {
        return ordinal as SheetSize
    }
    static DragBehavior_ToOrdinal(value: DragBehavior): int32 {
        return value as int32
    }
    static DragBehavior_FromOrdinal(ordinal: int32): DragBehavior {
        return ordinal as DragBehavior
    }
    static DragResult_ToOrdinal(value: DragResult): int32 {
        return value as int32
    }
    static DragResult_FromOrdinal(ordinal: int32): DragResult {
        return ordinal as DragResult
    }
    static BlendMode_ToOrdinal(value: BlendMode): int32 {
        return value as int32
    }
    static BlendMode_FromOrdinal(ordinal: int32): BlendMode {
        return ordinal as BlendMode
    }
    static BlendApplyType_ToOrdinal(value: BlendApplyType): int32 {
        return value as int32
    }
    static BlendApplyType_FromOrdinal(ordinal: int32): BlendApplyType {
        return ordinal as BlendApplyType
    }
    static SheetType_ToOrdinal(value: SheetType): int32 {
        return value as int32
    }
    static SheetType_FromOrdinal(ordinal: int32): SheetType {
        return ordinal as SheetType
    }
    static SheetMode_ToOrdinal(value: SheetMode): int32 {
        return value as int32
    }
    static SheetMode_FromOrdinal(ordinal: int32): SheetMode {
        return ordinal as SheetMode
    }
    static ScrollSizeMode_ToOrdinal(value: ScrollSizeMode): int32 {
        return value as int32
    }
    static ScrollSizeMode_FromOrdinal(ordinal: int32): ScrollSizeMode {
        return ordinal as ScrollSizeMode
    }
    static SheetKeyboardAvoidMode_ToOrdinal(value: SheetKeyboardAvoidMode): int32 {
        return value as int32
    }
    static SheetKeyboardAvoidMode_FromOrdinal(ordinal: int32): SheetKeyboardAvoidMode {
        return ordinal as SheetKeyboardAvoidMode
    }
    static DismissReason_ToOrdinal(value: DismissReason): int32 {
        return value as int32
    }
    static DismissReason_FromOrdinal(ordinal: int32): DismissReason {
        return ordinal as DismissReason
    }
    static MenuPreviewMode_ToOrdinal(value: MenuPreviewMode): int32 {
        return value as int32
    }
    static MenuPreviewMode_FromOrdinal(ordinal: int32): MenuPreviewMode {
        return ordinal as MenuPreviewMode
    }
    static OutlineStyle_ToOrdinal(value: OutlineStyle): int32 {
        return value as int32
    }
    static OutlineStyle_FromOrdinal(ordinal: int32): OutlineStyle {
        return ordinal as OutlineStyle
    }
    static DragPreviewMode_ToOrdinal(value: DragPreviewMode): int32 {
        return value as int32
    }
    static DragPreviewMode_FromOrdinal(ordinal: int32): DragPreviewMode {
        return ordinal as DragPreviewMode
    }
    static MenuPolicy_ToOrdinal(value: MenuPolicy): int32 {
        return value as int32
    }
    static MenuPolicy_FromOrdinal(ordinal: int32): MenuPolicy {
        return ordinal as MenuPolicy
    }
    static ContentClipMode_ToOrdinal(value: ContentClipMode): int32 {
        return value as int32
    }
    static ContentClipMode_FromOrdinal(ordinal: int32): ContentClipMode {
        return ordinal as ContentClipMode
    }
    static KeyboardAvoidMode_ToOrdinal(value: KeyboardAvoidMode): int32 {
        return value as int32
    }
    static KeyboardAvoidMode_FromOrdinal(ordinal: int32): KeyboardAvoidMode {
        return ordinal as KeyboardAvoidMode
    }
    static HoverModeAreaType_ToOrdinal(value: HoverModeAreaType): int32 {
        return value as int32
    }
    static HoverModeAreaType_FromOrdinal(ordinal: int32): HoverModeAreaType {
        return ordinal as HoverModeAreaType
    }
    static ModelType_ToOrdinal(value: ModelType): int32 {
        return value as int32
    }
    static ModelType_FromOrdinal(ordinal: int32): ModelType {
        return ordinal as ModelType
    }
    static DataPanelType_ToOrdinal(value: DataPanelType): int32 {
        return value as int32
    }
    static DataPanelType_FromOrdinal(ordinal: int32): DataPanelType {
        return ordinal as DataPanelType
    }
    static CheckBoxShape_ToOrdinal(value: CheckBoxShape): int32 {
        return value as int32
    }
    static CheckBoxShape_FromOrdinal(ordinal: int32): CheckBoxShape {
        return ordinal as CheckBoxShape
    }
    static Color_ToOrdinal(value: Color): int32 {
        return value as int32
    }
    static Color_FromOrdinal(ordinal: int32): Color {
        return ordinal as Color
    }
    static ColoringStrategy_ToOrdinal(value: ColoringStrategy): int32 {
        return value as int32
    }
    static ColoringStrategy_FromOrdinal(ordinal: int32): ColoringStrategy {
        return ordinal as ColoringStrategy
    }
    static ImageFit_ToOrdinal(value: ImageFit): int32 {
        return value as int32
    }
    static ImageFit_FromOrdinal(ordinal: int32): ImageFit {
        return ordinal as ImageFit
    }
    static BorderStyle_ToOrdinal(value: BorderStyle): int32 {
        return value as int32
    }
    static BorderStyle_FromOrdinal(ordinal: int32): BorderStyle {
        return ordinal as BorderStyle
    }
    static LineJoinStyle_ToOrdinal(value: LineJoinStyle): int32 {
        return value as int32
    }
    static LineJoinStyle_FromOrdinal(ordinal: int32): LineJoinStyle {
        return ordinal as LineJoinStyle
    }
    static TouchType_ToOrdinal(value: TouchType): int32 {
        return value as int32
    }
    static TouchType_FromOrdinal(ordinal: int32): TouchType {
        return ordinal as TouchType
    }
    static MouseButton_ToOrdinal(value: MouseButton): int32 {
        return value as int32
    }
    static MouseButton_FromOrdinal(ordinal: int32): MouseButton {
        return ordinal as MouseButton
    }
    static MouseAction_ToOrdinal(value: MouseAction): int32 {
        return value as int32
    }
    static MouseAction_FromOrdinal(ordinal: int32): MouseAction {
        return ordinal as MouseAction
    }
    static AnimationStatus_ToOrdinal(value: AnimationStatus): int32 {
        return value as int32
    }
    static AnimationStatus_FromOrdinal(ordinal: int32): AnimationStatus {
        return ordinal as AnimationStatus
    }
    static Curve_ToOrdinal(value: Curve): int32 {
        return value as int32
    }
    static Curve_FromOrdinal(ordinal: int32): Curve {
        return ordinal as Curve
    }
    static FillMode_ToOrdinal(value: FillMode): int32 {
        return value as int32
    }
    static FillMode_FromOrdinal(ordinal: int32): FillMode {
        return ordinal as FillMode
    }
    static PlayMode_ToOrdinal(value: PlayMode): int32 {
        return value as int32
    }
    static PlayMode_FromOrdinal(ordinal: int32): PlayMode {
        return ordinal as PlayMode
    }
    static KeyType_ToOrdinal(value: KeyType): int32 {
        return value as int32
    }
    static KeyType_FromOrdinal(ordinal: int32): KeyType {
        return ordinal as KeyType
    }
    static KeySource_ToOrdinal(value: KeySource): int32 {
        return value as int32
    }
    static KeySource_FromOrdinal(ordinal: int32): KeySource {
        return ordinal as KeySource
    }
    static Edge_ToOrdinal(value: Edge): int32 {
        return value as int32
    }
    static Edge_FromOrdinal(ordinal: int32): Edge {
        return ordinal as Edge
    }
    static Week_ToOrdinal(value: Week): int32 {
        return value as int32
    }
    static Week_FromOrdinal(ordinal: int32): Week {
        return ordinal as Week
    }
    static Direction_ToOrdinal(value: Direction): int32 {
        return value as int32
    }
    static Direction_FromOrdinal(ordinal: int32): Direction {
        return ordinal as Direction
    }
    static BarState_ToOrdinal(value: BarState): int32 {
        return value as int32
    }
    static BarState_FromOrdinal(ordinal: int32): BarState {
        return ordinal as BarState
    }
    static EdgeEffect_ToOrdinal(value: EdgeEffect): int32 {
        return value as int32
    }
    static EdgeEffect_FromOrdinal(ordinal: int32): EdgeEffect {
        return ordinal as EdgeEffect
    }
    static Alignment_ToOrdinal(value: Alignment): int32 {
        return value as int32
    }
    static Alignment_FromOrdinal(ordinal: int32): Alignment {
        return ordinal as Alignment
    }
    static TransitionType_ToOrdinal(value: TransitionType): int32 {
        return value as int32
    }
    static TransitionType_FromOrdinal(ordinal: int32): TransitionType {
        return ordinal as TransitionType
    }
    static RelateType_ToOrdinal(value: RelateType): int32 {
        return value as int32
    }
    static RelateType_FromOrdinal(ordinal: int32): RelateType {
        return ordinal as RelateType
    }
    static Visibility_ToOrdinal(value: Visibility): int32 {
        return value as int32
    }
    static Visibility_FromOrdinal(ordinal: int32): Visibility {
        return ordinal as Visibility
    }
    static LineCapStyle_ToOrdinal(value: LineCapStyle): int32 {
        return value as int32
    }
    static LineCapStyle_FromOrdinal(ordinal: int32): LineCapStyle {
        return ordinal as LineCapStyle
    }
    static Axis_ToOrdinal(value: Axis): int32 {
        return value as int32
    }
    static Axis_FromOrdinal(ordinal: int32): Axis {
        return ordinal as Axis
    }
    static HorizontalAlign_ToOrdinal(value: HorizontalAlign): int32 {
        return value as int32
    }
    static HorizontalAlign_FromOrdinal(ordinal: int32): HorizontalAlign {
        return ordinal as HorizontalAlign
    }
    static FlexAlign_ToOrdinal(value: FlexAlign): int32 {
        return value as int32
    }
    static FlexAlign_FromOrdinal(ordinal: int32): FlexAlign {
        return ordinal as FlexAlign
    }
    static ItemAlign_ToOrdinal(value: ItemAlign): int32 {
        return value as int32
    }
    static ItemAlign_FromOrdinal(ordinal: int32): ItemAlign {
        return ordinal as ItemAlign
    }
    static FlexDirection_ToOrdinal(value: FlexDirection): int32 {
        return value as int32
    }
    static FlexDirection_FromOrdinal(ordinal: int32): FlexDirection {
        return ordinal as FlexDirection
    }
    static PixelRoundCalcPolicy_ToOrdinal(value: PixelRoundCalcPolicy): int32 {
        return value as int32
    }
    static PixelRoundCalcPolicy_FromOrdinal(ordinal: int32): PixelRoundCalcPolicy {
        return ordinal as PixelRoundCalcPolicy
    }
    static FlexWrap_ToOrdinal(value: FlexWrap): int32 {
        return value as int32
    }
    static FlexWrap_FromOrdinal(ordinal: int32): FlexWrap {
        return ordinal as FlexWrap
    }
    static VerticalAlign_ToOrdinal(value: VerticalAlign): int32 {
        return value as int32
    }
    static VerticalAlign_FromOrdinal(ordinal: int32): VerticalAlign {
        return ordinal as VerticalAlign
    }
    static ImageRepeat_ToOrdinal(value: ImageRepeat): int32 {
        return value as int32
    }
    static ImageRepeat_FromOrdinal(ordinal: int32): ImageRepeat {
        return ordinal as ImageRepeat
    }
    static ImageSize_ToOrdinal(value: ImageSize): int32 {
        return value as int32
    }
    static ImageSize_FromOrdinal(ordinal: int32): ImageSize {
        return ordinal as ImageSize
    }
    static GradientDirection_ToOrdinal(value: GradientDirection): int32 {
        return value as int32
    }
    static GradientDirection_FromOrdinal(ordinal: int32): GradientDirection {
        return ordinal as GradientDirection
    }
    static SharedTransitionEffectType_ToOrdinal(value: SharedTransitionEffectType): int32 {
        return value as int32
    }
    static SharedTransitionEffectType_FromOrdinal(ordinal: int32): SharedTransitionEffectType {
        return ordinal as SharedTransitionEffectType
    }
    static FontStyle_ToOrdinal(value: FontStyle): int32 {
        return value as int32
    }
    static FontStyle_FromOrdinal(ordinal: int32): FontStyle {
        return ordinal as FontStyle
    }
    static FontWeight_ToOrdinal(value: FontWeight): int32 {
        return value as int32
    }
    static FontWeight_FromOrdinal(ordinal: int32): FontWeight {
        return ordinal as FontWeight
    }
    static TextAlign_ToOrdinal(value: TextAlign): int32 {
        return value as int32
    }
    static TextAlign_FromOrdinal(ordinal: int32): TextAlign {
        return ordinal as TextAlign
    }
    static TextOverflow_ToOrdinal(value: TextOverflow): int32 {
        return value as int32
    }
    static TextOverflow_FromOrdinal(ordinal: int32): TextOverflow {
        return ordinal as TextOverflow
    }
    static TextDecorationType_ToOrdinal(value: TextDecorationType): int32 {
        return value as int32
    }
    static TextDecorationType_FromOrdinal(ordinal: int32): TextDecorationType {
        return ordinal as TextDecorationType
    }
    static TextCase_ToOrdinal(value: TextCase): int32 {
        return value as int32
    }
    static TextCase_FromOrdinal(ordinal: int32): TextCase {
        return ordinal as TextCase
    }
    static TextHeightAdaptivePolicy_ToOrdinal(value: TextHeightAdaptivePolicy): int32 {
        return value as int32
    }
    static TextHeightAdaptivePolicy_FromOrdinal(ordinal: int32): TextHeightAdaptivePolicy {
        return ordinal as TextHeightAdaptivePolicy
    }
    static ResponseType_ToOrdinal(value: ResponseType): int32 {
        return value as int32
    }
    static ResponseType_FromOrdinal(ordinal: int32): ResponseType {
        return ordinal as ResponseType
    }
    static HoverEffect_ToOrdinal(value: HoverEffect): int32 {
        return value as int32
    }
    static HoverEffect_FromOrdinal(ordinal: int32): HoverEffect {
        return ordinal as HoverEffect
    }
    static Placement_ToOrdinal(value: Placement): int32 {
        return value as int32
    }
    static Placement_FromOrdinal(ordinal: int32): Placement {
        return ordinal as Placement
    }
    static ArrowPointPosition_ToOrdinal(value: ArrowPointPosition): int32 {
        return value as int32
    }
    static ArrowPointPosition_FromOrdinal(ordinal: int32): ArrowPointPosition {
        return ordinal as ArrowPointPosition
    }
    static CopyOptions_ToOrdinal(value: CopyOptions): int32 {
        return value as int32
    }
    static CopyOptions_FromOrdinal(ordinal: int32): CopyOptions {
        return ordinal as CopyOptions
    }
    static HitTestMode_ToOrdinal(value: HitTestMode): int32 {
        return value as int32
    }
    static HitTestMode_FromOrdinal(ordinal: int32): HitTestMode {
        return ordinal as HitTestMode
    }
    static TitleHeight_ToOrdinal(value: TitleHeight): int32 {
        return value as int32
    }
    static TitleHeight_FromOrdinal(ordinal: int32): TitleHeight {
        return ordinal as TitleHeight
    }
    static ModifierKey_ToOrdinal(value: ModifierKey): int32 {
        return value as int32
    }
    static ModifierKey_FromOrdinal(ordinal: int32): ModifierKey {
        return ordinal as ModifierKey
    }
    static FunctionKey_ToOrdinal(value: FunctionKey): int32 {
        return value as int32
    }
    static FunctionKey_FromOrdinal(ordinal: int32): FunctionKey {
        return ordinal as FunctionKey
    }
    static ImageSpanAlignment_ToOrdinal(value: ImageSpanAlignment): int32 {
        return value as int32
    }
    static ImageSpanAlignment_FromOrdinal(ordinal: int32): ImageSpanAlignment {
        return ordinal as ImageSpanAlignment
    }
    static ObscuredReasons_ToOrdinal(value: ObscuredReasons): int32 {
        return value as int32
    }
    static ObscuredReasons_FromOrdinal(ordinal: int32): ObscuredReasons {
        return ordinal as ObscuredReasons
    }
    static TextContentStyle_ToOrdinal(value: TextContentStyle): int32 {
        return value as int32
    }
    static TextContentStyle_FromOrdinal(ordinal: int32): TextContentStyle {
        return ordinal as TextContentStyle
    }
    static ClickEffectLevel_ToOrdinal(value: ClickEffectLevel): int32 {
        return value as int32
    }
    static ClickEffectLevel_FromOrdinal(ordinal: int32): ClickEffectLevel {
        return ordinal as ClickEffectLevel
    }
    static XComponentType_ToOrdinal(value: XComponentType): int32 {
        return value as int32
    }
    static XComponentType_FromOrdinal(ordinal: int32): XComponentType {
        return ordinal as XComponentType
    }
    static NestedScrollMode_ToOrdinal(value: NestedScrollMode): int32 {
        return value as int32
    }
    static NestedScrollMode_FromOrdinal(ordinal: int32): NestedScrollMode {
        return ordinal as NestedScrollMode
    }
    static ScrollSource_ToOrdinal(value: ScrollSource): int32 {
        return value as int32
    }
    static ScrollSource_FromOrdinal(ordinal: int32): ScrollSource {
        return ordinal as ScrollSource
    }
    static RenderFit_ToOrdinal(value: RenderFit): int32 {
        return value as int32
    }
    static RenderFit_FromOrdinal(ordinal: int32): RenderFit {
        return ordinal as RenderFit
    }
    static DialogButtonStyle_ToOrdinal(value: DialogButtonStyle): int32 {
        return value as int32
    }
    static DialogButtonStyle_FromOrdinal(ordinal: int32): DialogButtonStyle {
        return ordinal as DialogButtonStyle
    }
    static WordBreak_ToOrdinal(value: WordBreak): int32 {
        return value as int32
    }
    static WordBreak_FromOrdinal(ordinal: int32): WordBreak {
        return ordinal as WordBreak
    }
    static LineBreakStrategy_ToOrdinal(value: LineBreakStrategy): int32 {
        return value as int32
    }
    static LineBreakStrategy_FromOrdinal(ordinal: int32): LineBreakStrategy {
        return ordinal as LineBreakStrategy
    }
    static EllipsisMode_ToOrdinal(value: EllipsisMode): int32 {
        return value as int32
    }
    static EllipsisMode_FromOrdinal(ordinal: int32): EllipsisMode {
        return ordinal as EllipsisMode
    }
    static OptionWidthMode_ToOrdinal(value: OptionWidthMode): int32 {
        return value as int32
    }
    static OptionWidthMode_FromOrdinal(ordinal: int32): OptionWidthMode {
        return ordinal as OptionWidthMode
    }
    static IlluminatedType_ToOrdinal(value: IlluminatedType): int32 {
        return value as int32
    }
    static IlluminatedType_FromOrdinal(ordinal: int32): IlluminatedType {
        return ordinal as IlluminatedType
    }
    static FoldStatus_ToOrdinal(value: FoldStatus): int32 {
        return value as int32
    }
    static FoldStatus_FromOrdinal(ordinal: int32): FoldStatus {
        return ordinal as FoldStatus
    }
    static AppRotation_ToOrdinal(value: AppRotation): int32 {
        return value as int32
    }
    static AppRotation_FromOrdinal(ordinal: int32): AppRotation {
        return ordinal as AppRotation
    }
    static EmbeddedType_ToOrdinal(value: EmbeddedType): int32 {
        return value as int32
    }
    static EmbeddedType_FromOrdinal(ordinal: int32): EmbeddedType {
        return ordinal as EmbeddedType
    }
    static MarqueeUpdateStrategy_ToOrdinal(value: MarqueeUpdateStrategy): int32 {
        return value as int32
    }
    static MarqueeUpdateStrategy_FromOrdinal(ordinal: int32): MarqueeUpdateStrategy {
        return ordinal as MarqueeUpdateStrategy
    }
    static TextDecorationStyle_ToOrdinal(value: TextDecorationStyle): int32 {
        return value as int32
    }
    static TextDecorationStyle_FromOrdinal(ordinal: int32): TextDecorationStyle {
        return ordinal as TextDecorationStyle
    }
    static TextSelectableMode_ToOrdinal(value: TextSelectableMode): int32 {
        return value as int32
    }
    static TextSelectableMode_FromOrdinal(ordinal: int32): TextSelectableMode {
        return ordinal as TextSelectableMode
    }
    static AccessibilityHoverType_ToOrdinal(value: AccessibilityHoverType): int32 {
        return value as int32
    }
    static AccessibilityHoverType_FromOrdinal(ordinal: int32): AccessibilityHoverType {
        return ordinal as AccessibilityHoverType
    }
    static WidthBreakpoint_ToOrdinal(value: WidthBreakpoint): int32 {
        return value as int32
    }
    static WidthBreakpoint_FromOrdinal(ordinal: int32): WidthBreakpoint {
        return ordinal as WidthBreakpoint
    }
    static HeightBreakpoint_ToOrdinal(value: HeightBreakpoint): int32 {
        return value as int32
    }
    static HeightBreakpoint_FromOrdinal(ordinal: int32): HeightBreakpoint {
        return ordinal as HeightBreakpoint
    }
    static FocusPriority_ToOrdinal(value: FocusPriority): int32 {
        return value as int32
    }
    static FocusPriority_FromOrdinal(ordinal: int32): FocusPriority {
        return ordinal as FocusPriority
    }
    static FormDimension_ToOrdinal(value: FormDimension): int32 {
        return value as int32
    }
    static FormDimension_FromOrdinal(ordinal: int32): FormDimension {
        return ordinal as FormDimension
    }
    static FormRenderingMode_ToOrdinal(value: FormRenderingMode): int32 {
        return value as int32
    }
    static FormRenderingMode_FromOrdinal(ordinal: int32): FormRenderingMode {
        return ordinal as FormRenderingMode
    }
    static FormShape_ToOrdinal(value: FormShape): int32 {
        return value as int32
    }
    static FormShape_FromOrdinal(ordinal: int32): FormShape {
        return ordinal as FormShape
    }
    static PanDirection_ToOrdinal(value: PanDirection): int32 {
        return value as int32
    }
    static PanDirection_FromOrdinal(ordinal: int32): PanDirection {
        return ordinal as PanDirection
    }
    static SwipeDirection_ToOrdinal(value: SwipeDirection): int32 {
        return value as int32
    }
    static SwipeDirection_FromOrdinal(ordinal: int32): SwipeDirection {
        return ordinal as SwipeDirection
    }
    static GestureMode_ToOrdinal(value: GestureMode): int32 {
        return value as int32
    }
    static GestureMode_FromOrdinal(ordinal: int32): GestureMode {
        return ordinal as GestureMode
    }
    static GestureMask_ToOrdinal(value: GestureMask): int32 {
        return value as int32
    }
    static GestureMask_FromOrdinal(ordinal: int32): GestureMask {
        return ordinal as GestureMask
    }
    static GestureJudgeResult_ToOrdinal(value: GestureJudgeResult): int32 {
        return value as int32
    }
    static GestureJudgeResult_FromOrdinal(ordinal: int32): GestureJudgeResult {
        return ordinal as GestureJudgeResult
    }
    static GestureControl_GestureType_ToOrdinal(value: GestureControl.GestureType): int32 {
        return value as int32
    }
    static GestureControl_GestureType_FromOrdinal(ordinal: int32): GestureControl.GestureType {
        return ordinal as GestureControl.GestureType
    }
    static GesturePriority_ToOrdinal(value: GesturePriority): int32 {
        return value as int32
    }
    static GesturePriority_FromOrdinal(ordinal: int32): GesturePriority {
        return ordinal as GesturePriority
    }
    static GestureRecognizerState_ToOrdinal(value: GestureRecognizerState): int32 {
        return value as int32
    }
    static GestureRecognizerState_FromOrdinal(ordinal: int32): GestureRecognizerState {
        return ordinal as GestureRecognizerState
    }
    static GridDirection_ToOrdinal(value: GridDirection): int32 {
        return value as int32
    }
    static GridDirection_FromOrdinal(ordinal: int32): GridDirection {
        return ordinal as GridDirection
    }
    static GridItemAlignment_ToOrdinal(value: GridItemAlignment): int32 {
        return value as int32
    }
    static GridItemAlignment_FromOrdinal(ordinal: int32): GridItemAlignment {
        return ordinal as GridItemAlignment
    }
    static GridItemStyle_ToOrdinal(value: GridItemStyle): int32 {
        return value as int32
    }
    static GridItemStyle_FromOrdinal(ordinal: int32): GridItemStyle {
        return ordinal as GridItemStyle
    }
    static SizeType_ToOrdinal(value: SizeType): int32 {
        return value as int32
    }
    static SizeType_FromOrdinal(ordinal: int32): SizeType {
        return ordinal as SizeType
    }
    static BreakpointsReference_ToOrdinal(value: BreakpointsReference): int32 {
        return value as int32
    }
    static BreakpointsReference_FromOrdinal(ordinal: int32): BreakpointsReference {
        return ordinal as BreakpointsReference
    }
    static GridRowDirection_ToOrdinal(value: GridRowDirection): int32 {
        return value as int32
    }
    static GridRowDirection_FromOrdinal(ordinal: int32): GridRowDirection {
        return ordinal as GridRowDirection
    }
    static ImageRenderMode_ToOrdinal(value: ImageRenderMode): int32 {
        return value as int32
    }
    static ImageRenderMode_FromOrdinal(ordinal: int32): ImageRenderMode {
        return ordinal as ImageRenderMode
    }
    static ImageContent_ToOrdinal(value: ImageContent): int32 {
        return value as int32
    }
    static ImageContent_FromOrdinal(ordinal: int32): ImageContent {
        return ordinal as ImageContent
    }
    static DynamicRangeMode_ToOrdinal(value: DynamicRangeMode): int32 {
        return value as int32
    }
    static DynamicRangeMode_FromOrdinal(ordinal: int32): DynamicRangeMode {
        return ordinal as DynamicRangeMode
    }
    static ImageInterpolation_ToOrdinal(value: ImageInterpolation): int32 {
        return value as int32
    }
    static ImageInterpolation_FromOrdinal(ordinal: int32): ImageInterpolation {
        return ordinal as ImageInterpolation
    }
    static ImageAnalyzerType_ToOrdinal(value: ImageAnalyzerType): int32 {
        return value as int32
    }
    static ImageAnalyzerType_FromOrdinal(ordinal: int32): ImageAnalyzerType {
        return ordinal as ImageAnalyzerType
    }
    static DataOperationType_ToOrdinal(value: DataOperationType): int32 {
        return value as int32
    }
    static DataOperationType_FromOrdinal(ordinal: int32): DataOperationType {
        return ordinal as DataOperationType
    }
    static ScrollState_ToOrdinal(value: ScrollState): int32 {
        return value as int32
    }
    static ScrollState_FromOrdinal(ordinal: int32): ScrollState {
        return ordinal as ScrollState
    }
    static ListItemAlign_ToOrdinal(value: ListItemAlign): int32 {
        return value as int32
    }
    static ListItemAlign_FromOrdinal(ordinal: int32): ListItemAlign {
        return ordinal as ListItemAlign
    }
    static ListItemGroupArea_ToOrdinal(value: ListItemGroupArea): int32 {
        return value as int32
    }
    static ListItemGroupArea_FromOrdinal(ordinal: int32): ListItemGroupArea {
        return ordinal as ListItemGroupArea
    }
    static StickyStyle_ToOrdinal(value: StickyStyle): int32 {
        return value as int32
    }
    static StickyStyle_FromOrdinal(ordinal: int32): StickyStyle {
        return ordinal as StickyStyle
    }
    static ChainEdgeEffect_ToOrdinal(value: ChainEdgeEffect): int32 {
        return value as int32
    }
    static ChainEdgeEffect_FromOrdinal(ordinal: int32): ChainEdgeEffect {
        return ordinal as ChainEdgeEffect
    }
    static ScrollSnapAlign_ToOrdinal(value: ScrollSnapAlign): int32 {
        return value as int32
    }
    static ScrollSnapAlign_FromOrdinal(ordinal: int32): ScrollSnapAlign {
        return ordinal as ScrollSnapAlign
    }
    static Sticky_ToOrdinal(value: Sticky): int32 {
        return value as int32
    }
    static Sticky_FromOrdinal(ordinal: int32): Sticky {
        return ordinal as Sticky
    }
    static EditMode_ToOrdinal(value: EditMode): int32 {
        return value as int32
    }
    static EditMode_FromOrdinal(ordinal: int32): EditMode {
        return ordinal as EditMode
    }
    static SwipeEdgeEffect_ToOrdinal(value: SwipeEdgeEffect): int32 {
        return value as int32
    }
    static SwipeEdgeEffect_FromOrdinal(ordinal: int32): SwipeEdgeEffect {
        return ordinal as SwipeEdgeEffect
    }
    static SwipeActionState_ToOrdinal(value: SwipeActionState): int32 {
        return value as int32
    }
    static SwipeActionState_FromOrdinal(ordinal: int32): SwipeActionState {
        return ordinal as SwipeActionState
    }
    static ListItemStyle_ToOrdinal(value: ListItemStyle): int32 {
        return value as int32
    }
    static ListItemStyle_FromOrdinal(ordinal: int32): ListItemStyle {
        return ordinal as ListItemStyle
    }
    static ListItemGroupStyle_ToOrdinal(value: ListItemGroupStyle): int32 {
        return value as int32
    }
    static ListItemGroupStyle_FromOrdinal(ordinal: int32): ListItemGroupStyle {
        return ordinal as ListItemGroupStyle
    }
    static LoadingProgressStyle_ToOrdinal(value: LoadingProgressStyle): int32 {
        return value as int32
    }
    static LoadingProgressStyle_FromOrdinal(ordinal: int32): LoadingProgressStyle {
        return ordinal as LoadingProgressStyle
    }
    static LocationIconStyle_ToOrdinal(value: LocationIconStyle): int32 {
        return value as int32
    }
    static LocationIconStyle_FromOrdinal(ordinal: int32): LocationIconStyle {
        return ordinal as LocationIconStyle
    }
    static LocationDescription_ToOrdinal(value: LocationDescription): int32 {
        return value as int32
    }
    static LocationDescription_FromOrdinal(ordinal: int32): LocationDescription {
        return ordinal as LocationDescription
    }
    static LocationButtonOnClickResult_ToOrdinal(value: LocationButtonOnClickResult): int32 {
        return value as int32
    }
    static LocationButtonOnClickResult_FromOrdinal(ordinal: int32): LocationButtonOnClickResult {
        return ordinal as LocationButtonOnClickResult
    }
    static SubMenuExpandingMode_ToOrdinal(value: SubMenuExpandingMode): int32 {
        return value as int32
    }
    static SubMenuExpandingMode_FromOrdinal(ordinal: int32): SubMenuExpandingMode {
        return ordinal as SubMenuExpandingMode
    }
    static NavigationSystemTransitionType_ToOrdinal(value: NavigationSystemTransitionType): int32 {
        return value as int32
    }
    static NavigationSystemTransitionType_FromOrdinal(ordinal: int32): NavigationSystemTransitionType {
        return ordinal as NavigationSystemTransitionType
    }
    static NavDestinationMode_ToOrdinal(value: NavDestinationMode): int32 {
        return value as int32
    }
    static NavDestinationMode_FromOrdinal(ordinal: int32): NavDestinationMode {
        return ordinal as NavDestinationMode
    }
    static NavRouteMode_ToOrdinal(value: NavRouteMode): int32 {
        return value as int32
    }
    static NavRouteMode_FromOrdinal(ordinal: int32): NavRouteMode {
        return ordinal as NavRouteMode
    }
    static NavigationMode_ToOrdinal(value: NavigationMode): int32 {
        return value as int32
    }
    static NavigationMode_FromOrdinal(ordinal: int32): NavigationMode {
        return ordinal as NavigationMode
    }
    static NavBarPosition_ToOrdinal(value: NavBarPosition): int32 {
        return value as int32
    }
    static NavBarPosition_FromOrdinal(ordinal: int32): NavBarPosition {
        return ordinal as NavBarPosition
    }
    static NavigationTitleMode_ToOrdinal(value: NavigationTitleMode): int32 {
        return value as int32
    }
    static NavigationTitleMode_FromOrdinal(ordinal: int32): NavigationTitleMode {
        return ordinal as NavigationTitleMode
    }
    static LaunchMode_ToOrdinal(value: LaunchMode): int32 {
        return value as int32
    }
    static LaunchMode_FromOrdinal(ordinal: int32): LaunchMode {
        return ordinal as LaunchMode
    }
    static ToolbarItemStatus_ToOrdinal(value: ToolbarItemStatus): int32 {
        return value as int32
    }
    static ToolbarItemStatus_FromOrdinal(ordinal: int32): ToolbarItemStatus {
        return ordinal as ToolbarItemStatus
    }
    static NavigationOperation_ToOrdinal(value: NavigationOperation): int32 {
        return value as int32
    }
    static NavigationOperation_FromOrdinal(ordinal: int32): NavigationOperation {
        return ordinal as NavigationOperation
    }
    static BarStyle_ToOrdinal(value: BarStyle): int32 {
        return value as int32
    }
    static BarStyle_FromOrdinal(ordinal: int32): BarStyle {
        return ordinal as BarStyle
    }
    static NavigationType_ToOrdinal(value: NavigationType): int32 {
        return value as int32
    }
    static NavigationType_FromOrdinal(ordinal: int32): NavigationType {
        return ordinal as NavigationType
    }
    static RouteType_ToOrdinal(value: RouteType): int32 {
        return value as int32
    }
    static RouteType_FromOrdinal(ordinal: int32): RouteType {
        return ordinal as RouteType
    }
    static SlideEffect_ToOrdinal(value: SlideEffect): int32 {
        return value as int32
    }
    static SlideEffect_FromOrdinal(ordinal: int32): SlideEffect {
        return ordinal as SlideEffect
    }
    static PanelMode_ToOrdinal(value: PanelMode): int32 {
        return value as int32
    }
    static PanelMode_FromOrdinal(ordinal: int32): PanelMode {
        return ordinal as PanelMode
    }
    static PanelType_ToOrdinal(value: PanelType): int32 {
        return value as int32
    }
    static PanelType_FromOrdinal(ordinal: int32): PanelType {
        return ordinal as PanelType
    }
    static PanelHeight_ToOrdinal(value: PanelHeight): int32 {
        return value as int32
    }
    static PanelHeight_FromOrdinal(ordinal: int32): PanelHeight {
        return ordinal as PanelHeight
    }
    static ParticleType_ToOrdinal(value: ParticleType): int32 {
        return value as int32
    }
    static ParticleType_FromOrdinal(ordinal: int32): ParticleType {
        return ordinal as ParticleType
    }
    static ParticleEmitterShape_ToOrdinal(value: ParticleEmitterShape): int32 {
        return value as int32
    }
    static ParticleEmitterShape_FromOrdinal(ordinal: int32): ParticleEmitterShape {
        return ordinal as ParticleEmitterShape
    }
    static DistributionType_ToOrdinal(value: DistributionType): int32 {
        return value as int32
    }
    static DistributionType_FromOrdinal(ordinal: int32): DistributionType {
        return ordinal as DistributionType
    }
    static ParticleUpdater_ToOrdinal(value: ParticleUpdater): int32 {
        return value as int32
    }
    static ParticleUpdater_FromOrdinal(ordinal: int32): ParticleUpdater {
        return ordinal as ParticleUpdater
    }
    static DisturbanceFieldShape_ToOrdinal(value: DisturbanceFieldShape): int32 {
        return value as int32
    }
    static DisturbanceFieldShape_FromOrdinal(ordinal: int32): DisturbanceFieldShape {
        return ordinal as DisturbanceFieldShape
    }
    static PasteIconStyle_ToOrdinal(value: PasteIconStyle): int32 {
        return value as int32
    }
    static PasteIconStyle_FromOrdinal(ordinal: int32): PasteIconStyle {
        return ordinal as PasteIconStyle
    }
    static PasteDescription_ToOrdinal(value: PasteDescription): int32 {
        return value as int32
    }
    static PasteDescription_FromOrdinal(ordinal: int32): PasteDescription {
        return ordinal as PasteDescription
    }
    static PasteButtonOnClickResult_ToOrdinal(value: PasteButtonOnClickResult): int32 {
        return value as int32
    }
    static PasteButtonOnClickResult_FromOrdinal(ordinal: int32): PasteButtonOnClickResult {
        return ordinal as PasteButtonOnClickResult
    }
    static PatternLockChallengeResult_ToOrdinal(value: PatternLockChallengeResult): int32 {
        return value as int32
    }
    static PatternLockChallengeResult_FromOrdinal(ordinal: int32): PatternLockChallengeResult {
        return ordinal as PatternLockChallengeResult
    }
    static ProgressType_ToOrdinal(value: ProgressType): int32 {
        return value as int32
    }
    static ProgressType_FromOrdinal(ordinal: int32): ProgressType {
        return ordinal as ProgressType
    }
    static ProgressStatus_ToOrdinal(value: ProgressStatus): int32 {
        return value as int32
    }
    static ProgressStatus_FromOrdinal(ordinal: int32): ProgressStatus {
        return ordinal as ProgressStatus
    }
    static ProgressStyle_ToOrdinal(value: ProgressStyle): int32 {
        return value as int32
    }
    static ProgressStyle_FromOrdinal(ordinal: int32): ProgressStyle {
        return ordinal as ProgressStyle
    }
    static RadioIndicatorType_ToOrdinal(value: RadioIndicatorType): int32 {
        return value as int32
    }
    static RadioIndicatorType_FromOrdinal(ordinal: int32): RadioIndicatorType {
        return ordinal as RadioIndicatorType
    }
    static RefreshStatus_ToOrdinal(value: RefreshStatus): int32 {
        return value as int32
    }
    static RefreshStatus_FromOrdinal(ordinal: int32): RefreshStatus {
        return ordinal as RefreshStatus
    }
    static BarrierDirection_ToOrdinal(value: BarrierDirection): int32 {
        return value as int32
    }
    static BarrierDirection_FromOrdinal(ordinal: int32): BarrierDirection {
        return ordinal as BarrierDirection
    }
    static LocalizedBarrierDirection_ToOrdinal(value: LocalizedBarrierDirection): int32 {
        return value as int32
    }
    static LocalizedBarrierDirection_FromOrdinal(ordinal: int32): LocalizedBarrierDirection {
        return ordinal as LocalizedBarrierDirection
    }
    static RichEditorDeleteDirection_ToOrdinal(value: RichEditorDeleteDirection): int32 {
        return value as int32
    }
    static RichEditorDeleteDirection_FromOrdinal(ordinal: int32): RichEditorDeleteDirection {
        return ordinal as RichEditorDeleteDirection
    }
    static RichEditorSpanType_ToOrdinal(value: RichEditorSpanType): int32 {
        return value as int32
    }
    static RichEditorSpanType_FromOrdinal(ordinal: int32): RichEditorSpanType {
        return ordinal as RichEditorSpanType
    }
    static RichEditorResponseType_ToOrdinal(value: RichEditorResponseType): int32 {
        return value as int32
    }
    static RichEditorResponseType_FromOrdinal(ordinal: int32): RichEditorResponseType {
        return ordinal as RichEditorResponseType
    }
    static SaveIconStyle_ToOrdinal(value: SaveIconStyle): int32 {
        return value as int32
    }
    static SaveIconStyle_FromOrdinal(ordinal: int32): SaveIconStyle {
        return ordinal as SaveIconStyle
    }
    static SaveDescription_ToOrdinal(value: SaveDescription): int32 {
        return value as int32
    }
    static SaveDescription_FromOrdinal(ordinal: int32): SaveDescription {
        return ordinal as SaveDescription
    }
    static SaveButtonOnClickResult_ToOrdinal(value: SaveButtonOnClickResult): int32 {
        return value as int32
    }
    static SaveButtonOnClickResult_FromOrdinal(ordinal: int32): SaveButtonOnClickResult {
        return ordinal as SaveButtonOnClickResult
    }
    static ScrollDirection_ToOrdinal(value: ScrollDirection): int32 {
        return value as int32
    }
    static ScrollDirection_FromOrdinal(ordinal: int32): ScrollDirection {
        return ordinal as ScrollDirection
    }
    static ScrollAlign_ToOrdinal(value: ScrollAlign): int32 {
        return value as int32
    }
    static ScrollAlign_FromOrdinal(ordinal: int32): ScrollAlign {
        return ordinal as ScrollAlign
    }
    static ScrollBarDirection_ToOrdinal(value: ScrollBarDirection): int32 {
        return value as int32
    }
    static ScrollBarDirection_FromOrdinal(ordinal: int32): ScrollBarDirection {
        return ordinal as ScrollBarDirection
    }
    static CancelButtonStyle_ToOrdinal(value: CancelButtonStyle): int32 {
        return value as int32
    }
    static CancelButtonStyle_FromOrdinal(ordinal: int32): CancelButtonStyle {
        return ordinal as CancelButtonStyle
    }
    static SearchType_ToOrdinal(value: SearchType): int32 {
        return value as int32
    }
    static SearchType_FromOrdinal(ordinal: int32): SearchType {
        return ordinal as SearchType
    }
    static SecurityComponentLayoutDirection_ToOrdinal(value: SecurityComponentLayoutDirection): int32 {
        return value as int32
    }
    static SecurityComponentLayoutDirection_FromOrdinal(ordinal: int32): SecurityComponentLayoutDirection {
        return ordinal as SecurityComponentLayoutDirection
    }
    static ArrowPosition_ToOrdinal(value: ArrowPosition): int32 {
        return value as int32
    }
    static ArrowPosition_FromOrdinal(ordinal: int32): ArrowPosition {
        return ordinal as ArrowPosition
    }
    static MenuAlignType_ToOrdinal(value: MenuAlignType): int32 {
        return value as int32
    }
    static MenuAlignType_FromOrdinal(ordinal: int32): MenuAlignType {
        return ordinal as MenuAlignType
    }
    static SliderStyle_ToOrdinal(value: SliderStyle): int32 {
        return value as int32
    }
    static SliderStyle_FromOrdinal(ordinal: int32): SliderStyle {
        return ordinal as SliderStyle
    }
    static SliderChangeMode_ToOrdinal(value: SliderChangeMode): int32 {
        return value as int32
    }
    static SliderChangeMode_FromOrdinal(ordinal: int32): SliderChangeMode {
        return ordinal as SliderChangeMode
    }
    static SliderInteraction_ToOrdinal(value: SliderInteraction): int32 {
        return value as int32
    }
    static SliderInteraction_FromOrdinal(ordinal: int32): SliderInteraction {
        return ordinal as SliderInteraction
    }
    static SliderBlockType_ToOrdinal(value: SliderBlockType): int32 {
        return value as int32
    }
    static SliderBlockType_FromOrdinal(ordinal: int32): SliderBlockType {
        return ordinal as SliderBlockType
    }
    static ColorMode_ToOrdinal(value: ColorMode): int32 {
        return value as int32
    }
    static ColorMode_FromOrdinal(ordinal: int32): ColorMode {
        return ordinal as ColorMode
    }
    static LayoutDirection_ToOrdinal(value: LayoutDirection): int32 {
        return value as int32
    }
    static LayoutDirection_FromOrdinal(ordinal: int32): LayoutDirection {
        return ordinal as LayoutDirection
    }
    static ItemState_ToOrdinal(value: ItemState): int32 {
        return value as int32
    }
    static ItemState_FromOrdinal(ordinal: int32): ItemState {
        return ordinal as ItemState
    }
    static SwiperDisplayMode_ToOrdinal(value: SwiperDisplayMode): int32 {
        return value as int32
    }
    static SwiperDisplayMode_FromOrdinal(ordinal: int32): SwiperDisplayMode {
        return ordinal as SwiperDisplayMode
    }
    static SwiperNestedScrollMode_ToOrdinal(value: SwiperNestedScrollMode): int32 {
        return value as int32
    }
    static SwiperNestedScrollMode_FromOrdinal(ordinal: int32): SwiperNestedScrollMode {
        return ordinal as SwiperNestedScrollMode
    }
    static SymbolRenderingStrategy_ToOrdinal(value: SymbolRenderingStrategy): int32 {
        return value as int32
    }
    static SymbolRenderingStrategy_FromOrdinal(ordinal: int32): SymbolRenderingStrategy {
        return ordinal as SymbolRenderingStrategy
    }
    static SymbolEffectStrategy_ToOrdinal(value: SymbolEffectStrategy): int32 {
        return value as int32
    }
    static SymbolEffectStrategy_FromOrdinal(ordinal: int32): SymbolEffectStrategy {
        return ordinal as SymbolEffectStrategy
    }
    static EffectFillStyle_ToOrdinal(value: EffectFillStyle): int32 {
        return value as int32
    }
    static EffectFillStyle_FromOrdinal(ordinal: int32): EffectFillStyle {
        return ordinal as EffectFillStyle
    }
    static BarMode_ToOrdinal(value: BarMode): int32 {
        return value as int32
    }
    static BarMode_FromOrdinal(ordinal: int32): BarMode {
        return ordinal as BarMode
    }
    static AnimationMode_ToOrdinal(value: AnimationMode): int32 {
        return value as int32
    }
    static AnimationMode_FromOrdinal(ordinal: int32): AnimationMode {
        return ordinal as AnimationMode
    }
    static BarPosition_ToOrdinal(value: BarPosition): int32 {
        return value as int32
    }
    static BarPosition_FromOrdinal(ordinal: int32): BarPosition {
        return ordinal as BarPosition
    }
    static LayoutStyle_ToOrdinal(value: LayoutStyle): int32 {
        return value as int32
    }
    static LayoutStyle_FromOrdinal(ordinal: int32): LayoutStyle {
        return ordinal as LayoutStyle
    }
    static SelectedMode_ToOrdinal(value: SelectedMode): int32 {
        return value as int32
    }
    static SelectedMode_FromOrdinal(ordinal: int32): SelectedMode {
        return ordinal as SelectedMode
    }
    static LayoutMode_ToOrdinal(value: LayoutMode): int32 {
        return value as int32
    }
    static LayoutMode_FromOrdinal(ordinal: int32): LayoutMode {
        return ordinal as LayoutMode
    }
    static TextSpanType_ToOrdinal(value: TextSpanType): int32 {
        return value as int32
    }
    static TextSpanType_FromOrdinal(ordinal: int32): TextSpanType {
        return ordinal as TextSpanType
    }
    static TextResponseType_ToOrdinal(value: TextResponseType): int32 {
        return value as int32
    }
    static TextResponseType_FromOrdinal(ordinal: int32): TextResponseType {
        return ordinal as TextResponseType
    }
    static TextAreaType_ToOrdinal(value: TextAreaType): int32 {
        return value as int32
    }
    static TextAreaType_FromOrdinal(ordinal: int32): TextAreaType {
        return ordinal as TextAreaType
    }
    static ContentType_ToOrdinal(value: ContentType): int32 {
        return value as int32
    }
    static ContentType_FromOrdinal(ordinal: int32): ContentType {
        return ordinal as ContentType
    }
    static TextDataDetectorType_ToOrdinal(value: TextDataDetectorType): int32 {
        return value as int32
    }
    static TextDataDetectorType_FromOrdinal(ordinal: int32): TextDataDetectorType {
        return ordinal as TextDataDetectorType
    }
    static TextDeleteDirection_ToOrdinal(value: TextDeleteDirection): int32 {
        return value as int32
    }
    static TextDeleteDirection_FromOrdinal(ordinal: int32): TextDeleteDirection {
        return ordinal as TextDeleteDirection
    }
    static MenuType_ToOrdinal(value: MenuType): int32 {
        return value as int32
    }
    static MenuType_FromOrdinal(ordinal: int32): MenuType {
        return ordinal as MenuType
    }
    static InputType_ToOrdinal(value: InputType): int32 {
        return value as int32
    }
    static InputType_FromOrdinal(ordinal: int32): InputType {
        return ordinal as InputType
    }
    static EnterKeyType_ToOrdinal(value: EnterKeyType): int32 {
        return value as int32
    }
    static EnterKeyType_FromOrdinal(ordinal: int32): EnterKeyType {
        return ordinal as EnterKeyType
    }
    static TextInputStyle_ToOrdinal(value: TextInputStyle): int32 {
        return value as int32
    }
    static TextInputStyle_FromOrdinal(ordinal: int32): TextInputStyle {
        return ordinal as TextInputStyle
    }
    static TimePickerFormat_ToOrdinal(value: TimePickerFormat): int32 {
        return value as int32
    }
    static TimePickerFormat_FromOrdinal(ordinal: int32): TimePickerFormat {
        return ordinal as TimePickerFormat
    }
    static ToggleType_ToOrdinal(value: ToggleType): int32 {
        return value as int32
    }
    static ToggleType_FromOrdinal(ordinal: int32): ToggleType {
        return ordinal as ToggleType
    }
    static SeekMode_ToOrdinal(value: SeekMode): int32 {
        return value as int32
    }
    static SeekMode_FromOrdinal(ordinal: int32): SeekMode {
        return ordinal as SeekMode
    }
    static PlaybackSpeed_ToOrdinal(value: PlaybackSpeed): int32 {
        return value as int32
    }
    static PlaybackSpeed_FromOrdinal(ordinal: int32): PlaybackSpeed {
        return ordinal as PlaybackSpeed
    }
    static MessageLevel_ToOrdinal(value: MessageLevel): int32 {
        return value as int32
    }
    static MessageLevel_FromOrdinal(ordinal: int32): MessageLevel {
        return ordinal as MessageLevel
    }
    static MixedMode_ToOrdinal(value: MixedMode): int32 {
        return value as int32
    }
    static MixedMode_FromOrdinal(ordinal: int32): MixedMode {
        return ordinal as MixedMode
    }
    static HitTestType_ToOrdinal(value: HitTestType): int32 {
        return value as int32
    }
    static HitTestType_FromOrdinal(ordinal: int32): HitTestType {
        return ordinal as HitTestType
    }
    static CacheMode_ToOrdinal(value: CacheMode): int32 {
        return value as int32
    }
    static CacheMode_FromOrdinal(ordinal: int32): CacheMode {
        return ordinal as CacheMode
    }
    static OverScrollMode_ToOrdinal(value: OverScrollMode): int32 {
        return value as int32
    }
    static OverScrollMode_FromOrdinal(ordinal: int32): OverScrollMode {
        return ordinal as OverScrollMode
    }
    static WebDarkMode_ToOrdinal(value: WebDarkMode): int32 {
        return value as int32
    }
    static WebDarkMode_FromOrdinal(ordinal: int32): WebDarkMode {
        return ordinal as WebDarkMode
    }
    static WebCaptureMode_ToOrdinal(value: WebCaptureMode): int32 {
        return value as int32
    }
    static WebCaptureMode_FromOrdinal(ordinal: int32): WebCaptureMode {
        return ordinal as WebCaptureMode
    }
    static ThreatType_ToOrdinal(value: ThreatType): int32 {
        return value as int32
    }
    static ThreatType_FromOrdinal(ordinal: int32): ThreatType {
        return ordinal as ThreatType
    }
    static RenderExitReason_ToOrdinal(value: RenderExitReason): int32 {
        return value as int32
    }
    static RenderExitReason_FromOrdinal(ordinal: int32): RenderExitReason {
        return ordinal as RenderExitReason
    }
    static SslError_ToOrdinal(value: SslError): int32 {
        return value as int32
    }
    static SslError_FromOrdinal(ordinal: int32): SslError {
        return ordinal as SslError
    }
    static FileSelectorMode_ToOrdinal(value: FileSelectorMode): int32 {
        return value as int32
    }
    static FileSelectorMode_FromOrdinal(ordinal: int32): FileSelectorMode {
        return ordinal as FileSelectorMode
    }
    static WebLayoutMode_ToOrdinal(value: WebLayoutMode): int32 {
        return value as int32
    }
    static WebLayoutMode_FromOrdinal(ordinal: int32): WebLayoutMode {
        return ordinal as WebLayoutMode
    }
    static RenderProcessNotRespondingReason_ToOrdinal(value: RenderProcessNotRespondingReason): int32 {
        return value as int32
    }
    static RenderProcessNotRespondingReason_FromOrdinal(ordinal: int32): RenderProcessNotRespondingReason {
        return ordinal as RenderProcessNotRespondingReason
    }
    static ProtectedResourceType_ToOrdinal(value: ProtectedResourceType): int32 {
        return value as int32
    }
    static ProtectedResourceType_FromOrdinal(ordinal: int32): ProtectedResourceType {
        return ordinal as ProtectedResourceType
    }
    static ContextMenuSourceType_ToOrdinal(value: ContextMenuSourceType): int32 {
        return value as int32
    }
    static ContextMenuSourceType_FromOrdinal(ordinal: int32): ContextMenuSourceType {
        return ordinal as ContextMenuSourceType
    }
    static ContextMenuMediaType_ToOrdinal(value: ContextMenuMediaType): int32 {
        return value as int32
    }
    static ContextMenuMediaType_FromOrdinal(ordinal: int32): ContextMenuMediaType {
        return ordinal as ContextMenuMediaType
    }
    static ContextMenuInputFieldType_ToOrdinal(value: ContextMenuInputFieldType): int32 {
        return value as int32
    }
    static ContextMenuInputFieldType_FromOrdinal(ordinal: int32): ContextMenuInputFieldType {
        return ordinal as ContextMenuInputFieldType
    }
    static NativeEmbedStatus_ToOrdinal(value: NativeEmbedStatus): int32 {
        return value as int32
    }
    static NativeEmbedStatus_FromOrdinal(ordinal: int32): NativeEmbedStatus {
        return ordinal as NativeEmbedStatus
    }
    static ContextMenuEditStateFlags_ToOrdinal(value: ContextMenuEditStateFlags): int32 {
        return value as int32
    }
    static ContextMenuEditStateFlags_FromOrdinal(ordinal: int32): ContextMenuEditStateFlags {
        return ordinal as ContextMenuEditStateFlags
    }
    static WebNavigationType_ToOrdinal(value: WebNavigationType): int32 {
        return value as int32
    }
    static WebNavigationType_FromOrdinal(ordinal: int32): WebNavigationType {
        return ordinal as WebNavigationType
    }
    static RenderMode_ToOrdinal(value: RenderMode): int32 {
        return value as int32
    }
    static RenderMode_FromOrdinal(ordinal: int32): RenderMode {
        return ordinal as RenderMode
    }
    static ViewportFit_ToOrdinal(value: ViewportFit): int32 {
        return value as int32
    }
    static ViewportFit_FromOrdinal(ordinal: int32): ViewportFit {
        return ordinal as ViewportFit
    }
    static WebKeyboardAvoidMode_ToOrdinal(value: WebKeyboardAvoidMode): int32 {
        return value as int32
    }
    static WebKeyboardAvoidMode_FromOrdinal(ordinal: int32): WebKeyboardAvoidMode {
        return ordinal as WebKeyboardAvoidMode
    }
    static WebElementType_ToOrdinal(value: WebElementType): int32 {
        return value as int32
    }
    static WebElementType_FromOrdinal(ordinal: int32): WebElementType {
        return ordinal as WebElementType
    }
    static WebResponseType_ToOrdinal(value: WebResponseType): int32 {
        return value as int32
    }
    static WebResponseType_FromOrdinal(ordinal: int32): WebResponseType {
        return ordinal as WebResponseType
    }
    static SideBarContainerType_ToOrdinal(value: SideBarContainerType): int32 {
        return value as int32
    }
    static SideBarContainerType_FromOrdinal(ordinal: int32): SideBarContainerType {
        return ordinal as SideBarContainerType
    }
    static SideBarPosition_ToOrdinal(value: SideBarPosition): int32 {
        return value as int32
    }
    static SideBarPosition_FromOrdinal(ordinal: int32): SideBarPosition {
        return ordinal as SideBarPosition
    }
    static WaterFlowLayoutMode_ToOrdinal(value: WaterFlowLayoutMode): int32 {
        return value as int32
    }
    static WaterFlowLayoutMode_FromOrdinal(ordinal: int32): WaterFlowLayoutMode {
        return ordinal as WaterFlowLayoutMode
    }
    static DpiFollowStrategy_ToOrdinal(value: DpiFollowStrategy): int32 {
        return value as int32
    }
    static DpiFollowStrategy_FromOrdinal(ordinal: int32): DpiFollowStrategy {
        return ordinal as DpiFollowStrategy
    }
    static StyledStringKey_ToOrdinal(value: StyledStringKey): int32 {
        return value as int32
    }
    static StyledStringKey_FromOrdinal(ordinal: int32): StyledStringKey {
        return ordinal as StyledStringKey
    }
    static isArray_String(value: object|string|number|undefined|null): boolean {
        return Array.isArray(value)
    }
    static isArray_PixelMap(value: object|string|number|undefined|null): boolean {
        return Array.isArray(value)
    }
    static isArray_WebHeader(value: object|string|number|undefined|null): boolean {
        return Array.isArray(value)
    }
    static isArray_Union_Number_String(value: object|string|number|undefined|null): boolean {
        return Array.isArray(value)
    }
    static isArray_SheetInfo(value: object|string|number|undefined|null): boolean {
        return Array.isArray(value)
    }
    static isArray_AlertDialogButtonOptions(value: object|string|number|undefined|null): boolean {
        return Array.isArray(value)
    }
    static isArray_CalendarDay(value: object|string|number|undefined|null): boolean {
        return Array.isArray(value)
    }
    static isArray_Number(value: object|string|number|undefined|null): boolean {
        return Array.isArray(value)
    }
    static isArray_CustomObject(value: object|string|number|undefined|null): boolean {
        return Array.isArray(value)
    }
    static isArray_TouchObject(value: object|string|number|undefined|null): boolean {
        return Array.isArray(value)
    }
    static isArray_HistoricalPoint(value: object|string|number|undefined|null): boolean {
        return Array.isArray(value)
    }
    static isArray_GestureRecognizer(value: object|string|number|undefined|null): boolean {
        return Array.isArray(value)
    }
    static isArray_DragPreviewMode(value: object|string|number|undefined|null): boolean {
        return Array.isArray(value)
    }
    static isArray_TouchTestInfo(value: object|string|number|undefined|null): boolean {
        return Array.isArray(value)
    }
    static isArray_Tuple_ResourceColor_Number(value: object|string|number|undefined|null): boolean {
        return Array.isArray(value)
    }
    static isArray_Rectangle(value: object|string|number|undefined|null): boolean {
        return Array.isArray(value)
    }
    static isArray_UniformDataType(value: object|string|number|undefined|null): boolean {
        return Array.isArray(value)
    }
    static isArray_ObscuredReasons(value: object|string|number|undefined|null): boolean {
        return Array.isArray(value)
    }
    static isArray_SafeAreaType(value: object|string|number|undefined|null): boolean {
        return Array.isArray(value)
    }
    static isArray_SafeAreaEdge(value: object|string|number|undefined|null): boolean {
        return Array.isArray(value)
    }
    static isArray_MenuElement(value: object|string|number|undefined|null): boolean {
        return Array.isArray(value)
    }
    static isArray_ModifierKey(value: object|string|number|undefined|null): boolean {
        return Array.isArray(value)
    }
    static isArray_Length(value: object|string|number|undefined|null): boolean {
        return Array.isArray(value)
    }
    static isArray_FractionStop(value: object|string|number|undefined|null): boolean {
        return Array.isArray(value)
    }
    static isArray_LayoutChild(value: object|string|number|undefined|null): boolean {
        return Array.isArray(value)
    }
    static isArray_Layoutable(value: object|string|number|undefined|null): boolean {
        return Array.isArray(value)
    }
    static isArray_Measurable(value: object|string|number|undefined|null): boolean {
        return Array.isArray(value)
    }
    static isArray_ColorStop(value: object|string|number|undefined|null): boolean {
        return Array.isArray(value)
    }
    static isArray_Union_ResourceColor_LinearGradient(value: object|string|number|undefined|null): boolean {
        return Array.isArray(value)
    }
    static isArray_Tuple_Union_ResourceColor_LinearGradient_Number(value: object|string|number|undefined|null): boolean {
        return Array.isArray(value)
    }
    static isArray_FingerInfo(value: object|string|number|undefined|null): boolean {
        return Array.isArray(value)
    }
    static isArray_SourceTool(value: object|string|number|undefined|null): boolean {
        return Array.isArray(value)
    }
    static isArray_GestureType(value: object|string|number|undefined|null): boolean {
        return Array.isArray(value)
    }
    static isArray_ImageFrameInfo(value: object|string|number|undefined|null): boolean {
        return Array.isArray(value)
    }
    static isArray_ImageAnalyzerType(value: object|string|number|undefined|null): boolean {
        return Array.isArray(value)
    }
    static isArray_NavigationMenuItem(value: object|string|number|undefined|null): boolean {
        return Array.isArray(value)
    }
    static isArray_ToolbarItem(value: object|string|number|undefined|null): boolean {
        return Array.isArray(value)
    }
    static isArray_LayoutSafeAreaType(value: object|string|number|undefined|null): boolean {
        return Array.isArray(value)
    }
    static isArray_LayoutSafeAreaEdge(value: object|string|number|undefined|null): boolean {
        return Array.isArray(value)
    }
    static isArray_Point(value: object|string|number|undefined|null): boolean {
        return Array.isArray(value)
    }
    static isArray_GuideLineStyle(value: object|string|number|undefined|null): boolean {
        return Array.isArray(value)
    }
    static isArray_BarrierStyle(value: object|string|number|undefined|null): boolean {
        return Array.isArray(value)
    }
    static isArray_LocalizedBarrierStyle(value: object|string|number|undefined|null): boolean {
        return Array.isArray(value)
    }
    static isArray_ShadowOptions(value: object|string|number|undefined|null): boolean {
        return Array.isArray(value)
    }
    static isArray_ResourceColor(value: object|string|number|undefined|null): boolean {
        return Array.isArray(value)
    }
    static isArray_Union_RichEditorTextSpanResult_RichEditorImageSpanResult(value: object|string|number|undefined|null): boolean {
        return Array.isArray(value)
    }
    static isArray_RichEditorTextSpanResult(value: object|string|number|undefined|null): boolean {
        return Array.isArray(value)
    }
    static isArray_RichEditorImageSpanResult(value: object|string|number|undefined|null): boolean {
        return Array.isArray(value)
    }
    static isArray_Union_RichEditorImageSpanResult_RichEditorTextSpanResult(value: object|string|number|undefined|null): boolean {
        return Array.isArray(value)
    }
    static isArray_RichEditorParagraphResult(value: object|string|number|undefined|null): boolean {
        return Array.isArray(value)
    }
    static isArray_RichEditorSpan(value: object|string|number|undefined|null): boolean {
        return Array.isArray(value)
    }
    static isArray_SelectOption(value: object|string|number|undefined|null): boolean {
        return Array.isArray(value)
    }
    static isArray_TextDataDetectorType(value: object|string|number|undefined|null): boolean {
        return Array.isArray(value)
    }
    static isArray_TextBox(value: object|string|number|undefined|null): boolean {
        return Array.isArray(value)
    }
    static isArray_TextMenuItem(value: object|string|number|undefined|null): boolean {
        return Array.isArray(value)
    }
    static isArray_TextCascadePickerRangeContent(value: object|string|number|undefined|null): boolean {
        return Array.isArray(value)
    }
    static isArray_Array_String(value: object|string|number|undefined|null): boolean {
        return Array.isArray(value)
    }
    static isArray_TextPickerRangeContent(value: object|string|number|undefined|null): boolean {
        return Array.isArray(value)
    }
    static isArray_Header(value: object|string|number|undefined|null): boolean {
        return Array.isArray(value)
    }
    static isArray_Buffer(value: object|string|number|undefined|null): boolean {
        return Array.isArray(value)
    }
    static isArray_ScriptItem(value: object|string|number|undefined|null): boolean {
        return Array.isArray(value)
    }
    static isArray_ExpandedMenuItemOptions(value: object|string|number|undefined|null): boolean {
        return Array.isArray(value)
    }
    static isArray_SectionOptions(value: object|string|number|undefined|null): boolean {
        return Array.isArray(value)
    }
    static isArray_StyleOptions(value: object|string|number|undefined|null): boolean {
        return Array.isArray(value)
    }
    static isArray_SpanStyle(value: object|string|number|undefined|null): boolean {
        return Array.isArray(value)
    }
}
