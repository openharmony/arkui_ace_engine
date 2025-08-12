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

import { AttributeModifier } from '../../component/common'
import { AccessibilityCallback, AlignRuleOption, AnimateParam, BackgroundBlurStyleOptions, BackgroundBrightnessOptions, BackgroundEffectOptions, BlendApplyType, BlurOptions, BlurStyle, BorderImageOption, ChainStyle, ClickEffect, ClickEvent, CommonAttribute, ContentCoverOptions, ContextMenuOptions, CustomBuilder, CustomPopupOptions, DragEvent, DragInteractionOptions, DragItemInfo, DragPreviewOptions, DrawModifier, EffectType, ForegroundBlurStyleOptions, ForegroundEffectOptions, GeometryTransitionOptions, GestureModifier, GestureRecognizerJudgeBeginCallback, HoverEvent, InvertOptions, KeyEvent, LinearGradientBlurOptions, Literal_Alignment_align, Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs, LocalizedAlignRuleOptions, MenuElement, MenuOptions, ModalTransition, MotionBlurOptions, MotionPathOptions, MouseEvent, OutlineStyle, OverlayOptions, PixelRoundPolicy, PixelStretchEffectOptions, PopupOptions, PreDragStatus, ProgressMask, Rectangle, RotateOptions, SafeAreaEdge, SafeAreaType, ScaleOptions, ShadowOptions, ShadowStyle, SheetOptions, ShouldBuiltInRecognizerParallelWithCallback, SizeChangeCallback, StateStyles, TouchEvent, TouchResult, TouchTestInfo, TransitionEffect, TransitionFinishCallback, TransitionOptions, TranslateOptions, VisibleAreaChangeCallback, sharedTransitionOptions, BackgroundImageOptions, ArkCommonMethodPeer, SystemAdaptiveOptions, CrownEvent, FocusAxisEvent, AxisEvent, FocusMovement, LinearGradientOptions, OnDragEventCallback, LayoutPolicy, PreviewConfiguration, DropOptions, SweepGradientOptions, AccessibilitySamePageMode, AccessibilityRoleType, AccessibilityFocusCallback, ReuseOptions, TipsMessageType, TipsOptions, VisibleAreaEventOptions, RadialGradientOptions, CommonMethod } from "../../component/common";
import { Color, HitTestMode, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Visibility, ItemAlign, Direction, ObscuredReasons, RenderFit, FocusDrawLevel, ImageRepeat, Axis, ResponseType, FunctionKey, ModifierKey } from '../../component/enums'
import { ResourceColor, ConstraintSizeOptions, SizeOptions, Length, ChainWeightOptions, Padding, LocalizedPadding, Position, BorderOptions, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, Dimension, EdgeOutlineWidths, OutlineRadiuses, Area, LocalizedEdges, LocalizedPosition, ResourceStr, AccessibilityOptions, EdgeStyles, Edges } from '../../component/units'
import { Resource } from "global.resource"
import { LengthMetrics } from "../../Graphics"
import { PixelMap } from '../../component/arkui-pixelmap'
import { ResizableOptions } from "../../component/image"
import { VisualEffect, Filter, BrightnessBlender } from "../../component/arkui-uieffect"
import { CircleShape, EllipseShape, PathShape, RectShape } from "../../component/arkui-external"
import { FocusBoxStyle, FocusPriority } from "../../component/focus"
import { TransformationMatrix } from "../../component/arkui-common"
import { UniformDataType } from "../../component/arkui-uniformtypedescriptor"
import { GestureInfo, BaseGestureEvent, GestureJudgeResult, GestureType, GestureMask } from "../../component/gesture"
import { ComponentContent } from "../../component/arkui-custom"
import { BlendMode } from "../../component/common"
import { int32} from "@koalaui/common"
import { PeerNode } from '../../PeerNode';

export enum ModifierType {
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

export function applyUIAttributes<T>(modifier: AttributeModifier<T>, nativeNode: ArkCommonMethodPeer, state: int32 = 0): void {
    modifier.applyNormalAttribute(nativeNode._attributeSet! as T);
    if (state & UI_STATE_PRESSED) {
        modifier.applyPressedAttribute(nativeNode._attributeSet! as T);
    }
    if (state & UI_STATE_FOCUSED) {
        modifier.applyFocusedAttribute(nativeNode._attributeSet! as T);
    }
    if (state & UI_STATE_DISABLED) {
        modifier.applyDisabledAttribute(nativeNode._attributeSet! as T);
    }
    if (state & UI_STATE_SELECTED) {
        modifier.applySelectedAttribute(nativeNode._attributeSet! as T);
    }
}

export function applyUIAttributesUpdate<T>(modifier: AttributeModifier<T>, nativeNode: ArkCommonMethodPeer, state: int32 = 0, isInit:boolean = true): void {
    if (state == UI_STATE_NORMAL && !isInit) {
        modifier.applyNormalAttribute(nativeNode._attributeSet! as T);
    }
    if (state & UI_STATE_PRESSED) {
        modifier.applyPressedAttribute(nativeNode._attributeSet! as T);
    }
    if (state & UI_STATE_FOCUSED) {
        modifier.applyFocusedAttribute(nativeNode._attributeSet! as T);
    }
    if (state & UI_STATE_DISABLED) {
        modifier.applyDisabledAttribute(nativeNode._attributeSet! as T);
    }
    if (state & UI_STATE_SELECTED) {
        modifier.applySelectedAttribute(nativeNode._attributeSet! as T);
    }
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
         node.backgroundColor0Attribute(this.value!);
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
         node.width0Attribute(this.value!);
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
         node.height0Attribute(this.value!);
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

   static factory(value: (event: ClickEvent) => void): OnClickModifier {
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


export class ArkCommonAttributeSet implements CommonAttribute {

    accessibilityDescription(value: String | Resource | undefined): this {
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
      this._modifiersWithKeys.forEach((value, key) => {
         value.applyStageImmediately(peerNode)
      });
   }

  public drawModifier(value: DrawModifier | undefined): this {
      return this
  }
  public responseRegion(value: Array<Rectangle> | Rectangle | undefined): this {
      return this
  }
  public mouseResponseRegion(value: Array<Rectangle> | Rectangle | undefined): this {
      return this
  }
  public constraintSize(value: ConstraintSizeOptions | undefined): this {
      return this
  }
  public touchable(value: boolean | undefined): this {
      return this
  }
  public hitTestBehavior(value: HitTestMode | undefined): this {
      return this
  }
  public onChildTouchTest(value: ((value: Array<TouchTestInfo>) => TouchResult) | undefined): this {
      return this
  }
  public layoutWeight(value: number | string | undefined): this {
      return this
  }
  public chainWeight(value: ChainWeightOptions | undefined): this {
      return this
  }
  public padding(value: Padding | Length | LocalizedPadding | undefined): this {
      return this
  }
  public safeAreaPadding(value: Padding | LengthMetrics | LocalizedPadding | undefined): this {
      return this
  }
  public margin(value: Padding | Length | LocalizedPadding | undefined): this {
      return this
  }
  public pixelRound(value: PixelRoundPolicy | undefined): this {
      return this
  }
  public backgroundImageSize(value: SizeOptions | ImageSize | undefined): this {
      return this
  }
  public backgroundImagePosition(value: Position | Alignment | undefined): this {
      return this
  }
  public backgroundEffect(options: BackgroundEffectOptions | undefined, sysOptions?: SystemAdaptiveOptions): this {
      return this
  }
  public backgroundImageResizable(value: ResizableOptions | undefined): this {
      return this
  }
  public foregroundEffect(value: ForegroundEffectOptions | undefined): this {
      return this
  }
  public visualEffect(value: VisualEffect | undefined): this {
      return this
  }
  public backgroundFilter(value: Filter | undefined): this {
      return this
  }
  public foregroundFilter(value: Filter | undefined): this {
      return this
  }
  public compositingFilter(value: Filter | undefined): this {
      return this
  }
  public opacity(value: number | Resource | undefined): this {
      return this
  }
  public border(value: BorderOptions | undefined): this {
      return this
  }
  public borderStyle(value: BorderStyle | EdgeStyles | undefined): this {
      return this
  }
  public borderWidth(value: Length | EdgeWidths | LocalizedEdgeWidths | undefined): this {
      return this
  }
  public borderColor(value: ResourceColor | EdgeColors | LocalizedEdgeColors | undefined): this {
      return this
  }
  public borderRadius(value: Length | BorderRadiuses | LocalizedBorderRadiuses | undefined): this {
      return this
  }
  public borderImage(value: BorderImageOption | undefined): this {
      return this
  }
  public outline(value: OutlineOptions | undefined): this {
      return this
  }
  public outlineStyle(value: OutlineStyle | EdgeOutlineStyles | undefined): this {
      return this
  }
  public outlineWidth(value: Dimension | EdgeOutlineWidths | undefined): this {
      return this
  }
  public outlineColor(value: ResourceColor | EdgeColors | LocalizedEdgeColors | undefined): this {
      return this
  }
  public outlineRadius(value: Dimension | OutlineRadiuses | undefined): this {
      return this
  }
  public foregroundColor(value: ResourceColor | ColoringStrategy | undefined): this {
      return this
  }
  public onHover(value: ((isHover: boolean,event: HoverEvent) => void) | undefined): this {
      return this
  }
  public onHoverMove(value: ((parameter: HoverEvent) => void) | undefined): this {
      return this
  }
  public onAccessibilityHover(value: AccessibilityCallback | undefined): this {
      return this
  }
  public hoverEffect(value: HoverEffect | undefined): this {
      return this
  }
  public onMouse(value: ((event: MouseEvent) => void) | undefined): this {
      return this
  }
  public onTouch(value: ((event: TouchEvent) => void) | undefined): this {
      return this
  }
  public onKeyEvent(value: ((event: KeyEvent) => void) | undefined | ((parameter: KeyEvent) => boolean) | undefined): this {
      return this
  }
  public onDigitalCrown(value: ((parameter: CrownEvent) => void) | undefined): this {
      return this
  }
  public onKeyPreIme(value: ((parameter: KeyEvent) => boolean) | undefined): this {
      return this
  }
  public onKeyEventDispatch(value: ((parameter: KeyEvent) => boolean) | undefined): this {
      return this
  }
  public onFocusAxisEvent(value: ((parameter: FocusAxisEvent) => void) | undefined): this {
      return this
  }
  public onAxisEvent(value: ((parameter: AxisEvent) => void) | undefined): this {
      return this
  }
  public focusable(value: boolean | undefined): this {
      return this
  }
  public nextFocus(value: FocusMovement | undefined): this {
      return this
  }
  public tabStop(value: boolean | undefined): this {
      return this
  }
  public onFocus(value: (() => void) | undefined): this {
      return this
  }
  public onBlur(value: (() => void) | undefined): this {
      return this
  }
  public tabIndex(value: number | undefined): this {
      return this
  }
  public defaultFocus(value: boolean | undefined): this {
      return this
  }
  public groupDefaultFocus(value: boolean | undefined): this {
      return this
  }
  public focusOnTouch(value: boolean | undefined): this {
      return this
  }
  public focusBox(value: FocusBoxStyle | undefined): this {
      return this
  }
  public animationStart(value: AnimateParam | undefined): this {
    return this
  }
  public animationStop(value: AnimateParam | undefined): this {
    return this
  }
  public animation(value: AnimateParam | undefined): this {
      return this
  }
  public transition(effect: TransitionOptions | TransitionEffect | undefined | TransitionEffect | undefined, onFinish?: TransitionFinishCallback): this {
      return this
  }
  public motionBlur(value: MotionBlurOptions | undefined): this {
      return this
  }
  public brightness(value: number | undefined): this {
      return this
  }
  public contrast(value: number | undefined): this {
      return this
  }
  public grayscale(value: number | undefined): this {
      return this
  }
  public colorBlend(value: Color | string | Resource | undefined): this {
      return this
  }
  public saturate(value: number | undefined): this {
      return this
  }
  public sepia(value: number | undefined): this {
      return this
  }
  public invert(value: number | InvertOptions | undefined): this {
      return this
  }
  public hueRotate(value: number | string | undefined): this {
      return this
  }
  public useShadowBatching(value: boolean | undefined): this {
      return this
  }
  public useEffect(useEffect: boolean | undefined, effectType?: EffectType | undefined | EffectType): this {
      return this
  }
  public renderGroup(value: boolean | undefined): this {
      return this
  }
  public freeze(value: boolean | undefined): this {
      return this
  }
  public translate(value: TranslateOptions | undefined): this {
      return this
  }
  public scale(value: ScaleOptions | undefined): this {
      return this
  }
  public gridSpan(value: number | undefined): this {
      return this
  }
  public gridOffset(value: number | undefined): this {
      return this
  }
  public rotate(value: RotateOptions | undefined): this {
      return this
  }
  public transform(value: TransformationMatrix | undefined | Object | undefined): this {
      return this
  }
  public onAppear(value: (() => void) | undefined): this {
      return this
  }
  public onDisAppear(value: (() => void) | undefined): this {
      return this
  }
  public onAttach(value: (() => void) | undefined): this {
      return this
  }
  public onDetach(value: (() => void) | undefined): this {
      return this
  }
  public onAreaChange(value: ((oldValue: Area,newValue: Area) => void) | undefined): this {
      return this
  }
  public visibility(value: Visibility | undefined): this {
      return this
  }
  public flexGrow(value: number | undefined): this {
      return this
  }
  public flexShrink(value: number | undefined): this {
      return this
  }
  public flexBasis(value: number | string | undefined): this {
      return this
  }
  public alignSelf(value: ItemAlign | undefined): this {
      return this
  }
  public displayPriority(value: number | undefined): this {
      return this
  }
  public direction(value: Direction | undefined): this {
      return this
  }
  public align(value: Alignment | undefined): this {
      return this
  }
  public position(value: Position | Edges | LocalizedEdges | undefined): this {
      return this
  }
  public markAnchor(value: Position | LocalizedPosition | undefined): this {
      return this
  }
  public offset(value: Position | Edges | LocalizedEdges | undefined): this {
      return this
  }
  public enabled(value: boolean | undefined): this {
      return this
  }
  public useSizeType(value: Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs | undefined): this {
      return this
  }
  public alignRules(value: AlignRuleOption | undefined | LocalizedAlignRuleOptions | undefined): this {
      return this
  }
  public aspectRatio(value: number | undefined): this {
      return this
  }
  public clickEffect(value: ClickEffect | undefined): this {
      return this
  }
  public onDragStart(value: ((event: DragEvent,extraParams?: string) => CustomBuilder | DragItemInfo) | undefined): this {
      return this
  }
  public onDragEnter(value: ((event: DragEvent,extraParams?: string) => void) | undefined): this {
      return this
  }
  public onDragMove(value: ((event: DragEvent,extraParams?: string) => void) | undefined): this {
      return this
  }
  public onDragLeave(value: ((event: DragEvent,extraParams?: string) => void) | undefined): this {
      return this
  }
  public onDrop(eventCallback: ((event: DragEvent,extraParams?: string) => void) | undefined | OnDragEventCallback | undefined, dropOptions?: DropOptions): this {
      return this
  }
  public onDragEnd(value: ((event: DragEvent,extraParams?: string) => void) | undefined): this {
      return this
  }
  public allowDrop(value: Array<UniformDataType> | undefined): this {
      return this
  }
  public draggable(value: boolean | undefined): this {
      return this
  }
  public dragPreview(preview: CustomBuilder | DragItemInfo | string | undefined, config?: PreviewConfiguration): this {
      return this
  }
  public onPreDrag(value: ((parameter: PreDragStatus) => void) | undefined): this {
      return this
  }
  public linearGradient(value: LinearGradientOptions | undefined): this {
      return this
  }
  public sweepGradient(value: SweepGradientOptions | undefined): this {
      return this
  }
  public radialGradient(value: RadialGradientOptions | undefined): this {
      return this
  }
  public motionPath(value: MotionPathOptions | undefined): this {
      return this
  }
  public shadow(value: ShadowOptions | ShadowStyle | undefined): this {
      return this
  }
  public clip(value: boolean | undefined): this {
      return this
  }
  public clipShape(value: CircleShape | EllipseShape | PathShape | RectShape | undefined): this {
      return this
  }
  public mask(value: ProgressMask | undefined): this {
      return this
  }
  public maskShape(value: CircleShape | EllipseShape | PathShape | RectShape | undefined): this {
      return this
  }
  public key(value: string | undefined): this {
      return this
  }
  public id(value: string | undefined): this {
      return this
  }
  public geometryTransition(id: string | undefined, options?: GeometryTransitionOptions): this {
      return this
  }
  public stateStyles(value: StateStyles | undefined): this {
      return this
  }
  public restoreId(value: number | undefined): this {
      return this
  }
  public sphericalEffect(value: number | undefined): this {
      return this
  }
  public lightUpEffect(value: number | undefined): this {
      return this
  }
  public pixelStretchEffect(value: PixelStretchEffectOptions | undefined): this {
      return this
  }
  public accessibilityGroup(isGroup: boolean | undefined, accessibilityOptions?: AccessibilityOptions): this {
      return this
  }
  public accessibilityText(value: string | undefined | Resource | undefined): this {
      return this
  }
  public accessibilityNextFocusId(value: string | undefined): this {
      return this
  }
  public accessibilityDefaultFocus(value: boolean | undefined): this {
      return this
  }
  public accessibilityUseSamePage(value: AccessibilitySamePageMode | undefined): this {
      return this
  }
  public accessibilityScrollTriggerable(value: boolean | undefined): this {
      return this
  }
  public accessibilityRole(value: AccessibilityRoleType | undefined): this {
      return this
  }
  public onAccessibilityFocus(value: AccessibilityFocusCallback | undefined): this {
      return this
  }
  public accessibilityTextHint(value: string | undefined): this {
      return this
  }

  public accessibilityLevel(value: string | undefined): this {
      return this
  }
  public accessibilityVirtualNode(value: CustomBuilder | undefined): this {
      return this
  }
  public accessibilityChecked(value: boolean | undefined): this {
      return this
  }
  public accessibilitySelected(value: boolean | undefined): this {
      return this
  }
  public obscured(value: Array<ObscuredReasons> | undefined): this {
      return this
  }
  public reuseId(value: string | undefined): this {
      return this
  }
  public reuse(value: ReuseOptions | undefined): this {
      return this
  }
  public renderFit(value: RenderFit | undefined): this {
      return this
  }
  public gestureModifier(value: GestureModifier | undefined): this {
      return this
  }
  public backgroundBrightness(value: BackgroundBrightnessOptions | undefined): this {
      return this
  }
  public onGestureJudgeBegin(value: ((gestureInfo: GestureInfo,event: BaseGestureEvent) => GestureJudgeResult) | undefined): this {
      return this
  }
  public onGestureRecognizerJudgeBegin(callback_: GestureRecognizerJudgeBeginCallback | undefined, exposeInnerGesture?: boolean): this {
      return this
  }
  public shouldBuiltInRecognizerParallelWith(value: ShouldBuiltInRecognizerParallelWithCallback | undefined): this {
      return this
  }
  public monopolizeEvents(value: boolean | undefined): this {
      return this
  }
  public onTouchIntercept(value: ((parameter: TouchEvent) => HitTestMode) | undefined): this {
      return this
  }
  public onSizeChange(value: SizeChangeCallback | undefined): this {
      return this
  }
  public accessibilityFocusDrawLevel(value: FocusDrawLevel | undefined): this {
      return this
  }
  public customProperty(name: string | undefined, value: Object | undefined): this {
      return this
  }
  public expandSafeArea(types?: Array<SafeAreaType> | undefined, edges?: Array<SafeAreaEdge> | undefined): this {
      return this
  }
  public background(builder: CustomBuilder | undefined, options?: Literal_Alignment_align): this {
      return this
  }
  public backgroundImage(src: ResourceStr | PixelMap | undefined, repeat?: ImageRepeat | BackgroundImageOptions): this {
      return this
  }
  public backgroundBlurStyle(style: BlurStyle | undefined, options?: BackgroundBlurStyleOptions, sysOptions?: SystemAdaptiveOptions): this {
      return this
  }
  public foregroundBlurStyle(style: BlurStyle | undefined, options?: ForegroundBlurStyleOptions, sysOptions?: SystemAdaptiveOptions): this {
      return this
  }
  public focusScopeId(id: string | undefined, isGroup?: boolean, arrowStepOut?: boolean): this {
      return this
  }
  public focusScopePriority(scopeId: string | undefined, priority?: FocusPriority): this {
      return this
  }
  public gesture(gesture: GestureType | undefined, mask?: GestureMask): this {
      return this
  }
  public priorityGesture(gesture: GestureType | undefined, mask?: GestureMask): this {
      return this
  }
  public parallelGesture(gesture: GestureType | undefined, mask?: GestureMask): this {
      return this
  }
  public blur(blurRadius: number | undefined, options?: BlurOptions, sysOptions?: SystemAdaptiveOptions): this {
      return this
  }
  public linearGradientBlur(value: number | undefined, options: LinearGradientBlurOptions | undefined): this {
      return this
  }
  public systemBarEffect(): this {
      return this
  }
  public backdropBlur(radius: number | undefined, options?: BlurOptions, sysOptions?: SystemAdaptiveOptions): this {
      return this
  }
  public sharedTransition(id: string | undefined, options?: sharedTransitionOptions): this {
      return this
  }
  public chainMode(direction: Axis | undefined, style: ChainStyle | undefined): this {
      return this
  }
  public dragPreviewOptions(value: DragPreviewOptions | undefined, options?: DragInteractionOptions): this {
      return this
  }
  public overlay(value: string | CustomBuilder | ComponentContent | undefined, options?: OverlayOptions): this {
      return this
  }
  public blendMode(value: BlendMode | undefined, type?: BlendApplyType): this {
      return this
  }
  public advancedBlendMode(effect: BlendMode | BrightnessBlender | undefined, type?: BlendApplyType): this {
      return this
  }
  public bindTips(message: TipsMessageType | undefined, options?: TipsOptions): this {
      return this
  }
  public bindPopup(show: boolean | undefined, popup: PopupOptions | CustomPopupOptions | undefined): this {
      return this
  }
  public bindMenu(content: Array<MenuElement> | CustomBuilder | undefined, options?: MenuOptions | undefined): this {
      return this
  }
  public bindContextMenu(content: CustomBuilder | undefined, responseType: ResponseType | undefined, options?: ContextMenuOptions | undefined): this {
      return this
  }
  public bindContentCover(isShow: boolean | undefined, builder: CustomBuilder | undefined, type?: ModalTransition | ContentCoverOptions): this {
      return this
  }
  public bindSheet(isShow: boolean | undefined, builder: CustomBuilder | undefined, options?: SheetOptions): this {
      return this
  }
  public onVisibleAreaChange(ratios: Array<number> | undefined, event: VisibleAreaChangeCallback | undefined): this {
      return this
  }
  public onVisibleAreaApproximateChange(options: VisibleAreaEventOptions | undefined, event: VisibleAreaChangeCallback | undefined): this {
      return this
  }
  public keyboardShortcut(value: string | FunctionKey | undefined, keys: Array<ModifierKey> | undefined, action?: (() => void)): this {
      return this
  }
  
 
   width(value: Length | undefined | Length | LayoutPolicy | undefined | undefined): this {
      if (value) {
         modifierWithKey(this._modifiersWithKeys, WidthModifier.identity, WidthModifier.factory, value as Length);
      } else {
         modifierNullWithKey(this._modifiersWithKeys, WidthModifier.identity)
      }
      return this;
   }
   height(value: Length | undefined | Length | LayoutPolicy | undefined | undefined): this {
      if (value != null) {
         modifierWithKey(this._modifiersWithKeys, HeightModifier.identity, HeightModifier.factory, value as Length);
      } else {
         modifierNullWithKey(this._modifiersWithKeys, HeightModifier.identity)
      }
      return this;
   }
   backgroundColor(value: ResourceColor | undefined): this {
      if (value != null) {
         modifierWithKey(this._modifiersWithKeys, BackgroundColorModifier.identity, BackgroundColorModifier.factory, value as ResourceColor);
      } else {
         modifierNullWithKey(this._modifiersWithKeys, BackgroundColorModifier.identity)
      }
      return this;
   }
   zIndex(value: number|undefined): this {
      if (value) {
         modifierWithKey(this._modifiersWithKeys, ZIndexModifier.identity, ZIndexModifier.factory, value);
      } else {
         modifierNullWithKey(this._modifiersWithKeys, ZIndexModifier.identity)
      }
      return this;
   }
   size(value: SizeOptions|undefined): this {
      if (value) {
         modifierWithKey(this._modifiersWithKeys, SizeModifier.identity, SizeModifier.factory, value);
      } else {
         modifierNullWithKey(this._modifiersWithKeys, SizeModifier.identity)
      }
      return this;
   }
   onClick(event: ((event: ClickEvent) => void) | undefined): this {
      if (event) {
         modifierWithKey(this._modifiersWithKeys, OnClickModifier.identity, OnClickModifier.factory, event);
      } else {
         modifierNullWithKey(this._modifiersWithKeys, OnClickModifier.identity)
      }
      return this;
   }
    public attributeModifier<T>(value: AttributeModifier<T>): this {
        return this
    }
}