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
import { WrappedArray } from 'stateManagement/base/observeWrappedArray'
import { IObservedObject, RenderIdType } from 'stateManagement/interface/iObservedObject'
import { WatchIdType } from 'stateManagement/interface/iWatch'
import { IMutableStateMeta } from 'stateManagement/interface/iMutableStateMeta'
import { stateMgmtConsole } from 'stateManagement/tools/stateMgmtConsoleTrace';
import { StateMgmtFactory } from 'stateManagement/interface/iStateMgmtFactory'
import { IStateDecoratedVariable } from 'stateManagement/interface/iDecorators'
import { ILocalDecoratedVariable } from 'stateManagement/interface/iDecorators'
import { IParamV2DecoratedVariable } from 'stateManagement/interface/iDecorators'
import { IComputedDecoratedVariable } from 'stateManagement/interface/iComputedDecorator.ets'
import { ObserveSingleton } from 'stateManagement/base/observeSingleton.ets';

import { UIUtilsPlugin, UIUtils } from '../../sdk/uiutils.ets';

// unit testing
import { tsuite, tcase, test, eq } from 'stateManagement/utest/lib/testFramework'
import { int32 } from '../../mock/env_mock.ets'

/*
https://gitee.com/openharmony/docs/blob/master/en/application-dev/quick-start/arkts-new-Computed.md#computed-decorated-properties-initialize-param
@ObservedV2
class Article {
  @Trace quantity: number = 0;
  unitPrice: number = 0;

  constructor(quantity: number, unitPrice: number) {
    this.quantity = quantity;
    this.unitPrice = unitPrice;
  }
}
*/


export class Article implements IObservedObject {
    private ____V1RenderId: RenderIdType = 0;
    public setV1RenderId(renderId: RenderIdType): void {
        this.____V1RenderId = renderId;
    }
    public addWatchSubscriber(watchId: WatchIdType): void {
    }
    public removeWatchSubscriber(watchId: WatchIdType): boolean {
        return false;
    }

    private readonly __meta: IMutableStateMeta = StateMgmtFactory.makeMutableStateMeta();

    unitPrice: number = 0;
    private __backing_quantity:  number;

    public get quantity(): number {
        this.__meta.addRef();
        return this.__backing_quantity;
    }

    public set quantity(newValue: number) {
        if (this.__backing_quantity !== newValue) {
            this.__backing_quantity = newValue;
            this.__meta.fireChange();
        }
    }

    constructor(quantity: number, unitPrice: number) {
        this.quantity = quantity;
        this.unitPrice = unitPrice;
      }
}


/*
@Entry
@ComponentV2
struct IndexComputedParams {
  @Local shoppingBasket: Article[] = [new Article(1, 20), new Article(5, 2)];

  @Computed
  get total(): number {
    return this.shoppingBasket.reduce((acc: number, item: Article) => acc + (item.quantity * item.unitPrice), 0);
  }

  @Computed
  get qualifiesForDiscount(): boolean {
    return this.total >= 100;
  }

  build() {
    Column() {
      Text(`Shopping List: `).fontSize(30)
      ForEach(this.shoppingBasket, (item: Article) => {
        Row() {
          Text(`unitPrice: ${item.unitPrice}`)
          Button('-').onClick(() => {
            if (item.quantity > 0) {
              item.quantity--;
            }
          })
          Text(`quantity: ${item.quantity}`)
          Button('+').onClick(() => {
            item.quantity++;
          })
        }

        Divider()
      })
      Child({ total: this.total, qualifiesForDiscount: this.qualifiesForDiscount })
    }.alignItems(HorizontalAlign.Start)
  }
}
*/

interface IndexComputedParamsComponent_init_update_struct {
    shoppingBasket?: Array<Article>
}

export class IndexComputedParamsComponent extends ExtendableComponent {
    private ____V1RenderId: RenderIdType = 0;
    public setV1RenderId(renderId: RenderIdType): void {
        this.____V1RenderId = renderId;
    }
    public addWatchSubscriber(watchId: WatchIdType): void {
    }
    public removeWatchSubscriber(watchId: WatchIdType): boolean {
        return false;
    }

    // Expose for testing purposes
    childComp : ChildComponent | undefined = undefined

    // IObservedObject interface
    // @JsonIgnore

    //@Local shoppingBasket: Article[] = [new Article(1, 20), new Article(5, 2)];
    private _backing_shoppingBasket: ILocalDecoratedVariable<WrappedArray<Article>>;
    get shoppingBasket(): Array<Article> {
        return this._backing_shoppingBasket!.get();
    }
    set shoppingBasket(newValue: Array<Article>) {
        this._backing_shoppingBasket!.set(UIUtilsPlugin.makeObservedArray(newValue)! as WrappedArray<Article>);
    }

    /**
     * @Computed generated code:
     */
    /*
    @Computed
    get total(): number {
      return this.shoppingBasket.reduce((acc: number, item: Article) => acc + (item.quantity * item.unitPrice), 0);
    }
    */

    private _computed_total : IComputedDecoratedVariable<number>;
    get total(): number {
        return this._computed_total.get()
    }

    /*
    @Computed
    get qualifiesForDiscount(): boolean {
      return this.total >= 100;
    }
    */
    private _computed_qualifiesForDiscount : IComputedDecoratedVariable<boolean>;
    get qualifiesForDiscount(): boolean {
        return this._computed_qualifiesForDiscount.get()
    }
 
    constructor(parent : ExtendableComponent | null,
        param : IndexComputedParamsComponent_init_update_struct) {
        super(parent);
        /**
         * First step: we initialize state variables
         */
        this._backing_shoppingBasket = StateMgmtFactory.makeLocal<WrappedArray<Article>>(
            this,
            "shoppingBasket",
            UIUtilsPlugin.makeObservedArray(
              new Array<Article>(new Article(1, 20), new Article(5, 2))) as WrappedArray<Article>
        );

        /**
         * Second step: we initialize computed
         */
        this._computed_total = StateMgmtFactory.makeComputedVariable<number>(
            () : number => {
                return this.shoppingBasket.reduce((acc: number, item: Article) => {
                    return acc + (item.quantity * item.unitPrice)
                }, 0);
            },
            "total"
        )
        this._computed_qualifiesForDiscount = StateMgmtFactory.makeComputedVariable<boolean>(
            () : boolean => {
                return this.total >= 100;
            },
            "qualifiesForDiscount"
        )
    }

    build() {
        this.childComp = new ChildComponent(this,
            { total: this.total, qualifiesForDiscount: this.qualifiesForDiscount })
    }
}


/*
@ComponentV2
struct Child {
  @Param total: number = 0;
  @Param qualifiesForDiscount: boolean = false;

  build() {
    Row() {
      Text(`Total: ${this.total} `).fontSize(30)
      Text(`Discount: ${this.qualifiesForDiscount} `).fontSize(30)
    }
  }
}
*/


interface ChildComponent_init_update_struct {
    total: number
    qualifiesForDiscount: boolean
}

// @Component struct ChildComponent
class ChildComponent extends ExtendableComponent{

    private _backing_total: IParamV2DecoratedVariable<number>;
    private _backing_qualifiesForDiscount: IParamV2DecoratedVariable<boolean>;

    get total(): int32 {
        return this._backing_total!.get();
    }

    get qualifiesForDiscount(): boolean {
        return this._backing_qualifiesForDiscount!.get();
    }

    constructor(parent : ExtendableComponent | null, param: ChildComponent_init_update_struct) {
        super(parent);
        // @Param can init from parent, can have local value;
        this._backing_total = StateMgmtFactory.makeParamV2<number>(
            this,
            "total",
            param.total
        );

        this._backing_qualifiesForDiscount = StateMgmtFactory.makeParamV2<boolean>(
            this,
            "qualifiesForDiscount",
            param.qualifiesForDiscount
        );
    }

    update_struct(param: ChildComponent_init_update_struct) {
        this._backing_total.update(param.total);
        this._backing_qualifiesForDiscount.update(param.qualifiesForDiscount);
    }
}


export function run_computed_params() : Boolean {
    const tests = tsuite("@Computed params", () => {

    tcase("Test 1: @Computed param", () => {
        let indexComponent = new IndexComputedParamsComponent(null, {})
        indexComponent.build()
        test(`total = ${indexComponent.total} `, indexComponent.total === 30);
        test(`total = ${indexComponent.qualifiesForDiscount} `, indexComponent.qualifiesForDiscount === false);
        indexComponent.shoppingBasket[0].quantity = 2
        ObserveSingleton.instance.updateDirty2()
        test(`total = ${indexComponent.total} `, indexComponent.total === 50);
        test(`total = ${indexComponent.qualifiesForDiscount} `, indexComponent.qualifiesForDiscount === false);
        indexComponent.shoppingBasket[1].quantity = 70
        ObserveSingleton.instance.updateDirty2()
        test(`total = ${indexComponent.total} `, indexComponent.total === 180);
        test(`total = ${indexComponent.qualifiesForDiscount} `, indexComponent.qualifiesForDiscount === true);
    })

    });

    tests();
    return true;
}
