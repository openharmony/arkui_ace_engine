import { common2D, drawing } from '@kit.ArkGraphics2D';
import { ColorMetrics } from '@ohos.arkui.node';
import hilog from '@ohos.hilog';

export class Const {
  public static readonly ANGLE_TO_RADIAN = Math.PI / 180;
  public static readonly RADIAN_TO_ANGLE = 180 / Math.PI;
  public static readonly PI_RADIAN = 180;
  public static readonly TWO_PI_ANGLE = 360;
  public static readonly TWO_PI_RADIAN = 2 * Math.PI;
  public static readonly APPROXIMATE_NUMBER = Math.pow(10, -7);
  public static readonly ANGLE_OVER_MIN = 10;
  public static readonly LENGTH_OVER_MIN = 0.15;
  public static readonly TOTAL_LENGTH = 233;
  public static readonly VALUE_DEFAULT = 0;
  public static readonly MIN_DEFAULT = 0;
  public static readonly MAX_DEFAULT = 100;
  public static readonly X_DEFAULT = 116.5;
  public static readonly Y_DEFAULT = 116.5;
  public static readonly RADIUS_DEFAULT = 116.5;
  public static readonly PADDING_DEFAULT = 5.5;
  public static readonly START_ANGLE_DEFAULT = 15;
  public static readonly END_ANGLE_DEFAULT = 45;
  public static readonly ACTIVE_START_ANGLE_DEFAULT = -60;
  public static readonly ACTIVE_END_ANGLE_DEFAULT = 60;
  public static readonly REVERSE_DEFAULT = true;
  public static readonly TRACK_THICKNESS_DEFAULT = 5;
  public static readonly ACTIVE_TRACK_THICKNESS_DEFAULT = 24;
  public static readonly TRACK_BLUR_DEFAULT = 20;
  public static readonly TRACK_COLOR_DEFAULT = '#33FFFFFF';
  public static readonly SELECTED_COLOR_DEFAULT = '#FF5EA1FF';
  public static readonly BLUR_COLOR_DEFAULT = $r('sys.color.ohos_id_color_subtab_bg');
  public static readonly VIBRATOR_TYPE_TWO = 'watchhaptic.crown.strength2';
  public static readonly VIBRATOR_TYPE_SIX = 'watchhaptic.crown.strength6';
  public static readonly CROWN_EVENT_FLAG = 30;
  public static readonly CROWN_CONTROL_RATIO = 2.10;
  public static readonly CROWN_SENSITIVITY_LOW = 0.5;
  public static readonly CROWN_SENSITIVITY_MEDIUM = 1;
  public static readonly CROWN_SENSITIVITY_HIGH = 2;
  public static readonly INVALID_TIMEOUT_ID = -1;
  public static readonly RESTORE_TIMEOUT = 3000;
}

export enum MinOrMaxStatus {
  MinStatus = 'min',
  MaxStatus = 'max',
  NormalStatus = 'normal',
}

export enum ClipPathArc {
  Arc1 = '1',
  Arc2 = '2',
  Arc3 = '3',
  Arc4 = '4'
}

export interface ArcSliderValueOptionsConstructorOptions {
  value?: number;
  min?: number;
  max?: number;
}

@ObservedV2
export class ArcSliderValueOptions {
  @Trace public value: number = Const.VALUE_DEFAULT;
  @Trace public min: number = Const.MIN_DEFAULT;
  @Trace public max: number = Const.MAX_DEFAULT;

  constructor(options?: ArcSliderValueOptionsConstructorOptions) {
    if (options) {
      this.value = options.value ?? Const.VALUE_DEFAULT;
      this.min = options.min ?? Const.MIN_DEFAULT;
      this.max = options.max ?? Const.MAX_DEFAULT;
    }
  }
}

export interface ArcSliderLayoutOptionsConstructorOptions {
  x?: number;
  y?: number;
  radius?: number;
  padding?: number;
  startAngle?: number;
  endAngle?: number;
  activeStartAngle?: number;
  activeEndAngle?: number;
  reverse?: boolean;
}

@ObservedV2
export class ArcSliderLayoutOptions {
  @Trace public x: number = Const.X_DEFAULT;
  @Trace public y: number = Const.Y_DEFAULT;
  @Trace public radius: number = Const.RADIUS_DEFAULT;
  @Trace public padding: number = Const.PADDING_DEFAULT;
  @Trace public startAngle: number = Const.START_ANGLE_DEFAULT;
  @Trace public endAngle: number = Const.END_ANGLE_DEFAULT;
  @Trace public activeStartAngle: number = Const.ACTIVE_START_ANGLE_DEFAULT;
  @Trace public activeEndAngle: number = Const.ACTIVE_END_ANGLE_DEFAULT;
  @Trace public reverse: boolean = Const.REVERSE_DEFAULT;

  constructor(options?: ArcSliderLayoutOptionsConstructorOptions) {
    if (options) {
      this.x = options.x ?? Const.X_DEFAULT;
      this.y = options.y ?? Const.Y_DEFAULT;
      this.radius = options.radius ?? Const.RADIUS_DEFAULT;
      this.padding = options.padding ?? Const.PADDING_DEFAULT;
      this.startAngle = options.startAngle ?? Const.START_ANGLE_DEFAULT;
      this.endAngle = options.endAngle ?? Const.END_ANGLE_DEFAULT;
      this.activeStartAngle = options.activeStartAngle ?? Const.ACTIVE_START_ANGLE_DEFAULT;
      this.activeEndAngle = options.activeEndAngle ?? Const.ACTIVE_END_ANGLE_DEFAULT;
      this.reverse = options.reverse ?? Const.REVERSE_DEFAULT;
    }
  }
}

export interface ArcSliderStyleOptionsConstructorOptions {
  trackThickness?: number;
  activeTrackThickness?: number;
  trackColor?: string;
  selectedColor?: string;
  trackBlur?: number;
}

@ObservedV2
export class ArcSliderStyleOptions {
  @Trace public trackThickness: number = Const.TRACK_THICKNESS_DEFAULT;
  @Trace public activeTrackThickness: number = Const.ACTIVE_TRACK_THICKNESS_DEFAULT;
  @Trace public trackColor: string = Const.TRACK_COLOR_DEFAULT;
  @Trace public selectedColor: string = Const.SELECTED_COLOR_DEFAULT;
  @Trace public trackBlur: number = Const.TRACK_BLUR_DEFAULT;

  constructor(options?: ArcSliderStyleOptionsConstructorOptions) {
    if (options) {
      this.trackThickness = options.trackThickness ?? Const.TRACK_THICKNESS_DEFAULT;
      this.activeTrackThickness = options.activeTrackThickness ?? Const.ACTIVE_TRACK_THICKNESS_DEFAULT;
      this.trackColor = options.trackColor ?? Const.TRACK_COLOR_DEFAULT;
      this.selectedColor = options.selectedColor ?? Const.SELECTED_COLOR_DEFAULT;
      this.trackBlur = options.trackBlur ?? Const.TRACK_BLUR_DEFAULT;
    }
  }
}

export interface ArcSliderOptionsConstructorOptions {
  valueOptions?: ArcSliderValueOptions;
  layoutOptions?: ArcSliderLayoutOptions;
  styleOptions?: ArcSliderStyleOptions;
  digitalCrownSensitivity?: CrownSensitivity;
  onTouch?: Callback<TouchEvent>;
  onChange?: Callback<number>;
}

@ObservedV2
export class ArcSliderOptions {
  @Trace public valueOptions: ArcSliderValueOptions = new ArcSliderValueOptions();
  @Trace public layoutOptions: ArcSliderLayoutOptions = new ArcSliderLayoutOptions();
  @Trace public styleOptions: ArcSliderStyleOptions = new ArcSliderStyleOptions();
  @Trace public digitalCrownSensitivity: CrownSensitivity = CrownSensitivity.MEDIUM;
  @Trace public onTouch: Callback<TouchEvent> = (event: TouchEvent) => {
  };
  @Trace public onChange: Callback<number> = (value: number) => {
  };

  constructor(options?: ArcSliderOptionsConstructorOptions) {
    if (options) {
      this.valueOptions = options.valueOptions ?? new ArcSliderValueOptions();
      this.layoutOptions = options.layoutOptions ?? new ArcSliderLayoutOptions();
      this.styleOptions = options.styleOptions ?? new ArcSliderStyleOptions();
      this.digitalCrownSensitivity = options.digitalCrownSensitivity ?? CrownSensitivity.MEDIUM;
      this.onTouch = options.onTouch ?? ((event: TouchEvent) => {
      });
      this.onChange = options.onChange ?? ((value: number) => {
      });
    }
  }
}

export class DrawParameters {
  public lineWidth: number = 0;
  public radius: number = 0;
  public trackEndAngle: number = 0;
  public trackStartAngle: number = 0;
  public selectedStartAngle: number = 0;
  public selectedEndAngle: number = 0;
  public trackColor: ColorMetrics = ColorMetrics.resourceColor(Const.TRACK_COLOR_DEFAULT);
  public selectedColor: ColorMetrics = ColorMetrics.resourceColor(Const.SELECTED_COLOR_DEFAULT);
  public reverse: boolean = Const.REVERSE_DEFAULT;
  public x: number = Const.X_DEFAULT;
  public y: number = Const.Y_DEFAULT;
  public blur: number = Const.TRACK_BLUR_DEFAULT;
  public uiContext: UIContext | undefined = undefined;

  constructor() {
  }
}

export function nearEqual(num1: number, num2: number): boolean {
  return Math.abs(num1 - num2) < Const.APPROXIMATE_NUMBER;
}

export class MyFullDrawModifier extends DrawModifier {
  public parameters: DrawParameters = new DrawParameters();

  constructor(parameters: DrawParameters) {
    super();
    this.parameters = parameters;
  }

  parseColorString(color: ColorMetrics): common2D.Color {
    return { alpha: color.alpha, red: color.red, green: color.green, blue: color.blue };
  }

  drawTrack(context: DrawContext) {
    if (this.parameters.uiContext === undefined) {
      hilog.error(0x3900, 'ArcSlider', `uiContext is undefined`);
      return;
    }
    const canvas = context.canvas;
    const pen = new drawing.Pen();
    pen.setAntiAlias(true);
    pen.setColor(this.parseColorString(this.parameters.trackColor));
    pen.setStrokeWidth(this.parameters.uiContext.vp2px(this.parameters.lineWidth));
    pen.setCapStyle(drawing.CapStyle.ROUND_CAP);
    canvas.attachPen(pen);
    let path = new drawing.Path();
    let leftTopX = this.parameters.uiContext.vp2px(this.parameters.x - this.parameters.radius);
    let leftTopY = this.parameters.uiContext.vp2px(this.parameters.y - this.parameters.radius);
    let rightBottomX = this.parameters.uiContext.vp2px(this.parameters.x + this.parameters.radius);
    let rightBottomY = this.parameters.uiContext.vp2px(this.parameters.y + this.parameters.radius);
    let startAngle: number;
    let sweepAngle: number;
    let trackEndAngle = this.parameters.trackEndAngle * Const.RADIAN_TO_ANGLE;
    let delta = (this.parameters.trackStartAngle - this.parameters.trackEndAngle) * Const.RADIAN_TO_ANGLE;
    if (this.parameters.reverse && this.parameters.selectedStartAngle < this.parameters.trackEndAngle) {
      startAngle = trackEndAngle;
      sweepAngle = Const.TWO_PI_ANGLE + delta;
    } else if (!this.parameters.reverse && this.parameters.selectedStartAngle > this.parameters.trackEndAngle) {
      startAngle = this.parameters.trackStartAngle * Const.RADIAN_TO_ANGLE;
      sweepAngle = Const.TWO_PI_ANGLE - delta;
    } else {
      startAngle = trackEndAngle;
      sweepAngle = delta;
    }
    path.arcTo(leftTopX, leftTopY, rightBottomX, rightBottomY, startAngle, sweepAngle);
    canvas.drawPath(path);
    canvas.detachPen();
  }

  drawSelection(context: DrawContext) {
    if (this.parameters.uiContext === undefined) {
      hilog.error(0x3900, 'ArcSlider', `uiContext is undefined`);
      return;
    }
    if (nearEqual(this.parameters.selectedStartAngle, this.parameters.selectedEndAngle)) {
      return;
    }
    const canvas = context.canvas;
    const pen = new drawing.Pen();
    pen.setAntiAlias(true);
    pen.setColor(this.parseColorString(this.parameters.selectedColor));
    pen.setStrokeWidth(this.parameters.uiContext.vp2px(this.parameters.lineWidth));
    pen.setCapStyle(drawing.CapStyle.ROUND_CAP);
    canvas.attachPen(pen);
    let path = new drawing.Path();
    let leftTopX = this.parameters.uiContext.vp2px(this.parameters.x - this.parameters.radius);
    let leftTopY = this.parameters.uiContext.vp2px(this.parameters.y - this.parameters.radius);
    let rightBottomX = this.parameters.uiContext.vp2px(this.parameters.x + this.parameters.radius);
    let rightBottomY = this.parameters.uiContext.vp2px(this.parameters.y + this.parameters.radius);
    let startAngle: number;
    let sweepAngle: number;
    let selectedEndAngle = this.parameters.selectedEndAngle * Const.RADIAN_TO_ANGLE;
    let selectedStartAngle = this.parameters.selectedStartAngle * Const.RADIAN_TO_ANGLE;
    let delta = (this.parameters.selectedStartAngle - this.parameters.selectedEndAngle) * Const.RADIAN_TO_ANGLE;
    if (this.parameters.reverse && this.parameters.selectedStartAngle < this.parameters.trackEndAngle &&
      this.parameters.selectedEndAngle > this.parameters.selectedStartAngle) {
      startAngle = selectedEndAngle - Const.TWO_PI_ANGLE;
      sweepAngle = Const.TWO_PI_ANGLE + delta;
    } else if (!this.parameters.reverse && this.parameters.selectedStartAngle > this.parameters.trackEndAngle &&
      this.parameters.selectedEndAngle < this.parameters.selectedStartAngle) {
      startAngle = selectedStartAngle - Const.TWO_PI_ANGLE;
      sweepAngle = Const.TWO_PI_ANGLE - delta;
    } else {
      startAngle = selectedEndAngle;
      sweepAngle = delta;
    }
    path.arcTo(leftTopX, leftTopY, rightBottomX, rightBottomY, startAngle, sweepAngle);
    canvas.drawPath(path);
    canvas.detachPen();
  }

  drawContent(context: DrawContext): void {
    this.drawTrack(context);
  }

  drawFront(context: DrawContext): void {
    this.drawSelection(context);
  }
}
