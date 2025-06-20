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

import { ArkColumnPeer, ArkCommonMethodPeer, AttributeModifier, ColumnAttribute, HorizontalAlign, FlexAlign, PointLightStyle } from './component';
import { ArkCommonAttributeSet, modifierWithKey, ModifierWithKey } from './handwritten/modifiers/ArkCommonModifier';

class AlignItemsModifier extends ModifierWithKey<HorizontalAlign | undefined> {
    static identity: string = 'alignItems';

    constructor(value: HorizontalAlign | undefined) {
        super(value);
    }

    applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
        let alignItemsNode = node as ArkColumnPeer;
        if (reset) {
            // now do nothing
        } else {
            if (this.value !== undefined) {
                alignItemsNode.alignItemsAttribute(this.value as HorizontalAlign);
            }
        }
    }

    static factory(value: HorizontalAlign | undefined): AlignItemsModifier {
        return new AlignItemsModifier(value);
    }
}

class JustifyContentModifier extends ModifierWithKey<FlexAlign | undefined> {
    static identity: string = 'justifyContent';

    constructor(value: FlexAlign | undefined) {
        super(value);
    }

    applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
        let justifyContentNode = node as ArkColumnPeer;
        if (reset) {
            // now do nothing
        } else {
            if (this.value !== undefined) {
                justifyContentNode.justifyContentAttribute(this.value as FlexAlign);
            }
        }
    }

    static factory(value: FlexAlign | undefined): JustifyContentModifier {
        return new JustifyContentModifier(value);
    }
}

class PointLightModifier extends ModifierWithKey<PointLightStyle | undefined> {
    static identity: string = 'pointLight';

    constructor(value: PointLightStyle | undefined) {
        super(value);
    }

    applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
        let pointLightNode = node as ArkColumnPeer;
        if (reset) {
            // now do nothing
        } else {
            if (this.value !== undefined) {
                pointLightNode.pointLightAttribute(this.value as PointLightStyle);
            }
        }
    }

    static factory(value: PointLightStyle | undefined): PointLightModifier {
        return new PointLightModifier(value);
    }
}

class ReverseModifier extends ModifierWithKey<boolean | undefined> {
    static identity: string = 'reverse';

    constructor(value: boolean | undefined) {
        super(value);
    }

    applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
        let reverseNode = node as ArkColumnPeer;
        if (reset) {
            // now do nothing
        } else {
            if (this.value !== undefined) {
                reverseNode.reverseAttribute(this.value as boolean);
            }
        }
    }

    static factory(value: boolean | undefined): ReverseModifier {
        return new ReverseModifier(value);
    }
}

export class ArkColumnAttributeSet extends ArkCommonAttributeSet implements ColumnAttribute {
    alignItems(value: HorizontalAlign | undefined): this {
        modifierWithKey(this._modifiersWithKeys, AlignItemsModifier.identity, AlignItemsModifier.factory, value);
        return this;
    }
    justifyContent(value: FlexAlign | undefined): this {
        modifierWithKey(this._modifiersWithKeys, JustifyContentModifier.identity, JustifyContentModifier.factory, value);
        return this;
    }
    pointLight(value: PointLightStyle | undefined): this {
        modifierWithKey(this._modifiersWithKeys, PointLightModifier.identity, PointLightModifier.factory, value);
        return this;
    }
    reverse(value: boolean | undefined): this {
        modifierWithKey(this._modifiersWithKeys, ReverseModifier.identity, ReverseModifier.factory, value);
        return this;
    }
}

export class ColumnModifier implements AttributeModifier<ColumnAttribute> {
    attributeSet: ArkColumnAttributeSet = new ArkColumnAttributeSet();

    applyNormalAttribute(instance: ColumnAttribute): void {}
    applyPressedAttribute(instance: ColumnAttribute): void {}
    applyFocusedAttribute(instance: ColumnAttribute): void {}
    applyDisabledAttribute(instance: ColumnAttribute): void {}
    applySelectedAttribute(instance: ColumnAttribute): void {}

    alignItems(value: HorizontalAlign | undefined): this {
        this.attributeSet.alignItems(value);
        return this;
    }
    justifyContent(value: FlexAlign | undefined): this {
        this.attributeSet.justifyContent(value);
        return this;
    }
    pointLight(value: PointLightStyle | undefined): this {
        this.attributeSet.pointLight(value);
        return this;
    }
    reverse(value: boolean | undefined): this {
        this.attributeSet.reverse(value);
        return this;
    }
}
