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
import { AccessibilityHoverType, Alignment, AnimationStatus, AppRotation, ArrowPointPosition, Axis, AxisAction, AxisModel, BarState, BorderStyle, CheckBoxShape, Color, ClickEffectLevel, ColoringStrategy, CopyOptions, CrownAction, CrownSensitivity, Curve, DialogButtonStyle, Direction, DividerMode, Edge, EdgeEffect, EllipsisMode, EmbeddedType, FillMode, FlexAlign, FlexDirection, FlexWrap, FocusDrawLevel, FoldStatus, FontStyle, FontWeight, FunctionKey, GradientDirection, HeightBreakpoint, HitTestMode, HorizontalAlign, HoverEffect, IlluminatedType, ImageFit, ImageRepeat, ImageSize, ImageSpanAlignment, InteractionHand, ItemAlign, KeySource, KeyType, LineBreakStrategy, LineCapStyle, LineJoinStyle, MarqueeUpdateStrategy, ModifierKey, MouseAction, MouseButton, NestedScrollMode, ObscuredReasons, OptionWidthMode, PageFlipMode, PixelRoundCalcPolicy, PixelRoundMode, Placement, PlayMode, RelateType, RenderFit, ResponseType, ScrollSource, SharedTransitionEffectType, TextAlign, TextCase, TextContentStyle, TextDecorationStyle, TextDecorationType, TextHeightAdaptivePolicy, TextOverflow, TextSelectableMode, TitleHeight, TouchType, TransitionType, WidthBreakpoint, VerticalAlign, Visibility, Week, WordBreak, XComponentType } from "./../../component/enums"
import { AccessibilityRoleType, AccessibilitySamePageMode, AdaptiveColor, BlendApplyType, BlendMode, BlurStyle, BlurStyleActivePolicy, TouchEvent, ChainStyle, ContentClipMode, DismissReason, DragBehavior, DraggingSizeChangeEffect, DragPreviewMode, DragResult, EffectEdge, EffectType, FinishCallbackType, SourceTool, GestureModifier, UIGestureEvent, HapticFeedbackMode, HoverModeAreaType, ICurve, KeyboardAvoidMode, Layoutable, Measurable, GeometryInfo, SizeResult, LayoutPolicy, LayoutSafeAreaEdge, LayoutSafeAreaType, RectResult, CommonConfiguration, TranslateOptions, ScaleOptions, RotateOptions, MenuPolicy, MenuPreviewMode, ModalTransition, NestedScrollOptions, OutlineStyle, PixelMapMock, PopupStateChangeParam, PreDragStatus, ProgressMask, PopupCommonOptions, MenuOptions, RepeatMode, SelectionOptions, SafeAreaEdge, SafeAreaType, ScrollResult, ScrollSizeMode, TextContentControllerBase, ShadowStyle, ShadowType, SheetKeyboardAvoidMode, SheetMode, SheetSize, SheetType, SourceType, CaretOffset, TextContentControllerOptions, ThemeColorMode, TouchTestInfo, TouchTestStrategy, TransitionEdge, TransitionEffect, AsymmetricTransitionOption, AnimateParam, TransitionHierarchyStrategy, UICommonEvent, ClickEvent, KeyEvent, HoverCallback, HoverEvent, MouseEvent, SizeChangeCallback, VisibleAreaEventOptions, VisibleAreaChangeCallback, SheetOptions, AlignRuleOption, BackgroundBrightnessOptions, BackgroundImageOptions, BackgroundOptions, BlurOptions, ChildrenMainSize, ClickEffect, CrownEvent, DateRange, DismissContentCoverAction, DismissPopupAction, DismissSheetAction, DragEvent, ModifierKeyStateGetter, Rectangle, DataSyncOptions, DragInteractionOptions, DragItemInfo, DrawModifier, DropOptions, EdgeEffectOptions, ExpectedFrameRateRange, FocusMovement, ForegroundEffectOptions, GeometryTransitionOptions, InputCounterOptions, InvertOptions, ItemDragInfo, FractionStop, LinearGradientBlurOptions, LinearGradientOptions, LocalizedHorizontalAlignParam, LocalizedVerticalAlignParam, MeasureResult, MotionBlurAnchor, MotionBlurOptions, MotionPathOptions, OverlayOffset, PixelRoundPolicy, PopupButton, PreviewConfiguration, SheetDismiss, SpringBackAction, StateStyles, CustomStyles, SystemAdaptiveOptions, ShadowOptions, TouchObject, TouchResult, BackgroundBlurStyleOptions, BlurStyleOptions, BackgroundEffectOptions, ContentCoverOptions, BindOptions, ContextMenuAnimationOptions, AnimationNumberRange, MultiShadowOptions, DragPreviewOptions, FadingEdgeOptions, ForegroundBlurStyleOptions, HistoricalPoint, LightSource, LocalizedAlignRuleOptions, MenuElement, OverlayOptions, PopupMaskType, ReuseOptions, ReuseIdCallback, sharedTransitionOptions, SheetTitleOptions, TerminationInfo, TextDecorationOptions, DividerStyle, PixelStretchEffectOptions, PointLightStyle, RadialGradientOptions, SweepGradientOptions, TipsOptions, BorderImageOption, ContextMenuOptions, BorderRadiusType, CustomPopupOptions, PopupStateChangeCallback, EventTarget, FocusAxisEvent, BaseEvent, LayoutChild, PickerDialogButtonStyle, PickerTextStyle, PopupMessageOptions, TripleLengthDetents, AccessibilityHoverEvent, AxisEvent, PopupOptions } from "./../../component/common"
import { AnimationMode, BarMode, BarPosition, LayoutStyle, TabContentTransitionProxy, TabsAnimationEvent, TabsCacheMode, TabsController, TabContentAnimatedTransition, TabsOptions, BarGridColumnOptions, ScrollableBarModeOptions } from "./../../component/tabs"
import { ArrowPosition, AvoidanceMode, MenuAlignType, MenuItemConfiguration, SelectOption, MenuOutlineOptions } from "./../../component/select"
import { AutoCapitalizationMode, KeyboardAppearance, LayoutManager, PositionWithAffinity, MenuType, TextEditControllerEx, PreviewText, StyledStringController, StyledStringChangedListener, TextBaseController, TextRange, TextDataDetectorType, TextDeleteDirection, TextMenuOptions, TextMenuItemId, TextMenuShowMode, TextMenuItem, DeleteValue, EditMenuOptions, OnCreateMenuCallback, OnMenuItemClickCallback, FontSettingOptions, InsertValue, StyledStringChangeValue, OnDidChangeCallback, DecorationStyleResult, TextChangeOptions, CaretStyle, EditableTextChangeValue, TextDataDetectorConfig } from "./../../component/textCommon"
import { BadgePosition, BadgeStyle, BadgeParamWithNumber, BadgeParam, BadgeParamWithString } from "./../../component/badge"
import { BarrierDirection, LocalizedBarrierDirection, BarrierStyle, GuideLinePosition, GuideLineStyle } from "./../../component/relativeContainer"
import { BarStyle, LaunchMode, NavBarPosition, NavigationMode, NavigationOperation, NavigationTitleMode, NavPathInfo, NavPathStack, NavigationOptions, PopInfo, NavigationInterception, ToolbarItemStatus, NavContentInfo, NavigationAnimatedTransition, NavigationTransitionProxy, InterceptionShowCallback, NavBar, InterceptionModeCallback, NavigationCommonTitle, NavigationMenuItem, UpdateTransitionCallback, ToolbarItem, MoreButtonOptions, NavigationCustomTitle, NavigationTitleOptions, NavigationMenuOptions, NavigationToolbarOptions } from "./../../component/navigation"
import { BaseContext } from "./../application.BaseContext"
import { BaseCustomComponent, ContentModifier, CustomComponentV2 } from "./../../handwritten"
import { ExtendableComponent, LifeCycle } from "./../../component/extendableComponent"
import { BaseShape, BuilderNodeOps, BuilderNodeOptions, CommonShape, Offset_componentutils, PerfMonitorActionType, PerfMonitorSourceType, RotateResult, ScaleResult, Scene, TranslateResult, WorkerEventListener, Event, DoubleAnimationParam, Callback_Extender_OnProgress, Callback_Extender_OnFinish, ErrorEvent, FontInfo, MessageEvents, PostMessageOptions, SnapshotOptions, WorkerOptions, ComponentInfo, Matrix4Result, FontOptions, MeasureOptions, RestrictedWorker, RestrictedWorker_onexit_Callback, RestrictedWorker_onerror_Callback, RestrictedWorker_onmessage_Callback } from "./../../component/idlize"
import { Length, SizeOptions, Position, ResourceColor, ColorFilter, ConstraintSizeOptions, ResourceStr, VoidCallback, AccessibilityOptions, Bias, ChainWeightOptions, DirectionalEdgesT, EdgeOutlineStyles, EdgeStyles, VP, DividerStyleOptions, EdgeColors, LengthConstrain, Dimension, LocalizedBorderRadiuses, LocalizedEdgeColors, LocalizedEdges, LocalizedEdgeWidths, LocalizedPadding, LocalizedPosition, Offset, BorderRadiuses, EdgeOutlineWidths, Edges, EdgeWidths, Font, PX, LPX, MarkStyle, OutlineRadiuses, Padding, Area, BorderOptions, OutlineOptions } from "./../../component/units"
import { Resource } from "./../resource"
import { BlurOnKeyboardHideMode, CacheMode, ClientAuthenticationHandler, ConsoleMessage, MessageLevel, ContextMenuEditStateFlags, ContextMenuInputFieldType, ContextMenuMediaType, ContextMenuSourceType, ControllerHandler, DataResubmissionHandler, EventResult, FileSelectorMode, FileSelectorParam, FileSelectorResult, FullScreenExitHandler, HitTestType, HttpAuthHandler, JsGeolocation, JsResult, MixedMode, NativeEmbedStatus, NativeMediaPlayerConfig, OnAudioStateChangedEvent, OnConsoleEvent, OnDataResubmittedEvent, OnFaviconReceivedEvent, OnFirstContentfulPaintEvent, OnOverScrollEvent, OnProgressChangeEvent, OnScaleChangeEvent, OnScrollEvent, OnSearchResultReceiveEvent, OnShowFileSelectorEvent, OverScrollMode, PermissionRequest, ProtectedResourceType, RenderExitReason, RenderMode, RenderProcessNotRespondingReason, ScreenCaptureHandler, ScreenCaptureConfig, SslError, SslErrorHandler, ThreatType, ViewportFit, WebCaptureMode, WebContextMenuParam, WebContextMenuResult, WebCookie, WebDarkMode, WebElementType, WebKeyboardAvoidMode, WebKeyboardController, WebLayoutMode, WebNavigationType, WebResourceError, Header, WebResourceRequest, WebResourceResponse, WebResponseType, AdsBlockedDetails, EmbedOptions, FirstMeaningfulPaint, FullScreenEnterEvent, IntelligentTrackingPreventionDetails, JavaScriptProxy, LargestContentfulPaint, LoadCommittedDetails, NativeEmbedVisibilityInfo, NestedScrollOptionsExt, OnAlertEvent, OnBeforeUnloadEvent, OnClientAuthenticationEvent, OnConfirmEvent, OnContextMenuShowEvent, OnDownloadStartEvent, OnErrorReceiveEvent, OnGeolocationShowEvent, OnHttpAuthRequestEvent, OnHttpErrorReceiveEvent, OnInterceptRequestEvent, OnLoadInterceptEvent, OnPageBeginEvent, OnPageEndEvent, OnPageVisibleEvent, OnPermissionRequestEvent, OnPromptEvent, OnRefreshAccessedHistoryEvent, OnRenderExitedEvent, OnResourceLoadEvent, OnScreenCaptureRequestEvent, OnSslErrorEventReceiveEvent, OnTitleReceiveEvent, OnTouchIconUrlReceivedEvent, OnWindowNewEvent, RenderProcessNotRespondingData, ScriptItem, SelectionMenuOptionsExt, SslErrorEvent, WebKeyboardCallbackInfo, WebKeyboardOptions, WebMediaOptions, WebOptions, NativeEmbedInfo, NativeEmbedDataInfo, NativeEmbedTouchInfo } from "./../../component/web"
import { BreakpointsReference, GridRowDirection, BreakPoints, GridRowColumnOption, GridRowSizeOption, GutterOption, GridRowOptions } from "./../../component/gridRow"
import { ButtonRole, ButtonStyleMode, ButtonType, ControlSize, ButtonConfiguration, ButtonTriggerClickCallback, ButtonOptions, ButtonLabelStyle } from "./../../component/button"
import { CalendarAlign, CalendarPickerDialog, CalendarDialogOptions, CalendarOptions } from "./../../component/calendarPicker"
import { CalendarController, CalendarSelectedDate, CalendarDay, CalendarRequestedData, MonthData, CalendarRequestedMonths, CurrentDayStyle, NonCurrentDayStyle, TodayStyle, WeekStyle, WorkStateStyle } from "./../../component/calendar"
import { CancelButtonStyle, SearchController, SearchType, CancelButtonSymbolOptions, SearchOptions, IconOptions, SearchButtonOptions, CancelButtonOptions } from "./../../component/search"
import { CanvasGradient, CanvasPath, CanvasPattern, OffscreenCanvas, ImageBitmap, RenderingContextSettings, OffscreenCanvasRenderingContext2D, Path2D, TextMetrics, DrawingRenderingContext, ImageData, CanvasRenderer, ImageSmoothingQuality, CanvasLineCap, CanvasLineJoin, CanvasDirection, CanvasTextAlign, CanvasTextBaseline, CanvasFillRule, CanvasRenderingContext2D } from "./../../component/canvas"
import { Matrix2D } from "./../../component/matrix2d"
import { ChainEdgeEffect, ListItemAlign, ListItemGroupArea, ListScroller, CloseSwipeActionOptions, VisibleListContentInfo, ScrollSnapAlign, ScrollState, StickyStyle, ListOptions, ChainAnimationOptions, ListDividerOptions } from "./../../component/list"
import { CircleShape, ShapeSize, EllipseShape, PathShape, PathShapeOptions, RectShape, RectShapeOptions, RoundRectShapeOptions } from "./../ohos.arkui.shape"
import { ColorContent, DynamicRangeMode, ImageContent, ImageInterpolation, ImageRenderMode, ImageRotateOrientation, ImageCompleteEvent, ImageSourceSize, ImageError, ResizableOptions } from "./../../component/image"
import { ColorMetrics, CornerRadius, DrawContext, Size, LengthMetricsUnit, LengthUnit, ShapeClip, RoundRect, Circle, CommandPath, ShapeMask, Vector2, Vector3, LengthMetrics, Frame } from "./../arkui.Graphics"
import { ColorMode, LayoutDirection } from "./../../component/stateManagement"
import { CommonModifier } from "./../arkui.CommonModifier"
import { ComponentContent } from "./../arkui.ComponentContent"
import { ContentType, EnterKeyType, InputType, SubmitEvent, TextInputController, TextInputStyle, PasswordIcon, TextInputOptions, UnderlineColor } from "./../../component/textInput"
import { Context } from "./../application.Context"
import { webview } from "./../ohos.web.webview"
import { CustomDialogController, CustomDialogControllerOptions } from "./../../component/customDialogController"
import { DataOperationType } from "./../../component/lazyForEach"
import { DataPanelType, ColorStop, LinearGradient, DataPanelConfiguration, DataPanelOptions, DataPanelShadowOptions } from "./../../component/dataPanel"
import { DatePickerDialog, DatePickerMode, DatePickerOptions } from "./../../component/datePicker"
import { DialogAlignment, DialogButtonDirection, DismissDialogAction, AlertDialogButtonOptions } from "./../../component/alertDialog"
import { DistributionType, DisturbanceFieldShape, ParticleEmitterShape, ParticleType, ParticleUpdater, ParticlePropertyAnimation } from "./../../component/particle"
import { DpiFollowStrategy, UIExtensionProxy, WindowModeFollowStrategy, UIExtensionOptions } from "./../../component/uiExtensionComponent"
import { DrawableDescriptor } from "./../ohos.arkui.drawableDescriptor"
import { image } from "./../ohos.multimedia.image"
import { drawing } from "./../ohos.graphics.drawing"
import { common2D } from "./../ohos.graphics.common2D"
import { EffectDirection, EffectFillStyle, EffectScope, PulseSymbolEffect, SymbolEffect, SymbolEffectStrategy, SymbolRenderingStrategy, AppearSymbolEffect, BounceSymbolEffect, DisappearSymbolEffect, HierarchicalSymbolEffect, ReplaceSymbolEffect, ScaleSymbolEffect } from "./../../component/symbolglyph"
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
import { LayoutCallback, PageLifeCycle } from "./../../component/customComponent"
import { LayoutMode, SelectedMode, TabBarSymbol, TabBarIconStyle, TabBarOptions, BoardStyle, SubTabBarIndicatorStyle, TabBarLabelStyle, BottomTabBarStyle, SubTabBarStyle } from "./../../component/tabContent"
import { LinearIndicatorController, LinearIndicatorStartOptions, LinearIndicatorStyle } from "./../../component/linearindicator"
import { ListItemGroupStyle, ListItemGroupOptions } from "./../../component/listItemGroup"
import { ListItemStyle, SwipeActionState, SwipeEdgeEffect, ListItemOptions, SwipeActionItem, SwipeActionOptions } from "./../../component/listItem"
import { Scroller, ScrollAlign, OffsetResult, OnScrollFrameBeginHandlerResult, ScrollDirection, ScrollOptions, ScrollEdgeOptions, ScrollPageOptions, ScrollToIndexOptions, ScrollAnimationOptions, OffsetOptions, ScrollSnapOptions } from "./../../component/scroll"
import { LoadingProgressConfiguration, LoadingProgressStyle } from "./../../component/loadingProgress"
import { MarqueeStartPolicy, MarqueeState, TextController, TextOptions, TextOverflowOptions, TextResponseType, TextSpanType, TextMarqueeOptions } from "./../../component/text"
import { matrix4 } from "./../ohos.matrix4"
import { NavDestinationActiveReason, NavDestinationMode, NavigationSystemTransitionType, NavDestinationTransition, NavDestinationContext, NestedScrollInfo, RouteMapConfig, NavDestinationCommonTitle, NavDestinationCustomTitle } from "./../../component/navDestination"
import { NavigationType } from "./../../component/navigator"
import { NodeContent } from "./../arkui.nodecontent"
import { Content } from "./../ohos.arkui.node"
import { NodeController } from "./../arkui.NodeController"
import { OnFoldStatusChangeInfo, FolderStackOptions, HoverEventParam } from "./../../component/folderStack"
import { PasteButtonOnClickResult, PasteDescription, PasteIconStyle, PasteButtonOptions } from "./../../component/pasteButton"
import { PatternLockChallengeResult, PatternLockController, CircleStyleOptions } from "./../../component/patternLock"
import { pointer } from "./../ohos.multimodalInput.pointer"
import { ProgressConfiguration, ProgressStatus, ProgressStyle, ProgressType, ProgressOptions, LinearStyleOptions, ScanEffectOptions, CommonProgressStyleOptions, ProgressStyleOptions, RingStyleOptions, CapsuleStyleOptions } from "./../../component/progress"
import { RadioIndicatorType, RadioConfiguration, RadioOptions, RadioStyle } from "./../../component/radio"
import { RefreshStatus, RefreshOptions } from "./../../component/refresh"
import { RichEditorBaseController, RichEditorTextStyle, RichEditorParagraphResult, RichEditorSpan, RichEditorController, RichEditorTextSpanOptions, RichEditorImageSpanOptions, RichEditorBuilderSpanOptions, RichEditorSymbolSpanOptions, RichEditorUpdateTextSpanStyleOptions, RichEditorUpdateImageSpanStyleOptions, RichEditorUpdateSymbolSpanStyleOptions, RichEditorParagraphStyleOptions, RichEditorRange, RichEditorImageSpanResult, RichEditorTextSpanResult, RichEditorSelection, RichEditorDeleteDirection, RichEditorOptions, RichEditorResponseType, RichEditorSpanType, RichEditorStyledStringController, RichEditorStyledStringOptions, KeyboardOptions, PreviewMenuOptions, RichEditorDeleteValue, RichEditorGesture, RichEditorInsertValue, RichEditorSpanPosition, CopyEvent, CutEvent, PasteEvent, RichEditorChangeValue, RichEditorSymbolSpanStyle, RichEditorSpanStyleOptions, RichEditorUrlStyle, SelectionMenuOptions, MenuOnAppearCallback, MenuCallback, LeadingMarginPlaceholder, PlaceholderStyle, RichEditorLayoutStyle, RichEditorParagraphStyle, RichEditorImageSpanStyle, RichEditorImageSpanStyleResult, RichEditorTextStyleResult, OnHoverCallback } from "./../../component/richEditor"
import { CustomBuilder } from "./../../component/builder"
import { RootSceneSession } from "./../../component/rootScene"
import { RouteType, SlideEffect } from "./../../component/pageTransition"
import { RowOptionsV2, RowOptions } from "./../../component/row"
import { RRect, WindowAnimationTarget } from "./../../component/remoteWindow"
import { SaveButtonOnClickResult, SaveDescription, SaveIconStyle, SaveButtonOptions } from "./../../component/saveButton"
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
import { CircleOptions } from "./../../component/circle"
import { ColumnOptions, ColumnOptionsV2 } from "./../../component/column"
import { CompatibleComponentInfo } from "./../../component/interop"
import { EllipseOptions } from "./../../component/ellipse"
import { font } from "./../ohos.font"
import { FormLinkOptions } from "./../../component/formLink"
import { GaugeConfiguration, GaugeOptions, GaugeShadowOptions, GaugeIndicatorOptions } from "./../../component/gauge"
import { GridColColumnOption, GridColOptions } from "./../../component/gridCol"
import { ImageLoadResult } from "./../../component/imageSpan"
import { intl } from "./../ohos.intl"
import { LineOptions, ShapePoint } from "./../../component/line"
import { MarqueeOptions } from "./../../component/marquee"
import { PathOptions } from "./../../component/path"
import { PluginComponentTemplate, PluginErrorData, PluginComponentOptions } from "./../../component/pluginComponent"
import { PolygonOptions } from "./../../component/polygon"
import { PolylineOptions } from "./../../component/polyline"
import { RatingConfiguration, RatingOptions, StarStyleOptions } from "./../../component/rating"
import { RoundedRectOptions, RadiusItem, RectOptions } from "./../../component/rect"
import { StackOptions } from "./../../component/stack"
import { StepperOptions } from "./../../component/stepper"
import { SurfaceRect, SurfaceRotationOptions, XComponentController, NativeXComponentParameters, XComponentOptions, XComponentParameter } from "./../../component/xcomponent"
import { ViewportRect } from "./../../component/shape"
import { Want } from "./../ohos.app.ability.Want"
import { FlexSpaceOptions, FlexOptions } from "./../../component/flex"
import { ImageFrameInfo } from "./../../component/imageAnimator"
import { MenuItemGroupOptions } from "./../../component/menuItemGroup"
import { MenuItemOptions } from "./../../component/menuItem"
import { ColumnSplitDividerStyle } from "./../../component/columnSplit"
import { TextBackgroundStyle } from "./../../component/span"
import { SheetInfo } from "./../../component/actionSheet"
export class TypeChecker {
    static typeInstanceOf<T>(value: Object, prop: string): boolean {
        return value.hasOwnProperty(prop)
    }
    static typeCast<T>(value: Object): any {
        return value as unknown as T
    }
    static isNativeBuffer(value: Object): boolean {
        return value instanceof ArrayBuffer
    }
    static isAccessibilityHoverEvent(value: Object | string | number | undefined | boolean, duplicated_type: boolean, duplicated_x: boolean, duplicated_y: boolean, duplicated_displayX: boolean, duplicated_displayY: boolean, duplicated_windowX: boolean, duplicated_windowY: boolean): boolean {
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
    static isAccessibilityHoverType(value: Object | string | number | undefined | boolean): boolean {
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
    static isAccessibilityOptions(value: Object | string | number | undefined | boolean, duplicated_accessibilityPreferred: boolean): boolean {
        if ((!duplicated_accessibilityPreferred) && (value?.hasOwnProperty("accessibilityPreferred"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof AccessibilityOptions")
        }
    }
    static isAccessibilityRoleType(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (AccessibilityRoleType.ACTION_SHEET)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.ALERT_DIALOG)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.INDEXER_COMPONENT)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.BADGE_COMPONENT)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.BLANK)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.BUTTON)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.BACK_BUTTON)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.SHEET_DRAG_BAR)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.CALENDAR_PICKER)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.CALENDAR)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.CANVAS)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.CANVAS_GRADIENT)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.CANVAS_PATTERN)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.CHECKBOX)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.CHECKBOX_GROUP)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.CIRCLE)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.COLUMN_SPLIT)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.COLUMN)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.CANVAS_RENDERING_CONTEXT_2D)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.CHART)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.COUNTER)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.CONTAINER_MODAL)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.DATA_PANEL)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.DATE_PICKER)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.DIALOG)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.DIVIDER)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.DRAG_BAR)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.EFFECT_COMPONENT)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.ELLIPSE)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.FLEX)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.FLOW_ITEM)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.FORM_COMPONENT)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.FORM_LINK)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.GAUGE)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.GRID)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.GRID_COL)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.GRID_CONTAINER)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.GRID_ITEM)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.GRID_ROW)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.HYPERLINK)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.IMAGE)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.IMAGE_ANIMATOR)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.IMAGE_BITMAP)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.IMAGE_DATA)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.IMAGE_SPAN)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.LABEL)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.LINE)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.LIST)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.LIST_ITEM)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.LIST_ITEM_GROUP)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.LOADING_PROGRESS)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.MARQUEE)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.MATRIX2D)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.MENU)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.MENU_ITEM)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.MENU_ITEM_GROUP)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.NAV_DESTINATION)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.NAV_ROUTER)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.NAVIGATION)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.NAVIGATION_BAR)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.NAVIGATION_MENU)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.NAVIGATOR)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.OFFSCREEN_CANVAS)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.OFFSCREEN_CANVAS_RENDERING_CONTEXT2D)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.OPTION)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.PANEL)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.PAPER_PAGE)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.PATH)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.PATH2D)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.PATTERN_LOCK)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.PICKER)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.PICKER_VIEW)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.PLUGIN_COMPONENT)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.POLYGON)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.POLYLINE)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.POPUP)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.PROGRESS)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.QRCODE)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.RADIO)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.RATING)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.RECT)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.REFRESH)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.RELATIVE_CONTAINER)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.REMOTE_WINDOW)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.RICH_EDITOR)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.RICH_TEXT)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.ROLE_PAGER)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.ROW)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.ROW_SPLIT)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.SCROLL)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.SCROLL_BAR)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.SEARCH)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.SEARCH_FIELD)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.SELECT)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.SHAPE)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.SIDEBAR_CONTAINER)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.SLIDER)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.SPAN)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.STACK)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.STEPPER)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.STEPPER_ITEM)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.SWIPER)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.SWIPER_INDICATOR)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.SWITCH)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.SYMBOL_GLYPH)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.TAB_CONTENT)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.TAB_BAR)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.TABS)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.TEXT)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.TEXT_CLOCK)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.TEXT_ENTRY)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.TEXT_INPUT)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.TEXT_PICKER)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.TEXT_TIMER)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.TEXT_AREA)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.TEXT_FIELD)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.TIME_PICKER)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.TITLE_BAR)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.TOGGLER)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.UI_EXTENSION_COMPONENT)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.VIDEO)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.WATER_FLOW)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.WEB)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.XCOMPONENT)) {
            return true
        }
        else if ((value) === (AccessibilityRoleType.ROLE_NONE)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof AccessibilityRoleType")
        }
    }
    static isAccessibilitySamePageMode(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (AccessibilitySamePageMode.SEMI_SILENT)) {
            return true
        }
        else if ((value) === (AccessibilitySamePageMode.FULL_SILENT)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof AccessibilitySamePageMode")
        }
    }
    static isAdaptiveColor(value: Object | string | number | undefined | boolean): boolean {
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
    static isAdsBlockedDetails(value: Object | string | number | undefined | boolean, duplicated_url: boolean, duplicated_adsBlocked: boolean): boolean {
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
    static isAlignment(value: Object | string | number | undefined | boolean): boolean {
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
    static isAlignRuleOption(value: Object | string | number | undefined | boolean, duplicated__stub: boolean): boolean {
        if ((!duplicated__stub) && (value?.hasOwnProperty("_stub"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof AlignRuleOption")
        }
    }
    static isAlphabetIndexerOptions(value: Object | string | number | undefined | boolean, duplicated_arrayValue: boolean, duplicated_selected: boolean): boolean {
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
    static isAnimateParam(value: Object | string | number | undefined | boolean, duplicated_duration: boolean, duplicated_tempo: boolean, duplicated_curve: boolean, duplicated_delay: boolean, duplicated_iterations: boolean, duplicated_playMode: boolean, duplicated_onFinish: boolean, duplicated_finishCallbackType: boolean, duplicated_expectedFrameRateRange: boolean): boolean {
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
    static isAnimationMode(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (AnimationMode.CONTENT_FIRST)) {
            return true
        }
        else if ((value) === (AnimationMode.ACTION_FIRST)) {
            return true
        }
        else if ((value) === (AnimationMode.NO_ANIMATION)) {
            return true
        }
        else if ((value) === (AnimationMode.CONTENT_FIRST_WITH_JUMP)) {
            return true
        }
        else if ((value) === (AnimationMode.ACTION_FIRST_WITH_JUMP)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof AnimationMode")
        }
    }
    static isAnimationStatus(value: Object | string | number | undefined | boolean): boolean {
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
    static isAppearSymbolEffect(value: Object | string | number | undefined | boolean, duplicated_scope: boolean): boolean {
        if ((!duplicated_scope) && (value?.hasOwnProperty("scope"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof AppearSymbolEffect")
        }
    }
    static isAppRotation(value: Object | string | number | undefined | boolean): boolean {
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
    static isArea(value: Object | string | number | undefined | boolean, duplicated_width: boolean, duplicated_height: boolean, duplicated_position: boolean, duplicated_globalPosition: boolean): boolean {
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
    static isArrowPointPosition(value: Object | string | number | undefined | boolean): boolean {
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
    static isArrowPosition(value: Object | string | number | undefined | boolean): boolean {
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
    static isArrowStyle(value: Object | string | number | undefined | boolean, duplicated_showBackground: boolean, duplicated_isSidebarMiddle: boolean, duplicated_backgroundSize: boolean, duplicated_backgroundColor: boolean, duplicated_arrowSize: boolean, duplicated_arrowColor: boolean): boolean {
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
    static isASTCResource(value: Object | string | number | undefined | boolean, duplicated_sources: boolean, duplicated_column: boolean): boolean {
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
    static isAsymmetricTransitionOption(value: Object | string | number | undefined | boolean, duplicated_appear: boolean, duplicated_disappear: boolean): boolean {
        if ((!duplicated_appear) && (value?.hasOwnProperty("appear"))) {
            return true
        }
        else if ((!duplicated_disappear) && (value?.hasOwnProperty("disappear"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof AsymmetricTransitionOption")
        }
    }
    static isAutoCapitalizationMode(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (AutoCapitalizationMode.NONE)) {
            return true
        }
        else if ((value) === (AutoCapitalizationMode.WORDS)) {
            return true
        }
        else if ((value) === (AutoCapitalizationMode.SENTENCES)) {
            return true
        }
        else if ((value) === (AutoCapitalizationMode.ALL_CHARACTERS)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof AutoCapitalizationMode")
        }
    }
    static isAutoPlayOptions(value: Object | string | number | undefined | boolean, duplicated_stopWhenTouched: boolean): boolean {
        if ((!duplicated_stopWhenTouched) && (value?.hasOwnProperty("stopWhenTouched"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof AutoPlayOptions")
        }
    }
    static isAvoidanceMode(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (AvoidanceMode.COVER_TARGET)) {
            return true
        }
        else if ((value) === (AvoidanceMode.AVOID_AROUND_TARGET)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof AvoidanceMode")
        }
    }
    static isAxis(value: Object | string | number | undefined | boolean): boolean {
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
    static isAxisAction(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (AxisAction.NONE)) {
            return true
        }
        else if ((value) === (AxisAction.BEGIN)) {
            return true
        }
        else if ((value) === (AxisAction.UPDATE)) {
            return true
        }
        else if ((value) === (AxisAction.END)) {
            return true
        }
        else if ((value) === (AxisAction.CANCEL)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof AxisAction")
        }
    }
    static isAxisEvent(value: Object | string | number | undefined | boolean, duplicated_action: boolean, duplicated_displayX: boolean, duplicated_displayY: boolean, duplicated_windowX: boolean, duplicated_windowY: boolean, duplicated_x: boolean, duplicated_y: boolean, duplicated_scrollStep: boolean, duplicated_propagation: boolean): boolean {
        if ((!duplicated_action) && (value?.hasOwnProperty("action"))) {
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
        else if ((!duplicated_x) && (value?.hasOwnProperty("x"))) {
            return true
        }
        else if ((!duplicated_y) && (value?.hasOwnProperty("y"))) {
            return true
        }
        else if ((!duplicated_propagation) && (value?.hasOwnProperty("propagation"))) {
            return true
        }
        else if ((!duplicated_scrollStep) && (value?.hasOwnProperty("scrollStep"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof AxisEvent")
        }
    }
    static isAxisModel(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (AxisModel.ABS_X)) {
            return true
        }
        else if ((value) === (AxisModel.ABS_Y)) {
            return true
        }
        else if ((value) === (AxisModel.ABS_Z)) {
            return true
        }
        else if ((value) === (AxisModel.ABS_RZ)) {
            return true
        }
        else if ((value) === (AxisModel.ABS_GAS)) {
            return true
        }
        else if ((value) === (AxisModel.ABS_BRAKE)) {
            return true
        }
        else if ((value) === (AxisModel.ABS_HAT0X)) {
            return true
        }
        else if ((value) === (AxisModel.ABS_HAT0Y)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof AxisModel")
        }
    }
    static isBackgroundBlurStyleOptions(value: Object | string | number | undefined | boolean, duplicated_policy: boolean, duplicated_inactiveColor: boolean): boolean {
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
    static isBackgroundBrightnessOptions(value: Object | string | number | undefined | boolean, duplicated_rate: boolean, duplicated_lightUpDegree: boolean): boolean {
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
    static isBackgroundColorStyle(value: Object | string | number | undefined | boolean, duplicated_textBackgroundStyle: boolean): boolean {
        if ((!duplicated_textBackgroundStyle) && (value?.hasOwnProperty("textBackgroundStyle"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof BackgroundColorStyle")
        }
    }
    static isBackgroundEffectOptions(value: Object | string | number | undefined | boolean, duplicated_radius: boolean, duplicated_saturation: boolean, duplicated_brightness: boolean, duplicated_color: boolean, duplicated_adaptiveColor: boolean, duplicated_blurOptions: boolean, duplicated_policy: boolean, duplicated_inactiveColor: boolean): boolean {
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
    static isBackgroundImageOptions(value: Object | string | number | undefined | boolean, duplicated_syncLoad: boolean, duplicated_repeat: boolean): boolean {
        if ((!duplicated_syncLoad) && (value?.hasOwnProperty("syncLoad"))) {
            return true
        }
        else if ((!duplicated_repeat) && (value?.hasOwnProperty("repeat"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof BackgroundImageOptions")
        }
    }
    static isBackgroundOptions(value: Object | string | number | undefined | boolean, duplicated_align: boolean): boolean {
        if ((!duplicated_align) && (value?.hasOwnProperty("align"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof BackgroundOptions")
        }
    }
    static isBadgeParamWithNumber(value: Object | string | number | undefined | boolean, duplicated_count: boolean, duplicated_maxCount: boolean): boolean {
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
    static isBadgeParamWithString(value: Object | string | number | undefined | boolean, duplicated_value: boolean): boolean {
        if ((!duplicated_value) && (value?.hasOwnProperty("value"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof BadgeParamWithString")
        }
    }
    static isBadgePosition(value: Object | string | number | undefined | boolean): boolean {
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
    static isBadgeStyle(value: Object | string | number | undefined | boolean, duplicated_color: boolean, duplicated_fontSize: boolean, duplicated_badgeSize: boolean, duplicated_badgeColor: boolean, duplicated_borderColor: boolean, duplicated_borderWidth: boolean, duplicated_fontWeight: boolean): boolean {
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
    static isBarGridColumnOptions(value: Object | string | number | undefined | boolean, duplicated_sm: boolean, duplicated_md: boolean, duplicated_lg: boolean, duplicated_margin: boolean, duplicated_gutter: boolean): boolean {
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
    static isBarMode(value: Object | string | number | undefined | boolean): boolean {
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
    static isBarPosition(value: Object | string | number | undefined | boolean): boolean {
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
    static isBarrierDirection(value: Object | string | number | undefined | boolean): boolean {
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
    static isBarrierStyle(value: Object | string | number | undefined | boolean, duplicated_id: boolean, duplicated_direction: boolean, duplicated_referencedId: boolean): boolean {
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
    static isBarState(value: Object | string | number | undefined | boolean): boolean {
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
    static isBarStyle(value: Object | string | number | undefined | boolean): boolean {
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
    static isBaseContext(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof BaseContext")
    }
    static isBaseCustomComponent(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof BaseCustomComponent")
    }
    static isBaseEvent(value: Object | string | number | undefined | boolean, duplicated_target: boolean, duplicated_timestamp: boolean, duplicated_source: boolean, duplicated_axisHorizontal: boolean, duplicated_axisVertical: boolean, duplicated_pressure: boolean, duplicated_tiltX: boolean, duplicated_tiltY: boolean, duplicated_rollAngle: boolean, duplicated_sourceTool: boolean, duplicated_getModifierKeyState: boolean, duplicated_deviceId: boolean, duplicated_targetDisplayId: boolean): boolean {
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
        else if ((!duplicated_rollAngle) && (value?.hasOwnProperty("rollAngle"))) {
            return true
        }
        else if ((!duplicated_getModifierKeyState) && (value?.hasOwnProperty("getModifierKeyState"))) {
            return true
        }
        else if ((!duplicated_deviceId) && (value?.hasOwnProperty("deviceId"))) {
            return true
        }
        else if ((!duplicated_targetDisplayId) && (value?.hasOwnProperty("targetDisplayId"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof BaseEvent")
        }
    }
    static isBaseGestureEvent(value: Object | string | number | undefined | boolean, duplicated_fingerList: boolean): boolean {
        if ((!duplicated_fingerList) && (value?.hasOwnProperty("fingerList"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof BaseGestureEvent")
        }
    }
    static isBaselineOffsetStyle(value: Object | string | number | undefined | boolean, duplicated_baselineOffset: boolean): boolean {
        if ((!duplicated_baselineOffset) && (value?.hasOwnProperty("baselineOffset"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof BaselineOffsetStyle")
        }
    }
    static isBaseShape(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof BaseShape")
    }
    static isBias(value: Object | string | number | undefined | boolean, duplicated_horizontal: boolean, duplicated_vertical: boolean): boolean {
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
    static isBlendApplyType(value: Object | string | number | undefined | boolean): boolean {
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
    static isBlendMode(value: Object | string | number | undefined | boolean): boolean {
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
    static isBlurOnKeyboardHideMode(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (BlurOnKeyboardHideMode.SILENT)) {
            return true
        }
        else if ((value) === (BlurOnKeyboardHideMode.BLUR)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof BlurOnKeyboardHideMode")
        }
    }
    static isBlurOptions(value: Object | string | number | undefined | boolean, duplicated_grayscale: boolean): boolean {
        if ((!duplicated_grayscale) && (value?.hasOwnProperty("grayscale"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof BlurOptions")
        }
    }
    static isBlurStyle(value: Object | string | number | undefined | boolean): boolean {
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
    static isBlurStyleActivePolicy(value: Object | string | number | undefined | boolean): boolean {
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
    static isBoardStyle(value: Object | string | number | undefined | boolean, duplicated_borderRadius: boolean): boolean {
        if ((!duplicated_borderRadius) && (value?.hasOwnProperty("borderRadius"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof BoardStyle")
        }
    }
    static isBorderImageOption(value: Object | string | number | undefined | boolean, duplicated_slice: boolean, duplicated_repeat: boolean, duplicated_source: boolean, duplicated_width: boolean, duplicated_outset: boolean, duplicated_fill: boolean): boolean {
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
    static isBorderOptions(value: Object | string | number | undefined | boolean, duplicated_width: boolean, duplicated_color: boolean, duplicated_radius: boolean, duplicated_style: boolean, duplicated_dashGap: boolean, duplicated_dashWidth: boolean): boolean {
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
    static isBorderRadiuses(value: Object | string | number | undefined | boolean, duplicated_topLeft: boolean, duplicated_topRight: boolean, duplicated_bottomLeft: boolean, duplicated_bottomRight: boolean): boolean {
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
    static isBorderRadiuses_graphics(value: Object | string | number | undefined | boolean, duplicated_topLeft: boolean, duplicated_topRight: boolean, duplicated_bottomLeft: boolean, duplicated_bottomRight: boolean): boolean {
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
            throw new Error("Can not discriminate value typeof BorderRadiuses_graphics")
        }
    }
    static isBorderStyle(value: Object | string | number | undefined | boolean): boolean {
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
    static isBottomTabBarStyle(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof BottomTabBarStyle")
    }
    static isBounceSymbolEffect(value: Object | string | number | undefined | boolean, duplicated_scope: boolean, duplicated_direction: boolean): boolean {
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
    static isBreakPoints(value: Object | string | number | undefined | boolean, duplicated_value: boolean, duplicated_reference: boolean): boolean {
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
    static isBreakpointsReference(value: Object | string | number | undefined | boolean): boolean {
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
    static isBuilderNodeOps(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof BuilderNodeOps")
    }
    static isBuilderNodeOptions(value: Object | string | number | undefined | boolean, duplicated_selfIdealSize: boolean, duplicated_type: boolean, duplicated_surfaceId: boolean): boolean {
        if ((!duplicated_selfIdealSize) && (value?.hasOwnProperty("selfIdealSize"))) {
            return true
        }
        else if ((!duplicated_type) && (value?.hasOwnProperty("type"))) {
            return true
        }
        else if ((!duplicated_surfaceId) && (value?.hasOwnProperty("surfaceId"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof BuilderNodeOptions")
        }
    }
    static isBusinessError(value: Object | string | number | undefined | boolean, duplicated_name: boolean, duplicated_message: boolean, duplicated_stack: boolean, duplicated_code: boolean): boolean {
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
    static isButtonConfiguration(value: Object | string | number | undefined | boolean, duplicated_label: boolean, duplicated_pressed: boolean, duplicated_triggerClick: boolean): boolean {
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
    static isButtonIconOptions(value: Object | string | number | undefined | boolean, duplicated_shown: boolean, duplicated_hidden: boolean, duplicated_switching: boolean): boolean {
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
    static isButtonLabelStyle(value: Object | string | number | undefined | boolean, duplicated_overflow: boolean, duplicated_maxLines: boolean, duplicated_minFontSize: boolean, duplicated_maxFontSize: boolean, duplicated_heightAdaptivePolicy: boolean, duplicated_font: boolean): boolean {
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
            throw new Error("Can not discriminate value typeof ButtonLabelStyle")
        }
    }
    static isButtonOptions(value: Object | string | number | undefined | boolean, duplicated_type: boolean, duplicated_stateEffect: boolean, duplicated_buttonStyle: boolean, duplicated_controlSize: boolean, duplicated_role: boolean): boolean {
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
    static isButtonRole(value: Object | string | number | undefined | boolean): boolean {
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
    static isButtonStyle(value: Object | string | number | undefined | boolean, duplicated_left: boolean, duplicated_top: boolean, duplicated_width: boolean, duplicated_height: boolean, duplicated_icons: boolean): boolean {
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
    static isButtonStyleMode(value: Object | string | number | undefined | boolean): boolean {
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
    static isButtonType(value: Object | string | number | undefined | boolean): boolean {
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
    static isCacheMode(value: Object | string | number | undefined | boolean): boolean {
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
    static isCalendarAlign(value: Object | string | number | undefined | boolean): boolean {
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
    static isCalendarController(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof CalendarController")
    }
    static isCalendarDay(value: Object | string | number | undefined | boolean, duplicated_index: boolean, duplicated_lunarMonth: boolean, duplicated_lunarDay: boolean, duplicated_dayMark: boolean, duplicated_dayMarkValue: boolean, duplicated_year: boolean, duplicated_month: boolean, duplicated_day: boolean, duplicated_isFirstOfLunar: boolean, duplicated_hasSchedule: boolean, duplicated_markLunarDay: boolean): boolean {
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
    static isCalendarDialogOptions(value: Object | string | number | undefined | boolean, duplicated_onAccept: boolean, duplicated_onCancel: boolean, duplicated_onChange: boolean, duplicated_backgroundColor: boolean, duplicated_backgroundBlurStyle: boolean, duplicated_backgroundBlurStyleOptions: boolean, duplicated_backgroundEffect: boolean, duplicated_acceptButtonStyle: boolean, duplicated_cancelButtonStyle: boolean, duplicated_onDidAppear: boolean, duplicated_onDidDisappear: boolean, duplicated_onWillAppear: boolean, duplicated_onWillDisappear: boolean, duplicated_shadow: boolean, duplicated_enableHoverMode: boolean, duplicated_hoverModeArea: boolean, duplicated_markToday: boolean): boolean {
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
        else if ((!duplicated_backgroundBlurStyleOptions) && (value?.hasOwnProperty("backgroundBlurStyleOptions"))) {
            return true
        }
        else if ((!duplicated_backgroundEffect) && (value?.hasOwnProperty("backgroundEffect"))) {
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
        else if ((!duplicated_markToday) && (value?.hasOwnProperty("markToday"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof CalendarDialogOptions")
        }
    }
    static isCalendarOptions(value: Object | string | number | undefined | boolean, duplicated_hintRadius: boolean, duplicated_selected: boolean, duplicated_start: boolean, duplicated_end: boolean, duplicated_disabledDateRange: boolean): boolean {
        if ((!duplicated_hintRadius) && (value?.hasOwnProperty("hintRadius"))) {
            return true
        }
        else if ((!duplicated_selected) && (value?.hasOwnProperty("selected"))) {
            return true
        }
        else if ((!duplicated_start) && (value?.hasOwnProperty("start"))) {
            return true
        }
        else if ((!duplicated_end) && (value?.hasOwnProperty("end"))) {
            return true
        }
        else if ((!duplicated_disabledDateRange) && (value?.hasOwnProperty("disabledDateRange"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof CalendarOptions")
        }
    }
    static isCalendarPickerDialog(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof CalendarPickerDialog")
    }
    static isCalendarRequestedData(value: Object | string | number | undefined | boolean, duplicated_year: boolean, duplicated_month: boolean, duplicated_currentYear: boolean, duplicated_currentMonth: boolean, duplicated_monthState: boolean): boolean {
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
    static isCalendarRequestedMonths(value: Object | string | number | undefined | boolean, duplicated_date: boolean, duplicated_currentData: boolean, duplicated_preData: boolean, duplicated_nextData: boolean, duplicated_controller: boolean): boolean {
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
            throw new Error("Can not discriminate value typeof CalendarRequestedMonths")
        }
    }
    static isCalendarSelectedDate(value: Object | string | number | undefined | boolean, duplicated_year: boolean, duplicated_month: boolean, duplicated_day: boolean): boolean {
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
    static isCancelButtonOptions(value: Object | string | number | undefined | boolean, duplicated_style: boolean, duplicated_icon: boolean): boolean {
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
    static isCancelButtonStyle(value: Object | string | number | undefined | boolean): boolean {
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
    static isCancelButtonSymbolOptions(value: Object | string | number | undefined | boolean, duplicated_style: boolean, duplicated_icon: boolean): boolean {
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
    static isCanvasGradient(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof CanvasGradient")
    }
    static isCanvasPath(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof CanvasPath")
    }
    static isCanvasPattern(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof CanvasPattern")
    }
    static isCanvasRenderer(value: Object | string | number | undefined | boolean, duplicated_letterSpacing: boolean, duplicated_globalAlpha: boolean, duplicated_globalCompositeOperation: boolean, duplicated_fillStyle: boolean, duplicated_strokeStyle: boolean, duplicated_filter: boolean, duplicated_imageSmoothingEnabled: boolean, duplicated_imageSmoothingQuality: boolean, duplicated_lineCap: boolean, duplicated_lineDashOffset: boolean, duplicated_lineJoin: boolean, duplicated_lineWidth: boolean, duplicated_miterLimit: boolean, duplicated_shadowBlur: boolean, duplicated_shadowColor: boolean, duplicated_shadowOffsetX: boolean, duplicated_shadowOffsetY: boolean, duplicated_direction: boolean, duplicated_font: boolean, duplicated_textAlign: boolean, duplicated_textBaseline: boolean): boolean {
        if ((!duplicated_letterSpacing) && (value?.hasOwnProperty("letterSpacing"))) {
            return true
        }
        else if ((!duplicated_globalAlpha) && (value?.hasOwnProperty("globalAlpha"))) {
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
    static isCanvasRenderingContext2D(value: Object | string | number | undefined | boolean, duplicated_height: boolean, duplicated_width: boolean, duplicated_canvas: boolean): boolean {
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
    static isCapsuleStyleOptions(value: Object | string | number | undefined | boolean, duplicated_borderColor: boolean, duplicated_borderWidth: boolean, duplicated_content: boolean, duplicated_font: boolean, duplicated_fontColor: boolean, duplicated_showDefaultPercentage: boolean, duplicated_borderRadius: boolean): boolean {
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
        else if ((!duplicated_borderRadius) && (value?.hasOwnProperty("borderRadius"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof CapsuleStyleOptions")
        }
    }
    static isCaretOffset(value: Object | string | number | undefined | boolean, duplicated_index: boolean, duplicated_x: boolean, duplicated_y: boolean): boolean {
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
    static isCaretStyle(value: Object | string | number | undefined | boolean, duplicated_width: boolean, duplicated_color: boolean): boolean {
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
    static isChainAnimationOptions(value: Object | string | number | undefined | boolean, duplicated_minSpace: boolean, duplicated_maxSpace: boolean, duplicated_conductivity: boolean, duplicated_intensity: boolean, duplicated_edgeEffect: boolean, duplicated_stiffness: boolean, duplicated_damping: boolean): boolean {
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
    static isChainEdgeEffect(value: Object | string | number | undefined | boolean): boolean {
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
    static isChainStyle(value: Object | string | number | undefined | boolean): boolean {
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
    static isChainWeightOptions(value: Object | string | number | undefined | boolean, duplicated_horizontal: boolean, duplicated_vertical: boolean): boolean {
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
    static isCheckBoxConfiguration(value: Object | string | number | undefined | boolean, duplicated_name: boolean, duplicated_selected: boolean, duplicated_triggerChange: boolean): boolean {
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
    static isCheckboxGroupOptions(value: Object | string | number | undefined | boolean, duplicated_group: boolean): boolean {
        if ((!duplicated_group) && (value?.hasOwnProperty("group"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof CheckboxGroupOptions")
        }
    }
    static isCheckboxGroupResult(value: Object | string | number | undefined | boolean, duplicated_name: boolean, duplicated_status: boolean): boolean {
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
    static isCheckboxOptions(value: Object | string | number | undefined | boolean, duplicated_name: boolean, duplicated_group: boolean, duplicated_indicatorBuilder: boolean): boolean {
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
    static isCheckBoxShape(value: Object | string | number | undefined | boolean): boolean {
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
    static isChildrenMainSize(value: Object | string | number | undefined | boolean, duplicated_childDefaultSize: boolean): boolean {
        if ((!duplicated_childDefaultSize) && (value?.hasOwnProperty("childDefaultSize"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ChildrenMainSize")
        }
    }
    static isCircle(value: Object | string | number | undefined | boolean, duplicated_centerX: boolean, duplicated_centerY: boolean, duplicated_radius: boolean): boolean {
        if ((!duplicated_centerX) && (value?.hasOwnProperty("centerX"))) {
            return true
        }
        else if ((!duplicated_centerY) && (value?.hasOwnProperty("centerY"))) {
            return true
        }
        else if ((!duplicated_radius) && (value?.hasOwnProperty("radius"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof Circle")
        }
    }
    static isCircleOptions(value: Object | string | number | undefined | boolean, duplicated_width: boolean, duplicated_height: boolean): boolean {
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
    static isCircleShape(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof CircleShape")
    }
    static isCircleStyleOptions(value: Object | string | number | undefined | boolean, duplicated_color: boolean, duplicated_radius: boolean, duplicated_enableWaveEffect: boolean, duplicated_enableForeground: boolean): boolean {
        if ((!duplicated_color) && (value?.hasOwnProperty("color"))) {
            return true
        }
        else if ((!duplicated_radius) && (value?.hasOwnProperty("radius"))) {
            return true
        }
        else if ((!duplicated_enableWaveEffect) && (value?.hasOwnProperty("enableWaveEffect"))) {
            return true
        }
        else if ((!duplicated_enableForeground) && (value?.hasOwnProperty("enableForeground"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof CircleStyleOptions")
        }
    }
    static isClickEffect(value: Object | string | number | undefined | boolean, duplicated_level: boolean, duplicated_scale: boolean): boolean {
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
    static isClickEffectLevel(value: Object | string | number | undefined | boolean): boolean {
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
    static isClickEvent(value: Object | string | number | undefined | boolean, duplicated_displayX: boolean, duplicated_displayY: boolean, duplicated_windowX: boolean, duplicated_windowY: boolean, duplicated_x: boolean, duplicated_y: boolean, duplicated_hand: boolean, duplicated_preventDefault: boolean): boolean {
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
        else if ((!duplicated_x) && (value?.hasOwnProperty("x"))) {
            return true
        }
        else if ((!duplicated_y) && (value?.hasOwnProperty("y"))) {
            return true
        }
        else if ((!duplicated_preventDefault) && (value?.hasOwnProperty("preventDefault"))) {
            return true
        }
        else if ((!duplicated_hand) && (value?.hasOwnProperty("hand"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ClickEvent")
        }
    }
    static isClientAuthenticationHandler(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof ClientAuthenticationHandler")
    }
    static isCloseSwipeActionOptions(value: Object | string | number | undefined | boolean, duplicated_onFinish: boolean): boolean {
        if ((!duplicated_onFinish) && (value?.hasOwnProperty("onFinish"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof CloseSwipeActionOptions")
        }
    }
    static isColor(value: Object | string | number | undefined | boolean): boolean {
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
    static isColorContent(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof ColorContent")
    }
    static isColorFilter(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof ColorFilter")
    }
    static isColoringStrategy(value: Object | string | number | undefined | boolean): boolean {
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
    static isColorMetrics(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof ColorMetrics")
    }
    static isColorMode(value: Object | string | number | undefined | boolean): boolean {
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
    static isColors(value: Object | string | number | undefined | boolean, duplicated_brand: boolean, duplicated_warning: boolean, duplicated_alert: boolean, duplicated_confirm: boolean, duplicated_fontPrimary: boolean, duplicated_fontSecondary: boolean, duplicated_fontTertiary: boolean, duplicated_fontFourth: boolean, duplicated_fontEmphasize: boolean, duplicated_fontOnPrimary: boolean, duplicated_fontOnSecondary: boolean, duplicated_fontOnTertiary: boolean, duplicated_fontOnFourth: boolean, duplicated_iconPrimary: boolean, duplicated_iconSecondary: boolean, duplicated_iconTertiary: boolean, duplicated_iconFourth: boolean, duplicated_iconEmphasize: boolean, duplicated_iconSubEmphasize: boolean, duplicated_iconOnPrimary: boolean, duplicated_iconOnSecondary: boolean, duplicated_iconOnTertiary: boolean, duplicated_iconOnFourth: boolean, duplicated_backgroundPrimary: boolean, duplicated_backgroundSecondary: boolean, duplicated_backgroundTertiary: boolean, duplicated_backgroundFourth: boolean, duplicated_backgroundEmphasize: boolean, duplicated_compForegroundPrimary: boolean, duplicated_compBackgroundPrimary: boolean, duplicated_compBackgroundPrimaryTran: boolean, duplicated_compBackgroundPrimaryContrary: boolean, duplicated_compBackgroundGray: boolean, duplicated_compBackgroundSecondary: boolean, duplicated_compBackgroundTertiary: boolean, duplicated_compBackgroundEmphasize: boolean, duplicated_compBackgroundNeutral: boolean, duplicated_compEmphasizeSecondary: boolean, duplicated_compEmphasizeTertiary: boolean, duplicated_compDivider: boolean, duplicated_compCommonContrary: boolean, duplicated_compBackgroundFocus: boolean, duplicated_compFocusedPrimary: boolean, duplicated_compFocusedSecondary: boolean, duplicated_compFocusedTertiary: boolean, duplicated_interactiveHover: boolean, duplicated_interactivePressed: boolean, duplicated_interactiveFocus: boolean, duplicated_interactiveActive: boolean, duplicated_interactiveSelect: boolean, duplicated_interactiveClick: boolean): boolean {
        if ((!duplicated_brand) && (value?.hasOwnProperty("brand"))) {
            return true
        }
        else if ((!duplicated_warning) && (value?.hasOwnProperty("warning"))) {
            return true
        }
        else if ((!duplicated_alert) && (value?.hasOwnProperty("alert"))) {
            return true
        }
        else if ((!duplicated_confirm) && (value?.hasOwnProperty("confirm"))) {
            return true
        }
        else if ((!duplicated_fontPrimary) && (value?.hasOwnProperty("fontPrimary"))) {
            return true
        }
        else if ((!duplicated_fontSecondary) && (value?.hasOwnProperty("fontSecondary"))) {
            return true
        }
        else if ((!duplicated_fontTertiary) && (value?.hasOwnProperty("fontTertiary"))) {
            return true
        }
        else if ((!duplicated_fontFourth) && (value?.hasOwnProperty("fontFourth"))) {
            return true
        }
        else if ((!duplicated_fontEmphasize) && (value?.hasOwnProperty("fontEmphasize"))) {
            return true
        }
        else if ((!duplicated_fontOnPrimary) && (value?.hasOwnProperty("fontOnPrimary"))) {
            return true
        }
        else if ((!duplicated_fontOnSecondary) && (value?.hasOwnProperty("fontOnSecondary"))) {
            return true
        }
        else if ((!duplicated_fontOnTertiary) && (value?.hasOwnProperty("fontOnTertiary"))) {
            return true
        }
        else if ((!duplicated_fontOnFourth) && (value?.hasOwnProperty("fontOnFourth"))) {
            return true
        }
        else if ((!duplicated_iconPrimary) && (value?.hasOwnProperty("iconPrimary"))) {
            return true
        }
        else if ((!duplicated_iconSecondary) && (value?.hasOwnProperty("iconSecondary"))) {
            return true
        }
        else if ((!duplicated_iconTertiary) && (value?.hasOwnProperty("iconTertiary"))) {
            return true
        }
        else if ((!duplicated_iconFourth) && (value?.hasOwnProperty("iconFourth"))) {
            return true
        }
        else if ((!duplicated_iconEmphasize) && (value?.hasOwnProperty("iconEmphasize"))) {
            return true
        }
        else if ((!duplicated_iconSubEmphasize) && (value?.hasOwnProperty("iconSubEmphasize"))) {
            return true
        }
        else if ((!duplicated_iconOnPrimary) && (value?.hasOwnProperty("iconOnPrimary"))) {
            return true
        }
        else if ((!duplicated_iconOnSecondary) && (value?.hasOwnProperty("iconOnSecondary"))) {
            return true
        }
        else if ((!duplicated_iconOnTertiary) && (value?.hasOwnProperty("iconOnTertiary"))) {
            return true
        }
        else if ((!duplicated_iconOnFourth) && (value?.hasOwnProperty("iconOnFourth"))) {
            return true
        }
        else if ((!duplicated_backgroundPrimary) && (value?.hasOwnProperty("backgroundPrimary"))) {
            return true
        }
        else if ((!duplicated_backgroundSecondary) && (value?.hasOwnProperty("backgroundSecondary"))) {
            return true
        }
        else if ((!duplicated_backgroundTertiary) && (value?.hasOwnProperty("backgroundTertiary"))) {
            return true
        }
        else if ((!duplicated_backgroundFourth) && (value?.hasOwnProperty("backgroundFourth"))) {
            return true
        }
        else if ((!duplicated_backgroundEmphasize) && (value?.hasOwnProperty("backgroundEmphasize"))) {
            return true
        }
        else if ((!duplicated_compForegroundPrimary) && (value?.hasOwnProperty("compForegroundPrimary"))) {
            return true
        }
        else if ((!duplicated_compBackgroundPrimary) && (value?.hasOwnProperty("compBackgroundPrimary"))) {
            return true
        }
        else if ((!duplicated_compBackgroundPrimaryTran) && (value?.hasOwnProperty("compBackgroundPrimaryTran"))) {
            return true
        }
        else if ((!duplicated_compBackgroundPrimaryContrary) && (value?.hasOwnProperty("compBackgroundPrimaryContrary"))) {
            return true
        }
        else if ((!duplicated_compBackgroundGray) && (value?.hasOwnProperty("compBackgroundGray"))) {
            return true
        }
        else if ((!duplicated_compBackgroundSecondary) && (value?.hasOwnProperty("compBackgroundSecondary"))) {
            return true
        }
        else if ((!duplicated_compBackgroundTertiary) && (value?.hasOwnProperty("compBackgroundTertiary"))) {
            return true
        }
        else if ((!duplicated_compBackgroundEmphasize) && (value?.hasOwnProperty("compBackgroundEmphasize"))) {
            return true
        }
        else if ((!duplicated_compBackgroundNeutral) && (value?.hasOwnProperty("compBackgroundNeutral"))) {
            return true
        }
        else if ((!duplicated_compEmphasizeSecondary) && (value?.hasOwnProperty("compEmphasizeSecondary"))) {
            return true
        }
        else if ((!duplicated_compEmphasizeTertiary) && (value?.hasOwnProperty("compEmphasizeTertiary"))) {
            return true
        }
        else if ((!duplicated_compDivider) && (value?.hasOwnProperty("compDivider"))) {
            return true
        }
        else if ((!duplicated_compCommonContrary) && (value?.hasOwnProperty("compCommonContrary"))) {
            return true
        }
        else if ((!duplicated_compBackgroundFocus) && (value?.hasOwnProperty("compBackgroundFocus"))) {
            return true
        }
        else if ((!duplicated_compFocusedPrimary) && (value?.hasOwnProperty("compFocusedPrimary"))) {
            return true
        }
        else if ((!duplicated_compFocusedSecondary) && (value?.hasOwnProperty("compFocusedSecondary"))) {
            return true
        }
        else if ((!duplicated_compFocusedTertiary) && (value?.hasOwnProperty("compFocusedTertiary"))) {
            return true
        }
        else if ((!duplicated_interactiveHover) && (value?.hasOwnProperty("interactiveHover"))) {
            return true
        }
        else if ((!duplicated_interactivePressed) && (value?.hasOwnProperty("interactivePressed"))) {
            return true
        }
        else if ((!duplicated_interactiveFocus) && (value?.hasOwnProperty("interactiveFocus"))) {
            return true
        }
        else if ((!duplicated_interactiveActive) && (value?.hasOwnProperty("interactiveActive"))) {
            return true
        }
        else if ((!duplicated_interactiveSelect) && (value?.hasOwnProperty("interactiveSelect"))) {
            return true
        }
        else if ((!duplicated_interactiveClick) && (value?.hasOwnProperty("interactiveClick"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof Colors")
        }
    }
    static isColorStop(value: Object | string | number | undefined | boolean, duplicated_color: boolean, duplicated_offset: boolean): boolean {
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
    static isColumnOptions(value: Object | string | number | undefined | boolean, duplicated_space: boolean): boolean {
        if ((!duplicated_space) && (value?.hasOwnProperty("space"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ColumnOptions")
        }
    }
    static isColumnOptionsV2(value: Object | string | number | undefined | boolean, duplicated__stub: boolean): boolean {
        if ((!duplicated__stub) && (value?.hasOwnProperty("_stub"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ColumnOptionsV2")
        }
    }
    static isColumnSplitDividerStyle(value: Object | string | number | undefined | boolean, duplicated_startMargin: boolean, duplicated_endMargin: boolean): boolean {
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
    static isCommandPath(value: Object | string | number | undefined | boolean, duplicated_commands: boolean): boolean {
        if ((!duplicated_commands) && (value?.hasOwnProperty("commands"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof CommandPath")
        }
    }
    static iscommon_Context(value: Object | string | number | undefined | boolean, duplicated_cacheDir: boolean, duplicated_tempDir: boolean, duplicated_filesDir: boolean, duplicated_databaseDir: boolean, duplicated_preferencesDir: boolean, duplicated_bundleCodeDir: boolean, duplicated_distributedFilesDir: boolean, duplicated_resourceDir: boolean, duplicated_cloudFileDir: boolean): boolean {
        if ((!duplicated_cacheDir) && (value?.hasOwnProperty("cacheDir"))) {
            return true
        }
        else if ((!duplicated_tempDir) && (value?.hasOwnProperty("tempDir"))) {
            return true
        }
        else if ((!duplicated_filesDir) && (value?.hasOwnProperty("filesDir"))) {
            return true
        }
        else if ((!duplicated_databaseDir) && (value?.hasOwnProperty("databaseDir"))) {
            return true
        }
        else if ((!duplicated_preferencesDir) && (value?.hasOwnProperty("preferencesDir"))) {
            return true
        }
        else if ((!duplicated_bundleCodeDir) && (value?.hasOwnProperty("bundleCodeDir"))) {
            return true
        }
        else if ((!duplicated_distributedFilesDir) && (value?.hasOwnProperty("distributedFilesDir"))) {
            return true
        }
        else if ((!duplicated_resourceDir) && (value?.hasOwnProperty("resourceDir"))) {
            return true
        }
        else if ((!duplicated_cloudFileDir) && (value?.hasOwnProperty("cloudFileDir"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof common.Context")
        }
    }
    static iscommon2D_Color(value: Object | string | number | undefined | boolean, duplicated_alpha: boolean, duplicated_red: boolean, duplicated_green: boolean, duplicated_blue: boolean): boolean {
        if ((!duplicated_alpha) && (value?.hasOwnProperty("alpha"))) {
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
        else {
            throw new Error("Can not discriminate value typeof common2D.Color")
        }
    }
    static iscommon2D_Point(value: Object | string | number | undefined | boolean, duplicated_x: boolean, duplicated_y: boolean): boolean {
        if ((!duplicated_x) && (value?.hasOwnProperty("x"))) {
            return true
        }
        else if ((!duplicated_y) && (value?.hasOwnProperty("y"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof common2D.Point")
        }
    }
    static iscommon2D_Point3d(value: Object | string | number | undefined | boolean, duplicated_z: boolean): boolean {
        if ((!duplicated_z) && (value?.hasOwnProperty("z"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof common2D.Point3d")
        }
    }
    static iscommon2D_Rect(value: Object | string | number | undefined | boolean, duplicated_left: boolean, duplicated_top: boolean, duplicated_right: boolean, duplicated_bottom: boolean): boolean {
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
        else {
            throw new Error("Can not discriminate value typeof common2D.Rect")
        }
    }
    static isCommonModifier(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof CommonModifier")
    }
    static isCommonShape(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof CommonShape")
    }
    static isCompatibleComponentInfo(value: Object | string | number | undefined | boolean, duplicated_name: boolean, duplicated_component: boolean): boolean {
        if ((!duplicated_name) && (value?.hasOwnProperty("name"))) {
            return true
        }
        else if ((!duplicated_component) && (value?.hasOwnProperty("component"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof CompatibleComponentInfo")
        }
    }
    static isComponentContent(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof ComponentContent")
    }
    static isComponentInfo(value: Object | string | number | undefined | boolean, duplicated_size: boolean, duplicated_localOffset: boolean, duplicated_windowOffset: boolean, duplicated_screenOffset: boolean, duplicated_translate: boolean, duplicated_scale: boolean, duplicated_rotate: boolean, duplicated_transform: boolean): boolean {
        if ((!duplicated_size) && (value?.hasOwnProperty("size"))) {
            return true
        }
        else if ((!duplicated_localOffset) && (value?.hasOwnProperty("localOffset"))) {
            return true
        }
        else if ((!duplicated_windowOffset) && (value?.hasOwnProperty("windowOffset"))) {
            return true
        }
        else if ((!duplicated_screenOffset) && (value?.hasOwnProperty("screenOffset"))) {
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
        else if ((!duplicated_transform) && (value?.hasOwnProperty("transform"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ComponentInfo")
        }
    }
    static isComputedBarAttribute(value: Object | string | number | undefined | boolean, duplicated_totalOffset: boolean, duplicated_totalLength: boolean): boolean {
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
    static isConsoleMessage(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof ConsoleMessage")
    }
    static isConstraintSizeOptions(value: Object | string | number | undefined | boolean, duplicated_minWidth: boolean, duplicated_maxWidth: boolean, duplicated_minHeight: boolean, duplicated_maxHeight: boolean): boolean {
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
    static isContentClipMode(value: Object | string | number | undefined | boolean): boolean {
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
    static isContentCoverOptions(value: Object | string | number | undefined | boolean, duplicated_modalTransition: boolean, duplicated_onWillDismiss: boolean, duplicated_transition: boolean): boolean {
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
    static isContentModifier(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof ContentModifier")
    }
    static isContentType(value: Object | string | number | undefined | boolean): boolean {
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
        else if ((value) === (ContentType.PASSPORT_NUMBER)) {
            return true
        }
        else if ((value) === (ContentType.VALIDITY)) {
            return true
        }
        else if ((value) === (ContentType.ISSUE_AT)) {
            return true
        }
        else if ((value) === (ContentType.ORGANIZATION)) {
            return true
        }
        else if ((value) === (ContentType.TAX_ID)) {
            return true
        }
        else if ((value) === (ContentType.ADDRESS_CITY_AND_STATE)) {
            return true
        }
        else if ((value) === (ContentType.FLIGHT_NUMBER)) {
            return true
        }
        else if ((value) === (ContentType.LICENSE_NUMBER)) {
            return true
        }
        else if ((value) === (ContentType.LICENSE_FILE_NUMBER)) {
            return true
        }
        else if ((value) === (ContentType.LICENSE_PLATE)) {
            return true
        }
        else if ((value) === (ContentType.ENGINE_NUMBER)) {
            return true
        }
        else if ((value) === (ContentType.LICENSE_CHASSIS_NUMBER)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ContentType")
        }
    }
    static isContext(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof Context")
    }
    static isContextMenuAnimationOptions(value: Object | string | number | undefined | boolean, duplicated_scale: boolean, duplicated_transition: boolean, duplicated_hoverScale: boolean): boolean {
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
    static isContextMenuEditStateFlags(value: Object | string | number | undefined | boolean): boolean {
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
    static isContextMenuInputFieldType(value: Object | string | number | undefined | boolean): boolean {
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
    static isContextMenuMediaType(value: Object | string | number | undefined | boolean): boolean {
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
    static isContextMenuOptions(value: Object | string | number | undefined | boolean, duplicated_offset: boolean, duplicated_placement: boolean, duplicated_enableArrow: boolean, duplicated_arrowOffset: boolean, duplicated_preview: boolean, duplicated_previewBorderRadius: boolean, duplicated_borderRadius: boolean, duplicated_onAppear: boolean, duplicated_onDisappear: boolean, duplicated_aboutToAppear: boolean, duplicated_aboutToDisappear: boolean, duplicated_layoutRegionMargin: boolean, duplicated_previewAnimationOptions: boolean, duplicated_backgroundColor: boolean, duplicated_backgroundBlurStyle: boolean, duplicated_backgroundBlurStyleOptions: boolean, duplicated_backgroundEffect: boolean, duplicated_transition: boolean, duplicated_enableHoverMode: boolean, duplicated_outlineColor: boolean, duplicated_outlineWidth: boolean, duplicated_hapticFeedbackMode: boolean): boolean {
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
        else if ((!duplicated_previewBorderRadius) && (value?.hasOwnProperty("previewBorderRadius"))) {
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
        else if ((!duplicated_backgroundBlurStyleOptions) && (value?.hasOwnProperty("backgroundBlurStyleOptions"))) {
            return true
        }
        else if ((!duplicated_backgroundEffect) && (value?.hasOwnProperty("backgroundEffect"))) {
            return true
        }
        else if ((!duplicated_transition) && (value?.hasOwnProperty("transition"))) {
            return true
        }
        else if ((!duplicated_enableHoverMode) && (value?.hasOwnProperty("enableHoverMode"))) {
            return true
        }
        else if ((!duplicated_outlineColor) && (value?.hasOwnProperty("outlineColor"))) {
            return true
        }
        else if ((!duplicated_outlineWidth) && (value?.hasOwnProperty("outlineWidth"))) {
            return true
        }
        else if ((!duplicated_hapticFeedbackMode) && (value?.hasOwnProperty("hapticFeedbackMode"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ContextMenuOptions")
        }
    }
    static isContextMenuSourceType(value: Object | string | number | undefined | boolean): boolean {
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
    static isControllerHandler(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof ControllerHandler")
    }
    static isControlSize(value: Object | string | number | undefined | boolean): boolean {
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
    static isCopyEvent(value: Object | string | number | undefined | boolean, duplicated_preventDefault: boolean): boolean {
        if ((!duplicated_preventDefault) && (value?.hasOwnProperty("preventDefault"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof CopyEvent")
        }
    }
    static isCopyOptions(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (CopyOptions.None)) {
            return true
        }
        else if ((value) === (CopyOptions.InApp)) {
            return true
        }
        else if ((value) === (CopyOptions.LocalDevice)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof CopyOptions")
        }
    }
    static isCornerRadius(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof CornerRadius")
    }
    static isCrossLanguageOptions(value: Object | string | number | undefined | boolean, duplicated_attributeSetting: boolean): boolean {
        if ((!duplicated_attributeSetting) && (value?.hasOwnProperty("attributeSetting"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof CrossLanguageOptions")
        }
    }
    static isCrownAction(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (CrownAction.BEGIN)) {
            return true
        }
        else if ((value) === (CrownAction.UPDATE)) {
            return true
        }
        else if ((value) === (CrownAction.END)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof CrownAction")
        }
    }
    static isCrownEvent(value: Object | string | number | undefined | boolean, duplicated_timestamp: boolean, duplicated_angularVelocity: boolean, duplicated_degree: boolean, duplicated_action: boolean, duplicated_stopPropagation: boolean): boolean {
        if ((!duplicated_timestamp) && (value?.hasOwnProperty("timestamp"))) {
            return true
        }
        else if ((!duplicated_angularVelocity) && (value?.hasOwnProperty("angularVelocity"))) {
            return true
        }
        else if ((!duplicated_degree) && (value?.hasOwnProperty("degree"))) {
            return true
        }
        else if ((!duplicated_action) && (value?.hasOwnProperty("action"))) {
            return true
        }
        else if ((!duplicated_stopPropagation) && (value?.hasOwnProperty("stopPropagation"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof CrownEvent")
        }
    }
    static isCrownSensitivity(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (CrownSensitivity.LOW)) {
            return true
        }
        else if ((value) === (CrownSensitivity.MEDIUM)) {
            return true
        }
        else if ((value) === (CrownSensitivity.HIGH)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof CrownSensitivity")
        }
    }
    static isCurrentDayStyle(value: Object | string | number | undefined | boolean, duplicated_dayColor: boolean, duplicated_lunarColor: boolean, duplicated_markLunarColor: boolean, duplicated_dayFontSize: boolean, duplicated_lunarDayFontSize: boolean, duplicated_dayHeight: boolean, duplicated_dayWidth: boolean, duplicated_gregorianCalendarHeight: boolean, duplicated_dayYAxisOffset: boolean, duplicated_lunarDayYAxisOffset: boolean, duplicated_underscoreXAxisOffset: boolean, duplicated_underscoreYAxisOffset: boolean, duplicated_scheduleMarkerXAxisOffset: boolean, duplicated_scheduleMarkerYAxisOffset: boolean, duplicated_colSpace: boolean, duplicated_dailyFiveRowSpace: boolean, duplicated_dailySixRowSpace: boolean, duplicated_lunarHeight: boolean, duplicated_underscoreWidth: boolean, duplicated_underscoreLength: boolean, duplicated_scheduleMarkerRadius: boolean, duplicated_boundaryRowOffset: boolean, duplicated_boundaryColOffset: boolean): boolean {
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
    static isCurve(value: Object | string | number | undefined | boolean): boolean {
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
    static isCustomComponentV2(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof CustomComponentV2")
    }
    static isCustomDialogController(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof CustomDialogController")
    }
    static isCustomDialogControllerOptions(value: Object | string | number | undefined | boolean, duplicated_builder: boolean, duplicated_cancel: boolean, duplicated_autoCancel: boolean, duplicated_alignment: boolean, duplicated_offset: boolean, duplicated_customStyle: boolean, duplicated_gridCount: boolean, duplicated_maskColor: boolean, duplicated_maskRect: boolean, duplicated_openAnimation: boolean, duplicated_closeAnimation: boolean, duplicated_showInSubWindow: boolean, duplicated_backgroundColor: boolean, duplicated_cornerRadius: boolean, duplicated_isModal: boolean, duplicated_onWillDismiss: boolean, duplicated_width: boolean, duplicated_height: boolean, duplicated_borderWidth: boolean, duplicated_borderColor: boolean, duplicated_borderStyle: boolean, duplicated_shadow: boolean, duplicated_backgroundBlurStyle: boolean, duplicated_backgroundBlurStyleOptions: boolean, duplicated_backgroundEffect: boolean, duplicated_keyboardAvoidMode: boolean, duplicated_enableHoverMode: boolean, duplicated_hoverModeArea: boolean, duplicated_onDidAppear: boolean, duplicated_onDidDisappear: boolean, duplicated_onWillAppear: boolean, duplicated_onWillDisappear: boolean, duplicated_keyboardAvoidDistance: boolean, duplicated_levelMode: boolean, duplicated_levelUniqueId: boolean, duplicated_immersiveMode: boolean, duplicated_levelOrder: boolean, duplicated_focusable: boolean): boolean {
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
        else if ((!duplicated_backgroundBlurStyleOptions) && (value?.hasOwnProperty("backgroundBlurStyleOptions"))) {
            return true
        }
        else if ((!duplicated_backgroundEffect) && (value?.hasOwnProperty("backgroundEffect"))) {
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
        else if ((!duplicated_keyboardAvoidDistance) && (value?.hasOwnProperty("keyboardAvoidDistance"))) {
            return true
        }
        else if ((!duplicated_levelMode) && (value?.hasOwnProperty("levelMode"))) {
            return true
        }
        else if ((!duplicated_levelUniqueId) && (value?.hasOwnProperty("levelUniqueId"))) {
            return true
        }
        else if ((!duplicated_immersiveMode) && (value?.hasOwnProperty("immersiveMode"))) {
            return true
        }
        else if ((!duplicated_levelOrder) && (value?.hasOwnProperty("levelOrder"))) {
            return true
        }
        else if ((!duplicated_focusable) && (value?.hasOwnProperty("focusable"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof CustomDialogControllerOptions")
        }
    }
    static isCustomPopupOptions(value: Object | string | number | undefined | boolean, duplicated_builder: boolean, duplicated_placement: boolean, duplicated_popupColor: boolean, duplicated_enableArrow: boolean, duplicated_autoCancel: boolean, duplicated_onStateChange: boolean, duplicated_arrowOffset: boolean, duplicated_showInSubWindow: boolean, duplicated_mask: boolean, duplicated_targetSpace: boolean, duplicated_offset: boolean, duplicated_width: boolean, duplicated_arrowPointPosition: boolean, duplicated_arrowWidth: boolean, duplicated_arrowHeight: boolean, duplicated_radius: boolean, duplicated_shadow: boolean, duplicated_backgroundBlurStyle: boolean, duplicated_focusable: boolean, duplicated_transition: boolean, duplicated_onWillDismiss: boolean, duplicated_enableHoverMode: boolean, duplicated_followTransformOfTarget: boolean, duplicated_keyboardAvoidMode: boolean): boolean {
        if ((!duplicated_builder) && (value?.hasOwnProperty("builder"))) {
            return true
        }
        else if ((!duplicated_placement) && (value?.hasOwnProperty("placement"))) {
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
        else if ((!duplicated_keyboardAvoidMode) && (value?.hasOwnProperty("keyboardAvoidMode"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof CustomPopupOptions")
        }
    }
    static isCustomSpan(value: Object | string | number | undefined | boolean, duplicated_onMeasure: boolean, duplicated_onDraw: boolean): boolean {
        if ((!duplicated_onMeasure) && (value?.hasOwnProperty("onMeasure"))) {
            return true
        }
        else if ((!duplicated_onDraw) && (value?.hasOwnProperty("onDraw"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof CustomSpan")
        }
    }
    static isCustomSpanDrawInfo(value: Object | string | number | undefined | boolean, duplicated_x: boolean, duplicated_lineTop: boolean, duplicated_lineBottom: boolean, duplicated_baseline: boolean): boolean {
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
    static isCustomSpanMeasureInfo(value: Object | string | number | undefined | boolean, duplicated_fontSize: boolean): boolean {
        if ((!duplicated_fontSize) && (value?.hasOwnProperty("fontSize"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof CustomSpanMeasureInfo")
        }
    }
    static isCustomSpanMetrics(value: Object | string | number | undefined | boolean, duplicated_width: boolean, duplicated_height: boolean): boolean {
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
    static isCustomTheme(value: Object | string | number | undefined | boolean, duplicated_colors: boolean): boolean {
        if ((!duplicated_colors) && (value?.hasOwnProperty("colors"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof CustomTheme")
        }
    }
    static isCutEvent(value: Object | string | number | undefined | boolean, duplicated_preventDefault: boolean): boolean {
        if ((!duplicated_preventDefault) && (value?.hasOwnProperty("preventDefault"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof CutEvent")
        }
    }
    static isDataOperationType(value: Object | string | number | undefined | boolean): boolean {
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
    static isDataPanelConfiguration(value: Object | string | number | undefined | boolean, duplicated_values: boolean, duplicated_maxValue: boolean): boolean {
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
    static isDataPanelOptions(value: Object | string | number | undefined | boolean, duplicated_values: boolean, duplicated_max: boolean, duplicated_type: boolean): boolean {
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
    static isDataPanelShadowOptions(value: Object | string | number | undefined | boolean, duplicated_colors: boolean): boolean {
        if ((!duplicated_colors) && (value?.hasOwnProperty("colors"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof DataPanelShadowOptions")
        }
    }
    static isDataPanelType(value: Object | string | number | undefined | boolean): boolean {
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
    static isDataResubmissionHandler(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof DataResubmissionHandler")
    }
    static isDatePickerDialog(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof DatePickerDialog")
    }
    static isDatePickerMode(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (DatePickerMode.DATE)) {
            return true
        }
        else if ((value) === (DatePickerMode.YEAR_AND_MONTH)) {
            return true
        }
        else if ((value) === (DatePickerMode.MONTH_AND_DAY)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof DatePickerMode")
        }
    }
    static isDatePickerOptions(value: Object | string | number | undefined | boolean, duplicated_start: boolean, duplicated_end: boolean, duplicated_selected: boolean, duplicated_mode: boolean): boolean {
        if ((!duplicated_start) && (value?.hasOwnProperty("start"))) {
            return true
        }
        else if ((!duplicated_end) && (value?.hasOwnProperty("end"))) {
            return true
        }
        else if ((!duplicated_selected) && (value?.hasOwnProperty("selected"))) {
            return true
        }
        else if ((!duplicated_mode) && (value?.hasOwnProperty("mode"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof DatePickerOptions")
        }
    }
    static isDateRange(value: Object | string | number | undefined | boolean, duplicated_start: boolean, duplicated_end: boolean): boolean {
        if ((!duplicated_start) && (value?.hasOwnProperty("start"))) {
            return true
        }
        else if ((!duplicated_end) && (value?.hasOwnProperty("end"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof DateRange")
        }
    }
    static isDecorationStyle(value: Object | string | number | undefined | boolean, duplicated_type: boolean, duplicated_color: boolean, duplicated_style: boolean): boolean {
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
    static isDecorationStyleInterface(value: Object | string | number | undefined | boolean, duplicated_type: boolean, duplicated_color: boolean, duplicated_style: boolean): boolean {
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
    static isDecorationStyleResult(value: Object | string | number | undefined | boolean, duplicated_type: boolean, duplicated_color: boolean, duplicated_style: boolean): boolean {
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
    static isDeleteValue(value: Object | string | number | undefined | boolean, duplicated_deleteOffset: boolean, duplicated_direction: boolean, duplicated_deleteValue: boolean): boolean {
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
    static isDialogAlignment(value: Object | string | number | undefined | boolean): boolean {
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
    static isDialogButtonDirection(value: Object | string | number | undefined | boolean): boolean {
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
    static isDialogButtonStyle(value: Object | string | number | undefined | boolean): boolean {
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
    static isDigitIndicator(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof DigitIndicator")
    }
    static isDirection(value: Object | string | number | undefined | boolean): boolean {
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
    static isDirectionalEdgesT(value: Object | string | number | undefined | boolean, duplicated_start: boolean, duplicated_end: boolean, duplicated_top: boolean, duplicated_bottom: boolean): boolean {
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
    static isDisappearSymbolEffect(value: Object | string | number | undefined | boolean, duplicated_scope: boolean): boolean {
        if ((!duplicated_scope) && (value?.hasOwnProperty("scope"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof DisappearSymbolEffect")
        }
    }
    static isDismissContentCoverAction(value: Object | string | number | undefined | boolean, duplicated_dismiss: boolean, duplicated_reason: boolean): boolean {
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
    static isDismissDialogAction(value: Object | string | number | undefined | boolean, duplicated_dismiss: boolean, duplicated_reason: boolean): boolean {
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
    static isDismissPopupAction(value: Object | string | number | undefined | boolean, duplicated_dismiss: boolean, duplicated_reason: boolean): boolean {
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
    static isDismissReason(value: Object | string | number | undefined | boolean): boolean {
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
    static isDismissSheetAction(value: Object | string | number | undefined | boolean, duplicated_dismiss: boolean, duplicated_reason: boolean): boolean {
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
    static isDistributionType(value: Object | string | number | undefined | boolean): boolean {
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
    static isDisturbanceFieldShape(value: Object | string | number | undefined | boolean): boolean {
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
    static isDividerMode(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (DividerMode.FLOATING_ABOVE_MENU)) {
            return true
        }
        else if ((value) === (DividerMode.EMBEDDED_IN_MENU)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof DividerMode")
        }
    }
    static isDividerOptions(value: Object | string | number | undefined | boolean, duplicated_strokeWidth: boolean, duplicated_color: boolean, duplicated_startMargin: boolean, duplicated_endMargin: boolean): boolean {
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
    static isDividerStyle(value: Object | string | number | undefined | boolean, duplicated_strokeWidth: boolean, duplicated_color: boolean, duplicated_startMargin: boolean, duplicated_endMargin: boolean): boolean {
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
    static isDividerStyleOptions(value: Object | string | number | undefined | boolean, duplicated_strokeWidth: boolean, duplicated_color: boolean, duplicated_startMargin: boolean, duplicated_endMargin: boolean, duplicated_mode: boolean): boolean {
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
        else if ((!duplicated_mode) && (value?.hasOwnProperty("mode"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof DividerStyleOptions")
        }
    }
    static isDotIndicator(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof DotIndicator")
    }
    static isDoubleAnimationParam(value: Object | string | number | undefined | boolean, duplicated_propertyName: boolean, duplicated_startValue: boolean, duplicated_endValue: boolean, duplicated_duration: boolean, duplicated_delay: boolean, duplicated_curve: boolean, duplicated_onProgress: boolean, duplicated_onFinish: boolean): boolean {
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
    static isDpiFollowStrategy(value: Object | string | number | undefined | boolean): boolean {
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
    static isDragBehavior(value: Object | string | number | undefined | boolean): boolean {
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
    static isDragEvent(value: Object | string | number | undefined | boolean, duplicated_dragBehavior: boolean, duplicated_useCustomDropAnimation: boolean, duplicated_getModifierKeyState: boolean): boolean {
        if ((!duplicated_dragBehavior) && (value?.hasOwnProperty("dragBehavior"))) {
            return true
        }
        else if ((!duplicated_useCustomDropAnimation) && (value?.hasOwnProperty("useCustomDropAnimation"))) {
            return true
        }
        else if ((!duplicated_getModifierKeyState) && (value?.hasOwnProperty("getModifierKeyState"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof DragEvent")
        }
    }
    static isDraggingSizeChangeEffect(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (DraggingSizeChangeEffect.DEFAULT)) {
            return true
        }
        else if ((value) === (DraggingSizeChangeEffect.SIZE_TRANSITION)) {
            return true
        }
        else if ((value) === (DraggingSizeChangeEffect.SIZE_CONTENT_TRANSITION)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof DraggingSizeChangeEffect")
        }
    }
    static isDragInteractionOptions(value: Object | string | number | undefined | boolean, duplicated_isMultiSelectionEnabled: boolean, duplicated_defaultAnimationBeforeLifting: boolean, duplicated_enableEdgeAutoScroll: boolean, duplicated_enableHapticFeedback: boolean, duplicated_isLiftingDisabled: boolean): boolean {
        if ((!duplicated_isMultiSelectionEnabled) && (value?.hasOwnProperty("isMultiSelectionEnabled"))) {
            return true
        }
        else if ((!duplicated_defaultAnimationBeforeLifting) && (value?.hasOwnProperty("defaultAnimationBeforeLifting"))) {
            return true
        }
        else if ((!duplicated_enableEdgeAutoScroll) && (value?.hasOwnProperty("enableEdgeAutoScroll"))) {
            return true
        }
        else if ((!duplicated_enableHapticFeedback) && (value?.hasOwnProperty("enableHapticFeedback"))) {
            return true
        }
        else if ((!duplicated_isLiftingDisabled) && (value?.hasOwnProperty("isLiftingDisabled"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof DragInteractionOptions")
        }
    }
    static isDragItemInfo(value: Object | string | number | undefined | boolean, duplicated_pixelMap: boolean, duplicated_builder: boolean, duplicated_extraInfo: boolean): boolean {
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
    static isDragPreviewMode(value: Object | string | number | undefined | boolean): boolean {
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
        else if ((value) === (DragPreviewMode.ENABLE_DRAG_ITEM_GRAY_EFFECT)) {
            return true
        }
        else if ((value) === (DragPreviewMode.ENABLE_MULTI_TILE_EFFECT)) {
            return true
        }
        else if ((value) === (DragPreviewMode.ENABLE_TOUCH_POINT_CALCULATION_BASED_ON_FINAL_PREVIEW)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof DragPreviewMode")
        }
    }
    static isDragPreviewOptions(value: Object | string | number | undefined | boolean, duplicated_mode: boolean, duplicated_numberBadge: boolean, duplicated_sizeChangeEffect: boolean): boolean {
        if ((!duplicated_mode) && (value?.hasOwnProperty("mode"))) {
            return true
        }
        else if ((!duplicated_numberBadge) && (value?.hasOwnProperty("numberBadge"))) {
            return true
        }
        else if ((!duplicated_sizeChangeEffect) && (value?.hasOwnProperty("sizeChangeEffect"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof DragPreviewOptions")
        }
    }
    static isDragResult(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (DragResult.UNKNOWN)) {
            return true
        }
        else if ((value) === (DragResult.DRAG_SUCCESSFUL)) {
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
    static isDrawableDescriptor(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof DrawableDescriptor")
    }
    static isDrawContext(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof DrawContext")
    }
    static isdrawing_BlendMode(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (drawing.BlendMode.CLEAR)) {
            return true
        }
        else if ((value) === (drawing.BlendMode.SRC)) {
            return true
        }
        else if ((value) === (drawing.BlendMode.DST)) {
            return true
        }
        else if ((value) === (drawing.BlendMode.SRC_OVER)) {
            return true
        }
        else if ((value) === (drawing.BlendMode.DST_OVER)) {
            return true
        }
        else if ((value) === (drawing.BlendMode.SRC_IN)) {
            return true
        }
        else if ((value) === (drawing.BlendMode.DST_IN)) {
            return true
        }
        else if ((value) === (drawing.BlendMode.SRC_OUT)) {
            return true
        }
        else if ((value) === (drawing.BlendMode.DST_OUT)) {
            return true
        }
        else if ((value) === (drawing.BlendMode.SRC_ATOP)) {
            return true
        }
        else if ((value) === (drawing.BlendMode.DST_ATOP)) {
            return true
        }
        else if ((value) === (drawing.BlendMode.XOR)) {
            return true
        }
        else if ((value) === (drawing.BlendMode.PLUS)) {
            return true
        }
        else if ((value) === (drawing.BlendMode.MODULATE)) {
            return true
        }
        else if ((value) === (drawing.BlendMode.SCREEN)) {
            return true
        }
        else if ((value) === (drawing.BlendMode.OVERLAY)) {
            return true
        }
        else if ((value) === (drawing.BlendMode.DARKEN)) {
            return true
        }
        else if ((value) === (drawing.BlendMode.LIGHTEN)) {
            return true
        }
        else if ((value) === (drawing.BlendMode.COLOR_DODGE)) {
            return true
        }
        else if ((value) === (drawing.BlendMode.COLOR_BURN)) {
            return true
        }
        else if ((value) === (drawing.BlendMode.HARD_LIGHT)) {
            return true
        }
        else if ((value) === (drawing.BlendMode.SOFT_LIGHT)) {
            return true
        }
        else if ((value) === (drawing.BlendMode.DIFFERENCE)) {
            return true
        }
        else if ((value) === (drawing.BlendMode.EXCLUSION)) {
            return true
        }
        else if ((value) === (drawing.BlendMode.MULTIPLY)) {
            return true
        }
        else if ((value) === (drawing.BlendMode.HUE)) {
            return true
        }
        else if ((value) === (drawing.BlendMode.SATURATION)) {
            return true
        }
        else if ((value) === (drawing.BlendMode.COLOR)) {
            return true
        }
        else if ((value) === (drawing.BlendMode.LUMINOSITY)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof drawing.BlendMode")
        }
    }
    static isdrawing_BlurType(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (drawing.BlurType.NORMAL)) {
            return true
        }
        else if ((value) === (drawing.BlurType.SOLID)) {
            return true
        }
        else if ((value) === (drawing.BlurType.OUTER)) {
            return true
        }
        else if ((value) === (drawing.BlurType.INNER)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof drawing.BlurType")
        }
    }
    static isdrawing_Brush(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof drawing.Brush")
    }
    static isdrawing_Canvas(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof drawing.Canvas")
    }
    static isdrawing_CapStyle(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (drawing.CapStyle.FLAT_CAP)) {
            return true
        }
        else if ((value) === (drawing.CapStyle.SQUARE_CAP)) {
            return true
        }
        else if ((value) === (drawing.CapStyle.ROUND_CAP)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof drawing.CapStyle")
        }
    }
    static isdrawing_ClipOp(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (drawing.ClipOp.DIFFERENCE)) {
            return true
        }
        else if ((value) === (drawing.ClipOp.INTERSECT)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof drawing.ClipOp")
        }
    }
    static isdrawing_ColorFilter(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof drawing.ColorFilter")
    }
    static isdrawing_CornerPos(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (drawing.CornerPos.TOP_LEFT_POS)) {
            return true
        }
        else if ((value) === (drawing.CornerPos.TOP_RIGHT_POS)) {
            return true
        }
        else if ((value) === (drawing.CornerPos.BOTTOM_RIGHT_POS)) {
            return true
        }
        else if ((value) === (drawing.CornerPos.BOTTOM_LEFT_POS)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof drawing.CornerPos")
        }
    }
    static isdrawing_FilterMode(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (drawing.FilterMode.FILTER_MODE_NEAREST)) {
            return true
        }
        else if ((value) === (drawing.FilterMode.FILTER_MODE_LINEAR)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof drawing.FilterMode")
        }
    }
    static isdrawing_Font(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof drawing.Font")
    }
    static isdrawing_FontEdging(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (drawing.FontEdging.ALIAS)) {
            return true
        }
        else if ((value) === (drawing.FontEdging.ANTI_ALIAS)) {
            return true
        }
        else if ((value) === (drawing.FontEdging.SUBPIXEL_ANTI_ALIAS)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof drawing.FontEdging")
        }
    }
    static isdrawing_FontHinting(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (drawing.FontHinting.NONE)) {
            return true
        }
        else if ((value) === (drawing.FontHinting.SLIGHT)) {
            return true
        }
        else if ((value) === (drawing.FontHinting.NORMAL)) {
            return true
        }
        else if ((value) === (drawing.FontHinting.FULL)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof drawing.FontHinting")
        }
    }
    static isdrawing_FontMetrics(value: Object | string | number | undefined | boolean, duplicated_flags: boolean, duplicated_top: boolean, duplicated_ascent: boolean, duplicated_descent: boolean, duplicated_bottom: boolean, duplicated_leading: boolean, duplicated_avgCharWidth: boolean, duplicated_maxCharWidth: boolean, duplicated_xMin: boolean, duplicated_xMax: boolean, duplicated_xHeight: boolean, duplicated_capHeight: boolean, duplicated_underlineThickness: boolean, duplicated_underlinePosition: boolean, duplicated_strikethroughThickness: boolean, duplicated_strikethroughPosition: boolean): boolean {
        if ((!duplicated_top) && (value?.hasOwnProperty("top"))) {
            return true
        }
        else if ((!duplicated_ascent) && (value?.hasOwnProperty("ascent"))) {
            return true
        }
        else if ((!duplicated_descent) && (value?.hasOwnProperty("descent"))) {
            return true
        }
        else if ((!duplicated_bottom) && (value?.hasOwnProperty("bottom"))) {
            return true
        }
        else if ((!duplicated_leading) && (value?.hasOwnProperty("leading"))) {
            return true
        }
        else if ((!duplicated_flags) && (value?.hasOwnProperty("flags"))) {
            return true
        }
        else if ((!duplicated_avgCharWidth) && (value?.hasOwnProperty("avgCharWidth"))) {
            return true
        }
        else if ((!duplicated_maxCharWidth) && (value?.hasOwnProperty("maxCharWidth"))) {
            return true
        }
        else if ((!duplicated_xMin) && (value?.hasOwnProperty("xMin"))) {
            return true
        }
        else if ((!duplicated_xMax) && (value?.hasOwnProperty("xMax"))) {
            return true
        }
        else if ((!duplicated_xHeight) && (value?.hasOwnProperty("xHeight"))) {
            return true
        }
        else if ((!duplicated_capHeight) && (value?.hasOwnProperty("capHeight"))) {
            return true
        }
        else if ((!duplicated_underlineThickness) && (value?.hasOwnProperty("underlineThickness"))) {
            return true
        }
        else if ((!duplicated_underlinePosition) && (value?.hasOwnProperty("underlinePosition"))) {
            return true
        }
        else if ((!duplicated_strikethroughThickness) && (value?.hasOwnProperty("strikethroughThickness"))) {
            return true
        }
        else if ((!duplicated_strikethroughPosition) && (value?.hasOwnProperty("strikethroughPosition"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof drawing.FontMetrics")
        }
    }
    static isdrawing_FontMetricsFlags(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (drawing.FontMetricsFlags.UNDERLINE_THICKNESS_VALID)) {
            return true
        }
        else if ((value) === (drawing.FontMetricsFlags.UNDERLINE_POSITION_VALID)) {
            return true
        }
        else if ((value) === (drawing.FontMetricsFlags.STRIKETHROUGH_THICKNESS_VALID)) {
            return true
        }
        else if ((value) === (drawing.FontMetricsFlags.STRIKETHROUGH_POSITION_VALID)) {
            return true
        }
        else if ((value) === (drawing.FontMetricsFlags.BOUNDS_INVALID)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof drawing.FontMetricsFlags")
        }
    }
    static isdrawing_ImageFilter(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof drawing.ImageFilter")
    }
    static isdrawing_JoinStyle(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (drawing.JoinStyle.MITER_JOIN)) {
            return true
        }
        else if ((value) === (drawing.JoinStyle.ROUND_JOIN)) {
            return true
        }
        else if ((value) === (drawing.JoinStyle.BEVEL_JOIN)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof drawing.JoinStyle")
        }
    }
    static isdrawing_Lattice(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof drawing.Lattice")
    }
    static isdrawing_MaskFilter(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof drawing.MaskFilter")
    }
    static isdrawing_Matrix(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof drawing.Matrix")
    }
    static isdrawing_Path(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof drawing.Path")
    }
    static isdrawing_PathDirection(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (drawing.PathDirection.CLOCKWISE)) {
            return true
        }
        else if ((value) === (drawing.PathDirection.COUNTER_CLOCKWISE)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof drawing.PathDirection")
        }
    }
    static isdrawing_PathEffect(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof drawing.PathEffect")
    }
    static isdrawing_PathFillType(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (drawing.PathFillType.WINDING)) {
            return true
        }
        else if ((value) === (drawing.PathFillType.EVEN_ODD)) {
            return true
        }
        else if ((value) === (drawing.PathFillType.INVERSE_WINDING)) {
            return true
        }
        else if ((value) === (drawing.PathFillType.INVERSE_EVEN_ODD)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof drawing.PathFillType")
        }
    }
    static isdrawing_PathMeasureMatrixFlags(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (drawing.PathMeasureMatrixFlags.GET_POSITION_MATRIX)) {
            return true
        }
        else if ((value) === (drawing.PathMeasureMatrixFlags.GET_TANGENT_MATRIX)) {
            return true
        }
        else if ((value) === (drawing.PathMeasureMatrixFlags.GET_POSITION_AND_TANGENT_MATRIX)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof drawing.PathMeasureMatrixFlags")
        }
    }
    static isdrawing_PathOp(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (drawing.PathOp.DIFFERENCE)) {
            return true
        }
        else if ((value) === (drawing.PathOp.INTERSECT)) {
            return true
        }
        else if ((value) === (drawing.PathOp.UNION)) {
            return true
        }
        else if ((value) === (drawing.PathOp.XOR)) {
            return true
        }
        else if ((value) === (drawing.PathOp.REVERSE_DIFFERENCE)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof drawing.PathOp")
        }
    }
    static isdrawing_Pen(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof drawing.Pen")
    }
    static isdrawing_PointMode(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (drawing.PointMode.POINTS)) {
            return true
        }
        else if ((value) === (drawing.PointMode.LINES)) {
            return true
        }
        else if ((value) === (drawing.PointMode.POLYGON)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof drawing.PointMode")
        }
    }
    static isdrawing_RectType(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (drawing.RectType.DEFAULT)) {
            return true
        }
        else if ((value) === (drawing.RectType.TRANSPARENT)) {
            return true
        }
        else if ((value) === (drawing.RectType.FIXEDCOLOR)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof drawing.RectType")
        }
    }
    static isdrawing_Region(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof drawing.Region")
    }
    static isdrawing_RegionOp(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (drawing.RegionOp.DIFFERENCE)) {
            return true
        }
        else if ((value) === (drawing.RegionOp.INTERSECT)) {
            return true
        }
        else if ((value) === (drawing.RegionOp.UNION)) {
            return true
        }
        else if ((value) === (drawing.RegionOp.XOR)) {
            return true
        }
        else if ((value) === (drawing.RegionOp.REVERSE_DIFFERENCE)) {
            return true
        }
        else if ((value) === (drawing.RegionOp.REPLACE)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof drawing.RegionOp")
        }
    }
    static isdrawing_RoundRect(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof drawing.RoundRect")
    }
    static isdrawing_SamplingOptions(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof drawing.SamplingOptions")
    }
    static isdrawing_ScaleToFit(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (drawing.ScaleToFit.FILL_SCALE_TO_FIT)) {
            return true
        }
        else if ((value) === (drawing.ScaleToFit.START_SCALE_TO_FIT)) {
            return true
        }
        else if ((value) === (drawing.ScaleToFit.CENTER_SCALE_TO_FIT)) {
            return true
        }
        else if ((value) === (drawing.ScaleToFit.END_SCALE_TO_FIT)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof drawing.ScaleToFit")
        }
    }
    static isdrawing_ShaderEffect(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof drawing.ShaderEffect")
    }
    static isdrawing_ShadowFlag(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (drawing.ShadowFlag.NONE)) {
            return true
        }
        else if ((value) === (drawing.ShadowFlag.TRANSPARENT_OCCLUDER)) {
            return true
        }
        else if ((value) === (drawing.ShadowFlag.GEOMETRIC_ONLY)) {
            return true
        }
        else if ((value) === (drawing.ShadowFlag.ALL)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof drawing.ShadowFlag")
        }
    }
    static isdrawing_ShadowLayer(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof drawing.ShadowLayer")
    }
    static isdrawing_SrcRectConstraint(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (drawing.SrcRectConstraint.STRICT)) {
            return true
        }
        else if ((value) === (drawing.SrcRectConstraint.FAST)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof drawing.SrcRectConstraint")
        }
    }
    static isdrawing_TextBlob(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof drawing.TextBlob")
    }
    static isdrawing_TextBlobRunBuffer(value: Object | string | number | undefined | boolean, duplicated_glyph: boolean, duplicated_positionX: boolean, duplicated_positionY: boolean): boolean {
        if ((!duplicated_glyph) && (value?.hasOwnProperty("glyph"))) {
            return true
        }
        else if ((!duplicated_positionX) && (value?.hasOwnProperty("positionX"))) {
            return true
        }
        else if ((!duplicated_positionY) && (value?.hasOwnProperty("positionY"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof drawing.TextBlobRunBuffer")
        }
    }
    static isdrawing_TextEncoding(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (drawing.TextEncoding.TEXT_ENCODING_UTF8)) {
            return true
        }
        else if ((value) === (drawing.TextEncoding.TEXT_ENCODING_UTF16)) {
            return true
        }
        else if ((value) === (drawing.TextEncoding.TEXT_ENCODING_UTF32)) {
            return true
        }
        else if ((value) === (drawing.TextEncoding.TEXT_ENCODING_GLYPH_ID)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof drawing.TextEncoding")
        }
    }
    static isdrawing_TileMode(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (drawing.TileMode.CLAMP)) {
            return true
        }
        else if ((value) === (drawing.TileMode.REPEAT)) {
            return true
        }
        else if ((value) === (drawing.TileMode.MIRROR)) {
            return true
        }
        else if ((value) === (drawing.TileMode.DECAL)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof drawing.TileMode")
        }
    }
    static isdrawing_Typeface(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof drawing.Typeface")
    }
    static isDrawingRenderingContext(value: Object | string | number | undefined | boolean, duplicated_size: boolean): boolean {
        if ((!duplicated_size) && (value?.hasOwnProperty("size"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof DrawingRenderingContext")
        }
    }
    static isDrawModifier(value: Object | string | number | undefined | boolean, duplicated_drawBehind_callback: boolean, duplicated_drawContent_callback: boolean, duplicated_drawFront_callback: boolean): boolean {
        if ((!duplicated_drawBehind_callback) && (value?.hasOwnProperty("drawBehind_callback"))) {
            return true
        }
        else if ((!duplicated_drawContent_callback) && (value?.hasOwnProperty("drawContent_callback"))) {
            return true
        }
        else if ((!duplicated_drawFront_callback) && (value?.hasOwnProperty("drawFront_callback"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof DrawModifier")
        }
    }
    static isDropOptions(value: Object | string | number | undefined | boolean, duplicated_disableDataPrefetch: boolean): boolean {
        if ((!duplicated_disableDataPrefetch) && (value?.hasOwnProperty("disableDataPrefetch"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof DropOptions")
        }
    }
    static isDynamicRangeMode(value: Object | string | number | undefined | boolean): boolean {
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
    static isEdge(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (Edge.Top)) {
            return true
        }
        else if ((value) === (Edge.Bottom)) {
            return true
        }
        else if ((value) === (Edge.Start)) {
            return true
        }
        else if ((value) === (Edge.End)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof Edge")
        }
    }
    static isEdgeColors(value: Object | string | number | undefined | boolean, duplicated_top: boolean, duplicated_right: boolean, duplicated_bottom: boolean, duplicated_left: boolean): boolean {
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
    static isEdgeEffect(value: Object | string | number | undefined | boolean): boolean {
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
    static isEdgeEffectOptions(value: Object | string | number | undefined | boolean, duplicated_alwaysEnabled: boolean, duplicated_effectEdge: boolean): boolean {
        if ((!duplicated_alwaysEnabled) && (value?.hasOwnProperty("alwaysEnabled"))) {
            return true
        }
        else if ((!duplicated_effectEdge) && (value?.hasOwnProperty("effectEdge"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof EdgeEffectOptions")
        }
    }
    static isEdgeOutlineStyles(value: Object | string | number | undefined | boolean, duplicated_top: boolean, duplicated_right: boolean, duplicated_bottom: boolean, duplicated_left: boolean): boolean {
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
    static isEdgeOutlineWidths(value: Object | string | number | undefined | boolean, duplicated_top: boolean, duplicated_right: boolean, duplicated_bottom: boolean, duplicated_left: boolean): boolean {
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
    static isEdges(value: Object | string | number | undefined | boolean, duplicated_top: boolean, duplicated_left: boolean, duplicated_bottom: boolean, duplicated_right: boolean): boolean {
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
    static isEdgeStyles(value: Object | string | number | undefined | boolean, duplicated_top: boolean, duplicated_right: boolean, duplicated_bottom: boolean, duplicated_left: boolean): boolean {
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
    static isEdgeWidths(value: Object | string | number | undefined | boolean, duplicated_top: boolean, duplicated_right: boolean, duplicated_bottom: boolean, duplicated_left: boolean): boolean {
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
    static isEditableTextChangeValue(value: Object | string | number | undefined | boolean, duplicated_content: boolean, duplicated_previewText: boolean, duplicated_options: boolean): boolean {
        if ((!duplicated_content) && (value?.hasOwnProperty("content"))) {
            return true
        }
        else if ((!duplicated_previewText) && (value?.hasOwnProperty("previewText"))) {
            return true
        }
        else if ((!duplicated_options) && (value?.hasOwnProperty("options"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof EditableTextChangeValue")
        }
    }
    static isEditMenuOptions(value: Object | string | number | undefined | boolean, duplicated_onCreateMenu: boolean, duplicated_onMenuItemClick: boolean): boolean {
        if ((!duplicated_onCreateMenu) && (value?.hasOwnProperty("onCreateMenu"))) {
            return true
        }
        else if ((!duplicated_onMenuItemClick) && (value?.hasOwnProperty("onMenuItemClick"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof EditMenuOptions")
        }
    }
    static isEffectDirection(value: Object | string | number | undefined | boolean): boolean {
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
    static isEffectEdge(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (EffectEdge.START)) {
            return true
        }
        else if ((value) === (EffectEdge.END)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof EffectEdge")
        }
    }
    static isEffectFillStyle(value: Object | string | number | undefined | boolean): boolean {
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
    static isEffectScope(value: Object | string | number | undefined | boolean): boolean {
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
    static isEffectType(value: Object | string | number | undefined | boolean): boolean {
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
    static isEllipseOptions(value: Object | string | number | undefined | boolean, duplicated_width: boolean, duplicated_height: boolean): boolean {
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
    static isEllipseShape(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof EllipseShape")
    }
    static isEllipsisMode(value: Object | string | number | undefined | boolean): boolean {
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
    static isEmbeddedType(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (EmbeddedType.EMBEDDED_UI_EXTENSION)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof EmbeddedType")
        }
    }
    static isEmbedOptions(value: Object | string | number | undefined | boolean, duplicated_supportDefaultIntrinsicSize: boolean): boolean {
        if ((!duplicated_supportDefaultIntrinsicSize) && (value?.hasOwnProperty("supportDefaultIntrinsicSize"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof EmbedOptions")
        }
    }
    static isEnterKeyType(value: Object | string | number | undefined | boolean): boolean {
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
    static isErrorEvent(value: Object | string | number | undefined | boolean, duplicated_message: boolean, duplicated_filename: boolean, duplicated_lineno: boolean, duplicated_colno: boolean, duplicated_error: boolean): boolean {
        if ((!duplicated_message) && (value?.hasOwnProperty("message"))) {
            return true
        }
        else if ((!duplicated_filename) && (value?.hasOwnProperty("filename"))) {
            return true
        }
        else if ((!duplicated_lineno) && (value?.hasOwnProperty("lineno"))) {
            return true
        }
        else if ((!duplicated_colno) && (value?.hasOwnProperty("colno"))) {
            return true
        }
        else if ((!duplicated_error) && (value?.hasOwnProperty("error"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ErrorEvent")
        }
    }
    static isErrorInformation(value: Object | string | number | undefined | boolean, duplicated_errcode: boolean, duplicated_msg: boolean): boolean {
        if ((!duplicated_errcode) && (value?.hasOwnProperty("errcode"))) {
            return true
        }
        else if ((!duplicated_msg) && (value?.hasOwnProperty("msg"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ErrorInformation")
        }
    }
    static isEvent(value: Object | string | number | undefined | boolean, duplicated_type: boolean, duplicated_timeStamp: boolean): boolean {
        if ((!duplicated_type) && (value?.hasOwnProperty("type"))) {
            return true
        }
        else if ((!duplicated_timeStamp) && (value?.hasOwnProperty("timeStamp"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof Event")
        }
    }
    static isEventResult(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof EventResult")
    }
    static isEventTarget(value: Object | string | number | undefined | boolean, duplicated_area: boolean, duplicated_id: boolean): boolean {
        if ((!duplicated_area) && (value?.hasOwnProperty("area"))) {
            return true
        }
        else if ((!duplicated_id) && (value?.hasOwnProperty("id"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof EventTarget")
        }
    }
    static isEventTargetInfo(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof EventTargetInfo")
    }
    static isExpectedFrameRateRange(value: Object | string | number | undefined | boolean, duplicated_min: boolean, duplicated_max: boolean, duplicated_expected: boolean): boolean {
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
    static isExtendableComponent(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof ExtendableComponent")
    }
    static isFadingEdgeOptions(value: Object | string | number | undefined | boolean, duplicated_fadingEdgeLength: boolean): boolean {
        if ((!duplicated_fadingEdgeLength) && (value?.hasOwnProperty("fadingEdgeLength"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof FadingEdgeOptions")
        }
    }
    static isFileSelectorMode(value: Object | string | number | undefined | boolean): boolean {
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
    static isFileSelectorParam(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof FileSelectorParam")
    }
    static isFileSelectorResult(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof FileSelectorResult")
    }
    static isFillMode(value: Object | string | number | undefined | boolean): boolean {
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
    static isFingerInfo(value: Object | string | number | undefined | boolean, duplicated_id: boolean, duplicated_globalX: boolean, duplicated_globalY: boolean, duplicated_localX: boolean, duplicated_localY: boolean, duplicated_displayX: boolean, duplicated_displayY: boolean, duplicated_hand: boolean): boolean {
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
        else if ((!duplicated_hand) && (value?.hasOwnProperty("hand"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof FingerInfo")
        }
    }
    static isFinishCallbackType(value: Object | string | number | undefined | boolean): boolean {
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
    static isFirstMeaningfulPaint(value: Object | string | number | undefined | boolean, duplicated_navigationStartTime: boolean, duplicated_firstMeaningfulPaintTime: boolean): boolean {
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
    static isFlexAlign(value: Object | string | number | undefined | boolean): boolean {
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
    static isFlexDirection(value: Object | string | number | undefined | boolean): boolean {
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
    static isFlexOptions(value: Object | string | number | undefined | boolean, duplicated_direction: boolean, duplicated_wrap: boolean, duplicated_justifyContent: boolean, duplicated_alignItems: boolean, duplicated_alignContent: boolean, duplicated_space: boolean): boolean {
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
    static isFlexSpaceOptions(value: Object | string | number | undefined | boolean, duplicated_main: boolean, duplicated_cross: boolean): boolean {
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
    static isFlexWrap(value: Object | string | number | undefined | boolean): boolean {
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
    static isFocusAxisEvent(value: Object | string | number | undefined | boolean, duplicated_axisMap: boolean, duplicated_stopPropagation: boolean): boolean {
        if ((!duplicated_axisMap) && (value?.hasOwnProperty("axisMap"))) {
            return true
        }
        else if ((!duplicated_stopPropagation) && (value?.hasOwnProperty("stopPropagation"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof FocusAxisEvent")
        }
    }
    static isFocusBoxStyle(value: Object | string | number | undefined | boolean, duplicated_margin: boolean, duplicated_strokeColor: boolean, duplicated_strokeWidth: boolean): boolean {
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
    static isFocusDrawLevel(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (FocusDrawLevel.SELF)) {
            return true
        }
        else if ((value) === (FocusDrawLevel.TOP)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof FocusDrawLevel")
        }
    }
    static isFocusMovement(value: Object | string | number | undefined | boolean, duplicated_forward: boolean, duplicated_backward: boolean, duplicated_up: boolean, duplicated_down: boolean, duplicated_left: boolean, duplicated_right: boolean): boolean {
        if ((!duplicated_forward) && (value?.hasOwnProperty("forward"))) {
            return true
        }
        else if ((!duplicated_backward) && (value?.hasOwnProperty("backward"))) {
            return true
        }
        else if ((!duplicated_up) && (value?.hasOwnProperty("up"))) {
            return true
        }
        else if ((!duplicated_down) && (value?.hasOwnProperty("down"))) {
            return true
        }
        else if ((!duplicated_left) && (value?.hasOwnProperty("left"))) {
            return true
        }
        else if ((!duplicated_right) && (value?.hasOwnProperty("right"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof FocusMovement")
        }
    }
    static isFocusPriority(value: Object | string | number | undefined | boolean): boolean {
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
    static isFolderStackOptions(value: Object | string | number | undefined | boolean, duplicated_upperItems: boolean): boolean {
        if ((!duplicated_upperItems) && (value?.hasOwnProperty("upperItems"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof FolderStackOptions")
        }
    }
    static isFoldStatus(value: Object | string | number | undefined | boolean): boolean {
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
    static isFont(value: Object | string | number | undefined | boolean, duplicated_size: boolean, duplicated_weight: boolean, duplicated_family: boolean, duplicated_style: boolean): boolean {
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
    static isfont_UIFontAdjustInfo(value: Object | string | number | undefined | boolean, duplicated_weight: boolean, duplicated_to: boolean): boolean {
        if ((!duplicated_weight) && (value?.hasOwnProperty("weight"))) {
            return true
        }
        else if ((!duplicated_to) && (value?.hasOwnProperty("to"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof font.UIFontAdjustInfo")
        }
    }
    static isfont_UIFontAliasInfo(value: Object | string | number | undefined | boolean, duplicated_name: boolean, duplicated_weight: boolean): boolean {
        if ((!duplicated_name) && (value?.hasOwnProperty("name"))) {
            return true
        }
        else if ((!duplicated_weight) && (value?.hasOwnProperty("weight"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof font.UIFontAliasInfo")
        }
    }
    static isfont_UIFontConfig(value: Object | string | number | undefined | boolean, duplicated_fontDir: boolean, duplicated_generic: boolean, duplicated_fallbackGroups: boolean): boolean {
        if ((!duplicated_fontDir) && (value?.hasOwnProperty("fontDir"))) {
            return true
        }
        else if ((!duplicated_generic) && (value?.hasOwnProperty("generic"))) {
            return true
        }
        else if ((!duplicated_fallbackGroups) && (value?.hasOwnProperty("fallbackGroups"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof font.UIFontConfig")
        }
    }
    static isfont_UIFontFallbackGroupInfo(value: Object | string | number | undefined | boolean, duplicated_fontSetName: boolean, duplicated_fallback: boolean): boolean {
        if ((!duplicated_fontSetName) && (value?.hasOwnProperty("fontSetName"))) {
            return true
        }
        else if ((!duplicated_fallback) && (value?.hasOwnProperty("fallback"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof font.UIFontFallbackGroupInfo")
        }
    }
    static isfont_UIFontFallbackInfo(value: Object | string | number | undefined | boolean, duplicated_language: boolean, duplicated_family: boolean): boolean {
        if ((!duplicated_language) && (value?.hasOwnProperty("language"))) {
            return true
        }
        else if ((!duplicated_family) && (value?.hasOwnProperty("family"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof font.UIFontFallbackInfo")
        }
    }
    static isfont_UIFontGenericInfo(value: Object | string | number | undefined | boolean, duplicated_family: boolean, duplicated_alias: boolean, duplicated_adjust: boolean): boolean {
        if ((!duplicated_family) && (value?.hasOwnProperty("family"))) {
            return true
        }
        else if ((!duplicated_alias) && (value?.hasOwnProperty("alias"))) {
            return true
        }
        else if ((!duplicated_adjust) && (value?.hasOwnProperty("adjust"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof font.UIFontGenericInfo")
        }
    }
    static isFontInfo(value: Object | string | number | undefined | boolean, duplicated_path: boolean, duplicated_postScriptName: boolean, duplicated_fullName: boolean, duplicated_family: boolean, duplicated_subfamily: boolean, duplicated_weight: boolean, duplicated_width: boolean, duplicated_italic: boolean, duplicated_monoSpace: boolean, duplicated_symbolic: boolean): boolean {
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
    static isFontOptions(value: Object | string | number | undefined | boolean, duplicated_familyName: boolean, duplicated_familySrc: boolean): boolean {
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
    static isFontSettingOptions(value: Object | string | number | undefined | boolean, duplicated_enableVariableFontWeight: boolean): boolean {
        if ((!duplicated_enableVariableFontWeight) && (value?.hasOwnProperty("enableVariableFontWeight"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof FontSettingOptions")
        }
    }
    static isFontStyle(value: Object | string | number | undefined | boolean): boolean {
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
    static isFontWeight(value: Object | string | number | undefined | boolean): boolean {
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
    static isForegroundBlurStyleOptions(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof ForegroundBlurStyleOptions")
    }
    static isForegroundEffectOptions(value: Object | string | number | undefined | boolean, duplicated_radius: boolean): boolean {
        if ((!duplicated_radius) && (value?.hasOwnProperty("radius"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ForegroundEffectOptions")
        }
    }
    static isFormCallbackInfo(value: Object | string | number | undefined | boolean, duplicated_id: boolean, duplicated_idString: boolean): boolean {
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
    static isFormDimension(value: Object | string | number | undefined | boolean): boolean {
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
        else if ((value) === (FormDimension.DIMENSION_1_1)) {
            return true
        }
        else if ((value) === (FormDimension.DIMENSION_6_4)) {
            return true
        }
        else if ((value) === (FormDimension.DIMENSION_2_3)) {
            return true
        }
        else if ((value) === (FormDimension.DIMENSION_3_3)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof FormDimension")
        }
    }
    static isFormInfo(value: Object | string | number | undefined | boolean, duplicated_id: boolean, duplicated_name: boolean, duplicated_bundle: boolean, duplicated_ability: boolean, duplicated_module: boolean, duplicated_dimension: boolean, duplicated_temporary: boolean, duplicated_want: boolean, duplicated_renderingMode: boolean, duplicated_shape: boolean): boolean {
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
    static isFormLinkOptions(value: Object | string | number | undefined | boolean, duplicated_action: boolean, duplicated_moduleName: boolean, duplicated_bundleName: boolean, duplicated_abilityName: boolean, duplicated_uri: boolean, duplicated_params: boolean): boolean {
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
    static isFormRenderingMode(value: Object | string | number | undefined | boolean): boolean {
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
    static isFormShape(value: Object | string | number | undefined | boolean): boolean {
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
    static isFormSize(value: Object | string | number | undefined | boolean, duplicated_width: boolean, duplicated_height: boolean): boolean {
        if ((!duplicated_width) && (value?.hasOwnProperty("width"))) {
            return true
        }
        else if ((!duplicated_height) && (value?.hasOwnProperty("height"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof FormSize")
        }
    }
    static isFrame(value: Object | string | number | undefined | boolean, duplicated_x: boolean, duplicated_y: boolean, duplicated_width: boolean, duplicated_height: boolean): boolean {
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
            throw new Error("Can not discriminate value typeof Frame")
        }
    }
    static isFrameNode(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof FrameNode")
    }
    static isFrictionMotion(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof FrictionMotion")
    }
    static isFullScreenEnterEvent(value: Object | string | number | undefined | boolean, duplicated_handler: boolean, duplicated_videoWidth: boolean, duplicated_videoHeight: boolean): boolean {
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
    static isFullScreenExitHandler(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof FullScreenExitHandler")
    }
    static isFullscreenInfo(value: Object | string | number | undefined | boolean, duplicated_fullscreen: boolean): boolean {
        if ((!duplicated_fullscreen) && (value?.hasOwnProperty("fullscreen"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof FullscreenInfo")
        }
    }
    static isFunctionKey(value: Object | string | number | undefined | boolean): boolean {
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
    static isGaugeConfiguration(value: Object | string | number | undefined | boolean, duplicated_value: boolean, duplicated_min: boolean, duplicated_max: boolean): boolean {
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
    static isGaugeIndicatorOptions(value: Object | string | number | undefined | boolean, duplicated_icon: boolean, duplicated_space: boolean): boolean {
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
    static isGaugeOptions(value: Object | string | number | undefined | boolean, duplicated_value: boolean, duplicated_min: boolean, duplicated_max: boolean): boolean {
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
    static isGaugeShadowOptions(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof GaugeShadowOptions")
    }
    static isGeometryInfo(value: Object | string | number | undefined | boolean, duplicated_borderWidth: boolean, duplicated_margin: boolean, duplicated_padding: boolean): boolean {
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
    static isGeometryTransitionOptions(value: Object | string | number | undefined | boolean, duplicated_follow: boolean, duplicated_hierarchyStrategy: boolean): boolean {
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
    static isGesture(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof Gesture")
    }
    static isGestureControl_GestureType(value: Object | string | number | undefined | boolean): boolean {
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
    static isGestureEvent(value: Object | string | number | undefined | boolean, duplicated_repeat: boolean, duplicated_fingerList: boolean, duplicated_offsetX: boolean, duplicated_offsetY: boolean, duplicated_angle: boolean, duplicated_speed: boolean, duplicated_scale: boolean, duplicated_pinchCenterX: boolean, duplicated_pinchCenterY: boolean, duplicated_velocityX: boolean, duplicated_velocityY: boolean, duplicated_velocity: boolean): boolean {
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
    static isGestureGroupInterface(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof GestureGroupInterface")
    }
    static isGestureInfo(value: Object | string | number | undefined | boolean, duplicated_tag: boolean, duplicated_type: boolean, duplicated_isSystemGesture: boolean): boolean {
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
    static isGestureJudgeResult(value: Object | string | number | undefined | boolean): boolean {
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
    static isGestureMask(value: Object | string | number | undefined | boolean): boolean {
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
    static isGestureMode(value: Object | string | number | undefined | boolean): boolean {
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
    static isGestureModifier(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof GestureModifier")
    }
    static isGesturePriority(value: Object | string | number | undefined | boolean): boolean {
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
    static isGestureRecognizer(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof GestureRecognizer")
    }
    static isGestureRecognizerState(value: Object | string | number | undefined | boolean): boolean {
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
    static isGestureStyle(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof GestureStyle")
    }
    static isGestureStyleInterface(value: Object | string | number | undefined | boolean, duplicated_onClick: boolean, duplicated_onLongPress: boolean): boolean {
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
    static isGradientDirection(value: Object | string | number | undefined | boolean): boolean {
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
    static isGridColColumnOption(value: Object | string | number | undefined | boolean, duplicated_xs: boolean, duplicated_sm: boolean, duplicated_md: boolean, duplicated_lg: boolean, duplicated_xl: boolean, duplicated_xxl: boolean): boolean {
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
    static isGridColOptions(value: Object | string | number | undefined | boolean, duplicated_span: boolean, duplicated_offset: boolean, duplicated_order: boolean): boolean {
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
    static isGridDirection(value: Object | string | number | undefined | boolean): boolean {
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
    static isGridItemAlignment(value: Object | string | number | undefined | boolean): boolean {
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
    static isGridItemOptions(value: Object | string | number | undefined | boolean, duplicated_style: boolean): boolean {
        if ((!duplicated_style) && (value?.hasOwnProperty("style"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof GridItemOptions")
        }
    }
    static isGridItemStyle(value: Object | string | number | undefined | boolean): boolean {
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
    static isGridLayoutOptions(value: Object | string | number | undefined | boolean, duplicated_regularSize: boolean, duplicated_irregularIndexes: boolean, duplicated_onGetIrregularSizeByIndex: boolean, duplicated_onGetRectByIndex: boolean): boolean {
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
    static isGridRowColumnOption(value: Object | string | number | undefined | boolean, duplicated_xs: boolean, duplicated_sm: boolean, duplicated_md: boolean, duplicated_lg: boolean, duplicated_xl: boolean, duplicated_xxl: boolean): boolean {
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
    static isGridRowDirection(value: Object | string | number | undefined | boolean): boolean {
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
    static isGridRowOptions(value: Object | string | number | undefined | boolean, duplicated_gutter: boolean, duplicated_columns: boolean, duplicated_breakpoints: boolean, duplicated_direction: boolean): boolean {
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
    static isGridRowSizeOption(value: Object | string | number | undefined | boolean, duplicated_xs: boolean, duplicated_sm: boolean, duplicated_md: boolean, duplicated_lg: boolean, duplicated_xl: boolean, duplicated_xxl: boolean): boolean {
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
    static isGuideLinePosition(value: Object | string | number | undefined | boolean, duplicated_start: boolean, duplicated_end: boolean): boolean {
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
    static isGuideLineStyle(value: Object | string | number | undefined | boolean, duplicated_id: boolean, duplicated_direction: boolean, duplicated_position: boolean): boolean {
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
    static isGutterOption(value: Object | string | number | undefined | boolean, duplicated_x: boolean, duplicated_y: boolean): boolean {
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
    static isHapticFeedbackMode(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (HapticFeedbackMode.DISABLED)) {
            return true
        }
        else if ((value) === (HapticFeedbackMode.ENABLED)) {
            return true
        }
        else if ((value) === (HapticFeedbackMode.AUTO)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof HapticFeedbackMode")
        }
    }
    static isHeader(value: Object | string | number | undefined | boolean, duplicated_headerKey: boolean, duplicated_headerValue: boolean): boolean {
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
    static isHeightBreakpoint(value: Object | string | number | undefined | boolean): boolean {
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
    static isHierarchicalSymbolEffect(value: Object | string | number | undefined | boolean, duplicated_fillStyle: boolean): boolean {
        if ((!duplicated_fillStyle) && (value?.hasOwnProperty("fillStyle"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof HierarchicalSymbolEffect")
        }
    }
    static isHistoricalPoint(value: Object | string | number | undefined | boolean, duplicated_touchObject: boolean, duplicated_size: boolean, duplicated_force: boolean, duplicated_timestamp: boolean): boolean {
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
    static isHitTestMode(value: Object | string | number | undefined | boolean): boolean {
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
    static isHitTestType(value: Object | string | number | undefined | boolean): boolean {
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
    static isHorizontalAlign(value: Object | string | number | undefined | boolean): boolean {
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
    static isHoverEffect(value: Object | string | number | undefined | boolean): boolean {
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
    static isHoverEvent(value: Object | string | number | undefined | boolean, duplicated_x: boolean, duplicated_y: boolean, duplicated_windowX: boolean, duplicated_windowY: boolean, duplicated_displayX: boolean, duplicated_displayY: boolean, duplicated_stopPropagation: boolean): boolean {
        if ((!duplicated_stopPropagation) && (value?.hasOwnProperty("stopPropagation"))) {
            return true
        }
        else if ((!duplicated_x) && (value?.hasOwnProperty("x"))) {
            return true
        }
        else if ((!duplicated_y) && (value?.hasOwnProperty("y"))) {
            return true
        }
        else if ((!duplicated_windowX) && (value?.hasOwnProperty("windowX"))) {
            return true
        }
        else if ((!duplicated_windowY) && (value?.hasOwnProperty("windowY"))) {
            return true
        }
        else if ((!duplicated_displayX) && (value?.hasOwnProperty("displayX"))) {
            return true
        }
        else if ((!duplicated_displayY) && (value?.hasOwnProperty("displayY"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof HoverEvent")
        }
    }
    static isHoverEventParam(value: Object | string | number | undefined | boolean, duplicated_foldStatus: boolean, duplicated_isHoverMode: boolean, duplicated_appRotation: boolean, duplicated_windowStatusType: boolean): boolean {
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
    static isHoverModeAreaType(value: Object | string | number | undefined | boolean): boolean {
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
    static isHttpAuthHandler(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof HttpAuthHandler")
    }
    static isIconOptions(value: Object | string | number | undefined | boolean, duplicated_size: boolean, duplicated_color: boolean, duplicated_src: boolean): boolean {
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
    static isICurve(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof ICurve")
    }
    static isIlluminatedType(value: Object | string | number | undefined | boolean): boolean {
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
    static isimage_PixelMap(value: Object | string | number | undefined | boolean, duplicated_isEditable: boolean, duplicated_isStrideAlignment: boolean): boolean {
        if ((!duplicated_isEditable) && (value?.hasOwnProperty("isEditable"))) {
            return true
        }
        else if ((!duplicated_isStrideAlignment) && (value?.hasOwnProperty("isStrideAlignment"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof image.PixelMap")
        }
    }
    static isimage_ResolutionQuality(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (image.ResolutionQuality.LOW)) {
            return true
        }
        else if ((value) === (image.ResolutionQuality.MEDIUM)) {
            return true
        }
        else if ((value) === (image.ResolutionQuality.HIGH)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof image.ResolutionQuality")
        }
    }
    static isImageAIOptions(value: Object | string | number | undefined | boolean, duplicated_types: boolean, duplicated_aiController: boolean): boolean {
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
    static isImageAnalyzerConfig(value: Object | string | number | undefined | boolean, duplicated_types: boolean): boolean {
        if ((!duplicated_types) && (value?.hasOwnProperty("types"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ImageAnalyzerConfig")
        }
    }
    static isImageAnalyzerController(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof ImageAnalyzerController")
    }
    static isImageAnalyzerType(value: Object | string | number | undefined | boolean): boolean {
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
    static isImageAttachment(value: Object | string | number | undefined | boolean, duplicated_value: boolean, duplicated_size: boolean, duplicated_verticalAlign: boolean, duplicated_objectFit: boolean, duplicated_layoutStyle: boolean, duplicated_colorFilter: boolean): boolean {
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
        else if ((!duplicated_colorFilter) && (value?.hasOwnProperty("colorFilter"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ImageAttachment")
        }
    }
    static isImageAttachmentInterface(value: Object | string | number | undefined | boolean, duplicated_value: boolean, duplicated_size: boolean, duplicated_verticalAlign: boolean, duplicated_objectFit: boolean, duplicated_layoutStyle: boolean, duplicated_colorFilter: boolean): boolean {
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
        else if ((!duplicated_colorFilter) && (value?.hasOwnProperty("colorFilter"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ImageAttachmentInterface")
        }
    }
    static isImageAttachmentLayoutStyle(value: Object | string | number | undefined | boolean, duplicated_margin: boolean, duplicated_padding: boolean, duplicated_borderRadius: boolean): boolean {
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
    static isImageBitmap(value: Object | string | number | undefined | boolean, duplicated_height: boolean, duplicated_width: boolean): boolean {
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
    static isImageCompleteEvent(value: Object | string | number | undefined | boolean, duplicated_width: boolean, duplicated_height: boolean, duplicated_componentWidth: boolean, duplicated_componentHeight: boolean, duplicated_loadingStatus: boolean, duplicated_contentWidth: boolean, duplicated_contentHeight: boolean, duplicated_contentOffsetX: boolean, duplicated_contentOffsetY: boolean): boolean {
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
            throw new Error("Can not discriminate value typeof ImageCompleteEvent")
        }
    }
    static isImageContent(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (ImageContent.EMPTY)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ImageContent")
        }
    }
    static isImageData(value: Object | string | number | undefined | boolean, duplicated_data: boolean, duplicated_height: boolean, duplicated_width: boolean): boolean {
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
    static isImageError(value: Object | string | number | undefined | boolean, duplicated_componentWidth: boolean, duplicated_componentHeight: boolean, duplicated_message: boolean, duplicated_error: boolean): boolean {
        if ((!duplicated_componentWidth) && (value?.hasOwnProperty("componentWidth"))) {
            return true
        }
        else if ((!duplicated_componentHeight) && (value?.hasOwnProperty("componentHeight"))) {
            return true
        }
        else if ((!duplicated_message) && (value?.hasOwnProperty("message"))) {
            return true
        }
        else if ((!duplicated_error) && (value?.hasOwnProperty("error"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ImageError")
        }
    }
    static isImageFit(value: Object | string | number | undefined | boolean): boolean {
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
        else if ((value) === (ImageFit.MATRIX)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ImageFit")
        }
    }
    static isImageFrameInfo(value: Object | string | number | undefined | boolean, duplicated_src: boolean, duplicated_width: boolean, duplicated_height: boolean, duplicated_top: boolean, duplicated_left: boolean, duplicated_duration: boolean): boolean {
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
    static isImageInterpolation(value: Object | string | number | undefined | boolean): boolean {
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
    static isImageLoadResult(value: Object | string | number | undefined | boolean, duplicated_width: boolean, duplicated_height: boolean, duplicated_componentWidth: boolean, duplicated_componentHeight: boolean, duplicated_loadingStatus: boolean, duplicated_contentWidth: boolean, duplicated_contentHeight: boolean, duplicated_contentOffsetX: boolean, duplicated_contentOffsetY: boolean): boolean {
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
    static isImageRenderMode(value: Object | string | number | undefined | boolean): boolean {
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
    static isImageRepeat(value: Object | string | number | undefined | boolean): boolean {
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
    static isImageRotateOrientation(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (ImageRotateOrientation.AUTO)) {
            return true
        }
        else if ((value) === (ImageRotateOrientation.UP)) {
            return true
        }
        else if ((value) === (ImageRotateOrientation.RIGHT)) {
            return true
        }
        else if ((value) === (ImageRotateOrientation.DOWN)) {
            return true
        }
        else if ((value) === (ImageRotateOrientation.LEFT)) {
            return true
        }
        else if ((value) === (ImageRotateOrientation.UP_MIRRORED)) {
            return true
        }
        else if ((value) === (ImageRotateOrientation.RIGHT_MIRRORED)) {
            return true
        }
        else if ((value) === (ImageRotateOrientation.DOWN_MIRRORED)) {
            return true
        }
        else if ((value) === (ImageRotateOrientation.LEFT_MIRRORED)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ImageRotateOrientation")
        }
    }
    static isImageSize(value: Object | string | number | undefined | boolean): boolean {
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
    static isImageSourceSize(value: Object | string | number | undefined | boolean, duplicated_width: boolean, duplicated_height: boolean): boolean {
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
    static isImageSpanAlignment(value: Object | string | number | undefined | boolean): boolean {
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
    static isImmersiveMode(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (ImmersiveMode.DEFAULT)) {
            return true
        }
        else if ((value) === (ImmersiveMode.EXTEND)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ImmersiveMode")
        }
    }
    static isIndexerAlign(value: Object | string | number | undefined | boolean): boolean {
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
    static isIndicatorComponentController(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof IndicatorComponentController")
    }
    static isInputCounterOptions(value: Object | string | number | undefined | boolean, duplicated_thresholdPercentage: boolean, duplicated_highlightBorder: boolean): boolean {
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
    static isInputType(value: Object | string | number | undefined | boolean): boolean {
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
    static isInsertValue(value: Object | string | number | undefined | boolean, duplicated_insertOffset: boolean, duplicated_insertValue: boolean): boolean {
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
    static isIntelligentTrackingPreventionDetails(value: Object | string | number | undefined | boolean, duplicated_host: boolean, duplicated_trackerHost: boolean): boolean {
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
    static isIntentionCode(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (IntentionCode.INTENTION_UNKNOWN)) {
            return true
        }
        else if ((value) === (IntentionCode.INTENTION_UP)) {
            return true
        }
        else if ((value) === (IntentionCode.INTENTION_DOWN)) {
            return true
        }
        else if ((value) === (IntentionCode.INTENTION_LEFT)) {
            return true
        }
        else if ((value) === (IntentionCode.INTENTION_RIGHT)) {
            return true
        }
        else if ((value) === (IntentionCode.INTENTION_SELECT)) {
            return true
        }
        else if ((value) === (IntentionCode.INTENTION_ESCAPE)) {
            return true
        }
        else if ((value) === (IntentionCode.INTENTION_BACK)) {
            return true
        }
        else if ((value) === (IntentionCode.INTENTION_FORWARD)) {
            return true
        }
        else if ((value) === (IntentionCode.INTENTION_MENU)) {
            return true
        }
        else if ((value) === (IntentionCode.INTENTION_PAGE_UP)) {
            return true
        }
        else if ((value) === (IntentionCode.INTENTION_PAGE_DOWN)) {
            return true
        }
        else if ((value) === (IntentionCode.INTENTION_ZOOM_OUT)) {
            return true
        }
        else if ((value) === (IntentionCode.INTENTION_ZOOM_IN)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof IntentionCode")
        }
    }
    static isInteractionHand(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (InteractionHand.NONE)) {
            return true
        }
        else if ((value) === (InteractionHand.LEFT)) {
            return true
        }
        else if ((value) === (InteractionHand.RIGHT)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof InteractionHand")
        }
    }
    static isintl_DateTimeOptions(value: Object | string | number | undefined | boolean, duplicated_locale: boolean, duplicated_dateStyle: boolean, duplicated_timeStyle: boolean, duplicated_hourCycle: boolean, duplicated_timeZone: boolean, duplicated_numberingSystem: boolean, duplicated_hour12: boolean, duplicated_weekday: boolean, duplicated_era: boolean, duplicated_year: boolean, duplicated_month: boolean, duplicated_day: boolean, duplicated_hour: boolean, duplicated_minute: boolean, duplicated_second: boolean, duplicated_timeZoneName: boolean, duplicated_dayPeriod: boolean, duplicated_localeMatcher: boolean, duplicated_formatMatcher: boolean): boolean {
        if ((!duplicated_locale) && (value?.hasOwnProperty("locale"))) {
            return true
        }
        else if ((!duplicated_dateStyle) && (value?.hasOwnProperty("dateStyle"))) {
            return true
        }
        else if ((!duplicated_timeStyle) && (value?.hasOwnProperty("timeStyle"))) {
            return true
        }
        else if ((!duplicated_hourCycle) && (value?.hasOwnProperty("hourCycle"))) {
            return true
        }
        else if ((!duplicated_timeZone) && (value?.hasOwnProperty("timeZone"))) {
            return true
        }
        else if ((!duplicated_numberingSystem) && (value?.hasOwnProperty("numberingSystem"))) {
            return true
        }
        else if ((!duplicated_hour12) && (value?.hasOwnProperty("hour12"))) {
            return true
        }
        else if ((!duplicated_weekday) && (value?.hasOwnProperty("weekday"))) {
            return true
        }
        else if ((!duplicated_era) && (value?.hasOwnProperty("era"))) {
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
        else if ((!duplicated_hour) && (value?.hasOwnProperty("hour"))) {
            return true
        }
        else if ((!duplicated_minute) && (value?.hasOwnProperty("minute"))) {
            return true
        }
        else if ((!duplicated_second) && (value?.hasOwnProperty("second"))) {
            return true
        }
        else if ((!duplicated_timeZoneName) && (value?.hasOwnProperty("timeZoneName"))) {
            return true
        }
        else if ((!duplicated_dayPeriod) && (value?.hasOwnProperty("dayPeriod"))) {
            return true
        }
        else if ((!duplicated_localeMatcher) && (value?.hasOwnProperty("localeMatcher"))) {
            return true
        }
        else if ((!duplicated_formatMatcher) && (value?.hasOwnProperty("formatMatcher"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof intl.DateTimeOptions")
        }
    }
    static isInvertOptions(value: Object | string | number | undefined | boolean, duplicated_low: boolean, duplicated_high: boolean, duplicated_threshold: boolean, duplicated_thresholdRange: boolean): boolean {
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
    static isItemAlign(value: Object | string | number | undefined | boolean): boolean {
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
    static isItemDragInfo(value: Object | string | number | undefined | boolean, duplicated_x: boolean, duplicated_y: boolean): boolean {
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
    static isItemState(value: Object | string | number | undefined | boolean): boolean {
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
    static isJavaScriptProxy(value: Object | string | number | undefined | boolean, duplicated_object_: boolean, duplicated_name: boolean, duplicated_methodList: boolean, duplicated_controller: boolean, duplicated_asyncMethodList: boolean, duplicated_permission: boolean): boolean {
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
    static isJsGeolocation(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof JsGeolocation")
    }
    static isJsResult(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof JsResult")
    }
    static isKeyboardAppearance(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (KeyboardAppearance.NONE_IMMERSIVE)) {
            return true
        }
        else if ((value) === (KeyboardAppearance.IMMERSIVE)) {
            return true
        }
        else if ((value) === (KeyboardAppearance.LIGHT_IMMERSIVE)) {
            return true
        }
        else if ((value) === (KeyboardAppearance.DARK_IMMERSIVE)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof KeyboardAppearance")
        }
    }
    static isKeyboardAvoidMode(value: Object | string | number | undefined | boolean): boolean {
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
    static isKeyboardOptions(value: Object | string | number | undefined | boolean, duplicated_supportAvoidance: boolean): boolean {
        if ((!duplicated_supportAvoidance) && (value?.hasOwnProperty("supportAvoidance"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof KeyboardOptions")
        }
    }
    static isKeyEvent(value: Object | string | number | undefined | boolean, duplicated_type: boolean, duplicated_keyCode: boolean, duplicated_keyText: boolean, duplicated_keySource: boolean, duplicated_deviceId: boolean, duplicated_metaKey: boolean, duplicated_timestamp: boolean, duplicated_stopPropagation: boolean, duplicated_intentionCode: boolean, duplicated_getModifierKeyState: boolean, duplicated_unicode: boolean): boolean {
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
        else if ((!duplicated_getModifierKeyState) && (value?.hasOwnProperty("getModifierKeyState"))) {
            return true
        }
        else if ((!duplicated_unicode) && (value?.hasOwnProperty("unicode"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof KeyEvent")
        }
    }
    static isKeyProcessingMode(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (KeyProcessingMode.FOCUS_NAVIGATION)) {
            return true
        }
        else if ((value) === (KeyProcessingMode.ANCESTOR_EVENT)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof KeyProcessingMode")
        }
    }
    static isKeySource(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (KeySource.Unknown)) {
            return true
        }
        else if ((value) === (KeySource.Keyboard)) {
            return true
        }
        else if ((value) === (KeySource.JOYSTICK)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof KeySource")
        }
    }
    static isKeyType(value: Object | string | number | undefined | boolean): boolean {
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
    static isLargestContentfulPaint(value: Object | string | number | undefined | boolean, duplicated_navigationStartTime: boolean, duplicated_largestImagePaintTime: boolean, duplicated_largestTextPaintTime: boolean, duplicated_imageBPP: boolean, duplicated_largestImageLoadStartTime: boolean, duplicated_largestImageLoadEndTime: boolean): boolean {
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
    static isLaunchMode(value: Object | string | number | undefined | boolean): boolean {
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
    static isLayoutable(value: Object | string | number | undefined | boolean, duplicated_measureResult: boolean, duplicated_uniqueId: boolean): boolean {
        if ((!duplicated_measureResult) && (value?.hasOwnProperty("measureResult"))) {
            return true
        }
        else if ((!duplicated_uniqueId) && (value?.hasOwnProperty("uniqueId"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof Layoutable")
        }
    }
    static isLayoutCallback(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof LayoutCallback")
    }
    static isLayoutChild(value: Object | string | number | undefined | boolean, duplicated_name: boolean, duplicated_id: boolean, duplicated_position: boolean): boolean {
        if ((!duplicated_name) && (value?.hasOwnProperty("name"))) {
            return true
        }
        else if ((!duplicated_id) && (value?.hasOwnProperty("id"))) {
            return true
        }
        else if ((!duplicated_position) && (value?.hasOwnProperty("position"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof LayoutChild")
        }
    }
    static isLayoutConstraint(value: Object | string | number | undefined | boolean, duplicated_maxSize: boolean, duplicated_minSize: boolean, duplicated_percentReference: boolean): boolean {
        if ((!duplicated_maxSize) && (value?.hasOwnProperty("maxSize"))) {
            return true
        }
        else if ((!duplicated_minSize) && (value?.hasOwnProperty("minSize"))) {
            return true
        }
        else if ((!duplicated_percentReference) && (value?.hasOwnProperty("percentReference"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof LayoutConstraint")
        }
    }
    static isLayoutDirection(value: Object | string | number | undefined | boolean): boolean {
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
    static isLayoutManager(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof LayoutManager")
    }
    static isLayoutMode(value: Object | string | number | undefined | boolean): boolean {
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
    static isLayoutPolicy(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof LayoutPolicy")
    }
    static isLayoutSafeAreaEdge(value: Object | string | number | undefined | boolean): boolean {
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
    static isLayoutSafeAreaType(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (LayoutSafeAreaType.SYSTEM)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof LayoutSafeAreaType")
        }
    }
    static isLayoutStyle(value: Object | string | number | undefined | boolean): boolean {
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
    static isLeadingMarginPlaceholder(value: Object | string | number | undefined | boolean, duplicated_pixelMap: boolean, duplicated_size: boolean): boolean {
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
    static isLengthConstrain(value: Object | string | number | undefined | boolean, duplicated_minLength: boolean, duplicated_maxLength: boolean): boolean {
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
    static isLengthMetrics(value: Object | string | number | undefined | boolean, duplicated_unit: boolean, duplicated_value: boolean): boolean {
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
    static isLengthMetricsUnit(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (LengthMetricsUnit.DEFAULT)) {
            return true
        }
        else if ((value) === (LengthMetricsUnit.PX)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof LengthMetricsUnit")
        }
    }
    static isLengthUnit(value: Object | string | number | undefined | boolean): boolean {
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
    static isLetterSpacingStyle(value: Object | string | number | undefined | boolean, duplicated_letterSpacing: boolean): boolean {
        if ((!duplicated_letterSpacing) && (value?.hasOwnProperty("letterSpacing"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof LetterSpacingStyle")
        }
    }
    static isLevelMode(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (LevelMode.OVERLAY)) {
            return true
        }
        else if ((value) === (LevelMode.EMBEDDED)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof LevelMode")
        }
    }
    static isLevelOrder(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof LevelOrder")
    }
    static isLifeCycle(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof LifeCycle")
    }
    static isLightSource(value: Object | string | number | undefined | boolean, duplicated_positionX: boolean, duplicated_positionY: boolean, duplicated_positionZ: boolean, duplicated_intensity: boolean, duplicated_color: boolean): boolean {
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
    static isLinearGradient(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof LinearGradient")
    }
    static isLinearGradientBlurOptions(value: Object | string | number | undefined | boolean, duplicated_fractionStops: boolean, duplicated_direction: boolean): boolean {
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
    static isLinearGradientOptions(value: Object | string | number | undefined | boolean, duplicated_angle: boolean, duplicated_direction: boolean, duplicated_colors: boolean, duplicated_repeating: boolean): boolean {
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
            throw new Error("Can not discriminate value typeof LinearGradientOptions")
        }
    }
    static isLinearIndicatorController(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof LinearIndicatorController")
    }
    static isLinearIndicatorStartOptions(value: Object | string | number | undefined | boolean, duplicated_interval: boolean, duplicated_duration: boolean): boolean {
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
    static isLinearIndicatorStyle(value: Object | string | number | undefined | boolean, duplicated_space: boolean, duplicated_strokeWidth: boolean, duplicated_strokeRadius: boolean, duplicated_trackBackgroundColor: boolean, duplicated_trackColor: boolean): boolean {
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
    static isLinearStyleOptions(value: Object | string | number | undefined | boolean, duplicated_strokeWidth: boolean, duplicated_strokeRadius: boolean): boolean {
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
    static isLineBreakStrategy(value: Object | string | number | undefined | boolean): boolean {
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
    static isLineCapStyle(value: Object | string | number | undefined | boolean): boolean {
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
    static isLineHeightStyle(value: Object | string | number | undefined | boolean, duplicated_lineHeight: boolean): boolean {
        if ((!duplicated_lineHeight) && (value?.hasOwnProperty("lineHeight"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof LineHeightStyle")
        }
    }
    static isLineJoinStyle(value: Object | string | number | undefined | boolean): boolean {
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
    static isLineOptions(value: Object | string | number | undefined | boolean, duplicated_width: boolean, duplicated_height: boolean): boolean {
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
    static isListDividerOptions(value: Object | string | number | undefined | boolean, duplicated_strokeWidth: boolean, duplicated_color: boolean, duplicated_startMargin: boolean, duplicated_endMargin: boolean): boolean {
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
    static isListItemAlign(value: Object | string | number | undefined | boolean): boolean {
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
    static isListItemGroupArea(value: Object | string | number | undefined | boolean): boolean {
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
    static isListItemGroupOptions(value: Object | string | number | undefined | boolean, duplicated_header: boolean, duplicated_headerComponent: boolean, duplicated_footer: boolean, duplicated_footerComponent: boolean, duplicated_space: boolean, duplicated_style: boolean): boolean {
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
    static isListItemGroupStyle(value: Object | string | number | undefined | boolean): boolean {
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
    static isListItemOptions(value: Object | string | number | undefined | boolean, duplicated_style: boolean): boolean {
        if ((!duplicated_style) && (value?.hasOwnProperty("style"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ListItemOptions")
        }
    }
    static isListItemStyle(value: Object | string | number | undefined | boolean): boolean {
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
    static isListOptions(value: Object | string | number | undefined | boolean, duplicated_initialIndex: boolean, duplicated_space: boolean, duplicated_scroller: boolean): boolean {
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
    static isListScroller(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof ListScroller")
    }
    static isLoadCommittedDetails(value: Object | string | number | undefined | boolean, duplicated_isMainFrame: boolean, duplicated_isSameDocument: boolean, duplicated_didReplaceEntry: boolean, duplicated_navigationType: boolean, duplicated_url: boolean): boolean {
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
    static isLoadingProgressConfiguration(value: Object | string | number | undefined | boolean, duplicated_enableLoading: boolean): boolean {
        if ((!duplicated_enableLoading) && (value?.hasOwnProperty("enableLoading"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof LoadingProgressConfiguration")
        }
    }
    static isLoadingProgressStyle(value: Object | string | number | undefined | boolean): boolean {
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
    static isLocalizedAlignRuleOptions(value: Object | string | number | undefined | boolean, duplicated_start: boolean, duplicated_end: boolean, duplicated_middle: boolean, duplicated_top: boolean, duplicated_bottom: boolean, duplicated_center: boolean, duplicated_bias: boolean): boolean {
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
    static isLocalizedBarrierDirection(value: Object | string | number | undefined | boolean): boolean {
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
    static isLocalizedBorderRadiuses(value: Object | string | number | undefined | boolean, duplicated_topStart: boolean, duplicated_topEnd: boolean, duplicated_bottomStart: boolean, duplicated_bottomEnd: boolean): boolean {
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
    static isLocalizedEdgeColors(value: Object | string | number | undefined | boolean, duplicated_top: boolean, duplicated_end: boolean, duplicated_bottom: boolean, duplicated_start: boolean): boolean {
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
    static isLocalizedEdges(value: Object | string | number | undefined | boolean, duplicated_top: boolean, duplicated_start: boolean, duplicated_bottom: boolean, duplicated_end: boolean): boolean {
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
    static isLocalizedEdgeWidths(value: Object | string | number | undefined | boolean, duplicated_top: boolean, duplicated_end: boolean, duplicated_bottom: boolean, duplicated_start: boolean): boolean {
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
    static isLocalizedHorizontalAlignParam(value: Object | string | number | undefined | boolean, duplicated_anchor: boolean, duplicated_align: boolean): boolean {
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
    static isLocalizedPadding(value: Object | string | number | undefined | boolean, duplicated_top: boolean, duplicated_end: boolean, duplicated_bottom: boolean, duplicated_start: boolean): boolean {
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
    static isLocalizedPosition(value: Object | string | number | undefined | boolean, duplicated_start: boolean, duplicated_top: boolean): boolean {
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
    static isLocalizedVerticalAlignParam(value: Object | string | number | undefined | boolean, duplicated_anchor: boolean, duplicated_align: boolean): boolean {
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
    static isLongPressGestureEvent(value: Object | string | number | undefined | boolean, duplicated_repeat: boolean): boolean {
        if ((!duplicated_repeat) && (value?.hasOwnProperty("repeat"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof LongPressGestureEvent")
        }
    }
    static isLongPressGestureHandlerOptions(value: Object | string | number | undefined | boolean, duplicated_fingers: boolean, duplicated_repeat: boolean, duplicated_duration: boolean): boolean {
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
    static isLongPressGestureInterface(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof LongPressGestureInterface")
    }
    static isLongPressGestureInterface_Invoke_Literal(value: Object | string | number | undefined | boolean, duplicated_fingers: boolean, duplicated_repeat: boolean, duplicated_duration: boolean): boolean {
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
            throw new Error("Can not discriminate value typeof LongPressGestureInterface_Invoke_Literal")
        }
    }
    static isLongPressRecognizer(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof LongPressRecognizer")
    }
    static isMarkStyle(value: Object | string | number | undefined | boolean, duplicated_strokeColor: boolean, duplicated_size: boolean, duplicated_strokeWidth: boolean): boolean {
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
    static isMarqueeOptions(value: Object | string | number | undefined | boolean, duplicated_start: boolean, duplicated_step: boolean, duplicated_loop: boolean, duplicated_fromStart: boolean, duplicated_src: boolean): boolean {
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
    static isMarqueeStartPolicy(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (MarqueeStartPolicy.DEFAULT)) {
            return true
        }
        else if ((value) === (MarqueeStartPolicy.ON_FOCUS)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof MarqueeStartPolicy")
        }
    }
    static isMarqueeState(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (MarqueeState.START)) {
            return true
        }
        else if ((value) === (MarqueeState.BOUNCE)) {
            return true
        }
        else if ((value) === (MarqueeState.FINISH)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof MarqueeState")
        }
    }
    static isMarqueeUpdateStrategy(value: Object | string | number | undefined | boolean): boolean {
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
    static isMatrix2D(value: Object | string | number | undefined | boolean, duplicated_scaleX: boolean, duplicated_rotateY: boolean, duplicated_rotateX: boolean, duplicated_scaleY: boolean, duplicated_translateX: boolean, duplicated_translateY: boolean): boolean {
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
    static ismatrix4_Matrix4Transit(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof matrix4.Matrix4Transit")
    }
    static ismatrix4_PolyToPolyOptions(value: Object | string | number | undefined | boolean, duplicated_src: boolean, duplicated_srcIndex: boolean, duplicated_dst: boolean, duplicated_dstIndex: boolean, duplicated_pointCount: boolean): boolean {
        if ((!duplicated_src) && (value?.hasOwnProperty("src"))) {
            return true
        }
        else if ((!duplicated_dst) && (value?.hasOwnProperty("dst"))) {
            return true
        }
        else if ((!duplicated_srcIndex) && (value?.hasOwnProperty("srcIndex"))) {
            return true
        }
        else if ((!duplicated_dstIndex) && (value?.hasOwnProperty("dstIndex"))) {
            return true
        }
        else if ((!duplicated_pointCount) && (value?.hasOwnProperty("pointCount"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof matrix4.PolyToPolyOptions")
        }
    }
    static isMeasurable(value: Object | string | number | undefined | boolean, duplicated_uniqueId: boolean): boolean {
        if ((!duplicated_uniqueId) && (value?.hasOwnProperty("uniqueId"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof Measurable")
        }
    }
    static isMeasureOptions(value: Object | string | number | undefined | boolean, duplicated_textContent: boolean, duplicated_constraintWidth: boolean, duplicated_fontSize: boolean, duplicated_fontStyle: boolean, duplicated_fontWeight: boolean, duplicated_fontFamily: boolean, duplicated_letterSpacing: boolean, duplicated_textAlign: boolean, duplicated_overflow: boolean, duplicated_maxLines: boolean, duplicated_lineHeight: boolean, duplicated_baselineOffset: boolean, duplicated_textCase: boolean, duplicated_textIndent: boolean, duplicated_wordBreak: boolean): boolean {
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
    static isMeasureResult(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof MeasureResult")
    }
    static isMenuAlignType(value: Object | string | number | undefined | boolean): boolean {
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
    static isMenuElement(value: Object | string | number | undefined | boolean, duplicated_value: boolean, duplicated_icon: boolean, duplicated_symbolIcon: boolean, duplicated_enabled: boolean, duplicated_action: boolean): boolean {
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
    static isMenuItemConfiguration(value: Object | string | number | undefined | boolean, duplicated_value: boolean, duplicated_icon: boolean, duplicated_symbolIcon: boolean, duplicated_selected: boolean, duplicated_index: boolean): boolean {
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
    static isMenuItemGroupOptions(value: Object | string | number | undefined | boolean, duplicated_header: boolean, duplicated_footer: boolean): boolean {
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
    static isMenuItemOptions(value: Object | string | number | undefined | boolean, duplicated_startIcon: boolean, duplicated_symbolStartIcon: boolean, duplicated_content: boolean, duplicated_endIcon: boolean, duplicated_symbolEndIcon: boolean, duplicated_labelInfo: boolean, duplicated_builder: boolean): boolean {
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
    static isMenuOptions(value: Object | string | number | undefined | boolean, duplicated_title: boolean, duplicated_showInSubWindow: boolean): boolean {
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
    static isMenuOutlineOptions(value: Object | string | number | undefined | boolean, duplicated_width: boolean, duplicated_color: boolean): boolean {
        if ((!duplicated_width) && (value?.hasOwnProperty("width"))) {
            return true
        }
        else if ((!duplicated_color) && (value?.hasOwnProperty("color"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof MenuOutlineOptions")
        }
    }
    static isMenuPolicy(value: Object | string | number | undefined | boolean): boolean {
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
    static isMenuPreviewMode(value: Object | string | number | undefined | boolean): boolean {
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
    static isMenuType(value: Object | string | number | undefined | boolean): boolean {
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
    static isMessageEvents(value: Object | string | number | undefined | boolean, duplicated_data: boolean): boolean {
        if ((!duplicated_data) && (value?.hasOwnProperty("data"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof MessageEvents")
        }
    }
    static isMessageLevel(value: Object | string | number | undefined | boolean): boolean {
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
    static isMixedMode(value: Object | string | number | undefined | boolean): boolean {
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
    static isModalTransition(value: Object | string | number | undefined | boolean): boolean {
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
    static isModifierKey(value: Object | string | number | undefined | boolean): boolean {
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
    static isMonthData(value: Object | string | number | undefined | boolean, duplicated_year: boolean, duplicated_month: boolean, duplicated_data: boolean): boolean {
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
    static isMoreButtonOptions(value: Object | string | number | undefined | boolean, duplicated_backgroundBlurStyle: boolean, duplicated_backgroundBlurStyleOptions: boolean, duplicated_backgroundEffect: boolean): boolean {
        if ((!duplicated_backgroundBlurStyle) && (value?.hasOwnProperty("backgroundBlurStyle"))) {
            return true
        }
        else if ((!duplicated_backgroundBlurStyleOptions) && (value?.hasOwnProperty("backgroundBlurStyleOptions"))) {
            return true
        }
        else if ((!duplicated_backgroundEffect) && (value?.hasOwnProperty("backgroundEffect"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof MoreButtonOptions")
        }
    }
    static isMotionBlurAnchor(value: Object | string | number | undefined | boolean, duplicated_x: boolean, duplicated_y: boolean): boolean {
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
    static isMotionBlurOptions(value: Object | string | number | undefined | boolean, duplicated_radius: boolean, duplicated_anchor: boolean): boolean {
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
    static isMotionPathOptions(value: Object | string | number | undefined | boolean, duplicated_path: boolean, duplicated_from: boolean, duplicated_to: boolean, duplicated_rotatable: boolean): boolean {
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
    static isMouseAction(value: Object | string | number | undefined | boolean): boolean {
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
        else if ((value) === (MouseAction.CANCEL)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof MouseAction")
        }
    }
    static isMouseButton(value: Object | string | number | undefined | boolean): boolean {
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
    static isMouseEvent(value: Object | string | number | undefined | boolean, duplicated_button: boolean, duplicated_action: boolean, duplicated_displayX: boolean, duplicated_displayY: boolean, duplicated_windowX: boolean, duplicated_windowY: boolean, duplicated_x: boolean, duplicated_y: boolean, duplicated_stopPropagation: boolean, duplicated_rawDeltaX: boolean, duplicated_rawDeltaY: boolean, duplicated_pressedButtons: boolean): boolean {
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
        else if ((!duplicated_x) && (value?.hasOwnProperty("x"))) {
            return true
        }
        else if ((!duplicated_y) && (value?.hasOwnProperty("y"))) {
            return true
        }
        else if ((!duplicated_stopPropagation) && (value?.hasOwnProperty("stopPropagation"))) {
            return true
        }
        else if ((!duplicated_rawDeltaX) && (value?.hasOwnProperty("rawDeltaX"))) {
            return true
        }
        else if ((!duplicated_rawDeltaY) && (value?.hasOwnProperty("rawDeltaY"))) {
            return true
        }
        else if ((!duplicated_pressedButtons) && (value?.hasOwnProperty("pressedButtons"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof MouseEvent")
        }
    }
    static isMutableStyledString(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof MutableStyledString")
    }
    static isNativeEmbedDataInfo(value: Object | string | number | undefined | boolean, duplicated_status: boolean, duplicated_surfaceId: boolean, duplicated_embedId: boolean, duplicated_info: boolean): boolean {
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
    static isNativeEmbedInfo(value: Object | string | number | undefined | boolean, duplicated_id: boolean, duplicated_type: boolean, duplicated_src: boolean, duplicated_position: boolean, duplicated_width: boolean, duplicated_height: boolean, duplicated_url: boolean, duplicated_tag: boolean, duplicated_params: boolean): boolean {
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
    static isNativeEmbedStatus(value: Object | string | number | undefined | boolean): boolean {
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
    static isNativeEmbedTouchInfo(value: Object | string | number | undefined | boolean, duplicated_embedId: boolean, duplicated_touchEvent: boolean, duplicated_result: boolean): boolean {
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
    static isNativeEmbedVisibilityInfo(value: Object | string | number | undefined | boolean, duplicated_visibility: boolean, duplicated_embedId: boolean): boolean {
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
    static isNativeMediaPlayerConfig(value: Object | string | number | undefined | boolean, duplicated_enable: boolean, duplicated_shouldOverlay: boolean): boolean {
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
    static isNativeXComponentParameters(value: Object | string | number | undefined | boolean, duplicated_type: boolean, duplicated_imageAIOptions: boolean): boolean {
        if ((!duplicated_type) && (value?.hasOwnProperty("type"))) {
            return true
        }
        else if ((!duplicated_imageAIOptions) && (value?.hasOwnProperty("imageAIOptions"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof NativeXComponentParameters")
        }
    }
    static isNavBarPosition(value: Object | string | number | undefined | boolean): boolean {
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
    static isNavContentInfo(value: Object | string | number | undefined | boolean, duplicated_name: boolean, duplicated_index: boolean, duplicated_mode: boolean, duplicated_param: boolean, duplicated_navDestinationId: boolean): boolean {
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
    static isNavDestinationActiveReason(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (NavDestinationActiveReason.TRANSITION)) {
            return true
        }
        else if ((value) === (NavDestinationActiveReason.CONTENT_COVER)) {
            return true
        }
        else if ((value) === (NavDestinationActiveReason.SHEET)) {
            return true
        }
        else if ((value) === (NavDestinationActiveReason.DIALOG)) {
            return true
        }
        else if ((value) === (NavDestinationActiveReason.OVERLAY)) {
            return true
        }
        else if ((value) === (NavDestinationActiveReason.APP_STATE)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof NavDestinationActiveReason")
        }
    }
    static isNavDestinationCommonTitle(value: Object | string | number | undefined | boolean, duplicated_main: boolean, duplicated_sub: boolean): boolean {
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
    static isNavDestinationContext(value: Object | string | number | undefined | boolean, duplicated_pathInfo: boolean, duplicated_pathStack: boolean, duplicated_navDestinationId: boolean): boolean {
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
    static isNavDestinationCustomTitle(value: Object | string | number | undefined | boolean, duplicated_builder: boolean, duplicated_height: boolean): boolean {
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
    static isNavDestinationMode(value: Object | string | number | undefined | boolean): boolean {
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
    static isNavDestinationTransition(value: Object | string | number | undefined | boolean, duplicated_onTransitionEnd: boolean, duplicated_duration: boolean, duplicated_curve: boolean, duplicated_delay: boolean, duplicated_event: boolean): boolean {
        if ((!duplicated_event) && (value?.hasOwnProperty("event"))) {
            return true
        }
        else if ((!duplicated_onTransitionEnd) && (value?.hasOwnProperty("onTransitionEnd"))) {
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
            throw new Error("Can not discriminate value typeof NavDestinationTransition")
        }
    }
    static isNavigationAnimatedTransition(value: Object | string | number | undefined | boolean, duplicated_onTransitionEnd: boolean, duplicated_timeout: boolean, duplicated_isInteractive: boolean, duplicated_transition: boolean): boolean {
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
    static isNavigationCommonTitle(value: Object | string | number | undefined | boolean, duplicated_main: boolean, duplicated_sub: boolean): boolean {
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
    static isNavigationCustomTitle(value: Object | string | number | undefined | boolean, duplicated_builder: boolean, duplicated_height: boolean): boolean {
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
    static isNavigationInterception(value: Object | string | number | undefined | boolean, duplicated_willShow: boolean, duplicated_didShow: boolean, duplicated_modeChange: boolean): boolean {
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
    static isNavigationMenuItem(value: Object | string | number | undefined | boolean, duplicated_value: boolean, duplicated_icon: boolean, duplicated_symbolIcon: boolean, duplicated_isEnabled: boolean, duplicated_action: boolean): boolean {
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
    static isNavigationMenuOptions(value: Object | string | number | undefined | boolean, duplicated_moreButtonOptions: boolean): boolean {
        if ((!duplicated_moreButtonOptions) && (value?.hasOwnProperty("moreButtonOptions"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof NavigationMenuOptions")
        }
    }
    static isNavigationMode(value: Object | string | number | undefined | boolean): boolean {
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
    static isNavigationOperation(value: Object | string | number | undefined | boolean): boolean {
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
    static isNavigationOptions(value: Object | string | number | undefined | boolean, duplicated_launchMode: boolean, duplicated_animated: boolean): boolean {
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
    static isNavigationSystemTransitionType(value: Object | string | number | undefined | boolean): boolean {
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
        else if ((value) === (NavigationSystemTransitionType.FADE)) {
            return true
        }
        else if ((value) === (NavigationSystemTransitionType.EXPLODE)) {
            return true
        }
        else if ((value) === (NavigationSystemTransitionType.SLIDE_RIGHT)) {
            return true
        }
        else if ((value) === (NavigationSystemTransitionType.SLIDE_BOTTOM)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof NavigationSystemTransitionType")
        }
    }
    static isNavigationTitleMode(value: Object | string | number | undefined | boolean): boolean {
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
    static isNavigationTitleOptions(value: Object | string | number | undefined | boolean, duplicated_backgroundColor: boolean, duplicated_backgroundBlurStyle: boolean, duplicated_backgroundBlurStyleOptions: boolean, duplicated_backgroundEffect: boolean, duplicated_barStyle: boolean, duplicated_paddingStart: boolean, duplicated_paddingEnd: boolean, duplicated_mainTitleModifier: boolean, duplicated_subTitleModifier: boolean, duplicated_enableHoverMode: boolean): boolean {
        if ((!duplicated_backgroundColor) && (value?.hasOwnProperty("backgroundColor"))) {
            return true
        }
        else if ((!duplicated_backgroundBlurStyle) && (value?.hasOwnProperty("backgroundBlurStyle"))) {
            return true
        }
        else if ((!duplicated_backgroundBlurStyleOptions) && (value?.hasOwnProperty("backgroundBlurStyleOptions"))) {
            return true
        }
        else if ((!duplicated_backgroundEffect) && (value?.hasOwnProperty("backgroundEffect"))) {
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
    static isNavigationToolbarOptions(value: Object | string | number | undefined | boolean, duplicated_backgroundColor: boolean, duplicated_backgroundBlurStyle: boolean, duplicated_backgroundBlurStyleOptions: boolean, duplicated_backgroundEffect: boolean, duplicated_moreButtonOptions: boolean, duplicated_barStyle: boolean, duplicated_hideItemValue: boolean): boolean {
        if ((!duplicated_backgroundColor) && (value?.hasOwnProperty("backgroundColor"))) {
            return true
        }
        else if ((!duplicated_backgroundBlurStyle) && (value?.hasOwnProperty("backgroundBlurStyle"))) {
            return true
        }
        else if ((!duplicated_backgroundBlurStyleOptions) && (value?.hasOwnProperty("backgroundBlurStyleOptions"))) {
            return true
        }
        else if ((!duplicated_backgroundEffect) && (value?.hasOwnProperty("backgroundEffect"))) {
            return true
        }
        else if ((!duplicated_moreButtonOptions) && (value?.hasOwnProperty("moreButtonOptions"))) {
            return true
        }
        else if ((!duplicated_barStyle) && (value?.hasOwnProperty("barStyle"))) {
            return true
        }
        else if ((!duplicated_hideItemValue) && (value?.hasOwnProperty("hideItemValue"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof NavigationToolbarOptions")
        }
    }
    static isNavigationTransitionProxy(value: Object | string | number | undefined | boolean, duplicated_from: boolean, duplicated_to: boolean, duplicated_isInteractive: boolean, duplicated_cancelTransition: boolean, duplicated_updateTransition: boolean): boolean {
        if ((!duplicated_from) && (value?.hasOwnProperty("from"))) {
            return true
        }
        else if ((!duplicated_to) && (value?.hasOwnProperty("to"))) {
            return true
        }
        else if ((!duplicated_isInteractive) && (value?.hasOwnProperty("isInteractive"))) {
            return true
        }
        else if ((!duplicated_cancelTransition) && (value?.hasOwnProperty("cancelTransition"))) {
            return true
        }
        else if ((!duplicated_updateTransition) && (value?.hasOwnProperty("updateTransition"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof NavigationTransitionProxy")
        }
    }
    static isNavigationType(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (NavigationType.PUSH)) {
            return true
        }
        else if ((value) === (NavigationType.BACK)) {
            return true
        }
        else if ((value) === (NavigationType.REPLACE)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof NavigationType")
        }
    }
    static isNavPathInfo(value: Object | string | number | undefined | boolean, duplicated_name: boolean, duplicated_param: boolean, duplicated_onPop: boolean, duplicated_isEntry: boolean, duplicated_navDestinationId: boolean): boolean {
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
        else if ((!duplicated_navDestinationId) && (value?.hasOwnProperty("navDestinationId"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof NavPathInfo")
        }
    }
    static isNavPathStack(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof NavPathStack")
    }
    static isNestedScrollInfo(value: Object | string | number | undefined | boolean, duplicated_parent: boolean, duplicated_child: boolean): boolean {
        if ((!duplicated_parent) && (value?.hasOwnProperty("parent"))) {
            return true
        }
        else if ((!duplicated_child) && (value?.hasOwnProperty("child"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof NestedScrollInfo")
        }
    }
    static isNestedScrollMode(value: Object | string | number | undefined | boolean): boolean {
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
    static isNestedScrollOptions(value: Object | string | number | undefined | boolean, duplicated_scrollForward: boolean, duplicated_scrollBackward: boolean): boolean {
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
    static isNestedScrollOptionsExt(value: Object | string | number | undefined | boolean, duplicated_scrollUp: boolean, duplicated_scrollDown: boolean, duplicated_scrollRight: boolean, duplicated_scrollLeft: boolean): boolean {
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
    static isNodeContent(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof NodeContent")
    }
    static isNodeController(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof NodeController")
    }
    static isNonCurrentDayStyle(value: Object | string | number | undefined | boolean, duplicated_nonCurrentMonthDayColor: boolean, duplicated_nonCurrentMonthLunarColor: boolean, duplicated_nonCurrentMonthWorkDayMarkColor: boolean, duplicated_nonCurrentMonthOffDayMarkColor: boolean): boolean {
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
    static isObscuredReasons(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (ObscuredReasons.PLACEHOLDER)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ObscuredReasons")
        }
    }
    static isOffscreenCanvas(value: Object | string | number | undefined | boolean, duplicated_height: boolean, duplicated_width: boolean): boolean {
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
    static isOffscreenCanvasRenderingContext2D(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof OffscreenCanvasRenderingContext2D")
    }
    static isOffset(value: Object | string | number | undefined | boolean, duplicated_dx: boolean, duplicated_dy: boolean): boolean {
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
    static isOffset_componentutils(value: Object | string | number | undefined | boolean, duplicated_x: boolean, duplicated_y: boolean): boolean {
        if ((!duplicated_x) && (value?.hasOwnProperty("x"))) {
            return true
        }
        else if ((!duplicated_y) && (value?.hasOwnProperty("y"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof Offset_componentutils")
        }
    }
    static isOffsetOptions(value: Object | string | number | undefined | boolean, duplicated_xOffset: boolean, duplicated_yOffset: boolean): boolean {
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
    static isOffsetResult(value: Object | string | number | undefined | boolean, duplicated_xOffset: boolean, duplicated_yOffset: boolean): boolean {
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
    static isOnAlertEvent(value: Object | string | number | undefined | boolean, duplicated_url: boolean, duplicated_message: boolean, duplicated_result: boolean): boolean {
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
    static isOnAudioStateChangedEvent(value: Object | string | number | undefined | boolean, duplicated_playing: boolean): boolean {
        if ((!duplicated_playing) && (value?.hasOwnProperty("playing"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof OnAudioStateChangedEvent")
        }
    }
    static isOnBeforeUnloadEvent(value: Object | string | number | undefined | boolean, duplicated_url: boolean, duplicated_message: boolean, duplicated_result: boolean): boolean {
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
    static isOnClientAuthenticationEvent(value: Object | string | number | undefined | boolean, duplicated_handler: boolean, duplicated_host: boolean, duplicated_port: boolean, duplicated_keyTypes: boolean, duplicated_issuers: boolean): boolean {
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
    static isOnConfirmEvent(value: Object | string | number | undefined | boolean, duplicated_url: boolean, duplicated_message: boolean, duplicated_result: boolean): boolean {
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
    static isOnConsoleEvent(value: Object | string | number | undefined | boolean, duplicated_message: boolean): boolean {
        if ((!duplicated_message) && (value?.hasOwnProperty("message"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof OnConsoleEvent")
        }
    }
    static isOnContextMenuShowEvent(value: Object | string | number | undefined | boolean, duplicated_param: boolean, duplicated_result: boolean): boolean {
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
    static isOnDataResubmittedEvent(value: Object | string | number | undefined | boolean, duplicated_handler: boolean): boolean {
        if ((!duplicated_handler) && (value?.hasOwnProperty("handler"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof OnDataResubmittedEvent")
        }
    }
    static isOnDownloadStartEvent(value: Object | string | number | undefined | boolean, duplicated_url: boolean, duplicated_userAgent: boolean, duplicated_contentDisposition: boolean, duplicated_mimetype: boolean, duplicated_contentLength: boolean): boolean {
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
    static isOnErrorReceiveEvent(value: Object | string | number | undefined | boolean, duplicated_request: boolean, duplicated_error: boolean): boolean {
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
    static isOnFaviconReceivedEvent(value: Object | string | number | undefined | boolean, duplicated_favicon: boolean): boolean {
        if ((!duplicated_favicon) && (value?.hasOwnProperty("favicon"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof OnFaviconReceivedEvent")
        }
    }
    static isOnFirstContentfulPaintEvent(value: Object | string | number | undefined | boolean, duplicated_navigationStartTick: boolean, duplicated_firstContentfulPaintMs: boolean): boolean {
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
    static isOnFoldStatusChangeInfo(value: Object | string | number | undefined | boolean, duplicated_foldStatus: boolean): boolean {
        if ((!duplicated_foldStatus) && (value?.hasOwnProperty("foldStatus"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof OnFoldStatusChangeInfo")
        }
    }
    static isOnGeolocationShowEvent(value: Object | string | number | undefined | boolean, duplicated_origin: boolean, duplicated_geolocation: boolean): boolean {
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
    static isOnHttpAuthRequestEvent(value: Object | string | number | undefined | boolean, duplicated_handler: boolean, duplicated_host: boolean, duplicated_realm: boolean): boolean {
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
    static isOnHttpErrorReceiveEvent(value: Object | string | number | undefined | boolean, duplicated_request: boolean, duplicated_response: boolean): boolean {
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
    static isOnInterceptRequestEvent(value: Object | string | number | undefined | boolean, duplicated_request: boolean): boolean {
        if ((!duplicated_request) && (value?.hasOwnProperty("request"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof OnInterceptRequestEvent")
        }
    }
    static isOnLoadInterceptEvent(value: Object | string | number | undefined | boolean, duplicated_data: boolean): boolean {
        if ((!duplicated_data) && (value?.hasOwnProperty("data"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof OnLoadInterceptEvent")
        }
    }
    static isOnOverScrollEvent(value: Object | string | number | undefined | boolean, duplicated_xOffset: boolean, duplicated_yOffset: boolean): boolean {
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
    static isOnPageBeginEvent(value: Object | string | number | undefined | boolean, duplicated_url: boolean): boolean {
        if ((!duplicated_url) && (value?.hasOwnProperty("url"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof OnPageBeginEvent")
        }
    }
    static isOnPageEndEvent(value: Object | string | number | undefined | boolean, duplicated_url: boolean): boolean {
        if ((!duplicated_url) && (value?.hasOwnProperty("url"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof OnPageEndEvent")
        }
    }
    static isOnPageVisibleEvent(value: Object | string | number | undefined | boolean, duplicated_url: boolean): boolean {
        if ((!duplicated_url) && (value?.hasOwnProperty("url"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof OnPageVisibleEvent")
        }
    }
    static isOnPermissionRequestEvent(value: Object | string | number | undefined | boolean, duplicated_request: boolean): boolean {
        if ((!duplicated_request) && (value?.hasOwnProperty("request"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof OnPermissionRequestEvent")
        }
    }
    static isOnProgressChangeEvent(value: Object | string | number | undefined | boolean, duplicated_newProgress: boolean): boolean {
        if ((!duplicated_newProgress) && (value?.hasOwnProperty("newProgress"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof OnProgressChangeEvent")
        }
    }
    static isOnPromptEvent(value: Object | string | number | undefined | boolean, duplicated_url: boolean, duplicated_message: boolean, duplicated_value: boolean, duplicated_result: boolean): boolean {
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
    static isOnRefreshAccessedHistoryEvent(value: Object | string | number | undefined | boolean, duplicated_url: boolean, duplicated_isRefreshed: boolean): boolean {
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
    static isOnRenderExitedEvent(value: Object | string | number | undefined | boolean, duplicated_renderExitReason: boolean): boolean {
        if ((!duplicated_renderExitReason) && (value?.hasOwnProperty("renderExitReason"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof OnRenderExitedEvent")
        }
    }
    static isOnResourceLoadEvent(value: Object | string | number | undefined | boolean, duplicated_url: boolean): boolean {
        if ((!duplicated_url) && (value?.hasOwnProperty("url"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof OnResourceLoadEvent")
        }
    }
    static isOnScaleChangeEvent(value: Object | string | number | undefined | boolean, duplicated_oldScale: boolean, duplicated_newScale: boolean): boolean {
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
    static isOnScreenCaptureRequestEvent(value: Object | string | number | undefined | boolean, duplicated_handler: boolean): boolean {
        if ((!duplicated_handler) && (value?.hasOwnProperty("handler"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof OnScreenCaptureRequestEvent")
        }
    }
    static isOnScrollEvent(value: Object | string | number | undefined | boolean, duplicated_xOffset: boolean, duplicated_yOffset: boolean): boolean {
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
    static isOnScrollFrameBeginHandlerResult(value: Object | string | number | undefined | boolean, duplicated_offsetRemain: boolean): boolean {
        if ((!duplicated_offsetRemain) && (value?.hasOwnProperty("offsetRemain"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof OnScrollFrameBeginHandlerResult")
        }
    }
    static isOnSearchResultReceiveEvent(value: Object | string | number | undefined | boolean, duplicated_activeMatchOrdinal: boolean, duplicated_numberOfMatches: boolean, duplicated_isDoneCounting: boolean): boolean {
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
    static isOnShowFileSelectorEvent(value: Object | string | number | undefined | boolean, duplicated_result: boolean, duplicated_fileSelector: boolean): boolean {
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
    static isOnSslErrorEventReceiveEvent(value: Object | string | number | undefined | boolean, duplicated_handler: boolean, duplicated_error: boolean, duplicated_certChainData: boolean): boolean {
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
    static isOnTitleReceiveEvent(value: Object | string | number | undefined | boolean, duplicated_title: boolean): boolean {
        if ((!duplicated_title) && (value?.hasOwnProperty("title"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof OnTitleReceiveEvent")
        }
    }
    static isOnTouchIconUrlReceivedEvent(value: Object | string | number | undefined | boolean, duplicated_url: boolean, duplicated_precomposed: boolean): boolean {
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
    static isOnWindowNewEvent(value: Object | string | number | undefined | boolean, duplicated_isAlert: boolean, duplicated_isUserTrigger: boolean, duplicated_targetUrl: boolean, duplicated_handler: boolean): boolean {
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
    static isOptionWidthMode(value: Object | string | number | undefined | boolean): boolean {
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
    static isOutlineOptions(value: Object | string | number | undefined | boolean, duplicated_width: boolean, duplicated_color: boolean, duplicated_radius: boolean, duplicated_style: boolean): boolean {
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
    static isOutlineRadiuses(value: Object | string | number | undefined | boolean, duplicated_topLeft: boolean, duplicated_topRight: boolean, duplicated_bottomLeft: boolean, duplicated_bottomRight: boolean): boolean {
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
    static isOutlineStyle(value: Object | string | number | undefined | boolean): boolean {
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
    static isOverlayOffset(value: Object | string | number | undefined | boolean, duplicated_x: boolean, duplicated_y: boolean): boolean {
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
    static isOverlayOptions(value: Object | string | number | undefined | boolean, duplicated_align: boolean, duplicated_offset: boolean): boolean {
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
    static isOverScrollMode(value: Object | string | number | undefined | boolean): boolean {
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
    static isPadding(value: Object | string | number | undefined | boolean, duplicated_top: boolean, duplicated_right: boolean, duplicated_bottom: boolean, duplicated_left: boolean): boolean {
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
    static isPageFlipMode(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (PageFlipMode.CONTINUOUS)) {
            return true
        }
        else if ((value) === (PageFlipMode.SINGLE)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof PageFlipMode")
        }
    }
    static isPageLifeCycle(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof PageLifeCycle")
    }
    static isPanDirection(value: Object | string | number | undefined | boolean): boolean {
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
    static isPanGestureEvent(value: Object | string | number | undefined | boolean, duplicated_offsetX: boolean, duplicated_offsetY: boolean, duplicated_velocityX: boolean, duplicated_velocityY: boolean, duplicated_velocity: boolean): boolean {
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
    static isPanGestureHandlerOptions(value: Object | string | number | undefined | boolean, duplicated_fingers: boolean, duplicated_direction: boolean, duplicated_distance: boolean): boolean {
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
    static isPanGestureInterface(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof PanGestureInterface")
    }
    static isPanGestureInterface_Invoke_Literal(value: Object | string | number | undefined | boolean, duplicated_fingers: boolean, duplicated_direction: boolean, duplicated_distance: boolean): boolean {
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
            throw new Error("Can not discriminate value typeof PanGestureInterface_Invoke_Literal")
        }
    }
    static isPanGestureOptions(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof PanGestureOptions")
    }
    static isPanRecognizer(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof PanRecognizer")
    }
    static isParagraphStyle(value: Object | string | number | undefined | boolean, duplicated_textAlign: boolean, duplicated_textIndent: boolean, duplicated_maxLines: boolean, duplicated_overflow: boolean, duplicated_wordBreak: boolean, duplicated_leadingMargin: boolean, duplicated_paragraphSpacing: boolean): boolean {
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
        else if ((!duplicated_paragraphSpacing) && (value?.hasOwnProperty("paragraphSpacing"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ParagraphStyle")
        }
    }
    static isParagraphStyleInterface(value: Object | string | number | undefined | boolean, duplicated_textAlign: boolean, duplicated_textIndent: boolean, duplicated_maxLines: boolean, duplicated_overflow: boolean, duplicated_wordBreak: boolean, duplicated_leadingMargin: boolean, duplicated_paragraphSpacing: boolean): boolean {
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
        else if ((!duplicated_paragraphSpacing) && (value?.hasOwnProperty("paragraphSpacing"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ParagraphStyleInterface")
        }
    }
    static isParticleEmitterShape(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (ParticleEmitterShape.RECTANGLE)) {
            return true
        }
        else if ((value) === (ParticleEmitterShape.CIRCLE)) {
            return true
        }
        else if ((value) === (ParticleEmitterShape.ELLIPSE)) {
            return true
        }
        else if ((value) === (ParticleEmitterShape.ANNULUS)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ParticleEmitterShape")
        }
    }
    static isParticleType(value: Object | string | number | undefined | boolean): boolean {
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
    static isParticleUpdater(value: Object | string | number | undefined | boolean): boolean {
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
    static isPasswordIcon(value: Object | string | number | undefined | boolean, duplicated_onIconSrc: boolean, duplicated_offIconSrc: boolean): boolean {
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
    static isPasteButtonOnClickResult(value: Object | string | number | undefined | boolean): boolean {
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
    static isPasteButtonOptions(value: Object | string | number | undefined | boolean, duplicated_icon: boolean, duplicated_text: boolean, duplicated_buttonType: boolean): boolean {
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
    static isPasteDescription(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (PasteDescription.PASTE)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof PasteDescription")
        }
    }
    static isPasteEvent(value: Object | string | number | undefined | boolean, duplicated_preventDefault: boolean): boolean {
        if ((!duplicated_preventDefault) && (value?.hasOwnProperty("preventDefault"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof PasteEvent")
        }
    }
    static isPasteIconStyle(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (PasteIconStyle.LINES)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof PasteIconStyle")
        }
    }
    static isPath2D(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof Path2D")
    }
    static isPathOptions(value: Object | string | number | undefined | boolean, duplicated_width: boolean, duplicated_height: boolean, duplicated_commands: boolean): boolean {
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
    static isPathShape(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof PathShape")
    }
    static isPathShapeOptions(value: Object | string | number | undefined | boolean, duplicated_commands: boolean): boolean {
        if ((!duplicated_commands) && (value?.hasOwnProperty("commands"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof PathShapeOptions")
        }
    }
    static isPatternLockChallengeResult(value: Object | string | number | undefined | boolean): boolean {
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
    static isPatternLockController(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof PatternLockController")
    }
    static isPerfMonitorActionType(value: Object | string | number | undefined | boolean): boolean {
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
    static isPerfMonitorSourceType(value: Object | string | number | undefined | boolean): boolean {
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
    static isPermissionRequest(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof PermissionRequest")
    }
    static isPickerDialogButtonStyle(value: Object | string | number | undefined | boolean, duplicated_type: boolean, duplicated_style: boolean, duplicated_role: boolean, duplicated_fontSize: boolean, duplicated_fontColor: boolean, duplicated_fontWeight: boolean, duplicated_fontStyle: boolean, duplicated_fontFamily: boolean, duplicated_backgroundColor: boolean, duplicated_borderRadius: boolean, duplicated_primary: boolean): boolean {
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
    static isPickerTextStyle(value: Object | string | number | undefined | boolean, duplicated_color: boolean, duplicated_font: boolean): boolean {
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
    static isPinchGestureEvent(value: Object | string | number | undefined | boolean, duplicated_scale: boolean, duplicated_pinchCenterX: boolean, duplicated_pinchCenterY: boolean): boolean {
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
    static isPinchGestureHandlerOptions(value: Object | string | number | undefined | boolean, duplicated_fingers: boolean, duplicated_distance: boolean): boolean {
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
    static isPinchGestureInterface(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof PinchGestureInterface")
    }
    static isPinchGestureInterface_Invoke_Literal(value: Object | string | number | undefined | boolean, duplicated_fingers: boolean, duplicated_distance: boolean): boolean {
        if ((!duplicated_fingers) && (value?.hasOwnProperty("fingers"))) {
            return true
        }
        else if ((!duplicated_distance) && (value?.hasOwnProperty("distance"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof PinchGestureInterface_Invoke_Literal")
        }
    }
    static isPinchRecognizer(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof PinchRecognizer")
    }
    static isPixelMapMock(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof PixelMapMock")
    }
    static isPixelRoundCalcPolicy(value: Object | string | number | undefined | boolean): boolean {
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
    static isPixelRoundMode(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (PixelRoundMode.PIXEL_ROUND_ON_LAYOUT_FINISH)) {
            return true
        }
        else if ((value) === (PixelRoundMode.PIXEL_ROUND_AFTER_MEASURE)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof PixelRoundMode")
        }
    }
    static isPixelRoundPolicy(value: Object | string | number | undefined | boolean, duplicated_start: boolean, duplicated_top: boolean, duplicated_end: boolean, duplicated_bottom: boolean): boolean {
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
    static isPixelStretchEffectOptions(value: Object | string | number | undefined | boolean, duplicated_top: boolean, duplicated_bottom: boolean, duplicated_left: boolean, duplicated_right: boolean): boolean {
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
    static isPlaceholderStyle(value: Object | string | number | undefined | boolean, duplicated_font: boolean, duplicated_fontColor: boolean): boolean {
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
    static isPlacement(value: Object | string | number | undefined | boolean): boolean {
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
    static isPlaybackInfo(value: Object | string | number | undefined | boolean, duplicated_time: boolean): boolean {
        if ((!duplicated_time) && (value?.hasOwnProperty("time"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof PlaybackInfo")
        }
    }
    static isPlaybackSpeed(value: Object | string | number | undefined | boolean): boolean {
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
    static isPlayMode(value: Object | string | number | undefined | boolean): boolean {
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
    static isPluginComponentOptions(value: Object | string | number | undefined | boolean, duplicated_template: boolean, duplicated_data: boolean): boolean {
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
    static isPluginComponentTemplate(value: Object | string | number | undefined | boolean, duplicated_source: boolean, duplicated_bundleName: boolean): boolean {
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
    static isPluginErrorData(value: Object | string | number | undefined | boolean, duplicated_errcode: boolean, duplicated_msg: boolean): boolean {
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
    static ispointer_PointerStyle(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (pointer.PointerStyle.DEFAULT)) {
            return true
        }
        else if ((value) === (pointer.PointerStyle.EAST)) {
            return true
        }
        else if ((value) === (pointer.PointerStyle.WEST)) {
            return true
        }
        else if ((value) === (pointer.PointerStyle.SOUTH)) {
            return true
        }
        else if ((value) === (pointer.PointerStyle.NORTH)) {
            return true
        }
        else if ((value) === (pointer.PointerStyle.WEST_EAST)) {
            return true
        }
        else if ((value) === (pointer.PointerStyle.NORTH_SOUTH)) {
            return true
        }
        else if ((value) === (pointer.PointerStyle.NORTH_EAST)) {
            return true
        }
        else if ((value) === (pointer.PointerStyle.NORTH_WEST)) {
            return true
        }
        else if ((value) === (pointer.PointerStyle.SOUTH_EAST)) {
            return true
        }
        else if ((value) === (pointer.PointerStyle.SOUTH_WEST)) {
            return true
        }
        else if ((value) === (pointer.PointerStyle.NORTH_EAST_SOUTH_WEST)) {
            return true
        }
        else if ((value) === (pointer.PointerStyle.NORTH_WEST_SOUTH_EAST)) {
            return true
        }
        else if ((value) === (pointer.PointerStyle.CROSS)) {
            return true
        }
        else if ((value) === (pointer.PointerStyle.CURSOR_COPY)) {
            return true
        }
        else if ((value) === (pointer.PointerStyle.CURSOR_FORBID)) {
            return true
        }
        else if ((value) === (pointer.PointerStyle.COLOR_SUCKER)) {
            return true
        }
        else if ((value) === (pointer.PointerStyle.HAND_GRABBING)) {
            return true
        }
        else if ((value) === (pointer.PointerStyle.HAND_OPEN)) {
            return true
        }
        else if ((value) === (pointer.PointerStyle.HAND_POINTING)) {
            return true
        }
        else if ((value) === (pointer.PointerStyle.HELP)) {
            return true
        }
        else if ((value) === (pointer.PointerStyle.MOVE)) {
            return true
        }
        else if ((value) === (pointer.PointerStyle.RESIZE_LEFT_RIGHT)) {
            return true
        }
        else if ((value) === (pointer.PointerStyle.RESIZE_UP_DOWN)) {
            return true
        }
        else if ((value) === (pointer.PointerStyle.SCREENSHOT_CHOOSE)) {
            return true
        }
        else if ((value) === (pointer.PointerStyle.SCREENSHOT_CURSOR)) {
            return true
        }
        else if ((value) === (pointer.PointerStyle.TEXT_CURSOR)) {
            return true
        }
        else if ((value) === (pointer.PointerStyle.ZOOM_IN)) {
            return true
        }
        else if ((value) === (pointer.PointerStyle.ZOOM_OUT)) {
            return true
        }
        else if ((value) === (pointer.PointerStyle.MIDDLE_BTN_EAST)) {
            return true
        }
        else if ((value) === (pointer.PointerStyle.MIDDLE_BTN_WEST)) {
            return true
        }
        else if ((value) === (pointer.PointerStyle.MIDDLE_BTN_SOUTH)) {
            return true
        }
        else if ((value) === (pointer.PointerStyle.MIDDLE_BTN_NORTH)) {
            return true
        }
        else if ((value) === (pointer.PointerStyle.MIDDLE_BTN_NORTH_SOUTH)) {
            return true
        }
        else if ((value) === (pointer.PointerStyle.MIDDLE_BTN_NORTH_EAST)) {
            return true
        }
        else if ((value) === (pointer.PointerStyle.MIDDLE_BTN_NORTH_WEST)) {
            return true
        }
        else if ((value) === (pointer.PointerStyle.MIDDLE_BTN_SOUTH_EAST)) {
            return true
        }
        else if ((value) === (pointer.PointerStyle.MIDDLE_BTN_SOUTH_WEST)) {
            return true
        }
        else if ((value) === (pointer.PointerStyle.MIDDLE_BTN_NORTH_SOUTH_WEST_EAST)) {
            return true
        }
        else if ((value) === (pointer.PointerStyle.HORIZONTAL_TEXT_CURSOR)) {
            return true
        }
        else if ((value) === (pointer.PointerStyle.CURSOR_CROSS)) {
            return true
        }
        else if ((value) === (pointer.PointerStyle.CURSOR_CIRCLE)) {
            return true
        }
        else if ((value) === (pointer.PointerStyle.LOADING)) {
            return true
        }
        else if ((value) === (pointer.PointerStyle.RUNNING)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof pointer.PointerStyle")
        }
    }
    static isPointLightStyle(value: Object | string | number | undefined | boolean, duplicated_lightSource: boolean, duplicated_illuminated: boolean, duplicated_bloom: boolean): boolean {
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
    static isPolygonOptions(value: Object | string | number | undefined | boolean, duplicated_width: boolean, duplicated_height: boolean): boolean {
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
    static isPolylineOptions(value: Object | string | number | undefined | boolean, duplicated_width: boolean, duplicated_height: boolean): boolean {
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
    static isPopInfo(value: Object | string | number | undefined | boolean, duplicated_info: boolean, duplicated_result: boolean): boolean {
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
    static isPopupButton(value: Object | string | number | undefined | boolean, duplicated_value: boolean, duplicated_action: boolean): boolean {
        if ((!duplicated_value) && (value?.hasOwnProperty("value"))) {
            return true
        }
        else if ((!duplicated_action) && (value?.hasOwnProperty("action"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof PopupButton")
        }
    }
    static isPopupCommonOptions(value: Object | string | number | undefined | boolean, duplicated_placement: boolean, duplicated_popupColor: boolean, duplicated_enableArrow: boolean, duplicated_autoCancel: boolean, duplicated_onStateChange: boolean, duplicated_arrowOffset: boolean, duplicated_showInSubWindow: boolean, duplicated_mask: boolean, duplicated_targetSpace: boolean, duplicated_offset: boolean, duplicated_width: boolean, duplicated_arrowPointPosition: boolean, duplicated_arrowWidth: boolean, duplicated_arrowHeight: boolean, duplicated_radius: boolean, duplicated_shadow: boolean, duplicated_backgroundBlurStyle: boolean, duplicated_focusable: boolean, duplicated_transition: boolean, duplicated_onWillDismiss: boolean, duplicated_enableHoverMode: boolean, duplicated_followTransformOfTarget: boolean): boolean {
        if ((!duplicated_placement) && (value?.hasOwnProperty("placement"))) {
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
            throw new Error("Can not discriminate value typeof PopupCommonOptions")
        }
    }
    static isPopupMaskType(value: Object | string | number | undefined | boolean, duplicated_color: boolean): boolean {
        if ((!duplicated_color) && (value?.hasOwnProperty("color"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof PopupMaskType")
        }
    }
    static isPopupMessageOptions(value: Object | string | number | undefined | boolean, duplicated_textColor: boolean, duplicated_font: boolean): boolean {
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
    static isPopupOptions(value: Object | string | number | undefined | boolean, duplicated_message: boolean, duplicated_placement: boolean, duplicated_primaryButton: boolean, duplicated_secondaryButton: boolean, duplicated_onStateChange: boolean, duplicated_arrowOffset: boolean, duplicated_showInSubWindow: boolean, duplicated_mask: boolean, duplicated_messageOptions: boolean, duplicated_targetSpace: boolean, duplicated_enableArrow: boolean, duplicated_offset: boolean, duplicated_popupColor: boolean, duplicated_autoCancel: boolean, duplicated_width: boolean, duplicated_arrowPointPosition: boolean, duplicated_arrowWidth: boolean, duplicated_arrowHeight: boolean, duplicated_radius: boolean, duplicated_shadow: boolean, duplicated_backgroundBlurStyle: boolean, duplicated_transition: boolean, duplicated_onWillDismiss: boolean, duplicated_enableHoverMode: boolean, duplicated_followTransformOfTarget: boolean, duplicated_keyboardAvoidMode: boolean): boolean {
        if ((!duplicated_message) && (value?.hasOwnProperty("message"))) {
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
        else if ((!duplicated_keyboardAvoidMode) && (value?.hasOwnProperty("keyboardAvoidMode"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof PopupOptions")
        }
    }
    static isPopupStateChangeParam(value: Object | string | number | undefined | boolean, duplicated_isVisible: boolean): boolean {
        if ((!duplicated_isVisible) && (value?.hasOwnProperty("isVisible"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof PopupStateChangeParam")
        }
    }
    static isPosition(value: Object | string | number | undefined | boolean, duplicated_x: boolean, duplicated_y: boolean): boolean {
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
    static isPositionWithAffinity(value: Object | string | number | undefined | boolean, duplicated_position: boolean): boolean {
        if ((!duplicated_position) && (value?.hasOwnProperty("position"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof PositionWithAffinity")
        }
    }
    static isPosterOptions(value: Object | string | number | undefined | boolean, duplicated_showFirstFrame: boolean): boolean {
        if ((!duplicated_showFirstFrame) && (value?.hasOwnProperty("showFirstFrame"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof PosterOptions")
        }
    }
    static isPostMessageOptions(value: Object | string | number | undefined | boolean, duplicated_transfer: boolean): boolean {
        if ((!duplicated_transfer) && (value?.hasOwnProperty("transfer"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof PostMessageOptions")
        }
    }
    static isPreDragStatus(value: Object | string | number | undefined | boolean): boolean {
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
        else if ((value) === (PreDragStatus.PREPARING_FOR_DRAG_DETECTION)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof PreDragStatus")
        }
    }
    static isPreparedInfo(value: Object | string | number | undefined | boolean, duplicated_duration: boolean): boolean {
        if ((!duplicated_duration) && (value?.hasOwnProperty("duration"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof PreparedInfo")
        }
    }
    static isPreviewConfiguration(value: Object | string | number | undefined | boolean, duplicated_onlyForLifting: boolean, duplicated_delayCreating: boolean): boolean {
        if ((!duplicated_onlyForLifting) && (value?.hasOwnProperty("onlyForLifting"))) {
            return true
        }
        else if ((!duplicated_delayCreating) && (value?.hasOwnProperty("delayCreating"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof PreviewConfiguration")
        }
    }
    static isPreviewMenuOptions(value: Object | string | number | undefined | boolean, duplicated_hapticFeedbackMode: boolean): boolean {
        if ((!duplicated_hapticFeedbackMode) && (value?.hasOwnProperty("hapticFeedbackMode"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof PreviewMenuOptions")
        }
    }
    static isPreviewText(value: Object | string | number | undefined | boolean, duplicated_offset: boolean, duplicated_value: boolean): boolean {
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
    static isProgressConfiguration(value: Object | string | number | undefined | boolean, duplicated_value: boolean, duplicated_total: boolean): boolean {
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
    static isProgressMask(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof ProgressMask")
    }
    static isProgressOptions(value: Object | string | number | undefined | boolean, duplicated_value: boolean, duplicated_total: boolean, duplicated_type: boolean): boolean {
        if ((!duplicated_value) && (value?.hasOwnProperty("value"))) {
            return true
        }
        else if ((!duplicated_total) && (value?.hasOwnProperty("total"))) {
            return true
        }
        else if ((!duplicated_type) && (value?.hasOwnProperty("type"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ProgressOptions")
        }
    }
    static isProgressStatus(value: Object | string | number | undefined | boolean): boolean {
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
    static isProgressStyle(value: Object | string | number | undefined | boolean): boolean {
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
    static isProgressStyleOptions(value: Object | string | number | undefined | boolean, duplicated_strokeWidth: boolean, duplicated_scaleCount: boolean, duplicated_scaleWidth: boolean): boolean {
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
    static isProgressType(value: Object | string | number | undefined | boolean): boolean {
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
    static isPromptAction(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof PromptAction")
    }
    static isProtectedResourceType(value: Object | string | number | undefined | boolean): boolean {
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
    static isPulseSymbolEffect(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof PulseSymbolEffect")
    }
    static isRadialGradientOptions(value: Object | string | number | undefined | boolean, duplicated_center: boolean, duplicated_radius: boolean, duplicated_colors: boolean, duplicated_repeating: boolean): boolean {
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
            throw new Error("Can not discriminate value typeof RadialGradientOptions")
        }
    }
    static isRadioConfiguration(value: Object | string | number | undefined | boolean, duplicated_value: boolean, duplicated_checked: boolean, duplicated_triggerChange: boolean): boolean {
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
    static isRadioIndicatorType(value: Object | string | number | undefined | boolean): boolean {
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
    static isRadioOptions(value: Object | string | number | undefined | boolean, duplicated_group: boolean, duplicated_value: boolean, duplicated_indicatorType: boolean, duplicated_indicatorBuilder: boolean): boolean {
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
    static isRadioStyle(value: Object | string | number | undefined | boolean, duplicated_checkedBackgroundColor: boolean, duplicated_uncheckedBorderColor: boolean, duplicated_indicatorColor: boolean): boolean {
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
    static isRatingConfiguration(value: Object | string | number | undefined | boolean, duplicated_rating: boolean, duplicated_indicator: boolean, duplicated_stars: boolean, duplicated_stepSize: boolean, duplicated_triggerChange: boolean): boolean {
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
    static isRatingOptions(value: Object | string | number | undefined | boolean, duplicated_rating: boolean, duplicated_indicator: boolean): boolean {
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
    static isRectangle(value: Object | string | number | undefined | boolean, duplicated_x: boolean, duplicated_y: boolean, duplicated_width: boolean, duplicated_height: boolean): boolean {
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
    static isRectOptions(value: Object | string | number | undefined | boolean, duplicated_width: boolean, duplicated_height: boolean, duplicated_radius: boolean): boolean {
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
    static isRectResult(value: Object | string | number | undefined | boolean, duplicated_x: boolean, duplicated_y: boolean, duplicated_width: boolean, duplicated_height: boolean): boolean {
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
    static isRectShape(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof RectShape")
    }
    static isRectShapeOptions(value: Object | string | number | undefined | boolean, duplicated_radius: boolean): boolean {
        if ((!duplicated_radius) && (value?.hasOwnProperty("radius"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RectShapeOptions")
        }
    }
    static isRefreshOptions(value: Object | string | number | undefined | boolean, duplicated_refreshing: boolean, duplicated_promptText: boolean, duplicated_builder: boolean, duplicated_refreshingContent: boolean): boolean {
        if ((!duplicated_refreshing) && (value?.hasOwnProperty("refreshing"))) {
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
    static isRefreshStatus(value: Object | string | number | undefined | boolean): boolean {
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
    static isRelateType(value: Object | string | number | undefined | boolean): boolean {
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
    static isRenderExitReason(value: Object | string | number | undefined | boolean): boolean {
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
    static isRenderFit(value: Object | string | number | undefined | boolean): boolean {
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
    static isRenderingContextSettings(value: Object | string | number | undefined | boolean, duplicated_antialias: boolean): boolean {
        if ((!duplicated_antialias) && (value?.hasOwnProperty("antialias"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RenderingContextSettings")
        }
    }
    static isRenderMode(value: Object | string | number | undefined | boolean): boolean {
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
    static isRenderNode(value: Object | string | number | undefined | boolean, duplicated_backgroundColor: boolean, duplicated_clipToFrame: boolean, duplicated_opacity: boolean, duplicated_size: boolean, duplicated_position: boolean, duplicated_frame: boolean, duplicated_pivot: boolean, duplicated_scale: boolean, duplicated_translation: boolean, duplicated_rotation: boolean, duplicated_transform: boolean, duplicated_shadowColor: boolean, duplicated_shadowOffset: boolean, duplicated_label: boolean, duplicated_shadowAlpha: boolean, duplicated_shadowElevation: boolean, duplicated_shadowRadius: boolean, duplicated_borderStyle: boolean, duplicated_borderWidth: boolean, duplicated_borderColor: boolean, duplicated_borderRadius: boolean, duplicated_shapeMask: boolean, duplicated_shapeClip: boolean, duplicated_markNodeGroup: boolean, duplicated_lengthMetricsUnit: boolean): boolean {
        if ((!duplicated_backgroundColor) && (value?.hasOwnProperty("backgroundColor"))) {
            return true
        }
        else if ((!duplicated_clipToFrame) && (value?.hasOwnProperty("clipToFrame"))) {
            return true
        }
        else if ((!duplicated_opacity) && (value?.hasOwnProperty("opacity"))) {
            return true
        }
        else if ((!duplicated_size) && (value?.hasOwnProperty("size"))) {
            return true
        }
        else if ((!duplicated_position) && (value?.hasOwnProperty("position"))) {
            return true
        }
        else if ((!duplicated_frame) && (value?.hasOwnProperty("frame"))) {
            return true
        }
        else if ((!duplicated_pivot) && (value?.hasOwnProperty("pivot"))) {
            return true
        }
        else if ((!duplicated_scale) && (value?.hasOwnProperty("scale"))) {
            return true
        }
        else if ((!duplicated_translation) && (value?.hasOwnProperty("translation"))) {
            return true
        }
        else if ((!duplicated_rotation) && (value?.hasOwnProperty("rotation"))) {
            return true
        }
        else if ((!duplicated_transform) && (value?.hasOwnProperty("transform"))) {
            return true
        }
        else if ((!duplicated_shadowColor) && (value?.hasOwnProperty("shadowColor"))) {
            return true
        }
        else if ((!duplicated_shadowOffset) && (value?.hasOwnProperty("shadowOffset"))) {
            return true
        }
        else if ((!duplicated_label) && (value?.hasOwnProperty("label"))) {
            return true
        }
        else if ((!duplicated_shadowAlpha) && (value?.hasOwnProperty("shadowAlpha"))) {
            return true
        }
        else if ((!duplicated_shadowElevation) && (value?.hasOwnProperty("shadowElevation"))) {
            return true
        }
        else if ((!duplicated_shadowRadius) && (value?.hasOwnProperty("shadowRadius"))) {
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
        else if ((!duplicated_shapeMask) && (value?.hasOwnProperty("shapeMask"))) {
            return true
        }
        else if ((!duplicated_shapeClip) && (value?.hasOwnProperty("shapeClip"))) {
            return true
        }
        else if ((!duplicated_markNodeGroup) && (value?.hasOwnProperty("markNodeGroup"))) {
            return true
        }
        else if ((!duplicated_lengthMetricsUnit) && (value?.hasOwnProperty("lengthMetricsUnit"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RenderNode")
        }
    }
    static isRenderProcessNotRespondingData(value: Object | string | number | undefined | boolean, duplicated_jsStack: boolean, duplicated_pid: boolean, duplicated_reason: boolean): boolean {
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
    static isRenderProcessNotRespondingReason(value: Object | string | number | undefined | boolean): boolean {
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
    static isRepeatMode(value: Object | string | number | undefined | boolean): boolean {
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
    static isReplaceSymbolEffect(value: Object | string | number | undefined | boolean, duplicated_scope: boolean): boolean {
        if ((!duplicated_scope) && (value?.hasOwnProperty("scope"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ReplaceSymbolEffect")
        }
    }
    static isResizableOptions(value: Object | string | number | undefined | boolean, duplicated_slice: boolean, duplicated_lattice: boolean): boolean {
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
    static isResource(value: Object | string | number | undefined | boolean, duplicated_bundleName: boolean, duplicated_moduleName: boolean, duplicated_id: boolean, duplicated_params: boolean, duplicated_type: boolean): boolean {
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
    static isResourceImageAttachmentOptions(value: Object | string | number | undefined | boolean, duplicated_resourceValue: boolean, duplicated_size: boolean, duplicated_verticalAlign: boolean, duplicated_objectFit: boolean, duplicated_layoutStyle: boolean, duplicated_colorFilter: boolean, duplicated_syncLoad: boolean): boolean {
        if ((!duplicated_resourceValue) && (value?.hasOwnProperty("resourceValue"))) {
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
        else if ((!duplicated_colorFilter) && (value?.hasOwnProperty("colorFilter"))) {
            return true
        }
        else if ((!duplicated_syncLoad) && (value?.hasOwnProperty("syncLoad"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ResourceImageAttachmentOptions")
        }
    }
    static isResponseType(value: Object | string | number | undefined | boolean): boolean {
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
    static isRestrictedWorker(value: Object | string | number | undefined | boolean, duplicated_onexit: boolean, duplicated_onerror: boolean, duplicated_onmessage: boolean, duplicated_onmessageerror: boolean): boolean {
        if ((!duplicated_onexit) && (value?.hasOwnProperty("onexit"))) {
            return true
        }
        else if ((!duplicated_onerror) && (value?.hasOwnProperty("onerror"))) {
            return true
        }
        else if ((!duplicated_onmessage) && (value?.hasOwnProperty("onmessage"))) {
            return true
        }
        else if ((!duplicated_onmessageerror) && (value?.hasOwnProperty("onmessageerror"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RestrictedWorker")
        }
    }
    static isReuseOptions(value: Object | string | number | undefined | boolean, duplicated_reuseId: boolean): boolean {
        if ((!duplicated_reuseId) && (value?.hasOwnProperty("reuseId"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ReuseOptions")
        }
    }
    static isRichEditorBaseController(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof RichEditorBaseController")
    }
    static isRichEditorBuilderSpanOptions(value: Object | string | number | undefined | boolean, duplicated_offset: boolean, duplicated_dragBackgroundColor: boolean, duplicated_isDragShadowNeeded: boolean): boolean {
        if ((!duplicated_offset) && (value?.hasOwnProperty("offset"))) {
            return true
        }
        else if ((!duplicated_dragBackgroundColor) && (value?.hasOwnProperty("dragBackgroundColor"))) {
            return true
        }
        else if ((!duplicated_isDragShadowNeeded) && (value?.hasOwnProperty("isDragShadowNeeded"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RichEditorBuilderSpanOptions")
        }
    }
    static isRichEditorChangeValue(value: Object | string | number | undefined | boolean, duplicated_rangeBefore: boolean, duplicated_replacedSpans: boolean, duplicated_replacedImageSpans: boolean, duplicated_replacedSymbolSpans: boolean): boolean {
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
    static isRichEditorController(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof RichEditorController")
    }
    static isRichEditorDeleteDirection(value: Object | string | number | undefined | boolean): boolean {
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
    static isRichEditorDeleteValue(value: Object | string | number | undefined | boolean, duplicated_offset: boolean, duplicated_direction: boolean, duplicated_length: boolean, duplicated_richEditorDeleteSpans: boolean): boolean {
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
    static isRichEditorGesture(value: Object | string | number | undefined | boolean, duplicated_onClick: boolean, duplicated_onLongPress: boolean, duplicated_onDoubleClick: boolean): boolean {
        if ((!duplicated_onClick) && (value?.hasOwnProperty("onClick"))) {
            return true
        }
        else if ((!duplicated_onLongPress) && (value?.hasOwnProperty("onLongPress"))) {
            return true
        }
        else if ((!duplicated_onDoubleClick) && (value?.hasOwnProperty("onDoubleClick"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RichEditorGesture")
        }
    }
    static isRichEditorImageSpanOptions(value: Object | string | number | undefined | boolean, duplicated_offset: boolean, duplicated_imageStyle: boolean, duplicated_gesture: boolean, duplicated_onHover: boolean): boolean {
        if ((!duplicated_offset) && (value?.hasOwnProperty("offset"))) {
            return true
        }
        else if ((!duplicated_imageStyle) && (value?.hasOwnProperty("imageStyle"))) {
            return true
        }
        else if ((!duplicated_gesture) && (value?.hasOwnProperty("gesture"))) {
            return true
        }
        else if ((!duplicated_onHover) && (value?.hasOwnProperty("onHover"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RichEditorImageSpanOptions")
        }
    }
    static isRichEditorImageSpanResult(value: Object | string | number | undefined | boolean, duplicated_spanPosition: boolean, duplicated_valuePixelMap: boolean, duplicated_valueResourceStr: boolean, duplicated_imageStyle: boolean, duplicated_offsetInSpan: boolean): boolean {
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
    static isRichEditorImageSpanStyle(value: Object | string | number | undefined | boolean, duplicated_size: boolean, duplicated_verticalAlign: boolean, duplicated_objectFit: boolean, duplicated_layoutStyle: boolean): boolean {
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
    static isRichEditorImageSpanStyleResult(value: Object | string | number | undefined | boolean, duplicated_size: boolean, duplicated_verticalAlign: boolean, duplicated_objectFit: boolean, duplicated_layoutStyle: boolean): boolean {
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
    static isRichEditorInsertValue(value: Object | string | number | undefined | boolean, duplicated_insertOffset: boolean, duplicated_insertValue: boolean, duplicated_previewText: boolean): boolean {
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
    static isRichEditorLayoutStyle(value: Object | string | number | undefined | boolean, duplicated_margin: boolean, duplicated_borderRadius: boolean): boolean {
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
    static isRichEditorOptions(value: Object | string | number | undefined | boolean, duplicated_controller: boolean): boolean {
        if ((!duplicated_controller) && (value?.hasOwnProperty("controller"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RichEditorOptions")
        }
    }
    static isRichEditorParagraphResult(value: Object | string | number | undefined | boolean, duplicated_style: boolean, duplicated_range: boolean): boolean {
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
    static isRichEditorParagraphStyle(value: Object | string | number | undefined | boolean, duplicated_textAlign: boolean, duplicated_leadingMargin: boolean, duplicated_wordBreak: boolean, duplicated_lineBreakStrategy: boolean, duplicated_paragraphSpacing: boolean): boolean {
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
        else if ((!duplicated_paragraphSpacing) && (value?.hasOwnProperty("paragraphSpacing"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RichEditorParagraphStyle")
        }
    }
    static isRichEditorParagraphStyleOptions(value: Object | string | number | undefined | boolean, duplicated_style: boolean): boolean {
        if ((!duplicated_style) && (value?.hasOwnProperty("style"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RichEditorParagraphStyleOptions")
        }
    }
    static isRichEditorRange(value: Object | string | number | undefined | boolean, duplicated_start: boolean, duplicated_end: boolean): boolean {
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
    static isRichEditorResponseType(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (RichEditorResponseType.RIGHT_CLICK)) {
            return true
        }
        else if ((value) === (RichEditorResponseType.LONG_PRESS)) {
            return true
        }
        else if ((value) === (RichEditorResponseType.SELECT)) {
            return true
        }
        else if ((value) === (RichEditorResponseType.DEFAULT)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RichEditorResponseType")
        }
    }
    static isRichEditorSelection(value: Object | string | number | undefined | boolean, duplicated_selection: boolean, duplicated_spans: boolean): boolean {
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
    static isRichEditorSpanPosition(value: Object | string | number | undefined | boolean, duplicated_spanIndex: boolean, duplicated_spanRange: boolean): boolean {
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
    static isRichEditorSpanType(value: Object | string | number | undefined | boolean): boolean {
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
        else if ((value) === (RichEditorSpanType.DEFAULT)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RichEditorSpanType")
        }
    }
    static isRichEditorStyledStringController(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof RichEditorStyledStringController")
    }
    static isRichEditorStyledStringOptions(value: Object | string | number | undefined | boolean, duplicated_controller: boolean): boolean {
        if ((!duplicated_controller) && (value?.hasOwnProperty("controller"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RichEditorStyledStringOptions")
        }
    }
    static isRichEditorSymbolSpanOptions(value: Object | string | number | undefined | boolean, duplicated_offset: boolean, duplicated_style: boolean): boolean {
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
    static isRichEditorSymbolSpanStyle(value: Object | string | number | undefined | boolean, duplicated_fontSize: boolean, duplicated_fontColor: boolean, duplicated_fontWeight: boolean, duplicated_effectStrategy: boolean, duplicated_renderingStrategy: boolean): boolean {
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
    static isRichEditorTextSpanOptions(value: Object | string | number | undefined | boolean, duplicated_offset: boolean, duplicated_style: boolean, duplicated_paragraphStyle: boolean, duplicated_gesture: boolean, duplicated_urlStyle: boolean): boolean {
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
        else if ((!duplicated_urlStyle) && (value?.hasOwnProperty("urlStyle"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RichEditorTextSpanOptions")
        }
    }
    static isRichEditorTextSpanResult(value: Object | string | number | undefined | boolean, duplicated_spanPosition: boolean, duplicated_value: boolean, duplicated_textStyle: boolean, duplicated_offsetInSpan: boolean, duplicated_symbolSpanStyle: boolean, duplicated_valueResource: boolean, duplicated_paragraphStyle: boolean, duplicated_previewText: boolean, duplicated_urlStyle: boolean): boolean {
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
        else if ((!duplicated_urlStyle) && (value?.hasOwnProperty("urlStyle"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RichEditorTextSpanResult")
        }
    }
    static isRichEditorTextStyle(value: Object | string | number | undefined | boolean, duplicated_fontColor: boolean, duplicated_fontSize: boolean, duplicated_fontStyle: boolean, duplicated_fontWeight: boolean, duplicated_fontFamily: boolean, duplicated_decoration: boolean, duplicated_textShadow: boolean, duplicated_letterSpacing: boolean, duplicated_lineHeight: boolean, duplicated_halfLeading: boolean, duplicated_fontFeature: boolean, duplicated_textBackgroundStyle: boolean): boolean {
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
        else if ((!duplicated_halfLeading) && (value?.hasOwnProperty("halfLeading"))) {
            return true
        }
        else if ((!duplicated_fontFeature) && (value?.hasOwnProperty("fontFeature"))) {
            return true
        }
        else if ((!duplicated_textBackgroundStyle) && (value?.hasOwnProperty("textBackgroundStyle"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RichEditorTextStyle")
        }
    }
    static isRichEditorTextStyleResult(value: Object | string | number | undefined | boolean, duplicated_fontColor: boolean, duplicated_fontSize: boolean, duplicated_fontStyle: boolean, duplicated_fontWeight: boolean, duplicated_fontFamily: boolean, duplicated_decoration: boolean, duplicated_textShadow: boolean, duplicated_letterSpacing: boolean, duplicated_lineHeight: boolean, duplicated_halfLeading: boolean, duplicated_fontFeature: boolean, duplicated_textBackgroundStyle: boolean): boolean {
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
        else if ((!duplicated_halfLeading) && (value?.hasOwnProperty("halfLeading"))) {
            return true
        }
        else if ((!duplicated_fontFeature) && (value?.hasOwnProperty("fontFeature"))) {
            return true
        }
        else if ((!duplicated_textBackgroundStyle) && (value?.hasOwnProperty("textBackgroundStyle"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RichEditorTextStyleResult")
        }
    }
    static isRichEditorUpdateImageSpanStyleOptions(value: Object | string | number | undefined | boolean, duplicated_imageStyle: boolean): boolean {
        if ((!duplicated_imageStyle) && (value?.hasOwnProperty("imageStyle"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RichEditorUpdateImageSpanStyleOptions")
        }
    }
    static isRichEditorUpdateSymbolSpanStyleOptions(value: Object | string | number | undefined | boolean, duplicated_symbolStyle: boolean): boolean {
        if ((!duplicated_symbolStyle) && (value?.hasOwnProperty("symbolStyle"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RichEditorUpdateSymbolSpanStyleOptions")
        }
    }
    static isRichEditorUpdateTextSpanStyleOptions(value: Object | string | number | undefined | boolean, duplicated_textStyle: boolean, duplicated_urlStyle: boolean): boolean {
        if ((!duplicated_textStyle) && (value?.hasOwnProperty("textStyle"))) {
            return true
        }
        else if ((!duplicated_urlStyle) && (value?.hasOwnProperty("urlStyle"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RichEditorUpdateTextSpanStyleOptions")
        }
    }
    static isRichEditorUrlStyle(value: Object | string | number | undefined | boolean, duplicated_url: boolean): boolean {
        if ((!duplicated_url) && (value?.hasOwnProperty("url"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RichEditorUrlStyle")
        }
    }
    static isRingStyleOptions(value: Object | string | number | undefined | boolean, duplicated_strokeWidth: boolean, duplicated_shadow: boolean, duplicated_status: boolean): boolean {
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
    static isRootSceneSession(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof RootSceneSession")
    }
    static isRotateOptions(value: Object | string | number | undefined | boolean, duplicated_x: boolean, duplicated_y: boolean, duplicated_z: boolean, duplicated_centerX: boolean, duplicated_centerY: boolean, duplicated_centerZ: boolean, duplicated_perspective: boolean, duplicated_angle: boolean): boolean {
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
    static isRotateResult(value: Object | string | number | undefined | boolean, duplicated_x: boolean, duplicated_y: boolean, duplicated_z: boolean, duplicated_centerX: boolean, duplicated_centerY: boolean, duplicated_angle: boolean): boolean {
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
        else if ((!duplicated_angle) && (value?.hasOwnProperty("angle"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RotateResult")
        }
    }
    static isRotationGesture(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof RotationGesture")
    }
    static isRotationGestureEvent(value: Object | string | number | undefined | boolean, duplicated_angle: boolean): boolean {
        if ((!duplicated_angle) && (value?.hasOwnProperty("angle"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RotationGestureEvent")
        }
    }
    static isRotationGestureHandlerOptions(value: Object | string | number | undefined | boolean, duplicated_fingers: boolean, duplicated_angle: boolean): boolean {
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
    static isRotationRecognizer(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof RotationRecognizer")
    }
    static isRoundedRectOptions(value: Object | string | number | undefined | boolean, duplicated_width: boolean, duplicated_height: boolean, duplicated_radiusWidth: boolean, duplicated_radiusHeight: boolean): boolean {
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
    static isRoundRect(value: Object | string | number | undefined | boolean, duplicated_rect: boolean, duplicated_corners: boolean): boolean {
        if ((!duplicated_rect) && (value?.hasOwnProperty("rect"))) {
            return true
        }
        else if ((!duplicated_corners) && (value?.hasOwnProperty("corners"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RoundRect")
        }
    }
    static isRoundRectShapeOptions(value: Object | string | number | undefined | boolean, duplicated_radiusWidth: boolean, duplicated_radiusHeight: boolean): boolean {
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
    static isRouteMapConfig(value: Object | string | number | undefined | boolean, duplicated_name: boolean, duplicated_pageSourceFile: boolean, duplicated_data: boolean): boolean {
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
    static isRouteType(value: Object | string | number | undefined | boolean): boolean {
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
    static isRowOptions(value: Object | string | number | undefined | boolean, duplicated_space: boolean): boolean {
        if ((!duplicated_space) && (value?.hasOwnProperty("space"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RowOptions")
        }
    }
    static isRowOptionsV2(value: Object | string | number | undefined | boolean, duplicated__stub: boolean): boolean {
        if ((!duplicated__stub) && (value?.hasOwnProperty("_stub"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof RowOptionsV2")
        }
    }
    static isRRect(value: Object | string | number | undefined | boolean, duplicated_left: boolean, duplicated_top: boolean, duplicated_width: boolean, duplicated_height: boolean, duplicated_radius: boolean): boolean {
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
    static isSafeAreaEdge(value: Object | string | number | undefined | boolean): boolean {
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
    static isSafeAreaType(value: Object | string | number | undefined | boolean): boolean {
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
    static isSaveButtonOnClickResult(value: Object | string | number | undefined | boolean): boolean {
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
    static isSaveButtonOptions(value: Object | string | number | undefined | boolean, duplicated_icon: boolean, duplicated_text: boolean, duplicated_buttonType: boolean): boolean {
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
    static isSaveDescription(value: Object | string | number | undefined | boolean): boolean {
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
        else if ((value) === (SaveDescription.SAVE_ALL)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SaveDescription")
        }
    }
    static isSaveIconStyle(value: Object | string | number | undefined | boolean): boolean {
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
    static isScaleOptions(value: Object | string | number | undefined | boolean, duplicated_x: boolean, duplicated_y: boolean, duplicated_z: boolean, duplicated_centerX: boolean, duplicated_centerY: boolean): boolean {
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
    static isScaleResult(value: Object | string | number | undefined | boolean, duplicated_x: boolean, duplicated_y: boolean, duplicated_z: boolean, duplicated_centerX: boolean, duplicated_centerY: boolean): boolean {
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
            throw new Error("Can not discriminate value typeof ScaleResult")
        }
    }
    static isScaleSymbolEffect(value: Object | string | number | undefined | boolean, duplicated_scope: boolean, duplicated_direction: boolean): boolean {
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
    static isScene(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof Scene")
    }
    static isScreenCaptureConfig(value: Object | string | number | undefined | boolean, duplicated_captureMode: boolean): boolean {
        if ((!duplicated_captureMode) && (value?.hasOwnProperty("captureMode"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ScreenCaptureConfig")
        }
    }
    static isScreenCaptureHandler(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof ScreenCaptureHandler")
    }
    static isScriptItem(value: Object | string | number | undefined | boolean, duplicated_script: boolean, duplicated_scriptRules: boolean): boolean {
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
    static isScrollableBarModeOptions(value: Object | string | number | undefined | boolean, duplicated_margin: boolean, duplicated_nonScrollableLayoutStyle: boolean): boolean {
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
    static isScrollableTargetInfo(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof ScrollableTargetInfo")
    }
    static isScrollAlign(value: Object | string | number | undefined | boolean): boolean {
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
    static isScrollAnimationOptions(value: Object | string | number | undefined | boolean, duplicated_duration: boolean, duplicated_curve: boolean, duplicated_canOverScroll: boolean): boolean {
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
    static isScrollBarDirection(value: Object | string | number | undefined | boolean): boolean {
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
    static isScrollBarOptions(value: Object | string | number | undefined | boolean, duplicated_scroller: boolean, duplicated_direction: boolean, duplicated_state: boolean): boolean {
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
    static isScrollDirection(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (ScrollDirection.Vertical)) {
            return true
        }
        else if ((value) === (ScrollDirection.Horizontal)) {
            return true
        }
        else if ((value) === (ScrollDirection.None)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ScrollDirection")
        }
    }
    static isScrollEdgeOptions(value: Object | string | number | undefined | boolean, duplicated_velocity: boolean): boolean {
        if ((!duplicated_velocity) && (value?.hasOwnProperty("velocity"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ScrollEdgeOptions")
        }
    }
    static isScroller(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof Scroller")
    }
    static isScrollMotion(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof ScrollMotion")
    }
    static isScrollOptions(value: Object | string | number | undefined | boolean, duplicated_xOffset: boolean, duplicated_yOffset: boolean, duplicated_animation: boolean): boolean {
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
    static isScrollPageOptions(value: Object | string | number | undefined | boolean, duplicated_next: boolean, duplicated_animation: boolean): boolean {
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
    static isScrollResult(value: Object | string | number | undefined | boolean, duplicated_offsetRemain: boolean): boolean {
        if ((!duplicated_offsetRemain) && (value?.hasOwnProperty("offsetRemain"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ScrollResult")
        }
    }
    static isScrollSizeMode(value: Object | string | number | undefined | boolean): boolean {
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
    static isScrollSnapAlign(value: Object | string | number | undefined | boolean): boolean {
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
    static isScrollSnapOptions(value: Object | string | number | undefined | boolean, duplicated_snapAlign: boolean, duplicated_snapPagination: boolean, duplicated_enableSnapToStart: boolean, duplicated_enableSnapToEnd: boolean): boolean {
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
    static isScrollSource(value: Object | string | number | undefined | boolean): boolean {
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
    static isScrollState(value: Object | string | number | undefined | boolean): boolean {
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
    static isScrollToIndexOptions(value: Object | string | number | undefined | boolean, duplicated_extraOffset: boolean): boolean {
        if ((!duplicated_extraOffset) && (value?.hasOwnProperty("extraOffset"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ScrollToIndexOptions")
        }
    }
    static isSearchButtonOptions(value: Object | string | number | undefined | boolean, duplicated_fontSize: boolean, duplicated_fontColor: boolean, duplicated_autoDisable: boolean): boolean {
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
    static isSearchController(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof SearchController")
    }
    static isSearchOptions(value: Object | string | number | undefined | boolean, duplicated_value: boolean, duplicated_placeholder: boolean, duplicated_icon: boolean, duplicated_controller: boolean): boolean {
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
    static isSearchType(value: Object | string | number | undefined | boolean): boolean {
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
    static isSectionOptions(value: Object | string | number | undefined | boolean, duplicated_itemsCount: boolean, duplicated_crossCount: boolean, duplicated_onGetItemMainSizeByIndex: boolean, duplicated_columnsGap: boolean, duplicated_rowsGap: boolean, duplicated_margin: boolean): boolean {
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
    static isSecurityComponentLayoutDirection(value: Object | string | number | undefined | boolean): boolean {
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
    static isSeekMode(value: Object | string | number | undefined | boolean): boolean {
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
    static isSelectedMode(value: Object | string | number | undefined | boolean): boolean {
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
    static isSelectionMenuOptions(value: Object | string | number | undefined | boolean, duplicated_onAppear: boolean, duplicated_onDisappear: boolean, duplicated_menuType: boolean, duplicated_onMenuShow: boolean, duplicated_onMenuHide: boolean, duplicated_previewMenuOptions: boolean): boolean {
        if ((!duplicated_onAppear) && (value?.hasOwnProperty("onAppear"))) {
            return true
        }
        else if ((!duplicated_onDisappear) && (value?.hasOwnProperty("onDisappear"))) {
            return true
        }
        else if ((!duplicated_menuType) && (value?.hasOwnProperty("menuType"))) {
            return true
        }
        else if ((!duplicated_onMenuShow) && (value?.hasOwnProperty("onMenuShow"))) {
            return true
        }
        else if ((!duplicated_onMenuHide) && (value?.hasOwnProperty("onMenuHide"))) {
            return true
        }
        else if ((!duplicated_previewMenuOptions) && (value?.hasOwnProperty("previewMenuOptions"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SelectionMenuOptions")
        }
    }
    static isSelectionMenuOptionsExt(value: Object | string | number | undefined | boolean, duplicated_onAppear: boolean, duplicated_onDisappear: boolean, duplicated_preview: boolean, duplicated_menuType: boolean): boolean {
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
    static isSelectionOptions(value: Object | string | number | undefined | boolean, duplicated_menuPolicy: boolean): boolean {
        if ((!duplicated_menuPolicy) && (value?.hasOwnProperty("menuPolicy"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SelectionOptions")
        }
    }
    static isSelectOption(value: Object | string | number | undefined | boolean, duplicated_value: boolean, duplicated_icon: boolean, duplicated_symbolIcon: boolean): boolean {
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
    static isSelectStatus(value: Object | string | number | undefined | boolean): boolean {
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
    static isShadowOptions(value: Object | string | number | undefined | boolean, duplicated_radius: boolean, duplicated_type: boolean, duplicated_color: boolean, duplicated_offsetX: boolean, duplicated_offsetY: boolean, duplicated_fill: boolean): boolean {
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
    static isShadowStyle(value: Object | string | number | undefined | boolean): boolean {
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
    static isShadowType(value: Object | string | number | undefined | boolean): boolean {
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
    static isShapeClip(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof ShapeClip")
    }
    static isShapeMask(value: Object | string | number | undefined | boolean, duplicated_fillColor: boolean, duplicated_strokeColor: boolean, duplicated_strokeWidth: boolean): boolean {
        if ((!duplicated_fillColor) && (value?.hasOwnProperty("fillColor"))) {
            return true
        }
        else if ((!duplicated_strokeColor) && (value?.hasOwnProperty("strokeColor"))) {
            return true
        }
        else if ((!duplicated_strokeWidth) && (value?.hasOwnProperty("strokeWidth"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ShapeMask")
        }
    }
    static isShapeSize(value: Object | string | number | undefined | boolean, duplicated_width: boolean, duplicated_height: boolean): boolean {
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
    static isSharedTransitionEffectType(value: Object | string | number | undefined | boolean): boolean {
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
    static issharedTransitionOptions(value: Object | string | number | undefined | boolean, duplicated_duration: boolean, duplicated_curve: boolean, duplicated_delay: boolean, duplicated_motionPath: boolean, duplicated_zIndex: boolean, duplicated_type: boolean): boolean {
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
    static isSheetDismiss(value: Object | string | number | undefined | boolean, duplicated_dismiss: boolean): boolean {
        if ((!duplicated_dismiss) && (value?.hasOwnProperty("dismiss"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SheetDismiss")
        }
    }
    static isSheetKeyboardAvoidMode(value: Object | string | number | undefined | boolean): boolean {
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
    static isSheetMode(value: Object | string | number | undefined | boolean): boolean {
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
    static isSheetOptions(value: Object | string | number | undefined | boolean, duplicated_height: boolean, duplicated_dragBar: boolean, duplicated_maskColor: boolean, duplicated_detents: boolean, duplicated_blurStyle: boolean, duplicated_showClose: boolean, duplicated_preferType: boolean, duplicated_title: boolean, duplicated_shouldDismiss: boolean, duplicated_onWillDismiss: boolean, duplicated_onWillSpringBackWhenDismiss: boolean, duplicated_enableOutsideInteractive: boolean, duplicated_width: boolean, duplicated_borderWidth: boolean, duplicated_borderColor: boolean, duplicated_borderStyle: boolean, duplicated_shadow: boolean, duplicated_onHeightDidChange: boolean, duplicated_mode: boolean, duplicated_scrollSizeMode: boolean, duplicated_onDetentsDidChange: boolean, duplicated_onWidthDidChange: boolean, duplicated_onTypeDidChange: boolean, duplicated_uiContext: boolean, duplicated_keyboardAvoidMode: boolean, duplicated_enableHoverMode: boolean, duplicated_hoverModeArea: boolean, duplicated_offset: boolean, duplicated_effectEdge: boolean, duplicated_radius: boolean, duplicated_detentSelection: boolean, duplicated_showInSubWindow: boolean, duplicated_placement: boolean, duplicated_placementOnTarget: boolean): boolean {
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
        else if ((!duplicated_enableHoverMode) && (value?.hasOwnProperty("enableHoverMode"))) {
            return true
        }
        else if ((!duplicated_hoverModeArea) && (value?.hasOwnProperty("hoverModeArea"))) {
            return true
        }
        else if ((!duplicated_offset) && (value?.hasOwnProperty("offset"))) {
            return true
        }
        else if ((!duplicated_effectEdge) && (value?.hasOwnProperty("effectEdge"))) {
            return true
        }
        else if ((!duplicated_radius) && (value?.hasOwnProperty("radius"))) {
            return true
        }
        else if ((!duplicated_detentSelection) && (value?.hasOwnProperty("detentSelection"))) {
            return true
        }
        else if ((!duplicated_showInSubWindow) && (value?.hasOwnProperty("showInSubWindow"))) {
            return true
        }
        else if ((!duplicated_placement) && (value?.hasOwnProperty("placement"))) {
            return true
        }
        else if ((!duplicated_placementOnTarget) && (value?.hasOwnProperty("placementOnTarget"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SheetOptions")
        }
    }
    static isSheetSize(value: Object | string | number | undefined | boolean): boolean {
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
    static isSheetTitleOptions(value: Object | string | number | undefined | boolean, duplicated_title: boolean, duplicated_subtitle: boolean): boolean {
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
    static isSheetType(value: Object | string | number | undefined | boolean): boolean {
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
    static isSideBarContainerType(value: Object | string | number | undefined | boolean): boolean {
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
    static isSideBarPosition(value: Object | string | number | undefined | boolean): boolean {
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
    static isSize(value: Object | string | number | undefined | boolean, duplicated_width: boolean, duplicated_height: boolean): boolean {
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
    static isSizeOptions(value: Object | string | number | undefined | boolean, duplicated_width: boolean, duplicated_height: boolean): boolean {
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
    static isSizeResult(value: Object | string | number | undefined | boolean, duplicated_width: boolean, duplicated_height: boolean): boolean {
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
    static isSlideEffect(value: Object | string | number | undefined | boolean): boolean {
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
    static isSlideRange(value: Object | string | number | undefined | boolean, duplicated_from: boolean, duplicated_to: boolean): boolean {
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
    static isSliderBlockStyle(value: Object | string | number | undefined | boolean, duplicated_type: boolean, duplicated_image: boolean): boolean {
        if ((!duplicated_type) && (value?.hasOwnProperty("type"))) {
            return true
        }
        else if ((!duplicated_image) && (value?.hasOwnProperty("image"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SliderBlockStyle")
        }
    }
    static isSliderBlockType(value: Object | string | number | undefined | boolean): boolean {
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
    static isSliderChangeMode(value: Object | string | number | undefined | boolean): boolean {
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
    static isSliderConfiguration(value: Object | string | number | undefined | boolean, duplicated_value: boolean, duplicated_min: boolean, duplicated_max: boolean, duplicated_step: boolean, duplicated_triggerChange: boolean): boolean {
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
    static isSliderInteraction(value: Object | string | number | undefined | boolean): boolean {
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
    static isSliderOptions(value: Object | string | number | undefined | boolean, duplicated_value: boolean, duplicated_min: boolean, duplicated_max: boolean, duplicated_step: boolean, duplicated_style: boolean, duplicated_direction: boolean, duplicated_reverse: boolean): boolean {
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
    static isSliderStyle(value: Object | string | number | undefined | boolean): boolean {
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
    static isSnapshotOptions(value: Object | string | number | undefined | boolean, duplicated_scale: boolean, duplicated_waitUntilRenderFinished: boolean): boolean {
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
    static isSourceTool(value: Object | string | number | undefined | boolean): boolean {
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
    static isSourceType(value: Object | string | number | undefined | boolean): boolean {
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
    static isSpanStyle(value: Object | string | number | undefined | boolean, duplicated_start: boolean, duplicated_length: boolean, duplicated_styledKey: boolean, duplicated_styledValue: boolean): boolean {
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
    static isSpringBackAction(value: Object | string | number | undefined | boolean, duplicated_springBack: boolean): boolean {
        if ((!duplicated_springBack) && (value?.hasOwnProperty("springBack"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SpringBackAction")
        }
    }
    static isSpringMotion(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof SpringMotion")
    }
    static isSpringProp(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof SpringProp")
    }
    static isSslError(value: Object | string | number | undefined | boolean): boolean {
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
    static isSslErrorEvent(value: Object | string | number | undefined | boolean, duplicated_handler: boolean, duplicated_error: boolean, duplicated_url: boolean, duplicated_originalUrl: boolean, duplicated_referrer: boolean, duplicated_isFatalError: boolean, duplicated_isMainFrame: boolean): boolean {
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
    static isSslErrorHandler(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof SslErrorHandler")
    }
    static isStackOptions(value: Object | string | number | undefined | boolean, duplicated_alignContent: boolean): boolean {
        if ((!duplicated_alignContent) && (value?.hasOwnProperty("alignContent"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof StackOptions")
        }
    }
    static isStarStyleOptions(value: Object | string | number | undefined | boolean, duplicated_backgroundUri: boolean, duplicated_foregroundUri: boolean, duplicated_secondaryUri: boolean): boolean {
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
    static isStateStyles(value: Object | string | number | undefined | boolean, duplicated_normal: boolean, duplicated_pressed: boolean, duplicated_disabled: boolean, duplicated_focused: boolean, duplicated_clicked: boolean, duplicated_selected: boolean): boolean {
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
    static isStepperOptions(value: Object | string | number | undefined | boolean, duplicated_index: boolean): boolean {
        if ((!duplicated_index) && (value?.hasOwnProperty("index"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof StepperOptions")
        }
    }
    static isStickyStyle(value: Object | string | number | undefined | boolean): boolean {
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
    static isStyledString(value: Object | string | number | undefined | boolean, duplicated_length: boolean): boolean {
        if ((!duplicated_length) && (value?.hasOwnProperty("length"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof StyledString")
        }
    }
    static isStyledStringChangedListener(value: Object | string | number | undefined | boolean, duplicated_onWillChange: boolean, duplicated_onDidChange: boolean): boolean {
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
    static isStyledStringChangeValue(value: Object | string | number | undefined | boolean, duplicated_range: boolean, duplicated_replacementString: boolean, duplicated_previewText: boolean): boolean {
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
    static isStyledStringController(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof StyledStringController")
    }
    static isStyledStringKey(value: Object | string | number | undefined | boolean): boolean {
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
    static isStyleOptions(value: Object | string | number | undefined | boolean, duplicated_start: boolean, duplicated_length: boolean, duplicated_styledKey: boolean, duplicated_styledValue: boolean): boolean {
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
    static isSubMenuExpandingMode(value: Object | string | number | undefined | boolean): boolean {
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
    static isSubmitEvent(value: Object | string | number | undefined | boolean, duplicated_text: boolean): boolean {
        if ((!duplicated_text) && (value?.hasOwnProperty("text"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SubmitEvent")
        }
    }
    static isSubTabBarIndicatorStyle(value: Object | string | number | undefined | boolean, duplicated_color: boolean, duplicated_height: boolean, duplicated_width: boolean, duplicated_borderRadius: boolean, duplicated_marginTop: boolean): boolean {
        if ((!duplicated_color) && (value?.hasOwnProperty("color"))) {
            return true
        }
        else if ((!duplicated_height) && (value?.hasOwnProperty("height"))) {
            return true
        }
        else if ((!duplicated_width) && (value?.hasOwnProperty("width"))) {
            return true
        }
        else if ((!duplicated_borderRadius) && (value?.hasOwnProperty("borderRadius"))) {
            return true
        }
        else if ((!duplicated_marginTop) && (value?.hasOwnProperty("marginTop"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SubTabBarIndicatorStyle")
        }
    }
    static isSubTabBarStyle(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof SubTabBarStyle")
    }
    static isSurfaceRect(value: Object | string | number | undefined | boolean, duplicated_offsetX: boolean, duplicated_offsetY: boolean, duplicated_surfaceWidth: boolean, duplicated_surfaceHeight: boolean): boolean {
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
    static isSurfaceRotationOptions(value: Object | string | number | undefined | boolean, duplicated_lock: boolean): boolean {
        if ((!duplicated_lock) && (value?.hasOwnProperty("lock"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SurfaceRotationOptions")
        }
    }
    static isSweepGradientOptions(value: Object | string | number | undefined | boolean, duplicated_center: boolean, duplicated_start: boolean, duplicated_end: boolean, duplicated_rotation: boolean, duplicated_colors: boolean, duplicated_repeating: boolean): boolean {
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
            throw new Error("Can not discriminate value typeof SweepGradientOptions")
        }
    }
    static isSwipeActionItem(value: Object | string | number | undefined | boolean, duplicated_builder: boolean, duplicated_builderComponent: boolean, duplicated_actionAreaDistance: boolean, duplicated_onAction: boolean, duplicated_onEnterActionArea: boolean, duplicated_onExitActionArea: boolean, duplicated_onStateChange: boolean): boolean {
        if ((!duplicated_builder) && (value?.hasOwnProperty("builder"))) {
            return true
        }
        else if ((!duplicated_builderComponent) && (value?.hasOwnProperty("builderComponent"))) {
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
    static isSwipeActionOptions(value: Object | string | number | undefined | boolean, duplicated_start: boolean, duplicated_end: boolean, duplicated_edgeEffect: boolean, duplicated_onOffsetChange: boolean): boolean {
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
    static isSwipeActionState(value: Object | string | number | undefined | boolean): boolean {
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
    static isSwipeDirection(value: Object | string | number | undefined | boolean): boolean {
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
    static isSwipeEdgeEffect(value: Object | string | number | undefined | boolean): boolean {
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
    static isSwipeGesture(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof SwipeGesture")
    }
    static isSwipeGestureEvent(value: Object | string | number | undefined | boolean, duplicated_angle: boolean, duplicated_speed: boolean): boolean {
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
    static isSwipeGestureHandlerOptions(value: Object | string | number | undefined | boolean, duplicated_fingers: boolean, duplicated_direction: boolean, duplicated_speed: boolean): boolean {
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
    static isSwiperAnimationEvent(value: Object | string | number | undefined | boolean, duplicated_currentOffset: boolean, duplicated_targetOffset: boolean, duplicated_velocity: boolean): boolean {
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
    static isSwiperAnimationMode(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (SwiperAnimationMode.NO_ANIMATION)) {
            return true
        }
        else if ((value) === (SwiperAnimationMode.DEFAULT_ANIMATION)) {
            return true
        }
        else if ((value) === (SwiperAnimationMode.FAST_ANIMATION)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SwiperAnimationMode")
        }
    }
    static isSwiperAutoFill(value: Object | string | number | undefined | boolean, duplicated_minSize: boolean): boolean {
        if ((!duplicated_minSize) && (value?.hasOwnProperty("minSize"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SwiperAutoFill")
        }
    }
    static isSwiperContentAnimatedTransition(value: Object | string | number | undefined | boolean, duplicated_timeout: boolean, duplicated_transition: boolean): boolean {
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
    static isSwiperContentTransitionProxy(value: Object | string | number | undefined | boolean, duplicated_selectedIndex: boolean, duplicated_index: boolean, duplicated_position: boolean, duplicated_mainAxisLength: boolean): boolean {
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
    static isSwiperContentWillScrollResult(value: Object | string | number | undefined | boolean, duplicated_currentIndex: boolean, duplicated_comingIndex: boolean, duplicated_offset: boolean): boolean {
        if ((!duplicated_currentIndex) && (value?.hasOwnProperty("currentIndex"))) {
            return true
        }
        else if ((!duplicated_comingIndex) && (value?.hasOwnProperty("comingIndex"))) {
            return true
        }
        else if ((!duplicated_offset) && (value?.hasOwnProperty("offset"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SwiperContentWillScrollResult")
        }
    }
    static isSwiperController(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof SwiperController")
    }
    static isSwiperDisplayMode(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (SwiperDisplayMode.STRETCH)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SwiperDisplayMode")
        }
    }
    static isSwipeRecognizer(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof SwipeRecognizer")
    }
    static isSwiperNestedScrollMode(value: Object | string | number | undefined | boolean): boolean {
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
    static isSwitchStyle(value: Object | string | number | undefined | boolean, duplicated_pointRadius: boolean, duplicated_unselectedColor: boolean, duplicated_pointColor: boolean, duplicated_trackBorderRadius: boolean): boolean {
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
    static isSymbolEffect(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof SymbolEffect")
    }
    static isSymbolEffectStrategy(value: Object | string | number | undefined | boolean): boolean {
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
    static isSymbolGlyphModifier(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof SymbolGlyphModifier")
    }
    static isSymbolRenderingStrategy(value: Object | string | number | undefined | boolean): boolean {
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
    static isSystemAdaptiveOptions(value: Object | string | number | undefined | boolean, duplicated_disableSystemAdaptation: boolean): boolean {
        if ((!duplicated_disableSystemAdaptation) && (value?.hasOwnProperty("disableSystemAdaptation"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof SystemAdaptiveOptions")
        }
    }
    static isTabBarIconStyle(value: Object | string | number | undefined | boolean, duplicated_selectedColor: boolean, duplicated_unselectedColor: boolean): boolean {
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
    static isTabBarLabelStyle(value: Object | string | number | undefined | boolean, duplicated_overflow: boolean, duplicated_maxLines: boolean, duplicated_minFontSize: boolean, duplicated_maxFontSize: boolean, duplicated_heightAdaptivePolicy: boolean, duplicated_font: boolean, duplicated_selectedColor: boolean, duplicated_unselectedColor: boolean): boolean {
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
        else if ((!duplicated_selectedColor) && (value?.hasOwnProperty("selectedColor"))) {
            return true
        }
        else if ((!duplicated_unselectedColor) && (value?.hasOwnProperty("unselectedColor"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TabBarLabelStyle")
        }
    }
    static isTabBarOptions(value: Object | string | number | undefined | boolean, duplicated_icon: boolean, duplicated_text: boolean): boolean {
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
    static isTabBarSymbol(value: Object | string | number | undefined | boolean, duplicated_normal: boolean, duplicated_selected: boolean): boolean {
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
    static isTabContentAnimatedTransition(value: Object | string | number | undefined | boolean, duplicated_timeout: boolean, duplicated_transition: boolean): boolean {
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
    static isTabContentTransitionProxy(value: Object | string | number | undefined | boolean, duplicated_from: boolean, duplicated_to: boolean): boolean {
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
    static isTabsAnimationEvent(value: Object | string | number | undefined | boolean, duplicated_currentOffset: boolean, duplicated_targetOffset: boolean, duplicated_velocity: boolean): boolean {
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
    static isTabsCacheMode(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (TabsCacheMode.CACHE_BOTH_SIDE)) {
            return true
        }
        else if ((value) === (TabsCacheMode.CACHE_LATEST_SWITCHED)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TabsCacheMode")
        }
    }
    static isTabsController(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof TabsController")
    }
    static isTabsOptions(value: Object | string | number | undefined | boolean, duplicated_barPosition: boolean, duplicated_index: boolean, duplicated_controller: boolean, duplicated_barModifier: boolean): boolean {
        if ((!duplicated_barPosition) && (value?.hasOwnProperty("barPosition"))) {
            return true
        }
        else if ((!duplicated_index) && (value?.hasOwnProperty("index"))) {
            return true
        }
        else if ((!duplicated_controller) && (value?.hasOwnProperty("controller"))) {
            return true
        }
        else if ((!duplicated_barModifier) && (value?.hasOwnProperty("barModifier"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TabsOptions")
        }
    }
    static isTapGestureEvent(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof TapGestureEvent")
    }
    static isTapGestureInterface(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof TapGestureInterface")
    }
    static isTapGestureParameters(value: Object | string | number | undefined | boolean, duplicated_count: boolean, duplicated_fingers: boolean, duplicated_distanceThreshold: boolean): boolean {
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
    static isTapRecognizer(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof TapRecognizer")
    }
    static isTargetInfo(value: Object | string | number | undefined | boolean, duplicated_id: boolean, duplicated_componentId: boolean): boolean {
        if ((!duplicated_id) && (value?.hasOwnProperty("id"))) {
            return true
        }
        else if ((!duplicated_componentId) && (value?.hasOwnProperty("componentId"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TargetInfo")
        }
    }
    static isTerminationInfo(value: Object | string | number | undefined | boolean, duplicated_code: boolean, duplicated_want: boolean): boolean {
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
    static istext_Affinity(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (text.Affinity.UPSTREAM)) {
            return true
        }
        else if ((value) === (text.Affinity.DOWNSTREAM)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof text.Affinity")
        }
    }
    static istext_BreakStrategy(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (text.BreakStrategy.GREEDY)) {
            return true
        }
        else if ((value) === (text.BreakStrategy.HIGH_QUALITY)) {
            return true
        }
        else if ((value) === (text.BreakStrategy.BALANCED)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof text.BreakStrategy")
        }
    }
    static istext_Decoration(value: Object | string | number | undefined | boolean, duplicated_textDecoration: boolean, duplicated_color: boolean, duplicated_decorationStyle: boolean, duplicated_decorationThicknessScale: boolean): boolean {
        if ((!duplicated_textDecoration) && (value?.hasOwnProperty("textDecoration"))) {
            return true
        }
        else if ((!duplicated_color) && (value?.hasOwnProperty("color"))) {
            return true
        }
        else if ((!duplicated_decorationStyle) && (value?.hasOwnProperty("decorationStyle"))) {
            return true
        }
        else if ((!duplicated_decorationThicknessScale) && (value?.hasOwnProperty("decorationThicknessScale"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof text.Decoration")
        }
    }
    static istext_EllipsisMode(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (text.EllipsisMode.START)) {
            return true
        }
        else if ((value) === (text.EllipsisMode.MIDDLE)) {
            return true
        }
        else if ((value) === (text.EllipsisMode.END)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof text.EllipsisMode")
        }
    }
    static istext_FontCollection(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof text.FontCollection")
    }
    static istext_FontDescriptor(value: Object | string | number | undefined | boolean, duplicated_path: boolean, duplicated_postScriptName: boolean, duplicated_fullName: boolean, duplicated_fontFamily: boolean, duplicated_fontSubfamily: boolean, duplicated_weight: boolean, duplicated_width: boolean, duplicated_italic: boolean, duplicated_monoSpace: boolean, duplicated_symbolic: boolean): boolean {
        if ((!duplicated_path) && (value?.hasOwnProperty("path"))) {
            return true
        }
        else if ((!duplicated_postScriptName) && (value?.hasOwnProperty("postScriptName"))) {
            return true
        }
        else if ((!duplicated_fullName) && (value?.hasOwnProperty("fullName"))) {
            return true
        }
        else if ((!duplicated_fontFamily) && (value?.hasOwnProperty("fontFamily"))) {
            return true
        }
        else if ((!duplicated_fontSubfamily) && (value?.hasOwnProperty("fontSubfamily"))) {
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
            throw new Error("Can not discriminate value typeof text.FontDescriptor")
        }
    }
    static istext_FontFeature(value: Object | string | number | undefined | boolean, duplicated_name: boolean, duplicated_value: boolean): boolean {
        if ((!duplicated_name) && (value?.hasOwnProperty("name"))) {
            return true
        }
        else if ((!duplicated_value) && (value?.hasOwnProperty("value"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof text.FontFeature")
        }
    }
    static istext_FontStyle(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (text.FontStyle.NORMAL)) {
            return true
        }
        else if ((value) === (text.FontStyle.ITALIC)) {
            return true
        }
        else if ((value) === (text.FontStyle.OBLIQUE)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof text.FontStyle")
        }
    }
    static istext_FontVariation(value: Object | string | number | undefined | boolean, duplicated_axis: boolean, duplicated_value: boolean): boolean {
        if ((!duplicated_axis) && (value?.hasOwnProperty("axis"))) {
            return true
        }
        else if ((!duplicated_value) && (value?.hasOwnProperty("value"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof text.FontVariation")
        }
    }
    static istext_FontWeight(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (text.FontWeight.W100)) {
            return true
        }
        else if ((value) === (text.FontWeight.W200)) {
            return true
        }
        else if ((value) === (text.FontWeight.W300)) {
            return true
        }
        else if ((value) === (text.FontWeight.W400)) {
            return true
        }
        else if ((value) === (text.FontWeight.W500)) {
            return true
        }
        else if ((value) === (text.FontWeight.W600)) {
            return true
        }
        else if ((value) === (text.FontWeight.W700)) {
            return true
        }
        else if ((value) === (text.FontWeight.W800)) {
            return true
        }
        else if ((value) === (text.FontWeight.W900)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof text.FontWeight")
        }
    }
    static istext_FontWidth(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (text.FontWidth.ULTRA_CONDENSED)) {
            return true
        }
        else if ((value) === (text.FontWidth.EXTRA_CONDENSED)) {
            return true
        }
        else if ((value) === (text.FontWidth.CONDENSED)) {
            return true
        }
        else if ((value) === (text.FontWidth.SEMI_CONDENSED)) {
            return true
        }
        else if ((value) === (text.FontWidth.NORMAL)) {
            return true
        }
        else if ((value) === (text.FontWidth.SEMI_EXPANDED)) {
            return true
        }
        else if ((value) === (text.FontWidth.EXPANDED)) {
            return true
        }
        else if ((value) === (text.FontWidth.EXTRA_EXPANDED)) {
            return true
        }
        else if ((value) === (text.FontWidth.ULTRA_EXPANDED)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof text.FontWidth")
        }
    }
    static istext_LineMetrics(value: Object | string | number | undefined | boolean, duplicated_startIndex: boolean, duplicated_endIndex: boolean, duplicated_ascent: boolean, duplicated_descent: boolean, duplicated_height: boolean, duplicated_width: boolean, duplicated_left: boolean, duplicated_baseline: boolean, duplicated_lineNumber: boolean, duplicated_topHeight: boolean, duplicated_runMetrics: boolean): boolean {
        if ((!duplicated_startIndex) && (value?.hasOwnProperty("startIndex"))) {
            return true
        }
        else if ((!duplicated_endIndex) && (value?.hasOwnProperty("endIndex"))) {
            return true
        }
        else if ((!duplicated_ascent) && (value?.hasOwnProperty("ascent"))) {
            return true
        }
        else if ((!duplicated_descent) && (value?.hasOwnProperty("descent"))) {
            return true
        }
        else if ((!duplicated_height) && (value?.hasOwnProperty("height"))) {
            return true
        }
        else if ((!duplicated_width) && (value?.hasOwnProperty("width"))) {
            return true
        }
        else if ((!duplicated_left) && (value?.hasOwnProperty("left"))) {
            return true
        }
        else if ((!duplicated_baseline) && (value?.hasOwnProperty("baseline"))) {
            return true
        }
        else if ((!duplicated_lineNumber) && (value?.hasOwnProperty("lineNumber"))) {
            return true
        }
        else if ((!duplicated_topHeight) && (value?.hasOwnProperty("topHeight"))) {
            return true
        }
        else if ((!duplicated_runMetrics) && (value?.hasOwnProperty("runMetrics"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof text.LineMetrics")
        }
    }
    static istext_LineTypeset(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof text.LineTypeset")
    }
    static istext_Paragraph(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof text.Paragraph")
    }
    static istext_ParagraphBuilder(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof text.ParagraphBuilder")
    }
    static istext_ParagraphStyle(value: Object | string | number | undefined | boolean, duplicated_textStyle: boolean, duplicated_textDirection: boolean, duplicated_align: boolean, duplicated_wordBreak: boolean, duplicated_maxLines: boolean, duplicated_breakStrategy: boolean, duplicated_strutStyle: boolean, duplicated_textHeightBehavior: boolean, duplicated_tab: boolean): boolean {
        if ((!duplicated_textStyle) && (value?.hasOwnProperty("textStyle"))) {
            return true
        }
        else if ((!duplicated_textDirection) && (value?.hasOwnProperty("textDirection"))) {
            return true
        }
        else if ((!duplicated_align) && (value?.hasOwnProperty("align"))) {
            return true
        }
        else if ((!duplicated_wordBreak) && (value?.hasOwnProperty("wordBreak"))) {
            return true
        }
        else if ((!duplicated_maxLines) && (value?.hasOwnProperty("maxLines"))) {
            return true
        }
        else if ((!duplicated_breakStrategy) && (value?.hasOwnProperty("breakStrategy"))) {
            return true
        }
        else if ((!duplicated_strutStyle) && (value?.hasOwnProperty("strutStyle"))) {
            return true
        }
        else if ((!duplicated_textHeightBehavior) && (value?.hasOwnProperty("textHeightBehavior"))) {
            return true
        }
        else if ((!duplicated_tab) && (value?.hasOwnProperty("tab"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof text.ParagraphStyle")
        }
    }
    static istext_PlaceholderAlignment(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (text.PlaceholderAlignment.OFFSET_AT_BASELINE)) {
            return true
        }
        else if ((value) === (text.PlaceholderAlignment.ABOVE_BASELINE)) {
            return true
        }
        else if ((value) === (text.PlaceholderAlignment.BELOW_BASELINE)) {
            return true
        }
        else if ((value) === (text.PlaceholderAlignment.TOP_OF_ROW_BOX)) {
            return true
        }
        else if ((value) === (text.PlaceholderAlignment.BOTTOM_OF_ROW_BOX)) {
            return true
        }
        else if ((value) === (text.PlaceholderAlignment.CENTER_OF_ROW_BOX)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof text.PlaceholderAlignment")
        }
    }
    static istext_PlaceholderSpan(value: Object | string | number | undefined | boolean, duplicated_width: boolean, duplicated_height: boolean, duplicated_align: boolean, duplicated_baseline: boolean, duplicated_baselineOffset: boolean): boolean {
        if ((!duplicated_width) && (value?.hasOwnProperty("width"))) {
            return true
        }
        else if ((!duplicated_height) && (value?.hasOwnProperty("height"))) {
            return true
        }
        else if ((!duplicated_align) && (value?.hasOwnProperty("align"))) {
            return true
        }
        else if ((!duplicated_baseline) && (value?.hasOwnProperty("baseline"))) {
            return true
        }
        else if ((!duplicated_baselineOffset) && (value?.hasOwnProperty("baselineOffset"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof text.PlaceholderSpan")
        }
    }
    static istext_PositionWithAffinity(value: Object | string | number | undefined | boolean, duplicated_position: boolean, duplicated_affinity: boolean): boolean {
        if ((!duplicated_position) && (value?.hasOwnProperty("position"))) {
            return true
        }
        else if ((!duplicated_affinity) && (value?.hasOwnProperty("affinity"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof text.PositionWithAffinity")
        }
    }
    static istext_Range(value: Object | string | number | undefined | boolean, duplicated_start: boolean, duplicated_end: boolean): boolean {
        if ((!duplicated_start) && (value?.hasOwnProperty("start"))) {
            return true
        }
        else if ((!duplicated_end) && (value?.hasOwnProperty("end"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof text.Range")
        }
    }
    static istext_RectHeightStyle(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (text.RectHeightStyle.TIGHT)) {
            return true
        }
        else if ((value) === (text.RectHeightStyle.MAX)) {
            return true
        }
        else if ((value) === (text.RectHeightStyle.INCLUDE_LINE_SPACE_MIDDLE)) {
            return true
        }
        else if ((value) === (text.RectHeightStyle.INCLUDE_LINE_SPACE_TOP)) {
            return true
        }
        else if ((value) === (text.RectHeightStyle.INCLUDE_LINE_SPACE_BOTTOM)) {
            return true
        }
        else if ((value) === (text.RectHeightStyle.STRUT)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof text.RectHeightStyle")
        }
    }
    static istext_RectStyle(value: Object | string | number | undefined | boolean, duplicated_color: boolean, duplicated_leftTopRadius: boolean, duplicated_rightTopRadius: boolean, duplicated_rightBottomRadius: boolean, duplicated_leftBottomRadius: boolean): boolean {
        if ((!duplicated_color) && (value?.hasOwnProperty("color"))) {
            return true
        }
        else if ((!duplicated_leftTopRadius) && (value?.hasOwnProperty("leftTopRadius"))) {
            return true
        }
        else if ((!duplicated_rightTopRadius) && (value?.hasOwnProperty("rightTopRadius"))) {
            return true
        }
        else if ((!duplicated_rightBottomRadius) && (value?.hasOwnProperty("rightBottomRadius"))) {
            return true
        }
        else if ((!duplicated_leftBottomRadius) && (value?.hasOwnProperty("leftBottomRadius"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof text.RectStyle")
        }
    }
    static istext_RectWidthStyle(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (text.RectWidthStyle.TIGHT)) {
            return true
        }
        else if ((value) === (text.RectWidthStyle.MAX)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof text.RectWidthStyle")
        }
    }
    static istext_Run(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof text.Run")
    }
    static istext_RunMetrics(value: Object | string | number | undefined | boolean, duplicated_textStyle: boolean, duplicated_fontMetrics: boolean): boolean {
        if ((!duplicated_textStyle) && (value?.hasOwnProperty("textStyle"))) {
            return true
        }
        else if ((!duplicated_fontMetrics) && (value?.hasOwnProperty("fontMetrics"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof text.RunMetrics")
        }
    }
    static istext_StrutStyle(value: Object | string | number | undefined | boolean, duplicated_fontFamilies: boolean, duplicated_fontStyle: boolean, duplicated_fontWidth: boolean, duplicated_fontWeight: boolean, duplicated_fontSize: boolean, duplicated_height: boolean, duplicated_leading: boolean, duplicated_forceHeight: boolean, duplicated_enabled: boolean, duplicated_heightOverride: boolean, duplicated_halfLeading: boolean): boolean {
        if ((!duplicated_fontFamilies) && (value?.hasOwnProperty("fontFamilies"))) {
            return true
        }
        else if ((!duplicated_fontStyle) && (value?.hasOwnProperty("fontStyle"))) {
            return true
        }
        else if ((!duplicated_fontWidth) && (value?.hasOwnProperty("fontWidth"))) {
            return true
        }
        else if ((!duplicated_fontWeight) && (value?.hasOwnProperty("fontWeight"))) {
            return true
        }
        else if ((!duplicated_fontSize) && (value?.hasOwnProperty("fontSize"))) {
            return true
        }
        else if ((!duplicated_height) && (value?.hasOwnProperty("height"))) {
            return true
        }
        else if ((!duplicated_leading) && (value?.hasOwnProperty("leading"))) {
            return true
        }
        else if ((!duplicated_forceHeight) && (value?.hasOwnProperty("forceHeight"))) {
            return true
        }
        else if ((!duplicated_enabled) && (value?.hasOwnProperty("enabled"))) {
            return true
        }
        else if ((!duplicated_heightOverride) && (value?.hasOwnProperty("heightOverride"))) {
            return true
        }
        else if ((!duplicated_halfLeading) && (value?.hasOwnProperty("halfLeading"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof text.StrutStyle")
        }
    }
    static istext_SystemFontType(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (text.SystemFontType.ALL)) {
            return true
        }
        else if ((value) === (text.SystemFontType.GENERIC)) {
            return true
        }
        else if ((value) === (text.SystemFontType.STYLISH)) {
            return true
        }
        else if ((value) === (text.SystemFontType.INSTALLED)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof text.SystemFontType")
        }
    }
    static istext_TextAlign(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (text.TextAlign.LEFT)) {
            return true
        }
        else if ((value) === (text.TextAlign.RIGHT)) {
            return true
        }
        else if ((value) === (text.TextAlign.CENTER)) {
            return true
        }
        else if ((value) === (text.TextAlign.JUSTIFY)) {
            return true
        }
        else if ((value) === (text.TextAlign.START)) {
            return true
        }
        else if ((value) === (text.TextAlign.END)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof text.TextAlign")
        }
    }
    static istext_TextBaseline(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (text.TextBaseline.ALPHABETIC)) {
            return true
        }
        else if ((value) === (text.TextBaseline.IDEOGRAPHIC)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof text.TextBaseline")
        }
    }
    static istext_TextBox(value: Object | string | number | undefined | boolean, duplicated_rect: boolean, duplicated_direction: boolean): boolean {
        if ((!duplicated_rect) && (value?.hasOwnProperty("rect"))) {
            return true
        }
        else if ((!duplicated_direction) && (value?.hasOwnProperty("direction"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof text.TextBox")
        }
    }
    static istext_TextDecorationStyle(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (text.TextDecorationStyle.SOLID)) {
            return true
        }
        else if ((value) === (text.TextDecorationStyle.DOUBLE)) {
            return true
        }
        else if ((value) === (text.TextDecorationStyle.DOTTED)) {
            return true
        }
        else if ((value) === (text.TextDecorationStyle.DASHED)) {
            return true
        }
        else if ((value) === (text.TextDecorationStyle.WAVY)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof text.TextDecorationStyle")
        }
    }
    static istext_TextDecorationType(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (text.TextDecorationType.NONE)) {
            return true
        }
        else if ((value) === (text.TextDecorationType.UNDERLINE)) {
            return true
        }
        else if ((value) === (text.TextDecorationType.OVERLINE)) {
            return true
        }
        else if ((value) === (text.TextDecorationType.LINE_THROUGH)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof text.TextDecorationType")
        }
    }
    static istext_TextDirection(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (text.TextDirection.RTL)) {
            return true
        }
        else if ((value) === (text.TextDirection.LTR)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof text.TextDirection")
        }
    }
    static istext_TextHeightBehavior(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (text.TextHeightBehavior.ALL)) {
            return true
        }
        else if ((value) === (text.TextHeightBehavior.DISABLE_FIRST_ASCENT)) {
            return true
        }
        else if ((value) === (text.TextHeightBehavior.DISABLE_LAST_ASCENT)) {
            return true
        }
        else if ((value) === (text.TextHeightBehavior.DISABLE_ALL)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof text.TextHeightBehavior")
        }
    }
    static istext_TextLine(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof text.TextLine")
    }
    static istext_TextShadow(value: Object | string | number | undefined | boolean, duplicated_color: boolean, duplicated_point: boolean, duplicated_blurRadius: boolean): boolean {
        if ((!duplicated_color) && (value?.hasOwnProperty("color"))) {
            return true
        }
        else if ((!duplicated_point) && (value?.hasOwnProperty("point"))) {
            return true
        }
        else if ((!duplicated_blurRadius) && (value?.hasOwnProperty("blurRadius"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof text.TextShadow")
        }
    }
    static istext_TextStyle(value: Object | string | number | undefined | boolean, duplicated_decoration: boolean, duplicated_color: boolean, duplicated_fontWeight: boolean, duplicated_fontStyle: boolean, duplicated_baseline: boolean, duplicated_fontFamilies: boolean, duplicated_fontSize: boolean, duplicated_letterSpacing: boolean, duplicated_wordSpacing: boolean, duplicated_heightScale: boolean, duplicated_halfLeading: boolean, duplicated_heightOnly: boolean, duplicated_ellipsis: boolean, duplicated_ellipsisMode: boolean, duplicated_locale: boolean, duplicated_baselineShift: boolean, duplicated_fontFeatures: boolean, duplicated_textShadows: boolean, duplicated_backgroundRect: boolean, duplicated_fontVariations: boolean): boolean {
        if ((!duplicated_decoration) && (value?.hasOwnProperty("decoration"))) {
            return true
        }
        else if ((!duplicated_color) && (value?.hasOwnProperty("color"))) {
            return true
        }
        else if ((!duplicated_fontWeight) && (value?.hasOwnProperty("fontWeight"))) {
            return true
        }
        else if ((!duplicated_fontStyle) && (value?.hasOwnProperty("fontStyle"))) {
            return true
        }
        else if ((!duplicated_baseline) && (value?.hasOwnProperty("baseline"))) {
            return true
        }
        else if ((!duplicated_fontFamilies) && (value?.hasOwnProperty("fontFamilies"))) {
            return true
        }
        else if ((!duplicated_fontSize) && (value?.hasOwnProperty("fontSize"))) {
            return true
        }
        else if ((!duplicated_letterSpacing) && (value?.hasOwnProperty("letterSpacing"))) {
            return true
        }
        else if ((!duplicated_wordSpacing) && (value?.hasOwnProperty("wordSpacing"))) {
            return true
        }
        else if ((!duplicated_heightScale) && (value?.hasOwnProperty("heightScale"))) {
            return true
        }
        else if ((!duplicated_halfLeading) && (value?.hasOwnProperty("halfLeading"))) {
            return true
        }
        else if ((!duplicated_heightOnly) && (value?.hasOwnProperty("heightOnly"))) {
            return true
        }
        else if ((!duplicated_ellipsis) && (value?.hasOwnProperty("ellipsis"))) {
            return true
        }
        else if ((!duplicated_ellipsisMode) && (value?.hasOwnProperty("ellipsisMode"))) {
            return true
        }
        else if ((!duplicated_locale) && (value?.hasOwnProperty("locale"))) {
            return true
        }
        else if ((!duplicated_baselineShift) && (value?.hasOwnProperty("baselineShift"))) {
            return true
        }
        else if ((!duplicated_fontFeatures) && (value?.hasOwnProperty("fontFeatures"))) {
            return true
        }
        else if ((!duplicated_textShadows) && (value?.hasOwnProperty("textShadows"))) {
            return true
        }
        else if ((!duplicated_backgroundRect) && (value?.hasOwnProperty("backgroundRect"))) {
            return true
        }
        else if ((!duplicated_fontVariations) && (value?.hasOwnProperty("fontVariations"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof text.TextStyle")
        }
    }
    static istext_TextTab(value: Object | string | number | undefined | boolean, duplicated_alignment: boolean, duplicated_location: boolean): boolean {
        if ((!duplicated_alignment) && (value?.hasOwnProperty("alignment"))) {
            return true
        }
        else if ((!duplicated_location) && (value?.hasOwnProperty("location"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof text.TextTab")
        }
    }
    static istext_TypographicBounds(value: Object | string | number | undefined | boolean, duplicated_ascent: boolean, duplicated_descent: boolean, duplicated_leading: boolean, duplicated_width: boolean): boolean {
        if ((!duplicated_ascent) && (value?.hasOwnProperty("ascent"))) {
            return true
        }
        else if ((!duplicated_descent) && (value?.hasOwnProperty("descent"))) {
            return true
        }
        else if ((!duplicated_leading) && (value?.hasOwnProperty("leading"))) {
            return true
        }
        else if ((!duplicated_width) && (value?.hasOwnProperty("width"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof text.TypographicBounds")
        }
    }
    static istext_WordBreak(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (text.WordBreak.NORMAL)) {
            return true
        }
        else if ((value) === (text.WordBreak.BREAK_ALL)) {
            return true
        }
        else if ((value) === (text.WordBreak.BREAK_WORD)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof text.WordBreak")
        }
    }
    static isTextAlign(value: Object | string | number | undefined | boolean): boolean {
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
    static isTextAreaController(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof TextAreaController")
    }
    static isTextAreaOptions(value: Object | string | number | undefined | boolean, duplicated_placeholder: boolean, duplicated_text: boolean, duplicated_controller: boolean): boolean {
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
    static isTextAreaType(value: Object | string | number | undefined | boolean): boolean {
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
    static isTextBackgroundStyle(value: Object | string | number | undefined | boolean, duplicated_color: boolean, duplicated_radius: boolean): boolean {
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
    static isTextBaseController(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof TextBaseController")
    }
    static isTextCascadePickerRangeContent(value: Object | string | number | undefined | boolean, duplicated_text: boolean, duplicated_children: boolean): boolean {
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
    static isTextCase(value: Object | string | number | undefined | boolean): boolean {
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
    static isTextChangeOptions(value: Object | string | number | undefined | boolean, duplicated_rangeBefore: boolean, duplicated_rangeAfter: boolean, duplicated_oldContent: boolean, duplicated_oldPreviewText: boolean): boolean {
        if ((!duplicated_rangeBefore) && (value?.hasOwnProperty("rangeBefore"))) {
            return true
        }
        else if ((!duplicated_rangeAfter) && (value?.hasOwnProperty("rangeAfter"))) {
            return true
        }
        else if ((!duplicated_oldContent) && (value?.hasOwnProperty("oldContent"))) {
            return true
        }
        else if ((!duplicated_oldPreviewText) && (value?.hasOwnProperty("oldPreviewText"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TextChangeOptions")
        }
    }
    static isTextClockConfiguration(value: Object | string | number | undefined | boolean, duplicated_timeZoneOffset: boolean, duplicated_started: boolean, duplicated_timeValue: boolean): boolean {
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
    static isTextClockController(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof TextClockController")
    }
    static isTextClockOptions(value: Object | string | number | undefined | boolean, duplicated_timeZoneOffset: boolean, duplicated_controller: boolean): boolean {
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
    static isTextContentControllerBase(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof TextContentControllerBase")
    }
    static isTextContentControllerOptions(value: Object | string | number | undefined | boolean, duplicated_offset: boolean): boolean {
        if ((!duplicated_offset) && (value?.hasOwnProperty("offset"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TextContentControllerOptions")
        }
    }
    static isTextContentStyle(value: Object | string | number | undefined | boolean): boolean {
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
    static isTextController(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof TextController")
    }
    static isTextDataDetectorConfig(value: Object | string | number | undefined | boolean, duplicated_types: boolean, duplicated_onDetectResultUpdate: boolean, duplicated_color: boolean, duplicated_decoration: boolean): boolean {
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
    static isTextDataDetectorType(value: Object | string | number | undefined | boolean): boolean {
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
    static isTextDecorationOptions(value: Object | string | number | undefined | boolean, duplicated_type: boolean, duplicated_color: boolean, duplicated_style: boolean): boolean {
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
    static isTextDecorationStyle(value: Object | string | number | undefined | boolean): boolean {
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
    static isTextDecorationType(value: Object | string | number | undefined | boolean): boolean {
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
    static isTextDeleteDirection(value: Object | string | number | undefined | boolean): boolean {
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
    static isTextEditControllerEx(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof TextEditControllerEx")
    }
    static isTextHeightAdaptivePolicy(value: Object | string | number | undefined | boolean): boolean {
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
    static isTextInputController(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof TextInputController")
    }
    static isTextInputOptions(value: Object | string | number | undefined | boolean, duplicated_placeholder: boolean, duplicated_text: boolean, duplicated_controller: boolean): boolean {
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
    static isTextInputStyle(value: Object | string | number | undefined | boolean): boolean {
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
    static isTextMarqueeOptions(value: Object | string | number | undefined | boolean, duplicated_start: boolean, duplicated_step: boolean, duplicated_loop: boolean, duplicated_fromStart: boolean, duplicated_delay: boolean, duplicated_fadeout: boolean, duplicated_marqueeStartPolicy: boolean): boolean {
        if ((!duplicated_start) && (value?.hasOwnProperty("start"))) {
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
        else if ((!duplicated_delay) && (value?.hasOwnProperty("delay"))) {
            return true
        }
        else if ((!duplicated_fadeout) && (value?.hasOwnProperty("fadeout"))) {
            return true
        }
        else if ((!duplicated_marqueeStartPolicy) && (value?.hasOwnProperty("marqueeStartPolicy"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TextMarqueeOptions")
        }
    }
    static isTextMenuController(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof TextMenuController")
    }
    static isTextMenuItem(value: Object | string | number | undefined | boolean, duplicated_content: boolean, duplicated_icon: boolean, duplicated_id: boolean, duplicated_labelInfo: boolean): boolean {
        if ((!duplicated_content) && (value?.hasOwnProperty("content"))) {
            return true
        }
        else if ((!duplicated_id) && (value?.hasOwnProperty("id"))) {
            return true
        }
        else if ((!duplicated_icon) && (value?.hasOwnProperty("icon"))) {
            return true
        }
        else if ((!duplicated_labelInfo) && (value?.hasOwnProperty("labelInfo"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TextMenuItem")
        }
    }
    static isTextMenuItemId(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof TextMenuItemId")
    }
    static isTextMenuOptions(value: Object | string | number | undefined | boolean, duplicated_showMode: boolean): boolean {
        if ((!duplicated_showMode) && (value?.hasOwnProperty("showMode"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TextMenuOptions")
        }
    }
    static isTextMenuShowMode(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (TextMenuShowMode.DEFAULT)) {
            return true
        }
        else if ((value) === (TextMenuShowMode.PREFER_WINDOW)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TextMenuShowMode")
        }
    }
    static isTextMetrics(value: Object | string | number | undefined | boolean, duplicated_actualBoundingBoxAscent: boolean, duplicated_actualBoundingBoxDescent: boolean, duplicated_actualBoundingBoxLeft: boolean, duplicated_actualBoundingBoxRight: boolean, duplicated_alphabeticBaseline: boolean, duplicated_emHeightAscent: boolean, duplicated_emHeightDescent: boolean, duplicated_fontBoundingBoxAscent: boolean, duplicated_fontBoundingBoxDescent: boolean, duplicated_hangingBaseline: boolean, duplicated_ideographicBaseline: boolean, duplicated_width: boolean, duplicated_height: boolean): boolean {
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
    static isTextModifier(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof TextModifier")
    }
    static isTextOptions(value: Object | string | number | undefined | boolean, duplicated_controller: boolean): boolean {
        if ((!duplicated_controller) && (value?.hasOwnProperty("controller"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TextOptions")
        }
    }
    static isTextOverflow(value: Object | string | number | undefined | boolean): boolean {
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
    static isTextOverflowOptions(value: Object | string | number | undefined | boolean, duplicated_overflow: boolean): boolean {
        if ((!duplicated_overflow) && (value?.hasOwnProperty("overflow"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TextOverflowOptions")
        }
    }
    static isTextPickerDialog(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof TextPickerDialog")
    }
    static isTextPickerDialogOptions(value: Object | string | number | undefined | boolean, duplicated_defaultPickerItemHeight: boolean, duplicated_canLoop: boolean, duplicated_disappearTextStyle: boolean, duplicated_textStyle: boolean, duplicated_acceptButtonStyle: boolean, duplicated_cancelButtonStyle: boolean, duplicated_selectedTextStyle: boolean, duplicated_disableTextStyleAnimation: boolean, duplicated_defaultTextStyle: boolean, duplicated_onAccept: boolean, duplicated_onCancel: boolean, duplicated_onChange: boolean, duplicated_onScrollStop: boolean, duplicated_onEnterSelectedArea: boolean, duplicated_maskRect: boolean, duplicated_alignment: boolean, duplicated_offset: boolean, duplicated_backgroundColor: boolean, duplicated_backgroundBlurStyle: boolean, duplicated_backgroundBlurStyleOptions: boolean, duplicated_backgroundEffect: boolean, duplicated_onDidAppear: boolean, duplicated_onDidDisappear: boolean, duplicated_onWillAppear: boolean, duplicated_onWillDisappear: boolean, duplicated_shadow: boolean, duplicated_enableHoverMode: boolean, duplicated_hoverModeArea: boolean, duplicated_enableHapticFeedback: boolean): boolean {
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
        else if ((!duplicated_disableTextStyleAnimation) && (value?.hasOwnProperty("disableTextStyleAnimation"))) {
            return true
        }
        else if ((!duplicated_defaultTextStyle) && (value?.hasOwnProperty("defaultTextStyle"))) {
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
        else if ((!duplicated_onScrollStop) && (value?.hasOwnProperty("onScrollStop"))) {
            return true
        }
        else if ((!duplicated_onEnterSelectedArea) && (value?.hasOwnProperty("onEnterSelectedArea"))) {
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
        else if ((!duplicated_backgroundBlurStyleOptions) && (value?.hasOwnProperty("backgroundBlurStyleOptions"))) {
            return true
        }
        else if ((!duplicated_backgroundEffect) && (value?.hasOwnProperty("backgroundEffect"))) {
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
        else if ((!duplicated_enableHapticFeedback) && (value?.hasOwnProperty("enableHapticFeedback"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TextPickerDialogOptions")
        }
    }
    static isTextPickerOptions(value: Object | string | number | undefined | boolean, duplicated_range: boolean, duplicated_value: boolean, duplicated_selected: boolean, duplicated_columnWidths: boolean): boolean {
        if ((!duplicated_range) && (value?.hasOwnProperty("range"))) {
            return true
        }
        else if ((!duplicated_value) && (value?.hasOwnProperty("value"))) {
            return true
        }
        else if ((!duplicated_selected) && (value?.hasOwnProperty("selected"))) {
            return true
        }
        else if ((!duplicated_columnWidths) && (value?.hasOwnProperty("columnWidths"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TextPickerOptions")
        }
    }
    static isTextPickerRangeContent(value: Object | string | number | undefined | boolean, duplicated_icon: boolean, duplicated_text: boolean): boolean {
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
    static isTextPickerResult(value: Object | string | number | undefined | boolean, duplicated_value: boolean, duplicated_index: boolean): boolean {
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
    static isTextPickerTextStyle(value: Object | string | number | undefined | boolean, duplicated_minFontSize: boolean, duplicated_maxFontSize: boolean, duplicated_overflow: boolean): boolean {
        if ((!duplicated_minFontSize) && (value?.hasOwnProperty("minFontSize"))) {
            return true
        }
        else if ((!duplicated_maxFontSize) && (value?.hasOwnProperty("maxFontSize"))) {
            return true
        }
        else if ((!duplicated_overflow) && (value?.hasOwnProperty("overflow"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TextPickerTextStyle")
        }
    }
    static isTextRange(value: Object | string | number | undefined | boolean, duplicated_start: boolean, duplicated_end: boolean): boolean {
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
    static isTextResponseType(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (TextResponseType.RIGHT_CLICK)) {
            return true
        }
        else if ((value) === (TextResponseType.LONG_PRESS)) {
            return true
        }
        else if ((value) === (TextResponseType.SELECT)) {
            return true
        }
        else if ((value) === (TextResponseType.DEFAULT)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TextResponseType")
        }
    }
    static isTextSelectableMode(value: Object | string | number | undefined | boolean): boolean {
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
    static isTextShadowStyle(value: Object | string | number | undefined | boolean, duplicated_textShadow: boolean): boolean {
        if ((!duplicated_textShadow) && (value?.hasOwnProperty("textShadow"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TextShadowStyle")
        }
    }
    static isTextSpanType(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (TextSpanType.TEXT)) {
            return true
        }
        else if ((value) === (TextSpanType.IMAGE)) {
            return true
        }
        else if ((value) === (TextSpanType.MIXED)) {
            return true
        }
        else if ((value) === (TextSpanType.DEFAULT)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TextSpanType")
        }
    }
    static isTextStyle(value: Object | string | number | undefined | boolean, duplicated_fontColor: boolean, duplicated_fontFamily: boolean, duplicated_fontSize: boolean, duplicated_fontWeight: boolean, duplicated_fontStyle: boolean): boolean {
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
            throw new Error("Can not discriminate value typeof TextStyle")
        }
    }
    static isTextStyleInterface(value: Object | string | number | undefined | boolean, duplicated_fontColor: boolean, duplicated_fontFamily: boolean, duplicated_fontSize: boolean, duplicated_fontWeight: boolean, duplicated_fontStyle: boolean): boolean {
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
    static isTextTimerConfiguration(value: Object | string | number | undefined | boolean, duplicated_count: boolean, duplicated_isCountDown: boolean, duplicated_started: boolean, duplicated_elapsedTime: boolean): boolean {
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
    static isTextTimerController(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof TextTimerController")
    }
    static isTextTimerOptions(value: Object | string | number | undefined | boolean, duplicated_isCountDown: boolean, duplicated_count: boolean, duplicated_controller: boolean): boolean {
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
    static isThemeColorMode(value: Object | string | number | undefined | boolean): boolean {
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
    static isThemeControl(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof ThemeControl")
    }
    static isThreatType(value: Object | string | number | undefined | boolean): boolean {
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
    static isTimePickerDialog(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof TimePickerDialog")
    }
    static isTimePickerFormat(value: Object | string | number | undefined | boolean): boolean {
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
    static isTimePickerOptions(value: Object | string | number | undefined | boolean, duplicated_selected: boolean, duplicated_format: boolean, duplicated_start: boolean, duplicated_end: boolean): boolean {
        if ((!duplicated_selected) && (value?.hasOwnProperty("selected"))) {
            return true
        }
        else if ((!duplicated_format) && (value?.hasOwnProperty("format"))) {
            return true
        }
        else if ((!duplicated_start) && (value?.hasOwnProperty("start"))) {
            return true
        }
        else if ((!duplicated_end) && (value?.hasOwnProperty("end"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TimePickerOptions")
        }
    }
    static isTimePickerResult(value: Object | string | number | undefined | boolean, duplicated_hour: boolean, duplicated_minute: boolean, duplicated_second: boolean): boolean {
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
    static isTipsOptions(value: Object | string | number | undefined | boolean, duplicated_appearingTime: boolean, duplicated_disappearingTime: boolean, duplicated_appearingTimeWithContinuousOperation: boolean, duplicated_disappearingTimeWithContinuousOperation: boolean, duplicated_enableArrow: boolean, duplicated_arrowPointPosition: boolean, duplicated_arrowWidth: boolean, duplicated_arrowHeight: boolean): boolean {
        if ((!duplicated_appearingTime) && (value?.hasOwnProperty("appearingTime"))) {
            return true
        }
        else if ((!duplicated_disappearingTime) && (value?.hasOwnProperty("disappearingTime"))) {
            return true
        }
        else if ((!duplicated_appearingTimeWithContinuousOperation) && (value?.hasOwnProperty("appearingTimeWithContinuousOperation"))) {
            return true
        }
        else if ((!duplicated_disappearingTimeWithContinuousOperation) && (value?.hasOwnProperty("disappearingTimeWithContinuousOperation"))) {
            return true
        }
        else if ((!duplicated_enableArrow) && (value?.hasOwnProperty("enableArrow"))) {
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
        else {
            throw new Error("Can not discriminate value typeof TipsOptions")
        }
    }
    static isTitleHeight(value: Object | string | number | undefined | boolean): boolean {
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
    static isTodayStyle(value: Object | string | number | undefined | boolean, duplicated_focusedDayColor: boolean, duplicated_focusedLunarColor: boolean, duplicated_focusedAreaBackgroundColor: boolean, duplicated_focusedAreaRadius: boolean): boolean {
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
    static isToggleConfiguration(value: Object | string | number | undefined | boolean, duplicated_isOn: boolean, duplicated_toggleEnabled: boolean, duplicated_triggerChange: boolean): boolean {
        if ((!duplicated_isOn) && (value?.hasOwnProperty("isOn"))) {
            return true
        }
        else if ((!duplicated_toggleEnabled) && (value?.hasOwnProperty("toggleEnabled"))) {
            return true
        }
        else if ((!duplicated_triggerChange) && (value?.hasOwnProperty("triggerChange"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof ToggleConfiguration")
        }
    }
    static isToggleOptions(value: Object | string | number | undefined | boolean, duplicated_type: boolean, duplicated_isOn: boolean): boolean {
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
    static isToggleType(value: Object | string | number | undefined | boolean): boolean {
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
    static isToolbarItem(value: Object | string | number | undefined | boolean, duplicated_value: boolean, duplicated_icon: boolean, duplicated_symbolIcon: boolean, duplicated_action: boolean, duplicated_status: boolean, duplicated_activeIcon: boolean, duplicated_activeSymbolIcon: boolean): boolean {
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
    static isToolbarItemStatus(value: Object | string | number | undefined | boolean): boolean {
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
    static isTouchEvent(value: Object | string | number | undefined | boolean, duplicated_type: boolean, duplicated_touches: boolean, duplicated_changedTouches: boolean, duplicated_stopPropagation: boolean, duplicated_preventDefault: boolean): boolean {
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
    static isTouchObject(value: Object | string | number | undefined | boolean, duplicated_type: boolean, duplicated_id: boolean, duplicated_displayX: boolean, duplicated_displayY: boolean, duplicated_windowX: boolean, duplicated_windowY: boolean, duplicated_x: boolean, duplicated_y: boolean, duplicated_hand: boolean, duplicated_pressedTime: boolean, duplicated_pressure: boolean, duplicated_width: boolean, duplicated_height: boolean): boolean {
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
        else if ((!duplicated_x) && (value?.hasOwnProperty("x"))) {
            return true
        }
        else if ((!duplicated_y) && (value?.hasOwnProperty("y"))) {
            return true
        }
        else if ((!duplicated_hand) && (value?.hasOwnProperty("hand"))) {
            return true
        }
        else if ((!duplicated_pressedTime) && (value?.hasOwnProperty("pressedTime"))) {
            return true
        }
        else if ((!duplicated_pressure) && (value?.hasOwnProperty("pressure"))) {
            return true
        }
        else if ((!duplicated_width) && (value?.hasOwnProperty("width"))) {
            return true
        }
        else if ((!duplicated_height) && (value?.hasOwnProperty("height"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof TouchObject")
        }
    }
    static isTouchResult(value: Object | string | number | undefined | boolean, duplicated_strategy: boolean, duplicated_id: boolean): boolean {
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
    static isTouchTestInfo(value: Object | string | number | undefined | boolean, duplicated_windowX: boolean, duplicated_windowY: boolean, duplicated_parentX: boolean, duplicated_parentY: boolean, duplicated_x: boolean, duplicated_y: boolean, duplicated_rect: boolean, duplicated_id: boolean): boolean {
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
    static isTouchTestStrategy(value: Object | string | number | undefined | boolean): boolean {
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
    static isTouchType(value: Object | string | number | undefined | boolean): boolean {
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
    static isTransitionEdge(value: Object | string | number | undefined | boolean): boolean {
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
    static isTransitionEffect(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof TransitionEffect")
    }
    static isTransitionHierarchyStrategy(value: Object | string | number | undefined | boolean): boolean {
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
    static isTransitionType(value: Object | string | number | undefined | boolean): boolean {
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
    static isTranslateOptions(value: Object | string | number | undefined | boolean, duplicated_x: boolean, duplicated_y: boolean, duplicated_z: boolean): boolean {
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
    static isTranslateResult(value: Object | string | number | undefined | boolean, duplicated_x: boolean, duplicated_y: boolean, duplicated_z: boolean): boolean {
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
            throw new Error("Can not discriminate value typeof TranslateResult")
        }
    }
    static isUICommonEvent(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof UICommonEvent")
    }
    static isUIContext(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof UIContext")
    }
    static isuiEffect_BrightnessBlender(value: Object | string | number | undefined | boolean, duplicated_cubicRate: boolean, duplicated_quadraticRate: boolean, duplicated_linearRate: boolean, duplicated_degree: boolean, duplicated_saturation: boolean, duplicated_positiveCoefficient: boolean, duplicated_negativeCoefficient: boolean, duplicated_fraction: boolean): boolean {
        if ((!duplicated_cubicRate) && (value?.hasOwnProperty("cubicRate"))) {
            return true
        }
        else if ((!duplicated_quadraticRate) && (value?.hasOwnProperty("quadraticRate"))) {
            return true
        }
        else if ((!duplicated_linearRate) && (value?.hasOwnProperty("linearRate"))) {
            return true
        }
        else if ((!duplicated_degree) && (value?.hasOwnProperty("degree"))) {
            return true
        }
        else if ((!duplicated_saturation) && (value?.hasOwnProperty("saturation"))) {
            return true
        }
        else if ((!duplicated_positiveCoefficient) && (value?.hasOwnProperty("positiveCoefficient"))) {
            return true
        }
        else if ((!duplicated_negativeCoefficient) && (value?.hasOwnProperty("negativeCoefficient"))) {
            return true
        }
        else if ((!duplicated_fraction) && (value?.hasOwnProperty("fraction"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof uiEffect.BrightnessBlender")
        }
    }
    static isuiEffect_BrightnessBlenderParam(value: Object | string | number | undefined | boolean, duplicated_cubicRate: boolean, duplicated_quadraticRate: boolean, duplicated_linearRate: boolean, duplicated_degree: boolean, duplicated_saturation: boolean, duplicated_positiveCoefficient: boolean, duplicated_negativeCoefficient: boolean, duplicated_fraction: boolean): boolean {
        if ((!duplicated_cubicRate) && (value?.hasOwnProperty("cubicRate"))) {
            return true
        }
        else if ((!duplicated_quadraticRate) && (value?.hasOwnProperty("quadraticRate"))) {
            return true
        }
        else if ((!duplicated_linearRate) && (value?.hasOwnProperty("linearRate"))) {
            return true
        }
        else if ((!duplicated_degree) && (value?.hasOwnProperty("degree"))) {
            return true
        }
        else if ((!duplicated_saturation) && (value?.hasOwnProperty("saturation"))) {
            return true
        }
        else if ((!duplicated_positiveCoefficient) && (value?.hasOwnProperty("positiveCoefficient"))) {
            return true
        }
        else if ((!duplicated_negativeCoefficient) && (value?.hasOwnProperty("negativeCoefficient"))) {
            return true
        }
        else if ((!duplicated_fraction) && (value?.hasOwnProperty("fraction"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof uiEffect.BrightnessBlenderParam")
        }
    }
    static isuiEffect_Filter(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof uiEffect.Filter")
    }
    static isuiEffect_VisualEffect(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof uiEffect.VisualEffect")
    }
    static isUIExtensionOptions(value: Object | string | number | undefined | boolean, duplicated_isTransferringCaller: boolean, duplicated_placeholder: boolean, duplicated_areaChangePlaceholder: boolean, duplicated_dpiFollowStrategy: boolean, duplicated_windowModeFollowStrategy: boolean): boolean {
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
        else if ((!duplicated_windowModeFollowStrategy) && (value?.hasOwnProperty("windowModeFollowStrategy"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof UIExtensionOptions")
        }
    }
    static isUIExtensionProxy(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof UIExtensionProxy")
    }
    static isUIGestureEvent(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof UIGestureEvent")
    }
    static isUnderlineColor(value: Object | string | number | undefined | boolean, duplicated_typing: boolean, duplicated_normal: boolean, duplicated_error: boolean, duplicated_disable: boolean): boolean {
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
    static isunifiedDataChannel_Summary(value: Object | string | number | undefined | boolean, duplicated_summary: boolean, duplicated_totalSize: boolean): boolean {
        if ((!duplicated_summary) && (value?.hasOwnProperty("summary"))) {
            return true
        }
        else if ((!duplicated_totalSize) && (value?.hasOwnProperty("totalSize"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof unifiedDataChannel.Summary")
        }
    }
    static isunifiedDataChannel_UnifiedData(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof unifiedDataChannel.UnifiedData")
    }
    static isuniformTypeDescriptor_UniformDataType(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (uniformTypeDescriptor.UniformDataType.ENTITY)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.OBJECT)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.COMPOSITE_OBJECT)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.TEXT)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.PLAIN_TEXT)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.HTML)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.HYPERLINK)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.XML)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.XHTML)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.RSS)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.SMIL)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.SOURCE_CODE)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.SCRIPT)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.SHELL_SCRIPT)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.CSH_SCRIPT)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.PERL_SCRIPT)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.PHP_SCRIPT)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.PYTHON_SCRIPT)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.RUBY_SCRIPT)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.TYPE_SCRIPT)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.JAVA_SCRIPT)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.CSS)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.C_HEADER)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.C_SOURCE)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.C_PLUS_PLUS_HEADER)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.C_PLUS_PLUS_SOURCE)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.JAVA_SOURCE)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.TEX)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.MARKDOWN)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.ASC_TEXT)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.RICH_TEXT)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.DELIMITED_VALUES_TEXT)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.COMMA_SEPARATED_VALUES_TEXT)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.TAB_SEPARATED_VALUES_TEXT)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.EBOOK)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.EPUB)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.AZW)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.AZW3)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.KFX)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.MOBI)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.MEDIA)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.IMAGE)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.JPEG)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.PNG)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.RAW_IMAGE)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.TIFF)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.BMP)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.ICO)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.PHOTOSHOP_IMAGE)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.AI_IMAGE)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.FAX)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.JFX_FAX)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.EFX_FAX)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.XBITMAP_IMAGE)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.GIF)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.TGA_IMAGE)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.SGI_IMAGE)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.OPENEXR_IMAGE)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.FLASHPIX_IMAGE)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.WORD_DOC)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.EXCEL)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.PPT)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.WORD_DOT)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.POWERPOINT_PPS)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.POWERPOINT_POT)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.EXCEL_XLT)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.VISIO_VSD)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.PDF)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.POSTSCRIPT)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.ENCAPSULATED_POSTSCRIPT)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.VIDEO)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.AVI)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.MPEG)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.MPEG4)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.VIDEO_3GPP)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.VIDEO_3GPP2)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.TS)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.MPEGURL_VIDEO)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.WINDOWS_MEDIA_WM)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.WINDOWS_MEDIA_WMV)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.WINDOWS_MEDIA_WMP)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.WINDOWS_MEDIA_WVX)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.WINDOWS_MEDIA_WMX)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.REALMEDIA)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.MATROSKA_VIDEO)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.FLASH)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.AUDIO)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.AAC)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.AIFF)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.ALAC)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.FLAC)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.MP3)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.OGG)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.PCM)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.WINDOWS_MEDIA_WMA)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.WAVEFORM_AUDIO)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.WINDOWS_MEDIA_WAX)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.AU_AUDIO)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.AIFC_AUDIO)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.MPEGURL_AUDIO)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.MPEG_4_AUDIO)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.MP2)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.MPEG_AUDIO)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.ULAW_AUDIO)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.SD2_AUDIO)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.REALAUDIO)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.MATROSKA_AUDIO)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.FILE)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.DIRECTORY)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.FOLDER)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.SYMLINK)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.ARCHIVE)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.BZ2_ARCHIVE)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.OPG)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.TAZ_ARCHIVE)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.WEB_ARCHIVE)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.DISK_IMAGE)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.ISO)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.TAR_ARCHIVE)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.ZIP_ARCHIVE)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.JAVA_ARCHIVE)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.GNU_TAR_ARCHIVE)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.GNU_ZIP_ARCHIVE)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.GNU_ZIP_TAR_ARCHIVE)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.OPENXML)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.WORDPROCESSINGML_DOCUMENT)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.SPREADSHEETML_SHEET)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.PRESENTATIONML_PRESENTATION)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.DRAWINGML_VISIO)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.DRAWINGML_TEMPLATE)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.WORDPROCESSINGML_TEMPLATE)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.PRESENTATIONML_TEMPLATE)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.PRESENTATIONML_SLIDESHOW)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.SPREADSHEETML_TEMPLATE)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.OPENDOCUMENT)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.OPENDOCUMENT_TEXT)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.OPENDOCUMENT_SPREADSHEET)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.OPENDOCUMENT_PRESENTATION)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.OPENDOCUMENT_GRAPHICS)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.OPENDOCUMENT_FORMULA)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.STUFFIT_ARCHIVE)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.RAR_ARCHIVE)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.SEVEN_ZIP_ARCHIVE)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.CALENDAR)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.VCS)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.ICS)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.CONTACT)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.DATABASE)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.MESSAGE)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.EXECUTABLE)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.PORTABLE_EXECUTABLE)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.SUN_JAVA_CLASS)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.VCARD)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.NAVIGATION)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.LOCATION)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.FONT)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.TRUETYPE_FONT)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.TRUETYPE_COLLECTION_FONT)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.OPENTYPE_FONT)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.POSTSCRIPT_FONT)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.POSTSCRIPT_PFB_FONT)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.POSTSCRIPT_PFA_FONT)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.OPENHARMONY_FORM)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.OPENHARMONY_APP_ITEM)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.OPENHARMONY_PIXEL_MAP)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.OPENHARMONY_ATOMIC_SERVICE)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.OPENHARMONY_PACKAGE)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.OPENHARMONY_HAP)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.OPENHARMONY_HDOC)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.OPENHARMONY_HINOTE)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.OPENHARMONY_STYLED_STRING)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.OPENHARMONY_WANT)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.OFD)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.CAD)) {
            return true
        }
        else if ((value) === (uniformTypeDescriptor.UniformDataType.OCTET_STREAM)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof uniformTypeDescriptor.UniformDataType")
        }
    }
    static isUrlStyle(value: Object | string | number | undefined | boolean, duplicated_url: boolean): boolean {
        if ((!duplicated_url) && (value?.hasOwnProperty("url"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof UrlStyle")
        }
    }
    static isUserDataSpan(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof UserDataSpan")
    }
    static isVector2(value: Object | string | number | undefined | boolean, duplicated_x: boolean, duplicated_y: boolean): boolean {
        if ((!duplicated_x) && (value?.hasOwnProperty("x"))) {
            return true
        }
        else if ((!duplicated_y) && (value?.hasOwnProperty("y"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof Vector2")
        }
    }
    static isVector3(value: Object | string | number | undefined | boolean, duplicated_x: boolean, duplicated_y: boolean, duplicated_z: boolean): boolean {
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
            throw new Error("Can not discriminate value typeof Vector3")
        }
    }
    static isVerticalAlign(value: Object | string | number | undefined | boolean): boolean {
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
    static isVideoController(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof VideoController")
    }
    static isVideoOptions(value: Object | string | number | undefined | boolean, duplicated_src: boolean, duplicated_currentProgressRate: boolean, duplicated_previewUri: boolean, duplicated_controller: boolean, duplicated_imageAIOptions: boolean, duplicated_posterOptions: boolean): boolean {
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
        else if ((!duplicated_posterOptions) && (value?.hasOwnProperty("posterOptions"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof VideoOptions")
        }
    }
    static isViewportFit(value: Object | string | number | undefined | boolean): boolean {
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
    static isViewportRect(value: Object | string | number | undefined | boolean, duplicated_x: boolean, duplicated_y: boolean, duplicated_width: boolean, duplicated_height: boolean): boolean {
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
    static isVisibility(value: Object | string | number | undefined | boolean): boolean {
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
    static isVisibleAreaEventOptions(value: Object | string | number | undefined | boolean, duplicated_ratios: boolean, duplicated_expectedUpdateInterval: boolean): boolean {
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
    static isVisibleListContentInfo(value: Object | string | number | undefined | boolean, duplicated_index: boolean, duplicated_itemGroupArea: boolean, duplicated_itemIndexInGroup: boolean): boolean {
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
    static isWant(value: Object | string | number | undefined | boolean, duplicated_bundleName: boolean, duplicated_abilityName: boolean, duplicated_deviceId: boolean, duplicated_uri: boolean, duplicated_type: boolean, duplicated_flags: boolean, duplicated_action: boolean, duplicated_parameters: boolean, duplicated_entities: boolean, duplicated_moduleName: boolean): boolean {
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
    static isWaterFlowLayoutMode(value: Object | string | number | undefined | boolean): boolean {
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
    static isWaterFlowOptions(value: Object | string | number | undefined | boolean, duplicated_footer: boolean, duplicated_footerContent: boolean, duplicated_scroller: boolean, duplicated_sections: boolean, duplicated_layoutMode: boolean): boolean {
        if ((!duplicated_footer) && (value?.hasOwnProperty("footer"))) {
            return true
        }
        else if ((!duplicated_footerContent) && (value?.hasOwnProperty("footerContent"))) {
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
    static isWaterFlowSections(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof WaterFlowSections")
    }
    static isWebCaptureMode(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (WebCaptureMode.HOME_SCREEN)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof WebCaptureMode")
        }
    }
    static isWebContextMenuParam(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof WebContextMenuParam")
    }
    static isWebContextMenuResult(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof WebContextMenuResult")
    }
    static isWebCookie(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof WebCookie")
    }
    static isWebDarkMode(value: Object | string | number | undefined | boolean): boolean {
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
    static isWebElementType(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (WebElementType.IMAGE)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof WebElementType")
        }
    }
    static isWebKeyboardAvoidMode(value: Object | string | number | undefined | boolean): boolean {
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
    static isWebKeyboardCallbackInfo(value: Object | string | number | undefined | boolean, duplicated_controller: boolean, duplicated_attributes: boolean): boolean {
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
    static isWebKeyboardController(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof WebKeyboardController")
    }
    static isWebKeyboardOptions(value: Object | string | number | undefined | boolean, duplicated_useSystemKeyboard: boolean, duplicated_enterKeyType: boolean, duplicated_customKeyboard: boolean): boolean {
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
    static isWebLayoutMode(value: Object | string | number | undefined | boolean): boolean {
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
    static isWebMediaOptions(value: Object | string | number | undefined | boolean, duplicated_resumeInterval: boolean, duplicated_audioExclusive: boolean): boolean {
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
    static isWebNavigationType(value: Object | string | number | undefined | boolean): boolean {
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
    static isWebOptions(value: Object | string | number | undefined | boolean, duplicated_src: boolean, duplicated_controller: boolean, duplicated_renderMode: boolean, duplicated_incognitoMode: boolean, duplicated_sharedRenderProcessToken: boolean): boolean {
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
    static isWebResourceError(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof WebResourceError")
    }
    static isWebResourceRequest(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof WebResourceRequest")
    }
    static isWebResourceResponse(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof WebResourceResponse")
    }
    static isWebResponseType(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (WebResponseType.LONG_PRESS)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof WebResponseType")
        }
    }
    static iswebview_WebHeader(value: Object | string | number | undefined | boolean, duplicated_headerKey: boolean, duplicated_headerValue: boolean): boolean {
        if ((!duplicated_headerKey) && (value?.hasOwnProperty("headerKey"))) {
            return true
        }
        else if ((!duplicated_headerValue) && (value?.hasOwnProperty("headerValue"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof webview.WebHeader")
        }
    }
    static iswebview_WebviewController(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof webview.WebviewController")
    }
    static isWeek(value: Object | string | number | undefined | boolean): boolean {
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
    static isWeekStyle(value: Object | string | number | undefined | boolean, duplicated_weekColor: boolean, duplicated_weekendDayColor: boolean, duplicated_weekendLunarColor: boolean, duplicated_weekFontSize: boolean, duplicated_weekHeight: boolean, duplicated_weekWidth: boolean, duplicated_weekAndDayRowSpace: boolean): boolean {
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
    static isWidthBreakpoint(value: Object | string | number | undefined | boolean): boolean {
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
    static iswindow_SystemBarStyle(value: Object | string | number | undefined | boolean, duplicated_statusBarContentColor: boolean): boolean {
        if ((!duplicated_statusBarContentColor) && (value?.hasOwnProperty("statusBarContentColor"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof window.SystemBarStyle")
        }
    }
    static iswindow_WindowStatusType(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (window.WindowStatusType.UNDEFINED)) {
            return true
        }
        else if ((value) === (window.WindowStatusType.FULL_SCREEN)) {
            return true
        }
        else if ((value) === (window.WindowStatusType.MAXIMIZE)) {
            return true
        }
        else if ((value) === (window.WindowStatusType.MINIMIZE)) {
            return true
        }
        else if ((value) === (window.WindowStatusType.FLOATING)) {
            return true
        }
        else if ((value) === (window.WindowStatusType.SPLIT_SCREEN)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof window.WindowStatusType")
        }
    }
    static isWindowAnimationTarget(value: Object | string | number | undefined | boolean, duplicated_bundleName: boolean, duplicated_abilityName: boolean, duplicated_windowBounds: boolean, duplicated_missionId: boolean): boolean {
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
    static isWindowModeFollowStrategy(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (WindowModeFollowStrategy.FOLLOW_HOST_WINDOW_MODE)) {
            return true
        }
        else if ((value) === (WindowModeFollowStrategy.FOLLOW_UI_EXTENSION_ABILITY_WINDOW_MODE)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof WindowModeFollowStrategy")
        }
    }
    static isWordBreak(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (WordBreak.NORMAL)) {
            return true
        }
        else if ((value) === (WordBreak.BREAK_ALL)) {
            return true
        }
        else if ((value) === (WordBreak.BREAK_WORD)) {
            return true
        }
        else if ((value) === (WordBreak.HYPHENATION)) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof WordBreak")
        }
    }
    static isWorkerEventListener(value: Object | string | number | undefined | boolean): boolean {
        throw new Error("Can not discriminate value typeof WorkerEventListener")
    }
    static isWorkerOptions(value: Object | string | number | undefined | boolean, duplicated_type: boolean, duplicated_name: boolean, duplicated_shared: boolean): boolean {
        if ((!duplicated_type) && (value?.hasOwnProperty("type"))) {
            return true
        }
        else if ((!duplicated_name) && (value?.hasOwnProperty("name"))) {
            return true
        }
        else if ((!duplicated_shared) && (value?.hasOwnProperty("shared"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof WorkerOptions")
        }
    }
    static isWorkStateStyle(value: Object | string | number | undefined | boolean, duplicated_workDayMarkColor: boolean, duplicated_offDayMarkColor: boolean, duplicated_workDayMarkSize: boolean, duplicated_offDayMarkSize: boolean, duplicated_workStateWidth: boolean, duplicated_workStateHorizontalMovingDistance: boolean, duplicated_workStateVerticalMovingDistance: boolean): boolean {
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
    static isXComponentController(value: Object | string | number | undefined | boolean, duplicated_onSurfaceCreated: boolean, duplicated_onSurfaceChanged: boolean, duplicated_onSurfaceDestroyed: boolean): boolean {
        if ((!duplicated_onSurfaceCreated) && (value?.hasOwnProperty("onSurfaceCreated"))) {
            return true
        }
        else if ((!duplicated_onSurfaceChanged) && (value?.hasOwnProperty("onSurfaceChanged"))) {
            return true
        }
        else if ((!duplicated_onSurfaceDestroyed) && (value?.hasOwnProperty("onSurfaceDestroyed"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof XComponentController")
        }
    }
    static isXComponentOptions(value: Object | string | number | undefined | boolean, duplicated_type: boolean, duplicated_controller: boolean, duplicated_imageAIOptions: boolean, duplicated_screenId: boolean): boolean {
        if ((!duplicated_type) && (value?.hasOwnProperty("type"))) {
            return true
        }
        else if ((!duplicated_controller) && (value?.hasOwnProperty("controller"))) {
            return true
        }
        else if ((!duplicated_imageAIOptions) && (value?.hasOwnProperty("imageAIOptions"))) {
            return true
        }
        else if ((!duplicated_screenId) && (value?.hasOwnProperty("screenId"))) {
            return true
        }
        else {
            throw new Error("Can not discriminate value typeof XComponentOptions")
        }
    }
    static isXComponentParameter(value: Object | string | number | undefined | boolean, duplicated_id: boolean, duplicated_type: boolean, duplicated_libraryname: boolean, duplicated_controller: boolean): boolean {
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
            throw new Error("Can not discriminate value typeof XComponentParameter")
        }
    }
    static isXComponentType(value: Object | string | number | undefined | boolean): boolean {
        if ((value) === (XComponentType.SURFACE)) {
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
    static AccessibilityHoverType_ToNumeric(value: AccessibilityHoverType): int32 {
        return value as int32
    }
    static AccessibilityHoverType_FromNumeric(ordinal: int32): AccessibilityHoverType {
        return ordinal as AccessibilityHoverType
    }
    static AccessibilityRoleType_ToNumeric(value: AccessibilityRoleType): int32 {
        return value as int32
    }
    static AccessibilityRoleType_FromNumeric(ordinal: int32): AccessibilityRoleType {
        return ordinal as AccessibilityRoleType
    }
    static AccessibilitySamePageMode_ToNumeric(value: AccessibilitySamePageMode): int32 {
        return value as int32
    }
    static AccessibilitySamePageMode_FromNumeric(ordinal: int32): AccessibilitySamePageMode {
        return ordinal as AccessibilitySamePageMode
    }
    static AdaptiveColor_ToNumeric(value: AdaptiveColor): int32 {
        return value as int32
    }
    static AdaptiveColor_FromNumeric(ordinal: int32): AdaptiveColor {
        return ordinal as AdaptiveColor
    }
    static Alignment_ToNumeric(value: Alignment): int32 {
        return value as int32
    }
    static Alignment_FromNumeric(ordinal: int32): Alignment {
        return ordinal as Alignment
    }
    static AnimationMode_ToNumeric(value: AnimationMode): int32 {
        return value as int32
    }
    static AnimationMode_FromNumeric(ordinal: int32): AnimationMode {
        return ordinal as AnimationMode
    }
    static AnimationStatus_ToNumeric(value: AnimationStatus): int32 {
        return value as int32
    }
    static AnimationStatus_FromNumeric(ordinal: int32): AnimationStatus {
        return ordinal as AnimationStatus
    }
    static AppRotation_ToNumeric(value: AppRotation): int32 {
        return value as int32
    }
    static AppRotation_FromNumeric(ordinal: int32): AppRotation {
        return ordinal as AppRotation
    }
    static ArrowPointPosition_ToNumeric(value: ArrowPointPosition): int32 {
        return value as int32
    }
    static ArrowPointPosition_FromNumeric(ordinal: int32): ArrowPointPosition {
        return ordinal as ArrowPointPosition
    }
    static ArrowPosition_ToNumeric(value: ArrowPosition): int32 {
        return value as int32
    }
    static ArrowPosition_FromNumeric(ordinal: int32): ArrowPosition {
        return ordinal as ArrowPosition
    }
    static AutoCapitalizationMode_ToNumeric(value: AutoCapitalizationMode): int32 {
        return value as int32
    }
    static AutoCapitalizationMode_FromNumeric(ordinal: int32): AutoCapitalizationMode {
        return ordinal as AutoCapitalizationMode
    }
    static AvoidanceMode_ToNumeric(value: AvoidanceMode): int32 {
        return value as int32
    }
    static AvoidanceMode_FromNumeric(ordinal: int32): AvoidanceMode {
        return ordinal as AvoidanceMode
    }
    static Axis_ToNumeric(value: Axis): int32 {
        return value as int32
    }
    static Axis_FromNumeric(ordinal: int32): Axis {
        return ordinal as Axis
    }
    static AxisAction_ToNumeric(value: AxisAction): int32 {
        return value as int32
    }
    static AxisAction_FromNumeric(ordinal: int32): AxisAction {
        return ordinal as AxisAction
    }
    static AxisModel_ToNumeric(value: AxisModel): int32 {
        return value as int32
    }
    static AxisModel_FromNumeric(ordinal: int32): AxisModel {
        return ordinal as AxisModel
    }
    static BadgePosition_ToNumeric(value: BadgePosition): int32 {
        return value as int32
    }
    static BadgePosition_FromNumeric(ordinal: int32): BadgePosition {
        return ordinal as BadgePosition
    }
    static BarMode_ToNumeric(value: BarMode): int32 {
        return value as int32
    }
    static BarMode_FromNumeric(ordinal: int32): BarMode {
        return ordinal as BarMode
    }
    static BarPosition_ToNumeric(value: BarPosition): int32 {
        return value as int32
    }
    static BarPosition_FromNumeric(ordinal: int32): BarPosition {
        return ordinal as BarPosition
    }
    static BarrierDirection_ToNumeric(value: BarrierDirection): int32 {
        return value as int32
    }
    static BarrierDirection_FromNumeric(ordinal: int32): BarrierDirection {
        return ordinal as BarrierDirection
    }
    static BarState_ToNumeric(value: BarState): int32 {
        return value as int32
    }
    static BarState_FromNumeric(ordinal: int32): BarState {
        return ordinal as BarState
    }
    static BarStyle_ToNumeric(value: BarStyle): int32 {
        return value as int32
    }
    static BarStyle_FromNumeric(ordinal: int32): BarStyle {
        return ordinal as BarStyle
    }
    static BlendApplyType_ToNumeric(value: BlendApplyType): int32 {
        return value as int32
    }
    static BlendApplyType_FromNumeric(ordinal: int32): BlendApplyType {
        return ordinal as BlendApplyType
    }
    static BlendMode_ToNumeric(value: BlendMode): int32 {
        return value as int32
    }
    static BlendMode_FromNumeric(ordinal: int32): BlendMode {
        return ordinal as BlendMode
    }
    static BlurOnKeyboardHideMode_ToNumeric(value: BlurOnKeyboardHideMode): int32 {
        return value as int32
    }
    static BlurOnKeyboardHideMode_FromNumeric(ordinal: int32): BlurOnKeyboardHideMode {
        return ordinal as BlurOnKeyboardHideMode
    }
    static BlurStyle_ToNumeric(value: BlurStyle): int32 {
        return value as int32
    }
    static BlurStyle_FromNumeric(ordinal: int32): BlurStyle {
        return ordinal as BlurStyle
    }
    static BlurStyleActivePolicy_ToNumeric(value: BlurStyleActivePolicy): int32 {
        return value as int32
    }
    static BlurStyleActivePolicy_FromNumeric(ordinal: int32): BlurStyleActivePolicy {
        return ordinal as BlurStyleActivePolicy
    }
    static BorderStyle_ToNumeric(value: BorderStyle): int32 {
        return value as int32
    }
    static BorderStyle_FromNumeric(ordinal: int32): BorderStyle {
        return ordinal as BorderStyle
    }
    static BreakpointsReference_ToNumeric(value: BreakpointsReference): int32 {
        return value as int32
    }
    static BreakpointsReference_FromNumeric(ordinal: int32): BreakpointsReference {
        return ordinal as BreakpointsReference
    }
    static ButtonRole_ToNumeric(value: ButtonRole): int32 {
        return value as int32
    }
    static ButtonRole_FromNumeric(ordinal: int32): ButtonRole {
        return ordinal as ButtonRole
    }
    static ButtonStyleMode_ToNumeric(value: ButtonStyleMode): int32 {
        return value as int32
    }
    static ButtonStyleMode_FromNumeric(ordinal: int32): ButtonStyleMode {
        return ordinal as ButtonStyleMode
    }
    static ButtonType_ToNumeric(value: ButtonType): int32 {
        return value as int32
    }
    static ButtonType_FromNumeric(ordinal: int32): ButtonType {
        return ordinal as ButtonType
    }
    static CacheMode_ToNumeric(value: CacheMode): int32 {
        return value as int32
    }
    static CacheMode_FromNumeric(ordinal: int32): CacheMode {
        return ordinal as CacheMode
    }
    static CalendarAlign_ToNumeric(value: CalendarAlign): int32 {
        return value as int32
    }
    static CalendarAlign_FromNumeric(ordinal: int32): CalendarAlign {
        return ordinal as CalendarAlign
    }
    static CancelButtonStyle_ToNumeric(value: CancelButtonStyle): int32 {
        return value as int32
    }
    static CancelButtonStyle_FromNumeric(ordinal: int32): CancelButtonStyle {
        return ordinal as CancelButtonStyle
    }
    static ChainEdgeEffect_ToNumeric(value: ChainEdgeEffect): int32 {
        return value as int32
    }
    static ChainEdgeEffect_FromNumeric(ordinal: int32): ChainEdgeEffect {
        return ordinal as ChainEdgeEffect
    }
    static ChainStyle_ToNumeric(value: ChainStyle): int32 {
        return value as int32
    }
    static ChainStyle_FromNumeric(ordinal: int32): ChainStyle {
        return ordinal as ChainStyle
    }
    static CheckBoxShape_ToNumeric(value: CheckBoxShape): int32 {
        return value as int32
    }
    static CheckBoxShape_FromNumeric(ordinal: int32): CheckBoxShape {
        return ordinal as CheckBoxShape
    }
    static ClickEffectLevel_ToNumeric(value: ClickEffectLevel): int32 {
        return value as int32
    }
    static ClickEffectLevel_FromNumeric(ordinal: int32): ClickEffectLevel {
        return ordinal as ClickEffectLevel
    }
    static Color_ToNumeric(value: Color): int32 {
        return value as int32
    }
    static Color_FromNumeric(ordinal: int32): Color {
        return ordinal as Color
    }
    static ColoringStrategy_ToNumeric(value: ColoringStrategy): int32 {
        return value as int32
    }
    static ColoringStrategy_FromNumeric(ordinal: int32): ColoringStrategy {
        return ordinal as ColoringStrategy
    }
    static ColorMode_ToNumeric(value: ColorMode): int32 {
        return value as int32
    }
    static ColorMode_FromNumeric(ordinal: int32): ColorMode {
        return ordinal as ColorMode
    }
    static ContentClipMode_ToNumeric(value: ContentClipMode): int32 {
        return value as int32
    }
    static ContentClipMode_FromNumeric(ordinal: int32): ContentClipMode {
        return ordinal as ContentClipMode
    }
    static ContentType_ToNumeric(value: ContentType): int32 {
        return value as int32
    }
    static ContentType_FromNumeric(ordinal: int32): ContentType {
        return ordinal as ContentType
    }
    static ContextMenuEditStateFlags_ToNumeric(value: ContextMenuEditStateFlags): int32 {
        return value as int32
    }
    static ContextMenuEditStateFlags_FromNumeric(ordinal: int32): ContextMenuEditStateFlags {
        return ordinal as ContextMenuEditStateFlags
    }
    static ContextMenuInputFieldType_ToNumeric(value: ContextMenuInputFieldType): int32 {
        return value as int32
    }
    static ContextMenuInputFieldType_FromNumeric(ordinal: int32): ContextMenuInputFieldType {
        return ordinal as ContextMenuInputFieldType
    }
    static ContextMenuMediaType_ToNumeric(value: ContextMenuMediaType): int32 {
        return value as int32
    }
    static ContextMenuMediaType_FromNumeric(ordinal: int32): ContextMenuMediaType {
        return ordinal as ContextMenuMediaType
    }
    static ContextMenuSourceType_ToNumeric(value: ContextMenuSourceType): int32 {
        return value as int32
    }
    static ContextMenuSourceType_FromNumeric(ordinal: int32): ContextMenuSourceType {
        return ordinal as ContextMenuSourceType
    }
    static ControlSize_ToNumeric(value: ControlSize): int32 {
        return value as int32
    }
    static ControlSize_FromNumeric(ordinal: int32): ControlSize {
        return ordinal as ControlSize
    }
    static CopyOptions_ToNumeric(value: CopyOptions): int32 {
        return value as int32
    }
    static CopyOptions_FromNumeric(ordinal: int32): CopyOptions {
        return ordinal as CopyOptions
    }
    static CrownAction_ToNumeric(value: CrownAction): int32 {
        return value as int32
    }
    static CrownAction_FromNumeric(ordinal: int32): CrownAction {
        return ordinal as CrownAction
    }
    static CrownSensitivity_ToNumeric(value: CrownSensitivity): int32 {
        return value as int32
    }
    static CrownSensitivity_FromNumeric(ordinal: int32): CrownSensitivity {
        return ordinal as CrownSensitivity
    }
    static Curve_ToNumeric(value: Curve): int32 {
        return value as int32
    }
    static Curve_FromNumeric(ordinal: int32): Curve {
        return ordinal as Curve
    }
    static DataOperationType_ToNumeric(value: DataOperationType): int32 {
        return value as int32
    }
    static DataOperationType_FromNumeric(ordinal: int32): DataOperationType {
        return ordinal as DataOperationType
    }
    static DataPanelType_ToNumeric(value: DataPanelType): int32 {
        return value as int32
    }
    static DataPanelType_FromNumeric(ordinal: int32): DataPanelType {
        return ordinal as DataPanelType
    }
    static DatePickerMode_ToNumeric(value: DatePickerMode): int32 {
        return value as int32
    }
    static DatePickerMode_FromNumeric(ordinal: int32): DatePickerMode {
        return ordinal as DatePickerMode
    }
    static DialogAlignment_ToNumeric(value: DialogAlignment): int32 {
        return value as int32
    }
    static DialogAlignment_FromNumeric(ordinal: int32): DialogAlignment {
        return ordinal as DialogAlignment
    }
    static DialogButtonDirection_ToNumeric(value: DialogButtonDirection): int32 {
        return value as int32
    }
    static DialogButtonDirection_FromNumeric(ordinal: int32): DialogButtonDirection {
        return ordinal as DialogButtonDirection
    }
    static DialogButtonStyle_ToNumeric(value: DialogButtonStyle): int32 {
        return value as int32
    }
    static DialogButtonStyle_FromNumeric(ordinal: int32): DialogButtonStyle {
        return ordinal as DialogButtonStyle
    }
    static Direction_ToNumeric(value: Direction): int32 {
        return value as int32
    }
    static Direction_FromNumeric(ordinal: int32): Direction {
        return ordinal as Direction
    }
    static DismissReason_ToNumeric(value: DismissReason): int32 {
        return value as int32
    }
    static DismissReason_FromNumeric(ordinal: int32): DismissReason {
        return ordinal as DismissReason
    }
    static DistributionType_ToNumeric(value: DistributionType): int32 {
        return value as int32
    }
    static DistributionType_FromNumeric(ordinal: int32): DistributionType {
        return ordinal as DistributionType
    }
    static DisturbanceFieldShape_ToNumeric(value: DisturbanceFieldShape): int32 {
        return value as int32
    }
    static DisturbanceFieldShape_FromNumeric(ordinal: int32): DisturbanceFieldShape {
        return ordinal as DisturbanceFieldShape
    }
    static DividerMode_ToNumeric(value: DividerMode): int32 {
        return value as int32
    }
    static DividerMode_FromNumeric(ordinal: int32): DividerMode {
        return ordinal as DividerMode
    }
    static DpiFollowStrategy_ToNumeric(value: DpiFollowStrategy): int32 {
        return value as int32
    }
    static DpiFollowStrategy_FromNumeric(ordinal: int32): DpiFollowStrategy {
        return ordinal as DpiFollowStrategy
    }
    static DragBehavior_ToNumeric(value: DragBehavior): int32 {
        return value as int32
    }
    static DragBehavior_FromNumeric(ordinal: int32): DragBehavior {
        return ordinal as DragBehavior
    }
    static DraggingSizeChangeEffect_ToNumeric(value: DraggingSizeChangeEffect): int32 {
        return value as int32
    }
    static DraggingSizeChangeEffect_FromNumeric(ordinal: int32): DraggingSizeChangeEffect {
        return ordinal as DraggingSizeChangeEffect
    }
    static DragPreviewMode_ToNumeric(value: DragPreviewMode): int32 {
        return value as int32
    }
    static DragPreviewMode_FromNumeric(ordinal: int32): DragPreviewMode {
        return ordinal as DragPreviewMode
    }
    static DragResult_ToNumeric(value: DragResult): int32 {
        return value as int32
    }
    static DragResult_FromNumeric(ordinal: int32): DragResult {
        return ordinal as DragResult
    }
    static drawing_BlendMode_ToNumeric(value: drawing.BlendMode): int32 {
        return value as int32
    }
    static drawing_BlendMode_FromNumeric(ordinal: int32): drawing.BlendMode {
        return ordinal as drawing.BlendMode
    }
    static drawing_BlurType_ToNumeric(value: drawing.BlurType): int32 {
        return value as int32
    }
    static drawing_BlurType_FromNumeric(ordinal: int32): drawing.BlurType {
        return ordinal as drawing.BlurType
    }
    static drawing_CapStyle_ToNumeric(value: drawing.CapStyle): int32 {
        return value as int32
    }
    static drawing_CapStyle_FromNumeric(ordinal: int32): drawing.CapStyle {
        return ordinal as drawing.CapStyle
    }
    static drawing_ClipOp_ToNumeric(value: drawing.ClipOp): int32 {
        return value as int32
    }
    static drawing_ClipOp_FromNumeric(ordinal: int32): drawing.ClipOp {
        return ordinal as drawing.ClipOp
    }
    static drawing_CornerPos_ToNumeric(value: drawing.CornerPos): int32 {
        return value as int32
    }
    static drawing_CornerPos_FromNumeric(ordinal: int32): drawing.CornerPos {
        return ordinal as drawing.CornerPos
    }
    static drawing_FilterMode_ToNumeric(value: drawing.FilterMode): int32 {
        return value as int32
    }
    static drawing_FilterMode_FromNumeric(ordinal: int32): drawing.FilterMode {
        return ordinal as drawing.FilterMode
    }
    static drawing_FontEdging_ToNumeric(value: drawing.FontEdging): int32 {
        return value as int32
    }
    static drawing_FontEdging_FromNumeric(ordinal: int32): drawing.FontEdging {
        return ordinal as drawing.FontEdging
    }
    static drawing_FontHinting_ToNumeric(value: drawing.FontHinting): int32 {
        return value as int32
    }
    static drawing_FontHinting_FromNumeric(ordinal: int32): drawing.FontHinting {
        return ordinal as drawing.FontHinting
    }
    static drawing_FontMetricsFlags_ToNumeric(value: drawing.FontMetricsFlags): int32 {
        return value as int32
    }
    static drawing_FontMetricsFlags_FromNumeric(ordinal: int32): drawing.FontMetricsFlags {
        return ordinal as drawing.FontMetricsFlags
    }
    static drawing_JoinStyle_ToNumeric(value: drawing.JoinStyle): int32 {
        return value as int32
    }
    static drawing_JoinStyle_FromNumeric(ordinal: int32): drawing.JoinStyle {
        return ordinal as drawing.JoinStyle
    }
    static drawing_PathDirection_ToNumeric(value: drawing.PathDirection): int32 {
        return value as int32
    }
    static drawing_PathDirection_FromNumeric(ordinal: int32): drawing.PathDirection {
        return ordinal as drawing.PathDirection
    }
    static drawing_PathFillType_ToNumeric(value: drawing.PathFillType): int32 {
        return value as int32
    }
    static drawing_PathFillType_FromNumeric(ordinal: int32): drawing.PathFillType {
        return ordinal as drawing.PathFillType
    }
    static drawing_PathMeasureMatrixFlags_ToNumeric(value: drawing.PathMeasureMatrixFlags): int32 {
        return value as int32
    }
    static drawing_PathMeasureMatrixFlags_FromNumeric(ordinal: int32): drawing.PathMeasureMatrixFlags {
        return ordinal as drawing.PathMeasureMatrixFlags
    }
    static drawing_PathOp_ToNumeric(value: drawing.PathOp): int32 {
        return value as int32
    }
    static drawing_PathOp_FromNumeric(ordinal: int32): drawing.PathOp {
        return ordinal as drawing.PathOp
    }
    static drawing_PointMode_ToNumeric(value: drawing.PointMode): int32 {
        return value as int32
    }
    static drawing_PointMode_FromNumeric(ordinal: int32): drawing.PointMode {
        return ordinal as drawing.PointMode
    }
    static drawing_RectType_ToNumeric(value: drawing.RectType): int32 {
        return value as int32
    }
    static drawing_RectType_FromNumeric(ordinal: int32): drawing.RectType {
        return ordinal as drawing.RectType
    }
    static drawing_RegionOp_ToNumeric(value: drawing.RegionOp): int32 {
        return value as int32
    }
    static drawing_RegionOp_FromNumeric(ordinal: int32): drawing.RegionOp {
        return ordinal as drawing.RegionOp
    }
    static drawing_ScaleToFit_ToNumeric(value: drawing.ScaleToFit): int32 {
        return value as int32
    }
    static drawing_ScaleToFit_FromNumeric(ordinal: int32): drawing.ScaleToFit {
        return ordinal as drawing.ScaleToFit
    }
    static drawing_ShadowFlag_ToNumeric(value: drawing.ShadowFlag): int32 {
        return value as int32
    }
    static drawing_ShadowFlag_FromNumeric(ordinal: int32): drawing.ShadowFlag {
        return ordinal as drawing.ShadowFlag
    }
    static drawing_SrcRectConstraint_ToNumeric(value: drawing.SrcRectConstraint): int32 {
        return value as int32
    }
    static drawing_SrcRectConstraint_FromNumeric(ordinal: int32): drawing.SrcRectConstraint {
        return ordinal as drawing.SrcRectConstraint
    }
    static drawing_TextEncoding_ToNumeric(value: drawing.TextEncoding): int32 {
        return value as int32
    }
    static drawing_TextEncoding_FromNumeric(ordinal: int32): drawing.TextEncoding {
        return ordinal as drawing.TextEncoding
    }
    static drawing_TileMode_ToNumeric(value: drawing.TileMode): int32 {
        return value as int32
    }
    static drawing_TileMode_FromNumeric(ordinal: int32): drawing.TileMode {
        return ordinal as drawing.TileMode
    }
    static DynamicRangeMode_ToNumeric(value: DynamicRangeMode): int32 {
        return value as int32
    }
    static DynamicRangeMode_FromNumeric(ordinal: int32): DynamicRangeMode {
        return ordinal as DynamicRangeMode
    }
    static Edge_ToNumeric(value: Edge): int32 {
        return value as int32
    }
    static Edge_FromNumeric(ordinal: int32): Edge {
        return ordinal as Edge
    }
    static EdgeEffect_ToNumeric(value: EdgeEffect): int32 {
        return value as int32
    }
    static EdgeEffect_FromNumeric(ordinal: int32): EdgeEffect {
        return ordinal as EdgeEffect
    }
    static EffectDirection_ToNumeric(value: EffectDirection): int32 {
        return value as int32
    }
    static EffectDirection_FromNumeric(ordinal: int32): EffectDirection {
        return ordinal as EffectDirection
    }
    static EffectEdge_ToNumeric(value: EffectEdge): int32 {
        return value as int32
    }
    static EffectEdge_FromNumeric(ordinal: int32): EffectEdge {
        return ordinal as EffectEdge
    }
    static EffectFillStyle_ToNumeric(value: EffectFillStyle): int32 {
        return value as int32
    }
    static EffectFillStyle_FromNumeric(ordinal: int32): EffectFillStyle {
        return ordinal as EffectFillStyle
    }
    static EffectScope_ToNumeric(value: EffectScope): int32 {
        return value as int32
    }
    static EffectScope_FromNumeric(ordinal: int32): EffectScope {
        return ordinal as EffectScope
    }
    static EffectType_ToNumeric(value: EffectType): int32 {
        return value as int32
    }
    static EffectType_FromNumeric(ordinal: int32): EffectType {
        return ordinal as EffectType
    }
    static EllipsisMode_ToNumeric(value: EllipsisMode): int32 {
        return value as int32
    }
    static EllipsisMode_FromNumeric(ordinal: int32): EllipsisMode {
        return ordinal as EllipsisMode
    }
    static EmbeddedType_ToNumeric(value: EmbeddedType): int32 {
        return value as int32
    }
    static EmbeddedType_FromNumeric(ordinal: int32): EmbeddedType {
        return ordinal as EmbeddedType
    }
    static EnterKeyType_ToNumeric(value: EnterKeyType): int32 {
        return value as int32
    }
    static EnterKeyType_FromNumeric(ordinal: int32): EnterKeyType {
        return ordinal as EnterKeyType
    }
    static FileSelectorMode_ToNumeric(value: FileSelectorMode): int32 {
        return value as int32
    }
    static FileSelectorMode_FromNumeric(ordinal: int32): FileSelectorMode {
        return ordinal as FileSelectorMode
    }
    static FillMode_ToNumeric(value: FillMode): int32 {
        return value as int32
    }
    static FillMode_FromNumeric(ordinal: int32): FillMode {
        return ordinal as FillMode
    }
    static FinishCallbackType_ToNumeric(value: FinishCallbackType): int32 {
        return value as int32
    }
    static FinishCallbackType_FromNumeric(ordinal: int32): FinishCallbackType {
        return ordinal as FinishCallbackType
    }
    static FlexAlign_ToNumeric(value: FlexAlign): int32 {
        return value as int32
    }
    static FlexAlign_FromNumeric(ordinal: int32): FlexAlign {
        return ordinal as FlexAlign
    }
    static FlexDirection_ToNumeric(value: FlexDirection): int32 {
        return value as int32
    }
    static FlexDirection_FromNumeric(ordinal: int32): FlexDirection {
        return ordinal as FlexDirection
    }
    static FlexWrap_ToNumeric(value: FlexWrap): int32 {
        return value as int32
    }
    static FlexWrap_FromNumeric(ordinal: int32): FlexWrap {
        return ordinal as FlexWrap
    }
    static FocusDrawLevel_ToNumeric(value: FocusDrawLevel): int32 {
        return value as int32
    }
    static FocusDrawLevel_FromNumeric(ordinal: int32): FocusDrawLevel {
        return ordinal as FocusDrawLevel
    }
    static FocusPriority_ToNumeric(value: FocusPriority): int32 {
        return value as int32
    }
    static FocusPriority_FromNumeric(ordinal: int32): FocusPriority {
        return ordinal as FocusPriority
    }
    static FoldStatus_ToNumeric(value: FoldStatus): int32 {
        return value as int32
    }
    static FoldStatus_FromNumeric(ordinal: int32): FoldStatus {
        return ordinal as FoldStatus
    }
    static FontStyle_ToNumeric(value: FontStyle): int32 {
        return value as int32
    }
    static FontStyle_FromNumeric(ordinal: int32): FontStyle {
        return ordinal as FontStyle
    }
    static FontWeight_ToNumeric(value: FontWeight): int32 {
        return value as int32
    }
    static FontWeight_FromNumeric(ordinal: int32): FontWeight {
        return ordinal as FontWeight
    }
    static FormDimension_ToNumeric(value: FormDimension): int32 {
        return value as int32
    }
    static FormDimension_FromNumeric(ordinal: int32): FormDimension {
        return ordinal as FormDimension
    }
    static FormRenderingMode_ToNumeric(value: FormRenderingMode): int32 {
        return value as int32
    }
    static FormRenderingMode_FromNumeric(ordinal: int32): FormRenderingMode {
        return ordinal as FormRenderingMode
    }
    static FormShape_ToNumeric(value: FormShape): int32 {
        return value as int32
    }
    static FormShape_FromNumeric(ordinal: int32): FormShape {
        return ordinal as FormShape
    }
    static FunctionKey_ToNumeric(value: FunctionKey): int32 {
        return value as int32
    }
    static FunctionKey_FromNumeric(ordinal: int32): FunctionKey {
        return ordinal as FunctionKey
    }
    static GestureControl_GestureType_ToNumeric(value: GestureControl.GestureType): int32 {
        return value as int32
    }
    static GestureControl_GestureType_FromNumeric(ordinal: int32): GestureControl.GestureType {
        return ordinal as GestureControl.GestureType
    }
    static GestureJudgeResult_ToNumeric(value: GestureJudgeResult): int32 {
        return value as int32
    }
    static GestureJudgeResult_FromNumeric(ordinal: int32): GestureJudgeResult {
        return ordinal as GestureJudgeResult
    }
    static GestureMask_ToNumeric(value: GestureMask): int32 {
        return value as int32
    }
    static GestureMask_FromNumeric(ordinal: int32): GestureMask {
        return ordinal as GestureMask
    }
    static GestureMode_ToNumeric(value: GestureMode): int32 {
        return value as int32
    }
    static GestureMode_FromNumeric(ordinal: int32): GestureMode {
        return ordinal as GestureMode
    }
    static GesturePriority_ToNumeric(value: GesturePriority): int32 {
        return value as int32
    }
    static GesturePriority_FromNumeric(ordinal: int32): GesturePriority {
        return ordinal as GesturePriority
    }
    static GestureRecognizerState_ToNumeric(value: GestureRecognizerState): int32 {
        return value as int32
    }
    static GestureRecognizerState_FromNumeric(ordinal: int32): GestureRecognizerState {
        return ordinal as GestureRecognizerState
    }
    static GradientDirection_ToNumeric(value: GradientDirection): int32 {
        return value as int32
    }
    static GradientDirection_FromNumeric(ordinal: int32): GradientDirection {
        return ordinal as GradientDirection
    }
    static GridDirection_ToNumeric(value: GridDirection): int32 {
        return value as int32
    }
    static GridDirection_FromNumeric(ordinal: int32): GridDirection {
        return ordinal as GridDirection
    }
    static GridItemAlignment_ToNumeric(value: GridItemAlignment): int32 {
        return value as int32
    }
    static GridItemAlignment_FromNumeric(ordinal: int32): GridItemAlignment {
        return ordinal as GridItemAlignment
    }
    static GridItemStyle_ToNumeric(value: GridItemStyle): int32 {
        return value as int32
    }
    static GridItemStyle_FromNumeric(ordinal: int32): GridItemStyle {
        return ordinal as GridItemStyle
    }
    static GridRowDirection_ToNumeric(value: GridRowDirection): int32 {
        return value as int32
    }
    static GridRowDirection_FromNumeric(ordinal: int32): GridRowDirection {
        return ordinal as GridRowDirection
    }
    static HapticFeedbackMode_ToNumeric(value: HapticFeedbackMode): int32 {
        return value as int32
    }
    static HapticFeedbackMode_FromNumeric(ordinal: int32): HapticFeedbackMode {
        return ordinal as HapticFeedbackMode
    }
    static HeightBreakpoint_ToNumeric(value: HeightBreakpoint): int32 {
        return value as int32
    }
    static HeightBreakpoint_FromNumeric(ordinal: int32): HeightBreakpoint {
        return ordinal as HeightBreakpoint
    }
    static HitTestMode_ToNumeric(value: HitTestMode): int32 {
        return value as int32
    }
    static HitTestMode_FromNumeric(ordinal: int32): HitTestMode {
        return ordinal as HitTestMode
    }
    static HitTestType_ToNumeric(value: HitTestType): int32 {
        return value as int32
    }
    static HitTestType_FromNumeric(ordinal: int32): HitTestType {
        return ordinal as HitTestType
    }
    static HorizontalAlign_ToNumeric(value: HorizontalAlign): int32 {
        return value as int32
    }
    static HorizontalAlign_FromNumeric(ordinal: int32): HorizontalAlign {
        return ordinal as HorizontalAlign
    }
    static HoverEffect_ToNumeric(value: HoverEffect): int32 {
        return value as int32
    }
    static HoverEffect_FromNumeric(ordinal: int32): HoverEffect {
        return ordinal as HoverEffect
    }
    static HoverModeAreaType_ToNumeric(value: HoverModeAreaType): int32 {
        return value as int32
    }
    static HoverModeAreaType_FromNumeric(ordinal: int32): HoverModeAreaType {
        return ordinal as HoverModeAreaType
    }
    static IlluminatedType_ToNumeric(value: IlluminatedType): int32 {
        return value as int32
    }
    static IlluminatedType_FromNumeric(ordinal: int32): IlluminatedType {
        return ordinal as IlluminatedType
    }
    static image_ResolutionQuality_ToNumeric(value: image.ResolutionQuality): int32 {
        return value as int32
    }
    static image_ResolutionQuality_FromNumeric(ordinal: int32): image.ResolutionQuality {
        return ordinal as image.ResolutionQuality
    }
    static ImageAnalyzerType_ToNumeric(value: ImageAnalyzerType): int32 {
        return value as int32
    }
    static ImageAnalyzerType_FromNumeric(ordinal: int32): ImageAnalyzerType {
        return ordinal as ImageAnalyzerType
    }
    static ImageContent_ToNumeric(value: ImageContent): int32 {
        return value as int32
    }
    static ImageContent_FromNumeric(ordinal: int32): ImageContent {
        return ordinal as ImageContent
    }
    static ImageFit_ToNumeric(value: ImageFit): int32 {
        return value as int32
    }
    static ImageFit_FromNumeric(ordinal: int32): ImageFit {
        return ordinal as ImageFit
    }
    static ImageInterpolation_ToNumeric(value: ImageInterpolation): int32 {
        return value as int32
    }
    static ImageInterpolation_FromNumeric(ordinal: int32): ImageInterpolation {
        return ordinal as ImageInterpolation
    }
    static ImageRenderMode_ToNumeric(value: ImageRenderMode): int32 {
        return value as int32
    }
    static ImageRenderMode_FromNumeric(ordinal: int32): ImageRenderMode {
        return ordinal as ImageRenderMode
    }
    static ImageRepeat_ToNumeric(value: ImageRepeat): int32 {
        return value as int32
    }
    static ImageRepeat_FromNumeric(ordinal: int32): ImageRepeat {
        return ordinal as ImageRepeat
    }
    static ImageRotateOrientation_ToNumeric(value: ImageRotateOrientation): int32 {
        return value as int32
    }
    static ImageRotateOrientation_FromNumeric(ordinal: int32): ImageRotateOrientation {
        return ordinal as ImageRotateOrientation
    }
    static ImageSize_ToNumeric(value: ImageSize): int32 {
        return value as int32
    }
    static ImageSize_FromNumeric(ordinal: int32): ImageSize {
        return ordinal as ImageSize
    }
    static ImageSpanAlignment_ToNumeric(value: ImageSpanAlignment): int32 {
        return value as int32
    }
    static ImageSpanAlignment_FromNumeric(ordinal: int32): ImageSpanAlignment {
        return ordinal as ImageSpanAlignment
    }
    static ImmersiveMode_ToNumeric(value: ImmersiveMode): int32 {
        return value as int32
    }
    static ImmersiveMode_FromNumeric(ordinal: int32): ImmersiveMode {
        return ordinal as ImmersiveMode
    }
    static IndexerAlign_ToNumeric(value: IndexerAlign): int32 {
        return value as int32
    }
    static IndexerAlign_FromNumeric(ordinal: int32): IndexerAlign {
        return ordinal as IndexerAlign
    }
    static InputType_ToNumeric(value: InputType): int32 {
        return value as int32
    }
    static InputType_FromNumeric(ordinal: int32): InputType {
        return ordinal as InputType
    }
    static IntentionCode_ToNumeric(value: IntentionCode): int32 {
        return value as int32
    }
    static IntentionCode_FromNumeric(ordinal: int32): IntentionCode {
        return ordinal as IntentionCode
    }
    static InteractionHand_ToNumeric(value: InteractionHand): int32 {
        return value as int32
    }
    static InteractionHand_FromNumeric(ordinal: int32): InteractionHand {
        return ordinal as InteractionHand
    }
    static ItemAlign_ToNumeric(value: ItemAlign): int32 {
        return value as int32
    }
    static ItemAlign_FromNumeric(ordinal: int32): ItemAlign {
        return ordinal as ItemAlign
    }
    static ItemState_ToNumeric(value: ItemState): int32 {
        return value as int32
    }
    static ItemState_FromNumeric(ordinal: int32): ItemState {
        return ordinal as ItemState
    }
    static KeyboardAppearance_ToNumeric(value: KeyboardAppearance): int32 {
        return value as int32
    }
    static KeyboardAppearance_FromNumeric(ordinal: int32): KeyboardAppearance {
        return ordinal as KeyboardAppearance
    }
    static KeyboardAvoidMode_ToNumeric(value: KeyboardAvoidMode): int32 {
        return value as int32
    }
    static KeyboardAvoidMode_FromNumeric(ordinal: int32): KeyboardAvoidMode {
        return ordinal as KeyboardAvoidMode
    }
    static KeyProcessingMode_ToNumeric(value: KeyProcessingMode): int32 {
        return value as int32
    }
    static KeyProcessingMode_FromNumeric(ordinal: int32): KeyProcessingMode {
        return ordinal as KeyProcessingMode
    }
    static KeySource_ToNumeric(value: KeySource): int32 {
        return value as int32
    }
    static KeySource_FromNumeric(ordinal: int32): KeySource {
        return ordinal as KeySource
    }
    static KeyType_ToNumeric(value: KeyType): int32 {
        return value as int32
    }
    static KeyType_FromNumeric(ordinal: int32): KeyType {
        return ordinal as KeyType
    }
    static LaunchMode_ToNumeric(value: LaunchMode): int32 {
        return value as int32
    }
    static LaunchMode_FromNumeric(ordinal: int32): LaunchMode {
        return ordinal as LaunchMode
    }
    static LayoutDirection_ToNumeric(value: LayoutDirection): int32 {
        return value as int32
    }
    static LayoutDirection_FromNumeric(ordinal: int32): LayoutDirection {
        return ordinal as LayoutDirection
    }
    static LayoutMode_ToNumeric(value: LayoutMode): int32 {
        return value as int32
    }
    static LayoutMode_FromNumeric(ordinal: int32): LayoutMode {
        return ordinal as LayoutMode
    }
    static LayoutSafeAreaEdge_ToNumeric(value: LayoutSafeAreaEdge): int32 {
        return value as int32
    }
    static LayoutSafeAreaEdge_FromNumeric(ordinal: int32): LayoutSafeAreaEdge {
        return ordinal as LayoutSafeAreaEdge
    }
    static LayoutSafeAreaType_ToNumeric(value: LayoutSafeAreaType): int32 {
        return value as int32
    }
    static LayoutSafeAreaType_FromNumeric(ordinal: int32): LayoutSafeAreaType {
        return ordinal as LayoutSafeAreaType
    }
    static LayoutStyle_ToNumeric(value: LayoutStyle): int32 {
        return value as int32
    }
    static LayoutStyle_FromNumeric(ordinal: int32): LayoutStyle {
        return ordinal as LayoutStyle
    }
    static LengthMetricsUnit_ToNumeric(value: LengthMetricsUnit): int32 {
        return value as int32
    }
    static LengthMetricsUnit_FromNumeric(ordinal: int32): LengthMetricsUnit {
        return ordinal as LengthMetricsUnit
    }
    static LengthUnit_ToNumeric(value: LengthUnit): int32 {
        return value as int32
    }
    static LengthUnit_FromNumeric(ordinal: int32): LengthUnit {
        return ordinal as LengthUnit
    }
    static LevelMode_ToNumeric(value: LevelMode): int32 {
        return value as int32
    }
    static LevelMode_FromNumeric(ordinal: int32): LevelMode {
        return ordinal as LevelMode
    }
    static LineBreakStrategy_ToNumeric(value: LineBreakStrategy): int32 {
        return value as int32
    }
    static LineBreakStrategy_FromNumeric(ordinal: int32): LineBreakStrategy {
        return ordinal as LineBreakStrategy
    }
    static LineCapStyle_ToNumeric(value: LineCapStyle): int32 {
        return value as int32
    }
    static LineCapStyle_FromNumeric(ordinal: int32): LineCapStyle {
        return ordinal as LineCapStyle
    }
    static LineJoinStyle_ToNumeric(value: LineJoinStyle): int32 {
        return value as int32
    }
    static LineJoinStyle_FromNumeric(ordinal: int32): LineJoinStyle {
        return ordinal as LineJoinStyle
    }
    static ListItemAlign_ToNumeric(value: ListItemAlign): int32 {
        return value as int32
    }
    static ListItemAlign_FromNumeric(ordinal: int32): ListItemAlign {
        return ordinal as ListItemAlign
    }
    static ListItemGroupArea_ToNumeric(value: ListItemGroupArea): int32 {
        return value as int32
    }
    static ListItemGroupArea_FromNumeric(ordinal: int32): ListItemGroupArea {
        return ordinal as ListItemGroupArea
    }
    static ListItemGroupStyle_ToNumeric(value: ListItemGroupStyle): int32 {
        return value as int32
    }
    static ListItemGroupStyle_FromNumeric(ordinal: int32): ListItemGroupStyle {
        return ordinal as ListItemGroupStyle
    }
    static ListItemStyle_ToNumeric(value: ListItemStyle): int32 {
        return value as int32
    }
    static ListItemStyle_FromNumeric(ordinal: int32): ListItemStyle {
        return ordinal as ListItemStyle
    }
    static LoadingProgressStyle_ToNumeric(value: LoadingProgressStyle): int32 {
        return value as int32
    }
    static LoadingProgressStyle_FromNumeric(ordinal: int32): LoadingProgressStyle {
        return ordinal as LoadingProgressStyle
    }
    static LocalizedBarrierDirection_ToNumeric(value: LocalizedBarrierDirection): int32 {
        return value as int32
    }
    static LocalizedBarrierDirection_FromNumeric(ordinal: int32): LocalizedBarrierDirection {
        return ordinal as LocalizedBarrierDirection
    }
    static MarqueeStartPolicy_ToNumeric(value: MarqueeStartPolicy): int32 {
        return value as int32
    }
    static MarqueeStartPolicy_FromNumeric(ordinal: int32): MarqueeStartPolicy {
        return ordinal as MarqueeStartPolicy
    }
    static MarqueeState_ToNumeric(value: MarqueeState): int32 {
        return value as int32
    }
    static MarqueeState_FromNumeric(ordinal: int32): MarqueeState {
        return ordinal as MarqueeState
    }
    static MarqueeUpdateStrategy_ToNumeric(value: MarqueeUpdateStrategy): int32 {
        return value as int32
    }
    static MarqueeUpdateStrategy_FromNumeric(ordinal: int32): MarqueeUpdateStrategy {
        return ordinal as MarqueeUpdateStrategy
    }
    static MenuAlignType_ToNumeric(value: MenuAlignType): int32 {
        return value as int32
    }
    static MenuAlignType_FromNumeric(ordinal: int32): MenuAlignType {
        return ordinal as MenuAlignType
    }
    static MenuPolicy_ToNumeric(value: MenuPolicy): int32 {
        return value as int32
    }
    static MenuPolicy_FromNumeric(ordinal: int32): MenuPolicy {
        return ordinal as MenuPolicy
    }
    static MenuPreviewMode_ToNumeric(value: MenuPreviewMode): int32 {
        return value as int32
    }
    static MenuPreviewMode_FromNumeric(ordinal: int32): MenuPreviewMode {
        return ordinal as MenuPreviewMode
    }
    static MenuType_ToNumeric(value: MenuType): int32 {
        return value as int32
    }
    static MenuType_FromNumeric(ordinal: int32): MenuType {
        return ordinal as MenuType
    }
    static MessageLevel_ToNumeric(value: MessageLevel): int32 {
        return value as int32
    }
    static MessageLevel_FromNumeric(ordinal: int32): MessageLevel {
        return ordinal as MessageLevel
    }
    static MixedMode_ToNumeric(value: MixedMode): int32 {
        return value as int32
    }
    static MixedMode_FromNumeric(ordinal: int32): MixedMode {
        return ordinal as MixedMode
    }
    static ModalTransition_ToNumeric(value: ModalTransition): int32 {
        return value as int32
    }
    static ModalTransition_FromNumeric(ordinal: int32): ModalTransition {
        return ordinal as ModalTransition
    }
    static ModifierKey_ToNumeric(value: ModifierKey): int32 {
        return value as int32
    }
    static ModifierKey_FromNumeric(ordinal: int32): ModifierKey {
        return ordinal as ModifierKey
    }
    static MouseAction_ToNumeric(value: MouseAction): int32 {
        return value as int32
    }
    static MouseAction_FromNumeric(ordinal: int32): MouseAction {
        return ordinal as MouseAction
    }
    static MouseButton_ToNumeric(value: MouseButton): int32 {
        return value as int32
    }
    static MouseButton_FromNumeric(ordinal: int32): MouseButton {
        return ordinal as MouseButton
    }
    static NativeEmbedStatus_ToNumeric(value: NativeEmbedStatus): int32 {
        return value as int32
    }
    static NativeEmbedStatus_FromNumeric(ordinal: int32): NativeEmbedStatus {
        return ordinal as NativeEmbedStatus
    }
    static NavBarPosition_ToNumeric(value: NavBarPosition): int32 {
        return value as int32
    }
    static NavBarPosition_FromNumeric(ordinal: int32): NavBarPosition {
        return ordinal as NavBarPosition
    }
    static NavDestinationActiveReason_ToNumeric(value: NavDestinationActiveReason): int32 {
        return value as int32
    }
    static NavDestinationActiveReason_FromNumeric(ordinal: int32): NavDestinationActiveReason {
        return ordinal as NavDestinationActiveReason
    }
    static NavDestinationMode_ToNumeric(value: NavDestinationMode): int32 {
        return value as int32
    }
    static NavDestinationMode_FromNumeric(ordinal: int32): NavDestinationMode {
        return ordinal as NavDestinationMode
    }
    static NavigationMode_ToNumeric(value: NavigationMode): int32 {
        return value as int32
    }
    static NavigationMode_FromNumeric(ordinal: int32): NavigationMode {
        return ordinal as NavigationMode
    }
    static NavigationOperation_ToNumeric(value: NavigationOperation): int32 {
        return value as int32
    }
    static NavigationOperation_FromNumeric(ordinal: int32): NavigationOperation {
        return ordinal as NavigationOperation
    }
    static NavigationSystemTransitionType_ToNumeric(value: NavigationSystemTransitionType): int32 {
        return value as int32
    }
    static NavigationSystemTransitionType_FromNumeric(ordinal: int32): NavigationSystemTransitionType {
        return ordinal as NavigationSystemTransitionType
    }
    static NavigationTitleMode_ToNumeric(value: NavigationTitleMode): int32 {
        return value as int32
    }
    static NavigationTitleMode_FromNumeric(ordinal: int32): NavigationTitleMode {
        return ordinal as NavigationTitleMode
    }
    static NavigationType_ToNumeric(value: NavigationType): int32 {
        return value as int32
    }
    static NavigationType_FromNumeric(ordinal: int32): NavigationType {
        return ordinal as NavigationType
    }
    static NestedScrollMode_ToNumeric(value: NestedScrollMode): int32 {
        return value as int32
    }
    static NestedScrollMode_FromNumeric(ordinal: int32): NestedScrollMode {
        return ordinal as NestedScrollMode
    }
    static ObscuredReasons_ToNumeric(value: ObscuredReasons): int32 {
        return value as int32
    }
    static ObscuredReasons_FromNumeric(ordinal: int32): ObscuredReasons {
        return ordinal as ObscuredReasons
    }
    static OptionWidthMode_ToNumeric(value: OptionWidthMode): int32 {
        return value as int32
    }
    static OptionWidthMode_FromNumeric(ordinal: int32): OptionWidthMode {
        return ordinal as OptionWidthMode
    }
    static OutlineStyle_ToNumeric(value: OutlineStyle): int32 {
        return value as int32
    }
    static OutlineStyle_FromNumeric(ordinal: int32): OutlineStyle {
        return ordinal as OutlineStyle
    }
    static OverScrollMode_ToNumeric(value: OverScrollMode): int32 {
        return value as int32
    }
    static OverScrollMode_FromNumeric(ordinal: int32): OverScrollMode {
        return ordinal as OverScrollMode
    }
    static PageFlipMode_ToNumeric(value: PageFlipMode): int32 {
        return value as int32
    }
    static PageFlipMode_FromNumeric(ordinal: int32): PageFlipMode {
        return ordinal as PageFlipMode
    }
    static PanDirection_ToNumeric(value: PanDirection): int32 {
        return value as int32
    }
    static PanDirection_FromNumeric(ordinal: int32): PanDirection {
        return ordinal as PanDirection
    }
    static ParticleEmitterShape_ToNumeric(value: ParticleEmitterShape): int32 {
        return value as int32
    }
    static ParticleEmitterShape_FromNumeric(ordinal: int32): ParticleEmitterShape {
        return ordinal as ParticleEmitterShape
    }
    static ParticleType_ToNumeric(value: ParticleType): int32 {
        return value as int32
    }
    static ParticleType_FromNumeric(ordinal: int32): ParticleType {
        return ordinal as ParticleType
    }
    static ParticleUpdater_ToNumeric(value: ParticleUpdater): int32 {
        return value as int32
    }
    static ParticleUpdater_FromNumeric(ordinal: int32): ParticleUpdater {
        return ordinal as ParticleUpdater
    }
    static PasteButtonOnClickResult_ToNumeric(value: PasteButtonOnClickResult): int32 {
        return value as int32
    }
    static PasteButtonOnClickResult_FromNumeric(ordinal: int32): PasteButtonOnClickResult {
        return ordinal as PasteButtonOnClickResult
    }
    static PasteDescription_ToNumeric(value: PasteDescription): int32 {
        return value as int32
    }
    static PasteDescription_FromNumeric(ordinal: int32): PasteDescription {
        return ordinal as PasteDescription
    }
    static PasteIconStyle_ToNumeric(value: PasteIconStyle): int32 {
        return value as int32
    }
    static PasteIconStyle_FromNumeric(ordinal: int32): PasteIconStyle {
        return ordinal as PasteIconStyle
    }
    static PatternLockChallengeResult_ToNumeric(value: PatternLockChallengeResult): int32 {
        return value as int32
    }
    static PatternLockChallengeResult_FromNumeric(ordinal: int32): PatternLockChallengeResult {
        return ordinal as PatternLockChallengeResult
    }
    static PerfMonitorActionType_ToNumeric(value: PerfMonitorActionType): int32 {
        return value as int32
    }
    static PerfMonitorActionType_FromNumeric(ordinal: int32): PerfMonitorActionType {
        return ordinal as PerfMonitorActionType
    }
    static PerfMonitorSourceType_ToNumeric(value: PerfMonitorSourceType): int32 {
        return value as int32
    }
    static PerfMonitorSourceType_FromNumeric(ordinal: int32): PerfMonitorSourceType {
        return ordinal as PerfMonitorSourceType
    }
    static PixelRoundCalcPolicy_ToNumeric(value: PixelRoundCalcPolicy): int32 {
        return value as int32
    }
    static PixelRoundCalcPolicy_FromNumeric(ordinal: int32): PixelRoundCalcPolicy {
        return ordinal as PixelRoundCalcPolicy
    }
    static PixelRoundMode_ToNumeric(value: PixelRoundMode): int32 {
        return value as int32
    }
    static PixelRoundMode_FromNumeric(ordinal: int32): PixelRoundMode {
        return ordinal as PixelRoundMode
    }
    static Placement_ToNumeric(value: Placement): int32 {
        return value as int32
    }
    static Placement_FromNumeric(ordinal: int32): Placement {
        return ordinal as Placement
    }
    static PlaybackSpeed_ToNumeric(value: PlaybackSpeed): int32 {
        return value as int32
    }
    static PlaybackSpeed_FromNumeric(ordinal: int32): PlaybackSpeed {
        return ordinal as PlaybackSpeed
    }
    static PlayMode_ToNumeric(value: PlayMode): int32 {
        return value as int32
    }
    static PlayMode_FromNumeric(ordinal: int32): PlayMode {
        return ordinal as PlayMode
    }
    static pointer_PointerStyle_ToNumeric(value: pointer.PointerStyle): int32 {
        return value as int32
    }
    static pointer_PointerStyle_FromNumeric(ordinal: int32): pointer.PointerStyle {
        return ordinal as pointer.PointerStyle
    }
    static PreDragStatus_ToNumeric(value: PreDragStatus): int32 {
        return value as int32
    }
    static PreDragStatus_FromNumeric(ordinal: int32): PreDragStatus {
        return ordinal as PreDragStatus
    }
    static ProgressStatus_ToNumeric(value: ProgressStatus): int32 {
        return value as int32
    }
    static ProgressStatus_FromNumeric(ordinal: int32): ProgressStatus {
        return ordinal as ProgressStatus
    }
    static ProgressStyle_ToNumeric(value: ProgressStyle): int32 {
        return value as int32
    }
    static ProgressStyle_FromNumeric(ordinal: int32): ProgressStyle {
        return ordinal as ProgressStyle
    }
    static ProgressType_ToNumeric(value: ProgressType): int32 {
        return value as int32
    }
    static ProgressType_FromNumeric(ordinal: int32): ProgressType {
        return ordinal as ProgressType
    }
    static ProtectedResourceType_ToNumeric(value: ProtectedResourceType): int32 {
        return value as int32
    }
    static ProtectedResourceType_FromNumeric(ordinal: int32): ProtectedResourceType {
        return ordinal as ProtectedResourceType
    }
    static RadioIndicatorType_ToNumeric(value: RadioIndicatorType): int32 {
        return value as int32
    }
    static RadioIndicatorType_FromNumeric(ordinal: int32): RadioIndicatorType {
        return ordinal as RadioIndicatorType
    }
    static RefreshStatus_ToNumeric(value: RefreshStatus): int32 {
        return value as int32
    }
    static RefreshStatus_FromNumeric(ordinal: int32): RefreshStatus {
        return ordinal as RefreshStatus
    }
    static RelateType_ToNumeric(value: RelateType): int32 {
        return value as int32
    }
    static RelateType_FromNumeric(ordinal: int32): RelateType {
        return ordinal as RelateType
    }
    static RenderExitReason_ToNumeric(value: RenderExitReason): int32 {
        return value as int32
    }
    static RenderExitReason_FromNumeric(ordinal: int32): RenderExitReason {
        return ordinal as RenderExitReason
    }
    static RenderFit_ToNumeric(value: RenderFit): int32 {
        return value as int32
    }
    static RenderFit_FromNumeric(ordinal: int32): RenderFit {
        return ordinal as RenderFit
    }
    static RenderMode_ToNumeric(value: RenderMode): int32 {
        return value as int32
    }
    static RenderMode_FromNumeric(ordinal: int32): RenderMode {
        return ordinal as RenderMode
    }
    static RenderProcessNotRespondingReason_ToNumeric(value: RenderProcessNotRespondingReason): int32 {
        return value as int32
    }
    static RenderProcessNotRespondingReason_FromNumeric(ordinal: int32): RenderProcessNotRespondingReason {
        return ordinal as RenderProcessNotRespondingReason
    }
    static RepeatMode_ToNumeric(value: RepeatMode): int32 {
        return value as int32
    }
    static RepeatMode_FromNumeric(ordinal: int32): RepeatMode {
        return ordinal as RepeatMode
    }
    static ResponseType_ToNumeric(value: ResponseType): int32 {
        return value as int32
    }
    static ResponseType_FromNumeric(ordinal: int32): ResponseType {
        return ordinal as ResponseType
    }
    static RichEditorDeleteDirection_ToNumeric(value: RichEditorDeleteDirection): int32 {
        return value as int32
    }
    static RichEditorDeleteDirection_FromNumeric(ordinal: int32): RichEditorDeleteDirection {
        return ordinal as RichEditorDeleteDirection
    }
    static RichEditorResponseType_ToNumeric(value: RichEditorResponseType): int32 {
        return value as int32
    }
    static RichEditorResponseType_FromNumeric(ordinal: int32): RichEditorResponseType {
        return ordinal as RichEditorResponseType
    }
    static RichEditorSpanType_ToNumeric(value: RichEditorSpanType): int32 {
        return value as int32
    }
    static RichEditorSpanType_FromNumeric(ordinal: int32): RichEditorSpanType {
        return ordinal as RichEditorSpanType
    }
    static RouteType_ToNumeric(value: RouteType): int32 {
        return value as int32
    }
    static RouteType_FromNumeric(ordinal: int32): RouteType {
        return ordinal as RouteType
    }
    static SafeAreaEdge_ToNumeric(value: SafeAreaEdge): int32 {
        return value as int32
    }
    static SafeAreaEdge_FromNumeric(ordinal: int32): SafeAreaEdge {
        return ordinal as SafeAreaEdge
    }
    static SafeAreaType_ToNumeric(value: SafeAreaType): int32 {
        return value as int32
    }
    static SafeAreaType_FromNumeric(ordinal: int32): SafeAreaType {
        return ordinal as SafeAreaType
    }
    static SaveButtonOnClickResult_ToNumeric(value: SaveButtonOnClickResult): int32 {
        return value as int32
    }
    static SaveButtonOnClickResult_FromNumeric(ordinal: int32): SaveButtonOnClickResult {
        return ordinal as SaveButtonOnClickResult
    }
    static SaveDescription_ToNumeric(value: SaveDescription): int32 {
        return value as int32
    }
    static SaveDescription_FromNumeric(ordinal: int32): SaveDescription {
        return ordinal as SaveDescription
    }
    static SaveIconStyle_ToNumeric(value: SaveIconStyle): int32 {
        return value as int32
    }
    static SaveIconStyle_FromNumeric(ordinal: int32): SaveIconStyle {
        return ordinal as SaveIconStyle
    }
    static ScrollAlign_ToNumeric(value: ScrollAlign): int32 {
        return value as int32
    }
    static ScrollAlign_FromNumeric(ordinal: int32): ScrollAlign {
        return ordinal as ScrollAlign
    }
    static ScrollBarDirection_ToNumeric(value: ScrollBarDirection): int32 {
        return value as int32
    }
    static ScrollBarDirection_FromNumeric(ordinal: int32): ScrollBarDirection {
        return ordinal as ScrollBarDirection
    }
    static ScrollDirection_ToNumeric(value: ScrollDirection): int32 {
        return value as int32
    }
    static ScrollDirection_FromNumeric(ordinal: int32): ScrollDirection {
        return ordinal as ScrollDirection
    }
    static ScrollSizeMode_ToNumeric(value: ScrollSizeMode): int32 {
        return value as int32
    }
    static ScrollSizeMode_FromNumeric(ordinal: int32): ScrollSizeMode {
        return ordinal as ScrollSizeMode
    }
    static ScrollSnapAlign_ToNumeric(value: ScrollSnapAlign): int32 {
        return value as int32
    }
    static ScrollSnapAlign_FromNumeric(ordinal: int32): ScrollSnapAlign {
        return ordinal as ScrollSnapAlign
    }
    static ScrollSource_ToNumeric(value: ScrollSource): int32 {
        return value as int32
    }
    static ScrollSource_FromNumeric(ordinal: int32): ScrollSource {
        return ordinal as ScrollSource
    }
    static ScrollState_ToNumeric(value: ScrollState): int32 {
        return value as int32
    }
    static ScrollState_FromNumeric(ordinal: int32): ScrollState {
        return ordinal as ScrollState
    }
    static SearchType_ToNumeric(value: SearchType): int32 {
        return value as int32
    }
    static SearchType_FromNumeric(ordinal: int32): SearchType {
        return ordinal as SearchType
    }
    static SecurityComponentLayoutDirection_ToNumeric(value: SecurityComponentLayoutDirection): int32 {
        return value as int32
    }
    static SecurityComponentLayoutDirection_FromNumeric(ordinal: int32): SecurityComponentLayoutDirection {
        return ordinal as SecurityComponentLayoutDirection
    }
    static SeekMode_ToNumeric(value: SeekMode): int32 {
        return value as int32
    }
    static SeekMode_FromNumeric(ordinal: int32): SeekMode {
        return ordinal as SeekMode
    }
    static SelectedMode_ToNumeric(value: SelectedMode): int32 {
        return value as int32
    }
    static SelectedMode_FromNumeric(ordinal: int32): SelectedMode {
        return ordinal as SelectedMode
    }
    static SelectStatus_ToNumeric(value: SelectStatus): int32 {
        return value as int32
    }
    static SelectStatus_FromNumeric(ordinal: int32): SelectStatus {
        return ordinal as SelectStatus
    }
    static ShadowStyle_ToNumeric(value: ShadowStyle): int32 {
        return value as int32
    }
    static ShadowStyle_FromNumeric(ordinal: int32): ShadowStyle {
        return ordinal as ShadowStyle
    }
    static ShadowType_ToNumeric(value: ShadowType): int32 {
        return value as int32
    }
    static ShadowType_FromNumeric(ordinal: int32): ShadowType {
        return ordinal as ShadowType
    }
    static SharedTransitionEffectType_ToNumeric(value: SharedTransitionEffectType): int32 {
        return value as int32
    }
    static SharedTransitionEffectType_FromNumeric(ordinal: int32): SharedTransitionEffectType {
        return ordinal as SharedTransitionEffectType
    }
    static SheetKeyboardAvoidMode_ToNumeric(value: SheetKeyboardAvoidMode): int32 {
        return value as int32
    }
    static SheetKeyboardAvoidMode_FromNumeric(ordinal: int32): SheetKeyboardAvoidMode {
        return ordinal as SheetKeyboardAvoidMode
    }
    static SheetMode_ToNumeric(value: SheetMode): int32 {
        return value as int32
    }
    static SheetMode_FromNumeric(ordinal: int32): SheetMode {
        return ordinal as SheetMode
    }
    static SheetSize_ToNumeric(value: SheetSize): int32 {
        return value as int32
    }
    static SheetSize_FromNumeric(ordinal: int32): SheetSize {
        return ordinal as SheetSize
    }
    static SheetType_ToNumeric(value: SheetType): int32 {
        return value as int32
    }
    static SheetType_FromNumeric(ordinal: int32): SheetType {
        return ordinal as SheetType
    }
    static SideBarContainerType_ToNumeric(value: SideBarContainerType): int32 {
        return value as int32
    }
    static SideBarContainerType_FromNumeric(ordinal: int32): SideBarContainerType {
        return ordinal as SideBarContainerType
    }
    static SideBarPosition_ToNumeric(value: SideBarPosition): int32 {
        return value as int32
    }
    static SideBarPosition_FromNumeric(ordinal: int32): SideBarPosition {
        return ordinal as SideBarPosition
    }
    static SlideEffect_ToNumeric(value: SlideEffect): int32 {
        return value as int32
    }
    static SlideEffect_FromNumeric(ordinal: int32): SlideEffect {
        return ordinal as SlideEffect
    }
    static SliderBlockType_ToNumeric(value: SliderBlockType): int32 {
        return value as int32
    }
    static SliderBlockType_FromNumeric(ordinal: int32): SliderBlockType {
        return ordinal as SliderBlockType
    }
    static SliderChangeMode_ToNumeric(value: SliderChangeMode): int32 {
        return value as int32
    }
    static SliderChangeMode_FromNumeric(ordinal: int32): SliderChangeMode {
        return ordinal as SliderChangeMode
    }
    static SliderInteraction_ToNumeric(value: SliderInteraction): int32 {
        return value as int32
    }
    static SliderInteraction_FromNumeric(ordinal: int32): SliderInteraction {
        return ordinal as SliderInteraction
    }
    static SliderStyle_ToNumeric(value: SliderStyle): int32 {
        return value as int32
    }
    static SliderStyle_FromNumeric(ordinal: int32): SliderStyle {
        return ordinal as SliderStyle
    }
    static SourceTool_ToNumeric(value: SourceTool): int32 {
        return value as int32
    }
    static SourceTool_FromNumeric(ordinal: int32): SourceTool {
        return ordinal as SourceTool
    }
    static SourceType_ToNumeric(value: SourceType): int32 {
        return value as int32
    }
    static SourceType_FromNumeric(ordinal: int32): SourceType {
        return ordinal as SourceType
    }
    static SslError_ToNumeric(value: SslError): int32 {
        return value as int32
    }
    static SslError_FromNumeric(ordinal: int32): SslError {
        return ordinal as SslError
    }
    static StickyStyle_ToNumeric(value: StickyStyle): int32 {
        return value as int32
    }
    static StickyStyle_FromNumeric(ordinal: int32): StickyStyle {
        return ordinal as StickyStyle
    }
    static StyledStringKey_ToNumeric(value: StyledStringKey): int32 {
        return value as int32
    }
    static StyledStringKey_FromNumeric(ordinal: int32): StyledStringKey {
        return ordinal as StyledStringKey
    }
    static SubMenuExpandingMode_ToNumeric(value: SubMenuExpandingMode): int32 {
        return value as int32
    }
    static SubMenuExpandingMode_FromNumeric(ordinal: int32): SubMenuExpandingMode {
        return ordinal as SubMenuExpandingMode
    }
    static SwipeActionState_ToNumeric(value: SwipeActionState): int32 {
        return value as int32
    }
    static SwipeActionState_FromNumeric(ordinal: int32): SwipeActionState {
        return ordinal as SwipeActionState
    }
    static SwipeDirection_ToNumeric(value: SwipeDirection): int32 {
        return value as int32
    }
    static SwipeDirection_FromNumeric(ordinal: int32): SwipeDirection {
        return ordinal as SwipeDirection
    }
    static SwipeEdgeEffect_ToNumeric(value: SwipeEdgeEffect): int32 {
        return value as int32
    }
    static SwipeEdgeEffect_FromNumeric(ordinal: int32): SwipeEdgeEffect {
        return ordinal as SwipeEdgeEffect
    }
    static SwiperAnimationMode_ToNumeric(value: SwiperAnimationMode): int32 {
        return value as int32
    }
    static SwiperAnimationMode_FromNumeric(ordinal: int32): SwiperAnimationMode {
        return ordinal as SwiperAnimationMode
    }
    static SwiperDisplayMode_ToNumeric(value: SwiperDisplayMode): int32 {
        return value as int32
    }
    static SwiperDisplayMode_FromNumeric(ordinal: int32): SwiperDisplayMode {
        return ordinal as SwiperDisplayMode
    }
    static SwiperNestedScrollMode_ToNumeric(value: SwiperNestedScrollMode): int32 {
        return value as int32
    }
    static SwiperNestedScrollMode_FromNumeric(ordinal: int32): SwiperNestedScrollMode {
        return ordinal as SwiperNestedScrollMode
    }
    static SymbolEffectStrategy_ToNumeric(value: SymbolEffectStrategy): int32 {
        return value as int32
    }
    static SymbolEffectStrategy_FromNumeric(ordinal: int32): SymbolEffectStrategy {
        return ordinal as SymbolEffectStrategy
    }
    static SymbolRenderingStrategy_ToNumeric(value: SymbolRenderingStrategy): int32 {
        return value as int32
    }
    static SymbolRenderingStrategy_FromNumeric(ordinal: int32): SymbolRenderingStrategy {
        return ordinal as SymbolRenderingStrategy
    }
    static TabsCacheMode_ToNumeric(value: TabsCacheMode): int32 {
        return value as int32
    }
    static TabsCacheMode_FromNumeric(ordinal: int32): TabsCacheMode {
        return ordinal as TabsCacheMode
    }
    static text_Affinity_ToNumeric(value: text.Affinity): int32 {
        return value as int32
    }
    static text_Affinity_FromNumeric(ordinal: int32): text.Affinity {
        return ordinal as text.Affinity
    }
    static text_BreakStrategy_ToNumeric(value: text.BreakStrategy): int32 {
        return value as int32
    }
    static text_BreakStrategy_FromNumeric(ordinal: int32): text.BreakStrategy {
        return ordinal as text.BreakStrategy
    }
    static text_EllipsisMode_ToNumeric(value: text.EllipsisMode): int32 {
        return value as int32
    }
    static text_EllipsisMode_FromNumeric(ordinal: int32): text.EllipsisMode {
        return ordinal as text.EllipsisMode
    }
    static text_FontStyle_ToNumeric(value: text.FontStyle): int32 {
        return value as int32
    }
    static text_FontStyle_FromNumeric(ordinal: int32): text.FontStyle {
        return ordinal as text.FontStyle
    }
    static text_FontWeight_ToNumeric(value: text.FontWeight): int32 {
        return value as int32
    }
    static text_FontWeight_FromNumeric(ordinal: int32): text.FontWeight {
        return ordinal as text.FontWeight
    }
    static text_FontWidth_ToNumeric(value: text.FontWidth): int32 {
        return value as int32
    }
    static text_FontWidth_FromNumeric(ordinal: int32): text.FontWidth {
        return ordinal as text.FontWidth
    }
    static text_PlaceholderAlignment_ToNumeric(value: text.PlaceholderAlignment): int32 {
        return value as int32
    }
    static text_PlaceholderAlignment_FromNumeric(ordinal: int32): text.PlaceholderAlignment {
        return ordinal as text.PlaceholderAlignment
    }
    static text_RectHeightStyle_ToNumeric(value: text.RectHeightStyle): int32 {
        return value as int32
    }
    static text_RectHeightStyle_FromNumeric(ordinal: int32): text.RectHeightStyle {
        return ordinal as text.RectHeightStyle
    }
    static text_RectWidthStyle_ToNumeric(value: text.RectWidthStyle): int32 {
        return value as int32
    }
    static text_RectWidthStyle_FromNumeric(ordinal: int32): text.RectWidthStyle {
        return ordinal as text.RectWidthStyle
    }
    static text_SystemFontType_ToNumeric(value: text.SystemFontType): int32 {
        return value as int32
    }
    static text_SystemFontType_FromNumeric(ordinal: int32): text.SystemFontType {
        return ordinal as text.SystemFontType
    }
    static text_TextAlign_ToNumeric(value: text.TextAlign): int32 {
        return value as int32
    }
    static text_TextAlign_FromNumeric(ordinal: int32): text.TextAlign {
        return ordinal as text.TextAlign
    }
    static text_TextBaseline_ToNumeric(value: text.TextBaseline): int32 {
        return value as int32
    }
    static text_TextBaseline_FromNumeric(ordinal: int32): text.TextBaseline {
        return ordinal as text.TextBaseline
    }
    static text_TextDecorationStyle_ToNumeric(value: text.TextDecorationStyle): int32 {
        return value as int32
    }
    static text_TextDecorationStyle_FromNumeric(ordinal: int32): text.TextDecorationStyle {
        return ordinal as text.TextDecorationStyle
    }
    static text_TextDecorationType_ToNumeric(value: text.TextDecorationType): int32 {
        return value as int32
    }
    static text_TextDecorationType_FromNumeric(ordinal: int32): text.TextDecorationType {
        return ordinal as text.TextDecorationType
    }
    static text_TextDirection_ToNumeric(value: text.TextDirection): int32 {
        return value as int32
    }
    static text_TextDirection_FromNumeric(ordinal: int32): text.TextDirection {
        return ordinal as text.TextDirection
    }
    static text_TextHeightBehavior_ToNumeric(value: text.TextHeightBehavior): int32 {
        return value as int32
    }
    static text_TextHeightBehavior_FromNumeric(ordinal: int32): text.TextHeightBehavior {
        return ordinal as text.TextHeightBehavior
    }
    static text_WordBreak_ToNumeric(value: text.WordBreak): int32 {
        return value as int32
    }
    static text_WordBreak_FromNumeric(ordinal: int32): text.WordBreak {
        return ordinal as text.WordBreak
    }
    static TextAlign_ToNumeric(value: TextAlign): int32 {
        return value as int32
    }
    static TextAlign_FromNumeric(ordinal: int32): TextAlign {
        return ordinal as TextAlign
    }
    static TextAreaType_ToNumeric(value: TextAreaType): int32 {
        return value as int32
    }
    static TextAreaType_FromNumeric(ordinal: int32): TextAreaType {
        return ordinal as TextAreaType
    }
    static TextCase_ToNumeric(value: TextCase): int32 {
        return value as int32
    }
    static TextCase_FromNumeric(ordinal: int32): TextCase {
        return ordinal as TextCase
    }
    static TextContentStyle_ToNumeric(value: TextContentStyle): int32 {
        return value as int32
    }
    static TextContentStyle_FromNumeric(ordinal: int32): TextContentStyle {
        return ordinal as TextContentStyle
    }
    static TextDataDetectorType_ToNumeric(value: TextDataDetectorType): int32 {
        return value as int32
    }
    static TextDataDetectorType_FromNumeric(ordinal: int32): TextDataDetectorType {
        return ordinal as TextDataDetectorType
    }
    static TextDecorationStyle_ToNumeric(value: TextDecorationStyle): int32 {
        return value as int32
    }
    static TextDecorationStyle_FromNumeric(ordinal: int32): TextDecorationStyle {
        return ordinal as TextDecorationStyle
    }
    static TextDecorationType_ToNumeric(value: TextDecorationType): int32 {
        return value as int32
    }
    static TextDecorationType_FromNumeric(ordinal: int32): TextDecorationType {
        return ordinal as TextDecorationType
    }
    static TextDeleteDirection_ToNumeric(value: TextDeleteDirection): int32 {
        return value as int32
    }
    static TextDeleteDirection_FromNumeric(ordinal: int32): TextDeleteDirection {
        return ordinal as TextDeleteDirection
    }
    static TextHeightAdaptivePolicy_ToNumeric(value: TextHeightAdaptivePolicy): int32 {
        return value as int32
    }
    static TextHeightAdaptivePolicy_FromNumeric(ordinal: int32): TextHeightAdaptivePolicy {
        return ordinal as TextHeightAdaptivePolicy
    }
    static TextInputStyle_ToNumeric(value: TextInputStyle): int32 {
        return value as int32
    }
    static TextInputStyle_FromNumeric(ordinal: int32): TextInputStyle {
        return ordinal as TextInputStyle
    }
    static TextMenuShowMode_ToNumeric(value: TextMenuShowMode): int32 {
        return value as int32
    }
    static TextMenuShowMode_FromNumeric(ordinal: int32): TextMenuShowMode {
        return ordinal as TextMenuShowMode
    }
    static TextOverflow_ToNumeric(value: TextOverflow): int32 {
        return value as int32
    }
    static TextOverflow_FromNumeric(ordinal: int32): TextOverflow {
        return ordinal as TextOverflow
    }
    static TextResponseType_ToNumeric(value: TextResponseType): int32 {
        return value as int32
    }
    static TextResponseType_FromNumeric(ordinal: int32): TextResponseType {
        return ordinal as TextResponseType
    }
    static TextSelectableMode_ToNumeric(value: TextSelectableMode): int32 {
        return value as int32
    }
    static TextSelectableMode_FromNumeric(ordinal: int32): TextSelectableMode {
        return ordinal as TextSelectableMode
    }
    static TextSpanType_ToNumeric(value: TextSpanType): int32 {
        return value as int32
    }
    static TextSpanType_FromNumeric(ordinal: int32): TextSpanType {
        return ordinal as TextSpanType
    }
    static ThemeColorMode_ToNumeric(value: ThemeColorMode): int32 {
        return value as int32
    }
    static ThemeColorMode_FromNumeric(ordinal: int32): ThemeColorMode {
        return ordinal as ThemeColorMode
    }
    static ThreatType_ToNumeric(value: ThreatType): int32 {
        return value as int32
    }
    static ThreatType_FromNumeric(ordinal: int32): ThreatType {
        return ordinal as ThreatType
    }
    static TimePickerFormat_ToNumeric(value: TimePickerFormat): int32 {
        return value as int32
    }
    static TimePickerFormat_FromNumeric(ordinal: int32): TimePickerFormat {
        return ordinal as TimePickerFormat
    }
    static TitleHeight_ToNumeric(value: TitleHeight): int32 {
        return value as int32
    }
    static TitleHeight_FromNumeric(ordinal: int32): TitleHeight {
        return ordinal as TitleHeight
    }
    static ToggleType_ToNumeric(value: ToggleType): int32 {
        return value as int32
    }
    static ToggleType_FromNumeric(ordinal: int32): ToggleType {
        return ordinal as ToggleType
    }
    static ToolbarItemStatus_ToNumeric(value: ToolbarItemStatus): int32 {
        return value as int32
    }
    static ToolbarItemStatus_FromNumeric(ordinal: int32): ToolbarItemStatus {
        return ordinal as ToolbarItemStatus
    }
    static TouchTestStrategy_ToNumeric(value: TouchTestStrategy): int32 {
        return value as int32
    }
    static TouchTestStrategy_FromNumeric(ordinal: int32): TouchTestStrategy {
        return ordinal as TouchTestStrategy
    }
    static TouchType_ToNumeric(value: TouchType): int32 {
        return value as int32
    }
    static TouchType_FromNumeric(ordinal: int32): TouchType {
        return ordinal as TouchType
    }
    static TransitionEdge_ToNumeric(value: TransitionEdge): int32 {
        return value as int32
    }
    static TransitionEdge_FromNumeric(ordinal: int32): TransitionEdge {
        return ordinal as TransitionEdge
    }
    static TransitionHierarchyStrategy_ToNumeric(value: TransitionHierarchyStrategy): int32 {
        return value as int32
    }
    static TransitionHierarchyStrategy_FromNumeric(ordinal: int32): TransitionHierarchyStrategy {
        return ordinal as TransitionHierarchyStrategy
    }
    static TransitionType_ToNumeric(value: TransitionType): int32 {
        return value as int32
    }
    static TransitionType_FromNumeric(ordinal: int32): TransitionType {
        return ordinal as TransitionType
    }
    static uniformTypeDescriptor_UniformDataType_ToNumeric(value: uniformTypeDescriptor.UniformDataType): int32 {
        return value as int32
    }
    static uniformTypeDescriptor_UniformDataType_FromNumeric(ordinal: int32): uniformTypeDescriptor.UniformDataType {
        return ordinal as uniformTypeDescriptor.UniformDataType
    }
    static VerticalAlign_ToNumeric(value: VerticalAlign): int32 {
        return value as int32
    }
    static VerticalAlign_FromNumeric(ordinal: int32): VerticalAlign {
        return ordinal as VerticalAlign
    }
    static ViewportFit_ToNumeric(value: ViewportFit): int32 {
        return value as int32
    }
    static ViewportFit_FromNumeric(ordinal: int32): ViewportFit {
        return ordinal as ViewportFit
    }
    static Visibility_ToNumeric(value: Visibility): int32 {
        return value as int32
    }
    static Visibility_FromNumeric(ordinal: int32): Visibility {
        return ordinal as Visibility
    }
    static WaterFlowLayoutMode_ToNumeric(value: WaterFlowLayoutMode): int32 {
        return value as int32
    }
    static WaterFlowLayoutMode_FromNumeric(ordinal: int32): WaterFlowLayoutMode {
        return ordinal as WaterFlowLayoutMode
    }
    static WebCaptureMode_ToNumeric(value: WebCaptureMode): int32 {
        return value as int32
    }
    static WebCaptureMode_FromNumeric(ordinal: int32): WebCaptureMode {
        return ordinal as WebCaptureMode
    }
    static WebDarkMode_ToNumeric(value: WebDarkMode): int32 {
        return value as int32
    }
    static WebDarkMode_FromNumeric(ordinal: int32): WebDarkMode {
        return ordinal as WebDarkMode
    }
    static WebElementType_ToNumeric(value: WebElementType): int32 {
        return value as int32
    }
    static WebElementType_FromNumeric(ordinal: int32): WebElementType {
        return ordinal as WebElementType
    }
    static WebKeyboardAvoidMode_ToNumeric(value: WebKeyboardAvoidMode): int32 {
        return value as int32
    }
    static WebKeyboardAvoidMode_FromNumeric(ordinal: int32): WebKeyboardAvoidMode {
        return ordinal as WebKeyboardAvoidMode
    }
    static WebLayoutMode_ToNumeric(value: WebLayoutMode): int32 {
        return value as int32
    }
    static WebLayoutMode_FromNumeric(ordinal: int32): WebLayoutMode {
        return ordinal as WebLayoutMode
    }
    static WebNavigationType_ToNumeric(value: WebNavigationType): int32 {
        return value as int32
    }
    static WebNavigationType_FromNumeric(ordinal: int32): WebNavigationType {
        return ordinal as WebNavigationType
    }
    static WebResponseType_ToNumeric(value: WebResponseType): int32 {
        return value as int32
    }
    static WebResponseType_FromNumeric(ordinal: int32): WebResponseType {
        return ordinal as WebResponseType
    }
    static Week_ToNumeric(value: Week): int32 {
        return value as int32
    }
    static Week_FromNumeric(ordinal: int32): Week {
        return ordinal as Week
    }
    static WidthBreakpoint_ToNumeric(value: WidthBreakpoint): int32 {
        return value as int32
    }
    static WidthBreakpoint_FromNumeric(ordinal: int32): WidthBreakpoint {
        return ordinal as WidthBreakpoint
    }
    static window_WindowStatusType_ToNumeric(value: window.WindowStatusType): int32 {
        return value as int32
    }
    static window_WindowStatusType_FromNumeric(ordinal: int32): window.WindowStatusType {
        return ordinal as window.WindowStatusType
    }
    static WindowModeFollowStrategy_ToNumeric(value: WindowModeFollowStrategy): int32 {
        return value as int32
    }
    static WindowModeFollowStrategy_FromNumeric(ordinal: int32): WindowModeFollowStrategy {
        return ordinal as WindowModeFollowStrategy
    }
    static WordBreak_ToNumeric(value: WordBreak): int32 {
        return value as int32
    }
    static WordBreak_FromNumeric(ordinal: int32): WordBreak {
        return ordinal as WordBreak
    }
    static XComponentType_ToNumeric(value: XComponentType): int32 {
        return value as int32
    }
    static XComponentType_FromNumeric(ordinal: int32): XComponentType {
        return ordinal as XComponentType
    }
    static isArray_Number(value: Object | string | number | undefined): boolean {
        return Array.isArray(value)
    }
    static isArray_common2D_Point(value: Object | string | number | undefined): boolean {
        return Array.isArray(value)
    }
    static isArray_common2D_Rect(value: Object | string | number | undefined): boolean {
        return Array.isArray(value)
    }
    static isArray_drawing_RectType(value: Object | string | number | undefined): boolean {
        return Array.isArray(value)
    }
    static isArray_CustomObject(value: Object | string | number | undefined): boolean {
        return Array.isArray(value)
    }
    static isArray_drawing_TextBlobRunBuffer(value: Object | string | number | undefined): boolean {
        return Array.isArray(value)
    }
    static isArray_String(value: Object | string | number | undefined): boolean {
        return Array.isArray(value)
    }
    static isArray_SourceTool(value: Object | string | number | undefined): boolean {
        return Array.isArray(value)
    }
    static isArray_GestureType(value: Object | string | number | undefined): boolean {
        return Array.isArray(value)
    }
    static isArray_ImageAnalyzerType(value: Object | string | number | undefined): boolean {
        return Array.isArray(value)
    }
    static isArray_Layoutable(value: Object | string | number | undefined): boolean {
        return Array.isArray(value)
    }
    static isArray_Measurable(value: Object | string | number | undefined): boolean {
        return Array.isArray(value)
    }
    static isArray_ColorStop(value: Object | string | number | undefined): boolean {
        return Array.isArray(value)
    }
    static isArray_Opt_Object(value: Object | string | number | undefined): boolean {
        return Array.isArray(value)
    }
    static isArray_NavPathInfo(value: Object | string | number | undefined): boolean {
        return Array.isArray(value)
    }
    static isArray_Union_Number_String(value: Object | string | number | undefined): boolean {
        return Array.isArray(value)
    }
    static isArray_Union_RichEditorImageSpanResult_RichEditorTextSpanResult(value: Object | string | number | undefined): boolean {
        return Array.isArray(value)
    }
    static isArray_RichEditorParagraphResult(value: Object | string | number | undefined): boolean {
        return Array.isArray(value)
    }
    static isArray_RichEditorSpan(value: Object | string | number | undefined): boolean {
        return Array.isArray(value)
    }
    static isArray_StyleOptions(value: Object | string | number | undefined): boolean {
        return Array.isArray(value)
    }
    static isArray_SpanStyle(value: Object | string | number | undefined): boolean {
        return Array.isArray(value)
    }
    static isArray_text_TextBox(value: Object | string | number | undefined): boolean {
        return Array.isArray(value)
    }
    static isArray_text_TextLine(value: Object | string | number | undefined): boolean {
        return Array.isArray(value)
    }
    static isArray_text_LineMetrics(value: Object | string | number | undefined): boolean {
        return Array.isArray(value)
    }
    static isArray_text_Run(value: Object | string | number | undefined): boolean {
        return Array.isArray(value)
    }
    static isArray_SectionOptions(value: Object | string | number | undefined): boolean {
        return Array.isArray(value)
    }
    static isArray_Header(value: Object | string | number | undefined): boolean {
        return Array.isArray(value)
    }
    static isArray_webview_WebHeader(value: Object | string | number | undefined): boolean {
        return Array.isArray(value)
    }
    static isArray_TextMenuItem(value: Object | string | number | undefined): boolean {
        return Array.isArray(value)
    }
    static isArray_TouchTestInfo(value: Object | string | number | undefined): boolean {
        return Array.isArray(value)
    }
    static isArray_NavDestinationTransition(value: Object | string | number | undefined): boolean {
        return Array.isArray(value)
    }
    static isArray_ResourceStr(value: Object | string | number | undefined): boolean {
        return Array.isArray(value)
    }
    static isArray_GestureRecognizer(value: Object | string | number | undefined): boolean {
        return Array.isArray(value)
    }
    static isArray_font_UIFontGenericInfo(value: Object | string | number | undefined): boolean {
        return Array.isArray(value)
    }
    static isArray_font_UIFontFallbackGroupInfo(value: Object | string | number | undefined): boolean {
        return Array.isArray(value)
    }
    static isArray_font_UIFontFallbackInfo(value: Object | string | number | undefined): boolean {
        return Array.isArray(value)
    }
    static isArray_font_UIFontAliasInfo(value: Object | string | number | undefined): boolean {
        return Array.isArray(value)
    }
    static isArray_font_UIFontAdjustInfo(value: Object | string | number | undefined): boolean {
        return Array.isArray(value)
    }
    static isArray_FractionStop(value: Object | string | number | undefined): boolean {
        return Array.isArray(value)
    }
    static isArray_Tuple_ResourceColor_Number(value: Object | string | number | undefined): boolean {
        return Array.isArray(value)
    }
    static isArray_CalendarDay(value: Object | string | number | undefined): boolean {
        return Array.isArray(value)
    }
    static isArray_Buffer(value: Object | string | number | undefined): boolean {
        return Array.isArray(value)
    }
    static isArray_Object(value: Object | string | number | undefined): boolean {
        return Array.isArray(value)
    }
    static isArray_Union_RichEditorTextSpanResult_RichEditorImageSpanResult(value: Object | string | number | undefined): boolean {
        return Array.isArray(value)
    }
    static isArray_ShadowOptions(value: Object | string | number | undefined): boolean {
        return Array.isArray(value)
    }
    static isArray_DateRange(value: Object | string | number | undefined): boolean {
        return Array.isArray(value)
    }
    static isArray_Union_ResourceColor_LinearGradient(value: Object | string | number | undefined): boolean {
        return Array.isArray(value)
    }
    static isArray_DragPreviewMode(value: Object | string | number | undefined): boolean {
        return Array.isArray(value)
    }
    static isArray_RichEditorTextSpanResult(value: Object | string | number | undefined): boolean {
        return Array.isArray(value)
    }
    static isArray_RichEditorImageSpanResult(value: Object | string | number | undefined): boolean {
        return Array.isArray(value)
    }
    static isArray_ResourceColor(value: Object | string | number | undefined): boolean {
        return Array.isArray(value)
    }
    static isArray_TextCascadePickerRangeContent(value: Object | string | number | undefined): boolean {
        return Array.isArray(value)
    }
    static isArray_Array_String(value: Object | string | number | undefined): boolean {
        return Array.isArray(value)
    }
    static isArray_TextPickerRangeContent(value: Object | string | number | undefined): boolean {
        return Array.isArray(value)
    }
    static isArray_LengthMetrics(value: Object | string | number | undefined): boolean {
        return Array.isArray(value)
    }
    static isArray_RadiusItem(value: Object | string | number | undefined): boolean {
        return Array.isArray(value)
    }
    static isArray_Dimension(value: Object | string | number | undefined): boolean {
        return Array.isArray(value)
    }
    static isArray_text_FontFeature(value: Object | string | number | undefined): boolean {
        return Array.isArray(value)
    }
    static isArray_text_TextShadow(value: Object | string | number | undefined): boolean {
        return Array.isArray(value)
    }
    static isArray_text_FontVariation(value: Object | string | number | undefined): boolean {
        return Array.isArray(value)
    }
    static isArray_TextDataDetectorType(value: Object | string | number | undefined): boolean {
        return Array.isArray(value)
    }
    static isArray_FingerInfo(value: Object | string | number | undefined): boolean {
        return Array.isArray(value)
    }
    static isArray_MouseButton(value: Object | string | number | undefined): boolean {
        return Array.isArray(value)
    }
    static isArray_TouchObject(value: Object | string | number | undefined): boolean {
        return Array.isArray(value)
    }
    static isArray_HistoricalPoint(value: Object | string | number | undefined): boolean {
        return Array.isArray(value)
    }
    static isArray_text_FontDescriptor(value: Object | string | number | undefined): boolean {
        return Array.isArray(value)
    }
    static isArray_SheetInfo(value: Object | string | number | undefined): boolean {
        return Array.isArray(value)
    }
    static isArray_AlertDialogButtonOptions(value: Object | string | number | undefined): boolean {
        return Array.isArray(value)
    }
    static isArray_Rectangle(value: Object | string | number | undefined): boolean {
        return Array.isArray(value)
    }
    static isArray_uniformTypeDescriptor_UniformDataType(value: Object | string | number | undefined): boolean {
        return Array.isArray(value)
    }
    static isArray_ObscuredReasons(value: Object | string | number | undefined): boolean {
        return Array.isArray(value)
    }
    static isArray_SafeAreaType(value: Object | string | number | undefined): boolean {
        return Array.isArray(value)
    }
    static isArray_SafeAreaEdge(value: Object | string | number | undefined): boolean {
        return Array.isArray(value)
    }
    static isArray_MenuElement(value: Object | string | number | undefined): boolean {
        return Array.isArray(value)
    }
    static isArray_ModifierKey(value: Object | string | number | undefined): boolean {
        return Array.isArray(value)
    }
    static isArray_Length(value: Object | string | number | undefined): boolean {
        return Array.isArray(value)
    }
    static isArray_Tuple_Union_ResourceColor_LinearGradient_Number(value: Object | string | number | undefined): boolean {
        return Array.isArray(value)
    }
    static isArray_ImageFrameInfo(value: Object | string | number | undefined): boolean {
        return Array.isArray(value)
    }
    static isArray_NavigationMenuItem(value: Object | string | number | undefined): boolean {
        return Array.isArray(value)
    }
    static isArray_Scroller(value: Object | string | number | undefined): boolean {
        return Array.isArray(value)
    }
    static isArray_NestedScrollInfo(value: Object | string | number | undefined): boolean {
        return Array.isArray(value)
    }
    static isArray_ToolbarItem(value: Object | string | number | undefined): boolean {
        return Array.isArray(value)
    }
    static isArray_LayoutSafeAreaType(value: Object | string | number | undefined): boolean {
        return Array.isArray(value)
    }
    static isArray_LayoutSafeAreaEdge(value: Object | string | number | undefined): boolean {
        return Array.isArray(value)
    }
    static isArray_ParticlePropertyAnimation(value: Object | string | number | undefined): boolean {
        return Array.isArray(value)
    }
    static isArray_ShapePoint(value: Object | string | number | undefined): boolean {
        return Array.isArray(value)
    }
    static isArray_GuideLineStyle(value: Object | string | number | undefined): boolean {
        return Array.isArray(value)
    }
    static isArray_BarrierStyle(value: Object | string | number | undefined): boolean {
        return Array.isArray(value)
    }
    static isArray_ScriptItem(value: Object | string | number | undefined): boolean {
        return Array.isArray(value)
    }
}
