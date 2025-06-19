/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

import { AccessibilityCallback, AccessibilityOptions, AlignRuleOption, Alignment, AnimateParam, Area, AttributeModifier, Axis, BackgroundBlurStyleOptions, BackgroundBrightnessOptions, BackgroundEffectOptions, BaseGestureEvent, BlendApplyType, BlendMode, Blender, BlurOptions, BlurStyle, BorderImageOption, BorderOptions, BorderRadiuses, BorderStyle, ChainStyle, ChainWeightOptions, CircleShape, ClickEffect, ClickEvent, Color, ColoringStrategy, CommonAttribute, CommonMethod, ComponentContent, ConstraintSizeOptions, ContentCoverOptions, ContextMenuOptions, CustomBuilder, CustomPopupOptions, Dimension, Direction, DragEvent, DragInteractionOptions, DragItemInfo, DragPreviewOptions, DrawModifier, EdgeColors, EdgeOutlineStyles, EdgeOutlineWidths, EdgeStyles, EdgeWidths, Edges, EffectType, EllipseShape, Filter, FocusBoxStyle, FocusPriority, ForegroundBlurStyleOptions, ForegroundEffectOptions, FunctionKey, GeometryTransitionOptions, GestureInfo, GestureJudgeResult, GestureMask, GestureModifier, GestureRecognizerJudgeBeginCallback, GestureType, HitTestMode, HoverEffect, HoverEvent, ImageRepeat, ImageSize, InvertOptions, ItemAlign, KeyEvent, Length, LinearGradientBlurOptions, Literal_Alignment_align, Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs, LocalizedAlignRuleOptions, LocalizedBorderRadiuses, LocalizedEdgeColors, LocalizedEdgeWidths, LocalizedEdges, LocalizedPadding, LocalizedPosition, MenuElement, MenuOptions, ModalTransition, ModifierKey, MotionBlurOptions, MotionPathOptions, MouseEvent, ObscuredReasons, OutlineOptions, OutlineRadiuses, OutlineStyle, OverlayOptions, Padding, PathShape, PixelMap, PixelRoundPolicy, PixelStretchEffectOptions, PopupOptions, Position, PreDragStatus, ProgressMask, RectShape, Rectangle, RenderFit, ResizableOptions, ResourceColor, ResourceStr, ResponseType, RotateOptions, SafeAreaEdge, SafeAreaType, ScaleOptions, ShadowOptions, ShadowStyle, SheetOptions, ShouldBuiltInRecognizerParallelWithCallback, SizeChangeCallback, SizeOptions, StateStyles, TouchEvent, TouchResult, TouchTestInfo, TransitionEffect, TransitionFinishCallback, TransitionOptions, TranslateOptions, Type_CommonMethod_linearGradient_value, Type_CommonMethod_radialGradient_value, Type_CommonMethod_sweepGradient_value, UniformDataType, Visibility, VisibleAreaChangeCallback, VisualEffect, sharedTransitionOptions } from "../..";
import { ArkCommonMethodPeer } from "../../generated/peers/ArkCommonPeer";
import { InteropNativeModule } from "@koalaui/interop"
import { Resource } from "global/resource";
import { LengthMetrics } from "../../Graphics"
import { ArkUIGeneratedNativeModule } from "#components"
import { int64 } from "@koalaui/common";
enum ModifierType {
    ORIGIN = 0,
    STATE = 1,
    FRAME_NODE = 2,
    EXPOSE_MODIFIER = 3,
}

abstract class BaseModifier {
    abstract applyStage(node: ArkCommonMethodPeer): boolean

    abstract applyStageImmediately(node: ArkCommonMethodPeer): void

    abstract applyPeer(node: ArkCommonMethodPeer, reset: boolean): void

    abstract checkObjectDiff(): boolean

    abstract reset(): void
}

class ObservedMap {
    private map_: Map<string, BaseModifier> = new Map<string, BaseModifier>();
    private changeCallback?: (key: string, value: BaseModifier) => void;

    public clear(): void {
        this.map_.clear();
    }

    public delete(key: string): boolean {
        return this.map_.delete(key);
    }

    public forEach(callbackfn: (value: BaseModifier, key: string) => void): void {
        this.map_.forEach(callbackfn);
    }
    public get(key: string): BaseModifier | undefined {
        return this.map_.get(key);
    }
    public has(key: string): boolean {
        return this.map_.has(key);
    }
    public set(key: string, value: BaseModifier): this {
        this.map_.set(key, value);
        if (this.changeCallback) {
            this.changeCallback!(key, value)
        }
        return this;
    }
    public get size(): number {
        return this.map_.size;
    }
    public entries(): IterableIterator<[string, BaseModifier]> {
        return this.map_.entries();
    }
    public keys(): IterableIterator<string> {
        return this.map_.keys();
    }
    public values(): IterableIterator<BaseModifier> {
        return this.map_.values();
    }
    public setOnChange(callback: (key: string, value: BaseModifier) => void): void {
        if (!this.changeCallback) {
            this.changeCallback = callback;
        }
    }
}

const UI_STATE_NORMAL = 0;
const UI_STATE_PRESSED = 1;
const UI_STATE_FOCUSED = 1 << 1;
const UI_STATE_DISABLED = 1 << 2;
const UI_STATE_SELECTED = 1 << 3;

 /** @memo */
export function applyUIAttributes<T>(modifier: AttributeModifier<T>, nativeNode: ArkCommonMethodPeer): void {
   //let status = ArkUIGeneratedNativeModule._UIStateGet(nativeNode.peer.ptr);
   modifier.applyNormalAttribute(nativeNode._attributeSet! as T);
   modifier.applyPressedAttribute(nativeNode._attributeSet! as T);
   modifier.applyFocusedAttribute(nativeNode._attributeSet! as T);
   modifier.applyDisabledAttribute(nativeNode._attributeSet! as T);
   modifier.applySelectedAttribute(nativeNode._attributeSet! as T);
}

export class ModifierWithKey<T> extends BaseModifier {
    stageValue: T | undefined;
    value: T | undefined;
    constructor(value: T) {
        super()
        this.stageValue = value;
    }

    reset(): void {
        this.stageValue = undefined
    }

    applyStage(node: ArkCommonMethodPeer): boolean {
        if (this.stageValue === undefined || this.stageValue === null) {
            this.value = this.stageValue
            this.applyPeer(node, true)
            return true;
        }
        let needDiff = this.checkObjectDiff()
        if (needDiff) {
            this.value = this.stageValue
            this.applyPeer(node, false)
            return true
        }
        return false
    }

    applyStageImmediately(node: ArkCommonMethodPeer): void {
        this.value = this.stageValue;
        if (this.stageValue === undefined || this.stageValue === null) {
            this.applyPeer(node, true);
            return;
        }
        this.applyPeer(node, false);
    }

    applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
     }

    checkObjectDiff(): boolean {
        const stageTypeInfo: string = typeof this.stageValue;
        const valueTypeInfo: string = typeof this.value;
        if (stageTypeInfo !== valueTypeInfo) {
            return true;
        }
        if (stageTypeInfo === 'number' || stageTypeInfo === 'string' || stageTypeInfo === 'boolean') {
            return (this.stageValue !== this.value);
        }
        // if (this.stageValue instanceof ArkResourceImpl) {
        //     return (this.stageValue as ArkResource).isEqual(this.value as ArkResource)
        // }
        return false;
    }
}

class BackgroundColorModifier extends ModifierWithKey<ResourceColor> {
    constructor(value: ResourceColor) {
        super(value);
    }
    static identity: string = 'backgroundColor';
    applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
        if (reset) {
            // commomPeerNode.resetBackgroundColor();
        } else {
            node.backgroundColorAttribute(this.value!);
        }
    }
    static factory(value: ResourceColor): BackgroundColorModifier {
        return new BackgroundColorModifier(value)
    }
}

class WidthModifier extends ModifierWithKey<Length> {
    constructor(value: Length) {
        super(value);
    }
    static identity: string = 'width';
    applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
        if (reset) {
            // commomPeerNode.resetWidthAttribute();
        } else {
            node.widthAttribute(this.value!);
        }
    }
    static factory(value: Length): WidthModifier {
        return new WidthModifier(value)
    }
}

class HeightModifier extends ModifierWithKey<Length> {
    constructor(value: Length) {
        super(value);
    }
    static identity: string = 'height';
    applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
        if (reset) {
            // commomPeerNode.resetWidthAttribute();
        } else {
            node.heightAttribute(this.value!);
        }
    }
    static factory(value: Length): HeightModifier {
        return new HeightModifier(value)
    }
}

class OnClickModifier extends ModifierWithKey<(event: ClickEvent) => void> {
   constructor(value: (event: ClickEvent) => void) {
       super(value);
   }
   static identity: string = 'onClick';
   applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
       if (reset) {
           // commomPeerNode.resetBackgroundColor();
       } else {
           node.onClick0Attribute(this.value!);
       }
   }
   
   static factory(value:(event: ClickEvent) => void): OnClickModifier {
       return new OnClickModifier(value)
   }
}

class ZIndexModifier extends ModifierWithKey<number> {
   constructor(value: number) {
       super(value);
   }
   static identity: string = 'zIndex';
   applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
       if (reset) {
           // commomPeerNode.resetBackgroundColor();
       } else {
           node.zIndexAttribute(this.value!);
       }
   }
   static factory(value: number): ZIndexModifier {
       return new ZIndexModifier(value)
   }
}

class SizeModifier extends ModifierWithKey<SizeOptions> {
   constructor(value: SizeOptions) {
       super(value);
   }
   static identity: string = 'size';
   applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
       if (reset) {
           // commomPeerNode.resetWidthAttribute();
       } else {
           node.sizeAttribute(this.value!);
       }
   }
   static factory(value: SizeOptions): SizeModifier {
       return new SizeModifier(value)
   }
}

export function modifierWithKey<T, M extends ModifierWithKey<T>>(
    modifiers: ObservedMap,
    identity: string,
    modifierClass: (value: T) => M, value: T) {
    let item = modifiers.get(identity)
    if (item == undefined) {
        modifiers.set(identity, modifierClass(value));
        return;
    }
    let item1 = item as ModifierWithKey<T>;
    item1.stageValue = value;
    modifiers.set(identity, item1);
}
export function modifierNullWithKey(modifiers: ObservedMap, identity: string) {
    const item = modifiers.get(identity)
    if (item) {
        item.reset()
        modifiers.set(identity, item);
    }
}

/** @memo:stable */
export class ArkCommonAttributeSet implements CommonAttribute {

   /** @memo */ 
   setCommonOptions(): this {
      return this;
    }
    
    _modifiersWithKeys: ObservedMap = new ObservedMap();
    _instanceId: number = -1;

    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId;
    }
    cleanStageValue(): void {
        if (!this._modifiersWithKeys) {
            return;
        }
        this._modifiersWithKeys.forEach((value, key) => {
            value.reset();
        });
    }
    applyModifierPatch(peerNode: ArkCommonMethodPeer): void {
        let expiringItemsWithKeys = new Array<string>;
        this._modifiersWithKeys.forEach((value, key) => {
            if (value.applyStage(peerNode)) {
                expiringItemsWithKeys.push(key);
            }
        });
    }

    /** @memo */
    drawModifier(value?: DrawModifier | undefined): this {
       return this;
    }
    /** @memo */
    responseRegion(value: Rectangle | Array<Rectangle>): this {
       return this;
    }
    /** @memo */
    mouseResponseRegion(value: Rectangle | Array<Rectangle>): this {
       return this;
    }
    /** @memo */
    size(value: SizeOptions): this {
      if (value) {
         modifierWithKey(this._modifiersWithKeys, SizeModifier.identity, SizeModifier.factory, value);
     } else {
         modifierNullWithKey(this._modifiersWithKeys, SizeModifier.identity)
     }
        return this;
    }
    /** @memo */
    constraintSize(value: ConstraintSizeOptions): this {
       return this;
    }
    /** @memo */
    touchable(value: boolean): this {
       return this;
    }
    /** @memo */
    hitTestBehavior(value: HitTestMode): this {
       return this;
    }
    /** @memo */
    onChildTouchTest(value: (value: Array<TouchTestInfo>) => TouchResult): this {
       return this;
    }
    /** @memo */
    layoutWeight(value: string | number): this {
       return this;
    }
    /** @memo */
    chainWeight(value: ChainWeightOptions): this {
       return this;
    }
    /** @memo */
    padding(value: Length | Padding | LocalizedPadding): this {
       return this;
    }
    /** @memo */
    safeAreaPadding(value: Padding | LocalizedPadding | LengthMetrics): this {
       return this;
    }
    /** @memo */
    margin(value: Length | Padding | LocalizedPadding): this {
       return this;
    }
    /** @memo */
    pixelRound(value: PixelRoundPolicy): this {
       return this;
    }
    /** @memo */
    backgroundImageSize(value: SizeOptions | ImageSize): this {
       return this;
    }
    /** @memo */
    backgroundImagePosition(value: Position | Alignment): this {
       return this;
    }
    /** @memo */
    backgroundEffect(value: BackgroundEffectOptions): this {
       return this;
    }
    /** @memo */
    backgroundImageResizable(value: ResizableOptions): this {
       return this;
    }
    /** @memo */
    foregroundEffect(value: ForegroundEffectOptions): this {
       return this;
    }
    /** @memo */
    visualEffect(value: VisualEffect): this {
       return this;
    }
    /** @memo */
    backgroundFilter(value: Filter): this {
       return this;
    }
    /** @memo */
    foregroundFilter(value: Filter): this {
       return this;
    }
    /** @memo */
    compositingFilter(value: Filter): this {
       return this;
    }
    /** @memo */
    opacity(value: number | Resource): this {
       return this;
    }
    /** @memo */
    border(value: BorderOptions): this {
       return this;
    }
    /** @memo */
    borderStyle(value: BorderStyle | EdgeStyles): this {
       return this;
    }
    /** @memo */
    borderWidth(value: Length | EdgeWidths | LocalizedEdgeWidths): this {
       return this;
    }
    /** @memo */
    borderColor(value: ResourceColor | EdgeColors | LocalizedEdgeColors): this {
       return this;
    }
    /** @memo */
    borderRadius(value: Length | BorderRadiuses | LocalizedBorderRadiuses): this {
       return this;
    }
    /** @memo */
    borderImage(value: BorderImageOption): this {
       return this;
    }
    /** @memo */
    outline(value: OutlineOptions): this {
    
       return this;
    }
    /** @memo */
    outlineStyle(value: OutlineStyle | EdgeOutlineStyles): this {
       return this;
    }
    /** @memo */
    outlineWidth(value: Dimension | EdgeOutlineWidths): this {
       return this;
    }
    /** @memo */
    outlineColor(value: ResourceColor | EdgeColors | LocalizedEdgeColors): this {
       return this;
    }
    /** @memo */
    outlineRadius(value: Dimension | OutlineRadiuses): this {
       return this;
    }
    /** @memo */
    foregroundColor(value:  ResourceColor | ColoringStrategy): this {
       return this;
    }
    /** @memo */
    onClick(event: (event: ClickEvent) => void, distanceThreshold?: number | undefined): this {
      if (event!=undefined) {
         modifierWithKey(this._modifiersWithKeys, OnClickModifier.identity, OnClickModifier.factory, event);
     } else {
         modifierNullWithKey(this._modifiersWithKeys, OnClickModifier.identity)
     }
     return this;
    }
    /** @memo */
    onHover(value: (isHover: boolean, event: HoverEvent) => void): this {
       return this;
    }
    /** @memo */
    onAccessibilityHover(value: AccessibilityCallback): this {
       return this;
    }
    /** @memo */
    hoverEffect(value: HoverEffect): this {
       return this;
    }
    /** @memo */
    onMouse(value: (event: MouseEvent) => void): this {
       return this;
    }
    /** @memo */
    onTouch(value: (event: TouchEvent) => void): this {
       return this;
    }
    /** @memo */
    onKeyEvent(value: (event: KeyEvent) => void): this {
       return this;
    }
    /** @memo */
    onKeyPreIme(value: (parameter: KeyEvent) => boolean): this {
       return this;
    }
    /** @memo */
    focusable(value: boolean): this {
       return this;
    }
    /** @memo */
    onFocus(value: () => void): this {
       return this;
    }
    /** @memo */
    onBlur(value: () => void): this {
       return this;
    }
    /** @memo */
    tabIndex(value: number): this {
       return this;
    }
    /** @memo */
    defaultFocus(value: boolean): this {
       return this;
    }
    /** @memo */
    groupDefaultFocus(value: boolean): this {
       return this;
    }
    /** @memo */
    focusOnTouch(value: boolean): this {
       return this;
    }
    /** @memo */
    focusBox(value: FocusBoxStyle): this {
       return this;
    }
    /** @memo */
    animation(value: AnimateParam): this {
       return this;
    }
    /** @memo */
    transition(effect: TransitionOptions | TransitionEffect, onFinish?: TransitionFinishCallback | undefined): this {
       return this;
    }
     /** @memo */
    motionBlur(value: MotionBlurOptions): this {
       return this;
    }
     /** @memo */
    brightness(value: number): this {
       return this;
    }
     /** @memo */
    contrast(value: number): this {
       return this;
    }
     /** @memo */
    grayscale(value: number): this {
       return this;
    }
     /** @memo */
    colorBlend(value: string | Color | Resource): this {
       return this;
    }
     /** @memo */
    saturate(value: number): this {
       return this;
    }
     /** @memo */
    sepia(value: number): this {
       return this;
    }
     /** @memo */
    invert(value: number | InvertOptions): this {
       return this;
    }
     /** @memo */
    hueRotate(value: string | number): this {
       return this;
    }
     /** @memo */
    useShadowBatching(value: boolean): this {
       return this;
    }
     /** @memo */
    useEffect(useEffect: boolean, effectType?: EffectType | undefined): this {
       return this;
    }
     /** @memo */
    renderGroup(value: boolean): this {
       return this;
    }
     /** @memo */
    freeze(value: boolean): this {
       return this;
    }
     /** @memo */
    translate(value: TranslateOptions): this {
       return this;
    }
     /** @memo */
    scale(value: ScaleOptions): this {
       return this;
    }
     /** @memo */
    gridSpan(value: number): this {
       return this;
    }
     /** @memo */
    gridOffset(value: number): this {
       return this;
    }
     /** @memo */
    rotate(value: RotateOptions): this {
       return this;
    }
     /** @memo */
    transform(value: Object): this {
       return this;
    }
     /** @memo */
    onAppear(value: () => void): this {
       return this;
    }
     /** @memo */
    onDisAppear(value: () => void): this {
       return this;
    }
     /** @memo */
    onAttach(value: () => void): this {
       return this;
    }
     /** @memo */
    onDetach(value: () => void): this {
       return this;
    }
     /** @memo */
    onAreaChange(value: (oldValue: Area, newValue: Area) => void): this {
       return this;
    }
     /** @memo */
    visibility(value: Visibility): this {
       return this;
    }
     /** @memo */
    flexGrow(value: number): this {
       return this;
    }
     /** @memo */
    flexShrink(value: number): this {
       return this;
    }
     /** @memo */
    flexBasis(value: string | number): this {
       return this;
    }
     /** @memo */
    alignSelf(value: ItemAlign): this {
       return this;
    }
     /** @memo */
    displayPriority(value: number): this {
       return this;
    }
    /** @memo */
    zIndex(value: number): this {
      if (value) {
         modifierWithKey(this._modifiersWithKeys, ZIndexModifier.identity, ZIndexModifier.factory, value);
     } else {
         modifierNullWithKey(this._modifiersWithKeys, ZIndexModifier.identity)
     }
     return this;
    }
     /** @memo */
    direction(value: Direction): this {
       return this;
    }
     /** @memo */
    align(value: Alignment): this {
       return this;
    }
     /** @memo */
    position(value: Position | Edges | LocalizedEdges): this {
       return this;
    }
     /** @memo */
    markAnchor(value: Position | LocalizedPosition): this {
       return this;
    }
     /** @memo */
    offset(value: Position | Edges | LocalizedEdges): this {
       return this;
    }
     /** @memo */
    enabled(value: boolean): this {
       return this;
    }
     /** @memo */
    useSizeType(value: Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs): this {
       return this;
    }
     /** @memo */
    alignRules(value: AlignRuleOption | LocalizedAlignRuleOptions): this {
       return this;
    }
     /** @memo */
    aspectRatio(value: number): this {
       return this;
    }
     /** @memo */
    clickEffect(value?: ClickEffect | undefined): this {
       return this;
    }
     /** @memo */
    onDragStart(value: (event: DragEvent, extraParams?: string | undefined) => CustomBuilder | DragItemInfo): this {
       return this;
    }
     /** @memo */
    onDragEnter(value: (event: DragEvent, extraParams?: string | undefined) => void): this {
       return this;
    }
     /** @memo */
    onDragMove(value: (event: DragEvent, extraParams?: string | undefined) => void): this {
       return this;
    }
     /** @memo */
    onDragLeave(value: (event: DragEvent, extraParams?: string | undefined) => void): this {
       return this;
    }
     /** @memo */
    onDrop(value: (event: DragEvent, extraParams?: string | undefined) => void): this {
       return this;
    }
     /** @memo */
    onDragEnd(value: (event: DragEvent, extraParams?: string | undefined) => void): this {
        return this;
    }
     /** @memo */
    allowDrop(value?: Array<UniformDataType> | undefined): this {
       return this;
    }
     /** @memo */
    draggable(value: boolean): this {
       return this;
    }
     /** @memo */
    dragPreview(value: string | CustomBuilder | DragItemInfo): this {
       return this;
    }
     /** @memo */
    onPreDrag(value: (parameter: PreDragStatus) => void): this {
       return this;
    }
     /** @memo */
    linearGradient(value: Type_CommonMethod_linearGradient_value): this {
       return this;
    }
     /** @memo */
    sweepGradient(value: Type_CommonMethod_sweepGradient_value): this {
       return this;
    }
     /** @memo */
    radialGradient(value: Type_CommonMethod_radialGradient_value): this {
       return this;
    }
     /** @memo */
    motionPath(value: MotionPathOptions): this {
       return this;
    }
     /** @memo */
    shadow(value: ShadowOptions | ShadowStyle): this {
       return this;
    }
     /** @memo */
    clip(value?: boolean | undefined): this {
        return this;
    }
     /** @memo */
    clipShape(value: CircleShape | EllipseShape | PathShape | RectShape): this {
       return this;
    }
     /** @memo */
    mask(value?: ProgressMask | undefined): this {
       return this;
    }
     /** @memo */
    maskShape(value: CircleShape | EllipseShape | PathShape | RectShape): this {
       return this;
    }
     /** @memo */
    key(value: string): this {
       return this;
    }
     /** @memo */
    id(value: string): this {
       return this;
    }
     /** @memo */
    geometryTransition(id: string, options?: GeometryTransitionOptions | undefined): this {
       return this;
    }
     /** @memo */
    stateStyles(value: StateStyles): this {
       return this;
    }
     /** @memo */
    restoreId(value: number): this {
       return this;
    }
     /** @memo */
    sphericalEffect(value: number): this {
       return this;
    }
    /** @memo */
    lightUpEffect(value: number): this {
       return this;
    }
     /** @memo */
    pixelStretchEffect(value: PixelStretchEffectOptions): this {
       return this;
    }
     /** @memo */
    accessibilityGroup(isGroup: boolean, accessibilityOptions?: AccessibilityOptions | undefined): this {
       return this;
    }
     /** @memo */
    accessibilityText(value: string | Resource): this {
       return this;
    }
     /** @memo */
    accessibilityTextHint(value: string): this {
       return this;
    }
     /** @memo */
    accessibilityDescription(value: string | Resource): this {
       return this;
    }
     /** @memo */
    accessibilityLevel(value: string): this {
       return this;
    }
     /** @memo */
    accessibilityVirtualNode(value: CustomBuilder): this {
       return this;
    }
     /** @memo */
    accessibilityChecked(value: boolean): this {
       return this;
    }
     /** @memo */
    accessibilitySelected(value: boolean): this {
       return this;
    }
     /** @memo */
    obscured(value: Array<ObscuredReasons>): this {
       return this;
    }
     /** @memo */
    reuseId(value: string): this {
       return this;
    }
     /** @memo */
    renderFit(value: RenderFit): this {
       return this;
    }
     /** @memo */
    gestureModifier(value: GestureModifier): this {
       return this;
    }
     /** @memo */
    backgroundBrightness(value: BackgroundBrightnessOptions): this {
       return this;
    }
     /** @memo */
    onGestureJudgeBegin(value: (gestureInfo: GestureInfo, event: BaseGestureEvent) => GestureJudgeResult): this {
       return this;
    }
     /** @memo */
    onGestureRecognizerJudgeBegin(callback_: GestureRecognizerJudgeBeginCallback, exposeInnerGesture?: boolean | undefined): this {
       return this;
    }
     /** @memo */
    shouldBuiltInRecognizerParallelWith(value: ShouldBuiltInRecognizerParallelWithCallback): this {
       return this;
    }
     /** @memo */
    monopolizeEvents(value: boolean): this {
       return this;
    }
     /** @memo */
    onTouchIntercept(value: (parameter: TouchEvent) => HitTestMode): this {
       return this;
    }
     /** @memo */
    onSizeChange(value: SizeChangeCallback): this {
       return this;
    }
     /** @memo */
    customProperty(name: string, value?: Object | undefined): this {
       return this;
    }
     /** @memo */
    expandSafeArea(types?: Array<SafeAreaType> | undefined, edges?: Array<SafeAreaEdge> | undefined): this {
       return this;
    }
     /** @memo */
    background(builder: CustomBuilder, options?: Literal_Alignment_align | undefined): this {
       return this;
    }
     /** @memo */
    backgroundImage(src: ResourceStr | PixelMap, repeat?: ImageRepeat | undefined): this {
       return this;
    }
     /** @memo */
    backgroundBlurStyle(value: BlurStyle, options?: BackgroundBlurStyleOptions | undefined): this {
       return this;
    }
     /** @memo */
    foregroundBlurStyle(value: BlurStyle, options?: ForegroundBlurStyleOptions | undefined): this {
       return this;
    }
     /** @memo */
    focusScopeId(id: string, isGroup?: boolean | undefined, arrowStepOut?: boolean | undefined): this {
       return this;
    }
     /** @memo */
    focusScopePriority(scopeId: string, priority?: FocusPriority | undefined): this {
       return this;
    }
     /** @memo */
    gesture(gesture: GestureType, mask?: GestureMask | undefined): this {
       return this;
    }
     /** @memo */
    priorityGesture(gesture: GestureType, mask?: GestureMask | undefined): this {
       return this;
    }
     /** @memo */
    parallelGesture(gesture: GestureType, mask?: GestureMask | undefined): this {
       return this;
    }
     /** @memo */
    blur(value: number, options?: BlurOptions | undefined): this {
       return this;
    }
     /** @memo */
    linearGradientBlur(value: number, options: LinearGradientBlurOptions): this {
       return this;
    }
     /** @memo */
    systemBarEffect(): this {
       return this;
    }
     /** @memo */
    backdropBlur(value: number, options?: BlurOptions | undefined): this {
       return this;
    }
     /** @memo */
    sharedTransition(id: string, options?: sharedTransitionOptions | undefined): this {
       return this;
    }
     /** @memo */
    chainMode(direction: Axis, style: ChainStyle): this {
       return this;
    }
     /** @memo */
    dragPreviewOptions(value: DragPreviewOptions, options?: DragInteractionOptions | undefined): this {
       return this;
    }
     /** @memo */
    overlay(value: string | CustomBuilder | ComponentContent, options?: OverlayOptions | undefined): this {
       return this;
    }
     /** @memo */
    blendMode(value: BlendMode, type?: BlendApplyType | undefined): this {
       return this;
    }
     /** @memo */
    advancedBlendMode(effect: BlendMode | Blender, type?: BlendApplyType | undefined): this {
       return this;
    }
     /** @memo */
    bindPopup(show: boolean, popup: PopupOptions | CustomPopupOptions): this {
       return this;
    }
     /** @memo */
    bindMenu(content: CustomBuilder | Array<MenuElement>, options?: MenuOptions | undefined): this {
       return this;
    }
     /** @memo */
    bindContextMenu(content: CustomBuilder, responseType: ResponseType, options?: ContextMenuOptions | undefined): this {
       return this;
    }
     /** @memo */
    bindContentCover(isShow: boolean | undefined, builder: CustomBuilder, type?: ModalTransition | ContentCoverOptions | undefined): this {
       return this;
    }
     /** @memo */
    bindSheet(isShow: boolean | undefined, builder: CustomBuilder, options?: SheetOptions | undefined): this {
       return this;
    }
     /** @memo */
    onVisibleAreaChange(ratios: Array<number>, event: VisibleAreaChangeCallback): this {
       return this;
    }
     /** @memo */
    keyboardShortcut(value: string | FunctionKey, keys: Array<ModifierKey>, action?: (() => void) | undefined): this {
       return this;
    }
   /** @memo */
   width(value: Length | undefined): this {
      if (value) {
         modifierWithKey(this._modifiersWithKeys, WidthModifier.identity, WidthModifier.factory, value as Length);
      } else {
         modifierNullWithKey(this._modifiersWithKeys, WidthModifier.identity)
      }
      return this;
   }
   /** @memo */
   height(value: Length | undefined): this {
      if (value != null) {
         modifierWithKey(this._modifiersWithKeys, HeightModifier.identity, HeightModifier.factory, value as Length);
      } else {
         modifierNullWithKey(this._modifiersWithKeys, HeightModifier.identity)
      }
      return this;
   }
   /** @memo */
    backgroundColor(value: ResourceColor | undefined): this {
      if (value != null) {
         modifierWithKey(this._modifiersWithKeys, HeightModifier.identity, BackgroundColorModifier.factory, value as ResourceColor);
      } else {
         modifierNullWithKey(this._modifiersWithKeys, HeightModifier.identity)
      }
       return this;
    }
    /** @memo */
    attributeModifier<T >(modifier:AttributeModifier<T>): this  {
      return this;
    }

}