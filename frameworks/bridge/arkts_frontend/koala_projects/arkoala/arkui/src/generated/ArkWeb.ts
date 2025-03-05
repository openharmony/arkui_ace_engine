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

import { int32, float32, unsafeCast } from "@koalaui/common"
import { KStringPtr, KBoolean, RuntimeType, runtimeType, isResource, isInstanceOf } from "@koalaui/interop"
import { NodeAttach, remember } from "@koalaui/runtime"
import { ComponentBase } from "./../ComponentBase"
import { ArkCommonMethodComponent } from "./ArkCommon"
import { ArkWebPeer } from "./peers/ArkWebPeer"
import { UseEventsProperties } from "./use_properties"
import { CommonMethod, Rectangle, PixelRoundPolicy, BackgroundEffectOptions, ForegroundEffectOptions, VisualEffect, Filter, BorderImageOption, OutlineStyle, AccessibilityCallback, AnimateParam, TransitionOptions, MotionBlurOptions, InvertOptions, TranslateOptions, ScaleOptions, RotateOptions, AlignRuleOption, LocalizedAlignRuleOptions, ClickEffect, UniformDataType, CustomBuilder, DragItemInfo, MotionPathOptions, ShadowOptions, ShadowStyle, StateStyles, PixelStretchEffectOptions, BackgroundBrightnessOptions, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, SizeChangeCallback, SafeAreaType, SafeAreaEdge, BlurStyle, BackgroundBlurStyleOptions, ForegroundBlurStyleOptions, TransitionFinishCallback, BlurOptions, LinearGradientBlurOptions, EffectType, sharedTransitionOptions, ChainStyle, DragPreviewOptions, DragInteractionOptions, ComponentContent, OverlayOptions, BlendMode, BlendApplyType, Blender, GeometryTransitionOptions, PopupOptions, CustomPopupOptions, MenuElement, MenuOptions, ContextMenuOptions, ModalTransition, ContentCoverOptions, SheetOptions, VisibleAreaChangeCallback, DrawContext, TouchTestInfo, TouchResult, AdaptiveColor, BlurStyleActivePolicy, RepeatMode, LinearGradient_common, FinishCallbackType, ExpectedFrameRateRange, TransitionEffects, TransitionEdge, MotionBlurAnchor, LocalizedHorizontalAlignParam, LocalizedVerticalAlignParam, PreDragStatus, ShadowType, UIGestureEvent, BlurStyleOptions, ThemeColorMode, FractionStop, DragPreviewMode, ImageModifier, OverlayOffset, TransitionHierarchyStrategy, PopupMessageOptions, SymbolGlyphModifier, MenuPreviewMode, ContextMenuAnimationOptions, BindOptions, SheetSize, SheetType, SheetTitleOptions, SheetMode, ScrollSizeMode, UIContext, SheetKeyboardAvoidMode, SourceTool, RectResult, TouchTestStrategy, EventTarget, SourceType, TouchObject, HistoricalPoint, IntentionCode, DragBehavior, Summary, DragResult, DismissPopupAction, DismissContentCoverAction, SheetDismiss, DismissSheetAction, SpringBackAction, DismissReason, NestedScrollOptions } from "./ArkCommonInterfaces"
import { Length, SizeOptions, ConstraintSizeOptions, ChainWeightOptions, Padding, LocalizedPadding, Margin, LocalizedMargin, ResourceColor, Position, BorderOptions, EdgeStyles, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, Dimension, EdgeOutlineWidths, OutlineRadiuses, Edges, LocalizedEdges, LocalizedPosition, ResourceStr, AccessibilityOptions, PX, VP, FP, LPX, Percentage, ColorMetrics, Area, Bias, Font } from "./ArkUnitsInterfaces"
import { DrawModifier } from "./ArkDrawModifierMaterialized"
import { HitTestMode, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Color, Visibility, ItemAlign, Direction, GradientDirection, ObscuredReasons, RenderFit, ImageRepeat, Axis, ResponseType, FunctionKey, ModifierKey, PixelRoundCalcPolicy, Curve, PlayMode, TransitionType, HorizontalAlign, VerticalAlign, ClickEffectLevel, SharedTransitionEffectType, Placement, ArrowPointPosition, MouseButton, MouseAction, TouchType, KeyType, KeySource, FontWeight, FontStyle, CopyOptions, NestedScrollMode } from "./ArkEnumsInterfaces"
import { LengthMetrics } from "./ArkLengthMetricsMaterialized"
import { ResizableOptions, DrawingLattice } from "./ArkImageInterfaces"
import { Resource } from "./ArkResourceInterfaces"
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
import { GestureType, GestureMask, TapGestureInterface, LongPressGestureInterface, PanGestureInterface, PinchGestureInterface, SwipeGestureInterface, RotationGestureInterface, GestureGroupInterface, GestureInfo, GestureJudgeResult, GestureInterface, TapGestureParameters, PanDirection, SwipeDirection, GestureMode, GestureHandler, GesturePriority, FingerInfo } from "./ArkGestureInterfaces"
import { LengthUnit, ShapeSize, PathShapeOptions, RectShapeOptions, RoundRectShapeOptions, WebHeader } from "./ArkArkuiExternalInterfaces"
import { ClickEvent } from "./ArkClickEventMaterialized"
import { HoverEvent } from "./ArkHoverEventMaterialized"
import { MouseEvent } from "./ArkMouseEventMaterialized"
import { TouchEvent } from "./ArkTouchEventMaterialized"
import { KeyEvent } from "./ArkKeyEventMaterialized"
import { ICurve } from "./ArkICurveMaterialized"
import { DragEvent } from "./ArkDragEventMaterialized"
import { BaseGestureEvent } from "./ArkBaseGestureEventMaterialized"
import { PanGestureOptions } from "./ArkPanGestureOptionsMaterialized"
import { BaseEvent } from "./ArkBaseEventMaterialized"
import { UnifiedData } from "./ArkUnifiedDataMaterialized"
import { GestureControl } from "./ArkGestureControlNamespace"
import { GestureEvent } from "./ArkGestureEventMaterialized"
import { MixedMode, JavaScriptProxy, CacheMode, WebDarkMode, WebMediaOptions, OverScrollMode, OnFullScreenEnterCallback, OnContextMenuHideCallback, OnSslErrorEventCallback, OnFirstMeaningfulPaintCallback, OnLargestContentfulPaintCallback, OnSafeBrowsingCheckResultCallback, OnNavigationEntryCommittedCallback, OnIntelligentTrackingPreventionCallback, ScriptItem, WebLayoutMode, NestedScrollOptionsExt, OnNativeEmbedVisibilityChangeCallback, OnOverrideUrlLoadingCallback, NativeMediaPlayerConfig, OnRenderProcessNotRespondingCallback, OnRenderProcessRespondingCallback, ExpandedMenuItemOptions, OnViewportFitChangedCallback, WebKeyboardCallback, OnAdsBlockedCallback, WebKeyboardAvoidMode, WebAttribute, WebElementType, WebResponseType, SelectionMenuOptionsExt, OnPageEndEvent, OnPageBeginEvent, OnProgressChangeEvent, OnTitleReceiveEvent, OnGeolocationShowEvent, OnAlertEvent, OnBeforeUnloadEvent, OnConfirmEvent, OnPromptEvent, OnConsoleEvent, OnErrorReceiveEvent, OnHttpErrorReceiveEvent, OnDownloadStartEvent, OnRefreshAccessedHistoryEvent, OnRenderExitedEvent, OnShowFileSelectorEvent, OnResourceLoadEvent, OnScaleChangeEvent, OnHttpAuthRequestEvent, OnInterceptRequestEvent, OnPermissionRequestEvent, OnScreenCaptureRequestEvent, OnContextMenuShowEvent, OnSearchResultReceiveEvent, OnScrollEvent, OnSslErrorEventReceiveEvent, OnClientAuthenticationEvent, OnWindowNewEvent, OnTouchIconUrlReceivedEvent, OnFaviconReceivedEvent, OnPageVisibleEvent, OnDataResubmittedEvent, OnAudioStateChangedEvent, OnFirstContentfulPaintEvent, OnLoadInterceptEvent, OnOverScrollEvent, NativeEmbedDataInfo, NativeEmbedTouchInfo, Header, HitTestType, RenderExitReason, SslError, NativeEmbedStatus, NativeEmbedInfo, MessageLevel, FileSelectorMode, ScreenCaptureConfig, ContextMenuMediaType, ContextMenuSourceType, ContextMenuInputFieldType, WebCaptureMode, WebOptions, RenderMode } from "./ArkWebInterfaces"
import { EditMenuOptions } from "./ArkEditMenuOptionsMaterialized"
import { WebController } from "./ArkWebControllerMaterialized"
import { WebviewController } from "./ArkWebviewControllerMaterialized"
import { WebResourceRequest } from "./ArkWebResourceRequestMaterialized"
import { WebResourceResponse } from "./ArkWebResourceResponseMaterialized"
import { TextMenuItem, TextRange, MenuType } from "./ArkTextCommonInterfaces"
import { WebCookie } from "./ArkWebCookieMaterialized"
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
import { SslErrorHandler } from "./ArkSslErrorHandlerMaterialized"
import { ClientAuthenticationHandler } from "./ArkClientAuthenticationHandlerMaterialized"
import { ControllerHandler } from "./ArkControllerHandlerMaterialized"
import { DataResubmissionHandler } from "./ArkDataResubmissionHandlerMaterialized"
import { EventResult } from "./ArkEventResultMaterialized"
import { TextMenuItemId } from "./ArkTextMenuItemIdMaterialized"
/** @memo:stable */
export class ArkWebComponent extends ArkCommonMethodComponent {
    getPeer(): ArkWebPeer {
        return (this.peer as ArkWebPeer)
    }
    /** @memo */
    public setWebOptions(value: WebOptions): this {
        if (this.checkPriority("setWebOptions")) {
            const value_casted = value as (WebOptions)
            this.getPeer()?.setWebOptionsAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public javaScriptAccess(value: boolean): this {
        if (this.checkPriority("javaScriptAccess")) {
            const value_casted = value as (boolean)
            this.getPeer()?.javaScriptAccessAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public fileAccess(value: boolean): this {
        if (this.checkPriority("fileAccess")) {
            const value_casted = value as (boolean)
            this.getPeer()?.fileAccessAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onlineImageAccess(value: boolean): this {
        if (this.checkPriority("onlineImageAccess")) {
            const value_casted = value as (boolean)
            this.getPeer()?.onlineImageAccessAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public domStorageAccess(value: boolean): this {
        if (this.checkPriority("domStorageAccess")) {
            const value_casted = value as (boolean)
            this.getPeer()?.domStorageAccessAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public imageAccess(value: boolean): this {
        if (this.checkPriority("imageAccess")) {
            const value_casted = value as (boolean)
            this.getPeer()?.imageAccessAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public mixedMode(value: MixedMode): this {
        if (this.checkPriority("mixedMode")) {
            const value_casted = value as (MixedMode)
            this.getPeer()?.mixedModeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public zoomAccess(value: boolean): this {
        if (this.checkPriority("zoomAccess")) {
            const value_casted = value as (boolean)
            this.getPeer()?.zoomAccessAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public geolocationAccess(value: boolean): this {
        if (this.checkPriority("geolocationAccess")) {
            const value_casted = value as (boolean)
            this.getPeer()?.geolocationAccessAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public javaScriptProxy(value: JavaScriptProxy): this {
        if (this.checkPriority("javaScriptProxy")) {
            const value_casted = value as (JavaScriptProxy)
            this.getPeer()?.javaScriptProxyAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public password(value: boolean): this {
        if (this.checkPriority("password")) {
            const value_casted = value as (boolean)
            this.getPeer()?.passwordAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public cacheMode(value: CacheMode): this {
        if (this.checkPriority("cacheMode")) {
            const value_casted = value as (CacheMode)
            this.getPeer()?.cacheModeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public darkMode(value: WebDarkMode): this {
        if (this.checkPriority("darkMode")) {
            const value_casted = value as (WebDarkMode)
            this.getPeer()?.darkModeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public forceDarkAccess(value: boolean): this {
        if (this.checkPriority("forceDarkAccess")) {
            const value_casted = value as (boolean)
            this.getPeer()?.forceDarkAccessAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public mediaOptions(value: WebMediaOptions): this {
        if (this.checkPriority("mediaOptions")) {
            const value_casted = value as (WebMediaOptions)
            this.getPeer()?.mediaOptionsAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public tableData(value: boolean): this {
        if (this.checkPriority("tableData")) {
            const value_casted = value as (boolean)
            this.getPeer()?.tableDataAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public wideViewModeAccess(value: boolean): this {
        if (this.checkPriority("wideViewModeAccess")) {
            const value_casted = value as (boolean)
            this.getPeer()?.wideViewModeAccessAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public overviewModeAccess(value: boolean): this {
        if (this.checkPriority("overviewModeAccess")) {
            const value_casted = value as (boolean)
            this.getPeer()?.overviewModeAccessAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public overScrollMode(value: OverScrollMode): this {
        if (this.checkPriority("overScrollMode")) {
            const value_casted = value as (OverScrollMode)
            this.getPeer()?.overScrollModeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public textZoomAtio(value: number): this {
        if (this.checkPriority("textZoomAtio")) {
            const value_casted = value as (number)
            this.getPeer()?.textZoomAtioAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public textZoomRatio(value: number): this {
        if (this.checkPriority("textZoomRatio")) {
            const value_casted = value as (number)
            this.getPeer()?.textZoomRatioAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public databaseAccess(value: boolean): this {
        if (this.checkPriority("databaseAccess")) {
            const value_casted = value as (boolean)
            this.getPeer()?.databaseAccessAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public initialScale(value: number): this {
        if (this.checkPriority("initialScale")) {
            const value_casted = value as (number)
            this.getPeer()?.initialScaleAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public userAgent(value: string): this {
        if (this.checkPriority("userAgent")) {
            const value_casted = value as (string)
            this.getPeer()?.userAgentAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public metaViewport(value: boolean): this {
        if (this.checkPriority("metaViewport")) {
            const value_casted = value as (boolean)
            this.getPeer()?.metaViewportAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onPageEnd(value: ((parameter: OnPageEndEvent) => void)): this {
        if (this.checkPriority("onPageEnd")) {
            const value_casted = value as (((parameter: OnPageEndEvent) => void))
            UseEventsProperties({Web_onPageEnd: value_casted})
            this.getPeer()?.onPageEndAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onPageBegin(value: ((parameter: OnPageBeginEvent) => void)): this {
        if (this.checkPriority("onPageBegin")) {
            const value_casted = value as (((parameter: OnPageBeginEvent) => void))
            UseEventsProperties({Web_onPageBegin: value_casted})
            this.getPeer()?.onPageBeginAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onProgressChange(value: ((parameter: OnProgressChangeEvent) => void)): this {
        if (this.checkPriority("onProgressChange")) {
            const value_casted = value as (((parameter: OnProgressChangeEvent) => void))
            UseEventsProperties({Web_onProgressChange: value_casted})
            this.getPeer()?.onProgressChangeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onTitleReceive(value: ((parameter: OnTitleReceiveEvent) => void)): this {
        if (this.checkPriority("onTitleReceive")) {
            const value_casted = value as (((parameter: OnTitleReceiveEvent) => void))
            UseEventsProperties({Web_onTitleReceive: value_casted})
            this.getPeer()?.onTitleReceiveAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onGeolocationHide(value: (() => void)): this {
        if (this.checkPriority("onGeolocationHide")) {
            const value_casted = value as ((() => void))
            UseEventsProperties({Web_onGeolocationHide: value_casted})
            this.getPeer()?.onGeolocationHideAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onGeolocationShow(value: ((parameter: OnGeolocationShowEvent) => void)): this {
        if (this.checkPriority("onGeolocationShow")) {
            const value_casted = value as (((parameter: OnGeolocationShowEvent) => void))
            UseEventsProperties({Web_onGeolocationShow: value_casted})
            this.getPeer()?.onGeolocationShowAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onRequestSelected(value: (() => void)): this {
        if (this.checkPriority("onRequestSelected")) {
            const value_casted = value as ((() => void))
            UseEventsProperties({Web_onRequestSelected: value_casted})
            this.getPeer()?.onRequestSelectedAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onAlert(value: ((parameter: OnAlertEvent) => boolean)): this {
        if (this.checkPriority("onAlert")) {
            const value_casted = value as (((parameter: OnAlertEvent) => boolean))
            UseEventsProperties({Web_onAlert: value_casted})
            this.getPeer()?.onAlertAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onBeforeUnload(value: ((parameter: OnBeforeUnloadEvent) => boolean)): this {
        if (this.checkPriority("onBeforeUnload")) {
            const value_casted = value as (((parameter: OnBeforeUnloadEvent) => boolean))
            UseEventsProperties({Web_onBeforeUnload: value_casted})
            this.getPeer()?.onBeforeUnloadAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onConfirm(value: ((parameter: OnConfirmEvent) => boolean)): this {
        if (this.checkPriority("onConfirm")) {
            const value_casted = value as (((parameter: OnConfirmEvent) => boolean))
            UseEventsProperties({Web_onConfirm: value_casted})
            this.getPeer()?.onConfirmAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onPrompt(value: ((parameter: OnPromptEvent) => boolean)): this {
        if (this.checkPriority("onPrompt")) {
            const value_casted = value as (((parameter: OnPromptEvent) => boolean))
            UseEventsProperties({Web_onPrompt: value_casted})
            this.getPeer()?.onPromptAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onConsole(value: ((parameter: OnConsoleEvent) => boolean)): this {
        if (this.checkPriority("onConsole")) {
            const value_casted = value as (((parameter: OnConsoleEvent) => boolean))
            UseEventsProperties({Web_onConsole: value_casted})
            this.getPeer()?.onConsoleAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onErrorReceive(value: ((parameter: OnErrorReceiveEvent) => void)): this {
        if (this.checkPriority("onErrorReceive")) {
            const value_casted = value as (((parameter: OnErrorReceiveEvent) => void))
            UseEventsProperties({Web_onErrorReceive: value_casted})
            this.getPeer()?.onErrorReceiveAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onHttpErrorReceive(value: ((parameter: OnHttpErrorReceiveEvent) => void)): this {
        if (this.checkPriority("onHttpErrorReceive")) {
            const value_casted = value as (((parameter: OnHttpErrorReceiveEvent) => void))
            UseEventsProperties({Web_onHttpErrorReceive: value_casted})
            this.getPeer()?.onHttpErrorReceiveAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onDownloadStart(value: ((parameter: OnDownloadStartEvent) => void)): this {
        if (this.checkPriority("onDownloadStart")) {
            const value_casted = value as (((parameter: OnDownloadStartEvent) => void))
            UseEventsProperties({Web_onDownloadStart: value_casted})
            this.getPeer()?.onDownloadStartAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onRefreshAccessedHistory(value: ((parameter: OnRefreshAccessedHistoryEvent) => void)): this {
        if (this.checkPriority("onRefreshAccessedHistory")) {
            const value_casted = value as (((parameter: OnRefreshAccessedHistoryEvent) => void))
            UseEventsProperties({Web_onRefreshAccessedHistory: value_casted})
            this.getPeer()?.onRefreshAccessedHistoryAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onUrlLoadIntercept(value: ((event?: { data: string | WebResourceRequest }) => boolean)): this {
        if (this.checkPriority("onUrlLoadIntercept")) {
            const value_casted = value as (((event?: { data: string | WebResourceRequest }) => boolean))
            UseEventsProperties({Web_onUrlLoadIntercept: value_casted})
            this.getPeer()?.onUrlLoadInterceptAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onSslErrorReceive(value: ((event?: { handler: Function, error: Object }) => void)): this {
        if (this.checkPriority("onSslErrorReceive")) {
            const value_casted = value as (((event?: { handler: Function, error: Object }) => void))
            UseEventsProperties({Web_onSslErrorReceive: value_casted})
            this.getPeer()?.onSslErrorReceiveAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onRenderExited(value: ((parameter: OnRenderExitedEvent) => void) | ((event?: { detail: Object }) => boolean)): this {
        if (this.checkPriority("onRenderExited")) {
            const value_type = runtimeType(value)
            if (RuntimeType.FUNCTION == value_type) {
                const value_casted = value as (((parameter: OnRenderExitedEvent) => void))
                UseEventsProperties({Web_onRenderExited0: value_casted})
                this.getPeer()?.onRenderExited0Attribute(value_casted)
                return this
            }
            if (RuntimeType.FUNCTION == value_type) {
                const value_casted = value as (((event?: { detail: Object }) => boolean))
                UseEventsProperties({Web_onRenderExited1: value_casted})
                this.getPeer()?.onRenderExited1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    /** @memo */
    public onShowFileSelector(value: ((parameter: OnShowFileSelectorEvent) => boolean)): this {
        if (this.checkPriority("onShowFileSelector")) {
            const value_casted = value as (((parameter: OnShowFileSelectorEvent) => boolean))
            UseEventsProperties({Web_onShowFileSelector: value_casted})
            this.getPeer()?.onShowFileSelectorAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onFileSelectorShow(value: ((event?: { callback_: Function, fileSelector: Object }) => void)): this {
        if (this.checkPriority("onFileSelectorShow")) {
            const value_casted = value as (((event?: { callback_: Function, fileSelector: Object }) => void))
            UseEventsProperties({Web_onFileSelectorShow: value_casted})
            this.getPeer()?.onFileSelectorShowAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onResourceLoad(value: ((parameter: OnResourceLoadEvent) => void)): this {
        if (this.checkPriority("onResourceLoad")) {
            const value_casted = value as (((parameter: OnResourceLoadEvent) => void))
            UseEventsProperties({Web_onResourceLoad: value_casted})
            this.getPeer()?.onResourceLoadAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onFullScreenExit(value: (() => void)): this {
        if (this.checkPriority("onFullScreenExit")) {
            const value_casted = value as ((() => void))
            UseEventsProperties({Web_onFullScreenExit: value_casted})
            this.getPeer()?.onFullScreenExitAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onFullScreenEnter(value: OnFullScreenEnterCallback): this {
        if (this.checkPriority("onFullScreenEnter")) {
            const value_casted = value as (OnFullScreenEnterCallback)
            UseEventsProperties({Web_onFullScreenEnter: value_casted})
            this.getPeer()?.onFullScreenEnterAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onScaleChange(value: ((parameter: OnScaleChangeEvent) => void)): this {
        if (this.checkPriority("onScaleChange")) {
            const value_casted = value as (((parameter: OnScaleChangeEvent) => void))
            UseEventsProperties({Web_onScaleChange: value_casted})
            this.getPeer()?.onScaleChangeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onHttpAuthRequest(value: ((parameter: OnHttpAuthRequestEvent) => boolean)): this {
        if (this.checkPriority("onHttpAuthRequest")) {
            const value_casted = value as (((parameter: OnHttpAuthRequestEvent) => boolean))
            UseEventsProperties({Web_onHttpAuthRequest: value_casted})
            this.getPeer()?.onHttpAuthRequestAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onInterceptRequest(value: ((parameter: OnInterceptRequestEvent) => WebResourceResponse)): this {
        if (this.checkPriority("onInterceptRequest")) {
            const value_casted = value as (((parameter: OnInterceptRequestEvent) => WebResourceResponse))
            UseEventsProperties({Web_onInterceptRequest: value_casted})
            this.getPeer()?.onInterceptRequestAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onPermissionRequest(value: ((parameter: OnPermissionRequestEvent) => void)): this {
        if (this.checkPriority("onPermissionRequest")) {
            const value_casted = value as (((parameter: OnPermissionRequestEvent) => void))
            UseEventsProperties({Web_onPermissionRequest: value_casted})
            this.getPeer()?.onPermissionRequestAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onScreenCaptureRequest(value: ((parameter: OnScreenCaptureRequestEvent) => void)): this {
        if (this.checkPriority("onScreenCaptureRequest")) {
            const value_casted = value as (((parameter: OnScreenCaptureRequestEvent) => void))
            UseEventsProperties({Web_onScreenCaptureRequest: value_casted})
            this.getPeer()?.onScreenCaptureRequestAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onContextMenuShow(value: ((parameter: OnContextMenuShowEvent) => boolean)): this {
        if (this.checkPriority("onContextMenuShow")) {
            const value_casted = value as (((parameter: OnContextMenuShowEvent) => boolean))
            UseEventsProperties({Web_onContextMenuShow: value_casted})
            this.getPeer()?.onContextMenuShowAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onContextMenuHide(value: OnContextMenuHideCallback): this {
        if (this.checkPriority("onContextMenuHide")) {
            const value_casted = value as (OnContextMenuHideCallback)
            UseEventsProperties({Web_onContextMenuHide: value_casted})
            this.getPeer()?.onContextMenuHideAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public mediaPlayGestureAccess(value: boolean): this {
        if (this.checkPriority("mediaPlayGestureAccess")) {
            const value_casted = value as (boolean)
            this.getPeer()?.mediaPlayGestureAccessAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onSearchResultReceive(value: ((parameter: OnSearchResultReceiveEvent) => void)): this {
        if (this.checkPriority("onSearchResultReceive")) {
            const value_casted = value as (((parameter: OnSearchResultReceiveEvent) => void))
            UseEventsProperties({Web_onSearchResultReceive: value_casted})
            this.getPeer()?.onSearchResultReceiveAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onScroll(value: ((parameter: OnScrollEvent) => void)): this {
        if (this.checkPriority("onScroll")) {
            const value_casted = value as (((parameter: OnScrollEvent) => void))
            UseEventsProperties({Web_onScroll: value_casted})
            this.getPeer()?.onScrollAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onSslErrorEventReceive(value: ((parameter: OnSslErrorEventReceiveEvent) => void)): this {
        if (this.checkPriority("onSslErrorEventReceive")) {
            const value_casted = value as (((parameter: OnSslErrorEventReceiveEvent) => void))
            UseEventsProperties({Web_onSslErrorEventReceive: value_casted})
            this.getPeer()?.onSslErrorEventReceiveAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onSslErrorEvent(value: OnSslErrorEventCallback): this {
        if (this.checkPriority("onSslErrorEvent")) {
            const value_casted = value as (OnSslErrorEventCallback)
            UseEventsProperties({Web_onSslErrorEvent: value_casted})
            this.getPeer()?.onSslErrorEventAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onClientAuthenticationRequest(value: ((parameter: OnClientAuthenticationEvent) => void)): this {
        if (this.checkPriority("onClientAuthenticationRequest")) {
            const value_casted = value as (((parameter: OnClientAuthenticationEvent) => void))
            UseEventsProperties({Web_onClientAuthenticationRequest: value_casted})
            this.getPeer()?.onClientAuthenticationRequestAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onWindowNew(value: ((parameter: OnWindowNewEvent) => void)): this {
        if (this.checkPriority("onWindowNew")) {
            const value_casted = value as (((parameter: OnWindowNewEvent) => void))
            UseEventsProperties({Web_onWindowNew: value_casted})
            this.getPeer()?.onWindowNewAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onWindowExit(value: (() => void)): this {
        if (this.checkPriority("onWindowExit")) {
            const value_casted = value as ((() => void))
            UseEventsProperties({Web_onWindowExit: value_casted})
            this.getPeer()?.onWindowExitAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public multiWindowAccess(value: boolean): this {
        if (this.checkPriority("multiWindowAccess")) {
            const value_casted = value as (boolean)
            this.getPeer()?.multiWindowAccessAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onInterceptKeyEvent(value: ((parameter: KeyEvent) => boolean)): this {
        if (this.checkPriority("onInterceptKeyEvent")) {
            const value_casted = value as (((parameter: KeyEvent) => boolean))
            UseEventsProperties({Web_onInterceptKeyEvent: value_casted})
            this.getPeer()?.onInterceptKeyEventAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public webStandardFont(value: string): this {
        if (this.checkPriority("webStandardFont")) {
            const value_casted = value as (string)
            this.getPeer()?.webStandardFontAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public webSerifFont(value: string): this {
        if (this.checkPriority("webSerifFont")) {
            const value_casted = value as (string)
            this.getPeer()?.webSerifFontAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public webSansSerifFont(value: string): this {
        if (this.checkPriority("webSansSerifFont")) {
            const value_casted = value as (string)
            this.getPeer()?.webSansSerifFontAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public webFixedFont(value: string): this {
        if (this.checkPriority("webFixedFont")) {
            const value_casted = value as (string)
            this.getPeer()?.webFixedFontAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public webFantasyFont(value: string): this {
        if (this.checkPriority("webFantasyFont")) {
            const value_casted = value as (string)
            this.getPeer()?.webFantasyFontAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public webCursiveFont(value: string): this {
        if (this.checkPriority("webCursiveFont")) {
            const value_casted = value as (string)
            this.getPeer()?.webCursiveFontAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public defaultFixedFontSize(value: number): this {
        if (this.checkPriority("defaultFixedFontSize")) {
            const value_casted = value as (number)
            this.getPeer()?.defaultFixedFontSizeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public defaultFontSize(value: number): this {
        if (this.checkPriority("defaultFontSize")) {
            const value_casted = value as (number)
            this.getPeer()?.defaultFontSizeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public minFontSize(value: number): this {
        if (this.checkPriority("minFontSize")) {
            const value_casted = value as (number)
            this.getPeer()?.minFontSizeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public minLogicalFontSize(value: number): this {
        if (this.checkPriority("minLogicalFontSize")) {
            const value_casted = value as (number)
            this.getPeer()?.minLogicalFontSizeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public defaultTextEncodingFormat(value: string): this {
        if (this.checkPriority("defaultTextEncodingFormat")) {
            const value_casted = value as (string)
            this.getPeer()?.defaultTextEncodingFormatAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public forceDisplayScrollBar(value: boolean): this {
        if (this.checkPriority("forceDisplayScrollBar")) {
            const value_casted = value as (boolean)
            this.getPeer()?.forceDisplayScrollBarAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public blockNetwork(value: boolean): this {
        if (this.checkPriority("blockNetwork")) {
            const value_casted = value as (boolean)
            this.getPeer()?.blockNetworkAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public horizontalScrollBarAccess(value: boolean): this {
        if (this.checkPriority("horizontalScrollBarAccess")) {
            const value_casted = value as (boolean)
            this.getPeer()?.horizontalScrollBarAccessAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public verticalScrollBarAccess(value: boolean): this {
        if (this.checkPriority("verticalScrollBarAccess")) {
            const value_casted = value as (boolean)
            this.getPeer()?.verticalScrollBarAccessAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onTouchIconUrlReceived(value: ((parameter: OnTouchIconUrlReceivedEvent) => void)): this {
        if (this.checkPriority("onTouchIconUrlReceived")) {
            const value_casted = value as (((parameter: OnTouchIconUrlReceivedEvent) => void))
            UseEventsProperties({Web_onTouchIconUrlReceived: value_casted})
            this.getPeer()?.onTouchIconUrlReceivedAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onFaviconReceived(value: ((parameter: OnFaviconReceivedEvent) => void)): this {
        if (this.checkPriority("onFaviconReceived")) {
            const value_casted = value as (((parameter: OnFaviconReceivedEvent) => void))
            UseEventsProperties({Web_onFaviconReceived: value_casted})
            this.getPeer()?.onFaviconReceivedAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onPageVisible(value: ((parameter: OnPageVisibleEvent) => void)): this {
        if (this.checkPriority("onPageVisible")) {
            const value_casted = value as (((parameter: OnPageVisibleEvent) => void))
            UseEventsProperties({Web_onPageVisible: value_casted})
            this.getPeer()?.onPageVisibleAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onDataResubmitted(value: ((parameter: OnDataResubmittedEvent) => void)): this {
        if (this.checkPriority("onDataResubmitted")) {
            const value_casted = value as (((parameter: OnDataResubmittedEvent) => void))
            UseEventsProperties({Web_onDataResubmitted: value_casted})
            this.getPeer()?.onDataResubmittedAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public pinchSmooth(value: boolean): this {
        if (this.checkPriority("pinchSmooth")) {
            const value_casted = value as (boolean)
            this.getPeer()?.pinchSmoothAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public allowWindowOpenMethod(value: boolean): this {
        if (this.checkPriority("allowWindowOpenMethod")) {
            const value_casted = value as (boolean)
            this.getPeer()?.allowWindowOpenMethodAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onAudioStateChanged(value: ((parameter: OnAudioStateChangedEvent) => void)): this {
        if (this.checkPriority("onAudioStateChanged")) {
            const value_casted = value as (((parameter: OnAudioStateChangedEvent) => void))
            UseEventsProperties({Web_onAudioStateChanged: value_casted})
            this.getPeer()?.onAudioStateChangedAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onFirstContentfulPaint(value: ((parameter: OnFirstContentfulPaintEvent) => void)): this {
        if (this.checkPriority("onFirstContentfulPaint")) {
            const value_casted = value as (((parameter: OnFirstContentfulPaintEvent) => void))
            UseEventsProperties({Web_onFirstContentfulPaint: value_casted})
            this.getPeer()?.onFirstContentfulPaintAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onFirstMeaningfulPaint(value: OnFirstMeaningfulPaintCallback): this {
        if (this.checkPriority("onFirstMeaningfulPaint")) {
            const value_casted = value as (OnFirstMeaningfulPaintCallback)
            UseEventsProperties({Web_onFirstMeaningfulPaint: value_casted})
            this.getPeer()?.onFirstMeaningfulPaintAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onLargestContentfulPaint(value: OnLargestContentfulPaintCallback): this {
        if (this.checkPriority("onLargestContentfulPaint")) {
            const value_casted = value as (OnLargestContentfulPaintCallback)
            UseEventsProperties({Web_onLargestContentfulPaint: value_casted})
            this.getPeer()?.onLargestContentfulPaintAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onLoadIntercept(value: ((parameter: OnLoadInterceptEvent) => boolean)): this {
        if (this.checkPriority("onLoadIntercept")) {
            const value_casted = value as (((parameter: OnLoadInterceptEvent) => boolean))
            UseEventsProperties({Web_onLoadIntercept: value_casted})
            this.getPeer()?.onLoadInterceptAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onControllerAttached(value: (() => void)): this {
        if (this.checkPriority("onControllerAttached")) {
            const value_casted = value as ((() => void))
            UseEventsProperties({Web_onControllerAttached: value_casted})
            this.getPeer()?.onControllerAttachedAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onOverScroll(value: ((parameter: OnOverScrollEvent) => void)): this {
        if (this.checkPriority("onOverScroll")) {
            const value_casted = value as (((parameter: OnOverScrollEvent) => void))
            UseEventsProperties({Web_onOverScroll: value_casted})
            this.getPeer()?.onOverScrollAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onSafeBrowsingCheckResult(value: OnSafeBrowsingCheckResultCallback): this {
        if (this.checkPriority("onSafeBrowsingCheckResult")) {
            const value_casted = value as (OnSafeBrowsingCheckResultCallback)
            UseEventsProperties({Web_onSafeBrowsingCheckResult: value_casted})
            this.getPeer()?.onSafeBrowsingCheckResultAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onNavigationEntryCommitted(value: OnNavigationEntryCommittedCallback): this {
        if (this.checkPriority("onNavigationEntryCommitted")) {
            const value_casted = value as (OnNavigationEntryCommittedCallback)
            UseEventsProperties({Web_onNavigationEntryCommitted: value_casted})
            this.getPeer()?.onNavigationEntryCommittedAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onIntelligentTrackingPreventionResult(value: OnIntelligentTrackingPreventionCallback): this {
        if (this.checkPriority("onIntelligentTrackingPreventionResult")) {
            const value_casted = value as (OnIntelligentTrackingPreventionCallback)
            UseEventsProperties({Web_onIntelligentTrackingPreventionResult: value_casted})
            this.getPeer()?.onIntelligentTrackingPreventionResultAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public javaScriptOnDocumentStart(value: Array<ScriptItem>): this {
        if (this.checkPriority("javaScriptOnDocumentStart")) {
            const value_casted = value as (Array<ScriptItem>)
            this.getPeer()?.javaScriptOnDocumentStartAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public javaScriptOnDocumentEnd(value: Array<ScriptItem>): this {
        if (this.checkPriority("javaScriptOnDocumentEnd")) {
            const value_casted = value as (Array<ScriptItem>)
            this.getPeer()?.javaScriptOnDocumentEndAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public layoutMode(value: WebLayoutMode): this {
        if (this.checkPriority("layoutMode")) {
            const value_casted = value as (WebLayoutMode)
            this.getPeer()?.layoutModeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public nestedScroll(value: NestedScrollOptions | NestedScrollOptionsExt): this {
        if (this.checkPriority("nestedScroll")) {
            const value_casted = value as (NestedScrollOptions | NestedScrollOptionsExt)
            this.getPeer()?.nestedScrollAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public enableNativeEmbedMode(value: boolean): this {
        if (this.checkPriority("enableNativeEmbedMode")) {
            const value_casted = value as (boolean)
            this.getPeer()?.enableNativeEmbedModeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onNativeEmbedLifecycleChange(value: ((event: NativeEmbedDataInfo) => void)): this {
        if (this.checkPriority("onNativeEmbedLifecycleChange")) {
            const value_casted = value as (((event: NativeEmbedDataInfo) => void))
            UseEventsProperties({Web_onNativeEmbedLifecycleChange: value_casted})
            this.getPeer()?.onNativeEmbedLifecycleChangeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onNativeEmbedVisibilityChange(value: OnNativeEmbedVisibilityChangeCallback): this {
        if (this.checkPriority("onNativeEmbedVisibilityChange")) {
            const value_casted = value as (OnNativeEmbedVisibilityChangeCallback)
            UseEventsProperties({Web_onNativeEmbedVisibilityChange: value_casted})
            this.getPeer()?.onNativeEmbedVisibilityChangeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onNativeEmbedGestureEvent(value: ((event: NativeEmbedTouchInfo) => void)): this {
        if (this.checkPriority("onNativeEmbedGestureEvent")) {
            const value_casted = value as (((event: NativeEmbedTouchInfo) => void))
            UseEventsProperties({Web_onNativeEmbedGestureEvent: value_casted})
            this.getPeer()?.onNativeEmbedGestureEventAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public copyOptions(value: CopyOptions): this {
        if (this.checkPriority("copyOptions")) {
            const value_casted = value as (CopyOptions)
            this.getPeer()?.copyOptionsAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onOverrideUrlLoading(value: OnOverrideUrlLoadingCallback): this {
        if (this.checkPriority("onOverrideUrlLoading")) {
            const value_casted = value as (OnOverrideUrlLoadingCallback)
            UseEventsProperties({Web_onOverrideUrlLoading: value_casted})
            this.getPeer()?.onOverrideUrlLoadingAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public textAutosizing(value: boolean): this {
        if (this.checkPriority("textAutosizing")) {
            const value_casted = value as (boolean)
            this.getPeer()?.textAutosizingAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public enableNativeMediaPlayer(value: NativeMediaPlayerConfig): this {
        if (this.checkPriority("enableNativeMediaPlayer")) {
            const value_casted = value as (NativeMediaPlayerConfig)
            this.getPeer()?.enableNativeMediaPlayerAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public enableSmoothDragResize(value: boolean): this {
        if (this.checkPriority("enableSmoothDragResize")) {
            const value_casted = value as (boolean)
            this.getPeer()?.enableSmoothDragResizeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onRenderProcessNotResponding(value: OnRenderProcessNotRespondingCallback): this {
        if (this.checkPriority("onRenderProcessNotResponding")) {
            const value_casted = value as (OnRenderProcessNotRespondingCallback)
            UseEventsProperties({Web_onRenderProcessNotResponding: value_casted})
            this.getPeer()?.onRenderProcessNotRespondingAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onRenderProcessResponding(value: OnRenderProcessRespondingCallback): this {
        if (this.checkPriority("onRenderProcessResponding")) {
            const value_casted = value as (OnRenderProcessRespondingCallback)
            UseEventsProperties({Web_onRenderProcessResponding: value_casted})
            this.getPeer()?.onRenderProcessRespondingAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public selectionMenuOptions(value: Array<ExpandedMenuItemOptions>): this {
        if (this.checkPriority("selectionMenuOptions")) {
            const value_casted = value as (Array<ExpandedMenuItemOptions>)
            this.getPeer()?.selectionMenuOptionsAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onViewportFitChanged(value: OnViewportFitChangedCallback): this {
        if (this.checkPriority("onViewportFitChanged")) {
            const value_casted = value as (OnViewportFitChangedCallback)
            UseEventsProperties({Web_onViewportFitChanged: value_casted})
            this.getPeer()?.onViewportFitChangedAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onInterceptKeyboardAttach(value: WebKeyboardCallback): this {
        if (this.checkPriority("onInterceptKeyboardAttach")) {
            const value_casted = value as (WebKeyboardCallback)
            UseEventsProperties({Web_onInterceptKeyboardAttach: value_casted})
            this.getPeer()?.onInterceptKeyboardAttachAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onAdsBlocked(value: OnAdsBlockedCallback): this {
        if (this.checkPriority("onAdsBlocked")) {
            const value_casted = value as (OnAdsBlockedCallback)
            UseEventsProperties({Web_onAdsBlocked: value_casted})
            this.getPeer()?.onAdsBlockedAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public keyboardAvoidMode(value: WebKeyboardAvoidMode): this {
        if (this.checkPriority("keyboardAvoidMode")) {
            const value_casted = value as (WebKeyboardAvoidMode)
            this.getPeer()?.keyboardAvoidModeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public editMenuOptions(value: EditMenuOptions): this {
        if (this.checkPriority("editMenuOptions")) {
            const value_casted = value as (EditMenuOptions)
            this.getPeer()?.editMenuOptionsAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public enableHapticFeedback(value: boolean): this {
        if (this.checkPriority("enableHapticFeedback")) {
            const value_casted = value as (boolean)
            this.getPeer()?.enableHapticFeedbackAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public registerNativeEmbedRule(tag: string, type: string): this {
        if (this.checkPriority("registerNativeEmbedRule")) {
            const tag_casted = tag as (string)
            const type_casted = type as (string)
            this.getPeer()?.registerNativeEmbedRuleAttribute(tag_casted, type_casted)
            return this
        }
        return this
    }
    /** @memo */
    public bindSelectionMenu(elementType: WebElementType, content: CustomBuilder, responseType: WebResponseType, options?: SelectionMenuOptionsExt): this {
        if (this.checkPriority("bindSelectionMenu")) {
            const elementType_casted = elementType as (WebElementType)
            const content_casted = content as (CustomBuilder)
            const responseType_casted = responseType as (WebResponseType)
            const options_casted = options as (SelectionMenuOptionsExt | undefined)
            UseEventsProperties({Web_bindSelectionMenu: content_casted})
            this.getPeer()?.bindSelectionMenuAttribute(elementType_casted, content_casted, responseType_casted, options_casted)
            return this
        }
        return this
    }
    public applyAttributesFinish(): void {
        // we calls this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}

/** @memo */
export function ArkWeb(
  /** @memo */
  style: ((attributes: ArkWebComponent) => void) | undefined,
  /** @memo */
  content_: (() => void) | undefined,
  value: WebOptions
) {
    const receiver = remember(() => {
        return new ArkWebComponent()
    })
    NodeAttach<ArkWebPeer>((): ArkWebPeer => ArkWebPeer.create(receiver), (_: ArkWebPeer) => {
        receiver.setWebOptions(value)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
