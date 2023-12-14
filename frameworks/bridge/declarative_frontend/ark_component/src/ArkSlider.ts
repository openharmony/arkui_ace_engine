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
class ArkSliderComponent extends ArkComponent implements SliderAttribute {
  constructor(nativePtr: KNode) {
    super(nativePtr);
  }
  onGestureJudgeBegin(callback: (gestureInfo: GestureInfo, event: BaseGestureEvent) => GestureJudgeResult): this {
    throw new Error('Method not implemented.');
  }
  blockColor(value: ResourceColor): this {
    modifierWithKey(this._modifiersWithKeys, BlockColorModifier.identity, BlockColorModifier, value);
    return this;
  }
  trackColor(value: ResourceColor): this {
    modifierWithKey(this._modifiersWithKeys, TrackColorModifier.identity, TrackColorModifier, value);
    return this;
  }
  selectedColor(value: ResourceColor): this {
    modifierWithKey(this._modifiersWithKeys, SelectColorModifier.identity, SelectColorModifier, value);
    return this;
  }
  minLabel(value: string): this {
    throw new Error('Method not implemented.');
  }
  maxLabel(value: string): this {
    throw new Error('Method not implemented.');
  }
  showSteps(value: boolean): this {
    modifier(this._modifiers, ShowStepsModifier, value);
    return this;
  }
  showTips(value: boolean, content?: any): this {
    let showTips = new ArkSliderTips(value, content);
    modifierWithKey(this._modifiersWithKeys, ShowTipsModifier.identity, ShowTipsModifier, showTips);
    return this;
  }
  trackThickness(value: Length): this {
    modifierWithKey(this._modifiersWithKeys, TrackThicknessModifier.identity, TrackThicknessModifier, value);
    return this;
  }
  onChange(callback: (value: number, mode: SliderChangeMode) => void): this {
    throw new Error('Method not implemented.');
  }
  blockBorderColor(value: ResourceColor): this {
    modifierWithKey(this._modifiersWithKeys, BlockBorderColorModifier.identity, BlockBorderColorModifier, value);
    return this;
  }
  blockBorderWidth(value: Length): this {
    modifierWithKey(this._modifiersWithKeys, BlockBorderWidthModifier.identity, BlockBorderWidthModifier, value);
    return this;
  }
  stepColor(value: ResourceColor): this {
    modifierWithKey(this._modifiersWithKeys, StepColorModifier.identity, StepColorModifier, value);
    return this;
  }
  trackBorderRadius(value: Length): this {
    modifierWithKey(this._modifiersWithKeys, TrackBorderRadiusModifier.identity, TrackBorderRadiusModifier, value);
    return this;
  }
  blockSize(value: SizeOptions): this {
    modifierWithKey(this._modifiersWithKeys, BlockSizeModifier.identity, BlockSizeModifier, value);
    return this;
  }
  blockStyle(value: SliderBlockStyle): this {
    modifierWithKey(this._modifiersWithKeys, BlockStyleModifier.identity, BlockStyleModifier, value);
    return this;
  }
  stepSize(value: Length): this {
    modifierWithKey(this._modifiersWithKeys, StepSizeModifier.identity, StepSizeModifier, value);
    return this;
  }
}

class BlockStyleModifier extends ModifierWithKey<SliderBlockStyle> {
  constructor(value: SliderBlockStyle) {
    super(value);
  }
  static identity: Symbol = Symbol('sliderBlockStyle');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().slider.resetBlockStyle(node);
    }
    else {
      GetUINativeModule().slider.setBlockStyle(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !((this.stageValue as SliderBlockStyle).type === (this.value as SliderBlockStyle).type &&
      (this.stageValue as SliderBlockStyle).image === (this.value as SliderBlockStyle).image &&
      (this.stageValue as SliderBlockStyle).shape === (this.value as SliderBlockStyle).shape)

  }
}

class ShowTipsModifier extends ModifierWithKey<ArkSliderTips> {
  constructor(value: ArkSliderTips) {
    super(value);
  }
  static identity: Symbol = Symbol('sliderShowTips');
  applyPeer(node: KNode, reset: boolean) {
    if (reset) {
      GetUINativeModule().slider.resetShowTips(node);
    }
    else {
      GetUINativeModule().slider.setShowTips(node, this.value.showTip, this.value?.tipText);
    }
  }

  checkObjectDiff(): boolean {
    let showTipDiff = this.stageValue.showTip !== this.value.showTip;
    let tipTextDiff = !isBaseOrResourceEqual(this.stageValue.tipText, this.value.tipText);
    return showTipDiff || tipTextDiff;
  }

}

class StepSizeModifier extends ModifierWithKey<Length> {
  constructor(value: Length) {
    super(value);
  }
  static identity: Symbol = Symbol('sliderStepSize');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().slider.resetStepSize(node);
    } else {
      GetUINativeModule().slider.setStepSize(node, this.value);
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

class BlockSizeModifier extends ModifierWithKey<SizeOptions> {
  constructor(value: SizeOptions) {
    super(value);
  }
  static identity: Symbol = Symbol('sliderBlockSize');
  applyPeer(node: KNode, reset: boolean) {
    if (reset) {
      GetUINativeModule().slider.resetBlockSize(node);
    }
    else {
      GetUINativeModule().slider.setBlockSize(node, this.value!.width, this.value!.height);
    }
  }

  checkObjectDiff(): boolean {
    if (isResource(this.stageValue.height) && isResource(this.value.height) && isResource(this.stageValue.width) && isResource(this.value.width)) {
      return !(isResourceEqual(this.stageValue.height, this.value.height) && isResourceEqual(this.stageValue.width, this.value.width));
    } else {
      return true;
    }
  }
}

class TrackBorderRadiusModifier extends ModifierWithKey<Length> {
  constructor(value: Length) {
    super(value);
  }
  static identity: Symbol = Symbol('sliderTrackBorderRadius');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().slider.resetTrackBorderRadius(node);
    } else {
      GetUINativeModule().slider.setTrackBorderRadius(node, this.value);
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

class StepColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity: Symbol = Symbol('sliderStepColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().slider.resetStepColor(node);
    } else {
      GetUINativeModule().slider.setStepColor(node, this.value);
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

class BlockBorderColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity: Symbol = Symbol('sliderBlockBorderColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().slider.resetBlockBorderColor(node);
    } else {
      GetUINativeModule().slider.setBlockBorderColor(node, this.value);
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

class BlockBorderWidthModifier extends ModifierWithKey<Length> {
  constructor(value: Length) {
    super(value);
  }
  static identity: Symbol = Symbol('sliderBlockBorderWidth');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().slider.resetBlockBorderWidth(node);
    } else {
      GetUINativeModule().slider.setBlockBorderWidth(node, this.value);
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

class BlockColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity: Symbol = Symbol('sliderBlockColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().slider.resetBlockColor(node);
    } else {
      GetUINativeModule().slider.setBlockColor(node, this.value);
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

class TrackColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity: Symbol = Symbol('sliderTrackColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().slider.resetTrackBackgroundColor(node);
    } else {
      GetUINativeModule().slider.setTrackBackgroundColor(node, this.value);
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

class SelectColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity: Symbol = Symbol('sliderSelectColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().slider.resetSelectColor(node);
    } else {
      GetUINativeModule().slider.setSelectColor(node, this.value);
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

class ShowStepsModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('sliderShowSteps');
  applyPeer(node: KNode, reset: boolean) {
    if (reset) {
      GetUINativeModule().slider.resetShowSteps(node);
    }
    else {
      GetUINativeModule().slider.setShowSteps(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return this.stageValue !== this.value;
  }
}

class TrackThicknessModifier extends ModifierWithKey<Length> {
  constructor(value: Length) {
    super(value);
  }
  static identity: Symbol = Symbol('sliderTrackThickness');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().slider.resetThickness(node);
    } else {
      GetUINativeModule().slider.setThickness(node, this.value);
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

// @ts-ignore
globalThis.Slider.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkSliderComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
}