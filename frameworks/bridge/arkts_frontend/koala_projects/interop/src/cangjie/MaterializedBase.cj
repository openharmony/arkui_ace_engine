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

public open class Finalizable {
    public var ptr: KPointer
    public var finalizer: KPointer

    public Finalizable(ptr: KPointer, finalizer: KPointer) {
        this.ptr = ptr
        this.finalizer = finalizer
    }
}

public interface MaterializedBase {
    public func getPeer(): ?Finalizable

    public static func toPeerPtr(value: Any): KPointer
    {
        let base: MaterializedBase = match (value as MaterializedBase) {
            case Some(x) => x
            case None => throw Exception("Value is not a MaterializedBase instance!")
        }
        return match (base.getPeer()) {
            case Some(peer) => peer.ptr
            case None => nullptr
        }
    }
}
