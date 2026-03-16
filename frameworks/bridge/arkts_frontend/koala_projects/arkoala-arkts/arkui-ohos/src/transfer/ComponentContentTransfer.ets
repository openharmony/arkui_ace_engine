/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
import { UIContextTransfer } from '../handwritten/transfer/UIContextTransfer';
import { ComponentContent } from '../ComponentContent';
import { UIContext } from '@ohos.arkui.UIContext';
import { KPointer } from '@koalaui/interop';
import { int32 } from '@koalaui/compat';
import { FrameNodeExtender } from '../framework';
import { BusinessError } from '#external';
import { RecordData } from '@ohos.base';

export class ComponentContentTransfer {
    static transferStatic(input: Any): Object {
        if (typeof (input) !== 'object') {
            throw Error('The ComponentContent is not object convert fail.');
        }
        if (input === null) {
            throw Error('The ComponentContent is null convert fail.');
        }
        let arkUINode = ESValue.load('@ohos.arkui.node').getProperty('default');

        let frameNodeDyn = ESValue.wrap(input).invokeMethod('getFrameNodePtr');
        if (typeof (frameNodeDyn) !== 'object') {
            throw Error('The ComponentContent transferStatic failed: frameNode is not object.');
        }
        let getFrameNodeRawPtr = arkUINode.getProperty('getFrameNodeRawPtr');
        let frameNodeRawPtr = getFrameNodeRawPtr.invoke(frameNodeDyn! as Object).toNumber();
        let frameNodePeer = FrameNodeExtender.createByRawPtr(frameNodeRawPtr as KPointer);

        let nodePtrDyn = ESValue.wrap(input).invokeMethod('getNodePtr');
        if (typeof(nodePtrDyn) !== 'object') {
            throw Error('The ComponentContent transferStatic failed: get NodePtr failed.');
        }
        let nodeRawPtr = getFrameNodeRawPtr.invoke(nodePtrDyn as Object).toNumber();

        let instanceId = ESValue.wrap(input).invokeMethod('getInstanceId').toNumber();
        let uiContextSta = new UIContext(instanceId as int32);
        return new TransComponentContent(uiContextSta as UIContext, nodeRawPtr as KPointer, frameNodePeer);
    }

    static transferDynamic(input: Object): Any {
        if (typeof (input) !== 'object') {
            throw Error('The ComponentContent is not object convert fail.');
        }
        if (input === null) {
            throw Error('The ComponentContent is null convert fail.');
        }
        let componentContentSta = input as ComponentContent;
        const instanceId = componentContentSta.getInstanceId();
        let uiContext = UIContextTransfer.createDynamic(instanceId);

        let rootPtr = componentContentSta.getBuilderRootNode();
        if (rootPtr === undefined) {
            throw Error('The ComponentContent transferDynamic failed: get root node failed.');
        }

        let frameNodeSta = componentContentSta!.getFrameNode();
        if (frameNodeSta === null || frameNodeSta === undefined || frameNodeSta!.nodePtr_ === null) {
            throw Error('The ComponentContent transferDynamic failed: get frameNode failed.');
        }
        let frameNodeStaPtr = frameNodeSta!.nodePtr_;
        let frameNodeRawPtr = FrameNodeExtender.unWrapRawPtr(frameNodeStaPtr!);

        let arkUINode = ESValue.load('@ohos.arkui.node').getProperty('default');
        let createComponentContent = arkUINode.getProperty('createComponentContentByTrans');
        let componentContentWrapper = createComponentContent.invoke(uiContext as Object, rootPtr, frameNodeRawPtr);
        return componentContentWrapper.unwrap();
    }
}

export class TransComponentContent<T = undefined> extends ComponentContent<T> {
    constructor(uiContext: UIContext, nodePtr: KPointer, frameNodePtr: KPointer) {
        super(uiContext, nodePtr, frameNodePtr);
    }

    isTransferred(): boolean {
        return true;
    }

    update(params: T): void {
        const error = Error('componentContent created by transferStatic not support update');
        throw new BusinessError(100021, error);
    }

    reuse(param?: RecordData): void {
        const error = Error('componentContent created by transferStatic not support reuse');
        throw new BusinessError(100021, error);
    }

    recycle(): void {
        const error = Error('componentContent created by transferStatic not support recycle');
        throw new BusinessError(100021, error);
    }

    updateConfiguration(): void {
        const error = Error('componentContent created by transferStatic not support updateConfiguration');
        throw new BusinessError(100021, error);
    }
}
