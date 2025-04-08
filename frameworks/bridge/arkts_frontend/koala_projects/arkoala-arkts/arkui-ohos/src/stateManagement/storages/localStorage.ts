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
import { WatchIdType } from '../decorators/decoratorWatch';
import { __MkPropReturnType, StateDecoratedVariable } from '../decorators/decoratorState';
import { LinkDecoratedVariable } from '../decorators/decoratorLink';
import { PropDecoratedVariable } from '../decorators/decoratorProp';

type StorageLinkPropIdType = int32;

interface StorageLinkPropRegistration {
    id: StorageLinkPropIdType;
    propName: string;
    watchIdToKeepPropUpdated?: WatchIdType
}

export class LocalStorage {
    private storage_: Map<string, StateDecoratedVariable<Object>>;
    private nextLinkPropId: StorageLinkPropIdType = 1;
    private linkPropRegistrations_: Map<string, Set<StorageLinkPropIdType>> =
        new Map<string, Set<StorageLinkPropIdType>>();

    constructor() {
        this.storage_ = new Map<string, StateDecoratedVariable<Object>>();
    }
    
    private getInfo(): string {
        return '@LocalStorage';
    }

    public has(propName: string): boolean {
        return this.storage_.has(propName);
    }

    public keys(): IterableIterator<string> {
        return this.storage_.keys();
    }

    public size(): number {
        return this.storage_.size;
    }

    public get<T>(propName: string): T | undefined {
        const p: StateDecoratedVariable<Object> | undefined = this.storage_.get(propName);
        return p ? p!.get() as T : undefined;
    }

    public set<T>(propName: string, newValue: T): boolean {
        const p: StateDecoratedVariable<Object> | undefined = 
            this.storage_.get(propName);
        if (p === undefined) {
            return false;
        }
        p!.set(newValue as Object);
        return true;
    }

    public setOrCreate<T>(propName: string, newValue: T): boolean {
        const p: StateDecoratedVariable<Object> | undefined = this.storage_.get(propName);
        if (p !== undefined) {
            p!.set(newValue as Object);
            return true;
        }
        this.addNewPropertyInternal(propName, newValue as Object);
        return true;
    }

    private addNewPropertyInternal(propName: string, value: Object): StateDecoratedVariable<Object> {
        const newProp = new StateDecoratedVariable<Object>(propName, value);
        this.storage_.set(propName, newProp);
        return newProp;
    }

    public link(propName: string): LinkDecoratedVariable<Object> | undefined {
        const p: StateDecoratedVariable<Object> | undefined = this.storage_.get(propName);
        if (p === undefined) {
          return undefined;
        }
        return this.linkInternal(p!, propName);
    }
    
    public setAndLink(propName: string, defaultValue: Object): LinkDecoratedVariable<Object> {
        let p: StateDecoratedVariable<Object> | undefined = this.storage_.get(propName);
        if (p === undefined) {
            p = this.addNewPropertyInternal(propName, defaultValue);
        }
        return this.linkInternal(p!, propName)!;
    }

    private linkInternal(p: StateDecoratedVariable<Object>, propName: string): LinkDecoratedVariable<Object> {
        const link: LinkDecoratedVariable<Object> = p.mkLink(propName);
        const id = this.nextLinkPropId++;
        let reg = this.linkPropRegistrations_.get(propName);
        if (reg === undefined) {
            reg = new Set<StorageLinkPropIdType>();
            this.linkPropRegistrations_.set(propName, reg);
        }
        reg!.add(id);
        // why no used here
        const regEntry: StorageLinkPropRegistration = { propName: propName, id: id };
        return link;
    }

    public prop(propName: string): PropDecoratedVariable<Object> | undefined {
        const p: StateDecoratedVariable<Object> | undefined = this.storage_.get(propName);
        if (p === undefined) {
            return undefined;
        }
        return this.propInternal(propName, p!);
    }

    public setAndProp(propName: string, defaultValue: Object): PropDecoratedVariable<Object> {
        let p: StateDecoratedVariable<Object> | undefined = this.storage_.get(propName);
        if (p === undefined) {
            p = this.addNewPropertyInternal(propName, defaultValue);
        }
        return this.propInternal(propName, p);
    }


    private propInternal(propName: string, p: StateDecoratedVariable<Object>): PropDecoratedVariable<Object> {
        const result: __MkPropReturnType<Object> = p.mkProp(propName);
        const prop = result.prop;
        
        const id = this.nextLinkPropId++;
        let reg = this.linkPropRegistrations_.get(propName)
        if (reg === undefined) {
            reg = new Set<StorageLinkPropIdType>();
            this.linkPropRegistrations_.set(propName, reg);
        }
        reg.add(id);
        return prop;
    }

    public delete(propName: string): boolean {
        let p: StateDecoratedVariable<Object> | undefined = this.storage_.get(propName);
        if (p === undefined) {
            return false;
        }

        const registrations = this.linkPropRegistrations_.get(propName);
        if (registrations && registrations.size > 0) {
            return false;
        }

        // can delete
        this.linkPropRegistrations_.delete(propName);
        this.storage_.delete(propName);
        return true;
    }

    protected clear(): boolean {
        if (this.linkPropRegistrations_.size > 0) {
            for (let propName of this.keys()) {
                if ((this.linkPropRegistrations_.get(propName) !== undefined)
                    && (this.linkPropRegistrations_.get(propName)!.size > 0)) {
                    return false;
                }
            }
        }
        this.storage_.clear();
        this.linkPropRegistrations_.clear();
        return true;
    }    
}