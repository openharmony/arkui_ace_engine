import { remember } from "@koalaui/runtime"
import { ArkCustomComponentImpl } from "./ArkCustomComponent";
import { ArkComponentRoot } from "./ArkComponentRoot";
import { ArkCommonMethodComponent } from "./generated";

/** base class for user's structs */
export abstract class ArkStructBase<T, T_Options> extends ArkCustomComponentImpl {
    // Can be overridden as an effect of @Prop, @Watch etc
    /** @memo */
    protected __updateStruct(arg1?: T_Options): void { }

    /** @memo */
    static _instantiate<T extends ArkStructBase<T, T_Options>, T_Options>(
        /** @memo */
        attributes: undefined | ((instance: ArkCommonMethodComponent) => void),
        factory: () => T,
        /** @memo */
        arg1?: () => void,
        arg2?: T_Options
    ): void {
        const receiver = remember(() => {
            const instance = factory();
            instance.__initializeStruct(arg1, arg2);
            return instance;
        });
        receiver._buildWrapper(attributes, arg1, arg2);
    }

    protected __initializeStruct(
        /** @memo */
        content?: () => void,
        initializers?: T_Options
    ): void {
        console.log("__initializeStruct()")
    }

    /** @memo */
    _buildWrapper(
        /** @memo */
        attributes: undefined | ((instance: ArkCommonMethodComponent) => void),
        /** @memo */
        content?: () => void,
        initializers?: T_Options
    ): void {
        ArkComponentRoot(this, () => {
            this.__updateStruct(initializers)
            this.__build(attributes, content, initializers)
        })
    }

    /** @memo */
    abstract __build(
        /** @memo */
        attributes: undefined | ((instance: ArkCommonMethodComponent) => void),
        /** @memo */
        content?: () => void,
        initializers?: T_Options
    ): void
}
