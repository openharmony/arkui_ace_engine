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

export interface RegionNode {
  name: string;
  code: string;
  children?: RegionNode[];
}

const area: RegionNode[] = [
  {
    'name': '山东省',
    'code': '370000',
    'children': [
      {
        'name': '青岛市',
        'code': '370200',
        'children': [
          {
            'name': '市南区',
            'code': '370202',
            'children': [
              {
                'name': '香港中路街道',
                'code': '370202001',
                'children': [
                  { 'name': '东海村', 'code': '370202001001' },
                  { 'name': '五四村', 'code': '370202001002' }
                ]
              },
              {
                'name': '八大关街道',
                'code': '370202002',
                'children': [
                  { 'name': '花石楼村', 'code': '370202002001' },
                  { 'name': '第二海水浴场村', 'code': '370202002002' }
                ]
              }
            ]
          },
          {
            'name': '市北区',
            'code': '370203',
            'children': [
              {
                'name': '敦化路街道',
                'code': '370203001',
                'children': [
                  { 'name': '敦化村', 'code': '370203001001' },
                  { 'name': '辽源村', 'code': '370203001002' }
                ]
              }
            ]
          }
        ]
      },
      {
        'name': '济南市',
        'code': '370100',
        'children': [
          {
            'name': '历下区',
            'code': '370102',
            'children': [
              {
                'name': '泉城路街道',
                'code': '370102001',
                'children': [
                  { 'name': '趵突泉村', 'code': '370102001001' },
                  { 'name': '泉城广场村', 'code': '370102001002' }
                ]
              }
            ]
          }
        ]
      }
    ]
  },
  {
    'name': '浙江省',
    'code': '330000',
    'children': [
      {
        'name': '杭州市',
        'code': '330100',
        'children': [
          {
            'name': '西湖区',
            'code': '330106',
            'children': [
              {
                'name': '灵隐街道',
                'code': '330106001',
                'children': [
                  { 'name': '灵隐村', 'code': '330106001001' },
                  { 'name': '玉泉村', 'code': '330106001002' }
                ]
              }
            ]
          }
        ]
      }
    ]
  }, {
  'name': '新疆维吾尔自治区',
  'code': '650000',
  'children': [
    {
      'name': '乌鲁木齐市',
      'code': '650100',
      'children': [
        {
          'name': '天山区',
          'code': '650102',
          'children': [
            {
              'name': '幸福路街道',
              'code': '650102001',
              'children': [
                { 'name': '幸福南路社区', 'code': '650102001001' },
                { 'name': '幸福东路社区', 'code': '650102001002' }
              ]
            },
            {
              'name': '解放南路街道',
              'code': '650102002',
              'children': [
                { 'name': '解放南路社区', 'code': '650102002001' },
                { 'name': '新疆大学南校区家属院社区', 'code': '650102002002' }
              ]
            }
          ]
        }
      ]
    },
    {
      'name': '伊犁哈萨克自治州',
      'code': '654000',
      'children': [
        {
          'name': '伊宁市',
          'code': '654002',
          'children': [
            {
              'name': '喀赞其街道',
              'code': '654002001',
              'children': [
                { 'name': '喀赞其社区', 'code': '654002001001' },
                { 'name': '伊犁河畔民族团结示范村', 'code': '654002001002' }
              ]
            },
            {
              'name': '解放路街道',
              'code': '654002002',
              'children': [
                { 'name': '解放路社区', 'code': '654002002001' },
                { 'name': '伊宁市第八中学家属区社区', 'code': '654002002002' }
              ]
            }
          ]
        }
      ]
    },
    {
      'name': '巴音郭楞蒙古自治州',
      'code': '652800',
      'children': [
        {
          'name': '且末县',
          'code': '652825',
          'children': [
            {
              'name': '塔提让镇',
              'code': '652825100',
              'children': [
                { 'name': '塔提让村', 'code': '652825100001' },
                { 'name': '巴音郭楞蒙古自治州且末县塔提让镇巴音郭楞村', 'code': '652825100002' }
              ]
            }
          ]
        }
      ]
    }
  ]
}
]

@Entry
@Component
struct MultiTextPicker {
  @State provinces: RegionNode[] = area
  @State cities: RegionNode[] = []
  @State districts: RegionNode[] = []
  @State streets: RegionNode[] = []
  @State villages: RegionNode[] = []
  @State selectedProvince: string = ''
  @State selectedCity: string = ''
  @State selectedDistrict: string = ''
  @State selectedStreet: string = ''
  @State selectedVillage: string = ''
  @State provinceFontSize: number = 15

  aboutToAppear() {
    if (this.provinces.length > 0) {
      this.selectedProvince = this.provinces[0].name
      this.cities = this.provinces[0].children ?? []
      if (this.cities.length > 0) {
        this.selectedCity = this.cities[0].name
        this.districts = this.cities[0].children ?? []
        if (this.districts.length > 0) {
          this.selectedDistrict = this.districts[0].name
          this.streets = this.districts[0].children ?? []
          if (this.streets.length > 0) {
            this.selectedStreet = this.streets[0].name
            this.villages = this.streets[0].children ?? []
            if (this.villages.length > 0) {
              this.selectedVillage = this.villages[0].name
            }
          }
        }
      }
    }
  }

  updateCascade(level: number, index: number) {
    if (level === 0) { // 省
      this.selectedProvince = this.provinces[index].name
      this.cities = this.provinces[index].children ?? []
      this.selectedCity = this.cities[0]?.name ?? ''
      this.updateCascade(1, 0)
    } else if (level === 1) { // 市
      this.selectedCity = this.cities[index].name
      this.districts = this.cities[index]?.children ?? []
      this.selectedDistrict = this.districts[0]?.name ?? ''
      this.updateCascade(2, 0)
    } else if (level === 2) { // 区
      this.selectedDistrict = this.districts[index].name
      this.streets = this.districts[index]?.children ?? []
      this.selectedStreet = this.streets[0]?.name ?? ''
      this.updateCascade(3, 0)
    } else if (level === 3) { // 街道
      this.selectedStreet = this.streets[index].name
      this.villages = this.streets[index]?.children ?? []
      this.selectedVillage = this.villages[0]?.name ?? ''
    } else if (level === 4) { // 村
      this.selectedVillage = this.villages[index].name
    }
  }

  build() {
    Stack({ alignContent: Alignment.Center }) {
      Row() {
        // 省
        TextPicker({
          range: this.provinces.map(item => item.name),
          selected: this.selectedProvince ? this.provinces.findIndex(item => item.name === this.selectedProvince) : 0
        })
          .textStyle({ color: Color.Yellow, font: { size: 13, weight: FontWeight.Normal } })
          .selectedTextStyle({ color: Color.Blue, font: { size: this.provinceFontSize, weight: FontWeight.Bolder } })
          .width('20%')
          .onScrollStop((value: string | string[], index: number | number[]) => {
            this.provinceFontSize = 15
          })
          .onChange((value: string | string[], index: number | number[]) => {
            this.provinceFontSize = 8
            const idx = Array.isArray(index) ? index[0] : index
            this.updateCascade(0, idx)
          })

        // 市
        TextPicker({
          range: this.cities.map(item => item.name),
          selected: this.selectedCity ? this.cities.findIndex(item => item.name === this.selectedCity) : 0
        })
          .textStyle({ color: Color.Yellow, font: { size: 13, weight: FontWeight.Normal } })
          .selectedTextStyle({ color: Color.Blue, font: { size: 13, weight: FontWeight.Bolder } })
          .width('20%')
          .onChange((value: string | string[], index: number | number[]) => {
            const idx = Array.isArray(index) ? index[0] : index
            this.updateCascade(1, idx)
          })

        // 区
        TextPicker({
          range: this.districts.map(item => item.name),
          selected: this.selectedDistrict ? this.districts.findIndex(item => item.name === this.selectedDistrict) : 0
        })
          .textStyle({ color: Color.Yellow, font: { size: 13, weight: FontWeight.Normal } })
          .selectedTextStyle({ color: Color.Blue, font: { size: 13, weight: FontWeight.Bolder } })
          .width('20%')
          .onChange((value: string | string[], index: number | number[]) => {
            const idx = Array.isArray(index) ? index[0] : index
            this.updateCascade(2, idx)
          })

        // 街道
        TextPicker({
          range: this.streets.map(item => item.name),
          selected: this.selectedStreet ? this.streets.findIndex(item => item.name === this.selectedStreet) : 0
        })
          .textStyle({ color: Color.Yellow, font: { size: 13, weight: FontWeight.Normal } })
          .selectedTextStyle({ color: Color.Blue, font: { size: 13, weight: FontWeight.Bolder } })
          .width('20%')
          .onChange((value: string | string[], index: number | number[]) => {
            const idx = Array.isArray(index) ? index[0] : index
            this.updateCascade(3, idx)
          })

        // 村
        TextPicker({
          range: this.villages.map(item => item.name),
          selected: this.selectedVillage ? this.villages.findIndex(item => item.name === this.selectedVillage) : 0
        })
          .textStyle({ color: Color.Yellow, font: { size: 13, weight: FontWeight.Normal } })
          .selectedTextStyle({ color: Color.Blue, font: { size: 13, weight: FontWeight.Bolder } })
          .width('20%')
          .onChange((value: string | string[], index: number | number[]) => {
            const idx = Array.isArray(index) ? index[0] : index
            this.updateCascade(4, idx)
          })
      }
      .width('100%')
      .height(400)
      .backgroundColor(Color.White)
      .borderRadius({ topLeft: 16, topRight: 16 })
      .padding(16)

      // 居中叠加的 Text
      Text(this.selectedProvince)
        .fontSize(24)
        .fontWeight(FontWeight.Bold)
        .textAlign(TextAlign.Center)
        .backgroundColor('#ffffff88') // 半透明背景可选
        .padding(10)
        .borderRadius(8)
        .width('100%')
    }
    .width('100%')
    .height('100%')
  }
}
