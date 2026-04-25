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

class LazyArkDataPanelComponent extends ArkComponent {
  static module: DataPanelComponentModule | undefined = undefined;

  constructor(nativePtr: KNode, classType: ModifierType) {
    super(nativePtr, classType);
    if (LazyArkDataPanelComponent.module === undefined) {
      LazyArkDataPanelComponent.module = globalThis.requireNapi('arkui.components.arkdatapanel');
    }

    this.lazyComponent = LazyArkDataPanelComponent.module.createComponent(nativePtr, classType);
  }

  setMap(): void {
    this.lazyComponent._modifiersWithKeys = this._modifiersWithKeys;
  }

  closeEffect(value: boolean): this {
    this.lazyComponent.closeEffect(value);
    return this;
  }

  valueColors(value: Array<ResourceColor | LinearGradient>): this {
    this.lazyComponent.valueColors(value);
    return this;
  }

  trackBackgroundColor(value: ResourceColor): this {
    this.lazyComponent.trackBackgroundColor(value);
    return this;
  }

  strokeWidth(value: Length): this {
    this.lazyComponent.strokeWidth(value);
    return this;
  }

  trackShadow(value: DataPanelShadowOptions): this {
    this.lazyComponent.trackShadow(value);
    return this;
  }

  contentModifier(value: ContentModifier<DataPanelConfiguration>): this {
    this.lazyComponent.contentModifier(value);
    return this;
  }
}
  class DataPanelModifier extends LazyArkDataPanelComponent implements AttributeModifier<DataPanelAttribute> {

  constructor(nativePtr: KNode, classType: ModifierType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
    this.setMap();
  }

  applyNormalAttribute(instance: DataPanelAttribute): void {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier<DataPanelAttribute, ArkDataPanelComponent, ArkComponent>(instance, this);
  }
}
