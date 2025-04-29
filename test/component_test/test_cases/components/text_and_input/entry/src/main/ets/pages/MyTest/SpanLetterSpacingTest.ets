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

export default async function spanLetterSpacingTest() {
  /*
   * Span组件 LetterSpacing属性
   * 找到画面id为spanLetterSpacing1的Span组件
   * 找到画面文本为SpanLetterSpacing的Button组件
   * 获取span的LetterSpacing属性与期待值'10px'比对
   * 点击button，变更span的LetterSpacing属性值为10
   * 获取span的LetterSpacing属性与期待值10比对
   */
  defineTest('spanLetterSpacingTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("spanLetterSpacingTestDemo running")
    let driver: Tester = Tester.create()
    let span: Component = await driver.findComponent(Matcher.create().id('spanLetterSpacing1').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('SpanLetterSpacing').enabled(true))

    assertFalse(span == null)
    let letterSpacing1: string = await span.getInspectorInfo()
    assertEqual(JSON.parse(letterSpacing1).$attrs.letterSpacing, '10px')

    await button.tap()
    let letterSpacing2: string = await span.getInspectorInfo()
    assertEqual(JSON.parse(letterSpacing2).$attrs.letterSpacing, 10)
  }, 0)
}