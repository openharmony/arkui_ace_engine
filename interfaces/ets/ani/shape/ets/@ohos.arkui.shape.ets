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

    width?: number | string;

    height?: number | string;
}

interface RectShapeOptions extends ShapeSize {

    radius?: number | string | Array<number | string>;
}

interface RoundRectShapeOptions extends ShapeSize {

    radiusWidth?: number | string;

    radiusHeight?: number | string;
}

interface PathShapeOptions {

    commands?: string;
}

class CommonShapeMethod<T> {
    static { loadLibrary("shape_ani") }

    public native offset(offset: Position): T;

    public native fill(color: ResourceColor): T;

    public native position(position: Position): T;
}

class BaseShape<T> extends CommonShapeMethod<T> {

   public native width(width: Length): T;

   public native height(height: Length): T;

   public native size(size: SizeOptions): T;
}

export class RectShape extends BaseShape<RectShape> {
    rectShapeResult:long;

    public native constructor(options?: RectShapeOptions | RoundRectShapeOptions);

    public native radiusWidth(rWidth: number | string): RectShape;

    public native radiusHeight(rHeight: number | string): RectShape;

    public native radius(radius: number | string | Array<number | string>): RectShape;

    public native width(width: Length): RectShape;

    public native height(height: Length): RectShape;

    public native size(size: SizeOptions): RectShape;

    public native offset(offset: Position): RectShape;

    public native fill(color: ResourceColor): RectShape;

    public native position(position: Position): RectShape;
}

export class EllipseShape  extends BaseShape<EllipseShape > {

    ellipseShapeResult:long;

    public native constructor(options?: ShapeSize);

    public native width(width: Length): EllipseShape;

    public native height(height: Length): EllipseShape;

    public native size(size: SizeOptions): EllipseShape;

    public native offset(offset: Position): EllipseShape;

    public native fill(color: ResourceColor): EllipseShape;

    public native position(position: Position): EllipseShape;
}

export class CircleShape extends BaseShape<CircleShape > {

    circleShapeResult:long;

    public native constructor(options?: ShapeSize);

    public native width(width: Length): CircleShape;

    public native height(height: Length): CircleShape;

    public native size(size: SizeOptions): CircleShape;

    public native offset(offset: Position): CircleShape;

    public native fill(color: ResourceColor): CircleShape;

    public native position(position: Position): CircleShape;
}

export class PathShape extends CommonShapeMethod<PathShape> {

    pathShapeResult:long;

    public native constructor(options?: PathShapeOptions);

    public native commands(commands: string): PathShape;

    public native offset(offset: Position): PathShape;

    public native fill(color: ResourceColor): PathShape;

    public native position(position: Position): PathShape;
}