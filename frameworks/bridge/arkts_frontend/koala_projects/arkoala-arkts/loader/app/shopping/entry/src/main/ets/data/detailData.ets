/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
import { expect } from '@ohos/hypium'

import {
  SwiperModel, PhoneTypeModel, ShowImgModel, RecommendDataModel, GoodsInfoModel, ListDataModel
} from "../model/detailModel"

export const swiperData: Array<SwiperModel> = [
  new SwiperModel("/resources/detailImg/swiper/swiper1.png"),
  new SwiperModel("/resources/detailImg/swiper/swiper2.png"),
  new SwiperModel("/resources/detailImg/swiper/swiper3.png")
]

export const phoneTypeData: Array<PhoneTypeModel> = [
  new PhoneTypeModel("/resources/detailImg/deliver/deliver_type1.png", "亮黑色"),
  new PhoneTypeModel("/resources/detailImg/deliver/deliver_type2.png", "星河银"),
  new PhoneTypeModel("/resources/detailImg/deliver/deliver_type3.png", "翡翠冷"),
  new PhoneTypeModel("/resources/detailImg/deliver/deliver_type4.png", "紫罗兰"),
  new PhoneTypeModel("/resources/detailImg/deliver/deliver_type5.png", "丹霞橙")
]

export const showImgData: Array<ShowImgModel> = [
  new ShowImgModel("/resources/detailImg/evaluation/buyersShow1.png"),
  new ShowImgModel("/resources/detailImg/evaluation/buyersShow2.png"),
  new ShowImgModel("/resources/detailImg/evaluation/buyersShow3.png"),
  new ShowImgModel("/resources/detailImg/evaluation/buyersShow4.png")
]

export const recommendData: Array<RecommendDataModel> = [
  new RecommendDataModel("/resources/detailImg/recommendImg/recommendImg/recommendImg1.png", "XX Mate 40 5G 全网通", "￥196"),
  new RecommendDataModel("/resources/detailImg/recommendImg/recommendImg/recommendImg2.png", "XX手机 大多数人的选择", "￥339.98"),
  new RecommendDataModel("/resources/detailImg/recommendImg/recommendImg/recommendImg3.png", "XX Mate 40 Pro 5G 全网通", "￥188"),
  new RecommendDataModel("/resources/detailImg/recommendImg/recommendImg/recommendImg4.png", "XX Mate 40 5G 全网通", "￥196"),
  new RecommendDataModel("/resources/detailImg/recommendImg/recommendImg/recommendImg5.png", "XX手机 大多数人的选择", "￥339.98"),
  new RecommendDataModel("/resources/detailImg/recommendImg/recommendImg/recommendImg6.png", "XX Mate 40 Pro 5G 全网通", "￥188")
]

export const goodsInfoData: Array<GoodsInfoModel> = [
  new GoodsInfoModel("/resources/detailImg/recommendImg/attention/list_1.png"),
  new GoodsInfoModel("/resources/detailImg/recommendImg/attention/list_1.png"),
  new GoodsInfoModel("/resources/detailImg/recommendImg/attention/list_2.png"),
  new GoodsInfoModel("/resources/detailImg/recommendImg/attention/list_3.png"),
  new GoodsInfoModel("/resources/detailImg/recommendImg/attention/list_4.png"),
  new GoodsInfoModel("/resources/detailImg/recommendImg/attention/list_4.png"),
  new GoodsInfoModel("/resources/detailImg/recommendImg/attention/list_5.png"),
  new GoodsInfoModel("/resources/detailImg/recommendImg/attention/list_5.png"),
  new GoodsInfoModel("/resources/detailImg/recommendImg/attention/list_5.png"),
  new GoodsInfoModel("/resources/detailImg/recommendImg/attention/list_5.png"),
  new GoodsInfoModel("/resources/detailImg/recommendImg/attention/list_5.png"),
  new GoodsInfoModel("/resources/detailImg/recommendImg/attention/list_5.png"),
  new GoodsInfoModel("/resources/detailImg/recommendImg/attention/list_6.png"),
  new GoodsInfoModel("/resources/detailImg/recommendImg/attention/list_6.png"),
  new GoodsInfoModel("/resources/detailImg/recommendImg/attention/list_6.png"),
  new GoodsInfoModel("/resources/detailImg/recommendImg/attention/list_6.png"),
  new GoodsInfoModel("/resources/detailImg/recommendImg/attention/list_4.png"),
  new GoodsInfoModel("/resources/detailImg/recommendImg/attention/list_5.png"),
  new GoodsInfoModel("/resources/detailImg/recommendImg/attention/list_6.png"),
  new GoodsInfoModel("/resources/detailImg/recommendImg/attention/list_5.png"),
  new GoodsInfoModel("/resources/detailImg/recommendImg/attention/list_4.png"),
  new GoodsInfoModel("/resources/detailImg/recommendImg/attention/list_5.png"),
  new GoodsInfoModel("/resources/detailImg/recommendImg/attention/list_6.png")
]

export const listData: Array<ListDataModel> = [
  new ListDataModel("/resources/detailImg/recommendImg/recommendImg/recommendImg1.png", "XX Mate 40 5G 全网通", "￥196"),
  new ListDataModel("/resources/detailImg/recommendImg/recommendImg/recommendImg2.png", "XX手机 大多数人的选择", "￥339.98"),
  new ListDataModel("/resources/detailImg/recommendImg/recommendImg/recommendImg3.png", "XX Mate 40 Pro 5G 全网通", "￥188"),
  new ListDataModel("/resources/detailImg/recommendImg/recommendImg/recommendImg4.png", "XX Mate 40 5G 全网通", "￥196"),
  new ListDataModel("/resources/detailImg/recommendImg/recommendImg/recommendImg5.png", "XX手机 大多数人的选择", "￥339.98"),
  new ListDataModel("/resources/detailImg/recommendImg/recommendImg/recommendImg6.png", "XX Mate 40 Pro 5G 全网通", "￥188"),
  new ListDataModel("/resources/detailImg/recommendImg/recommendImg/recommendImg7.png", "XX Mate 40 5G 全网通", "￥196"),
  new ListDataModel("/resources/detailImg/recommendImg/recommendImg/recommendImg8.png", "XX手机 大多数人的选择", "￥339.98"),
  new ListDataModel("/resources/detailImg/recommendImg/recommendImg/recommendImg9.png", "XX Mate 40 Pro 5G 全网通", "￥188"),
  new ListDataModel("/resources/detailImg/recommendImg/recommendImg/recommendImg10.png", "XX Mate 40 5G 全网通", "￥196"),
  new ListDataModel("/resources/detailImg/recommendImg/recommendImg/recommendImg1.png", "XX手机 大多数人的选择", "￥339.98"),
  new ListDataModel("/resources/detailImg/recommendImg/recommendImg/recommendImg2.png", "XX Mate 40 Pro 5G 全网通", "￥188"),
  new ListDataModel("/resources/detailImg/recommendImg/recommendImg/recommendImg3.png", "XX Mate 40 5G 全网通", "￥196"),
  new ListDataModel("/resources/detailImg/recommendImg/recommendImg/recommendImg4.png", "XX手机 大多数人的选择", "￥339.98"),
  new ListDataModel("/resources/detailImg/recommendImg/recommendImg/recommendImg5.png", "XX Mate 40 Pro 5G 全网通", "￥188"),
  new ListDataModel("/resources/detailImg/recommendImg/recommendImg/recommendImg6.png", "XX Mate 40 5G 全网通", "￥196"),
  new ListDataModel("/resources/detailImg/recommendImg/recommendImg/recommendImg7.png", "XX手机 大多数人的选择", "￥339.98"),
  new ListDataModel("/resources/detailImg/recommendImg/recommendImg/recommendImg8.png","XX Mate 40 Pro 5G 全网通","￥188"),
  new ListDataModel("/resources/detailImg/recommendImg/recommendImg/recommendImg9.png","XX Mate 40 5G 全网通","￥196"),
  new ListDataModel("/resources/detailImg/recommendImg/recommendImg/recommendImg10.png","XX手机 大多数人的选择","￥339.98"),
  new ListDataModel("/resources/detailImg/recommendImg/recommendImg/recommendImg1.png","XX Mate 40 Pro 5G 全网通","￥188"),
  new ListDataModel("/resources/detailImg/recommendImg/recommendImg/recommendImg2.png","XX Mate 40 5G 全网通","￥196"),
  new ListDataModel("/resources/detailImg/recommendImg/recommendImg/recommendImg3.png","XX手机 大多数人的选择","￥339.98"),
  new ListDataModel("/resources/detailImg/recommendImg/recommendImg/recommendImg4.png","XX Mate 40 Pro 5G 全网通","￥188"),
  new ListDataModel("/resources/detailImg/recommendImg/recommendImg/recommendImg5.png", "XX Mate 40 5G 全网通","￥196"),
  new ListDataModel("/resources/detailImg/recommendImg/recommendImg/recommendImg6.png", "XX手机 大多数人的选择","￥339.98"),
  new ListDataModel("/resources/detailImg/recommendImg/recommendImg/recommendImg7.png", "XX Mate 40 Pro 5G 全网通", "￥188"),
  new ListDataModel("/resources/detailImg/recommendImg/recommendImg/recommendImg8.png", "XX Mate 40 5G 全网通", "￥196"),
  new ListDataModel("/resources/detailImg/recommendImg/recommendImg/recommendImg9.png", "XX手机 大多数人的选择", "￥339.98"),
  new ListDataModel("/resources/detailImg/recommendImg/recommendImg/recommendImg10.png", "XX Mate 40 Pro 5G 全网通", "￥188"),
  new ListDataModel("/resources/detailImg/recommendImg/recommendImg/recommendImg1.png", "XX Mate 40 5G 全网通", "￥196"),
  new ListDataModel("/resources/detailImg/recommendImg/recommendImg/recommendImg2.png", "XX手机 大多数人的选择", "￥339.98"),
  new ListDataModel("/resources/detailImg/recommendImg/recommendImg/recommendImg3.png", "XX Mate 40 Pro 5G 全网通", "￥188"),
  new ListDataModel("/resources/detailImg/recommendImg/recommendImg/recommendImg4.png", "XX Mate 40 5G 全网通", "￥196"),
  new ListDataModel("/resources/detailImg/recommendImg/recommendImg/recommendImg5.png", "XX手机 大多数人的选择", "￥339.98"),
  new ListDataModel("/resources/detailImg/recommendImg/recommendImg/recommendImg6.png", "XX Mate 40 Pro 5G 全网通", "￥188"),
  new ListDataModel("/resources/detailImg/recommendImg/recommendImg/recommendImg7.png", "XX Mate 40 Pro 5G 全网通","￥188")
]