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

import { TabTitleModel, SearchTextModel, NavDataModel, SwiperModel, TitleBarModel, ProductDataModel, CoreDataModel,
  BoutiqueModel, InformationModel, ShopCartItemDataModel, FindTitleTextModel, FindImgSrcModel, FindImgIntroModel,
  FindImgNameModel, FindIconSrcModel, RecordModel, OrderModel, DiscountModel, ServiceModel } from '../model/homeModel'

export const tabTitleData: Array<TabTitleModel> = [
  new TabTitleModel(0, "/resources/homeImg/tabIcon/home.png","/resources/homeImg/tabIcon/homeSelected.png", "首页"),
  new TabTitleModel(1, "/resources/homeImg/tabIcon/classification.png", "/resources/homeImg/tabIcon/classificationSelected.png", "分类"),
  new TabTitleModel(2, "/resources/homeImg/tabIcon/find.png","/resources/homeImg/tabIcon/findSelected.png", "消息"),
]

export const findSearchTextData: Array<SearchTextModel> = [
  new SearchTextModel("精品好礼"),
  new SearchTextModel("节日大优惠"),
  new SearchTextModel("品牌手机")
]

export const navData: Array<NavDataModel> = [
  new NavDataModel("首页"),
  new NavDataModel("推荐"),
  new NavDataModel("XX专区"),
  new NavDataModel("新品频道"),
  new NavDataModel("智能家居"),
  new NavDataModel("拼团"),
  new NavDataModel("企业购物"),
  new NavDataModel("推荐"),
  new NavDataModel("XX专区"),
  new NavDataModel("新品频道"),
  new NavDataModel("智能家居"),
  new NavDataModel("拼团"),
  new NavDataModel("企业购物"),
  new NavDataModel("推荐"),
  new NavDataModel("XX专区"),
  new NavDataModel("新品频道"),
  new NavDataModel("智能家居"),
  new NavDataModel("拼团"),
  new NavDataModel("企业购物")
]

export const swiperData: Array<SwiperModel> = [
  new SwiperModel("/resources/homeImg/banner/banner1.jpg"),
  new SwiperModel("/resources/homeImg/banner/banner2.jpg"),
  new SwiperModel("/resources/homeImg/banner/banner1.jpg")
]

export const coreData: Array<CoreDataModel> = [
  new CoreDataModel("/resources/homeImg/core/core1.png", "火爆热款"),
  new CoreDataModel("/resources/homeImg/core/core2.png", "商品分类"),
  new CoreDataModel("/resources/homeImg/core/core3.png", "充值中心"),
  new CoreDataModel("/resources/homeImg/core/core4.png", "活动专区"),
  new CoreDataModel("/resources/homeImg/core/core5.png", "积分商城"),
  new CoreDataModel("/resources/homeImg/core/core6.png", "精选热卖"),
  new CoreDataModel("/resources/homeImg/core/core7.png", "酒店订购"),
  new CoreDataModel("/resources/homeImg/core/core8.png", "好物众测"),
  new CoreDataModel("/resources/homeImg/core/core9.png", "精品手机"),
  new CoreDataModel("/resources/homeImg/core/core10.png", "数码电器"),
  new CoreDataModel("/resources/homeImg/core/core11.png", "数码配件"),
  new CoreDataModel("/resources/homeImg/core/core12.png", "以旧换新"),
  new CoreDataModel("/resources/homeImg/core/core13.png", "限时抢购"),
  new CoreDataModel("/resources/homeImg/core/core14.png", "新品推荐"),
  new CoreDataModel("/resources/homeImg/core/core15.png", "邀请有礼"),
  new CoreDataModel("/resources/homeImg/core/core16.png", "优惠专区"),
  new CoreDataModel("/resources/homeImg/core/core17.png", "正在直播"),
  new CoreDataModel("/resources/homeImg/core/core18.png", "智慧生活"),
  new CoreDataModel("/resources/homeImg/core/core19.png", "会员中心"),
  new CoreDataModel("/resources/homeImg/core/core13.png", "限时抢购")
]

export const boutiqueData: Array<BoutiqueModel> = [
  new BoutiqueModel("XX Phone", "最高优惠200元", "/resources/homeImg/boutique/1.png", "/resources/homeImg/boutique/2.png"),
  new BoutiqueModel("XX Watch", "500元起", "/resources/homeImg/boutique/3.png", "/resources/homeImg/boutique/4.png"),
  new BoutiqueModel("phone & watch", "8这起购", "/resources/homeImg/boutique/5.png", "/resources/homeImg/boutique/6.png"),
  new BoutiqueModel("XX配件", "500元起", "/resources/homeImg/boutique/7.png", "/resources/homeImg/boutique/8.png"),
  new BoutiqueModel("XX笔记本", "500元起", "/resources/homeImg/boutique/9.png", "/resources/homeImg/boutique/10.png"),
  new BoutiqueModel("XX笔记本", "4000元起", "/resources/homeImg/boutique/11.png", "/resources/homeImg/boutique/12.png")
]

export const titleBarData: Array<TitleBarModel> = [
  new TitleBarModel(0, "全部"),
  new TitleBarModel(1, "直播" ),
  new TitleBarModel(2, "便宜好货"),
  new TitleBarModel(3, "淘货")
]

export const productData: Array<ProductDataModel> = [
  new ProductDataModel('/resources/homeImg/imgLoads/product001.png', 'XX设备 优惠直购', '尊享', '￥4122.0', 0),
  new ProductDataModel('/resources/homeImg/imgLoads/product002.png', '送给亲人！快速购买', '纯色', '￥4122.0', 0),
  new ProductDataModel('/resources/homeImg/imgLoads/product003.png', '高质量产品', '净含量:350g', '￥4122.0', 0),
  new ProductDataModel('/resources/homeImg/imgLoads/product004.png', 'XX pro手机', '材质:玻璃/金属/塑料', '￥4122.0', 0),
  new ProductDataModel('/resources/homeImg/imgLoads/product005.png', 'XX手机 限时特惠', '购买免运费 | 跨店', '￥4122.0', 0),
  new ProductDataModel('/resources/homeImg/imgLoads/product006.png', 'XX设备 优惠直购', '尊享', '￥4122.0', 0),
  new ProductDataModel('/resources/homeImg/imgLoads/product007.png', '送给亲人！快速购买', '纯色', '￥4122.0', 0),
  new ProductDataModel('/resources/homeImg/imgLoads/product008.png', '高质量产品', '净含量:350g', '￥4122.0', 0),
  new ProductDataModel('/resources/homeImg/imgLoads/product009.png', 'XX pro手机', '材质:玻璃/金属/塑料', '￥4122.0', 0),
  new ProductDataModel('/resources/homeImg/imgLoads/product010.png', 'XX手机 限时特惠', '购买免运费 | 跨店', '￥4122.0', 0),
  new ProductDataModel('/resources/homeImg/imgLoads/product011.png', 'XX设备 优惠直购', '尊享', '￥4122.0', 0),
  new ProductDataModel('/resources/homeImg/imgLoads/product012.png', '送给亲人！快速购买', '纯色', '￥4122.0', 0),
  new ProductDataModel('/resources/homeImg/imgLoads/product013.png', '高质量产品', '净含量:350g', '￥4122.0', 0),
  new ProductDataModel('/resources/homeImg/imgLoads/product014.png', 'XX pro手机', '材质:玻璃/金属/塑料', '￥4122.0', 0)
]

export const informationData: Array<InformationModel> = [
  new InformationModel("/resources/common/our.png",  "我的助手",  "您的交易存在商品问题？点击快速解决！", "09:50"),
  new InformationModel("/resources/common/person.png", "活动优惠", "您的交易存在商品问题？点击快速解决！", "09:50"),
  new InformationModel("/resources/common/user.png", "中国XX官方旗舰店", "您的交易存在商品问题？点击快速解决！", "09:50"),
  new InformationModel("/resources/common/our.png", "服务通知", "您的交易存在商品问题？点击快速解决！", "09:50"),
  new InformationModel("/resources/common/person.png", "消息互动", "您的交易存在商品问题？点击快速解决！", "09:50"),
  new InformationModel("/resources/common/user.png", "交易物流", "您的交易存在商品问题？点击快速解决！", "09:50"),
  new InformationModel("/resources/common/our.png", "我的助手", "您的交易存在商品问题？点击快速解决！", "09:50"),
  new InformationModel("/resources/common/person.png", "活动优惠", "您的交易存在商品问题？点击快速解决！", "09:50"),
  new InformationModel("/resources/common/user.png", "中国XX官方旗舰店", "您的交易存在商品问题？点击快速解决！", "09:50"),
  new InformationModel("/resources/common/person.png", "服务通知", "您的交易存在商品问题？点击快速解决！", "09:50"),
  new InformationModel("/resources/common/user.png", "互动消息", "您的交易存在商品问题？点击快速解决！", "09:50"),
  new InformationModel("/resources/common/our.png", "交易物流", "您的交易存在商品问题？点击快速解决！", "09:50"),
  new InformationModel("/resources/common/user.png", "中国XX官方旗舰店",  "您的交易存在商品问题？点击快速解决！", "09:50"),
  new InformationModel("/resources/common/person.png", "服务通知", "您的交易存在商品问题？点击快速解决！", "09:50"),
  new InformationModel("/resources/common/user.png", "互动消息", "您的交易存在商品问题？点击快速解决！",  "09:50"),
  new InformationModel("/resources/common/our.png", "交易物流", "您的交易存在商品问题？点击快速解决！", "09:50"),
]

export const shopCartItemData: Array<ShopCartItemDataModel> = [
  new ShopCartItemDataModel('/resources/homeImg/imgLoads/product001.png', 'XX 官方旗舰店手机 5G网速 超大内存 快来购买'),
  new ShopCartItemDataModel('/resources/homeImg/imgLoads/product002.png', 'XX 官方旗舰店手机 5G网速 超大内存 快来购买'),
  new ShopCartItemDataModel('/resources/homeImg/imgLoads/product003.png', 'XX 官方旗舰店手机 5G网速 超大内存 快来购买'),
  new ShopCartItemDataModel('/resources/homeImg/imgLoads/product004.png', 'XX 官方旗舰店手机 5G网速 超大内存 快来购买'),
  new ShopCartItemDataModel('/resources/homeImg/imgLoads/product005.png', 'XX XX 官方旗舰店手机 5G网速 超大内存 快来购买'),
  new ShopCartItemDataModel('/resources/homeImg/imgLoads/product006.png', 'XX 官方旗舰店手机 5G网速 超大内存 快来购买'),
  new ShopCartItemDataModel('/resources/homeImg/imgLoads/product007.png', 'XX 官方旗舰店手机 5G网速 超大内存 快来购买')
]

export const findTitleTextData: Array<FindTitleTextModel> = [
  new FindTitleTextModel("全部"),
  new FindTitleTextModel("节日优惠晒单"),
  new FindTitleTextModel("出品"),
  new FindTitleTextModel("穿搭"),
  new FindTitleTextModel("家居"),
  new FindTitleTextModel("+")
]

export const findImgSrcData: Array<FindImgSrcModel> = [
  new FindImgSrcModel("/resources/homeImg/imgLoads/product001.png"),
  new FindImgSrcModel("/resources/homeImg/imgLoads/product001.png"),
  new FindImgSrcModel("/resources/homeImg/imgLoads/product001.png")
]

export const findImgIntroData: Array<FindImgIntroModel> = [
  new FindImgIntroModel("XXX Phone 30 vip手机设计 5G 全网通 12GB+256GB"),
  new FindImgIntroModel("室外摄像机 精品版 （支持XX XX等设备）"),
  new FindImgIntroModel("潮流XXX系列手机壳")
]

export const findImgNameData: Array<FindImgNameModel> = [
  new FindImgNameModel("普通用户"),
  new FindImgNameModel("我是VIP"),
  new FindImgNameModel("User")
]

export const findIconSrcData: Array<FindIconSrcModel> = [
  new FindIconSrcModel("/resources/icon/game.png"),
  new FindIconSrcModel("/resources/icon/install.png"),
  new FindIconSrcModel("/resources/icon/promotions.png")
]

export const recordData: Array<RecordModel> = [
  new RecordModel("/resources/icon/attention.png", "收藏", "pages/collect/collected"),
  new RecordModel("/resources/icon/attention.png", "订阅店铺",  ""),
  new RecordModel("/resources/icon/attention.png", "足迹", ""),
  new RecordModel("/resources/icon/attention.png", "零钱￥100.0",  "")
]

export const orderData: Array<OrderModel> = [
  new OrderModel(1, "/resources/icon/attention.png", "待付款", "pages/delivery/delivery"),
  new OrderModel(2, "/resources/icon/attention.png", "待发货", "pages/delivery/delivery"),
  new OrderModel(3, "/resources/icon/attention.png", "待收货", "pages/delivery/delivery"),
  new OrderModel(4, "/resources/icon/attention.png", "待评价", "pages/delivery/delivery"),
  new OrderModel(5,  "/resources/icon/attention.png", "退款/售后",  "")
]

export const discountData: Array<DiscountModel> = [
  new DiscountModel("/resources/common/achievement.png", "88VIP", "抢5折券"),
  new DiscountModel("/resources/common/activity.png", "打折优惠共享", "领101元红包"),
  new DiscountModel("/resources/common/gift.png", "88VIP", "查看可用优惠"),
  new DiscountModel("/resources/common/sales.png", "领券中心", "天天领5折券")
]

export const serviceData: Array<ServiceModel> = [
  new ServiceModel("/resources/icon/attention.png", "待付款", ""),
  new ServiceModel("/resources/icon/attention.png", "待发货", ""),
  new ServiceModel("/resources/icon/attention.png", "待收货", ""),
  new ServiceModel("/resources/icon/attention.png", "官方客服", "pages/customerService/customerService")
]