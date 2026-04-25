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
import { ILocalDecoratedVariable }  from '../decorator'
import { IMonitor, IMonitorPathInfo, IMonitorDecoratedVariable, MonitorCallback } from '../decorator'
import { ExtendableComponent } from '../mock/extendableComponent';

import { ClassAWithAnyMeta, ClassA_ObserveAnyProp_NoAnyMeta, ClassB, ClassC, ClassA } from './uipluginObservedObject3'
import { MyArray } from './uiplugin_custom_arrays'
import { ObserveSingleton } from '../base/observeSingleton';
import { STATE_MGMT_FACTORY } from '../decorator'
import { uiUtils } from '../base/uiUtilsImpl';
import { UIUtils, MonitorOptions, IMonitorValueInfo } from '../utils';
import { TestMSM, TestMutableKeyedStateMeta } from './lib/testAddRefFireChange'

let StateMgmtFactory = STATE_MGMT_FACTORY;
let stateMgmtConsole=console;

/*
    @Observed class ClassA  {
        propA : number;
        @Track classB : ClassB;

        // init with declaration
        @Track classC : ClassC = new ClassC;

        constructor() {
            // init in constructor
            this.classB = new ClassB();
            this.propA = 8;
        }
    }

    // @Observe compat mode, no @Track
    @Observe class ClassB {
        propB1 : string = "BBB111";
        propB2 : boolean = false;
    }

    // untracked
    class ClassC  {
        propC : number = 888;
    }
*/


// UI plugin generate
export interface ParentComponent_init_update_struct {
    // @Local nothing, @Local can not init from parent @Component/V2
}

export class ParentComponent extends ExtendableComponent {
    // @Local a: ClassA = new ClassAWithAnyMeta();
    private _backing_a: ILocalDecoratedVariable<ClassAWithAnyMeta>;
    // __meta_any_property - NO, IObserveAnyProp - NO
    private _backing_a_no_any: ILocalDecoratedVariable<ClassA>;
    // __meta_any_property - NO, IObserveAnyProp - YES
    private _backing_a_anyprop_no_meta: ILocalDecoratedVariable<ClassA_ObserveAnyProp_NoAnyMeta>;

    get a(): ClassAWithAnyMeta {
        return this._backing_a.get();
    }
    set a(newValue: ClassAWithAnyMeta) {
        this._backing_a.set(newValue);
    }

    get a_no_any(): ClassA {
        return this._backing_a_no_any.get();
    }
    set a_no_any(newValue: ClassA) {
        this._backing_a_no_any.set(newValue);
    }

    get a_anyprop_no_meta(): ClassA_ObserveAnyProp_NoAnyMeta {
        console.log('Parent - get a_anyprop_no_meta():');
        return this._backing_a_anyprop_no_meta.get();
    }
    set a_anyprop_no_meta(newValue: ClassA_ObserveAnyProp_NoAnyMeta) {
        this._backing_a_anyprop_no_meta.set(newValue);
    }

    public monitorFunctionRunCount: number = 0;

    // @Monitor("b.obj.propA") onAChanged(m: IMonitor)
    //private _monitor: IMonitorDecoratedVariable;
    public onAChanged?: (m: IMonitor) => void;

    constructor(parent: ExtendableComponent | null, param: ParentComponent_init_update_struct) {
        super(parent)
        // @Local optional to init from parent
        // must check if defined, the following is WRONG
        // because can not differentiate btw undefiend value 
        // and param.localA not defined
        this._backing_a = STATE_MGMT_FACTORY.makeLocal<ClassAWithAnyMeta>(
            this,
            'a',
            /* local init value */ new ClassAWithAnyMeta());

        this._backing_a_no_any = STATE_MGMT_FACTORY.makeLocal<ClassA>(
            this,
            'a_no_any',
            /* local init value */ new ClassA());

        this._backing_a_anyprop_no_meta = STATE_MGMT_FACTORY.makeLocal<ClassA_ObserveAnyProp_NoAnyMeta>(
            this,
            'a_anyprop_no_meta',
            /* local init value */ new ClassA_ObserveAnyProp_NoAnyMeta());

    }
}

// UI plugin generates
export interface ComponentWithArray_init_update_struct {
    arr?: MyArray<number>;
}

export class ComponentWithArray extends ExtendableComponent {
    private _backing_state_arr: ILocalDecoratedVariable<MyArray<number>>;
    get arr(): MyArray<number> {
        return this._backing_state_arr!.get() as MyArray<number>;
    }
    set arr(newArr: MyArray<number>) {
        this._backing_state_arr!.set(newArr);
    }

    // For testing
    public getFireChangeCnt(key:string): Int {
        // meta_ not visible
        return (this._backing_state_arr.get().meta_ instanceof TestMutableKeyedStateMeta)
            ? (this._backing_state_arr.get().meta_ as TestMutableKeyedStateMeta).getFireChangeCnt(key) : 0
    }
    public getRefCnt(key:string) {
        // meta_ not visible
        return TestMSM.getRefCnt(this._backing_state_arr.get().meta_, key);
    }

    constructor(parent: ExtendableComponent | null, param: ComponentWithArray_init_update_struct) {
        super(parent);

        this._backing_state_arr = StateMgmtFactory.makeLocal<MyArray<number>>(
            this,
            'arr',
            (param.arr !== undefined)
                ? param.arr!
                : new MyArray<number>(1,2,3)
        );
    }
}

class NonObservedClass {
    prop1: string = 'p1';
    prop2: string = 'p2';
}

// Minimal subclass of ParentComponent that lets the test toggle view activity.
// Used by doAddMonitorFrozenDelaysUntilUnfreeze to force MonitorFunctionDecorator.isFreeze()
// to return true; MonitorFunctionDecorator.isFreeze() consults
// owningComponent_.__isViewActive__Internal() (decoratorMonitor.ts:61-63).
class FreezableParentComponent extends ParentComponent {
    private viewActive_: boolean = true;
    constructor(parent: ExtendableComponent | null, param: ParentComponent_init_update_struct) {
        super(parent, param);
    }
    public setViewActive(active: boolean): void {
        this.viewActive_ = active;
    }
    public override __isViewActive__Internal(): boolean {
        return this.viewActive_;
    }
}

interface NonObservedInterface {
    prop1: string;
    prop2: string;
}

// Helper: addMonitor with single non-wildcard path on @ObserveAnyProp object
function doAddMonitorOnePathNoWild(sync: boolean): void {
    const tag: string = sync ? 'SYNC' : 'ASYNC';
    let monitorCallCount: int = 0;
    console.log('TestCase [' + tag + '] -> new ParentComponent');
    let comp = new ParentComponent(null, {});

    let valueCallback = () => {
        console.log('[' + tag + '] valueCallback for comp.a_anyprop_no_meta.classB.propB1');
        return comp.a_anyprop_no_meta.classB.propB1;
    }
    let options: MonitorOptions = {
        isSynchronous: sync,
        owner: comp,
    } as MonitorOptions;
    let monitorFunction: MonitorCallback = (m: IMonitor) => {
        monitorCallCount++;
        console.log('[' + tag + '] Monitor triggered');
    };

    UIUtils.addMonitor(
        {callback: valueCallback, path: 'comp.a_anyprop_no_meta.classB.propB1'} as IMonitorValueInfo,
        monitorFunction,
        options);
    comp.a_anyprop_no_meta.classB.propB1 = 'new';
    test('[' + tag + '] monitorCallCount before UpdateDirty', eq(monitorCallCount, sync ? 1 : 0))
    ObserveSingleton.instance.updateDirty();
    test('[' + tag + '] monitorCallCount', eq(monitorCallCount, 1))
}

// Helper: addMonitor with wildcard path on a custom Array
function doAddMonitorWildcardArray(sync: boolean): void {
    const tag: string = sync ? 'SYNC' : 'ASYNC';
    let monitorCallCount: int = 0;
    console.log('TestCase [' + tag + '] -> new ComponentWithArray');
    let arrayComp = new ComponentWithArray(null, {});

    let valueCallbackWildcard = () => {
        console.log('[' + tag + '] valueCallback comp.arr');
        return arrayComp.arr;
    }
    let options: MonitorOptions = {
        isSynchronous: sync,
        owner: arrayComp,
    } as MonitorOptions;

    let monitorFunction: MonitorCallback = (m: IMonitor) => {
        monitorCallCount++;
        console.log('[' + tag + '] Monitor WILD triggered');
    };

    UIUtils.addMonitor(
        {callback: valueCallbackWildcard, path: 'comp.arr.*', observeProps: true} as IMonitorValueInfo,
        monitorFunction,
        options);

    arrayComp.arr[1] = 1;
    ObserveSingleton.instance.updateDirty();
    test('[' + tag + '] monitorCallCount == 1', eq(monitorCallCount, 1))

    arrayComp.arr[1] = 500;
    ObserveSingleton.instance.updateDirty();
    test('[' + tag + '] monitorCallCount == 2', eq(monitorCallCount, 2))

    arrayComp.arr.sort()
    ObserveSingleton.instance.updateDirty();
    test('[' + tag + '] monitorCallCount == 3', eq(monitorCallCount, 3))
}

// Helper: addMonitor with wildcard path on an IObserveAnyProp-implementing object.
// comp.a_anyprop_no_meta is a ClassA_ObserveAnyProp_NoAnyMeta whose
// addRefAnyProp() registers refs on every @Track meta, so the framework's
// wildcard auto-bind branch (decoratorMonitor.recordDependenciesForMonitorValue)
// can wire up dependencies from the parent reference alone.
function doAddMonitorWildcardObservedObject(sync: boolean): void {
    const tag: string = sync ? 'SYNC' : 'ASYNC';
    let monitorCallCount: int = 0;
    console.log('TestCase [' + tag + '] -> new ParentComponent');
    let comp = new ParentComponent(null, {});

    // Compiler generated function for the wildcard path. Returns the last
    // "sure" reference before the wildcard (comp.a_anyprop_no_meta); the
    // framework binds all of its tracked properties via addRefAnyProp().
    let valueCallback_comp_A_Wildcard = () => {
        console.log('[' + tag + '] valueCallback for comp.a_anyprop_no_meta.*');
        return comp.a_anyprop_no_meta;
    }

    let options: MonitorOptions = {
        isSynchronous: sync,
        owner: comp,
    } as MonitorOptions;

    let monitorFunction: MonitorCallback = (m: IMonitor) => {
        monitorCallCount++;
        console.log('[' + tag + '] Monitor triggered comp.a_anyprop_no_meta.* ' + JSON.stringify(m));
        console.log('[' + tag + '] Monitor triggered comp.a_anyprop_no_meta.* ' + JSON.stringify(m.dirty));
    };

    UIUtils.addMonitor(
        {callback: valueCallback_comp_A_Wildcard, path: 'comp.a_anyprop_no_meta.*', observeProps: true} as IMonitorValueInfo,
        monitorFunction,
        options);

    comp.a_anyprop_no_meta.classB = new ClassB();
    ObserveSingleton.instance.updateDirty();
    test('[' + tag + '] monitorCallCount 1', eq(monitorCallCount, 1))

    comp.a_anyprop_no_meta.classC = new ClassC();
    ObserveSingleton.instance.updateDirty();
    test('[' + tag + '] monitorCallCount 2', eq(monitorCallCount, 2))

    comp.a_anyprop_no_meta.propA++;
    ObserveSingleton.instance.updateDirty();
    test('[' + tag + '] monitorCallCount 2 after propA++', eq(monitorCallCount, 2))
}

// Helper: single addMonitor call with an Array<IMonitorValueInfo> that mixes
// a non-wildcard path and a wildcard path. Verifies that one MonitorFunction
// reacts to mutations on either path and ignores writes to non-tracked members.
//
// This helper deliberately omits intermediate updateDirty() calls to highlight
// the difference between sync and async dispatch:
//   * SYNC : every tracked mutation fires the monitor immediately
//            → expected count after 3 tracked mutations = 3
//   * ASYNC: mutations only mark values dirty; the trailing updateDirty()
//            coalesces all dirty paths into a SINGLE callback invocation
//            (see MonitorFunctionDecorator.runMonitorFunction)
//            → expected count after 3 tracked mutations + 1 updateDirty() = 1
function doAddMonitorMixedWildAndNonWild(sync: boolean): void {
    const tag: string = sync ? 'SYNC' : 'ASYNC';
    let monitorCallCount: int = 0;
    console.log('TestCase [' + tag + '] -> new ParentComponent');
    let comp = new ParentComponent(null, {});

    // Non-wildcard value info: a single concrete property reachable via the
    // @ObserveAnyProp object. Note: both this path and the wildcard below
    // are rooted at the SAME object (comp.a_anyprop_no_meta), but bound to
    // different metas — see expected counts below.
    let valueCallbackPropB1 = () => {
        console.log('[' + tag + '] valueCallback for comp.a_anyprop_no_meta.classB.propB1');
        return comp.a_anyprop_no_meta.classB.propB1;
    }

    // Wildcard value info: returns the last "sure" reference before the
    // wildcard (comp.a_anyprop_no_meta); the framework binds all of its
    // tracked properties via addRefAnyProp().
    let valueCallbackAStar = () => {
        console.log('[' + tag + '] valueCallback for comp.a_anyprop_no_meta.*');
        return comp.a_anyprop_no_meta;
    }

    let options: MonitorOptions = {
        isSynchronous: sync,
        owner: comp,
    } as MonitorOptions;

    let monitorFunction: MonitorCallback = (m: IMonitor) => {
        monitorCallCount++;
        console.log('[' + tag + '] Monitor MIXED triggered, dirty: ' + JSON.stringify(m.dirty));
    };

    UIUtils.addMonitor(
        new Array<IMonitorValueInfo>(
            {callback: valueCallbackPropB1, path: 'comp.a_anyprop_no_meta.classB.propB1'} as IMonitorValueInfo,
            {callback: valueCallbackAStar, path: 'comp.a_anyprop_no_meta.*', observeProps: true} as IMonitorValueInfo
        ),
        monitorFunction,
        options);

    // 1) Mutate the non-wildcard path. propB1 lives on ClassB, not on the
    //    @ObserveAnyProp object, so the wildcard path is NOT bound to it
    //    and only the non-wildcard path fires. SYNC: count -> 1, ASYNC: still 0.
    comp.a_anyprop_no_meta.classB.propB1 = 'new';
    test('[' + tag + '] mixed: count after non-wildcard write',
        eq(monitorCallCount, sync ? 1 : 0))

    // 2) Mutate a @Track property covered ONLY by the wildcard. Note we
    //    intentionally mutate classC and not classB here: the non-wildcard
    //    callback also reads classB on the way to propB1, so reassigning
    //    classB would dirty BOTH paths and fire the monitor twice in sync
    //    mode. classC is bound exclusively by addRefAnyProp(), so the
    //    wildcard path is the only dependent. SYNC: count -> 2, ASYNC: still 0.
    comp.a_anyprop_no_meta.classC = new ClassC();
    test('[' + tag + '] mixed: count after wildcard classC write (1st)',
        eq(monitorCallCount, sync ? 2 : 0))

    // 3) Reassign classC again - again only the wildcard fires.
    //    SYNC: count -> 3, ASYNC: still 0.
    comp.a_anyprop_no_meta.classC = new ClassC();
    test('[' + tag + '] mixed: count after wildcard classC write (2nd)',
        eq(monitorCallCount, sync ? 3 : 0))

    // 4) Mutate a non-tracked property - must NOT fire either path in either mode.
    comp.a_anyprop_no_meta.propA++;
    test('[' + tag + '] mixed: count unchanged after non-tracked propA++',
        eq(monitorCallCount, sync ? 3 : 0))

    // 5) Flush deferred work. SYNC: nothing to do, count stays 3.
    //    ASYNC: runMonitorFunction fires the callback exactly once for the
    //    accumulated dirty set, so count becomes 1.
    ObserveSingleton.instance.updateDirty();
    test('[' + tag + '] mixed: count after UpdateDirty',
        eq(monitorCallCount, sync ? 3 : 1))
}

// Helper: single addMonitor call with an Array<IMonitorValueInfo> that mixes
// a non-wildcard path and a wildcard path rooted at TWO DIFFERENT objects
// (separate component instances). One MonitorFunction must react to mutations
// on either object.
function doAddMonitorMixedWildAndNonWildDifferentObjects(sync: boolean): void {
    const tag: string = sync ? 'SYNC' : 'ASYNC';
    let monitorCallCount: int = 0;
    console.log('TestCase [' + tag + '] -> new ParentComponent + new ComponentWithArray');
    let comp = new ParentComponent(null, {});
    let arrayComp = new ComponentWithArray(null, {});

    // Non-wildcard value info rooted at `comp` (ParentComponent).
    let valueCallbackPropB1 = () => {
        console.log('[' + tag + '] valueCallback for comp.a_anyprop_no_meta.classB.propB1');
        return comp.a_anyprop_no_meta.classB.propB1;
    }

    // Wildcard value info rooted at `arrayComp` (a different component instance).
    let valueCallbackArrStar = () => {
        console.log('[' + tag + '] valueCallback for arrayComp.arr.*');
        return arrayComp.arr;
    }

    let options: MonitorOptions = {
        isSynchronous: sync,
        owner: comp,
    } as MonitorOptions;

    let monitorFunction: MonitorCallback = (m: IMonitor) => {
        monitorCallCount++;
        console.log('[' + tag + '] Monitor MIXED-OBJECTS triggered, dirty: ' + JSON.stringify(m.dirty));
    };

    UIUtils.addMonitor(
        new Array<IMonitorValueInfo>(
            {callback: valueCallbackPropB1, path: 'comp.a_anyprop_no_meta.classB.propB1'} as IMonitorValueInfo,
            {callback: valueCallbackArrStar, path: 'arrayComp.arr.*', observeProps: true} as IMonitorValueInfo
        ),
        monitorFunction,
        options);

    // 1) Mutate the non-wildcard path on `comp`
    comp.a_anyprop_no_meta.classB.propB1 = 'new';
    test('[' + tag + '] mixed-objects: count after non-wildcard write before UpdateDirty',
        eq(monitorCallCount, sync ? 1 : 0))
    ObserveSingleton.instance.updateDirty();
    test('[' + tag + '] mixed-objects: count == 1 after non-wildcard write',
        eq(monitorCallCount, 1))

    // 2) Mutate an array element on `arrayComp` (covered by the wildcard)
    arrayComp.arr[1] = 1;
    ObserveSingleton.instance.updateDirty();
    test('[' + tag + '] mixed-objects: count == 2 after wildcard arr[1] write',
        eq(monitorCallCount, 2))

    // 3) Sort the array on `arrayComp` (mutating method, also covered by the wildcard)
    arrayComp.arr.sort()
    ObserveSingleton.instance.updateDirty();
    test('[' + tag + '] mixed-objects: count == 3 after wildcard arr.sort()',
        eq(monitorCallCount, 3))
}

// Helper: one addMonitor call that registers a non-wildcard path AND a wildcard
// path ROOTED AT THE SAME OBJECT, where a SINGLE mutation dirties both paths.
//
// Both paths ultimately bind to `comp.a_anyprop_no_meta.__meta_classB`:
//   * the non-wildcard path reads comp.a_anyprop_no_meta.classB, whose getter
//     calls conditionalAddRef method with __meta_classB
//   * the wildcard path reads comp.a_anyprop_no_meta and then the framework
//     calls addRefAnyProp() which also binds __meta_classB (and __meta_classC).
// Assigning comp.a_anyprop_no_meta.classB fires __meta_classB, which enqueues
// BOTH monitor value refs into syncMonitorPathRefsChanged_. The current upstream
// drain (notifyDirtyMonitorPaths) deduplicates on MonitorFunctionDecorator identity,
// so the user-supplied callback must fire EXACTLY ONCE per fireChange cycle, not
// once per dirty path ref.
//
// In the previous addmon implementation (processSyncMonitors, dropped during the
// rebase), the same scenario would fire the callback TWICE — once for each ref
// in the iteration — because it called notifyChangesForPath + runMonitorFunction
// inline per ref with no cross-ref dedup.
//
// This is the regression-guard test for scenario #1 in tests/notes.md.
//
// Pre-rebase (dropped processSyncMonitors) behavior:
//   * SYNC  : FAILS. processSyncMonitors forEach visits both refs. Non-wildcard
//             ref → notifyChangesForPath sets dirty via (before !== now) → callback
//             fires → count=1 → values_ reset. Wildcard ref → notifyChangesForPath
//             sets dirty unconditionally (MonitorValueInternal.readValue() always
//             returns `isWildcard || before !== now`, decoratorMonitor.ts:220) →
//             callback fires again → count=2. Assertion `count==1` fails (actual 2).
//   * ASYNC : PASSES. Async drain uses notifyDirtyMonitorPaths which already
//             deduplicates via Set<MonitorFunctionDecorator>; addmon did not touch
//             that path, so both pre- and post-rebase give count=1.
function doAddMonitorDedupOverlappingPaths(sync: boolean): void {
    const tag: string = sync ? 'SYNC' : 'ASYNC';
    let monitorCallCount: int = 0;
    console.log('TestCase [' + tag + '] -> new ParentComponent');
    let comp = new ParentComponent(null, {});

    // Non-wildcard path: reads comp.a_anyprop_no_meta.classB → binds __meta_classB.
    let valueCallbackClassB = () => {
        console.log('[' + tag + '] valueCallback for comp.a_anyprop_no_meta.classB');
        return comp.a_anyprop_no_meta.classB;
    }
    // Wildcard path: reads comp.a_anyprop_no_meta → framework calls
    // addRefAnyProp() which binds both __meta_classB and __meta_classC.
    let valueCallbackStar = () => {
        console.log('[' + tag + '] valueCallback for comp.a_anyprop_no_meta.*');
        return comp.a_anyprop_no_meta;
    }

    let options: MonitorOptions = {
        isSynchronous: sync,
        owner: comp,
    } as MonitorOptions;

    let monitorFunction: MonitorCallback = (m: IMonitor) => {
        monitorCallCount++;
        console.log('[' + tag + '] Monitor DEDUP triggered, dirty: ' + JSON.stringify(m.dirty));
    };

    UIUtils.addMonitor(
        new Array<IMonitorValueInfo>(
            {callback: valueCallbackClassB, path: 'comp.a_anyprop_no_meta.classB'} as IMonitorValueInfo,
            {callback: valueCallbackStar,   path: 'comp.a_anyprop_no_meta.*', observeProps: true} as IMonitorValueInfo
        ),
        monitorFunction,
        options);

    // Single mutation that dirties BOTH registered paths via __meta_classB.
    // Upstream behavior: dedup to ONE callback invocation per fireChange cycle.
    comp.a_anyprop_no_meta.classB = new ClassB();
    test('[' + tag + '] dedup: one callback after SYNC fireChange, zero before updateDirty otherwise',
        eq(monitorCallCount, sync ? 1 : 0))

    // updateDirty() does not double-count in either mode (sync already drained the
    // queue; async drain uses the same Set-based dedup in notifyDirtyMonitorPaths).
    ObserveSingleton.instance.updateDirty();
    test('[' + tag + '] dedup: count == 1 after updateDirty (no double-fire)',
        eq(monitorCallCount, 1))
}

// Helper: two sync monitors on two DIFFERENT component instances. Monitor A's
// callback mutates state watched by Monitor B, triggering a nested fireChange
// from inside the outer sync drain.
//
// This verifies that updateDirtySyncMonitorPaths' "swap-before-drain" pattern
// (observeSingleton.ts:148-149) correctly isolates the nested drain: the inner
// fireChange queues into the already-swapped (fresh) syncMonitorPathRefsChanged_
// set, the nested updateDirtySyncMonitorPaths swaps again and drains B, then
// control returns to the outer drain with no lingering refs.
//
// Regression guard for scenario #2 in tests/notes.md. In the dropped addmon
// implementation, the inner fireChange would add a ref to the same set that
// processSyncMonitors was currently iterating, so order and completeness
// depended on JS Set iteration semantics under mid-loop mutation.
//
// Two separate component instances are used so neither monitor's path aliases
// the other; each monitor observes exactly one classB meta on its own component.
//
// Pre-rebase (dropped processSyncMonitors) behavior:
//   * SYNC  : PASSES ACCIDENTALLY. Outer processSyncMonitors forEach visits A_ref,
//             runs A's callback, which mutates compB.classB. That nested fireChange
//             calls processSyncMonitors AGAIN on the still-not-cleared outer set
//             (which now holds {A_ref, B_ref}). The nested forEach re-visits A_ref
//             but A's values_ were just reset by the outer runMonitorFunction, so
//             notifyChangesForPath finds `before === now` and runMonitorFunction
//             short-circuits via `some(v => v.dirty)`. Then visits B_ref → fires B
//             → countB=1. Nested .clear() wipes the set. Outer forEach has nothing
//             left. Final countA=1 countB=1 — same observable counts as upstream,
//             but achieved via set-mutation-during-iteration plus the reset/re-read
//             short-circuit. Fragile: any ordering or freeze change can break it.
//   * ASYNC : PASSES. Async drain uses updateDirty's do-while loop which was
//             unchanged by addmon, so the cascade completes identically on both
//             implementations.
function doAddMonitorSyncMonitorCascade(sync: boolean): void {
    const tag: string = sync ? 'SYNC' : 'ASYNC';
    let countA: int = 0;
    let countB: int = 0;
    console.log('TestCase [' + tag + '] -> new compA + new compB');
    let compA = new ParentComponent(null, {});
    let compB = new ParentComponent(null, {});

    // Monitor A: watches compA.a_anyprop_no_meta.classB and on fire reassigns
    // compB.a_anyprop_no_meta.classB to trigger monitor B.
    let valueCallbackA = () => {
        console.log('[' + tag + '] valueCallback A for compA.a_anyprop_no_meta.classB');
        return compA.a_anyprop_no_meta.classB;
    }
    let monitorFunctionA: MonitorCallback = (_m: IMonitor) => {
        countA++;
        console.log('[' + tag + '] Monitor A fired (countA=' + countA + '); mutating compB to cascade');
        compB.a_anyprop_no_meta.classB = new ClassB();
    };
    UIUtils.addMonitor(
        {callback: valueCallbackA, path: 'compA.a_anyprop_no_meta.classB'} as IMonitorValueInfo,
        monitorFunctionA,
        { isSynchronous: sync, owner: compA } as MonitorOptions);

    // Monitor B: watches compB.a_anyprop_no_meta.classB and just counts.
    let valueCallbackB = () => {
        console.log('[' + tag + '] valueCallback B for compB.a_anyprop_no_meta.classB');
        return compB.a_anyprop_no_meta.classB;
    }
    let monitorFunctionB: MonitorCallback = (_m: IMonitor) => {
        countB++;
        console.log('[' + tag + '] Monitor B fired (countB=' + countB + ')');
    };
    UIUtils.addMonitor(
        {callback: valueCallbackB, path: 'compB.a_anyprop_no_meta.classB'} as IMonitorValueInfo,
        monitorFunctionB,
        { isSynchronous: sync, owner: compB } as MonitorOptions);

    // Trigger the cascade: assigning compA.classB fires A, whose callback
    // assigns compB.classB, which must fire B before control returns.
    compA.a_anyprop_no_meta.classB = new ClassB();

    // SYNC: both monitors have already fired by now because the outer fireChange
    //       drains A synchronously, A's callback triggers an inner drain for B.
    // ASYNC: mutations only queue dirty refs; neither monitor has fired yet.
    test('[' + tag + '] cascade: countA before updateDirty',
        eq(countA, sync ? 1 : 0))
    test('[' + tag + '] cascade: countB before updateDirty',
        eq(countB, sync ? 1 : 0))

    // In ASYNC mode, updateDirty's do-while loop (observeSingleton.ts:195-200)
    // drains A first, A's callback mutates compB, the loop re-enters and drains B.
    ObserveSingleton.instance.updateDirty();
    test('[' + tag + '] cascade: countA == 1 after updateDirty', eq(countA, 1))
    test('[' + tag + '] cascade: countB == 1 after updateDirty', eq(countB, 1))
}

// Helper: sync monitor on a component that is frozen BEFORE the mutation. The
// current upstream drain honors isFreeze() in notifyDirtyMonitorPaths (line 225
// of observeSingleton.ts) and parks the path ref in monitorPathRefsDelayed_
// instead of firing the callback. After unFreezeDelayedMonitorPaths() the refs
// are moved to the async monitorPathRefsChanged_ queue and drained by updateDirty.
//
// The dropped addmon processSyncMonitors had no freeze branch, so it would fire
// the callback regardless of component activity. Regression guard for scenario #4
// in tests/notes.md.
//
// A minimal subclass of ParentComponent overrides __isViewActive__Internal so
// MonitorFunctionDecorator.isFreeze() (decoratorMonitor.ts:61-63) returns true
// while the component is marked inactive.
//
// Pre-rebase (dropped processSyncMonitors) behavior:
//   * SYNC  : FAILS. processSyncMonitors has no isFreeze() branch, so the
//             callback fires immediately on the frozen component. The first
//             assertion `count==0 right after mutation` fails (actual 1).
//             The subsequent `count==0 after updateDirty while frozen` also
//             fails for the same reason. The final "count==1 after unfreeze"
//             assertion happens to match (count is already 1), but the delay
//             semantics were never exercised.
//   * ASYNC : PASSES. Async drain goes through notifyDirtyMonitorPaths which
//             has always honored isFreeze() (observeSingleton.ts:225) in both
//             implementations, so the ref is parked in monitorPathRefsDelayed_
//             and only released by unFreezeDelayedMonitorPaths + updateDirty.
function doAddMonitorFrozenDelaysUntilUnfreeze(sync: boolean): void {
    const tag: string = sync ? 'SYNC' : 'ASYNC';
    let monitorCallCount: int = 0;
    console.log('TestCase [' + tag + '] -> new FreezableParentComponent');
    let comp = new FreezableParentComponent(null, {});

    let valueCallback = () => {
        console.log('[' + tag + '] valueCallback for comp.a_anyprop_no_meta.classB');
        return comp.a_anyprop_no_meta.classB;
    }
    let monitorFunction: MonitorCallback = (_m: IMonitor) => {
        monitorCallCount++;
        console.log('[' + tag + '] Monitor FROZEN fired (count=' + monitorCallCount + ')');
    };

    UIUtils.addMonitor(
        {callback: valueCallback, path: 'comp.a_anyprop_no_meta.classB'} as IMonitorValueInfo,
        monitorFunction,
        { isSynchronous: sync, owner: comp } as MonitorOptions);

    // Freeze the component BEFORE mutating, so notifyDirtyMonitorPaths' isFreeze()
    // check routes the ref to monitorPathRefsDelayed_.
    comp.setViewActive(false);

    console.log('TestCase [' + tag + '] (frozen) update comp.a_anyprop_no_meta.classB = new ClassB()');
    comp.a_anyprop_no_meta.classB = new ClassB();
    test('[' + tag + '] frozen: monitor did NOT fire synchronously',
        eq(monitorCallCount, 0))

    // Flushing the async queue while frozen also must NOT fire the callback;
    // notifyDirtyMonitorPaths is used by the async drain too and re-checks
    // isFreeze() (same code path).
    ObserveSingleton.instance.updateDirty();
    test('[' + tag + '] frozen: updateDirty while frozen leaves count at 0',
        eq(monitorCallCount, 0))

    // Unfreeze and release the delayed refs. unFreezeDelayedMonitorPaths moves
    // them to monitorPathRefsChanged_ (the async queue). A subsequent updateDirty
    // drains them and fires the callback EXACTLY ONCE.
    comp.setViewActive(true);
    ObserveSingleton.instance.unFreezeDelayedMonitorPaths();
    ObserveSingleton.instance.updateDirty();
    test('[' + tag + '] frozen: callback fires once after unfreeze + updateDirty',
        eq(monitorCallCount, 1))
}

export function run_addmonitor(): boolean {

    const ttest = tsuite('@AddMonitor with wildcards') {

    // Single non-wildcard path on an @ObserveAnyProp object.
    // Synchronous mode: monitor callback fires immediately on property assignment,
    // before updateDirty() is called. monitorCallCount must be 1 right after the
    // assignment and remain 1 after updateDirty().
    tcase('### addMonitor IMonitorValueInfo, comp.a_anyprop_no_meta.classB.propB1, SYNC') {
        doAddMonitorOnePathNoWild(true);
    }

    // Same scenario as the SYNC variant above, but asynchronous.
    // The monitor callback is deferred: monitorCallCount stays 0 right after the
    // property assignment and only becomes 1 after ObserveSingleton.updateDirty().
    tcase('### addMonitor IMonitorValueInfo, comp.a_anyprop_no_meta.classB.propB1, ASYNC') {
        doAddMonitorOnePathNoWild(false);
    }

    // Wildcard path "comp.arr.*" on a custom MyArray<number>.
    // Verifies that element assignment (arr[i] = v) and mutating methods (arr.sort())
    // each trigger the monitor exactly once. Synchronous mode: each mutation fires
    // the callback immediately, so monitorCallCount increments per mutation.
    tcase('### addMonitor IMonitorValueInfo, wildcard for Array, SYNC') {
        doAddMonitorWildcardArray(true);
    }

    // Same as the SYNC array wildcard variant, but asynchronous.
    // updateDirty() is called between mutations so the deferred callback fires once
    // per mutation, matching the SYNC counts (1, 2, 3).
    tcase('### addMonitor IMonitorValueInfo, wildcard for Array, ASYNC') {
        doAddMonitorWildcardArray(false);
    }

    // Wildcard path "comp.a_anyprop_no_meta.*" on an IObserveAnyProp-implementing object.
    // Reassigning @Track properties (classB, classC) must fire the monitor;
    // mutating a non-tracked property (propA++) must NOT fire it.
    // Synchronous mode: callback fires immediately on each tracked assignment.
    tcase('### addMonitor IMonitorValueInfo, IObserveAnyProp object comp.a_anyprop_no_meta.*, SYNC') {
        doAddMonitorWildcardObservedObject(true);
    }

    // Same as the SYNC IObserveAnyProp wildcard variant, but asynchronous.
    // Confirms that the deferred path picks up reassignments to @Track members
    // and ignores writes to non-tracked members, just like the synchronous path.
    tcase('### addMonitor IMonitorValueInfo, IObserveAnyProp object comp.a_anyprop_no_meta.*, ASYNC') {
        doAddMonitorWildcardObservedObject(false);
    }

    // Single addMonitor call with an Array<IMonitorValueInfo> mixing a non-wildcard
    // path ("comp.a_anyprop_no_meta.classB.propB1") and a wildcard path
    // ("comp.a_anyprop_no_meta.*") rooted at the same IObserveAnyProp object.
    // Synchronous mode: the same monitor function fires immediately for each
    // tracked mutation on either path.
    tcase('### addMonitor Array<IMonitorValueInfo>, mixed wildcard + non-wildcard, SYNC') {
        doAddMonitorMixedWildAndNonWild(true);
    }

    // Same mixed wildcard + non-wildcard scenario, but asynchronous.
    // Confirms a single addMonitor call can register both path styles together
    // and that the deferred dispatch fires the monitor for each tracked mutation.
    tcase('### addMonitor Array<IMonitorValueInfo>, mixed wildcard + non-wildcard, ASYNC') {
        doAddMonitorMixedWildAndNonWild(false);
    }

    // Single addMonitor call with an Array<IMonitorValueInfo> that mixes a
    // non-wildcard path on a ParentComponent and a wildcard path on a SEPARATE
    // ComponentWithArray instance. Verifies one MonitorFunction can react to
    // mutations on two different objects. Synchronous mode: each tracked
    // mutation fires the monitor immediately.
    tcase('### addMonitor Array<IMonitorValueInfo>, mixed paths on different objects, SYNC') {
        doAddMonitorMixedWildAndNonWildDifferentObjects(true);
    }

    // Same cross-object mixed scenario, asynchronous.
    // Confirms the deferred dispatch correctly fires the monitor for each
    // tracked mutation regardless of which root object the path is rooted at.
    tcase('### addMonitor Array<IMonitorValueInfo>, mixed paths on different objects, ASYNC') {
        doAddMonitorMixedWildAndNonWildDifferentObjects(false);
    }

    // Dedup: one addMonitor call registers overlapping non-wildcard + wildcard
    // paths whose metas are both hit by a single mutation. Regression guard for
    // notes.md scenario #1 — upstream's Set-based drain must fire the callback
    // exactly once per fireChange cycle, not once per dirty path ref.
    tcase('### addMonitor overlapping non-wildcard + wildcard, dedup, SYNC') {
        doAddMonitorDedupOverlappingPaths(true);
    }
    tcase('### addMonitor overlapping non-wildcard + wildcard, dedup, ASYNC') {
        doAddMonitorDedupOverlappingPaths(false);
    }

    // Cascade: monitor A's callback mutates state watched by monitor B, forcing
    // a nested fireChange from inside the outer drain. Regression guard for
    // notes.md scenario #2 — upstream's swap-before-drain isolates the nested
    // queue cleanly so both monitors fire exactly once.
    tcase('### addMonitor sync monitor cascade, SYNC') {
        doAddMonitorSyncMonitorCascade(true);
    }
    tcase('### addMonitor sync monitor cascade, ASYNC') {
        doAddMonitorSyncMonitorCascade(false);
    }

    // Frozen: component is frozen before mutation, so the drain must defer the
    // callback via monitorPathRefsDelayed_ and only fire after unfreeze + a
    // subsequent updateDirty. Regression guard for notes.md scenario #4.
    tcase('### addMonitor frozen delays until unfreeze, SYNC') {
        doAddMonitorFrozenDelaysUntilUnfreeze(true);
    }
    tcase('### addMonitor frozen delays until unfreeze, ASYNC') {
        doAddMonitorFrozenDelaysUntilUnfreeze(false);
    }
}

ttest();
return true;
}
