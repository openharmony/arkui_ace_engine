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

class ComponentContent extends Content implements IDisposable {
  // the name of "builderNode_" is used in ace_engine/interfaces/native/node/native_node_napi.cpp.
  private builderNode_: BuilderNode;
  private attachNodeRef_: NativeStrongRef;
  private parentWeak_: WeakRef<FrameNode> | undefined;
  private disposable_: Disposable;
  constructor(uiContext: UIContext, builder: WrappedBuilder<[]> | WrappedBuilder<[Object]>, params?: Object, options?: BuildOptions) {
    super();
    let builderNode = new BuilderNode(uiContext, {});
    this.builderNode_ = builderNode;
    this.builderNode_.build(builder, params ?? undefined, options);
    this.disposable_ = new Disposable();
  }

  public update(params: Object) {
    this.builderNode_.update(params);
  }

  public getFrameNode(): FrameNode | null | undefined {
    return this.builderNode_.getFrameNodeWithoutCheck();
  }
  public setAttachedParent(parent: WeakRef<FrameNode> | undefined) {
    this.parentWeak_ = parent;
  }
  public getNodePtr(): NodePtr {
    if (this.attachNodeRef_ !== undefined) {
      return this.attachNodeRef_.getNativeHandle();
    }
    return this.builderNode_.getNodePtr();
  }
  public reuse(param: Object): void {
    this.builderNode_.reuse(param);
  }
  public recycle(): void {
    this.builderNode_.recycle();
  }
  public onReuseWithBindObject(param?: Object): void {
    this.builderNode_.onReuseWithBindObject(param);
  }
  public onRecycleWithBindObject(): void {
    this.builderNode_.onRecycleWithBindObject();
  }
  public dispose(): void {
    if (this.getNodePtr()) {
      getUINativeModule().frameNode.fireArkUIObjectLifecycleCallback(new WeakRef(this), 'ComponentContent', this.getFrameNode()?.getNodeType() || 'ComponentContent', this.getNodePtr());
    }
    this.disposable_.dispose();
    this.detachFromParent();
    this.attachNodeRef_?.dispose();
    this.builderNode_?.dispose();
  }

  public isDisposed(): boolean {
    return this.disposable_.isDisposed() && (this.builderNode_ ? this.builderNode_.isDisposed() : true);
  }
  
  public detachFromParent() {
    if (this.parentWeak_ === undefined) {
      return;
    }
    let parent = this.parentWeak_.deref();
    if (parent !== undefined) {
      parent.removeComponentContent(this);
    }
  }

  public getNodeWithoutProxy(): NodePtr {
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

  public updateConfiguration(): void {
    this.builderNode_.updateConfiguration();
  }

  public inheritFreezeOptions(enable: boolean): void {
    this.builderNode_.inheritFreezeOptions(enable);
  }
}
