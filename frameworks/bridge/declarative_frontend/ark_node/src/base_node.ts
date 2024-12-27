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
    updateConfiguration, supportLazyBuild: boolean): NodePtr;
  finishUpdateFunc(): void;
  postTouchEvent(touchEvent: TouchEvent): boolean;
  disposeNode(): void;
  updateStart(): void;
  updateEnd(): void;
  onRecycleWithBindObject(): void;
  onReuseWithBindObject(object: Object): void;
}

class BaseNode extends __JSBaseNode__ {
  protected instanceId_?: number;
  protected nodePtr_: NodePtr;
  constructor(uiContext: UIContext, options?: RenderOptions) {
    super(options);

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
}
