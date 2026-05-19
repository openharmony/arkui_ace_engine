/*
 * Copyright (c) 2025-2026 Huawei Device Co., Ltd.
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

// ClassWithMapSet (commonClasses.ts) holds @Local Set<number> and @Local
// Map<string, number> properties. The class also implements IObservedAnyProp
// with paired __meta_set / __meta_map metas. These tests cover three paths
// per container, parameterized by isSync:
//
//   c.set, c.set.*, c.set.size
//   c.map, c.map.*, c.map.size
//
// Counts mirror the standalone Map/Set tests because the inner WrappedMap /
// WrappedSet keyed metas behave the same whether the container lives in a
// local variable or in an @Local class slot.

import { tsuite, tcase, test, eq } from './lib/testFramework'
import {
    IMonitor,
    IMonitorPathInfo,
    IMonitorDecoratedVariable,
    MonitorCallback,
} from '../decorator'
import { ClassWithMapSet } from './commonClasses'
import { ObserveSingleton } from '../base/observeSingleton';
import { STATE_MGMT_FACTORY } from '../decorator'

const StateMgmtFactory = STATE_MGMT_FACTORY;

const testMonitors_: Array<IMonitorDecoratedVariable> = new Array<IMonitorDecoratedVariable>();

function makeMonitorByMode(
    isSync: boolean,
    pathInfos: IMonitorPathInfo[],
    onChanged: MonitorCallback,
): IMonitorDecoratedVariable {
    const m = isSync
        ? STATE_MGMT_FACTORY.makeSyncMonitor(pathInfos, onChanged, undefined)
        : STATE_MGMT_FACTORY.makeMonitor(pathInfos, onChanged);
    testMonitors_.push(m);
    return m;
}

// === path 'c.set' =========================================================

// Identity lambda: lambda returns `c.set` without calling a getter on the
// inner WrappedSet, so no per-value or LENGTH meta is bound. Inner Set
// mutations queue dirty refs only on metas the monitor isn't bound to.
function doMonitorOnClassSetIdentityLambdaNoFire(isSync: boolean): void {
    const tag = isSync ? 'sync' : 'async';
    let count: int = 0;
    const c = new ClassWithMapSet();

    const _monitor = makeMonitorByMode(
        isSync,
        [{
            path: 'c.set',
            valueCallback: () => c.set,
            enableWildcard: false } as IMonitorPathInfo
        ] as IMonitorPathInfo[],
        (m: IMonitor): void => {
            count++;
            console.log(`Monitor[${tag}] 'c.set' triggered: count=${count} dirty=${JSON.stringify(m.dirty)}`);
        },
    );

    c.set.add(1);
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] c.set identity: add new value does not fire: count=${count} === 0`, eq(count, 0));

    c.set.add(1); // already present
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] c.set identity: add existing value does not fire: count=${count} === 0`, eq(count, 0));

    c.set.delete(1);
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] c.set identity: delete does not fire: count=${count} === 0`, eq(count, 0));

    c.set.add(2);
    c.set.clear();
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] c.set identity: clear does not fire: count=${count} === 0`, eq(count, 0));
}

// === path 'c.set.*' =======================================================

// Wildcard. `c.set` returns the WrappedSet; addRefAnyKey() binds OB_LENGTH
// AND OB_SET_ANY_PROPERTY on the inner keyed-meta. Inner add/delete/clear
// each fire exactly once per logical mutation thanks to fireChangeBatch.
function doMonitorOnClassSetWildcardFiresOncePerMutation(isSync: boolean): void {
    const tag = isSync ? 'sync' : 'async';
    let count: int = 0;
    const c = new ClassWithMapSet();

    const _monitor = makeMonitorByMode(
        isSync,
        [{
            path: 'c.set.*',
            valueCallback: () => c.set,
            enableWildcard: true } as IMonitorPathInfo
        ] as IMonitorPathInfo[],
        (m: IMonitor): void => {
            count++;
            console.log(`Monitor[${tag}] 'c.set.*' triggered: count=${count} dirty=${JSON.stringify(m.dirty)}`);
        },
    );

    c.set.add(1);
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] c.set wildcard: add new value fires once: count=${count} === 1`, eq(count, 1));

    c.set.add(2);
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] c.set wildcard: add second new value fires once: count=${count} === 2`, eq(count, 2));

    c.set.add(1); // already present — no fire
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] c.set wildcard: add existing value does not fire: count=${count} === 2`, eq(count, 2));

    c.set.delete(1);
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] c.set wildcard: delete fires once: count=${count} === 3`, eq(count, 3));

    c.set.delete(99); // not present — no fire
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] c.set wildcard: delete non-existent value does not fire: count=${count} === 3`, eq(count, 3));

    c.set.clear();
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] c.set wildcard: clear fires once: count=${count} === 4`, eq(count, 4));

    c.set.clear(); // empty — no fire
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] c.set wildcard: clear on empty set does not fire: count=${count} === 4`, eq(count, 4));
}

// === path 'c.set.size' ====================================================

function doMonitorOnClassSetSize(isSync: boolean): void {
    const tag = isSync ? 'sync' : 'async';
    let count: int = 0;
    const c = new ClassWithMapSet();

    const _monitor = makeMonitorByMode(
        isSync,
        [{
            path: 'c.set.size',
            valueCallback: () => c.set.size,
            enableWildcard: false } as IMonitorPathInfo
        ] as IMonitorPathInfo[],
        (m: IMonitor): void => {
            count++;
            console.log(`Monitor[${tag}] 'c.set.size' triggered: count=${count} dirty=${JSON.stringify(m.dirty)}`);
        },
    );

    c.set.add(1);
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] c.set.size: add new value fires: count=${count} === 1`, eq(count, 1));

    c.set.add(1); // already present — no length change
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] c.set.size: add existing value does not fire: count=${count} === 1`, eq(count, 1));

    c.set.delete(1);
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] c.set.size: delete fires: count=${count} === 2`, eq(count, 2));

    c.set.add(2);
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    c.set.add(3);
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] c.set.size: two more adds: count=${count} === 4`, eq(count, 4));

    c.set.clear();
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] c.set.size: clear fires: count=${count} === 5`, eq(count, 5));
}

// === path 'c.map' =========================================================

function doMonitorOnClassMapIdentityLambdaNoFire(isSync: boolean): void {
    const tag = isSync ? 'sync' : 'async';
    let count: int = 0;
    const c = new ClassWithMapSet();

    const _monitor = makeMonitorByMode(
        isSync,
        [{
            path: 'c.map',
            valueCallback: () => c.map,
            enableWildcard: false } as IMonitorPathInfo
        ] as IMonitorPathInfo[],
        (m: IMonitor): void => {
            count++;
            console.log(`Monitor[${tag}] 'c.map' triggered: count=${count} dirty=${JSON.stringify(m.dirty)}`);
        },
    );

    c.map.set('a', 1);
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] c.map identity: set new key does not fire: count=${count} === 0`, eq(count, 0));

    c.map.set('a', 100);
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] c.map identity: update existing key does not fire: count=${count} === 0`, eq(count, 0));

    c.map.delete('a');
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] c.map identity: delete does not fire: count=${count} === 0`, eq(count, 0));

    c.map.set('b', 2);
    c.map.clear();
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] c.map identity: clear does not fire: count=${count} === 0`, eq(count, 0));
}

// === path 'c.map.*' =======================================================

function doMonitorOnClassMapWildcardFiresOncePerMutation(isSync: boolean): void {
    const tag = isSync ? 'sync' : 'async';
    let count: int = 0;
    const c = new ClassWithMapSet();

    const _monitor = makeMonitorByMode(
        isSync,
        [{
            path: 'c.map.*',
            valueCallback: () => c.map,
            enableWildcard: true } as IMonitorPathInfo
        ] as IMonitorPathInfo[],
        (m: IMonitor): void => {
            count++;
            console.log(`Monitor[${tag}] 'c.map.*' triggered: count=${count} dirty=${JSON.stringify(m.dirty)}`);
        },
    );

    c.map.set('a', 1); // new key
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] c.map wildcard: set new key fires once: count=${count} === 1`, eq(count, 1));

    c.map.set('b', 2);
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] c.map wildcard: set second new key fires once: count=${count} === 2`, eq(count, 2));

    c.map.set('a', 100); // existing key, new value
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] c.map wildcard: update existing key fires once: count=${count} === 3`, eq(count, 3));

    c.map.set('a', 100); // idempotent — same key, same value, no fire
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] c.map wildcard: idempotent set does not fire: count=${count} === 3`, eq(count, 3));

    c.map.delete('b');
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] c.map wildcard: delete fires once: count=${count} === 4`, eq(count, 4));

    c.map.clear();
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] c.map wildcard: clear fires once: count=${count} === 5`, eq(count, 5));
}

// === path 'c.map.size' ====================================================

function doMonitorOnClassMapSize(isSync: boolean): void {
    const tag = isSync ? 'sync' : 'async';
    let count: int = 0;
    const c = new ClassWithMapSet();

    const _monitor = makeMonitorByMode(
        isSync,
        [{
            path: 'c.map.size',
            valueCallback: () => c.map.size,
            enableWildcard: false } as IMonitorPathInfo
        ] as IMonitorPathInfo[],
        (m: IMonitor): void => {
            count++;
            console.log(`Monitor[${tag}] 'c.map.size' triggered: count=${count} dirty=${JSON.stringify(m.dirty)}`);
        },
    );

    c.map.set('x', 1); // size 0 → 1
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] c.map.size: set new key fires: count=${count} === 1`, eq(count, 1));

    c.map.set('x', 100); // existing key — size unchanged
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] c.map.size: update existing key does not fire: count=${count} === 1`, eq(count, 1));

    c.map.delete('x'); // size 1 → 0
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] c.map.size: delete fires: count=${count} === 2`, eq(count, 2));

    c.map.set('y', 2);
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    c.map.set('z', 3);
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] c.map.size: two more sets: count=${count} === 4`, eq(count, 4));

    c.map.clear();
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] c.map.size: clear fires: count=${count} === 5`, eq(count, 5));
}

// === Suite wiring ==========================================================

function runClassMapSetSuite(isSync: boolean): void {
    const factoryName = isSync ? 'makeSyncMonitor' : 'makeMonitor';

    tcase(`### ${factoryName} on ClassWithMapSet path 'c.set': identity lambda does not bind — no fires`)
    {
        doMonitorOnClassSetIdentityLambdaNoFire(isSync);
    }

    tcase(`### ${factoryName} on ClassWithMapSet path 'c.set.*': wildcard via addRefAnyKey — one fire per logical mutation`)
    {
        doMonitorOnClassSetWildcardFiresOncePerMutation(isSync);
    }

    tcase(`### ${factoryName} on ClassWithMapSet path 'c.set.size': fires only on length-changing mutations`)
    {
        doMonitorOnClassSetSize(isSync);
    }

    tcase(`### ${factoryName} on ClassWithMapSet path 'c.map': identity lambda does not bind — no fires`)
    {
        doMonitorOnClassMapIdentityLambdaNoFire(isSync);
    }

    tcase(`### ${factoryName} on ClassWithMapSet path 'c.map.*': wildcard via addRefAnyKey — one fire per logical mutation`)
    {
        doMonitorOnClassMapWildcardFiresOncePerMutation(isSync);
    }

    tcase(`### ${factoryName} on ClassWithMapSet path 'c.map.size': fires only on length-changing mutations`)
    {
        doMonitorOnClassMapSize(isSync);
    }
}

export function run_monitor_class_map_set(): boolean {
    const ttest = tsuite('@Monitor ClassWithMapSet (@Local Set / @Local Map)') {
        runClassMapSetSuite(/* isSync */ false);
    }
    ttest();
    return true;
}

export function run_syncmonitor_class_map_set(): boolean {
    const ttest = tsuite('@SyncMonitor ClassWithMapSet (@Local Set / @Local Map)') {
        runClassMapSetSuite(/* isSync */ true);
    }
    ttest();
    return true;
}
