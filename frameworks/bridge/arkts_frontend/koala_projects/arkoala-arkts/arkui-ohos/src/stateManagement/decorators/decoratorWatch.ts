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
import { int32 } from "@koalaui/common";

export type WatchFuncType = ((propertyName: string) => void);

export type WatchIdType = int32;

// WatchFunc: Representaton of a @Watch function isnide V1 decorator class
export class WatchFunc {
    private static nextWatchId_: WatchIdType = 1;
    private static readonly watchId2WatchFunc: Map<WatchIdType, WatchFunc>
        = new Map<WatchIdType, WatchFunc>();
    private static readonly watchFinalizer: FinalizationRegistry<WatchIdType>
        = new FinalizationRegistry<WatchIdType>((watchId: WatchIdType) => {
            // remove @Watch id from watchId2WatchFunc Map to avoid memory growth
            WatchFunc.watchId2WatchFunc.delete(watchId);
        });

    /**
     * Execute @Watch with given WatchId
     * @param watchId 
     * @returns true if @Watch / WatchFunc with given id was found
     * otherwise false
     */
    public static execWatchById(watchId: WatchIdType, propertyName: string): boolean {
        const watchFuncOpt = WatchFunc.watchId2WatchFunc.get(watchId);
        if (watchFuncOpt) {
            watchFuncOpt!.execute(propertyName);
            return true;
        } else {
            return false;
        }
    }

    public func_: WatchFuncType;
    private readonly id_: WatchIdType;

    constructor(func: WatchFuncType) {
        this.id_ = WatchFunc.nextWatchId_++;
        WatchFunc.watchId2WatchFunc.set(this.id_, this);
        this.func_ = func;
        // when this instance gets GC'ed, unregister its id from 
        // static watchId2WatchFunc Map
        WatchFunc.watchFinalizer.register(this, this.id_);
    }

    public id() {
        return this.id_
    }

    // replace the watch function 
    // needed for mkProp
    public setFunc(newFunc : WatchFuncType) : void {
        this.func_ = newFunc;
    }

    // register to given object 
    // when object changes it will call Execute 
    // for each subscriber
    registerMeTo(obj: IWatchTrigger) {
        obj.addWatchSubscriber(this.id_);
    }
    unregisterMeFrom(obj: IWatchTrigger) {
        obj.removeWatchSubscriber(this.id_);
    }
    execute(propertyName: string): void {
        this.func_(propertyName);
    }
}

export interface IWatchTrigger {
    addWatchSubscriber(watchId: WatchIdType): void;
    removeWatchSubscriber(watchId: WatchIdType): boolean;
    executeOnSubscribingWatches(propertyName: string): void;
}

// IObserveObject object instances also need to implement WatchTrigger
export class SubscribedWatches implements IWatchTrigger {
    private subscribers_: Set<WatchIdType> = new Set<WatchIdType>();
    public addWatchSubscriber(id: WatchIdType): void {
        this.subscribers_.add(id);
    }
    public removeWatchSubscriber(id: WatchIdType): boolean {
        return this.subscribers_.delete(id);
    }
    public executeOnSubscribingWatches(propertyName: string): void {
        Array.from(this.subscribers_).forEach((watchId: WatchIdType) => {
            if (!WatchFunc.execWatchById(watchId, propertyName)) {
                // lazy delete WatchIds from subscribers_ Set
                // whose watchId has been removed from watchId2WatchFunc by
                // watchFinalizer
                this.subscribers_.delete(watchId)
            }
        });
    }
}