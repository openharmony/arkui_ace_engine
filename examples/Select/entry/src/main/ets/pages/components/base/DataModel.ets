/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

export class Model1 {
  public rating?: number = undefined
  public indicator?: boolean = undefined
  public stars?: number = undefined
  public stepSize?: number = undefined
  public backgroundUri?: string = undefined
  public foregroundUri?: string = undefined
  public secondaryUri?: string = undefined

  constructor(rating?: number, indicator?: boolean, stars?: number, stepSize?: number,
    backgroundUri?: string, foregroundUri?: string, secondaryUri?: string) {
    this.rating = rating
    this.indicator = indicator
    this.stars = stars
    this.stepSize = stepSize
    this.backgroundUri = backgroundUri
    this.foregroundUri = foregroundUri
    this.secondaryUri = secondaryUri
  }
}

export class TestListOption {
  public title?: string = undefined
  public url?: string = undefined
  public key?: string = undefined
}

export class Model2 {
  public start?: Date = undefined
  public end?: Date = undefined
  public selected?: Date = undefined
  public lunar?: boolean = undefined

  constructor(start?: Date, end?: Date, selected?: Date, lunar?: boolean) {
    this.start = start
    this.end = end
    this.selected = selected
    this.lunar = lunar
  }
}

export class Model3 {
  public selected?: Date = undefined
  public format?: TimePickerFormat = undefined

  constructor(selected?: Date, format?: TimePickerFormat) {
    this.selected = selected
    this.format = format
  }
}

export class Model4 {
  public selected1?: number | number[] = undefined
  public selected2?: number | number[] = undefined
  public value1?: string = undefined
  public value2?: string[] = undefined
  public defaultPickerItemHeight?: number | string = undefined
  public selectedIndex1?: number | number[] = undefined
  public selectedIndex2?: number | number[] = undefined
  public rangeStringSingle?: string[] | Resource | TextCascadePickerRangeContent[] | string[][] |
  TextPickerRangeContent[] = undefined
  public rangeStringMulti?: string[] | Resource | TextCascadePickerRangeContent[] | string[][] |
  TextPickerRangeContent[] = undefined

  constructor(selected1?: number | number[], selected2?: number | number[], value1?: string, value2?: string[],
    defaultPickerItemHeight?: number | string, selectedIndex1?: number | number[], selectedIndex2?: number | number[],
    rangeStringSingle?: string[] | Resource | TextCascadePickerRangeContent[] | string[][] | TextPickerRangeContent[],
    rangeStringMulti?: string[] | Resource | TextCascadePickerRangeContent[] | string[][] | TextPickerRangeContent[]) {
    this.selected1 = selected1
    this.selected2 = selected2
    this.value1 = value1
    this.value2 = value2
    this.defaultPickerItemHeight = defaultPickerItemHeight
    this.selectedIndex1 = selectedIndex1
    this.selectedIndex2 = selectedIndex2
    this.rangeStringSingle = rangeStringSingle
    this.rangeStringMulti = rangeStringMulti
  }
}

export class Model6 {
  public selected?: Date = undefined
  public hintRadius?: number | Resource = undefined
  public alignType?: CalendarAlign = undefined
  public offset?: Offset = undefined
  public color?: ResourceColor = undefined
  public font?: Font = undefined
  public direction?: Direction | undefined = undefined
  public enabled?: boolean | undefined = undefined

  constructor(selected?: Date, hintRadius?: number | Resource, alignType?: CalendarAlign, offset?: Offset,
    color?: ResourceColor, font?: Font, direction?: Direction | undefined, enabled?: boolean | undefined) {
    this.selected = selected
    this.hintRadius = hintRadius
    this.alignType = alignType
    this.offset = offset
    this.color = color
    this.font = font
    this.direction = direction
    this.enabled = enabled
  }
}

export class Model5 {
  public dateTimeOptions?: DateTimeOptions = undefined
  public disappearTextColor?: ResourceColor = undefined
  public textColor?: ResourceColor = undefined
  public selectedTextColor?: ResourceColor = undefined
  public disappearFontSize?: Length = undefined
  public textFontSize?: Length = undefined
  public selectedTextFontSize?: Length = undefined
  public disappearFontWeight?: FontWeight | number | string = undefined
  public textFontWeight?: FontWeight | number | string = undefined
  public selectedTextFontWeight?: FontWeight | number | string = undefined
  public canLoops?: boolean = undefined
  public loop?: boolean = undefined
  public divider?: DividerOptions | null = undefined
  public direction?: Direction = undefined
  public gradientHeight?: Dimension = undefined
  public enableHapticFeedback?: boolean | undefined = undefined

  constructor(dateTimeOptions?: DateTimeOptions, disappearTextColor?: ResourceColor, textColor?: ResourceColor,
    selectedTextColor?: ResourceColor,
    disappearFontSize?: Length, textFontSize?: Length, selectedTextFontSize?: Length,
    disappearFontWeight?: FontWeight | number | string,
    textFontWeight?: FontWeight | number | string, selectedTextFontWeight?: FontWeight | number | string,
    canLoops?: boolean, loop?: boolean,
    divider?: DividerOptions | null, direction?: Direction, gradientHeight?: Dimension
    , enableHapticFeedback?: boolean | undefined) {
    this.disappearTextColor = disappearTextColor
    this.textColor = textColor
    this.selectedTextColor = selectedTextColor
    this.disappearFontSize = disappearFontSize
    this.textFontSize = textFontSize
    this.selectedTextFontSize = selectedTextFontSize
    this.disappearFontWeight = disappearFontWeight
    this.textFontWeight = textFontWeight
    this.selectedTextFontWeight = selectedTextFontWeight
    this.canLoops = canLoops
    this.loop = loop
    this.divider = divider
    this.direction = direction
    this.gradientHeight = gradientHeight
    this.dateTimeOptions = dateTimeOptions
    this.enableHapticFeedback = enableHapticFeedback
  }
}