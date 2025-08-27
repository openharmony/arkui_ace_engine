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

interface formData {
  username: string,
  password: string,
  confirmPassword: string,
  gender: number,
  age: number,
  hobbies: Array<boolean>,
  province: string,
  city: string,
  address: string,
  agree: boolean,
  deliveryTime: string,
  paymentMethod: string,
  couponCode: string
}

interface validState {
  valid: boolean,
  message: string
}

interface validationInfo {
  username: validState,
  password: validState,
  confirmPassword: validState,
  address: validState,
  agree: validState
}

interface areaDataInfo {
  province: string,
  cities: Array<string>
}

@Builder
export function FormIndexBuilder(name: string, param: Object) {
  formBuild()
}

@Component
export struct formBuild {
  pathStack: NavPathStack = new NavPathStack()
  // 表单数据
  @State formData: formData = {
    username: '',
    password: '',
    confirmPassword: '',
    gender: 0,
    age: 18,
    hobbies: [false, false, false, false],
    province: '',
    city: '',
    address: '',
    agree: false,
    deliveryTime: '09:00-12:00',
    paymentMethod: 'alipay',
    couponCode: ''
  }
  // 表单验证状态
  @State validation: validationInfo = {
    username: { valid: true, message: '' },
    password: { valid: true, message: '' },
    confirmPassword: { valid: true, message: '' },
    address: { valid: true, message: '' },
    agree: { valid: true, message: '' }
  }
  // 省份城市数据
  private areaData: Array<areaDataInfo> = [
    { province: '北京', cities: ['北京市'] },
    { province: '上海', cities: ['上海市'] },
    { province: '天津', cities: ['天津市'] },
    { province: '重庆', cities: ['重庆市'] },
    { province: '河北', cities: ['石家庄市', '唐山市', '秦皇岛市', '邯郸市', '保定市'] },
    { province: '山西', cities: ['太原市', '大同市', '阳泉市', '长治市', '晋城市'] },
    { province: '辽宁', cities: ['沈阳市', '大连市', '鞍山市', '抚顺市', '本溪市'] },
    { province: '吉林', cities: ['长春市', '吉林市', '四平市', '辽源市', '通化市'] },
    { province: '黑龙江', cities: ['哈尔滨市', '齐齐哈尔市', '鸡西市', '鹤岗市', '大庆市'] },
    { province: '江苏', cities: ['南京市', '无锡市', '徐州市', '常州市', '苏州市'] },
    { province: '浙江', cities: ['杭州市', '宁波市', '温州市', '嘉兴市', '湖州市'] },
    { province: '安徽', cities: ['合肥市', '芜湖市', '蚌埠市', '淮南市', '马鞍山市'] },
    { province: '福建', cities: ['福州市', '厦门市', '莆田市', '三明市', '泉州市'] },
    { province: '江西', cities: ['南昌市', '景德镇市', '萍乡市', '九江市', '新余市'] },
    { province: '山东', cities: ['济南市', '青岛市', '淄博市', '枣庄市', '东营市'] },
    { province: '河南', cities: ['郑州市', '开封市', '洛阳市', '平顶山市', '安阳市'] },
    { province: '湖北', cities: ['武汉市', '黄石市', '十堰市', '宜昌市', '襄阳市'] },
    { province: '湖南', cities: ['长沙市', '株洲市', '湘潭市', '衡阳市', '邵阳市'] },
    { province: '广东', cities: ['广州市', '深圳市', '珠海市', '汕头市', '佛山市'] },
    { province: '海南', cities: ['海口市', '三亚市', '三沙市', '儋州市'] },
    { province: '四川', cities: ['成都市', '自贡市', '攀枝花市', '泸州市', '德阳市'] },
    { province: '贵州', cities: ['贵阳市', '六盘水市', '遵义市', '安顺市', '毕节市'] },
    { province: '云南', cities: ['昆明市', '曲靖市', '玉溪市', '保山市', '昭通市'] },
    { province: '陕西', cities: ['西安市', '铜川市', '宝鸡市', '咸阳市', '渭南市'] },
    { province: '甘肃', cities: ['兰州市', '嘉峪关市', '金昌市', '白银市', '天水市'] },
    { province: '青海', cities: ['西宁市', '海东市'] },
    { province: '台湾', cities: ['台北市', '新北市', '桃园市', '台中市', '台南市'] },
    { province: '内蒙古', cities: ['呼和浩特市', '包头市', '乌海市', '赤峰市', '通辽市'] },
    { province: '广西', cities: ['南宁市', '柳州市', '桂林市', '梧州市', '北海市'] },
    { province: '西藏', cities: ['拉萨市', '日喀则市', '昌都市', '林芝市', '山南市'] },
    { province: '宁夏', cities: ['银川市', '石嘴山市', '吴忠市', '固原市', '中卫市'] },
    { province: '新疆', cities: ['乌鲁木齐市', '克拉玛依市', '吐鲁番市', '哈密市'] },
    { province: '香港', cities: ['香港'] },
    { province: '澳门', cities: ['澳门'] }
  ]
  // 城市选项
  @State cityOptions: Array<SelectOption> = []
  @State cityIndex: number = -1;
  @State cityName: string = '';
  // 提交状态
  @State isSubmitting: boolean = false
  @State submitSuccess: boolean = false

  // 验证用户名
  private validateUsername() {
    if (this.formData.username.length < 4) {
      this.validation.username = { valid: false, message: '用户名至少4个字符' }
    } else if (this.formData.username.length > 16) {
      this.validation.username = { valid: false, message: '用户名不能超过16个字符' }
    } else {
      this.validation.username = { valid: true, message: '' }
    }
  }

  // 验证密码
  private validatePassword() {
    const passwordRegex = /^(?=.*[a-z])(?=.*[A-Z])(?=.*\d)[^]{8,16}$/
    if (!passwordRegex.test(this.formData.password)) {
      this.validation.password = {
        valid: false,
        message: '密码需8-16位，包含大小写字母和数字'
      }
    } else {
      this.validation.password = { valid: true, message: '' }
    }
  }

  // 验证确认密码
  private validateConfirmPassword() {
    if (this.formData.password !== this.formData.confirmPassword) {
      this.validation.confirmPassword = { valid: false, message: '两次密码不一致' }
    } else {
      this.validation.confirmPassword = { valid: true, message: '' }
    }
  }

  // 验证地址
  private validateAddress() {
    if (this.formData.address.length < 10) {
      this.validation.address = { valid: false, message: '请填写详细地址，至少10个字符' }
    } else {
      this.validation.address = { valid: true, message: '' }
    }
  }

  // 验证协议
  private validateAgreement() {
    if (!this.formData.agree) {
      this.validation.agree = { valid: false, message: '请阅读并同意用户协议' }
    } else {
      this.validation.agree = { valid: true, message: '' }
    }
  }

  // 验证整个表单
  private validateForm(): boolean {
    this.validateUsername()
    this.validatePassword()
    this.validateConfirmPassword()
    this.validateAddress()
    this.validateAgreement()

    return this.validation.username.valid &&
    this.validation.password.valid &&
    this.validation.confirmPassword.valid &&
    this.validation.address.valid &&
    this.validation.agree.valid
  }

  // 处理省份选择变化
  private handleProvinceChange(province: string) {
    this.formData.province = province
    this.formData.city = ''
    const selectedProvince = this.areaData.find(item => item.province === province)
    this.cityOptions = selectedProvince ? selectedProvince.cities.map(item => {
      return { value: item } as SelectOption
    }) : [{ value: '' }]
  }

  // 提交表单
  private submitForm() {
    if (!this.validateForm()) {
      return
    }

    this.isSubmitting = true

    // 模拟API调用
    setTimeout(() => {
      this.isSubmitting = false
      this.submitSuccess = true
      // 实际应用中这里可以调用API提交数据
      console.log('表单提交成功:', JSON.stringify(this.formData))
    }, 1500)
  }

  // 重置表单
  private resetForm() {
    this.formData = {
      username: '',
      password: '',
      confirmPassword: '',
      gender: 0,
      age: 18,
      hobbies: [false, false, false, false],
      province: '',
      city: '',
      address: '',
      agree: false,
      deliveryTime: '09:00-12:00',
      paymentMethod: 'alipay',
      couponCode: ''
    }
    this.cityOptions = []
    this.submitSuccess = false
  }

  private getProvincedata(): SelectOption[] {
    let provinceDate = this.areaData.map(item => {
      return { value: item.province } as SelectOption
    })
    return provinceDate;
  }

  build() {
    NavDestination() {
      Column() {
        if (this.submitSuccess) {
          // 提交成功视图
          Column() {
            Image($r('sys.media.ohos_ic_public_ok'))
              .width(100)
              .height(100)
              .margin({ bottom: 20 })

            Text('提交成功！')
              .fontSize(20)
              .fontWeight(FontWeight.Bold)
              .margin({ bottom: 10 })

            Text('您的表单已成功提交，我们将尽快处理。')
              .fontSize(16)
              .margin({ bottom: 30 })

            Button('返回表单', { type: ButtonType.Normal })
              .width('80%')
              .onClick(() => {
                this.submitSuccess = false
                this.resetForm()
              })
          }
          .width('100%')
          .justifyContent(FlexAlign.Center)
          .alignItems(HorizontalAlign.Center)
        } else {
          // 表单视图
          Scroll() {
            Column() {
              // 标题
              Text('用户注册')
                .fontSize(24)
                .fontWeight(FontWeight.Bold)
                .margin({ top: 20, bottom: 30 })

              // 用户名
              FormItem({ label: '用户名', required: true }) {
                TextInput({ placeholder: '请输入用户名' })
                  .width('100%')
                  .height(40)
                  .type(InputType.Normal)
                  .onChange((value: string) => {
                    this.formData.username = value
                    this.validateUsername()
                  })
              }

              if (!this.validation.username.valid) {
                Text(this.validation.username.message)
                  .fontSize(12)
                  .fontColor(Color.Red)
                  .margin({ left: 20, top: -10, bottom: 10 })
                  .width('100%')
              }

              // 密码
              FormItem({ label: '密码', required: true }) {
                TextInput({ placeholder: '请输入密码' })
                  .width('100%')
                  .height(40)
                  .type(InputType.Password)
                  .onChange((value: string) => {
                    this.formData.password = value
                    this.validatePassword()
                  })
              }

              if (!this.validation.password.valid) {
                Text(this.validation.password.message)
                  .fontSize(12)
                  .fontColor(Color.Red)
                  .margin({ left: 20, top: -10, bottom: 10 })
                  .width('100%')
              }

              // 确认密码
              FormItem({ label: '确认密码', required: true }) {
                TextInput({ placeholder: '请再次输入密码' })
                  .width('100%')
                  .height(40)
                  .type(InputType.Password)
                  .onChange((value: string) => {
                    this.formData.confirmPassword = value
                    this.validateConfirmPassword()
                  })
              }

              if (!this.validation.confirmPassword.valid) {
                Text(this.validation.confirmPassword.message)
                  .fontSize(12)
                  .fontColor(Color.Red)
                  .margin({ left: 20, top: -10, bottom: 10 })
                  .width('100%')
              }

              // 性别
              FormItem({ label: '性别', required: true }) {
                Row() {
                  Radio({ value: 'male', group: 'gender' })
                    .checked(this.formData.gender === 0)
                    .onChange((checked: boolean) => {
                      if (checked) {
                        this.formData.gender = 0
                      }
                    })
                  Text('男').margin({ left: 5, right: 20 })

                  Radio({ value: 'female', group: 'gender' })
                    .checked(this.formData.gender === 1)
                    .onChange((checked: boolean) => {
                      if (checked) {
                        this.formData.gender = 1
                      }
                    })
                  Text('女').margin({ left: 5 })
                }
                .margin({ top: 10 })
              }

              // 年龄
              FormItem({ label: '年龄' }) {
                Slider({
                  value: this.formData.age,
                  min: 1,
                  max: 100,
                  step: 1,
                  style: SliderStyle.OutSet
                })
                  .width('100%')
                  .onChange((value: number) => {
                    this.formData.age = value
                  })

                Text(this.formData.age.toString())
                  .fontSize(16)
                  .margin({ top: 5 })
              }

              // 兴趣爱好
              FormItem({ label: '兴趣爱好' }) {
                Column() {
                  Checkbox({ name: 'reading' })
                    .select(this.formData.hobbies[0])
                    .onChange((checked: boolean) => {
                      this.formData.hobbies[0] = checked
                    })
                  Text('阅读').margin({ left: 5 })

                  Checkbox({ name: 'sports' })
                    .select(this.formData.hobbies[1])
                    .onChange((checked: boolean) => {
                      this.formData.hobbies[1] = checked
                    })
                  Text('运动').margin({ left: 5 })

                  Checkbox({ name: 'music' })
                    .select(this.formData.hobbies[2])
                    .onChange((checked: boolean) => {
                      this.formData.hobbies[2] = checked
                    })
                  Text('音乐').margin({ left: 5 })

                  Checkbox({ name: 'travel' })
                    .select(this.formData.hobbies[3])
                    .onChange((checked: boolean) => {
                      this.formData.hobbies[3] = checked
                    })
                  Text('旅行').margin({ left: 5 })
                }
                .margin({ top: 10 })
              }

              // 省市区选择
              FormItem({ label: '所在地区', required: true }) {
                Column() {
                  Select(this.getProvincedata())
                    .width('100%')
                    .height(40)
                    .onSelect((index: number) => {
                      this.handleProvinceChange(this.areaData[index].province)
                      this.cityIndex = -1;
                      this.cityName = '';
                    })

                  if (this.cityOptions.length > 0) {
                    Select(this.cityOptions)
                      .value(this.cityName)
                      .selected(this.cityIndex)
                      .width('100%')
                      .height(40)
                      .margin({ top: 10 })
                      .onSelect((index: number) => {
                        this.formData.city = this.cityOptions[index].value as string;
                        this.cityName = this.cityOptions[index].value as string;
                      })
                  }
                }
              }

              // 详细地址
              FormItem({ label: '详细地址', required: true }) {
                TextInput({ placeholder: '请输入详细地址' })
                  .width('100%')
                  .height(60)
                  .type(InputType.Normal)
                  .onChange((value: string) => {
                    this.formData.address = value
                    this.validateAddress()
                  })
              }

              if (!this.validation.address.valid) {
                Text(this.validation.address.message)
                  .fontSize(12)
                  .fontColor(Color.Red)
                  .margin({ left: 20, top: -10, bottom: 10 })
                  .width('100%')
              }

              // 配送时间
              FormItem({ label: '配送时间' }) {
                Select([
                  { value: '09:00-12:00' },
                  { value: '12:00-18:00' },
                  { value: '18:00-22:00' }
                ])// .selected(this.formData.deliveryTime)
                  .onSelect((index: number, text?: string | undefined) => {
                    this.formData.deliveryTime = text as string;
                  })

                  .width('100%')
                  .height(40)
              }

              // 支付方式
              FormItem({ label: '支付方式' }) {
                Column() {
                  Radio({ value: 'alipay', group: 'payment' })
                    .checked(this.formData.paymentMethod === 'alipay')
                    .onChange((checked: boolean) => {
                      if (checked) {
                        this.formData.paymentMethod = 'alipay'
                      }
                    })
                  Text('支付宝').margin({ left: 5 })

                  Radio({ value: 'wechat', group: 'payment' })
                    .checked(this.formData.paymentMethod === 'wechat')
                    .onChange((checked: boolean) => {
                      if (checked) {
                        this.formData.paymentMethod = 'wechat'
                      }
                    })
                  Text('微信支付').margin({ left: 5 })

                  Radio({ value: 'bank', group: 'payment' })
                    .checked(this.formData.paymentMethod === 'bank')
                    .onChange((checked: boolean) => {
                      if (checked) {
                        this.formData.paymentMethod = 'bank'
                      }
                    })
                  Text('银行卡').margin({ left: 5 })
                }
                .margin({ top: 10 })
              }

              // 优惠码
              FormItem({ label: '优惠码' }) {
                TextInput({ placeholder: '如有优惠码请填写' })
                  .width('100%')
                  .height(40)
                  .type(InputType.Normal)
                  .onChange((value: string) => {
                    this.formData.couponCode = value
                  })
              }

              // 用户协议
              Row() {
                Checkbox()
                  .select(this.formData.agree)
                  .onChange((checked: boolean) => {
                    this.formData.agree = checked
                    this.validateAgreement()
                  })

                Text('我已阅读并同意')
                  .fontSize(14)
                  .margin({ left: 5 })

                Text('《用户协议》')
                  .fontSize(14)
                  .fontColor(Color.Blue)
                  .onClick(() => {
                    // 跳转到用户协议页面
                    console.log('跳转到用户协议')
                  })
              }
              .margin({ top: 20, bottom: 10 })
              .alignItems(VerticalAlign.Center)

              if (!this.validation.agree.valid) {
                Text(this.validation.agree.message)
                  .fontSize(12)
                  .fontColor(Color.Red)
                  .margin({ left: 25, top: -10, bottom: 10 })
              }

              // 提交按钮
              Button(this.isSubmitting ? '提交中...' : '提交表单', { type: ButtonType.Capsule })
                .width('80%')
                .height(50)
                .margin({ top: 20, bottom: 30 })
                .backgroundColor('#007DFF')
                .enabled(!this.isSubmitting)
                .onClick(() => {
                  this.submitForm()
                })
            }
            .padding(20)
            .width('100%')
          }
        }
      }
      .width('100%')
      .height('100%')
    }.title('表单提交场景')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}

// 表单项组件
@Component
struct FormItem {
  @Prop label: string
  @Prop required: boolean = false
  @BuilderParam content: () => void

  build() {
    Column() {
      Row() {
        if (this.required) {
          Text('*')
            .fontSize(16)
            .fontColor(Color.Red)
            .margin({ right: 2 })
        }
        Text(this.label)
          .fontSize(16)
      }
      .width('100%')
      .justifyContent(FlexAlign.Start)
      .margin({ bottom: 8 })

      this.content()
    }
    .margin({ bottom: 15 })
    .width('100%')
  }
}