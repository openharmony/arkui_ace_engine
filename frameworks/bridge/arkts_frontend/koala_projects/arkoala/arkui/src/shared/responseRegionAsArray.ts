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

import { parseDimension } from "./basic"

export function responseRegionAsArray(value: Rectangle | Rectangle[]): Float32Array {
    const array: number[] = []
    const rects: Rectangle[] = Array.isArray(value) ? value : [value]

    for (let index = 0; index < rects.length; index++) {
        array.push(parseDimension(rects[index].x ?? 0).value)
        array.push(parseDimension(rects[index].x ?? 0).unit)
        array.push(parseDimension(rects[index].y ?? 0).value)
        array.push(parseDimension(rects[index].y ?? 0).unit)
        array.push(parseDimension(rects[index].width ?? 0).value)
        array.push(parseDimension(rects[index].width ?? 0).unit)
        array.push(parseDimension(rects[index].height ?? 0).value)
        array.push(parseDimension(rects[index].height ?? 0).unit)
    }

    return new Float32Array(array)
}
