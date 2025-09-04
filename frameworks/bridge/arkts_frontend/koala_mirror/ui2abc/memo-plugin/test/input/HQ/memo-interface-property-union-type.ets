import { memo } from "@koalaui/runtime/annotations"

interface A {
    @memo memo_union_arg: (() => void) | undefined
}

@memo() (() => {
    let a: A = {
        memo_union_arg: (() => {})
    };
});
