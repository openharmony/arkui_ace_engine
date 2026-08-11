/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

package idlize

import Interop.*
import std.collection.*

%NATIVE_MODULE_CONTENT%

foreign {
%NATIVE_FUNCTIONS%
}

public class %NATIVE_MODULE_NAME%NativeModule {
    static func callCallbackFromNative(id: KInt, args: KPointer, length: KInt): KInt {
        // Improve: implement callCallbackFromNative
        return 0
    }    

%CJ_NATIVE_FUNCTIONS%
}
