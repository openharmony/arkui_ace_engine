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

export default async function gridSupportAnimationTest() {
  /*
  * Grid组件 SupportAnimation属性
  * 找到画面id为gridSupportAnimation的Grid组件
  * 找到画面文本为GridSupportAnimation的Button组件
  * 获取gridSupportAnimation的SupportAnimation属性与期待值true比对
  * 点击button，变更gridSupportAnimation的SupportAnimation属性值为false
  * 获取gridSupportAnimation的SupportAnimation属性与期待值false比对
  */
  defineTest('gridSupportAnimationTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('gridSupportAnimationTestDemo running')
    let driver: Tester = Tester.create()
    let gridSupportAnimation: Component =
      await driver.findComponent(Matcher.create().id('gridSupportAnimation').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('GridSupportAnimation').enabled(true))

    let supportAnimation1: string = await gridSupportAnimation.getInspectorInfo()
    assertTrue(JSON.parse(supportAnimation1).$attrs.supportAnimation)
    await button.tap()
    let supportAnimation2: string = await gridSupportAnimation.getInspectorInfo()
    assertFalse(JSON.parse(supportAnimation2).$attrs.supportAnimation)
  }, 0)
}