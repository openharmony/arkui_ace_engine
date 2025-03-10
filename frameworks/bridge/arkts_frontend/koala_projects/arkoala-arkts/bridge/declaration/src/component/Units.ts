import { Resource } from "../Resource";
import { Color } from "./Enums";

export type PX = string;
export type VP = string | number;
export type FP = string;
export type LPX = string;
export type Percentage = string;

export type Dimension = PX | VP | FP | LPX | Percentage | Resource;

export type Length = string | number | Resource;

export type ResourceColor = Color | number | string | Resource;