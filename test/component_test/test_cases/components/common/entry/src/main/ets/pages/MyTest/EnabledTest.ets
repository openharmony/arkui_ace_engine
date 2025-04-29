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

import { assertFalse, assertTrue } from '@ohos.arkui.componentTest'
import { TestCaseLevel, defineTest } from '@ohos.arkui.componentTest'
import { Tester, Component, Matcher } from '@ohos.arkui.componentTest'

export default async function enabledTest() {
  /* Button组件enabled属性
   * 找到id为buttonEnabled的Button组件
   * 找到画面文本为ButtonEnabled2的Button组件
   * 获取Button1的enabled属性与期望值true比对
   * 点击button1,变更Button1的enabled属性值为false
   * 获取Button1的enabled属性与期待值false比对
   * */
  defineTest('enabledTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('enabledTestDemo running')
    let driver: Tester = Tester.create()
    let buttonEnabled: Component = await driver.findComponent(Matcher.create().id('buttonEnabled').enabled(true))
    let buttonClick: Component = await driver.findComponent(Matcher.create().text('ButtonEnabled2').enabled(true))
    let enabled1: boolean = await buttonEnabled.isEnabled()
    assertTrue(enabled1)

    await buttonClick.tap()
    let enabled2: boolean = await buttonEnabled.isEnabled()
    assertFalse(enabled2)
  }, 0)
}