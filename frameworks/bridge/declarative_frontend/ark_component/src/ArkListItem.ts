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
class ListItemSelectedModifier extends ModifierWithKey<boolean> {
  static identity: Symbol = Symbol('listItemSelected');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().listItem.resetListItemSelected(node);
    } else {
      getUINativeModule().listItem.setListItemSelected(node, this.value!);
    }
  }
}

class ListItemSelectableModifier extends ModifierWithKey<boolean> {
  static identity: Symbol = Symbol('listItemSelectable');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().listItem.resetSelectable(node);
    } else {
      getUINativeModule().listItem.setSelectable(node, this.value!);
    }
  }
}

class ListItemSwipeActionModifier extends ModifierWithKey<SwipeActionOptions> {
  constructor(value: SwipeActionOptions) {
    super(value);
  }
  static identity: Symbol = Symbol('listItemSwipeAction');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().listItem.resetSwipeAction(node);
    } else {
      getUINativeModule().listItem.setSwipeAction(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return true;
  }
}

class ArkListItemComponent extends ArkComponent implements ListItemAttribute {
  constructor(nativePtr: KNode, classType?: ModifierType) {
    super(nativePtr, classType);
  }
  initialize(value: Object[]): this {
    return this;
  }
  sticky(value: Sticky): this {
    throw new Error('Method not implemented.');
  }
  editable(value: boolean | EditMode): this {
    throw new Error('Method not implemented.');
  }
  selectable(value: boolean): this {
    modifierWithKey(this._modifiersWithKeys, ListItemSelectableModifier.identity, ListItemSelectableModifier, value);
    return this;
  }
  selected(value: boolean): this {
    modifierWithKey(this._modifiersWithKeys, ListItemSelectedModifier.identity, ListItemSelectedModifier, value);
    return this;
  }
  swipeAction(value: SwipeActionOptions): this {
    modifierWithKey(this._modifiersWithKeys, ListItemSwipeActionModifier.identity, ListItemSwipeActionModifier, value);
    return this;
  }
  onSelect(event: (isSelected: boolean) => void): this {
    throw new Error('Method not implemented.');
  }
}

// @ts-ignore
globalThis.ListItem.attributeModifier = function (modifier: ArkComponent): void {
  attributeModifierFunc.call(this, modifier, (nativePtr: KNode) => {
    return new ArkListItemComponent(nativePtr);
  }, (nativePtr: KNode, classType: ModifierType, modifierJS: ModifierJS) => {
    return new modifierJS.ListItemModifier(nativePtr, classType);
  });
};
