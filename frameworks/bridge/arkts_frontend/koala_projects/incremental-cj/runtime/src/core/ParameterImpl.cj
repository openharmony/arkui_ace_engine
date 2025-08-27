/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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
package KoalaRuntime.core

import KoalaRuntime.util.*

class ParameterImpl<Value> <: UniqueObject & MutableState<Value> {
    private var dependencies: ?Dependencies
    private var name: ?String
    private var value: Value
    private var modified = false

    /**
     * @param value - initial state value
     * @param name - name defined for named states only
     */
    init(value: Value, name: ?String) {
        this.dependencies = Dependencies()
        this.name = name
        this.value = value
    }

    public func isModified(): Bool {
        this.dependencies?.onAccess()
        return this.modified
    }

    public func getValue(): Value {
        this.dependencies?.onAccess()
        return this.value
    }

    public func setValue(value: Value): Unit {
        this.modified = !equalValues(this.value, value)
        if (this.modified) {
            this.value = value
        }
        this.dependencies?.onUpdate(this.modified)
    }

    protected func disposeImpl(): Unit {
        GlobalStateManager.checkForStateDisposing()
        this.dependencies = None
    }

    public func toString(): String {
        let sb = StringBuilder("Parameter")
        if (let Some(name) <- this.name) {
            sb.append("(")
            sb.append(name)
            sb.append(")")
        }
        if (this.isDisposed()) {
            sb.append(",disposed")
        }
        if (this.modified) {
            sb.append(",modified")
        }
        if (let Some(value) <- (this.value as ToString)) {
            sb.append("=")
            sb.append(value.toString())
        }
        sb.toString()
    }
}
