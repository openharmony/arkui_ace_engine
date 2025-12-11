import { Position, SizeOptions, Length, ResourceColor } from 'arkui/framework'
export interface ShapeSize {

    width?: double | string;

    height?: double | string;
}

export interface RectShapeOptions extends ShapeSize {

    radius?: double | string | Array<double | string>;
}

export interface RoundRectShapeOptions extends ShapeSize {

    radiusWidth?: double | string;

    radiusHeight?: double | string;
}

export interface PathShapeOptions {

    commands?: string;
}

export declare class CommonShapeMethod {
    public offset(offset: Position): this;
    public fill(color: ResourceColor): this;
    public position(position: Position): this;
}

export declare class BaseShape extends CommonShapeMethod {
    public width(width: Length): this;
    public height(height: Length): this;
    public size(size: SizeOptions): this;
}

export declare class RectShape extends BaseShape {
    public constructor(options?: RectShapeOptions | RoundRectShapeOptions);
    public radiusWidth(rWidth: number | string): this;
    public radiusHeight(rHeight: number | string): this;
    public radius(radius: double | string | Array<double | string>): this;
    public width(width: Length): this;
    public height(width: Length): this;
    public size(width: Length): this;
    public offset(offset: Position): this;
    public fill(color: ResourceColor): this;
    public position(position: Position): this;
}

export declare class EllipseShape extends BaseShape {

    public constructor(options?: ShapeSize);
    public width(width: Length): this;
    public height(width: Length): this;
    public size(width: Length): this;
    public offset(offset: Position): this;
    public fill(color: ResourceColor): this;
    public position(position: Position): this;
}

export declare class CircleShape extends BaseShape {

    public constructor(options?: ShapeSize);
    public width(width: Length): this;
    public height(width: Length): this;
    public size(width: Length): this;
    public offset(offset: Position): this;
    public fill(color: ResourceColor): this;
    public position(position: Position): this;
}

export declare class PathShape extends CommonShapeMethod {
    public constructor(options?: PathShapeOptions);
    public commands(commands: string): this;
    public offset(offset: Position): this;
    public fill(color: ResourceColor): this;
    public position(position: Position): this;
}