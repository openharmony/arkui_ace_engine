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

class LazyArkNavigatorComponent extends ArkComponent {
  static module: NavigatorComponentModule | undefined = undefined;

  constructor(nativePtr: KNode, classType: ModifierType) {
    super(nativePtr, classType);
    if (LazyArkNavigatorComponent.module === undefined) {
      LazyArkNavigatorComponent.module = globalThis.requireNapi('arkui.components.arknavigator');
    }
    this.lazyComponent = LazyArkNavigatorComponent.module.createComponent(nativePtr, classType);
  }

  setMap(): void {
    this.lazyComponent._modifiersWithKeys = this._modifiersWithKeys;
  }

  active(value: boolean): this {
    this.lazyComponent.active(value);
    return this;
  }

  type(value: NavigationType): this {
    this.lazyComponent.type(value);
    return this;
  }

  target(value: string): this {
    this.lazyComponent.target(value);
    return this;
  }

  params(value: object): this {
    this.lazyComponent.params(value);
    return this;
  }
}

class NavigatorModifier extends LazyArkNavigatorComponent implements AttributeModifier<NavigatorAttribute> {

  constructor(nativePtr: KNode, classType: ModifierType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
    this.setMap();
  }

  applyNormalAttribute(instance: NavigatorAttribute): void {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier<NavigatorAttribute, ArkNavigatorComponent, ArkComponent>(instance, this);
  }
}
