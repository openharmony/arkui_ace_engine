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

export default async function gridItemSelectableTest() {
  /*
* GridItem组件 Selectable属性
* 找到画面id为gridItemSelectable1, gridItemSelectable2的GridItem组件
* 找到画面文本为GridItemSelectable的button组件
* 获取gridItem1的selectable属性与期待值false比对
* 点击button，变更gridItem1的selectable属性值为true
* 获取gridItem1的selectable属性与期待值true比对
* 获取gridItem2的selectable属性与期待值true比对
*/
  defineTest('gridItemSelectableTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('gridItemSelectableTestDemo running')
    let driver: Tester = Tester.create()
    let gridItem1: Component = await driver.findComponent(Matcher.create().id('gridItemSelectable1').enabled(true))
    let gridItem2: Component = await driver.findComponent(Matcher.create().id('gridItemSelectable2').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('GridItemSelectable').enabled(true))

    let selectable1: string = await gridItem1.getInspectorInfo()
    assertFalse(JSON.parse(selectable1).$attrs.selectable)
    await button.tap()
    let selectable2: string = await gridItem1.getInspectorInfo()
    assertTrue(JSON.parse(selectable2).$attrs.selectable)
    let selectable3: string = await gridItem2.getInspectorInfo()
    assertTrue(JSON.parse(selectable3).$attrs.selectable)
  })
}