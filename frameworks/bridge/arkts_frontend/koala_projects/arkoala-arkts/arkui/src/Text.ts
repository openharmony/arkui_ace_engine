import { ArkText } from "./generated/ArkText";

// An attempt to put down a component
export class Text {
    /** @memo */
    static instantiateImpl(
        /** @memo */
        style: ((instance: Text) => Text) | undefined,
        factory: () => Text,
        options?: string,
        /** @memo */
        content?: () => void
    ): void {
        ArkText(undefined, undefined, options, undefined)
    }
}
