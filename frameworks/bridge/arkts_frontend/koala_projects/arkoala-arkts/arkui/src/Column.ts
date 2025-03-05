import { ArkColumn } from "./generated/ArkColumn"

export class Column {
    /** @memo */
    static instantiateImpl(
        /** @memo */
        style: (instance: Column) => Column,
        factory: () => Column,
        /** @memo */
        content?: () => void,
        options?: undefined
    ): void {
        ArkColumn(undefined, content, options)
    }
}