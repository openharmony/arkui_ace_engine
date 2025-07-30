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


import { stateMgmtConsole } from 'stateManagement/tools/stateMgmtConsoleTrace';
import { tsuite, tcase, test, eq } from 'stateManagement/utest/lib/testFramework'
import { StateMgmtFactory } from '../../interface/iStateMgmtFactory.ets'
import { ILocalDecoratedVariable } from 'stateManagement/interface/iDecorators.ets'
import { IMonitorFunctionDecorator, IMonitorPathsInfo, MonitorPathLambda, MonitorFunction } from 'stateManagement/interface/iMonitorFunctionDecorator.ets'
import { IMonitor } from 'stateManagement/sdk/iMonitor.ets'
import { ExtendableComponent } from 'stateManagement/base/extendableComponent'

import { ClassA, ClassB } from 'stateManagement/utest/uiPlugin/uipluginObservedObject3'
import { MyArray } from 'stateManagement/utest/uiPlugin/uiplugin_custom_arrays'
import { ObserveSingleton } from '../../base/observeSingleton.ets';

// UI plugin generate
interface ParentComponent_init_update_struct {
    // @Local nothing, @Local can not init from parent @Component/V2
}

class ParentComponent extends ExtendableComponent {
    // @Local arr: MyArray<ClassA> = new MyArray<ClassA>(new ClassA(), new ClassA());
    private _backing_arr: ILocalDecoratedVariable<MyArray<ClassA>>;
    get arr(): MyArray<ClassA> {
        return this._backing_arr.get();
    }
    set arr(newValue: MyArray<ClassA>) {
        this._backing_arr.set(newValue);
    }

    public monitorFunctionRunCount: number = 0;

    // @Monitor("arr.1.classB.propB1", "arr.2.classB", "length") onArrChanged(m: IMonitor)
    private _monitor: IMonitorFunctionDecorator;
    public onArrChanged?: (m: IMonitor) => void;

    // @Monitor("arr.arrProp") onArrPropChanged(m: IMonitor)
    private _monitorArrProp: IMonitorFunctionDecorator;
    public onArrPropChanged?: (m: IMonitor) => void;

    constructor(parent: ExtendableComponent | null, param: ParentComponent_init_update_struct) {
        super(parent)
        // @Local optional to init from parent
        // must check if defined, the following is WRONG
        // because can not differentiate btw undefiend value 
        // and param.localA not defined
        this._backing_arr = StateMgmtFactory.makeLocal<MyArray<ClassA>>(
            this,
            "arr",
            /* local init value */ new MyArray<ClassA>(new ClassA(), new ClassA()));

        this._monitor = StateMgmtFactory.makeMonitor(new Array<IMonitorPathsInfo>(
            StateMgmtFactory.makeMonitorPath("arr.1.classB.propB1", () => {
                const result = this.arr[1].classB.propB1;
                stateMgmtConsole.log(`===== lamda for path 'arr.1.classB.propB1', value: ${result}`);
                return result;
            }),
            StateMgmtFactory.makeMonitorPath("arr.2.classB", () => {
                const result = this.arr[2].classB;
                stateMgmtConsole.log(`==== lamda for path 'arr.2.classB', value: ${result}`);
                return result;
            }),
            StateMgmtFactory.makeMonitorPath("length", () => {
                return this.arr.length;
            })
        ), 
            (m: IMonitor) => {
                this.onArrChanged!(m);
            }
        );

        this._monitorArrProp = StateMgmtFactory.makeMonitor(new Array<IMonitorPathsInfo>(
            StateMgmtFactory.makeMonitorPath("arr.arrProp", () => {
                const result = this.arr.arrProp;
                stateMgmtConsole.log(`==== lambda for path 'arr.arrProp', value: ${result}`);
                return result;
            })
        ),
            (m: IMonitor) => {
                this.onArrPropChanged!(m);
            }
        );
    }
}

export function run_monitor_array(): boolean {

    const ttest = tsuite("@Monitor arrays") {
        let comp: ParentComponent;

    tcase("#1: init ======") {
        comp = new ParentComponent(null, {});
    }

    tcase("#2: change existing array item =====") {

        comp.onArrChanged = (m: IMonitor) => {
            stateMgmtConsole.debug(`tcase #2 onArrChanged`);

            comp.monitorFunctionRunCount += 1;

            test("m.dirty length", eq(m.dirty.length, 1))
            test("m.dirty[0] value", eq(m.dirty[0], 'arr.1.classB.propB1'));
            
            let monitorValue = m.value<string>(Type.of("hello"), 'arr.1.classB.propB1');
            test("m.value<..>(Type.of('hello', 'arr.1.classB.propB1')).path", eq(monitorValue!.path, 'arr.1.classB.propB1'));
            test("m.value<..>(Type.of('hello', 'arr.1.classB.propB1')).now", eq(monitorValue!.now, "new"));

            let firstDirtyValue = m.value<string>(Type.of("hello"));
            test("m.value<..>(Type.of('hello')).path", eq (firstDirtyValue!.path, 'arr.1.classB.propB1'));
            test("m.value<..>(Type.of('hello')).now", eq (firstDirtyValue!.now, "new"));
        }

        // mutate sate e.g. in onclick
        stateMgmtConsole.log("++++++ assign to comp.a.classB.propB1")
        comp.arr[1].classB.propB1 = "new";

        // give framework a chance to respond to value change
        // this will run 
        ObserveSingleton.instance.updateDirty2();

        test("@Monitor function has run", eq(comp.monitorFunctionRunCount, 1));
    }

    tcase("#3: add item for path that wasn't available =====") {

        const newItem: ClassA = new ClassA();

        comp.onArrChanged = (m: IMonitor) => {
            stateMgmtConsole.debug(`tcase #3 onArrChanged`);

            comp.monitorFunctionRunCount += 1;

            test("m.dirty length", eq(m.dirty.length, 2))
            test("m.dirty[0] value", eq(m.dirty[0], 'arr.2.classB'));
            test("m.dirty[1] value", eq(m.dirty[1], 'length'));
            
            let monitorValue = m.value<ClassB>(Type.of(new ClassB()), 'arr.2.classB');
            test("m.value<ClassB>(Type.of(new ClassB()), 'arr.2.classB').path", eq(monitorValue!.path, 'arr.2.classB'));
            test("m.value<ClassB>(Type.of(new ClassB()), 'arr.2.classB').now", eq(monitorValue!.now, newItem.classB));

            let firstDirtyValue = m.value<ClassB>(Type.of(new ClassB()));
            test("m.value<ClassB>(Type.of(new ClassB())).path", eq (firstDirtyValue!.path, 'arr.2.classB'));
            test("m.value<ClassB>(Type.of(new ClassB())).now", eq (firstDirtyValue!.now, newItem.classB));

            let monitorValueLength = m.value<number>(Type.of(8), 'length');
            test("m.value<number>(Type.of(8), 'length').path", eq(monitorValueLength!.path, 'length'));
            test("m.value<number>(Type.of(8), 'length').now", eq(monitorValueLength!.now, 3));
            test("m.value<number>(Type.of(8), 'length').before", eq(monitorValueLength!.before, 2));
        }

        // mutate sate e.g. in onclick
        stateMgmtConsole.log("++++++ arr.push() ")
        comp.arr.push(newItem);

        // give framework a chance to respond to value change
        // this will run 
        ObserveSingleton.instance.updateDirty2();

        test("@Monitor function has run", eq(comp.monitorFunctionRunCount, 2));
    }

    tcase("#4: change custom property =====") {
        comp.onArrPropChanged = (m: IMonitor) => {
            stateMgmtConsole.debug(`tcase #4 onArrPropChanged`);

            comp.monitorFunctionRunCount += 1;

            test("m.dirty length", eq(m.dirty.length, 1))
            test("m.dirty[0] value", eq(m.dirty[0], 'arr.arrProp'));

            let firstDirtyValue = m.value<string>(Type.of('hello'));
            test("m.value<string>(Type.of('hello')).path", eq (firstDirtyValue!.path, 'arr.arrProp'));
            test("m.value<string>(Type.of('hello')).now", eq (firstDirtyValue!.now, "testnew"));
            test("m.value<string>(Type.of('hello')).before", eq (firstDirtyValue!.before, "test"));
        }
    }

    // mutate sate e.g. in onclick
    stateMgmtConsole.log("++++++ arr.arrProp += 'new' ");
    comp.arr.arrProp += 'new';

    // give framework a chance to respond to value change
    // this will run 
    ObserveSingleton.instance.updateDirty2();

    test("@Monitor for arrProp has run", eq(comp.monitorFunctionRunCount, 3));
}

ttest();
return true;
}
