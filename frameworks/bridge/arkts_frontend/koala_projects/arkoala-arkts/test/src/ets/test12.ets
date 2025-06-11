@Observed
class Son12 {
  public title: string;

  constructor(title: string) {
    this.title = title;
  }
}

@Observed
class Father12 {
  public name: string;
  public son: Son12;

  constructor(name: string, son: Son12) {
    this.name = name;
    this.son = son;
  }
}


@Entry
@Component
struct Person12 {
  @State person: Father12 = new Father12('Hello', new Son12('world'));

  build() {
    Column() {
      Flex({ direction: FlexDirection.Column, alignItems: ItemAlign.Center }) {
        Button('change Father12 name')
          .width(312)
          .height(40)
          .margin(12)
          .fontColor('#FFFFFF，90%')
          .onClick(() => {
            this.person.name = "Hi";
          })
        Button('change Son12 title')
          .width(312)
          .height(40)
          .margin(12)
          .fontColor('#FFFFFF，90%')
          .onClick(() => {
            this.person.son.title = "ArkUI";  // Son12 must be decorated with @Observed
          })
        Text(this.person.name)
          .fontSize(16)
          .margin(12)
          .width(312)
          .height(40)
          .backgroundColor('#ededed')
          .borderRadius(20)
          .textAlign(TextAlign.Center)
          .fontColor('#e6000000')
          .onClick(() => {
            this.person.name = 'Bye';
          })
        Text(this.person.son.title)
          .fontSize(16)
          .margin(12)
          .width(312)
          .height(40)
          .backgroundColor('#ededed')
          .borderRadius(20)
          .textAlign(TextAlign.Center)
          .onClick(() => {
            this.person.son.title = "openHarmony";
          })
        Child({ child: this.person.son })
      }

    }

  }
}


@Component
struct Child {
  @Prop child: Son12 = new Son12('');

  build() {
    Column() {
      Text(this.child.title)
        .fontSize(16)
        .margin(12)
        .width(312)
        .height(40)
        .backgroundColor('#ededed')
        .borderRadius(20)
        .textAlign(TextAlign.Center)
        .onClick(() => {
          this.child.title = 'Bye Bye';
        })
    }
  }
}
