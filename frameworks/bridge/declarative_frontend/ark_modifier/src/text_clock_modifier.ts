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

class LazyArkTextClockComponent extends ArkComponent {
  static module: TextClockComponentModule | undefined = undefined;
  constructor(nativePtr: KNode, classType: ModifierType) {
   super(nativePtr, classType);
   if (LazyArkTextClockComponent.module === undefined) {
     LazyArkTextClockComponent.module = globalThis.requireNapi('arkui.components.arktextclock');
   }

   this.lazyComponent = LazyArkTextClockComponent.module.createComponent(nativePtr, classType);
  }

  setMap(): void {
   this.lazyComponent._modifiersWithKeys = this._modifiersWithKeys;
  }

  value(value: number): this {
   this.lazyComponent.value(value);
   return this;
  }

  format(value: ResourceStr): this {
   this.lazyComponent.format(value);
   return this;
  }

  onDateChange(event: (value: number) => void): this {
   this.lazyComponent.onDateChange(event);
   return this;
  }

  fontColor(value: ResourceColor): this {
   this.lazyComponent.fontColor(value);
   return this;
  }

  fontSize(value: Length): this {
   this.lazyComponent.fontSize(value);
   return this;
  }

  fontStyle(value: FontStyle): this {
   this.lazyComponent.fontStyle(value);
   return this;
  }

  fontWeight(value: number | FontWeight | string): this {
   this.lazyComponent.fontWeight(value);
   return this;
  }

  fontFamily(value: ResourceStr): this {
   this.lazyComponent.fontFamily(value);
   return this;
  }

  textShadow(value: ShadowOptions | Array<ShadowOptions>): this {
   this.lazyComponent.textShadow(value);
   return this;
  }

  fontFeature(value: string): this {
   this.lazyComponent.fontFeature(value);
   return this;
  }

  contentModifier(modifier: ContentModifier<TextClockConfiguration>): this {
   this.lazyComponent.contentModifier(modifier);
   return this;
  }

  dateTimeOptions(dateTimeOptions: DateTimeOptions): this {
   this.lazyComponent.dateTimeOptions(dateTimeOptions);
   return this;
  }
}
class TextClockModifier extends LazyArkTextClockComponent implements AttributeModifier<TextClockAttribute> {

  constructor(nativePtr: KNode, classType: ModifierType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
    this.setMap();
  }

  applyNormalAttribute(instance: TextClockAttribute): void {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier<TextClockAttribute, ArkTextClockComponent, ArkComponent>(instance, this);
  }
}
