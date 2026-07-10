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

class LazyArkShapeComponent extends LazyArkCommonShapeComponent {
  static module: ShapeComponentModule | undefined = undefined;
  constructor(nativePtr: KNode, classType: ModifierType) {
    super(nativePtr, classType);
    if (LazyArkShapeComponent.module === undefined) {
      LazyArkShapeComponent.module = globalThis.requireNapi('arkui.components.arkshape');
    }
    this.lazyComponent = LazyArkShapeComponent.module.createComponent(nativePtr, classType);
  }

  viewPort(value: ViewportRect): this {
    this.lazyComponent.viewPort(value);
    return this;
  }

  mesh(value: Array<any>, column: number, row: number): this {
    this.lazyComponent.mesh(value, column, row);
    return this;
  }

  setMap(): void {
    this.lazyComponent._modifiersWithKeys = this._modifiersWithKeys;
  }
}

class ShapeModifier extends LazyArkShapeComponent implements AttributeModifier<ShapeAttribute> {

  constructor(nativePtr: KNode, classType: ModifierType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
    this.setMap();
  }

  applyNormalAttribute(instance: ShapeAttribute): void {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier<ShapeAttribute, ArkShapeComponent, ArkComponent>(instance, this);
  }
}
