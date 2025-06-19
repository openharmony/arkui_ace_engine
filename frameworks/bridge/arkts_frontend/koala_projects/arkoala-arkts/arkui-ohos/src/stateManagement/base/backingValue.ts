/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
 
/**
  skeleton of a class to support 
  versioning of backing store values
*/

export class BackingValue<T> {
    private current_ : T;

    constructor(initValue : T) {
        this.current_ = initValue;
    }

    public get value() : T {
        return this.current_;
    }
    public set value(newValue : T) {
        this.current_ = newValue;
    }
}