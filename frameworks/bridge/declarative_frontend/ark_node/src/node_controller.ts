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

class __InternalField__ {
  _value: number;
  __rootNodeOfNodeController__: FrameNode | null;
  constructor()
  {
    this._value = -1;
  }
}

abstract class NodeController {
  _nodeContainerId: __InternalField__;
  constructor() {
    this._nodeContainerId = new __InternalField__();
  }

  abstract makeNode(UIContext: UIContext): FrameNode | null;
  __makeNode__(UIContext: UIContext): FrameNode | null {
    this._nodeContainerId.__rootNodeOfNodeController__ = this.makeNode(UIContext);
    return this._nodeContainerId.__rootNodeOfNodeController__;

  }
  rebuild() {
    if (this._nodeContainerId !== undefined && this._nodeContainerId !== null && this._nodeContainerId._value >= 0) {
      getUINativeModule().nodeContainer.rebuild(this._nodeContainerId._value);
    }
  }
}
