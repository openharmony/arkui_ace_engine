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
import { ExtendableComponent } from '../../component/extendableComponent';
import { DecoratedV1VariableBase } from './decoratorBase';
import { IDecoratedV1Variable, WatchFuncType } from '../decorator';
import { ILinkDecoratedVariable } from '../decorator';
import { ObserveSingleton } from '../base/observeSingleton';
import { NullableObject } from '../base/types';
import { UIUtils } from '../utils';

/**
 * implementation of V1 @Link
 *
 * must no have local init
 * must have source of same type
 * source most be a Decorated variable
 * source is allowed to be immutable (@ObjectLink),
 *   when the unsolved issues arises that a set on @Link has no effect
 * @Link reads-through from source, and if source mutable also writes-through
 * to source. Therefore, source meta.addRef and meta.fireChange is enough to
 * manage dependencies of the @link: LinkDecoratedVariable does not use its meta
 */
export class LinkDecoratedVariable<T> extends DecoratedV1VariableBase<T> implements ILinkDecoratedVariable<T> {
    private readonly sourceGet_: () => T;
    private readonly sourceSet_?: (newValue: T) => void;

    // localInitValue is the rhs of @state variable : type = localInitialValue;
    // caller ensure it is IObseredObject, eg. by wrapping
    constructor(
        owningView: ExtendableComponent | null,
        varName: string,
        source: IDecoratedV1Variable<T>,
        sourceGet: () => T,
        sourceSet: (newValue: T) => void,
        watchFunc?: WatchFuncType
    ) {
        super('@Link', owningView, varName, watchFunc);
        const initValue = sourceGet();
        this.sourceGet_ = sourceGet;
        this.sourceSet_ = sourceSet;

        if (source instanceof LinkDecoratedVariable) {
            this.source_ = source.getSource();
        } else {
            this.source_ = source;
        }
        // @Watch
        // if initial value is object, register so that property changes trigger
        // @Watch function exec
        this.registerWatchForObservedObjectChanges(initValue);
        // registerWatchtoSource is done in factory
    }

    public getInfo(): string {
        return `@Link ${this.varName} (LinkDecoratedVariable)`;
    }

    public get(): T {
        const value = this.sourceGet_();
        // @Link V1: if this.__value instanceof IObservedObject limit permissible addRef depth to 1
        ObserveSingleton.instance.setV1RenderId(value as NullableObject);

        // a @Link get triggers a meta.addRef of the Link source XXXXDecoratedVariable
        // therefore, when the source changes (its meta.fireChabge), the bindings using
        // the @Link also update
        // source will trigger also update
        return value;
    }

    public set(newValue: T): void {
        const oldValue = this.sourceGet_();
        if (oldValue !== newValue) {
            if (this.sourceSet_ === undefined) {
                throw new Error(`${this.getInfo()}: Can not set @Link value. @Link source is immutable error.`);
            }
            const value = UIUtils.makeObserved(newValue);
            // @Watch
            // if new value is object, register so that property changes trigger
            // Watch function exec
            // unregister if old value is an object
            this.unregisterWatchFromObservedObjectChanges(oldValue);
            this.registerWatchForObservedObjectChanges(value);
            // a @Link set  truggers a meta.fireChange on the source XXXDecoratedVariable
            // set also get above.
            this.sourceSet_!(value);
        }
    }

    private source_: IDecoratedV1Variable<T>;

    public getSource(): IDecoratedV1Variable<T> {
        return this.source_;
    }
}
