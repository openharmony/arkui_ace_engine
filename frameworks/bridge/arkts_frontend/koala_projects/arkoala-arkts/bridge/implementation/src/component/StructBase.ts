import { ArkCommonMethodComponent, ArkStructBase } from "@koalaui/arkts-arkui"

class Delegate<T extends StructBase<T, T_Options>, T_Options> extends ArkStructBase<Delegate<T, T_Options>, T_Options> {
    instance: StructBase<T, T_Options>;

    constructor(instance: StructBase<T, T_Options>) {
        super();
        this.instance = instance;
    }

    /** @memo */
    __build(
        /** @memo */
        attributes: undefined | ((instance: ArkCommonMethodComponent) => void),
        /** @memo */
        content?: () => void,
        initializers?: T_Options | undefined
    ): void {
        this.instance.internalBuildWrapper(undefined, initializers, content);
    }

    aboutToAppear(): void {
        this.instance.aboutToAppear();
    }

    aboutToDisAppear(): void {
        this.instance.aboutToDisAppear();
    }
}

export interface CustomComponent {
    aboutToAppear(): void;
    aboutToDisAppear(): void;
    build(): void;
}

export abstract class CustomComponentImpl implements CustomComponent {
    aboutToAppear(): void {}
    aboutToDisAppear(): void {}
    build(): void {}
}

export abstract class StructBase<T extends StructBase<T, T_Options>, T_Options> extends CustomComponentImpl {
    /** @memo */
    // @BuildLambda("_instantiateImpl")
    static $_instantiate<S extends StructBase<S, S_Options>, S_Options>(
        factory: () => S,
        /** @memo */
        initializers?: S_Options,
        /** @memo */
        content?: () => void
    ): S {
        throw new Error("MUST NOT RUN HERE !!!");
    }

    /** @memo */
    static _instantiateImpl<S extends StructBase<S, S_Options>, S_Options>(
        /** @memo */
        style: ((instance: S) => void) | undefined,
        factory: () => S,
        initializers?: S_Options,
        /** @memo */
        content?: () => void
    ): void {
        Delegate._instantiate(undefined, () => new Delegate<S, S_Options>(factory()), content, initializers);
    }

    // Can be overridden as an effect of @Prop, @Watch etc
    /** @memo */
    protected __updateStruct(initializers?: T_Options): void {}

    /** @memo */
    protected __initializeStruct(
        initializers?: T_Options,
        /** @memo */
        content?: () => void
    ): void {}

    /** @memo */
    protected abstract __build(
        /** @memo */
        style: ((instance: T) => void) | undefined,
        /** @memo */
        content?: () => void
    ): void;

    /** @memo */
    private _buildWrapper(
        /** @memo */
        style: ((instance: T) => void) | undefined,
        initializers?: T_Options,
        /** @memo */
        content?: () => void
    ): void {
        this.__build(style, content);
    }

    // @internal API for work around
    /** @memo */
    internalUpdateStruct(initializers?: T_Options): void {
        this.__updateStruct(initializers);
    }

    // @internal API for work around
    /** @memo */
    internalInitializeStruct(
        initializers?: T_Options,
        /** @memo */
        content?: () => void
    ): void {
        this.__initializeStruct(initializers, content);
    }

    // @internal API for work around
    /** @memo */
    internalBuildWrapper(
        /** @memo */
        style: ((instance: T) => void) | undefined,
        initializers?: T_Options,
        /** @memo */
        content?: () => void
    ): void {
        this._buildWrapper(style, initializers, content);
    }
}
