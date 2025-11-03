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

import { Rect, Circle, RoundRect, CommandPath, Size, Frame, Vector2, Vector3, Matrix4, NodeEdges, Corners, ShapeMask, ShapeClip, LengthMetricsUnit, DrawContext } from "../Graphics"
import { BorderStyle } from "../component/enums"
import { RenderNode } from "../RenderNode"
import { ArkUIAniModule } from "arkui.ani"
import hilog from '@ohos.hilog'
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, InteropNativeModule } from "@koalaui/interop"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { int16, uint32 } from "@koalaui/compat"
import { ShapeClipTransfer } from "../handwritten/transfer/ShapeClipTransfer"
import { ShapeMaskTransfer } from "../handwritten/transfer/ShapeMaskTransfer"
import { TransferUtil } from "../handwritten/transfer/TransferUtil"

export class RenderNodeTransfer {
    private mapNodeStatic = new Map<int, RenderNode>();
    private mapNodeDynamic = new Map<int, ESValue>();

    private transProperty2Static(inVal: ESValue, rn: RenderNode): void {
        rn.lengthMetricsUnit = TransferUtil.getPropNumber(inVal, "lengthMetricsUnitValue") as int as LengthMetricsUnit;
        let styleVal = TransferUtil.getPropBorderStyle(inVal, "borderStyleValue");
        if (styleVal) {
            rn.borderStyle = styleVal as NodeEdges<BorderStyle>;
        }
        let borderWidthVal = TransferUtil.getPropBorderNoExcept(inVal, "borderWidthValue");
        if (borderWidthVal) {
            rn.borderWidth = borderWidthVal as NodeEdges<number>;
        }
        let borderColorVal = TransferUtil.getPropEdgesColor(inVal, "borderColorValue");
        if (borderColorVal) {
            rn.borderColor = borderColorVal as NodeEdges<int>;
        }
        let borderRadiusVal = TransferUtil.getPropCornersNoExcept(inVal, "borderRadiusValue");
        if (borderRadiusVal) {
            rn.borderRadius = borderRadiusVal as Corners<number>;
        }
        let maskVal = TransferUtil.getPropShapeMask(inVal, "shapeMaskValue");
        if (maskVal) {
            rn.shapeMask = maskVal as ShapeMask;
        }
        let clipVal = TransferUtil.getPropShapeClip(inVal, "shapeClipValue");
        if (clipVal) {
            rn.shapeClip = clipVal as ShapeClip;
        }
        let colorVal = TransferUtil.getPropColorInt(inVal, "backgroundColorValue");
        if (colorVal !== undefined) {
            rn.backgroundColor = colorVal as int;
        }
        rn.clipToFrame = TransferUtil.getPropBool(inVal, "clipToFrameValue");
        rn.frame = TransferUtil.getPropFrame(inVal, "frameValue");
        rn.opacity = TransferUtil.getPropNumber(inVal, "opacityValue");
        rn.pivot = TransferUtil.getPropVector2(inVal, "pivotValue");
        rn.rotation = TransferUtil.getPropVector3(inVal, "rotationValue");

        rn.scale = TransferUtil.getPropVector2(inVal, "scaleValue");
        let ClrVal = TransferUtil.getPropColorInt(inVal, "shadowColorValue");
        if (ClrVal !== undefined) {
            rn.shadowColor = ClrVal as int;
        }
        rn.shadowOffset = TransferUtil.getPropVector2(inVal, "shadowOffsetValue");
        rn.label = TransferUtil.getPropString(inVal, "labelValue");
        rn.shadowAlpha = TransferUtil.getPropNumber(inVal, "shadowAlphaValue");
        rn.shadowElevation = TransferUtil.getPropNumber(inVal, "shadowElevationValue");
        rn.shadowRadius = TransferUtil.getPropNumber(inVal, "shadowRadiusValue");
        rn.transform = TransferUtil.getPropMatrix4(inVal, "transformValue");
        rn.translation = TransferUtil.getPropVector2(inVal, "translationValue");
        rn.markNodeGroup = TransferUtil.getPropBool(inVal, "markNodeGroupValue");
        // rn.frameNode_;   NOT required transfer.  WeakRef<FrameNode>
    }

    // 1. get nodePtr
    // 2. get nodeId
    // 3. check map
    // 4. transfer property
    public transfer2S(input: Object): RenderNode | undefined {
        let inVal = ESValue.wrap(input);
        if (inVal.isNull() || inVal.isUndefined()) {
            return undefined;
        }

        // try get nodePtr(1.1)
        let nativeRef = TransferUtil.getPropNativeRef(inVal, "_nativeRef");
        // get nodePtr value
        let nodePtrVal = TransferUtil.getNodePtrValue(nativeRef);
        if (nodePtrVal === 0) {
            return undefined;
        }

        // get node id
        let nodeId = ArkUIAniModule._GetNodeIdWithNodePtr(nodePtrVal);
        if (nodeId <= 0) {
            return undefined;
        }
        // check if exist
        if (this.mapNodeStatic.has(nodeId)) {
            let tsNode = this.mapNodeStatic.get(nodeId);
            return tsNode as RenderNode;
        }
        // get node type
        let typeStr : string | undefined = TransferUtil.getPropStringType(inVal, "type");
        let tsNode: RenderNode = new RenderNode(nodePtrVal, typeStr);
        this.mapNodeStatic.set(nodeId, tsNode);
        // tsNode set property
        this.transProperty2Static(inVal, tsNode);
        // set parent
        let ParentVal = inVal.getProperty("parentRenderNode");
        if (ParentVal.isObject()) {
            let parVal = TransferUtil.nodeDeref(ParentVal.unwrap()! as Object);
            if (parVal !== undefined) {
                this.transfer2S(parVal as Object);
            }
        }
 
        // set children
        let childrenVal = inVal.getProperty("childrenList") ;
        for (let i = 0; ; i++ ) {
            const childVal = childrenVal.getProperty(i);
            if (childVal.isNull() || childVal.isUndefined()) {
                break;
            }
            const childObj = childVal.unwrap() as Object;
            let childNode = this.transfer2S(childObj);
            if (childNode === undefined) {
                break;
            }
            tsNode.appendChild(childNode as RenderNode);
        }
        return tsNode;
    }

    /**
     * @description cast to 1.1 (dynaimc)
     * @param type : node type
     * @param nodePtr : pointer of FrameNode
     * @returns ESValue object of RenderNode
     */
    private instantiateRenderNodeDynamic(type: string | undefined, nodePtr: KPointer): ESValue {
        let module = ESValue.load('@ohos.arkui.node');
        if (module.isUndefined() || module.isNull()) {
            throw Error("The arkui.node is not defined, convert fail.");
        }
        let clsName = module.getProperty('RenderNode');
        if (clsName.isUndefined() || clsName.isNull()) {
            throw Error("RenderNode is not a class, convert fail.");
        }
        let objVal = clsName.instantiate(type, nodePtr);
        return objVal;
    }

    private transferProperty2Dynamic(inRn: RenderNode, outJs: ESValue) {
        console.log("testTag. 2D prop...");
        // [peer, type, nodePtrVal, nodeId, _nativeRef ] init on constructor, apiTargetVersion not need
        TransferUtil.setPropNumber('lengthMetricsUnitValue', inRn.lengthMetricsUnit, outJs);

        if (inRn.borderStyle) {
            TransferUtil.setPropEdgeStyle('borderStyleValue', inRn.borderStyle!, outJs);
        }
        if (inRn.borderWidth) {
            TransferUtil.setPropEdges('borderWidthValue', inRn.borderWidth!, outJs);
        }
        if (inRn.borderColor) {
            TransferUtil.setPropEdgesColor('borderColorValue', inRn.borderColor!, outJs);
        }
        if (inRn.borderRadius) {
            TransferUtil.setPropCorners('borderRadiusValue', inRn.borderRadius!, outJs);
        }
        if (inRn.shapeMask) {
            TransferUtil.setPropShapeMask('shapeMaskValue', inRn.shapeMask!, outJs);
        }
        if (inRn.shapeClip) {
            TransferUtil.setPropShapeClip('shapeClipValue', inRn.shapeClip!, outJs);
        }

        TransferUtil.setPropColorLong('backgroundColorValue', inRn.backgroundColor, outJs);
        TransferUtil.setPropBool('clipToFrameValue', inRn.clipToFrame, outJs);
        TransferUtil.setPropFrame('frameValue', inRn.frame, outJs);
        TransferUtil.setPropNumber('opacityValue', inRn.opacity, outJs);
        TransferUtil.setPropVector2('pivotValue', inRn.pivot, outJs);
        TransferUtil.setPropVector3('rotationValue', inRn.rotation, outJs);
        TransferUtil.setPropVector2('scaleValue', inRn.scale, outJs);
        TransferUtil.setPropColorLong('shadowColorValue', inRn.shadowColor, outJs);
        TransferUtil.setPropVector2('shadowOffsetValue', inRn.shadowOffset, outJs); 
        TransferUtil.setPropString('labelValue', inRn.label, outJs);
        TransferUtil.setPropNumber('shadowAlphaValue', inRn.shadowAlpha, outJs);
        TransferUtil.setPropNumber('shadowElevationValue', inRn.shadowElevation, outJs);
        TransferUtil.setPropNumber('shadowRadiusValue', inRn.shadowRadius, outJs);
        TransferUtil.setPropMatrix4('transformValue', inRn.transform, outJs);
        TransferUtil.setPropVector2('translationValue', inRn.translation, outJs);
        TransferUtil.setPropBool('markNodeGroupValue', inRn.markNodeGroup, outJs);
    }

    /**
     * @param input from arkts1.2
     * step:
     *  1. get peerPtr
     *  2. get nodeId
     *  3. check map
     *  4. transfer property
     * @returns Object for arkts1.1
     */
    public transfer2D(input: Object): Object | undefined {
        let inVal = ESValue.wrap(input);
        // get peerPtr
        let peerPtr = TransferUtil.getPropPeerPtr(inVal, "peer");
        if (peerPtr == 0) {
            return undefined;
        }
        // get nodePtr, it's frameNode pointer
        let nodePtr = ArkUIAniModule._GetNodePtrWithPeerPtr(peerPtr);
        // get nodeId
        let nodeId = ArkUIAniModule._GetNodeIdWithPeerPtr(peerPtr);
        if (nodeId <= 0) {
            return undefined;
        }
        if (this.mapNodeDynamic.has(nodeId)) {
            let dVal = this.mapNodeDynamic.get(nodeId);
            let nodeVal = dVal! as ESValue;
            let obj = nodeVal.unwrap();
            return obj! as Object;
        }
        // get type
        let typeStr: string | undefined = TransferUtil.getPropStringType(inVal, "type");
        let jsNodeVal = this.instantiateRenderNodeDynamic(typeStr, nodePtr);
        this.mapNodeDynamic.set(nodeId, jsNodeVal);

        // get property
        let rn = input as RenderNode;
        this.transferProperty2Dynamic(rn, jsNodeVal);

        // get parent ("parentRenderNode")
        let parentVal = rn.getParentNode();
        if (parentVal !== undefined) {
            let parent: RenderNode = parentVal as RenderNode;
            this.transfer2D(parent);
        }
 
        // get children
        let childrenVal = inVal.getProperty("childrenList") ;
        let nCnt = childrenVal.getProperty('length').toNumber()
        for (let i = 0; i < nCnt; i++) {
            let childVal = childrenVal.getProperty(i);
            if (childVal.isNull() || childVal.isUndefined()) {
                break;
            }
            const childObj = childVal.unwrap();
            let jsChild = this.transfer2D(childObj! as Object);
            if (jsChild === undefined) {
                break;
            }
            jsNodeVal.invokeMethod("appendChild", jsChild as Object);
        }
        let obj = jsNodeVal.unwrap();
        return obj as Object;
    }

    /*
       function: transferStatic
       param: input is RenderNode on arkts1.1
       return: Object is RenderNode on arkts1.2
    */
    static transferStatic(input: Any): Object {
        if (input === null || input === undefined) {
            throw new Error("The RenderNode is not object, convert fail.");
        }
    
        const trans = new RenderNodeTransfer();
        const node = trans.transfer2S(input! as Object);
    
        return node !== undefined ? node : new Object();
    }

    /*
       function: transferDynamic
       param: input is RenderNode on arkts1.2
       return: Any is RenderNode on arkts1.1
    */
    static transferDynamic(input: Object): Any {
        if (input === null) {
            throw new Error("The input is not object, convert fail.");
        }

        const trans = new RenderNodeTransfer();
        return trans.transfer2D(input);
    }
}
