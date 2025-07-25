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
import { SymbolGlyphAttribute } from "../../generated";
import { Resource } from "../../generated";
import { ArkSymbolGlyphPeer } from "../../generated/peers/ArkSymbolglyphPeer";
import { ArkBaseNode } from "./ArkBaseNode";
import { FontWeight } from "../../generated";
import { ResourceColor } from "../../generated";
import { SymbolEffectStrategy, SymbolRenderingStrategy } from "../../generated";
import { SymbolEffect } from "../../generated";

export class ArkSymbolGlyphNode extends ArkBaseNode implements SymbolGlyphAttribute {
    fontSize(value: number | string | Resource | undefined): this {
        if (value) {
            this.getPeer().fontSizeAttribute(value!);
        } else {
            // this.getPeer().resetFontSizeAttribute(value);
        }
        return this;
    }
    fontColor(value: Array<ResourceColor>): this {
        if (value) {
            this.getPeer().fontColorAttribute(value!);
        } else {
            // this.getPeer().resetFontColorAttribute(value);
        }
        return this;
    }
    fontWeight(value: number | FontWeight | string): this {
        if (value) {
            this.getPeer().fontWeightAttribute(value!);
        } else {
            // this.getPeer().resetFontWeightAttribute(value);
        }
        return this;
    }
    effectStrategy(value: SymbolEffectStrategy): this {
        if (value) {
            this.getPeer().effectStrategyAttribute(value!);
        } else {
            // this.getPeer().resetEffectStrategyAttribute(value);
        }
        return this;
    }
    renderingStrategy(value: SymbolRenderingStrategy): this {
        if (value) {
            this.getPeer().renderingStrategyAttribute(value!);
        } else {
            // this.getPeer().resetRenderingStrategyAttribute(value);
        }
        return this;
    }
    symbolEffect(symbolEffect: SymbolEffect, isActive?: boolean | undefined | number | undefined): this {
        if (symbolEffect) {
            const isActive_type = runtimeType(isActive);
            if (isActive_type == RuntimeType.BOOLEAN) {
                this.getPeer().symbolEffect0Attribute(symbolEffect!, isActive as boolean);
            } else if (isActive_type == RuntimeType.NUMBER) {
                this.getPeer().symbolEffect1Attribute(symbolEffect!, isActive as number);
            } else {
                this.getPeer().symbolEffect0Attribute(symbolEffect!, undefined);
            }
        } else {
            // this.getPeer().resetFontSizeAttribute(value);
        }
        return this;
    }
    getPeer() : ArkSymbolGlyphPeer {
        return this.peer as ArkSymbolGlyphPeer;
    }
}