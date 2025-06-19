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

import { int32, float32 } from "@koalaui/common"
import { nullptr, KPointer, KInt, KBoolean, KStringPtr } from "@koalaui/interop"
import { runtimeType, RuntimeType } from "@koalaui/interop"
import { Serializer } from "./Serializer"
import { ComponentBase } from "../../ComponentBase"
import { PeerNode } from "../../PeerNode"
import { isInstanceOf } from "@koalaui/interop"
import { isResource, isPadding } from "../../utils"
import { ArkUIGeneratedNativeModule } from "../ArkUIGeneratedNativeModule"
import { ArkCommonMethodPeer, ArkCommonMethodAttributes } from "./ArkCommonPeer"
import { CommonMethod, Rectangle, PixelRoundPolicy, BackgroundEffectOptions, ForegroundEffectOptions, VisualEffect, Filter, BorderImageOption, OutlineStyle, AccessibilityCallback, AnimateParam, TransitionOptions, MotionBlurOptions, InvertOptions, TranslateOptions, ScaleOptions, RotateOptions, AlignRuleOption, LocalizedAlignRuleOptions, ClickEffect, UniformDataType, CustomBuilder, DragItemInfo, MotionPathOptions, ShadowOptions, ShadowStyle, StateStyles, PixelStretchEffectOptions, BackgroundBrightnessOptions, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, SizeChangeCallback, SafeAreaType, SafeAreaEdge, BlurStyle, BackgroundBlurStyleOptions, ForegroundBlurStyleOptions, TransitionFinishCallback, BlurOptions, LinearGradientBlurOptions, EffectType, sharedTransitionOptions, ChainStyle, DragPreviewOptions, DragInteractionOptions, ComponentContent, OverlayOptions, BlendMode, BlendApplyType, Blender, GeometryTransitionOptions, PopupOptions, CustomPopupOptions, MenuElement, MenuOptions, ContextMenuOptions, ModalTransition, ContentCoverOptions, SheetOptions, VisibleAreaChangeCallback, DrawContext, TouchTestInfo, TouchResult, AdaptiveColor, BlurStyleActivePolicy, RepeatMode, LinearGradient_common, FinishCallbackType, ExpectedFrameRateRange, TransitionEffects, TransitionEdge, MotionBlurAnchor, LocalizedHorizontalAlignParam, LocalizedVerticalAlignParam, PreDragStatus, ShadowType, UIGestureEvent, BlurStyleOptions, ThemeColorMode, FractionStop, DragPreviewMode, ImageModifier, OverlayOffset, TransitionHierarchyStrategy, PopupMessageOptions, SymbolGlyphModifier, MenuPreviewMode, ContextMenuAnimationOptions, BindOptions, SheetSize, SheetType, SheetTitleOptions, SheetMode, ScrollSizeMode, UIContext, SheetKeyboardAvoidMode, SourceTool, RectResult, TouchTestStrategy, EventTarget, SourceType, TouchObject, HistoricalPoint, IntentionCode, DragBehavior, Summary, DragResult, DismissPopupAction, DismissContentCoverAction, SheetDismiss, DismissSheetAction, SpringBackAction, DismissReason, NestedScrollOptions } from "./../ArkCommonInterfaces"
import { Length, SizeOptions, ConstraintSizeOptions, ChainWeightOptions, Padding, LocalizedPadding, Margin, LocalizedMargin, ResourceColor, Position, BorderOptions, EdgeStyles, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, Dimension, EdgeOutlineWidths, OutlineRadiuses, Edges, LocalizedEdges, LocalizedPosition, ResourceStr, AccessibilityOptions, PX, VP, FP, LPX, Percentage, Area, Bias, Font } from "./../ArkUnitsInterfaces"
import { DrawModifier } from "./../ArkDrawModifierMaterialized"
import { HitTestMode, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Color, Visibility, ItemAlign, Direction, GradientDirection, ObscuredReasons, RenderFit, ImageRepeat, Axis, ResponseType, FunctionKey, ModifierKey, PixelRoundCalcPolicy, Curve, PlayMode, TransitionType, HorizontalAlign, VerticalAlign, ClickEffectLevel, SharedTransitionEffectType, Placement, ArrowPointPosition, MouseButton, MouseAction, TouchType, KeyType, KeySource, FontWeight, FontStyle, CopyOptions, NestedScrollMode } from "./../ArkEnumsInterfaces"
import { LengthMetrics } from "./../ArkLengthMetricsMaterialized"
import { ResizableOptions, DrawingLattice } from "./../ArkImageInterfaces"
import { Resource } from "./../ArkResourceInterfaces"
import { FocusBoxStyle, FocusPriority } from "./../ArkFocusInterfaces"
import { TransitionEffect } from "./../ArkTransitionEffectMaterialized"
import { CircleShape } from "./../ArkCircleShapeMaterialized"
import { EllipseShape } from "./../ArkEllipseShapeMaterialized"
import { PathShape } from "./../ArkPathShapeMaterialized"
import { RectShape } from "./../ArkRectShapeMaterialized"
import { ProgressMask } from "./../ArkProgressMaskMaterialized"
import { AttributeModifier } from "./../../handwritten"
import { GestureModifier } from "./../ArkGestureModifierMaterialized"
import { PixelMap } from "./../ArkPixelMapMaterialized"
import { GestureType, GestureMask, GestureInfo, GestureJudgeResult, GestureInterface, TapGestureParameters, PanDirection, SwipeDirection, GestureMode, GestureHandler, GesturePriority, FingerInfo } from "./../ArkGestureInterfaces"
import { TapGestureInterface } from "./../ArkTapGestureInterfaceMaterialized"
import { LongPressGestureInterface } from "./../ArkLongPressGestureInterfaceMaterialized"
import { PanGestureInterface } from "./../ArkPanGestureInterfaceMaterialized"
import { PinchGestureInterface } from "./../ArkPinchGestureInterfaceMaterialized"
import { SwipeGestureInterface } from "./../ArkSwipeGestureInterfaceMaterialized"
import { RotationGestureInterface } from "./../ArkRotationGestureInterfaceMaterialized"
import { GestureGroupInterface } from "./../ArkGestureGroupInterfaceMaterialized"
import { LengthUnit, ShapeSize, PathShapeOptions, RectShapeOptions, RoundRectShapeOptions, WebHeader } from "./../ArkArkuiExternalInterfaces"
import { ClickEvent } from "./../ArkClickEventMaterialized"
import { HoverEvent } from "./../ArkHoverEventMaterialized"
import { MouseEvent } from "./../ArkMouseEventMaterialized"
import { TouchEvent } from "./../ArkTouchEventMaterialized"
import { KeyEvent } from "./../ArkKeyEventMaterialized"
import { ColorMetrics } from "./../ArkColorMetricsMaterialized"
import { ICurve } from "./../ArkICurveMaterialized"
import { DragEvent } from "./../ArkDragEventMaterialized"
import { BaseGestureEvent } from "./../ArkBaseGestureEventMaterialized"
import { PanGestureOptions } from "./../ArkPanGestureOptionsMaterialized"
import { BaseEvent } from "./../ArkBaseEventMaterialized"
import { UnifiedData } from "./../ArkUnifiedDataMaterialized"
import { GestureControl } from "./../ArkGestureControlNamespace"
import { GestureEvent } from "./../ArkGestureEventMaterialized"
import { MixedMode, JavaScriptProxy, CacheMode, WebDarkMode, WebMediaOptions, OverScrollMode, OnFullScreenEnterCallback, OnContextMenuHideCallback, OnSslErrorEventCallback, OnFirstMeaningfulPaintCallback, OnLargestContentfulPaintCallback, OnSafeBrowsingCheckResultCallback, OnNavigationEntryCommittedCallback, OnIntelligentTrackingPreventionCallback, ScriptItem, WebLayoutMode, NestedScrollOptionsExt, OnNativeEmbedVisibilityChangeCallback, OnOverrideUrlLoadingCallback, NativeMediaPlayerConfig, OnRenderProcessNotRespondingCallback, OnRenderProcessRespondingCallback, ExpandedMenuItemOptions, OnViewportFitChangedCallback, WebKeyboardCallback, OnAdsBlockedCallback, WebKeyboardAvoidMode, WebAttribute, WebElementType, WebResponseType, SelectionMenuOptionsExt, OnPageEndEvent, OnPageBeginEvent, OnProgressChangeEvent, OnTitleReceiveEvent, OnGeolocationShowEvent, OnAlertEvent, OnBeforeUnloadEvent, OnConfirmEvent, OnPromptEvent, OnConsoleEvent, OnErrorReceiveEvent, OnHttpErrorReceiveEvent, OnDownloadStartEvent, OnRefreshAccessedHistoryEvent, OnRenderExitedEvent, OnShowFileSelectorEvent, OnResourceLoadEvent, OnScaleChangeEvent, OnHttpAuthRequestEvent, OnInterceptRequestEvent, OnPermissionRequestEvent, OnScreenCaptureRequestEvent, OnContextMenuShowEvent, OnSearchResultReceiveEvent, OnScrollEvent, OnSslErrorEventReceiveEvent, OnClientAuthenticationEvent, OnWindowNewEvent, OnTouchIconUrlReceivedEvent, OnFaviconReceivedEvent, OnPageVisibleEvent, OnDataResubmittedEvent, OnAudioStateChangedEvent, OnFirstContentfulPaintEvent, OnLoadInterceptEvent, OnOverScrollEvent, NativeEmbedDataInfo, NativeEmbedTouchInfo, Header, HitTestType, RenderExitReason, SslError, NativeEmbedStatus, NativeEmbedInfo, MessageLevel, FileSelectorMode, ScreenCaptureConfig, ContextMenuMediaType, ContextMenuSourceType, ContextMenuInputFieldType, WebCaptureMode, WebOptions, RenderMode } from "./../ArkWebInterfaces"
import { EditMenuOptions } from "./../ArkEditMenuOptionsMaterialized"
import { WebController } from "./../ArkWebControllerMaterialized"
import { WebviewController } from "./../ArkWebviewControllerMaterialized"
import { WebResourceRequest } from "./../ArkWebResourceRequestMaterialized"
import { WebResourceResponse } from "./../ArkWebResourceResponseMaterialized"
import { TextMenuItem, TextRange, MenuType } from "./../ArkTextCommonInterfaces"
import { WebCookie } from "./../ArkWebCookieMaterialized"
import { JsGeolocation } from "./../ArkJsGeolocationMaterialized"
import { JsResult } from "./../ArkJsResultMaterialized"
import { ConsoleMessage } from "./../ArkConsoleMessageMaterialized"
import { WebResourceError } from "./../ArkWebResourceErrorMaterialized"
import { FileSelectorResult } from "./../ArkFileSelectorResultMaterialized"
import { FileSelectorParam } from "./../ArkFileSelectorParamMaterialized"
import { HttpAuthHandler } from "./../ArkHttpAuthHandlerMaterialized"
import { PermissionRequest } from "./../ArkPermissionRequestMaterialized"
import { ScreenCaptureHandler } from "./../ArkScreenCaptureHandlerMaterialized"
import { WebContextMenuParam } from "./../ArkWebContextMenuParamMaterialized"
import { WebContextMenuResult } from "./../ArkWebContextMenuResultMaterialized"
import { SslErrorHandler } from "./../ArkSslErrorHandlerMaterialized"
import { ClientAuthenticationHandler } from "./../ArkClientAuthenticationHandlerMaterialized"
import { ControllerHandler } from "./../ArkControllerHandlerMaterialized"
import { DataResubmissionHandler } from "./../ArkDataResubmissionHandlerMaterialized"
import { EventResult } from "./../ArkEventResultMaterialized"
import { TextMenuItemId } from "./../ArkTextMenuItemIdMaterialized"
import { GestureName, GestureComponent } from "./../shared/generated-utils"
import { CallbackKind } from "./CallbackKind"
import { CallbackTransformer } from "./CallbackTransformer"
import { unsafeCast } from "@koalaui/common"
import { Deserializer, createDeserializer } from "./Deserializer"
import { MaterializedBase, toPeerPtr, wrapCallback } from "@koalaui/interop"
import { DotIndicator } from "./../ArkDotIndicatorBuilder"
import { DigitIndicator } from "./../ArkDigitIndicatorBuilder"
import { SubTabBarStyle } from "./../ArkSubTabBarStyleBuilder"
import { BottomTabBarStyle } from "./../ArkBottomTabBarStyleBuilder"
export class ArkWebPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkWebPeer {
        const peerId = PeerNode.nextId()
        const _peerPtr = ArkUIGeneratedNativeModule._Web_construct(peerId, flags)
        const _peer = new ArkWebPeer(_peerPtr, peerId, "Web", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setWebOptionsAttribute(value: WebOptions): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeWebOptions(value)
        ArkUIGeneratedNativeModule._WebInterface_setWebOptions(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    javaScriptAccessAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._WebAttribute_javaScriptAccess(this.peer.ptr, +value)
    }
    fileAccessAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._WebAttribute_fileAccess(this.peer.ptr, +value)
    }
    onlineImageAccessAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._WebAttribute_onlineImageAccess(this.peer.ptr, +value)
    }
    domStorageAccessAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._WebAttribute_domStorageAccess(this.peer.ptr, +value)
    }
    imageAccessAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._WebAttribute_imageAccess(this.peer.ptr, +value)
    }
    mixedModeAttribute(value: MixedMode): void {
        ArkUIGeneratedNativeModule._WebAttribute_mixedMode(this.peer.ptr, value)
    }
    zoomAccessAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._WebAttribute_zoomAccess(this.peer.ptr, +value)
    }
    geolocationAccessAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._WebAttribute_geolocationAccess(this.peer.ptr, +value)
    }
    javaScriptProxyAttribute(value: JavaScriptProxy): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeJavaScriptProxy(value)
        ArkUIGeneratedNativeModule._WebAttribute_javaScriptProxy(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    passwordAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._WebAttribute_password(this.peer.ptr, +value)
    }
    cacheModeAttribute(value: CacheMode): void {
        ArkUIGeneratedNativeModule._WebAttribute_cacheMode(this.peer.ptr, value)
    }
    darkModeAttribute(value: WebDarkMode): void {
        ArkUIGeneratedNativeModule._WebAttribute_darkMode(this.peer.ptr, value)
    }
    forceDarkAccessAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._WebAttribute_forceDarkAccess(this.peer.ptr, +value)
    }
    mediaOptionsAttribute(value: WebMediaOptions): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeWebMediaOptions(value)
        ArkUIGeneratedNativeModule._WebAttribute_mediaOptions(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    tableDataAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._WebAttribute_tableData(this.peer.ptr, +value)
    }
    wideViewModeAccessAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._WebAttribute_wideViewModeAccess(this.peer.ptr, +value)
    }
    overviewModeAccessAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._WebAttribute_overviewModeAccess(this.peer.ptr, +value)
    }
    overScrollModeAttribute(value: OverScrollMode): void {
        ArkUIGeneratedNativeModule._WebAttribute_overScrollMode(this.peer.ptr, value)
    }
    textZoomAtioAttribute(value: number): void {
        ArkUIGeneratedNativeModule._WebAttribute_textZoomAtio(this.peer.ptr, value)
    }
    textZoomRatioAttribute(value: number): void {
        ArkUIGeneratedNativeModule._WebAttribute_textZoomRatio(this.peer.ptr, value)
    }
    databaseAccessAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._WebAttribute_databaseAccess(this.peer.ptr, +value)
    }
    initialScaleAttribute(value: number): void {
        ArkUIGeneratedNativeModule._WebAttribute_initialScale(this.peer.ptr, value)
    }
    userAgentAttribute(value: string): void {
        ArkUIGeneratedNativeModule._WebAttribute_userAgent(this.peer.ptr, value)
    }
    metaViewportAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._WebAttribute_metaViewport(this.peer.ptr, +value)
    }
    onPageEndAttribute(value: ((parameter: OnPageEndEvent) => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onPageEnd(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onPageBeginAttribute(value: ((parameter: OnPageBeginEvent) => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onPageBegin(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onProgressChangeAttribute(value: ((parameter: OnProgressChangeEvent) => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onProgressChange(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onTitleReceiveAttribute(value: ((parameter: OnTitleReceiveEvent) => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onTitleReceive(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onGeolocationHideAttribute(value: (() => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onGeolocationHide(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onGeolocationShowAttribute(value: ((parameter: OnGeolocationShowEvent) => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onGeolocationShow(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onRequestSelectedAttribute(value: (() => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onRequestSelected(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onAlertAttribute(value: ((parameter: OnAlertEvent) => boolean)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onAlert(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onBeforeUnloadAttribute(value: ((parameter: OnBeforeUnloadEvent) => boolean)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onBeforeUnload(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onConfirmAttribute(value: ((parameter: OnConfirmEvent) => boolean)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onConfirm(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onPromptAttribute(value: ((parameter: OnPromptEvent) => boolean)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onPrompt(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onConsoleAttribute(value: ((parameter: OnConsoleEvent) => boolean)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onConsole(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onErrorReceiveAttribute(value: ((parameter: OnErrorReceiveEvent) => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onErrorReceive(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onHttpErrorReceiveAttribute(value: ((parameter: OnHttpErrorReceiveEvent) => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onHttpErrorReceive(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onDownloadStartAttribute(value: ((parameter: OnDownloadStartEvent) => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onDownloadStart(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onRefreshAccessedHistoryAttribute(value: ((parameter: OnRefreshAccessedHistoryEvent) => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onRefreshAccessedHistory(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onUrlLoadInterceptAttribute(value: ((event?: { data: string | WebResourceRequest }) => boolean)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onUrlLoadIntercept(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onSslErrorReceiveAttribute(value: ((event?: { handler: Function, error: Object }) => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onSslErrorReceive(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onRenderExited0Attribute(value: ((parameter: OnRenderExitedEvent) => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onRenderExited0(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onRenderExited1Attribute(value: ((event?: { detail: Object }) => boolean)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onRenderExited1(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onShowFileSelectorAttribute(value: ((parameter: OnShowFileSelectorEvent) => boolean)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onShowFileSelector(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onFileSelectorShowAttribute(value: ((event?: { callback_: Function, fileSelector: Object }) => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onFileSelectorShow(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onResourceLoadAttribute(value: ((parameter: OnResourceLoadEvent) => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onResourceLoad(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onFullScreenExitAttribute(value: (() => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onFullScreenExit(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onFullScreenEnterAttribute(value: OnFullScreenEnterCallback): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onFullScreenEnter(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onScaleChangeAttribute(value: ((parameter: OnScaleChangeEvent) => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onScaleChange(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onHttpAuthRequestAttribute(value: ((parameter: OnHttpAuthRequestEvent) => boolean)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onHttpAuthRequest(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onInterceptRequestAttribute(value: ((parameter: OnInterceptRequestEvent) => WebResourceResponse)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onInterceptRequest(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onPermissionRequestAttribute(value: ((parameter: OnPermissionRequestEvent) => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onPermissionRequest(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onScreenCaptureRequestAttribute(value: ((parameter: OnScreenCaptureRequestEvent) => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onScreenCaptureRequest(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onContextMenuShowAttribute(value: ((parameter: OnContextMenuShowEvent) => boolean)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onContextMenuShow(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onContextMenuHideAttribute(value: OnContextMenuHideCallback): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onContextMenuHide(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    mediaPlayGestureAccessAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._WebAttribute_mediaPlayGestureAccess(this.peer.ptr, +value)
    }
    onSearchResultReceiveAttribute(value: ((parameter: OnSearchResultReceiveEvent) => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onSearchResultReceive(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onScrollAttribute(value: ((parameter: OnScrollEvent) => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onScroll(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onSslErrorEventReceiveAttribute(value: ((parameter: OnSslErrorEventReceiveEvent) => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onSslErrorEventReceive(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onSslErrorEventAttribute(value: OnSslErrorEventCallback): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onSslErrorEvent(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onClientAuthenticationRequestAttribute(value: ((parameter: OnClientAuthenticationEvent) => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onClientAuthenticationRequest(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onWindowNewAttribute(value: ((parameter: OnWindowNewEvent) => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onWindowNew(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onWindowExitAttribute(value: (() => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onWindowExit(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    multiWindowAccessAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._WebAttribute_multiWindowAccess(this.peer.ptr, +value)
    }
    onInterceptKeyEventAttribute(value: ((parameter: KeyEvent) => boolean)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onInterceptKeyEvent(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    webStandardFontAttribute(value: string): void {
        ArkUIGeneratedNativeModule._WebAttribute_webStandardFont(this.peer.ptr, value)
    }
    webSerifFontAttribute(value: string): void {
        ArkUIGeneratedNativeModule._WebAttribute_webSerifFont(this.peer.ptr, value)
    }
    webSansSerifFontAttribute(value: string): void {
        ArkUIGeneratedNativeModule._WebAttribute_webSansSerifFont(this.peer.ptr, value)
    }
    webFixedFontAttribute(value: string): void {
        ArkUIGeneratedNativeModule._WebAttribute_webFixedFont(this.peer.ptr, value)
    }
    webFantasyFontAttribute(value: string): void {
        ArkUIGeneratedNativeModule._WebAttribute_webFantasyFont(this.peer.ptr, value)
    }
    webCursiveFontAttribute(value: string): void {
        ArkUIGeneratedNativeModule._WebAttribute_webCursiveFont(this.peer.ptr, value)
    }
    defaultFixedFontSizeAttribute(value: number): void {
        ArkUIGeneratedNativeModule._WebAttribute_defaultFixedFontSize(this.peer.ptr, value)
    }
    defaultFontSizeAttribute(value: number): void {
        ArkUIGeneratedNativeModule._WebAttribute_defaultFontSize(this.peer.ptr, value)
    }
    minFontSizeAttribute(value: number): void {
        ArkUIGeneratedNativeModule._WebAttribute_minFontSize(this.peer.ptr, value)
    }
    minLogicalFontSizeAttribute(value: number): void {
        ArkUIGeneratedNativeModule._WebAttribute_minLogicalFontSize(this.peer.ptr, value)
    }
    defaultTextEncodingFormatAttribute(value: string): void {
        ArkUIGeneratedNativeModule._WebAttribute_defaultTextEncodingFormat(this.peer.ptr, value)
    }
    forceDisplayScrollBarAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._WebAttribute_forceDisplayScrollBar(this.peer.ptr, +value)
    }
    blockNetworkAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._WebAttribute_blockNetwork(this.peer.ptr, +value)
    }
    horizontalScrollBarAccessAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._WebAttribute_horizontalScrollBarAccess(this.peer.ptr, +value)
    }
    verticalScrollBarAccessAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._WebAttribute_verticalScrollBarAccess(this.peer.ptr, +value)
    }
    onTouchIconUrlReceivedAttribute(value: ((parameter: OnTouchIconUrlReceivedEvent) => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onTouchIconUrlReceived(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onFaviconReceivedAttribute(value: ((parameter: OnFaviconReceivedEvent) => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onFaviconReceived(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onPageVisibleAttribute(value: ((parameter: OnPageVisibleEvent) => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onPageVisible(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onDataResubmittedAttribute(value: ((parameter: OnDataResubmittedEvent) => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onDataResubmitted(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    pinchSmoothAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._WebAttribute_pinchSmooth(this.peer.ptr, +value)
    }
    allowWindowOpenMethodAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._WebAttribute_allowWindowOpenMethod(this.peer.ptr, +value)
    }
    onAudioStateChangedAttribute(value: ((parameter: OnAudioStateChangedEvent) => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onAudioStateChanged(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onFirstContentfulPaintAttribute(value: ((parameter: OnFirstContentfulPaintEvent) => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onFirstContentfulPaint(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onFirstMeaningfulPaintAttribute(value: OnFirstMeaningfulPaintCallback): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onFirstMeaningfulPaint(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onLargestContentfulPaintAttribute(value: OnLargestContentfulPaintCallback): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onLargestContentfulPaint(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onLoadInterceptAttribute(value: ((parameter: OnLoadInterceptEvent) => boolean)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onLoadIntercept(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onControllerAttachedAttribute(value: (() => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onControllerAttached(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onOverScrollAttribute(value: ((parameter: OnOverScrollEvent) => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onOverScroll(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onSafeBrowsingCheckResultAttribute(value: OnSafeBrowsingCheckResultCallback): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onSafeBrowsingCheckResult(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onNavigationEntryCommittedAttribute(value: OnNavigationEntryCommittedCallback): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onNavigationEntryCommitted(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onIntelligentTrackingPreventionResultAttribute(value: OnIntelligentTrackingPreventionCallback): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onIntelligentTrackingPreventionResult(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    javaScriptOnDocumentStartAttribute(value: Array<ScriptItem>): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeInt32(value.length)
        for (let i = 0; i < value.length; i++) {
            const value_element: ScriptItem = value[i]
            thisSerializer.writeScriptItem(value_element)
        }
        ArkUIGeneratedNativeModule._WebAttribute_javaScriptOnDocumentStart(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    javaScriptOnDocumentEndAttribute(value: Array<ScriptItem>): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeInt32(value.length)
        for (let i = 0; i < value.length; i++) {
            const value_element: ScriptItem = value[i]
            thisSerializer.writeScriptItem(value_element)
        }
        ArkUIGeneratedNativeModule._WebAttribute_javaScriptOnDocumentEnd(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    layoutModeAttribute(value: WebLayoutMode): void {
        ArkUIGeneratedNativeModule._WebAttribute_layoutMode(this.peer.ptr, value)
    }
    nestedScrollAttribute(value: NestedScrollOptions | NestedScrollOptionsExt): void {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (((RuntimeType.OBJECT) == (value_type)) && ((value!.hasOwnProperty("scrollForward")))) {
            thisSerializer.writeInt8(0)
            const value_0 = unsafeCast<NestedScrollOptions>(value)
            thisSerializer.writeNestedScrollOptions(value_0)
        }
        else if (((RuntimeType.OBJECT) == (value_type)) && (((value!.hasOwnProperty("scrollUp")) || (value!.hasOwnProperty("scrollDown")) || (value!.hasOwnProperty("scrollRight")) || (value!.hasOwnProperty("scrollLeft"))))) {
            thisSerializer.writeInt8(1)
            const value_1 = unsafeCast<NestedScrollOptionsExt>(value)
            thisSerializer.writeNestedScrollOptionsExt(value_1)
        }
        ArkUIGeneratedNativeModule._WebAttribute_nestedScroll(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    enableNativeEmbedModeAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._WebAttribute_enableNativeEmbedMode(this.peer.ptr, +value)
    }
    onNativeEmbedLifecycleChangeAttribute(value: ((event: NativeEmbedDataInfo) => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onNativeEmbedLifecycleChange(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onNativeEmbedVisibilityChangeAttribute(value: OnNativeEmbedVisibilityChangeCallback): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onNativeEmbedVisibilityChange(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onNativeEmbedGestureEventAttribute(value: ((event: NativeEmbedTouchInfo) => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onNativeEmbedGestureEvent(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    copyOptionsAttribute(value: CopyOptions): void {
        ArkUIGeneratedNativeModule._WebAttribute_copyOptions(this.peer.ptr, value)
    }
    onOverrideUrlLoadingAttribute(value: OnOverrideUrlLoadingCallback): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onOverrideUrlLoading(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    textAutosizingAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._WebAttribute_textAutosizing(this.peer.ptr, +value)
    }
    enableNativeMediaPlayerAttribute(value: NativeMediaPlayerConfig): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeNativeMediaPlayerConfig(value)
        ArkUIGeneratedNativeModule._WebAttribute_enableNativeMediaPlayer(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    enableSmoothDragResizeAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._WebAttribute_enableSmoothDragResize(this.peer.ptr, +value)
    }
    onRenderProcessNotRespondingAttribute(value: OnRenderProcessNotRespondingCallback): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onRenderProcessNotResponding(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onRenderProcessRespondingAttribute(value: OnRenderProcessRespondingCallback): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onRenderProcessResponding(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    selectionMenuOptionsAttribute(value: Array<ExpandedMenuItemOptions>): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeInt32(value.length)
        for (let i = 0; i < value.length; i++) {
            const value_element: ExpandedMenuItemOptions = value[i]
            thisSerializer.writeExpandedMenuItemOptions(value_element)
        }
        ArkUIGeneratedNativeModule._WebAttribute_selectionMenuOptions(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onViewportFitChangedAttribute(value: OnViewportFitChangedCallback): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onViewportFitChanged(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onInterceptKeyboardAttachAttribute(value: WebKeyboardCallback): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onInterceptKeyboardAttach(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onAdsBlockedAttribute(value: OnAdsBlockedCallback): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WebAttribute_onAdsBlocked(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    keyboardAvoidModeAttribute(value: WebKeyboardAvoidMode): void {
        ArkUIGeneratedNativeModule._WebAttribute_keyboardAvoidMode(this.peer.ptr, value)
    }
    editMenuOptionsAttribute(value: EditMenuOptions): void {
        ArkUIGeneratedNativeModule._WebAttribute_editMenuOptions(this.peer.ptr, toPeerPtr(value))
    }
    enableHapticFeedbackAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._WebAttribute_enableHapticFeedback(this.peer.ptr, +value)
    }
    registerNativeEmbedRuleAttribute(tag: string, type: string): void {
        ArkUIGeneratedNativeModule._WebAttribute_registerNativeEmbedRule(this.peer.ptr, tag, type)
    }
    bindSelectionMenuAttribute(elementType: WebElementType, content: CustomBuilder, responseType: WebResponseType, options?: SelectionMenuOptionsExt): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(content))
        let options_type: int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value = options!
            thisSerializer.writeSelectionMenuOptionsExt(options_value)
        }
        ArkUIGeneratedNativeModule._WebAttribute_bindSelectionMenu(this.peer.ptr, elementType, thisSerializer.asArray(), thisSerializer.length(), responseType)
        thisSerializer.release()
    }
}
export interface ArkWebAttributes extends ArkCommonMethodAttributes {
    javaScriptAccess?: boolean
    fileAccess?: boolean
    onlineImageAccess?: boolean
    domStorageAccess?: boolean
    imageAccess?: boolean
    mixedMode?: MixedMode
    zoomAccess?: boolean
    geolocationAccess?: boolean
    javaScriptProxy?: JavaScriptProxy
    password?: boolean
    cacheMode?: CacheMode
    darkMode?: WebDarkMode
    forceDarkAccess?: boolean
    mediaOptions?: WebMediaOptions
    tableData?: boolean
    wideViewModeAccess?: boolean
    overviewModeAccess?: boolean
    overScrollMode?: OverScrollMode
    textZoomAtio?: number
    textZoomRatio?: number
    databaseAccess?: boolean
    initialScale?: number
    userAgent?: string
    metaViewport?: boolean
    onPageEnd?: ((parameter: OnPageEndEvent) => void)
    onPageBegin?: ((parameter: OnPageBeginEvent) => void)
    onProgressChange?: ((parameter: OnProgressChangeEvent) => void)
    onTitleReceive?: ((parameter: OnTitleReceiveEvent) => void)
    onGeolocationHide?: (() => void)
    onGeolocationShow?: ((parameter: OnGeolocationShowEvent) => void)
    onRequestSelected?: (() => void)
    onAlert?: ((parameter: OnAlertEvent) => boolean)
    onBeforeUnload?: ((parameter: OnBeforeUnloadEvent) => boolean)
    onConfirm?: ((parameter: OnConfirmEvent) => boolean)
    onPrompt?: ((parameter: OnPromptEvent) => boolean)
    onConsole?: ((parameter: OnConsoleEvent) => boolean)
    onErrorReceive?: ((parameter: OnErrorReceiveEvent) => void)
    onHttpErrorReceive?: ((parameter: OnHttpErrorReceiveEvent) => void)
    onDownloadStart?: ((parameter: OnDownloadStartEvent) => void)
    onRefreshAccessedHistory?: ((parameter: OnRefreshAccessedHistoryEvent) => void)
    onUrlLoadIntercept?: ((event?: { data: string | WebResourceRequest }) => boolean)
    onSslErrorReceive?: ((event?: { handler: Function, error: Object }) => void)
    onRenderExited?: ((parameter: OnRenderExitedEvent) => void)
    onShowFileSelector?: ((parameter: OnShowFileSelectorEvent) => boolean)
    onFileSelectorShow?: ((event?: { callback_: Function, fileSelector: Object }) => void)
    onResourceLoad?: ((parameter: OnResourceLoadEvent) => void)
    onFullScreenExit?: (() => void)
    onFullScreenEnter?: OnFullScreenEnterCallback
    onScaleChange?: ((parameter: OnScaleChangeEvent) => void)
    onHttpAuthRequest?: ((parameter: OnHttpAuthRequestEvent) => boolean)
    onInterceptRequest?: ((parameter: OnInterceptRequestEvent) => WebResourceResponse)
    onPermissionRequest?: ((parameter: OnPermissionRequestEvent) => void)
    onScreenCaptureRequest?: ((parameter: OnScreenCaptureRequestEvent) => void)
    onContextMenuShow?: ((parameter: OnContextMenuShowEvent) => boolean)
    onContextMenuHide?: OnContextMenuHideCallback
    mediaPlayGestureAccess?: boolean
    onSearchResultReceive?: ((parameter: OnSearchResultReceiveEvent) => void)
    onScroll?: ((parameter: OnScrollEvent) => void)
    onSslErrorEventReceive?: ((parameter: OnSslErrorEventReceiveEvent) => void)
    onSslErrorEvent?: OnSslErrorEventCallback
    onClientAuthenticationRequest?: ((parameter: OnClientAuthenticationEvent) => void)
    onWindowNew?: ((parameter: OnWindowNewEvent) => void)
    onWindowExit?: (() => void)
    multiWindowAccess?: boolean
    onInterceptKeyEvent?: ((parameter: KeyEvent) => boolean)
    webStandardFont?: string
    webSerifFont?: string
    webSansSerifFont?: string
    webFixedFont?: string
    webFantasyFont?: string
    webCursiveFont?: string
    defaultFixedFontSize?: number
    defaultFontSize?: number
    minFontSize?: number
    minLogicalFontSize?: number
    defaultTextEncodingFormat?: string
    forceDisplayScrollBar?: boolean
    blockNetwork?: boolean
    horizontalScrollBarAccess?: boolean
    verticalScrollBarAccess?: boolean
    onTouchIconUrlReceived?: ((parameter: OnTouchIconUrlReceivedEvent) => void)
    onFaviconReceived?: ((parameter: OnFaviconReceivedEvent) => void)
    onPageVisible?: ((parameter: OnPageVisibleEvent) => void)
    onDataResubmitted?: ((parameter: OnDataResubmittedEvent) => void)
    pinchSmooth?: boolean
    allowWindowOpenMethod?: boolean
    onAudioStateChanged?: ((parameter: OnAudioStateChangedEvent) => void)
    onFirstContentfulPaint?: ((parameter: OnFirstContentfulPaintEvent) => void)
    onFirstMeaningfulPaint?: OnFirstMeaningfulPaintCallback
    onLargestContentfulPaint?: OnLargestContentfulPaintCallback
    onLoadIntercept?: ((parameter: OnLoadInterceptEvent) => boolean)
    onControllerAttached?: (() => void)
    onOverScroll?: ((parameter: OnOverScrollEvent) => void)
    onSafeBrowsingCheckResult?: OnSafeBrowsingCheckResultCallback
    onNavigationEntryCommitted?: OnNavigationEntryCommittedCallback
    onIntelligentTrackingPreventionResult?: OnIntelligentTrackingPreventionCallback
    javaScriptOnDocumentStart?: Array<ScriptItem>
    javaScriptOnDocumentEnd?: Array<ScriptItem>
    layoutMode?: WebLayoutMode
    nestedScroll?: NestedScrollOptions | NestedScrollOptionsExt
    enableNativeEmbedMode?: boolean
    onNativeEmbedLifecycleChange?: ((event: NativeEmbedDataInfo) => void)
    onNativeEmbedVisibilityChange?: OnNativeEmbedVisibilityChangeCallback
    onNativeEmbedGestureEvent?: ((event: NativeEmbedTouchInfo) => void)
    copyOptions?: CopyOptions
    onOverrideUrlLoading?: OnOverrideUrlLoadingCallback
    textAutosizing?: boolean
    enableNativeMediaPlayer?: NativeMediaPlayerConfig
    enableSmoothDragResize?: boolean
    onRenderProcessNotResponding?: OnRenderProcessNotRespondingCallback
    onRenderProcessResponding?: OnRenderProcessRespondingCallback
    selectionMenuOptions?: Array<ExpandedMenuItemOptions>
    onViewportFitChanged?: OnViewportFitChangedCallback
    onInterceptKeyboardAttach?: WebKeyboardCallback
    onAdsBlocked?: OnAdsBlockedCallback
    keyboardAvoidMode?: WebKeyboardAvoidMode
    editMenuOptions?: EditMenuOptions
    enableHapticFeedback?: boolean
}
