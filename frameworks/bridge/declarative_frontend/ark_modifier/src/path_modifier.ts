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

class LazyArkPathComponent extends LazyArkCommonShapeComponent {
  static module: PathComponentModule | undefined = undefined;
  constructor(nativePtr: KNode, classType: ModifierType) {
    super(nativePtr, classType);
    if (LazyArkPathComponent.module === undefined) {
      LazyArkPathComponent.module = globalThis.requireNapi('arkui.components.arkpath');
    }
    this.lazyComponent = LazyArkPathComponent.module.createComponent(nativePtr, classType);
  }

  commands(value: ResourceStr): this {
    this.lazyComponent.commands(value);
    return this;
  }

  setMap(): void {
    this.lazyComponent._modifiersWithKeys = this._modifiersWithKeys;
  }
}

class PathModifier extends LazyArkPathComponent implements AttributeModifier<PathAttribute> {

  constructor(nativePtr: KNode, classType: ModifierType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
    this.setMap();
  }

  applyNormalAttribute(instance: PathAttribute): void {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier<PathAttribute, ArkPathComponent, ArkComponent>(instance, this);
  }
}
