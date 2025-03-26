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
import { nullptr, KPointer, KInt, KBoolean, KStringPtr, runtimeType, RuntimeType, MaterializedBase, toPeerPtr, wrapCallback } from "@koalaui/interop"
import { Serializer } from "./Serializer"
import { ComponentBase } from "./../../ComponentBase"
import { PeerNode } from "./../../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonMethodPeer, ArkCommonMethodAttributes } from "./ArkCommonPeer"
import { CommonMethod, Rectangle, TouchTestInfo, TouchResult, PixelRoundPolicy, BackgroundEffectOptions, ForegroundEffectOptions, VisualEffect, Filter, BorderImageOption, OutlineStyle, AccessibilityCallback, AnimateParam, TransitionOptions, MotionBlurOptions, InvertOptions, TranslateOptions, ScaleOptions, RotateOptions, AlignRuleOption, LocalizedAlignRuleOptions, ClickEffect, CustomBuilder, DragItemInfo, UniformDataType, PreDragStatus, MotionPathOptions, ShadowOptions, ShadowStyle, StateStyles, PixelStretchEffectOptions, BackgroundBrightnessOptions, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, SizeChangeCallback, SafeAreaType, SafeAreaEdge, BlurStyle, BackgroundBlurStyleOptions, ForegroundBlurStyleOptions, TransitionFinishCallback, BlurOptions, LinearGradientBlurOptions, EffectType, sharedTransitionOptions, ChainStyle, DragPreviewOptions, DragInteractionOptions, ComponentContent, OverlayOptions, BlendMode, BlendApplyType, Blender, GeometryTransitionOptions, PopupOptions, CustomPopupOptions, MenuElement, MenuOptions, ContextMenuOptions, ModalTransition, ContentCoverOptions, SheetOptions, VisibleAreaChangeCallback, SymbolGlyphModifier, LayoutSafeAreaType, LayoutSafeAreaEdge } from "./../ArkCommonInterfaces"
import { Length, SizeOptions, ConstraintSizeOptions, ChainWeightOptions, Padding, LocalizedPadding, Margin, LocalizedMargin, ResourceColor, Position, BorderOptions, EdgeStyles, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, Dimension, EdgeOutlineWidths, OutlineRadiuses, Area, Edges, LocalizedEdges, LocalizedPosition, ResourceStr, AccessibilityOptions, PX, VP, FP, LPX, Percentage } from "./../ArkUnitsInterfaces"
import { DrawModifier } from "./../ArkDrawModifierMaterialized"
import { HitTestMode, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Color, Visibility, ItemAlign, Direction, GradientDirection, ObscuredReasons, RenderFit, ImageRepeat, Axis, ResponseType, FunctionKey, ModifierKey } from "./../ArkEnumsInterfaces"
import { Callback_Array_TouchTestInfo_TouchResult, Callback_ClickEvent_Void, Callback_Boolean_HoverEvent_Void, Callback_MouseEvent_Void, Callback_TouchEvent_Void, Callback_KeyEvent_Void, Callback_KeyEvent_Boolean, Callback_Void, Callback_Area_Area_Void, Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs, Literal_Number_offset_span, Callback_DragEvent_String_Union_CustomBuilder_DragItemInfo, Callback_DragEvent_String_Void, Callback_PreDragStatus_Void, Type_CommonMethod_linearGradient_value, Tuple_ResourceColor_Number, Type_CommonMethod_sweepGradient_value, Tuple_Length_Length, Type_CommonMethod_radialGradient_value, Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult, Callback_TouchEvent_HitTestMode, Literal_Alignment_align, Callback_Boolean, Callback_NavDestinationContext_Void } from "./../SyntheticDeclarations"
import { LengthMetrics } from "./../ArkLengthMetricsMaterialized"
import { ResizableOptions } from "./../ArkImageInterfaces"
import { Resource } from "./../ArkResourceInterfaces"
import { ClickEvent } from "./../ArkClickEventMaterialized"
import { HoverEvent } from "./../ArkHoverEventMaterialized"
import { MouseEvent } from "./../ArkMouseEventMaterialized"
import { TouchEvent } from "./../ArkTouchEventMaterialized"
import { KeyEvent } from "./../ArkKeyEventMaterialized"
import { FocusBoxStyle, FocusPriority } from "./../ArkFocusInterfaces"
import { TransitionEffect } from "./../ArkTransitionEffectMaterialized"
import { DragEvent } from "./../ArkDragEventMaterialized"
import { CircleShape } from "./../ArkCircleShapeMaterialized"
import { EllipseShape } from "./../ArkEllipseShapeMaterialized"
import { PathShape } from "./../ArkPathShapeMaterialized"
import { RectShape } from "./../ArkRectShapeMaterialized"
import { ProgressMask } from "./../ArkProgressMaskMaterialized"
import { AttributeModifier } from "./../../handwritten"
import { GestureModifier } from "./../ArkGestureModifierMaterialized"
import { GestureInfo, GestureJudgeResult, GestureType, GestureMask } from "./../ArkGestureInterfaces"
import { BaseGestureEvent } from "./../ArkBaseGestureEventMaterialized"
import { PixelMap } from "./../ArkPixelMapMaterialized"
import { NavDestinationMode, NavigationSystemTransitionType, NavDestinationCommonTitle, NavDestinationCustomTitle, NavDestinationAttribute } from "./../ArkNavDestinationInterfaces"
import { NavigationMenuItem, SystemBarStyle, NavigationTitleOptions, ToolbarItem, NavigationToolbarOptions } from "./../ArkNavigationInterfaces"
import { NavDestinationContext } from "./../ArkNavDestinationContextMaterialized"
import { TapGestureInterface } from "./../ArkTapGestureInterfaceMaterialized"
import { LongPressGestureInterface } from "./../ArkLongPressGestureInterfaceMaterialized"
import { PanGestureInterface } from "./../ArkPanGestureInterfaceMaterialized"
import { PinchGestureInterface } from "./../ArkPinchGestureInterfaceMaterialized"
import { SwipeGestureInterface } from "./../ArkSwipeGestureInterfaceMaterialized"
import { RotationGestureInterface } from "./../ArkRotationGestureInterfaceMaterialized"
import { GestureGroupInterface } from "./../ArkGestureGroupInterfaceMaterialized"
import { CallbackKind } from "./CallbackKind"
import { CallbackTransformer } from "./CallbackTransformer"
import { DotIndicator } from "./../ArkDotIndicatorBuilder"
import { DigitIndicator } from "./../ArkDigitIndicatorBuilder"
import { SubTabBarStyle } from "./../ArkSubTabBarStyleBuilder"
import { BottomTabBarStyle } from "./../ArkBottomTabBarStyleBuilder"
export class ArkNavDestinationPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkNavDestinationPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._NavDestination_construct(peerId, flags)
        const _peer  = new ArkNavDestinationPeer(_peerPtr, peerId, "NavDestination", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setNavDestinationOptionsAttribute(): void {
        ArkUIGeneratedNativeModule._NavDestinationInterface_setNavDestinationOptions(this.peer.ptr)
    }
    hideTitleBar0Attribute(value: boolean): void {
        ArkUIGeneratedNativeModule._NavDestinationAttribute_hideTitleBar0(this.peer.ptr, value ? 1 : 0)
    }
    hideTitleBar1Attribute(hide: boolean, animated: boolean): void {
        ArkUIGeneratedNativeModule._NavDestinationAttribute_hideTitleBar1(this.peer.ptr, hide ? 1 : 0, animated ? 1 : 0)
    }
    onShownAttribute(value: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._NavDestinationAttribute_onShown(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onHiddenAttribute(value: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._NavDestinationAttribute_onHidden(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onBackPressedAttribute(value: (() => boolean)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._NavDestinationAttribute_onBackPressed(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    modeAttribute(value: NavDestinationMode): void {
        ArkUIGeneratedNativeModule._NavDestinationAttribute_mode(this.peer.ptr, value.valueOf())
    }
    backButtonIconAttribute(value: ResourceStr | PixelMap | SymbolGlyphModifier): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if ((RuntimeType.STRING == value_type) || (RuntimeType.OBJECT == value_type)) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as ResourceStr
            let value_0_type : int32 = RuntimeType.UNDEFINED
            value_0_type = runtimeType(value_0)
            if (RuntimeType.STRING == value_0_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_0_0  = value_0 as string
                thisSerializer.writeString(value_0_0)
            }
            else if (RuntimeType.OBJECT == value_0_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_0_1  = value_0 as Resource
                thisSerializer.writeResource(value_0_1)
            }
        }
        else if (TypeChecker.isPixelMap(value, false, false)) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as PixelMap
            thisSerializer.writePixelMap(value_1)
        }
        else if (TypeChecker.isSymbolGlyphModifier(value, false)) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as SymbolGlyphModifier
            thisSerializer.writeSymbolGlyphModifier(value_2)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_backButtonIcon(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    menusAttribute(value: Array<NavigationMenuItem> | CustomBuilder): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as Array<NavigationMenuItem>
            thisSerializer.writeInt32(value_0.length as int32)
            for (let i = 0; i < value_0.length; i++) {
                const value_0_element : NavigationMenuItem = value_0[i]
                thisSerializer.writeNavigationMenuItem(value_0_element)
            }
        }
        else if (RuntimeType.FUNCTION == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as CustomBuilder
            thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(value_1))
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_menus(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onReadyAttribute(value: ((parameter: NavDestinationContext) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._NavDestinationAttribute_onReady(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onWillAppearAttribute(value: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._NavDestinationAttribute_onWillAppear(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onWillDisappearAttribute(value: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._NavDestinationAttribute_onWillDisappear(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onWillShowAttribute(value: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._NavDestinationAttribute_onWillShow(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onWillHideAttribute(value: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._NavDestinationAttribute_onWillHide(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    systemBarStyleAttribute(value?: SystemBarStyle): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeSystemBarStyle(value_value)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_systemBarStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    recoverableAttribute(value?: boolean): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_recoverable(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    systemTransitionAttribute(value: NavigationSystemTransitionType): void {
        ArkUIGeneratedNativeModule._NavDestinationAttribute_systemTransition(this.peer.ptr, value.valueOf())
    }
    titleAttribute(value: string | CustomBuilder | NavDestinationCommonTitle | NavDestinationCustomTitle | Resource, options?: NavigationTitleOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as string
            thisSerializer.writeString(value_0)
        }
        else if (RuntimeType.FUNCTION == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as CustomBuilder
            thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(value_1))
        }
        else if (TypeChecker.isNavDestinationCommonTitle(value, false, false)) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as NavDestinationCommonTitle
            thisSerializer.writeNavDestinationCommonTitle(value_2)
        }
        else if (TypeChecker.isNavDestinationCustomTitle(value, false, false)) {
            thisSerializer.writeInt8(3 as int32)
            const value_3  = value as NavDestinationCustomTitle
            thisSerializer.writeNavDestinationCustomTitle(value_3)
        }
        else if (TypeChecker.isResource(value, false, false, false, false, false)) {
            thisSerializer.writeInt8(4 as int32)
            const value_4  = value as Resource
            thisSerializer.writeResource(value_4)
        }
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeNavigationTitleOptions(options_value)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_title(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    toolbarConfigurationAttribute(toolbarParam: Array<ToolbarItem> | CustomBuilder, options?: NavigationToolbarOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let toolbarParam_type : int32 = RuntimeType.UNDEFINED
        toolbarParam_type = runtimeType(toolbarParam)
        if (RuntimeType.OBJECT == toolbarParam_type) {
            thisSerializer.writeInt8(0 as int32)
            const toolbarParam_0  = toolbarParam as Array<ToolbarItem>
            thisSerializer.writeInt32(toolbarParam_0.length as int32)
            for (let i = 0; i < toolbarParam_0.length; i++) {
                const toolbarParam_0_element : ToolbarItem = toolbarParam_0[i]
                thisSerializer.writeToolbarItem(toolbarParam_0_element)
            }
        }
        else if (RuntimeType.FUNCTION == toolbarParam_type) {
            thisSerializer.writeInt8(1 as int32)
            const toolbarParam_1  = toolbarParam as CustomBuilder
            thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(toolbarParam_1))
        }
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeNavigationToolbarOptions(options_value)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_toolbarConfiguration(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    hideToolBarAttribute(hide: boolean, animated?: boolean): void {
        const thisSerializer : Serializer = Serializer.hold()
        let animated_type : int32 = RuntimeType.UNDEFINED
        animated_type = runtimeType(animated)
        thisSerializer.writeInt8(animated_type as int32)
        if ((RuntimeType.UNDEFINED) != (animated_type)) {
            const animated_value  = animated!
            thisSerializer.writeBoolean(animated_value)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_hideToolBar(this.peer.ptr, hide ? 1 : 0, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    ignoreLayoutSafeAreaAttribute(types?: Array<LayoutSafeAreaType>, edges?: Array<LayoutSafeAreaEdge>): void {
        const thisSerializer : Serializer = Serializer.hold()
        let types_type : int32 = RuntimeType.UNDEFINED
        types_type = runtimeType(types)
        thisSerializer.writeInt8(types_type as int32)
        if ((RuntimeType.UNDEFINED) != (types_type)) {
            const types_value  = types!
            thisSerializer.writeInt32(types_value.length as int32)
            for (let i = 0; i < types_value.length; i++) {
                const types_value_element : LayoutSafeAreaType = types_value[i]
                thisSerializer.writeInt32(types_value_element.valueOf())
            }
        }
        let edges_type : int32 = RuntimeType.UNDEFINED
        edges_type = runtimeType(edges)
        thisSerializer.writeInt8(edges_type as int32)
        if ((RuntimeType.UNDEFINED) != (edges_type)) {
            const edges_value  = edges!
            thisSerializer.writeInt32(edges_value.length as int32)
            for (let i = 0; i < edges_value.length; i++) {
                const edges_value_element : LayoutSafeAreaEdge = edges_value[i]
                thisSerializer.writeInt32(edges_value_element.valueOf())
            }
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_ignoreLayoutSafeArea(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
