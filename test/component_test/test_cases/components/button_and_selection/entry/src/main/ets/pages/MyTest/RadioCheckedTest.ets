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
  assertFalse,
  assertTrue,
  Component,
  defineTest,
  Matcher,
  TestCaseLevel,
  Tester
} from '@ohos.arkui.componentTest'

export default async function radioCheckedTest() {
  /*
   * Radio组件 Checked属性
   * 找到画面id为radioChecked的Radio组件
   * 找到画面文本为RadioChecked的Button组件
   * 获取radioChecked的Checked属性与期待值true比对
   * 点击button，变更radioChecked的Checked属性值为false
   * 获取radioChecked的Checked属性与期待值false比对
   */
  defineTest('radioCheckedTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('radioCheckedTestDemo running')
    let driver: Tester = Tester.create()
    let radioChecked: Component = await driver.findComponent(Matcher.create().id('radioChecked').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('RadioChecked').enabled(true))

    let checked1: boolean = await radioChecked.isChecked()
    assertTrue(checked1)

    await button.tap()
    let checked2: boolean = await radioChecked.isChecked()
    assertFalse(checked2)
  }, 0)
}