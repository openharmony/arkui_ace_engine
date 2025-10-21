
import { Color}  from './arkui.component.enums';

import { Resource } from 'global.resource'
export type Length = number | string | Resource;

export type ResourceColor = Color | number | string | Resource;

export interface SizeOptions {

  width?: Length;

  height?: Length;
}

export interface Position {

  x?: Length;

  y?: Length;
}
