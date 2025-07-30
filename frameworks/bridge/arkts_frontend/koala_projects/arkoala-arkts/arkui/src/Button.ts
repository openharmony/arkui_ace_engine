import { ArkButton } from "./generated/ArkButton";

// An attempt to put down a component
export class Button {
    /** @memo */
    static instantiateImpl(
        /** @memo */
        style: ((instance: Button) => Button) | undefined,
        factory: () => Button,
        options?: string,
        /** @memo */
        content?: () => void
    ): void {
        ArkButton(undefined, undefined, options, undefined)
    }
}
