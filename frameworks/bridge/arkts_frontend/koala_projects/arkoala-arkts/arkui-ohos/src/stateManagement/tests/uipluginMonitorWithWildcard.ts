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
import { IMonitor, IMonitorPathInfo, IMonitorDecoratedVariable, MonitorCallback } from '../decorator'
import { ClassB_ObserveAnyProp, ClassC, ClassA_ObserveAnyProp_NoAnyMeta } from './uipluginObservedObject3'
import { ObserveSingleton } from '../base/observeSingleton';
import { STATE_MGMT_FACTORY } from '../decorator'
import { MyArray } from './uiplugin_custom_arrays'

import { ParentComponent, ComponentWithArray } from './uipluginAddMonitorWildcards'

let stateMgmtConsole = console;

// -----------------------------------------------------------------------------
// Helpers in this file are parameterized by `isSync`:
//   * isSync=false → STATE_MGMT_FACTORY.makeMonitor (async dispatch, callbacks
//     fire only after ObserveSingleton.instance.updateDirty()).
//   * isSync=true  → STATE_MGMT_FACTORY.makeSyncMonitor (callbacks fire
//     immediately inside MutableStateMeta.fireChange).
//
// run_monitor_wildcard() drives every helper with isSync=false.
// run_syncmonitor_wildcard() drives every helper with isSync=true.
//
// Counts diverge between modes when:
//   - multiple bound mutations happen between drains (async coalesces via the
//     Set<MonitorFunctionDecorator> dedup in notifyDirtyMonitorPaths; sync
//     fires the callback once per fireChange that has bound listeners), or
//   - bindings overlap across two paths of the same monitor and a single
//     fireChange dirties both refs (both modes dedup, because the dedup is
//     across paths-within-the-same-call, not across separate fireChange calls).
//
// UIUtils.addMonitor (the higher-level path-validating API) is covered by
// uipluginAddMonitorWildcards.ts.
// -----------------------------------------------------------------------------


// --- Mode-aware test plumbing ----------------------------------------------

// Strong-reference store for monitors created by makeMonitorByMode below.
// The Panda VM's GC eagerly reclaims locally-scoped monitors that are never
// read after `let _monitor = makeMonitor(...)`, which clears the WeakRefs in
// MutableStateMeta.bindingRefs_ mid-test and causes intermittent count=0
// failures. Pushing each created monitor here keeps it alive across the
// helper's mutations and assertions.
const testMonitors_: Array<IMonitorDecoratedVariable> = new Array<IMonitorDecoratedVariable>();

// Build a monitor in either sync or async mode. Both forms have the same
// (pathInfos, callback, options?) signature.
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

// Helper: basic wildcard monitor over a single IObserveAnyProp-implementing
// object. Verifies that reassigning any @Track property on the observed object
// fires the monitor and that reassigning an untracked property does not.
//
// Async dispatch coalesces multiple bound fireChanges between updateDirty()
// calls into ONE callback (via Set<MonitorFunctionDecorator> dedup inside
// notifyDirtyMonitorPaths). Sync fires once per fireChange with bound listeners.
function doMakeMonitorWildcardSinglePath(isSync: boolean): void {
    const tag = isSync ? 'sync' : 'async';
    const wildcardPath = 'comp.a_anyprop_no_meta.*';
    let comp = new ParentComponent(null, {});
    let count: int = 0;
    let lastDirtyLen: int = 0;
    let lastDirtyHead: string = '';
    let lastValueByPathUndef: boolean = false;
    let lastValueNoArgUndef: boolean = false;
    const onChanged: MonitorCallback = (m: IMonitor) => {
        stateMgmtConsole.debug(`doMakeMonitorWildcardSinglePath fired`);
        count++;
        const dirty = m.dirty;
        lastDirtyLen = dirty.length;
        lastDirtyHead = dirty.length > 0 ? dirty[0] : '';
        // Wildcard paths never resolve to a single observable read, so both
        // overloads of m.value() return undefined here (no before/now to read).
        const vByPath = m.value<ClassA_ObserveAnyProp_NoAnyMeta>(wildcardPath);
        lastValueByPathUndef = vByPath === undefined;
        const vNoArg = m.value<ClassA_ObserveAnyProp_NoAnyMeta>();
        lastValueNoArgUndef = vNoArg === undefined;
    }

    let _monitor: IMonitorDecoratedVariable = makeMonitorByMode(
        isSync,
        new Array<IMonitorPathInfo>(
            {
                path: wildcardPath,
                enableWildcard: true,
                valueCallback: () => {
                    console.log('lambda for path comp.a_anyprop_no_meta.*');
                    return comp.a_anyprop_no_meta;
                }
            } as IMonitorPathInfo
        ),
        onChanged
    );

    // 3 mutations; only the first two fire the wildcard binding (outer's
    // __meta_classB and __meta_classC). The third write targets the inner
    // ClassB_ObserveAnyProp's __meta_propB1 which the wildcard does not bind.
    comp.a_anyprop_no_meta.classB = new ClassB_ObserveAnyProp();
    comp.a_anyprop_no_meta.classC = new ClassC();
    comp.a_anyprop_no_meta.classB.propB1 = 'new again';

    // No updateDirty() here on purpose: in async mode the dirty queue never
    // drains, so the callback never fires (count stays 0). Sync fires inline.
    test(`${tag} wildcard single path: 3 writes (1 unbound, no drain): count=${count} === ${isSync ? 2 : 0}`, eq(count, isSync ? 2 : 0));
    if (isSync) {
        // Sync inline fires: every callback saw dirty length 1 with the wildcard path,
        // and m.value (both overloads) returned undefined.
        test(`${tag} wildcard single path: dirty.length === 1 in last sync callback`, eq(lastDirtyLen, 1));
        test(`${tag} wildcard single path: dirty[0] === wildcardPath`, eq(lastDirtyHead, wildcardPath));
        test(`${tag} wildcard single path: m.value(wildcardPath) === undefined`, eq(lastValueByPathUndef, true));
        test(`${tag} wildcard single path: m.value() === undefined`, eq(lastValueNoArgUndef, true));
    }

    // A later mutation on the bound wildcard target. Async coalesces the
    // still-queued bound writes from the previous batch + this new fire into
    // a single callback (count=1). Sync fired inline above and now adds 1 more.
    comp.a_anyprop_no_meta.classC = new ClassC();
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`${tag} wildcard single path: +classC: count=${count} === ${isSync ? 3 : 1}`, eq(count, isSync ? 3 : 1));
    // Single bound path means dirty length is always 1 when it fires.
    test(`${tag} wildcard single path: +classC: dirty.length === 1`, eq(lastDirtyLen, 1));
    test(`${tag} wildcard single path: +classC: dirty[0] === wildcardPath`, eq(lastDirtyHead, wildcardPath));
    test(`${tag} wildcard single path: +classC: m.value(wildcardPath) === undefined`, eq(lastValueByPathUndef, true));
    test(`${tag} wildcard single path: +classC: m.value() === undefined`, eq(lastValueNoArgUndef, true));

    // Untracked write (propA has no @Track meta) must not fire either mode —
    // captured values stay at the previous fire's snapshot.
    comp.a_anyprop_no_meta.propA++;
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`${tag} wildcard single path: +untracked propA++: count=${count} === ${isSync ? 3 : 1}`, eq(count, isSync ? 3 : 1));
    test(`${tag} wildcard single path: +untracked propA++: dirty.length unchanged`, eq(lastDirtyLen, 1));
    test(`${tag} wildcard single path: +untracked propA++: dirty[0] unchanged`, eq(lastDirtyHead, wildcardPath));
}

function doMakeMonitorWildcardSinglePathKeepLSV(isSync: boolean): void {
    const tag = isSync ? 'sync' : 'async';
    let comp = new ParentComponent(null, {});
    let count: int = 0;
    const onChanged: MonitorCallback = (_m: IMonitor) => {
        stateMgmtConsole.debug(`doMakeMonitorWildcardSinglePath fired`);
        count++;
    }

    let _monitor: IMonitorDecoratedVariable = makeMonitorByMode(
        isSync,
        new Array<IMonitorPathInfo>(
            {
                path: 'comp.a_anyprop_no_meta.classB.*',
                enableWildcard: true,
                valueCallback: () => {
                    console.log('lambda for path comp.a_anyprop_no_meta.*');
                    return comp.a_anyprop_no_meta.classB;
                }
            } as IMonitorPathInfo
        ),
        onChanged
    );

    let newA = new ClassA_ObserveAnyProp_NoAnyMeta();
    newA.classB = comp.a_anyprop_no_meta.classB;
    comp.a_anyprop_no_meta = newA;

    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    // sync: 2 separate fireChanges → 2 callbacks. async: 2 dirty refs → 1 coalesced callback.
    test(`${tag} wildcard single path: keep LSV: count=${count} === ${isSync ? 0 : 0}`, eq(count, isSync ? 0 : 0));

    comp.a_anyprop_no_meta = new ClassA_ObserveAnyProp_NoAnyMeta();

    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    // NOTE: re-enabled; test is expected to fail — known wildcard LSV bug:
    // wildcards over-fire on transit-dep changes. See memory note
    // project_wildcard_monitor_lsv_bug.md.
    test(`${tag} wildcard single path: keep LSV: count=${count} === ${isSync ? 1 : 1}`, eq(count, isSync ? 1 : 1));
}


// Helper: verifies the IMonitor.dirty list and IMonitor.value<T>(path) lookup
// for a wildcard path. Same single-fire behavior in both modes — one bound
// write, one callback, m.dirty has the wildcard path.
function doMakeMonitorWildcardVerifyIMonitorAPI(isSync: boolean): void {
    const tag = isSync ? 'sync' : 'async';
    let comp = new ParentComponent(null, {});
    const wildcardPath = 'comp.a_anyprop_no_meta.*';
    let count: int = 0;
    let lastDirty: Array<string> = new Array<string>();
    let lookupPath: string = '';

    const onChanged: MonitorCallback = (m: IMonitor) => {
        count++;
        lastDirty = m.dirty;
        let v = m.value<ClassA_ObserveAnyProp_NoAnyMeta>(wildcardPath);
        lookupPath = v === undefined ? '' : v!.path;
        test(`${tag} last dirty  ${wildcardPath} =====`, eq(lastDirty[0], wildcardPath));
        //TODO: IMonitor.value functions for wildcard path always returns undefined
        test(`${tag} onChanged wildcard value is undefined =====`, eq(v ===  undefined, true));
    }

    let _monitor: IMonitorDecoratedVariable = makeMonitorByMode(
        isSync,
        new Array<IMonitorPathInfo>(
            {
                path: wildcardPath,
                enableWildcard: true,
                valueCallback: () => comp.a_anyprop_no_meta
            } as IMonitorPathInfo
        ),
        onChanged
    );

    comp.a_anyprop_no_meta.classB = new ClassB_ObserveAnyProp();
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }

    test(`${tag} IMonitor API: callback ran once: count=${count} === ${isSync ? 1 : 1}`, eq(count, isSync ? 1 : 1));
    test('IMonitor API: m.dirty length == 1', eq(lastDirty.length, 1))
    test('IMonitor API: m.dirty[0] is wildcard path', eq(lastDirty[0], wildcardPath))
    // m.value(wildcardPath) returns undefined (wildcards do not represent
    // a single observable read), so lookupPath is left at its empty-string
    // initial value.
    test('IMonitor API: m.value(wildcardPath) returns undefined', eq(lookupPath, ''))
}


// Helper: path string ends in ".*" but the IMonitorPathInfo.isWildcard flag is
// EXPLICITLY false. The framework must NOT auto-bind every tracked property —
// only refs read by the value lambda are tracked. The lambda here reads only
// the parent reference, so reassigning child tracked properties (classB,
// classC, propB1) must never fire the monitor in either mode.
//
// Guards the decoratorMonitor.ts addRefAnyProp() branch which is gated on
// `monitorValue.isWildcard`, not on the path string shape.
function doMakeMonitorWildcardFlagFalse(isSync: boolean): void {
    const tag = isSync ? 'sync' : 'async';
    let comp = new ParentComponent(null, {});
    let count: int = 0;
    const onChanged: MonitorCallback = (_m: IMonitor) => {
        stateMgmtConsole.debug(`doMakeMonitorWildcardFlagFalse fired`);
        count++;
    }

    let _monitor: IMonitorDecoratedVariable = makeMonitorByMode(
        isSync,
        new Array<IMonitorPathInfo>(
            {
                path: 'comp.a_anyprop_no_meta.*',
                enableWildcard: false,
                valueCallback: () => comp.a_anyprop_no_meta
            } as IMonitorPathInfo
        ),
        onChanged
    );

    comp.a_anyprop_no_meta.classB = new ClassB_ObserveAnyProp();
    comp.a_anyprop_no_meta.classC = new ClassC();
    comp.a_anyprop_no_meta.classB.propB1 = 'new again';
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`${tag} wildcard flag false: not wired as wildcard: count=${count} === ${isSync ? 0 : 0}`, eq(count, isSync ? 0 : 0));

    comp.a_anyprop_no_meta.classC = new ClassC();
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`${tag} wildcard flag false: second classC write: count=${count} === ${isSync ? 0 : 0}`, eq(count, isSync ? 0 : 0));
}


// Helper: ONE monitor with TWO wildcard paths rooted at TWO DIFFERENT
// ParentComponent instances. A single MonitorFunctionDecorator can observe
// multiple independent objects via wildcards. Async coalesces all
// fireChanges within a drain into one callback; sync fires once per
// fireChange (and there are several across two components).
function doMakeMonitorWildcardTwoComponents(isSync: boolean): void {
    const tag = isSync ? 'sync' : 'async';
    const path1 = 'c1.a_anyprop_no_meta.*';
    const path2 = 'c2.a_anyprop_no_meta.*';
    let c1 = new ParentComponent(null, {});
    let c2 = new ParentComponent(null, {});
    let count: int = 0;
    let lastDirty: Array<string> = new Array<string>();
    let maxDirtyLen: int = 0;
    let sawPath1: boolean = false;
    let sawPath2: boolean = false;
    const onChanged: MonitorCallback = (m: IMonitor) => {
        stateMgmtConsole.debug(`doMakeMonitorWildcardTwoComponents fired`);
        count++;
        lastDirty = m.dirty;
        if (lastDirty.length > maxDirtyLen) { maxDirtyLen = lastDirty.length; }
        for (let p of lastDirty) {
            if (p === path1) { sawPath1 = true; }
            if (p === path2) { sawPath2 = true; }
        }
    }

    let _monitor: IMonitorDecoratedVariable = makeMonitorByMode(
        isSync,
        new Array<IMonitorPathInfo>(
            {
                path: path1,
                enableWildcard: true,
                valueCallback: () => c1.a_anyprop_no_meta
            } as IMonitorPathInfo,
            {
                path: path2,
                enableWildcard: true,
                valueCallback: () => c2.a_anyprop_no_meta
            } as IMonitorPathInfo
        ),
        onChanged
    );

    // 4 bound writes (2 per component); the inner classB.propB1 writes are
    // unbound because the wildcards bind only outer @Track metas.
    c1.a_anyprop_no_meta.classB = new ClassB_ObserveAnyProp();
    c1.a_anyprop_no_meta.classC = new ClassC();
    c1.a_anyprop_no_meta.classB.propB1 = 'new again';
    c2.a_anyprop_no_meta.classB = new ClassB_ObserveAnyProp();
    c2.a_anyprop_no_meta.classC = new ClassC();
    c2.a_anyprop_no_meta.classB.propB1 = 'new again';
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    // sync: 4 fireChanges → 4 callbacks, each with one path dirty (max length 1).
    // async: 4 dirty refs → 1 coalesced callback, both wildcards dirty (length 2).
    test(`${tag} two components: bulk writes: count=${count} === ${isSync ? 4 : 1}`, eq(count, isSync ? 4 : 1));
    test(`${tag} two components: bulk writes: maxDirtyLen=${maxDirtyLen} === ${isSync ? 1 : 2}`, eq(maxDirtyLen, isSync ? 1 : 2));
    test(`${tag} two components: bulk writes: saw path1`, eq(sawPath1, true));
    test(`${tag} two components: bulk writes: saw path2`, eq(sawPath2, true));

    maxDirtyLen = 0;
    sawPath1 = false;
    sawPath2 = false;
    c2.a_anyprop_no_meta.classC = new ClassC();
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`${tag} two components: +c2 classC: count=${count} === ${isSync ? 5 : 2}`, eq(count, isSync ? 5 : 2));
    // Single fire on c2 — only path2 dirty in this callback.
    test(`${tag} two components: +c2 classC: lastDirty.length === 1`, eq(lastDirty.length, 1));
    test(`${tag} two components: +c2 classC: lastDirty[0] === path2`, eq(lastDirty[0], path2));

    maxDirtyLen = 0;
    sawPath1 = false;
    sawPath2 = false;
    c1.a_anyprop_no_meta.classB = new ClassB_ObserveAnyProp();
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`${tag} two components: +c1 classB: count=${count} === ${isSync ? 6 : 3}`, eq(count, isSync ? 6 : 3));
    test(`${tag} two components: +c1 classB: lastDirty.length === 1`, eq(lastDirty.length, 1));
    test(`${tag} two components: +c1 classB: lastDirty[0] === path1`, eq(lastDirty[0], path1));
}


// Helper: single makeMonitor call mixing a non-wildcard path and a wildcard
// path on the SAME IObserveAnyProp object. Both paths share __meta_classB as
// a binding target via different routes (non-wild reads classB getter,
// wildcard binds via addRefAnyProp).
//
// A single fireChange that dirties refs from both paths benefits from the
// per-call Set<MonitorFunctionDecorator> dedup in BOTH modes — the dedup is
// across paths within one call, not across separate fireChanges.
function doMakeMonitorMixedWildAndNonWild(isSync: boolean): void {
    const tag = isSync ? 'sync' : 'async';
    let comp = new ParentComponent(null, {});
    let count: int = 0;
    const onChanged: MonitorCallback = (_m: IMonitor) => {
        stateMgmtConsole.debug(`doMakeMonitorMixedWildAndNonWild fired`);
        count++;
    }

    let _monitor: IMonitorDecoratedVariable = makeMonitorByMode(
        isSync,
        new Array<IMonitorPathInfo>(
            // Non-wildcard reads classB.propB1 → binds outer __meta_classB and
            // inner classB's __meta_propB1.
            {
                path: 'comp.a_anyprop_no_meta.classB.propB1',
                enableWildcard: false,
                valueCallback: () => comp.a_anyprop_no_meta.classB.propB1
            } as IMonitorPathInfo,
            // Wildcard reads parent → addRefAnyProp() binds outer __meta_classB
            // and __meta_classC.
            {
                path: 'comp.a_anyprop_no_meta.*',
                enableWildcard: true,
                valueCallback: () => comp.a_anyprop_no_meta
            } as IMonitorPathInfo
        ),
        onChanged
    );

    // 1) Inner propB1 write: dirties only the non-wildcard path.
    comp.a_anyprop_no_meta.classB.propB1 = 'new';
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`${tag} mixed: propB1 write: count=${count} === ${isSync ? 1 : 1}`, eq(count, isSync ? 1 : 1));

    // 2) classC write: dirties only the wildcard path.
    comp.a_anyprop_no_meta.classC = new ClassC();
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`${tag} mixed: classC write: count=${count} === ${isSync ? 2 : 2}`, eq(count, isSync ? 2 : 2));

    // 3) Untracked write: neither path fires.
    comp.a_anyprop_no_meta.propA++;
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`${tag} mixed: untracked propA++: count=${count} === ${isSync ? 2 : 2}`, eq(count, isSync ? 2 : 2));

    // 4) classB write: outer __meta_classB.fireChange iterates bindingRefs (2
    //    refs to same monitor) and routes both to the dirty set; per-call
    //    Set<MonitorFunctionDecorator> dedup → ONE callback in both modes.
    comp.a_anyprop_no_meta.classB = new ClassB_ObserveAnyProp();
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`${tag} mixed: classB write (per-call dedup): count=${count} === ${isSync ? 3 : 3}`, eq(count, isSync ? 3 : 3));
}


// Helper: single makeMonitor call mixing a non-wildcard path on one
// ParentComponent and a wildcard path on a SEPARATE ParentComponent.
//
// Async coalesces simultaneous mutations on both components into one callback;
// sync fires per fireChange and so reports an extra callback for that batch.
function doMakeMonitorMixedWildAndNonWildDifferentObjects(isSync: boolean): void {
    const tag = isSync ? 'sync' : 'async';
    const nonWildPath = 'comp.a_anyprop_no_meta.classB.propB1';
    const wildPath = 'other.a_anyprop_no_meta.*';
    let comp = new ParentComponent(null, {});
    let other = new ParentComponent(null, {});
    let count: int = 0;
    let lastDirty: Array<string> = new Array<string>();
    let lastNonWildDefined: boolean = false;
    let lastNonWildBefore: string = '';
    let lastNonWildNow: string = '';
    let lastNonWildPath: string = '';
    let lastWildDefined: boolean = false;
    const onChanged: MonitorCallback = (m: IMonitor) => {
        stateMgmtConsole.debug(`doMakeMonitorMixedWildAndNonWildDifferentObjects fired`);
        count++;
        lastDirty = m.dirty;
        const nv = m.value<string>(nonWildPath);
        lastNonWildDefined = nv !== undefined;
        lastNonWildBefore = nv === undefined ? '' : nv!.before;
        lastNonWildNow = nv === undefined ? '' : nv!.now;
        lastNonWildPath = nv === undefined ? '' : nv!.path;
        const wv = m.value<ClassA_ObserveAnyProp_NoAnyMeta>(wildPath);
        lastWildDefined = wv !== undefined;
    }

    let _monitor: IMonitorDecoratedVariable = makeMonitorByMode(
        isSync,
        new Array<IMonitorPathInfo>(
            {
                path: nonWildPath,
                enableWildcard: false,
                valueCallback: () => comp.a_anyprop_no_meta.classB.propB1
            } as IMonitorPathInfo,
            {
                path: wildPath,
                enableWildcard: true,
                valueCallback: () => other.a_anyprop_no_meta
            } as IMonitorPathInfo
        ),
        onChanged
    );

    // 1) Non-wildcard fire via comp. Initial propB1 == 'BBB111'.
    comp.a_anyprop_no_meta.classB.propB1 = 'new';
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`${tag} mixed 2 objects: #1 propB1 on comp: count=${count} === 1`, eq(count, 1));
    test(`${tag} mixed 2 objects: #1 dirty.length === 1`, eq(lastDirty.length, 1));
    test(`${tag} mixed 2 objects: #1 dirty[0] === nonWildPath`, eq(lastDirty[0], nonWildPath));
    test(`${tag} mixed 2 objects: #1 m.value(nonWildPath) defined`, eq(lastNonWildDefined, true));
    test(`${tag} mixed 2 objects: #1 m.value(nonWildPath).path === nonWildPath`, eq(lastNonWildPath, nonWildPath));
    test(`${tag} mixed 2 objects: #1 m.value(nonWildPath).before === 'BBB111'`, eq(lastNonWildBefore, 'BBB111'));
    test(`${tag} mixed 2 objects: #1 m.value(nonWildPath).now === 'new'`, eq(lastNonWildNow, 'new'));
    test(`${tag} mixed 2 objects: #1 m.value(wildPath) === undefined`, eq(lastWildDefined, false));

    // 2) Wildcard fire via other. NO drain in async — leaves the wildcard
    //    queued for coalescing with step 3.
    other.a_anyprop_no_meta.classC = new ClassC();
    test(`${tag} mixed 2 objects: #2 classC on other: count=${count} === ${isSync ? 2 : 1}`, eq(count, isSync ? 2 : 1));
    if (isSync) {
        // Sync fired immediately for the wildcard only.
        test(`${tag} mixed 2 objects: #2 dirty.length === 1`, eq(lastDirty.length, 1));
        test(`${tag} mixed 2 objects: #2 dirty[0] === wildPath`, eq(lastDirty[0], wildPath));
        test(`${tag} mixed 2 objects: #2 m.value(nonWildPath) === undefined`, eq(lastNonWildDefined, false));
        test(`${tag} mixed 2 objects: #2 m.value(wildPath) === undefined`, eq(lastWildDefined, false));
    }

    // 3) Two SEPARATE fireChanges. Sync drains per fireChange → 2 more callbacks.
    //    Async drains the queued wildcard (from step 2) PLUS both new writes in
    //    one coalesced callback (count goes 1 → 2), with dirty containing both
    //    paths.
    comp.a_anyprop_no_meta.classB.propB1 = 'new again';
    other.a_anyprop_no_meta.classB = new ClassB_ObserveAnyProp();
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`${tag} mixed 2 objects: #3 simultaneous writes: count=${count} === ${isSync ? 4 : 2}`, eq(count, isSync ? 4 : 2));
    if (isSync) {
        // Sync ran two callbacks for step 3; LAST callback was for other.classB
        // (wildcard only) — non-wild MonitorValueInternal was reset between fires.
        test(`${tag} mixed 2 objects: #3 (sync last) dirty.length === 1`, eq(lastDirty.length, 1));
        test(`${tag} mixed 2 objects: #3 (sync last) dirty[0] === wildPath`, eq(lastDirty[0], wildPath));
        test(`${tag} mixed 2 objects: #3 (sync last) m.value(nonWildPath) === undefined`, eq(lastNonWildDefined, false));
    } else {
        // Async coalesced: dirty contains BOTH paths; non-wild m.value defined
        // with before='new' (post-step-1 reset) and now='new again'.
        test(`${tag} mixed 2 objects: #3 (async) dirty.length === 2`, eq(lastDirty.length, 2));
        let sawNonWild = false;
        let sawWild = false;
        for (let p of lastDirty) {
            if (p === nonWildPath) { sawNonWild = true; }
            if (p === wildPath) { sawWild = true; }
        }
        test(`${tag} mixed 2 objects: #3 (async) dirty contains nonWildPath`, eq(sawNonWild, true));
        test(`${tag} mixed 2 objects: #3 (async) dirty contains wildPath`, eq(sawWild, true));
        test(`${tag} mixed 2 objects: #3 (async) m.value(nonWildPath) defined`, eq(lastNonWildDefined, true));
        test(`${tag} mixed 2 objects: #3 (async) m.value(nonWildPath).before === 'new'`, eq(lastNonWildBefore, 'new'));
        test(`${tag} mixed 2 objects: #3 (async) m.value(nonWildPath).now === 'new again'`, eq(lastNonWildNow, 'new again'));
        test(`${tag} mixed 2 objects: #3 (async) m.value(wildPath) === undefined`, eq(lastWildDefined, false));
    }

    // 4) Untracked write on either side fires nothing — captured snapshot
    //    from step 3 is preserved.
    let prevCount = count;
    let prevDirtyLen = lastDirty.length;
    other.a_anyprop_no_meta.propA++;
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`${tag} mixed 2 objects: #4 untracked propA++: count=${count} === ${prevCount}`, eq(count, prevCount));
    test(`${tag} mixed 2 objects: #4 untracked propA++: dirty.length unchanged`, eq(lastDirty.length, prevDirtyLen));
}


// Helper: one makeMonitor call with a non-wildcard path AND a wildcard path
// that both bind __meta_classB on the SAME object. A single mutation to classB
// enqueues both path refs in one fireChange; per-call Set dedup collapses
// them to ONE callback in both modes.
function doMakeMonitorDedupOverlappingPaths(isSync: boolean): void {
    const tag = isSync ? 'sync' : 'async';
    let comp = new ParentComponent(null, {});
    let count: int = 0;
    const onChanged: MonitorCallback = (_m: IMonitor) => {
        stateMgmtConsole.debug(`doMakeMonitorDedupOverlappingPaths fired`);
        count++;
    }

    let _monitor: IMonitorDecoratedVariable = makeMonitorByMode(
        isSync,
        new Array<IMonitorPathInfo>(
            {
                path: 'comp.a_anyprop_no_meta.classB',
                enableWildcard: false,
                valueCallback: () => comp.a_anyprop_no_meta.classB
            } as IMonitorPathInfo,
            {
                path: 'comp.a_anyprop_no_meta.*',
                enableWildcard: true,
                valueCallback: () => comp.a_anyprop_no_meta
            } as IMonitorPathInfo
        ),
        onChanged
    );

    comp.a_anyprop_no_meta.classB = new ClassB_ObserveAnyProp();
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`${tag} dedup overlapping: single classB write: count=${count} === ${isSync ? 1 : 1}`, eq(count, isSync ? 1 : 1));
}


// Helper: single wildcard path rooted at a custom MyArray via
// ComponentWithArray. The value lambda returns the array; the framework calls
// addRefAnyKey() on the ObserveWrappedKeyedMeta and binds every keyed slot.
//
// Element assignments and mutating methods like sort() each fire one keyed
// fireChange. Async drain coalesces N writes between drains into one callback;
// sync fires per fireChange.
function doMakeMonitorWildcardSingleArray(isSync: boolean): void {
    const tag = isSync ? 'sync' : 'async';
    let comp = new ComponentWithArray(null, {});
    let count: int = 0;
    const onChanged: MonitorCallback = (_m: IMonitor) => {
        stateMgmtConsole.debug(`doMakeMonitorWildcardSingleArray fired`);
        count++;
    }

    let _monitor: IMonitorDecoratedVariable = makeMonitorByMode(
        isSync,
        new Array<IMonitorPathInfo>(
            {
                path: 'comp.arr.*',
                enableWildcard: true,
                valueCallback: () => {
                    console.log('lambda for path comp.arr.*');
                    return comp.arr;
                }
            } as IMonitorPathInfo
        ),
        onChanged
    );

    comp.arr[1] = 99;
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`${tag} wildcard single array: arr[1] write: count=${count} === ${isSync ? 1 : 1}`, eq(count, isSync ? 1 : 1));

    comp.arr[2] = 500;
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`${tag} wildcard single array: arr[2] write: count=${count} === ${isSync ? 2 : 2}`, eq(count, isSync ? 2 : 2));

    comp.arr.sort();
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`${tag} wildcard single array: sort: count=${count} === ${isSync ? 3 : 3}`, eq(count, isSync ? 3 : 3));

    // 3 element writes between drains.
    // async: coalesces into 1 callback. sync: 3 separate fireChanges → 3 callbacks.
    comp.arr[0] = 111;
    comp.arr[1] = 222;
    comp.arr[2] = 333;
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`${tag} wildcard single array: triple write: count=${count} === ${isSync ? 6 : 4}`, eq(count, isSync ? 6 : 4));
}


// Helper: one monitor mixing a WILDCARD path on one MyArray and a NON-WILDCARD
// path on a DIFFERENT MyArray's @Trace arrProp. Element writes on the
// non-wildcard array do NOT fire the monitor — its lambda reads only arrProp.
function doMakeMonitorTwoArraysOneWildcardOneNot(isSync: boolean): void {
    const tag = isSync ? 'sync' : 'async';
    let compWild = new ComponentWithArray(null, {});
    let compNoWild = new ComponentWithArray(null, {});
    let count: int = 0;
    const onChanged: MonitorCallback = (_m: IMonitor) => {
        stateMgmtConsole.debug(`doMakeMonitorTwoArraysOneWildcardOneNot fired`);
        count++;
    }

    let _monitor: IMonitorDecoratedVariable = makeMonitorByMode(
        isSync,
        new Array<IMonitorPathInfo>(
            {
                path: 'compWild.arr.*',
                enableWildcard: true,
                valueCallback: () => compWild.arr
            } as IMonitorPathInfo,
            {
                path: 'compNoWild.arr.arrProp',
                enableWildcard: false,
                valueCallback: () => compNoWild.arr.arrProp
            } as IMonitorPathInfo
        ),
        onChanged
    );

    compWild.arr[0] = 99;
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`${tag} two arrays mixed: wildcard arr[0] write: count=${count} === ${isSync ? 1 : 1}`, eq(count, isSync ? 1 : 1));

    compNoWild.arr.arrProp = 'new';
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`${tag} two arrays mixed: arrProp write: count=${count} === ${isSync ? 2 : 2}`, eq(count, isSync ? 2 : 2));

    // Element write on the non-wildcard array binds to the keyed meta only —
    // this monitor's non-wildcard path binds __meta_arrProp, not the keyed meta.
    compNoWild.arr[0] = 77;
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`${tag} two arrays mixed: compNoWild element write (no fire): count=${count} === ${isSync ? 2 : 2}`, eq(count, isSync ? 2 : 2));

    // Two separate fireChanges before the next drain.
    // async: coalesced to 1 callback. sync: 2 callbacks.
    compWild.arr.sort();
    compNoWild.arr.arrProp = 'new again';
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`${tag} two arrays mixed: simultaneous fires: count=${count} === ${isSync ? 4 : 3}`, eq(count, isSync ? 4 : 3));
}


// Helper: one monitor with two WILDCARD paths, one rooted at a MyArray (binds
// every keyed slot via addRefAnyKey) and the other at an IObserveAnyProp
// object (binds every @Track meta via addRefAnyProp). Verifies the
// decoratorMonitor wildcard branch dispatches to the right routine for each
// path type.
function doMakeMonitorArrayAndClassBothWildcards(isSync: boolean): void {
    const tag = isSync ? 'sync' : 'async';
    let compArr = new ComponentWithArray(null, {});
    let compObj = new ParentComponent(null, {});
    let count: int = 0;
    const onChanged: MonitorCallback = (_m: IMonitor) => {
        stateMgmtConsole.debug(`doMakeMonitorArrayAndClassBothWildcards fired`);
        count++;
    }

    let _monitor: IMonitorDecoratedVariable = makeMonitorByMode(
        isSync,
        new Array<IMonitorPathInfo>(
            {
                path: 'compArr.arr.*',
                enableWildcard: true,
                valueCallback: () => compArr.arr
            } as IMonitorPathInfo,
            {
                path: 'compObj.a_anyprop_no_meta.*',
                enableWildcard: true,
                valueCallback: () => compObj.a_anyprop_no_meta
            } as IMonitorPathInfo
        ),
        onChanged
    );

    compArr.arr[0] = 99;
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`${tag} array + class: array element write: count=${count} === ${isSync ? 1 : 1}`, eq(count, isSync ? 1 : 1));

    compObj.a_anyprop_no_meta.classB = new ClassB_ObserveAnyProp();
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`${tag} array + class: classB write: count=${count} === ${isSync ? 2 : 2}`, eq(count, isSync ? 2 : 2));

    // Two separate fireChanges before the next drain.
    // async: coalesced to 1 callback. sync: 2 callbacks.
    compArr.arr.sort();
    compObj.a_anyprop_no_meta.classC = new ClassC();
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`${tag} array + class: simultaneous fires: count=${count} === ${isSync ? 4 : 3}`, eq(count, isSync ? 4 : 3));

    // Untracked propA++ on the IObserveAnyProp side fires nothing —
    // addRefAnyProp binds only @Track metas.
    compObj.a_anyprop_no_meta.propA++;
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`${tag} array + class: untracked propA++: count=${count} === ${isSync ? 4 : 3}`, eq(count, isSync ? 4 : 3));
}


// --- Suite drivers ---------------------------------------------------------

function runWildcardSuite(isSync: boolean): void {
    const factoryName = isSync ? 'makeSyncMonitor' : 'makeMonitor';

    tcase(`### ${factoryName} wildcard single path, IObserveAnyProp object`) {
        doMakeMonitorWildcardSinglePath(isSync);
    }

    tcase(`### ${factoryName} wildcard single path, IObserveAnyProp object, keep LSV`) {
        doMakeMonitorWildcardSinglePathKeepLSV(isSync);
    }

    tcase(`### ${factoryName} wildcard: IMonitor.dirty and IMonitor.value API`) {
        doMakeMonitorWildcardVerifyIMonitorAPI(isSync);
    }

    tcase(`### ${factoryName} path '.*' with enableWildcard: false (no auto-bind)`) {
        doMakeMonitorWildcardFlagFalse(isSync);
    }

    tcase(`### ${factoryName} wildcards on two components in one monitor`) {
        doMakeMonitorWildcardTwoComponents(isSync);
    }

    tcase(`### ${factoryName} mixed wildcard + non-wildcard, same object`) {
        doMakeMonitorMixedWildAndNonWild(isSync);
    }

    tcase(`### ${factoryName} mixed wildcard + non-wildcard, different objects`) {
        doMakeMonitorMixedWildAndNonWildDifferentObjects(isSync);
    }

    tcase(`### ${factoryName} dedup across overlapping wildcard + non-wildcard paths`) {
        doMakeMonitorDedupOverlappingPaths(isSync);
    }

    tcase(`### ${factoryName} single wildcard on array`) {
        doMakeMonitorWildcardSingleArray(isSync);
    }

    tcase(`### ${factoryName} two arrays, one wildcard and one non-wildcard`) {
        doMakeMonitorTwoArraysOneWildcardOneNot(isSync);
    }

    tcase(`### ${factoryName} array + class object, both wildcards`) {
        doMakeMonitorArrayAndClassBothWildcards(isSync);
    }
}


export function run_monitor_wildcard(): boolean {
    const ttest = tsuite('@Monitor with wildcards') {
        runWildcardSuite(/* isSync */ false);
    }
    ttest();
    return true;
}


export function run_syncmonitor_wildcard(): boolean {
    const ttest = tsuite('@SyncMonitor with wildcards') {
        runWildcardSuite(/* isSync */ true);
    }
    ttest();
    return true;
}

