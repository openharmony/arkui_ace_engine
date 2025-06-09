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
import { IMutableStateMeta, IMutableKeyedStateMeta } from '../decorator';
import { RenderIdType } from '../decorator';
import { ObserveSingleton } from './observeSingleton';
import { StateMgmtConsole } from '../tools/stateMgmtDFX';

class MutableStateMetaBase {
    public readonly info_: string;

    constructor(info: string) {
        this.info_ = info;
    }
}

export interface IBindingSource {
    clearBinding(id: RenderIdType): void;
}
/**
* manage one meta MutableState
* 
* V2 equivalent: sym_ref entry for particular property called 'propName'
* addRef(obj, propName) records dependency, 
* fireChange(obj, propName) marks all dependencies for this prop need update
*/
export class MutableStateMeta extends MutableStateMetaBase implements IMutableStateMeta, IBindingSource {
    // meta MutableState to record dependencies in addRef
    // and mutate in fireChange
    protected __metaDependency: MutableState<int32> = mutableState<int32>(0);
    private bindings_?: Set<RenderIdType>;

    constructor(info: string) {
        super(info);
    }

    public addRef(): void {
        if (false) {
            // for Monitor & Computed
        } else {
            this.__metaDependency!.value;
        }
    }

    public fireChange(): void {
        if (this.bindings_) {
            // for Monitor & Computed
        }
        this.__metaDependency!.value += 1;
    }

    clearBinding(id: RenderIdType): void {
        this.bindings_?.delete(id);
    }
}

export class MutableKeyedStateMeta extends MutableStateMetaBase
    implements IMutableKeyedStateMeta {

    protected readonly __metaDependencies = new Map<string, MutableStateMeta>();

    constructor(info: string = "") {
        super(info);
    }

    public addRef(key: string): void {
        let metaDependency: MutableStateMeta | undefined = this.__metaDependencies.get(key);
        if (!metaDependency) {
            metaDependency = new MutableStateMeta(key); // incremental engine does not allow create mutableState while building tree
            this.__metaDependencies.set(key, metaDependency);
        }
        metaDependency.addRef();
    }

    // public addRef(index: int32): void {
    //     // FIXME is there a faster way to convert int32 to string?
    //     this.addRef(String(index));
    // }

    public fireChange(key: string): void {
        let metaDependency: MutableStateMeta | undefined = this.__metaDependencies.get(key);
        if (metaDependency) {
            metaDependency.fireChange();
        }
    }

    // public fireChange(index: int32): void {
    //     // FIXME is there a faster way to convert int32 to string?
    //     this.fireChange(String(index));
    // }
}