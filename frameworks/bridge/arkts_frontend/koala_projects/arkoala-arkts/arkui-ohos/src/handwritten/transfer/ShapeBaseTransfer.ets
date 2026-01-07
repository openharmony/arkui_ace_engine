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

import { Rect, RoundRect, CornerRadius, Vector2, Circle, CommandPath } from '../../Graphics'

export class ShapeBaseTransfer {
    static transferRectStatic(rectValue: ESValue): Rect {
        const left = rectValue.getProperty('left').toNumber();
        const top = rectValue.getProperty('top').toNumber();
        const right = rectValue.getProperty('right').toNumber();
        const bottom = rectValue.getProperty('bottom').toNumber();
        let rect: Rect = { left: left, top: top, right: right, bottom: bottom };
        return rect
    }

    static transferRoundRectStatic(roundRectValue: ESValue): RoundRect {
        const innerRectValue = roundRectValue.getProperty('rect');
        let rect: Rect = ShapeBaseTransfer.transferRectStatic(innerRectValue);
        let topLeftVector: Vector2 = { x: 0, y: 0 };
        let topRightVector: Vector2 = { x: 0, y: 0 };
        let bottomLeftVector: Vector2 = { x: 0, y: 0 };
        let bottomRightVector: Vector2 = { x: 0, y: 0 };
        const innerCorners = roundRectValue.getProperty('corners');
        const topLeft = innerCorners.getProperty('topLeft');
        const topLeftXValue = topLeft.getProperty('x').toNumber();
        const topLeftYValue = topLeft.getProperty('y').toNumber();
        topLeftVector.x = topLeftXValue;
        topLeftVector.y = topLeftYValue;
        const topRight = innerCorners.getProperty('topRight');
        const topRightXValue = topRight.getProperty('x').toNumber();
        const topRightYValue = topRight.getProperty('y').toNumber();
        topRightVector.x = topRightXValue;
        topRightVector.y = topRightYValue;
        const bottomLeft = innerCorners.getProperty('bottomLeft');
        const bottomLeftXValue = bottomLeft.getProperty('x').toNumber();
        const bottomLeftYValue = bottomLeft.getProperty('y').toNumber();
        bottomLeftVector.x = bottomLeftXValue;
        bottomLeftVector.y = bottomLeftYValue;
        const bottomRight = innerCorners.getProperty('bottomRight');
        const bottomRightXValue = bottomRight.getProperty('x').toNumber();
        const bottomRightYValue = bottomRight.getProperty('y').toNumber();
        bottomRightVector.x = bottomRightXValue;
        bottomRightVector.y = bottomRightYValue;

        let corner: CornerRadius = { topLeft: topLeftVector, topRight: topRightVector, bottomLeft:bottomLeftVector, bottomRight: bottomRightVector };
        let roundRect: RoundRect = { rect: rect, corners: corner };
        return roundRect;
    }

    static transferPathStatic(pathValue: ESValue): CommandPath {
        const commandString = pathValue.getProperty('commands').toString();
        let path: CommandPath = { commands: commandString };
        return path;
    }

    static transferCircleStatic(circleValue: ESValue): Circle {
        const centerX = circleValue.getProperty('centerX').toNumber();
        const centerY = circleValue.getProperty('centerY').toNumber();
        const radius = circleValue.getProperty('radius').toNumber();
        let circle: Circle = { centerX: centerX, centerY: centerY, radius: radius };
        return circle
    }

    static transferRectDynamic(staticRectValue: Rect): ESValue {
        let rectValue = ESValue.instantiateEmptyObject();
        rectValue.setProperty('left', ESValue.wrap(staticRectValue.left));
        rectValue.setProperty('right', ESValue.wrap(staticRectValue.right));
        rectValue.setProperty('top', ESValue.wrap(staticRectValue.top));
        rectValue.setProperty('bottom', ESValue.wrap(staticRectValue.bottom));
        return rectValue;
    }

    static transferRoundRectDynamic(staticRoundRectValue: RoundRect): ESValue {
        let staticRectValue = staticRoundRectValue.rect as Rect;
        let staticCornersValue = staticRoundRectValue.corners as CornerRadius;

        let dynamicRectValue = ESValue.instantiateEmptyObject();
        dynamicRectValue.setProperty('left', ESValue.wrap(staticRectValue.left));
        dynamicRectValue.setProperty('right', ESValue.wrap(staticRectValue.right));
        dynamicRectValue.setProperty('top', ESValue.wrap(staticRectValue.top));
        dynamicRectValue.setProperty('bottom', ESValue.wrap(staticRectValue.bottom));

        let dynamicCornerRadius = ESValue.instantiateEmptyObject()
        let cornerTopLeft = ESValue.instantiateEmptyObject();
        let dynamicCornerTopLeft = staticCornersValue.topLeft as Vector2;
        cornerTopLeft.setProperty('x', ESValue.wrap(dynamicCornerTopLeft.x));
        cornerTopLeft.setProperty('y', ESValue.wrap(dynamicCornerTopLeft.y));
        dynamicCornerRadius.setProperty('topLeft', cornerTopLeft);

        let cornerTopRight = ESValue.instantiateEmptyObject();
        let dynamicCornerTopRight = staticCornersValue.topRight as Vector2;
        cornerTopRight.setProperty('x', ESValue.wrap(dynamicCornerTopRight.x));
        cornerTopRight.setProperty('y', ESValue.wrap(dynamicCornerTopRight.y));
        dynamicCornerRadius.setProperty('topRight', cornerTopRight);

        let cornerBottomLeft = ESValue.instantiateEmptyObject();
        let dynamicCornerBottomLeft = staticCornersValue.bottomLeft as Vector2;
        cornerBottomLeft.setProperty('x', ESValue.wrap(dynamicCornerBottomLeft.x));
        cornerBottomLeft.setProperty('y', ESValue.wrap(dynamicCornerBottomLeft.y));
        dynamicCornerRadius.setProperty('bottomLeft', cornerBottomLeft);

        let cornerBottomRight = ESValue.instantiateEmptyObject();
        let dynamicCornerBottomRight = staticCornersValue.bottomRight as Vector2;
        cornerBottomRight.setProperty('x', ESValue.wrap(dynamicCornerBottomRight.x));
        cornerBottomRight.setProperty('y', ESValue.wrap(dynamicCornerBottomRight.y));
        dynamicCornerRadius.setProperty('bottomRight', cornerBottomRight); 

        let dynamicRoundRectValue = ESValue.instantiateEmptyObject()
        dynamicRoundRectValue.setProperty('rect', dynamicRectValue);
        dynamicRoundRectValue.setProperty('corners', dynamicCornerRadius);            
        return dynamicRoundRectValue;
    }

    static transferCircleDynamic(staticCircleValue: Circle): ESValue {
        let circleValue = ESValue.instantiateEmptyObject()
        circleValue.setProperty('centerX', ESValue.wrap(staticCircleValue.centerX))
        circleValue.setProperty('centerY', ESValue.wrap(staticCircleValue.centerY))
        circleValue.setProperty('radius', ESValue.wrap(staticCircleValue.radius))
        return circleValue;
    }

    static transferPathDynamic(staticPathValue: CommandPath): ESValue {
        let pathValue = ESValue.instantiateEmptyObject()
        pathValue.setProperty('commands', ESValue.wrap(staticPathValue.commands))
        return pathValue;
    }
}
