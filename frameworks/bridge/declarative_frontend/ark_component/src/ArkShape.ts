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
  x?: string | number |
  undefined; y?: string | number | undefined; width?: string | number |
  undefined; height?: string | number | undefined;
}> {
  constructor(value: {
    x?: string | number | undefined; y?: string |
    number | undefined; width?: string | number | undefined;
    height?: string | number | undefined;
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
    return !(this.stageValue.x === this.value.x && this.stageValue.y === this.value.y &&
      this.stageValue.width === this.value.width && this.stageValue.height === this.value.height);
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
class ArkShapeComponent extends ArkCommonShapeComponent implements ShapeAttribute {
  constructor(nativePtr: KNode) {
    super(nativePtr);
  }
  viewPort(value: {
    x?: string | number | undefined;
    y?: string | number | undefined; width?: string | number | undefined;
    height?: string | number | undefined;
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
}

// @ts-ignore
globalThis.Shape.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkShapeComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};
