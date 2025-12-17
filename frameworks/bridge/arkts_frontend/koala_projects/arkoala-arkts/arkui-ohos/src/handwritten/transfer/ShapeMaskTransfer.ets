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


import { ArkUIAniModule } from 'arkui.ani'
import { ShapeMask, Rect, RoundRect, CornerRadius, Vector2, Circle, CommandPath } from '../../Graphics'
import { ShapeBaseTransfer } from './ShapeBaseTransfer';
import { TransferUtil } from './TransferUtil';
import { int32 } from '@koalaui/common';

export class ShapeMaskTransfer {
    static transferStatic(input: Any): Object {
        if (typeof (input) !== 'object') {
            throw Error('The ShapeMask is not object convert fail.');
        }
        let shapeMask = new ShapeMask();
        if (!(ESValue.wrap(input).getProperty('rect').isNull() || 
            ESValue.wrap(input).getProperty('rect').isUndefined())) {
            const rectValue = ESValue.wrap(input).getProperty('rect');
            shapeMask.rect = ShapeBaseTransfer.transferRectStatic(rectValue);
        }
        if (!(ESValue.wrap(input).getProperty('roundRect').isNull() || 
            ESValue.wrap(input).getProperty('roundRect').isUndefined())) {
            const roundRectValue = ESValue.wrap(input).getProperty('roundRect');
            shapeMask.roundRect = ShapeBaseTransfer.transferRoundRectStatic(roundRectValue);
        }
        if (!(ESValue.wrap(input).getProperty('circle').isNull() || 
            ESValue.wrap(input).getProperty('circle').isUndefined())) {
            const circleValue = ESValue.wrap(input).getProperty('circle');
            shapeMask.circle = ShapeBaseTransfer.transferCircleStatic(circleValue);
        }
        if (!(ESValue.wrap(input).getProperty('oval').isNull() || 
            ESValue.wrap(input).getProperty('oval').isUndefined())) {
            const ovalValue = ESValue.wrap(input).getProperty('oval');
            shapeMask.oval = ShapeBaseTransfer.transferRectStatic(ovalValue);
        }
        if (!(ESValue.wrap(input).getProperty('path').isNull() || 
            ESValue.wrap(input).getProperty('path').isUndefined())) {
            const pathValue = ESValue.wrap(input).getProperty('path');
            shapeMask.path = ShapeBaseTransfer.transferPathStatic(pathValue);
        }

        let maskVal = ESValue.wrap(input);
        let fiColor = TransferUtil.getPropColorInt(maskVal, 'fillColor');
        if (fiColor !== undefined) {
            shapeMask.fillColor = fiColor as int32;
        }
        let stroColor = TransferUtil.getPropColorInt(maskVal, 'strokeColor');
        if (stroColor !== undefined) {
            shapeMask.strokeColor = stroColor as int32;
        }
        if (ESValue.wrap(input).getProperty('strokeWidth').isNumber()) {
            const strokeWidth = ESValue.wrap(input).getProperty('strokeWidth').toNumber();
            shapeMask.strokeWidth = strokeWidth;
        }

        return shapeMask;
    }
    static transferDynamic(input: Object): Any {
        if (input === null) {
            throw Error('The ShapeMask is null, convert fail.');
        }
        if (input === undefined) {
            throw Error('The ShapeMask is undefined, convert fail.');
        }
        let staticValue = input as ShapeMask;
        if (staticValue === null) {
            throw Error('Not a ShapeMask object, convert fail.');
        }
        if (staticValue === undefined) {
            throw Error('Not a ShapeMask object, convert fail.');
        }

        let nodeModule = ESValue.load('@ohos.arkui.node');
        let shapeMaskModule = nodeModule.getProperty('ShapeMask');
        let ret = shapeMaskModule.instantiate();
        if (staticValue.rect !== null) {
            let staticRectValue = staticValue.rect as Rect;
            ret.setProperty('rect', ShapeBaseTransfer.transferRectDynamic(staticRectValue));
        } else {
            ret.setProperty('rect', null);
        }
        if (staticValue.roundRect !== null) {
            let staticRoundRectValue = staticValue.roundRect as RoundRect;
            ret.setProperty('roundRect', ShapeBaseTransfer.transferRoundRectDynamic(staticRoundRectValue));
        } else {
            ret.setProperty('roundRect', null);
        }
        if (staticValue.circle !== null) {
            let staticCircleValue = staticValue.circle as Circle;
            ret.setProperty('circle', ShapeBaseTransfer.transferCircleDynamic(staticCircleValue));
        } else {
            ret.setProperty('circle', null);
        }
        if (staticValue.oval !== null) {
            let staticRectValue = staticValue.oval as Rect;
            ret.setProperty('oval', ShapeBaseTransfer.transferRectDynamic(staticRectValue));
        } else {
            ret.setProperty('oval', null);
        }
        if (staticValue.path !== null) {
            let staticPathValue = staticValue.path as CommandPath;
            ret.setProperty('path', ShapeBaseTransfer.transferPathDynamic(staticPathValue));
        } else {
            ret.setProperty('path', null);
        }
        let fiColor = Double.toInt(staticValue.fillColor);
        let fillColor = ArkUIAniModule._ToColorLong(fiColor);
        ret.setProperty('fillColor', fillColor);
        let stroColor = Double.toInt(staticValue.strokeColor);
        let strokeColor = ArkUIAniModule._ToColorLong(stroColor);
        ret.setProperty('strokeColor', strokeColor);
        ret.setProperty('strokeWidth', staticValue.strokeWidth);
        return ret.unwrap();
    }
}
