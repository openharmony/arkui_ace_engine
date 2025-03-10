import { CommonMethod, PointLightStyle } from "./Common";
import { FlexAlign, HorizontalAlign } from "./Enums";
import { Resource } from "../Resource";

import { ArkColumn, ArkColumnComponent } from "@koalaui/arkts-arkui"

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

/** @memo */
// @BuildLambda("ColumnImpl")
export function Column (
    options?: ColumnOptions,
    /** @memo */
    content?: () => void
): ColumnAttribute {
    throw new Error("MUST NOT RUN HERE !!!");
}

/** @memo */
export function ColumnImpl (
    /** @memo */
    style?: (instance: ColumnAttribute) => void,
    options?: ColumnOptions,
    /** @memo */
    content?: () => void
): void {
    ArkColumn((instance: ArkColumnComponent): void => {
        style?.(instance);
    }, content, options);
}
