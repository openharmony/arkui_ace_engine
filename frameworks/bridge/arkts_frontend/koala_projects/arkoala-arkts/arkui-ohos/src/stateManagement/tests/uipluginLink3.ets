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
import { IStateDecoratedVariable, ILinkDecoratedVariable, IObjectLinkDecoratedVariable, LinkSourcesType } from 'stateManagement/interface/iDecorators'
import { IProvideDecoratedVariable, IConsumeDecoratedVariable } from 'stateManagement/interface/iDecorators'
import { ClassA } from 'stateManagement/utest/uiPlugin/uipluginLink1.ets'


// unit testing
import { tsuite, tcase, test, eq } from 'stateManagement/utest/lib/testFramework'
import { StateTracker } from 'stateManagement/utest/lib/stateTracker'

const NumberTypeValue = Type.of(1 as Number);
const BooleanTypeValue = Type.of(true as Boolean);
const StringTypeValue = Type.of("hello" as String);


// following  lines just for test
let childComp1: ChildComponent | null = null;
let childComponentOfObjectLinkComp: ChildComponent | null = null;
let provideConsumeAsSourceChildComponent: ProvideConsumeAsSourceChildComponent | null = null;
let childComp4: ProvideConsumeAsSourceChildComponent | null = null;
let objectLinkChildComp: ObjectLinkChildComponent | null = null;
let linkOfLinkChildComp: LinkOfLinkChildComponent | null = null;

/*
ETS
@Component struct ParentComponent {
@State stateA : ClassA = new ClassA()
build() {
   ChildComponent({ linkA: this.stateA })
   ProvideConsumeAsSourceChildComponent( linkOfProvideConsume: this._backing_provideA })
   ObjectLinkChildComponent ({ olA : this.stateA })
 }
}

@Component struct ChildComponent {
    @Link linkA : ClassA
    build() {
    ChildComponent({ linkA: this.linkA }
    ProvideConsumeAsSourceChildComponent( linkOfProvideConsume: this._backing_provideA })
    }
}

@Component struct LinkOfLinkChildComponent {
    @Link linkA : ClassA
    build() {
    ....
    }}
}

@Component struct ObjectLinkChildComponent {
    @Objectlink olA : ClassA
    build() {
        ChildComponent({ linkA: this.olA }
    }
}
*/

// UI plugin generate
interface ParentComponent_init_update_struct {
    // @State optional to init from parent, not allowed to update
    stateA?: ClassA;
    provideA?: number;
}

class ParentComponent extends ExtendableComponent {
    // @State stateA: ClassA = new ClassA();
    private _backing_stateA: IStateDecoratedVariable<ClassA>;
    get stateA(): ClassA {
        return this._backing_stateA.get();
    }
    set stateA(newValue: ClassA) {
        this._backing_stateA.set(newValue);
    }

    private _backing_provideA: IProvideDecoratedVariable<number>;
    get provideA(): number {
        return this._backing_provideA.get();
    }
    set provideA(newValue: number) {
        this._backing_provideA.set(newValue);
    }

    public watchFuncRunCtrA: number = 0;
    onStateAChanged(propertyName: string): void {
        stateMgmtConsole.log(`ParentComponent.onStateAChanged: @State @Watch stateA func exec: '${propertyName} newValue ${this.stateA}'`)
        this.watchFuncRunCtrA++;
    };

    public watchFuncProvideRunCtr: number = 0;
    onProvideAChanged(propertyName: string): void {
        stateMgmtConsole.log(`ParentComponent.onProvideAChanged: Parent component @Provide @Watch provideA func exec: '${propertyName}' newValue '${this.provideA}'`)
        this.watchFuncProvideRunCtr++;
    };

    constructor(parent: ExtendableComponent | null, param: ParentComponent_init_update_struct) {
        super(parent);
        // automatically convert  @Watch("onStateAChanged") to this:
        // or inline if the compiler improves to support inline
        const watchFunc: WatchFuncType = (propName: string) => { this.onStateAChanged(propName) };
        const watchFuncProvide: WatchFuncType = (propName: string) => { this.onProvideAChanged(propName) };

        // @State optional to init from parent
        // must check if defined, the following is WRONG
        // because can not differentiate btw undefiend value
        // and param.stateA not defined
        this._backing_stateA = StateMgmtFactory.makeState<ClassA>(
            this,
            "stateA",
            (param.stateA !== undefined)
                ? param!.stateA as ClassA // compiler bug: "!" and as not required
                : new ClassA(),
            watchFunc);

        this._backing_provideA = StateMgmtFactory.makeProvide<number>(
            this,
            "provideA",
            "provideA", // alias
            (param.provideA !== undefined)
                ? param!.provideA as number
                : 8,
            NumberTypeValue,
            false, // allowOverride
            watchFuncProvide);
    }

    update_struct(param: ParentComponent_init_update_struct) {
    }

    // build is fake, just for testing
    build() {
        // ETS: ChildComponent({ linkA: this.stateA })
        childComp1 = new ChildComponent(this, { linkA: this._backing_stateA })
        provideConsumeAsSourceChildComponent = new ProvideConsumeAsSourceChildComponent(this, { linkOfProvideConsume: this._backing_provideA })
        childComp1!.build();
        provideConsumeAsSourceChildComponent!.build();
        objectLinkChildComp = new ObjectLinkChildComponent(this, { objectLinkA: this.stateA })
        objectLinkChildComp!.build();
    }
}

interface ChildComponent_init_update_struct {
    // for @Link pass the reference to the StateDecoratedVariable (or other supported DecoratedVariable sub class)
    // to the child @Component. There is a StateMgmtFactory.makeLink factory function defined for each of the
    // supported source classes of @Link
    linkA: LinkSourcesType<ClassA>
}

interface ProvideConsumeAsASourceForLinkChildComponent_init_update_struct {

    linkOfProvideConsume: LinkSourcesType<number>
}

class ProvideConsumeAsSourceChildComponent extends ExtendableComponent {

    private _backing_linkOfProvide: ILinkDecoratedVariable<number>;
    get linkOfProvideConsume(): number {
        return this._backing_linkOfProvide.get();
    }
    set linkOfProvideConsume(newValue: number) {
        this._backing_linkOfProvide.set(newValue);
    }

    constructor(parent: ExtendableComponent | null, param: ProvideConsumeAsASourceForLinkChildComponent_init_update_struct) {
        super(parent)
        const watchFuncLinkOfProvide: WatchFuncType = (propName: string) => { this.onLinkOfProvideChanged(propName) };

        this._backing_linkOfProvide = StateMgmtFactory.makeLink<number>(
            this, "linkOfProvideConsume", param.linkOfProvideConsume, watchFuncLinkOfProvide)
    }

    update_struct(param: ProvideConsumeAsASourceForLinkChildComponent_init_update_struct) {
        // @Link never update from parent to child @Component
        // uses read and write through approach instead
    }
    public watchFuncRunCnt: number = 0;
    onLinkOfProvideChanged(propertyName: string): void {
        stateMgmtConsole.log(`ProvideConsumeAsSourceChildComponent.onLinkOfProvideChanged: @Link source is @Provider @Watch func exec: ${propertyName}, newValue ${this.linkOfProvideConsume}`)
        this.watchFuncRunCnt++;
    };

    // build is fake, just for testing
    build() {

    }
}
class ChildComponent extends ExtendableComponent {
    // @Link linkA : ClassA;
    private _backing_linkA: ILinkDecoratedVariable<ClassA>;
    get linkA(): ClassA {
        return this._backing_linkA.get();
    }
    set linkA(newValue: ClassA) {
        this._backing_linkA.set(newValue);
    }

    private _backing_provideA: IConsumeDecoratedVariable<number>;

    get provideA(): number {
        return this._backing_provideA.get();
    }

    set provideA(newValue: number) {
        this._backing_provideA.set(newValue);
    }

    constructor(parent: ExtendableComponent | null, param: ChildComponent_init_update_struct) {
        super(parent)
        const watchFunc: WatchFuncType = (propName: string) => { this.onLinkAChanged(propName) };
        const watchFuncConsume: WatchFuncType = (propName: string) => { this.onConsumeAChanged(propName) };

        // @Link getter and setter must be included in param for init from Paremt
        // see ChildComponent_init_struct
        this._backing_linkA = StateMgmtFactory.makeLink<ClassA>(
            this, "linkA", param.linkA, watchFunc)

        this._backing_provideA = StateMgmtFactory.makeConsume<number>(
            this,
            "provideA",
            "provideA", // alias
            100,
            NumberTypeValue,  // type of the @Consume property
            watchFuncConsume);
    }

    update_struct(param: ChildComponent_init_update_struct) {
        // @Link never update from parent to child @Component
        // uses read and write through approach instead
    }
    public watchFuncRunLinkA: number = 0;
    onLinkAChanged(propertyName: string): void {
        stateMgmtConsole.log(`ChildComponent.onLinkAChanged: @Link LinkA @Watch exec: ${propertyName}, newValue ${this.linkA}`)
        this.watchFuncRunLinkA++;
    };

    public watchFuncRunCtrProvideA: number = 0;
    onConsumeAChanged(propertyName: string): void {
        stateMgmtConsole.log(`ChildComponent.onConsumeAChanged: @Link @Consume @Watch exec: ${propertyName}, newValue ${this.provideA}`)
        this.watchFuncRunCtrProvideA++;
    };

    // build is fake, just for testing
    build() {
        linkOfLinkChildComp = new LinkOfLinkChildComponent(this, { linkA: this._backing_linkA })
        childComp4 = new ProvideConsumeAsSourceChildComponent(this, { linkOfProvideConsume: this._backing_provideA })
    }
}

interface LinkOfLinkChildComponent_init_update_struct {
    // for @Link pass the reference to the StateDecoratedVariable (or other supported DecoratedVariable sub class)
    // to the child @Component. There is a StateMgmtFactory.makeLink factory function defined for each of the
    // supported source classes of @Link
    linkA: LinkSourcesType<ClassA>
}
// @Component struct ChildComponent
class LinkOfLinkChildComponent extends ExtendableComponent {
    // @Link linkA : ClassA;
    private _backing_linkA: ILinkDecoratedVariable<ClassA>;
    get linkA(): ClassA {
        return this._backing_linkA.get();
    }

    set linkA(newValue: ClassA) {
        this._backing_linkA.set(newValue);
    }

    constructor(parent: ExtendableComponent | null, param: LinkOfLinkChildComponent_init_update_struct) {
        super(parent)
        const watchFunc: WatchFuncType = (propName: string) => { this.onLinkAChanged(propName) };

        // @Link getter and setter must be included in param for init from Paremt
        // see ChildComponent_init_struct
        this._backing_linkA = StateMgmtFactory.makeLink<ClassA>(
            this, "linkA", param.linkA, watchFunc)
    }

    update_struct(param: LinkOfLinkChildComponent_init_update_struct) {
        // @Link never update from parent to child @Component
        // uses read and write through approach instead
    }
    public watchFuncRunLinkOfLinkA: number = 0;
    onLinkAChanged(propertyName: string): void {
        stateMgmtConsole.log(`LinkOfLinkChildComponent.onLinkAChanged @Watch exec: ${propertyName}, newValue ${this.linkA}`)
        this.watchFuncRunLinkOfLinkA++;
    };
}

interface ObjectLinkOLChildComponent_init_update_struct {
    objectLinkA: ClassA
}

// @Component struct ChildComponent
class ObjectLinkChildComponent extends ExtendableComponent {
    // @ObjectLink linkA : number;
    public /* public for testing, should be private */_backing_objectlinkA: IObjectLinkDecoratedVariable<ClassA>;
    get objectlinkA(): ClassA {
        return this._backing_objectlinkA.get();
    }
    // no setter

    constructor(parent: ExtendableComponent | null, param: ObjectLinkOLChildComponent_init_update_struct) {
        super(parent)
        const watchFunc: WatchFuncType = (propName: string) => { this.onLinkAChanged(propName) };

        this._backing_objectlinkA = StateMgmtFactory.makeObjectLink<ClassA>(
            this, "objectlinkA", param.objectLinkA, watchFunc)
    }

    update_struct(param: ObjectLinkOLChildComponent_init_update_struct) {
        // @Link never update from parent to child @Component
        // uses read and write through approach instead
        this._backing_objectlinkA.update(param.objectLinkA)
    }

    public watchFuncRunLinkoLA: number = 0;
    onLinkAChanged(propertyName: string): void {
        stateMgmtConsole.log(`ObjectLinkChildComponent.onLinkAChanged @Objectlink objectlinkA @Watch exec: ${propertyName}, newValue ${this.objectlinkA}`)
        this.watchFuncRunLinkoLA++;
    };

    build() {
        // create a @Link from immutable @ObjectLink source
        childComponentOfObjectLinkComp = new ChildComponent(this, { linkA: this._backing_objectlinkA })
    }
}

export function run_link3(): Boolean {

    const tests = tsuite("@Link tests #3 (various sources for a @Link", () => {
        stateMgmtConsole.log(`run @Link and @ObjectLink tests =======================`);

        const parent = new ParentComponent(null, {});
        parent.build();

        if (!childComp1 ||
            !childComponentOfObjectLinkComp ||
            !provideConsumeAsSourceChildComponent ||
            !childComp4 ||
            !objectLinkChildComp ||
            !linkOfLinkChildComp) {
            throw new Error("Child components not initialized");
        }

        tcase('Test 1: LinkA assignment and verify @Link, @ObjectLink and state sync', () => {
            // reset counters
            parent.watchFuncRunCtrA = 0;
            childComp1!.watchFuncRunLinkA = 0
            objectLinkChildComp!.watchFuncRunLinkoLA = 0;
            childComp1!.linkA.propB = 11;

            test(`@Link set parent @state correctly: parent.stateA.propB`, eq(parent.stateA.propB, 11));
            test(`on property change: parent @watch func watchFuncRunCtrA executed`, eq(parent.watchFuncRunCtrA, 1));

            test(`on property change: Child @Link @Watch func executed once`, eq(childComp1!.watchFuncRunLinkA, 1));

            // simulate @State to @ObjectLink update
            objectLinkChildComp!._backing_objectlinkA.update(parent.stateA);
            test(`Child OL @Watch exec once`, eq(objectLinkChildComp!.watchFuncRunLinkoLA, 1));
            test(`@Link on @ObjectLink value set correctly`, eq(childComp1!.linkA.propB, 11));
            test(`Child @Link on @ObjectLink @Watch did exec`, eq(childComponentOfObjectLinkComp!.watchFuncRunLinkA, 1));
        });

        // tcase('Test 2: State / Link source object property change, test @Watch', () => {
        //     // reset counters
        //     parent.watchFuncRunCtrA = 0;
        //     childComp1!.watchFuncRunLinkA = 0
        //     objectLinkChildComp!.watchFuncRunLinkoLA = 0;
        //     childComponentOfObjectLinkComp!.watchFuncRunLinkA = 0;

        //     parent.stateA.propA = "state / link source changed value";
        //     test(`childComp1!.linkA.propA value changed`, eq(childComp1?.linkA.propA, "state / link source changed value"));
        //     test(`@Link source, i.e. parent.stateA.propA, value change by link`, eq(parent.stateA.propA, "state / link source changed value"));
        //     test(`@Observe obj property changed in source: parent @watch func watchFuncRunCtrA executed once`, eq(parent.watchFuncRunCtrA, 1));
        //     test(`@Observe obj property change in source: Child @Link @Watch func executed once`, eq(childComp1!.watchFuncRunLinkA, 1));
        //     test(`OLChild @Watch exec once caused by shared object prop change`, eq(objectLinkChildComp!.watchFuncRunLinkoLA, 1));
        //     test(`Child @Link on @ObjectLink @Watch exec once caused by shared object prop change`, eq(childComponentOfObjectLinkComp!.watchFuncRunLinkA, 1));
        // });


        // tcase('Test 3: LinkA object property change, test @Watch', () => {
        //     // reset counters
        //     parent.watchFuncRunCtrA = 0;
        //     childComp1!.watchFuncRunLinkA = 0
        //     objectLinkChildComp!.watchFuncRunLinkoLA = 0;
        //     childComponentOfObjectLinkComp!.watchFuncRunLinkA = 0;

        //     childComp1!.linkA.propA = "link changed value";
        //     test(`childComp1!.linkA.propA value changed`, eq(childComp1?.linkA.propA, "link changed value"));
        //     test(`@Link source, i.e. parent.stateA.propA, value change by link`, eq(parent.stateA.propA, "link changed value"));
        //     test(`@Observe obj property change in link: parent @watch func watchFuncRunCtrA executed once`, eq(parent.watchFuncRunCtrA, 1));
        //     test(`@Observe obj property change: Child @Link @Watch func executed once`, eq(childComp1!.watchFuncRunLinkA, 1));
        //     test(`OLChild @Watch exec once caused by shared object prop change`, eq(objectLinkChildComp!.watchFuncRunLinkoLA, 1));
        //     test(`Child @Link on @ObjectLink @Watch exec once caused by shared object prop change`, eq(childComponentOfObjectLinkComp!.watchFuncRunLinkA, 1));
        // });

        // tcase('Test 4: Assign new stateA and observe Watch triggers', () => {
        //     stateMgmtConsole.log(`Assigning to stateA. Expect fireChange and Watch trigger on both linkA and stateA.`);
        //     // reset counters
        //     parent.watchFuncRunCtrA = 0;
        //     childComp1!.watchFuncRunLinkA = 0
        //     objectLinkChildComp!.watchFuncRunLinkoLA = 0;
        //     childComponentOfObjectLinkComp!.watchFuncRunLinkA = 0;

        //     parent.stateA = new ClassA('name2', 9);
        //     // simulate @State to @ObjectLink update
        //     objectLinkChildComp!._backing_objectlinkA.update(parent.stateA);

        //     test(`parent @Watch watchFuncRunCtrA executed: ${parent.watchFuncRunCtrA}`, eq(parent.watchFuncRunCtrA, 1));
        //     test(`parent.stateA.propB: == 9`, eq(parent.stateA.propB, 9));
        //     test(`Child @Watch executed: ${childComp1!.watchFuncRunLinkA}`, eq(childComp1!.watchFuncRunLinkA, 1));
        //     test(`OLChild @Watch exec once caused by update`, eq(objectLinkChildComp!.watchFuncRunLinkoLA, 1));
        //     test(`Child @Link on @ObjectLink @Watch exec once`, eq(childComponentOfObjectLinkComp!.watchFuncRunLinkA, 1));
        // });

        // tcase('Test 5: Read does not trigger @Watch', () => {
        //     // reset counters
        //     parent.watchFuncRunCtrA = 0;
        //     childComp1!.watchFuncRunLinkA = 0
        //     objectLinkChildComp!.watchFuncRunLinkoLA = 0;
        //     childComponentOfObjectLinkComp!.watchFuncRunLinkA = 0;

        //     // just a read must not trigger an 
        //     stateMgmtConsole.log(`Result: parent.stateA.propA - ${parent.stateA.propA}, childComp.linkA.propA - ${childComp1!.linkA.propA}`);

        //     test(`parent @Watch watchFuncRunCtrA did not exec triggered by read ${parent.watchFuncRunCtrA} == 2`, eq(parent.watchFuncRunCtrA, 0));
        //     test(`Child @Watch did not exec ${childComp1!.watchFuncRunLinkA} == 3`, eq(childComp1!.watchFuncRunLinkA, 0));
        //     test(`OLChild @Watch did not exec: ${objectLinkChildComp!.watchFuncRunLinkoLA} == 0`, eq(objectLinkChildComp!.watchFuncRunLinkoLA, 0));
        //     test(`Child2 @Watch did not exec ${childComponentOfObjectLinkComp!.watchFuncRunLinkA} == 0`, eq(childComponentOfObjectLinkComp!.watchFuncRunLinkA, 0));
        // });


        // tcase(`Test 6: Link Source is @Provide`, () => {
        //     provideConsumeAsSourceChildComponent!.watchFuncRunCnt = 0;
        //     parent.provideA = 1;
        //     test(`Child @Link source @Provide works: ${provideConsumeAsSourceChildComponent!.linkOfProvideConsume} == 1`, eq(provideConsumeAsSourceChildComponent!.linkOfProvideConsume, 1));
        //     test(`Child @Link source @Provide watch exec once`, eq(provideConsumeAsSourceChildComponent!.watchFuncRunCnt, 1));
        //     provideConsumeAsSourceChildComponent!.watchFuncRunCnt = 0;

        //     parent.provideA = -1;
        //     test(`Child @Link source @Provide works: ${provideConsumeAsSourceChildComponent!.linkOfProvideConsume} == -1`, eq(provideConsumeAsSourceChildComponent!.linkOfProvideConsume, -1));
        //     test(`Child @Link source @Provide watch exec again once`, eq(provideConsumeAsSourceChildComponent!.watchFuncRunCnt, 1));
        // });

        // tcase(`Test 7: Link Source is @Consume`, () => {
        //     childComp4!.watchFuncRunCnt = 0;

        //     parent.provideA = 1;
        //     test(`Child @Link source @Consume works: ${childComp4!.linkOfProvideConsume} == 1`, eq(childComp4!.linkOfProvideConsume, 1));
        //     test(`Child @Link source @Consume watch exec once`, eq(childComp4!.watchFuncRunCnt, 1));

        //     childComp4!.watchFuncRunCnt = 0;
        //     parent.provideA = -1;
        //     test(`Child @Link source @Consume Watch works: ${childComp4!.linkOfProvideConsume} == -1`, eq(childComp4!.linkOfProvideConsume, -1));
        //     test(`Child @Link source @Consume watch exec once again upon 2nd change`, eq(childComp4!.watchFuncRunCnt, 1));
        // });


        // let expectedWatchCount = 0;
        // parent.provideA = -10; // Make sure following loop does update value (i.e is not the same than previously)
        // childComp4!.watchFuncRunCnt = 0;
        // tcase(`Test 8: Link Source is @Consume`, () => {
        //     for (let i = -1; i <= 1; i++) {
        //         parent.provideA = i;
        //         expectedWatchCount++;
        //         test(`@Link @Consume link == ${i}`, eq(childComp4!.linkOfProvideConsume, i));
        //         test(`@Link @Consume watch executes once per assignment, i.e. ${expectedWatchCount}x times`, eq(childComp4!.watchFuncRunCnt, expectedWatchCount));
        //     }
        // });
    });

    tests();
    return true;

}
