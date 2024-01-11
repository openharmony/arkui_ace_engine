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
        var instanceId = -1;
        if (uiContext === undefined) {
            throw Error("Node constructor error, param uiContext error");
        }
        else {
            if (!(typeof uiContext === "object") || !("instanceId_" in uiContext)) {
                throw Error("Node constructor error, param uiContext is invalid");
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
        let id = Symbol("BuilderNode");
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
    reset() {
        this._JSBuilderNode.reset();
    }
    getFrameNode() {
        return this._JSBuilderNode.getFrameNode();
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
    updateStateVarsOfChildByElmtId(elmtId, params, updateParams) {
        if (elmtId < 0) {
            return;
        }
        let child = this.getChildById(elmtId);
        if (!child) {
            return;
        }
        if (typeof child.aboutToUpdate === "function") {
            child.aboutToUpdate(updateParams);
        }
    }
    build(builder, params) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        this.params_ = params;
        this.updateFuncByElmtId.clear();
        this.nodePtr_ = super.create(builder.builder, this.params_);
        if (this.frameNode_ === undefined || this.frameNode_ === null) {
            this.frameNode_ = new FrameNode(this.uiContext_, "BuilderNode");
        }
        this.frameNode_.setNodePtr(this.nodePtr_);
        __JSScopeUtil__.restoreInstanceId();
    }
    update(param) {
        __JSScopeUtil__.syncInstanceId(this.instanceId_);
        this.purgeDeletedElmtIds();
        this.params_ = param;
        Array.from(this.updateFuncByElmtId.keys()).sort((a, b) => {
            return (a < b) ? -1 : (a > b) ? 1 : 0;
        }).forEach(elmtId => this.UpdateElement(elmtId));
        __JSScopeUtil__.restoreInstanceId();
    }
    UpdateElement(elmtId) {
        // do not process an Element that has been marked to be deleted
        const obj = this.updateFuncByElmtId.get(elmtId);
        const updateFunc = (typeof obj === "object") ? obj.updateFunc : null;
        if (typeof updateFunc === "function") {
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
        var elmId = ViewStackProcessor.AllocateNewElmetIdForNextComponent();
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
        const _componentName = classObject && "name" in classObject ? Reflect.get(classObject, "name") : "unspecified UINode";
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
        if (branchId == oldBranchid) {
            return;
        }
        // branchId identifies uniquely the if .. <1> .. else if .<2>. else .<3>.branch
        // ifElseNode stores the most recent branch, so we can compare
        // removedChildElmtIds will be filled with the elmtIds of all children and their children will be deleted in response to if .. else change
        var removedChildElmtIds = new Array();
        If.branchId(branchId, removedChildElmtIds);
        this.purgeDeletedElmtIds();
        branchfunc();
    }
    getNodePtr() {
        return this.nodePtr_;
    }
    reset() {
        this.nodePtr_ = null;
        super.reset();
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
            if (heldValue.name === "BuilderNode") {
                const builderNode = BuilderNodeFinalizationRegisterProxy.ElementIdToOwningBuilderNode_.get(heldValue.idOfNode);
                BuilderNodeFinalizationRegisterProxy.ElementIdToOwningBuilderNode_.delete(heldValue.idOfNode);
                builderNode.reset();
            }
        });
    }
    static register(target, heldValue) {
        BuilderNodeFinalizationRegisterProxy.instance_.finalizationRegistry_.register(target, heldValue);
    }
}
BuilderNodeFinalizationRegisterProxy.instance_ = new BuilderNodeFinalizationRegisterProxy();
BuilderNodeFinalizationRegisterProxy.ElementIdToOwningBuilderNode_ = new Map();
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
const arkUINativeModule = globalThis.getArkUINativeModule();
function GetUINativeModule() {
    if (arkUINativeModule) {
        return arkUINativeModule;
    }
    return arkUINativeModule;
}
class NodeController {
    constructor() {
        this.nodeContainerId_ = -1;
    }
    aboutToResize(size) { }
    aboutToAppear() { }
    aboutToDisappear() { }
    onTouchEvent(event) { }
    rebuild() {
        if (this.nodeContainerId_ >= 0) {
            GetUINativeModule().nodeContainer.rebuild(this.nodeContainerId_);
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
class FrameNode {
    constructor(uiContext, type) {
        this.renderNode_ = new RenderNode("FrameNode");
        if (type == "BuilderNode") {
            return;
        }
        this.baseNode_ = new BaseNode(uiContext);
        this.nodePtr_ = this.baseNode_.createRenderNode();
        this.renderNode_.setNodePtr(this.nodePtr_);
    }
    getRenderNode() {
        if (this.renderNode_ !== undefined &&
            this.renderNode_ !== null &&
            this.renderNode_.getNodePtr() !== null) {
            return this.renderNode_;
        }
        return null;
    }
    setNodePtr(nodePtr) {
        this.nodePtr_ = nodePtr;
        this.renderNode_.setNodePtr(nodePtr);
    }
    getNodePtr() {
        return this.nodePtr_;
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
class RenderNode {
    constructor(type) {
        this.nodePtr = null;
        this.childrenList = [];
        this.parentRenderNode = null;
        this.backgroundColorValue = 0;
        this.clipToFrameValue = false;
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
        if (type === "FrameNode") {
            return;
        }
        this.baseNode_ = new __JSBaseNode__();
        this.nodePtr = this.baseNode_.createRenderNode();
    }
    set backgroundColor(color) {
        this.backgroundColorValue = this.checkUndefinedOrNullWithDefaultValue(color, 0);
        GetUINativeModule().common.setBackgroundColor(this.nodePtr, this.backgroundColorValue);
    }
    set clipToFrame(useClip) {
        this.clipToFrameValue = this.checkUndefinedOrNullWithDefaultValue(useClip, false);
        GetUINativeModule().renderNode.setClipToFrame(this.nodePtr, this.clipToFrameValue);
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
        GetUINativeModule().common.setOpacity(this.nodePtr, this.opacityValue);
    }
    set pivot(pivot) {
        if (pivot === undefined || pivot === null) {
            this.pivotValue = { x: 0.5, y: 0.5 };
        }
        else {
            this.pivotValue.x = this.checkUndefinedOrNullWithDefaultValue(pivot.x, 0.5);
            this.pivotValue.y = this.checkUndefinedOrNullWithDefaultValue(pivot.y, 0.5);
        }
        GetUINativeModule().renderNode.setPivot(this.nodePtr, this.pivotValue.x, this.pivotValue.y);
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
        GetUINativeModule().common.setPosition(this.nodePtr, this.frameValue.x, this.frameValue.y);
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
        GetUINativeModule().renderNode.setRotation(this.nodePtr, this.rotationValue.x, this.rotationValue.y, this.rotationValue.z);
    }
    set scale(scale) {
        if (scale === undefined || scale === null) {
            this.scaleValue = { x: 1.0, y: 1.0 };
        }
        else {
            this.scaleValue.x = this.checkUndefinedOrNullWithDefaultValue(scale.x, 1.0);
            this.scaleValue.y = this.checkUndefinedOrNullWithDefaultValue(scale.y, 1.0);
        }
        GetUINativeModule().renderNode.setScale(this.nodePtr, this.scaleValue.x, this.scaleValue.y);
    }
    set shadowColor(color) {
        this.shadowColorValue = this.checkUndefinedOrNullWithDefaultValue(color, 0);
        GetUINativeModule().renderNode.setShadowColor(this.nodePtr, this.shadowColorValue);
    }
    set shadowOffset(offset) {
        if (offset === undefined || offset === null) {
            this.shadowOffsetValue = { x: 0, y: 0 };
        }
        else {
            this.shadowOffsetValue.x = this.checkUndefinedOrNullWithDefaultValue(offset.x, 0);
            this.shadowOffsetValue.y = this.checkUndefinedOrNullWithDefaultValue(offset.y, 0);
        }
        GetUINativeModule().renderNode.setShadowOffset(this.nodePtr, this.shadowOffsetValue.x, this.shadowOffsetValue.y);
    }
    set shadowAlpha(alpha) {
        this.shadowAlphaValue = this.checkUndefinedOrNullWithDefaultValue(alpha, 0);
        GetUINativeModule().renderNode.setShadowAlpha(this.nodePtr, this.shadowAlphaValue);
    }
    set shadowElevation(elevation) {
        this.shadowElevationValue = this.checkUndefinedOrNullWithDefaultValue(elevation, 0);
        GetUINativeModule().renderNode.setShadowElevation(this.nodePtr, this.shadowElevationValue);
    }
    set shadowRadius(radius) {
        this.shadowRadiusValue = this.checkUndefinedOrNullWithDefaultValue(radius, 0);
        GetUINativeModule().renderNode.setShadowRadius(this.nodePtr, this.shadowRadiusValue);
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
        GetUINativeModule().renderNode.setSize(this.nodePtr, this.frameValue.width, this.frameValue.height);
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
        GetUINativeModule().common.setTransform(this.nodePtr, this.transformValue);
    }
    set translation(translation) {
        if (translation === undefined || translation === null) {
            this.translationValue = { x: 0, y: 0 };
        }
        else {
            this.translationValue.x = this.checkUndefinedOrNullWithDefaultValue(translation.x, 0);
            this.translationValue.y = this.checkUndefinedOrNullWithDefaultValue(translation.y, 0);
        }
        GetUINativeModule().renderNode.setTranslate(this.nodePtr, this.translationValue.x, this.translationValue.y, 0);
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
        node.parentRenderNode = this;
        GetUINativeModule().renderNode.appendChild(this.nodePtr, node.nodePtr);
    }
    insertChildAfter(child, sibling) {
        if (child === undefined || child === null) {
            return;
        }
        let indexOfNode = this.childrenList.findIndex(element => element === child);
        if (indexOfNode !== -1) {
            return;
        }
        child.parentRenderNode = this;
        let indexOfSibling = this.childrenList.findIndex(element => element === sibling);
        if (indexOfSibling === -1) {
            sibling === null;
        }
        if (sibling === undefined || sibling === null) {
            this.childrenList.splice(0, 0, child);
            GetUINativeModule().renderNode.insertChildAfter(this.nodePtr, child.nodePtr, null);
        }
        else {
            this.childrenList.splice(indexOfSibling + 1, 0, child);
            GetUINativeModule().renderNode.insertChildAfter(this.nodePtr, child.nodePtr, sibling.nodePtr);
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
        GetUINativeModule().renderNode.removeChild(this.nodePtr, node.nodePtr);
    }
    clearChildren() {
        this.childrenList = new Array();
        GetUINativeModule().renderNode.clearChildren(this.nodePtr);
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
        let siblingList = this.parentRenderNode.childrenList;
        const index = siblingList.findIndex(element => element === this);
        if (index === -1) {
            return null;
        }
        return this.parentRenderNode.getChild(index + 1);
    }
    getPreviousSibling() {
        if (this.parentRenderNode === undefined || this.parentRenderNode === null) {
            return null;
        }
        let siblingList = this.parentRenderNode.childrenList;
        const index = siblingList.findIndex(element => element === this);
        if (index === -1) {
            return null;
        }
        return this.parentRenderNode.getChild(index - 1);
    }
    setNodePtr(nodePtr) {
        this.nodePtr = nodePtr;
    }
    getNodePtr() {
        return this.nodePtr;
    }
    draw(context) {
    }
    invalidate() {
        GetUINativeModule().renderNode.invalidate(this.nodePtr);
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
class XComponentNode extends FrameNode {
    constructor(uiContext, options, id, type, libraryname) {
        super(uiContext, "XComponentNode");
        const elmtId = ViewStackProcessor.AllocateNewElmetIdForNextComponent();
        this.xcomponentNode_ = GetUINativeModule().xcomponentNode;
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

export default { NodeController, BuilderNode, BaseNode, RenderNode, FrameNode, NodeRenderType, XComponentNode };
