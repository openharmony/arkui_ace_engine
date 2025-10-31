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
      top: LengthMetrics.vp(4),
      end: LengthMetrics.px(6),
      bottom: LengthMetrics.lpx(10),
      start: LengthMetrics.fp(15)
    },
    { top: LengthMetrics.vp(-6), end: LengthMetrics.vp(0), bottom: null, start: undefined },
    { end: new LengthMetrics(2, LengthUnit.VP), start: new LengthMetrics(3, LengthUnit.VP) },
    { top: new LengthMetrics(2, LengthUnit.PX), bottom: new LengthMetrics(0.03, LengthUnit.PERCENT) },
    { start: new LengthMetrics(2, LengthUnit.FP), top: new LengthMetrics(3, LengthUnit.LPX) },
  ];
  @State language: string = I18n.System.getSystemLanguage();
  @State caseName: string = '';
  @State value: EdgeWidths | null = null;
  case: string = 'bindSheet_width_';
  @State isShow: boolean[] = [false, false, false, false, false]
  @State isShow2: boolean = false
  @State sheetHeight: number = 300;
  @State showDragBar: boolean = true;

  @Builder myBuilder() {
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
      Button("change height")
        .margin(10)
        .fontSize(20)
        .onClick(() => {
          let strJson = getInspectorByKey(Constants.getCaseName(this.case, 1));
          let obj: ESObject = JSON.parse(strJson);
          this.caseName = Constants.getCaseName(this.case, 1);
          this.value = {
            left: obj.$attrs.borderWidth.left,
            top: obj.$attrs.borderWidth.top,
            right: obj.$attrs.borderWidth.right,
            bottom: obj.$attrs.borderWidth.bottom
          };
          console.info('ArkUIHDS_BorderWidth_Test_0100:' + strJson);
        })

      Button("Set Illegal height")
        .margin(10)
        .fontSize(20)
        .onClick(() => {
          this.sheetHeight = -1;
        })

      Button("close dragBar")
        .margin(10)
        .fontSize(20)
        .onClick(() => {
          this.showDragBar = false;
        })
    }
    .width('100%')
    .height('100%')
  }

  build() {
    Column() {

      Text(`当前caseName: ${this.caseName}
left: ${this.value?.left}
top: ${this.value?.top}
right: ${this.value?.right}
bottom: ${this.value?.bottom}`)

      Stack({ alignContent: Alignment.End }) {
        Scroll(this.scroller) {
          Flex({ direction: FlexDirection.Column }) {
            Column({ space: 10 }) {
              ForEach(this.simpleList, (item: Info, index: number) => {
                Text(JSON.stringify(item))
                Button('caseName: ' + Constants.getCaseName(this.case, index + 1))
                  .onClick(() => {
                    this.isShow[index] = true
                  })
                  .fontSize(20)
                    // .key(Constants.getCaseName(this.case, index + 1))
                  .margin(10)
                  .bindSheet(this.isShow[index], this.myBuilder(), {
                    height: this.sheetHeight,
                    dragBar: this.showDragBar,
                    borderWidth: { top: item.top, end: item.end, bottom: item.bottom, start: item.start },
                    onAppear: () => {
                      console.log("BindSheet onAppear.")
                    },
                    onDisappear: () => {
                      console.log("BindSheet onDisappear.")
                    }
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

