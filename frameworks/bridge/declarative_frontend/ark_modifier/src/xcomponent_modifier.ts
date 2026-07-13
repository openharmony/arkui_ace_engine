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

class LazyArkXComponentComponent extends ArkComponent {
  static module: XComponentComponentModule | undefined = undefined;
  constructor(nativePtr: KNode, classType: ModifierType) {
    super(nativePtr, classType);
    if (LazyArkXComponentComponent.module === undefined) {
      LazyArkXComponentComponent.module = globalThis.requireNapi('arkui.components.arkxcomponent');
    }
    this.lazyComponent = LazyArkXComponentComponent.module.createComponent(nativePtr, classType);
  }

  setMap(): void {
    this.lazyComponent._modifiersWithKeys = this._modifiersWithKeys;
  }

  initialize(value: object): LazyArkXComponentComponent {
    this.lazyComponent.initialize(value);
    return this;
  }

  backgroundColor(value: ResourceColor): this {
    this.lazyComponent.backgroundColor(value);
    return this;
  }

  opacity(value: number | Resource): LazyArkXComponentComponent {
    this.lazyComponent.opacity(value);
    return this;
  }

  enableAnalyzer(enable: boolean): LazyArkXComponentComponent {
    this.lazyComponent.enableAnalyzer(enable);
    return this;
  }

  enableSecure(isSecure: boolean): LazyArkXComponentComponent {
    this.lazyComponent.enableSecure(isSecure);
    return this;
  }

  hdrBrightness(brightness: number, type?: number): LazyArkXComponentComponent {
    this.lazyComponent.hdrBrightness(brightness, type);
    return this;
  }

  renderFit(fitMode: number): LazyArkXComponentComponent {
    this.lazyComponent.renderFit(fitMode);
    return this;
  }

  enableTransparentLayer(enable: boolean): LazyArkXComponentComponent {
    this.lazyComponent.enableTransparentLayer(enable);
    return this;
  }

  onLoad(callback: Callback<object>): LazyArkXComponentComponent {
    this.lazyComponent.onLoad(callback);
    return this;
  }

  onDestroy(event: Callback<void>): LazyArkXComponentComponent {
    this.lazyComponent.onDestroy(event);
    return this;
  }
}

class XComponentModifier extends LazyArkXComponentComponent implements AttributeModifier<XComponentAttribute> {

  constructor(nativePtr: KNode, classType: ModifierType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
    this.setMap();
  }

  applyNormalAttribute(instance: XComponentAttribute): void {
    ModifierUtils.applySetOnChange(this);
    // @ts-ignore
    ModifierUtils.applyAndMergeModifier<XComponentAttribute, ArkXComponentComponent, ArkComponent>(instance, this);
  }
}
