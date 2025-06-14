/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * Check if the node has parent View.
 * @param nodeId id of node, obtained on the c++ side.
 * @returns true if the node has parent View.
 */
globalThis.__hasParentView__ = function __hasParentView__(nodeId: number): boolean {
    let view = UINodeRegisterProxy.GetView(nodeId);
    if (view) {
      return true;
    }
    return false;
}

globalThis.__addBuilderNode__ = function __addBuilderNode__(id: number, builderIds: Array<number>): boolean {
    let view = UINodeRegisterProxy.GetView(id);
    if (!view) {
        return false;
    }
    let allow = view.isCompFreezeAllowed();
    builderIds.forEach((builderId, indx) => {
        let builderNodePtr = FrameNodeFinalizationRegisterProxy.rootFrameNodeIdToBuilderNode_.get(builderId);
        let builderNode = builderNodePtr?.deref()?.getBuilderNode();
        if (!builderNode) {
            return false;
        }
        builderNode.setParentAllowFreeze(allow);
        if (builderNode.getInheritFreeze()) {
            builderNode.setAllowFreezeWhenInactive(allow);
        }
        view.addChildBuilderNode(builderNode);
    });
    return true;
}

globalThis.__deleteBuilderNode__ = function __deleteBuilderNode__(id: number, builderIds: Array<number>): boolean {
    let view = UINodeRegisterProxy.GetView(id);
    if (!view) {
        return false;
    }
    builderIds.forEach((builderId, indx) => {
        let builderNodePtr = FrameNodeFinalizationRegisterProxy.rootFrameNodeIdToBuilderNode_.get(builderId);
        let builderNode = builderNodePtr?.deref()?.getBuilderNode();
        if (!builderNode) {
            return false;
        }
        builderNode.setParentAllowFreeze(false);
        builderNode.setAllowFreezeWhenInactive(false);
        if (builderNode.getIsFreeze()) {
            builderNode.setActiveInternal(true);
        }
        view.removeChildBuilderNode(builderId);
    });
    return true;
}

globalThis.__addBuilderNodeToBuilder__ = function __addBuilderNodeToBuilder__(id: number, builderIds: Array<number>): boolean {
    let builderNodePtr = FrameNodeFinalizationRegisterProxy.rootFrameNodeIdToBuilderNode_.get(id);
    let builderNode = builderNodePtr?.deref()?.getBuilderNode();
    if (!builderNode) {
        return false;
    }
    let allow = builderNode.getAllowFreezeWhenInactive();
    builderIds.forEach((builderId, indx) => {
        let childBuilderNodePtr = FrameNodeFinalizationRegisterProxy.rootFrameNodeIdToBuilderNode_.get(builderId);
        let childBuilderNode = childBuilderNodePtr?.deref()?.getBuilderNode();
        if (!childBuilderNode) {
            return false;
        }
        childBuilderNode.setParentAllowFreeze(allow);
        if (childBuilderNode.getInheritFreeze()) {
            childBuilderNode.setAllowFreezeWhenInactive(allow);
        }
        builderNode.addChildBuilderNode(childBuilderNode);
    });
    return true;
}

globalThis.__deleteBuilderNodeFromBuilder__ = function __deleteBuilderNodeFromBuilder__(id: number, builderIds: Array<number>): boolean {
    let builderNodePtr = FrameNodeFinalizationRegisterProxy.rootFrameNodeIdToBuilderNode_.get(id);
    let builderNode = builderNodePtr?.deref()?.getBuilderNode();
    if (!builderNode) {
        return false;
    }
    builderIds.forEach((builderId, indx) => {
        let childBuilderNodePtr = FrameNodeFinalizationRegisterProxy.rootFrameNodeIdToBuilderNode_.get(builderId);
        let childBuilderNode = childBuilderNodePtr?.deref()?.getBuilderNode();
        if (!childBuilderNode) {
            return false;
        }
        childBuilderNode.setParentAllowFreeze(false);
        childBuilderNode.setAllowFreezeWhenInactive(false);
        if (builderNode.getIsFreeze()) {
            builderNode.setActiveInternal(true);
        }
        builderNode.removeChildBuilderNode(childBuilderNode.id__());
    });
    return true;
}

globalThis.__clearBuilderNodes__ = function __clearBuilderNodes__(id: number): boolean{
    let view = UINodeRegisterProxy.GetView(id);
    if (view) {
        for (const child of view.builderNodeWeakrefMap_.values()) {
            child.deref()?.setParentAllowFreeze(false);
            child.deref()?.setAllowFreezeWhenInactive(false);
            if (child?.deref()?.getIsFreeze()) {
                child?.deref()?.setActiveInternal(true);
            }
        }
        view.clearChildBuilderNode();
        return true;
    }
    return false;
}

globalThis.__clearFromBuilder__ = function __clearFromBuilder__(id: number): boolean {
    let builderNodePtr = FrameNodeFinalizationRegisterProxy.rootFrameNodeIdToBuilderNode_.get(id);
    let builderNode = builderNodePtr?.deref()?.getBuilderNode();
    if (!builderNode) {
        return false;
    }
    for (const child of builderNode.builderNodeWeakrefMap_.values()) {
        child.deref()?.setParentAllowFreeze(false);
        child.deref()?.setAllowFreezeWhenInactive(false);
        if (child?.deref()?.getIsFreeze()) {
            child?.deref()?.setActiveInternal(true);
        }
    }
    builderNode.clearChildBuilderNode();
    return true;
}