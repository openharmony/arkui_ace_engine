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
import { int32 } from "@koalaui/common"
import { pointer, nullptr, InteropNativeModule, SerializerBase } from "@koalaui/interop"

let foreignContext: pointer = nullptr

export function enterForeignContext(context: pointer) {
    foreignContext = context
    InteropNativeModule._SetForeignVMContext(context)
}

export function leaveForeignContext() {
    foreignContext = nullptr
    InteropNativeModule._SetForeignVMContext(nullptr)
}

export function setTimeoutForeign(code: () => void, delay: int32): int32 {
    if (foreignContext == nullptr) throw new Error("null foreign VM context")
    let serializer = new SerializerBase()
    serializer.writeInt32(1)
    serializer.holdAndWriteCallback(code)
    serializer.writeInt32(delay)
    let rv = InteropNativeModule._CallForeignVM(foreignContext, 3, serializer.asBuffer(), serializer.length())
    serializer.release()
    return rv
}
