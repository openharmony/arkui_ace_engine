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

class FrameNode {
  public _nodeId: number;
  protected _commonAttribute: ArkComponent;
  protected _commonEvent: UICommonEvent;
  protected _childList: Map<number, FrameNode>;
  protected _nativeRef: NativeStrongRef | NativeWeakRef;
  protected renderNode_: RenderNode;
  protected baseNode_: BaseNode;
  protected uiContext_: UIContext | undefined | null;
  protected nodePtr_: NodePtr;
  protected instanceId_?: number;
  constructor(uiContext: UIContext, type: string) {
    if (uiContext === undefined) {
      throw Error('Node constructor error, param uiContext error');
    } else {
      if (!(typeof uiContext === "object") || !("instanceId_" in uiContext)) {
        throw Error(
          'Node constructor error, param uiContext is invalid'
        );
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
    } else {
      result = getUINativeModule().frameNode.createTypedFrameNode(this, type);
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
  getType(): string {
    return 'CustomFrameNode';
  }
  setRenderNode(nativeRef: NativeStrongRef): void {
    this.renderNode_?.setNodePtr(nativeRef);
  }
  getRenderNode(): RenderNode | null {
    if (
      this.renderNode_ !== undefined &&
      this.renderNode_ !== null &&
      this.renderNode_.getNodePtr() !== null
    ) {
      return this.renderNode_;
    }
    return null;
  }
  setNodePtr(nativeRef: NativeStrongRef | NativeWeakRef): void {
    this._nativeRef = nativeRef;
    if (nativeRef === null || nativeRef === undefined) {
      this.resetNodePtr();
      return;
    }
    this.nodePtr_ = this._nativeRef.getNativeHandle();
    this._nodeId = getUINativeModule().frameNode.getIdByNodePtr(this.nodePtr_);
    if (this._nodeId === -1) {
      return;
    }
    FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.set(this._nodeId, new WeakRef(this));
    FrameNodeFinalizationRegisterProxy.register(this, this._nodeId);
  }
  resetNodePtr(): void {
    FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.delete(this._nodeId);
    this._nodeId = -1;
    this._nativeRef = null;
    this.nodePtr_ = null;
    this.renderNode_?.resetNodePtr();
  }
  setBaseNode(baseNode: BaseNode | null): void {
    this.baseNode_ = baseNode;
    this.renderNode_?.setBaseNode(baseNode);
  }
  getNodePtr(): NodePtr | null {
    return this.nodePtr_;
  }
  dispose(): void {
    this.renderNode_?.dispose();
    FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.delete(this._nodeId);
    this._nodeId = -1;
    this._nativeRef = null;
    this.nodePtr_ = null;
  }

  checkType(): void {
    if (!this.isModifiable()) {
      throw { message: 'The FrameNode is not modifiable.', code: 100021 };
    }
  }
  isModifiable(): boolean {
    return this._nativeRef !== undefined && this._nativeRef !== null;
  }

  convertToFrameNode(nodePtr: NodePtr, nodeId: number = -1): FrameNode | null {
    if (nodeId === -1) {
      nodeId = getUINativeModule().frameNode.getIdByNodePtr(nodePtr);
    }
    if (nodeId !== -1 && !getUINativeModule().frameNode.isModifiable(nodePtr)) {
      let frameNode = new ProxyFrameNode(this.uiContext_);
      let node = getUINativeModule().nativeUtils.createNativeWeakRef(nodePtr);
      frameNode.setNodePtr(node);
      frameNode._nodeId = nodeId;
      FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.set(frameNode._nodeId, new WeakRef(frameNode));
      FrameNodeFinalizationRegisterProxy.register(frameNode, frameNode._nodeId);
      return frameNode;
    }
    return null;
  }

  appendChild(node: FrameNode): void {
    if (node === undefined || node === null) {
      return;
    }
    if (node.getType() === 'ProxyFrameNode') {
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

  addComponentContent(content: ComponentContent): void {
    if (content === undefined || content === null || content.getNodePtr() === null || content.getNodePtr() == undefined) {
      return;
    }
    __JSScopeUtil__.syncInstanceId(this.instanceId_);
    let flag = getUINativeModule().frameNode.appendChild(this.nodePtr_, content.getNodePtr());
    __JSScopeUtil__.restoreInstanceId();
    if (!flag) {
      throw { message: 'The FrameNode is not modifiable.', code: 100021 };
    }
  }

  insertChildAfter(child: FrameNode, sibling: FrameNode): void {
    if (child === undefined || child === null) {
      return;
    }
    if (child.getType() === 'ProxyFrameNode') {
      throw { message: 'The FrameNode is not modifiable.', code: 100021 };
    }
    let flag = true;
    __JSScopeUtil__.syncInstanceId(this.instanceId_);
    if (sibling === undefined || sibling === null) {
      flag = getUINativeModule().frameNode.insertChildAfter(this.nodePtr_, child.nodePtr_, null);
    } else {
      flag = getUINativeModule().frameNode.insertChildAfter(this.nodePtr_, child.nodePtr_, sibling.getNodePtr());
    }
    __JSScopeUtil__.restoreInstanceId();
    if (!flag) {
      throw { message: 'The FrameNode is not modifiable.', code: 100021 };
    }
    this._childList.set(child._nodeId, child);
  }

  removeChild(node: FrameNode): void {
    if (node === undefined || node === null) {
      return;
    }
    __JSScopeUtil__.syncInstanceId(this.instanceId_);
    getUINativeModule().frameNode.removeChild(this.nodePtr_, node.nodePtr_);
    __JSScopeUtil__.restoreInstanceId();
    this._childList.delete(node._nodeId);
  }

  clearChildren(): void {
    __JSScopeUtil__.syncInstanceId(this.instanceId_);
    getUINativeModule().frameNode.clearChildren(this.nodePtr_);
    __JSScopeUtil__.restoreInstanceId();
    this._childList.clear();
  }
  getChild(index: number): FrameNode | null {
    const result = getUINativeModule().frameNode.getChild(this.getNodePtr(), index);
    const nodeId = result?.nodeId;
    if (nodeId === undefined || nodeId === -1) {
      return null;
    }
    if (FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.has(nodeId)) {
      var frameNode = FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.get(nodeId).deref();
      return frameNode === undefined ? null : frameNode;
    }
    return this.convertToFrameNode(result.nodePtr, result.nodeId);
  }

  getFirstChild(): FrameNode | null {
    const result = getUINativeModule().frameNode.getFirst(this.getNodePtr());
    const nodeId = result?.nodeId;
    if (nodeId === undefined || nodeId === -1) {
      return null;
    }
    if (FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.has(nodeId)) {
      var frameNode = FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.get(nodeId).deref();
      return frameNode === undefined ? null : frameNode;
    }
    return this.convertToFrameNode(result.nodePtr, result.nodeId);
  }

  getNextSibling(): FrameNode | null {
    const result = getUINativeModule().frameNode.getNextSibling(this.getNodePtr());
    const nodeId = result?.nodeId;
    if (nodeId === undefined || nodeId === -1) {
      return null;
    }
    if (FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.has(nodeId)) {
      var frameNode = FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.get(nodeId).deref();
      return frameNode === undefined ? null : frameNode;
    }
    return this.convertToFrameNode(result.nodePtr, result.nodeId);
  }

  getPreviousSibling(): FrameNode | null {
    const result = getUINativeModule().frameNode.getPreviousSibling(this.getNodePtr());
    const nodeId = result?.nodeId;
    if (nodeId === undefined || nodeId === -1) {
      return null;
    }
    if (FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.has(nodeId)) {
      var frameNode = FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.get(nodeId).deref();
      return frameNode === undefined ? null : frameNode;
    }
    return this.convertToFrameNode(result.nodePtr, result.nodeId);
  }

  getParent(): FrameNode | null {
    const result = getUINativeModule().frameNode.getParent(this.getNodePtr());
    const nodeId = result?.nodeId;
    if (nodeId === undefined || nodeId === -1) {
      return null;
    }
    if (FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.has(nodeId)) {
      var frameNode = FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.get(nodeId).deref();
      return frameNode === undefined ? null : frameNode;
    }
    return this.convertToFrameNode(result.nodePtr, result.nodeId);
  }

  getChildrenCount(): number {
    return getUINativeModule().frameNode.getChildrenCount(this.nodePtr_);
  }

  getPositionToParent(): Position {
    const position = getUINativeModule().frameNode.getPositionToParent(this.getNodePtr());
    return { x: position[0], y: position[1] };
  }

  getPositionToWindow(): Position {
    const position = getUINativeModule().frameNode.getPositionToWindow(this.getNodePtr());
    return { x: position[0], y: position[1] };
  }

  getMeasuredSize(): Size {
    const size = getUINativeModule().frameNode.getMeasuredSize(this.getNodePtr());
    return { width: size[0], height: size[1] };
  }

  getLayoutPosition(): Position {
    const position = getUINativeModule().frameNode.getLayoutPosition(this.getNodePtr());
    return { x: position[0], y: position[1] };
  }

  getUserConfigBorderWidth(): EdgesT<LengthMetrics> {
    const borderWidth = getUINativeModule().frameNode.getConfigBorderWidth(this.getNodePtr());
    return {
      top: new LengthMetrics(borderWidth[0], borderWidth[1]),
      right: new LengthMetrics(borderWidth[2], borderWidth[3]),
      bottom: new LengthMetrics(borderWidth[4], borderWidth[5]),
      left: new LengthMetrics(borderWidth[6], borderWidth[7])
    };
  }

  getUserConfigPadding(): EdgesT<LengthMetrics> {
    const borderWidth = getUINativeModule().frameNode.getConfigPadding(this.getNodePtr());
    return {
      top: new LengthMetrics(borderWidth[0], borderWidth[1]),
      right: new LengthMetrics(borderWidth[2], borderWidth[3]),
      bottom: new LengthMetrics(borderWidth[4], borderWidth[5]),
      left: new LengthMetrics(borderWidth[6], borderWidth[7])
    };
  }

  getUserConfigMargin(): EdgesT<LengthMetrics> {
    const margin = getUINativeModule().frameNode.getConfigMargin(this.getNodePtr());
    return {
      top: new LengthMetrics(margin[0], margin[1]),
      right: new LengthMetrics(margin[2], margin[3]),
      bottom: new LengthMetrics(margin[4], margin[5]),
      left: new LengthMetrics(margin[6], margin[7])
    };
  }

  getUserConfigSize(): SizeT<LengthMetrics> {
    const size = getUINativeModule().frameNode.getConfigSize(this.getNodePtr());
    return {
      width: new LengthMetrics(size[0], size[1]),
      height: new LengthMetrics(size[2], size[3])
    };
  }

  getId(): string {
    return getUINativeModule().frameNode.getId(this.getNodePtr());
  }

  getUniqueId(): number {
      return getUINativeModule().frameNode.getIdByNodePtr(this.getNodePtr());
  }

  getNodeType(): string {
    return getUINativeModule().frameNode.getNodeType(this.getNodePtr());
  }

  getOpacity(): number {
    return getUINativeModule().frameNode.getOpacity(this.getNodePtr());
  }

  isVisible(): boolean {
    return getUINativeModule().frameNode.isVisible(this.getNodePtr());
  }

  isClipToFrame(): boolean {
    return getUINativeModule().frameNode.isClipToFrame(this.getNodePtr());
  }

  isAttached(): boolean {
    return getUINativeModule().frameNode.isAttached(this.getNodePtr());
  }

  getInspectorInfo(): Object {
    const inspectorInfoStr = getUINativeModule().frameNode.getInspectorInfo(this.getNodePtr());
    const inspectorInfo = JSON.parse(inspectorInfoStr);
    return inspectorInfo;
  }

  getCustomProperty(key: string): Object | undefined {
    return key === undefined ? undefined : __getCustomProperty__(this._nodeId, key);
  }

  get commonAttribute(): ArkComponent {
    if (this._commonAttribute === undefined) {
      this._commonAttribute = new ArkComponent(this.nodePtr_, ModifierType.FRAME_NODE);
    }
    this._commonAttribute.setNodePtr(this.nodePtr_);
    return this._commonAttribute;
  }

  get commonEvent(): UICommonEvent {
    let node = this.getNodePtr();
    if (this._commonEvent === undefined) {
      this._commonEvent = new UICommonEvent(node);
    }
    this._commonEvent.setNodePtr(node);
    this._commonEvent.setInstanceId((this.uiContext_ === undefined || this.uiContext_ === null) ? -1 : this.uiContext_.instanceId_);
    return this._commonEvent;
  }
}

class ImmutableFrameNode extends FrameNode {
  isModifiable(): boolean {
    return false;
  }
  invalidate() {
    return;
  }
  appendChild(node: FrameNode): void {
    throw { message: 'The FrameNode is not modifiable.', code: 100021 };
  }
  insertChildAfter(child: FrameNode, sibling: FrameNode): void {
    throw { message: 'The FrameNode is not modifiable.', code: 100021 };
  }
  removeChild(node: FrameNode): void {
    throw { message: 'The FrameNode is not modifiable.', code: 100021 };
  }
  clearChildren(): void {
    throw { message: 'The FrameNode is not modifiable.', code: 100021 };
  }
  get commonAttribute(): ArkComponent {
    if (this._commonAttribute === undefined) {
      this._commonAttribute = new ArkComponent(undefined, ModifierType.FRAME_NODE);
    }
    this._commonAttribute.setNodePtr(undefined);
    return this._commonAttribute;
  }
}

class BuilderRootFrameNode extends ImmutableFrameNode {
  constructor(uiContext: UIContext, type: string = 'BuilderRootFrameNode') {
    super(uiContext, type);
  }
  getType(): string {
    return 'BuilderRootFrameNode';
  }
}

class ProxyFrameNode extends ImmutableFrameNode {
  _nativeRef: NativeWeakRef;

  constructor(uiContext: UIContext, type: string = 'ProxyFrameNode') {
    super(uiContext, type);
  }

  setNodePtr(nativeRef: NativeWeakRef) {
    this._nativeRef = nativeRef;
    this.nodePtr_ = this._nativeRef.getNativeHandle();
  }
  getType(): string {
    return 'ProxyFrameNode';
  }
  getRenderNode(): RenderNode | null {
    return null;
  }
  getNodePtr(): NodePtr | null {
    if (this._nativeRef === undefined || this._nativeRef === null || this._nativeRef.invalid()) {
      return null;
    }
    return this.nodePtr_;
  }
  dispose(): void {
    this.renderNode_?.dispose();
    FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.delete(this._nodeId);
    this._nodeId = -1;
    this._nativeRef = undefined;
    this.nodePtr_ = undefined;
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

class TypedFrameNode<T extends ArkComponent> extends FrameNode {
  attribute_: T;
  attrCreator_: (node: NodePtr, type: ModifierType) => T

  constructor(uiContext: UIContext, type: string, attrCreator: (node: NodePtr, type: ModifierType) => T) {
    super(uiContext, type)
    this.attrCreator_ = attrCreator;
  }

  initialize(...args: Object[]): T {
    return this.attribute.initialize(args);
  }

  get attribute(): T {
    if (this.attribute_ === undefined) {
      this.attribute_ = this.attrCreator_(this.nodePtr_, ModifierType.FRAME_NODE);
    }
    this.attribute_.setNodePtr(this.nodePtr_);
    return this.attribute_;
  }
}

const __creatorMap__ = new Map<string, (context: UIContext) => FrameNode>(
  [
    ["Text", (context: UIContext) => {
      return new TypedFrameNode(context, "Text", (node: NodePtr, type: ModifierType) => {
        return new ArkTextComponent(node, type);
      })
    }],
    ["Column", (context: UIContext) => {
      return new TypedFrameNode(context, "Column", (node: NodePtr, type: ModifierType) => {
        return new ArkColumnComponent(node, type);
      })
    }],
    ["Row", (context: UIContext) => {
      return new TypedFrameNode(context, "Row", (node: NodePtr, type: ModifierType) => {
        return new ArkRowComponent(node, type);
      })
    }],
    ["Stack", (context: UIContext) => {
      return new TypedFrameNode(context, "Stack", (node: NodePtr, type: ModifierType) => {
        return new ArkStackComponent(node, type);
      })
    }],
  ]
)

class TypedNode {
  static createNode(context: UIContext, type: string): FrameNode {
    let creator = __creatorMap__.get(type)
    if (creator === undefined) {
      return undefined
    }
    return creator(context);
  }
}
