/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

declare type OnTerminatedCallback = (event: TerminationInfo) => void;
class EmbeddedComponentOnTerminatedModifier extends ModifierWithKey<OnTerminatedCallback> {
  constructor(value: OnTerminatedCallback) {
    super(value);
  }
  static identity: Symbol = Symbol('onTerminated');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().embeddedComponent.resetOnTerminated(node);
    } else {
      getUINativeModule().embeddedComponent.setOnTerminated(node, this.value);
    }
  }
}

declare type OnErrorCallback = (event: ErrorCallback) => void;
class EmbeddedComponentOnErrorModifier extends ModifierWithKey<OnErrorCallback> {
  constructor(value: OnErrorCallback) {
    super(value);
  }
  static identity: Symbol = Symbol('onError');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().embeddedComponent.resetOnError(node);
    } else {
      getUINativeModule().embeddedComponent.setOnError(node, this.value);
    }
  }
}

class ArkEmbeddedComponent extends ArkComponent implements EmbeddedComponentAttribute {
  constructor(nativePtr: KNode, classType?: ModifierType) {
    super(nativePtr, classType);
  }
  onTerminated(callback: (event: TerminationInfo) => void): this {
    modifierWithKey(this._modifiersWithKeys,
      EmbeddedComponentOnTerminatedModifier.identity, EmbeddedComponentOnTerminatedModifier, callback);
    return this;
  }
  onError(callback: (event: ErrorCallback) => void): this {
    modifierWithKey(this._modifiersWithKeys,
      EmbeddedComponentOnErrorModifier.identity, EmbeddedComponentOnErrorModifier, callback);
    return this;
  }
}

// @ts-ignore
globalThis.EmbeddedComponent.attributeModifier = function (modifier: ArkComponent): void {
  attributeModifierFunc.call(this, modifier, (nativePtr: KNode) => {
    return new ArkEmbeddedComponent(nativePtr);
  }, (nativePtr: KNode, classType: ModifierType, modifierJS: ModifierJS) => {
    return new modifierJS.EmbeddedComponentModifier(nativePtr, classType);
  });
};
