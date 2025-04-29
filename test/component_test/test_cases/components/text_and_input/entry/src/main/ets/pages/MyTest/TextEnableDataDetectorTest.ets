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
import { assertTrue, assertFalse, assertEqual } from '@ohos.arkui.componentTest';
import { TestCaseLevel, defineTest } from '@ohos.arkui.componentTest'
import { Tester, Component, Matcher } from '@ohos.arkui.componentTest'

export default async function textEnableDataDetectorTest() {
  /*
   * Text组件 EnableDataDetector属性
   * 找到画面id为textEnableDataDetector1,textEnableDataDetector2的Text组件
   * 找到画面文本为TextEnableDataDetector的Button组件
   * 获取text1的EnableDataDetector属性与期待值true比对
   * 获取text2的EnableDataDetector属性与期待值true比对
   * 点击button1，变更text1的EnableDataDetector属性值为false
   * 获取text1的EnableDataDetector属性与期待值false比对
   */
  defineTest('textEnableDataDetectorTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("textEnableDataDetectorTestDemo running")
    let driver: Tester = Tester.create()
    let text1: Component = await driver.findComponent(Matcher.create().id('textEnableDataDetector1').enabled(true))
    let text2: Component = await driver.findComponent(Matcher.create().id('textEnableDataDetector2').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('TextEnableDataDetector').enabled(true))

    let enableDataDetector1: string = await text1.getInspectorInfo()
    assertTrue(JSON.parse(enableDataDetector1).$attrs.enableDataDetector)
    let enableDataDetector2: string = await text2.getInspectorInfo()
    assertTrue(JSON.parse(enableDataDetector2).$attrs.enableDataDetector)

    await button.tap()
    let enableDataDetector3: string = await text1.getInspectorInfo()
    assertFalse(JSON.parse(enableDataDetector3).$attrs.enableDataDetector)
  }, 0)
}