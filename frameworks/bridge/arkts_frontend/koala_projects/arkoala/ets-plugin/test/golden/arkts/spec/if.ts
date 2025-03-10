import { ArkColumn, ArkCommonMethodComponent, ArkPageTransitionEnterComponent, ArkPageTransitionExitComponent, ArkStructBase, ArkText, stateOf } from "@koalaui/arkts-arkui";
import { MutableState } from "@koalaui/runtime";
import { LocalStorage } from "@koalaui/arkui-common";
import { observableProxy } from "@koalaui/common";
/** @memo:stable */
class ArkIFViewComponent extends ArkStructBase<ArkIFViewComponent, IFViewOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: IFViewOptions): void {
        this.__backing_toggle1 = stateOf<boolean>(initializers?.toggle1 ?? (false), this);
        this.__backing_toggle2 = stateOf<boolean>(initializers?.toggle2 ?? (false), this);
        this.__backing_toggle3 = stateOf<boolean>(initializers?.toggle3 ?? (false), this);
    }
    private __backing_toggle1?: MutableState<boolean>;
    private get toggle1(): boolean {
        return this.__backing_toggle1!.value;
    }
    private set toggle1(value: boolean) {
        this.__backing_toggle1!.value = observableProxy(value);
    }
    private __backing_toggle2?: MutableState<boolean>;
    private get toggle2(): boolean {
        return this.__backing_toggle2!.value;
    }
    private set toggle2(value: boolean) {
        this.__backing_toggle2!.value = observableProxy(value);
    }
    private __backing_toggle3?: MutableState<boolean>;
    private get toggle3(): boolean {
        return this.__backing_toggle3!.value;
    }
    private set toggle3(value: boolean) {
        this.__backing_toggle3!.value = observableProxy(value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: IFViewOptions) {
        ArkColumn(__builder, () => {
            if (this.toggle1) {
                ArkText(undefined, undefined, 'toggle1');
            }
            else if (this.toggle2) {
                ArkText(undefined, undefined, 'toggle2');
            }
            else if (this.toggle3) {
                ArkText(undefined, undefined, 'toggle3');
            }
            else {
                ArkText(undefined, undefined, 'toggle no thing');
            }
            if (this.toggle1) {
                ArkText(undefined, undefined, 'toggle1 Single');
            }
        });
    }
}
export {};
/** @memo */
export function IFView(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: IFViewOptions): void {
    const updatedInitializers: IFViewOptions = {
        __backing_toggle1: initializers?.__backing_toggle1,
        __backing_toggle2: initializers?.__backing_toggle2,
        __backing_toggle3: initializers?.__backing_toggle3
    };
    ArkIFViewComponent._instantiate(style, () => new ArkIFViewComponent, content, updatedInitializers);
}
export interface IFViewOptions {
    __backing_toggle1?: MutableState<boolean>;
    toggle1?: boolean;
    __backing_toggle2?: MutableState<boolean>;
    toggle2?: boolean;
    __backing_toggle3?: MutableState<boolean>;
    toggle3?: boolean;
}
