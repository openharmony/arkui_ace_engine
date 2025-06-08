import { memo } from "@koalaui/runtime/annotations"

interface A {
    arg_memo_type: @memo () => void
}

@memo() (() => {
    let a: A = {
        arg_memo_type: (() => {}),
    };
});
