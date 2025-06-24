
import { Component, Column, Text } from "@ohos.arkui"
import { State } from "@ohos.arkui"
import { ManyImportComponent162 } from "./manyImportFile162"
import { ManyImportComponent163 } from "./manyImportFile163"


@Component
export struct ManyImportComponent81 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent162()
            ManyImportComponent163()

        }
    }
}
