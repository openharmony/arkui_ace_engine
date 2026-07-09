'use static';

/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
import { Entry, Component, Scroll, Text, TextAlign, Button,
  Column, Color, ClickEvent } from '@ohos.arkui.component';

@Entry
@Component
struct Index {
  build(): void {
    Scroll() {
      Column() {
        Text('AccessibilityCustomCapi')
          .textAlign(TextAlign.Center)
          .fontSize(20)
          .margin({ bottom: 10 })
        this.NavButton('单实例', 'pages/PageAccessibility');
        this.NavButton('多实例', 'pages/PageAccessibilityMultiple');
        this.NavButton('非custom类型', 'pages/PageNoCustom');
        this.NavButton('弹窗测试场景', 'pages/PageCustomDialog');
        this.NavButton('弹窗测试场景-子窗', 'pages/PageCustomDialogSubWindow');
      }
    }
  }

  @Builder
  NavButton(name: string, routerUrl: string): void {
    Button(name)
      .id(name)
      .backgroundColor(Color.Blue)
      .fontSize(12)
      .height(24)
      .margin(3)
      .onClick((e: ClickEvent) => {
        let uiContext = this.getUIContext();
        let router = uiContext.getRouter();
        router.pushUrl({ url: routerUrl })
      })
  }
}
