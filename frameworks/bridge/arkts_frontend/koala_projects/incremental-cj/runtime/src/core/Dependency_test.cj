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

class MyDep <: Dependency {
    protected func disposeImpl() {
        println("disposed")
    }
    public func toString(): String {
        "MyDep: ${this.hashCode()}"
    }
    public func invalidate() {
        @Assert(!this.isDisposed())
        println("invalidated")
    }
}

@Test
public class DependenciesTest {
    @TestCase
    public func checkDifferentInstances(): Unit {
        let dep1 = MyDep()
        let dep2 = MyDep()
        @Assert(dep1 != dep2)
    }
    @TestCase
    public func checkUnregisterDisposed(): Unit {
        let dep = MyDep()
        let deps = Dependencies()

        deps.register(None)
        @Assert(deps.empty)

        deps.register(dep)
        @Assert(!deps.empty)

        deps.onUpdate(true)
        @Assert(!deps.empty)

        dep.dispose()
        deps.onUpdate(false)
        @Assert(!deps.empty)

        deps.onUpdate(true)
        @Assert(deps.empty)
    }
}
