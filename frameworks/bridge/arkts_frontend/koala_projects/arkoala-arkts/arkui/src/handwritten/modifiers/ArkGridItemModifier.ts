/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import { AttributeModifier, GridItemAttribute } from "../..";
import { ArkGridItemPeer } from "../../generated/peers/ArkGridItemPeer";
import { ArkCommonMethodPeer } from "../../generated/peers/ArkCommonPeer";
import { ArkCommonAttributeSet, modifierNullWithKey, modifierWithKey, ModifierWithKey } from "./ArkCommonModifier";

class RowStartModifier extends ModifierWithKey<number> {
    static identity: string = 'rowStart';

    constructor(value: number) {
        super(value)
    }

    applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
        let gridItemPeerNode = node as ArkGridItemPeer
        if (reset) {
            
        } else {
            gridItemPeerNode.rowStartAttribute(this.value as (number));
        }
    }

    static factory(value: number): RowStartModifier {
        return new RowStartModifier(value)
    }
}

class RowEndModifier extends ModifierWithKey<number> {
    static identity: string = 'rowEnd';

    constructor(value: number) {
        super(value)
    }

    applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
        let gridItemPeerNode = node as ArkGridItemPeer
        if (reset) {
            
        } else {
            gridItemPeerNode.rowEndAttribute(this.value as (number));
        }
    }

    static factory(value: number): RowEndModifier {
        return new RowEndModifier(value)
    }
}

class ColumnStartModifier extends ModifierWithKey<number> {
    static identity: string = 'columnStart';

    constructor(value: number) {
        super(value)
    }

    applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
        let gridItemPeerNode = node as ArkGridItemPeer
        if (reset) {
            
        } else {
            gridItemPeerNode.columnStartAttribute(this.value as (number));
        }
    }

    static factory(value: number): ColumnStartModifier {
        return new ColumnStartModifier(value)
    }
}

class ColumnEndModifier extends ModifierWithKey<number> {
    static identity: string = 'columnEnd';

    constructor(value: number) {
        super(value)
    }

    applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
        let gridItemPeerNode = node as ArkGridItemPeer
        if (reset) {
            
        } else {
            gridItemPeerNode.columnEndAttribute(this.value as (number));
        }
    }

    static factory(value: number): ColumnEndModifier {
        return new ColumnEndModifier(value)
    }
}

export class ArkGridItemAttributeSet extends ArkCommonAttributeSet implements GridItemAttribute {

    rowStart(value: number): this {
        if (value) {
            modifierWithKey(this._modifiersWithKeys, RowStartModifier.identity, RowStartModifier.factory, value);
        } else {
            modifierNullWithKey(this._modifiersWithKeys, RowStartModifier.identity);
        }
        return this;
    }

    rowEnd(value: number): this {
        if (value) {
            modifierWithKey(this._modifiersWithKeys, RowEndModifier.identity, RowEndModifier.factory, value);
        } else {
            modifierNullWithKey(this._modifiersWithKeys, RowEndModifier.identity);
        }
        return this;
    }

    columnStart(value: number): this {
        if (value) {
            modifierWithKey(this._modifiersWithKeys, ColumnStartModifier.identity, ColumnStartModifier.factory, value);
        } else {
            modifierNullWithKey(this._modifiersWithKeys, ColumnStartModifier.identity);
        }
        return this;
    }

    columnEnd(value: number): this {
        if (value) {
            modifierWithKey(this._modifiersWithKeys, ColumnEndModifier.identity, ColumnEndModifier.factory, value);
        } else {
            modifierNullWithKey(this._modifiersWithKeys, ColumnEndModifier.identity);
        }
        return this;
    }
}

export class GridItemModifier extends ArkGridItemAttributeSet implements AttributeModifier<GridItemAttribute> {
    applyNormalAttribute(instance: GridItemAttribute){}
    applyPressedAttribute(instance: GridItemAttribute){}
    applyFocusedAttribute(instance: GridItemAttribute){}
    applyDisabledAttribute(instance: GridItemAttribute){}
    applySelectedAttribute(instance: GridItemAttribute){}
}