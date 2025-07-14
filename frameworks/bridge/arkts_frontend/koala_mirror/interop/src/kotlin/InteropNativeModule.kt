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
package interop

public class InteropNativeModule {
    companion object {
        public fun _Malloc(length: Long): KPointer {
            return nullptr
        }
        fun _Free(data: KPointer) {
            
        }
        public fun _ReadByte(data: KPointer, index: Int, length: Int): Int {
            return 0
        }
        public fun _WriteByte(data: KPointer, index: Int, length: Int, value: Int) {
        }
        public fun _ManagedStringWrite(str1: String, arr: pointer, arg: Int): Int {
            return 0
        }
        public fun _Utf8ToString(data: KPointer, offset: Int, length: Int): String {
            return ""
        }
    }
}