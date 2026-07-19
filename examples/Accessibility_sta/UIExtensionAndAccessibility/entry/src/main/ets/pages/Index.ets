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

import { Builder, Entry, Component, Scroll, Text, TextAlign, Button,
  Column, Color, ClickEvent } from '@ohos.arkui.component';

const UI_EXTENSION_ROUTE = 'pages/UIExtensionComponent/Index';
const EMBEDDED_ROUTE = 'pages/EmbeddedComponent/Index';
const SCREEN_ROUTE = 'pages/FullScreenLaunchComponent/Index';
const ACCESSIBILITY_INDEX_ROUTE = 'pages/UniversalAttributesAccessibility/Index';
const SHOW_EMBEDDED_ROUTE = 'pages/ShowEmbeddedComponent/ShowPage';


@Entry
@Component
struct Index {
  build(): void {
    Scroll() {
      Column() {
        Text('UIExtensionAndAccessibility')
          .textAlign(TextAlign.Center)
          .fontSize(20)
          .margin({ bottom: 10 })
        this.NavButton('UIExtensionComponent', UI_EXTENSION_ROUTE);
        this.NavButton('EmbeddedComponent', EMBEDDED_ROUTE);
        this.NavButton('FullScreenLaunchComponent', SCREEN_ROUTE);
        this.NavButton('Accessibility', ACCESSIBILITY_INDEX_ROUTE);
        this.NavButton('ShowPage', SHOW_EMBEDDED_ROUTE);
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
        router.pushUrl({ url: routerUrl})
      })
  }
}
