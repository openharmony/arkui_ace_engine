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

/// <reference path='./../../ark_component/src/import.ts' />
type ComponentObj = { component: any }

function loadComponent(): ComponentObj | undefined {
  if (loadComponent.componentObj === undefined && globalThis.__ArkComponent__ !== undefined) {
    class ArkMesh {
      constructor() {
        this.value = undefined;
        this.column = undefined;
        this.row = undefined;
      }
      isEqual(another) {
        return (deepCompareArrays(this.value, another.value) &&
          this.column === another.column &&
          this.row === another.row);
      }
    }
    class ArkShapeComponent extends ArkCommonShapeComponent {
      constructor(nativePtr, classType) {
        super(nativePtr, classType);
      }
      viewPort(value) {
        if (value === null) {
          value = undefined;
        }
        modifierWithKey(this._modifiersWithKeys, ShapeViewPortModifier.identity, ShapeViewPortModifier, value);
        return this;
      }
      mesh(value, column, row) {
        let arkMesh = new ArkMesh();
          arkMesh.value = value;
          arkMesh.column = column;
          arkMesh.row = row;
        modifierWithKey(this._modifiersWithKeys, ShapeMeshModifier.identity, ShapeMeshModifier, arkMesh);
        return this;
      }
      height(value) {
        modifierWithKey(this._modifiersWithKeys, ShapeHeightModifier.identity, ShapeHeightModifier, value);
        return this;
      }
      width(value) {
        modifierWithKey(this._modifiersWithKeys, ShapeWidthModifier.identity, ShapeWidthModifier, value);
        return this;
      }
      initialize(value) {
        if (value[0] !== undefined && value[0] !== null) {
          modifierWithKey(this._modifiersWithKeys, ShapeInitializeModifier.identity,
            ShapeInitializeModifier, value[0]);
        } else {
          modifierWithKey(this._modifiersWithKeys, ShapeInitializeModifier.identity,
            ShapeInitializeModifier, undefined);
        }
        return this;
      }
    }

    class ShapeViewPortModifier extends ModifierWithKey {
      constructor(value) {
        super(value);
      }
      applyPeer(node, reset) {
        if (reset) {
          getUINativeModule().shape.resetShapeViewPort(node);
        }
        else {
          getUINativeModule().shape.setShapeViewPort(node, this.value);
        }
      }
      checkObjectDiff() {
        return !(isBaseOrResourceEqual(this.stageValue.x, this.value.x) &&
        isBaseOrResourceEqual(this.stageValue.y, this.value.y) &&
        isBaseOrResourceEqual(this.stageValue.width, this.value.width) &&
        isBaseOrResourceEqual(this.stageValue.height, this.value.height));
      }
    }
    ShapeViewPortModifier.identity = Symbol('shapeViewPort');
    class ShapeMeshModifier extends ModifierWithKey {
      constructor(value) {
        super(value);
      }
      applyPeer(node, reset) {
        if (reset) {
          getUINativeModule().shape.resetShapeMesh(node);
        }
        else {
          getUINativeModule().shape.setShapeMesh(node, this.value.value, this.value.column, this.value.row);
        }
      }
      checkObjectDiff() {
        return !this.stageValue.isEqual(this.value);
      }
    }
    ShapeMeshModifier.identity = Symbol('shapeMesh');
    class ShapeHeightModifier extends ModifierWithKey {
      constructor(value) {
        super(value);
      }
      applyPeer(node, reset) {
        if (reset) {
          getUINativeModule().common.resetHeight(node);
        }
        else {
          getUINativeModule().common.setHeight(node, this.value);
        }
      }
      checkObjectDiff() {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    ShapeHeightModifier.identity = Symbol('shapeHeight');
    class ShapeWidthModifier extends ModifierWithKey {
      constructor(value) {
        super(value);
      }
      applyPeer(node, reset) {
        if (reset) {
          getUINativeModule().common.resetWidth(node);
        }
        else {
          getUINativeModule().common.setWidth(node, this.value);
        }
      }
      checkObjectDiff() {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    ShapeWidthModifier.identity = Symbol('shapeWidth');
    class ShapeInitializeModifier extends ModifierWithKey {
      constructor(value) {
        super(value);
      }

      applyPeer(node, reset) {
        if (reset) {
          getUINativeModule().shape.resetShapeInitialize(node);
        } else {
          getUINativeModule().shape.setShapeInitialize(node, this.value);
        }
      }
    }
    ShapeInitializeModifier.identity = Symbol('shapeInitialize');

    loadComponent.componentObj = {'component' : ArkShapeComponent };
  }
  return loadComponent.componentObj;
}

class JSShape extends JSContainerBase {
    static create(value: any): void {
        getUINativeModule().shape.create(value);
    }
    static mesh(value: any, column: any, row: any): void {
        getUINativeModule().shape.setShapeMesh(true, value, column, row);
    }
    static viewPort(value: any): void {
        getUINativeModule().shape.setShapeViewPort(true, value);
    }
    static stroke(value: any): void {
        getUINativeModule().commonShape.setStroke(true, value);
    }
    static fill(value: any): void {
        getUINativeModule().commonShape.setFill(true, value);
    }
    static strokeWidth(value: any): void {
        getUINativeModule().commonShape.setStrokeWidth(true, value);
    }
    static strokeOpacity(value: any): void {
        getUINativeModule().commonShape.setStrokeOpacity(true, value);
    }
    static fillOpacity(value: any): void {
        getUINativeModule().commonShape.setFillOpacity(true, value);
    }
    static antiAlias(value: any): void {
        getUINativeModule().commonShape.setAntiAlias(true, value);
    }
    static strokeDashArray(value: any): void {
        getUINativeModule().commonShape.setStrokeDashArray(true, value);
    }
    static strokeDashOffset(value: any): void {
        getUINativeModule().commonShape.setStrokeDashOffset(true, value);
    }
    static strokeLineCap(value: any): void {
        getUINativeModule().commonShape.setStrokeLineCap(true, value);
    }
    static strokeLineJoin(value: any): void {
        getUINativeModule().commonShape.setStrokeLineJoin(true, value);
    }
    static strokeMiterLimit(value: any): void {
        getUINativeModule().commonShape.setStrokeMiterLimit(true, value);
    }
    static width(value: any): void {
        getUINativeModule().commonShape.setWidth(true, value);
    }
    static height(value: any): void {
        getUINativeModule().commonShape.setHeight(true, value);
    }
    static foregroundColor(value: any): void {
        getUINativeModule().commonShape.setForegroundColor(true, value);
    }
    static attributeModifier(modifier: any): void {
        attributeModifierFunc.call(this, modifier, (nativePtr: any) => {
            return createComponent(nativePtr);
        }, (nativePtr: any, classType: any, modifierJS: any) => {
            return new modifierJS.ShapeModifier(nativePtr, classType);
        });
    }

    static onTouch(value: any): void {
        __Common__.onTouch(value);
    }
    static onHover(value: any): void {
        __Common__.onHover(value);
    }
    static onKeyEvent(value: any): void {
        __Common__.onKeyEvent(value);
    }
    static onDeleteEvent(value: any): void {
        __Common__.onDeleteEvent(value);
    }
    static onClick(value: any): void {
        __Common__.onClick(value);
    }
    static onAttach(value: any): void {
        __Common__.onAttach(value);
    }
    static onAppear(value: any): void {
        __Common__.onAppear(value);
    }
    static onDetach(value: any): void {
        __Common__.onDetach(value);
    }
    static onDisAppear(value: any): void {
        __Common__.onDisAppear(value);
    }
    static remoteMessage(value: any): void {
        __Common__.remoteMessage(value);
    }
}

function createComponent(nativePtr: any, classType: any): any {
    loadComponent();
    if (loadComponent.componentObj !== undefined) {
        return new loadComponent.componentObj.component(nativePtr, classType);
    }
    return undefined;
}

function exportComponent(): void {
    globalThis.ArkShapeComponent = (loadComponent as any).componentObj?.component;
}

function exportView(): void {
    globalThis.Shape = JSShape;
}

export default { loadComponent, createComponent, exportComponent, exportView };
