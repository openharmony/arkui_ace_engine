/*
 * Copyright (c) 2025-2026 Huawei Device Co., Ltd.
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

class LazyArkLazyVGridLayoutComponent extends ArkScrollable {
  static module: LazyVGridLayoutComponentModule | undefined = undefined;

  constructor(nativePtr: KNode, classType: ModifierType) {
    super(nativePtr, classType);
    if (LazyArkLazyVGridLayoutComponent.module === undefined) {
      LazyArkLazyVGridLayoutComponent.module = globalThis.requireNapi('arkui.components.arklazygridlayout');
    }
    this.lazyComponent = LazyArkLazyVGridLayoutComponent.module.createComponent(nativePtr, classType);
  }

  setMap(): void {
    this.lazyComponent._modifiersWithKeys = this._modifiersWithKeys;
  }

  columnsTemplate(value: string): this {
    this.lazyComponent.columnsTemplate(value);
    return this;
  }
  columnsGap(value: LengthMetrics): this {
    this.lazyComponent.columnsGap(value);
    return this;
  }
  rowsGap(value: LengthMetrics): this {
    this.lazyComponent.rowsGap(value);
    return this;
  }
  sticky(value: StickyStyle): this {
    this.lazyComponent.sticky(value);
    return this;
  }
  header(value: CustomBuilder | ComponentContent | undefined): this {
    this.lazyComponent.header(value);
    return this;
  }
  footer(value: CustomBuilder | ComponentContent | undefined): this {
    this.lazyComponent.footer(value);
    return this;
  }
  onVisibleIndexesChange(callback: ((start: number, end: number) => void) | undefined): this {
    this.lazyComponent.onVisibleIndexesChange(callback);
    return this;
  }
}

class LazyVGridLayoutModifier extends LazyArkLazyVGridLayoutComponent implements AttributeModifier<LazyVGridLayoutAttribute> {
  constructor(nativePtr: KNode, classType: ModifierType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
    this.setMap();
  }

  applyNormalAttribute(instance: LazyVGridLayoutAttribute): void {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier<LazyVGridLayoutAttribute, ArkLazyVGridLayoutComponent, ArkComponent>(instance, this);
  }
}
