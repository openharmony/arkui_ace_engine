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

import {
  Entry,
  Text,
  Column,
  Component,
  Button,
  ClickEvent,
  FontWeight,
  ButtonOptions,
  Padding,
  LocalizedPadding,
  BlurStyle,
  Row,
  Stack,
  LocalizedEdges,
  Color,
  Image,
  TextAlign,
  Callback,
  Builder,
  Alignment,
  ButtonType,
  HoverEffect,
  SourceType,
  Curve,
  GestureEvent,
  KeyEvent,
  KeyType,
  SourceTool,
  Context,
  $r,
  ColumnOptions,
  RowOptions,
  Position,
  Resource,
  ResourceStr,
  Direction,
  TextInputController,
  RelativeContainer,
  LocalizedMargin,
  LocalizedAlignRuleOptions,
  LocalizedHorizontalAlignParam,
  LocalizedVerticalAlignParam,
  VerticalAlign,
  Rectangle,
  HoverEvent,
  LongPressGesture,
  EnterKeyType,
  EditableTextOnChangeCallback,
  InputType,
  HorizontalAlign,
  OnSubmitCallback,
  EdgeWidths,
  FocusDrawLevel,
  LocalizedEdgeWidths,
  TextInput,
  Rect,
  CopyOptions,
  focusControl,
  BusinessError
} from '@ohos.arkui.component';
import { Watch, State, PropRef } from '@ohos.arkui.stateManagement';
import { LengthMetrics } from '@ohos.arkui.node';
import resourceManager from '@ohos.resourceManager';
import accessibility from '@ohos.accessibility';
import common from '@ohos.app.ability.common';
import intl from '@ohos.intl';
import i18n from '@ohos.i18n';

export enum CounterType {
  LIST = 0,
  COMPACT = 1,
  INLINE = 2,
  INLINE_DATE = 3
}

enum FocusText {
  NONE,
  TEXT1,
  TEXT2,
  TEXT3,
}

export class CommonOptions {
  public focusable?: boolean;
  public step?: int;
  public onHoverIncrease?: (isHover: boolean) => void;
  public onHoverDecrease?: (isHover: boolean) => void;
}

export class InlineStyleOptions extends CommonOptions {
  public value?: int;
  public min?: int;
  public max?: int;
  public textWidth?: double;
  public onChange?: (value: int) => void;
}

export class NumberStyleOptions extends InlineStyleOptions {
  public label?: ResourceStr;
  public onFocusIncrease?: () => void;
  public onFocusDecrease?: () => void;
  public onBlurIncrease?: () => void;
  public onBlurDecrease?: () => void;
}

export class DateData {
  public year: int;
  public month: int;
  public day: int;

  constructor(year: int, month: int, day: int) {
    this.year = year;
    this.month = month;
    this.day = day;
  }

  toString(): string {
    let date = String(this.year) + '-';
    let month = this.month < 10 ? '0' + String(this.month) : String(this.month);
    date += month + '-';
    let day = this.day < 10 ? '0' + String(this.day) : String(this.day);
    date += day;
    return date;
  }
}

export class DateStyleOptions extends CommonOptions {
  public year?: int;
  public month?: int;
  public day?: int;
  public onDateChange?: (date: DateData) => void;
}

export class CounterOptions {
  public type: CounterType = CounterType.LIST;
  public direction?: Direction;
  public numberOptions?: NumberStyleOptions;
  public inlineOptions?: InlineStyleOptions;
  public dateOptions?: DateStyleOptions;
}

class CounterResource {
  // counter color
  public static readonly BUTTON_BACKGROUD_COLOR = $r('sys.color.ohos_id_color_button_normal');
  public static readonly BUTTON_ICON_COLOR = $r('sys.color.ohos_id_color_primary');
  public static readonly BUTTON_BORDER_FOCUSED_COLOR = $r('sys.color.ohos_id_color_focused_outline');
  public static readonly COUNTER_TEXT_COLOR = $r('sys.color.ohos_id_color_text_primary');
  public static readonly COUNTER_BORDER_COLOR = $r('sys.color.ohos_id_color_component_normal');
  // button icon
  public static readonly BUTTON_ADD_ICON = $r("sys.media.ohos_ic_public_add");
  public static readonly BUTTON_SUB_ICON = $r("sys.media.ohos_ic_public_minus");
  public static readonly BUTTON_ARROW_UP = $r('sys.media.ohos_ic_public_arrow_up');
  public static readonly BUTTON_ARROW_DOWN = $r('sys.media.ohos_ic_public_arrow_down');
  // counter size
  public static readonly BUTTON_BORDER_FOCUSED_WIDTH = '2vp';
  public static readonly BUTTON_BORDER_BLUR_WIDTH = '0vp';
  public static readonly COUNTER_BORDER_WIDTH_NUMBER: number = 1;
  public static readonly COUNTER_LIST_LABEL_SIZE = $r('sys.float.ohos_id_text_size_body1');
  public static readonly COUNTER_LIST_NUMBER_SIZE = $r('sys.float.ohos_id_text_size_body1');
  public static readonly COUNTER_COMPACT_LABEL_SIZE = $r('sys.float.ohos_id_text_size_body2');
  public static readonly COUNTER_NUMBER_SIZE = $r('sys.float.ohos_id_text_size_body1');
  public static readonly COUNTER_LIST_LEFT_PADDING = $r('sys.float.ohos_id_default_padding_start');
  public static readonly COUNTER_LIST_RIGHT_PADDING = $r('sys.float.ohos_id_default_padding_end');
  public static readonly COUNTER_COMPACT_BUTTON_ICON_SIZE = $r('sys.float.button_icon_size');
  public static readonly COUNTER_COMPACT_CONTAINER_HEIGHT = $r('sys.float.container_height');
  public static readonly COUNTER_BORDER_WIDTH = $r('sys.float.border_width');
  public static readonly COUNTER_COMPACT_BUTTON_SIZE = $r('sys.float.button_size');
  public static readonly COUNTER_COMPACT_CONTAINER_RADIUS = $r('sys.float.container_radius');
  public static readonly COUNTER_COMPACT_BUTTON_CONTAINER_MARGIN = $r('sys.float.button_container_margin');
  public static readonly COUNTER_LIST_PADDING: number = 12;
  public static readonly COUNTER_LIST_HEIGHT = '48vp';
  public static readonly COUNTER_LIST_BUTTON_ICON_SIZE = '20vp';
  public static readonly COUNTER_LIST_BUTTON_SIZE = '32vp';
  public static readonly COUNTER_LIST_BUTTON_RADIUS = '16vp';
  public static readonly COUNTER_LIST_BUTTON_TEXT_DISTANCE = '8vp';
  public static readonly COUNTER_LIST_BUTTON_TEXT_MARGIN: number = 8;
  public static readonly COUNTER_LIST_FOCUS_BORDER_SIZE = '30vp';
  public static readonly COUNTER_LIST_FOCUS_BORDER_RADIUS = '15vp';
  public static readonly COUNTER_LIST_BUTTON_HOT_SPOT_X = '-8vp';
  public static readonly COUNTER_LIST_BUTTON_HOT_SPOT_Y = '-8vp';
  public static readonly COUNTER_COMPACT_BUTTON_RADIUS = '12vp';
  public static readonly COUNTER_COMPACT_BUTTON_TEXT_DISTANCE = '10vp';
  public static readonly COUNTER_COMPACT_BUTTON_TEXT_MARGIN: number = 10;
  public static readonly COUNTER_COMPACT_CONTAINER_LABEL_DISTANCE: number = 8;
  public static readonly COUNTER_COMPACT_FOCUS_BORDER_SIZE = '22vp';
  public static readonly COUNTER_COMPACT_FOCUS_BORDER_RADIUS = '11vp';
  public static readonly COUNTER_INLINE_BUTTON_ICON_WIDTH = '24vp';
  public static readonly COUNTER_INLINE_BUTTON_ICON_HEIGHT = '12vp';
  public static readonly COUNTER_INLINE_BUTTON_TEXT_DISTANCE = '12vp';
  public static readonly COUNTER_INLINE_CONTAINER_HEIGHT = '32vp';
  public static readonly COUNTER_INLINE_BUTTON_WIDTH = '32vp';
  public static readonly COUNTER_INLINE_BUTTON_HEIGHT = '16vp';
  public static readonly COUNTER_INLINE_RADIUS = '8vp';
  public static readonly COUNTER_INLINE_FOCUS_BORDER_WIDTH = '28vp';
  public static readonly COUNTER_INLINE_FOCUS_BORDER_HEIGHT = '13.5vp';
  public static readonly COUNTER_INLINE_DATE_TEXT_MARGIN: number = 12;
  public static readonly COUNTER_INLINE_INPUT_TEXT_MARGIN: number = 12;
  public static readonly COUNTER_BUTTON_INITIAL_OPACITY: number = 1;
  public static readonly COUNTER_BUTTON_DISABLE_OPACITY: number = 0.4;
  public static readonly COUNTER_LABEL_MAX_FONT_SIZE_SCALE: number = 2;
  public static readonly COUNTER_NUMBER_MAX_FONT_SIZE_SCALE: number = 1;
}

class CounterConstant {
  public static readonly COUNTER_MAX_YEAR: int = 5000;
  public static readonly COUNTER_MIN_YEAR: int = 1;
  public static readonly COUNTER_INITIAL_MONTH: int = 1;
  public static readonly COUNTER_INITIAL_DAY: int = 1;
  public static readonly COUNTER_INITIAL_STEP: int = 1;
  public static readonly COUNTER_TEN_NUMBER: int = 10;
  public static readonly COUNTER_MIN_MONTH: int = 1;
  public static readonly COUNTER_MAX_MONTH: int = 12;
  public static readonly COUNTER_MIN_DAY: int = 1;
  public static readonly KEYCODE_DPAD_UP: number = 2012;
  public static readonly KEYCODE_DPAD_DOWN: number = 2013;
  public static readonly KEYCODE_DPAD_LEFT: number = 2014;
  public static readonly KEYCODE_DPAD_RIGHT: number = 2015;
  public static readonly KEYCODE_MOVE_HOME: number = 2081;
  public static readonly KEYCODE_MOVE_END: number = 2082;
  public static readonly KEYCODE_TAB: number = 2049;
  public static readonly KEYCODE_ESC: number = 2070;
  public static readonly COUNTER_MIN_VALUE: int = 0;
  public static readonly COUNTER_MAX_VALUE: int = 999;
  public static readonly JANUARY: int = 1;
  public static readonly FEBRUARY: int = 2;
  public static readonly MARCH: int = 3;
  public static readonly APRIL: int = 4;
  public static readonly MAY: int = 5;
  public static readonly JUNE: int = 6;
  public static readonly JULY: int = 7;
  public static readonly AUGUST: int = 8;
  public static readonly SEPTEMBER: int = 9;
  public static readonly OCTOBER: int = 10;
  public static readonly NOVEMBER: int = 11;
  public static readonly DECEMBER: int = 12;
  public static readonly BIG_MONTH_DAYS: int = 31;
  public static readonly SMALL_MONTH_DAYS: int = 30;
  public static readonly FEBRUARY_DAYS: int = 28;
  public static readonly AUSPICIOUS_FEBRUARY_DAYS: int = 29;
  public static readonly AUSPICIOUS_FOUR: int = 4;
  public static readonly AUSPICIOUS_HUNDRED: int = 100;
  public static readonly AUSPICIOUS_FOUR_HUNDRED: int = 400;
}

@Component
export struct CounterComponent {
  @PropRef @Watch('onOptionsChange') options: CounterOptions = new CounterOptions();
  @State type: number = -1;
  @State counterDirection: Direction = Direction.Auto;
  @State choverEffect: HoverEffect = HoverEffect.Auto;
  @State focusEnable: boolean = true;
  @State step: int = CounterConstant.COUNTER_INITIAL_STEP as int;
  @State inputValue: string = '0';
  @State inputYear: int = CounterConstant.COUNTER_MIN_YEAR;
  @State inputMoon: int = 0;
  @State inputDay: int = 0;
  @State inputHour: int = 0;
  @State inputMinute: int = 0;
  @State inputSecond: int = 0;
  @State subOpacity: number = CounterResource.COUNTER_BUTTON_INITIAL_OPACITY as number;
  @State addOpacity: number = CounterResource.COUNTER_BUTTON_INITIAL_OPACITY as number;
  @State subBtnStateEffect: boolean = true;
  @State addBtnStateEffect: boolean = true;
  @State focusText: FocusText = FocusText.NONE;
  @State hasFocusText1: boolean = false
  @State hasFocusText2: boolean = false
  @State hasFocusText3: boolean = false
  @State subBtnFocusWidth: string = '0vp'
  @State addBtnFocusWidth: string = '0vp'
  @State value: int = 0;
  @State year: int = 0;
  @State month: int = 0;
  @State day: int = 0;
  @State hour: int = 0;
  @State minute: int = 0;
  @State second: int = 0;
  @State subBtnEnabled: boolean = true
  @State addBtnEnabled: boolean = true
  @State hasInputText1: boolean = false;
  @State hasInputText2: boolean = false;
  @State hasInputText3: boolean = false;
  @State textWidth: double = 0;
  @State min: int = CounterConstant.COUNTER_MIN_VALUE as int;
  @State max: int = CounterConstant.COUNTER_MAX_VALUE as int;
  private maxYear: int = CounterConstant.COUNTER_MAX_YEAR;
  private minYear: int = CounterConstant.COUNTER_MIN_YEAR;
  private numberStrList: Array<string> = ['00', '01', '02', '03', '04', '05', '06', '07', '08', '09'];
  private onHoverIncrease?: (isHover: boolean) => void;
  private onHoverDecrease?: (isHover: boolean) => void;
  private onFocusIncrease?: () => void;
  private onFocusDecrease?: () => void;
  private onBlurIncrease?: () => void;
  private onBlurDecrease?: () => void;
  private onChange?: (value: int) => void;
  private onDateChange?: (date: DateData) => void;
  private timeoutID1: int = -1;
  private timeoutID2: int = -1;
  private timeoutID3: int = -1;
  private numberStyleOptions: NumberStyleOptions = new NumberStyleOptions();
  private dateStyleOptions: DateStyleOptions = new DateStyleOptions();
  private inlineStyleOptions: InlineStyleOptions = new InlineStyleOptions();
  private timeStamp: number = 0;
  private hasTextWidth: boolean = false;
  private controller1: TextInputController = new TextInputController();
  private controller2: TextInputController = new TextInputController();
  private controller3: TextInputController = new TextInputController();
  private increaseStrCache: string | undefined = undefined;
  private reduceStrCache: string | undefined = undefined;
  private lastOptionValue: int = -1;

  getTextInputFontSize() {
    let fontSize = this.resourceToVp(CounterResource.COUNTER_NUMBER_SIZE);
    let uiContext = this.getUIContext();
    let fontSizeScale: number = (uiContext.getHostContext() as common.UIAbilityContext)?.config?.fontSizeScale ?? 1;
    if (fontSizeScale < 1) {
      return fontSize + 'fp';
    } else {
      return fontSize + 'vp';
    }
  }

  getDate(value: string | undefined): string {
    return `[n2] ${value} [n0]`
  }

  getDateYear(value: int): string {
    const locale = i18n.System.getSystemLocaleInstance();
    const localeID = locale.toString();
    let date = new Date(this.year, this.month - 1, this.day);
    date.setFullYear(this.year);
    let dateFormatYear = new intl.DateTimeFormat(localeID, { year: 'numeric' });
    let formattedDateYear = dateFormatYear.format(date);
    return this.getDate(formattedDateYear);
  }

  getDateMonth(value: int): string {
    const locale = i18n.System.getSystemLocaleInstance();
    const localeID = locale.toString();
    let date = new Date(this.year, this.month - 1, this.day);
    date.setFullYear(this.year);
    let dateFormatMonth = new intl.DateTimeFormat(localeID, { month: 'long'});
    let formattedDateMonth = dateFormatMonth.format(date);
    return this.getDate(formattedDateMonth);
  }

  getDateDay(value: int): string {
    const manager = this.getUIContext().getHostContext()?.resourceManager;
    if (!manager) {
      return this.getDate('');
    }
    let dateDayMap = new Map<int, string>([
      [1, manager.getStringByNameSync('First_counter_accessibility_text')],
      [2, manager.getStringByNameSync('Second_counter_accessibility_text')],
      [3, manager.getStringByNameSync('Third_counter_accessibility_text')],
      [4, manager.getStringByNameSync('Fourth_counter_accessibility_text')],
      [5, manager.getStringByNameSync('Fifth_counter_accessibility_text')],
      [6, manager.getStringByNameSync('Sixth_counter_accessibility_text')],
      [7, manager.getStringByNameSync('Seventh_counter_accessibility_text')],
      [8, manager.getStringByNameSync('Eighth_counter_accessibility_text')],
      [9, manager.getStringByNameSync('Ninth_counter_accessibility_text')],
      [10, manager.getStringByNameSync('Tenth_counter_accessibility_text')],
      [11, manager.getStringByNameSync('Eleventh_counter_accessibility_text')],
      [12, manager.getStringByNameSync('Twelfth_counter_accessibility_text')],
      [13, manager.getStringByNameSync('Thirteenth_counter_accessibility_text')],
      [14, manager.getStringByNameSync('Fourteenth_counter_accessibility_text')],
      [15, manager.getStringByNameSync('Fifteenth_counter_accessibility_text')],
      [16, manager.getStringByNameSync('Sixteenth_counter_accessibility_text')],
      [17, manager.getStringByNameSync('Seventeenth_counter_accessibility_text')],
      [18, manager.getStringByNameSync('Eighteenth_counter_accessibility_text')],
      [19, manager.getStringByNameSync('Nineteenth_counter_accessibility_text')],
      [20, manager.getStringByNameSync('Twentieth_counter_accessibility_text')],
      [21, manager.getStringByNameSync('TwentyFirst_counter_accessibility_text')],
      [22, manager.getStringByNameSync('TwentySecond_counter_accessibility_text')],
      [23, manager.getStringByNameSync('TwentyThird_counter_accessibility_text')],
      [24, manager.getStringByNameSync('TwentyFourth_counter_accessibility_text')],
      [25, manager.getStringByNameSync('TwentyFifth_counter_accessibility_text')],
      [26, manager.getStringByNameSync('TwentySixth_counter_accessibility_text')],
      [27, manager.getStringByNameSync('TwentySeventh_counter_accessibility_text')],
      [28, manager.getStringByNameSync('TwentyEighth_counter_accessibility_text')],
      [29, manager.getStringByNameSync('TwentyNinth_counter_accessibility_text')],
      [30, manager.getStringByNameSync('Thirtieth_counter_accessibility_text')],
      [31, manager.getStringByNameSync('ThirtyFirst_counter_accessibility_text')],
    ]);
    return this.getDate(dateDayMap.get(this.day));
  }

  convertNumberToString(value: int) {
    if (value >= 0 && value < CounterConstant.COUNTER_TEN_NUMBER) {
      return this.numberStrList[value];
    } else {
      return String(value);
    }
  }

  aboutToAppear(): void {
    let dateTime = new Date();
    this.timeStamp = dateTime.getTime();
    if (this.options !== undefined && this.options !== null) {
      this.onOptionsChange('');
    }
  }

  private updateNumberStyleOptions() {
    if (this.numberStyleOptions.label === undefined) {
      this.numberStyleOptions.label = '';
    }
    if (this.numberStyleOptions.value !== undefined && this.numberStyleOptions.value !== this.lastOptionValue) {
      this.lastOptionValue = this.numberStyleOptions.value as int;
      this.value = this.numberStyleOptions.value as int;
      this.onChange?.(this.value);
      this.inputValue = String(this.value);
    }
    if (this.numberStyleOptions.min !== undefined) {
      this.min = (this.numberStyleOptions.min as int) >= 0 ? (this.numberStyleOptions.min as int) : CounterConstant.COUNTER_MIN_VALUE;
    }
    if (this.numberStyleOptions.max !== undefined) {
      this.max = (this.numberStyleOptions.max as int) >= 0 ? (this.numberStyleOptions.max as int) : CounterConstant.COUNTER_MAX_VALUE;
    }
    if (this.min > this.max) {
      this.min = this.max;
    }
    if (this.numberStyleOptions.textWidth !== undefined) {
      this.textWidth = this.numberStyleOptions.textWidth as double;
      if (this.textWidth < 0) {
        this.textWidth = 0;
      }
      this.hasTextWidth = true;
    }
    if (this.value <= this.min) {
      this.value = this.min;
      this.onChange?.(this.value);
      this.inputValue = String(this.value);
    }
    if (this.value >= this.max) {
      this.value = this.max;
      this.onChange?.(this.value);
      this.inputValue = String(this.value);
    }
    if (this.numberStyleOptions.step !== undefined) {
      if ((this.numberStyleOptions.step as int) < 1) {
        this.step = 1
      } else {
        this.step = this.numberStyleOptions.step as int;
      }
    }
    this.updateButtonStatus()
    this.updateNumberStyleOptionsEvent();
  }

  private updateNumberStyleOptionsEvent() {
    if (this.numberStyleOptions.onHoverIncrease !== undefined) {
      this.onHoverIncrease = this.numberStyleOptions.onHoverIncrease;
    }
    if (this.numberStyleOptions.onHoverDecrease !== undefined) {
      this.onHoverDecrease = this.numberStyleOptions.onHoverDecrease;
    }
    if (this.numberStyleOptions.onFocusIncrease !== undefined) {
      this.onFocusIncrease = this.numberStyleOptions.onFocusIncrease;
    }
    if (this.numberStyleOptions.onFocusDecrease !== undefined) {
      this.onFocusDecrease = this.numberStyleOptions.onFocusDecrease;
    }
    if (this.numberStyleOptions.onBlurIncrease !== undefined) {
      this.onBlurIncrease = this.numberStyleOptions.onBlurIncrease;
    }
    if (this.numberStyleOptions.onBlurDecrease !== undefined) {
      this.onBlurDecrease = this.numberStyleOptions.onBlurDecrease;
    }
    if (this.numberStyleOptions.onChange !== undefined) {
      this.onChange = this.numberStyleOptions.onChange;
    }
    if (this.numberStyleOptions.focusable !== undefined) {
      this.focusEnable = !!this.numberStyleOptions.focusable;
    }
  }

  private updateInlineStyleOptions() {
    if (this.inlineStyleOptions.value !== undefined && this.inlineStyleOptions.value !== this.lastOptionValue) {
      this.lastOptionValue = this.inlineStyleOptions.value as int;
      this.value = this.inlineStyleOptions.value as int;
      this.onChange?.(this.value);
      this.inputValue = String(this.value);
    }
    if (this.inlineStyleOptions.min !== undefined) {
      this.min = (this.inlineStyleOptions.min as int) >= 0 ? (this.inlineStyleOptions.min as int) : CounterConstant.COUNTER_MIN_VALUE;
    }
    if (this.inlineStyleOptions.max !== undefined) {
      this.max = (this.inlineStyleOptions.max as int) >= 0 ? (this.inlineStyleOptions.max as int) : CounterConstant.COUNTER_MAX_VALUE;
    }
    if (this.min > this.max) {
      this.min = this.max;
    }

    if (this.inlineStyleOptions.textWidth !== undefined) {
      this.textWidth = this.inlineStyleOptions.textWidth as double;
      if (this.textWidth < 0) {
        this.textWidth = 0;
      }
      this.hasTextWidth = true;
    }
    if (this.value <= this.min) {
      this.value = this.min;
      this.onChange?.(this.value);
      this.inputValue = String(this.value);
    }
    if (this.value >= this.max) {
      this.value = this.max;
      this.onChange?.(this.value);
      this.inputValue = String(this.value);
    }
    if (this.inlineStyleOptions.step !== undefined) {
      if ((this.inlineStyleOptions.step as int) < 1) {
        this.step = 1
      } else {
        this.step = this.inlineStyleOptions.step as int;
      }
    }
    this.updateButtonStatus()
    this.updateInlineStyleOptionsEvent();
  }

  private updateInlineStyleOptionsEvent() {
    if (this.inlineStyleOptions.onHoverIncrease !== undefined) {
      this.onHoverIncrease = this.inlineStyleOptions.onHoverIncrease;
    }
    if (this.inlineStyleOptions.onHoverDecrease !== undefined) {
      this.onHoverDecrease = this.inlineStyleOptions.onHoverDecrease;
    }
    if (this.inlineStyleOptions.onChange !== undefined) {
      this.onChange = this.inlineStyleOptions.onChange;
    }
    if (this.inlineStyleOptions.focusable !== undefined) {
      this.focusEnable = !!this.inlineStyleOptions.focusable;
    }
  }

  private updateDateStyleOptions() {
    if (this.dateStyleOptions.step !== undefined) {
      if ((this.dateStyleOptions.step as int) < 1) {
        this.step = 1
      } else {
        this.step = this.dateStyleOptions.step as int;
      }
    }
    if (this.dateStyleOptions.onHoverIncrease !== undefined) {
      this.onHoverIncrease = this.dateStyleOptions.onHoverIncrease;
    }
    if (this.dateStyleOptions.onHoverDecrease !== undefined) {
      this.onHoverDecrease = this.dateStyleOptions.onHoverDecrease;
    }
    if (this.dateStyleOptions.year !== undefined) {
      const yearValue = this.dateStyleOptions.year as int;
      if (yearValue >= this.minYear && yearValue <= this.maxYear) {
        this.year = yearValue;
      } else {
        this.year = CounterConstant.COUNTER_MIN_YEAR;
      }
    } else {
      this.year = CounterConstant.COUNTER_MIN_YEAR;
    }
    if (this.dateStyleOptions.month !== undefined) {
      const monthValue = this.dateStyleOptions.month as int;
      if (monthValue <= CounterConstant.COUNTER_MAX_MONTH && monthValue >= CounterConstant.COUNTER_MIN_MONTH) {
        this.month = monthValue;
      } else {
        this.month = CounterConstant.COUNTER_INITIAL_MONTH;
      }
    } else {
      this.month = CounterConstant.COUNTER_INITIAL_MONTH;
    }
    if (this.dateStyleOptions.day !== undefined) {
      const dateValue = this.dateStyleOptions.day as int;
      if (dateValue <= this.getDayNumber() && dateValue >= CounterConstant.COUNTER_MIN_DAY) {
        this.day = dateValue;
      }  else {
        this.day = CounterConstant.COUNTER_INITIAL_DAY;
      }
    } else {
      this.day = CounterConstant.COUNTER_INITIAL_DAY;
    }
    if (this.dateStyleOptions.onDateChange !== undefined) {
      this.onDateChange = this.dateStyleOptions.onDateChange;
    }
    if (this.dateStyleOptions.focusable !== undefined) {
      this.focusEnable = !!this.dateStyleOptions.focusable;
    }
    this.updateDay();
  }

  private onOptionsChange(str: string) {
    this.type = this.options.type;
    if (this.options.direction !== undefined) {
      this.counterDirection = this.options.direction as Direction;
    } else {
      this.counterDirection = Direction.Auto;
    }

    if (this.type === CounterType.LIST ||
      this.type === CounterType.COMPACT) {
      if (this.options.numberOptions !== undefined) {
        this.numberStyleOptions = this.options.numberOptions as NumberStyleOptions;
      }
      this.updateNumberStyleOptions();
    } else if (this.type === CounterType.INLINE) {
      if (this.options.inlineOptions !== undefined) {
        this.inlineStyleOptions = this.options.inlineOptions as InlineStyleOptions;
      }
      this.updateInlineStyleOptions();
    } else if (this.type === CounterType.INLINE_DATE) {
      let options = this.options.dateOptions;
      if (options !== undefined) {
        options.year = options.year ? options.year : CounterConstant.COUNTER_MIN_YEAR;
        options.month = options.month ? options.month : CounterConstant.COUNTER_MIN_MONTH;
        options.day = options.day ? options.day : CounterConstant.COUNTER_MIN_DAY;
        this.dateStyleOptions = options;
      }
      this.updateDateStyleOptions();
    } else {

    }
  }

  private subValue(): void {
    if (this.subBtnStateEffect) {
      this.value -= this.step;
    }
    if (!this.addBtnStateEffect) {
      this.addBtnStateEffect = true;
      this.addOpacity = CounterResource.COUNTER_BUTTON_INITIAL_OPACITY;
      this.addBtnEnabled = true;
    }
    if (this.value <= this.min) {
      this.value = this.min;
      this.subOpacity = CounterResource.COUNTER_BUTTON_DISABLE_OPACITY;
      this.subBtnStateEffect = false;
      this.subBtnEnabled = false;
    } else {
      if (this.subOpacity === CounterResource.COUNTER_BUTTON_DISABLE_OPACITY) {
        this.subOpacity = CounterResource.COUNTER_BUTTON_INITIAL_OPACITY;
      }
      if (!this.subBtnStateEffect) {
        this.subBtnStateEffect = true;
      }
      if (!this.subBtnEnabled) {
        this.subBtnEnabled = true;
      }
    }
    this.focusText1();
  }

  private focusText1() {
    if (this.type === CounterType.INLINE) {
      if (this.focusText === FocusText.NONE) {
        this.focusText = FocusText.TEXT1;
        this.hasFocusText1 = true;
        this.focusWithTarget('InlineTextInput' + String(this.timeStamp));
      }
    }
  }

  private addValue(): void {
    if (this.addBtnStateEffect) {
      this.value += this.step;
    }

    if (!this.subBtnStateEffect) {
      this.subBtnStateEffect = true;
      this.subOpacity = CounterResource.COUNTER_BUTTON_INITIAL_OPACITY;
      this.subBtnEnabled = true;
    }
    if (this.value >= this.max) {
      this.value = this.max;
      this.addOpacity = CounterResource.COUNTER_BUTTON_DISABLE_OPACITY;
      this.addBtnStateEffect = false;
      this.addBtnEnabled = false;
    } else {
      if (this.addOpacity === CounterResource.COUNTER_BUTTON_DISABLE_OPACITY) {
        this.addOpacity = CounterResource.COUNTER_BUTTON_INITIAL_OPACITY;
      }
      if (!this.addBtnStateEffect) {
        this.addBtnStateEffect = true;
      }
      if (!this.addBtnEnabled) {
        this.addBtnEnabled = true;
      }
    }

    this.focusText1();
  }

  private getDayNumber(): int {
    switch (this.month) {
      case CounterConstant.JANUARY:
      case CounterConstant.MARCH:
      case CounterConstant.MAY:
      case CounterConstant.JULY:
      case CounterConstant.AUGUST:
      case CounterConstant.OCTOBER:
      case CounterConstant.DECEMBER:
        return CounterConstant.BIG_MONTH_DAYS;
        break;
      case CounterConstant.APRIL:
      case CounterConstant.JUNE:
      case CounterConstant.SEPTEMBER:
      case CounterConstant.NOVEMBER:
        return CounterConstant.SMALL_MONTH_DAYS;
        break;
      case CounterConstant.FEBRUARY:
        if ((this.year % CounterConstant.AUSPICIOUS_FOUR === 0 &&
          this.year % CounterConstant.AUSPICIOUS_HUNDRED !== 0) ||
          this.year % CounterConstant.AUSPICIOUS_FOUR_HUNDRED === 0) {
          return CounterConstant.AUSPICIOUS_FEBRUARY_DAYS;
        } else {
          return CounterConstant.FEBRUARY_DAYS;
        }
        break;
      default:
        return CounterConstant.SMALL_MONTH_DAYS;
        break;
    }
  }

  private accessibilityBroadcastSubDate(): void {
    if (this.focusText === FocusText.TEXT1) {
      if (this.subBtnStateEffect) {
        this.inputYear = this.year;
        this.year -= this.step;
        if (!this.hasFocusText1) {
          this.hasFocusText1 = true;
        }
      }
      if (!this.addBtnStateEffect) {
        this.addBtnStateEffect = true;
        this.addOpacity = CounterResource.COUNTER_BUTTON_INITIAL_OPACITY;
        this.addBtnEnabled = true;
      }
      if (this.year <= this.minYear) {
        this.subOpacity = CounterResource.COUNTER_BUTTON_DISABLE_OPACITY;
        this.subBtnStateEffect = false;
        this.subBtnEnabled = false;
      } else {
        if (this.subOpacity === CounterResource.COUNTER_BUTTON_DISABLE_OPACITY) {
          this.subOpacity = CounterResource.COUNTER_BUTTON_INITIAL_OPACITY;
        }
        if (!this.subBtnStateEffect) {
          this.subBtnStateEffect = true;
        }
        if (!this.subBtnEnabled) {
          this.subBtnEnabled = true;
        }
      }
      try {
        const context: common.Context = this.getUIContext().getHostContext() as common.Context;
        const bundleName = (context as common.UIAbilityContext).abilityInfo.bundleName;
        let eventInfo: accessibility.EventInfo = new accessibility.EventInfo(
          'announceForAccessibility',
          bundleName,
          'click',
        );
        accessibility.sendAccessibilityEvent(eventInfo).then(() => {
          console.log('Accessibility subYear click send event');
        });
      } catch (exception) {
        let code: number = (exception as BusinessError).code;
        let message: string = (exception as BusinessError).message;
        console.log(`Accessibility subYear failed error code:${code} message:${message}`);
      }
    } else if (this.focusText === FocusText.TEXT2) {
      this.month -= this.step % CounterConstant.COUNTER_MAX_MONTH;
      if (this.month < CounterConstant.COUNTER_MIN_MONTH) {
        this.month += CounterConstant.COUNTER_MAX_MONTH;
      }
      if (!this.hasFocusText2) {
        this.hasFocusText2 = true;
      }
      try {
        const context: common.Context = this.getUIContext().getHostContext() as common.Context;
        const bundleName = (context as common.UIAbilityContext).abilityInfo.bundleName;
        let eventInfo: accessibility.EventInfo = new accessibility.EventInfo(
          'announceForAccessibility',
          bundleName,
          'click',
        );
        accessibility.sendAccessibilityEvent(eventInfo).then(() => {
          console.log('Accessibility subMonth click send event');
        });
      } catch (exception) {
        let code: number = (exception as BusinessError).code;
        let message: string = (exception as BusinessError).message;
        console.log(`Accessibility subMonth failed error code:${code} message:${message}`);
      }
    } else if (this.focusText === FocusText.TEXT3) {
      this.day -= this.step % this.getDayNumber();
      if (this.day < CounterConstant.COUNTER_MIN_DAY) {
        this.day += this.getDayNumber();
      }
      if (!this.hasFocusText3) {
        this.hasFocusText3 = true;
      }
      try {
        const context: common.Context = this.getUIContext().getHostContext() as common.Context;
        const bundleName = (context as common.UIAbilityContext).abilityInfo.bundleName;
        let eventInfo: accessibility.EventInfo = new accessibility.EventInfo(
          'announceForAccessibility',
          bundleName,
          'click',
        );
        accessibility.sendAccessibilityEvent(eventInfo).then(() => {
          console.log('Accessibility subDay click send event');
        });
      } catch (exception) {
        let code: number = (exception as BusinessError).code;
        let message: string = (exception as BusinessError).message;
        console.log(`Accessibility subDay failed error code:${code} message:${message}`);
      }
    } else {
      this.focusDayWitdhSub();
    }
  }

  private subDate(): void {
    if (this.focusText === FocusText.TEXT1) {
      if (this.subBtnStateEffect) {
        this.inputYear = this.year;
        this.year -= this.step;
        if (!this.hasFocusText1) {
          this.hasFocusText1 = true;
        }
      }
      if (!this.addBtnStateEffect) {
        this.addBtnStateEffect = true;
        this.addOpacity = CounterResource.COUNTER_BUTTON_INITIAL_OPACITY;
        this.addBtnEnabled = true;
      }
      if (this.year <= this.minYear) {
        this.subOpacity = CounterResource.COUNTER_BUTTON_DISABLE_OPACITY;
        this.subBtnStateEffect = false;
        this.subBtnEnabled = false;
      } else {
        if (this.subOpacity === CounterResource.COUNTER_BUTTON_DISABLE_OPACITY) {
          this.subOpacity = CounterResource.COUNTER_BUTTON_INITIAL_OPACITY;
        }
        if (!this.subBtnStateEffect) {
          this.subBtnStateEffect = true;
        }
        if (!this.subBtnEnabled) {
          this.subBtnEnabled = true;
        }
      }
    } else if (this.focusText === FocusText.TEXT2) {
      this.month -= this.step % CounterConstant.COUNTER_MAX_MONTH;
      if (this.month < CounterConstant.COUNTER_MIN_MONTH) {
        this.month += CounterConstant.COUNTER_MAX_MONTH;
      }
      if (!this.hasFocusText2) {
        this.hasFocusText2 = true;
      }
    } else if (this.focusText === FocusText.TEXT3) {
      this.day -= this.step % this.getDayNumber();
      if (this.day < CounterConstant.COUNTER_MIN_DAY) {
        this.day += this.getDayNumber();
      }
      if (!this.hasFocusText3) {
        this.hasFocusText3 = true;
      }
    } else {
      this.focusDayWitdhSub();
    }
  }

  private focusDayWitdhSub() {
    this.focusText = FocusText.TEXT3;
    this.hasFocusText3 = true;
    this.day -= this.step % this.getDayNumber();
    if (this.day < CounterConstant.COUNTER_MIN_DAY) {
      this.day += this.getDayNumber();
    }
    this.focusWithTarget('DateTextInput3' + String(this.timeStamp));
  }

  private accessibilityBroadcastAddDate(): void {
    if (this.focusText === FocusText.TEXT1) {
      if (this.addBtnStateEffect) {
        this.inputYear = this.year;
        this.year += this.step;
        if (!this.hasFocusText1) {
          this.hasFocusText1 = true;
        }
      }
      if (!this.subBtnStateEffect) {
        this.subBtnStateEffect = true;
        this.subOpacity = CounterResource.COUNTER_BUTTON_INITIAL_OPACITY;
        this.subBtnEnabled = true;
      }
      if (this.year >= this.maxYear) {
        this.addOpacity = CounterResource.COUNTER_BUTTON_DISABLE_OPACITY;
        this.addBtnStateEffect = false;
        this.addBtnEnabled = false;
      } else {
        if (this.addOpacity === CounterResource.COUNTER_BUTTON_DISABLE_OPACITY) {
          this.addOpacity = CounterResource.COUNTER_BUTTON_INITIAL_OPACITY;
        }
        if (!this.addBtnStateEffect) {
          this.addBtnStateEffect = true;
        }
        if (!this.addBtnEnabled) {
          this.addBtnEnabled = true;
        }
      }
      try {
        const context: common.Context = this.getUIContext().getHostContext() as common.Context;
        const bundleName = (context as common.UIAbilityContext).abilityInfo.bundleName;
        let eventInfo: accessibility.EventInfo = new accessibility.EventInfo(
          'announceForAccessibility',
          bundleName,
          'click',
        );
        accessibility.sendAccessibilityEvent(eventInfo).then(() => {
          console.log('Accessibility addYear click send event');
        });
      } catch (exception) {
        let code: number = (exception as BusinessError).code;
        let message: string = (exception as BusinessError).message;
        console.log(`Accessibility addYear click failed error code:${code} message:${message}`);
      }
    } else if (this.focusText === FocusText.TEXT2) {
      this.month += this.step % CounterConstant.COUNTER_MAX_MONTH;
      if (this.month > CounterConstant.COUNTER_MAX_MONTH) {
        this.month -= CounterConstant.COUNTER_MAX_MONTH;
      }
      if (!this.hasFocusText2) {
        this.hasFocusText2 = true;
      }
      try {
        const context: common.Context = this.getUIContext().getHostContext() as common.Context;
        const bundleName = (context as common.UIAbilityContext).abilityInfo.bundleName;
        let eventInfo: accessibility.EventInfo = new accessibility.EventInfo(
          'announceForAccessibility',
          bundleName,
          'click',
        );
        accessibility.sendAccessibilityEvent(eventInfo).then(() => {
          console.log('Accessibility addMonth click send event');
        });
      } catch (exception) {
        let code: number = (exception as BusinessError).code;
        let message: string = (exception as BusinessError).message;
        console.log(`Accessibility addMonth failed error code:${code} message:${message}`);
      }
    } else if (this.focusText === FocusText.TEXT3) {
      this.day += this.step % this.getDayNumber();
      if (this.day > this.getDayNumber()) {
        this.day -= this.getDayNumber();
      }
      if (!this.hasFocusText3) {
        this.hasFocusText3 = true;
      }
      try {
        const context: common.Context = this.getUIContext().getHostContext() as common.Context;
        const bundleName = (context as common.UIAbilityContext).abilityInfo.bundleName;
        let eventInfo: accessibility.EventInfo = new accessibility.EventInfo(
          'announceForAccessibility',
          bundleName,
          'click',
        );
        accessibility.sendAccessibilityEvent(eventInfo).then(() => {
          console.log('Accessibility addDay click send event');
        });
      } catch (exception) {
        let code: number = (exception as BusinessError).code;
        let message: string = (exception as BusinessError).message;
        console.log(`Accessibility addDay failed error code:${code} message:${message}`);
      }
    } else {
      this.focusDayWithAdd();
    }
  }

  private addDate(): void {
    if (this.focusText === FocusText.TEXT1) {
      if (this.addBtnStateEffect) {
        this.inputYear = this.year;
        this.year += this.step;
        if (!this.hasFocusText1) {
          this.hasFocusText1 = true;
        }
      }
      if (!this.subBtnStateEffect) {
        this.subBtnStateEffect = true;
        this.subOpacity = CounterResource.COUNTER_BUTTON_INITIAL_OPACITY;
        this.subBtnEnabled = true;
      }
      if (this.year >= this.maxYear) {
        this.addOpacity = CounterResource.COUNTER_BUTTON_DISABLE_OPACITY;
        this.addBtnStateEffect = false;
        this.addBtnEnabled = false;
      } else {
        if (this.addOpacity === CounterResource.COUNTER_BUTTON_DISABLE_OPACITY) {
          this.addOpacity = CounterResource.COUNTER_BUTTON_INITIAL_OPACITY;
        }
        if (!this.addBtnStateEffect) {
          this.addBtnStateEffect = true;
        }
        if (!this.addBtnEnabled) {
          this.addBtnEnabled = true;
        }
      }
    } else if (this.focusText === FocusText.TEXT2) {
      this.month += this.step % CounterConstant.COUNTER_MAX_MONTH;
      if (this.month > CounterConstant.COUNTER_MAX_MONTH) {
        this.month -= CounterConstant.COUNTER_MAX_MONTH;
      }
      if (!this.hasFocusText2) {
        this.hasFocusText2 = true;
      }
    } else if (this.focusText === FocusText.TEXT3) {
      this.day += this.step % this.getDayNumber();
      if (this.day > this.getDayNumber()) {
        this.day -= this.getDayNumber();
      }
      if (!this.hasFocusText3) {
        this.hasFocusText3 = true;
      }
    } else {
      this.focusDayWithAdd();
    }
  }

  private focusDayWithAdd() {
    this.focusText = FocusText.TEXT3;
    this.hasFocusText3 = true;
    this.day += this.step % this.getDayNumber();
    if (this.day > this.getDayNumber()) {
      this.day -= this.getDayNumber();
    }
    this.focusWithTarget('DateTextInput3' + String(this.timeStamp));
  }

  private updateInlineEnableSate() {
    if (this.value >= this.max) {
      this.addOpacity = CounterResource.COUNTER_BUTTON_DISABLE_OPACITY;
      this.addBtnStateEffect = false;
      this.addBtnEnabled = false;
    } else {
      this.addOpacity = CounterResource.COUNTER_BUTTON_INITIAL_OPACITY;
      this.addBtnStateEffect = true;
      this.addBtnEnabled = true;
    }
    if (this.value <= this.min) {
      this.subOpacity = CounterResource.COUNTER_BUTTON_DISABLE_OPACITY;
      this.subBtnStateEffect = false;
      this.subBtnEnabled = false;
    } else {
      this.subOpacity = CounterResource.COUNTER_BUTTON_INITIAL_OPACITY;
      this.subBtnStateEffect = true;
      this.subBtnEnabled = true;
    }
  }

  private updateDateEnableSate() {
    if (this.year === this.maxYear && this.focusText === FocusText.TEXT1) {
      this.addOpacity = CounterResource.COUNTER_BUTTON_DISABLE_OPACITY;
      this.addBtnStateEffect = false;
      this.addBtnEnabled = false;
    } else {
      if (this.addOpacity === CounterResource.COUNTER_BUTTON_DISABLE_OPACITY) {
        this.addOpacity = CounterResource.COUNTER_BUTTON_INITIAL_OPACITY;
      }
      if (!this.addBtnStateEffect) {
        this.addBtnStateEffect = true;
      }
      if (!this.addBtnEnabled) {
        this.addBtnEnabled = true;
      }
    }
    if (this.year === this.minYear && this.focusText === FocusText.TEXT1) {
      this.subOpacity = CounterResource.COUNTER_BUTTON_DISABLE_OPACITY;
      this.subBtnStateEffect = false;
      this.subBtnEnabled = false;
    } else {
      if (this.subOpacity === CounterResource.COUNTER_BUTTON_DISABLE_OPACITY) {
        this.subOpacity = CounterResource.COUNTER_BUTTON_INITIAL_OPACITY;
      }
      if (!this.subBtnStateEffect) {
        this.subBtnStateEffect = true;
      }
      if (!this.subBtnEnabled) {
        this.subBtnEnabled = true;
      }
    }
  }

  private updateDay() {
    if (this.day > this.getDayNumber()) {
      this.day = this.getDayNumber();
    }
  }

  private resetFocusText() {
    this.focusText = FocusText.NONE;
    this.hasFocusText1 = false;
    this.hasFocusText2 = false;
    this.hasFocusText3 = false;
  }

  private resetFocusButton() {
    if (this.addBtnFocusWidth === CounterResource.BUTTON_BORDER_FOCUSED_WIDTH) {
      this.addBtnFocusWidth = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
      this.onBlurIncrease?.();
    }
    if (this.subBtnFocusWidth === CounterResource.BUTTON_BORDER_FOCUSED_WIDTH) {
      this.subBtnFocusWidth = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
      this.onBlurDecrease?.();
    }
  }

  private homeFocusText() {
    this.focusWithTarget('DateTextInput1' + String(this.timeStamp));
  }

  private endFocusText() {
    this.focusWithTarget('DateTextInput3' + String(this.timeStamp));
  }

  private homeFirstValue() {
    this.value = this.min;
    if (!this.addBtnStateEffect) {
      this.addBtnStateEffect = true;
      this.addOpacity = CounterResource.COUNTER_BUTTON_INITIAL_OPACITY;
      this.addBtnEnabled = true;
    }
  }

  private endLastValue() {
    this.value = this.max;
    if (!this.subBtnStateEffect) {
      this.subBtnStateEffect = true;
      this.subOpacity = CounterResource.COUNTER_BUTTON_INITIAL_OPACITY;
      this.subBtnEnabled = true;
    }
  }

  private updateButtonStatus() {
    if (this.value <= this.min) {
      if (!this.addBtnStateEffect && this.max != this.min) {
        this.addBtnStateEffect = true;
        this.addOpacity = CounterResource.COUNTER_BUTTON_INITIAL_OPACITY;
        this.addBtnEnabled = true;
      }
      this.subOpacity = CounterResource.COUNTER_BUTTON_DISABLE_OPACITY;
      this.subBtnStateEffect = false;
      this.subBtnEnabled = false;
    }
    if (this.value >= this.max) {
      if (!this.subBtnStateEffect && this.max != this.min) {
        this.subBtnStateEffect = true;
        this.subOpacity = CounterResource.COUNTER_BUTTON_INITIAL_OPACITY;
        this.subBtnEnabled = true;
      }
      this.addOpacity = CounterResource.COUNTER_BUTTON_DISABLE_OPACITY;
      this.addBtnStateEffect = false;
      this.addBtnEnabled = false;
    }
  }

  private getValue() {
    if (this.inputValue == undefined) {
      this.inputValue = ''
    }
    return this.hasInputText1 ? this.inputValue : String(this.value);
  }

  private getValueLength() {
    return this.getValue().length > 0 ? this.getValue().length : 1;
  }

  private getYear(): string {
    let year: string = String(this.year);
    if (year.length === 1) {
      year = '000' + year;
    } else if (year.length === 2) {
      year = '00' + year;
    } else if (year.length === 3) {
      year = '0' + year;
    } else {
      year = year;
    }
    return year;
  }

  private focusWithTarget(key: string) {
    setTimeout(() => {
      let res = focusControl.requestFocus(key);
      if (res) {
        console.log('Request success');
      } else {
        console.log('Request failed');
      }
    });
  }

  private focusCurrentText(text: FocusText) {
    if (text === FocusText.TEXT1) {
      if (this.focusText === FocusText.NONE) {
        this.focusText = FocusText.TEXT1;
      }
      if (!this.hasFocusText1) {
        this.hasFocusText1 = true;
      }
    } else if (text === FocusText.TEXT2) {
      if (this.focusText === FocusText.NONE) {
        this.focusText = FocusText.TEXT2;
      }
      if (!this.hasFocusText2) {
        this.hasFocusText2 = true;
      }
    } else if (text === FocusText.TEXT3) {
      if (this.focusText === FocusText.NONE) {
        this.focusText = FocusText.TEXT3;
      }
      if (!this.hasFocusText3) {
        this.hasFocusText3 = true;
      }
    } else {

    }
  }

  private getMaxLength() {
    if (String(this.max).length > String(this.min).length) {
      return String(this.max).length + 1;
    } else {
      return String(this.min).length + 1;
    }
  }

  private resourceToVp(value: Resource): number {
    try {
      if ((value as Resource).id !== -1) {
        return this.getUIContext().px2vp(resourceManager.getSysResourceManager().getDouble((value as Resource).id));
      } else {
        return this.getUIContext().px2vp(resourceManager.getSysResourceManager()
          .getDoubleByName(((value.params as Any as string[])[0]).split('.')[2]));
      }
    } catch (error) {
      return CounterResource.COUNTER_LIST_PADDING;
    }
  }

  public getAccessibilityResource(resource: ResourceStr | string | undefined): string {
    let accessibilityResource: string = '';
    try {
      if (typeof resource === 'undefined') {
      } else if (typeof resource === 'string') {
        accessibilityResource = String(resource);
      } else {
        accessibilityResource = resourceManager.getSysResourceManager().getStringSync((resource as Resource).id);
      }
    } catch (error) {
      let code: number = (error as BusinessError).code;
      let message: string = (error as BusinessError).message;
      console.log(`Get accessility resource error code:${code} message:${message}`);
    }
    return accessibilityResource;
  }

  private getTextDirection() {
    if (this.counterDirection === Direction.Auto) {
      const locale = i18n.System.getSystemLocaleInstance();
      const localeID = String(locale);
      return i18n.isRTL(localeID) ? Direction.Rtl : Direction.Ltr;
    } else {
      return this.counterDirection;
    }
  }

  private getAccessibilityDesc(condition: boolean, resource: ResourceStr): ResourceStr | undefined {
    return condition ? resource : undefined;
  }

  private getIncreaseStr(): string {
    if (this.increaseStrCache === undefined) {
      this.increaseStrCache = this.getUIContext().getHostContext()?.resourceManager?.getStringSync(125834852) ?? '';
    }
    return this.increaseStrCache ?? '';
  }

  private getReduceStr(): string {
    if (this.reduceStrCache === undefined) {
      this.reduceStrCache = this.getUIContext().getHostContext()?.resourceManager?.getStringSync(125834853) ?? '';
    }
    return this.reduceStrCache ?? '';
  }

  build() {
    if (this.type === CounterType.LIST) {
      RelativeContainer() {
        Text(this.numberStyleOptions.label)
          .direction(this.getTextDirection())
          .fontSize(CounterResource.COUNTER_LIST_LABEL_SIZE)
          .maxFontScale(CounterResource.COUNTER_LABEL_MAX_FONT_SIZE_SCALE)
          .fontColor(CounterResource.COUNTER_TEXT_COLOR)
          .margin({
            start: LengthMetrics.vp(this.resourceToVp(CounterResource.COUNTER_LIST_LEFT_PADDING))
          } as LocalizedMargin)
          .alignRules({
            center: { anchor: '__container__', align: VerticalAlign.Center as VerticalAlign } as LocalizedVerticalAlignParam,
            start: { anchor: '__container__', align: HorizontalAlign.Start as HorizontalAlign } as LocalizedHorizontalAlignParam,
            end: { anchor: 'Row1', align: HorizontalAlign.Start as HorizontalAlign } as LocalizedHorizontalAlignParam
          } as LocalizedAlignRuleOptions)
          .id('Text')
        Row() {
          Stack() {
            Image(CounterResource.BUTTON_SUB_ICON)
              .direction(this.counterDirection)
              .width(CounterResource.COUNTER_LIST_BUTTON_ICON_SIZE)
              .height(CounterResource.COUNTER_LIST_BUTTON_ICON_SIZE)
              .fillColor(CounterResource.BUTTON_ICON_COLOR)
              .opacity(this.subOpacity)
            Button({ type: ButtonType.Circle, stateEffect: this.subBtnStateEffect } as ButtonOptions)
              .accessibilityText($r('sys.string.reduce_used_for_accessibility_text'))
              .accessibilityDescription(this.value === this.min ? '' : this.getReduceStr())
              .accessibilityFocusDrawLevel(FocusDrawLevel.TOP)
              .direction(this.counterDirection)
              .width(CounterResource.COUNTER_LIST_BUTTON_SIZE)
              .height(CounterResource.COUNTER_LIST_BUTTON_SIZE)
              .responseRegion({
                x: CounterResource.COUNTER_LIST_BUTTON_HOT_SPOT_X,
                y: CounterResource.COUNTER_LIST_BUTTON_HOT_SPOT_Y,
                width: '150%',
                height: '150%'
              } as Rectangle)
              .groupDefaultFocus(true)
              .backgroundColor(CounterResource.BUTTON_BACKGROUD_COLOR)
              .opacity(this.subOpacity)
              .enabled(this.subBtnEnabled)
              .key('ListSubButton' + String(this.timeStamp))
              .onKeyEvent((event: KeyEvent) => {
                this.subBtnFocusWidth = CounterResource.BUTTON_BORDER_FOCUSED_WIDTH;
                if (event.keyCode === CounterConstant.KEYCODE_ESC) {
                  this.resetFocusButton();
                  event.stopPropagation();
                  return true;
                }
                if (event.type === KeyType.Down &&
                  event.keyCode === CounterConstant.KEYCODE_MOVE_HOME) {
                  event.stopPropagation();
                  this.homeFirstValue();
                  this.focusWithTarget('ListAddButton' + String(this.timeStamp));
                  return true;
                }
                if (event.type === KeyType.Down &&
                  event.keyCode === CounterConstant.KEYCODE_MOVE_END) {
                  event.stopPropagation();
                  if (this.addBtnStateEffect) {
                    this.addBtnStateEffect = false;
                    this.addOpacity = CounterResource.COUNTER_BUTTON_DISABLE_OPACITY;
                    this.addBtnEnabled = false;
                  }
                  this.endLastValue();
                  this.focusWithTarget('ListAddButton' + String(this.timeStamp));
                  return true;
                }
                return false;
              })
              .onClick((event: ClickEvent) => {
                this.subValue();
                this.onChange?.(this.value);
                if (event.source === SourceType.Mouse ||
                  event.source === SourceType.TouchScreen) {
                  this.subBtnFocusWidth = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                }
                try {
                  const context: common.Context = this.getUIContext().getHostContext() as common.Context;
                  const bundleName = (context as common.UIAbilityContext).abilityInfo.bundleName;
                  let eventInfo: accessibility.EventInfo = new accessibility.EventInfo(
                    'announceForAccessibility',
                    bundleName,
                    'click',
                  );
                  accessibility.sendAccessibilityEvent(eventInfo).then(() => {
                    console.log('Accessibility subValue click send event');
                  })
                } catch (exception) {
                  let code: number = (exception as BusinessError).code;
                  let message: string = (exception as BusinessError).message;
                  console.log(`Accessibility subValue failed error code:${code} message:${message}`);
                }
              })
              .gesture(
                LongPressGesture({ repeat: true })
                  .onAction((event: GestureEvent) => {
                    if (event.repeat) {
                      this.subValue();
                      this.onChange?.(this.value);
                    }
                    this.subBtnFocusWidth = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                  })
                  .onActionEnd(() => {
                    try {
                      const context: common.Context = this.getUIContext().getHostContext() as common.Context;
                      const bundleName = (context as common.UIAbilityContext).abilityInfo.bundleName;
                      let eventInfo: accessibility.EventInfo = new accessibility.EventInfo(
                        'announceForAccessibility',
                        bundleName,
                        'common',
                      );
                      accessibility.sendAccessibilityEvent(eventInfo).then(() => {
                        console.log('Accessibility subValue longPress send event');
                      })
                    } catch (exception) {
                      let code: number = (exception as BusinessError).code;
                      let message: string = (exception as BusinessError).message;
                      console.log(`Accessibility subValue longPress failed error code:${code} message:${message}`);
                    }
                  })
              )
              .hoverEffect(this.choverEffect)
              .onHover((isHover: boolean, event: HoverEvent) => {
                this.onHoverDecrease?.(isHover);
              })
              .focusable(this.focusEnable)
              .onFocus(() => {
                this.subBtnFocusWidth = CounterResource.BUTTON_BORDER_FOCUSED_WIDTH;
                this.onFocusDecrease?.();
                this.updateButtonStatus();
              })
              .onBlur(() => {
                this.subBtnFocusWidth = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                this.onBlurDecrease?.();
              })
          }
          .direction(this.counterDirection)
          .width(CounterResource.COUNTER_LIST_BUTTON_SIZE)
          .height(CounterResource.COUNTER_LIST_BUTTON_SIZE)
          .borderRadius(CounterResource.COUNTER_LIST_BUTTON_RADIUS)
          .borderWidth(this.subBtnFocusWidth)
          .borderColor(CounterResource.BUTTON_BORDER_FOCUSED_COLOR)
          .clip(true)

          if (this.hasTextWidth) {
            Text(String(this.value))
              .accessibilityText(this.getAccessibilityResource(this.numberStyleOptions.label) + '[n2]' +
              String(this.value) + '[n0]')
              .direction(this.counterDirection)
              .width(String(this.textWidth))
              .textAlign(TextAlign.Center)
              .fontSize(CounterResource.COUNTER_LIST_NUMBER_SIZE)
              .maxFontScale(CounterResource.COUNTER_NUMBER_MAX_FONT_SIZE_SCALE)
              .fontColor(CounterResource.COUNTER_TEXT_COLOR)
              .margin({
                start: LengthMetrics.vp(CounterResource.COUNTER_LIST_BUTTON_TEXT_MARGIN),
                end: LengthMetrics.vp(CounterResource.COUNTER_LIST_BUTTON_TEXT_MARGIN)
              } as LocalizedMargin)
          } else {
            Text(String(this.value))
              .accessibilityText(this.getAccessibilityResource(this.numberStyleOptions.label) + '[n2]' +
              String(this.value) + '[n0]')
              .direction(this.counterDirection)
              .textAlign(TextAlign.Center)
              .fontSize(CounterResource.COUNTER_LIST_NUMBER_SIZE)
              .maxFontScale(CounterResource.COUNTER_NUMBER_MAX_FONT_SIZE_SCALE)
              .fontColor(CounterResource.COUNTER_TEXT_COLOR)
              .margin({
                start: LengthMetrics.vp(CounterResource.COUNTER_LIST_BUTTON_TEXT_MARGIN),
                end: LengthMetrics.vp(CounterResource.COUNTER_LIST_BUTTON_TEXT_MARGIN)
              } as LocalizedMargin)
          }

          Stack() {
            Image(CounterResource.BUTTON_ADD_ICON)
              .direction(this.counterDirection)
              .width(CounterResource.COUNTER_LIST_BUTTON_ICON_SIZE)
              .height(CounterResource.COUNTER_LIST_BUTTON_ICON_SIZE)
              .fillColor(CounterResource.BUTTON_ICON_COLOR)
              .opacity(this.addOpacity)
            Button({ type: ButtonType.Circle, stateEffect: this.addBtnStateEffect } as ButtonOptions)
              .accessibilityText($r('sys.string.increase_used_for_accessibility_text'))
              .accessibilityDescription(this.value === this.max ? '' : this.getIncreaseStr())
              .accessibilityFocusDrawLevel(FocusDrawLevel.TOP)
              .direction(this.counterDirection)
              .width(CounterResource.COUNTER_LIST_BUTTON_SIZE)
              .height(CounterResource.COUNTER_LIST_BUTTON_SIZE)
              .responseRegion({
                x: CounterResource.COUNTER_LIST_BUTTON_HOT_SPOT_X,
                y: CounterResource.COUNTER_LIST_BUTTON_HOT_SPOT_Y,
                width: '150%',
                height: '150%'
              } as Rectangle)
              .backgroundColor(CounterResource.BUTTON_BACKGROUD_COLOR)
              .opacity(this.addOpacity)
              .enabled(this.addBtnEnabled)
              .key('ListAddButton' + String(this.timeStamp))
              .onKeyEvent((event: KeyEvent) => {
                this.addBtnFocusWidth = CounterResource.BUTTON_BORDER_FOCUSED_WIDTH
                if (event.keyCode === CounterConstant.KEYCODE_ESC) {
                  this.resetFocusButton();
                  event.stopPropagation();
                  return true;
                }
                if (event.type === KeyType.Down &&
                  event.keyCode === CounterConstant.KEYCODE_MOVE_HOME) {
                  event.stopPropagation();
                  this.homeFirstValue();
                  if (this.subBtnStateEffect) {
                    this.subBtnStateEffect = false;
                    this.subOpacity = CounterResource.COUNTER_BUTTON_DISABLE_OPACITY;
                    this.subBtnEnabled = false;
                  }
                  this.focusWithTarget('ListAddButton' + String(this.timeStamp));
                  return true;
                }
                if (event.type === KeyType.Down &&
                  event.keyCode === CounterConstant.KEYCODE_MOVE_END) {
                  event.stopPropagation();
                  this.endLastValue();
                  this.focusWithTarget('ListSubButton' + String(this.timeStamp));
                  return true;
                }
                return false;
              })
              .onClick((event: ClickEvent) => {
                this.addValue();
                this.onChange?.(this.value);
                if (event.source === SourceType.Mouse ||
                  event.source === SourceType.TouchScreen) {
                  this.addBtnFocusWidth = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                }
                try {
                  const context: common.Context = this.getUIContext().getHostContext() as common.Context;
                  const bundleName = (context as common.UIAbilityContext).abilityInfo.bundleName;
                  let eventInfo: accessibility.EventInfo = new accessibility.EventInfo(
                    'announceForAccessibility',
                    bundleName,
                    'click',
                  );
                  accessibility.sendAccessibilityEvent(eventInfo).then(() => {
                    console.log('Accessibility addValue click send event');
                  })
                } catch (exception) {
                  let code: number = (exception as BusinessError).code;
                  let message: string = (exception as BusinessError).message;
                  console.log(`Accessibility addValue click longPress failed error code:${code} message:${message}`);
                }
              })
              .gesture(
                LongPressGesture({ repeat: true })
                  .onAction((event: GestureEvent) => {
                    if (event.repeat) {
                      this.addValue();
                      this.onChange?.(this.value);
                    }
                    this.addBtnFocusWidth = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                  })
                  .onActionEnd(() => {
                    try {
                      const context: common.Context = this.getUIContext().getHostContext() as common.Context;
                      const bundleName = (context as common.UIAbilityContext).abilityInfo.bundleName;
                      let eventInfo: accessibility.EventInfo = new accessibility.EventInfo(
                        'announceForAccessibility',
                        bundleName,
                        'common',
                      );
                      accessibility.sendAccessibilityEvent(eventInfo).then(() => {
                        console.log('Accessibility addValue longPress send event');
                      })
                    } catch (exception) {
                      let code: number = (exception as BusinessError).code;
                      let message: string = (exception as BusinessError).message;
                      console.log(`Accessibility addValue longPress longPress failed error code:${code} message:${message}`);
                    }
                  })
              )
              .hoverEffect(this.choverEffect)
              .onHover((isHover: boolean, event: HoverEvent) => {
                this.onHoverIncrease?.(isHover);
              })
              .focusable(this.focusEnable)
              .onFocus(() => {
                this.addBtnFocusWidth = CounterResource.BUTTON_BORDER_FOCUSED_WIDTH;
                this.onFocusIncrease?.();
                this.updateButtonStatus();
              })
              .onBlur(() => {
                this.addBtnFocusWidth = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                this.onBlurIncrease?.();
              })
          }
          .direction(this.counterDirection)
          .width(CounterResource.COUNTER_LIST_BUTTON_SIZE)
          .height(CounterResource.COUNTER_LIST_BUTTON_SIZE)
          .borderRadius(CounterResource.COUNTER_LIST_BUTTON_RADIUS)
          .borderWidth(this.addBtnFocusWidth)
          .borderColor(CounterResource.BUTTON_BORDER_FOCUSED_COLOR)
          .clip(true)
        }
        .direction(this.counterDirection)
        .height(CounterResource.COUNTER_LIST_BUTTON_SIZE)
        .margin({
          end: LengthMetrics.vp(LengthMetrics.resource(CounterResource.COUNTER_LIST_RIGHT_PADDING).value)
        } as LocalizedMargin)
        .alignRules({
          center: { anchor: '__container__', align: VerticalAlign.Center } as LocalizedVerticalAlignParam,
          end: { anchor: '__container__', align: HorizontalAlign.End } as LocalizedHorizontalAlignParam
        } as LocalizedAlignRuleOptions)
        .tabIndex(0)
        .id('Row1')
      }
      .direction(this.counterDirection)
      .width('100%')
      .height(CounterResource.COUNTER_LIST_HEIGHT)
    } else if (this.type === CounterType.COMPACT) {
      Column() {
        Row() {
          Stack() {
            Image(CounterResource.BUTTON_SUB_ICON)
              .direction(this.counterDirection)
              .width(CounterResource.COUNTER_COMPACT_BUTTON_ICON_SIZE)
              .height(CounterResource.COUNTER_COMPACT_BUTTON_ICON_SIZE)
              .fillColor(CounterResource.BUTTON_ICON_COLOR)
              .opacity(this.subOpacity)
            Button({ type: ButtonType.Circle, stateEffect: this.subBtnStateEffect } as ButtonOptions)
              .accessibilityText($r('sys.string.reduce_used_for_accessibility_text'))
              .accessibilityDescription(this.value === this.min ? '' : this.getReduceStr())
              .accessibilityFocusDrawLevel(FocusDrawLevel.TOP)
              .direction(this.counterDirection)
              .width(CounterResource.COUNTER_COMPACT_BUTTON_SIZE)
              .height(CounterResource.COUNTER_COMPACT_BUTTON_SIZE)
              .backgroundColor(CounterResource.BUTTON_BACKGROUD_COLOR)
              .opacity(this.subOpacity)
              .enabled(this.subBtnEnabled)
              .key('CompactSubButton' + String(this.timeStamp))
              .onKeyEvent((event: KeyEvent) => {
                this.subBtnFocusWidth = CounterResource.BUTTON_BORDER_FOCUSED_WIDTH
                if (event.keyCode === CounterConstant.KEYCODE_ESC) {
                  this.resetFocusButton();
                  event.stopPropagation();
                  return true;
                }
                if (event.type === KeyType.Down &&
                  event.keyCode === CounterConstant.KEYCODE_MOVE_HOME) {
                  event.stopPropagation();
                  this.homeFirstValue();
                  this.focusWithTarget('CompactAddButton' + String(this.timeStamp));
                  return true;
                }
                if (event.type === KeyType.Down &&
                  event.keyCode === CounterConstant.KEYCODE_MOVE_END) {
                  event.stopPropagation();
                  this.endLastValue();
                  if (this.addBtnStateEffect) {
                    this.addBtnStateEffect = false;
                    this.addOpacity = CounterResource.COUNTER_BUTTON_DISABLE_OPACITY;
                    this.addBtnEnabled = false;
                  }
                  this.focusWithTarget('CompactSubButton' + String(this.timeStamp));
                  return true;
                }
                return false;
              })
              .onClick((event: ClickEvent) => {
                this.subValue();
                this.onChange?.(this.value);
                if (event.source === SourceType.Mouse ||
                  event.source === SourceType.TouchScreen) {
                  this.subBtnFocusWidth = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                }
                try {
                  const context: common.Context = this.getUIContext().getHostContext() as common.Context;
                  const bundleName = (context as common.UIAbilityContext).abilityInfo.bundleName;
                  let eventInfo: accessibility.EventInfo = new accessibility.EventInfo(
                    'announceForAccessibility',
                    bundleName,
                    'click',
                  );
                  accessibility.sendAccessibilityEvent(eventInfo).then(() => {
                    console.log('Accessibility subValue click send event');
                  })
                } catch (exception) {
                  let code: number = (exception as BusinessError).code;
                  let message: string = (exception as BusinessError).message;
                  console.log(`Accessibility subValue click longPress failed error code:${code} message:${message}`);
                }
              })
              .gesture(
                LongPressGesture({ repeat: true })
                  .onAction((event: GestureEvent) => {
                    if (event.repeat) {
                      this.subValue();
                      this.onChange?.(this.value);
                    }
                    if (event.source === SourceType.Mouse ||
                      event.source === SourceType.TouchScreen) {
                      this.subBtnFocusWidth = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                    }
                  })
                  .onActionEnd(() => {
                    try {
                      const context: common.Context = this.getUIContext().getHostContext() as common.Context;
                      const bundleName = (context as common.UIAbilityContext).abilityInfo.bundleName;
                      let eventInfo: accessibility.EventInfo = new accessibility.EventInfo(
                        'announceForAccessibility',
                        bundleName,
                        'common',
                      );
                      accessibility.sendAccessibilityEvent(eventInfo).then(() => {
                        console.log('Accessibility subValue longPress send event');
                      })
                    } catch (exception) {
                      let code: number = (exception as BusinessError).code;
                      let message: string = (exception as BusinessError).message;
                      console.log(`Accessibility subValue longPress longPress failed error code:${code} message:${message}`);
                    }
                  })
              )
              .hoverEffect(this.choverEffect)
              .onHover((isHover: boolean, event: HoverEvent) => {
                this.onHoverDecrease?.(isHover);
              })
              .focusable(this.focusEnable)
              .groupDefaultFocus(true)
              .onFocus(() => {
                this.subBtnFocusWidth = CounterResource.BUTTON_BORDER_FOCUSED_WIDTH;
                this.onFocusDecrease?.();
                this.updateButtonStatus();
              })
              .onBlur(() => {
                this.subBtnFocusWidth = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                this.onBlurDecrease?.();
              })
          }
          .width(CounterResource.COUNTER_COMPACT_BUTTON_SIZE)
          .height(CounterResource.COUNTER_COMPACT_BUTTON_SIZE)
          .borderRadius(CounterResource.COUNTER_COMPACT_BUTTON_RADIUS)
          .borderWidth(this.subBtnFocusWidth)
          .borderColor(CounterResource.BUTTON_BORDER_FOCUSED_COLOR)
          .margin({
            start: LengthMetrics.vp(this.resourceToVp(CounterResource.COUNTER_COMPACT_BUTTON_CONTAINER_MARGIN))
          } as LocalizedMargin)
          .clip(true)

          if (this.hasTextWidth) {
            Text(String(this.value))
              .accessibilityText(this.getAccessibilityResource(this.numberStyleOptions.label) + '[n2]' +
              String(this.value) + '[n0]')
              .textAlign(TextAlign.Center)
              .fontSize(CounterResource.COUNTER_NUMBER_SIZE)
              .maxFontScale(CounterResource.COUNTER_NUMBER_MAX_FONT_SIZE_SCALE)
              .fontColor(CounterResource.COUNTER_TEXT_COLOR)
              .width(String(this.textWidth))
              .margin({
                start: LengthMetrics.vp(CounterResource.COUNTER_COMPACT_BUTTON_TEXT_MARGIN),
                end: LengthMetrics.vp(CounterResource.COUNTER_COMPACT_BUTTON_TEXT_MARGIN)
              } as LocalizedMargin)
          } else {
            Text(String(this.value))
              .accessibilityText(this.getAccessibilityResource(this.numberStyleOptions.label) + '[n2]' +
              String(this.value) + '[n0]')
              .direction(this.counterDirection)
              .textAlign(TextAlign.Center)
              .fontSize(CounterResource.COUNTER_NUMBER_SIZE)
              .maxFontScale(CounterResource.COUNTER_NUMBER_MAX_FONT_SIZE_SCALE)
              .fontColor(CounterResource.COUNTER_TEXT_COLOR)
              .margin({
                start: LengthMetrics.vp(CounterResource.COUNTER_COMPACT_BUTTON_TEXT_MARGIN),
                end: LengthMetrics.vp(CounterResource.COUNTER_COMPACT_BUTTON_TEXT_MARGIN)
              } as LocalizedMargin)
          }

          Stack() {
            Image(CounterResource.BUTTON_ADD_ICON)
              .direction(this.counterDirection)
              .width(CounterResource.COUNTER_COMPACT_BUTTON_ICON_SIZE)
              .height(CounterResource.COUNTER_COMPACT_BUTTON_ICON_SIZE)
              .fillColor(CounterResource.BUTTON_ICON_COLOR)
              .opacity(this.addOpacity)
            Button({ type: ButtonType.Circle, stateEffect: this.addBtnStateEffect } as ButtonOptions)
              .accessibilityText($r('sys.string.increase_used_for_accessibility_text'))
              .accessibilityDescription(this.value === this.max ? '' : this.getIncreaseStr())
              .accessibilityFocusDrawLevel(FocusDrawLevel.TOP)
              .direction(this.counterDirection)
              .width(CounterResource.COUNTER_COMPACT_BUTTON_SIZE)
              .height(CounterResource.COUNTER_COMPACT_BUTTON_SIZE)
              .backgroundColor(CounterResource.BUTTON_BACKGROUD_COLOR)
              .opacity(this.addOpacity)
              .enabled(this.addBtnEnabled)
              .key('CompactAddButton' + String(this.timeStamp))
              .onKeyEvent((event: KeyEvent) => {
                this.addBtnFocusWidth = CounterResource.BUTTON_BORDER_FOCUSED_WIDTH
                if (event.keyCode === CounterConstant.KEYCODE_ESC) {
                  this.resetFocusButton();
                  event.stopPropagation();
                  return true;
                }
                if (event.type === KeyType.Down &&
                  event.keyCode === CounterConstant.KEYCODE_MOVE_HOME) {
                  event.stopPropagation();
                  this.homeFirstValue();
                  if (this.subBtnStateEffect) {
                    this.subBtnStateEffect = false;
                    this.subOpacity = CounterResource.COUNTER_BUTTON_DISABLE_OPACITY;
                    this.subBtnEnabled = false;
                  }
                  this.focusWithTarget('CompactAddButton' + String(this.timeStamp));
                  return true;
                }
                if (event.type === KeyType.Down &&
                  event.keyCode === CounterConstant.KEYCODE_MOVE_END) {
                  event.stopPropagation();
                  this.endLastValue();
                  this.focusWithTarget('CompactSubButton' + String(this.timeStamp));
                  return true;
                }
                return false;
              })
              .onClick((event: ClickEvent) => {
                this.addValue();
                this.onChange?.(this.value);
                if (event.source === SourceType.Mouse ||
                  event.source === SourceType.TouchScreen) {
                  this.addBtnFocusWidth = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                }
                try {
                  const context: common.Context = this.getUIContext().getHostContext() as common.Context;
                  const bundleName = (context as common.UIAbilityContext).abilityInfo.bundleName;
                  let eventInfo: accessibility.EventInfo = new accessibility.EventInfo(
                    'announceForAccessibility',
                    bundleName,
                    'click',
                  );
                  accessibility.sendAccessibilityEvent(eventInfo).then(() => {
                    console.log('Accessibility addValue click send event');
                  })
                } catch (exception) {
                  let code: number = (exception as BusinessError).code;
                  let message: string = (exception as BusinessError).message;
                  console.log(`Accessibility addValue click longPress failed error code:${code} message:${message}`);
                }
              })
              .gesture(
                LongPressGesture({ repeat: true })
                  .onAction((event: GestureEvent) => {
                    if (event.repeat) {
                      this.addValue();
                      this.onChange?.(this.value);
                    }
                    if (event.source === SourceType.Mouse ||
                      event.source === SourceType.TouchScreen) {
                      this.addBtnFocusWidth = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                    }
                  })
                  .onActionEnd(() => {
                    try {
                      const context: common.Context = this.getUIContext().getHostContext() as common.Context;
                      const bundleName = (context as common.UIAbilityContext).abilityInfo.bundleName;
                      let eventInfo: accessibility.EventInfo = new accessibility.EventInfo(
                        'announceForAccessibility',
                        bundleName,
                        'common',
                      );
                      accessibility.sendAccessibilityEvent(eventInfo).then(() => {
                        console.log('Accessibility addValue longPress send event');
                      })
                    } catch (exception) {
                      let code: number = (exception as BusinessError).code;
                      let message: string = (exception as BusinessError).message;
                      console.log(`Accessibility addValue longPress longPress failed error code:${code} message:${message}`);
                    }
                  })
              )
              .hoverEffect(this.choverEffect)
              .onHover((isHover: boolean, event: HoverEvent) => {
                this.onHoverIncrease?.(isHover);
              })
              .focusable(this.focusEnable)
              .onFocus(() => {
                this.addBtnFocusWidth = CounterResource.BUTTON_BORDER_FOCUSED_WIDTH;
                this.onFocusIncrease?.();
                this.updateButtonStatus();
              })
              .onBlur(() => {
                this.addBtnFocusWidth = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                this.onBlurIncrease?.();
              })
          }
          .direction(this.counterDirection)
          .width(CounterResource.COUNTER_COMPACT_BUTTON_SIZE)
          .height(CounterResource.COUNTER_COMPACT_BUTTON_SIZE)
          .borderRadius(CounterResource.COUNTER_COMPACT_BUTTON_RADIUS)
          .borderWidth(this.addBtnFocusWidth)
          .borderColor(CounterResource.BUTTON_BORDER_FOCUSED_COLOR)
          .margin({
            end: LengthMetrics.vp(this.resourceToVp(CounterResource.COUNTER_COMPACT_BUTTON_CONTAINER_MARGIN))
          } as LocalizedMargin)
          .clip(true)
        }
        .direction(this.counterDirection)
        .tabIndex(0)
        .height(CounterResource.COUNTER_COMPACT_CONTAINER_HEIGHT)
        .align(Alignment.Center)
        .borderWidth(CounterResource.COUNTER_BORDER_WIDTH)
        .borderColor(CounterResource.COUNTER_BORDER_COLOR)
        .borderRadius(CounterResource.COUNTER_COMPACT_CONTAINER_RADIUS)

        Text(this.numberStyleOptions.label)
          .direction(this.counterDirection)
          .margin({ top: LengthMetrics.vp(CounterResource.COUNTER_COMPACT_CONTAINER_LABEL_DISTANCE) } as LocalizedMargin)
          .fontSize(CounterResource.COUNTER_COMPACT_LABEL_SIZE)
          .maxFontScale(CounterResource.COUNTER_LABEL_MAX_FONT_SIZE_SCALE)
          .fontColor(CounterResource.COUNTER_TEXT_COLOR)
          .align(Alignment.Top)
      }
    } else if (this.type === CounterType.INLINE) {
      Row() {
        if (this.hasTextWidth) {
          RelativeContainer() {
            TextInput({
              text: this.hasInputText1 ? this.inputValue : String(this.value),
              controller: this.controller1
            })
              .accessibilityDescription($r('sys.string.input_counter_double_click_description'))
              .alignRules({
                center: { anchor: '__container__', align: VerticalAlign.Center } as LocalizedVerticalAlignParam,
                middle: { anchor: '__container__', align: HorizontalAlign.Center } as LocalizedHorizontalAlignParam
              } as LocalizedAlignRuleOptions)
              .width(Math.min(this.getValueLength() * 9.6, this.textWidth))
              .height('20vp')
              .padding(0)
              .borderRadius(0)
              .textAlign(TextAlign.Center)
              .type(InputType.PhoneNumber)
              .copyOption(CopyOptions.None)
              .fontSize(this.getTextInputFontSize())
              .fontWeight(FontWeight.Medium)
              .fontColor(this.hasFocusText1 ? Color.White : CounterResource.COUNTER_TEXT_COLOR)
              .maxLength(this.getMaxLength())
              .backgroundColor(this.hasFocusText1 ? CounterResource.BUTTON_BORDER_FOCUSED_COLOR : Color.Transparent)
              .key('InlineTextInput' + String(this.timeStamp))
              .onKeyEvent((event: KeyEvent) => {
                this.focusCurrentText(FocusText.TEXT1)
                if (event.keyCode === CounterConstant.KEYCODE_ESC) {
                  this.resetFocusText();
                  event.stopPropagation();
                  return true;
                }
                if (event.type === KeyType.Down &&
                  event.keyCode === CounterConstant.KEYCODE_DPAD_UP) {
                  this.addValue();
                  event.stopPropagation();
                  return true;
                }
                if (event.type === KeyType.Down &&
                  event.keyCode === CounterConstant.KEYCODE_MOVE_HOME) {
                  event.stopPropagation();
                  this.focusWithTarget('InlineTextInput' + String(this.timeStamp));
                  return true;
                }
                if (event.type === KeyType.Down &&
                  event.keyCode === CounterConstant.KEYCODE_MOVE_END) {
                  event.stopPropagation();
                  this.focusWithTarget('InlineTextInput' + String(this.timeStamp));
                  return true;
                }
                if (event.type === KeyType.Down &&
                  event.keyCode === CounterConstant.KEYCODE_DPAD_DOWN) {
                  this.subValue();
                  event.stopPropagation();
                  return true;
                }
                if (event.type === KeyType.Down &&
                  event.keyCode === CounterConstant.KEYCODE_DPAD_LEFT) {
                  this.focusWithTarget('InlineTextInput' + String(this.timeStamp));
                  event.stopPropagation();
                  return true;
                }
                if (event.type === KeyType.Down &&
                  event.keyCode === CounterConstant.KEYCODE_DPAD_RIGHT) {
                  this.focusWithTarget('InlineTextInput' + String(this.timeStamp));
                  event.stopPropagation();
                  return true;
                }
                return false;
              })
              .onChange((value: string) => {
                this.inputValue = value;
                for (let i = 0; i < value.length; i++) {
                  let c: string = value[i];
                  if (c === '+' || c === '*' || c === '#') {
                    this.value -= 1;
                    this.value += 1;
                    this.inputValue = String(this.value);
                    return;
                  }
                  if (c === '-' && i !== 0) {
                    this.inputValue = c;
                    break;
                  }
                }

                this.hasInputText1 = true;
                let c: string = '';
                if (value.length > 0) {
                  c = value[value.length - 1];
                }
                if (value.length === this.getMaxLength()) {
                  this.inputValue = c;
                }
                if (this.timeoutID1 !== -1) {
                  clearTimeout(this.timeoutID1);
                  this.timeoutID1 = -1;
                }
                const inputValueToInt: int = Double.toInt(Number.parseInt(this.inputValue));
                if (this.inputValue !== '' && inputValueToInt <= this.max &&
                  inputValueToInt >= this.min) {
                  this.value = inputValueToInt;
                  this.onChange?.(this.value);
                  this.hasInputText1 = false;
                } else {
                  if (inputValueToInt > this.max ||
                    (inputValueToInt < this.min &&
                      this.inputValue.length <= String(this.min).length)) {
                    this.inputValue = c;
                  }
                  if (value.length < this.getMaxLength()) {
                    this.timeoutID1 = setTimeout(() => {
                      const inputValueInTimer: int = Double.toInt(Number.parseInt(this.inputValue));
                      if (this.inputValue !== '' && inputValueInTimer <= this.max &&
                        inputValueInTimer >= this.min) {
                        this.value = inputValueInTimer;
                        this.onChange?.(this.value);
                      }
                      this.inputValue = String(this.value);
                      this.hasInputText1 = false;
                      this.updateInlineEnableSate();
                    }, 1500);
                  }
                }
                this.updateInlineEnableSate();
              } as EditableTextOnChangeCallback)
              .onSubmit((enterKey: EnterKeyType) => {
                if (this.timeoutID1 != -1) {
                  clearTimeout(this.timeoutID1);
                  this.timeoutID1 = -1;
                }
                this.hasInputText1 = false;
                this.value -= 1;
                const inputValueToInt: int = Double.toInt(Number.parseInt(this.inputValue));
                if (inputValueToInt >= this.min && inputValueToInt <= this.max) {
                  this.value = inputValueToInt;
                  this.onChange?.(this.value);
                  this.updateInlineEnableSate();
                } else {
                  this.value += 1;
                  this.inputValue = String(this.value);
                }
              } as OnSubmitCallback)
              .focusable(true)
              .focusOnTouch(true)
              .onFocus(() => {
                this.focusText = FocusText.TEXT1;
                this.hasFocusText1 = true;
                this.controller1.caretPosition(String(this.value).length);
              })
              .onBlur(() => {
                this.focusText = FocusText.NONE;
                this.hasFocusText1 = false;
              })
              .onClick((event: ClickEvent) => {
                this.focusText = FocusText.TEXT1;
                this.hasFocusText1 = true;
                this.focusWithTarget('InlineTextInput' + String(this.timeStamp));
                this.controller1.caretPosition(String(this.value).length);
              })
          }
          .direction(this.counterDirection)
          .margin({
            start: LengthMetrics.vp(CounterResource.COUNTER_INLINE_INPUT_TEXT_MARGIN),
            end: LengthMetrics.vp(CounterResource.COUNTER_INLINE_INPUT_TEXT_MARGIN)
          } as LocalizedMargin)
          .height('100%')
          .width(this.textWidth)
        } else {
          Row() {
            TextInput({
              text: this.hasInputText1 ? this.inputValue : String(this.value),
              controller: this.controller1
            })
              .accessibilityDescription($r('sys.string.input_counter_double_click_description'))
              .direction(this.counterDirection)
              .width(this.getValueLength() * 9.6)
              .height('20vp')
              .padding(0)
              .borderRadius(0)
              .textAlign(TextAlign.Center)
              .type(InputType.PhoneNumber)
              .copyOption(CopyOptions.None)
              .fontSize(this.getTextInputFontSize())
              .fontWeight(FontWeight.Medium)
              .fontColor(this.hasFocusText1 ? Color.White : CounterResource.COUNTER_TEXT_COLOR)
              .maxLength(this.getMaxLength())
              .backgroundColor(this.hasFocusText1 ? CounterResource.BUTTON_BORDER_FOCUSED_COLOR : Color.Transparent)
              .key('InlineTextInput' + String(this.timeStamp))
              .onKeyEvent((event: KeyEvent) => {
                this.focusCurrentText(FocusText.TEXT1)
                if (event.keyCode === CounterConstant.KEYCODE_ESC) {
                  this.resetFocusText();
                  event.stopPropagation();
                  return true;
                }
                if (event.type === KeyType.Down &&
                  event.keyCode === CounterConstant.KEYCODE_DPAD_UP) {
                  this.addValue();
                  event.stopPropagation();
                  return true;
                }
                if (event.type === KeyType.Down &&
                  event.keyCode === CounterConstant.KEYCODE_DPAD_DOWN) {
                  this.subValue();
                  event.stopPropagation();
                  return true;
                }
                if (event.type === KeyType.Down &&
                  event.keyCode === CounterConstant.KEYCODE_DPAD_LEFT) {
                  this.focusWithTarget('InlineTextInput' + String(this.timeStamp));
                  event.stopPropagation();
                  return true;
                }
                if (event.type === KeyType.Down &&
                  event.keyCode === CounterConstant.KEYCODE_DPAD_RIGHT) {
                  this.focusWithTarget('InlineTextInput' + String(this.timeStamp));
                  event.stopPropagation();
                  return true;
                }
                return false;
              })
              .onChange((value: string) => {
                this.inputValue = value;
                for (let i = 0; i < value.length; i++) {
                  let c: string = value[i];
                  if (c === '+' || c === '*' || c === '#') {
                    this.value -= 1;
                    this.value += 1;
                    this.inputValue = String(this.value);
                    return;
                  }
                  if (c === '-' && i !== 0) {
                    this.inputValue = c;
                    break;
                  }
                }
                this.hasInputText1 = true;
                let c: string = '';
                if (value.length > 0) {
                  c = value[value.length - 1];
                }
                if (value.length === this.getMaxLength()) {
                  this.inputValue = c;
                }
                if (this.timeoutID1 !== -1) {
                  clearTimeout(this.timeoutID1);
                  this.timeoutID1 = -1;
                }
                const inputValueToInt: int = Double.toInt(Number.parseInt(this.inputValue));
                if (this.inputValue !== '' && inputValueToInt <= this.max &&
                  inputValueToInt >= this.min) {
                  this.value = inputValueToInt;
                  this.onChange?.(this.value);
                  this.hasInputText1 = false;
                } else {
                  if (inputValueToInt > this.max ||
                    (inputValueToInt < this.min &&
                      this.inputValue.length <= String(this.min).length)) {
                    this.inputValue = c;
                  }
                  if (value.length < this.getMaxLength()) {
                    this.timeoutID1 = setTimeout(() => {
                      const inputValueInTimer: int = Double.toInt(Number.parseInt(this.inputValue));
                      if (this.inputValue !== '' && inputValueInTimer <= this.max &&
                        inputValueInTimer >= this.min) {
                        this.value = inputValueInTimer;
                        this.onChange?.(this.value);
                      }
                      this.inputValue = String(this.value)
                      this.hasInputText1 = false;
                      this.updateInlineEnableSate();
                    }, 1500);
                  }
                }
                this.updateInlineEnableSate();
              })
              .onSubmit((enterKey: EnterKeyType) => {
                if (this.timeoutID1 !== -1) {
                  clearTimeout(this.timeoutID1);
                  this.timeoutID1 = -1;
                }
                this.hasInputText1 = false;
                this.value -= 1;
                const inputValueToInt: int = Double.toInt(Number.parseInt(this.inputValue));
                if (inputValueToInt >= this.min && inputValueToInt <= this.max) {
                  this.value = inputValueToInt;
                  this.onChange?.(this.value);
                  this.updateInlineEnableSate();
                } else {
                  this.value += 1;
                  this.inputValue = String(this.value);
                }
              } as OnSubmitCallback)
              .focusable(true)
              .focusOnTouch(true)
              .onFocus(() => {
                this.focusText = FocusText.TEXT1;
                this.hasFocusText1 = true;
                this.controller1.caretPosition(String(this.value).length);
              })
              .onBlur(() => {
                this.focusText = FocusText.NONE;
                this.hasFocusText1 = false;
              })
              .onClick((event: ClickEvent) => {
                this.focusText = FocusText.TEXT1;
                this.hasFocusText1 = true;
                this.focusWithTarget('InlineTextInput' + String(this.timeStamp));
                this.controller1.caretPosition(String(this.value).length);
              })
          }
          .direction(this.counterDirection)
          .margin({
            start: LengthMetrics.vp(CounterResource.COUNTER_INLINE_INPUT_TEXT_MARGIN),
            end: LengthMetrics.vp(CounterResource.COUNTER_INLINE_INPUT_TEXT_MARGIN)
          } as LocalizedMargin)
        }

        Column() {
          Stack() {
            Rect()
              .direction(this.counterDirection)
              .width(CounterResource.COUNTER_INLINE_FOCUS_BORDER_WIDTH)
              .height(CounterResource.COUNTER_INLINE_FOCUS_BORDER_HEIGHT)
              .radius([
                ['0vp', '0vp'],
                [CounterResource.COUNTER_INLINE_RADIUS, CounterResource.COUNTER_INLINE_RADIUS],
                ['0vp', '0vp'],
                ['0vp', '0vp']])
              .strokeWidth(this.addBtnFocusWidth)
              .stroke(CounterResource.BUTTON_BORDER_FOCUSED_COLOR)
              .margin({ end: LengthMetrics.vp(2) } as LocalizedMargin)
              .fillOpacity(0)
            Image(CounterResource.BUTTON_ARROW_UP)
              .direction(this.counterDirection)
              .width(CounterResource.COUNTER_INLINE_BUTTON_ICON_WIDTH)
              .height(CounterResource.COUNTER_INLINE_BUTTON_ICON_HEIGHT)
              .fillColor(CounterResource.BUTTON_ICON_COLOR)
              .opacity(this.addOpacity)

            Button({ type: ButtonType.Normal, stateEffect: this.addBtnStateEffect } as ButtonOptions)
              .accessibilityText($r('sys.string.increase_used_for_accessibility_text'))
              .accessibilityDescription(this.value === this.max ? '' : this.getIncreaseStr())
              .direction(this.counterDirection)
              .width(CounterResource.COUNTER_INLINE_BUTTON_WIDTH)
              .height(CounterResource.COUNTER_INLINE_BUTTON_HEIGHT)
              .backgroundColor(Color.Transparent)
              .opacity(this.addOpacity)
              .enabled(this.addBtnEnabled)
              .onClick((event: ClickEvent) => {
                this.addValue();
                if (event.source === SourceType.Mouse ||
                  event.source === SourceType.TouchScreen) {
                  this.addBtnFocusWidth = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                }
                try {
                  const context: common.Context = this.getUIContext().getHostContext() as common.Context;
                  const bundleName = (context as common.UIAbilityContext).abilityInfo.bundleName;
                  let eventInfo: accessibility.EventInfo = new accessibility.EventInfo(
                    'announceForAccessibility',
                    bundleName,
                    'click',
                  );
                  accessibility.sendAccessibilityEvent(eventInfo).then(() => {
                    console.log('Accessibility addValue click send event');
                  })
                } catch (exception) {
                  let code: number = (exception as BusinessError).code;
                  let message: string = (exception as BusinessError).message;
                  console.log(`Accessibility addValue click longPress failed error code:${code} message:${message}`);
                }
              })
              .gesture(
                LongPressGesture({ repeat: true })
                  .onAction((event: GestureEvent) => {
                    if (event.repeat) {
                      this.addValue();
                    }
                    this.addBtnFocusWidth = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                  })
                  .onActionEnd(() => {
                    try {
                      const context: common.Context = this.getUIContext().getHostContext() as common.Context;
                      const bundleName = (context as common.UIAbilityContext).abilityInfo.bundleName;
                      let eventInfo: accessibility.EventInfo = new accessibility.EventInfo(
                        'announceForAccessibility',
                        bundleName,
                        'common',
                      );
                      accessibility.sendAccessibilityEvent(eventInfo).then(() => {
                        console.log('Accessibility addValue longPress send event');
                      })
                    } catch (exception) {
                      let code: number = (exception as BusinessError).code;
                      let message: string = (exception as BusinessError).message;
                      console.log(`Accessibility addValue longPress failed error code:${code} message:${message}`);
                    }
                  })
              )
              .hoverEffect(this.choverEffect)
              .onHover((isHover: boolean, event: HoverEvent) => {
                this.onHoverIncrease?.(isHover);
              })
              .focusable(false)
              .onFocus(() => {
                this.addBtnFocusWidth = CounterResource.BUTTON_BORDER_FOCUSED_WIDTH;
                this.onFocusIncrease?.();
              })
              .onBlur(() => {
                this.addBtnFocusWidth = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                this.onBlurIncrease?.();
              })
          }
          .direction(this.counterDirection)
          .width(CounterResource.COUNTER_INLINE_BUTTON_WIDTH)
          .height(CounterResource.COUNTER_INLINE_BUTTON_HEIGHT)
          .padding({ top: '1vp' } as Padding)
          .borderWidth({ bottom: '1vp' } as EdgeWidths)
          .borderColor(CounterResource.COUNTER_BORDER_COLOR)
          .clip(true)

          Stack() {
            Rect()
              .direction(this.counterDirection)
              .width(CounterResource.COUNTER_INLINE_FOCUS_BORDER_WIDTH)
              .height(CounterResource.COUNTER_INLINE_FOCUS_BORDER_HEIGHT)
              .radius([
                ['0vp', '0vp'],
                ['0vp', '0vp'],
                [CounterResource.COUNTER_INLINE_RADIUS, CounterResource.COUNTER_INLINE_RADIUS],
                ['0vp', '0vp']
              ])
              .strokeWidth(this.subBtnFocusWidth)
              .stroke(CounterResource.BUTTON_BORDER_FOCUSED_COLOR)
              .margin({ top: LengthMetrics.vp(1), end: LengthMetrics.vp(1), bottom: LengthMetrics.vp(2) } as LocalizedMargin)
              .fillOpacity(0)
            Image(CounterResource.BUTTON_ARROW_DOWN)
              .direction(this.counterDirection)
              .width(CounterResource.COUNTER_INLINE_BUTTON_ICON_WIDTH)
              .height(CounterResource.COUNTER_INLINE_BUTTON_ICON_HEIGHT)
              .fillColor(CounterResource.BUTTON_ICON_COLOR)
              .opacity(this.subOpacity)
            Button({ type: ButtonType.Normal, stateEffect: this.subBtnStateEffect } as ButtonOptions)
              .accessibilityText($r('sys.string.reduce_used_for_accessibility_text'))
              .accessibilityDescription(this.value === this.min ? '' : this.getReduceStr())
              .direction(this.counterDirection)
              .width(CounterResource.COUNTER_INLINE_BUTTON_WIDTH)
              .height(CounterResource.COUNTER_INLINE_BUTTON_HEIGHT)
              .backgroundColor(Color.Transparent)
              .opacity(this.subOpacity)
              .enabled(this.subBtnEnabled)
              .onClick((event: ClickEvent) => {
                this.subValue();
                if (event.source === SourceType.Mouse ||
                  event.source === SourceType.TouchScreen) {
                  this.subBtnFocusWidth = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                }
                try {
                  const context: common.Context = this.getUIContext().getHostContext() as common.Context;
                  const bundleName = (context as common.UIAbilityContext).abilityInfo.bundleName;
                  let eventInfo: accessibility.EventInfo = new accessibility.EventInfo(
                    'announceForAccessibility',
                    bundleName,
                    'click',
                  );
                  accessibility.sendAccessibilityEvent(eventInfo).then(() => {
                    console.log('Accessibility subValue click send event');
                  })
                } catch (exception) {
                  let code: number = (exception as BusinessError).code;
                  let message: string = (exception as BusinessError).message;
                  console.log(`Accessibility subValue click failed error code:${code} message:${message}`);
                }
              })
              .gesture(
                LongPressGesture({ repeat: true })
                  .onAction((event: GestureEvent) => {
                    if (event.repeat) {
                      this.subValue();
                    }
                    this.subBtnFocusWidth = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                  })
                  .onActionEnd(() => {
                    try {
                      const context: common.Context = this.getUIContext().getHostContext() as common.Context;
                      const bundleName = (context as common.UIAbilityContext).abilityInfo.bundleName;
                      let eventInfo: accessibility.EventInfo = new accessibility.EventInfo(
                        'announceForAccessibility',
                        bundleName,
                        'common',
                      );
                      accessibility.sendAccessibilityEvent(eventInfo).then(() => {
                        console.log('Accessibility subValue longPress send event');
                      })
                    } catch (exception) {
                      let code: number = (exception as BusinessError).code;
                      let message: string = (exception as BusinessError).message;
                      console.log(`Accessibility subValue longPress failed error code:${code} message:${message}`);
                    }
                  })
              )
              .hoverEffect(this.choverEffect)
              .onHover((isHover: boolean, event: HoverEvent) => {
                this.onHoverDecrease?.(isHover);
              })
              .focusable(false)
              .onFocus(() => {
                this.subBtnFocusWidth = CounterResource.BUTTON_BORDER_FOCUSED_WIDTH;
                this.onFocusDecrease?.();
              })
              .onBlur(() => {
                this.subBtnFocusWidth = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                this.onBlurDecrease?.();
              })
          }
          .direction(this.counterDirection)
          .width(CounterResource.COUNTER_INLINE_BUTTON_WIDTH)
          .height(CounterResource.COUNTER_INLINE_BUTTON_HEIGHT)
          .clip(true)
        }
        .direction(this.counterDirection)
        .width(CounterResource.COUNTER_INLINE_BUTTON_WIDTH)
        .height(CounterResource.COUNTER_INLINE_CONTAINER_HEIGHT)
        .borderWidth({ start: LengthMetrics.vp(CounterResource.COUNTER_BORDER_WIDTH_NUMBER) } as LocalizedEdgeWidths)
        .borderColor(CounterResource.COUNTER_BORDER_COLOR)
      }
      .direction(this.counterDirection)
      .height(CounterResource.COUNTER_INLINE_CONTAINER_HEIGHT)
      .borderWidth(CounterResource.COUNTER_BORDER_WIDTH)
      .borderColor(CounterResource.COUNTER_BORDER_COLOR)
      .borderRadius(CounterResource.COUNTER_INLINE_RADIUS)
      .clip(true)
    } else if (this.type === CounterType.INLINE_DATE) {
      Row() {
        Row() {
          TextInput({
            text: this.hasInputText1 ? String(this.inputYear) : this.getYear(),
            controller: this.controller1
          })
            .accessibilityText(this.getDateYear(this.year))
            .accessibilityDescription($r('sys.string.input_counter_double_click_description'))
            .direction(this.counterDirection)
            .type(InputType.NUMBER)
            .copyOption(CopyOptions.None)
            .fontSize(this.getTextInputFontSize())
            .fontWeight(FontWeight.Medium)
            .fontColor(this.hasFocusText1 ? Color.White : CounterResource.COUNTER_TEXT_COLOR)
            .maxLength(5)
            .padding(0)
            .backgroundColor(this.hasFocusText1 ? CounterResource.BUTTON_BORDER_FOCUSED_COLOR : Color.Transparent)
            .width('38vp')
            .height('20vp')
            .borderRadius(0)
            .borderWidth(0)
            .key('DateTextInput1' + String(this.timeStamp))
            .onKeyEvent((event: KeyEvent) => {
              this.focusCurrentText(FocusText.TEXT1);
              if (event.keyCode === CounterConstant.KEYCODE_ESC) {
                this.resetFocusText();
                event.stopPropagation();
                return true;
              }
              if (event.type === KeyType.Down &&
                event.keyCode === CounterConstant.KEYCODE_DPAD_UP) {
                this.addDate();
                event.stopPropagation();
                return true;
              }
              if (event.type === KeyType.Down &&
                event.keyCode === CounterConstant.KEYCODE_DPAD_DOWN) {
                this.subDate();
                event.stopPropagation();
                return true;
              }
              if (event.type === KeyType.Down &&
                event.keyCode === CounterConstant.KEYCODE_MOVE_HOME) {
                this.homeFocusText();
                event.stopPropagation();
                return true;
              }
              if (event.type === KeyType.Down &&
                event.keyCode === CounterConstant.KEYCODE_MOVE_END) {
                this.endFocusText();
                event.stopPropagation();
                return true;
              }
              if (event.type === KeyType.Down &&
                event.keyCode === CounterConstant.KEYCODE_DPAD_LEFT) {
                this.focusWithTarget('DateTextInput1' + String(this.timeStamp));
                event.stopPropagation();
                return true;
              }
              if (event.type === KeyType.Down &&
                event.keyCode === CounterConstant.KEYCODE_DPAD_RIGHT) {
                this.focusWithTarget('DateTextInput2' + String(this.timeStamp));
                return true;
              }
              return false;
            })
            .onChange((value: string) => {
              if (value.length !== 4) {
                this.hasInputText1 = true;
              }
              this.inputYear = parseInt(value).toInt();
              if (value.length === 5) {
                this.inputYear = this.inputYear % 10;
              }

              if (this.timeoutID1 !== -1) {
                clearTimeout(this.timeoutID1);
                this.timeoutID1 = -1;
              }

              this.timeoutID1 = setTimeout(() => {
                this.hasInputText1 = false;
                this.inputYear = this.year;
                this.updateDateEnableSate();
                this.updateDay();
              }, 1500);

              if (this.inputYear >= this.minYear && this.inputYear <= this.maxYear) {
                this.year = this.inputYear;
                this.updateDateEnableSate();
                this.updateDay();
              }

              if (value.length === 4) {
                let date = new DateData(this.year, this.month, this.day);
                this.onDateChange?.(date);
              }
            } as EditableTextOnChangeCallback)
            .onSubmit((enterKey: EnterKeyType) => {
              if (this.timeoutID1 !== -1) {
                clearTimeout(this.timeoutID1);
                this.timeoutID1 = -1;
              }
              this.hasInputText1 = false;
              this.year -= 1;
              if (this.inputYear >= this.minYear && this.inputYear <= this.maxYear) {
                this.year = this.inputYear;
              } else {
                this.year += 1;
                this.inputYear = this.year;
              }
              this.updateDateEnableSate();
              this.updateDay();
            } as OnSubmitCallback)
            .tabIndex(0)
            .focusOnTouch(true)
            .focusable(true)
            .onFocus(() => {
              this.focusText = FocusText.TEXT1;
              this.hasFocusText1 = true;
              this.updateDateEnableSate();
              this.controller1.caretPosition(this.getYear().length);
            })
            .onBlur(() => {
              this.focusText = FocusText.NONE;
              this.hasFocusText1 = false;
              this.updateDateEnableSate();
            })
            .onClick((event: ClickEvent) => {
              this.focusText = FocusText.TEXT1;
              this.hasFocusText1 = true;
              this.updateDateEnableSate();
              this.controller1.caretPosition(this.getYear().length);
            })
          Text('/')
            .accessibilityLevel('no')
            .direction(this.counterDirection)
            .textAlign(TextAlign.Center)
            .fontSize(CounterResource.COUNTER_NUMBER_SIZE)
            .maxFontScale(CounterResource.COUNTER_NUMBER_MAX_FONT_SIZE_SCALE)
            .fontColor(CounterResource.COUNTER_TEXT_COLOR)
            .width('8vp')
          TextInput({
            text: this.hasInputText2 ? String(this.inputMoon) : this.convertNumberToString(this.month),
            controller: this.controller2
          })
            .accessibilityText(this.getDateMonth(this.month))
            .accessibilityDescription($r('sys.string.input_counter_double_click_description'))
            .direction(this.counterDirection)
            .type(InputType.NUMBER)
            .copyOption(CopyOptions.None)
            .fontSize(this.getTextInputFontSize())
            .fontWeight(FontWeight.Medium)
            .fontColor(this.hasFocusText2 ? Color.White : CounterResource.COUNTER_TEXT_COLOR)
            .maxLength(3)
            .padding(0)
            .backgroundColor(this.hasFocusText2 ? CounterResource.BUTTON_BORDER_FOCUSED_COLOR : Color.Transparent)
            .width('19vp')
            .height('20vp')
            .borderRadius(0)
            .key('DateTextInput2' + String(this.timeStamp))
            .onKeyEvent((event: KeyEvent) => {
              this.focusCurrentText(FocusText.TEXT2)
              if (event.keyCode === CounterConstant.KEYCODE_ESC) {
                this.resetFocusText();
                event.stopPropagation();
                return true;
              }
              if (event.type === KeyType.Down &&
                event.keyCode === CounterConstant.KEYCODE_DPAD_DOWN) {
                this.subDate();
                this.updateDay();
                event.stopPropagation();
                return true;
              }
              if (event.type === KeyType.Down &&
                event.keyCode === CounterConstant.KEYCODE_DPAD_UP) {
                this.addDate();
                this.updateDay();
                event.stopPropagation();
                return true;
              }
              if (event.type === KeyType.Down &&
                event.keyCode === CounterConstant.KEYCODE_MOVE_HOME) {
                this.homeFocusText();
                event.stopPropagation();
                return true;
              }
              if (event.type === KeyType.Down &&
                event.keyCode === CounterConstant.KEYCODE_MOVE_END) {
                this.endFocusText();
                event.stopPropagation();
                return true;
              }
              if (event.type === KeyType.Down &&
                event.keyCode === CounterConstant.KEYCODE_DPAD_LEFT) {
                this.focusWithTarget('DateTextInput1' + String(this.timeStamp));
                return true;
              }
              if (event.type === KeyType.Down &&
                event.keyCode === CounterConstant.KEYCODE_DPAD_RIGHT) {
                this.focusWithTarget('DateTextInput3' + String(this.timeStamp));
                return true;
              }
              if (event.type === KeyType.Down &&
                event.keyCode === CounterConstant.KEYCODE_TAB) {
                event.stopPropagation();
                this.focusWithTarget('DateTextInput1' + String(this.timeStamp));
                return true;
              }
              return false;
            })
            .onChange((value: string) => {
              this.inputMoon = parseInt(value).toInt();
              if (value.length !== 2) {
                this.hasInputText2 = true;
              }
              if (value.length === 3) {
                this.inputMoon = this.inputMoon % 10;
              }
              if (this.timeoutID2 !== -1) {
                clearTimeout(this.timeoutID2);
                this.timeoutID2 = -1;
              }

              this.timeoutID2 = setTimeout(() => {
                this.hasInputText2 = false;
                this.month -= 1;
                if (this.inputMoon >= 1 && this.inputMoon <= 12) {
                  this.month = this.inputMoon;
                } else {
                  this.month += 1;
                  this.inputMoon = this.month;
                }
                this.updateDay();
              }, 1000);

              if (value.length === 2) {
                this.hasInputText2 = false;
                this.month -= 1;
                if (this.inputMoon >= 1 && this.inputMoon <= 12) {
                  this.month = this.inputMoon;
                  let date = new DateData(this.year, this.month, this.day);
                  this.onDateChange?.(date);
                } else {
                  this.month += 1;
                  this.inputMoon = this.month;
                }
                this.updateDay();
              }
            } as EditableTextOnChangeCallback)
            .onSubmit((enterKey: EnterKeyType) => {
              if (this.timeoutID2 !== -1) {
                clearTimeout(this.timeoutID2);
                this.timeoutID2 = -1;
              }
              this.hasInputText2 = false;
              this.month -= 1;
              if (this.inputMoon >= 1 && this.inputMoon <= 12) {
                this.month = this.inputMoon;
                this.updateDay();
              } else {
                this.month += 1;
              }
            } as OnSubmitCallback)
            .focusOnTouch(true)
            .tabIndex(-1)
            .focusable(true)
            .onFocus(() => {
              this.focusText = FocusText.TEXT2;
              this.hasFocusText2 = true;
              this.controller2.caretPosition(this.convertNumberToString(this.month).length);
            })
            .onBlur(() => {
              this.focusText = FocusText.NONE
              this.hasFocusText2 = false
            })
            .onClick((event: ClickEvent) => {
              this.focusText = FocusText.TEXT2;
              this.hasFocusText2 = true;
              this.controller2.caretPosition(this.convertNumberToString(this.month).length);
            })
          Text('/')
            .accessibilityLevel('no')
            .direction(this.counterDirection)
            .textAlign(TextAlign.Center)
            .fontSize(CounterResource.COUNTER_NUMBER_SIZE)
            .maxFontScale(CounterResource.COUNTER_NUMBER_MAX_FONT_SIZE_SCALE)
            .fontColor(CounterResource.COUNTER_TEXT_COLOR)
            .width('8vp')
          TextInput({
            text: this.hasInputText3 ? String(this.inputDay) : this.convertNumberToString(this.day),
            controller: this.controller3
          })
            .accessibilityText(this.getDateDay(this.day))
            .accessibilityDescription($r('sys.string.input_counter_double_click_description'))
            .direction(this.counterDirection)
            .type(InputType.NUMBER)
            .copyOption(CopyOptions.None)
            .fontSize(this.getTextInputFontSize())
            .fontWeight(FontWeight.Medium)
            .fontColor(this.hasFocusText3 ? Color.White : CounterResource.COUNTER_TEXT_COLOR)
            .maxLength(3)
            .padding(0)
            .backgroundColor(this.hasFocusText3 ? CounterResource.BUTTON_BORDER_FOCUSED_COLOR : Color.Transparent)
            .width('19vp')
            .height('20vp')
            .borderRadius(0)
            .key('DateTextInput3' + String(this.timeStamp))
            .onKeyEvent((event: KeyEvent) => {
              this.focusCurrentText(FocusText.TEXT3)
              if (event.keyCode === CounterConstant.KEYCODE_ESC) {
                this.resetFocusText();
                event.stopPropagation();
                return true;
              }
              if (event.type === KeyType.Down &&
                event.keyCode === CounterConstant.KEYCODE_DPAD_DOWN) {
                this.subDate();
                event.stopPropagation();
                return true;
              }
              if (event.type === KeyType.Down &&
                event.keyCode === CounterConstant.KEYCODE_DPAD_UP) {
                this.addDate();
                event.stopPropagation();
                return true;
              }
              if (event.type === KeyType.Down &&
                event.keyCode === CounterConstant.KEYCODE_MOVE_HOME) {
                this.homeFocusText();
                event.stopPropagation();
                return true;
              }
              if (event.type === KeyType.Down &&
                event.keyCode === CounterConstant.KEYCODE_MOVE_END) {
                this.endFocusText();
                event.stopPropagation();
                return true;
              }
              if (event.type === KeyType.Down &&
                event.keyCode === CounterConstant.KEYCODE_DPAD_LEFT) {
                this.focusWithTarget('DateTextInput2' + String(this.timeStamp));
                return true;
              }

              if (event.type === KeyType.Down &&
                event.keyCode === CounterConstant.KEYCODE_DPAD_RIGHT) {
                this.focusWithTarget('DateTextInput3' + String(this.timeStamp));
                event.stopPropagation();
                return true;
              }

              if (event.type === KeyType.Down &&
                event.keyCode === CounterConstant.KEYCODE_TAB) {
                event.stopPropagation();
                this.focusWithTarget('DateTextInput1' + String(this.timeStamp));
                return true;
              }
              return false;
            })
            .onChange((value: string) => {
              this.inputDay = parseInt(value).toInt();
              if (value.length !== 2) {
                this.hasInputText3 = true;
              }
              if (value.length === 3) {
                this.inputDay = this.inputDay % 10;
              }
              if (this.timeoutID3 !== -1) {
                clearTimeout(this.timeoutID3);
                this.timeoutID3 = -1;
              }

              this.timeoutID3 = setTimeout(() => {
                this.hasInputText3 = false;
                this.day -= 1;
                if (this.inputDay >= 1 && this.inputDay <= this.getDayNumber()) {
                  this.day = this.inputDay;
                } else {
                  this.day += 1;
                  this.inputDay = this.day;
                }
              }, 1000);

              if (value.length === 2) {
                this.hasInputText3 = false;
                this.day -= 1;
                if (this.inputDay >= 1 && this.inputDay <= this.getDayNumber()) {
                  this.day = this.inputDay;
                  let date = new DateData(this.year, this.month, this.day);
                  this.onDateChange?.(date);
                } else {
                  this.day += 1;
                  this.inputDay = this.day;
                }
              }
            } as EditableTextOnChangeCallback)
            .onSubmit((enterKey: EnterKeyType) => {
              if (this.timeoutID3 !== -1) {
                clearTimeout(this.timeoutID3);
                this.timeoutID3 = -1;
              }
              this.hasInputText3 = false;
              this.day -= 1;
              if (this.inputDay >= 1 && this.inputDay <= this.getDayNumber()) {
                this.day = this.inputDay;
              } else {
                this.day += 1;
              }
            } as OnSubmitCallback)
            .tabIndex(-2)
            .focusOnTouch(true)
            .focusable(true)
            .onFocus(() => {
              this.focusText = FocusText.TEXT3;
              this.hasFocusText3 = true;
              this.controller3.caretPosition(this.convertNumberToString(this.day).length);
            })
            .onBlur(() => {
              this.focusText = FocusText.NONE;
              this.hasFocusText3 = false;
            })
            .onClick((event: ClickEvent) => {
              this.focusText = FocusText.TEXT3;
              this.hasFocusText3 = true;
              this.controller3.caretPosition(this.convertNumberToString(this.day).length);
            })
        }
        .direction(this.counterDirection)
        .width('92vp')
        .height(CounterResource.COUNTER_INLINE_CONTAINER_HEIGHT)
        .margin({
          start: LengthMetrics.vp(CounterResource.COUNTER_INLINE_DATE_TEXT_MARGIN),
          end: LengthMetrics.vp(CounterResource.COUNTER_INLINE_DATE_TEXT_MARGIN)
        } as LocalizedMargin)

        Column() {
          Stack() {
            Rect()
              .direction(this.counterDirection)
              .width(CounterResource.COUNTER_INLINE_FOCUS_BORDER_WIDTH)
              .height(CounterResource.COUNTER_INLINE_FOCUS_BORDER_HEIGHT)
              .radius([
                ['0vp', '0vp'],
                [CounterResource.COUNTER_INLINE_RADIUS, CounterResource.COUNTER_INLINE_RADIUS],
                ['0vp', '0vp'],
                ['0vp', '0vp']])
              .strokeWidth(this.addBtnFocusWidth)
              .stroke(CounterResource.BUTTON_BORDER_FOCUSED_COLOR)
              .margin({ end: LengthMetrics.vp(1) } as LocalizedMargin)
              .fillOpacity(0)
            Image(CounterResource.BUTTON_ARROW_UP)
              .direction(this.counterDirection)
              .width(CounterResource.COUNTER_INLINE_BUTTON_ICON_WIDTH)
              .height(CounterResource.COUNTER_INLINE_BUTTON_ICON_HEIGHT)
              .fillColor(CounterResource.BUTTON_ICON_COLOR)
              .opacity(this.addOpacity)
            Button({ type: ButtonType.Normal, stateEffect: this.addBtnStateEffect } as ButtonOptions)
              .accessibilityText($r('sys.string.increase_used_for_accessibility_text'))
              .accessibilityDescription($r('sys.string.increase_counter_double_click_description'))
              .direction(this.counterDirection)
              .width(CounterResource.COUNTER_INLINE_BUTTON_WIDTH)
              .height(CounterResource.COUNTER_INLINE_BUTTON_HEIGHT)
              .backgroundColor(Color.Transparent)
              .opacity(this.addOpacity)
              .enabled(this.addBtnEnabled)
              .onClick((event: ClickEvent) => {
                this.accessibilityBroadcastAddDate();
                if (event.source === SourceType.Mouse ||
                  event.source === SourceType.TouchScreen) {
                  this.addBtnFocusWidth = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                }
              })
              .gesture(
                LongPressGesture({ repeat: true })
                  .onAction((event: GestureEvent) => {
                    if (event.repeat) {
                      this.addDate();
                    }
                    this.addBtnFocusWidth = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                  })
                  .onActionEnd(() => {
                    this.accessibilityBroadcastAddDate();
                  })
              )
              .hoverEffect(this.choverEffect)
              .onHover((isHover: boolean, event: HoverEvent) => {
                this.onHoverIncrease?.(isHover);
              })
              .focusable(false)
              .onFocus(() => {
                this.addBtnFocusWidth = CounterResource.BUTTON_BORDER_FOCUSED_WIDTH;
                this.onFocusIncrease?.();
              })
              .onBlur(() => {
                this.addBtnFocusWidth = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                this.onBlurIncrease?.();
              })
          }
          .width(CounterResource.COUNTER_INLINE_BUTTON_WIDTH)
          .height(CounterResource.COUNTER_INLINE_BUTTON_HEIGHT)
          .padding({ top: '1vp' } as Padding)
          .borderWidth({ bottom: '1vp' } as EdgeWidths)
          .borderColor(CounterResource.COUNTER_BORDER_COLOR)
          .clip(true)

          Stack() {
            Rect()
              .direction(this.counterDirection)
              .width(CounterResource.COUNTER_INLINE_FOCUS_BORDER_WIDTH)
              .height(CounterResource.COUNTER_INLINE_FOCUS_BORDER_HEIGHT)
              .radius([
                ['0vp', '0vp'],
                ['0vp', '0vp'],
                [CounterResource.COUNTER_INLINE_RADIUS, CounterResource.COUNTER_INLINE_RADIUS],
                ['0vp', '0vp']
              ])
              .strokeWidth(this.subBtnFocusWidth)
              .stroke(CounterResource.BUTTON_BORDER_FOCUSED_COLOR)
              .margin({ top: LengthMetrics.vp(1), end: LengthMetrics.vp(1), bottom: LengthMetrics.vp(2) } as LocalizedMargin)
              .fillOpacity(0)
            Image(CounterResource.BUTTON_ARROW_DOWN)
              .direction(this.counterDirection)
              .width(CounterResource.COUNTER_INLINE_BUTTON_ICON_WIDTH)
              .height(CounterResource.COUNTER_INLINE_BUTTON_ICON_HEIGHT)
              .fillColor(CounterResource.BUTTON_ICON_COLOR)
              .opacity(this.subOpacity)
            Button({ type: ButtonType.Normal, stateEffect: this.subBtnStateEffect } as ButtonOptions)
              .accessibilityText($r('sys.string.reduce_used_for_accessibility_text'))
              .accessibilityDescription($r('sys.string.reduce_counter_double_click_description'))
              .direction(this.counterDirection)
              .width(CounterResource.COUNTER_INLINE_BUTTON_WIDTH)
              .height(CounterResource.COUNTER_INLINE_BUTTON_HEIGHT)
              .backgroundColor(Color.Transparent)
              .opacity(this.subOpacity)
              .enabled(this.subBtnEnabled)
              .onClick((event: ClickEvent) => {
                this.accessibilityBroadcastSubDate();
                if (event.source === SourceType.Mouse ||
                  event.source === SourceType.TouchScreen) {
                  this.subBtnFocusWidth = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                }
              })
              .gesture(
                LongPressGesture({ repeat: true })
                  .onAction((event: GestureEvent) => {
                    if (event.repeat) {
                      this.subDate();
                    }
                    this.subBtnFocusWidth = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                  })
                  .onActionEnd(() => {
                    this.accessibilityBroadcastSubDate();
                  })
              )
              .hoverEffect(this.choverEffect)
              .onHover((isHover: boolean, event: HoverEvent) => {
                this.onHoverDecrease?.(isHover);
              })
              .focusable(false)
              .onFocus(() => {
                this.subBtnFocusWidth = CounterResource.BUTTON_BORDER_FOCUSED_WIDTH;
                this.onFocusDecrease?.();
              })
              .onBlur(() => {
                this.subBtnFocusWidth = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                this.onBlurDecrease?.();
              })
          }.width(CounterResource.COUNTER_INLINE_BUTTON_WIDTH)
          .height(CounterResource.COUNTER_INLINE_BUTTON_HEIGHT)
          .clip(true)
        }
        .direction(this.counterDirection)
        .width(CounterResource.COUNTER_INLINE_BUTTON_WIDTH)
        .height(CounterResource.COUNTER_INLINE_CONTAINER_HEIGHT)
        .borderWidth({ start: LengthMetrics.vp(CounterResource.COUNTER_BORDER_WIDTH_NUMBER) } as LocalizedEdgeWidths)
        .borderColor(CounterResource.COUNTER_BORDER_COLOR)
      }
      .direction(this.counterDirection)
      .height(CounterResource.COUNTER_INLINE_CONTAINER_HEIGHT)
      .borderWidth(CounterResource.COUNTER_BORDER_WIDTH)
      .borderColor(CounterResource.COUNTER_BORDER_COLOR)
      .borderRadius(CounterResource.COUNTER_INLINE_RADIUS)
      .clip(true)
    }
  }
}
