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

class LazyArkCheckboxComponent extends ArkComponent {
  static module: CheckboxComponentModule | undefined = undefined;
  constructor(nativePtr: KNode, classType: ModifierType) {
   super(nativePtr, classType);
   if (LazyArkCheckboxComponent.module === undefined) {
     LazyArkCheckboxComponent.module = globalThis.requireNapi('arkui.components.arkcheckbox');
   }

   this.lazyComponent = LazyArkCheckboxComponent.module.createComponent(nativePtr, classType);
  }

  setMap(): void {
   this.lazyComponent._modifiersWithKeys = this._modifiersWithKeys;
  }

  allowChildCount(): number {
   return 0;
  }

  initialize(value: CheckboxOptions): this {
   this.lazyComponent.initialize(value);
   return this;
  }

  shape(value: CheckBoxShape): this {
   this.lazyComponent.shape(value);
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

  select(value: boolean): this {
   this.lazyComponent.select(value);
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

  padding(value: Padding | Length): this {
   this.lazyComponent.padding(value);
   return this;
  }

  size(value: SizeOptions): this {
   this.lazyComponent.size(value);
   return this;
  }

  responseRegion(value: Array<Rectangle> | Rectangle): this {
   this.lazyComponent.responseRegion(value);
   return this;
  }

  margin(value: Margin | Length): this {
   this.lazyComponent.margin(value);
   return this;
  }

  contentModifier(value: ContentModifier<CheckBoxConfiguration>): this {
   this.lazyComponent.contentModifier(value);
   return this;
  }

  onChange(callback: OnCheckboxChangeCallback): this {
   this.lazyComponent.onChange(callback);
   return this;
  }
}
class CheckboxModifier extends LazyArkCheckboxComponent implements AttributeModifier<CheckboxAttribute> {

  constructor(nativePtr: KNode, classType: ModifierType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
    this.setMap();
  }

  applyNormalAttribute(instance: CheckboxAttribute): void {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier<CheckboxAttribute, ArkCheckboxComponent, ArkComponent>(instance, this);
  }
}
