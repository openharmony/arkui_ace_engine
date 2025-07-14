class Person3 {
  public value: string;

  constructor(value: string) {
    this.value = value;
  }
}

class Model3 {
  public value: string;
  public name: Person3;
  constructor(value: string, person: Person3) {
    this.value = value;
    this.name = person;
  }
}

@Entry
@Component
struct Page3 {
  // 数组类型
  @State @Watch("onTitleChange") title: Model3[] = [new Model3("11", new Person3("11")), new Model3("22", new Person3("22"))];
  onTitleChange(name: string) {
    console.log(`observe the object and object property change`)
  }

  build() {
    Column() {
      Text(`assign an array: ${JSON.stringify(this.title)}`)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .alignRules({
          center: { anchor: '__container__', align: VerticalAlign.Center },
          middle: { anchor: '__container__', align: HorizontalAlign.Center }
        }).backgroundColor(Color.Green)
        .onClick(()=>{
          this.title = [new Model3("33", new Person3("33"))]; // Array assignment
        })
      Text(`assign item: ${this.title[0].value}`)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .alignRules({
          center: { anchor: '__container__', align: VerticalAlign.Center },
          middle: { anchor: '__container__', align: HorizontalAlign.Center }
        }).backgroundColor(Color.Red)
        .onClick(()=>{
          this.title[0] = new Model3("44", new Person3("44"));  // Array item assignment
        })
      Text(`delete array items: ${JSON.stringify(this.title)}`)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .alignRules({
          center: { anchor: '__container__', align: VerticalAlign.Center },
          middle: { anchor: '__container__', align: HorizontalAlign.Center }
        }).backgroundColor(Color.Gray)
        .onClick(()=>{
          this.title.pop(); //
        })
      Text(`Added array items: ${JSON.stringify(this.title)}`)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .alignRules({
          center: { anchor: '__container__', align: VerticalAlign.Center },
          middle: { anchor: '__container__', align: HorizontalAlign.Center }
        }).backgroundColor(Color.Yellow)
        .onClick(()=>{
          this.title.push(new Model3("12", new Person3("12")));
        })
    }
    .height('100%')
    .width('100%')
  }
}
