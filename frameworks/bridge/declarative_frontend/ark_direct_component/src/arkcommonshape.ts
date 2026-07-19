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
    class ArkCommonShapeComponent extends globalThis.__ArkComponent__ {
        constructor(nativePtr: any, classType: any) {
            super(nativePtr, classType);
        }
        viewPort(value: any): this {
            throw new Error('Method not implemented.');
        }
        stroke(value: any): this {
            modifierWithKey(this._modifiersWithKeys, StrokeModifier.identity, StrokeModifier, value);
            return this;
        }
        fill(value: any): this {
            modifierWithKey(this._modifiersWithKeys, FillModifier.identity, FillModifier, value);
            return this;
        }
        strokeDashOffset(value: any): this {
            modifierWithKey(this._modifiersWithKeys, StrokeDashOffsetModifier.identity,
                StrokeDashOffsetModifier, value);
            return this;
        }
        strokeLineCap(value: any): this {
            modifierWithKey(this._modifiersWithKeys, StrokeLineCapModifier.identity, StrokeLineCapModifier, value);
            return this;
        }
        strokeLineJoin(value: any): this {
            modifierWithKey(this._modifiersWithKeys, StrokeLineJoinModifier.identity, StrokeLineJoinModifier, value);
            return this;
        }
        strokeMiterLimit(value: any): this {
            modifierWithKey(this._modifiersWithKeys, StrokeMiterLimitModifier.identity,
                StrokeMiterLimitModifier, value);
            return this;
        }
        strokeOpacity(value: any): this {
            modifierWithKey(this._modifiersWithKeys, StrokeOpacityModifier.identity, StrokeOpacityModifier, value);
            return this;
        }
        fillOpacity(value: any): this {
            modifierWithKey(this._modifiersWithKeys, FillOpacityModifier.identity, FillOpacityModifier, value);
            return this;
        }
        strokeWidth(value: any): this {
            modifierWithKey(this._modifiersWithKeys, StrokeWidthModifier.identity, StrokeWidthModifier, value);
            return this;
        }
        antiAlias(value: any): this {
            modifierWithKey(this._modifiersWithKeys, AntiAliasModifier.identity, AntiAliasModifier, value);
            return this;
        }
        strokeDashArray(value: any): this {
            modifierWithKey(this._modifiersWithKeys, StrokeDashArrayModifier.identity, StrokeDashArrayModifier, value);
            return this;
        }
        mesh(value: any, column: any, row: any): this {
            throw new Error('Method not implemented.');
        }
        height(value: any): this {
            modifierWithKey(this._modifiersWithKeys, CommonShapeHeightModifier.identity,
                CommonShapeHeightModifier, value);
            return this;
        }
        width(value: any): this {
            modifierWithKey(this._modifiersWithKeys, CommonShapeWidthModifier.identity,
                CommonShapeWidthModifier, value);
            return this;
        }
        foregroundColor(value: any): this {
            modifierWithKey(this._modifiersWithKeys, CommonShapeForegroundColorModifier.identity,
                CommonShapeForegroundColorModifier, value);
            return this;
        }
        resetCommonShapeOptions(): void {
            modifierWithKey(this._modifiersWithKeys, CommonShapeWidthModifier.identity,
                CommonShapeWidthModifier, undefined);
            modifierWithKey(this._modifiersWithKeys, CommonShapeHeightModifier.identity,
                CommonShapeHeightModifier, undefined);
        }
        initialize(value: any): this {
            if (isUndefined(value[0]) || isNull(value[0])) {
                this.resetCommonShapeOptions();
                return this;
            }
            if (!isUndefined(value[0].width) && !isNull(value[0].width)) {
                modifierWithKey(this._modifiersWithKeys, CommonShapeWidthModifier.identity,
                    CommonShapeWidthModifier, value[0].width);
            } else {
                modifierWithKey(this._modifiersWithKeys, CommonShapeWidthModifier.identity,
                    CommonShapeWidthModifier, undefined);
            }
            if (!isUndefined(value[0].height) && !isNull(value[0].height)) {
                modifierWithKey(this._modifiersWithKeys, CommonShapeHeightModifier.identity,
                    CommonShapeHeightModifier, value[0].height);
            } else {
                modifierWithKey(this._modifiersWithKeys, CommonShapeHeightModifier.identity,
                    CommonShapeHeightModifier, undefined);
            }
            return this;
        }
    }

    class StrokeDashArrayModifier extends ModifierWithKey<any> {
        constructor(value: any) {
            super(value);
        }
        static identity: Symbol = Symbol('strokeDashArray');
        applyPeer(node: any, reset: any): void {
            if (reset) {
                getUINativeModule().commonShape.resetStrokeDashArray(node);
            } else {
                getUINativeModule().commonShape.setStrokeDashArray(node, this.value);
            }
        }
        checkObjectDiff(): boolean {
            return !isBaseOrResourceEqual(this.stageValue, this.value);
        }
    }
    class StrokeModifier extends ModifierWithKey<any> {
        constructor(value: any) {
            super(value);
        }
        static identity: Symbol = Symbol('stroke');
        applyPeer(node: any, reset: any): void {
            if (reset) {
                getUINativeModule().commonShape.resetStroke(node);
            } else {
                getUINativeModule().commonShape.setStroke(node, this.value);
            }
        }
        checkObjectDiff(): boolean {
            return !isBaseOrResourceEqual(this.stageValue, this.value);
        }
    }
    class FillModifier extends ModifierWithKey<any> {
        constructor(value: any) {
            super(value);
        }
        static identity: Symbol = Symbol('fill');
        applyPeer(node: any, reset: any): void {
            if (reset) {
                getUINativeModule().commonShape.resetFill(node);
            } else {
                getUINativeModule().commonShape.setFill(node, this.value);
            }
        }
        checkObjectDiff(): boolean {
            return !isBaseOrResourceEqual(this.stageValue, this.value);
        }
    }
    class StrokeDashOffsetModifier extends ModifierWithKey<any> {
        constructor(value: any) {
            super(value);
        }
        static identity: Symbol = Symbol('strokeDashOffset');
        applyPeer(node: any, reset: any): void {
            if (reset) {
                getUINativeModule().commonShape.resetStrokeDashOffset(node);
            } else {
                getUINativeModule().commonShape.setStrokeDashOffset(node, this.value);
            }
        }
        checkObjectDiff(): boolean {
            return !isBaseOrResourceEqual(this.stageValue, this.value);
        }
    }
    class StrokeLineCapModifier extends ModifierWithKey<any> {
        constructor(value: any) {
            super(value);
        }
        static identity: Symbol = Symbol('strokeLineCap');
        applyPeer(node: any, reset: any): void {
            if (reset) {
                getUINativeModule().commonShape.resetStrokeLineCap(node);
            } else {
                getUINativeModule().commonShape.setStrokeLineCap(node, this.value);
            }
        }
    }
    class StrokeLineJoinModifier extends ModifierWithKey<any> {
        constructor(value: any) {
            super(value);
        }
        static identity: Symbol = Symbol('strokeLineJoin');
        applyPeer(node: any, reset: any): void {
            if (reset) {
                getUINativeModule().commonShape.resetStrokeLineJoin(node);
            } else {
                getUINativeModule().commonShape.setStrokeLineJoin(node, this.value);
            }
        }
    }
    class StrokeMiterLimitModifier extends ModifierWithKey<any> {
        constructor(value: any) {
            super(value);
        }
        static identity: Symbol = Symbol('strokeMiterLimit');
        applyPeer(node: any, reset: any): void {
            if (reset) {
                getUINativeModule().commonShape.resetStrokeMiterLimit(node);
            } else {
                getUINativeModule().commonShape.setStrokeMiterLimit(node, this.value);
            }
        }
    }
    class FillOpacityModifier extends ModifierWithKey<any> {
        constructor(value: any) {
            super(value);
        }
        static identity: Symbol = Symbol('FillOpacity');
        applyPeer(node: any, reset: any): void {
            if (reset) {
                getUINativeModule().commonShape.resetFillOpacity(node);
            } else {
                getUINativeModule().commonShape.setFillOpacity(node, this.value);
            }
        }
        checkObjectDiff(): boolean {
            return !isBaseOrResourceEqual(this.stageValue, this.value);
        }
    }
    class StrokeOpacityModifier extends ModifierWithKey<any> {
        constructor(value: any) {
            super(value);
        }
        static identity: Symbol = Symbol('StrokeOpacity');
        applyPeer(node: any, reset: any): void {
            if (reset) {
                getUINativeModule().commonShape.resetStrokeOpacity(node);
            } else {
                getUINativeModule().commonShape.setStrokeOpacity(node, this.value);
            }
        }
        checkObjectDiff(): boolean {
            return !isBaseOrResourceEqual(this.stageValue, this.value);
        }
    }
    class StrokeWidthModifier extends ModifierWithKey<any> {
        constructor(value: any) {
            super(value);
        }
        static identity: Symbol = Symbol('strokeWidth');
        applyPeer(node: any, reset: any): void {
            if (reset) {
                getUINativeModule().commonShape.resetStrokeWidth(node);
            } else {
                getUINativeModule().commonShape.setStrokeWidth(node, this.value);
            }
        }
    }
    class AntiAliasModifier extends ModifierWithKey<any> {
        constructor(value: any) {
            super(value);
        }
        static identity: Symbol = Symbol('antiAlias');
        applyPeer(node: any, reset: any): void {
            if (reset) {
                getUINativeModule().commonShape.resetAntiAlias(node);
            } else {
                getUINativeModule().commonShape.setAntiAlias(node, this.value);
            }
        }
    }
    class CommonShapeHeightModifier extends ModifierWithKey<any> {
        constructor(value: any) {
            super(value);
        }
        static identity: Symbol = Symbol('commonShapeHeight');
        applyPeer(node: any, reset: any): void {
            if (reset) {
                getUINativeModule().commonShape.resetHeight(node);
            } else {
                getUINativeModule().commonShape.setHeight(node, this.value);
            }
        }
        checkObjectDiff(): boolean {
            return !isBaseOrResourceEqual(this.stageValue, this.value);
        }
    }
    class CommonShapeWidthModifier extends ModifierWithKey<any> {
        constructor(value: any) {
            super(value);
        }
        static identity: Symbol = Symbol('commonShapeWidth');
        applyPeer(node: any, reset: any): void {
            if (reset) {
                getUINativeModule().commonShape.resetWidth(node);
            } else {
                getUINativeModule().commonShape.setWidth(node, this.value);
            }
        }
        checkObjectDiff(): boolean {
            return !isBaseOrResourceEqual(this.stageValue, this.value);
        }
    }
    class CommonShapeForegroundColorModifier extends ModifierWithKey<any> {
        constructor(value: any) {
            super(value);
        }
        static identity: Symbol = Symbol('commonShapeForegroundColor');
        applyPeer(node: any, reset: any): void {
            if (reset) {
                getUINativeModule().commonShape.resetForegroundColor(node);
            } else {
                getUINativeModule().commonShape.setForegroundColor(node, this.value);
            }
        }
        checkObjectDiff(): boolean {
            return !isBaseOrResourceEqual(this.stageValue, this.value);
        }
    }

    loadComponent.componentObj = {'component' : ArkCommonShapeComponent };
  }
  return loadComponent.componentObj;
}

class JSShapeAbstract extends JSViewAbstract {
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
}

function createComponent(nativePtr: any, classType: any): any {
    loadComponent();
    if (loadComponent.componentObj !== undefined) {
        return new loadComponent.componentObj.component(nativePtr, classType);
    }
    return undefined;
}

function exportComponent(): void {
    globalThis.ArkCommonShapeComponent = (loadComponent as any).componentObj?.component;
}

function exportView(): void {
    globalThis.CommonShape = JSShapeAbstract;
}

export default { loadComponent, createComponent, exportComponent, exportView, CommonShape: JSShapeAbstract };
