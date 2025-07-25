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

import { Finalizable } from "./Finalizable"
import { InteropNativeModule } from "./InteropNativeModule"
import { pointer } from "./InteropTypes"

export class NativeString extends Finalizable {
    constructor(ptr: pointer) {
        super(ptr, InteropNativeModule._GetStringFinalizer())
    }
    static Make(value: string): NativeString {
        return new NativeString(InteropNativeModule._StringMake(value))
    }
    toString(): string {
        return InteropNativeModule._StdStringToString(this.ptr)
    }
}
