/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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


// HANDWRITTEN, DO NOT REGENERATE
import { __memo_context_type , __memo_id_type  } from "arkui.stateManagement.runtime";
import { int32, hashCodeFromString, KoalaCallsiteKey } from "@koalaui/common"
import { RepeatByArray } from "@koalaui/runtime"
import { InteropNativeModule } from "@koalaui/interop"

export function ForEach<T>(__memo_context: __memo_context_type, __memo_id: __memo_id_type, arr: Array<T>, 
itemGenerator: (__memo_context: __memo_context_type, __memo_id: __memo_id_type, item: T, index: number) => void, keyGenerator?: (item: T, index: number) => string) {
    const __memo_scope = __memo_context.scope<void>(__memo_id + (0x1bf2b52427 as __memo_id_type), 3);
    const __memo_parameter_arr = __memo_scope.param(0, arr);
    const __memo_parameter_itemGenerator = __memo_scope.param(1, itemGenerator);
    const __memo_parameter_keyGenerator = __memo_scope.param(2, keyGenerator);
    if (__memo_scope.unchanged) {
        __memo_scope.cached;
        return;
    }
    if (__memo_parameter_arr.value === null || __memo_parameter_arr.value === undefined) {
        InteropNativeModule._NativeLog('input array is null or undefined error. Application error!');
        {
            __memo_scope.recache();
            return;
        }
    }
    if (typeof __memo_parameter_itemGenerator.value != 'function') {
        InteropNativeModule._NativeLog('item generator function missing. Application error!');
        {
            __memo_scope.recache();
            return;
        }
    }
    if (__memo_parameter_keyGenerator.value !== undefined && typeof __memo_parameter_keyGenerator.value !== 'function') {
        InteropNativeModule._NativeLog('key generator is not a function. Application error!');
        {
            __memo_scope.recache();
            return;
        }
    }
    RepeatByArray<T>(__memo_context,__memo_id,__memo_parameter_arr.value, (element: T, index: int32) => __memo_parameter_keyGenerator.value ? hashCodeFromString(__memo_parameter_keyGenerator.value!(element, (index as number))) : index, (__memo_context: __memo_context_type, __memo_id: __memo_id_type, element: T, index: int32) => {
        const __memo_scope = __memo_context.scope<void>(__memo_id + (0x8b272adf6d as __memo_id_type), 2);
        const __memo_parameter_element = __memo_scope.param(0, element);
        const __memo_parameter_index = __memo_scope.param(1, index);
        if (__memo_scope.unchanged) {
            __memo_scope.cached;
            return;
        }
        __memo_parameter_itemGenerator.value(__memo_context, __memo_id + (0xfb138595b8 as __memo_id_type), __memo_parameter_element.value, (__memo_parameter_index.value as number));
        {
            __memo_scope.recache();
            return;
        }
    });
    {
        __memo_scope.recache();
        return;
    }
}
