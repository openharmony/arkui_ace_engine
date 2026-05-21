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

class LazyArkGridRowComponent extends ArkComponent {
  static module: any | undefined = undefined;

  constructor(nativePtr: KNode, classType: ModifierType) {
    super(nativePtr, classType);
    if (LazyArkGridRowComponent.module === undefined) {
      LazyArkGridRowComponent.module = globalThis.requireNapi('arkui.components.arkgridrow');
    }
    this.lazyComponent = LazyArkGridRowComponent.module.createComponent(nativePtr, classType);
  }

  setMap(): void {
    this.lazyComponent._modifiersWithKeys = this._modifiersWithKeys;
  }

  onBreakpointChange(callback: (breakpoints: string) => void): this {
    this.lazyComponent.onBreakpointChange(callback);
    return this;
  }

  alignItems(value: ItemAlign): this {
    this.lazyComponent.alignItems(value);
    return this;
  }

  setDirection(value: number): this {
    this.lazyComponent.setDirection(value);
    return this;
  }

  setBreakpoints(value: any): this {
    this.lazyComponent.setBreakpoints(value);
    return this;
  }

  setColumns(value: any): this {
    this.lazyComponent.setColumns(value);
    return this;
  }

  setGutter(value: any): this {
    this.lazyComponent.setGutter(value);
    return this;
  }
}

class GridRowModifier extends LazyArkGridRowComponent implements AttributeModifier<GridRowAttribute> {
  constructor(nativePtr: KNode, classType: ModifierType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
    this.setMap();
  }

  applyNormalAttribute(instance: GridRowAttribute): void {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier<GridRowAttribute, LazyArkGridRowComponent, ArkComponent>(instance, this);
  }
}