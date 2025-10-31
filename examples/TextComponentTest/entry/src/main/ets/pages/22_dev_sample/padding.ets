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
      top: LengthMetrics.lpx(2),
      end: LengthMetrics.px(3),
      bottom: LengthMetrics.vp(3),
      start: LengthMetrics.fp(5)
    },
    { top: LengthMetrics.lpx(-2), end: LengthMetrics.lpx(0), bottom: null, start: undefined },
    { end: LengthMetrics.lpx(2), start: LengthMetrics.px(3) },
    { top: LengthMetrics.vp(2), bottom: LengthMetrics.percent(0.08) },
    { start: LengthMetrics.fp(2), top: LengthMetrics.lpx(3) },
  ];
  @State language: string = I18n.System.getSystemLanguage();
  @State caseName: string = '';
  @State value: EdgeWidths | null = null;
  case: string = 'padding';

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
left: ${this.value?.left}
top: ${this.value?.top}
right: ${this.value?.right}
bottom: ${this.value?.bottom}`)

      Stack({ alignContent: Alignment.End }) {
        Scroll(this.scroller) {
          Flex({ direction: FlexDirection.Column }) {
            Column({ space: 10 }) {
              ForEach(this.simpleList, (item: Info, index: number) => {
                Row() {
                  Text('caseName: ' + Constants.getCaseName(this.case, index + 1))
                    .borderWidth(2)
                    .backgroundColor(Color.Pink)
                }
                .key(Constants.getCaseName(this.case, index + 1))
                .borderWidth(2)
                .backgroundColor(Color.Yellow)
                .padding({ top: item.top, end: item.end, bottom: item.bottom, start: item.start })

                Button("获取组件信息:" + Constants.getCaseName(this.case, index + 1)).onClick(() => {
                  let strJson = getInspectorByKey(Constants.getCaseName(this.case, index + 1));
                  let obj: ESObject = JSON.parse(strJson);
                  let padding: ESObject = JSON.parse(obj.$attrs.padding);
                  this.caseName = Constants.getCaseName(this.case, index + 1);
                  this.value = {
                    left: padding.left,
                    top: padding.top,
                    right: padding.right,
                    bottom: padding.bottom
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

