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

/*
    When decorating variables of complex types,
    @Prop makes a deep copy, during which all types,
    except primitive types, Map, Set, Date, and Array, will be lost.
 */
import { getObservableTarget } from './observable.ts'

export function propDeepCopy<T>(sourceObject: T): T {
    // at the moment of intergation deepcopy from the stdlib requires a default constructor
    // but default constructor is not available for ObservableDate, so we
    // add a special case for Date (a parent for ObservableDate)
    if (sourceObject instanceof Date) {
        const copy: Date = new Date(sourceObject.valueOf());
        return copy as T;
    }
    return deepcopy<T>(getObservableTarget(sourceObject as Object) as T) as T
}
