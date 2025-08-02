import { ArkStructBase } from './ArkStructBase'
import { ArkCommonMethodComponent } from './generated';
import { InteropNativeModule } from "@koalaui/interop"
class Delegate<T, OptionsT> extends ArkStructBase<Delegate<T, OptionsT>, OptionsT> {
    instance: StructBase<T, OptionsT>;

    constructor(instance: StructBase<T, OptionsT>) {
        super()
        this.instance = instance
    }

    /** @memo */
    __build(
        /** @memo */
        attributes: undefined | ((instance: ArkCommonMethodComponent) => void),
        /** @memo */
        content?: () => void,
        initializers?: OptionsT | undefined): void {
        this.instance._build(undefined, content, undefined)
    }
    aboutToAppear(): void {
        InteropNativeModule._NativeLog("ARKTS: aboutToAppear")
        this.instance.aboutToAppear()
    }
    aboutToDisappear(): void {
        InteropNativeModule._NativeLog("ARKTS: aboutToDisappear")
        this.instance.aboutToAppear()
    }
    onPageShow(): void {
        InteropNativeModule._NativeLog("ARKTS: onPageShow")
        this.instance.aboutToAppear()
    }
    onPageHide(): void {
        InteropNativeModule._NativeLog("ARKTS: onPageHide")
        this.instance.aboutToAppear()
    }
}

export abstract class StructBase<T, OptionsT> {
    /** @memo */
    static instantiateImpl<S extends StructBase<S, OptionsS>, OptionsS> (
        /** @memo */
        builder: ((instance: S) => S) | undefined,
        factory: () => S,
        options?: OptionsS,
        /** @memo */
        content?: () => void
    ) {
        Delegate._instantiate(undefined, () => new Delegate<S, OptionsS>(factory()), content, options);
    }
    aboutToAppear(): void {
    }
    aboutToDisappear(): void {
    }
    onPageShow(): void {
    }
    onPageHide(): void {
    }
    /** @memo */
    abstract _build(
        /** @memo */
        style: ((instance: T) => T) | undefined,
        /** @memo */
        content: (() => void) | undefined, options: OptionsT | undefined ): void;
}