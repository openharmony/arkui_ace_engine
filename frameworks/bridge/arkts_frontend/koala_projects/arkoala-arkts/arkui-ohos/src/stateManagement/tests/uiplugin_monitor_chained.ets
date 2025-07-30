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
    // @Local a1: ClassA = new ClassA();
    private _backing_a1: ILocalDecoratedVariable<ClassA>;
    get a1(): ClassA {
        return this._backing_a1.get();
    }
    set a1(newValue: ClassA) {
        this._backing_a1.set(newValue);
    }

    // @Local a2: ClassA = new ClassA();
    private _backing_a2: ILocalDecoratedVariable<ClassA>;
    get a2(): ClassA {
        return this._backing_a2.get();
    }
    set a2(newValue: ClassA) {
        this._backing_a2.set(newValue);
    }

    public monitorFunctionRunCount: number = 0;

    // @Monitor("a1.classB.propB1") onA1Changed(m: IMonitor)
    private _monitor1: IMonitorFunctionDecorator;
    public onA1Changed?: (m: IMonitor) => void;

    // @Monitor("a2.classB.propB1") onA2Changed(m: IMonitor)
    private _monitor2: IMonitorFunctionDecorator;
    public onA2Changed?: (m: IMonitor) => void;

    constructor(parent: ExtendableComponent | null, param: ParentComponent_init_update_struct) {
        super(parent)
        // @Local optional to init from parent
        // must check if defined, the following is WRONG
        // because can not differentiate btw undefiend value 
        // and param.localA not defined
        this._backing_a1 = StateMgmtFactory.makeLocal<ClassA>(
            this,
            "a1",
            /* local init value */ new ClassA());
        
        this._backing_a2 = StateMgmtFactory.makeLocal<ClassA>(
            this,
            "a2",
            /* local init value */ new ClassA());

        // NOTE define Monitors in "wrong" order to see if affects test, should not!
        this._monitor2 = StateMgmtFactory.makeMonitor(new Array<IMonitorPathsInfo>(
            StateMgmtFactory.makeMonitorPath("a2.classB.propB1", () => {
                const result = this.a2.classB.propB1;
                console.log("==== lamda for path a2.classB.propB1, value: ", result);
                return result;
            })
        ), 
            (m: IMonitor) => {
                this.onA2Changed!(m);
            }
        );

        this._monitor1 = StateMgmtFactory.makeMonitor(new Array<IMonitorPathsInfo>(
            StateMgmtFactory.makeMonitorPath("a1.classB.propB1", () => {
                const result = this.a1.classB.propB1;
                console.log("==== lamda for path a1.classB.propB1, value: ", result);
                return result;
            })
        ),
            (m: IMonitor) => {
                this.onA1Changed!(m);
            }
        );
    }
}

export function run_monitor_chained(): boolean {

    const ttest = tsuite("@Monitor chained") {
        let comp: ParentComponent;

    tcase("#1: init ======") {
        comp = new ParentComponent(null, {});
    }

    tcase("#2: change @Tracked property, the first @Monitor changes the second @Tracked property and the second @Monitor fires =====") {

        comp.onA1Changed = (m: IMonitor) => {
            comp.monitorFunctionRunCount += 1;

            test("m.dirty length", eq(m.dirty.length, 1))
            test("m.dirty[0] value", eq(m.dirty[0], "a1.classB.propB1"));

            // mutate the second state
            comp.a2.classB.propB1 = "new too";
        }

        comp.onA2Changed = (m: IMonitor) => {
            test("@Monitor function for a1 has already run", eq(comp.monitorFunctionRunCount, 1));
            comp.monitorFunctionRunCount += 1;

            test("m.dirty length", eq(m.dirty.length, 1))
            test("m.dirty[0] value", eq(m.dirty[0], "a2.classB.propB1"));
        }

        // mutate state e.g. in onclick
        console.log("++++++ assign to comp.a1.classB.propB1")
        comp.a1.classB.propB1 = "new";

        // give framework a chance to respond to value change
        // this will run 
        ObserveSingleton.instance.updateDirty2();

        test("@Monitor function has run twice", eq(comp.monitorFunctionRunCount, 2));
    }
}

ttest();
return true;
}
