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
      GetUINativeModule().gridItem.resetGridItemSelectable(node);
    } else {
      GetUINativeModule().gridItem.setGridItemSelectable(node, this.value!);
    }
  }
}

class GridItemSelectedModifier extends ModifierWithKey<boolean> {
  static identity: Symbol = Symbol('gridItemSelected');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().gridItem.resetGridItemSelected(node);
    } else {
      GetUINativeModule().gridItem.setGridItemSelected(node, this.value!);
    }
  }
}

class GridItemRowStartModifier extends ModifierWithKey<number> {
  static identity: Symbol = Symbol('gridItemRowStart');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().gridItem.resetGridItemRowStart(node);
    } else {
      GetUINativeModule().gridItem.setGridItemRowStart(node, this.value!);
    }
  }
}

class GridItemRowEndModifier extends ModifierWithKey<number> {
  static identity: Symbol = Symbol('gridItemRowEnd');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().gridItem.resetGridItemRowEnd(node);
    } else {
      GetUINativeModule().gridItem.setGridItemRowEnd(node, this.value!);
    }
  }
}

class GridItemColumnStartModifier extends ModifierWithKey<number> {
  static identity: Symbol = Symbol('gridItemColumnStart');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().gridItem.resetGridItemColumnStart(node);
    } else {
      GetUINativeModule().gridItem.setGridItemColumnStart(node, this.value!);
    }
  }
}

class GridItemColumnEndModifier extends ModifierWithKey<number> {
  static identity: Symbol = Symbol('gridItemColumnEnd');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().gridItem.resetGridItemColumnEnd(node);
    } else {
      GetUINativeModule().gridItem.setGridItemColumnEnd(node, this.value!);
    }
  }
}

class ArkGridItemComponent extends ArkComponent implements GridItemAttribute {
  constructor(nativePtr: KNode) {
    super(nativePtr);
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
    throw new Error('Method not implemented.');
  }
  monopolizeEvents(monopolize: boolean): this {
    throw new Error('Method not implemented.');
  }
}

// @ts-ignore
globalThis.GridItem.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkGridItemComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
}
