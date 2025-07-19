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

export class InterfaceProxyHandler<T extends Object>
    implements proxy.ProxyHandler<T>, IObservedObject, ISubscribedWatches
{
    private readonly __meta: IMutableStateMeta = STATE_MGMT_FACTORY.makeMutableStateMeta();

    private subscribedWatches: SubscribedWatches = new SubscribedWatches();
    public addWatchSubscriber(watchId: WatchIdType): void {
        this.subscribedWatches.addWatchSubscriber(watchId);
    }
    public removeWatchSubscriber(watchId: WatchIdType): boolean {
        return this.subscribedWatches.removeWatchSubscriber(watchId);
    }

    public executeOnSubscribingWatches(propertyName: string): void {
        this.subscribedWatches.executeOnSubscribingWatches(propertyName);
    }

    private ____V1RenderId: RenderIdType = 0;
    public setV1RenderId(renderId: RenderIdType): void {
        this.____V1RenderId = renderId;
    }
    public shouldAddRef(): boolean {
        return OBSERVE.shouldAddRef(this.____V1RenderId);
    }
    public get(target: T, name: string): Any {
        const value = Reflect.get(target, name) as Any;
        if (typeof value !== 'function' && this.shouldAddRef()) {
            this.__meta.addRef();
        }
        return UIUtils.makeObserved(value);
    }
    public set(target: T, name: string, newValue: Any): boolean {
        if (Reflect.get(target, name) !== newValue) {
            const result = Reflect.set(target, name, newValue);
            this.__meta.fireChange();
            this.executeOnSubscribingWatches(name);
            return result;
        }
        return true;
    }

    public invoke(target: T, method: Method, args: FixedArray<Any>): Any {
        return method.invoke(target, args);
    }
}
