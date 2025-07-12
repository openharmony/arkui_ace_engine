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

import { int32 } from "@koalaui/compat"
import { createSha1 } from "./sha1";

export class UniqueId {
    private sha = createSha1()

    public addString(data: string): UniqueId {
        this.sha.updateString(data)
        return this
    }

    public addI32(data: int32): UniqueId {
        this.sha.updateInt32(data)
        return this
    }

    public addF32Array(data: Float32Array): UniqueId {
        this.sha.update(data)
        return this
    }

    public addI32Array(data: Int32Array): UniqueId {
        this.sha.update(data)
        return this
    }

    public addU32Array(data: Uint32Array): UniqueId {
        this.sha.update(data)
        return this
    }

    public addU8Array(data: Uint8Array): UniqueId {
        this.sha.update(data)
        return this
    }

    public addPtr(data: Uint32Array | number): UniqueId {
        if (data instanceof Uint32Array) {
            return this.addU32Array(data)
        }
        return this.addI32(data as int32)
    }

    public compute(): string {
        return this.sha.digest("hex") as string
    }
}
