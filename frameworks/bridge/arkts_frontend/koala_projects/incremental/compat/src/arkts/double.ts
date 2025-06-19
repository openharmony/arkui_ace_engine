import { float64, int32, float32 } from "./types"

export function asFloat64(value: string): float64 {
    return (new Number(value)).valueOf()
}

export function asString(value: float64 | undefined): string | undefined {
    if (value === undefined) return undefined
    return (new Number(value)).toString()
}

export function float32FromBits(value: int32): float32 {
    return Float.bitCastFromInt(value)
}

export function int32BitsFromFloat(value: float32): int32 {
    return Float.bitCastToInt(value)
}
