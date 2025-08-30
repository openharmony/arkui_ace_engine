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

import { LengthMetrics, LengthUnit } from '@kit.ArkUI';

namespace IPicker {
  export enum EPickerMode {
    region = 'region',
    time = 'time',
    selector = 'selector',
    multiSelector = 'multiSelector',
    date = 'date'
  }

  export interface PickerInfo {
    range: string[][] | string[],
    current?: string,
    selected: number[] | number | undefined,
    fields?: string;
    start?: string;
    end?: string;
    requestId?: string;
    mode?: EPickerMode;
    level?: string;
    webviewId?: number;
  }
  export interface PickerStyle {
    // mask 颜色
    maskColor: string,

    // 背景
    backgroundColor: string,

    // 选择中的字体颜色
    selectedTextColor: string,

    // 待选择的字体颜色
    defaultTextColor: string,

    // 最上和最下两个选项的文本颜色
    disappearTextColor: string,
  }
}

const AGE_0: number = 0;

function getAgeString(age: number): Resource {
  if (age === AGE_0) {
    return $r('app.string.zero_age', 1);
  }
  return $r('app.plural.minors_temp_user_age', age, age);
}

function getPickerRange(maxAge: number) {
  const list: TextCascadePickerRangeContent[] = [];
  for (let index = AGE_0; index < maxAge; index++) {
    list.push({
      text: getAgeString(index)
    });
  }
  return list;
}

const lightStyle: IPicker.PickerStyle = {
  maskColor: 'rgba(0, 0, 0, 0.5)',
  backgroundColor: '#FEFFFF',
  selectedTextColor: '#FF0000',
  defaultTextColor: '#00FF00',
  disappearTextColor: '#0000FF',
}

@Entry
@Component
struct TextPickerExample {
  private select: number = 1
  @State pickerSelectId: number = 5;
  @State pickerRange: TextCascadePickerRangeContent[] = getPickerRange(18);
  private selectedTime: Date = new Date('2022-07-22T08:00:00')
  private strange: string[] = ['apple0', 'apple1']
  private fruits: string[] = ['apple', 'apple1', 'apple2', 'apple3', 'apple4', 'banana', 'watermelon']
  private apm: string[] =
    ['全天', '上午0:00-6:00', '上午6:00-7:00', '上午11:00-12:00', '下午12:00-13:00', '下午13:00-14:00',
      '下午22:00-23:00']
  private orfruits: string[] =
    ['orange1', 'orange2', 'orange3', 'orange4', 'orange5', 'orange6', 'orange7', 'orange8', 'orange9', 'orange10',
      'orange11', 'orange12', 'orange13', 'orange14'];
  private pefruits: string[] = ['peach1', 'peach2', 'peach3', 'peach4'];
  private multiThreeColumn: string[][] = [this.fruits, this.orfruits, this.pefruits];
  private multiTwoColumn: string[][] = [this.fruits, this.orfruits];
  @State isShow: boolean = true;
  @State selected: number[] = [0, 0, 0];
  @State selected11: number[] = [0, 0, 0];
  @State selected22: number[] = [0, 0, 0];
  @State value: string = '';
  private year: string[] = ['2023', '2024', '2025'];
  @State private month: string[] = ['1', '2', '3', '4', '5', '6', '7'];
  @State multiDate: string[][] = [this.year, this.month];
  @State strSelected1: string = '';
  @State strSelected2: string = '';
  @State selected2: number = 0;
  @State valueText: ResourceStr = $r('app.string.border_radius');
  private textWidth: number = 100;
  @State isCascade: boolean = true;
  @State rangeCascade?: TextCascadePickerRangeContent[] =
    [
      {
        text: '护肤品',
        children: [
          {
            text: '面霜',
            children: [{ text: '滋润面霜' }, { text: '清爽面霜   会啊啊啊啊啊啊超长字符串' },
              { text: '敏感肌专用aaaaaa' }]
          },
          {
            text: '眼霜',
            children: [{ text: '娇韵诗\n水油混合抗老眼霜' }, { text: '兰蔻小黑瓶' }, { text: '雅诗兰黛小棕瓶' }]
          },
          {
            text: '洗面奶',
            children: [{ text: '迪奥睡莲洗面奶' }, { text: '香奈儿经典洗面奶' },
              { text: '#￥%！@34245566666666666666666666666666666666' }]
          },]
      },
      {
        text: '化妆品',
        children: [{ text: '眼影', children: [{ text: '汤姆福德四色眼影' }] },
          { text: '化妆刷', children: [{ text: '唇刷' }, { text: '眼影刷' }, { text: '腮红刷' }] }]
      },
      {
        text: '女装',
        children: [{ text: '上装', children: [{ text: '短袖' }, { text: '长袖' }, { text: '背心' }] },
          { text: '下装', children: [{ text: '短裤' }, { text: '长裤' }, { text: '长裙' }, { text: '短裙' }] }]
      },
      {
        text: '女鞋',
        children: [{ text: '夏鞋', children: [{ text: '洞洞鞋' }, { text: '凉鞋' }, { text: '帆布鞋' }] },
          { text: '冬鞋', children: [{ text: '雪地靴' }, { text: '切西尔靴' }, { text: '板鞋' }] }]
      },
      {
        text: '零食酒水',
        children: [{
          text: '休闲零食',
          children: [{ text: '薯片' }, { text: 'cookie' }, { text: '果冻' }]
        },
          {
            text: '酒水',
            children: [{ text: '白葡萄酒' }, { text: '红葡萄酒' }, { text: '香槟' },
              { text: 'beer' }]
          }]
      }
    ]
  private multiDate1: TextCascadePickerRangeContent[] = [
    {
      text: '2023年',
      children: [{ text: '1月' }, { text: '2月' }, { text: '3月' }, { text: '4月' }, { text: '5月' }, { text: '6月' },
        { text: '7月' }]
    },
    {
      text: '2024年',
      children: [{ text: '1月' }, { text: '2月' }, { text: '3月' }]
    },
    {
      text: '2025年',
      children: [{ text: '1月' }, { text: '2月' }, { text: '3月' }, { text: '4月' }, { text: '5月' }, { text: '6月' },
        { text: '7月' }, { text: '8月' }, { text: '9月' }, { text: '10月' }]
    }
  ]
  private cascade: TextCascadePickerRangeContent[] = [
    {
      text: '山东省',
      children: [
        { text: '济南市', children: [{ text: '历下区' }, { text: '市中区' }, { text: '天桥区' }] },
        { text: '青岛市', children: [{ text: '市南区' }, { text: '市北区' }, { text: '李沧区' }] },
        { text: '烟台市', children: [{ text: '芝罘区' }, { text: '福山区' }, { text: '莱山区' }] }
      ]
    },
    {
      text: '浙江省',
      children: [
        { text: '杭州市', children: [{ text: '西湖区' }, { text: '上城区' }, { text: '滨江区' }] },
        { text: '宁波市', children: [{ text: '海曙区' }, { text: '江北区' }, { text: '鄞州区' }] },
        { text: '温州市', children: [{ text: '鹿城区' }, { text: '龙湾区' }, { text: '瓯海区' }] }
      ]
    },
    {
      text: '湖北省',
      children: [
        { text: '武汉市', children: [{ text: '江岸区' }, { text: '武昌区' }, { text: '洪山区' }] },
        { text: '宜昌市', children: [{ text: '西陵区' }, { text: '伍家岗区' }, { text: '点军区' }] },
        { text: '襄阳市', children: [{ text: '襄城区' }, { text: '樊城区' }, { text: '襄州区' }] }
      ]
    }
  ];
  private multipleColumnWidths1: LengthMetrics[] = [
    LengthMetrics.percent(20),
    LengthMetrics.percent(50),
    LengthMetrics.percent(50)
  ];
  private multipleColumnWidths2: LengthMetrics[] = [
    LengthMetrics.vp(100),
    LengthMetrics.vp(100),
    LengthMetrics.vp(100)
  ];

  aboutToAppear(): void {
    console.log('aboutToAppear()...')
  }

  build() {
    Column() {
      Text('基础 TextPicker')
        .fontSize(30)
        .backgroundColor(Color.Pink)
        .fontWeight(FontWeight.Bold)
        .width('100%')
        .textAlign(TextAlign.Center)


      Row() {
        Button('Visibility: ' + this.isShow)
          .onClick(() => {
            this.isShow = !this.isShow
          })

        Button('Cascade: ' + this.isCascade)
          .onClick(() => {
            if (this.isCascade) {
              this.isCascade = false
              this.rangeCascade = undefined
            } else {
              this.isCascade = true
              this.rangeCascade =
                [
                  {
                    text: '护肤品',
                    children: [
                      {
                        text: '面霜',
                        children: [{ text: '滋润面霜' }, { text: '清爽面霜   会啊啊啊啊啊啊超长字符串' },
                          { text: '敏感肌专用aaaaaa' }]
                      },
                      {
                        text: '眼霜',
                        children: [{ text: '娇韵诗\n水油混合抗老眼霜' }, { text: '兰蔻小黑瓶' },
                          { text: '雅诗兰黛小棕瓶' }]
                      },
                      {
                        text: '洗面奶',
                        children: [{ text: '迪奥睡莲洗面奶' }, { text: '香奈儿经典洗面奶' },
                          { text: '#￥%！@34245566666666666666666666666666666666' }]
                      },]
                  },
                  {
                    text: '化妆品',
                    children: [{ text: '眼影', children: [{ text: '汤姆福德四色眼影' }] },
                      { text: '化妆刷', children: [{ text: '唇刷' }, { text: '眼影刷' }, { text: '腮红刷' }] }]
                  },
                  {
                    text: '女装',
                    children: [{ text: '上装', children: [{ text: '短袖' }, { text: '长袖' }, { text: '背心' }] },
                      {
                        text: '下装',
                        children: [{ text: '短裤' }, { text: '长裤' }, { text: '长裙' }, { text: '短裙' }]
                      }]
                  },
                  {
                    text: '女鞋',
                    children: [{ text: '夏鞋', children: [{ text: '洞洞鞋' }, { text: '凉鞋' }, { text: '帆布鞋' }] },
                      { text: '冬鞋', children: [{ text: '雪地靴' }, { text: '切西尔靴' }, { text: '板鞋' }] }]
                  },
                  //问题：资源引用不显示
                  {
                    text: '零食酒水',
                    children: [{
                      text: '休闲零食',
                      children: [{ text: '薯片' }, { text: 'cookie' }, { text: '果冻' }]
                    },
                      {
                        text: '酒水',
                        children: [{ text: '白葡萄酒' }, { text: '红葡萄酒' }, { text: '香槟' },
                          { text: 'beer' }]
                      }]
                  }
                ]
            }
          })
      }

      Column() {
        Row() {
          Text('非循环' + this.strSelected1)
            .fontSize(30)
            .textAlign(TextAlign.Center)

          Text('循环' + this.strSelected2)
            .fontSize(30)
            .textAlign(TextAlign.Center)
            .margin({ left: 20 })
        }

        Row() {
          TextPicker({
            range: this.cascade,
            selected: $$this.selected,
            value: $$this.value,
            columnWidths: this.multipleColumnWidths2
          })
            .key('textpicker_7')
            .border({ width: 2, color: Color.Red })
            .selectedIndex([null, 1, 1])
            .width(this.textWidth)
            .canLoop(true)
            .align(Alignment.Center)
            .enableHapticFeedback(false)
            .selectedBackgroundStyle({ color: '#000000', borderRadius: { value: 0, unit: LengthUnit.VP } })
            .selectedTextStyle({ color: lightStyle.selectedTextColor, font: { size: 25, family: 'HarmonyHeiTi' } })
            .textStyle({ color: Color.Blue, font: { size: 20, weight: FontWeight.Normal, family: 'HarmonyHeiTi' } })
            .disappearTextStyle({ color: Color.Red, font: { size: 15, weight: FontWeight.Lighter } })
            .visibility(this.isShow ? Visibility.Visible : Visibility.None)
            .disableTextStyleAnimation(false)
            .defaultTextStyle({
              color: Color.Black,
              font: { size: 20, weight: FontWeight.Normal },
              minFontSize: 40,
              maxFontSize: 28,
              overflow: TextOverflow.Ellipsis
            })
            .onChange((value: string | string[], index: number | number[]) => {
              this.strSelected1 = value as string;
              console.log('value : ' + JSON.stringify(value) + ', selected : ' + JSON.stringify(index) + '\n' +
                'this.selected : ' + this.selected + ' this.value : ' + this.value)
            })
        }
      }.alignRules({ center: { anchor: '__container__', align: VerticalAlign.Center } })
    }
    .backgroundColor('#90EE90')
    .width('100%')
    .height('100%')
  }
}
