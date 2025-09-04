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

@file:OptIn(ExperimentalForeignApi::class)

package koalaui.interop

import kotlinx.cinterop.*
import platform.posix.exit

import cinterop.interop_native_module.kotlin_SetKoalaKotlinCallbackDispatcher

typealias CallbackType = (args: KSerializerBuffer, length: Int) -> Int

class CallbackRecord (var callback: CallbackType, var autoDisposable: Boolean)

object CallbackRegistry {
    private var callbacks = mutableMapOf<Int, CallbackRecord>()
    private var id = 1024

    fun wrap(callback: CallbackType, autoDisposable: Boolean): Int {
        val newId = this.id++
        this.callbacks.set(newId, CallbackRecord(callback, autoDisposable))
        return newId
    }

    fun wrapSystem(newId: Int, callback: CallbackType): Int {
        this.callbacks.set(newId, CallbackRecord(callback, false))
        return newId
    }

    fun call(id: Int, length: Int, args: KSerializerBuffer): Int {
        val record = callbacks[id]
        if (record == null) {
            println("Callback $id is not known, terminating app...")
            exit(1) // exceptions in code called from C can lead to UB, so just terminate app with error
        }
        if (record!!.autoDisposable) {
            this.dispose(id)
        }
        return record.callback(args, length)
    }

    fun dispose(id: Int) {
        this.callbacks.remove(id)
    }

    init {
        val dispatcher = staticCFunction<Int, Int, CPointer<CPointed>, Int> { id, length, args ->
            CallbackRegistry.call(id, length, args.toLong())
        }
        kotlin_SetKoalaKotlinCallbackDispatcher(dispatcher)
    }
}
