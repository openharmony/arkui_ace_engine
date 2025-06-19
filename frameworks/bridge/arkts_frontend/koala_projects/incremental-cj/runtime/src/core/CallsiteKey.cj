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

import std.convert.*

public type CallsiteKey = UInt64

extend CallsiteKey {
    /**
     * @return text representation of the callsite key
     */
    public prop text: String {
        get() {
            format("016X")
        }
    }
}

foreign func return_address_3(): CallsiteKey

/**
 * @return the callsite key, which identifies a place where the outer function is called
 * @internal
 */
public func getCallsiteKey(): CallsiteKey {
    unsafe {
        return_address_3()
    }
}
