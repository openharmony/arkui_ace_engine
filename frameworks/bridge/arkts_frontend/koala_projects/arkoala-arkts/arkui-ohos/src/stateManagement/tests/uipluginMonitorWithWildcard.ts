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


import { tsuite, tcase, test, eq } from './lib/testFramework'
import { IMonitor, IMonitorPathInfo, IMonitorDecoratedVariable } from '../decorator'
import { ClassB, ClassC, ClassA_ObserveAnyProp_NoAnyMeta } from './uipluginObservedObject3'
import { ObserveSingleton } from '../base/observeSingleton';
import { STATE_MGMT_FACTORY } from '../decorator'
import { MyArray } from './uiplugin_custom_arrays'

import { ParentComponent, ComponentWithArray } from './uipluginAddMonitorWildcards'

let stateMgmtConsole = console;

// -----------------------------------------------------------------------------
// All helpers in this file drive monitors created via STATE_MGMT_FACTORY.makeMonitor
// (async dispatch). Sync-monitor coverage lives in uipluginSyncMonitor.ts, and
// UIUtils.addMonitor (the higher-level path-validating API) is covered by
// uipluginAddMonitorWildcards.ts.
// -----------------------------------------------------------------------------


// Helper: basic wildcard monitor over a single IObserveAnyProp-implementing
// object. Verifies that reassigning any @Track property on the observed object
// fires the monitor and that reassigning an untracked property does not.
//
// Async dispatch: updateDirty() coalesces all dirty refs queued since the last
// drain into exactly one monitorFunction invocation via the Set-based dedup
// inside notifyDirtyMonitorPaths.
function doMakeMonitorWildcardSinglePath(): void {
    let comp = new ParentComponent(null, {});
    let count: int = 0;
    const onChanged = (_m: IMonitor) => {
        stateMgmtConsole.debug(`doMakeMonitorWildcardSinglePath fired`);
        count++;
    }

    // Keep the monitor alive for the whole tcase (decorator value holds a ref).
    let _monitor: IMonitorDecoratedVariable = STATE_MGMT_FACTORY.makeMonitor(
        new Array<IMonitorPathInfo>(
            {
                path: 'comp.a_anyprop_no_meta.*',
                isWildcard: true,
                valueCallback: () => {
                    console.log('lambda for path comp.a_anyprop_no_meta.*');
                    return comp.a_anyprop_no_meta;
                }
            } as IMonitorPathInfo
        ),
        onChanged
    );

    // Three mutations between updateDirty() calls are coalesced into ONE callback.
    comp.a_anyprop_no_meta.classB = new ClassB();
    comp.a_anyprop_no_meta.classC = new ClassC();
    comp.a_anyprop_no_meta.classB.propB1 = 'new again';

    test('wildcard single path: count == 0 before updateDirty (async)', eq(count, 0))
    ObserveSingleton.instance.updateDirty();
    test('wildcard single path: count == 1 after updateDirty (coalesced)', eq(count, 1))

    // A later mutation + drain produces exactly one more callback.
    comp.a_anyprop_no_meta.classC = new ClassC();
    ObserveSingleton.instance.updateDirty();
    test('wildcard single path: count == 2 after second updateDirty', eq(count, 2))

    // Mutating an untracked property (propA has no @Track meta) must NOT add to
    // the dirty set at all, so the callback count stays at 2.
    comp.a_anyprop_no_meta.propA++;
    ObserveSingleton.instance.updateDirty();
    test('wildcard single path: untracked propA++ does not fire',  eq(count, 2))
}


// Helper: verifies the IMonitor.dirty list and IMonitor.value<T>(path) lookup
// for a wildcard path. Replaces the old non-wildcard "m.dirty / m.value" API
// check — the assertions still exercise the same IMonitor surface, just with
// the wildcard path string as the lookup key.
function doMakeMonitorWildcardVerifyIMonitorAPI(): void {
    let comp = new ParentComponent(null, {});
    const wildcardPath = 'comp.a_anyprop_no_meta.*';
    let count: int = 0;
    let lastDirty: Array<string> = new Array<string>();
    let lookupPath: string = '';

    const onChanged = (m: IMonitor) => {
        count++;
        lastDirty = m.dirty;
        let v = m.value<ClassA_ObserveAnyProp_NoAnyMeta>(wildcardPath);
        lookupPath = v === undefined ? '' : v!.path;
    }

    let _monitor: IMonitorDecoratedVariable = STATE_MGMT_FACTORY.makeMonitor(
        new Array<IMonitorPathInfo>(
            {
                path: wildcardPath,
                isWildcard: true,
                valueCallback: () => comp.a_anyprop_no_meta
            } as IMonitorPathInfo
        ),
        onChanged
    );

    comp.a_anyprop_no_meta.classB = new ClassB();
    ObserveSingleton.instance.updateDirty();

    test('IMonitor API: callback ran once', eq(count, 1))
    test('IMonitor API: m.dirty length == 1', eq(lastDirty.length, 1))
    test('IMonitor API: m.dirty[0] is wildcard path', eq(lastDirty[0], wildcardPath))
    test('IMonitor API: m.value(path).path matches wildcard path', eq(lookupPath, wildcardPath))
}


// Helper: path string ends in ".*" but the IMonitorPathInfo.isWildcard flag is
// EXPLICITLY false. In that configuration the framework must NOT auto-bind
// every tracked property on the observed object — only the refs read by the
// value lambda are tracked. The lambda here reads only the parent reference,
// so reassigning child tracked properties (classB, classC, propB1) must never
// fire the monitor.
//
// This test guards the decoratorMonitor.ts:137-142 branch: the addRefAnyProp()
// call is gated on `monitorValue.isWildcard`, not on the path string shape.
function doMakeMonitorWildcardFlagFalse(): void {
    let comp = new ParentComponent(null, {});
    let count: int = 0;
    const onChanged = (_m: IMonitor) => {
        stateMgmtConsole.debug(`doMakeMonitorWildcardFlagFalse fired`);
        count++;
    }

    let _monitor: IMonitorDecoratedVariable = STATE_MGMT_FACTORY.makeMonitor(
        new Array<IMonitorPathInfo>(
            {
                path: 'comp.a_anyprop_no_meta.*',
                isWildcard: false,
                valueCallback: () => comp.a_anyprop_no_meta
            } as IMonitorPathInfo
        ),
        onChanged
    );

    comp.a_anyprop_no_meta.classB = new ClassB();
    comp.a_anyprop_no_meta.classC = new ClassC();
    comp.a_anyprop_no_meta.classB.propB1 = 'new again';
    test('wildcard flag false: count == 0 before updateDirty', eq(count, 0))
    ObserveSingleton.instance.updateDirty();
    test('wildcard flag false: count == 0 after updateDirty (not wired as wildcard)', eq(count, 0))

    comp.a_anyprop_no_meta.classC = new ClassC();
    ObserveSingleton.instance.updateDirty();
    test('wildcard flag false: second classC write still does not fire', eq(count, 0))
}


// Helper: ONE monitor with TWO wildcard paths rooted at TWO DIFFERENT
// ParentComponent instances. Verifies that a single MonitorFunctionDecorator
// can observe multiple independent objects via wildcards and that the async
// drain's Set-based dedup fires the callback once per drain cycle regardless
// of which object was mutated.
function doMakeMonitorWildcardTwoComponents(): void {
    let c1 = new ParentComponent(null, {});
    let c2 = new ParentComponent(null, {});
    let count: int = 0;
    const onChanged = (_m: IMonitor) => {
        stateMgmtConsole.debug(`doMakeMonitorWildcardTwoComponents fired`);
        count++;
    }

    let _monitor: IMonitorDecoratedVariable = STATE_MGMT_FACTORY.makeMonitor(
        new Array<IMonitorPathInfo>(
            {
                path: 'c1.a_anyprop_no_meta.*',
                isWildcard: true,
                valueCallback: () => c1.a_anyprop_no_meta
            } as IMonitorPathInfo,
            {
                path: 'c2.a_anyprop_no_meta.*',
                isWildcard: true,
                valueCallback: () => c2.a_anyprop_no_meta
            } as IMonitorPathInfo
        ),
        onChanged
    );

    // Mutations on BOTH components queue dirty refs in monitorPathRefsChanged_.
    // The Set-based dedup inside notifyDirtyMonitorPaths coalesces everything
    // into a SINGLE callback invocation per updateDirty() cycle.
    c1.a_anyprop_no_meta.classB = new ClassB();
    c1.a_anyprop_no_meta.classC = new ClassC();
    c1.a_anyprop_no_meta.classB.propB1 = 'new again';
    c2.a_anyprop_no_meta.classB = new ClassB();
    c2.a_anyprop_no_meta.classC = new ClassC();
    c2.a_anyprop_no_meta.classB.propB1 = 'new again';
    test('two components: count == 0 before updateDirty', eq(count, 0))
    ObserveSingleton.instance.updateDirty();
    test('two components: count == 1 after coalesced drain', eq(count, 1))

    // A single mutation on c2 alone fires the monitor once more.
    c2.a_anyprop_no_meta.classC = new ClassC();
    ObserveSingleton.instance.updateDirty();
    test('two components: count == 2 after second drain', eq(count, 2))

    // A single mutation on c1 alone also fires it.
    c1.a_anyprop_no_meta.classB = new ClassB();
    ObserveSingleton.instance.updateDirty();
    test('two components: count == 3 after c1 drain', eq(count, 3))
}


// Helper: single makeMonitor call with a mix of a non-wildcard path and a
// wildcard path rooted at the SAME IObserveAnyProp-implementing object. Both
// paths share __meta_classB as a binding target, so writes to classB (or to
// anything reachable from the non-wildcard lambda) dirty both paths; writes
// to classC go only through the wildcard branch.
//
// This is the async twin of doAddMonitorMixedWildAndNonWild in the
// uipluginAddMonitorWildcards.ts file.
function doMakeMonitorMixedWildAndNonWild(): void {
    let comp = new ParentComponent(null, {});
    let count: int = 0;
    const onChanged = (_m: IMonitor) => {
        stateMgmtConsole.debug(`doMakeMonitorMixedWildAndNonWild fired`);
        count++;
    }

    let _monitor: IMonitorDecoratedVariable = STATE_MGMT_FACTORY.makeMonitor(
        new Array<IMonitorPathInfo>(
            // Non-wildcard: reads comp.a_anyprop_no_meta.classB.propB1 — binds
            // __meta_classB (via the classB getter) and classB's own propB1 meta.
            {
                path: 'comp.a_anyprop_no_meta.classB.propB1',
                isWildcard: false,
                valueCallback: () => comp.a_anyprop_no_meta.classB.propB1
            } as IMonitorPathInfo,
            // Wildcard: reads comp.a_anyprop_no_meta — addRefAnyProp() binds
            // both __meta_classB and __meta_classC.
            {
                path: 'comp.a_anyprop_no_meta.*',
                isWildcard: true,
                valueCallback: () => comp.a_anyprop_no_meta
            } as IMonitorPathInfo
        ),
        onChanged
    );

    // 1) Write to propB1: dirties only the non-wildcard path (propB1 lives on
    //    ClassB, not on the IObserveAnyProp parent). Async drain → count 1.
    comp.a_anyprop_no_meta.classB.propB1 = 'new';
    ObserveSingleton.instance.updateDirty();
    test('mixed: count == 1 after propB1 write', eq(count, 1))

    // 2) Write classC. Only the wildcard path is bound to __meta_classC
    //    (the non-wildcard lambda reads propB1 via classB, not classC).
    //    Async drain → count 2.
    comp.a_anyprop_no_meta.classC = new ClassC();
    ObserveSingleton.instance.updateDirty();
    test('mixed: count == 2 after classC write', eq(count, 2))

    // 3) Untracked write: neither path fires.
    comp.a_anyprop_no_meta.propA++;
    ObserveSingleton.instance.updateDirty();
    test('mixed: count == 2 after untracked propA++', eq(count, 2))

    // 4) Write classB — dirties BOTH paths (non-wildcard reads classB on the
    //    way to propB1, wildcard binds __meta_classB). Upstream's async drain
    //    deduplicates via Set<MonitorFunctionDecorator>, so exactly ONE
    //    callback invocation, count 3.
    comp.a_anyprop_no_meta.classB = new ClassB();
    ObserveSingleton.instance.updateDirty();
    test('mixed: count == 3 after classB write (dedup)', eq(count, 3))
}


// Helper: single makeMonitor call that mixes a non-wildcard path on one
// ParentComponent and a wildcard path on a SEPARATE ParentComponent, then
// drives mutations on both.
//
// Async twin of doAddMonitorMixedWildAndNonWildDifferentObjects.
function doMakeMonitorMixedWildAndNonWildDifferentObjects(): void {
    let comp = new ParentComponent(null, {});
    let other = new ParentComponent(null, {});
    let count: int = 0;
    const onChanged = (_m: IMonitor) => {
        stateMgmtConsole.debug(`doMakeMonitorMixedWildAndNonWildDifferentObjects fired`);
        count++;
    }

    let _monitor: IMonitorDecoratedVariable = STATE_MGMT_FACTORY.makeMonitor(
        new Array<IMonitorPathInfo>(
            // Non-wildcard on comp: tracks propB1 transitively.
            {
                path: 'comp.a_anyprop_no_meta.classB.propB1',
                isWildcard: false,
                valueCallback: () => comp.a_anyprop_no_meta.classB.propB1
            } as IMonitorPathInfo,
            // Wildcard on `other`.
            {
                path: 'other.a_anyprop_no_meta.*',
                isWildcard: true,
                valueCallback: () => other.a_anyprop_no_meta
            } as IMonitorPathInfo
        ),
        onChanged
    );

    // Non-wildcard fire via comp.
    comp.a_anyprop_no_meta.classB.propB1 = 'new';
    ObserveSingleton.instance.updateDirty();
    test('mixed 2 objects: count == 1 after comp propB1 write', eq(count, 1))

    // Wildcard fire via other.
    other.a_anyprop_no_meta.classC = new ClassC();
    ObserveSingleton.instance.updateDirty();
    test('mixed 2 objects: count == 2 after other classC write', eq(count, 2))

    // Both mutations before the same drain coalesce into ONE callback due to
    // async dedup (Set<MonitorFunctionDecorator>).
    comp.a_anyprop_no_meta.classB.propB1 = 'new again';
    other.a_anyprop_no_meta.classB = new ClassB();
    ObserveSingleton.instance.updateDirty();
    test('mixed 2 objects: count == 3 after simultaneous drain (dedup)', eq(count, 3))

    // Untracked mutation on either component is still a no-op.
    other.a_anyprop_no_meta.propA++;
    ObserveSingleton.instance.updateDirty();
    test('mixed 2 objects: count == 3 after untracked other propA++', eq(count, 3))
}


// Helper: one makeMonitor call with a non-wildcard path AND a wildcard path
// that both bind __meta_classB on the SAME object. A single mutation to classB
// enqueues both path refs; notifyDirtyMonitorPaths' Set<MonitorFunctionDecorator>
// dedup must collapse them into ONE callback invocation.
//
// Async counterpart of doAddMonitorDedupOverlappingPaths. Both pre- and
// post-rebase implementations should pass this test because the async drain
// has always used dedup; the helper guards against future changes that might
// remove or break that Set dedup.
function doMakeMonitorDedupOverlappingPaths(): void {
    let comp = new ParentComponent(null, {});
    let count: int = 0;
    const onChanged = (_m: IMonitor) => {
        stateMgmtConsole.debug(`doMakeMonitorDedupOverlappingPaths fired`);
        count++;
    }

    let _monitor: IMonitorDecoratedVariable = STATE_MGMT_FACTORY.makeMonitor(
        new Array<IMonitorPathInfo>(
            // Non-wildcard bound to __meta_classB via the classB getter.
            {
                path: 'comp.a_anyprop_no_meta.classB',
                isWildcard: false,
                valueCallback: () => comp.a_anyprop_no_meta.classB
            } as IMonitorPathInfo,
            // Wildcard also bound to __meta_classB via addRefAnyProp().
            {
                path: 'comp.a_anyprop_no_meta.*',
                isWildcard: true,
                valueCallback: () => comp.a_anyprop_no_meta
            } as IMonitorPathInfo
        ),
        onChanged
    );

    // Single mutation dirties BOTH overlapping paths.
    comp.a_anyprop_no_meta.classB = new ClassB();
    test('dedup overlapping: count == 0 before updateDirty (async)', eq(count, 0))
    ObserveSingleton.instance.updateDirty();
    test('dedup overlapping: count == 1 after drain (not 2)', eq(count, 1))
}


// Helper: single wildcard path rooted at a custom Array wrapped via
// ComponentWithArray. The value lambda returns the MyArray<number> instance;
// the framework sees that `monitorValue.now instanceof ObserveWrappedKeyedMeta`
// and calls addRefAnyKey() (decoratorMonitor.ts:137-142), which binds the
// monitor to every keyed slot of the array. Any indexed assignment or mutating
// method (sort, push-via-wrapper, etc.) must fire the monitor; multiple
// mutations between updateDirty() calls are coalesced into ONE callback by
// the async drain's Set dedup in notifyDirtyMonitorPaths.
function doMakeMonitorWildcardSingleArray(): void {
    let comp = new ComponentWithArray(null, {});
    let count: int = 0;
    const onChanged = (_m: IMonitor) => {
        stateMgmtConsole.debug(`doMakeMonitorWildcardSingleArray fired`);
        count++;
    }

    let _monitor: IMonitorDecoratedVariable = STATE_MGMT_FACTORY.makeMonitor(
        new Array<IMonitorPathInfo>(
            {
                path: 'comp.arr.*',
                isWildcard: true,
                valueCallback: () => {
                    console.log('lambda for path comp.arr.*');
                    return comp.arr;
                }
            } as IMonitorPathInfo
        ),
        onChanged
    );

    // Element assignment on the underlying array fires the keyed meta.
    comp.arr[1] = 99;
    test('wildcard single array: count == 0 before updateDirty', eq(count, 0))
    ObserveSingleton.instance.updateDirty();
    test('wildcard single array: count == 1 after arr[1] write', eq(count, 1))

    comp.arr[2] = 500;
    ObserveSingleton.instance.updateDirty();
    test('wildcard single array: count == 2 after arr[2] write', eq(count, 2))

    // Mutating method: sort() fires via the wrapped array.
    comp.arr.sort();
    ObserveSingleton.instance.updateDirty();
    test('wildcard single array: count == 3 after arr.sort()', eq(count, 3))

    // Multiple element writes before one drain are coalesced into ONE callback.
    comp.arr[0] = 111;
    comp.arr[1] = 222;
    comp.arr[2] = 333;
    ObserveSingleton.instance.updateDirty();
    test('wildcard single array: count == 4 after triple write + single drain', eq(count, 4))
}


// Helper: one monitor whose pathInfo array mixes a WILDCARD path rooted at one
// MyArray and a NON-WILDCARD path rooted at a DIFFERENT MyArray's @Trace
// arrProp. The wildcard side fires on any keyed mutation (indexed write, sort);
// the non-wildcard side fires only when the specific property it reads changes
// (here, MyArray.arrProp, which is backed by its own __meta_arrProp).
//
// Writing to an element of the non-wildcard array MUST NOT fire the monitor —
// the non-wildcard lambda reads only `arrNoWild.arr.arrProp`, so it is not
// bound to the array's keyed meta.
function doMakeMonitorTwoArraysOneWildcardOneNot(): void {
    let compWild = new ComponentWithArray(null, {});
    let compNoWild = new ComponentWithArray(null, {});
    let count: int = 0;
    const onChanged = (_m: IMonitor) => {
        stateMgmtConsole.debug(`doMakeMonitorTwoArraysOneWildcardOneNot fired`);
        count++;
    }

    let _monitor: IMonitorDecoratedVariable = STATE_MGMT_FACTORY.makeMonitor(
        new Array<IMonitorPathInfo>(
            // Wildcard on compWild.arr — binds every keyed slot via addRefAnyKey.
            {
                path: 'compWild.arr.*',
                isWildcard: true,
                valueCallback: () => compWild.arr
            } as IMonitorPathInfo,
            // Non-wildcard on compNoWild.arr.arrProp — binds only __meta_arrProp.
            {
                path: 'compNoWild.arr.arrProp',
                isWildcard: false,
                valueCallback: () => compNoWild.arr.arrProp
            } as IMonitorPathInfo
        ),
        onChanged
    );

    // Wildcard side fires on indexed write.
    compWild.arr[0] = 99;
    ObserveSingleton.instance.updateDirty();
    test('two arrays mixed: count == 1 after wildcard arr[0] write', eq(count, 1))

    // Non-wildcard side fires on arrProp assignment.
    compNoWild.arr.arrProp = 'new';
    ObserveSingleton.instance.updateDirty();
    test('two arrays mixed: count == 2 after non-wildcard arrProp write', eq(count, 2))

    // Indexed write on the non-wildcard array must NOT fire — the path binds
    // only __meta_arrProp, not the keyed meta.
    compNoWild.arr[0] = 77;
    ObserveSingleton.instance.updateDirty();
    test('two arrays mixed: count == 2 after compNoWild element write (no fire)', eq(count, 2))

    // Simultaneous mutations on both arrays before a single drain — async
    // Set dedup coalesces both dirty refs into ONE callback invocation.
    compWild.arr.sort();
    compNoWild.arr.arrProp = 'new again';
    ObserveSingleton.instance.updateDirty();
    test('two arrays mixed: count == 3 after coalesced drain (dedup)', eq(count, 3))
}


// Helper: one monitor with two WILDCARD paths, one rooted at a MyArray (via
// ComponentWithArray → ObserveWrappedKeyedMeta → addRefAnyKey binds every
// keyed slot) and the other rooted at an IObserveAnyProp class object (via
// addRefAnyProp binds every @Track meta). Verifies the decoratorMonitor.ts
// wildcard branch routes to the right auxiliary call depending on
// `monitorValue.now instanceof ObserveWrappedKeyedMeta` vs `IObserveAnyProp`
// (see decoratorMonitor.ts:137-142).
function doMakeMonitorArrayAndClassBothWildcards(): void {
    let compArr = new ComponentWithArray(null, {});
    let compObj = new ParentComponent(null, {});
    let count: int = 0;
    const onChanged = (_m: IMonitor) => {
        stateMgmtConsole.debug(`doMakeMonitorArrayAndClassBothWildcards fired`);
        count++;
    }

    let _monitor: IMonitorDecoratedVariable = STATE_MGMT_FACTORY.makeMonitor(
        new Array<IMonitorPathInfo>(
            // Wildcard #1: MyArray via ObserveWrappedKeyedMeta path.
            {
                path: 'compArr.arr.*',
                isWildcard: true,
                valueCallback: () => compArr.arr
            } as IMonitorPathInfo,
            // Wildcard #2: IObserveAnyProp object via addRefAnyProp.
            {
                path: 'compObj.a_anyprop_no_meta.*',
                isWildcard: true,
                valueCallback: () => compObj.a_anyprop_no_meta
            } as IMonitorPathInfo
        ),
        onChanged
    );

    // Array keyed-slot mutation → wildcard #1 fires.
    compArr.arr[0] = 99;
    ObserveSingleton.instance.updateDirty();
    test('array + class both wildcards: count == 1 after array element write', eq(count, 1))

    // Tracked property mutation on the IObserveAnyProp object → wildcard #2 fires.
    compObj.a_anyprop_no_meta.classB = new ClassB();
    ObserveSingleton.instance.updateDirty();
    test('array + class both wildcards: count == 2 after class classB write', eq(count, 2))

    // Simultaneous mutations on both roots before one drain → Set dedup
    // collapses both into a single callback.
    compArr.arr.sort();
    compObj.a_anyprop_no_meta.classC = new ClassC();
    ObserveSingleton.instance.updateDirty();
    test('array + class both wildcards: count == 3 after coalesced drain', eq(count, 3))

    // Untracked property on the class object must NOT fire — addRefAnyProp
    // only binds @Track metas and propA has no meta.
    compObj.a_anyprop_no_meta.propA++;
    ObserveSingleton.instance.updateDirty();
    test('array + class both wildcards: count == 3 after untracked propA++', eq(count, 3))
}


export function run_monitor_wildcard(): boolean {

    const ttest = tsuite('@Monitor with wildcards') {

    // Basic wildcard single path. Tracked mutations fire the monitor; untracked
    // mutations (propA++) are ignored. Multiple writes between updateDirty()
    // calls are coalesced into a single callback via the async drain's dedup.
    tcase('### makeMonitor wildcard single path, IObserveAnyProp object') {
        doMakeMonitorWildcardSinglePath();
    }

    // Verify the IMonitor.dirty list and IMonitor.value<T>(path) API surface
    // for a wildcard path. Replaces the old non-wildcard "m.dirty / m.value"
    // test case with a wildcard-flavored equivalent.
    tcase('### makeMonitor wildcard: IMonitor.dirty and IMonitor.value API') {
        doMakeMonitorWildcardVerifyIMonitorAPI();
    }

    // Path string ends in ".*" but isWildcard is explicitly false. The monitor
    // must bind only to refs actually read by the value lambda (here just the
    // parent reference), NOT to every @Track property via addRefAnyProp().
    tcase('### makeMonitor path \'.*\' with isWildcard: false (no auto-bind)') {
        doMakeMonitorWildcardFlagFalse();
    }

    // One monitor with two wildcards rooted at two separate components. Each
    // updateDirty cycle fires the callback exactly once regardless of how many
    // mutations happened across either component.
    tcase('### makeMonitor wildcards on two components in one monitor') {
        doMakeMonitorWildcardTwoComponents();
    }

    // Mix non-wildcard + wildcard paths on the same IObserveAnyProp object in
    // a single makeMonitor call. Covers all combinations of per-path targeted
    // writes and a shared (dedup-required) write to classB.
    tcase('### makeMonitor mixed wildcard + non-wildcard, same object') {
        doMakeMonitorMixedWildAndNonWild();
    }

    // Mix non-wildcard + wildcard paths on two different components. A single
    // drain coalesces simultaneous mutations across both components via async
    // Set dedup.
    tcase('### makeMonitor mixed wildcard + non-wildcard, different objects') {
        doMakeMonitorMixedWildAndNonWildDifferentObjects();
    }

    // Overlapping non-wildcard + wildcard paths bound to the same meta. Single
    // mutation must fire the callback once, not twice — regression guard for
    // the Set<MonitorFunctionDecorator> dedup inside notifyDirtyMonitorPaths.
    tcase('### makeMonitor dedup across overlapping wildcard + non-wildcard paths') {
        doMakeMonitorDedupOverlappingPaths();
    }

    // Single wildcard path rooted at a custom MyArray via ComponentWithArray.
    // Exercises the decoratorMonitor wildcard branch that calls addRefAnyKey()
    // on ObserveWrappedKeyedMeta instances.
    tcase('### makeMonitor single wildcard on array') {
        doMakeMonitorWildcardSingleArray();
    }

    // Two arrays in one monitor — wildcard on one, non-wildcard on the other.
    // Element writes on the wildcard array fire; element writes on the
    // non-wildcard array do not fire (its lambda reads only arrProp).
    tcase('### makeMonitor two arrays, one wildcard and one non-wildcard') {
        doMakeMonitorTwoArraysOneWildcardOneNot();
    }

    // Two wildcard paths in one monitor, one over a MyArray (ObserveWrappedKeyedMeta)
    // and one over an IObserveAnyProp class object. Verifies that the
    // decoratorMonitor wildcard branch dispatches to addRefAnyKey() vs
    // addRefAnyProp() correctly for each path type.
    tcase('### makeMonitor array + class object, both wildcards') {
        doMakeMonitorArrayAndClassBothWildcards();
    }

}

ttest();
return true;
}
