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

export default async function spanTextCaseTest() {
  /*
   * Span组件 TextCase属性
   * 找到画面id为spanTextCase1,spanTextCase2的Span组件
   * 找到画面文本为SpanTextCase的Button组件
   * 获取span1的TextCase属性与期待值TextCase.LowerCase比对
   * 获取span2的TextCase属性与期待值TextCase.Normal比对
   * 点击button，变更span2的TextCase属性值为TextCase.UpperCase
   * 获取span2的TextCase属性与期待值TextCase.UpperCase比对
   */
  defineTest('spanTextCaseTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("spanTextCaseTestDemo running")
    let driver: Tester = Tester.create()
    let span1: Component = await driver.findComponent(Matcher.create().id('spanTextCase1').enabled(true))
    let span2: Component = await driver.findComponent(Matcher.create().id('spanTextCase2').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('SpanTextCase').enabled(true))

    assertFalse(span1 == null)
    let textCase1: string = await span1.getInspectorInfo()
    assertEqual(JSON.parse(textCase1).$attrs.textCase, TextCase.LowerCase)
    let textCase2: string = await span2.getInspectorInfo()
    assertEqual(JSON.parse(textCase2).$attrs.textCase, TextCase.Normal)

    await button.tap()
    let textCase3: string = await span2.getInspectorInfo()
    assertEqual(JSON.parse(textCase3).$attrs.textCase, TextCase.UpperCase)
  }, 0)
}