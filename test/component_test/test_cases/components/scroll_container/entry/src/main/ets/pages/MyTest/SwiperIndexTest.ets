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

export default async function swiperIndexTest() {
  /*
* Swiper组件 Index属性
* 找到画面id为swiperIndex1，swiperIndex2的Swiper组件
* 找到画面文本为SwiperIndex1的Button组件
* 获取swiperIndex1的Index属性与期待值0比对
* 获取swiperIndex2的Index属性与期待值1比对
* 点击button1，变更swiperIndex2的Index属性值为0
* 获取swiperIndex2的Index属性与期待值0比对
*/
  defineTest('swiperIndexTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('swiperIndexTestDemo running')
    let driver: Tester = Tester.create()
    let swiper1: Component = await driver.findComponent(Matcher.create().id('swiperIndex1').enabled(true))
    let swiper2: Component = await driver.findComponent(Matcher.create().id('swiperIndex2').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('SwiperIndex1').enabled(true))
    let index1: string = await swiper1.getInspectorInfo()
    let index2: string = await swiper2.getInspectorInfo()
    assertEqual(JSON.parse(index2).$attrs.index, '1')
    await button1.tap()
    let index3: string = await swiper2.getInspectorInfo()
    assertEqual(JSON.parse(index3).$attrs.index, '0')
  }, 0)
}