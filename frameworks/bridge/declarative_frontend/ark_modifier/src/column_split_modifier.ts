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

class LazyArkColumnSplitComponent extends ArkComponent {
  static module: ColumnSplitComponentModule | undefined = undefined;

  constructor(nativePtr: KNode, classType: ModifierType) {
    super(nativePtr, classType);
    if (LazyArkColumnSplitComponent.module === undefined) {
      LazyArkColumnSplitComponent.module = globalThis.requireNapi('arkui.components.arkcolumnsplit');
    }

    this.lazyComponent = LazyArkColumnSplitComponent.module.createComponent(nativePtr, classType);
  }

  setMap(): void {
    this.lazyComponent._modifiersWithKeys = this._modifiersWithKeys;
  }

  resizeable(value: boolean): this {
    this.lazyComponent.resizeable(value);
    return this;
  }

  divider(value: ColumnSplitDividerStyle | null): this {
    this.lazyComponent.divider(value);
    return this;
  }

  clip(value: boolean | CircleAttribute | EllipseAttribute | PathAttribute | RectAttribute): this {
    this.lazyComponent.clip(value);
    return this;
  }
}

class ColumnSplitModifier extends LazyArkColumnSplitComponent implements AttributeModifier<ColumnSplitAttribute> {

  constructor(nativePtr: KNode, classType: ModifierType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
    this.setMap();
  }

  applyNormalAttribute(instance: ColumnSplitAttribute): void {
    ModifierUtils.applySetOnChange(this);
    // @ts-ignore
    ModifierUtils.applyAndMergeModifier<ColumnSplitAttribute, ArkColumnSplitComponent, ArkComponent>(instance, this);
  }
}
