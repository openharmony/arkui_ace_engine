import { ArkButton, ArkButtonComponent, ArkColumn, ArkCommonMethodComponent, ArkPageTransitionEnterComponent, ArkPageTransitionExitComponent, ArkStructBase, ArkText, ArkTextComponent, LocalStorage, MutableState, contextLocal, contextLocalStateOf, observableProxy } from "@koalaui/arkoala-arkui";
import { registerArkuiEntry } from "@koalaui/arkoala-arkui/ohos.router";
/** @memo:stable */
class ArkCompAComponent extends ArkStructBase<ArkCompAComponent, CompAOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: CompAOptions): void {
        this.__backing_reviewVotes = initializers!.__backing_reviewVotes!;
    }
    private __backing_reviewVotes?: MutableState<number>;
    private get reviewVotes(): number {
        return this.__backing_reviewVotes!.value;
    }
    private set reviewVotes(value: number) {
        this.__backing_reviewVotes!.value = observableProxy(value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: CompAOptions) {
        ArkColumn(__builder, () => {
            CompB(undefined, undefined);
            ArkButton((__instance: ArkButtonComponent) => {
                __instance.onClick(() => {
                    this.reviewVotes += 1;
                });
            }, () => {
                ArkText((__instance: ArkTextComponent) => {
                    __instance.fontSize(30);
                }, undefined, '' + this.reviewVotes);
            });
        });
    }
}
/** @memo:stable */
class ArkCompBComponent extends ArkStructBase<ArkCompBComponent, CompBOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: CompBOptions): void {
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: CompBOptions) {
        ArkColumn(__builder, () => {
            CompC(undefined, undefined);
        });
    }
}
/** @memo:stable */
class ArkCompCComponent extends ArkStructBase<ArkCompCComponent, CompCOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: CompCOptions): void {
        this.__backing_reviewVotes = initializers!.__backing_reviewVotes!;
    }
    private __backing_reviewVotes?: MutableState<number>;
    private get reviewVotes(): number {
        return this.__backing_reviewVotes!.value;
    }
    private set reviewVotes(value: number) {
        this.__backing_reviewVotes!.value = observableProxy(value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: CompCOptions) {
        ArkColumn(__builder, () => {
            ArkButton((__instance: ArkButtonComponent) => {
                __instance.onClick(() => {
                    this.reviewVotes += 1;
                });
            }, () => {
                ArkText((__instance: ArkTextComponent) => {
                    __instance.fontSize(30);
                }, undefined, '' + this.reviewVotes);
            });
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
    const __provide_reviewVote = contextLocalStateOf<number>("reviewVote", () => 0);
    const updatedInitializers: CompAOptions = {
        __backing_reviewVotes: __provide_reviewVote
    };
    ArkCompAComponent._instantiate(style, () => new ArkCompAComponent, content, updatedInitializers);
}
/** @memo */
export function CompB(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: CompBOptions): void {
    const updatedInitializers: CompBOptions = {};
    ArkCompBComponent._instantiate(style, () => new ArkCompBComponent, content, updatedInitializers);
}
/** @memo */
export function CompC(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: CompCOptions): void {
    const __consume_reviewVote = contextLocal<number>("reviewVote") as MutableState<number>;
    const updatedInitializers: CompCOptions = {
        __backing_reviewVotes: __consume_reviewVote
    };
    ArkCompCComponent._instantiate(style, () => new ArkCompCComponent, content, updatedInitializers);
}
export interface CompAOptions {
    __backing_reviewVotes?: MutableState<number>;
    reviewVotes?: number;
}
registerArkuiEntry(CompA, "@consume_@provide");
export const __Entry = CompA;
export interface CompBOptions {
}
export interface CompCOptions {
    __backing_reviewVotes?: MutableState<number>;
    reviewVotes?: number;
}
