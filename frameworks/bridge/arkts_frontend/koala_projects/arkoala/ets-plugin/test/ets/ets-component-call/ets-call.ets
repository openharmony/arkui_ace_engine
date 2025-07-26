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

import { Foo, Text, Struct, StructWithContent } from './user-function-declaration'

@Builder
export function callPlainFunction() {
    Foo()
}

@Builder
export function callBuiltinComponent() {
    Button()
}

@Builder
export function callFunctionWithReservedName() {
    Text()
}

@Builder
export function callStruct() {
    Struct({param: 17})
}

@Builder
export function callStructWithContent() {
    StructWithContent({param: 17})
}

@Builder
export function callStructWithContentWithContent() {
    StructWithContent({param: 17}) {
        Button()
    }
}

function main() {

    Column({ space: 30 }) {
            Flex({ justifyContent: 30 })
    }
}