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

class LazyArkSliderComponent extends ArkComponent {
  static module: SliderComponentModule | undefined = undefined;
  constructor(nativePtr: KNode, classType: ModifierType) {
   super(nativePtr, classType);
   if (LazyArkSliderComponent.module === undefined) {
     LazyArkSliderComponent.module = globalThis.requireNapi('arkui.components.arkslider');
   }

   this.lazyComponent = LazyArkSliderComponent.module.createComponent(nativePtr, classType);
  }

  setMap(): void {
   this.lazyComponent._modifiersWithKeys = this._modifiersWithKeys;
  }

  allowChildCount(): number {
   return 0;
  }

  initialize(value: [SliderOptions | undefined]): this {
   this.lazyComponent.initialize(value);
   return this;
  }

  blockColor(value: ResourceColor | LinearGradient): this {
   this.lazyComponent.blockColor(value);
   return this;
  }

  trackColor(value: ResourceColor | LinearGradient): this {
   this.lazyComponent.trackColor(value);
   return this;
  }

  trackColorMetrics(value: ColorMetricsLinearGradient): this {
   this.lazyComponent.trackColorMetrics(value);
   return this;
  }

  selectedColor(value: ResourceColor | LinearGradient): this {
   this.lazyComponent.selectedColor(value);
   return this;
  }

  minLabel(value: string): this {
   throw new Error('Method not implemented.');
  }

  maxLabel(value: string): this {
   throw new Error('Method not implemented.');
  }

  showSteps(value: boolean, options?: SliderShowStepOptions): this {
   this.lazyComponent.showSteps(value, options);
   return this;
  }

  showTips(value: boolean, content?: ResourceStr): this {
   this.lazyComponent.showTips(value, content);
   return this;
  }

  trackThickness(value: Length): this {
   this.lazyComponent.trackThickness(value);
   return this;
  }

  onChange(callback: (value: number, mode: SliderChangeMode) => void): this {
   this.lazyComponent.onChange(callback);
   return this;
  }

  blockBorderColor(value: ResourceColor): this {
   this.lazyComponent.blockBorderColor(value);
   return this;
  }

  blockBorderWidth(value: Length): this {
   this.lazyComponent.blockBorderWidth(value);
   return this;
  }

  stepColor(value: ResourceColor): this {
   this.lazyComponent.stepColor(value);
   return this;
  }

  trackBorderRadius(value: Length): this {
   this.lazyComponent.trackBorderRadius(value);
   return this;
  }

  selectedBorderRadius(value: Dimension): this {
   this.lazyComponent.selectedBorderRadius(value);
   return this;
  }

  blockSize(value: SizeOptions): this {
   this.lazyComponent.blockSize(value);
   return this;
  }

  blockStyle(value: SliderBlockStyle): this {
   this.lazyComponent.blockStyle(value);
   return this;
  }

  stepSize(value: Length): this {
   this.lazyComponent.stepSize(value);
   return this;
  }

  sliderInteractionMode(value: SliderInteraction): this {
   this.lazyComponent.sliderInteractionMode(value);
   return this;
  }

  minResponsiveDistance(value: number): this {
   this.lazyComponent.minResponsiveDistance(value);
   return this;
  }

  contentModifier(value: ContentModifier<SliderConfiguration>): this {
   this.lazyComponent.contentModifier(value);
   return this;
  }

  slideRange(value: SlideRange): this {
   this.lazyComponent.slideRange(value);
   return this;
  }

  enableHapticFeedback(value: boolean): this {
   this.lazyComponent.enableHapticFeedback(value);
   return this;
  }

  prefix(value: ComponentContent, options?: SliderPrefixOptions): this {
   this.lazyComponent.prefix(value, options);
   return this;
  }

  suffix(value: ComponentContent, options?: SliderSuffixOptions): this {
   this.lazyComponent.suffix(value, options);
   return this;
  }
}

class SliderModifier extends LazyArkSliderComponent implements AttributeModifier<SliderAttribute> {

  constructor(nativePtr: KNode, classType: ModifierType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
    this.setMap();
  }

  applyNormalAttribute(instance: SliderAttribute): void {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier<SliderAttribute, ArkSliderComponent, ArkComponent>(instance, this);
  }
}
