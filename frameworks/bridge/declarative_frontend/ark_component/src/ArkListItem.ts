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
class ArkListItemComponent extends ArkComponent implements ListItemAttribute {
  constructor(nativePtr: KNode) {
    super(nativePtr);
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
    throw new Error('Method not implemented.');
  }
  onSelect(event: (isSelected: boolean) => void): this {
    throw new Error('Method not implemented.');
  }
  monopolizeEvents(monopolize: boolean): this {
    throw new Error('Method not implemented.');
  }
}

// @ts-ignore
globalThis.ListItem.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkListItemComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};
