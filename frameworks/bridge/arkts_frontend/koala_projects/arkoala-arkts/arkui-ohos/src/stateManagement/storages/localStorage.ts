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

import { NullableObject } from '../base/types';
import { AbstractProperty, SubscribedAbstractProperty } from '../base/decoratorBase';

import { __MkPropReturnType, StateDecoratedVariable } from '../decorators/decoratorState';
import { LinkDecoratedVariable } from '../decorators/decoratorLink';
import { PropDecoratedVariable } from '../decorators/decoratorProp';
import { WatchIdType } from '../decorators/decoratorWatch';

import { int32 } from '@koalaui/common';

type StorageLinkPropIdType = int32;

interface StorageLinkPropRegistration {
    id: StorageLinkPropIdType;
    propName: string;
    watchIdToKeepPropUpdated?: WatchIdType
}

export class LocalStorage {
    private storage_: Map<string, StateDecoratedVariable<NullableObject>>;
    private nextLinkPropId: StorageLinkPropIdType = 1;
    private linkPropRegistrations_: Map<string, Set<StorageLinkPropIdType>> =
        new Map<string, Set<StorageLinkPropIdType>>();

    constructor() {
        this.storage_ = new Map<string, StateDecoratedVariable<NullableObject>>();
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
        const p: StateDecoratedVariable<NullableObject> | undefined = this.storage_.get(propName);
        return p ? p!.get() as T : undefined;
    }

    public set<T>(propName: string, newValue: T): boolean {
        const p: StateDecoratedVariable<NullableObject> | undefined = 
            this.storage_.get(propName);
        if (p === undefined) {
            return false;
        }
        p!.set(newValue as NullableObject);
        return true;
    }

    public setOrCreate<T>(propName: string, newValue: T): boolean {
        const p: StateDecoratedVariable<NullableObject> | undefined = this.storage_.get(propName);
        if (p !== undefined) {
            p!.set(newValue as NullableObject);
            return true;
        }
        this.addNewPropertyInternal<T>(propName, newValue);
        return true;
    }

    private addNewPropertyInternal<T>(propName: string, value: T): StateDecoratedVariable<NullableObject> {
        const newProp = new StateDecoratedVariable<NullableObject>(propName, value as NullableObject);
        this.storage_.set(propName, newProp);
        return newProp;
    }

    public ref<T>(propName: string): AbstractProperty<T> | undefined {
        const p: StateDecoratedVariable<NullableObject> | undefined = this.storage_.get(propName);
        if (p === undefined) {
          return undefined;
        }
        let ref = this.linkInternalAbstractProperty(propName, p!);
        return ref as AbstractProperty<NullableObject> as AbstractProperty<T>;
    }
    
    public setAndRef<T>(propName: string, defaultValue: T): AbstractProperty<T> {
        let p: StateDecoratedVariable<NullableObject> | undefined = this.storage_.get(propName);
        if (p === undefined) {
            p = this.addNewPropertyInternal<T>(propName, defaultValue);
        }
        let ref = this.linkInternalAbstractProperty(propName, p!);
        return ref as AbstractProperty<NullableObject> as AbstractProperty<T>;
    }

    public link<T>(propName: string): SubscribedAbstractProperty<T> | undefined {
        const p: StateDecoratedVariable<NullableObject> | undefined = this.storage_.get(propName);
        if (p === undefined) {
          return undefined;
        }
        return this.linkInternalAbstractProperty(propName, p!) as SubscribedAbstractProperty<T>;
    }
    
    public setAndLink<T>(propName: string, defaultValue: T): SubscribedAbstractProperty<T> {
        let p: StateDecoratedVariable<NullableObject> | undefined = this.storage_.get(propName);
        if (p === undefined) {
            p = this.addNewPropertyInternal<T>(propName, defaultValue);
        }
        return this.linkInternalAbstractProperty(propName, p!) as SubscribedAbstractProperty<T>;
    }
    
    public createLink<T>(propName: string, defaultValue: T): LinkDecoratedVariable<NullableObject> {
        let p: StateDecoratedVariable<NullableObject> | undefined = this.storage_.get(propName);
        if (p === undefined) {
            p = this.addNewPropertyInternal<T>(propName, defaultValue);
        }
        return this.linkInternal(propName, p!)!;
    }

    private linkInternalAbstractProperty<T>(propName: string, p: StateDecoratedVariable<T>): 
        SubscribedAbstractProperty<T> {
        return this.linkInternal(propName, p!) as SubscribedAbstractProperty<T>;
    }

    private linkInternal<T>(propName: string, p: StateDecoratedVariable<T>): LinkDecoratedVariable<T> {
        const link: LinkDecoratedVariable<T> = p.mkLink(propName);
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

    public prop<T>(propName: string): SubscribedAbstractProperty<T> | undefined {
        const p: StateDecoratedVariable<NullableObject> | undefined = this.storage_.get(propName);
        if (p === undefined) {
            return undefined;
        }
        return this.propInternalAbstractProperty(propName, p!) as SubscribedAbstractProperty<T>;
    }

    public setAndProp<T>(propName: string, defaultValue: T): SubscribedAbstractProperty<T> {
        let p: StateDecoratedVariable<NullableObject> | undefined = this.storage_.get(propName);
        if (p === undefined) {
            p = this.addNewPropertyInternal<T>(propName, defaultValue);
        }
        return this.propInternalAbstractProperty(propName, p) as SubscribedAbstractProperty<T>;
    }

    public createProp<T>(propName: string, defaultValue: T): PropDecoratedVariable<NullableObject> {
        let p: StateDecoratedVariable<NullableObject> | undefined = this.storage_.get(propName);
        if (p === undefined) {
            p = this.addNewPropertyInternal<T>(propName, defaultValue);
        }
        return this.propInternal(propName, p);
    }

    private propInternalAbstractProperty<T>(propName: string, p: StateDecoratedVariable<T>): 
        SubscribedAbstractProperty<T> {
        return this.propInternal(propName, p!) as SubscribedAbstractProperty<T>;
    }

    private propInternal<T>(propName: string, p: StateDecoratedVariable<T>): PropDecoratedVariable<T> {
        const result: __MkPropReturnType<T> = p.mkProp(propName);
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
        let p: StateDecoratedVariable<NullableObject> | undefined = this.storage_.get(propName);
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