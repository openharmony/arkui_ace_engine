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

import I18n from '@ohos.i18n';
import { BusinessError } from '@ohos.base'
import { Constants } from './Utils/Constants';
import { LengthMetrics, LengthUnit } from '@ohos.arkui.node';

interface Info {
  top?: LengthMetrics | null | undefined;
  end?: LengthMetrics | null | undefined;
  bottom?: LengthMetrics | null | undefined;
  start?: LengthMetrics | null | undefined;
}

@Entry
@Component
struct WebComponent {
  private scroller: Scroller = new Scroller()
  simpleList: Array<Info> = [
    {
      top: LengthMetrics.vp(2),
      end: LengthMetrics.px(3),
      bottom: LengthMetrics.lpx(4),
      start: LengthMetrics.fp(5)
    },
    {
      top: LengthMetrics.vp(10),
      end: LengthMetrics.vp(10),
      bottom: LengthMetrics.vp(0),
      start: LengthMetrics.vp(0)
    },
    {
      top: LengthMetrics.px(10),
      end: LengthMetrics.px(10),
      bottom: LengthMetrics.px(0),
      start: LengthMetrics.px(0)
    },
    {
      top: LengthMetrics.lpx(10),
      end: LengthMetrics.lpx(10),
      bottom: LengthMetrics.lpx(0),
      start: LengthMetrics.lpx(0)
    },
    {
      top: LengthMetrics.fp(10),
      end: LengthMetrics.fp(10),
      bottom: LengthMetrics.fp(0),
      start: LengthMetrics.fp(0)
    },
    {
      top: LengthMetrics.percent(10),
      end: LengthMetrics.percent(10),
      bottom: LengthMetrics.percent(10),
      start: LengthMetrics.percent(10)
    },
    { top: LengthMetrics.vp(-2), end: LengthMetrics.vp(0), bottom: null, start: undefined },
    { end: new LengthMetrics(2, LengthUnit.VP), start: new LengthMetrics(3, LengthUnit.VP) },
    { top: new LengthMetrics(2, LengthUnit.PX), bottom: new LengthMetrics(0.03, LengthUnit.PERCENT) },
    { start: new LengthMetrics(2, LengthUnit.FP), top: new LengthMetrics(3, LengthUnit.LPX) },
  ];
  @State language: string = I18n.System.getSystemLanguage();
  @State caseName: string = '';
  @State value: EdgeWidths | null | string = null;
  case: string = 'borderImage_width_';

  build() {
    Column() {
      Button("rtl语言").onClick(() => {
        console.log("getSystemLanguage last " + I18n.System.getSystemLanguage());
        try {
          I18n.System.setAppPreferredLanguage("ar-EG");
        } catch (error) {
          let err: BusinessError = error as BusinessError;
          console.error(`call System.setSystemLanguage failed, error code: ${err.code}, message: ${err.message}.`);
        }
        console.log("getSystemLanguage new" + I18n.System.getSystemLanguage());
      }).margin({ bottom: 30, top: 30 })
      Button("ltr语言").onClick(() => {
        console.log("getSystemLanguage last " + I18n.System.getSystemLanguage());
        try {
          I18n.System.setAppPreferredLanguage("zh-Hans");
        } catch (error) {
          let err: BusinessError = error as BusinessError;
          console.error(`call System.setSystemLanguage failed, error code: ${err.code}, message: ${err.message}.`);
        }
        console.log("getSystemLanguage new" + I18n.System.getSystemLanguage());
      })
      Text(`当前caseName: ${this.caseName}
borderImage: ${this.value}`)

      Stack({ alignContent: Alignment.End }) {
        Scroll(this.scroller) {
          Flex({ direction: FlexDirection.Column }) {
            Column({ space: 10 }) {
              ForEach(this.simpleList, (item: Info, index: number) => {
                Column({ space: 20 }) {
                  Text('caseName: ' + Constants.getCaseName(this.case, index + 1))
                    .key(Constants.getCaseName(this.case, index + 1))
                    .borderImage({
                      source: {
                        angle: 90,
                        direction: GradientDirection.Left,
                        colors: [[0xAEE1E1, 0.0], [0xD3E0DC, 0.3], [0xFCD1D1, 1.0]]
                      },
                      slice: 10,
                      width: { top: item.top, end: item.end, bottom: item.bottom, start: item.start },
                    }).width("70%").height("50%")
                  Button("获取组件信息:" + Constants.getCaseName(this.case, index + 1)).onClick(() => {
                    let strJson = getInspectorByKey(Constants.getCaseName(this.case, index + 1));
                    let obj: ESObject = JSON.parse(strJson);
                    let borderImage: ESObject = JSON.parse(obj.$attrs.borderImage);
                    this.caseName = Constants.getCaseName(this.case, index + 1);
                    /* this.value = {
                       left: obj.$attrs.borderWidth.left,
                       top: obj.$attrs.borderWidth.top,
                       right: obj.$attrs.borderWidth.right,
                       bottom: obj.$attrs.borderWidth.bottom
                     };*/
                    this.value = obj.$attrs.borderImage
                    console.log("borderImage " + obj.$attrs.borderImage);
                    console.log("borderImage1 " + borderImage.slice);
                  })
                }
              })
            }
          }.margin({ right: 15 })
        }
        .width('100%')
        .scrollBar(BarState.Off)
        .scrollable(ScrollDirection.Vertical)

        ScrollBar({ scroller: this.scroller, direction: ScrollBarDirection.Vertical, state: BarState.Auto }) {
          Text()
            .width(20)
            .height(100)
            .borderRadius(10)
            .backgroundColor('#C0C0C0')
        }.width(20).backgroundColor('#ededed')
      }
    }.height('70%')
  }
}

