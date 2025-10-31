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

interface Info {
  top?: ResourceColor | null | undefined;
  end?: ResourceColor | null | undefined;
  bottom?: ResourceColor | null | undefined;
  start?: ResourceColor | null | undefined;
}

@Entry
@Component
struct WebComponent {
  private scroller: Scroller = new Scroller()
  simpleList: Array<Info> = [
    { top: Color.Red, bottom: $r("app.color.pink"), start: 0x3848C0, end: 'rgba(12, 193, 29, 1.00)' },
    { top: -2, end: "", bottom: null, start: undefined },
    { top: 0xEE0B7C, bottom: Color.Black },
    { start: 0xEE0B7C, end: Color.Black },
    { start: 0xEE0B7C, top: Color.Black },
  ];
  @State language: string = I18n.System.getSystemLanguage();
  @State caseName: string = '';
  @State value: EdgeWidths | null = null;
  case: string = 'borderColor';

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
                List() {
                  ListItem() {
                    Text(Constants.getCaseName(this.case, index + 1))
                  }
                  ListItem() {
                    Text(Constants.getCaseName(this.case, index + 1))
                  }
                  ListItem() {
                    Text(Constants.getCaseName(this.case, index + 1))
                  }
                }.height("10%").width('50%')
                .key(Constants.getCaseName(this.case, index + 1))
                .border({ width: 4, color: { top: item.top, end: item.end, bottom: item.bottom, start: item.start } })
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
                  console.log("borderColor " + strJson)
                })
              })
            }
          }.margin({ right: 15 })
        }
        .backgroundColor(Color.Pink)
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

