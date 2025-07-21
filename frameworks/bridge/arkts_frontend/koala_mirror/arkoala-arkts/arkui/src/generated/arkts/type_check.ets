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
import { AccessibilityHoverType, Alignment, AnimationStatus, AppRotation, ArrowPointPosition, Axis, AxisAction, AxisModel, BarState, BorderStyle, CheckBoxShape, Color, ClickEffectLevel, ColoringStrategy, CopyOptions, CrownAction, CrownSensitivity, DialogButtonStyle, Direction, DividerMode, Edge, EdgeEffect, EllipsisMode, EmbeddedType, FillMode, FlexAlign, FlexDirection, FlexWrap, FocusDrawLevel, FoldStatus, FontStyle, FontWeight, FunctionKey, GradientDirection, HeightBreakpoint, HitTestMode, HorizontalAlign, HoverEffect, IlluminatedType, ImageFit, ImageRepeat, ImageSize, ImageSpanAlignment, InteractionHand, ItemAlign, KeySource, KeyType, LineBreakStrategy, LineCapStyle, LineJoinStyle, MarqueeUpdateStrategy, ModifierKey, MouseAction, MouseButton, NestedScrollMode, ObscuredReasons, OptionWidthMode, PageFlipMode, PixelRoundCalcPolicy, PixelRoundMode, Placement, PlayMode, RelateType, RenderFit, ResponseType, ScrollSource, SharedTransitionEffectType, TextAlign, TextCase, TextContentStyle, TextDecorationStyle, TextDecorationType, TextHeightAdaptivePolicy, TextOverflow, TextSelectableMode, TitleHeight, TouchType, TransitionType, WidthBreakpoint, VerticalAlign, Visibility, Week, WordBreak, XComponentType } from "./../../component/enums"
import { AccessibilityRoleType, AccessibilitySamePageMode, AdaptiveColor, BlendApplyType, BlendMode, BlurStyle, BlurStyleActivePolicy, TouchEvent, ChainStyle, ContentClipMode, DismissReason, DragBehavior, DraggingSizeChangeEffect, DragPreviewMode, DragResult, EffectEdge, EffectType, FinishCallbackType, SourceTool, GestureModifier, UIGestureEvent, HapticFeedbackMode, HoverModeAreaType, KeyboardAvoidMode, Layoutable, Measurable, GeometryInfo, SizeResult, LayoutPolicy, LayoutSafeAreaEdge, LayoutSafeAreaType, RectResult, CommonConfiguration, TranslateOptions, ScaleOptions, RotateOptions, MenuPolicy, MenuPreviewMode, ModalTransition, NestedScrollOptions, OutlineStyle, PixelMapMock, PopupStateChangeParam, PreDragStatus, ProgressMask, PopupCommonOptions, MenuOptions, RepeatMode, SelectionOptions, SafeAreaEdge, SafeAreaType, ScrollResult, ScrollSizeMode, TextContentControllerBase, ShadowStyle, ShadowType, SheetKeyboardAvoidMode, SheetMode, SheetSize, SheetType, SourceType, CaretOffset, TextContentControllerOptions, ThemeColorMode, TouchTestInfo, TouchTestStrategy, TransitionEdge, TransitionHierarchyStrategy, UICommonEvent, ClickEvent, KeyEvent, HoverCallback, HoverEvent, MouseEvent, SizeChangeCallback, VisibleAreaEventOptions, VisibleAreaChangeCallback, AnimateParam, SheetOptions, AlignRuleOption, BackgroundBrightnessOptions, BackgroundImageOptions, BackgroundOptions, BlurOptions, ChildrenMainSize, ClickEffect, CrownEvent, DateRange, DismissContentCoverAction, DismissPopupAction, DismissSheetAction, DragEvent, ModifierKeyStateGetter, Rectangle, DragInteractionOptions, DragItemInfo, DrawModifier, DropOptions, EdgeEffectOptions, ExpectedFrameRateRange, FocusMovement, ForegroundEffectOptions, GeometryTransitionOptions, InputCounterOptions, InvertOptions, ItemDragInfo, FractionStop, LinearGradientBlurOptions, LinearGradientOptions, LocalizedHorizontalAlignParam, LocalizedVerticalAlignParam, MeasureResult, MotionBlurAnchor, MotionBlurOptions, MotionPathOptions, OverlayOffset, PixelRoundPolicy, PopupButton, PreviewConfiguration, SheetDismiss, SpringBackAction, StateStyles, CustomStyles, SystemAdaptiveOptions, ShadowOptions, TouchObject, TouchResult, BackgroundBlurStyleOptions, BlurStyleOptions, BackgroundEffectOptions, MultiShadowOptions, DragPreviewOptions, FadingEdgeOptions, ForegroundBlurStyleOptions, HistoricalPoint, LightSource, LocalizedAlignRuleOptions, MenuElement, OverlayOptions, PopupMaskType, ReuseOptions, ReuseIdCallback, sharedTransitionOptions, SheetTitleOptions, TerminationInfo, TextDecorationOptions, DividerStyle, PixelStretchEffectOptions, PointLightStyle, RadialGradientOptions, SweepGradientOptions, TipsOptions, BorderImageOption, EventTarget, FocusAxisEvent, BaseEvent, LayoutChild, PickerDialogButtonStyle, PickerTextStyle, PopupMessageOptions, BindOptions, TripleLengthDetents, AccessibilityHoverEvent, AxisEvent, AsymmetricTransitionOption, TransitionEffect, ContentCoverOptions, ContextMenuAnimationOptions, AnimationNumberRange, ContextMenuOptions, BorderRadiusType, CustomPopupOptions, PopupStateChangeCallback, PopupOptions } from "./../../component/common"
import { AnimationMode, BarMode, BarPosition, LayoutStyle, TabContentTransitionProxy, TabsAnimationEvent, TabsCacheMode, TabsController, TabContentAnimatedTransition, TabsOptions, BarGridColumnOptions, ScrollableBarModeOptions } from "./../../component/tabs"
import { ArrowPosition, AvoidanceMode, MenuAlignType, MenuItemConfiguration, SelectOption, MenuOutlineOptions } from "./../../component/select"
import { AutoCapitalizationMode, KeyboardAppearance, LayoutManager, PositionWithAffinity, MenuType, TextEditControllerEx, PreviewText, StyledStringController, StyledStringChangedListener, TextBaseController, TextRange, TextDataDetectorType, TextDeleteDirection, TextMenuOptions, TextMenuItemId, TextMenuShowMode, TextMenuItem, DeleteValue, EditMenuOptions, OnCreateMenuCallback, OnMenuItemClickCallback, FontSettingOptions, InsertValue, StyledStringChangeValue, OnDidChangeCallback, DecorationStyleResult, TextChangeOptions, CaretStyle, EditableTextChangeValue, TextDataDetectorConfig } from "./../../component/textCommon"
import { BadgePosition, BadgeStyle, BadgeParamWithNumber, BadgeParam, BadgeParamWithString } from "./../../component/badge"
import { BarrierDirection, LocalizedBarrierDirection, BarrierStyle, GuideLinePosition, GuideLineStyle } from "./../../component/relativeContainer"
import { BarStyle, LaunchMode, NavBarPosition, NavigationMode, NavigationOperation, NavigationTitleMode, NavPathInfo, NavPathStack, NavigationOptions, PopInfo, NavigationInterception, ToolbarItemStatus, NavContentInfo, NavigationAnimatedTransition, NavigationTransitionProxy, InterceptionShowCallback, NavBar, InterceptionModeCallback, NavigationCommonTitle, NavigationMenuItem, UpdateTransitionCallback, ToolbarItem, MoreButtonOptions, NavigationCustomTitle, NavigationTitleOptions, NavigationMenuOptions, NavigationToolbarOptions } from "./../../component/navigation"
import { BaseContext } from "./../application.BaseContext"
import { BaseCustomComponent, ContentModifier, CustomComponentV2 } from "./../../handwritten"
import { ExtendableComponent, LifeCycle } from "./../../component/extendableComponent"
import { LayoutCallback, PageLifeCycle } from "./../../component/customComponent"
import { BaseShape, BuilderNodeOps, BuilderNodeOptions, CommonShape, Offset_componentutils, PerfMonitorActionType, PerfMonitorSourceType, RotateResult, ScaleResult, Scene, TranslateResult, WorkerEventListener, Event, DoubleAnimationParam, Callback_Extender_OnProgress, Callback_Extender_OnFinish, ErrorEvent, FontInfo, MessageEvents, PostMessageOptions, SnapshotOptions, WorkerOptions, ComponentInfo, Matrix4Result, FontOptions, MeasureOptions, RestrictedWorker, RestrictedWorker_onexit_Callback, RestrictedWorker_onerror_Callback, RestrictedWorker_onmessage_Callback } from "./../../component/idlize"
import { Length, SizeOptions, Position, ResourceColor, ColorFilter, ConstraintSizeOptions, ResourceStr, VoidCallback, AccessibilityOptions, Bias, ChainWeightOptions, DirectionalEdgesT, EdgeOutlineStyles, EdgeStyles, VP, DividerStyleOptions, EdgeColors, LengthConstrain, Dimension, LocalizedBorderRadiuses, LocalizedEdgeColors, LocalizedEdges, LocalizedEdgeWidths, LocalizedPadding, LocalizedPosition, Offset, BorderRadiuses, EdgeOutlineWidths, Edges, EdgeWidths, Font, PX, LPX, MarkStyle, OutlineRadiuses, Padding, Area, BorderOptions, OutlineOptions } from "./../../component/units"
import { Resource } from "./../resource"
import { BlurOnKeyboardHideMode, CacheMode, ClientAuthenticationHandler, ConsoleMessage, MessageLevel, ContextMenuEditStateFlags, ContextMenuInputFieldType, ContextMenuMediaType, ContextMenuSourceType, ControllerHandler, DataResubmissionHandler, EventResult, FileSelectorMode, FileSelectorParam, FileSelectorResult, FullScreenExitHandler, HitTestType, HttpAuthHandler, JsGeolocation, JsResult, MixedMode, NativeEmbedStatus, NativeMediaPlayerConfig, OnAudioStateChangedEvent, OnConsoleEvent, OnDataResubmittedEvent, OnFaviconReceivedEvent, OnFirstContentfulPaintEvent, OnOverScrollEvent, OnProgressChangeEvent, OnScaleChangeEvent, OnScrollEvent, OnSearchResultReceiveEvent, OnShowFileSelectorEvent, OverScrollMode, PermissionRequest, ProtectedResourceType, RenderExitReason, RenderMode, RenderProcessNotRespondingReason, ScreenCaptureHandler, ScreenCaptureConfig, SslError, SslErrorHandler, ThreatType, ViewportFit, WebCaptureMode, WebContextMenuParam, WebContextMenuResult, WebCookie, WebDarkMode, WebElementType, WebKeyboardAvoidMode, WebKeyboardController, WebLayoutMode, WebNavigationType, WebResourceError, Header, WebResourceRequest, WebResourceResponse, WebResponseType, AdsBlockedDetails, EmbedOptions, FirstMeaningfulPaint, FullScreenEnterEvent, IntelligentTrackingPreventionDetails, JavaScriptProxy, LargestContentfulPaint, LoadCommittedDetails, NativeEmbedVisibilityInfo, NestedScrollOptionsExt, OnAlertEvent, OnBeforeUnloadEvent, OnClientAuthenticationEvent, OnConfirmEvent, OnContextMenuShowEvent, OnDownloadStartEvent, OnErrorReceiveEvent, OnGeolocationShowEvent, OnHttpAuthRequestEvent, OnHttpErrorReceiveEvent, OnInterceptRequestEvent, OnLoadInterceptEvent, OnPageBeginEvent, OnPageEndEvent, OnPageVisibleEvent, OnPermissionRequestEvent, OnPromptEvent, OnRefreshAccessedHistoryEvent, OnRenderExitedEvent, OnResourceLoadEvent, OnScreenCaptureRequestEvent, OnSslErrorEventReceiveEvent, OnTitleReceiveEvent, OnTouchIconUrlReceivedEvent, OnWindowNewEvent, RenderProcessNotRespondingData, ScriptItem, SelectionMenuOptionsExt, SslErrorEvent, WebKeyboardCallbackInfo, WebKeyboardOptions, WebMediaOptions, WebOptions, NativeEmbedInfo, NativeEmbedDataInfo, NativeEmbedTouchInfo } from "./../../component/web"
import { BreakpointsReference, GridRowDirection, BreakPoints, GridRowColumnOption, GridRowSizeOption, GutterOption, GridRowOptions } from "./../../component/gridRow"
import { ButtonRole, ButtonStyleMode, ButtonType, ControlSize, ButtonConfiguration, ButtonTriggerClickCallback, ButtonOptions, ButtonLabelStyle } from "./../../component/button"
import { CalendarAlign, CalendarPickerDialog, CalendarDialogOptions, CalendarOptions } from "./../../component/calendarPicker"
import { CancelButtonStyle, SearchController, SearchType, CancelButtonSymbolOptions, SearchOptions, IconOptions, SearchButtonOptions, CancelButtonOptions } from "./../../component/search"
import { CanvasGradient, CanvasPath, CanvasPattern, OffscreenCanvas, ImageBitmap, RenderingContextSettings, OffscreenCanvasRenderingContext2D, Path2D, TextMetrics, DrawingRenderingContext, ImageData, CanvasRenderer, ImageSmoothingQuality, CanvasLineCap, CanvasLineJoin, CanvasDirection, CanvasTextAlign, CanvasTextBaseline, CanvasFillRule, CanvasRenderingContext2D } from "./../../component/canvas"
import { Matrix2D } from "./../../component/matrix2d"
import { ChainEdgeEffect, ListItemAlign, ListItemGroupArea, ListScroller, CloseSwipeActionOptions, VisibleListContentInfo, ScrollSnapAlign, ScrollState, StickyStyle, ListOptions, ChainAnimationOptions, ListDividerOptions } from "./../../component/list"
import { CircleOptions } from "./../../component/circle"
import { CircleShape, ShapeSize, EllipseShape, PathShape, PathShapeOptions, RectShape, RectShapeOptions, RoundRectShapeOptions } from "./../ohos.arkui.shape"
import { ColorContent, DynamicRangeMode, ImageContent, ImageInterpolation, ImageRenderMode, ImageRotateOrientation, ImageCompleteEvent, ImageSourceSize, ImageError, ResizableOptions } from "./../../component/image"
import { ColorMetrics, CornerRadius, DrawContext, Size, LengthMetricsUnit, LengthUnit, ShapeClip, RoundRect, Circle, CommandPath, ShapeMask, Vector2, Vector3, LengthMetrics, Frame } from "./../arkui.Graphics"
import { ColorMode, LayoutDirection } from "./../../component/stateManagement"
import { ComponentContent } from "./../arkui.ComponentContent"
import { ContentType, EnterKeyType, InputType, SubmitEvent, TextInputController, TextInputStyle, PasswordIcon, TextInputOptions, UnderlineColor } from "./../../component/textInput"
import { Context } from "./../application.Context"
import { webview } from "./../ohos.web.webview"
import { curves } from "./../ohos.curves"
import { CustomDialogController, CustomDialogControllerOptions } from "./../../component/customDialogController"
import { DataOperationType } from "./../../component/lazyForEach"
import { DataPanelType, ColorStop, LinearGradient, DataPanelConfiguration, DataPanelOptions, DataPanelShadowOptions } from "./../../component/dataPanel"
import { DatePickerDialog, DatePickerMode, DatePickerOptions } from "./../../component/datePicker"
import { DialogAlignment, DialogButtonDirection, AlertDialogButtonOptions } from "./../../component/alertDialog"
import { DistributionType, DisturbanceFieldShape, ParticleEmitterShape, ParticleType, ParticleUpdater, ParticlePropertyAnimation } from "./../../component/particle"
import { DpiFollowStrategy, UIExtensionProxy, WindowModeFollowStrategy, UIExtensionOptions } from "./../../component/uiExtensionComponent"
import { DrawableDescriptor } from "./../ohos.arkui.drawableDescriptor"
import { image } from "./../ohos.multimedia.image"
import { drawing } from "./../ohos.graphics.drawing"
import { common2D } from "./../ohos.graphics.common2D"
import { EffectDirection, EffectFillStyle, EffectScope, SymbolEffect, SymbolEffectStrategy, SymbolRenderingStrategy, AppearSymbolEffect, BounceSymbolEffect, DisappearSymbolEffect, HierarchicalSymbolEffect, ReplaceSymbolEffect, ScaleSymbolEffect } from "./../../component/symbolglyph"
import { EllipseOptions } from "./../../component/ellipse"
import { EventTargetInfo, Gesture, GestureControl, GestureType, GestureMode, GestureJudgeResult, GestureMask, GesturePriority, GestureRecognizer, GestureRecognizerState, LongPressGestureHandlerOptions, GestureEvent, LongPressRecognizer, PanDirection, PanGestureOptions, PanGestureHandlerOptions, PanRecognizer, PinchGestureHandlerOptions, PinchRecognizer, RotationGesture, RotationGestureHandlerOptions, RotationRecognizer, ScrollableTargetInfo, SwipeDirection, SwipeGesture, SwipeGestureHandlerOptions, SwipeRecognizer, TapGestureParameters, TapRecognizer, GestureHandler, FingerInfo, GestureInfo, BaseHandlerOptions, LongPressGestureEvent, BaseGestureEvent, PanGestureEvent, PinchGestureEvent, RotationGestureEvent, SwipeGestureEvent, TapGestureEvent } from "./../../component/gesture"
import { UIContext, PromptAction, TargetInfo, TextMenuController } from "./../ohos.arkui.UIContext"
import { FocusPriority, KeyProcessingMode, FocusBoxStyle } from "./../../component/focus"
import { FormDimension, FormRenderingMode, FormShape, FormSize, ErrorInformation, FormCallbackInfo, FormInfo } from "./../../component/formComponent"
import { FrameNode, CrossLanguageOptions, LayoutConstraint } from "./../arkui.FrameNode"
import { FrictionMotion, ScrollMotion, SpringProp, SpringMotion } from "./../../component/animator"
import { FullscreenInfo, PlaybackInfo, PlaybackSpeed, PreparedInfo, SeekMode, VideoController, PosterOptions, VideoOptions } from "./../../component/video"
import { GestureGroupInterface, LongPressGestureInterface, GestureInterface, LongPressGestureInterface_Invoke_Literal, PanGestureInterface, PanGestureInterface_Invoke_Literal, PinchGestureInterface, PinchGestureInterface_Invoke_Literal, TapGestureInterface } from "./../../component/gesture.extra"
import { GestureStyle, GestureStyleInterface, StyledString, MutableStyledString, StyleOptions, SpanStyle, ImageAttachment, CustomSpan, StyledStringKey, StyledStringMarshallCallback, UserDataSpan, StyledStringUnmarshallCallback, UrlStyle, BaselineOffsetStyle, CustomSpanMeasureInfo, CustomSpanMetrics, CustomSpanDrawInfo, LetterSpacingStyle, LineHeightStyle, TextShadowStyle, DecorationStyle, DecorationStyleInterface, TextStyle, TextStyleInterface, ImageAttachmentLayoutStyle, ParagraphStyle, ParagraphStyleInterface, BackgroundColorStyle, ColorFilterType, ImageAttachmentInterface, AttachmentType, ResourceImageAttachmentOptions, StyledStringValue } from "./../../component/styledString"
import { GridDirection, GridItemAlignment, ComputedBarAttribute, GridLayoutOptions } from "./../../component/grid"
import { GridItemStyle, GridItemOptions } from "./../../component/gridItem"
import { ImageAnalyzerType, ImageAnalyzerController, ImageAIOptions, ImageAnalyzerConfig } from "./../../component/imageCommon"
import { ImmersiveMode, LevelMode, LevelOrder } from "./../ohos.promptAction"
import { IndexerAlign, AlphabetIndexerOptions } from "./../../component/alphabetIndexer"
import { IndicatorComponentController } from "./../../component/indicatorcomponent"
import { IntentionCode } from "./../ohos.multimodalInput.intentionCode"
import { ItemState } from "./../../component/stepperItem"
import { LayoutMode, SelectedMode, TabBarSymbol, TabBarIconStyle, TabBarOptions, BoardStyle, SubTabBarIndicatorStyle, TabBarLabelStyle, BottomTabBarStyle, SubTabBarStyle } from "./../../component/tabContent"
import { LinearIndicatorController, LinearIndicatorStartOptions, LinearIndicatorStyle } from "./../../component/linearindicator"
import { LineOptions, ShapePoint } from "./../../component/line"
import { ListItemGroupStyle, ListItemGroupOptions } from "./../../component/listItemGroup"
import { ListItemStyle, SwipeActionState, SwipeEdgeEffect, ListItemOptions, SwipeActionItem, SwipeActionOptions } from "./../../component/listItem"
import { Scroller, ScrollAlign, OffsetResult, OnScrollFrameBeginHandlerResult, ScrollDirection, ScrollOptions, ScrollEdgeOptions, ScrollPageOptions, ScrollToIndexOptions, ScrollAnimationOptions, OffsetOptions, ScrollSnapOptions } from "./../../component/scroll"
import { LoadingProgressConfiguration, LoadingProgressStyle } from "./../../component/loadingProgress"
import { LocationButtonOnClickResult, LocationDescription, LocationIconStyle } from "./../../component/locationButton"
import { MarqueeStartPolicy, MarqueeState, TextController, TextOptions, TextOverflowOptions, TextResponseType, TextSpanType, TextMarqueeOptions } from "./../../component/text"
import { matrix4 } from "./../ohos.matrix4"
import { NavDestinationActiveReason, NavDestinationMode, NavigationSystemTransitionType, NavDestinationTransition, NavDestinationContext, NestedScrollInfo, RouteMapConfig, NavDestinationCommonTitle, NavDestinationCustomTitle } from "./../../component/navDestination"
import { NavigationType } from "./../../component/navigator"
import { NodeContent } from "./../arkui.nodecontent"
import { Content } from "./../ohos.arkui.node"
import { NodeController } from "./../arkui.NodeController"
import { OnFoldStatusChangeInfo, FolderStackOptions, HoverEventParam } from "./../../component/folderStack"
import { PasteButtonOnClickResult, PasteDescription, PasteIconStyle } from "./../../component/pasteButton"
import { PathOptions } from "./../../component/path"
import { PatternLockChallengeResult, PatternLockController, CircleStyleOptions } from "./../../component/patternLock"
import { pointer } from "./../ohos.multimodalInput.pointer"
import { PolygonOptions } from "./../../component/polygon"
import { PolylineOptions } from "./../../component/polyline"
import { ProgressConfiguration, ProgressStatus, ProgressStyle, ProgressType, ProgressOptions, LinearStyleOptions, ScanEffectOptions, CommonProgressStyleOptions, ProgressStyleOptions, RingStyleOptions, CapsuleStyleOptions } from "./../../component/progress"
import { RadioIndicatorType, RadioConfiguration, RadioOptions, RadioStyle } from "./../../component/radio"
import { RefreshStatus, RefreshOptions } from "./../../component/refresh"
import { RichEditorBaseController, RichEditorTextStyle, RichEditorParagraphResult, RichEditorSpan, RichEditorController, RichEditorTextSpanOptions, RichEditorImageSpanOptions, RichEditorBuilderSpanOptions, RichEditorSymbolSpanOptions, RichEditorUpdateTextSpanStyleOptions, RichEditorUpdateImageSpanStyleOptions, RichEditorUpdateSymbolSpanStyleOptions, RichEditorParagraphStyleOptions, RichEditorRange, RichEditorImageSpanResult, RichEditorTextSpanResult, RichEditorSelection, RichEditorDeleteDirection, RichEditorOptions, RichEditorResponseType, RichEditorSpanType, RichEditorStyledStringController, RichEditorStyledStringOptions, KeyboardOptions, PreviewMenuOptions, RichEditorDeleteValue, RichEditorGesture, RichEditorInsertValue, RichEditorSpanPosition, CopyEvent, CutEvent, PasteEvent, RichEditorChangeValue, RichEditorSymbolSpanStyle, RichEditorSpanStyleOptions, RichEditorUrlStyle, SelectionMenuOptions, MenuOnAppearCallback, MenuCallback, LeadingMarginPlaceholder, PlaceholderStyle, RichEditorLayoutStyle, RichEditorParagraphStyle, RichEditorImageSpanStyle, RichEditorImageSpanStyleResult, RichEditorTextStyleResult, OnHoverCallback } from "./../../component/richEditor"
import { CustomBuilder } from "./../../component/builder"
import { RootSceneSession } from "./../../component/rootScene"
import { RoundedRectOptions, RadiusItem, RectOptions } from "./../../component/rect"
import { RouteType, SlideEffect } from "./../../component/pageTransition"
import { RowOptionsV2, RowOptions } from "./../../component/row"
import { RRect, WindowAnimationTarget } from "./../../component/remoteWindow"
import { SaveButtonOnClickResult, SaveDescription, SaveIconStyle } from "./../../component/saveButton"
import { ScrollBarDirection, ScrollBarOptions } from "./../../component/scrollBar"
import { SecurityComponentLayoutDirection } from "./../../component/securityComponent"
import { SelectStatus, CheckboxGroupOptions, CheckboxGroupResult } from "./../../component/checkboxgroup"
import { SideBarContainerType, SideBarPosition, ButtonIconOptions, ButtonStyle } from "./../../component/sidebar"
import { SliderBlockType, SliderChangeMode, SliderInteraction, SliderStyle, SlideRange, SliderConfiguration, SliderTriggerChangeCallback, SliderOptions, SliderBlockStyle } from "./../../component/slider"
import { SubMenuExpandingMode } from "./../../component/menu"
import { SwiperAnimationEvent, SwiperAnimationMode, SwiperContentTransitionProxy, SwiperContentWillScrollResult, SwiperController, SwiperDisplayMode, SwiperNestedScrollMode, AutoPlayOptions, SwiperAutoFill, SwiperContentAnimatedTransition, ArrowStyle, DotIndicator, Indicator, DigitIndicator } from "./../../component/swiper"
import { SymbolGlyphModifier } from "./../arkui.SymbolGlyphModifier"
import { text } from "./../ohos.graphics.text"
import { TextAreaController, TextAreaType, TextAreaOptions } from "./../../component/textArea"
import { TextClockConfiguration, TextClockController, TextClockOptions } from "./../../component/textClock"
import { TextModifier } from "./../arkui.TextModifier"
import { TextPickerDialog, TextPickerDialogOptions, TextCascadePickerRangeContent, TextPickerRangeContent, TextPickerOptions, TextPickerResult, DividerOptions, TextPickerTextStyle } from "./../../component/textPicker"
import { TextTimerConfiguration, TextTimerController, TextTimerOptions } from "./../../component/textTimer"
import { ThemeControl, CustomTheme, Colors } from "./../ohos.arkui.theme"
import { TimePickerDialog, TimePickerFormat, TimePickerResult, TimePickerOptions } from "./../../component/timePicker"
import { ToggleType, ToggleConfiguration, ToggleOptions, SwitchStyle } from "./../../component/toggle"
import { common, Context_getGroupDir_Callback } from "./../ohos.app.ability.common"
import { uiEffect } from "./../ohos.graphics.uiEffect"
import { unifiedDataChannel } from "./../ohos.data.unifiedDataChannel"
import { uniformTypeDescriptor } from "./../ohos.data.uniformTypeDescriptor"
import { WaterFlowLayoutMode, SectionOptions, WaterFlowSections, WaterFlowOptions, GetItemMainSizeByIndex } from "./../../component/waterFlow"
import { window } from "./../ohos.window"
import { ASTCResource } from "./../../component/mediaCachedImage"
import { BorderRadiuses_graphics, RenderNode } from "./../arkui.RenderNode"
import { BusinessError } from "./../ohos.base"
import { CheckBoxConfiguration, CheckboxOptions } from "./../../component/checkbox"
import { ColumnOptions, ColumnOptionsV2 } from "./../../component/column"
import { CompatibleComponentInfo } from "./../../component/interop"
import { DismissDialogAction, SheetInfo } from "./../../component/actionSheet"
import { font } from "./../ohos.font"
import { FormLinkOptions } from "./../../component/formLink"
import { GaugeConfiguration, GaugeOptions, GaugeShadowOptions, GaugeIndicatorOptions } from "./../../component/gauge"
import { GridColColumnOption, GridColOptions } from "./../../component/gridCol"
import { ImageLoadResult } from "./../../component/imageSpan"
import { intl } from "./../ohos.intl"
import { MarqueeOptions } from "./../../component/marquee"
import { PluginComponentTemplate, PluginErrorData, PluginComponentOptions } from "./../../component/pluginComponent"
import { RatingConfiguration, RatingOptions, StarStyleOptions } from "./../../component/rating"
import { StackOptions } from "./../../component/stack"
import { StepperOptions } from "./../../component/stepper"
import { SurfaceRect, SurfaceRotationOptions, XComponentController, NativeXComponentParameters, XComponentOptions, XComponentParameter } from "./../../component/xcomponent"
import { Want } from "./../ohos.app.ability.Want"
import { FlexSpaceOptions, FlexOptions } from "./../../component/flex"
import { ImageFrameInfo } from "./../../component/imageAnimator"
import { MenuItemGroupOptions } from "./../../component/menuItemGroup"
import { MenuItemOptions } from "./../../component/menuItem"
import { ColumnSplitDividerStyle } from "./../../component/columnSplit"
import { ViewportRect } from "./../../component/shape"
import { TextBackgroundStyle } from "./../../component/span"
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
    static isAccessibilityHoverEvent(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean): boolean {
        return value instanceof AccessibilityHoverEvent
    }
    static isAccessibilityHoverType(value: Object | string | number | undefined): boolean {
        return value instanceof AccessibilityHoverType
    }
    static isAccessibilityOptions(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof AccessibilityOptions
    }
    static isAccessibilityRoleType(value: Object | string | number | undefined): boolean {
        return value instanceof AccessibilityRoleType
    }
    static isAccessibilitySamePageMode(value: Object | string | number | undefined): boolean {
        return value instanceof AccessibilitySamePageMode
    }
    static isAdaptiveColor(value: Object | string | number | undefined): boolean {
        return value instanceof AdaptiveColor
    }
    static isAdsBlockedDetails(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof AdsBlockedDetails
    }
    static isAlignment(value: Object | string | number | undefined): boolean {
        return value instanceof Alignment
    }
    static isAlignRuleOption(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof AlignRuleOption
    }
    static isAlphabetIndexerOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof AlphabetIndexerOptions
    }
    static isAnimateParam(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean): boolean {
        return value instanceof AnimateParam
    }
    static isAnimationMode(value: Object | string | number | undefined): boolean {
        return value instanceof AnimationMode
    }
    static isAnimationStatus(value: Object | string | number | undefined): boolean {
        return value instanceof AnimationStatus
    }
    static isAppearSymbolEffect(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof AppearSymbolEffect
    }
    static isAppRotation(value: Object | string | number | undefined): boolean {
        return value instanceof AppRotation
    }
    static isArea(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof Area
    }
    static isArrowPointPosition(value: Object | string | number | undefined): boolean {
        return value instanceof ArrowPointPosition
    }
    static isArrowPosition(value: Object | string | number | undefined): boolean {
        return value instanceof ArrowPosition
    }
    static isArrowStyle(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean): boolean {
        return value instanceof ArrowStyle
    }
    static isASTCResource(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof ASTCResource
    }
    static isAsymmetricTransitionOption(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof AsymmetricTransitionOption
    }
    static isAutoCapitalizationMode(value: Object | string | number | undefined): boolean {
        return value instanceof AutoCapitalizationMode
    }
    static isAutoPlayOptions(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof AutoPlayOptions
    }
    static isAvoidanceMode(value: Object | string | number | undefined): boolean {
        return value instanceof AvoidanceMode
    }
    static isAxis(value: Object | string | number | undefined): boolean {
        return value instanceof Axis
    }
    static isAxisAction(value: Object | string | number | undefined): boolean {
        return value instanceof AxisAction
    }
    static isAxisEvent(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean): boolean {
        return value instanceof AxisEvent
    }
    static isAxisModel(value: Object | string | number | undefined): boolean {
        return value instanceof AxisModel
    }
    static isBackgroundBlurStyleOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof BackgroundBlurStyleOptions
    }
    static isBackgroundBrightnessOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof BackgroundBrightnessOptions
    }
    static isBackgroundColorStyle(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof BackgroundColorStyle
    }
    static isBackgroundEffectOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean): boolean {
        return value instanceof BackgroundEffectOptions
    }
    static isBackgroundImageOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof BackgroundImageOptions
    }
    static isBackgroundOptions(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof BackgroundOptions
    }
    static isBadgeParamWithNumber(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof BadgeParamWithNumber
    }
    static isBadgeParamWithString(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof BadgeParamWithString
    }
    static isBadgePosition(value: Object | string | number | undefined): boolean {
        return value instanceof BadgePosition
    }
    static isBadgeStyle(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean): boolean {
        return value instanceof BadgeStyle
    }
    static isBarGridColumnOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean): boolean {
        return value instanceof BarGridColumnOptions
    }
    static isBarMode(value: Object | string | number | undefined): boolean {
        return value instanceof BarMode
    }
    static isBarPosition(value: Object | string | number | undefined): boolean {
        return value instanceof BarPosition
    }
    static isBarrierDirection(value: Object | string | number | undefined): boolean {
        return value instanceof BarrierDirection
    }
    static isBarrierStyle(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof BarrierStyle
    }
    static isBarState(value: Object | string | number | undefined): boolean {
        return value instanceof BarState
    }
    static isBarStyle(value: Object | string | number | undefined): boolean {
        return value instanceof BarStyle
    }
    static isBaseContext(value: Object | string | number | undefined): boolean {
        return value instanceof BaseContext
    }
    static isBaseCustomComponent(value: Object | string | number | undefined): boolean {
        return value instanceof BaseCustomComponent
    }
    static isBaseEvent(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean, arg9: boolean, arg10: boolean, arg11: boolean, arg12: boolean): boolean {
        return value instanceof BaseEvent
    }
    static isBaseGestureEvent(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof BaseGestureEvent
    }
    static isBaselineOffsetStyle(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof BaselineOffsetStyle
    }
    static isBaseShape(value: Object | string | number | undefined): boolean {
        return value instanceof BaseShape
    }
    static isBias(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof Bias
    }
    static isBlendApplyType(value: Object | string | number | undefined): boolean {
        return value instanceof BlendApplyType
    }
    static isBlendMode(value: Object | string | number | undefined): boolean {
        return value instanceof BlendMode
    }
    static isBlurOnKeyboardHideMode(value: Object | string | number | undefined): boolean {
        return value instanceof BlurOnKeyboardHideMode
    }
    static isBlurOptions(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof BlurOptions
    }
    static isBlurStyle(value: Object | string | number | undefined): boolean {
        return value instanceof BlurStyle
    }
    static isBlurStyleActivePolicy(value: Object | string | number | undefined): boolean {
        return value instanceof BlurStyleActivePolicy
    }
    static isBoardStyle(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof BoardStyle
    }
    static isBorderImageOption(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean): boolean {
        return value instanceof BorderImageOption
    }
    static isBorderOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean): boolean {
        return value instanceof BorderOptions
    }
    static isBorderRadiuses(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof BorderRadiuses
    }
    static isBorderRadiuses_graphics(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof BorderRadiuses_graphics
    }
    static isBorderStyle(value: Object | string | number | undefined): boolean {
        return value instanceof BorderStyle
    }
    static isBottomTabBarStyle(value: Object | string | number | undefined): boolean {
        return value instanceof BottomTabBarStyle
    }
    static isBounceSymbolEffect(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof BounceSymbolEffect
    }
    static isBreakPoints(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof BreakPoints
    }
    static isBreakpointsReference(value: Object | string | number | undefined): boolean {
        return value instanceof BreakpointsReference
    }
    static isBuilderNodeOps(value: Object | string | number | undefined): boolean {
        return value instanceof BuilderNodeOps
    }
    static isBuilderNodeOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof BuilderNodeOptions
    }
    static isBusinessError(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof BusinessError
    }
    static isButtonConfiguration(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof ButtonConfiguration
    }
    static isButtonIconOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof ButtonIconOptions
    }
    static isButtonLabelStyle(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean): boolean {
        return value instanceof ButtonLabelStyle
    }
    static isButtonOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean): boolean {
        return value instanceof ButtonOptions
    }
    static isButtonRole(value: Object | string | number | undefined): boolean {
        return value instanceof ButtonRole
    }
    static isButtonStyle(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean): boolean {
        return value instanceof ButtonStyle
    }
    static isButtonStyleMode(value: Object | string | number | undefined): boolean {
        return value instanceof ButtonStyleMode
    }
    static isButtonType(value: Object | string | number | undefined): boolean {
        return value instanceof ButtonType
    }
    static isCacheMode(value: Object | string | number | undefined): boolean {
        return value instanceof CacheMode
    }
    static isCalendarAlign(value: Object | string | number | undefined): boolean {
        return value instanceof CalendarAlign
    }
    static isCalendarDialogOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean, arg9: boolean, arg10: boolean, arg11: boolean, arg12: boolean, arg13: boolean, arg14: boolean, arg15: boolean, arg16: boolean): boolean {
        return value instanceof CalendarDialogOptions
    }
    static isCalendarOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean): boolean {
        return value instanceof CalendarOptions
    }
    static isCalendarPickerDialog(value: Object | string | number | undefined): boolean {
        return value instanceof CalendarPickerDialog
    }
    static isCancelButtonOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof CancelButtonOptions
    }
    static isCancelButtonStyle(value: Object | string | number | undefined): boolean {
        return value instanceof CancelButtonStyle
    }
    static isCancelButtonSymbolOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof CancelButtonSymbolOptions
    }
    static isCanvasGradient(value: Object | string | number | undefined): boolean {
        return value instanceof CanvasGradient
    }
    static isCanvasPath(value: Object | string | number | undefined): boolean {
        return value instanceof CanvasPath
    }
    static isCanvasPattern(value: Object | string | number | undefined): boolean {
        return value instanceof CanvasPattern
    }
    static isCanvasRenderer(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean, arg9: boolean, arg10: boolean, arg11: boolean, arg12: boolean, arg13: boolean, arg14: boolean, arg15: boolean, arg16: boolean, arg17: boolean, arg18: boolean, arg19: boolean, arg20: boolean): boolean {
        return value instanceof CanvasRenderer
    }
    static isCanvasRenderingContext2D(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof CanvasRenderingContext2D
    }
    static isCapsuleStyleOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean): boolean {
        return value instanceof CapsuleStyleOptions
    }
    static isCaretOffset(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof CaretOffset
    }
    static isCaretStyle(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof CaretStyle
    }
    static isChainAnimationOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean): boolean {
        return value instanceof ChainAnimationOptions
    }
    static isChainEdgeEffect(value: Object | string | number | undefined): boolean {
        return value instanceof ChainEdgeEffect
    }
    static isChainStyle(value: Object | string | number | undefined): boolean {
        return value instanceof ChainStyle
    }
    static isChainWeightOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof ChainWeightOptions
    }
    static isCheckBoxConfiguration(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof CheckBoxConfiguration
    }
    static isCheckboxGroupOptions(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof CheckboxGroupOptions
    }
    static isCheckboxGroupResult(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof CheckboxGroupResult
    }
    static isCheckboxOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof CheckboxOptions
    }
    static isCheckBoxShape(value: Object | string | number | undefined): boolean {
        return value instanceof CheckBoxShape
    }
    static isChildrenMainSize(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof ChildrenMainSize
    }
    static isCircle(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof Circle
    }
    static isCircleOptions(value: Object | string | number | undefined): boolean {
        return value instanceof CircleOptions
    }
    static isCircleShape(value: Object | string | number | undefined): boolean {
        return value instanceof CircleShape
    }
    static isCircleStyleOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof CircleStyleOptions
    }
    static isClickEffect(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof ClickEffect
    }
    static isClickEffectLevel(value: Object | string | number | undefined): boolean {
        return value instanceof ClickEffectLevel
    }
    static isClickEvent(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean): boolean {
        return value instanceof ClickEvent
    }
    static isClientAuthenticationHandler(value: Object | string | number | undefined): boolean {
        return value instanceof ClientAuthenticationHandler
    }
    static isCloseSwipeActionOptions(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof CloseSwipeActionOptions
    }
    static isColor(value: Object | string | number | undefined): boolean {
        return value instanceof Color
    }
    static isColorContent(value: Object | string | number | undefined): boolean {
        return value instanceof ColorContent
    }
    static isColorFilter(value: Object | string | number | undefined): boolean {
        return value instanceof ColorFilter
    }
    static isColoringStrategy(value: Object | string | number | undefined): boolean {
        return value instanceof ColoringStrategy
    }
    static isColorMetrics(value: Object | string | number | undefined): boolean {
        return value instanceof ColorMetrics
    }
    static isColorMode(value: Object | string | number | undefined): boolean {
        return value instanceof ColorMode
    }
    static isColors(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean, arg9: boolean, arg10: boolean, arg11: boolean, arg12: boolean, arg13: boolean, arg14: boolean, arg15: boolean, arg16: boolean, arg17: boolean, arg18: boolean, arg19: boolean, arg20: boolean, arg21: boolean, arg22: boolean, arg23: boolean, arg24: boolean, arg25: boolean, arg26: boolean, arg27: boolean, arg28: boolean, arg29: boolean, arg30: boolean, arg31: boolean, arg32: boolean, arg33: boolean, arg34: boolean, arg35: boolean, arg36: boolean, arg37: boolean, arg38: boolean, arg39: boolean, arg40: boolean, arg41: boolean, arg42: boolean, arg43: boolean, arg44: boolean, arg45: boolean, arg46: boolean, arg47: boolean, arg48: boolean, arg49: boolean, arg50: boolean): boolean {
        return value instanceof Colors
    }
    static isColorStop(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof ColorStop
    }
    static isColumnOptions(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof ColumnOptions
    }
    static isColumnOptionsV2(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof ColumnOptionsV2
    }
    static isColumnSplitDividerStyle(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof ColumnSplitDividerStyle
    }
    static isCommandPath(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof CommandPath
    }
    static iscommon_Context(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean): boolean {
        return value instanceof common.Context
    }
    static iscommon2D_Color(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof common2D.Color
    }
    static iscommon2D_Point(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof common2D.Point
    }
    static iscommon2D_Point3d(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof common2D.Point3d
    }
    static iscommon2D_Rect(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof common2D.Rect
    }
    static isCommonShape(value: Object | string | number | undefined): boolean {
        return value instanceof CommonShape
    }
    static isCompatibleComponentInfo(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof CompatibleComponentInfo
    }
    static isComponentContent(value: Object | string | number | undefined): boolean {
        return value instanceof ComponentContent
    }
    static isComponentInfo(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean): boolean {
        return value instanceof ComponentInfo
    }
    static isComputedBarAttribute(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof ComputedBarAttribute
    }
    static isConsoleMessage(value: Object | string | number | undefined): boolean {
        return value instanceof ConsoleMessage
    }
    static isConstraintSizeOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof ConstraintSizeOptions
    }
    static isContentClipMode(value: Object | string | number | undefined): boolean {
        return value instanceof ContentClipMode
    }
    static isContentCoverOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof ContentCoverOptions
    }
    static isContentModifier(value: Object | string | number | undefined): boolean {
        return value instanceof ContentModifier
    }
    static isContentType(value: Object | string | number | undefined): boolean {
        return value instanceof ContentType
    }
    static isContext(value: Object | string | number | undefined): boolean {
        return value instanceof Context
    }
    static isContextMenuAnimationOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof ContextMenuAnimationOptions
    }
    static isContextMenuEditStateFlags(value: Object | string | number | undefined): boolean {
        return value instanceof ContextMenuEditStateFlags
    }
    static isContextMenuInputFieldType(value: Object | string | number | undefined): boolean {
        return value instanceof ContextMenuInputFieldType
    }
    static isContextMenuMediaType(value: Object | string | number | undefined): boolean {
        return value instanceof ContextMenuMediaType
    }
    static isContextMenuOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean, arg9: boolean, arg10: boolean, arg11: boolean, arg12: boolean, arg13: boolean, arg14: boolean, arg15: boolean, arg16: boolean, arg17: boolean, arg18: boolean, arg19: boolean, arg20: boolean, arg21: boolean): boolean {
        return value instanceof ContextMenuOptions
    }
    static isContextMenuSourceType(value: Object | string | number | undefined): boolean {
        return value instanceof ContextMenuSourceType
    }
    static isControllerHandler(value: Object | string | number | undefined): boolean {
        return value instanceof ControllerHandler
    }
    static isControlSize(value: Object | string | number | undefined): boolean {
        return value instanceof ControlSize
    }
    static isCopyEvent(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof CopyEvent
    }
    static isCopyOptions(value: Object | string | number | undefined): boolean {
        return value instanceof CopyOptions
    }
    static isCornerRadius(value: Object | string | number | undefined): boolean {
        return value instanceof CornerRadius
    }
    static isCrossLanguageOptions(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof CrossLanguageOptions
    }
    static isCrownAction(value: Object | string | number | undefined): boolean {
        return value instanceof CrownAction
    }
    static isCrownEvent(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean): boolean {
        return value instanceof CrownEvent
    }
    static isCrownSensitivity(value: Object | string | number | undefined): boolean {
        return value instanceof CrownSensitivity
    }
    static iscurves_Curve(value: Object | string | number | undefined): boolean {
        return value instanceof curves.Curve
    }
    static iscurves_ICurve(value: Object | string | number | undefined): boolean {
        return value instanceof curves.ICurve
    }
    static isCustomComponentV2(value: Object | string | number | undefined): boolean {
        return value instanceof CustomComponentV2
    }
    static isCustomDialogController(value: Object | string | number | undefined): boolean {
        return value instanceof CustomDialogController
    }
    static isCustomDialogControllerOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean, arg9: boolean, arg10: boolean, arg11: boolean, arg12: boolean, arg13: boolean, arg14: boolean, arg15: boolean, arg16: boolean, arg17: boolean, arg18: boolean, arg19: boolean, arg20: boolean, arg21: boolean, arg22: boolean, arg23: boolean, arg24: boolean, arg25: boolean, arg26: boolean, arg27: boolean, arg28: boolean, arg29: boolean, arg30: boolean, arg31: boolean, arg32: boolean, arg33: boolean, arg34: boolean, arg35: boolean, arg36: boolean, arg37: boolean): boolean {
        return value instanceof CustomDialogControllerOptions
    }
    static isCustomPopupOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean, arg9: boolean, arg10: boolean, arg11: boolean, arg12: boolean, arg13: boolean, arg14: boolean, arg15: boolean, arg16: boolean, arg17: boolean, arg18: boolean, arg19: boolean, arg20: boolean, arg21: boolean, arg22: boolean, arg23: boolean): boolean {
        return value instanceof CustomPopupOptions
    }
    static isCustomSpan(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof CustomSpan
    }
    static isCustomSpanDrawInfo(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof CustomSpanDrawInfo
    }
    static isCustomSpanMeasureInfo(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof CustomSpanMeasureInfo
    }
    static isCustomSpanMetrics(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof CustomSpanMetrics
    }
    static isCustomTheme(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof CustomTheme
    }
    static isCutEvent(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof CutEvent
    }
    static isDataOperationType(value: Object | string | number | undefined): boolean {
        return value instanceof DataOperationType
    }
    static isDataPanelConfiguration(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof DataPanelConfiguration
    }
    static isDataPanelOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof DataPanelOptions
    }
    static isDataPanelShadowOptions(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof DataPanelShadowOptions
    }
    static isDataPanelType(value: Object | string | number | undefined): boolean {
        return value instanceof DataPanelType
    }
    static isDataResubmissionHandler(value: Object | string | number | undefined): boolean {
        return value instanceof DataResubmissionHandler
    }
    static isDatePickerDialog(value: Object | string | number | undefined): boolean {
        return value instanceof DatePickerDialog
    }
    static isDatePickerMode(value: Object | string | number | undefined): boolean {
        return value instanceof DatePickerMode
    }
    static isDatePickerOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof DatePickerOptions
    }
    static isDateRange(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof DateRange
    }
    static isDecorationStyle(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof DecorationStyle
    }
    static isDecorationStyleInterface(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof DecorationStyleInterface
    }
    static isDecorationStyleResult(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof DecorationStyleResult
    }
    static isDeleteValue(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof DeleteValue
    }
    static isDialogAlignment(value: Object | string | number | undefined): boolean {
        return value instanceof DialogAlignment
    }
    static isDialogButtonDirection(value: Object | string | number | undefined): boolean {
        return value instanceof DialogButtonDirection
    }
    static isDialogButtonStyle(value: Object | string | number | undefined): boolean {
        return value instanceof DialogButtonStyle
    }
    static isDigitIndicator(value: Object | string | number | undefined): boolean {
        return value instanceof DigitIndicator
    }
    static isDirection(value: Object | string | number | undefined): boolean {
        return value instanceof Direction
    }
    static isDirectionalEdgesT(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof DirectionalEdgesT
    }
    static isDisappearSymbolEffect(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof DisappearSymbolEffect
    }
    static isDismissContentCoverAction(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof DismissContentCoverAction
    }
    static isDismissDialogAction(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof DismissDialogAction
    }
    static isDismissPopupAction(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof DismissPopupAction
    }
    static isDismissReason(value: Object | string | number | undefined): boolean {
        return value instanceof DismissReason
    }
    static isDismissSheetAction(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof DismissSheetAction
    }
    static isDistributionType(value: Object | string | number | undefined): boolean {
        return value instanceof DistributionType
    }
    static isDisturbanceFieldShape(value: Object | string | number | undefined): boolean {
        return value instanceof DisturbanceFieldShape
    }
    static isDividerMode(value: Object | string | number | undefined): boolean {
        return value instanceof DividerMode
    }
    static isDividerOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof DividerOptions
    }
    static isDividerStyle(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof DividerStyle
    }
    static isDividerStyleOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean): boolean {
        return value instanceof DividerStyleOptions
    }
    static isDotIndicator(value: Object | string | number | undefined): boolean {
        return value instanceof DotIndicator
    }
    static isDoubleAnimationParam(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean): boolean {
        return value instanceof DoubleAnimationParam
    }
    static isDpiFollowStrategy(value: Object | string | number | undefined): boolean {
        return value instanceof DpiFollowStrategy
    }
    static isDragBehavior(value: Object | string | number | undefined): boolean {
        return value instanceof DragBehavior
    }
    static isDragEvent(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof DragEvent
    }
    static isDraggingSizeChangeEffect(value: Object | string | number | undefined): boolean {
        return value instanceof DraggingSizeChangeEffect
    }
    static isDragInteractionOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean): boolean {
        return value instanceof DragInteractionOptions
    }
    static isDragItemInfo(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof DragItemInfo
    }
    static isDragPreviewMode(value: Object | string | number | undefined): boolean {
        return value instanceof DragPreviewMode
    }
    static isDragPreviewOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof DragPreviewOptions
    }
    static isDragResult(value: Object | string | number | undefined): boolean {
        return value instanceof DragResult
    }
    static isDrawableDescriptor(value: Object | string | number | undefined): boolean {
        return value instanceof DrawableDescriptor
    }
    static isDrawContext(value: Object | string | number | undefined): boolean {
        return value instanceof DrawContext
    }
    static isdrawing_BlendMode(value: Object | string | number | undefined): boolean {
        return value instanceof drawing.BlendMode
    }
    static isdrawing_BlurType(value: Object | string | number | undefined): boolean {
        return value instanceof drawing.BlurType
    }
    static isdrawing_Brush(value: Object | string | number | undefined): boolean {
        return value instanceof drawing.Brush
    }
    static isdrawing_Canvas(value: Object | string | number | undefined): boolean {
        return value instanceof drawing.Canvas
    }
    static isdrawing_CapStyle(value: Object | string | number | undefined): boolean {
        return value instanceof drawing.CapStyle
    }
    static isdrawing_ClipOp(value: Object | string | number | undefined): boolean {
        return value instanceof drawing.ClipOp
    }
    static isdrawing_ColorFilter(value: Object | string | number | undefined): boolean {
        return value instanceof drawing.ColorFilter
    }
    static isdrawing_CornerPos(value: Object | string | number | undefined): boolean {
        return value instanceof drawing.CornerPos
    }
    static isdrawing_FilterMode(value: Object | string | number | undefined): boolean {
        return value instanceof drawing.FilterMode
    }
    static isdrawing_Font(value: Object | string | number | undefined): boolean {
        return value instanceof drawing.Font
    }
    static isdrawing_FontEdging(value: Object | string | number | undefined): boolean {
        return value instanceof drawing.FontEdging
    }
    static isdrawing_FontHinting(value: Object | string | number | undefined): boolean {
        return value instanceof drawing.FontHinting
    }
    static isdrawing_FontMetrics(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean, arg9: boolean, arg10: boolean, arg11: boolean, arg12: boolean, arg13: boolean, arg14: boolean, arg15: boolean): boolean {
        return value instanceof drawing.FontMetrics
    }
    static isdrawing_FontMetricsFlags(value: Object | string | number | undefined): boolean {
        return value instanceof drawing.FontMetricsFlags
    }
    static isdrawing_ImageFilter(value: Object | string | number | undefined): boolean {
        return value instanceof drawing.ImageFilter
    }
    static isdrawing_JoinStyle(value: Object | string | number | undefined): boolean {
        return value instanceof drawing.JoinStyle
    }
    static isdrawing_Lattice(value: Object | string | number | undefined): boolean {
        return value instanceof drawing.Lattice
    }
    static isdrawing_MaskFilter(value: Object | string | number | undefined): boolean {
        return value instanceof drawing.MaskFilter
    }
    static isdrawing_Matrix(value: Object | string | number | undefined): boolean {
        return value instanceof drawing.Matrix
    }
    static isdrawing_Path(value: Object | string | number | undefined): boolean {
        return value instanceof drawing.Path
    }
    static isdrawing_PathDirection(value: Object | string | number | undefined): boolean {
        return value instanceof drawing.PathDirection
    }
    static isdrawing_PathEffect(value: Object | string | number | undefined): boolean {
        return value instanceof drawing.PathEffect
    }
    static isdrawing_PathFillType(value: Object | string | number | undefined): boolean {
        return value instanceof drawing.PathFillType
    }
    static isdrawing_PathMeasureMatrixFlags(value: Object | string | number | undefined): boolean {
        return value instanceof drawing.PathMeasureMatrixFlags
    }
    static isdrawing_PathOp(value: Object | string | number | undefined): boolean {
        return value instanceof drawing.PathOp
    }
    static isdrawing_Pen(value: Object | string | number | undefined): boolean {
        return value instanceof drawing.Pen
    }
    static isdrawing_PointMode(value: Object | string | number | undefined): boolean {
        return value instanceof drawing.PointMode
    }
    static isdrawing_RectType(value: Object | string | number | undefined): boolean {
        return value instanceof drawing.RectType
    }
    static isdrawing_Region(value: Object | string | number | undefined): boolean {
        return value instanceof drawing.Region
    }
    static isdrawing_RegionOp(value: Object | string | number | undefined): boolean {
        return value instanceof drawing.RegionOp
    }
    static isdrawing_RoundRect(value: Object | string | number | undefined): boolean {
        return value instanceof drawing.RoundRect
    }
    static isdrawing_SamplingOptions(value: Object | string | number | undefined): boolean {
        return value instanceof drawing.SamplingOptions
    }
    static isdrawing_ScaleToFit(value: Object | string | number | undefined): boolean {
        return value instanceof drawing.ScaleToFit
    }
    static isdrawing_ShaderEffect(value: Object | string | number | undefined): boolean {
        return value instanceof drawing.ShaderEffect
    }
    static isdrawing_ShadowFlag(value: Object | string | number | undefined): boolean {
        return value instanceof drawing.ShadowFlag
    }
    static isdrawing_ShadowLayer(value: Object | string | number | undefined): boolean {
        return value instanceof drawing.ShadowLayer
    }
    static isdrawing_SrcRectConstraint(value: Object | string | number | undefined): boolean {
        return value instanceof drawing.SrcRectConstraint
    }
    static isdrawing_TextBlob(value: Object | string | number | undefined): boolean {
        return value instanceof drawing.TextBlob
    }
    static isdrawing_TextBlobRunBuffer(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof drawing.TextBlobRunBuffer
    }
    static isdrawing_TextEncoding(value: Object | string | number | undefined): boolean {
        return value instanceof drawing.TextEncoding
    }
    static isdrawing_TileMode(value: Object | string | number | undefined): boolean {
        return value instanceof drawing.TileMode
    }
    static isdrawing_Typeface(value: Object | string | number | undefined): boolean {
        return value instanceof drawing.Typeface
    }
    static isDrawingRenderingContext(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof DrawingRenderingContext
    }
    static isDrawModifier(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof DrawModifier
    }
    static isDropOptions(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof DropOptions
    }
    static isDynamicRangeMode(value: Object | string | number | undefined): boolean {
        return value instanceof DynamicRangeMode
    }
    static isEdge(value: Object | string | number | undefined): boolean {
        return value instanceof Edge
    }
    static isEdgeColors(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof EdgeColors
    }
    static isEdgeEffect(value: Object | string | number | undefined): boolean {
        return value instanceof EdgeEffect
    }
    static isEdgeEffectOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof EdgeEffectOptions
    }
    static isEdgeOutlineStyles(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof EdgeOutlineStyles
    }
    static isEdgeOutlineWidths(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof EdgeOutlineWidths
    }
    static isEdges(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof Edges
    }
    static isEdgeStyles(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof EdgeStyles
    }
    static isEdgeWidths(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof EdgeWidths
    }
    static isEditableTextChangeValue(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof EditableTextChangeValue
    }
    static isEditMenuOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof EditMenuOptions
    }
    static isEffectDirection(value: Object | string | number | undefined): boolean {
        return value instanceof EffectDirection
    }
    static isEffectEdge(value: Object | string | number | undefined): boolean {
        return value instanceof EffectEdge
    }
    static isEffectFillStyle(value: Object | string | number | undefined): boolean {
        return value instanceof EffectFillStyle
    }
    static isEffectScope(value: Object | string | number | undefined): boolean {
        return value instanceof EffectScope
    }
    static isEffectType(value: Object | string | number | undefined): boolean {
        return value instanceof EffectType
    }
    static isEllipseOptions(value: Object | string | number | undefined): boolean {
        return value instanceof EllipseOptions
    }
    static isEllipseShape(value: Object | string | number | undefined): boolean {
        return value instanceof EllipseShape
    }
    static isEllipsisMode(value: Object | string | number | undefined): boolean {
        return value instanceof EllipsisMode
    }
    static isEmbeddedType(value: Object | string | number | undefined): boolean {
        return value instanceof EmbeddedType
    }
    static isEmbedOptions(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof EmbedOptions
    }
    static isEnterKeyType(value: Object | string | number | undefined): boolean {
        return value instanceof EnterKeyType
    }
    static isErrorEvent(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean): boolean {
        return value instanceof ErrorEvent
    }
    static isErrorInformation(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof ErrorInformation
    }
    static isEvent(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof Event
    }
    static isEventResult(value: Object | string | number | undefined): boolean {
        return value instanceof EventResult
    }
    static isEventTarget(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof EventTarget
    }
    static isEventTargetInfo(value: Object | string | number | undefined): boolean {
        return value instanceof EventTargetInfo
    }
    static isExpectedFrameRateRange(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof ExpectedFrameRateRange
    }
    static isExtendableComponent(value: Object | string | number | undefined): boolean {
        return value instanceof ExtendableComponent
    }
    static isFadingEdgeOptions(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof FadingEdgeOptions
    }
    static isFileSelectorMode(value: Object | string | number | undefined): boolean {
        return value instanceof FileSelectorMode
    }
    static isFileSelectorParam(value: Object | string | number | undefined): boolean {
        return value instanceof FileSelectorParam
    }
    static isFileSelectorResult(value: Object | string | number | undefined): boolean {
        return value instanceof FileSelectorResult
    }
    static isFillMode(value: Object | string | number | undefined): boolean {
        return value instanceof FillMode
    }
    static isFingerInfo(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean): boolean {
        return value instanceof FingerInfo
    }
    static isFinishCallbackType(value: Object | string | number | undefined): boolean {
        return value instanceof FinishCallbackType
    }
    static isFirstMeaningfulPaint(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof FirstMeaningfulPaint
    }
    static isFlexAlign(value: Object | string | number | undefined): boolean {
        return value instanceof FlexAlign
    }
    static isFlexDirection(value: Object | string | number | undefined): boolean {
        return value instanceof FlexDirection
    }
    static isFlexOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean): boolean {
        return value instanceof FlexOptions
    }
    static isFlexSpaceOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof FlexSpaceOptions
    }
    static isFlexWrap(value: Object | string | number | undefined): boolean {
        return value instanceof FlexWrap
    }
    static isFocusAxisEvent(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof FocusAxisEvent
    }
    static isFocusBoxStyle(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof FocusBoxStyle
    }
    static isFocusDrawLevel(value: Object | string | number | undefined): boolean {
        return value instanceof FocusDrawLevel
    }
    static isFocusMovement(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean): boolean {
        return value instanceof FocusMovement
    }
    static isFocusPriority(value: Object | string | number | undefined): boolean {
        return value instanceof FocusPriority
    }
    static isFolderStackOptions(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof FolderStackOptions
    }
    static isFoldStatus(value: Object | string | number | undefined): boolean {
        return value instanceof FoldStatus
    }
    static isFont(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof Font
    }
    static isfont_UIFontAdjustInfo(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof font.UIFontAdjustInfo
    }
    static isfont_UIFontAliasInfo(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof font.UIFontAliasInfo
    }
    static isfont_UIFontConfig(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof font.UIFontConfig
    }
    static isfont_UIFontFallbackGroupInfo(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof font.UIFontFallbackGroupInfo
    }
    static isfont_UIFontFallbackInfo(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof font.UIFontFallbackInfo
    }
    static isfont_UIFontGenericInfo(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof font.UIFontGenericInfo
    }
    static isFontInfo(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean, arg9: boolean): boolean {
        return value instanceof FontInfo
    }
    static isFontOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof FontOptions
    }
    static isFontSettingOptions(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof FontSettingOptions
    }
    static isFontStyle(value: Object | string | number | undefined): boolean {
        return value instanceof FontStyle
    }
    static isFontWeight(value: Object | string | number | undefined): boolean {
        return value instanceof FontWeight
    }
    static isForegroundBlurStyleOptions(value: Object | string | number | undefined): boolean {
        return value instanceof ForegroundBlurStyleOptions
    }
    static isForegroundEffectOptions(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof ForegroundEffectOptions
    }
    static isFormCallbackInfo(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof FormCallbackInfo
    }
    static isFormDimension(value: Object | string | number | undefined): boolean {
        return value instanceof FormDimension
    }
    static isFormInfo(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean, arg9: boolean): boolean {
        return value instanceof FormInfo
    }
    static isFormLinkOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean): boolean {
        return value instanceof FormLinkOptions
    }
    static isFormRenderingMode(value: Object | string | number | undefined): boolean {
        return value instanceof FormRenderingMode
    }
    static isFormShape(value: Object | string | number | undefined): boolean {
        return value instanceof FormShape
    }
    static isFormSize(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof FormSize
    }
    static isFrame(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof Frame
    }
    static isFrameNode(value: Object | string | number | undefined): boolean {
        return value instanceof FrameNode
    }
    static isFrictionMotion(value: Object | string | number | undefined): boolean {
        return value instanceof FrictionMotion
    }
    static isFullScreenEnterEvent(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof FullScreenEnterEvent
    }
    static isFullScreenExitHandler(value: Object | string | number | undefined): boolean {
        return value instanceof FullScreenExitHandler
    }
    static isFullscreenInfo(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof FullscreenInfo
    }
    static isFunctionKey(value: Object | string | number | undefined): boolean {
        return value instanceof FunctionKey
    }
    static isGaugeConfiguration(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof GaugeConfiguration
    }
    static isGaugeIndicatorOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof GaugeIndicatorOptions
    }
    static isGaugeOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof GaugeOptions
    }
    static isGaugeShadowOptions(value: Object | string | number | undefined): boolean {
        return value instanceof GaugeShadowOptions
    }
    static isGeometryInfo(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof GeometryInfo
    }
    static isGeometryTransitionOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof GeometryTransitionOptions
    }
    static isGesture(value: Object | string | number | undefined): boolean {
        return value instanceof Gesture
    }
    static isGestureControl_GestureType(value: Object | string | number | undefined): boolean {
        return value instanceof GestureControl.GestureType
    }
    static isGestureEvent(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean, arg9: boolean, arg10: boolean, arg11: boolean): boolean {
        return value instanceof GestureEvent
    }
    static isGestureGroupInterface(value: Object | string | number | undefined): boolean {
        return value instanceof GestureGroupInterface
    }
    static isGestureInfo(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof GestureInfo
    }
    static isGestureJudgeResult(value: Object | string | number | undefined): boolean {
        return value instanceof GestureJudgeResult
    }
    static isGestureMask(value: Object | string | number | undefined): boolean {
        return value instanceof GestureMask
    }
    static isGestureMode(value: Object | string | number | undefined): boolean {
        return value instanceof GestureMode
    }
    static isGestureModifier(value: Object | string | number | undefined): boolean {
        return value instanceof GestureModifier
    }
    static isGesturePriority(value: Object | string | number | undefined): boolean {
        return value instanceof GesturePriority
    }
    static isGestureRecognizer(value: Object | string | number | undefined): boolean {
        return value instanceof GestureRecognizer
    }
    static isGestureRecognizerState(value: Object | string | number | undefined): boolean {
        return value instanceof GestureRecognizerState
    }
    static isGestureStyle(value: Object | string | number | undefined): boolean {
        return value instanceof GestureStyle
    }
    static isGestureStyleInterface(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof GestureStyleInterface
    }
    static isGradientDirection(value: Object | string | number | undefined): boolean {
        return value instanceof GradientDirection
    }
    static isGridColColumnOption(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean): boolean {
        return value instanceof GridColColumnOption
    }
    static isGridColOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof GridColOptions
    }
    static isGridDirection(value: Object | string | number | undefined): boolean {
        return value instanceof GridDirection
    }
    static isGridItemAlignment(value: Object | string | number | undefined): boolean {
        return value instanceof GridItemAlignment
    }
    static isGridItemOptions(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof GridItemOptions
    }
    static isGridItemStyle(value: Object | string | number | undefined): boolean {
        return value instanceof GridItemStyle
    }
    static isGridLayoutOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof GridLayoutOptions
    }
    static isGridRowColumnOption(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean): boolean {
        return value instanceof GridRowColumnOption
    }
    static isGridRowDirection(value: Object | string | number | undefined): boolean {
        return value instanceof GridRowDirection
    }
    static isGridRowOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof GridRowOptions
    }
    static isGridRowSizeOption(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean): boolean {
        return value instanceof GridRowSizeOption
    }
    static isGuideLinePosition(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof GuideLinePosition
    }
    static isGuideLineStyle(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof GuideLineStyle
    }
    static isGutterOption(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof GutterOption
    }
    static isHapticFeedbackMode(value: Object | string | number | undefined): boolean {
        return value instanceof HapticFeedbackMode
    }
    static isHeader(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof Header
    }
    static isHeightBreakpoint(value: Object | string | number | undefined): boolean {
        return value instanceof HeightBreakpoint
    }
    static isHierarchicalSymbolEffect(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof HierarchicalSymbolEffect
    }
    static isHistoricalPoint(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof HistoricalPoint
    }
    static isHitTestMode(value: Object | string | number | undefined): boolean {
        return value instanceof HitTestMode
    }
    static isHitTestType(value: Object | string | number | undefined): boolean {
        return value instanceof HitTestType
    }
    static isHorizontalAlign(value: Object | string | number | undefined): boolean {
        return value instanceof HorizontalAlign
    }
    static isHoverEffect(value: Object | string | number | undefined): boolean {
        return value instanceof HoverEffect
    }
    static isHoverEvent(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean): boolean {
        return value instanceof HoverEvent
    }
    static isHoverEventParam(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof HoverEventParam
    }
    static isHoverModeAreaType(value: Object | string | number | undefined): boolean {
        return value instanceof HoverModeAreaType
    }
    static isHttpAuthHandler(value: Object | string | number | undefined): boolean {
        return value instanceof HttpAuthHandler
    }
    static isIconOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof IconOptions
    }
    static isIlluminatedType(value: Object | string | number | undefined): boolean {
        return value instanceof IlluminatedType
    }
    static isimage_PixelMap(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof image.PixelMap
    }
    static isimage_ResolutionQuality(value: Object | string | number | undefined): boolean {
        return value instanceof image.ResolutionQuality
    }
    static isImageAIOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof ImageAIOptions
    }
    static isImageAnalyzerConfig(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof ImageAnalyzerConfig
    }
    static isImageAnalyzerController(value: Object | string | number | undefined): boolean {
        return value instanceof ImageAnalyzerController
    }
    static isImageAnalyzerType(value: Object | string | number | undefined): boolean {
        return value instanceof ImageAnalyzerType
    }
    static isImageAttachment(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean): boolean {
        return value instanceof ImageAttachment
    }
    static isImageAttachmentInterface(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean): boolean {
        return value instanceof ImageAttachmentInterface
    }
    static isImageAttachmentLayoutStyle(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof ImageAttachmentLayoutStyle
    }
    static isImageBitmap(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof ImageBitmap
    }
    static isImageCompleteEvent(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean): boolean {
        return value instanceof ImageCompleteEvent
    }
    static isImageContent(value: Object | string | number | undefined): boolean {
        return value instanceof ImageContent
    }
    static isImageData(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof ImageData
    }
    static isImageError(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof ImageError
    }
    static isImageFit(value: Object | string | number | undefined): boolean {
        return value instanceof ImageFit
    }
    static isImageFrameInfo(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean): boolean {
        return value instanceof ImageFrameInfo
    }
    static isImageInterpolation(value: Object | string | number | undefined): boolean {
        return value instanceof ImageInterpolation
    }
    static isImageLoadResult(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean): boolean {
        return value instanceof ImageLoadResult
    }
    static isImageRenderMode(value: Object | string | number | undefined): boolean {
        return value instanceof ImageRenderMode
    }
    static isImageRepeat(value: Object | string | number | undefined): boolean {
        return value instanceof ImageRepeat
    }
    static isImageRotateOrientation(value: Object | string | number | undefined): boolean {
        return value instanceof ImageRotateOrientation
    }
    static isImageSize(value: Object | string | number | undefined): boolean {
        return value instanceof ImageSize
    }
    static isImageSourceSize(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof ImageSourceSize
    }
    static isImageSpanAlignment(value: Object | string | number | undefined): boolean {
        return value instanceof ImageSpanAlignment
    }
    static isImmersiveMode(value: Object | string | number | undefined): boolean {
        return value instanceof ImmersiveMode
    }
    static isIndexerAlign(value: Object | string | number | undefined): boolean {
        return value instanceof IndexerAlign
    }
    static isIndicatorComponentController(value: Object | string | number | undefined): boolean {
        return value instanceof IndicatorComponentController
    }
    static isInputCounterOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof InputCounterOptions
    }
    static isInputType(value: Object | string | number | undefined): boolean {
        return value instanceof InputType
    }
    static isInsertValue(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof InsertValue
    }
    static isIntelligentTrackingPreventionDetails(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof IntelligentTrackingPreventionDetails
    }
    static isIntentionCode(value: Object | string | number | undefined): boolean {
        return value instanceof IntentionCode
    }
    static isInteractionHand(value: Object | string | number | undefined): boolean {
        return value instanceof InteractionHand
    }
    static isintl_DateTimeOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean, arg9: boolean, arg10: boolean, arg11: boolean, arg12: boolean, arg13: boolean, arg14: boolean, arg15: boolean, arg16: boolean, arg17: boolean, arg18: boolean): boolean {
        return value instanceof intl.DateTimeOptions
    }
    static isInvertOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof InvertOptions
    }
    static isItemAlign(value: Object | string | number | undefined): boolean {
        return value instanceof ItemAlign
    }
    static isItemDragInfo(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof ItemDragInfo
    }
    static isItemState(value: Object | string | number | undefined): boolean {
        return value instanceof ItemState
    }
    static isJavaScriptProxy(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean): boolean {
        return value instanceof JavaScriptProxy
    }
    static isJsGeolocation(value: Object | string | number | undefined): boolean {
        return value instanceof JsGeolocation
    }
    static isJsResult(value: Object | string | number | undefined): boolean {
        return value instanceof JsResult
    }
    static isKeyboardAppearance(value: Object | string | number | undefined): boolean {
        return value instanceof KeyboardAppearance
    }
    static isKeyboardAvoidMode(value: Object | string | number | undefined): boolean {
        return value instanceof KeyboardAvoidMode
    }
    static isKeyboardOptions(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof KeyboardOptions
    }
    static isKeyEvent(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean, arg9: boolean, arg10: boolean): boolean {
        return value instanceof KeyEvent
    }
    static isKeyProcessingMode(value: Object | string | number | undefined): boolean {
        return value instanceof KeyProcessingMode
    }
    static isKeySource(value: Object | string | number | undefined): boolean {
        return value instanceof KeySource
    }
    static isKeyType(value: Object | string | number | undefined): boolean {
        return value instanceof KeyType
    }
    static isLargestContentfulPaint(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean): boolean {
        return value instanceof LargestContentfulPaint
    }
    static isLaunchMode(value: Object | string | number | undefined): boolean {
        return value instanceof LaunchMode
    }
    static isLayoutable(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof Layoutable
    }
    static isLayoutCallback(value: Object | string | number | undefined): boolean {
        return value instanceof LayoutCallback
    }
    static isLayoutChild(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof LayoutChild
    }
    static isLayoutConstraint(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof LayoutConstraint
    }
    static isLayoutDirection(value: Object | string | number | undefined): boolean {
        return value instanceof LayoutDirection
    }
    static isLayoutManager(value: Object | string | number | undefined): boolean {
        return value instanceof LayoutManager
    }
    static isLayoutMode(value: Object | string | number | undefined): boolean {
        return value instanceof LayoutMode
    }
    static isLayoutPolicy(value: Object | string | number | undefined): boolean {
        return value instanceof LayoutPolicy
    }
    static isLayoutSafeAreaEdge(value: Object | string | number | undefined): boolean {
        return value instanceof LayoutSafeAreaEdge
    }
    static isLayoutSafeAreaType(value: Object | string | number | undefined): boolean {
        return value instanceof LayoutSafeAreaType
    }
    static isLayoutStyle(value: Object | string | number | undefined): boolean {
        return value instanceof LayoutStyle
    }
    static isLeadingMarginPlaceholder(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof LeadingMarginPlaceholder
    }
    static isLengthConstrain(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof LengthConstrain
    }
    static isLengthMetrics(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof LengthMetrics
    }
    static isLengthMetricsUnit(value: Object | string | number | undefined): boolean {
        return value instanceof LengthMetricsUnit
    }
    static isLengthUnit(value: Object | string | number | undefined): boolean {
        return value instanceof LengthUnit
    }
    static isLetterSpacingStyle(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof LetterSpacingStyle
    }
    static isLevelMode(value: Object | string | number | undefined): boolean {
        return value instanceof LevelMode
    }
    static isLevelOrder(value: Object | string | number | undefined): boolean {
        return value instanceof LevelOrder
    }
    static isLifeCycle(value: Object | string | number | undefined): boolean {
        return value instanceof LifeCycle
    }
    static isLightSource(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean): boolean {
        return value instanceof LightSource
    }
    static isLinearGradient(value: Object | string | number | undefined): boolean {
        return value instanceof LinearGradient
    }
    static isLinearGradientBlurOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof LinearGradientBlurOptions
    }
    static isLinearGradientOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof LinearGradientOptions
    }
    static isLinearIndicatorController(value: Object | string | number | undefined): boolean {
        return value instanceof LinearIndicatorController
    }
    static isLinearIndicatorStartOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof LinearIndicatorStartOptions
    }
    static isLinearIndicatorStyle(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean): boolean {
        return value instanceof LinearIndicatorStyle
    }
    static isLinearStyleOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof LinearStyleOptions
    }
    static isLineBreakStrategy(value: Object | string | number | undefined): boolean {
        return value instanceof LineBreakStrategy
    }
    static isLineCapStyle(value: Object | string | number | undefined): boolean {
        return value instanceof LineCapStyle
    }
    static isLineHeightStyle(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof LineHeightStyle
    }
    static isLineJoinStyle(value: Object | string | number | undefined): boolean {
        return value instanceof LineJoinStyle
    }
    static isLineOptions(value: Object | string | number | undefined): boolean {
        return value instanceof LineOptions
    }
    static isListDividerOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof ListDividerOptions
    }
    static isListItemAlign(value: Object | string | number | undefined): boolean {
        return value instanceof ListItemAlign
    }
    static isListItemGroupArea(value: Object | string | number | undefined): boolean {
        return value instanceof ListItemGroupArea
    }
    static isListItemGroupOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean): boolean {
        return value instanceof ListItemGroupOptions
    }
    static isListItemGroupStyle(value: Object | string | number | undefined): boolean {
        return value instanceof ListItemGroupStyle
    }
    static isListItemOptions(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof ListItemOptions
    }
    static isListItemStyle(value: Object | string | number | undefined): boolean {
        return value instanceof ListItemStyle
    }
    static isListOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof ListOptions
    }
    static isListScroller(value: Object | string | number | undefined): boolean {
        return value instanceof ListScroller
    }
    static isLoadCommittedDetails(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean): boolean {
        return value instanceof LoadCommittedDetails
    }
    static isLoadingProgressConfiguration(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof LoadingProgressConfiguration
    }
    static isLoadingProgressStyle(value: Object | string | number | undefined): boolean {
        return value instanceof LoadingProgressStyle
    }
    static isLocalizedAlignRuleOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean): boolean {
        return value instanceof LocalizedAlignRuleOptions
    }
    static isLocalizedBarrierDirection(value: Object | string | number | undefined): boolean {
        return value instanceof LocalizedBarrierDirection
    }
    static isLocalizedBorderRadiuses(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof LocalizedBorderRadiuses
    }
    static isLocalizedEdgeColors(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof LocalizedEdgeColors
    }
    static isLocalizedEdges(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof LocalizedEdges
    }
    static isLocalizedEdgeWidths(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof LocalizedEdgeWidths
    }
    static isLocalizedHorizontalAlignParam(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof LocalizedHorizontalAlignParam
    }
    static isLocalizedPadding(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof LocalizedPadding
    }
    static isLocalizedPosition(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof LocalizedPosition
    }
    static isLocalizedVerticalAlignParam(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof LocalizedVerticalAlignParam
    }
    static isLocationButtonOnClickResult(value: Object | string | number | undefined): boolean {
        return value instanceof LocationButtonOnClickResult
    }
    static isLocationDescription(value: Object | string | number | undefined): boolean {
        return value instanceof LocationDescription
    }
    static isLocationIconStyle(value: Object | string | number | undefined): boolean {
        return value instanceof LocationIconStyle
    }
    static isLongPressGestureEvent(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof LongPressGestureEvent
    }
    static isLongPressGestureHandlerOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof LongPressGestureHandlerOptions
    }
    static isLongPressGestureInterface(value: Object | string | number | undefined): boolean {
        return value instanceof LongPressGestureInterface
    }
    static isLongPressGestureInterface_Invoke_Literal(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof LongPressGestureInterface_Invoke_Literal
    }
    static isLongPressRecognizer(value: Object | string | number | undefined): boolean {
        return value instanceof LongPressRecognizer
    }
    static isMarkStyle(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof MarkStyle
    }
    static isMarqueeOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean): boolean {
        return value instanceof MarqueeOptions
    }
    static isMarqueeStartPolicy(value: Object | string | number | undefined): boolean {
        return value instanceof MarqueeStartPolicy
    }
    static isMarqueeState(value: Object | string | number | undefined): boolean {
        return value instanceof MarqueeState
    }
    static isMarqueeUpdateStrategy(value: Object | string | number | undefined): boolean {
        return value instanceof MarqueeUpdateStrategy
    }
    static isMatrix2D(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean): boolean {
        return value instanceof Matrix2D
    }
    static ismatrix4_Matrix4Transit(value: Object | string | number | undefined): boolean {
        return value instanceof matrix4.Matrix4Transit
    }
    static ismatrix4_PolyToPolyOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean): boolean {
        return value instanceof matrix4.PolyToPolyOptions
    }
    static isMeasurable(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof Measurable
    }
    static isMeasureOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean, arg9: boolean, arg10: boolean, arg11: boolean, arg12: boolean, arg13: boolean, arg14: boolean): boolean {
        return value instanceof MeasureOptions
    }
    static isMeasureResult(value: Object | string | number | undefined): boolean {
        return value instanceof MeasureResult
    }
    static isMenuAlignType(value: Object | string | number | undefined): boolean {
        return value instanceof MenuAlignType
    }
    static isMenuElement(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean): boolean {
        return value instanceof MenuElement
    }
    static isMenuItemConfiguration(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean): boolean {
        return value instanceof MenuItemConfiguration
    }
    static isMenuItemGroupOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof MenuItemGroupOptions
    }
    static isMenuItemOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean): boolean {
        return value instanceof MenuItemOptions
    }
    static isMenuOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof MenuOptions
    }
    static isMenuOutlineOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof MenuOutlineOptions
    }
    static isMenuPolicy(value: Object | string | number | undefined): boolean {
        return value instanceof MenuPolicy
    }
    static isMenuPreviewMode(value: Object | string | number | undefined): boolean {
        return value instanceof MenuPreviewMode
    }
    static isMenuType(value: Object | string | number | undefined): boolean {
        return value instanceof MenuType
    }
    static isMessageEvents(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof MessageEvents
    }
    static isMessageLevel(value: Object | string | number | undefined): boolean {
        return value instanceof MessageLevel
    }
    static isMixedMode(value: Object | string | number | undefined): boolean {
        return value instanceof MixedMode
    }
    static isModalTransition(value: Object | string | number | undefined): boolean {
        return value instanceof ModalTransition
    }
    static isModifierKey(value: Object | string | number | undefined): boolean {
        return value instanceof ModifierKey
    }
    static isMoreButtonOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof MoreButtonOptions
    }
    static isMotionBlurAnchor(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof MotionBlurAnchor
    }
    static isMotionBlurOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof MotionBlurOptions
    }
    static isMotionPathOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof MotionPathOptions
    }
    static isMouseAction(value: Object | string | number | undefined): boolean {
        return value instanceof MouseAction
    }
    static isMouseButton(value: Object | string | number | undefined): boolean {
        return value instanceof MouseButton
    }
    static isMouseEvent(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean, arg9: boolean, arg10: boolean, arg11: boolean): boolean {
        return value instanceof MouseEvent
    }
    static isMutableStyledString(value: Object | string | number | undefined): boolean {
        return value instanceof MutableStyledString
    }
    static isNativeEmbedDataInfo(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof NativeEmbedDataInfo
    }
    static isNativeEmbedInfo(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean): boolean {
        return value instanceof NativeEmbedInfo
    }
    static isNativeEmbedStatus(value: Object | string | number | undefined): boolean {
        return value instanceof NativeEmbedStatus
    }
    static isNativeEmbedTouchInfo(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof NativeEmbedTouchInfo
    }
    static isNativeEmbedVisibilityInfo(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof NativeEmbedVisibilityInfo
    }
    static isNativeMediaPlayerConfig(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof NativeMediaPlayerConfig
    }
    static isNativeXComponentParameters(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof NativeXComponentParameters
    }
    static isNavBarPosition(value: Object | string | number | undefined): boolean {
        return value instanceof NavBarPosition
    }
    static isNavContentInfo(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean): boolean {
        return value instanceof NavContentInfo
    }
    static isNavDestinationActiveReason(value: Object | string | number | undefined): boolean {
        return value instanceof NavDestinationActiveReason
    }
    static isNavDestinationCommonTitle(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof NavDestinationCommonTitle
    }
    static isNavDestinationContext(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof NavDestinationContext
    }
    static isNavDestinationCustomTitle(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof NavDestinationCustomTitle
    }
    static isNavDestinationMode(value: Object | string | number | undefined): boolean {
        return value instanceof NavDestinationMode
    }
    static isNavDestinationTransition(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean): boolean {
        return value instanceof NavDestinationTransition
    }
    static isNavigationAnimatedTransition(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof NavigationAnimatedTransition
    }
    static isNavigationCommonTitle(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof NavigationCommonTitle
    }
    static isNavigationCustomTitle(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof NavigationCustomTitle
    }
    static isNavigationInterception(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof NavigationInterception
    }
    static isNavigationMenuItem(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean): boolean {
        return value instanceof NavigationMenuItem
    }
    static isNavigationMenuOptions(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof NavigationMenuOptions
    }
    static isNavigationMode(value: Object | string | number | undefined): boolean {
        return value instanceof NavigationMode
    }
    static isNavigationOperation(value: Object | string | number | undefined): boolean {
        return value instanceof NavigationOperation
    }
    static isNavigationOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof NavigationOptions
    }
    static isNavigationSystemTransitionType(value: Object | string | number | undefined): boolean {
        return value instanceof NavigationSystemTransitionType
    }
    static isNavigationTitleMode(value: Object | string | number | undefined): boolean {
        return value instanceof NavigationTitleMode
    }
    static isNavigationTitleOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean, arg9: boolean): boolean {
        return value instanceof NavigationTitleOptions
    }
    static isNavigationToolbarOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean): boolean {
        return value instanceof NavigationToolbarOptions
    }
    static isNavigationTransitionProxy(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean): boolean {
        return value instanceof NavigationTransitionProxy
    }
    static isNavigationType(value: Object | string | number | undefined): boolean {
        return value instanceof NavigationType
    }
    static isNavPathInfo(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean): boolean {
        return value instanceof NavPathInfo
    }
    static isNavPathStack(value: Object | string | number | undefined): boolean {
        return value instanceof NavPathStack
    }
    static isNestedScrollInfo(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof NestedScrollInfo
    }
    static isNestedScrollMode(value: Object | string | number | undefined): boolean {
        return value instanceof NestedScrollMode
    }
    static isNestedScrollOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof NestedScrollOptions
    }
    static isNestedScrollOptionsExt(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof NestedScrollOptionsExt
    }
    static isNodeContent(value: Object | string | number | undefined): boolean {
        return value instanceof NodeContent
    }
    static isNodeController(value: Object | string | number | undefined): boolean {
        return value instanceof NodeController
    }
    static isObscuredReasons(value: Object | string | number | undefined): boolean {
        return value instanceof ObscuredReasons
    }
    static isOffscreenCanvas(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof OffscreenCanvas
    }
    static isOffscreenCanvasRenderingContext2D(value: Object | string | number | undefined): boolean {
        return value instanceof OffscreenCanvasRenderingContext2D
    }
    static isOffset(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof Offset
    }
    static isOffset_componentutils(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof Offset_componentutils
    }
    static isOffsetOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof OffsetOptions
    }
    static isOffsetResult(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof OffsetResult
    }
    static isOnAlertEvent(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof OnAlertEvent
    }
    static isOnAudioStateChangedEvent(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof OnAudioStateChangedEvent
    }
    static isOnBeforeUnloadEvent(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof OnBeforeUnloadEvent
    }
    static isOnClientAuthenticationEvent(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean): boolean {
        return value instanceof OnClientAuthenticationEvent
    }
    static isOnConfirmEvent(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof OnConfirmEvent
    }
    static isOnConsoleEvent(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof OnConsoleEvent
    }
    static isOnContextMenuShowEvent(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof OnContextMenuShowEvent
    }
    static isOnDataResubmittedEvent(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof OnDataResubmittedEvent
    }
    static isOnDownloadStartEvent(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean): boolean {
        return value instanceof OnDownloadStartEvent
    }
    static isOnErrorReceiveEvent(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof OnErrorReceiveEvent
    }
    static isOnFaviconReceivedEvent(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof OnFaviconReceivedEvent
    }
    static isOnFirstContentfulPaintEvent(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof OnFirstContentfulPaintEvent
    }
    static isOnFoldStatusChangeInfo(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof OnFoldStatusChangeInfo
    }
    static isOnGeolocationShowEvent(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof OnGeolocationShowEvent
    }
    static isOnHttpAuthRequestEvent(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof OnHttpAuthRequestEvent
    }
    static isOnHttpErrorReceiveEvent(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof OnHttpErrorReceiveEvent
    }
    static isOnInterceptRequestEvent(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof OnInterceptRequestEvent
    }
    static isOnLoadInterceptEvent(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof OnLoadInterceptEvent
    }
    static isOnOverScrollEvent(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof OnOverScrollEvent
    }
    static isOnPageBeginEvent(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof OnPageBeginEvent
    }
    static isOnPageEndEvent(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof OnPageEndEvent
    }
    static isOnPageVisibleEvent(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof OnPageVisibleEvent
    }
    static isOnPermissionRequestEvent(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof OnPermissionRequestEvent
    }
    static isOnProgressChangeEvent(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof OnProgressChangeEvent
    }
    static isOnPromptEvent(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof OnPromptEvent
    }
    static isOnRefreshAccessedHistoryEvent(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof OnRefreshAccessedHistoryEvent
    }
    static isOnRenderExitedEvent(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof OnRenderExitedEvent
    }
    static isOnResourceLoadEvent(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof OnResourceLoadEvent
    }
    static isOnScaleChangeEvent(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof OnScaleChangeEvent
    }
    static isOnScreenCaptureRequestEvent(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof OnScreenCaptureRequestEvent
    }
    static isOnScrollEvent(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof OnScrollEvent
    }
    static isOnScrollFrameBeginHandlerResult(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof OnScrollFrameBeginHandlerResult
    }
    static isOnSearchResultReceiveEvent(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof OnSearchResultReceiveEvent
    }
    static isOnShowFileSelectorEvent(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof OnShowFileSelectorEvent
    }
    static isOnSslErrorEventReceiveEvent(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof OnSslErrorEventReceiveEvent
    }
    static isOnTitleReceiveEvent(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof OnTitleReceiveEvent
    }
    static isOnTouchIconUrlReceivedEvent(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof OnTouchIconUrlReceivedEvent
    }
    static isOnWindowNewEvent(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof OnWindowNewEvent
    }
    static isOptionWidthMode(value: Object | string | number | undefined): boolean {
        return value instanceof OptionWidthMode
    }
    static isOutlineOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof OutlineOptions
    }
    static isOutlineRadiuses(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof OutlineRadiuses
    }
    static isOutlineStyle(value: Object | string | number | undefined): boolean {
        return value instanceof OutlineStyle
    }
    static isOverlayOffset(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof OverlayOffset
    }
    static isOverlayOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof OverlayOptions
    }
    static isOverScrollMode(value: Object | string | number | undefined): boolean {
        return value instanceof OverScrollMode
    }
    static isPadding(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof Padding
    }
    static isPageFlipMode(value: Object | string | number | undefined): boolean {
        return value instanceof PageFlipMode
    }
    static isPageLifeCycle(value: Object | string | number | undefined): boolean {
        return value instanceof PageLifeCycle
    }
    static isPanDirection(value: Object | string | number | undefined): boolean {
        return value instanceof PanDirection
    }
    static isPanGestureEvent(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean): boolean {
        return value instanceof PanGestureEvent
    }
    static isPanGestureHandlerOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof PanGestureHandlerOptions
    }
    static isPanGestureInterface(value: Object | string | number | undefined): boolean {
        return value instanceof PanGestureInterface
    }
    static isPanGestureInterface_Invoke_Literal(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof PanGestureInterface_Invoke_Literal
    }
    static isPanGestureOptions(value: Object | string | number | undefined): boolean {
        return value instanceof PanGestureOptions
    }
    static isPanRecognizer(value: Object | string | number | undefined): boolean {
        return value instanceof PanRecognizer
    }
    static isParagraphStyle(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean): boolean {
        return value instanceof ParagraphStyle
    }
    static isParagraphStyleInterface(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean): boolean {
        return value instanceof ParagraphStyleInterface
    }
    static isParticleEmitterShape(value: Object | string | number | undefined): boolean {
        return value instanceof ParticleEmitterShape
    }
    static isParticleType(value: Object | string | number | undefined): boolean {
        return value instanceof ParticleType
    }
    static isParticleUpdater(value: Object | string | number | undefined): boolean {
        return value instanceof ParticleUpdater
    }
    static isPasswordIcon(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof PasswordIcon
    }
    static isPasteButtonOnClickResult(value: Object | string | number | undefined): boolean {
        return value instanceof PasteButtonOnClickResult
    }
    static isPasteDescription(value: Object | string | number | undefined): boolean {
        return value instanceof PasteDescription
    }
    static isPasteEvent(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof PasteEvent
    }
    static isPasteIconStyle(value: Object | string | number | undefined): boolean {
        return value instanceof PasteIconStyle
    }
    static isPath2D(value: Object | string | number | undefined): boolean {
        return value instanceof Path2D
    }
    static isPathOptions(value: Object | string | number | undefined): boolean {
        return value instanceof PathOptions
    }
    static isPathShape(value: Object | string | number | undefined): boolean {
        return value instanceof PathShape
    }
    static isPathShapeOptions(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof PathShapeOptions
    }
    static isPatternLockChallengeResult(value: Object | string | number | undefined): boolean {
        return value instanceof PatternLockChallengeResult
    }
    static isPatternLockController(value: Object | string | number | undefined): boolean {
        return value instanceof PatternLockController
    }
    static isPerfMonitorActionType(value: Object | string | number | undefined): boolean {
        return value instanceof PerfMonitorActionType
    }
    static isPerfMonitorSourceType(value: Object | string | number | undefined): boolean {
        return value instanceof PerfMonitorSourceType
    }
    static isPermissionRequest(value: Object | string | number | undefined): boolean {
        return value instanceof PermissionRequest
    }
    static isPickerDialogButtonStyle(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean, arg9: boolean, arg10: boolean): boolean {
        return value instanceof PickerDialogButtonStyle
    }
    static isPickerTextStyle(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof PickerTextStyle
    }
    static isPinchGestureEvent(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof PinchGestureEvent
    }
    static isPinchGestureHandlerOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof PinchGestureHandlerOptions
    }
    static isPinchGestureInterface(value: Object | string | number | undefined): boolean {
        return value instanceof PinchGestureInterface
    }
    static isPinchGestureInterface_Invoke_Literal(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof PinchGestureInterface_Invoke_Literal
    }
    static isPinchRecognizer(value: Object | string | number | undefined): boolean {
        return value instanceof PinchRecognizer
    }
    static isPixelMapMock(value: Object | string | number | undefined): boolean {
        return value instanceof PixelMapMock
    }
    static isPixelRoundCalcPolicy(value: Object | string | number | undefined): boolean {
        return value instanceof PixelRoundCalcPolicy
    }
    static isPixelRoundMode(value: Object | string | number | undefined): boolean {
        return value instanceof PixelRoundMode
    }
    static isPixelRoundPolicy(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof PixelRoundPolicy
    }
    static isPixelStretchEffectOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof PixelStretchEffectOptions
    }
    static isPlaceholderStyle(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof PlaceholderStyle
    }
    static isPlacement(value: Object | string | number | undefined): boolean {
        return value instanceof Placement
    }
    static isPlaybackInfo(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof PlaybackInfo
    }
    static isPlaybackSpeed(value: Object | string | number | undefined): boolean {
        return value instanceof PlaybackSpeed
    }
    static isPlayMode(value: Object | string | number | undefined): boolean {
        return value instanceof PlayMode
    }
    static isPluginComponentOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof PluginComponentOptions
    }
    static isPluginComponentTemplate(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof PluginComponentTemplate
    }
    static isPluginErrorData(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof PluginErrorData
    }
    static ispointer_PointerStyle(value: Object | string | number | undefined): boolean {
        return value instanceof pointer.PointerStyle
    }
    static isPointLightStyle(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof PointLightStyle
    }
    static isPolygonOptions(value: Object | string | number | undefined): boolean {
        return value instanceof PolygonOptions
    }
    static isPolylineOptions(value: Object | string | number | undefined): boolean {
        return value instanceof PolylineOptions
    }
    static isPopInfo(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof PopInfo
    }
    static isPopupButton(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof PopupButton
    }
    static isPopupCommonOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean, arg9: boolean, arg10: boolean, arg11: boolean, arg12: boolean, arg13: boolean, arg14: boolean, arg15: boolean, arg16: boolean, arg17: boolean, arg18: boolean, arg19: boolean, arg20: boolean, arg21: boolean): boolean {
        return value instanceof PopupCommonOptions
    }
    static isPopupMaskType(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof PopupMaskType
    }
    static isPopupMessageOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof PopupMessageOptions
    }
    static isPopupOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean, arg9: boolean, arg10: boolean, arg11: boolean, arg12: boolean, arg13: boolean, arg14: boolean, arg15: boolean, arg16: boolean, arg17: boolean, arg18: boolean, arg19: boolean, arg20: boolean, arg21: boolean, arg22: boolean, arg23: boolean, arg24: boolean, arg25: boolean): boolean {
        return value instanceof PopupOptions
    }
    static isPopupStateChangeParam(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof PopupStateChangeParam
    }
    static isPosition(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof Position
    }
    static isPositionWithAffinity(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof PositionWithAffinity
    }
    static isPosterOptions(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof PosterOptions
    }
    static isPostMessageOptions(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof PostMessageOptions
    }
    static isPreDragStatus(value: Object | string | number | undefined): boolean {
        return value instanceof PreDragStatus
    }
    static isPreparedInfo(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof PreparedInfo
    }
    static isPreviewConfiguration(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof PreviewConfiguration
    }
    static isPreviewMenuOptions(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof PreviewMenuOptions
    }
    static isPreviewText(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof PreviewText
    }
    static isProgressConfiguration(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof ProgressConfiguration
    }
    static isProgressMask(value: Object | string | number | undefined): boolean {
        return value instanceof ProgressMask
    }
    static isProgressOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof ProgressOptions
    }
    static isProgressStatus(value: Object | string | number | undefined): boolean {
        return value instanceof ProgressStatus
    }
    static isProgressStyle(value: Object | string | number | undefined): boolean {
        return value instanceof ProgressStyle
    }
    static isProgressStyleOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof ProgressStyleOptions
    }
    static isProgressType(value: Object | string | number | undefined): boolean {
        return value instanceof ProgressType
    }
    static isPromptAction(value: Object | string | number | undefined): boolean {
        return value instanceof PromptAction
    }
    static isProtectedResourceType(value: Object | string | number | undefined): boolean {
        return value instanceof ProtectedResourceType
    }
    static isRadialGradientOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof RadialGradientOptions
    }
    static isRadioConfiguration(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof RadioConfiguration
    }
    static isRadioIndicatorType(value: Object | string | number | undefined): boolean {
        return value instanceof RadioIndicatorType
    }
    static isRadioOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof RadioOptions
    }
    static isRadioStyle(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof RadioStyle
    }
    static isRatingConfiguration(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean): boolean {
        return value instanceof RatingConfiguration
    }
    static isRatingOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof RatingOptions
    }
    static isRectangle(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof Rectangle
    }
    static isRectOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof RectOptions
    }
    static isRectResult(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof RectResult
    }
    static isRectShape(value: Object | string | number | undefined): boolean {
        return value instanceof RectShape
    }
    static isRectShapeOptions(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof RectShapeOptions
    }
    static isRefreshOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof RefreshOptions
    }
    static isRefreshStatus(value: Object | string | number | undefined): boolean {
        return value instanceof RefreshStatus
    }
    static isRelateType(value: Object | string | number | undefined): boolean {
        return value instanceof RelateType
    }
    static isRenderExitReason(value: Object | string | number | undefined): boolean {
        return value instanceof RenderExitReason
    }
    static isRenderFit(value: Object | string | number | undefined): boolean {
        return value instanceof RenderFit
    }
    static isRenderingContextSettings(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof RenderingContextSettings
    }
    static isRenderMode(value: Object | string | number | undefined): boolean {
        return value instanceof RenderMode
    }
    static isRenderNode(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean, arg9: boolean, arg10: boolean, arg11: boolean, arg12: boolean, arg13: boolean, arg14: boolean, arg15: boolean, arg16: boolean, arg17: boolean, arg18: boolean, arg19: boolean, arg20: boolean, arg21: boolean, arg22: boolean, arg23: boolean, arg24: boolean): boolean {
        return value instanceof RenderNode
    }
    static isRenderProcessNotRespondingData(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof RenderProcessNotRespondingData
    }
    static isRenderProcessNotRespondingReason(value: Object | string | number | undefined): boolean {
        return value instanceof RenderProcessNotRespondingReason
    }
    static isRepeatMode(value: Object | string | number | undefined): boolean {
        return value instanceof RepeatMode
    }
    static isReplaceSymbolEffect(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof ReplaceSymbolEffect
    }
    static isResizableOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof ResizableOptions
    }
    static isResource(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean): boolean {
        return value instanceof Resource
    }
    static isResourceImageAttachmentOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean): boolean {
        return value instanceof ResourceImageAttachmentOptions
    }
    static isResponseType(value: Object | string | number | undefined): boolean {
        return value instanceof ResponseType
    }
    static isRestrictedWorker(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof RestrictedWorker
    }
    static isReuseOptions(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof ReuseOptions
    }
    static isRichEditorBaseController(value: Object | string | number | undefined): boolean {
        return value instanceof RichEditorBaseController
    }
    static isRichEditorBuilderSpanOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof RichEditorBuilderSpanOptions
    }
    static isRichEditorChangeValue(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof RichEditorChangeValue
    }
    static isRichEditorController(value: Object | string | number | undefined): boolean {
        return value instanceof RichEditorController
    }
    static isRichEditorDeleteDirection(value: Object | string | number | undefined): boolean {
        return value instanceof RichEditorDeleteDirection
    }
    static isRichEditorDeleteValue(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof RichEditorDeleteValue
    }
    static isRichEditorGesture(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof RichEditorGesture
    }
    static isRichEditorImageSpanOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof RichEditorImageSpanOptions
    }
    static isRichEditorImageSpanResult(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean): boolean {
        return value instanceof RichEditorImageSpanResult
    }
    static isRichEditorImageSpanStyle(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof RichEditorImageSpanStyle
    }
    static isRichEditorImageSpanStyleResult(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof RichEditorImageSpanStyleResult
    }
    static isRichEditorInsertValue(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof RichEditorInsertValue
    }
    static isRichEditorLayoutStyle(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof RichEditorLayoutStyle
    }
    static isRichEditorOptions(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof RichEditorOptions
    }
    static isRichEditorParagraphResult(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof RichEditorParagraphResult
    }
    static isRichEditorParagraphStyle(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean): boolean {
        return value instanceof RichEditorParagraphStyle
    }
    static isRichEditorParagraphStyleOptions(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof RichEditorParagraphStyleOptions
    }
    static isRichEditorRange(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof RichEditorRange
    }
    static isRichEditorResponseType(value: Object | string | number | undefined): boolean {
        return value instanceof RichEditorResponseType
    }
    static isRichEditorSelection(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof RichEditorSelection
    }
    static isRichEditorSpanPosition(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof RichEditorSpanPosition
    }
    static isRichEditorSpanType(value: Object | string | number | undefined): boolean {
        return value instanceof RichEditorSpanType
    }
    static isRichEditorStyledStringController(value: Object | string | number | undefined): boolean {
        return value instanceof RichEditorStyledStringController
    }
    static isRichEditorStyledStringOptions(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof RichEditorStyledStringOptions
    }
    static isRichEditorSymbolSpanOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof RichEditorSymbolSpanOptions
    }
    static isRichEditorSymbolSpanStyle(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean): boolean {
        return value instanceof RichEditorSymbolSpanStyle
    }
    static isRichEditorTextSpanOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean): boolean {
        return value instanceof RichEditorTextSpanOptions
    }
    static isRichEditorTextSpanResult(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean): boolean {
        return value instanceof RichEditorTextSpanResult
    }
    static isRichEditorTextStyle(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean, arg9: boolean, arg10: boolean, arg11: boolean): boolean {
        return value instanceof RichEditorTextStyle
    }
    static isRichEditorTextStyleResult(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean, arg9: boolean, arg10: boolean, arg11: boolean): boolean {
        return value instanceof RichEditorTextStyleResult
    }
    static isRichEditorUpdateImageSpanStyleOptions(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof RichEditorUpdateImageSpanStyleOptions
    }
    static isRichEditorUpdateSymbolSpanStyleOptions(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof RichEditorUpdateSymbolSpanStyleOptions
    }
    static isRichEditorUpdateTextSpanStyleOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof RichEditorUpdateTextSpanStyleOptions
    }
    static isRichEditorUrlStyle(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof RichEditorUrlStyle
    }
    static isRingStyleOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof RingStyleOptions
    }
    static isRootSceneSession(value: Object | string | number | undefined): boolean {
        return value instanceof RootSceneSession
    }
    static isRotateOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean): boolean {
        return value instanceof RotateOptions
    }
    static isRotateResult(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean): boolean {
        return value instanceof RotateResult
    }
    static isRotationGesture(value: Object | string | number | undefined): boolean {
        return value instanceof RotationGesture
    }
    static isRotationGestureEvent(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof RotationGestureEvent
    }
    static isRotationGestureHandlerOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof RotationGestureHandlerOptions
    }
    static isRotationRecognizer(value: Object | string | number | undefined): boolean {
        return value instanceof RotationRecognizer
    }
    static isRoundedRectOptions(value: Object | string | number | undefined): boolean {
        return value instanceof RoundedRectOptions
    }
    static isRoundRect(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof RoundRect
    }
    static isRoundRectShapeOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof RoundRectShapeOptions
    }
    static isRouteMapConfig(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof RouteMapConfig
    }
    static isRouteType(value: Object | string | number | undefined): boolean {
        return value instanceof RouteType
    }
    static isRowOptions(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof RowOptions
    }
    static isRowOptionsV2(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof RowOptionsV2
    }
    static isRRect(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean): boolean {
        return value instanceof RRect
    }
    static isSafeAreaEdge(value: Object | string | number | undefined): boolean {
        return value instanceof SafeAreaEdge
    }
    static isSafeAreaType(value: Object | string | number | undefined): boolean {
        return value instanceof SafeAreaType
    }
    static isSaveButtonOnClickResult(value: Object | string | number | undefined): boolean {
        return value instanceof SaveButtonOnClickResult
    }
    static isSaveDescription(value: Object | string | number | undefined): boolean {
        return value instanceof SaveDescription
    }
    static isSaveIconStyle(value: Object | string | number | undefined): boolean {
        return value instanceof SaveIconStyle
    }
    static isScaleOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean): boolean {
        return value instanceof ScaleOptions
    }
    static isScaleResult(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean): boolean {
        return value instanceof ScaleResult
    }
    static isScaleSymbolEffect(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof ScaleSymbolEffect
    }
    static isScene(value: Object | string | number | undefined): boolean {
        return value instanceof Scene
    }
    static isScreenCaptureConfig(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof ScreenCaptureConfig
    }
    static isScreenCaptureHandler(value: Object | string | number | undefined): boolean {
        return value instanceof ScreenCaptureHandler
    }
    static isScriptItem(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof ScriptItem
    }
    static isScrollableBarModeOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof ScrollableBarModeOptions
    }
    static isScrollableTargetInfo(value: Object | string | number | undefined): boolean {
        return value instanceof ScrollableTargetInfo
    }
    static isScrollAlign(value: Object | string | number | undefined): boolean {
        return value instanceof ScrollAlign
    }
    static isScrollAnimationOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof ScrollAnimationOptions
    }
    static isScrollBarDirection(value: Object | string | number | undefined): boolean {
        return value instanceof ScrollBarDirection
    }
    static isScrollBarOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof ScrollBarOptions
    }
    static isScrollDirection(value: Object | string | number | undefined): boolean {
        return value instanceof ScrollDirection
    }
    static isScrollEdgeOptions(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof ScrollEdgeOptions
    }
    static isScroller(value: Object | string | number | undefined): boolean {
        return value instanceof Scroller
    }
    static isScrollMotion(value: Object | string | number | undefined): boolean {
        return value instanceof ScrollMotion
    }
    static isScrollOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof ScrollOptions
    }
    static isScrollPageOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof ScrollPageOptions
    }
    static isScrollResult(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof ScrollResult
    }
    static isScrollSizeMode(value: Object | string | number | undefined): boolean {
        return value instanceof ScrollSizeMode
    }
    static isScrollSnapAlign(value: Object | string | number | undefined): boolean {
        return value instanceof ScrollSnapAlign
    }
    static isScrollSnapOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof ScrollSnapOptions
    }
    static isScrollSource(value: Object | string | number | undefined): boolean {
        return value instanceof ScrollSource
    }
    static isScrollState(value: Object | string | number | undefined): boolean {
        return value instanceof ScrollState
    }
    static isScrollToIndexOptions(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof ScrollToIndexOptions
    }
    static isSearchButtonOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof SearchButtonOptions
    }
    static isSearchController(value: Object | string | number | undefined): boolean {
        return value instanceof SearchController
    }
    static isSearchOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof SearchOptions
    }
    static isSearchType(value: Object | string | number | undefined): boolean {
        return value instanceof SearchType
    }
    static isSectionOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean): boolean {
        return value instanceof SectionOptions
    }
    static isSecurityComponentLayoutDirection(value: Object | string | number | undefined): boolean {
        return value instanceof SecurityComponentLayoutDirection
    }
    static isSeekMode(value: Object | string | number | undefined): boolean {
        return value instanceof SeekMode
    }
    static isSelectedMode(value: Object | string | number | undefined): boolean {
        return value instanceof SelectedMode
    }
    static isSelectionMenuOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean): boolean {
        return value instanceof SelectionMenuOptions
    }
    static isSelectionMenuOptionsExt(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof SelectionMenuOptionsExt
    }
    static isSelectionOptions(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof SelectionOptions
    }
    static isSelectOption(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof SelectOption
    }
    static isSelectStatus(value: Object | string | number | undefined): boolean {
        return value instanceof SelectStatus
    }
    static isShadowOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean): boolean {
        return value instanceof ShadowOptions
    }
    static isShadowStyle(value: Object | string | number | undefined): boolean {
        return value instanceof ShadowStyle
    }
    static isShadowType(value: Object | string | number | undefined): boolean {
        return value instanceof ShadowType
    }
    static isShapeClip(value: Object | string | number | undefined): boolean {
        return value instanceof ShapeClip
    }
    static isShapeMask(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof ShapeMask
    }
    static isShapeSize(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof ShapeSize
    }
    static isSharedTransitionEffectType(value: Object | string | number | undefined): boolean {
        return value instanceof SharedTransitionEffectType
    }
    static issharedTransitionOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean): boolean {
        return value instanceof sharedTransitionOptions
    }
    static isSheetDismiss(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof SheetDismiss
    }
    static isSheetKeyboardAvoidMode(value: Object | string | number | undefined): boolean {
        return value instanceof SheetKeyboardAvoidMode
    }
    static isSheetMode(value: Object | string | number | undefined): boolean {
        return value instanceof SheetMode
    }
    static isSheetOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean, arg9: boolean, arg10: boolean, arg11: boolean, arg12: boolean, arg13: boolean, arg14: boolean, arg15: boolean, arg16: boolean, arg17: boolean, arg18: boolean, arg19: boolean, arg20: boolean, arg21: boolean, arg22: boolean, arg23: boolean, arg24: boolean, arg25: boolean, arg26: boolean, arg27: boolean, arg28: boolean, arg29: boolean, arg30: boolean, arg31: boolean, arg32: boolean, arg33: boolean): boolean {
        return value instanceof SheetOptions
    }
    static isSheetSize(value: Object | string | number | undefined): boolean {
        return value instanceof SheetSize
    }
    static isSheetTitleOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof SheetTitleOptions
    }
    static isSheetType(value: Object | string | number | undefined): boolean {
        return value instanceof SheetType
    }
    static isSideBarContainerType(value: Object | string | number | undefined): boolean {
        return value instanceof SideBarContainerType
    }
    static isSideBarPosition(value: Object | string | number | undefined): boolean {
        return value instanceof SideBarPosition
    }
    static isSize(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof Size
    }
    static isSizeOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof SizeOptions
    }
    static isSizeResult(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof SizeResult
    }
    static isSlideEffect(value: Object | string | number | undefined): boolean {
        return value instanceof SlideEffect
    }
    static isSlideRange(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof SlideRange
    }
    static isSliderBlockStyle(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof SliderBlockStyle
    }
    static isSliderBlockType(value: Object | string | number | undefined): boolean {
        return value instanceof SliderBlockType
    }
    static isSliderChangeMode(value: Object | string | number | undefined): boolean {
        return value instanceof SliderChangeMode
    }
    static isSliderConfiguration(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean): boolean {
        return value instanceof SliderConfiguration
    }
    static isSliderInteraction(value: Object | string | number | undefined): boolean {
        return value instanceof SliderInteraction
    }
    static isSliderOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean): boolean {
        return value instanceof SliderOptions
    }
    static isSliderStyle(value: Object | string | number | undefined): boolean {
        return value instanceof SliderStyle
    }
    static isSnapshotOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof SnapshotOptions
    }
    static isSourceTool(value: Object | string | number | undefined): boolean {
        return value instanceof SourceTool
    }
    static isSourceType(value: Object | string | number | undefined): boolean {
        return value instanceof SourceType
    }
    static isSpanStyle(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof SpanStyle
    }
    static isSpringBackAction(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof SpringBackAction
    }
    static isSpringMotion(value: Object | string | number | undefined): boolean {
        return value instanceof SpringMotion
    }
    static isSpringProp(value: Object | string | number | undefined): boolean {
        return value instanceof SpringProp
    }
    static isSslError(value: Object | string | number | undefined): boolean {
        return value instanceof SslError
    }
    static isSslErrorEvent(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean): boolean {
        return value instanceof SslErrorEvent
    }
    static isSslErrorHandler(value: Object | string | number | undefined): boolean {
        return value instanceof SslErrorHandler
    }
    static isStackOptions(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof StackOptions
    }
    static isStarStyleOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof StarStyleOptions
    }
    static isStateStyles(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean): boolean {
        return value instanceof StateStyles
    }
    static isStepperOptions(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof StepperOptions
    }
    static isStickyStyle(value: Object | string | number | undefined): boolean {
        return value instanceof StickyStyle
    }
    static isStyledString(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof StyledString
    }
    static isStyledStringChangedListener(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof StyledStringChangedListener
    }
    static isStyledStringChangeValue(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof StyledStringChangeValue
    }
    static isStyledStringController(value: Object | string | number | undefined): boolean {
        return value instanceof StyledStringController
    }
    static isStyledStringKey(value: Object | string | number | undefined): boolean {
        return value instanceof StyledStringKey
    }
    static isStyleOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof StyleOptions
    }
    static isSubMenuExpandingMode(value: Object | string | number | undefined): boolean {
        return value instanceof SubMenuExpandingMode
    }
    static isSubmitEvent(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof SubmitEvent
    }
    static isSubTabBarIndicatorStyle(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean): boolean {
        return value instanceof SubTabBarIndicatorStyle
    }
    static isSubTabBarStyle(value: Object | string | number | undefined): boolean {
        return value instanceof SubTabBarStyle
    }
    static isSurfaceRect(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof SurfaceRect
    }
    static isSurfaceRotationOptions(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof SurfaceRotationOptions
    }
    static isSweepGradientOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean): boolean {
        return value instanceof SweepGradientOptions
    }
    static isSwipeActionItem(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean): boolean {
        return value instanceof SwipeActionItem
    }
    static isSwipeActionOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof SwipeActionOptions
    }
    static isSwipeActionState(value: Object | string | number | undefined): boolean {
        return value instanceof SwipeActionState
    }
    static isSwipeDirection(value: Object | string | number | undefined): boolean {
        return value instanceof SwipeDirection
    }
    static isSwipeEdgeEffect(value: Object | string | number | undefined): boolean {
        return value instanceof SwipeEdgeEffect
    }
    static isSwipeGesture(value: Object | string | number | undefined): boolean {
        return value instanceof SwipeGesture
    }
    static isSwipeGestureEvent(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof SwipeGestureEvent
    }
    static isSwipeGestureHandlerOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof SwipeGestureHandlerOptions
    }
    static isSwiperAnimationEvent(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof SwiperAnimationEvent
    }
    static isSwiperAnimationMode(value: Object | string | number | undefined): boolean {
        return value instanceof SwiperAnimationMode
    }
    static isSwiperAutoFill(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof SwiperAutoFill
    }
    static isSwiperContentAnimatedTransition(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof SwiperContentAnimatedTransition
    }
    static isSwiperContentTransitionProxy(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof SwiperContentTransitionProxy
    }
    static isSwiperContentWillScrollResult(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof SwiperContentWillScrollResult
    }
    static isSwiperController(value: Object | string | number | undefined): boolean {
        return value instanceof SwiperController
    }
    static isSwiperDisplayMode(value: Object | string | number | undefined): boolean {
        return value instanceof SwiperDisplayMode
    }
    static isSwipeRecognizer(value: Object | string | number | undefined): boolean {
        return value instanceof SwipeRecognizer
    }
    static isSwiperNestedScrollMode(value: Object | string | number | undefined): boolean {
        return value instanceof SwiperNestedScrollMode
    }
    static isSwitchStyle(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof SwitchStyle
    }
    static isSymbolEffect(value: Object | string | number | undefined): boolean {
        return value instanceof SymbolEffect
    }
    static isSymbolEffectStrategy(value: Object | string | number | undefined): boolean {
        return value instanceof SymbolEffectStrategy
    }
    static isSymbolGlyphModifier(value: Object | string | number | undefined): boolean {
        return value instanceof SymbolGlyphModifier
    }
    static isSymbolRenderingStrategy(value: Object | string | number | undefined): boolean {
        return value instanceof SymbolRenderingStrategy
    }
    static isSystemAdaptiveOptions(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof SystemAdaptiveOptions
    }
    static isTabBarIconStyle(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof TabBarIconStyle
    }
    static isTabBarLabelStyle(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean): boolean {
        return value instanceof TabBarLabelStyle
    }
    static isTabBarOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof TabBarOptions
    }
    static isTabBarSymbol(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof TabBarSymbol
    }
    static isTabContentAnimatedTransition(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof TabContentAnimatedTransition
    }
    static isTabContentTransitionProxy(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof TabContentTransitionProxy
    }
    static isTabsAnimationEvent(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof TabsAnimationEvent
    }
    static isTabsCacheMode(value: Object | string | number | undefined): boolean {
        return value instanceof TabsCacheMode
    }
    static isTabsController(value: Object | string | number | undefined): boolean {
        return value instanceof TabsController
    }
    static isTabsOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof TabsOptions
    }
    static isTapGestureEvent(value: Object | string | number | undefined): boolean {
        return value instanceof TapGestureEvent
    }
    static isTapGestureInterface(value: Object | string | number | undefined): boolean {
        return value instanceof TapGestureInterface
    }
    static isTapGestureParameters(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof TapGestureParameters
    }
    static isTapRecognizer(value: Object | string | number | undefined): boolean {
        return value instanceof TapRecognizer
    }
    static isTargetInfo(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof TargetInfo
    }
    static isTerminationInfo(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof TerminationInfo
    }
    static istext_Affinity(value: Object | string | number | undefined): boolean {
        return value instanceof text.Affinity
    }
    static istext_BreakStrategy(value: Object | string | number | undefined): boolean {
        return value instanceof text.BreakStrategy
    }
    static istext_Decoration(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof text.Decoration
    }
    static istext_EllipsisMode(value: Object | string | number | undefined): boolean {
        return value instanceof text.EllipsisMode
    }
    static istext_FontCollection(value: Object | string | number | undefined): boolean {
        return value instanceof text.FontCollection
    }
    static istext_FontDescriptor(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean, arg9: boolean): boolean {
        return value instanceof text.FontDescriptor
    }
    static istext_FontFeature(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof text.FontFeature
    }
    static istext_FontStyle(value: Object | string | number | undefined): boolean {
        return value instanceof text.FontStyle
    }
    static istext_FontVariation(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof text.FontVariation
    }
    static istext_FontWeight(value: Object | string | number | undefined): boolean {
        return value instanceof text.FontWeight
    }
    static istext_FontWidth(value: Object | string | number | undefined): boolean {
        return value instanceof text.FontWidth
    }
    static istext_LineMetrics(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean, arg9: boolean, arg10: boolean): boolean {
        return value instanceof text.LineMetrics
    }
    static istext_LineTypeset(value: Object | string | number | undefined): boolean {
        return value instanceof text.LineTypeset
    }
    static istext_Paragraph(value: Object | string | number | undefined): boolean {
        return value instanceof text.Paragraph
    }
    static istext_ParagraphBuilder(value: Object | string | number | undefined): boolean {
        return value instanceof text.ParagraphBuilder
    }
    static istext_ParagraphStyle(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean): boolean {
        return value instanceof text.ParagraphStyle
    }
    static istext_PlaceholderAlignment(value: Object | string | number | undefined): boolean {
        return value instanceof text.PlaceholderAlignment
    }
    static istext_PlaceholderSpan(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean): boolean {
        return value instanceof text.PlaceholderSpan
    }
    static istext_PositionWithAffinity(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof text.PositionWithAffinity
    }
    static istext_Range(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof text.Range
    }
    static istext_RectHeightStyle(value: Object | string | number | undefined): boolean {
        return value instanceof text.RectHeightStyle
    }
    static istext_RectStyle(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean): boolean {
        return value instanceof text.RectStyle
    }
    static istext_RectWidthStyle(value: Object | string | number | undefined): boolean {
        return value instanceof text.RectWidthStyle
    }
    static istext_Run(value: Object | string | number | undefined): boolean {
        return value instanceof text.Run
    }
    static istext_RunMetrics(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof text.RunMetrics
    }
    static istext_StrutStyle(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean, arg9: boolean, arg10: boolean): boolean {
        return value instanceof text.StrutStyle
    }
    static istext_SystemFontType(value: Object | string | number | undefined): boolean {
        return value instanceof text.SystemFontType
    }
    static istext_TextAlign(value: Object | string | number | undefined): boolean {
        return value instanceof text.TextAlign
    }
    static istext_TextBaseline(value: Object | string | number | undefined): boolean {
        return value instanceof text.TextBaseline
    }
    static istext_TextBox(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof text.TextBox
    }
    static istext_TextDecorationStyle(value: Object | string | number | undefined): boolean {
        return value instanceof text.TextDecorationStyle
    }
    static istext_TextDecorationType(value: Object | string | number | undefined): boolean {
        return value instanceof text.TextDecorationType
    }
    static istext_TextDirection(value: Object | string | number | undefined): boolean {
        return value instanceof text.TextDirection
    }
    static istext_TextHeightBehavior(value: Object | string | number | undefined): boolean {
        return value instanceof text.TextHeightBehavior
    }
    static istext_TextLine(value: Object | string | number | undefined): boolean {
        return value instanceof text.TextLine
    }
    static istext_TextShadow(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof text.TextShadow
    }
    static istext_TextStyle(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean, arg9: boolean, arg10: boolean, arg11: boolean, arg12: boolean, arg13: boolean, arg14: boolean, arg15: boolean, arg16: boolean, arg17: boolean, arg18: boolean, arg19: boolean): boolean {
        return value instanceof text.TextStyle
    }
    static istext_TextTab(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof text.TextTab
    }
    static istext_TypographicBounds(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof text.TypographicBounds
    }
    static istext_WordBreak(value: Object | string | number | undefined): boolean {
        return value instanceof text.WordBreak
    }
    static isTextAlign(value: Object | string | number | undefined): boolean {
        return value instanceof TextAlign
    }
    static isTextAreaController(value: Object | string | number | undefined): boolean {
        return value instanceof TextAreaController
    }
    static isTextAreaOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof TextAreaOptions
    }
    static isTextAreaType(value: Object | string | number | undefined): boolean {
        return value instanceof TextAreaType
    }
    static isTextBackgroundStyle(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof TextBackgroundStyle
    }
    static isTextBaseController(value: Object | string | number | undefined): boolean {
        return value instanceof TextBaseController
    }
    static isTextCascadePickerRangeContent(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof TextCascadePickerRangeContent
    }
    static isTextCase(value: Object | string | number | undefined): boolean {
        return value instanceof TextCase
    }
    static isTextChangeOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof TextChangeOptions
    }
    static isTextClockConfiguration(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof TextClockConfiguration
    }
    static isTextClockController(value: Object | string | number | undefined): boolean {
        return value instanceof TextClockController
    }
    static isTextClockOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof TextClockOptions
    }
    static isTextContentControllerBase(value: Object | string | number | undefined): boolean {
        return value instanceof TextContentControllerBase
    }
    static isTextContentControllerOptions(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof TextContentControllerOptions
    }
    static isTextContentStyle(value: Object | string | number | undefined): boolean {
        return value instanceof TextContentStyle
    }
    static isTextController(value: Object | string | number | undefined): boolean {
        return value instanceof TextController
    }
    static isTextDataDetectorConfig(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof TextDataDetectorConfig
    }
    static isTextDataDetectorType(value: Object | string | number | undefined): boolean {
        return value instanceof TextDataDetectorType
    }
    static isTextDecorationOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof TextDecorationOptions
    }
    static isTextDecorationStyle(value: Object | string | number | undefined): boolean {
        return value instanceof TextDecorationStyle
    }
    static isTextDecorationType(value: Object | string | number | undefined): boolean {
        return value instanceof TextDecorationType
    }
    static isTextDeleteDirection(value: Object | string | number | undefined): boolean {
        return value instanceof TextDeleteDirection
    }
    static isTextEditControllerEx(value: Object | string | number | undefined): boolean {
        return value instanceof TextEditControllerEx
    }
    static isTextHeightAdaptivePolicy(value: Object | string | number | undefined): boolean {
        return value instanceof TextHeightAdaptivePolicy
    }
    static isTextInputController(value: Object | string | number | undefined): boolean {
        return value instanceof TextInputController
    }
    static isTextInputOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof TextInputOptions
    }
    static isTextInputStyle(value: Object | string | number | undefined): boolean {
        return value instanceof TextInputStyle
    }
    static isTextMarqueeOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean): boolean {
        return value instanceof TextMarqueeOptions
    }
    static isTextMenuController(value: Object | string | number | undefined): boolean {
        return value instanceof TextMenuController
    }
    static isTextMenuItem(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof TextMenuItem
    }
    static isTextMenuItemId(value: Object | string | number | undefined): boolean {
        return value instanceof TextMenuItemId
    }
    static isTextMenuOptions(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof TextMenuOptions
    }
    static isTextMenuShowMode(value: Object | string | number | undefined): boolean {
        return value instanceof TextMenuShowMode
    }
    static isTextMetrics(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean, arg9: boolean, arg10: boolean, arg11: boolean, arg12: boolean): boolean {
        return value instanceof TextMetrics
    }
    static isTextModifier(value: Object | string | number | undefined): boolean {
        return value instanceof TextModifier
    }
    static isTextOptions(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof TextOptions
    }
    static isTextOverflow(value: Object | string | number | undefined): boolean {
        return value instanceof TextOverflow
    }
    static isTextOverflowOptions(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof TextOverflowOptions
    }
    static isTextPickerDialog(value: Object | string | number | undefined): boolean {
        return value instanceof TextPickerDialog
    }
    static isTextPickerDialogOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean, arg9: boolean, arg10: boolean, arg11: boolean, arg12: boolean, arg13: boolean, arg14: boolean, arg15: boolean, arg16: boolean, arg17: boolean, arg18: boolean, arg19: boolean, arg20: boolean, arg21: boolean, arg22: boolean, arg23: boolean, arg24: boolean, arg25: boolean, arg26: boolean, arg27: boolean, arg28: boolean): boolean {
        return value instanceof TextPickerDialogOptions
    }
    static isTextPickerOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof TextPickerOptions
    }
    static isTextPickerRangeContent(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof TextPickerRangeContent
    }
    static isTextPickerResult(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof TextPickerResult
    }
    static isTextPickerTextStyle(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof TextPickerTextStyle
    }
    static isTextRange(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof TextRange
    }
    static isTextResponseType(value: Object | string | number | undefined): boolean {
        return value instanceof TextResponseType
    }
    static isTextSelectableMode(value: Object | string | number | undefined): boolean {
        return value instanceof TextSelectableMode
    }
    static isTextShadowStyle(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof TextShadowStyle
    }
    static isTextSpanType(value: Object | string | number | undefined): boolean {
        return value instanceof TextSpanType
    }
    static isTextStyle(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean): boolean {
        return value instanceof TextStyle
    }
    static isTextStyleInterface(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean): boolean {
        return value instanceof TextStyleInterface
    }
    static isTextTimerConfiguration(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof TextTimerConfiguration
    }
    static isTextTimerController(value: Object | string | number | undefined): boolean {
        return value instanceof TextTimerController
    }
    static isTextTimerOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof TextTimerOptions
    }
    static isThemeColorMode(value: Object | string | number | undefined): boolean {
        return value instanceof ThemeColorMode
    }
    static isThemeControl(value: Object | string | number | undefined): boolean {
        return value instanceof ThemeControl
    }
    static isThreatType(value: Object | string | number | undefined): boolean {
        return value instanceof ThreatType
    }
    static isTimePickerDialog(value: Object | string | number | undefined): boolean {
        return value instanceof TimePickerDialog
    }
    static isTimePickerFormat(value: Object | string | number | undefined): boolean {
        return value instanceof TimePickerFormat
    }
    static isTimePickerOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof TimePickerOptions
    }
    static isTimePickerResult(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof TimePickerResult
    }
    static isTipsOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean): boolean {
        return value instanceof TipsOptions
    }
    static isTitleHeight(value: Object | string | number | undefined): boolean {
        return value instanceof TitleHeight
    }
    static isToggleConfiguration(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof ToggleConfiguration
    }
    static isToggleOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof ToggleOptions
    }
    static isToggleType(value: Object | string | number | undefined): boolean {
        return value instanceof ToggleType
    }
    static isToolbarItem(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean): boolean {
        return value instanceof ToolbarItem
    }
    static isToolbarItemStatus(value: Object | string | number | undefined): boolean {
        return value instanceof ToolbarItemStatus
    }
    static isTouchEvent(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean): boolean {
        return value instanceof TouchEvent
    }
    static isTouchObject(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean, arg9: boolean, arg10: boolean, arg11: boolean, arg12: boolean): boolean {
        return value instanceof TouchObject
    }
    static isTouchResult(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof TouchResult
    }
    static isTouchTestInfo(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean): boolean {
        return value instanceof TouchTestInfo
    }
    static isTouchTestStrategy(value: Object | string | number | undefined): boolean {
        return value instanceof TouchTestStrategy
    }
    static isTouchType(value: Object | string | number | undefined): boolean {
        return value instanceof TouchType
    }
    static isTransitionEdge(value: Object | string | number | undefined): boolean {
        return value instanceof TransitionEdge
    }
    static isTransitionEffect(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof TransitionEffect
    }
    static isTransitionHierarchyStrategy(value: Object | string | number | undefined): boolean {
        return value instanceof TransitionHierarchyStrategy
    }
    static isTransitionType(value: Object | string | number | undefined): boolean {
        return value instanceof TransitionType
    }
    static isTranslateOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof TranslateOptions
    }
    static isTranslateResult(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof TranslateResult
    }
    static isUICommonEvent(value: Object | string | number | undefined): boolean {
        return value instanceof UICommonEvent
    }
    static isUIContext(value: Object | string | number | undefined): boolean {
        return value instanceof UIContext
    }
    static isuiEffect_BrightnessBlender(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean): boolean {
        return value instanceof uiEffect.BrightnessBlender
    }
    static isuiEffect_BrightnessBlenderParam(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean): boolean {
        return value instanceof uiEffect.BrightnessBlenderParam
    }
    static isuiEffect_Filter(value: Object | string | number | undefined): boolean {
        return value instanceof uiEffect.Filter
    }
    static isuiEffect_VisualEffect(value: Object | string | number | undefined): boolean {
        return value instanceof uiEffect.VisualEffect
    }
    static isUIExtensionOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean): boolean {
        return value instanceof UIExtensionOptions
    }
    static isUIExtensionProxy(value: Object | string | number | undefined): boolean {
        return value instanceof UIExtensionProxy
    }
    static isUIGestureEvent(value: Object | string | number | undefined): boolean {
        return value instanceof UIGestureEvent
    }
    static isUnderlineColor(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof UnderlineColor
    }
    static isunifiedDataChannel_Summary(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof unifiedDataChannel.Summary
    }
    static isunifiedDataChannel_UnifiedData(value: Object | string | number | undefined): boolean {
        return value instanceof unifiedDataChannel.UnifiedData
    }
    static isuniformTypeDescriptor_UniformDataType(value: Object | string | number | undefined): boolean {
        return value instanceof uniformTypeDescriptor.UniformDataType
    }
    static isUrlStyle(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof UrlStyle
    }
    static isUserDataSpan(value: Object | string | number | undefined): boolean {
        return value instanceof UserDataSpan
    }
    static isVector2(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof Vector2
    }
    static isVector3(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof Vector3
    }
    static isVerticalAlign(value: Object | string | number | undefined): boolean {
        return value instanceof VerticalAlign
    }
    static isVideoController(value: Object | string | number | undefined): boolean {
        return value instanceof VideoController
    }
    static isVideoOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean): boolean {
        return value instanceof VideoOptions
    }
    static isViewportFit(value: Object | string | number | undefined): boolean {
        return value instanceof ViewportFit
    }
    static isViewportRect(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof ViewportRect
    }
    static isVisibility(value: Object | string | number | undefined): boolean {
        return value instanceof Visibility
    }
    static isVisibleAreaEventOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof VisibleAreaEventOptions
    }
    static isVisibleListContentInfo(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof VisibleListContentInfo
    }
    static isWant(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean, arg5: boolean, arg6: boolean, arg7: boolean, arg8: boolean, arg9: boolean): boolean {
        return value instanceof Want
    }
    static isWaterFlowLayoutMode(value: Object | string | number | undefined): boolean {
        return value instanceof WaterFlowLayoutMode
    }
    static isWaterFlowOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean): boolean {
        return value instanceof WaterFlowOptions
    }
    static isWaterFlowSections(value: Object | string | number | undefined): boolean {
        return value instanceof WaterFlowSections
    }
    static isWebCaptureMode(value: Object | string | number | undefined): boolean {
        return value instanceof WebCaptureMode
    }
    static isWebContextMenuParam(value: Object | string | number | undefined): boolean {
        return value instanceof WebContextMenuParam
    }
    static isWebContextMenuResult(value: Object | string | number | undefined): boolean {
        return value instanceof WebContextMenuResult
    }
    static isWebCookie(value: Object | string | number | undefined): boolean {
        return value instanceof WebCookie
    }
    static isWebDarkMode(value: Object | string | number | undefined): boolean {
        return value instanceof WebDarkMode
    }
    static isWebElementType(value: Object | string | number | undefined): boolean {
        return value instanceof WebElementType
    }
    static isWebKeyboardAvoidMode(value: Object | string | number | undefined): boolean {
        return value instanceof WebKeyboardAvoidMode
    }
    static isWebKeyboardCallbackInfo(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof WebKeyboardCallbackInfo
    }
    static isWebKeyboardController(value: Object | string | number | undefined): boolean {
        return value instanceof WebKeyboardController
    }
    static isWebKeyboardOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof WebKeyboardOptions
    }
    static isWebLayoutMode(value: Object | string | number | undefined): boolean {
        return value instanceof WebLayoutMode
    }
    static isWebMediaOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof WebMediaOptions
    }
    static isWebNavigationType(value: Object | string | number | undefined): boolean {
        return value instanceof WebNavigationType
    }
    static isWebOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean, arg4: boolean): boolean {
        return value instanceof WebOptions
    }
    static isWebResourceError(value: Object | string | number | undefined): boolean {
        return value instanceof WebResourceError
    }
    static isWebResourceRequest(value: Object | string | number | undefined): boolean {
        return value instanceof WebResourceRequest
    }
    static isWebResourceResponse(value: Object | string | number | undefined): boolean {
        return value instanceof WebResourceResponse
    }
    static isWebResponseType(value: Object | string | number | undefined): boolean {
        return value instanceof WebResponseType
    }
    static iswebview_WebHeader(value: Object | string | number | undefined, arg0: boolean, arg1: boolean): boolean {
        return value instanceof webview.WebHeader
    }
    static iswebview_WebviewController(value: Object | string | number | undefined): boolean {
        return value instanceof webview.WebviewController
    }
    static isWeek(value: Object | string | number | undefined): boolean {
        return value instanceof Week
    }
    static isWidthBreakpoint(value: Object | string | number | undefined): boolean {
        return value instanceof WidthBreakpoint
    }
    static iswindow_SystemBarStyle(value: Object | string | number | undefined, arg0: boolean): boolean {
        return value instanceof window.SystemBarStyle
    }
    static iswindow_WindowStatusType(value: Object | string | number | undefined): boolean {
        return value instanceof window.WindowStatusType
    }
    static isWindowAnimationTarget(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof WindowAnimationTarget
    }
    static isWindowModeFollowStrategy(value: Object | string | number | undefined): boolean {
        return value instanceof WindowModeFollowStrategy
    }
    static isWordBreak(value: Object | string | number | undefined): boolean {
        return value instanceof WordBreak
    }
    static isWorkerEventListener(value: Object | string | number | undefined): boolean {
        return value instanceof WorkerEventListener
    }
    static isWorkerOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof WorkerOptions
    }
    static isXComponentController(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean): boolean {
        return value instanceof XComponentController
    }
    static isXComponentOptions(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof XComponentOptions
    }
    static isXComponentParameter(value: Object | string | number | undefined, arg0: boolean, arg1: boolean, arg2: boolean, arg3: boolean): boolean {
        return value instanceof XComponentParameter
    }
    static isXComponentType(value: Object | string | number | undefined): boolean {
        return value instanceof XComponentType
    }
    static AccessibilityHoverType_ToNumeric(value: AccessibilityHoverType): int32 {
        return value.valueOf()
    }
    static AccessibilityHoverType_FromNumeric(ordinal: int32): AccessibilityHoverType {
        return AccessibilityHoverType.fromValue(ordinal)
    }
    static AccessibilityRoleType_ToNumeric(value: AccessibilityRoleType): int32 {
        return value.valueOf()
    }
    static AccessibilityRoleType_FromNumeric(ordinal: int32): AccessibilityRoleType {
        return AccessibilityRoleType.fromValue(ordinal)
    }
    static AccessibilitySamePageMode_ToNumeric(value: AccessibilitySamePageMode): int32 {
        return value.valueOf()
    }
    static AccessibilitySamePageMode_FromNumeric(ordinal: int32): AccessibilitySamePageMode {
        return AccessibilitySamePageMode.fromValue(ordinal)
    }
    static AdaptiveColor_ToNumeric(value: AdaptiveColor): int32 {
        return value.valueOf()
    }
    static AdaptiveColor_FromNumeric(ordinal: int32): AdaptiveColor {
        return AdaptiveColor.fromValue(ordinal)
    }
    static Alignment_ToNumeric(value: Alignment): int32 {
        return value.valueOf()
    }
    static Alignment_FromNumeric(ordinal: int32): Alignment {
        return Alignment.fromValue(ordinal)
    }
    static AnimationMode_ToNumeric(value: AnimationMode): int32 {
        return value.valueOf()
    }
    static AnimationMode_FromNumeric(ordinal: int32): AnimationMode {
        return AnimationMode.fromValue(ordinal)
    }
    static AnimationStatus_ToNumeric(value: AnimationStatus): int32 {
        return value.valueOf()
    }
    static AnimationStatus_FromNumeric(ordinal: int32): AnimationStatus {
        return AnimationStatus.fromValue(ordinal)
    }
    static AppRotation_ToNumeric(value: AppRotation): int32 {
        return value.valueOf()
    }
    static AppRotation_FromNumeric(ordinal: int32): AppRotation {
        return AppRotation.fromValue(ordinal)
    }
    static ArrowPointPosition_ToNumeric(value: ArrowPointPosition): int32 {
        return value.getOrdinal()
    }
    static ArrowPointPosition_FromNumeric(ordinal: int32): ArrowPointPosition {
        return ArrowPointPosition.values()[ordinal]
    }
    static ArrowPosition_ToNumeric(value: ArrowPosition): int32 {
        return value.valueOf()
    }
    static ArrowPosition_FromNumeric(ordinal: int32): ArrowPosition {
        return ArrowPosition.fromValue(ordinal)
    }
    static AutoCapitalizationMode_ToNumeric(value: AutoCapitalizationMode): int32 {
        return value.valueOf()
    }
    static AutoCapitalizationMode_FromNumeric(ordinal: int32): AutoCapitalizationMode {
        return AutoCapitalizationMode.fromValue(ordinal)
    }
    static AvoidanceMode_ToNumeric(value: AvoidanceMode): int32 {
        return value.valueOf()
    }
    static AvoidanceMode_FromNumeric(ordinal: int32): AvoidanceMode {
        return AvoidanceMode.fromValue(ordinal)
    }
    static Axis_ToNumeric(value: Axis): int32 {
        return value.valueOf()
    }
    static Axis_FromNumeric(ordinal: int32): Axis {
        return Axis.fromValue(ordinal)
    }
    static AxisAction_ToNumeric(value: AxisAction): int32 {
        return value.valueOf()
    }
    static AxisAction_FromNumeric(ordinal: int32): AxisAction {
        return AxisAction.fromValue(ordinal)
    }
    static AxisModel_ToNumeric(value: AxisModel): int32 {
        return value.valueOf()
    }
    static AxisModel_FromNumeric(ordinal: int32): AxisModel {
        return AxisModel.fromValue(ordinal)
    }
    static BadgePosition_ToNumeric(value: BadgePosition): int32 {
        return value.valueOf()
    }
    static BadgePosition_FromNumeric(ordinal: int32): BadgePosition {
        return BadgePosition.fromValue(ordinal)
    }
    static BarMode_ToNumeric(value: BarMode): int32 {
        return value.valueOf()
    }
    static BarMode_FromNumeric(ordinal: int32): BarMode {
        return BarMode.fromValue(ordinal)
    }
    static BarPosition_ToNumeric(value: BarPosition): int32 {
        return value.valueOf()
    }
    static BarPosition_FromNumeric(ordinal: int32): BarPosition {
        return BarPosition.fromValue(ordinal)
    }
    static BarrierDirection_ToNumeric(value: BarrierDirection): int32 {
        return value.valueOf()
    }
    static BarrierDirection_FromNumeric(ordinal: int32): BarrierDirection {
        return BarrierDirection.fromValue(ordinal)
    }
    static BarState_ToNumeric(value: BarState): int32 {
        return value.valueOf()
    }
    static BarState_FromNumeric(ordinal: int32): BarState {
        return BarState.fromValue(ordinal)
    }
    static BarStyle_ToNumeric(value: BarStyle): int32 {
        return value.valueOf()
    }
    static BarStyle_FromNumeric(ordinal: int32): BarStyle {
        return BarStyle.fromValue(ordinal)
    }
    static BlendApplyType_ToNumeric(value: BlendApplyType): int32 {
        return value.valueOf()
    }
    static BlendApplyType_FromNumeric(ordinal: int32): BlendApplyType {
        return BlendApplyType.fromValue(ordinal)
    }
    static BlendMode_ToNumeric(value: BlendMode): int32 {
        return value.valueOf()
    }
    static BlendMode_FromNumeric(ordinal: int32): BlendMode {
        return BlendMode.fromValue(ordinal)
    }
    static BlurOnKeyboardHideMode_ToNumeric(value: BlurOnKeyboardHideMode): int32 {
        return value.valueOf()
    }
    static BlurOnKeyboardHideMode_FromNumeric(ordinal: int32): BlurOnKeyboardHideMode {
        return BlurOnKeyboardHideMode.fromValue(ordinal)
    }
    static BlurStyle_ToNumeric(value: BlurStyle): int32 {
        return value.valueOf()
    }
    static BlurStyle_FromNumeric(ordinal: int32): BlurStyle {
        return BlurStyle.fromValue(ordinal)
    }
    static BlurStyleActivePolicy_ToNumeric(value: BlurStyleActivePolicy): int32 {
        return value.valueOf()
    }
    static BlurStyleActivePolicy_FromNumeric(ordinal: int32): BlurStyleActivePolicy {
        return BlurStyleActivePolicy.fromValue(ordinal)
    }
    static BorderStyle_ToNumeric(value: BorderStyle): int32 {
        return value.valueOf()
    }
    static BorderStyle_FromNumeric(ordinal: int32): BorderStyle {
        return BorderStyle.fromValue(ordinal)
    }
    static BreakpointsReference_ToNumeric(value: BreakpointsReference): int32 {
        return value.valueOf()
    }
    static BreakpointsReference_FromNumeric(ordinal: int32): BreakpointsReference {
        return BreakpointsReference.fromValue(ordinal)
    }
    static ButtonRole_ToNumeric(value: ButtonRole): int32 {
        return value.valueOf()
    }
    static ButtonRole_FromNumeric(ordinal: int32): ButtonRole {
        return ButtonRole.fromValue(ordinal)
    }
    static ButtonStyleMode_ToNumeric(value: ButtonStyleMode): int32 {
        return value.valueOf()
    }
    static ButtonStyleMode_FromNumeric(ordinal: int32): ButtonStyleMode {
        return ButtonStyleMode.fromValue(ordinal)
    }
    static ButtonType_ToNumeric(value: ButtonType): int32 {
        return value.valueOf()
    }
    static ButtonType_FromNumeric(ordinal: int32): ButtonType {
        return ButtonType.fromValue(ordinal)
    }
    static CacheMode_ToNumeric(value: CacheMode): int32 {
        return value.valueOf()
    }
    static CacheMode_FromNumeric(ordinal: int32): CacheMode {
        return CacheMode.fromValue(ordinal)
    }
    static CalendarAlign_ToNumeric(value: CalendarAlign): int32 {
        return value.valueOf()
    }
    static CalendarAlign_FromNumeric(ordinal: int32): CalendarAlign {
        return CalendarAlign.fromValue(ordinal)
    }
    static CancelButtonStyle_ToNumeric(value: CancelButtonStyle): int32 {
        return value.valueOf()
    }
    static CancelButtonStyle_FromNumeric(ordinal: int32): CancelButtonStyle {
        return CancelButtonStyle.fromValue(ordinal)
    }
    static ChainEdgeEffect_ToNumeric(value: ChainEdgeEffect): int32 {
        return value.valueOf()
    }
    static ChainEdgeEffect_FromNumeric(ordinal: int32): ChainEdgeEffect {
        return ChainEdgeEffect.fromValue(ordinal)
    }
    static ChainStyle_ToNumeric(value: ChainStyle): int32 {
        return value.valueOf()
    }
    static ChainStyle_FromNumeric(ordinal: int32): ChainStyle {
        return ChainStyle.fromValue(ordinal)
    }
    static CheckBoxShape_ToNumeric(value: CheckBoxShape): int32 {
        return value.valueOf()
    }
    static CheckBoxShape_FromNumeric(ordinal: int32): CheckBoxShape {
        return CheckBoxShape.fromValue(ordinal)
    }
    static ClickEffectLevel_ToNumeric(value: ClickEffectLevel): int32 {
        return value.valueOf()
    }
    static ClickEffectLevel_FromNumeric(ordinal: int32): ClickEffectLevel {
        return ClickEffectLevel.fromValue(ordinal)
    }
    static Color_ToNumeric(value: Color): int32 {
        return value.valueOf()
    }
    static Color_FromNumeric(ordinal: int32): Color {
        return Color.fromValue(ordinal)
    }
    static ColoringStrategy_ToNumeric(value: ColoringStrategy): int32 {
        return value.getOrdinal()
    }
    static ColoringStrategy_FromNumeric(ordinal: int32): ColoringStrategy {
        return ColoringStrategy.values()[ordinal]
    }
    static ColorMode_ToNumeric(value: ColorMode): int32 {
        return value.valueOf()
    }
    static ColorMode_FromNumeric(ordinal: int32): ColorMode {
        return ColorMode.fromValue(ordinal)
    }
    static ContentClipMode_ToNumeric(value: ContentClipMode): int32 {
        return value.valueOf()
    }
    static ContentClipMode_FromNumeric(ordinal: int32): ContentClipMode {
        return ContentClipMode.fromValue(ordinal)
    }
    static ContentType_ToNumeric(value: ContentType): int32 {
        return value.valueOf()
    }
    static ContentType_FromNumeric(ordinal: int32): ContentType {
        return ContentType.fromValue(ordinal)
    }
    static ContextMenuEditStateFlags_ToNumeric(value: ContextMenuEditStateFlags): int32 {
        return value.valueOf()
    }
    static ContextMenuEditStateFlags_FromNumeric(ordinal: int32): ContextMenuEditStateFlags {
        return ContextMenuEditStateFlags.fromValue(ordinal)
    }
    static ContextMenuInputFieldType_ToNumeric(value: ContextMenuInputFieldType): int32 {
        return value.valueOf()
    }
    static ContextMenuInputFieldType_FromNumeric(ordinal: int32): ContextMenuInputFieldType {
        return ContextMenuInputFieldType.fromValue(ordinal)
    }
    static ContextMenuMediaType_ToNumeric(value: ContextMenuMediaType): int32 {
        return value.valueOf()
    }
    static ContextMenuMediaType_FromNumeric(ordinal: int32): ContextMenuMediaType {
        return ContextMenuMediaType.fromValue(ordinal)
    }
    static ContextMenuSourceType_ToNumeric(value: ContextMenuSourceType): int32 {
        return value.valueOf()
    }
    static ContextMenuSourceType_FromNumeric(ordinal: int32): ContextMenuSourceType {
        return ContextMenuSourceType.fromValue(ordinal)
    }
    static ControlSize_ToNumeric(value: ControlSize): int32 {
        return value.getOrdinal()
    }
    static ControlSize_FromNumeric(ordinal: int32): ControlSize {
        return ControlSize.values()[ordinal]
    }
    static CopyOptions_ToNumeric(value: CopyOptions): int32 {
        return value.valueOf()
    }
    static CopyOptions_FromNumeric(ordinal: int32): CopyOptions {
        return CopyOptions.fromValue(ordinal)
    }
    static CrownAction_ToNumeric(value: CrownAction): int32 {
        return value.valueOf()
    }
    static CrownAction_FromNumeric(ordinal: int32): CrownAction {
        return CrownAction.fromValue(ordinal)
    }
    static CrownSensitivity_ToNumeric(value: CrownSensitivity): int32 {
        return value.valueOf()
    }
    static CrownSensitivity_FromNumeric(ordinal: int32): CrownSensitivity {
        return CrownSensitivity.fromValue(ordinal)
    }
    static curves_Curve_ToNumeric(value: curves.Curve): int32 {
        return value.valueOf()
    }
    static curves_Curve_FromNumeric(ordinal: int32): curves.Curve {
        return curves.Curve.fromValue(ordinal)
    }
    static DataOperationType_ToNumeric(value: DataOperationType): int32 {
        return value.getOrdinal()
    }
    static DataOperationType_FromNumeric(ordinal: int32): DataOperationType {
        return DataOperationType.values()[ordinal]
    }
    static DataPanelType_ToNumeric(value: DataPanelType): int32 {
        return value.valueOf()
    }
    static DataPanelType_FromNumeric(ordinal: int32): DataPanelType {
        return DataPanelType.fromValue(ordinal)
    }
    static DatePickerMode_ToNumeric(value: DatePickerMode): int32 {
        return value.valueOf()
    }
    static DatePickerMode_FromNumeric(ordinal: int32): DatePickerMode {
        return DatePickerMode.fromValue(ordinal)
    }
    static DialogAlignment_ToNumeric(value: DialogAlignment): int32 {
        return value.valueOf()
    }
    static DialogAlignment_FromNumeric(ordinal: int32): DialogAlignment {
        return DialogAlignment.fromValue(ordinal)
    }
    static DialogButtonDirection_ToNumeric(value: DialogButtonDirection): int32 {
        return value.valueOf()
    }
    static DialogButtonDirection_FromNumeric(ordinal: int32): DialogButtonDirection {
        return DialogButtonDirection.fromValue(ordinal)
    }
    static DialogButtonStyle_ToNumeric(value: DialogButtonStyle): int32 {
        return value.valueOf()
    }
    static DialogButtonStyle_FromNumeric(ordinal: int32): DialogButtonStyle {
        return DialogButtonStyle.fromValue(ordinal)
    }
    static Direction_ToNumeric(value: Direction): int32 {
        return value.valueOf()
    }
    static Direction_FromNumeric(ordinal: int32): Direction {
        return Direction.fromValue(ordinal)
    }
    static DismissReason_ToNumeric(value: DismissReason): int32 {
        return value.valueOf()
    }
    static DismissReason_FromNumeric(ordinal: int32): DismissReason {
        return DismissReason.fromValue(ordinal)
    }
    static DistributionType_ToNumeric(value: DistributionType): int32 {
        return value.valueOf()
    }
    static DistributionType_FromNumeric(ordinal: int32): DistributionType {
        return DistributionType.fromValue(ordinal)
    }
    static DisturbanceFieldShape_ToNumeric(value: DisturbanceFieldShape): int32 {
        return value.valueOf()
    }
    static DisturbanceFieldShape_FromNumeric(ordinal: int32): DisturbanceFieldShape {
        return DisturbanceFieldShape.fromValue(ordinal)
    }
    static DividerMode_ToNumeric(value: DividerMode): int32 {
        return value.valueOf()
    }
    static DividerMode_FromNumeric(ordinal: int32): DividerMode {
        return DividerMode.fromValue(ordinal)
    }
    static DpiFollowStrategy_ToNumeric(value: DpiFollowStrategy): int32 {
        return value.valueOf()
    }
    static DpiFollowStrategy_FromNumeric(ordinal: int32): DpiFollowStrategy {
        return DpiFollowStrategy.fromValue(ordinal)
    }
    static DragBehavior_ToNumeric(value: DragBehavior): int32 {
        return value.valueOf()
    }
    static DragBehavior_FromNumeric(ordinal: int32): DragBehavior {
        return DragBehavior.fromValue(ordinal)
    }
    static DraggingSizeChangeEffect_ToNumeric(value: DraggingSizeChangeEffect): int32 {
        return value.valueOf()
    }
    static DraggingSizeChangeEffect_FromNumeric(ordinal: int32): DraggingSizeChangeEffect {
        return DraggingSizeChangeEffect.fromValue(ordinal)
    }
    static DragPreviewMode_ToNumeric(value: DragPreviewMode): int32 {
        return value.valueOf()
    }
    static DragPreviewMode_FromNumeric(ordinal: int32): DragPreviewMode {
        return DragPreviewMode.fromValue(ordinal)
    }
    static DragResult_ToNumeric(value: DragResult): int32 {
        return value.valueOf()
    }
    static DragResult_FromNumeric(ordinal: int32): DragResult {
        return DragResult.fromValue(ordinal)
    }
    static drawing_BlendMode_ToNumeric(value: drawing.BlendMode): int32 {
        return value.valueOf()
    }
    static drawing_BlendMode_FromNumeric(ordinal: int32): drawing.BlendMode {
        return drawing.BlendMode.fromValue(ordinal)
    }
    static drawing_BlurType_ToNumeric(value: drawing.BlurType): int32 {
        return value.valueOf()
    }
    static drawing_BlurType_FromNumeric(ordinal: int32): drawing.BlurType {
        return drawing.BlurType.fromValue(ordinal)
    }
    static drawing_CapStyle_ToNumeric(value: drawing.CapStyle): int32 {
        return value.valueOf()
    }
    static drawing_CapStyle_FromNumeric(ordinal: int32): drawing.CapStyle {
        return drawing.CapStyle.fromValue(ordinal)
    }
    static drawing_ClipOp_ToNumeric(value: drawing.ClipOp): int32 {
        return value.valueOf()
    }
    static drawing_ClipOp_FromNumeric(ordinal: int32): drawing.ClipOp {
        return drawing.ClipOp.fromValue(ordinal)
    }
    static drawing_CornerPos_ToNumeric(value: drawing.CornerPos): int32 {
        return value.valueOf()
    }
    static drawing_CornerPos_FromNumeric(ordinal: int32): drawing.CornerPos {
        return drawing.CornerPos.fromValue(ordinal)
    }
    static drawing_FilterMode_ToNumeric(value: drawing.FilterMode): int32 {
        return value.valueOf()
    }
    static drawing_FilterMode_FromNumeric(ordinal: int32): drawing.FilterMode {
        return drawing.FilterMode.fromValue(ordinal)
    }
    static drawing_FontEdging_ToNumeric(value: drawing.FontEdging): int32 {
        return value.valueOf()
    }
    static drawing_FontEdging_FromNumeric(ordinal: int32): drawing.FontEdging {
        return drawing.FontEdging.fromValue(ordinal)
    }
    static drawing_FontHinting_ToNumeric(value: drawing.FontHinting): int32 {
        return value.valueOf()
    }
    static drawing_FontHinting_FromNumeric(ordinal: int32): drawing.FontHinting {
        return drawing.FontHinting.fromValue(ordinal)
    }
    static drawing_FontMetricsFlags_ToNumeric(value: drawing.FontMetricsFlags): int32 {
        return value.valueOf()
    }
    static drawing_FontMetricsFlags_FromNumeric(ordinal: int32): drawing.FontMetricsFlags {
        return drawing.FontMetricsFlags.fromValue(ordinal)
    }
    static drawing_JoinStyle_ToNumeric(value: drawing.JoinStyle): int32 {
        return value.valueOf()
    }
    static drawing_JoinStyle_FromNumeric(ordinal: int32): drawing.JoinStyle {
        return drawing.JoinStyle.fromValue(ordinal)
    }
    static drawing_PathDirection_ToNumeric(value: drawing.PathDirection): int32 {
        return value.valueOf()
    }
    static drawing_PathDirection_FromNumeric(ordinal: int32): drawing.PathDirection {
        return drawing.PathDirection.fromValue(ordinal)
    }
    static drawing_PathFillType_ToNumeric(value: drawing.PathFillType): int32 {
        return value.valueOf()
    }
    static drawing_PathFillType_FromNumeric(ordinal: int32): drawing.PathFillType {
        return drawing.PathFillType.fromValue(ordinal)
    }
    static drawing_PathMeasureMatrixFlags_ToNumeric(value: drawing.PathMeasureMatrixFlags): int32 {
        return value.valueOf()
    }
    static drawing_PathMeasureMatrixFlags_FromNumeric(ordinal: int32): drawing.PathMeasureMatrixFlags {
        return drawing.PathMeasureMatrixFlags.fromValue(ordinal)
    }
    static drawing_PathOp_ToNumeric(value: drawing.PathOp): int32 {
        return value.valueOf()
    }
    static drawing_PathOp_FromNumeric(ordinal: int32): drawing.PathOp {
        return drawing.PathOp.fromValue(ordinal)
    }
    static drawing_PointMode_ToNumeric(value: drawing.PointMode): int32 {
        return value.valueOf()
    }
    static drawing_PointMode_FromNumeric(ordinal: int32): drawing.PointMode {
        return drawing.PointMode.fromValue(ordinal)
    }
    static drawing_RectType_ToNumeric(value: drawing.RectType): int32 {
        return value.valueOf()
    }
    static drawing_RectType_FromNumeric(ordinal: int32): drawing.RectType {
        return drawing.RectType.fromValue(ordinal)
    }
    static drawing_RegionOp_ToNumeric(value: drawing.RegionOp): int32 {
        return value.valueOf()
    }
    static drawing_RegionOp_FromNumeric(ordinal: int32): drawing.RegionOp {
        return drawing.RegionOp.fromValue(ordinal)
    }
    static drawing_ScaleToFit_ToNumeric(value: drawing.ScaleToFit): int32 {
        return value.valueOf()
    }
    static drawing_ScaleToFit_FromNumeric(ordinal: int32): drawing.ScaleToFit {
        return drawing.ScaleToFit.fromValue(ordinal)
    }
    static drawing_ShadowFlag_ToNumeric(value: drawing.ShadowFlag): int32 {
        return value.valueOf()
    }
    static drawing_ShadowFlag_FromNumeric(ordinal: int32): drawing.ShadowFlag {
        return drawing.ShadowFlag.fromValue(ordinal)
    }
    static drawing_SrcRectConstraint_ToNumeric(value: drawing.SrcRectConstraint): int32 {
        return value.valueOf()
    }
    static drawing_SrcRectConstraint_FromNumeric(ordinal: int32): drawing.SrcRectConstraint {
        return drawing.SrcRectConstraint.fromValue(ordinal)
    }
    static drawing_TextEncoding_ToNumeric(value: drawing.TextEncoding): int32 {
        return value.valueOf()
    }
    static drawing_TextEncoding_FromNumeric(ordinal: int32): drawing.TextEncoding {
        return drawing.TextEncoding.fromValue(ordinal)
    }
    static drawing_TileMode_ToNumeric(value: drawing.TileMode): int32 {
        return value.valueOf()
    }
    static drawing_TileMode_FromNumeric(ordinal: int32): drawing.TileMode {
        return drawing.TileMode.fromValue(ordinal)
    }
    static DynamicRangeMode_ToNumeric(value: DynamicRangeMode): int32 {
        return value.valueOf()
    }
    static DynamicRangeMode_FromNumeric(ordinal: int32): DynamicRangeMode {
        return DynamicRangeMode.fromValue(ordinal)
    }
    static Edge_ToNumeric(value: Edge): int32 {
        return value.valueOf()
    }
    static Edge_FromNumeric(ordinal: int32): Edge {
        return Edge.fromValue(ordinal)
    }
    static EdgeEffect_ToNumeric(value: EdgeEffect): int32 {
        return value.valueOf()
    }
    static EdgeEffect_FromNumeric(ordinal: int32): EdgeEffect {
        return EdgeEffect.fromValue(ordinal)
    }
    static EffectDirection_ToNumeric(value: EffectDirection): int32 {
        return value.valueOf()
    }
    static EffectDirection_FromNumeric(ordinal: int32): EffectDirection {
        return EffectDirection.fromValue(ordinal)
    }
    static EffectEdge_ToNumeric(value: EffectEdge): int32 {
        return value.valueOf()
    }
    static EffectEdge_FromNumeric(ordinal: int32): EffectEdge {
        return EffectEdge.fromValue(ordinal)
    }
    static EffectFillStyle_ToNumeric(value: EffectFillStyle): int32 {
        return value.valueOf()
    }
    static EffectFillStyle_FromNumeric(ordinal: int32): EffectFillStyle {
        return EffectFillStyle.fromValue(ordinal)
    }
    static EffectScope_ToNumeric(value: EffectScope): int32 {
        return value.valueOf()
    }
    static EffectScope_FromNumeric(ordinal: int32): EffectScope {
        return EffectScope.fromValue(ordinal)
    }
    static EffectType_ToNumeric(value: EffectType): int32 {
        return value.valueOf()
    }
    static EffectType_FromNumeric(ordinal: int32): EffectType {
        return EffectType.fromValue(ordinal)
    }
    static EllipsisMode_ToNumeric(value: EllipsisMode): int32 {
        return value.valueOf()
    }
    static EllipsisMode_FromNumeric(ordinal: int32): EllipsisMode {
        return EllipsisMode.fromValue(ordinal)
    }
    static EmbeddedType_ToNumeric(value: EmbeddedType): int32 {
        return value.valueOf()
    }
    static EmbeddedType_FromNumeric(ordinal: int32): EmbeddedType {
        return EmbeddedType.fromValue(ordinal)
    }
    static EnterKeyType_ToNumeric(value: EnterKeyType): int32 {
        return value.valueOf()
    }
    static EnterKeyType_FromNumeric(ordinal: int32): EnterKeyType {
        return EnterKeyType.fromValue(ordinal)
    }
    static FileSelectorMode_ToNumeric(value: FileSelectorMode): int32 {
        return value.valueOf()
    }
    static FileSelectorMode_FromNumeric(ordinal: int32): FileSelectorMode {
        return FileSelectorMode.fromValue(ordinal)
    }
    static FillMode_ToNumeric(value: FillMode): int32 {
        return value.valueOf()
    }
    static FillMode_FromNumeric(ordinal: int32): FillMode {
        return FillMode.fromValue(ordinal)
    }
    static FinishCallbackType_ToNumeric(value: FinishCallbackType): int32 {
        return value.valueOf()
    }
    static FinishCallbackType_FromNumeric(ordinal: int32): FinishCallbackType {
        return FinishCallbackType.fromValue(ordinal)
    }
    static FlexAlign_ToNumeric(value: FlexAlign): int32 {
        return value.valueOf()
    }
    static FlexAlign_FromNumeric(ordinal: int32): FlexAlign {
        return FlexAlign.fromValue(ordinal)
    }
    static FlexDirection_ToNumeric(value: FlexDirection): int32 {
        return value.valueOf()
    }
    static FlexDirection_FromNumeric(ordinal: int32): FlexDirection {
        return FlexDirection.fromValue(ordinal)
    }
    static FlexWrap_ToNumeric(value: FlexWrap): int32 {
        return value.valueOf()
    }
    static FlexWrap_FromNumeric(ordinal: int32): FlexWrap {
        return FlexWrap.fromValue(ordinal)
    }
    static FocusDrawLevel_ToNumeric(value: FocusDrawLevel): int32 {
        return value.valueOf()
    }
    static FocusDrawLevel_FromNumeric(ordinal: int32): FocusDrawLevel {
        return FocusDrawLevel.fromValue(ordinal)
    }
    static FocusPriority_ToNumeric(value: FocusPriority): int32 {
        return value.valueOf()
    }
    static FocusPriority_FromNumeric(ordinal: int32): FocusPriority {
        return FocusPriority.fromValue(ordinal)
    }
    static FoldStatus_ToNumeric(value: FoldStatus): int32 {
        return value.valueOf()
    }
    static FoldStatus_FromNumeric(ordinal: int32): FoldStatus {
        return FoldStatus.fromValue(ordinal)
    }
    static FontStyle_ToNumeric(value: FontStyle): int32 {
        return value.valueOf()
    }
    static FontStyle_FromNumeric(ordinal: int32): FontStyle {
        return FontStyle.fromValue(ordinal)
    }
    static FontWeight_ToNumeric(value: FontWeight): int32 {
        return value.valueOf()
    }
    static FontWeight_FromNumeric(ordinal: int32): FontWeight {
        return FontWeight.fromValue(ordinal)
    }
    static FormDimension_ToNumeric(value: FormDimension): int32 {
        return value.valueOf()
    }
    static FormDimension_FromNumeric(ordinal: int32): FormDimension {
        return FormDimension.fromValue(ordinal)
    }
    static FormRenderingMode_ToNumeric(value: FormRenderingMode): int32 {
        return value.valueOf()
    }
    static FormRenderingMode_FromNumeric(ordinal: int32): FormRenderingMode {
        return FormRenderingMode.fromValue(ordinal)
    }
    static FormShape_ToNumeric(value: FormShape): int32 {
        return value.valueOf()
    }
    static FormShape_FromNumeric(ordinal: int32): FormShape {
        return FormShape.fromValue(ordinal)
    }
    static FunctionKey_ToNumeric(value: FunctionKey): int32 {
        return value.valueOf()
    }
    static FunctionKey_FromNumeric(ordinal: int32): FunctionKey {
        return FunctionKey.fromValue(ordinal)
    }
    static GestureControl_GestureType_ToNumeric(value: GestureControl.GestureType): int32 {
        return value.valueOf()
    }
    static GestureControl_GestureType_FromNumeric(ordinal: int32): GestureControl.GestureType {
        return GestureControl.GestureType.fromValue(ordinal)
    }
    static GestureJudgeResult_ToNumeric(value: GestureJudgeResult): int32 {
        return value.valueOf()
    }
    static GestureJudgeResult_FromNumeric(ordinal: int32): GestureJudgeResult {
        return GestureJudgeResult.fromValue(ordinal)
    }
    static GestureMask_ToNumeric(value: GestureMask): int32 {
        return value.valueOf()
    }
    static GestureMask_FromNumeric(ordinal: int32): GestureMask {
        return GestureMask.fromValue(ordinal)
    }
    static GestureMode_ToNumeric(value: GestureMode): int32 {
        return value.valueOf()
    }
    static GestureMode_FromNumeric(ordinal: int32): GestureMode {
        return GestureMode.fromValue(ordinal)
    }
    static GesturePriority_ToNumeric(value: GesturePriority): int32 {
        return value.valueOf()
    }
    static GesturePriority_FromNumeric(ordinal: int32): GesturePriority {
        return GesturePriority.fromValue(ordinal)
    }
    static GestureRecognizerState_ToNumeric(value: GestureRecognizerState): int32 {
        return value.valueOf()
    }
    static GestureRecognizerState_FromNumeric(ordinal: int32): GestureRecognizerState {
        return GestureRecognizerState.fromValue(ordinal)
    }
    static GradientDirection_ToNumeric(value: GradientDirection): int32 {
        return value.valueOf()
    }
    static GradientDirection_FromNumeric(ordinal: int32): GradientDirection {
        return GradientDirection.fromValue(ordinal)
    }
    static GridDirection_ToNumeric(value: GridDirection): int32 {
        return value.valueOf()
    }
    static GridDirection_FromNumeric(ordinal: int32): GridDirection {
        return GridDirection.fromValue(ordinal)
    }
    static GridItemAlignment_ToNumeric(value: GridItemAlignment): int32 {
        return value.valueOf()
    }
    static GridItemAlignment_FromNumeric(ordinal: int32): GridItemAlignment {
        return GridItemAlignment.fromValue(ordinal)
    }
    static GridItemStyle_ToNumeric(value: GridItemStyle): int32 {
        return value.valueOf()
    }
    static GridItemStyle_FromNumeric(ordinal: int32): GridItemStyle {
        return GridItemStyle.fromValue(ordinal)
    }
    static GridRowDirection_ToNumeric(value: GridRowDirection): int32 {
        return value.valueOf()
    }
    static GridRowDirection_FromNumeric(ordinal: int32): GridRowDirection {
        return GridRowDirection.fromValue(ordinal)
    }
    static HapticFeedbackMode_ToNumeric(value: HapticFeedbackMode): int32 {
        return value.valueOf()
    }
    static HapticFeedbackMode_FromNumeric(ordinal: int32): HapticFeedbackMode {
        return HapticFeedbackMode.fromValue(ordinal)
    }
    static HeightBreakpoint_ToNumeric(value: HeightBreakpoint): int32 {
        return value.valueOf()
    }
    static HeightBreakpoint_FromNumeric(ordinal: int32): HeightBreakpoint {
        return HeightBreakpoint.fromValue(ordinal)
    }
    static HitTestMode_ToNumeric(value: HitTestMode): int32 {
        return value.valueOf()
    }
    static HitTestMode_FromNumeric(ordinal: int32): HitTestMode {
        return HitTestMode.fromValue(ordinal)
    }
    static HitTestType_ToNumeric(value: HitTestType): int32 {
        return value.valueOf()
    }
    static HitTestType_FromNumeric(ordinal: int32): HitTestType {
        return HitTestType.fromValue(ordinal)
    }
    static HorizontalAlign_ToNumeric(value: HorizontalAlign): int32 {
        return value.valueOf()
    }
    static HorizontalAlign_FromNumeric(ordinal: int32): HorizontalAlign {
        return HorizontalAlign.fromValue(ordinal)
    }
    static HoverEffect_ToNumeric(value: HoverEffect): int32 {
        return value.valueOf()
    }
    static HoverEffect_FromNumeric(ordinal: int32): HoverEffect {
        return HoverEffect.fromValue(ordinal)
    }
    static HoverModeAreaType_ToNumeric(value: HoverModeAreaType): int32 {
        return value.valueOf()
    }
    static HoverModeAreaType_FromNumeric(ordinal: int32): HoverModeAreaType {
        return HoverModeAreaType.fromValue(ordinal)
    }
    static IlluminatedType_ToNumeric(value: IlluminatedType): int32 {
        return value.valueOf()
    }
    static IlluminatedType_FromNumeric(ordinal: int32): IlluminatedType {
        return IlluminatedType.fromValue(ordinal)
    }
    static image_ResolutionQuality_ToNumeric(value: image.ResolutionQuality): int32 {
        return value.valueOf()
    }
    static image_ResolutionQuality_FromNumeric(ordinal: int32): image.ResolutionQuality {
        return image.ResolutionQuality.fromValue(ordinal)
    }
    static ImageAnalyzerType_ToNumeric(value: ImageAnalyzerType): int32 {
        return value.valueOf()
    }
    static ImageAnalyzerType_FromNumeric(ordinal: int32): ImageAnalyzerType {
        return ImageAnalyzerType.fromValue(ordinal)
    }
    static ImageContent_ToNumeric(value: ImageContent): int32 {
        return value.valueOf()
    }
    static ImageContent_FromNumeric(ordinal: int32): ImageContent {
        return ImageContent.fromValue(ordinal)
    }
    static ImageFit_ToNumeric(value: ImageFit): int32 {
        return value.valueOf()
    }
    static ImageFit_FromNumeric(ordinal: int32): ImageFit {
        return ImageFit.fromValue(ordinal)
    }
    static ImageInterpolation_ToNumeric(value: ImageInterpolation): int32 {
        return value.valueOf()
    }
    static ImageInterpolation_FromNumeric(ordinal: int32): ImageInterpolation {
        return ImageInterpolation.fromValue(ordinal)
    }
    static ImageRenderMode_ToNumeric(value: ImageRenderMode): int32 {
        return value.valueOf()
    }
    static ImageRenderMode_FromNumeric(ordinal: int32): ImageRenderMode {
        return ImageRenderMode.fromValue(ordinal)
    }
    static ImageRepeat_ToNumeric(value: ImageRepeat): int32 {
        return value.valueOf()
    }
    static ImageRepeat_FromNumeric(ordinal: int32): ImageRepeat {
        return ImageRepeat.fromValue(ordinal)
    }
    static ImageRotateOrientation_ToNumeric(value: ImageRotateOrientation): int32 {
        return value.valueOf()
    }
    static ImageRotateOrientation_FromNumeric(ordinal: int32): ImageRotateOrientation {
        return ImageRotateOrientation.fromValue(ordinal)
    }
    static ImageSize_ToNumeric(value: ImageSize): int32 {
        return value.valueOf()
    }
    static ImageSize_FromNumeric(ordinal: int32): ImageSize {
        return ImageSize.fromValue(ordinal)
    }
    static ImageSpanAlignment_ToNumeric(value: ImageSpanAlignment): int32 {
        return value.valueOf()
    }
    static ImageSpanAlignment_FromNumeric(ordinal: int32): ImageSpanAlignment {
        return ImageSpanAlignment.fromValue(ordinal)
    }
    static ImmersiveMode_ToNumeric(value: ImmersiveMode): int32 {
        return value.valueOf()
    }
    static ImmersiveMode_FromNumeric(ordinal: int32): ImmersiveMode {
        return ImmersiveMode.fromValue(ordinal)
    }
    static IndexerAlign_ToNumeric(value: IndexerAlign): int32 {
        return value.valueOf()
    }
    static IndexerAlign_FromNumeric(ordinal: int32): IndexerAlign {
        return IndexerAlign.fromValue(ordinal)
    }
    static InputType_ToNumeric(value: InputType): int32 {
        return value.valueOf()
    }
    static InputType_FromNumeric(ordinal: int32): InputType {
        return InputType.fromValue(ordinal)
    }
    static IntentionCode_ToNumeric(value: IntentionCode): int32 {
        return value.valueOf()
    }
    static IntentionCode_FromNumeric(ordinal: int32): IntentionCode {
        return IntentionCode.fromValue(ordinal)
    }
    static InteractionHand_ToNumeric(value: InteractionHand): int32 {
        return value.valueOf()
    }
    static InteractionHand_FromNumeric(ordinal: int32): InteractionHand {
        return InteractionHand.fromValue(ordinal)
    }
    static ItemAlign_ToNumeric(value: ItemAlign): int32 {
        return value.valueOf()
    }
    static ItemAlign_FromNumeric(ordinal: int32): ItemAlign {
        return ItemAlign.fromValue(ordinal)
    }
    static ItemState_ToNumeric(value: ItemState): int32 {
        return value.valueOf()
    }
    static ItemState_FromNumeric(ordinal: int32): ItemState {
        return ItemState.fromValue(ordinal)
    }
    static KeyboardAppearance_ToNumeric(value: KeyboardAppearance): int32 {
        return value.valueOf()
    }
    static KeyboardAppearance_FromNumeric(ordinal: int32): KeyboardAppearance {
        return KeyboardAppearance.fromValue(ordinal)
    }
    static KeyboardAvoidMode_ToNumeric(value: KeyboardAvoidMode): int32 {
        return value.valueOf()
    }
    static KeyboardAvoidMode_FromNumeric(ordinal: int32): KeyboardAvoidMode {
        return KeyboardAvoidMode.fromValue(ordinal)
    }
    static KeyProcessingMode_ToNumeric(value: KeyProcessingMode): int32 {
        return value.valueOf()
    }
    static KeyProcessingMode_FromNumeric(ordinal: int32): KeyProcessingMode {
        return KeyProcessingMode.fromValue(ordinal)
    }
    static KeySource_ToNumeric(value: KeySource): int32 {
        return value.valueOf()
    }
    static KeySource_FromNumeric(ordinal: int32): KeySource {
        return KeySource.fromValue(ordinal)
    }
    static KeyType_ToNumeric(value: KeyType): int32 {
        return value.valueOf()
    }
    static KeyType_FromNumeric(ordinal: int32): KeyType {
        return KeyType.fromValue(ordinal)
    }
    static LaunchMode_ToNumeric(value: LaunchMode): int32 {
        return value.valueOf()
    }
    static LaunchMode_FromNumeric(ordinal: int32): LaunchMode {
        return LaunchMode.fromValue(ordinal)
    }
    static LayoutDirection_ToNumeric(value: LayoutDirection): int32 {
        return value.valueOf()
    }
    static LayoutDirection_FromNumeric(ordinal: int32): LayoutDirection {
        return LayoutDirection.fromValue(ordinal)
    }
    static LayoutMode_ToNumeric(value: LayoutMode): int32 {
        return value.valueOf()
    }
    static LayoutMode_FromNumeric(ordinal: int32): LayoutMode {
        return LayoutMode.fromValue(ordinal)
    }
    static LayoutSafeAreaEdge_ToNumeric(value: LayoutSafeAreaEdge): int32 {
        return value.valueOf()
    }
    static LayoutSafeAreaEdge_FromNumeric(ordinal: int32): LayoutSafeAreaEdge {
        return LayoutSafeAreaEdge.fromValue(ordinal)
    }
    static LayoutSafeAreaType_ToNumeric(value: LayoutSafeAreaType): int32 {
        return value.valueOf()
    }
    static LayoutSafeAreaType_FromNumeric(ordinal: int32): LayoutSafeAreaType {
        return LayoutSafeAreaType.fromValue(ordinal)
    }
    static LayoutStyle_ToNumeric(value: LayoutStyle): int32 {
        return value.valueOf()
    }
    static LayoutStyle_FromNumeric(ordinal: int32): LayoutStyle {
        return LayoutStyle.fromValue(ordinal)
    }
    static LengthMetricsUnit_ToNumeric(value: LengthMetricsUnit): int32 {
        return value.valueOf()
    }
    static LengthMetricsUnit_FromNumeric(ordinal: int32): LengthMetricsUnit {
        return LengthMetricsUnit.fromValue(ordinal)
    }
    static LengthUnit_ToNumeric(value: LengthUnit): int32 {
        return value.valueOf()
    }
    static LengthUnit_FromNumeric(ordinal: int32): LengthUnit {
        return LengthUnit.fromValue(ordinal)
    }
    static LevelMode_ToNumeric(value: LevelMode): int32 {
        return value.valueOf()
    }
    static LevelMode_FromNumeric(ordinal: int32): LevelMode {
        return LevelMode.fromValue(ordinal)
    }
    static LineBreakStrategy_ToNumeric(value: LineBreakStrategy): int32 {
        return value.valueOf()
    }
    static LineBreakStrategy_FromNumeric(ordinal: int32): LineBreakStrategy {
        return LineBreakStrategy.fromValue(ordinal)
    }
    static LineCapStyle_ToNumeric(value: LineCapStyle): int32 {
        return value.valueOf()
    }
    static LineCapStyle_FromNumeric(ordinal: int32): LineCapStyle {
        return LineCapStyle.fromValue(ordinal)
    }
    static LineJoinStyle_ToNumeric(value: LineJoinStyle): int32 {
        return value.valueOf()
    }
    static LineJoinStyle_FromNumeric(ordinal: int32): LineJoinStyle {
        return LineJoinStyle.fromValue(ordinal)
    }
    static ListItemAlign_ToNumeric(value: ListItemAlign): int32 {
        return value.valueOf()
    }
    static ListItemAlign_FromNumeric(ordinal: int32): ListItemAlign {
        return ListItemAlign.fromValue(ordinal)
    }
    static ListItemGroupArea_ToNumeric(value: ListItemGroupArea): int32 {
        return value.valueOf()
    }
    static ListItemGroupArea_FromNumeric(ordinal: int32): ListItemGroupArea {
        return ListItemGroupArea.fromValue(ordinal)
    }
    static ListItemGroupStyle_ToNumeric(value: ListItemGroupStyle): int32 {
        return value.valueOf()
    }
    static ListItemGroupStyle_FromNumeric(ordinal: int32): ListItemGroupStyle {
        return ListItemGroupStyle.fromValue(ordinal)
    }
    static ListItemStyle_ToNumeric(value: ListItemStyle): int32 {
        return value.valueOf()
    }
    static ListItemStyle_FromNumeric(ordinal: int32): ListItemStyle {
        return ListItemStyle.fromValue(ordinal)
    }
    static LoadingProgressStyle_ToNumeric(value: LoadingProgressStyle): int32 {
        return value.valueOf()
    }
    static LoadingProgressStyle_FromNumeric(ordinal: int32): LoadingProgressStyle {
        return LoadingProgressStyle.fromValue(ordinal)
    }
    static LocalizedBarrierDirection_ToNumeric(value: LocalizedBarrierDirection): int32 {
        return value.valueOf()
    }
    static LocalizedBarrierDirection_FromNumeric(ordinal: int32): LocalizedBarrierDirection {
        return LocalizedBarrierDirection.fromValue(ordinal)
    }
    static LocationButtonOnClickResult_ToNumeric(value: LocationButtonOnClickResult): int32 {
        return value.valueOf()
    }
    static LocationButtonOnClickResult_FromNumeric(ordinal: int32): LocationButtonOnClickResult {
        return LocationButtonOnClickResult.fromValue(ordinal)
    }
    static LocationDescription_ToNumeric(value: LocationDescription): int32 {
        return value.valueOf()
    }
    static LocationDescription_FromNumeric(ordinal: int32): LocationDescription {
        return LocationDescription.fromValue(ordinal)
    }
    static LocationIconStyle_ToNumeric(value: LocationIconStyle): int32 {
        return value.valueOf()
    }
    static LocationIconStyle_FromNumeric(ordinal: int32): LocationIconStyle {
        return LocationIconStyle.fromValue(ordinal)
    }
    static MarqueeStartPolicy_ToNumeric(value: MarqueeStartPolicy): int32 {
        return value.valueOf()
    }
    static MarqueeStartPolicy_FromNumeric(ordinal: int32): MarqueeStartPolicy {
        return MarqueeStartPolicy.fromValue(ordinal)
    }
    static MarqueeState_ToNumeric(value: MarqueeState): int32 {
        return value.valueOf()
    }
    static MarqueeState_FromNumeric(ordinal: int32): MarqueeState {
        return MarqueeState.fromValue(ordinal)
    }
    static MarqueeUpdateStrategy_ToNumeric(value: MarqueeUpdateStrategy): int32 {
        return value.valueOf()
    }
    static MarqueeUpdateStrategy_FromNumeric(ordinal: int32): MarqueeUpdateStrategy {
        return MarqueeUpdateStrategy.fromValue(ordinal)
    }
    static MenuAlignType_ToNumeric(value: MenuAlignType): int32 {
        return value.valueOf()
    }
    static MenuAlignType_FromNumeric(ordinal: int32): MenuAlignType {
        return MenuAlignType.fromValue(ordinal)
    }
    static MenuPolicy_ToNumeric(value: MenuPolicy): int32 {
        return value.valueOf()
    }
    static MenuPolicy_FromNumeric(ordinal: int32): MenuPolicy {
        return MenuPolicy.fromValue(ordinal)
    }
    static MenuPreviewMode_ToNumeric(value: MenuPreviewMode): int32 {
        return value.valueOf()
    }
    static MenuPreviewMode_FromNumeric(ordinal: int32): MenuPreviewMode {
        return MenuPreviewMode.fromValue(ordinal)
    }
    static MenuType_ToNumeric(value: MenuType): int32 {
        return value.valueOf()
    }
    static MenuType_FromNumeric(ordinal: int32): MenuType {
        return MenuType.fromValue(ordinal)
    }
    static MessageLevel_ToNumeric(value: MessageLevel): int32 {
        return value.valueOf()
    }
    static MessageLevel_FromNumeric(ordinal: int32): MessageLevel {
        return MessageLevel.fromValue(ordinal)
    }
    static MixedMode_ToNumeric(value: MixedMode): int32 {
        return value.valueOf()
    }
    static MixedMode_FromNumeric(ordinal: int32): MixedMode {
        return MixedMode.fromValue(ordinal)
    }
    static ModalTransition_ToNumeric(value: ModalTransition): int32 {
        return value.valueOf()
    }
    static ModalTransition_FromNumeric(ordinal: int32): ModalTransition {
        return ModalTransition.fromValue(ordinal)
    }
    static ModifierKey_ToNumeric(value: ModifierKey): int32 {
        return value.valueOf()
    }
    static ModifierKey_FromNumeric(ordinal: int32): ModifierKey {
        return ModifierKey.fromValue(ordinal)
    }
    static MouseAction_ToNumeric(value: MouseAction): int32 {
        return value.valueOf()
    }
    static MouseAction_FromNumeric(ordinal: int32): MouseAction {
        return MouseAction.fromValue(ordinal)
    }
    static MouseButton_ToNumeric(value: MouseButton): int32 {
        return value.valueOf()
    }
    static MouseButton_FromNumeric(ordinal: int32): MouseButton {
        return MouseButton.fromValue(ordinal)
    }
    static NativeEmbedStatus_ToNumeric(value: NativeEmbedStatus): int32 {
        return value.valueOf()
    }
    static NativeEmbedStatus_FromNumeric(ordinal: int32): NativeEmbedStatus {
        return NativeEmbedStatus.fromValue(ordinal)
    }
    static NavBarPosition_ToNumeric(value: NavBarPosition): int32 {
        return value.valueOf()
    }
    static NavBarPosition_FromNumeric(ordinal: int32): NavBarPosition {
        return NavBarPosition.fromValue(ordinal)
    }
    static NavDestinationActiveReason_ToNumeric(value: NavDestinationActiveReason): int32 {
        return value.valueOf()
    }
    static NavDestinationActiveReason_FromNumeric(ordinal: int32): NavDestinationActiveReason {
        return NavDestinationActiveReason.fromValue(ordinal)
    }
    static NavDestinationMode_ToNumeric(value: NavDestinationMode): int32 {
        return value.valueOf()
    }
    static NavDestinationMode_FromNumeric(ordinal: int32): NavDestinationMode {
        return NavDestinationMode.fromValue(ordinal)
    }
    static NavigationMode_ToNumeric(value: NavigationMode): int32 {
        return value.valueOf()
    }
    static NavigationMode_FromNumeric(ordinal: int32): NavigationMode {
        return NavigationMode.fromValue(ordinal)
    }
    static NavigationOperation_ToNumeric(value: NavigationOperation): int32 {
        return value.valueOf()
    }
    static NavigationOperation_FromNumeric(ordinal: int32): NavigationOperation {
        return NavigationOperation.fromValue(ordinal)
    }
    static NavigationSystemTransitionType_ToNumeric(value: NavigationSystemTransitionType): int32 {
        return value.valueOf()
    }
    static NavigationSystemTransitionType_FromNumeric(ordinal: int32): NavigationSystemTransitionType {
        return NavigationSystemTransitionType.fromValue(ordinal)
    }
    static NavigationTitleMode_ToNumeric(value: NavigationTitleMode): int32 {
        return value.valueOf()
    }
    static NavigationTitleMode_FromNumeric(ordinal: int32): NavigationTitleMode {
        return NavigationTitleMode.fromValue(ordinal)
    }
    static NavigationType_ToNumeric(value: NavigationType): int32 {
        return value.valueOf()
    }
    static NavigationType_FromNumeric(ordinal: int32): NavigationType {
        return NavigationType.fromValue(ordinal)
    }
    static NestedScrollMode_ToNumeric(value: NestedScrollMode): int32 {
        return value.valueOf()
    }
    static NestedScrollMode_FromNumeric(ordinal: int32): NestedScrollMode {
        return NestedScrollMode.fromValue(ordinal)
    }
    static ObscuredReasons_ToNumeric(value: ObscuredReasons): int32 {
        return value.valueOf()
    }
    static ObscuredReasons_FromNumeric(ordinal: int32): ObscuredReasons {
        return ObscuredReasons.fromValue(ordinal)
    }
    static OptionWidthMode_ToNumeric(value: OptionWidthMode): int32 {
        return value.getOrdinal()
    }
    static OptionWidthMode_FromNumeric(ordinal: int32): OptionWidthMode {
        return OptionWidthMode.values()[ordinal]
    }
    static OutlineStyle_ToNumeric(value: OutlineStyle): int32 {
        return value.valueOf()
    }
    static OutlineStyle_FromNumeric(ordinal: int32): OutlineStyle {
        return OutlineStyle.fromValue(ordinal)
    }
    static OverScrollMode_ToNumeric(value: OverScrollMode): int32 {
        return value.valueOf()
    }
    static OverScrollMode_FromNumeric(ordinal: int32): OverScrollMode {
        return OverScrollMode.fromValue(ordinal)
    }
    static PageFlipMode_ToNumeric(value: PageFlipMode): int32 {
        return value.valueOf()
    }
    static PageFlipMode_FromNumeric(ordinal: int32): PageFlipMode {
        return PageFlipMode.fromValue(ordinal)
    }
    static PanDirection_ToNumeric(value: PanDirection): int32 {
        return value.valueOf()
    }
    static PanDirection_FromNumeric(ordinal: int32): PanDirection {
        return PanDirection.fromValue(ordinal)
    }
    static ParticleEmitterShape_ToNumeric(value: ParticleEmitterShape): int32 {
        return value.getOrdinal()
    }
    static ParticleEmitterShape_FromNumeric(ordinal: int32): ParticleEmitterShape {
        return ParticleEmitterShape.values()[ordinal]
    }
    static ParticleType_ToNumeric(value: ParticleType): int32 {
        return value.getOrdinal()
    }
    static ParticleType_FromNumeric(ordinal: int32): ParticleType {
        return ParticleType.values()[ordinal]
    }
    static ParticleUpdater_ToNumeric(value: ParticleUpdater): int32 {
        return value.getOrdinal()
    }
    static ParticleUpdater_FromNumeric(ordinal: int32): ParticleUpdater {
        return ParticleUpdater.values()[ordinal]
    }
    static PasteButtonOnClickResult_ToNumeric(value: PasteButtonOnClickResult): int32 {
        return value.valueOf()
    }
    static PasteButtonOnClickResult_FromNumeric(ordinal: int32): PasteButtonOnClickResult {
        return PasteButtonOnClickResult.fromValue(ordinal)
    }
    static PasteDescription_ToNumeric(value: PasteDescription): int32 {
        return value.valueOf()
    }
    static PasteDescription_FromNumeric(ordinal: int32): PasteDescription {
        return PasteDescription.fromValue(ordinal)
    }
    static PasteIconStyle_ToNumeric(value: PasteIconStyle): int32 {
        return value.valueOf()
    }
    static PasteIconStyle_FromNumeric(ordinal: int32): PasteIconStyle {
        return PasteIconStyle.fromValue(ordinal)
    }
    static PatternLockChallengeResult_ToNumeric(value: PatternLockChallengeResult): int32 {
        return value.valueOf()
    }
    static PatternLockChallengeResult_FromNumeric(ordinal: int32): PatternLockChallengeResult {
        return PatternLockChallengeResult.fromValue(ordinal)
    }
    static PerfMonitorActionType_ToNumeric(value: PerfMonitorActionType): int32 {
        return value.valueOf()
    }
    static PerfMonitorActionType_FromNumeric(ordinal: int32): PerfMonitorActionType {
        return PerfMonitorActionType.fromValue(ordinal)
    }
    static PerfMonitorSourceType_ToNumeric(value: PerfMonitorSourceType): int32 {
        return value.valueOf()
    }
    static PerfMonitorSourceType_FromNumeric(ordinal: int32): PerfMonitorSourceType {
        return PerfMonitorSourceType.fromValue(ordinal)
    }
    static PixelRoundCalcPolicy_ToNumeric(value: PixelRoundCalcPolicy): int32 {
        return value.valueOf()
    }
    static PixelRoundCalcPolicy_FromNumeric(ordinal: int32): PixelRoundCalcPolicy {
        return PixelRoundCalcPolicy.fromValue(ordinal)
    }
    static PixelRoundMode_ToNumeric(value: PixelRoundMode): int32 {
        return value.valueOf()
    }
    static PixelRoundMode_FromNumeric(ordinal: int32): PixelRoundMode {
        return PixelRoundMode.fromValue(ordinal)
    }
    static Placement_ToNumeric(value: Placement): int32 {
        return value.valueOf()
    }
    static Placement_FromNumeric(ordinal: int32): Placement {
        return Placement.fromValue(ordinal)
    }
    static PlaybackSpeed_ToNumeric(value: PlaybackSpeed): int32 {
        return value.valueOf()
    }
    static PlaybackSpeed_FromNumeric(ordinal: int32): PlaybackSpeed {
        return PlaybackSpeed.fromValue(ordinal)
    }
    static PlayMode_ToNumeric(value: PlayMode): int32 {
        return value.valueOf()
    }
    static PlayMode_FromNumeric(ordinal: int32): PlayMode {
        return PlayMode.fromValue(ordinal)
    }
    static pointer_PointerStyle_ToNumeric(value: pointer.PointerStyle): int32 {
        return value.valueOf()
    }
    static pointer_PointerStyle_FromNumeric(ordinal: int32): pointer.PointerStyle {
        return pointer.PointerStyle.fromValue(ordinal)
    }
    static PreDragStatus_ToNumeric(value: PreDragStatus): int32 {
        return value.valueOf()
    }
    static PreDragStatus_FromNumeric(ordinal: int32): PreDragStatus {
        return PreDragStatus.fromValue(ordinal)
    }
    static ProgressStatus_ToNumeric(value: ProgressStatus): int32 {
        return value.valueOf()
    }
    static ProgressStatus_FromNumeric(ordinal: int32): ProgressStatus {
        return ProgressStatus.fromValue(ordinal)
    }
    static ProgressStyle_ToNumeric(value: ProgressStyle): int32 {
        return value.valueOf()
    }
    static ProgressStyle_FromNumeric(ordinal: int32): ProgressStyle {
        return ProgressStyle.fromValue(ordinal)
    }
    static ProgressType_ToNumeric(value: ProgressType): int32 {
        return value.valueOf()
    }
    static ProgressType_FromNumeric(ordinal: int32): ProgressType {
        return ProgressType.fromValue(ordinal)
    }
    static ProtectedResourceType_ToNumeric(value: ProtectedResourceType): int32 {
        return value.getOrdinal()
    }
    static ProtectedResourceType_FromNumeric(ordinal: int32): ProtectedResourceType {
        return ProtectedResourceType.values()[ordinal]
    }
    static RadioIndicatorType_ToNumeric(value: RadioIndicatorType): int32 {
        return value.valueOf()
    }
    static RadioIndicatorType_FromNumeric(ordinal: int32): RadioIndicatorType {
        return RadioIndicatorType.fromValue(ordinal)
    }
    static RefreshStatus_ToNumeric(value: RefreshStatus): int32 {
        return value.valueOf()
    }
    static RefreshStatus_FromNumeric(ordinal: int32): RefreshStatus {
        return RefreshStatus.fromValue(ordinal)
    }
    static RelateType_ToNumeric(value: RelateType): int32 {
        return value.valueOf()
    }
    static RelateType_FromNumeric(ordinal: int32): RelateType {
        return RelateType.fromValue(ordinal)
    }
    static RenderExitReason_ToNumeric(value: RenderExitReason): int32 {
        return value.valueOf()
    }
    static RenderExitReason_FromNumeric(ordinal: int32): RenderExitReason {
        return RenderExitReason.fromValue(ordinal)
    }
    static RenderFit_ToNumeric(value: RenderFit): int32 {
        return value.valueOf()
    }
    static RenderFit_FromNumeric(ordinal: int32): RenderFit {
        return RenderFit.fromValue(ordinal)
    }
    static RenderMode_ToNumeric(value: RenderMode): int32 {
        return value.valueOf()
    }
    static RenderMode_FromNumeric(ordinal: int32): RenderMode {
        return RenderMode.fromValue(ordinal)
    }
    static RenderProcessNotRespondingReason_ToNumeric(value: RenderProcessNotRespondingReason): int32 {
        return value.valueOf()
    }
    static RenderProcessNotRespondingReason_FromNumeric(ordinal: int32): RenderProcessNotRespondingReason {
        return RenderProcessNotRespondingReason.fromValue(ordinal)
    }
    static RepeatMode_ToNumeric(value: RepeatMode): int32 {
        return value.valueOf()
    }
    static RepeatMode_FromNumeric(ordinal: int32): RepeatMode {
        return RepeatMode.fromValue(ordinal)
    }
    static ResponseType_ToNumeric(value: ResponseType): int32 {
        return value.valueOf()
    }
    static ResponseType_FromNumeric(ordinal: int32): ResponseType {
        return ResponseType.fromValue(ordinal)
    }
    static RichEditorDeleteDirection_ToNumeric(value: RichEditorDeleteDirection): int32 {
        return value.valueOf()
    }
    static RichEditorDeleteDirection_FromNumeric(ordinal: int32): RichEditorDeleteDirection {
        return RichEditorDeleteDirection.fromValue(ordinal)
    }
    static RichEditorResponseType_ToNumeric(value: RichEditorResponseType): int32 {
        return value.valueOf()
    }
    static RichEditorResponseType_FromNumeric(ordinal: int32): RichEditorResponseType {
        return RichEditorResponseType.fromValue(ordinal)
    }
    static RichEditorSpanType_ToNumeric(value: RichEditorSpanType): int32 {
        return value.valueOf()
    }
    static RichEditorSpanType_FromNumeric(ordinal: int32): RichEditorSpanType {
        return RichEditorSpanType.fromValue(ordinal)
    }
    static RouteType_ToNumeric(value: RouteType): int32 {
        return value.valueOf()
    }
    static RouteType_FromNumeric(ordinal: int32): RouteType {
        return RouteType.fromValue(ordinal)
    }
    static SafeAreaEdge_ToNumeric(value: SafeAreaEdge): int32 {
        return value.valueOf()
    }
    static SafeAreaEdge_FromNumeric(ordinal: int32): SafeAreaEdge {
        return SafeAreaEdge.fromValue(ordinal)
    }
    static SafeAreaType_ToNumeric(value: SafeAreaType): int32 {
        return value.valueOf()
    }
    static SafeAreaType_FromNumeric(ordinal: int32): SafeAreaType {
        return SafeAreaType.fromValue(ordinal)
    }
    static SaveButtonOnClickResult_ToNumeric(value: SaveButtonOnClickResult): int32 {
        return value.valueOf()
    }
    static SaveButtonOnClickResult_FromNumeric(ordinal: int32): SaveButtonOnClickResult {
        return SaveButtonOnClickResult.fromValue(ordinal)
    }
    static SaveDescription_ToNumeric(value: SaveDescription): int32 {
        return value.valueOf()
    }
    static SaveDescription_FromNumeric(ordinal: int32): SaveDescription {
        return SaveDescription.fromValue(ordinal)
    }
    static SaveIconStyle_ToNumeric(value: SaveIconStyle): int32 {
        return value.valueOf()
    }
    static SaveIconStyle_FromNumeric(ordinal: int32): SaveIconStyle {
        return SaveIconStyle.fromValue(ordinal)
    }
    static ScrollAlign_ToNumeric(value: ScrollAlign): int32 {
        return value.valueOf()
    }
    static ScrollAlign_FromNumeric(ordinal: int32): ScrollAlign {
        return ScrollAlign.fromValue(ordinal)
    }
    static ScrollBarDirection_ToNumeric(value: ScrollBarDirection): int32 {
        return value.valueOf()
    }
    static ScrollBarDirection_FromNumeric(ordinal: int32): ScrollBarDirection {
        return ScrollBarDirection.fromValue(ordinal)
    }
    static ScrollDirection_ToNumeric(value: ScrollDirection): int32 {
        return value.valueOf()
    }
    static ScrollDirection_FromNumeric(ordinal: int32): ScrollDirection {
        return ScrollDirection.fromValue(ordinal)
    }
    static ScrollSizeMode_ToNumeric(value: ScrollSizeMode): int32 {
        return value.valueOf()
    }
    static ScrollSizeMode_FromNumeric(ordinal: int32): ScrollSizeMode {
        return ScrollSizeMode.fromValue(ordinal)
    }
    static ScrollSnapAlign_ToNumeric(value: ScrollSnapAlign): int32 {
        return value.valueOf()
    }
    static ScrollSnapAlign_FromNumeric(ordinal: int32): ScrollSnapAlign {
        return ScrollSnapAlign.fromValue(ordinal)
    }
    static ScrollSource_ToNumeric(value: ScrollSource): int32 {
        return value.valueOf()
    }
    static ScrollSource_FromNumeric(ordinal: int32): ScrollSource {
        return ScrollSource.fromValue(ordinal)
    }
    static ScrollState_ToNumeric(value: ScrollState): int32 {
        return value.valueOf()
    }
    static ScrollState_FromNumeric(ordinal: int32): ScrollState {
        return ScrollState.fromValue(ordinal)
    }
    static SearchType_ToNumeric(value: SearchType): int32 {
        return value.valueOf()
    }
    static SearchType_FromNumeric(ordinal: int32): SearchType {
        return SearchType.fromValue(ordinal)
    }
    static SecurityComponentLayoutDirection_ToNumeric(value: SecurityComponentLayoutDirection): int32 {
        return value.valueOf()
    }
    static SecurityComponentLayoutDirection_FromNumeric(ordinal: int32): SecurityComponentLayoutDirection {
        return SecurityComponentLayoutDirection.fromValue(ordinal)
    }
    static SeekMode_ToNumeric(value: SeekMode): int32 {
        return value.valueOf()
    }
    static SeekMode_FromNumeric(ordinal: int32): SeekMode {
        return SeekMode.fromValue(ordinal)
    }
    static SelectedMode_ToNumeric(value: SelectedMode): int32 {
        return value.valueOf()
    }
    static SelectedMode_FromNumeric(ordinal: int32): SelectedMode {
        return SelectedMode.fromValue(ordinal)
    }
    static SelectStatus_ToNumeric(value: SelectStatus): int32 {
        return value.valueOf()
    }
    static SelectStatus_FromNumeric(ordinal: int32): SelectStatus {
        return SelectStatus.fromValue(ordinal)
    }
    static ShadowStyle_ToNumeric(value: ShadowStyle): int32 {
        return value.valueOf()
    }
    static ShadowStyle_FromNumeric(ordinal: int32): ShadowStyle {
        return ShadowStyle.fromValue(ordinal)
    }
    static ShadowType_ToNumeric(value: ShadowType): int32 {
        return value.valueOf()
    }
    static ShadowType_FromNumeric(ordinal: int32): ShadowType {
        return ShadowType.fromValue(ordinal)
    }
    static SharedTransitionEffectType_ToNumeric(value: SharedTransitionEffectType): int32 {
        return value.valueOf()
    }
    static SharedTransitionEffectType_FromNumeric(ordinal: int32): SharedTransitionEffectType {
        return SharedTransitionEffectType.fromValue(ordinal)
    }
    static SheetKeyboardAvoidMode_ToNumeric(value: SheetKeyboardAvoidMode): int32 {
        return value.valueOf()
    }
    static SheetKeyboardAvoidMode_FromNumeric(ordinal: int32): SheetKeyboardAvoidMode {
        return SheetKeyboardAvoidMode.fromValue(ordinal)
    }
    static SheetMode_ToNumeric(value: SheetMode): int32 {
        return value.valueOf()
    }
    static SheetMode_FromNumeric(ordinal: int32): SheetMode {
        return SheetMode.fromValue(ordinal)
    }
    static SheetSize_ToNumeric(value: SheetSize): int32 {
        return value.valueOf()
    }
    static SheetSize_FromNumeric(ordinal: int32): SheetSize {
        return SheetSize.fromValue(ordinal)
    }
    static SheetType_ToNumeric(value: SheetType): int32 {
        return value.valueOf()
    }
    static SheetType_FromNumeric(ordinal: int32): SheetType {
        return SheetType.fromValue(ordinal)
    }
    static SideBarContainerType_ToNumeric(value: SideBarContainerType): int32 {
        return value.valueOf()
    }
    static SideBarContainerType_FromNumeric(ordinal: int32): SideBarContainerType {
        return SideBarContainerType.fromValue(ordinal)
    }
    static SideBarPosition_ToNumeric(value: SideBarPosition): int32 {
        return value.valueOf()
    }
    static SideBarPosition_FromNumeric(ordinal: int32): SideBarPosition {
        return SideBarPosition.fromValue(ordinal)
    }
    static SlideEffect_ToNumeric(value: SlideEffect): int32 {
        return value.valueOf()
    }
    static SlideEffect_FromNumeric(ordinal: int32): SlideEffect {
        return SlideEffect.fromValue(ordinal)
    }
    static SliderBlockType_ToNumeric(value: SliderBlockType): int32 {
        return value.valueOf()
    }
    static SliderBlockType_FromNumeric(ordinal: int32): SliderBlockType {
        return SliderBlockType.fromValue(ordinal)
    }
    static SliderChangeMode_ToNumeric(value: SliderChangeMode): int32 {
        return value.valueOf()
    }
    static SliderChangeMode_FromNumeric(ordinal: int32): SliderChangeMode {
        return SliderChangeMode.fromValue(ordinal)
    }
    static SliderInteraction_ToNumeric(value: SliderInteraction): int32 {
        return value.valueOf()
    }
    static SliderInteraction_FromNumeric(ordinal: int32): SliderInteraction {
        return SliderInteraction.fromValue(ordinal)
    }
    static SliderStyle_ToNumeric(value: SliderStyle): int32 {
        return value.valueOf()
    }
    static SliderStyle_FromNumeric(ordinal: int32): SliderStyle {
        return SliderStyle.fromValue(ordinal)
    }
    static SourceTool_ToNumeric(value: SourceTool): int32 {
        return value.valueOf()
    }
    static SourceTool_FromNumeric(ordinal: int32): SourceTool {
        return SourceTool.fromValue(ordinal)
    }
    static SourceType_ToNumeric(value: SourceType): int32 {
        return value.valueOf()
    }
    static SourceType_FromNumeric(ordinal: int32): SourceType {
        return SourceType.fromValue(ordinal)
    }
    static SslError_ToNumeric(value: SslError): int32 {
        return value.valueOf()
    }
    static SslError_FromNumeric(ordinal: int32): SslError {
        return SslError.fromValue(ordinal)
    }
    static StickyStyle_ToNumeric(value: StickyStyle): int32 {
        return value.valueOf()
    }
    static StickyStyle_FromNumeric(ordinal: int32): StickyStyle {
        return StickyStyle.fromValue(ordinal)
    }
    static StyledStringKey_ToNumeric(value: StyledStringKey): int32 {
        return value.valueOf()
    }
    static StyledStringKey_FromNumeric(ordinal: int32): StyledStringKey {
        return StyledStringKey.fromValue(ordinal)
    }
    static SubMenuExpandingMode_ToNumeric(value: SubMenuExpandingMode): int32 {
        return value.valueOf()
    }
    static SubMenuExpandingMode_FromNumeric(ordinal: int32): SubMenuExpandingMode {
        return SubMenuExpandingMode.fromValue(ordinal)
    }
    static SwipeActionState_ToNumeric(value: SwipeActionState): int32 {
        return value.valueOf()
    }
    static SwipeActionState_FromNumeric(ordinal: int32): SwipeActionState {
        return SwipeActionState.fromValue(ordinal)
    }
    static SwipeDirection_ToNumeric(value: SwipeDirection): int32 {
        return value.valueOf()
    }
    static SwipeDirection_FromNumeric(ordinal: int32): SwipeDirection {
        return SwipeDirection.fromValue(ordinal)
    }
    static SwipeEdgeEffect_ToNumeric(value: SwipeEdgeEffect): int32 {
        return value.valueOf()
    }
    static SwipeEdgeEffect_FromNumeric(ordinal: int32): SwipeEdgeEffect {
        return SwipeEdgeEffect.fromValue(ordinal)
    }
    static SwiperAnimationMode_ToNumeric(value: SwiperAnimationMode): int32 {
        return value.valueOf()
    }
    static SwiperAnimationMode_FromNumeric(ordinal: int32): SwiperAnimationMode {
        return SwiperAnimationMode.fromValue(ordinal)
    }
    static SwiperDisplayMode_ToNumeric(value: SwiperDisplayMode): int32 {
        return value.valueOf()
    }
    static SwiperDisplayMode_FromNumeric(ordinal: int32): SwiperDisplayMode {
        return SwiperDisplayMode.fromValue(ordinal)
    }
    static SwiperNestedScrollMode_ToNumeric(value: SwiperNestedScrollMode): int32 {
        return value.valueOf()
    }
    static SwiperNestedScrollMode_FromNumeric(ordinal: int32): SwiperNestedScrollMode {
        return SwiperNestedScrollMode.fromValue(ordinal)
    }
    static SymbolEffectStrategy_ToNumeric(value: SymbolEffectStrategy): int32 {
        return value.valueOf()
    }
    static SymbolEffectStrategy_FromNumeric(ordinal: int32): SymbolEffectStrategy {
        return SymbolEffectStrategy.fromValue(ordinal)
    }
    static SymbolRenderingStrategy_ToNumeric(value: SymbolRenderingStrategy): int32 {
        return value.valueOf()
    }
    static SymbolRenderingStrategy_FromNumeric(ordinal: int32): SymbolRenderingStrategy {
        return SymbolRenderingStrategy.fromValue(ordinal)
    }
    static TabsCacheMode_ToNumeric(value: TabsCacheMode): int32 {
        return value.valueOf()
    }
    static TabsCacheMode_FromNumeric(ordinal: int32): TabsCacheMode {
        return TabsCacheMode.fromValue(ordinal)
    }
    static text_Affinity_ToNumeric(value: text.Affinity): int32 {
        return value.valueOf()
    }
    static text_Affinity_FromNumeric(ordinal: int32): text.Affinity {
        return text.Affinity.fromValue(ordinal)
    }
    static text_BreakStrategy_ToNumeric(value: text.BreakStrategy): int32 {
        return value.valueOf()
    }
    static text_BreakStrategy_FromNumeric(ordinal: int32): text.BreakStrategy {
        return text.BreakStrategy.fromValue(ordinal)
    }
    static text_EllipsisMode_ToNumeric(value: text.EllipsisMode): int32 {
        return value.valueOf()
    }
    static text_EllipsisMode_FromNumeric(ordinal: int32): text.EllipsisMode {
        return text.EllipsisMode.fromValue(ordinal)
    }
    static text_FontStyle_ToNumeric(value: text.FontStyle): int32 {
        return value.valueOf()
    }
    static text_FontStyle_FromNumeric(ordinal: int32): text.FontStyle {
        return text.FontStyle.fromValue(ordinal)
    }
    static text_FontWeight_ToNumeric(value: text.FontWeight): int32 {
        return value.valueOf()
    }
    static text_FontWeight_FromNumeric(ordinal: int32): text.FontWeight {
        return text.FontWeight.fromValue(ordinal)
    }
    static text_FontWidth_ToNumeric(value: text.FontWidth): int32 {
        return value.valueOf()
    }
    static text_FontWidth_FromNumeric(ordinal: int32): text.FontWidth {
        return text.FontWidth.fromValue(ordinal)
    }
    static text_PlaceholderAlignment_ToNumeric(value: text.PlaceholderAlignment): int32 {
        return value.valueOf()
    }
    static text_PlaceholderAlignment_FromNumeric(ordinal: int32): text.PlaceholderAlignment {
        return text.PlaceholderAlignment.fromValue(ordinal)
    }
    static text_RectHeightStyle_ToNumeric(value: text.RectHeightStyle): int32 {
        return value.valueOf()
    }
    static text_RectHeightStyle_FromNumeric(ordinal: int32): text.RectHeightStyle {
        return text.RectHeightStyle.fromValue(ordinal)
    }
    static text_RectWidthStyle_ToNumeric(value: text.RectWidthStyle): int32 {
        return value.valueOf()
    }
    static text_RectWidthStyle_FromNumeric(ordinal: int32): text.RectWidthStyle {
        return text.RectWidthStyle.fromValue(ordinal)
    }
    static text_SystemFontType_ToNumeric(value: text.SystemFontType): int32 {
        return value.valueOf()
    }
    static text_SystemFontType_FromNumeric(ordinal: int32): text.SystemFontType {
        return text.SystemFontType.fromValue(ordinal)
    }
    static text_TextAlign_ToNumeric(value: text.TextAlign): int32 {
        return value.valueOf()
    }
    static text_TextAlign_FromNumeric(ordinal: int32): text.TextAlign {
        return text.TextAlign.fromValue(ordinal)
    }
    static text_TextBaseline_ToNumeric(value: text.TextBaseline): int32 {
        return value.valueOf()
    }
    static text_TextBaseline_FromNumeric(ordinal: int32): text.TextBaseline {
        return text.TextBaseline.fromValue(ordinal)
    }
    static text_TextDecorationStyle_ToNumeric(value: text.TextDecorationStyle): int32 {
        return value.valueOf()
    }
    static text_TextDecorationStyle_FromNumeric(ordinal: int32): text.TextDecorationStyle {
        return text.TextDecorationStyle.fromValue(ordinal)
    }
    static text_TextDecorationType_ToNumeric(value: text.TextDecorationType): int32 {
        return value.valueOf()
    }
    static text_TextDecorationType_FromNumeric(ordinal: int32): text.TextDecorationType {
        return text.TextDecorationType.fromValue(ordinal)
    }
    static text_TextDirection_ToNumeric(value: text.TextDirection): int32 {
        return value.valueOf()
    }
    static text_TextDirection_FromNumeric(ordinal: int32): text.TextDirection {
        return text.TextDirection.fromValue(ordinal)
    }
    static text_TextHeightBehavior_ToNumeric(value: text.TextHeightBehavior): int32 {
        return value.valueOf()
    }
    static text_TextHeightBehavior_FromNumeric(ordinal: int32): text.TextHeightBehavior {
        return text.TextHeightBehavior.fromValue(ordinal)
    }
    static text_WordBreak_ToNumeric(value: text.WordBreak): int32 {
        return value.valueOf()
    }
    static text_WordBreak_FromNumeric(ordinal: int32): text.WordBreak {
        return text.WordBreak.fromValue(ordinal)
    }
    static TextAlign_ToNumeric(value: TextAlign): int32 {
        return value.valueOf()
    }
    static TextAlign_FromNumeric(ordinal: int32): TextAlign {
        return TextAlign.fromValue(ordinal)
    }
    static TextAreaType_ToNumeric(value: TextAreaType): int32 {
        return value.valueOf()
    }
    static TextAreaType_FromNumeric(ordinal: int32): TextAreaType {
        return TextAreaType.fromValue(ordinal)
    }
    static TextCase_ToNumeric(value: TextCase): int32 {
        return value.valueOf()
    }
    static TextCase_FromNumeric(ordinal: int32): TextCase {
        return TextCase.fromValue(ordinal)
    }
    static TextContentStyle_ToNumeric(value: TextContentStyle): int32 {
        return value.valueOf()
    }
    static TextContentStyle_FromNumeric(ordinal: int32): TextContentStyle {
        return TextContentStyle.fromValue(ordinal)
    }
    static TextDataDetectorType_ToNumeric(value: TextDataDetectorType): int32 {
        return value.valueOf()
    }
    static TextDataDetectorType_FromNumeric(ordinal: int32): TextDataDetectorType {
        return TextDataDetectorType.fromValue(ordinal)
    }
    static TextDecorationStyle_ToNumeric(value: TextDecorationStyle): int32 {
        return value.valueOf()
    }
    static TextDecorationStyle_FromNumeric(ordinal: int32): TextDecorationStyle {
        return TextDecorationStyle.fromValue(ordinal)
    }
    static TextDecorationType_ToNumeric(value: TextDecorationType): int32 {
        return value.valueOf()
    }
    static TextDecorationType_FromNumeric(ordinal: int32): TextDecorationType {
        return TextDecorationType.fromValue(ordinal)
    }
    static TextDeleteDirection_ToNumeric(value: TextDeleteDirection): int32 {
        return value.valueOf()
    }
    static TextDeleteDirection_FromNumeric(ordinal: int32): TextDeleteDirection {
        return TextDeleteDirection.fromValue(ordinal)
    }
    static TextHeightAdaptivePolicy_ToNumeric(value: TextHeightAdaptivePolicy): int32 {
        return value.valueOf()
    }
    static TextHeightAdaptivePolicy_FromNumeric(ordinal: int32): TextHeightAdaptivePolicy {
        return TextHeightAdaptivePolicy.fromValue(ordinal)
    }
    static TextInputStyle_ToNumeric(value: TextInputStyle): int32 {
        return value.valueOf()
    }
    static TextInputStyle_FromNumeric(ordinal: int32): TextInputStyle {
        return TextInputStyle.fromValue(ordinal)
    }
    static TextMenuShowMode_ToNumeric(value: TextMenuShowMode): int32 {
        return value.valueOf()
    }
    static TextMenuShowMode_FromNumeric(ordinal: int32): TextMenuShowMode {
        return TextMenuShowMode.fromValue(ordinal)
    }
    static TextOverflow_ToNumeric(value: TextOverflow): int32 {
        return value.valueOf()
    }
    static TextOverflow_FromNumeric(ordinal: int32): TextOverflow {
        return TextOverflow.fromValue(ordinal)
    }
    static TextResponseType_ToNumeric(value: TextResponseType): int32 {
        return value.valueOf()
    }
    static TextResponseType_FromNumeric(ordinal: int32): TextResponseType {
        return TextResponseType.fromValue(ordinal)
    }
    static TextSelectableMode_ToNumeric(value: TextSelectableMode): int32 {
        return value.valueOf()
    }
    static TextSelectableMode_FromNumeric(ordinal: int32): TextSelectableMode {
        return TextSelectableMode.fromValue(ordinal)
    }
    static TextSpanType_ToNumeric(value: TextSpanType): int32 {
        return value.valueOf()
    }
    static TextSpanType_FromNumeric(ordinal: int32): TextSpanType {
        return TextSpanType.fromValue(ordinal)
    }
    static ThemeColorMode_ToNumeric(value: ThemeColorMode): int32 {
        return value.valueOf()
    }
    static ThemeColorMode_FromNumeric(ordinal: int32): ThemeColorMode {
        return ThemeColorMode.fromValue(ordinal)
    }
    static ThreatType_ToNumeric(value: ThreatType): int32 {
        return value.valueOf()
    }
    static ThreatType_FromNumeric(ordinal: int32): ThreatType {
        return ThreatType.fromValue(ordinal)
    }
    static TimePickerFormat_ToNumeric(value: TimePickerFormat): int32 {
        return value.valueOf()
    }
    static TimePickerFormat_FromNumeric(ordinal: int32): TimePickerFormat {
        return TimePickerFormat.fromValue(ordinal)
    }
    static TitleHeight_ToNumeric(value: TitleHeight): int32 {
        return value.valueOf()
    }
    static TitleHeight_FromNumeric(ordinal: int32): TitleHeight {
        return TitleHeight.fromValue(ordinal)
    }
    static ToggleType_ToNumeric(value: ToggleType): int32 {
        return value.valueOf()
    }
    static ToggleType_FromNumeric(ordinal: int32): ToggleType {
        return ToggleType.fromValue(ordinal)
    }
    static ToolbarItemStatus_ToNumeric(value: ToolbarItemStatus): int32 {
        return value.valueOf()
    }
    static ToolbarItemStatus_FromNumeric(ordinal: int32): ToolbarItemStatus {
        return ToolbarItemStatus.fromValue(ordinal)
    }
    static TouchTestStrategy_ToNumeric(value: TouchTestStrategy): int32 {
        return value.valueOf()
    }
    static TouchTestStrategy_FromNumeric(ordinal: int32): TouchTestStrategy {
        return TouchTestStrategy.fromValue(ordinal)
    }
    static TouchType_ToNumeric(value: TouchType): int32 {
        return value.valueOf()
    }
    static TouchType_FromNumeric(ordinal: int32): TouchType {
        return TouchType.fromValue(ordinal)
    }
    static TransitionEdge_ToNumeric(value: TransitionEdge): int32 {
        return value.valueOf()
    }
    static TransitionEdge_FromNumeric(ordinal: int32): TransitionEdge {
        return TransitionEdge.fromValue(ordinal)
    }
    static TransitionHierarchyStrategy_ToNumeric(value: TransitionHierarchyStrategy): int32 {
        return value.valueOf()
    }
    static TransitionHierarchyStrategy_FromNumeric(ordinal: int32): TransitionHierarchyStrategy {
        return TransitionHierarchyStrategy.fromValue(ordinal)
    }
    static TransitionType_ToNumeric(value: TransitionType): int32 {
        return value.valueOf()
    }
    static TransitionType_FromNumeric(ordinal: int32): TransitionType {
        return TransitionType.fromValue(ordinal)
    }
    static uniformTypeDescriptor_UniformDataType_ToNumeric(value: uniformTypeDescriptor.UniformDataType): int32 {
        return value.getOrdinal()
    }
    static uniformTypeDescriptor_UniformDataType_FromNumeric(ordinal: int32): uniformTypeDescriptor.UniformDataType {
        return uniformTypeDescriptor.UniformDataType.values()[ordinal]
    }
    static VerticalAlign_ToNumeric(value: VerticalAlign): int32 {
        return value.valueOf()
    }
    static VerticalAlign_FromNumeric(ordinal: int32): VerticalAlign {
        return VerticalAlign.fromValue(ordinal)
    }
    static ViewportFit_ToNumeric(value: ViewportFit): int32 {
        return value.valueOf()
    }
    static ViewportFit_FromNumeric(ordinal: int32): ViewportFit {
        return ViewportFit.fromValue(ordinal)
    }
    static Visibility_ToNumeric(value: Visibility): int32 {
        return value.valueOf()
    }
    static Visibility_FromNumeric(ordinal: int32): Visibility {
        return Visibility.fromValue(ordinal)
    }
    static WaterFlowLayoutMode_ToNumeric(value: WaterFlowLayoutMode): int32 {
        return value.valueOf()
    }
    static WaterFlowLayoutMode_FromNumeric(ordinal: int32): WaterFlowLayoutMode {
        return WaterFlowLayoutMode.fromValue(ordinal)
    }
    static WebCaptureMode_ToNumeric(value: WebCaptureMode): int32 {
        return value.valueOf()
    }
    static WebCaptureMode_FromNumeric(ordinal: int32): WebCaptureMode {
        return WebCaptureMode.fromValue(ordinal)
    }
    static WebDarkMode_ToNumeric(value: WebDarkMode): int32 {
        return value.valueOf()
    }
    static WebDarkMode_FromNumeric(ordinal: int32): WebDarkMode {
        return WebDarkMode.fromValue(ordinal)
    }
    static WebElementType_ToNumeric(value: WebElementType): int32 {
        return value.valueOf()
    }
    static WebElementType_FromNumeric(ordinal: int32): WebElementType {
        return WebElementType.fromValue(ordinal)
    }
    static WebKeyboardAvoidMode_ToNumeric(value: WebKeyboardAvoidMode): int32 {
        return value.valueOf()
    }
    static WebKeyboardAvoidMode_FromNumeric(ordinal: int32): WebKeyboardAvoidMode {
        return WebKeyboardAvoidMode.fromValue(ordinal)
    }
    static WebLayoutMode_ToNumeric(value: WebLayoutMode): int32 {
        return value.valueOf()
    }
    static WebLayoutMode_FromNumeric(ordinal: int32): WebLayoutMode {
        return WebLayoutMode.fromValue(ordinal)
    }
    static WebNavigationType_ToNumeric(value: WebNavigationType): int32 {
        return value.valueOf()
    }
    static WebNavigationType_FromNumeric(ordinal: int32): WebNavigationType {
        return WebNavigationType.fromValue(ordinal)
    }
    static WebResponseType_ToNumeric(value: WebResponseType): int32 {
        return value.valueOf()
    }
    static WebResponseType_FromNumeric(ordinal: int32): WebResponseType {
        return WebResponseType.fromValue(ordinal)
    }
    static Week_ToNumeric(value: Week): int32 {
        return value.valueOf()
    }
    static Week_FromNumeric(ordinal: int32): Week {
        return Week.fromValue(ordinal)
    }
    static WidthBreakpoint_ToNumeric(value: WidthBreakpoint): int32 {
        return value.valueOf()
    }
    static WidthBreakpoint_FromNumeric(ordinal: int32): WidthBreakpoint {
        return WidthBreakpoint.fromValue(ordinal)
    }
    static window_WindowStatusType_ToNumeric(value: window.WindowStatusType): int32 {
        return value.valueOf()
    }
    static window_WindowStatusType_FromNumeric(ordinal: int32): window.WindowStatusType {
        return window.WindowStatusType.fromValue(ordinal)
    }
    static WindowModeFollowStrategy_ToNumeric(value: WindowModeFollowStrategy): int32 {
        return value.valueOf()
    }
    static WindowModeFollowStrategy_FromNumeric(ordinal: int32): WindowModeFollowStrategy {
        return WindowModeFollowStrategy.fromValue(ordinal)
    }
    static WordBreak_ToNumeric(value: WordBreak): int32 {
        return value.valueOf()
    }
    static WordBreak_FromNumeric(ordinal: int32): WordBreak {
        return WordBreak.fromValue(ordinal)
    }
    static XComponentType_ToNumeric(value: XComponentType): int32 {
        return value.valueOf()
    }
    static XComponentType_FromNumeric(ordinal: int32): XComponentType {
        return XComponentType.fromValue(ordinal)
    }
    static isArray_Number(value: Object | string | number | undefined): boolean {
        return value instanceof Array
    }
    static isArray_common2D_Point(value: Object | string | number | undefined): boolean {
        return value instanceof Array
    }
    static isArray_common2D_Rect(value: Object | string | number | undefined): boolean {
        return value instanceof Array
    }
    static isArray_drawing_RectType(value: Object | string | number | undefined): boolean {
        return value instanceof Array
    }
    static isArray_CustomObject(value: Object | string | number | undefined): boolean {
        return value instanceof Array
    }
    static isArray_drawing_TextBlobRunBuffer(value: Object | string | number | undefined): boolean {
        return value instanceof Array
    }
    static isArray_String(value: Object | string | number | undefined): boolean {
        return value instanceof Array
    }
    static isArray_SourceTool(value: Object | string | number | undefined): boolean {
        return value instanceof Array
    }
    static isArray_GestureType(value: Object | string | number | undefined): boolean {
        return value instanceof Array
    }
    static isArray_ImageAnalyzerType(value: Object | string | number | undefined): boolean {
        return value instanceof Array
    }
    static isArray_Layoutable(value: Object | string | number | undefined): boolean {
        return value instanceof Array
    }
    static isArray_Measurable(value: Object | string | number | undefined): boolean {
        return value instanceof Array
    }
    static isArray_ColorStop(value: Object | string | number | undefined): boolean {
        return value instanceof Array
    }
    static isArray_Opt_Object(value: Object | string | number | undefined): boolean {
        return value instanceof Array
    }
    static isArray_NavPathInfo(value: Object | string | number | undefined): boolean {
        return value instanceof Array
    }
    static isArray_Union_Number_String(value: Object | string | number | undefined): boolean {
        return value instanceof Array
    }
    static isArray_Union_RichEditorImageSpanResult_RichEditorTextSpanResult(value: Object | string | number | undefined): boolean {
        return value instanceof Array
    }
    static isArray_RichEditorParagraphResult(value: Object | string | number | undefined): boolean {
        return value instanceof Array
    }
    static isArray_RichEditorSpan(value: Object | string | number | undefined): boolean {
        return value instanceof Array
    }
    static isArray_StyleOptions(value: Object | string | number | undefined): boolean {
        return value instanceof Array
    }
    static isArray_SpanStyle(value: Object | string | number | undefined): boolean {
        return value instanceof Array
    }
    static isArray_text_TextBox(value: Object | string | number | undefined): boolean {
        return value instanceof Array
    }
    static isArray_text_TextLine(value: Object | string | number | undefined): boolean {
        return value instanceof Array
    }
    static isArray_text_LineMetrics(value: Object | string | number | undefined): boolean {
        return value instanceof Array
    }
    static isArray_text_Run(value: Object | string | number | undefined): boolean {
        return value instanceof Array
    }
    static isArray_SectionOptions(value: Object | string | number | undefined): boolean {
        return value instanceof Array
    }
    static isArray_Header(value: Object | string | number | undefined): boolean {
        return value instanceof Array
    }
    static isArray_webview_WebHeader(value: Object | string | number | undefined): boolean {
        return value instanceof Array
    }
    static isArray_TextMenuItem(value: Object | string | number | undefined): boolean {
        return value instanceof Array
    }
    static isArray_TouchTestInfo(value: Object | string | number | undefined): boolean {
        return value instanceof Array
    }
    static isArray_NavDestinationTransition(value: Object | string | number | undefined): boolean {
        return value instanceof Array
    }
    static isArray_ResourceStr(value: Object | string | number | undefined): boolean {
        return value instanceof Array
    }
    static isArray_GestureRecognizer(value: Object | string | number | undefined): boolean {
        return value instanceof Array
    }
    static isArray_font_UIFontGenericInfo(value: Object | string | number | undefined): boolean {
        return value instanceof Array
    }
    static isArray_font_UIFontFallbackGroupInfo(value: Object | string | number | undefined): boolean {
        return value instanceof Array
    }
    static isArray_font_UIFontFallbackInfo(value: Object | string | number | undefined): boolean {
        return value instanceof Array
    }
    static isArray_font_UIFontAliasInfo(value: Object | string | number | undefined): boolean {
        return value instanceof Array
    }
    static isArray_font_UIFontAdjustInfo(value: Object | string | number | undefined): boolean {
        return value instanceof Array
    }
    static isArray_FractionStop(value: Object | string | number | undefined): boolean {
        return value instanceof Array
    }
    static isArray_Tuple_ResourceColor_Number(value: Object | string | number | undefined): boolean {
        return value instanceof Array
    }
    static isArray_Buffer(value: Object | string | number | undefined): boolean {
        return value instanceof Array
    }
    static isArray_Object(value: Object | string | number | undefined): boolean {
        return value instanceof Array
    }
    static isArray_Union_RichEditorTextSpanResult_RichEditorImageSpanResult(value: Object | string | number | undefined): boolean {
        return value instanceof Array
    }
    static isArray_ShadowOptions(value: Object | string | number | undefined): boolean {
        return value instanceof Array
    }
    static isArray_DateRange(value: Object | string | number | undefined): boolean {
        return value instanceof Array
    }
    static isArray_Union_ResourceColor_LinearGradient(value: Object | string | number | undefined): boolean {
        return value instanceof Array
    }
    static isArray_DragPreviewMode(value: Object | string | number | undefined): boolean {
        return value instanceof Array
    }
    static isArray_RichEditorTextSpanResult(value: Object | string | number | undefined): boolean {
        return value instanceof Array
    }
    static isArray_RichEditorImageSpanResult(value: Object | string | number | undefined): boolean {
        return value instanceof Array
    }
    static isArray_ResourceColor(value: Object | string | number | undefined): boolean {
        return value instanceof Array
    }
    static isArray_TextCascadePickerRangeContent(value: Object | string | number | undefined): boolean {
        return value instanceof Array
    }
    static isArray_Array_String(value: Object | string | number | undefined): boolean {
        return value instanceof Array
    }
    static isArray_TextPickerRangeContent(value: Object | string | number | undefined): boolean {
        return value instanceof Array
    }
    static isArray_LengthMetrics(value: Object | string | number | undefined): boolean {
        return value instanceof Array
    }
    static isArray_RadiusItem(value: Object | string | number | undefined): boolean {
        return value instanceof Array
    }
    static isArray_Dimension(value: Object | string | number | undefined): boolean {
        return value instanceof Array
    }
    static isArray_text_FontFeature(value: Object | string | number | undefined): boolean {
        return value instanceof Array
    }
    static isArray_text_TextShadow(value: Object | string | number | undefined): boolean {
        return value instanceof Array
    }
    static isArray_text_FontVariation(value: Object | string | number | undefined): boolean {
        return value instanceof Array
    }
    static isArray_TextDataDetectorType(value: Object | string | number | undefined): boolean {
        return value instanceof Array
    }
    static isArray_FingerInfo(value: Object | string | number | undefined): boolean {
        return value instanceof Array
    }
    static isArray_MouseButton(value: Object | string | number | undefined): boolean {
        return value instanceof Array
    }
    static isArray_TouchObject(value: Object | string | number | undefined): boolean {
        return value instanceof Array
    }
    static isArray_HistoricalPoint(value: Object | string | number | undefined): boolean {
        return value instanceof Array
    }
    static isArray_text_FontDescriptor(value: Object | string | number | undefined): boolean {
        return value instanceof Array
    }
    static isArray_SheetInfo(value: Object | string | number | undefined): boolean {
        return value instanceof Array
    }
    static isArray_AlertDialogButtonOptions(value: Object | string | number | undefined): boolean {
        return value instanceof Array
    }
    static isArray_Rectangle(value: Object | string | number | undefined): boolean {
        return value instanceof Array
    }
    static isArray_uniformTypeDescriptor_UniformDataType(value: Object | string | number | undefined): boolean {
        return value instanceof Array
    }
    static isArray_ObscuredReasons(value: Object | string | number | undefined): boolean {
        return value instanceof Array
    }
    static isArray_SafeAreaType(value: Object | string | number | undefined): boolean {
        return value instanceof Array
    }
    static isArray_SafeAreaEdge(value: Object | string | number | undefined): boolean {
        return value instanceof Array
    }
    static isArray_MenuElement(value: Object | string | number | undefined): boolean {
        return value instanceof Array
    }
    static isArray_ModifierKey(value: Object | string | number | undefined): boolean {
        return value instanceof Array
    }
    static isArray_Length(value: Object | string | number | undefined): boolean {
        return value instanceof Array
    }
    static isArray_Tuple_Union_ResourceColor_LinearGradient_Number(value: Object | string | number | undefined): boolean {
        return value instanceof Array
    }
    static isArray_ImageFrameInfo(value: Object | string | number | undefined): boolean {
        return value instanceof Array
    }
    static isArray_NavigationMenuItem(value: Object | string | number | undefined): boolean {
        return value instanceof Array
    }
    static isArray_Scroller(value: Object | string | number | undefined): boolean {
        return value instanceof Array
    }
    static isArray_NestedScrollInfo(value: Object | string | number | undefined): boolean {
        return value instanceof Array
    }
    static isArray_ToolbarItem(value: Object | string | number | undefined): boolean {
        return value instanceof Array
    }
    static isArray_LayoutSafeAreaType(value: Object | string | number | undefined): boolean {
        return value instanceof Array
    }
    static isArray_LayoutSafeAreaEdge(value: Object | string | number | undefined): boolean {
        return value instanceof Array
    }
    static isArray_ParticlePropertyAnimation<number>(value: Object | string | number | undefined): boolean {
        return value instanceof Array
    }
    static isArray_ShapePoint(value: Object | string | number | undefined): boolean {
        return value instanceof Array
    }
    static isArray_GuideLineStyle(value: Object | string | number | undefined): boolean {
        return value instanceof Array
    }
    static isArray_BarrierStyle(value: Object | string | number | undefined): boolean {
        return value instanceof Array
    }
    static isArray_ScriptItem(value: Object | string | number | undefined): boolean {
        return value instanceof Array
    }
}
