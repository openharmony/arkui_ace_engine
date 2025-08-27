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
import KoalaRuntime.util.*

/**
 * This is a node implementation for a tree, which is represented as a pair of bidirectional lists.
 * It allows nodes to be added or removed incrementally using the state manager.
 */
public open class IncrementalNode <: UniqueObject & TreeNode<IncrementalNode> {
    private var childRef = None<IncrementalNode>
    private var prevRef = None<IncrementalNode>
    private var nextRef = None<IncrementalNode>
    private var parentRef = None<IncrementalNode>
    private var incrementalRef = None<IncrementalNode>

    /**
     * @param kind - the kind of this instance that can be used to distinguish nodes
     * @see isKind
     */
    public IncrementalNode(let kind: UInt32) {
    }

    /**
     * Use this method instead of standard instanceof for the sake of speed and reliability.
     * @param kind - a kind of this or parent instance to check against
     * @returns `true` if this node is an instance of the expected kind
     * @see PrimeNumbers
     */
    func isKind(kind: UInt32): Bool {
        return this.kind % kind == 0
    }

    /**
     * This method is called to remove this node from the hierarchy.
     */
    protected open func disposeImpl() {
        let prev = this.prevRef
        let next = this.nextRef
        let parent = this.parentRef
        this.childRef = None
        if (let Some(prev) <- prev) {
            this.prevRef = None
            prev.nextRef = next
        }
        if (let Some(next) <- next) {
            this.nextRef = None
            next.prevRef = prev
        }
        if (let Some(parent) <- parent) {
            this.parentRef = None
            if (let Some(child) <- parent.childRef) {
                if (refEq(child, this)) {
                    parent.childRef = next
                }
            }
            parent.onChildRemoved(this)
        }
    }

    /**
     * @returns text representation of the node
     */
    public func toString(): String {
        let sb = StringBuilder()
        this.toStringBuilder(sb)
        sb.toString()
    }

    public open func toStringBuilder(sb: StringBuilder): Unit {
        sb.append("IncrementalNode:")
        sb.append(this.kind)
    }

    /**
     * @returns a parent node if it is exist
     */
    public prop parent: ?IncrementalNode {
        get() {
            this.parentRef
        }
    }

    /**
     * @returns the first child node contained in this node if it is exist
     */
    public prop firstChild: ?IncrementalNode {
        get() {
            this.childRef
        }
    }

    /**
     * @returns the next sibling of this node if it is exist
     */
    public prop nextSibling: ?IncrementalNode {
        get() {
            this.nextRef
        }
    }

    /**
     * @returns the previous sibling of this node if it is exist
     */
    public prop previousSibling: ?IncrementalNode {
        get() {
            this.prevRef
        }
    }

    /**
     * This callback is called when a child node is added to this parent.
     */
    protected open func onChildInserted(_: IncrementalNode): Unit {
    }

    /**
     * This callback is called when a child node is removed from this parent.
     */
    protected open func onChildRemoved(_: IncrementalNode): Unit {
    }

    /**
     * This method is called by the state manager
     * when the incremental update should skip several unchanged child nodes.
     * @param count - a number of child nodes to skip during the incremental update
     * @internal
     */
    func incrementalUpdateSkip(count: UInt32) {
        if (count > 0) {
            let prev = this.incrementalRef
            var next = if (let Some(prev) <- prev) {
                prev.nextRef
            } else {
                this.childRef
            }
            for (_ in 1..count) {
                next = if (let Some(next) <- next) {
                    next.nextRef
                } else {
                    throw IllegalStateException("child node is expected here")
                }
            }
            this.incrementalRef = next
        } else {
            throw IllegalArgumentException("unexpected count of child nodes to skip: ${count}")
        }
    }

    /**
     * This method is called by the state manager
     * when the incremental update of all children of this node is completed.
     * @internal
     */
    func incrementalUpdateDone(parent: ?IncrementalNode) {
        if (this.isDisposed()) {
            throw IllegalStateException("child node is already disposed")
        }
        this.incrementalRef = None
        if (let Some(parent) <- parent) {
            let prev = parent.incrementalRef
            let next = if (let Some(prev) <- prev) {
                prev.nextRef
            } else {
                parent.childRef
            }
            if (let Some(existing) <- this.parentRef) {
                if (!refEq(existing, parent)) {
                    throw IllegalStateException("child node belongs to another parent")
                }
                if (next.isNone() || !refEq(this, next.getOrThrow())) {
                    throw IllegalStateException("child node is not expected here")
                }
                parent.incrementalRef = this
            } else {
                parent.incrementalRef = this
                this.prevRef = prev
                this.nextRef = next
                this.parentRef = parent
                if (let Some(next) <- next) {
                    next.prevRef = this
                }
                if (let Some(prev) <- prev) {
                    prev.nextRef = this
                } else {
                    parent.childRef = this
                }
                parent.onChildInserted(this)
            }
        }
    }
}
