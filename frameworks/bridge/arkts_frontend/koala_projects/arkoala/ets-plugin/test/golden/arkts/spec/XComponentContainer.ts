import { ArkColumn, ArkCommonMethodComponent, ArkPageTransitionEnterComponent, ArkPageTransitionExitComponent, ArkStructBase, ArkXComponent, XComponentOptions, XComponentType } from "@koalaui/arkts-arkui";
import { LocalStorage } from "@koalaui/arkui-common";
/** @memo:stable */
class ArkHomeComponentComponent extends ArkStructBase<ArkHomeComponentComponent, HomeComponentOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: HomeComponentOptions): void {
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: HomeComponentOptions) {
        ArkColumn(__builder, () => {
            ArkXComponent(undefined, undefined, { id: '1', type: 'component' } as XComponentOptions);
            ArkXComponent(undefined, undefined, { id: '2', type: 1 } as XComponentOptions);
            ArkXComponent(undefined, undefined, { id: '3', type: XComponentType.COMPONENT } as XComponentOptions);
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
    const updatedInitializers: HomeComponentOptions = {};
    ArkHomeComponentComponent._instantiate(style, () => new ArkHomeComponentComponent, content, updatedInitializers);
}
export interface HomeComponentOptions {
}
