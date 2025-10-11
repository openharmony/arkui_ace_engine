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

  rippleFields(value: Array<RippleFieldOptions>): this {
    modifierWithKey(this._modifiersWithKeys, ParticleRippleModifier.identity, ParticleRippleModifier, value);
    return this;
  }

  velocityFields(value: Array<VelocityFieldOptions>): this {
    modifierWithKey(this._modifiersWithKeys, ParticleVelocityModifier.identity, ParticleVelocityModifier, value);
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

class ArkRippleFieldOptions {
  isSetAmplitude: number;
  amplitude: number | undefined;
  isSetWaveLength: number;
  wavelength: number | undefined;
  isSetWaveSpeed: number;
  waveSpeed: number | undefined;
  isSetAttenuation: number;
  attenuation: number | undefined;
  isSetCenter: number;
  centerX: number | undefined;
  centerY: number | undefined;
  isSetRegion: number;
  isSetShape: number;
  shape: number | undefined;
  isSetPosition: number;
  positionX: number | undefined;
  positionY: number | undefined;
  isSetSize: number;
  sizeWidth: number | undefined;
  sizeHeight: number | undefined;

  constructor() {
    this.isSetAmplitude = 0;
    this.amplitude = undefined;
    this.isSetWaveLength = 0;
    this.wavelength = undefined;
    this.isSetWaveSpeed = 0;
    this.waveSpeed = undefined;
    this.isSetAttenuation = 0;
    this.attenuation = undefined;
    this.isSetCenter = 0;
    this.centerX = undefined;
    this.centerY = undefined;
    this.isSetRegion = 0;
    this.isSetShape = 0;
    this.shape = undefined;
    this.isSetPosition = 0;
    this.positionX = undefined;
    this.positionY = undefined;
    this.isSetSize = 0;
    this.sizeWidth = undefined;
    this.sizeHeight = undefined;
  }
}

class ParticleRippleModifier extends ModifierWithKey<Array<RippleFieldOptions>> {
  constructor(value: Array<RippleFieldOptions>) {
    super(value);
  }
  static identity: Symbol = Symbol('rippleFields');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().particle.resetRippleField(node);
    } else {
      let dataArray = [];
      if (!Array.isArray(this.value)) {
        return;
      }
      for (let i = 0; i < this.value.length; i++) {
        let arkRippleFieldOptions = new ArkRippleFieldOptions();
        let data = this.value[i];
        if (!data) {
          continue;
        }
        if (isNumber(data.amplitude)) {
          arkRippleFieldOptions.isSetAmplitude = 1;
          arkRippleFieldOptions.amplitude = data.amplitude;
        }
        if (isNumber(data.wavelength)) {
          arkRippleFieldOptions.isSetWaveLength = 1;
          arkRippleFieldOptions.wavelength = data.wavelength;
        }
        if (isNumber(data.waveSpeed)) {
          arkRippleFieldOptions.isSetWaveSpeed = 1;
          arkRippleFieldOptions.waveSpeed = data.waveSpeed;
        }
        if (isNumber(data.attenuation)) {
          arkRippleFieldOptions.isSetAttenuation = 1;
          arkRippleFieldOptions.attenuation = data.attenuation;
        }
        if (isObject(data.center)) {
          arkRippleFieldOptions.isSetCenter = 1;
          arkRippleFieldOptions.centerX = data.center.x;
          arkRippleFieldOptions.centerY = data.center.y;
        }
        if (isObject(data.region)) {
          arkRippleFieldOptions.isSetRegion = 1;
          if (isNumber(data.region.shape)) {
            arkRippleFieldOptions.isSetShape = 1;
            arkRippleFieldOptions.shape = data.region.shape;
          }

          if (isObject(data.region.position)) {
            arkRippleFieldOptions.isSetPosition = 1;
            arkRippleFieldOptions.positionX = data.region.position.x;
            arkRippleFieldOptions.positionY = data.region.position.y;
          }

          if (isObject(data.region.size)) {
            arkRippleFieldOptions.isSetSize = 1;
            arkRippleFieldOptions.sizeWidth = data.region.size.width;
            arkRippleFieldOptions.sizeHeight = data.region.size.height;
          }
        }
        dataArray.push(arkRippleFieldOptions);
      }
      getUINativeModule().particle.setRippleField(node, dataArray);
    }
  }

  checkObjectDiff(): boolean {
    return this.stageValue !== this.value;
  }
}

class ArkVelocityFieldOptions {
  isSetVelocity: number;
  velocityX: number | undefined;
  velocityY: number | undefined;
  isSetRegion: number;
  isSetShape: number;
  shape: number | undefined;
  isSetPosition: number;
  positionX: number | undefined;
  positionY: number | undefined;
  isSetSize: number;
  sizeWidth: number | undefined;
  sizeHeight: number | undefined;

  constructor() {
    this.isSetVelocity = 0;
    this.velocityX = undefined;
    this.velocityY = undefined;
    this.isSetRegion = 0;
    this.isSetShape = 0;
    this.shape = undefined;
    this.isSetPosition = 0;
    this.positionX = undefined;
    this.positionY = undefined;
    this.isSetSize = 0;
    this.sizeWidth = undefined;
    this.sizeHeight = undefined;
  }
}

class ParticleVelocityModifier extends ModifierWithKey<Array<VelocityFieldOptions>> {
  constructor(value: Array<VelocityFieldOptions>) {
    super(value);
  }
  static identity: Symbol = Symbol('velocityFields');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().particle.resetVelocityField(node);
    } else {
      let dataArray = [];
      if (!Array.isArray(this.value)) {
        return;
      }
      for (let i = 0; i < this.value.length; i++) {
        let arkVelocityFieldOptions = new ArkVelocityFieldOptions();
        let data = this.value[i];
        if (!data) {
          continue;
        }
        if (isObject(data.velocity)) {
          arkVelocityFieldOptions.isSetVelocity = 1;
          arkVelocityFieldOptions.velocityX = data.velocity.x;
          arkVelocityFieldOptions.velocityY = data.velocity.y;
        }
        if (isObject(data.region)) {
          arkVelocityFieldOptions.isSetRegion = 1;
          if (isNumber(data.region.shape)) {
            arkVelocityFieldOptions.isSetShape = 1;
            arkVelocityFieldOptions.shape = data.region.shape;
          }

          if (isObject(data.region.position)) {
            arkVelocityFieldOptions.arkVelocityFieldOptions = 1;
            arkVelocityFieldOptions.positionX = data.region.position.x;
            arkVelocityFieldOptions.positionY = data.region.position.y;
          }

          if (isObject(data.region.size)) {
            arkVelocityFieldOptions.isSetSize = 1;
            arkVelocityFieldOptions.sizeWidth = data.region.size.width;
            arkVelocityFieldOptions.sizeHeight = data.region.size.height;
          }
        }
        dataArray.push(arkVelocityFieldOptions);
      }
      getUINativeModule().particle.setVelocityField(node, dataArray);
    }
  }

  checkObjectDiff(): boolean {
    return this.stageValue !== this.value;
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
