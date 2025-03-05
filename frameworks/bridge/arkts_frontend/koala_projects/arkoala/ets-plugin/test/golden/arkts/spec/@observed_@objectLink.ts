import { ArkColumn, ArkCommonMethodComponent, ArkPageTransitionEnterComponent, ArkPageTransitionExitComponent, ArkRow, ArkStructBase, ArkText, SyncedProperty, objectLinkState, stateOf } from "@koalaui/arkts-arkui";
import { LocalStorage } from "@koalaui/arkui-common";
import { observableProxy } from "@koalaui/common";
import { MutableState } from "@koalaui/runtime";
let NextID: number = 0;
class ClassA {
    public id: number;
    public c: number;
    constructor(c: number) {
        this.id = NextID++;
        this.c = c;
    }
}
class ClassB {
    public a: ClassA;
    constructor(a: ClassA) {
        this.a = a;
    }
}
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
