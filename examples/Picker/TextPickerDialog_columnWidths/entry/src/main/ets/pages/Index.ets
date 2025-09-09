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

import { CalleeCallback, ConfigurationConstant } from '@kit.AbilityKit';
import { Callback } from '@ohos.base';
import { LengthMetrics } from '@kit.ArkUI';

interface pickerCategories<T> {
  id?: string,
  text: string,
  value?: T
}

interface pickerData {
  id: string,
  range: string[] | string[][] | Resource | TextPickerRangeContent[] | TextCascadePickerRangeContent[]
}

@Entry
@Component
struct Index {
  @State currentDialog: string = '';

  private apples: string[] = ['apple1', 'apple2', 'apple3', 'apple4'];
  private oranges: string[] = ['orange1', 'orange2', 'orange3', 'orange4'];
  private peaches: string[] = ['peach1', 'peach2', 'peach3', 'peach4'];
  private multiFruits: string[][] = [this.apples, this.oranges, this.peaches];

  private resRange: Resource = $r('app.strarray.example_name_1');
  private contentRange: TextPickerRangeContent[] = [
    {
      icon: $r('app.media.svg1'),
      text: $r('app.string.heilongjiang')
    },
    {
      icon: $r('sys.media.ohos_ic_public_phone'),
      text: $r('app.string.jilin')
    },
    {
      icon: $r('sys.media.ohos_ic_public_more'),
      text: $r('app.string.liaoning')
    },
    {
      icon: $r('app.media.3_C'),
      text: $r('app.string.shenhe')
    }
  ];

  private cascade: TextCascadePickerRangeContent[] = [
    {
      text: $r('app.string.liaoning'),
      children: [
        {
          text: $r('app.string.shenyang'),
          children: [
            {
              text: $r('app.string.shenhe')
            },
            {
              text: $r('app.string.heping')
            },
            {
              text: $r('app.string.hunnan')
            }
          ]
        },
        {
          text: $r('app.string.dalian'),
          children: [
            {
              text: $r('app.string.zhongshan')
            },
            {
              text: $r('app.string.jinzhou')
            },
            {
              text: $r('app.string.changhai')
            }
          ]
        }
      ]
    },
    {
      text: $r('app.string.jilin'),
      children: [
        {
          text: $r('app.string.changchun'),
          children: [
            {
              text: $r('app.string.nanguan')
            },
            {
              text: $r('app.string.kuancheng')
            },
            {
              text: $r('app.string.chaoyang')
            }
          ]
        },
        {
          text: $r('app.string.siping'),
          children: [
            {
              text: $r('app.string.tiexi')
            },
            {
              text: $r('app.string.tiedong')
            },
            {
              text: $r('app.string.lishu')
            }
          ]
        }
      ]
    },
    {
      text: $r('app.string.heilongjiang'),
      children: [
        {
          text: $r('app.string.haerbing'),
          children: [
            {
              text: $r('app.string.daoli'),
            },
            {
              text: $r('app.string.daowai'),
            },
            {
              text: $r('app.string.nangang'),
            }
          ]
        },
        {
          text: $r('app.string.mudan'),
          children: [
            {
              text: $r('app.string.dongan')
            },
            {
              text: $r('app.string.xian')
            },
            {
              text: $r('app.string.aimin')
            }
          ]
        }
      ]
    }
  ];

  allData: pickerData[] = [
    {id: '单列', range: this.resRange},
    {id: '单列图文', range: this.contentRange},
    {id: '多列不联动', range: this.multiFruits},
    {id: '多列联动', range: this.cascade},
    {id: '单例超长', range: ['这是一个超级超级超级超级超级超级无敌长的文本']}
  ];
  @State dataIndex: number = -1;

  @State columnWidthsValues: pickerCategories<LengthMetrics[]>[] = [
    {
      text: 'undefined',
      value: undefined
    },
    {
      text: '[]',
      value: []
    },
    {
      text: '60(170)vp',
      value: [LengthMetrics.resource($r('app.string.100vpDark200'))]
    },
    {
      text: '60%',
      value: [LengthMetrics.percent(60)]
    },
    {
      text: '100%',
      value: [LengthMetrics.percent(100)]
    },
    {
      text: '100-100-200(200-120-220)vp',
      value: [LengthMetrics.resource($r('app.string.100vpDark200')),
      LengthMetrics.resource($r('app.string.100vpDark120')),
      LengthMetrics.resource($r('app.string.200vpDark220'))]
    },
    {
      text: '20-40-20(25-45-25)%',
      value: [LengthMetrics.resource($r('app.string.20PercentDark25')),
        LengthMetrics.resource($r('app.string.40PercentDark45')),
        LengthMetrics.resource($r('app.string.20PercentDark25'))]
    },
    {
      text: '100vp-20%-20%(120vp-25%-25%)',
      value: [LengthMetrics.resource($r('app.string.100vpDark120')),
        LengthMetrics.resource($r('app.string.20PercentDark25')),
        LengthMetrics.resource($r('app.string.20PercentDark25'))]
    },
    {
      text: '100vp-99999vp',
      value: [LengthMetrics.vp(100), LengthMetrics.resource($r('app.string.99999vp'))]
    },
    {
      text: '20%-20%-60%',
      value: [LengthMetrics.percent(20), LengthMetrics.percent(20), LengthMetrics.percent(60)]
    },
    {
      text: '60%-20%-20%',
      value: [LengthMetrics.percent(60), LengthMetrics.percent(20), LengthMetrics.percent(20)]
    }
  ];
  @State columnWidths?: LengthMetrics[] = undefined;
  @State columnWidthsStr: string = '';

  @Builder
  clickComponent(id?: string, text?: string, click?: Callback<ClickEvent>) {
    Column() {
      Button(text).fontSize(12)
    }
    .id(id)
    .onClick(click)
  }

  build() {
    Column({space: 5}) {
      Text('TextPickerDialog columnWidths')

      Scroll() {
        Column({space: 5}) {
          Row({space: 5}) {
            this.clickComponent(undefined, '深色', (event: ClickEvent) => {
              let context = this.getUIContext().getHostContext()?.getApplicationContext()
              context?.setColorMode(ConfigurationConstant.ColorMode.COLOR_MODE_DARK)
            })
            this.clickComponent(undefined, '浅色', (event: ClickEvent) => {
              let context = this.getUIContext().getHostContext()?.getApplicationContext()
              context?.setColorMode(ConfigurationConstant.ColorMode.COLOR_MODE_LIGHT)
            })
          }.width('100%')

          Text('选择一个TextPickerDialog: ' + this.currentDialog).width('100%')
          Flex({wrap: FlexWrap.Wrap, alignContent: FlexAlign.Center, space: {main: LengthMetrics.vp(5)}}) {
            ForEach(this.allData, (item: pickerData, index: number) => {
              this.clickComponent(item.id, item.id, (event: ClickEvent) => {
                this.dataIndex = index;
                this.currentDialog = this.allData[index].id;
              })
            })
          }.width('100%')

          Text('columnWidths: ' + this.columnWidthsStr).width('100%')
          Flex({wrap: FlexWrap.Wrap, alignContent: FlexAlign.Center, space: {main: LengthMetrics.vp(5)}}) {
            ForEach(this.columnWidthsValues, (item: pickerCategories<LengthMetrics[]>, index: number) => {
              this.clickComponent(item.text, item.text, (event: ClickEvent) => {
                this.columnWidths = item.value;
                this.columnWidthsStr = item.text;
              })
            })
          }.width('100%')

        }.width('100%')
      }.constraintSize({maxHeight: '500vp'})

      Stack() {
        ForEach(this.allData, (item: pickerData, index: number) => {
          Button('TextPickerDialog')
            .onClick(() => {
              this.getUIContext().showTextPickerDialog({
                range: item.range,
                columnWidths: this.columnWidths,
              })
            })
            .visibility(this.dataIndex == index ? Visibility.Visible : Visibility.Hidden)
        })
      }
    }.width('100%')
  }
}
