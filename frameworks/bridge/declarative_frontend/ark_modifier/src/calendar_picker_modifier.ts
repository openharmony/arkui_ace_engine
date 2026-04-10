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

class LazyArkCalendarPickerComponent extends ArkComponent {
  static module: CalendarPickerComponentModule | undefined = undefined;

  constructor(nativePtr: KNode, classType: ModifierType) {
    super(nativePtr, classType);
    if (LazyArkCalendarPickerComponent.module === undefined) {
      LazyArkCalendarPickerComponent.module = globalThis.requireNapi('arkui.components.arkCalendarpicker');
    }

    this.lazyComponent = LazyArkCalendarPickerComponent.module.createComponent(nativePtr, classType);
  }

  setMap(): void {
    this.lazyComponent._modifiersWithKeys = this._modifiersWithKeys;
  }

  value(value: Date): this {
    this.lazyComponent.value(value);
    return this;
  }

  edgeAlign(alignType: CalendarAlign, offset?: Offset): this {
    this.lazyComponent.edgeAlign(alignType, offset);
    return this;
  }

  textStyle(value: PickerTextStyle): this {
    this.lazyComponent.textStyle(value);
    return this;
  }

  onChange(value: Callback<Date>): this {
    this.lazyComponent.onChange(value);
    return this;
  }

  padding(value: Padding | Length | LocalizedPadding): this {
    this.lazyComponent.padding(value);
    return this;
  }

  border(value: BorderOptions): this {
    this.lazyComponent.border(value);
    return this;
  }

  height(value: Length): this {
    this.lazyComponent.height(value);
    return this;
  }

  borderRadius(value: Length | BorderRadiuses | LocalizedBorderRadiuses): this {
    this.lazyComponent.borderRadius(value);
    return this;
  }

  borderColor(value: ResourceColor | EdgeColors | LocalizedEdgeColors): this {
    this.lazyComponent.borderColor(value);
    return this;
  }

  markToday(value: boolean): this {
    this.lazyComponent.markToday(value);
    return this;
  }
}
class CalendarPickerModifier extends LazyArkCalendarPickerComponent implements AttributeModifier<CalendarPickerAttribute> {

  constructor(nativePtr: KNode, classType: ModifierType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
    this.setMap();
  }

  applyNormalAttribute(instance: CalendarPickerAttribute): void {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier<CalendarPickerAttribute, ArkCalendarPickerComponent, ArkComponent>(instance, this);
  }
}
