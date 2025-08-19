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

import { KPointer } from "@koalaui/interop"
import { image } from "@ohos.multimedia.image"

export namespace extractors {

    export function toImagePixelMapPtr(value: image.PixelMap): KPointer {
        return toPointer(value, "image.PixelMap", "nativeObj")
    }

    export function fromImagePixelMapPtr(ptr: KPointer): image.PixelMap {
        return new image.PixelMapInner(ptr)
    }

    function toPointer(obj: Object, declarationName: string, pointerPropName: string): long {
        for (const entry of Object.entries(obj)) {
            if (entry == undefined) continue
            if (entry[0] == pointerPropName) return entry[1] as long
        }
        throw new Error(`native pointer for ${declarationName} declaration is not found!`)
    }
}

