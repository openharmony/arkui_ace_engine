import { ArkColumn, ArkCommonMethodComponent, ArkPageTransitionEnterComponent, ArkPageTransitionExitComponent, ArkStructBase, ArkText, ArkTextComponent, LocalStorage } from "@koalaui/arkoala-arkui";
/** @memo:stable */
export class ArkTestComponentComponent extends ArkStructBase<ArkTestComponentComponent, TestComponentOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: TestComponentOptions): void {
        this.__backing_content = initializers?.content ?? ('Test Component');
    }
    private __backing_content?: string;
    private get content(): string {
        return this.__backing_content as string;
    }
    private set content(value: string) {
        this.__backing_content = value;
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: TestComponentOptions) {
        ArkColumn(__builder, () => {
            ArkText((__instance: ArkTextComponent) => {
                __instance.fontSize(32);
            }, undefined, this.content);
        });
    }
}
/** @memo:stable */
export class ArkCustomContainerExportComponent extends ArkStructBase<ArkCustomContainerExportComponent, CustomContainerExportOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: CustomContainerExportOptions): void {
        this.__backing_header = initializers?.header ?? ("");
        if (initializers?.closer) {
            this.__backing_closer = initializers?.closer;
        }
        if (this.__backing_closer === undefined && content !== undefined)
            this.__backing_closer = content;
    }
    private __backing_header?: string;
    private get header(): string {
        return this.__backing_header as string;
    }
    private set header(value: string) {
        this.__backing_header = value;
    }
    /** @memo */
    private __backing_closer?: () => void;
    /** @memo */
    private get closer(): () => void {
        return this.__backing_closer!;
    }
    private set closer(/**/
    /** @memo */
    value: () => void) {
        this.__backing_closer = value;
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: CustomContainerExportOptions) {
        ArkColumn(__builder, () => {
            ArkText((__instance: ArkTextComponent) => {
                __instance.fontSize(50);
            }, undefined, this.header);
            this.closer();
        });
    }
}
export {};
/** @memo */
export function TestComponent(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: TestComponentOptions): void {
    const updatedInitializers: TestComponentOptions = {
        content: initializers?.content
    };
    ArkTestComponentComponent._instantiate(style, () => new ArkTestComponentComponent, content, updatedInitializers);
}
/** @memo */
export function CustomContainerExport(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: CustomContainerExportOptions): void {
    const updatedInitializers: CustomContainerExportOptions = {
        header: initializers?.header,
        closer: initializers?.closer
    };
    ArkCustomContainerExportComponent._instantiate(style, () => new ArkCustomContainerExportComponent, content, updatedInitializers);
}
export interface TestComponentOptions {
    content?: string;
}
export interface CustomContainerExportOptions {
    header?: string;
    /** @memo */
    closer?: () => void;
}
