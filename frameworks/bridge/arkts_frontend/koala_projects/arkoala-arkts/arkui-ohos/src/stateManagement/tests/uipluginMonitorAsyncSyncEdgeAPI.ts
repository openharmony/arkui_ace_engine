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

// IMonitor API + path topology edge cases parameterized by `isSync`. Covers:
//
//   - Duplicate paths in a single IMonitorPathInfo[]: callback should fire
//     ONCE per logical mutation (per-call MonitorFunctionDecorator dedup),
//     but m.dirty should report both entries (length 2, both === path).
//   - m.value() with no path argument when MULTIPLE non-wildcard paths are
//     dirty — verifies which one is returned (the first dirty in declaration
//     order per decoratorMonitor.ts).
//   - m.dirty array immutability: mutating the returned array from the
//     callback must not corrupt the framework's internal state — subsequent
//     callbacks should still see a fresh, correct dirty list.

import { tsuite, tcase, test, eq } from './lib/testFramework'
import {
    ILocalDecoratedVariable,
    IMonitor,
    IMonitorPathInfo,
    IMonitorDecoratedVariable,
    IMonitorValue,
    MonitorCallback,
} from '../decorator'
import { ExtendableComponent } from '../mock/extendableComponent';
import { ObserveSingleton } from '../base/observeSingleton';
import { STATE_MGMT_FACTORY } from '../decorator'

const StateMgmtFactory = STATE_MGMT_FACTORY;

// Strong-reference store; see other Async/Sync test files for the rationale.
const installedMonitors_: Array<IMonitorDecoratedVariable> = new Array<IMonitorDecoratedVariable>();

function makeMonitorByMode(
    isSync: boolean,
    pathInfos: IMonitorPathInfo[],
    onChanged: MonitorCallback,
): IMonitorDecoratedVariable {
    const m = isSync
        ? STATE_MGMT_FACTORY.makeSyncMonitor(pathInfos, onChanged, undefined)
        : STATE_MGMT_FACTORY.makeMonitor(pathInfos, onChanged);
    installedMonitors_.push(m);
    return m;
}

// Component with two independent @Local strings — used to drive multi-path
// monitors where each path can be made dirty independently.
class ComponentWithTwoStrings extends ExtendableComponent {
    private _backing_a: ILocalDecoratedVariable<string>;
    private _backing_b: ILocalDecoratedVariable<string>;
    get a(): string { return this._backing_a.get(); }
    set a(v: string) { this._backing_a.set(v); }
    get b(): string { return this._backing_b.get(); }
    set b(v: string) { this._backing_b.set(v); }
    constructor(parent: ExtendableComponent | null, initA: string, initB: string) {
        super(parent);
        this._backing_a = StateMgmtFactory.makeLocal<string>(this, 'a', initA);
        this._backing_b = StateMgmtFactory.makeLocal<string>(this, 'b', initB);
    }
}

// === Tests ================================================================

// Two IMonitorPathInfo entries with the SAME path string and equivalent
// lambdas. Each registers a separate MonitorValueInternal. A single mutation
// to the underlying observable dirties both — but the parent
// MonitorFunctionDecorator dedup means the callback fires ONCE per logical
// mutation. m.dirty reports both entries (length 2).
function doMonitorDuplicatePathsInOneMonitor(isSync: boolean): void {
    const tag = isSync ? 'sync' : 'async';
    const comp = new ComponentWithTwoStrings(null, 'a0', 'b0');
    let count: int = 0;
    let lastDirty: Array<string> = new Array<string>();

    const _monitor = makeMonitorByMode(
        isSync,
        [
            { path: 'comp.a', valueCallback: () => comp.a, enableWildcard: false } as IMonitorPathInfo,
            { path: 'comp.a', valueCallback: () => comp.a, enableWildcard: false } as IMonitorPathInfo,
        ],
        (m: IMonitor): void => {
            count++;
            lastDirty = m.dirty;
        },
    );

    comp.a = 'a1';
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] dup paths: single mutation fires once: count=${count} === 1`, eq(count, 1));
    test(`[${tag}] dup paths: m.dirty.length === 2`, eq(lastDirty.length, 2));
    test(`[${tag}] dup paths: m.dirty[0] === 'comp.a'`, eq(lastDirty[0], 'comp.a'));
    test(`[${tag}] dup paths: m.dirty[1] === 'comp.a'`, eq(lastDirty[1], 'comp.a'));

    comp.a = 'a2';
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] dup paths: second mutation fires once: count=${count} === 2`, eq(count, 2));
    test(`[${tag}] dup paths: m.dirty still length 2`, eq(lastDirty.length, 2));
}

// m.value() with no path argument scans values_ and returns the first dirty
// non-wildcard MonitorValuePublic (per decoratorMonitor.ts:66-72). Set up two
// independent paths and dirty BOTH in one drain — the no-arg overload should
// return the first one.
function doMonitorValueNoArgWithMultipleDirty(isSync: boolean): void {
    const tag = isSync ? 'sync' : 'async';
    const comp = new ComponentWithTwoStrings(null, 'A', 'B');
    let count: int = 0;
    let lastNoArgPath: string = '';
    let lastNoArgNow: string = '';

    const _monitor = makeMonitorByMode(
        isSync,
        [
            { path: 'comp.a', valueCallback: () => comp.a, enableWildcard: false } as IMonitorPathInfo,
            { path: 'comp.b', valueCallback: () => comp.b, enableWildcard: false } as IMonitorPathInfo,
        ],
        (m: IMonitor): void => {
            count++;
            const v = m.value<string>();
            lastNoArgPath = v === undefined ? '' : v!.path;
            lastNoArgNow = v === undefined ? '' : v!.now;
        },
    );

    // Mutate ONLY comp.b — only the second path is dirty. m.value() must
    // return the comp.b entry (it's the only dirty one).
    comp.b = 'B1';
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] no-arg-value: only b dirty: count=${count} === 1`, eq(count, 1));
    test(`[${tag}] no-arg-value: only b dirty: path === 'comp.b'`, eq(lastNoArgPath, 'comp.b'));
    test(`[${tag}] no-arg-value: only b dirty: now === 'B1'`, eq(lastNoArgNow, 'B1'));

    // Now mutate BOTH in one drain (sync sees them as separate fires; async
    // coalesces). In async mode, both are dirty at callback time and m.value()
    // returns the FIRST in declaration order, which is comp.a.
    comp.a = 'A1';
    comp.b = 'B2';
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    if (isSync) {
        // Sync fired twice: first for 'a' (only a dirty, picks a), then for 'b'
        // (only b dirty, picks b). Last snapshot is from the b callback.
        test(`[${tag}] no-arg-value: both written sync: count=${count} === 3`, eq(count, 3));
        test(`[${tag}] no-arg-value: last sync callback path === 'comp.b'`, eq(lastNoArgPath, 'comp.b'));
        test(`[${tag}] no-arg-value: last sync callback now === 'B2'`, eq(lastNoArgNow, 'B2'));
    } else {
        // Async: one coalesced callback with BOTH dirty → no-arg picks first
        // declared (comp.a).
        test(`[${tag}] no-arg-value: both dirty async: count=${count} === 2`, eq(count, 2));
        test(`[${tag}] no-arg-value: both dirty async: path === 'comp.a' (first declared)`, eq(lastNoArgPath, 'comp.a'));
        test(`[${tag}] no-arg-value: both dirty async: now === 'A1'`, eq(lastNoArgNow, 'A1'));
    }
}

// m.dirty contract: callbacks may legitimately mutate the returned array
// (e.g., as scratch space). The framework must not be corrupted — the next
// callback's m.dirty should still be a correct, fresh list.
function doMonitorDirtyArrayMutationDoesNotCorruptFraework(isSync: boolean): void {
    const tag = isSync ? 'sync' : 'async';
    const comp = new ComponentWithTwoStrings(null, 'A', 'B');
    let count: int = 0;
    let lastLengthAfterClear: int = -1;
    let nextLengthSeen: int = -1;
    let nextHeadSeen: string = '';

    const _monitor = makeMonitorByMode(
        isSync,
        [{ path: 'comp.a', valueCallback: () => comp.a, enableWildcard: false } as IMonitorPathInfo],
        (m: IMonitor): void => {
            count++;
            const dirty = m.dirty;
            if (count === 1) {
                // Try to mutate: clear the local reference. Subsequent calls must
                // not be affected.
                while (dirty.length > 0) {
                    dirty.pop();
                }
                lastLengthAfterClear = dirty.length;
            } else {
                nextLengthSeen = dirty.length;
                nextHeadSeen = dirty.length > 0 ? dirty[0] : '';
            }
        },
    );

    comp.a = 'A1';
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] dirty-mutation: first cb cleared local: cleared.length === 0`, eq(lastLengthAfterClear, 0));

    // Second mutation — second callback's m.dirty must be a freshly-built
    // list with the path back in it.
    comp.a = 'A2';
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] dirty-mutation: second cb sees fresh list length 1`, eq(nextLengthSeen, 1));
    test(`[${tag}] dirty-mutation: second cb head === 'comp.a'`, eq(nextHeadSeen, 'comp.a'));
}

// === Suite wiring ==========================================================

function runEdgeAPISuite(isSync: boolean): void {
    const factoryName = isSync ? 'makeSyncMonitor' : 'makeMonitor';

    tcase(`### ${factoryName} edge: duplicate paths in one IMonitorPathInfo[] — fires once, m.dirty length 2`)
    {
        doMonitorDuplicatePathsInOneMonitor(isSync);
    }

    tcase(`### ${factoryName} edge: m.value() no-arg with multiple dirty — picks first declared`)
    {
        doMonitorValueNoArgWithMultipleDirty(isSync);
    }

    tcase(`### ${factoryName} edge: mutating returned m.dirty does not corrupt subsequent callbacks`)
    {
        doMonitorDirtyArrayMutationDoesNotCorruptFraework(isSync);
    }
}

export function run_monitor_edge_api(): boolean {
    const ttest = tsuite('@Monitor edge cases — IMonitor API + path topology') {
        runEdgeAPISuite(/* isSync */ false);
    }
    ttest();
    return true;
}

export function run_syncmonitor_edge_api(): boolean {
    const ttest = tsuite('@SyncMonitor edge cases — IMonitor API + path topology') {
        runEdgeAPISuite(/* isSync */ true);
    }
    ttest();
    return true;
}
