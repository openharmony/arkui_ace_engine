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

import { InteropNativeModule } from "@koalaui/interop";

import { ArkBaseNode } from "./ArkBaseNode";
import { MarqueeAttribute, ResourceColor, Length, FontWeight, MarqueeUpdateStrategy } from "../../component";
import { ArkMarqueePeer, MarqueeOptions } from "../../component";
import { Resource } from "global.resource";

export class ArkMarqueeNode extends ArkBaseNode  implements MarqueeAttribute  {
    constructParam(...param: Object[]): this {
        InteropNativeModule._NativeLog("list constructParam enter")
        return this;
    }

    getPeer() : ArkMarqueePeer {
        return this.peer as ArkMarqueePeer
    }
    initialize(options: MarqueeOptions): this {
        const options_casted = options as (MarqueeOptions)
        this.getPeer()?.setMarqueeOptionsAttribute(options_casted)
        this.markDirty();
        return this;
    }
    allowChildTypes(): string[] {
        return ["MarqueeItem", "MarqueeItemGroup"];
    }
    setMarqueeOptions(options: MarqueeOptions): this {
        const options_casted = options as (MarqueeOptions)
        this.getPeer()?.setMarqueeOptionsAttribute(options_casted)
        this.markDirty();
        return this;
    }
    fontColor(value: ResourceColor | undefined): this {
        const value_casted = value as (ResourceColor | undefined)
        this.getPeer()?.fontColorAttribute(value_casted)
        this.markDirty();
        return this;
    }
    fontSize(value: Length | undefined): this {
        const value_casted = value as (Length | undefined)
        this.getPeer()?.fontSizeAttribute(value_casted)
        this.markDirty();
        return this;
    }
    allowScale(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined)
        this.getPeer()?.allowScaleAttribute(value_casted)
        this.markDirty();
        return this;
    }
    fontWeight(value: number | FontWeight | string | undefined): this {
        const value_casted = value as (number | FontWeight | string | undefined)
        this.getPeer()?.fontWeightAttribute(value_casted)
        this.markDirty();
        return this;
    }
    fontFamily(value: string | Resource | undefined): this {
        const value_casted = value as (string | Resource | undefined)
        this.getPeer()?.fontFamilyAttribute(value_casted)
        this.markDirty();
        return this;
    }
    marqueeUpdateStrategy(value: MarqueeUpdateStrategy | undefined): this {
        const value_casted = value as (MarqueeUpdateStrategy | undefined)
        this.getPeer()?.marqueeUpdateStrategyAttribute(value_casted)
        this.markDirty();
        return this;
    }
    onStart(value: (() => void) | undefined): this {
        const value_casted = value as ((() => void) | undefined)
        this.getPeer()?.onStartAttribute(value_casted)
        this.markDirty();
        return this;
    }
    onBounce(value: (() => void) | undefined): this {
        const value_casted = value as ((() => void) | undefined)
        this.getPeer()?.onBounceAttribute(value_casted)
        this.markDirty();
        return this;
    }
    onFinish(value: (() => void) | undefined): this {
        const value_casted = value as ((() => void) | undefined)
        this.getPeer()?.onFinishAttribute(value_casted)
        this.markDirty();
        return this;
    }
}