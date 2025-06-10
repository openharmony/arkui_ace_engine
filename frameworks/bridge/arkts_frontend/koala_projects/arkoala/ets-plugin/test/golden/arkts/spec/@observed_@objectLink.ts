import { ArkColumn, ArkCommonMethodComponent, ArkPageTransitionEnterComponent, ArkPageTransitionExitComponent, ArkRow, ArkStructBase, ArkText, SyncedProperty, objectLinkState, stateOf } from "@koalaui/arkts-arkui";
import { MutableState } from "@koalaui/runtime";
import { observableProxy } from "@koalaui/common";
import { LocalStorage } from "@koalaui/arkui-common";
let NextID: number = 0;
class ClassA {
    private __backing_id?: MutableState<number>;
    public get id(): number {
        return this.__backing_id!.value;
    }
    public set id(value: number) {
        if (this.__backing_id)
            this.__backing_id!.value = observableProxy(value);
        else
            this.__backing_id = stateOf<number>(value);
    }
    private __backing_c?: MutableState<number>;
    public get c(): number {
        return this.__backing_c!.value;
    }
    public set c(value: number) {
        if (this.__backing_c)
            this.__backing_c!.value = observableProxy(value);
        else
            this.__backing_c = stateOf<number>(value);
    }
    constructor(c: number) {
        this.id = NextID++;
        this.c = c;
    }
}
class ClassB {
    private __backing_a?: MutableState<ClassA>;
    public get a(): ClassA {
        return this.__backing_a!.value;
    }
    public set a(value: ClassA) {
        if (this.__backing_a)
            this.__backing_a!.value = observableProxy(value);
        else
            this.__backing_a = stateOf<ClassA>(value);
    }
    constructor(a: ClassA) {
        this.a = a;
    }
}
/** @memo:stable */
class ArkViewAComponent extends ArkStructBase<ArkViewAComponent, ViewAOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: ViewAOptions): void {
        this.__backing_varA = objectLinkState<ClassA>();
    }
    private __backing_varA?: SyncedProperty<ClassA>;
    private get varA(): ClassA {
        return this.__backing_varA!.value;
    }
    private set varA(value: ClassA) {
        this.__backing_varA!.value = observableProxy(value);
    }
    /** @memo */
    __updateStruct(initializers: ViewAOptions | undefined): void {
        this.__backing_varA?.update(initializers?.varA);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: ViewAOptions) {
        ArkRow(__builder, () => {
            ArkText(undefined, undefined, 'ViewA-' + this.varA.id);
        });
    }
}
/** @memo:stable */
class ArkViewBComponent extends ArkStructBase<ArkViewBComponent, ViewBOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: ViewBOptions): void {
        this.__backing_varB = stateOf<ClassB>(initializers?.varB ?? (new ClassB(new ClassA(0))), this);
    }
    private __backing_varB?: MutableState<ClassB>;
    private get varB(): ClassB {
        return this.__backing_varB!.value;
    }
    private set varB(value: ClassB) {
        this.__backing_varB!.value = observableProxy(value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: ViewBOptions) {
        ArkColumn(__builder, () => {
            ArkRow(undefined, () => {
                ViewA(undefined, undefined, { varA: this.varB.a } as ViewAOptions);
                ArkText(undefined, undefined, 'ViewB');
            });
        });
    }
}
export {};
/** @memo */
export function ViewA(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: ViewAOptions): void {
    const updatedInitializers: ViewAOptions = {
        varA: initializers?.varA,
        __backing_varA: initializers?.__backing_varA
    };
    ArkViewAComponent._instantiate(style, () => new ArkViewAComponent, content, updatedInitializers);
}
/** @memo */
export function ViewB(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: ViewBOptions): void {
    const updatedInitializers: ViewBOptions = {
        __backing_varB: initializers?.__backing_varB
    };
    ArkViewBComponent._instantiate(style, () => new ArkViewBComponent, content, updatedInitializers);
}
export interface ViewAOptions {
    __backing_varA?: SyncedProperty<ClassA>;
    varA?: ClassA;
}
export interface ViewBOptions {
    __backing_varB?: MutableState<ClassB>;
    varB?: ClassB;
}
