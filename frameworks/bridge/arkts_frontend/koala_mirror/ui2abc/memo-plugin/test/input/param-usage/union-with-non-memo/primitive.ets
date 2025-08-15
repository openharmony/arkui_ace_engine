import { memo, memo_skip } from "@koalaui/runtime/annotations"

type Builder = @memo () => void

@memo function memo_function(@memo_skip param: Builder | string): void {
    if (param instanceof Builder) {
        param()
    } else {
        param
    }
}

@memo function callsite(): void {
    memo_function(() => {})
    memo_function("hello")
}
