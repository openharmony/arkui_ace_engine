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

import { KoalaCallsiteKey } from "@koalaui/common"
import { StateContext } from "./states/State"

// These are used for the hidden parameters inserted by the plugin.
// Must only be used by compiler rewrite, do not use directly.
export type __memo_context_type = StateContext
export type __memo_id_type = KoalaCallsiteKey
// References to this type will be changed to an incompatible type
// so that typing expression `x extends __memo_transformed ? A : B`
// can change its branch
export type __memo_transformed_before = string
export type __memo_transformed_after = number
export type __memo_transformed = __memo_transformed_before

export function __context(): StateContext {
    throw new Error("All __context() references should have been transformed by the compiler plugin. Either have 'context' argument or have '/** @memo */' marking and use intrinsic '__context()'.")
}

export function __id(): KoalaCallsiteKey {
    throw new Error("All __id() references should have been transformed by the compiler plugin. Either have 'id' argument or have '/** @memo */' marking and use intrinsic '__id()'.")
}

export function __key(): KoalaCallsiteKey {
    throw new Error("All __key() references should have been transformed by the compiler plugin.")
}

export function __hash(value: string): KoalaCallsiteKey {
    throw new Error("The __hash() function is only for source transformation tests.")
}

