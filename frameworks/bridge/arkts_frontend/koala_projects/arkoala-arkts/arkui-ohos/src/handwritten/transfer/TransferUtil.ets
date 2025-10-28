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

import { Rect, Circle, RoundRect, CommandPath, Size, Frame, Vector2, Vector3, Matrix4, NodeEdges, Corners, ShapeMask, ShapeClip, LengthMetricsUnit, DrawContext } from '../../Graphics'
import { KPointer } from '@koalaui/interop'
import { BorderStyle } from '../../component/enums'
import { ArkUIAniModule } from 'arkui.ani'
import { ShapeClipTransfer } from './ShapeClipTransfer'
import { ShapeMaskTransfer } from './ShapeMaskTransfer'

export class TransferUtil {
    /*******************************************************************************
        cast to 1.2 (static), function of get property
    *******************************************************************************/ 
    // with throw
    static getPropNumber(inVal: ESValue, name: string): number {
        let nameVal = inVal.getProperty(name);
        if (nameVal.isUndefined() || nameVal.isNull()) {
            throw Error('prop number is null, convert fail.');
        }
        let num = nameVal.toNumber();
        return num;
    }

    static getPropNumberNoExcept(inVal: ESValue, name: string): number | undefined {
        return inVal.getProperty(name)?.toNumber() ?? undefined;
    }

    /* 
       function: getPropColorInt,
       description: number color: long(1.1) -> int(1.2)
       example:
       1. color = Color.Red   -> number
       2. color = '#FF000000' -> number
       3. color = 0xFF000000  -> number
    */
    static getPropColorInt(inVal: ESValue, name: string): number | undefined {
        const propVal = inVal.getProperty(name);
        if (propVal.typeOf() === 'string') {
            let parStr = propVal.toString();
            if (parStr.startsWith('#')) {
                parStr = parStr.replace('#', '0x');
            }
            const nVal = Number(parStr);
            return ArkUIAniModule._ToColorInt(Double.toLong(nVal));
        } else if (propVal.typeOf() === 'number') {
            const nVal = propVal.toNumber();
            return ArkUIAniModule._ToColorInt(Double.toLong(nVal));
        }
        return undefined;
    }

    // 通用工具函数
    private static invokeModuleFunction(moduleId: string, functionName: string, input: Object): ESValue | undefined {
        const module = ESValue.load(moduleId);
        const func = module.getProperty(functionName);
        const result = func.invoke(input);
        return result.isUndefined() || result.isNull() ? undefined : result;
    }

    // get node deref
    static nodeDeref(input: Object): Object | undefined {
        let objVal = TransferUtil.invokeModuleFunction('@ohos.arkui.node', 'nodeDeref', input);
        return objVal?.unwrap() as Object | undefined;
    }
    // get nodePtr Value on arkts1.1
    static getNodePtrValue(input: Object): KPointer {
        const result = TransferUtil.invokeModuleFunction('@ohos.arkui.node', 'getNodePtrValue', input);
        return result ? Double.toLong(result.unwrap() as number) : 0;
    }

    // get nativeRef on arkts1.1. 
    static getPropNativeRef(inVal: ESValue, name: string): Object {
        const refVal = inVal.getProperty(name);
        if (refVal.isNull() || refVal.isUndefined()) {
            throw new Error('nativeRef is null, transfer error.');
        }
        return refVal.unwrap() as Object;
    }

    // nodeId: -> 1.2(int)
    static getPropNumberInt(inVal: ESValue, name: string): int {
        let nVal = inVal.getProperty(name);
        if (nVal.isNumber()) {
            let num = nVal.toNumber();
            return Double.toInt(num);
        }
        return -1;
    }

    // peerPtr on arkts1.2
    static getPropPeerPtr(inVal: ESValue, name: string): long {
        let peerVal = inVal.getProperty(name);
        if (peerVal.isNull() || peerVal.isUndefined()) {
            return 0;
        }
        let ptrVal = peerVal.getProperty('ptr');
        if (!ptrVal.isNumber()) {
            return 0
        }
        let num = ptrVal.unwrap();
        return num as long;
    }

    static getPropBool(inVal: ESValue, name: string): boolean {
        let bVal = inVal.getProperty(name);
        if (bVal.isUndefined() || bVal.isNull()) {
            throw Error('prop boolen is null, convert fail.');
        }
        return bVal.toBoolean();
    }

    static getPropString(inVal: ESValue, name: string): string {
        let sVal = inVal.getProperty(name);
        if (sVal.isUndefined() || sVal.isNull()) {
            throw Error('prop string is null, convert fail.');
        }
        return sVal.toString();
    }

    static getPropStringType(inVal: ESValue, name: string): string | undefined {
        let sVal = inVal.getProperty(name);
        if (!sVal.isString()) {
            return undefined;
        }
        return sVal.toString();
    }

    static getPropVector2(inVal: ESValue, name: string): Vector2 {
        let vctVal = inVal.getProperty(name);
        if (vctVal.isUndefined() || vctVal.isNull()) {
            throw Error('prop vector2 is null, convert fail.');
        }
        let x = vctVal.getProperty('x').toNumber();
        let y = vctVal.getProperty('y').toNumber();
        return {x: x, y: y} as Vector2;
    }

    static getPropVector3(inVal: ESValue, name: string): Vector3 {
        let v3Val = inVal.getProperty(name);
        if (v3Val.isUndefined() || v3Val.isNull()) {
            throw Error('prop vector3 is null, convert fail.');
        }
        let x = v3Val.getProperty('x').toNumber();
        let y = v3Val.getProperty('y').toNumber();
        let z = v3Val.getProperty('z').toNumber();
        return {x: x, y: y, z: z} as Vector3;
    }

    static getPropBorderStyle(inVal: ESValue, name: string): NodeEdges<BorderStyle> | undefined {
        const borderVal = inVal.getProperty(name);
        if (borderVal.isUndefined() || borderVal.isNull()) {
            return undefined;
        }
    
        const getStyle = (property: string): BorderStyle | undefined => {
            const val = borderVal.getProperty(property);
            return val.isNumber() ? Double.toInt(val.toNumber()) as BorderStyle : undefined;
        };
    
        return {
            left: getStyle('left'),
            top: getStyle('top'),
            right: getStyle('right'),
            bottom: getStyle('bottom')
        } as NodeEdges<BorderStyle>;
    }

    // borderWidthValue: 1.1 -> 1.2(int)
    static getPropBorderNoExcept(inVal: ESValue, name: string): NodeEdges<number> | undefined {
        let borderVal = inVal.getProperty(name);
        if (borderVal.isUndefined() || borderVal.isNull()) {
            return undefined;
        }
        let left = TransferUtil.getPropNumberNoExcept(borderVal, 'left');
        let top = TransferUtil.getPropNumberNoExcept(borderVal, 'top');
        let right = TransferUtil.getPropNumberNoExcept(borderVal, 'right');
        let bottom = TransferUtil.getPropNumberNoExcept(borderVal, 'bottom');
        let egVal = {left: left, top: top, right: right, bottom: bottom} as NodeEdges<number>;
        return egVal;
    }

    // number color: 1.1(long) -> 1.2(int)
    static getPropEdgesColor(inVal: ESValue, name: string): NodeEdges<number> | undefined {
        let borderVal = inVal.getProperty(name);
        if (borderVal.isUndefined() || borderVal.isNull()) {
            return undefined;
        }
        let left = TransferUtil.getPropColorInt(borderVal, 'left');
        let top = TransferUtil.getPropColorInt(borderVal, 'top');
        let right = TransferUtil.getPropColorInt(borderVal, 'right');
        let bottom = TransferUtil.getPropColorInt(borderVal, 'bottom');
        let egVal = {left: left, top: top, right: right, bottom: bottom} as NodeEdges<number>;
        return egVal;
    }

    static getPropCornersNoExcept(inVal: ESValue, name: string): Corners<number> | undefined {
        let corVal = inVal.getProperty(name);
        if (corVal.isUndefined() || corVal.isNull()) {
            return undefined;
        }
        let r1 = corVal.getProperty('topLeft').toNumber();
        let r2 = corVal.getProperty('topRight').toNumber();
        let r3 = corVal.getProperty('bottomLeft').toNumber();
        let r4 = corVal.getProperty('bottomRight').toNumber();
        return {topLeft: r1, topRight: r2, bottomLeft: r3, bottomRight: r4} as Corners<number>;
    }

    static getPropFrame(inVal: ESValue, name: string): Frame {
        let frameVal = inVal.getProperty(name);
        if (frameVal.isUndefined() || frameVal.isNull()) {
            throw Error('prop frame is null, convert fail.');
        }
        // 'frameValue'
        let x = frameVal.getProperty('x').toNumber();
        let y = frameVal.getProperty('y').toNumber();
        let w = frameVal.getProperty('width').toNumber();
        let h = frameVal.getProperty('height').toNumber();
        return {x: x, y: y, width: w, height: h} as Frame;
    }

    static getPropMatrix4(inVal: ESValue, name: string): Matrix4 {
        let mxVal = inVal.getProperty(name);
        if (mxVal.isUndefined() || mxVal.isNull()) {
            throw Error('prop matrix4 is null, convert fail.');
        }
        let mx4: Matrix4 = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
        mx4[0] = mxVal.getProperty(0).toNumber();
        mx4[1] = mxVal.getProperty(1).toNumber();
        mx4[2] = mxVal.getProperty(2).toNumber();
        mx4[3] = mxVal.getProperty(3).toNumber();
        mx4[4] = mxVal.getProperty(4).toNumber();
        mx4[5] = mxVal.getProperty(5).toNumber();
        mx4[6] = mxVal.getProperty(6).toNumber();
        mx4[7] = mxVal.getProperty(7).toNumber();
        mx4[8] = mxVal.getProperty(8).toNumber();
        mx4[9] = mxVal.getProperty(9).toNumber();
        mx4[10] = mxVal.getProperty(10).toNumber();
        mx4[11] = mxVal.getProperty(11).toNumber();
        mx4[12] = mxVal.getProperty(12).toNumber();
        mx4[13] = mxVal.getProperty(13).toNumber();
        mx4[14] = mxVal.getProperty(14).toNumber();
        mx4[15] = mxVal.getProperty(15).toNumber();
        return mx4;
    }

    static getPropShapeMask(inVal: ESValue, name: string): ShapeMask | undefined {
        let shpVal = inVal.getProperty(name);
        if (shpVal.isUndefined() || shpVal.isNull()) {
            return undefined;
        }
        let shpObj = shpVal.unwrap();
        let shape = ShapeMaskTransfer.transferStatic(shpObj);
        return shape as ShapeMask;
    }
    static getPropShapeClip(inVal: ESValue, name: string): ShapeClip | undefined {
        let shpVal = inVal.getProperty(name);
        if (shpVal.isUndefined() || shpVal.isNull()) {
            return undefined;
        }
        let shpObj = shpVal.unwrap();
        let shape = ShapeClipTransfer.transferStatic(shpObj);
        return shape as ShapeClip;
    }

    /*******************************************************************************
       cast to 1.1 (dynaimc), function of set property
    *******************************************************************************/ 
    static setPropNumber(name: string, inVal: number, outJs: ESValue) {
        outJs.setProperty(name, inVal);
    }

    // number color: int(1.2) -> long(1.1)
    static setPropColorLong(name: string, inVal: int | undefined, outJs: ESValue) {
        if (inVal === undefined) {
            return;
        }
    
        const colorLong = ArkUIAniModule._ToColorLong(Double.toInt(inVal));
        outJs.setProperty(name, colorLong);
    }

    static setPropBool(name: string, inVal: boolean, outJs: ESValue) {
        outJs.setProperty(name, inVal);
    }
     
    static setPropString(name: string, inVal: string, outJs: ESValue) {
        outJs.setProperty(name, inVal);
    }

    static setPropEdges(name: string, inVal: NodeEdges<number>, outJs: ESValue) {
        let propVal: ESValue = ESValue.instantiateEmptyObject();
        propVal.setProperty('left', inVal.left);
        propVal.setProperty('top', inVal.top);
        propVal.setProperty('right', inVal.right);
        propVal.setProperty('bottom', inVal.bottom);
        outJs.setProperty(name, propVal);
    }

    // number color: int(1.2) -> long(1.1)
    static setPropEdgesColor(name: string, inVal: NodeEdges<int>, outJs: ESValue) {
        let propVal: ESValue = ESValue.instantiateEmptyObject();
        TransferUtil.setPropColorLong('left', inVal.left, propVal);
        TransferUtil.setPropColorLong('top', inVal.top, propVal);
        TransferUtil.setPropColorLong('right', inVal.right, propVal);
        TransferUtil.setPropColorLong('bottom', inVal.bottom, propVal);
        outJs.setProperty(name, propVal);
    }

    static setPropEdgeStyle(name: string, inVal: NodeEdges<BorderStyle>, outJs: ESValue) {
        const propVal: ESValue = ESValue.instantiateEmptyObject();
        const setEdgeProperty = (propertyName: string, value: BorderStyle | undefined) => {
            if (value !== undefined) {
                const num = Double.toInt(value.valueOf());
                propVal.setProperty(propertyName, num);
            }
        };
    
        setEdgeProperty('left', inVal.left);
        setEdgeProperty('top', inVal.top);
        setEdgeProperty('right', inVal.right);
        setEdgeProperty('bottom', inVal.bottom);    
        outJs.setProperty(name, propVal);
    }

    static setPropCorners(name: string, inVal: Corners<number>, outJs: ESValue) {
       let propVal: ESValue = ESValue.instantiateEmptyObject();
       propVal.setProperty('topLeft', inVal.topLeft);
       propVal.setProperty('topRight', inVal.topRight);
       propVal.setProperty('bottomLeft', inVal.bottomLeft);
       propVal.setProperty('bottomRight', inVal.bottomRight);
       outJs.setProperty(name, propVal);
    }

    static setPropFrame(name: string, inVal: Frame, outJs: ESValue) {
       let propVal: ESValue = ESValue.instantiateEmptyObject();
       propVal.setProperty('x', inVal.x);
       propVal.setProperty('y', inVal.y);
       propVal.setProperty('width', inVal.width);
       propVal.setProperty('height', inVal.height);
       outJs.setProperty(name, propVal);
    }

    static setPropVector2(name: string, inVal: Vector2, outJs: ESValue) {
       let propVal: ESValue = ESValue.instantiateEmptyObject();
       propVal.setProperty('x', inVal.x);
       propVal.setProperty('y', inVal.y);
       outJs.setProperty(name, propVal);
    }

    static setPropVector3(name: string, inVal: Vector3, outJs: ESValue) {
       let propVal: ESValue = ESValue.instantiateEmptyObject();
       propVal.setProperty('x', inVal.x);
       propVal.setProperty('y', inVal.y);
       propVal.setProperty('z', inVal.z);
       outJs.setProperty(name, propVal);
    }

    static setPropMatrix4(name: string, inVal: Matrix4, outJs: ESValue) {
        let propVal: ESValue = ESValue.instantiateEmptyArray();
        propVal.setProperty(0, inVal[0]);
        propVal.setProperty(1, inVal[1]);
        propVal.setProperty(2, inVal[2]);
        propVal.setProperty(3, inVal[3]);
        propVal.setProperty(4, inVal[4]);
        propVal.setProperty(5, inVal[5]);
        propVal.setProperty(6, inVal[6]);
        propVal.setProperty(7, inVal[7]);
        propVal.setProperty(8, inVal[8]);
        propVal.setProperty(9, inVal[9]);
        propVal.setProperty(10, inVal[10]);
        propVal.setProperty(11, inVal[11]);
        propVal.setProperty(12, inVal[12]);
        propVal.setProperty(13, inVal[13]);
        propVal.setProperty(14, inVal[14]);
        propVal.setProperty(15, inVal[15]);
        outJs.setProperty(name, propVal);
    }

    static setPropShapeMask(name: string, inVal: ShapeMask, outJs: ESValue) {
        let propVal = ShapeMaskTransfer.transferDynamic(inVal);
        if (propVal === null || propVal === undefined) {
            return ;
        }
        outJs.setProperty(name, propVal! as Object);
    }

    static setPropShapeClip(name: string, inVal: ShapeClip, outJs: ESValue) {
        let propVal = ShapeClipTransfer.transferDynamic(inVal);
        if (propVal === null || propVal === undefined) {
            return ;
        }
        outJs.setProperty(name, propVal! as Object);
    }
}
