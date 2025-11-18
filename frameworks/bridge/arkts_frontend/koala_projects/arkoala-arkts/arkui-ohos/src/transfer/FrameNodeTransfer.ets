/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import { FrameNode, LayoutConstraint } from '../FrameNode';
import { KPointer } from '@koalaui/interop'
import { UIContextImpl } from '../base/UIContextImpl';
import { int32 } from '@koalaui/compat';
import { UIContextTransfer } from '../handwritten/transfer/UIContextTransfer'
import { UIContext } from '@ohos.arkui.UIContext';
import { RenderNode } from '../RenderNode';
import { BusinessError } from '#external';
import { CustomProperty, CommonMethod, UICommonEvent, UIGestureEvent } from '../component/common';
import { DrawContext, Size } from '../Graphics';
import { Position } from '@ohos.arkui.component';
import { ComponentContent } from '../ComponentContent';
import { ArkUIAniModule } from 'arkui.ani';
import { FrameNodeExtender } from '../framework';
export class FrameNodeTransfer {

    static transferStatic(input: Any): Object {
        if (typeof (input) !== 'object') {
            throw Error('The FrameNode is not object convert fail.');
        }
        if (input === null) {
            throw Error('The FrameNode is null convert fail.');
        }
        const instanceId = ESValue.wrap(input).getProperty('instanceId_').toNumber();
        let nodeType: string | undefined = undefined;
        let nodeTypeESValue = ESValue.wrap(input).getProperty('type_');
        if (nodeTypeESValue.isString()) {
            nodeType = nodeTypeESValue.toString();
        }
        let uiContext = new UIContextImpl(instanceId as int32);
        let arkUINode = ESValue.load('@ohos.arkui.node');
        let frameNodeTrans = arkUINode.getProperty('getFrameNodeRawPtr');
        let point = frameNodeTrans.invoke(input! as Object);
        if (point.isUndefined()) {
            throw Error("The FrameNode point is undefined object convert fail.");
        }
        const pointStr = point.toNumber();
        // todo 
        let frameNodePeerPont = FrameNodeExtender.createByRawPtr(pointStr as KPointer);
        let node: FrameNode = new TransFrameNode(uiContext, nodeType, frameNodePeerPont);
        return node;
    }
    static transferDynamic(input: Object): Any {
        if (input === null) {
            throw Error('The FrameNode is null convert fail.');
        }
        let frameNodeStatic = input as FrameNode;
        const instanceId = frameNodeStatic!.uiContext!.instanceId_;
        const point = frameNodeStatic.nodePtr_;
        if (point === null) {
            throw Error('The FrameNode is not object convert fail.');
        }
        //todo 
        let frameNodeRaw = FrameNodeExtender.unWrapRawPtr(point!);
        let nodeType: string | undefined = frameNodeStatic.nodeType_;
        let arkUINode = ESValue.load('@ohos.arkui.node');
        let frameNodeTrans = arkUINode.getProperty('createFrameNodeByTrans');
        let uiContext = UIContextTransfer.createDynamic(instanceId);
        if (nodeType) {
            let frameNodeWrapper = frameNodeTrans.invoke(frameNodeRaw, uiContext! as Object, nodeType);
            return frameNodeWrapper.unwrap();
        }
        else {
            let frameNodeWrapper = frameNodeTrans.invoke(frameNodeRaw, uiContext! as Object);
            return frameNodeWrapper.unwrap();
        }
    }
}

export class TransFrameNode extends FrameNode {
    constructor(uiContext?: UIContext, type?: string, ptr?: KPointer) {
        super(uiContext, type, ptr);
    }
    public isTransferred(): boolean {
        return true;
    }
    public getRenderNode(): RenderNode | null {
        const error = Error('frameNode created by transferStatic not support getRenderNode');
        throw new BusinessError(100021, error);
    }
    public getCustomProperty(name: string): CustomProperty {
        const error = Error('frameNode created by transferStatic not support getCustomProperty');

        throw new BusinessError(100021, error);
    }
    get commonAttribute(): CommonMethod {
        const error = Error('frameNode created by transferStatic not support commonAttribute');
        throw new BusinessError(100021, error);
    }
    get commonEvent(): UICommonEvent {
        const error = Error('frameNode created by transferStatic not support commonEvent');
        throw new BusinessError(100021, error);
    }
    get gestureEvent(): UIGestureEvent {
        const error = Error('frameNode created by transferStatic not support gestureEvent');
        throw new BusinessError(100021, error);
    }
    public setMeasuredSize(size: Size): void {
        const error = Error('frameNode created by transferStatic not support setMeasuredSize');
        throw new BusinessError(100021, error);
    }
    public setLayoutPosition(position: Position): void {
        const error = Error('frameNode created by transferStatic not support setLayoutPosition');
        throw new BusinessError(100021, error);
    }
    public measure(constraint: LayoutConstraint): void {
        const error = Error('frameNode created by transferStatic not support measure');
        throw new BusinessError(100021, error);
    }
    public layout(position: Position): void {
        const error = Error('frameNode created by transferStatic not support layout');
        throw new BusinessError(100021, error);
    }
    public setNeedsLayout(): void {
        const error = Error('frameNode created by transferStatic not support setNeedsLayout');
        throw new BusinessError(100021, error);
    }
    public invalidate(): void {
        const error = Error('frameNode created by transferStatic not support invalidate');
        throw new BusinessError(100021, error);
    }
    public addComponentContent<T = undefined>(content: ComponentContent<T>) {
        const error = Error('frameNode created by transferStatic not support addComponentContent');
        throw new BusinessError(100021, error);
    }
    final onDraw(context: DrawContext): void {}
    final onMeasure(constraint: LayoutConstraint): void {
        ArkUIAniModule._OnMeasure_InnerMeasure(this!.peer!.ptr);
    }
    final onLayout(position: Position): void {
        ArkUIAniModule._OnLayout_InnerLayout(this!.peer!.ptr);
    }
}