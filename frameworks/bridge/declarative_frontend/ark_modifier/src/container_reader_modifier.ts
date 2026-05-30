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

class LazyArkContainerReaderComponent extends ArkComponent {
  static module: ContainerReaderComponentModule | undefined = undefined;
  constructor(nativePtr: KNode, classType: ModifierType) {
    super(nativePtr, classType);
    if (LazyArkContainerReaderComponent.module === undefined) {
      LazyArkContainerReaderComponent.module = globalThis.requireNapi('arkui.components.containerreader');
    }
    this.lazyComponent = LazyArkContainerReaderComponent.module.createComponent(nativePtr, classType);
  }

  setMap(): void {
    this.lazyComponent._modifiersWithKeys = this._modifiersWithKeys;
  }

  breakpointConfig(value: BreakpointOptions): this {
    this.lazyComponent.breakpointConfig(value);
    return this;
  }
}

class ContainerReaderModifier extends LazyArkContainerReaderComponent implements AttributeModifier<ContainerReaderAttribute> {

  constructor(nativePtr: KNode, classType: ModifierType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
    this.setMap();
  }

  applyNormalAttribute(instance: ContainerReaderAttribute): void {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier<ContainerReaderAttribute, ArkContainerReaderComponent, ArkComponent>(instance, this);
  }
}
