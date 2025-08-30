/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

@CustomDialog
export struct CustomSelectDialog {
  @Prop title: ResourceStr;
  @Prop primaryButton: SelectButtonOptions;
  @Prop secondaryButton: SelectButtonOptions;
  @BuilderParam contentBuilder: () => void;
  controller?: CustomDialogController

  build() {
    Column() {
      Text(this.title)
        .fontSize(20)
        .fontFamily('HarmonyHeiTi')
        .fontWeight(FontWeight.Medium)
        .fontColor($r('sys.color.font_primary'))
        .height(27)
        .margin({ top: 24, bottom: 24 })
      this.contentBuilder()
      Row({ space: 24 }) {
        Button() {
          Text(this.primaryButton.value)
            .attributeModifier(new ButtonTextModifier())
        }
        .attributeModifier(new ButtonModifier(this.primaryButton.background, this.primaryButton.isShowBorder))
        .onClick(() => {
          this.primaryButton.action();
        })

        Button() {
          Text(this.secondaryButton.value)
            .attributeModifier(new ButtonTextModifier())
        }
        .attributeModifier(new ButtonModifier(this.secondaryButton.background, this.secondaryButton.isShowBorder))
        .onClick(() => {
          this.secondaryButton.action();
        })
      }
      .height(40)
      .margin({ top: 24, bottom: 24 })
    }
    .borderRadius(16)
    .height('auto')
    .width(346)
    .alignItems(HorizontalAlign.Center)
  }
}

export class ButtonTextModifier implements AttributeModifier<TextAttribute> {
  applyNormalAttribute(instance: TextAttribute): void {
    instance.fontColor($r('sys.color.font_primary'))
      .fontSize(18)
      .fontWeight(FontWeight.Medium)
      .focusable(true)
      .fontFamily('HarmonyHeiTi')
      .maxLines(1)
      .textOverflow({ overflow: TextOverflow.Ellipsis })
      .textAlign(TextAlign.Center)
  }
}

export interface SelectButtonOptions {
  value: ResourceStr;
  action: () => void;
  background?: ResourceColor;
  isShowBorder?: boolean;
}

class ButtonModifier implements AttributeModifier<ButtonAttribute> {
  private buttonColor: ResourceColor = $r('sys.color.ohos_id_color_button_normal');
  private isShowBorder: boolean = false;

  constructor(color: ResourceColor, isShowBorder: boolean) {
    this.buttonColor = color;
    this.isShowBorder = isShowBorder;
  }

  applyNormalAttribute(instance: ButtonAttribute): void {
    instance.backgroundColor(this.buttonColor)
      .borderWidth(this.isShowBorder ? 0.5 : 0)
      .borderColor('#26FFFFFF')
      .constraintSize({
        minWidth: 137,
        minHeight: 40
      });
  }
}
