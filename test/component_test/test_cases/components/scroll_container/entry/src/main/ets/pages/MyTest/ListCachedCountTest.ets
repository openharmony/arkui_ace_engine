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

export default async function listCachedCountTest() {
  /*
   * List组件 CachedCount属性
   * 找到画面id为listCachedCount1,listCachedCount2的List组件
   * 获取list1的CachedCount属性与期待值10比对
   * 获取list2的CachedCount属性与期待值1比对
   */
  defineTest('listCachedCountTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('listCachedCountTestDemo running')
    let driver: Tester = Tester.create()
    let list1: Component = await driver.findComponent(Matcher.create().id('listCachedCount1').enabled(true))
    let list2: Component = await driver.findComponent(Matcher.create().id('listCachedCount2').enabled(true))

    let CachedCount1: string = await list1.getInspectorInfo()
    assertEqual(JSON.parse(CachedCount1).$attrs.cachedCount, '10')
    let CachedCount2: string = await list2.getInspectorInfo()
    assertEqual(JSON.parse(CachedCount2).$attrs.cachedCount, '1')
  }, 0)
}