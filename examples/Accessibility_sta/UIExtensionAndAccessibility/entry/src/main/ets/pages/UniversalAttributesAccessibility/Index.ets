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

const ACCESSIBILITY_TEXT_ROUTE = 'pages/UniversalAttributesAccessibility/AccessibilityText';
const ACCESSIBILITY_GROUP_ROUTE = 'pages/UniversalAttributesAccessibility/AccessibilityGroup';
const ACCESSIBILITY_FOCUS_DRAW_LEVEL_ROUTE = 'pages/UniversalAttributesAccessibility/AccessibilityFocusDrawLevel';
const ACCESSIBILITY_TEXT_CASE01_ROUTE = 'pages/UniversalAttributesAccessibility/AccessibilityTextCase01';
const ACCESSIBILITY_TEXT_CASE02_ROUTE = 'pages/UniversalAttributesAccessibility/AccessibilityTextCase02';
const ACCESSIBILITY_DESCRIPTION_CASE01_ROUTE = 'pages/UniversalAttributesAccessibility/AccessibilityDescriptionCase01';
const ACCESSIBILITY_DESCRIPTION_CASE02_ROUTE = 'pages/UniversalAttributesAccessibility/AccessibilityDescriptionCase02';
const ACCESSIBILITY_GROUP_CASE01_ROUTE = 'pages/UniversalAttributesAccessibility/AccessibilityGroupCase01';
const ACCESSIBILITY_GROUP_CASE02_ROUTE = 'pages/UniversalAttributesAccessibility/AccessibilityGroupCase02';
const ACCESSIBILITY_LEVEL_CASE01_ROUTE = 'pages/UniversalAttributesAccessibility/AccessibilityLevelCase01';

@Entry
@Component
struct AccessibilityExample {
  build(): void {
    Scroll() {
      Column() {
        Text('UniversalAttributesAccessibility')
          .textAlign(TextAlign.Center)
          .fontSize(20)
          .margin({ bottom: 10 })
        this.NavButton('AccessibilityText', ACCESSIBILITY_TEXT_ROUTE);
        this.NavButton('AccessibilityGroup', ACCESSIBILITY_GROUP_ROUTE);
        this.NavButton('AccessibilityFocusDrawLevel', ACCESSIBILITY_FOCUS_DRAW_LEVEL_ROUTE);
        this.NavButton('AccessibilityTextCase01', ACCESSIBILITY_TEXT_CASE01_ROUTE);
        this.NavButton('AccessibilityTextCase02', ACCESSIBILITY_TEXT_CASE02_ROUTE);
        this.NavButton('AccessibilityDescriptionCase01', ACCESSIBILITY_DESCRIPTION_CASE01_ROUTE);
        this.NavButton('AccessibilityDescriptionCase02', ACCESSIBILITY_DESCRIPTION_CASE02_ROUTE);
        this.NavButton('AccessibilityGroupCase01', ACCESSIBILITY_GROUP_CASE01_ROUTE);
        this.NavButton('AccessibilityGroupCase02', ACCESSIBILITY_GROUP_CASE02_ROUTE);
        this.NavButton('AccessibilityLevelCase01', ACCESSIBILITY_LEVEL_CASE01_ROUTE);
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
