/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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


// WARNING! THIS FILE IS AUTO-GENERATED, DO NOT MAKE CHANGES, THEY WILL BE LOST ON NEXT GENERATION!

import { ComponentBase } from "../ComponentBase"

/** @memo:stable */
export class ArkCommonTransitionComponent extends ComponentBase {
    // getPeer(): ArkCommonTransitionPeer {
    //     return (this.peer as ArkCommonTransitionPeer)
    // }
    /** @memo */
    slide(value: SlideEffect): this {
        console.log("CommonTransition.slide")
        // if (this.checkPriority("slide")) {
        //     const value_casted = value as (SlideEffect)
        //     this.getPeer()?.slideAttribute(value_casted)
        //     return this
        // }
        return this
    }
    /** @memo */
    translate(value: TranslateOptions): this {
        // if (this.checkPriority("translate")) {
        //     const value_casted = value as (TranslateOptions)
        //     this.getPeer()?.translateAttribute(value_casted)
        //     return this
        // }
        console.log("CommonTransition.translate")
        return this
    }
    /** @memo */
    scale(value: ScaleOptions): this {
        // if (this.checkPriority("scale")) {
        //     const value_casted = value as (ScaleOptions)
        //     this.getPeer()?.scaleAttribute(value_casted)
        //     return this
        // }
        console.log("CommonTransition.scale")
        return this
    }
    /** @memo */
    opacity(value: number): this {
        // if (this.checkPriority("opacity")) {
        //     const value_casted = value as (number)
        //     this.getPeer()?.opacityAttribute(value_casted)
        //     return this
        // }
        console.log("CommonTransition.number")
        return this
    }
    public applyAttributesFinish(): void {
        // we calls this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
