/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
import { Drawer, RadioBlock, SliderBlock, useEnabled, useEnabledNumber } from 'common';
import { CounterComponent, CounterType, DateData } from '@ohos.arkui.advanced.Counter';
import { BlockTag } from 'common/src/main/ets/model/BlockTag';
import { formatDate } from 'common/src/main/ets/utils/timeUtil';

@Component
export struct AdvancedCounterBootcamp {
  @Require @Prop title: ResourceStr;
  @State showParameters: boolean = false;
  @State enableType: boolean = false;
  @State enabledDirection: boolean = false;
  @State enabledFocusable: boolean = false;
  @State enabledValue: boolean = false;
  @State enabledMin: boolean = false;
  @State enabledMax: boolean = false;
  @State enabledTextWidth: boolean = false;
  @State enabledYear: boolean = false;
  @State enabledMonth: boolean = false;
  @State enabledDay: boolean = false;
  @State enabledStep: boolean = false;
  @State counterFocusable: boolean = true;
  @State counterDirection: Direction = Direction.Ltr;
  @State counterMin: number = 0;
  @State counterMax: number = 999;
  @State counterValue: number = 0;
  @State counterStep: number = 1;
  @State counterTextWidth: number = 0;
  @State counterType: CounterType = 0;
  @State counterYear: number = 1;
  @State counterMonth: number = 1;
  @State counterDay: number = 1;
  //compEvent
  @StorageLink('Block') listEventTriggeredTags: Array<BlockTag> = [];
  @State listEventTriggeredTagsTemp: Array<BlockTag> = [];

  //compEvent
  compEventTriggeredLog(value: string) {
    let time = formatDate(new Date(Date.now()))
    this.listEventTriggeredTagsTemp.push(
      new BlockTag(time, value)
    )
    setTimeout(() => {
      if (AppStorage.get('Block')) {
        this.listEventTriggeredTags = this.listEventTriggeredTags.concat(
          this.listEventTriggeredTagsTemp
        );
        this.listEventTriggeredTagsTemp = [];
      } else {
        if (this.listEventTriggeredTagsTemp) {
          this.listEventTriggeredTags = this.listEventTriggeredTags.concat(
            this.listEventTriggeredTagsTemp
          );
        }
        if (this.listEventTriggeredTags) {
          this.listEventTriggeredTagsTemp = [];
        }
      }
    }, 200);
  }

  build() {
    NavDestination() {
      Drawer({
        title: this.title,
        showParameters: $showParameters,
        content: () => {
          this.Content()
        },
        parameters: () => {
          this.Parameters()
        }
      })
    }
    .backgroundColor($r('sys.color.ohos_id_color_sub_background'))
    .hideTitleBar(true)
  }

  @Builder
  Content() {
    Column() {
      if (this.counterType == 0) {
        CounterComponent({
          options: {
            type: useEnabledNumber(this.enableType, this.counterType, 0),
            direction: useEnabled(this.enabledDirection, this.counterDirection),
            numberOptions: {
              label: 'Counter',
              value: useEnabled(this.enabledValue, this.counterValue),
              min: useEnabled(this.enabledMin, this.counterMin),
              max: useEnabled(this.enabledMax, this.counterMax),
              focusable: useEnabled(this.enabledFocusable, this.counterFocusable),
              onFocusIncrease: () => {
                this.compEventTriggeredLog('onFocusIncrease,当前Counter组件增加按钮获取焦点时触发的回调');
                console.log('11111','asd');
              },
              onFocusDecrease: () => {
                this.compEventTriggeredLog('onFocusDecrease,当前Counter组件减小按钮获取焦点时触发的回调');
              },
              onBlurIncrease: () => {
                this.compEventTriggeredLog('onBlurIncrease,当前Counter组件增加按钮失去焦点时触发的回调');
              },
              onBlurDecrease: () => {
                this.compEventTriggeredLog('onBlurDecrease,当前Counter组件减小按钮失去焦点时触发的回调');
              },
              onHoverIncrease: (isHover: boolean) => {
                this.compEventTriggeredLog('onHoverIncrease,鼠标进入或退出Counter组件的增加按钮触发该回调');
              },
              onHoverDecrease: (isHover: boolean) => {
                this.compEventTriggeredLog('onHoverDecrease,鼠标进入或退出Counter组件的减小按钮触发该回调');
              },
            }
          }
        })
      } else if (this.counterType == 1) {
        CounterComponent({
          options: {
            type: useEnabledNumber(this.enableType, this.counterType, 0),
            direction: useEnabled(this.enabledDirection, this.counterDirection),
            numberOptions: {
              label: 'Counter',
              value: useEnabled(this.enabledValue, this.counterValue),
              min: useEnabled(this.enabledMin, this.counterMin),
              max: useEnabled(this.enabledMax, this.counterMax),
              focusable: useEnabled(this.enabledFocusable, this.counterFocusable),
              onFocusIncrease: () => {
                this.compEventTriggeredLog('onFocusIncrease,当前Counter组件增加按钮获取焦点时触发的回调');
              },
              onFocusDecrease: () => {
                this.compEventTriggeredLog('onFocusDecrease,当前Counter组件减小按钮获取焦点时触发的回调');
              },
              onBlurIncrease: () => {
                this.compEventTriggeredLog('onBlurIncrease,当前Counter组件增加按钮失去焦点时触发的回调');
              },
              onBlurDecrease: () => {
                this.compEventTriggeredLog('onBlurDecrease,当前Counter组件减小按钮失去焦点时触发的回调');
              },
              onHoverIncrease: (isHover: boolean) => {
                this.compEventTriggeredLog('onHoverIncrease,鼠标进入或退出Counter组件的增加按钮触发该回调');
              },
              onHoverDecrease: (isHover: boolean) => {
                this.compEventTriggeredLog('onHoverDecrease,鼠标进入或退出Counter组件的减小按钮触发该回调');
              },
            }
          }
        })
      } else if (this.counterType == 2) {
        CounterComponent({
          options: {
            type: useEnabledNumber(this.enableType, this.counterType, 0),
            direction: useEnabled(this.enabledDirection, this.counterDirection),
            inlineOptions: {
              value: useEnabled(this.enabledValue, this.counterValue),
              min: useEnabled(this.enabledMin, this.counterMin),
              max: useEnabled(this.enabledMax, this.counterMax),
              step: useEnabled(this.enabledStep, this.counterStep),
              textWidth: useEnabled(this.enabledTextWidth, this.counterTextWidth),
              focusable: useEnabled(this.enabledFocusable, this.counterFocusable),
              onChange: (value: number) => {
                console.log('onDateChange Date: ' + value.toString());
              },
              onHoverIncrease: (isHover: boolean) => {
                this.compEventTriggeredLog('onHoverIncrease,鼠标进入或退出Counter组件的增加按钮触发该回调');
              },
              onHoverDecrease: (isHover: boolean) => {
                this.compEventTriggeredLog('onHoverDecrease,鼠标进入或退出Counter组件的减小按钮触发该回调');
              },
            }
          }
        })
      } else {
        CounterComponent({
          options: {
            type: useEnabledNumber(this.enableType, this.counterType, 0),
            direction: useEnabled(this.enabledDirection, this.counterDirection),
            dateOptions: {
              year: useEnabled(this.enabledYear, this.counterYear),
              month: useEnabled(this.enabledMonth, this.counterMonth),
              day: useEnabled(this.enabledDay, this.counterDay),
              focusable: this.counterFocusable,
              onDateChange: (date: DateData) => {
                console.log('onDateChange Date: ' + date.toString());
              },
              onHoverIncrease: (isHover: boolean) => {
                this.compEventTriggeredLog('onHoverIncrease,鼠标进入或退出Counter组件的增加按钮触发该回调');
              },
              onHoverDecrease: (isHover: boolean) => {
                this.compEventTriggeredLog('onHoverDecrease,鼠标进入或退出Counter组件的减小按钮触发该回调');
              },
            }
          }
        })
      }
    }
  }

  @Builder
  Parameters() {
    Scroll() {
      Column({ space: 8 }) {
        RadioBlock({
          title: 'type',
          isEnabled: $enableType,
          value: $counterType,
          dataSource: [
            { label: 'LIST', value: 0 },
            { label: 'COMPACT', value: 1 },
            { label: 'INLINE', value: 2 },
            { label: 'INLINE_DATE', value: 3 },
          ]
        })
        RadioBlock({
          title: 'direction',
          isEnabled: $enabledDirection,
          value: $counterDirection,
          dataSource: [
            { label: 'Ltr', value: Direction.Ltr },
            { label: 'Rtl', value: Direction.Rtl },
            { label: 'Auto', value: Direction.Auto },
          ]
        })
        RadioBlock({
          title: 'focusable',
          isEnabled: $enabledFocusable,
          value: $counterFocusable,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false },
          ]
        })
        SliderBlock({
          title: 'value',
          isEnabled: $enabledValue,
          value: $counterValue,
          min: 0,
          max: 999
        })
        SliderBlock({
          title: 'min',
          isEnabled: $enabledMin,
          value: $counterMin,
          min: 0,
          max: 999
        })
        SliderBlock({
          title: 'max',
          isEnabled: $enabledMax,
          value: $counterMax,
          min: 1,
          max: 999
        })
        SliderBlock({
          title: 'step',
          isEnabled: $enabledStep,
          value: $counterStep,
          min: 1,
          max: 100
        })
        SliderBlock({
          title: 'textWidth',
          isEnabled: $enabledTextWidth,
          value: $counterTextWidth,
          min: 1,
          max: 999
        })
        SliderBlock({
          title: 'year',
          isEnabled: $enabledYear,
          value: $counterYear,
          min: 1,
          max: 9999
        })
        SliderBlock({
          title: 'month',
          isEnabled: $enabledMonth,
          value: $counterMonth,
          min: 1,
          max: 12
        })
        SliderBlock({
          title: 'day',
          isEnabled: $enabledDay,
          value: $counterDay,
          min: 1,
          max: 31
        })
      }
    }
    .height('52%')
  }
}

@Preview
@Component
struct AdvancedCounterBootcampPreviewer {
  build() {
    AdvancedCounterBootcamp({
      title: '计数器/AdvancedCounter'
    })
  }
}
