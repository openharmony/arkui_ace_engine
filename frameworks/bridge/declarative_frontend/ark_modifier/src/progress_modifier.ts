/*
 * Copyright (c) 2024-2026 Huawei Device Co., Ltd.
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

class LazyArkProgressComponent extends ArkComponent {
  static module: ProgressComponentModule | undefined = undefined;
  constructor(nativePtr: KNode, classType: ModifierType) {
   super(nativePtr, classType);
   if (LazyArkProgressComponent.module === undefined) {
     LazyArkProgressComponent.module = globalThis.requireNapi('arkui.components.arkprogress');
   }

   this.lazyComponent = LazyArkProgressComponent.module.createComponent(nativePtr, classType);
  }

  setMap(): void {
   this.lazyComponent._modifiersWithKeys = this._modifiersWithKeys;
  }

  value(value: number): LazyArkProgressComponent {
   this.lazyComponent.value(value);
   return this;
  }

  color(value: ResourceColor): LazyArkProgressComponent {
   this.lazyComponent.color(value);
   return this;
  }

  style(value: ProgressStyle): LazyArkProgressComponent {
   this.lazyComponent.style(value);
   return this;
  }

  backgroundColor(value: ResourceColor): this {
    this.lazyComponent.backgroundColor(value);
    return this;
  }

  contentModifier(value: ContentModifier<ProgressConfiguration>): this {
    this.lazyComponent.contentModifier(value);
    return this;
  }

  privacySensitive(value: Optional<boolean>): this {
    this.lazyComponent.privacySensitive(value);
    return this;
  }

  initialize(value: Object[]): this {
    this.lazyComponent.initialize(value);
    return this;
  }
}

class ProgressModifier extends LazyArkProgressComponent implements AttributeModifier<ProgressAttribute> {
  constructor(nativePtr: KNode, classType: ModifierType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
    this.setMap();
  }

  applyNormalAttribute(instance: ProgressAttribute): void {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier<ProgressAttribute, ArkProgressComponent, ArkComponent>(instance, this);
  }
}
