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


import { AttributeUpdater } from '../../AttributeUpdater';
import { CommonModifier } from '../../CommonModifier';
import { ArkCommonMethodComponent, AttributeModifier, AnimatableArithmetic, BackgroundOptions, BlendMode } from '../../component/common';
import { AccessibilityCallback, AlignRuleOption, AnimateParam, Bindable, BackgroundBlurStyleOptions, BackgroundBrightnessOptions, BackgroundEffectOptions, BlendApplyType, BlurOptions, BlurStyle, BorderImageOption, ChainStyle, ClickEffect, ClickEvent, CommonAttribute, ContentCoverOptions, ContextMenuOptions, CustomBuilder, CustomPopupOptions, DragEvent, DragInteractionOptions, DragItemInfo, DragPreviewOptions, DrawModifier, EffectType, ForegroundBlurStyleOptions, ForegroundEffectOptions, GeometryTransitionOptions, GestureModifier, GestureRecognizerJudgeBeginCallback, HoverEvent, InvertOptions, KeyEvent, LinearGradientBlurOptions, Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs, LocalizedAlignRuleOptions, MenuElement, MenuOptions, ModalTransition, MotionBlurOptions, MotionPathOptions, MouseEvent, OutlineStyle, OverlayOptions, PixelRoundPolicy, PixelStretchEffectOptions, PopupOptions, PreDragStatus, ProgressMask, Rectangle, RotateOptions, SafeAreaEdge, SafeAreaType, ScaleOptions, ShadowOptions, ShadowStyle, SheetOptions, ShouldBuiltInRecognizerParallelWithCallback, SizeChangeCallback, StateStyles, TouchEvent, TouchResult, TouchTestInfo, TransitionEffect, TransitionFinishCallback, TransitionOptions, TranslateOptions, VisibleAreaChangeCallback, sharedTransitionOptions, BackgroundImageOptions, ArkCommonMethodPeer, SystemAdaptiveOptions, CrownEvent, FocusAxisEvent, AxisEvent, FocusMovement, LinearGradientOptions, OnDragEventCallback, LayoutPolicy, PreviewConfiguration, DropOptions, SweepGradientOptions, AccessibilitySamePageMode, AccessibilityRoleType, AccessibilityFocusCallback, ReuseOptions, TipsMessageType, TipsOptions, VisibleAreaEventOptions, RadialGradientOptions, CommonMethod } from "../../component/common";
import { Color, HitTestMode, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Visibility, ItemAlign, Direction, ObscuredReasons, RenderFit, FocusDrawLevel, ImageRepeat, Axis, ResponseType, FunctionKey, ModifierKey } from '../../component/enums'
import { ResourceColor, ConstraintSizeOptions, SizeOptions, Length, ChainWeightOptions, Padding, LocalizedPadding, Position, BorderOptions, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, Dimension, EdgeOutlineWidths, OutlineRadiuses, Area, LocalizedEdges, LocalizedPosition, ResourceStr, AccessibilityOptions, EdgeStyles, Edges } from '../../component/units'
import { Resource } from "global.resource"
import { LengthMetrics } from "../../Graphics"
import { PixelMap, UniformDataType } from '#external'
import { ResizableOptions } from "../../component/image"
import { Filter, VisualEffect, BrightnessBlender } from "#external"
import { CircleShape, EllipseShape, PathShape, RectShape } from "@ohos/arkui/shape"
import { FocusBoxStyle, FocusPriority } from "../../component/focus"
import { TransformationMatrix } from "../../component/arkui-common"
import { GestureInfo, BaseGestureEvent, GestureJudgeResult, GestureType, GestureMask } from "../../component/gesture"
import { ComponentContent } from 'arkui/ComponentContent'
import { int32} from "@koalaui/common"
import { PeerNode } from '../../PeerNode';
import { InteropNativeModule } from '@koalaui/interop';
import { CommonMethodModifier } from '../../CommonMethodModifier';
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

export function applyUIAttributes<T>(modifier: AttributeModifier<T>, attributeSet: CommonMethodModifier, state: int32 = 0): void {     
    modifier.applyNormalAttribute(attributeSet as T);
    if (state & UI_STATE_PRESSED) {
        modifier.applyPressedAttribute(attributeSet as T);
    }
    if (state & UI_STATE_FOCUSED) {
        modifier.applyFocusedAttribute(attributeSet as T);
    }
    if (state & UI_STATE_DISABLED) {
        modifier.applyDisabledAttribute(attributeSet as T);
    }
    if (state & UI_STATE_SELECTED) {
        modifier.applySelectedAttribute(attributeSet as T);
    }
}

export function applyUIAttributesUpdate<T>(modifier: AttributeModifier<T>, attributeSet: CommonMethodModifier, state: int32 = 0, isInit:boolean = true): void {
    if (state == UI_STATE_NORMAL && !isInit) {
        modifier.applyNormalAttribute(attributeSet as T);
    }
    if (state & UI_STATE_PRESSED) {
        modifier.applyPressedAttribute(attributeSet as T);
    }
    if (state & UI_STATE_FOCUSED) {
        modifier.applyFocusedAttribute(attributeSet as T);
    }
    if (state & UI_STATE_DISABLED) {
        modifier.applyDisabledAttribute(attributeSet as T);
    }
    if (state & UI_STATE_SELECTED) {
        modifier.applySelectedAttribute(attributeSet as T);
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

function boolToNumber(value: boolean): number {
    return value ? 1 : 0;;
}

function numberToBool(value: number): boolean {
    return value === 1;
}

class TabIndexModifier extends ModifierWithKey<number> {
   constructor(value: number) {
      super(value);
   }
   static identity: string = 'tabIndex';
   applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
      if (reset) {
         // commomPeerNode.resetBackgroundColor();
      } else {
         node.tabIndexAttribute(this.value);
      }
   }
   static factory(value: number): TabIndexModifier {
      return new TabIndexModifier(value)
   }
}

class OnKeyEventModifier extends ModifierWithKey<((parameter: KeyEvent) => boolean) | undefined> {
   constructor(value: (event: KeyEvent) => boolean) {
      super(value);
   }
   static identity: string = 'onKeyEvent';
   applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
      if (reset) {
         // commomPeerNode.resetBackgroundColor();
      } else {
         node.onKeyEvent1Attribute(this.value);
      }
   }

   static factory(value: (event: KeyEvent) => boolean): OnKeyEventModifier {
      return new OnKeyEventModifier(value)
   }
}

class OnHoverModifier extends ModifierWithKey<((isHover: boolean,event: HoverEvent) => void) | undefined> {
   constructor(value: ((isHover: boolean,event: HoverEvent) => void) | undefined) {
      super(value);
   }
   static identity: string = 'onHover';
   applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
      if (reset) {
         // commomPeerNode.resetBackgroundColor();
      } else {
         node.onHoverAttribute(this.value);
      }
   }

   static factory(value: ((isHover: boolean,event: HoverEvent) => void) | undefined): OnHoverModifier {
      return new OnHoverModifier(value)
   }
}

class OnKeyPreImeModifier extends ModifierWithKey<((parameter: KeyEvent) => boolean) | undefined> {
    constructor(value: ((parameter: KeyEvent) => boolean) | undefined) {
        super(value);
    }
    static identity: string = 'onKeyPreIme';
    applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
        if (reset) {
            // commomPeerNode.resetBackgroundColor();
        } else {
            node.onKeyPreImeAttribute(this.value);
        }
    }

    static factory(value: ((parameter: KeyEvent) => boolean) | undefined): OnKeyPreImeModifier {
        return new OnKeyPreImeModifier(value)
    }
}

class OnHoverMoveModifier extends ModifierWithKey<((parameter: HoverEvent) => void) | undefined> {
    constructor(value: ((parameter: HoverEvent) => void) | undefined) {
        super(value);
    }
    static identity: string = 'onHoverMove';
    applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
        if (reset) {
            // commomPeerNode.resetBackgroundColor();
        } else {
            node.onHoverMoveAttribute(this.value);
        }
    }

    static factory(value: ((parameter: HoverEvent) => void) | undefined): OnHoverMoveModifier {
        return new OnHoverMoveModifier(value)
    }
}

class HoverEffectModifier extends ModifierWithKey<HoverEffect | undefined> {
    constructor(value: HoverEffect | undefined) {
        super(value);
    }
    static identity: string = 'hoverEffect';
    applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
        if (reset) {
            // commomPeerNode.resetBackgroundColor();
        } else {
            node.hoverEffectAttribute(this.value);
        }
    }

    static factory(value: HoverEffect | undefined): HoverEffectModifier {
        return new HoverEffectModifier(value)
    }
}

class OnMouseModifier extends ModifierWithKey<((event: MouseEvent) => void) | undefined> {
    constructor(value: ((event: MouseEvent) => void) | undefined) {
        super(value);
    }
    static identity: string = 'onMouse';
    applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
        if (reset) {
            // commomPeerNode.resetBackgroundColor();
        } else {
            node.onMouseAttribute(this.value);
        }
    }

    static factory(value: ((event: MouseEvent) => void) | undefined): OnMouseModifier {
        return new OnMouseModifier(value)
    }
}

class OnTouchModifier extends ModifierWithKey<((event: TouchEvent) => void) | undefined> {
    constructor(value: ((event: TouchEvent) => void) | undefined) {
        super(value);
    }
    static identity: string = 'onTouch';
    applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
        if (reset) {
            // commomPeerNode.resetBackgroundColor();
        } else {
            node.onTouchAttribute(this.value);
        }
    }
    
    static factory(value: ((event: TouchEvent) => void) | undefined): OnTouchModifier {
        return new OnTouchModifier(value)
    }
}

class OnKeyEventDispatchModifier extends ModifierWithKey<((parameter: KeyEvent) => boolean) | undefined> {
    constructor(value: ((parameter: KeyEvent) => boolean) | undefined) {
        super(value);
    }
    static identity: string = 'onKeyEventDispatch';
    applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
        if (reset) {
            // commomPeerNode.resetBackgroundColor();
        } else {
            node.onKeyEventDispatchAttribute(this.value);
        }
    }
    
    static factory(value: ((parameter: KeyEvent) => boolean) | undefined): OnKeyEventDispatchModifier {
        return new OnKeyEventDispatchModifier(value)
    }
}

class OnFocusAxisEventModifier extends ModifierWithKey<((event: FocusAxisEvent) => void) | undefined> {
    constructor(value: ((event: FocusAxisEvent) => void) | undefined) {
        super(value);
    }
    static identity: string = 'onFocusAxisEvent';
    applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
        if (reset) {
            // commomPeerNode.resetBackgroundColor();
        } else {
            node.onFocusAxisEventAttribute(this.value);
        }
    }
    
    static factory(value: ((event: FocusAxisEvent) => void) | undefined): OnFocusAxisEventModifier {
        return new OnFocusAxisEventModifier(value)
    }
}

class OnAxisEventModifier extends ModifierWithKey<((event: AxisEvent) => void) | undefined> {
    constructor(value: ((event: AxisEvent) => void) | undefined) {
        super(value);
    }
    static identity: string = 'onAxisEvent';
    applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
        if (reset) {
            // commomPeerNode.resetBackgroundColor();
        } else {
            node.onAxisEventAttribute(this.value);
        }
    }
    
    static factory(value: ((event: AxisEvent) => void) | undefined): OnAxisEventModifier {
        return new OnAxisEventModifier(value)
    }
}


class FocusableModifier extends ModifierWithKey<number> {
    constructor(value: number) {
        super(value);
    }
    static identity: string = 'focusable';
    applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
        if (reset) {
            // commomPeerNode.resetBackgroundColor();
        } else {
            node.focusableAttribute(numberToBool(this.value!));
        }
    }
    static factory(value: number): FocusableModifier {
        return new FocusableModifier(value)
    }
}

class NextFocusModifier extends ModifierWithKey<FocusMovement | undefined> {
    constructor(value: FocusMovement | undefined) {
        super(value);
    }
    static identity: string = 'nextFocus';
    applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
        if (reset) {
            // commomPeerNode.resetBackgroundColor();
        } else {
            node.nextFocusAttribute(this.value);
        }
    }
    static factory(value: FocusMovement | undefined): NextFocusModifier {
        return new NextFocusModifier(value)
    }
}

class TabStopModifier extends ModifierWithKey<number> {
    constructor(value: number) {
        super(value);
    }
    static identity: string = 'tabStop';
    applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
        if (reset) {
            // commomPeerNode.resetBackgroundColor();
        } else {
            node.tabStopAttribute(numberToBool(this.value!));
        }
    }
    static factory(value: number): TabStopModifier {
        return new TabStopModifier(value)
    }
}

class OnFocusModifier extends ModifierWithKey<(() => void) | undefined> {
    constructor(value: (() => void) | undefined) {
        super(value);
    }
    static identity: string = 'onFocus';
    applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
        if (reset) {
            // commomPeerNode.resetBackgroundColor();
        } else {
            node.onFocusAttribute(this.value);
        }
    }
    
    static factory(value: (() => void) | undefined): OnFocusModifier {
        return new OnFocusModifier(value)
    }
}

class OnBlurModifier extends ModifierWithKey<(() => void) | undefined> {
    constructor(value: (() => void) | undefined) {
        super(value);
    }
    static identity: string = 'onBlur';
    applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
        if (reset) {
            // commomPeerNode.resetBackgroundColor();
        } else {
            node.onBlurAttribute(this.value);
        }
    }
    
    static factory(value: (() => void) | undefined): OnBlurModifier {
        return new OnBlurModifier(value)
    }
}

class DefaultFocusModifier extends ModifierWithKey<number> {
    constructor(value: number) {
        super(value);
    }
    static identity: string = 'defaultFocus';
    applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
        if (reset) {
            // commomPeerNode.resetBackgroundColor();
        } else {
            node.defaultFocusAttribute(numberToBool(this.value!));
        }
    }
    static factory(value: number): DefaultFocusModifier {
        return new DefaultFocusModifier(value)
    }
}

class GroupDefaultFocusModifier extends ModifierWithKey<number> {
    constructor(value: number) {
        super(value);
    }
    static identity: string = 'groupDefaultFocus';
    applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
        if (reset) {
            // commomPeerNode.resetBackgroundColor();
        } else {
            node.groupDefaultFocusAttribute(numberToBool(this.value!));
        }
    }
    static factory(value: number): GroupDefaultFocusModifier {
        return new GroupDefaultFocusModifier(value)
    }
}

class FocusOnTouchModifier extends ModifierWithKey<number> {
    constructor(value: number) {
        super(value);
    }
    static identity: string = 'focusOnTouch';
    applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
        if (reset) {
            // commomPeerNode.resetBackgroundColor();
        } else {
            node.focusOnTouchAttribute(numberToBool(this.value!));
        }
    }
    static factory(value: number): FocusOnTouchModifier {
        return new FocusOnTouchModifier(value)
    }
}

class FocusBoxModifier extends ModifierWithKey<FocusBoxStyle | undefined> {
    constructor(value: FocusBoxStyle | undefined) {
        super(value);
    }
    static identity: string = 'focusBox';
    applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
        if (reset) {
            // commomPeerNode.resetBackgroundColor();
        } else {
            node.focusBoxAttribute(this.value);
        }
    }
    static factory(value: FocusBoxStyle | undefined): FocusBoxModifier {
        return new FocusBoxModifier(value)
    }
}

class OnAppearModifier extends ModifierWithKey<(() => void) | undefined> {
    constructor(value: (() => void) | undefined) {
        super(value);
    }
    static identity: string = 'onAppear';
    applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
        if (reset) {
            // commomPeerNode.resetBackgroundColor();
        } else {
            node.onAppearAttribute(this.value);
        }
    }
    
    static factory(value: (() => void) | undefined): OnAppearModifier {
        return new OnAppearModifier(value)
    }
}

class OnDisAppearModifier extends ModifierWithKey<(() => void) | undefined> {
    constructor(value: (() => void) | undefined) {
        super(value);
    }
    static identity: string = 'onDisappear';
    applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
        if (reset) {
            // commomPeerNode.resetBackgroundColor();
        } else {
            node.onDisAppearAttribute(this.value);
        }
    }
    
    static factory(value: (() => void) | undefined): OnDisAppearModifier {
        return new OnDisAppearModifier(value)
    }
}

class OnAttachModifier extends ModifierWithKey<(() => void) | undefined> {
    constructor(value: (() => void) | undefined) {
        super(value);
    }
    static identity: string = 'onAttach';
    applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
        if (reset) {
            // commomPeerNode.resetBackgroundColor();
        } else {
            node.onAttachAttribute(this.value);
        }
    }
    
    static factory(value: (() => void) | undefined): OnAttachModifier {
        return new OnAttachModifier(value)
    }
}

class OnDetachModifier extends ModifierWithKey<(() => void) | undefined> {
    constructor(value: (() => void) | undefined) {
        super(value);
    }
    static identity: string = 'onDetach';
    applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
        if (reset) {
            // commomPeerNode.resetBackgroundColor();
        } else {
            node.onDetachAttribute(this.value);
        }
    }
    
    static factory(value: (() => void) | undefined): OnDetachModifier {
        return new OnDetachModifier(value)
    }
}

class OnAreaChangeModifier extends ModifierWithKey<((oldValue: Area,newValue: Area) => void) | undefined> {
    constructor(value: ((oldValue: Area,newValue: Area) => void) | undefined) {
        super(value);
    }
    static identity: string = 'onAreaChange';
    applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
        if (reset) {
            // commomPeerNode.resetBackgroundColor();
        } else {
            node.onAreaChangeAttribute(this.value);
        }
    }
    
    static factory(value: ((oldValue: Area,newValue: Area) => void) | undefined): OnAreaChangeModifier {
        return new OnAreaChangeModifier(value)
    }
}

class VisibilityModifier extends ModifierWithKey<Visibility | undefined> {
    constructor(value: Visibility | undefined) {
        super(value);
    }
    static identity: string = 'visibility';
    applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
        if (reset) {
            // commomPeerNode.resetBackgroundColor();
        } else {
            node.visibilityAttribute(this.value);
        }
    }
    static factory(value: Visibility | undefined): VisibilityModifier {
        return new VisibilityModifier(value)
    }
}

class EnabledModifier extends ModifierWithKey<number> {
    constructor(value: number) {
        super(value);
    }
    static identity: string = 'enabled';
    applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
        if (reset) {
            // commomPeerNode.resetBackgroundColor();
        } else {
            node.enabledAttribute(numberToBool(this.value!));
        }
    }
    static factory(value: number): EnabledModifier {
        return new EnabledModifier(value)
    }
}

class OnSizeChangeModifier extends ModifierWithKey<((oldValue: SizeOptions, newValue: SizeOptions) => void) | undefined> {
    constructor(value: ((oldValue: SizeOptions, newValue: SizeOptions) => void) | undefined) {
        super(value);
    }
    static identity: string = 'onSizeChange';
    applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
        if (reset) {
            // commomPeerNode.resetBackgroundColor();
        } else {
            node.onSizeChangeAttribute(this.value);
        }
    }
    static factory(value: ((oldValue: SizeOptions, newValue: SizeOptions) => void) | undefined): OnSizeChangeModifier {
        return new OnSizeChangeModifier(value)
    }
}

class KeyModifier extends ModifierWithKey<string | undefined> {
    constructor(value: string | undefined) {
        super(value);
    }
    static identity: string = 'key';  
    applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
        if (reset) {
            // commomPeerNode.resetBackgroundColor();
        } else {
            node.keyAttribute(this.value);
        }
    }
    static factory(value: string | undefined): KeyModifier {
        return new KeyModifier(value)
    }
}

class RestoreIdModifier extends ModifierWithKey<number | undefined> {
    constructor(value: number | undefined) {
        super(value);
    }
    static identity: string = 'restoreId';
    applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
        if (reset) {
            // commomPeerNode.resetBackgroundColor();
        } else {
            node.restoreIdAttribute(this.value);
        }
    }
    static factory(value: number | undefined): RestoreIdModifier {
        return new RestoreIdModifier(value)
    }
}

class BackgroundImageModifierOptions {
    src: ResourceStr | PixelMap | undefined
    repeat?: ImageRepeat | undefined
}
class BackgroundImageModifier extends ModifierWithKey<BackgroundImageModifierOptions> {
    constructor(value: BackgroundImageModifierOptions) {
        super(value);
    }
    static identity: string = 'backgroundImage';
    applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
        if (reset) {
            // commomPeerNode.resetBackgroundColor();
        } else {
            node.backgroundImage0Attribute(this.value?.src, this.value?.repeat);
        }
    }
    static factory(value: BackgroundImageModifierOptions): BackgroundImageModifier {
        return new BackgroundImageModifier(value)
    }
}

class FocusScopeIdModifierOption{
    id: string | undefined
    isGroup?: boolean
    arrowStepOut?: boolean
}

class FocusScopeIdModifier extends ModifierWithKey<FocusScopeIdModifierOption> {
    constructor(value: FocusScopeIdModifierOption) {
        super(value);
    }
    static identity: string = 'focusScopeId';
    applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
        if (reset) {
            // commomPeerNode.resetBackgroundColor();
        } else {
            node.focusScopeId1Attribute(this.value?.id, this.value?.isGroup, this.value?.arrowStepOut);
        }
    }
    static factory(value: FocusScopeIdModifierOption): FocusScopeIdModifier {
        return new FocusScopeIdModifier(value)
    }
}

class FocusScopePriorityModifierOption {
    scopeId: string | undefined
    priority?: FocusPriority
}

class FocusScopePriorityModifier extends ModifierWithKey<FocusScopePriorityModifierOption> {
    constructor(value: FocusScopePriorityModifierOption) {
        super(value);
    }
    static identity: string = 'focusScopePriority';
    applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
        if (reset) {
            // commomPeerNode.resetBackgroundColor();
        } else {
            node.focusScopePriorityAttribute(this.value?.scopeId, this.value?.priority);
        }
    }
    static factory(value: FocusScopePriorityModifierOption): FocusScopePriorityModifier {
        return new FocusScopePriorityModifier(value)
    }
}

class BackgroundImageSizeModifier extends ModifierWithKey<SizeOptions | ImageSize | undefined> {
    constructor(value: SizeOptions | ImageSize | undefined) {
        super(value);
    }
    static identity: string = 'backgroundImageSize';
    applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
        if (reset) {
            // commomPeerNode.resetBackgroundColor();
        } else {
            node.backgroundImageSizeAttribute(this.value);
        }
    }
    static factory(value: SizeOptions | ImageSize | undefined): BackgroundImageSizeModifier {
        return new BackgroundImageSizeModifier(value)
    }
}

class BackgroundImagePositionModifier extends ModifierWithKey<Position | Alignment | undefined> {
    constructor(value: Position | Alignment | undefined) {
        super(value);
    }
    static identity: string = 'backgroundImagePosition';
    applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
        if (reset) {
            // commomPeerNode.resetBackgroundColor();
        } else {
            node.backgroundImagePositionAttribute(this.value);
        }
    }
    static factory(value: Position | Alignment | undefined): BackgroundImagePositionModifier {
        return new BackgroundImagePositionModifier(value)
    }
}

class BackgroundImageResizableModifier extends ModifierWithKey<ResizableOptions | undefined> {
    constructor(value: ResizableOptions | undefined) {
        super(value);
    }
    static identity: string = 'backgroundImageResizable';
    applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
        if (reset) {
            // commomPeerNode.resetBackgroundColor();
        } else {
            node.backgroundImageResizableAttribute(this.value);
        }
    }
    static factory(value: ResizableOptions | undefined): BackgroundImageResizableModifier {
        return new BackgroundImageResizableModifier(value)
    }
}

class OnGestureJudgeBeginModifier extends ModifierWithKey<((gestureInfo: GestureInfo, event: BaseGestureEvent) => GestureJudgeResult) | undefined> {
    constructor(value: ((gestureInfo: GestureInfo, event: BaseGestureEvent) => GestureJudgeResult) | undefined) {
        super(value);
    }
    static identity: string = 'onGestureJudgeBegin';
    applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
        if (reset) {
            // commomPeerNode.resetBackgroundColor();
        } else {
            node.onGestureJudgeBeginAttribute(this.value);
        }
    }

    static factory(value: ((gestureInfo: GestureInfo, event: BaseGestureEvent) => GestureJudgeResult) | undefined): OnGestureJudgeBeginModifier {
        return new OnGestureJudgeBeginModifier(value)
    }
}

class OnGestureRecognizerJudgeBeginModifierOptions {
    callback_: GestureRecognizerJudgeBeginCallback | undefined
    exposeInnerGesture?: boolean
}

class OnGestureRecognizerJudgeBeginModifier extends ModifierWithKey<OnGestureRecognizerJudgeBeginModifierOptions> {
    constructor(value: OnGestureRecognizerJudgeBeginModifierOptions) {
        super(value);
    }
    static identity: string = 'onGestureRecognizerJudgeBegin';
    applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
        if (reset) {
            // commomPeerNode.resetBackgroundColor();
        } else {
            node.onGestureRecognizerJudgeBegin1Attribute(this.value?.callback_, this.value?.exposeInnerGesture);
        }
    }
    static factory(value: OnGestureRecognizerJudgeBeginModifierOptions): OnGestureRecognizerJudgeBeginModifier {
        return new OnGestureRecognizerJudgeBeginModifier(value)
    }
}

class ShouldBuiltInRecognizerParallelWithModifier extends ModifierWithKey<ShouldBuiltInRecognizerParallelWithCallback | undefined> {
    constructor(value: ShouldBuiltInRecognizerParallelWithCallback | undefined) {
        super(value);
    }
    static identity: string = 'shouldBuiltInRecognizerParallelWith';
    applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
        if (reset) {
            // commomPeerNode.resetBackgroundColor();
        } else {
            node.shouldBuiltInRecognizerParallelWithAttribute(this.value);
        }
    }
    static factory(value: ShouldBuiltInRecognizerParallelWithCallback | undefined): ShouldBuiltInRecognizerParallelWithModifier {
        return new ShouldBuiltInRecognizerParallelWithModifier(value)
    }
}

class MonopolizeEventsModifier extends ModifierWithKey<number> {
    constructor(value: number) {
        super(value);
    }
    static identity: string = 'monopolizeEvents';
    applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
        if (reset) {
            // commomPeerNode.resetBackgroundColor();
        } else {
            node.monopolizeEventsAttribute(numberToBool(this.value!));
        }
    }
    static factory(value: number): MonopolizeEventsModifier {
        return new MonopolizeEventsModifier(value)
    }
}

class OnVisibleAreaChangeModifierOptions {
    ratios: Array<number> | undefined
    event: VisibleAreaChangeCallback | undefined
}

class OnVisibleAreaChangeModifier extends ModifierWithKey<OnVisibleAreaChangeModifierOptions> {
    constructor(value: OnVisibleAreaChangeModifierOptions) {
        super(value);
    }
    static identity: string = 'onVisibleAreaChange';
    applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
        if (reset) {
            // commomPeerNode.resetBackgroundColor();
        } else {
            node.onVisibleAreaChangeAttribute(this.value?.ratios, this.value?.event);
        }
    }
    static factory(value: OnVisibleAreaChangeModifierOptions): OnVisibleAreaChangeModifier {
        return new OnVisibleAreaChangeModifier(value)
    }
}

class OnVisibleAreaApproximateChangeModifierOptions {
    options: VisibleAreaEventOptions | undefined
    event: VisibleAreaChangeCallback | undefined
}
class OnVisibleAreaApproximateChangeModifier extends ModifierWithKey<OnVisibleAreaApproximateChangeModifierOptions> {
    constructor(value: OnVisibleAreaApproximateChangeModifierOptions) {
        super(value);
    }
    static identity: string = 'onVisibleAreaApproximateChange';
    applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
        if (reset) {
            // commomPeerNode.resetBackgroundColor();
        } else {
            node.onVisibleAreaApproximateChangeAttribute(this.value?.options, this.value?.event);
        }
    }
    static factory(value: OnVisibleAreaApproximateChangeModifierOptions): OnVisibleAreaApproximateChangeModifier {
        return new OnVisibleAreaApproximateChangeModifier(value)
    }
}

class KeyboardShortcutModifierOptions {
    value: string | FunctionKey | undefined
    keys: Array<ModifierKey> | undefined
    action?: (() => void)
}

class KeyboardShortcutModifier extends ModifierWithKey<KeyboardShortcutModifierOptions> {
    constructor(value: KeyboardShortcutModifierOptions) {
        super(value);
    }
    static identity: string = 'keyboardShortcut';
    applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
        if (reset) {
            // commomPeerNode.resetBackgroundColor();
        } else {
            node.keyboardShortcutAttribute(this.value?.value, this.value?.keys, this.value?.action);
        }
    }
    static factory(value: KeyboardShortcutModifierOptions): KeyboardShortcutModifier {
        return new KeyboardShortcutModifier(value)
    }
}

class HitTestBehaviorModifier extends ModifierWithKey<HitTestMode> {
    constructor(value: HitTestMode) {
        super(value);
    }
    static identity: string = 'hitTestBehavior';
    applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
        if (reset) {
            // commomPeerNode.resetBackgroundColor();
        } else {
            node.hitTestBehaviorAttribute(this.value);
        }
    }
    static factory(value: HitTestMode): HitTestBehaviorModifier {
        return new HitTestBehaviorModifier(value)
    }
}

class ResponseRegionModifier extends ModifierWithKey<Array<Rectangle> | Rectangle | undefined> {
    constructor(value: Array<Rectangle> | Rectangle | undefined) {
        super(value);
    }
    static identity: string = 'responseRegion';
    applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
        if (reset) {
            // commomPeerNode.resetResponseRegion();
        } else {
            node.responseRegionAttribute(this.value);
        }
    }
    static factory(value: Array<Rectangle> | Rectangle | undefined): ResponseRegionModifier {
        return new ResponseRegionModifier(value)
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
      if (value) {
          modifierWithKey(this._modifiersWithKeys, ResponseRegionModifier.identity, ResponseRegionModifier.factory, value as (Array<Rectangle> | Rectangle | undefined));
      } else {
          modifierNullWithKey(this._modifiersWithKeys, ResponseRegionModifier.identity)
      }
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
      if (value) {
          modifierWithKey(this._modifiersWithKeys, HitTestBehaviorModifier.identity, HitTestBehaviorModifier.factory, value as HitTestMode);
      } else {
          modifierNullWithKey(this._modifiersWithKeys, HitTestBehaviorModifier.identity)
      }
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
      if (value) {
          modifierWithKey(this._modifiersWithKeys, BackgroundImageSizeModifier.identity, BackgroundImageSizeModifier.factory, value as (SizeOptions | ImageSize | undefined));
      } else {
          modifierNullWithKey(this._modifiersWithKeys, BackgroundImageSizeModifier.identity)
      }
      return this
  }
  public backgroundImagePosition(value: Position | Alignment | undefined): this {
      if (value) {
          modifierWithKey(this._modifiersWithKeys, BackgroundImagePositionModifier.identity, BackgroundImagePositionModifier.factory, value as (Position | Alignment | undefined));
      } else {
          modifierNullWithKey(this._modifiersWithKeys, BackgroundImagePositionModifier.identity)
      }
      return this
  }
  public backgroundEffect(options: BackgroundEffectOptions | undefined, sysOptions?: SystemAdaptiveOptions): this {
      return this
  }
  public backgroundImageResizable(value: ResizableOptions | undefined): this {
      if (value) {
          modifierWithKey(this._modifiersWithKeys, BackgroundImageResizableModifier.identity, BackgroundImageResizableModifier.factory, value);
      } else {
          modifierNullWithKey(this._modifiersWithKeys, BackgroundImageResizableModifier.identity)
      }
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
      if (value) {
          modifierWithKey(this._modifiersWithKeys, OnHoverModifier.identity, OnHoverModifier.factory, value);
      } else {
          modifierNullWithKey(this._modifiersWithKeys, OnHoverModifier.identity)
      }
      return this
  }
  public onHoverMove(value: ((parameter: HoverEvent) => void) | undefined): this {
      if (value) {
          modifierWithKey(this._modifiersWithKeys, OnHoverMoveModifier.identity, OnHoverMoveModifier.factory, value);
      } else {
          modifierNullWithKey(this._modifiersWithKeys, OnHoverMoveModifier.identity)
      }
      return this
  }
  public onAccessibilityHover(value: AccessibilityCallback | undefined): this {
      return this
  }
  public hoverEffect(value: HoverEffect | undefined): this {
      if (value) {
          modifierWithKey(this._modifiersWithKeys, HoverEffectModifier.identity, HoverEffectModifier.factory, value as (HoverEffect | undefined));
      } else {
          modifierNullWithKey(this._modifiersWithKeys, HoverEffectModifier.identity)
      }
      return this
  }
  public onMouse(value: ((event: MouseEvent) => void) | undefined): this {
      if (value) {
          modifierWithKey(this._modifiersWithKeys, OnMouseModifier.identity, OnMouseModifier.factory, value);
      } else {
          modifierNullWithKey(this._modifiersWithKeys, OnMouseModifier.identity)
      }
      return this
  }
  public onTouch(value: ((event: TouchEvent) => void) | undefined): this {
      if (value) {
          modifierWithKey(this._modifiersWithKeys, OnTouchModifier.identity, OnTouchModifier.factory, value);
      } else {
          modifierNullWithKey(this._modifiersWithKeys, OnTouchModifier.identity)
      }
      return this
  }
  public onKeyEvent(value: ((event: KeyEvent) => boolean) | undefined): this {
      if (value) {
          modifierWithKey(this._modifiersWithKeys, OnKeyEventModifier.identity, OnKeyEventModifier.factory, value);
      } else {
          modifierNullWithKey(this._modifiersWithKeys, OnKeyEventModifier.identity)
      }
      return this
  }
  public onDigitalCrown(value: ((parameter: CrownEvent) => void) | undefined): this {
      return this
  }
  public onKeyPreIme(value: ((parameter: KeyEvent) => boolean) | undefined): this {
      if (value) {
          modifierWithKey(this._modifiersWithKeys, OnKeyPreImeModifier.identity, OnKeyPreImeModifier.factory, value);
      } else {
          modifierNullWithKey(this._modifiersWithKeys, OnKeyPreImeModifier.identity)
      }
      return this
  }
  public onKeyEventDispatch(value: ((parameter: KeyEvent) => boolean) | undefined): this {
      if (value) {
          modifierWithKey(this._modifiersWithKeys, OnKeyEventDispatchModifier.identity, OnKeyEventDispatchModifier.factory, value);
      } else {
          modifierNullWithKey(this._modifiersWithKeys, OnKeyEventDispatchModifier.identity)
      }
      return this
  }
  public onFocusAxisEvent(value: ((parameter: FocusAxisEvent) => void) | undefined): this {
      if (value) {
          modifierWithKey(this._modifiersWithKeys, OnFocusAxisEventModifier.identity, OnFocusAxisEventModifier.factory, value);
      } else {
          modifierNullWithKey(this._modifiersWithKeys, OnFocusAxisEventModifier.identity)
      }
      return this
  }
  public onAxisEvent(value: ((parameter: AxisEvent) => void) | undefined): this {
      if (value) {
          modifierWithKey(this._modifiersWithKeys, OnAxisEventModifier.identity, OnAxisEventModifier.factory, value);
      } else {
          modifierNullWithKey(this._modifiersWithKeys, OnAxisEventModifier.identity)
      }
      return this
  }
  public focusable(value: boolean | undefined): this {
      if (value !== undefined) {
          modifierWithKey(this._modifiersWithKeys, FocusableModifier.identity, FocusableModifier.factory, boolToNumber(value));
      } else {
          modifierNullWithKey(this._modifiersWithKeys, FocusableModifier.identity)
      }
      return this
  }
  public nextFocus(value: FocusMovement | undefined): this {
      if (value) {
          modifierWithKey(this._modifiersWithKeys, NextFocusModifier.identity, NextFocusModifier.factory, value);
      } else {
          modifierNullWithKey(this._modifiersWithKeys, NextFocusModifier.identity)
      }
      return this
  }
  public tabStop(value: boolean | undefined): this {
      if (value !== undefined) {
          modifierWithKey(this._modifiersWithKeys, TabStopModifier.identity, TabStopModifier.factory, boolToNumber(value));
      } else {
          modifierNullWithKey(this._modifiersWithKeys, TabStopModifier.identity)
      }
      return this
  }
  public onFocus(value: (() => void) | undefined): this {
      if (value) {
          modifierWithKey(this._modifiersWithKeys, OnFocusModifier.identity, OnFocusModifier.factory, value);
      } else {
          modifierNullWithKey(this._modifiersWithKeys, OnFocusModifier.identity)
      }
      return this
  }
  public onBlur(value: (() => void) | undefined): this {
      if (value) {
          modifierWithKey(this._modifiersWithKeys, OnBlurModifier.identity, OnBlurModifier.factory, value);
      } else {
          modifierNullWithKey(this._modifiersWithKeys, OnBlurModifier.identity)
      }
      return this
  }
  public tabIndex(value: number | undefined): this {
      if (value != null) {
         modifierWithKey(this._modifiersWithKeys, TabIndexModifier.identity, TabIndexModifier.factory, value);
      } else {
         modifierNullWithKey(this._modifiersWithKeys, TabIndexModifier.identity)
      }
      return this;
  }
  public defaultFocus(value: boolean | undefined): this {
      if (value !== undefined) {
          modifierWithKey(this._modifiersWithKeys, DefaultFocusModifier.identity, DefaultFocusModifier.factory, boolToNumber(value));
      } else {
          modifierNullWithKey(this._modifiersWithKeys, DefaultFocusModifier.identity)
      }
      return this
  }
  public groupDefaultFocus(value: boolean | undefined): this {
      if (value !== undefined) {
          modifierWithKey(this._modifiersWithKeys, GroupDefaultFocusModifier.identity, GroupDefaultFocusModifier.factory, boolToNumber(value));
      } else {
          modifierNullWithKey(this._modifiersWithKeys, GroupDefaultFocusModifier.identity)
      }
      return this
  }
  public focusOnTouch(value: boolean | undefined): this {
      if (value !== undefined) {
          modifierWithKey(this._modifiersWithKeys, FocusOnTouchModifier.identity, FocusOnTouchModifier.factory, boolToNumber(value));
      } else {
          modifierNullWithKey(this._modifiersWithKeys, FocusOnTouchModifier.identity)
      }
      return this
  }
  public focusBox(value: FocusBoxStyle | undefined): this {
      if (value) {
          modifierWithKey(this._modifiersWithKeys, FocusBoxModifier.identity, FocusBoxModifier.factory, value);
      } else {
          modifierNullWithKey(this._modifiersWithKeys, FocusBoxModifier.identity)
      }
      return this
  }
  public animationStart(value: AnimateParam | undefined): this {
    return this
  }
  public animationStop(value: AnimateParam | undefined): this {
    return this
  }
  public __createOrSetAnimatableProperty<T>(functionName: string, value: number | AnimatableArithmetic<T>,
    callback: (value: number | AnimatableArithmetic<T>) => void): void {}
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
      if (value) {
          modifierWithKey(this._modifiersWithKeys, OnAppearModifier.identity, OnAppearModifier.factory, value);
      } else {
          modifierNullWithKey(this._modifiersWithKeys, OnAppearModifier.identity)
      }
      return this
  }
  public onDisAppear(value: (() => void) | undefined): this {
      if (value) {
          modifierWithKey(this._modifiersWithKeys, OnDisAppearModifier.identity, OnDisAppearModifier.factory, value);
      } else {
          modifierNullWithKey(this._modifiersWithKeys, OnDisAppearModifier.identity)
      }
      return this
  }
  public onAttach(value: (() => void) | undefined): this {
      if (value) {
          modifierWithKey(this._modifiersWithKeys, OnAttachModifier.identity, OnAttachModifier.factory, value);
      } else {
          modifierNullWithKey(this._modifiersWithKeys, OnAttachModifier.identity)
      }
      return this
  }
  public onDetach(value: (() => void) | undefined): this {
      if (value) {
          modifierWithKey(this._modifiersWithKeys, OnDetachModifier.identity, OnDetachModifier.factory, value);
      } else {
          modifierNullWithKey(this._modifiersWithKeys, OnDetachModifier.identity)
      }
      return this
  }
  public onAreaChange(value: ((oldValue: Area,newValue: Area) => void) | undefined): this {
      if (value) {
          modifierWithKey(this._modifiersWithKeys, OnAreaChangeModifier.identity, OnAreaChangeModifier.factory, value);
      } else {
          modifierNullWithKey(this._modifiersWithKeys, OnAreaChangeModifier.identity)
      }
      return this
  }
  public visibility(value: Visibility | undefined): this {
      if (value) {
          modifierWithKey(this._modifiersWithKeys, VisibilityModifier.identity, VisibilityModifier.factory, value as (Visibility | undefined));
      } else {
          modifierNullWithKey(this._modifiersWithKeys, VisibilityModifier.identity)
      }
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
      if (value !== undefined) {
          modifierWithKey(this._modifiersWithKeys, EnabledModifier.identity, EnabledModifier.factory, boolToNumber(value));
      } else {
          modifierNullWithKey(this._modifiersWithKeys, EnabledModifier.identity)
      }
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
  public allowDrop(value: Array<UniformDataType> | null | undefined): this {
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
      if (value) {
          modifierWithKey(this._modifiersWithKeys, KeyModifier.identity, KeyModifier.factory, value);
      } else {
          modifierNullWithKey(this._modifiersWithKeys, KeyModifier.identity)
      }
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
      if (value) {
          modifierWithKey(this._modifiersWithKeys, RestoreIdModifier.identity, RestoreIdModifier.factory, value);
      } else {
          modifierNullWithKey(this._modifiersWithKeys, RestoreIdModifier.identity)
      }
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
      if (value) {
          modifierWithKey(this._modifiersWithKeys, OnGestureJudgeBeginModifier.identity, OnGestureJudgeBeginModifier.factory, value);
      } else {
          modifierNullWithKey(this._modifiersWithKeys, OnGestureJudgeBeginModifier.identity)
      }
      return this
  }
  public onGestureRecognizerJudgeBegin(callback_: GestureRecognizerJudgeBeginCallback | undefined, exposeInnerGesture?: boolean): this {
      if (callback_) {
          modifierWithKey(this._modifiersWithKeys, OnGestureRecognizerJudgeBeginModifier.identity, OnGestureRecognizerJudgeBeginModifier.factory, { callback_, exposeInnerGesture } as OnGestureRecognizerJudgeBeginModifierOptions);
      } else {
          modifierNullWithKey(this._modifiersWithKeys, OnGestureRecognizerJudgeBeginModifier.identity)
      }
      return this
  }
  public shouldBuiltInRecognizerParallelWith(value: ShouldBuiltInRecognizerParallelWithCallback | undefined): this {
      if (value) {
          modifierWithKey(this._modifiersWithKeys, ShouldBuiltInRecognizerParallelWithModifier.identity, ShouldBuiltInRecognizerParallelWithModifier.factory, value);
      } else {
          modifierNullWithKey(this._modifiersWithKeys, ShouldBuiltInRecognizerParallelWithModifier.identity)
      }
      return this
  }
  public monopolizeEvents(value: boolean | undefined): this {
      if (value !== undefined) {
          modifierWithKey(this._modifiersWithKeys, MonopolizeEventsModifier.identity, MonopolizeEventsModifier.factory, boolToNumber(value));
      } else {
          modifierNullWithKey(this._modifiersWithKeys, MonopolizeEventsModifier.identity)
      }
      return this
  }
  public onTouchIntercept(value: ((parameter: TouchEvent) => HitTestMode) | undefined): this {
      return this
  }
  public onSizeChange(value: SizeChangeCallback | undefined): this {
      if (value) {
          modifierWithKey(this._modifiersWithKeys, OnSizeChangeModifier.identity, OnSizeChangeModifier.factory, value);
      } else {
          modifierNullWithKey(this._modifiersWithKeys, OnSizeChangeModifier.identity)
      }
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
  public background(builder: CustomBuilder | undefined, options?: BackgroundOptions): this {
      return this
  }
  public backgroundImage(src: ResourceStr | PixelMap | undefined, repeat?: ImageRepeat | undefined): this {
      if (src) {
          modifierWithKey(this._modifiersWithKeys, BackgroundImageModifier.identity, BackgroundImageModifier.factory, { src, repeat } as BackgroundImageModifierOptions);
      } else {
          modifierNullWithKey(this._modifiersWithKeys, BackgroundImageModifier.identity)
      }
      return this
  }
  public backgroundBlurStyle(style: BlurStyle | undefined, options?: BackgroundBlurStyleOptions, sysOptions?: SystemAdaptiveOptions): this {
      return this
  }
  public foregroundBlurStyle(style: BlurStyle | undefined, options?: ForegroundBlurStyleOptions, sysOptions?: SystemAdaptiveOptions): this {
      return this
  }
  public focusScopeId(id: string | undefined, isGroup?: boolean, arrowStepOut?: boolean): this {
      if (id) {
          modifierWithKey(this._modifiersWithKeys, FocusScopeIdModifier.identity, FocusScopeIdModifier.factory, { id, isGroup, arrowStepOut } as FocusScopeIdModifierOption);
      } else {
          modifierNullWithKey(this._modifiersWithKeys, FocusScopeIdModifier.identity)
      }
      return this
  }
  public focusScopePriority(scopeId: string | undefined, priority?: FocusPriority): this {
      if (scopeId) {
          modifierWithKey(this._modifiersWithKeys, FocusScopePriorityModifier.identity, FocusScopePriorityModifier.factory, { scopeId, priority } as FocusScopePriorityModifierOption);
      } else {
          modifierNullWithKey(this._modifiersWithKeys, FocusScopePriorityModifier.identity)
      }
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
  public bindContentCover(isShow: boolean | undefined | Bindable<boolean>, builder: CustomBuilder | undefined, type?: ModalTransition | ContentCoverOptions): this {
      return this
  }
  public bindSheet(isShow: boolean | undefined | Bindable<boolean>, builder: CustomBuilder | undefined, options?: SheetOptions): this {
      return this
  }
  public onVisibleAreaChange(ratios: Array<number> | undefined, event: VisibleAreaChangeCallback | undefined): this {
      if (ratios && event) {
          modifierWithKey(this._modifiersWithKeys, OnVisibleAreaChangeModifier.identity, OnVisibleAreaChangeModifier.factory, { ratios, event } as OnVisibleAreaChangeModifierOptions);
      } else {
          modifierNullWithKey(this._modifiersWithKeys, OnVisibleAreaChangeModifier.identity)
      }
      return this
  }
  public onVisibleAreaApproximateChange(options: VisibleAreaEventOptions | undefined, event: VisibleAreaChangeCallback | undefined): this {
      if (options && event) {
          modifierWithKey(this._modifiersWithKeys, OnVisibleAreaApproximateChangeModifier.identity, OnVisibleAreaApproximateChangeModifier.factory, { options, event } as OnVisibleAreaApproximateChangeModifierOptions);
      } else {
          modifierNullWithKey(this._modifiersWithKeys, OnVisibleAreaApproximateChangeModifier.identity)
      }
      return this
  }
  public keyboardShortcut(value: string | FunctionKey | undefined, keys: Array<ModifierKey> | undefined, action?: (() => void)): this {
      if (value) {
          modifierWithKey(this._modifiersWithKeys, KeyboardShortcutModifier.identity, KeyboardShortcutModifier.factory, { value, keys, action } as KeyboardShortcutModifierOptions);
      } else {
          modifierNullWithKey(this._modifiersWithKeys, KeyboardShortcutModifier.identity)
      }
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

export function applyAttributeModifierBase<T, MethodSet extends CommonMethodModifier, MethodComponent extends ArkCommonMethodComponent>
    (modifier: AttributeModifier<T>, attributeSet: () => MethodSet, func: (component: MethodComponent, ...params: FixedArray<Object>) => void, updaterReceiver: () => MethodComponent, node: ArkCommonMethodPeer): void {
    let attributeSet_ = attributeSet();
    let isAttributeUpdater: boolean = (modifier instanceof AttributeUpdater);
    if (isAttributeUpdater) {
        let attributeUpdater = modifier as object as AttributeUpdater<T>
        let needUpdate: boolean = false;
        if (!attributeUpdater.peerNode_) {
            attributeUpdater.initializeModifier(attributeSet_ as Object as T);
            needUpdate = true;
        } else if (node !== attributeUpdater.peerNode_) {
            attributeUpdater.onComponentChanged(attributeSet_ as Object as T);
            needUpdate = true;
        }
        if (needUpdate) {
            attributeUpdater.peerNode_ = node;
            let receiver = updaterReceiver();
            receiver.setPeer(node);
            attributeUpdater.attribute = receiver as Object as T;
            attributeUpdater.updateConstructorParams = (...params: FixedArray<Object>) => {
                func(receiver, ...params);
                receiver.applyAttributesFinish();
                return receiver as Object as T;
            };
        }
    }
    let isInit: boolean = true;
    let currentState = node.getStateStyleMutable();
    if (currentState === undefined) {
        currentState = node.getOrCreateStateStyleMutable()!;
    } else {
        isInit = false;
    }
    if (isAttributeUpdater) {
        applyUIAttributesUpdate(modifier, attributeSet_, currentState.value, isInit);
    } else {
        applyUIAttributes(modifier, attributeSet_, currentState.value);
    }
    attributeSet_.applyModifierPatch(node);
}

export function applyCommonModifier(peerNode: ArkCommonMethodPeer, modifier: AttributeModifier<CommonMethod>) {
    let attributeSet = (): CommonMethodModifier => {
        let commonModifier = modifier as object as CommonModifier;
        let initModifier = peerNode._attributeSet ? peerNode._attributeSet! : new CommonMethodModifier();
        initModifier.mergeModifier(commonModifier);
        peerNode._attributeSet = initModifier;
        return initModifier;
    }
    let constructParam = (component:ArkCommonMethodComponent, ...params: FixedArray<Object>): void => {
    };
    let updaterReceiver = (): ArkCommonMethodComponent => {
        let component: ArkCommonMethodComponent = new ArkCommonMethodComponent();
        component.setPeer(peerNode);
        return component;
    };
    applyAttributeModifierBase(modifier, attributeSet, constructParam, updaterReceiver, peerNode);
}