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

class LazyArkGridColComponent extends ArkComponent {
  static module: GridColComponentModule | undefined = undefined;

  constructor(nativePtr: KNode, classType: ModifierType) {
    super(nativePtr, classType);
    if (LazyArkGridColComponent.module === undefined) {
      LazyArkGridColComponent.module = globalThis.requireNapi('arkui.components.arkgridcol');
    }
    this.lazyComponent = LazyArkGridColComponent.module.createComponent(nativePtr, classType);
  }

  setMap(): void {
    this.lazyComponent._modifiersWithKeys = this._modifiersWithKeys;
  }

  span(value: any): this {
    this.lazyComponent.span(value);
    return this;
  }

  gridColOffset(value: any): this {
    this.lazyComponent.gridColOffset(value);
    return this;
  }

  order(value: any): this {
    this.lazyComponent.order(value);
    return this;
  }
}

class GridColModifier extends LazyArkGridColComponent implements AttributeModifier<GridColAttribute> {
  constructor(nativePtr: KNode, classType: ModifierType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
    this.setMap();
  }

  applyNormalAttribute(instance: GridColAttribute): void {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier<GridColAttribute, LazyArkGridColComponent, ArkComponent>(instance, this);
  }
}