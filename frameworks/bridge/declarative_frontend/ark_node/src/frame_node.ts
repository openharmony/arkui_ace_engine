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

class FrameNode extends BaseNode {
  private renderNode_: RenderNode;
  constructor(uiContext: UIContext, type: string) {
    super(uiContext);
    this.renderNode_ = new RenderNode("FrameNode");
    if (type == "BuilderNode") {
      return;
    }
    this.nodePtr_ = this.createRenderNode();
    this.renderNode_.setNodePtr(this.nodePtr_);
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
  setNodePtr(nodePtr: number | null) {
    this.nodePtr_ = nodePtr;
    this.renderNode_.setNodePtr(nodePtr);
  }
  getNodePtr(): number | null {
    return this.nodePtr_;
  }
}
