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

// unit testing
import { tsuite, tcase, test, eq } from 'stateManagement/utest/lib/testFramework'

const NumberTypeValue = Type.of(1 as Number);
const BooleanTypeValue = Type.of(true as Boolean);
const StringTypeValue = Type.of("hello" as String);



/*
@Observe class ClassA {
  @Track propA : stirng
  @Track propB : number

constructor(propA: string = 'name', propB: number = 35) {
  ...
}
}
*/

export class ClassA implements IObservedObject, IWatchSubscriberRegister {

    constructor(propA: string = 'name', propB: number = 35) {
        // init in constructor
        // need to change to _backing,
        // otherwise compiler warns about uninitialized
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
        stateMgmtConsole.log(`ClassD: get @Track propA`);
        this.conditionalAddRef(this.__meta_propA);
        return this.__backing_propA
    }
    public set propA(newValue: string) {
        if (this.__backing_propA !== newValue) {
            stateMgmtConsole.log(`ClassD: set @Track propA`);
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
        stateMgmtConsole.log(`ClassD: get @Track propB`);
        this.conditionalAddRef(this.__meta_propB);
        return this.__backing_propB;
    }
    public set propB(newValue: number) {
        stateMgmtConsole.log(`ClassD: set @Track propB`);
        if (this.__backing_propB !== newValue) {
            this.__backing_propB = newValue;
            this.__meta_propB.fireChange();
            this.executeOnSubscribingWatches("propB");
        }
    }
}


// following 1 lines just for test
export let linkChildComp: LinkChildComponent | null = null;

/*
ETS
@Component struct ParentComponent {
@State stateA : ClassA = new ClassA()
build() {
   LinkChildComponent({ linkA: this.stateA })
 }
}

@Component struct LinkChildComponent {
    @Link linkA : ClassA
    build() {
    ChildComponent({ linkA: this.linkA }
    ProvideConsumeAsSourceChildComponent( linkOfProvideConsume: this._backing_provideA })
    }
}
*/

// UI plugin generate
export interface ParentComponent_init_update_struct {
    // @State optional to init from parent, not allowed to update
    stateA?: ClassA;
    provideA?: number;
}

export class ParentComponent extends ExtendableComponent {
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
        stateMgmtConsole.log(`onStateAChanged: @State @Watch stateA func exec: '${propertyName} newValue ${this.stateA}'`)
        this.watchFuncRunCtrA++;
    };

    public watchFuncProvideRunCtr: number = 0;
    onProvideAChanged(propertyName: string): void {
        stateMgmtConsole.log(`onProvideAChanged: Parent component @Provide @Watch provideA func exec: '${propertyName}' newValue '${this.provideA}'`)
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
        linkChildComp = new LinkChildComponent(this, { linkA: this._backing_stateA })
        linkChildComp!.build();
    }
}

export interface LinkChildComponent_init_update_struct {
    // for @Link pass the reference to the StateDecoratedVariable (or other supported DecoratedVariable sub class)
    // to the child @Component. There is a StateMgmtFactory.makeLink factory function defined for each of the
    // supported source classes of @Link
    linkA: LinkSourcesType<ClassA>
}

export class LinkChildComponent extends ExtendableComponent {
    // @Link linkA : ClassA;
    private _backing_linkA: ILinkDecoratedVariable<ClassA>;
    get linkA(): ClassA {
        return this._backing_linkA.get();
    }
    set linkA(newValue: ClassA) {
        this._backing_linkA.set(newValue);
    }

    constructor(parent: ExtendableComponent | null, param: LinkChildComponent_init_update_struct) {
        super(parent)
        const watchFunc: WatchFuncType = (propName: string) => { this.onLinkAChanged(propName) };

        // @Link getter and setter must be included in param for init from Paremt
        // see ChildComponent_init_struct
        this._backing_linkA = StateMgmtFactory.makeLink<ClassA>(
            this, "linkA", param.linkA, watchFunc)
    }

    update_struct(param: LinkChildComponent_init_update_struct) {
        // @Link never update from parent to child @Component
        // uses read and write through approach instead
    }
    public watchFuncRunLinkA: number = 0;
    onLinkAChanged(propertyName: string): void {
        stateMgmtConsole.log(`LinkChildComponent.onLinkAChanged: @Link LinkA @Watch exec: ${propertyName}, newValue ${this.linkA}`)
        this.watchFuncRunLinkA++;
    };

    // build is fake, just for testing
    build() {
    }
}

export function run_link1(): Boolean {

    const tests = tsuite("@Link tests #1", () => {
        const parent = new ParentComponent(null, {});
        parent.build();

        if (!linkChildComp) {
            throw new Error("LinkChildComponent not initialized");
        }

        tcase('Test 1: LinkA assignment and verify @Link, @ObjectLink and state sync', () => {
            // reset counters
            parent.watchFuncRunCtrA = 0;
            linkChildComp!.watchFuncRunLinkA = 0

            linkChildComp!.linkA = new ClassA('name1', 9);
            // linkChildComp!.linkA.propB = 11;

            test(`@Link set parent @state correctly: parent.stateA.propB`, eq(parent.stateA.propB, 9));
            test(`on property change: parent @watch func watchFuncRunCtrA executed`, eq(parent.watchFuncRunCtrA, 1));

            test(`on property change: Child @Link @Watch func executed once`, eq(linkChildComp!.watchFuncRunLinkA, 1));
        });

        tcase('Test 2: State / Link source object property change, test @Watch', () => {
            // reset counters
            parent.watchFuncRunCtrA = 0;
            linkChildComp!.watchFuncRunLinkA = 0

            parent.stateA.propA = "state / link source changed value";
            test(`@Link value changed: of linkChildComp!.linkA.propA value changed`, eq(linkChildComp?.linkA.propA, "state / link source changed value"));
            test(`@Link source, i.e. parent.stateA.propA, value change by link`, eq(parent.stateA.propA, "state / link source changed value"));

            test(`@Observe obj property changed in source: parent @watch func watchFuncRunCtrA executed once`, eq(parent.watchFuncRunCtrA, 1));
            test(`@Observe obj property change in source: Child @Link @Watch func executed once`, eq(linkChildComp!.watchFuncRunLinkA, 1));
        });


        tcase('Test 3: LinkA object property change, test @Watch', () => {
            // reset counters
            parent.watchFuncRunCtrA = 0;
            linkChildComp!.watchFuncRunLinkA = 0

            linkChildComp!.linkA.propA = "link changed value";
            test(`childComp1!.linkA.propA value changed`, eq(linkChildComp?.linkA.propA, "link changed value"));
            test(`@Link source, i.e. parent.stateA.propA, value change by link`, eq(parent.stateA.propA, "link changed value"));
            test(`@Observe obj property change in link: parent @watch func watchFuncRunCtrA executed once`, eq(parent.watchFuncRunCtrA, 1));
            test(`@Observe obj property change: Child @Link @Watch func executed once`, eq(linkChildComp!.watchFuncRunLinkA, 1));
        });

        tcase('Test 4: Assign new stateA and observe Watch triggers, then change properties of newly assigned object', () => {
            stateMgmtConsole.log(`Assigning to stateA. Expect fireChange and Watch trigger on both linkA and stateA.`);
            // reset counters
            parent.watchFuncRunCtrA = 0;
            linkChildComp!.watchFuncRunLinkA = 0

            parent.stateA = new ClassA('name2', 9);

            test(`parent @Watch watchFuncRunCtrA executed: ${parent.watchFuncRunCtrA}`, eq(parent.watchFuncRunCtrA, 1));
            test(`parent.stateA.propB: == 9`, eq(parent.stateA.propB, 9));
            test(`Child @Watch executed once`, eq(linkChildComp!.watchFuncRunLinkA, 1));


            // reset counters
            parent.watchFuncRunCtrA = 0;
            linkChildComp!.watchFuncRunLinkA = 0

            // prop change on newly assigned object
            linkChildComp!.linkA.propA = "link changed prop value";
            parent.stateA.propB += 1;
            test(`@Observe obj property change in link: parent @watch func watchFuncRunCtrA executed once`, eq(parent.watchFuncRunCtrA, 2));
            test(`@Observe obj property change: Child @Link @Watch func executed once`, eq(linkChildComp!.watchFuncRunLinkA, 2));
        });

        tcase('Test 5: Read does not trigger @Watch', () => {
            // reset counters
            parent.watchFuncRunCtrA = 0;
            linkChildComp!.watchFuncRunLinkA = 0

            // just a read must not trigger an 
            stateMgmtConsole.log(`Result: parent.stateA.propA - ${parent.stateA.propA}, childComp.linkA.propA - ${linkChildComp!.linkA.propA}`);

            test(`parent @Watch watchFuncRunCtrA did not exec triggered by read ${parent.watchFuncRunCtrA} == 2`, eq(parent.watchFuncRunCtrA, 0));
            test(`Child @Watch did not exec`, eq(linkChildComp!.watchFuncRunLinkA, 0));
        });
    });

    tests();
    return true;

}
