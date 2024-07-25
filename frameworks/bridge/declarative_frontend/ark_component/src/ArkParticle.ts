/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
class ArkParticleComponent extends ArkComponent implements ParticleAttribute {
  constructor(nativePtr: KNode, classType?: ModifierType) {
    super(nativePtr, classType);
  }
  disturbanceFields(value: Array<DisturbanceFieldOptions>): this {
    modifierWithKey(this._modifiersWithKeys, ParticleModifier.identity, ParticleModifier, value);
    return this;
  }

  emitter(value: Array<EmitterProperty>): this {
    modifierWithKey(this._modifiersWithKeys, ParticleEmitterModifier.identity, ParticleEmitterModifier, value);
    return this;
  }
}

class ParticleModifier extends ModifierWithKey<Array<DisturbanceFieldOptions>> {
  constructor(value: Array<DisturbanceFieldOptions>) {
    super(value);
  }
  static identity: Symbol = Symbol('disturbanceFields');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().particle.resetDisturbanceField(node);
    } else {
      let dataArray = [];
      if (Array.isArray(this.value)) {
        return;
      }
      for (let i = 0; i < this.value.length; i++) {
        let data = this.value[i];
        dataArray.push(parseWithDefaultNumber(data.strength, 0));
        dataArray.push(parseWithDefaultNumber(data.shape, 0));
        if (isObject(data.size)) {
          dataArray.push(parseWithDefaultNumber(data.size.width, 0));
          dataArray.push(parseWithDefaultNumber(data.size.height, 0));
        }
        else {
          dataArray.push(0);
          dataArray.push(0);
        }
        if (isObject(data.position)) {
          dataArray.push(parseWithDefaultNumber(data.position.x, 0));
          dataArray.push(parseWithDefaultNumber(data.position.y, 0));
        }
        else {
          dataArray.push(0);
          dataArray.push(0);
        }
        dataArray.push(parseWithDefaultNumber(data.feather, 0));
        dataArray.push(parseWithDefaultNumber(data.noiseScale, 1));
        dataArray.push(parseWithDefaultNumber(data.noiseFrequency, 1));
        dataArray.push(parseWithDefaultNumber(data.noiseAmplitude, 1));
      }
      getUINativeModule().particle.setDisturbanceField(node, dataArray);
    }
  }

  checkObjectDiff(): boolean {
    if (isString(this.stageValue) && isString(this.value)) {
      return this.stageValue !== this.value;
    } else {
      return true;
    }
  }
}

class ParticleEmitterModifier extends ModifierWithKey<Array<EmitterProperty>> {
  constructor(value: Array<EmitterProperty>) {
    super(value);
  }

  static identity: Symbol = Symbol('emitter');
  applyPeer(node, reset): void {
    let emitRatePlaceHolder;
    let positionXPlaceHolder;
    let positionYPlaceHolder;
    let sizeXPlaceHolder;
    let sizeYPlaceHolder;
    if (reset) {
      getUINativeModule().particle.resetEmitter(node);
    }
    else {
      let dataArray = [];
      if (!Array.isArray(this.value)) {
        return;
      }
      for (let i = 0; i < this.value.length; i++) {
        let data = this.value[i];
        let indexValue = 0;
        if (data.index > 0) {
          indexValue = data.index;
        }
        dataArray.push(indexValue);

        let emitRateValue = 5;
        if (isNumber(data.emitRate)) {
          dataArray.push(1);
          if (data.emitRate >= 0) {
            emitRateValue = data.emitRate;
          }
          dataArray.push(emitRateValue);
        } else {
          dataArray.push(0);
          dataArray.push(emitRatePlaceHolder);
        }

        if (isObject(data.position)) {
          if (isNumber(data.position.x) && isNumber(data.position.y)) {
            dataArray.push(1);
            dataArray.push(data.position.x);
            dataArray.push(data.position.y);
          } else {
            dataArray.push(0);
            dataArray.push(positionXPlaceHolder);
            dataArray.push(positionYPlaceHolder);
          }
        } else {
          dataArray.push(0);
          dataArray.push(positionXPlaceHolder);
          dataArray.push(positionYPlaceHolder);
        }

        if (isObject(data.size)) {
          if (data.size.width > 0 && data.size.height > 0) {
            dataArray.push(1);
            dataArray.push(data.size.width);
            dataArray.push(data.size.height);
          } else {
            dataArray.push(0);
            dataArray.push(sizeXPlaceHolder);
            dataArray.push(sizeYPlaceHolder);
          }
        }
        else {
          dataArray.push(0);
          dataArray.push(sizeXPlaceHolder);
          dataArray.push(sizeYPlaceHolder);
        }
      }
      getUINativeModule().particle.setEmitter(node, dataArray);
    }
  }

  checkObjectDiff(): boolean {
    if (isString(this.stageValue) && isString(this.value)) {
      return this.stageValue !== this.value;
    } else {
      return true;
    }
  }
}

// @ts-ignore
globalThis.Particle.attributeModifier = function (modifier: ArkComponent): void {
  attributeModifierFunc.call(this, modifier, (nativePtr: KNode) => {
    return new ArkParticleComponent(nativePtr);
  }, (nativePtr: KNode, classType: ModifierType, modifierJS: ModifierJS) => {
    return new modifierJS.PathModifier(nativePtr, classType);
  });
};
