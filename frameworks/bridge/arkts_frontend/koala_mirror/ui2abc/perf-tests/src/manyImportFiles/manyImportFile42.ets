
import { Component, Column, Text } from "@ohos.arkui"
import { State } from "@ohos.arkui"
import { ManyImportComponent84 } from "./manyImportFile84"
import { ManyImportComponent85 } from "./manyImportFile85"


@Component
export struct ManyImportComponent42 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent84()
            ManyImportComponent85()

        }
    }
}
