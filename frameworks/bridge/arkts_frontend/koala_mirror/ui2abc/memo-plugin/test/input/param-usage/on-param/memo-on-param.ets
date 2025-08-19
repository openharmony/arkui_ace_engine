import { memo } from "@koalaui/runtime/annotations"

@memo function memo_function(@memo param: () => void): void {
    param()
}
