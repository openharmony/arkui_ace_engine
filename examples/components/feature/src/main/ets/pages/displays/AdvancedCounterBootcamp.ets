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

@Component
export struct AdvancedCounterBootcamp{
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
  @State Focusable: boolean = true;
  @State Direction: Direction = Direction.Ltr;
  @State Min: number = 0;
  @State Max: number = 999;
  @State Value: number = 0;
  @State Step: number = 1;
  @State textWidth: number = 0;
  @State counterType: CounterType = 0;
  @State Year: number = 1;
  @State Month: number = 1;
  @State Day: number = 1;
  @State Label: string = '';

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
    Column(){
      if (this.counterType == 0){
        CounterComponent({
          options: {
            type: useEnabledNumber(this.enableType,this.counterType,0),
            direction: useEnabled(this.enabledDirection,this.Direction),
            numberOptions: {
              label: 'Counter',
              value: useEnabled(this.enabledValue,this.Value),
              min: useEnabled(this.enabledMin,this.Min),
              max: useEnabled(this.enabledMax,this.Max),
              focusable:useEnabled(this.enabledFocusable,this.Focusable),
              onFocusIncrease: () => {
                console.log("onFocusIncrease,当前Counter组件增加按钮获取焦点时触发的回调" );
              },
              onFocusDecrease: () => {
                console.log("onFocusIncrease,当前Counter组件减小按钮获取焦点时触发的回调" );
              },
              onBlurIncrease: () => {
                console.log("onFocusIncrease,当前Counter组件增加按钮失去焦点时触发的回调" );
              },
              onBlurDecrease: () => {
                console.log("onFocusIncrease,当前Counter组件减小按钮失去焦点时触发的回调" );
              }
            }
          }
        })
      }else if (this.counterType == 1){
        CounterComponent({
          options: {
            type: useEnabledNumber(this.enableType,this.counterType,0),
            direction: useEnabled(this.enabledDirection,this.Direction),
            numberOptions: {
              label: 'Counter',
              value: useEnabled(this.enabledValue,this.Value),
              min: useEnabled(this.enabledMin,this.Min),
              max: useEnabled(this.enabledMax,this.Max),
              focusable:useEnabled(this.enabledFocusable,this.Focusable),
              onFocusIncrease: () => {
                console.log("onFocusIncrease,当前Counter组件增加按钮获取焦点时触发的回调" );
              },
              onFocusDecrease: () => {
                console.log("onFocusIncrease,当前Counter组件减小按钮获取焦点时触发的回调" );
              },
              onBlurIncrease: () => {
                console.log("onFocusIncrease,当前Counter组件增加按钮失去焦点时触发的回调" );
              },
              onBlurDecrease: () => {
                console.log("onFocusIncrease,当前Counter组件减小按钮失去焦点时触发的回调" );
              }
            }
          }
        })
      }else if (this.counterType == 2){
        CounterComponent({
          options: {
            type: useEnabledNumber(this.enableType,this.counterType,0),
            direction: useEnabled(this.enabledDirection,this.Direction),
            inlineOptions: {
              value: useEnabled(this.enabledValue,this.Value),
              min: useEnabled(this.enabledMin,this.Min),
              max: useEnabled(this.enabledMax,this.Max),
              step: useEnabled(this.enabledStep,this.Step),
              textWidth: useEnabled(this.enabledTextWidth,this.textWidth),
              focusable:useEnabled(this.enabledFocusable,this.Focusable),
              onChange: (value: number) => {
                console.log("onDateChange Date: " + value.toString());
              }
            }
          }
        })
      }else {
        CounterComponent({
          options: {
            type: useEnabledNumber(this.enableType,this.counterType,0),
            direction: useEnabled(this.enabledDirection,this.Direction),
            dateOptions: {
              year: useEnabled(this.enabledYear,this.Year),
              month: useEnabled(this.enabledMonth,this.Month),
              day: useEnabled(this.enabledDay,this.Day),
              focusable:this.Focusable,
              onDateChange: (date: DateData) => {
                console.log("onDateChange Date: " + date.toString());
              }
            }
          }
        })
      }
    }
  }

  @Builder
  Parameters() {
    Scroll(){
      Column({ space: 8 }) {
        RadioBlock({
          title: 'type',
          isEnabled: $enableType,
          value: $counterType,
          dataSource: [
            { label: 'LIST', value: 0},
            { label: 'COMPACT', value: 1 },
            { label: 'INLINE', value: 2 },
            { label: 'INLINE_DATE', value: 3 },
          ]
        })
        RadioBlock({
          title: 'direction',
          isEnabled: $enabledDirection,
          value: $Direction,
          dataSource: [
            { label: 'Ltr', value: Direction.Ltr},
            { label: 'Rtl', value: Direction.Rtl },
            { label: 'Auto', value: Direction.Auto },
          ]
        })
        RadioBlock({
          title: 'focusable',
          isEnabled: $enabledFocusable,
          value: $Focusable,
          dataSource: [
            { label: 'true', value: true},
            { label: 'false', value: false},
          ]
        })
        SliderBlock({
          title: 'value',
          isEnabled: $enabledValue,
          value: $Value,
          min: 0,
          max: 999
        })
        SliderBlock({
          title: 'min',
          isEnabled: $enabledMin,
          value: $Min,
          min: 0,
          max: 999
        })
        SliderBlock({
          title: 'max',
          isEnabled: $enabledMax,
          value: $Max,
          min: 1,
          max: 999
        })
        SliderBlock({
          title: 'step',
          isEnabled: $enabledStep,
          value: $Step,
          min: 1,
          max: 100
        })
        SliderBlock({
          title: 'textWidth',
          isEnabled: $enabledTextWidth,
          value: $textWidth,
          min: 1,
          max: 999
        })
        SliderBlock({
          title: 'year',
          isEnabled: $enabledYear,
          value: $Year,
          min: 1,
          max: 9999
        })
        SliderBlock({
          title: 'month',
          isEnabled: $enabledMonth,
          value: $Month,
          min: 1,
          max: 12
        })
        SliderBlock({
          title: 'day',
          isEnabled: $enabledDay,
          value: $Day,
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
struct AdvancedCounterBootcampPreviewer{
  build() {
    AdvancedCounterBootcamp({
      title: '计数器/AdvancedCounter'
    })
  }
}
