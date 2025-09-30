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
package Interop

import std.collection.*

public type CallbackType = (args: KSerializerBuffer, length: Int32) -> Int32

class CallbackRecord {
    let callback: CallbackType
    let autoDisposable: Bool
    init(callback: CallbackType, autoDisposable: Bool) {
        this.callback = callback
        this.autoDisposable = autoDisposable
    }
}

class CallbackRegistry {

    static var INSTANCE = CallbackRegistry()

    private var callbacks = HashMap<Int32, CallbackRecord>()
    private var id: Int32 = 1024

    init() {
        this.callbacks.add(0, CallbackRecord(
            {args: KSerializerBuffer, length: Int32 =>
                println("Callback 0 called with args = ${args} and length = ${length}")
                throw Exception("Null callback called")
            }, false)
        )
    }

    func wrap(callback: CallbackType, autoDisposable: Bool): Int32 {
        this.id += 1
        let id = this.id
        this.callbacks.add(id, CallbackRecord(callback, autoDisposable))
        return id
    }

    func wrapSystem(id: Int32, callback: CallbackType, autoDisposable: Bool): Int32 {
        this.callbacks.add(id, CallbackRecord(callback, autoDisposable))
        return id
    }

    func call(id: Int32, args: KSerializerBuffer, length: Int32): Int32 {
        let record = this.callbacks.get(id)
        if (let Some(record) <- record) {
            if (record.autoDisposable) {
                this.dispose(id)
            }
            return record.callback(args, length)
        } else {
            println("Callback ${id} is not known")
            return 0
        }
    }

    func dispose(id: Int32): Unit {
        this.callbacks.remove(id)
    }
}

public func wrapCallback(callback: CallbackType): Int32 {
    wrapCallback(callback, true)
}
public func wrapCallback(callback: CallbackType, autoDisposable: Bool): Int32 {
    return CallbackRegistry.INSTANCE.wrap(callback, autoDisposable)
}

public func wrapSystemCallback(id: Int32, callback: CallbackType): Int32 {
    return CallbackRegistry.INSTANCE.wrapSystem(id, callback, false)
}

public func disposeCallback(id: Int32): Unit {
    CallbackRegistry.INSTANCE.dispose(id)
}

public func callCallback(id: Int32, args: KSerializerBuffer, length: Int32): Int32 {
    return CallbackRegistry.INSTANCE.call(id, args, length)
}
