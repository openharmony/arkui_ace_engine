/*
 * Copyright (c) 2023-2025 Huawei Device Co., Ltd.
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
/// <reference path="../../state_mgmt/src/lib/common/ace_console.native.d.ts" />
enum LogTag {
  ARK_COMPONENT = 1,
}
class JSXNodeLogConsole {
  static warn(...args:any) {
      aceConsole.warn(LogTag.ARK_COMPONENT, ...args);
  }
}
enum NodeRenderType {
  RENDER_TYPE_DISPLAY = 0,
  RENDER_TYPE_TEXTURE,
}

declare interface RenderOptions {
  selfIdealSize?: Size,
  type?: NodeRenderType,
  surfaceId?: string
}

declare class DrawContext { }
declare type NodePtr = Object | null;
declare class __JSBaseNode__ {
  constructor(options?: RenderOptions);
  create(builder: (...args: Object[]) => void, params: Object, update: (instanceId: number, nodePtr: NodePtr) => void,
    updateConfiguration, supportLazyBuild: boolean, baseNode: BaseNode): NodePtr;
  finishUpdateFunc(): void;
  postTouchEvent(touchEvent: TouchEvent): boolean;
  postInputEvent(event: InputEventType): boolean;
  disposeNode(): void;
  updateStart(): void;
  updateEnd(): void;
  onRecycleWithBindObject(): void;
  onReuseWithBindObject(object: Object): void;
}
abstract class BaseNode extends ViewBuildNodeBase {
  protected instanceId_?: number;
  protected nodePtr_: NodePtr;
  public builderBaseNode_: __JSBaseNode__;
  constructor(uiContext: UIContext, options?: RenderOptions) {
    super(false);
    let baseNode = new __JSBaseNode__(options);
    this.builderBaseNode_ = baseNode;

    if (uiContext === undefined) {
      throw Error('Node constructor error, param uiContext error');
    } else {
      if (!(typeof uiContext === 'object') || !('instanceId_' in uiContext)) {
        throw Error(
          'Node constructor error, param uiContext is invalid'
        );
      }
    }
    this.instanceId_ = uiContext.instanceId_;
  }
  public getInstanceId() {
    return this.instanceId_;
  }
  updateInstance(uiContext: UIContext): void {
      this.instanceId_ = uiContext.instanceId_;
  }
  create(builder: (...args: Object[]) => void, params: Object, update: (instanceId: number, nodePtr: NodePtr) => void,
    updateConfiguration, supportLazyBuild: boolean): NodePtr {
      return this.builderBaseNode_.create(builder.bind(this), params, update.bind(this), updateConfiguration.bind(this), supportLazyBuild, this);
    }
  finishUpdateFunc(): void {
    return this.builderBaseNode_.finishUpdateFunc();
  }
  postTouchEvent(touchEvent: TouchEvent): boolean {
    return this.builderBaseNode_.postTouchEvent(touchEvent);
  }
  postInputEvent(event: InputEventType): boolean {
    return this.builderBaseNode_.postInputEvent(event);
  }
  disposeNode(): void {
    return this.builderBaseNode_.disposeNode();
  }
  updateStart(): void {
    return this.builderBaseNode_.updateStart();
  }
  updateEnd(): void {
    return this.builderBaseNode_.updateEnd();
  }
  onRecycleWithBindObject(): void {
    return this.builderBaseNode_.onRecycleWithBindObject();
  }
  onReuseWithBindObject(object: Object): void {
    return this.builderBaseNode_.onReuseWithBindObject(object);
  }
  public abstract ifElseBranchUpdateFunctionDirtyRetaken(): void;
  public abstract forceCompleteRerender(deep: boolean): void;
  public abstract forceRerenderNode(elmtId: number): void;
  public abstract purgeDeleteElmtId(rmElmtId: number): boolean;
}
