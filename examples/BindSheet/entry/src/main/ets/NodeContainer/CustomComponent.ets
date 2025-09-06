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
// 自定义占位节点，跨容器迁移能力
import { BuilderNode, FrameNode, NodeController } from '@kit.ArkUI';

@Builder
function cardBuilder() {
  Image($r('app.media.startIcon'))
    // 避免第一次加载图片时图片闪烁
    .syncLoad(true)
}

export class MyNodeController extends NodeController {
  private cardNode: BuilderNode<[]> | null = null;
  private wrapBuilder: WrappedBuilder<[]> = wrapBuilder(cardBuilder);
  private needCreate: boolean = false;
  private isRemove: boolean = false;

  constructor(create: boolean) {
    super();
    this.needCreate = create;
  }

  makeNode(uiContext: UIContext): FrameNode | null {
    if(this.isRemove == true){
      return null;
    }
    if (this.needCreate && this.cardNode == null) {
      this.cardNode = new BuilderNode(uiContext);
      this.cardNode.build(this.wrapBuilder)
    }
    if (this.cardNode == null) {
      return null;
    }
    return this.cardNode!.getFrameNode()!;
  }

  getNode(): BuilderNode<[]> | null {
    return this.cardNode;
  }

  setNode(node: BuilderNode<[]> | null) {
    this.cardNode = node;
    this.rebuild();
  }

  onRemove() {
    this.isRemove = true;
    this.rebuild();
    this.isRemove = false;
  }

  init(uiContext: UIContext) {
    this.cardNode = new BuilderNode(uiContext);
    this.cardNode.build(this.wrapBuilder)
  }
}

let myNode: MyNodeController | undefined;

export const createMyNode =
  (uiContext: UIContext) => {
    myNode = new MyNodeController(false);
    myNode.init(uiContext);
  }

export const getMyNode = (): MyNodeController | undefined => {
  return myNode;
}