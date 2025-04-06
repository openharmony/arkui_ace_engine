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
class ImageAnimatorImagesModifier extends ModifierWithKey<Array<ImageFrameInfo>> {
  constructor(value: Array<ImageFrameInfo>) {
    super(value);
  }
  static identity: Symbol = Symbol('imageAnimatorImages');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().imageAnimator.resetImages(node);
    } else {
      let arkImageFrame: ArkImageFrameInfoToArray = this.convertImageFrames(this.value);
      if (!arkImageFrame) {
        getUINativeModule().imageAnimator.resetImages(node);
      } else {
        getUINativeModule().imageAnimator.setImages(node, arkImageFrame.arrSrc,
          arkImageFrame.arrWidth, arkImageFrame.arrHeight, arkImageFrame.arrTop, arkImageFrame.arrLeft,
          arkImageFrame.arrDuration, arkImageFrame.arrSrc.length);
      }
    }
  }

  checkObjectDiff(): boolean {
    let checkDiff = true;
    if (this.value && this.value.length > 0 &&
      this.stageValue && this.stageValue.length > 0 &&
      this.value.length === this.stageValue.length) {
      let checkItemEqual: Boolean = false;

      for (let i: number = 0; i < this.value.length; i++) {
        checkItemEqual = this.isEqual(this.stageValue[i], this.value[i]);
        if (!checkItemEqual) {
          checkDiff = !checkItemEqual;
          break;
        }
      }
    }
    return checkDiff;
  }

  isEqual(one: ImageFrameInfo, another: ImageFrameInfo): boolean {
    if (!(one.width === another.width &&
      one.height === another.height &&
      one.top === another.top &&
      one.left === another.left &&
      one.duration === another.duration)) {
      return true;
    } else {
      return !isBaseOrResourceEqual(one.src, another.src);
    }
  }

  convertImageFrames(value: Array<ImageFrameInfo>): ArkImageFrameInfoToArray {
    if (value && value.length > 0) {
      let isFlag: Boolean = true;
      for (let item of value) {
        if (item.src === undefined || item.src === null) {
          isFlag = false;
          break;
        }
      }
      if (isFlag) {
        let array: ArkImageFrameInfoToArray = new ArkImageFrameInfoToArray();
        for (let item of value) {
          array.arrSrc.push(<string>item.src);
          array.arrWidth.push((item.width === undefined || item.width === null) ? 0 : item.width);
          array.arrHeight.push((item.height === undefined || item.height === null) ? 0 : item.height);
          array.arrTop.push((item.top === undefined || item.top === null) ? 0 : item.top);
          array.arrLeft.push((item.left === undefined || item.left === null) ? 0 : item.left);
          array.arrDuration.push((item.duration === undefined || item.duration === null) ? 0 : item.duration);
        }
        return array;
      } else {
        return undefined;
      }
    } else {
      return undefined;
    }
  }
}

class ImageAnimatorDurationModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('imageAnimatorDuration');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().imageAnimator.resetDuration(node);
    } else {
      getUINativeModule().imageAnimator.setDuration(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return this.stageValue !== this.value;
  }
}

class ImageAnimatorReverseModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('imageAnimatorReverse');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().imageAnimator.resetReverse(node);
    } else {
      getUINativeModule().imageAnimator.setReverse(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return this.stageValue !== this.value;
  }
}

class ImageAnimatorStateModifier extends ModifierWithKey<AnimationStatus> {
  constructor(value: AnimationStatus) {
    super(value);
  }
  static identity: Symbol = Symbol('imageAnimatorState');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().imageAnimator.resetState(node);
    } else {
      getUINativeModule().imageAnimator.setState(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return this.stageValue !== this.value;
  }
}

class ImageAnimatorFixedSizeModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('imageAnimatorFixedSize');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().imageAnimator.resetFixedSize(node);
    } else {
      getUINativeModule().imageAnimator.setFixedSize(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return this.stageValue !== this.value;
  }
}

class ImageAnimatorFillModeModifier extends ModifierWithKey<FillMode> {
  constructor(value: FillMode) {
    super(value);
  }
  static identity: Symbol = Symbol('imageAnimatorFillMode');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().imageAnimator.resetFillMode(node);
    } else {
      getUINativeModule().imageAnimator.setFillMode(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return this.stageValue !== this.value;
  }
}

class ImageAnimatorIterationsModeModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('imageAnimatorIterationsMode');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().imageAnimator.resetIterations(node);
    } else {
      getUINativeModule().imageAnimator.setIterations(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return this.stageValue !== this.value;
  }
}

class ImageAnimatorAutoMonitorInvisibleAreaModeModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('autoMonitorInvisibleAreaMode');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().imageAnimator.setAutoMonitorInvisibleAreaMode(node, false);
    } else {
      getUINativeModule().imageAnimator.setAutoMonitorInvisibleAreaMode(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return this.stageValue !== this.value;
  }
}

declare type OnStart = () => void;
class ImageAnimatorOnStartModifier extends ModifierWithKey<OnStart> {
  constructor(value: OnStart) {
    super(value);
  }
  static identity: Symbol = Symbol('imageAnimatorOnStart');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().imageAnimator.resetImageAnimatorOnStart(node);
    } else {
      getUINativeModule().imageAnimator.setImageAnimatorOnStart(node, this.value);
    }
  }
}

declare type OnPause = () => void;
class ImageAnimatorOnPauseModifier extends ModifierWithKey<OnPause> {
  constructor(value: OnPause) {
    super(value);
  }
  static identity: Symbol = Symbol('imageAnimatorOnPause');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().imageAnimator.resetImageAnimatorOnPause(node);
    } else {
      getUINativeModule().imageAnimator.setImageAnimatorOnPause(node, this.value);
    }
  }
}

declare type OnRepeat = () => void;
class ImageAnimatorOnRepeatModifier extends ModifierWithKey<OnRepeat> {
  constructor(value: OnRepeat) {
    super(value);
  }
  static identity: Symbol = Symbol('imageAnimatorOnRepeat');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().imageAnimator.resetImageAnimatorOnRepeat(node);
    } else {
      getUINativeModule().imageAnimator.setImageAnimatorOnRepeat(node, this.value);
    }
  }
}

declare type OnCancel = () => void;
class ImageAnimatorOnCancelModifier extends ModifierWithKey<OnCancel> {
  constructor(value: OnCancel) {
    super(value);
  }
  static identity: Symbol = Symbol('imageAnimatorOnCancel');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().imageAnimator.resetImageAnimatorOnCancel(node);
    } else {
      getUINativeModule().imageAnimator.setImageAnimatorOnCancel(node, this.value);
    }
  }
}

declare type OnFinish = () => void;
class ImageAnimatorOnFinishModifier extends ModifierWithKey<OnFinish> {
  constructor(value: OnFinish) {
    super(value);
  }
  static identity: Symbol = Symbol('imageAnimatorOnFinish');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().imageAnimator.resetImageAnimatorOnFinish(node);
    } else {
      getUINativeModule().imageAnimator.setImageAnimatorOnFinish(node, this.value);
    }
  }
}

class ArkImageAnimatorComponent extends ArkComponent implements CommonMethod<ImageAnimatorAttribute> {
  constructor(nativePtr: KNode, classType?: ModifierType) {
    super(nativePtr, classType);
  }
  images(value: Array<ImageFrameInfo>): ImageAnimatorAttribute {
    modifierWithKey(this._modifiersWithKeys, ImageAnimatorImagesModifier.identity,
      ImageAnimatorImagesModifier, value);
    return this;
  }
  state(value: AnimationStatus): ImageAnimatorAttribute {
    modifierWithKey(this._modifiersWithKeys, ImageAnimatorStateModifier.identity,
      ImageAnimatorStateModifier, value);
    return this;
  }
  duration(value: number): ImageAnimatorAttribute {
    modifierWithKey(this._modifiersWithKeys, ImageAnimatorDurationModifier.identity,
      ImageAnimatorDurationModifier, value);
    return this;
  }
  reverse(value: boolean): ImageAnimatorAttribute {
    modifierWithKey(this._modifiersWithKeys, ImageAnimatorReverseModifier.identity,
      ImageAnimatorReverseModifier, value);
    return this;
  }
  fixedSize(value: boolean): ImageAnimatorAttribute {
    modifierWithKey(this._modifiersWithKeys, ImageAnimatorFixedSizeModifier.identity,
      ImageAnimatorFixedSizeModifier, value);
    return this;
  }
  preDecode(value: number): ImageAnimatorAttribute {
    throw new Error('Method not implemented.');
  }
  fillMode(value: FillMode): ImageAnimatorAttribute {
    modifierWithKey(this._modifiersWithKeys, ImageAnimatorFillModeModifier.identity,
      ImageAnimatorFillModeModifier, value);
    return this;
  }
  iterations(value: number): ImageAnimatorAttribute {
    modifierWithKey(this._modifiersWithKeys, ImageAnimatorIterationsModeModifier.identity,
      ImageAnimatorIterationsModeModifier, value);
    return this;
  }
  monitorInvisibleAreaMode(value: boolean): ImageAnimatorAttribute {
    modifierWithKey(this._modifiersWithKeys, ImageAnimatorAutoMonitorInvisibleAreaModeModifier.identity,
      ImageAnimatorAutoMonitorInvisibleAreaModeModifier, value);
    return this;
  }
  onStart(event: () => void): ImageAnimatorAttribute {
    modifierWithKey(this._modifiersWithKeys, ImageAnimatorOnStartModifier.identity, ImageAnimatorOnIncModifier, event);
    return this;
  }
  onPause(event: () => void): ImageAnimatorAttribute {
    modifierWithKey(this._modifiersWithKeys, ImageAnimatorOnPauseModifier.identity, ImageAnimatorOnPauseModifier, event);
    return this;
  }
  onRepeat(event: () => void): ImageAnimatorAttribute {
    modifierWithKey(this._modifiersWithKeys, ImageAnimatorOnRepeatModifier.identity, ImageAnimatorOnRepeatModifier, event);
    return this;
  }
  onCancel(event: () => void): ImageAnimatorAttribute {
    modifierWithKey(this._modifiersWithKeys, ImageAnimatorOnCancelModifier.identity, ImageAnimatorOnCancelModifier, event);
    return this;
  }
  onFinish(event: () => void): ImageAnimatorAttribute {
    modifierWithKey(this._modifiersWithKeys, ImageAnimatorOnFinishModifier.identity, ImageAnimatorOnFinishModifier, event);
    return this;
  }
}
// @ts-ignore
globalThis.ImageAnimator.attributeModifier = function (modifier: ArkComponent): void {
  attributeModifierFunc.call(this, modifier, (nativePtr: KNode) => {
    return new ArkImageAnimatorComponent(nativePtr);
  }, (nativePtr: KNode, classType: ModifierType, modifierJS: ModifierJS) => {
    return new modifierJS.ImageAnimatorModifier(nativePtr, classType);
  });
};
