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

class LazyArkRadioComponent extends ArkComponent {
  static module: RadioComponentModule | undefined = undefined;
  constructor(nativePtr: KNode, classType: ModifierType) {
   super(nativePtr, classType);
   if (LazyArkRadioComponent.module === undefined) {
     LazyArkRadioComponent.module = globalThis.requireNapi('arkui.components.arkradio');
   }

   this.lazyComponent = LazyArkRadioComponent.module.createComponent(nativePtr, classType);
  }

  setMap(): void {
   this.lazyComponent._modifiersWithKeys = this._modifiersWithKeys;
  }

  allowChildCount(): number {
   return 0;
  }

  initialize(value: RadioOptions): this {
   this.lazyComponent.initialize(value);
   return this;
  }

  checked(value: boolean): this {
   this.lazyComponent.checked(value);
   return this;
  }

  onChange(callback: (isChecked: boolean) => void): this {
   this.lazyComponent.onChange(callback);
   return this;
  }

  radioStyle(value: RadioStyle): this {
   this.lazyComponent.radioStyle(value);
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

  size(value: SizeOptions): this {
   this.lazyComponent.size(value);
   return this;
  }

  hoverEffect(value: HoverEffect): this {
   this.lazyComponent.hoverEffect(value);
   return this;
  }

  padding(value: Padding | Length): this {
   this.lazyComponent.padding(value);
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

  contentModifier(value: ContentModifier<RadioConfiguration>): this {
   this.lazyComponent.contentModifier(value);
   return this;
  }
}
class RadioModifier extends LazyArkRadioComponent implements AttributeModifier<RadioAttribute> {

  constructor(nativePtr: KNode, classType: ModifierType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
    this.setMap();
  }

  applyNormalAttribute(instance: RadioAttribute): void {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier<RadioAttribute, ArkRadioComponent, ArkComponent>(instance, this);
  }
}
