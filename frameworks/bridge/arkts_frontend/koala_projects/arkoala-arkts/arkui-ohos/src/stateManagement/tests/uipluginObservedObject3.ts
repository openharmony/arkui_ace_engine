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

import { IObservedObject, RenderIdType } from '../decorator'
import { IWatchSubscriberRegister, ISubscribedWatches, WatchIdType } from '../decorator'
import { IMutableStateMeta } from '../decorator'

// unit testing
import { StateTracker } from './lib/stateTracker'
import { tsuite, tcase, test, eq } from './lib/testFramework'
import { ObserveSingleton } from '../base/observeSingleton';
import { STATE_MGMT_FACTORY } from '../decorator'
import { IObservedAnyProp } from '../decorator';
import { GlobalStateManager, MockedElement } from '../mock/env_mock';
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

// Not exported
class ClassA implements IObservedObject, IWatchSubscriberRegister {
    // propA : number (no @Track)
    public propA: number

    // @Track classB : ClassB_SingleMeta
    // @JsonRename("classB")
    private __backing_classB: ClassB_SingleMeta;
    // @JsonIgnore
    private readonly __meta_classB: IMutableStateMeta;

    // @Track classC : ClassC = new ClassC();
    // @JsonRename("classC")
    private __backing_classC: ClassC = new ClassC
    // @JsonIgnore
    private readonly __meta_classC: IMutableStateMeta;

    constructor() {
        // Per-property metas capture `this` as wildcard LSV target so
        // fireChange() routes the owner identity without per-call args.
        this.__meta_classB = StateMgmtFactory.makeMutableStateMeta(this, '__meta_classB');
        this.__meta_classC = StateMgmtFactory.makeMutableStateMeta(this, '__meta_classC');
        this.__backing_classB = new ClassB_SingleMeta();
        this.propA = 8;
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
        if (ObserveSingleton.instance.shouldAddRef(this.____V1RenderId)) {
            meta.addRef();
        }
    }

    public get classB(): ClassB_SingleMeta {
        this.conditionalAddRef(this.__meta_classB);
        return this.__backing_classB;
    }
    public set classB(newValue: ClassB_SingleMeta) {
        stateMgmtConsole.log(`ClassA: set @Track classB`);
        if (this.__backing_classB !== newValue) {
            this.__backing_classB = newValue;
            this.__meta_classB.fireChange();
            this.executeOnSubscribingWatches('classB');
        }
    }

    public get classC(): ClassC {
        stateMgmtConsole.log(`ClassA: get @Track classC`);
        this.conditionalAddRef(this.__meta_classC);
        return this.__backing_classC;
    }
    public set classC(newValue: ClassC) {
        stateMgmtConsole.log(`ClassA: set @Track classC`);
        if (this.__backing_classC !== newValue) {
            this.__backing_classC = newValue;
            this.__meta_classC.fireChange();
            this.executeOnSubscribingWatches('classC');
        }
    }
}

export class ClassA_ObserveAnyProp_NoAnyMeta implements IObservedObject, IWatchSubscriberRegister
    , IObservedAnyProp
{

    // propA : number (no @Track)
    public propA: number

    // @Track classB : ClassB_SingleMeta
    // @JsonRename("classB")
    private __backing_classB: ClassB_ObserveAnyProp;

    // @Track classC : ClassC = new ClassC();
    // @JsonRename("classC")
    private __backing_classC: ClassC = new ClassC

    // @JsonIgnore
    private readonly __meta_classB: IMutableStateMeta;

    // @JsonIgnore
    private readonly __meta_classC: IMutableStateMeta;

    public addRefAnyProp(): void {
        // "Read" all  tracked variables here
        console.log('ClassA_ObserveAnyProp_NoAnyMeta addRefAnyProp');
        this.__meta_classB.addRef();
        this.__meta_classC.addRef();
    }

    constructor() {
        // Per-property metas capture `this` as wildcard LSV target.
        this.__meta_classB = StateMgmtFactory.makeMutableStateMeta(this, '__meta_classB');
        this.__meta_classC = StateMgmtFactory.makeMutableStateMeta(this, '__meta_classC');
        this.__backing_classB = new ClassB_ObserveAnyProp();
        this.propA = 8;
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
        if (ObserveSingleton.instance.shouldAddRef(this.____V1RenderId)) {
            meta.addRef();
        }
    }

    public get classB(): ClassB_ObserveAnyProp {
        console.log('ClassA_ObserveAnyProp_NoAnyMeta(), get classB');
        this.conditionalAddRef(this.__meta_classB);
        return this.__backing_classB;
    }
    public set classB(newValue: ClassB_ObserveAnyProp) {
        stateMgmtConsole.log(`ClassA: set @Track classB`);
        if (this.__backing_classB !== newValue) {
            this.__backing_classB = newValue;
            this.__meta_classB.fireChange();
            this.executeOnSubscribingWatches('classB');
        }
    }

    public get classC(): ClassC {
        stateMgmtConsole.log(`ClassA: get @Track classC`);
        this.conditionalAddRef(this.__meta_classC);
        return this.__backing_classC;
    }
    public set classC(newValue: ClassC) {
        stateMgmtConsole.log(`ClassA: set @Track classC`);
        if (this.__backing_classC !== newValue) {
            this.__backing_classC = newValue;
            this.__meta_classC.fireChange();
            this.executeOnSubscribingWatches('classC');
        }
    }
}

export class ClassB_SingleMeta implements IObservedObject, IWatchSubscriberRegister,
    IObservedAnyProp
{

    constructor() {
        // Pass `this` so the meta captures owner identity as wildcard LSV target.
        this.__meta = StateMgmtFactory.makeMutableStateMeta(this, '__meta');
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
        this.subscribedWatches_.executeOnSubscribingWatches('propE');
    }

    public addRefAnyProp(): void {
        console.log('ClassB_ObserveAnyProp addRefAnyProp');
        this.__meta.addRef();
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
        if (ObserveSingleton.instance.shouldAddRef(this.____V1RenderId)) {
            this.__meta.addRef();
        }
    }

    // @JsonIgnore
    private readonly __meta: IMutableStateMeta;

    // propB1 : string = "BBB111";
    // @JsonRename("classC")
    private __backing_propB1: string = 'BBB111';
    public get propB1(): string {
        this.conditionalAddRef();
        return this.__backing_propB1;
    }
    public set propB1(newValue: string) {
        if (this.__backing_propB1 !== newValue) {
            this.__backing_propB1 = newValue;
            this.__meta.fireChange();
            this.executeOnSubscribingWatches('propB1');
        }
    }

    // propB2 : boolean = false;
    // @JsonRename("classC")
    private __backing_propB2: boolean = false;
    public get propB2(): boolean {
        stateMgmtConsole.log(`ClassB_SingleMeta (@Observe compat): get propB2`);
        this.conditionalAddRef();
        return this.__backing_propB2;
    }
    public set propB2(newValue: boolean) {
        stateMgmtConsole.log(`ClassB_SingleMeta (@Observe compat): set propB2`);
        if (this.__backing_propB2 !== newValue) {
            this.__backing_propB2 = newValue;
            this.__meta.fireChange();
            this.executeOnSubscribingWatches('propB2');
        }
    }
}

// Same as ClassB_SingleMeta, but each @Track property has its own meta and
// the class additionally implements IObservedAnyProp so wildcard monitors can
// bind every per-property meta via addRefAnyProp().
export class ClassB_ObserveAnyProp implements IObservedObject, IWatchSubscriberRegister
    , IObservedAnyProp
{

    // @Watch
    private readonly subscribedWatches_: ISubscribedWatches = StateMgmtFactory.makeSubscribedWatches();

    public addWatchSubscriber(watchId: WatchIdType): void {
        this.subscribedWatches_.addWatchSubscriber(watchId);
    }
    public removeWatchSubscriber(watchId: WatchIdType): boolean {
        return this.subscribedWatches_.removeWatchSubscriber(watchId);
    }
    protected executeOnSubscribingWatches(changedPropName: string): void {
        this.subscribedWatches_.executeOnSubscribingWatches(changedPropName);
    }

    private ____V1RenderId: RenderIdType = 0;
    public setV1RenderId(renderId: RenderIdType): void {
        this.____V1RenderId = renderId;
    }

    protected conditionalAddRef(meta: IMutableStateMeta): void {
        if (ObserveSingleton.instance.shouldAddRef(this.____V1RenderId)) {
            meta.addRef();
        }
    }

    public addRefAnyProp(): void {
        console.log('ClassB_ObserveAnyProp addRefAnyProp');
        this.__meta_propB1.addRef();
        this.__meta_propB2.addRef();
    }

    constructor() {
        // Pass `this` so each per-property meta captures its owner as the
        // wildcard LSV target; fireChange() then routes the owner identity
        // through addDirtyRef without a per-call target argument.
        this.__meta_propB1 = StateMgmtFactory.makeMutableStateMeta(this, '__meta_propB1');
        this.__meta_propB2 = StateMgmtFactory.makeMutableStateMeta(this, '__meta_propB2');
    }

    private readonly __meta_propB1: IMutableStateMeta;

    private readonly __meta_propB2: IMutableStateMeta;

    private __backing_propB1: string = 'BBB111';
    public get propB1(): string {
        this.conditionalAddRef(this.__meta_propB1);
        return this.__backing_propB1;
    }
    public set propB1(newValue: string) {
        if (this.__backing_propB1 !== newValue) {
            this.__backing_propB1 = newValue;
            this.__meta_propB1.fireChange();
            this.executeOnSubscribingWatches('propB1');
        }
    }

    private __backing_propB2: boolean = false;
    public get propB2(): boolean {
        stateMgmtConsole.log(`ClassB_ObserveAnyProp: get propB2`);
        this.conditionalAddRef(this.__meta_propB2);
        return this.__backing_propB2;
    }
    public set propB2(newValue: boolean) {
        stateMgmtConsole.log(`ClassB_ObserveAnyProp: set propB2`);
        if (this.__backing_propB2 !== newValue) {
            this.__backing_propB2 = newValue;
            this.__meta_propB2.fireChange();
            this.executeOnSubscribingWatches('propB2');
        }
    }
}

// non-observed, no change
export class ClassC {
    propC: number = 888;
}

export function run_observed_object3(): Boolean {

    // some quick and dirty way to test if
    // init , read and modify properties works
    const ttest = tsuite('@Observe @Track and @Observe compat, plain class: nested objects') {

        tcase('Test 1: init, read and modify properties') {

            let classA = new ClassA()
            test('read classA.propA - expect 8', eq(classA.propA, 8))
            test('read classA.classB.propB1 - expect BBB111', eq(classA.classB.propB1, 'BBB111'))
            test('read classA.classB.propB2 - expect false', eq(classA.classB.propB2, false))
            test('read classA.classC.propC - expect 888', eq(classA.classC.propC, 888))

            classA.propA += 1;

            classA.classB.propB1 = '****';

            ObserveSingleton.instance.updateDirty();

            test('read classA.propA - expect 9', eq(classA.propA, 9))
            test('read classA.classB.propB1 - expect ****', eq(classA.classB.propB1, '****'))
        }

        tcase('Test 2: Verify AddRef for V1') {

            ObserveSingleton.instance.renderingComponent = ObserveSingleton.RenderingComponentV1;
            // V1 conditionalAddRef requires the object's V1RenderId to match
            // the singleton's renderingId, which the framework reads from
            // GlobalStateManager.instance.currentScope?.id. Mock a scope so
            // that path returns a real id; production sets currentScope
            // during render automatically.
            GlobalStateManager.instance.currentScope = new MockedElement(1);
            let classA = new ClassA()
            classA.setV1RenderId(1);

            StateTracker.reset();
            // Cause addRef
            classA.classB;
            test('Use classA.classB expect 1 add ref for classB', eq(StateTracker.getRefCnt(), 1))
            GlobalStateManager.instance.currentScope = undefined;
        }

        tcase('Test 3: Verify AddRef for V2') {

            ObserveSingleton.instance.renderingComponent = ObserveSingleton.RenderingComponentV2;
            let classA = new ClassA()

            StateTracker.reset();
            // Cause addRef
            classA.classB;
            test('Use classA.classB expect 1 add ref for classB', eq(StateTracker.getRefCnt(), 1))
        }

        tcase('Test 4: Verify 2*AddRef and FireChange for V1') {

            ObserveSingleton.instance.renderingComponent = ObserveSingleton.RenderingComponentV1;
            // Mock the koalaui scope so renderingId resolves to a real id;
            // tag both ClassA and inner ClassB_SingleMeta with that id so
            // the V1 conditionalAddRef paths execute. Tag BEFORE the
            // StateTracker.reset so the assertion only counts the timed
            // addRefs from the intentional test access.
            GlobalStateManager.instance.currentScope = new MockedElement(1);
            let classA = new ClassA()
            classA.setV1RenderId(1);
            classA.classB.setV1RenderId(1);

            StateTracker.reset();
            // Cause addRef
            classA.classB.propB1;
            test('Use classA.classB.probB1 expect 2 add refs. classB and propB1', eq(StateTracker.getRefCnt(), 2))
            // This causes fireChange event
            classA.classB = new ClassB_SingleMeta();
            test('New classA.classB expect fire change', eq(StateTracker.getFireChangeCnt(), 1))
            GlobalStateManager.instance.currentScope = undefined;
        }

        tcase('Test 5: Verify 2*AddRef and FireChange for V2') {

            ObserveSingleton.instance.renderingComponent = ObserveSingleton.RenderingComponentV2;
            let classA = new ClassA()
            StateTracker.reset();
            // Cause addRefs
            classA.classB.propB1;
            test('Use classA.classB.probB1 expect 2 add refs. classB and propB1', eq(StateTracker.getRefCnt(), 2))
            // This causes fireChange event
            classA.classB = new ClassB_SingleMeta();
            test('New classA.classB expect fire change', eq(StateTracker.getFireChangeCnt(), 1))

        }
    }

    ttest();
    return true;
}
