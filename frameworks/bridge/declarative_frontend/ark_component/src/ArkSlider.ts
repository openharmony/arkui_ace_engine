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
  builder: WrappedBuilder<Object[]> | null = null;
  sliderNode: BuilderNode<[SliderConfiguration]> | null = null;
  modifier: ContentModifier<SliderConfiguration>;
  needRebuild: boolean = false;
  constructor(nativePtr: KNode, classType?: ModifierType) {
    super(nativePtr, classType);
  }
  allowChildCount(): number {
    return 0;
  }
  initialize(value: Object[]): this {
    if (!value.length) {
      return this;
    }
    if (!isUndefined(value[0]) && !isNull(value[0]) && isObject(value[0])) {
      modifierWithKey(this._modifiersWithKeys, SliderOptionsModifier.identity, SliderOptionsModifier, value[0]);
    } else {
      modifierWithKey(this._modifiersWithKeys, SliderOptionsModifier.identity, SliderOptionsModifier, undefined);
    }
    return this;
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
    modifierWithKey(this._modifiersWithKeys, ShowStepsModifier.identity, ShowStepsModifier, value);
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
  selectedBorderRadius(value: Dimension): this {
    modifierWithKey(this._modifiersWithKeys, SelectedBorderRadiusModifier.identity, SelectedBorderRadiusModifier, value);
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
  sliderInteractionMode(value: SliderInteraction): this {
    modifierWithKey(this._modifiersWithKeys, InteractionModeModifier.identity, InteractionModeModifier, value);
    return this;
  }
  minResponsiveDistance(value: number): this {
    modifierWithKey(this._modifiersWithKeys, MinResponsiveDistanceModifier.identity, MinResponsiveDistanceModifier, value);
    return this;
  }
  contentModifier(value: ContentModifier<SliderConfiguration>): this {
    modifierWithKey(this._modifiersWithKeys, SliderContentModifier.identity, SliderContentModifier, value);
    return this;
  }
  slideRange(value: ValidSlideRange): this {
    modifierWithKey(this._modifiersWithKeys, ValidSlideRangeModifier.identity, ValidSlideRangeModifier, value);
    return this;
  }
  setContentModifier(modifier: ContentModifier<SliderConfiguration>): this {
    if (modifier === undefined || modifier === null) {
      getUINativeModule().slider.setContentModifierBuilder(this.nativePtr, false);
      return;
    }
    this.needRebuild = false;
    if (this.builder !== modifier.applyContent()) {
      this.needRebuild = true;
    }
    this.builder = modifier.applyContent();
    this.modifier = modifier;
    getUINativeModule().slider.setContentModifierBuilder(this.nativePtr, this);
  }
  makeContentModifierNode(context: UIContext, sliderConfiguration: SliderConfiguration): FrameNode | null {
    sliderConfiguration.contentModifier = this.modifier;
    if (isUndefined(this.sliderNode) || this.needRebuild) {
      const xNode = globalThis.requireNapi('arkui.node');
      this.sliderNode = new xNode.BuilderNode(context);
      this.sliderNode.build(this.builder, sliderConfiguration);
      this.needRebuild = false;
    } else {
      this.sliderNode.update(sliderConfiguration);
    }
    return this.sliderNode.getFrameNode();
  }
}

class SliderOptionsModifier extends ModifierWithKey<SliderOptions> {
  constructor(value: SliderOptions) {
    super(value);
  }
  static identity: Symbol = Symbol('sliderOptions');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().slider.setSliderOptions(node, undefined, undefined, undefined, undefined, undefined,
        undefined, undefined);
    } else {
      getUINativeModule().slider.setSliderOptions(node, this.value.value, this.value.min, this.value.max,
        this.value.step, this.value.style, this.value.direction, this.value.reverse);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue?.value, this.value?.value) ||
      !isBaseOrResourceEqual(this.stageValue?.min, this.value?.min) ||
      !isBaseOrResourceEqual(this.stageValue?.max, this.value?.max) ||
      !isBaseOrResourceEqual(this.stageValue?.step, this.value?.step) ||
      !isBaseOrResourceEqual(this.stageValue?.style, this.value?.style) ||
      !isBaseOrResourceEqual(this.stageValue?.direction, this.value?.direction) ||
      !isBaseOrResourceEqual(this.stageValue?.reverse, this.value?.reverse);
  }
}

class BlockStyleModifier extends ModifierWithKey<SliderBlockStyle> {
  constructor(value: SliderBlockStyle) {
    super(value);
  }
  static identity: Symbol = Symbol('sliderBlockStyle');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().slider.resetBlockStyle(node);
    } else {
      getUINativeModule().slider.setBlockStyle(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !((this.stageValue as SliderBlockStyle).type === (this.value as SliderBlockStyle).type &&
      (this.stageValue as SliderBlockStyle).image === (this.value as SliderBlockStyle).image &&
      (this.stageValue as SliderBlockStyle).shape === (this.value as SliderBlockStyle).shape);

  }
}

class ShowTipsModifier extends ModifierWithKey<ArkSliderTips> {
  constructor(value: ArkSliderTips) {
    super(value);
  }
  static identity: Symbol = Symbol('sliderShowTips');
  applyPeer(node: KNode, reset: boolean) {
    if (reset) {
      getUINativeModule().slider.resetShowTips(node);
    } else {
      getUINativeModule().slider.setShowTips(node, this.value.showTip, this.value?.tipText);
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
      getUINativeModule().slider.resetStepSize(node);
    } else {
      getUINativeModule().slider.setStepSize(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class BlockSizeModifier extends ModifierWithKey<SizeOptions> {
  constructor(value: SizeOptions) {
    super(value);
  }
  static identity: Symbol = Symbol('sliderBlockSize');
  applyPeer(node: KNode, reset: boolean) {
    if (reset) {
      getUINativeModule().slider.resetBlockSize(node);
    } else {
      getUINativeModule().slider.setBlockSize(node, this.value!.width, this.value!.height);
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
      getUINativeModule().slider.resetTrackBorderRadius(node);
    } else {
      getUINativeModule().slider.setTrackBorderRadius(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class StepColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity: Symbol = Symbol('sliderStepColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().slider.resetStepColor(node);
    } else {
      getUINativeModule().slider.setStepColor(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class BlockBorderColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity: Symbol = Symbol('sliderBlockBorderColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().slider.resetBlockBorderColor(node);
    } else {
      getUINativeModule().slider.setBlockBorderColor(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class BlockBorderWidthModifier extends ModifierWithKey<Length> {
  constructor(value: Length) {
    super(value);
  }
  static identity: Symbol = Symbol('sliderBlockBorderWidth');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().slider.resetBlockBorderWidth(node);
    } else {
      getUINativeModule().slider.setBlockBorderWidth(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class BlockColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity: Symbol = Symbol('sliderBlockColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().slider.resetBlockColor(node);
    } else {
      getUINativeModule().slider.setBlockColor(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TrackColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity: Symbol = Symbol('sliderTrackColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().slider.resetTrackBackgroundColor(node);
    } else {
      getUINativeModule().slider.setTrackBackgroundColor(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class SelectColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity: Symbol = Symbol('sliderSelectColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().slider.resetSelectColor(node);
    } else {
      getUINativeModule().slider.setSelectColor(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class ShowStepsModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('sliderShowSteps');
  applyPeer(node: KNode, reset: boolean) {
    if (reset) {
      getUINativeModule().slider.resetShowSteps(node);
    } else {
      getUINativeModule().slider.setShowSteps(node, this.value);
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
      getUINativeModule().slider.resetThickness(node);
    } else {
      getUINativeModule().slider.setThickness(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class ValidSlideRangeModifier extends ModifierWithKey<ValidSlideRange> {
  constructor(value: ValidSlideRange) {
    super(value);
  }
  static identity: Symbol = Symbol('slideRange');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().slider.resetValidSlideRange(node);
    } else {
      getUINativeModule().slider.setValidSlideRange(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class SelectedBorderRadiusModifier extends ModifierWithKey<Dimension> {
  constructor(value: Dimension) {
    super(value);
  }
  static identity: Symbol = Symbol('sliderSelectedBorderRadius');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().slider.resetSelectedBorderRadius(node);
    } else {
      getUINativeModule().slider.setSelectedBorderRadius(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class InteractionModeModifier extends ModifierWithKey<SliderInteraction> {
  constructor(value: SliderInteraction) {
    super(value);
  }
  static identity: Symbol = Symbol('sliderInteractionMode');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().slider.resetInteractionMode(node);
    } else {
      getUINativeModule().slider.setInteractionMode(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class MinResponsiveDistanceModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('sliderMinResponsiveDistance');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().slider.resetMinResponsiveDistance(node);
    } else {
      getUINativeModule().slider.setMinResponsiveDistance(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class SliderContentModifier extends ModifierWithKey<ContentModifier<SliderConfiguration>> {
  constructor(value: ContentModifier<SliderConfiguration>) {
    super(value);
  }
  static identity: Symbol = Symbol('sliderContentModifier');
  applyPeer(node: KNode, reset: boolean, component: ArkComponent) {
    let sliderComponent = component as ArkSliderComponent;
    sliderComponent.setContentModifier(this.value);
  }
}

// @ts-ignore
globalThis.Slider.attributeModifier = function (modifier: ArkComponent): void {
  attributeModifierFunc.call(this, modifier, (nativePtr: KNode) => {
    return new ArkSliderComponent(nativePtr);
  }, (nativePtr: KNode, classType: ModifierType, modifierJS: ModifierJS) => {
    return new modifierJS.SliderModifier(nativePtr, classType);
  });
};

// @ts-ignore
globalThis.Slider.contentModifier = function (modifier): void {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkSliderComponent(nativeNode);
  });
  component.setContentModifier(modifier);
};
