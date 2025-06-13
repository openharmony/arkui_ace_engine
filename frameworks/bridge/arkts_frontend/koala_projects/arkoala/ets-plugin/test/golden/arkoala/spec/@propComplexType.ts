import { ArkCommonMethodComponent, ArkPageTransitionEnterComponent, ArkPageTransitionExitComponent, ArkRow, ArkStructBase, ArkText, LocalStorage, MutableState, SyncedProperty, observableProxy, propState, stateOf } from "@koalaui/arkoala-arkui";
import { registerArkuiEntry } from "@koalaui/arkoala-arkui/ohos.router";
var nextID: number = 0;
class ClassA {
    private __backing_name?: MutableState<string>;
    public get name(): string {
        return this.__backing_name!.value;
    }
    public set name(value: string) {
        if (this.__backing_name)
            this.__backing_name!.value = observableProxy(value);
        else
            this.__backing_name = stateOf<string>(value);
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
    constructor(c: number, name: string = 'OK') {
        this.name = name;
        this.c = c;
        this.id = nextID++;
    }
}
/** @memo:stable */
class ArkCustomXComponent extends ArkStructBase<ArkCustomXComponent, CustomXOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: CustomXOptions): void {
        this.__backing_fruit = propState<ClassA>(new ClassA(1));
    }
    private __backing_fruit?: SyncedProperty<ClassA>;
    private get fruit(): ClassA {
        return this.__backing_fruit!.value;
    }
    private set fruit(value: ClassA) {
        this.__backing_fruit!.value = observableProxy(value);
    }
    /** @memo */
    __updateStruct(initializers: CustomXOptions | undefined): void {
        this.__backing_fruit?.update(initializers?.fruit);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: CustomXOptions) {
        ArkRow(__builder, () => {
            ArkText(undefined, undefined, JSON.stringify(this.fruit.c));
        });
    }
}
/** @memo:stable */
class ArkIndexComponent extends ArkStructBase<ArkIndexComponent, IndexOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: IndexOptions): void {
        this.__backing_arrA = stateOf<ClassA[]>(initializers?.arrA ?? ([new ClassA(0), new ClassA(0)]), this);
    }
    private __backing_arrA?: MutableState<ClassA[]>;
    private get arrA(): ClassA[] {
        return this.__backing_arrA!.value;
    }
    private set arrA(value: ClassA[]) {
        this.__backing_arrA!.value = observableProxy(value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: IndexOptions) {
        ArkRow(__builder, () => {
            CustomX(undefined, undefined, { fruit: this.arrA[0] } as CustomXOptions);
            CustomX(undefined, undefined, {} as CustomXOptions);
        });
    }
}
export {};
/** @memo */
export function CustomX(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: CustomXOptions): void {
    const updatedInitializers: CustomXOptions = {
        fruit: initializers?.fruit,
        __backing_fruit: initializers?.__backing_fruit
    };
    ArkCustomXComponent._instantiate(style, () => new ArkCustomXComponent, content, updatedInitializers);
}
/** @memo */
export function Index(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: IndexOptions): void {
    const updatedInitializers: IndexOptions = {
        __backing_arrA: initializers?.__backing_arrA
    };
    ArkIndexComponent._instantiate(style, () => new ArkIndexComponent, content, updatedInitializers);
}
export interface CustomXOptions {
    __backing_fruit?: SyncedProperty<ClassA>;
    fruit?: ClassA;
}
export interface IndexOptions {
    __backing_arrA?: MutableState<ClassA[]>;
    arrA?: ClassA[];
}
registerArkuiEntry(Index, "@propComplexType");
export const __Entry = Index;
