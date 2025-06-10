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
import { KStringPtr, KBoolean, RuntimeType, runtimeType } from "@koalaui/interop"
import { NodeAttach, remember } from "@koalaui/runtime"
import { ComponentBase } from "./../ComponentBase"
import { TypeChecker } from "#components"
import { ArkCommonMethodComponent } from "./ArkCommon"
import { ArkNavDestinationPeer } from "./peers/ArkNavDestinationPeer"
import { CommonMethod, Rectangle, TouchTestInfo, TouchResult, PixelRoundPolicy, BackgroundEffectOptions, ForegroundEffectOptions, VisualEffect, Filter, BorderImageOption, OutlineStyle, AccessibilityCallback, AnimateParam, TransitionOptions, MotionBlurOptions, InvertOptions, TranslateOptions, ScaleOptions, RotateOptions, AlignRuleOption, LocalizedAlignRuleOptions, ClickEffect, CustomBuilder, DragItemInfo, UniformDataType, PreDragStatus, MotionPathOptions, ShadowOptions, ShadowStyle, StateStyles, PixelStretchEffectOptions, BackgroundBrightnessOptions, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, SizeChangeCallback, SafeAreaType, SafeAreaEdge, BlurStyle, BackgroundBlurStyleOptions, ForegroundBlurStyleOptions, TransitionFinishCallback, BlurOptions, LinearGradientBlurOptions, EffectType, sharedTransitionOptions, ChainStyle, DragPreviewOptions, DragInteractionOptions, ComponentContent, OverlayOptions, BlendMode, BlendApplyType, Blender, GeometryTransitionOptions, PopupOptions, CustomPopupOptions, MenuElement, MenuOptions, ContextMenuOptions, ModalTransition, ContentCoverOptions, SheetOptions, VisibleAreaChangeCallback, SymbolGlyphModifier, LayoutSafeAreaType, LayoutSafeAreaEdge } from "./ArkCommonInterfaces"
import { Length, SizeOptions, ConstraintSizeOptions, ChainWeightOptions, Padding, LocalizedPadding, Margin, LocalizedMargin, ResourceColor, Position, BorderOptions, EdgeStyles, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, Dimension, EdgeOutlineWidths, OutlineRadiuses, Area, Edges, LocalizedEdges, LocalizedPosition, ResourceStr, AccessibilityOptions } from "./ArkUnitsInterfaces"
import { DrawModifier } from "./ArkDrawModifierMaterialized"
import { HitTestMode, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Color, Visibility, ItemAlign, Direction, GradientDirection, ObscuredReasons, RenderFit, ImageRepeat, Axis, ResponseType, FunctionKey, ModifierKey } from "./ArkEnumsInterfaces"
import { Callback_Array_TouchTestInfo_TouchResult, Callback_ClickEvent_Void, Callback_Boolean_HoverEvent_Void, Callback_MouseEvent_Void, Callback_TouchEvent_Void, Callback_KeyEvent_Void, Callback_KeyEvent_Boolean, Callback_Void, Callback_Area_Area_Void, Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs, Literal_Number_offset_span, Callback_DragEvent_String_Union_CustomBuilder_DragItemInfo, Callback_DragEvent_String_Void, Callback_PreDragStatus_Void, Type_CommonMethod_linearGradient_value, Tuple_ResourceColor_Number, Type_CommonMethod_sweepGradient_value, Tuple_Length_Length, Type_CommonMethod_radialGradient_value, Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult, Callback_TouchEvent_HitTestMode, Literal_Alignment_align, Callback_Boolean, Callback_NavDestinationContext_Void } from "./SyntheticDeclarations"
import { LengthMetrics } from "./ArkLengthMetricsMaterialized"
import { ResizableOptions } from "./ArkImageInterfaces"
import { Resource } from "./ArkResourceInterfaces"
import { ClickEvent } from "./ArkClickEventMaterialized"
import { HoverEvent } from "./ArkHoverEventMaterialized"
import { MouseEvent } from "./ArkMouseEventMaterialized"
import { TouchEvent } from "./ArkTouchEventMaterialized"
import { KeyEvent } from "./ArkKeyEventMaterialized"
import { FocusBoxStyle, FocusPriority } from "./ArkFocusInterfaces"
import { TransitionEffect } from "./ArkTransitionEffectMaterialized"
import { DragEvent } from "./ArkDragEventMaterialized"
import { CircleShape } from "./ArkCircleShapeMaterialized"
import { EllipseShape } from "./ArkEllipseShapeMaterialized"
import { PathShape } from "./ArkPathShapeMaterialized"
import { RectShape } from "./ArkRectShapeMaterialized"
import { ProgressMask } from "./ArkProgressMaskMaterialized"
import { AttributeModifier } from "./../handwritten"
import { GestureModifier } from "./ArkGestureModifierMaterialized"
import { GestureInfo, GestureJudgeResult, GestureType, GestureMask } from "./ArkGestureInterfaces"
import { BaseGestureEvent } from "./ArkBaseGestureEventMaterialized"
import { PixelMap } from "./ArkPixelMapMaterialized"
import { NavDestinationMode, NavigationSystemTransitionType, NavDestinationCommonTitle, NavDestinationCustomTitle, NavDestinationAttribute } from "./ArkNavDestinationInterfaces"
import { NavigationMenuItem, SystemBarStyle, NavigationTitleOptions, ToolbarItem, NavigationToolbarOptions } from "./ArkNavigationInterfaces"
import { NavDestinationContext } from "./ArkNavDestinationContextMaterialized"
/** @memo:stable */
export class ArkNavDestinationComponent extends ArkCommonMethodComponent {
    getPeer(): ArkNavDestinationPeer {
        return (this.peer as ArkNavDestinationPeer)
    }
    /** @memo */
    public setNavDestinationOptions(): this {
        if (this.checkPriority("setNavDestinationOptions")) {
            this.getPeer()?.setNavDestinationOptionsAttribute()
            return this
        }
        return this
    }
    /** @memo */
    public hideTitleBar(hide: boolean, animated?: boolean): this {
        if (this.checkPriority("hideTitleBar")) {
            const hide_type = runtimeType(hide)
            const animated_type = runtimeType(animated)
            if (RuntimeType.UNDEFINED == animated_type) {
                const value_casted = hide as (boolean)
                this.getPeer()?.hideTitleBar0Attribute(value_casted)
                return this
            }
            if (RuntimeType.BOOLEAN == animated_type) {
                const hide_casted = hide as (boolean)
                const animated_casted = animated as (boolean)
                this.getPeer()?.hideTitleBar1Attribute(hide_casted, animated_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    /** @memo */
    public onShown(value: (() => void)): this {
        if (this.checkPriority("onShown")) {
            const value_casted = value as ((() => void))
            this.getPeer()?.onShownAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onHidden(value: (() => void)): this {
        if (this.checkPriority("onHidden")) {
            const value_casted = value as ((() => void))
            this.getPeer()?.onHiddenAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onBackPressed(value: (() => boolean)): this {
        if (this.checkPriority("onBackPressed")) {
            const value_casted = value as ((() => boolean))
            this.getPeer()?.onBackPressedAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public mode(value: NavDestinationMode): this {
        if (this.checkPriority("mode")) {
            const value_casted = value as (NavDestinationMode)
            this.getPeer()?.modeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public backButtonIcon(value: ResourceStr | PixelMap | SymbolGlyphModifier): this {
        if (this.checkPriority("backButtonIcon")) {
            const value_casted = value as (ResourceStr | PixelMap | SymbolGlyphModifier)
            this.getPeer()?.backButtonIconAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public menus(value: Array<NavigationMenuItem> | CustomBuilder): this {
        if (this.checkPriority("menus")) {
            const value_casted = value as (Array<NavigationMenuItem> | CustomBuilder)
            this.getPeer()?.menusAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onReady(value: ((parameter: NavDestinationContext) => void)): this {
        if (this.checkPriority("onReady")) {
            const value_casted = value as (((parameter: NavDestinationContext) => void))
            this.getPeer()?.onReadyAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onWillAppear(value: (() => void)): this {
        if (this.checkPriority("onWillAppear")) {
            const value_casted = value as ((() => void))
            this.getPeer()?.onWillAppearAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onWillDisappear(value: (() => void)): this {
        if (this.checkPriority("onWillDisappear")) {
            const value_casted = value as ((() => void))
            this.getPeer()?.onWillDisappearAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onWillShow(value: (() => void)): this {
        if (this.checkPriority("onWillShow")) {
            const value_casted = value as ((() => void))
            this.getPeer()?.onWillShowAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onWillHide(value: (() => void)): this {
        if (this.checkPriority("onWillHide")) {
            const value_casted = value as ((() => void))
            this.getPeer()?.onWillHideAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public systemBarStyle(value?: SystemBarStyle): this {
        if (this.checkPriority("systemBarStyle")) {
            const value_casted = value as (SystemBarStyle | undefined)
            this.getPeer()?.systemBarStyleAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public recoverable(value?: boolean): this {
        if (this.checkPriority("recoverable")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.recoverableAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public systemTransition(value: NavigationSystemTransitionType): this {
        if (this.checkPriority("systemTransition")) {
            const value_casted = value as (NavigationSystemTransitionType)
            this.getPeer()?.systemTransitionAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public title(value: string | CustomBuilder | NavDestinationCommonTitle | NavDestinationCustomTitle | Resource, options?: NavigationTitleOptions): this {
        if (this.checkPriority("title")) {
            const value_casted = value as (string | CustomBuilder | NavDestinationCommonTitle | NavDestinationCustomTitle | Resource)
            const options_casted = options as (NavigationTitleOptions | undefined)
            this.getPeer()?.titleAttribute(value_casted, options_casted)
            return this
        }
        return this
    }
    /** @memo */
    public toolbarConfiguration(toolbarParam: Array<ToolbarItem> | CustomBuilder, options?: NavigationToolbarOptions): this {
        if (this.checkPriority("toolbarConfiguration")) {
            const toolbarParam_casted = toolbarParam as (Array<ToolbarItem> | CustomBuilder)
            const options_casted = options as (NavigationToolbarOptions | undefined)
            this.getPeer()?.toolbarConfigurationAttribute(toolbarParam_casted, options_casted)
            return this
        }
        return this
    }
    /** @memo */
    public hideToolBar(hide: boolean, animated?: boolean): this {
        if (this.checkPriority("hideToolBar")) {
            const hide_casted = hide as (boolean)
            const animated_casted = animated as (boolean | undefined)
            this.getPeer()?.hideToolBarAttribute(hide_casted, animated_casted)
            return this
        }
        return this
    }
    /** @memo */
    public ignoreLayoutSafeArea(types?: Array<LayoutSafeAreaType>, edges?: Array<LayoutSafeAreaEdge>): this {
        if (this.checkPriority("ignoreLayoutSafeArea")) {
            const types_casted = types as (Array<LayoutSafeAreaType> | undefined)
            const edges_casted = edges as (Array<LayoutSafeAreaEdge> | undefined)
            this.getPeer()?.ignoreLayoutSafeAreaAttribute(types_casted, edges_casted)
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
export function ArkNavDestination(
  /** @memo */
  style: ((attributes: ArkNavDestinationComponent) => void) | undefined,
  /** @memo */
  content_: (() => void) | undefined,
  
) {
    const receiver = remember(() => {
        return new ArkNavDestinationComponent()
    })
    NodeAttach<ArkNavDestinationPeer>((): ArkNavDestinationPeer => ArkNavDestinationPeer.create(receiver), (_: ArkNavDestinationPeer) => {
        receiver.setNavDestinationOptions()
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
