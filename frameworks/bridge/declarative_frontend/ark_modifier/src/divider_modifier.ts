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

class LazyArkDividerComponent extends ArkComponent {
  static module: DividerComponentModule | undefined = undefined;

  constructor(nativePtr: KNode, classType: ModifierType) {
    super(nativePtr, classType);
    if (LazyArkDividerComponent.module === undefined) {
      LazyArkDividerComponent.module = globalThis.requireNapi('arkui.components.arkdivider');
    }
    this.lazyComponent = LazyArkDividerComponent.module.createComponent(nativePtr, classType);
  }

  setMap(): void {
    this.lazyComponent._modifiersWithKeys = this._modifiersWithKeys;
  }

  vertical(value: boolean): this {
    this.lazyComponent.vertical(value);
    return this;
  }

  color(value: ResourceColor): this {
    this.lazyComponent.color(value);
    return this;
  }

  strokeWidth(value: number | string): this {
    this.lazyComponent.strokeWidth(value);
    return this;
  }

  lineCap(value: LineCapStyle): this {
    this.lazyComponent.lineCap(value);
    return this;
  }
}

class DividerModifier extends LazyArkDividerComponent implements AttributeModifier<DividerAttribute> {

  constructor(nativePtr: KNode, classType: ModifierType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
    this.setMap();
  }

  applyNormalAttribute(instance: DividerAttribute): void {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier<DividerAttribute, LazyArkDividerComponent, ArkComponent>(instance, this);
  }
}
