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

class ItemConstraintSizeModifier extends ModifierWithKey<ArkConstraintSizeOptions> {
  constructor(value: ArkConstraintSizeOptions) {
    super(value);
  }
  static identity: Symbol = Symbol('itemConstraintSize');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().waterFlow.resetItemConstraintSize(node);
    } else {
      GetUINativeModule().waterFlow.setItemConstraintSize(node, this.value.minWidth,
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
      GetUINativeModule().waterFlow.resetColumnsTemplate(node);
    } else {
      GetUINativeModule().waterFlow.setColumnsTemplate(node, this.value);
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
      GetUINativeModule().waterFlow.resetRowsTemplate(node);
    } else {
      GetUINativeModule().waterFlow.setRowsTemplate(node, this.value);
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
          GetUINativeModule().waterFlow.resetEnableScrollInteraction(node);
      }
      else {
          GetUINativeModule().waterFlow.setEnableScrollInteraction(node, this.value);
      }
  }
}

class RowsGapModifier extends ModifierWithKey<number | string> {
  constructor(value: number | string) {
    super(value);
  }
  static identity: Symbol = Symbol('rowsGap');
  applyPeer(node: KNode, reset: boolean): void {
      if (reset) {
          GetUINativeModule().waterFlow.resetRowsGap(node);
      }
      else {
          GetUINativeModule().waterFlow.setRowsGap(node, this.value);
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
          GetUINativeModule().waterFlow.resetColumnsGap(node);
      }
      else {
          GetUINativeModule().waterFlow.setColumnsGap(node, this.value);
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
      GetUINativeModule().waterFlow.resetLayoutDirection(node);
    }
    else {
      GetUINativeModule().waterFlow.setLayoutDirection(node, this.value);
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
      GetUINativeModule().waterFlow.resetNestedScroll(node);
    }
    else {
      GetUINativeModule().waterFlow.setNestedScroll(node, this.value.scrollForward, this.value.scrollBackward);
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
      GetUINativeModule().waterFlow.resetFriction(node);
    }
    else {
      GetUINativeModule().waterFlow.setFriction(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class ArkWaterFlowComponent extends ArkComponent implements WaterFlowAttribute {
  constructor(nativePtr: KNode) {
    super(nativePtr);
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
  cachedCount(value: number): this {
    throw new Error('Method not implemented.');
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
  monopolizeEvents(monopolize: boolean): this {
    throw new Error('Method not implemented.');
  }
}

// @ts-ignore
globalThis.WaterFlow.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkWaterFlowComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
}
