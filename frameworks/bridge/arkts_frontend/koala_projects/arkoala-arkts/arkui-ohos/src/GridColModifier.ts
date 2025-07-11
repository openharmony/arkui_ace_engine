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

import { ArkGridColPeer, ArkCommonMethodPeer, AttributeModifier, GridColAttribute, GridColColumnOption } from './component';
import { ArkCommonAttributeSet, modifierWithKey, ModifierWithKey } from './handwritten/modifiers/ArkCommonModifier';

class SpanModifier extends ModifierWithKey<number | GridColColumnOption | undefined> {
    static identity: string = 'span';

    constructor(value: number | GridColColumnOption | undefined) {
        super(value);
    }

    applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
        let spanPeerNode = node as ArkGridColPeer;
        if (reset) {
            // now do nothing
        } else {
            if (this.value !== undefined) {
                spanPeerNode.spanAttribute(this.value as number | GridColColumnOption);
            }
        }
    }

    static factory(value: number | GridColColumnOption | undefined): SpanModifier {
        return new SpanModifier(value);
    }
}

class GridColOffsetModifier extends ModifierWithKey<number | GridColColumnOption | undefined> {
    static identity: string = 'gridColOffset';

    constructor(value: number | GridColColumnOption | undefined) {
        super(value);
    }

    applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
        let gridColOffsetNode = node as ArkGridColPeer;
        if (reset) {
            // now do nothing
        } else {
            if (this.value !== undefined) {
                gridColOffsetNode.gridColOffsetAttribute(this.value as number | GridColColumnOption);
            }
        }
    }

    static factory(value: number | GridColColumnOption | undefined): GridColOffsetModifier {
        return new GridColOffsetModifier(value);
    }
}


class OrderModifier extends ModifierWithKey<number | GridColColumnOption | undefined> {
    static identity: string = 'order';

    constructor(value: number | GridColColumnOption | undefined) {
        super(value);
    }

    applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
        let orderNode = node as ArkGridColPeer;
        if (reset) {
            // now do nothing
        } else {
            if (this.value !== undefined) {
                orderNode.orderAttribute(this.value as number | GridColColumnOption);
            }
        }
    }

    static factory(value: number | GridColColumnOption | undefined): OrderModifier {
        return new OrderModifier(value);
    }
}

export class ArkGridColAttributeSet extends ArkCommonAttributeSet implements GridColAttribute {
    span(value: number | GridColColumnOption | undefined): this {
        modifierWithKey(this._modifiersWithKeys, SpanModifier.identity, SpanModifier.factory, value);
        return this;
    }
    
    gridColOffset(value: number | GridColColumnOption | undefined): this {
        modifierWithKey(this._modifiersWithKeys, GridColOffsetModifier.identity, GridColOffsetModifier.factory, value);
        return this;
    }

    order(value: number | GridColColumnOption | undefined): this {
        modifierWithKey(this._modifiersWithKeys, OrderModifier.identity, OrderModifier.factory, value);
        return this;
    }
}

export class GridColModifier implements AttributeModifier<GridColAttribute> {
    attributeSet: ArkGridColAttributeSet = new ArkGridColAttributeSet();

    applyNormalAttribute(instance: GridColAttribute): void {}
    applyPressedAttribute(instance: GridColAttribute): void {}
    applyFocusedAttribute(instance: GridColAttribute): void {}
    applyDisabledAttribute(instance: GridColAttribute): void {}
    applySelectedAttribute(instance: GridColAttribute): void {}

    span(value: number | GridColColumnOption | undefined): this {
        this.attributeSet.span(value);
        return this;
    }

    gridColOffset(value: number | GridColColumnOption | undefined): this {
        this.attributeSet.gridColOffset(value);
        return this;
    }

    order(value: number | GridColColumnOption | undefined): this {
        this.attributeSet.order(value);
        return this;
    }
}
