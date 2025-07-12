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

import { int32 } from "@koalaui/common"

// todo can be removed if passing ArrayBuffer type through interop is possible
export class KBuffer {
    private readonly _buffer: Uint8Array
    public get buffer(): ArrayBuffer {
        return this._buffer
    }
    public get length(): int32 {
        return this._buffer.length
    }

    constructor(length: int32) {
        this._buffer = new Uint8Array(length)
    }

    set(index: int32, value: int32): void {
        this._buffer[index] = value
    }

    get(index: int32): int32 {
        return this._buffer[index]
    }
}