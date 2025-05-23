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
class GridItemSelectableModifier extends ModifierWithKey<boolean> {
  static identity: Symbol = Symbol('gridItemSelectable');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().gridItem.resetGridItemSelectable(node);
    } else {
      getUINativeModule().gridItem.setGridItemSelectable(node, this.value!);
    }
  }
}

class GridItemSelectedModifier extends ModifierWithKey<boolean> {
  static identity: Symbol = Symbol('gridItemSelected');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().gridItem.resetGridItemSelected(node);
    } else {
      getUINativeModule().gridItem.setGridItemSelected(node, this.value!);
    }
  }
}

class GridItemRowStartModifier extends ModifierWithKey<number> {
  static identity: Symbol = Symbol('gridItemRowStart');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().gridItem.resetGridItemRowStart(node);
    } else {
      getUINativeModule().gridItem.setGridItemRowStart(node, this.value!);
    }
  }
}

class GridItemRowEndModifier extends ModifierWithKey<number> {
  static identity: Symbol = Symbol('gridItemRowEnd');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().gridItem.resetGridItemRowEnd(node);
    } else {
      getUINativeModule().gridItem.setGridItemRowEnd(node, this.value!);
    }
  }
}

class GridItemColumnStartModifier extends ModifierWithKey<number> {
  static identity: Symbol = Symbol('gridItemColumnStart');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().gridItem.resetGridItemColumnStart(node);
    } else {
      getUINativeModule().gridItem.setGridItemColumnStart(node, this.value!);
    }
  }
}

class GridItemColumnEndModifier extends ModifierWithKey<number> {
  static identity: Symbol = Symbol('gridItemColumnEnd');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().gridItem.resetGridItemColumnEnd(node);
    } else {
      getUINativeModule().gridItem.setGridItemColumnEnd(node, this.value!);
    }
  }
}

class GridItemOptionsModifier extends ModifierWithKey<GridItemOptions> {
  static identity: Symbol = Symbol('gridItemOptions');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().gridItem.setGridItemOptions(node, undefined);
    } else {
      if (this.value?.style === undefined) {
        getUINativeModule().gridItem.setGridItemOptions(node, undefined);
      } else {
        getUINativeModule().gridItem.setGridItemOptions(node, this.value.style);
      }
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue?.style, this.value?.style);
  }
}

class GridItemOnSelectedModifier extends ModifierWithKey<(isSelected: boolean) => void> {
  constructor(value: (isSelected: boolean) => void) {
    super(value);
  }
  static identity: Symbol = Symbol('gridItemOnSelected');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().gridItem.resetGridItemOnSelected(node);
    } else {
      getUINativeModule().gridItem.setGridItemOnSelected(node, this.value!);
    }
  }
}

class ArkGridItemComponent extends ArkComponent implements GridItemAttribute {
  constructor(nativePtr: KNode, classType?: ModifierType) {
    super(nativePtr, classType);
  }
  allowChildCount(): number {
    return 1;
  }
  initialize(value: Object[]): this {
    if (value.length === 1 && isObject(value[0])) {
      modifierWithKey(this._modifiersWithKeys, GridItemOptionsModifier.identity, GridItemOptionsModifier, value[0]);
    }
    return this;
  }
  rowStart(value: number): this {
    modifierWithKey(this._modifiersWithKeys, GridItemRowStartModifier.identity, GridItemRowStartModifier, value);
    return this;
  }
  rowEnd(value: number): this {
    modifierWithKey(this._modifiersWithKeys, GridItemRowEndModifier.identity, GridItemRowEndModifier, value);
    return this;
  }
  columnStart(value: number): this {
    modifierWithKey(this._modifiersWithKeys, GridItemColumnStartModifier.identity, GridItemColumnStartModifier, value);
    return this;
  }
  columnEnd(value: number): this {
    modifierWithKey(this._modifiersWithKeys, GridItemColumnEndModifier.identity, GridItemColumnEndModifier, value);
    return this;
  }
  forceRebuild(value: boolean): this {
    throw new Error('Method not implemented.');
  }
  selectable(value: boolean): this {
    modifierWithKey(this._modifiersWithKeys, GridItemSelectableModifier.identity, GridItemSelectableModifier, value);
    return this;
  }
  selected(value: boolean): this {
    modifierWithKey(this._modifiersWithKeys, GridItemSelectedModifier.identity, GridItemSelectedModifier, value);
    return this;
  }
  onSelect(event: (isSelected: boolean) => void): this {
    modifierWithKey(this._modifiersWithKeys, GridItemOnSelectedModifier.identity, GridItemOnSelectedModifier, event);
    return this;
  }
}

// @ts-ignore
globalThis.GridItem.attributeModifier = function (modifier: ArkComponent): void {
  attributeModifierFunc.call(this, modifier, (nativePtr: KNode) => {
    return new ArkGridItemComponent(nativePtr);
  }, (nativePtr: KNode, classType: ModifierType, modifierJS: ModifierJS) => {
    return new modifierJS.GridItemModifier(nativePtr, classType);
  });
};

globalThis.GridItem.onSelect = function (value: (isSelected: boolean) => void): void {
  let nodePtr = getUINativeModule().frameNode.getStackTopNode();
  getUINativeModule().gridItem.setGridItemOnSelected(nodePtr, value);
};
