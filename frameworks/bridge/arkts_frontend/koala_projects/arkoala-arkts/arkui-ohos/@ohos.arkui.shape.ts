import { Position, SizeOptions, Length, ResourceColor } from "arkui/component/units";
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

declare class CommonShapeMethod<T> {
    public offset(offset: Position): T;
    public fill(color: ResourceColor): T;
    public position(position: Position): T;
}

declare class BaseShape<T> extends CommonShapeMethod<T> {
    public width(width: Length): T;
    public height(height: Length): T;
    public size(size: SizeOptions): T;
}

export declare class RectShape extends BaseShape<RectShape> {
    public constructor(options?: RectShapeOptions | RoundRectShapeOptions);
    public radiusWidth(rWidth: number | string): RectShape;
    public radiusHeight(rHeight: number | string): RectShape;
    public radius(radius: number | string | Array<number | string>): RectShape;
    public width(width: Length): RectShape;
    public height(width: Length): RectShape;
    public size(width: Length): RectShape;
    public offset(offset: Position): RectShape;
    public fill(color: ResourceColor): RectShape;
    public position(position: Position): RectShape;
}

export declare class EllipseShape extends BaseShape<EllipseShape > {

    public constructor(options?: ShapeSize);
    public width(width: Length): EllipseShape;
    public height(width: Length): EllipseShape;
    public size(width: Length): EllipseShape;
    public offset(offset: Position): EllipseShape;
    public fill(color: ResourceColor): EllipseShape;
    public position(position: Position): EllipseShape;
}

export declare class CircleShape extends BaseShape<CircleShape > {

    public constructor(options?: ShapeSize);
    public width(width: Length): CircleShape;
    public height(width: Length): CircleShape;
    public size(width: Length): CircleShape;
    public offset(offset: Position): CircleShape;
    public fill(color: ResourceColor): CircleShape;
    public position(position: Position): CircleShape;
}

export declare class PathShape extends CommonShapeMethod<PathShape> {
    public constructor(options?: PathShapeOptions);
    public commands(commands: string): PathShape;
    public offset(offset: Position): PathShape;
    public fill(color: ResourceColor): PathShape;
    public position(position: Position): PathShape;
}