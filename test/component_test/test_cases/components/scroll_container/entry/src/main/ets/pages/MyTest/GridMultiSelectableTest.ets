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

export default async function gridMultiSelectableTest() {
  /*
  * Grid组件 MultiSelectable属性
  * 找到画面id为gridMultiSelectable的Grid组件
  * 找到画面文本为GridMultiSelectable的Button组件
  * 获取gridMultiSelectable的MultiSelectable属性与期待值true比对
  * 点击button，变更gridMultiSelectable的MultiSelectable属性值为false
  * 获取gridMultiSelectable的MultiSelectable属性与期待值false比对
  */
  defineTest('gridMultiSelectableTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('gridMultiSelectableTestDemo running')
    let driver: Tester = Tester.create()
    let gridMultiSelectable: Component =
      await driver.findComponent(Matcher.create().id('gridMultiSelectable').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('GridMultiSelectable').enabled(true))

    let multiSelectable1: string = await gridMultiSelectable.getInspectorInfo()
    assertTrue(JSON.parse(multiSelectable1).$attrs.multiSelectable)
    await button.tap()
    let multiSelectable2: string = await gridMultiSelectable.getInspectorInfo()
    assertFalse(JSON.parse(multiSelectable2).$attrs.multiSelectable)
  }, 0)
}