import { Dimension, Length, ResourceColor } from "./Units";
import { IlluminatedType } from "./Enums";

export interface LightSource {
    positionX: Dimension;
    positionY: Dimension;
    positionZ: Dimension;
    intensity: number;
    color?: ResourceColor;
}

export interface PointLightStyle {
    lightSource?: LightSource;
    illuminated?: IlluminatedType;
    bloom?: number;
}

export interface CommonMethod {
    /** @memo */
    width(w: Length): this;
    /** @memo */
    height(h: Length): this;
    /** @memo */
    backgroundColor(color: ResourceColor): this;
}
