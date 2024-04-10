/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
var NodeRenderType;
(function (NodeRenderType) {
    NodeRenderType[NodeRenderType["RENDER_TYPE_DISPLAY"] = 0] = "RENDER_TYPE_DISPLAY";
    NodeRenderType[NodeRenderType["RENDER_TYPE_TEXTURE"] = 1] = "RENDER_TYPE_TEXTURE";
})(NodeRenderType || (NodeRenderType = {}));
class BaseNode extends __JSBaseNode__ {
    constructor(uiContext, options) {
        super(options);
        let instanceId = -1;
        if (uiContext === undefined) {
            throw Error('Node constructor error, param uiContext error');
        }
        else {
            if (!(typeof uiContext === "object") || !("instanceId_" in uiContext)) {
                throw Error('Node constructor error, param uiContext is invalid');
            }
            instanceId = uiContext.instanceId_;
        }
        this.instanceId_ = instanceId;
    }
    getInstanceId() {
        return this.instanceId_;
    }
}
/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
/// <reference path="../../state_mgmt/src/lib/common/ifelse_native.d.ts" />
/// <reference path="../../state_mgmt/src/lib/partial_update/pu_viewstack_processor.d.ts" />
class BuilderNode {
    constructor(uiContext, options) {
        let jsBuilderNode = new JSBuilderNode(uiContext, options);
        this._JSBuilderNode = jsBuilderNode;
        let id = Symbol('BuilderNode');
        BuilderNodeFinalizationRegisterProxy.ElementIdToOwningBuilderNode_.set(id, jsBuilderNode);
        BuilderNodeFinalizationRegisterProxy.register(this, { name: 'BuilderNode', idOfNode: id });
    }
    update(params) {
        this._JSBuilderNode.update(params);
    }
    build(builder, params) {
        this._JSBuilderNode.build(builder, params);
        this.nodePtr_ = this._JSBuilderNode.getNodePtr();
    }
    getFrameNode() {
        return this._JSBuilderNode.getFrameNode();
    }
    postTouchEvent(touchEvent) {
        return this._JSBuilderNode.postTouchEvent(touchEvent);
    }
    dispose() {
        this._JSBuilderNode.dispose();
    }
}
class JSBuilderNode extends BaseNode {
    constructor(uiContext, options) {
        super(uiContext, options);
        this.childrenWeakrefMap_ = new Map();
        this.uiContext_ = uiContext;
        this.updateFuncByElmtId = new Map();
    }
    getCardId() {
        return -1;
    }
    addChild(child) {
        if (this.childrenWeakrefMap_.has(child.id__())) {
            return false;
        }
        this.childrenWeakrefMap_.set(child.id__(), new WeakRef(child));
        return true;
    }
    getChildById(id) {
        const childWeakRef = this.childrenWeakrefMap_.get(id);
        return childWeakRef ? childWeakRef.deref() : undefined;
    }
    updateStateVarsOfChildByElmtId(elmtId, params) {
        if (elmtId < 0) {
            return;
        }
        let child = this.getChildById(elmtId);
        if (!child) {
            return;
        }
        child.updateStateVars(params);
    }
    createOrGetNode(elmtId, builder) {
        const entry = this.updateFuncByElmtId.get(elmtId);
        if (entry === undefined) {
            throw new Error(`fail to create node, elmtId is illegal`);
        }
        let updateFuncRecord = (typeof entry === 'object') ? entry : undefined;
        if (updateFuncRecord === undefined) {
            throw new Error(`fail to create node, the api level of app does not supported`);
        }
        let nodeInfo = updateFuncRecord.node;
        if (nodeInfo === undefined) {
            nodeInfo = builder();
            updateFuncRecord.node = nodeInfo;
        }
        return nodeInfo;
    }
    build(builder, params) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        this.params_ = params;
        this.updateFuncByElmtId.clear();
        this.nodePtr_ = super.create(builder.builder, this.params_);
        if (this.frameNode_ === undefined || this.frameNode_ === null) {
            this.frameNode_ = new FrameNode(this.uiContext_, 'BuilderNode');
        }
        this.frameNode_.setNodePtr(this.nodePtr_);
        this.frameNode_.setBaseNode(this);
        __JSScopeUtil__.restoreInstanceId();
    }
    update(param) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        this.updateStart();
        this.purgeDeletedElmtIds();
        this.params_ = param;
        Array.from(this.updateFuncByElmtId.keys()).sort((a, b) => {
            return (a < b) ? -1 : (a > b) ? 1 : 0;
        }).forEach(elmtId => this.UpdateElement(elmtId));
        this.updateEnd();
        __JSScopeUtil__.restoreInstanceId();
    }
    UpdateElement(elmtId) {
        // do not process an Element that has been marked to be deleted
        const obj = this.updateFuncByElmtId.get(elmtId);
        const updateFunc = (typeof obj === 'object') ? obj.updateFunc : null;
        if (typeof updateFunc === 'function') {
            updateFunc(elmtId, /* isFirstRender */ false);
            this.finishUpdateFunc();
        }
    }
    purgeDeletedElmtIds() {
        UINodeRegisterProxy.obtainDeletedElmtIds();
        UINodeRegisterProxy.unregisterElmtIdsFromViewPUs();
    }
    purgeDeleteElmtId(rmElmtId) {
        const result = this.updateFuncByElmtId.delete(rmElmtId);
        if (result) {
            UINodeRegisterProxy.ElementIdToOwningViewPU_.delete(rmElmtId);
        }
        return result;
    }
    getFrameNode() {
        if (this.frameNode_ !== undefined &&
            this.frameNode_ !== null &&
            this.frameNode_.getNodePtr() !== null) {
            return this.frameNode_;
        }
        return null;
    }
    observeComponentCreation(func) {
        let elmId = ViewStackProcessor.AllocateNewElmetIdForNextComponent();
        UINodeRegisterProxy.ElementIdToOwningViewPU_.set(elmId, new WeakRef(this));
        try {
            func(elmId, true);
        }
        catch (error) {
            // avoid the incompatible change that move set function before updateFunc.
            UINodeRegisterProxy.ElementIdToOwningViewPU_.delete(elmId);
            throw error;
        }
    }
    observeComponentCreation2(compilerAssignedUpdateFunc, classObject) {
        const _componentName = classObject && 'name' in classObject ? Reflect.get(classObject, 'name') : 'unspecified UINode';
        const _popFunc = classObject && "pop" in classObject ? classObject.pop : () => { };
        const updateFunc = (elmtId, isFirstRender) => {
            __JSScopeUtil__.syncInstanceId(this.instanceId_);
            ViewStackProcessor.StartGetAccessRecordingFor(elmtId);
            compilerAssignedUpdateFunc(elmtId, isFirstRender, this.params_);
            if (!isFirstRender) {
                _popFunc();
            }
            ViewStackProcessor.StopGetAccessRecording();
            __JSScopeUtil__.restoreInstanceId();
        };
        const elmtId = ViewStackProcessor.AllocateNewElmetIdForNextComponent();
        // needs to move set before updateFunc.
        // make sure the key and object value exist since it will add node in attributeModifier during updateFunc.
        this.updateFuncByElmtId.set(elmtId, {
            updateFunc: updateFunc,
            componentName: _componentName,
        });
        UINodeRegisterProxy.ElementIdToOwningViewPU_.set(elmtId, new WeakRef(this));
        try {
            updateFunc(elmtId, /* is first render */ true);
        }
        catch (error) {
            // avoid the incompatible change that move set function before updateFunc.
            this.updateFuncByElmtId.delete(elmtId);
            UINodeRegisterProxy.ElementIdToOwningViewPU_.delete(elmtId);
            throw error;
        }
    }
    /**
     Partial updates for ForEach.
     * @param elmtId ID of element.
     * @param itemArray Array of items for use of itemGenFunc.
     * @param itemGenFunc Item generation function to generate new elements. If index parameter is
     *                    given set itemGenFuncUsesIndex to true.
     * @param idGenFunc   ID generation function to generate unique ID for each element. If index parameter is
     *                    given set idGenFuncUsesIndex to true.
     * @param itemGenFuncUsesIndex itemGenFunc optional index parameter is given or not.
     * @param idGenFuncUsesIndex idGenFunc optional index parameter is given or not.
     */
    forEachUpdateFunction(elmtId, itemArray, itemGenFunc, idGenFunc, itemGenFuncUsesIndex = false, idGenFuncUsesIndex = false) {
        if (itemArray === null || itemArray === undefined) {
            return;
        }
        if (itemGenFunc === null || itemGenFunc === undefined) {
            return;
        }
        if (idGenFunc === undefined) {
            idGenFuncUsesIndex = true;
            // catch possible error caused by Stringify and re-throw an Error with a meaningful (!) error message
            idGenFunc = (item, index) => {
                try {
                    return `${index}__${JSON.stringify(item)}`;
                }
                catch (e) {
                    throw new Error(` ForEach id ${elmtId}: use of default id generator function not possible on provided data structure. Need to specify id generator function (ForEach 3rd parameter). Application Error!`);
                }
            };
        }
        let diffIndexArray = []; // New indexes compared to old one.
        let newIdArray = [];
        let idDuplicates = [];
        const arr = itemArray; // just to trigger a 'get' onto the array
        // ID gen is with index.
        if (idGenFuncUsesIndex) {
            // Create array of new ids.
            arr.forEach((item, indx) => {
                newIdArray.push(idGenFunc(item, indx));
            });
        }
        else {
            // Create array of new ids.
            arr.forEach((item, index) => {
                newIdArray.push(`${itemGenFuncUsesIndex ? index + "_" : ""}` + idGenFunc(item));
            });
        }
        // Set new array on C++ side.
        // C++ returns array of indexes of newly added array items.
        // these are indexes in new child list.
        ForEach.setIdArray(elmtId, newIdArray, diffIndexArray, idDuplicates);
        // Item gen is with index.
        diffIndexArray.forEach((indx) => {
            ForEach.createNewChildStart(newIdArray[indx], this);
            if (itemGenFuncUsesIndex) {
                itemGenFunc(arr[indx], indx);
            }
            else {
                itemGenFunc(arr[indx]);
            }
            ForEach.createNewChildFinish(newIdArray[indx], this);
        });
    }
    ifElseBranchUpdateFunction(branchId, branchfunc) {
        const oldBranchid = If.getBranchId();
        if (branchId === oldBranchid) {
            return;
        }
        // branchId identifies uniquely the if .. <1> .. else if .<2>. else .<3>.branch
        // ifElseNode stores the most recent branch, so we can compare
        // removedChildElmtIds will be filled with the elmtIds of all children and their children will be deleted in response to if .. else change
        let removedChildElmtIds = new Array();
        If.branchId(branchId, removedChildElmtIds);
        this.purgeDeletedElmtIds();
        branchfunc();
    }
    getNodePtr() {
        return this.nodePtr_;
    }
    dispose() {
        this.nodePtr_ = null;
        super.dispose();
        if (this.frameNode_ !== undefined && this.frameNode_ !== null) {
            this.frameNode_.setNodePtr(null);
        }
    }
}
/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
class BuilderNodeFinalizationRegisterProxy {
    constructor() {
        this.finalizationRegistry_ = new FinalizationRegistry((heldValue) => {
            if (heldValue.name === 'BuilderNode') {
                const builderNode = BuilderNodeFinalizationRegisterProxy.ElementIdToOwningBuilderNode_.get(heldValue.idOfNode);
                BuilderNodeFinalizationRegisterProxy.ElementIdToOwningBuilderNode_.delete(heldValue.idOfNode);
                builderNode.dispose();
            }
        });
    }
    static register(target, heldValue) {
        BuilderNodeFinalizationRegisterProxy.instance_.finalizationRegistry_.register(target, heldValue);
    }
}
BuilderNodeFinalizationRegisterProxy.instance_ = new BuilderNodeFinalizationRegisterProxy();
BuilderNodeFinalizationRegisterProxy.ElementIdToOwningBuilderNode_ = new Map();
class FrameNodeFinalizationRegisterProxy {
    constructor() {
        this.finalizationRegistry_ = new FinalizationRegistry((heldValue) => {
            FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.delete(heldValue);
        });
    }
    static register(target, heldValue) {
        FrameNodeFinalizationRegisterProxy.instance_.finalizationRegistry_.register(target, heldValue);
    }
}
FrameNodeFinalizationRegisterProxy.instance_ = new FrameNodeFinalizationRegisterProxy();
FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_ = new Map();
FrameNodeFinalizationRegisterProxy.FrameNodeInMainTree_ = new Map();
globalThis.__AttachToMainTree__ = function __AttachToMainTree__(nodeId) {
    if (FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.has(nodeId)) {
        FrameNodeFinalizationRegisterProxy.FrameNodeInMainTree_.set(nodeId, FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.get(nodeId).deref());
    }
};
globalThis.__DetachToMainTree__ = function __DetachToMainTree__(nodeId) {
    FrameNodeFinalizationRegisterProxy.FrameNodeInMainTree_.delete(nodeId);
};
/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
class __InternalField__ {
    constructor() {
        this._value = -1;
    }
}
class NodeController {
    constructor() {
        this._nodeContainerId = new __InternalField__();
    }
    rebuild() {
        if (this._nodeContainerId != undefined && this._nodeContainerId !== null && this._nodeContainerId._value >= 0) {
            getUINativeModule().nodeContainer.rebuild(this._nodeContainerId._value);
        }
    }
}
/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
class FrameNodeAttributeMap {
    constructor() {
        this.map_ = new Map();
    }
    clear() {
        this.map_.clear();
    }
    delete(key) {
        return this.map_.delete(key);
    }
    forEach(callbackfn, thisArg) {
        this.map_.forEach(callbackfn, thisArg);
    }
    get(key) {
        return this.map_.get(key);
    }
    has(key) {
        return this.map_.has(key);
    }
    set(key, value) {
        const _a = this.changeCallback;
        this.map_.set(key, value);
        _a === null || _a === void 0 ? void 0 : _a(key, value);
        return this;
    }
    get size() {
        return this.map_.size;
    }
    entries() {
        return this.map_.entries();
    }
    keys() {
        return this.map_.keys();
    }
    values() {
        return this.map_.values();
    }
    [Symbol.iterator]() {
        return this.map_.entries();
    }
    get [Symbol.toStringTag]() {
        return 'FrameNodeAttributeMapTag';
    }
    setOnChange(callback) {
        if (this.changeCallback === undefined) {
            this.changeCallback = callback;
        }
    }
}
class FrameNodeModifier extends ArkComponent {
    constructor(nodePtr) {
        super(nodePtr);
        this._modifiersWithKeys = new FrameNodeAttributeMap();
        this._modifiersWithKeys.setOnChange((key, value) => {
            if (this.nativePtr === undefined) {
                return;
            }
            value.applyStage(this.nativePtr);
            getUINativeModule().frameNode.propertyUpdate(this.nativePtr);
        });
    }
    setNodePtr(nodePtr) {
        this.nativePtr = nodePtr;
    }
}
class FrameNode {
    constructor(uiContext, type) {
        this.uiContext_ = uiContext;
        this.nodeId_ = -1;
        this._childList = new Map();
        if (type === 'BuilderNode' || type === 'ArkTsNode') {
            this.renderNode_ = new RenderNode('BuilderNode');
            this.type_ = type;
            return;
        }
        this.renderNode_ = new RenderNode('FrameNode');
        this.baseNode_ = new BaseNode(uiContext);
        this.nodePtr_ = this.baseNode_.createFrameNode(this);
        this.nodeId_ = getUINativeModule().frameNode.getIdByNodePtr(this.nodePtr_);
        FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.set(this.nodeId_, new WeakRef(this));
        FrameNodeFinalizationRegisterProxy.register(this, this.nodeId_);
        this.renderNode_.setNodePtr(this.nodePtr_);
        this.renderNode_.setBaseNode(this.baseNode_);
    }
    getRenderNode() {
        if (this.renderNode_ !== undefined &&
            this.renderNode_ !== null &&
            this.renderNode_.getNodePtr() !== null && this.type_ !== 'ArkTsNode') {
            return this.renderNode_;
        }
        return null;
    }
    setNodePtr(nodePtr) {
        this.renderNode_.setNodePtr(nodePtr);
        if (nodePtr === null) {
            FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.delete(this.nodeId_);
            this.nodeId_ = -1;
            this.nodePtr_ = null;
            return;
        }
        this.nodePtr_ = nodePtr;
        this.nodeId_ = getUINativeModule().frameNode.getIdByNodePtr(this.nodePtr_);
        if (this.nodeId_ === -1) {
            return;
        }
        FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.set(this.nodeId_, new WeakRef(this));
        FrameNodeFinalizationRegisterProxy.register(this, this.nodeId_);
    }
    setBaseNode(baseNode) {
        this.baseNode_ = baseNode;
        this.renderNode_.setBaseNode(baseNode);
    }
    getNodePtr() {
        return this.nodePtr_;
    }
    dispose() {
        this.baseNode_.dispose();
        FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.delete(this.nodeId_);
        this.nodeId_ = -1;
        this.nodePtr_ = null;
    }
    checkType() {
        if (!getUINativeModule().frameNode.isModifiable(this.nodePtr_)) {
            throw { message: 'The FrameNode is not modifiable.', code: 100021 };
        }
    }
    isModifiable() {
        return getUINativeModule().frameNode.isModifiable(this.nodePtr_);
    }
    convertToFrameNode(nodePtr) {
        var nodeId = getUINativeModule().frameNode.getIdByNodePtr(nodePtr);
        if (nodeId !== -1 && !getUINativeModule().frameNode.isModifiable(nodePtr)) {
            var frameNode = new FrameNode(this.uiContext_, 'ArkTsNode');
            var baseNode = new BaseNode(this.uiContext_);
            var node = baseNode.convertToFrameNode(nodePtr);
            if (nodeId !== getUINativeModule().frameNode.getIdByNodePtr(node)) {
                return null;
            }
            frameNode.setNodePtr(nodePtr);
            frameNode.setBaseNode(baseNode);
            frameNode.uiContext_ = this.uiContext_;
            frameNode.nodeId_ = nodeId;
            FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.set(frameNode.nodeId_, new WeakRef(frameNode));
            FrameNodeFinalizationRegisterProxy.register(frameNode, frameNode.nodeId_);
            return frameNode;
        }
        return null;
    }
    appendChild(node) {
        this.checkType();
        if (node === undefined || node === null) {
            return;
        }
        if (node.type_ === 'ArkTsNode') {
            throw { message: 'The FrameNode is not modifiable.', code: 100021 };
        }
        let flag = getUINativeModule().frameNode.appendChild(this.nodePtr_, node.nodePtr_);
        if (!flag) {
            throw { message: 'The FrameNode is not modifiable.', code: 100021 };
        }
        this._childList.set(node.nodeId_, node);
    }
    insertChildAfter(child, sibling) {
        this.checkType();
        if (child === undefined || child === null) {
            return;
        }
        if (child.type_ === 'ArkTsNode') {
            throw { message: 'The FrameNode is not modifiable.', code: 100021 };
        }
        let flag = true;
        if (sibling === undefined || sibling === null) {
            flag = getUINativeModule().frameNode.insertChildAfter(this.nodePtr_, child.nodePtr_, null);
        }
        else {
            flag = getUINativeModule().frameNode.insertChildAfter(this.nodePtr_, child.nodePtr_, sibling.nodePtr_);
        }
        if (!flag) {
            throw { message: 'The FrameNode is not modifiable.', code: 100021 };
        }
        this._childList.set(child.nodeId_, child);
    }
    removeChild(node) {
        this.checkType();
        if (node === undefined || node === null) {
            return;
        }
        getUINativeModule().frameNode.removeChild(this.nodePtr_, node.nodePtr_);
        this._childList.delete(node.nodeId_);
    }
    clearChildren() {
        this.checkType();
        getUINativeModule().frameNode.clearChildren(this.nodePtr_);
        this._childList.clear();
    }
    getChild(index) {
        const nodePtr = getUINativeModule().frameNode.getChild(this.nodePtr_, index);
        var nodeId = getUINativeModule().frameNode.getIdByNodePtr(nodePtr);
        if (nodeId === -1) {
            return null;
        }
        if (FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.has(nodeId)) {
            var frameNode = FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.get(nodeId).deref();
            return frameNode === undefined ? null : frameNode;
        }
        return this.convertToFrameNode(nodePtr);
    }
    getFirstChild() {
        const nodePtr = getUINativeModule().frameNode.getFirst(this.nodePtr_);
        var nodeId = getUINativeModule().frameNode.getIdByNodePtr(nodePtr);
        if (nodeId === -1) {
            return null;
        }
        if (FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.has(nodeId)) {
            var frameNode = FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.get(nodeId).deref();
            return frameNode === undefined ? null : frameNode;
        }
        return this.convertToFrameNode(nodePtr);
    }
    getNextSibling() {
        const nodePtr = getUINativeModule().frameNode.getNextSibling(this.nodePtr_);
        var nodeId = getUINativeModule().frameNode.getIdByNodePtr(nodePtr);
        if (nodeId === -1) {
            return null;
        }
        if (FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.has(nodeId)) {
            var frameNode = FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.get(nodeId).deref();
            return frameNode === undefined ? null : frameNode;
        }
        return this.convertToFrameNode(nodePtr);
    }
    getPreviousSibling() {
        const nodePtr = getUINativeModule().frameNode.getPreviousSibling(this.nodePtr_);
        var nodeId = getUINativeModule().frameNode.getIdByNodePtr(nodePtr);
        if (nodeId === -1) {
            return null;
        }
        if (FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.has(nodeId)) {
            var frameNode = FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.get(nodeId).deref();
            return frameNode === undefined ? null : frameNode;
        }
        return this.convertToFrameNode(nodePtr);
    }
    getParent() {
        const nodePtr = getUINativeModule().frameNode.getParent(this.nodePtr_);
        var nodeId = getUINativeModule().frameNode.getIdByNodePtr(nodePtr);
        if (nodeId === -1) {
            return null;
        }
        if (FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.has(nodeId)) {
            var frameNode = FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.get(nodeId).deref();
            return frameNode === undefined ? null : frameNode;
        }
        return this.convertToFrameNode(nodePtr);
    }
    getChildrenCount() {
        const number = getUINativeModule().frameNode.getChildrenCount(this.nodePtr_);
        return number;
    }
    getPositionToParent() {
        const position = getUINativeModule().frameNode.getPositionToParent(this.nodePtr_);
        return { x: position[0], y: position[1] };
    }
    getPositionToWindow() {
        const position = getUINativeModule().frameNode.getPositionToWindow(this.nodePtr_);
        return { x: position[0], y: position[1] };
    }
    getMeasuredSize() {
        const size = getUINativeModule().frameNode.getMeasuredSize(this.nodePtr_);
        if (size) {
            return { width: size[0], height: size[1] };
        }
        return null;
      }
    getLayoutPosition() {
        const position = getUINativeModule().frameNode.getLayoutPosition(this.nodePtr_);
        if (position) {
            return { x: position[0], y: position[1] };
        }
        return null;
      }
    getUserConfigBorderWidth() {
        const borderWidth = getUINativeModule().frameNode.getConfigBorderWidth(this.nodePtr_);
        if (borderWidth) {
            return {
                top: new LengthMetric(borderWidth[0], borderWidth[1]),
                right: new LengthMetric(borderWidth[2], borderWidth[3]),
                bottom: new LengthMetric(borderWidth[4], borderWidth[5]),
                left: new LengthMetric(borderWidth[6], borderWidth[7])
              };
        }
        return null;
    }
    getUserConfigPadding() {
        const padding = getUINativeModule().frameNode.getConfigPadding(this.nodePtr_);
        if (padding) {
            return {
                top: new LengthMetric(padding[0], padding[1]),
                right: new LengthMetric(padding[2], padding[3]),
                bottom: new LengthMetric(padding[4], padding[5]),
                left: new LengthMetric(padding[6], padding[7])
              };
        }
        return null;
    }
    getUserConfigMargin() {
        const margin = getUINativeModule().frameNode.getConfigMargin(this.nodePtr_);
        if (margin) {
            return {
                top: new LengthMetric(margin[0], margin[1]),
                right: new LengthMetric(margin[2], margin[3]),
                bottom: new LengthMetric(margin[4], margin[5]),
                left: new LengthMetric(margin[6], margin[7])
              };
        }
        return null;
    }
    getUserConfigSize() {
        const size = getUINativeModule().frameNode.getConfigSize(this.nodePtr_);
        if (size) {
            return {
                width: new LengthMetric(size[0], size[1]),
                height: new LengthMetric(size[2], size[3])
            };
        }
        return null;
    }
    getId() {
        return getUINativeModule().frameNode.getId(this.nodePtr_);
    }
    getNodeType() {
        return getUINativeModule().frameNode.getNodeType(this.nodePtr_);
    }
    getOpacity() {
        return getUINativeModule().frameNode.getOpacity(this.nodePtr_);
    }
    isVisible() {
        return getUINativeModule().frameNode.isVisible(this.nodePtr_);
    }
    isClipToFrame() {
        return getUINativeModule().frameNode.isClipToFrame(this.nodePtr_);
    }
    isAttached() {
        return getUINativeModule().frameNode.isAttached(this.nodePtr_);
    }
    getInspectorInfo() {
        const inspectorInfoStr = getUINativeModule().frameNode.getInspectorInfo(this.nodePtr_);
        const inspectorInfo = JSON.parse(inspectorInfoStr);
        return inspectorInfo;
    }

    get commonAttribute() {
        if (this._commonAttribute === undefined) {
            this._commonAttribute = new FrameNodeModifier(this.nodePtr_);
        }
        this._commonAttribute.setNodePtr((this.type_ === 'BuilderNode' || this.type_ === 'ArkTsNode') ? undefined : this.nodePtr_);
        return this._commonAttribute;
    }
    get commonEvent() {
        if (this._commonEvent === undefined) {
            this._commonEvent = new UICommonEvent(this.nodePtr_);
        }
        this._commonEvent.setNodePtr(this.nodePtr_);
        this._commonEvent.setInstanceId((this.uiContext_ === undefined || this.uiContext_ === null) ? -1 : this.uiContext_.instanceId_);
        return this._commonEvent;
    }
}
class FrameNodeUtils {
    static searchNodeInRegisterProxy(nodePtr) {
        let nodeId = getUINativeModule().frameNode.getIdByNodePtr(nodePtr);
        if (nodeId === -1) {
            return null;
        }
        if (FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.has(nodeId)) {
            let frameNode = FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.get(nodeId).deref();
            return frameNode === undefined ? null : frameNode;
        }
        return null;
    }
    static createFrameNode(uiContext, nodePtr) {
        if (!getUINativeModule().frameNode.isModifiable(nodePtr)) {
            let frameNode = new FrameNode(uiContext, 'ArkTsNode');
            let baseNode = new BaseNode(uiContext);
            let node = baseNode.convertToFrameNode(nodePtr);
            let nodeId = getUINativeModule().frameNode.getIdByNodePtr(node);
            if (nodeId !== getUINativeModule().frameNode.getIdByNodePtr(node)) {
                return null;
            }
            frameNode.setNodePtr(nodePtr);
            frameNode.setBaseNode(baseNode);
            return frameNode;
        }
        return null;
    }
}
/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
var BorderStyle;
(function (BorderStyle) {
    BorderStyle[BorderStyle["SOLID"] = 0] = "SOLID";
    BorderStyle[BorderStyle["DASHED"] = 1] = "DASHED";
    BorderStyle[BorderStyle["DOTTED"] = 2] = "DOTTED";
    BorderStyle[BorderStyle["NONE"] = 3] = "NONE";
})(BorderStyle || (BorderStyle = {}));

var LengthUnit;
(function (LengthUnit) {
    LengthUnit[LengthUnit["PX"] = 0] = "PX";
    LengthUnit[LengthUnit["VP"] = 1] = "VP";
    LengthUnit[LengthUnit["FP"] = 2] = "FP";
    LengthUnit[LengthUnit["PERCENT"] = 3] = "PERCENT";
    LengthUnit[LengthUnit["LPX"] = 4] = "LPX";
})(LengthUnit || (LengthUnit = {}));

class LengthMetric {
    constructor(value, unit) {
        if (unit in LengthUnit) {
            this.unit = unit;
            this.value = value;
        } else {
            this.unit = LengthUnit.VP;
            this.value = 0;
        }
    }
    static px(value) {
        return new LengthMetric(value, LengthUnit.PX);
    }
    static vp(value) {
        return new LengthMetric(value, LengthUnit.VP);
    }
    static fp(value) {
        return new LengthMetric(value, LengthUnit.FP);
    }
    static percent(value) {
        return new LengthMetric(value, LengthUnit.PERCENT);
    }
    static lpx(value) {
        return new LengthMetric(value, LengthUnit.LPX);
    }
}
class ShapeMask {
    constructor() {
        this.rect = null;
        this.roundRect = null;
        this.circle = null;
        this.oval = null;
        this.path = null;
        this.fillColor = 0XFF000000;
        this.strokeColor = 0XFF000000;
        this.strokeWidth = 0;
    }
    setRectShape(rect) {
        this.rect = rect;
        this.roundRect = null;
        this.circle = null;
        this.oval = null;
        this.path = null;
    }
    setRoundRectShape(roundRect) {
        this.roundRect = roundRect;
        this.rect = null;
        this.circle = null;
        this.oval = null;
        this.path = null;
    }
    setCircleShape(circle) {
        this.circle = circle;
        this.rect = null;
        this.roundRect = null;
        this.oval = null;
        this.path = null;
    }
    setOvalShape(oval) {
        this.oval = oval;
        this.rect = null;
        this.circle = null;
        this.roundRect = null;
        this.path = null;
    }
    setCommandPath(path) {
        this.path = path;
        this.oval = null;
        this.rect = null;
        this.circle = null;
        this.roundRect = null;
    }
}
class RenderNode {
    constructor(type) {
        this.nodePtr = null;
        this.childrenList = [];
        this.parentRenderNode = null;
        this.backgroundColorValue = 0;
        this.clipToFrameValue = true;
        this.frameValue = { x: 0, y: 0, width: 0, height: 0 };
        this.opacityValue = 1.0;
        this.pivotValue = { x: 0.5, y: 0.5 };
        this.rotationValue = { x: 0, y: 0, z: 0 };
        this.scaleValue = { x: 1.0, y: 1.0 };
        this.shadowColorValue = 0;
        this.shadowOffsetValue = { x: 0, y: 0 };
        this.shadowAlphaValue = 0;
        this.shadowElevationValue = 0;
        this.shadowRadiusValue = 0;
        this.transformValue = [1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1];
        this.translationValue = { x: 0, y: 0 };
        if (type === 'BuilderNode' || type === 'FrameNode') {
            return;
        }
        this.baseNode_ = new __JSBaseNode__();
        this.baseNode_.draw = this.draw;
        this.nodePtr = this.baseNode_.createRenderNode(this);
        this.clipToFrame = true;
    }
    set backgroundColor(color) {
        this.backgroundColorValue = this.checkUndefinedOrNullWithDefaultValue(color, 0);
        getUINativeModule().renderNode.setBackgroundColor(this.nodePtr, this.backgroundColorValue);
    }
    set clipToFrame(useClip) {
        this.clipToFrameValue = this.checkUndefinedOrNullWithDefaultValue(useClip, true);
        getUINativeModule().renderNode.setClipToFrame(this.nodePtr, this.clipToFrameValue);
    }
    set frame(frame) {
        if (frame === undefined || frame === null) {
            this.frameValue = { x: 0, y: 0, width: 0, height: 0 };
        }
        else {
            this.size = { width: frame.width, height: frame.height };
            this.position = { x: frame.x, y: frame.y };
        }
    }
    set opacity(value) {
        this.opacityValue = this.checkUndefinedOrNullWithDefaultValue(value, 1.0);
        getUINativeModule().common.setOpacity(this.nodePtr, this.opacityValue);
    }
    set pivot(pivot) {
        if (pivot === undefined || pivot === null) {
            this.pivotValue = { x: 0.5, y: 0.5 };
        }
        else {
            this.pivotValue.x = this.checkUndefinedOrNullWithDefaultValue(pivot.x, 0.5);
            this.pivotValue.y = this.checkUndefinedOrNullWithDefaultValue(pivot.y, 0.5);
        }
        getUINativeModule().renderNode.setPivot(this.nodePtr, this.pivotValue.x, this.pivotValue.y);
    }
    set position(position) {
        if (position === undefined || position === null) {
            this.frameValue.x = 0;
            this.frameValue.y = 0;
        }
        else {
            this.frameValue.x = this.checkUndefinedOrNullWithDefaultValue(position.x, 0);
            this.frameValue.y = this.checkUndefinedOrNullWithDefaultValue(position.y, 0);
        }
        getUINativeModule().common.setPosition(this.nodePtr, this.frameValue.x, this.frameValue.y);
    }
    set rotation(rotation) {
        if (rotation === undefined || rotation === null) {
            this.rotationValue = { x: 0, y: 0, z: 0 };
        }
        else {
            this.rotationValue.x = this.checkUndefinedOrNullWithDefaultValue(rotation.x, 0);
            this.rotationValue.y = this.checkUndefinedOrNullWithDefaultValue(rotation.y, 0);
            this.rotationValue.z = this.checkUndefinedOrNullWithDefaultValue(rotation.z, 0);
        }
        getUINativeModule().renderNode.setRotation(this.nodePtr, this.rotationValue.x, this.rotationValue.y, this.rotationValue.z);
    }
    set scale(scale) {
        if (scale === undefined || scale === null) {
            this.scaleValue = { x: 1.0, y: 1.0 };
        }
        else {
            this.scaleValue.x = this.checkUndefinedOrNullWithDefaultValue(scale.x, 1.0);
            this.scaleValue.y = this.checkUndefinedOrNullWithDefaultValue(scale.y, 1.0);
        }
        getUINativeModule().renderNode.setScale(this.nodePtr, this.scaleValue.x, this.scaleValue.y);
    }
    set shadowColor(color) {
        this.shadowColorValue = this.checkUndefinedOrNullWithDefaultValue(color, 0);
        getUINativeModule().renderNode.setShadowColor(this.nodePtr, this.shadowColorValue);
    }
    set shadowOffset(offset) {
        if (offset === undefined || offset === null) {
            this.shadowOffsetValue = { x: 0, y: 0 };
        }
        else {
            this.shadowOffsetValue.x = this.checkUndefinedOrNullWithDefaultValue(offset.x, 0);
            this.shadowOffsetValue.y = this.checkUndefinedOrNullWithDefaultValue(offset.y, 0);
        }
        getUINativeModule().renderNode.setShadowOffset(this.nodePtr, this.shadowOffsetValue.x, this.shadowOffsetValue.y);
    }
    set shadowAlpha(alpha) {
        this.shadowAlphaValue = this.checkUndefinedOrNullWithDefaultValue(alpha, 0);
        getUINativeModule().renderNode.setShadowAlpha(this.nodePtr, this.shadowAlphaValue);
    }
    set shadowElevation(elevation) {
        this.shadowElevationValue = this.checkUndefinedOrNullWithDefaultValue(elevation, 0);
        getUINativeModule().renderNode.setShadowElevation(this.nodePtr, this.shadowElevationValue);
    }
    set shadowRadius(radius) {
        this.shadowRadiusValue = this.checkUndefinedOrNullWithDefaultValue(radius, 0);
        getUINativeModule().renderNode.setShadowRadius(this.nodePtr, this.shadowRadiusValue);
    }
    set size(size) {
        if (size === undefined || size === null) {
            this.frameValue.width = 0;
            this.frameValue.height = 0;
        }
        else {
            this.frameValue.width = this.checkUndefinedOrNullWithDefaultValue(size.width, 0);
            this.frameValue.height = this.checkUndefinedOrNullWithDefaultValue(size.height, 0);
        }
        getUINativeModule().renderNode.setSize(this.nodePtr, this.frameValue.width, this.frameValue.height);
    }
    set transform(transform) {
        if (transform === undefined || transform === null) {
            this.transformValue = [1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1];
        }
        else {
            let i = 0;
            while (i < transform.length && i < 16) {
                if (i % 5 === 0) {
                    this.transformValue[i] = this.checkUndefinedOrNullWithDefaultValue(transform[i], 1);
                }
                else {
                    this.transformValue[i] = this.checkUndefinedOrNullWithDefaultValue(transform[i], 0);
                }
                i = i + 1;
            }
        }
        getUINativeModule().common.setTransform(this.nodePtr, this.transformValue);
    }
    set translation(translation) {
        if (translation === undefined || translation === null) {
            this.translationValue = { x: 0, y: 0 };
        }
        else {
            this.translationValue.x = this.checkUndefinedOrNullWithDefaultValue(translation.x, 0);
            this.translationValue.y = this.checkUndefinedOrNullWithDefaultValue(translation.y, 0);
        }
        getUINativeModule().renderNode.setTranslate(this.nodePtr, this.translationValue.x, this.translationValue.y, 0);
    }
    get backgroundColor() {
        return this.backgroundColorValue;
    }
    get clipToFrame() {
        return this.clipToFrameValue;
    }
    get opacity() {
        return this.opacityValue;
    }
    get frame() {
        return this.frameValue;
    }
    get pivot() {
        return this.pivotValue;
    }
    get position() {
        return { x: this.frameValue.x, y: this.frameValue.y };
    }
    get rotation() {
        return this.rotationValue;
    }
    get scale() {
        return this.scaleValue;
    }
    get shadowColor() {
        return this.shadowColorValue;
    }
    get shadowOffset() {
        return this.shadowOffsetValue;
    }
    get shadowAlpha() {
        return this.shadowAlphaValue;
    }
    get shadowElevation() {
        return this.shadowElevationValue;
    }
    get shadowRadius() {
        return this.shadowRadiusValue;
    }
    get size() {
        return { width: this.frameValue.width, height: this.frameValue.height };
    }
    get transform() {
        return this.transformValue;
    }
    get translation() {
        return this.translationValue;
    }
    checkUndefinedOrNullWithDefaultValue(arg, defaultValue) {
        if (arg === undefined || arg === null) {
            return defaultValue;
        }
        else {
            return arg;
        }
    }
    appendChild(node) {
        if (node === undefined || node === null) {
            return;
        }
        if (this.childrenList.findIndex(element => element === node) !== -1) {
            return;
        }
        this.childrenList.push(node);
        node.parentRenderNode = new WeakRef(this);
        getUINativeModule().renderNode.appendChild(this.nodePtr, node.nodePtr);
    }
    insertChildAfter(child, sibling) {
        if (child === undefined || child === null) {
            return;
        }
        let indexOfNode = this.childrenList.findIndex(element => element === child);
        if (indexOfNode !== -1) {
            return;
        }
        child.parentRenderNode = new WeakRef(this);
        let indexOfSibling = this.childrenList.findIndex(element => element === sibling);
        if (indexOfSibling === -1) {
            sibling === null;
        }
        if (sibling === undefined || sibling === null) {
            this.childrenList.splice(0, 0, child);
            getUINativeModule().renderNode.insertChildAfter(this.nodePtr, child.nodePtr, null);
        }
        else {
            this.childrenList.splice(indexOfSibling + 1, 0, child);
            getUINativeModule().renderNode.insertChildAfter(this.nodePtr, child.nodePtr, sibling.nodePtr);
        }
    }
    removeChild(node) {
        if (node === undefined || node === null) {
            return;
        }
        const index = this.childrenList.findIndex(element => element === node);
        if (index === -1) {
            return;
        }
        const child = this.childrenList[index];
        child.parentRenderNode = null;
        this.childrenList.splice(index, 1);
        getUINativeModule().renderNode.removeChild(this.nodePtr, node.nodePtr);
    }
    clearChildren() {
        this.childrenList = new Array();
        getUINativeModule().renderNode.clearChildren(this.nodePtr);
    }
    getChild(index) {
        if (this.childrenList.length > index && index >= 0) {
            return this.childrenList[index];
        }
        return null;
    }
    getFirstChild() {
        if (this.childrenList.length > 0) {
            return this.childrenList[0];
        }
        return null;
    }
    getNextSibling() {
        if (this.parentRenderNode === undefined || this.parentRenderNode === null) {
            return null;
        }
        let parent = this.parentRenderNode.deref();
        if (parent === undefined || parent === null) {
            return null;
        }
        let siblingList = parent.childrenList;
        const index = siblingList.findIndex(element => element === this);
        if (index === -1) {
            return null;
        }
        return parent.getChild(index + 1);
    }
    getPreviousSibling() {
        if (this.parentRenderNode === undefined || this.parentRenderNode === null) {
            return null;
        }
        let parent = this.parentRenderNode.deref();
        if (parent === undefined || parent === null) {
            return null;
        }
        let siblingList = parent.childrenList;
        const index = siblingList.findIndex(element => element === this);
        if (index === -1) {
            return null;
        }
        return parent.getChild(index - 1);
    }
    setNodePtr(nodePtr) {
        this.nodePtr = nodePtr;
    }
    setBaseNode(baseNode) {
        this.baseNode_ = baseNode;
    }
    dispose() {
        this.baseNode_.dispose();
    }
    getNodePtr() {
        return this.nodePtr;
    }
    draw(context) {
    }
    invalidate() {
        getUINativeModule().renderNode.invalidate(this.nodePtr);
    }
    set borderStyle(style) {
        if (style === undefined || style === null) {
            this.borderStyleValue = { left: BorderStyle.NONE, top: BorderStyle.NONE, right: BorderStyle.NONE, bottom: BorderStyle.NONE };
        }
        else {
            this.borderStyleValue = style;
        }
        getUINativeModule().renderNode.setBorderStyle(this.nodePtr, this.borderStyleValue.left, this.borderStyleValue.top, this.borderStyleValue.right, this.borderStyleValue.bottom);
    }
    get borderStyle() {
        return this.borderStyleValue;
    }
    set borderWidth(width) {
        if (width === undefined || width === null) {
            this.borderWidthValue = { left: 0, top: 0, right: 0, bottom: 0 };
        }
        else {
            this.borderWidthValue = width;
        }
        getUINativeModule().renderNode.setBorderWidth(this.nodePtr, this.borderWidthValue.left, this.borderWidthValue.top, this.borderWidthValue.right, this.borderWidthValue.bottom);
    }
    get borderWidth() {
        return this.borderWidthValue;
    }
    set borderColor(color) {
        if (color === undefined || color === null) {
            this.borderColorValue = { left: 0XFF000000, top: 0XFF000000, right: 0XFF000000, bottom: 0XFF000000 };
        }
        else {
            this.borderColorValue = color;
        }
        getUINativeModule().renderNode.setBorderColor(this.nodePtr, this.borderColorValue.left, this.borderColorValue.top, this.borderColorValue.right, this.borderColorValue.bottom);
    }
    get borderColor() {
        return this.borderColorValue;
    }
    set borderRadius(radius) {
        if (radius === undefined || radius === null) {
            this.borderRadiusValue = { topLeft: 0, topRight: 0, bottomLeft: 0, bottomRight: 0 };
        }
        else {
            this.borderRadiusValue = radius;
        }
        getUINativeModule().renderNode.setBorderRadius(this.nodePtr, this.borderRadiusValue.topLeft, this.borderRadiusValue.topRight, this.borderRadiusValue.bottomLeft, this.borderRadiusValue.bottomRight);
    }
    get borderRadius() {
        return this.borderRadiusValue;
    }
    set shapeMask(shapeMask) {
        if (shapeMask === undefined || shapeMask === null) {
            this.shapeMaskValue = new ShapeMask();
        }
        else {
            this.shapeMaskValue = shapeMask;
        }
        if (this.shapeMaskValue.rect !== null) {
            const rectMask = this.shapeMaskValue.rect;
            getUINativeModule().renderNode.setRectMask(this.nodePtr, rectMask.left, rectMask.top, rectMask.right, rectMask.bottom, this.shapeMaskValue.fillColor, this.shapeMaskValue.strokeColor, this.shapeMaskValue.strokeWidth);
        }
        else if (this.shapeMaskValue.circle !== null) {
            const circle = this.shapeMaskValue.circle;
            getUINativeModule().renderNode.setCircleMask(this.nodePtr, circle.centerX, circle.centerY, circle.radius, this.shapeMaskValue.fillColor, this.shapeMaskValue.strokeColor, this.shapeMaskValue.strokeWidth);
        }
        else if (this.shapeMaskValue.roundRect !== null) {
            const reoundRect = this.shapeMask.roundRect;
            const corners = reoundRect.corners;
            const rect = reoundRect.rect;
            getUINativeModule().renderNode.setRoundRectMask(this.nodePtr, corners.topLeft.x, corners.topLeft.y, corners.topRight.x, corners.topRight.y, corners.bottomLeft.x, corners.bottomLeft.y, corners.bottomRight.x, corners.bottomRight.y, rect.left, rect.top, rect.right, rect.bottom, this.shapeMaskValue.fillColor, this.shapeMaskValue.strokeColor, this.shapeMaskValue.strokeWidth);
        }
        else if (this.shapeMaskValue.oval !== null) {
            const oval = this.shapeMaskValue.oval;
            getUINativeModule().renderNode.setOvalMask(this.nodePtr, oval.left, oval.top, oval.right, oval.bottom, this.shapeMaskValue.fillColor, this.shapeMaskValue.strokeColor, this.shapeMaskValue.strokeWidth);
        }
        else if (this.shapeMaskValue.path !== null) {
            const path = this.shapeMaskValue.path;
            getUINativeModule().renderNode.setPath(this.nodePtr, path.commands, this.shapeMaskValue.fillColor, this.shapeMaskValue.strokeColor, this.shapeMaskValue.strokeWidth);
        }
    }
    get shapeMask() {
        return this.shapeMaskValue;
    }
}
function edgeColors(all) {
    return { left: all, top: all, right: all, bottom: all };
}
function edgeWidths(all) {
    return { left: all, top: all, right: all, bottom: all };
}
function borderStyles(all) {
    return { left: all, top: all, right: all, bottom: all };
}
function borderRadiuses(all) {
    return { topLeft: all, topRight: all, bottomLeft: all, bottomRight: all };
}
/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
class XComponentNode extends FrameNode {
    constructor(uiContext, options, id, type, libraryname) {
        super(uiContext, 'XComponentNode');
        const elmtId = ViewStackProcessor.AllocateNewElmetIdForNextComponent();
        this.xcomponentNode_ = getUINativeModule().xcomponentNode;
        this.renderType_ = options.type;
        const surfaceId = options.surfaceId;
        const selfIdealWidth = options.selfIdealSize.width;
        const selfIdealHeight = options.selfIdealSize.height;
        this.nativeModule_ = this.xcomponentNode_.create(elmtId, id, type, this.renderType_, surfaceId, selfIdealWidth, selfIdealHeight, libraryname);
        this.xcomponentNode_.registerOnCreateCallback(this.nativeModule_, this.onCreate);
        this.xcomponentNode_.registerOnDestroyCallback(this.nativeModule_, this.onDestroy);
        this.nodePtr_ = this.xcomponentNode_.getFrameNode(this.nativeModule_);
        this.setNodePtr(this.nodePtr_);
    }
    onCreate(event) { }
    onDestroy() { }
    changeRenderType(type) {
        if (this.renderType_ === type) {
            return true;
        }
        if (this.xcomponentNode_.changeRenderType(this.nativeModule_, type)) {
            this.renderType_ = type;
            return true;
        }
        return false;
    }
}
/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
/// <reference path="../../state_mgmt/src/lib/common/ifelse_native.d.ts" />
/// <reference path="../../state_mgmt/src/lib/partial_update/pu_viewstack_processor.d.ts" />
class ComponentContent {
    constructor(uiContext, builder, params) {
        let builderNode = new BuilderNode(uiContext, {});
        this.builderNode_ = builderNode;
        this.builderNode_.build(builder, params !== null && params !== void 0 ? params : {});
    }
    update(params) {
        this.builderNode_.update(params);
    }
    getFrameNode() {
        return this.builderNode_.getFrameNode();
    }
}

export default { NodeController, BuilderNode, BaseNode, RenderNode, FrameNode, FrameNodeUtils, NodeRenderType, XComponentNode, LengthMetric, LengthUnit, ShapeMask, edgeColors, edgeWidths, borderStyles, borderRadiuses, ComponentContent };
