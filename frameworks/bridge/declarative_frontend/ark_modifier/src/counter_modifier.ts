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

class LazyArkCounterComponent extends ArkComponent {
  static module: CounterComponentModule | undefined = undefined;

  constructor(nativePtr: KNode, classType: ModifierType) {
    super(nativePtr, classType);
    if (LazyArkCounterComponent.module === undefined) {
      LazyArkCounterComponent.module = globalThis.requireNapi('arkui.components.arkcounter');
    }

    this.lazyComponent = LazyArkCounterComponent.module.createComponent(nativePtr, classType);
  }

  setMap(): void {
    this.lazyComponent._modifiersWithKeys = this._modifiersWithKeys;
  }

  onInc(event: VoidCallback): this {
    this.lazyComponent.onInc(event);
    return this;
  }

  onDec(event: VoidCallback): this {
    this.lazyComponent.onDec(event);
    return this;
  }

  enableDec(value: boolean): this {
    this.lazyComponent.enableDec(value);
    return this;
  }

  enableInc(value: boolean): this {
    this.lazyComponent.enableInc(value);
    return this;
  }

  backgroundColor(value: ResourceColor): this {
    this.lazyComponent.backgroundColor(value);
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
}

class CounterModifier extends LazyArkCounterComponent implements AttributeModifier<CounterAttribute> {

  constructor(nativePtr: KNode, classType: ModifierType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
    this.setMap();
  }

  applyNormalAttribute(instance: CounterAttribute): void {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier<CounterAttribute, ArkCounterComponent, ArkComponent>(instance, this);
  }
}
