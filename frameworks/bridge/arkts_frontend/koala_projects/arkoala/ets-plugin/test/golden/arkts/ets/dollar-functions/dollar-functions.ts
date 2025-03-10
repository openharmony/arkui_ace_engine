import { ArkColumn, ArkColumnComponent, ArkCommonMethodComponent, ArkImage, ArkPageTransitionEnterComponent, ArkPageTransitionExitComponent, ArkStructBase, ArkText, _r, _rawfile, stateOf } from "@koalaui/arkts-arkui";
import { MutableState } from "@koalaui/runtime";
import { LocalStorage } from "@koalaui/arkui-common";
import { observableProxy } from "@koalaui/common";
/** @memo:stable */
class ArkIndexComponent extends ArkStructBase<ArkIndexComponent, IndexOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: IndexOptions): void {
        this.__backing_myState2 = stateOf<string>(initializers?.myState2 ?? ("Hello"), this);
    }
    private __backing_myState2?: MutableState<string>;
    private get myState2(): string {
        return this.__backing_myState2!.value;
    }
    private set myState2(value: string) {
        this.__backing_myState2!.value = observableProxy(value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: IndexOptions) {
        ArkColumn(__instance => {
            {
                __instance.height('100%')
                    .width('100%');
            }
            __builder?.(__instance);
        }, () => {
            ArkImage(undefined, undefined, _rawfile("com.application.example", "entry", 'startIcon.png'));
            ArkImage(undefined, undefined, _r("com.application.example", "entry", 'app.media.icon'));
            ArkText(undefined, undefined, this.$myState2);
        });
    }
}
/** @memo */
export function Index(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: IndexOptions): void {
    const updatedInitializers: IndexOptions = {
        __backing_myState2: initializers?.__backing_myState2
    };
    ArkIndexComponent._instantiate(style, () => new ArkIndexComponent, content, updatedInitializers);
}
export interface IndexOptions {
    __backing_myState2?: MutableState<string>;
    myState2?: string;
}
