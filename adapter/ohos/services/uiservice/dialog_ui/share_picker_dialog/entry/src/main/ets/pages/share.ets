/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

import extension from '@ohos.app.ability.ExtensionAbility'


@Entry
@Component
struct Share {
  @State private mainTextHeight: number = 19
  @State private mainText: string = undefined
  @State private subText: string = undefined
  @State private sharedIcon: string = undefined
  @State private subTextVisible: Visibility = Visibility.Visible

  private TAG = "[PickerDialogService]"

  // 页面出现
  aboutToAppear() {
    console.info(this.TAG, "aboutToAppear")
    this.getViewStyle(globalThis.want["parameters"])
  }

  // 全局返回按键
  onBackPress() {
    console.info(this.TAG, "onBackPress")
    // 触发全局返回按键销毁窗口和服务
    globalThis.context.terminateSelf()
  }

  // 应用内返回按键
  async onBack() {
    console.info(this.TAG, "onBack")
    // 触发返回按键销毁窗口
    await globalThis.extensionWin.destroy()
    await globalThis.context.terminateSelf()
  }

  async onShare(item) {
    console.info(this.TAG, "onShare")
    // 触发分享, 拉起分享方, 并传递want, 销毁服务
    globalThis.want["parameters"]["ability.want.params.INTENT"]["abilityName"] = item.ability
    globalThis.want["parameters"]["ability.want.params.INTENT"]["bundleName"] = item.bundle
    await globalThis.context.startAbility(globalThis.want["parameters"]["ability.want.params.INTENT"])
    await globalThis.context.terminateSelf()
  }

  // ohos分享卡片预览渲染
  private getViewStyle(data: any) {
    console.info(this.TAG, "getViewStyle")
    let fileNums: number = data["ability.picker.fileNames"] == null ? 0: data["ability.picker.fileNames"].length
    let defaultIcon: string = ""
    if (data["ability.picker.type"] == "text/plain") {
      // 如果类型是纯文本，隐藏子文本，调整主文本高度
      this.subTextVisible = Visibility.Hidden
      this.mainTextHeight = 38
      this.mainText = data["ability.picker.text"]
      defaultIcon = "ic_documents"
    } else if (data["ability.picker.type"] == "text/html") {
      // 如果类型是html
      this.mainText = data["ability.picker.text"]
      this.subText = "网页地址: " + data["ability.picker.uri"]
      defaultIcon = "ic_html"
    } else if (fileNums == 0) {
      // 如果文件数量为0
      defaultIcon = "ic_unknown"
      if (data["ability.picker.type"] == null) {
        // 类型也为空
        if (data["ability.picker.uri"] != null) {
          // 但是uri存在，也就是导引了一个网络文件，但未知类型
          defaultIcon = "ic_html"
          this.subText = "网页地址: " + data["ability.picker.uri"]
        } else if (data["ability.picker.text"] != null) {
          // 如果text存在
          this.subTextVisible = Visibility.Hidden
          this.mainTextHeight = 38
          defaultIcon = "ic_documents"
        }
      }
      if (defaultIcon == "ic_unknown") {
        this.mainText = "未知文件名称"
        this.subText =  "文件大小未知"
      }
    } else if (fileNums == 1) {
      // 如果文件数量为1
      this.mainText = data["ability.picker.fileNames"][0]
      this.subText = "文件大小" +  Math.round(data["ability.picker.fileSizes"][0] / 1024) + "KB"
      switch (data["ability.picker.type"]) {
        case "application/image": defaultIcon = "ic_image"; break
        case "application/apk": defaultIcon = "ic_apk"; break
        case "application/pdf": defaultIcon = "ic_pdf"; break
        case "application/doc": defaultIcon = "ic_doc"; break
        case "application/ppt": defaultIcon = "ic_pptx"; break
        case "application/xls": defaultIcon = "ic_xls"; break
        case "application/ics": defaultIcon = "ic_calendar"; break
        case "application/vcf": defaultIcon = "ic_contacts"; break
        case "video/mp4": defaultIcon = "ic_video"; break
        case "audio/mp3": defaultIcon = "ic_mp3"; break
        default: defaultIcon = "ic_unknown"; break
      }
    } else {
      // 如果文件数量很多
      defaultIcon = "ic_file_multiple"
      if (data["ability.picker.type"].indexOf("*") != -1) {
        // 如果是同类文件
        this.mainText = fileNums + "个不同类文件"
      } else {
        this.mainText = fileNums + "个同类文件"
      }
      let totalSize = 0
      for (let i = 0; i < fileNums; i++) {
        if (data["ability.picker.fileSizes"][i] != null) {
          totalSize += data["ability.picker.fileSizes"][i]
        }
      }
      this.subText = "总大小" + Math.round(totalSize/1024) + "KB"
    }
    this.sharedIcon = defaultIcon + ".png"
  }

  build() {
    // share
    Column() {

      // 下拉标签
      Column() {
        Image($rawfile("handle_down.png")).width(64).height(24).onClick(() => {
          this.onBack()
        })
      }
      .margin({top: globalThis.style["shareBackTop"]})

      // ohos分享卡片预览
      Column() {
        Row() {
          Image($rawfile(this.sharedIcon))
            .width(48)
            .height(48)
            .backgroundColor("#FFFFFF")
            .border({radius: 0})
          Column() {
            Text(this.mainText)
              .width(globalThis.style["shareCardTextWidth"])
              .height(this.mainTextHeight)
              .maxLines(2)
              .fontSize(14)
              .fontFamily("sans-serif")
              .textOverflow({overflow: TextOverflow.Ellipsis})
            Text(this.subText)
              .width(globalThis.style["shareCardTextWidth"])
              .maxLines(1)
              .fontSize(10)
              .fontFamily("sans-serif")
              .height(14)
              .textOverflow({overflow: TextOverflow.Ellipsis})
              .visibility(this.subTextVisible)
              .margin({top: globalThis.style["shareCardSubTop"]})
          }
          .margin({
            left: globalThis.style["shareCardTextLeft"],
            top: globalThis.style["shareCardTextTop"]
          })
        }
        .margin(globalThis.style["shareContentMargin"])
      }
      .backgroundColor("#FFFFFF")
      .width(globalThis.style["shareCardWidth"])
      .height(globalThis.style["shareCardHeight"])
      .borderRadius(globalThis.style["shareCardRadius"])
      .margin({
        top: 8,
        right: 12,
        bottom: 8,
        left: 12
      })

      // 应用列表组件
      Swiper() {
        ForEach(globalThis.shareHapList, (items) => {
          Flex({direction: FlexDirection.Row, wrap: FlexWrap.Wrap}) {
            ForEach(items, (item) => {
              Column() {
                Image(item.icon)
                  .height(48)
                  .width(48)
                  .margin(8)
                  .borderRadius(8)
                Text(item.name)
                  .width(64)
                  .height(16)
                  .fontSize(12)
                  .textAlign(TextAlign.Center)
              }
              .margin({left: 15})
              .height(81)
              .onClick(() => {
                this.onShare(item)
              })
            })
          }
          .margin({
            top: globalThis.style["swiperSelectMarginTop"],
            left: 15,
            right: 15
          })
        })
      }
      .loop(false)
      .height(globalThis.style["swiperHeight"])
      .indicatorStyle({
        size: 4, top: "90%"
      })

    }
    .backgroundColor("#FAFAFA")
    .width("100%")
    .height("100%")
    .border({
      radius: {
        topLeft: 24,
        topRight: 24,
        bottomRight: 0,
        bottomLeft: 0
      }})
  }
}