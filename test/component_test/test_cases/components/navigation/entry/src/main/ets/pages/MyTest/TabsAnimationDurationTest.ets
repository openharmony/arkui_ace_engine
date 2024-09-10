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
import { assertEqual, Component, defineTest, Matcher, TestCaseLevel, Tester } from '@ohos.arkui.componentTest'

export default async function tabsAnimationDurationTest() {
  /*
* Tabs组件 AnimationDuration属性
* 找到画面id为tabsAnimationDuration的Tabs组件
* 找到画面文本为TabsAnimationDuration的Button组件
* 获取tabs的AnimationDuration属性与期待值10比对
* 点击button，变更tabs的AnimationDuration属性值为600
* 获取tabs的AnimationDuration属性与期待值600比对
*/
  defineTest('tabsAnimationDurationTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('tabsAnimationDurationTestDemo running')
    let driver: Tester = Tester.create()
    let tabs: Component = await driver.findComponent(Matcher.create().id('tabsAnimationDuration').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('TabsAnimationDuration').enabled(true))

    let animationDuration1: string = await tabs.getInspectorInfo()
    assertEqual(JSON.parse(animationDuration1).$attrs.animationDuration, 10)
    await button.tap()
    let animationDuration2: string = await tabs.getInspectorInfo()
    assertEqual(JSON.parse(animationDuration2).$attrs.animationDuration, 600)
  }, 0)
}