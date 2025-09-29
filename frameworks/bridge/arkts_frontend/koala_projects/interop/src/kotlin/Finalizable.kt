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

package koalaui.interop

import kotlin.experimental.ExperimentalNativeApi
import kotlin.native.ref.createCleaner

private class _FinalizableDataHolder(val ptr: KPointer, val finalizer: KPointer) {}

public open class Finalizable(var ptr: KPointer, var finalizer: KPointer) {
    @OptIn(ExperimentalNativeApi::class)
    var cleaner = createCleaner(_FinalizableDataHolder(ptr, finalizer)) {
        if (it.finalizer != nullptr) {
            InteropNativeModule._InvokeFinalizer(it.ptr, it.finalizer)
        }
    }
}
