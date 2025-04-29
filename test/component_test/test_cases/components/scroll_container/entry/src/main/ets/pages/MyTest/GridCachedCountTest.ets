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

export default async function gridCachedCountTest() {
  /*
  * Grid组件 CachedCount属性
  * 找到画面id为gridCachedCount1，gridCachedCount2的Grid组件
  * 找到画面文本为gridCachedCount的Button组件
  * 获取gridCachedCount1的CachedCount属性与期待值3比对
  * 获取gridCachedCount2的CachedCount属性与期待值1比对
  */
  defineTest('gridCachedCountTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('gridCachedCountTestDemo running')
    let driver: Tester = Tester.create()
    let gridCachedCount1: Component = await driver.findComponent(Matcher.create().id('gridCachedCount1').enabled(true))
    let gridCachedCount2: Component = await driver.findComponent(Matcher.create().id('gridCachedCount2').enabled(true))

    let cachedCount1: string = await gridCachedCount1.getInspectorInfo()
    assertEqual(JSON.parse(cachedCount1).$attrs.cachedCount, 3)
    let cachedCount2: string = await gridCachedCount2.getInspectorInfo()
    assertEqual(JSON.parse(cachedCount2).$attrs.cachedCount, 1)
  }, 0)
}