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

class LazyArkGridItemComponent extends ArkComponent {
  static module: GridItemComponentModule | undefined = undefined;

  constructor(nativePtr: KNode, classType: ModifierType) {
   super(nativePtr, classType);
   if (LazyArkGridItemComponent.module === undefined) {
     LazyArkGridItemComponent.module = globalThis.requireNapi('arkui.components.arkgriditem');
   }

   this.lazyComponent = LazyArkGridItemComponent.module.createComponent(nativePtr, classType);
  }

  setMap(): void {
   this.lazyComponent._modifiersWithKeys = this._modifiersWithKeys;
  }

  initialize(value: Object[]): this {
    this.lazyComponent.initialize(value);
    return this;
  }

  rowStart(value: number): this {
    this.lazyComponent.rowStart(value);
    return this;
  }
  rowEnd(value: number): this {
    this.lazyComponent.rowEnd(value);
    return this;
  }
  columnStart(value: number): this {
    this.lazyComponent.columnStart(value);
    return this;
  }
  columnEnd(value: number): this {
    this.lazyComponent.columnEnd(value);
    return this;
  }
  forceRebuild(value: boolean): this {
    this.lazyComponent.forceRebuild(value);
    return this;
  }
  selectable(value: boolean): this {
    this.lazyComponent.selectable(value);
    return this;
  }
  selected(value: boolean): this {
    this.lazyComponent.selected(value);
    return this;
  }
  onSelect(event: (isSelected: boolean) => void): this {
    this.lazyComponent.onSelect(event);
    return this;
  }
}
class GridItemModifier extends LazyArkGridItemComponent implements AttributeModifier<GridItemAttribute> {

  constructor(nativePtr: KNode, classType: ModifierType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
    this.setMap();
  }

  applyNormalAttribute(instance: GridItemAttribute): void {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier<GridItemAttribute, ArkGridItemComponent, ArkComponent>(instance, this);
  }
}
