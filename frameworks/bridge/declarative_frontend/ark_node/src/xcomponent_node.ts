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
  private nativeModule_: any;
  private xcomponentNode_: any;
  private renderType_: NodeRenderType;
  constructor(uiContext: UIContext, options: RenderOptions,
    id: string, type: XComponentType, libraryname?: string, controller?: XComponentController) {
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

  onCreate(event?: object): void { }

  onDestroy(): void { }

  changeRenderType(type: NodeRenderType): boolean {
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
