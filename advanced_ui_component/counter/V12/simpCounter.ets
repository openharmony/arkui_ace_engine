import { LengthMetrics } from '@ohos.arkui.node';

/**
 * 简化版计数器选项
 */
export interface SimpleCounterOptions {
  value?: number;       // 初始值
  min?: number;         // 最小值
  max?: number;         // 最大值
  step?: number;        // 步长
  onChange?: (value: number) => void;  // 值变化回调
}

/**
 * 简化版计数器组件
 */
@Component
export struct SimpleCounter {
  // 计数器配置选项
  @Prop options: SimpleCounterOptions;

  // 组件内部状态
  @State value: number = 0;
  @State min: number = 0;
  @State max: number = 999;
  @State step: number = 1;
  @State subBtnEnabled: boolean = true;
  @State addBtnEnabled: boolean = true;

  // 事件回调
  private onChange?: (value: number) => void;

  // 用于背景颜色
  private static readonly BUTTON_BG_COLOR = '#F1F3F5';
  private static readonly BUTTON_ICON_COLOR = '#007DFF';
  private static readonly TEXT_COLOR = '#182431';
  private static readonly DISABLED_OPACITY = 0.4;

  aboutToAppear(): void {
    // 初始化组件数据
    if (this.options) {
      this.value = this.options.value !== undefined ? this.options.value : 0;
      this.min = this.options.min !== undefined ? this.options.min : 0;
      this.max = this.options.max !== undefined ? this.options.max : 999;
      this.step = this.options.step !== undefined && this.options.step > 0 ? this.options.step : 1;
      this.onChange = this.options.onChange;

      this.updateButtonStatus();
    }
  }

  // 减少数值
  private subValue(): void {
    if (this.value > this.min) {
      this.value -= this.step;
      // 防止超出下限
      if (this.value < this.min) {
        this.value = this.min;
      }

      this.onChange?.(this.value);
      this.updateButtonStatus();
    }
  }

  // 增加数值
  private addValue(): void {
    if (this.value < this.max) {
      this.value += this.step;
      // 防止超出上限
      if (this.value > this.max) {
        this.value = this.max;
      }

      this.onChange?.(this.value);
      this.updateButtonStatus();
    }
  }

  // 更新按钮状态
  private updateButtonStatus(): void {
    this.subBtnEnabled = this.value > this.min;
    this.addBtnEnabled = this.value < this.max;
  }

  build() {
    Row() {
      // 减号按钮
      Button({ type: ButtonType.Circle }) {
        Image($r('sys.media.ohos_ic_public_minus'))
          .width(16)
          .height(16)
          .fillColor(SimpleCounter.BUTTON_ICON_COLOR)
      }
      .width(32)
      .height(32)
      .backgroundColor(SimpleCounter.BUTTON_BG_COLOR)
      .enabled(this.subBtnEnabled)
      .opacity(this.subBtnEnabled ? 1 : SimpleCounter.DISABLED_OPACITY)
      .onClick(() => this.subValue())

      // 显示值的文本
      Text(this.value.toString())
        .fontSize(16)
        .fontColor(SimpleCounter.TEXT_COLOR)
        // .margin({ horizontal: 12 })
        .width(40)
        .textAlign(TextAlign.Center)

      // 加号按钮
      Button({ type: ButtonType.Circle }) {
        Image($r('sys.media.ohos_ic_public_add'))
          .width(16)
          .height(16)
          .fillColor(SimpleCounter.BUTTON_ICON_COLOR)
      }
      .width(32)
      .height(32)
      .backgroundColor(SimpleCounter.BUTTON_BG_COLOR)
      .enabled(this.addBtnEnabled)
      .opacity(this.addBtnEnabled ? 1 : SimpleCounter.DISABLED_OPACITY)
      .onClick(() => this.addValue())
    }
    .height(40)
    .border({ width: 1, color: '#E3E5E7', radius: 8 })
    // .padding({ horizontal: 4 })
  }
}