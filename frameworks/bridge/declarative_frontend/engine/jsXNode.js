/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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
/// <reference path="../../state_mgmt/distRelease/stateMgmt.d.ts" />
var NodeRenderType;
(function (NodeRenderType) {
    NodeRenderType[NodeRenderType["RENDER_TYPE_DISPLAY"] = 0] = "RENDER_TYPE_DISPLAY";
    NodeRenderType[NodeRenderType["RENDER_TYPE_TEXTURE"] = 1] = "RENDER_TYPE_TEXTURE";
})(NodeRenderType || (NodeRenderType = {}));
class BaseNode extends ViewBuildNodeBase {
    constructor(uiContext, options) {
        super(false);
        let baseNode = new __JSBaseNode__(options);
        this.builderBaseNode_ = baseNode;
        if (uiContext === undefined) {
            throw Error('Node constructor error, param uiContext error');
        }
        else {
            if (!(typeof uiContext === 'object') || !('instanceId_' in uiContext)) {
                throw Error('Node constructor error, param uiContext is invalid');
            }
        }
        this.instanceId_ = uiContext.instanceId_;
    }
    getInstanceId() {
        return this.instanceId_;
    }
    updateInstance(uiContext) {
        this.instanceId_ = uiContext.instanceId_;
    }
    create(builder, params, update, updateConfiguration, supportLazyBuild) {
        return this.builderBaseNode_.create(builder.bind(this), params, update, updateConfiguration, supportLazyBuild);
    }
    finishUpdateFunc() {
        return this.builderBaseNode_.finishUpdateFunc();
    }
    postTouchEvent(touchEvent) {
        return this.builderBaseNode_.postTouchEvent(touchEvent);
    }
    disposeNode() {
        return this.builderBaseNode_.disposeNode();
    }
    updateStart() {
        return this.builderBaseNode_.updateStart();
    }
    updateEnd() {
        return this.builderBaseNode_.updateEnd();
    }
    onRecycleWithBindObject() {
        return this.builderBaseNode_.onRecycleWithBindObject();
    }
    onReuseWithBindObject(object) {
        return this.builderBaseNode_.onReuseWithBindObject(object);
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
/// <reference path="../../state_mgmt/src/lib/puv2_common/puv2_viewstack_processor.d.ts" />
class BuilderNode {
    constructor(uiContext, options) {
        let jsBuilderNode = new JSBuilderNode(uiContext, options);
        this._JSBuilderNode = jsBuilderNode;
        let id = Symbol('BuilderRootFrameNode');
        BuilderNodeFinalizationRegisterProxy.ElementIdToOwningBuilderNode_.set(id, jsBuilderNode);
        BuilderNodeFinalizationRegisterProxy.register(this, { name: 'BuilderRootFrameNode', idOfNode: id });
    }
    update(params) {
        this._JSBuilderNode.update(params);
    }
    build(builder, params, options) {
        this._JSBuilderNode.build(builder, params, options);
        this.nodePtr_ = this._JSBuilderNode.getNodePtr();
    }
    getNodePtr() {
        return this._JSBuilderNode.getValidNodePtr();
    }
    getFrameNode() {
        return this._JSBuilderNode.getFrameNode();
    }
    getFrameNodeWithoutCheck() {
        return this._JSBuilderNode.getFrameNodeWithoutCheck();
    }
    postTouchEvent(touchEvent) {
        __JSScopeUtil__.syncInstanceId(this._JSBuilderNode.getInstanceId());
        let ret = this._JSBuilderNode.postTouchEvent(touchEvent);
        __JSScopeUtil__.restoreInstanceId();
        return ret;
    }
    dispose() {
        this._JSBuilderNode.dispose();
    }
    reuse(param) {
        this._JSBuilderNode.reuse(param);
    }
    recycle() {
        this._JSBuilderNode.recycle();
    }
    updateConfiguration() {
        this._JSBuilderNode.updateConfiguration();
    }
    onReuseWithBindObject(param) {
        this._JSBuilderNode.onReuseWithBindObject(param);
    }
    onRecycleWithBindObject() {
        this._JSBuilderNode.onRecycleWithBindObject();
    }
}
class JSBuilderNode extends BaseNode {
    constructor(uiContext, options) {
        super(uiContext, options);
        this.uiContext_ = uiContext;
        this.updateFuncByElmtId = new UpdateFuncsByElmtId();
        this._supportNestingBuilder = false;
    }
    reuse(param) {
        this.updateStart();
        this.childrenWeakrefMap_.forEach((weakRefChild) => {
            const child = weakRefChild.deref();
            if (child) {
                if (child instanceof ViewPU) {
                    child.aboutToReuseInternal(param);
                }
                else {
                    // FIXME fix for mixed V2 - V3 Hierarchies
                    throw new Error('aboutToReuseInternal: Recycle not implemented for ViewV2, yet');
                }
            } // if child
        });
        this.updateEnd();
    }
    recycle() {
        this.childrenWeakrefMap_.forEach((weakRefChild) => {
            const child = weakRefChild.deref();
            if (child) {
                if (child instanceof ViewPU) {
                    child.aboutToRecycleInternal();
                }
                else {
                    // FIXME fix for mixed V2 - V3 Hierarchies
                    throw new Error('aboutToRecycleInternal: Recycle not yet implemented for ViewV2');
                }
            } // if child
        });
    }
    onReuseWithBindObject(param) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        super.onReuseWithBindObject(param);
        __JSScopeUtil__.restoreInstanceId();
    }
    onRecycleWithBindObject() {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        super.onRecycleWithBindObject();
        __JSScopeUtil__.restoreInstanceId();
    }
    getCardId() {
        return -1;
    }
    isObject(param) {
        const typeName = Object.prototype.toString.call(param);
        const objectName = `[object Object]`;
        if (typeName === objectName) {
            return true;
        }
        else {
            return false;
        }
    }
    buildWithNestingBuilder(builder, supportLazyBuild) {
        if (this._supportNestingBuilder && this.isObject(this.params_)) {
            this._proxyObjectParam = new Proxy(this.params_, {
                set(target, property, val) {
                    throw Error(`@Builder : Invalid attempt to set(write to) parameter '${property.toString()}' error!`);
                },
                get: (target, property, receiver) => { return this.params_?.[property]; }
            });
            this.nodePtr_ = super.create(builder.builder?.bind(this.bindedViewOfBuilderNode ? this.bindedViewOfBuilderNode : this), this._proxyObjectParam, this.updateNodeFromNative, this.updateConfiguration, supportLazyBuild);
        }
        else {
            this.nodePtr_ = super.create(builder.builder?.bind(this.bindedViewOfBuilderNode ? this.bindedViewOfBuilderNode : this), this.params_, this.updateNodeFromNative, this.updateConfiguration, supportLazyBuild);
        }
    }
    build(builder, params, options) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        this._supportNestingBuilder = options?.nestingBuilderSupported ? options.nestingBuilderSupported : false;
        const supportLazyBuild = options?.lazyBuildSupported ? options.lazyBuildSupported : false;
        this.bindedViewOfBuilderNode = options?.bindedViewOfBuilderNode;
        this.params_ = params;
        this.updateFuncByElmtId.clear();
        if (this.bindedViewOfBuilderNode) {
            globalThis.__viewPuStack__?.push(this.bindedViewOfBuilderNode);
        }
        this.buildWithNestingBuilder(builder, supportLazyBuild);
        if (this.bindedViewOfBuilderNode) {
            globalThis.__viewPuStack__?.pop();
        }
        this._nativeRef = getUINativeModule().nativeUtils.createNativeStrongRef(this.nodePtr_);
        if (this.frameNode_ === undefined || this.frameNode_ === null) {
            this.frameNode_ = new BuilderRootFrameNode(this.uiContext_);
        }
        this.frameNode_.setNodePtr(this._nativeRef, this.nodePtr_);
        this.frameNode_.setRenderNode(this._nativeRef);
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
    updateConfiguration() {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        this.updateStart();
        this.purgeDeletedElmtIds();
        Array.from(this.updateFuncByElmtId.keys()).sort((a, b) => {
            return (a < b) ? -1 : (a > b) ? 1 : 0;
        }).forEach(elmtId => this.UpdateElement(elmtId));
        for (const child of this.childrenWeakrefMap_.values()) {
            const childView = child.deref();
            if (childView) {
                childView.forceCompleteRerender(true);
            }
        }
        this.updateEnd();
        __JSScopeUtil__.restoreInstanceId();
    }
    UpdateElement(elmtId) {
        // do not process an Element that has been marked to be deleted
        const obj = this.updateFuncByElmtId.get(elmtId);
        const updateFunc = (typeof obj === 'object') ? obj.getUpdateFunc() : null;
        if (typeof updateFunc === 'function') {
            updateFunc(elmtId, /* isFirstRender */ false);
            this.finishUpdateFunc();
        }
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
    getFrameNodeWithoutCheck() {
        return this.frameNode_;
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
        const _popFunc = classObject && 'pop' in classObject ? classObject.pop : () => { };
        const updateFunc = (elmtId, isFirstRender) => {
            __JSScopeUtil__.syncInstanceId(this.instanceId_);
            if (Utils.isApiVersionEQAbove(16)) {
                ViewBuildNodeBase.arkThemeScopeManager?.onComponentCreateEnter(_componentName, elmtId, isFirstRender, this);
            }
            ViewStackProcessor.StartGetAccessRecordingFor(elmtId);
            // if V2 @Observed/@Track used anywhere in the app (there is no more fine grained criteria),
            // enable V2 object deep observation
            // FIXME: A @Component should only use PU or V2 state, but ReactNative dynamic viewer uses both.
            if (ConfigureStateMgmt.instance.needsV2Observe()) {
                // FIXME: like in V2 setting bindId_ in ObserveV2 does not work with 'stacked'
                // update + initial render calls, like in if and ForEach case, convert to stack as well
                ObserveV2.getObserve().startRecordDependencies(this, elmtId, true);
            }
            if (this._supportNestingBuilder) {
                compilerAssignedUpdateFunc(elmtId, isFirstRender);
            }
            else {
                compilerAssignedUpdateFunc(elmtId, isFirstRender, this.params_);
            }
            if (!isFirstRender) {
                _popFunc();
            }
            if (ConfigureStateMgmt.instance.needsV2Observe()) {
                ObserveV2.getObserve().stopRecordDependencies();
            }
            ViewStackProcessor.StopGetAccessRecording();
            if (Utils.isApiVersionEQAbove(16)) {
                ViewBuildNodeBase.arkThemeScopeManager?.onComponentCreateExit(elmtId);
            }
            __JSScopeUtil__.restoreInstanceId();
        };
        const elmtId = ViewStackProcessor.AllocateNewElmetIdForNextComponent();
        // needs to move set before updateFunc.
        // make sure the key and object value exist since it will add node in attributeModifier during updateFunc.
        this.updateFuncByElmtId.set(elmtId, { updateFunc: updateFunc, classObject: classObject });
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
                newIdArray.push(`${itemGenFuncUsesIndex ? index + '_' : ''}` + idGenFunc(item));
            });
        }
        // removedChildElmtIds will be filled with the elmtIds of all children and their children will be deleted in response to foreach change
        let removedChildElmtIds = [];
        // Set new array on C++ side.
        // C++ returns array of indexes of newly added array items.
        // these are indexes in new child list.
        ForEach.setIdArray(elmtId, newIdArray, diffIndexArray, idDuplicates, removedChildElmtIds);
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
        // un-registers the removed child elementIDs using proxy
        UINodeRegisterProxy.unregisterRemovedElmtsFromViewPUs(removedChildElmtIds);
        // purging these elmtIds from state mgmt will make sure no more update function on any deleted child will be executed
        this.purgeDeletedElmtIds();
    }
    getNodePtr() {
        return this.nodePtr_;
    }
    getValidNodePtr() {
        return this._nativeRef?.getNativeHandle();
    }
    dispose() {
        this.frameNode_?.dispose();
    }
    disposeNode() {
        super.disposeNode();
        this.nodePtr_ = null;
        this._nativeRef = null;
        this.frameNode_?.resetNodePtr();
    }
    updateInstance(uiContext) {
        this.uiContext_ = uiContext;
        this.instanceId_ = uiContext.instanceId_;
        if (this.frameNode_ !== undefined && this.frameNode_ !== null) {
            this.frameNode_.updateInstance(uiContext);
        }
    }
    updateNodePtr(nodePtr) {
        if (nodePtr != this.nodePtr_) {
            this.dispose();
            this.nodePtr_ = nodePtr;
            this._nativeRef = getUINativeModule().nativeUtils.createNativeStrongRef(this.nodePtr_);
            this.frameNode_.setNodePtr(this._nativeRef, this.nodePtr_);
        }
    }
    updateInstanceId(instanceId) {
        this.instanceId_ = instanceId;
    }
    updateNodeFromNative(instanceId, nodePtr) {
        this.updateNodePtr(nodePtr);
        this.updateInstanceId(instanceId);
    }
    observeRecycleComponentCreation(name, recycleUpdateFunc) {
        throw new Error('custom component in @Builder used by BuilderNode does not support @Reusable');
    }
    ifElseBranchUpdateFunctionDirtyRetaken() { }
    forceCompleteRerender(deep) { }
    forceRerenderNode(elmtId) { }
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
class NodeAdapter {
    constructor() {
        this.nodeRefs_ = new Array();
        this.count_ = 0;
        this.nativeRef_ = getUINativeModule().nodeAdapter.createAdapter();
        this.nativePtr_ = this.nativeRef_.getNativeHandle();
        getUINativeModule().nodeAdapter.setCallbacks(this.nativePtr_, this, this.onAttachToNodePtr, this.onDetachFromNodePtr, this.onGetChildId !== undefined ? this.onGetChildId : undefined, this.onCreateChild !== undefined ? this.onCreateNewNodePtr : undefined, this.onDisposeChild !== undefined ? this.onDisposeNodePtr : undefined, this.onUpdateChild !== undefined ? this.onUpdateNodePtr : undefined);
    }
    dispose() {
        let hostNode = this.attachedNodeRef_.deref();
        if (hostNode !== undefined) {
            NodeAdapter.detachNodeAdapter(hostNode);
        }
        this.nativeRef_.dispose();
        this.nativePtr_ = null;
    }
    set totalNodeCount(count) {
        if (count < 0) {
            return;
        }
        getUINativeModule().nodeAdapter.setTotalNodeCount(this.nativePtr_, count);
        this.count_ = count;
    }
    get totalNodeCount() {
        return this.count_;
    }
    reloadAllItems() {
        getUINativeModule().nodeAdapter.notifyItemReloaded(this.nativePtr_);
    }
    reloadItem(start, count) {
        if (start < 0 || count < 0) {
            return;
        }
        getUINativeModule().nodeAdapter.notifyItemChanged(this.nativePtr_, start, count);
    }
    removeItem(start, count) {
        if (start < 0 || count < 0) {
            return;
        }
        getUINativeModule().nodeAdapter.notifyItemRemoved(this.nativePtr_, start, count);
    }
    insertItem(start, count) {
        if (start < 0 || count < 0) {
            return;
        }
        getUINativeModule().nodeAdapter.notifyItemInserted(this.nativePtr_, start, count);
    }
    moveItem(from, to) {
        if (from < 0 || to < 0) {
            return;
        }
        getUINativeModule().nodeAdapter.notifyItemMoved(this.nativePtr_, from, to);
    }
    getAllAvailableItems() {
        let result = new Array();
        let nodes = getUINativeModule().nodeAdapter.getAllItems(this.nativePtr_);
        if (nodes !== undefined) {
            nodes.forEach(node => {
                let nodeId = node.nodeId;
                if (FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.has(nodeId)) {
                    let frameNode = FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.get(nodeId).deref();
                    result.push(frameNode);
                }
            });
        }
        return result;
    }
    onAttachToNodePtr(target) {
        let nodeId = target.nodeId;
        if (FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.has(nodeId)) {
            let frameNode = FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.get(nodeId).deref();
            if (frameNode === undefined) {
                return;
            }
            frameNode.setAdapterRef(this);
            this.attachedNodeRef_ = new WeakRef(frameNode);
            if (this.onAttachToNode !== undefined) {
                this.onAttachToNode(frameNode);
            }
        }
    }
    onDetachFromNodePtr() {
        if (this === undefined) {
            return;
        }
        if (this.onDetachFromNode !== undefined) {
            this.onDetachFromNode();
        }
        let attachedNode = this.attachedNodeRef_.deref();
        if (attachedNode !== undefined) {
            attachedNode.setAdapterRef(undefined);
        }
        this.nodeRefs_.splice(0, this.nodeRefs_.length);
    }
    onCreateNewNodePtr(index) {
        if (this.onCreateChild !== undefined) {
            let node = this.onCreateChild(index);
            if (!this.nodeRefs_.includes(node)) {
                this.nodeRefs_.push(node);
            }
            return node.getNodePtr();
        }
        return null;
    }
    onDisposeNodePtr(id, node) {
        let nodeId = node.nodeId;
        if (FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.has(nodeId)) {
            let frameNode = FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.get(nodeId).deref();
            if (this.onDisposeChild !== undefined && frameNode !== undefined) {
                this.onDisposeChild(id, frameNode);
                let index = this.nodeRefs_.indexOf(frameNode);
                if (index > -1) {
                    this.nodeRefs_.splice(index, 1);
                }
            }
        }
    }
    onUpdateNodePtr(id, node) {
        let nodeId = node.nodeId;
        if (FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.has(nodeId)) {
            let frameNode = FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.get(nodeId).deref();
            if (this.onUpdateChild !== undefined && frameNode !== undefined) {
                this.onUpdateChild(id, frameNode);
            }
        }
    }
    static attachNodeAdapter(adapter, node) {
        if (node === null || node === undefined) {
            return false;
        }
        if (!node.isModifiable()) {
            return false;
        }
        const hasAttributeProperty = Object.prototype.hasOwnProperty.call(node, 'attribute_');
        if (hasAttributeProperty) {
            let frameeNode = node;
            if (frameeNode.attribute_.allowChildCount !== undefined) {
                const allowCount = frameeNode.attribute_.allowChildCount();
                if (allowCount <= 1) {
                    return false;
                }
            }
        }
        return getUINativeModule().nodeAdapter.attachNodeAdapter(adapter.nativePtr_, node.getNodePtr());
    }
    static detachNodeAdapter(node) {
        if (node === null || node === undefined) {
            return;
        }
        getUINativeModule().nodeAdapter.detachNodeAdapter(node.getNodePtr());
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
            if (heldValue.name === 'BuilderRootFrameNode') {
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
class NodeControllerRegisterProxy {
}
NodeControllerRegisterProxy.instance_ = new NodeControllerRegisterProxy();
NodeControllerRegisterProxy.__NodeControllerMap__ = new Map();
globalThis.__AddToNodeControllerMap__ = function __AddToNodeControllerMap__(containerId, nodeController) {
    NodeControllerRegisterProxy.__NodeControllerMap__.set(containerId, nodeController);
};
globalThis.__RemoveFromNodeControllerMap__ = function __RemoveFromNodeControllerMap__(containerId) {
    let nodeController = NodeControllerRegisterProxy.__NodeControllerMap__.get(containerId);
    if (nodeController) {
        nodeController._nodeContainerId.__rootNodeOfNodeController__ = undefined;
        nodeController._nodeContainerId._value = -1;
        NodeControllerRegisterProxy.__NodeControllerMap__.delete(containerId);
    }
};
globalThis.__viewPuStack__ = new Array();
globalThis.__CheckIsInBuilderNode__ = function __CheckIsInBuilderNode__(parent) {
    if (globalThis.__viewPuStack__ === undefined || globalThis.__viewPuStack__.length === 0) {
        return false;
    }
    const _BuilderNodeView = globalThis.__viewPuStack__?.pop();
    if (_BuilderNodeView) {
        globalThis.__viewPuStack__?.push(_BuilderNodeView);
    }
    return (_BuilderNodeView !== undefined && _BuilderNodeView === parent) ? true : false;
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
    __makeNode__(UIContext) {
        this._nodeContainerId.__rootNodeOfNodeController__ = this.makeNode(UIContext);
        return this._nodeContainerId.__rootNodeOfNodeController__;
    }
    rebuild() {
        if (this._nodeContainerId !== undefined && this._nodeContainerId !== null && this._nodeContainerId._value >= 0) {
            getUINativeModule().nodeContainer.rebuild(this._nodeContainerId._value);
        }
    }
}
/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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
var ExpandMode;
(function (ExpandMode) {
    ExpandMode[ExpandMode["NOT_EXPAND"] = 0] = "NOT_EXPAND";
    ExpandMode[ExpandMode["EXPAND"] = 1] = "EXPAND";
    ExpandMode[ExpandMode["LAZY_EXPAND"] = 2] = "LAZY_EXPAND";
})(ExpandMode || (ExpandMode = {}));
class FrameNode {
    constructor(uiContext, type, options) {
        if (uiContext === undefined) {
            throw Error('Node constructor error, param uiContext error');
        }
        else {
            if (!(typeof uiContext === "object") || !("instanceId_" in uiContext)) {
                throw Error('Node constructor error, param uiContext is invalid');
            }
        }
        this.instanceId_ = uiContext.instanceId_;
        this.uiContext_ = uiContext;
        this._nodeId = -1;
        this._childList = new Map();
        if (type === 'BuilderRootFrameNode') {
            this.renderNode_ = new RenderNode(type);
            this.renderNode_.setFrameNode(new WeakRef(this));
            return;
        }
        if (type === 'ProxyFrameNode') {
            return;
        }
        let result;
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        if (type === undefined || type === "CustomFrameNode") {
            this.renderNode_ = new RenderNode('CustomFrameNode');
            result = getUINativeModule().frameNode.createFrameNode(this);
        }
        else {
            result = getUINativeModule().frameNode.createTypedFrameNode(this, type, options);
        }
        __JSScopeUtil__.restoreInstanceId();
        this._nativeRef = result?.nativeStrongRef;
        this._nodeId = result?.nodeId;
        this.nodePtr_ = this._nativeRef?.getNativeHandle();
        this.renderNode_?.setNodePtr(result?.nativeStrongRef);
        this.renderNode_?.setFrameNode(new WeakRef(this));
        if (result === undefined || this._nodeId === -1) {
            return;
        }
        FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.set(this._nodeId, new WeakRef(this));
        FrameNodeFinalizationRegisterProxy.register(this, this._nodeId);
    }
    invalidate() {
        if (this.nodePtr_ === undefined || this.nodePtr_ === null) {
            return;
        }
        getUINativeModule().frameNode.invalidate(this.nodePtr_);
    }
    getType() {
        return 'CustomFrameNode';
    }
    setRenderNode(nativeRef) {
        this.renderNode_?.setNodePtr(nativeRef);
    }
    getRenderNode() {
        if (this.renderNode_ !== undefined &&
            this.renderNode_ !== null &&
            this.renderNode_.getNodePtr() !== null) {
            return this.renderNode_;
        }
        return null;
    }
    setNodePtr(nativeRef, nodePtr) {
        FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.delete(this._nodeId);
        this._nativeRef = nativeRef;
        this.nodePtr_ = nodePtr ? nodePtr : this._nativeRef?.getNativeHandle();
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        this._nodeId = getUINativeModule().frameNode.getIdByNodePtr(this.nodePtr_);
        __JSScopeUtil__.restoreInstanceId();
        if (this._nodeId === -1) {
            return;
        }
        FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.set(this._nodeId, new WeakRef(this));
        FrameNodeFinalizationRegisterProxy.register(this, this._nodeId);
    }
    resetNodePtr() {
        FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.delete(this._nodeId);
        this._nodeId = -1;
        this._nativeRef = null;
        this.nodePtr_ = null;
        this.renderNode_?.resetNodePtr();
    }
    setBaseNode(baseNode) {
        this.baseNode_ = baseNode;
        this.renderNode_?.setBaseNode(baseNode);
    }
    setAdapterRef(adapter) {
        this.nodeAdapterRef_ = adapter;
    }
    getNodePtr() {
        return this.nodePtr_;
    }
    getValidNodePtr() {
        const node = this.getNodePtr();
        if (node === null) {
            throw Error('The FrameNode has been disposed!');
        } else {
            return node;
        }
    }
    dispose() {
        this.renderNode_?.dispose();
        FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.delete(this._nodeId);
        this._nodeId = -1;
        this._nativeRef = null;
        this.nodePtr_ = null;
    }
    static disposeTreeRecursively(node) {
        if (node === null) {
            return;
        }
        let child = node.getFirstChildWithoutExpand();
        FrameNode.disposeTreeRecursively(child);
        let sibling = node.getNextSiblingWithoutExpand();
        FrameNode.disposeTreeRecursively(sibling);
        node.dispose();
    }
    disposeTree() {
        let parent = this.getParent();
        if (parent?.getNodeType() === "NodeContainer") {
            getUINativeModule().nodeContainer.clean(parent?.getNodePtr());
        }
        else {
            parent?.removeChild(this);
        }
        FrameNode.disposeTreeRecursively(this);
    }
    checkType() {
        if (!this.isModifiable()) {
            throw { message: 'The FrameNode is not modifiable.', code: 100021 };
        }
    }
    isModifiable() {
        return this._nativeRef !== undefined && this._nativeRef !== null;
    }
    convertToFrameNode(nodePtr, nodeId = -1) {
        if (nodeId === -1) {
            __JSScopeUtil__.syncInstanceId(this.instanceId_);
            nodeId = getUINativeModule().frameNode.getIdByNodePtr(nodePtr);
            __JSScopeUtil__.restoreInstanceId();
        }
        if (nodeId !== -1 && !getUINativeModule().frameNode.isModifiable(nodePtr)) {
            __JSScopeUtil__.syncInstanceId(this.instanceId_);
            let frameNode = new ProxyFrameNode(this.uiContext_);
            let node = getUINativeModule().nativeUtils.createNativeWeakRef(nodePtr);
            __JSScopeUtil__.restoreInstanceId();
            frameNode.setNodePtr(node);
            frameNode._nodeId = nodeId;
            FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.set(frameNode._nodeId, new WeakRef(frameNode));
            FrameNodeFinalizationRegisterProxy.register(frameNode, frameNode._nodeId);
            return frameNode;
        }
        return null;
    }
    checkValid(node) {
        return true;
    }
    appendChild(node) {
        if (node === undefined || node === null) {
            return;
        }
        if (node.getType() === 'ProxyFrameNode' || !this.checkValid(node)) {
            throw { message: 'The FrameNode is not modifiable.', code: 100021 };
        }
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        let flag = getUINativeModule().frameNode.appendChild(this.nodePtr_, node.nodePtr_);
        __JSScopeUtil__.restoreInstanceId();
        if (!flag) {
            throw { message: 'The FrameNode is not modifiable.', code: 100021 };
        }
        this._childList.set(node._nodeId, node);
    }
    addComponentContent(content) {
        if (content === undefined || content === null || content.getNodePtr() === null || content.getNodePtr() == undefined) {
            return;
        }
        if (!this.checkValid() || !this.isModifiable()) {
            throw { message: 'The FrameNode is not modifiable.', code: 100021 };
        }
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        let flag = getUINativeModule().frameNode.appendChild(this.nodePtr_, content.getNodeWithoutProxy());
        __JSScopeUtil__.restoreInstanceId();
        if (!flag) {
            throw { message: 'The FrameNode is not modifiable.', code: 100021 };
        }
        else {
            content.setAttachedParent(new WeakRef(this));
        }
    }
    removeComponentContent(content) {
        if (content === undefined || content === null || content.getNodePtr() === null || content.getNodePtr() === undefined) {
            return;
        }
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        getUINativeModule().frameNode.removeChild(this.nodePtr_, content.getNodePtr());
        content.setAttachedParent(undefined);
        __JSScopeUtil__.restoreInstanceId();
    }
    insertChildAfter(child, sibling) {
        if (child === undefined || child === null) {
            return;
        }
        if (child.getType() === 'ProxyFrameNode' || !this.checkValid(child)) {
            throw { message: 'The FrameNode is not modifiable.', code: 100021 };
        }
        let flag = true;
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        if (sibling === undefined || sibling === null) {
            flag = getUINativeModule().frameNode.insertChildAfter(this.nodePtr_, child.nodePtr_, null);
        }
        else {
            flag = getUINativeModule().frameNode.insertChildAfter(this.nodePtr_, child.nodePtr_, sibling.getNodePtr());
        }
        __JSScopeUtil__.restoreInstanceId();
        if (!flag) {
            throw { message: 'The FrameNode is not modifiable.', code: 100021 };
        }
        this._childList.set(child._nodeId, child);
    }
    removeChild(node) {
        if (node === undefined || node === null) {
            return;
        }
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        getUINativeModule().frameNode.removeChild(this.nodePtr_, node.nodePtr_);
        __JSScopeUtil__.restoreInstanceId();
        this._childList.delete(node._nodeId);
    }
    clearChildren() {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        getUINativeModule().frameNode.clearChildren(this.nodePtr_);
        __JSScopeUtil__.restoreInstanceId();
        this._childList.clear();
    }
    moveTo(targetParent, index) {
        if (targetParent === undefined || targetParent === null) {
            return;
        }
        if (index === undefined || index === null) {
            index = -1;
        }
        const oldParent = this.getParent();
        if (oldParent && !oldParent.isModifiable() || !targetParent.isModifiable() || !targetParent.checkValid(this)) {
            throw { message: 'The FrameNode is not modifiable.', code: 100021 };
        }
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        getUINativeModule().frameNode.moveTo(this.nodePtr_, targetParent.nodePtr_, index);
        __JSScopeUtil__.restoreInstanceId();
        if (oldParent) {
            oldParent._childList.delete(this._nodeId);
        }
        targetParent._childList.set(this._nodeId, this);
    }
    getChild(index, expandMode) {
        const result = getUINativeModule().frameNode.getChild(this.getNodePtr(), index, expandMode);
        const nodeId = result?.nodeId;
        if (nodeId === undefined || nodeId === -1) {
            return null;
        }
        if (FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.has(nodeId)) {
            let frameNode = FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.get(nodeId).deref();
            return frameNode === undefined ? null : frameNode;
        }
        return this.convertToFrameNode(result.nodePtr, result.nodeId);
    }
    getFirstChildIndexWithoutExpand() {
        return getUINativeModule().frameNode.getFirstChildIndexWithoutExpand(this.getNodePtr());
    }
    getLastChildIndexWithoutExpand() {
        return getUINativeModule().frameNode.getLastChildIndexWithoutExpand(this.getNodePtr());
    }
    getFirstChild(isExpanded) {
        const result = getUINativeModule().frameNode.getFirst(this.getNodePtr(), isExpanded);
        const nodeId = result?.nodeId;
        if (nodeId === undefined || nodeId === -1) {
            return null;
        }
        if (FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.has(nodeId)) {
            let frameNode = FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.get(nodeId).deref();
            return frameNode === undefined ? null : frameNode;
        }
        return this.convertToFrameNode(result.nodePtr, result.nodeId);
    }
    getFirstChildWithoutExpand() {
        const result = getUINativeModule().frameNode.getFirst(this.getNodePtr(), false);
        const nodeId = result?.nodeId;
        if (nodeId === undefined || nodeId === -1) {
            return null;
        }
        if (FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.has(nodeId)) {
            let frameNode = FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.get(nodeId).deref();
            return frameNode === undefined ? null : frameNode;
        }
        return this.convertToFrameNode(result.nodePtr, result.nodeId);
    }
    getNextSibling(isExpanded) {
        const result = getUINativeModule().frameNode.getNextSibling(this.getNodePtr(), isExpanded);
        const nodeId = result?.nodeId;
        if (nodeId === undefined || nodeId === -1) {
            return null;
        }
        if (FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.has(nodeId)) {
            let frameNode = FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.get(nodeId).deref();
            return frameNode === undefined ? null : frameNode;
        }
        return this.convertToFrameNode(result.nodePtr, result.nodeId);
    }
    getNextSiblingWithoutExpand() {
        const result = getUINativeModule().frameNode.getNextSibling(this.getNodePtr(), false);
        const nodeId = result?.nodeId;
        if (nodeId === undefined || nodeId === -1) {
            return null;
        }
        if (FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.has(nodeId)) {
            let frameNode = FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.get(nodeId).deref();
            return frameNode === undefined ? null : frameNode;
        }
        return this.convertToFrameNode(result.nodePtr, result.nodeId);
    }
    getPreviousSibling(isExpanded) {
        const result = getUINativeModule().frameNode.getPreviousSibling(this.getNodePtr(), isExpanded);
        const nodeId = result?.nodeId;
        if (nodeId === undefined || nodeId === -1) {
            return null;
        }
        if (FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.has(nodeId)) {
            let frameNode = FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.get(nodeId).deref();
            return frameNode === undefined ? null : frameNode;
        }
        return this.convertToFrameNode(result.nodePtr, result.nodeId);
    }
    getParent() {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        const result = getUINativeModule().frameNode.getParent(this.getNodePtr());
        const nodeId = result?.nodeId;
        __JSScopeUtil__.restoreInstanceId();
        if (nodeId === undefined || nodeId === -1) {
            return null;
        }
        if (FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.has(nodeId)) {
            let frameNode = FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.get(nodeId).deref();
            return frameNode === undefined ? null : frameNode;
        }
        return this.convertToFrameNode(result.nodePtr, result.nodeId);
    }
    getChildrenCount(isExpanded) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        const childrenCount = getUINativeModule().frameNode.getChildrenCount(this.nodePtr_, isExpanded);
        __JSScopeUtil__.restoreInstanceId();
        return childrenCount;
    }
    getPositionToParent() {
        const position = getUINativeModule().frameNode.getPositionToParent(this.getNodePtr());
        return { x: position[0], y: position[1] };
    }
    getPositionToScreen() {
        const position = getUINativeModule().frameNode.getPositionToScreen(this.getNodePtr());
        return { x: position[0], y: position[1] };
    }
    getPositionToWindow() {
        const position = getUINativeModule().frameNode.getPositionToWindow(this.getNodePtr());
        return { x: position[0], y: position[1] };
    }
    getPositionToParentWithTransform() {
        const position = getUINativeModule().frameNode.getPositionToParentWithTransform(this.getNodePtr());
        return { x: position[0], y: position[1] };
    }
    getPositionToScreenWithTransform() {
        const position = getUINativeModule().frameNode.getPositionToScreenWithTransform(this.getNodePtr());
        return { x: position[0], y: position[1] };
    }
    getPositionToWindowWithTransform() {
        const position = getUINativeModule().frameNode.getPositionToWindowWithTransform(this.getNodePtr());
        return { x: position[0], y: position[1] };
    }
    getMeasuredSize() {
        const size = getUINativeModule().frameNode.getMeasuredSize(this.getValidNodePtr());
        return { width: size[0], height: size[1] };
    }
    getLayoutPosition() {
        const position = getUINativeModule().frameNode.getLayoutPosition(this.getValidNodePtr());
        return { x: position[0], y: position[1] };
    }
    getUserConfigBorderWidth() {
        const borderWidth = getUINativeModule().frameNode.getConfigBorderWidth(this.getNodePtr());
        return {
            top: new LengthMetrics(borderWidth[0], borderWidth[1]),
            right: new LengthMetrics(borderWidth[2], borderWidth[3]),
            bottom: new LengthMetrics(borderWidth[4], borderWidth[5]),
            left: new LengthMetrics(borderWidth[6], borderWidth[7])
        };
    }
    getUserConfigPadding() {
        const borderWidth = getUINativeModule().frameNode.getConfigPadding(this.getNodePtr());
        return {
            top: new LengthMetrics(borderWidth[0], borderWidth[1]),
            right: new LengthMetrics(borderWidth[2], borderWidth[3]),
            bottom: new LengthMetrics(borderWidth[4], borderWidth[5]),
            left: new LengthMetrics(borderWidth[6], borderWidth[7])
        };
    }
    getUserConfigMargin() {
        const margin = getUINativeModule().frameNode.getConfigMargin(this.getNodePtr());
        return {
            top: new LengthMetrics(margin[0], margin[1]),
            right: new LengthMetrics(margin[2], margin[3]),
            bottom: new LengthMetrics(margin[4], margin[5]),
            left: new LengthMetrics(margin[6], margin[7])
        };
    }
    getUserConfigSize() {
        const size = getUINativeModule().frameNode.getConfigSize(this.getNodePtr());
        return {
            width: new LengthMetrics(size[0], size[1]),
            height: new LengthMetrics(size[2], size[3])
        };
    }
    getId() {
        return getUINativeModule().frameNode.getId(this.getNodePtr());
    }
    getUniqueId() {
        return getUINativeModule().frameNode.getIdByNodePtr(this.getNodePtr());
    }
    getNodeType() {
        return getUINativeModule().frameNode.getNodeType(this.getNodePtr());
    }
    getOpacity() {
        return getUINativeModule().frameNode.getOpacity(this.getNodePtr());
    }
    isVisible() {
        return getUINativeModule().frameNode.isVisible(this.getNodePtr());
    }
    isClipToFrame() {
        return getUINativeModule().frameNode.isClipToFrame(this.getNodePtr());
    }
    isAttached() {
        return getUINativeModule().frameNode.isAttached(this.getNodePtr());
    }
    getInspectorInfo() {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        const inspectorInfoStr = getUINativeModule().frameNode.getInspectorInfo(this.getNodePtr());
        __JSScopeUtil__.restoreInstanceId();
        const inspectorInfo = JSON.parse(inspectorInfoStr);
        return inspectorInfo;
    }
    getCustomProperty(key) {
        if (key === undefined) {
            return undefined;
        }
        let value = __getCustomProperty__(this._nodeId, key);
        if (value === undefined) {
            const valueStr = getUINativeModule().frameNode.getCustomPropertyCapiByKey(this.getNodePtr(), key);
            value = valueStr === undefined ? undefined : valueStr;
        }
        return value;
    }
    setMeasuredSize(size) {
        getUINativeModule().frameNode.setMeasuredSize(this.getNodePtr(), Math.max(size.width, 0), Math.max(size.height, 0));
    }
    setLayoutPosition(position) {
        getUINativeModule().frameNode.setLayoutPosition(this.getNodePtr(), position.x, position.y);
    }
    measure(constraint) {
        const minSize = constraint.minSize;
        const maxSize = constraint.maxSize;
        const percentReference = constraint.percentReference;
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        getUINativeModule().frameNode.measureNode(this.getNodePtr(), minSize.width, minSize.height, maxSize.width, maxSize.height, percentReference.width, percentReference.height);
        __JSScopeUtil__.restoreInstanceId();
    }
    layout(position) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        getUINativeModule().frameNode.layoutNode(this.getNodePtr(), position.x, position.y);
        __JSScopeUtil__.restoreInstanceId();
    }
    setNeedsLayout() {
        getUINativeModule().frameNode.setNeedsLayout(this.getNodePtr());
    }
    setCrossLanguageOptions(options) {
        if (!this.isModifiable()) {
            throw { message: 'The FrameNode cannot be set whether to support cross-language common attribute setting.', code: 100022 };
        }
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        const result = getUINativeModule().frameNode.setCrossLanguageOptions(this.getNodePtr(), options.attributeSetting ?? false);
        __JSScopeUtil__.restoreInstanceId();
        if (result !== 0) {
            throw { message: 'The FrameNode cannot be set whether to support cross-language common attribute setting.', code: 100022 };
        }
    }
    getCrossLanguageOptions() {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        const attributeSetting = getUINativeModule().frameNode.getCrossLanguageOptions(this.getNodePtr());
        __JSScopeUtil__.restoreInstanceId();
        return { attributeSetting: attributeSetting ?? false };
    }
    checkIfCanCrossLanguageAttributeSetting() {
        return this.isModifiable() || getUINativeModule().frameNode.checkIfCanCrossLanguageAttributeSetting(this.getNodePtr());
    }
    get commonAttribute() {
        if (this._commonAttribute === undefined) {
            this._commonAttribute = new ArkComponent(this.nodePtr_, ModifierType.FRAME_NODE);
        }
        this._commonAttribute.setNodePtr(this.nodePtr_);
        this._commonAttribute.setInstanceId((this.uiContext_ === undefined || this.uiContext_ === null) ? -1 : this.uiContext_.instanceId_);
        return this._commonAttribute;
    }
    get commonEvent() {
        let node = this.getNodePtr();
        if (this._commonEvent === undefined) {
            this._commonEvent = new UICommonEvent(node);
        }
        this._commonEvent.setNodePtr(node);
        this._commonEvent.setInstanceId((this.uiContext_ === undefined || this.uiContext_ === null) ? -1 : this.uiContext_.instanceId_);
        return this._commonEvent;
    }
    get gestureEvent() {
        if (this._gestureEvent === undefined) {
            this._gestureEvent = new UIGestureEvent();
            this._gestureEvent.setNodePtr(this.nodePtr_);
            let weakPtr = getUINativeModule().nativeUtils.createNativeWeakRef(this.nodePtr_);
            this._gestureEvent.setWeakNodePtr(weakPtr);
            __JSScopeUtil__.syncInstanceId(this.instanceId_);
            this._gestureEvent.registerFrameNodeDeletedCallback(this.nodePtr_);
            __JSScopeUtil__.restoreInstanceId();
        }
        return this._gestureEvent;
    }
    updateInstance(uiContext) {
        this.uiContext_ = uiContext;
        this.instanceId_ = uiContext.instanceId_;
    }
    triggerOnReuse() {
        getUINativeModule().frameNode.triggerOnReuse(this.getNodePtr());
    }
    triggerOnRecycle() {
        getUINativeModule().frameNode.triggerOnRecycle(this.getNodePtr());
    }
    reuse() {
        this.triggerOnReuse();
    }
    recycle() {
        this.triggerOnRecycle();
    }
}
class ImmutableFrameNode extends FrameNode {
    isModifiable() {
        return false;
    }
    invalidate() {
        return;
    }
    appendChild(node) {
        throw { message: 'The FrameNode is not modifiable.', code: 100021 };
    }
    insertChildAfter(child, sibling) {
        throw { message: 'The FrameNode is not modifiable.', code: 100021 };
    }
    removeChild(node) {
        throw { message: 'The FrameNode is not modifiable.', code: 100021 };
    }
    clearChildren() {
        throw { message: 'The FrameNode is not modifiable.', code: 100021 };
    }
    get commonAttribute() {
        if (this._commonAttribute === undefined) {
            this._commonAttribute = new ArkComponent(undefined, ModifierType.FRAME_NODE);
        }
        this._commonAttribute.setNodePtr(undefined);
        return this._commonAttribute;
    }
}
class BuilderRootFrameNode extends ImmutableFrameNode {
    constructor(uiContext, type = 'BuilderRootFrameNode') {
        super(uiContext, type);
    }
    getType() {
        return 'BuilderRootFrameNode';
    }
}
class ProxyFrameNode extends ImmutableFrameNode {
    constructor(uiContext, type = 'ProxyFrameNode') {
        super(uiContext, type);
    }
    setNodePtr(nativeRef) {
        this._nativeRef = nativeRef;
        this.nodePtr_ = this._nativeRef.getNativeHandle();
    }
    getType() {
        return 'ProxyFrameNode';
    }
    getRenderNode() {
        return null;
    }
    getNodePtr() {
        if (this._nativeRef === undefined || this._nativeRef === null || this._nativeRef.invalid()) {
            return null;
        }
        return this.nodePtr_;
    }
    dispose() {
        this.renderNode_?.dispose();
        FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.delete(this._nodeId);
        this._nodeId = -1;
        this._nativeRef = undefined;
        this.nodePtr_ = undefined;
    }
    moveTo(targetParent, index) {
        throw { message: 'The FrameNode is not modifiable.', code: 100021 };
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
        let nodeId = getUINativeModule().frameNode.getIdByNodePtr(nodePtr);
        if (nodeId !== -1 && !getUINativeModule().frameNode.isModifiable(nodePtr)) {
            let frameNode = new ProxyFrameNode(uiContext);
            let node = getUINativeModule().nativeUtils.createNativeWeakRef(nodePtr);
            frameNode.setNodePtr(node);
            frameNode._nodeId = nodeId;
            FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.set(nodeId, new WeakRef(frameNode));
            FrameNodeFinalizationRegisterProxy.register(frameNode, nodeId);
            return frameNode;
        }
        return null;
    }
}
class TypedFrameNode extends FrameNode {
    constructor(uiContext, type, attrCreator, options) {
        super(uiContext, type, options);
        this.attrCreator_ = attrCreator;
    }
    initialize(...args) {
        return this.attribute.initialize(args);
    }
    get attribute() {
        if (this.attribute_ === undefined) {
            this.attribute_ = this.attrCreator_(this.nodePtr_, ModifierType.FRAME_NODE);
        }
        this.attribute_.setNodePtr(this.nodePtr_);
        this.attribute_.setInstanceId((this.uiContext_ === undefined || this.uiContext_ === null) ? -1 : this.uiContext_.instanceId_);
        return this.attribute_;
    }
    checkValid(node) {
        if (this.attribute_ === undefined) {
            this.attribute_ = this.attrCreator_(this.nodePtr_, ModifierType.FRAME_NODE);
        }
        if (this.attribute_.allowChildCount !== undefined) {
            const allowCount = this.attribute_.allowChildCount();
            if (this.getChildrenCount() >= allowCount) {
                return false;
            }
        }
        if (this.attribute_.allowChildTypes !== undefined && node !== undefined) {
            const childType = node.getNodeType();
            const allowTypes = this.attribute_.allowChildTypes();
            let isValid = false;
            allowTypes.forEach((nodeType) => {
                if (nodeType === childType) {
                    isValid = true;
                }
            });
            return isValid;
        }
        return true;
    }
}
const __creatorMap__ = new Map([
    ['Text', (context) => {
            return new TypedFrameNode(context, 'Text', (node, type) => {
                return new ArkTextComponent(node, type);
            });
        }],
    ['Column', (context) => {
            return new TypedFrameNode(context, 'Column', (node, type) => {
                return new ArkColumnComponent(node, type);
            });
        }],
    ['Row', (context) => {
            return new TypedFrameNode(context, 'Row', (node, type) => {
                return new ArkRowComponent(node, type);
            });
        }],
    ['Stack', (context) => {
            return new TypedFrameNode(context, 'Stack', (node, type) => {
                return new ArkStackComponent(node, type);
            });
        }],
    ['GridRow', (context) => {
            let node = new TypedFrameNode(context, 'GridRow', (node, type) => {
                return new ArkGridRowComponent(node, type);
            });
            node.initialize();
            return node;
        }],
    ['TextInput', (context) => {
            return new TypedFrameNode(context, 'TextInput', (node, type) => {
                return new ArkTextInputComponent(node, type);
            });
        }],
    ['GridCol', (context) => {
            let node = new TypedFrameNode(context, 'GridCol', (node, type) => {
                return new ArkGridColComponent(node, type);
            });
            node.initialize();
            return node;
        }],
    ['Blank', (context) => {
            return new TypedFrameNode(context, 'Blank', (node, type) => {
                return new ArkBlankComponent(node, type);
            });
        }],
    ['Image', (context) => {
            return new TypedFrameNode(context, 'Image', (node, type) => {
                return new ArkImageComponent(node, type);
            });
        }],
    ['Flex', (context) => {
            return new TypedFrameNode(context, 'Flex', (node, type) => {
                return new ArkFlexComponent(node, type);
            });
        }],
    ['Swiper', (context) => {
            return new TypedFrameNode(context, 'Swiper', (node, type) => {
                return new ArkSwiperComponent(node, type);
            });
        }],
    ['Progress', (context) => {
            return new TypedFrameNode(context, 'Progress', (node, type) => {
                return new ArkProgressComponent(node, type);
            });
        }],
    ['Scroll', (context) => {
            return new TypedFrameNode(context, 'Scroll', (node, type) => {
                return new ArkScrollComponent(node, type);
            });
        }],
    ['RelativeContainer', (context) => {
            return new TypedFrameNode(context, 'RelativeContainer', (node, type) => {
                return new ArkRelativeContainerComponent(node, type);
            });
        }],
    ['List', (context) => {
            return new TypedFrameNode(context, 'List', (node, type) => {
                return new ArkListComponent(node, type);
            });
        }],
    ['ListItem', (context) => {
            return new TypedFrameNode(context, 'ListItem', (node, type) => {
                return new ArkListItemComponent(node, type);
            });
        }],
    ['Divider', (context) => {
            return new TypedFrameNode(context, 'Divider', (node, type) => {
                return new ArkDividerComponent(node, type);
            });
        }],
    ['LoadingProgress', (context) => {
            return new TypedFrameNode(context, 'LoadingProgress', (node, type) => {
                return new ArkLoadingProgressComponent(node, type);
            });
        }],
    ['Search', (context) => {
            return new TypedFrameNode(context, 'Search', (node, type) => {
                return new ArkSearchComponent(node, type);
            });
        }],
    ['Button', (context) => {
            return new TypedFrameNode(context, 'Button', (node, type) => {
                return new ArkButtonComponent(node, type);
            });
        }],
    ['XComponent', (context, options) => {
            return new TypedFrameNode(context, 'XComponent', (node, type) => {
                return new ArkXComponentComponent(node, type);
            }, options);
        }],
    ['ListItemGroup', (context) => {
            return new TypedFrameNode(context, 'ListItemGroup', (node, type) => {
                return new ArkListItemGroupComponent(node, type);
            });
        }],
    ['WaterFlow', (context) => {
            return new TypedFrameNode(context, 'WaterFlow', (node, type) => {
                return new ArkWaterFlowComponent(node, type);
            });
        }],
    ['SymbolGlyph', (context) => {
            return new TypedFrameNode(context, 'SymbolGlyph', (node, type) => {
                return new ArkSymbolGlyphComponent(node, type);
            });
        }],
    ['FlowItem', (context) => {
            return new TypedFrameNode(context, 'FlowItem', (node, type) => {
                return new ArkFlowItemComponent(node, type);
            });
        }],
    ['QRCode', (context) => {
            return new TypedFrameNode(context, 'QRCode', (node, type) => {
                return new ArkQRCodeComponent(node, type);
            });
        }],
    ['Badge', (context) => {
            return new TypedFrameNode(context, 'Badge', (node, type) => {
                return new ArkBadgeComponent(node, type);
            });
        }],
    ['Grid', (context) => {
            return new TypedFrameNode(context, 'Grid', (node, type) => {
                return new ArkGridComponent(node, type);
            });
        }],
    ['GridItem', (context) => {
            return new TypedFrameNode(context, 'GridItem', (node, type) => {
                return new ArkGridItemComponent(node, type);
            });
        }],
    ['TextClock', (context) => {
            return new TypedFrameNode(context, 'TextClock', (node, type) => {
                return new ArkTextClockComponent(node, type);
            });
        }],
    ['TextTimer', (context) => {
            return new TypedFrameNode(context, 'TextTimer', (node, type) => {
                return new ArkTextTimerComponent(node, type);
            });
        }],
    ['Marquee', (context) => {
            return new TypedFrameNode(context, 'Marquee', (node, type) => {
                return new ArkMarqueeComponent(node, type);
            });
        }],
    ['TextArea', (context) => {
            return new TypedFrameNode(context, 'TextArea', (node, type) => {
                return new ArkTextAreaComponent(node, type);
            });
        }],
    ['Checkbox', (context) => {
            return new TypedFrameNode(context, 'Checkbox', (node, type) => {
                return new ArkCheckboxComponent(node, type);
            });
        }],
    ['CheckboxGroup', (context) => {
            return new TypedFrameNode(context, 'CheckboxGroup', (node, type) => {
                return new ArkCheckboxGroupComponent(node, type);
            });
        }],
    ['Radio', (context) => {
            return new TypedFrameNode(context, 'Radio', (node, type) => {
                return new ArkRadioComponent(node, type);
            });
        }],
    ['Rating', (context) => {
            return new TypedFrameNode(context, 'Rating', (node, type) => {
                return new ArkRatingComponent(node, type);
            });
        }],
    ['Slider', (context) => {
            return new TypedFrameNode(context, 'Slider', (node, type) => {
                return new ArkSliderComponent(node, type);
            });
        }],
    ['Select', (context) => {
            return new TypedFrameNode(context, 'Select', (node, type) => {
                return new ArkSelectComponent(node, type);
            });
        }],
    ['Toggle', (context, options) => {
            return new TypedFrameNode(context, 'Toggle', (node, type) => {
                return new ArkToggleComponent(node, type);
            }, options);
        }],
]);
const __attributeMap__ = new Map([
    ['Scroll', (node) => {
            if (node._componentAttribute) {
                return node._componentAttribute;
            }
            if (!node.getNodePtr()) {
                return undefined;
            }
            node._componentAttribute = new ArkScrollComponent(node.getNodePtr(), ModifierType.FRAME_NODE);
            return node._componentAttribute;
        }],
]);
class typeNode {
    static createNode(context, type, options) {
        let creator = __creatorMap__.get(type);
        if (creator === undefined) {
            return undefined;
        }
        return creator(context, options);
    }
    static getAttribute(node, nodeType) {
        if (node === undefined || node === null || node.getNodeType() !== nodeType) {
            return undefined;
        }
        if (!node.checkIfCanCrossLanguageAttributeSetting()) {
            return undefined;
        }
        let attribute = __attributeMap__.get(nodeType);
        if (attribute === undefined || attribute === null) {
            return undefined;
        }
        return attribute(node);
    }
    static bindController(node, controller, nodeType) {
        if (node === undefined || node === null || controller === undefined || controller === null ||
            node.getNodeType() !== nodeType || node.getNodePtr() === null || node.getNodePtr() === undefined) {
            throw { message: 'Parameter error. Possible causes: 1. The type of the node is error; 2. The node is null or undefined.', code: 401 };
        }
        if (!node.checkIfCanCrossLanguageAttributeSetting()) {
            throw { message: 'The FrameNode is not modifiable.', code: 100021 };
        }
        getUINativeModule().scroll.setScrollInitialize(node.getNodePtr(), controller);
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
var LengthMetricsUnit;
(function (LengthMetricsUnit) {
    LengthMetricsUnit[LengthMetricsUnit["DEFAULT"] = 0] = "DEFAULT";
    LengthMetricsUnit[LengthMetricsUnit["PX"] = 1] = "PX";
})(LengthMetricsUnit || (LengthMetricsUnit = {}));
class LengthMetrics {
    constructor(value, unit) {
        if (unit in LengthUnit) {
            this.unit = unit;
            this.value = value;
        }
        else {
            this.unit = LengthUnit.VP;
            this.value = unit === undefined ? value : 0;
        }
    }
    static px(value) {
        return new LengthMetrics(value, LengthUnit.PX);
    }
    static vp(value) {
        return new LengthMetrics(value, LengthUnit.VP);
    }
    static fp(value) {
        return new LengthMetrics(value, LengthUnit.FP);
    }
    static percent(value) {
        return new LengthMetrics(value, LengthUnit.PERCENT);
    }
    static lpx(value) {
        return new LengthMetrics(value, LengthUnit.LPX);
    }
    static resource(res) {
        let length = getUINativeModule().nativeUtils.resoureToLengthMetrics(res);
        return new LengthMetrics(length[0], length[1]);
    }
}
const MAX_CHANNEL_VALUE = 0xFF;
const MAX_ALPHA_VALUE = 1;
const ERROR_CODE_RESOURCE_GET_FAILED = 180003;
const ERROR_CODE_COLOR_PARAMETER_INCORRECT = 401;
class ColorMetrics {
    constructor(red, green, blue, alpha = MAX_CHANNEL_VALUE) {
        this.red_ = ColorMetrics.clamp(red);
        this.green_ = ColorMetrics.clamp(green);
        this.blue_ = ColorMetrics.clamp(blue);
        this.alpha_ = ColorMetrics.clamp(alpha);
    }
    static clamp(value) {
        return Math.min(Math.max(value, 0), MAX_CHANNEL_VALUE);
    }
    toNumeric() {
        return (this.alpha_ << 24) + (this.red_ << 16) + (this.green_ << 8) + this.blue_;
    }
    static numeric(value) {
        const red = (value >> 16) & 0x000000FF;
        const green = (value >> 8) & 0x000000FF;
        const blue = value & 0x000000FF;
        const alpha = (value >> 24) & 0x000000FF;
        if (alpha === 0) {
            return new ColorMetrics(red, green, blue);
        }
        return new ColorMetrics(red, green, blue, alpha);
    }
    static rgba(red, green, blue, alpha = MAX_ALPHA_VALUE) {
        return new ColorMetrics(red, green, blue, alpha * MAX_CHANNEL_VALUE);
    }
    static rgbOrRGBA(format) {
        const rgbPattern = /^rgb\(\s*(\d+)\s*,\s*(\d+)\s*,\s*(\d+)\s*\)$/i;
        const rgbaPattern = /^rgba\(\s*(\d+)\s*,\s*(\d+)\s*,\s*(\d+)\s*,\s*(\d+(\.\d+)?)\s*\)$/i;
        const rgbMatch = rgbPattern.exec(format);
        const rgbaMatch = rgbaPattern.exec(format);
        if (rgbMatch) {
            const [, red, green, blue] = rgbMatch;
            return new ColorMetrics(Number.parseInt(red, 10), Number.parseInt(green, 10), Number.parseInt(blue, 10));
        }
        else if (rgbaMatch) {
            const [, red, green, blue, alpha] = rgbaMatch;
            return new ColorMetrics(Number.parseInt(red, 10), Number.parseInt(green, 10), Number.parseInt(blue, 10), Number.parseFloat(alpha) * MAX_CHANNEL_VALUE);
        }
        else {
            const error = new Error('Parameter error. The format of the input color string is not RGB or RGBA.');
            error.code = ERROR_CODE_COLOR_PARAMETER_INCORRECT;
            throw error;
        }
    }
    static resourceColor(color) {
        if (color === undefined || color === null) {
            const error = new Error('Parameter error. The type of the input color parameter is not ResourceColor.');
            error.code = ERROR_CODE_COLOR_PARAMETER_INCORRECT;
            throw error;
        }
        let chanels = [];
        if (typeof color === 'object') {
            chanels = getUINativeModule().nativeUtils.parseResourceColor(color);
            if (chanels === undefined) {
                const error = new Error('Failed to obtain the color resource.');
                error.code = ERROR_CODE_RESOURCE_GET_FAILED;
                throw error;
            }
            const red = chanels[0];
            const green = chanels[1];
            const blue = chanels[2];
            const alpha = chanels[3];
            const resourceId = chanels[4];
            const colorMetrics = new ColorMetrics(red, green, blue, alpha);
            colorMetrics.setResourceId(resourceId);
            return colorMetrics;
        }
        else if (typeof color === 'number') {
            return ColorMetrics.numeric(color);
        }
        else if (typeof color === 'string') {
            if (ColorMetrics.isHexFormat(color)) {
                return ColorMetrics.hex(color);
            }
            else {
                return ColorMetrics.rgbOrRGBA(color);
            }
        }
        else {
            const error = new Error('Parameter error. The type of the input color parameter is not ResourceColor.');
            error.code = ERROR_CODE_COLOR_PARAMETER_INCORRECT;
            throw error;
        }
    }
    static isHexFormat(format) {
        return /#(([0-9A-Fa-f]{3})|([0-9A-Fa-f]{6})|([0-9A-Fa-f]{4})|([0-9A-Fa-f]{8}))/.test(format);
    }
    static hex(hexFormat) {
        let r = 0;
        let g = 0;
        let b = 0;
        let a = 255;
        if (hexFormat.length === 4) {
            r = parseInt(hexFormat.slice(1, 2).repeat(2), 16);
            g = parseInt(hexFormat.slice(2, 3).repeat(2), 16);
            b = parseInt(hexFormat.slice(3).repeat(2), 16);
        }
        else if (hexFormat.length === 7) {
            r = parseInt(hexFormat.slice(1, 3), 16);
            g = parseInt(hexFormat.slice(3, 5), 16);
            b = parseInt(hexFormat.slice(5), 16);
        }
        else if (hexFormat.length === 5) {
            a = parseInt(hexFormat.slice(1, 2).repeat(2), 16);
            r = parseInt(hexFormat.slice(2, 3).repeat(2), 16);
            g = parseInt(hexFormat.slice(3, 4).repeat(2), 16);
            b = parseInt(hexFormat.slice(4).repeat(2), 16);
        }
        else if (hexFormat.length === 9) {
            a = parseInt(hexFormat.slice(1, 3), 16);
            r = parseInt(hexFormat.slice(3, 5), 16);
            g = parseInt(hexFormat.slice(5, 7), 16);
            b = parseInt(hexFormat.slice(7), 16);
        }
        return new ColorMetrics(r, g, b, a);
    }
    blendColor(overlayColor) {
        if (overlayColor === undefined || overlayColor === null) {
            const error = new Error('Parameter error. The type of the input parameter is not ColorMetrics.');
            error.code = ERROR_CODE_COLOR_PARAMETER_INCORRECT;
            throw error;
        }
        const chanels = getUINativeModule().nativeUtils.blendColor(this.toNumeric(), overlayColor.toNumeric());
        if (chanels === undefined) {
            const error = new Error('Parameter error. The type of the input parameter is not ColorMetrics.');
            error.code = ERROR_CODE_COLOR_PARAMETER_INCORRECT;
            throw error;
        }
        const red = chanels[0];
        const green = chanels[1];
        const blue = chanels[2];
        const alpha = chanels[3];
        return new ColorMetrics(red, green, blue, alpha);
    }
    get color() {
        return `rgba(${this.red_}, ${this.green_}, ${this.blue_}, ${this.alpha_ / MAX_CHANNEL_VALUE})`;
    }
    get red() {
        return this.red_;
    }
    get green() {
        return this.green_;
    }
    get blue() {
        return this.blue_;
    }
    get alpha() {
        return this.alpha_;
    }
    setResourceId(resourceId) {
        this.resourceId_ = resourceId;
    }
    getResourceId() {
        return this.resourceId_;
    }
}
class BaseShape {
    constructor() {
        this.rect = null;
        this.roundRect = null;
        this.circle = null;
        this.oval = null;
        this.path = null;
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
class ShapeClip extends BaseShape {
}
class ShapeMask extends BaseShape {
    constructor(...args) {
        super(...args);
        this.fillColor = 0XFF000000;
        this.strokeColor = 0XFF000000;
        this.strokeWidth = 0;
    }
}
class RenderNode {
    constructor(type) {
        this.nodePtr = null;
        this.childrenList = [];
        this.parentRenderNode = null;
        this.backgroundColorValue = 0;
        this.apiTargetVersion = getUINativeModule().common.getApiTargetVersion();
        this.clipToFrameValue = true;
        if (this.apiTargetVersion && this.apiTargetVersion < 12) {
            this.clipToFrameValue = false;
        }
        this.frameValue = { x: 0, y: 0, width: 0, height: 0 };
        this.opacityValue = 1.0;
        this.pivotValue = { x: 0.5, y: 0.5 };
        this.rotationValue = { x: 0, y: 0, z: 0 };
        this.scaleValue = { x: 1.0, y: 1.0 };
        this.shadowColorValue = 0;
        this.shadowOffsetValue = { x: 0, y: 0 };
        this.labelValue = '';
        this.shadowAlphaValue = 0;
        this.shadowElevationValue = 0;
        this.shadowRadiusValue = 0;
        this.transformValue = [1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1];
        this.translationValue = { x: 0, y: 0 };
        this.lengthMetricsUnitValue = LengthMetricsUnit.DEFAULT;
        this.markNodeGroupValue = false;
        if (type === 'BuilderRootFrameNode' || type === 'CustomFrameNode') {
            return;
        }
        this._nativeRef = getUINativeModule().renderNode.createRenderNode(this);
        this.nodePtr = this._nativeRef?.getNativeHandle();
        if (this.apiTargetVersion && this.apiTargetVersion < 12) {
            this.clipToFrame = false;
        }
        else {
            this.clipToFrame = true;
        }
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
        getUINativeModule().renderNode.setPosition(this.nodePtr, this.frameValue.x, this.frameValue.y, this.lengthMetricsUnitValue);
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
        getUINativeModule().renderNode.setRotation(this.nodePtr, this.rotationValue.x, this.rotationValue.y, this.rotationValue.z, this.lengthMetricsUnitValue);
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
        getUINativeModule().renderNode.setShadowOffset(this.nodePtr, this.shadowOffsetValue.x, this.shadowOffsetValue.y, this.lengthMetricsUnitValue);
    }
    set label(label) {
        this.labelValue = this.checkUndefinedOrNullWithDefaultValue(label, '');
        getUINativeModule().renderNode.setLabel(this.nodePtr, this.labelValue);
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
        getUINativeModule().renderNode.setSize(this.nodePtr, this.frameValue.width, this.frameValue.height, this.lengthMetricsUnitValue);
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
    set lengthMetricsUnit(unit) {
        if (unit === undefined || unit == null) {
            this.lengthMetricsUnitValue = LengthMetricsUnit.DEFAULT;
        }
        else {
            this.lengthMetricsUnitValue = unit;
        }
    }
    set markNodeGroup(isNodeGroup) {
        if (isNodeGroup === undefined || isNodeGroup === null) {
            this.markNodeGroupValue = false;
        }
        else {
            this.markNodeGroupValue = isNodeGroup;
        }
        getUINativeModule().renderNode.setMarkNodeGroup(this.nodePtr, this.markNodeGroupValue);
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
    get label() {
        return this.labelValue;
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
    get lengthMetricsUnit() {
        return this.lengthMetricsUnitValue;
    }
    get markNodeGroup() {
        return this.markNodeGroupValue;
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
    setFrameNode(frameNode) {
        this._frameNode = frameNode;
    }
    setNodePtr(nativeRef) {
        this._nativeRef = nativeRef;
        this.nodePtr = this._nativeRef?.getNativeHandle();
    }
    setBaseNode(baseNode) {
        this.baseNode_ = baseNode.builderBaseNode_;
    }
    resetNodePtr() {
        this.nodePtr = null;
        this._nativeRef = null;
    }
    dispose() {
        this._nativeRef?.dispose();
        this.baseNode_?.disposeNode();
        this._frameNode?.deref()?.resetNodePtr();
        this._nativeRef = null;
        this.nodePtr = null;
    }
    getNodePtr() {
        return this.nodePtr;
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
        getUINativeModule().renderNode.setBorderWidth(this.nodePtr, this.borderWidthValue.left, this.borderWidthValue.top, this.borderWidthValue.right, this.borderWidthValue.bottom, this.lengthMetricsUnitValue);
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
        getUINativeModule().renderNode.setBorderRadius(this.nodePtr, this.borderRadiusValue.topLeft, this.borderRadiusValue.topRight, this.borderRadiusValue.bottomLeft, this.borderRadiusValue.bottomRight, this.lengthMetricsUnitValue);
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
            const roundRect = this.shapeMask.roundRect;
            const corners = roundRect.corners;
            const rect = roundRect.rect;
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
    set shapeClip(shapeClip) {
        if (shapeClip === undefined || shapeClip === null) {
            this.shapeClipValue = new ShapeClip();
        }
        else {
            this.shapeClipValue = shapeClip;
        }
        if (this.shapeClipValue.rect !== null) {
            const rectClip = this.shapeClipValue.rect;
            getUINativeModule().renderNode.setRectClip(this.nodePtr, rectClip.left, rectClip.top, rectClip.right, rectClip.bottom);
        }
        else if (this.shapeClipValue.circle !== null) {
            const circle = this.shapeClipValue.circle;
            getUINativeModule().renderNode.setCircleClip(this.nodePtr, circle.centerX, circle.centerY, circle.radius);
        }
        else if (this.shapeClipValue.roundRect !== null) {
            const roundRect = this.shapeClipValue.roundRect;
            const corners = roundRect.corners;
            const rect = roundRect.rect;
            getUINativeModule().renderNode.setRoundRectClip(this.nodePtr, corners.topLeft.x, corners.topLeft.y, corners.topRight.x, corners.topRight.y, corners.bottomLeft.x, corners.bottomLeft.y, corners.bottomRight.x, corners.bottomRight.y, rect.left, rect.top, rect.right, rect.bottom);
        }
        else if (this.shapeClipValue.oval !== null) {
            const oval = this.shapeClipValue.oval;
            getUINativeModule().renderNode.setOvalClip(this.nodePtr, oval.left, oval.top, oval.right, oval.bottom);
        }
        else if (this.shapeClipValue.path !== null) {
            const path = this.shapeClipValue.path;
            getUINativeModule().renderNode.setPathClip(this.nodePtr, path.commands);
        }
    }
    get shapeClip() {
        this.shapeClipValue = this.shapeClipValue ? this.shapeClipValue : new ShapeClip();
        return this.shapeClipValue;
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
    constructor(uiContext, options, id, type, libraryname, controller) {
        super(uiContext, 'XComponentNode');
        const elmtId = ViewStackProcessor.AllocateNewElmetIdForNextComponent();
        this.xcomponentNode_ = getUINativeModule().xcomponentNode;
        this.renderType_ = options.type;
        const surfaceId = options.surfaceId;
        const selfIdealWidth = options.selfIdealSize.width;
        const selfIdealHeight = options.selfIdealSize.height;
        this.nativeModule_ = this.xcomponentNode_.create(elmtId, id, type, this.renderType_, surfaceId, selfIdealWidth, selfIdealHeight, libraryname, controller);
        this.xcomponentNode_.registerOnCreateCallback(this.nativeModule_, this.onCreate);
        this.xcomponentNode_.registerOnDestroyCallback(this.nativeModule_, this.onDestroy);
        this.nodePtr_ = this.xcomponentNode_.getFrameNode(this.nativeModule_);
        this.setNodePtr(getUINativeModule().nativeUtils.createNativeStrongRef(this.nodePtr_), this.nodePtr_);
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
class Content {
    constructor() { }
    onAttachToWindow() { }
    onDetachFromWindow() { }
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
class ComponentContent extends Content {
    constructor(uiContext, builder, params, options) {
        super();
        let builderNode = new BuilderNode(uiContext, {});
        this.builderNode_ = builderNode;
        this.builderNode_.build(builder, params ?? undefined, options);
    }
    update(params) {
        this.builderNode_.update(params);
    }
    getFrameNode() {
        return this.builderNode_.getFrameNodeWithoutCheck();
    }
    setAttachedParent(parent) {
        this.parentWeak_ = parent;
    }
    getNodePtr() {
        if (this.attachNodeRef_ !== undefined) {
            return this.attachNodeRef_.getNativeHandle();
        }
        return this.builderNode_.getNodePtr();
    }
    reuse(param) {
        this.builderNode_.reuse(param);
    }
    recycle() {
        this.builderNode_.recycle();
    }
    onReuseWithBindObject(param) {
        this.builderNode_.onReuseWithBindObject(param);
    }
    onRecycleWithBindObject() {
        this.builderNode_.onRecycleWithBindObject();
    }
    dispose() {
        this.detachFromParent();
        this.attachNodeRef_?.dispose();
        this.builderNode_?.dispose();
    }
    detachFromParent() {
        if (this.parentWeak_ === undefined) {
            return;
        }
        let parent = this.parentWeak_.deref();
        if (parent !== undefined) {
            parent.removeComponentContent(this);
        }
    }
    getNodeWithoutProxy() {
        const node = this.getNodePtr();
        const nodeType = getUINativeModule().frameNode.getNodeType(node);
        if (nodeType === "BuilderProxyNode") {
            const result = getUINativeModule().frameNode.getFirstUINode(node);
            this.attachNodeRef_ = getUINativeModule().nativeUtils.createNativeStrongRef(result);
            getUINativeModule().frameNode.removeChild(node, result);
            return result;
        }
        return node;
    }
    updateConfiguration() {
        this.builderNode_.updateConfiguration();
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
class NodeContent extends Content {
    constructor() {
        super();
        this.nativeRef_ = getUINativeModule().frameNode.createNodeContent();
        this.nativePtr_ = this.nativeRef_.getNativeHandle();
        this.nodeArray_ = new Array();
    }
    addFrameNode(node) {
        if (this.nodeArray_.includes(node)) {
            return;
        }
        if (getUINativeModule().frameNode.addFrameNodeToNodeContent(node.getNodePtr(), this.nativePtr_)) {
            this.nodeArray_.push(node);
        }
    }
    removeFrameNode(node) {
        if (!this.nodeArray_.includes(node)) {
            return;
        }
        if (getUINativeModule().frameNode.removeFrameNodeFromNodeContent(node.getNodePtr(), this.nativePtr_)) {
            let index = this.nodeArray_.indexOf(node);
            if (index > -1) {
                this.nodeArray_.splice(index, 1);
            }
        }
    }
}

export default {
    NodeController, BuilderNode, BaseNode, RenderNode, FrameNode, FrameNodeUtils,
    NodeRenderType, XComponentNode, LengthMetrics, ColorMetrics, LengthUnit, LengthMetricsUnit, ShapeMask, ShapeClip,
    edgeColors, edgeWidths, borderStyles, borderRadiuses, Content, ComponentContent, NodeContent,
    typeNode, NodeAdapter, ExpandMode
};
