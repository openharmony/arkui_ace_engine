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
import { ISubscribedWatches, WatchIdType } from 'stateManagement/interface/iWatch'
import { IMutableStateMeta } from 'stateManagement/interface/iMutableStateMeta'
import { stateMgmtConsole } from 'stateManagement/tools/stateMgmtConsoleTrace';
import { StateMgmtFactory } from 'stateManagement/interface/iStateMgmtFactory';
import { IStoragePropRefDecoratedVariable } from 'stateManagement/interface/iDecorators';
import { AppStorage } from 'stateManagement/storages/appStorage.ets';
import { AbstractProperty } from 'stateManagement/storages/abstractProperty.ets';

// unit testing
import { tsuite, tcase, test, eq, not_eq } from 'stateManagement/utest/lib/testFramework';
import { AbstractProperty } from 'stateManagement/storages/abstractProperty.ets'


class ClassA implements IObservedObject {

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
    propA?: ClassA
}

class EntryComponent extends ExtendableComponent {

    // @StoragePropRef("a") propA: ClassA = new ClassA("name1", 100);
    private _backing_propA: IStoragePropRefDecoratedVariable<ClassA>;

    get propA(): ClassA {
        stateMgmtConsole.debug(`EntryComponent, propA get`);
        const ret = this._backing_propA!.get();
        return ret;
    }
    set propA(newValue: ClassA) {
        stateMgmtConsole.debug(`EntryComponent, propA set`);
        this._backing_propA!.set(newValue);
    }

    entryComponentStoragePropRefWatchFuncCount: number = 0;

    entryComponentStoragePropRefWatchFunc(propName: string) {
        this.entryComponentStoragePropRefWatchFuncCount += 1;
        stateMgmtConsole.log(`EntryComponent: entryComponentStoragePropRefWatchFunc counter: ${this.entryComponentStoragePropRefWatchFunc}`);
    }

    constructor(parent: ExtendableComponent | null, param: EntryComponent_init_update_struct) {
        super(parent);

        this._backing_propA = StateMgmtFactory.makeStoragePropRef<ClassA>(
            this,
            "a",
            "propA",
            new ClassA("name1", 100),
            Type.from<ClassA>(),
            this.entryComponentStoragePropRefWatchFunc
        );
    }

    __updateStruct(param: EntryComponent_init_update_struct): void { }

    incrPropB() {
        this.propA.propB += 1;
    }

    resetName() {
        this.propA.propA = this.propA.propA + '_A'
    }

    assignNewA() {
        this.propA = new ClassA("newObject", 1101)
    }
}


export function run_storagePropRef(): Boolean {

    const tests = tsuite("@StoragePropRef  tests", () => {
        stateMgmtConsole.log(`run @StoragePropRef  tests=======================`);

        AppStorage.clear();
        const compA = new EntryComponent(null, {});

        let ref: AbstractProperty<ClassA> | undefined = AppStorage.ref<ClassA>("a", Type.from<ClassA>());

        tcase("Test 1: @StoragePropRef init value in compA and AppStorage", () => {
            test(`compA.propA.propA = ${compA.propA.propA} === 'name1'`, eq(compA.propA.propA, 'name1'));
            test(`compA.propA.propB = ${compA.propA.propB} === 100`, eq(compA!.propA.propB, 100));

            test(`AppStorage.has("a")`, eq(AppStorage.has("a"), true));
            test(`AppStorage.ref<ClassA>("a", Type.from<ClassA>() !== undefined)`, eq((ref !== undefined), true));

            test(`AbstractProperty read @STorageLink property from AppStorage: ref.get().propA = ${ref!.get().propA} === 'name1'`, eq(ref!.get().propA, 'name1'));
            test(`AbstractProperty read @STorageLink property from AppStorage: re.get().propB = ${ref!.get().propB} === 100`, eq(ref!.get().propB, 100));

            test("@StorageLink @Watch was not exec", eq(compA.entryComponentStoragePropRefWatchFuncCount, 0));
        })

        tcase("Test 2: @StoragePropRef change object property value ", () => {
            compA.entryComponentStoragePropRefWatchFuncCount = 0;
            stateMgmtConsole.log("About to change observed object property of @StoragePropRef and AppStorage 'a' key")
            compA.incrPropB();
            test(`compA.propA.propB = ${compA.propA.propB} === 101`, eq(compA.propA.propB, 101));
            test(`AbstractProperty read AppStorage value, property changed: ref.get().propB = ${ref!.get().propB} === 101`, eq(ref!.get().propB, 101));
            test("@StorageLink @Watch exec once (test 2)", eq(compA.entryComponentStoragePropRefWatchFuncCount, 1));
        })

        tcase("Test 3: @StoragePropRef assign new value", () => {
            compA.entryComponentStoragePropRefWatchFuncCount = 0;
            stateMgmtConsole.log("About to assign new object to @StoragePropRef, modifies local value")
            compA.assignNewA();     // does not affect "a" in AppStorage!
            test(`compA.propA.propA = ${compA.propA.propA} === 'newObject'`, eq(compA.propA.propA, 'newObject'));
            test(`compA.propA.propB = ${compA.propA.propB} === 1101`, eq(compA.propA.propB, 1101));
            test(`Verify AppStorage unchanged: ref.get().propA = ${ref!.get().propA} === 'name1'`, eq(ref!.get().propA, 'name1'));
            test(`Verify AppStorage unchanged: ref.get().propB = ${ref!.get().propA} === 101`, eq(ref!.get().propB, 101));
            test("@StorageLink @Watch exec once (test 3)", eq(compA.entryComponentStoragePropRefWatchFuncCount, 1));
        })

        tcase("Test 4: @StoragePropRef change object property value ", () => {
            compA.entryComponentStoragePropRefWatchFuncCount = 0;
            stateMgmtConsole.log("About to change obs object property of @StoragePropRef, modifies local value only")
            compA.incrPropB();      // does not affect "a" in AppStorage!
            test(`@StorageLink local value changed: compA.propA.propB = ${compA.propA.propB} === 1102`, eq(compA.propA.propB, 1102));
            test(`Verify AppStorage unchanged: ref.get().propB = ${ref!.get().propB} === 101`, eq(ref!.get().propB, 101));
            test("@StorageLink @Watch exec once (test 4)", eq(compA.entryComponentStoragePropRefWatchFuncCount, 1));
        })

        tcase("Test 5: AppStorage change object property value, overwritrws @StorageLink local value ", () => {
            compA.entryComponentStoragePropRefWatchFuncCount = 0;
            stateMgmtConsole.log("About to change obs object property in ppStorage, overwrites @StoragePropRef local value")
            ref!.get().propB++;           // DOES overwrite @StoragePropRef!
            test(`@StorageLink value changed: compA.propA.propB = ${compA.propA.propB} === 102`, eq(compA.propA.propB, 102));
            test(`Verify AppStorage unchanged: ref.get().propB = ${ref!.get().propB} === 102`, eq(ref!.get().propB, 102));
            test("@StorageLink @Watch exec once (test 5)", eq(compA.entryComponentStoragePropRefWatchFuncCount, 1));
        })

        tcase("Test 6: AppStorage assign new", () => {
            compA.entryComponentStoragePropRefWatchFuncCount = 0;
            stateMgmtConsole.log("About to assign new obs object AppStorage,  overwrites @StoragePropRef local value");
            AppStorage.set<ClassA>("a", new ClassA("newAP", -4));   // is synced to @StoragePropRef
            test(`@StorageLink value changed: compA.propA.propA = ${compA.propA.propA} === 'newAP'`, eq(compA.propA.propA, 'newAP'));
            test(`@StorageLink value changed: compA.propA.propB = ${compA.propA.propB} === -4`, eq(compA.propA.propB, -4));
            test("@StorageLink @Watch exec once (test 6)", eq(compA.entryComponentStoragePropRefWatchFuncCount, 1));
        })

        tcase("Test 7: AppStorage change object property value ", () => {
            compA.entryComponentStoragePropRefWatchFuncCount = 0;
            stateMgmtConsole.log("About to change obs object property in AppStorage, overwrites @StoragePropRef local value");
            ref!.get().propB++;           // DOES affect @StoragePropRef!
            test(`@StorageLink value changed:  compA.propA.propB = ${compA.propA.propB} === -3`, eq(compA.propA.propB, -3));
            test(`Verify AppStorage changed: ref.get().propB = ${ref!.get().propB} === -3`, eq(ref!.get().propB, -3));
            test("@StorageLink @Watch exec once (test 7)", eq(compA.entryComponentStoragePropRefWatchFuncCount, 1));
        })

        tcase("Test 8: @StoragePropRef update object property, obs object shared with AppStorage ", () => {
            compA.entryComponentStoragePropRefWatchFuncCount = 0;
            stateMgmtConsole.log("About to change  @StoragePropRef update object property, obs object shared with AppStorage");
            compA!.incrPropB();     // affects both
            test(`@StorageLink value changed: compA.propA.propB = ${compA.propA.propB} === -2`, eq(compA.propA.propB, -2));
            test(`Verify AppStorage changed:  ref.get().propB = ${ref!.get().propB} === -2`, eq(ref!.get().propB, -2));
            test("@StorageLink @Watch exec once (test 8)", eq(compA.entryComponentStoragePropRefWatchFuncCount, 1));
        })

        tcase("Test 9 (repeat of test 3): @StoragePropRef assign new value", () => {
            compA.entryComponentStoragePropRefWatchFuncCount = 0;
            stateMgmtConsole.log("About to assign new object to @StoragePropRef, modifies local value, test 9")
            compA.assignNewA();     // does not affect "a" in AppStorage!
            test(`@StorageLink value changed: compA.propA.propA = ${compA.propA.propA} === 'newObject'`, eq(compA.propA.propA, 'newObject'));
            test(`@StorageLink value changed: compA.propA.propB = ${compA.propA.propB} === 1101`, eq(compA.propA.propB, 1101));
            test(`Verify AppStorage unchanged: ref.get().propB = ${ref!.get().propB} === -2`, eq(ref!.get().propB, -2));
            test("@StorageLink @Watch exec once (test 9)", eq(compA.entryComponentStoragePropRefWatchFuncCount, 1));
        })

        tcase("Test 10: Make sure cleanup AppStorage") {
            ref = undefined;
            const sp = AppStorage.__getStoragePropUnsafe<ClassA>("a")
            test("__getStoragePropUnsafe gets used storageProperty", not_eq(sp, undefined));
            if (sp) {
                sp.__unregisterAllWatches();
            }
            const success = AppStorage.delete("a")
            test("Able to delete property 'a' to which @StoragePropRef's connect", success)

            test(`No properties left in AppStorage keys returns [${AppStorage.keys()}]`, !AppStorage.keys().length);
            const canClear = AppStorage.clear();
            test("AppStorage.clear succeeds", eq(canClear, true))
        }
    });

    tests();
    return true;

}
