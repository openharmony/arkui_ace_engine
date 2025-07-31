
import { Color}  from './arkui.component.enums';

export type Length = number | string | Resource;

export interface Resource {
    id: number;

    bundleName: string;

    moduleName: string;

    params?: Array<String>;

    type?: number;
};

export type ResourceColor = Color | number | string | Resource;

export interface SizeOptions {

  width?: Length;

  height?: Length;
}

export interface Position {

  x?: Length;

  y?: Length;
}
