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

import { FrameNode } from "./FrameNode";
import { UIContext } from "@ohos/arkui/UIContext"
import { Size } from "./Graphics";
import { TouchEvent } from "./component/common";
import { ArkNodeContainerComponent } from "./component/nodeContainer";

export abstract class NodeController {
    _nodeContainer: ArkNodeContainerComponent | null = null
    _rootNodeOfNodeController: FrameNode | null = null
    setNodeContainer(nodeContainer: ArkNodeContainerComponent) {
        this._nodeContainer = nodeContainer;
    }
    resetInternalField() {
        this._nodeContainer = null;
        this._rootNodeOfNodeController = null;
    }
    abstract makeNode(UIContext: UIContext): FrameNode | null;
    __makeNode__(uiContext: UIContext): FrameNode | null {
        this._rootNodeOfNodeController = this.makeNode(uiContext);
        return this._rootNodeOfNodeController;

    }
    rebuild() {
        if (this._nodeContainer) {
            this._nodeContainer!.rebuild();
        }
    }
    aboutToResize(size: Size) { }
    aboutToAppear() { }
    aboutToDisappear() { }
    onTouchEvent(event: TouchEvent) {}
    onAttach() { }
    onDetach() { }
    onBind(containerId: number) { }
    onUnbind(containerId: number) { }
    onWillBind(containerId: number) { }
    onWillUnbind(containerId: number) { }
}
