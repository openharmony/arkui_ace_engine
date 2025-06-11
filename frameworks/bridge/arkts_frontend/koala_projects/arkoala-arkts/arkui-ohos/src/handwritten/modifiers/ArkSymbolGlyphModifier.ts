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

import { RuntimeType, runtimeType } from "@koalaui/interop";
import { SymbolEffectStrategy, SymbolRenderingStrategy } from "../../generated";
import { AttributeModifier } from "../..";
import { SymbolGlyphAttribute } from "../..";
import { Resource } from "../..";
import { FontWeight } from "../../generated";
import { ResourceColor } from "../../generated";
import { ArkSymbolGlyphPeer } from "../../generated/peers/ArkSymbolglyphPeer";
import { ArkCommonMethodPeer } from "../../generated/peers/ArkCommonPeer";
import { ArkCommonAttributeSet, modifierNullWithKey, modifierWithKey, ModifierWithKey } from "./ArkCommonModifier";
import { SymbolEffect } from "../..";

class ArkSymbolEffect {
    symbolEffect?: SymbolEffect;
    triggerValue?: number;
    isActive?: boolean;

    constructor() {
        this.symbolEffect = undefined;
        this.triggerValue = undefined;
        this.isActive = undefined;
    }
}

class SymbolGlyphFontSizeModifier extends ModifierWithKey<number | string | Resource> {
    static identity: string = 'symbolGlyphFontSize';

    constructor(value: number | string | Resource) {
        super(value)
    }

    applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
        let peerNode = node as ArkSymbolGlyphPeer
        if (reset) {
            // peerNode.resetFontSizeAttribute();
        } else {
            peerNode.fontSizeAttribute(this.value!);
        }
    }

    static factory(value: number | string | Resource): SymbolGlyphFontSizeModifier {
        return new SymbolGlyphFontSizeModifier(value)
    }
}

class SymbolGlyphFontColorModifier extends ModifierWithKey<Array<ResourceColor>> {
    static identity: string = 'symbolGlyphFontColor';

    constructor(value: Array<ResourceColor>) {
        super(value)
    }

    applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
        let peerNode = node as ArkSymbolGlyphPeer
        if (reset) {
            // peerNode.resetFontColorAttribute();
        } else {
            peerNode.fontColorAttribute(this.value!);
        }
    }

    static factory(value: Array<ResourceColor>): SymbolGlyphFontColorModifier {
        return new SymbolGlyphFontColorModifier(value)
    }
}

class SymbolGlyphFontWeightModifier extends ModifierWithKey<number | FontWeight | string> {
    static identity: string = 'symbolGlyphFontWeight';

    constructor(value: number | FontWeight | string) {
        super(value)
    }

    applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
        let peerNode = node as ArkSymbolGlyphPeer
        if (reset) {
            // peerNode.resetFontWeightAttribute();
        } else {
            peerNode.fontWeightAttribute(this.value!);
        }
    }

    static factory(value: number | FontWeight | string): SymbolGlyphFontWeightModifier {
        return new SymbolGlyphFontWeightModifier(value)
    }
}

class SymbolGlyphEffectStrategyModifier extends ModifierWithKey<SymbolEffectStrategy> {
    static identity: string = 'symbolGlyphEffectStrategy';

    constructor(value: SymbolEffectStrategy) {
        super(value)
    }

    applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
        let peerNode = node as ArkSymbolGlyphPeer
        if (reset) {
            // peerNode.resetEffectStrategyAttribute();
        } else {
            peerNode.effectStrategyAttribute(this.value!);
        }
    }

    static factory(value: SymbolEffectStrategy): SymbolGlyphEffectStrategyModifier {
        return new SymbolGlyphEffectStrategyModifier(value)
    }
}

class SymbolGlyphRenderingStrategyModifier extends ModifierWithKey<SymbolRenderingStrategy> {
    static identity: string = 'symbolGlyphRenderingStrategy';

    constructor(value: SymbolRenderingStrategy) {
        super(value)
    }

    applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
        let peerNode = node as ArkSymbolGlyphPeer
        if (reset) {
            // peerNode.resetRenderingStrategyAttribute();
        } else {
            peerNode.renderingStrategyAttribute(this.value!);
        }
    }

    static factory(value: SymbolRenderingStrategy): SymbolGlyphRenderingStrategyModifier {
        return new SymbolGlyphRenderingStrategyModifier(value)
    }
}

class SymbolGlyphEffectModifier extends ModifierWithKey<ArkSymbolEffect> {
    static identity: string = 'symbolGlyphEffect';

    constructor(value: ArkSymbolEffect) {
        super(value)
    }

    applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
        let peerNode = node as ArkSymbolGlyphPeer
        if (reset) {
            // peerNode.resetSymbolEffectAttribute();
        } else {
            let symbolEffect = this.value!.symbolEffect;
            let isActive = this.value!.isActive;
            let triggerValue = this.value!.triggerValue;
            if (symbolEffect !== undefined) {
                if (isActive !== undefined) {
                    peerNode.symbolEffect0Attribute(symbolEffect!, isActive);
                } else if (triggerValue !== undefined) {
                    peerNode.symbolEffect1Attribute(symbolEffect!, triggerValue);
                } else {
                    peerNode.symbolEffect0Attribute(symbolEffect!, undefined);
                }
            } else {
                // peerNode.resetSymbolEffectAttribute();
            }
        }
    }

    static factory(value: ArkSymbolEffect): SymbolGlyphEffectModifier {
        return new SymbolGlyphEffectModifier(value)
    }
}

export class ArkSymbolGlyphAttributeSet extends ArkCommonAttributeSet /* implements SymbolGlyphAttribute */ {
    fontSize(value: number | string | Resource | undefined): this {
        if (value) {
            modifierWithKey(this._modifiersWithKeys, SymbolGlyphFontSizeModifier.identity, SymbolGlyphFontSizeModifier.factory, value!);
        } else {
            modifierNullWithKey(this._modifiersWithKeys, SymbolGlyphFontSizeModifier.identity);
        }
        return this;
    }
    fontColor(value: Array<ResourceColor>): this {
        if (value) {
            modifierWithKey(this._modifiersWithKeys, SymbolGlyphFontColorModifier.identity, SymbolGlyphFontColorModifier.factory, value!);
        } else {
            modifierNullWithKey(this._modifiersWithKeys, SymbolGlyphFontColorModifier.identity);
        }
        return this;
    }
    fontWeight(value: number | FontWeight | string): this {
        if (value) {
            modifierWithKey(this._modifiersWithKeys, SymbolGlyphFontWeightModifier.identity, SymbolGlyphFontWeightModifier.factory, value!);
        } else {
            modifierNullWithKey(this._modifiersWithKeys, SymbolGlyphFontWeightModifier.identity);
        }
        return this;
    }
    effectStrategy(value: SymbolEffectStrategy): this {
        if (value) {
            modifierWithKey(this._modifiersWithKeys, SymbolGlyphEffectStrategyModifier.identity, SymbolGlyphEffectStrategyModifier.factory, value! as SymbolEffectStrategy);
        } else {
            modifierNullWithKey(this._modifiersWithKeys, SymbolGlyphEffectStrategyModifier.identity);
        }
        return this;
    }
    renderingStrategy(value: SymbolRenderingStrategy): this {
        if (value) {
            modifierWithKey(this._modifiersWithKeys, SymbolGlyphRenderingStrategyModifier.identity, SymbolGlyphRenderingStrategyModifier.factory, value! as SymbolRenderingStrategy);
        } else {
            modifierNullWithKey(this._modifiersWithKeys, SymbolGlyphRenderingStrategyModifier.identity);
        }
        return this;
    }
    symbolEffect(symbolEffect: SymbolEffect, isActive?: boolean | undefined | number | undefined): this {
        let value = new ArkSymbolEffect();
        value.symbolEffect = symbolEffect;
        const isActive_type = runtimeType(isActive);
        if (isActive_type == RuntimeType.BOOLEAN) {
            value.isActive = isActive as boolean;
        } else if (isActive_type == RuntimeType.NUMBER) {
            value.triggerValue = isActive as number;
        } else {
            value.isActive = undefined;
            value.triggerValue = undefined;
        }
        if (symbolEffect) {
            modifierWithKey(this._modifiersWithKeys, SymbolGlyphEffectModifier.identity, SymbolGlyphEffectModifier.factory, value!);
        } else {
            modifierNullWithKey(this._modifiersWithKeys, SymbolGlyphEffectModifier.identity);
        }
        return this;
    }
}

export class SymbolGlyphModifier extends ArkSymbolGlyphAttributeSet implements AttributeModifier<SymbolGlyphAttribute> {
    _SymbolGlyphModifierStub: string = "";
   
      applyNormalAttribute(instance: SymbolGlyphAttribute){}
    
     applyPressedAttribute(instance: SymbolGlyphAttribute){}
     
     applyFocusedAttribute(instance: SymbolGlyphAttribute){}
     
     applyDisabledAttribute(instance: SymbolGlyphAttribute){}
   
     applySelectedAttribute(instance: SymbolGlyphAttribute){}
}