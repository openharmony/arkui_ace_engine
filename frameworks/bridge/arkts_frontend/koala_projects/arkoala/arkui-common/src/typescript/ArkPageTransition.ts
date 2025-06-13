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

import { ArkRouteType } from "./ArkRouteType"

export interface ArkPageTransitionParams {
    kind: ArkRouteType
    duration: number
    curve: Curve | string
    delay: number
}

export class ArkPageTransitionData {
    params: Partial<ArkPageTransitionParams>
    _onEnter?: (type: ArkRouteType, progress: number) => void
    _onExit?: (type: ArkRouteType, progress: number) => void
    _slide?: SlideEffect
    _translate?: { x?: string | number | undefined; y?: string | number | undefined; z?: string | number | undefined; }
    _scale?: { x?: number | undefined; y?: number | undefined; z?: number | undefined; centerX?: string | number | undefined; centerY?: string | number | undefined; }
    _opacity?: number

    constructor(params: Partial<ArkPageTransitionParams>) {
        this.params = params
    }
    onEnter(event: (type: ArkRouteType, progress: number) => void): this {
        this._onEnter = event
        return this
    }
    onExit(event: (type: ArkRouteType, progress: number) => void): this {
        this._onExit = event
        return this
    }
    slide(value: SlideEffect): this {
        this._slide = value
        return this
    }
    translate(value: { x?: string | number | undefined; y?: string | number | undefined; z?: string | number | undefined; }): this {
        this._translate = value
        return this
    }
    scale(value: { x?: number | undefined; y?: number | undefined; z?: number | undefined; centerX?: string | number | undefined; centerY?: string | number | undefined; }): this {
        this._scale = value
        return this
    }
    opacity(value: number): this {
        this._opacity = value
        return this
    }
}

export class ArkPageTransitionEnterComponent extends ArkPageTransitionData /* implements PageTransitionEnterInterface */ {
    constructor(params: Partial<ArkPageTransitionParams>) {
        super(params)
    }
}

export class ArkPageTransitionExitComponent extends ArkPageTransitionData /* implements PageTransitionExitInterface */ {
    constructor(params: Partial<ArkPageTransitionParams>) {
        super(params)
    }
}
