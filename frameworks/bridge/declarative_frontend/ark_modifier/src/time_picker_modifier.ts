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

class LazyArkTimePickerComponent extends ArkComponent {
  static module: TimePickerComponentModule | undefined = undefined;
  constructor(nativePtr: KNode, classType: ModifierType) {
   super(nativePtr, classType);
   if (LazyArkTimePickerComponent.module === undefined) {
     LazyArkTimePickerComponent.module = globalThis.requireNapi('arkui.components.arktimepicker');
   }

   this.lazyComponent = LazyArkTimePickerComponent.module.createComponent(nativePtr, classType);
  }

  setMap(): void {
   this.lazyComponent._modifiersWithKeys = this._modifiersWithKeys;
  }

  loop(value: boolean): this {
   this.lazyComponent.loop(value);
   return this;
  }

  digitalCrownSensitivity(value: CrownSensitivity): this {
   this.lazyComponent.digitalCrownSensitivity(value);
   return this;
  }

  useMilitaryTime(value: boolean): this {
   this.lazyComponent.useMilitaryTime(value);
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

  enableCascade(value: boolean): this {
   this.lazyComponent.enableCascade(value);
   return this;
  }

  onChange(value: (value: TimePickerResult) => void): this {
   this.lazyComponent.onChange(value);
   return this;
  }

  dateTimeOptions(value: DateTimeOptions): this {
   this.lazyComponent.dateTimeOptions(value);
   return this;
  }

  enableHapticFeedback(value: boolean): this {
   this.lazyComponent.enableHapticFeedback(value);
   return this;
  }
}
class TimePickerModifier extends LazyArkTimePickerComponent implements AttributeModifier<TimePickerAttribute> {

  constructor(nativePtr: KNode, classType: ModifierType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
    this.setMap();
  }

  applyNormalAttribute(instance: TimePickerAttribute): void {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier<TimePickerAttribute, ArkTimePickerComponent, ArkComponent>(instance, this);
  }
}
