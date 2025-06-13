export interface NodeController {
}
export interface TextModifier {
}
export enum RectWidthStyle {
    TIGHT,
    MAX = 1,
}
export enum Affinity {
    UPSTREAM = 0,
    DOWNSTREAM = 1
}
export enum RectHeightStyle {
    TIGHT,
    MAX = 1,
    INCLUDE_LINE_SPACE_MIDDLE = 2,
    INCLUDE_LINE_SPACE_TOP = 3,
    INCLUDE_LINE_SPACE_BOTTOM = 4,
    STRUT = 5,
}
export interface Want {
    bundleName?: string;
    abilityName?: string;
    deviceId?: string;
    uri?: string;
    type?: string;
    flags?: number;
    action?: string;
    parameters?: Map<string, Object>;
    entities?: Array<string>;
    moduleName?: string;
}
export enum LengthUnit {
    PX,
    VP = 1,
    FP = 2,
    PERCENT = 3,
    LPX = 4,
}
export interface LengthMetrics {
    unit: LengthUnit;
    value: number;
}
export interface WebHeader {
    headerKey: string;
    headerValue: string;
}