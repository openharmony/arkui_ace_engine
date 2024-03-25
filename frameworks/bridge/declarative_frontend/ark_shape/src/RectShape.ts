/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

interface RectShapeOptions extends ShapeSize {
    radius?: number | string | Array<number | string>;
}

interface RoundRectShapeOptions extends ShapeSize {
    radiusWidth?: number | string;
    radiusHeight?: number | string;
}

declare class __RectShape__<T> {
    constructor(options: RectShapeOptions | RoundRectShapeOptions);
    width(width: string | number): T;
    height(height: string | number): T;
    size(size: SizeOptions): T;
    offset(offset: Position): T;
    fill(color: number | string): T;
    position(position: Position): T;
    radiusWidth(rWidth: number | string): T;
    radiusHeight(rHeight: number | string): T;
    radius(radius: number | string | Array<number | string>): T;
}

class RectShape extends __RectShape__<RectShape> {
    constructor(options: RectShapeOptions | RoundRectShapeOptions) {
        super(options);
    }

    width(width: string | number): RectShape {
        return super.width(width);
    }

    height(height: string | number): RectShape {
        return super.height(height);
    }

    size(size: SizeOptions): RectShape {
        return super.size(size);
    }

    offset(offset: Position): RectShape {
        return super.offset(offset);
    }

    fill(width: string | number): RectShape {
        return super.fill(width);
    }

    position(position: Position): RectShape {
        return super.position(position);
    }

    radiusWidth(rWidth: number | string): RectShape {
        return super.radiusWidth(rWidth);
    }

    radiusHeight(rHeight: number | string): RectShape {
        return super.radiusHeight(rHeight);
    }

    radius(radius: number | string | Array<number | string>): RectShape {
        return super.radius(radius);
    }
}


