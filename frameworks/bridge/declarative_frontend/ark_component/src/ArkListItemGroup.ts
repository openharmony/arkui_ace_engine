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
class ListItemGroupInitializeModifier extends ModifierWithKey<ListItemGroupParam> {
  constructor(value: ListItemGroupParam) {
    super(value);
  }
  static identity: Symbol = Symbol('listItemGroupinitialize');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().listItemGroup.resetListItemGroupInitialize(node);
    } else {
      getUINativeModule().listItemGroup.setListItemGroupInitialize(node, this.value?.space, this.value?.style);
    }
  }
}
class ListItemGroupDividerModifier extends ModifierWithKey<DividerStyle> {
  constructor(value: DividerStyle) {
    super(value);
  }
  static identity: Symbol = Symbol('listItemGroupDivider');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().listItemGroup.resetDivider(node);
    } else {
      getUINativeModule().listItemGroup.setDivider(node, this.value?.strokeWidth!, this.value?.color, this.value?.startMargin, this.value?.endMargin);
    }
  }

  checkObjectDiff(): boolean {
    return !(this.stageValue?.strokeWidth === this.value?.strokeWidth &&
      this.stageValue?.color === this.value?.color &&
      this.stageValue?.startMargin === this.value?.startMargin &&
      this.stageValue?.endMargin === this.value?.endMargin);
  }
}

class ListItemGroupChildrenMainSizeModifier extends ModifierWithKey<ChildrenMainSize> {
  constructor(value: ChildrenMainSize) {
    super(value);
  }
  static identity: Symbol = Symbol('listItemGroupChildrenMainSize');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().listItemGroup.resetListItemGroupChildrenMainSize(node);
    } else {
      getUINativeModule().listItemGroup.setListItemGroupChildrenMainSize(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return true;
  }
}

interface ListItemGroupParam {
  space: string | number;
  style: ListItemGroupStyle;
}

class ArkListItemGroupComponent extends ArkComponent implements ListItemGroupAttribute {
  constructor(nativePtr: KNode, classType?: ModifierType) {
    super(nativePtr, classType);
  }
  divider(value: { strokeWidth: any; color?: any; startMargin?: any; endMargin?: any; } | null): this {
    modifierWithKey(this._modifiersWithKeys, ListItemGroupDividerModifier.identity, ListItemGroupDividerModifier, value);
    return this;
  }
  childrenMainSize(value: ChildrenMainSize): this {
    modifierWithKey(this._modifiersWithKeys, ListItemGroupChildrenMainSizeModifier.identity, ListItemGroupChildrenMainSizeModifier, value);
    return this;
  }
  initialize(value: Object[]): this {
    if (value[0] !== undefined) {
      modifierWithKey(this._modifiersWithKeys, ListItemGroupInitializeModifier.identity,
        ListItemGroupInitializeModifier, value[0] as ListItemGroupParam);
    } else {
      modifierWithKey(this._modifiersWithKeys, ListItemGroupInitializeModifier.identity,
        ListItemGroupInitializeModifier, undefined);
    }
    return this;
  }
  allowChildTypes(): string[] {
    return ['ListItem'];
  }
}

// @ts-ignore
globalThis.ListItemGroup.attributeModifier = function (modifier: ArkComponent): void {
  attributeModifierFunc.call(this, modifier, (nativePtr: KNode) => {
    return new ArkListItemGroupComponent(nativePtr);
  }, (nativePtr: KNode, classType: ModifierType, modifierJS: ModifierJS) => {
    return new modifierJS.ListItemGroupModifier(nativePtr, classType);
  });
};
