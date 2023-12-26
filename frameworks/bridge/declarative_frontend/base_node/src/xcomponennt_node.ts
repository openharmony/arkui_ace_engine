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
/// <reference path="./index.d.ts" />
/// <reference path="./base_node.ts" />

type XComponentType = /*unresolved*/ any

const arkUINativeModule = globalThis.getArkUINativeModule();
function GetUINativeModule() {
  if (arkUINativeModule) {
    return arkUINativeModule;
  }
  return arkUINativeModule;
}

class XComponentNode extends BaseNode {
  instanceId_?: number;
  elmtId: number;
  nativeModule: any;
  renderOptions: RenderOptions;
  constructor(uiContext: UIContext, options: RenderOptions, size: Size,
    id: string, type: XComponentType, libraryname?: string) {
      super();
      var instanceId: number = -1;
      if (uiContext === undefined) {
          throw Error("BuilderNode construtor error, parem uicontext error");
      }
      else {
          if (!(typeof uiContext === "object") || !("instanceId_" in uiContext)) {
              throw Error("BuilderNode construtor error, parem uicontext is invalid");
          }
          instanceId = uiContext.instanceId_;
      }
      this.instanceId_ = instanceId;

      this.renderOptions = options;
      this.elmtId = ViewStackProcessor.AllocateNewElmetIdForNextComponent();
      var node = GetUINativeModule().xcomponentNode;
      this.nativeModule = node.create(this.elmtId, options, size, id, type, libraryname);
      node.registerOnLoadCallback(this.nativeModule, this.onLoad);
      node.registerOnDestroyCallback(this.nativeModule, this.onDestroy);
  }

  onCreate(event?: object): void {
  }


  onDestroy(): void {
  }

  setRenderType(type: NodeRenderType): void {
    this.renderOptions.type = type;
  }


  getRenderType(): NodeRenderType {
    return this.renderOptions.type;
  }
}
