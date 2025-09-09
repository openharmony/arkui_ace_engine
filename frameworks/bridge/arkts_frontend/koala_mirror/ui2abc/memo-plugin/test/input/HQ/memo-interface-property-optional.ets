import { memo } from "@koalaui/runtime/annotations"

interface A {
    @memo memo_optional_arg?: () => void
}

@memo() (() => {
    let a: A = {
    };
});
