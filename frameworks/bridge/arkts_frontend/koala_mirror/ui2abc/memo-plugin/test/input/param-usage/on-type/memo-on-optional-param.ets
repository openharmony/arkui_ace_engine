import { memo } from "@koalaui/runtime/annotations"

@memo function memo_function(param?: @memo () => void): void {
    param?.()
}
