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

/// <reference path="./import.ts" />
class ArkCommonShapeComponent extends ArkComponent implements CommonShapeMethod<ShapeAttribute> {
    constructor(nativePtr: KNode) {
        super(nativePtr);
    }
    viewPort(value: { x?: string | number | undefined; y?: string | number | undefined; width?: string | number | undefined; height?: string | number | undefined; }): this {
        throw new Error('Method not implemented.');
    }
    stroke(value: ResourceColor): this {
        modifierWithKey(this._modifiersWithKeys, StrokeModifier.identity, StrokeModifier, value);
        return this;
    }
    fill(value: ResourceColor): this {
        modifierWithKey(this._modifiersWithKeys, FillModifier.identity, FillModifier, value);
        return this;
    }
    strokeDashOffset(value: string | number): this {
        modifierWithKey(this._modifiersWithKeys, StrokeDashOffsetModifier.identity,
                StrokeDashOffsetModifier, value);
        return this;
    }
    strokeLineCap(value: LineCapStyle): this {
        modifierWithKey(this._modifiersWithKeys, StrokeLineCapModifier.identity, StrokeLineCapModifier, value);
        return this;
    }
    strokeLineJoin(value: LineJoinStyle): this {
        modifierWithKey(this._modifiersWithKeys, StrokeLineJoinModifier.identity, StrokeLineJoinModifier, value);
        return this;
    }
    strokeMiterLimit(value: string | number): this {
        modifierWithKey(this._modifiersWithKeys, StrokeMiterLimitModifier.identity,
                StrokeMiterLimitModifier, value);
        return this;
    }
    strokeOpacity(value: number | string | Resource): this {
        modifierWithKey(this._modifiersWithKeys, StrokeOpacityModifier.identity, StrokeOpacityModifier, value);
        return this;
    }
    fillOpacity(value: number | string | Resource): this {
        modifierWithKey(this._modifiersWithKeys, FillOpacityModifier.identity, FillOpacityModifier, value);
        return this;
    }
    strokeWidth(value: string | number): this {
        modifierWithKey(this._modifiersWithKeys, StrokeWidthModifier.identity, StrokeWidthModifier, value);
        return this;
    }
    antiAlias(value: boolean): this {
        modifierWithKey(this._modifiersWithKeys, AntiAliasModifier.identity, AntiAliasModifier, value);
        return this;
    }
    strokeDashArray(value: any[]): this {
        modifierWithKey(this._modifiersWithKeys, Symbol('strokeDashArray'), StrokeDashArrayModifier, value);
        return this;
    }
    mesh(value: any[], column: number, row: number): this {
        throw new Error('Method not implemented.');
    }
}

class StrokeDashArrayModifier extends ModifierWithKey<object> {
    constructor(value: object) {
        super(value);
    }
    static identity: Symbol = Symbol('strokeDashArray');
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().commonShape.resetStrokeDashArray(node);
        }
        else {
            GetUINativeModule().commonShape.setStrokeDashArray(node, this.value);
        }
    }

    checkObjectDiff(): boolean {
        if (isResource(this.stageValue) && isResource(this.value)) {
            return !isResourceEqual(this.stageValue, this.value);
        } else {
            return true;
        }
    }
}

class StrokeModifier extends ModifierWithKey<ResourceColor> {
    constructor(value: ResourceColor) {
        super(value);
    }
    static identity: Symbol = Symbol('stroke');
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().commonShape.resetStroke(node);
        } else {
            GetUINativeModule().commonShape.setStroke(node, this.value);
        }
    }

    checkObjectDiff(): boolean {
        if (isResource(this.stageValue) && isResource(this.value)) {
            return !isResourceEqual(this.stageValue, this.value);
        } else {
            return true;
        }
    }
}

class FillModifier extends ModifierWithKey<ResourceColor> {
    constructor(value: ResourceColor) {
        super(value);
    }
    static identity: Symbol = Symbol('fill');
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().commonShape.resetFill(node);
        } else {
            GetUINativeModule().commonShape.setFill(node, this.value);
        }
    }

    checkObjectDiff(): boolean {
        if (isResource(this.stageValue) && isResource(this.value)) {
            return !isResourceEqual(this.stageValue, this.value);
        } else {
            return true;
        }
    }
}

class StrokeDashOffsetModifier extends ModifierWithKey<number | string> {
    constructor(value: number | string) {
        super(value);
    }
    static identity: Symbol = Symbol('strokeDashOffset');
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().commonShape.resetStrokeDashOffset(node);
        } else {
            GetUINativeModule().commonShape.setStrokeDashOffset(node, this.value);
        }
    }

    checkObjectDiff(): boolean {
        if (isResource(this.stageValue) && isResource(this.value)) {
            return !isResourceEqual(this.stageValue, this.value);
        } else {
            return true;
        }
    }
}

class StrokeLineCapModifier extends ModifierWithKey<number> {
    constructor(value: number) {
        super(value);
    }
    static identity: Symbol = Symbol('strokeLineCap');
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().commonShape.resetStrokeLineCap(node);
        } else {
            GetUINativeModule().commonShape.setStrokeLineCap(node, this.value);
        }
    }
}

class StrokeLineJoinModifier extends ModifierWithKey<number> {
    constructor(value: number) {
        super(value);
    }
    static identity: Symbol = Symbol('strokeLineJoin');
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().commonShape.resetStrokeLineJoin(node);
        } else {
            GetUINativeModule().commonShape.setStrokeLineJoin(node, this.value);
        }
    }
}

class StrokeMiterLimitModifier extends ModifierWithKey<number | string> {
    constructor(value: number | string) {
        super(value);
    }
    static identity: Symbol = Symbol('strokeMiterLimit');
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().commonShape.resetStrokeMiterLimit(node);
        } else {
            GetUINativeModule().commonShape.setStrokeMiterLimit(node, this.value);
        }
    }
}

class FillOpacityModifier extends ModifierWithKey<number | string | Resource> {
    constructor(value: number | string | Resource) {
        super(value);
    }
    static identity: Symbol = Symbol('FillOpacity');
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().commonShape.resetFillOpacity(node);
        } else {
            GetUINativeModule().commonShape.setFillOpacity(node, this.value);
        }
    }
    checkObjectDiff(): boolean {
        if (isResource(this.stageValue) && isResource(this.value)) {
            return !isResourceEqual(this.stageValue, this.value);
        } else {
            return true;
        }
    }
}

class StrokeOpacityModifier extends ModifierWithKey<number | string | Resource> {
    constructor(value: number | string | Resource) {
        super(value);
    }
    static identity: Symbol = Symbol('StrokeOpacity');
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().commonShape.resetStrokeOpacity(node);
        } else {
            GetUINativeModule().commonShape.setStrokeOpacity(node, this.value);
        }
    }
    checkObjectDiff(): boolean {
        if (isResource(this.stageValue) && isResource(this.value)) {
            return !isResourceEqual(this.stageValue, this.value);
        } else {
            return true;
        }
    }
}

class StrokeWidthModifier extends ModifierWithKey<number | string> {
    constructor(value: number | string) {
        super(value);
    }
    static identity: Symbol = Symbol('strokeWidth');
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().commonShape.resetStrokeWidth(node);
        } else {
            GetUINativeModule().commonShape.setStrokeWidth(node, this.value);
        }
    }
}

class AntiAliasModifier extends ModifierWithKey<boolean> {
    constructor(value: boolean) {
        super(value);
    }
    static identity: Symbol = Symbol('antiAlias');
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().commonShape.resetAntiAlias(node);
        } else {
            GetUINativeModule().commonShape.setAntiAlias(node, this.value);
        }
    }
}