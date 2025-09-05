/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

import { SlideEffect, PageTransitionOptions, TranslateOptions, ScaleOptions, PageTransitionCallback } from "../generated"
import { PageTransitionEnterInterface, PageTransitionExitInterface } from "./ArkPageTransition"

export class ArkPageTransitionData implements PageTransitionEnterInterface, PageTransitionExitInterface {
    params: PageTransitionOptions
    _onEnter?: PageTransitionCallback
    _onExit?: PageTransitionCallback
    _slide?: SlideEffect
    _translate?: TranslateOptions
    _scale?: ScaleOptions
    _opacity?: number

    constructor(params: PageTransitionOptions) {
        this.params = params
    }
    onEnter(event: PageTransitionCallback): this {
        this._onEnter = event
        return this
    }
    onExit(event: PageTransitionCallback): this {
        this._onExit = event
        return this
    }
    slide(value: SlideEffect): this {
        this._slide = value
        return this
    }
    translate(value: TranslateOptions): this {
        this._translate = value
        return this
    }
    scale(value: ScaleOptions): this {
        this._scale = value
        return this
    }
    opacity(value: number): this {
        this._opacity = value
        return this
    }

    toString(): string {
        return `[params=${optionsToString(this.params)}, slide=${this._slide}, translate=${this._translate}, scale=${this._scale}, opacity=${this._opacity}, onEnter=${this._onEnter}, onExit=${this._onExit}]`
    }
}

function optionsToString(options:PageTransitionOptions): string {
    return `[type=${options.type}, curve = ${options.curve}, duration=${options.duration}, delay=${options.delay}]`
}

export class ArkPageTransitionEnterComponent extends ArkPageTransitionData {
    constructor(params: PageTransitionOptions) {
        super(params)
    }
}

export class ArkPageTransitionExitComponent extends ArkPageTransitionData {
    constructor(params: PageTransitionOptions) {
        super(params)
    }
}
