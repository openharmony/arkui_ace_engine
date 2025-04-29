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

export default async function navigationHideBackButtonTest() {
  /*
  * Navigation组件 HideBackButton属性
  * 找到画面id为navigationHideBackButton的Navigation组件
  * 找到画面文本为NavigationHideBackButton的Button组件
  * 获取navigation1的HideBackButton属性与期待值True比对
  * 点击button1，变更navigation1的HideBackButton属性值为False
  * 获取navigation1的HideBackButton属性与期待值False比对
  */
  defineTest('navigationHideBackButtonTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("navigationHideBackButtonTestDemo running")
    let driver: Tester = Tester.create()
    let navigation1: Component =
      await driver.findComponent(Matcher.create().id('navigationHideBackButton').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('NavigationHideBackButton').enabled(true))
    let hideBackButton1: string = await navigation1.getInspectorInfo()
    assertTrue(JSON.parse(hideBackButton1).$attrs.hideBackButton)
    await button1.tap()
    let hideBackButton2: string = await navigation1.getInspectorInfo()
    assertFalse(JSON.parse(hideBackButton2).$attrs.hideBackButton)
  }, 0)
}