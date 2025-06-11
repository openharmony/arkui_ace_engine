// This file is needed to check how unmemoized (by ts plugin) should look like
// It is not actually executed

import { GlobalStateManager, memoEntry, StateContext, IncrementalNode,
    NodeAttach, mutableState, contextLocalValue, ReadonlyTreeNode, CONTEXT_ROOT_SCOPE,
    memoRoot, updateStateManager,
} from "@koalaui/runtime"
import { memo_foo } from "./stub"

/** @memo */
function f(s: string) {
    let x = () => {
        console.log(s)
    }
    x()
    let y = (s: string) => {
        console.log(s)
    }
    y("she")
}

/** @memo */
function bar(
    arg1: number,
    /** @memo */ arg2: (x: number) => number,
) {
    console.log(arg1, arg2(arg1))
}

/** @memo */
function foo_wrapper() {
    f("he")
    memo_foo("hello")
    bar(1, (x: number): number => { return 3 + x; })
}

class StringerNode extends IncrementalNode {
    constructor(kind: number = 1) {
        super(kind)
    }
    data: string | undefined = undefined
}

/** @memo */
function Stringer(
    arg: string,
    /** @memo */
    content?: () => void
): void {
    NodeAttach(() => new StringerNode(), (node: StringerNode): void => {
        node.data = arg
        console.log("I am recomputing with arg: ", arg)
        content?.()
    })
}

const state = mutableState<number>(17)

/** @memo */
function demo(node: StringerNode): void {
    Stringer("First", () => {
        console.log("Content of the first")
        Stringer(`Second ${state.value}`, () => {
            console.log("Content of the second")
            Stringer("Third")
        })
        Stringer("Fourth", () => {
            console.log("Content of the 4th")
            Stringer("5th")
        })
    })

    // This is to dump the complete managed incremental scope tree
    const scope = contextLocalValue<ReadonlyTreeNode>(CONTEXT_ROOT_SCOPE)
    console.log(scope?.toHierarchy())
}

function main() {
    const manager = GlobalStateManager.instance
    const state0 = manager.computableState((context: StateContext) => {
        memoEntry<void>(context, 0, foo_wrapper)
        return 20
    })
    console.log(state0.value)

    // memoRoot is the entry point here.
    // It initializes the incremental runtime and computes the first frame.
    // Have a look at its implementation.
    const root = memoRoot<StringerNode>(new StringerNode(0), demo)
    console.log(root.value.toHierarchy()) // dump ui subtree

    updateStateManager() // Compute next frame.
    console.log(root.value.toHierarchy())

    state.value = 19

    updateStateManager() // Compute the next frame.
    console.log(root.value.toHierarchy())
    console.log("-----END-----")
}
