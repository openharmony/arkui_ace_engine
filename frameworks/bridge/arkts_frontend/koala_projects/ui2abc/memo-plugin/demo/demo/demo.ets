/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
 
import { IncrementalNode,
    NodeAttach, mutableState, contextLocalValue, ReadonlyTreeNode,
    memoRoot, updateStateManager,
} from "@koalaui/runtime"

import { memo } from "@koalaui/runtime/annotations"

const CONTEXT_ROOT_SCOPE = "ohos.koala.context.root.scope" // not exported due to restart
class StringerNode extends IncrementalNode {
    constructor(kind: int = 1) {
        super(kind)
    }
    data: string | undefined = undefined
}

@memo
function Stringer(
    arg: string,
    @memo
    content?: () => void
): void {
    NodeAttach(():StringerNode => 
        new StringerNode(), (node: StringerNode): void => {
        node.data = arg
        console.log("I am recomputing with arg: ", arg)
        content?.()
    })
}

const state = mutableState<Int>(17)

@memo
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
    console.log(state.value)

    // memoRoot is the entry point here.
    // It initializes the incremental runtime and computes the first frame.
    // Have a look at its implementation.
    console.log("\nBuild first frame")
    const root = memoRoot<StringerNode>(new StringerNode(0), demo)
    console.log(root.value.toHierarchy()) // dump ui subtree

    console.log("\nBuild second frame")
    updateStateManager() // Compute next frame.
    console.log(root.value.toHierarchy())

    state.value = 19

    console.log("\nBuild third frame")
    updateStateManager() // Compute the next frame.
    console.log(root.value.toHierarchy())
    console.log("-----END-----")
}
