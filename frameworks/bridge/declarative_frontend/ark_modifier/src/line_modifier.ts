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

class LazyArkLineComponent extends LazyArkCommonShapeComponent {
  static module: LineComponentModule | undefined = undefined;
  constructor(nativePtr: KNode, classType: ModifierType) {
    super(nativePtr, classType);
    if (LazyArkLineComponent.module === undefined) {
      LazyArkLineComponent.module = globalThis.requireNapi('arkui.components.arkline');
    }
    this.lazyComponent = LazyArkLineComponent.module.createComponent(nativePtr, classType);
  }

  startPoint(value:	Array<any>): this {
    this.lazyComponent.startPoint(value);
    return this;
  }

  endPoint(value: Array<any>): this {
    this.lazyComponent.endPoint(value);
    return this;
  }

  setMap(): void {
    this.lazyComponent._modifiersWithKeys = this._modifiersWithKeys;
  }
}

class LineModifier extends LazyArkLineComponent implements AttributeModifier<LineAttribute> {
  constructor(nativePtr: KNode, classType: ModifierType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
    this.setMap();
  }

  applyNormalAttribute(instance: LineAttribute): void {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier<LineAttribute, ArkLineComponent, ArkComponent>(instance, this);
  }
}
