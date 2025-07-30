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
import { ISubscribedWatches, WatchIdType, WatchFuncType } from 'stateManagement/interface/iWatch'
import { IMutableStateMeta } from 'stateManagement/interface/iMutableStateMeta'
import { stateMgmtConsole } from 'stateManagement/tools/stateMgmtConsoleTrace';
import { StateMgmtFactory } from 'stateManagement/interface/iStateMgmtFactory'
import { IStateDecoratedVariable, IPropRefDecoratedVariable } from 'stateManagement/interface/iDecorators'
import { AppStorage } from 'stateManagement/storages/appStorage.ets';

// unit testing
import { tsuite, tcase, test, eq, not_eq } from 'stateManagement/utest/lib/testFramework'
import { int32 } from '../../mock/env_mock.ets'

let childComp: ChildComponent | null = null ;

export class ClassA implements IObservedObject {

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

    // @State stateA: ClassA = new ClassA("name1", 100);
    private _backing_stateA: IStateDecoratedVariable<ClassA>;
    // @State statePrice: number = 100;
    private _backing_statePrice: IStateDecoratedVariable<number>;

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

    get statePrice(): number {
        stateMgmtConsole.debug(`EntryComponent, statePrice get`);
        return this._backing_statePrice!.get();
    }
    set statePrice(newValue: number) {
        stateMgmtConsole.debug(`EntryComponent, statePrice set`);
        this._backing_statePrice!.set(newValue);
    }


    constructor(parent : ExtendableComponent | null, param : EntryComponent_init_update_struct) {
        super(parent);

      this._backing_stateA = StateMgmtFactory.makeState<ClassA>(
        this,
        "stateA",
        param.stateA !== undefined
        ? param.stateA!
        :  new ClassA("name1", 100)
      );

      this._backing_statePrice = StateMgmtFactory.makeState<number>(
        this,
        "localPrice",
        100
      );
    }

    __updateStruct(param: EntryComponent_init_update_struct) : void {
        // @State nothing, can not update from parent
    }

    incrPropB() {
      this.stateA.propB += 1;
    }

    changeName() {
      this.stateA.propA = this.stateA.propA+'_A'
    }

    assignNewA() {
      this.stateA = new ClassA("newObject", 1101)
    }

    setNewPrice(num : number) {
      this.statePrice = num;
    }

    build() {
        childComp = new ChildComponent(this, {
            propA: () => this.stateA,
            propPrice: () => this.statePrice,
        })
    }
}


interface ChildComponent_init_update_struct {
    propA?: () => ClassA
    propPrice?: () => number
}

// @Component struct ChildComponent
class ChildComponent extends ExtendableComponent{

    // @PropRef propPrice: number = 50;
    private _backing_propPrice: IPropRefDecoratedVariable<number>;
    get propPrice(): int32 {
        console.log(`ChildComponent, propPrice get ${this._backing_propPrice.get()}`);
        return this._backing_propPrice!.get();
    }
    set propPrice(newValue: int32) {
        console.log(`ChildComponent, propPrice set ${newValue}`)
        this._backing_propPrice!.set(newValue);
    }

    // @Required @PropRef propA: ClassA;  // no local value
    private _backing_propA: IPropRefDecoratedVariable<ClassA>;
    get propA(): ClassA {
        console.log("ChildComponent, propA get")
        return this._backing_propA.get();
    }
    set propA(newValue: ClassA) {
        console.log("ChildComponent, propA set")
        this._backing_propA!.set(newValue);
    }

    public watchFuncRunCtr: number = 0;
    // @Watch for propA
    onPropChanged(propName: string): void {
        this.watchFuncRunCtr++;
        stateMgmtConsole.debug(`@Watch function onPropChanged executed for '${propName}', counter value ${this.watchFuncRunCtr}`);
    }

    constructor(parent : ExtendableComponent | null, param: ChildComponent_init_update_struct) {
        super(parent);

        const watchFunc: WatchFuncType =  (propName: string) => { this.onPropChanged(propName) };

        this._backing_propA = StateMgmtFactory.makePropRef<ClassA>(
            this,
            "propA",
            param.propA as (() => ClassA),
            watchFunc
        )

        this._backing_propPrice = StateMgmtFactory.makePropRef<number>(
            this,
            "propPrice",
            param.propPrice ? param.propPrice as (() => number) : 50 as number
        );
    }

    assignNew() {
        this.propA = new ClassA("newObjectProp", -4);
    }
    updateValue() {
        this.propA.propB += 200;
    }
    updatePrice() {
        this.propPrice += 1000;
    }

    update_struct(param: ChildComponent_init_update_struct) {
        console.log(`### ChildComponent update_struct`);
        if (param.propA !== undefined) {
            this._backing_propA.update(param.propA!());
        }
        if (param.propPrice !== undefined) {
            this._backing_propPrice.update(param.propPrice!());
        }
    }
}

export function run_prop() : Boolean {

  const tests = tsuite("@PropRef  tests", () => {
    stateMgmtConsole.log(`run @PropRef  tests=======================`);

    const compA = new EntryComponent(null, {});

    tcase("Test 1: @PropRef init values", () => {
        compA.build();
        test(`compA.stateA.propA = ${compA.stateA.propA} === 'name1'`, eq(compA.stateA.propA,'name1'));
        test(`childComp.propA.propA = ${childComp!.propA.propA} === 'name1'`, eq(childComp!.propA.propA,'name1'));
        test(`compA.statePrice = ${compA.statePrice} === 100`, eq(compA.statePrice,100));
        test(`childComp.propPrice = ${childComp!.propPrice} === 100`, eq(childComp!.propPrice,100));
    })

    tcase("Test 2: @State change object property value ", () => {
        childComp!.watchFuncRunCtr = 0;
        compA.incrPropB();
        childComp!.update_struct({ propA: () => compA.stateA });
        test(`compA.stateA.propB = ${compA.stateA.propB} === 101`,  eq(compA.stateA.propB,101));
        test(`childComp.propA.propB = ${childComp!.propA.propB} === 101`, eq(childComp!.propA.propB,101));
        test(`child @ProRef @Watch function exec on parent to child update (test 2a)`, eq(childComp!.watchFuncRunCtr, 1));

        childComp!.watchFuncRunCtr = 0;
        compA.changeName();
        childComp!.update_struct({ propA: () => compA.stateA });
        test(`compA.stateA.propA = ${compA.stateA.propA} === 'name1_A'`, eq(compA.stateA.propA,'name1_A'));
        test(`childComp.propA.propA = ${childComp!.propA.propA} === 'name1_A'`, eq(childComp!.propA.propA,'name1_A'));
        test(`child @ProRef @Watch function exec on parent to child update (test 2b)`, eq(childComp!.watchFuncRunCtr, 1));
    })

    tcase("Test 3: @PropRef update object property ", () => {
        childComp!.watchFuncRunCtr = 0;
        childComp!.updateValue();   // DOES affect compA, shared reference!
        test(`compA.stateA.propB = ${compA.stateA.propB} === 301`, eq(compA.stateA.propB,301));
        test(`childComp.propA.propB = ${childComp!.propA.propB} === 301`, eq(childComp!.propA.propB,301));
        test(`child @ProRef @Watch function exec on parent to child update (test 3)`, eq(childComp!.watchFuncRunCtr, 1));
    })

    tcase("Test 4: @State assign new object", () => {
        childComp!.watchFuncRunCtr = 0;
        compA.assignNewA();
        childComp!.update_struct({ propA: () => compA.stateA });
        test(`compA.stateA.propA = ${compA.stateA.propA} === 'newObject'`, eq(compA.stateA.propA,'newObject'));
        test(`childComp.propA.propA = ${childComp!.propA.propA} === 'newObject'`, eq(childComp!.propA.propA,'newObject'));
        test(`childComp.propA.propB = ${childComp!.propA.propB} === 1101`, eq(childComp!.propA.propB,1101));
        test(`child @ProRef @Watch function exec on parent to child update (test 4)`, eq(childComp!.watchFuncRunCtr, 1));
    })

    tcase("Test 5: @PropRef assign new object", () => {
        childComp!.watchFuncRunCtr = 0;
        childComp!.assignNew();     // does not affect compA!
        test(`compA.stateA.propA = ${compA.stateA.propA} === 'newObject'`, eq(compA.stateA.propA, 'newObject'));
        test(`compA.stateA.propB = ${compA.stateA.propB} === 1101`, eq(compA.stateA.propB, 1101));
        test(`childComp.propA.propA = ${childComp!.propA.propA} === 'newObjectProp'`, eq(childComp!.propA.propA,'newObjectProp'));
        test(`childComp.propA.propA = ${childComp!.propA.propB} === -4`, eq(childComp!.propA.propB, -4));
        test(`@Watch function executed once upon local obs object assignment (test 5)`, eq(childComp!.watchFuncRunCtr, 1));
    })
    
    tcase("Test 6: @PropRef increment object value ", () => {
        childComp!.watchFuncRunCtr = 0;
        childComp!.updateValue();   // property change, does not affect compA!
        test(`compA.stateA.propB = ${compA.stateA.propB} === 1101`,  eq(compA.stateA.propB,1101));
        test(`childComp.propA.propB = ${childComp!.propA.propB} === 196`, eq(childComp!.propA.propB,196));
        test(`@Watch function executed once upon local obs object property change (test 6)`, eq(childComp!.watchFuncRunCtr, 1));
    })

    tcase("Test 7: @State increment object value ", () => {
        childComp!.watchFuncRunCtr = 0;
        compA.incrPropB();          // @PropRef source change overwrites child @PropRef local value!
        childComp!.update_struct({ propA: () => compA.stateA });
        test(`compA.stateA.propB = ${compA.stateA.propB} === 1102`,  eq(compA.stateA.propB,1102));
        test(`childComp.propA.propB = ${childComp!.propA.propB} === 1102`, eq(childComp!.propA.propB,1102));
        test(`@Watch function executed once upon obs object assignment from parent (test 7)`, eq(childComp!.watchFuncRunCtr, 1));
    })


    tcase("Test 8: @State assign global object ", () => {
    const globalClassA =  new ClassA("global ClassA", 4444);

        childComp!.watchFuncRunCtr = 0;

        compA.stateA = globalClassA     // @PropRef source change overwrites child @PropRef local value
        childComp!.update_struct({ propA: () => compA.stateA });
        test(`compA.stateA.propB = ${compA.stateA.propB} === 4444`,  eq(compA.stateA.propB, 4444));
        test(`childComp.propA.propB = ${childComp!.propA.propB} === 4444`, eq(childComp!.propA.propB, 4444));
        test(`@Watch function executed once upon obs object assignment from parent (test 8a)`, eq(childComp!.watchFuncRunCtr, 1));

        childComp!.watchFuncRunCtr = 0;
        compA.assignNewA();   // @PropRef source change overwrites child @PropRef local value
        childComp!.update_struct({ propA: () => compA.stateA });
        test(`changed compA.stateA.propB = ${compA.stateA.propB} === 1101`,  eq(compA.stateA.propB, 1101));
        test(`changed childComp.propA.propB = ${childComp!.propA.propB} === 1101`, eq(childComp!.propA.propB, 1101));
        test(`@Watch function executed once upon obs object assignment from parent (test 8b)`, eq(childComp!.watchFuncRunCtr, 1));

        childComp!.watchFuncRunCtr = 0;
        globalClassA.propB = 5555;
        test(`global obs object does not affect: unchanged compA.stateA.propB = ${compA.stateA.propB} === 1101`,  eq(compA.stateA.propB, 1101));
        test(`global obs object does not affect: unchanged childComp.propA.propB = ${childComp!.propA.propB} === 1101`, eq(childComp!.propA.propB, 1101));
        test(`@Watch function NOT exec, no connection to earlier obs obj. (test 8c)`, eq(childComp!.watchFuncRunCtr, 0));

    })

    tcase("Test 10: @PropRef increment simple value ", () => {
        childComp!.updatePrice();
        test(`compA.statePrice = ${compA.statePrice} === 100`,  eq(compA.statePrice,100));
        test(`childComp.propPrice = ${childComp!.propPrice} === 1100`, eq(childComp!.propPrice,1100));
    })

    tcase("Test 11: @State increment simple value ", () => {
        compA.setNewPrice(150);
        childComp!.update_struct({ propPrice: () => compA.statePrice });
        test(`compA.statePrice = ${compA.statePrice} === 150`,  eq(compA.statePrice,150));
        test(`childComp.propPrice = ${childComp!.propPrice} === 150`, eq(childComp!.propPrice,150));
    })

    tcase("Cleanup AppStorage") {
            // delete all properties
            AppStorage.keys().forEach(key => {
                const sp = AppStorage.__getStoragePropUnsafe<NullishType>(key)
                test(`__getStoragePropUnsafe gets ${key}`, not_eq(sp, undefined));
                if (sp) {
                    sp.__unregisterAllWatches();
                }
                const success = AppStorage.delete(key);
                test(`Able to delete property ${key} from AppStorage`, success);
            });
            test(`No properties left in AppStorage keys returns [${AppStorage.keys()}]`, !AppStorage.keys().length);
            const canClear = AppStorage.clear();
            test("AppStorage.clear succeeds", eq(canClear, true));
        }
  });

  tests();
  return true;

}
