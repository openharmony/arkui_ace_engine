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
import { WatchIdType } from '../decorator';
import { int32 } from '@koalaui/common';
import { WatchFunc } from '../decoratorImpl/decoratorWatch';

export class StateUpdateLoop {
    private static callbacks: Array<() => void> = new Array<() => void>();
    // This task is for freezing the watch
    private static activeTasks: Map<int32, Set<WatchIdType>> = new Map<int32, Set<WatchIdType>>();
    public static canRequestFrame: boolean = true;
    public static add(callback: () => void): void {
        StateUpdateLoop.callbacks.push(callback);
    }
    public static addFreezeTask(peerId: int32, watchId: WatchIdType): void {
        let taskSet = StateUpdateLoop.activeTasks.get(peerId);
        if (!taskSet) {
            taskSet = new Set<WatchIdType>();
        }
        taskSet.add(watchId);
        StateUpdateLoop.activeTasks.set(peerId, taskSet);
    }
    public static consume(): void {
        StateUpdateLoop.callbacks.forEach((callback: () => void) => {
            callback();
        });
        StateUpdateLoop.callbacks.length = 0;
    }
    public static consumeFreezeTasks(peerId: int32): void {
        const taskSet = StateUpdateLoop.activeTasks.get(peerId);
        if (!taskSet) {
            return;
        }
        taskSet.forEach((watchId: WatchIdType) => {
            // This property name does not affect the actual property name.
            WatchFunc.execWatchById(watchId, '');
        });
        taskSet.clear();
        StateUpdateLoop.activeTasks.delete(peerId);
    }
    public static clearFreezeTaskWhenReuse(peerId: int32): void {
        StateUpdateLoop.activeTasks.get(peerId)?.clear();
    }
    public static get len(): number {
        return StateUpdateLoop.callbacks.length;
    }
}
