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

object MaterializedBaseTag {
    val NOP = MaterializedBaseTag
}

public interface MaterializedBase {
    public fun getPeer(): Finalizable?
    public companion object {    
        public fun toPeerPtr(value: Any): KPointer
        {
            if (value is MaterializedBase) {
                val peer = value.getPeer() 
                if (peer != null) {
                    return peer.ptr
                } else {
                    return nullptr
                }
            } else {
                throw Exception("Value is not a MaterializedBase instance!")
            }
        }
    }    
}
