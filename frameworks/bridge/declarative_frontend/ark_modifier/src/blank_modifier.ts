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

class LazyArkBlankComponent extends ArkComponent {
  static module: BlankComponentModule | undefined = undefined;

  constructor(nativePtr: KNode, classType: ModifierType) {
    super(nativePtr, classType);
    if (LazyArkBlankComponent.module === undefined) {
      LazyArkBlankComponent.module = globalThis.requireNapi('arkui.components.arkblank');
    }

    this.lazyComponent = LazyArkBlankComponent.module.createComponent(nativePtr, classType);
  }

  setMap(): void {
    this.lazyComponent._modifiersWithKeys = this._modifiersWithKeys;
  }

  color(value: ResourceColor): this {
    this.lazyComponent.color(value);
    return this;
  }

  height(value: Length): this {
    this.lazyComponent.height(value);
    return this;
  }
}

class BlankModifier extends LazyArkBlankComponent implements AttributeModifier<BlankAttribute> {

  constructor(nativePtr: KNode, classType: ModifierType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
    this.setMap();
  }

  applyNormalAttribute(instance: BlankAttribute): void {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier<BlankAttribute, LazyArkBlankComponent, ArkComponent>(instance, this);
  }
}
