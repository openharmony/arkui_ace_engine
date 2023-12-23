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

abstract class NodeController {
  nodeContainerId_: number;
  constructor() {
    this.nodeContainerId_ = -1;
  }

  abstract makeNode(UIContext: UIContext): FrameNode | null;
  aboutToResize(size: Size) { }
  aboutToAppear() { }
  aboutToDisappear() { }
  onTouchEvent(event: TouchEvent) { }

  rebuild() {
    if (this.nodeContainerId_ >= 0) {
      GetUINativeModule().nodeContainer.rebuild(this.nodeContainerId_);
    }
  }
}
