/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
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

@Observed
class ObservedParent {
    initialized: number = 4
    lazy: string
    constructor() {
        this.lazy = "set in constructor"
    }
}

class NonObserved<T> extends ObservedParent {
    @Track
    protected parent: ObservedParent = new ObservedParent()
    private untraceable: string = "do not notify on modify"
}

// If there is at least one @Track property in a class,
// then we do not convert all other properties to states,
// even if this class is @Observed

@Observed
class TrackWithinObserved {
    @Track
    one: number = 1
    two: string = "do not notify on modify"
}
