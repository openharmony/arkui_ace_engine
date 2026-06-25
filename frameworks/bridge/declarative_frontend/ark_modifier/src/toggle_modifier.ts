/*
 * Copyright (c) 2024-2026 Huawei Device Co., Ltd.
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

class LazyArkToggleComponent extends ArkComponent {
  static module: ToggleComponentModule | undefined = undefined;
  constructor(nativePtr: KNode, classType: ModifierType) {
    super(nativePtr, classType);
    if (LazyArkToggleComponent.module === undefined) {
      LazyArkToggleComponent.module = globalThis.requireNapi('arkui.components.arktoggle');
    }

    this.lazyComponent = LazyArkToggleComponent.module.createComponent(nativePtr, classType);
  }

  setMap(): void {
    this.lazyComponent._modifiersWithKeys = this._modifiersWithKeys;
  }

  allowChildCount(): number {
    return this.lazyComponent.allowChildCount();
  }

  initialize(value: Object[]): this {
    this.lazyComponent.initialize(value);
    return this;
  }

  onChange(callback: (isOn: boolean) => void): this {
    this.lazyComponent.onChange(callback);
    return this;
  }

  selectedColor(value: ResourceColor): this {
    this.lazyComponent.selectedColor(value);
    return this;
  }

  switchPointColor(value: ResourceColor): this {
    this.lazyComponent.switchPointColor(value);
    return this;
  }

  height(value: Length): this {
    this.lazyComponent.height(value);
    return this;
  }

  responseRegion(value: Array<Rectangle> | Rectangle): this {
    this.lazyComponent.responseRegion(value);
    return this;
  }

  padding(value: Padding | Length): this {
    this.lazyComponent.padding(value);
    return this;
  }

  backgroundColor(value: ResourceColor): this {
    this.lazyComponent.backgroundColor(value);
    return this;
  }

  hoverEffect(value: HoverEffect): this {
    this.lazyComponent.hoverEffect(value);
    return this;
  }

  switchStyle(value: SwitchStyle): this {
    this.lazyComponent.switchStyle(value);
    return this;
  }

  margin(value: Margin | Length): this {
    this.lazyComponent.margin(value);
    return this;
  }

  contentModifier(value: ContentModifier<ToggleConfiguration>): this {
    this.lazyComponent.contentModifier(value);
    return this;
  }
}
class ToggleModifier extends LazyArkToggleComponent implements AttributeModifier<ToggleAttribute> {

  constructor(nativePtr: KNode, classType: ModifierType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
    this.setMap();
  }

  applyNormalAttribute(instance: ToggleAttribute): void {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier<ToggleAttribute, ArkToggleComponent, ArkComponent>(instance, this);
  }
}
