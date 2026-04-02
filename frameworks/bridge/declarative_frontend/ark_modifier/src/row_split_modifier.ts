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

class LazyArkRowSplitComponent extends ArkComponent {
  static module: RowSplitComponentModule | undefined = undefined;
  constructor(nativePtr: KNode, classType: ModifierType) {
   super(nativePtr, classType);
   if (LazyArkRowSplitComponent.module === undefined) {
     LazyArkRowSplitComponent.module = globalThis.requireNapi('arkui.components.arkrowsplit');
   }

   this.lazyComponent = LazyArkRowSplitComponent.module.createComponent(nativePtr, classType);
  }

  setMap(): void {
   this.lazyComponent._modifiersWithKeys = this._modifiersWithKeys;
  }

  resizeable(value: boolean): LazyArkRowSplitComponent {
   this.lazyComponent.resizeable(value);
   return this;
  }

  clip(value: boolean): this {
    this.lazyComponent.clip(value);
    return this;
  }
}

class RowSplitModifier extends LazyArkRowSplitComponent implements AttributeModifier<RowSplitAttribute> {

  constructor(nativePtr: KNode, classType: ModifierType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
    this.setMap();
  }

  applyNormalAttribute(instance: RowSplitAttribute): void {
    ModifierUtils.applySetOnChange(this);
    // @ts-ignore
    ModifierUtils.applyAndMergeModifier<RowSplitAttribute, ArkRowSplitComponent, ArkComponent>(instance, this);
  }
}
