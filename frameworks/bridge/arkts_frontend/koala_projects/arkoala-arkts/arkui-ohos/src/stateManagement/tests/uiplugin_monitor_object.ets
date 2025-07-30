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
import { IWatchSubscriberRegister, ISubscribedWatches, WatchIdType } from 'stateManagement/interface/iWatch'
import { IMutableStateMeta } from 'stateManagement/interface/iMutableStateMeta'
import { IObservedObject, RenderIdType } from 'stateManagement/interface/iObservedObject'
import { Observe } from 'stateManagement/interface/iObserve'
import { ObserveSingleton } from '../../base/observeSingleton.ets';


class ClassA implements IObservedObject, IWatchSubscriberRegister {

    constructor() {
        // init in constructor
        // need to change to _backing, 
        // otherwise compiler warns about uninitialized 
        // __backing
        this.__backing_classB = new ClassB();
        this.propA = 8;

        // @Monitor("classB", "classB.propB1") onBChanged(m: IMonitor)
        this._monitor = 
            StateMgmtFactory.makeMonitor(new Array<IMonitorPathsInfo>(
                StateMgmtFactory.makeMonitorPath("classB", () => {
                    const result = this.classB;
                    console.log("==== lamda for path classB, value: ", result);
                    return result;
                }),
                StateMgmtFactory.makeMonitorPath("classB.propB1", () => {
                    const result = this.classB.propB1;
                    console.log("==== lamda for path classB.propB1, value: ", result);
                    return result;
                })
            ), 
                (m: IMonitor) => {
                    this.onBChanged!(m);
                }
        );
    }

    private _monitor: IMonitorFunctionDecorator;
    public monitorFunctionRunCount: number = 0; // for testing
    public onBChanged?: (m: IMonitor) => void;  // defined by user

    // @Watch
    // Watches firing when this object's property changes
    // @JsonIgnore
    private readonly subscribedWatches_: ISubscribedWatches = StateMgmtFactory.makeSubscribedWatches();

    // implementation of ISubscribedWatches by forwarding to subscribedWatches
    public addWatchSubscriber(watchId: WatchIdType): void {
        this.subscribedWatches_.addWatchSubscriber(watchId);
    }
    public removeWatchSubscriber(watchId: WatchIdType): boolean {
        return this.subscribedWatches_.removeWatchSubscriber(watchId);
    }
    protected executeOnSubscribingWatches(changedPropName: string): void {
        this.subscribedWatches_.executeOnSubscribingWatches("propE");
    }

    // IObservedObject interface
    // @JsonIgnore
    private ____V1RenderId: RenderIdType = 0;
    public setV1RenderId(renderId: RenderIdType): void {
        this.____V1RenderId = renderId;
    }

    // helper
    // do not inline, will not work for 
    // inherited classes.
    protected conditionalAddRef(meta: IMutableStateMeta): void {
        if (Observe.shouldAddRef(this.____V1RenderId)) {
            meta.addRef();
        }
    }

    // @Track classB : ClassB
    //@JsonRename("classB")
    private __backing_classB: ClassB;

    // @JsonIgnore
    private readonly __meta_classB: IMutableStateMeta
        = StateMgmtFactory.makeMutableStateMeta();

    public get classB(): ClassB {
        stateMgmtConsole.log(`ClassA: get @Track classB`);
        this.conditionalAddRef(this.__meta_classB);
        return this.__backing_classB;
    }
    public set classB(newValue: ClassB) {
        stateMgmtConsole.log(`ClassA: set @Track classB`);
        if (this.__backing_classB !== newValue) {
            this.__backing_classB = newValue;
            this.__meta_classB.fireChange();
            this.executeOnSubscribingWatches("classB");
        }
    }

    // @Track classC : ClassC = new ClassC();
    //@JsonRename("classC")
    private __backing_classC: ClassC = new ClassC

    // @JsonIgnore
    private readonly __meta_classC: IMutableStateMeta
        = StateMgmtFactory.makeMutableStateMeta();
    public get classC(): ClassC {
        stateMgmtConsole.log(`ClassA: get @Track classC`);
        this.conditionalAddRef(this.__meta_classC);
        return this.__backing_classC;
    }
    public set classC(newValue: ClassC) {
        stateMgmtConsole.log(`ClassA: set @Track classC`);
        if (this.__backing_classC !== newValue) {
            this.__backing_classC = newValue;
            this.__meta_classB.fireChange();
            this.executeOnSubscribingWatches("classC");
        }
    }

    // propA : number (no @Track)
    public propA: number
}

class ClassB implements IObservedObject, IWatchSubscriberRegister {

    // constructor generated by uiPlugin to create @Monitor
    constructor() {
        // @Monitor("propB1") onPropChanged(m: IMonitor)
        this._monitor = 
            StateMgmtFactory.makeMonitor(new Array<IMonitorPathsInfo>(
                StateMgmtFactory.makeMonitorPath("propB1", () => {
                    const result = this.propB1;
                    console.log("==== lamda for path propB1, value: ", result);
                    return result;
                })
            ), 
            (m: IMonitor) => {
                this.onPropChanged!(m);
            }
        );
    }

    private _monitor: IMonitorFunctionDecorator;
    public onPropChanged?: (m: IMonitor) => void;   // defined by user
    public monitorFunctionRunCount: number = 0;     // for testing

    // @Watch
    // Watches firing when this object's property changes
    // @JsonIgnore
    private readonly subscribedWatches_: ISubscribedWatches = StateMgmtFactory.makeSubscribedWatches();

    // implementation of ISubscribedWatches by forwarding to subscribedWatches
    public addWatchSubscriber(watchId: WatchIdType): void {
        this.subscribedWatches_.addWatchSubscriber(watchId);
    }
    public removeWatchSubscriber(watchId: WatchIdType): boolean {
        return this.subscribedWatches_.removeWatchSubscriber(watchId);
    }
    protected executeOnSubscribingWatches(changedPropName: string): void {
        this.subscribedWatches_.executeOnSubscribingWatches("propE");
    }

    // IObservedObject interface
    // @JsonIgnore
    private ____V1RenderId: RenderIdType = 0;
    public setV1RenderId(renderId: RenderIdType): void {
        this.____V1RenderId = renderId;
    }

    // helper
    // do not inline, will not work for 
    // inherited classes.
    protected conditionalAddRef(): void {
        if (Observe.shouldAddRef(this.____V1RenderId)) {
            this.__meta.addRef();
        }
    }

    // @JsonIgnore
    private readonly __meta: IMutableStateMeta
        = StateMgmtFactory.makeMutableStateMeta();


    // propB1 : string = "BBB111";
    // @JsonRename("classC")
    private __backing_propB1: string = "BBB111";
    public get propB1(): string {
        stateMgmtConsole.log(`ClassB (@Observe compat): get propB1`);
        this.conditionalAddRef();
        return this.__backing_propB1;
    }
    public set propB1(newValue: string) {
        stateMgmtConsole.log(`ClassB (@Observe compat): set propB1`);
        if (this.__backing_propB1 !== newValue) {
            this.__backing_propB1 = newValue;
            this.__meta.fireChange();
            this.executeOnSubscribingWatches("propB1");
        }
    }

    // propB2 : boolean = false;
    // @JsonRename("classC")
    private __backing_propB2: boolean = false;
    public get propB2(): boolean {
        stateMgmtConsole.log(`ClassB (@Observe compat): get propB2`);
        this.conditionalAddRef();
        return this.__backing_propB2;
    }
    public set propB2(newValue: boolean) {
        stateMgmtConsole.log(`ClassB (@Observe compat): set propB2`);
        if (this.__backing_propB2 !== newValue) {
            this.__backing_propB2 = newValue;
            this.__meta.fireChange();
            this.executeOnSubscribingWatches("propB2");
        }
    }
}

// non-observed, no change
class ClassC {
    propC: number = 888;
}

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
    }
}

export function run_monitor_object(): boolean {

    const ttest = tsuite("@Monitor basics") {
        let comp: ParentComponent;

    tcase("#1: init ======") {
        comp = new ParentComponent(null, {});
    }

    tcase("#2: change @Tracked property and verify Monitor function =====") {

        comp.a.classB.onPropChanged = (m: IMonitor) => {
            stateMgmtConsole.debug(`tcase #2 onPropChanged`);

            comp.a.classB.monitorFunctionRunCount += 1;

            test("m.dirty length", eq(m.dirty.length, 1))
            test("m.dirty[0] value", eq(m.dirty[0], "propB1"));
            
            let monitorValue = m.value<string>(Type.of("hello"), "propB1");
            test("m.value<..>(Type.of('hello', propB1)).path", eq(monitorValue!.path, "propB1"));
            test("m.value<..>(Type.of('hello', propB1)).now", eq(monitorValue!.now, "new"));

            let firstDirtyValue = m.value<string>(Type.of("hello"));
            test("m.value<..>(Type.of('hello')).path", eq (firstDirtyValue!.path, "propB1"));
            test("m.value<..>(Type.of('hello')).now", eq (firstDirtyValue!.now, "new"));
        }

        comp.a.onBChanged = (m: IMonitor) => {
            stateMgmtConsole.debug(`tcase #2 onBChanged`);

            comp.a.monitorFunctionRunCount += 1;

            test("m.dirty length", eq(m.dirty.length, 1))
            test("m.dirty[0] value", eq(m.dirty[0], "classB.propB1"));
            
            let monitorValue = m.value<string>(Type.of("hello"), "classB.propB1");
            test("m.value<..>(Type.of('hello', classB.propB1)).path", eq(monitorValue!.path, "classB.propB1"));
            test("m.value<..>(Type.of('hello', classB.propB1)).now", eq(monitorValue!.now, "new"));
        }

        // mutate sate e.g. in onclick
        console.log("++++++ assign to comp.a.classB.propB1")
        comp.a.classB.propB1 = "new";

        // give framework a chance to respond to value change
        // this will run 
        ObserveSingleton.instance.updateDirty2();

        test("ClassB @Monitor function has run", eq(comp.a.classB.monitorFunctionRunCount, 1));
        test("ClassA @Monitor function has run", eq(comp.a.monitorFunctionRunCount, 1));
    }

    tcase("#3: assign new ClassB and verify Monitor function =====") {

        let newInstance: ClassB = new ClassB();

        comp.a.classB.onPropChanged = (m: IMonitor) => {
            test("classB Monitor has run", false);
        }

        comp.a.onBChanged = (m: IMonitor) => {
            stateMgmtConsole.debug(`tcase #3 onBChanged`);

            comp.a.monitorFunctionRunCount += 1;

            test("m.dirty length", eq(m.dirty.length, 2))
            test("m.dirty[0] value", eq(m.dirty[0], "classB"));
            test("m.dirty[1] value", eq(m.dirty[1], "classB.propB1"));
            
            let monitorValue = m.value<ClassB>(Type.of(newInstance), 'classB');
            test("m.value<ClassB>(Type.of(new ClassB()), 'classB').path", eq(monitorValue!.path, "classB"));
            test("m.value<ClassB>(Type.of(new ClassB()), 'classB').now", eq(monitorValue!.now, newInstance));

            let monitorValue2 = m.value<string>(Type.of("hello"), "classB.propB1");
            test("m.value<..>(Type.of('hello', classB.propB1)).path", eq(monitorValue2!.path, "classB.propB1"));
            test("m.value<..>(Type.of('hello', classB.propB1)).now", eq(monitorValue2!.now, "BBB111"));
        }

        // mutate sate e.g. in onclick
        console.log("++++++ assign to comp.a.classB");
        comp.a.classB = newInstance;

        // give framework a chance to respond to value change
        // this will run 
        ObserveSingleton.instance.updateDirty2();

        // note, a.classB is a new instance, monitors never run before!
        test("ClassB @Monitor function has NOT run", eq(comp.a.classB.monitorFunctionRunCount, 0));
        test("ClassA @Monitor function has run", eq(comp.a.monitorFunctionRunCount, 2));
    }

    tcase("#4: assign new ClassA and Monitor DOESN'T fire =====") {

        comp.a.classB.onPropChanged = (m: IMonitor) => {
            test(`tcase #4 onPropChanged`, false);
        }

        // mutate sate e.g. in onclick
        console.log("++++++ assign to comp.a");
        comp.a = new ClassA();

        // give framework a chance to respond to value change
        // this will run 
        ObserveSingleton.instance.updateDirty2();

        // note, a is a new instance, monitors never run before!
        test("ClassA @Monitor function has NOT run", eq(comp.a.monitorFunctionRunCount, 0));
    }
}

ttest();
return true;
}
