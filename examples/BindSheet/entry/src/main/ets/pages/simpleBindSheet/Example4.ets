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
// xxx.ets
@Entry
@Component
struct bindSheetExample4 {
  @State isShow: boolean = false;

  @Builder
  myBuilder() {
    Column() {
      Button("CONTEXT")
        .margin(10)
        .fontSize(20)
    }
  }

  build() {
    Column() {
      Button("NoRegisterSpringback")
        .onClick(() => {
          this.isShow = true;
        })
        .fontSize(20)
        .margin(10)
        .bindSheet($$this.isShow, this.myBuilder(), {
          height: SheetSize.MEDIUM,
          blurStyle: BlurStyle.Thick,
          showClose: true,
          title: { title: "title", subtitle: "subtitle" },
          preferType: SheetType.CENTER,

          onWillDismiss: ((dismissSheetAction: DismissSheetAction) => {
            if (dismissSheetAction.reason == DismissReason.SLIDE_DOWN) {
              dismissSheetAction.dismiss();// 注册dismiss行为
            }
          }),

          onWillSpringBackWhenDismiss: ((SpringBackAction: SpringBackAction) => {
            // 没有注册springBack，下拉半模态页面无回弹行为
            // SpringBackAction.springBack();
          }),
        })
    }
  }
}