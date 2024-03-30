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
  private map_: Map<Symbol, ModifierWithKey<number | string | boolean | object>>;
  private changeCallback: ((key: Symbol, value: ModifierWithKey<number | string | boolean | object>) => void) | undefined;

  constructor() {
    this.map_ = new Map();
  }

  public clear(): void {
    this.map_.clear();
  }

  public delete(key: Symbol): boolean {
    return this.map_.delete(key);
  }

  public forEach(callbackfn: (value: ModifierWithKey<number | string | boolean | object>, key: Symbol,
    map: Map<Symbol, ModifierWithKey<number | string | boolean | object>>) => void, thisArg?: any): void {
    this.map_.forEach(callbackfn, thisArg);
  }
  public get(key: Symbol): ModifierWithKey<number | string | boolean | object> | undefined {
    return this.map_.get(key);
  }
  public has(key: Symbol): boolean {
    return this.map_.has(key);
  }
  public set(key: Symbol, value: ModifierWithKey<number | string | boolean | object>): this {
    const _a = this.changeCallback;
    this.map_.set(key, value);
    _a === null || _a === void 0 ? void 0 : _a(key, value);
    return this;
  }
  public get size(): number {
    return this.map_.size;
  }
  public entries(): IterableIterator<[Symbol, ModifierWithKey<number | string | boolean | object>]> {
    return this.map_.entries();
  }
  public keys(): IterableIterator<Symbol> {
    return this.map_.keys();
  }
  public values(): IterableIterator<ModifierWithKey<number | string | boolean | object>> {
    return this.map_.values();
  }
  public [Symbol.iterator](): IterableIterator<[Symbol, ModifierWithKey<number | string | boolean | object>]> {
    return this.map_.entries();
  }
  public get [Symbol.toStringTag](): string {
    return 'FrameNodeAttributeMapTag';
  }
  public setOnChange(callback: (key: Symbol, value: ModifierWithKey<number | string | boolean | object>) => void): void {
    if (this.changeCallback === undefined) {
      this.changeCallback = callback;
    }
  }
}

class FrameNodeModifier extends ArkComponent {
  constructor(nodePtr: NodePtr) {
    super(nodePtr);
    this._modifiersWithKeys = new FrameNodeAttributeMap();
    this._modifiersWithKeys.setOnChange((key, value) => {
      if (this.nativePtr === undefined) {
        return;
      }
      value.applyStage(this.nativePtr);
      getUINativeModule().frameNode.propertyUpdate(this.nativePtr);
    })
  }
  setNodePtr(nodePtr: NodePtr): void {
    this.nativePtr = nodePtr;
  }
}

class FrameNode {
  private renderNode_: RenderNode;
  private baseNode_: BaseNode;
  protected nodePtr_: NodePtr;
  protected uiContext_: UIContext | undefined | null;
  private nodeId_: number;
  private type_: string;
  private _commonAttribute: FrameNodeModifier;
  private _commonEvent: UICommonEvent;
  private _childList :Map<number,FrameNode>
  constructor(uiContext: UIContext, type: string) {
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
    FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.set(this.nodeId_, new WeakRef(this))
    FrameNodeFinalizationRegisterProxy.register(this, this.nodeId_);
    this.renderNode_.setNodePtr(this.nodePtr_);
    this.renderNode_.setBaseNode(this.baseNode_);
  }
  getRenderNode(): RenderNode | null {
    if (
      this.renderNode_ !== undefined &&
      this.renderNode_ !== null &&
      this.renderNode_.getNodePtr() !== null && this.type_ !== 'ArkTsNode'
    ) {
      return this.renderNode_;
    }
    return null;
  }
  setNodePtr(nodePtr: NodePtr): void {
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
  setBaseNode(baseNode: BaseNode | null): void {
    this.baseNode_ = baseNode;
    this.renderNode_.setBaseNode(baseNode);
  }
  getNodePtr(): NodePtr {
    return this.nodePtr_;
  }
  dispose(): void {
    this.baseNode_.dispose();
    FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.delete(this.nodeId_);
    this.nodeId_ = -1;
    this.nodePtr_ = null;
  }

  checkType(): void {
    if (!getUINativeModule().frameNode.isModifiable(this.nodePtr_)) {
      throw { message: 'The FrameNode is not modifiable.', code: 100021 };
    }
  }
  isModifiable(): boolean {
    return getUINativeModule().frameNode.isModifiable(this.nodePtr_);
  }
  convertToFrameNode(nodePtr: NodePtr): FrameNode | null {
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
  appendChild(node: FrameNode): void {
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
    this._childList.set(node.nodeId_,node);
  }
  insertChildAfter(child: FrameNode, sibling: FrameNode): void {
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
    this._childList.set(child.nodeId_,child);
  }
  removeChild(node: FrameNode): void {
    this.checkType();
    if (node === undefined || node === null) {
      return;
    }
    getUINativeModule().frameNode.removeChild(this.nodePtr_, node.nodePtr_);
    this._childList.delete(node.nodeId_);
  }
  clearChildren(): void {
    this.checkType();
    getUINativeModule().frameNode.clearChildren(this.nodePtr_);
    this._childList.clear();
  }
  getChild(index: number): FrameNode | null {
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
  getFirstChild(): FrameNode | null {
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
  getNextSibling(): FrameNode | null {
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
  getPreviousSibling(): FrameNode | null {
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
  getParent(): FrameNode | null {
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
  getChildrenCount(): number {
    const number = getUINativeModule().frameNode.getChildrenCount(this.nodePtr_);
    return number;
  }
  getPositionToParent(): Position {
    const position = getUINativeModule().frameNode.getPositionToParent(this.nodePtr_);
    return { x: position[0], y: position[1] };
  }

  getPositionToWindow(): Position {
    const position = getUINativeModule().frameNode.getPositionToWindow(this.nodePtr_);
    return { x: position[0], y: position[1] };
  }

  get commonAttribute(): ArkComponent {
    if (this._commonAttribute === undefined) {
      this._commonAttribute = new FrameNodeModifier(this.nodePtr_);
    }
    this._commonAttribute.setNodePtr((this.type_ === 'BuilderNode' || this.type_ === 'ArkTsNode') ? undefined : this.nodePtr_);
    return this._commonAttribute;
  }

  get commonEvent(): UICommonEvent {
    if (this._commonEvent === undefined) {
      this._commonEvent = new UICommonEvent(this.nodePtr_);
    }
    this._commonEvent.setNodePtr(this.nodePtr_);
    this._commonEvent.setInstanceId((this.uiContext_ === undefined || this.uiContext_ === null) ? -1 : this.uiContext_.instanceId_);
    return this._commonEvent;
  }
}

class FrameNodeUtils {
  static searchNodeInRegisterProxy(nodePtr: NodePtr): FrameNode | null {
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

  static createFrameNode(uiContext: UIContext, nodePtr: NodePtr): FrameNode | null {
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
