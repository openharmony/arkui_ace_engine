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

export default async function tabsFadingEdgeTest() {
  /*
* Tabs组件 FadingEdge属性
* 找到画面id为tabsFadingEdge1、 tabsFadingEdge2的Tabs组件
* 找到画面文本为TabsFadingEdge的Button组件
* 获取tabs1的FadingEdge属性与期待值true比对
* 获取tabs2的FadingEdge属性与期待值true比对
* 点击button，变更tabs1、 tabs2的FadingEdge属性值为false
* 获取tabs1的FadingEdge属性与期待值false比对
* 获取tabs2的FadingEdge属性与期待值false比对
*/
  defineTest('tabsFadingEdgeTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('tabsFadingEdgeTestDemo running')
    let driver: Tester = Tester.create()
    let tabs1: Component = await driver.findComponent(Matcher.create().id('tabsFadingEdge1').enabled(true))
    let tabs2: Component = await driver.findComponent(Matcher.create().id('tabsFadingEdge2').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('TabsFadingEdge').enabled(true))

    let fadingEdge1: string = await tabs1.getInspectorInfo()
    assertTrue(JSON.parse(fadingEdge1).$attrs.fadingEdge)
    await button.tap()
    let fadingEdge2: string = await tabs1.getInspectorInfo()
    assertFalse(JSON.parse(fadingEdge2).$attrs.fadingEdge)

    let fadingEdge3: string = await tabs2.getInspectorInfo()
    assertFalse(JSON.parse(fadingEdge3).$attrs.fadingEdge)
    await button.tap()
    let fadingEdge4: string = await tabs2.getInspectorInfo()
    assertTrue(JSON.parse(fadingEdge4).$attrs.fadingEdge)
  }, 0)
}