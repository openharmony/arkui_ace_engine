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

import { ExtendableComponent } from 'stateManagement/base/extendableComponent'
import { IObservedObject, RenderIdType } from 'stateManagement/interface/iObservedObject'
import { Observe } from 'stateManagement/interface/iObserve'
import { IWatchSubscriberRegister, ISubscribedWatches, WatchIdType, WatchFuncType } from 'stateManagement/interface/iWatch'
import { IMutableStateMeta } from 'stateManagement/interface/iMutableStateMeta'
import { stateMgmtConsole } from 'stateManagement/tools/stateMgmtConsoleTrace';
import { StateMgmtFactory } from 'stateManagement/interface/iStateMgmtFactory'
import { IStateDecoratedVariable, IPropRefDecoratedVariable } from 'stateManagement/interface/iDecorators'
import { WrappedArray } from 'stateManagement/base/observeWrappedArray'

// unit testing
import { tsuite, tcase, test, eq } from 'stateManagement/utest/lib/testFramework'
import { int32 } from '../../mock/env_mock.ets'

let childComp: ChildComponent | null = null;

export class ClassA implements IObservedObject, IWatchSubscriberRegister {

    constructor(propA: string, propB: number) {
        // init in constructor
        // need to change to _backing,
        // otherwise compiler warns about uninitialized
        // __backing
        this.__backing_propA = propA;
        this.__backing_propB = propB;
    }

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
        this.subscribedWatches_.executeOnSubscribingWatches(changedPropName);
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

    // @Track name : string;
    // @JsonRename("name")
    private __backing_propA: string;

    // @JsonIgnore
    private readonly __meta_propA: IMutableStateMeta
        = StateMgmtFactory.makeMutableStateMeta();

    public get propA(): string {
        stateMgmtConsole.log(`ClassA: get @Track propA`);
        this.conditionalAddRef(this.__meta_propA);
        return this.__backing_propA
    }
    public set propA(newValue: string) {
        if (this.__backing_propA !== newValue) {
            stateMgmtConsole.log(`ClassA: set @Track propA`);
            this.__backing_propA = newValue;
            this.__meta_propA.fireChange();
            this.executeOnSubscribingWatches("propA");
        }
    }

    // @Track propD2 : number;
    // @JsonRename("propD2")
    private __backing_propB: number;

    // @JsonIgnore
    private readonly __meta_propB: IMutableStateMeta
        = StateMgmtFactory.makeMutableStateMeta();

    public get propB(): number {
        stateMgmtConsole.log(`ClassA: get @Track propB`);
        this.conditionalAddRef(this.__meta_propB);
        return this.__backing_propB;
    }
    public set propB(newValue: number) {
        stateMgmtConsole.log(`ClassA: set @Track propB`);
        if (this.__backing_propB !== newValue) {
            this.__backing_propB = newValue;
            this.__meta_propB.fireChange();
            this.executeOnSubscribingWatches("propB");
        }
    }
}

interface EntryComponent_init_update_struct {
    stateA?: ClassA
    statePrice?: number
}

class EntryComponent extends ExtendableComponent {

    // @State stateA: ClassA = new ClassA("name1", 1000);
    private _backing_stateA: IStateDecoratedVariable<ClassA>;
    // @State stateNum: number = 100;
    private _backing_stateNum: IStateDecoratedVariable<number>;
    // @State condition: boolean = false;
    private _backing_condition: IStateDecoratedVariable<boolean>;
    // @State arr: Array<number> = new Array<number>(1,2,3);
    private _backing_arr: IStateDecoratedVariable<WrappedArray<number>>;

    get stateA(): ClassA {
        stateMgmtConsole.debug(`EntryComponent, stateA get`);
        const ret = this._backing_stateA!.get();
        stateMgmtConsole.debug(`EntryComponent, stateA get`);
        return ret;
    }
    set stateA(newValue: ClassA) {
        stateMgmtConsole.debug(`EntryComponent, stateA set`);
        this._backing_stateA!.set(newValue);
    }

    get stateNum(): number {
        stateMgmtConsole.debug(`EntryComponent, stateNum get`);
        return this._backing_stateNum!.get();
    }
    set stateNum(newValue: number) {
        stateMgmtConsole.debug(`EntryComponent, stateNum set`);
        this._backing_stateNum!.set(newValue);
    }

    get condition(): boolean {
        stateMgmtConsole.debug(`EntryComponent, condition get`);
        return this._backing_condition!.get();
    }
    set condition(newValue: boolean) {
        stateMgmtConsole.debug(`EntryComponent, condition set`);
        this._backing_condition!.set(newValue);
    }

    get arr(): Array<number> {
        stateMgmtConsole.debug(`EntryComponent, arr get`);
        return this._backing_arr!.get();
    }
    set arr(newValue: Array<number>) {
        stateMgmtConsole.debug(`EntryComponent, arr set`);
        this._backing_arr!.set(new WrappedArray<number>(newValue));
    }

    constructor(parent : ExtendableComponent | null, param : EntryComponent_init_update_struct) {
        super(parent);

      this._backing_stateA = StateMgmtFactory.makeState<ClassA>(
        this,
        "stateA",
        param.stateA !== undefined
        ? param.stateA!
        :  new ClassA("name1", 1000)
      );

      this._backing_stateNum = StateMgmtFactory.makeState<number>(
        this,
        "stateNum",
        100
      );

      this._backing_condition = StateMgmtFactory.makeState<boolean>(
        this,
        "condition",
        false
      );

      this._backing_arr = StateMgmtFactory.makeState<WrappedArray<number>>(
        this,
        "arr",
        new WrappedArray<number>(new Array<number>(1,2,3))
      );
    }

    __updateStruct(param: EntryComponent_init_update_struct) : void {
        // @State nothing, can not update from parent
    }

    incrPropB() {
      this.stateA.propB += 1;
    }

    // For testing logic!
    build(buildStruct: ChildComponent_init_update_struct) {
        childComp = new ChildComponent(this, buildStruct);
    }

    func(): number {
        return this.stateA.propB;
    }
}


interface ChildComponent_init_update_struct {
    prop?: () => number;
}

// @Component struct ChildComponent
class ChildComponent extends ExtendableComponent{

    // @PropRef prop: number = 3;
    private _backing_prop: IPropRefDecoratedVariable<number>;
    get prop(): int32 {
        console.log(`ChildComponent, prop get ${this._backing_prop.get()}`);
        return this._backing_prop!.get();
    }
    set prop(newValue: int32) {
        console.log(`ChildComponent, prop set ${newValue}`)
        this._backing_prop!.set(newValue);
    }

    public watchFuncRunCtr: number = 0;
    // @Watch for prop
    onPropChanged(propName: string): void {
        this.watchFuncRunCtr++;
        stateMgmtConsole.debug(`@Watch function executed for '${propName}', counter value ${this.watchFuncRunCtr}`);
    }

    constructor(parent : ExtendableComponent | null, param: ChildComponent_init_update_struct) {
        super(parent);

        const watchFunc: WatchFuncType =  (propName: string) => { this.onPropChanged(propName) };

        this._backing_prop = StateMgmtFactory.makePropRef<number>(
            this,
            "prop",
            (param.prop !== undefined) ? param.prop as (() => number) : (3 as number),
            watchFunc
        );
    }

    update_struct(param: ChildComponent_init_update_struct) {
        console.log(`### ChildComponent update_struct`);
        if (param.prop !== undefined) {
            this._backing_prop.update(param.prop!());
        }
    }
}

export function run_prop_special() : Boolean {

  const tests = tsuite("@PropRef special cases", () => {
    stateMgmtConsole.log(`run @PropRef special cases =======================`);

    const compA = new EntryComponent(null, {});
    
    tcase("Test 1: Child({ prop: this.func() })", () => {
        compA.build({ prop: () => compA.func() });
        test(`childComp.prop = ${childComp!.prop} === 1000`, eq(childComp!.prop,1000));

        compA.incrPropB();
        childComp?.update_struct({ prop: () => compA.func() });
        test(`childComp.prop = ${childComp!.prop} === 1001`, eq(childComp!.prop,1001));
    })

    tcase("Test 2: Child({ prop: this.condition ? 1 : this.stateNum })", () => {
        compA.build({ prop: () => { return compA.condition ? 1 : compA.stateNum } });
        test(`childComp.prop = ${childComp!.prop} === 100`, eq(childComp!.prop,100));

        compA.stateNum++;
        childComp?.update_struct({ prop: () => { return compA.condition ? 1 : compA.stateNum } });
        test(`childComp.prop = ${childComp!.prop} === 101`, eq(childComp!.prop,101));

        compA.condition = !compA.condition;
        childComp?.update_struct({ prop: () => { return compA.condition ? 1 : compA.stateNum } });
        test(`childComp.prop = ${childComp!.prop} === 1`, eq(childComp!.prop,1));

        compA.stateNum++;
        childComp?.update_struct({ prop: () => { return compA.condition ? 1 : compA.stateNum } });
        test(`childComp.prop = ${childComp!.prop} === 1`, eq(childComp!.prop,1));
    })

    tcase("Test 3: Child({ prop: 11 })", () => {
        compA.build({ prop: () => 11 as number });
        test(`childComp.prop = ${childComp!.prop} === 11`, eq(childComp!.prop,11));

        compA.stateNum++;
        childComp?.update_struct({ prop: () => 11 as number });
        test(`childComp.prop = ${childComp!.prop} === 11`, eq(childComp!.prop,11));
    })

    tcase("Test 4: Child({ prop: this.stateA.propB })", () => {
        compA.build({ prop: () => compA.stateA.propB });
        test(`childComp.prop = ${childComp!.prop} === 1001`, eq(childComp!.prop,1001));

        compA.stateA.propB++;
        childComp?.update_struct({ prop: () => compA.stateA.propB });
        test(`childComp.prop = ${childComp!.prop} === 1002`, eq(childComp!.prop,1002));
    })

    tcase("Test 5: Child({ prop: this.arr[1] })", () => {
        compA.build({ prop: () => compA.arr[1] });
        test(`childComp.prop = ${childComp!.prop} === 2`, eq(childComp!.prop,2));

        compA.arr.push(4);
        childComp?.update_struct({ prop: () => compA.arr[1] });
        test(`childComp.prop = ${childComp!.prop} === 2`, eq(childComp!.prop,2));

        compA.arr[1] = 5;
        childComp?.update_struct({ prop: () => compA.arr[1] });
        test(`childComp.prop = ${childComp!.prop} === 5`, eq(childComp!.prop,5));
    })
    
    tcase("Test 6: Child({})", () => {
        compA.build({});
        test(`childComp.prop = ${childComp!.prop} === 3`, eq(childComp!.prop,3));

        compA.incrPropB();
        childComp?.update_struct({});
        test(`childComp.prop = ${childComp!.prop} === 3`, eq(childComp!.prop,3));
    })

  });

  tests();
  return true;

}
