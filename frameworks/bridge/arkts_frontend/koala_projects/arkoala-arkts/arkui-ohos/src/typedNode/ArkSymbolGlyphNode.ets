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
import { InteropNativeModule, runtimeType, RuntimeType } from "@koalaui/interop";

import { ArkBaseNode } from "./ArkBaseNode";
import { SymbolGlyphAttribute, ResourceColor, FontWeight, SymbolEffect, SymbolEffectStrategy, SymbolRenderingStrategy } from "../framework";
import { ArkSymbolGlyphPeer } from "../framework";
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
    fontSize(value: double | string | Resource | undefined): this {
        const value_casted = value as (double | string | Resource | undefined)
        this.getPeer()?.setFontSizeAttribute(value_casted)
        this.markDirty();
        return this;
    }
    fontColor(value: Array<ResourceColor> | undefined): this {
        const value_casted = value as (Array<ResourceColor> | undefined)
        this.getPeer()?.setFontColorAttribute(value_casted)
        this.markDirty();
        return this;
    }
    fontWeight(value: int32 | FontWeight | string | undefined): this {
        const value_casted = value as (int32 | FontWeight | string | undefined)
        this.getPeer()?.setFontWeightAttribute(value_casted)
        this.markDirty();
        return this;
    }
    effectStrategy(value: SymbolEffectStrategy | undefined): this {
        const value_casted = value as (SymbolEffectStrategy | undefined)
        this.getPeer()?.setEffectStrategyAttribute(value_casted)
        this.markDirty();
        return this;
    }
    renderingStrategy(value: SymbolRenderingStrategy | undefined): this {
        const value_casted = value as (SymbolRenderingStrategy | undefined)
        this.getPeer()?.setRenderingStrategyAttribute(value_casted)
        this.markDirty();
        return this;
    }
    minFontScale(value: double | Resource | undefined): this {
        const value_casted = value as (double | Resource | undefined)
        this.getPeer()?.setMinFontScaleAttribute(value_casted)
        this.markDirty();
        return this;
    }
    maxFontScale(value: double | Resource | undefined): this {
        const value_casted = value as (double | Resource | undefined)
        this.getPeer()?.setMaxFontScaleAttribute(value_casted)
        this.markDirty();
        return this;
    }
    symbolEffect(symbolEffect: SymbolEffect | undefined, isActive?: int32 | boolean | undefined): this {
        const symbolEffect_type = runtimeType(symbolEffect)
        const isActive_type = runtimeType(isActive)
        if (((RuntimeType.OBJECT == symbolEffect_type) || (RuntimeType.UNDEFINED == symbolEffect_type)) && ((RuntimeType.BOOLEAN == isActive_type) || (RuntimeType.UNDEFINED == isActive_type))) {
            const symbolEffect_casted = symbolEffect as (SymbolEffect | undefined)
            const isActive_casted = isActive as (boolean | undefined)
            this.getPeer()?.setSymbolEffectAttribute(symbolEffect_casted, isActive_casted)
            this.markDirty();
            return this
        }
        if (((RuntimeType.OBJECT == symbolEffect_type) || (RuntimeType.UNDEFINED == symbolEffect_type)) && ((RuntimeType.NUMBER == isActive_type) || (RuntimeType.UNDEFINED == isActive_type))) {
            const symbolEffect_casted = symbolEffect as (SymbolEffect | undefined)
            const triggerValue_casted = isActive as (int32 | undefined)
            this.getPeer()?.setSymbolEffectAttribute(symbolEffect_casted, triggerValue_casted)
            this.markDirty();
            return this
        }
        return this;
    }
}