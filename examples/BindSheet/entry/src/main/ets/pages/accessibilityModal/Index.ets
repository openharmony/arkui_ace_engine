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
@Entry
@Component
struct BindSheetExample {
  @State isShowInModal: boolean = false;
  @State isShowNotInModal: boolean = false;
  @State message: string = 'Hello World';

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
      Button("Sheet not in modal")
        .onClick(() => {
          this.isShowNotInModal = true;
        })
        .fontSize(20)
        .margin(10)
        .bindSheet($$this.isShowNotInModal, this.myBuilder(), {
          height: SheetSize.MEDIUM,
          blurStyle: BlurStyle.Thick,
          showClose: true,
          title: { title: "title", subtitle: "subtitle" },
          preferType: SheetType.CENTER,
          enableOutsideInteractive: true,
          shouldDismiss: (sheetDismiss: SheetDismiss) => {
            sheetDismiss.dismiss();
          },
          onWillDismiss: ((dismissSheetAction: DismissSheetAction) => {
            if (dismissSheetAction.reason == DismissReason.SLIDE_DOWN) {
              dismissSheetAction.dismiss(); //注册dismiss行为
            }
          }),
        })
      Button("Sheet in modal")
        .onClick(() => {
          this.isShowInModal = true;
        })
        .fontSize(20)
        .margin(10)
        .bindSheet($$this.isShowInModal, this.myBuilder(), {
          height: SheetSize.MEDIUM,
          blurStyle: BlurStyle.Thick,
          showClose: true,
          title: { title: "title", subtitle: "subtitle" },
          preferType: SheetType.CENTER,
          enableOutsideInteractive: false,
          shouldDismiss: (sheetDismiss: SheetDismiss) => {
            sheetDismiss.dismiss();
          },
          onWillDismiss: ((dismissSheetAction: DismissSheetAction) => {
            if (dismissSheetAction.reason == DismissReason.SLIDE_DOWN) {
              dismissSheetAction.dismiss(); //注册dismiss行为
            }
          }),
        })
      Text(this.message)
        .id('HelloWorld')
        .fontSize($r('app.float.page_text_font_size'))
        .margin(50)
        .fontWeight(FontWeight.Bold)
        .alignRules({
          center: { anchor: '__container__', align: VerticalAlign.Center },
          middle: { anchor: '__container__', align: HorizontalAlign.Center }
        })
        .onClick(() => {
          this.message = this.message === 'Hello World' ? 'Welcome' : 'Hello World';
        })
    }
  }
}