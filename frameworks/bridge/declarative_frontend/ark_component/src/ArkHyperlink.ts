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

class ArkHyperlinkComponent extends ArkComponent implements HyperlinkAttribute {
  constructor(nativePtr: KNode, classType?: ModifierType) {
    super(nativePtr, classType);
  }
  color(value: ResourceColor): this {
    modifierWithKey(this._modifiersWithKeys, HyperlinkColorModifier.identity, HyperlinkColorModifier, value);
    return this;
  }
  draggable(value: boolean): this {
    modifierWithKey(this._modifiersWithKeys, HyperlinkDraggableModifier.identity, HyperlinkDraggableModifier, value);
    return this;
  }
}

class HyperlinkColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity: Symbol = Symbol('hyperlinkColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().hyperlink.resetColor(node);
    } else {
      getUINativeModule().hyperlink.setColor(node, this.value!);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class HyperlinkDraggableModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('hyperlinkDraggable');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().hyperlink.resetDraggable(node);
    } else {
      getUINativeModule().hyperlink.setDraggable(node, this.value);
    }
  }
}

// @ts-ignore
globalThis.Hyperlink.attributeModifier = function (modifier: ArkComponent): void {
  attributeModifierFunc.call(this, modifier, (nativePtr: KNode) => {
    return new ArkHyperlinkComponent(nativePtr);
  }, (nativePtr: KNode, classType: ModifierType, modifierJS: ModifierJS) => {
    return new modifierJS.HyperlinkModifier(nativePtr, classType);
  });
};
