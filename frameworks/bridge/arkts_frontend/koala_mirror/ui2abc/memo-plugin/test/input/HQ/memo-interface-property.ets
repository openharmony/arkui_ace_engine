import { memo } from "@koalaui/runtime/annotations"

interface A {
    @memo memo_arg: () => void
}

@memo() (() => {
    let a: A = {
        memo_arg: (() => {})
    };
});
