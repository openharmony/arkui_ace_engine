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
      top: LengthMetrics.px(2),
      end: LengthMetrics.vp(3),
      bottom: LengthMetrics.fp(4),
      start: LengthMetrics.lpx(5)
    },
    { top: LengthMetrics.vp(-2), end: LengthMetrics.percent(0), bottom: LengthMetrics.vp(null), start: LengthMetrics.lpx(undefined) },
    { end: new LengthMetrics(2, LengthUnit.PX), start: new LengthMetrics(3, LengthUnit.VP) },
    { top: new LengthMetrics(2, LengthUnit.VP), bottom: new LengthMetrics(3, LengthUnit.PX) },
    { start: new LengthMetrics(2, LengthUnit.PX), top: new LengthMetrics(3, LengthUnit.FP) },
  ];
  @State language: string = I18n.System.getSystemLanguage();
  @State caseName: string = '';
  @State value: EdgeWidths | null = null;
  case: string = 'borderWidth';

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
border: ${this.value?.left}`)

      Stack({ alignContent: Alignment.End }) {
        Scroll(this.scroller) {
          Flex({ direction: FlexDirection.Column }) {
            Column({ space: 10 }) {
              ForEach(this.simpleList, (item: Info, index: number) => {
                Text('caseName: ' + Constants.getCaseName(this.case, index + 1))

                Gauge({ value: 50, min: 1, max: 100 }) {
                  Column() {
                    Text('50')
                      .fontWeight(FontWeight.Medium)
                      .width('62%')
                      .fontColor("#ff182431")
                      .maxFontSize("60.0vp")
                      .minFontSize("30.0vp")
                      .textAlign(TextAlign.Center)
                      .margin({ top: '35%' })
                      .textOverflow({ overflow: TextOverflow.Ellipsis })
                      .maxLines(1)
                    Text('辅助文本')
                      .maxFontSize("16.0fp")
                      .minFontSize("10.0vp")
                      .fontColor($r('sys.color.ohos_id_color_text_secondary'))
                      .fontColor($r('sys.color.ohos_id_color_text_secondary'))
                      .fontWeight(FontWeight.Regular)
                      .width('67.4%')
                      .height('9.5%')
                      .textAlign(TextAlign.Center)
                  }.width('100%').height('100%')
                }
                .key(Constants.getCaseName(this.case, index + 1))
                .border({ width: { top: item.top, end: item.end, bottom: item.bottom, start: item.start } })
                .value(50)
                .startAngle(210)
                .endAngle(150)
                .colors([[new LinearGradient([{ color: "#deb6fb", offset: 0 }, { color: "#ac49f5", offset: 1 }]), 9],
                  [new LinearGradient([{ color: "#bbb7fc", offset: 0 }, { color: "#564af7", offset: 1 }]), 8],
                  [new LinearGradient([{ color: "#f5b5c2", offset: 0 }, { color: "#e64566", offset: 1 }]), 7],
                  [new LinearGradient([{ color: "#f8c5a6", offset: 0 }, { color: "#ed6f21", offset: 1 }]), 6],
                  [new LinearGradient([{ color: "#fceb99", offset: 0 }, { color: "#f7ce00", offset: 1 }]), 5],
                  [new LinearGradient([{ color: "#dbefa5", offset: 0 }, { color: "#a5d61d", offset: 1 }]), 4],
                  [new LinearGradient([{ color: "#c1e4be", offset: 0 }, { color: "#64bb5c", offset: 1 }]), 3],
                  [new LinearGradient([{ color: "#c0ece5", offset: 0 }, { color: "#61cfbe", offset: 1 }]), 2],
                  [new LinearGradient([{ color: "#b5e0f4", offset: 0 }, { color: "#46b1e3", offset: 1 }]), 1]])
                .width('40%')
                .height('40%')
                .strokeWidth(18)
                .trackShadow({ radius: 7, offsetX: 7, offsetY: 7 })
                .padding(18)
                Button("获取组件信息:" + Constants.getCaseName(this.case, index + 1)).onClick(() => {
                  let strJson = getInspectorByKey(Constants.getCaseName(this.case, index + 1));
                  let obj: ESObject = JSON.parse(strJson);
                  this.caseName = Constants.getCaseName(this.case, index + 1);
                  this.value = {
                    left: obj.$attrs.border,
                    top: obj.$attrs.border,
                    right: obj.$attrs.border,
                    bottom: obj.$attrs.border
                  };
                })
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

