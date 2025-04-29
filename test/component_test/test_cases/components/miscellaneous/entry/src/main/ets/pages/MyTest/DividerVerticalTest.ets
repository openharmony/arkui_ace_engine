/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 // * You may obtain a copy of the License at
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
  assertFalse,
  assertTrue,
  Component,
  defineTest,
  Matcher,
  TestCaseLevel,
  Tester
} from '@ohos.arkui.componentTest'

export default async function dividerVerticalTest() {
  /*
   * Divider组件 Vertical 属性
   * 找到画面id为dividerVertical的Divider组件
   * 找到画面文本为DividerVertical的Button组件
   * 获取dividerVertical的vertical属性与期待值true比对
   * 点击button，变更dividerVertical的Vertical属性值为false
   * 获取dividerVertical的Vertical属性与期待值false比对
   */
  defineTest('dividerVerticalTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('dividerVerticalTestDemo running')
    let driver: Tester = Tester.create()
    let dividerVertical: Component = await driver.findComponent(Matcher.create().id('dividerVertical').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('DividerVertical').enabled(true))

    let vertical1: string = await dividerVertical.getInspectorInfo()
    assertTrue(JSON.parse(vertical1).$attrs.vertical)

    await button.tap()
    let vertical2: string = await dividerVertical.getInspectorInfo()
    assertFalse(JSON.parse(vertical2).$attrs.vertical)
  }, 0)
}