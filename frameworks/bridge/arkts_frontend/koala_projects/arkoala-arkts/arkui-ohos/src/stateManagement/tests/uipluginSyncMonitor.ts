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

import { ClassAWithAnyMeta, ClassB, ClassC, ClassA } from './uipluginObservedObject3'
import { MyArray } from './uiplugin_custom_arrays'
import { ObserveSingleton } from '../base/observeSingleton';
import { STATE_MGMT_FACTORY } from '../decorator'
import { uiUtils } from '../base/uiUtilsImpl';
import { UIUtils, MonitorOptions } from '../utils';
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
interface ParentComponent_init_update_struct {
    // @Local nothing, @Local can not init from parent @Component/V2
}

class ParentComponent extends ExtendableComponent {
    // @Local a: ClassA = new ClassA();
    private _backing_a: ILocalDecoratedVariable<ClassAWithAnyMeta>;
    private _backing_a_no_any: ILocalDecoratedVariable<ClassA>;
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

    }
}

// UI plugin generates
interface ComponentWithArray_init_update_struct {
    arr?: MyArray<number>;
}

class ComponentWithArray extends ExtendableComponent {
    private _backing_state_arr: ILocalDecoratedVariable<MyArray<number>>;
    get arr(): MyArray<number> {
        console.log('ParentComponent.arr()');
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

interface NonObservedInterface {
    prop1: string;
    prop2: string;
}

function doTcase8() {
    let monitorCallCount: int = 0;
    console.log('TestCase -> new ParentComponent');
    let proxiedObjectLiteral : NonObservedInterface = UIUtils.makeObserved(
        { prop1: 'A', prop2: 'B'} as NonObservedInterface);

    // Solution #1:
    // Compiler generated function that reads all trackable properties for the wild card path
    // Benefits
    // - Does not increase memory usage for every class that we want to monitor with the classInstance.*
    // - We do not use reflect API to iterate through all trackable properties

    let valueCallback = () => {
        console.log('valueCallback proxiedClass.prop1');
        return proxiedObjectLiteral.prop1;
    }

    let monitorFunction: MonitorCallback = (m: IMonitor) => {
        monitorCallCount++;
        console.log('Monitor triggered comp.a.*'  + JSON.stringify(m));
        console.log('Monitor triggered comp.a.*'  + JSON.stringify(m.dirty));
    };

    console.log('TestCase -> addMonitor');
    let _monitor = STATE_MGMT_FACTORY.makeSyncMonitor([{
            path: 'proxiedObjectLiteral.prop1',
            valueCallback: valueCallback
        } as IMonitorPathInfo] as IMonitorPathInfo[],
        monitorFunction,
        undefined
    );

    proxiedObjectLiteral.prop1 = 'newstring';
    test('monitorCallCount 1', eq(monitorCallCount, 1))
}
function doTcase9() {
    let monitorCallCount: int = 0;
    console.log('TestCase -> new ParentComponent');
    let v1Observed = new ClassB();

    let valueCallback = () => {
        console.log('valueCallback v1Observed.*');
        // it is enough to read any of the properties to record dependency
        v1Observed.propB1;
        return undefined;
    }

    let monitorFunction: MonitorCallback = (m: IMonitor) => {
        monitorCallCount++;
        console.log('Monitor triggered v1Observed.*'  + JSON.stringify(m));
    };

    v1Observed.propB2 = true;
    let _monitor = STATE_MGMT_FACTORY.makeSyncMonitor([{
            path: 'v1Observed.*',
            isWildcard: true,
            valueCallback: valueCallback
        } as IMonitorPathInfo] as IMonitorPathInfo[],
        monitorFunction,
        undefined
    );

    v1Observed.propB1 = 'new string';
    test('monitorCallCount 1', eq(monitorCallCount, 1))
    v1Observed.propB1 = 'newer string';
    test('monitorCallCount 3', eq(monitorCallCount, 2))
    v1Observed.propB2 = false;
    test('monitorCallCount 3', eq(monitorCallCount, 3))
    v1Observed.propB2 = true;
    test('monitorCallCount 4', eq(monitorCallCount, 4))
    v1Observed.propB2 = true;
    test('monitorCallCount 4', eq(monitorCallCount, 4))
}

function doTest4()
{
    let monitorCallCount: int = 0;
    console.log('TestCase -> new ParentComponent');
    let comp = new ParentComponent(null, {});

    // solution 2:
    // ObservedV2 class implements IObserveAnyProp.addRefAnyProp
    // That means more complex implementaiton of ObservedV2
    //
    // recordDependenciesForMonitorValue will call that method for wildcard path

    // TODO: That solution look closer to what we finally agreed
    let valueCallback_comp_a_Wildcard_S2 = () => {
        console.log('valueCallback for comp.a.*, solution2');
        return comp.a;
    }

    let monitorFunction: MonitorCallback = (m: IMonitor): void => {
        monitorCallCount++;
        console.log('Monitor triggered comp.a.*'  + JSON.stringify(m));
        console.log('Monitor triggered comp.a.*'  + JSON.stringify(m.dirty));
    };

    let _monitor = STATE_MGMT_FACTORY.makeSyncMonitor([{
            path: 'comp.a.*',
            isWildcard: true,
            valueCallback: valueCallback_comp_a_Wildcard_S2
        } as IMonitorPathInfo] as IMonitorPathInfo[],
        monitorFunction,
        undefined
    );

    comp.a.classB = new ClassB();
    comp.a.classC = new ClassC();
    comp.a.propA++;
    test('monitorCallCount == 2', eq(monitorCallCount, 2))
}

function doTest5()
{
    let monitorCallCount: int = 0;
    console.log('TestCase -> new ParentComponent');
    let arrayComp = new ComponentWithArray(null, {});

    let valueCallbackWildcard = () => {
        console.log('valueCallback comp.arr ')
        return arrayComp.arr;
    }

    let monitorFunction: MonitorCallback = (m: IMonitor) => {
        monitorCallCount++;
        console.log('Monitor WILD triggered');
    };

    let _monitor = STATE_MGMT_FACTORY.makeSyncMonitor([{
            path: 'comp.arr.*',
            isWildcard: true,
            valueCallback: valueCallbackWildcard
        } as IMonitorPathInfo] as IMonitorPathInfo[],
        monitorFunction,
        undefined
    );

    arrayComp.arr[1] = 1;
    test('monitorCallCount == 1', eq(monitorCallCount, 1))
    arrayComp.arr[1] = 500;
    test('monitorCallCount == 2', eq(monitorCallCount, 2))
    arrayComp.arr.sort()
    test('monitorCallCount == 3', eq(monitorCallCount, 3))
    test('monitorCallCount == 3', eq(monitorCallCount, 3))
}

export function run_sync_monitor(): boolean {

    const ttest = tsuite('@SyncMonitor basics') {

    tcase('### 4: makeSyncMonitor @ObservedV2 object comp.a.*, Solution 2, using  MonitorFunctionDecorator directly') {
        doTest4();
    }


    tcase('### 5, mirror of 2, makeSyncMonitor with wildcard for Array') {
        doTest5();
    }

    // TODO: we decided to drop that solution
    tcase('### 6, mirror of 3: makeSyncMonitor @ObservedV2 object comp.a.*') {
        let monitorCallCount: int = 0;
        console.log('TestCase -> new ParentComponent');
        let comp = new ParentComponent(null, {});

        // Solution #1:
        // Compiler generated function that reads all trackable properties for the wild card path
        // Benefits
        // - Does not increase memory usage for every class that we want to monitor with the classInstance.*
        // - We do not use reflect API to iterate through all trackable properties

        let valueCallback_comp_A_Wildcard = () => {
            console.log('valueCallback for comp.a.*');
            comp.a_no_any.classB;
            comp.a_no_any.classC;
            // Returns undefined
            return undefined;
        }

        let monitorFunction: MonitorCallback = (m: IMonitor) => {
            monitorCallCount++;
            console.log('Monitor triggered comp.a.*'  + JSON.stringify(m));
            console.log('Monitor triggered comp.a.*'  + JSON.stringify(m.dirty));
        };

        console.log('TestCase -> addMonitor');
        let _monitor = STATE_MGMT_FACTORY.makeSyncMonitor([{
                path: 'comp.a_no_any.*',
                isWildcard: true,
                valueCallback: valueCallback_comp_A_Wildcard
            } as IMonitorPathInfo] as IMonitorPathInfo[],
            monitorFunction,
            undefined
        );

        comp.a_no_any.classB = new ClassB();
        test('monitorCallCount 1', eq(monitorCallCount, 1))
        comp.a_no_any.classC = new ClassC();
        test('monitorCallCount 2', eq(monitorCallCount, 2))
        comp.a_no_any.propA++;
        test('monitorCallCount 2', eq(monitorCallCount, 2))
        comp.a_no_any = new ClassA();
        test('monitorCallCount 3', eq(monitorCallCount, 3))
    }

    // TODO: proxy fails for current version of the framework
    // node_modules-62220
    tcase('### 7, makeSyncMonitor @ObservedV2 for makeObserved') {
        let monitorCallCount: int = 0;
        console.log('TestCase -> new ParentComponent');
        let proxiedClass = UIUtils.makeObserved(new NonObservedClass());

        // Solution #1:
        // Compiler generated function that reads all trackable properties for the wild card path
        // Benefits
        // - Does not increase memory usage for every class that we want to monitor with the classInstance.*
        // - We do not use reflect API to iterate through all trackable properties

        let valueCallback = () => {
            console.log('valueCallback proxiedClass.prop1');
            return proxiedClass.prop1;
        }

        let monitorFunction: MonitorCallback = (m: IMonitor) => {
            monitorCallCount++;
            console.log('Monitor triggered comp.a.*'  + JSON.stringify(m));
            console.log('Monitor triggered comp.a.*'  + JSON.stringify(m.dirty));
        };

        console.log('TestCase -> addMonitor');
        let _monitor = STATE_MGMT_FACTORY.makeSyncMonitor([{
                path: 'proxiedClass.prop1',
                valueCallback: valueCallback
            } as IMonitorPathInfo] as IMonitorPathInfo[],
            monitorFunction,
            undefined
        );

        proxiedClass.prop1 = 'newstring';
        test('monitorCallCount 1', eq(monitorCallCount, 1))
    }

    // TODO: proxy fails in sdk
    tcase('### 8, makeSyncMonitor @ObservedV2 for makeObserved') {
        doTcase8();
    }

    tcase('### 9, makeSyncMonitor @Observed, V1 observation') {
        doTcase9();
    }

}

ttest();
return true;
}
