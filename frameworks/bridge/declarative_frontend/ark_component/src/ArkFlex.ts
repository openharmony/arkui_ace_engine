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

class FlexInitializeModifier extends ModifierWithKey<FlexParam> {
  constructor(value: FlexParam) {
    super(value);
  }
  static identity: Symbol = Symbol('flexInitialize');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().flex.resetFlexInitialize(node);
    } else {
      getUINativeModule().flex.setFlexInitialize(node, this.value.direction, this.value.wrap,
        this.value.justifyContent, this.value.alignItems, this.value.alignContent, this.value?.space?.main,
        this.value?.space?.cross);
    }
  }
}
interface FlexParam {
  direction?: FlexDirection;
  wrap?: FlexWrap;
  justifyContent?: FlexAlign;
  alignItems?: ItemAlign;
  alignContent?: FlexAlign;
  space?: FlexSpaceOptions;
}

class FlexPointLightModifier extends ModifierWithKey<PointLightStyle> {
  constructor(value: PointLightStyle) {
    super(value);
  }
  static identity: Symbol = Symbol('flexPointLight');
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

class ArkFlexComponent extends ArkComponent {
  constructor(nativePtr: KNode, classType?: ModifierType) {
    super(nativePtr, classType);
  }
  pointLight(value: PointLightStyle): this {
    modifierWithKey(this._modifiersWithKeys, FlexPointLightModifier.identity, FlexPointLightModifier, value);
    return this;
  }
  initialize(value: Object[]): this {
    if (value[0] !== undefined) {
      modifierWithKey(this._modifiersWithKeys, FlexInitializeModifier.identity,
        FlexInitializeModifier, (value[0] as FlexParam));
    }
    return this;
  }
}

// @ts-ignore
if (globalThis.Flex !== undefined) {
  (globalThis as any).Flex.attributeModifier = function (modifier) {
    attributeModifierFunc.call(this, modifier, (nativePtr) => {
      return new ArkFlexComponent(nativePtr);
    }, (nativePtr, classType, modifierJS) => {
      return new modifierJS.FlexModifier(nativePtr, classType);
    });
  };
}
