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


interface StackParam {
  alignContent: Alignment
}

class ArkStackComponent extends ArkComponent {
  constructor(nativePtr: KNode, classType?: ModifierType) {
    super(nativePtr, classType);
  }
  initialize(value: Object[]): this {
    if (value[0] !== undefined) {
      this.alignContent((value[0] as StackParam).alignContent);
    }
    return this
  }
  alignContent(value: Alignment): this {
    modifierWithKey(this._modifiersWithKeys, StackAlignContentModifier.identity, StackAlignContentModifier, value);
    return this;
  }
  align(value: Alignment): this {
    modifierWithKey(this._modifiersWithKeys, StackAlignContentModifier.identity, StackAlignContentModifier, value);
    return this;
  }
  pointLight(value: PointLightStyle): this {
    modifierWithKey(this._modifiersWithKeys, StackPointLightModifier.identity, StackPointLightModifier, value);
    return this;
  }
  syncLoad(value: boolean): this {
    modifierWithKey(this._modifiersWithKeys, StackSyncLoadModifier.identity, StackSyncLoadModifier, value);
    return this;
  }
}

class StackPointLightModifier extends ModifierWithKey<PointLightStyle> {
  constructor(value: PointLightStyle) {
    super(value);
  }
  static identity: Symbol = Symbol('stackPointLight');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetPointLightStyle(node);
    } else {
      let positionX: Dimension | undefined;
      let positionY: Dimension | undefined;
      let positionZ: Dimension | undefined;
      let intensity: number | undefined;
      let color: ResourceColor | undefined;
      let illuminated: number | undefined;
      let bloom: number | undefined;
      if (!isUndefined(this.value.lightSource) && this.value.lightSource != null) {
        positionX = this.value.lightSource.positionX;
        positionY = this.value.lightSource.positionY;
        positionZ = this.value.lightSource.positionZ;
        intensity = this.value.lightSource.intensity;
        color = this.value.lightSource.color;
      }
      illuminated = this.value.illuminated;
      bloom = this.value.bloom;
      getUINativeModule().common.setPointLightStyle(node, positionX, positionY, positionZ, intensity, color,
        illuminated, bloom);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue.lightSource?.positionX, this.value.lightSource?.positionX) ||
    !isBaseOrResourceEqual(this.stageValue.lightSource?.positionY, this.value.lightSource?.positionY) ||
    !isBaseOrResourceEqual(this.stageValue.lightSource?.positionZ, this.value.lightSource?.positionZ) ||
    !isBaseOrResourceEqual(this.stageValue.lightSource?.intensity, this.value.lightSource?.intensity) ||
    !isBaseOrResourceEqual(this.stageValue.lightSource?.color, this.value.lightSource?.color) ||
    !isBaseOrResourceEqual(this.stageValue.illuminated, this.value.illuminated) ||
    !isBaseOrResourceEqual(this.stageValue.bloom, this.value.bloom);
  }
}

class StackAlignContentModifier extends ModifierWithKey<number> {
  constructor(nativePtr: number) {
    super(nativePtr);
  }
  static identity: Symbol = Symbol('stackAlignContent');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().stack.resetAlignContent(node);
    } else {
      getUINativeModule().stack.setAlignContent(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return this.stageValue !== this.value;
  }
}

class StackSyncLoadModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('stackSyncLoad');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().stack.resetSyncLoad(node);
    } else {
      getUINativeModule().stack.setSyncLoad(node, this.value);
    }
  }
}

// @ts-ignore
if (globalThis.Stack !== undefined) {
  (globalThis as any).Stack.attributeModifier = function (modifier) {
    attributeModifierFunc.call(this, modifier, (nativePtr) => {
      return new ArkStackComponent(nativePtr);
    }, (nativePtr, classType, modifierJS) => {
      return new modifierJS.StackModifier(nativePtr, classType);
    });
  };
}
