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

// Lambda-value edge cases parameterized by `isSync`. Covers behavior the
// happy-path tests don't exercise:
//
//   - Value lambda throws after dependencies are already recorded.
//     MonitorValueInternal.readValue catches and returns false → callback
//     should NOT fire on subsequent mutations.
//   - Value lambda returns NaN. NaN !== NaN bypasses the non-wildcard
//     equality short-circuit, so even an idempotent reassign fires.
//   - Value lambda returns undefined initially, then a real value.
//     Verifies before=undefined snapshot and the first real assignment fires.
//   - Primitive same-value reassign on @Local. The @Local setter's
//     newValue !== oldValue check should suppress fireChange entirely.

import { tsuite, tcase, test, eq } from './lib/testFramework'
import {
    ILocalDecoratedVariable,
    IMonitor,
    IMonitorPathInfo,
    IMonitorDecoratedVariable,
    MonitorCallback,
} from '../decorator'
import { ExtendableComponent } from '../mock/extendableComponent';
import { ObserveSingleton } from '../base/observeSingleton';
import { STATE_MGMT_FACTORY } from '../decorator'
import { ClassWithDate } from './commonClasses';

const StateMgmtFactory = STATE_MGMT_FACTORY;

// Strong-reference store; see other Async/Sync test files for the rationale
// (Panda VM GC reclaims locally-scoped monitors that aren't read after init).
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

// Minimal component holding a single @Local number. Used for the
// primitive-equality and NaN edge tests.
class ComponentWithNumber extends ExtendableComponent {
    private _backing_x: ILocalDecoratedVariable<number>;
    get x(): number { return this._backing_x.get(); }
    set x(v: number) { this._backing_x.set(v); }
    constructor(parent: ExtendableComponent | null, init: number) {
        super(parent);
        this._backing_x = StateMgmtFactory.makeLocal<number>(this, 'x', init);
    }
}

// === Tests ================================================================

// Lambda throws AFTER the first run that successfully recorded dependencies.
// Subsequent re-reads in MonitorValueInternal.readValue throw — the try/catch
// returns false, so dirty_ stays false and runMonitorFunction skips the
// callback. Mutations to the underlying observable do still queue the monitor
// but the drain produces no user-visible callback.
function doMonitorLambdaThrowsAfterDepsRecorded(isSync: boolean): void {
    const tag = isSync ? 'sync' : 'async';
    const comp = new ComponentWithNumber(null, 0);
    let count: int = 0;
    let throwOnRead = false;
    const lambda = () => {
        const v = comp.x;
        if (throwOnRead) {
            throw new Error('lambda boom');
        }
        return v;
    };

    const _monitor = makeMonitorByMode(
        isSync,
        [{ path: 'comp.x', valueCallback: lambda, enableWildcard: false } as IMonitorPathInfo],
        (_m: IMonitor): void => { count++; },
    );

    // Sanity: a normal write before flipping the throw flag fires once.
    comp.x = 1;
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] lambda-throws: pre-throw fire: count=${count} === 1`, eq(count, 1));

    // Flip the lambda into throwing mode.
    throwOnRead = true;

    // Two more writes — re-reads throw → dirty stays false → no callback.
    comp.x = 2;
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] lambda-throws: write 1 after throw flag: count=${count} === 1`, eq(count, 1));

    comp.x = 3;
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] lambda-throws: write 2 after throw flag: count=${count} === 1`, eq(count, 1));

    // Restore: subsequent writes resume firing.
    throwOnRead = false;
    comp.x = 4;
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] lambda-throws: post-throw recovery fire: count=${count} === 2`, eq(count, 2));
}

// Lambda returns NaN. The non-wildcard equality is `before !== now`, and
// NaN !== NaN is true — so an idempotent NaN reassign STILL fires in sync
// mode. Async coalesces multiple NaN writes between drains into one callback.
function doMonitorLambdaReturnsNaN(isSync: boolean): void {
    const tag = isSync ? 'sync' : 'async';
    const comp = new ComponentWithNumber(null, 0);
    let count: int = 0;

    const _monitor = makeMonitorByMode(
        isSync,
        [{ path: 'comp.x', valueCallback: () => comp.x, enableWildcard: false } as IMonitorPathInfo],
        (_m: IMonitor): void => { count++; },
    );

    // 0 → NaN: fires (different by both equality definitions).
    comp.x = NaN;
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] NaN: 0->NaN fires: count=${count} === 1`, eq(count, 1));

    // NaN → NaN (idempotent value, but NaN !== NaN). Sync fires again because
    // each fireChange re-reads and dirty_ trips. Async coalesces — still ONE
    // callback because the drain runs readValue once.
    comp.x = NaN;
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] NaN: NaN->NaN fires (NaN!==NaN): count=${count} === 2`, eq(count, 2));

    comp.x = NaN;
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] NaN: NaN->NaN second time fires: count=${count} === 3`, eq(count, 3));

    // NaN → real number: fires (NaN !== 5).
    comp.x = 5;
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] NaN: NaN->5 fires: count=${count} === 4`, eq(count, 4));
}

// Same-value reassign on a @Local primitive. The @Local setter's
// newValue !== oldValue check suppresses fireChange entirely, so the monitor
// never gets queued. Both modes report count=0 across N idempotent writes.
function doMonitorPrimitiveSameValueIdempotent(isSync: boolean): void {
    const tag = isSync ? 'sync' : 'async';
    const comp = new ComponentWithNumber(null, 5);
    let count: int = 0;

    const _monitor = makeMonitorByMode(
        isSync,
        [{ path: 'comp.x', valueCallback: () => comp.x, enableWildcard: false } as IMonitorPathInfo],
        (_m: IMonitor): void => { count++; },
    );

    // Five idempotent assigns of the same value — none should fire.
    comp.x = 5;
    comp.x = 5;
    comp.x = 5;
    comp.x = 5;
    comp.x = 5;
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] primitive idempotent: 5 same-value writes: count=${count} === 0`, eq(count, 0));

    // Different value fires.
    comp.x = 6;
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] primitive idempotent: change to 6 fires: count=${count} === 1`, eq(count, 1));

    // Back to 5 fires.
    comp.x = 5;
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] primitive idempotent: change back to 5 fires: count=${count} === 2`, eq(count, 2));

    // 5 again — idempotent, no fire.
    comp.x = 5;
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] primitive idempotent: 5 again no fire: count=${count} === 2`, eq(count, 2));
}

// Regression test: BackingValue.set passes the new value as the wildcard
// target sentinel (`this.fireChange(this.value_)`). When an async wildcard
// monitor is bound to an IObservedAnyProp-implementing @Local field and the
// field is reassigned A → B → A within a single drain pass, the LSV (A) ends
// up in the per-monitor `sources` set. The wildcard transit-dep branch
// (`sources.has(this.before)`) then trips and fires a phantom callback even
// though the lambda's value is unchanged AND no internal property of A was
// mutated.
//
// Sync mode is unaffected because each fireChange drains immediately, so
// `sources` only ever contains one value per drain — a restored LSV in a
// later set goes through the regular `before !== now` branch correctly.
//
// FIX: pass `this` (the BackingValue itself) as the target sentinel in
// backingValue.ts:55 and :68. The BackingValue instance can never be the
// return value of any user-written lambda, so `sources.has(this.before)` is
// always false → the wildcard branch correctly falls through to
// `before !== now`.
function doMonitorBackingValueTargetSentinelBug(isSync: boolean): void {
    const tag = isSync ? 'sync' : 'async';
    const initialDt = new Date(2020, 0, 15);
    const altDt = new Date(2025, 5, 10);
    const comp = new ClassWithDate(null, initialDt);

    // The @Local autoProxies the input Date — capture the wrapped instance
    // the lambda actually returns, so we can restore the SAME reference.
    const lsv = comp.dt;

    let count: int = 0;
    const _monitor = makeMonitorByMode(
        isSync,
        [{
            path: 'comp.dt.*',
            valueCallback: () => comp.dt,
            enableWildcard: true,
        } as IMonitorPathInfo],
        (_m: IMonitor): void => { count++; },
    );

    // A → B → A within one async drain. Same wrapped Date reference at the
    // end. Sync sees both ref changes (count=2 via before !== now); async
    // should see net no-op (count=0 — but the bug fires once).
    comp.dt = altDt;
    comp.dt = lsv;
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }

    if (isSync) {
        test(`[${tag}] BackingValue target sentinel: sync sees both ref changes: count=${count} === 2`,
            eq(count, 2));
    } else {
        test(`[${tag}] BackingValue target sentinel: async A->B->A net no-op: count=${count} === 0`,
            eq(count, 0));
    }
}

// === Suite wiring ==========================================================

function runEdgeLambdaSuite(isSync: boolean): void {
    const factoryName = isSync ? 'makeSyncMonitor' : 'makeMonitor';

    tcase(`### ${factoryName} edge: value lambda throws after deps recorded — no callback`)
    {
        doMonitorLambdaThrowsAfterDepsRecorded(isSync);
    }

    tcase(`### ${factoryName} edge: value lambda returns NaN — idempotent reassign still fires (NaN !== NaN)`)
    {
        doMonitorLambdaReturnsNaN(isSync);
    }

    tcase(`### ${factoryName} edge: primitive same-value reassign suppressed by @Local equality short-circuit`)
    {
        doMonitorPrimitiveSameValueIdempotent(isSync);
    }

    tcase(`### ${factoryName} edge: BackingValue target sentinel — wildcard A->B->A net no-op (regression)`)
    {
        doMonitorBackingValueTargetSentinelBug(isSync);
    }
}

export function run_monitor_edge_lambda(): boolean {
    const ttest = tsuite('@Monitor edge cases — lambda value behavior') {
        runEdgeLambdaSuite(/* isSync */ false);
    }
    ttest();
    return true;
}

export function run_syncmonitor_edge_lambda(): boolean {
    const ttest = tsuite('@SyncMonitor edge cases — lambda value behavior') {
        runEdgeLambdaSuite(/* isSync */ true);
    }
    ttest();
    return true;
}
