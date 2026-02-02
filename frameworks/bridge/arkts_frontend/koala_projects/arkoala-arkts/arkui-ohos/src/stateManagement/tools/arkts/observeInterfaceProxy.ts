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

import { WatchIdType, ISubscribedWatches } from '../../decorator';
import { IObservedObject, RenderIdType } from '../../decorator';
import { SubscribedWatches } from '../../decoratorImpl/decoratorWatch';
import { IMutableStateMeta } from '../../decorator';
import { STATE_MGMT_FACTORY } from '../../decorator';
import { OBSERVE } from '../../decorator';
import { NullableObject } from '../../base/types';
import { UIUtils } from '../../utils';
import { uiUtils } from '../../base/uiUtilsImpl';

export class InterfaceProxyHandler implements reflect.InvocationHandler, IObservedObject, ISubscribedWatches {
    private readonly __meta: IMutableStateMeta = STATE_MGMT_FACTORY.makeMutableStateMeta();
    private subscribedWatches: SubscribedWatches = new SubscribedWatches();
    private ____V1RenderId: RenderIdType = 0;
    private allowDeep_: boolean;
    private _target: Object;
    private isAPI_: boolean;
    constructor(target: Object, allowDeep: boolean, isAPI: boolean) {
        this._target = target;
        this.allowDeep_ = allowDeep;
        this.isAPI_ = isAPI;
    }
    public addWatchSubscriber(watchId: WatchIdType): void {
        this.subscribedWatches.addWatchSubscriber(watchId);
    }
    public removeWatchSubscriber(watchId: WatchIdType): boolean {
        return this.subscribedWatches.removeWatchSubscriber(watchId);
    }
    public executeOnSubscribingWatches(propertyName: string): void {
        this.subscribedWatches.executeOnSubscribingWatches(propertyName);
    }
    public setV1RenderId(renderId: RenderIdType): void {
        this.____V1RenderId = renderId;
    }
    public shouldAddRef(): boolean {
        return this.allowDeep_ || OBSERVE.shouldAddRef(this.____V1RenderId);
    }
    get(target: Object, method: reflect.InstanceMethod): Any {
        const value = method.invoke(this._target);
        if (typeof value !== 'function' && this.shouldAddRef()) {
            this.__meta.addRef();
        }
        const makeObserved = uiUtils.makeObservedEntrance(value, this.allowDeep_, this.isAPI_);
        if (makeObserved === value) {
            return value;
        }
        const varName = method.getName().substring(6);
        const SETTER_PREFIX = '%%set-';
        const targetType = Class.of(this._target);
        try {
            const setter = targetType.getInstanceMethod(SETTER_PREFIX + varName);
            if (setter) {
                setter.invoke(this._target, [makeObserved]);
            }
        } catch (e) {
            console.log(e);
        }
        return makeObserved;
    }
    set (target: Object, method: reflect.InstanceMethod, newValue: Any): void {
        const varName = method.getName().substring(6);
        const GETTER_PREFIX = '%%get-';
        const targetType = Class.of(this._target);
        try {
            const getter = targetType.getInstanceMethod(GETTER_PREFIX + varName);
            if (getter && getter.invoke(this._target, []) !== newValue) {
                method.invoke(this._target, [newValue]);
                this.__meta.fireChange();
                this.executeOnSubscribingWatches(varName);
            }
        } catch (e) {
            console.log(e);
        }
    }

    invoke(target: Object, method: reflect.InstanceMethod, args: FixedArray<Any>): Any {
        return method.invoke(this._target, args);
    }

    get target(): Object {
        return this._target;
    }
}
