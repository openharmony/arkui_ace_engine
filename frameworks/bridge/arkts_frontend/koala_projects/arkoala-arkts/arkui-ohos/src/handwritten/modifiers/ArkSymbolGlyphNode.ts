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

import { InteropNativeModule, runtimeType, RuntimeType } from "@koalaui/interop";

import { ArkBaseNode } from "./ArkBaseNode";
import { SymbolGlyphAttribute, ResourceColor, FontWeight, SymbolEffect, SymbolEffectStrategy, SymbolRenderingStrategy } from "../../component";
import { ArkSymbolGlyphPeer } from "../../component";
import { Resource } from "global.resource";

export class ArkSymbolGlyphNode extends ArkBaseNode implements SymbolGlyphAttribute {
    constructParam(...param: Object[]): this {
        InteropNativeModule._NativeLog("list constructParam enter")
        return this;
    }
    getPeer() : ArkSymbolGlyphPeer {
        return this.peer as ArkSymbolGlyphPeer
    }
    initialize(value?: Resource): this {
        const value_casted = value as (Resource | undefined)
        this.getPeer()?.setSymbolGlyphOptionsAttribute(value_casted)
        this.markDirty();
        return this;
    }
    allowChildTypes(): string[] {
        return ["SymbolGlyphItem", "SymbolGlyphItemGroup"];
    }
    setSymbolGlyphOptions(value?: Resource): this {
        const value_casted = value as (Resource | undefined)
        this.getPeer()?.setSymbolGlyphOptionsAttribute(value_casted)
        this.markDirty();
        return this;
    }
    fontSize(value: number | string | Resource | undefined): this {
        const value_casted = value as (number | string | Resource | undefined)
        this.getPeer()?.fontSizeAttribute(value_casted)
        this.markDirty();
        return this;
    }
    fontColor(value: Array<ResourceColor> | undefined): this {
        const value_casted = value as (Array<ResourceColor> | undefined)
        this.getPeer()?.fontColorAttribute(value_casted)
        this.markDirty();
        return this;
    }
    fontWeight(value: number | FontWeight | string | undefined): this {
        const value_casted = value as (number | FontWeight | string | undefined)
        this.getPeer()?.fontWeightAttribute(value_casted)
        this.markDirty();
        return this;
    }
    effectStrategy(value: SymbolEffectStrategy | undefined): this {
        const value_casted = value as (SymbolEffectStrategy | undefined)
        this.getPeer()?.effectStrategyAttribute(value_casted)
        this.markDirty();
        return this;
    }
    renderingStrategy(value: SymbolRenderingStrategy | undefined): this {
        const value_casted = value as (SymbolRenderingStrategy | undefined)
        this.getPeer()?.renderingStrategyAttribute(value_casted)
        this.markDirty();
        return this;
    }
    minFontScale(value: number | Resource | undefined): this {
        const value_casted = value as (number | Resource | undefined)
        this.getPeer()?.minFontScaleAttribute(value_casted)
        this.markDirty();
        return this;
    }
    maxFontScale(value: number | Resource | undefined): this {
        const value_casted = value as (number | Resource | undefined)
        this.getPeer()?.maxFontScaleAttribute(value_casted)
        this.markDirty();
        return this;
    }
    symbolEffect(symbolEffect: SymbolEffect | undefined, isActive?: number | boolean | undefined): this {
        const symbolEffect_type = runtimeType(symbolEffect)
        const isActive_type = runtimeType(isActive)
        if (((RuntimeType.OBJECT == symbolEffect_type) || (RuntimeType.UNDEFINED == symbolEffect_type)) && ((RuntimeType.BOOLEAN == isActive_type) || (RuntimeType.UNDEFINED == isActive_type))) {
            const symbolEffect_casted = symbolEffect as (SymbolEffect | undefined)
            const isActive_casted = isActive as (boolean | undefined)
            this.getPeer()?.symbolEffect0Attribute(symbolEffect_casted, isActive_casted)
            this.markDirty();
            return this
        }
        if (((RuntimeType.OBJECT == symbolEffect_type) || (RuntimeType.UNDEFINED == symbolEffect_type)) && ((RuntimeType.NUMBER == isActive_type) || (RuntimeType.UNDEFINED == isActive_type))) {
            const symbolEffect_casted = symbolEffect as (SymbolEffect | undefined)
            const triggerValue_casted = isActive as (number | undefined)
            this.getPeer()?.symbolEffect1Attribute(symbolEffect_casted, triggerValue_casted)
            this.markDirty();
            return this
        }
        return this;
    }
}