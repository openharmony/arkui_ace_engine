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

@Test
public class IncrementalNodeTest {
    @TestCase
    public func treeSctructure(): Unit {
        let root = IncrementalNode(0)
        @Assert(root.kind == 0)
        @Assert(root.parent.isNone())
        @Assert(root.firstChild.isNone())
        IncrementalNode(1).incrementalUpdateDone(Some(root))
        IncrementalNode(2).incrementalUpdateDone(Some(root))
        IncrementalNode(3).incrementalUpdateDone(Some(root))
        @Assert(root.kind == 0)
        @Assert(root.parent.isNone())
        @Assert(root.firstChild.isSome())
        if(let Some(firstChild) <- root.firstChild) {
            @Assert(firstChild.kind == 1)
            @Assert(firstChild.nextSibling.isSome())
            if (let Some(secondChild) <- firstChild.nextSibling) {
                @Assert(secondChild.kind == 2)
            }
        }
    }
    @TestCase
    public func performance(): Unit {
        let root = IncrementalNode(0)
        for (x in 0..1000000) {
            IncrementalNode(1).incrementalUpdateDone(Some(root))
        }
    }
}
