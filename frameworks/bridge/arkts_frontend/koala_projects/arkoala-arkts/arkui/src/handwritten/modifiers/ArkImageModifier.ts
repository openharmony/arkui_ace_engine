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

import { int32 } from "@koalaui/common"
import { AttributeModifier, ColumnAttribute, ImageAttribute, HorizontalAlign } from "../..";
import { ArkImagePeer } from "../../generated/peers/ArkImagePeer";
import { ArkCommonMethodPeer } from "../../generated/peers/ArkCommonPeer";
import { Length, BorderRadiuses } from "../../generated/ArkUnitsInterfaces"
import { Resource } from "../../generated/ArkResourceInterfaces"
import { ArkCommonAttributeSet, modifierNullWithKey, modifierWithKey, ModifierWithKey } from "./ArkCommonModifier";

class BorderRadiusModifier extends ModifierWithKey<Length | BorderRadiuses> {
    static identity: string = 'imageBorderRadius';

    constructor(value: Length | BorderRadiuses) {
        super(value);
    }

    applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
        let imagePeerNode = node as ArkImagePeer
        if (reset) {
            imagePeerNode.imageBorderRadiusAttribute(0);
        } else {
            imagePeerNode.imageBorderRadiusAttribute(this.value);
        }
    }

    static factory(value: Length | BorderRadiuses): BorderRadiusModifier {
        return new BorderRadiusModifier(value)
    }
}

class OpacityModifier extends ModifierWithKey<number | Resource> {
    static identity: string = 'imageOpacity';

    constructor(value: number | Resource) {
        super(value);
    }

    applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
        let imagePeerNode = node as ArkImagePeer
        if (reset) {
            imagePeerNode.imageOpacityAttribute(0);
        } else {
            imagePeerNode.imageOpacityAttribute(this.value);
        }
    }

    static factory(value: number | Resource): OpacityModifier {
        return new OpacityModifier(value)
    }
}

export class ArkImageAttributeSet extends ArkCommonAttributeSet implements ImageAttribute {
    borderRadius(value: Length | BorderRadiuses): this {
        if (value) {
            modifierWithKey(this._modifiersWithKeys, BorderRadiusModifier.identity, BorderRadiusModifier.factory, value);
        } else {
            modifierNullWithKey(this._modifiersWithKeys, BorderRadiusModifier.identity)
        }
        return this;
    }

    opacity(value: number | Resource): this {
        if (value) {
            modifierWithKey(this._modifiersWithKeys, OpacityModifier.identity, OpacityModifier.factory, value);
        } else {
            modifierNullWithKey(this._modifiersWithKeys, OpacityModifier.identity)
        }
        return this;
    }
}

export class ImageModifier extends ArkImageAttributeSet implements AttributeModifier<ImageAttribute> {
    applyNormalAttribute(instance: ImageAttribute) { this.opacity(1); }
    applyPressedAttribute(instance: ImageAttribute) { }
    applyFocusedAttribute(instance: ImageAttribute) { }
    applyDisabledAttribute(instance: ImageAttribute) { }
    applySelectedAttribute(instance: ImageAttribute) { }
    _ImageModifierStub: string = "";
}