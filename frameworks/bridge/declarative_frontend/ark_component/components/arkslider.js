/*
     * Copyright (c) 2026 Huawei Device Co., Ltd.
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

class ArkSliderStepOptions {
  constructor(value, options) {
    this.showSteps = value;
    this.stepOptions = options;
  }
  isEqual(another) {
    let isShowStepsEqual = this.showSteps === another.showSteps;
    let isStepOptionsEqual = true;
    if ((this.stepOptions === null) || (this.stepOptions === undefined)) {
      isStepOptionsEqual = (another.stepOptions === null) || (another.stepOptions === undefined);
    } else if ((another.stepOptions === null) || (another.stepOptions === undefined)) {
      isStepOptionsEqual = false;
    } else if (this.stepOptions.stepsAccessibility.size !== another.stepOptions.stepsAccessibility.size) {
      isStepOptionsEqual = false;
    } else {
      for (const [key, val] of this.stepOptions.stepsAccessibility) {
        if (!another.stepOptions.stepsAccessibility.has(key)) {
          isStepOptionsEqual = false;
        } else if (!isBaseOrResourceEqual(another.stepOptions.stepsAccessibility.get(key), val)) {
          isStepOptionsEqual = false;
        }
      }
    }
    return isShowStepsEqual && isStepOptionsEqual;
  }
}
class ArkSliderTips {
  constructor(value, content) {
    this.showTip = value;
    this.tipText = content;
  }
  isEqual(another) {
    return this.showTip === another.showTip && this.tipText === another.tipText;
  }
}
class ArkPrefixOrSuffix {
  constructor(value, options) {
    this.value = value;
    this.options = options;
  }
  isEqual(another) {
    return this.value === another.value && this.options === another.options;
  }
}
/// <reference path='./import.ts' />
class ArkSliderComponent extends ArkComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
  }
  allowChildCount() {
    return 0;
  }
  initialize(value) {
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
  blockColor(value) {
    modifierWithKey(this._modifiersWithKeys, BlockColorModifier.identity, BlockColorModifier, value);
    return this;
  }
  trackColor(value) {
    modifierWithKey(this._modifiersWithKeys, TrackColorModifier.identity, TrackColorModifier, value);
    return this;
  }
  trackColorMetrics(value) {
    modifierWithKey(this._modifiersWithKeys, TrackColorMetricsModifier.identity, TrackColorMetricsModifier, value);
    return this;
  }
  selectedColor(value) {
    modifierWithKey(this._modifiersWithKeys, SelectColorModifier.identity, SelectColorModifier, value);
    return this;
  }
  minLabel(value) {
    throw new Error('Method not implemented.');
  }
  maxLabel(value) {
    throw new Error('Method not implemented.');
  }
  showSteps(value, options) {
    let stepOptions = new ArkSliderStepOptions(value, options);
    modifierWithKey(this._modifiersWithKeys, ShowStepsModifier.identity, ShowStepsModifier, stepOptions);
    return this;
  }
  showTips(value, content) {
    let showTips = new ArkSliderTips(value, content);
    modifierWithKey(this._modifiersWithKeys, ShowTipsModifier.identity, ShowTipsModifier, showTips);
    return this;
  }
  trackThickness(value) {
    modifierWithKey(this._modifiersWithKeys, TrackThicknessModifier.identity, TrackThicknessModifier, value);
    return this;
  }
  onChange(callback) {
    modifierWithKey(this._modifiersWithKeys, OnChangeModifier.identity, OnChangeModifier, callback);
    return this;
  }
  blockBorderColor(value) {
    modifierWithKey(this._modifiersWithKeys, BlockBorderColorModifier.identity, BlockBorderColorModifier, value);
    return this;
  }
  blockBorderWidth(value) {
    modifierWithKey(this._modifiersWithKeys, BlockBorderWidthModifier.identity, BlockBorderWidthModifier, value);
    return this;
  }
  stepColor(value) {
    modifierWithKey(this._modifiersWithKeys, StepColorModifier.identity, StepColorModifier, value);
    return this;
  }
  trackBorderRadius(value) {
    modifierWithKey(this._modifiersWithKeys, TrackBorderRadiusModifier.identity, TrackBorderRadiusModifier, value);
    return this;
  }
  selectedBorderRadius(value) {
    modifierWithKey(this._modifiersWithKeys, SelectedBorderRadiusModifier.identity, SelectedBorderRadiusModifier, value);
    return this;
  }
  blockSize(value) {
    modifierWithKey(this._modifiersWithKeys, BlockSizeModifier.identity, BlockSizeModifier, value);
    return this;
  }
  blockStyle(value) {
    modifierWithKey(this._modifiersWithKeys, BlockStyleModifier.identity, BlockStyleModifier, value);
    return this;
  }
  stepSize(value) {
    modifierWithKey(this._modifiersWithKeys, StepSizeModifier.identity, StepSizeModifier, value);
    return this;
  }
  sliderInteractionMode(value) {
    modifierWithKey(this._modifiersWithKeys, InteractionModeModifier.identity, InteractionModeModifier, value);
    return this;
  }
  minResponsiveDistance(value) {
    modifierWithKey(this._modifiersWithKeys, MinResponsiveDistanceModifier.identity, MinResponsiveDistanceModifier, value);
    return this;
  }
  contentModifier(value) {
    modifierWithKey(this._modifiersWithKeys, SliderContentModifier.identity, SliderContentModifier, value);
    return this;
  }
  slideRange(value) {
    modifierWithKey(this._modifiersWithKeys, ValidSlideRangeModifier.identity, ValidSlideRangeModifier, value);
    return this;
  }
  setContentModifier(modifier) {
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
  makeContentModifierNode(context, sliderConfiguration) {
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
  enableHapticFeedback(value) {
    modifierWithKey(this._modifiersWithKeys, SliderEnableHapticFeedbackModifier.identity, SliderEnableHapticFeedbackModifier, value);
    return this;
  }
  prefix(value, options) {
    let prefix = new ArkPrefixOrSuffix(value, options);
    modifierWithKey(this._modifiersWithKeys, PrefixModifier.identity, PrefixModifier, prefix);
    return this;
  }
  suffix(value, options) {
    let suffix = new ArkPrefixOrSuffix(value, options);
    modifierWithKey(this._modifiersWithKeys, SuffixModifier.identity, SuffixModifier, suffix);
    return this;
  }
}
class SliderOptionsModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().slider.setSliderOptions(node, undefined, undefined, undefined, undefined, undefined,
        undefined, undefined);
    } else {
      getUINativeModule().slider.setSliderOptions(node, this.value.value, this.value.min, this.value.max,
        this.value.step, this.value.style, this.value.direction, this.value.reverse);
    }
  }

  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue.value, this.value.value) ||
      !isBaseOrResourceEqual(this.stageValue.min, this.value.min) ||
      !isBaseOrResourceEqual(this.stageValue.max, this.value.max) ||
      !isBaseOrResourceEqual(this.stageValue.step, this.value.step) ||
      !isBaseOrResourceEqual(this.stageValue.style, this.value.style) ||
      !isBaseOrResourceEqual(this.stageValue.direction, this.value.direction) ||
      !isBaseOrResourceEqual(this.stageValue.reverse, this.value.reverse);
  }
}
SliderOptionsModifier.identity = Symbol('sliderOptions');
class BlockStyleModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().slider.resetBlockStyle(node);
    }
    else {
      getUINativeModule().slider.setBlockStyle(node, this.value);
    }
  }
  checkObjectDiff() {
    return !(this.stageValue.type === this.value.type &&
      this.stageValue.image === this.value.image &&
      this.stageValue.shape === this.value.shape);
  }
}
BlockStyleModifier.identity = Symbol('sliderBlockStyle');
class ShowTipsModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    let _a;
    if (reset) {
      getUINativeModule().slider.resetShowTips(node);
    }
    else {
      getUINativeModule().slider.setShowTips(node, this.value.showTip, (_a = this.value) === null || _a === void 0 ? void 0 : _a.tipText);
    }
  }
  checkObjectDiff() {
    let showTipDiff = this.stageValue.showTip !== this.value.showTip;
    let tipTextDiff = !isBaseOrResourceEqual(this.stageValue.tipText, this.value.tipText);
    return showTipDiff || tipTextDiff;
  }
}
ShowTipsModifier.identity = Symbol('sliderShowTips');
class StepSizeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().slider.resetSliderStepSize(node);
    }
    else {
      getUINativeModule().slider.setSliderStepSize(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
StepSizeModifier.identity = Symbol('sliderStepSize');
class BlockSizeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().slider.resetBlockSize(node);
    }
    else {
      getUINativeModule().slider.setBlockSize(node, this.value.width, this.value.height);
    }
  }
}
BlockSizeModifier.identity = Symbol('sliderBlockSize');
class TrackBorderRadiusModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().slider.resetTrackBorderRadius(node);
    }
    else {
      getUINativeModule().slider.setTrackBorderRadius(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TrackBorderRadiusModifier.identity = Symbol('sliderTrackBorderRadius');
class StepColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().slider.resetStepColor(node);
    }
    else {
      getUINativeModule().slider.setStepColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
StepColorModifier.identity = Symbol('sliderStepColor');
class BlockBorderColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().slider.resetBlockBorderColor(node);
    }
    else {
      getUINativeModule().slider.setBlockBorderColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
BlockBorderColorModifier.identity = Symbol('sliderBlockBorderColor');
class BlockBorderWidthModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().slider.resetBlockBorderWidth(node);
    }
    else {
      getUINativeModule().slider.setBlockBorderWidth(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
BlockBorderWidthModifier.identity = Symbol('sliderBlockBorderWidth');
class BlockColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().slider.resetBlockColor(node);
    }
    else {
      getUINativeModule().slider.setBlockColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
BlockColorModifier.identity = Symbol('sliderBlockColor');
class TrackColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().slider.resetTrackBackgroundColor(node);
    }
    else {
      getUINativeModule().slider.setTrackBackgroundColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TrackColorModifier.identity = Symbol('sliderTrackColor');
class TrackColorMetricsModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().slider.resetTrackColorMetrics(node);
    }
    else {
      getUINativeModule().slider.setTrackColorMetrics(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TrackColorMetricsModifier.identity = Symbol('sliderTrackColorMetrics');
class SelectColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().slider.resetSelectColor(node);
    }
    else {
      getUINativeModule().slider.setSelectColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
SelectColorModifier.identity = Symbol('sliderSelectColor');
class ShowStepsModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().slider.resetShowSteps(node);
    }
    else {
      getUINativeModule().slider.setShowSteps(node, this.value.showSteps, (_a = this.value) === null || _a === void 0 ? void 0 : _a.stepOptions);
    }
  }
  checkObjectDiff() {
    let isShowStepsDiff = this.stageValue.showSteps !== this.value.showSteps;
    let isStepOptionsDiff = false;
    if ((this.stageValue.stepOptions === null) || (this.stageValue.stepOptions === undefined)) {
      isStepOptionsDiff = (this.value.stepOptions !== null) && (this.value.stepOptions !== undefined);
    } else if ((this.value.stepOptions === null) || (this.value.stepOptions === undefined)) {
      isStepOptionsDiff = true;
    } else if (this.stageValue.stepOptions.stepsAccessibility.size !==
      this.value.stepOptions.stepsAccessibility.size) {
      isStepOptionsDiff = true;
    } else {
      for (const [key, val] of this.stageValue.stepOptions.stepsAccessibility) {
        if (!this.value.stepOptions.stepsAccessibility.has(key)) {
          isStepOptionsDiff = true;
        } else if (!isBaseOrResourceEqual(this.value.stepOptions.stepsAccessibility.get(key), val)) {
          isStepOptionsDiff = true;
        }
      }
    }
    return isShowStepsDiff || isStepOptionsDiff;
  }
}
ShowStepsModifier.identity = Symbol('sliderShowSteps');
class TrackThicknessModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().slider.resetThickness(node);
    }
    else {
      getUINativeModule().slider.setThickness(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TrackThicknessModifier.identity = Symbol('sliderTrackThickness');
class OnChangeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().slider.resetOnChange(node);
    }
    else {
      getUINativeModule().slider.setOnChange(node, this.value);
    }
  }
}
OnChangeModifier.identity = Symbol('sliderOnChange');
class ValidSlideRangeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().slider.resetValidSlideRange(node);
    } else {
      getUINativeModule().slider.setValidSlideRange(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
ValidSlideRangeModifier.identity = Symbol('slideRange');
class SelectedBorderRadiusModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().slider.resetSelectedBorderRadius(node);
    } else {
      getUINativeModule().slider.setSelectedBorderRadius(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
SelectedBorderRadiusModifier.identity = Symbol('sliderSelectedBorderRadius');
class InteractionModeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().slider.resetInteractionMode(node);
    } else {
      getUINativeModule().slider.setInteractionMode(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
InteractionModeModifier.identity = Symbol('sliderInteractionMode');
class MinResponsiveDistanceModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().slider.resetMinResponsiveDistance(node);
    } else {
      getUINativeModule().slider.setMinResponsiveDistance(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
MinResponsiveDistanceModifier.identity = Symbol('sliderMinResponsiveDistance');
class SliderContentModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(nodenode, reset, component) {
    let sliderComponent = component;
    sliderComponent.setContentModifier(this.value);
  }
}
class PrefixModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().slider.resetPrefix(node);
    }
    else {
      getUINativeModule().slider.setPrefix(node, this.value.options);
    }
  }
}
class SuffixModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().slider.resetSuffix(node);
    }
    else {
      getUINativeModule().slider.setSuffix(node, this.value.options);
    }
  }
}
class SliderEnableHapticFeedbackModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().slider.resetEnableHapticFeedback(node);
    }
    else {
      getUINativeModule().slider.setEnableHapticFeedback(node, this.value);
    }
  }
}
SliderEnableHapticFeedbackModifier.identity = Symbol('sliderEnableHapticFeedback');

SliderContentModifier.identity = Symbol('sliderContentModifier');
// @ts-ignore
if (globalThis.Slider !== undefined) {
  globalThis.Slider.attributeModifier = function (modifier) {
    attributeModifierFunc.call(this, modifier, (nativePtr) => {
      return new ArkSliderComponent(nativePtr);
    }, (nativePtr, classType, modifierJS) => {
      return new modifierJS.SliderModifier(nativePtr, classType);
    });
  };
  globalThis.Slider.contentModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
      return new ArkSliderComponent(nativeNode);
    });
    component.setContentModifier(modifier);
  };
}

class JSSlider extends JSViewAbstract {
  static create(params) {
    getUINativeModule().slider.create(params);
  }

  static blockColor(value) {
    getUINativeModule().slider.setBlockColor(true, value);
  }
  static trackColor(value) {
    getUINativeModule().slider.setTrackBackgroundColor(true, value);
  }
  static trackColorMetrics(value) {
    getUINativeModule().slider.setTrackColorMetrics(true, value);
  }
  static selectedColor(value) {
    getUINativeModule().slider.setSelectColor(true, value);
  }
  static minLabel(value) {
    getUINativeModule().slider.setMinLabel(true, value);
  }
  static maxLabel(value) {
    getUINativeModule().slider.setMaxLabel(true, value);
  }
  static showSteps(value, options) {
    getUINativeModule().slider.setShowSteps(true, value, options);
  }
  static showTips(value, content) {
    getUINativeModule().slider.setShowTips(true, value, content);
  }
  static trackThickness(value) {
    getUINativeModule().slider.setThickness(true, value);
  }
  static onChange(callback) {
    getUINativeModule().slider.setOnChange(true, callback);

  }
  static blockBorderColor(value) {
    getUINativeModule().slider.setBlockBorderColor(true, value);
  }
  static blockBorderWidth(value) {
    getUINativeModule().slider.setBlockBorderWidth(true, value);
  }
  static stepColor(value) {
    getUINativeModule().slider.setStepColor(true, value);
  }
  static trackBorderRadius(value) {
    getUINativeModule().slider.setTrackBorderRadius(true, value);
  }
  static selectedBorderRadius(value) {
    getUINativeModule().slider.setSelectedBorderRadius(true, value);
  }
  static blockSize(value) {
    getUINativeModule().slider.setBlockSize(true, value);
  }
  static blockStyle(value) {
    getUINativeModule().slider.setBlockStyle(true, value);
  }
  static stepSize(value) {
    getUINativeModule().slider.setSliderStepSize(true, value);
  }
  static sliderInteractionMode(value) {
    getUINativeModule().slider.setInteractionMode(true, value);
  }
  static minResponsiveDistance(value) {
    getUINativeModule().slider.setMinResponsiveDistance(true, value);
  }
  static slideRange(value) {
    getUINativeModule().slider.setValidSlideRange(true, value);
  }
  static digitalCrownSensitivity(value) {
    getUINativeModule().slider.setDigitalCrownSensitivity(true, value);
  }
  static contentModifier(modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
      return createComponent(nativeNode, 'slider');
    });
    component.setContentModifier(modifier);
  }
  static attributeModifier(modifier) {
    attributeModifierFunc.call(this, modifier, (nativePtr) => {
      return new ArkSliderComponent(nativePtr);
    }, (nativePtr, classType, modifierJS) => {
      return new modifierJS.SliderModifier(nativePtr, classType);
    });
  }

  static enableHapticFeedback(value) {
    getUINativeModule().slider.setEnableHapticFeedback(true, value);
  }
  static prefix(value, options) {
    getUINativeModule().slider.setPrefix(true, value, options);
  }
  static suffix(value, options) {
    getUINativeModule().slider.setSuffix(true, value, options);
  }

  static onClick(value) {
    __Common__.onClick(value);
  }
  static onKeyEvent(value) {
    __Common__.onKeyEvent(value);
  }
  static onDeleteEvent(value) {
    __Common__.onDeleteEvent(value);
  }
  static onAttach(value) {
    __Common__.onAttach(value);
  }
  static onAppear(value) {
    __Common__.onAppear(value);
  }
  static onDetach(value) {
    __Common__.onDetach(value);
  }
  static onDisAppear(value) {
    __Common__.onDisAppear(value);
  }
  static onTouch(value) {
    __Common__.onTouch(value);
  }
}

function createComponent(nativePtr, classType) {
  return new ArkSliderComponent(nativePtr, classType);
}

function exportComponent() {
  globalThis.ArkSliderComponent = ArkSliderComponent;
}

function exportView() {
  globalThis.Slider = JSSlider;
}

export default { ArkSliderComponent, createComponent, exportComponent, exportView };