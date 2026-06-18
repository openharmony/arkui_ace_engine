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

class LazyArkPolylineComponent extends LazyArkCommonShapeComponent {
  static module: PolylineComponentModule | undefined = undefined; 
  constructor(nativePtr: KNode, classType: ModifierType) {
    super(nativePtr, classType);
    if (LazyArkPolylineComponent.module === undefined) {
      LazyArkPolylineComponent.module = globalThis.requireNapi('arkui.components.arkpolyline');
    }
    this.lazyComponent = LazyArkPolylineComponent.module.createComponent(nativePtr, classType);
  }

  points(value: Array<any>): this {
    this.lazyComponent.points(value);
    return this;
  }

  setMap(): void {
    this.lazyComponent._modifiersWithKeys = this._modifiersWithKeys;
  }
}

class PolylineModifier extends LazyArkPolylineComponent implements AttributeModifier<PolylineAttribute> {

  constructor(nativePtr: KNode, classType: ModifierType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
    this.setMap();
  }

  applyNormalAttribute(instance: PolylineAttribute): void {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier<PolylineAttribute, ArkPolylineComponent, ArkComponent>(instance, this);
  }
}
