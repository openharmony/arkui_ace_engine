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

import { ClassA_ObserveAnyProp_NoAnyMeta, ClassB_ObserveAnyProp, ClassC } from './uipluginObservedObject3'
import { MyArray } from './uiplugin_custom_arrays'
import { ObserveSingleton } from '../base/observeSingleton';
import { STATE_MGMT_FACTORY } from '../decorator'
import { uiUtils } from '../base/uiUtilsImpl';
import { UIUtils, MonitorBaseOptions, MonitorValueInfo } from '../utils';
import { TestMSM, TestMutableKeyedStateMeta } from './lib/testAddRefFireChange'

let StateMgmtFactory = STATE_MGMT_FACTORY;
let stateMgmtConsole=console;

/*
    @Observed class ClassA  {
        propA : number;
        @Track classB : ClassB_SingleMeta;

        // init with declaration
        @Track classC : ClassC = new ClassC;

        constructor() {
            // init in constructor
            this.classB = new ClassB_SingleMeta();
            this.propA = 8;
        }
    }

    // @Observe compat mode, no @Track
    @Observe class ClassB_SingleMeta {
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
    // __meta_any_property - NO, IObserveAnyProp - NO
    // __meta_any_property - NO, IObserveAnyProp - YES
    private _backing_a_anyprop_no_meta: ILocalDecoratedVariable<ClassA_ObserveAnyProp_NoAnyMeta>;

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
    let options: MonitorBaseOptions = {
        isSynchronous: sync,
        owner: comp,
    } as MonitorBaseOptions;
    let monitorFunction: MonitorCallback = (m: IMonitor) => {
        monitorCallCount++;
        console.log('[' + tag + '] Monitor triggered');
    };

    UIUtils.addMonitor(
        {valueCallback: valueCallback, path: 'comp.a_anyprop_no_meta.classB.propB1'} as MonitorValueInfo,
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
    let options: MonitorBaseOptions = {
        isSynchronous: sync,
        owner: arrayComp,
    } as MonitorBaseOptions;

    let monitorFunction: MonitorCallback = (m: IMonitor) => {
        monitorCallCount++;
        console.log('[' + tag + '] Monitor WILD triggered');
    };

    UIUtils.addMonitor(
        {valueCallback: valueCallbackWildcard, path: 'comp.arr.*', observeProps: true} as MonitorValueInfo,
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

    let options: MonitorBaseOptions = {
        isSynchronous: sync,
        owner: comp,
    } as MonitorBaseOptions;

    let monitorFunction: MonitorCallback = (m: IMonitor) => {
        monitorCallCount++;
        console.log('[' + tag + '] Monitor triggered comp.a_anyprop_no_meta.* ' + JSON.stringify(m));
        console.log('[' + tag + '] Monitor triggered comp.a_anyprop_no_meta.* ' + JSON.stringify(m.dirty));
    };

    UIUtils.addMonitor(
        {valueCallback: valueCallback_comp_A_Wildcard, path: 'comp.a_anyprop_no_meta.*', observeProps: true} as MonitorValueInfo,
        monitorFunction,
        options);

    comp.a_anyprop_no_meta.classB = new ClassB_ObserveAnyProp();
    ObserveSingleton.instance.updateDirty();
    test('[' + tag + '] monitorCallCount 1', eq(monitorCallCount, 1))

    comp.a_anyprop_no_meta.classC = new ClassC();
    ObserveSingleton.instance.updateDirty();
    test('[' + tag + '] monitorCallCount 2', eq(monitorCallCount, 2))

    comp.a_anyprop_no_meta.propA++;
    ObserveSingleton.instance.updateDirty();
    test('[' + tag + '] monitorCallCount 2 after propA++', eq(monitorCallCount, 2))
}

// Helper: single addMonitor call with an Array<MonitorValueInfo> that mixes
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

    let options: MonitorBaseOptions = {
        isSynchronous: sync,
        owner: comp,
    } as MonitorBaseOptions;

    const nonWildcardPath = 'comp.a_anyprop_no_meta.classB.propB1';
    const wildcardPath = 'comp.a_anyprop_no_meta.*';

    let monitorFunction: MonitorCallback = (m: IMonitor) => {
        monitorCallCount++;
        console.log('[' + tag + '] Monitor MIXED triggered, dirty: ' + JSON.stringify(m.dirty));

        // m.value() return values inside the callback:
        //   * wildcard path → always undefined (a wildcard binding fans out
        //     to multiple metas, so it doesn't represent a single observable
        //     read; m.value() skips wildcard entries).
        //   * non-wildcard path → defined IFF its path is in m.dirty for
        //     this fire; the returned IMonitorValue has .path equal to the
        //     path string passed in.
        const wv = m.value<ClassA_ObserveAnyProp_NoAnyMeta>(wildcardPath);
        test('[' + tag + '] m.value(wildcardPath) returns undefined',
            eq(wv === undefined, true));

        const nwv = m.value<string>(nonWildcardPath);
        const nonWildIsDirty = m.dirty.indexOf(nonWildcardPath) >= 0;
        if (nonWildIsDirty) {
            test('[' + tag + '] m.value(nonWildcardPath) defined when path is dirty',
                eq(nwv === undefined, false));
            test('[' + tag + '] m.value(nonWildcardPath).path matches input',
                eq(nwv === undefined ? '' : nwv!.path, nonWildcardPath));
        } else {
            test('[' + tag + '] m.value(nonWildcardPath) undefined when path not dirty',
                eq(nwv === undefined, true));
        }
    };

    UIUtils.addMonitor(
        new Array<MonitorValueInfo>(
            {valueCallback: valueCallbackPropB1, path: nonWildcardPath} as MonitorValueInfo,
            {valueCallback: valueCallbackAStar, path: wildcardPath, observeProps: true} as MonitorValueInfo
        ),
        monitorFunction,
        options);

    // 1) Mutate the non-wildcard path. propB1 lives on ClassB_SingleMeta, not on the
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

// Helper: single addMonitor call with an Array<MonitorValueInfo> that mixes
// a non-wildcard path and a wildcard path rooted at TWO DIFFERENT objects
// (separate component instances). One MonitorFunction must react to mutations
// on either object.
function doAddMonitorMixedWildAndNonWildDifferentObjects(sync: boolean): void {
    const tag: string = sync ? 'SYNC' : 'ASYNC';
    let monitorCallCount: int = 0;
    console.log('TestCase [' + tag + '] -> new ParentComponent + new ComponentWithArray');
    let comp = new ParentComponent(null, {});
    let arrayComp = new ComponentWithArray(null, {});

    const nonWildcardPath = 'comp.a_anyprop_no_meta.classB.propB1';
    const wildcardPath = 'arrayComp.arr.*';

    // Non-wildcard value info rooted at `comp` (ParentComponent).
    let valueCallbackPropB1 = () => {
        return comp.a_anyprop_no_meta.classB.propB1;
    }

    // Wildcard value info rooted at `arrayComp` (a different component instance).
    let valueCallbackArrStar = () => {
        console.log('[' + tag + '] valueCallback for ' + wildcardPath);
        return arrayComp.arr;
    }

    let options: MonitorBaseOptions = {
        isSynchronous: sync,
        owner: comp,
    } as MonitorBaseOptions;

    // Capture the per-fire snapshot so outside-the-callback assertions can
    // verify both the dirty list and the m.value() lookups for both paths.
    let lastDirty: Array<string> = new Array<string>();
    let lastNonWildValueDefined: boolean = false;
    let lastNonWildValueNow: string = '';
    let lastNonWildValuePath: string = '';
    let lastWildValueIsUndefined: boolean = false;

    let monitorFunction: MonitorCallback = (m: IMonitor) => {
        monitorCallCount++;
        lastDirty = m.dirty;
        console.log('[' + tag + '] Monitor MIXED-OBJECTS triggered, dirty: ' + JSON.stringify(m.dirty));

        const nwv = m.value<string>(nonWildcardPath);
        lastNonWildValueDefined = nwv !== undefined;
        lastNonWildValueNow = nwv === undefined ? '' : nwv!.now;
        lastNonWildValuePath = nwv === undefined ? '' : nwv!.path;

        // Wildcard always returns undefined — wildcard bindings fan out to
        // multiple metas, so they don't represent a single observable read.
        const wv = m.value<MyArray<number>>(wildcardPath);
        lastWildValueIsUndefined = wv === undefined;
    };

    UIUtils.addMonitor(
        new Array<MonitorValueInfo>(
            {valueCallback: valueCallbackPropB1, path: nonWildcardPath} as MonitorValueInfo,
            {valueCallback: valueCallbackArrStar, path: wildcardPath, observeProps: true} as MonitorValueInfo
        ),
        monitorFunction,
        options);

    // 1) Mutate the non-wildcard path on `comp`. propB1 starts at 'BBB111'.
    comp.a_anyprop_no_meta.classB.propB1 = 'new';
    test('[' + tag + '] mixed-objects: count after non-wildcard write before UpdateDirty',
        eq(monitorCallCount, sync ? 1 : 0))
    ObserveSingleton.instance.updateDirty();
    test('[' + tag + '] mixed-objects: count == 1 after non-wildcard write',
        eq(monitorCallCount, 1))
    test('[' + tag + '] mixed-objects: dirty list after #1 has exactly the non-wildcard path',
        eq(lastDirty.length === 1 && lastDirty[0] === nonWildcardPath, true))
    test('[' + tag + '] mixed-objects: m.value(nonWildcardPath) defined after #1',
        eq(lastNonWildValueDefined, true))
    test('[' + tag + '] mixed-objects: m.value(nonWildcardPath).path matches input after #1',
        eq(lastNonWildValuePath, nonWildcardPath))
    test('[' + tag + '] mixed-objects: m.value(nonWildcardPath).now == "new" after #1',
        eq(lastNonWildValueNow, 'new'))
    test('[' + tag + '] mixed-objects: m.value(wildcardPath) undefined after #1',
        eq(lastWildValueIsUndefined, true))

    // 2) Mutate an array element on `arrayComp` (covered by the wildcard).
    arrayComp.arr[1] = 1;
    ObserveSingleton.instance.updateDirty();
    test('[' + tag + '] mixed-objects: count == 2 after wildcard arr[1] write',
        eq(monitorCallCount, 2))
    test('[' + tag + '] mixed-objects: dirty list after #2 has exactly the wildcard path',
        eq(lastDirty.length === 1 && lastDirty[0] === wildcardPath, true))
    test('[' + tag + '] mixed-objects: m.value(nonWildcardPath) undefined after #2 (path not dirty)',
        eq(lastNonWildValueDefined, false))
    test('[' + tag + '] mixed-objects: m.value(wildcardPath) undefined after #2',
        eq(lastWildValueIsUndefined, true))

    // 3) Sort the array on `arrayComp` (mutating method, also wildcard).
    arrayComp.arr.sort()
    ObserveSingleton.instance.updateDirty();
    test('[' + tag + '] mixed-objects: count == 3 after wildcard arr.sort()',
        eq(monitorCallCount, 3))
    test('[' + tag + '] mixed-objects: dirty list after #3 has exactly the wildcard path',
        eq(lastDirty.length === 1 && lastDirty[0] === wildcardPath, true))
    test('[' + tag + '] mixed-objects: m.value(nonWildcardPath) undefined after #3 (path not dirty)',
        eq(lastNonWildValueDefined, false))
    test('[' + tag + '] mixed-objects: m.value(wildcardPath) undefined after #3',
        eq(lastWildValueIsUndefined, true))
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
    let valueCallbackClassB_SingleMeta = () => {
        console.log('[' + tag + '] valueCallback for comp.a_anyprop_no_meta.classB');
        return comp.a_anyprop_no_meta.classB;
    }
    // Wildcard path: reads comp.a_anyprop_no_meta → framework calls
    // addRefAnyProp() which binds both __meta_classB and __meta_classC.
    let valueCallbackStar = () => {
        console.log('[' + tag + '] valueCallback for comp.a_anyprop_no_meta.*');
        return comp.a_anyprop_no_meta;
    }

    let options: MonitorBaseOptions = {
        isSynchronous: sync,
        owner: comp,
    } as MonitorBaseOptions;

    let monitorFunction: MonitorCallback = (m: IMonitor) => {
        monitorCallCount++;
        console.log('[' + tag + '] Monitor DEDUP triggered, dirty: ' + JSON.stringify(m.dirty));
    };

    UIUtils.addMonitor(
        new Array<MonitorValueInfo>(
            {valueCallback: valueCallbackClassB_SingleMeta, path: 'comp.a_anyprop_no_meta.classB'} as MonitorValueInfo,
            {valueCallback: valueCallbackStar,   path: 'comp.a_anyprop_no_meta.*', observeProps: true} as MonitorValueInfo
        ),
        monitorFunction,
        options);

    // Single mutation that dirties BOTH registered paths via __meta_classB.
    // Upstream behavior: dedup to ONE callback invocation per fireChange cycle.
    comp.a_anyprop_no_meta.classB = new ClassB_ObserveAnyProp();
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
        compB.a_anyprop_no_meta.classB = new ClassB_ObserveAnyProp();
    };
    UIUtils.addMonitor(
        {valueCallback: valueCallbackA, path: 'compA.a_anyprop_no_meta.classB'} as MonitorValueInfo,
        monitorFunctionA,
        { isSynchronous: sync, owner: compA } as MonitorBaseOptions);

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
        {valueCallback: valueCallbackB, path: 'compB.a_anyprop_no_meta.classB'} as MonitorValueInfo,
        monitorFunctionB,
        { isSynchronous: sync, owner: compB } as MonitorBaseOptions);

    // Trigger the cascade: assigning compA.classB fires A, whose callback
    // assigns compB.classB, which must fire B before control returns.
    compA.a_anyprop_no_meta.classB = new ClassB_ObserveAnyProp();

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
        {valueCallback: valueCallback, path: 'comp.a_anyprop_no_meta.classB'} as MonitorValueInfo,
        monitorFunction,
        { isSynchronous: sync, owner: comp } as MonitorBaseOptions);

    // Freeze the component BEFORE mutating, so notifyDirtyMonitorPaths' isFreeze()
    // check routes the ref to monitorPathRefsDelayed_.
    comp.setViewActive(false);

    console.log('TestCase [' + tag + '] (frozen) update comp.a_anyprop_no_meta.classB = new ClassB_SingleMeta()');
    comp.a_anyprop_no_meta.classB = new ClassB_ObserveAnyProp();
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

// Regression guard: when an async drain batches multiple per-monitor fires
// with DIFFERENT targets, the wildcard LSV check (`sources.has(this.before)`)
// must see every source — not just the last one written.
//
// Setup:
//   monitor lambda  : () => comp.a_anyprop_no_meta.classB
//   wildcard        : comp.a_anyprop_no_meta.classB.*
//
// The lambda binds the monitor to (a) the @Local backingValue meta of
// a_anyprop_no_meta, (b) oldA.__meta_classB, and (c) classB's @Track metas
// (via addRefAnyProp on classB).
//
// Two batched async mutations fire with two DIFFERENT targets:
//   1) originalClassB.propB1 = 'new'              → addDirtyRef source = originalClassB
//   2) comp.a_anyprop_no_meta = newA              → addDirtyRef source = newA
//      where newA.classB has been swapped to originalClassB so the lambda's
//      result is unchanged after both mutations: before === now === originalClassB.
//
// With Map<weakThis, single-source> last-writer-wins, mutation (2)'s source
// (newA) overwrites mutation (1)'s (originalClassB). The wildcard check
// `source === this.before` fails (newA !== originalClassB), and the value
// fall-through `before !== now` also fails (both are originalClassB), so
// the monitor stays clean and `count === 0`.
//
// With Map<weakThis, Set<source>>, both sources are preserved.
// `sources.has(this.before)` finds originalClassB, dirty=true, monitor fires.
function doAddMonitorMultiSourceLSV(): void {
    let monitorCallCount: int = 0;
    let comp = new ParentComponent(null, {});

    let valueCallback = () => {
        return comp.a_anyprop_no_meta.classB;
    }
    let monitorFunction: MonitorCallback = (_m: IMonitor) => {
        monitorCallCount++;
    };

    UIUtils.addMonitor(
        {valueCallback: valueCallback, path: 'comp.a_anyprop_no_meta.classB.*', observeProps: true} as MonitorValueInfo,
        monitorFunction,
        { isSynchronous: false, owner: comp } as MonitorBaseOptions);

    // Capture the classB instance the lambda recorded as `before`.
    let originalClassB = comp.a_anyprop_no_meta.classB;

    // (1) Inner mutation on originalClassB → addDirtyRef(monitor, originalClassB)
    originalClassB.propB1 = 'new';

    // (2) Replace the parent ClassA with a new instance whose classB is the
    // SAME originalClassB reference. The @Local setter fires with target=newA.
    // The newA.classB = originalClassB inner assignment fires newA's own
    // __meta_classB, but that meta has no bindings yet (newA was just built),
    // so it's a no-op for the queued drain.
    let newA = new ClassA_ObserveAnyProp_NoAnyMeta();
    newA.classB = originalClassB;
    comp.a_anyprop_no_meta = newA;

    // before === now === originalClassB. Without Set<source> the LSV match
    // is lost and the monitor never fires.
    ObserveSingleton.instance.updateDirty();
    test('multi-source LSV: monitor fires once when batched fires include the LSV target',
        eq(monitorCallCount, 1));
}

// SYNC variant of doAddMonitorMultiSourceLSV. Same setup, but the drain
// happens after every fireChange instead of being batched by updateDirty().
//
//   1) originalClassB.propB1 = 'new'   → drain sources = {originalClassB}
//      sources.has(this.before === originalClassB) ⇒ dirty, monitor fires
//      → count = 1, before is reset to originalClassB by the post-fire reset.
//
//   2) comp.a_anyprop_no_meta = newA   → drain sources = {newA}
//      where newA.classB has been swapped to originalClassB so the lambda
//      still returns originalClassB and before === now === originalClassB.
//      sources.has(originalClassB) is FALSE (only newA), and the value
//      fall-through `before !== now` is also false. The monitor must NOT
//      re-fire — nothing about classB itself has changed; only the parent
//      reference moved, and the child wildcard's identity guard keeps it
//      from firing on that.
//
// Documents the sync wildcard LSV contract: per-fireChange drains see one
// source at a time, so the recovery the multi-source set buys for the
// async path doesn't apply here, and the LSV identity guard is the only
// thing keeping a parent-swap-with-unchanged-child from spuriously firing
// the child wildcard.
function doAddMonitorMultiSourceLSVSync(): void {
    let monitorCallCount: int = 0;
    let comp = new ParentComponent(null, {});

    let valueCallback = () => {
        return comp.a_anyprop_no_meta.classB;
    }
    let monitorFunction: MonitorCallback = (_m: IMonitor) => {
        monitorCallCount++;
    };

    UIUtils.addMonitor(
        {valueCallback: valueCallback, path: 'comp.a_anyprop_no_meta.classB.*', observeProps: true} as MonitorValueInfo,
        monitorFunction,
        { isSynchronous: true, owner: comp } as MonitorBaseOptions);

    let originalClassB = comp.a_anyprop_no_meta.classB;

    // (1) Inner mutation on originalClassB. SYNC: drain runs immediately.
    // sources={originalClassB} matches the LSV, monitor fires once.
    originalClassB.propB1 = 'new';
    test('sync multi-source LSV: monitor fires once after inner change',
        eq(monitorCallCount, 1));

    // (2) Parent swap that leaves the watched child reference unchanged.
    // SYNC: drain runs immediately with sources={newA}. newA !== before
    // (originalClassB) and before === now, so the monitor must not re-fire.
    let newA = new ClassA_ObserveAnyProp_NoAnyMeta();
    newA.classB = originalClassB;
    comp.a_anyprop_no_meta = newA;
    test('sync multi-source LSV: parent swap with same classB does not re-fire',
        eq(monitorCallCount, 1));
}

export function run_addmonitor(): boolean {

    const ttest = tsuite('@AddMonitor with wildcards') {

    // Single non-wildcard path on an @ObserveAnyProp object.
    // Synchronous mode: monitor callback fires immediately on property assignment,
    // before updateDirty() is called. monitorCallCount must be 1 right after the
    // assignment and remain 1 after updateDirty().
    tcase('### addMonitor MonitorValueInfo, comp.a_anyprop_no_meta.classB.propB1, SYNC') {
        doAddMonitorOnePathNoWild(true);
    }

    // Same scenario as the SYNC variant above, but asynchronous.
    // The monitor callback is deferred: monitorCallCount stays 0 right after the
    // property assignment and only becomes 1 after ObserveSingleton.updateDirty().
    tcase('### addMonitor MonitorValueInfo, comp.a_anyprop_no_meta.classB.propB1, ASYNC') {
        doAddMonitorOnePathNoWild(false);
    }

    // Wildcard path "comp.arr.*" on a custom MyArray<number>.
    // Verifies that element assignment (arr[i] = v) and mutating methods (arr.sort())
    // each trigger the monitor exactly once. Synchronous mode: each mutation fires
    // the callback immediately, so monitorCallCount increments per mutation.
    tcase('### addMonitor MonitorValueInfo, wildcard for Array, SYNC') {
        doAddMonitorWildcardArray(true);
    }

    // Same as the SYNC array wildcard variant, but asynchronous.
    // updateDirty() is called between mutations so the deferred callback fires once
    // per mutation, matching the SYNC counts (1, 2, 3).
    tcase('### addMonitor MonitorValueInfo, wildcard for Array, ASYNC') {
        doAddMonitorWildcardArray(false);
    }

    // Wildcard path "comp.a_anyprop_no_meta.*" on an IObserveAnyProp-implementing object.
    // Reassigning @Track properties (classB, classC) must fire the monitor;
    // mutating a non-tracked property (propA++) must NOT fire it.
    // Synchronous mode: callback fires immediately on each tracked assignment.
    tcase('### addMonitor MonitorValueInfo, IObserveAnyProp object comp.a_anyprop_no_meta.*, SYNC') {
        doAddMonitorWildcardObservedObject(true);
    }

    // Same as the SYNC IObserveAnyProp wildcard variant, but asynchronous.
    // Confirms that the deferred path picks up reassignments to @Track members
    // and ignores writes to non-tracked members, just like the synchronous path.
    tcase('### addMonitor MonitorValueInfo, IObserveAnyProp object comp.a_anyprop_no_meta.*, ASYNC') {
        doAddMonitorWildcardObservedObject(false);
    }

    // Single addMonitor call with an Array<MonitorValueInfo> mixing a non-wildcard
    // path ("comp.a_anyprop_no_meta.classB.propB1") and a wildcard path
    // ("comp.a_anyprop_no_meta.*") rooted at the same IObserveAnyProp object.
    // Synchronous mode: the same monitor function fires immediately for each
    // tracked mutation on either path.
    tcase('### addMonitor Array<MonitorValueInfo>, mixed wildcard + non-wildcard, SYNC') {
        doAddMonitorMixedWildAndNonWild(true);
    }

    // Same mixed wildcard + non-wildcard scenario, but asynchronous.
    // Confirms a single addMonitor call can register both path styles together
    // and that the deferred dispatch fires the monitor for each tracked mutation.
    tcase('### addMonitor Array<MonitorValueInfo>, mixed wildcard + non-wildcard, ASYNC') {
        doAddMonitorMixedWildAndNonWild(false);
    }

    // Single addMonitor call with an Array<MonitorValueInfo> that mixes a
    // non-wildcard path on a ParentComponent and a wildcard path on a SEPARATE
    // ComponentWithArray instance. Verifies one MonitorFunction can react to
    // mutations on two different objects. Synchronous mode: each tracked
    // mutation fires the monitor immediately.
    tcase('### addMonitor Array<MonitorValueInfo>, mixed paths on different objects, SYNC') {
        doAddMonitorMixedWildAndNonWildDifferentObjects(true);
    }

    // Same cross-object mixed scenario, asynchronous.
    // Confirms the deferred dispatch correctly fires the monitor for each
    // tracked mutation regardless of which root object the path is rooted at.
    tcase('### addMonitor Array<MonitorValueInfo>, mixed paths on different objects, ASYNC') {
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

    // Regression guard: the async drain must preserve every triggering source
    // per monitor (not last-writer-wins) so the wildcard LSV check finds the
    // matching source even when batched fires arrive with mixed targets.
    tcase('### addMonitor multi-source LSV preserves all sources, ASYNC') {
        doAddMonitorMultiSourceLSV();
    }

    // SYNC counterpart: per-fireChange drains see one source at a time, so
    // the LSV check fires on inner-change but a parent swap whose watched
    // child reference is unchanged must not spuriously re-fire.
    tcase('### addMonitor multi-source LSV sync semantics, SYNC') {
        doAddMonitorMultiSourceLSVSync();
    }
}

ttest();
return true;
}
