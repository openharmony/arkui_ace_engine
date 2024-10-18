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
import { assertEqual } from '@ohos.arkui.componentTest'
import { TestCaseLevel, defineTest } from '@ohos.arkui.componentTest'
import { Tester, Component, Matcher } from '@ohos.arkui.componentTest'

export default async function hoverEffectTest() {
  /*
  * 使用Column组件 HoverEffect属性
  * 找到画面id为columnHoverEffect的Column组件
  * 找到画面文本为 ButtonHoverEffect 的Button组件
  * 获取columnHoverEffect的HoverEffect属性与期待值HoverEffect.Auto比对
  * 点击button，变更columnHoverEffect的HoverEffect属性值为HoverEffect.Scale
  * 获取columnHoverEffect的HoverEffect属性与期待值HoverEffect.Scale比对
  * 点击button，变更columnHoverEffect的HoverEffect属性值为HoverEffect.Highlight
  * 获取columnHoverEffect的HoverEffect属性与期待值HoverEffect.Highlight比对
  * 点击button，变更columnHoverEffect的HoverEffect属性值为HoverEffect.None
  * 获取columnHoverEffect的HoverEffect属性与期待值HoverEffect.None比对
  */
  defineTest('hoverEffectTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('hoverEffectTestDemo running')
    let driver: Tester = Tester.create()
    let columnHoverEffect: Component =
      await driver.findComponent(Matcher.create().id('columnHoverEffect').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('ButtonHoverEffect').enabled(true))
    let hoverEffect1: string = await columnHoverEffect.getInspectorInfo()
    assertEqual(JSON.parse(hoverEffect1).$attrs.hoverEffect, 'HoverEffect.Auto')

    await button.tap()
    let hoverEffect2: string = await columnHoverEffect.getInspectorInfo()
    assertEqual(JSON.parse(hoverEffect2).$attrs.hoverEffect, 'HoverEffect.Scale')

    await button.tap()
    let hoverEffect3: string = await columnHoverEffect.getInspectorInfo()
    assertEqual(JSON.parse(hoverEffect3).$attrs.hoverEffect, 'HoverEffect.Highlight')

    await button.tap()
    let hoverEffect4: string = await columnHoverEffect.getInspectorInfo()
    assertEqual(JSON.parse(hoverEffect4).$attrs.hoverEffect, 'HoverEffect.None')
  }, 0)
}