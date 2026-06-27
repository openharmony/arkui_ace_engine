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

class LazyArkDatePickerComponent extends ArkComponent {
  static module: DatePickerComponentModule | undefined = undefined;
  constructor(nativePtr: KNode, classType: ModifierType) {
   super(nativePtr, classType);
   if (LazyArkDatePickerComponent.module === undefined) {
     LazyArkDatePickerComponent.module = globalThis.requireNapi('arkui.components.arkdatepicker');
   }

   this.lazyComponent = LazyArkDatePickerComponent.module.createComponent(nativePtr, classType);
  }

  setMap(): void {
   this.lazyComponent._modifiersWithKeys = this._modifiersWithKeys;
  }

  lunar(value: boolean): this {
   this.lazyComponent.lunar(value);
   return this;
  }

  digitalCrownSensitivity(value: CrownSensitivity): this {
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

  onChange(value: (value: DatePickerResult) => void): this {
   this.lazyComponent.onChange(value);
   return this;
  }

  onDateChange(value: Callback<Date>): this {
   this.lazyComponent.onDateChange(value);
   return this;
  }

  backgroundColor(value: ResourceColor): this {
   this.lazyComponent.backgroundColor(value);
   return this;
  }

  enableHapticFeedback(value: boolean): this {
   this.lazyComponent.enableHapticFeedback(value);
   return this;
  }

  canLoop(value: boolean): this {
   this.lazyComponent.canLoop(value);
   return this;
  }
}
class DatePickerModifier extends LazyArkDatePickerComponent implements AttributeModifier<DatePickerAttribute> {

  constructor(nativePtr: KNode, classType: ModifierType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
    this.setMap();
  }

  applyNormalAttribute(instance: DatePickerAttribute): void {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier<DatePickerAttribute, ArkDatePickerComponent, ArkComponent>(instance, this);
  }
}
