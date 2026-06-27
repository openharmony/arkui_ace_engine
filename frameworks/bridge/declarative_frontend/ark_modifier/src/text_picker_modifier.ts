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

class LazyArkTextPickerComponent extends ArkComponent {
  static module: TextPickerComponentModule | undefined = undefined;
  constructor(nativePtr: KNode, classType: ModifierType) {
   super(nativePtr, classType);
   if (LazyArkTextPickerComponent.module === undefined) {
     LazyArkTextPickerComponent.module = globalThis.requireNapi('arkui.components.arktextpicker');
   }

   this.lazyComponent = LazyArkTextPickerComponent.module.createComponent(nativePtr, classType);
  }

  setMap(): void {
   this.lazyComponent._modifiersWithKeys = this._modifiersWithKeys;
  }

  defaultPickerItemHeight(value: number | string): this {
   this.lazyComponent.defaultPickerItemHeight(value);
   return this;
  }

  canLoop(value: boolean): this {
   this.lazyComponent.canLoop(value);
   return this;
  }

  digitalCrownSensitivity(value: Optional<CrownSensitivity>): this {
   this.lazyComponent.digitalCrownSensitivity(value);
   return this;
  }

  disappearTextStyle(value: PickerTextStyle): this {
   this.lazyComponent.disappearTextStyle(value);
   return this;
  }

  textStyle(value: PickerTextStyle): this {
   this.lazyComponent.textStyle(value);
   return this;
  }

  selectedTextStyle(value: PickerTextStyle): this {
   this.lazyComponent.selectedTextStyle(value);
   return this;
  }

  onAccept(value: (value: string, index: number) => void): this {
   this.lazyComponent.onAccept(value);
   return this;
  }

  onCancel(value: () => void): this {
   this.lazyComponent.onCancel(value);
   return this;
  }

  onChange(value: (value: string | string[], index: number | number[]) => void): this {
   this.lazyComponent.onChange(value);
   return this;
  }

  selectedIndex(value: number | number[]): this {
   this.lazyComponent.selectedIndex(value);
   return this;
  }

  divider(value: DividerOptions | null): this {
   this.lazyComponent.divider(value);
   return this;
  }

  gradientHeight(value: Dimension): this {
   this.lazyComponent.gradientHeight(value);
   return this;
  }

  disableTextStyleAnimation(value: boolean): this {
   this.lazyComponent.disableTextStyleAnimation(value);
   return this;
  }

  defaultTextStyle(value: PickerTextStyle): this {
   this.lazyComponent.defaultTextStyle(value);
   return this;
  }

  enableHapticFeedback(value: boolean): this {
   this.lazyComponent.enableHapticFeedback(value);
   return this;
  }

  selectedBackgroundStyle(value: PickerBackgroundStyle): this {
   this.lazyComponent.selectedBackgroundStyle(value);
   return this;
  }

  onScrollStop(value: (value: string | string[], index: number | number[]) => void): this {
   this.lazyComponent.onScrollStop(value);
   return this;
  }
}

class TextPickerModifier extends LazyArkTextPickerComponent implements AttributeModifier<TextPickerAttribute> {

  constructor(nativePtr: KNode, classType: ModifierType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
    this.setMap();
  }

  applyNormalAttribute(instance: TextPickerAttribute): void {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier<TextPickerAttribute, ArkTextPickerComponent, ArkComponent>(instance, this);
  }
}
