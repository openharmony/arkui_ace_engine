import { ArkButton, ArkButtonComponent, ArkColumn, ArkCommonMethodComponent, ArkPageTransitionEnterComponent, ArkPageTransitionExitComponent, ArkStructBase, ArkText, ArkTextComponent, LocalStorage, MutableState, OnChange, animateTo, observableProxy, stateOf } from "@koalaui/arkoala-arkui";
import { registerArkuiEntry } from "@koalaui/arkoala-arkui/ohos.router";
/** @memo:stable */
class ArkCompAComponent extends ArkStructBase<ArkCompAComponent, CompAOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: CompAOptions): void {
        this.__backing_shopBasket = stateOf<Array<number>>(initializers?.shopBasket ?? ([7, 12, 47, 3]), this);
        this.__backing_totalPurchase = stateOf<number>(initializers?.totalPurchase ?? (0), this);
        this.__backing_defArray = stateOf<Array<string>>(initializers?.defArray ?? (['c', 'g', 't', 'z']), this);
        this.__backing_resultTip = stateOf<string>(initializers?.resultTip ?? (''), this);
    }
    private __backing_shopBasket?: MutableState<Array<number>>;
    private get shopBasket(): Array<number> {
        return this.__backing_shopBasket!.value;
    }
    private set shopBasket(value: Array<number>) {
        this.__backing_shopBasket!.value = observableProxy(value);
    }
    private __backing_totalPurchase?: MutableState<number>;
    private get totalPurchase(): number {
        return this.__backing_totalPurchase!.value;
    }
    private set totalPurchase(value: number) {
        this.__backing_totalPurchase!.value = observableProxy(value);
    }
    private __backing_defArray?: MutableState<Array<string>>;
    private get defArray(): Array<string> {
        return this.__backing_defArray!.value;
    }
    private set defArray(value: Array<string>) {
        this.__backing_defArray!.value = observableProxy(value);
    }
    private __backing_resultTip?: MutableState<string>;
    private get resultTip(): string {
        return this.__backing_resultTip!.value;
    }
    private set resultTip(value: string) {
        this.__backing_resultTip!.value = observableProxy(value);
    }
    /** @memo */
    __updateStruct(initializers: CompAOptions | undefined): void {
        OnChange(this.shopBasket, (_: Array<number>) => this.onBasketUpdated("shopBasket"));
        OnChange(this.defArray, (_: Array<string>) => this.onPutItem("defArray"));
    }
    updateTotal(): number {
        let sum = 0;
        this.shopBasket.forEach((i) => { sum += i; });
        this.totalPurchase = (sum < 100) ? sum : 0.9 * sum;
        return this.totalPurchase;
    }
    onBasketUpdated(propName: string): void {
        animateTo({ duration: 1000 }, () => {
            this.updateTotal();
        });
    }
    updateTip(): string {
        let tempArray = this.defArray.slice(0, -1);
        let addItem = this.defArray[this.defArray.length - 1];
        this.resultTip = tempArray.includes(addItem) ?
            'add item invalid' :
            'congratulations! add item success';
        return this.resultTip;
    }
    onPutItem(propName: string): void {
        this.updateTip();
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: CompAOptions) {
        ArkColumn(__builder, () => {
            ArkButton((__instance: ArkButtonComponent) => {
                __instance.onClick(() => {
                    this.shopBasket.push(Math.round(100 * Math.random()));
                });
            }, undefined, "add to basket");
            ArkText((__instance: ArkTextComponent) => {
                __instance.fontSize(20);
            }, undefined, 'totalPurchase: ' + this.totalPurchase);
            ArkButton((__instance: ArkButtonComponent) => {
                __instance.onClick(() => {
                    let alList = 'abcdefghijklmnopqrstuvwxyz';
                    let ranItem = alList[Math.floor(Math.random() * 26)];
                    this.defArray.push(ranItem);
                });
            }, undefined, "put item");
            ArkText((__instance: ArkTextComponent) => {
                __instance.fontSize(20);
            }, undefined, 'tips: ' + this.resultTip);
        });
    }
}
export {};
/** @memo */
export function CompA(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: CompAOptions): void {
    const updatedInitializers: CompAOptions = {
        __backing_shopBasket: initializers?.__backing_shopBasket,
        __backing_totalPurchase: initializers?.__backing_totalPurchase,
        __backing_defArray: initializers?.__backing_defArray,
        __backing_resultTip: initializers?.__backing_resultTip
    };
    ArkCompAComponent._instantiate(style, () => new ArkCompAComponent, content, updatedInitializers);
}
export interface CompAOptions {
    __backing_shopBasket?: MutableState<Array<number>>;
    shopBasket?: Array<number>;
    __backing_totalPurchase?: MutableState<number>;
    totalPurchase?: number;
    __backing_defArray?: MutableState<Array<string>>;
    defArray?: Array<string>;
    __backing_resultTip?: MutableState<string>;
    resultTip?: string;
}
registerArkuiEntry(CompA, "@watch");
export const __Entry = CompA;
