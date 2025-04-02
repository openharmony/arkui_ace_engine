import { float64, int32, float32 } from "./types"

export function asFloat64(value: string): float64 {
    return Number(value)
}

export function asString(value: float64 | undefined): string | undefined {
    return value?.toString()
}

export function float32FromBits(value: int32): float32 {
    return value
}

export function int32BitsFromFloat(value: float32): int32 {
    return value
}
