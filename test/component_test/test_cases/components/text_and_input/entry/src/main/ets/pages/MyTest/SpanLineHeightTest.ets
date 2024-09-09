/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
import {
  assertEqual,
  assertFalse,
  Component,
  defineTest,
  Matcher,
  TestCaseLevel,
  Tester
} from '@ohos.arkui.componentTest';

export default async function spanLineHeightTest() {
  /*
   * Span组件 LineHeight属性
   * 找到画面id为spanLineHeight1的Span组件
   * 找到画面文本为SpanLineHeight1,SpanLineHeight2的Button组件
   * 获取span的LineHeight属性与期待值50比对
   * 点击button1，变更span的LineHeight属性值为'50px'
   * 获取span的LineHeight属性与期待值'50px'比对
   * 点击button2，变更span的LineHeight属性值为$r('app.string.line_height')
   * 获取span的LineHeight属性与期待值$r('app.string.line_height')比对
   */
  defineTest('spanLineHeightTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("spanLineHeightTestDemo running")
    let driver: Tester = Tester.create()
    let span: Component = await driver.findComponent(Matcher.create().id('spanLineHeight1').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('SpanLineHeight1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('SpanLineHeight2').enabled(true))

    assertFalse(span == null)
    let lineHeight1: string = await span.getInspectorInfo()
    assertEqual(JSON.parse(lineHeight1).$attrs.lineHeight, 50)

    await button1.tap()
    let lineHeight2: string = await span.getInspectorInfo()
    assertEqual(JSON.parse(lineHeight2).$attrs.lineHeight, '50px')
    await button2.tap()
    let lineHeight3: string = await span.getInspectorInfo()
    assertEqual(JSON.parse(lineHeight3).$attrs.lineHeight, $r('app.string.line_height'))
  }, 0)
}