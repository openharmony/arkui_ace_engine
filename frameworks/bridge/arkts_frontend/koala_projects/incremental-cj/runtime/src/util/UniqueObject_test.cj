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
package KoalaRuntime.util

import std.collection.*

class SimpleUniqueObject <: UniqueObject {
    protected func disposeImpl() {
        println("SimpleUniqueObject is disposed")
    }

    public func toString(): String {
        "SimpleUniqueObject: ${this.hashCode()}"
    }
}

class EquatableUniqueObject <: UniqueObject & Equatable<EquatableUniqueObject> {
    protected func disposeImpl() {
        println("EquatableUniqueObject is disposed")
    }

    public func toString(): String {
        "EquatableUniqueObject: ${this.hashCode()}"
    }

    public operator func ==(that: EquatableUniqueObject): Bool {
        super == that
    }

    public operator func !=(that: EquatableUniqueObject): Bool {
        super != that
    }
}

@Test
public class UniqueObjectTest {
    @TestCase
    public func checkSimpleUniqueObject(): Unit {
        let o1 = SimpleUniqueObject()
        @Assert(o1 == o1)
        let o2 = SimpleUniqueObject()
        @Assert(o1 != o2)
        let diff = o2.hashCode() - o1.hashCode()
        @Assert(diff == 1)
        let set = HashSet<UniqueObject>([o1])
        @Assert(set.contains(o1))
        @Assert(!set.contains(o2))
    }
    @TestCase
    public func checkEquatableUniqueObject(): Unit {
        let o1 = EquatableUniqueObject()
        @Assert(o1 == o1)
        let o2 = EquatableUniqueObject()
        @Assert(o1 != o2)
        let diff = o2.hashCode() - o1.hashCode()
        @Assert(diff == 1)
        let set = HashSet<EquatableUniqueObject>([o1])
        @Assert(set.contains(o1))
        @Assert(!set.contains(o2))
    }
}
