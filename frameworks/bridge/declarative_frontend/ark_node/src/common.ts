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

function __establishConnection__(allow: boolean, parentView: ViewBuildNodeBase | undefined, builderIds: Array<number>): boolean {
    if (!parentView) {
        return false;
    }
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
        builderNode.__parentViewOfBuildNode = new WeakRef(parentView);
        parentView?.addChildBuilderNode(builderNode);
    });
    return true;
}

function __disconnectConnection__(parentView: ViewBuildNodeBase | undefined, builderIds: Array<number>): boolean {
    if (!parentView) {
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
        builderNode.__parentViewOfBuildNode = undefined;
        parentView?.removeChildBuilderNode(builderId);
    });
    return true;
}

globalThis.__addBuilderNode__ = function __addBuilderNode__(id: number, builderIds: Array<number>): boolean {
    let view = UINodeRegisterProxy.GetView(id);
    if (!view || !(view instanceof PUV2ViewBase)) {
        globalThis.__addBuilderNodeToBuilder__(id, builderIds);
        return false;
    }
    return __establishConnection__((view as PUV2ViewBase).isCompFreezeAllowed(), view as PUV2ViewBase, builderIds);
}

globalThis.__deleteBuilderNode__ = function __deleteBuilderNode__(id: number, builderIds: Array<number>): boolean {
    return __disconnectConnection__(UINodeRegisterProxy.GetViewBuildNodeBase(id), builderIds)
}

globalThis.__addBuilderNodeToBuilder__ = function __addBuilderNodeToBuilder__(id: number, builderIds: Array<number>): boolean {
    let builderNode = UINodeRegisterProxy.GetViewBuildNodeBase(id);
    if (!builderNode || !(builderNode instanceof JSBuilderNode)) {
        return false;
    }
    return __establishConnection__((builderNode as JSBuilderNode).getAllowFreezeWhenInactive(), builderNode, builderIds);
}

globalThis.__deleteBuilderNodeFromBuilder__ = function __deleteBuilderNodeFromBuilder__(id: number, builderIds: Array<number>): boolean {
    return __disconnectConnection__(UINodeRegisterProxy.GetViewBuildNodeBase(id), builderIds)
}