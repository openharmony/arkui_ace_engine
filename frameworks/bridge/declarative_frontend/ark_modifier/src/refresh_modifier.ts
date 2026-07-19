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

class LazyArkRefreshComponent extends ArkComponent {
  static module: RefreshComponentModule | undefined = undefined;

  constructor(nativePtr: KNode, classType: ModifierType) {
    super(nativePtr, classType);
    if (LazyArkRefreshComponent.module === undefined) {
      LazyArkRefreshComponent.module = globalThis.requireNapi('arkui.components.arkrefresh');
    }

    this.lazyComponent = LazyArkRefreshComponent.module.createComponent(nativePtr, classType);
  }

  setMap(): void {
    this.lazyComponent._modifiersWithKeys = this._modifiersWithKeys;
  }

  allowChildCount(): number {
    return 1;
  }

  initialize(value: any): this {
    this.lazyComponent.initialize(value);
    return this;
  }

  onStateChange(value: (state: number) => void): this {
    this.lazyComponent.onStateChange(value);
    return this;
  }

  onRefreshing(value: () => void): this {
    this.lazyComponent.onRefreshing(value);
    return this;
  }

  refreshOffset(value: number | Resource): this {
    this.lazyComponent.refreshOffset(value);
    return this;
  }

  pullToRefresh(value: boolean): this {
    this.lazyComponent.pullToRefresh(value);
    return this;
  }

  pullUpToCancelRefresh(value: boolean): this {
    this.lazyComponent.pullUpToCancelRefresh(value);
    return this;
  }

  pullDownRatio(value: number): this {
    this.lazyComponent.pullDownRatio(value);
    return this;
  }

  onOffsetChange(value: Callback<number>): this {
    this.lazyComponent.onOffsetChange(value);
    return this;
  }

  maxPullDownDistance(value: number | Resource): this {
    this.lazyComponent.maxPullDownDistance(value);
    return this;
  }
}

class RefreshModifier extends LazyArkRefreshComponent implements AttributeModifier<RefreshAttribute> {

  constructor(nativePtr: KNode, classType: ModifierType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
    this.setMap();
  }

  applyNormalAttribute(instance: RefreshAttribute): void {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier<RefreshAttribute, ArkRefreshComponent, ArkComponent>(instance, this);
  }
}
