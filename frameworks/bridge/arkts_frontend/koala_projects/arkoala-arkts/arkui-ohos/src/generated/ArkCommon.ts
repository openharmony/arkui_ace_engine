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
import { ComponentBase } from "../ComponentBase"
import { TypeChecker } from "#components"
import { InteropNativeModule } from "@koalaui/interop"
import { ArkCommonMethodPeer, ArkCommonShapeMethodPeer, ArkCommonPeer, ArkScrollableCommonMethodPeer } from "./peers/ArkCommonPeer"
import { Length, SizeOptions, ConstraintSizeOptions, ChainWeightOptions, Padding, LocalizedPadding, Margin, LocalizedMargin, ResourceColor, Position, BorderOptions, EdgeStyles, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, Dimension, EdgeOutlineWidths, OutlineRadiuses, Area, Edges, LocalizedEdges, LocalizedPosition, ResourceStr, AccessibilityOptions } from "./../component/units"
import { DrawModifier, Rectangle, Callback_Array_TouchTestInfo_TouchResult, TouchTestInfo, TouchResult, PixelRoundPolicy, BackgroundEffectOptions, ForegroundEffectOptions, VisualEffect, Filter, BorderImageOption, OutlineStyle, Callback_ClickEvent_Void, ClickEvent, Callback_Boolean_HoverEvent_Void, HoverEvent, AccessibilityCallback, Callback_MouseEvent_Void, MouseEvent, Callback_TouchEvent_Void, TouchEvent, Callback_KeyEvent_Void, KeyEvent, Callback_KeyEvent_Boolean, AnimateParam, TransitionOptions, TransitionEffect, MotionBlurOptions, InvertOptions, TranslateOptions, ScaleOptions, RotateOptions, Callback_Area_Area_Void, Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs, Literal_Number_offset_span, AlignRuleOption, LocalizedAlignRuleOptions, ClickEffect, Callback_DragEvent_String_Union_CustomBuilder_DragItemInfo, DragEvent, CustomBuilder, DragItemInfo, Callback_DragEvent_String_Void, UniformDataType, Callback_PreDragStatus_Void, PreDragStatus, Type_CommonMethod_linearGradient_value, Tuple_ResourceColor_Number, Type_CommonMethod_sweepGradient_value, Tuple_Length_Length, Type_CommonMethod_radialGradient_value, MotionPathOptions, ShadowOptions, ShadowStyle, ProgressMask, StateStyles, PixelStretchEffectOptions, GestureModifier, BackgroundBrightnessOptions, Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, Callback_TouchEvent_HitTestMode, SizeChangeCallback, SafeAreaType, SafeAreaEdge, Literal_Alignment_align, BlurStyle, BackgroundBlurStyleOptions, ForegroundBlurStyleOptions, TransitionFinishCallback, BlurOptions, LinearGradientBlurOptions, EffectType, sharedTransitionOptions, ChainStyle, DragPreviewOptions, DragInteractionOptions, ComponentContent, OverlayOptions, BlendMode, BlendApplyType, Blender, GeometryTransitionOptions, PopupOptions, CustomPopupOptions, MenuElement, MenuOptions, ContextMenuOptions, ModalTransition, ContentCoverOptions, SheetOptions, VisibleAreaChangeCallback, CommonMethod, CommonAttribute, NestedScrollOptions, ContentClipMode, EdgeEffectOptions, FadingEdgeOptions, CommonShapeMethod, ScrollableCommonMethod, CommonInteface } from "./../component/common"
import { HitTestMode, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Color, Visibility, ItemAlign, Direction, GradientDirection, ObscuredReasons, RenderFit, ImageRepeat, Axis, ResponseType, FunctionKey, ModifierKey, LineCapStyle, LineJoinStyle, BarState, EdgeEffect } from "./../component/enums"
import { LengthMetrics } from "../Graphics"
import { ResizableOptions } from "./../component/image"
import { Resource } from "global/resource";
import { Callback_Void } from "./../component/abilityComponent"
import { FocusBoxStyle, FocusPriority } from "./../component/focus"
import { CircleShape } from "./ArkCircleShapeMaterialized"
import { EllipseShape } from "./ArkEllipseShapeMaterialized"
import { PathShape } from "./ArkPathShapeMaterialized"
import { RectShape } from "./ArkRectShapeMaterialized"
import { AttributeModifier } from "./../component/common"
import { GestureInfo, BaseGestureEvent, GestureJudgeResult, GestureType, GestureMask } from "./../component/gesture"
import { PixelMap } from "./ArkPixelMapMaterialized"
import { Callback_Number_Number_Void } from "./../component/grid"
import { ScrollOnWillScrollCallback, ScrollOnScrollCallback } from "./../component/scroll"
import { ArkCommonAttributeSet, applyUIAttributes } from "../handwritten/modifiers/ArkCommonModifier"
import { CommonModifier } from "../CommonModifier"
import { AttributeUpdater } from "../ohos.arkui.modifier"
import { ArkBaseNode } from "../handwritten/modifiers/ArkBaseNode"
/** @memo:stable */
export class ArkCommonMethodComponent extends ComponentBase implements CommonMethod {

    constructParam(...param: Object[]): this {
        return this;
    }
    constructFunction: ((...param: object[]) => void) | undefined

    protected _modifierHost: ArkBaseNode | undefined
    protected _attributeModifier: AttributeModifier<CommonAttribute> | undefined

    setModifierHost(value: ArkBaseNode): void {
        this._modifierHost = value
    }

    getModifierHost(): ArkBaseNode {
        if (this._modifierHost === undefined || this._modifierHost === null) {
            this._modifierHost = new ArkBaseNode()
            this._modifierHost!.setPeer(this.getPeer())
        }
        return this._modifierHost!
    }

    getPeer(): ArkCommonMethodPeer {
        return (this.peer as ArkCommonMethodPeer)
    }
    /** @memo */
    public width(value: Length): this {
        if (this.checkPriority("width")) {
            const value_casted = value as (Length)
            this.getPeer()?.widthAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public height(value: Length): this {
        if (this.checkPriority("height")) {
            const value_casted = value as (Length)
            this.getPeer()?.heightAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public drawModifier(value?: DrawModifier): this {
        if (this.checkPriority("drawModifier")) {
            const value_casted = value as (DrawModifier | undefined)
            this.getPeer()?.drawModifierAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public responseRegion(value: Array<Rectangle> | Rectangle): this {
        if (this.checkPriority("responseRegion")) {
            const value_casted = value as (Array<Rectangle> | Rectangle)
            this.getPeer()?.responseRegionAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public mouseResponseRegion(value: Array<Rectangle> | Rectangle): this {
        if (this.checkPriority("mouseResponseRegion")) {
            const value_casted = value as (Array<Rectangle> | Rectangle)
            this.getPeer()?.mouseResponseRegionAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public size(value: SizeOptions): this {
        if (this.checkPriority("size")) {
            const value_casted = value as (SizeOptions)
            this.getPeer()?.sizeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public constraintSize(value: ConstraintSizeOptions): this {
        if (this.checkPriority("constraintSize")) {
            const value_casted = value as (ConstraintSizeOptions)
            this.getPeer()?.constraintSizeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public touchable(value: boolean): this {
        if (this.checkPriority("touchable")) {
            const value_casted = value as (boolean)
            this.getPeer()?.touchableAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public hitTestBehavior(value: HitTestMode): this {
        if (this.checkPriority("hitTestBehavior")) {
            const value_casted = value as (HitTestMode)
            this.getPeer()?.hitTestBehaviorAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onChildTouchTest(value: ((value: Array<TouchTestInfo>) => TouchResult)): this {
        if (this.checkPriority("onChildTouchTest")) {
            const value_casted = value as (((value: Array<TouchTestInfo>) => TouchResult))
            this.getPeer()?.onChildTouchTestAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public layoutWeight(value: number | string): this {
        if (this.checkPriority("layoutWeight")) {
            const value_casted = value as (number | string)
            this.getPeer()?.layoutWeightAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public chainWeight(value: ChainWeightOptions): this {
        if (this.checkPriority("chainWeight")) {
            const value_casted = value as (ChainWeightOptions)
            this.getPeer()?.chainWeightAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public padding(value: Padding | Length | LocalizedPadding): this {
        if (this.checkPriority("padding")) {
            const value_casted = value as (Padding | Length | LocalizedPadding)
            this.getPeer()?.paddingAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public safeAreaPadding(value: Padding | LengthMetrics | LocalizedPadding): this {
        if (this.checkPriority("safeAreaPadding")) {
            const value_casted = value as (Padding | LengthMetrics | LocalizedPadding)
            this.getPeer()?.safeAreaPaddingAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public margin(value: Margin | Length | LocalizedMargin): this {
        if (this.checkPriority("margin")) {
            const value_casted = value as (Margin | Length | LocalizedMargin)
            this.getPeer()?.marginAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public backgroundColor(value: ResourceColor): this {
        if (this.checkPriority("backgroundColor")) {
            const value_casted = value as (ResourceColor)
            this.getPeer()?.backgroundColorAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public pixelRound(value: PixelRoundPolicy): this {
        if (this.checkPriority("pixelRound")) {
            const value_casted = value as (PixelRoundPolicy)
            this.getPeer()?.pixelRoundAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public backgroundImageSize(value: SizeOptions | ImageSize): this {
        if (this.checkPriority("backgroundImageSize")) {
            const value_casted = value as (SizeOptions | ImageSize)
            this.getPeer()?.backgroundImageSizeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public backgroundImagePosition(value: Position | Alignment): this {
        if (this.checkPriority("backgroundImagePosition")) {
            const value_casted = value as (Position | Alignment)
            this.getPeer()?.backgroundImagePositionAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public backgroundEffect(value: BackgroundEffectOptions): this {
        if (this.checkPriority("backgroundEffect")) {
            const value_casted = value as (BackgroundEffectOptions)
            this.getPeer()?.backgroundEffectAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public backgroundImageResizable(value: ResizableOptions): this {
        if (this.checkPriority("backgroundImageResizable")) {
            const value_casted = value as (ResizableOptions)
            this.getPeer()?.backgroundImageResizableAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public foregroundEffect(value: ForegroundEffectOptions): this {
        if (this.checkPriority("foregroundEffect")) {
            const value_casted = value as (ForegroundEffectOptions)
            this.getPeer()?.foregroundEffectAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public visualEffect(value: VisualEffect): this {
        if (this.checkPriority("visualEffect")) {
            const value_casted = value as (VisualEffect)
            this.getPeer()?.visualEffectAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public backgroundFilter(value: Filter): this {
        if (this.checkPriority("backgroundFilter")) {
            const value_casted = value as (Filter)
            this.getPeer()?.backgroundFilterAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public foregroundFilter(value: Filter): this {
        if (this.checkPriority("foregroundFilter")) {
            const value_casted = value as (Filter)
            this.getPeer()?.foregroundFilterAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public compositingFilter(value: Filter): this {
        if (this.checkPriority("compositingFilter")) {
            const value_casted = value as (Filter)
            this.getPeer()?.compositingFilterAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public opacity(value: number | Resource): this {
        if (this.checkPriority("opacity")) {
            const value_casted = value as (number | Resource)
            this.getPeer()?.opacityAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public border(value: BorderOptions): this {
        if (this.checkPriority("border")) {
            const value_casted = value as (BorderOptions)
            this.getPeer()?.borderAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public borderStyle(value: BorderStyle | EdgeStyles): this {
        if (this.checkPriority("borderStyle")) {
            const value_casted = value as (BorderStyle | EdgeStyles)
            this.getPeer()?.borderStyleAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public borderWidth(value: Length | EdgeWidths | LocalizedEdgeWidths): this {
        if (this.checkPriority("borderWidth")) {
            const value_casted = value as (Length | EdgeWidths | LocalizedEdgeWidths)
            this.getPeer()?.borderWidthAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public borderColor(value: ResourceColor | EdgeColors | LocalizedEdgeColors): this {
        if (this.checkPriority("borderColor")) {
            const value_casted = value as (ResourceColor | EdgeColors | LocalizedEdgeColors)
            this.getPeer()?.borderColorAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public borderRadius(value: Length | BorderRadiuses | LocalizedBorderRadiuses): this {
        if (this.checkPriority("borderRadius")) {
            const value_casted = value as (Length | BorderRadiuses | LocalizedBorderRadiuses)
            this.getPeer()?.borderRadiusAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public borderImage(value: BorderImageOption): this {
        if (this.checkPriority("borderImage")) {
            const value_casted = value as (BorderImageOption)
            this.getPeer()?.borderImageAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public outline(value: OutlineOptions): this {
        if (this.checkPriority("outline")) {
            const value_casted = value as (OutlineOptions)
            this.getPeer()?.outlineAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public outlineStyle(value: OutlineStyle | EdgeOutlineStyles): this {
        if (this.checkPriority("outlineStyle")) {
            const value_casted = value as (OutlineStyle | EdgeOutlineStyles)
            this.getPeer()?.outlineStyleAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public outlineWidth(value: Dimension | EdgeOutlineWidths): this {
        if (this.checkPriority("outlineWidth")) {
            const value_casted = value as (Dimension | EdgeOutlineWidths)
            this.getPeer()?.outlineWidthAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public outlineColor(value: ResourceColor | EdgeColors | LocalizedEdgeColors): this {
        if (this.checkPriority("outlineColor")) {
            const value_casted = value as (ResourceColor | EdgeColors | LocalizedEdgeColors)
            this.getPeer()?.outlineColorAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public outlineRadius(value: Dimension | OutlineRadiuses): this {
        if (this.checkPriority("outlineRadius")) {
            const value_casted = value as (Dimension | OutlineRadiuses)
            this.getPeer()?.outlineRadiusAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public foregroundColor(value: ResourceColor | ColoringStrategy): this {
        if (this.checkPriority("foregroundColor")) {
            const value_casted = value as (ResourceColor | ColoringStrategy)
            this.getPeer()?.foregroundColorAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onClick(event: ((event: ClickEvent) => void), distanceThreshold?: number): this {
        if (this.checkPriority("onClick")) {
            const event_type = runtimeType(event)
            const distanceThreshold_type = runtimeType(distanceThreshold)
            if (RuntimeType.UNDEFINED == distanceThreshold_type) {
                const value_casted = event as (((event: ClickEvent) => void))
                this.getPeer()?.onClick0Attribute(value_casted)
                return this
            }
            if (RuntimeType.NUMBER == distanceThreshold_type) {
                const event_casted = event as (((event: ClickEvent) => void))
                const distanceThreshold_casted = distanceThreshold as (number)
                this.getPeer()?.onClick1Attribute(event_casted, distanceThreshold_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    /** @memo */
    public onHover(value: ((isHover: boolean, event: HoverEvent) => void)): this {
        if (this.checkPriority("onHover")) {
            const value_casted = value as (((isHover: boolean, event: HoverEvent) => void))
            this.getPeer()?.onHoverAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onAccessibilityHover(value: AccessibilityCallback): this {
        if (this.checkPriority("onAccessibilityHover")) {
            const value_casted = value as (AccessibilityCallback)
            this.getPeer()?.onAccessibilityHoverAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public hoverEffect(value: HoverEffect): this {
        if (this.checkPriority("hoverEffect")) {
            const value_casted = value as (HoverEffect)
            this.getPeer()?.hoverEffectAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onMouse(value: ((event: MouseEvent) => void)): this {
        if (this.checkPriority("onMouse")) {
            const value_casted = value as (((event: MouseEvent) => void))
            this.getPeer()?.onMouseAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onTouch(value: ((event: TouchEvent) => void)): this {
        if (this.checkPriority("onTouch")) {
            const value_casted = value as (((event: TouchEvent) => void))
            this.getPeer()?.onTouchAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onKeyEvent(value: ((event: KeyEvent) => void)): this {
        if (this.checkPriority("onKeyEvent")) {
            const value_casted = value as (((event: KeyEvent) => void))
            this.getPeer()?.onKeyEventAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onKeyPreIme(value: ((parameter: KeyEvent) => boolean)): this {
        if (this.checkPriority("onKeyPreIme")) {
            const value_casted = value as (((parameter: KeyEvent) => boolean))
            this.getPeer()?.onKeyPreImeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public focusable(value: boolean): this {
        if (this.checkPriority("focusable")) {
            const value_casted = value as (boolean)
            this.getPeer()?.focusableAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onFocus(value: (() => void)): this {
        if (this.checkPriority("onFocus")) {
            const value_casted = value as ((() => void))
            this.getPeer()?.onFocusAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onBlur(value: (() => void)): this {
        if (this.checkPriority("onBlur")) {
            const value_casted = value as ((() => void))
            this.getPeer()?.onBlurAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public tabIndex(value: number): this {
        if (this.checkPriority("tabIndex")) {
            const value_casted = value as (number)
            this.getPeer()?.tabIndexAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public defaultFocus(value: boolean): this {
        if (this.checkPriority("defaultFocus")) {
            const value_casted = value as (boolean)
            this.getPeer()?.defaultFocusAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public groupDefaultFocus(value: boolean): this {
        if (this.checkPriority("groupDefaultFocus")) {
            const value_casted = value as (boolean)
            this.getPeer()?.groupDefaultFocusAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public focusOnTouch(value: boolean): this {
        if (this.checkPriority("focusOnTouch")) {
            const value_casted = value as (boolean)
            this.getPeer()?.focusOnTouchAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public focusBox(value: FocusBoxStyle): this {
        if (this.checkPriority("focusBox")) {
            const value_casted = value as (FocusBoxStyle)
            this.getPeer()?.focusBoxAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public animation(value: AnimateParam): this {
        if (this.checkPriority("animation")) {
            const value_casted = value as (AnimateParam)
            this.getPeer()?.animationAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public transition(effect: TransitionOptions | TransitionEffect | TransitionEffect, onFinish?: TransitionFinishCallback): this {
        if (this.checkPriority("transition")) {
            const effect_type = runtimeType(effect)
            const onFinish_type = runtimeType(onFinish)
            if (((TypeChecker.isTransitionOptions(effect, false, false, false, false, false)) || (TypeChecker.isTransitionEffect(effect))) && (RuntimeType.UNDEFINED == onFinish_type)) {
                const value_casted = effect as (TransitionOptions | TransitionEffect)
                this.getPeer()?.transition0Attribute(value_casted)
                return this
            }
            if ((TypeChecker.isTransitionEffect(effect)) && ((RuntimeType.FUNCTION == onFinish_type) || (RuntimeType.UNDEFINED == onFinish_type))) {
                const effect_casted = effect as (TransitionEffect)
                const onFinish_casted = onFinish as (TransitionFinishCallback | undefined)
                this.getPeer()?.transition1Attribute(effect_casted, onFinish_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    /** @memo */
    public motionBlur(value: MotionBlurOptions): this {
        if (this.checkPriority("motionBlur")) {
            const value_casted = value as (MotionBlurOptions)
            this.getPeer()?.motionBlurAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public brightness(value: number): this {
        if (this.checkPriority("brightness")) {
            const value_casted = value as (number)
            this.getPeer()?.brightnessAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public contrast(value: number): this {
        if (this.checkPriority("contrast")) {
            const value_casted = value as (number)
            this.getPeer()?.contrastAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public grayscale(value: number): this {
        if (this.checkPriority("grayscale")) {
            const value_casted = value as (number)
            this.getPeer()?.grayscaleAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public colorBlend(value: Color | string | Resource): this {
        if (this.checkPriority("colorBlend")) {
            const value_casted = value as (Color | string | Resource)
            this.getPeer()?.colorBlendAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public saturate(value: number): this {
        if (this.checkPriority("saturate")) {
            const value_casted = value as (number)
            this.getPeer()?.saturateAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public sepia(value: number): this {
        if (this.checkPriority("sepia")) {
            const value_casted = value as (number)
            this.getPeer()?.sepiaAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public invert(value: number | InvertOptions): this {
        if (this.checkPriority("invert")) {
            const value_casted = value as (number | InvertOptions)
            this.getPeer()?.invertAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public hueRotate(value: number | string): this {
        if (this.checkPriority("hueRotate")) {
            const value_casted = value as (number | string)
            this.getPeer()?.hueRotateAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public useShadowBatching(value: boolean): this {
        if (this.checkPriority("useShadowBatching")) {
            const value_casted = value as (boolean)
            this.getPeer()?.useShadowBatchingAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public useEffect(useEffect: boolean, effectType?: EffectType): this {
        if (this.checkPriority("useEffect")) {
            const useEffect_type = runtimeType(useEffect)
            const effectType_type = runtimeType(effectType)
            if (RuntimeType.UNDEFINED == effectType_type) {
                const value_casted = useEffect as (boolean)
                this.getPeer()?.useEffect0Attribute(value_casted)
                return this
            }
            if (TypeChecker.isEffectType(effectType)) {
                const useEffect_casted = useEffect as (boolean)
                const effectType_casted = effectType as (EffectType)
                this.getPeer()?.useEffect1Attribute(useEffect_casted, effectType_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    /** @memo */
    public renderGroup(value: boolean): this {
        if (this.checkPriority("renderGroup")) {
            const value_casted = value as (boolean)
            this.getPeer()?.renderGroupAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public freeze(value: boolean): this {
        if (this.checkPriority("freeze")) {
            const value_casted = value as (boolean)
            this.getPeer()?.freezeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public translate(value: TranslateOptions): this {
        if (this.checkPriority("translate")) {
            const value_casted = value as (TranslateOptions)
            this.getPeer()?.translateAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public scale(value: ScaleOptions): this {
        if (this.checkPriority("scale")) {
            const value_casted = value as (ScaleOptions)
            this.getPeer()?.scaleAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public gridSpan(value: number): this {
        if (this.checkPriority("gridSpan")) {
            const value_casted = value as (number)
            this.getPeer()?.gridSpanAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public gridOffset(value: number): this {
        if (this.checkPriority("gridOffset")) {
            const value_casted = value as (number)
            this.getPeer()?.gridOffsetAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public rotate(value: RotateOptions): this {
        if (this.checkPriority("rotate")) {
            const value_casted = value as (RotateOptions)
            this.getPeer()?.rotateAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public transform(value: Object): this {
        if (this.checkPriority("transform")) {
            const value_casted = value as (Object)
            this.getPeer()?.transformAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onAppear(value: (() => void)): this {
        if (this.checkPriority("onAppear")) {
            const value_casted = value as ((() => void))
            this.getPeer()?.onAppearAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onDisAppear(value: (() => void)): this {
        if (this.checkPriority("onDisAppear")) {
            const value_casted = value as ((() => void))
            this.getPeer()?.onDisAppearAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onAttach(value: (() => void)): this {
        if (this.checkPriority("onAttach")) {
            const value_casted = value as ((() => void))
            this.getPeer()?.onAttachAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onDetach(value: (() => void)): this {
        if (this.checkPriority("onDetach")) {
            const value_casted = value as ((() => void))
            this.getPeer()?.onDetachAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onAreaChange(value: ((oldValue: Area, newValue: Area) => void)): this {
        if (this.checkPriority("onAreaChange")) {
            const value_casted = value as (((oldValue: Area, newValue: Area) => void))
            this.getPeer()?.onAreaChangeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public visibility(value: Visibility): this {
        if (this.checkPriority("visibility")) {
            const value_casted = value as (Visibility)
            this.getPeer()?.visibilityAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public flexGrow(value: number): this {
        if (this.checkPriority("flexGrow")) {
            const value_casted = value as (number)
            this.getPeer()?.flexGrowAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public flexShrink(value: number): this {
        if (this.checkPriority("flexShrink")) {
            const value_casted = value as (number)
            this.getPeer()?.flexShrinkAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public flexBasis(value: number | string): this {
        if (this.checkPriority("flexBasis")) {
            const value_casted = value as (number | string)
            this.getPeer()?.flexBasisAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public alignSelf(value: ItemAlign): this {
        if (this.checkPriority("alignSelf")) {
            const value_casted = value as (ItemAlign)
            this.getPeer()?.alignSelfAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public displayPriority(value: number): this {
        if (this.checkPriority("displayPriority")) {
            const value_casted = value as (number)
            this.getPeer()?.displayPriorityAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public zIndex(value: number): this {
        if (this.checkPriority("zIndex")) {
            const value_casted = value as (number)
            this.getPeer()?.zIndexAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public direction(value: Direction): this {
        if (this.checkPriority("direction")) {
            const value_casted = value as (Direction)
            this.getPeer()?.directionAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public align(value: Alignment): this {
        if (this.checkPriority("align")) {
            const value_casted = value as (Alignment)
            this.getPeer()?.alignAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public position(value: Position | Edges | LocalizedEdges): this {
        if (this.checkPriority("position")) {
            const value_casted = value as (Position | Edges | LocalizedEdges)
            this.getPeer()?.positionAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public markAnchor(value: Position | LocalizedPosition): this {
        if (this.checkPriority("markAnchor")) {
            const value_casted = value as (Position | LocalizedPosition)
            this.getPeer()?.markAnchorAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public offset(value: Position | Edges | LocalizedEdges): this {
        if (this.checkPriority("offset")) {
            const value_casted = value as (Position | Edges | LocalizedEdges)
            this.getPeer()?.offsetAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public enabled(value: boolean): this {
        if (this.checkPriority("enabled")) {
            const value_casted = value as (boolean)
            this.getPeer()?.enabledAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public useSizeType(value: Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs): this {
        if (this.checkPriority("useSizeType")) {
            const value_casted = value as (Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs)
            this.getPeer()?.useSizeTypeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public alignRules(value: AlignRuleOption | LocalizedAlignRuleOptions): this {
        if (this.checkPriority("alignRules")) {
            const value_type = runtimeType(value)
            if (TypeChecker.isAlignRuleOption(value, false, false, true, true, true, true, true)) {
                const value_casted = value as (AlignRuleOption)
                this.getPeer()?.alignRules0Attribute(value_casted)
                return this
            }
            if (TypeChecker.isLocalizedAlignRuleOptions(value, false, false, true, true, true, true, true)) {
                const value_casted = value as (LocalizedAlignRuleOptions)
                this.getPeer()?.alignRules1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    /** @memo */
    public aspectRatio(value: number): this {
        if (this.checkPriority("aspectRatio")) {
            const value_casted = value as (number)
            this.getPeer()?.aspectRatioAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public clickEffect(value?: ClickEffect): this {
        if (this.checkPriority("clickEffect")) {
            const value_casted = value as (ClickEffect | undefined)
            this.getPeer()?.clickEffectAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onDragStart(value: ((event: DragEvent, extraParams?: string) => CustomBuilder | DragItemInfo)): this {
        if (this.checkPriority("onDragStart")) {
            const value_casted = value as (((event: DragEvent, extraParams?: string) => CustomBuilder | DragItemInfo))
            this.getPeer()?.onDragStartAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onDragEnter(value: ((event: DragEvent, extraParams?: string) => void)): this {
        if (this.checkPriority("onDragEnter")) {
            const value_casted = value as (((event: DragEvent, extraParams?: string) => void))
            this.getPeer()?.onDragEnterAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onDragMove(value: ((event: DragEvent, extraParams?: string) => void)): this {
        if (this.checkPriority("onDragMove")) {
            const value_casted = value as (((event: DragEvent, extraParams?: string) => void))
            this.getPeer()?.onDragMoveAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onDragLeave(value: ((event: DragEvent, extraParams?: string) => void)): this {
        if (this.checkPriority("onDragLeave")) {
            const value_casted = value as (((event: DragEvent, extraParams?: string) => void))
            this.getPeer()?.onDragLeaveAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onDrop(value: ((event: DragEvent, extraParams?: string) => void)): this {
        if (this.checkPriority("onDrop")) {
            const value_casted = value as (((event: DragEvent, extraParams?: string) => void))
            this.getPeer()?.onDropAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onDragEnd(value: ((event: DragEvent, extraParams?: string) => void)): this {
        if (this.checkPriority("onDragEnd")) {
            const value_casted = value as (((event: DragEvent, extraParams?: string) => void))
            this.getPeer()?.onDragEndAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public allowDrop(value?: Array<UniformDataType>): this {
        if (this.checkPriority("allowDrop")) {
            const value_casted = value as (Array<UniformDataType> | undefined)
            this.getPeer()?.allowDropAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public draggable(value: boolean): this {
        if (this.checkPriority("draggable")) {
            const value_casted = value as (boolean)
            this.getPeer()?.draggableAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public dragPreview(value: CustomBuilder | DragItemInfo | string): this {
        if (this.checkPriority("dragPreview")) {
            const value_casted = value as (CustomBuilder | DragItemInfo | string)
            this.getPeer()?.dragPreviewAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onPreDrag(value: ((parameter: PreDragStatus) => void)): this {
        if (this.checkPriority("onPreDrag")) {
            const value_casted = value as (((parameter: PreDragStatus) => void))
            this.getPeer()?.onPreDragAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public linearGradient(value: Type_CommonMethod_linearGradient_value): this {
        if (this.checkPriority("linearGradient")) {
            const value_casted = value as (Type_CommonMethod_linearGradient_value)
            this.getPeer()?.linearGradientAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public sweepGradient(value: Type_CommonMethod_sweepGradient_value): this {
        if (this.checkPriority("sweepGradient")) {
            const value_casted = value as (Type_CommonMethod_sweepGradient_value)
            this.getPeer()?.sweepGradientAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public radialGradient(value: Type_CommonMethod_radialGradient_value): this {
        if (this.checkPriority("radialGradient")) {
            const value_casted = value as (Type_CommonMethod_radialGradient_value)
            this.getPeer()?.radialGradientAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public motionPath(value: MotionPathOptions): this {
        if (this.checkPriority("motionPath")) {
            const value_casted = value as (MotionPathOptions)
            this.getPeer()?.motionPathAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public shadow(value: ShadowOptions | ShadowStyle): this {
        if (this.checkPriority("shadow")) {
            const value_casted = value as (ShadowOptions | ShadowStyle)
            this.getPeer()?.shadowAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public clip(value?: boolean): this {
        if (this.checkPriority("clip")) {
            const value_type = runtimeType(value)
            if ((RuntimeType.BOOLEAN == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (boolean | undefined)
                this.getPeer()?.clip0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.BOOLEAN == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (boolean | undefined)
                this.getPeer()?.clip1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    /** @memo */
    public clipShape(value: CircleShape | EllipseShape | PathShape | RectShape): this {
        if (this.checkPriority("clipShape")) {
            const value_casted = value as (CircleShape | EllipseShape | PathShape | RectShape)
            this.getPeer()?.clipShapeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public mask(value?: ProgressMask): this {
        if (this.checkPriority("mask")) {
            const value_type = runtimeType(value)
            if ((RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (ProgressMask | undefined)
                this.getPeer()?.mask0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (ProgressMask | undefined)
                this.getPeer()?.mask1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    /** @memo */
    public maskShape(value: CircleShape | EllipseShape | PathShape | RectShape): this {
        if (this.checkPriority("maskShape")) {
            const value_casted = value as (CircleShape | EllipseShape | PathShape | RectShape)
            this.getPeer()?.maskShapeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public key(value: string): this {
        if (this.checkPriority("key")) {
            const value_casted = value as (string)
            this.getPeer()?.keyAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public id(value: string): this {
        if (this.checkPriority("id")) {
            const value_casted = value as (string)
            this.getPeer()?.idAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public geometryTransition(id: string, options?: GeometryTransitionOptions): this {
        if (this.checkPriority("geometryTransition")) {
            const id_type = runtimeType(id)
            const options_type = runtimeType(options)
            if (RuntimeType.UNDEFINED == options_type) {
                const value_casted = id as (string)
                this.getPeer()?.geometryTransition0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.OBJECT == options_type) || (RuntimeType.UNDEFINED == options_type)) {
                const id_casted = id as (string)
                const options_casted = options as (GeometryTransitionOptions | undefined)
                this.getPeer()?.geometryTransition1Attribute(id_casted, options_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    /** @memo */
    public stateStyles(value: StateStyles): this {
        if (this.checkPriority("stateStyles")) {
            const value_casted = value as (StateStyles)
            this.getPeer()?.stateStylesAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public restoreId(value: number): this {
        if (this.checkPriority("restoreId")) {
            const value_casted = value as (number)
            this.getPeer()?.restoreIdAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public sphericalEffect(value: number): this {
        if (this.checkPriority("sphericalEffect")) {
            const value_casted = value as (number)
            this.getPeer()?.sphericalEffectAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public lightUpEffect(value: number): this {
        if (this.checkPriority("lightUpEffect")) {
            const value_casted = value as (number)
            this.getPeer()?.lightUpEffectAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public pixelStretchEffect(value: PixelStretchEffectOptions): this {
        if (this.checkPriority("pixelStretchEffect")) {
            const value_casted = value as (PixelStretchEffectOptions)
            this.getPeer()?.pixelStretchEffectAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public accessibilityGroup(isGroup: boolean, accessibilityOptions?: AccessibilityOptions): this {
        if (this.checkPriority("accessibilityGroup")) {
            const isGroup_type = runtimeType(isGroup)
            const accessibilityOptions_type = runtimeType(accessibilityOptions)
            if (RuntimeType.UNDEFINED == accessibilityOptions_type) {
                const value_casted = isGroup as (boolean)
                this.getPeer()?.accessibilityGroup0Attribute(value_casted)
                return this
            }
            if (RuntimeType.OBJECT == accessibilityOptions_type) {
                const isGroup_casted = isGroup as (boolean)
                const accessibilityOptions_casted = accessibilityOptions as (AccessibilityOptions)
                this.getPeer()?.accessibilityGroup1Attribute(isGroup_casted, accessibilityOptions_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    /** @memo */
    public accessibilityText(value: string | Resource): this {
        if (this.checkPriority("accessibilityText")) {
            const value_type = runtimeType(value)
            if (RuntimeType.STRING == value_type) {
                const value_casted = value as (string)
                this.getPeer()?.accessibilityText0Attribute(value_casted)
                return this
            }
            if (RuntimeType.OBJECT == value_type) {
                const value_casted = value as (Resource)
                this.getPeer()?.accessibilityText1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    /** @memo */
    public accessibilityTextHint(value: string): this {
        if (this.checkPriority("accessibilityTextHint")) {
            const value_casted = value as (string)
            this.getPeer()?.accessibilityTextHintAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public accessibilityDescription(value: string | Resource): this {
        if (this.checkPriority("accessibilityDescription")) {
            const value_type = runtimeType(value)
            if (RuntimeType.STRING == value_type) {
                const value_casted = value as (string)
                this.getPeer()?.accessibilityDescription0Attribute(value_casted)
                return this
            }
            if (RuntimeType.OBJECT == value_type) {
                const value_casted = value as (Resource)
                this.getPeer()?.accessibilityDescription1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    /** @memo */
    public accessibilityLevel(value: string): this {
        if (this.checkPriority("accessibilityLevel")) {
            const value_casted = value as (string)
            this.getPeer()?.accessibilityLevelAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public accessibilityVirtualNode(value: CustomBuilder): this {
        if (this.checkPriority("accessibilityVirtualNode")) {
            const value_casted = value as (CustomBuilder)
            this.getPeer()?.accessibilityVirtualNodeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public accessibilityChecked(value: boolean): this {
        if (this.checkPriority("accessibilityChecked")) {
            const value_casted = value as (boolean)
            this.getPeer()?.accessibilityCheckedAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public accessibilitySelected(value: boolean): this {
        if (this.checkPriority("accessibilitySelected")) {
            const value_casted = value as (boolean)
            this.getPeer()?.accessibilitySelectedAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public obscured(value: Array<ObscuredReasons>): this {
        if (this.checkPriority("obscured")) {
            const value_casted = value as (Array<ObscuredReasons>)
            this.getPeer()?.obscuredAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public reuseId(value: string): this {
        if (this.checkPriority("reuseId")) {
            const value_casted = value as (string)
            this.getPeer()?.reuseIdAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public renderFit(value: RenderFit): this {
        if (this.checkPriority("renderFit")) {
            const value_casted = value as (RenderFit)
            this.getPeer()?.renderFitAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public gestureModifier(value: GestureModifier): this {
        if (this.checkPriority("gestureModifier")) {
            const value_casted = value as (GestureModifier)
            this.getPeer()?.gestureModifierAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public backgroundBrightness(value: BackgroundBrightnessOptions): this {
        if (this.checkPriority("backgroundBrightness")) {
            const value_casted = value as (BackgroundBrightnessOptions)
            this.getPeer()?.backgroundBrightnessAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onGestureJudgeBegin(value: ((gestureInfo: GestureInfo, event: BaseGestureEvent) => GestureJudgeResult)): this {
        if (this.checkPriority("onGestureJudgeBegin")) {
            const value_casted = value as (((gestureInfo: GestureInfo, event: BaseGestureEvent) => GestureJudgeResult))
            this.getPeer()?.onGestureJudgeBeginAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onGestureRecognizerJudgeBegin(callback_: GestureRecognizerJudgeBeginCallback, exposeInnerGesture?: boolean): this {
        if (this.checkPriority("onGestureRecognizerJudgeBegin")) {
            const callback__type = runtimeType(callback_)
            const exposeInnerGesture_type = runtimeType(exposeInnerGesture)
            if (RuntimeType.UNDEFINED == exposeInnerGesture_type) {
                const value_casted = callback_ as (GestureRecognizerJudgeBeginCallback)
                this.getPeer()?.onGestureRecognizerJudgeBegin0Attribute(value_casted)
                return this
            }
            if (RuntimeType.BOOLEAN == exposeInnerGesture_type) {
                const callback__casted = callback_ as (GestureRecognizerJudgeBeginCallback)
                const exposeInnerGesture_casted = exposeInnerGesture as (boolean)
                this.getPeer()?.onGestureRecognizerJudgeBegin1Attribute(callback__casted, exposeInnerGesture_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    /** @memo */
    public shouldBuiltInRecognizerParallelWith(value: ShouldBuiltInRecognizerParallelWithCallback): this {
        if (this.checkPriority("shouldBuiltInRecognizerParallelWith")) {
            const value_casted = value as (ShouldBuiltInRecognizerParallelWithCallback)
            this.getPeer()?.shouldBuiltInRecognizerParallelWithAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public monopolizeEvents(value: boolean): this {
        if (this.checkPriority("monopolizeEvents")) {
            const value_casted = value as (boolean)
            this.getPeer()?.monopolizeEventsAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onTouchIntercept(value: ((parameter: TouchEvent) => HitTestMode)): this {
        if (this.checkPriority("onTouchIntercept")) {
            const value_casted = value as (((parameter: TouchEvent) => HitTestMode))
            this.getPeer()?.onTouchInterceptAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onSizeChange(value: SizeChangeCallback): this {
        if (this.checkPriority("onSizeChange")) {
            const value_casted = value as (SizeChangeCallback)
            this.getPeer()?.onSizeChangeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public customProperty(name: string, value?: Object): this {
        if (this.checkPriority("customProperty")) {
            const name_casted = name as (string)
            const value_casted = value as (Object | undefined)
            this.getPeer()?.customPropertyAttribute(name_casted, value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public expandSafeArea(types?: Array<SafeAreaType>, edges?: Array<SafeAreaEdge>): this {
        if (this.checkPriority("expandSafeArea")) {
            const types_casted = types as (Array<SafeAreaType> | undefined)
            const edges_casted = edges as (Array<SafeAreaEdge> | undefined)
            this.getPeer()?.expandSafeAreaAttribute(types_casted, edges_casted)
            return this
        }
        return this
    }
    /** @memo */
    public background(builder: CustomBuilder, options?: Literal_Alignment_align): this {
        if (this.checkPriority("background")) {
            const builder_casted = builder as (CustomBuilder)
            const options_casted = options as (Literal_Alignment_align | undefined)
            this.getPeer()?.backgroundAttribute(builder_casted, options_casted)
            return this
        }
        return this
    }
    /** @memo */
    public backgroundImage(src: ResourceStr | PixelMap, repeat?: ImageRepeat): this {
        if (this.checkPriority("backgroundImage")) {
            const src_casted = src as (ResourceStr | PixelMap)
            const repeat_casted = repeat as (ImageRepeat | undefined)
            this.getPeer()?.backgroundImageAttribute(src_casted, repeat_casted)
            return this
        }
        return this
    }
    /** @memo */
    public backgroundBlurStyle(value: BlurStyle, options?: BackgroundBlurStyleOptions): this {
        if (this.checkPriority("backgroundBlurStyle")) {
            const value_casted = value as (BlurStyle)
            const options_casted = options as (BackgroundBlurStyleOptions | undefined)
            this.getPeer()?.backgroundBlurStyleAttribute(value_casted, options_casted)
            return this
        }
        return this
    }
    /** @memo */
    public foregroundBlurStyle(value: BlurStyle, options?: ForegroundBlurStyleOptions): this {
        if (this.checkPriority("foregroundBlurStyle")) {
            const value_casted = value as (BlurStyle)
            const options_casted = options as (ForegroundBlurStyleOptions | undefined)
            this.getPeer()?.foregroundBlurStyleAttribute(value_casted, options_casted)
            return this
        }
        return this
    }
    /** @memo */
    public focusScopeId(id: string, isGroup?: boolean, arrowStepOut?: boolean): this {
        if (this.checkPriority("focusScopeId")) {
            const id_type = runtimeType(id)
            const isGroup_type = runtimeType(isGroup)
            const arrowStepOut_type = runtimeType(arrowStepOut)
            if (((RuntimeType.BOOLEAN == isGroup_type) || (RuntimeType.UNDEFINED == isGroup_type)) && (RuntimeType.UNDEFINED == arrowStepOut_type)) {
                const id_casted = id as (string)
                const isGroup_casted = isGroup as (boolean | undefined)
                this.getPeer()?.focusScopeId0Attribute(id_casted, isGroup_casted)
                return this
            }
            if (((RuntimeType.BOOLEAN == isGroup_type) || (RuntimeType.UNDEFINED == isGroup_type)) && ((RuntimeType.BOOLEAN == arrowStepOut_type) || (RuntimeType.UNDEFINED == arrowStepOut_type))) {
                const id_casted = id as (string)
                const isGroup_casted = isGroup as (boolean | undefined)
                const arrowStepOut_casted = arrowStepOut as (boolean | undefined)
                this.getPeer()?.focusScopeId1Attribute(id_casted, isGroup_casted, arrowStepOut_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    /** @memo */
    public focusScopePriority(scopeId: string, priority?: FocusPriority): this {
        if (this.checkPriority("focusScopePriority")) {
            const scopeId_casted = scopeId as (string)
            const priority_casted = priority as (FocusPriority | undefined)
            this.getPeer()?.focusScopePriorityAttribute(scopeId_casted, priority_casted)
            return this
        }
        return this
    }
    /** @memo */
    public gesture(gesture: GestureType, mask?: GestureMask): this {
        if (this.checkPriority("gesture")) {
            const gesture_casted = gesture as (GestureType)
            const mask_casted = mask as (GestureMask | undefined)
            this.getPeer()?.gestureAttribute(gesture_casted, mask_casted)
            return this
        }
        return this
    }
    /** @memo */
    public priorityGesture(gesture: GestureType, mask?: GestureMask): this {
        if (this.checkPriority("priorityGesture")) {
            const gesture_casted = gesture as (GestureType)
            const mask_casted = mask as (GestureMask | undefined)
            this.getPeer()?.priorityGestureAttribute(gesture_casted, mask_casted)
            return this
        }
        return this
    }
    /** @memo */
    public parallelGesture(gesture: GestureType, mask?: GestureMask): this {
        if (this.checkPriority("parallelGesture")) {
            const gesture_casted = gesture as (GestureType)
            const mask_casted = mask as (GestureMask | undefined)
            this.getPeer()?.parallelGestureAttribute(gesture_casted, mask_casted)
            return this
        }
        return this
    }
    /** @memo */
    public blur(value: number, options?: BlurOptions): this {
        if (this.checkPriority("blur")) {
            const value_casted = value as (number)
            const options_casted = options as (BlurOptions | undefined)
            this.getPeer()?.blurAttribute(value_casted, options_casted)
            return this
        }
        return this
    }
    /** @memo */
    public linearGradientBlur(value: number, options: LinearGradientBlurOptions): this {
        if (this.checkPriority("linearGradientBlur")) {
            const value_casted = value as (number)
            const options_casted = options as (LinearGradientBlurOptions)
            this.getPeer()?.linearGradientBlurAttribute(value_casted, options_casted)
            return this
        }
        return this
    }
    /** @memo */
    public systemBarEffect(): this {
        if (this.checkPriority("systemBarEffect")) {
            this.getPeer()?.systemBarEffectAttribute()
            return this
        }
        return this
    }
    /** @memo */
    public backdropBlur(value: number, options?: BlurOptions): this {
        if (this.checkPriority("backdropBlur")) {
            const value_casted = value as (number)
            const options_casted = options as (BlurOptions | undefined)
            this.getPeer()?.backdropBlurAttribute(value_casted, options_casted)
            return this
        }
        return this
    }
    /** @memo */
    public sharedTransition(id: string, options?: sharedTransitionOptions): this {
        if (this.checkPriority("sharedTransition")) {
            const id_casted = id as (string)
            const options_casted = options as (sharedTransitionOptions | undefined)
            this.getPeer()?.sharedTransitionAttribute(id_casted, options_casted)
            return this
        }
        return this
    }
    /** @memo */
    public chainMode(direction: Axis, style: ChainStyle): this {
        if (this.checkPriority("chainMode")) {
            const direction_casted = direction as (Axis)
            const style_casted = style as (ChainStyle)
            this.getPeer()?.chainModeAttribute(direction_casted, style_casted)
            return this
        }
        return this
    }
    /** @memo */
    public dragPreviewOptions(value: DragPreviewOptions, options?: DragInteractionOptions): this {
        if (this.checkPriority("dragPreviewOptions")) {
            const value_casted = value as (DragPreviewOptions)
            const options_casted = options as (DragInteractionOptions | undefined)
            this.getPeer()?.dragPreviewOptionsAttribute(value_casted, options_casted)
            return this
        }
        return this
    }
    /** @memo */
    public overlay(value: string | CustomBuilder | ComponentContent, options?: OverlayOptions): this {
        if (this.checkPriority("overlay")) {
            const value_casted = value as (string | CustomBuilder | ComponentContent)
            const options_casted = options as (OverlayOptions | undefined)
            this.getPeer()?.overlayAttribute(value_casted, options_casted)
            return this
        }
        return this
    }
    /** @memo */
    public blendMode(value: BlendMode, type?: BlendApplyType): this {
        if (this.checkPriority("blendMode")) {
            const value_casted = value as (BlendMode)
            const type_casted = type as (BlendApplyType | undefined)
            this.getPeer()?.blendModeAttribute(value_casted, type_casted)
            return this
        }
        return this
    }
    /** @memo */
    public advancedBlendMode(effect: BlendMode | Blender, type?: BlendApplyType): this {
        if (this.checkPriority("advancedBlendMode")) {
            const effect_casted = effect as (BlendMode | Blender)
            const type_casted = type as (BlendApplyType | undefined)
            this.getPeer()?.advancedBlendModeAttribute(effect_casted, type_casted)
            return this
        }
        return this
    }
    /** @memo */
    public bindPopup(show: boolean, popup: PopupOptions | CustomPopupOptions): this {
        if (this.checkPriority("bindPopup")) {
            const show_casted = show as (boolean)
            const popup_casted = popup as (PopupOptions | CustomPopupOptions)
            this.getPeer()?.bindPopupAttribute(show_casted, popup_casted)
            return this
        }
        return this
    }
    /** @memo */
    public bindMenu(content: Array<MenuElement> | CustomBuilder, options?: MenuOptions): this {
        if (this.checkPriority("bindMenu")) {
            const content_type = runtimeType(content)
            const options_type = runtimeType(options)
            if (((RuntimeType.OBJECT == content_type) || (RuntimeType.FUNCTION == content_type)) && ((RuntimeType.OBJECT == options_type) || (RuntimeType.UNDEFINED == options_type))) {
                const content_casted = content as (Array<MenuElement> | CustomBuilder)
                const options_casted = options as (MenuOptions | undefined)
                this.getPeer()?.bindMenu0Attribute(content_casted, options_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    /** @memo */
    public bindContextMenu(content: CustomBuilder, responseType: ResponseType, options?: ContextMenuOptions): this {
        if (this.checkPriority("bindContextMenu")) {
            const content_type = runtimeType(content)
            const options_type = runtimeType(options)
            if ((RuntimeType.FUNCTION == content_type) && (TypeChecker.isResponseType(responseType)) && ((RuntimeType.OBJECT == options_type) || (RuntimeType.UNDEFINED == options_type))) {
                const content_casted = content as (CustomBuilder)
                const responseType_casted = responseType as (ResponseType)
                const options_casted = options as (ContextMenuOptions | undefined)
                this.getPeer()?.bindContextMenu0Attribute(content_casted, responseType_casted, options_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    /** @memo */
    public bindContentCover(isShow: boolean | undefined, builder: CustomBuilder, type?: ModalTransition | undefined | ContentCoverOptions | undefined): this {
        if (this.checkPriority("bindContentCover")) {
            const isShow_type = runtimeType(isShow)
            const builder_type = runtimeType(builder)
            const type_type = runtimeType(type)
            if (((RuntimeType.BOOLEAN == isShow_type) || (RuntimeType.UNDEFINED == isShow_type)) && ((RuntimeType.OBJECT == type_type) || (RuntimeType.OBJECT == type_type))) {
                const isShow_casted = isShow as (boolean | undefined)
                const builder_casted = builder as (CustomBuilder)
                const type_casted = type as (ModalTransition | undefined)
                this.getPeer()?.bindContentCover0Attribute(isShow_casted, builder_casted, type_casted)
                return this
            }
            if (((RuntimeType.BOOLEAN == isShow_type) || (RuntimeType.UNDEFINED == isShow_type)) && ((RuntimeType.OBJECT == type_type) || (RuntimeType.UNDEFINED == type_type))) {
                const isShow_casted = isShow as (boolean | undefined)
                const builder_casted = builder as (CustomBuilder)
                const options_casted = type as (ContentCoverOptions | undefined)
                this.getPeer()?.bindContentCover1Attribute(isShow_casted, builder_casted, options_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    /** @memo */
    public bindSheet(isShow: boolean | undefined, builder: CustomBuilder, options?: SheetOptions): this {
        if (this.checkPriority("bindSheet")) {
            const isShow_casted = isShow as (boolean | undefined)
            const builder_casted = builder as (CustomBuilder)
            const options_casted = options as (SheetOptions | undefined)
            this.getPeer()?.bindSheetAttribute(isShow_casted, builder_casted, options_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onVisibleAreaChange(ratios: Array<number>, event: VisibleAreaChangeCallback): this {
        if (this.checkPriority("onVisibleAreaChange")) {
            const ratios_casted = ratios as (Array<number>)
            const event_casted = event as (VisibleAreaChangeCallback)
            this.getPeer()?.onVisibleAreaChangeAttribute(ratios_casted, event_casted)
            return this
        }
        return this
    }
    /** @memo */
    public keyboardShortcut(value: string | FunctionKey, keys: Array<ModifierKey>, action?: (() => void)): this {
        if (this.checkPriority("keyboardShortcut")) {
            const value_casted = value as (string | FunctionKey)
            const keys_casted = keys as (Array<ModifierKey>)
            const action_casted = action as ((() => void) | undefined)
            this.getPeer()?.keyboardShortcutAttribute(value_casted, keys_casted, action_casted)
            return this
        }
        return this
    }
    /** @memo */
    attributeModifier<T>(modifier: AttributeModifier<T>): this {
        let peerNode = this.getPeer()
        if (!peerNode._attributeSet) {
            let isCommonModifier: boolean = (modifier instanceof CommonModifier);
            if (isCommonModifier) {
                let commonModifier = modifier as object as CommonModifier;
                peerNode._attributeSet = commonModifier.attribute;
            } else {
                peerNode._attributeSet = new ArkCommonAttributeSet()
            }
        }
        applyUIAttributes(modifier, peerNode);
        let isAttributeUpdater: boolean = (modifier instanceof AttributeUpdater);
        if (isAttributeUpdater) {
            let attributeUpdater = modifier as object as AttributeUpdater<CommonAttribute, CommonInteface>
            attributeUpdater.initializeModifier(peerNode._attributeSet as CommonAttribute);
            attributeUpdater.onComponentChanged(peerNode._attributeSet as CommonAttribute);
            attributeUpdater.attribute = this.getModifierHost() as CommonAttribute
            attributeUpdater.updateConstructorParams = (...params: Object[]) => {
                let attribute = this.getModifierHost()! as CommonAttribute;
                //  this.getModifierHost()!.constructParam(params);
                return attribute;
            };
        }
        peerNode._attributeSet!.applyModifierPatch(peerNode);
        return this
    }
    public applyAttributesFinish(): void {
        // we calls this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
/** @memo:stable */
export class ArkCommonShapeMethodComponent extends ArkCommonMethodComponent implements CommonShapeMethod {
    getPeer(): ArkCommonShapeMethodPeer {
        return (this.peer as ArkCommonShapeMethodPeer)
    }
    /** @memo */
    public stroke(value: ResourceColor): this {
        if (this.checkPriority("stroke")) {
            const value_casted = value as (ResourceColor)
            this.getPeer()?.strokeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public fill(value: ResourceColor): this {
        if (this.checkPriority("fill")) {
            const value_casted = value as (ResourceColor)
            this.getPeer()?.fillAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public strokeDashOffset(value: number | string): this {
        if (this.checkPriority("strokeDashOffset")) {
            const value_casted = value as (number | string)
            this.getPeer()?.strokeDashOffsetAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public strokeLineCap(value: LineCapStyle): this {
        if (this.checkPriority("strokeLineCap")) {
            const value_casted = value as (LineCapStyle)
            this.getPeer()?.strokeLineCapAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public strokeLineJoin(value: LineJoinStyle): this {
        if (this.checkPriority("strokeLineJoin")) {
            const value_casted = value as (LineJoinStyle)
            this.getPeer()?.strokeLineJoinAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public strokeMiterLimit(value: number | string): this {
        if (this.checkPriority("strokeMiterLimit")) {
            const value_casted = value as (number | string)
            this.getPeer()?.strokeMiterLimitAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public strokeOpacity(value: number | string | Resource): this {
        if (this.checkPriority("strokeOpacity")) {
            const value_casted = value as (number | string | Resource)
            this.getPeer()?.strokeOpacityAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public fillOpacity(value: number | string | Resource): this {
        if (this.checkPriority("fillOpacity")) {
            const value_casted = value as (number | string | Resource)
            this.getPeer()?.fillOpacityAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public strokeWidth(value: Length): this {
        if (this.checkPriority("strokeWidth")) {
            const value_casted = value as (Length)
            this.getPeer()?.strokeWidthAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public antiAlias(value: boolean): this {
        if (this.checkPriority("antiAlias")) {
            const value_casted = value as (boolean)
            this.getPeer()?.antiAliasAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public strokeDashArray(value: Array<Length>): this {
        if (this.checkPriority("strokeDashArray")) {
            const value_casted = value as (Array<Length>)
            this.getPeer()?.strokeDashArrayAttribute(value_casted)
            return this
        }
        return this
    }
    public applyAttributesFinish(): void {
        // we calls this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
/** @memo:stable */
export class ArkCommonComponent extends ArkCommonMethodComponent implements CommonAttribute {
    getPeer(): ArkCommonPeer {
        return (this.peer as ArkCommonPeer)
    }
    /** @memo */
    public setCommonOptions(): this {
        if (this.checkPriority("setCommonOptions")) {
            this.getPeer()?.setCommonOptionsAttribute()
            return this
        }
        return this
    }
    public applyAttributesFinish(): void {
        // we calls this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
/** @memo:stable */
export class ArkScrollableCommonMethodComponent extends ArkCommonMethodComponent implements ScrollableCommonMethod {
    getPeer(): ArkScrollableCommonMethodPeer {
        return (this.peer as ArkScrollableCommonMethodPeer)
    }
    /** @memo */
    public scrollBar(value: BarState): this {
        if (this.checkPriority("scrollBar")) {
            const value_casted = value as (BarState)
            this.getPeer()?.scrollBarAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public scrollBarColor(value: Color | number | string): this {
        if (this.checkPriority("scrollBarColor")) {
            const value_casted = value as (Color | number | string)
            this.getPeer()?.scrollBarColorAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public scrollBarWidth(value: number | string): this {
        if (this.checkPriority("scrollBarWidth")) {
            const value_casted = value as (number | string)
            this.getPeer()?.scrollBarWidthAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public nestedScroll(value: NestedScrollOptions): this {
        if (this.checkPriority("nestedScroll")) {
            const value_casted = value as (NestedScrollOptions)
            this.getPeer()?.nestedScrollAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public enableScrollInteraction(value: boolean): this {
        if (this.checkPriority("enableScrollInteraction")) {
            const value_casted = value as (boolean)
            this.getPeer()?.enableScrollInteractionAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public friction(value: number | Resource): this {
        if (this.checkPriority("friction")) {
            const value_casted = value as (number | Resource)
            this.getPeer()?.frictionAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onScroll(value: ((first: number, last: number) => void)): this {
        if (this.checkPriority("onScroll")) {
            const value_casted = value as (((first: number, last: number) => void))
            this.getPeer()?.onScrollAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onWillScroll(value?: ScrollOnWillScrollCallback): this {
        if (this.checkPriority("onWillScroll")) {
            const value_casted = value as (ScrollOnWillScrollCallback | undefined)
            this.getPeer()?.onWillScrollAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onReachStart(value: (() => void)): this {
        if (this.checkPriority("onReachStart")) {
            const value_casted = value as ((() => void))
            this.getPeer()?.onReachStartAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onReachEnd(value: (() => void)): this {
        if (this.checkPriority("onReachEnd")) {
            const value_casted = value as ((() => void))
            this.getPeer()?.onReachEndAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onScrollStart(value: (() => void)): this {
        if (this.checkPriority("onScrollStart")) {
            const value_casted = value as ((() => void))
            this.getPeer()?.onScrollStartAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onScrollStop(value: (() => void)): this {
        if (this.checkPriority("onScrollStop")) {
            const value_casted = value as ((() => void))
            this.getPeer()?.onScrollStopAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public flingSpeedLimit(value: number): this {
        if (this.checkPriority("flingSpeedLimit")) {
            const value_casted = value as (number)
            this.getPeer()?.flingSpeedLimitAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public clipContent(value: ContentClipMode | RectShape): this {
        if (this.checkPriority("clipContent")) {
            const value_casted = value as (ContentClipMode | RectShape)
            this.getPeer()?.clipContentAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public edgeEffect(edgeEffect: EdgeEffect, options?: EdgeEffectOptions): this {
        if (this.checkPriority("edgeEffect")) {
            const edgeEffect_casted = edgeEffect as (EdgeEffect)
            const options_casted = options as (EdgeEffectOptions | undefined)
            this.getPeer()?.edgeEffectAttribute(edgeEffect_casted, options_casted)
            return this
        }
        return this
    }
    /** @memo */
    public fadingEdge(enabled?: boolean, options?: FadingEdgeOptions): this {
        if (this.checkPriority("fadingEdge")) {
            const enabled_casted = enabled as (boolean | undefined)
            const options_casted = options as (FadingEdgeOptions | undefined)
            this.getPeer()?.fadingEdgeAttribute(enabled_casted, options_casted)
            return this
        }
        return this
    }
    public applyAttributesFinish(): void {
        // we calls this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
