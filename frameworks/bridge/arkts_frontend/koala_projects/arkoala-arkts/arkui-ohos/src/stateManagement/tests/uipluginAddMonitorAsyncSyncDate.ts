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

// Date / @Local Date coverage for the UIUtils.addMonitor API,
// parameterized by `isSync` (passed as MonitorBaseOptions.isSynchronous).
// Mirrors uipluginMonitorAsyncSyncDate.ts: same six scenarios, same expected
// counts. addMonitor ultimately constructs the same MonitorFunctionDecorator
// as makeMonitor/makeSyncMonitor, so behavior matches.

import { tsuite, tcase, test, eq } from './lib/testFramework'
import {
    IMonitor,
    IMonitorDecoratedVariable,
} from '../decorator'
import { ClassWithDate } from './commonClasses'
import { ObserveSingleton } from '../base/observeSingleton';
import { UIUtils, MonitorValueInfo, MonitorBaseOptions } from '../utils';

// Strong-reference store. Without this, locally-scoped monitors get GC'd
// after the test function stops reading them, clearing the WeakRefs in
// MutableStateMeta.bindingRefs_ mid-test and causing intermittent missing
// callbacks.
const testMonitors_: Array<IMonitorDecoratedVariable> = new Array<IMonitorDecoratedVariable>();

// === WrappedDate tests =====================================================

// Identity-lambda monitor: lambda returns `d` without calling any getter,
// so the WrappedDate's shared __meta is never bound and inner-Date setters
// cannot reach the monitor. setDate (changed value, idempotent repeat, then
// a different value) all leave the counter at 0 in either mode.
function doAddMonitorOnDateSetterNoFireIdentityLambda(isSync: boolean): void {
    const tag = isSync ? 'sync' : 'async';
    let count: int = 0;
    const d = UIUtils.makeObserved(new Date(2020, 0, 15, 10, 30, 45, 100));

    const options: MonitorBaseOptions = { isSynchronous: isSync };
    const _monitor = UIUtils.addMonitor(
        { valueCallback: () => d, path: 'd' } as MonitorValueInfo,
        (m: IMonitor): void => {
            count++;
            console.log(`addMonitor[${tag}] 'd' triggered: count=${count} dirty=${JSON.stringify(m.dirty)}`);
        },
        options,
    );
    testMonitors_.push(_monitor);

    d.setDate(20); // 15 → 20
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] addMonitor date: setDate(20) does not fire (no getter binding): count=${count} === 0`, eq(count, 0));

    d.setDate(20); // idempotent
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] addMonitor date: setDate(20) idempotent does not fire: count=${count} === 0`, eq(count, 0));

    d.setDate(25); // change value
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] addMonitor date: setDate(25) does not fire (no getter binding): count=${count} === 0`, eq(count, 0));
}

// setHours has 4 overloads (1-arg through 4-arg). Same identity-lambda
// pattern — the WrappedDate's shared meta is never bound.
function doAddMonitorOnDateSetHoursOverloadsNoFireIdentityLambda(isSync: boolean): void {
    const tag = isSync ? 'sync' : 'async';
    let count: int = 0;
    const d = UIUtils.makeObserved(new Date(2020, 0, 15, 10, 30, 45, 100));

    const options: MonitorBaseOptions = { isSynchronous: isSync };
    const _monitor = UIUtils.addMonitor(
        { valueCallback: () => d, path: 'd' } as MonitorValueInfo,
        (m: IMonitor): void => {
            count++;
            console.log(`addMonitor[${tag}] 'date.getTime()' triggered: count=${count} dirty=${JSON.stringify(m.dirty)}`);
        },
        options,
    );
    testMonitors_.push(_monitor);

    d.setHours(11);
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] addMonitor date setHours(h): does not fire: count=${count} === 0`, eq(count, 0));

    d.setHours(12, 0);
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] addMonitor date setHours(h,m): does not fire: count=${count} === 0`, eq(count, 0));

    d.setHours(13, 0, 0);
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] addMonitor date setHours(h,m,s): does not fire: count=${count} === 0`, eq(count, 0));

    d.setHours(14, 0, 0, 0);
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] addMonitor date setHours(h,m,s,ms): does not fire: count=${count} === 0`, eq(count, 0));
}

// Wildcard monitor (observeProps: true) over UIUtils.makeObserved(Date) with
// an identity lambda. Unlike the non-wildcard variants, setTime fires the
// callback even without a getter binding — the wildcard transit-dep branch
// in MonitorValueInternal's LSV check picks up the source-of-fire.
function doAddMonitorOnDateWildcardSetTimeFires(isSync: boolean): void {
    const tag = isSync ? 'sync' : 'async';
    let count: int = 0;
    const d = UIUtils.makeObserved(new Date(0));

    const options: MonitorBaseOptions = { isSynchronous: isSync };
    const _monitor = UIUtils.addMonitor(
        { valueCallback: () => d, path: 'd', observeProps: true } as MonitorValueInfo,
        (m: IMonitor): void => {
            count++;
            console.log(`addMonitor[${tag}] 'date.valueOf()' triggered: count=${count} dirty=${JSON.stringify(m.dirty)}`);
        },
        options,
    );
    testMonitors_.push(_monitor);

    d.setTime(1_000_000_000);
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] addMonitor date setTime: fires: count=${count} === 1`, eq(count, 1));

    d.setTime(2_000_000_000);
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] addMonitor date setTime again: fires: count=${count} === 2`, eq(count, 2));
}

// === @Local Date tests =====================================================

// Lambda reads the WrappedDate identity (c.dt). Reassigning to a brand-new
// Date wraps it in a NEW WrappedDate, so identity changes → fire. Reassigning
// the same WrappedDate identity is autoProxyObject's no-op path → identity
// unchanged → no fire.
function doAddMonitorOnLocalDateAssignment(isSync: boolean): void {
    const tag = isSync ? 'sync' : 'async';
    let count: int = 0;
    const c = new ClassWithDate(null, new Date(2020, 0, 15));

    const options: MonitorBaseOptions = { isSynchronous: isSync };
    const _monitor = UIUtils.addMonitor(
        { valueCallback: () => c.dt, path: 'c.dt' } as MonitorValueInfo,
        (m: IMonitor): void => {
            count++;
            console.log(`addMonitor[${tag}] 'c.dt' triggered: count=${count} dirty=${JSON.stringify(m.dirty)}`);
        },
        options,
    );
    testMonitors_.push(_monitor);

    // autoProxyObject returns the same WrappedDate → identity unchanged → no fire.
    c.dt = c.dt;
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] addMonitor Local Date: c.dt = c.dt does not fire: count=${count} === 0`, eq(count, 0));

    // Brand-new Date with the SAME wall-clock time wraps to a NEW WrappedDate
    // → `before !== now` → fires.
    c.dt = new Date(2020, 0, 15);
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] addMonitor Local Date: c.dt = new Date(same time) fires: count=${count} === 1`, eq(count, 1));

    c.dt = new Date(2025, 5, 30);
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] addMonitor Local Date: c.dt = new Date(diff time) fires: count=${count} === 2`, eq(count, 2));
}

// Identity-lambda monitor on @Local Date. Inner-Date setters all leave the
// counter at 0 because the WrappedDate's shared meta isn't bound. A
// subsequent assignment fires once via the @Local backing's own meta.
function doAddMonitorOnLocalDateInnerSetterNoFireAssignmentFires(isSync: boolean): void {
    const tag = isSync ? 'sync' : 'async';
    let count: int = 0;
    const c = new ClassWithDate(null, new Date(2020, 0, 15));

    const options: MonitorBaseOptions = { isSynchronous: isSync };
    const _monitor = UIUtils.addMonitor(
        { valueCallback: () => c.dt, path: 'c.dt' } as MonitorValueInfo,
        (m: IMonitor): void => {
            count++;
            console.log(`addMonitor[${tag}] 'c.dt' triggered: count=${count} dirty=${JSON.stringify(m.dirty)}`);
        },
        options,
    );
    testMonitors_.push(_monitor);

    c.dt.setDate(20);
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] addMonitor Local Date: c.dt.setDate(20) does not fire (no getter binding): count=${count} === 0`, eq(count, 0));

    c.dt.setDate(20); // idempotent
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] addMonitor Local Date: c.dt.setDate(20) idempotent does not fire: count=${count} === 0`, eq(count, 0));

    c.dt.setHours(5); // cross-field
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] addMonitor Local Date: c.dt.setHours cross-field does not fire: count=${count} === 0`, eq(count, 0));

    c.dt.setDate(25);
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] addMonitor Local Date: c.dt.setDate(25) does not fire: count=${count} === 0`, eq(count, 0));

    // Assignment fires through the @Local setter.
    c.dt = new Date(2025, 5, 30);
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] addMonitor Local Date: c.dt = new Date(diff time) fires: count=${count} === 1`, eq(count, 1));
}

// Wildcard monitor on @Local Date. ClassWithDate implements IObservedAnyProp
// with a paired __meta_dt that the dt setter fires alongside the @Local
// backing meta. The wildcard binds via addRefAnyProp, so inner-Date setters
// all queue dirty refs that fire once each — even idempotent setDate and
// cross-field setHours.
function doAddMonitorOnLocalDateWildcardPairedMetaFires(isSync: boolean): void {
    const tag = isSync ? 'sync' : 'async';
    let count: int = 0;
    const c = new ClassWithDate(null, new Date(2020, 0, 15));

    const options: MonitorBaseOptions = { isSynchronous: isSync };
    const _monitor = UIUtils.addMonitor(
        { valueCallback: () => c.dt, path: 'c.dt.*', observeProps: true } as MonitorValueInfo,
        (m: IMonitor): void => {
            count++;
            console.log(`addMonitor[${tag}] 'c.dt.*' triggered: count=${count} dirty=${JSON.stringify(m.dirty)}`);
        },
        options,
    );
    testMonitors_.push(_monitor);

    c.dt.setDate(20);
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] addMonitor Local Date wildcard: c.dt.setDate(20) fires: count=${count} === 1`, eq(count, 1));

    c.dt.setDate(20); // idempotent
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] addMonitor Local Date wildcard: c.dt.setDate(20) idempotent fires: count=${count} === 2`, eq(count, 2));

    c.dt.setHours(5); // cross-field
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] addMonitor Local Date wildcard: c.dt.setHours cross-field fires: count=${count} === 3`, eq(count, 3));

    c.dt.setDate(25);
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] addMonitor Local Date wildcard: c.dt.setDate(25) fires: count=${count} === 4`, eq(count, 4));

    c.dt.setDate(25); // idempotent
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] addMonitor Local Date wildcard: c.dt.setDate(25) idempotent fires: count=${count} === 5`, eq(count, 5));
}

// === Suite wiring ==========================================================

function runAddMonitorDateSuite(isSync: boolean): void {
    const tag = isSync ? 'sync' : 'async';

    tcase(`### addMonitor[${tag}] on WrappedDate: identity lambda does not bind shared meta — setDate calls do not fire`)
    {
        doAddMonitorOnDateSetterNoFireIdentityLambda(isSync);
    }

    tcase(`### addMonitor[${tag}] on WrappedDate: identity lambda does not bind shared meta — setHours overloads do not fire`)
    {
        doAddMonitorOnDateSetHoursOverloadsNoFireIdentityLambda(isSync);
    }

    tcase(`### addMonitor[${tag}] wildcard on WrappedDate: setTime fires via wildcard transit-dep branch`)
    {
        doAddMonitorOnDateWildcardSetTimeFires(isSync);
    }

    tcase(`### addMonitor[${tag}] on @Local Date: c.dt = c.dt no-op; new Date instance fires (identity LSV)`)
    {
        doAddMonitorOnLocalDateAssignment(isSync);
    }

    tcase(`### addMonitor[${tag}] on @Local Date: inner-Date setters do not fire; assignment fires via @Local meta`)
    {
        doAddMonitorOnLocalDateInnerSetterNoFireAssignmentFires(isSync);
    }

    tcase(`### addMonitor[${tag}] wildcard on @Local Date: every inner-Date setter fires via paired __meta_dt`)
    {
        doAddMonitorOnLocalDateWildcardPairedMetaFires(isSync);
    }
}

export function run_addmonitor_date(): boolean {
    const ttest = tsuite('UIUtils.addMonitor (async) WrappedDate / @Local Date') {
        runAddMonitorDateSuite(/* isSync */ false);
    }
    ttest();
    return true;
}

export function run_addsyncmonitor_date(): boolean {
    const ttest = tsuite('UIUtils.addMonitor (sync) WrappedDate / @Local Date') {
        runAddMonitorDateSuite(/* isSync */ true);
    }
    ttest();
    return true;
}
