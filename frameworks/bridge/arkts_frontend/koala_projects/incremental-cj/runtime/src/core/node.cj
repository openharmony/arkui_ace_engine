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

/**
 * @param create - the node constructor is invoked only once,
 *                 then the created node is attached to the hierarchy
 * @memo:intrinsic
 */
public func NodeAttach<TreeNode>(create: () -> TreeNode): Unit where TreeNode <: IncrementalNode {
    getMemoScope(getCallsiteKey(), 0, create, EMPTY_RUNNABLE, None, false).getValue()
}

/**
 * @param create - the node constructor is invoked only once,
 *                 then the created node is attached to the hierarchy
 * @param update - the node updater is invoked right after the node constructor,
 *                 than it can be invoked again if the values of the used states have changed
 * @memo:intrinsic
 */
public func NodeAttach<TreeNode>(create: () -> TreeNode, update: () -> Unit): Unit where TreeNode <: IncrementalNode {
    getMemoScope(getCallsiteKey(), 0, create, update, None, false).getValue()
}

/**
 * @param kind - expected kind of current node
 * @param getErrorMessage - supplier of an error message
 * @returns current node of the specified type
 * @throws Error with the given error message if expected node is not found
 * @memo:intrinsic
 */
public func contextNode<TreeNode>(kind: UInt32, getErrorMessage: () -> String): TreeNode where TreeNode <: IncrementalNode {
    let node = contextNode<TreeNode>(getErrorMessage)
    if (node.isKind(kind)) {
        return node
    } else {
        throw IllegalStateException("context node has unexpected kind ${kind}: ${getErrorMessage()}")
    }
}

/**
 * @param getErrorMessage - supplier of an error message
 * @returns current node of the specified type
 * @throws Error with the given error message if expected node is not found
 * @memo:intrinsic
 */
public func contextNode<TreeNode>(getErrorMessage: () -> String): TreeNode where TreeNode <: IncrementalNode {
    if (let Some(node) <- getManagedScope(getErrorMessage).nodeRef) {
        if (let Some(node) <- (node as TreeNode)) {
            return node
        } else {
            throw IllegalStateException("context node has unexpected type: ${getErrorMessage()}")
        }
    } else {
        throw IllegalStateException("context node not found: ${getErrorMessage()}")
    }
}

/**
 * @param kind - expected kind of current node
 * @returns current node of the specified type or None if expected node is not found
 * @memo:intrinsic
 */
public func contextNode<TreeNode>(kind: UInt32): ?TreeNode where TreeNode <: IncrementalNode {
    if (let Some(node) <- contextNode<TreeNode>()) {
        if (node.isKind(kind)) {
            return node
        }
    }
    None
}

/**
 * @returns current node of the specified type or None if expected node is not found
 * @memo:intrinsic
 */
public func contextNode<TreeNode>(): ?TreeNode where TreeNode <: IncrementalNode {
    if (let Some(node) <- getManagedScope {"context node access"}.nodeRef) {
        return node as TreeNode
    }
    None
}
