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
import { assertEqual, assertTrue } from '@ohos.arkui.componentTest';
import { TestCaseLevel, defineTest } from '@ohos.arkui.componentTest'
import { Tester, Component, Matcher } from '@ohos.arkui.componentTest'

export default async function clickEffectTest() {
  /*
  * menu组件 clickEffect属性
  * 找到画面id为 menuClickEffect1 menuClickEffect2 的menu组件
  * 找到画面文本为 ButtonClickEffect1 的Button组件
  * 获取menuClickEffect1的ClickEffect.level属性与期待值"-1"比对
  * 获取menuClickEffect2的ClickEffect.level属性与期待值'1'比对
  * 点击button1，变更menuClickEffect2的ClickEffect属性值为ClickEffectLevel.LIGHT
  * 获取menuClickEffect2的ClickEffect属性与期待值ClickEffectLevel.LIGHT比对
  * 点击button2，变更menuClickEffect2的ClickEffect属性值为ClickEffectLevel.MIDDLE
  * 获取menuClickEffect2的ClickEffect属性与期待值ClickEffectLevel.MIDDLE比对
  * 点击button3，变更menuClickEffect2的ClickEffect属性值为ClickEffectLevel.HEAVY
  * 获取menuClickEffect2的ClickEffect属性与期待值ClickEffectLevel.HEAVY比对
  */
  defineTest('clickEffectTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("clickEffectTestDemo running")
    let driver: Tester = Tester.create()
    let menuClickEffect1: Component = await driver.findComponent(Matcher.create().id('menuClickEffect1').enabled(true))
    let menuClickEffect2: Component = await driver.findComponent(Matcher.create().id('menuClickEffect2').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('ButtonClickEffect1').enabled(true))
    let clickEffect1: string = await menuClickEffect1.getInspectorInfo()
    assertEqual(JSON.parse(clickEffect1).$attrs.clickEffect.level, "-1")
    let clickEffect2: string = await menuClickEffect2.getInspectorInfo()
    assertEqual(JSON.parse(clickEffect2).$attrs.clickEffect.level, '1')

    await button1.tap()
    let clickEffect3: string = await menuClickEffect2.getInspectorInfo()
    assertTrue(JSON.parse(clickEffect3).$attrs.clickEffect.level == ClickEffectLevel.LIGHT)

    await button1.tap()
    let clickEffect4: string = await menuClickEffect2.getInspectorInfo()
    assertTrue(JSON.parse(clickEffect4).$attrs.clickEffect.level == ClickEffectLevel.MIDDLE)

    await button1.tap()
    let clickEffect5: string = await menuClickEffect2.getInspectorInfo()
    assertTrue(JSON.parse(clickEffect5).$attrs.clickEffect.level == ClickEffectLevel.HEAVY)
  }, 0)
}