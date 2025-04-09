@Observed
export class ImgEntity {
  public color: ResourceColor;
  public ratio: number = 0.0;
  public isDivider: boolean = false;

  constructor(color: ResourceColor, ratio?: number, isDivider?: boolean) {
    this.color = color;
    if (ratio) {
      this.ratio = ratio;
    }
    if (isDivider) {
      this.isDivider = isDivider;
    }
  }
}