/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/// <reference path='./import.ts' />

import { ArkScrollable } from "./ArkScrollable";

class ItemConstraintSizeModifier extends ModifierWithKey<ArkConstraintSizeOptions> {
  constructor(value: ArkConstraintSizeOptions) {
    super(value);
  }
  static identity: Symbol = Symbol('itemConstraintSize');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().waterFlow.resetItemConstraintSize(node);
    } else {
      getUINativeModule().waterFlow.setItemConstraintSize(node, this.value.minWidth,
        this.value.maxWidth, this.value.minHeight, this.value.maxHeight);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue.minWidth, this.value.minWidth) ||
      !isBaseOrResourceEqual(this.stageValue.maxWidth, this.value.maxWidth) ||
      !isBaseOrResourceEqual(this.stageValue.minHeight, this.value.minHeight) ||
      !isBaseOrResourceEqual(this.stageValue.maxHeight, this.value.maxHeight);
  }
}

class ColumnsTemplateModifier extends ModifierWithKey<string> {
  constructor(value: string) {
    super(value);
  }
  static identity: Symbol = Symbol('columnsTemplate');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().waterFlow.resetColumnsTemplate(node);
    } else {
      getUINativeModule().waterFlow.setColumnsTemplate(node, this.value);
    }
  }
}

class RowsTemplateModifier extends ModifierWithKey<string> {
  constructor(value: string) {
    super(value);
  }
  static identity: Symbol = Symbol('rowsTemplate');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().waterFlow.resetRowsTemplate(node);
    } else {
      getUINativeModule().waterFlow.setRowsTemplate(node, this.value);
    }
  }
}

class EnableScrollInteractionModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity = Symbol('enableScrollInteraction');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().waterFlow.resetEnableScrollInteraction(node);
    } else {
      getUINativeModule().waterFlow.setEnableScrollInteraction(node, this.value);
    }
  }
}

class WaterFlowClipModifier extends ModifierWithKey<boolean | object> {
  constructor(value: boolean | object) {
    super(value);
  }
  static identity: Symbol = Symbol('waterFlowclip');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetClipWithEdge(node);
    } else {
      getUINativeModule().common.setClipWithEdge(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return true;
  }
}

class RowsGapModifier extends ModifierWithKey<number | string> {
  constructor(value: number | string) {
    super(value);
  }
  static identity: Symbol = Symbol('rowsGap');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().waterFlow.resetRowsGap(node);
    } else {
      getUINativeModule().waterFlow.setRowsGap(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class ColumnsGapModifier extends ModifierWithKey<number | string> {
  constructor(value: number | string) {
    super(value);
  }
  static identity: Symbol = Symbol('columnsGap');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().waterFlow.resetColumnsGap(node);
    } else {
      getUINativeModule().waterFlow.setColumnsGap(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class LayoutDirectionModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('layoutDirection');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().waterFlow.resetLayoutDirection(node);
    } else {
      getUINativeModule().waterFlow.setLayoutDirection(node, this.value);
    }
  }
}

class NestedScrollModifier extends ModifierWithKey<ArkNestedScrollOptions> {
  constructor(value: ArkNestedScrollOptions) {
    super(value);
  }
  static identity: Symbol = Symbol('nestedScroll');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().waterFlow.resetNestedScroll(node);
    } else {
      getUINativeModule().waterFlow.setNestedScroll(node, this.value.scrollForward, this.value.scrollBackward);
    }
  }
}

class FrictionModifier extends ModifierWithKey<number | Resource> {
  constructor(value: number | Resource) {
    super(value);
  }
  static identity: Symbol = Symbol('friction');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().waterFlow.resetFriction(node);
    } else {
      getUINativeModule().waterFlow.setFriction(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class WaterFlowEdgeEffectModifier extends ModifierWithKey<ArkWaterFlowEdgeEffect> {
  constructor(value: ArkWaterFlowEdgeEffect) {
    super(value);
  }
  static identity: Symbol = Symbol('waterFlowEdgeEffect');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().waterFlow.resetEdgeEffect(node);
    } else {
      getUINativeModule().waterFlow.setEdgeEffect(node, this.value?.value, this.value.options?.alwaysEnabled);
    }
  }

  checkObjectDiff(): boolean {
    return !((this.stageValue.value === this.value.value) &&
      (this.stageValue.options === this.value.options));
  }
}

class WaterFlowFadingEdgeModifier extends ModifierWithKey<ArkFadingEdge> {
  constructor(value: ArkFadingEdge) {
    super(value);
  }
  static identity: Symbol = Symbol('waterFlowFadingEdge');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().waterFlow.resetFadingEdge(node);
    } else {
      getUINativeModule().waterFlow.setFadingEdge(node, this.value.value!, this.value.options?.fadingEdgeLength);
    }
  }
  checkObjectDiff(): boolean {
    return !((this.stageValue.value === this.value.value) &&
      (this.stageValue.options === this.value.options));
  }
}


class WaterFlowScrollBarWidthModifier extends ModifierWithKey<string | number> {
  constructor(value: string | number) {
    super(value);
  }
  static identity: Symbol = Symbol('waterFlowScrollBarWidth');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().waterFlow.resetScrollBarWidth(node);
    } else {
      getUINativeModule().waterFlow.setScrollBarWidth(node, this.value);
    }
  }
}

class WaterFlowScrollBarModifier extends ModifierWithKey<BarState> {
  constructor(value: BarState) {
    super(value);
  }
  static identity: Symbol = Symbol('waterFlowScrollBar');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().waterFlow.resetScrollBar(node);
    } else {
      getUINativeModule().waterFlow.setScrollBar(node, this.value);
    }
  }
}

class WaterFlowScrollBarColorModifier extends ModifierWithKey<string | number | Color> {
  constructor(value: string | number | Color) {
    super(value);
  }
  static identity: Symbol = Symbol('waterFlowScrollBarColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().waterFlow.resetScrollBarColor(node);
    } else {
      getUINativeModule().waterFlow.setScrollBarColor(node, this.value);
    }
  }
}

class WaterFlowCachedCountModifier extends ModifierWithKey<ArkScrollableCacheOptions> {
  constructor(value: ArkScrollableCacheOptions) {
    super(value);
  }
  static identity: Symbol = Symbol('waterFlowCachedCount');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().waterFlow.resetCachedCount(node);
    } else {
      getUINativeModule().waterFlow.setCachedCount(node, this.value.count, this.value.show);
    }
  }
}

class WaterFlowFlingSpeedLimitModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('waterFlowFlingSpeedLimit');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().waterFlow.resetFlingSpeedLimit(node);
    } else {
      getUINativeModule().waterFlow.setFlingSpeedLimit(node, this.value);
    }
  }
}

class WaterFlowInitializeModifier extends ModifierWithKey<WaterFlowParam> {
  constructor(value: WaterFlowParam) {
    super(value);
  }
  static identity: Symbol = Symbol('waterFlowInitialize');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().waterFlow.resetWaterFlowInitialize(node);
    } else {
      getUINativeModule().waterFlow.setWaterFlowInitialize(node,
        this.value?.scroller, this.value?.sections, this.value?.layoutMode);
    }
  }
}

interface WaterFlowParam {
  scroller?: Scroller;
  sections?: WaterFlowSections;
  layoutMode?: WaterFlowLayoutMode;
}

class ArkWaterFlowComponent extends ArkScrollable<WaterFlowAttribute> implements WaterFlowAttribute {
  constructor(nativePtr: KNode, classType?: ModifierType) {
    super(nativePtr, classType);
  }
  columnsTemplate(value: string): this {
    modifierWithKey(this._modifiersWithKeys, ColumnsTemplateModifier.identity, ColumnsTemplateModifier, value);
    return this;
  }
  rowsTemplate(value: string): this {
    modifierWithKey(this._modifiersWithKeys, RowsTemplateModifier.identity, RowsTemplateModifier, value);
    return this;
  }
  itemConstraintSize(value: ConstraintSizeOptions): this {
    if (!value) {
      modifierWithKey(
        this._modifiersWithKeys, ItemConstraintSizeModifier.identity, ItemConstraintSizeModifier, undefined);
      return this;
    }
    let arkValue: ArkConstraintSizeOptions = new ArkConstraintSizeOptions();
    arkValue.minWidth = value.minWidth;
    arkValue.maxWidth = value.maxWidth;
    arkValue.minHeight = value.minHeight;
    arkValue.maxHeight = value.maxHeight;
    modifierWithKey(this._modifiersWithKeys, ItemConstraintSizeModifier.identity, ItemConstraintSizeModifier, arkValue);
    return this;
  }
  columnsGap(value: Length): this {
    modifierWithKey(this._modifiersWithKeys, ColumnsGapModifier.identity, ColumnsGapModifier, value);
    return this;
  }
  rowsGap(value: Length): this {
    modifierWithKey(this._modifiersWithKeys, RowsGapModifier.identity, RowsGapModifier, value);
    return this;
  }
  layoutDirection(value: FlexDirection): this {
    modifierWithKey(this._modifiersWithKeys, LayoutDirectionModifier.identity, LayoutDirectionModifier, value);
    return this;
  }
  nestedScroll(value: NestedScrollOptions): this {
    let options = new ArkNestedScrollOptions();
    if (value) {
      if (value.scrollForward) {
        options.scrollForward = value.scrollForward;
      }
      if (value.scrollBackward) {
        options.scrollBackward = value.scrollBackward;
      }
      modifierWithKey(this._modifiersWithKeys, NestedScrollModifier.identity, NestedScrollModifier, options);
    }
    return this;
  }
  enableScrollInteraction(value: boolean): this {
    modifierWithKey(
      this._modifiersWithKeys, EnableScrollInteractionModifier.identity, EnableScrollInteractionModifier, value);
    return this;
  }
  friction(value: number | Resource): this {
    modifierWithKey(this._modifiersWithKeys, FrictionModifier.identity, FrictionModifier, value);
    return this;
  }
  cachedCount(count: number, show?: boolean): WaterFlowAttribute {
    let opt = new ArkScrollableCacheOptions(count, show ? show : false);
    modifierWithKey(this._modifiersWithKeys, WaterFlowCachedCountModifier.identity, WaterFlowCachedCountModifier, opt);
    return this;
  }
  onReachStart(event: () => void): this {
    throw new Error('Method not implemented.');
  }
  onReachEnd(event: () => void): this {
    throw new Error('Method not implemented.');
  }
  onScrollFrameBegin(event: (offset: number, state: ScrollState) => { offsetRemain: number; }): this {
    throw new Error('Method not implemented.');
  }
  clip(value: boolean | CircleAttribute | EllipseAttribute | PathAttribute | RectAttribute): this {
    modifierWithKey(this._modifiersWithKeys, WaterFlowClipModifier.identity, WaterFlowClipModifier, value);
    return this;
  }
  edgeEffect(value: EdgeEffect, options?: EdgeEffectOptions | undefined): this {
    let effect: ArkWaterFlowEdgeEffect = new ArkWaterFlowEdgeEffect();
    effect.value = value;
    effect.options = options;
    modifierWithKey(this._modifiersWithKeys, WaterFlowEdgeEffectModifier.identity, WaterFlowEdgeEffectModifier, effect);
    return this;
  }
  fadingEdge(value: boolean, options?: FadingEdgeOptions | undefined): this {
    let fadingEdge: ArkFadingEdge = new ArkFadingEdge();
    fadingEdge.value = value;
    fadingEdge.options = options;
    modifierWithKey(this._modifiersWithKeys, WaterFlowFadingEdgeModifier.identity, WaterFlowFadingEdgeModifier, fadingEdge);
    return this;
  }
  scrollBarWidth(value: string | number): this {
    modifierWithKey(this._modifiersWithKeys, WaterFlowScrollBarWidthModifier.identity, WaterFlowScrollBarWidthModifier, value);
    return this;
  }
  scrollBarColor(value: string | number | Color): this {
    modifierWithKey(this._modifiersWithKeys, WaterFlowScrollBarColorModifier.identity, WaterFlowScrollBarColorModifier, value);
    return this;
  }
  scrollBar(value: BarState): this {
    modifierWithKey(this._modifiersWithKeys, WaterFlowScrollBarModifier.identity, WaterFlowScrollBarModifier, value);
    return this;
  }
  flingSpeedLimit(value: number): this {
    modifierWithKey(this._modifiersWithKeys, WaterFlowFlingSpeedLimitModifier.identity, WaterFlowFlingSpeedLimitModifier, value);
    return this;
  }
  initialize(value: Object[]): this {
    if (value[0] !== undefined) {
      modifierWithKey(this._modifiersWithKeys, WaterFlowInitializeModifier.identity,
        WaterFlowInitializeModifier, (value[0] as WaterFlowParam));
    } else {
      modifierWithKey(this._modifiersWithKeys, WaterFlowInitializeModifier.identity,
        WaterFlowInitializeModifier, undefined);
    }
    return this;
  }
  allowChildTypes(): string[] {
    return ['FlowItem'];
  }
}

// @ts-ignore
globalThis.WaterFlow.attributeModifier = function (modifier: ArkComponent): void {
  attributeModifierFunc.call(this, modifier, (nativePtr: KNode) => {
    return new ArkWaterFlowComponent(nativePtr);
  }, (nativePtr: KNode, classType: ModifierType, modifierJS: ModifierJS) => {
    return new modifierJS.WaterFlowModifier(nativePtr, classType);
  });
};
