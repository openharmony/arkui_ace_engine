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

// WrappedMap monitor coverage parameterized by `isSync`. Three paths only:
//   'map'       — identity lambda; no getter binding → no fires
//   'map.*'     — wildcard; addRefAnyKey on the keyed-meta map → one
//                 callback per logical mutation
//   'map.size'  — primitive lambda over the LENGTH meta → fires only when
//                 size changes
// Each helper runs twice — async (run_monitor_map) with an explicit
// updateDirty() flush, and sync (run_syncmonitor_map) where the callback
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

// === path 'map' ============================================================

// Identity lambda: lambda returns `map` without calling a getter, so no per-
// key or LENGTH meta is bound. Mutations queue dirty refs only on the metas
// they actually fire, none of which the monitor is bound to → no fires.
function doMonitorOnMapIdentityLambdaNoFire(isSync: boolean): void {
    const tag = isSync ? 'sync' : 'async';
    let count: int = 0;
    const map = UIUtils.makeObserved(new Map<string, number>());

    const _monitor = makeMonitorByMode(
        isSync,
        [{
            path: 'map',
            valueCallback: () => map,
            enableWildcard: false } as IMonitorPathInfo
        ] as IMonitorPathInfo[],
        (m: IMonitor): void => {
            count++;
            console.log(`Monitor[${tag}] 'map' triggered: count=${count} dirty=${JSON.stringify(m.dirty)}`);
        },
    );

    map.set('a', 1);
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] map identity: set new key does not fire: count=${count} === 0`, eq(count, 0));

    map.set('a', 100);
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] map identity: update existing key does not fire: count=${count} === 0`, eq(count, 0));

    map.delete('a');
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] map identity: delete does not fire: count=${count} === 0`, eq(count, 0));

    map.set('b', 2);
    map.clear();
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] map identity: clear does not fire: count=${count} === 0`, eq(count, 0));
}

// === path 'map.*' ==========================================================

// Wildcard over the keyed-meta map. addRefAnyKey() binds OB_LENGTH AND
// OB_MAP_ANY_PROPERTY, so set/delete/clear each fire exactly once per logical
// mutation thanks to fireChangeBatch batching across the multi-key fire.
// Idempotent set (same key, same value) still fires the wildcard via the
// per-key/touch path.
function doMonitorOnMapWildcardFiresOncePerMutation(isSync: boolean): void {
    const tag = isSync ? 'sync' : 'async';
    let count: int = 0;
    const map = UIUtils.makeObserved(new Map<string, number>());

    const _monitor = makeMonitorByMode(
        isSync,
        [{
            path: 'map.*',
            valueCallback: () => map,
            enableWildcard: true } as IMonitorPathInfo
        ] as IMonitorPathInfo[],
        (m: IMonitor): void => {
            count++;
            console.log(`Monitor[${tag}] 'map.*' triggered: count=${count} dirty=${JSON.stringify(m.dirty)}`);
        },
    );

    map.set('a', 1); // new key
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] map wildcard: set new key fires once: count=${count} === 1`, eq(count, 1));

    map.set('b', 2);
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] map wildcard: set second new key fires once: count=${count} === 2`, eq(count, 2));

    map.set('a', 100); // existing key, new value
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] map wildcard: update existing key fires once: count=${count} === 3`, eq(count, 3));

    map.set('a', 100); // idempotent — same key, same value, no fire
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] map wildcard: idempotent set does not fire: count=${count} === 3`, eq(count, 3));

    map.delete('b');
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] map wildcard: delete fires once: count=${count} === 4`, eq(count, 4));

    map.clear();
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] map wildcard: clear fires once: count=${count} === 5`, eq(count, 5));
}

// === path 'map.size' =======================================================

// Lambda reads .size, binding the LENGTH meta. Fires only on size-changing
// mutations: set-new and delete change size; set-existing leaves size alone.
function doMonitorOnMapSize(isSync: boolean): void {
    const tag = isSync ? 'sync' : 'async';
    let count: int = 0;
    const map = UIUtils.makeObserved(new Map<string, number>());

    const _monitor = makeMonitorByMode(
        isSync,
        [{
            path: 'map.size',
            valueCallback: () => map.size,
            enableWildcard: false } as IMonitorPathInfo
        ] as IMonitorPathInfo[],
        (m: IMonitor): void => {
            count++;
            console.log(`Monitor[${tag}] 'map.size' triggered: count=${count} dirty=${JSON.stringify(m.dirty)}`);
        },
    );

    map.set('x', 1); // size 0 → 1
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] map.size: set new key fires: count=${count} === 1`, eq(count, 1));

    map.set('x', 100); // existing key — size unchanged
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] map.size: update existing key does not fire: count=${count} === 1`, eq(count, 1));

    map.delete('x'); // size 1 → 0
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] map.size: delete fires: count=${count} === 2`, eq(count, 2));

    map.set('y', 2);
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    map.set('z', 3);
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] map.size: two more sets: count=${count} === 4`, eq(count, 4));

    map.clear();
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] map.size: clear fires: count=${count} === 5`, eq(count, 5));
}

// === Suite wiring ==========================================================

function runMapSuite(isSync: boolean): void {
    const factoryName = isSync ? 'makeSyncMonitor' : 'makeMonitor';

    tcase(`### ${factoryName} on WrappedMap path 'map': identity lambda does not bind — no fires`)
    {
        doMonitorOnMapIdentityLambdaNoFire(isSync);
    }

    tcase(`### ${factoryName} on WrappedMap path 'map.*': addRefAnyKey binds — one fire per logical mutation`)
    {
        doMonitorOnMapWildcardFiresOncePerMutation(isSync);
    }

    tcase(`### ${factoryName} on WrappedMap path 'map.size': fires only on length-changing mutations`)
    {
        doMonitorOnMapSize(isSync);
    }
}

export function run_monitor_map(): boolean {
    const ttest = tsuite('@Monitor WrappedMap') {
        runMapSuite(/* isSync */ false);
    }
    ttest();
    return true;
}

export function run_syncmonitor_map(): boolean {
    const ttest = tsuite('@SyncMonitor WrappedMap') {
        runMapSuite(/* isSync */ true);
    }
    ttest();
    return true;
}
