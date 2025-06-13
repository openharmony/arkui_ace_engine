import { ArkColumn } from "./generated/ArkColumn"
import { ColumnOptions as ArkColumnOptions } from "./generated/ArkColumnInterfaces"

export interface ColumnOptions {
    space?: number
}

function CastColumnOptions(options?: ColumnOptions): ArkColumnOptions {
    let ret: ArkColumnOptions = {}
    ret.space = options?.space;
    return ret;
}

export class Column {
    /** @memo */
    static instantiateImpl(
        /** @memo */
        style: (instance: Column) => Column | undefined,
        factory: () => Column,
        /** @memo */
        content?: () => void,
        options?: ColumnOptions | undefined
    ): void {
        ArkColumn(undefined, content, CastColumnOptions(options))
    }
}