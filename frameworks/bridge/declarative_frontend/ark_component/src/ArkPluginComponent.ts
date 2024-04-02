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
class ArkPluginComponent extends ArkComponent implements PluginComponentAttribute {
  constructor(nativePtr: KNode, classType?: ModifierType) {
    super(nativePtr, classType);
  }
  onComplete(callback: () => void): this {
    throw new Error('Method not implemented.');
  }
  onError(callback: (info: { errcode: number; msg: string; }) => void): this {
    throw new Error('Method not implemented.');
  }
  size(value: SizeOptions): this {
    modifierWithKey(this._modifiersWithKeys, PluginSizeModifier.identity, PluginSizeModifier, value);
    return this;
  }
  width(value: Length): this {
    modifierWithKey(this._modifiersWithKeys, PluginWidthModifier.identity, PluginWidthModifier, value);
    return this;
  }

  height(value: Length): this {
    modifierWithKey(this._modifiersWithKeys, PluginHeightModifier.identity, PluginHeightModifier, value);
    return this;
  }
}

class PluginWidthModifier extends ModifierWithKey<Length> {
  constructor(value: Length) {
    super(value);
  }
  static identity: Symbol = Symbol('pluginWidth');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().plugin.resetWidth(node);
    } else {
      getUINativeModule().plugin.setWidth(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    if (isResource(this.stageValue) && isResource(this.value)) {
      return !isResourceEqual(this.stageValue, this.value);
    } else {
      return true;
    }
  }
}

class PluginHeightModifier extends ModifierWithKey<Length> {
  constructor(value: Length) {
    super(value);
  }
  static identity: Symbol = Symbol('pluginHeight');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().plugin.resetHeight(node);
    } else {
      getUINativeModule().plugin.setHeight(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    if (isResource(this.stageValue) && isResource(this.value)) {
      return !isResourceEqual(this.stageValue, this.value);
    } else {
      return true;
    }
  }
}

class PluginSizeModifier extends ModifierWithKey<SizeOptions> {
  constructor(value: SizeOptions) {
    super(value);
  }
  static identity: Symbol = Symbol('size');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().plugin.resetSize(node);
    } else {
      getUINativeModule().plugin.setSize(node, this.value.width, this.value.height);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue.width, this.value.width) ||
      !isBaseOrResourceEqual(this.stageValue.height, this.value.height);
  }
}

// @ts-ignore
globalThis.PluginComponent.attributeModifier = function (modifier: ArkComponent): void {
  attributeModifierFunc.call(this, modifier, (nativePtr: KNode) => {
    return new ArkPluginComponent(nativePtr);
  }, (nativePtr: KNode, classType: ModifierType, modifierJS: ModifierJS) => {
    return new modifierJS.PluginComponentModifier(nativePtr, classType);
  });
};
