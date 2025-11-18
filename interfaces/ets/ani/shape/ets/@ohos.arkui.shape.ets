/*
 * Copyright (C) 2024 Huawei Device Co., Ltd.
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

import { Position, SizeOptions, Length, ResourceColor }  from './arkui.component.units';

interface ShapeSize {

    width?: double | string;

    height?: double | string;
}

interface RectShapeOptions extends ShapeSize {

    radius?: double | string | Array<double | string>;
}

interface RoundRectShapeOptions extends ShapeSize {

    radiusWidth?: double | string;

    radiusHeight?: double | string;
}

interface PathShapeOptions {

    commands?: string;
}

class CommonShapeMethod {
    static { loadLibrary("shape_ani") }

    public native offset(offset: Position): this;

    public native fill(color: ResourceColor): this;

    public native position(position: Position): this;
}

class BaseShape extends CommonShapeMethod {

   public native width(width: Length): this;

   public native height(height: Length): this;

   public native size(size: SizeOptions): this;
}

export class RectShape extends BaseShape {
    basicShapeResult:long;

    public native constructor(options?: RectShapeOptions | RoundRectShapeOptions);

    public native radiusWidth(rWidth: double | string): this;

    public native radiusHeight(rHeight: double | string): this;

    public native radius(radius: double | string | Array<double | string>): this;

    public native width(width: Length): this;

    public native height(height: Length): this;

    public native size(size: SizeOptions): this;

    public native offset(offset: Position): this;

    public native fill(color: ResourceColor): this;

    public native position(position: Position): this;
}

export class EllipseShape  extends BaseShape {

    basicShapeResult:long;

    public native constructor(options?: ShapeSize);

    public native width(width: Length): this;

    public native height(height: Length): this;

    public native size(size: SizeOptions): this;

    public native offset(offset: Position): this;

    public native fill(color: ResourceColor): this;

    public native position(position: Position): this;
}

export class CircleShape extends BaseShape {

    basicShapeResult:long;

    public native constructor(options?: ShapeSize);

    public native width(width: Length): this;

    public native height(height: Length): this;

    public native size(size: SizeOptions): this;

    public native offset(offset: Position): this;

    public native fill(color: ResourceColor): this;

    public native position(position: Position): this;
}

export class PathShape extends CommonShapeMethod {

    basicShapeResult:long;

    public native constructor(options?: PathShapeOptions);

    public native commands(commands: string): this;

    public native offset(offset: Position): this;

    public native fill(color: ResourceColor): this;

    public native position(position: Position): this;
}

export class __ShapeInnerMethods__ {
    static { loadLibrary("shape_ani") }
    public static native CircleFromPtr(ptr: long): CircleShape;
    public static native RectFromPtr(ptr: long): RectShape;
    public static native EllipseFromPtr(ptr: long): EllipseShape;
    public static native PathFromPtr(ptr: long): PathShape;
}
