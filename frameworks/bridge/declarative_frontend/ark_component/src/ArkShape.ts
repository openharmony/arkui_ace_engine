/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

/// <reference path='./import.ts' />
/// <reference path="./ArkCommonShape.ts" />
class ShapeViewPortModifier extends ModifierWithKey<{
  x?: Length | undefined;
  y?: Length | undefined;
  width?: Length | undefined;
  height?: Length | undefined;
}> {
  constructor(value: {
    x?: Length | undefined;
    y?: Length | undefined;
    width?: Length | undefined;
    height?: Length | undefined;
  }) {
    super(value);
  }
  static identity: Symbol = Symbol('shapeViewPort');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().shape.resetShapeViewPort(node);
    } else {
      getUINativeModule().shape.setShapeViewPort(node, this.value.x, this.value.y, this.value.width, this.value.height);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
class ShapeMeshModifier extends ModifierWithKey<ArkMesh> {
  constructor(value: ArkMesh) {
    super(value);
  }
  static identity: Symbol = Symbol('shapeMesh');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().shape.resetShapeMesh(node);
    } else {
      getUINativeModule().shape.setShapeMesh(node, this.value.value, this.value.column, this.value.row);
    }
  }
  checkObjectDiff(): boolean {
    return !(this.stageValue as ArkMesh).isEqual(this.value as ArkMesh);
  }
}
class ShapeHeightModifier extends ModifierWithKey<Length> {
  constructor(value: Length) {
    super(value);
  }
  static identity: Symbol = Symbol('shapeHeight');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetHeight(node);
    } else {
      getUINativeModule().common.setHeight(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
class ShapeWidthModifier extends ModifierWithKey<Length> {
  constructor(value: Length) {
    super(value);
  }
  static identity: Symbol = Symbol('shapeWidth');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetWidth(node);
    } else {
      getUINativeModule().common.setWidth(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
class ShapeInitializeModifier extends ModifierWithKey<PixelMap> {
  constructor(value: PixelMap) {
    super(value);
  }
  static identity: Symbol = Symbol('shapeInitialize');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().shape.resetShapeInitialize(node);
    } else {
      getUINativeModule().shape.setShapeInitialize(node, this.value);
    }
  }
}
class ArkShapeComponent extends ArkCommonShapeComponent implements ShapeAttribute {
  constructor(nativePtr: KNode, classType?: ModifierType) {
    super(nativePtr, classType);
  }
  viewPort(value: {
    x?: Length | undefined;
    y?: Length | undefined;
    width?: Length | undefined;
    height?: Length | undefined;
  }): this {
    if (value === null) {
      value = undefined;
    }
    modifierWithKey(this._modifiersWithKeys, ShapeViewPortModifier.identity, ShapeViewPortModifier, value);
    return this;
  }
  mesh(value: Array<any> | undefined, column: number | undefined, row: number | undefined): this {
    let arkMesh = new ArkMesh();
    if (value !== null && column !== null && row !== null) {
      arkMesh.value = value;
      arkMesh.column = column;
      arkMesh.row = row;
    }
    modifierWithKey(this._modifiersWithKeys, ShapeMeshModifier.identity, ShapeMeshModifier, arkMesh);
    return this;
  }
  height(value: Length): this {
    modifierWithKey(this._modifiersWithKeys, ShapeHeightModifier.identity, ShapeHeightModifier, value);
    return this;
  }
  width(value: Length): this {
    modifierWithKey(this._modifiersWithKeys, ShapeWidthModifier.identity, ShapeWidthModifier, value);
    return this;
  }
  initialize(value: Object[]): this {
    if (!isUndefined(value[0]) && !isNull(value[0])) {
      modifierWithKey(this._modifiersWithKeys, ShapeInitializeModifier.identity,
        ShapeInitializeModifier, value[0] as PixelMap);
    } else {
      modifierWithKey(this._modifiersWithKeys, ShapeInitializeModifier.identity,
        ShapeInitializeModifier, undefined);
    }
    return this;
  }
}

// @ts-ignore
globalThis.Shape.attributeModifier = function (modifier: ArkComponent): void {
  attributeModifierFunc.call(this, modifier, (nativePtr: KNode) => {
    return new ArkShapeComponent(nativePtr);
  }, (nativePtr: KNode, classType: ModifierType, modifierJS: ModifierJS) => {
    return new modifierJS.ShapeModifier(nativePtr, classType);
  });
};
