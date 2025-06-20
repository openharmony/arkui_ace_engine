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

import { ArkRowPeer, ArkCommonMethodPeer, AttributeModifier, VerticalAlign, FlexAlign, PointLightStyle, RowAttribute } from './component';
import { ArkCommonAttributeSet, modifierWithKey, ModifierWithKey } from './handwritten/modifiers/ArkCommonModifier';

class AlignItemsModifier extends ModifierWithKey<VerticalAlign | undefined> {
    static identity: string = 'alignItems';

    constructor(value: VerticalAlign | undefined) {
        super(value);
    }

    applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
        let alignItemsNode = node as ArkRowPeer;
        if (reset) {
            // now do nothing
        } else {
            if (this.value !== undefined) {
                alignItemsNode.alignItemsAttribute(this.value as VerticalAlign);
            }
        }
    }

    static factory(value: VerticalAlign | undefined): AlignItemsModifier {
        return new AlignItemsModifier(value);
    }
}

class JustifyContentModifier extends ModifierWithKey<FlexAlign | undefined> {
    static identity: string = 'justifyContent';

    constructor(value: FlexAlign | undefined) {
        super(value);
    }

    applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
        let justifyContentNode = node as ArkRowPeer;
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
        let pointLightNode = node as ArkRowPeer;
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
        let reverseNode = node as ArkRowPeer;
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

export class ArkRowAttributeSet extends ArkCommonAttributeSet implements RowAttribute {
    alignItems(value: VerticalAlign | undefined): this {
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

export class RowModifier implements AttributeModifier<RowAttribute> {
    attributeSet: ArkRowAttributeSet = new ArkRowAttributeSet();

    applyNormalAttribute(instance: RowAttribute): void {}
    applyPressedAttribute(instance: RowAttribute): void {}
    applyFocusedAttribute(instance: RowAttribute): void {}
    applyDisabledAttribute(instance: RowAttribute): void {}
    applySelectedAttribute(instance: RowAttribute): void {}

    alignItems(value: VerticalAlign | undefined): this {
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
