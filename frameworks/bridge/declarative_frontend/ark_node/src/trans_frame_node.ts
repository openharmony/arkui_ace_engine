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
/// <reference path="./frame_node.ts" />
function createFrameNodeByTrans(nativePointer, uiContext, nodeType) {
   return new TransFrameNode(uiContext, nodeType, undefined, nativePointer);
}

class TransFrameNode extends FrameNode {
    constructor(uiContext: UIContext, type: string, options?: object, nativePointer?: number) {
        super(uiContext, type, options, nativePointer);
    }
    public isTransferred(): boolean {
        return true;
    }
    public getRenderNode(): RenderNode | null {
        throw Error('frameNode created by transferDynamic not support getRenderNode');
    }
    public getCustomProperty(name: string): Object | undefined {
        throw Error('frameNode created by transferDynamic not support getCustomProperty');
    }
    get commonAttribute(): ArkComponent {
        throw Error('frameNode created by transferDynamic not support commonAttribute');
    }
    get commonEvent(): UICommonEvent {
        throw Error('frameNode created by transferDynamic not support commonEvent');
    }
    get gestureEvent(): UIGestureEvent {
        throw Error('frameNode created by transferDynamic not support gestureEvent');
    }
    public setMeasuredSize(size: Size): void {
        throw Error('frameNode created by transferDynamic not support setMeasuredSize');
    }
    public setLayoutPosition(position: Position): void {
        throw Error('frameNode created by transferDynamic not support setLayoutPosition');
    }
    public measure(constraint: LayoutConstraint): void {
        throw Error('frameNode created by transferDynamic not support measure');
    }
    public layout(position: Position): void {
        throw Error('frameNode created by transferDynamic not support layout');
    }
    public setNeedsLayout(): void {
        throw Error('frameNode created by transferDynamic not support setNeedsLayout');
    }
    public invalidate(): void {
        throw Error('frameNode created by transferDynamic not support invalidate');
    }
    public addComponentContent(content: ComponentContent): void {
        throw Error('frameNode created by transferDynamic not support addComponentContent');
    }
}