import { CommonMethod, PointLightStyle } from "./Common";
import { FlexAlign, HorizontalAlign } from "./Enums";
import { Resource } from "../Resource";

export type SpaceType = string | number | Resource;

export interface ColumnOptions {
    space?: string | number;
}

export interface ColumnOptionsV2 {
    space?: SpaceType;
}

export interface ColumnAttribute extends CommonMethod {
    /** @memo */
    alignItems(value: HorizontalAlign): this;
    /** @memo */
    justifyContent(value: FlexAlign): this;
    /** @memo */
    pointLight(value: PointLightStyle): this;
    /** @memo */
    reverse(isReversed?: boolean): this;
}