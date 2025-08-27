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
import { CommonMethod, Rectangle, PixelRoundPolicy, BackgroundEffectOptions, ForegroundEffectOptions, VisualEffect, Filter, BorderImageOption, OutlineStyle, AccessibilityCallback, AnimateParam, TransitionOptions, MotionBlurOptions, InvertOptions, TranslateOptions, ScaleOptions, RotateOptions, AlignRuleOption, LocalizedAlignRuleOptions, ClickEffect, UniformDataType, CustomBuilder, DragItemInfo, MotionPathOptions, ShadowOptions, ShadowStyle, StateStyles, PixelStretchEffectOptions, BackgroundBrightnessOptions, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, SizeChangeCallback, SafeAreaType, SafeAreaEdge, BlurStyle, BackgroundBlurStyleOptions, ForegroundBlurStyleOptions, TransitionFinishCallback, BlurOptions, LinearGradientBlurOptions, EffectType, sharedTransitionOptions, ChainStyle, DragPreviewOptions, DragInteractionOptions, ComponentContent, OverlayOptions, BlendMode, BlendApplyType, Blender, GeometryTransitionOptions, PopupOptions, CustomPopupOptions, MenuElement, MenuOptions, ContextMenuOptions, ModalTransition, ContentCoverOptions, SheetOptions, VisibleAreaChangeCallback, DrawContext, TouchTestInfo, TouchResult, AdaptiveColor, BlurStyleActivePolicy, RepeatMode, LinearGradient_common, FinishCallbackType, ExpectedFrameRateRange, TransitionEffects, TransitionEdge, MotionBlurAnchor, LocalizedHorizontalAlignParam, LocalizedVerticalAlignParam, PreDragStatus, ShadowType, UIGestureEvent, BlurStyleOptions, ThemeColorMode, FractionStop, DragPreviewMode, ImageModifier, OverlayOffset, TransitionHierarchyStrategy, PopupMessageOptions, SymbolGlyphModifier, MenuPreviewMode, ContextMenuAnimationOptions, BindOptions, SheetSize, SheetType, SheetTitleOptions, SheetMode, ScrollSizeMode, UIContext, SheetKeyboardAvoidMode, SourceTool, RectResult, TouchTestStrategy, EventTarget, SourceType, TouchObject, HistoricalPoint, IntentionCode, DragBehavior, Summary, DragResult, DismissPopupAction, DismissContentCoverAction, SheetDismiss, DismissSheetAction, SpringBackAction, DismissReason, LayoutSafeAreaType, LayoutSafeAreaEdge } from "./../ArkCommonInterfaces"
import { Length, SizeOptions, ConstraintSizeOptions, ChainWeightOptions, Padding, LocalizedPadding, Margin, LocalizedMargin, ResourceColor, Position, BorderOptions, EdgeStyles, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, Dimension, EdgeOutlineWidths, OutlineRadiuses, Edges, LocalizedEdges, LocalizedPosition, ResourceStr, AccessibilityOptions, PX, VP, FP, LPX, Percentage, Area, Bias, Font } from "./../ArkUnitsInterfaces"
import { DrawModifier } from "./../ArkDrawModifierMaterialized"
import { HitTestMode, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Color, Visibility, ItemAlign, Direction, GradientDirection, ObscuredReasons, RenderFit, ImageRepeat, Axis, ResponseType, FunctionKey, ModifierKey, PixelRoundCalcPolicy, Curve, PlayMode, TransitionType, HorizontalAlign, VerticalAlign, ClickEffectLevel, SharedTransitionEffectType, Placement, ArrowPointPosition, MouseButton, MouseAction, TouchType, KeyType, KeySource, FontWeight, FontStyle, TitleHeight } from "./../ArkEnumsInterfaces"
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
import { LengthUnit, ShapeSize, PathShapeOptions, RectShapeOptions, RoundRectShapeOptions, TextModifier } from "./../ArkArkuiExternalInterfaces"
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
import { NavDestinationMode, NavigationSystemTransitionType, NavDestinationCommonTitle, NavDestinationCustomTitle, NavDestinationAttribute, RouteMapConfig } from "./../ArkNavDestinationInterfaces"
import { NavigationMenuItem, SystemBarStyle, NavigationTitleOptions, ToolbarItem, NavigationToolbarOptions, BarStyle, ToolbarItemStatus, NavigationOptions, NavigationInterception, PopInfo, LaunchMode, InterceptionShowCallback, InterceptionModeCallback } from "./../ArkNavigationInterfaces"
import { NavDestinationContext } from "./../ArkNavDestinationContextMaterialized"
import { NavPathInfo } from "./../ArkNavPathInfoMaterialized"
import { NavPathStack } from "./../ArkNavPathStackMaterialized"
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
export class ArkNavDestinationPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkNavDestinationPeer {
        const peerId = PeerNode.nextId()
        const _peerPtr = ArkUIGeneratedNativeModule._NavDestination_construct(peerId, flags)
        const _peer = new ArkNavDestinationPeer(_peerPtr, peerId, "NavDestination", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setNavDestinationOptionsAttribute(): void {
        ArkUIGeneratedNativeModule._NavDestinationInterface_setNavDestinationOptions(this.peer.ptr)
    }
    hideTitleBar0Attribute(value: boolean): void {
        ArkUIGeneratedNativeModule._NavDestinationAttribute_hideTitleBar0(this.peer.ptr, +value)
    }
    hideTitleBar1Attribute(hide: boolean, animated: boolean): void {
        ArkUIGeneratedNativeModule._NavDestinationAttribute_hideTitleBar1(this.peer.ptr, +hide, +animated)
    }
    onShownAttribute(value: (() => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._NavDestinationAttribute_onShown(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onHiddenAttribute(value: (() => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._NavDestinationAttribute_onHidden(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onBackPressedAttribute(value: (() => boolean)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._NavDestinationAttribute_onBackPressed(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    modeAttribute(value: NavDestinationMode): void {
        ArkUIGeneratedNativeModule._NavDestinationAttribute_mode(this.peer.ptr, value)
    }
    backButtonIconAttribute(value: ResourceStr | PixelMap | SymbolGlyphModifier): void {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if ((RuntimeType.STRING == value_type) || (RuntimeType.OBJECT == value_type)) {
            thisSerializer.writeInt8(0)
            const value_0 = unsafeCast<ResourceStr>(value)
            let value_0_type: int32 = RuntimeType.UNDEFINED
            value_0_type = runtimeType(value_0)
            if (RuntimeType.STRING == value_0_type) {
                thisSerializer.writeInt8(0)
                const value_0_0 = unsafeCast<string>(value_0)
                thisSerializer.writeString(value_0_0)
            }
            else if (RuntimeType.OBJECT == value_0_type) {
                thisSerializer.writeInt8(1)
                const value_0_1 = unsafeCast<Resource>(value_0)
                thisSerializer.writeResource(value_0_1)
            }
        }
        else if (((RuntimeType.OBJECT) == (value_type)) && ((value!.hasOwnProperty("isEditable")))) {
            thisSerializer.writeInt8(1)
            const value_1 = unsafeCast<PixelMap>(value)
            thisSerializer.writePixelMap(value_1)
        }
        else if (((RuntimeType.OBJECT) == (value_type)) && ((value!.hasOwnProperty("_SymbolGlyphModifierStub")))) {
            thisSerializer.writeInt8(2)
            const value_2 = unsafeCast<SymbolGlyphModifier>(value)
            thisSerializer.writeSymbolGlyphModifier(value_2)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_backButtonIcon(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    menusAttribute(value: Array<NavigationMenuItem> | CustomBuilder): void {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(0)
            const value_0 = unsafeCast<Array<NavigationMenuItem>>(value)
            thisSerializer.writeInt32(value_0.length)
            for (let i = 0; i < value_0.length; i++) {
                const value_0_element: NavigationMenuItem = value_0[i]
                thisSerializer.writeNavigationMenuItem(value_0_element)
            }
        }
        else if (RuntimeType.FUNCTION == value_type) {
            thisSerializer.writeInt8(1)
            const value_1 = unsafeCast<CustomBuilder>(value)
            thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(value_1))
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_menus(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onReadyAttribute(value: ((parameter: NavDestinationContext) => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._NavDestinationAttribute_onReady(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onWillAppearAttribute(value: (() => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._NavDestinationAttribute_onWillAppear(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onWillDisappearAttribute(value: (() => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._NavDestinationAttribute_onWillDisappear(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onWillShowAttribute(value: (() => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._NavDestinationAttribute_onWillShow(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onWillHideAttribute(value: (() => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._NavDestinationAttribute_onWillHide(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    systemBarStyleAttribute(value?: SystemBarStyle): void {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value = value!
            thisSerializer.writeSystemBarStyle(value_value)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_systemBarStyle(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    recoverableAttribute(value?: boolean): void {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_recoverable(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    systemTransitionAttribute(value: NavigationSystemTransitionType): void {
        ArkUIGeneratedNativeModule._NavDestinationAttribute_systemTransition(this.peer.ptr, value)
    }
    titleAttribute(value: string | CustomBuilder | NavDestinationCommonTitle | NavDestinationCustomTitle | Resource, options?: NavigationTitleOptions): void {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(0)
            const value_0 = unsafeCast<string>(value)
            thisSerializer.writeString(value_0)
        }
        else if (RuntimeType.FUNCTION == value_type) {
            thisSerializer.writeInt8(1)
            const value_1 = unsafeCast<CustomBuilder>(value)
            thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(value_1))
        }
        else if (((RuntimeType.OBJECT) == (value_type)) && ((value!.hasOwnProperty("main")))) {
            thisSerializer.writeInt8(2)
            const value_2 = unsafeCast<NavDestinationCommonTitle>(value)
            thisSerializer.writeNavDestinationCommonTitle(value_2)
        }
        else if (((RuntimeType.OBJECT) == (value_type)) && ((value!.hasOwnProperty("builder")))) {
            thisSerializer.writeInt8(3)
            const value_3 = unsafeCast<NavDestinationCustomTitle>(value)
            thisSerializer.writeNavDestinationCustomTitle(value_3)
        }
        else if (((RuntimeType.OBJECT) == (value_type)) && ((value!.hasOwnProperty("bundleName")))) {
            thisSerializer.writeInt8(4)
            const value_4 = unsafeCast<Resource>(value)
            thisSerializer.writeResource(value_4)
        }
        let options_type: int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value = options!
            thisSerializer.writeNavigationTitleOptions(options_value)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_title(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    toolbarConfigurationAttribute(toolbarParam: Array<ToolbarItem> | CustomBuilder, options?: NavigationToolbarOptions): void {
        const thisSerializer: Serializer = Serializer.hold()
        let toolbarParam_type: int32 = RuntimeType.UNDEFINED
        toolbarParam_type = runtimeType(toolbarParam)
        if (RuntimeType.OBJECT == toolbarParam_type) {
            thisSerializer.writeInt8(0)
            const toolbarParam_0 = unsafeCast<Array<ToolbarItem>>(toolbarParam)
            thisSerializer.writeInt32(toolbarParam_0.length)
            for (let i = 0; i < toolbarParam_0.length; i++) {
                const toolbarParam_0_element: ToolbarItem = toolbarParam_0[i]
                thisSerializer.writeToolbarItem(toolbarParam_0_element)
            }
        }
        else if (RuntimeType.FUNCTION == toolbarParam_type) {
            thisSerializer.writeInt8(1)
            const toolbarParam_1 = unsafeCast<CustomBuilder>(toolbarParam)
            thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(toolbarParam_1))
        }
        let options_type: int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value = options!
            thisSerializer.writeNavigationToolbarOptions(options_value)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_toolbarConfiguration(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    hideToolBarAttribute(hide: boolean, animated?: boolean): void {
        const thisSerializer: Serializer = Serializer.hold()
        let animated_type: int32 = RuntimeType.UNDEFINED
        animated_type = runtimeType(animated)
        thisSerializer.writeInt8(animated_type)
        if ((RuntimeType.UNDEFINED) != (animated_type)) {
            const animated_value = animated!
            thisSerializer.writeBoolean(animated_value)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_hideToolBar(this.peer.ptr, +hide, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    ignoreLayoutSafeAreaAttribute(types?: Array<LayoutSafeAreaType>, edges?: Array<LayoutSafeAreaEdge>): void {
        const thisSerializer: Serializer = Serializer.hold()
        let types_type: int32 = RuntimeType.UNDEFINED
        types_type = runtimeType(types)
        thisSerializer.writeInt8(types_type)
        if ((RuntimeType.UNDEFINED) != (types_type)) {
            const types_value = types!
            thisSerializer.writeInt32(types_value.length)
            for (let i = 0; i < types_value.length; i++) {
                const types_value_element: LayoutSafeAreaType = types_value[i]
                thisSerializer.writeInt32(types_value_element)
            }
        }
        let edges_type: int32 = RuntimeType.UNDEFINED
        edges_type = runtimeType(edges)
        thisSerializer.writeInt8(edges_type)
        if ((RuntimeType.UNDEFINED) != (edges_type)) {
            const edges_value = edges!
            thisSerializer.writeInt32(edges_value.length)
            for (let i = 0; i < edges_value.length; i++) {
                const edges_value_element: LayoutSafeAreaEdge = edges_value[i]
                thisSerializer.writeInt32(edges_value_element)
            }
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_ignoreLayoutSafeArea(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface ArkNavDestinationAttributes extends ArkCommonMethodAttributes {
    hideTitleBar?: boolean
    onShown?: (() => void)
    onHidden?: (() => void)
    onBackPressed?: (() => boolean)
    mode?: NavDestinationMode
    backButtonIcon?: ResourceStr | PixelMap | SymbolGlyphModifier
    menus?: Array<NavigationMenuItem> | CustomBuilder
    onReady?: ((parameter: NavDestinationContext) => void)
    onWillAppear?: (() => void)
    onWillDisappear?: (() => void)
    onWillShow?: (() => void)
    onWillHide?: (() => void)
    systemBarStyle?: SystemBarStyle | undefined
    recoverable?: boolean | undefined
    systemTransition?: NavigationSystemTransitionType
}
