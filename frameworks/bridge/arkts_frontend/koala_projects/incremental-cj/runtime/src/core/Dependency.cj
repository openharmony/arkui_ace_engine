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

import KoalaRuntime.util.*

import std.collection.*

const SKIP_FRAMES: UInt8 = 10

/** This interface represents an unique observer that can be notified that some changes. */
public abstract class Dependency <: UniqueObject & Equatable<Dependency> {
    public operator func ==(that: Dependency): Bool {
        super == that
    }
    public operator func !=(that: Dependency): Bool {
        super != that
    }

    /** Notifies the dependency that it should be invalidated. */
    public func invalidate(): Unit
}

/** This class allows to store and update all dependencies. */
public class Dependencies {
    private var frame: UInt8 = 0
    private var dependencies = None<HashSet<Dependency>>
    private var latest = None<Dependency>

    /** Returns `true` if there are no dependencies to invalidate. */
    public prop empty: Bool {
        get() {
            if (let Some(dependencies) <- this.dependencies) {
                dependencies.isEmpty()
            } else {
                this.latest.isNone()
            }
        }
    }

    /**
     * Registers current dependencies to invalidate later.
     * Must be called when accessing a dependencies holder.
     */
    public func onAccess(): Unit {
        GlobalStateManager.register(this)
    }

    /** @param dependency - a dependency to invalidate later */
    func register(dependency: ?Dependency): Unit {
        if (let Some(dependency) <- dependency) {
            if (dependency.isDisposed()) {
                return
            }
            if (let Some(latest) <- this.latest) {
                if (latest == dependency) {
                    return
                }
                if (let Some(dependencies) <- this.dependencies) {
                    dependencies.add(dependency)
                } else {
                    let set = HashSet<Dependency>()
                    set.add(latest)
                    set.add(dependency)
                    this.dependencies = set
                }
            }
            this.latest = dependency
        }
    }

    /**
     * Processes all registered dependencies and removes disposed ones.
     * Must be called when updating a dependencies holder.
     * @param invalidate - specifies whether to invalidate all dependencies or not
     */
    public func onUpdate(invalidate: Bool): Unit {
        this.frame++
        if (this.frame < SKIP_FRAMES && !invalidate) {
            return
        }
        this.frame = 0
        if (let Some(dependencies) <- this.dependencies) {
            dependencies.removeIf {dependency => !updateDependency(invalidate, dependency)}
        } else if (let Some(latest) <- this.latest) {
            if (!updateDependency(invalidate, latest)) {
                this.latest = None
            }
        }
    }
}

func updateDependency(invalidate: Bool, dependency: Dependency): Bool {
    if (dependency.isDisposed()) {
        return false
    }
    if (invalidate) {
        dependency.invalidate()
    }
    return true
}
