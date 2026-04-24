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

// Date / @Local Date monitor coverage parameterized by `isSync`. Each helper
// is exercised twice — once via run_monitor_date (async makeMonitor + an
// explicit ObserveSingleton.instance.updateDirty() flush after every
// mutation) and once via run_syncmonitor_date (makeSyncMonitor, fires inside
// MutableStateMeta.fireChange). Counts match across both modes because every
// mutation is followed by a flush before the next assertion.

import { tsuite, tcase, test, eq } from './lib/testFramework'
import {
    IMonitor,
    IMonitorPathInfo,
    IMonitorDecoratedVariable,
    MonitorCallback,
} from '../decorator'
import { ClassWithDate } from './commonClasses'
import { ObserveSingleton } from '../base/observeSingleton';
import { STATE_MGMT_FACTORY } from '../decorator'
import { UIUtils } from '../utils';

// Strong-reference store. The Panda VM's GC eagerly reclaims locally-scoped
// monitors that are never read after construction, which clears the WeakRefs
// in MutableStateMeta.bindingRefs_ mid-test and causes intermittent missing
// callbacks. Push each monitor here to keep it alive across mutations and
// assertions.
const testMonitors_: Array<IMonitorDecoratedVariable> = new Array<IMonitorDecoratedVariable>();

// Build a monitor in either sync or async mode. Both forms have the same
// (pathInfos, callback) signature for our purposes.
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

// === WrappedDate tests =====================================================

// Identity-lambda monitor: lambda returns `d` without calling any getter,
// so the WrappedDate's shared __meta is never bound and inner-Date setters
// cannot reach the monitor. setDate (changed value, idempotent repeat, then
// a different value) all leave the counter at 0 in either mode.
function doMonitorOnDateSetterNoFireIdentityLambda(isSync: boolean): void {
    const tag = isSync ? 'sync' : 'async';
    let count: int = 0;
    const d = UIUtils.makeObserved(new Date(2020, 0, 15, 10, 30, 45, 100));

    const _monitor = makeMonitorByMode(
        isSync,
        [{
            path: 'd',
            valueCallback: () => d,
            enableWildcard: false } as IMonitorPathInfo
        ] as IMonitorPathInfo[],
        (m: IMonitor): void => {
            count++;
            console.log(`Monitor[${tag}] 'd' triggered: count=${count} dirty=${JSON.stringify(m.dirty)}`);
        },
    );

    d.setDate(20); // 15 → 20
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] date: setDate(20) does not fire (lambda returns d, no getter binding): count=${count} === 0`, eq(count, 0));

    d.setDate(20); // idempotent
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] date: setDate(20) idempotent does not fire: count=${count} === 0`, eq(count, 0));

    d.setDate(25); // change value
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] date: setDate(25) does not fire (lambda returns d, no getter binding): count=${count} === 0`, eq(count, 0));
}

// setHours has 4 overloads (1-arg through 4-arg). Same identity-lambda
// pattern as the setter test above — the WrappedDate's shared meta is never
// bound, so none of the overloads fire the monitor.
function doMonitorOnDateSetHoursOverloadsNoFireIdentityLambda(isSync: boolean): void {
    const tag = isSync ? 'sync' : 'async';
    let count: int = 0;
    const d = UIUtils.makeObserved(new Date(2020, 0, 15, 10, 30, 45, 100));

    const _monitor = makeMonitorByMode(
        isSync,
        [{
            path: 'd',
            valueCallback: () => d,
            enableWildcard: false } as IMonitorPathInfo
        ] as IMonitorPathInfo[],
        (m: IMonitor): void => {
            count++;
            console.log(`Monitor[${tag}] 'date.getTime()' triggered: count=${count} dirty=${JSON.stringify(m.dirty)}`);
        },
    );

    d.setHours(11);
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] date setHours(h): does not fire: count=${count} === 0`, eq(count, 0));

    d.setHours(12, 0);
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] date setHours(h,m): does not fire: count=${count} === 0`, eq(count, 0));

    d.setHours(13, 0, 0);
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] date setHours(h,m,s): does not fire: count=${count} === 0`, eq(count, 0));

    d.setHours(14, 0, 0, 0);
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] date setHours(h,m,s,ms): does not fire: count=${count} === 0`, eq(count, 0));
}

// Wildcard monitor over UIUtils.makeObserved(Date) with an identity lambda.
// Unlike the non-wildcard variants, setTime fires the callback even without
// a getter binding — the wildcard transit-dep branch in
// MonitorValueInternal's LSV check picks up the source-of-fire.
function doMonitorOnDateWildcardSetTimeFires(isSync: boolean): void {
    const tag = isSync ? 'sync' : 'async';
    let count: int = 0;
    const d = UIUtils.makeObserved(new Date(0));

    const _monitor = makeMonitorByMode(
        isSync,
        [{
            path: 'd',
            valueCallback: () => d,
            enableWildcard: true } as IMonitorPathInfo
        ] as IMonitorPathInfo[],
        (m: IMonitor): void => {
            count++;
            console.log(`Monitor[${tag}] 'date.valueOf()' triggered: count=${count} dirty=${JSON.stringify(m.dirty)}`);
        },
    );

    d.setTime(1_000_000_000);
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] date setTime: fires: count=${count} === 1`, eq(count, 1));

    d.setTime(2_000_000_000);
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] date setTime again: fires: count=${count} === 2`, eq(count, 2));
}

// === @Local Date tests =====================================================
//
// ClassWithDate (from commonClasses.ts) holds a Date in an @Local slot and
// also implements IObservedAnyProp with a paired __meta_dt that the dt setter
// fires alongside the @Local backing meta.

// Lambda reads the WrappedDate identity (c.dt). Reassigning to a brand-new
// Date wraps it in a NEW WrappedDate, so identity changes → fire. Reassigning
// the same WrappedDate identity is autoProxyObject's no-op path → identity
// unchanged → no fire.
function doMonitorOnLocalDateAssignment(isSync: boolean): void {
    const tag = isSync ? 'sync' : 'async';
    let count: int = 0;
    const c = new ClassWithDate(null, new Date(2020, 0, 15));

    const _monitor = makeMonitorByMode(
        isSync,
        [{
            path: 'c.dt',
            valueCallback: () => c.dt,
            enableWildcard: false } as IMonitorPathInfo
        ] as IMonitorPathInfo[],
        (m: IMonitor): void => {
            count++;
            console.log(`Monitor[${tag}] 'c.dt' triggered: count=${count} dirty=${JSON.stringify(m.dirty)}`);
        },
    );

    // autoProxyObject returns the same WrappedDate → identity unchanged → no fire.
    c.dt = c.dt;
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] Local Date: c.dt = c.dt does not fire: count=${count} === 0`, eq(count, 0));

    // Brand-new Date with the SAME wall-clock time wraps to a NEW WrappedDate
    // → `before !== now` → fires.
    c.dt = new Date(2020, 0, 15);
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] Local Date: c.dt = new Date(same time) fires: count=${count} === 1`, eq(count, 1));

    // Different time stamp — same identity-change reasoning, fires.
    c.dt = new Date(2025, 5, 30);
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] Local Date: c.dt = new Date(diff time) fires: count=${count} === 2`, eq(count, 2));
}

// Identity-lambda monitor on @Local Date. Inner-Date setters all leave the
// counter at 0 because the WrappedDate's shared meta isn't bound. A
// subsequent assignment fires once via the @Local backing's own meta.
function doMonitorOnLocalDateInnerSetterNoFireAssignmentFires(isSync: boolean): void {
    const tag = isSync ? 'sync' : 'async';
    let count: int = 0;
    const c = new ClassWithDate(null, new Date(2020, 0, 15));

    const _monitor = makeMonitorByMode(
        isSync,
        [{
            path: 'c.dt',
            valueCallback: () => c.dt,
            enableWildcard: false } as IMonitorPathInfo
        ] as IMonitorPathInfo[],
        (m: IMonitor): void => {
            count++;
            console.log(`Monitor[${tag}] 'c.dt' triggered: count=${count} dirty=${JSON.stringify(m.dirty)}`);
        },
    );

    c.dt.setDate(20); // 15 → 20
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] Local Date: c.dt.setDate(20) does not fire (no getter binding): count=${count} === 0`, eq(count, 0));

    c.dt.setDate(20); // idempotent
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] Local Date: c.dt.setDate(20) idempotent does not fire: count=${count} === 0`, eq(count, 0));

    c.dt.setHours(5); // cross-field setter on shared meta
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] Local Date: c.dt.setHours cross-field does not fire: count=${count} === 0`, eq(count, 0));

    c.dt.setDate(25);
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] Local Date: c.dt.setDate(25) does not fire: count=${count} === 0`, eq(count, 0));

    // Assignment goes through the @Local setter, fires.
    c.dt = new Date(2025, 5, 30);
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] Local Date: c.dt = new Date(diff time) fires: count=${count} === 1`, eq(count, 1));
}

// Wildcard monitor on @Local Date. ClassWithDate implements IObservedAnyProp
// with a paired __meta_dt that the dt setter fires alongside the @Local
// backing meta. Because the wildcard binds via addRefAnyProp, inner-Date
// setters all queue dirty refs that fire once each — even idempotent setDate
// and cross-field setHours.
function doMonitorOnLocalDateWildcardPairedMetaFires(isSync: boolean): void {
    const tag = isSync ? 'sync' : 'async';
    let count: int = 0;
    const c = new ClassWithDate(null, new Date(2020, 0, 15));

    const _monitor = makeMonitorByMode(
        isSync,
        [{
            path: 'c.dt.*',
            valueCallback: () => c.dt,
            enableWildcard: true } as IMonitorPathInfo
        ] as IMonitorPathInfo[],
        (m: IMonitor): void => {
            count++;
            console.log(`Monitor[${tag}] 'c.dt.*' triggered: count=${count} dirty=${JSON.stringify(m.dirty)}`);
        },
    );

    c.dt.setDate(20);
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] Local Date wildcard: c.dt.setDate(20) fires: count=${count} === 1`, eq(count, 1));

    c.dt.setDate(20); // idempotent
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] Local Date wildcard: c.dt.setDate(20) idempotent fires: count=${count} === 2`, eq(count, 2));

    c.dt.setHours(5); // cross-field
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] Local Date wildcard: c.dt.setHours cross-field fires: count=${count} === 3`, eq(count, 3));

    c.dt.setDate(25);
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] Local Date wildcard: c.dt.setDate(25) fires: count=${count} === 4`, eq(count, 4));

    c.dt.setDate(25); // idempotent
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] Local Date wildcard: c.dt.setDate(25) idempotent fires: count=${count} === 5`, eq(count, 5));
}

// === Suite wiring ==========================================================

function runDateSuite(isSync: boolean): void {
    const factoryName = isSync ? 'makeSyncMonitor' : 'makeMonitor';

    tcase(`### ${factoryName} on WrappedDate: identity lambda does not bind shared meta — setDate calls do not fire`)
    {
        doMonitorOnDateSetterNoFireIdentityLambda(isSync);
    }

    tcase(`### ${factoryName} on WrappedDate: identity lambda does not bind shared meta — setHours overloads do not fire`)
    {
        doMonitorOnDateSetHoursOverloadsNoFireIdentityLambda(isSync);
    }

    tcase(`### ${factoryName} wildcard on WrappedDate: setTime fires via wildcard transit-dep branch`)
    {
        doMonitorOnDateWildcardSetTimeFires(isSync);
    }

    tcase(`### ${factoryName} on @Local Date: c.dt = c.dt no-op; new Date instance fires (identity LSV)`)
    {
        doMonitorOnLocalDateAssignment(isSync);
    }

    tcase(`### ${factoryName} on @Local Date: inner-Date setters do not fire; assignment fires via @Local meta`)
    {
        doMonitorOnLocalDateInnerSetterNoFireAssignmentFires(isSync);
    }

    tcase(`### ${factoryName} wildcard on @Local Date: every inner-Date setter fires via paired __meta_dt`)
    {
        doMonitorOnLocalDateWildcardPairedMetaFires(isSync);
    }
}

export function run_monitor_date(): boolean {
    const ttest = tsuite('@Monitor WrappedDate / @Local Date') {
        runDateSuite(/* isSync */ false);
    }
    ttest();
    return true;
}

export function run_syncmonitor_date(): boolean {
    const ttest = tsuite('@SyncMonitor WrappedDate / @Local Date') {
        runDateSuite(/* isSync */ true);
    }
    ttest();
    return true;
}
