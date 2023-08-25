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
  focusable?: boolean;
  step?: number;
  onHoverIncrease?: (isHover?: boolean) => void;
  onHoverDecrease?: (isHover?: boolean) => void;
  onFocusIncrease?: () => void;
  onFocusDecrease?: () => void;
  onBlurIncrease?: () => void;
  onBlurDecrease?: () => void;
}

export class InlineStyleOptions extends CommonOptions {
    value?: number;
    min?: number;
    max?: number;
    textWidth?: number;
    onChange?: (value: number) => void;
}

export class NumberStyleOptions extends InlineStyleOptions {
  label?: ResourceStr;
}

export class DateData{
  year: number;
  month: number;
  day: number;

  constructor(year: number, month: number, day: number) {
    this.year = year;
    this.month = month;
    this.day = day;
  }

  toString(): string {
    let date = this.year.toString() + "-";
    let month = this.month < 10 ? "0" + this.month.toString() : this.month.toString();
    date += month + "-";
    let day = this.day < 10 ? "0" + this.day.toString() : this.day.toString();
    date += day;
    return date;
  }
}

export class DateStyleOptions extends CommonOptions {
  year?: number;
  month?: number;
  day?: number;
  onDateChange?: (date: DateData) => void;
}

export class CounterStyleMap {
  [CounterType.LIST]: NumberStyleOptions;
  [CounterType.COMPACT]: NumberStyleOptions;
  [CounterType.INLINE]: InlineStyleOptions;
  [CounterType.INLINE_DATE]: DateStyleOptions;
}

export class CounterAttribute<Type extends keyof CounterStyleMap = keyof CounterStyleMap,
  Style extends CounterStyleMap[Type] = CounterStyleMap[Type]> {
  type: Type;
  counterOptions?: Style;
}

export class CounterOptions<Type extends keyof CounterStyleMap> {
  constructor(options: CounterAttribute<Type>) {
    this.type = options.type;
    this.counterOptions = options.counterOptions;
  }
  type: CounterType;
  counterOptions?: NumberStyleOptions | InlineStyleOptions | DateStyleOptions;
}

class CounterResource {
  // counter color
  static readonly BUTTON_BACKGROUD_COLOR = $r('sys.color.ohos_id_color_button_normal')
  static readonly BUTTON_ICON_COLOR = $r('sys.color.ohos_id_color_primary')
  static readonly BUTTON_BORDER_FOCUSED_COLOR = $r('sys.color.ohos_id_color_focused_outline')
  static readonly COUNTER_TEXT_COLOR = $r('sys.color.ohos_id_color_text_primary')
  static readonly COUNTER_BORDER_COLOR = $r('sys.color.ohos_id_color_component_normal')
  // button icon
  static readonly BUTTON_ADD_ICON = $r("app.media.ohos_ic_public_add")
  static readonly BUTTON_SUB_ICON = $r("app.media.ohos_ic_public_minus")
  static readonly BUTTON_ARROW_UP = $r('app.media.ohos_ic_public_arrow_up')
  static readonly BUTTON_ARROW_DOWN = $r('app.media.ohos_ic_public_arrow_down')

  // counter size
  static readonly BUTTON_BORDER_FOCUSED_WIDTH = '2vp'
  static readonly BUTTON_BORDER_BLUR_WIDTH = '0vp'
  static readonly COUNTER_BORDER_WIDTH = '1vp'
  static readonly COUNTER_LIST_LABEL_SIZE = $r('sys.float.ohos_id_text_size_body1')
  static readonly COUNTER_LIST_NUMBER_SIZE = $r('sys.float.ohos_id_text_size_body1')
  static readonly COUNTER_COMPACT_LABEL_SIZE = $r('sys.float.ohos_id_text_size_body2')
  static readonly COUNTER_NUMBER_SIZE = $r('sys.float.ohos_id_text_size_body1')
  static readonly COUNTER_LIST_LEFT_PADDING = $r('sys.float.ohos_id_default_padding_start')
  static readonly COUNTER_LIST_RIGHT_PADDING = $r('sys.float.ohos_id_default_padding_end')
  static readonly COUNTER_LIST_HEIGHT = '48vp'
  static readonly COUNTER_LIST_BUTTON_ICON_SIZE = '20vp'
  static readonly COUNTER_LIST_BUTTON_SIZE = '32vp'
  static readonly COUNTER_LIST_BUTTON_RADIUS = '16vp'
  static readonly COUNTER_LIST_BUTTON_TEXT_DISTANCE = '8vp'
  static readonly COUNTER_LIST_FOCUS_BORDER_SIZE = '30vp'
  static readonly COUNTER_LIST_FOCUS_BORDER_RADIUS = '15vp'
  static readonly COUNTER_LIST_BUTTON_HOT_SPOT_X = '-8vp'
  static readonly COUNTER_LIST_BUTTON_HOT_SPOT_Y = '-8vp'

  static readonly COUNTER_COMPACT_BUTTON_ICON_SIZE = '16vp'
  static readonly COUNTER_COMPACT_BUTTON_SIZE = '24vp'
  static readonly COUNTER_COMPACT_BUTTON_RADIUS = '12vp'
  static readonly COUNTER_COMPACT_BUTTON_TEXT_DISTANCE = '10vp'
  static readonly COUNTER_COMPACT_CONTAINER_HEIGHT = '28vp'
  static readonly COUNTER_COMPACT_CONTAINER_RADIUS = '14vp'
  static readonly COUNTER_COMPACT_CONTAINER_LABEL_DISTANCE = '8vp'
  static readonly COUNTER_COMPACT_FOCUS_BORDER_SIZE = '22vp'
  static readonly COUNTER_COMPACT_FOCUS_BORDER_RADIUS = '11vp'

  static readonly COUNTER_INLINE_BUTTON_ICON_WIDTH = '24vp'
  static readonly COUNTER_INLINE_BUTTON_ICON_HEIGHT = '12vp'
  static readonly COUNTER_INLINE_BUTTON_TEXT_DISTANCE = '12vp'
  static readonly COUNTER_INLINE_CONTAINER_HEIGHT = '32vp'
  static readonly COUNTER_INLINE_BUTTON_WIDTH = '32vp'
  static readonly COUNTER_INLINE_BUTTON_HEIGHT = '16vp'
  static readonly COUNTER_INLINE_RADIUS = '8vp'
  static readonly COUNTER_INLINE_FOCUS_BORDER_WIDTH = '28vp'
  static readonly COUNTER_INLINE_FOCUS_BORDER_HEIGHT = '13.5vp'
  static readonly COUNTER_INLINE_DATE_TEXT_MARGIN = '12vp'
  static readonly COUNTER_BUTTON_INITIAL_OPACITY = 1
  static readonly COUNTER_BUTTON_DISABLE_OPACITY = 0.4
}

class CounterConstant {
  static readonly COUNTER_MAX_YEAR = 5000
  static readonly COUNTER_MIN_YEAR = 1
  static readonly COUNTER_INITIAL_MONTH = 1
  static readonly COUNTER_INITIAL_DAY = 1
  static readonly COUNTER_INITIAL_STEP = 1

  static readonly COUNTER_TEN_NUMBER = 10
  static readonly COUNTER_MIN_MONTH = 1
  static readonly COUNTER_MAX_MONTH = 12
  static readonly COUNTER_MIN_DAY = 1
  static readonly KEYCODE_DPAD_UP = 2012
  static readonly KEYCODE_DPAD_DOWN = 2013
  static readonly KEYCODE_DPAD_LEFT = 2014
  static readonly KEYCODE_DPAD_RIGHT = 2015
  static readonly KEYCODE_MOVE_HOME = 2081
  static readonly KEYCODE_MOVE_END = 2082
  static readonly KEYCODE_TAB = 2049
  static readonly KEYCODE_ESC = 2070
  static readonly COUNTER_MIN_VALUE = 0
  static readonly COUNTER_MAX_VALUE = 999
}

@Component
export struct CounterComponent {
  @Prop  @Watch('onOptionsChange')  options: CounterOptions<keyof CounterStyleMap>;
  @State type: number = -1;
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
  @State value: number = 0;
  @State year: number = CounterConstant.COUNTER_MIN_YEAR;
  @State month: number = CounterConstant.COUNTER_INITIAL_MONTH;
  @State day: number = CounterConstant.COUNTER_INITIAL_DAY;
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
  private numberStrList: Array<string> = [ "00", "01", "02", "03", "04", "05", "06", "07", "08", "09"];

  private onHoverIncrease?: (isHover?: boolean) => void;
  private onHoverDecrease?: (isHover?: boolean) => void;
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


  private controller1: TextInputController = new TextInputController()
  private controller2: TextInputController = new TextInputController()
  private controller3: TextInputController = new TextInputController()

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
    if (this.options != undefined && this.options != null) {
      this.onOptionsChange();
    }
  }

  private updateNumberStyleOptions() {
    if (this.numberStyleOptions.label == undefined) {
      this.numberStyleOptions.label = "";
    }
    if (this.numberStyleOptions.value != undefined ) {
      this.value = this.numberStyleOptions.value;
      this.inputValue = this.value.toString();
    }
    if (this.numberStyleOptions.min != undefined &&
        this.numberStyleOptions.min < this.max &&
        this.numberStyleOptions.min >= this.min) {
      this.min = this.numberStyleOptions.min;
    }
    if (this.numberStyleOptions.max != undefined &&
        this.numberStyleOptions.max > this.min &&
        this.numberStyleOptions.max <= this.max) {
      this.max = this.numberStyleOptions.max;
    }
    if (this.numberStyleOptions.textWidth != undefined) {
      this.textWidth = this.numberStyleOptions.textWidth;
      if (this.textWidth  < 0) {
        this.textWidth = 0;
      }
      this.hasTextWidth = true;
    }
    if (this.value <= this.min) {
      this.subOpacity = CounterResource.COUNTER_BUTTON_DISABLE_OPACITY
      this.subBtnStateEffect = false
      this.subBtnEnabled = false
      this.value = this.min
      this.inputValue = this.value.toString();
    }
    if (this.value >= this.max) {
      this.addOpacity = CounterResource.COUNTER_BUTTON_DISABLE_OPACITY
      this.addBtnStateEffect = false
      this.addBtnEnabled = false
      this.value = this.max
      this.inputValue = this.value.toString();
    }
    if (this.numberStyleOptions.step != undefined) {
      this.step = this.numberStyleOptions.step;
    }
    this.updateNumberStyleOptionsEvent();
  }

  private updateNumberStyleOptionsEvent() {
    if (this.numberStyleOptions.onHoverIncrease != undefined) {
      this.onHoverIncrease = this.numberStyleOptions.onHoverIncrease;
    }
    if (this.numberStyleOptions.onHoverDecrease != undefined) {
      this.onHoverDecrease = this.numberStyleOptions.onHoverDecrease;
    }
    if (this.numberStyleOptions.onFocusIncrease != undefined) {
      this.onFocusIncrease = this.numberStyleOptions.onFocusIncrease;
    }
    if (this.numberStyleOptions.onFocusDecrease != undefined) {
      this.onFocusDecrease = this.numberStyleOptions.onFocusDecrease;
    }
    if (this.numberStyleOptions.onBlurIncrease != undefined) {
      this.onBlurIncrease = this.numberStyleOptions.onBlurIncrease;
    }
    if (this.numberStyleOptions.onBlurDecrease != undefined) {
      this.onBlurDecrease = this.numberStyleOptions.onBlurDecrease;
    }
    if (this.numberStyleOptions.onChange != undefined) {
      this.onChange = this.numberStyleOptions.onChange;
    }
    if (this.numberStyleOptions.focusable != undefined) {
      this.focusEnable = this.numberStyleOptions.focusable;
    }
  }

  private updateInlineStyleOptions() {
    if (this.inlineStyleOptions.value != undefined) {
        this.value = this.inlineStyleOptions.value;
        this.inputValue = this.value.toString();
    }
    if (this.inlineStyleOptions.min != undefined) {
      this.min = this.inlineStyleOptions.min;
    }
    if (this.inlineStyleOptions.max != undefined) {
      this.max = this.inlineStyleOptions.max;
    }
    if (this.min > this.max) {
      this.min = this.max;
    }

    if (this.inlineStyleOptions.textWidth != undefined) {
      this.textWidth = this.inlineStyleOptions.textWidth;
      if (this.textWidth  < 0) {
        this.textWidth = 0;
      }
      this.hasTextWidth = true;
    }
    if (this.value <= this.min) {
      this.subOpacity = CounterResource.COUNTER_BUTTON_DISABLE_OPACITY
      this.subBtnStateEffect = false
      this.subBtnEnabled = false
      this.value = this.min
      this.inputValue = this.value.toString();
    }
    if (this.value >= this.max) {
      this.addOpacity = CounterResource.COUNTER_BUTTON_DISABLE_OPACITY
      this.addBtnStateEffect = false
      this.addBtnEnabled = false
      this.value = this.max
      this.inputValue = this.value.toString();
    }
    if (this.inlineStyleOptions.step != undefined) {
      this.step = this.inlineStyleOptions.step;
    }
    this.updateInlineStyleOptionsEvent();
  }

  private updateInlineStyleOptionsEvent() {
    if (this.inlineStyleOptions.onHoverIncrease != undefined) {
      this.onHoverIncrease = this.inlineStyleOptions.onHoverIncrease;
    }
    if (this.inlineStyleOptions.onHoverDecrease != undefined) {
      this.onHoverDecrease = this.inlineStyleOptions.onHoverDecrease;
    }
    if (this.inlineStyleOptions.onFocusIncrease != undefined) {
      this.onFocusIncrease = this.inlineStyleOptions.onFocusIncrease;
    }
    if (this.inlineStyleOptions.onFocusDecrease != undefined) {
      this.onFocusDecrease = this.inlineStyleOptions.onFocusDecrease;
    }
    if (this.inlineStyleOptions.onBlurIncrease != undefined) {
      this.onBlurIncrease = this.inlineStyleOptions.onBlurIncrease;
    }
    if (this.inlineStyleOptions.onBlurDecrease != undefined) {
      this.onBlurDecrease = this.inlineStyleOptions.onBlurDecrease;
    }
    if (this.inlineStyleOptions.onChange != undefined) {
      this.onChange = this.inlineStyleOptions.onChange;
    }
    if (this.inlineStyleOptions.focusable != undefined) {
      this.focusEnable = this.inlineStyleOptions.focusable;
    }
  }

  private updateDateStyleOptions() {
    if (this.dateStyleOptions.step != undefined) {
      this.step = this.dateStyleOptions.step;
    }
    if (this.dateStyleOptions.onHoverIncrease != undefined) {
      this.onHoverIncrease = this.dateStyleOptions.onHoverIncrease;
    }
    if (this.dateStyleOptions.onHoverDecrease != undefined) {
      this.onHoverDecrease = this.dateStyleOptions.onHoverDecrease;
    }
    if (this.dateStyleOptions.onFocusIncrease != undefined) {
      this.onFocusIncrease = this.dateStyleOptions.onFocusIncrease;
    }
    if (this.dateStyleOptions.onFocusDecrease != undefined) {
      this.onFocusDecrease = this.dateStyleOptions.onFocusDecrease;
    }
    if (this.dateStyleOptions.onBlurIncrease != undefined) {
      this.onBlurIncrease = this.dateStyleOptions.onBlurIncrease;
    }
    if (this.dateStyleOptions.onBlurDecrease != undefined) {
      this.onBlurDecrease = this.dateStyleOptions.onBlurDecrease;
    }
    if (this.dateStyleOptions.year != undefined &&
    this.dateStyleOptions.year >= this.minYear &&
    this.dateStyleOptions.year <= this.maxYear) {
      this.year = this.dateStyleOptions.year;
    }
    if (this.dateStyleOptions.month != undefined &&
    this.dateStyleOptions.month <= CounterConstant.COUNTER_MAX_MONTH &&
    this.dateStyleOptions.month >= CounterConstant.COUNTER_MIN_MONTH) {
      this.month = this.dateStyleOptions.month;
    }
    if (this.dateStyleOptions.day != undefined &&
    this.dateStyleOptions.day <= this.getDayNumber() &&
    this.dateStyleOptions.day >= CounterConstant.COUNTER_MIN_DAY) {
      this.day = this.dateStyleOptions.day;
    }
    if (this.dateStyleOptions.onDateChange != undefined) {
      this.onDateChange = this.dateStyleOptions.onDateChange;
    }
    if (this.dateStyleOptions.focusable != undefined) {
      this.focusEnable = this.dateStyleOptions.focusable;
    }
    this.updateDay();
  }

  private onOptionsChange() {
    this.type = this.options.type;
    if (this.type == CounterType.LIST ||
        this.type == CounterType.COMPACT) {
      this.numberStyleOptions = this.options.counterOptions;
      this.updateNumberStyleOptions();
    } else if (this.type == CounterType.INLINE) {
      this.inlineStyleOptions = this.options.counterOptions;
      this.updateInlineStyleOptions();
    } else if (this.type == CounterType.INLINE_DATE) {
      this.dateStyleOptions = this.options.counterOptions;
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
      this.addBtnEnabled = true
    }
    if (this.value <= this.min) {
      this.value = this.min
      this.subOpacity = CounterResource.COUNTER_BUTTON_DISABLE_OPACITY
      this.subBtnStateEffect = false
      this.subBtnEnabled = false
    } else {
      if (this.subOpacity == CounterResource.COUNTER_BUTTON_DISABLE_OPACITY) {
        this.subOpacity = CounterResource.COUNTER_BUTTON_INITIAL_OPACITY
      }
      if (!this.subBtnStateEffect) {
        this.subBtnStateEffect = true
      }
      if (!this.subBtnEnabled) {
        this.subBtnEnabled = true
      }
    }
    this.focusText1();
  }

  private focusText1() {
    if (this.type == CounterType.INLINE) {
      if (this.focusText == FocusText.NONE) {
        this.focusText = FocusText.TEXT1
        this.hasFocusText1 = true
        this.focusWithTarget("InlineTextInput" + this.timeStamp.toString())
      }
    }
  }

  private addValue(): void {
    if (this.addBtnStateEffect) {
      this.value += this.step
    }

    if (!this.subBtnStateEffect) {
      this.subBtnStateEffect = true;
      this.subOpacity = CounterResource.COUNTER_BUTTON_INITIAL_OPACITY;
      this.subBtnEnabled = true;
    }
    if (this.value >= this.max) {
      this.value = this.max;
      this.addOpacity = CounterResource.COUNTER_BUTTON_DISABLE_OPACITY
      this.addBtnStateEffect = false
      this.addBtnEnabled = false
    } else {
      if (this.addOpacity == CounterResource.COUNTER_BUTTON_DISABLE_OPACITY) {
        this.addOpacity = CounterResource.COUNTER_BUTTON_INITIAL_OPACITY
      }
      if (!this.addBtnStateEffect) {
        this.addBtnStateEffect = true
      }
      if (!this.addBtnEnabled) {
        this.addBtnEnabled = true
      }
    }

    this.focusText1();
  }

  private getDayNumber(): number {
    switch(this.month) {
      case 1:
      case 3:
      case 5:
      case 7:
      case 8:
      case 10:
      case 12:
        return 31;
        break;
      case 4:
      case 6:
      case 9:
      case 11:
        return 30;
        break;
      case 2:
        if ((this.year % 4 == 0 &&
            this.year % 100 != 0) ||
            this.year % 400 == 0) {
          return 29
        } else {
          return 28;
        }
        break
      default:
        break
    }
  }

  private subDate(): void {
    if (this.focusText == FocusText.TEXT1) {
      if (this.subBtnStateEffect) {
        this.inputYear = this.year
        this.year -= this.step;
        if (!this.hasFocusText1) {
          this.hasFocusText1 = true;
        }
      }
      if (!this.addBtnStateEffect) {
        this.addBtnStateEffect = true;
        this.addOpacity = CounterResource.COUNTER_BUTTON_INITIAL_OPACITY;
        this.addBtnEnabled = true
      }
      if (this.year <= this.minYear) {
        this.subOpacity = CounterResource.COUNTER_BUTTON_DISABLE_OPACITY
        this.subBtnStateEffect = false
        this.subBtnEnabled = false
      } else {
        if (this.subOpacity == CounterResource.COUNTER_BUTTON_DISABLE_OPACITY) {
          this.subOpacity = CounterResource.COUNTER_BUTTON_INITIAL_OPACITY
        }
        if (!this.subBtnStateEffect) {
          this.subBtnStateEffect = true
        }
        if (!this.subBtnEnabled) {
          this.subBtnEnabled = true
        }
      }
    } else if (this.focusText == FocusText.TEXT2) {
      this.month -= this.step % CounterConstant.COUNTER_MAX_MONTH
      if (this.month < CounterConstant.COUNTER_MIN_MONTH) {
        this.month += CounterConstant.COUNTER_MAX_MONTH
      }
      if (!this.hasFocusText2) {
        this.hasFocusText2 = true;
      }
    } else if (this.focusText == FocusText.TEXT3) {
      this.day -= this.step % this.getDayNumber()
      if (this.day < CounterConstant.COUNTER_MIN_DAY) {
        this.day += this.getDayNumber()
      }
      if (!this.hasFocusText3) {
        this.hasFocusText3 = true;
      }
    } else {
      this.focusDayWitdhSub();
    }
  }

  private focusDayWitdhSub() {
    this.focusText = FocusText.TEXT3
    this.hasFocusText3 = true
    this.day -= this.step % this.getDayNumber()
    if (this.day < CounterConstant.COUNTER_MIN_DAY) {
      this.day += this.getDayNumber()
    }
    this.focusWithTarget("DateTextInput3" + this.timeStamp.toString())
  }

  private addDate(): void {
    if (this.focusText == FocusText.TEXT1) {
      if (this.addBtnStateEffect) {
        this.inputYear = this.year
        this.year += this.step
        if (!this.hasFocusText1) {
          this.hasFocusText1 = true;
        }
      }
      if (!this.subBtnStateEffect) {
        this.subBtnStateEffect = true;
        this.subOpacity = CounterResource.COUNTER_BUTTON_INITIAL_OPACITY;
        this.subBtnEnabled = true
      }
      if (this.year >= this.maxYear) {
        this.addOpacity = CounterResource.COUNTER_BUTTON_DISABLE_OPACITY
        this.addBtnStateEffect = false
        this.addBtnEnabled = false
      } else {
        if (this.addOpacity == CounterResource.COUNTER_BUTTON_DISABLE_OPACITY) {
          this.addOpacity = CounterResource.COUNTER_BUTTON_INITIAL_OPACITY;
        }
        if (!this.addBtnStateEffect) {
          this.addBtnStateEffect = true
        }
        if (!this.addBtnEnabled) {
          this.addBtnEnabled = true
        }
      }
    } else if (this.focusText == FocusText.TEXT2) {
      this.month += this.step % CounterConstant.COUNTER_MAX_MONTH
      if (this.month > CounterConstant.COUNTER_MAX_MONTH) {
        this.month -= CounterConstant.COUNTER_MAX_MONTH
      }
      if (!this.hasFocusText2) {
        this.hasFocusText2 = true;
      }
    } else if (this.focusText == FocusText.TEXT3) {
      this.day += this.step % this.getDayNumber()
      if (this.day > this.getDayNumber()) {
        this.day -= this.getDayNumber()
      }
      if (!this.hasFocusText3) {
        this.hasFocusText3 = true;
      }
    } else {
      this.focusDayWithAdd();
    }
  }

  private focusDayWithAdd() {
    this.focusText = FocusText.TEXT3
    this.hasFocusText3 = true
    this.day += this.step % this.getDayNumber()
    if (this.day > this.getDayNumber()) {
      this.day -= this.getDayNumber()
    }
    this.focusWithTarget("DateTextInput3" + this.timeStamp.toString())
  }

  private updateInlineEnableSate() {
    if (this.value >= this.max) {
      this.addOpacity = CounterResource.COUNTER_BUTTON_DISABLE_OPACITY
      this.addBtnStateEffect = false
      this.addBtnEnabled = false
    } else {
      this.addOpacity = CounterResource.COUNTER_BUTTON_INITIAL_OPACITY
      this.addBtnStateEffect = true
      this.addBtnEnabled = true
    }
    if (this.value <= this.min) {
      this.subOpacity = CounterResource.COUNTER_BUTTON_DISABLE_OPACITY
      this.subBtnStateEffect = false
      this.subBtnEnabled = false
    } else {
      this.subOpacity = CounterResource.COUNTER_BUTTON_INITIAL_OPACITY
      this.subBtnStateEffect = true
      this.subBtnEnabled = true
    }
  }

  private updateDateEnableSate() {
    if (this.year == this.maxYear && this.focusText == FocusText.TEXT1) {
      this.addOpacity = CounterResource.COUNTER_BUTTON_DISABLE_OPACITY
      this.addBtnStateEffect = false
      this.addBtnEnabled = false
    } else {
      if (this.addOpacity == CounterResource.COUNTER_BUTTON_DISABLE_OPACITY) {
        this.addOpacity = CounterResource.COUNTER_BUTTON_INITIAL_OPACITY
      }
      if (!this.addBtnStateEffect) {
        this.addBtnStateEffect = true
      }
      if (!this.addBtnEnabled) {
        this.addBtnEnabled = true
      }
    }
    if (this.year == this.minYear && this.focusText == FocusText.TEXT1) {
      this.subOpacity = CounterResource.COUNTER_BUTTON_DISABLE_OPACITY
      this.subBtnStateEffect = false
      this.subBtnEnabled = false
    } else {
      if (this.subOpacity == CounterResource.COUNTER_BUTTON_DISABLE_OPACITY) {
        this.subOpacity = CounterResource.COUNTER_BUTTON_INITIAL_OPACITY
      }
      if (!this.subBtnStateEffect) {
        this.subBtnStateEffect = true
      }
      if (!this.subBtnEnabled) {
        this.subBtnEnabled = true
      }
    }
  }

  private updateDay() {
    if (this.day > this.getDayNumber()) {
      this.day = this.getDayNumber();
    }
  }

  private resetFocusText() {
    this.focusText = FocusText.NONE
    this.hasFocusText1 = false
    this.hasFocusText2 = false
    this.hasFocusText3 = false
  }

  private resetFocusButton() {
    if (this.addBtnFocusWidh == CounterResource.BUTTON_BORDER_FOCUSED_WIDTH) {
      this.addBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH
      this.onBlurIncrease && this.onBlurIncrease()
    }
    if (this.subBtnFocusWidh == CounterResource.BUTTON_BORDER_FOCUSED_WIDTH) {
      this.subBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH
      this.onBlurDecrease && this.onBlurDecrease()
    }
  }

  private homeFocusText() {
    this.focusWithTarget("DateTextInput1" + this.timeStamp.toString())
  }

  private endFocusText() {
    this.focusWithTarget("DateTextInput3" + this.timeStamp.toString())
  }

  private homeFirstValue() {
    this.value = this.min;
    if (!this.addBtnStateEffect) {
      this.addBtnStateEffect = true;
      this.addOpacity = CounterResource.COUNTER_BUTTON_INITIAL_OPACITY;
      this.addBtnEnabled = true
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
      if (!this.addBtnStateEffect) {
        this.addBtnStateEffect = true;
        this.addOpacity = CounterResource.COUNTER_BUTTON_INITIAL_OPACITY;
        this.addBtnEnabled = true
      }
      this.subOpacity = CounterResource.COUNTER_BUTTON_DISABLE_OPACITY
      this.subBtnStateEffect = false
      this.subBtnEnabled = false
    }
    if (this.value >= this.max) {
      if (!this.subBtnStateEffect) {
        this.subBtnStateEffect = true;
        this.subOpacity = CounterResource.COUNTER_BUTTON_INITIAL_OPACITY;
        this.subBtnEnabled = true;
      }
      this.addOpacity = CounterResource.COUNTER_BUTTON_DISABLE_OPACITY
      this.addBtnStateEffect = false
      this.addBtnEnabled = false
    }
  }

  private getValue() {
    return this.hasInputText1? this.inputValue : this.value.toString()
  }

  private getValueLength() {
    return this.getValue().length > 0 ? this.getValue().length : 1
  }

  private getYear() {
    let year: string = this.year.toString()
    if (year.length == 1) {
      year = "000" + year;
    } else if (year.length == 2) {
      year = "00" + year;
    } else if (year.length == 3) {
      year = "0" + year;
    } else {
      year = year;
    }
    return year;
  }

  private focusWithTarget(key: string) {
    setTimeout(()=>{
      var res = focusControl.requestFocus(key)
      if (res) {
        console.log('Request success')
      } else {
        console.log('Request failed')
      }
    });
  }

  private focusCurrentText(text: FocusText) {
    if (text == FocusText.TEXT1) {
      if (this.focusText == FocusText.NONE) {
        this.focusText = FocusText.TEXT1
      }
      if (!this.hasFocusText1) {
        this.hasFocusText1 = true;
      }
    } else if (text == FocusText.TEXT2) {
      if (this.focusText == FocusText.NONE) {
        this.focusText = FocusText.TEXT2
      }
      if (!this.hasFocusText2) {
        this.hasFocusText2 = true;
      }
    } else if (text == FocusText.TEXT3) {
      if (this.focusText == FocusText.NONE) {
        this.focusText = FocusText.TEXT3
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

  build() {
    if (this.type == CounterType.LIST) {
      RelativeContainer() {
        Text(this.numberStyleOptions.label)
          .fontSize(CounterResource.COUNTER_LIST_LABEL_SIZE)
          .fontColor(CounterResource.COUNTER_TEXT_COLOR)
          .margin({ left: CounterResource.COUNTER_LIST_LEFT_PADDING})
          .alignRules({
            center: {anchor: "__container__", align: VerticalAlign.Center},
            left: {anchor: "__container__", align: HorizontalAlign.Start}
          })
          .id("Text")
        Row() {
          Stack() {
            Rect()
              .width(CounterResource.COUNTER_LIST_FOCUS_BORDER_SIZE)
              .height(CounterResource.COUNTER_LIST_FOCUS_BORDER_SIZE)
              .radius(CounterResource.COUNTER_LIST_FOCUS_BORDER_RADIUS)
              .strokeWidth(this.subBtnFocusWidh)
              .stroke(CounterResource.BUTTON_BORDER_FOCUSED_COLOR)
              .fillOpacity(0)
            Image(CounterResource.BUTTON_SUB_ICON)
              .width(CounterResource.COUNTER_LIST_BUTTON_ICON_SIZE)
              .height(CounterResource.COUNTER_LIST_BUTTON_ICON_SIZE)
              .fillColor(CounterResource.BUTTON_ICON_COLOR)
              .opacity(this.subOpacity)
            Button({ type: ButtonType.Circle, stateEffect: this.subBtnStateEffect })
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
              .key("ListSubButton" + this.timeStamp.toString())
              .onKeyEvent((event: KeyEvent) => {
                this.subBtnFocusWidh = CounterResource.BUTTON_BORDER_FOCUSED_WIDTH
                if (event.keyCode == CounterConstant.KEYCODE_ESC) {
                  this.resetFocusButton();
                  event.stopPropagation();
                }
                if (event.type == KeyType.Down &&
                    event.keyCode == CounterConstant.KEYCODE_MOVE_HOME) {
                  event.stopPropagation()
                  this.homeFirstValue()
                  this.focusWithTarget("ListAddButton" + this.timeStamp.toString())
                }
                if (event.type == KeyType.Down &&
                    event.keyCode == CounterConstant.KEYCODE_MOVE_END) {
                  event.stopPropagation();
                  if (this.addBtnStateEffect) {
                    this.addBtnStateEffect = false;
                    this.addOpacity = CounterResource.COUNTER_BUTTON_DISABLE_OPACITY;
                    this.addBtnEnabled = false
                  }
                  this.endLastValue()
                  this.focusWithTarget("ListAddButton" + this.timeStamp.toString())
                }
              })
              .onClick((event: ClickEvent) => {
                this.subValue()
                this.onChange && this.onChange(this.value)
                if (event.source == SourceType.Mouse ||
                    event.source == SourceType.TouchScreen) {
                  this.subBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH
                }
              })
              .gesture(
                LongPressGesture({ repeat: true })
                  .onAction((event: GestureEvent) => {
                    if (event.repeat) {
                      this.subValue()
                      this.onChange && this.onChange(this.value)
                    }
                    this.subBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH
                  })
              )
              .hoverEffect(this.choverEffect)
              .onHover((isHover: boolean) => {
                this.onHoverDecrease && this.onHoverDecrease(isHover)
              })
              .focusable(this.focusEnable)
              .onFocus(() => {
                this.subBtnFocusWidh = CounterResource.BUTTON_BORDER_FOCUSED_WIDTH
                this.onFocusDecrease && this.onFocusDecrease()
                this.updateButtonStatus();
              })
              .onBlur(() => {
                this.subBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH
                this.onBlurDecrease && this.onBlurDecrease()
              })
          }.width(CounterResource.COUNTER_LIST_BUTTON_SIZE)
          .height(CounterResource.COUNTER_LIST_BUTTON_SIZE)
          .borderRadius(CounterResource.COUNTER_LIST_BUTTON_RADIUS)
          .clip(true)

          if (this.hasTextWidth) {
            Text(this.value.toString())
              .width(this.textWidth.toString())
              .textAlign(TextAlign.Center)
              .fontSize(CounterResource.COUNTER_LIST_NUMBER_SIZE)
              .fontColor(CounterResource.COUNTER_TEXT_COLOR)
              .margin({
                left: CounterResource.COUNTER_LIST_BUTTON_TEXT_DISTANCE,
                right: CounterResource.COUNTER_LIST_BUTTON_TEXT_DISTANCE
              })
          } else {
            Text(this.value.toString())
              .textAlign(TextAlign.Center)
              .fontSize(CounterResource.COUNTER_LIST_NUMBER_SIZE)
              .fontColor(CounterResource.COUNTER_TEXT_COLOR)
              .margin({
                left: CounterResource.COUNTER_LIST_BUTTON_TEXT_DISTANCE,
                right: CounterResource.COUNTER_LIST_BUTTON_TEXT_DISTANCE
              })
          }

          Stack() {
            Rect()
              .width(CounterResource.COUNTER_LIST_FOCUS_BORDER_SIZE)
              .height(CounterResource.COUNTER_LIST_FOCUS_BORDER_SIZE)
              .radius(CounterResource.COUNTER_LIST_FOCUS_BORDER_RADIUS)
              .strokeWidth(this.addBtnFocusWidh)
              .stroke(CounterResource.BUTTON_BORDER_FOCUSED_COLOR)
              .fillOpacity(0)
            Image(CounterResource.BUTTON_ADD_ICON)
              .width(CounterResource.COUNTER_LIST_BUTTON_ICON_SIZE)
              .height(CounterResource.COUNTER_LIST_BUTTON_ICON_SIZE)
              .fillColor(CounterResource.BUTTON_ICON_COLOR)
              .opacity(this.addOpacity)
            Button({ type: ButtonType.Circle, stateEffect: this.addBtnStateEffect })
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
              .key("ListAddButton" + this.timeStamp.toString())
              .onKeyEvent((event: KeyEvent) => {
                this.addBtnFocusWidh = CounterResource.BUTTON_BORDER_FOCUSED_WIDTH
                if (event.keyCode == CounterConstant.KEYCODE_ESC) {
                  this.resetFocusButton();
                  event.stopPropagation();
                }
                if (event.type == KeyType.Down &&
                    event.keyCode == CounterConstant.KEYCODE_MOVE_HOME) {
                  event.stopPropagation();
                  this.homeFirstValue()
                  if (this.subBtnStateEffect) {
                    this.subBtnStateEffect = false;
                    this.subOpacity = CounterResource.COUNTER_BUTTON_DISABLE_OPACITY;
                    this.subBtnEnabled = false
                  }
                  this.focusWithTarget("ListAddButton" + this.timeStamp.toString())
                }
                if (event.type == KeyType.Down &&
                    event.keyCode == CounterConstant.KEYCODE_MOVE_END) {
                  event.stopPropagation();
                  this.endLastValue()
                  this.focusWithTarget("ListSubButton" + this.timeStamp.toString())
                }
              })
              .onClick((event: ClickEvent) => {
                this.addValue()
                this.onChange && this.onChange(this.value)
                if (event.source == SourceType.Mouse ||
                    event.source == SourceType.TouchScreen) {
                  this.addBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH
                }
              })
              .gesture(
                LongPressGesture({ repeat: true })
                  .onAction((event: GestureEvent) => {
                    if (event.repeat) {
                      this.addValue()
                      this.onChange && this.onChange(
                        this.value)
                    }
                    this.addBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH
                  })
              )
              .hoverEffect(this.choverEffect)
              .onHover((isHover: boolean) => {
                this.onHoverIncrease && this.onHoverIncrease(isHover)
              })
              .focusable(this.focusEnable)
              .onFocus(() => {
                this.addBtnFocusWidh = CounterResource.BUTTON_BORDER_FOCUSED_WIDTH
                this.onFocusIncrease && this.onFocusIncrease()
                this.updateButtonStatus();
              })
              .onBlur(() => {
                this.addBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH
                this.onBlurIncrease && this.onBlurIncrease()
              })
          }.width(CounterResource.COUNTER_LIST_BUTTON_SIZE)
          .height(CounterResource.COUNTER_LIST_BUTTON_SIZE)
          .borderRadius(CounterResource.COUNTER_LIST_BUTTON_RADIUS)
          .clip(true)
        }
        .height(CounterResource.COUNTER_LIST_BUTTON_SIZE)
        .margin({ right: CounterResource.COUNTER_LIST_RIGHT_PADDING })
        .alignRules({
          center: { anchor: "__container__", align: VerticalAlign.Center },
          right: { anchor: "__container__", align: HorizontalAlign.End }
        })
        .tabIndex(0)
        .id("Row1")
      }
      .width('100%')
      .height(CounterResource.COUNTER_LIST_HEIGHT)
    } else if (this.type == CounterType.COMPACT) {
      Column() {
        Row() {
          Stack() {
            Rect()
              .width(CounterResource.COUNTER_COMPACT_FOCUS_BORDER_SIZE)
              .height(CounterResource.COUNTER_COMPACT_FOCUS_BORDER_SIZE)
              .radius(CounterResource.COUNTER_COMPACT_FOCUS_BORDER_RADIUS)
              .strokeWidth(this.subBtnFocusWidh)
              .stroke(CounterResource.BUTTON_BORDER_FOCUSED_COLOR)
              .fillOpacity(0)
            Image(CounterResource.BUTTON_SUB_ICON)
              .width(CounterResource.COUNTER_COMPACT_BUTTON_ICON_SIZE)
              .height(CounterResource.COUNTER_COMPACT_BUTTON_ICON_SIZE)
              .fillColor(CounterResource.BUTTON_ICON_COLOR)
              .opacity(this.subOpacity)
            Button({ type: ButtonType.Circle, stateEffect: this.subBtnStateEffect })
            .width(CounterResource.COUNTER_COMPACT_BUTTON_SIZE)
            .height(CounterResource.COUNTER_COMPACT_BUTTON_SIZE)
            .backgroundColor(CounterResource.BUTTON_BACKGROUD_COLOR)
            .opacity(this.subOpacity)
            .enabled(this.subBtnEnabled)
            .key("CompactSubButton" + this.timeStamp.toString())
            .onKeyEvent((event: KeyEvent) => {
              this.subBtnFocusWidh = CounterResource.BUTTON_BORDER_FOCUSED_WIDTH
              if (event.keyCode == CounterConstant.KEYCODE_ESC) {
                this.resetFocusButton();
                event.stopPropagation();
              }
              if (event.type == KeyType.Down &&
                  event.keyCode == CounterConstant.KEYCODE_MOVE_HOME) {
                event.stopPropagation();
                this.homeFirstValue()
                this.focusWithTarget("CompactAddButton" + this.timeStamp.toString())
              }
              if (event.type == KeyType.Down &&
                  event.keyCode == CounterConstant.KEYCODE_MOVE_END) {
                event.stopPropagation();
                this.endLastValue()
                if (this.addBtnStateEffect) {
                  this.addBtnStateEffect = false;
                  this.addOpacity = CounterResource.COUNTER_BUTTON_DISABLE_OPACITY;
                  this.addBtnEnabled = false
                }
                this.focusWithTarget("CompactSubButton" + this.timeStamp.toString())
              }
            })
            .onClick((event: ClickEvent) => {
              this.subValue()
              this.onChange && this.onChange(this.value)
              if (event.source == SourceType.Mouse ||
                  event.source == SourceType.TouchScreen) {
                this.subBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH
              }
            })
            .gesture(
              LongPressGesture({ repeat: true })
                .onAction((event: GestureEvent) => {
                  if (event.repeat) {
                    this.subValue()
                    this.onChange && this.onChange(
                      this.value)
                  }
                  if (event.source == SourceType.Mouse ||
                      event.source == SourceType.TouchScreen) {
                    this.subBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH
                  }
                })
            )
            .hoverEffect(this.choverEffect)
            .onHover((isHover: boolean) => {
              this.onHoverDecrease && this.onHoverDecrease(isHover)
            })
            .focusable(this.focusEnable)
            .groupDefaultFocus(true)
            .onFocus(()=>{
              this.subBtnFocusWidh = CounterResource.BUTTON_BORDER_FOCUSED_WIDTH
              this.onFocusDecrease && this.onFocusDecrease()
              this.updateButtonStatus();
            })
            .onBlur(()=>{
              this.subBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH
              this.onBlurDecrease && this.onBlurDecrease()
            })
          }.width(CounterResource.COUNTER_COMPACT_BUTTON_SIZE)
          .height(CounterResource.COUNTER_COMPACT_BUTTON_SIZE)
          .borderRadius(CounterResource.COUNTER_COMPACT_BUTTON_RADIUS)
          .margin({left: '1vp'})
          .clip(true)

          if (this.hasTextWidth) {
            Text(this.value.toString())
              .textAlign(TextAlign.Center)
              .fontSize(CounterResource.COUNTER_NUMBER_SIZE)
              .fontColor(CounterResource.COUNTER_TEXT_COLOR)
              .width(this.textWidth.toString())
              .margin({
                left: CounterResource.COUNTER_COMPACT_BUTTON_TEXT_DISTANCE,
                right: CounterResource.COUNTER_COMPACT_BUTTON_TEXT_DISTANCE
              })
          } else {
            Text(this.value.toString())
              .textAlign(TextAlign.Center)
              .fontSize(CounterResource.COUNTER_NUMBER_SIZE)
              .fontColor(CounterResource.COUNTER_TEXT_COLOR)
              .margin({
                left: CounterResource.COUNTER_COMPACT_BUTTON_TEXT_DISTANCE,
                right: CounterResource.COUNTER_COMPACT_BUTTON_TEXT_DISTANCE
              })
          }

          Stack() {
            Rect()
              .width(CounterResource.COUNTER_COMPACT_FOCUS_BORDER_SIZE)
              .height(CounterResource.COUNTER_COMPACT_FOCUS_BORDER_SIZE)
              .radius(CounterResource.COUNTER_COMPACT_FOCUS_BORDER_RADIUS)
              .strokeWidth(this.addBtnFocusWidh)
              .stroke(CounterResource.BUTTON_BORDER_FOCUSED_COLOR)
              .fillOpacity(0)
            Image(CounterResource.BUTTON_ADD_ICON)
              .width(CounterResource.COUNTER_COMPACT_BUTTON_ICON_SIZE)
              .height(CounterResource.COUNTER_COMPACT_BUTTON_ICON_SIZE)
              .fillColor(CounterResource.BUTTON_ICON_COLOR)
              .opacity(this.addOpacity)
            Button({ type: ButtonType.Circle, stateEffect: this.addBtnStateEffect })
            .width(CounterResource.COUNTER_COMPACT_BUTTON_SIZE)
            .height(CounterResource.COUNTER_COMPACT_BUTTON_SIZE)
            .backgroundColor(CounterResource.BUTTON_BACKGROUD_COLOR)
            .opacity(this.addOpacity)
            .enabled(this.addBtnEnabled)
            .key("CompactAddButton" + this.timeStamp.toString())
            .onKeyEvent((event: KeyEvent) => {
              this.addBtnFocusWidh = CounterResource.BUTTON_BORDER_FOCUSED_WIDTH
              if (event.keyCode == CounterConstant.KEYCODE_ESC) {
                this.resetFocusButton();
                event.stopPropagation();
              }
              if (event.type == KeyType.Down &&
                  event.keyCode == CounterConstant.KEYCODE_MOVE_HOME) {
                event.stopPropagation();
                this.homeFirstValue()
                if (this.subBtnStateEffect) {
                  this.subBtnStateEffect = false;
                  this.subOpacity = CounterResource.COUNTER_BUTTON_DISABLE_OPACITY;
                  this.subBtnEnabled = false
                }
                this.focusWithTarget("CompactAddButton" + this.timeStamp.toString())
              }
              if (event.type == KeyType.Down &&
                  event.keyCode == CounterConstant.KEYCODE_MOVE_END) {
                event.stopPropagation();
                this.endLastValue()
                this.focusWithTarget("CompactSubButton" + this.timeStamp.toString())
              }
            })
            .onClick((event: ClickEvent) => {
              this.addValue()
              this.onChange && this.onChange(this.value)
              if (event.source == SourceType.Mouse ||
                  event.source == SourceType.TouchScreen) {
                this.addBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH
              }
            })
            .gesture(
              LongPressGesture({ repeat: true })
                .onAction((event: GestureEvent) => {
                  if (event.repeat) {
                    this.addValue()
                    this.onChange && this.onChange(this.value)
                  }
                  if (event.source == SourceType.Mouse ||
                      event.source == SourceType.TouchScreen) {
                    this.addBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH
                  }
                })
            )
            .hoverEffect(this.choverEffect)
            .onHover((isHover: boolean) => {
              this.onHoverIncrease && this.onHoverIncrease(isHover)
            })
            .focusable(this.focusEnable)
            .onFocus(()=>{
              this.addBtnFocusWidh = CounterResource.BUTTON_BORDER_FOCUSED_WIDTH
              this.onFocusIncrease && this.onFocusIncrease()
              this.updateButtonStatus();
            })
            .onBlur(()=>{
              this.addBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH
              this.onBlurIncrease && this.onBlurIncrease()
            })
          }
          .width(CounterResource.COUNTER_COMPACT_BUTTON_SIZE)
          .height(CounterResource.COUNTER_COMPACT_BUTTON_SIZE)
          .borderRadius(CounterResource.COUNTER_COMPACT_BUTTON_RADIUS)
          .margin({right: '1vp'})
          .clip(true)
        }
        .tabIndex(0)
        .height(CounterResource.COUNTER_COMPACT_CONTAINER_HEIGHT)
        .align(Alignment.Center)
        .borderWidth(CounterResource.COUNTER_BORDER_WIDTH)
        .borderColor(CounterResource.COUNTER_BORDER_COLOR)
        .borderRadius(CounterResource.COUNTER_COMPACT_CONTAINER_RADIUS)
        Text(this.numberStyleOptions.label)
          .margin({top: CounterResource.COUNTER_COMPACT_CONTAINER_LABEL_DISTANCE})
          .fontSize(CounterResource.COUNTER_COMPACT_LABEL_SIZE)
          .fontColor(CounterResource.COUNTER_TEXT_COLOR)
          .align(Alignment.Top)
      }
    } else if (this.type == CounterType.INLINE) {
      Row() {
        if (this.hasTextWidth) {
          RelativeContainer() {
            TextInput({
                text: this.hasInputText1 ? this.inputValue : this.value.toString(),
                controller: this.controller1
              })
              .alignRules({
                center: {anchor: "__container__", align: VerticalAlign.Center},
                middle: {anchor: "__container__", align: HorizontalAlign.Center}
              })
              .width(this.getValueLength() * 9.6)
              .height('20vp')
              .padding(0)
              .borderRadius(0)
              .textAlign(TextAlign.Center)
              .type(InputType.PhoneNumber)
              .caretColor(Color.Transparent)
              .copyOption(CopyOptions.None)
              .fontSize(CounterResource.COUNTER_NUMBER_SIZE)
              .fontColor(this.hasFocusText1 ? Color.White : CounterResource.COUNTER_TEXT_COLOR)
              .maxLength(this.getMaxLength())
              .backgroundColor(this.hasFocusText1 ? CounterResource.BUTTON_BORDER_FOCUSED_COLOR : Color.Transparent)
              .key("InlineTextInput" + this.timeStamp.toString())
              .onKeyEvent((event: KeyEvent) => {
                this.focusCurrentText(FocusText.TEXT1)
                if (event.keyCode == CounterConstant.KEYCODE_ESC) {
                  this.resetFocusText();
                  event.stopPropagation();
                }
                if (event.type == KeyType.Down &&
                    event.keyCode == CounterConstant.KEYCODE_DPAD_UP) {
                  this.addValue()
                  event.stopPropagation();
                }
                if (event.type == KeyType.Down &&
                    event.keyCode == CounterConstant.KEYCODE_MOVE_HOME) {
                  event.stopPropagation();
                  this.focusWithTarget("InlineTextInput" + this.timeStamp.toString())
                }
                if (event.type == KeyType.Down &&
                    event.keyCode == CounterConstant.KEYCODE_MOVE_END) {
                  event.stopPropagation();
                  this.focusWithTarget("InlineTextInput" + this.timeStamp.toString())
                }
                if (event.type == KeyType.Down &&
                    event.keyCode == CounterConstant.KEYCODE_DPAD_DOWN) {
                  this.subValue()
                  event.stopPropagation();
                }
                if (event.type == KeyType.Down &&
                    event.keyCode == CounterConstant.KEYCODE_DPAD_LEFT) {
                  this.focusWithTarget("InlineTextInput" + this.timeStamp.toString())
                  event.stopPropagation();
                }
                if (event.type == KeyType.Down &&
                    event.keyCode == CounterConstant.KEYCODE_DPAD_RIGHT) {
                  this.focusWithTarget("InlineTextInput" + this.timeStamp.toString())
                  event.stopPropagation();
                }
              })
              .onChange((value: string) => {
                this.inputValue = value
                for(let i= 0; i < value.length; i++) {
                  let c = value[i]
                  if (c == '+' || c == '*' || c == '#') {
                    this.value -= 1;
                    this.value += 1;
                    this.inputValue = this.value.toString();
                    return;
                  }
                  if (c == '-' && i != 0) {
                    this.inputValue = c
                    break;
                  }
                }

                this.hasInputText1 = true;
                let c = value[value.length -1]
                if (value.length == this.getMaxLength()) {
                  this.inputValue = c
                }
                if (this.timeoutID1 != -1) {
                  clearTimeout(this.timeoutID1);
                  this.timeoutID1 = -1;
                }
                if (this.inputValue != '' && Number(this.inputValue) <= this.max &&
                    Number(this.inputValue) >= this.min) {
                  this.value = Number(this.inputValue)
                  this.hasInputText1 = false;
                } else {
                  if (Number(this.inputValue) > this.max ||
                     (Number(this.inputValue) < this.min &&
                     this.inputValue.length <= this.min.toString().length)) {
                    this.inputValue = c;
                  }
                  if (value.length < this.getMaxLength()) {
                    this.timeoutID1 = setTimeout(() => {
                      if (this.inputValue != '' && Number(this.inputValue) <= this.max &&
                          Number(this.inputValue) >= this.min) {
                        this.value = Number(this.inputValue)
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
                if (this.timeoutID1 != -1) {
                  clearTimeout(this.timeoutID1);
                  this.timeoutID1 = -1;
                }
                this.hasInputText1 = false;
                this.value -= 1
                if (Number(this.inputValue) >= this.min && Number(this.inputValue) <= this.max) {
                  this.value = Number(this.inputValue)
                  this.updateInlineEnableSate()
                } else {
                  this.value += 1
                  this.inputValue = this.value.toString()
                }
              })
              .focusable(this.focusEnable)
              .focusOnTouch(true)
              .onFocus(() => {
                this.focusText = FocusText.TEXT1
                this.hasFocusText1 = true;
                this.controller1.caretPosition(this.value.toString().length);
              })
              .onBlur(() => {
                this.focusText = FocusText.NONE
                this.hasFocusText1 = false
              })
              .onClick((event: ClickEvent)=>{
                this.focusText = FocusText.TEXT1
                this.hasFocusText1 = true;
                this.focusWithTarget("InlineTextInput" + this.timeStamp.toString())
                this.controller1.caretPosition(this.value.toString().length)
              })
          }
          .margin({
            left: '12vp',
            right: '12vp'
          })
          .height('100%')
          .width(this.textWidth)
        } else {
          Row() {
            TextInput({
                text: this.hasInputText1 ? this.inputValue : this.value.toString(),
                controller: this.controller1
              })
              .width(this.getValueLength() * 9.6)
              .height('20vp')
              .padding(0)
              .borderRadius(0)
              .textAlign(TextAlign.Center)
              .type(InputType.PhoneNumber )
              .caretColor(Color.Transparent)
              .copyOption(CopyOptions.None)
              .fontSize(CounterResource.COUNTER_NUMBER_SIZE)
              .fontColor(this.hasFocusText1 ? Color.White : CounterResource.COUNTER_TEXT_COLOR)
              .maxLength(this.getMaxLength())
              .backgroundColor(this.hasFocusText1 ? CounterResource.BUTTON_BORDER_FOCUSED_COLOR : Color.Transparent)
              .key("InlineTextInput" + this.timeStamp.toString())
              .onKeyEvent((event: KeyEvent) => {
                this.focusCurrentText(FocusText.TEXT1)
                if (event.keyCode == CounterConstant.KEYCODE_ESC) {
                  this.resetFocusText();
                  event.stopPropagation();
                }
                if (event.type == KeyType.Down &&
                    event.keyCode == CounterConstant.KEYCODE_DPAD_UP) {
                  this.addValue()
                  event.stopPropagation();
                }
                if (event.type == KeyType.Down &&
                    event.keyCode == CounterConstant.KEYCODE_DPAD_DOWN) {
                  this.subValue()
                  event.stopPropagation();
                }
                if (event.type == KeyType.Down &&
                    event.keyCode == CounterConstant.KEYCODE_DPAD_LEFT) {
                  this.focusWithTarget("InlineTextInput" + this.timeStamp.toString())
                  event.stopPropagation();
                }
                if (event.type == KeyType.Down &&
                    event.keyCode == CounterConstant.KEYCODE_DPAD_RIGHT) {
                  this.focusWithTarget("InlineTextInput" + this.timeStamp.toString())
                  event.stopPropagation();
                }
              })
              .onChange((value: string) => {
                this.inputValue = value
                for(let i= 0; i < value.length; i++) {
                  let c = value[i]
                  if (c == '+' || c == '*' || c == '#') {
                    this.value -= 1;
                    this.value += 1;
                    this.inputValue = this.value.toString();
                    return;
                  }
                  if (c == '-' && i != 0) {
                    this.inputValue = c
                    break;
                  }
                }

                this.hasInputText1 = true;
                let c = value[value.length -1]
                if (value.length == this.getMaxLength()) {
                  this.inputValue = c
                }
                if (this.timeoutID1 != -1) {
                  clearTimeout(this.timeoutID1);
                  this.timeoutID1 = -1;
                }
                if (this.inputValue != '' && Number(this.inputValue) <= this.max &&
                    Number(this.inputValue) >= this.min) {
                  this.value = Number(this.inputValue)
                  this.hasInputText1 = false;
                } else {
                  if (Number(this.inputValue) > this.max ||
                      (Number(this.inputValue) < this.min &&
                      this.inputValue.length <= this.min.toString().length)) {
                    this.inputValue = c;
                  }
                  if (value.length < this.getMaxLength()) {
                    this.timeoutID1 = setTimeout(() => {
                      if (this.inputValue != '' && Number(this.inputValue) <= this.max &&
                          Number(this.inputValue) >= this.min) {
                        this.value = Number(this.inputValue)
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
                if (this.timeoutID1 != -1) {
                  clearTimeout(this.timeoutID1);
                  this.timeoutID1 = -1;
                }
                this.hasInputText1 = false;
                this.value -= 1
                if (Number(this.inputValue) >= this.min && Number(this.inputValue) <= this.max) {
                  this.value = Number(this.inputValue)
                  this.updateInlineEnableSate()
                } else {
                  this.value += 1
                  this.inputValue = this.value.toString()
                }
              })
              .focusable(this.focusEnable)
              .focusOnTouch(true)
              .onFocus(() => {
                this.focusText = FocusText.TEXT1
                this.hasFocusText1 = true;
                this.controller1.caretPosition(this.value.toString().length)
              })
              .onBlur(() => {
                this.focusText = FocusText.NONE
                this.hasFocusText1 = false
              })
              .onClick((event: ClickEvent)=>{
                this.focusText = FocusText.TEXT1
                this.hasFocusText1 = true;
                this.focusWithTarget("InlineTextInput" + this.timeStamp.toString())
                this.controller1.caretPosition(this.value.toString().length)
              })
          }
          .margin({
            left: '12vp',
            right: '12vp'
          })
        }

        Column(){
          Stack() {
            Rect()
              .width(CounterResource.COUNTER_INLINE_FOCUS_BORDER_WIDTH)
              .height(CounterResource.COUNTER_INLINE_FOCUS_BORDER_HEIGHT)
              .radius([
                ['0vp', '0vp'],
                [CounterResource.COUNTER_INLINE_RADIUS, CounterResource.COUNTER_INLINE_RADIUS],
                ['0vp', '0vp'],
                ['0vp', '0vp']])
              .strokeWidth(this.addBtnFocusWidh)
              .stroke(CounterResource.BUTTON_BORDER_FOCUSED_COLOR)
              .margin({right: '2vp'})
              .fillOpacity(0)
            Image(CounterResource.BUTTON_ARROW_UP)
              .width(CounterResource.COUNTER_INLINE_BUTTON_ICON_WIDTH)
              .height(CounterResource.COUNTER_INLINE_BUTTON_ICON_HEIGHT)
              .fillColor(CounterResource.BUTTON_ICON_COLOR)
              .opacity(this.addOpacity)
            Button({ type: ButtonType.Normal, stateEffect: this.addBtnStateEffect })
            .width(CounterResource.COUNTER_INLINE_BUTTON_WIDTH)
            .height(CounterResource.COUNTER_INLINE_BUTTON_HEIGHT)
            .backgroundColor(CounterResource.BUTTON_BACKGROUD_COLOR)
            .opacity(this.addOpacity)
            .enabled(this.addBtnEnabled)
            .onClick((event: ClickEvent) => {
              this.addValue()
              this.onChange && this.onChange(this.value)
              if (event.source == SourceType.Mouse ||
                  event.source == SourceType.TouchScreen) {
                this.addBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH
              }
            })
            .gesture(
              LongPressGesture({ repeat: true })
                .onAction((event: GestureEvent) => {
                  if (event.repeat) {
                    this.addValue()
                    this.onChange && this.onChange(this.value)
                  }
                  this.addBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH
                })
            )
            .hoverEffect(this.choverEffect)
            .onHover((isHover: boolean) => {
              this.onHoverIncrease && this.onHoverIncrease(isHover)
            })
            .focusable(false)
            .onFocus(()=>{
              this.addBtnFocusWidh = CounterResource.BUTTON_BORDER_FOCUSED_WIDTH
              this.onFocusIncrease&& this.onFocusIncrease()
            })
            .onBlur(()=>{
              this.addBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH
              this.onBlurIncrease && this.onBlurIncrease()
            })
          }
          .width(CounterResource.COUNTER_INLINE_BUTTON_WIDTH)
          .height(CounterResource.COUNTER_INLINE_BUTTON_HEIGHT)
          .borderColor(CounterResource.BUTTON_BACKGROUD_COLOR)
          .borderWidth({bottom: '1vp'})
          .clip(true)
          Stack() {
            Rect()
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
              .margin({top: '1vp', right: '1vp', bottom: '2vp'})
              .fillOpacity(0)
            Image(CounterResource.BUTTON_ARROW_DOWN)
              .width(CounterResource.COUNTER_INLINE_BUTTON_ICON_WIDTH)
              .height(CounterResource.COUNTER_INLINE_BUTTON_ICON_HEIGHT)
              .fillColor(CounterResource.BUTTON_ICON_COLOR)
              .opacity(this.subOpacity)
            Button({ type: ButtonType.Normal, stateEffect: this.subBtnStateEffect })
            .width(CounterResource.COUNTER_INLINE_BUTTON_WIDTH)
            .height(CounterResource.COUNTER_INLINE_BUTTON_HEIGHT)
            .backgroundColor(CounterResource.BUTTON_BACKGROUD_COLOR)
            .opacity(this.subOpacity)
            .enabled(this.subBtnEnabled)
            .onClick((event: ClickEvent) => {
              this.subValue()
              this.onChange && this.onChange(this.value)
              if (event.source == SourceType.Mouse ||
                  event.source == SourceType.TouchScreen) {
                this.subBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH
              }
            })
            .gesture(
              LongPressGesture({ repeat: true })
                .onAction((event: GestureEvent) => {
                  if (event.repeat) {
                    this.subValue()
                    this.onChange && this.onChange(this.value)
                  }
                  this.subBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH
                })
            )
            .hoverEffect(this.choverEffect)
            .onHover((isHover: boolean) => {
              this.onHoverDecrease && this.onHoverDecrease(isHover)
            })
            .focusable(false)
            .onFocus(()=>{
              this.subBtnFocusWidh = CounterResource.BUTTON_BORDER_FOCUSED_WIDTH
              this.onFocusDecrease && this.onFocusDecrease()
            })
            .onBlur(()=>{
              this.subBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH
              this.onBlurDecrease && this.onBlurDecrease()
            })
          }
          .width(CounterResource.COUNTER_INLINE_BUTTON_WIDTH)
          .height(CounterResource.COUNTER_INLINE_BUTTON_HEIGHT)
          .clip(true)
        }
        .width(CounterResource.COUNTER_INLINE_BUTTON_WIDTH)
        .height(CounterResource.COUNTER_INLINE_CONTAINER_HEIGHT)
        .borderWidth({left: CounterResource.COUNTER_BORDER_WIDTH})
        .borderColor(CounterResource.COUNTER_BORDER_COLOR)
      }
      .height(CounterResource.COUNTER_INLINE_CONTAINER_HEIGHT)
      .borderWidth(CounterResource.COUNTER_BORDER_WIDTH)
      .borderColor(CounterResource.COUNTER_BORDER_COLOR)
      .borderRadius(CounterResource.COUNTER_INLINE_RADIUS)
      .clip(true)
    } else if (this.type == CounterType.INLINE_DATE) {
      Row() {
        Row() {
          TextInput({
              text: this.hasInputText1? this.inputYear.toString() : this.getYear(),
              controller: this.controller1
            })
            .type(InputType.Number)
            .caretColor(Color.Transparent)
            .copyOption(CopyOptions.None)
            .fontSize(CounterResource.COUNTER_NUMBER_SIZE)
            .fontColor(this.hasFocusText1? Color.White : CounterResource.COUNTER_TEXT_COLOR)
            .maxLength(5)
            .padding(0)
            .backgroundColor(this.hasFocusText1? CounterResource.BUTTON_BORDER_FOCUSED_COLOR : Color.Transparent)
            .width('38vp')
            .height('20vp')
            .borderRadius(0)
            .borderWidth(0)
            .key("DateTextInput1" + this.timeStamp.toString())
            .onKeyEvent((event: KeyEvent) => {
              this.focusCurrentText(FocusText.TEXT1)
              if (event.keyCode == CounterConstant.KEYCODE_ESC) {
                this.resetFocusText();
                event.stopPropagation();
              }
              if (event.type == KeyType.Down &&
                  event.keyCode == CounterConstant.KEYCODE_DPAD_UP) {
                this.addDate()
                event.stopPropagation();
              }
              if (event.type == KeyType.Down &&
                  event.keyCode == CounterConstant.KEYCODE_DPAD_DOWN) {
                this.subDate()
                event.stopPropagation();
              }
              if (event.type == KeyType.Down &&
                  event.keyCode == CounterConstant.KEYCODE_MOVE_HOME) {
                this.homeFocusText()
                event.stopPropagation();
              }
              if (event.type == KeyType.Down &&
                  event.keyCode == CounterConstant.KEYCODE_MOVE_END) {
                this.endFocusText()
                event.stopPropagation();
              }
              if (event.type == KeyType.Down &&
                  event.keyCode == CounterConstant.KEYCODE_DPAD_LEFT) {
                this.focusWithTarget("DateTextInput1" + this.timeStamp.toString())
                event.stopPropagation();
              }
              if (event.type == KeyType.Down &&
                 event.keyCode == CounterConstant.KEYCODE_DPAD_RIGHT) {
                this.focusWithTarget("DateTextInput2" + this.timeStamp.toString())
              }
            })
            .onChange((value: string) => {
              if (value.length !=4) {
                this.hasInputText1 = true;
              }
              this.inputYear = Number(value)
              if(value.length == 5) {
                this.inputYear = this.inputYear % 10;
              }

              if (this.timeoutID1 != -1) {
                clearTimeout(this.timeoutID1);
                this.timeoutID1 = -1;
              }

              this.timeoutID1 = setTimeout(()=>{
                this.hasInputText1 = false;
                this.inputYear = this.year
                this.updateDateEnableSate();
                this.updateDay();
              }, 1500);

              if (this.inputYear >= this.minYear && this.inputYear <= this.maxYear) {
                this.year = this.inputYear
                this.updateDateEnableSate();
                this.updateDay();
              }
            })
            .onSubmit((enterKey: EnterKeyType) =>{
              if (this.timeoutID1 != -1) {
                clearTimeout(this.timeoutID1);
                this.timeoutID1 = -1;
              }
              this.hasInputText1 = false;
              this.year -= 1
              if (this.inputYear >= this.minYear && this.inputYear <= this.maxYear) {
                this.year = this.inputYear
              } else {
                this.year += 1
                this.inputYear = this.year
              }
              this.updateDateEnableSate()
              this.updateDay();
            })
            .tabIndex(0)
            .focusOnTouch(true)
            .focusable(true)
            .onFocus(() => {
              this.focusText = FocusText.TEXT1
              this.hasFocusText1 = true
              this.updateDateEnableSate()
              this.controller1.caretPosition(this.getYear().length)
            })
            .onBlur(()=>{
              this.focusText = FocusText.NONE
              this.hasFocusText1 = false
              this.updateDateEnableSate()
            })
            .onClick((event: ClickEvent)=>{
              this.focusText = FocusText.TEXT1
              this.hasFocusText1 = true
              this.updateDateEnableSate()
              this.controller1.caretPosition(this.getYear().length)
            })
          Text('/')
            .textAlign(TextAlign.Center)
            .fontSize(CounterResource.COUNTER_NUMBER_SIZE)
            .fontColor(CounterResource.COUNTER_TEXT_COLOR)
            .width('8vp')
          TextInput({
              text: this.hasInputText2? this.inputMoon.toString() : this.convertNumberToString(this.month),
              controller: this.controller2
            })
            .type(InputType.Number)
            .caretColor(Color.Transparent)
            .copyOption(CopyOptions.None)
            .fontSize(CounterResource.COUNTER_NUMBER_SIZE)
            .fontColor(this.hasFocusText2? Color.White : CounterResource.COUNTER_TEXT_COLOR)
            .maxLength(3)
            .padding(0)
            .backgroundColor(this.hasFocusText2? CounterResource.BUTTON_BORDER_FOCUSED_COLOR : Color.Transparent)
            .width('19vp')
            .height('20vp')
            .borderRadius(0)
            .key("DateTextInput2" + this.timeStamp.toString())
            .onKeyEvent((event: KeyEvent) => {
              this.focusCurrentText(FocusText.TEXT2)
              if (event.keyCode == CounterConstant.KEYCODE_ESC) {
                this.resetFocusText();
                event.stopPropagation();
              }
              if (event.type == KeyType.Down &&
                  event.keyCode == CounterConstant.KEYCODE_DPAD_DOWN) {
                this.subDate()
                this.updateDay()
                event.stopPropagation();
              }
              if (event.type == KeyType.Down &&
                  event.keyCode == CounterConstant.KEYCODE_DPAD_UP) {
                this.addDate()
                this.updateDay()
                event.stopPropagation();
              }
              if (event.type == KeyType.Down &&
                  event.keyCode == CounterConstant.KEYCODE_MOVE_HOME) {
                this.homeFocusText()
                event.stopPropagation();
              }
              if (event.type == KeyType.Down &&
                  event.keyCode == CounterConstant.KEYCODE_MOVE_END) {
                this.endFocusText()
                event.stopPropagation();
              }
              if (event.type == KeyType.Down &&
                  event.keyCode == CounterConstant.KEYCODE_DPAD_LEFT) {
                this.focusWithTarget("DateTextInput1" + this.timeStamp.toString())
              }
              if (event.type == KeyType.Down &&
                 event.keyCode == CounterConstant.KEYCODE_DPAD_RIGHT) {
                this.focusWithTarget("DateTextInput3" + this.timeStamp.toString())
              }

              if (event.type == KeyType.Down &&
                  event.keyCode == CounterConstant.KEYCODE_TAB) {
                event.stopPropagation();
                this.focusWithTarget("DateTextInput1" + this.timeStamp.toString())
              }
            })
            .onChange((value: string) => {
              this.inputMoon = Number(value)
              if (value.length != 2) {
                this.hasInputText2 = true;
              }
              if (value.length == 3) {
                this.inputMoon = this.inputMoon %10
              }
              if (this.timeoutID2 != -1) {
                clearTimeout(this.timeoutID2);
                this.timeoutID2 = -1
              }

              this.timeoutID2 = setTimeout(()=>{
                this.hasInputText2 = false;
                this.month -= 1
                if (this.inputMoon >= 1 && this.inputMoon <= 12) {
                  this.month = this.inputMoon
                } else {
                  this.month += 1
                  this.inputMoon = this.month
                }
                this.updateDay();
              }, 1000);

              if (value.length == 2) {
                this.hasInputText2 = false;
                this.month -= 1
                if (this.inputMoon >= 1 && this.inputMoon <= 12) {
                  this.month = this.inputMoon
                } else {
                  this.month += 1
                  this.inputMoon = this.month
                }
                this.updateDay();
              }
            })
            .onSubmit((enterKey: EnterKeyType) =>{
              if (this.timeoutID2 != -1) {
                clearTimeout(this.timeoutID2);
                this.timeoutID2 = -1;
              }
              this.hasInputText2 = false;
              this.month -= 1
              if (this.inputMoon >= 1 && this.inputMoon <= 12) {
                this.month = this.inputMoon
                this.updateDay();
              } else {
                this.month += 1
              }
            })
            .focusOnTouch(true)
            .tabIndex(-1)
            .focusable(true)
            .onFocus(() => {
              this.focusText = FocusText.TEXT2
              this.hasFocusText2 = true
              this.controller2.caretPosition(this.convertNumberToString(this.month).length)
            })
            .onBlur(()=>{
              this.focusText = FocusText.NONE
              this.hasFocusText2 = false
            })
            .onClick((event: ClickEvent)=>{
              this.focusText = FocusText.TEXT2
              this.hasFocusText2 = true
              this.controller2.caretPosition(this.convertNumberToString(this.month).length)
            })
          Text('/')
            .textAlign(TextAlign.Center)
            .fontSize(CounterResource.COUNTER_NUMBER_SIZE)
            .fontColor(CounterResource.COUNTER_TEXT_COLOR)
            .width('8vp')
          TextInput({
              text: this.hasInputText3? this.inputDay.toString(): this.convertNumberToString(this.day),
              controller: this.controller3
            })
            .type(InputType.Number)
            .caretColor(Color.Transparent)
            .copyOption(CopyOptions.None)
            .fontSize(CounterResource.COUNTER_NUMBER_SIZE)
            .fontColor(this.hasFocusText3? Color.White : CounterResource.COUNTER_TEXT_COLOR)
            .maxLength(3)
            .padding(0)
            .backgroundColor(this.hasFocusText3? CounterResource.BUTTON_BORDER_FOCUSED_COLOR : Color.Transparent)
            .width('19vp')
            .height('20vp')
            .borderRadius(0)
            .key("DateTextInput3" + this.timeStamp.toString())
            .onKeyEvent((event: KeyEvent) => {
              this.focusCurrentText(FocusText.TEXT3)
              if (event.keyCode == CounterConstant.KEYCODE_ESC) {
                this.resetFocusText();
                event.stopPropagation();
              }
              if (event.type == KeyType.Down &&
                  event.keyCode == CounterConstant.KEYCODE_DPAD_DOWN) {
                this.subDate()
                event.stopPropagation();
              }
              if (event.type == KeyType.Down &&
                  event.keyCode == CounterConstant.KEYCODE_DPAD_UP) {
                this.addDate()
                event.stopPropagation();
              }
              if (event.type == KeyType.Down &&
                  event.keyCode == CounterConstant.KEYCODE_MOVE_HOME) {
                this.homeFocusText()
                event.stopPropagation();
              }
              if (event.type == KeyType.Down &&
                  event.keyCode == CounterConstant.KEYCODE_MOVE_END) {
                this.endFocusText()
                event.stopPropagation();
              }
              if (event.type == KeyType.Down &&
                event.keyCode == CounterConstant.KEYCODE_DPAD_LEFT) {
                this.focusWithTarget("DateTextInput2" + this.timeStamp.toString())
              }

              if (event.type == KeyType.Down &&
                  event.keyCode == CounterConstant.KEYCODE_DPAD_RIGHT) {
                this.focusWithTarget("DateTextInput3" + this.timeStamp.toString())
                event.stopPropagation();
              }

              if (event.type == KeyType.Down &&
                  event.keyCode == CounterConstant.KEYCODE_TAB) {
                event.stopPropagation();
                this.focusWithTarget("DateTextInput1" + this.timeStamp.toString())
              }
            })
            .onChange((value: string) => {
              this.inputDay = Number(value)
              if (value.length != 2) {
                this.hasInputText3 = true;
              }
              if (value.length == 3) {
                this.inputDay = this.inputDay % 10
              }
              if (this.timeoutID3 != -1) {
                clearTimeout(this.timeoutID3);
                this.timeoutID3 = -1;
              }

              this.timeoutID3 = setTimeout(()=>{
                this.hasInputText3 = false;
                this.day -= 1
                if (this.inputDay >= 1 && this.inputDay <= this.getDayNumber()) {
                  this.day = this.inputDay
                } else {
                  this.day += 1
                  this.inputDay = this.day
                }
              }, 1000);

              if (value.length == 2) {
                this.hasInputText3 = false;
                this.day -= 1
                if (this.inputDay >= 1 && this.inputDay <= this.getDayNumber()) {
                  this.day = this.inputDay
                } else {
                  this.day += 1
                  this.inputDay = this.day
                }
              }
            })
            .onSubmit((enterKey: EnterKeyType) =>{
              if (this.timeoutID3 != -1) {
                clearTimeout(this.timeoutID3);
                this.timeoutID3 = -1;
              }
              this.hasInputText3 = false
              this.day -= 1
              if (this.inputDay >= 1 && this.inputDay <= this.getDayNumber()) {
                this.day = this.inputDay
              } else {
                this.day += 1
              }
            })
            .tabIndex(-2)
            .focusOnTouch(true)
            .focusable(true)
            .onFocus(() => {
              this.focusText = FocusText.TEXT3
              this.hasFocusText3 = true
              this.controller3.caretPosition(this.convertNumberToString(this.day).length)
            })
            .onBlur(()=>{
              this.focusText = FocusText.NONE
              this.hasFocusText3 = false
            })
            .onClick((event: ClickEvent)=>{
              this.focusText = FocusText.TEXT3
              this.hasFocusText3 = true
              this.controller3.caretPosition(this.convertNumberToString(this.day).length)
            })
        }.width('92vp')
        .height(CounterResource.COUNTER_INLINE_CONTAINER_HEIGHT)
        .margin({
          left: CounterResource.COUNTER_INLINE_DATE_TEXT_MARGIN,
          right: CounterResource.COUNTER_INLINE_DATE_TEXT_MARGIN
        })
        Column(){
          Stack() {
            Rect()
              .width(CounterResource.COUNTER_INLINE_FOCUS_BORDER_WIDTH)
              .height(CounterResource.COUNTER_INLINE_FOCUS_BORDER_HEIGHT)
              .radius([
                ['0vp', '0vp'],
                [CounterResource.COUNTER_INLINE_RADIUS, CounterResource.COUNTER_INLINE_RADIUS],
                ['0vp', '0vp'],
                ['0vp', '0vp']])
              .strokeWidth(this.addBtnFocusWidh)
              .stroke(CounterResource.BUTTON_BORDER_FOCUSED_COLOR)
              .margin({right: '1vp'})
              .fillOpacity(0)
            Button({ type: ButtonType.Normal, stateEffect: this.addBtnStateEffect }) {
              Image(CounterResource.BUTTON_ARROW_UP)
                .width(CounterResource.COUNTER_INLINE_BUTTON_ICON_WIDTH)
                .height(CounterResource.COUNTER_INLINE_BUTTON_ICON_HEIGHT)
                .fillColor(CounterResource.BUTTON_ICON_COLOR)
            }
            .width(CounterResource.COUNTER_INLINE_BUTTON_WIDTH)
            .height(CounterResource.COUNTER_INLINE_BUTTON_HEIGHT)
            .backgroundColor(CounterResource.BUTTON_BACKGROUD_COLOR)
            .opacity(this.addOpacity)
            .enabled(this.addBtnEnabled)
            .onClick((event: ClickEvent) => {
              this.addDate()
              let date = new DateData(this.year, this.month, this.day);
              this.onDateChange && this.onDateChange(date)
              if (event.source == SourceType.Mouse ||
                  event.source == SourceType.TouchScreen) {
                this.addBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH
              }
            })
            .gesture(
              LongPressGesture({ repeat: true })
                .onAction((event: GestureEvent) => {
                  if (event.repeat) {
                    this.addDate()
                    let date = new DateData(this.year, this.month, this.day);
                    this.onDateChange && this.onDateChange(date);
                  }
                  this.addBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH
                })
            )
            .hoverEffect(this.choverEffect)
            .onHover((isHover: boolean) => {
              this.onHoverIncrease && this.onHoverIncrease(isHover)
            })
            .focusable(false)
            .onFocus(()=>{
              this.addBtnFocusWidh = CounterResource.BUTTON_BORDER_FOCUSED_WIDTH
              this.onFocusIncrease && this.onFocusIncrease()
            })
            .onBlur(()=>{
              this.addBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH
              this.onBlurIncrease && this.onBlurIncrease()
            })
          }.width(CounterResource.COUNTER_INLINE_BUTTON_WIDTH)
          .height(CounterResource.COUNTER_INLINE_BUTTON_HEIGHT)
          .borderWidth({bottom: '1vp'})
          .borderColor(CounterResource.BUTTON_BACKGROUD_COLOR)
          .clip(true)
          Stack() {
            Rect()
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
              .margin({top: '1vp', right: '1vp', bottom: '2vp'})
              .fillOpacity(0)
            Button({ type: ButtonType.Normal, stateEffect: this.subBtnStateEffect }) {
              Image(CounterResource.BUTTON_ARROW_DOWN)
                .width(CounterResource.COUNTER_INLINE_BUTTON_ICON_WIDTH)
                .height(CounterResource.COUNTER_INLINE_BUTTON_ICON_HEIGHT)
                .fillColor(CounterResource.BUTTON_ICON_COLOR)
            }
            .width(CounterResource.COUNTER_INLINE_BUTTON_WIDTH)
            .height(CounterResource.COUNTER_INLINE_BUTTON_HEIGHT)
            .backgroundColor(CounterResource.BUTTON_BACKGROUD_COLOR)
            .opacity(this.subOpacity)
            .enabled(this.subBtnEnabled)
            .onClick((event: ClickEvent) => {
              this.subDate()
              let date = new DateData(this.year, this.month, this.day);
              this.onDateChange && this.onDateChange(date)
              if (event.source == SourceType.Mouse ||
                  event.source == SourceType.TouchScreen) {
                this.subBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH
              }
            })
            .gesture(
              LongPressGesture({ repeat: true })
                .onAction((event: GestureEvent) => {
                  if (event.repeat) {
                    this.subDate()
                    let date = new DateData(this.year, this.month, this.day);
                    this.onDateChange && this.onDateChange(date)
                  }
                  this.subBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH
                })
            )
            .hoverEffect(this.choverEffect)
            .onHover((isHover: boolean) => {
              this.onHoverDecrease && this.onHoverDecrease(isHover)
            })
            .focusable(false)
            .onFocus(()=>{
              this.subBtnFocusWidh = CounterResource.BUTTON_BORDER_FOCUSED_WIDTH
              this.onFocusDecrease && this.onFocusDecrease()
            })
            .onBlur(()=>{
              this.subBtnFocusWidh = CounterResource.BUTTON_BORDER_BLUR_WIDTH
              this.onBlurDecrease && this.onBlurDecrease()
            })
          }.width(CounterResource.COUNTER_INLINE_BUTTON_WIDTH)
          .height(CounterResource.COUNTER_INLINE_BUTTON_HEIGHT)
          .clip(true)
        }.width(CounterResource.COUNTER_INLINE_BUTTON_WIDTH)
        .height(CounterResource.COUNTER_INLINE_CONTAINER_HEIGHT)
        .borderWidth({left: CounterResource.COUNTER_BORDER_WIDTH})
        .borderColor(CounterResource.COUNTER_BORDER_COLOR)
      }
      .width('148vp')
      .height(CounterResource.COUNTER_INLINE_CONTAINER_HEIGHT)
      .borderWidth(CounterResource.COUNTER_BORDER_WIDTH)
      .borderColor(CounterResource.COUNTER_BORDER_COLOR)
      .borderRadius(CounterResource.COUNTER_INLINE_RADIUS)
      .clip(true)
    } else {

    }
  }
}
