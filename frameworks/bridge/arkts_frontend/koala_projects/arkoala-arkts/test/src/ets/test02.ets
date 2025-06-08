class Person2 {
  public value: string;

  constructor(value: string) {
    this.value = value;
  }
}

class Model2 {
  public value: string;
  public name: Person2;
  constructor(value: string, person: Person2) {
    this.value = value;
    this.name = person;
  }
}

@Entry
@Component
struct Page2 {
  // class类型
  @State @Watch("onTitleChange") title: Model2 = new Model2('Hello', new Person2('World'));
  onTitleChange(name: string) {
    console.log(`observe the object and object property change`)
  }

  build() {
    Column() {
      Text(`assign a object: ${JSON.stringify(this.title)}`)
        .id('Page2HelloWorld')
        .fontSize(40)
        .fontWeight(FontWeight.Bold)
        .alignRules({
          center: { anchor: '__container__', align: VerticalAlign.Center },
          middle: { anchor: '__container__', align: HorizontalAlign.Center }
        }).backgroundColor(Color.Green)
        .onClick(()=>{
          this.title = new Model2('Hi', new Person2('ArkUI')); // assign the object to @State variable
        })
      Text(`assign a object property: ${this.title.value}`)
        .id('Page2HelloWorld')
        .fontSize(40)
        .fontWeight(FontWeight.Bold)
        .alignRules({
          center: { anchor: '__container__', align: VerticalAlign.Center },
          middle: { anchor: '__container__', align: HorizontalAlign.Center }
        }).backgroundColor(Color.Red)
        .onClick(()=>{
          this.title.value = 'Hi';  // assign the object property
        })
      Text(`assign a object second layer property: ${this.title.name.value}`)
        .id('Page2HelloWorld')
        .fontSize(40)
        .fontWeight(FontWeight.Bold)
        .alignRules({
          center: { anchor: '__container__', align: VerticalAlign.Center },
          middle: { anchor: '__container__', align: HorizontalAlign.Center }
        }).backgroundColor(Color.Blue)
        .onClick(()=>{
          this.title.name.value = 'ArkUI'; // can not observe properties of second-level objects
        })
    }
    .height('100%')
    .width('100%')
  }
}
