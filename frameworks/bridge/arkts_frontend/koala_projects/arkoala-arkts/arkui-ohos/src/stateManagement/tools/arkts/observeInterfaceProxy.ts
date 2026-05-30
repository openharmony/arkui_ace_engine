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
import { IMutableStateMeta, IMutableKeyedStateMeta } from '../../decorator';
import { STATE_MGMT_FACTORY } from '../../decorator';
import { OBSERVE } from '../../decorator';
import { NullableObject } from '../../base/types';
import { UIUtils } from '../../utils';
import { uiUtils } from '../../base/uiUtilsImpl';
import { FactoryInternal } from '../../base/iFactoryInternal';

export class InterfaceProxyHandler implements reflect.InvocationHandler, IObservedObject, ISubscribedWatches, JsonSerializable {
    private __meta: IMutableStateMeta | undefined;
    private __keyedMeta: IMutableKeyedStateMeta | undefined;
    private subscribedWatches: SubscribedWatches = new SubscribedWatches();
    private allowDeep_: boolean;
    private _target: Object;
    private isAPI_: boolean;
    private readonly skipSymbol: string = '__observeInterfaceProxy_skipsymbol_Internal';
    private static readonly TO_JSON_METHOD: string = 'toJSON';
    constructor(target: Object, allowDeep: boolean, isAPI: boolean) {
        this._target = target;
        this.allowDeep_ = allowDeep;
        this.isAPI_ = isAPI;
        if (this.isAPI_) {
            this.__keyedMeta = FactoryInternal.mkMutableKeyedStateMeta(
                '__metaInterfaceMakeObserved_', this);
        } else {
            this.__meta = STATE_MGMT_FACTORY.makeMutableStateMeta(this,
                this.allowDeep_ ? '__metaInterfaceMakeObserved_' : '__metaInterfaceV1_');
        }
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
    public setV1RenderId(renderId: RenderIdType): void {}
    public shouldAddRef(): boolean {
        return OBSERVE.renderingComponent > 0;
    }
    public override toJSON(): string {
        return JSON.stringify(this.toJSONObject());
    }
    public toJSONObject(): Record<string, Object> {
        const result: Record<string, Object> = {};
        const targetType = Class.of(this._target);
        const visited = new Set<string>();
        const getterPrefix = '%%get-';
        const getterPrefixLength = getterPrefix.length;
        for (let cls: Class | undefined = targetType; cls !== undefined; cls = cls!.getSuper()) {
            const methods = cls!.getInstanceMethods();
            for (const method of methods) {
                const methodName = method.getName();
                if (!methodName.startsWith(getterPrefix)) {
                    continue;
                }
                const varName = methodName.substring(getterPrefixLength);
                if (visited.has(varName)) {
                    continue;
                }
                visited.add(varName);
                const observedValue = this.getValue(varName);
                if (observedValue !== this.skipSymbol) {
                    result[varName] = observedValue;
                }
            }
        }
        return result;
    }
    public getValue(varName: string): Object {
        const getterPrefix = '%%get-';
        const targetType = Class.of(this._target);
        const getter = targetType.getInstanceMethod(getterPrefix + varName);
        if (!getter) {
            return this.skipSymbol as Object;
        }
        const value = getter.invoke(this._target, []);
        if (typeof value !== 'function' && this.shouldAddRef()) {
            if (this.isAPI_) {
                this.__keyedMeta!.addRef(varName);
            } else {
                this.__meta!.addRef();
            }
        }
        return uiUtils.makeObservedEntrance(value, this.allowDeep_, this.isAPI_) as Object;
    }
    get(target: Object, method: reflect.InstanceMethod): Any {
        const value = method.invoke(this._target);
        const varName = method.getName().substring(6);
        if (typeof value !== 'function' && this.shouldAddRef()) {
            if (this.isAPI_) {
                this.__keyedMeta!.addRef(varName);
            } else {
                this.__meta!.addRef();
            }
        }
        const makeObserved = uiUtils.makeObservedEntrance(value, this.allowDeep_, this.isAPI_);
        if (makeObserved === value) {
            return value;
        }
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
                if (this.isAPI_) {
                    this.__keyedMeta!.fireChange(varName);
                } else {
                    this.__meta!.fireChange();
                }
                this.executeOnSubscribingWatches(varName);
            }
        } catch (e) {
            console.log(e);
        }
    }
    invoke(target: Object, method: reflect.InstanceMethod, args: FixedArray<Any>): Any {
        if (method.getName() === InterfaceProxyHandler.TO_JSON_METHOD) {
            return this.toJSON();
        }
        return method.invoke(this._target, args);
    }
    get target(): Object {
        return this._target;
    }
}
