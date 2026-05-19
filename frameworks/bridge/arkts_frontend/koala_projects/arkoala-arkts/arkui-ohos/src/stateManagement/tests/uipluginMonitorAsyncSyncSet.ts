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

// WrappedSet monitor coverage parameterized by `isSync`. Three paths only:
//   'set'       — identity lambda; no getter binding → no fires
//   'set.*'     — wildcard; addRefAnyKey on the keyed-meta set → one
//                 callback per logical mutation
//   'set.size'  — primitive lambda over the LENGTH meta → fires only when
//                 size changes
// Each helper runs twice — async (run_monitor_set) with an explicit
// updateDirty() flush, and sync (run_syncmonitor_set) where the callback
// fires inside fireChange. Counts match across modes.

import { tsuite, tcase, test, eq } from './lib/testFramework'
import {
    IMonitor,
    IMonitorPathInfo,
    IMonitorDecoratedVariable,
    MonitorCallback,
} from '../decorator'
import { ObserveSingleton } from '../base/observeSingleton';
import { STATE_MGMT_FACTORY } from '../decorator'
import { UIUtils } from '../utils';

// Strong-reference store. Without this, locally-scoped monitors get GC'd.
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

// === path 'set' ============================================================

// Identity lambda: lambda returns `set` without calling a getter, so no
// per-value or LENGTH meta is bound. Mutations fire metas the monitor isn't
// bound to → no fires.
function doMonitorOnSetIdentityLambdaNoFire(isSync: boolean): void {
    const tag = isSync ? 'sync' : 'async';
    let count: int = 0;
    const set = UIUtils.makeObserved(new Set<number>());

    const _monitor = makeMonitorByMode(
        isSync,
        [{
            path: 'set',
            valueCallback: () => set,
            enableWildcard: false } as IMonitorPathInfo
        ] as IMonitorPathInfo[],
        (m: IMonitor): void => {
            count++;
            console.log(`Monitor[${tag}] 'set' triggered: count=${count} dirty=${JSON.stringify(m.dirty)}`);
        },
    );

    set.add(1);
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] set identity: add new value does not fire: count=${count} === 0`, eq(count, 0));

    set.add(1); // already present
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] set identity: add existing value does not fire: count=${count} === 0`, eq(count, 0));

    set.delete(1);
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] set identity: delete does not fire: count=${count} === 0`, eq(count, 0));

    set.add(2);
    set.clear();
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] set identity: clear does not fire: count=${count} === 0`, eq(count, 0));
}

// === path 'set.*' ==========================================================

// Wildcard over the keyed-meta set. addRefAnyKey() binds OB_SET_ANY_PROPERTY
// AND OB_LENGTH, so add/delete/clear each fire exactly once per logical
// mutation thanks to fireChangeBatch batching across the multi-key fire.
// Idempotent add (value already present) and delete of absent value do not
// fire — the WrappedSet short-circuits those before any meta change.
function doMonitorOnSetWildcardFiresOncePerMutation(isSync: boolean): void {
    const tag = isSync ? 'sync' : 'async';
    let count: int = 0;
    const set = UIUtils.makeObserved(new Set<number>());

    const _monitor = makeMonitorByMode(
        isSync,
        [{
            path: 'set.*',
            valueCallback: () => set,
            enableWildcard: true } as IMonitorPathInfo
        ] as IMonitorPathInfo[],
        (m: IMonitor): void => {
            count++;
            console.log(`Monitor[${tag}] 'set.*' triggered: count=${count} dirty=${JSON.stringify(m.dirty)}`);
        },
    );

    set.add(1);
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] set wildcard: add new value fires once: count=${count} === 1`, eq(count, 1));

    set.add(2);
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] set wildcard: add second new value fires once: count=${count} === 2`, eq(count, 2));

    set.add(1); // already present — no fire
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] set wildcard: add existing value does not fire: count=${count} === 2`, eq(count, 2));

    set.delete(1);
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] set wildcard: delete fires once: count=${count} === 3`, eq(count, 3));

    set.delete(99); // not present — no fire
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] set wildcard: delete non-existent value does not fire: count=${count} === 3`, eq(count, 3));

    set.clear();
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] set wildcard: clear fires once: count=${count} === 4`, eq(count, 4));

    set.clear(); // empty — no fire
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] set wildcard: clear on empty set does not fire: count=${count} === 4`, eq(count, 4));
}

// === path 'set.size' =======================================================

// Lambda reads .size, binding the LENGTH meta. Fires only on size-changing
// mutations.
function doMonitorOnSetSize(isSync: boolean): void {
    const tag = isSync ? 'sync' : 'async';
    let count: int = 0;
    const set = UIUtils.makeObserved(new Set<number>());

    const _monitor = makeMonitorByMode(
        isSync,
        [{
            path: 'set.size',
            valueCallback: () => set.size,
            enableWildcard: false } as IMonitorPathInfo
        ] as IMonitorPathInfo[],
        (m: IMonitor): void => {
            count++;
            console.log(`Monitor[${tag}] 'set.size' triggered: count=${count} dirty=${JSON.stringify(m.dirty)}`);
        },
    );

    set.add(1); // size 0 → 1
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] set.size: add new value fires: count=${count} === 1`, eq(count, 1));

    set.add(1); // already present — no length change
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] set.size: add existing value does not fire: count=${count} === 1`, eq(count, 1));

    set.delete(1); // size 1 → 0
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] set.size: delete fires: count=${count} === 2`, eq(count, 2));

    set.add(2);
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    set.add(3);
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] set.size: two more adds: count=${count} === 4`, eq(count, 4));

    set.clear();
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] set.size: clear fires: count=${count} === 5`, eq(count, 5));
}

// === Suite wiring ==========================================================

function runSetSuite(isSync: boolean): void {
    const factoryName = isSync ? 'makeSyncMonitor' : 'makeMonitor';

    tcase(`### ${factoryName} on WrappedSet path 'set': identity lambda does not bind — no fires`)
    {
        doMonitorOnSetIdentityLambdaNoFire(isSync);
    }

    tcase(`### ${factoryName} on WrappedSet path 'set.*': addRefAnyKey binds — one fire per logical mutation`)
    {
        doMonitorOnSetWildcardFiresOncePerMutation(isSync);
    }

    tcase(`### ${factoryName} on WrappedSet path 'set.size': fires only on length-changing mutations`)
    {
        doMonitorOnSetSize(isSync);
    }
}

export function run_monitor_set(): boolean {
    const ttest = tsuite('@Monitor WrappedSet') {
        runSetSuite(/* isSync */ false);
    }
    ttest();
    return true;
}

export function run_syncmonitor_set(): boolean {
    const ttest = tsuite('@SyncMonitor WrappedSet') {
        runSetSuite(/* isSync */ true);
    }
    ttest();
    return true;
}
