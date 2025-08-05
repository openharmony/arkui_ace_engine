import { memo } from "@koalaui/runtime/annotations"

@memo function memo_function(@memo param: @memo ((() => void) | undefined)): void {
    param?.()
}
