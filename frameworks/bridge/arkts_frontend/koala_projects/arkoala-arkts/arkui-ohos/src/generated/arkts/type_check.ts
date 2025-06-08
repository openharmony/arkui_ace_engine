import { KBoolean, KStringPtr, NativeBuffer, MaterializedBase } from "@koalaui/interop"
import { int32 } from "@koalaui/common"
import { BusinessError } from "./../ArkBaseInterfaces"
import { DoubleAnimationParam, Callback_Extender_OnProgress, Callback_Extender_OnFinish } from "./../ArkAnimationExtenderInterfaces"
import { Curve, FontStyle, FontWeight, TextAlign, TextOverflow, TextCase, WordBreak, HitTestMode, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Color, Visibility, ItemAlign, Direction, GradientDirection, ObscuredReasons, RenderFit, ImageRepeat, Axis, ResponseType, FunctionKey, ModifierKey, DialogButtonStyle, AnimationStatus, FillMode, PlayMode, TextHeightAdaptivePolicy, CheckBoxShape, LineCapStyle, LineJoinStyle, HorizontalAlign, FlexAlign, TextDecorationType, TextDecorationStyle, SharedTransitionEffectType, VerticalAlign, TransitionType, MouseButton, MouseAction, AccessibilityHoverType, TouchType, KeyType, KeySource, Placement, ArrowPointPosition, ClickEffectLevel, NestedScrollMode, PixelRoundCalcPolicy, BarState, EdgeEffect, IlluminatedType, ImageFit, Edge, Week, RelateType, FlexDirection, FlexWrap, CopyOptions, TitleHeight, ImageSpanAlignment, TextContentStyle, XComponentType, ScrollSource, LineBreakStrategy, EllipsisMode, OptionWidthMode, FoldStatus, AppRotation, EmbeddedType, MarqueeUpdateStrategy, TextSelectableMode, WidthBreakpoint, HeightBreakpoint } from "./../../component/enums"
import { ICurve, AnimateParam, TranslateOptions, UIContext, ClickEvent, CommonMethod, DrawModifier, Rectangle, Callback_Array_TouchTestInfo_TouchResult, TouchTestInfo, TouchResult, PixelRoundPolicy, BackgroundEffectOptions, ForegroundEffectOptions, VisualEffect, Filter, BorderImageOption, OutlineStyle, Callback_ClickEvent_Void, Callback_Boolean_HoverEvent_Void, HoverEvent, AccessibilityCallback, Callback_MouseEvent_Void, MouseEvent, Callback_TouchEvent_Void, TouchEvent, Callback_KeyEvent_Void, KeyEvent, Callback_KeyEvent_Boolean, TransitionOptions, TransitionEffect, MotionBlurOptions, InvertOptions, ScaleOptions, RotateOptions, Callback_Area_Area_Void, Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs, Literal_Number_offset_span, AlignRuleOption, LocalizedAlignRuleOptions, ClickEffect, Callback_DragEvent_String_Union_CustomBuilder_DragItemInfo, DragEvent, CustomBuilder, DragItemInfo, Callback_DragEvent_String_Void, UniformDataType, Callback_PreDragStatus_Void, PreDragStatus, Type_CommonMethod_linearGradient_value, Tuple_ResourceColor_Number, Type_CommonMethod_sweepGradient_value, Tuple_Length_Length, Type_CommonMethod_radialGradient_value, MotionPathOptions, ShadowOptions, ShadowStyle, ProgressMask, StateStyles, PixelStretchEffectOptions, GestureModifier, BackgroundBrightnessOptions, Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, Callback_TouchEvent_HitTestMode, SizeChangeCallback, SafeAreaType, SafeAreaEdge, Literal_Alignment_align, BlurStyle, BackgroundBlurStyleOptions, ForegroundBlurStyleOptions, TransitionFinishCallback, BlurOptions, LinearGradientBlurOptions, EffectType, sharedTransitionOptions, ChainStyle, DragPreviewOptions, DragInteractionOptions, ComponentContent, OverlayOptions, BlendMode, BlendApplyType, Blender, GeometryTransitionOptions, PopupOptions, CustomPopupOptions, MenuElement, MenuOptions, ContextMenuOptions, ModalTransition, ContentCoverOptions, SheetOptions, VisibleAreaChangeCallback, DismissReason, HoverModeAreaType, CommonConfiguration, ContentModifier, PickerTextStyle, PickerDialogButtonStyle, CommonShapeMethod, PointLightStyle, ComponentOptions, InputCounterOptions, TextDecorationOptions, ProvideOptions, AnimatableArithmetic, Context, Configuration, ExpectedFrameRateRange, FinishCallbackType, TouchTestStrategy, TransitionHierarchyStrategy, Literal_String_anchor_HorizontalAlign_align, Literal_String_anchor_VerticalAlign_align, LocalizedHorizontalAlignParam, LocalizedVerticalAlignParam, TransitionEdge, Literal_TransitionEffect_appear_disappear, TransitionEffects, DrawContext, PreviewParams, ItemDragInfo, EventTarget, SourceType, SourceTool, RepeatMode, BlurStyleActivePolicy, ThemeColorMode, AdaptiveColor, BlurStyleOptions, Tuple_Number_Number, ShadowType, MultiShadowOptions, LayoutSafeAreaType, LayoutSafeAreaEdge, SheetSize, BaseEvent, LinearGradient_common, AccessibilityHoverEvent, TouchObject, HistoricalPoint, PixelMapMock, DragBehavior, Summary, DragResult, IntentionCode, BindOptions, DismissContentCoverAction, Callback_DismissContentCoverAction_Void, SheetTitleOptions, SheetType, SheetMode, ScrollSizeMode, SheetKeyboardAvoidMode, SheetDismiss, DismissSheetAction, SpringBackAction, Type_SheetOptions_detents, Callback_SheetDismiss_Void, Callback_DismissSheetAction_Void, Callback_SpringBackAction_Void, Callback_SheetType_Void, PopupMessageOptions, DismissPopupAction, Literal_String_value_Callback_Void_action, Literal_Boolean_isVisible, Literal_ResourceColor_color, Callback_Literal_Boolean_isVisible_Void, Callback_DismissPopupAction_Void, MenuPreviewMode, ContextMenuAnimationOptions, RectResult, FadingEdgeOptions, NestedScrollOptions, SymbolGlyphModifier, DragPreviewMode, MenuPolicy, ImageModifier, CommonAttribute, OverlayOffset, FractionStop, MotionBlurAnchor, LayoutBorderInfo, LayoutInfo, LayoutChild, GeometryInfo, SizeResult, Layoutable, Measurable, MeasureResult, NavDestinationInfo, NavigationInfo, RouterPageInfo, Theme, Literal_Empty, View, CaretOffset, TextContentControllerBase, ContentClipMode, ScrollableCommonMethod, EdgeEffectOptions, ScrollResult, OnWillScrollCallback, DynamicNode, OnMoveHandler, ChildrenMainSize, LightSource, KeyframeAnimateParam, KeyframeState, Callback, VisibleAreaEventOptions, UICommonEvent, HoverCallback, UIGestureEvent, SelectionOptions, KeyboardAvoidMode } from "./../../component/common"
import { AnimationExtender } from "./../ArkAnimationExtenderMaterialized"
import { PointerStyle, Callback_RangeUpdate } from "./../ArkArkuiCustomInterfaces"
import { UnifiedData } from "./../ArkUnifiedDataMaterialized"
import { LazyForEachOps } from "./../ArkLazyForEachOpsMaterialized"
import { SystemOps } from "./../ArkSystemOpsMaterialized"
import { FocusController } from "./../ArkFocusControllerMaterialized"
import { DrawingCanvas } from "./../ArkDrawingCanvasMaterialized"
import { PixelMap } from "./../ArkPixelMapMaterialized"
import { NodeController, TextModifier, RectWidthStyle, RectHeightStyle, Want, WebHeader, SnapshotOptions, PerfMonitorActionType, PerfMonitorSourceType, ShapeSize, RectShapeOptions, RoundRectShapeOptions, PathShapeOptions, EffectDirection, EffectScope, SymbolEffect, ErrorCallback } from "./../ArkArkuiExternalInterfaces"
import { FontOptions, FontInfo } from "@ohos.font.font"
import { MeasureOptions } from "@ohos.measure"
import { LengthMetrics, LengthUnit, LengthMetricsUnit } from "../../Graphics"
import { Resource } from "global/resource";
import { ColorMetrics } from "./../ArkColorMetricsMaterialized"
import { ResourceColor, Position, Length, SizeOptions, ConstraintSizeOptions, ChainWeightOptions, Padding, LocalizedPadding, Margin, LocalizedMargin, BorderOptions, EdgeStyles, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, Dimension, EdgeOutlineWidths, OutlineRadiuses, Area, Edges, LocalizedEdges, LocalizedPosition, ResourceStr, AccessibilityOptions, VoidCallback, Offset, Font, MarkStyle, Bias, EdgeWidth, DirectionalEdgesT, ColorFilter, LengthConstrain, DividerStyleOptions, VP, PX, LPX, TouchPoint } from "./../../component/units"
import { WebviewController } from "./../ArkWebviewControllerMaterialized"
import { GlobalScope_ohos_arkui_componentSnapshot } from "./../ArkGlobalScopeOhosArkuiComponentSnapshotMaterialized"
import { AsyncCallback_image_PixelMap_Void, AnimationRange_Number, onItemDragStart_event_type } from "./../SyntheticDeclarations"
import { GlobalScope_ohos_arkui_performanceMonitor } from "./../ArkGlobalScopeOhosArkuiPerformanceMonitorMaterialized"
import { CommonShape } from "./../ArkCommonShapeMaterialized"
import { BaseShape } from "./../ArkBaseShapeMaterialized"
import { RectShape } from "./../ArkRectShapeMaterialized"
import { CircleShape } from "./../ArkCircleShapeMaterialized"
import { EllipseShape } from "./../ArkEllipseShapeMaterialized"
import { PathShape } from "./../ArkPathShapeMaterialized"
import { GlobalScope_ohos_font } from "./../ArkGlobalScopeOhosFontMaterialized"
import { GlobalScope_ohos_measure_utils } from "./../ArkGlobalScopeOhosMeasureUtilsMaterialized"
import { ScaleSymbolEffect } from "./../ArkScaleSymbolEffectMaterialized"
import { ReplaceSymbolEffect } from "./../ArkReplaceSymbolEffectMaterialized"
import { FrameNode } from "../../FrameNode"
import { NavExtender } from "./../ArkNavExtenderMaterialized"
import { NavPathStack, NavPathInfo, NavigationMenuItem, SystemBarStyle, NavigationTitleOptions, ToolbarItem, NavigationToolbarOptions, NavigationCommonTitle, NavigationCustomTitle, NavigationMode, NavBarPosition, NavigationTitleMode, PopInfo, Callback_PopInfo_Void, LaunchMode, NavigationOptions, NavigationInterception, InterceptionShowCallback, InterceptionModeCallback, NavigationInterface, ToolbarItemStatus, NavigationOperation, BarStyle, Tuple_Dimension_Dimension, Callback_NavigationTitleMode_Void, Callback_NavigationMode_Void, Callback_String_Unknown_Void, Type_NavigationAttribute_customNavContentTransition_delegate, NavContentInfo, NavigationAnimatedTransition, Callback_NavigationTransitionProxy_Void, NavigationTransitionProxy } from "./../../component/navigation"
import { NavExtender_OnUpdateStack } from "./../ArkNavigationExtenderInterfaces"
import { Point } from "./../ArkPointInterfaces"
import { Root, ComponentRoot } from "./../ArkStaticComponentsInterfaces"
import { EventEmulator } from "./../ArkEventEmulatorMaterialized"
import { Literal_Want_want, AbilityComponentAttribute, Callback_Void } from "./../../component/abilityComponent"
import { ResizableOptions, DrawableDescriptor, DrawingColorFilter, ResolutionQuality, DrawingLattice, ImageRenderMode, ImageContent, DynamicRangeMode, ImageInterpolation, ImageSourceSize, Type_ImageAttribute_onComplete_callback_event, ImageAttribute, Callback_Type_ImageAttribute_onComplete_callback_event_Void, ImageErrorCallback, ImageError } from "./../../component/image"
import { FocusBoxStyle, FocusPriority } from "./../../component/focus"
import {  CustomComponent, IPropertySubscriber, ISinglePropertyChangeSubscriber, SubscribaleAbstract, NavigationAttribute, CommonTransition, PageTransitionEnterInterface, PageTransitionExitInterface } from "./../../handwritten"
import { GestureInfo, BaseGestureEvent, GestureJudgeResult, GestureType, GestureMask, GestureHandler, GesturePriority, PanDirection, SwipeDirection, GestureMode, GestureControl, FingerInfo, TapGestureEvent, LongPressGestureEvent, PanGestureEvent, PinchGestureEvent, RotationGestureEvent, SwipeGestureEvent, GestureEvent, GestureInterface, TapGestureParameters, TapGestureInterface, Callback_GestureEvent_Void, Literal_Number_duration_fingers_Boolean_repeat, LongPressGestureInterface, Literal_Number_distance_fingers_PanDirection_direction, PanGestureOptions, PanGestureInterface, Literal_Number_fingers_speed_SwipeDirection_direction, SwipeGestureInterface, Literal_Number_distance_fingers, PinchGestureInterface, Literal_Number_angle_fingers, RotationGestureInterface, GestureGroupInterface, TapGestureHandlerOptions, TapGestureHandler, LongPressGestureHandlerOptions, LongPressGestureHandler, PanGestureHandlerOptions, PanGestureHandler, SwipeGestureHandlerOptions, SwipeGestureHandler, PinchGestureHandlerOptions, PinchGestureHandler, RotationGestureHandlerOptions, RotationGestureHandler, GestureGroupGestureHandlerOptions, GestureRecognizerState, ScrollableTargetInfo, EventTargetInfo, GestureRecognizer, PanRecognizer } from "./../../component/gesture"
import { SheetInfo, DismissDialogAction, ActionSheetButtonOptions, ActionSheetOffset, ActionSheetOptions, Callback_DismissDialogAction_Void, ActionSheet } from "./../../component/actionSheet"
import { DialogAlignment, DialogButtonDirection, AlertDialogButtonBaseOptions, AlertDialogButtonOptions, TextStyle_alert_dialog, AlertDialogParam, AlertDialogParamWithConfirm, AlertDialogParamWithButtons, AlertDialogParamWithOptions, AlertDialog } from "./../../component/alertDialog"
import { IndexerAlign, AlphabetIndexerOptions, AlphabetIndexerAttribute, Callback_Number_Void, OnAlphabetIndexerSelectCallback, OnAlphabetIndexerRequestPopupDataCallback, OnAlphabetIndexerPopupSelectCallback } from "./../../component/alphabetIndexer"
import { SpringProp, SpringMotion, FrictionMotion, ScrollMotion, AnimatorAttribute } from "./../../component/animator"
import { BadgePosition, BadgeStyle, BadgeParam, BadgeParamWithNumber, BadgeParamWithString, BadgeAttribute } from "./../../component/badge"
import { BlankAttribute } from "./../../component/blank"
import { ButtonType, ButtonStyleMode, ButtonRole, ButtonConfiguration, ButtonTriggerClickCallback, ControlSize, ButtonOptions, LabelStyle, ButtonAttribute } from "./../../component/button"
import { CalendarDay, MonthData, CurrentDayStyle, NonCurrentDayStyle, TodayStyle, WeekStyle, WorkStateStyle, CalendarSelectedDate, CalendarRequestedData, Literal_Number_day_month_year, CalendarController, Type_CalendarInterface_value, CalendarAttribute, Callback_CalendarSelectedDate_Void, Callback_CalendarRequestedData_Void } from "./../../component/calendar"
import { CalendarAlign, CalendarOptions, CalendarPickerAttribute, Callback_Date_Void, CalendarDialogOptions, CalendarPickerDialog } from "./../../component/calendarPicker"
import { CanvasGradient, CanvasPath, Path2D, CanvasPattern, TextMetrics, ImageBitmap, ImageData, RenderingContextSettings, CanvasRenderer, ImageSmoothingQuality, CanvasLineCap, CanvasLineJoin, CanvasDirection, CanvasTextAlign, CanvasTextBaseline, CanvasFillRule, CanvasRenderingContext2D, OffscreenCanvasRenderingContext2D, OffscreenCanvas, Size, DrawingRenderingContext, CanvasAttribute } from "./../../component/canvas"
import { Matrix2D } from "./../../component/matrix2d"
import { ImageAnalyzerConfig, ImageAnalyzerType, ImageAnalyzerController, ImageAIOptions } from "./../../component/imageCommon"
import { CheckboxOptions, CheckBoxConfiguration, Callback_Boolean_Void, CheckboxAttribute, OnCheckboxChangeCallback } from "./../../component/checkbox"
import { SelectStatus, CheckboxGroupOptions, CheckboxGroupResult, CheckboxGroupAttribute, OnCheckboxGroupChangeCallback } from "./../../component/checkboxgroup"
import { CircleOptions, CircleAttribute } from "./../../component/circle"
import { ColumnOptions, ColumnAttribute } from "./../../component/column"
import { ColumnSplitDividerStyle, ColumnSplitAttribute } from "./../../component/columnSplit"
import { Callback_Number_Number_Void, GridLayoutOptions, Callback_Number_Tuple_Number_Number, Callback_Number_Tuple_Number_Number_Number_Number, Tuple_Number_Number_Number_Number, GridDirection, GridItemAlignment, ComputedBarAttribute, Literal_Number_offsetRemain, GridAttribute, Callback_Number_Number_ComputedBarAttribute, Callback_ItemDragInfo_Void, Callback_ItemDragInfo_Number_Number_Void, Callback_ItemDragInfo_Number_Void, Callback_ItemDragInfo_Number_Number_Boolean_Void, Callback_Number_ScrollState_Literal_Number_offsetRemain } from "./../../component/grid"
import { ScrollOnWillScrollCallback, ScrollOnScrollCallback, Scroller, ScrollOptions, ScrollEdgeOptions, ScrollPageOptions, Literal_Boolean_next_Axis_direction, OffsetResult, ScrollAlign, ScrollToIndexOptions, ScrollDirection, ScrollAnimationOptions, OffsetOptions, ScrollSnapOptions, OnScrollFrameBeginHandlerResult, ScrollAttribute, OnScrollEdgeCallback, OnScrollFrameBeginCallback } from "./../../component/scroll"
import { EnvPropsOptions, Literal_String_key_Any_defaultValue, PersistPropsOptions } from "./../../component/commonTsEtsApi"
import { Scene, ModelType, SceneOptions, Component3DAttribute } from "./../../component/component3d"
import { ContainerSpanAttribute } from "./../../component/containerSpan"
import { TextBackgroundStyle, BaseSpan, SpanAttribute } from "./../../component/span"
import { Content, ContentSlotAttribute, ContentSlotInterface } from "./../../component/contentSlot"
import { ContextMenu } from "./../../component/contextMenu"
import { CounterAttribute } from "./../../component/counter"
import { CustomDialogControllerOptions, CustomDialogController } from "./../../component/customDialogController"
import { DataPanelType, ColorStop, LinearGradient, DataPanelShadowOptions, DataPanelOptions, DataPanelConfiguration, DataPanelAttribute } from "./../../component/dataPanel"
import { DatePickerResult, DatePickerOptions, DatePickerAttribute, Callback_DatePickerResult_Void, LunarSwitchStyle, DatePickerDialogOptions, DatePickerDialog } from "./../../component/datePicker"
import { DateTimeOptions, TimePickerResult, TimePickerFormat, TimePickerOptions, TimePickerAttribute, Callback_TimePickerResult_Void, TimePickerDialogOptions, TimePickerDialog } from "./../../component/timePicker"
import { DividerAttribute } from "./../../component/divider"
import { EffectComponentAttribute } from "./../../component/effectComponent"
import { EllipseOptions, EllipseAttribute } from "./../../component/ellipse"
import { TerminationInfo, EmbeddedComponentAttribute, Callback_TerminationInfo_Void } from "./../../component/embeddedComponent"
import { FlexOptions, FlexSpaceOptions, FlexAttribute } from "./../../component/flex"
import { FlowItemAttribute } from "./../../component/flowItem"
import { WindowStatusType, FolderStackOptions, OnFoldStatusChangeInfo, FolderStackAttribute, OnFoldStatusChangeCallback, OnHoverStatusChangeCallback, HoverEventParam } from "./../../component/folderStack"
import { FormDimension, FormRenderingMode, FormShape, FormInfo, FormCallbackInfo, Literal_Number_errcode_String_msg, FormComponentAttribute, Callback_FormCallbackInfo_Void, Callback_Literal_Number_errcode_String_msg_Void, Callback_Any_Void } from "./../../component/formComponent"
import { FormLinkOptions, FormLinkAttribute } from "./../../component/formLink"
import { GaugeOptions, GaugeShadowOptions, GaugeIndicatorOptions, GaugeConfiguration, GaugeAttribute, Tuple_Union_ResourceColor_LinearGradient_Number } from "./../../component/gauge"
import { ScrollState, ListItemAlign, ListItemGroupArea, StickyStyle, ChainEdgeEffect, ScrollSnapAlign, ChainAnimationOptions, CloseSwipeActionOptions, VisibleListContentInfo, ListScroller, ListOptions, ListDividerOptions, ListAttribute, Callback_Number_Number_Number_Void, OnScrollVisibleContentChangeCallback, Callback_Number_Boolean, Callback_Number_Number_Boolean } from "./../../component/list"
import { GridItemStyle, GridItemOptions, GridItemAttribute } from "./../../component/griditem"
import { GridColColumnOption, GridColOptions, GridColAttribute } from "./../../component/gridCol"
import { SizeType, GridContainerOptions, GridContainerAttribute } from "./../../component/gridContainer"
import { GridRowSizeOption, GridRowColumnOption, GutterOption, BreakpointsReference, GridRowDirection, BreakPoints, GridRowOptions, GridRowAttribute, Callback_String_Void } from "./../../component/gridRow"
import { HyperlinkAttribute } from "./../../component/hyperlink"
import { ImageFrameInfo, ImageAnimatorAttribute } from "./../../component/imageAnimator"
import { ImageSpanAttribute, ImageCompleteCallback, ImageLoadResult } from "./../../component/imageSpan"
import { DataOperationType, DataAddOperation, DataDeleteOperation, DataChangeOperation, MoveIndex, ExchangeIndex, ExchangeKey, DataMoveOperation, DataExchangeOperation, DataReloadOperation } from "./../../component/lazyForEach"
import { LineOptions, LineAttribute } from "./../../component/line"
import { Sticky, EditMode, SwipeEdgeEffect, SwipeActionState, SwipeActionItem, Callback_SwipeActionState_Void, SwipeActionOptions, ListItemStyle, ListItemOptions, ListItemAttribute } from "./../../component/listItem"
import { ListItemGroupStyle, ListItemGroupOptions, ListItemGroupAttribute } from "./../../component/listItemGroup"
import { LoadingProgressStyle, LoadingProgressAttribute, LoadingProgressConfiguration } from "./../../component/loadingProgress"
import { LocationIconStyle, LocationDescription, LocationButtonOptions, LocationButtonOnClickResult, LocationButtonAttribute, Callback_ClickEvent_LocationButtonOnClickResult_Void } from "./../../component/locationButton"
import { SecurityComponentMethod, SecurityComponentLayoutDirection } from "./../../component/securityComponent"
import { MarqueeOptions, MarqueeAttribute } from "./../../component/marquee"
import { ASTCResource, MediaCachedImageAttribute } from "./../../component/mediaCachedImage"
import { SubMenuExpandingMode, MenuAttribute } from "./../../component/menu"
import { MenuItemOptions, MenuItemAttribute } from "./../../component/menuItem"
import { MenuItemGroupOptions, MenuItemGroupAttribute } from "./../../component/menuItemGroup"
import { NavDestinationCommonTitle, NavDestinationCustomTitle, NavigationSystemTransitionType, NavDestinationMode, RouteMapConfig, NavDestinationContext, NavDestinationAttribute, Callback_Boolean, Callback_NavDestinationContext_Void } from "./../../component/navDestination"
import { RouteInfo, NavRouteMode, NavRouterAttribute } from "./../../component/navRouter"
import { NavigationType, Literal_String_target_NavigationType_type, NavigatorAttribute } from "./../../component/navigator"
import { NodeContainerAttribute } from "./../../component/nodeContainer"
import { RouteType, SlideEffect, PageTransitionOptions, PageTransitionCallback } from "./../../component/pageTransition"
import { PanelMode, PanelType, PanelHeight, PanelAttribute, Callback_Number_Number_PanelMode_Void, Callback_PanelMode_Void } from "./../../component/panel"
import { VelocityOptions, ParticleTuple, PointParticleParameters, ImageParticleParameters, ParticleConfigs, EmitterProperty, EmitterParticleOptions, ParticlePropertyUpdaterConfigs, ParticleUpdaterOptions, ParticleColorOptions, ParticleColorUpdaterOptions, ParticleColorPropertyUpdaterConfigs, ParticlePropertyAnimation, ParticleType, ParticleEmitterShape, DistributionType, ParticleUpdater, DisturbanceFieldShape } from "./../../component/particle"
import { PasteIconStyle, PasteDescription, PasteButtonOptions, PasteButtonOnClickResult, PasteButtonAttribute, Callback_ClickEvent_PasteButtonOnClickResult_Void } from "./../../component/pasteButton"
import { PathOptions, PathAttribute } from "./../../component/path"
import { PatternLockChallengeResult, CircleStyleOptions, PatternLockController, PatternLockAttribute, Callback_Array_Number_Void } from "./../../component/patternLock"
import { PluginComponentTemplate, PluginComponentOptions, PluginErrorData, PluginComponentAttribute, PluginErrorCallback } from "./../../component/pluginComponent"
import { PolygonOptions, PolygonAttribute } from "./../../component/polygon"
import { PolylineOptions, PolylineAttribute } from "./../../component/polyline"
import { ProgressOptions, ProgressStyle, ProgressType, ProgressStatus, ProgressStyleOptions, CommonProgressStyleOptions, ScanEffectOptions, EclipseStyleOptions, ScaleRingStyleOptions, RingStyleOptions, LinearStyleOptions, CapsuleStyleOptions, ProgressStyleMap, ProgressAttribute, ProgressConfiguration } from "./../../component/progress"
import { QRCodeAttribute } from "./../../component/qrcode"
import { RadioIndicatorType, RadioOptions, RadioStyle, RadioAttribute, RadioConfiguration } from "./../../component/radio"
import { RatingOptions, StarStyleOptions, RatingConfiguration, RatingAttribute } from "./../../component/rating"
import { RectOptions, RoundedRectOptions, RectAttribute } from "./../../component/rect"
import { RefreshStatus, RefreshOptions, RefreshAttribute, Callback_RefreshStatus_Void } from "./../../component/refresh"
import { GuideLinePosition, GuideLineStyle, BarrierDirection, LocalizedBarrierDirection, BarrierStyle, LocalizedBarrierStyle, RelativeContainerAttribute } from "./../../component/relativeContainer"
import { VirtualScrollOptions, TemplateOptions } from "./../../component/repeat"
import { RichEditorDeleteDirection, RichEditorSpanType, RichEditorResponseType, RichEditorSpanPosition, RichEditorTextStyle, LeadingMarginPlaceholder, RichEditorParagraphStyle, PasteEvent, RichEditorTextSpan, RichEditorLayoutStyle, RichEditorImageSpanStyle, RichEditorSymbolSpanStyle, RichEditorTextStyleResult, RichEditorParagraphResult, RichEditorSymbolSpanStyleResult, RichEditorTextSpanResult, RichEditorImageSpanStyleResult, RichEditorImageSpanResult, RichEditorImageSpan, RichEditorRange, RichEditorGesture, RichEditorTextSpanOptions, KeyboardOptions, RichEditorImageSpanOptions, RichEditorBuilderSpanOptions, PlaceholderStyle, RichEditorSpanStyleOptions, RichEditorParagraphStyleOptions, RichEditorUpdateTextSpanStyleOptions, RichEditorUpdateImageSpanStyleOptions, RichEditorUpdateSymbolSpanStyleOptions, RichEditorSymbolSpanOptions, RichEditorSelection, RichEditorInsertValue, RichEditorDeleteValue, RichEditorChangeValue, RichEditorOptions, RichEditorController, RichEditorStyledStringOptions, RichEditorStyledStringController, SelectionMenuOptions, MenuOnAppearCallback, RichEditorBaseController, RichEditorSpan, RichEditorAttribute, Callback_RichEditorSelection_Void, Callback_RichEditorRange_Void, Callback_RichEditorInsertValue_Boolean, Callback_RichEditorTextSpanResult_Void, Callback_TextRange_Void, Callback_RichEditorDeleteValue_Boolean, PasteEventCallback, SubmitCallback, Callback_RichEditorChangeValue_Boolean, Callback_CutEvent_Void, CutEvent, Callback_CopyEvent_Void, CopyEvent } from "./../../component/richEditor"
import { DecorationStyleInterface, StyledString, MutableStyledString, ImageAttachment, CustomSpan, StyleOptions, StyledStringKey, SpanStyle, StyledStringValue, TextStyle_styled_string, TextStyleInterface, DecorationStyle, BaselineOffsetStyle, LetterSpacingStyle, TextShadowStyle, BackgroundColorStyle, GestureStyle, GestureStyleInterface, ParagraphStyle, ParagraphStyleInterface, LineHeightStyle, UrlStyle, ImageAttachmentLayoutStyle, ImageAttachmentInterface, CustomSpanMetrics, CustomSpanDrawInfo, CustomSpanMeasureInfo, UserDataSpan } from "./../../component/styledString"
import { SymbolEffectStrategy, SymbolRenderingStrategy, EffectFillStyle, HierarchicalSymbolEffect, AppearSymbolEffect, DisappearSymbolEffect, BounceSymbolEffect, PulseSymbolEffect, SymbolGlyphAttribute } from "./../../component/symbolglyph"
import { DecorationStyleResult, TextRange, MenuType, TextEditControllerEx, TextBaseController, LayoutManager, PreviewText, StyledStringController, StyledStringChangedListener, TextDataDetectorConfig, OnDidChangeCallback, EditMenuOptions, CaretStyle, EditableTextOnChangeCallback, InsertValue, DeleteValue, FontSettingOptions, TextDataDetectorType, TextDeleteDirection, Callback_StyledStringChangeValue_Boolean, StyledStringChangeValue, PositionWithAffinity, LineMetrics, TextBox, Affinity, TextMenuItemId, TextMenuItem } from "./../../component/textCommon"
import { EnterKeyType, OnTextSelectionChangeCallback, OnContentScrollCallback, OnPasteCallback, InputType, UnderlineColor, SubmitEvent, TextInputController, TextInputOptions, TextInputStyle, PasswordIcon, TextInputAttribute, OnSubmitCallback } from "./../../component/textInput"
import { RichTextAttribute } from "./../../component/richText"
import { RootSceneSession, RootSceneAttribute } from "./../../component/rootScene"
import { RowOptions, RowAttribute } from "./../../component/row"
import { RowSplitAttribute } from "./../../component/rowSplit"
import { SaveIconStyle, SaveDescription, SaveButtonOptions, SaveButtonOnClickResult, SaveButtonAttribute, Callback_ClickEvent_SaveButtonOnClickResult_Void } from "./../../component/saveButton"
import { ScreenAttribute } from "./../../component/screen"
import { ScrollBarDirection, ScrollBarOptions, ScrollBarAttribute } from "./../../component/scrollBar"
import { SearchController, CancelButtonStyle, SearchType, SearchOptions, IconOptions, SearchButtonOptions, CancelButtonOptions, CancelButtonSymbolOptions, SearchAttribute, SearchSubmitCallback, Callback_InsertValue_Boolean, Callback_InsertValue_Void, Callback_DeleteValue_Boolean, Callback_DeleteValue_Void } from "./../../component/search"
import { SelectOption, ArrowPosition, MenuAlignType, SelectAttribute, Callback_Number_String_Void, MenuItemConfiguration, Callback_Union_Number_Resource_Void, Callback_ResourceStr_Void } from "./../../component/select"
import { DividerOptions, TextPickerRangeContent, TextCascadePickerRangeContent, TextPickerOptions, TextPickerAttribute, Callback_String_Number_Void, Type_TextPickerAttribute_onChange_callback, Callback_Union_Number_Array_Number_Void, Callback_Union_String_Array_String_Void, TextPickerResult, TextPickerDialogOptions, Callback_TextPickerResult_Void, TextPickerDialog } from "./../../component/textPicker"
import { ViewportRect, ShapeAttribute } from "./../../component/shape"
import { SliderStyle, SliderChangeMode, SliderInteraction, SlideRange, SliderOptions, SliderBlockType, SliderBlockStyle, SliderConfiguration, SliderTriggerChangeCallback, SliderAttribute, Callback_Number_SliderChangeMode_Void } from "./../../component/slider"
import { StackOptions, StackAttribute } from "./../../component/stack"
import { ColorMode, LayoutDirection } from "./../../component/stateManagement"
import { Literal_Number_index, StepperAttribute } from "./../../component/stepper"
import { ItemState, StepperItemAttribute } from "./../../component/stepperItem"
import { SwiperController, Indicator, DotIndicator, DigitIndicator, SwiperAutoFill, ArrowStyle, SwiperDisplayMode, IndicatorStyle, SwiperAnimationEvent, SwiperNestedScrollMode, SwiperAttribute, OnSwiperAnimationStartCallback, OnSwiperAnimationEndCallback, OnSwiperGestureSwipeCallback, SwiperContentAnimatedTransition, ContentDidScrollCallback, Callback_SwiperContentTransitionProxy_Void, SwiperContentTransitionProxy } from "./../../component/swiper"
import { IndicatorComponentController, IndicatorComponentAttribute } from "./../../component/indicatorcomponent"
import { SymbolSpanAttribute } from "./../../component/symbolSpan"
import { BarMode, AnimationMode, BarPosition, LayoutStyle, TabsController, TabsOptions, DividerStyle, TabsAnimationEvent, BarGridColumnOptions, ScrollableBarModeOptions, TabsAttribute, OnTabsAnimationStartCallback, OnTabsAnimationEndCallback, OnTabsGestureSwipeCallback, TabsCustomContentTransitionCallback, OnTabsContentWillChangeCallback, TabContentAnimatedTransition, Callback_TabContentTransitionProxy_Void, TabContentTransitionProxy } from "./../../component/tabs"
import { SelectedMode, LayoutMode, BoardStyle, TabBarIconStyle, TabBarSymbol, TabBarOptions, SubTabBarStyle, BottomTabBarStyle, TabContentAttribute } from "./../../component/tabContent"
import { TextOverflowOptions, TextAttribute, TextSpanType, TextResponseType, TextOptions, TextController } from "./../../component/text"
import { TextAreaController, TextAreaOptions, TextAreaType, ContentType, TextAreaAttribute, Callback_EnterKeyType_Void, TextAreaSubmitCallback, Callback_String_PasteEvent_Void } from "./../../component/textArea"
import { TextClockController, TextClockConfiguration, TextClockOptions, TextClockAttribute } from "./../../component/textClock"
import { TextTimerController, TextTimerConfiguration, TextTimerOptions, TextTimerAttribute } from "./../../component/textTimer"
import { ToggleType, SwitchStyle, ToggleConfiguration, ToggleOptions, ToggleAttribute } from "./../../component/toggle"
import { CustomTheme, WithThemeOptions, WithThemeAttribute } from "./../../component/withTheme"
import { SeekMode, PlaybackSpeed, FullscreenInfo, PreparedInfo, PlaybackInfo, VideoOptions, VideoController, VideoAttribute, Callback_FullscreenInfo_Void, Callback_PreparedInfo_Void, Callback_PlaybackInfo_Void } from "./../../component/video"
import { NativeMediaPlayerConfig, AdsBlockedDetails, WebKeyboardOptions, WebKeyboardController, WebKeyboardCallbackInfo, MessageLevel, MixedMode, HitTestType, CacheMode, OverScrollMode, WebDarkMode, WebCaptureMode, ThreatType, WebMediaOptions, ScreenCaptureConfig, FullScreenExitHandler, FullScreenEnterEvent, RenderExitReason, SslError, FileSelectorMode, WebLayoutMode, RenderProcessNotRespondingReason, FileSelectorParam, JsResult, FileSelectorResult, HttpAuthHandler, SslErrorHandler, ClientAuthenticationHandler, ProtectedResourceType, PermissionRequest, ScreenCaptureHandler, DataResubmissionHandler, ControllerHandler, ContextMenuSourceType, ContextMenuMediaType, ContextMenuInputFieldType, NativeEmbedStatus, ContextMenuEditStateFlags, WebNavigationType, RenderMode, ViewportFit, WebContextMenuParam, WebContextMenuResult, ConsoleMessage, WebResourceRequest, Header, WebResourceResponse, WebResourceError, JsGeolocation, WebCookie, EventResult, Literal_String_script_Callback_String_Void_callback_, Literal_String_baseUrl_data_encoding_historyUrl_mimeType, Literal_Union_String_Resource_url_Array_Header_headers, Literal_Object_object__String_name_Array_String_methodList, WebController, WebOptions, ScriptItem, LoadCommittedDetails, IntelligentTrackingPreventionDetails, NativeEmbedInfo, NativeEmbedDataInfo, NativeEmbedVisibilityInfo, NativeEmbedTouchInfo, FirstMeaningfulPaint, LargestContentfulPaint, RenderProcessNotRespondingData, OnPageEndEvent, OnPageBeginEvent, OnProgressChangeEvent, OnTitleReceiveEvent, OnGeolocationShowEvent, OnAlertEvent, OnBeforeUnloadEvent, OnConfirmEvent, OnPromptEvent, OnConsoleEvent, OnErrorReceiveEvent, OnHttpErrorReceiveEvent, OnDownloadStartEvent, OnRefreshAccessedHistoryEvent, OnRenderExitedEvent, OnShowFileSelectorEvent, OnResourceLoadEvent, OnScaleChangeEvent, OnHttpAuthRequestEvent, OnInterceptRequestEvent, OnPermissionRequestEvent, OnScreenCaptureRequestEvent, OnContextMenuShowEvent, OnSearchResultReceiveEvent, OnScrollEvent, OnSslErrorEventReceiveEvent, OnClientAuthenticationEvent, OnWindowNewEvent, OnTouchIconUrlReceivedEvent, OnFaviconReceivedEvent, OnPageVisibleEvent, OnDataResubmittedEvent, OnAudioStateChangedEvent, OnFirstContentfulPaintEvent, OnLoadInterceptEvent, OnOverScrollEvent, JavaScriptProxy, WebKeyboardAvoidMode, WebElementType, WebResponseType, SelectionMenuOptionsExt, Literal_Union_String_WebResourceRequest_data, Literal_Function_handler_Object_error, Literal_Object_detail, Literal_Function_callback__Object_fileSelector, WebAttribute, Callback_OnPageEndEvent_Void, Callback_OnPageBeginEvent_Void, Callback_OnProgressChangeEvent_Void, Callback_OnTitleReceiveEvent_Void, Callback_OnGeolocationShowEvent_Void, Callback_OnAlertEvent_Boolean, Callback_OnBeforeUnloadEvent_Boolean, Callback_OnConfirmEvent_Boolean, Callback_OnPromptEvent_Boolean, Callback_OnConsoleEvent_Boolean, Callback_OnErrorReceiveEvent_Void, Callback_OnHttpErrorReceiveEvent_Void, Callback_OnDownloadStartEvent_Void, Callback_OnRefreshAccessedHistoryEvent_Void, Type_WebAttribute_onUrlLoadIntercept_callback, Callback_Literal_Function_handler_Object_error_Void, Callback_OnRenderExitedEvent_Void, Callback_OnShowFileSelectorEvent_Boolean, Callback_Literal_Object_detail_Boolean, Type_WebAttribute_onFileSelectorShow_callback, Callback_OnResourceLoadEvent_Void, OnFullScreenEnterCallback, Callback_OnScaleChangeEvent_Void, Callback_OnHttpAuthRequestEvent_Boolean, Callback_OnInterceptRequestEvent_WebResourceResponse, Callback_OnPermissionRequestEvent_Void, Callback_OnScreenCaptureRequestEvent_Void, Callback_OnContextMenuShowEvent_Boolean, OnContextMenuHideCallback, Callback_OnSearchResultReceiveEvent_Void, Callback_OnScrollEvent_Void, Callback_OnSslErrorEventReceiveEvent_Void, OnSslErrorEventCallback, Callback_OnClientAuthenticationEvent_Void, Callback_OnWindowNewEvent_Void, Callback_OnTouchIconUrlReceivedEvent_Void, Callback_OnFaviconReceivedEvent_Void, Callback_OnPageVisibleEvent_Void, Callback_OnDataResubmittedEvent_Void, Callback_OnAudioStateChangedEvent_Void, Callback_OnFirstContentfulPaintEvent_Void, OnFirstMeaningfulPaintCallback, OnLargestContentfulPaintCallback, Callback_OnLoadInterceptEvent_Boolean, Callback_OnOverScrollEvent_Void, OnSafeBrowsingCheckResultCallback, OnNavigationEntryCommittedCallback, OnIntelligentTrackingPreventionCallback, NestedScrollOptionsExt, Callback_NativeEmbedDataInfo_Void, OnNativeEmbedVisibilityChangeCallback, Callback_NativeEmbedTouchInfo_Void, OnOverrideUrlLoadingCallback, OnRenderProcessNotRespondingCallback, OnRenderProcessRespondingCallback, ExpandedMenuItemOptions, OnViewportFitChangedCallback, WebKeyboardCallback, OnAdsBlockedCallback, SslErrorEvent, Literal_String_plainText, Callback_Literal_String_plainText_Void } from "./../../component/web"
import { WindowSceneAttribute } from "./../../component/windowScene"
import { SurfaceRect, SurfaceRotationOptions, Literal_Number_surfaceHeight_surfaceWidth, XComponentController, XComponentOptions, Type_XComponentInterface_value, XComponentAttribute, OnNativeLoadCallback } from "./../../component/xcomponent"
import { SideBarContainerType, SideBarPosition, ButtonIconOptions, ButtonStyle, SideBarContainerAttribute } from "./../../component/sidebar"
import { RRect, WindowAnimationTarget, RemoteWindowAttribute } from "./../../component/remoteWindow"
import { SectionOptions, GetItemMainSizeByIndex, WaterFlowSections, WaterFlowLayoutMode, WaterFlowOptions, WaterFlowAttribute } from "./../../component/waterFlow"
import { DpiFollowStrategy, UIExtensionOptions, ReceiveCallback, UIExtensionProxy, Callback_UIExtensionProxy_Void, Literal_Number_code_Want_want, UIExtensionComponentAttribute, Callback_Literal_Number_code_Want_want_Void } from "./../../component/uiExtensionComponent"
import { RestrictedWorker, IsolatedOptions, IsolatedComponentAttribute } from "./../../component/isolatedComponent"
import { LinearIndicatorController, LinearIndicatorStartOptions, LinearIndicatorStyle, LinearIndicatorAttribute, OnLinearIndicatorChangeCallback } from "./../../component/linearindicator"
import { RawFileDescriptor } from "./../ArkRawFileDescriptorInterfaces"
import { AttributeModifier } from "./../../component/common"
import { IObservedObject, IWatchTrigger } from "../../stateManagement"
export class TypeChecker {
    static typeInstanceOf<T>(value: Object, prop: string): boolean {
        return value instanceof T
    }
    static typeCast<T>(value: Object): T {
        return value as T
    }
    static isNativeBuffer(value: Object): boolean {
        return value instanceof NativeBuffer
    }
    static isAbilityComponentAttribute(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof AbilityComponentAttribute
    }
    static isAccessibilityHoverEvent(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean): boolean {
        return value instanceof AccessibilityHoverEvent
    }
    static isAccessibilityHoverType(value: object|string|number|undefined|null): boolean {
        return value instanceof AccessibilityHoverType
    }
    static isAccessibilityOptions(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof AccessibilityOptions
    }
    static isActionSheet(value: object|string|number|undefined|null): boolean {
        return value instanceof ActionSheet
    }
    static isActionSheetButtonOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean): boolean {
        return value instanceof ActionSheetButtonOptions
    }
    static isActionSheetOffset(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof ActionSheetOffset
    }
    static isActionSheetOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean, arg9: boolean, arg10: boolean, arg11: boolean, arg12: boolean, arg13: boolean, arg14: boolean, arg15: boolean, arg16: boolean, arg17: boolean, arg18: boolean, arg19: boolean, arg20: boolean, arg21: boolean, arg22: boolean, arg23: boolean, arg24: boolean): boolean {
        return value instanceof ActionSheetOptions
    }
    static isAdaptiveColor(value: object|string|number|undefined|null): boolean {
        return value instanceof AdaptiveColor
    }
    static isAdsBlockedDetails(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof AdsBlockedDetails
    }
    static isAffinity(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof Affinity
    }
    static isAlertDialog(value: object|string|number|undefined|null): boolean {
        return value instanceof AlertDialog
    }
    static isAlertDialogButtonBaseOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean): boolean {
        return value instanceof AlertDialogButtonBaseOptions
    }
    static isAlertDialogButtonOptions(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof AlertDialogButtonOptions
    }
    static isAlertDialogParam(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean, arg9: boolean, arg10: boolean, arg11: boolean, arg12: boolean, arg13: boolean, arg14: boolean, arg15: boolean, arg16: boolean, arg17: boolean, arg18: boolean, arg19: boolean, arg20: boolean, arg21: boolean, arg22: boolean, arg23: boolean, arg24: boolean): boolean {
        return value instanceof AlertDialogParam
    }
    static isAlertDialogParamWithButtons(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof AlertDialogParamWithButtons
    }
    static isAlertDialogParamWithConfirm(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof AlertDialogParamWithConfirm
    }
    static isAlertDialogParamWithOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof AlertDialogParamWithOptions
    }
    static isAlignment(value: object|string|number|undefined|null): boolean {
        return value instanceof Alignment
    }
    static isAlignRuleOption(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean): boolean {
        return value instanceof AlignRuleOption
    }
    static isAlphabetIndexerAttribute(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean, arg9: boolean, arg10: boolean, arg11: boolean, arg12: boolean, arg13: boolean, arg14: boolean, arg15: boolean, arg16: boolean, arg17: boolean, arg18: boolean, arg19: boolean, arg20: boolean, arg21: boolean, arg22: boolean, arg23: boolean, arg24: boolean, arg25: boolean): boolean {
        return value instanceof AlphabetIndexerAttribute
    }
    static isAlphabetIndexerOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof AlphabetIndexerOptions
    }
    static isAnimatableArithmetic(value: object|string|number|undefined|null): boolean {
        return value instanceof AnimatableArithmetic
    }
    static isAnimateParam(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean): boolean {
        return value instanceof AnimateParam
    }
    static isAnimationExtender(value: object|string|number|undefined|null): boolean {
        return value instanceof AnimationExtender
    }
    static isAnimationMode(value: object|string|number|undefined|null): boolean {
        return value instanceof AnimationMode
    }
    static isAnimationStatus(value: object|string|number|undefined|null): boolean {
        return value instanceof AnimationStatus
    }
    static isAnimatorAttribute(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean, arg9: boolean, arg10: boolean, arg11: boolean, arg12: boolean, arg13: boolean): boolean {
        return value instanceof AnimatorAttribute
    }
    static isAppearSymbolEffect(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof AppearSymbolEffect
    }
    static isAppRotation(value: object|string|number|undefined|null): boolean {
        return value instanceof AppRotation
    }
    static isArea(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof Area
    }
    static isArrowPointPosition(value: object|string|number|undefined|null): boolean {
        return value instanceof ArrowPointPosition
    }
    static isArrowPosition(value: object|string|number|undefined|null): boolean {
        return value instanceof ArrowPosition
    }
    static isArrowStyle(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean): boolean {
        return value instanceof ArrowStyle
    }
    static isASTCResource(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof ASTCResource
    }
    static isAttributeModifier(value: object|string|number|undefined|null): boolean {
        return value instanceof AttributeModifier
    }
    static isAxis(value: object|string|number|undefined|null): boolean {
        return value instanceof Axis
    }
    static isBackgroundBlurStyleOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof BackgroundBlurStyleOptions
    }
    static isBackgroundBrightnessOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof BackgroundBrightnessOptions
    }
    static isBackgroundColorStyle(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof BackgroundColorStyle
    }
    static isBackgroundEffectOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean): boolean {
        return value instanceof BackgroundEffectOptions
    }
    static isBadgeAttribute(value: object|string|number|undefined|null): boolean {
        return value instanceof BadgeAttribute
    }
    static isBadgeParam(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof BadgeParam
    }
    static isBadgeParamWithNumber(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof BadgeParamWithNumber
    }
    static isBadgeParamWithString(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof BadgeParamWithString
    }
    static isBadgePosition(value: object|string|number|undefined|null): boolean {
        return value instanceof BadgePosition
    }
    static isBadgeStyle(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean): boolean {
        return value instanceof BadgeStyle
    }
    static isBarGridColumnOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean): boolean {
        return value instanceof BarGridColumnOptions
    }
    static isBarMode(value: object|string|number|undefined|null): boolean {
        return value instanceof BarMode
    }
    static isBarPosition(value: object|string|number|undefined|null): boolean {
        return value instanceof BarPosition
    }
    static isBarrierDirection(value: object|string|number|undefined|null): boolean {
        return value instanceof BarrierDirection
    }
    static isBarrierStyle(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof BarrierStyle
    }
    static isBarState(value: object|string|number|undefined|null): boolean {
        return value instanceof BarState
    }
    static isBarStyle(value: object|string|number|undefined|null): boolean {
        return value instanceof BarStyle
    }
    static isBaseEvent(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean, arg9: boolean): boolean {
        return value instanceof BaseEvent
    }
    static isBaseGestureEvent(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof BaseGestureEvent
    }
    static isBaselineOffsetStyle(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof BaselineOffsetStyle
    }
    static isBaseShape(value: object|string|number|undefined|null): boolean {
        return value instanceof BaseShape
    }
    static isBaseSpan(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof BaseSpan
    }
    static isBias(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof Bias
    }
    static isBindOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean): boolean {
        return value instanceof BindOptions
    }
    static isBlankAttribute(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof BlankAttribute
    }
    static isBlendApplyType(value: object|string|number|undefined|null): boolean {
        return value instanceof BlendApplyType
    }
    static isBlender(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof Blender
    }
    static isBlendMode(value: object|string|number|undefined|null): boolean {
        return value instanceof BlendMode
    }
    static isBlurOptions(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof BlurOptions
    }
    static isBlurStyle(value: object|string|number|undefined|null): boolean {
        return value instanceof BlurStyle
    }
    static isBlurStyleActivePolicy(value: object|string|number|undefined|null): boolean {
        return value instanceof BlurStyleActivePolicy
    }
    static isBlurStyleOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof BlurStyleOptions
    }
    static isBoardStyle(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof BoardStyle
    }
    static isBorderImageOption(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean): boolean {
        return value instanceof BorderImageOption
    }
    static isBorderOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean): boolean {
        return value instanceof BorderOptions
    }
    static isBorderRadiuses(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof BorderRadiuses
    }
    static isBorderStyle(value: object|string|number|undefined|null): boolean {
        return value instanceof BorderStyle
    }
    static isBottomTabBarStyle(value: object|string|number|undefined|null): boolean {
        return value instanceof BottomTabBarStyle
    }
    static isBounceSymbolEffect(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof BounceSymbolEffect
    }
    static isBreakPoints(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof BreakPoints
    }
    static isBreakpointsReference(value: object|string|number|undefined|null): boolean {
        return value instanceof BreakpointsReference
    }
    static isBusinessError(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof BusinessError
    }
    static isButtonAttribute(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean, arg9: boolean, arg10: boolean, arg11: boolean): boolean {
        return value instanceof ButtonAttribute
    }
    static isButtonConfiguration(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof ButtonConfiguration
    }
    static isButtonIconOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof ButtonIconOptions
    }
    static isButtonOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean): boolean {
        return value instanceof ButtonOptions
    }
    static isButtonRole(value: object|string|number|undefined|null): boolean {
        return value instanceof ButtonRole
    }
    static isButtonStyle(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean): boolean {
        return value instanceof ButtonStyle
    }
    static isButtonStyleMode(value: object|string|number|undefined|null): boolean {
        return value instanceof ButtonStyleMode
    }
    static isButtonType(value: object|string|number|undefined|null): boolean {
        return value instanceof ButtonType
    }
    static isCacheMode(value: object|string|number|undefined|null): boolean {
        return value instanceof CacheMode
    }
    static isCalendarAlign(value: object|string|number|undefined|null): boolean {
        return value instanceof CalendarAlign
    }
    static isCalendarAttribute(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean, arg9: boolean, arg10: boolean, arg11: boolean, arg12: boolean): boolean {
        return value instanceof CalendarAttribute
    }
    static isCalendarController(value: object|string|number|undefined|null): boolean {
        return value instanceof CalendarController
    }
    static isCalendarDay(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean, arg9: boolean, arg10: boolean): boolean {
        return value instanceof CalendarDay
    }
    static isCalendarDialogOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean, arg9: boolean, arg10: boolean, arg11: boolean, arg12: boolean, arg13: boolean): boolean {
        return value instanceof CalendarDialogOptions
    }
    static isCalendarOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof CalendarOptions
    }
    static isCalendarPickerAttribute(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof CalendarPickerAttribute
    }
    static isCalendarPickerDialog(value: object|string|number|undefined|null): boolean {
        return value instanceof CalendarPickerDialog
    }
    static isCalendarRequestedData(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean): boolean {
        return value instanceof CalendarRequestedData
    }
    static isCalendarSelectedDate(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof CalendarSelectedDate
    }
    static isCallback(value: object|string|number|undefined|null): boolean {
        return value instanceof Callback<void, void>
    }
    static isCancelButtonOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof CancelButtonOptions
    }
    static isCancelButtonStyle(value: object|string|number|undefined|null): boolean {
        return value instanceof CancelButtonStyle
    }
    static isCancelButtonSymbolOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof CancelButtonSymbolOptions
    }
    static isCanvasAttribute(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof CanvasAttribute
    }
    static isCanvasGradient(value: object|string|number|undefined|null): boolean {
        return value instanceof CanvasGradient
    }
    static isCanvasPath(value: object|string|number|undefined|null): boolean {
        return value instanceof CanvasPath
    }
    static isCanvasPattern(value: object|string|number|undefined|null): boolean {
        return value instanceof CanvasPattern
    }
    static isCanvasRenderer(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean, arg9: boolean, arg10: boolean, arg11: boolean, arg12: boolean, arg13: boolean, arg14: boolean, arg15: boolean, arg16: boolean, arg17: boolean, arg18: boolean, arg19: boolean): boolean {
        return value instanceof CanvasRenderer
    }
    static isCanvasRenderingContext2D(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof CanvasRenderingContext2D
    }
    static isCapsuleStyleOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean): boolean {
        return value instanceof CapsuleStyleOptions
    }
    static isCaretOffset(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof CaretOffset
    }
    static isCaretStyle(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof CaretStyle
    }
    static isChainAnimationOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean): boolean {
        return value instanceof ChainAnimationOptions
    }
    static isChainEdgeEffect(value: object|string|number|undefined|null): boolean {
        return value instanceof ChainEdgeEffect
    }
    static isChainStyle(value: object|string|number|undefined|null): boolean {
        return value instanceof ChainStyle
    }
    static isChainWeightOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof ChainWeightOptions
    }
    static isCheckboxAttribute(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean): boolean {
        return value instanceof CheckboxAttribute
    }
    static isCheckBoxConfiguration(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof CheckBoxConfiguration
    }
    static isCheckboxGroupAttribute(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean): boolean {
        return value instanceof CheckboxGroupAttribute
    }
    static isCheckboxGroupOptions(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof CheckboxGroupOptions
    }
    static isCheckboxGroupResult(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof CheckboxGroupResult
    }
    static isCheckboxOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof CheckboxOptions
    }
    static isCheckBoxShape(value: object|string|number|undefined|null): boolean {
        return value instanceof CheckBoxShape
    }
    static isChildrenMainSize(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof ChildrenMainSize
    }
    static isCircleAttribute(value: object|string|number|undefined|null): boolean {
        return value instanceof CircleAttribute
    }
    static isCircleOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof CircleOptions
    }
    static isCircleShape(value: object|string|number|undefined|null): boolean {
        return value instanceof CircleShape
    }
    static isCircleStyleOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof CircleStyleOptions
    }
    static isClickEffect(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof ClickEffect
    }
    static isClickEffectLevel(value: object|string|number|undefined|null): boolean {
        return value instanceof ClickEffectLevel
    }
    static isClickEvent(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean): boolean {
        return value instanceof ClickEvent
    }
    static isClientAuthenticationHandler(value: object|string|number|undefined|null): boolean {
        return value instanceof ClientAuthenticationHandler
    }
    static isCloseSwipeActionOptions(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof CloseSwipeActionOptions
    }
    static isColor(value: object|string|number|undefined|null): boolean {
        return value instanceof Color
    }
    static isColorFilter(value: object|string|number|undefined|null): boolean {
        return value instanceof ColorFilter
    }
    static isColoringStrategy(value: object|string|number|undefined|null): boolean {
        return value instanceof ColoringStrategy
    }
    static isColorMetrics(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean): boolean {
        return value instanceof ColorMetrics
    }
    static isColorMode(value: object|string|number|undefined|null): boolean {
        return value instanceof ColorMode
    }
    static isColorStop(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof ColorStop
    }
    static isColumnAttribute(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof ColumnAttribute
    }
    static isColumnOptions(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof ColumnOptions
    }
    static isColumnSplitAttribute(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof ColumnSplitAttribute
    }
    static isColumnSplitDividerStyle(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof ColumnSplitDividerStyle
    }
    static isCommonAttribute(value: object|string|number|undefined|null): boolean {
        return value instanceof CommonAttribute
    }
    static isCommonConfiguration(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof CommonConfiguration
    }
    static isCommonMethod(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean, arg9: boolean, arg10: boolean, arg11: boolean, arg12: boolean, arg13: boolean, arg14: boolean, arg15: boolean, arg16: boolean, arg17: boolean, arg18: boolean, arg19: boolean, arg20: boolean, arg21: boolean, arg22: boolean, arg23: boolean, arg24: boolean, arg25: boolean, arg26: boolean, arg27: boolean, arg28: boolean, arg29: boolean, arg30: boolean, arg31: boolean, arg32: boolean, arg33: boolean, arg34: boolean, arg35: boolean, arg36: boolean, arg37: boolean, arg38: boolean, arg39: boolean, arg40: boolean, arg41: boolean, arg42: boolean, arg43: boolean, arg44: boolean, arg45: boolean, arg46: boolean, arg47: boolean, arg48: boolean, arg49: boolean, arg50: boolean, arg51: boolean, arg52: boolean, arg53: boolean, arg54: boolean, arg55: boolean, arg56: boolean, arg57: boolean, arg58: boolean, arg59: boolean, arg60: boolean, arg61: boolean, arg62: boolean, arg63: boolean, arg64: boolean, arg65: boolean, arg66: boolean, arg67: boolean, arg68: boolean, arg69: boolean, arg70: boolean, arg71: boolean, arg72: boolean, arg73: boolean, arg74: boolean, arg75: boolean, arg76: boolean, arg77: boolean, arg78: boolean, arg79: boolean, arg80: boolean, arg81: boolean, arg82: boolean, arg83: boolean, arg84: boolean, arg85: boolean, arg86: boolean, arg87: boolean, arg88: boolean, arg89: boolean, arg90: boolean, arg91: boolean, arg92: boolean, arg93: boolean, arg94: boolean, arg95: boolean, arg96: boolean, arg97: boolean, arg98: boolean, arg99: boolean, arg100: boolean, arg101: boolean, arg102: boolean, arg103: boolean, arg104: boolean, arg105: boolean, arg106: boolean, arg107: boolean, arg108: boolean, arg109: boolean, arg110: boolean, arg111: boolean, arg112: boolean, arg113: boolean, arg114: boolean, arg115: boolean, arg116: boolean, arg117: boolean, arg118: boolean, arg119: boolean, arg120: boolean, arg121: boolean, arg122: boolean, arg123: boolean, arg124: boolean, arg125: boolean, arg126: boolean, arg127: boolean, arg128: boolean, arg129: boolean, arg130: boolean, arg131: boolean, arg132: boolean, arg133: boolean, arg134: boolean, arg135: boolean, arg136: boolean, arg137: boolean, arg138: boolean, arg139: boolean, arg140: boolean, arg141: boolean, arg142: boolean, arg143: boolean, arg144: boolean): boolean {
        return value instanceof CommonMethod
    }
    static isCommonProgressStyleOptions(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof CommonProgressStyleOptions
    }
    static isCommonShape(value: object|string|number|undefined|null): boolean {
        return value instanceof CommonShape
    }
    static isCommonShapeMethod(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean, arg9: boolean, arg10: boolean): boolean {
        return value instanceof CommonShapeMethod
    }
    static isCommonTransition(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof CommonTransition
    }
    static isComponent3DAttribute(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean): boolean {
        return value instanceof Component3DAttribute
    }
    static isComponentContent(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof ComponentContent
    }
    static isComponentOptions(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof ComponentOptions
    }
    // static isComponentRoot(value: object|string|number|undefined|null): boolean {
    //     return value instanceof ComponentRoot
    // }
    static isComputedBarAttribute(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof ComputedBarAttribute
    }
    static isConfiguration(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof Configuration
    }
    static isConsoleMessage(value: object|string|number|undefined|null): boolean {
        return value instanceof ConsoleMessage
    }
    static isConstraintSizeOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof ConstraintSizeOptions
    }
    static isContainerSpanAttribute(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof ContainerSpanAttribute
    }
    static isContent(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof Content
    }
    static isContentClipMode(value: object|string|number|undefined|null): boolean {
        return value instanceof ContentClipMode
    }
    static isContentCoverOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof ContentCoverOptions
    }
    static isContentModifier(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof ContentModifier
    }
    static isContentSlotAttribute(value: object|string|number|undefined|null): boolean {
        return value instanceof ContentSlotAttribute
    }
    static isContentSlotInterface(value: object|string|number|undefined|null): boolean {
        return value instanceof ContentSlotInterface
    }
    static isContentType(value: object|string|number|undefined|null): boolean {
        return value instanceof ContentType
    }
    static isContext(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof Context
    }
    static isContextMenu(value: object|string|number|undefined|null): boolean {
        return value instanceof ContextMenu
    }
    static isContextMenuAnimationOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof ContextMenuAnimationOptions
    }
    static isContextMenuEditStateFlags(value: object|string|number|undefined|null): boolean {
        return value instanceof ContextMenuEditStateFlags
    }
    static isContextMenuInputFieldType(value: object|string|number|undefined|null): boolean {
        return value instanceof ContextMenuInputFieldType
    }
    static isContextMenuMediaType(value: object|string|number|undefined|null): boolean {
        return value instanceof ContextMenuMediaType
    }
    static isContextMenuOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean, arg9: boolean, arg10: boolean, arg11: boolean, arg12: boolean, arg13: boolean, arg14: boolean, arg15: boolean): boolean {
        return value instanceof ContextMenuOptions
    }
    static isContextMenuSourceType(value: object|string|number|undefined|null): boolean {
        return value instanceof ContextMenuSourceType
    }
    static isControllerHandler(value: object|string|number|undefined|null): boolean {
        return value instanceof ControllerHandler
    }
    static isControlSize(value: object|string|number|undefined|null): boolean {
        return value instanceof ControlSize
    }
    static isCopyEvent(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof CopyEvent
    }
    static isCopyOptions(value: object|string|number|undefined|null): boolean {
        return value instanceof CopyOptions
    }
    static isCounterAttribute(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof CounterAttribute
    }
    static isCurrentDayStyle(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean, arg9: boolean, arg10: boolean, arg11: boolean, arg12: boolean, arg13: boolean, arg14: boolean, arg15: boolean, arg16: boolean, arg17: boolean, arg18: boolean, arg19: boolean, arg20: boolean, arg21: boolean, arg22: boolean): boolean {
        return value instanceof CurrentDayStyle
    }
    static isCurve(value: object|string|number|undefined|null): boolean {
        return value instanceof Curve
    }
    static isCustomComponent(value: object|string|number|undefined|null): boolean {
        return value instanceof CustomComponent
    }
    static isCustomDialogController(value: object|string|number|undefined|null): boolean {
        return value instanceof CustomDialogController
    }
    static isCustomDialogControllerOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean, arg9: boolean, arg10: boolean, arg11: boolean, arg12: boolean, arg13: boolean, arg14: boolean, arg15: boolean, arg16: boolean, arg17: boolean, arg18: boolean, arg19: boolean, arg20: boolean, arg21: boolean, arg22: boolean, arg23: boolean, arg24: boolean, arg25: boolean): boolean {
        return value instanceof CustomDialogControllerOptions
    }
    static isCustomPopupOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean, arg9: boolean, arg10: boolean, arg11: boolean, arg12: boolean, arg13: boolean, arg14: boolean, arg15: boolean, arg16: boolean, arg17: boolean, arg18: boolean, arg19: boolean, arg20: boolean, arg21: boolean, arg22: boolean, arg23: boolean): boolean {
        return value instanceof CustomPopupOptions
    }
    static isCustomSpan(value: object|string|number|undefined|null): boolean {
        return value instanceof CustomSpan
    }
    static isCustomSpanDrawInfo(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof CustomSpanDrawInfo
    }
    static isCustomSpanMeasureInfo(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof CustomSpanMeasureInfo
    }
    static isCustomSpanMetrics(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof CustomSpanMetrics
    }
    static isCustomTheme(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof CustomTheme
    }
    static isCutEvent(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof CutEvent
    }
    static isDataAddOperation(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof DataAddOperation
    }
    static isDataChangeOperation(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof DataChangeOperation
    }
    static isDataDeleteOperation(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof DataDeleteOperation
    }
    static isDataExchangeOperation(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof DataExchangeOperation
    }
    static isDataMoveOperation(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof DataMoveOperation
    }
    static isDataOperationType(value: object|string|number|undefined|null): boolean {
        return value instanceof DataOperationType
    }
    static isDataPanelAttribute(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean): boolean {
        return value instanceof DataPanelAttribute
    }
    static isDataPanelConfiguration(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof DataPanelConfiguration
    }
    static isDataPanelOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof DataPanelOptions
    }
    static isDataPanelShadowOptions(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof DataPanelShadowOptions
    }
    static isDataPanelType(value: object|string|number|undefined|null): boolean {
        return value instanceof DataPanelType
    }
    static isDataReloadOperation(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof DataReloadOperation
    }
    static isDataResubmissionHandler(value: object|string|number|undefined|null): boolean {
        return value instanceof DataResubmissionHandler
    }
    static isDatePickerAttribute(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean): boolean {
        return value instanceof DatePickerAttribute
    }
    static isDatePickerDialog(value: object|string|number|undefined|null): boolean {
        return value instanceof DatePickerDialog
    }
    static isDatePickerDialogOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean, arg9: boolean, arg10: boolean, arg11: boolean, arg12: boolean, arg13: boolean, arg14: boolean, arg15: boolean, arg16: boolean, arg17: boolean, arg18: boolean, arg19: boolean, arg20: boolean, arg21: boolean, arg22: boolean, arg23: boolean, arg24: boolean, arg25: boolean, arg26: boolean, arg27: boolean): boolean {
        return value instanceof DatePickerDialogOptions
    }
    static isDatePickerOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof DatePickerOptions
    }
    static isDatePickerResult(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof DatePickerResult
    }
    static isDateTimeOptions(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof DateTimeOptions
    }
    static isDecorationStyle(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof DecorationStyle
    }
    static isDecorationStyleInterface(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof DecorationStyleInterface
    }
    static isDecorationStyleResult(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof DecorationStyleResult
    }
    static isDeleteValue(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof DeleteValue
    }
    static isDialogAlignment(value: object|string|number|undefined|null): boolean {
        return value instanceof DialogAlignment
    }
    static isDialogButtonDirection(value: object|string|number|undefined|null): boolean {
        return value instanceof DialogButtonDirection
    }
    static isDialogButtonStyle(value: object|string|number|undefined|null): boolean {
        return value instanceof DialogButtonStyle
    }
    static isDigitIndicator(value: object|string|number|undefined|null): boolean {
        return value instanceof DigitIndicator
    }
    static isDirection(value: object|string|number|undefined|null): boolean {
        return value instanceof Direction
    }
    static isDirectionalEdgesT(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof DirectionalEdgesT
    }
    static isDisappearSymbolEffect(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof DisappearSymbolEffect
    }
    static isDismissContentCoverAction(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof DismissContentCoverAction
    }
    static isDismissDialogAction(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof DismissDialogAction
    }
    static isDismissPopupAction(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof DismissPopupAction
    }
    static isDismissReason(value: object|string|number|undefined|null): boolean {
        return value instanceof DismissReason
    }
    static isDismissSheetAction(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof DismissSheetAction
    }
    static isDistributionType(value: object|string|number|undefined|null): boolean {
        return value instanceof DistributionType
    }
    static isDisturbanceFieldShape(value: object|string|number|undefined|null): boolean {
        return value instanceof DisturbanceFieldShape
    }
    static isDividerAttribute(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof DividerAttribute
    }
    static isDividerOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof DividerOptions
    }
    static isDividerStyle(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof DividerStyle
    }
    static isDividerStyleOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof DividerStyleOptions
    }
    static isDotIndicator(value: object|string|number|undefined|null): boolean {
        return value instanceof DotIndicator
    }
    static isDoubleAnimationParam(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean): boolean {
        return value instanceof DoubleAnimationParam
    }
    static isDpiFollowStrategy(value: object|string|number|undefined|null): boolean {
        return value instanceof DpiFollowStrategy
    }
    static isDragBehavior(value: object|string|number|undefined|null): boolean {
        return value instanceof DragBehavior
    }
    static isDragEvent(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof DragEvent
    }
    static isDragInteractionOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof DragInteractionOptions
    }
    static isDragItemInfo(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof DragItemInfo
    }
    static isDragPreviewMode(value: object|string|number|undefined|null): boolean {
        return value instanceof DragPreviewMode
    }
    static isDragPreviewOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof DragPreviewOptions
    }
    static isDragResult(value: object|string|number|undefined|null): boolean {
        return value instanceof DragResult
    }
    static isDrawableDescriptor(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof DrawableDescriptor
    }
    static isDrawContext(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof DrawContext
    }
    static isDrawingCanvas(value: object|string|number|undefined|null): boolean {
        return value instanceof DrawingCanvas
    }
    static isDrawingColorFilter(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof DrawingColorFilter
    }
    static isDrawingLattice(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof DrawingLattice
    }
    static isDrawingRenderingContext(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof DrawingRenderingContext
    }
    static isDrawModifier(value: object|string|number|undefined|null): boolean {
        return value instanceof DrawModifier
    }
    static isDynamicNode(value: object|string|number|undefined|null): boolean {
        return value instanceof DynamicNode
    }
    static isDynamicRangeMode(value: object|string|number|undefined|null): boolean {
        return value instanceof DynamicRangeMode
    }
    static isEclipseStyleOptions(value: object|string|number|undefined|null): boolean {
        return value instanceof EclipseStyleOptions
    }
    static isEdge(value: object|string|number|undefined|null): boolean {
        return value instanceof Edge
    }
    static isEdgeColors(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof EdgeColors
    }
    static isEdgeEffect(value: object|string|number|undefined|null): boolean {
        return value instanceof EdgeEffect
    }
    static isEdgeEffectOptions(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof EdgeEffectOptions
    }
    static isEdgeOutlineStyles(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof EdgeOutlineStyles
    }
    static isEdgeOutlineWidths(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof EdgeOutlineWidths
    }
    static isEdges(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof Edges
    }
    static isEdgeStyles(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof EdgeStyles
    }
    static isEdgeWidths(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof EdgeWidths
    }
    static isEditMenuOptions(value: object|string|number|undefined|null): boolean {
        return value instanceof EditMenuOptions
    }
    static isEditMode(value: object|string|number|undefined|null): boolean {
        return value instanceof EditMode
    }
    static isEffectComponentAttribute(value: object|string|number|undefined|null): boolean {
        return value instanceof EffectComponentAttribute
    }
    static isEffectDirection(value: object|string|number|undefined|null): boolean {
        return value instanceof EffectDirection
    }
    static isEffectFillStyle(value: object|string|number|undefined|null): boolean {
        return value instanceof EffectFillStyle
    }
    static isEffectScope(value: object|string|number|undefined|null): boolean {
        return value instanceof EffectScope
    }
    static isEffectType(value: object|string|number|undefined|null): boolean {
        return value instanceof EffectType
    }
    static isEllipseAttribute(value: object|string|number|undefined|null): boolean {
        return value instanceof EllipseAttribute
    }
    static isEllipseOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof EllipseOptions
    }
    static isEllipseShape(value: object|string|number|undefined|null): boolean {
        return value instanceof EllipseShape
    }
    static isEllipsisMode(value: object|string|number|undefined|null): boolean {
        return value instanceof EllipsisMode
    }
    static isEmbeddedComponentAttribute(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof EmbeddedComponentAttribute
    }
    static isEmbeddedType(value: object|string|number|undefined|null): boolean {
        return value instanceof EmbeddedType
    }
    static isEmitterParticleOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean): boolean {
        return value instanceof EmitterParticleOptions
    }
    static isEmitterProperty(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof EmitterProperty
    }
    static isEnterKeyType(value: object|string|number|undefined|null): boolean {
        return value instanceof EnterKeyType
    }
    static isEnvPropsOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof EnvPropsOptions
    }
    static isEventEmulator(value: object|string|number|undefined|null): boolean {
        return value instanceof EventEmulator
    }
    static isEventResult(value: object|string|number|undefined|null): boolean {
        return value instanceof EventResult
    }
    static isEventTarget(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof EventTarget
    }
    static isEventTargetInfo(value: object|string|number|undefined|null): boolean {
        return value instanceof EventTargetInfo
    }
    static isExchangeIndex(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof ExchangeIndex
    }
    static isExchangeKey(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof ExchangeKey
    }
    static isExpandedMenuItemOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof ExpandedMenuItemOptions
    }
    static isExpectedFrameRateRange(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof ExpectedFrameRateRange
    }
    static isFadingEdgeOptions(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof FadingEdgeOptions
    }
    static isFileSelectorMode(value: object|string|number|undefined|null): boolean {
        return value instanceof FileSelectorMode
    }
    static isFileSelectorParam(value: object|string|number|undefined|null): boolean {
        return value instanceof FileSelectorParam
    }
    static isFileSelectorResult(value: object|string|number|undefined|null): boolean {
        return value instanceof FileSelectorResult
    }
    static isFillMode(value: object|string|number|undefined|null): boolean {
        return value instanceof FillMode
    }
    static isFilter(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof Filter
    }
    static isFingerInfo(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean): boolean {
        return value instanceof FingerInfo
    }
    static isFinishCallbackType(value: object|string|number|undefined|null): boolean {
        return value instanceof FinishCallbackType
    }
    static isFirstMeaningfulPaint(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof FirstMeaningfulPaint
    }
    static isFlexAlign(value: object|string|number|undefined|null): boolean {
        return value instanceof FlexAlign
    }
    static isFlexAttribute(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof FlexAttribute
    }
    static isFlexDirection(value: object|string|number|undefined|null): boolean {
        return value instanceof FlexDirection
    }
    static isFlexOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean): boolean {
        return value instanceof FlexOptions
    }
    static isFlexSpaceOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof FlexSpaceOptions
    }
    static isFlexWrap(value: object|string|number|undefined|null): boolean {
        return value instanceof FlexWrap
    }
    static isFlowItemAttribute(value: object|string|number|undefined|null): boolean {
        return value instanceof FlowItemAttribute
    }
    static isFocusBoxStyle(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof FocusBoxStyle
    }
    static isFocusController(value: object|string|number|undefined|null): boolean {
        return value instanceof FocusController
    }
    static isFocusPriority(value: object|string|number|undefined|null): boolean {
        return value instanceof FocusPriority
    }
    static isFolderStackAttribute(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean): boolean {
        return value instanceof FolderStackAttribute
    }
    static isFolderStackOptions(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof FolderStackOptions
    }
    static isFoldStatus(value: object|string|number|undefined|null): boolean {
        return value instanceof FoldStatus
    }
    static isFont(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof Font
    }
    static isFontInfo(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean, arg9: boolean): boolean {
        return value instanceof FontInfo
    }
    static isFontOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof FontOptions
    }
    static isFontSettingOptions(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof FontSettingOptions
    }
    static isFontStyle(value: object|string|number|undefined|null): boolean {
        return value instanceof FontStyle
    }
    static isFontWeight(value: object|string|number|undefined|null): boolean {
        return value instanceof FontWeight
    }
    static isForegroundBlurStyleOptions(value: object|string|number|undefined|null): boolean {
        return value instanceof ForegroundBlurStyleOptions
    }
    static isForegroundEffectOptions(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof ForegroundEffectOptions
    }
    static isFormCallbackInfo(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof FormCallbackInfo
    }
    static isFormComponentAttribute(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean, arg9: boolean): boolean {
        return value instanceof FormComponentAttribute
    }
    static isFormDimension(value: object|string|number|undefined|null): boolean {
        return value instanceof FormDimension
    }
    static isFormInfo(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean, arg9: boolean): boolean {
        return value instanceof FormInfo
    }
    static isFormLinkAttribute(value: object|string|number|undefined|null): boolean {
        return value instanceof FormLinkAttribute
    }
    static isFormLinkOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean): boolean {
        return value instanceof FormLinkOptions
    }
    static isFormRenderingMode(value: object|string|number|undefined|null): boolean {
        return value instanceof FormRenderingMode
    }
    static isFormShape(value: object|string|number|undefined|null): boolean {
        return value instanceof FormShape
    }
    static isFrameNode(value: object|string|number|undefined|null): boolean {
        return value instanceof FrameNode
    }
    static isFrictionMotion(value: object|string|number|undefined|null): boolean {
        return value instanceof FrictionMotion
    }
    static isFullScreenEnterEvent(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof FullScreenEnterEvent
    }
    static isFullScreenExitHandler(value: object|string|number|undefined|null): boolean {
        return value instanceof FullScreenExitHandler
    }
    static isFullscreenInfo(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof FullscreenInfo
    }
    static isFunctionKey(value: object|string|number|undefined|null): boolean {
        return value instanceof FunctionKey
    }
    static isGaugeAttribute(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean, arg9: boolean): boolean {
        return value instanceof GaugeAttribute
    }
    static isGaugeConfiguration(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof GaugeConfiguration
    }
    static isGaugeIndicatorOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof GaugeIndicatorOptions
    }
    static isGaugeOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof GaugeOptions
    }
    static isGaugeShadowOptions(value: object|string|number|undefined|null): boolean {
        return value instanceof GaugeShadowOptions
    }
    static isGeometryInfo(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof GeometryInfo
    }
    static isGeometryTransitionOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof GeometryTransitionOptions
    }
    static isGestureControlGestureType(value: object|string|number|undefined|null): boolean {
        return value instanceof GestureControl.GestureType
    }
    static isGestureEvent(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean, arg9: boolean, arg10: boolean, arg11: boolean): boolean {
        return value instanceof GestureEvent
    }
    static isGestureGroupGestureHandlerOptions(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof GestureGroupGestureHandlerOptions
    }
    static isGestureGroupInterface(value: object|string|number|undefined|null): boolean {
        return value instanceof GestureGroupInterface
    }
    static isGestureHandler(value: object|string|number|undefined|null): boolean {
        return value instanceof GestureHandler
    }
    static isGestureInfo(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof GestureInfo
    }
    static isGestureInterface(value: object|string|number|undefined|null): boolean {
        return value instanceof GestureInterface
    }
    static isGestureJudgeResult(value: object|string|number|undefined|null): boolean {
        return value instanceof GestureJudgeResult
    }
    static isGestureMask(value: object|string|number|undefined|null): boolean {
        return value instanceof GestureMask
    }
    static isGestureMode(value: object|string|number|undefined|null): boolean {
        return value instanceof GestureMode
    }
    static isGestureModifier(value: object|string|number|undefined|null): boolean {
        return value instanceof GestureModifier
    }
    static isGesturePriority(value: object|string|number|undefined|null): boolean {
        return value instanceof GesturePriority
    }
    static isGestureRecognizer(value: object|string|number|undefined|null): boolean {
        return value instanceof GestureRecognizer
    }
    static isGestureRecognizerState(value: object|string|number|undefined|null): boolean {
        return value instanceof GestureRecognizerState
    }
    static isGestureStyle(value: object|string|number|undefined|null): boolean {
        return value instanceof GestureStyle
    }
    static isGestureStyleInterface(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof GestureStyleInterface
    }
    static isGlobalScope_ohos_arkui_componentSnapshot(value: object|string|number|undefined|null): boolean {
        return value instanceof GlobalScope_ohos_arkui_componentSnapshot
    }
    static isGlobalScope_ohos_arkui_performanceMonitor(value: object|string|number|undefined|null): boolean {
        return value instanceof GlobalScope_ohos_arkui_performanceMonitor
    }
    static isGlobalScope_ohos_font(value: object|string|number|undefined|null): boolean {
        return value instanceof GlobalScope_ohos_font
    }
    static isGlobalScope_ohos_measure_utils(value: object|string|number|undefined|null): boolean {
        return value instanceof GlobalScope_ohos_measure_utils
    }
    static isGradientDirection(value: object|string|number|undefined|null): boolean {
        return value instanceof GradientDirection
    }
    static isGridAttribute(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean, arg9: boolean, arg10: boolean, arg11: boolean, arg12: boolean, arg13: boolean, arg14: boolean, arg15: boolean, arg16: boolean, arg17: boolean, arg18: boolean, arg19: boolean, arg20: boolean, arg21: boolean, arg22: boolean, arg23: boolean, arg24: boolean, arg25: boolean, arg26: boolean, arg27: boolean, arg28: boolean, arg29: boolean, arg30: boolean, arg31: boolean): boolean {
        return value instanceof GridAttribute
    }
    static isGridColAttribute(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof GridColAttribute
    }
    static isGridColColumnOption(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean): boolean {
        return value instanceof GridColColumnOption
    }
    static isGridColOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof GridColOptions
    }
    static isGridContainerAttribute(value: object|string|number|undefined|null): boolean {
        return value instanceof GridContainerAttribute
    }
    static isGridContainerOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof GridContainerOptions
    }
    static isGridDirection(value: object|string|number|undefined|null): boolean {
        return value instanceof GridDirection
    }
    static isGridItemAlignment(value: object|string|number|undefined|null): boolean {
        return value instanceof GridItemAlignment
    }
    static isGridItemAttribute(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean): boolean {
        return value instanceof GridItemAttribute
    }
    static isGridItemOptions(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof GridItemOptions
    }
    static isGridItemStyle(value: object|string|number|undefined|null): boolean {
        return value instanceof GridItemStyle
    }
    static isGridLayoutOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof GridLayoutOptions
    }
    static isGridRowAttribute(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof GridRowAttribute
    }
    static isGridRowColumnOption(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean): boolean {
        return value instanceof GridRowColumnOption
    }
    static isGridRowDirection(value: object|string|number|undefined|null): boolean {
        return value instanceof GridRowDirection
    }
    static isGridRowOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof GridRowOptions
    }
    static isGridRowSizeOption(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean): boolean {
        return value instanceof GridRowSizeOption
    }
    static isGuideLinePosition(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof GuideLinePosition
    }
    static isGuideLineStyle(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof GuideLineStyle
    }
    static isGutterOption(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof GutterOption
    }
    static isHeader(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof Header
    }
    static isHeightBreakpoint(value: object|string|number|undefined|null): boolean {
        return value instanceof HeightBreakpoint
    }
    static isHierarchicalSymbolEffect(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof HierarchicalSymbolEffect
    }
    static isHistoricalPoint(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof HistoricalPoint
    }
    static isHitTestMode(value: object|string|number|undefined|null): boolean {
        return value instanceof HitTestMode
    }
    static isHitTestType(value: object|string|number|undefined|null): boolean {
        return value instanceof HitTestType
    }
    static isHorizontalAlign(value: object|string|number|undefined|null): boolean {
        return value instanceof HorizontalAlign
    }
    static isHoverEffect(value: object|string|number|undefined|null): boolean {
        return value instanceof HoverEffect
    }
    static isHoverEvent(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof HoverEvent
    }
    static isHoverEventParam(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof HoverEventParam
    }
    static isHoverModeAreaType(value: object|string|number|undefined|null): boolean {
        return value instanceof HoverModeAreaType
    }
    static isHttpAuthHandler(value: object|string|number|undefined|null): boolean {
        return value instanceof HttpAuthHandler
    }
    static isHyperlinkAttribute(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof HyperlinkAttribute
    }
    static isIconOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof IconOptions
    }
    static isICurve(value: object|string|number|undefined|null): boolean {
        return value instanceof ICurve
    }
    static isIlluminatedType(value: object|string|number|undefined|null): boolean {
        return value instanceof IlluminatedType
    }
    static isImageAIOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof ImageAIOptions
    }
    static isImageAnalyzerConfig(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof ImageAnalyzerConfig
    }
    static isImageAnalyzerController(value: object|string|number|undefined|null): boolean {
        return value instanceof ImageAnalyzerController
    }
    static isImageAnalyzerType(value: object|string|number|undefined|null): boolean {
        return value instanceof ImageAnalyzerType
    }
    static isImageAnimatorAttribute(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean, arg9: boolean, arg10: boolean, arg11: boolean, arg12: boolean): boolean {
        return value instanceof ImageAnimatorAttribute
    }
    static isImageAttachment(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean): boolean {
        return value instanceof ImageAttachment
    }
    static isImageAttachmentInterface(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean): boolean {
        return value instanceof ImageAttachmentInterface
    }
    static isImageAttachmentLayoutStyle(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof ImageAttachmentLayoutStyle
    }
    static isImageAttribute(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean, arg9: boolean, arg10: boolean, arg11: boolean, arg12: boolean, arg13: boolean, arg14: boolean, arg15: boolean, arg16: boolean, arg17: boolean, arg18: boolean, arg19: boolean, arg20: boolean, arg21: boolean, arg22: boolean, arg23: boolean, arg24: boolean): boolean {
        return value instanceof ImageAttribute
    }
    static isImageBitmap(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof ImageBitmap
    }
    static isImageContent(value: object|string|number|undefined|null): boolean {
        return value instanceof ImageContent
    }
    static isImageData(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof ImageData
    }
    static isImageError(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof ImageError
    }
    static isImageFit(value: object|string|number|undefined|null): boolean {
        return value instanceof ImageFit
    }
    static isImageFrameInfo(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean): boolean {
        return value instanceof ImageFrameInfo
    }
    static isImageInterpolation(value: object|string|number|undefined|null): boolean {
        return value instanceof ImageInterpolation
    }
    static isImageLoadResult(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean): boolean {
        return value instanceof ImageLoadResult
    }
    static isImageModifier(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof ImageModifier
    }
    static isImageParticleParameters(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof ImageParticleParameters
    }
    static isImageRenderMode(value: object|string|number|undefined|null): boolean {
        return value instanceof ImageRenderMode
    }
    static isImageRepeat(value: object|string|number|undefined|null): boolean {
        return value instanceof ImageRepeat
    }
    static isImageSize(value: object|string|number|undefined|null): boolean {
        return value instanceof ImageSize
    }
    static isImageSourceSize(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof ImageSourceSize
    }
    static isImageSpanAlignment(value: object|string|number|undefined|null): boolean {
        return value instanceof ImageSpanAlignment
    }
    static isImageSpanAttribute(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean): boolean {
        return value instanceof ImageSpanAttribute
    }
    static isIndexerAlign(value: object|string|number|undefined|null): boolean {
        return value instanceof IndexerAlign
    }
    static isIndicator(value: object|string|number|undefined|null): boolean {
        return value instanceof Indicator
    }
    static isIndicatorComponentAttribute(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean): boolean {
        return value instanceof IndicatorComponentAttribute
    }
    static isIndicatorComponentController(value: object|string|number|undefined|null): boolean {
        return value instanceof IndicatorComponentController
    }
    static isIndicatorStyle(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean): boolean {
        return value instanceof IndicatorStyle
    }
    static isInputCounterOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof InputCounterOptions
    }
    static isInputType(value: object|string|number|undefined|null): boolean {
        return value instanceof InputType
    }
    static isInsertValue(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof InsertValue
    }
    static isIntelligentTrackingPreventionDetails(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof IntelligentTrackingPreventionDetails
    }
    static isIntentionCode(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof IntentionCode
    }
    static isInvertOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof InvertOptions
    }
    static isIPropertySubscriber(value: object|string|number|undefined|null): boolean {
        return value instanceof IPropertySubscriber
    }
    static isISinglePropertyChangeSubscriber(value: object|string|number|undefined|null): boolean {
        return value instanceof ISinglePropertyChangeSubscriber
    }
    static isIsolatedComponentAttribute(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof IsolatedComponentAttribute
    }
    static isIsolatedOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof IsolatedOptions
    }
    static isItemAlign(value: object|string|number|undefined|null): boolean {
        return value instanceof ItemAlign
    }
    static isItemDragInfo(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof ItemDragInfo
    }
    static isItemState(value: object|string|number|undefined|null): boolean {
        return value instanceof ItemState
    }
    static isJavaScriptProxy(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean): boolean {
        return value instanceof JavaScriptProxy
    }
    static isJsGeolocation(value: object|string|number|undefined|null): boolean {
        return value instanceof JsGeolocation
    }
    static isJsResult(value: object|string|number|undefined|null): boolean {
        return value instanceof JsResult
    }
    static isKeyboardAvoidMode(value: object|string|number|undefined|null): boolean {
        return value instanceof KeyboardAvoidMode
    }
    static isKeyboardOptions(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof KeyboardOptions
    }
    static isKeyEvent(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean, arg9: boolean): boolean {
        return value instanceof KeyEvent
    }
    static isKeyframeAnimateParam(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof KeyframeAnimateParam
    }
    static isKeyframeState(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof KeyframeState
    }
    static isKeySource(value: object|string|number|undefined|null): boolean {
        return value instanceof KeySource
    }
    static isKeyType(value: object|string|number|undefined|null): boolean {
        return value instanceof KeyType
    }
    static isLabelStyle(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean): boolean {
        return value instanceof LabelStyle
    }
    static isLargestContentfulPaint(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean): boolean {
        return value instanceof LargestContentfulPaint
    }
    static isLaunchMode(value: object|string|number|undefined|null): boolean {
        return value instanceof LaunchMode
    }
    static isLayoutable(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof Layoutable
    }
    static isLayoutBorderInfo(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof LayoutBorderInfo
    }
    static isLayoutChild(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof LayoutChild
    }
    static isLayoutDirection(value: object|string|number|undefined|null): boolean {
        return value instanceof LayoutDirection
    }
    static isLayoutInfo(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof LayoutInfo
    }
    static isLayoutManager(value: object|string|number|undefined|null): boolean {
        return value instanceof LayoutManager
    }
    static isLayoutMode(value: object|string|number|undefined|null): boolean {
        return value instanceof LayoutMode
    }
    static isLayoutSafeAreaEdge(value: object|string|number|undefined|null): boolean {
        return value instanceof LayoutSafeAreaEdge
    }
    static isLayoutSafeAreaType(value: object|string|number|undefined|null): boolean {
        return value instanceof LayoutSafeAreaType
    }
    static isLayoutStyle(value: object|string|number|undefined|null): boolean {
        return value instanceof LayoutStyle
    }
    static isLazyForEachOps(value: object|string|number|undefined|null): boolean {
        return value instanceof LazyForEachOps
    }
    static isLeadingMarginPlaceholder(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof LeadingMarginPlaceholder
    }
    static isLengthConstrain(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof LengthConstrain
    }
    static isLengthMetrics(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof LengthMetrics
    }
    static isLengthMetricsUnit(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof LengthMetricsUnit
    }
    static isLengthUnit(value: object|string|number|undefined|null): boolean {
        return value instanceof LengthUnit
    }
    static isLetterSpacingStyle(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof LetterSpacingStyle
    }
    static isLightSource(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean): boolean {
        return value instanceof LightSource
    }
    static isLinearGradient(value: object|string|number|undefined|null): boolean {
        return value instanceof LinearGradient
    }
    static isLinearGradient_common(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof LinearGradient_common
    }
    static isLinearGradientBlurOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof LinearGradientBlurOptions
    }
    static isLinearIndicatorAttribute(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof LinearIndicatorAttribute
    }
    static isLinearIndicatorController(value: object|string|number|undefined|null): boolean {
        return value instanceof LinearIndicatorController
    }
    static isLinearIndicatorStartOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof LinearIndicatorStartOptions
    }
    static isLinearIndicatorStyle(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean): boolean {
        return value instanceof LinearIndicatorStyle
    }
    static isLinearStyleOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof LinearStyleOptions
    }
    static isLineAttribute(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof LineAttribute
    }
    static isLineBreakStrategy(value: object|string|number|undefined|null): boolean {
        return value instanceof LineBreakStrategy
    }
    static isLineCapStyle(value: object|string|number|undefined|null): boolean {
        return value instanceof LineCapStyle
    }
    static isLineHeightStyle(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof LineHeightStyle
    }
    static isLineJoinStyle(value: object|string|number|undefined|null): boolean {
        return value instanceof LineJoinStyle
    }
    static isLineMetrics(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof LineMetrics
    }
    static isLineOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof LineOptions
    }
    static isListAttribute(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean, arg9: boolean, arg10: boolean, arg11: boolean, arg12: boolean, arg13: boolean, arg14: boolean, arg15: boolean, arg16: boolean, arg17: boolean, arg18: boolean, arg19: boolean, arg20: boolean, arg21: boolean, arg22: boolean, arg23: boolean, arg24: boolean, arg25: boolean, arg26: boolean, arg27: boolean, arg28: boolean, arg29: boolean, arg30: boolean, arg31: boolean, arg32: boolean): boolean {
        return value instanceof ListAttribute
    }
    static isListDividerOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof ListDividerOptions
    }
    static isListItemAlign(value: object|string|number|undefined|null): boolean {
        return value instanceof ListItemAlign
    }
    static isListItemAttribute(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean): boolean {
        return value instanceof ListItemAttribute
    }
    static isListItemGroupArea(value: object|string|number|undefined|null): boolean {
        return value instanceof ListItemGroupArea
    }
    static isListItemGroupAttribute(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof ListItemGroupAttribute
    }
    static isListItemGroupOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean): boolean {
        return value instanceof ListItemGroupOptions
    }
    static isListItemGroupStyle(value: object|string|number|undefined|null): boolean {
        return value instanceof ListItemGroupStyle
    }
    static isListItemOptions(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof ListItemOptions
    }
    static isListItemStyle(value: object|string|number|undefined|null): boolean {
        return value instanceof ListItemStyle
    }
    static isListOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof ListOptions
    }
    static isListScroller(value: object|string|number|undefined|null): boolean {
        return value instanceof ListScroller
    }
    static isLiteral_Alignment_align(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof Literal_Alignment_align
    }
    static isLiteral_Boolean_isVisible(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof Literal_Boolean_isVisible
    }
    static isLiteral_Boolean_next_Axis_direction(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof Literal_Boolean_next_Axis_direction
    }
    static isLiteral_Empty(value: object|string|number|undefined|null): boolean {
        return value instanceof Literal_Empty
    }
    static isLiteral_Function_callback__Object_fileSelector(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof Literal_Function_callback__Object_fileSelector
    }
    static isLiteral_Function_handler_Object_error(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof Literal_Function_handler_Object_error
    }
    static isLiteral_Number_angle_fingers(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof Literal_Number_angle_fingers
    }
    static isLiteral_Number_code_Want_want(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof Literal_Number_code_Want_want
    }
    static isLiteral_Number_day_month_year(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof Literal_Number_day_month_year
    }
    static isLiteral_Number_distance_fingers(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof Literal_Number_distance_fingers
    }
    static isLiteral_Number_distance_fingers_PanDirection_direction(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof Literal_Number_distance_fingers_PanDirection_direction
    }
    static isLiteral_Number_duration_fingers_Boolean_repeat(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof Literal_Number_duration_fingers_Boolean_repeat
    }
    static isLiteral_Number_errcode_String_msg(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof Literal_Number_errcode_String_msg
    }
    static isLiteral_Number_fingers_speed_SwipeDirection_direction(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof Literal_Number_fingers_speed_SwipeDirection_direction
    }
    static isLiteral_Number_index(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof Literal_Number_index
    }
    static isLiteral_Number_offset_span(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof Literal_Number_offset_span
    }
    static isLiteral_Number_offsetRemain(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof Literal_Number_offsetRemain
    }
    static isLiteral_Number_surfaceHeight_surfaceWidth(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof Literal_Number_surfaceHeight_surfaceWidth
    }
    static isLiteral_Object_detail(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof Literal_Object_detail
    }
    static isLiteral_Object_object__String_name_Array_String_methodList(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof Literal_Object_object__String_name_Array_String_methodList
    }
    static isLiteral_ResourceColor_color(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof Literal_ResourceColor_color
    }
    static isLiteral_String_anchor_HorizontalAlign_align(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof Literal_String_anchor_HorizontalAlign_align
    }
    static isLiteral_String_anchor_VerticalAlign_align(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof Literal_String_anchor_VerticalAlign_align
    }
    static isLiteral_String_baseUrl_data_encoding_historyUrl_mimeType(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean): boolean {
        return value instanceof Literal_String_baseUrl_data_encoding_historyUrl_mimeType
    }
    static isLiteral_String_key_Any_defaultValue(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof Literal_String_key_Any_defaultValue
    }
    static isLiteral_String_plainText(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof Literal_String_plainText
    }
    static isLiteral_String_script_Callback_String_Void_callback_(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof Literal_String_script_Callback_String_Void_callback_
    }
    static isLiteral_String_target_NavigationType_type(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof Literal_String_target_NavigationType_type
    }
    static isLiteral_String_value_Callback_Void_action(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof Literal_String_value_Callback_Void_action
    }
    static isLiteral_TransitionEffect_appear_disappear(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof Literal_TransitionEffect_appear_disappear
    }
    static isLiteral_Union_Number_Literal_Number_offset_span_lg_md_sm_xs(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs
    }
    static isLiteral_Union_String_Resource_url_Array_Header_headers(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof Literal_Union_String_Resource_url_Array_Header_headers
    }
    static isLiteral_Union_String_WebResourceRequest_data(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof Literal_Union_String_WebResourceRequest_data
    }
    static isLiteral_Want_want(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof Literal_Want_want
    }
    static isLoadCommittedDetails(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean): boolean {
        return value instanceof LoadCommittedDetails
    }
    static isLoadingProgressAttribute(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof LoadingProgressAttribute
    }
    static isLoadingProgressConfiguration(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof LoadingProgressConfiguration
    }
    static isLoadingProgressStyle(value: object|string|number|undefined|null): boolean {
        return value instanceof LoadingProgressStyle
    }
    static isLocalizedAlignRuleOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean): boolean {
        return value instanceof LocalizedAlignRuleOptions
    }
    static isLocalizedBarrierDirection(value: object|string|number|undefined|null): boolean {
        return value instanceof LocalizedBarrierDirection
    }
    static isLocalizedBarrierStyle(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof LocalizedBarrierStyle
    }
    static isLocalizedBorderRadiuses(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof LocalizedBorderRadiuses
    }
    static isLocalizedEdgeColors(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof LocalizedEdgeColors
    }
    static isLocalizedEdges(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof LocalizedEdges
    }
    static isLocalizedEdgeWidths(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof LocalizedEdgeWidths
    }
    static isLocalizedHorizontalAlignParam(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof LocalizedHorizontalAlignParam
    }
    static isLocalizedPadding(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof LocalizedPadding
    }
    static isLocalizedPosition(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof LocalizedPosition
    }
    static isLocalizedVerticalAlignParam(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof LocalizedVerticalAlignParam
    }
    static isLocationButtonAttribute(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof LocationButtonAttribute
    }
    static isLocationButtonOnClickResult(value: object|string|number|undefined|null): boolean {
        return value instanceof LocationButtonOnClickResult
    }
    static isLocationButtonOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof LocationButtonOptions
    }
    static isLocationDescription(value: object|string|number|undefined|null): boolean {
        return value instanceof LocationDescription
    }
    static isLocationIconStyle(value: object|string|number|undefined|null): boolean {
        return value instanceof LocationIconStyle
    }
    static isLongPressGestureEvent(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof LongPressGestureEvent
    }
    static isLongPressGestureHandler(value: object|string|number|undefined|null): boolean {
        return value instanceof LongPressGestureHandler
    }
    static isLongPressGestureHandlerOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof LongPressGestureHandlerOptions
    }
    static isLongPressGestureInterface(value: object|string|number|undefined|null): boolean {
        return value instanceof LongPressGestureInterface
    }
    static isLunarSwitchStyle(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof LunarSwitchStyle
    }
    static isMarkStyle(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof MarkStyle
    }
    static isMarqueeAttribute(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean): boolean {
        return value instanceof MarqueeAttribute
    }
    static isMarqueeOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean): boolean {
        return value instanceof MarqueeOptions
    }
    static isMarqueeUpdateStrategy(value: object|string|number|undefined|null): boolean {
        return value instanceof MarqueeUpdateStrategy
    }
    static isMatrix2D(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean): boolean {
        return value instanceof Matrix2D
    }
    static isMeasurable(value: object|string|number|undefined|null): boolean {
        return value instanceof Measurable
    }
    static isMeasureOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean, arg9: boolean, arg10: boolean, arg11: boolean, arg12: boolean, arg13: boolean, arg14: boolean): boolean {
        return value instanceof MeasureOptions
    }
    static isMeasureResult(value: object|string|number|undefined|null): boolean {
        return value instanceof MeasureResult
    }
    static isMediaCachedImageAttribute(value: object|string|number|undefined|null): boolean {
        return value instanceof MediaCachedImageAttribute
    }
    static isMenuAlignType(value: object|string|number|undefined|null): boolean {
        return value instanceof MenuAlignType
    }
    static isMenuAttribute(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean): boolean {
        return value instanceof MenuAttribute
    }
    static isMenuElement(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean): boolean {
        return value instanceof MenuElement
    }
    static isMenuItemAttribute(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean): boolean {
        return value instanceof MenuItemAttribute
    }
    static isMenuItemConfiguration(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean): boolean {
        return value instanceof MenuItemConfiguration
    }
    static isMenuItemGroupAttribute(value: object|string|number|undefined|null): boolean {
        return value instanceof MenuItemGroupAttribute
    }
    static isMenuItemGroupOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof MenuItemGroupOptions
    }
    static isMenuItemOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean): boolean {
        return value instanceof MenuItemOptions
    }
    static isMenuOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof MenuOptions
    }
    static isMenuPolicy(value: object|string|number|undefined|null): boolean {
        return value instanceof MenuPolicy
    }
    static isMenuPreviewMode(value: object|string|number|undefined|null): boolean {
        return value instanceof MenuPreviewMode
    }
    static isMenuType(value: object|string|number|undefined|null): boolean {
        return value instanceof MenuType
    }
    static isMessageLevel(value: object|string|number|undefined|null): boolean {
        return value instanceof MessageLevel
    }
    static isMixedMode(value: object|string|number|undefined|null): boolean {
        return value instanceof MixedMode
    }
    static isModalTransition(value: object|string|number|undefined|null): boolean {
        return value instanceof ModalTransition
    }
    static isModelType(value: object|string|number|undefined|null): boolean {
        return value instanceof ModelType
    }
    static isModifierKey(value: object|string|number|undefined|null): boolean {
        return value instanceof ModifierKey
    }
    static isMonthData(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof MonthData
    }
    static isMotionBlurAnchor(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof MotionBlurAnchor
    }
    static isMotionBlurOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof MotionBlurOptions
    }
    static isMotionPathOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof MotionPathOptions
    }
    static isMouseAction(value: object|string|number|undefined|null): boolean {
        return value instanceof MouseAction
    }
    static isMouseButton(value: object|string|number|undefined|null): boolean {
        return value instanceof MouseButton
    }
    static isMouseEvent(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean, arg9: boolean, arg10: boolean): boolean {
        return value instanceof MouseEvent
    }
    static isMoveIndex(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof MoveIndex
    }
    static isMultiShadowOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof MultiShadowOptions
    }
    static isMutableStyledString(value: object|string|number|undefined|null): boolean {
        return value instanceof MutableStyledString
    }
    static isNativeEmbedDataInfo(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof NativeEmbedDataInfo
    }
    static isNativeEmbedInfo(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean): boolean {
        return value instanceof NativeEmbedInfo
    }
    static isNativeEmbedStatus(value: object|string|number|undefined|null): boolean {
        return value instanceof NativeEmbedStatus
    }
    static isNativeEmbedTouchInfo(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof NativeEmbedTouchInfo
    }
    static isNativeEmbedVisibilityInfo(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof NativeEmbedVisibilityInfo
    }
    static isNativeMediaPlayerConfig(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof NativeMediaPlayerConfig
    }
    static isNavBarPosition(value: object|string|number|undefined|null): boolean {
        return value instanceof NavBarPosition
    }
    static isNavContentInfo(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean): boolean {
        return value instanceof NavContentInfo
    }
    static isNavDestinationAttribute(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean, arg9: boolean, arg10: boolean, arg11: boolean, arg12: boolean, arg13: boolean, arg14: boolean): boolean {
        return value instanceof NavDestinationAttribute
    }
    static isNavDestinationCommonTitle(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof NavDestinationCommonTitle
    }
    static isNavDestinationContext(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof NavDestinationContext
    }
    static isNavDestinationCustomTitle(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof NavDestinationCustomTitle
    }
    static isNavDestinationInfo(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof NavDestinationInfo
    }
    static isNavDestinationMode(value: object|string|number|undefined|null): boolean {
        return value instanceof NavDestinationMode
    }
    static isNavExtender(value: object|string|number|undefined|null): boolean {
        return value instanceof NavExtender
    }
    static isNavigationAnimatedTransition(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof NavigationAnimatedTransition
    }
    static isNavigationAttribute(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean, arg9: boolean, arg10: boolean, arg11: boolean, arg12: boolean, arg13: boolean, arg14: boolean, arg15: boolean, arg16: boolean, arg17: boolean, arg18: boolean, arg19: boolean, arg20: boolean, arg21: boolean): boolean {
        return value instanceof NavigationAttribute
    }
    static isNavigationCommonTitle(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof NavigationCommonTitle
    }
    static isNavigationCustomTitle(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof NavigationCustomTitle
    }
    static isNavigationInfo(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof NavigationInfo
    }
    static isNavigationInterception(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof NavigationInterception
    }
    static isNavigationInterface(value: object|string|number|undefined|null): boolean {
        return value instanceof NavigationInterface
    }
    static isNavigationMenuItem(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean): boolean {
        return value instanceof NavigationMenuItem
    }
    static isNavigationMode(value: object|string|number|undefined|null): boolean {
        return value instanceof NavigationMode
    }
    static isNavigationOperation(value: object|string|number|undefined|null): boolean {
        return value instanceof NavigationOperation
    }
    static isNavigationOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof NavigationOptions
    }
    static isNavigationSystemTransitionType(value: object|string|number|undefined|null): boolean {
        return value instanceof NavigationSystemTransitionType
    }
    static isNavigationTitleMode(value: object|string|number|undefined|null): boolean {
        return value instanceof NavigationTitleMode
    }
    static isNavigationTitleOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean): boolean {
        return value instanceof NavigationTitleOptions
    }
    static isNavigationToolbarOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof NavigationToolbarOptions
    }
    static isNavigationTransitionProxy(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof NavigationTransitionProxy
    }
    static isNavigationType(value: object|string|number|undefined|null): boolean {
        return value instanceof NavigationType
    }
    static isNavigatorAttribute(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof NavigatorAttribute
    }
    static isNavPathInfo(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof NavPathInfo
    }
    static isNavPathStack(value: object|string|number|undefined|null): boolean {
        return value instanceof NavPathStack
    }
    static isNavRouteMode(value: object|string|number|undefined|null): boolean {
        return value instanceof NavRouteMode
    }
    static isNavRouterAttribute(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof NavRouterAttribute
    }
    static isNestedScrollMode(value: object|string|number|undefined|null): boolean {
        return value instanceof NestedScrollMode
    }
    static isNestedScrollOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof NestedScrollOptions
    }
    static isNestedScrollOptionsExt(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof NestedScrollOptionsExt
    }
    static isNodeContainerAttribute(value: object|string|number|undefined|null): boolean {
        return value instanceof NodeContainerAttribute
    }
    static isNodeController(value: object|string|number|undefined|null): boolean {
        return value instanceof NodeController
    }
    static isNonCurrentDayStyle(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof NonCurrentDayStyle
    }
    static isObscuredReasons(value: object|string|number|undefined|null): boolean {
        return value instanceof ObscuredReasons
    }
    static isOffscreenCanvas(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof OffscreenCanvas
    }
    static isOffscreenCanvasRenderingContext2D(value: object|string|number|undefined|null): boolean {
        return value instanceof OffscreenCanvasRenderingContext2D
    }
    static isOffset(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof Offset
    }
    static isOffsetOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof OffsetOptions
    }
    static isOffsetResult(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof OffsetResult
    }
    static isOnAlertEvent(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof OnAlertEvent
    }
    static isOnAudioStateChangedEvent(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof OnAudioStateChangedEvent
    }
    static isOnBeforeUnloadEvent(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof OnBeforeUnloadEvent
    }
    static isOnClientAuthenticationEvent(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean): boolean {
        return value instanceof OnClientAuthenticationEvent
    }
    static isOnConfirmEvent(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof OnConfirmEvent
    }
    static isOnConsoleEvent(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof OnConsoleEvent
    }
    static isOnContextMenuShowEvent(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof OnContextMenuShowEvent
    }
    static isOnDataResubmittedEvent(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof OnDataResubmittedEvent
    }
    static isOnDownloadStartEvent(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean): boolean {
        return value instanceof OnDownloadStartEvent
    }
    static isOnErrorReceiveEvent(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof OnErrorReceiveEvent
    }
    static isOnFaviconReceivedEvent(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof OnFaviconReceivedEvent
    }
    static isOnFirstContentfulPaintEvent(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof OnFirstContentfulPaintEvent
    }
    static isOnFoldStatusChangeInfo(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof OnFoldStatusChangeInfo
    }
    static isOnGeolocationShowEvent(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof OnGeolocationShowEvent
    }
    static isOnHttpAuthRequestEvent(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof OnHttpAuthRequestEvent
    }
    static isOnHttpErrorReceiveEvent(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof OnHttpErrorReceiveEvent
    }
    static isOnInterceptRequestEvent(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof OnInterceptRequestEvent
    }
    static isOnLoadInterceptEvent(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof OnLoadInterceptEvent
    }
    static isOnOverScrollEvent(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof OnOverScrollEvent
    }
    static isOnPageBeginEvent(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof OnPageBeginEvent
    }
    static isOnPageEndEvent(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof OnPageEndEvent
    }
    static isOnPageVisibleEvent(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof OnPageVisibleEvent
    }
    static isOnPermissionRequestEvent(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof OnPermissionRequestEvent
    }
    static isOnProgressChangeEvent(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof OnProgressChangeEvent
    }
    static isOnPromptEvent(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof OnPromptEvent
    }
    static isOnRefreshAccessedHistoryEvent(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof OnRefreshAccessedHistoryEvent
    }
    static isOnRenderExitedEvent(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof OnRenderExitedEvent
    }
    static isOnResourceLoadEvent(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof OnResourceLoadEvent
    }
    static isOnScaleChangeEvent(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof OnScaleChangeEvent
    }
    static isOnScreenCaptureRequestEvent(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof OnScreenCaptureRequestEvent
    }
    static isOnScrollEvent(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof OnScrollEvent
    }
    static isOnScrollFrameBeginHandlerResult(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof OnScrollFrameBeginHandlerResult
    }
    static isOnSearchResultReceiveEvent(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof OnSearchResultReceiveEvent
    }
    static isOnShowFileSelectorEvent(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof OnShowFileSelectorEvent
    }
    static isOnSslErrorEventReceiveEvent(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof OnSslErrorEventReceiveEvent
    }
    static isOnTitleReceiveEvent(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof OnTitleReceiveEvent
    }
    static isOnTouchIconUrlReceivedEvent(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof OnTouchIconUrlReceivedEvent
    }
    static isOnWillScrollCallback(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof OnWillScrollCallback
    }
    static isOnWindowNewEvent(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof OnWindowNewEvent
    }
    static isOptionWidthMode(value: object|string|number|undefined|null): boolean {
        return value instanceof OptionWidthMode
    }
    static isOutlineOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof OutlineOptions
    }
    static isOutlineRadiuses(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof OutlineRadiuses
    }
    static isOutlineStyle(value: object|string|number|undefined|null): boolean {
        return value instanceof OutlineStyle
    }
    static isOverlayOffset(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof OverlayOffset
    }
    static isOverlayOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof OverlayOptions
    }
    static isOverScrollMode(value: object|string|number|undefined|null): boolean {
        return value instanceof OverScrollMode
    }
    static isPadding(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof Padding
    }
    static isPageTransitionEnterInterface(value: object|string|number|undefined|null): boolean {
        return value instanceof PageTransitionEnterInterface
    }
    static isPageTransitionExitInterface(value: object|string|number|undefined|null): boolean {
        return value instanceof PageTransitionExitInterface
    }
    static isPageTransitionOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof PageTransitionOptions
    }
    static isPanDirection(value: object|string|number|undefined|null): boolean {
        return value instanceof PanDirection
    }
    static isPanelAttribute(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean, arg9: boolean, arg10: boolean, arg11: boolean): boolean {
        return value instanceof PanelAttribute
    }
    static isPanelHeight(value: object|string|number|undefined|null): boolean {
        return value instanceof PanelHeight
    }
    static isPanelMode(value: object|string|number|undefined|null): boolean {
        return value instanceof PanelMode
    }
    static isPanelType(value: object|string|number|undefined|null): boolean {
        return value instanceof PanelType
    }
    static isPanGestureEvent(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean): boolean {
        return value instanceof PanGestureEvent
    }
    static isPanGestureHandler(value: object|string|number|undefined|null): boolean {
        return value instanceof PanGestureHandler
    }
    static isPanGestureHandlerOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof PanGestureHandlerOptions
    }
    static isPanGestureInterface(value: object|string|number|undefined|null): boolean {
        return value instanceof PanGestureInterface
    }
    static isPanGestureOptions(value: object|string|number|undefined|null): boolean {
        return value instanceof PanGestureOptions
    }
    static isPanRecognizer(value: object|string|number|undefined|null): boolean {
        return value instanceof PanRecognizer
    }
    static isParagraphStyle(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean): boolean {
        return value instanceof ParagraphStyle
    }
    static isParagraphStyleInterface(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean): boolean {
        return value instanceof ParagraphStyleInterface
    }
    static isParticleColorOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof ParticleColorOptions
    }
    static isParticleColorPropertyUpdaterConfigs(value: object|string|number|undefined|null): boolean {
        return value instanceof ParticleColorPropertyUpdaterConfigs
    }
    static isParticleColorUpdaterOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof ParticleColorUpdaterOptions
    }
    static isParticleConfigs(value: object|string|number|undefined|null): boolean {
        return value instanceof ParticleConfigs
    }
    static isParticleEmitterShape(value: object|string|number|undefined|null): boolean {
        return value instanceof ParticleEmitterShape
    }
    static isParticlePropertyAnimation(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean): boolean {
        return value instanceof ParticlePropertyAnimation
    }
    static isParticlePropertyUpdaterConfigs(value: object|string|number|undefined|null): boolean {
        return value instanceof ParticlePropertyUpdaterConfigs
    }
    static isParticleType(value: object|string|number|undefined|null): boolean {
        return value instanceof ParticleType
    }
    static isParticleUpdater(value: object|string|number|undefined|null): boolean {
        return value instanceof ParticleUpdater
    }
    static isParticleUpdaterOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof ParticleUpdaterOptions
    }
    static isPasswordIcon(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof PasswordIcon
    }
    static isPasteButtonAttribute(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof PasteButtonAttribute
    }
    static isPasteButtonOnClickResult(value: object|string|number|undefined|null): boolean {
        return value instanceof PasteButtonOnClickResult
    }
    static isPasteButtonOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof PasteButtonOptions
    }
    static isPasteDescription(value: object|string|number|undefined|null): boolean {
        return value instanceof PasteDescription
    }
    static isPasteEvent(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof PasteEvent
    }
    static isPasteIconStyle(value: object|string|number|undefined|null): boolean {
        return value instanceof PasteIconStyle
    }
    static isPath2D(value: object|string|number|undefined|null): boolean {
        return value instanceof Path2D
    }
    static isPathAttribute(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof PathAttribute
    }
    static isPathOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof PathOptions
    }
    static isPathShape(value: object|string|number|undefined|null): boolean {
        return value instanceof PathShape
    }
    static isPathShapeOptions(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof PathShapeOptions
    }
    static isPatternLockAttribute(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean, arg9: boolean, arg10: boolean, arg11: boolean): boolean {
        return value instanceof PatternLockAttribute
    }
    static isPatternLockChallengeResult(value: object|string|number|undefined|null): boolean {
        return value instanceof PatternLockChallengeResult
    }
    static isPatternLockController(value: object|string|number|undefined|null): boolean {
        return value instanceof PatternLockController
    }
    static isPerfMonitorActionType(value: object|string|number|undefined|null): boolean {
        return value instanceof PerfMonitorActionType
    }
    static isPerfMonitorSourceType(value: object|string|number|undefined|null): boolean {
        return value instanceof PerfMonitorSourceType
    }
    static isPermissionRequest(value: object|string|number|undefined|null): boolean {
        return value instanceof PermissionRequest
    }
    static isPersistPropsOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof PersistPropsOptions
    }
    static isPickerDialogButtonStyle(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean, arg9: boolean, arg10: boolean): boolean {
        return value instanceof PickerDialogButtonStyle
    }
    static isPickerTextStyle(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof PickerTextStyle
    }
    static isPinchGestureEvent(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof PinchGestureEvent
    }
    static isPinchGestureHandler(value: object|string|number|undefined|null): boolean {
        return value instanceof PinchGestureHandler
    }
    static isPinchGestureHandlerOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof PinchGestureHandlerOptions
    }
    static isPinchGestureInterface(value: object|string|number|undefined|null): boolean {
        return value instanceof PinchGestureInterface
    }
    static isPixelMap(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof PixelMap
    }
    static isPixelMapMock(value: object|string|number|undefined|null): boolean {
        return value instanceof PixelMapMock
    }
    static isPixelRoundCalcPolicy(value: object|string|number|undefined|null): boolean {
        return value instanceof PixelRoundCalcPolicy
    }
    static isPixelRoundPolicy(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof PixelRoundPolicy
    }
    static isPixelStretchEffectOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof PixelStretchEffectOptions
    }
    static isPlaceholderStyle(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof PlaceholderStyle
    }
    static isPlacement(value: object|string|number|undefined|null): boolean {
        return value instanceof Placement
    }
    static isPlaybackInfo(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof PlaybackInfo
    }
    static isPlaybackSpeed(value: object|string|number|undefined|null): boolean {
        return value instanceof PlaybackSpeed
    }
    static isPlayMode(value: object|string|number|undefined|null): boolean {
        return value instanceof PlayMode
    }
    static isPluginComponentAttribute(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof PluginComponentAttribute
    }
    static isPluginComponentOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof PluginComponentOptions
    }
    static isPluginComponentTemplate(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof PluginComponentTemplate
    }
    static isPluginErrorData(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof PluginErrorData
    }
    static isPoint(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof Point
    }
    static isPointerStyle(value: object|string|number|undefined|null): boolean {
        return value instanceof PointerStyle
    }
    static isPointLightStyle(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof PointLightStyle
    }
    static isPointParticleParameters(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof PointParticleParameters
    }
    static isPolygonAttribute(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof PolygonAttribute
    }
    static isPolygonOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof PolygonOptions
    }
    static isPolylineAttribute(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof PolylineAttribute
    }
    static isPolylineOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof PolylineOptions
    }
    static isPopInfo(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof PopInfo
    }
    static isPopupMessageOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof PopupMessageOptions
    }
    static isPopupOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean, arg9: boolean, arg10: boolean, arg11: boolean, arg12: boolean, arg13: boolean, arg14: boolean, arg15: boolean, arg16: boolean, arg17: boolean, arg18: boolean, arg19: boolean, arg20: boolean, arg21: boolean, arg22: boolean, arg23: boolean, arg24: boolean, arg25: boolean): boolean {
        return value instanceof PopupOptions
    }
    static isPosition(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof Position
    }
    static isPositionWithAffinity(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof PositionWithAffinity
    }
    static isPreDragStatus(value: object|string|number|undefined|null): boolean {
        return value instanceof PreDragStatus
    }
    static isPreparedInfo(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof PreparedInfo
    }
    static isPreviewParams(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean): boolean {
        return value instanceof PreviewParams
    }
    static isPreviewText(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof PreviewText
    }
    static isProgressAttribute(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean): boolean {
        return value instanceof ProgressAttribute
    }
    static isProgressConfiguration(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof ProgressConfiguration
    }
    static isProgressMask(value: object|string|number|undefined|null): boolean {
        return value instanceof ProgressMask
    }
    static isProgressOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof ProgressOptions
    }
    static isProgressStatus(value: object|string|number|undefined|null): boolean {
        return value instanceof ProgressStatus
    }
    static isProgressStyle(value: object|string|number|undefined|null): boolean {
        return value instanceof ProgressStyle
    }
    static isProgressStyleMap(value: object|string|number|undefined|null): boolean {
        return value instanceof ProgressStyleMap
    }
    static isProgressStyleOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof ProgressStyleOptions
    }
    static isProgressType(value: object|string|number|undefined|null): boolean {
        return value instanceof ProgressType
    }
    static isProtectedResourceType(value: object|string|number|undefined|null): boolean {
        return value instanceof ProtectedResourceType
    }
    static isProvideOptions(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof ProvideOptions
    }
    static isPulseSymbolEffect(value: object|string|number|undefined|null): boolean {
        return value instanceof PulseSymbolEffect
    }
    static isQRCodeAttribute(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof QRCodeAttribute
    }
    static isRadioAttribute(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof RadioAttribute
    }
    static isRadioConfiguration(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof RadioConfiguration
    }
    static isRadioIndicatorType(value: object|string|number|undefined|null): boolean {
        return value instanceof RadioIndicatorType
    }
    static isRadioOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof RadioOptions
    }
    static isRadioStyle(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof RadioStyle
    }
    static isRatingAttribute(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean): boolean {
        return value instanceof RatingAttribute
    }
    static isRatingConfiguration(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean): boolean {
        return value instanceof RatingConfiguration
    }
    static isRatingOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof RatingOptions
    }
    static isRawFileDescriptor(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof RawFileDescriptor
    }
    static isReceiveCallback(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof ReceiveCallback
    }
    static isRectangle(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof Rectangle
    }
    static isRectAttribute(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof RectAttribute
    }
    static isRectHeightStyle(value: object|string|number|undefined|null): boolean {
        return value instanceof RectHeightStyle
    }
    static isRectOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof RectOptions
    }
    static isRectResult(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof RectResult
    }
    static isRectShape(value: object|string|number|undefined|null): boolean {
        return value instanceof RectShape
    }
    static isRectShapeOptions(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof RectShapeOptions
    }
    static isRectWidthStyle(value: object|string|number|undefined|null): boolean {
        return value instanceof RectWidthStyle
    }
    static isRefreshAttribute(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean): boolean {
        return value instanceof RefreshAttribute
    }
    static isRefreshOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean): boolean {
        return value instanceof RefreshOptions
    }
    static isRefreshStatus(value: object|string|number|undefined|null): boolean {
        return value instanceof RefreshStatus
    }
    static isRelateType(value: object|string|number|undefined|null): boolean {
        return value instanceof RelateType
    }
    static isRelativeContainerAttribute(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof RelativeContainerAttribute
    }
    static isRemoteWindowAttribute(value: object|string|number|undefined|null): boolean {
        return value instanceof RemoteWindowAttribute
    }
    static isRenderExitReason(value: object|string|number|undefined|null): boolean {
        return value instanceof RenderExitReason
    }
    static isRenderFit(value: object|string|number|undefined|null): boolean {
        return value instanceof RenderFit
    }
    static isRenderingContextSettings(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof RenderingContextSettings
    }
    static isRenderMode(value: object|string|number|undefined|null): boolean {
        return value instanceof RenderMode
    }
    static isRenderProcessNotRespondingData(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof RenderProcessNotRespondingData
    }
    static isRenderProcessNotRespondingReason(value: object|string|number|undefined|null): boolean {
        return value instanceof RenderProcessNotRespondingReason
    }
    static isRepeatMode(value: object|string|number|undefined|null): boolean {
        return value instanceof RepeatMode
    }
    static isReplaceSymbolEffect(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof ReplaceSymbolEffect
    }
    static isResizableOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof ResizableOptions
    }
    static isResolutionQuality(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof ResolutionQuality
    }
    static isResource(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean): boolean {
        return value instanceof Resource
    }
    static isResponseType(value: object|string|number|undefined|null): boolean {
        return value instanceof ResponseType
    }
    static isRestrictedWorker(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof RestrictedWorker
    }
    static isRichEditorAttribute(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean, arg9: boolean, arg10: boolean, arg11: boolean, arg12: boolean, arg13: boolean, arg14: boolean, arg15: boolean, arg16: boolean, arg17: boolean, arg18: boolean, arg19: boolean, arg20: boolean, arg21: boolean, arg22: boolean, arg23: boolean, arg24: boolean, arg25: boolean): boolean {
        return value instanceof RichEditorAttribute
    }
    static isRichEditorBaseController(value: object|string|number|undefined|null): boolean {
        return value instanceof RichEditorBaseController
    }
    static isRichEditorBuilderSpanOptions(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof RichEditorBuilderSpanOptions
    }
    static isRichEditorChangeValue(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof RichEditorChangeValue
    }
    static isRichEditorController(value: object|string|number|undefined|null): boolean {
        return value instanceof RichEditorController
    }
    static isRichEditorDeleteDirection(value: object|string|number|undefined|null): boolean {
        return value instanceof RichEditorDeleteDirection
    }
    static isRichEditorDeleteValue(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof RichEditorDeleteValue
    }
    static isRichEditorGesture(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof RichEditorGesture
    }
    static isRichEditorImageSpan(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof RichEditorImageSpan
    }
    static isRichEditorImageSpanOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof RichEditorImageSpanOptions
    }
    static isRichEditorImageSpanResult(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean): boolean {
        return value instanceof RichEditorImageSpanResult
    }
    static isRichEditorImageSpanStyle(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof RichEditorImageSpanStyle
    }
    static isRichEditorImageSpanStyleResult(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof RichEditorImageSpanStyleResult
    }
    static isRichEditorInsertValue(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof RichEditorInsertValue
    }
    static isRichEditorLayoutStyle(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof RichEditorLayoutStyle
    }
    static isRichEditorOptions(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof RichEditorOptions
    }
    static isRichEditorParagraphResult(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof RichEditorParagraphResult
    }
    static isRichEditorParagraphStyle(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof RichEditorParagraphStyle
    }
    static isRichEditorParagraphStyleOptions(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof RichEditorParagraphStyleOptions
    }
    static isRichEditorRange(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof RichEditorRange
    }
    static isRichEditorResponseType(value: object|string|number|undefined|null): boolean {
        return value instanceof RichEditorResponseType
    }
    static isRichEditorSelection(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof RichEditorSelection
    }
    static isRichEditorSpanPosition(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof RichEditorSpanPosition
    }
    static isRichEditorSpanStyleOptions(value: object|string|number|undefined|null): boolean {
        return value instanceof RichEditorSpanStyleOptions
    }
    static isRichEditorSpanType(value: object|string|number|undefined|null): boolean {
        return value instanceof RichEditorSpanType
    }
    static isRichEditorStyledStringController(value: object|string|number|undefined|null): boolean {
        return value instanceof RichEditorStyledStringController
    }
    static isRichEditorStyledStringOptions(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof RichEditorStyledStringOptions
    }
    static isRichEditorSymbolSpanOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof RichEditorSymbolSpanOptions
    }
    static isRichEditorSymbolSpanStyle(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean): boolean {
        return value instanceof RichEditorSymbolSpanStyle
    }
    static isRichEditorSymbolSpanStyleResult(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean): boolean {
        return value instanceof RichEditorSymbolSpanStyleResult
    }
    static isRichEditorTextSpan(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof RichEditorTextSpan
    }
    static isRichEditorTextSpanOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof RichEditorTextSpanOptions
    }
    static isRichEditorTextSpanResult(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean): boolean {
        return value instanceof RichEditorTextSpanResult
    }
    static isRichEditorTextStyle(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean, arg9: boolean): boolean {
        return value instanceof RichEditorTextStyle
    }
    static isRichEditorTextStyleResult(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean, arg9: boolean): boolean {
        return value instanceof RichEditorTextStyleResult
    }
    static isRichEditorUpdateImageSpanStyleOptions(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof RichEditorUpdateImageSpanStyleOptions
    }
    static isRichEditorUpdateSymbolSpanStyleOptions(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof RichEditorUpdateSymbolSpanStyleOptions
    }
    static isRichEditorUpdateTextSpanStyleOptions(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof RichEditorUpdateTextSpanStyleOptions
    }
    static isRichTextAttribute(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof RichTextAttribute
    }
    static isRingStyleOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof RingStyleOptions
    }
    // static isRoot(value: object|string|number|undefined|null): boolean {
    //     return value instanceof Root
    // }
    static isRootSceneAttribute(value: object|string|number|undefined|null): boolean {
        return value instanceof RootSceneAttribute
    }
    static isRootSceneSession(value: object|string|number|undefined|null): boolean {
        return value instanceof RootSceneSession
    }
    static isRotateOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean): boolean {
        return value instanceof RotateOptions
    }
    static isRotationGestureEvent(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof RotationGestureEvent
    }
    static isRotationGestureHandler(value: object|string|number|undefined|null): boolean {
        return value instanceof RotationGestureHandler
    }
    static isRotationGestureHandlerOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof RotationGestureHandlerOptions
    }
    static isRotationGestureInterface(value: object|string|number|undefined|null): boolean {
        return value instanceof RotationGestureInterface
    }
    static isRoundedRectOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof RoundedRectOptions
    }
    static isRoundRectShapeOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof RoundRectShapeOptions
    }
    static isRouteInfo(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof RouteInfo
    }
    static isRouteMapConfig(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof RouteMapConfig
    }
    static isRouterPageInfo(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof RouterPageInfo
    }
    static isRouteType(value: object|string|number|undefined|null): boolean {
        return value instanceof RouteType
    }
    static isRowAttribute(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof RowAttribute
    }
    static isRowOptions(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof RowOptions
    }
    static isRowSplitAttribute(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof RowSplitAttribute
    }
    static isRRect(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean): boolean {
        return value instanceof RRect
    }
    static isSafeAreaEdge(value: object|string|number|undefined|null): boolean {
        return value instanceof SafeAreaEdge
    }
    static isSafeAreaType(value: object|string|number|undefined|null): boolean {
        return value instanceof SafeAreaType
    }
    static isSaveButtonAttribute(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof SaveButtonAttribute
    }
    static isSaveButtonOnClickResult(value: object|string|number|undefined|null): boolean {
        return value instanceof SaveButtonOnClickResult
    }
    static isSaveButtonOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof SaveButtonOptions
    }
    static isSaveDescription(value: object|string|number|undefined|null): boolean {
        return value instanceof SaveDescription
    }
    static isSaveIconStyle(value: object|string|number|undefined|null): boolean {
        return value instanceof SaveIconStyle
    }
    static isScaleOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean): boolean {
        return value instanceof ScaleOptions
    }
    static isScaleRingStyleOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof ScaleRingStyleOptions
    }
    static isScaleSymbolEffect(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof ScaleSymbolEffect
    }
    static isScanEffectOptions(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof ScanEffectOptions
    }
    static isScene(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof Scene
    }
    static isSceneOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof SceneOptions
    }
    static isScreenAttribute(value: object|string|number|undefined|null): boolean {
        return value instanceof ScreenAttribute
    }
    static isScreenCaptureConfig(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof ScreenCaptureConfig
    }
    static isScreenCaptureHandler(value: object|string|number|undefined|null): boolean {
        return value instanceof ScreenCaptureHandler
    }
    static isScriptItem(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof ScriptItem
    }
    static isScrollableBarModeOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof ScrollableBarModeOptions
    }
    static isScrollableCommonMethod(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean, arg9: boolean, arg10: boolean, arg11: boolean, arg12: boolean, arg13: boolean, arg14: boolean): boolean {
        return value instanceof ScrollableCommonMethod
    }
    static isScrollableTargetInfo(value: object|string|number|undefined|null): boolean {
        return value instanceof ScrollableTargetInfo
    }
    static isScrollAlign(value: object|string|number|undefined|null): boolean {
        return value instanceof ScrollAlign
    }
    static isScrollAnimationOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof ScrollAnimationOptions
    }
    static isScrollAttribute(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean, arg9: boolean, arg10: boolean, arg11: boolean, arg12: boolean, arg13: boolean, arg14: boolean, arg15: boolean, arg16: boolean, arg17: boolean): boolean {
        return value instanceof ScrollAttribute
    }
    static isScrollBarAttribute(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof ScrollBarAttribute
    }
    static isScrollBarDirection(value: object|string|number|undefined|null): boolean {
        return value instanceof ScrollBarDirection
    }
    static isScrollBarOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof ScrollBarOptions
    }
    static isScrollDirection(value: object|string|number|undefined|null): boolean {
        return value instanceof ScrollDirection
    }
    static isScrollEdgeOptions(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof ScrollEdgeOptions
    }
    static isScroller(value: object|string|number|undefined|null): boolean {
        return value instanceof Scroller
    }
    static isScrollMotion(value: object|string|number|undefined|null): boolean {
        return value instanceof ScrollMotion
    }
    static isScrollOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof ScrollOptions
    }
    static isScrollPageOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof ScrollPageOptions
    }
    static isScrollResult(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof ScrollResult
    }
    static isScrollSizeMode(value: object|string|number|undefined|null): boolean {
        return value instanceof ScrollSizeMode
    }
    static isScrollSnapAlign(value: object|string|number|undefined|null): boolean {
        return value instanceof ScrollSnapAlign
    }
    static isScrollSnapOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof ScrollSnapOptions
    }
    static isScrollSource(value: object|string|number|undefined|null): boolean {
        return value instanceof ScrollSource
    }
    static isScrollState(value: object|string|number|undefined|null): boolean {
        return value instanceof ScrollState
    }
    static isScrollToIndexOptions(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof ScrollToIndexOptions
    }
    static isSearchAttribute(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean, arg9: boolean, arg10: boolean, arg11: boolean, arg12: boolean, arg13: boolean, arg14: boolean, arg15: boolean, arg16: boolean, arg17: boolean, arg18: boolean, arg19: boolean, arg20: boolean, arg21: boolean, arg22: boolean, arg23: boolean, arg24: boolean, arg25: boolean, arg26: boolean, arg27: boolean, arg28: boolean, arg29: boolean, arg30: boolean, arg31: boolean, arg32: boolean, arg33: boolean, arg34: boolean, arg35: boolean, arg36: boolean): boolean {
        return value instanceof SearchAttribute
    }
    static isSearchButtonOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof SearchButtonOptions
    }
    static isSearchController(value: object|string|number|undefined|null): boolean {
        return value instanceof SearchController
    }
    static isSearchOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof SearchOptions
    }
    static isSearchType(value: object|string|number|undefined|null): boolean {
        return value instanceof SearchType
    }
    static isSectionOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean): boolean {
        return value instanceof SectionOptions
    }
    static isSecurityComponentLayoutDirection(value: object|string|number|undefined|null): boolean {
        return value instanceof SecurityComponentLayoutDirection
    }
    static isSecurityComponentMethod(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean, arg9: boolean, arg10: boolean, arg11: boolean, arg12: boolean, arg13: boolean, arg14: boolean, arg15: boolean, arg16: boolean, arg17: boolean, arg18: boolean, arg19: boolean, arg20: boolean, arg21: boolean, arg22: boolean): boolean {
        return value instanceof SecurityComponentMethod
    }
    static isSeekMode(value: object|string|number|undefined|null): boolean {
        return value instanceof SeekMode
    }
    static isSelectAttribute(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean, arg9: boolean, arg10: boolean, arg11: boolean, arg12: boolean, arg13: boolean, arg14: boolean, arg15: boolean, arg16: boolean, arg17: boolean, arg18: boolean, arg19: boolean): boolean {
        return value instanceof SelectAttribute
    }
    static isSelectedMode(value: object|string|number|undefined|null): boolean {
        return value instanceof SelectedMode
    }
    static isSelectionMenuOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof SelectionMenuOptions
    }
    static isSelectionMenuOptionsExt(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof SelectionMenuOptionsExt
    }
    static isSelectionOptions(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof SelectionOptions
    }
    static isSelectOption(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof SelectOption
    }
    static isSelectStatus(value: object|string|number|undefined|null): boolean {
        return value instanceof SelectStatus
    }
    static isShadowOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean): boolean {
        return value instanceof ShadowOptions
    }
    static isShadowStyle(value: object|string|number|undefined|null): boolean {
        return value instanceof ShadowStyle
    }
    static isShadowType(value: object|string|number|undefined|null): boolean {
        return value instanceof ShadowType
    }
    static isShapeAttribute(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean, arg9: boolean, arg10: boolean, arg11: boolean): boolean {
        return value instanceof ShapeAttribute
    }
    static isShapeSize(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof ShapeSize
    }
    static isSharedTransitionEffectType(value: object|string|number|undefined|null): boolean {
        return value instanceof SharedTransitionEffectType
    }
    static issharedTransitionOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean): boolean {
        return value instanceof sharedTransitionOptions
    }
    static isSheetDismiss(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof SheetDismiss
    }
    static isSheetInfo(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof SheetInfo
    }
    static isSheetKeyboardAvoidMode(value: object|string|number|undefined|null): boolean {
        return value instanceof SheetKeyboardAvoidMode
    }
    static isSheetMode(value: object|string|number|undefined|null): boolean {
        return value instanceof SheetMode
    }
    static isSheetOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean, arg9: boolean, arg10: boolean, arg11: boolean, arg12: boolean, arg13: boolean, arg14: boolean, arg15: boolean, arg16: boolean, arg17: boolean, arg18: boolean, arg19: boolean, arg20: boolean, arg21: boolean, arg22: boolean, arg23: boolean, arg24: boolean): boolean {
        return value instanceof SheetOptions
    }
    static isSheetSize(value: object|string|number|undefined|null): boolean {
        return value instanceof SheetSize
    }
    static isSheetTitleOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof SheetTitleOptions
    }
    static isSheetType(value: object|string|number|undefined|null): boolean {
        return value instanceof SheetType
    }
    static isSideBarContainerAttribute(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean, arg9: boolean, arg10: boolean): boolean {
        return value instanceof SideBarContainerAttribute
    }
    static isSideBarContainerType(value: object|string|number|undefined|null): boolean {
        return value instanceof SideBarContainerType
    }
    static isSideBarPosition(value: object|string|number|undefined|null): boolean {
        return value instanceof SideBarPosition
    }
    static isSize(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof Size
    }
    static isSizeOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof SizeOptions
    }
    static isSizeResult(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof SizeResult
    }
    static isSizeType(value: object|string|number|undefined|null): boolean {
        return value instanceof SizeType
    }
    static isSlideEffect(value: object|string|number|undefined|null): boolean {
        return value instanceof SlideEffect
    }
    static isSlideRange(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof SlideRange
    }
    static isSliderAttribute(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean, arg9: boolean, arg10: boolean, arg11: boolean, arg12: boolean, arg13: boolean, arg14: boolean, arg15: boolean, arg16: boolean, arg17: boolean, arg18: boolean, arg19: boolean): boolean {
        return value instanceof SliderAttribute
    }
    static isSliderBlockStyle(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof SliderBlockStyle
    }
    static isSliderBlockType(value: object|string|number|undefined|null): boolean {
        return value instanceof SliderBlockType
    }
    static isSliderChangeMode(value: object|string|number|undefined|null): boolean {
        return value instanceof SliderChangeMode
    }
    static isSliderConfiguration(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean): boolean {
        return value instanceof SliderConfiguration
    }
    static isSliderInteraction(value: object|string|number|undefined|null): boolean {
        return value instanceof SliderInteraction
    }
    static isSliderOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean): boolean {
        return value instanceof SliderOptions
    }
    static isSliderStyle(value: object|string|number|undefined|null): boolean {
        return value instanceof SliderStyle
    }
    static isSnapshotOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof SnapshotOptions
    }
    static isSourceTool(value: object|string|number|undefined|null): boolean {
        return value instanceof SourceTool
    }
    static isSourceType(value: object|string|number|undefined|null): boolean {
        return value instanceof SourceType
    }
    static isSpanAttribute(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean, arg9: boolean, arg10: boolean): boolean {
        return value instanceof SpanAttribute
    }
    static isSpanStyle(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof SpanStyle
    }
    static isSpringBackAction(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof SpringBackAction
    }
    static isSpringMotion(value: object|string|number|undefined|null): boolean {
        return value instanceof SpringMotion
    }
    static isSpringProp(value: object|string|number|undefined|null): boolean {
        return value instanceof SpringProp
    }
    static isSslError(value: object|string|number|undefined|null): boolean {
        return value instanceof SslError
    }
    static isSslErrorEvent(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean): boolean {
        return value instanceof SslErrorEvent
    }
    static isSslErrorHandler(value: object|string|number|undefined|null): boolean {
        return value instanceof SslErrorHandler
    }
    static isStackAttribute(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof StackAttribute
    }
    static isStackOptions(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof StackOptions
    }
    static isStarStyleOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof StarStyleOptions
    }
    static isStateStyles(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean): boolean {
        return value instanceof StateStyles
    }
    static isStepperAttribute(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean): boolean {
        return value instanceof StepperAttribute
    }
    static isStepperItemAttribute(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof StepperItemAttribute
    }
    static isSticky(value: object|string|number|undefined|null): boolean {
        return value instanceof Sticky
    }
    static isStickyStyle(value: object|string|number|undefined|null): boolean {
        return value instanceof StickyStyle
    }
    static isStyledString(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof StyledString
    }
    static isStyledStringChangedListener(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof StyledStringChangedListener
    }
    static isStyledStringChangeValue(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof StyledStringChangeValue
    }
    static isStyledStringController(value: object|string|number|undefined|null): boolean {
        return value instanceof StyledStringController
    }
    static isStyledStringKey(value: object|string|number|undefined|null): boolean {
        return value instanceof StyledStringKey
    }
    static isStyleOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof StyleOptions
    }
    static isSubMenuExpandingMode(value: object|string|number|undefined|null): boolean {
        return value instanceof SubMenuExpandingMode
    }
    static isSubmitEvent(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof SubmitEvent
    }
    static isSubscribaleAbstract(value: object|string|number|undefined|null): boolean {
        return value instanceof SubscribaleAbstract
    }
    static isSubTabBarStyle(value: object|string|number|undefined|null): boolean {
        return value instanceof SubTabBarStyle
    }
    static isSummary(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof Summary
    }
    static isSurfaceRect(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof SurfaceRect
    }
    static isSurfaceRotationOptions(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof SurfaceRotationOptions
    }
    static isSwipeActionItem(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean): boolean {
        return value instanceof SwipeActionItem
    }
    static isSwipeActionOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof SwipeActionOptions
    }
    static isSwipeActionState(value: object|string|number|undefined|null): boolean {
        return value instanceof SwipeActionState
    }
    static isSwipeDirection(value: object|string|number|undefined|null): boolean {
        return value instanceof SwipeDirection
    }
    static isSwipeEdgeEffect(value: object|string|number|undefined|null): boolean {
        return value instanceof SwipeEdgeEffect
    }
    static isSwipeGestureEvent(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof SwipeGestureEvent
    }
    static isSwipeGestureHandler(value: object|string|number|undefined|null): boolean {
        return value instanceof SwipeGestureHandler
    }
    static isSwipeGestureHandlerOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof SwipeGestureHandlerOptions
    }
    static isSwipeGestureInterface(value: object|string|number|undefined|null): boolean {
        return value instanceof SwipeGestureInterface
    }
    static isSwiperAnimationEvent(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof SwiperAnimationEvent
    }
    static isSwiperAttribute(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean, arg9: boolean, arg10: boolean, arg11: boolean, arg12: boolean, arg13: boolean, arg14: boolean, arg15: boolean, arg16: boolean, arg17: boolean, arg18: boolean, arg19: boolean, arg20: boolean, arg21: boolean): boolean {
        return value instanceof SwiperAttribute
    }
    static isSwiperAutoFill(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof SwiperAutoFill
    }
    static isSwiperContentAnimatedTransition(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof SwiperContentAnimatedTransition
    }
    static isSwiperContentTransitionProxy(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof SwiperContentTransitionProxy
    }
    static isSwiperController(value: object|string|number|undefined|null): boolean {
        return value instanceof SwiperController
    }
    static isSwiperDisplayMode(value: object|string|number|undefined|null): boolean {
        return value instanceof SwiperDisplayMode
    }
    static isSwiperNestedScrollMode(value: object|string|number|undefined|null): boolean {
        return value instanceof SwiperNestedScrollMode
    }
    static isSwitchStyle(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof SwitchStyle
    }
    static isSymbolEffect(value: object|string|number|undefined|null): boolean {
        return value instanceof SymbolEffect
    }
    static isSymbolEffectStrategy(value: object|string|number|undefined|null): boolean {
        return value instanceof SymbolEffectStrategy
    }
    static isSymbolGlyphAttribute(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean): boolean {
        return value instanceof SymbolGlyphAttribute
    }
    static isSymbolGlyphModifier(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof SymbolGlyphModifier
    }
    static isSymbolRenderingStrategy(value: object|string|number|undefined|null): boolean {
        return value instanceof SymbolRenderingStrategy
    }
    static isSymbolSpanAttribute(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean): boolean {
        return value instanceof SymbolSpanAttribute
    }
    static isSystemBarStyle(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof SystemBarStyle
    }
    static isSystemOps(value: object|string|number|undefined|null): boolean {
        return value instanceof SystemOps
    }
    static isTabBarIconStyle(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof TabBarIconStyle
    }
    static isTabBarOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof TabBarOptions
    }
    static isTabBarSymbol(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof TabBarSymbol
    }
    static isTabContentAnimatedTransition(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof TabContentAnimatedTransition
    }
    static isTabContentAttribute(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof TabContentAttribute
    }
    static isTabContentTransitionProxy(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof TabContentTransitionProxy
    }
    static isTabsAnimationEvent(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof TabsAnimationEvent
    }
    static isTabsAttribute(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean, arg9: boolean, arg10: boolean, arg11: boolean, arg12: boolean, arg13: boolean, arg14: boolean, arg15: boolean, arg16: boolean, arg17: boolean, arg18: boolean, arg19: boolean, arg20: boolean, arg21: boolean, arg22: boolean): boolean {
        return value instanceof TabsAttribute
    }
    static isTabsController(value: object|string|number|undefined|null): boolean {
        return value instanceof TabsController
    }
    static isTabsOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof TabsOptions
    }
    static isTapGestureEvent(value: object|string|number|undefined|null): boolean {
        return value instanceof TapGestureEvent
    }
    static isTapGestureHandler(value: object|string|number|undefined|null): boolean {
        return value instanceof TapGestureHandler
    }
    static isTapGestureHandlerOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof TapGestureHandlerOptions
    }
    static isTapGestureInterface(value: object|string|number|undefined|null): boolean {
        return value instanceof TapGestureInterface
    }
    static isTapGestureParameters(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof TapGestureParameters
    }
    static isTemplateOptions(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof TemplateOptions
    }
    static isTerminationInfo(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof TerminationInfo
    }
    static isTextAlign(value: object|string|number|undefined|null): boolean {
        return value instanceof TextAlign
    }
    static isTextAreaAttribute(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean, arg9: boolean, arg10: boolean, arg11: boolean, arg12: boolean, arg13: boolean, arg14: boolean, arg15: boolean, arg16: boolean, arg17: boolean, arg18: boolean, arg19: boolean, arg20: boolean, arg21: boolean, arg22: boolean, arg23: boolean, arg24: boolean, arg25: boolean, arg26: boolean, arg27: boolean, arg28: boolean, arg29: boolean, arg30: boolean, arg31: boolean, arg32: boolean, arg33: boolean, arg34: boolean, arg35: boolean, arg36: boolean, arg37: boolean, arg38: boolean, arg39: boolean, arg40: boolean, arg41: boolean, arg42: boolean, arg43: boolean, arg44: boolean, arg45: boolean, arg46: boolean, arg47: boolean, arg48: boolean): boolean {
        return value instanceof TextAreaAttribute
    }
    static isTextAreaController(value: object|string|number|undefined|null): boolean {
        return value instanceof TextAreaController
    }
    static isTextAreaOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof TextAreaOptions
    }
    static isTextAreaType(value: object|string|number|undefined|null): boolean {
        return value instanceof TextAreaType
    }
    static isTextAttribute(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean, arg9: boolean, arg10: boolean, arg11: boolean, arg12: boolean, arg13: boolean, arg14: boolean, arg15: boolean, arg16: boolean, arg17: boolean, arg18: boolean, arg19: boolean, arg20: boolean, arg21: boolean, arg22: boolean, arg23: boolean, arg24: boolean, arg25: boolean, arg26: boolean, arg27: boolean, arg28: boolean, arg29: boolean, arg30: boolean, arg31: boolean, arg32: boolean, arg33: boolean, arg34: boolean, arg35: boolean, arg36: boolean, arg37: boolean, arg38: boolean): boolean {
        return value instanceof TextAttribute
    }
    static isTextBackgroundStyle(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof TextBackgroundStyle
    }
    static isTextBaseController(value: object|string|number|undefined|null): boolean {
        return value instanceof TextBaseController
    }
    static isTextBox(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof TextBox
    }
    static isTextCascadePickerRangeContent(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof TextCascadePickerRangeContent
    }
    static isTextCase(value: object|string|number|undefined|null): boolean {
        return value instanceof TextCase
    }
    static isTextClockAttribute(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean, arg9: boolean, arg10: boolean): boolean {
        return value instanceof TextClockAttribute
    }
    static isTextClockConfiguration(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof TextClockConfiguration
    }
    static isTextClockController(value: object|string|number|undefined|null): boolean {
        return value instanceof TextClockController
    }
    static isTextClockOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof TextClockOptions
    }
    static isTextContentControllerBase(value: object|string|number|undefined|null): boolean {
        return value instanceof TextContentControllerBase
    }
    static isTextContentStyle(value: object|string|number|undefined|null): boolean {
        return value instanceof TextContentStyle
    }
    static isTextController(value: object|string|number|undefined|null): boolean {
        return value instanceof TextController
    }
    static isTextDataDetectorConfig(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof TextDataDetectorConfig
    }
    static isTextDataDetectorType(value: object|string|number|undefined|null): boolean {
        return value instanceof TextDataDetectorType
    }
    static isTextDecorationOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof TextDecorationOptions
    }
    static isTextDecorationStyle(value: object|string|number|undefined|null): boolean {
        return value instanceof TextDecorationStyle
    }
    static isTextDecorationType(value: object|string|number|undefined|null): boolean {
        return value instanceof TextDecorationType
    }
    static isTextDeleteDirection(value: object|string|number|undefined|null): boolean {
        return value instanceof TextDeleteDirection
    }
    static isTextEditControllerEx(value: object|string|number|undefined|null): boolean {
        return value instanceof TextEditControllerEx
    }
    static isTextHeightAdaptivePolicy(value: object|string|number|undefined|null): boolean {
        return value instanceof TextHeightAdaptivePolicy
    }
    static isTextInputAttribute(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean, arg9: boolean, arg10: boolean, arg11: boolean, arg12: boolean, arg13: boolean, arg14: boolean, arg15: boolean, arg16: boolean, arg17: boolean, arg18: boolean, arg19: boolean, arg20: boolean, arg21: boolean, arg22: boolean, arg23: boolean, arg24: boolean, arg25: boolean, arg26: boolean, arg27: boolean, arg28: boolean, arg29: boolean, arg30: boolean, arg31: boolean, arg32: boolean, arg33: boolean, arg34: boolean, arg35: boolean, arg36: boolean, arg37: boolean, arg38: boolean, arg39: boolean, arg40: boolean, arg41: boolean, arg42: boolean, arg43: boolean, arg44: boolean, arg45: boolean, arg46: boolean, arg47: boolean, arg48: boolean, arg49: boolean, arg50: boolean, arg51: boolean, arg52: boolean, arg53: boolean, arg54: boolean, arg55: boolean, arg56: boolean, arg57: boolean, arg58: boolean, arg59: boolean, arg60: boolean): boolean {
        return value instanceof TextInputAttribute
    }
    static isTextInputController(value: object|string|number|undefined|null): boolean {
        return value instanceof TextInputController
    }
    static isTextInputOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof TextInputOptions
    }
    static isTextInputStyle(value: object|string|number|undefined|null): boolean {
        return value instanceof TextInputStyle
    }
    static isTextMenuItem(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof TextMenuItem
    }
    static isTextMenuItemId(value: object|string|number|undefined|null): boolean {
        return value instanceof TextMenuItemId
    }
    static isTextMetrics(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean, arg9: boolean, arg10: boolean, arg11: boolean, arg12: boolean): boolean {
        return value instanceof TextMetrics
    }
    static isTextModifier(value: object|string|number|undefined|null): boolean {
        return value instanceof TextModifier
    }
    static isTextOptions(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof TextOptions
    }
    static isTextOverflow(value: object|string|number|undefined|null): boolean {
        return value instanceof TextOverflow
    }
    static isTextOverflowOptions(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof TextOverflowOptions
    }
    static isTextPickerAttribute(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean, arg9: boolean, arg10: boolean): boolean {
        return value instanceof TextPickerAttribute
    }
    static isTextPickerDialog(value: object|string|number|undefined|null): boolean {
        return value instanceof TextPickerDialog
    }
    static isTextPickerDialogOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean, arg9: boolean, arg10: boolean, arg11: boolean, arg12: boolean, arg13: boolean, arg14: boolean, arg15: boolean, arg16: boolean, arg17: boolean, arg18: boolean, arg19: boolean, arg20: boolean, arg21: boolean): boolean {
        return value instanceof TextPickerDialogOptions
    }
    static isTextPickerOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof TextPickerOptions
    }
    static isTextPickerRangeContent(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof TextPickerRangeContent
    }
    static isTextPickerResult(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof TextPickerResult
    }
    static isTextRange(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof TextRange
    }
    static isTextResponseType(value: object|string|number|undefined|null): boolean {
        return value instanceof TextResponseType
    }
    static isTextSelectableMode(value: object|string|number|undefined|null): boolean {
        return value instanceof TextSelectableMode
    }
    static isTextShadowStyle(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof TextShadowStyle
    }
    static isTextSpanType(value: object|string|number|undefined|null): boolean {
        return value instanceof TextSpanType
    }
    static isTextStyle_alert_dialog(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof TextStyle_alert_dialog
    }
    static isTextStyle_styled_string(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean): boolean {
        return value instanceof TextStyle_styled_string
    }
    static isTextStyleInterface(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean): boolean {
        return value instanceof TextStyleInterface
    }
    static isTextTimerAttribute(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean): boolean {
        return value instanceof TextTimerAttribute
    }
    static isTextTimerConfiguration(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof TextTimerConfiguration
    }
    static isTextTimerController(value: object|string|number|undefined|null): boolean {
        return value instanceof TextTimerController
    }
    static isTextTimerOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof TextTimerOptions
    }
    static isTheme(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof Theme
    }
    static isThemeColorMode(value: object|string|number|undefined|null): boolean {
        return value instanceof ThemeColorMode
    }
    static isThreatType(value: object|string|number|undefined|null): boolean {
        return value instanceof ThreatType
    }
    static isTimePickerAttribute(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean): boolean {
        return value instanceof TimePickerAttribute
    }
    static isTimePickerDialog(value: object|string|number|undefined|null): boolean {
        return value instanceof TimePickerDialog
    }
    static isTimePickerDialogOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean, arg9: boolean, arg10: boolean, arg11: boolean, arg12: boolean, arg13: boolean, arg14: boolean, arg15: boolean, arg16: boolean, arg17: boolean, arg18: boolean, arg19: boolean, arg20: boolean, arg21: boolean): boolean {
        return value instanceof TimePickerDialogOptions
    }
    static isTimePickerFormat(value: object|string|number|undefined|null): boolean {
        return value instanceof TimePickerFormat
    }
    static isTimePickerOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof TimePickerOptions
    }
    static isTimePickerResult(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof TimePickerResult
    }
    static isTitleHeight(value: object|string|number|undefined|null): boolean {
        return value instanceof TitleHeight
    }
    static isTodayStyle(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof TodayStyle
    }
    static isToggleAttribute(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean): boolean {
        return value instanceof ToggleAttribute
    }
    static isToggleConfiguration(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof ToggleConfiguration
    }
    static isToggleOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof ToggleOptions
    }
    static isToggleType(value: object|string|number|undefined|null): boolean {
        return value instanceof ToggleType
    }
    static isToolbarItem(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean): boolean {
        return value instanceof ToolbarItem
    }
    static isToolbarItemStatus(value: object|string|number|undefined|null): boolean {
        return value instanceof ToolbarItemStatus
    }
    static isTouchEvent(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean): boolean {
        return value instanceof TouchEvent
    }
    static isTouchObject(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean, arg9: boolean): boolean {
        return value instanceof TouchObject
    }
    static isTouchPoint(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof TouchPoint
    }
    static isTouchResult(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof TouchResult
    }
    static isTouchTestInfo(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean): boolean {
        return value instanceof TouchTestInfo
    }
    static isTouchTestStrategy(value: object|string|number|undefined|null): boolean {
        return value instanceof TouchTestStrategy
    }
    static isTouchType(value: object|string|number|undefined|null): boolean {
        return value instanceof TouchType
    }
    static isTransitionEdge(value: object|string|number|undefined|null): boolean {
        return value instanceof TransitionEdge
    }
    static isTransitionEffect(value: object|string|number|undefined|null): boolean {
        return value instanceof TransitionEffect
    }
    static isTransitionEffects(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean): boolean {
        return value instanceof TransitionEffects
    }
    static isTransitionHierarchyStrategy(value: object|string|number|undefined|null): boolean {
        return value instanceof TransitionHierarchyStrategy
    }
    static isTransitionOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean): boolean {
        return value instanceof TransitionOptions
    }
    static isTransitionType(value: object|string|number|undefined|null): boolean {
        return value instanceof TransitionType
    }
    static isTranslateOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof TranslateOptions
    }
    static isType_CalendarInterface_value(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean): boolean {
        return value instanceof Type_CalendarInterface_value
    }
    static isType_CommonMethod_linearGradient_value(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof Type_CommonMethod_linearGradient_value
    }
    static isType_CommonMethod_radialGradient_value(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof Type_CommonMethod_radialGradient_value
    }
    static isType_CommonMethod_sweepGradient_value(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean): boolean {
        return value instanceof Type_CommonMethod_sweepGradient_value
    }
    static isType_ImageAttribute_onComplete_callback_event(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean): boolean {
        return value instanceof Type_ImageAttribute_onComplete_callback_event
    }
    static isType_XComponentInterface_value(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof Type_XComponentInterface_value
    }
    static isUICommonEvent(value: object|string|number|undefined|null): boolean {
        return value instanceof UICommonEvent
    }
    static isUIContext(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof UIContext
    }
    static isUIExtensionComponentAttribute(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean): boolean {
        return value instanceof UIExtensionComponentAttribute
    }
    static isUIExtensionOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof UIExtensionOptions
    }
    static isUIExtensionProxy(value: object|string|number|undefined|null): boolean {
        return value instanceof UIExtensionProxy
    }
    static isUIGestureEvent(value: object|string|number|undefined|null): boolean {
        return value instanceof UIGestureEvent
    }
    static isUnderlineColor(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof UnderlineColor
    }
    static isUnifiedData(value: object|string|number|undefined|null): boolean {
        return value instanceof UnifiedData
    }
    static isUniformDataType(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof UniformDataType
    }
    static isUrlStyle(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof UrlStyle
    }
    static isUserDataSpan(value: object|string|number|undefined|null): boolean {
        return value instanceof UserDataSpan
    }
    static isVelocityOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof VelocityOptions
    }
    static isVerticalAlign(value: object|string|number|undefined|null): boolean {
        return value instanceof VerticalAlign
    }
    static isVideoAttribute(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean, arg9: boolean, arg10: boolean, arg11: boolean, arg12: boolean, arg13: boolean, arg14: boolean, arg15: boolean, arg16: boolean): boolean {
        return value instanceof VideoAttribute
    }
    static isVideoController(value: object|string|number|undefined|null): boolean {
        return value instanceof VideoController
    }
    static isVideoOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean): boolean {
        return value instanceof VideoOptions
    }
    static isView(value: object|string|number|undefined|null): boolean {
        return value instanceof View
    }
    static isViewportFit(value: object|string|number|undefined|null): boolean {
        return value instanceof ViewportFit
    }
    static isViewportRect(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof ViewportRect
    }
    static isVirtualScrollOptions(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof VirtualScrollOptions
    }
    static isVisibility(value: object|string|number|undefined|null): boolean {
        return value instanceof Visibility
    }
    static isVisibleAreaEventOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof VisibleAreaEventOptions
    }
    static isVisibleListContentInfo(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof VisibleListContentInfo
    }
    static isVisualEffect(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof VisualEffect
    }
    static isWant(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean, arg9: boolean): boolean {
        return value instanceof Want
    }
    static isWaterFlowAttribute(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean, arg9: boolean, arg10: boolean, arg11: boolean, arg12: boolean, arg13: boolean): boolean {
        return value instanceof WaterFlowAttribute
    }
    static isWaterFlowLayoutMode(value: object|string|number|undefined|null): boolean {
        return value instanceof WaterFlowLayoutMode
    }
    static isWaterFlowOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof WaterFlowOptions
    }
    static isWaterFlowSections(value: object|string|number|undefined|null): boolean {
        return value instanceof WaterFlowSections
    }
    static isWebAttribute(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean, arg9: boolean, arg10: boolean, arg11: boolean, arg12: boolean, arg13: boolean, arg14: boolean, arg15: boolean, arg16: boolean, arg17: boolean, arg18: boolean, arg19: boolean, arg20: boolean, arg21: boolean, arg22: boolean, arg23: boolean, arg24: boolean, arg25: boolean, arg26: boolean, arg27: boolean, arg28: boolean, arg29: boolean, arg30: boolean, arg31: boolean, arg32: boolean, arg33: boolean, arg34: boolean, arg35: boolean, arg36: boolean, arg37: boolean, arg38: boolean, arg39: boolean, arg40: boolean, arg41: boolean, arg42: boolean, arg43: boolean, arg44: boolean, arg45: boolean, arg46: boolean, arg47: boolean, arg48: boolean, arg49: boolean, arg50: boolean, arg51: boolean, arg52: boolean, arg53: boolean, arg54: boolean, arg55: boolean, arg56: boolean, arg57: boolean, arg58: boolean, arg59: boolean, arg60: boolean, arg61: boolean, arg62: boolean, arg63: boolean, arg64: boolean, arg65: boolean, arg66: boolean, arg67: boolean, arg68: boolean, arg69: boolean, arg70: boolean, arg71: boolean, arg72: boolean, arg73: boolean, arg74: boolean, arg75: boolean, arg76: boolean, arg77: boolean, arg78: boolean, arg79: boolean, arg80: boolean, arg81: boolean, arg82: boolean, arg83: boolean, arg84: boolean, arg85: boolean, arg86: boolean, arg87: boolean, arg88: boolean, arg89: boolean, arg90: boolean, arg91: boolean, arg92: boolean, arg93: boolean, arg94: boolean, arg95: boolean, arg96: boolean, arg97: boolean, arg98: boolean, arg99: boolean, arg100: boolean, arg101: boolean, arg102: boolean, arg103: boolean, arg104: boolean, arg105: boolean, arg106: boolean, arg107: boolean, arg108: boolean, arg109: boolean, arg110: boolean, arg111: boolean, arg112: boolean, arg113: boolean, arg114: boolean, arg115: boolean, arg116: boolean): boolean {
        return value instanceof WebAttribute
    }
    static isWebCaptureMode(value: object|string|number|undefined|null): boolean {
        return value instanceof WebCaptureMode
    }
    static isWebContextMenuParam(value: object|string|number|undefined|null): boolean {
        return value instanceof WebContextMenuParam
    }
    static isWebContextMenuResult(value: object|string|number|undefined|null): boolean {
        return value instanceof WebContextMenuResult
    }
    static isWebController(value: object|string|number|undefined|null): boolean {
        return value instanceof WebController
    }
    static isWebCookie(value: object|string|number|undefined|null): boolean {
        return value instanceof WebCookie
    }
    static isWebDarkMode(value: object|string|number|undefined|null): boolean {
        return value instanceof WebDarkMode
    }
    static isWebElementType(value: object|string|number|undefined|null): boolean {
        return value instanceof WebElementType
    }
    static isWebHeader(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof WebHeader
    }
    static isWebKeyboardAvoidMode(value: object|string|number|undefined|null): boolean {
        return value instanceof WebKeyboardAvoidMode
    }
    static isWebKeyboardCallbackInfo(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof WebKeyboardCallbackInfo
    }
    static isWebKeyboardController(value: object|string|number|undefined|null): boolean {
        return value instanceof WebKeyboardController
    }
    static isWebKeyboardOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof WebKeyboardOptions
    }
    static isWebLayoutMode(value: object|string|number|undefined|null): boolean {
        return value instanceof WebLayoutMode
    }
    static isWebMediaOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof WebMediaOptions
    }
    static isWebNavigationType(value: object|string|number|undefined|null): boolean {
        return value instanceof WebNavigationType
    }
    static isWebOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean): boolean {
        return value instanceof WebOptions
    }
    static isWebResourceError(value: object|string|number|undefined|null): boolean {
        return value instanceof WebResourceError
    }
    static isWebResourceRequest(value: object|string|number|undefined|null): boolean {
        return value instanceof WebResourceRequest
    }
    static isWebResourceResponse(value: object|string|number|undefined|null): boolean {
        return value instanceof WebResourceResponse
    }
    static isWebResponseType(value: object|string|number|undefined|null): boolean {
        return value instanceof WebResponseType
    }
    static isWebviewController(value: object|string|number|undefined|null): boolean {
        return value instanceof WebviewController
    }
    static isWeek(value: object|string|number|undefined|null): boolean {
        return value instanceof Week
    }
    static isWeekStyle(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean): boolean {
        return value instanceof WeekStyle
    }
    static isWidthBreakpoint(value: object|string|number|undefined|null): boolean {
        return value instanceof WidthBreakpoint
    }
    static isWindowAnimationTarget(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof WindowAnimationTarget
    }
    static isWindowSceneAttribute(value: object|string|number|undefined|null): boolean {
        return value instanceof WindowSceneAttribute
    }
    static isWindowStatusType(value: object|string|number|undefined|null, arg0: boolean): boolean {
        return value instanceof WindowStatusType
    }
    static isWithThemeAttribute(value: object|string|number|undefined|null): boolean {
        return value instanceof WithThemeAttribute
    }
    static isWithThemeOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean): boolean {
        return value instanceof WithThemeOptions
    }
    static isWordBreak(value: object|string|number|undefined|null): boolean {
        return value instanceof WordBreak
    }
    static isWorkStateStyle(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean): boolean {
        return value instanceof WorkStateStyle
    }
    static isXComponentAttribute(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof XComponentAttribute
    }
    static isXComponentController(value: object|string|number|undefined|null): boolean {
        return value instanceof XComponentController
    }
    static isXComponentOptions(value: object|string|number|undefined|null, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof XComponentOptions
    }
    static isXComponentType(value: object|string|number|undefined|null): boolean {
        return value instanceof XComponentType
    }
    static PointerStyle_ToOrdinal(value: PointerStyle): int32 {
        return value as int32
    }
    static PointerStyle_FromOrdinal(ordinal: int32): PointerStyle {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static RectWidthStyle_ToOrdinal(value: RectWidthStyle): int32 {
        return value as int32
    }
    static RectWidthStyle_FromOrdinal(ordinal: int32): RectWidthStyle {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static RectHeightStyle_ToOrdinal(value: RectHeightStyle): int32 {
        return value as int32
    }
    static RectHeightStyle_FromOrdinal(ordinal: int32): RectHeightStyle {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static LengthUnit_ToOrdinal(value: LengthUnit): int32 {
        return value as int32
    }
    static LengthUnit_FromOrdinal(ordinal: int32): LengthUnit {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static PerfMonitorActionType_ToOrdinal(value: PerfMonitorActionType): int32 {
        return value as int32
    }
    static PerfMonitorActionType_FromOrdinal(ordinal: int32): PerfMonitorActionType {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static PerfMonitorSourceType_ToOrdinal(value: PerfMonitorSourceType): int32 {
        return value as int32
    }
    static PerfMonitorSourceType_FromOrdinal(ordinal: int32): PerfMonitorSourceType {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static EffectDirection_ToOrdinal(value: EffectDirection): int32 {
        return value as int32
    }
    static EffectDirection_FromOrdinal(ordinal: int32): EffectDirection {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static EffectScope_ToOrdinal(value: EffectScope): int32 {
        return value as int32
    }
    static EffectScope_FromOrdinal(ordinal: int32): EffectScope {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static DialogAlignment_ToOrdinal(value: DialogAlignment): int32 {
        return value as int32
    }
    static DialogAlignment_FromOrdinal(ordinal: int32): DialogAlignment {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static DialogButtonDirection_ToOrdinal(value: DialogButtonDirection): int32 {
        return value as int32
    }
    static DialogButtonDirection_FromOrdinal(ordinal: int32): DialogButtonDirection {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static IndexerAlign_ToOrdinal(value: IndexerAlign): int32 {
        return value as int32
    }
    static IndexerAlign_FromOrdinal(ordinal: int32): IndexerAlign {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static BadgePosition_ToOrdinal(value: BadgePosition): int32 {
        return value as int32
    }
    static BadgePosition_FromOrdinal(ordinal: int32): BadgePosition {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static ButtonType_ToOrdinal(value: ButtonType): int32 {
        return value as int32
    }
    static ButtonType_FromOrdinal(ordinal: int32): ButtonType {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static ButtonStyleMode_ToOrdinal(value: ButtonStyleMode): int32 {
        return value as int32
    }
    static ButtonStyleMode_FromOrdinal(ordinal: int32): ButtonStyleMode {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static ButtonRole_ToOrdinal(value: ButtonRole): int32 {
        return value as int32
    }
    static ButtonRole_FromOrdinal(ordinal: int32): ButtonRole {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static ControlSize_ToOrdinal(value: ControlSize): int32 {
        return 0 // value as int32
    }
    static ControlSize_FromOrdinal(ordinal: int32): ControlSize {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static CalendarAlign_ToOrdinal(value: CalendarAlign): int32 {
        return value as int32
    }
    static CalendarAlign_FromOrdinal(ordinal: int32): CalendarAlign {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static SelectStatus_ToOrdinal(value: SelectStatus): int32 {
        return value as int32
    }
    static SelectStatus_FromOrdinal(ordinal: int32): SelectStatus {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static FinishCallbackType_ToOrdinal(value: FinishCallbackType): int32 {
        return value as int32
    }
    static FinishCallbackType_FromOrdinal(ordinal: int32): FinishCallbackType {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static TouchTestStrategy_ToOrdinal(value: TouchTestStrategy): int32 {
        return value as int32
    }
    static TouchTestStrategy_FromOrdinal(ordinal: int32): TouchTestStrategy {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static TransitionHierarchyStrategy_ToOrdinal(value: TransitionHierarchyStrategy): int32 {
        return value as int32
    }
    static TransitionHierarchyStrategy_FromOrdinal(ordinal: int32): TransitionHierarchyStrategy {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static ChainStyle_ToOrdinal(value: ChainStyle): int32 {
        return value as int32
    }
    static ChainStyle_FromOrdinal(ordinal: int32): ChainStyle {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static TransitionEdge_ToOrdinal(value: TransitionEdge): int32 {
        return value as int32
    }
    static TransitionEdge_FromOrdinal(ordinal: int32): TransitionEdge {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static EffectType_ToOrdinal(value: EffectType): int32 {
        return value as int32
    }
    static EffectType_FromOrdinal(ordinal: int32): EffectType {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static PreDragStatus_ToOrdinal(value: PreDragStatus): int32 {
        return value as int32
    }
    static PreDragStatus_FromOrdinal(ordinal: int32): PreDragStatus {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static SourceType_ToOrdinal(value: SourceType): int32 {
        return value as int32
    }
    static SourceType_FromOrdinal(ordinal: int32): SourceType {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static SourceTool_ToOrdinal(value: SourceTool): int32 {
        return value as int32
    }
    static SourceTool_FromOrdinal(ordinal: int32): SourceTool {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static RepeatMode_ToOrdinal(value: RepeatMode): int32 {
        return value as int32
    }
    static RepeatMode_FromOrdinal(ordinal: int32): RepeatMode {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static BlurStyle_ToOrdinal(value: BlurStyle): int32 {
        return value as int32
    }
    static BlurStyle_FromOrdinal(ordinal: int32): BlurStyle {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static BlurStyleActivePolicy_ToOrdinal(value: BlurStyleActivePolicy): int32 {
        return value as int32
    }
    static BlurStyleActivePolicy_FromOrdinal(ordinal: int32): BlurStyleActivePolicy {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static ThemeColorMode_ToOrdinal(value: ThemeColorMode): int32 {
        return value as int32
    }
    static ThemeColorMode_FromOrdinal(ordinal: int32): ThemeColorMode {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static AdaptiveColor_ToOrdinal(value: AdaptiveColor): int32 {
        return value as int32
    }
    static AdaptiveColor_FromOrdinal(ordinal: int32): AdaptiveColor {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static ModalTransition_ToOrdinal(value: ModalTransition): int32 {
        return value as int32
    }
    static ModalTransition_FromOrdinal(ordinal: int32): ModalTransition {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static ShadowType_ToOrdinal(value: ShadowType): int32 {
        return value as int32
    }
    static ShadowType_FromOrdinal(ordinal: int32): ShadowType {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static ShadowStyle_ToOrdinal(value: ShadowStyle): int32 {
        return value as int32
    }
    static ShadowStyle_FromOrdinal(ordinal: int32): ShadowStyle {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static SafeAreaType_ToOrdinal(value: SafeAreaType): int32 {
        return value as int32
    }
    static SafeAreaType_FromOrdinal(ordinal: int32): SafeAreaType {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static SafeAreaEdge_ToOrdinal(value: SafeAreaEdge): int32 {
        return value as int32
    }
    static SafeAreaEdge_FromOrdinal(ordinal: int32): SafeAreaEdge {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static LayoutSafeAreaType_ToOrdinal(value: LayoutSafeAreaType): int32 {
        return value as int32
    }
    static LayoutSafeAreaType_FromOrdinal(ordinal: int32): LayoutSafeAreaType {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static LayoutSafeAreaEdge_ToOrdinal(value: LayoutSafeAreaEdge): int32 {
        return value as int32
    }
    static LayoutSafeAreaEdge_FromOrdinal(ordinal: int32): LayoutSafeAreaEdge {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static SheetSize_ToOrdinal(value: SheetSize): int32 {
        return value as int32
    }
    static SheetSize_FromOrdinal(ordinal: int32): SheetSize {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static DragBehavior_ToOrdinal(value: DragBehavior): int32 {
        return value as int32
    }
    static DragBehavior_FromOrdinal(ordinal: int32): DragBehavior {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static DragResult_ToOrdinal(value: DragResult): int32 {
        return value as int32
    }
    static DragResult_FromOrdinal(ordinal: int32): DragResult {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static BlendMode_ToOrdinal(value: BlendMode): int32 {
        return value as int32
    }
    static BlendMode_FromOrdinal(ordinal: int32): BlendMode {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static BlendApplyType_ToOrdinal(value: BlendApplyType): int32 {
        return value as int32
    }
    static BlendApplyType_FromOrdinal(ordinal: int32): BlendApplyType {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static SheetType_ToOrdinal(value: SheetType): int32 {
        return value as int32
    }
    static SheetType_FromOrdinal(ordinal: int32): SheetType {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static SheetMode_ToOrdinal(value: SheetMode): int32 {
        return value as int32
    }
    static SheetMode_FromOrdinal(ordinal: int32): SheetMode {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static ScrollSizeMode_ToOrdinal(value: ScrollSizeMode): int32 {
        return value as int32
    }
    static ScrollSizeMode_FromOrdinal(ordinal: int32): ScrollSizeMode {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static SheetKeyboardAvoidMode_ToOrdinal(value: SheetKeyboardAvoidMode): int32 {
        return value as int32
    }
    static SheetKeyboardAvoidMode_FromOrdinal(ordinal: int32): SheetKeyboardAvoidMode {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static DismissReason_ToOrdinal(value: DismissReason): int32 {
        return value as int32
    }
    static DismissReason_FromOrdinal(ordinal: int32): DismissReason {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static MenuPreviewMode_ToOrdinal(value: MenuPreviewMode): int32 {
        return value as int32
    }
    static MenuPreviewMode_FromOrdinal(ordinal: int32): MenuPreviewMode {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static OutlineStyle_ToOrdinal(value: OutlineStyle): int32 {
        return value as int32
    }
    static OutlineStyle_FromOrdinal(ordinal: int32): OutlineStyle {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static DragPreviewMode_ToOrdinal(value: DragPreviewMode): int32 {
        return value as int32
    }
    static DragPreviewMode_FromOrdinal(ordinal: int32): DragPreviewMode {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static MenuPolicy_ToOrdinal(value: MenuPolicy): int32 {
        return value as int32
    }
    static MenuPolicy_FromOrdinal(ordinal: int32): MenuPolicy {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static ContentClipMode_ToOrdinal(value: ContentClipMode): int32 {
        return value as int32
    }
    static ContentClipMode_FromOrdinal(ordinal: int32): ContentClipMode {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static KeyboardAvoidMode_ToOrdinal(value: KeyboardAvoidMode): int32 {
        return value as int32
    }
    static KeyboardAvoidMode_FromOrdinal(ordinal: int32): KeyboardAvoidMode {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static HoverModeAreaType_ToOrdinal(value: HoverModeAreaType): int32 {
        return value as int32
    }
    static HoverModeAreaType_FromOrdinal(ordinal: int32): HoverModeAreaType {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static ModelType_ToOrdinal(value: ModelType): int32 {
        return value as int32
    }
    static ModelType_FromOrdinal(ordinal: int32): ModelType {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static DataPanelType_ToOrdinal(value: DataPanelType): int32 {
        return value as int32
    }
    static DataPanelType_FromOrdinal(ordinal: int32): DataPanelType {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static CheckBoxShape_ToOrdinal(value: CheckBoxShape): int32 {
        return value as int32
    }
    static CheckBoxShape_FromOrdinal(ordinal: int32): CheckBoxShape {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static Color_ToOrdinal(value: Color): int32 {
        return value as int32
    }
    static Color_FromOrdinal(ordinal: int32): Color {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static ColoringStrategy_ToOrdinal(value: ColoringStrategy): int32 {
        return 0 // value as int32
    }
    static ColoringStrategy_FromOrdinal(ordinal: int32): ColoringStrategy {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static ImageFit_ToOrdinal(value: ImageFit): int32 {
        return value as int32
    }
    static ImageFit_FromOrdinal(ordinal: int32): ImageFit {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static BorderStyle_ToOrdinal(value: BorderStyle): int32 {
        return value as int32
    }
    static BorderStyle_FromOrdinal(ordinal: int32): BorderStyle {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static LineJoinStyle_ToOrdinal(value: LineJoinStyle): int32 {
        return value as int32
    }
    static LineJoinStyle_FromOrdinal(ordinal: int32): LineJoinStyle {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static TouchType_ToOrdinal(value: TouchType): int32 {
        return value as int32
    }
    static TouchType_FromOrdinal(ordinal: int32): TouchType {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static MouseButton_ToOrdinal(value: MouseButton): int32 {
        return value as int32
    }
    static MouseButton_FromOrdinal(ordinal: int32): MouseButton {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static MouseAction_ToOrdinal(value: MouseAction): int32 {
        return value as int32
    }
    static MouseAction_FromOrdinal(ordinal: int32): MouseAction {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static AnimationStatus_ToOrdinal(value: AnimationStatus): int32 {
        return value as int32
    }
    static AnimationStatus_FromOrdinal(ordinal: int32): AnimationStatus {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static Curve_ToOrdinal(value: Curve): int32 {
        return value as int32
    }
    static Curve_FromOrdinal(ordinal: int32): Curve {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static FillMode_ToOrdinal(value: FillMode): int32 {
        return value as int32
    }
    static FillMode_FromOrdinal(ordinal: int32): FillMode {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static PlayMode_ToOrdinal(value: PlayMode): int32 {
        return value as int32
    }
    static PlayMode_FromOrdinal(ordinal: int32): PlayMode {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static KeyType_ToOrdinal(value: KeyType): int32 {
        return value as int32
    }
    static KeyType_FromOrdinal(ordinal: int32): KeyType {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static KeySource_ToOrdinal(value: KeySource): int32 {
        return value as int32
    }
    static KeySource_FromOrdinal(ordinal: int32): KeySource {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static Edge_ToOrdinal(value: Edge): int32 {
        return value as int32
    }
    static Edge_FromOrdinal(ordinal: int32): Edge {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static Week_ToOrdinal(value: Week): int32 {
        return value as int32
    }
    static Week_FromOrdinal(ordinal: int32): Week {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static Direction_ToOrdinal(value: Direction): int32 {
        return value as int32
    }
    static Direction_FromOrdinal(ordinal: int32): Direction {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static BarState_ToOrdinal(value: BarState): int32 {
        return value as int32
    }
    static BarState_FromOrdinal(ordinal: int32): BarState {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static EdgeEffect_ToOrdinal(value: EdgeEffect): int32 {
        return value as int32
    }
    static EdgeEffect_FromOrdinal(ordinal: int32): EdgeEffect {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static Alignment_ToOrdinal(value: Alignment): int32 {
        return value as int32
    }
    static Alignment_FromOrdinal(ordinal: int32): Alignment {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static TransitionType_ToOrdinal(value: TransitionType): int32 {
        return value as int32
    }
    static TransitionType_FromOrdinal(ordinal: int32): TransitionType {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static RelateType_ToOrdinal(value: RelateType): int32 {
        return value as int32
    }
    static RelateType_FromOrdinal(ordinal: int32): RelateType {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static Visibility_ToOrdinal(value: Visibility): int32 {
        return value as int32
    }
    static Visibility_FromOrdinal(ordinal: int32): Visibility {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static LineCapStyle_ToOrdinal(value: LineCapStyle): int32 {
        return value as int32
    }
    static LineCapStyle_FromOrdinal(ordinal: int32): LineCapStyle {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static Axis_ToOrdinal(value: Axis): int32 {
        return value as int32
    }
    static Axis_FromOrdinal(ordinal: int32): Axis {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static HorizontalAlign_ToOrdinal(value: HorizontalAlign): int32 {
        return value as int32
    }
    static HorizontalAlign_FromOrdinal(ordinal: int32): HorizontalAlign {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static FlexAlign_ToOrdinal(value: FlexAlign): int32 {
        return value as int32
    }
    static FlexAlign_FromOrdinal(ordinal: int32): FlexAlign {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static ItemAlign_ToOrdinal(value: ItemAlign): int32 {
        return value as int32
    }
    static ItemAlign_FromOrdinal(ordinal: int32): ItemAlign {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static FlexDirection_ToOrdinal(value: FlexDirection): int32 {
        return value as int32
    }
    static FlexDirection_FromOrdinal(ordinal: int32): FlexDirection {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static PixelRoundCalcPolicy_ToOrdinal(value: PixelRoundCalcPolicy): int32 {
        return value as int32
    }
    static PixelRoundCalcPolicy_FromOrdinal(ordinal: int32): PixelRoundCalcPolicy {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static FlexWrap_ToOrdinal(value: FlexWrap): int32 {
        return value as int32
    }
    static FlexWrap_FromOrdinal(ordinal: int32): FlexWrap {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static VerticalAlign_ToOrdinal(value: VerticalAlign): int32 {
        return value as int32
    }
    static VerticalAlign_FromOrdinal(ordinal: int32): VerticalAlign {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static ImageRepeat_ToOrdinal(value: ImageRepeat): int32 {
        return value as int32
    }
    static ImageRepeat_FromOrdinal(ordinal: int32): ImageRepeat {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static ImageSize_ToOrdinal(value: ImageSize): int32 {
        return value as int32
    }
    static ImageSize_FromOrdinal(ordinal: int32): ImageSize {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static GradientDirection_ToOrdinal(value: GradientDirection): int32 {
        return value as int32
    }
    static GradientDirection_FromOrdinal(ordinal: int32): GradientDirection {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static SharedTransitionEffectType_ToOrdinal(value: SharedTransitionEffectType): int32 {
        return value as int32
    }
    static SharedTransitionEffectType_FromOrdinal(ordinal: int32): SharedTransitionEffectType {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static FontStyle_ToOrdinal(value: FontStyle): int32 {
        return value as int32
    }
    static FontStyle_FromOrdinal(ordinal: int32): FontStyle {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static FontWeight_ToOrdinal(value: FontWeight): int32 {
        return value as int32
    }
    static FontWeight_FromOrdinal(ordinal: int32): FontWeight {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static TextAlign_ToOrdinal(value: TextAlign): int32 {
        return value as int32
    }
    static TextAlign_FromOrdinal(ordinal: int32): TextAlign {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static TextOverflow_ToOrdinal(value: TextOverflow): int32 {
        return value as int32
    }
    static TextOverflow_FromOrdinal(ordinal: int32): TextOverflow {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static TextDecorationType_ToOrdinal(value: TextDecorationType): int32 {
        return value as int32
    }
    static TextDecorationType_FromOrdinal(ordinal: int32): TextDecorationType {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static TextCase_ToOrdinal(value: TextCase): int32 {
        return value as int32
    }
    static TextCase_FromOrdinal(ordinal: int32): TextCase {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static TextHeightAdaptivePolicy_ToOrdinal(value: TextHeightAdaptivePolicy): int32 {
        return value as int32
    }
    static TextHeightAdaptivePolicy_FromOrdinal(ordinal: int32): TextHeightAdaptivePolicy {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static ResponseType_ToOrdinal(value: ResponseType): int32 {
        return value as int32
    }
    static ResponseType_FromOrdinal(ordinal: int32): ResponseType {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static HoverEffect_ToOrdinal(value: HoverEffect): int32 {
        return value as int32
    }
    static HoverEffect_FromOrdinal(ordinal: int32): HoverEffect {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static Placement_ToOrdinal(value: Placement): int32 {
        return value as int32
    }
    static Placement_FromOrdinal(ordinal: int32): Placement {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static ArrowPointPosition_ToOrdinal(value: ArrowPointPosition): int32 {
        return 0 // value as int32
    }
    static ArrowPointPosition_FromOrdinal(ordinal: int32): ArrowPointPosition {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static CopyOptions_ToOrdinal(value: CopyOptions): int32 {
        return value as int32
    }
    static CopyOptions_FromOrdinal(ordinal: int32): CopyOptions {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static HitTestMode_ToOrdinal(value: HitTestMode): int32 {
        return value as int32
    }
    static HitTestMode_FromOrdinal(ordinal: int32): HitTestMode {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static TitleHeight_ToOrdinal(value: TitleHeight): int32 {
        return value as int32
    }
    static TitleHeight_FromOrdinal(ordinal: int32): TitleHeight {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static ModifierKey_ToOrdinal(value: ModifierKey): int32 {
        return value as int32
    }
    static ModifierKey_FromOrdinal(ordinal: int32): ModifierKey {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static FunctionKey_ToOrdinal(value: FunctionKey): int32 {
        return value as int32
    }
    static FunctionKey_FromOrdinal(ordinal: int32): FunctionKey {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static ImageSpanAlignment_ToOrdinal(value: ImageSpanAlignment): int32 {
        return value as int32
    }
    static ImageSpanAlignment_FromOrdinal(ordinal: int32): ImageSpanAlignment {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static ObscuredReasons_ToOrdinal(value: ObscuredReasons): int32 {
        return value as int32
    }
    static ObscuredReasons_FromOrdinal(ordinal: int32): ObscuredReasons {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static TextContentStyle_ToOrdinal(value: TextContentStyle): int32 {
        return value as int32
    }
    static TextContentStyle_FromOrdinal(ordinal: int32): TextContentStyle {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static ClickEffectLevel_ToOrdinal(value: ClickEffectLevel): int32 {
        return value as int32
    }
    static ClickEffectLevel_FromOrdinal(ordinal: int32): ClickEffectLevel {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static XComponentType_ToOrdinal(value: XComponentType): int32 {
        return value as int32
    }
    static XComponentType_FromOrdinal(ordinal: int32): XComponentType {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static NestedScrollMode_ToOrdinal(value: NestedScrollMode): int32 {
        return value as int32
    }
    static NestedScrollMode_FromOrdinal(ordinal: int32): NestedScrollMode {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static ScrollSource_ToOrdinal(value: ScrollSource): int32 {
        return value as int32
    }
    static ScrollSource_FromOrdinal(ordinal: int32): ScrollSource {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static RenderFit_ToOrdinal(value: RenderFit): int32 {
        return value as int32
    }
    static RenderFit_FromOrdinal(ordinal: int32): RenderFit {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static DialogButtonStyle_ToOrdinal(value: DialogButtonStyle): int32 {
        return value as int32
    }
    static DialogButtonStyle_FromOrdinal(ordinal: int32): DialogButtonStyle {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static WordBreak_ToOrdinal(value: WordBreak): int32 {
        return value as int32
    }
    static WordBreak_FromOrdinal(ordinal: int32): WordBreak {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static LineBreakStrategy_ToOrdinal(value: LineBreakStrategy): int32 {
        return value as int32
    }
    static LineBreakStrategy_FromOrdinal(ordinal: int32): LineBreakStrategy {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static EllipsisMode_ToOrdinal(value: EllipsisMode): int32 {
        return value as int32
    }
    static EllipsisMode_FromOrdinal(ordinal: int32): EllipsisMode {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static OptionWidthMode_ToOrdinal(value: OptionWidthMode): int32 {
        return 0 // value as int32
    }
    static OptionWidthMode_FromOrdinal(ordinal: int32): OptionWidthMode {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static IlluminatedType_ToOrdinal(value: IlluminatedType): int32 {
        return value as int32
    }
    static IlluminatedType_FromOrdinal(ordinal: int32): IlluminatedType {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static FoldStatus_ToOrdinal(value: FoldStatus): int32 {
        return value as int32
    }
    static FoldStatus_FromOrdinal(ordinal: int32): FoldStatus {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static AppRotation_ToOrdinal(value: AppRotation): int32 {
        return value as int32
    }
    static AppRotation_FromOrdinal(ordinal: int32): AppRotation {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static EmbeddedType_ToOrdinal(value: EmbeddedType): int32 {
        return value as int32
    }
    static EmbeddedType_FromOrdinal(ordinal: int32): EmbeddedType {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static MarqueeUpdateStrategy_ToOrdinal(value: MarqueeUpdateStrategy): int32 {
        return value as int32
    }
    static MarqueeUpdateStrategy_FromOrdinal(ordinal: int32): MarqueeUpdateStrategy {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static TextDecorationStyle_ToOrdinal(value: TextDecorationStyle): int32 {
        return value as int32
    }
    static TextDecorationStyle_FromOrdinal(ordinal: int32): TextDecorationStyle {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static TextSelectableMode_ToOrdinal(value: TextSelectableMode): int32 {
        return value as int32
    }
    static TextSelectableMode_FromOrdinal(ordinal: int32): TextSelectableMode {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static AccessibilityHoverType_ToOrdinal(value: AccessibilityHoverType): int32 {
        return value as int32
    }
    static AccessibilityHoverType_FromOrdinal(ordinal: int32): AccessibilityHoverType {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static WidthBreakpoint_ToOrdinal(value: WidthBreakpoint): int32 {
        return value as int32
    }
    static WidthBreakpoint_FromOrdinal(ordinal: int32): WidthBreakpoint {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static HeightBreakpoint_ToOrdinal(value: HeightBreakpoint): int32 {
        return value as int32
    }
    static HeightBreakpoint_FromOrdinal(ordinal: int32): HeightBreakpoint {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static FocusPriority_ToOrdinal(value: FocusPriority): int32 {
        return value as int32
    }
    static FocusPriority_FromOrdinal(ordinal: int32): FocusPriority {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static FormDimension_ToOrdinal(value: FormDimension): int32 {
        return value as int32
    }
    static FormDimension_FromOrdinal(ordinal: int32): FormDimension {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static FormRenderingMode_ToOrdinal(value: FormRenderingMode): int32 {
        return value as int32
    }
    static FormRenderingMode_FromOrdinal(ordinal: int32): FormRenderingMode {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static FormShape_ToOrdinal(value: FormShape): int32 {
        return value as int32
    }
    static FormShape_FromOrdinal(ordinal: int32): FormShape {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static PanDirection_ToOrdinal(value: PanDirection): int32 {
        return value as int32
    }
    static PanDirection_FromOrdinal(ordinal: int32): PanDirection {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static SwipeDirection_ToOrdinal(value: SwipeDirection): int32 {
        return value as int32
    }
    static SwipeDirection_FromOrdinal(ordinal: int32): SwipeDirection {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static GestureMode_ToOrdinal(value: GestureMode): int32 {
        return value as int32
    }
    static GestureMode_FromOrdinal(ordinal: int32): GestureMode {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static GestureMask_ToOrdinal(value: GestureMask): int32 {
        return value as int32
    }
    static GestureMask_FromOrdinal(ordinal: int32): GestureMask {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static GestureJudgeResult_ToOrdinal(value: GestureJudgeResult): int32 {
        return value as int32
    }
    static GestureJudgeResult_FromOrdinal(ordinal: int32): GestureJudgeResult {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static GestureControl_GestureType_ToOrdinal(value: GestureControl.GestureType): int32 {
        return value as int32
    }
    static GestureControl_GestureType_FromOrdinal(ordinal: int32): GestureControl.GestureType {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static GesturePriority_ToOrdinal(value: GesturePriority): int32 {
        return value as int32
    }
    static GesturePriority_FromOrdinal(ordinal: int32): GesturePriority {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static GestureRecognizerState_ToOrdinal(value: GestureRecognizerState): int32 {
        return value as int32
    }
    static GestureRecognizerState_FromOrdinal(ordinal: int32): GestureRecognizerState {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static GridDirection_ToOrdinal(value: GridDirection): int32 {
        return value as int32
    }
    static GridDirection_FromOrdinal(ordinal: int32): GridDirection {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static GridItemAlignment_ToOrdinal(value: GridItemAlignment): int32 {
        return value as int32
    }
    static GridItemAlignment_FromOrdinal(ordinal: int32): GridItemAlignment {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static GridItemStyle_ToOrdinal(value: GridItemStyle): int32 {
        return value as int32
    }
    static GridItemStyle_FromOrdinal(ordinal: int32): GridItemStyle {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static SizeType_ToOrdinal(value: SizeType): int32 {
        return value as int32
    }
    static SizeType_FromOrdinal(ordinal: int32): SizeType {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static BreakpointsReference_ToOrdinal(value: BreakpointsReference): int32 {
        return value as int32
    }
    static BreakpointsReference_FromOrdinal(ordinal: int32): BreakpointsReference {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static GridRowDirection_ToOrdinal(value: GridRowDirection): int32 {
        return value as int32
    }
    static GridRowDirection_FromOrdinal(ordinal: int32): GridRowDirection {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static ImageRenderMode_ToOrdinal(value: ImageRenderMode): int32 {
        return value as int32
    }
    static ImageRenderMode_FromOrdinal(ordinal: int32): ImageRenderMode {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static ImageContent_ToOrdinal(value: ImageContent): int32 {
        return value as int32
    }
    static ImageContent_FromOrdinal(ordinal: int32): ImageContent {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static DynamicRangeMode_ToOrdinal(value: DynamicRangeMode): int32 {
        return value as int32
    }
    static DynamicRangeMode_FromOrdinal(ordinal: int32): DynamicRangeMode {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static ImageInterpolation_ToOrdinal(value: ImageInterpolation): int32 {
        return value as int32
    }
    static ImageInterpolation_FromOrdinal(ordinal: int32): ImageInterpolation {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static ImageAnalyzerType_ToOrdinal(value: ImageAnalyzerType): int32 {
        return value as int32
    }
    static ImageAnalyzerType_FromOrdinal(ordinal: int32): ImageAnalyzerType {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static DataOperationType_ToOrdinal(value: DataOperationType): int32 {
        return 0 // value as int32
    }
    static DataOperationType_FromOrdinal(ordinal: int32): DataOperationType {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static ScrollState_ToOrdinal(value: ScrollState): int32 {
        return value as int32
    }
    static ScrollState_FromOrdinal(ordinal: int32): ScrollState {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static ListItemAlign_ToOrdinal(value: ListItemAlign): int32 {
        return value as int32
    }
    static ListItemAlign_FromOrdinal(ordinal: int32): ListItemAlign {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static ListItemGroupArea_ToOrdinal(value: ListItemGroupArea): int32 {
        return value as int32
    }
    static ListItemGroupArea_FromOrdinal(ordinal: int32): ListItemGroupArea {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static StickyStyle_ToOrdinal(value: StickyStyle): int32 {
        return value as int32
    }
    static StickyStyle_FromOrdinal(ordinal: int32): StickyStyle {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static ChainEdgeEffect_ToOrdinal(value: ChainEdgeEffect): int32 {
        return value as int32
    }
    static ChainEdgeEffect_FromOrdinal(ordinal: int32): ChainEdgeEffect {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static ScrollSnapAlign_ToOrdinal(value: ScrollSnapAlign): int32 {
        return value as int32
    }
    static ScrollSnapAlign_FromOrdinal(ordinal: int32): ScrollSnapAlign {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static Sticky_ToOrdinal(value: Sticky): int32 {
        return value as int32
    }
    static Sticky_FromOrdinal(ordinal: int32): Sticky {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static EditMode_ToOrdinal(value: EditMode): int32 {
        return value as int32
    }
    static EditMode_FromOrdinal(ordinal: int32): EditMode {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static SwipeEdgeEffect_ToOrdinal(value: SwipeEdgeEffect): int32 {
        return value as int32
    }
    static SwipeEdgeEffect_FromOrdinal(ordinal: int32): SwipeEdgeEffect {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static SwipeActionState_ToOrdinal(value: SwipeActionState): int32 {
        return value as int32
    }
    static SwipeActionState_FromOrdinal(ordinal: int32): SwipeActionState {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static ListItemStyle_ToOrdinal(value: ListItemStyle): int32 {
        return value as int32
    }
    static ListItemStyle_FromOrdinal(ordinal: int32): ListItemStyle {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static ListItemGroupStyle_ToOrdinal(value: ListItemGroupStyle): int32 {
        return value as int32
    }
    static ListItemGroupStyle_FromOrdinal(ordinal: int32): ListItemGroupStyle {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static LoadingProgressStyle_ToOrdinal(value: LoadingProgressStyle): int32 {
        return value as int32
    }
    static LoadingProgressStyle_FromOrdinal(ordinal: int32): LoadingProgressStyle {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static LocationIconStyle_ToOrdinal(value: LocationIconStyle): int32 {
        return value as int32
    }
    static LocationIconStyle_FromOrdinal(ordinal: int32): LocationIconStyle {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static LocationDescription_ToOrdinal(value: LocationDescription): int32 {
        return value as int32
    }
    static LocationDescription_FromOrdinal(ordinal: int32): LocationDescription {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static LocationButtonOnClickResult_ToOrdinal(value: LocationButtonOnClickResult): int32 {
        return value as int32
    }
    static LocationButtonOnClickResult_FromOrdinal(ordinal: int32): LocationButtonOnClickResult {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static SubMenuExpandingMode_ToOrdinal(value: SubMenuExpandingMode): int32 {
        return value as int32
    }
    static SubMenuExpandingMode_FromOrdinal(ordinal: int32): SubMenuExpandingMode {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static NavigationSystemTransitionType_ToOrdinal(value: NavigationSystemTransitionType): int32 {
        return value as int32
    }
    static NavigationSystemTransitionType_FromOrdinal(ordinal: int32): NavigationSystemTransitionType {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static NavDestinationMode_ToOrdinal(value: NavDestinationMode): int32 {
        return value as int32
    }
    static NavDestinationMode_FromOrdinal(ordinal: int32): NavDestinationMode {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static NavRouteMode_ToOrdinal(value: NavRouteMode): int32 {
        return value as int32
    }
    static NavRouteMode_FromOrdinal(ordinal: int32): NavRouteMode {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static NavigationMode_ToOrdinal(value: NavigationMode): int32 {
        return value as int32
    }
    static NavigationMode_FromOrdinal(ordinal: int32): NavigationMode {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static NavBarPosition_ToOrdinal(value: NavBarPosition): int32 {
        return value as int32
    }
    static NavBarPosition_FromOrdinal(ordinal: int32): NavBarPosition {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static NavigationTitleMode_ToOrdinal(value: NavigationTitleMode): int32 {
        return value as int32
    }
    static NavigationTitleMode_FromOrdinal(ordinal: int32): NavigationTitleMode {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static LaunchMode_ToOrdinal(value: LaunchMode): int32 {
        return value as int32
    }
    static LaunchMode_FromOrdinal(ordinal: int32): LaunchMode {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static ToolbarItemStatus_ToOrdinal(value: ToolbarItemStatus): int32 {
        return value as int32
    }
    static ToolbarItemStatus_FromOrdinal(ordinal: int32): ToolbarItemStatus {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static NavigationOperation_ToOrdinal(value: NavigationOperation): int32 {
        return value as int32
    }
    static NavigationOperation_FromOrdinal(ordinal: int32): NavigationOperation {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static BarStyle_ToOrdinal(value: BarStyle): int32 {
        return value as int32
    }
    static BarStyle_FromOrdinal(ordinal: int32): BarStyle {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static NavigationType_ToOrdinal(value: NavigationType): int32 {
        return value as int32
    }
    static NavigationType_FromOrdinal(ordinal: int32): NavigationType {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static RouteType_ToOrdinal(value: RouteType): int32 {
        return value as int32
    }
    static RouteType_FromOrdinal(ordinal: int32): RouteType {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static SlideEffect_ToOrdinal(value: SlideEffect): int32 {
        return value as int32
    }
    static SlideEffect_FromOrdinal(ordinal: int32): SlideEffect {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static PanelMode_ToOrdinal(value: PanelMode): int32 {
        return value as int32
    }
    static PanelMode_FromOrdinal(ordinal: int32): PanelMode {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static PanelType_ToOrdinal(value: PanelType): int32 {
        return value as int32
    }
    static PanelType_FromOrdinal(ordinal: int32): PanelType {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static PanelHeight_ToOrdinal(value: PanelHeight): int32 {
        return 0 // value as int32
    }
    static PanelHeight_FromOrdinal(ordinal: int32): PanelHeight {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static ParticleType_ToOrdinal(value: ParticleType): int32 {
        return 0 // value as int32
    }
    static ParticleType_FromOrdinal(ordinal: int32): ParticleType {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static ParticleEmitterShape_ToOrdinal(value: ParticleEmitterShape): int32 {
        return 0 // value as int32
    }
    static ParticleEmitterShape_FromOrdinal(ordinal: int32): ParticleEmitterShape {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static DistributionType_ToOrdinal(value: DistributionType): int32 {
        return value as int32
    }
    static DistributionType_FromOrdinal(ordinal: int32): DistributionType {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static ParticleUpdater_ToOrdinal(value: ParticleUpdater): int32 {
        return 0 // value as int32
    }
    static ParticleUpdater_FromOrdinal(ordinal: int32): ParticleUpdater {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static DisturbanceFieldShape_ToOrdinal(value: DisturbanceFieldShape): int32 {
        return value as int32
    }
    static DisturbanceFieldShape_FromOrdinal(ordinal: int32): DisturbanceFieldShape {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static PasteIconStyle_ToOrdinal(value: PasteIconStyle): int32 {
        return value as int32
    }
    static PasteIconStyle_FromOrdinal(ordinal: int32): PasteIconStyle {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static PasteDescription_ToOrdinal(value: PasteDescription): int32 {
        return value as int32
    }
    static PasteDescription_FromOrdinal(ordinal: int32): PasteDescription {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static PasteButtonOnClickResult_ToOrdinal(value: PasteButtonOnClickResult): int32 {
        return value as int32
    }
    static PasteButtonOnClickResult_FromOrdinal(ordinal: int32): PasteButtonOnClickResult {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static PatternLockChallengeResult_ToOrdinal(value: PatternLockChallengeResult): int32 {
        return value as int32
    }
    static PatternLockChallengeResult_FromOrdinal(ordinal: int32): PatternLockChallengeResult {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static ProgressType_ToOrdinal(value: ProgressType): int32 {
        return value as int32
    }
    static ProgressType_FromOrdinal(ordinal: int32): ProgressType {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static ProgressStatus_ToOrdinal(value: ProgressStatus): int32 {
        return value as int32
    }
    static ProgressStatus_FromOrdinal(ordinal: int32): ProgressStatus {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static ProgressStyle_ToOrdinal(value: ProgressStyle): int32 {
        return value as int32
    }
    static ProgressStyle_FromOrdinal(ordinal: int32): ProgressStyle {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static RadioIndicatorType_ToOrdinal(value: RadioIndicatorType): int32 {
        return value as int32
    }
    static RadioIndicatorType_FromOrdinal(ordinal: int32): RadioIndicatorType {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static RefreshStatus_ToOrdinal(value: RefreshStatus): int32 {
        return value as int32
    }
    static RefreshStatus_FromOrdinal(ordinal: int32): RefreshStatus {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static BarrierDirection_ToOrdinal(value: BarrierDirection): int32 {
        return value as int32
    }
    static BarrierDirection_FromOrdinal(ordinal: int32): BarrierDirection {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static LocalizedBarrierDirection_ToOrdinal(value: LocalizedBarrierDirection): int32 {
        return value as int32
    }
    static LocalizedBarrierDirection_FromOrdinal(ordinal: int32): LocalizedBarrierDirection {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static RichEditorDeleteDirection_ToOrdinal(value: RichEditorDeleteDirection): int32 {
        return value as int32
    }
    static RichEditorDeleteDirection_FromOrdinal(ordinal: int32): RichEditorDeleteDirection {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static RichEditorSpanType_ToOrdinal(value: RichEditorSpanType): int32 {
        return value as int32
    }
    static RichEditorSpanType_FromOrdinal(ordinal: int32): RichEditorSpanType {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static RichEditorResponseType_ToOrdinal(value: RichEditorResponseType): int32 {
        return value as int32
    }
    static RichEditorResponseType_FromOrdinal(ordinal: int32): RichEditorResponseType {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static SaveIconStyle_ToOrdinal(value: SaveIconStyle): int32 {
        return value as int32
    }
    static SaveIconStyle_FromOrdinal(ordinal: int32): SaveIconStyle {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static SaveDescription_ToOrdinal(value: SaveDescription): int32 {
        return value as int32
    }
    static SaveDescription_FromOrdinal(ordinal: int32): SaveDescription {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static SaveButtonOnClickResult_ToOrdinal(value: SaveButtonOnClickResult): int32 {
        return value as int32
    }
    static SaveButtonOnClickResult_FromOrdinal(ordinal: int32): SaveButtonOnClickResult {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static ScrollDirection_ToOrdinal(value: ScrollDirection): int32 {
        return value as int32
    }
    static ScrollDirection_FromOrdinal(ordinal: int32): ScrollDirection {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static ScrollAlign_ToOrdinal(value: ScrollAlign): int32 {
        return value as int32
    }
    static ScrollAlign_FromOrdinal(ordinal: int32): ScrollAlign {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static ScrollBarDirection_ToOrdinal(value: ScrollBarDirection): int32 {
        return value as int32
    }
    static ScrollBarDirection_FromOrdinal(ordinal: int32): ScrollBarDirection {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static CancelButtonStyle_ToOrdinal(value: CancelButtonStyle): int32 {
        return value as int32
    }
    static CancelButtonStyle_FromOrdinal(ordinal: int32): CancelButtonStyle {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static SearchType_ToOrdinal(value: SearchType): int32 {
        return value as int32
    }
    static SearchType_FromOrdinal(ordinal: int32): SearchType {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static SecurityComponentLayoutDirection_ToOrdinal(value: SecurityComponentLayoutDirection): int32 {
        return value as int32
    }
    static SecurityComponentLayoutDirection_FromOrdinal(ordinal: int32): SecurityComponentLayoutDirection {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static ArrowPosition_ToOrdinal(value: ArrowPosition): int32 {
        return value as int32
    }
    static ArrowPosition_FromOrdinal(ordinal: int32): ArrowPosition {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static MenuAlignType_ToOrdinal(value: MenuAlignType): int32 {
        return value as int32
    }
    static MenuAlignType_FromOrdinal(ordinal: int32): MenuAlignType {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static SliderStyle_ToOrdinal(value: SliderStyle): int32 {
        return value as int32
    }
    static SliderStyle_FromOrdinal(ordinal: int32): SliderStyle {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static SliderChangeMode_ToOrdinal(value: SliderChangeMode): int32 {
        return value as int32
    }
    static SliderChangeMode_FromOrdinal(ordinal: int32): SliderChangeMode {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static SliderInteraction_ToOrdinal(value: SliderInteraction): int32 {
        return value as int32
    }
    static SliderInteraction_FromOrdinal(ordinal: int32): SliderInteraction {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static SliderBlockType_ToOrdinal(value: SliderBlockType): int32 {
        return value as int32
    }
    static SliderBlockType_FromOrdinal(ordinal: int32): SliderBlockType {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static ColorMode_ToOrdinal(value: ColorMode): int32 {
        return value as int32
    }
    static ColorMode_FromOrdinal(ordinal: int32): ColorMode {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static LayoutDirection_ToOrdinal(value: LayoutDirection): int32 {
        return value as int32
    }
    static LayoutDirection_FromOrdinal(ordinal: int32): LayoutDirection {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static ItemState_ToOrdinal(value: ItemState): int32 {
        return value as int32
    }
    static ItemState_FromOrdinal(ordinal: int32): ItemState {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static SwiperDisplayMode_ToOrdinal(value: SwiperDisplayMode): int32 {
        return value as int32
    }
    static SwiperDisplayMode_FromOrdinal(ordinal: int32): SwiperDisplayMode {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static SwiperNestedScrollMode_ToOrdinal(value: SwiperNestedScrollMode): int32 {
        return value as int32
    }
    static SwiperNestedScrollMode_FromOrdinal(ordinal: int32): SwiperNestedScrollMode {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static SymbolRenderingStrategy_ToOrdinal(value: SymbolRenderingStrategy): int32 {
        return value as int32
    }
    static SymbolRenderingStrategy_FromOrdinal(ordinal: int32): SymbolRenderingStrategy {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static SymbolEffectStrategy_ToOrdinal(value: SymbolEffectStrategy): int32 {
        return value as int32
    }
    static SymbolEffectStrategy_FromOrdinal(ordinal: int32): SymbolEffectStrategy {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static EffectFillStyle_ToOrdinal(value: EffectFillStyle): int32 {
        return value as int32
    }
    static EffectFillStyle_FromOrdinal(ordinal: int32): EffectFillStyle {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static BarMode_ToOrdinal(value: BarMode): int32 {
        return value as int32
    }
    static BarMode_FromOrdinal(ordinal: int32): BarMode {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static AnimationMode_ToOrdinal(value: AnimationMode): int32 {
        return value as int32
    }
    static AnimationMode_FromOrdinal(ordinal: int32): AnimationMode {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static BarPosition_ToOrdinal(value: BarPosition): int32 {
        return value as int32
    }
    static BarPosition_FromOrdinal(ordinal: int32): BarPosition {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static LayoutStyle_ToOrdinal(value: LayoutStyle): int32 {
        return value as int32
    }
    static LayoutStyle_FromOrdinal(ordinal: int32): LayoutStyle {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static SelectedMode_ToOrdinal(value: SelectedMode): int32 {
        return value as int32
    }
    static SelectedMode_FromOrdinal(ordinal: int32): SelectedMode {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static LayoutMode_ToOrdinal(value: LayoutMode): int32 {
        return value as int32
    }
    static LayoutMode_FromOrdinal(ordinal: int32): LayoutMode {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static TextSpanType_ToOrdinal(value: TextSpanType): int32 {
        return value as int32
    }
    static TextSpanType_FromOrdinal(ordinal: int32): TextSpanType {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static TextResponseType_ToOrdinal(value: TextResponseType): int32 {
        return value as int32
    }
    static TextResponseType_FromOrdinal(ordinal: int32): TextResponseType {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static TextAreaType_ToOrdinal(value: TextAreaType): int32 {
        return value as int32
    }
    static TextAreaType_FromOrdinal(ordinal: int32): TextAreaType {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static ContentType_ToOrdinal(value: ContentType): int32 {
        return value as int32
    }
    static ContentType_FromOrdinal(ordinal: int32): ContentType {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static TextDataDetectorType_ToOrdinal(value: TextDataDetectorType): int32 {
        return value as int32
    }
    static TextDataDetectorType_FromOrdinal(ordinal: int32): TextDataDetectorType {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static TextDeleteDirection_ToOrdinal(value: TextDeleteDirection): int32 {
        return value as int32
    }
    static TextDeleteDirection_FromOrdinal(ordinal: int32): TextDeleteDirection {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static MenuType_ToOrdinal(value: MenuType): int32 {
        return value as int32
    }
    static MenuType_FromOrdinal(ordinal: int32): MenuType {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static InputType_ToOrdinal(value: InputType): int32 {
        return value as int32
    }
    static InputType_FromOrdinal(ordinal: int32): InputType {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static EnterKeyType_ToOrdinal(value: EnterKeyType): int32 {
        return value as int32
    }
    static EnterKeyType_FromOrdinal(ordinal: int32): EnterKeyType {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static TextInputStyle_ToOrdinal(value: TextInputStyle): int32 {
        return value as int32
    }
    static TextInputStyle_FromOrdinal(ordinal: int32): TextInputStyle {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static TimePickerFormat_ToOrdinal(value: TimePickerFormat): int32 {
        return value as int32
    }
    static TimePickerFormat_FromOrdinal(ordinal: int32): TimePickerFormat {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static ToggleType_ToOrdinal(value: ToggleType): int32 {
        return value as int32
    }
    static ToggleType_FromOrdinal(ordinal: int32): ToggleType {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static SeekMode_ToOrdinal(value: SeekMode): int32 {
        return value as int32
    }
    static SeekMode_FromOrdinal(ordinal: int32): SeekMode {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static PlaybackSpeed_ToOrdinal(value: PlaybackSpeed): int32 {
        return value as int32
    }
    static PlaybackSpeed_FromOrdinal(ordinal: int32): PlaybackSpeed {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static MessageLevel_ToOrdinal(value: MessageLevel): int32 {
        return value as int32
    }
    static MessageLevel_FromOrdinal(ordinal: int32): MessageLevel {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static MixedMode_ToOrdinal(value: MixedMode): int32 {
        return value as int32
    }
    static MixedMode_FromOrdinal(ordinal: int32): MixedMode {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static HitTestType_ToOrdinal(value: HitTestType): int32 {
        return value as int32
    }
    static HitTestType_FromOrdinal(ordinal: int32): HitTestType {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static CacheMode_ToOrdinal(value: CacheMode): int32 {
        return value as int32
    }
    static CacheMode_FromOrdinal(ordinal: int32): CacheMode {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static OverScrollMode_ToOrdinal(value: OverScrollMode): int32 {
        return value as int32
    }
    static OverScrollMode_FromOrdinal(ordinal: int32): OverScrollMode {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static WebDarkMode_ToOrdinal(value: WebDarkMode): int32 {
        return value as int32
    }
    static WebDarkMode_FromOrdinal(ordinal: int32): WebDarkMode {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static WebCaptureMode_ToOrdinal(value: WebCaptureMode): int32 {
        return value as int32
    }
    static WebCaptureMode_FromOrdinal(ordinal: int32): WebCaptureMode {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static ThreatType_ToOrdinal(value: ThreatType): int32 {
        return value as int32
    }
    static ThreatType_FromOrdinal(ordinal: int32): ThreatType {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static RenderExitReason_ToOrdinal(value: RenderExitReason): int32 {
        return value as int32
    }
    static RenderExitReason_FromOrdinal(ordinal: int32): RenderExitReason {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static SslError_ToOrdinal(value: SslError): int32 {
        return value as int32
    }
    static SslError_FromOrdinal(ordinal: int32): SslError {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static FileSelectorMode_ToOrdinal(value: FileSelectorMode): int32 {
        return value as int32
    }
    static FileSelectorMode_FromOrdinal(ordinal: int32): FileSelectorMode {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static WebLayoutMode_ToOrdinal(value: WebLayoutMode): int32 {
        return value as int32
    }
    static WebLayoutMode_FromOrdinal(ordinal: int32): WebLayoutMode {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static RenderProcessNotRespondingReason_ToOrdinal(value: RenderProcessNotRespondingReason): int32 {
        return value as int32
    }
    static RenderProcessNotRespondingReason_FromOrdinal(ordinal: int32): RenderProcessNotRespondingReason {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static ProtectedResourceType_ToOrdinal(value: ProtectedResourceType): int32 {
        return 0 // value as int32
    }
    static ProtectedResourceType_FromOrdinal(ordinal: int32): ProtectedResourceType {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static ContextMenuSourceType_ToOrdinal(value: ContextMenuSourceType): int32 {
        return value as int32
    }
    static ContextMenuSourceType_FromOrdinal(ordinal: int32): ContextMenuSourceType {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static ContextMenuMediaType_ToOrdinal(value: ContextMenuMediaType): int32 {
        return value as int32
    }
    static ContextMenuMediaType_FromOrdinal(ordinal: int32): ContextMenuMediaType {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static ContextMenuInputFieldType_ToOrdinal(value: ContextMenuInputFieldType): int32 {
        return value as int32
    }
    static ContextMenuInputFieldType_FromOrdinal(ordinal: int32): ContextMenuInputFieldType {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static NativeEmbedStatus_ToOrdinal(value: NativeEmbedStatus): int32 {
        return value as int32
    }
    static NativeEmbedStatus_FromOrdinal(ordinal: int32): NativeEmbedStatus {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static ContextMenuEditStateFlags_ToOrdinal(value: ContextMenuEditStateFlags): int32 {
        return value as int32
    }
    static ContextMenuEditStateFlags_FromOrdinal(ordinal: int32): ContextMenuEditStateFlags {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static WebNavigationType_ToOrdinal(value: WebNavigationType): int32 {
        return value as int32
    }
    static WebNavigationType_FromOrdinal(ordinal: int32): WebNavigationType {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static RenderMode_ToOrdinal(value: RenderMode): int32 {
        return value as int32
    }
    static RenderMode_FromOrdinal(ordinal: int32): RenderMode {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static ViewportFit_ToOrdinal(value: ViewportFit): int32 {
        return value as int32
    }
    static ViewportFit_FromOrdinal(ordinal: int32): ViewportFit {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static WebKeyboardAvoidMode_ToOrdinal(value: WebKeyboardAvoidMode): int32 {
        return value as int32
    }
    static WebKeyboardAvoidMode_FromOrdinal(ordinal: int32): WebKeyboardAvoidMode {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static WebElementType_ToOrdinal(value: WebElementType): int32 {
        return value as int32
    }
    static WebElementType_FromOrdinal(ordinal: int32): WebElementType {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static WebResponseType_ToOrdinal(value: WebResponseType): int32 {
        return value as int32
    }
    static WebResponseType_FromOrdinal(ordinal: int32): WebResponseType {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static SideBarContainerType_ToOrdinal(value: SideBarContainerType): int32 {
        return value as int32
    }
    static SideBarContainerType_FromOrdinal(ordinal: int32): SideBarContainerType {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static SideBarPosition_ToOrdinal(value: SideBarPosition): int32 {
        return value as int32
    }
    static SideBarPosition_FromOrdinal(ordinal: int32): SideBarPosition {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static WaterFlowLayoutMode_ToOrdinal(value: WaterFlowLayoutMode): int32 {
        return value as int32
    }
    static WaterFlowLayoutMode_FromOrdinal(ordinal: int32): WaterFlowLayoutMode {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static DpiFollowStrategy_ToOrdinal(value: DpiFollowStrategy): int32 {
        return value as int32
    }
    static DpiFollowStrategy_FromOrdinal(ordinal: int32): DpiFollowStrategy {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static StyledStringKey_ToOrdinal(value: StyledStringKey): int32 {
        return value as int32
    }
    static StyledStringKey_FromOrdinal(ordinal: int32): StyledStringKey {
        throw new Error("Waiting for possibility to convert ordinal to enum from Panda team")
    }
    static isArray_String(value: object|string|number|undefined|null): boolean {
        return value instanceof Array<string>
    }
    static isArray_WebHeader(value: object|string|number|undefined|null): boolean {
        return value instanceof Array<WebHeader>
    }
    static isArray_Union_Number_String(value: object|string|number|undefined|null): boolean {
        return value instanceof Array<number | string>
    }
    static isArray_SheetInfo(value: object|string|number|undefined|null): boolean {
        return value instanceof Array<SheetInfo>
    }
    static isArray_AlertDialogButtonOptions(value: object|string|number|undefined|null): boolean {
        return value instanceof Array<AlertDialogButtonOptions>
    }
    static isArray_CalendarDay(value: object|string|number|undefined|null): boolean {
        return value instanceof Array<CalendarDay>
    }
    static isArray_Number(value: object|string|number|undefined|null): boolean {
        return value instanceof Array<number>
    }
    static isArray_CustomObject(value: object|string|number|undefined|null): boolean {
        return value instanceof Array<object>
    }
    static isArray_TouchObject(value: object|string|number|undefined|null): boolean {
        return value instanceof Array<TouchObject>
    }
    static isArray_HistoricalPoint(value: object|string|number|undefined|null): boolean {
        return value instanceof Array<HistoricalPoint>
    }
    static isArray_GestureRecognizer(value: object|string|number|undefined|null): boolean {
        return value instanceof Array<GestureRecognizer>
    }
    static isArray_DragPreviewMode(value: object|string|number|undefined|null): boolean {
        return value instanceof Array<DragPreviewMode>
    }
    static isArray_TouchTestInfo(value: object|string|number|undefined|null): boolean {
        return value instanceof Array<TouchTestInfo>
    }
    static isArray_Tuple_ResourceColor_Number(value: object|string|number|undefined|null): boolean {
        return value instanceof Array<[ ResourceColor, number ]>
    }
    static isArray_Rectangle(value: object|string|number|undefined|null): boolean {
        return value instanceof Array<Rectangle>
    }
    static isArray_UniformDataType(value: object|string|number|undefined|null): boolean {
        return value instanceof Array<UniformDataType>
    }
    static isArray_ObscuredReasons(value: object|string|number|undefined|null): boolean {
        return value instanceof Array<ObscuredReasons>
    }
    static isArray_SafeAreaType(value: object|string|number|undefined|null): boolean {
        return value instanceof Array<SafeAreaType>
    }
    static isArray_SafeAreaEdge(value: object|string|number|undefined|null): boolean {
        return value instanceof Array<SafeAreaEdge>
    }
    static isArray_MenuElement(value: object|string|number|undefined|null): boolean {
        return value instanceof Array<MenuElement>
    }
    static isArray_ModifierKey(value: object|string|number|undefined|null): boolean {
        return value instanceof Array<ModifierKey>
    }
    static isArray_Length(value: object|string|number|undefined|null): boolean {
        return value instanceof Array<Length>
    }
    static isArray_FractionStop(value: object|string|number|undefined|null): boolean {
        return value instanceof Array<FractionStop>
    }
    static isArray_LayoutChild(value: object|string|number|undefined|null): boolean {
        return value instanceof Array<LayoutChild>
    }
    static isArray_Layoutable(value: object|string|number|undefined|null): boolean {
        return value instanceof Array<Layoutable>
    }
    static isArray_Measurable(value: object|string|number|undefined|null): boolean {
        return value instanceof Array<Measurable>
    }
    static isArray_ColorStop(value: object|string|number|undefined|null): boolean {
        return value instanceof Array<ColorStop>
    }
    static isArray_Union_ResourceColor_LinearGradient(value: object|string|number|undefined|null): boolean {
        return value instanceof Array<ResourceColor | LinearGradient>
    }
    static isArray_Tuple_Union_ResourceColor_LinearGradient_Number(value: object|string|number|undefined|null): boolean {
        return value instanceof Array<[ ResourceColor | LinearGradient, number ]>
    }
    static isArray_FingerInfo(value: object|string|number|undefined|null): boolean {
        return value instanceof Array<FingerInfo>
    }
    static isArray_SourceTool(value: object|string|number|undefined|null): boolean {
        return value instanceof Array<SourceTool>
    }
    static isArray_GestureType(value: object|string|number|undefined|null): boolean {
        return value instanceof Array<GestureType>
    }
    static isArray_ImageFrameInfo(value: object|string|number|undefined|null): boolean {
        return value instanceof Array<ImageFrameInfo>
    }
    static isArray_ImageAnalyzerType(value: object|string|number|undefined|null): boolean {
        return value instanceof Array<ImageAnalyzerType>
    }
    static isArray_NavigationMenuItem(value: object|string|number|undefined|null): boolean {
        return value instanceof Array<NavigationMenuItem>
    }
    static isArray_ToolbarItem(value: object|string|number|undefined|null): boolean {
        return value instanceof Array<ToolbarItem>
    }
    static isArray_LayoutSafeAreaType(value: object|string|number|undefined|null): boolean {
        return value instanceof Array<LayoutSafeAreaType>
    }
    static isArray_LayoutSafeAreaEdge(value: object|string|number|undefined|null): boolean {
        return value instanceof Array<LayoutSafeAreaEdge>
    }
    static isArray_Point(value: object|string|number|undefined|null): boolean {
        return value instanceof Array<Point>
    }
    static isArray_GuideLineStyle(value: object|string|number|undefined|null): boolean {
        return value instanceof Array<GuideLineStyle>
    }
    static isArray_BarrierStyle(value: object|string|number|undefined|null): boolean {
        return value instanceof Array<BarrierStyle>
    }
    static isArray_LocalizedBarrierStyle(value: object|string|number|undefined|null): boolean {
        return value instanceof Array<LocalizedBarrierStyle>
    }
    static isArray_ShadowOptions(value: object|string|number|undefined|null): boolean {
        return value instanceof Array<ShadowOptions>
    }
    static isArray_ResourceColor(value: object|string|number|undefined|null): boolean {
        return value instanceof Array<ResourceColor>
    }
    static isArray_Union_RichEditorTextSpanResult_RichEditorImageSpanResult(value: object|string|number|undefined|null): boolean {
        return value instanceof Array<RichEditorTextSpanResult | RichEditorImageSpanResult>
    }
    static isArray_RichEditorTextSpanResult(value: object|string|number|undefined|null): boolean {
        return value instanceof Array<RichEditorTextSpanResult>
    }
    static isArray_RichEditorImageSpanResult(value: object|string|number|undefined|null): boolean {
        return value instanceof Array<RichEditorImageSpanResult>
    }
    static isArray_Union_RichEditorImageSpanResult_RichEditorTextSpanResult(value: object|string|number|undefined|null): boolean {
        return value instanceof Array<RichEditorImageSpanResult | RichEditorTextSpanResult>
    }
    static isArray_RichEditorParagraphResult(value: object|string|number|undefined|null): boolean {
        return value instanceof Array<RichEditorParagraphResult>
    }
    static isArray_RichEditorSpan(value: object|string|number|undefined|null): boolean {
        return value instanceof Array<RichEditorSpan>
    }
    static isArray_TextDataDetectorType(value: object|string|number|undefined|null): boolean {
        return value instanceof Array<TextDataDetectorType>
    }
    static isArray_TextBox(value: object|string|number|undefined|null): boolean {
        return value instanceof Array<TextBox>
    }
    static isArray_TextMenuItem(value: object|string|number|undefined|null): boolean {
        return value instanceof Array<TextMenuItem>
    }
    static isArray_TextCascadePickerRangeContent(value: object|string|number|undefined|null): boolean {
        return value instanceof Array<TextCascadePickerRangeContent>
    }
    static isArray_Array_String(value: object|string|number|undefined|null): boolean {
        return value instanceof Array<Array<string>>
    }
    static isArray_TextPickerRangeContent(value: object|string|number|undefined|null): boolean {
        return value instanceof Array<TextPickerRangeContent>
    }
    static isArray_Header(value: object|string|number|undefined|null): boolean {
        return value instanceof Array<Header>
    }
    static isArray_Buffer(value: object|string|number|undefined|null): boolean {
        return value instanceof Array<NativeBuffer>
    }
    static isArray_ScriptItem(value: object|string|number|undefined|null): boolean {
        return value instanceof Array<ScriptItem>
    }
    static isArray_ExpandedMenuItemOptions(value: object|string|number|undefined|null): boolean {
        return value instanceof Array<ExpandedMenuItemOptions>
    }
    static isArray_SectionOptions(value: object|string|number|undefined|null): boolean {
        return value instanceof Array<SectionOptions>
    }
    static isArray_StyleOptions(value: object|string|number|undefined|null): boolean {
        return value instanceof Array<StyleOptions>
    }
    static isArray_SpanStyle(value: object|string|number|undefined|null): boolean {
        return value instanceof Array<SpanStyle>
    }
    static isIObservedObject<T>(value: T): boolean {
        return value instanceof IObservedObject;
    }
    static isIWatchTrigger<T>(value: T): boolean {
        return value instanceof IWatchTrigger;
    }
}