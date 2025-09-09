@Component
struct TotalView {
  @Prop @Watch('onCountUpdated') count: number = 0;
  @State total: number = 0;
  // @Watch 回调
  onCountUpdated(propName: string): void {
    this.total += this.count;
  }

  build() {
    Text(`Total: ${this.total}`)
  }
}

@Entry
@Component
struct CountModifier {
  @State @Watch('onCountChange') count: number = 0;

  onCountChange(name: string) {
    console.log(`change count = ${this.count}`)
  }
  build() {
    Column() {
      Button('add to basket')
        .onClick(() => {
          for (let i = 0; i < 1000; i++) {
            this.count++
          }

        })
      TotalView({ count: this.count })
    }
  }
}
