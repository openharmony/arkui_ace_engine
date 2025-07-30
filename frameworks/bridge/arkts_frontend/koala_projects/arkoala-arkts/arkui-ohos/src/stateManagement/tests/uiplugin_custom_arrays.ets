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

import { WrappedArray } from 'stateManagement/base/observeWrappedArray.ets'
import { ILocalDecoratedVariable } from 'stateManagement/interface/iDecorators'
import { StateMgmtFactory } from 'stateManagement/interface/iStateMgmtFactory'
import { ExtendableComponent } from 'stateManagement/base/extendableComponent'
import { IMutableStateMeta } from 'stateManagement/interface/iMutableStateMeta'
import { Observe } from 'stateManagement/interface/iObserve'

// unit testing
import { ObserveSingleton } from '../../base/observeSingleton.ets';
import { FactoryInternal } from 'stateManagement//base/iFactoryInternal'
import { TestMSM } from 'stateManagement/utest/lib/testAddRefFireChange'
import { StateTracker } from 'stateManagement/utest/lib/stateTracker'
import { stateMgmtConsole } from 'stateManagement/tools/stateMgmtConsoleTrace';
import { tsuite, tcase, test, eq } from 'stateManagement/utest/lib/testFramework'

/* ETS
@ObservedV2
class MyArray<T> extends Array<T> {
    constructor(...args) {
        super(...args);

        this.arrProp = "test";
    }
    @Trace arrProp: string;

    func() {
        this.reverse();
    }
}

@Entry
@ComponentV2
struct Parent {
    @Local arr: MyArray<number> = new MyArray<number>(1,2,3);

    build() {
        Column() {
            Text(`${this.arr}`).onClick(() => {
                this.arr.func();
            })
            Text(this.arr.arrProp).onClick(() => {
                this.arr.arrProp += "ddd";
            })
        }
    }
}
*/


export class MyArray<T> extends WrappedArray<T> {
    // NOTE to uiplugin:
    // whatever constructor the developer provides, it must be a valid way to
    // construct an Array<T>, so create the Array before passing it on to the WrappedArray!
    constructor(first: T, ...rest: T[]) {
        super(new Array<T>(first, ...rest));
        this.__backing_arrProp = "test";
    }
    // ...could be e.g. constructor() { super(new Array<T>()); } etc.

    // @Trace arrProp: string
    //@JsonRename("arrProp")
    private __backing_arrProp: string;

    // @JsonIgnore
    public readonly __meta_arrProp: IMutableStateMeta = FactoryInternal.makeMutableStateMeta("arrProp");
        //= StateMgmtFactory.makeMutableStateMeta();

    public get arrProp(): string {
        stateMgmtConsole.log(`MyArray: get @Trace arrProp`);
        this.conditionalAddRef(this.__meta_arrProp);
        return this.__backing_arrProp;
    }
    public set arrProp(newValue: string) {
        stateMgmtConsole.log(`MyArray: set @Trace arrProp`);
        if (this.__backing_arrProp !== newValue) {
            this.__backing_arrProp = newValue;
            this.__meta_arrProp.fireChange();
            this.executeOnSubscribingWatches("arrProp");
        }
    }

    // helper
    // do not inline, will not work for inherited classes.
    protected conditionalAddRef(meta: IMutableStateMeta): void {
        if (Observe.shouldAddRef(this.____V1RenderId)) {
            meta.addRef();
        }
    }

    // For testing
    public getFireChangeCnt(): number {
        return TestMSM.getFireChangeCnt(this.__meta_arrProp);
    }
    public getRefCnt() {
        return TestMSM.getRefCnt(this.__meta_arrProp);
    }

    func() {
        this.reverse();
    }
}

// UI plugin generates
interface ParentComponent_init_update_struct {
    arr?: MyArray<number>;
}

class ParentComponent extends ExtendableComponent {
    private _backing_state_arr: ILocalDecoratedVariable<MyArray<number>>;
    get arr(): MyArray<number> {
        return this._backing_state_arr!.get() as MyArray<number>;
    }
    set arr(newArr: MyArray<number>) {
        this._backing_state_arr!.set(newArr);
    }

    // For testing
    public getFireChangeCnt(key:string): number {
        return TestMSM.getFireChangeCnt(this._backing_state_arr.get().meta_, key);
    }
    public getRefCnt(key:string) {
        return TestMSM.getRefCnt(this._backing_state_arr.get().meta_, key);
    }

    constructor(parent: ExtendableComponent | null, param: ParentComponent_init_update_struct) {
        super(parent);

        this._backing_state_arr = StateMgmtFactory.makeLocal<MyArray<number>>(
            this,
            "arr",
            (param.arr !== undefined)
                ? param.arr!
                : new MyArray<number>(1,2,3)
        );
    }
}

export function run_custom_arrays(): boolean {
    const ttest = tsuite("Custom arrays") {

        const comp = new ParentComponent(null, {});
        stateMgmtConsole.log(`=== construct done ===\n`);

        tcase("Read custom array properties while rendering") {
            // rendering
            ObserveSingleton.instance.renderingComponent = ObserveSingleton.RenderingComponentV2;
            ObserveSingleton.instance.renderingId = 5;

            let len = comp.arr.length;
            test("length value", eq(len, 3));
            test("length refCnt", eq(comp.getRefCnt('__OB_LENGTH'), 1));

            let prop = comp.arr.arrProp;
            test("arrProp value", eq(prop, "test"));
            test("arrProp refCnt", eq(comp.arr.getRefCnt(), 1));

            let str = comp.arr.toString();
            test("arr.toString() OB_ANY_INDEX refCnt", eq(comp.getRefCnt('__OB_ANY_INDEX'), 1));

            // stop rendering
            ObserveSingleton.instance.renderingComponent = ObserveSingleton.RenderingNoComponent;
            ObserveSingleton.instance.renderingId = ObserveSingleton.InvalidRenderId;
        }

        tcase("Modify custom array") {
            comp.arr.join();
            test("arr.join() refCnt", eq(comp.getRefCnt('__OB_ANY_INDEX'), 1))

            comp.arr.func();
            test("arr.func() OB_LENGTH refCnt", eq(comp.getFireChangeCnt('__OB_LENGTH'), 1));
            test("arr.func() OB_ANY_INDEX refCnt", eq(comp.getFireChangeCnt('__OB_ANY_INDEX'), 1));
        }
    }

    ttest();
    return true;
}