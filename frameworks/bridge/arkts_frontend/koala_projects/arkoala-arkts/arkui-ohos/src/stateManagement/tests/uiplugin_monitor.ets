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

import { ClassA } from 'stateManagement/utest/uiPlugin/uipluginObservedObject3'
import { ObserveSingleton } from '../../base/observeSingleton.ets';

// UI plugin generate
interface ParentComponent_init_update_struct {
    // @Local nothing, @Local can not init from parent @Component/V2
}

let onAChanged: (m: IMonitor) => void;

class ParentComponent extends ExtendableComponent {
    // @Local a: ClassA = new ClassA();
    private _backing_a: ILocalDecoratedVariable<ClassA>;
    get a(): ClassA {
        return this._backing_a.get();
    }
    set a(newValue: ClassA) {
        this._backing_a.set(newValue);
    }

    public monitorFunctionRunCount: number = 0;

    // @Monitor("b.obj.propA") onAChanged(m: IMonitor)
    private _monitor: IMonitorFunctionDecorator;
    public onAChanged?: (m: IMonitor) => void;

    constructor(parent: ExtendableComponent | null, param: ParentComponent_init_update_struct) {
        super(parent)
        // @Local optional to init from parent
        // must check if defined, the following is WRONG
        // because can not differentiate btw undefiend value 
        // and param.localA not defined
        this._backing_a = StateMgmtFactory.makeLocal<ClassA>(
            this,
            "a",
            /* local init value */ new ClassA());

        this._monitor = StateMgmtFactory.makeMonitor(new Array<IMonitorPathsInfo>(
            StateMgmtFactory.makeMonitorPath("a.propA", () => {
                const result = this.a.propA;
                console.log("===== lamda for path a.propA, value: ", result);
                return result;
            }),
            StateMgmtFactory.makeMonitorPath("a.classB.propB1", () => {
                const result = this.a.classB.propB1;
                console.log("==== lamda for path a.classB.propB1, value: ", result);
                return result;
            })
        ), 
            (m: IMonitor) => {
                this.onAChanged!(m);
            }
        );
    }
}

export function run_monitor(): boolean {

    const ttest = tsuite("@Monitor basics") {
        let comp: ParentComponent;

    tcase("#1: init ======") {
        comp = new ParentComponent(null, {});
    }

    tcase("#2: change @Tracked property and verify Monitor function =====") {

        comp.onAChanged = (m: IMonitor) => {
            stateMgmtConsole.debug(`tcase #2 onAChanged`);

            comp.monitorFunctionRunCount += 1;

            test("m.dirty length", eq(m.dirty.length, 1))
            test("m.dirty[0] value", eq(m.dirty[0], "a.classB.propB1"));
            
            let monitorValue = m.value<string>(Type.of("hello"), "a.classB.propB1");
            test("m.value<..>(Type.of('hello', a.classB.propB1)).path", eq(monitorValue!.path, "a.classB.propB1"));
            test("m.value<..>(Type.of('hello', a.classB.propB1)).now", eq(monitorValue!.now, "new"));

            let firstDirtyValue = m.value<string>(Type.of("hello"));
            test("m.value<..>(Type.of('hello')).path", eq (firstDirtyValue!.path, "a.classB.propB1"));
            test("m.value<..>(Type.of('hello')).now", eq (firstDirtyValue!.now, "new"));
        }

        // mutate sate e.g. in onclick
        console.log("++++++ assign to comp.a.classB.propB1")
        comp.a.classB.propB1 = "new";

        // give framework a chance to respond to value change
        // this will run 
        ObserveSingleton.instance.updateDirty2();

        test("@Monitor function has run", eq(comp.monitorFunctionRunCount, 1));
    }

    tcase("#3: change regular and @Tracked property and verify Monitor function =====") {

        comp.onAChanged = (m: IMonitor) => {
            stateMgmtConsole.debug(`tcase #3 onAChanged`);

            comp.monitorFunctionRunCount += 1;

            test("m.dirty length", eq(m.dirty.length, 1))
            test("m.dirty[0] value", eq(m.dirty[0], "a.classB.propB1"));
        }

        // mutate sate e.g. in onclick
        console.log("++++++ assign to comp.a.propA and comp.a.classB.propB1")
        comp.a.propA = 1;
        comp.a.classB.propB1 = "new again";

        // give framework a chance to respond to value change
        // this will run 
        ObserveSingleton.instance.updateDirty2();

        test("@Monitor function has run", eq(comp.monitorFunctionRunCount, 2));
    }
}

ttest();
return true;
}
