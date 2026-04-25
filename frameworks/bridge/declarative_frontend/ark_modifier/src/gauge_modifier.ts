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

class LazyArkGaugeComponent extends ArkComponent {
  static module: GaugeComponentModule | undefined = undefined;

  constructor(nativePtr: KNode, classType: ModifierType) {
    super(nativePtr, classType);
    if (LazyArkGaugeComponent.module === undefined) {
      LazyArkGaugeComponent.module = globalThis.requireNapi('arkui.components.arkgauge');
    }

    this.lazyComponent = LazyArkGaugeComponent.module.createComponent(nativePtr, classType);
  }

  setMap(): void {
    this.lazyComponent._modifiersWithKeys = this._modifiersWithKeys;
  }

  value(value: number): this {
    this.lazyComponent.value(value);
    return this;
  }

  startAngle(angle: number): this {
    this.lazyComponent.startAngle(angle);
    return this;
  }

  endAngle(angle: number): this {
    this.lazyComponent.endAngle(angle);
    return this;
  }

  colors(colors: ResourceColor | LinearGradient | Array<[ResourceColor | LinearGradient, number]>): this {
    this.lazyComponent.colors(colors);
    return this;
  }

  strokeWidth(length: Length): this {
    this.lazyComponent.strokeWidth(length);
    return this;
  }

  description(value: CustomBuilder): this {
    throw new Error('Method not implemented.');
  }

  trackShadow(value: GaugeShadowOptions): this {
    this.lazyComponent.trackShadow(value);
    return this;
  }

  indicator(value: GaugeIndicatorOptions): this {
    this.lazyComponent.indicator(value);
    return this;
  }

  contentModifier(value: ContentModifier<GaugeConfiguration>): this {
    this.lazyComponent.contentModifier(value);
    return this;
  }

  privacySensitive(value: Optional<boolean>): this {
    this.lazyComponent.privacySensitive(value);
    return this;
  }
}
class GaugeModifier extends LazyArkGaugeComponent implements AttributeModifier<GaugeAttribute> {

  constructor(nativePtr: KNode, classType: ModifierType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
    this.setMap();
  }

  applyNormalAttribute(instance: GaugeAttribute): void {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier<GaugeAttribute, ArkGaugeComponent, ArkComponent>(instance, this);
  }
}
