/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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
import { LengthMetrics } from '@ohos.arkui.node';
import common from '@ohos.app.ability.common';

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
  public step?: number;
  public onHoverIncrease?: (isHover: boolean) => void;
  public onHoverDecrease?: (isHover: boolean) => void;
}

export class InlineStyleOptions extends CommonOptions {
  public value?: number;
  public min?: number;
  public max?: number;
  public textWidth?: number;
  public onChange?: (value: number) => void;
}

export class NumberStyleOptions extends InlineStyleOptions {
  public label?: ResourceStr;
  public onFocusIncrease?: () => void;
  public onFocusDecrease?: () => void;
  public onBlurIncrease?: () => void;
  public onBlurDecrease?: () => void;
}

export class DateData {
  public year: number;
  public month: number;
  public day: number;

  constructor(year: number, month: number, day: number) {
    this.year = year;
    this.month = month;
    this.day = day;
  }

  toString(): string {
    let date = this.year.toString() + '-';
    let month = this.month < 10 ? '0' + this.month.toString() : this.month.toString();
    date += month + '-';
    let day = this.day < 10 ? '0' + this.day.toString() : this.day.toString();
    date += day;
    return date;
  }
}

export class DateStyleOptions extends CommonOptions {
  public year?: number;
  public month?: number;
  public day?: number;
  public onDateChange?: (date: DateData) => void;
}

export class CounterOptions {
  public type: CounterType;
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
  public static readonly COUNTER_BORDER_WIDTH_NUMBER = 1;
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
  public static readonly COUNTER_LIST_PADDING = 12;
  public static readonly COUNTER_LIST_HEIGHT = '48vp';
  public static readonly COUNTER_LIST_BUTTON_ICON_SIZE = '20vp';
  public static readonly COUNTER_LIST_BUTTON_SIZE = '32vp';
  public static readonly COUNTER_LIST_BUTTON_RADIUS = '16vp';
  public static readonly COUNTER_LIST_BUTTON_TEXT_DISTANCE = '8vp';
  public static readonly COUNTER_LIST_BUTTON_TEXT_MARGIN = 8;
  public static readonly COUNTER_LIST_FOCUS_BORDER_SIZE = '30vp';
  public static readonly COUNTER_LIST_FOCUS_BORDER_RADIUS = '15vp';
  public static readonly COUNTER_LIST_BUTTON_HOT_SPOT_X = '-8vp';
  public static readonly COUNTER_LIST_BUTTON_HOT_SPOT_Y = '-8vp';
  public static readonly COUNTER_COMPACT_BUTTON_RADIUS = '12vp';
  public static readonly COUNTER_COMPACT_BUTTON_TEXT_DISTANCE = '10vp';
  public static readonly COUNTER_COMPACT_BUTTON_TEXT_MARGIN = 10;
  public static readonly COUNTER_COMPACT_CONTAINER_LABEL_DISTANCE = '8vp';
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
  public static readonly COUNTER_INLINE_DATE_TEXT_MARGIN = 12;
  public static readonly COUNTER_INLINE_INPUT_TEXT_MARGIN = 12;
  public static readonly COUNTER_BUTTON_INITIAL_OPACITY = 1;
  public static readonly COUNTER_BUTTON_DISABLE_OPACITY = 0.4;
  public static readonly COUNTER_LABEL_MAX_FONT_SIZE_SCALE = 2;
  public static readonly COUNTER_NUMBER_MAX_FONT_SIZE_SCALE = 1;
}

class CounterConstant {
  public static readonly COUNTER_MAX_YEAR = 5000;
  public static readonly COUNTER_MIN_YEAR = 1;
  public static readonly COUNTER_INITIAL_MONTH = 1;
  public static readonly COUNTER_INITIAL_DAY = 1;
  public static readonly COUNTER_INITIAL_STEP = 1;
  public static readonly COUNTER_TEN_NUMBER = 10;
  public static readonly COUNTER_MIN_MONTH = 1;
  public static readonly COUNTER_MAX_MONTH = 12;
  public static readonly COUNTER_MIN_DAY = 1;
  public static readonly KEYCODE_DPAD_UP = 2012;
  public static readonly KEYCODE_DPAD_DOWN = 2013;
  public static readonly KEYCODE_DPAD_LEFT = 2014;
  public static readonly KEYCODE_DPAD_RIGHT = 2015;
  public static readonly KEYCODE_MOVE_HOME = 2081;
  public static readonly KEYCODE_MOVE_END = 2082;
  public static readonly KEYCODE_TAB = 2049;
  public static readonly KEYCODE_ESC = 2070;
  public static readonly COUNTER_MIN_VALUE = 0;
  public static readonly COUNTER_MAX_VALUE = 999;
  public static readonly JANUARY = 1;
  public static readonly FEBRUARY = 2;
  public static readonly MARCH = 3;
  public static readonly APRIL = 4;
  public static readonly MAY = 5;
  public static readonly JUNE = 6;
  public static readonly JULY = 7;
  public static readonly AUGUST = 8;
  public static readonly SEPTEMBER = 9;
  public static readonly OCTOBER = 10;
  public static readonly NOVEMBER = 11;
  public static readonly DECEMBER = 12;
  public static readonly BIG_MONTH_DAYS = 31;
  public static readonly SMALL_MONTH_DAYS = 30;
  public static readonly FEBRUARY_DAYS = 28;
  public static readonly AUSPICIOUS_FEBRUARY_DAYS = 29;
  public static readonly AUSPICIOUS_FOUR = 4;
  public static readonly AUSPICIOUS_HUNDRED = 100;
  public static readonly AUSPICIOUS_FOUR_HUNDRED = 400;
}

@Component
export struct CounterComponent {
  @Prop @Watch('onOptionsChange') options: CounterOptions;
  @State type: number = -1;
  @State counterDirection: Direction = Direction.Auto;
  @State choverEffect: HoverEffect = HoverEffect.Auto;
  @State focusEnable: boolean = true;
  @State step: number = CounterConstant.COUNTER_INITIAL_STEP;
  @State inputValue: string = '0';
  @State inputYear: number = CounterConstant.COUNTER_MIN_YEAR;
  @State inputMoon: number = 0;
  @State inputDay: number = 0;
  @State inputHour: number = 0;
  @State inputMinute: number = 0;
  @State inputSecond: number = 0;
  @State subOpacity: number = CounterResource.COUNTER_BUTTON_INITIAL_OPACITY;
  @State addOpacity: number = CounterResource.COUNTER_BUTTON_INITIAL_OPACITY;
  @State subBtnStateEffect: boolean = true;
  @State addBtnStateEffect: boolean = true;
  @State focusText: number = FocusText.NONE;
  @State hasFocusText1: boolean = false
  @State hasFocusText2: boolean = false
  @State hasFocusText3: boolean = false
  @State subBtnFocusWidh: string = '0vp'
  @State addBtnFocusWidh: string = '0vp'
  @State value: number | undefined = undefined;
  @State year: number = 0;
  @State month: number = 0;
  @State day: number = 0;
  @State hour: number = 0;
  @State minute: number = 0;
  @State second: number = 0;
  @State subBtnEnabled: boolean = true
  @State addBtnEnabled: boolean = true
  @State hasInputText1: boolean = false;
  @State hasInputText2: boolean = false;
  @State hasInputText3: boolean = false;
  @State textWidth: number = 0;
  @State min: number = CounterConstant.COUNTER_MIN_VALUE;
  @State max: number = CounterConstant.COUNTER_MAX_VALUE;
  private maxYear: number = CounterConstant.COUNTER_MAX_YEAR;
  private minYear: number = CounterConstant.COUNTER_MIN_YEAR;
  private numberStrList: Array<string> = ['00', '01', '02', '03', '04', '05', '06', '07', '08', '09'];
  private onHoverIncrease?: (isHover: boolean) => void;
  private onHoverDecrease?: (isHover: boolean) => void;
  private onFocusIncrease?: () => void;
  private onFocusDecrease?: () => void;
  private onBlurIncrease?: () => void;
  private onBlurDecrease?: () => void;
  private onChange?: (value: number) => void;
  private onDateChange?: (date: DateData) => void;
  private timeoutID1: number = -1;
  private timeoutID2: number = -1;
  private timeoutID3: number = -1;
  private numberStyleOptions: NumberStyleOptions;
  private dateStyleOptions: DateStyleOptions;
  private inlineStyleOptions: InlineStyleOptions;
  private timeStamp: number = 0;
  private hasTextWidth: boolean = false;
  private controller1: TextInputController = new TextInputController();
  private controller2: TextInputController = new TextInputController();
  private controller3: TextInputController = new TextInputController();

  getTextInputFontSize() {
    let fontSize = this.resourceToVp(CounterResource.COUNTER_NUMBER_SIZE);
    let uiContext = this.getUIContext();
    let fontSizeScale = (uiContext.getHostContext() as common.UIAbilityContext)?.config?.fontSizeScale ?? 1;
    if (fontSizeScale < 1) {
      return fontSize + 'fp';
    } else {
      return fontSize + 'vp';
    }
  }

  convertNumberToString(value: number) {
    if (value >= 0 && value < CounterConstant.COUNTER_TEN_NUMBER) {
      return this.numberStrList[value];
    } else {
      return value.toString();
    }
  }

  aboutToAppear(): void {
    let dateTime = new Date();
    this.timeStamp = dateTime.getTime();
    if (this.options !== undefined && this.options !== null) {
      this.onOptionsChange();
    }
  }

  private updateNumberStyleOptions() {
    if (this.numberStyleOptions.label === undefined) {
      this.numberStyleOptions.label = '';
    }
    if (this.value === undefined) {
      this.value = this.numberStyleOptions.value !== undefined ? this.numberStyleOptions.value : 0;
      this.onChange?.(this.value);
      this.inputValue = this.value.toString();
    }
    if (this.numberStyleOptions.min !== undefined) {
      this.min = this.numberStyleOptions.min;
    }
    if (this.numberStyleOptions.max !== undefined) {
      this.max = this.numberStyleOptions.max;
    }
    if (this.min > this.max) {
      this.min = this.max;
    }
    if (this.numberStyleOptions.textWidth !== undefined) {
      this.textWidth = this.numberStyleOptions.textWidth;
      if (this.textWidth < 0) {
        this.textWidth = 0;
      }
      this.hasTextWidth = true;
    }
    if (this.value <= this.min) {
      this.value = this.min;
      this.onChange?.(this.value);
      this.inputValue = this.value.toString();
    }
    if (this.value >= this.max) {
      this.value = this.max;
      this.onChange?.(this.value);
      this.inputValue = this.value.toString();
    }
    if (this.numberStyleOptions.step !== undefined) {
      if (this.numberStyleOptions.step < 1) {
        this.step = 1
      } else {
        this.step = this.numberStyleOptions.step;
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
      this.focusEnable = this.numberStyleOptions.focusable;
    }
  }

  private updateInlineStyleOptions() {
    if (this.value === undefined) {
      this.value = this.inlineStyleOptions.value !== undefined ? this.inlineStyleOptions.value : 0;
      this.onChange?.(this.value);
      this.inputValue = this.value.toString();
    }
    if (this.inlineStyleOptions.min !== undefined) {
      this.min = this.inlineStyleOptions.min;
    }
    if (this.inlineStyleOptions.max !== undefined) {
      this.max = this.inlineStyleOptions.max;
    }
    if (this.min > this.max) {
      this.min = this.max;
    }

    if (this.inlineStyleOptions.textWidth !== undefined) {
      this.textWidth = this.inlineStyleOptions.textWidth;
      if (this.textWidth < 0) {
        this.textWidth = 0;
      }
      this.hasTextWidth = true;
    }
    if (this.value <= this.min) {
      this.value = this.min;
      this.onChange?.(this.value);
      this.inputValue = this.value.toString();
    }
    if (this.value >= this.max) {
      this.value = this.max;
      this.onChange?.(this.value);
      this.inputValue = this.value.toString();
    }
    if (this.inlineStyleOptions.step !== undefined) {
      if (this.inlineStyleOptions.step < 1) {
        this.step = 1
      } else {
        this.step = this.inlineStyleOptions.step;
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
      this.focusEnable = this.inlineStyleOptions.focusable;
    }
  }

  private updateDateStyleOptions() {
    if (this.dateStyleOptions.step !== undefined) {
      if (this.dateStyleOptions.step < 1) {
        this.step = 1
      } else {
        this.step = Math.floor(this.dateStyleOptions.step);
      }
    }
    if (this.dateStyleOptions.onHoverIncrease !== undefined) {
      this.onHoverIncrease = this.dateStyleOptions.onHoverIncrease;
    }
    if (this.dateStyleOptions.onHoverDecrease !== undefined) {
      this.onHoverDecrease = this.dateStyleOptions.onHoverDecrease;
    }
    if (this.dateStyleOptions.year !== undefined &&
      this.dateStyleOptions.year >= this.minYear &&
      this.dateStyleOptions.year <= this.maxYear) {
      if (this.year === 0) {
        this.year = this.dateStyleOptions.year;
      }
    } else {
      this.year = CounterConstant.COUNTER_MIN_YEAR;
    }
    if (this.dateStyleOptions.month !== undefined &&
      this.dateStyleOptions.month <= CounterConstant.COUNTER_MAX_MONTH &&
      this.dateStyleOptions.month >= CounterConstant.COUNTER_MIN_MONTH) {
      if (this.month === 0) {
        this.month = this.dateStyleOptions.month;
      }
    } else {
      this.month = CounterConstant.COUNTER_INITIAL_MONTH;
    }
    if (this.dateStyleOptions.day !== undefined &&
      this.dateStyleOptions.day <= this.getDayNumber() &&
      this.dateStyleOptions.day >= CounterConstant.COUNTER_MIN_DAY) {
      if (this.day === 0) {
        this.day = this.dateStyleOptions.day;
      }
    } else {
      this.day = CounterConstant.COUNTER_INITIAL_DAY;
    }
    if (this.dateStyleOptions.onDateChange !== undefined) {
      this.onDateChange = this.dateStyleOptions.onDateChange;
    }
    if (this.dateStyleOptions.focusable !== undefined) {
      this.focusEnable = this.dateStyleOptions.focusable;
    }
    this.updateDay();
  }

  private onOptionsChange() {
    this.type = this.options.type;
    if (this.options.direction) {
      this.counterDirection = this.options.direction;
    } else {
      this.counterDirection = Direction.Auto;
    }

    if (this.type === CounterType.LIST ||
      this.type === CounterType.COMPACT) {
      this.numberStyleOptions = this.options.numberOptions;
      this.updateNumberStyleOptions();
    } else if (this.type === CounterType.INLINE) {
      this.inlineStyleOptions = this.options.inlineOptions;
      this.updateInlineStyleOptions();
    } else if (this.type === CounterType.INLINE_DATE) {
      let options = this.options.dateOptions;
      options.year = options.year ? options.year : CounterConstant.COUNTER_MIN_YEAR;
      options.month = options.month ? options.month : CounterConstant.COUNTER_MIN_MONTH;
      options.day = options.day ? options.day : CounterConstant.COUNTER_MIN_DAY;
      this.dateStyleOptions = options;
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
        this.focusWithTarget('InlineTextInput' + this.timeStamp.toString());
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

  private getDayNumber(): number {
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
        break;
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
    this.focusWithTarget('DateTextInput3' + this.timeStamp.toString());
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
    this.focusWithTarget('DateTextInput3' + this.timeStamp.toString());
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
    if (this.addBtnFocusWidh === CounterResource.BUTTON_BORDER_FOCUSED_WIDTH) {
      this.addBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
      this.onBlurIncrease && this.onBlurIncrease();
    }
    if (this.subBtnFocusWidh === CounterResource.BUTTON_BORDER_FOCUSED_WIDTH) {
      this.subBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
      this.onBlurDecrease && this.onBlurDecrease();
    }
  }

  private homeFocusText() {
    this.focusWithTarget('DateTextInput1' + this.timeStamp.toString());
  }

  private endFocusText() {
    this.focusWithTarget('DateTextInput3' + this.timeStamp.toString());
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
    return this.hasInputText1 ? this.inputValue : this.value.toString();
  }

  private getValueLength() {
    return this.getValue().length > 0 ? this.getValue().length : 1;
  }

  private getYear() {
    let year: string = this.year.toString();
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
      var res = focusControl.requestFocus(key);
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
    if (this.max.toString().length > this.min.toString().length) {
      return this.max.toString().length + 1;
    } else {
      return this.min.toString().length + 1;
    }
  }

  private resourceToVp(value: Resource): number {
    try {
      if ((value as Resource).id !== -1) {
        return px2vp(getContext(this).resourceManager.getNumber((value as Resource).id))
      } else {
        return px2vp(getContext(this)
          .resourceManager
          .getNumberByName(((value.params as string[])[0]).split('.')[2]))
      }
    } catch (error) {
      return CounterResource.COUNTER_LIST_PADDING
    }
  }

  build() {
    if (this.type === CounterType.LIST) {
      RelativeContainer() {
        Text(this.numberStyleOptions.label)
          .direction(this.counterDirection)
          .fontSize(CounterResource.COUNTER_LIST_LABEL_SIZE)
          .maxFontScale(CounterResource.COUNTER_LABEL_MAX_FONT_SIZE_SCALE);
          .fontColor(CounterResource.COUNTER_TEXT_COLOR)
          .margin({
            start: LengthMetrics.vp(this.resourceToVp(CounterResource.COUNTER_LIST_LEFT_PADDING))
          })
          .alignRules({
            center: { anchor: '__container__', align: VerticalAlign.Center },
            start: { anchor: '__container__', align: HorizontalAlign.Start },
            end: { anchor: 'Row1', align: HorizontalAlign.Start }
          })
          .id('Text')
        Row() {
          Stack() {
            Image(CounterResource.BUTTON_SUB_ICON)
              .direction(this.counterDirection)
              .width(CounterResource.COUNTER_LIST_BUTTON_ICON_SIZE)
              .height(CounterResource.COUNTER_LIST_BUTTON_ICON_SIZE)
              .fillColor(CounterResource.BUTTON_ICON_COLOR)
              .opacity(this.subOpacity)
            Button({ type: ButtonType.Circle, stateEffect: this.subBtnStateEffect })
              .direction(this.counterDirection)
              .width(CounterResource.COUNTER_LIST_BUTTON_SIZE)
              .height(CounterResource.COUNTER_LIST_BUTTON_SIZE)
              .responseRegion({
                x: CounterResource.COUNTER_LIST_BUTTON_HOT_SPOT_X,
                y: CounterResource.COUNTER_LIST_BUTTON_HOT_SPOT_Y,
                width: '150%',
                height: '150%'
              })
              .groupDefaultFocus(true)
              .backgroundColor(CounterResource.BUTTON_BACKGROUD_COLOR)
              .opacity(this.subOpacity)
              .enabled(this.subBtnEnabled)
              .key('ListSubButton' + this.timeStamp.toString())
              .onKeyEvent((event: KeyEvent) => {
                this.subBtnFocusWidh = CounterResource.BUTTON_BORDER_FOCUSED_WIDTH;
                if (event.keyCode === CounterConstant.KEYCODE_ESC) {
                  this.resetFocusButton();
                  event.stopPropagation();
                }
                if (event.type === KeyType.Down &&
                  event.keyCode === CounterConstant.KEYCODE_MOVE_HOME) {
                  event.stopPropagation();
                  this.homeFirstValue();
                  this.focusWithTarget('ListAddButton' + this.timeStamp.toString());
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
                  this.focusWithTarget('ListAddButton' + this.timeStamp.toString());
                }
              })
              .onClick((event: ClickEvent) => {
                this.subValue();
                this.onChange?.(this.value);
                if (event.source === SourceType.Mouse ||
                  event.source === SourceType.TouchScreen) {
                  this.subBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                }
              })
              .gesture(
                LongPressGesture({ repeat: true })
                  .onAction((event: GestureEvent) => {
                    if (event.repeat) {
                      this.subValue();
                      this.onChange?.(this.value);
                    }
                    this.subBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                  })
              )
              .hoverEffect(this.choverEffect)
              .onHover((isHover: boolean) => {
                this.onHoverDecrease && this.onHoverDecrease(isHover);
              })
              .focusable(this.focusEnable)
              .onFocus(() => {
                this.subBtnFocusWidh = CounterResource.BUTTON_BORDER_FOCUSED_WIDTH;
                this.onFocusDecrease && this.onFocusDecrease();
                this.updateButtonStatus();
              })
              .onBlur(() => {
                this.subBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                this.onBlurDecrease && this.onBlurDecrease();
              })
          }
          .direction(this.counterDirection)
          .width(CounterResource.COUNTER_LIST_BUTTON_SIZE)
          .height(CounterResource.COUNTER_LIST_BUTTON_SIZE)
          .borderRadius(CounterResource.COUNTER_LIST_BUTTON_RADIUS)
          .borderWidth(this.subBtnFocusWidh)
          .borderColor(CounterResource.BUTTON_BORDER_FOCUSED_COLOR)
          .clip(true)

          if (this.hasTextWidth) {
            Text(this.value.toString())
              .direction(this.counterDirection)
              .width(this.textWidth.toString())
              .textAlign(TextAlign.Center)
              .fontSize(CounterResource.COUNTER_LIST_NUMBER_SIZE)
              .maxFontScale(CounterResource.COUNTER_NUMBER_MAX_FONT_SIZE_SCALE);
              .fontColor(CounterResource.COUNTER_TEXT_COLOR)
              .margin({
                start: LengthMetrics.vp(CounterResource.COUNTER_LIST_BUTTON_TEXT_MARGIN),
                end: LengthMetrics.vp(CounterResource.COUNTER_LIST_BUTTON_TEXT_MARGIN)
              })
          } else {
            Text(this.value.toString())
              .direction(this.counterDirection)
              .textAlign(TextAlign.Center)
              .fontSize(CounterResource.COUNTER_LIST_NUMBER_SIZE)
              .maxFontScale(CounterResource.COUNTER_NUMBER_MAX_FONT_SIZE_SCALE);
              .fontColor(CounterResource.COUNTER_TEXT_COLOR)
              .margin({
                start: LengthMetrics.vp(CounterResource.COUNTER_LIST_BUTTON_TEXT_MARGIN),
                end: LengthMetrics.vp(CounterResource.COUNTER_LIST_BUTTON_TEXT_MARGIN)
              })
          }

          Stack() {
            Image(CounterResource.BUTTON_ADD_ICON)
              .direction(this.counterDirection)
              .width(CounterResource.COUNTER_LIST_BUTTON_ICON_SIZE)
              .height(CounterResource.COUNTER_LIST_BUTTON_ICON_SIZE)
              .fillColor(CounterResource.BUTTON_ICON_COLOR)
              .opacity(this.addOpacity)
            Button({ type: ButtonType.Circle, stateEffect: this.addBtnStateEffect })
              .direction(this.counterDirection)
              .width(CounterResource.COUNTER_LIST_BUTTON_SIZE)
              .height(CounterResource.COUNTER_LIST_BUTTON_SIZE)
              .responseRegion({
                x: CounterResource.COUNTER_LIST_BUTTON_HOT_SPOT_X,
                y: CounterResource.COUNTER_LIST_BUTTON_HOT_SPOT_Y,
                width: '150%',
                height: '150%'
              })
              .backgroundColor(CounterResource.BUTTON_BACKGROUD_COLOR)
              .opacity(this.addOpacity)
              .enabled(this.addBtnEnabled)
              .key('ListAddButton' + this.timeStamp.toString())
              .onKeyEvent((event: KeyEvent) => {
                this.addBtnFocusWidh = CounterResource.BUTTON_BORDER_FOCUSED_WIDTH
                if (event.keyCode === CounterConstant.KEYCODE_ESC) {
                  this.resetFocusButton();
                  event.stopPropagation();
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
                  this.focusWithTarget('ListAddButton' + this.timeStamp.toString());
                }
                if (event.type === KeyType.Down &&
                  event.keyCode === CounterConstant.KEYCODE_MOVE_END) {
                  event.stopPropagation();
                  this.endLastValue();
                  this.focusWithTarget('ListSubButton' + this.timeStamp.toString());
                }
              })
              .onClick((event: ClickEvent) => {
                this.addValue();
                this.onChange?.(this.value);
                if (event.source === SourceType.Mouse ||
                  event.source === SourceType.TouchScreen) {
                  this.addBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                }
              })
              .gesture(
                LongPressGesture({ repeat: true })
                  .onAction((event: GestureEvent) => {
                    if (event.repeat) {
                      this.addValue();
                      this.onChange?.(this.value);
                    }
                    this.addBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                  })
              )
              .hoverEffect(this.choverEffect)
              .onHover((isHover: boolean) => {
                this.onHoverIncrease && this.onHoverIncrease(isHover);
              })
              .focusable(this.focusEnable)
              .onFocus(() => {
                this.addBtnFocusWidh = CounterResource.BUTTON_BORDER_FOCUSED_WIDTH;
                this.onFocusIncrease && this.onFocusIncrease();
                this.updateButtonStatus();
              })
              .onBlur(() => {
                this.addBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                this.onBlurIncrease && this.onBlurIncrease();
              })
          }
          .direction(this.counterDirection)
          .width(CounterResource.COUNTER_LIST_BUTTON_SIZE)
          .height(CounterResource.COUNTER_LIST_BUTTON_SIZE)
          .borderRadius(CounterResource.COUNTER_LIST_BUTTON_RADIUS)
          .borderWidth(this.addBtnFocusWidh)
          .borderColor(CounterResource.BUTTON_BORDER_FOCUSED_COLOR)
          .clip(true)
        }
        .direction(this.counterDirection)
        .height(CounterResource.COUNTER_LIST_BUTTON_SIZE)
        .margin({
          end: LengthMetrics.vp(this.resourceToVp(CounterResource.COUNTER_LIST_RIGHT_PADDING))
        })
        .alignRules({
          center: { anchor: '__container__', align: VerticalAlign.Center },
          end: { anchor: '__container__', align: HorizontalAlign.End }
        })
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
            Button({ type: ButtonType.Circle, stateEffect: this.subBtnStateEffect })
              .direction(this.counterDirection)
              .width(CounterResource.COUNTER_COMPACT_BUTTON_SIZE)
              .height(CounterResource.COUNTER_COMPACT_BUTTON_SIZE)
              .backgroundColor(CounterResource.BUTTON_BACKGROUD_COLOR)
              .opacity(this.subOpacity)
              .enabled(this.subBtnEnabled)
              .key('CompactSubButton' + this.timeStamp.toString())
              .onKeyEvent((event: KeyEvent) => {
                this.subBtnFocusWidh = CounterResource.BUTTON_BORDER_FOCUSED_WIDTH
                if (event.keyCode === CounterConstant.KEYCODE_ESC) {
                  this.resetFocusButton();
                  event.stopPropagation();
                }
                if (event.type === KeyType.Down &&
                  event.keyCode === CounterConstant.KEYCODE_MOVE_HOME) {
                  event.stopPropagation();
                  this.homeFirstValue();
                  this.focusWithTarget('CompactAddButton' + this.timeStamp.toString());
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
                  this.focusWithTarget('CompactSubButton' + this.timeStamp.toString());
                }
              })
              .onClick((event: ClickEvent) => {
                this.subValue();
                this.onChange?.(this.value);
                if (event.source === SourceType.Mouse ||
                  event.source === SourceType.TouchScreen) {
                  this.subBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
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
                      this.subBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                    }
                  })
              )
              .hoverEffect(this.choverEffect)
              .onHover((isHover: boolean) => {
                this.onHoverDecrease && this.onHoverDecrease(isHover);
              })
              .focusable(this.focusEnable)
              .groupDefaultFocus(true)
              .onFocus(() => {
                this.subBtnFocusWidh = CounterResource.BUTTON_BORDER_FOCUSED_WIDTH;
                this.onFocusDecrease && this.onFocusDecrease();
                this.updateButtonStatus();
              })
              .onBlur(() => {
                this.subBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                this.onBlurDecrease && this.onBlurDecrease();
              })
          }
          .width(CounterResource.COUNTER_COMPACT_BUTTON_SIZE)
          .height(CounterResource.COUNTER_COMPACT_BUTTON_SIZE)
          .borderRadius(CounterResource.COUNTER_COMPACT_BUTTON_RADIUS)
          .borderWidth(this.subBtnFocusWidh)
          .borderColor(CounterResource.BUTTON_BORDER_FOCUSED_COLOR)
          .margin({ 
            start: LengthMetrics.vp(this.resourceToVp(CounterResource.COUNTER_COMPACT_BUTTON_CONTAINER_MARGIN)) 
          });
          .clip(true)

          if (this.hasTextWidth) {
            Text(this.value.toString())
              .textAlign(TextAlign.Center)
              .fontSize(CounterResource.COUNTER_NUMBER_SIZE)
              .maxFontScale(CounterResource.COUNTER_NUMBER_MAX_FONT_SIZE_SCALE);
              .fontColor(CounterResource.COUNTER_TEXT_COLOR)
              .width(this.textWidth.toString())
              .margin({
                start: LengthMetrics.vp(CounterResource.COUNTER_COMPACT_BUTTON_TEXT_MARGIN),
                end: LengthMetrics.vp(CounterResource.COUNTER_COMPACT_BUTTON_TEXT_MARGIN)
              })
          } else {
            Text(this.value.toString())
              .direction(this.counterDirection)
              .textAlign(TextAlign.Center)
              .fontSize(CounterResource.COUNTER_NUMBER_SIZE)
              .maxFontScale(CounterResource.COUNTER_NUMBER_MAX_FONT_SIZE_SCALE);
              .fontColor(CounterResource.COUNTER_TEXT_COLOR)
              .margin({
                start: LengthMetrics.vp(CounterResource.COUNTER_COMPACT_BUTTON_TEXT_MARGIN),
                end: LengthMetrics.vp(CounterResource.COUNTER_COMPACT_BUTTON_TEXT_MARGIN)
              })
          }

          Stack() {
            Image(CounterResource.BUTTON_ADD_ICON)
              .direction(this.counterDirection)
              .width(CounterResource.COUNTER_COMPACT_BUTTON_ICON_SIZE)
              .height(CounterResource.COUNTER_COMPACT_BUTTON_ICON_SIZE)
              .fillColor(CounterResource.BUTTON_ICON_COLOR)
              .opacity(this.addOpacity)
            Button({ type: ButtonType.Circle, stateEffect: this.addBtnStateEffect })
              .direction(this.counterDirection)
              .width(CounterResource.COUNTER_COMPACT_BUTTON_SIZE)
              .height(CounterResource.COUNTER_COMPACT_BUTTON_SIZE)
              .backgroundColor(CounterResource.BUTTON_BACKGROUD_COLOR)
              .opacity(this.addOpacity)
              .enabled(this.addBtnEnabled)
              .key('CompactAddButton' + this.timeStamp.toString())
              .onKeyEvent((event: KeyEvent) => {
                this.addBtnFocusWidh = CounterResource.BUTTON_BORDER_FOCUSED_WIDTH
                if (event.keyCode === CounterConstant.KEYCODE_ESC) {
                  this.resetFocusButton();
                  event.stopPropagation();
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
                  this.focusWithTarget('CompactAddButton' + this.timeStamp.toString());
                }
                if (event.type === KeyType.Down &&
                  event.keyCode === CounterConstant.KEYCODE_MOVE_END) {
                  event.stopPropagation();
                  this.endLastValue();
                  this.focusWithTarget('CompactSubButton' + this.timeStamp.toString());
                }
              })
              .onClick((event: ClickEvent) => {
                this.addValue();
                this.onChange?.(this.value);
                if (event.source === SourceType.Mouse ||
                  event.source === SourceType.TouchScreen) {
                  this.addBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
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
                      this.addBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                    }
                  })
              )
              .hoverEffect(this.choverEffect)
              .onHover((isHover: boolean) => {
                this.onHoverIncrease && this.onHoverIncrease(isHover);
              })
              .focusable(this.focusEnable)
              .onFocus(() => {
                this.addBtnFocusWidh = CounterResource.BUTTON_BORDER_FOCUSED_WIDTH;
                this.onFocusIncrease && this.onFocusIncrease();
                this.updateButtonStatus();
              })
              .onBlur(() => {
                this.addBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                this.onBlurIncrease && this.onBlurIncrease();
              })
          }
          .direction(this.counterDirection)
          .width(CounterResource.COUNTER_COMPACT_BUTTON_SIZE)
          .height(CounterResource.COUNTER_COMPACT_BUTTON_SIZE)
          .borderRadius(CounterResource.COUNTER_COMPACT_BUTTON_RADIUS)
          .borderWidth(this.addBtnFocusWidh)
          .borderColor(CounterResource.BUTTON_BORDER_FOCUSED_COLOR)
          .margin({ 
            end: LengthMetrics.vp(this.resourceToVp(CounterResource.COUNTER_COMPACT_BUTTON_CONTAINER_MARGIN)) 
          });
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
          .margin({ top: CounterResource.COUNTER_COMPACT_CONTAINER_LABEL_DISTANCE })
          .fontSize(CounterResource.COUNTER_COMPACT_LABEL_SIZE)
          .maxFontScale(CounterResource.COUNTER_LABEL_MAX_FONT_SIZE_SCALE);
          .fontColor(CounterResource.COUNTER_TEXT_COLOR)
          .align(Alignment.Top)
      }
    } else if (this.type === CounterType.INLINE) {
      Row() {
        if (this.hasTextWidth) {
          RelativeContainer() {
            TextInput({
              text: this.hasInputText1 ? this.inputValue : this.value.toString(),
              controller: this.controller1
            })
              .alignRules({
                center: { anchor: '__container__', align: VerticalAlign.Center },
                middle: { anchor: '__container__', align: HorizontalAlign.Center }
              })
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
              .key('InlineTextInput' + this.timeStamp.toString())
              .onKeyEvent((event: KeyEvent) => {
                this.focusCurrentText(FocusText.TEXT1)
                if (event.keyCode === CounterConstant.KEYCODE_ESC) {
                  this.resetFocusText();
                  event.stopPropagation();
                }
                if (event.type === KeyType.Down &&
                  event.keyCode === CounterConstant.KEYCODE_DPAD_UP) {
                  this.addValue();
                  event.stopPropagation();
                }
                if (event.type === KeyType.Down &&
                  event.keyCode === CounterConstant.KEYCODE_MOVE_HOME) {
                  event.stopPropagation();
                  this.focusWithTarget('InlineTextInput' + this.timeStamp.toString());
                }
                if (event.type === KeyType.Down &&
                  event.keyCode === CounterConstant.KEYCODE_MOVE_END) {
                  event.stopPropagation();
                  this.focusWithTarget('InlineTextInput' + this.timeStamp.toString());
                }
                if (event.type === KeyType.Down &&
                  event.keyCode === CounterConstant.KEYCODE_DPAD_DOWN) {
                  this.subValue();
                  event.stopPropagation();
                }
                if (event.type === KeyType.Down &&
                  event.keyCode === CounterConstant.KEYCODE_DPAD_LEFT) {
                  this.focusWithTarget('InlineTextInput' + this.timeStamp.toString());
                  event.stopPropagation();
                }
                if (event.type === KeyType.Down &&
                  event.keyCode === CounterConstant.KEYCODE_DPAD_RIGHT) {
                  this.focusWithTarget('InlineTextInput' + this.timeStamp.toString());
                  event.stopPropagation();
                }
              })
              .onChange((value: string) => {
                this.inputValue = value;
                for (let i = 0; i < value.length; i++) {
                  let c = value[i];
                  if (c === '+' || c === '*' || c === '#') {
                    this.value -= 1;
                    this.value += 1;
                    this.inputValue = this.value.toString();
                    return;
                  }
                  if (c === '-' && i !== 0) {
                    this.inputValue = c;
                    break;
                  }
                }

                this.hasInputText1 = true;
                let c = value[value.length - 1];
                if (value.length === this.getMaxLength()) {
                  this.inputValue = c;
                }
                if (this.timeoutID1 !== -1) {
                  clearTimeout(this.timeoutID1);
                  this.timeoutID1 = -1;
                }
                if (this.inputValue !== '' && Number(this.inputValue) <= this.max &&
                  Number(this.inputValue) >= this.min) {
                  this.value = Number(this.inputValue);
                  this.onChange?.(this.value);
                  this.hasInputText1 = false;
                } else {
                  if (Number(this.inputValue) > this.max ||
                    (Number(this.inputValue) < this.min &&
                      this.inputValue.length <= this.min.toString().length)) {
                    this.inputValue = c;
                  }
                  if (value.length < this.getMaxLength()) {
                    this.timeoutID1 = setTimeout(() => {
                      if (this.inputValue !== '' && Number(this.inputValue) <= this.max &&
                        Number(this.inputValue) >= this.min) {
                        this.value = Number(this.inputValue);
                        this.onChange?.(this.value);
                      }
                      this.inputValue = this.value.toString();
                      this.hasInputText1 = false;
                      this.updateInlineEnableSate();
                    }, 1500);
                  }
                }
                this.updateInlineEnableSate();
              })
              .onSubmit((enterKey: EnterKeyType) => {
                if (this.timeoutID1 != -1) {
                  clearTimeout(this.timeoutID1);
                  this.timeoutID1 = -1;
                }
                this.hasInputText1 = false;
                this.value -= 1;
                if (Number(this.inputValue) >= this.min && Number(this.inputValue) <= this.max) {
                  this.value = Number(this.inputValue);
                  this.onChange?.(this.value);
                  this.updateInlineEnableSate();
                } else {
                  this.value += 1;
                  this.inputValue = this.value.toString();
                }
              })
              .focusable(true)
              .focusOnTouch(true)
              .onFocus(() => {
                this.focusText = FocusText.TEXT1;
                this.hasFocusText1 = true;
                this.controller1.caretPosition(this.value.toString().length);
              })
              .onBlur(() => {
                this.focusText = FocusText.NONE;
                this.hasFocusText1 = false;
              })
              .onClick((event: ClickEvent) => {
                this.focusText = FocusText.TEXT1;
                this.hasFocusText1 = true;
                this.focusWithTarget('InlineTextInput' + this.timeStamp.toString());
                this.controller1.caretPosition(this.value.toString().length);
              })
          }
          .direction(this.counterDirection)
          .margin({
            start: LengthMetrics.vp(CounterResource.COUNTER_INLINE_INPUT_TEXT_MARGIN),
            end: LengthMetrics.vp(CounterResource.COUNTER_INLINE_INPUT_TEXT_MARGIN)
          })
          .height('100%')
          .width(this.textWidth)
        } else {
          Row() {
            TextInput({
              text: this.hasInputText1 ? this.inputValue : this.value.toString(),
              controller: this.controller1
            })
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
              .key('InlineTextInput' + this.timeStamp.toString())
              .onKeyEvent((event: KeyEvent) => {
                this.focusCurrentText(FocusText.TEXT1)
                if (event.keyCode === CounterConstant.KEYCODE_ESC) {
                  this.resetFocusText();
                  event.stopPropagation();
                }
                if (event.type === KeyType.Down &&
                  event.keyCode === CounterConstant.KEYCODE_DPAD_UP) {
                  this.addValue();
                  event.stopPropagation();
                }
                if (event.type === KeyType.Down &&
                  event.keyCode === CounterConstant.KEYCODE_DPAD_DOWN) {
                  this.subValue();
                  event.stopPropagation();
                }
                if (event.type === KeyType.Down &&
                  event.keyCode === CounterConstant.KEYCODE_DPAD_LEFT) {
                  this.focusWithTarget('InlineTextInput' + this.timeStamp.toString());
                  event.stopPropagation();
                }
                if (event.type === KeyType.Down &&
                  event.keyCode === CounterConstant.KEYCODE_DPAD_RIGHT) {
                  this.focusWithTarget('InlineTextInput' + this.timeStamp.toString());
                  event.stopPropagation();
                }
              })
              .onChange((value: string) => {
                this.inputValue = value;
                for (let i = 0; i < value.length; i++) {
                  let c = value[i];
                  if (c === '+' || c === '*' || c === '#') {
                    this.value -= 1;
                    this.value += 1;
                    this.inputValue = this.value.toString();
                    return;
                  }
                  if (c === '-' && i !== 0) {
                    this.inputValue = c;
                    break;
                  }
                }

                this.hasInputText1 = true;
                let c = value[value.length -1];
                if (value.length === this.getMaxLength()) {
                  this.inputValue = c;
                }
                if (this.timeoutID1 !== -1) {
                  clearTimeout(this.timeoutID1);
                  this.timeoutID1 = -1;
                }
                if (this.inputValue !== '' && Number(this.inputValue) <= this.max &&
                  Number(this.inputValue) >= this.min) {
                  this.value = Number(this.inputValue);
                  this.onChange?.(this.value);
                  this.hasInputText1 = false;
                } else {
                  if (Number(this.inputValue) > this.max ||
                    (Number(this.inputValue) < this.min &&
                      this.inputValue.length <= this.min.toString().length)) {
                    this.inputValue = c;
                  }
                  if (value.length < this.getMaxLength()) {
                    this.timeoutID1 = setTimeout(() => {
                      if (this.inputValue !== '' && Number(this.inputValue) <= this.max &&
                        Number(this.inputValue) >= this.min) {
                        this.value = Number(this.inputValue);
                        this.onChange?.(this.value);
                      }
                      this.inputValue = this.value.toString()
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
                if (Number(this.inputValue) >= this.min && Number(this.inputValue) <= this.max) {
                  this.value = Number(this.inputValue);
                  this.onChange?.(this.value);
                  this.updateInlineEnableSate();
                } else {
                  this.value += 1;
                  this.inputValue = this.value.toString();
                }
              })
              .focusable(true)
              .focusOnTouch(true)
              .onFocus(() => {
                this.focusText = FocusText.TEXT1;
                this.hasFocusText1 = true;
                this.controller1.caretPosition(this.value.toString().length);
              })
              .onBlur(() => {
                this.focusText = FocusText.NONE;
                this.hasFocusText1 = false;
              })
              .onClick((event: ClickEvent) => {
                this.focusText = FocusText.TEXT1;
                this.hasFocusText1 = true;
                this.focusWithTarget('InlineTextInput' + this.timeStamp.toString());
                this.controller1.caretPosition(this.value.toString().length);
              })
          }
          .direction(this.counterDirection)
          .margin({
            start: LengthMetrics.vp(CounterResource.COUNTER_INLINE_INPUT_TEXT_MARGIN),
            end: LengthMetrics.vp(CounterResource.COUNTER_INLINE_INPUT_TEXT_MARGIN)
          })
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
              .strokeWidth(this.addBtnFocusWidh)
              .stroke(CounterResource.BUTTON_BORDER_FOCUSED_COLOR)
              .margin({ end: LengthMetrics.vp(2) })
              .fillOpacity(0)
            Image(CounterResource.BUTTON_ARROW_UP)
              .direction(this.counterDirection)
              .width(CounterResource.COUNTER_INLINE_BUTTON_ICON_WIDTH)
              .height(CounterResource.COUNTER_INLINE_BUTTON_ICON_HEIGHT)
              .fillColor(CounterResource.BUTTON_ICON_COLOR)
              .opacity(this.addOpacity)

            Button({ type: ButtonType.Normal, stateEffect: this.addBtnStateEffect })
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
                  this.addBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                }
              })
              .gesture(
                LongPressGesture({ repeat: true })
                  .onAction((event: GestureEvent) => {
                    if (event.repeat) {
                      this.addValue();
                    }
                    this.addBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                  })
              )
              .hoverEffect(this.choverEffect)
              .onHover((isHover: boolean) => {
                this.onHoverIncrease && this.onHoverIncrease(isHover);
              })
              .focusable(false)
              .onFocus(() => {
                this.addBtnFocusWidh = CounterResource.BUTTON_BORDER_FOCUSED_WIDTH;
                this.onFocusIncrease && this.onFocusIncrease();
              })
              .onBlur(() => {
                this.addBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                this.onBlurIncrease && this.onBlurIncrease();
              })
          }
          .direction(this.counterDirection)
          .width(CounterResource.COUNTER_INLINE_BUTTON_WIDTH)
          .height(CounterResource.COUNTER_INLINE_BUTTON_HEIGHT)
          .padding({ top: '1vp' })
          .borderWidth({ bottom: '1vp' })
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
              .strokeWidth(this.subBtnFocusWidh)
              .stroke(CounterResource.BUTTON_BORDER_FOCUSED_COLOR)
              .margin({ top: LengthMetrics.vp(1), end: LengthMetrics.vp(1), bottom: LengthMetrics.vp(2) })
              .fillOpacity(0)
            Image(CounterResource.BUTTON_ARROW_DOWN)
              .direction(this.counterDirection)
              .width(CounterResource.COUNTER_INLINE_BUTTON_ICON_WIDTH)
              .height(CounterResource.COUNTER_INLINE_BUTTON_ICON_HEIGHT)
              .fillColor(CounterResource.BUTTON_ICON_COLOR)
              .opacity(this.subOpacity)
            Button({ type: ButtonType.Normal, stateEffect: this.subBtnStateEffect })
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
                  this.subBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                }
              })
              .gesture(
                LongPressGesture({ repeat: true })
                  .onAction((event: GestureEvent) => {
                    if (event.repeat) {
                      this.subValue();
                    }
                    this.subBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                  })
              )
              .hoverEffect(this.choverEffect)
              .onHover((isHover: boolean) => {
                this.onHoverDecrease && this.onHoverDecrease(isHover);
              })
              .focusable(false)
              .onFocus(() => {
                this.subBtnFocusWidh = CounterResource.BUTTON_BORDER_FOCUSED_WIDTH;
                this.onFocusDecrease && this.onFocusDecrease();
              })
              .onBlur(() => {
                this.subBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                this.onBlurDecrease && this.onBlurDecrease();
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
        .borderWidth({ start: LengthMetrics.vp(CounterResource.COUNTER_BORDER_WIDTH_NUMBER) })
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
            text: this.hasInputText1 ? this.inputYear.toString() : this.getYear(),
            controller: this.controller1
          })
            .direction(this.counterDirection)
            .type(InputType.Number)
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
            .key('DateTextInput1' + this.timeStamp.toString())
            .onKeyEvent((event: KeyEvent) => {
              this.focusCurrentText(FocusText.TEXT1);
              if (event.keyCode === CounterConstant.KEYCODE_ESC) {
                this.resetFocusText();
                event.stopPropagation();
              }
              if (event.type === KeyType.Down &&
                event.keyCode === CounterConstant.KEYCODE_DPAD_UP) {
                this.addDate();
                event.stopPropagation();
              }
              if (event.type === KeyType.Down &&
                event.keyCode === CounterConstant.KEYCODE_DPAD_DOWN) {
                this.subDate();
                event.stopPropagation();
              }
              if (event.type === KeyType.Down &&
                event.keyCode === CounterConstant.KEYCODE_MOVE_HOME) {
                this.homeFocusText();
                event.stopPropagation();
              }
              if (event.type === KeyType.Down &&
                event.keyCode === CounterConstant.KEYCODE_MOVE_END) {
                this.endFocusText();
                event.stopPropagation();
              }
              if (event.type === KeyType.Down &&
                event.keyCode === CounterConstant.KEYCODE_DPAD_LEFT) {
                this.focusWithTarget('DateTextInput1' + this.timeStamp.toString());
                event.stopPropagation();
              }
              if (event.type === KeyType.Down &&
                event.keyCode === CounterConstant.KEYCODE_DPAD_RIGHT) {
                this.focusWithTarget('DateTextInput2' + this.timeStamp.toString());
              }
            })
            .onChange((value: string) => {
              if (value.length !== 4) {
                this.hasInputText1 = true;
              }
              this.inputYear = Number(value)
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
            })
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
            })
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
            .direction(this.counterDirection)
            .textAlign(TextAlign.Center)
            .fontSize(CounterResource.COUNTER_NUMBER_SIZE)
            .maxFontScale(CounterResource.COUNTER_NUMBER_MAX_FONT_SIZE_SCALE);
            .fontColor(CounterResource.COUNTER_TEXT_COLOR)
            .width('8vp')
          TextInput({
            text: this.hasInputText2 ? this.inputMoon.toString() : this.convertNumberToString(this.month),
            controller: this.controller2
          })
            .direction(this.counterDirection)
            .type(InputType.Number)
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
            .key('DateTextInput2' + this.timeStamp.toString())
            .onKeyEvent((event: KeyEvent) => {
              this.focusCurrentText(FocusText.TEXT2)
              if (event.keyCode === CounterConstant.KEYCODE_ESC) {
                this.resetFocusText();
                event.stopPropagation();
              }
              if (event.type === KeyType.Down &&
                event.keyCode === CounterConstant.KEYCODE_DPAD_DOWN) {
                this.subDate();
                this.updateDay();
                event.stopPropagation();
              }
              if (event.type === KeyType.Down &&
                event.keyCode === CounterConstant.KEYCODE_DPAD_UP) {
                this.addDate();
                this.updateDay();
                event.stopPropagation();
              }
              if (event.type === KeyType.Down &&
                event.keyCode === CounterConstant.KEYCODE_MOVE_HOME) {
                this.homeFocusText();
                event.stopPropagation();
              }
              if (event.type === KeyType.Down &&
                event.keyCode === CounterConstant.KEYCODE_MOVE_END) {
                this.endFocusText();
                event.stopPropagation();
              }
              if (event.type === KeyType.Down &&
                event.keyCode === CounterConstant.KEYCODE_DPAD_LEFT) {
                this.focusWithTarget('DateTextInput1' + this.timeStamp.toString());
              }
              if (event.type === KeyType.Down &&
                event.keyCode === CounterConstant.KEYCODE_DPAD_RIGHT) {
                this.focusWithTarget('DateTextInput3' + this.timeStamp.toString());
              }

              if (event.type === KeyType.Down &&
                event.keyCode === CounterConstant.KEYCODE_TAB) {
                event.stopPropagation();
                this.focusWithTarget('DateTextInput1' + this.timeStamp.toString());
              }
            })
            .onChange((value: string) => {
              this.inputMoon = Number(value);
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
            })
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
            })
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
            .direction(this.counterDirection)
            .textAlign(TextAlign.Center)
            .fontSize(CounterResource.COUNTER_NUMBER_SIZE)
            .maxFontScale(CounterResource.COUNTER_NUMBER_MAX_FONT_SIZE_SCALE);
            .fontColor(CounterResource.COUNTER_TEXT_COLOR)
            .width('8vp')
          TextInput({
            text: this.hasInputText3 ? this.inputDay.toString() : this.convertNumberToString(this.day),
            controller: this.controller3
          })
            .direction(this.counterDirection)
            .type(InputType.Number)
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
            .key('DateTextInput3' + this.timeStamp.toString())
            .onKeyEvent((event: KeyEvent) => {
              this.focusCurrentText(FocusText.TEXT3)
              if (event.keyCode === CounterConstant.KEYCODE_ESC) {
                this.resetFocusText();
                event.stopPropagation();
              }
              if (event.type === KeyType.Down &&
                event.keyCode === CounterConstant.KEYCODE_DPAD_DOWN) {
                this.subDate();
                event.stopPropagation();
              }
              if (event.type === KeyType.Down &&
                event.keyCode === CounterConstant.KEYCODE_DPAD_UP) {
                this.addDate();
                event.stopPropagation();
              }
              if (event.type === KeyType.Down &&
                event.keyCode === CounterConstant.KEYCODE_MOVE_HOME) {
                this.homeFocusText();
                event.stopPropagation();
              }
              if (event.type === KeyType.Down &&
                event.keyCode === CounterConstant.KEYCODE_MOVE_END) {
                this.endFocusText();
                event.stopPropagation();
              }
              if (event.type === KeyType.Down &&
                event.keyCode === CounterConstant.KEYCODE_DPAD_LEFT) {
                this.focusWithTarget('DateTextInput2' + this.timeStamp.toString());
              }

              if (event.type === KeyType.Down &&
                event.keyCode === CounterConstant.KEYCODE_DPAD_RIGHT) {
                this.focusWithTarget('DateTextInput3' + this.timeStamp.toString());
                event.stopPropagation();
              }

              if (event.type === KeyType.Down &&
                event.keyCode === CounterConstant.KEYCODE_TAB) {
                event.stopPropagation();
                this.focusWithTarget('DateTextInput1' + this.timeStamp.toString());
              }
            })
            .onChange((value: string) => {
              this.inputDay = Number(value)
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
            })
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
            })
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
        })

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
              .strokeWidth(this.addBtnFocusWidh)
              .stroke(CounterResource.BUTTON_BORDER_FOCUSED_COLOR)
              .margin({ end: LengthMetrics.vp(1) })
              .fillOpacity(0)
            Image(CounterResource.BUTTON_ARROW_UP)
              .direction(this.counterDirection)
              .width(CounterResource.COUNTER_INLINE_BUTTON_ICON_WIDTH)
              .height(CounterResource.COUNTER_INLINE_BUTTON_ICON_HEIGHT)
              .fillColor(CounterResource.BUTTON_ICON_COLOR)
              .opacity(this.addOpacity)
            Button({ type: ButtonType.Normal, stateEffect: this.addBtnStateEffect })
              .direction(this.counterDirection)
              .width(CounterResource.COUNTER_INLINE_BUTTON_WIDTH)
              .height(CounterResource.COUNTER_INLINE_BUTTON_HEIGHT)
              .backgroundColor(Color.Transparent)
              .opacity(this.addOpacity)
              .enabled(this.addBtnEnabled)
              .onClick((event: ClickEvent) => {
                this.addDate();
                if (event.source === SourceType.Mouse ||
                  event.source === SourceType.TouchScreen) {
                  this.addBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                }
              })
              .gesture(
                LongPressGesture({ repeat: true })
                  .onAction((event: GestureEvent) => {
                    if (event.repeat) {
                      this.addDate();
                    }
                    this.addBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                  })
              )
              .hoverEffect(this.choverEffect)
              .onHover((isHover: boolean) => {
                this.onHoverIncrease && this.onHoverIncrease(isHover);
              })
              .focusable(false)
              .onFocus(() => {
                this.addBtnFocusWidh = CounterResource.BUTTON_BORDER_FOCUSED_WIDTH;
                this.onFocusIncrease && this.onFocusIncrease();
              })
              .onBlur(() => {
                this.addBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                this.onBlurIncrease && this.onBlurIncrease();
              })
          }
          .width(CounterResource.COUNTER_INLINE_BUTTON_WIDTH)
          .height(CounterResource.COUNTER_INLINE_BUTTON_HEIGHT)
          .padding({ top: '1vp' })
          .borderWidth({ bottom: '1vp' })
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
              .strokeWidth(this.subBtnFocusWidh)
              .stroke(CounterResource.BUTTON_BORDER_FOCUSED_COLOR)
              .margin({ top: LengthMetrics.vp(1), end: LengthMetrics.vp(1), bottom: LengthMetrics.vp(2) })
              .fillOpacity(0)
            Image(CounterResource.BUTTON_ARROW_DOWN)
              .direction(this.counterDirection)
              .width(CounterResource.COUNTER_INLINE_BUTTON_ICON_WIDTH)
              .height(CounterResource.COUNTER_INLINE_BUTTON_ICON_HEIGHT)
              .fillColor(CounterResource.BUTTON_ICON_COLOR)
              .opacity(this.subOpacity)
            Button({ type: ButtonType.Normal, stateEffect: this.subBtnStateEffect })
              .direction(this.counterDirection)
              .width(CounterResource.COUNTER_INLINE_BUTTON_WIDTH)
              .height(CounterResource.COUNTER_INLINE_BUTTON_HEIGHT)
              .backgroundColor(Color.Transparent)
              .opacity(this.subOpacity)
              .enabled(this.subBtnEnabled)
              .onClick((event: ClickEvent) => {
                this.subDate();
                if (event.source === SourceType.Mouse ||
                  event.source === SourceType.TouchScreen) {
                  this.subBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                }
              })
              .gesture(
                LongPressGesture({ repeat: true })
                  .onAction((event: GestureEvent) => {
                    if (event.repeat) {
                      this.subDate();
                    }
                    this.subBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                  })
              )
              .hoverEffect(this.choverEffect)
              .onHover((isHover: boolean) => {
                this.onHoverDecrease && this.onHoverDecrease(isHover);
              })
              .focusable(false)
              .onFocus(() => {
                this.subBtnFocusWidh = CounterResource.BUTTON_BORDER_FOCUSED_WIDTH;
                this.onFocusDecrease && this.onFocusDecrease();
              })
              .onBlur(() => {
                this.subBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH;
                this.onBlurDecrease && this.onBlurDecrease();
              })
          }.width(CounterResource.COUNTER_INLINE_BUTTON_WIDTH)
          .height(CounterResource.COUNTER_INLINE_BUTTON_HEIGHT)
          .clip(true)
        }
        .direction(this.counterDirection)
        .width(CounterResource.COUNTER_INLINE_BUTTON_WIDTH)
        .height(CounterResource.COUNTER_INLINE_CONTAINER_HEIGHT)
        .borderWidth({ start: LengthMetrics.vp(CounterResource.COUNTER_BORDER_WIDTH_NUMBER) })
        .borderColor(CounterResource.COUNTER_BORDER_COLOR)
      }
      .direction(this.counterDirection)
      .height(CounterResource.COUNTER_INLINE_CONTAINER_HEIGHT)
      .borderWidth(CounterResource.COUNTER_BORDER_WIDTH)
      .borderColor(CounterResource.COUNTER_BORDER_COLOR)
      .borderRadius(CounterResource.COUNTER_INLINE_RADIUS)
      .clip(true)
    } else {

    }
  }
}
