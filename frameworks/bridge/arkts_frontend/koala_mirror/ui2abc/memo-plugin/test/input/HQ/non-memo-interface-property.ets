import { memo } from "@koalaui/runtime/annotations"

interface A {
    arg: () => void
}

@memo() (() => {
    let a: A = {
        arg: (() => {})
    };
});
