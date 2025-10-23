
import { Color}  from './arkui.component.enums';

import { Resource } from 'global.resource'
export type Length = double | string | Resource;

export type ResourceColor = Color | int | string | Resource;

export interface SizeOptions {

  width?: Length;

  height?: Length;
}

export interface Position {

  x?: Length;

  y?: Length;
}
