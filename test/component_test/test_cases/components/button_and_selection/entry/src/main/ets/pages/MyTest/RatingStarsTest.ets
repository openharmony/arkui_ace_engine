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

export default async function ratingStarsTest() {
  /*
   * Rating组件 Stars属性
   * 找到画面id为ratingStars1，ratingStars2的Rating组件
   * 找到画面文本为RatingStars的Button组件
   * 获取ratingStars1的Stars属性与期待值'5'比对
   * 获取ratingStars2的Stars属性与期待值'3'比对
   * 点击button，变更ratingStars2的Stars属性值为'2'
   * 获取ratingStars2的Stars属性与期待值'2'比对
   */
  defineTest('ratingStarsTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('ratingStarsTestDemo running')
    let driver: Tester = Tester.create()
    let ratingStars1: Component = await driver.findComponent(Matcher.create().id('ratingStars1').enabled(true))
    let ratingStars2: Component = await driver.findComponent(Matcher.create().id('ratingStars2').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('RatingStars').enabled(true))

    let stars1: string = await ratingStars1.getInspectorInfo()
    assertEqual(JSON.parse(stars1).$attrs.stars, '5')

    let stars2: string = await ratingStars2.getInspectorInfo()
    assertEqual(JSON.parse(stars2).$attrs.stars, '3')

    await button.tap()
    let stars3: string = await ratingStars2.getInspectorInfo()
    assertEqual(JSON.parse(stars3).$attrs.stars, '2')
  }, 0)
}