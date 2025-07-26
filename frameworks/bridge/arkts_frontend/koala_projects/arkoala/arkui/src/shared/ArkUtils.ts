/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

import { float32 } from "@koalaui/common";
/**
 * Converts a value in vp units to a value in px.
 * @since 7
 */
export function vp2px(value: float32): float32 {
    let scale = getVpToPxScale();
    if(scale == 0){
        return value
    }
    return value * scale
}

/**
 * Converts a number in units of px to a number in units of vp.
 * @since 7
 */
export function px2vp(value: float32): float32 {
    let scale = getVpToPxScale();
    if(scale == 0){
        return value
    }
    return value / scale
}

/**
 * Converts a number in fp units to a number in px.
 * @since 7
 */
export function fp2px(value: float32): float32 {
    let scale = getFpToPxScale()
    if(scale == 0){
        return value
    }
    return value * scale
}

/**
 * Converts a number in units of px to a number in units of fp.
 * @since 7
 */
export function px2fp(value: float32): float32 {
    let scale = getFpToPxScale()
    if(scale == 0){
        return value
    }
    return value / scale
}

/**
 * Converts a number in units of lpx to a number in units of px.
 * @since 7
 */
export function lpx2px(value: float32): float32 {
    let scale = getLpxToPxScale()
    if(scale == 0){
        return value
    }
    return value * scale
}

/**
 * Converts a number in units of px to a number in units of lpx.
 * @since 7
 */
export function px2lpx(value: float32): float32 {
    let scale = getLpxToPxScale()
    if(scale == 0){
        return value
    }
    return value / scale
}

function getVpToPxScale(): float32 {
    console.log("getVpToPxScale: not implemented")
    return 0
}

function getFpToPxScale(): float32 {
    console.log("getFpToPxScale: not implemented")
    return 0
}

function getLpxToPxScale(): float32 {
    console.log("getLpxToPxScale: not implemented")
    return 0
}

export type ESObject = any

export function isNotResource<T>(value: T | Resource): value is Exclude<T, Resource> {
    return value == null || isNotResourceOrNull(value)
}

export function isNotResourceOrNull<T>(value: T | Resource): value is NonNullable<Exclude<T, Resource>> {
    return value !== null && (typeof value !== "object" || !("id" in value))
}
