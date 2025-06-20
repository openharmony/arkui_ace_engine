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

import { ArkStackPeer, ArkCommonMethodPeer, AttributeModifier, Alignment, PointLightStyle, StackAttribute } from './component';
import { ArkCommonAttributeSet, modifierWithKey, ModifierWithKey } from './handwritten/modifiers/ArkCommonModifier';

class AlignContentModifier extends ModifierWithKey<Alignment | undefined> {
    static identity: string = 'alignContent';

    constructor(value: Alignment | undefined) {
        super(value);
    }

    applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
        let alignContentPeerNode = node as ArkStackPeer;
        if (reset) {
            // now do nothing
        } else {
            if (this.value !== undefined) {
                alignContentPeerNode.alignContentAttribute(this.value as Alignment);
            }
        }
    }

    static factory(value: Alignment | undefined): AlignContentModifier {
        return new AlignContentModifier(value);
    }
}

class PointLightModifier extends ModifierWithKey<PointLightStyle | undefined> {
    static identity: string = 'pointLight';

    constructor(value: PointLightStyle | undefined) {
        super(value);
    }

    applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
        let pointLightPeerNode = node as ArkStackPeer;
        if (reset) {
            // now do nothing
        } else {
            if (this.value !== undefined) {
                pointLightPeerNode.pointLightAttribute(this.value as PointLightStyle);
            }
        }
    }

    static factory(value: PointLightStyle | undefined): PointLightModifier {
        return new PointLightModifier(value);
    }
}

export class ArkStackAttributeSet extends ArkCommonAttributeSet implements StackAttribute {

    alignContent(value: Alignment | undefined): this {
        modifierWithKey(this._modifiersWithKeys, AlignContentModifier.identity, AlignContentModifier.factory, value);
        return this;
    }

    pointLight(value: PointLightStyle | undefined): this {
        modifierWithKey(this._modifiersWithKeys, PointLightModifier.identity, PointLightModifier.factory, value);
        return this;
    }
}

export class StackModifier implements AttributeModifier<StackAttribute> {
    attributeSet: ArkStackAttributeSet = new ArkStackAttributeSet();

    applyNormalAttribute(instance: StackAttribute): void {}
    applyPressedAttribute(instance: StackAttribute): void {}
    applyFocusedAttribute(instance: StackAttribute): void {}
    applyDisabledAttribute(instance: StackAttribute): void {}
    applySelectedAttribute(instance: StackAttribute): void {}

    alignContent(value: Alignment | undefined): this {
        this.attributeSet.alignContent(value);
        return this;
    }

    pointLight(value: PointLightStyle | undefined): this {
        this.attributeSet.pointLight(value);
        return this;
    }
}
