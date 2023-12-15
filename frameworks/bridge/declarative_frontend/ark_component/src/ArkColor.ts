/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/// <reference path='./import.ts' />
const COLOR_WITH_MAGIC = /#[0-9A-Fa-f]{6,8}/;
const COLOR_WITH_MAGIC_MINI = /#[0-9A-Fa-f]{3,4}/;
const COLOR_WITH_RGB = /rgb\(([0-9]{1,3})\,([0-9]{1,3})\,([0-9]{1,3})\)/i;
const COLOR_WITH_RGBA = /rgba\(([0-9]{1,3})\,([0-9]{1,3})\,([0-9]{1,3})\,(\d+\.?\d*)\)/i;

const COLOR_ALPHA_MASK = 0xff000000;
const MIN_RGB_VALUE = 0;
const MAX_RGB_VALUE = 255;
const COLOR_ALPHA_OFFSET = 24;
const MIN_RGBA_OPACITY = 0.0;
const MAX_RGBA_OPACITY = 1.0;
const MIN_COLOR_STR_LEN = 8;
const HEX_DECIMAL = 16;

class ArkColor implements Equable {
  color: number | undefined;

  constructor() {
    this.color = undefined;
  }

  isEqual(another: ArkColor) {
    return (this.color === another.color);
  }

  parseColorValue(value: number | string | undefined | Resource) {
    if (isResource(value)) {
      return false;
    }
    if (typeof value === 'number') {
      return this.parseColorUint(value);
    } else if (typeof value === 'string') {
      return this.parseColorString(value);
    } else if (value === undefined) {
      this.color = value;
      return true;
    }
    return false;
  }

  parseColorString(colorStr: string) {
    if (colorStr.length === 0) {
      return false;
    }
    colorStr = colorStr.replace(/\s/g, '');
    return (
      this.matchColorWithMagic(colorStr) ||
      this.matchColorWithMagicMini(colorStr) ||
      this.matchColorWithRGB(colorStr) ||
      this.matchColorWithRGBA(colorStr) ||
      this.matchColorSpecialString(colorStr) ||
      this.parseUintColorString(colorStr)
    );
  }

  matchColorWithMagic(colorStr: string) {
    const matches = colorStr.match(COLOR_WITH_MAGIC);
    if (matches) {
      colorStr = colorStr.substr(1);
      let value = parseInt(colorStr, HEX_DECIMAL);
      if (colorStr.length < MIN_COLOR_STR_LEN) {
        value |= COLOR_ALPHA_MASK;
      }
      this.color = value;
      return true;
    }
    return false;
  }

  matchColorWithMagicMini(colorStr: string) {
    const matches = colorStr.match(COLOR_WITH_MAGIC_MINI);
    if (matches) {
      colorStr = colorStr.substr(1);
      let newColorStr = colorStr.replace(/./g, (match) => match + match);
      let value = parseInt(newColorStr, HEX_DECIMAL);
      if (newColorStr.length < MIN_COLOR_STR_LEN) {
        value |= COLOR_ALPHA_MASK;
      }
      this.color = value;
      return true;
    }
    return false;
  }

  matchColorWithRGB(colorStr: string) {
    const matches = colorStr.match(COLOR_WITH_RGB);
    if (matches && matches.length === 4) {
      const [_, redInt, greenInt, blueInt] = matches;
      if (this.isRGBValid(parseInt(redInt)) && this.isRGBValid(parseInt(greenInt)) && this.isRGBValid(parseInt(blueInt))) {
        this.color = this.fromRGB(parseInt(redInt), parseInt(greenInt), parseInt(blueInt));
        return true;
      }
    }
    return false;
  }

  matchColorWithRGBA(colorStr: string) {
    const matches = colorStr.match(COLOR_WITH_RGBA);
    if (matches && matches.length === 5) {
      const [_, redInt, greenInt, blueInt, opacityDouble] = matches;
      if (
        this.isRGBValid(parseInt(redInt)) &&
        this.isRGBValid(parseInt(greenInt)) &&
        this.isRGBValid(parseInt(blueInt)) &&
        this.isOpacityValid(parseFloat(opacityDouble))
      ) {
        this.color = this.fromRGBO(
          parseInt(redInt),
          parseInt(greenInt),
          parseInt(blueInt),
          parseFloat(opacityDouble)
        );
        return true;
      }
    }
    return false;
  }

  matchColorSpecialString(colorStr: string) {
    const colorTable: { [key: string]: number } = {
      black: 0xff000000,
      blue: 0xff0000ff,
      gray: 0xffc0c0c0,
      green: 0xff00ff00,
      red: 0xffff0000,
      white: 0xffffffff,
    };

    if (colorStr in colorTable) {
      this.color = colorTable[colorStr];
      return true;
    }
    return false;
  }

  parseUintColorString(colorStr: string) {
    const colorInt = Number(colorStr);
    return this.parseColorUint(colorInt);
  }

  parseColorUint(colorInt: number) {
    if (colorInt > 0) {
      this.color = colorInt;
      if ((colorInt & COLOR_ALPHA_MASK) === 0) {
        this.color |= COLOR_ALPHA_MASK;
      }
      return true;
    }
    return false;
  }

  isRGBValid(value: number) {
    return value >= MIN_RGB_VALUE && value <= MAX_RGB_VALUE;
  }

  isOpacityValid(value: number) {
    return value >= MIN_RGBA_OPACITY && value <= MAX_RGBA_OPACITY;
  }

  fromARGB(alpha: number, red: number, green: number, blue: number) {
    const argb = (alpha << 24) | (red << 16) | (green << 8) | blue;
    return argb >>> 0;
  }

  fromRGBO(red: number, green: number, blue: number, opacity: number) {
    const alpha = Math.round(opacity * 0xff) & 0xff;
    return this.fromARGB(alpha, red, green, blue);
  }

  fromRGB(red: number, green: number, blue: number) {
    return this.fromARGB(0xff, red, green, blue);
  }

  getColor(): number | undefined {
    return this.color;
  }
}