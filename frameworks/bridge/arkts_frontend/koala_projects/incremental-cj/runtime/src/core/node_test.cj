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
package KoalaRuntime.core

import KoalaRuntime.tree.*

@Test
public class NodeTest {
    @TestCase
    public func checkNodeAttach(): Unit {
        testPrepareOnStart()
        let state = mutableState(false)
        let root = testRoot {
            let node = contextNode<TestNode>() {"root node"}
            collector.append("update:root")
            @Assert(node.content, "root")
            NodeAttach(
                {
                    =>
                    collector.append("create:first")
                    TestNode("first")
                }
            ) {
                state.getValue() // depended
                let node = contextNode<TestNode>() {"first node"}
                collector.append("update:first")
                @Assert(node.content, "first")
            }
            NodeAttach(
                {
                    =>
                    collector.append("create:second")
                    TestNode("second")
                }
            ) {
                state.getValue() // depended
                let node = contextNode<TestNode>() {"second node"}
                collector.append("update:second")
                @Assert(node.content, "second")
            }
        }
        testCollector("update:root", "create:first", "update:first", "create:second", "update:second")
        testTick(root)
        testCollector()
        state.setValue(true)
        testTick(root)
        testCollector("update:root", "update:first", "update:second")
    }
    @TestCase
    public func checkNodeAttachHierarchy(): Unit {
        testPrepareOnStart()
        let root = testRoot {
            NodeAttach({=> TestNode("parent1")}) {
                NodeAttach {TestNode("child11")}
                NodeAttach {TestNode("child12")}
            }
            NodeAttach({=> TestNode("parent2")}) {
                NodeAttach {TestNode("child21")}
                NodeAttach {TestNode("child22")}
            }
        }
        assertHierarchyOf(
            root.getValue(),
            """
root
  parent1
    child11
    child12
  parent2
    child21
    child22"""
        )
    }
}
