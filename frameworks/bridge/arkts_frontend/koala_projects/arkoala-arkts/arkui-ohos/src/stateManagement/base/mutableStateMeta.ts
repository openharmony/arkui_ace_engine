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
import { MutableState, mutableState } from '@koalaui/runtime';


class MutableStateMetaBase {
    public readonly decorator: string;

    constructor(decorator: string) {
        this.decorator = decorator;
    }
}


/**
* manage one meta MutableState
* 
* V2 equivalent: sym_ref entry for particular property called 'propName'
* addRef(obj, propName) records dependency, 
* fireChange(obj, propName) marks all dependencies for this prop need update
*/
export class MutableStateMeta extends MutableStateMetaBase {
    // meta MutableState to record dependencies in addRef
    // and mutate in fireChange
    private __metaDependency: MutableState<int32> = mutableState<int32>(0);

    constructor(decorator: string) {
        super(decorator);
    }

    public addRef(): void {
        this.__metaDependency.value;
    }

    public fireChange(): void {
        this.__metaDependency.value += 1;
    }
}

/**
* manage several meta MutableState
* This class is used by WrappedArray/Map/Set
* to record dependency for each Array item, map, Set entry
* 
* V2 equivalent: sym_ref sub-object
* addRef(obj, propName) records dependency on given propName
* fireChange(obj, propName) marks all dependencies for this prop need update
*/
export class MutableKeyedStateMeta extends MutableStateMetaBase {
    public static readonly OB_LENGTH = "__OB_LENGTH";
    private readonly __metaDependencies = new Map<string, MutableState<int32>>();


    public addRef(key: string): void {
        let metaDependency: MutableState<int32> | undefined = this.__metaDependencies.get(key);
        if (!metaDependency) {
            metaDependency = mutableState<int32>(0);
            this.__metaDependencies.set(key, metaDependency);
        }
        metaDependency.value;
    }

    public fireChange(key: string): void {
        let metaDependency: MutableState<int32> | undefined = this.__metaDependencies.get(key);
        if (metaDependency) {
            metaDependency.value += 1;
        }
    }

    constructor(decorator: string) {
        super(decorator);
    }
}