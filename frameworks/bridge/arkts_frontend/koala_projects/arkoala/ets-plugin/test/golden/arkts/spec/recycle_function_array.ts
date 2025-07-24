import { ArkCircle, ArkCircleComponent, ArkColumn, ArkCommonMethodComponent, ArkPageTransitionEnterComponent, ArkPageTransitionExitComponent, ArkReusableStruct, ArkStructBase, ArkText, ArkTextComponent, stateOf } from "@koalaui/arkts-arkui";
import { MutableState } from "@koalaui/runtime";
import { LocalStorage } from "@koalaui/arkui-common";
import { observableProxy } from "@koalaui/common";
/** @memo:stable */
class ArkHomeComponentComponent extends ArkStructBase<ArkHomeComponentComponent, HomeComponentOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: HomeComponentOptions): void {
        this.__backing_value = stateOf<number>(initializers?.value ?? (1), this);
    }
    private __backing_value?: MutableState<number>;
    private get value(): number {
        return this.__backing_value!.value;
    }
    private set value(value: number) {
        this.__backing_value!.value = observableProxy(value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: HomeComponentOptions) {
        ArkColumn(__builder, () => {
            child(undefined, undefined);
        });
    }
}
/** @memo:stable */
class ArkchildComponent extends ArkReusableStruct<ArkchildComponent, childOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: childOptions): void {
        this.__backing_state_value = stateOf<number>(initializers?.state_value ?? (1), this);
        this.__backing_reguar_value = initializers?.reguar_value ?? ("hello");
    }
    private __backing_state_value?: MutableState<number>;
    private get state_value(): number {
        return this.__backing_state_value!.value;
    }
    private set state_value(value: number) {
        this.__backing_state_value!.value = observableProxy(value);
    }
    private __backing_reguar_value?: string;
    private get reguar_value(): string {
        return this.__backing_reguar_value as string;
    }
    private set reguar_value(value: string) {
        this.__backing_reguar_value = value;
    }
    override __toRecord(initializers: Object): Record<string, Object> {
        const _optionData = initializers as childOptions;
        return { "state_value": _optionData.__backing_state_value?.value ?? (new Object()), "reguar_value": _optionData.__backing_reguar_value?.value ?? (new Object()) };
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: childOptions) {
        ArkColumn(__builder, () => {
            ArkCircle((__instance: ArkCircleComponent) => {
                __instance.onClick(() => {
                    console.log("hello");
                })
                    .strokeDashArray(["hello", this.reguar_value])
                    .height(100);
            }, undefined);
            ArkCircle((__instance: ArkCircleComponent) => {
                __instance.strokeDashArray([this.state_value]);
            }, undefined);
            ArkText((__instance: ArkTextComponent) => {
                __instance.onClick(() => {
                    console.log("hello");
                });
            }, undefined, "hello");
        });
    }
}
export {};
/** @memo */
export function HomeComponent(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: HomeComponentOptions): void {
    const updatedInitializers: HomeComponentOptions = {
        __backing_value: initializers?.__backing_value
    };
    ArkHomeComponentComponent._instantiate(style, () => new ArkHomeComponentComponent, content, updatedInitializers);
}
/** @memo */
export function child(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: childOptions): void {
    const updatedInitializers: childOptions = {
        __backing_state_value: initializers?.__backing_state_value,
        reguar_value: initializers?.reguar_value
    };
    ArkchildComponent._instantiate(style, () => new ArkchildComponent, content, updatedInitializers, "ArkchildComponent");
}
export interface HomeComponentOptions {
    __backing_value?: MutableState<number>;
    value?: number;
}
export interface childOptions {
    __backing_state_value?: MutableState<number>;
    state_value?: number;
    reguar_value?: string;
}
