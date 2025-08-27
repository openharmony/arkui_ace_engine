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

import { int32 } from '@koalaui/common';
import { IWatchTrigger } from '../decorators/decoratorWatch';
import { TypeChecker } from '#components';

// All classes implement this interface whose objects can be observed 
export interface IObservedObject extends IWatchTrigger {
    _permissibleAddRefDepth: int32;
}

/** 
* same as dynamic_cast lib C++
* if given value is observed object, cast it 
* otherwise return undefined. 
* given a value of any type
* if value is instance of class that implements IO
*/
export function castToIObservedObject<T>(obj: T): IObservedObject | undefined {
    return (obj && typeof obj === 'object' && TypeChecker.isIObservedObject(obj))
        ? (obj as Object as  IObservedObject)
        : undefined;
}


/**
* The helper function sets the observation depth in given `IObservedObject`
*/
export function setObservationDepth<T>(obj: T, depth: int32): void {
    const objOpt = castToIObservedObject(obj);
    if (objOpt) {
        objOpt._permissibleAddRefDepth = depth;
    }
}