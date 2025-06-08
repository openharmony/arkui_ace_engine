
import { Component, Column, Text } from "@ohos.arkui"
import { State } from "@ohos.arkui"
import { ManyImportComponent86 } from "./manyImportFile86"
import { ManyImportComponent87 } from "./manyImportFile87"


@Component
export struct ManyImportComponent43 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent86()
            ManyImportComponent87()

        }
    }
}
