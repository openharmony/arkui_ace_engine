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

class LazyArkCheckboxGroupComponent extends ArkComponent {
  static module: CheckboxGroupComponentModule | undefined = undefined;
  constructor(nativePtr: KNode, classType: ModifierType) {
   super(nativePtr, classType);
   if (LazyArkCheckboxGroupComponent.module === undefined) {
     LazyArkCheckboxGroupComponent.module = globalThis.requireNapi('arkui.components.arkcheckboxgroup');
   }

   this.lazyComponent = LazyArkCheckboxGroupComponent.module.createComponent(nativePtr, classType);
  }

  setMap(): void {
   this.lazyComponent._modifiersWithKeys = this._modifiersWithKeys;
  }

  allowChildCount(): number {
   return 0;
  }

  initialize(value: CheckboxGroupOptions): this {
   this.lazyComponent.initialize(value);
   return this;
  }

  selectAll(value: boolean): this {
   this.lazyComponent.selectAll(value);
   return this;
  }

  selectedColor(value: ResourceColor): this {
   this.lazyComponent.selectedColor(value);
   return this;
  }

  unselectedColor(value: ResourceColor): this {
  this.lazyComponent.unselectedColor(value);
   return this;
  }

  mark(value: MarkStyle): this {
   this.lazyComponent.mark(value);
   return this;
  }

  onChange(value: OnCheckboxGroupChangeCallback): this {
   this.lazyComponent.onChange(value);
   return this;
  }

  size(value: SizeOptions): this {
   this.lazyComponent.size(value);
   return this;
  }

  width(value: Length): this {
   this.lazyComponent.width(value);
   return this;
  }

  height(value: Length): this {
   this.lazyComponent.height(value);
   return this;
  }

  checkboxShape(value: CheckBoxShape): this {
   this.lazyComponent.checkboxShape(value);
   return this;
  }
}
class CheckboxGroupModifier extends LazyArkCheckboxGroupComponent implements AttributeModifier<CheckboxGroupAttribute> {

  constructor(nativePtr: KNode, classType: ModifierType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
    this.setMap();
  }

  applyNormalAttribute(instance: CheckboxGroupAttribute): void {
    ModifierUtils.applySetOnChange(this);
    // @ts-ignore
    ModifierUtils.applyAndMergeModifier<CheckboxGroupAttribute, ArkCheckboxGroupComponent, ArkComponent>(instance, this);
  }
}
