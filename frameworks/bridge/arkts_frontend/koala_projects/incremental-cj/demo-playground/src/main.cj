/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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
package DemoPlayground

import KoalaRuntime.*
import KoalaRuntime.memoize.*

class StringerNode <: IncrementalNode { 
    StringerNode(public var data: String) {
        super(0)
    }
    public func toStringBuilder(sb: StringBuilder): Unit {
        sb.append(this.data)
    }

}

@Memo
func Stringer(
    arg: String,
    content: ?() -> Unit
): Unit {
    NodeAttach<StringerNode>(
        { =>
            StringerNode(arg)
        }
    ) { 
        let node = contextNode<StringerNode>()
        if(let Some(n) <- node) {
            n.data = arg
        }
        println("I am recomputing with arg: " + arg)
        if(let Some(cont) <- content){
            cont()
        }
    }
}

let state: MutableState<String> = mutableState("before")

@Memo
func demo(): Unit {
    Stringer("First", @Memo({ => 
        println("Content of the first")
        Stringer(state.getValue(), @Memo({ => 
            println("Content of the second")
            Stringer("Third", Option.None)
        }))
        Stringer("Fourth", @Memo({ =>
            println("Content of the fourth")
            Stringer("Fifth", Option.None)
        }))
    }))

    // This is to dump the complete managed incremental scope tree
    let hierarchy = contextLocalValue<() -> String>(CONTEXT_ROOT_SCOPE_HIERARCHY_SUPPLIER)()
    println(hierarchy)
}

main(): Unit {
    let root: ComputableState<IncrementalNode> = memoRoot(IncrementalNode(0), demo)
    println(dumpHierarchyOf<IncrementalNode>(root.getValue())) // dump ui subtree

    GlobalStateManager.updateSnapshot() // Compute next frame.
    println(dumpHierarchyOf<IncrementalNode>(root.getValue())) // dump ui subtree

    state.setValue("after")

    GlobalStateManager.updateSnapshot() // Compute the next frame.
    println(dumpHierarchyOf<IncrementalNode>(root.getValue())) // dump ui subtree
}
